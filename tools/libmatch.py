#!/usr/bin/env python3
"""Find libultra functions in the game's code modules.

Compares every function in a set of reference IDO objects (a built
decompals/ultralib tree) against the code image's modules (boot_code,
main_code and every overlay, as bm64.<version>.yaml cuts them; the image
is made from baserom.<version>.z64), with the
immediate fields that relocations fill in masked out.  A function that
matches at exactly one place is named.  The relocations of a matched
function then name what it calls and the globals it touches, which also
catches library functions whose own body differs from the references.

Functions no reference matches exactly can still be placed by similarity
(--fuzzy), for a revision that differs from every ultralib build by a few
instructions.

Adapted from Blast Corps' tools/libmatch.py (../BlastCorps); only the
module loading differs.

Usage:
  libmatch.py <version> <objdir> [<objdir> ...]    # e.g. build/ultralib/build/I/libultra_rom
  libmatch.py <version> --scan <objdir> ...        # exact matches per objdir, to pick a revision

Prints every name with its evidence; ambiguities and conflicts go to stderr.
tools/gen_symbols.py turns the result into the symbol_addrs files, and
tools/build_ultralib.sh builds the reference objects.
"""
import argparse
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
sys.path.insert(0, str(HERE))
import layout  # noqa: E402


def code_image(version):
    """The code image (docs/LAYOUT.md, "Stage 2"), made from the baserom, so
    that this doesn't depend on which version is extracted."""
    return layout.image((ROOT / f"baserom.{version}.z64").read_bytes())

R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16 = 2, 4, 5, 6


# ---------------------------------------------------------------------------
# Minimal ELF32 big-endian reader: just enough for IDO relocatable objects.

class Obj:
    def __init__(self, path):
        self.path = path
        data = path.read_bytes()
        shoff, = struct.unpack_from(">I", data, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from(">HHH", data, 0x2E)
        secs = []
        for i in range(shnum):
            name, typ, flags, addr, off, size, link, info, align, entsize = \
                struct.unpack_from(">10I", data, shoff + i * shentsize)
            secs.append(dict(name=name, type=typ, off=off, size=size, link=link, info=info))
        shstr = secs[shstrndx]
        for s in secs:
            s["name"] = self._str(data, shstr["off"] + s["name"])
        self.secs = secs

        self.syms = []
        for s in secs:
            if s["type"] == 2:  # SHT_SYMTAB
                strtab = secs[s["link"]]
                for j in range(s["size"] // 16):
                    nm, val, sz, info, other, shndx = struct.unpack_from(">IIIBBH", data, s["off"] + j * 16)
                    self.syms.append(dict(name=self._str(data, strtab["off"] + nm), value=val, size=sz,
                                          type=info & 0xF, bind=info >> 4, shndx=shndx))

        self.text_idx = next((i for i, s in enumerate(secs) if s["name"] == ".text"), None)
        self.text = b""
        self.relocs = []
        if self.text_idx is not None:
            t = secs[self.text_idx]
            self.text = data[t["off"]:t["off"] + t["size"]]
            for s in secs:
                if s["type"] == 9 and s["info"] == self.text_idx:  # SHT_REL for .text
                    for j in range(s["size"] // 8):
                        off, info = struct.unpack_from(">II", data, s["off"] + j * 8)
                        self.relocs.append((off, info & 0xFF, info >> 8))

    @staticmethod
    def _str(data, off):
        return data[off:data.index(b"\0", off)].decode()

    def sym_name(self, idx):
        s = self.syms[idx]
        if s["type"] == 3:  # STT_SECTION
            return None, self.secs[s["shndx"]]["name"]
        return s["name"], None

    def local_at(self, secname, offset):
        """Name of a symbol defined at `offset` in section `secname`, if any."""
        for s in self.syms:
            if s["type"] in (1, 2) and s["name"] and s["shndx"] < len(self.secs) \
                    and self.secs[s["shndx"]]["name"] == secname and s["value"] == offset:
                return s["name"], s["type"] == 2
        return None, False

    def functions(self):
        """(name, start, end, is_global) for every function in .text."""
        if not self.text:
            return []
        fs = sorted({(s["value"], s["name"], s["bind"]) for s in self.syms
                     if s["shndx"] == self.text_idx and s["type"] == 2 and s["name"]})
        out = []
        for i, (val, name, bind) in enumerate(fs):
            end = fs[i + 1][0] if i + 1 < len(fs) else len(self.text)
            # Section padding is not part of the last function.
            while end - 4 > val and self.text[end - 4:end] == b"\0\0\0\0" and i + 1 == len(fs):
                end -= 4
            out.append((name, val, end, bind == 1))
        return out


# ---------------------------------------------------------------------------

def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


def code_segments(version):
    """[(name, start, text_end, vram)] for every code segment of the image
    except zerojump (handwritten, no library)."""
    import yaml
    cfg = yaml.safe_load((ROOT / f"bm64.{version}.yaml").read_text())
    out = []
    for seg in cfg["segments"]:
        if not isinstance(seg, dict) or seg.get("type") != "code" or seg["name"] == "zerojump":
            continue
        subs = seg["subsegments"]
        # text ends at the first data subsegment
        end = next(s[0] for s in subs if isinstance(s, list) and s[1].lstrip(".") in ("rodata", "data"))
        out.append((seg["name"], seg["start"], end, seg["vram"]))
    return out


class Signature:
    def __init__(self, obj, name, start, end, is_global):
        self.obj, self.name, self.start, self.end, self.is_global = obj, name, start, end, is_global
        n = (end - start) // 4
        self.words = list(struct.unpack_from(f">{n}I", obj.text, start))
        self.masks = [0xFFFFFFFF] * n
        self.relocs = []  # (word index, type, symidx)
        for off, typ, symidx in obj.relocs:
            if start <= off < end:
                i = (off - start) // 4
                self.masks[i] = 0xFC000000 if typ == R_MIPS_26 else 0xFFFF0000
                self.relocs.append((i, typ, symidx))
        self.relocs.sort()
        # Anchor on the fixed word that is rarest in practice; prologues and
        # nops are everywhere, so prefer something later in the body.
        full = [i for i, m in enumerate(self.masks) if m == 0xFFFFFFFF and self.words[i] not in (0, 0x03E00008)]
        self.anchor = full[len(full) // 2] if full else None

    def __len__(self):
        return len(self.words)


def find(sig, words, index):
    hits = []
    if sig.anchor is None:
        cands = range(len(words) - len(sig) + 1)
    else:
        cands = (p - sig.anchor for p in index.get(sig.words[sig.anchor], ()))
    n = len(sig)
    for base in cands:
        if base < 0 or base + n > len(words):
            continue
        for i in range(n):
            if (words[base + i] ^ sig.words[i]) & sig.masks[i]:
                break
        else:
            hits.append(base)
    return hits


class Module:
    """Name assignment for one separately linked module."""

    def __init__(self, name, vram, words):
        self.name, self.vram, self.words = name, vram, words
        self.index = defaultdict(list)
        for i, w in enumerate(words):
            self.index[w].append(i)
        # name -> {addr: [(sig, base, how)]}
        self.cands = defaultdict(lambda: defaultdict(list))
        self.func_at = {}   # addr -> name
        self.func_addr = {}  # name -> addr
        self.data_at = defaultdict(set)
        self.data_addr = defaultdict(set)
        self.evidence = defaultdict(set)
        self.conflicts = []

    def addr(self, base):
        return self.vram + 4 * base

    def reloc_targets(self, sig, base):
        """(kind, name, game address) for every named relocation of `sig` placed at `base`."""
        o = sig.obj
        hi = {}
        for i, typ, symidx in sig.relocs:
            gw, ow = self.words[base + i], sig.words[i]
            name, sec = o.sym_name(symidx)
            if typ == R_MIPS_26:
                tgt = (self.addr(base + i) & 0xF0000000) | ((gw & 0x3FFFFFF) << 2)
                if name is None:
                    name, _ = o.local_at(sec, (ow & 0x3FFFFFF) << 2)
                if name:
                    yield "func", name, tgt
            elif typ == R_MIPS_HI16:
                hi[symidx] = (gw & 0xFFFF, ow & 0xFFFF)
            elif typ == R_MIPS_LO16 and symidx in hi:
                ghi, ohi = hi[symidx]
                gaddr = ((ghi << 16) + sext16(gw & 0xFFFF)) & 0xFFFFFFFF
                oaddend = ((ohi << 16) + sext16(ow & 0xFFFF)) & 0xFFFFFFFF
                if name is None:
                    name, isfunc = o.local_at(sec, oaddend)
                    if name:
                        yield ("func" if isfunc else "data"), name, gaddr
                else:
                    yield "data", name, (gaddr - oaddend) & 0xFFFFFFFF

    def consistency(self, sig, base):
        """Relocations agreeing with names already placed, or None on a contradiction."""
        agree = 0
        for kind, name, tgt in self.reloc_targets(sig, base):
            if kind == "func":
                if tgt in self.func_at:
                    if self.func_at[tgt] != name:
                        return None
                    agree += 1
                elif name in self.func_addr and self.func_addr[name] != tgt:
                    return None
            else:
                if self.data_at.get(tgt) and name not in self.data_at[tgt]:
                    return None
                if name in self.data_at.get(tgt, ()):
                    agree += 1
        return agree

    def place(self, name, addr, why):
        self.func_at[addr] = name
        self.func_addr[name] = addr
        self.evidence[addr].add(why)

    def place_refs(self, sig, base):
        for kind, name, tgt in self.reloc_targets(sig, base):
            if kind == "func":
                cur = self.func_at.get(tgt)
                if cur is None and name not in self.func_addr:
                    self.place(name, tgt, f"called from {sig.name}")
                elif cur == name:
                    self.evidence[tgt].add(f"called from {sig.name}")
                else:
                    self.conflicts.append(f"{tgt:08X}: {sig.name} calls {name}, already {cur}")
            else:
                self.data_at[tgt].add(name)
                self.data_addr[name].add(tgt)
                self.evidence[tgt].add(f"referenced from {sig.name}")

    def rank_at(self, name, addr):
        hits = self.cands[name][addr]
        scores = [x for x in (self.consistency(sig, base) for sig, base, _ in hits) if x is not None]
        if not scores:
            return (False, -1)
        return (any(how == "object" for _, _, how in hits), max(scores))

    def is_func_start(self, base):
        """Whether `base` directly follows a return (and any padding)."""
        # The delay slot may itself be a nop, so try every point in the padding.
        b = base
        while True:
            if b < 2 or self.words[b - 2] in (0x03E00008, 0x42000018):  # jr $ra / eret
                return True
            if self.words[b - 1] != 0:
                return False
            b -= 1

    @staticmethod
    def trivial(sig):
        """Bodies such as `jr $ra; nop` or `jr $ra; li $v0, 0` fit any empty stub."""
        body = [w for w in sig.words if w != 0]
        return len(body) <= 1 or (len(body) == 2 and body[0] == 0x03E00008)

    def resolve(self, min_words):
        placed_sigs = []
        changed = True
        while changed:
            changed = False
            by_addr = defaultdict(set)
            for name, where in self.cands.items():
                if name in self.func_addr:
                    continue
                for addr in where:
                    if addr not in self.func_at:
                        by_addr[addr].add(name)
            for name, where in list(self.cands.items()):
                if name in self.func_addr:
                    continue
                viable = []
                for addr, hits in where.items():
                    if addr in self.func_at:
                        continue
                    scores = [self.consistency(sig, base) for sig, base, _ in hits]
                    scores = [x for x in scores if x is not None]
                    if not scores:
                        continue
                    strong = any(how == "object" for _, _, how in hits) or \
                        max(len(sig) for sig, _, _ in hits) >= min_words
                    obj = any(how == "object" for _, _, how in hits)
                    viable.append((addr, max(scores), strong, hits, obj))
                if not viable:
                    continue
                rank = lambda v: (v[4], v[1])
                best = max(rank(v) for v in viable)
                top = [v for v in viable if rank(v) == best]
                if len(top) != 1:
                    continue
                addr, score, strong, hits, obj = top[0]
                short_ok = len(where) == 1 and self.is_func_start(hits[0][1]) and not self.trivial(hits[0][0])
                if not strong and score == 0 and not short_ok:
                    continue
                # Another name with an identical body wanting this address must
                # have lost on its relocations (or its object layout) first.
                rivals = [n for n in by_addr[addr] if n != name and self.rank_at(n, addr) >= best]
                if rivals:
                    continue
                how = sorted({h for _, _, h in hits})
                self.place(name, addr, f"{'/'.join(how)} match" + (f", {score} refs agree" if score else ""))
                sig, base, _ = hits[0]
                placed_sigs.append((sig, base))
                self.place_refs(sig, base)
                changed = True
        return placed_sigs


def func_starts(m):
    """Plausible function starts: jal targets and whatever follows a return."""
    starts = {0}
    for i, w in enumerate(m.words):
        if w >> 26 == 3:
            t = (((m.vram & 0xF0000000) | ((w & 0x3FFFFFF) << 2)) - m.vram) // 4
            if 0 <= t < len(m.words):
                starts.add(t)
        if w in (0x03E00008, 0x42000018) and i + 2 < len(m.words):
            j = i + 2
            while j < len(m.words) and m.words[j] == 0:
                j += 1
            starts.add(j)
    return sorted(s for s in starts if s < len(m.words))


def fuzzy(m, funcs, threshold, margin=0.05):
    """Place still-missing library functions on the most similar unnamed game function.

    Similarity is difflib's ratio over the instruction words with relocated
    fields masked on both sides, so a few inserted or changed instructions
    (a different libultra revision) still score high."""
    import difflib
    starts = func_starts(m)
    bounds = {s: (starts[i + 1] if i + 1 < len(starts) else len(m.words)) for i, s in enumerate(starts)}
    free = [s for s in starts if m.addr(s) not in m.func_at]
    placed = set(m.func_addr)
    missing = defaultdict(list)
    for sig in funcs:
        if sig.name not in placed and len(sig) >= 16:
            missing[sig.name].append(sig)
    scored = []
    for name, variants in missing.items():
        best = []
        for s in free:
            n = bounds[s] - s
            for sig in variants:
                if not 0.8 * len(sig) <= n <= 1.25 * len(sig):
                    continue
                a = [w & mk for w, mk in zip(sig.words, sig.masks)]
                b = [w & (0xFC000000 if w >> 26 in (2, 3) else 0xFFFF0000 if w >> 26 in (0x0F,) else 0xFFFFFFFF)
                     for w in m.words[s:bounds[s]]]
                a = [w & (0xFC000000 if w >> 26 in (2, 3) else 0xFFFF0000 if w >> 26 in (0x0F,) else 0xFFFFFFFF)
                     for w in a]
                sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
                if sm.real_quick_ratio() < threshold or sm.quick_ratio() < threshold:
                    continue
                r = sm.ratio()
                if r >= threshold:
                    best.append((r, s, sig))
        best.sort(key=lambda x: -x[0])
        if best and (len(best) == 1 or best[0][0] - best[1][0] >= margin):
            scored.append(best[0] + (name,))
    # One name per address, and only when no other name comes close there;
    # identical bodies under different names (alCSP*/alSeqp*) stay unnamed.
    at = defaultdict(list)
    for r, s, sig, name in scored:
        at[s].append((r, sig, name))
    for s, cands in sorted(at.items()):
        cands.sort(key=lambda x: -x[0])
        if len(cands) > 1 and cands[0][0] - cands[1][0] < margin:
            continue
        r, sig, name = cands[0]
        addr = m.addr(s)
        if addr in m.func_at or name in m.func_addr:
            continue
        m.place(name, addr, f"fuzzy match {r:.2f} vs {sig.obj.path.name}")


def load_signatures(objdirs):
    """Per-function signatures, and whole-object ones (functions listed with offsets)."""
    funcs, objs = [], []
    seen = set()
    for d in objdirs:
        for p in sorted(d.rglob("*.o")):
            o = Obj(p)
            fl = o.functions()
            if not fl:
                continue
            for name, s, e, g in fl:
                if e > s:
                    sig = Signature(o, name, s, e, g)
                    key = (name, tuple(sig.words), tuple(sig.masks))
                    if key not in seen:
                        seen.add(key)
                        funcs.append(sig)
            if len(fl) > 1:
                whole = Signature(o, p.name, 0, fl[-1][2], True)
                key = (p.name, tuple(whole.words), tuple(whole.masks))
                if key not in seen:
                    seen.add(key)
                    parts = [Signature(o, n, s, e, g) for n, s, e, g in fl if e > s]
                    objs.append((whole, parts))
    return funcs, objs


def resolve_twins(m):
    """Names whose bodies are identical to another name's (libaudio's alSeqp*
    and alCSP* functions, one object each, for the two sequence players) can't
    be told apart by their code.  Each family is linked as a run of objects,
    next to its own player (seqplayer.o, csplayer.o) and to the functions of
    its family that did match uniquely (alSeqpLoop, alCSPGetTempo).  So a name
    goes to the copy whose nearest placed neighbour, among the two families,
    is of its own family."""
    def prefix(name, twin):
        n = 0
        while n < min(len(name), len(twin)) and name[-1 - n] == twin[-1 - n]:
            n += 1
        return name[:len(name) - n]

    changed = True
    while changed:
        changed = False
        for name, where in list(m.cands.items()):
            if name in m.func_addr or len(where) < 2 or any(a in m.func_at for a in where):
                continue
            twins = {n for n, w in m.cands.items() if n != name and n not in m.func_addr and set(w) == set(where)}
            if len(twins) != 1:
                continue
            (twin,) = twins
            mine, theirs = prefix(name, twin), prefix(twin, name)
            if not mine or not theirs:
                continue
            placed = sorted((a, n) for a, n in m.func_at.items()
                            if n.startswith(mine) or n.startswith(theirs))

            def family(addr):
                near = min(placed, key=lambda x: abs(x[0] - addr), default=None)
                return bool(near) and near[1].startswith(mine) and not near[1].startswith(theirs)
            good = [a for a in where if family(a)]
            if len(good) != 1:
                continue
            addr = good[0]
            sig, base, _ = where[addr][0]
            m.place(name, addr, f"body match, twin of {twin}, among {mine}* functions")
            m.place_refs(sig, base)
            if len(where) == 2:
                (other,) = set(where) - {addr}
                sig, base, _ = m.cands[twin][other][0]
                m.place(twin, other, f"body match, twin of {name}, among {theirs}* functions")
                m.place_refs(sig, base)
            changed = True


def object_bounds(m, funcs, whole_hits):
    """{addr: "start <object>" | "end <object>"}: where matched library objects
    begin and end in the module.  A whole-object match gives both ends; a
    placed function that begins its object in every reference gives the start,
    and the end too when its body matched and it is the object's only
    function (IDO pads each object's .text to 16 bytes)."""
    out = {}

    def objname(o):
        return o.path.as_posix().split("/libultra_rom/", 1)[-1]

    for whole, parts, base in whole_hits:
        if all(m.func_at.get(m.addr(base + sig.start // 4)) == sig.name for sig in parts):
            a = m.addr(base)
            out.setdefault(a, f"start {objname(whole.obj)}")
            out.setdefault(a + len(whole.obj.text), f"end {objname(whole.obj)}")
    starts = defaultdict(set)
    for sig in funcs:
        starts[sig.name].add(sig.start)
    for addr, name in m.func_at.items():
        if starts.get(name) != {0} or addr % 16:
            continue
        hits = [sig for sig, b, how in m.cands.get(name, {}).get(addr, ())]
        sig = hits[0] if hits else next(s for s in funcs if s.name == name)
        out.setdefault(addr, f"start {objname(sig.obj)}")
        if hits and len(sig.obj.functions()) == 1:
            out.setdefault(addr + len(sig.obj.text), f"end {objname(sig.obj)}")
    return out


def match_version(version, objdirs, min_words=6, fuzzy_ratio=0.85):
    """{module: [(addr, name, kind, evidence)]}, {module: object_bounds()}
    and a list of diagnostics."""
    funcs, objs = load_signatures(objdirs)
    result, bounds, notes = {}, {}, []
    image = code_image(version)
    for seg in code_segments(version):
        mname, start, end, vram = seg
        blob = image[start:end]
        words = list(struct.unpack(f">{len(blob) // 4}I", blob))
        m = Module(mname, vram, words)
        whole_hits = []
        for whole, parts in objs:
            for base in find(whole, words, m.index):
                whole_hits.append((whole, parts, base))
                for sig in parts:
                    b = base + sig.start // 4
                    m.cands[sig.name][m.addr(b)].append((sig, b, "object"))
        for sig in funcs:
            for base in find(sig, words, m.index):
                m.cands[sig.name][m.addr(base)].append((sig, base, "body"))
        m.resolve(min_words)
        if m.func_at:
            resolve_twins(m)
            m.resolve(min_words)
        # Similarity only where the library is: a module with no exact match
        # has none of it (the overlays are the game's own code).
        if fuzzy_ratio and m.func_at:
            fuzzy(m, funcs, fuzzy_ratio)

        syms = []
        for addr in sorted(set(m.func_at) | set(m.data_at)):
            if addr in m.func_at:
                name, kind = m.func_at[addr], "func"
            else:
                names = m.data_at[addr]
                if len(names) > 1 or any(len(m.data_addr[n]) > 1 for n in names):
                    m.conflicts.append(f"{addr:08X}: data {sorted(names)}")
                    continue
                (name,), kind = names, "data"
            syms.append((addr, name, kind, sorted(m.evidence[addr])))
        result[mname] = syms
        bounds[mname] = object_bounds(m, funcs, whole_hits)
        notes += [f"{mname} CONFLICT {c}" for c in m.conflicts]
        for n in sorted(n for n in m.cands if n not in m.func_addr):
            where = " ".join(f"{a:08X}({'/'.join(sorted({h for _, _, h in hs}))},{len(hs[0][0])}w)"
                             for a, hs in sorted(m.cands[n].items()))
            notes.append(f"{mname} unplaced {n}: {where}")
    return result, bounds, notes


def scan(version, objdirs, min_words):
    """Which reference builds each library function's body matches exactly.

    Prints, per function found anywhere, the objdirs (revisions) whose copy
    matches; then per objdir the count.  Where the revisions' bodies differ,
    this picks the revision."""
    image = code_image(version)
    mods = []
    for mname, start, end, vram in code_segments(version):
        words = list(struct.unpack(f">{(end - start) // 4}I", image[start:end]))
        index = defaultdict(list)
        for i, w in enumerate(words):
            index[w].append(i)
        mods.append((mname, vram, words, index))
    found = defaultdict(dict)   # name -> {objdir: [addresses]}
    differs = defaultdict(set)  # name -> distinct bodies across objdirs
    for d in objdirs:
        funcs, _ = load_signatures([d])
        for sig in funcs:
            if len(sig) < min_words or Module.trivial(sig):
                continue
            differs[sig.name].add((tuple(sig.words), tuple(sig.masks)))
            for mname, vram, words, index in mods:
                for base in find(sig, words, index):
                    found[sig.name].setdefault(d.parent.name if d.name.startswith("lib") else d.name, []).append(
                        f"{mname}:{vram + 4 * base:08X}")
    labels = [d.parent.name if d.name.startswith("lib") else d.name for d in objdirs]
    total = defaultdict(int)
    for name in sorted(found):
        hit = found[name]
        for lab in hit:
            total[lab] += 1
        if len(differs[name]) > 1:
            where = sorted({a for v in hit.values() for a in v})
            print(f"{name:32} {''.join(l if l in hit else '.' for l in labels):12} {' '.join(where)}")
    print("exact functions per build:", " ".join(f"{l}={total[l]}" for l in labels))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("version")
    ap.add_argument("objdirs", nargs="+", type=Path)
    ap.add_argument("--min-words", type=int, default=6,
                    help="shorter bodies need a whole-object match or agreeing relocations")
    ap.add_argument("--fuzzy", type=float, default=0.85, metavar="RATIO",
                    help="also place unmatched functions on game code at least this similar (0 disables)")
    ap.add_argument("--scan", action="store_true",
                    help="only list which builds each function matches (to pick the revision)")
    args = ap.parse_args()

    if args.scan:
        scan(args.version, args.objdirs, args.min_words)
        return
    result, bounds, notes = match_version(args.version, args.objdirs, args.min_words, args.fuzzy)
    for mname, syms in result.items():
        for addr, name, kind, ev in syms:
            print(f"{mname} {addr:08X} {kind:4} {name}: {'; '.join(ev)}")
        for addr, what in sorted(bounds[mname].items()):
            print(f"{mname} {addr:08X} obj  {what}")
    for n in notes:
        print(n, file=sys.stderr)


if __name__ == "__main__":
    main()
