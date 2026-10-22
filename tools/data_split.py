#!/usr/bin/env python3
"""Check data_split.txt against the C objects as IDO built them.

  data_split.py <version>                    check every listed object
  data_split.py <version> --add MODULE OBJ   list OBJ (the next C object of
                                             MODULE) with its built sizes

data_split.txt lists, per module, the C objects whose .data, .rodata and
.bss tools/layout.py cuts out of the module's block, with their sizes
(docs/DECOMPILING.md, "Data").  The sizes are the compiler's: this reads
them from build/<version>/src/.../<object>.c.o (so run `make` first) and
fails if a listed size differs.  --add appends a line for a new object
with the sizes it has now; an object is listed once its C defines all of
its .data and .bss (its .rodata may still come partly from GLOBAL_ASM
functions, which splat gives their share once the object owns it: until
then the built size is only the C functions' part, so check the line
against the ROM).  Then regenerate the configs (tools/layout.py us, eu)
and extract again.
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import layout  # noqa: E402

SPLIT = ROOT / "data_split.txt"
SECTIONS = (".data", ".rodata", ".bss")


def object_path(version, module, obj):
    seg_dir = f"overlays/{module}/" if module.startswith("ovl_") else ""
    return ROOT / "build" / version / "src" / f"{seg_dir}{obj}.c.o"


def sizes(path):
    """(.data, .rodata, .bss) sizes of a built object."""
    out = subprocess.run(["mips-linux-gnu-objdump", "-h", str(path)],
                         capture_output=True, text=True, check=True).stdout
    have = {}
    for line in out.splitlines():
        f = line.split()
        if len(f) > 2 and f[1] in SECTIONS:
            have[f[1]] = int(f[2], 16)
    return tuple(have.get(s, 0) for s in SECTIONS)


def check(version):
    bad = 0
    n = 0
    for module, (objs, _) in layout.data_split(version).items():
        for obj, *listed in objs:
            path = object_path(version, module, obj)
            if not path.exists():
                print(f"{module} {obj}: {path.relative_to(ROOT)} not built")
                bad += 1
                continue
            built = sizes(path)
            n += 1
            if tuple(listed) != built:
                fmt = lambda t: " ".join(f"0x{x:X}" for x in t)
                print(f"{module} {obj}: data_split.txt has {fmt(listed)}, the object {fmt(built)}")
                bad += 1
    if bad:
        sys.exit(f"data_split.txt: {bad} of the listed objects differ")
    print(f"data_split.txt: {n} objects match their build ({version})")


def add(version, module, obj):
    path = object_path(version, module, obj)
    if not path.exists():
        sys.exit(f"{path.relative_to(ROOT)} not built")
    d, r, b = sizes(path)
    line = " ".join([module, obj] + [f"0x{x:X}" if x else "0" for x in (d, r, b)])
    lines = SPLIT.read_text().splitlines()
    mine = [k for k, l in enumerate(lines) if re.match(rf"{re.escape(module)}\s+[^@\s]", l)]
    if any(l.split()[:2] == [module, obj] for l in lines):
        sys.exit(f"{module} {obj} is listed already")
    if mine:
        lines.insert(mine[-1] + 1, line)
    else:
        lines += ["", line]
    SPLIT.write_text("\n".join(lines) + "\n")
    print(line)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("version", choices=layout.VERSIONS)
    ap.add_argument("--add", nargs=2, metavar=("MODULE", "OBJECT"))
    args = ap.parse_args()
    if args.add:
        add(args.version, *args.add)
    else:
        check(args.version)


if __name__ == "__main__":
    main()
