#!/usr/bin/env python3
"""Diff one function between the original and the rebuilt code image.

A lighter stand-in for asm-differ (tools/asm-differ/diff.py, configured by
diff_settings.py): looks the function up in the link map, disassembles the
same range out of both images and prints a unified diff.  Exits 0 when the
bytes are identical.  The original's range is where the function's name says it
was (up to the next name), so a function that came out longer or shorter
still diffs against itself.

    tools/fdiff.py func_80225B40 [--version us] [--make]

The original is assets/code.bin (the code image `make extract` writes), the
rebuilt one build/<version>/code.bin.  The version defaults to the one asm/
is extracted for.  Overlays share VRAM, so a function is looked up in the
section the map lists it under.
"""

import argparse
import difflib
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OBJDUMP = "mips-linux-gnu-objdump"

SECTION = re.compile(r"^\.(\S+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) load address 0x([0-9a-f]+)")
SYMBOL = re.compile(r"^\s+0x([0-9a-f]{8,16})\s+(\S+)$")
# func_80225B00, D_8029F5A0, func_ovl09_01_80043010: named by their address
ADDR_NAME = re.compile(r"^(?:func|D|jtbl)_(?:ovl[0-9A-F]{2}_\d{2}_)?([0-9A-F]{8})$")


def read_map(path: Path):
    """{name: (vram, (section vram, size, image offset), [(vram, name)] of
    the section)}."""
    symbols = {}
    section = None
    in_section = []
    lines = path.read_text().splitlines()
    for i, line in enumerate(lines):
        m = SECTION.match(line)
        if not m and i + 1 < len(lines) and re.match(r"^\.\S+$", line):
            m = SECTION.match(line + lines[i + 1])
        if m:
            section = (int(m.group(2), 16), int(m.group(3), 16), int(m.group(4), 16))
            in_section = []
            continue
        m = SYMBOL.match(line)
        if m and section and not m.group(2).startswith("."):
            vram = int(m.group(1), 16)
            in_section.append((vram, m.group(2)))
            symbols.setdefault(m.group(2), (vram, section, in_section))
    return symbols


def original_vram(name):
    """The address a func_/D_ name was given for (us's, in us)."""
    m = ADDR_NAME.match(name)
    return int(m.group(1), 16) if m else None


def extent(name, symbols, original):
    """(start, end) of a function in the image: where the rebuilt link put
    it, or (original) where the name says it was, up to the next name."""
    vram, (s_vram, s_size, s_rom), in_section = symbols[name]
    later = [(v, n) for v, n in in_section
             if v > vram and not n.endswith(".NON_MATCHING")]
    if original:
        here = original_vram(name)
        if here is None:
            return None
        nxt = [original_vram(n) for _, n in later]
        nxt = [v for v in nxt if v is not None and v > here]
        end = min([s_vram + s_size] + nxt[:1])
        return here - s_vram + s_rom, end - s_vram + s_rom
    end = min([s_vram + s_size] + [v for v, _ in later[:1]])
    return vram - s_vram + s_rom, end - s_vram + s_rom


def disasm(image: Path, start: int, end: int) -> list[str]:
    out = subprocess.run(
        [OBJDUMP, "-D", "-z", "-b", "binary", "-m", "mips:4300", "-EB",
         f"--start-address={start}", f"--stop-address={end}", str(image)],
        check=True, capture_output=True, text=True).stdout
    lines = []
    for line in out.splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)$", line)
        if m:
            # branch and jump targets relative to the function, so that a
            # function that moved still compares equal
            text = m.group(3)
            if re.match(r"b|j\s", text):
                text = re.sub(r"\b0x([0-9a-f]+)$",
                              lambda t: f"+{int(t.group(1), 16) - start:#x}", text)
            word = m.group(2)
            if word[0] in "01" and int(word, 16) >> 26 in (2, 3):
                word = word[:1] + "......."  # j/jal: the target's absolute
            lines.append(f"{int(m.group(1), 16) - start:5x}: {word}  {text}")
    return lines


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("function")
    extracted = ROOT / ".version"
    ap.add_argument("--version", default=extracted.read_text().strip()
                    if extracted.exists() else "us")
    ap.add_argument("--make", action="store_true",
                    help="rebuild first (the sha1 check may fail)")
    args = ap.parse_args()

    build = ROOT / "build" / args.version
    image = build / "code.bin"
    if args.make:
        subprocess.run(["make", "-s", f"VERSION={args.version}", str(image.relative_to(ROOT))],
                       cwd=ROOT, check=True)

    # A failed build leaves the previous image in place, which would diff
    # clean against code that no longer compiles.
    inputs = [*(ROOT / "src").rglob("*.c"), *(ROOT / "include").rglob("*.h")]
    if image.exists() and any(f.stat().st_mtime > image.stat().st_mtime for f in inputs):
        sys.exit(f"{image.relative_to(ROOT)} is older than its sources; the last build failed")

    symbols = read_map(build / f"bm64.{args.version}.map")
    if args.function not in symbols:
        sys.exit(f"{args.function} is not in the {args.version} map")
    mine_range = extent(args.function, symbols, False)
    base_range = extent(args.function, symbols, True) or mine_range

    base = disasm(ROOT / "assets" / "code.bin", *base_range)
    mine = disasm(image, *mine_range)
    if base == mine:
        print(f"{args.function}: OK ({mine_range[1] - mine_range[0]:#x} bytes)")
        return
    sys.stdout.writelines(l + "\n" for l in difflib.unified_diff(
        base, mine, "original", "rebuilt", lineterm="", n=3))
    sys.exit(1)


if __name__ == "__main__":
    main()
