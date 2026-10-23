#!/usr/bin/env python3
"""Check data_split.txt against the C objects as IDO built them.

  data_split.py <version>                    check every listed object
  data_split.py <version> --add MODULE OBJ   list OBJ (the next C object of
                                             MODULE) with its built sizes;
                                             if it is listed, add this
                                             version's sizes where they differ

data_split.txt lists, per module, the C objects whose .data, .rodata and
.bss tools/layout.py cuts out of the module's block, with their sizes
(docs/DECOMPILING.md, "Data").  The sizes are the compiler's: this reads
them from build/<version>/src/.../<object>.c.o (so run `make` first) and
fails if a listed size differs; a version whose C builds to other sizes
(jp's text) has its own on a `MODULE @<version> OBJ sizes=...` line, which
is what that version is checked against.  --add appends a line for a new object
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
    if (ROOT / "src" / f"{seg_dir}{obj}.s").exists():
        # libultra's handwritten asm, a hasm subsegment (tools/layout.py)
        return ROOT / "build" / version / "asm" / f"{seg_dir}{obj}.s.o"
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
    for module, (objs, _, islands) in layout.data_split(version).items():
        for obj, *listed in objs + [(o, *v[:3]) for o, v in islands.items()]:
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
    have = [k for k, l in enumerate(lines) if l.split()[:2] == [module, obj]]
    if have:
        # listed (from another version's build): this version's own sizes
        # where its C builds to others
        listed = tuple(int(x, 16) for x in lines[have[0]].split()[2:5])
        if listed == (d, r, b) or any(l.split()[:3] == [module, f"@{version}", obj]
                                      and "sizes=" in l for l in lines):
            sys.exit(f"{module} {obj} is listed already")
        line = f"{module} @{version} {obj} sizes=" + ",".join(f"0x{x:X}" if x else "0" for x in (d, r, b))
        at = max(k for k, l in enumerate(lines) if l.split()[:1] == [module]
                 and obj in l.split()[1:3])
        lines.insert(at + 1, line)
        SPLIT.write_text("\n".join(lines) + "\n")
        print(line)
        return
    if mine:
        lines.insert(mine[-1] + 1, line)
    else:
        lines += ["", line]
    SPLIT.write_text("\n".join(lines) + "\n")
    print(line)


def text_vram(version, module, obj):
    """Where a named text subsegment starts: a library object's from
    lib_objects.<version>.txt, anything else's from bm64.<version>.yaml."""
    for vram, name in layout.lib_objects(version).get(module, {}).items():
        if name and f"libultra/{name}" == obj:
            return vram
    import yaml
    cfg = yaml.safe_load((ROOT / f"bm64.{version}.yaml").read_text())
    seg = next(s for s in cfg["segments"] if isinstance(s, dict) and s.get("name") == module)
    for sub in seg["subsegments"]:
        if not isinstance(sub, list) or len(sub) < 2 or sub[1] not in ("c", "hasm", "asm"):
            continue
        # a named subsegment, or one named by its image offset (`995C0`)
        if (str(sub[2]) if len(sub) > 2 else f"{sub[0]:X}") == obj:
            return sub[0] - seg["start"] + seg["vram"]
    sys.exit(f"{module} has no text object {obj} in bm64.{version}.yaml")


def section_bases(version, path, vram):
    """{section: VRAM} for an object whose .text is at `vram` in this
    version's code image, found from its .text's %hi/%lo relocations: each
    pair gives an address in the image, which is the section's base plus
    what the object adds.  Every pair must agree, and the .data and .rodata
    bytes must be the image's there (relocated words aside)."""
    import struct
    import libmatch
    image = libmatch.code_image(version)
    o = libmatch.Obj(path)
    off = layout_offset(version, vram)
    word = lambda a: struct.unpack_from(">I", image, a)[0]
    base = {}
    hi = None
    for r, typ, symidx in sorted(o.relocs):
        if typ == libmatch.R_MIPS_HI16:
            hi = (r, symidx)
            continue
        if typ != libmatch.R_MIPS_LO16 or hi is None or hi[1] != symidx:
            continue
        s = o.syms[symidx]
        if s["shndx"] >= len(o.secs) or s["shndx"] == 0:
            continue  # an undefined symbol
        sect = o.secs[s["shndx"]]["name"]
        if sect == ".text":
            continue
        mine_hi, = struct.unpack_from(">I", o.text, hi[0])
        mine_lo, = struct.unpack_from(">I", o.text, r)
        ahl = ((mine_hi & 0xFFFF) << 16) + libmatch.sext16(mine_lo & 0xFFFF)
        got = ((word(off + hi[0]) & 0xFFFF) << 16) + libmatch.sext16(word(off + r) & 0xFFFF)
        b = (got - ahl - s["value"]) & 0xFFFFFFFF
        assert base.setdefault(sect, b) == b, f"{path.name}: {sect} at 0x{base[sect]:08X} and 0x{b:08X}"
    data = path.read_bytes()
    for sect, b in base.items():
        if sect == ".bss":
            continue
        s = next(x for x in o.secs if x["name"] == sect)
        mine = data[s["off"]:s["off"] + s["size"]]
        relocated = set()
        idx = o.secs.index(s)
        for x in o.secs:
            if x["type"] == 9 and x["info"] == idx:
                for j in range(x["size"] // 8):
                    relocated.add(struct.unpack_from(">I", data, x["off"] + j * 8)[0] & ~3)
        at = layout_offset(version, b)
        for k in range(0, len(mine) - len(mine) % 4, 4):
            if k not in relocated and mine[k:k + 4] != image[at + k:at + k + 4]:
                sys.exit(f"{path.name}: its {sect} differs from the image at 0x{b + k:08X}")
    return base


def layout_offset(version, vram):
    """The code image offset of a boot_code or main_code VRAM (the library
    is in those two)."""
    import libmatch
    segs = {name: (start, v) for name, start, _, v in libmatch.code_segments(version)}
    start, v = segs["main_code" if vram >= layout.MAIN_VRAM else "boot_code"]
    return start + vram - v


def place(version, module, obj, ref):
    """Print the data_split.txt lines that place a library object's
    sections (its sizes, then this version's addresses)."""
    path = Path(ref) if ref else object_path(version, module, obj)
    if not path.exists():
        sys.exit(f"{path} not built")
    d, r, b = sizes(path)
    base = section_bases(version, path, text_vram(version, module, obj))
    where = [f"{k}=0x{base['.' + k]:08X}" for k, n in (("data", d), ("rodata", r), ("bss", b)) if n]
    missing = [k for k, n in (("data", d), ("rodata", r), ("bss", b)) if n and "." + k not in base]
    if missing:
        sys.exit(f"{obj}: no reference shows where its {', '.join(missing)} is")
    print(" ".join([module, obj] + [f"0x{x:X}" if x else "0" for x in (d, r, b)]))
    print(" ".join([module, f"@{version}", obj] + where))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("version", choices=layout.VERSIONS)
    ap.add_argument("--add", nargs=2, metavar=("MODULE", "OBJECT"))
    ap.add_argument("--place", nargs=2, metavar=("MODULE", "OBJECT"),
                    help="where a library object's data is in this version's image")
    ap.add_argument("--ref", help="with --place: the object to read (default: its build)")
    args = ap.parse_args()
    if args.add:
        add(args.version, *args.add)
    elif args.place:
        place(args.version, *args.place, args.ref)
    else:
        check(args.version)


if __name__ == "__main__":
    main()
