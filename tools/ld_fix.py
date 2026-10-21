#!/usr/bin/env python3
"""Turn splat's linker script into the build's.

  ld_fix.py <version> IN OUT [--shift PAD]

splat lays every segment out one after another.  This game has fixed ROM
positions (the segment size table at 0x30000, the file table at 0x30800,
main_code at 0x40000 = ROM segment 2, the overlays from 0x120000 in the
code image), with zero padding between them.  So:

- a pad segment (`pad_*`) links nothing: the ROM position jumps to the next
  segment's fixed start, with an ASSERT that what came before still fits
  (objcopy fills the gap with zeros, as the pad was);
- main_code's part that the boot thread loads once (`main_code_persist`)
  starts 2 KiB-aligned, at `main_code_PERSIST_START` (tools/rom.py writes
  the segment size table from it).

With --shift PAD (the SHIFT=1 build) every movable module gets PAD bytes of
zeros after its entry object's .text and at the start of its data: the
entries (0x80000400, 0x80225800, 0x80043000) stay where the loaders jump,
everything after them moves.  zerojump, a fixed page, doesn't.
"""
import argparse
import re
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent


def fixed_starts(version):
    """{pad segment: the ROM start of the segment after it}"""
    cfg = yaml.safe_load((ROOT / f"bm64.{version}.yaml").read_text())
    segs = cfg["segments"]
    out = {}
    for s, nxt in zip(segs, segs[1:]):
        name = s["name"] if isinstance(s, dict) else (s[2] if len(s) > 2 else None)
        if name and name.startswith("pad_"):
            out[name] = nxt["start"] if isinstance(nxt, dict) else nxt[0]
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("version")
    ap.add_argument("input")
    ap.add_argument("output")
    ap.add_argument("--shift", type=lambda x: int(x, 0), default=0)
    a = ap.parse_args()
    pads = fixed_starts(a.version)
    out = []
    section = None          # the output section we're in
    text_padded = set()
    for line in Path(a.input).read_text().splitlines():
        m = re.match(r"\s*\.(\w+)\s.*:\s*AT\(", line)
        if m:
            section = m.group(1)
        m = re.match(r"\s*__romPos \+= SIZEOF\(\.(pad_\w+)\);", line)
        if m and m.group(1) in pads:
            nxt = pads[m.group(1)]
            out.append(f"    ASSERT(__romPos <= 0x{nxt:X}, \"{m.group(1)}: what precedes "
                       f"it overflows 0x{nxt:X}\")")
            out.append(f"    __romPos = 0x{nxt:X};")
            continue
        if section in pads and re.search(r"\.bin\.o\(", line):
            continue  # the pad itself: zeros the gap provides
        if "main_code_persist" in line and ".o(.rodata)" in line:
            out.append("        . = ALIGN(., 0x800);")
            out.append("        main_code_PERSIST_START = .;")
        out.append(line)
        movable = section and section != "zerojump" and section in modules
        if a.shift and movable:
            if section not in text_padded and re.search(r"\.[sc]\.o\(\.text\);", line):
                text_padded.add(section)
                out.append(f"        . += 0x{a.shift:X}; /* SHIFT */")
            elif re.match(rf"\s*{section}_DATA_START = \.;", line):
                out.append(f"        . += 0x{a.shift:X}; /* SHIFT */")
    Path(a.output).write_text("\n".join(out) + "\n")


def code_modules(version):
    cfg = yaml.safe_load((ROOT / f"bm64.{version}.yaml").read_text())
    return {s["name"] for s in cfg["segments"] if isinstance(s, dict) and s.get("type") == "code"}


if __name__ == "__main__":
    modules = code_modules(sys.argv[1]) if len(sys.argv) > 1 else set()
    main()
