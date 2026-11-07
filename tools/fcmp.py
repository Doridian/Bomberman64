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
compared as part of the function before it. A relocated word is compared
without its relocated bits, and then by its target: our symbol plus
addend, resolved to a VRAM of the extracted version (RelocCheck), must give
the original word's bits (a %hi, a %lo, a jal's target), or the word
counts as differing; -v shows it as `R(wrong: ours vs the asm's)`.

tools/nonmatching.py imports compare() for the drafts in nonmatching/.
"""
import difflib, json, os, re, shutil, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


REFS_FORMAT = 1  # of build/fcmp_refs.<v>.json: bump when it changes


class CompileError(Exception):
    pass


def build_index(root):
    """{function: (image offset, size)}; also writes the references index
    (load_refs)."""
    idx = {}
    objsecs = {}  # a C object of the linked build (src/x.c): {section: VRAM}
    refs = {}    # image offset of an instruction: its symbolic operand
    labels = {}  # label (any: glabel, dlabel, jlabel, .L): VRAM
    nm = re.compile(r"^nonmatching (\S+), 0x([0-9A-Fa-f]+)")
    gl = re.compile(r"^glabel (\S+)")
    lab = re.compile(r"^\s*(?:[dj]?label|glabel) (\S+)|^\s*(\.L\w+):")
    ins = re.compile(r"^\s*/\* ([0-9A-F]+) ([0-9A-F]{8}) ")
    vr = re.compile(r"^\s*/\* (?:[0-9A-F]+ )?([0-9A-F]{8}) ")
    hilo = re.compile(r"%(hi|lo)\(([^)]*)\)")
    jmp = re.compile(r"\*/\s+(j|jal)\s+([A-Za-z_.][\w.]*(?: [-+] 0x[0-9A-Fa-f]+)?)\s*$")
    for d, _, files in os.walk(os.path.join(root, "asm")):
        for f in files:
            if not f.endswith(".s"): continue
            sizes = {}
            pending = None
            plabels = []
            for line in open(os.path.join(d, f), errors="replace"):
                m = nm.match(line)
                if m: sizes[m.group(1)] = int(m.group(2), 16); continue
                m = lab.match(line)
                if m: plabels.append(m.group(1) or m.group(2))
                m = gl.match(line)
                if m: pending = m.group(1); continue
                if plabels:
                    m = vr.match(line)
                    if m:
                        for x in plabels:
                            labels.setdefault(x, int(m.group(1), 16))
                        plabels = []
                m = ins.match(line)
                if m:
                    if pending:
                        idx.setdefault(pending, (int(m.group(1), 16), sizes.get(pending, 0)))
                        pending = None
                    r = hilo.search(line)
                    if r:
                        refs[int(m.group(1), 16)] = r.group(2).strip()
                    else:
                        r = jmp.search(line)
                        if r: refs[int(m.group(1), 16)] = r.group(2)
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
                if m.group(4).endswith(".c.o") and m.group(1) in ("text", "data", "rodata", "bss"):
                    k = re.sub(r"^build/[^/]+/", "", m.group(4))[:-2]
                    objsecs.setdefault(k, {}).setdefault("." + m.group(1), int(m.group(2), 16))
                if base and m.group(1) == "text" and m.group(4).endswith(".c.o"):
                    a = int(m.group(2), 16)
                    ctext = (a, a + int(m.group(3), 16))
                continue
            m = sym.match(line)
            if m and ctext:
                funcs.append((int(m.group(1), 16), m.group(2)))
        if ctext: flush()
        msym = re.compile(r"^\s+0x([0-9a-f]+)\s+([A-Za-z_]\w*)(?:$| = )")
        for line in open(mp, errors="replace"):
            m = msym.match(line)
            if m: labels.setdefault(m.group(2), int(m.group(1), 16) & 0xFFFFFFFF)
    # what splat left unlabelled (its *_auto.txt, the extracted version's)
    for f in ("undefined_syms_auto.txt", "undefined_funcs_auto.txt"):
        f = os.path.join(root, f)
        if os.path.exists(f):
            for line in open(f):
                m = re.match(r"^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", line)
                if m: labels.setdefault(m.group(1), int(m.group(2), 16))
    v = version(root)
    json.dump(idx, open(os.path.join(root, "build", f"fcmp_index.{v}.json"), "w"))
    json.dump({"format": REFS_FORMAT, "refs": refs, "labels": labels, "objsecs": objsecs}, open(os.path.join(root, "build", f"fcmp_refs.{v}.json"), "w"))
    return idx


def mdebug_procs(obj):
    """[(text offset, name)] of every procedure in IDO's .mdebug, statics
    included (stProc and stStaticProc local symbols)."""
    return sorted({(value, n) for st, _, value, n in mdebug_syms(obj) if st in (6, 14)})


def mdebug_syms(obj):
    """[(st, sc, value, name)] of every local symbol in IDO's .mdebug."""
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
    out = []
    for f in range(ifdMax):
        _, _, issBase, _, isymBase, csym = struct.unpack(">6I", data[cbFdOffset + f * 72:cbFdOffset + f * 72 + 24])
        for i in range(isymBase, isymBase + csym):
            iss, value, bits = struct.unpack(">3I", data[cbSymOffset + i * 12:cbSymOffset + i * 12 + 12])
            out.append((bits >> 26, (bits >> 21) & 0x1F, value, name(cbSsOffset + issBase + iss)))
    return out


def map_path(root):
    v = version(root)
    return os.path.join(root, "build", v, f"bm64.{v}.map")


def fresh(path, root):
    if not os.path.exists(path): return False
    stamp = os.path.getmtime(path)
    mp = map_path(root)
    return stamp > os.path.getmtime(os.path.join(root, "asm")) and \
        (not os.path.exists(mp) or stamp > os.path.getmtime(mp))


def load_index(root):
    index = os.path.join(root, "build", f"fcmp_index.{version(root)}.json")
    if fresh(index, root) and fresh(index.replace("fcmp_index", "fcmp_refs"), root):
        return json.load(open(index))
    return build_index(root)


def load_refs(root):
    """(refs, labels): the asm's symbolic operand of each relocated
    instruction by image offset ("D_x", "D_x + 0x4", ".L..."), and the VRAM
    of every asm label and every symbol of the linked build's map."""
    path = os.path.join(root, "build", f"fcmp_refs.{version(root)}.json")
    j = json.load(open(path)) if fresh(path, root) else {}
    if j.get("format") != REFS_FORMAT:
        build_index(root)
        j = json.load(open(path))
    return {int(k): v for k, v in j["refs"].items()}, j["labels"], j["objsecs"]


def split_expr(e):
    """"D_x + 0x4" -> ("D_x", 4)"""
    m = re.match(r"^(\S+)(?: ([-+]) (0x[0-9A-Fa-f]+|\d+))?$", e.strip())
    if not m: return e, 0
    n = int(m.group(3), 0) if m.group(3) else 0
    return m.group(1), -n if m.group(2) == "-" else n


def label_vram(name, labels):
    """A symbol's VRAM in the extracted version: its asm label, or failing
    that a name of the address form (us's address, D_ovlNN_MM_8004xxxx) 
    placed from the nearest label below it with the same prefix."""
    if name in labels: return labels[name]
    m = re.match(r"^(\w*?)([0-9A-F]{8})$", name)
    if not m: return None
    pre, a = m.group(1), int(m.group(2), 16)
    best = None
    for n, v in labels.items():
        if n.startswith(pre) and len(n) == len(name):
            mm = re.match(r"^(\w*?)([0-9A-F]{8})$", n)
            if mm and mm.group(1) == pre:
                b = int(mm.group(2), 16)
                if b <= a and (best is None or b > best[0]): best = (b, v)
    if best is None or a - best[0] > 0x1000: return None
    return best[1] + a - best[0]


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
        rlist = []
        res = subprocess.run(["mips-linux-gnu-readelf", "-rW", obj], capture_output=True, text=True).stdout
        sec = None
        for line in res.splitlines():
            m = re.match(r"Relocation section '\.rel\.?(\S*)'", line)
            if m: sec = m.group(1); continue
            m = re.match(r"^([0-9a-f]{8})\s+\S+\s+(\S+)(?:\s+[0-9a-f]+\s+(\S+))?", line)
            if m and sec == "text":
                relocs[int(m.group(1), 16)] = m.group(2)
                rlist.append((int(m.group(1), 16), m.group(2), m.group(3)))
        targets = reloc_targets(text, rlist)
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
        check = RelocCheck(root, obj, idx, targets, code, cfile)
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
        check.runs([(a, syms[k + 1][0] if k + 1 < len(syms) else len(text), s) for k, (a, s, _) in enumerate(syms)])
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
            wrong = {}
            for o in range(0, max(len(mine), size), 4):
                x, y = mine[o:o + 4], orig[o:o + 4]
                if len(x) == 4 and len(y) == 4 and (a + o) in relocs:
                    wx, wy = int.from_bytes(x, "big"), int.from_bytes(y, "big")
                    op = wx >> 26
                    mask = 0xFC000000 if op in (2, 3) else 0xFFFF0000
                    if wx & mask == wy & mask:
                        # the same instruction: then its target must be
                        # the original's
                        w = check.wrong(a + o, off + o, wy)
                        if not w: continue
                        wrong[o // 4] = w
                elif x == y: continue
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
                        md[o] = md[o].replace("-R", "R")
                        if o < len(od): od[o] = od[o].replace("-R", "R")
                        if o in wrong:
                            md[o] = re.sub(r"\bR\b", lambda _: f"R(wrong: {wrong[o][0]} vs {wrong[o][1]})", md[o], count=1)
                out(f"--- {s}")
                for l in difflib.unified_diff(od, md, "orig", "mine", lineterm="", n=4):
                    out(l)
        return results, secs
    finally:
        shutil.rmtree(tmp)


HI16, LO16, R26 = "R_MIPS_HI16", "R_MIPS_LO16", "R_MIPS_26"


def sext16(x):
    return x - 0x10000 if x & 0x8000 else x


def reloc_targets(text, rlist):
    """{text offset: (symbol, addend, type)} of our .rel.text relocations: the
    addend is in the instruction (REL), a HI16's completed by the next LO16
    of the same symbol, a LO16 by the last HI16 of it before."""
    word = lambda p: int.from_bytes(text[p:p + 4], "big")
    out = {}
    lasthi = {}
    for k, (p, t, sym) in enumerate(rlist):
        if sym is None: continue
        w = word(p)
        if t == R26:
            out[p] = (sym, (w & 0x3FFFFFF) << 2, t)
        elif t == HI16:
            lo = next((q for q, tt, ss in rlist[k + 1:] if tt == LO16 and ss == sym), None)
            out[p] = (sym, ((w & 0xFFFF) << 16) + (sext16(word(lo) & 0xFFFF) if lo is not None else 0), t)
            lasthi[sym] = w & 0xFFFF
        elif t == LO16:
            out[p] = (sym, (lasthi.get(sym, 0) << 16) + sext16(w & 0xFFFF), t)
    return out


class RelocCheck:
    """Whether a relocated word of ours, linked where the original is,
    would get the original's bits: our symbol plus addend resolved to a
    VRAM of the extracted version, its field compared with the original
    word's.

    - A named symbol (extern, common, global): its asm label (eu and jp
      carry us's names), else the linked build's map, else a name of the
      address form placed from the nearest label below with the same
      prefix.
    - .text (a static function, a `j` within the file): IDO's .mdebug names
      the procedure at that offset; its label if the asm has one, else the
      place in the original that lines up with ours (the function run that
      holds it).
    - .rodata/.data/.bss (statics, literals, jump tables): an .mdebug static
      at that offset whose name the asm labels, else the section's base in
      the original, the one most of the evidence agrees on: our named
      symbols of that section with an asm label, and each of our
      references to the section against the asm's operand at that word.
    Branches are PC-relative (no relocation), so local labels need nothing.
    A target that can't be resolved isn't counted."""

    def __init__(self, root, obj, idx, targets, code, cfile):
        self.refs, self.labels, objsecs = load_refs(root)
        # the C file's object in the linked build, if it is one
        m = re.search(r"(?:^|/)(?:src|nonmatching)/(.*)$", os.path.abspath(cfile))
        self.objsec = objsecs.get("src/" + m.group(1), {}) if m else {}
        self.idx, self.targets, self.code = idx, targets, code
        self.procs = {}
        self.statics = {}
        secname = {1: ".text", 2: ".data", 3: ".bss", 15: ".rodata", 13: ".sdata", 14: ".sbss"}
        for st, sc, value, n in mdebug_syms(obj):
            if st in (6, 14): self.procs.setdefault(value, n)
            elif st == 2 and sc in secname: self.statics.setdefault((secname[sc], value), n)
        self.defs = []
        res = subprocess.run(["mips-linux-gnu-readelf", "-sW", obj], capture_output=True, text=True).stdout
        shn = {}
        for line in subprocess.run(["mips-linux-gnu-readelf", "-SW", obj], capture_output=True, text=True).stdout.splitlines():
            m = re.match(r"\s*\[\s*(\d+)\]\s+(\S+)", line)
            if m: shn[m.group(1)] = m.group(2)
        for line in res.splitlines():
            p = line.split()
            if len(p) == 8 and p[3] == "OBJECT" and p[6] in shn:
                self.defs.append((shn[p[6]], int(p[1], 16), p[7]))
        self.defsec = {n: (sec, value) for sec, value, n in self.defs}
        self.cache = {}
        self.base = {}

    def vram(self, name):
        if name not in self.cache:
            self.cache[name] = label_vram(name, self.labels)
        return self.cache[name]

    def runs(self, runs):
        """Our function runs (start, end, name), each lined up with the
        original's function of that name; then the sections' bases."""
        self.run = runs
        # image offset to VRAM, from a function of ours the asm labels (one
        # object's text is contiguous in both)
        self.delta = next((self.labels[s] - self.idx[s][0] for _, _, s in runs if s in self.labels), None)
        from collections import Counter
        votes = {}
        for sec, v in self.objsec.items():
            votes.setdefault(sec, Counter())[v] += 1000
        for sec, value, n in self.defs:
            v = self.labels.get(n)
            if v is not None: votes.setdefault(sec, Counter())[v - value] += 2
        for (sec, value), n in self.statics.items():
            v = self.labels.get(n)
            if v is not None: votes.setdefault(sec, Counter())[v - value] += 2
        for p, (sym, add, _) in self.targets.items():
            if not sym.startswith(".") or sym == ".text": continue
            q = self.orig_offset(p)
            e = self.refs.get(q) if q is not None else None
            if e is None: continue
            n, d = split_expr(e)
            v = self.vram(n)
            if v is not None: votes.setdefault(sym, Counter())[v + d - add] += 1
        self.base = {sec: c.most_common(1)[0][0] for sec, c in votes.items()}

    def orig_offset(self, p):
        """The original's image offset that lines up with our text offset p
        (before our first named function: back from it)"""
        for k, (a, end, s) in enumerate(self.run):
            if a <= p < end or (k == 0 and 0 <= p < a):
                return self.idx[s][0] + p - a
        return None

    def ours(self, p):
        """(VRAM or None, how to show it)"""
        sym, add, _ = self.targets[p]
        if sym == ".text":
            n = self.procs.get(add)
            if n and self.vram(n) is not None and n in self.labels:
                return self.labels[n], n
            q = self.orig_offset(add)
            if q is not None and self.delta is not None:
                return q + self.delta, n or f".text + 0x{add:X}"
            return None, n or f".text + 0x{add:X}"
        if sym.startswith("."):
            n = self.statics.get((sym, add))
            if n and n in self.labels:
                return self.labels[n], n
            if sym in self.base:
                return self.base[sym] + add, n or f"{sym} + 0x{add:X}"
            return None, n or f"{sym} + 0x{add:X}"
        v = self.vram(sym)
        if v is None and sym in self.defsec and self.defsec[sym][0] in self.base:
            v = self.base[self.defsec[sym][0]] + self.defsec[sym][1]
        show = sym + (f" + 0x{add:X}" if add > 0 else f" - 0x{-add:X}" if add < 0 else "")
        return (None if v is None else v + add), show

    def wrong(self, p, q, wy):
        """None if our word at text offset p gets the original's bits at
        image offset q (word wy) once linked, else (ours, original) to show"""
        if p not in self.targets: return None
        typ = self.targets[p][2]
        v, show = self.ours(p)
        if v is None: return None
        if typ == R26:
            mask, field = 0x3FFFFFF, (v >> 2) & 0x3FFFFFF
        elif typ == HI16:
            mask, field = 0xFFFF, ((v + 0x8000) >> 16) & 0xFFFF
        elif typ == LO16:
            mask, field = 0xFFFF, v & 0xFFFF
        else:
            return None
        if field == wy & mask: return None
        return show, self.refs.get(q, f"0x{wy & mask:X}")


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
