#!/usr/bin/env python3
"""Write C definitions for a run of a module's data or bss, from the asm.

  data_c.py <module> <start> <end> [--c src/<object>.c]

<start> and <end> are VRAMs (hex) in <module>'s asm data block or its bss
(main_code, ovl_09_01, ...), as extracted: the run an object's C is to
define once it owns its data (docs/DECOMPILING.md, "Data").  Prints one
definition per label, in address order, for pasting into the C file:

- bss: `u8 D_X[n];` or, where the C file (--c) declares the name, its
  declared type.  IDO lays .bss out in the order it first sees each
  variable and aligns each by its size (8 from 8 bytes up, else 4, 2, 1),
  so the definitions go before the first function, and a gap the
  alignment wouldn't leave gets a `u8` array named by its address.
- data: a string as `char D_X[] = "..."`, words as `u32`/`void *` (one
  word: a scalar), anything else as `u8` bytes.  Words splat made symbols
  are written as those symbols.  IDO aligns .data variables to at least 4
  and keeps them in definition order.

Types are only a start: replace them with what the code shows (the sha1
decides).  Trailing zeros may be the section's padding to 16.  Reads
assets/code.bin and asm/ for the version in .version (names are us's in
both versions).
"""
import argparse
import re
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent

LINE = re.compile(r"^\s*/\* (?:([0-9A-F]+) )?([0-9A-F]{8})(?: [0-9A-F]+)? \*/\s+(\.\w+)\s*(.*)$")
DLABEL = re.compile(r"^dlabel (\w+)")


def module_info(version, module):
    cfg = yaml.safe_load((ROOT / f"bm64.{version}.yaml").read_text())
    segs = cfg["segments"]
    for s, nxt in zip(segs, segs[1:]):
        if isinstance(s, dict) and s.get("name") == module:
            end = nxt["start"] if isinstance(nxt, dict) else nxt[0]
            return s, end
    sys.exit(f"no module {module} in bm64.{version}.yaml")


def asm_files(module):
    base = ROOT / "asm" / "data"
    if module.startswith("ovl_"):
        return sorted((base / "overlays" / module).glob("*.s"))
    # the fixed modules' blocks are named by their image offsets (or names)
    return sorted(p for p in base.glob("*.s"))


def labels(files, lo, hi):
    """{vram: name} of the labels in [lo, hi), and {vram: symbol} of the
    words splat wrote as symbols."""
    names, syms = {}, {}
    for path in files:
        pending = None
        for line in path.read_text().splitlines():
            m = DLABEL.match(line)
            if m:
                pending = m.group(1)
                continue
            m = LINE.match(line)
            if not m:
                continue
            vram = int(m.group(2), 16)
            if pending:
                if lo <= vram < hi:
                    names[vram] = pending
                pending = None
            if m.group(3) == ".word" and lo <= vram < hi:
                arg = m.group(4).strip()
                if not re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", arg):
                    syms[vram] = arg
    return names, syms


def declared(c_path):
    """{name: (type, dims)} of the C file's extern declarations."""
    out = {}
    if not c_path:
        return out
    for m in re.finditer(r"^extern\s+([^;()]*?)\s*\b(\w+)\s*((?:\[[^\]]*\])*)\s*;",
                         Path(c_path).read_text(), re.M):
        t = m.group(1).strip()
        stars = ""
        while t.endswith("*"):
            stars += "*"
            t = t[:-1].strip()
        out[m.group(2)] = (t + " " + stars).strip(), m.group(3)
    return out


def ido_align(size):
    for a in (8, 4, 2):
        if size >= a:
            return a
    return 1


def c_string(raw):
    esc = {0x0A: "\\n", 0x22: '\\"', 0x5C: "\\\\", 0x09: "\\t"}
    s = ""
    for c in raw:
        if c in esc:
            s += esc[c]
        elif 0x20 <= c < 0x7F:
            s += chr(c)
        else:
            s += f"\\{c:03o}"
    return f'"{s}"'


def bss_defs(names, lo, hi, decl):
    out = []
    pos = lo
    addrs = sorted(names) + [hi]
    for a, b in zip(addrs, addrs[1:]):
        name, size = names[a], b - a
        want = (pos + ido_align(size) - 1) & ~(ido_align(size) - 1)
        if a > want:
            out.append(f"u8 D_{pos:08X}[0x{a - pos:X}]; /* not referenced */")
        if name in decl:
            t, dims = decl[name]
            if dims != "[]":
                out.append(f"{t} {name}{dims};")
            elif t in ("u8", "s8", "char"):
                out.append(f"{t} {name}[0x{size:X}];")
            else:
                out.append(f"{t} {name}[]; /* give it a size: 0x{size:X} bytes */")
        else:
            out.append(f"u8 {name}[0x{size:X}];")
        pos = b
    return out


def data_defs(names, syms, img, rom_of, lo, hi):
    out = []
    addrs = sorted(names) + [hi]
    if lo not in names:
        addrs = [lo] + addrs
        names = dict(names, **{lo: f"D_{lo:08X}"})
    for a, b in zip(addrs, addrs[1:]):
        name = names[a]
        raw = img[rom_of(a):rom_of(b)]
        text = raw.rstrip(b"\0")
        if text and len(text) < len(raw) and all(0x20 <= c < 0x7F or c in (9, 10) for c in text):
            out.append(f"char {name}[] = {c_string(text)};"
                       + (f" /* then 0x{len(raw) - len(text) - 1:X} zero bytes */" if len(raw) - len(text) > 4 else ""))
            continue
        if a % 4 == 0 and len(raw) % 4 == 0:
            words = []
            for o in range(0, len(raw), 4):
                if a + o in syms:
                    words.append(syms[a + o])
                else:
                    words.append(f"0x{int.from_bytes(raw[o:o + 4], 'big'):X}")
            ptrs = any(a + o in syms for o in range(0, len(raw), 4))
            if ptrs and all(w in syms.values() or w == "0x0" for w in words):
                words = [w if w != "0x0" else "NULL" for w in words]
                t = "void *"
            else:
                words = [w if not w[0].isalpha() else f"(u32){w}" for w in words]
                t = "u32 "
            if len(words) == 1:
                out.append(f"{t}{name} = {words[0]};")
            else:
                out.append(f"{t}{name}[] = {{ {', '.join(words)} }};")
            continue
        out.append(f"u8 {name}[] = {{ {', '.join(f'0x{c:02X}' for c in raw)} }};")
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("module")
    ap.add_argument("start", type=lambda x: int(x, 16))
    ap.add_argument("end", type=lambda x: int(x, 16))
    ap.add_argument("--c", help="the C file, for the types it declares")
    args = ap.parse_args()
    version = (ROOT / ".version").read_text().strip()
    seg, rom_end = module_info(version, args.module)
    vram, rom = seg["vram"], seg["start"]
    bss_lo = vram + rom_end - rom
    lo, hi = args.start, args.end
    names, syms = labels(asm_files(args.module), lo, hi)
    if lo >= bss_lo:
        print("\n".join(bss_defs(names, lo, hi, declared(args.c))))
    else:
        assert hi <= bss_lo, "a run is data or bss, not both"
        img = (ROOT / "assets" / "code.bin").read_bytes()
        print("\n".join(data_defs(names, syms, img, lambda a: rom + a - vram, lo, hi)))


if __name__ == "__main__":
    main()
