#!/usr/bin/env python3
"""Run a ROM headless in mupen64plus and save its RDRAM at given frames.

  emu_ram.py ROM --frames N[,N...] --out RAM.bin [--m64p DIR] [--input SCRIPT]
             [--patch OFF=HEX ...] [--settings-of MD5]

DIR holds libmupen64plus.so.2 and mupen64plus-rsp-hle.so (the official
Linux bundle, unpacked; $M64P_DIR by default).  Without either, the
system's install is used (the core from the library path, the plugin and
the ROM catalog from the distribution's mupen64plus directories).  Audio
and input are the core's dummies, saves go to a temporary directory (a
blank EEPROM every run), and video is tools/src/m64p_vicount.c (build/tools/
m64p_vicount.so), which draws nothing and calls back at each frame asked
for: the core's own frame callback only fires from a real video plugin.
No controller is plugged in, or with --input, tools/src/m64p_inputscript.c
plays SCRIPT on controller 1: lines of `frame buttons` (hex BUTTONS words,
held from that frame on; # comments).  Either way the run is the same
every time.  RDRAM is read through the core's debugger API at each frame
(big-endian, as the N64 sees it), and the run stops at the last one.  With
several frames, RAM.bin is the RDRAMs one after another.

--patch writes HEX at ROM offset OFF before the run (and fixes the header
checksum).  The core picks per-game settings (save type, ...) from its
catalog, mupen64plus.ini, by the ROM's MD5; a patched or rebuilt ROM isn't
in it.  So each run gets a catalog of its own with one entry: the settings
that the catalog has for --settings-of (default: the ROM's own MD5 before
patching), under the MD5 of the ROM as run.

tools/shift_check.py uses it to compare a shifted build with the original.
Session is the core set up for one run, which tools/tas.py drives too
(Core parameters, a starting EEPROM, a callback at every VI, soft resets,
the CPU's cycle counter).
"""
import argparse
import array
import ctypes
import hashlib
import os
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from n64crc import header_crc  # noqa: E402

M64CMD_ROM_OPEN = 1
M64CMD_ROM_CLOSE = 2
M64CMD_EXECUTE = 5
M64CMD_STOP = 6
M64CMD_CORE_STATE_SET = 17
M64CMD_RESET = 19
M64CORE_SPEED_LIMITER = 5
M64PLUGIN_RSP = 1
M64PLUGIN_GFX = 2
M64PLUGIN_INPUT = 4
TOOLS = Path(__file__).resolve().parent.parent / "build/tools"
M64P_DBG_PTR_RDRAM = 1
M64P_CPU_REG_COP0 = 5
M64TYPE_INT = 1
M64TYPE_BOOL = 3
M64TYPE_STRING = 4
RDRAM_SIZE = 0x800000

DEBUG_CB = ctypes.CFUNCTYPE(None, ctypes.c_void_p, ctypes.c_int, ctypes.c_char_p)
STATE_CB = ctypes.CFUNCTYPE(None, ctypes.c_void_p, ctypes.c_int, ctypes.c_int)
FRAME_CB = ctypes.CFUNCTYPE(None, ctypes.c_uint)
ROMOPEN_CB = ctypes.CFUNCTYPE(None)
# the Core parameters set here that are booleans (the others are ints)
BOOL_PARAMS = {"RandomizeInterrupt", "DisableExtraMem"}


def read_script(path):
    """[(frame, buttons)] from an input script."""
    steps = []
    for line in Path(path).read_text().splitlines():
        line = line.split("#")[0].split()
        if line:
            steps.append((int(line[0], 0), int(line[1], 16)))
    return sorted(steps)


SYSTEM_PLUGIN_DIRS = ["/usr/lib/mupen64plus", "/usr/lib64/mupen64plus",
                      "/usr/lib/x86_64-linux-gnu/mupen64plus", "/usr/local/lib/mupen64plus"]
SYSTEM_DATA_DIRS = ["/usr/share/mupen64plus", "/usr/local/share/mupen64plus"]


def find_m64p(m64p):
    """(core library, RSP plugin, data directory): from a bundle directory,
    or the system's install when m64p is None."""
    if m64p:
        m64p = Path(m64p)
        return str(m64p / "libmupen64plus.so.2"), str(m64p / "mupen64plus-rsp-hle.so"), str(m64p)
    rsp = next((Path(d) / "mupen64plus-rsp-hle.so" for d in SYSTEM_PLUGIN_DIRS
                if (Path(d) / "mupen64plus-rsp-hle.so").exists()), None)
    data = next((d for d in SYSTEM_DATA_DIRS if Path(d).is_dir()), None)
    if rsp is None or data is None:
        sys.exit("no mupen64plus install found: pass --m64p or set $M64P_DIR")
    return "libmupen64plus.so.2", str(rsp), data


def catalog_entry(data_dir, md5):
    """The settings lines of mupen64plus.ini's entry for md5 (following
    RefMD5), without its own MD5 and CRC."""
    sections, cur = {}, None
    for line in (Path(data_dir) / "mupen64plus.ini").read_text(errors="replace").splitlines():
        line = line.strip()
        if line.startswith("[") and line.endswith("]"):
            cur = sections.setdefault(line[1:-1].upper(), [])
        elif cur is not None and "=" in line:
            cur.append(line)
    lines = sections.get(md5.upper())
    if lines is None:
        sys.exit(f"mupen64plus.ini has no entry for {md5}")
    ref = next((x.split("=", 1)[1] for x in lines if x.startswith("RefMD5=")), None)
    own = [x for x in lines if not x.startswith(("RefMD5=", "CRC="))]
    if ref:
        names = {x.split("=", 1)[0] for x in own}
        own += [x for x in catalog_entry(data_dir, ref) if x.split("=", 1)[0] not in names]
    return own


def prepare(data, patches, settings_md5, data_dir, out_dir):
    """The ROM as run (patched, checksum fixed) and a data directory whose
    catalog gives it the settings of settings_md5."""
    rom = bytearray(data)
    settings_md5 = settings_md5 or hashlib.md5(data).hexdigest()
    for off, b in patches:
        rom[off:off + len(b)] = b
    if patches:
        cic, crc = header_crc(rom)
        if cic is None:
            sys.exit("unknown boot code: can't fix the checksum after patching")
        rom[0x10:0x18] = crc[0].to_bytes(4, "big") + crc[1].to_bytes(4, "big")
    entry = catalog_entry(data_dir, settings_md5)
    (Path(out_dir) / "mupen64plus.ini").write_text(
        f"[{hashlib.md5(rom).hexdigest().upper()}]\n" + "\n".join(entry) + "\n")
    return bytes(rom)


class Session:
    """One run of the core: started (config, ROM, plugins) but not running
    until run().  The core can only start once per process.

    config is extra Core parameters ({name: int}); eeprom, the EEPROM's
    contents to start from (a blank one is all 0xFF in this core).  With
    input=True the input plugin is attached (self.inp), to be set up before
    run().  on_romopen is called once the machine is set up, before the
    game's first instruction."""

    def __init__(self, rom, m64p=None, patches=(), settings_md5=None, quiet=True,
                 config=None, eeprom=None, input=False, on_romopen=None):
        core_lib, rsp_lib, data_dir = find_m64p(m64p)
        self.core = core = ctypes.CDLL(core_lib)
        self.rsp = rsp = ctypes.CDLL(rsp_lib)
        self.vic = vic = ctypes.CDLL(str(TOOLS / "m64p_vicount.so"))
        self.inp = inp = ctypes.CDLL(str(TOOLS / "m64p_inputscript.so")) if input else None
        core.DebugMemGetPointer.restype = ctypes.c_void_p
        core.DebugGetCPUDataPtr.restype = ctypes.c_void_p

        @DEBUG_CB
        def debug(_ctx, level, msg):
            if not quiet or level <= 1:  # M64MSG_ERROR
                print(f"m64p: {msg.decode(errors='replace')}", file=sys.stderr)

        @STATE_CB
        def state(_ctx, _param, _value):
            pass

        self._tmp = tempfile.TemporaryDirectory()
        cfg = self._tmp.name
        self._keep = [debug, state]
        data = prepare(Path(rom).read_bytes(), patches, settings_md5, data_dir, cfg)
        err = core.CoreStartup(0x020001, cfg.encode(), cfg.encode(), None, debug, None, state)
        if err:
            sys.exit(f"CoreStartup failed ({err})")
        # saves (the EEPROM) in the run's own directory, so every run starts
        # blank: the core's default is the user's data directory, where a
        # save written by one run would change the next
        sec = ctypes.c_void_p()
        if core.ConfigOpenSection(b"Core", ctypes.byref(sec)):
            sys.exit("opening the Core config section failed")
        for name in (b"SaveSRAMPath", b"SaveStatePath"):
            path = ctypes.c_char_p(cfg.encode())
            if core.ConfigSetParameter(sec, name, M64TYPE_STRING, path):
                sys.exit(f"setting {name.decode()} failed")
        # the core randomizes PI/SI interrupt timing by default, seeded from
        # the host's clock: runs started in different seconds would differ
        params = {"RandomizeInterrupt": 0, **(config or {})}
        for name, value in params.items():
            v = ctypes.c_int(value)
            kind = M64TYPE_BOOL if name in BOOL_PARAMS else M64TYPE_INT
            if core.ConfigSetParameter(sec, name.encode(), kind, ctypes.byref(v)):
                sys.exit(f"setting {name} failed")
        if eeprom is not None:
            # the core looks for <SaveSRAMPath><goodname>.eep first
            good = next((x.split("=", 1)[1] for x in
                         (Path(cfg) / "mupen64plus.ini").read_text().splitlines()
                         if x.startswith("GoodName=")), None)
            if good is None:
                sys.exit("the ROM has no GoodName in the catalog: can't place its EEPROM")
            (Path(cfg) / f"{good}.eep").write_bytes(eeprom)
        err = rsp.PluginStartup(ctypes.c_void_p(core._handle), None, debug)
        if err:
            sys.exit(f"RSP PluginStartup failed ({err})")
        self._rom = ctypes.create_string_buffer(data, len(data))
        if core.CoreDoCommand(M64CMD_ROM_OPEN, len(data), self._rom):
            sys.exit("ROM_OPEN failed")
        self._romopen = ROMOPEN_CB(on_romopen or (lambda: None))
        vic.vicount_romopen(self._romopen)
        if core.CoreAttachPlugin(M64PLUGIN_GFX, ctypes.c_void_p(vic._handle)):
            sys.exit("attaching the frame counter failed")
        if inp is not None:
            if inp.PluginStartup(ctypes.c_void_p(core._handle), None, debug):
                sys.exit("input PluginStartup failed")
            if core.CoreAttachPlugin(M64PLUGIN_INPUT, ctypes.c_void_p(inp._handle)):
                sys.exit("attaching the input plugin failed")
        if core.CoreAttachPlugin(M64PLUGIN_RSP, ctypes.c_void_p(rsp._handle)):
            sys.exit("attaching the RSP plugin failed")

    def frames(self):
        """The VIs so far."""
        return self.vic.vicount_frames()

    def rdram_ptr(self):
        return self.core.DebugMemGetPointer(M64P_DBG_PTR_RDRAM)

    def rdram(self):
        """All of RDRAM, big-endian, as the N64 sees it (None if unreadable)."""
        ptr = self.rdram_ptr()
        if not ptr:
            return None
        # the core keeps RDRAM as host-order 32-bit words
        words = array.array("I", ctypes.string_at(ptr, RDRAM_SIZE))
        if sys.byteorder == "little":
            words.byteswap()
        return words.tobytes()

    def word(self, addr):
        """The 32-bit word at a (KSEG0 or physical) address."""
        return ctypes.c_uint32.from_address(self.rdram_ptr() + (addr & 0x7FFFFC)).value

    def count(self):
        """The CPU's cycle counter (COUNT, cop0 register 9)."""
        cp0 = self.core.DebugGetCPUDataPtr(M64P_CPU_REG_COP0)
        return ctypes.c_uint32.from_address(cp0 + 9 * 4).value

    def reset(self, hard=False):
        self.core.CoreDoCommand(M64CMD_RESET, int(hard), None)

    def stop(self):
        self.core.CoreDoCommand(M64CMD_STOP, 0, None)

    def run(self, first, on_frame):
        """Run until stopped: on_frame(frame) is called at frame `first` and
        returns the next frame to be called at, or None to stop there."""

        @FRAME_CB
        def frame(index):
            nxt = on_frame(index)
            if nxt is None:
                self.stop()
            else:
                self.vic.vicount_at(nxt)

        self.vic.vicount_set(first, frame)
        # as fast as the host goes: the game only sees emulated time
        off = ctypes.c_int(0)
        self.core.CoreDoCommand(M64CMD_CORE_STATE_SET, M64CORE_SPEED_LIMITER, ctypes.byref(off))
        self.core.CoreDoCommand(M64CMD_EXECUTE, 0, None)
        self.core.CoreDoCommand(M64CMD_ROM_CLOSE, 0, None)
        self.core.CoreShutdown()
        self._tmp.cleanup()


def run(rom, frames, m64p=None, script=None, patches=(), settings_md5=None,
        quiet=os.environ.get("EMU_VERBOSE") is None):
    """{frame: RDRAM} at each of frames (an int gives just that RDRAM)."""
    single = isinstance(frames, int)
    todo = sorted({frames} if single else set(frames))
    emu = Session(rom, m64p, patches, settings_md5, quiet, input=script is not None)
    if script:
        steps = read_script(script)
        n = len(steps)
        fr = (ctypes.c_uint * n)(*[f for f, _ in steps])
        bt = (ctypes.c_uint * n)(*[b for _, b in steps])
        keep = (fr, bt)  # noqa: F841 (alive for the run)
        now = ctypes.cast(emu.vic.vicount_frames, ctypes.c_void_p)
        emu.inp.inputscript_set(now, fr, bt, n)

    ram = {}

    def frame(index):
        ram[index] = emu.rdram()
        later = [f for f in todo if f > index]
        return later[0] if ram[index] is not None and later else None

    emu.run(todo[0], frame)
    missing = [f for f in todo if ram.get(f) is None]
    if missing:
        sys.exit(f"the run ended before frame {missing[0]}, or RDRAM couldn't be read")
    return ram[todo[0]] if single else ram


def parse_patch(text):
    off, _, data = text.partition("=")
    return int(off, 0), bytes.fromhex(data)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("rom")
    ap.add_argument("--frames", required=True, help="frame numbers, comma-separated")
    ap.add_argument("--out", required=True)
    ap.add_argument("--m64p", default=os.environ.get("M64P_DIR"))
    ap.add_argument("--input", help="input script for controller 1")
    ap.add_argument("--patch", action="append", type=parse_patch, default=[],
                    help="OFF=HEX: bytes to write into the ROM first")
    ap.add_argument("--settings-of", help="the MD5 whose mupen64plus.ini settings to use")
    a = ap.parse_args()
    frames = sorted({int(x, 0) for x in a.frames.split(",")})
    ram = run(a.rom, frames, a.m64p, a.input, a.patch, a.settings_of)
    Path(a.out).write_bytes(b"".join(ram[f] for f in frames))


if __name__ == "__main__":
    main()
