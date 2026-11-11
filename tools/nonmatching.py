#!/usr/bin/env python3
"""Compile the NON_MATCHING drafts in nonmatching/ and src/ and compare
them with the original, function by function, for the extracted version
(.version).

    tools/nonmatching.py [--check] [-v FUNC|all] [draft.c ...]

With no paths, every nonmatching/**/*.c and every src/**/*.c with an
`#ifdef NON_MATCHING` block. A nonmatching/ draft starts with a comment
whose lines give its flags and how many words still differ per version:

    /*
     * NON_MATCHING: ...
     * flags: -O3
     * differing words: us 5, jp 12
     * ...
     */

Per draft it prints the functions that match and those that differ, with
their word counts (tools/fcmp.py's comparison: relocated words by their
targets, a static function found by its .mdebug procedure). --check fails if a
draft doesn't compile, has no flags line, or differs in more words than
its header records for the version (a version not recorded is only
reported). Functions already C in src/ are found in the linked build's
map, so `make` first (`make nonmatching-check` does).

A src/ file is an -O2 (or -g) object whose near misses sit beside their
asm, each one

    #ifdef NON_MATCHING
    /* 3 differing words (us 3, eu 3, jp 5): what differs */
    <the C function>
    #else
    #pragma GLOBAL_ASM(...)
    #endif

It is compiled with -DNON_MATCHING and the Makefile's flags for it; each
block's function is held to the count its comment records for the
version, and every other C function in the file must match.
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


def make_lists():
    """The Makefile's per-file flag lists: {name: set of src/ paths}."""
    text = open(os.path.join(ROOT, "Makefile")).read().replace("\\\n", " ")
    lists = {}
    for name in ("G_C_FILES", "O3_C_FILES", "MIPS2_C_FILES"):
        m = re.search(rf"^{name}\s*:?=(.*)$", text, re.M)
        lists[name] = set(m.group(1).split()) if m else set()
    return lists


def src_flags(path, lists):
    """A src/ file's flags, as the Makefile builds it."""
    rel = os.path.relpath(path, os.path.join(ROOT, "src"))
    opt = "-g" if rel in lists["G_C_FILES"] else "-O3" if rel in lists["O3_C_FILES"] else "-O2"
    return [opt] + (["-mips2"] if rel in lists["MIPS2_C_FILES"] else [])


BLOCK = re.compile(r"^#ifdef\s+NON_MATCHING\b[^\n]*\n\s*/\*(.*?)\*/(.*?)^#else\b", re.S | re.M)


def src_blocks(path):
    """{function: {version: words}} from a src/ file's NON_MATCHING blocks;
    a function's dict is empty if its comment gives no counts."""
    blocks = {}
    for m in BLOCK.finditer(open(path).read()):
        f = re.search(r"\b(\w+)\s*\([^;{]*\)\s*\{", m.group(2))
        if not f:
            continue
        counts = re.search(r"\(([^)]*)\)", m.group(1))
        blocks[f.group(1)] = {v: int(n) for v, n in re.findall(r"\b(us|eu|jp)\s+(\d+)", counts.group(1))} \
            if counts else {}
    return blocks


def src_files():
    """src/ files (outside libultra) with an #ifdef NON_MATCHING block."""
    out = []
    for p in sorted(glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True)):
        if os.sep + "libultra" + os.sep in p:
            continue
        if re.search(r"^#ifdef\s+NON_MATCHING\b", open(p).read(), re.M):
            out.append(p)
    return out


def run_src(path, verbose, out, lists):
    """Compare one src/ file's NON_MATCHING functions; (failed, summary)."""
    rel = os.path.relpath(path, ROOT)
    ver = fcmp.version(ROOT)
    flags = src_flags(path, lists)
    blocks = src_blocks(path)
    isa = flags[1] if len(flags) > 1 else "-mips1"
    try:
        results, _ = fcmp.compare(path, flags[0], isa, ["-DNON_MATCHING"], verbose, ROOT, out)
    except fcmp.CompileError as e:
        out(f"{rel} ({' '.join(flags)} -DNON_MATCHING): doesn't compile")
        out(textwrap.indent(str(e).strip(), "    "))
        return True, f"{rel}: doesn't compile"
    failed, states = False, []
    out(f"{rel} ({' '.join(flags)} -DNON_MATCHING): {len(blocks)} NON_MATCHING functions")
    for s in sorted(set(blocks) - {r[0] for r in results}):
        out(f"  MISSING {s}: in a NON_MATCHING block but not compiled")
        failed = True
    for s, b, m, o in results:
        words = b if b is not None else m // 4
        if s in blocks:
            lim = blocks[s].get(ver)
            line = f"  {s}: {words} words (size 0x{m:X} vs 0x{o:X})"
            if lim is None:
                out(line + f", no count for {ver}")
                states.append(f"{s} {words}")
                continue
            out(line + f", recorded {lim}")
            states.append(f"{s} {words}/{lim}")
            if words > lim:
                out(f"  WORSE: {s} differs in {words} words, its comment records {lim} for {ver}")
                failed = True
            elif words < lim:
                out(f"  better than the comment's {lim} for {ver}: lower it")
        elif b != 0:
            out(f"  BAD  {s}: {words} words, outside a NON_MATCHING block (should match)")
            failed = True
    return failed, f"{rel}: " + (", ".join(states) or "no blocks")


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
    ap.add_argument("drafts", nargs="*",
                    help="draft paths (default: every nonmatching/**/*.c and src/ file with NON_MATCHING blocks)")
    ap.add_argument("--check", action="store_true", help="fail on a compile error or a draft worse than its header")
    ap.add_argument("-v", dest="verbose", help="diff this function (all: every differing one)")
    a = ap.parse_args()
    paths = [os.path.abspath(p) for p in a.drafts] or \
        sorted(glob.glob(os.path.join(ROOT, "nonmatching", "**", "*.c"), recursive=True)) + src_files()
    if not paths:
        print("no drafts"); return 0
    failed = []
    summary = []
    lists = make_lists()
    src = os.path.join(ROOT, "src") + os.sep
    for p in paths:
        if p.startswith(src):
            f, line = run_src(p, a.verbose, print, lists)
        else:
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
