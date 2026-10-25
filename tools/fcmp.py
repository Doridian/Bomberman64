#!/usr/bin/env python3
"""Compile a C file with IDO and compare each of its functions with the
original (assets/code.bin), by name.

    tools/fcmp.py file.c [-O3|-O2|-g ...] [-mips2] [-v func] [--root DIR]

For a draft before it goes into src/: an -O3 object has to match as a
whole file, which tools/fdiff.py (one function in the linked build)
can't show. The version is the extracted one (.version). The original's place and size come from the extracted asm (asm/**/*.s:
`nonmatching NAME, SIZE` and the first instruction's image offset), so a
function must still be asm somewhere (an asm object or a GLOBAL_ASM .s),
or C already built: a function of a C object is found in the linked
build's map (build/<v>/bm64.<v>.map). A symbol found in neither (a
function splat folded into the one before, like an empty stub) is
compared as part of the function before it. Relocated words are compared
without their relocated bits.

tools/nonmatching.py imports compare() for the drafts in nonmatching/.
"""
import difflib, json, os, re, shutil, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


class CompileError(Exception):
    pass


def build_index(root):
    idx = {}
    nm = re.compile(r"^nonmatching (\S+), 0x([0-9A-Fa-f]+)")
    gl = re.compile(r"^glabel (\S+)")
    ins = re.compile(r"^\s*/\* ([0-9A-F]+) ([0-9A-F]{8}) ")
    for d, _, files in os.walk(os.path.join(root, "asm")):
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
    # functions of C objects, from the linked build's map: an output
    # section's load address is its image offset
    mp = map_path(root)
    if os.path.exists(mp):
        sec = re.compile(r"^\.\S+\s+0x([0-9a-f]+)\s+0x[0-9a-f]+\s+load address 0x([0-9a-f]+)")
        inp = re.compile(r"^ \.(\S+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)$")
        sym = re.compile(r"^\s+0x([0-9a-f]+)\s+([A-Za-z_][\w]*)$")
        base = None; ctext = None; funcs = []
        def flush():
            for k, (a, n) in enumerate(funcs):
                end = funcs[k + 1][0] if k + 1 < len(funcs) else ctext[1]
                idx.setdefault(n, (a - base[0] + base[1], end - a))
            funcs.clear()
        for line in open(mp, errors="replace"):
            m = sec.match(line)
            if m:
                if ctext: flush()
                base = (int(m.group(1), 16), int(m.group(2), 16)); ctext = None; continue
            m = inp.match(line)
            if m:
                if ctext: flush()
                ctext = None
                if base and m.group(1) == "text" and m.group(4).endswith(".c.o"):
                    a = int(m.group(2), 16)
                    ctext = (a, a + int(m.group(3), 16))
                continue
            m = sym.match(line)
            if m and ctext:
                funcs.append((int(m.group(1), 16), m.group(2)))
        if ctext: flush()
    json.dump(idx, open(os.path.join(root, "build", f"fcmp_index.{version(root)}.json"), "w"))
    return idx


def mdebug_procs(obj):
    """[(text offset, name)] of every procedure in IDO's .mdebug, statics
    included (stProc and stStaticProc local symbols)."""
    data = open(obj, "rb").read()
    shoff = struct.unpack(">I", data[0x20:0x24])[0]
    shentsize, shnum, shstrndx = struct.unpack(">HHH", data[0x2E:0x34])
    secs = [struct.unpack(">10I", data[shoff + i * shentsize:shoff + i * shentsize + 40]) for i in range(shnum)]
    strtab = secs[shstrndx][4]
    def name(o):
        return data[o:data.index(b"\0", o)].decode()
    md = next((h for h in secs if name(strtab + h[0]) == ".mdebug"), None)
    if md is None:
        return []
    hdr = struct.unpack(">HH23I", data[md[4]:md[4] + 0x60])
    cbSymOffset, cbSsOffset, ifdMax, cbFdOffset = hdr[10], hdr[16], hdr[19], hdr[20]
    out = set()
    for f in range(ifdMax):
        _, _, issBase, _, isymBase, csym = struct.unpack(">6I", data[cbFdOffset + f * 72:cbFdOffset + f * 72 + 24])
        for i in range(isymBase, isymBase + csym):
            iss, value, bits = struct.unpack(">3I", data[cbSymOffset + i * 12:cbSymOffset + i * 12 + 12])
            if bits >> 26 in (6, 14):
                out.add((value, name(cbSsOffset + issBase + iss)))
    return sorted(out)


def map_path(root):
    v = version(root)
    return os.path.join(root, "build", v, f"bm64.{v}.map")


def load_index(root):
    index = os.path.join(root, "build", f"fcmp_index.{version(root)}.json")
    if os.path.exists(index):
        stamp = os.path.getmtime(index)
        mp = map_path(root)
        if stamp > os.path.getmtime(os.path.join(root, "asm")) and \
                (not os.path.exists(mp) or stamp > os.path.getmtime(mp)):
            return json.load(open(index))
    return build_index(root)


def version(root=ROOT):
    return open(os.path.join(root, ".version")).read().strip()


def compare(cfile, opt="-O2", isa="-mips1", extra=(), verbose=None, root=ROOT, out=print):
    """Compile cfile and compare its functions with the original.

    Returns (results, sections): results is a list of (name, bad words,
    our size, original size), with bad None for a function the asm
    doesn't have; sections maps .text/.data/.rodata/.bss to sizes.
    Prints a diff of the function named verbose ("all": every bad one)
    through out. Raises CompileError with IDO's output if it fails."""
    ver = version(root)
    os.makedirs(os.path.join(root, "build"), exist_ok=True)
    tmp = tempfile.mkdtemp(dir=os.path.join(root, "build"))
    try:
        obj = os.path.join(tmp, "a.o")
        cmd = (f"{root}/tools/ido/5.3/cc -c -G 0 -Xfullwarn -Xcpluscomm -nostdinc -non_shared -Wab,-r4300_mul "
               f"-D_LANGUAGE_C -D_FINALROM -DVERSION_{ver.upper()} -woff 649,838,712,807 -I {root}/include -I {root}/include/PR "
               f"-I {root}/src {opt} {isa} -32 {' '.join(extra)} -o {obj} {os.path.abspath(cfile)}")
        r = subprocess.run(cmd, shell=True, cwd=tmp, capture_output=True, text=True)
        if r.returncode:
            raise CompileError(r.stdout + r.stderr)
        subprocess.run(["mips-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, tmp + "/t.bin"], check=True)
        text = open(tmp + "/t.bin", "rb").read()
        relocs = {}
        res = subprocess.run(["mips-linux-gnu-readelf", "-rW", obj], capture_output=True, text=True).stdout
        sec = None
        for line in res.splitlines():
            m = re.match(r"Relocation section '\.rel\.?(\S*)'", line)
            if m: sec = m.group(1); continue
            m = re.match(r"^([0-9a-f]{8})\s+\S+\s+(\S+)", line)
            if m and sec == "text": relocs[int(m.group(1), 16)] = m.group(2)
        syms = []
        res = subprocess.run(["mips-linux-gnu-nm", "-n", obj], capture_output=True, text=True).stdout
        for line in res.splitlines():
            p = line.split()
            if len(p) == 3 and p[1] in "tT": syms.append((int(p[0], 16), p[2]))
        hd = subprocess.run(["mips-linux-gnu-objdump", "-h", obj], capture_output=True, text=True).stdout
        secs = {l.split()[1]: int(l.split()[2], 16) for l in hd.splitlines() if re.match(r"\s+\d+ \.", l)}
        secs = {k: v for k, v in secs.items() if k in (".text", ".data", ".rodata", ".bss")}
        idx = load_index(root)
        # static functions have no ELF symbol, so statics emitted first would
        # go uncounted: .mdebug names the first, and what follows it up to
        # our first symbol is compared as one run, as below. Ours may come
        # out first under another static's name than the original's (one the
        # asm doesn't label, or a static emitted later there), so the run
        # starts at the original's first static: back from where our first
        # labelled function starts, over the functions the draft defines as
        # statics
        if not syms or syms[0][0] > 0:
            procs = mdebug_procs(obj)
            lead = [(a, s) for a, s in procs if a == 0]
            nxt = next((s for _, s in syms if s in idx), None)
            if lead and nxt:
                statics = {s for _, s in procs} - {s for _, s in syms}
                ends = {o + z: n for n, (o, z) in idx.items() if z}
                start, name = idx[nxt][0], None
                while start in ends and ends[start] in statics:
                    name = ends[start]
                    start = idx[name][0]
                if name:
                    lead = [(0, name)]
            syms[:0] = lead
        code = open(f"{root}/assets/code.bin", "rb").read()
        results = []
        # a symbol the original doesn't have (a function splat folded into
        # the one before) goes with the function before it, unless it's first
        first = next((k for k, (a, s) in enumerate(syms) if s in idx), len(syms))
        for a, s in syms[:first]:
            results.append((s, None, len(text[a:]), 0))
        syms = syms[first:]
        syms = [(a, s, [x for _, x in syms[k + 1:next((j for j in range(k + 1, len(syms)) if syms[j][1] in idx), len(syms))]])
                for k, (a, s) in enumerate(syms) if s in idx]
        starts = {o: n for n, (o, _) in idx.items()}
        names = {s for _, s, _ in syms}
        for k, (a, s, folded) in enumerate(syms):
            end = syms[k + 1][0] if k + 1 < len(syms) else len(text)
            mine = text[a:end]
            off, size = idx[s]
            # static functions have no symbol in IDO's object: what follows a
            # function up to our next symbol is compared with what follows it
            # in the original up to that symbol (empty stubs splat folded in)
            if k + 1 < len(syms):
                nxt = idx[syms[k + 1][1]][0]
                if 0 < nxt - off < 0x10000:
                    size = nxt - off
            else:
                # after the last one, the original's functions we don't
                # name (statics) as far as ours reaches
                while off + size in starts and starts[off + size] not in names \
                        and size + idx[starts[off + size]][1] <= len(mine):
                    size += idx[starts[off + size]][1]
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
            results.append((s + "".join(" +" + x for x in folded), bad, len(mine), size))
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
                out(f"--- {s}")
                for l in difflib.unified_diff(od, md, "orig", "mine", lineterm="", n=4):
                    out(l)
        return results, secs
    finally:
        shutil.rmtree(tmp)


def main():
    global ROOT
    args = sys.argv[1:]
    cfile = None; opt = "-O2"; isa = "-mips1"; verbose = None; extra = []
    i = 0
    while i < len(args):
        a = args[i]
        if a == "-v": verbose = args[i + 1]; i += 2; continue
        if a == "--root": ROOT = args[i + 1]; i += 2; continue
        if a.startswith("-O") or a == "-g": opt = a
        elif a.startswith("-mips"): isa = a
        elif a.startswith("-"): extra.append(a)
        else: cfile = os.path.abspath(a)
        i += 1
    try:
        results, secs = compare(cfile, opt, isa, extra, verbose, ROOT)
    except CompileError as e:
        print(e); sys.exit(1)
    nbad = 0
    for s, bad, mine, size in results:
        if bad is None:
            print(f"??  {s} (not in the asm)"); continue
        if bad: nbad += 1
        print(("ok  " if not bad else "BAD ") + s + ("" if not bad else f" ({bad} words, size 0x{mine:X} vs 0x{size:X})"))
    print("sections:", " ".join(f"{k}=0x{v:X}" for k, v in secs.items()))
    sys.exit(1 if nbad else 0)


if __name__ == "__main__":
    main()
