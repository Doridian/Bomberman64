#!/usr/bin/env python3
"""Compile a C file with IDO and compare each of its functions with the
original (assets/code.bin), by name.

    tools/fcmp.py file.c [-O3|-O2|-g ...] [-v func] [--root DIR]

For a draft before it goes into src/: an -O3 object has to match as a
whole file, which tools/fdiff.py (one function in the linked build)
can't show. The version is the extracted one (.version). The original's place and size come from the extracted asm (asm/**/*.s:
`nonmatching NAME, SIZE` and the first instruction's image offset), so a
function must still be asm somewhere (an asm object or a GLOBAL_ASM .s).
Relocated words are compared without their relocated bits.
"""
import difflib, json, os, re, shutil, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
args = sys.argv[1:]
cfile = None; opt = "-O2"; verbose = None; extra = []
i = 0
while i < len(args):
    a = args[i]
    if a == "-v": verbose = args[i + 1]; i += 2; continue
    if a == "--root": ROOT = args[i + 1]; i += 2; continue
    if a.startswith("-O") or a == "-g": opt = a
    elif a.startswith("-"): extra.append(a)
    else: cfile = os.path.abspath(a)
    i += 1

VERSION = open(os.path.join(ROOT, ".version")).read().strip()
os.makedirs(os.path.join(ROOT, "build"), exist_ok=True)
INDEX = os.path.join(ROOT, "build", "fcmp_index.json")


def build_index():
    idx = {}
    nm = re.compile(r"^nonmatching (\S+), 0x([0-9A-Fa-f]+)")
    gl = re.compile(r"^glabel (\S+)")
    ins = re.compile(r"^\s*/\* ([0-9A-F]+) ([0-9A-F]{8}) ")
    for d, _, files in os.walk(os.path.join(ROOT, "asm")):
        for f in files:
            if not f.endswith(".s"): continue
            sizes = {}
            pending = None
            for line in open(os.path.join(d, f), errors="replace"):
                m = nm.match(line)
                if m: sizes[m.group(1)] = int(m.group(2), 16); continue
                m = gl.match(line)
                if m: pending = m.group(1); continue
                if pending:
                    m = ins.match(line)
                    if m:
                        idx.setdefault(pending, (int(m.group(1), 16), sizes.get(pending, 0)))
                        pending = None
    json.dump(idx, open(INDEX, "w"))
    return idx


def load_index():
    if os.path.exists(INDEX):
        stamp = os.path.getmtime(INDEX)
        if stamp > os.path.getmtime(os.path.join(ROOT, "asm")):
            return json.load(open(INDEX))
    return build_index()


tmp = tempfile.mkdtemp(dir=os.path.join(ROOT, "build"))
try:
    obj = os.path.join(tmp, "a.o")
    cmd = (f"{ROOT}/tools/ido/5.3/cc -c -G 0 -Xfullwarn -Xcpluscomm -nostdinc -non_shared -Wab,-r4300_mul "
           f"-D_LANGUAGE_C -D_FINALROM -DVERSION_{VERSION.upper()} -woff 649,838,712,807 -I {ROOT}/include -I {ROOT}/include/PR "
           f"-I {ROOT}/src {opt} -mips1 -32 {' '.join(extra)} -o {obj} {cfile}")
    r = subprocess.run(cmd, shell=True, cwd=tmp, capture_output=True, text=True)
    if r.returncode:
        print(r.stdout, r.stderr); sys.exit(1)
    subprocess.run(["mips-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, tmp + "/t.bin"], check=True)
    text = open(tmp + "/t.bin", "rb").read()
    relocs = {}
    out = subprocess.run(["mips-linux-gnu-readelf", "-rW", obj], capture_output=True, text=True).stdout
    sec = None
    for line in out.splitlines():
        m = re.match(r"Relocation section '\.rel\.?(\S*)'", line)
        if m: sec = m.group(1); continue
        m = re.match(r"^([0-9a-f]{8})\s+\S+\s+(\S+)", line)
        if m and sec == "text": relocs[int(m.group(1), 16)] = m.group(2)
    syms = []
    out = subprocess.run(["mips-linux-gnu-nm", "-n", obj], capture_output=True, text=True).stdout
    for line in out.splitlines():
        p = line.split()
        if len(p) == 3 and p[1] in "tT": syms.append((int(p[0], 16), p[2]))
    hd = subprocess.run(["mips-linux-gnu-objdump", "-h", obj], capture_output=True, text=True).stdout
    secs = {l.split()[1]: int(l.split()[2], 16) for l in hd.splitlines() if re.match(r"\s+\d+ \.", l)}
    idx = load_index()
    code = open(f"{ROOT}/assets/code.bin", "rb").read()
    nbad = 0
    for k, (a, s) in enumerate(syms):
        end = syms[k + 1][0] if k + 1 < len(syms) else len(text)
        mine = text[a:end]
        if s not in idx:
            print(f"??  {s} (not in the asm)"); continue
        off, size = idx[s]
        # static functions have no symbol in IDO's object: what follows a
        # function up to our next symbol is compared with what follows it
        # in the original up to that symbol (empty stubs splat folded in)
        if k + 1 < len(syms) and syms[k + 1][1] in idx:
            nxt = idx[syms[k + 1][1]][0]
            if 0 < nxt - off < 0x10000:
                size = nxt - off
        orig = code[off:off + size]
        # IDO pads the last function of a file to 16 with nops
        while len(mine) > size and mine[-4:] == b"\0\0\0\0" and k + 1 == len(syms):
            mine = mine[:-4]
        bad = 0
        for o in range(0, max(len(mine), size), 4):
            x, y = mine[o:o + 4], orig[o:o + 4]
            if x == y: continue
            if len(x) == 4 and len(y) == 4 and (a + o) in relocs:
                wx, wy = int.from_bytes(x, "big"), int.from_bytes(y, "big")
                op = wx >> 26
                mask = 0xFC000000 if op in (2, 3) else 0xFFFF0000
                if wx & mask == wy & mask: continue
            bad += 1
        if bad: nbad += 1
        print(("ok  " if not bad else "BAD ") + s + ("" if not bad else f" ({bad} words, size 0x{len(mine):X} vs 0x{size:X})"))
        if verbose == s or (verbose == "all" and bad):
            open(tmp + "/m.bin", "wb").write(mine)
            open(tmp + "/o.bin", "wb").write(orig)
            def dis(p):
                o = subprocess.run(f"mips-linux-gnu-objdump -D -b binary -m mips:4300 -EB {p}", shell=True,
                                   capture_output=True, text=True).stdout
                res = []
                for l in o.splitlines():
                    l = l.split("\t")
                    if len(l) >= 3 and re.match(r"\s*[0-9a-f]+:", l[0]):
                        res.append(" ".join(x.strip() for x in l[2:]))
                return res
            # mark relocated words
            md, od = dis(tmp + "/m.bin"), dis(tmp + "/o.bin")
            for o in range(len(md)):
                if (a + o * 4) in relocs:
                    md[o] = re.sub(r"0x[0-9a-f]+|\b\d+\b", "R", md[o]) if relocs[a + o * 4] != "R_MIPS_26" else md[o].split()[0] + " R"
                    if o < len(od):
                        od[o] = re.sub(r"0x[0-9a-f]+|\b\d+\b", "R", od[o]) if relocs[a + o * 4] != "R_MIPS_26" else od[o].split()[0] + " R"
            for l in difflib.unified_diff(od, md, "orig", "mine", lineterm="", n=4):
                print(l)
    print("sections:", " ".join(f"{k}=0x{v:X}" for k, v in secs.items() if k in (".text", ".data", ".rodata", ".bss")))
    sys.exit(1 if nbad else 0)
finally:
    shutil.rmtree(tmp)
