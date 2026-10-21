#!/usr/bin/env python3
"""Run the shifted build against the original and compare the game state.

  shift_check.py <version> [--frames N,N,...] [--input SCRIPT]

Both ROMs (build/<v>/bm64.<v>.z64 and build/<v>-shift/bm64.<v>.z64) run
headless to each checkpoint frame (tools/emu_ram.py), with the same input
script (tools/inputs/menus.txt by default, which goes through the title,
the menus and into a stage).  Then every data object of boot_code,
main_code and the overlay that is loaded (and their bss) is compared, each
read at its own address in each build from the two ELFs.  A word that is the address of
something that moved is translated first: in the original it points at
`label + off`, so in the shifted build it has to point at that label's new
address + off.

The runs don't pace themselves against the host's clock (emu_ram.py turns
the speed limiter off), and with that they are exactly repeatable.  The
original is still run twice, and what differs between those two runs is
left out of the comparison (none so far).  Any other difference fails.
With the default pad (0x10) every checkpoint matches exactly, in us and
eu.  A bigger pad makes the overlays bigger, so the shifted ROM is a
little slower while it DMAs and inflates one, and a checkpoint during a
load catches it a few frames behind; it catches up afterwards.  --converge
accepts that: only the last two checkpoints have to match.  It is weaker:
a build with a code pointer left absolute (a thread's exit address) also
converges by frame 12000, and only the strict check catches it (at 600 and
1800).  This is a smoke test either way; the static check is
tools/find_abs.py.  A
shifted build that broke something (an address left absolute) shows up as
far more, usually as a crash.
"""
import argparse
import bisect
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


def module(section):
    """The code segment a section belongs to (`.main_code_bss` -> main_code)."""
    return section[1:].removesuffix("_bss")


class Map:
    """Original address -> shifted address, by label, for the modules in RAM."""

    def __init__(self, orig, shifted, modules):
        new = {n: a for a, _, n, _ in shifted}
        mine = [(a, sz, n) for a, sz, n, s in orig if module(s) in modules]
        # the asm's labels only: the linker's markers (X_DATA_START, ...)
        # share addresses with them but sit on the other side of a pad
        labels = sorted((a, n) for a, _, n in mine if n in new and not n.startswith(".")
                        and not MARKER.search(n))
        self.addrs = [a for a, _ in labels]
        self.labels = labels
        self.new = new
        self.ranges = []
        for m in modules:
            ins = [(a, a + sz) for a, sz, n, s in orig if module(s) == m]
            if ins:
                self.ranges.append((min(x for x, _ in ins), max(y for _, y in ins)))

    def __call__(self, v):
        if not any(lo <= v < hi for lo, hi in self.ranges):
            return v
        i = bisect.bisect_right(self.addrs, v) - 1
        a, n = self.labels[i]
        return self.new[n] + v - a


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


def text_ranges(syms, modules):
    """[(start, end)] of the modules' text, from <seg>_TEXT_START/END (the
    overlays share addresses, so only the ones in RAM)."""
    starts = {n[:-len("_TEXT_START")]: a for a, _, n, _ in syms if n.endswith("_TEXT_START")}
    ends = {n[:-len("_TEXT_END")]: a for a, _, n, _ in syms if n.endswith("_TEXT_END")}
    return [(starts[k], ends[k]) for k in starts if k in ends and k in modules]


def run(rom, frames, m64p, script):
    """RDRAM after `frames` frames (each run in its own process: the core
    can only start once)."""
    with tempfile.NamedTemporaryFile() as f:
        cmd = [sys.executable, str(Path(__file__).parent / "emu_ram.py"), str(rom),
               "--frames", str(frames), "--out", f.name]
        if m64p:
            cmd += ["--m64p", m64p]
        if script:
            cmd += ["--input", str(script)]
        subprocess.run(cmd, check=True)
        return Path(f.name).read_bytes()


def word(ram, addr):
    o = addr - PHYS
    return int.from_bytes(ram[o:o + 4], "big")


def compare(ram_a, ram_b, objects_a, where_b, translate):
    """(differing words, [(name, count)], {name: [(off, a, b)]})"""
    total, by, detail = 0, [], {}
    for addr, size, name in objects_a:
        b = where_b.get(name)
        if b is None or size == 0:
            continue
        n = 0
        for off in range(0, size - 3, 4):
            va, vb = word(ram_a, addr + off), word(ram_b, b + off)
            if translate(va) != vb:
                n += 1
                detail.setdefault(name, []).append((off, va, vb))
        if n:
            by.append((name, n))
            total += n
    by.sort(key=lambda x: -x[1])
    return total, by, detail


def check(v, frames, m64p, script, orig, shifted, orig_dir, shift_dir):
    """Compare at one checkpoint; returns the objects beyond the noise."""
    roms = [orig_dir / f"bm64.{v}.z64"] * 2 + [shift_dir / f"bm64.{v}.z64"]
    with ThreadPoolExecutor(3) as pool:  # each run is its own process
        ram_o1, ram_o2, ram_s = pool.map(lambda r: run(r, frames, m64p, script), roms)

    # what is in RAM: boot_code, main_code, and the overlay that's loaded
    ovl = loaded_overlay(ram_o1, orig_dir / "code.bin", ROOT / f"bm64.{v}.yaml")
    modules = {"boot_code", "main_code", "zerojump"} | ({ovl} if ovl else set())
    translate = Map(orig, shifted, modules)
    # data objects only: a label in text (handwritten code) holds
    # instructions, which encode addresses in ways this can't translate
    text = text_ranges(orig, modules)
    objects = [(ad, sz, n) for ad, sz, n, s in orig
               if module(s) in modules - {"zerojump"} and not n.startswith("func_") and sz
               and not n.endswith(".NON_MATCHING")
               and not any(t0 <= ad < t1 for t0, t1 in text)]
    where_shifted = {n: ad for ad, _, n, _ in shifted}
    where_orig = {n: ad for ad, _, n, _ in orig}

    words = sum(sz // 4 for _, sz, _ in objects)
    noise, by_noise, _ = compare(ram_o1, ram_o2, objects, where_orig, lambda x: x)
    diff, by_diff, detail = compare(ram_o1, ram_s, objects, where_shifted, translate)
    noisy = {n for n, _ in by_noise}
    print(f"frame {frames} ({ovl or 'no overlay'} loaded): {len(objects)} objects, "
          f"{words} words; {noise} differ between two original runs, "
          f"{diff} between original and shifted")
    extra = [(n, c) for n, c in by_diff if n not in noisy]
    for n, c in extra[:25]:
        print(f"  {n}: {c} words (not in the noise)")
        for off, va, vb in detail[n][:4]:
            print(f"    +0x{off:X}: 0x{va:08X} (-> 0x{translate(va):08X}) vs 0x{vb:08X}")
    return sum(c for _, c in extra)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("version")
    ap.add_argument("--frames", default="600,1800,3600,6000,12000,24000",
                    help="checkpoints, comma-separated")
    ap.add_argument("--input", default=str(ROOT / "tools/inputs/menus.txt"),
                    help="input script ('' for none)")
    ap.add_argument("--m64p", default=os.environ.get("M64P_DIR"))
    ap.add_argument("--converge", action="store_true",
                    help="only the last two checkpoints have to match (bigger pads)")
    a = ap.parse_args()
    v = a.version
    orig_dir, shift_dir = ROOT / f"build/{v}", ROOT / f"build/{v}-shift"
    orig, shifted = symbols(orig_dir / f"bm64.{v}.elf"), symbols(shift_dir / f"bm64.{v}.elf")
    frames = [int(x) for x in a.frames.split(",")]
    failed = []
    for f in frames:
        if check(v, f, a.m64p, a.input or None, orig, shifted, orig_dir, shift_dir):
            failed.append(f)
    if a.converge:
        late = [f for f in failed if f in frames[-2:]]
        if failed and not late:
            print(f"behind at frame(s) {', '.join(map(str, failed))}, caught up by the end")
        failed = late
    if failed:
        sys.exit(f"the shifted build differs from the original at frame(s) "
                 f"{', '.join(map(str, failed))}")
    print("the shifted build matches the original's state at every checkpoint")


if __name__ == "__main__":
    main()
