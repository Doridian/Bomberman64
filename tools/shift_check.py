#!/usr/bin/env python3
"""Run the shifted build against the original and compare the game state.

  shift_check.py <version> [--frames N,N,...] [--input SCRIPT]

Both ROMs (build/<v>/bm64.<v>.z64 and build/<v>-shift/bm64.<v>.z64) run
headless (tools/emu_ram.py) with the same input script
(tools/inputs/menus.txt by default: title, menus, the opening, a stage),
and their RDRAM is read at each checkpoint frame.  Then the data of
boot_code, main_code and the overlay that is loaded (everything from the
end of its text to the end of its section: rodata, data, main_code's
persistent part) is compared word by word: each word is read at its own
address in each build (found through the label it belongs to, from the two
ELFs).  A word that is the address of something that moved is translated
first: in the original it points at `label + off`, so in the shifted build
it has to point at that label's new address + off.

The game seeds its random number generator (main_code's init, at every
reload of main_code) with osGetTime(), the CPU's cycle counter.  The
counter at that point depends on how long everything before it took,
DMAs included, and the shifted build is bigger: its main_code takes one
more 2 KiB unit of the segment size table (0x80000 bytes instead of
0x7F800, reloaded at every scene change) and every overlay is longer.  So
the seed differs, and with it everything random (where a stage places
things, how long that takes, and from then on the frame counters).  That
is the emulated timing, not a fault of the build: both ROMs are run with
the seed pinned to the same constant (seed_patch() finds the one call,
`func(osGetTime())`, in the linked code and changes its argument).

bss isn't compared.  The same timing decides where within a frame each
thread is when the frame ends, so bss holds what that changes: the
scheduler's and osGetTime's clock values, saved thread contexts and
stacks, message queues, which audio buffer is current, the heap's
bookkeeping, and the DMA requests that carry the segment sizes.  An
overlay's bss isn't cleared by the loader and holds what the previous
overlay left there.  The game's state that matters to the next frame ends
up in the data (the frame counters that showed the seed, for one).

The runs don't pace themselves against the host's clock (emu_ram.py turns
the speed limiter off) and start from a blank save, and with that they are
exactly repeatable.  The original is still run twice, and what differs
between those two runs is left out of the comparison (none so far).  Any
other difference fails.  With the default pad (0x10) every checkpoint
matches exactly, in us, eu and jp.  A bigger pad makes the overlays bigger, so
the shifted ROM takes a little longer to DMA and inflate one; with 0x100
some load ends a frame later, and from then on the game's frame counters
are off (us: by one at frame 300, by 15 at 24000), and what follows them
(which frame buffer is current).  That is timing too, so the check is
meant for the default pad.

This is a smoke test; the static check is tools/find_abs.py.  A code
pointer left absolute that the game uses (a process's entry, in main_code's
init) fails every checkpoint.  One whose old address lands in the padding
before its function runs the same, and only find_abs.py sees it.
"""
import argparse
import bisect
import hashlib
import os
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
PHYS = 0x80000000
MARKER = re.compile(r"_(TEXT|DATA|RODATA|BSS)_(START|END|SIZE)$|_ROM_(START|END)$|_VRAM(_END)?$|_PERSIST_START$")
SEED = 0x1997


def symbols(elf):
    """[(address, size, name, section)] of the ELF's section symbols."""
    out = []
    objdump = subprocess.run(["mips-linux-gnu-objdump", "-tw", elf], capture_output=True,
                             check=True, text=True).stdout
    for line in objdump.splitlines():
        p = line.split()
        if len(p) >= 5 and len(p[0]) == 8 and p[-3].startswith("."):
            out.append((int(p[0], 16), int(p[-2], 16), p[-1], p[-3]))
    return out


def sections(elf):
    """{name: (vma, lma, size)}"""
    out = {}
    objdump = subprocess.run(["mips-linux-gnu-objdump", "-hw", elf], capture_output=True,
                             check=True, text=True).stdout
    for line in objdump.splitlines():
        p = line.split()
        if len(p) >= 6 and p[0].isdigit() and p[1].startswith("."):
            out[p[1][1:]] = (int(p[3], 16), int(p[4], 16), int(p[2], 16))
    return out


def module(section):
    """The code segment a section belongs to (`.main_code_bss` -> main_code)."""
    return section[1:].removesuffix("_bss")


def seed_patch(elf, rom):
    """(ROM offset, bytes) that pin the random seed: main_code's init calls
    the generator's init (Knuth's subtractive generator, MBIG = 1e9) as
    `jal init; or $a0, $v1, $zero` right after `jal osGetTime` (a ZeroJump
    stub, id 0x120): the low word of the cycle counter.  The delay slot
    becomes `addiu $a0, $zero, SEED`."""
    syms = symbols(elf)
    vma, lma, size = sections(elf)["main_code"]
    code = Path(rom).read_bytes()[lma:lma + size]

    def word(va):
        o = va - vma
        return int.from_bytes(code[o:o + 4], "big")

    at = {n: a for a, _, n, _ in syms}
    text = range(at["main_code_TEXT_START"], at["main_code_TEXT_END"], 4)
    hits = [va for va in text if word(va) == 0x3C083B9A  # lui $t0, 0x3B9A
            and any(word(va + 4 * i) == 0x3508CA00 for i in range(1, 8))]  # ori $t0, 0xCA00
    if len(hits) != 1:
        sys.exit(f"{elf}: {len(hits)} candidates for the generator's init, expected 1")
    funcs = sorted(a for a, _, n, s in syms if s == ".main_code" and not MARKER.search(n)
                   and not n.startswith(("D_", "jtbl_", ".")) and not n.endswith(".NON_MATCHING"))
    init = funcs[bisect.bisect_right(funcs, hits[0]) - 1]
    jal = 0x0C000000 | (init >> 2 & 0x3FFFFFF)
    calls = [va for va in text if word(va) == jal and word(va + 4) == 0x00602025]
    if len(calls) != 1:
        sys.exit(f"{elf}: {len(calls)} calls of 0x{init:08X} with the seed in $v1, expected 1")
    call = calls[0]
    before = word(call - 8)
    stub = (call & 0xF0000000) | (before & 0x3FFFFFF) << 2
    if before >> 26 != 3 or (word(stub), word(stub + 4)) != (0x00000008, 0x24080120):
        sys.exit(f"{elf}: the seed at 0x{call:08X} doesn't come from osGetTime (ZeroJump 0x120)")
    return lma + call + 4 - vma, (0x24040000 | SEED).to_bytes(4, "big")


class Map:
    """Original address -> shifted address, by label, for the modules in RAM."""

    def __init__(self, orig, shifted, modules):
        new = {n: a for a, _, n, _ in shifted}
        mine = [(a, sz, n) for a, sz, n, s in orig if module(s) in modules]
        # the asm's labels only: the linker's markers (X_DATA_START, ...)
        # share addresses with them but sit on the other side of a pad
        labels = sorted((a, n) for a, _, n in mine if n in new and not n.startswith(".")
                        and not n.endswith(".NON_MATCHING") and not MARKER.search(n))
        self.addrs = [a for a, _ in labels]
        self.labels = labels
        self.new = new
        self.ranges = []
        for m in modules:
            ins = [(a, a + sz) for a, sz, n, s in orig if module(s) == m]
            if ins:
                self.ranges.append((min(x for x, _ in ins), max(y for _, y in ins)))

    def label(self, v):
        """(label, offset) that v is in."""
        a, n = self.labels[bisect.bisect_right(self.addrs, v) - 1]
        return n, v - a

    def __call__(self, v):
        if not any(lo <= v < hi for lo, hi in self.ranges):
            return v
        n, off = self.label(v)
        return self.new[n] + off


def loaded_overlay(ram, image_path, config):
    """The overlay whose bytes are at 0x80043000 in RAM, or None."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import layout
    image = Path(image_path).read_bytes()
    here = ram[0x43000:0x63000]
    best, score = None, 0
    for (bank, entry), (start, end) in layout.overlay_offsets(config).items():
        code = image[start:end]
        same = sum(1 for o in range(0, len(code), 4) if here[o:o + 4] == code[o:o + 4])
        if same * 2 > len(code) // 4 and same > score:
            best, score = layout.overlay_name(bank, entry), same
    return best


def data_ranges(syms, secs, modules):
    """[(start, end)] of the modules' data: from <seg>_TEXT_END to the end
    of the section (the overlays share addresses, so only the ones in
    RAM)."""
    ends = {n[:-len("_TEXT_END")]: a for a, _, n, _ in syms if n.endswith("_TEXT_END")}
    out = []
    for m in sorted(modules):
        if m in ends and m in secs:
            vma, _, size = secs[m]
            out.append((ends[m], vma + size))
    return out


def run(rom, frames, m64p, script, patches, settings_md5):
    """{frame: RDRAM} (each run in its own process: the core can only
    start once)."""
    fd, out = tempfile.mkstemp(suffix=".bin")
    os.close(fd)
    out = Path(out)
    cmd = [sys.executable, str(Path(__file__).parent / "emu_ram.py"), str(rom),
           "--frames", ",".join(map(str, frames)), "--out", str(out),
           "--settings-of", settings_md5]
    if m64p:
        cmd += ["--m64p", m64p]
    if script:
        cmd += ["--input", str(script)]
    for off, data in patches:
        cmd += ["--patch", f"0x{off:X}={data.hex()}"]
    try:
        subprocess.run(cmd, check=True)
        data = out.read_bytes()
    finally:
        out.unlink(missing_ok=True)
    size = len(data) // len(frames)
    return {f: data[i * size:(i + 1) * size] for i, f in enumerate(frames)}


def word(ram, addr):
    o = addr - PHYS
    return int.from_bytes(ram[o:o + 4], "big")


def compare(ram_a, ram_b, ranges, where_b, translate):
    """{(label, offset): (a, b)} of the words that differ"""
    out = {}
    for lo, hi in ranges:
        for addr in range(lo, hi, 4):
            va, vb = word(ram_a, addr), word(ram_b, where_b(addr))
            if translate(va) != vb:
                out[addr] = (va, vb)
    return out


def check(v, frame, rams, orig, shifted, secs, orig_dir):
    """Compare at one checkpoint; returns the number of words beyond the noise."""
    ram_o1, ram_o2, ram_s = (r[frame] for r in rams)
    # what is in RAM: boot_code, main_code, and the overlay that's loaded
    ovl = loaded_overlay(ram_o1, orig_dir / "code.bin", ROOT / f"bm64.{v}.yaml")
    modules = {"boot_code", "main_code"} | ({ovl} if ovl else set())
    translate = Map(orig, shifted, modules)
    ranges = data_ranges(orig, secs, modules)
    words = sum((hi - lo) // 4 for lo, hi in ranges)
    noise = compare(ram_o1, ram_o2, ranges, lambda a: a, lambda x: x)
    diff = compare(ram_o1, ram_s, ranges, translate, translate)
    extra = {a: d for a, d in diff.items() if a not in noise}
    print(f"frame {frame} ({ovl or 'no overlay'} loaded): {words} words of data; "
          f"{len(noise)} differ between two original runs, {len(diff)} between original "
          f"and shifted")
    by = {}
    for a, (va, vb) in sorted(extra.items()):
        n, off = translate.label(a)
        by.setdefault(n, []).append((off, va, vb))
    for n, ds in sorted(by.items(), key=lambda x: -len(x[1]))[:25]:
        print(f"  {n}: {len(ds)} words (not in the noise)")
        for off, va, vb in ds[:4]:
            print(f"    +0x{off:X}: 0x{va:08X} (-> 0x{translate(va):08X}) vs 0x{vb:08X}")
    return len(extra)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("version")
    ap.add_argument("--frames", default="300,900,1800,3600,6000,10300,12000,18000,24000",
                    help="checkpoints, comma-separated")
    ap.add_argument("--input", default=str(ROOT / "tools/inputs/menus.txt"),
                    help="input script ('' for none)")
    ap.add_argument("--m64p", default=os.environ.get("M64P_DIR"))
    a = ap.parse_args()
    v = a.version
    orig_dir, shift_dir = ROOT / f"build/{v}", ROOT / f"build/{v}-shift"
    orig_elf, shift_elf = orig_dir / f"bm64.{v}.elf", shift_dir / f"bm64.{v}.elf"
    orig_rom, shift_rom = orig_dir / f"bm64.{v}.z64", shift_dir / f"bm64.{v}.z64"
    orig, shifted = symbols(orig_elf), symbols(shift_elf)
    secs = sections(orig_elf)
    frames = sorted({int(x) for x in a.frames.split(",")})
    # every run gets the original's mupen64plus.ini settings
    md5 = hashlib.md5(orig_rom.read_bytes()).hexdigest()
    jobs = [(orig_rom, [seed_patch(orig_elf, orig_rom)])] * 2 + \
           [(shift_rom, [seed_patch(shift_elf, shift_rom)])]
    with ThreadPoolExecutor(3) as pool:  # each run is its own process
        rams = list(pool.map(lambda j: run(j[0], frames, a.m64p, a.input or None, j[1], md5), jobs))
    failed = [f for f in frames if check(v, f, rams, orig, shifted, secs, orig_dir)]
    if failed:
        sys.exit(f"the shifted build differs from the original at frame(s) "
                 f"{', '.join(map(str, failed))}")
    print("the shifted build matches the original's state at every checkpoint")


if __name__ == "__main__":
    main()
