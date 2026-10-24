#!/usr/bin/env python3
"""Compile the NON_MATCHING drafts in nonmatching/ and compare them with
the original, function by function, for the extracted version (.version).

    tools/nonmatching.py [--check] [-v FUNC|all] [draft.c ...]

With no paths, every nonmatching/**/*.c. A draft starts with a comment
whose lines give its flags and how many words still differ per version:

    /*
     * NON_MATCHING: ...
     * flags: -O3
     * differing words: us 5, jp 12
     * ...
     */

Per draft it prints the functions that match and those that differ, with
their word counts (tools/fcmp.py's comparison: relocated bits masked, a
static function counted with the one before it). --check fails if a
draft doesn't compile, has no flags line, or differs in more words than
its header records for the version (a version not recorded is only
reported). Functions already C in src/ are found in the linked build's
map, so `make` first (`make nonmatching-check` does).
"""
import argparse, glob, os, re, sys, textwrap

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fcmp

ROOT = fcmp.ROOT


def header(path):
    m = re.match(r"\s*/\*(.*?)\*/", open(path).read(), re.S)
    text = m.group(1) if m else ""
    flags = re.search(r"^\s*\*?\s*flags:\s*(.*)$", text, re.M)
    limits = re.search(r"^\s*\*?\s*differing words:\s*(.*)$", text, re.M)
    lim = {}
    if limits:
        for v, n in re.findall(r"\b(us|eu|jp)\s+(\d+)", limits.group(1)):
            lim[v] = int(n)
    return (flags.group(1).split() if flags else None), lim


def run(path, verbose, out):
    """Compare one draft; returns (failed, line for the summary)."""
    rel = os.path.relpath(path, ROOT)
    ver = fcmp.version(ROOT)
    flags, lim = header(path)
    if flags is None:
        out(f"{rel}: no `flags:` line in its header")
        return True, f"{rel}: no flags"
    opt, isa, extra = "-O2", "-mips1", []
    for f in flags:
        if f.startswith("-O") or f == "-g": opt = f
        elif f.startswith("-mips"): isa = f
        else: extra.append(f)
    try:
        results, _ = fcmp.compare(path, opt, isa, extra, verbose, ROOT, out)
    except fcmp.CompileError as e:
        out(f"{rel} ({' '.join(flags)}): doesn't compile")
        out(textwrap.indent(str(e).strip(), "    "))
        return True, f"{rel}: doesn't compile"
    ok = [s for s, bad, _, _ in results if bad == 0]
    bad = [(s, b, m, o) for s, b, m, o in results if b]
    unknown = [(s, m) for s, b, m, _ in results if b is None]
    words = sum(b for _, b, _, _ in bad) + sum(m // 4 for _, m in unknown)
    out(f"{rel} ({' '.join(flags)}): {len(ok)} of {len(results)} functions match, {words} words differ")
    if ok:
        out(textwrap.fill(" ".join(ok), 100, initial_indent="  ok:  ", subsequent_indent="        "))
    for s, b, m, o in bad:
        out(f"  BAD  {s}: {b} words (size 0x{m:X} vs 0x{o:X})")
    for s, m in unknown:
        out(f"  ??   {s}: not in the original ({m // 4} words counted)")
    failed = False
    if ver in lim:
        if words > lim[ver]:
            out(f"  WORSE: {words} words differ, the header records {lim[ver]} for {ver}")
            failed = True
        elif words < lim[ver]:
            out(f"  better than the header's {lim[ver]} for {ver}: lower it")
        state = f"{words}/{lim[ver]}"
    else:
        state = f"{words} (no limit for {ver})"
    return failed, f"{rel}: {state}"


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("drafts", nargs="*", help="draft paths (default: every nonmatching/**/*.c)")
    ap.add_argument("--check", action="store_true", help="fail on a compile error or a draft worse than its header")
    ap.add_argument("-v", dest="verbose", help="diff this function (all: every differing one)")
    a = ap.parse_args()
    paths = [os.path.abspath(p) for p in a.drafts] or \
        sorted(glob.glob(os.path.join(ROOT, "nonmatching", "**", "*.c"), recursive=True))
    if not paths:
        print("no drafts"); return 0
    failed = []
    summary = []
    for p in paths:
        f, line = run(p, a.verbose, print)
        summary.append(line)
        if f: failed.append(os.path.relpath(p, ROOT))
    print(f"\n{fcmp.version(ROOT)}: words differing / recorded")
    for line in summary:
        print("  " + line)
    if failed:
        print(f"{len(failed)} failed: " + " ".join(failed))
    return 1 if a.check and failed else 0


if __name__ == "__main__":
    sys.exit(main())
