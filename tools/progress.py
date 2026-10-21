#!/usr/bin/env python3
"""Report how much of each code module is decompiled.

Reads the link map (build/<v>/bm64.<v>.map) for the .text size of every
object and the module it is in (boot_code, main_code, an overlay), then
subtracts what each C file still pulls in through GLOBAL_ASM.  The
handwritten objects (`hasm` in the config: boot_code's entry, zerojump, each
module's ZeroJump stub block) are counted apart: they are not meant to
become C for the matching build.  Libraries count with the module they are
linked into until phase 3 tells them apart.

Run after `make VERSION=<v>` (one version's build is there at a time):

    tools/progress.py [--version us] [--overlays] [--json]

--overlays lists every overlay; without it they are summed per bank.
"""

import argparse
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

SECTION = re.compile(r"^\.(\w+)\s")
TEXT_LINE = re.compile(r"^ \.text\s+0x[0-9a-f]+\s+0x([0-9a-f]+)\s+(\S+)$")
GLOBAL_ASM = re.compile(r'^\s*#pragma\s+GLOBAL_ASM\("([^"]+)"\)', re.M)
# one disassembled instruction: /* ROM VRAM WORD */
INSN = re.compile(r"^\s*/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/")
MODULE = re.compile(r"^(boot_code|zerojump|main_code|ovl_[0-9A-F]{2}_\d{2})$")


def asm_bytes(path: Path) -> int:
    with path.open() as f:
        return 4 * sum(1 for line in f if INSN.match(line))


def hasm_objects(version: str) -> set:
    """The config's handwritten objects, as their .s paths."""
    cfg = (ROOT / f"bm64.{version}.yaml").read_text()
    out = set()
    seg_dir = ""
    for line in cfg.splitlines():
        m = re.match(r"\s+dir: (\S+)", line)
        if m:
            seg_dir = m.group(1) + "/"
        elif re.match(r"  - name:", line):
            seg_dir = ""
        m = re.match(r"\s+- \[0x[0-9A-F]+, hasm, (\w+)\]", line)
        if m:
            out.add(f"asm/{seg_dir}{m.group(1)}.s")
    return out


def progress(version: str) -> dict:
    map_path = ROOT / "build" / version / f"bm64.{version}.map"
    if not map_path.exists():
        sys.exit(f"{map_path.relative_to(ROOT)} is missing; build {version} first")
    hand = hasm_objects(version)
    rows = defaultdict(lambda: {"total": 0, "decompiled": 0, "functions_left": 0,
                                "c_files": 0, "handwritten": 0})
    module = None
    prefix = f"build/{version}/"
    with map_path.open() as f:
        for line in f:
            m = SECTION.match(line)
            if m:
                module = m.group(1) if MODULE.match(m.group(1)) else None
                continue
            m = TEXT_LINE.match(line.rstrip())
            if not m or module is None:
                continue
            size = int(m.group(1), 16)
            obj = m.group(2).removeprefix(prefix)
            if not size:
                continue
            r = rows[module]
            if obj.endswith(".c.o"):
                src = ROOT / obj.removesuffix(".o")
                left = 0
                for inc in GLOBAL_ASM.findall(src.read_text()):
                    left += asm_bytes(ROOT / inc)
                    r["functions_left"] += 1
                r["total"] += size
                r["decompiled"] += size - left
                r["c_files"] += 1
            elif obj.endswith(".s.o") and obj.removesuffix(".o") in hand:
                r["handwritten"] += size
            elif obj.endswith(".s.o"):
                r["total"] += size
    return rows


def pct(done, total):
    return 100.0 * done / total if total else 0.0


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    extracted = ROOT / ".version"
    ap.add_argument("--version", default=extracted.read_text().strip()
                    if extracted.exists() else "us")
    ap.add_argument("--overlays", action="store_true", help="one row per overlay")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    rows = progress(args.version)
    if args.json:
        print(json.dumps({"version": args.version, "modules": rows}, indent=2))
        return

    shown = defaultdict(lambda: defaultdict(int))
    for mod, r in rows.items():
        key = mod
        if mod.startswith("ovl_") and not args.overlays:
            key = f"bank{mod[4:6]} ({sum(1 for m in rows if m[:6] == mod[:6])} overlays)"
        for k, v in r.items():
            shown[key][k] += v

    print(f"{args.version}:")
    print(f"{'module':<24}{'C bytes':>10}{'total':>10}{'%':>9}"
          f"{'C files':>9}{'funcs left':>12}{'hand asm':>10}")
    for key, r in shown.items():
        print(f"{key:<24}{r['decompiled']:>10}{r['total']:>10}"
              f"{pct(r['decompiled'], r['total']):>8.2f}%{r['c_files']:>9}"
              f"{r['functions_left']:>12}{r['handwritten']:>10}")
    done = sum(r["decompiled"] for r in rows.values())
    total = sum(r["total"] for r in rows.values())
    ovl = [r for m, r in rows.items() if m.startswith("ovl_")]
    odone, ototal = sum(r["decompiled"] for r in ovl), sum(r["total"] for r in ovl)
    print(f"{'overlays':<24}{odone:>10}{ototal:>10}{pct(odone, ototal):>8.2f}%")
    print(f"{'all':<24}{done:>10}{total:>10}{pct(done, total):>8.2f}%")


if __name__ == "__main__":
    main()
