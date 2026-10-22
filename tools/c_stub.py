#!/usr/bin/env python3
"""Start a C file for a text object: every function still GLOBAL_ASM.

  tools/c_stub.py <version> <object> [<object> ...]

<object> is the asm object's name as asm/ has it: `40300` (main_code),
`main_code_entry`, `overlays/ovl_09_01/120000`.  Writes src/<object>.c with
a `#pragma GLOBAL_ASM` line per function (asm-processor), in the order of
the object's asm/<object>.s, which must be extracted.  Then regenerate the
config (tools/layout.py <version>, which makes the object a `c`
subsegment because its file now exists) and re-extract, so that splat
writes the functions to asm/nonmatchings/ (docs/DECOMPILING.md).
"""
import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
GLABEL = re.compile(r"^glabel (\w+)")


def stub(obj):
    asm = ROOT / "asm" / f"{obj}.s"
    if not asm.exists():
        sys.exit(f"{asm.relative_to(ROOT)} is missing (not extracted, or already C)")
    funcs = [m.group(1) for line in asm.read_text().splitlines()
             if (m := GLABEL.match(line))]
    if not funcs:
        sys.exit(f"{asm.relative_to(ROOT)} has no functions")
    lines = ['#include "common.h"', ""]
    for f in funcs:
        lines.append(f'#pragma GLOBAL_ASM("asm/nonmatchings/{obj}/{f}.s")')
        lines.append("")
    return "\n".join(lines)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("version", choices=("us", "eu", "jp"))
    ap.add_argument("objects", nargs="+")
    args = ap.parse_args()
    have = (ROOT / ".version").read_text().strip() if (ROOT / ".version").exists() else None
    if have != args.version:
        sys.exit(f"asm/ holds {have or 'nothing'}, not {args.version}")
    for obj in args.objects:
        out = ROOT / "src" / f"{obj}.c"
        if out.exists():
            sys.exit(f"{out.relative_to(ROOT)} exists")
        text = stub(obj)
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(text)
        print(out.relative_to(ROOT))


if __name__ == "__main__":
    main()
