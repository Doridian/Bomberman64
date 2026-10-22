#!/usr/bin/env python3
"""Replace a C file's extern .rodata constants with the literals they hold.

  tools/inline_rodata.py src/<object>.c      e.g. src/overlays/ovl_09_02/1219F0.c

While a module's .rodata is still asm, every string or float constant a
decompiled function uses is an `extern` naming its address (`extern char
D_X[];`, `extern f32 D_X;`, `extern f64 D_X;`).  Once the object owns its
.rodata (data_split.txt, docs/DECOMPILING.md, "Data"), this rewrites each
use as the literal at that address (a string, `1.5f` or `1.5`) and drops
the extern, so that IDO emits the constant itself.  The bytes come from
assets/code.bin (us: the names are us's addresses).  The sha1 decides
whether that was right.

A symbol used more than once is reported and left alone: IDO emits one
constant per use, so which uses are literals depends on the original.
(Blast Corps' tool, reading the image instead of a .rodata.s.)
"""
import re
import struct
import sys
from collections import Counter
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent


def module_of(c_path):
    """(vram, image offset, symbol prefix) of the module a C file's object is in."""
    cfg = yaml.safe_load((ROOT / "bm64.us.yaml").read_text())
    segs = [s for s in cfg["segments"] if isinstance(s, dict) and s.get("type") == "code"]
    rel = c_path.resolve().relative_to(ROOT / "src")
    if rel.parts[0] == "overlays":
        seg = next(s for s in segs if s["name"] == rel.parts[1])
        return seg["vram"], seg["start"], f"D_ovl{rel.parts[1][4:]}_"
    obj = rel.stem
    for s in segs:
        offs = [sub[0] for sub in s["subsegments"] if isinstance(sub, list)
                and (len(sub) > 2 and sub[2] == obj or f"{sub[0]:X}" == obj)]
        if offs:
            return s["vram"], s["start"], "D_"
    sys.exit(f"{c_path}: no module has object {obj}")


def literal(img, at, ctype):
    if ctype == "char":
        end = img.index(b"\0", at)
        out = img[at:end]
        if not out:
            return None
        esc = {0x0A: "\\n", 0x22: '\\"', 0x5C: "\\\\", 0x09: "\\t"}
        return '"' + "".join(esc.get(c, chr(c) if 0x20 <= c < 0x7F else f"\\{c:03o}")
                             for c in out) + '"'
    if ctype == "f32":
        raw = img[at:at + 4]
        v = struct.unpack(">f", raw)[0]
        for prec in range(1, 20):
            r = f"{v:.{prec}g}"
            if struct.pack(">f", float(r)) == raw:
                break
    else:
        r = repr(struct.unpack(">d", img[at:at + 8])[0])
    if not re.search(r"[.e]", r):
        r += ".0"
    return r + ("f" if ctype == "f32" else "")


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    if (ROOT / ".version").read_text().strip() != "us":
        sys.exit("needs the us tree (make clean; make VERSION=us extract)")
    c_path = Path(sys.argv[1])
    vram, start, prefix = module_of(c_path)
    img = (ROOT / "assets" / "code.bin").read_bytes()
    src = c_path.read_text()
    externs = {m.group(2): m.group(1) for m in re.finditer(
        r"^extern (?:const )?(char|f32|f64) (D_(?:ovl\w\w_\d\d_)?[0-9A-F]{8})(?:\[\])?;[^\n]*$", src, re.M)}
    body = re.sub(r"^extern [^;]*;[^\n]*\n", "", src, flags=re.M)
    uses = Counter(re.findall(r"\b(D_(?:ovl\w\w_\d\d_)?[0-9A-F]{8})\b", body))
    done = []
    for sym, ctype in externs.items():
        if not uses[sym] or not re.fullmatch(rf"{prefix}[0-9A-F]{{8}}", sym):
            continue  # unused, or another module's
        lit = literal(img, start + int(sym[-8:], 16) - vram, ctype)
        if lit is None:
            continue
        if uses[sym] > 1:
            print(f"{sym}: used {uses[sym]} times, left as extern", file=sys.stderr)
            continue
        src = re.sub(rf"^extern [^;]*\b{sym}\b[^;]*;[^\n]*\n", "", src, flags=re.M)
        src = re.sub(rf"\b{sym}\b", lambda m: lit, src)
        done.append(sym)
    c_path.write_text(src)
    print(f"{c_path}: inlined {len(done)}: {' '.join(done)}")


if __name__ == "__main__":
    main()
