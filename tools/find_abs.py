#!/usr/bin/env python3
"""List what in the linked code still points into a module without a
relocation, i.e. what a shifted build would leave behind.

  find_abs.py <version> [elf]

The ELF (build/<v>/bm64.<v>.elf by default) must be linked with
--emit-relocs, as the Makefile does.  A module is a code segment of
bm64.<v>.yaml (boot_code, main_code, each overlay), with its bss; its load
address is fixed (the boot loader and the overlay loader jump there), the
rest of it moves.  Reported:

- a lui with no R_MIPS_HI16 whose pair (the next instruction that uses its
  register as a base or adds an immediate to it, before the register is
  written again) makes an address in a module; a lui with no such pair is
  reported when its own value is in a module;
- a word in a data section that holds such an address and has no R_MIPS_32;
- a relocation against an absolute symbol (from undefined_syms_auto.txt)
  whose value is in a module: it links, but it won't move.

zerojump (handwritten, on its fixed page) is left out.  Constants that merely look like addresses show up too; the
report is for a look by hand.
"""
import bisect
import re
import struct
import subprocess
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
CROSS = "mips-linux-gnu-"


def run(*args):
    return subprocess.run(args, capture_output=True, check=True).stdout


def modules(version):
    """[(name, vram, end incl. bss)] of the movable modules."""
    cfg = yaml.safe_load((ROOT / f"bm64.{version}.yaml").read_text())
    segs = cfg["segments"]
    starts = [s["start"] if isinstance(s, dict) else s[0] for s in segs]
    out = []
    for s, end in zip(segs, starts[1:]):
        if isinstance(s, dict) and s.get("type") == "code" and s["vram"]:
            out.append((s["name"], s["vram"],
                        s["vram"] + end - s["start"] + s.get("bss_size", 0)))
    return out


# opcodes that take rs + a 16-bit signed immediate: addiu, loads, stores
LO_OPS = {0x09, 0x20, 0x21, 0x23, 0x24, 0x25, 0x27, 0x28, 0x29, 0x2B,
          0x31, 0x35, 0x39, 0x3D, 0x37, 0x3F}


def writes(w):
    """The register an instruction writes, as far as pairing cares."""
    op = w >> 26
    if op == 0:
        return (w >> 11) & 31
    if op in (0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x20, 0x21,
              0x23, 0x24, 0x25, 0x27, 0x37):
        return (w >> 16) & 31
    if op == 3:
        return 31
    return None


def pair(data, off, end):
    """The address a lui at data[off] makes with its pair, or None."""
    w = struct.unpack_from(">I", data, off)[0]
    reg, hi = (w >> 16) & 31, (w & 0xFFFF) << 16
    for o in range(off + 4, min(end, off + 4 * 64), 4):
        x = struct.unpack_from(">I", data, o)[0]
        op, rs = x >> 26, (x >> 21) & 31
        if op in LO_OPS and rs == reg:
            lo = x & 0xFFFF
            return (hi + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
        if op == 0x0D and rs == reg:  # ori: IDO builds constants so, not addresses
            return None
        if x == 0x03E00008 or writes(x) == reg:
            return None
    return None


def main():
    version = sys.argv[1]
    elf = sys.argv[2] if len(sys.argv) > 2 else f"build/{version}/bm64.{version}.elf"
    mods = modules(version)
    loads = {v for _, v, _ in mods}

    def movable(v):
        # a module's end is a reference to it too (main_code clears its
        # bss up to there)
        return v not in loads and any(a <= v <= e for _, a, e in mods)

    relocs = {}   # (section, offset) -> types
    rsyms = []    # (section, offset, type, symbol)
    sect = None
    for line in run(CROSS + "readelf", "-rW", elf).decode().splitlines():
        m = re.match(r"Relocation section '\.rel(\.\S+)'", line)
        if m:
            sect = m.group(1)
            continue
        p = line.split()
        if sect and len(p) >= 3 and re.fullmatch(r"[0-9a-f]{8}", p[0]) and p[2].startswith("R_MIPS_"):
            relocs.setdefault((sect, int(p[0], 16)), set()).add(p[2])
            if len(p) >= 5:
                rsyms.append((sect, int(p[0], 16), p[2], p[4]))
    if not relocs:
        sys.exit(f"{elf} has no relocations; link it with --emit-relocs")

    sects = []
    for line in run(CROSS + "readelf", "-SW", elf).decode().splitlines():
        m = re.match(r"\s*\[\s*\d+\] (\S+)\s+PROGBITS\s+([0-9a-f]+) [0-9a-f]+ ([0-9a-f]+) \S+\s+(\S+)", line)
        if m and "A" in m.group(4):
            sects.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))

    # symbols, per section, to say where a hit is
    syms = {}
    for line in run(CROSS + "objdump", "-tw", elf).decode().splitlines():
        p = line.split()
        if len(p) >= 6 and re.fullmatch(r"[0-9a-f]{8}", p[0]) and p[-2] != "*ABS*" and p[-3] != "*ABS*":
            syms.setdefault(p[-3] if p[-3].startswith(".") else p[-2], []).append((int(p[0], 16), p[-1]))
    for v in syms.values():
        v.sort()
    absolute = {}
    for line in run(CROSS + "objdump", "-tw", elf).decode().splitlines():
        p = line.split()
        if len(p) >= 4 and re.fullmatch(r"[0-9a-f]{8}", p[0]) and "*ABS*" in p:
            absolute[p[-1]] = int(p[0], 16)

    def where(name, a):
        lst = syms.get(name, [])
        i = bisect.bisect_right(lst, (a, "\xff")) - 1
        return f"{name}:{lst[i][1]}+0x{a - lst[i][0]:X}" if i >= 0 else f"{name}:0x{a:08X}"

    code_ranges = {}
    for line in run(CROSS + "objdump", "-tw", elf).decode().splitlines():
        m = re.match(r"([0-9a-f]{8}) .* (\S+)_TEXT_(START|END)$", line)
        if m:
            code_ranges.setdefault(m.group(2), {})[m.group(3)] = int(m.group(1), 16)

    found = 0
    for name, vma, size in sects:
        if name in (".zerojump", ".header", ".boot"):
            continue
        data = run(CROSS + "objcopy", "-O", "binary", "--only-section", name, elf, "/dev/stdout")
        rng = code_ranges.get(name[1:], {})
        t0, t1 = rng.get("START", vma), rng.get("END", vma)
        for off in range(0, len(data) - 3, 4):
            w = struct.unpack(">I", data[off:off + 4])[0]
            a = vma + off
            r = relocs.get((name, a), ())
            if t0 <= a < t1:
                if w >> 26 == 0x0F and "R_MIPS_HI16" not in r:
                    full = pair(data, off, t1 - vma)
                    if movable(full if full is not None else (w & 0xFFFF) << 16):
                        what = f"0x{full:08X}" if full is not None else "unpaired"
                        print(f"{where(name, a)}: lui 0x{w & 0xFFFF:X} ({what})")
                        found += 1
            elif movable(w) and "R_MIPS_32" not in r:
                print(f"{where(name, a)}: .word 0x{w:08X}")
                found += 1
    # ld reports a symbol assigned outside SECTIONS as absolute; those in
    # module_syms_auto.txt are `label + off`, so they move with the label
    relative = set()
    mod_syms = ROOT / "module_syms_auto.txt"
    if mod_syms.exists():
        relative = {line.split(" = ")[0] for line in mod_syms.read_text().splitlines() if " = " in line}
    seen = set()
    for name, a, typ, sym in rsyms:
        if sym in relative:
            continue
        if sym in absolute and movable(absolute[sym]) and (sym, typ) not in seen:
            seen.add((sym, typ))
            print(f"{where(name, a)}: {typ} against absolute {sym} = 0x{absolute[sym]:08X}")
            found += 1
    print(f"{elf}: {found} found", file=sys.stderr)


if __name__ == "__main__":
    main()
