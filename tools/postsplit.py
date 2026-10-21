#!/usr/bin/env python3
"""Fix up splat's output so that nothing in a module is left at an absolute
address (what a shifted build would expose).

  postsplit.py <version>

Run by `make extract` after splat.  A module is a code segment of
bm64.<v>.yaml (boot_code, main_code, each overlay) with its bss.  Two kinds
of address survive splat as plain numbers:

- a reference into the middle of an object (`&table[3].field`): splat
  can't put a label there, so it writes an absolute `D_X = 0xX;` into
  undefined_syms_auto.txt.  Those inside a module move to
  module_syms_auto.txt as `D_X = <nearest label below> + off;`.
- a data word holding such an address (`.word 0x8029F8C0`, or the same
  four bytes as a .float or a .byte run): spimdisasm only symbolizes words
  that point at a label.  They are rewritten as
  `.word <nearest label below> + off`.

The labels are the global ones in the asm (glabel/dlabel), placed by the
addresses splat writes in its comments, so this needs no link.  A module
resolves addresses in itself and in the non-overlay modules; an address in
the overlay space seen from outside the overlays is left alone (which
overlay it means isn't known statically) and listed.  Also, ROM addresses
that are a code segment's ROM start or end become `<seg>_ROM_START`/
`_ROM_END` (zerojump's range, which boot_code DMAs), and an address one past
a module's end (with its bss) becomes `<seg>_VRAM_END` (main_code clears
its bss up to there).
"""
import bisect
import re
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
LABEL = re.compile(r"^\s*(?:glabel|dlabel)\s+(\S+)")
COMMENT = re.compile(r"/\* (?:[0-9A-F]+ )?([0-9A-F]{8})(?: [0-9A-F]{8})? \*/")
SYM = re.compile(r"^(\S+) = 0x([0-9A-F]+);")


class Module:
    def __init__(self, name, vram, end, rom, rom_end):
        self.name, self.vram, self.end = name, vram, end
        self.rom, self.rom_end = rom, rom_end
        self.labels = []   # sorted (vram, name)
        self.overlay = name.startswith("ovl_")

    def contains(self, v):
        return self.vram <= v < self.end

    def resolve(self, v, exclude=None):
        """`label + off` for v, or None."""
        i = bisect.bisect_right(self.labels, (v, "\xff")) - 1
        while i >= 0 and self.labels[i][1] == exclude:
            i -= 1
        if i < 0:
            return None
        a, name = self.labels[i]
        return name if a == v else f"{name} + 0x{v - a:X}"


def modules(version):
    cfg = yaml.safe_load((ROOT / f"bm64.{version}.yaml").read_text())
    segs = cfg["segments"]
    starts = [s["start"] if isinstance(s, dict) else s[0] for s in segs]
    out = []
    for s, end in zip(segs, starts[1:]):
        if isinstance(s, dict) and s.get("type") == "code":
            size = end - s["start"]
            out.append(Module(s["name"], s["vram"], s["vram"] + size + s.get("bss_size", 0),
                              s["start"], end))
    return out


def owner_of_file(path, mods):
    """The overlay a file belongs to, by its directory, or None."""
    for part in path.parts:
        if part.startswith("ovl_"):
            return next(m for m in mods if m.name == part)
    return None


def collect_labels(mods, files):
    by_name = {m.name: m for m in mods}
    plain = [m for m in mods if not m.overlay]
    for path in files:
        ovl = owner_of_file(path, mods)
        pending = None
        for line in path.read_text().splitlines():
            m = LABEL.match(line)
            if m:
                pending = m.group(1)
                continue
            if pending:
                c = COMMENT.search(line)
                if c:
                    v = int(c.group(1), 16)
                    mod = ovl if ovl else next((x for x in plain if x.contains(v)), None)
                    if mod is not None:
                        mod.labels.append((v, pending))
                    pending = None
    for m in mods:
        m.labels.sort()
    return by_name


def module_end(mods, home, v):
    """`<module>_VRAM_END` if v is one past the end of a module that `home`
    can see (main_code clears its bss up to its end, for one), else None."""
    for m in mods:
        if v == m.end and (not m.overlay or m is home):
            return f"{m.name}_VRAM_END"
    return None


def visible(mods, home, v):
    """The module an address in `home` (a module or None) refers to."""
    if home is not None and home.contains(v):
        return home
    for m in mods:
        if not m.overlay and m.contains(v):
            return m
    return None


ITEM = re.compile(r"^(\s*/\* [0-9A-F]+ ([0-9A-F]{8})(?: ([0-9A-F]{8}))? \*/\s*)"
                  r"\.(byte|short|half|word|float)\s+(\S+)\s*$")
SIZES = {"byte": 1, "short": 2, "half": 2, "word": 4, "float": 4}


def items(lines):
    """(line index, vram, raw bytes, prefix) of each plain data line;
    a label or anything else in between ends a run (None)."""
    for i, line in enumerate(lines):
        m = ITEM.match(line.rstrip("\n"))
        if not m:
            yield None
            continue
        kind, arg = m.group(4), m.group(5)
        size = SIZES[kind]
        if kind == "word" and not arg.startswith("0x"):
            yield None  # already a symbol
            continue
        if m.group(3):
            raw = int(m.group(3), 16).to_bytes(4, "big")
        elif arg.startswith("0x") and kind in ("byte", "short", "half", "word"):
            raw = int(arg, 16).to_bytes(size, "big")
        else:
            yield None  # already a symbol, or a value we can't reread
            continue
        yield (i, int(m.group(2), 16), raw, m.group(1))


def fix_words(mods, files, report):
    """Rewrite every word-aligned 4 bytes of data that hold a module
    address as `.word <label> + off`, whatever directives splat used for
    them (.word, .float, or a run of .byte/.short)."""
    plain = [m for m in mods if not m.overlay]
    n = 0
    for path in files:
        if "/data/" not in str(path) or path.name.endswith(".bss.s"):
            continue
        home = owner_of_file(path, mods)
        lines = path.read_text().splitlines(keepends=True)
        run = []          # consecutive items
        repl = {}         # first line index -> new line; others -> ""

        def flush():
            buf = b"".join(it[2] for it in run)
            if not run:
                return
            base = run[0][1]
            # byte offset in buf -> item index starting there
            starts, off = {}, 0
            for k, it in enumerate(run):
                starts[off] = k
                off += len(it[2])
            o = (-base) % 4
            while o + 4 <= len(buf):
                if o in starts:
                    k = starts[o]
                    # the 4 bytes must be whole items
                    span, size = [], 0
                    while size < 4 and k < len(run):
                        span.append(run[k])
                        size += len(run[k][2])
                        k += 1
                    v = int.from_bytes(buf[o:o + 4], "big")
                    if size == 4:
                        here = home or next((x for x in plain if x.contains(base)), None)
                        sym = symbol_for(mods, here, v, path, report)
                        if sym:
                            repl[span[0][0]] = f"{span[0][3]}.word {sym}\n"
                            for it in span[1:]:
                                repl[it[0]] = ""
                o += 4
            run.clear()

        for it in items(lines):
            if it is None or (run and it[1] != run[-1][1] + len(run[-1][2])):
                flush()
            if it is not None:
                run.append(it)
        flush()
        if repl:
            n += sum(1 for v in repl.values() if v)
            path.write_text("".join(repl.get(i, line) for i, line in enumerate(lines)))
    return n


def symbol_for(mods, here, v, path, report):
    """`label + off` for an address seen from module `here`, or None."""
    end = module_end(mods, here, v)
    if end:
        return end
    mod = visible(mods, here, v)
    if mod is None:
        if any(m.overlay and m.contains(v) for m in mods) and not (here and here.overlay):
            report.append(f"{path}: 0x{v:08X} points into the overlay space")
        return None
    if v == mod.vram:
        return None  # the load address doesn't move
    sym = mod.resolve(v)
    if sym is None:
        report.append(f"{path}: 0x{v:08X}: no label below it in {mod.name}")
    return sym


def fix_syms(mods, version, report):
    auto = ROOT / "undefined_syms_auto.txt"
    out = ROOT / "module_syms_auto.txt"
    keep = []
    # what an earlier run moved stays moved (this may run twice)
    moved = out.read_text().splitlines() if out.exists() else []
    done = len(moved)
    roms = {}
    for m in mods:  # a start wins over the previous segment's end
        roms.setdefault(m.rom, f"{m.name}_ROM_START")
    for m in mods:
        roms.setdefault(m.rom_end, f"{m.name}_ROM_END")
    for line in auto.read_text().splitlines():
        s = SYM.match(line)
        if not s:
            keep.append(line)
            continue
        name, v = s.group(1), int(s.group(2), 16)
        mod = None
        if name.startswith("D_ovl") or name.startswith("func_ovl"):
            ovl = "ovl_" + "_".join(name.split("_")[1:3])[3:]
            mod = next((m for m in mods if m.name == ovl), None)
        if mod is None:
            mod = visible(mods, None, v)
        end = module_end(mods, mod, v)
        if end and name == f"D_{v:X}" or (end and mod is not None and mod.overlay):
            moved.append(f"{name} = {end};")
            continue
        if mod is not None and mod.contains(v) and v != mod.vram:
            sym = mod.resolve(v, exclude=name)
            if sym is not None:
                moved.append(f"{name} = {sym};")
                continue
            report.append(f"{name} = 0x{v:X}: no label below it in {mod.name}")
        elif v in roms and v < 0x800000 and name == f"D_{v:X}":
            moved.append(f"{name} = {roms[v]};")
            continue
        keep.append(line)
    auto.write_text("\n".join(keep) + "\n")
    out.write_text("".join(f"{line}\n" for line in moved if line))
    return len(moved) - done


def main():
    version = sys.argv[1]
    mods = modules(version)
    files = sorted((ROOT / "asm").rglob("*.s"))
    collect_labels(mods, files)
    report = []
    words = fix_words(mods, files, report)
    syms = fix_syms(mods, version, report)
    for r in report:
        print(r)
    print(f"postsplit: {words} data words and {syms} symbols made relative; "
          f"{len(report)} left (above)", file=sys.stderr)


if __name__ == "__main__":
    main()
