#!/usr/bin/env python3
"""Play a TAS movie headless in mupen64plus and report the game's progress.

  tas.py run MOVIE ROM [--json OUT] [--frames N] [options]
  tas.py check MOVIE ROM_A ROM_B [--frames N]   run both, compare
  tas.py compare A.json B.json
  tas.py fetch [MOVIE]
  tas.py info MOVIE

MOVIE is a known movie's id (`tas.py fetch` lists them and downloads one
into build/tas/movies/ if it isn't there) or a path to a .bk2 or .m64.
docs/TAS.md has the details, and how far the movies sync (they don't, all
the way).

The movie's input is played by tools/src/m64p_inputscript.c, by frame
(BizHawk's .bk2: one line per VI, BizHawk's first two VIs before it) or by
poll (mupen64-rr's .m64: one sample per read of the controller), on
mupen64plus 2.6.0 set up as close to the movie's emulator as it goes:
BizHawk's frame length (1500 counts a scanline: the VI clock in the
core's memory is changed at ROM open), no RandomizeInterrupt, its count
per op, SI DMA time, Expansion Pak setting and cached interpreter, its
blank EEPROM (zeros), and its controller (BizHawk's input plugin answers
the joybus itself).  The video plugin is m64p_vicount.c, which raises the
RDP's interrupt for each display list with a full sync, as a real plugin
does.  The core's own frames are VIs (tools/src/m64p_vicount.c counts
them); soft resets in the movie happen at their frame.

Each VI the run records:
- the overlay at 0x80043000 (against the overlays of the ROM being run),
  once it has stayed the same for two VIs;
- the stage timer (the in-game clock shown in stages, hundredths of a
  second; it runs on through a lost life and starts over with the next
  stage) whenever it starts over: the value it had then is the stage's
  time, as the clear screen shows it;
- the soft resets, and the VIs where the game didn't read the controller.

`check` and `compare` take two runs (an original ROM and a rebuilt or
shifted one, both unpinned) and report the first checkpoint that differs.
"""
import argparse
import array
import ctypes
import hashlib
import io
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
import urllib.request
import zipfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import emu_ram  # noqa: E402
import layout  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
MOVIES_DIR = ROOT / "build/tas/movies"
OVERLAY_VRAM = 0x80043000
JP_SHA1 = "4813b147d552f72fdb0b306469bf9aa0f820fd5b"
JP_MD5 = "8183688A4B7D0A390496B5655BCD252E"

# Movies of this game on TASVideos (all on Baku Bomberman, jp).  The files
# are theirs and aren't committed: `fetch` downloads them from the
# publication's own download handler (the site asks not to link the files
# directly, and republishing has conditions).  zip_sha1 is what the handler
# serves, sha1 the movie in it.
MOVIES = {
    "4908M": {
        "page": "https://tasvideos.org/4908M",
        "title": "Bomberman 64 by zvsp in 21:40.57 (any%, BizHawk 2.8, current)",
        "zip_sha1": "8164fb6f0ded53e8d4996d3f0db9190a81fdf516",
        "file": "zvsp-bomberman64.bk2",
        "sha1": "09cfd140372fb2c58a41a5ad37b0cf0af1ee6e75",
        # the first stage times, read off the clear screens of the
        # publication's encode (Blue Resort 1 and 2)
        "stage_times": [1431, 316],
    },
    "2053M": {
        "page": "https://tasvideos.org/2053M",
        "title": "Bomberman 64 by Nahoc in 23:38.55 (any%, mupen64-rr, obsoleted)",
        "zip_sha1": "4cb14f8fd1f33bbe728830fb9d833e11242d29bd",
        "file": "nahoc-bomberman64.m64",
        "sha1": "ccff1361a6e0542df4e907b35407b137c0bedb09",
    },
    "2350M": {
        "page": "https://tasvideos.org/2350M",
        "title": 'Bomberman 64 "100%" by zvsp in 1:01:36.02 (mupen64-rr)',
        "zip_sha1": "f873b56911c2770ca522857fe5a84f7b08b07482",
        "file": "zvsp-bomberman64-100p.m64",
        "sha1": "9019259d65f004a73fb11ae2256175e390e15a31",
    },
}

# The stage timer: main_code bss, u32.  Its label (us's name, as every
# version has) and its address in the original jp ROM; a build's ELF gives
# it elsewhere.
STAGE_TIMER = ("D_802AC640", 0x802AB870)


def sha1(data):
    return hashlib.sha1(data).hexdigest()


def fetch(movie_id):
    """The movie file's path, downloaded (and checked) if it isn't there."""
    m = MOVIES[movie_id]
    path = MOVIES_DIR / movie_id / m["file"]
    if not path.exists():
        url = m["page"] + "?handler=Download"
        print(f"fetching {url}", file=sys.stderr)
        req = urllib.request.Request(url, headers={"User-Agent": "bm64 decomp tools/tas.py"})
        with urllib.request.urlopen(req, timeout=60) as r:
            data = r.read()
        if sha1(data) != m["zip_sha1"]:
            sys.exit(f"{url}: sha1 {sha1(data)}, expected {m['zip_sha1']}")
        with zipfile.ZipFile(io.BytesIO(data)) as z:
            member = z.read(m["file"])
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(member)
    if sha1(path.read_bytes()) != m["sha1"]:
        sys.exit(f"{path}: sha1 {sha1(path.read_bytes())}, expected {m['sha1']}")
    return path


def resolve(movie):
    return fetch(movie) if movie in MOVIES else Path(movie)


# BizHawk's N64 controller (N64Input.cs): button -> BUTTONS bit
BK2_BUTTONS = {"DPad R": 0, "DPad L": 1, "DPad D": 2, "DPad U": 3, "Start": 4, "Z": 5,
               "B": 6, "A": 7, "C Right": 8, "C Left": 9, "C Down": 10, "C Up": 11,
               "R": 12, "L": 13}


class Movie:
    """A movie's input, keys[frame][controller] (BUTTONS words), how it's
    counted (by_poll), its soft resets, and what it needs of the emulator."""

    def __init__(self, path):
        self.path = Path(path)
        self.resets = []
        self.power = []
        self.settings = {}
        self.vis = None
        if self.path.suffix == ".bk2":
            self._bk2()
        elif self.path.suffix == ".m64":
            self._m64()
        else:
            sys.exit(f"{path}: not a .bk2 or .m64")

    def _bk2(self):
        """BizHawk: Header.txt, SyncSettings.json and the Input Log, one line
        per frame (a VI), whether the game read the controller or not."""
        self.by_poll = False
        with zipfile.ZipFile(self.path) as z:
            header = dict(line.split(" ", 1) for line in
                          z.read("Header.txt").decode().splitlines() if " " in line)
            sync = json.loads(z.read("SyncSettings.json"))["o"]
            log = z.read("Input Log.txt").decode().splitlines()
        if header.get("Platform") != "N64":
            sys.exit(f"{self.path}: platform {header.get('Platform')}")
        self.header = header
        self.rom_sha1 = header.get("SHA1", "").lower()
        self.emulator = f"BizHawk {header.get('emuVersion', '?')}, core {header.get('Core', '?')}"
        self.expansion = not sync.get("DisableExpansionSlot", False)
        ctrl = sync.get("Controllers", [])
        self.present = sum(1 << i for i, c in enumerate(ctrl) if c.get("IsConnected"))
        self.paks = [c.get("PakType") for c in ctrl]
        # Core: 0 pure interpreter, 1 interpreter (mupen's cached one);
        # Rsp: 0 HLE; VideoPlugin: 4 GLideN64
        self.settings = {k: sync.get(k) for k in ("Core", "Rsp", "VideoPlugin",
                                                 "DisableExpansionSlot")}
        self.settings["PakType"] = self.paks
        self.interpreter = {0: 0, 1: 1}.get(sync.get("Core"), 1)
        key = next(x for x in log if x.startswith("LogKey:"))[len("LogKey:"):]
        groups = [g.strip("|").split("|") for g in key.split("#") if g]
        self.keys = []
        for line in log:
            if not line.startswith("|"):
                continue
            frame = [0, 0, 0, 0]
            for names, seg in zip(groups, line.strip().strip("|").split("|")):
                axes = [n for n in names if "Axis" in n]
                fields = seg.split(",")
                values = {n: int(v) for n, v in zip(axes, fields)}
                buttons = fields[len(axes)] if len(fields) > len(axes) else ""
                pressed = {n for n, c in zip([n for n in names if "Axis" not in n], buttons)
                           if c != "."}
                if "Reset" in pressed:
                    self.resets.append(len(self.keys))
                if "Power" in pressed:
                    self.power.append(len(self.keys))
                if not names or not names[0].startswith("P"):
                    continue
                p = names[0].split()[0]
                word = sum(1 << bit for b, bit in BK2_BUTTONS.items() if f"{p} {b}" in pressed)
                x, y = values.get(f"{p} X Axis", 0), values.get(f"{p} Y Axis", 0)
                # the "A" directions are the stick at full tilt
                if f"{p} A Left" in pressed:
                    x = -128
                elif f"{p} A Right" in pressed:
                    x = 127
                if f"{p} A Up" in pressed:
                    y = 127
                elif f"{p} A Down" in pressed:
                    y = -128
                frame[int(p[1:]) - 1] = word | (x & 0xFF) << 16 | (y & 0xFF) << 24
            self.keys.append(frame)
        if self.power:
            sys.exit(f"{self.path}: power cycles in the movie aren't supported")

    def _m64(self):
        """mupen64-rr (version 3): a 0x400 header, then a BUTTONS word per
        plugged-in controller per sample, a sample per read of controller
        1.  0xC000 (both reserved bits) is a soft reset."""
        self.by_poll = True
        d = self.path.read_bytes()
        if d[:4] != b"M64\x1a":
            sys.exit(f"{self.path}: not an .m64")
        version, = struct.unpack_from("<I", d, 4)
        vis, rerecords = struct.unpack_from("<II", d, 0xC)
        ncont = d[0x15]
        samples, = struct.unpack_from("<I", d, 0x18)
        start, = struct.unpack_from("<H", d, 0x1C)
        flags, = struct.unpack_from("<I", d, 0x20)
        if start != 2:
            sys.exit(f"{self.path}: starts from a savestate, not power-on")

        def text(o, n):
            return d[o:o + n].split(b"\0")[0].decode("utf-8", "replace")
        self.header = {"version": version, "VIs": vis, "rerecords": rerecords,
                       "samples": samples, "rom": text(0xC4, 32),
                       "video": text(0x122, 64), "audio": text(0x162, 64),
                       "input": text(0x1A2, 64), "rsp": text(0x1E2, 64),
                       "author": text(0x222, 222)}
        self.rom_sha1 = None  # the header has the ROM's CRC, not a hash
        self.emulator = "mupen64-rr"
        self.expansion = True  # Mupen64 0.5 always has 8 MiB
        self.interpreter = 1
        self.present = flags & 0xF
        self.paks = None
        self.vis = vis
        plugged = [c for c in range(4) if self.present >> c & 1]
        body = d[0x400 if version == 3 else 0x200:]
        self.keys = []
        for i in range(min(samples, len(body) // (4 * ncont))):
            frame = [0, 0, 0, 0]
            for j, c in enumerate(plugged):
                frame[c], = struct.unpack_from("<I", body, (i * ncont + j) * 4)
            if frame[plugged[0]] == 0xC000:
                self.resets.append(i)
            self.keys.append(frame)

    def describe(self):
        out = [f"{self.path.name}: {self.emulator}, {len(self.keys)} "
               f"{'samples (controller reads)' if self.by_poll else 'frames (VIs)'}"]
        out += [f"  {k}: {v}" for k, v in self.header.items()]
        if self.settings:
            out.append(f"  sync settings: {self.settings}")
        out.append(f"  controllers plugged in: {self.present:04b} (bit 0 = P1); "
                   f"Expansion Pak: {'yes' if self.expansion else 'no'}")
        if self.resets:
            what = "samples" if self.by_poll else "frames"
            out.append(f"  soft resets at {what} {self.resets}")
        return "\n".join(out)


VI_CLOCK_NTSC = 48681812
# BizHawk 2.8's core (and Mupen64 0.5) times a frame as (V_SYNC + 1) lines
# of 1500 counts; 2.6.0 as (clock / 60) / (V_SYNC + 1) a line, rounded down.
# A clock of 1500 * 60 * 526 gives 1500 a line at NTSC's V_SYNC (525):
# 789000 counts a frame instead of 811092.
VI_CLOCK_BIZHAWK = 1500 * 60 * 526


def find_vi_clock():
    """The address of struct vi_controller's clock in the core (mupen64plus
    2.6.0, device/rcp/vi/vi_controller.h: 14 registers, field, delay,
    clock, expected_refresh_rate, ...).  It isn't exported, so it's found in
    the core's writable memory by the clock and refresh rate (60) together,
    which have to be there exactly once."""
    hits = []
    pattern = struct.pack("<II", VI_CLOCK_NTSC, 60)
    with open("/proc/self/maps") as f:
        maps = [line.split() for line in f]
    ours = False
    for m in maps:  # the core's mappings and the anonymous ones after them
        if len(m) >= 6:
            ours = "libmupen64plus" in m[5]
        if not ours or "rw" not in m[1]:
            continue
        lo, hi = (int(x, 16) for x in m[0].split("-"))
        hits += [lo + h.start() for h in re.finditer(re.escape(pattern), ctypes.string_at(lo, hi - lo))]
    return hits[0] if len(hits) == 1 else None


class Overlays:
    """Identifies the overlay at 0x80043000 against a ROM's overlays."""

    def __init__(self, rom_data):
        self.by_head = {}
        for b, e, data in layout.overlays(rom_data):
            self.by_head.setdefault(data[:32], []).append((layout.overlay_name(b, e), data))

    def identify(self, here):
        """The overlay whose text is in RAM (most words matching, over half)."""
        best, score = None, 0
        for name, data in self.by_head.get(here[:32], []):
            n = len(data) // 4
            same = sum(1 for o in range(0, n * 4, 4) if here[o:o + 4] == data[o:o + 4])
            if same * 2 > n and same > score:
                best, score = name, same
        return best


class BizHawkSession(emu_ram.Session):
    """BizHawk 2.8's own mupen64plus core (tools/bizhawk_core.sh builds it
    for Linux), driven the way BizHawk drives it: the emulation thread
    stops at every VI until the front end advances a frame, and frames are
    advanced from boot.  Same interface as emu_ram.Session.  A reference:
    the plugins are still ours (BizHawk's movie used GLideN64)."""

    M64CMD_ADVANCE_FRAME = 20
    M64CMD_SET_VI_CALLBACK = 21

    def __init__(self, libdir, rom, config, quiet=True):
        import threading
        libdir = Path(libdir)
        self.core = core = ctypes.CDLL(str(libdir / "libmupen64plus.so.2"))
        self.rsp = rsp = ctypes.CDLL(str(libdir / "mupen64plus-rsp-hle.so"))
        self.vic = vic = ctypes.CDLL(str(emu_ram.TOOLS / "m64p_vicount.so"))
        self.inp = inp = ctypes.CDLL(str(emu_ram.TOOLS / "m64p_inputscript.so"))
        core.DebugMemGetPointer.restype = ctypes.c_void_p
        core.DebugGetCPUDataPtr.restype = ctypes.c_void_p
        self.vi_event, self.started = threading.Event(), threading.Event()
        self.threading = threading

        @emu_ram.DEBUG_CB
        def debug(_ctx, level, msg):
            if not quiet or level <= 1:
                print(f"bizhawk-m64p: {msg.decode(errors='replace')}", file=sys.stderr)

        @emu_ram.STATE_CB
        def state(_ctx, _param, _value):
            pass

        @ctypes.CFUNCTYPE(None)
        def vi():
            self.vi_event.set()

        @ctypes.CFUNCTYPE(None)
        def started():
            self.started.set()

        self._keep = [debug, state, vi, started]
        self._started_cb = started
        self._tmp = tempfile.TemporaryDirectory()
        cfg = self._tmp.name.encode()
        if core.CoreStartup(0x020001, cfg, cfg, b"Core", debug, None, state):
            sys.exit("CoreStartup failed")
        sec = ctypes.c_void_p()
        core.ConfigOpenSection(b"Core", ctypes.byref(sec))
        for name, value in config.items():
            v = ctypes.c_int(value)
            core.ConfigSetParameter(sec, name.encode(), emu_ram.M64TYPE_INT, ctypes.byref(v))
        data = Path(rom).read_bytes()
        self._rom = ctypes.create_string_buffer(data, len(data))
        if core.CoreDoCommand(emu_ram.M64CMD_ROM_OPEN, len(data), self._rom):
            sys.exit("ROM_OPEN failed")
        if core.CoreDoCommand(self.M64CMD_SET_VI_CALLBACK, 0, vi):
            sys.exit("SET_VI_CALLBACK failed")
        if rsp.PluginStartup(ctypes.c_void_p(core._handle), None, debug):
            sys.exit("RSP PluginStartup failed")
        if inp.PluginStartup(ctypes.c_void_p(core._handle), None, debug):
            sys.exit("input PluginStartup failed")
        for kind, lib in ((emu_ram.M64PLUGIN_GFX, vic), (emu_ram.M64PLUGIN_INPUT, inp),
                          (emu_ram.M64PLUGIN_RSP, rsp)):
            if core.CoreAttachPlugin(kind, ctypes.c_void_p(lib._handle)):
                sys.exit(f"attaching plugin {kind} failed")

    def advance(self):
        self.vi_event.clear()
        self.core.CoreDoCommand(self.M64CMD_ADVANCE_FRAME, 0, None)
        while not self.vi_event.wait(1):
            if not self.thread.is_alive():
                return False
        return True

    def run(self, first, on_frame):
        def execute():
            self.core.CoreDoCommand(emu_ram.M64CMD_EXECUTE, 0,
                                    ctypes.cast(self._started_cb, ctypes.c_void_p))

        self.vic.vicount_set(0, None)
        self.thread = self.threading.Thread(target=execute, daemon=True)
        self.thread.start()
        self.started.wait()
        nxt = first
        while nxt is not None and self.advance():
            if self.frames() >= nxt:
                nxt = on_frame(self.frames())
        self.core.CoreDoCommand(emu_ram.M64CMD_STOP, 0, None)
        self.core.CoreDoCommand(self.M64CMD_ADVANCE_FRAME, 0, None)
        self.thread.join(5)


def read_ram(emu, addr, size):
    """RDRAM bytes, big-endian."""
    words = array.array("I", ctypes.string_at(emu.rdram_ptr() + (addr & 0x7FFFFC), size))
    if sys.byteorder == "little":
        words.byteswap()
    return words.tobytes()


def elf_symbol(elf, name):
    out = subprocess.run(["mips-linux-gnu-objdump", "-tw", str(elf)], capture_output=True,
                         check=True, text=True).stdout
    for line in out.splitlines():
        p = line.split()
        if p and p[-1] == name:
            return int(p[0], 16)
    sys.exit(f"{elf}: no symbol {name}")


def timer_address(rom, rom_sha1, elf=None):
    """The stage timer's address in this ROM: from its ELF (given, or the
    build's next to the ROM), or the original's; None if unknown."""
    if elf is None and rom_sha1 != JP_SHA1:
        guess = Path(rom).with_suffix(".elf")
        elf = guess if guess.exists() else None
    if elf:
        return elf_symbol(elf, STAGE_TIMER[0])
    return STAGE_TIMER[1] if rom_sha1 == JP_SHA1 else None


def play(movie, rom, frames=None, offset=2, vi="bizhawk", raw=True, eeprom=0x00, dp=1,
         elf=None, settings_md5=JP_MD5, bizhawk=None, dumps=(), dump_dir=None, hook=None,
         quiet=True, log=None):
    """Run the movie on the ROM; returns the report (a dict).

    offset: a poll during VI n reads movie frame n - offset (BizHawk
    advances two frames after boot before the movie's first).  vi:
    "bizhawk" changes the core's VI clock so that a frame is as long as in
    BizHawk 2.8's core, "core" leaves it.  raw: the controller answers like
    BizHawk's input plugin.  eeprom: the byte a blank EEPROM is filled with
    (BizHawk's is zeros; None for the core's, 0xFF).  dp: the RDP interrupt
    (m64p_vicount.c).  bizhawk: a directory with BizHawk's own core instead
    (tools/bizhawk_core.sh)."""
    rom_data = Path(rom).read_bytes()
    rom_sha1 = sha1(rom_data)
    ovl = Overlays(rom_data)
    timer = timer_address(rom, rom_sha1, elf)
    total = len(movie.keys)
    if frames is None:
        frames = (total + offset if not movie.by_poll else int(movie.vis * 1.05)) + 600
    config = {"R4300Emulator": movie.interpreter, "CountPerOp": 2, "SiDmaDuration": 0x900,
              "DisableExtraMem": 0 if movie.expansion else 1}

    def romopen():
        if vi == "bizhawk":
            at = find_vi_clock()
            if at is None:
                sys.exit("couldn't find the core's VI clock to set BizHawk's frame length")
            ctypes.c_uint32.from_address(at).value = VI_CLOCK_BIZHAWK

    if bizhawk:
        emu = BizHawkSession(bizhawk, rom, {"R4300Emulator": movie.interpreter,
                                            "DisableExtraMem": config["DisableExtraMem"]},
                             quiet=quiet)
    else:
        emu = emu_ram.Session(rom, quiet=quiet, config=config, input=True, on_romopen=romopen,
                              settings_md5=settings_md5,
                              eeprom=None if eeprom is None else bytes([eeprom]) * 0x800)
    emu.vic.vicount_dp(dp)
    flat = [k for frame in movie.keys for k in frame]
    keys = (ctypes.c_uint * len(flat))(*flat)
    now = ctypes.cast(emu.vic.vicount_frames, ctypes.c_void_p)
    emu.inp.inputscript_controllers(movie.present, movie.present if raw else 0)
    emu.inp.inputscript_movie(now, keys, total, offset, int(movie.by_poll))

    events = []  # [frame, kind, value]
    lag = []     # [first, last] VIs without a read of the controller
    st = {"head": None, "stable": 0, "ovl": None, "polls": 0, "lag": None, "timer": 0,
          "resets": sorted(movie.resets) if not movie.by_poll else []}

    def event(n, kind, value):
        events.append([n, kind, value])
        if log:
            where = f"movie frame {n - offset}" if not movie.by_poll else f"poll {st['polls']}"
            print(f"{n:6d} {kind:7s} {value}  ({where})", file=log, flush=True)

    def on_frame(n):
        # a reset happens at the start of its movie frame, as in BizHawk
        if st["resets"] and n - offset == st["resets"][0]:
            st["resets"].pop(0)
            emu.reset()
            event(n, "reset", None)
        if movie.by_poll and emu.inp.inputscript_reset_wanted():
            emu.reset()
            event(n, "reset", None)
        p = emu.inp.inputscript_polls()
        if p == st["polls"]:
            if st["lag"] is None:
                st["lag"] = n
        else:
            if st["lag"] is not None:
                lag.append([st["lag"], n - 1])
                st["lag"] = None
            st["polls"] = p
        head = read_ram(emu, OVERLAY_VRAM, 64)
        if head != st["head"]:
            st["head"], st["stable"] = head, 0
        else:
            st["stable"] += 1
            if st["stable"] == 2:
                name = ovl.identify(read_ram(emu, OVERLAY_VRAM, 0x20000))
                if name != st["ovl"]:
                    st["ovl"] = name
                    event(n - 2, "overlay", name)
        if timer is not None:
            t = emu.word(timer)
            if t < st["timer"] and st["timer"] >= 10:
                event(n, "stage", st["timer"])
            st["timer"] = t
        if hook:
            hook(emu, n)
        if n in dumps:
            Path(dump_dir).mkdir(parents=True, exist_ok=True)
            (Path(dump_dir) / f"{n}.bin").write_bytes(emu.rdram())
        if movie.by_poll and p >= total + 600:
            return None
        return n + 1 if n < frames else None

    emu.run(1, on_frame)
    return {
        "movie": movie.path.name, "rom": str(rom), "rom_sha1": rom_sha1,
        "frames": frames, "movie_frames": total, "by_poll": movie.by_poll,
        "settings": {"offset": offset, "vi": vi, "raw": raw, "eeprom": eeprom, "dp": dp,
                     "core": "bizhawk" if bizhawk else "mupen64plus 2.6.0"},
        "polls": st["polls"], "timer_end": st["timer"] if timer is not None else None,
        "events": events, "lag": lag,
    }


def summary(rep, expected=None):
    """Lines about a report: stages, the overlays, how it ended."""
    ev = rep["events"]
    stages = [e for e in ev if e[1] == "stage"]
    out = [f"{rep['rom']}: {rep['frames']} VIs ({rep['movie']}, {rep['movie_frames']} "
           f"{'samples' if rep['by_poll'] else 'frames'}), {rep['polls']} controller reads"]
    out.append(f"  stage times: {[e[2] for e in stages]} (at VIs {[e[0] for e in stages]}); "
               f"the stage timer at the end: {rep.get('timer_end')}")
    if expected:
        got = [e[2] for e in stages]
        ok = got[:len(expected)] == expected
        out.append(f"  the movie's own first stage times {expected}: "
                   f"{'matched' if ok else 'NOT matched (desynced)'}")
    last = [e for e in ev if e[1] == "overlay"][-1:] or [[0, "overlay", None]]
    out.append(f"  last overlay {last[0][2]} from VI {last[0][0]}")
    return out


def compare(a, b, slack=0):
    """(first index where the checkpoints differ or None, message)."""
    ea, eb = a["events"], b["events"]
    for i, (x, y) in enumerate(zip(ea, eb)):
        if x[1:] != y[1:] or abs(x[0] - y[0]) > slack:
            return i, (f"checkpoint {i} differs: {x} vs {y} "
                       f"(the {i} before it match{'' if slack == 0 else f' within {slack} VIs'})")
    if len(ea) != len(eb):
        i = min(len(ea), len(eb))
        return i, f"one run has more checkpoints ({len(ea)} vs {len(eb)}); the first {i} match"
    return None, f"all {len(ea)} checkpoints match"


def parse_frames(text):
    out = set()
    for part in (text or "").split(","):
        if ":" in part:
            a, b, step = (int(x, 0) for x in part.split(":"))
            out.update(range(a, b + 1, step))
        elif part:
            out.add(int(part, 0))
    return out


def run_args(ap):
    ap.add_argument("--frames", type=int, help="VIs to run (default: the movie's length + 600)")
    ap.add_argument("--offset", type=int, default=2, help="VI n reads movie frame n - OFFSET")
    ap.add_argument("--vi", choices=("bizhawk", "core"), default="bizhawk",
                    help="frame length: BizHawk 2.8's (default) or the core's own")
    ap.add_argument("--no-raw", action="store_true",
                    help="the core's own controller instead of BizHawk's answers")
    ap.add_argument("--eeprom", default="00", help="byte a blank EEPROM is filled with, or 'core'")
    ap.add_argument("--dp", type=int, default=1, choices=(0, 1, 2),
                    help="RDP interrupt: 0 never, 1 for a display list with a full sync, 2 always")
    ap.add_argument("--bizhawk", help="directory with BizHawk 2.8's core (tools/bizhawk_core.sh)")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("run", help="play a movie on a ROM")
    r.add_argument("movie")
    r.add_argument("rom")
    r.add_argument("--json", help="write the report here")
    r.add_argument("--elf", help="the ROM's ELF, for the stage timer (default: next to the ROM)")
    r.add_argument("--settings-of", default=JP_MD5,
                   help="MD5 whose mupen64plus.ini entry the ROM gets (default: jp's)")
    r.add_argument("--dump", help="VIs to save RDRAM at (N,N,... or A:B:STEP)")
    r.add_argument("--dump-dir", default=str(ROOT / "build/tas/dumps"))
    run_args(r)
    c = sub.add_parser("check", help="play a movie on two ROMs and compare")
    c.add_argument("movie")
    c.add_argument("rom_a")
    c.add_argument("rom_b")
    c.add_argument("--slack", type=int, default=0, help="VIs a checkpoint may be off by")
    run_args(c)
    m = sub.add_parser("compare", help="compare two reports")
    m.add_argument("a")
    m.add_argument("b")
    m.add_argument("--slack", type=int, default=0)
    f = sub.add_parser("fetch", help="download the known movies")
    f.add_argument("movie", nargs="?")
    i = sub.add_parser("info", help="describe a movie")
    i.add_argument("movie")
    a = ap.parse_args()

    if a.cmd == "fetch":
        for k in [a.movie] if a.movie else MOVIES:
            print(f"{k}: {MOVIES[k]['title']}\n  {MOVIES[k]['page']}\n  {fetch(k)}")
        return
    if a.cmd == "info":
        print(Movie(resolve(a.movie)).describe())
        return
    if a.cmd == "compare":
        ra, rb = (json.loads(Path(x).read_text()) for x in (a.a, a.b))
        i, msg = compare(ra, rb, a.slack)
        print(msg)
        sys.exit(1 if i is not None else 0)
    expected = MOVIES.get(a.movie, {}).get("stage_times")
    if a.cmd == "check":
        resolve(a.movie)  # fetch once, before the two runs
        flags = [f"--offset={a.offset}", f"--vi={a.vi}", f"--eeprom={a.eeprom}", f"--dp={a.dp}"]
        flags += (["--frames", str(a.frames)] if a.frames else []) + (["--no-raw"] if a.no_raw else [])
        flags += ["--bizhawk", a.bizhawk] if a.bizhawk else []
        with tempfile.TemporaryDirectory() as tmp:
            def one(i_rom):
                i, rom = i_rom
                out = Path(tmp) / f"{i}.json"
                subprocess.run([sys.executable, __file__, "run", a.movie, rom, "--json", str(out)]
                               + flags, check=True, stdout=subprocess.DEVNULL)
                return json.loads(out.read_text())
            with ThreadPoolExecutor(2) as pool:  # each run is its own process
                ra, rb = pool.map(one, enumerate([a.rom_a, a.rom_b]))
        for rep in (ra, rb):
            print("\n".join(summary(rep, expected)))
        i, msg = compare(ra, rb, a.slack)
        print(msg)
        sys.exit(1 if i is not None else 0)

    movie = Movie(resolve(a.movie))
    rep = play(movie, a.rom, a.frames, a.offset, a.vi, not a.no_raw,
               None if a.eeprom == "core" else int(a.eeprom, 16), a.dp, a.elf, a.settings_of,
               a.bizhawk, parse_frames(a.dump), a.dump_dir,
               quiet=os.environ.get("EMU_VERBOSE") is None, log=sys.stdout)
    print("\n".join(summary(rep, expected)))
    if a.json:
        Path(a.json).write_text(json.dumps(rep, indent=1))


if __name__ == "__main__":
    main()
