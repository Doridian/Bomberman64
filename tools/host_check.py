#!/usr/bin/env python3
"""The game's C as a PC port's host compiler takes it (docs/PORT.md, "Readiness").

  host_check.py compile [-v VER] [--cc clang,gcc] [--arch m32,m64]
        every game C file (src/ but libultra, nonmatching/), -DTARGET_PC,
        -fsyntax-only, with the host compilers' errors for C a port can't
        take (implicit declarations, int/pointer and incompatible pointer
        conversions); fails on any error
  host_check.py layout [-v VER]
        the structs whose fields carry their N64 offsets in comments
        (`/* 0x18 */ s64 unk18;`, `} X; /* size 0x8A0 */`), laid out by
        clang for a 32-bit host (-m32 -malign-double: must all match) and a
        64-bit one (counted)
  host_check.py decls [-v VER]
        across files (clang's AST): calls with fewer arguments than the
        definition has (IDO leaves the rest in $a0-$a3; fails), and
        declarations of another shape than the definition (counted)
  host_check.py link [-v VER]
        all of it compiled to 64-bit host objects at once: globals defined
        twice (fails), and what the objects need from elsewhere, by who
        provides it on the N64 (asm data, libultra, ZeroJump stubs,
        handwritten asm, fixed addresses); needs the version's extract
  host_check.py zerojump [-v VER]
        every ZeroJump stub the C declares, resolved through the module
        tables to the function it reaches, and the declarations that differ
        from the definition; needs the version's extract

The port's own SDK headers have a display list's words as wide as a pointer
(Blast Corps' port); here a copy of ultralib's gbi.h with that change
(build/host_check/shim) stands in for them.
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
WORK = os.path.join(ROOT, "build", "host_check")
SHIM = os.path.join(WORK, "shim")
MALLOC_FLAGS = ["-I", "src/libmalloc/include", "-I", "src/libmalloc", "-include", "src/libmalloc/pc_names.h",
                "-DHAVE_UNISTD_H", "-DSTDC_HEADERS", "-DPAGESIZE=0x1000", "-Dsbrk=func_80225B00",
                "-Dmemmove=func_80225BB8", "-Dmemcpy=func_80225C44", "-Dmemset=func_80225C7C"]


def game_files():
    fs = glob.glob("src/**/*.c", recursive=True) + glob.glob("nonmatching/**/*.c", recursive=True)
    return sorted(f for f in fs if "/libultra/" not in f and ".__" not in f)


def make_shim():
    os.makedirs(os.path.join(SHIM, "PR"), exist_ok=True)
    os.makedirs(os.path.join(SHIM, "ultralib", "PR"), exist_ok=True)
    s = open("include/ultralib/PR/gbi.h").read()
    old = "typedef struct {\n\tunsigned int w0;\n\tunsigned int w1;\n} Gwords;"
    assert old in s, "gbi.h's Gwords"
    s = s.replace(old, "typedef struct {\n\t__UINTPTR_TYPE__ w0;\n\t__UINTPTR_TYPE__ w1;\n} Gwords;")
    open(os.path.join(SHIM, "PR", "gbi.h"), "w").write("/* host_check.py: Gwords as wide as a pointer */\n" + s)
    open(os.path.join(SHIM, "ultralib", "PR", "gbi.h"), "w").write("#include <PR/gbi.h>\n")


def flags(f, ver, cc="clang", arch=("-m64",), std="gnu89"):
    inc = ["-iquote", os.path.dirname(f)] + MALLOC_FLAGS if f.startswith("src/libmalloc/") else \
        ["-iquote", os.path.dirname(f), "-I", SHIM, "-I", "include", "-I", "include/PR", "-I", "src",
         "-I", "include/ultralib"]
    return [cc] + list(arch) + ["-std=" + std, "-DTARGET_PC", "-DVERSION_" + ver.upper(), "-D_LANGUAGE_C"] + inc


def blanked(f):
    """a copy of f with its #line directives blanked (IDO tricks), so that
    clang reports the file's own lines"""
    tmp = os.path.join(WORK, "blank", f[:-2] + ".__host_check.c")
    os.makedirs(os.path.dirname(tmp), exist_ok=True)
    open(tmp, "w").write(re.sub(r"(?m)^#line .*$", "", open(f).read()))
    return tmp


# ---- compile -------------------------------------------------------------------

def cmd_compile(a):
    errs = 0
    for cc in a.cc.split(","):
        for arch in a.arch.split(","):
            bad = defaultdict(list)
            for f in game_files():
                extra = ["-ferror-limit=0"] if cc.startswith("clang") else []
                r = subprocess.run(flags(f, a.version, cc, ["-" + arch]) + extra + [
                    "-fsyntax-only", "-w", "-Werror=implicit-function-declaration", "-Werror=int-conversion",
                    "-Werror=incompatible-pointer-types", f], capture_output=True, text=True)
                for l in r.stderr.splitlines():
                    if "error" in l:
                        bad[f].append(l)
            n = sum(len(v) for v in bad.values())
            errs += n
            print("%s -%s: %d files, %d errors" % (cc, arch, len(game_files()), n))
            for f, L in bad.items():
                for l in L[:5]:
                    print("   ", l)
    return 1 if errs else 0


# ---- layout --------------------------------------------------------------------

COMMENT = re.compile(r"/\*\s*0x([0-9A-Fa-f]+)\s*\*/\s*(.*?);")
SIZE = re.compile(r"\}\s*(\w+)?\s*;\s*/\*\s*size:?\s*(?:=\s*)?0x([0-9A-Fa-f]+)\s*\*/")


def struct_blocks(text):
    """line of each struct's `{` -> (names, {field: N64 offset}, N64 size)"""
    lines = text.split("\n")
    out = {}
    for i, line in enumerate(lines):
        m = re.search(r"\b(?:typedef\s+)?(?:struct|union)\s*(\w+)?\s*\{\s*$", line)
        if not m:
            continue
        depth, fields, size, names = 0, {}, None, {m.group(1)} if m.group(1) else set()
        for j in range(i, len(lines)):
            depth += lines[j].count("{") - lines[j].count("}")
            if depth == 1:
                for cm in COMMENT.finditer(lines[j]):
                    decl = re.sub(r"\(\*\s*(\w+)\)\s*\(.*\)", r"\1", cm.group(2))
                    nm = re.search(r"(\w+)\s*(?:\[[^\]]*\])*\s*(?::\s*\d+)?\s*$", decl)
                    if nm:
                        fields[nm.group(1)] = int(cm.group(1), 16)
            if depth == 0 and j > i:
                tm = re.search(r"\}\s*(\w+)?\s*;", lines[j])
                if tm and tm.group(1):
                    names.add(tm.group(1))
                sm = SIZE.search(lines[j])
                if sm:
                    size = int(sm.group(2), 16)
                break
        out[i + 1] = (names, fields, size)
    return out


def layout_diffs(ver, arch):
    total, bad = 0, []
    for f in game_files():
        if f.startswith("src/libmalloc/"):
            continue
        tmp = blanked(f)
        try:
            out = subprocess.run(flags(f, ver, "clang", arch) + [
                "-fsyntax-only", "-w", "-Xclang", "-fdump-record-layouts-complete", "-Xclang",
                "-fdump-record-layouts", tmp], capture_output=True, text=True).stdout
        finally:
            os.unlink(tmp)
        blk = struct_blocks(open(f).read())
        byname = {n: e for e in blk.values() for n in e[0]}
        seen = set()
        for r in out.split("*** Dumping AST Record Layout"):
            lines = r.strip("\n").split("\n")
            h = re.match(r"\s*0 \| (?:struct|union) (.*)$", lines[0]) if lines else None
            if not h:
                continue
            loc = re.match(r"\(unnamed at (.*?):(\d+):\d+\)", h.group(1))
            if loc:
                ent = blk.get(int(loc.group(2))) if loc.group(1).endswith(".__host_check.c") else None
            else:
                ent = byname.get(h.group(1))
            if ent is None or id(ent) in seen or (not ent[1] and ent[2] is None):
                continue
            seen.add(id(ent))
            total += 1
            got, sz = {}, None
            for l in lines[1:]:
                m = re.match(r"\s*(\d+)(?::\d+-\d+)? \|   (\S.*?) (\w+)$", l)
                if m:
                    got[m.group(3)] = int(m.group(1))
                m = re.search(r"\[sizeof=(\d+)", l)
                if m:
                    sz = int(m.group(1))
            d = [(n, o, got[n]) for n, o in ent[1].items() if n in got and got[n] != o]
            if ent[2] is not None and sz is not None and sz != ent[2]:
                d.append(("sizeof", ent[2], sz))
            if d:
                bad.append((f, h.group(1), d))
    return total, bad


def cmd_layout(a):
    t32, b32 = layout_diffs(a.version, ["-m32", "-malign-double"])
    print("-m32 -malign-double: %d structs with N64 offsets, %d laid out otherwise" % (t32, len(b32)))
    for f, n, d in b32:
        print("   %s %s %s" % (f, n, d[:3]))
    t64, b64 = layout_diffs(a.version, ["-m64"])
    print("-m64: %d structs with N64 offsets, %d laid out otherwise (pointers, 8 bytes)" % (t64, len(b64)))
    if a.verbose:
        for f, n, d in b64:
            print("   %s %s %s" % (f, n, d[:3]))
    return 1 if b32 else 0


# ---- the AST: declarations, definitions, calls ----------------------------------

def tcls(t):
    t = t.strip()
    if t == "void":
        return "v"
    if "*" in t or "[" in t or "(" in t:
        return "p"
    if t in ("float", "double", "long double"):
        return "f"
    return "i"


def split_params(ft):
    depth = 0
    for i in range(len(ft) - 1, -1, -1):
        c = ft[i]
        if c == ")":
            depth += 1
        elif c == "(":
            depth -= 1
            if depth == 0:
                ret, ps = ft[:i].strip(), ft[i + 1:-1]
                break
    else:
        return ft, None
    if ps.strip() == "":
        return ret, None
    out, depth, cur = [], 0, ""
    for c in ps:
        if c == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
            continue
        depth += c in "(["
        depth -= c in ")]"
        cur += c
    out.append(cur.strip())
    return ret, ([] if out == ["void"] else out)


def ast(ver):
    """funcs: name -> [(kind, static, ret, params|None, variadic, file)];
    calls: [(file, line, caller, callee, nargs)]"""
    cache = os.path.join(WORK, "ast-%s.json" % ver)
    funcs, calls = defaultdict(list), []

    def qt(n):
        t = n.get("type", {})
        return t.get("desugaredQualType", t.get("qualType", ""))

    def walk(n, f, fname, st):
        if not isinstance(n, dict):
            return
        b = n.get("range", {}).get("begin", {})
        b = b.get("spellingLoc", b)
        if "line" in b:
            st[0] = b["line"]
        if n.get("kind") == "CallExpr":
            inner = n.get("inner", [])
            c = inner[0] if inner else {}
            while c.get("kind") in ("ImplicitCastExpr", "ParenExpr") and c.get("inner"):
                c = c["inner"][0]
            rd = c.get("referencedDecl", {}) if c.get("kind") == "DeclRefExpr" else {}
            if rd.get("kind") == "FunctionDecl":
                calls.append((f, st[0], fname, rd.get("name"), len(inner) - 1))
        for x in n.get("inner", []) or []:
            walk(x, f, fname, st)

    for f in game_files():
        tmp = blanked(f)
        try:
            out = subprocess.run(flags(f, ver) + ["-fsyntax-only", "-w", "-Xclang", "-ast-dump=json", tmp],
                                 capture_output=True, text=True).stdout
        finally:
            os.unlink(tmp)
        for d in json.loads(out).get("inner", []):
            if d.get("kind") != "FunctionDecl" or not d.get("name"):
                continue
            ret, ps = split_params(qt(d))
            body = any(c.get("kind") == "CompoundStmt" for c in d.get("inner", []))
            if body and ps is None:
                ps = [qt(c) for c in d.get("inner", []) if c.get("kind") == "ParmVarDecl"]
            variadic = bool(d.get("variadic")) or bool(ps and ps[-1] == "...")
            funcs[d["name"]].append(("def" if body else "decl", d.get("storageClass") == "static", ret, ps,
                                     variadic, f))
            if body:
                b = d.get("loc", {})
                walk(d, f, d["name"], [b.get("spellingLoc", b).get("line", 0)])
    json.dump({"funcs": funcs, "calls": calls}, open(cache, "w"))
    return funcs, calls


def definitions(funcs):
    glob_defs, static_defs = {}, {}
    for n, L in funcs.items():
        for e in L:
            if e[0] == "def":
                if e[1]:
                    static_defs[(e[5], n)] = e
                else:
                    glob_defs.setdefault(n, e)
    return glob_defs, static_defs


def cmd_decls(a):
    funcs, calls = ast(a.version)
    gd, sd = definitions(funcs)
    fewer = []
    for f, line, caller, callee, n in calls:
        d = sd.get((f, callee)) or gd.get(callee)
        if d and not d[4] and n < len(d[3]):
            fewer.append("%s:%d %s calls %s with %d of %d arguments" % (f, line, caller, callee, n, len(d[3])))
    shapes = defaultdict(int)
    for n, L in funcs.items():
        d = gd.get(n)
        if d is None:
            continue
        dp = [tcls(p) for p in d[3]]
        for e in {(x[2], tuple(x[3]), x[5]) for x in L if x[0] == "decl" and x[3] is not None}:
            ep = [tcls(p) for p in e[1]]
            if len(ep) != len(dp) and not d[4]:
                shapes["parameter count"] += 1
            for x, y in zip(ep, dp):
                if x != y:
                    shapes["parameter %s/%s" % tuple(sorted((x, y)))] += 1
            r1, r2 = tcls(e[0]), tcls(d[2])
            if r1 != r2:
                shapes["return %s, defined %s" % (r1, r2)] += 1
    print("calls with fewer arguments than the definition: %d" % len(fewer))
    for l in fewer:
        print("   " + l)
    print("declarations of another shape than the definition (i: integer, p: pointer, f: float, v: void):")
    for k, n in sorted(shapes.items(), key=lambda e: -e[1]):
        print("   %4d %s" % (n, k))
    return 1 if fewer else 0


# ---- link and zerojump -------------------------------------------------------------

def zerojump_stubs():
    stubs, unnamed = {}, {}
    for f in glob.glob("asm/*_zerojmp.s") + glob.glob("asm/overlays/*/*_zerojmp.s"):
        mod = os.path.basename(f)[:-len("_zerojmp.s")]
        prefix = "func_" if mod == "main_code" else "func_ovl%s_" % mod[4:]
        lines = open(f).read().split("\n")
        label = None
        for i, line in enumerate(lines):
            g = re.match(r"\s*glabel (\w+)", line)
            if g:
                label = g.group(1)
                continue
            m = re.search(r"/\* \w+ ([0-9A-F]{8}) 00000008 \*/\s+jr\s+\$zero", line)
            if m:
                # a stub's name is its label (eu and jp's carry us's names, vermap) or its address
                m2 = re.search(r"\$t0, \$zero, (0x[0-9A-Fa-f]+|\d+)$", lines[i + 1])
                sid = int(m2.group(1), 0) if m2 else 0
                if label:
                    stubs[label] = sid
                else:
                    # an unlabelled stub: its address, unless a label (another
                    # version's name, vermap) already has that name
                    unnamed[prefix + m.group(1)] = sid
                label = None
    for n, sid in unnamed.items():
        stubs.setdefault(n, sid)
    return stubs


def need_extract():
    if not glob.glob("asm/*_zerojmp.s"):
        sys.exit("no asm/: run `make VERSION=<v> extract` first")


def cmd_link(a):
    need_extract()
    odir = os.path.join(WORK, "obj-" + a.version)
    os.makedirs(odir, exist_ok=True)
    defs, undef = defaultdict(set), defaultdict(set)
    failed = []
    for f in game_files():
        o = os.path.join(odir, f.replace("/", "_") + ".o")
        r = subprocess.run(flags(f, a.version) + ["-c", "-w", "-fno-common", "-fno-stack-protector", f, "-o", o],
                           capture_output=True, text=True)
        if r.returncode:
            failed.append(f)
            continue
        for line in subprocess.run(["nm", o], capture_output=True, text=True).stdout.splitlines():
            p = line.split()
            if len(p) == 2 and p[0] == "U":
                undef[p[1]].add(f)
            elif len(p) == 3 and p[1] in "TDBRCVW":
                defs[p[2]].add(f)
    dups = {s: fs for s, fs in defs.items() if len(fs) > 1}
    print("%d objects (%d failed to compile), %d globals, %d defined more than once" % (
        len(game_files()), len(failed), len(defs), len(dups)))
    for s, fs in sorted(dups.items()):
        print("   %s: %s" % (s, " ".join(sorted(fs))))

    def labels(paths, pat):
        out = set()
        for p in paths:
            for line in open(p, errors="replace"):
                m = re.match(pat, line)
                if m:
                    out.add(m.group(1))
        return out

    asm_data = labels(glob.glob("asm/data/**/*.s", recursive=True), r"\s*dlabel (\w+)")
    stubs = zerojump_stubs()
    hand = {}
    for p in glob.glob("asm/*.s"):
        if not p.endswith("_zerojmp.s") and not p.endswith("header.s"):
            for s in labels([p], r"\s*glabel (\w+)"):
                hand[s] = os.path.basename(p)
    cls = defaultdict(list)
    for s in sorted(undef):
        if s in defs:
            continue
        if s in hand:
            c = "handwritten asm: " + hand[s]
        elif s in stubs:
            c = "ZeroJump stubs (asm/*_zerojmp.s)"
        elif s in asm_data:
            c = "asm data (asm/data)"
        elif re.search(r"_ROM_(START|END)$", s):
            c = "linker symbols"
        elif re.match(r"^D_[0-9A-F]+$", s):
            c = "fixed addresses (in no section: undefined_syms_auto.txt)"
        elif re.match(r"^(__)?(os|al|gu|__ll|__ull|__d_to|__f_to|__osGet)|^(sinf|cosf|fcos|fsin|sqrtf|sprintf|memcpy|bcopy|bzero)$", s):
            c = "libultra (src/libultra)"
        else:
            c = "other"
        cls[c].append(s)
    for c, L in sorted(cls.items(), key=lambda e: -len(e[1])):
        show = c.startswith("handwritten") or c in ("linker symbols", "other")
        print("needed from %s: %d%s" % (c, len(L), (": " + " ".join(L)) if show else ""))
    return 1 if dups or failed else 0


def cmd_zerojump(a):
    need_extract()
    funcs, calls = ast(a.version)
    gd, _ = definitions(funcs)
    stubs = zerojump_stubs()
    reg = {"func_80001A30"} | {s for s, i in stubs.items() if i == 0}
    tables, regs = {}, defaultdict(set)
    for f in game_files():
        text = subprocess.run(flags(f, a.version)[:1] + ["-E", "-P"] + flags(f, a.version)[2:] + [f],
                              capture_output=True, text=True).stdout
        for m in re.finditer(r"\b(D_\w+)\s*\[\w*\]\s*=\s*\{(.*?)\};", text, flags=re.S):
            names = [re.sub(r"^\(\w+\s*\*?\)\s*", "", e.strip().lstrip("&").strip()) for e in m.group(2).split(",")
                     if e.strip()]
            if names and all(re.match(r"^([A-Za-z_]\w*|0|\(\(void \*\)0\))$", e) for e in names):
                tables[m.group(1)] = names
        for m in re.finditer(r"\b(func_\w+)\(\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*&?(D_\w+)\s*\)", text):
            if m.group(1) in reg:
                regs[int(m.group(2), 0)].add(m.group(3))
    for p in glob.glob("asm/data/**/*.s", recursive=True):
        cur, ents = None, []
        for line in open(p):
            m = re.match(r"\s*dlabel\s+(\w+)", line)
            if m:
                if cur and ents:
                    tables.setdefault(cur, ents)
                cur, ents = m.group(1), []
                continue
            m = re.search(r"\.word\s+(\w+)\s*$", line)
            if m and cur:
                ents.append(m.group(1))
        if cur and ents:
            tables.setdefault(cur, ents)
    called = {c[3] for c in calls}
    declared = sorted(n for n in funcs if n in stubs and stubs[n] != 0 and n in called)
    out, unresolved = defaultdict(int), []
    for s in declared:
        hi, lo = stubs[s] >> 8, stubs[s] & 0xFF
        targets = {tables[t][lo] for t in regs.get(hi, ()) if t in tables and lo < len(tables[t])}
        if not targets:
            unresolved.append("%s (%#x)" % (s, stubs[s]))
        for t in targets:
            d = gd.get(t)
            if d is None:
                out["reach a function that isn't the game's C (libultra, asm)"] += 1
                continue
            dp = [tcls(p) for p in d[3]]
            for e in {(x[2], tuple(x[3]) if x[3] is not None else None) for x in funcs[s] if x[0] == "decl"}:
                if e[1] is None:
                    out["declared without a prototype"] += 1
                    continue
                sp = [tcls(p) for p in e[1]]
                if len(sp) < len(dp) and not d[4]:
                    out["pass fewer arguments than the function takes"] += 1
                    if a.verbose:
                        print("   fewer: %s (%#x) -> %s: %d of %d" % (s, stubs[s], t, len(sp), len(dp)))
                if any(x != y and "f" in (x, y) for x, y in zip(sp, dp)):
                    out["pass a float for an integer or the reverse"] += 1
                if any(x != y and {x, y} == {"i", "p"} for x, y in zip(sp, dp)):
                    out["pass an integer for a pointer or the reverse"] += 1
                r1, r2 = tcls(e[0]), tcls(d[2])
                if r1 != r2 and r1 != "v":
                    out["expect a return value the function doesn't give" if r2 == "v" else
                        "expect a return value of another class"] += 1
    print("ZeroJump stubs the C calls: %d; module tables registered: %d (each id once)" % (
        len(declared), len(regs)))
    for k, n in sorted(out.items(), key=lambda e: -e[1]):
        print("   %4d %s" % (n, k))
    print("unresolved (no table registered for the id): %d %s" % (len(unresolved), " ".join(unresolved)))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["compile", "layout", "decls", "link", "zerojump"])
    ap.add_argument("-v", "--version", default=None, help="us, eu or jp (default: .version, else us)")
    ap.add_argument("--cc", default="clang,gcc")
    ap.add_argument("--arch", default="m32,m64")
    ap.add_argument("--verbose", action="store_true")
    a = ap.parse_args()
    os.chdir(ROOT)
    if a.version is None:
        a.version = open(".version").read().strip() if os.path.exists(".version") else "us"
    os.makedirs(WORK, exist_ok=True)
    make_shim()
    sys.exit({"compile": cmd_compile, "layout": cmd_layout, "decls": cmd_decls, "link": cmd_link,
              "zerojump": cmd_zerojump}[a.cmd](a))


if __name__ == "__main__":
    main()
