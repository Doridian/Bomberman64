#!/usr/bin/env python3
"""Where each us address is in eu and jp, and the names that follow.

us is the reference version: its names (`func_80225840`,
`func_ovl09_01_8004316C`, `D_8001A07C`: the address of the thing in us) are
the names of the same things in
eu and jp, so one C source compiles for all three (docs/ROADMAP.md, phase
4).  This tool works out the correspondence from two ROMs alone (it needs
baserom.us.z64 and the other version's ROM, not the tree), writes it to
vermap.<version>.txt (generated, committed), and renames what `make
extract` leaves for that version with it.  Each version is mapped from us
on its own.

How:

1. Each module (boot_code, zerojump, main_code, and every overlay: bank and
   entry numbers are the same in every ROM) is cut into functions (a start
   after every return that no branch or jump table crosses, and every jal
   target).  The two lists are aligned on the functions' bodies with the
   linker-filled fields masked (jal targets, lui/lo immediates): in order
   first (difflib), then what is left by identical body in any order (an
   object can sit elsewhere in the link order), then by similarity.  A pair
   is "identical" (same masked body) or "changed".  Words are aligned inside
   changed functions.
2. Every jal and every lui/lo pair in aligned code gives a (us address,
   other version's address) pair.  The pairs most code agrees on are anchors, rising in
   both versions.  Between two anchors the same distance apart in both the
   range maps as a whole; elsewhere only the anchors, and what the aligned
   code and the words of aligned data (pointers compared through the map)
   add.  Overlay-local addresses (0x80043000 and up, inside an overlay) are
   per overlay; all others are one space.

The naming rule: in us nothing changes.  In eu (jp), a function or datum
that sits where us has X is named for X, and one with no us counterpart
keeps its own address with `_eu` (`_jp`) appended
(`func_ovl09_01_80043A00_jp`).  Names given in symbol_addrs.us.txt carry
over to the other version's address.  The renaming works on splat's output
(after postsplit.py), every func_/D_/jtbl_/L token at once, so no name can
clash with a us name at another address.

Usage:
  vermap.py [V...]             write vermap.<V>.txt (default: eu and jp; needs
                               us's ROM and V's)
  vermap.py --check [V...]     fail if vermap.<V>.txt differs from what the ROMs give
  vermap.py --report [V...]    per-module alignment statistics
  vermap.py --functions M [V]  every function and how it aligned (one module, or all)
  vermap.py --rename V         rename the symbols in asm/ and the *_auto.txt
                               files to us's (make extract does this; needs
                               only vermap.<V>.txt)
"""
import argparse
import bisect
import collections
import difflib
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import layout  # noqa: E402

REF = "us"
TARGETS = ("eu", "jp")
LO_OPS = layout.LO_OPS
OVL_LO = layout.OVERLAY_VRAM


def map_file(tgt):
    return ROOT / f"vermap.{tgt}.txt"

# ---------------------------------------------------------------------------
# The modules of a ROM

class Module:
    """One code module of a version: its image, text, and bss."""

    def __init__(self, name, vram, blob, bss, rom):
        self.name, self.vram, self.blob, self.bss, self.rom = name, vram, blob, bss, rom
        self.text_end, self.stubs = layout.text_split(blob)
        self.words = [layout.u32(blob, o) for o in range(0, len(blob) - 3, 4)]
        self.overlay = name.startswith("ovl_")
        self.end = vram + len(blob)          # end of the image
        self.extent = self.end + bss         # end with bss
        self.tag = name[4:] if self.overlay else ""   # "09_01"

    def contains(self, a):
        return self.vram <= a < self.extent

    def local(self, a):
        """Is a an address only this module has (an overlay's own)?"""
        return self.overlay and self.contains(a)

    def sym(self, kind, a, suffix=""):
        mid = f"ovl{self.tag}_" if self.overlay else ""
        return f"{kind}_{mid}{a:08X}{suffix}"


def load_modules(version):
    d = (ROOT / f"baserom.{version}.z64").read_bytes()
    segs, boot_bss = layout.fixed(d)
    starts = {n: s for s, n, _ in segs}
    mods = {}
    boot_end = starts["zerojump"]
    mods["boot_code"] = Module("boot_code", layout.BOOT_VRAM, d[starts["boot_code"]:boot_end],
                               boot_bss, starts["boot_code"])
    # zerojump's range is what boot_code's entry DMAs
    mods["zerojump"] = Module("zerojump", layout.ZEROJUMP_VRAM,
                              d[boot_end:starts["pad_zerojump"]], 0, boot_end)
    main_end = starts["pad_main_code"]
    mods["main_code"] = Module("main_code", layout.MAIN_VRAM, d[0x40000:main_end],
                               layout.main_bss(d, main_end), 0x40000)
    pos = layout.FIRST_BANK
    for bank, entry, data in layout.overlays(d):
        name = layout.overlay_name(bank, entry)
        bss = layout.bss_size(data, OVL_LO, layout.OVERLAY_SPACE)
        mods[name] = Module(name, OVL_LO, data, bss, pos)
        pos += len(data)
    return mods


# ---------------------------------------------------------------------------
# Instructions

def mask(w):
    """w without its linker-filled fields."""
    op = w >> 26
    if op in (2, 3):
        return w & 0xFC000000
    if op == 0x0F or op in LO_OPS:
        return w & 0xFFFF0000
    return w


def shape(w):
    """w without registers and filled fields: a changed function's registers
    are renumbered."""
    op = w >> 26
    if op == 0:
        return (0, w & 0x3F, (w >> 6) & 31)
    if op in (2, 3, 0x0F) or op in LO_OPS:
        return (op,)
    if op == 1:
        return (1, (w >> 16) & 31)
    if op == 0x11:
        return (0x11, (w >> 21) & 31, w & 0x3F)
    return (op, w & 0xFFFF)


def writes(w):
    """The integer register an instruction writes, or None."""
    op = w >> 26
    if op == 0:
        return (w >> 11) & 31
    if op == 3:
        return 31
    if 0x08 <= op <= 0x0F or op in (0x18, 0x19, 0x1A, 0x1B, 0x20, 0x21, 0x22, 0x23,
                                    0x24, 0x25, 0x26, 0x27, 0x37):
        return (w >> 16) & 31
    if op == 0x11 and (w >> 21) & 31 in (0, 1, 2):  # mfc1, dmfc1, cfc1
        return (w >> 16) & 31
    return None


def lo_pairs(words):
    """{index of a lo instruction: (index of its lui, address)}: the loads,
    stores and addius based on a lui's register until something writes it."""
    out = {}
    for i, w in enumerate(words):
        if w >> 26 != 0x0F:
            continue
        reg, hi = (w >> 16) & 31, w & 0xFFFF
        if reg == 0:
            continue
        for j in range(i + 1, min(i + 32, len(words))):
            x = words[j]
            if x >> 26 in LO_OPS and (x >> 21) & 31 == reg:
                lo = x & 0xFFFF
                out[j] = (i, ((hi << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF)
            if x >> 26 == 0 and x & 0x3F in (0x21, 0x2D) and (x >> 11) & 31 == reg \
                    and reg in ((x >> 21) & 31, (x >> 16) & 31):
                continue  # addu reg, reg, index: still the address's base
            if writes(x) == reg or x == 0x03E00008 or x >> 26 == 2:
                break
    return out


def branch_target(w, i):
    """Word index a pc-relative branch at index i goes to, or None."""
    op = w >> 26
    if op in layout.BRANCH_OPS or op == 1 or (op == 0x11 and (w >> 21) & 31 == 8):
        imm = w & 0xFFFF
        return i + 1 + (imm - 0x10000 if imm & 0x8000 else imm)
    return None


def jump_target(m, w):
    return (m.vram & 0xF0000000) | ((w & 0x3FFFFFF) << 2)


# ---------------------------------------------------------------------------
# Functions

class Func:
    def __init__(self, m, s, e, stub=False):
        self.m, self.s, self.e, self.stub = m, s, e, stub
        # a ZeroJump stub is known by its id (`li $t0, id`), which is no
        # linker-filled field
        self.tok = tuple(m.words[s:e]) if stub else tuple(mask(w) for w in m.words[s:e])

    @property
    def addr(self):
        return self.m.vram + 4 * self.s

    @property
    def size(self):
        return self.e - self.s


def data_groups(m, lo):
    """[(first word index, [text word indexes it points to])]: runs of words
    in the module's data that all point into its text (jump tables)."""
    out = []
    n = len(m.words)
    i = m.text_end // 4
    while i < n:
        t = m.words[i]
        if m.vram <= t < m.vram + m.text_end and t % 4 == 0:
            j, tg = i, []
            while j < n and m.vram <= m.words[j] < m.vram + m.text_end and m.words[j] % 4 == 0:
                tg.append((m.words[j] - m.vram) // 4)
                j += 1
            out.append((i, tg))
            i = j
        else:
            i += 1
    return out


def functions(m):
    """The functions of a module's text, in order, and the jump tables as
    {data address: text word indexes}."""
    w, n = m.words, m.text_end // 4
    starts = {0}
    starts_hard = set()
    stubs = None
    if m.stubs and m.stubs[0] < m.text_end:
        stubs = (m.stubs[0] & ~15) // 4, ((m.stubs[1] + 15) & ~15) // 4
    for i in range(n):
        x = w[i]
        if x >> 26 == 3:
            t = (jump_target(m, x) - m.vram) // 4
            if 0 <= t < n:
                starts.add(t)
                starts_hard.add(t)
    cand = set()
    for i in range(n):
        if w[i] == 0x03E00008 and i + 2 <= n:
            j = i + 2
            while j < n and w[j] == 0:
                j += 1
            if j < n:
                cand.add(j)
    # a boundary a branch or a jump table jumps across is no boundary
    span = []
    for i in range(n):
        t = branch_target(w[i], i)
        if t is not None:
            span.append((min(i, t), max(i, t)))
    lo = lo_pairs(w)
    luis = collections.defaultdict(list)
    for j, (i, a) in lo.items():
        luis[a].append(i)
    tables = {}
    for at, tg in data_groups(m, 0):
        addr = m.vram + 4 * at
        tables[addr] = tg
        for i in luis.get(addr, []):
            span.append((min(i, min(tg)), max(tg)))
        if addr not in luis:
            span.append((min(tg), max(tg)))
    span.sort()
    keep = set()
    for c in sorted(cand):
        # any span with lo < c <= hi?
        k = bisect.bisect_left(span, (c, -1))
        crossed = any(hi >= c for lo_, hi in span[:k] if lo_ < c)
        if not crossed or c in starts_hard:
            keep.add(c)
    starts |= keep
    if stubs:
        # each stub of the block is aligned on its own: versions add and
        # drop entries (jp's main_code has 4 fewer)
        starts = {s for s in starts if not stubs[0] <= s < stubs[1]} | {stubs[0]}
        starts |= set(range(m.stubs[0] // 4, m.stubs[1] // 4, 2))
        if stubs[1] < n:
            starts.add(stubs[1])
    starts = sorted(s for s in starts if s < n)
    out = []
    for k, s in enumerate(starts):
        e = starts[k + 1] if k + 1 < len(starts) else n
        out.append(Func(m, s, e, stub=bool(stubs and stubs[0] <= s < stubs[1])))
    return out, tables


# ---------------------------------------------------------------------------
# Aligning functions

def similar(a, b):
    """How alike two masked bodies are, 0..1, by shape."""
    sa, sb = [shape(x) for x in a.tok], [shape(x) for x in b.tok]
    return difflib.SequenceMatcher(None, sa, sb, autojunk=False).ratio()


def align_functions(rf, tf):
    """{index in rf: index in tf} (exact masked bodies first, in order, then
    in any order), and {index: index} for the changed pairs."""
    rt, tt = [f.tok for f in rf], [f.tok for f in tf]
    exact = {}
    sm = difflib.SequenceMatcher(None, rt, tt, autojunk=False)
    # tiny functions (an empty `jr ra`) match anywhere: only keep them where
    # the code around them is in order too
    blocks = [b for b in sm.get_matching_blocks() if b.size]
    sz = lambda b: sum(rf[b.a + k].size for k in range(b.size))
    delta = lambda b: tf[b.b].s - rf[b.a].s
    big = [b for b in blocks if sz(b) >= 16]
    for b in blocks:
        if sz(b) < 16:
            before = [x for x in big if x.a < b.a]
            after = [x for x in big if x.a > b.a]
            near = ([delta(before[-1])] if before else []) + ([delta(after[0])] if after else [])
            if delta(b) not in near:
                continue
        for k in range(b.size):
            exact[b.a + k] = b.b + k
    # the rest by identical body, anywhere, where the body is unique on
    # both sides (or paired in order among equal ones)
    used = set(exact.values())
    byb = collections.defaultdict(list)
    for j, f in enumerate(tf):
        if j not in used and f.size >= 6:
            byb[f.tok].append(j)
    for i, f in enumerate(rf):
        if i not in exact and f.size >= 6 and byb.get(f.tok):
            exact[i] = byb[f.tok].pop(0)
    # similar ones in the gaps between exact pairs, in order
    changed = {}
    pts = [(-1, -1)] + sorted(exact.items()) + [(len(rf), len(tf))]
    for (a1, b1), (a2, b2) in zip(pts, pts[1:]):
        if b2 < b1:
            continue
        ra = [i for i in range(a1 + 1, a2) if i not in exact]
        ta = [j for j in range(b1 + 1, b2) if j not in exact and j not in set(exact.values())]
        if not ra or not ta:
            continue
        # greedy in order: best ratio for each us function among the later
        # eu ones
        pos = 0
        for i in ra:
            best, bj = 0.0, None
            for k in range(pos, len(ta)):
                f, g = rf[i], tf[ta[k]]
                if min(f.size, g.size) * 3 < max(f.size, g.size):
                    continue
                r = similar(f, g)
                if r > best:
                    best, bj = r, k
            if bj is not None and best >= 0.5:
                changed[i] = ta[bj]
                pos = bj + 1
    return exact, changed


def word_pairs(rm, tm, rf, tf, exact, changed):
    """{us word index: eu word index} over the aligned functions."""
    pairs = {}
    for i, j in exact.items():
        for k in range(rf[i].size):
            pairs[rf[i].s + k] = tf[j].s + k
    for i, j in changed.items():
        f, g = rf[i], tf[j]
        # a changed function is the same function: its start is its name
        pairs[f.s] = g.s
        for key in (mask, shape):
            ra = [key(x) for x in rm.words[f.s:f.e]]
            ta = [key(x) for x in tm.words[g.s:g.e]]
            sm = difflib.SequenceMatcher(None, ra, ta, autojunk=False)
            for b in sm.get_matching_blocks():
                if b.size >= (4 if key is mask else 6):
                    for k in range(b.size):
                        pairs.setdefault(f.s + b.a + k, g.s + b.b + k)
    return pairs


# ---------------------------------------------------------------------------
# The map

class VerMap:
    """{module: ranges (us start, us end, eu start)} of us addresses, as
    sorted lists, and each module's extent {module: (vram, us end, eu end)},
    bss included.  An address is looked up in its module (overlays share
    0x80043000, so a module is needed); the fixed modules are one space."""

    def __init__(self, ranges, ext):
        self.ext = ext
        self.ranges = {m: sorted(r) for m, r in ranges.items()}
        self.rs = {m: [r[0] for r in rs] for m, rs in self.ranges.items()}
        inv = {m: sorted((t, t + e - s, s) for s, e, t in rs) for m, rs in self.ranges.items()}
        self.inv = inv
        self.ts = {m: [r[0] for r in rs] for m, rs in inv.items()}

    def to_tgt(self, mod, a):
        rs = self.ranges.get(mod, ())
        i = bisect.bisect_right(self.rs.get(mod, ()), a) - 1
        if i >= 0 and rs[i][0] <= a < rs[i][1]:
            return rs[i][2] + (a - rs[i][0])
        return None

    def to_ref(self, mod, x):
        rs = self.inv.get(mod, ())
        i = bisect.bisect_right(self.ts.get(mod, ()), x) - 1
        if i >= 0 and rs[i][0] <= x < rs[i][1]:
            return rs[i][2] + (x - rs[i][0])
        return None

    def owner(self, a, side, module=None):
        """The module an address is in: `module` if it is an overlay's own,
        else a fixed one.  side: 1 for us's addresses, 2 for eu's."""
        if module and module.startswith("ovl_") and module in self.ext:
            v, *ends = self.ext[module]
            if v <= a <= ends[side - 1]:
                return module
        for name, (v, *ends) in self.ext.items():
            if not name.startswith("ovl_") and v <= a <= ends[side - 1]:
                return name
        return None


def runs(pairs):
    out = []
    for a in sorted(pairs):
        b = pairs[a]
        if out and out[-1][1] == a and out[-1][2] + (a - out[-1][0]) == b:
            out[-1][1] = a + 1
        else:
            out.append([a, a + 1, b])
    return [tuple(r) for r in out]


def anchors(pairs, lo, hi):
    """The (us, eu) pairs in [lo, hi) that most references agree on, kept
    where the distance is a neighbour's or the eu address lies between the
    neighbours' (a lone one out of place is a coincidence)."""
    votes = collections.defaultdict(collections.Counter)
    for a, b in pairs:
        if lo <= a < hi:
            votes[a][b] += 1
    best = {a: c.most_common(1)[0][0] for a, c in votes.items()}
    by_t = collections.defaultdict(list)
    for a, b in best.items():
        by_t[b].append(a)
    pts = sorted((a, b) for a, b in best.items() if len(by_t[b]) == 1)
    while True:
        keep = []
        for k, (a, b) in enumerate(pts):
            d = b - a
            prev = pts[k - 1] if k else None
            nxt = pts[k + 1] if k + 1 < len(pts) else None
            if (prev and prev[1] - prev[0] == d) or (nxt and nxt[1] - nxt[0] == d):
                keep.append((a, b))
            elif (prev is None or prev[1] < b) and (nxt is None or b < nxt[1]):
                keep.append((a, b))
        if len(keep) == len(pts):
            return keep
        pts = keep


def fill(anch, lo, hi, tlo, thi, compare=None):
    """Ranges between anchors: whole where the gap is the same size in both
    versions, else the anchors alone (or by compare(us lo, us hi, eu lo, eu
    hi), a list of ranges).  (lo, tlo) and (hi, thi) bound the section."""
    inner = [p for p in anch if lo < p[0] < hi and tlo < p[1] < thi]
    pts = inner
    if not inner or inner[0][1] - inner[0][0] == tlo - lo:
        pts = [(lo, tlo)] + pts
    if not inner or inner[-1][1] - inner[-1][0] == thi - hi:
        pts = pts + [(hi, thi)]
    out = []
    for (a1, b1), (a2, b2) in zip(pts, pts[1:]):
        if a2 - a1 == b2 - b1:
            out.append((a1, a2, b1))
        else:
            out.append((a1, a1 + 1, b1))
            if compare:
                out += compare(a1, a2, b1, b2)
    if pts and pts[-1] not in ((hi, thi),):
        a, b = pts[-1]
        out.append((a, a + 1, b))
    return out


def merge(ranges):
    """Ranges joined where they continue each other; where two overlap (in
    us or in eu) the longer wins."""
    out = []
    for s, e, t in sorted(set(ranges), key=lambda r: (r[0], -(r[1] - r[0]))):
        if out and s < out[-1][1]:
            ps, pe, pt = out[-1]
            if t - s == pt - ps:
                out[-1][1] = max(pe, e)
                continue
            t += pe - s
            s = pe
            if s >= e:
                continue
        if out and out[-1][1] == s and out[-1][2] + (s - out[-1][0]) == t:
            out[-1][1] = e
        else:
            out.append([s, e, t])
    res, taken = [], []
    for s, e, t in sorted(out, key=lambda r: -(r[1] - r[0])):
        te = t + (e - s)
        k = bisect.bisect_left(taken, (t,))
        if not any(x < te and t < y for x, y in taken[max(0, k - 1):k + 2]):
            bisect.insort(taken, (t, te))
            res.append((s, e, t))
    return sorted(res)


class Alignment:
    """Everything found for one module."""

    def __init__(self, rm, tm):
        self.rm, self.tm = rm, tm
        self.rf, self.rtab = functions(rm)
        self.tf, self.ttab = functions(tm)
        self.exact, self.changed = align_functions(self.rf, self.tf)
        self.wp = word_pairs(rm, tm, self.rf, self.tf, self.exact, self.changed)

    def stats(self):
        """Counts over the functions (the ZeroJump stubs are not)."""
        real = lambda fs: [i for i, f in enumerate(fs) if not f.stub]
        rr, tt = set(real(self.rf)), set(real(self.tf))
        ident = len([i for i in self.exact if i in rr])
        chg = len([i for i in self.changed if i in rr])
        return {"ref": len(rr), "tgt": len(tt), "identical": ident, "changed": chg,
                "ref_only": len(rr) - ident - chg,
                "tgt_only": len(tt) - len([j for j in self.exact.values() if j in tt])
                - len([j for j in self.changed.values() if j in tt])}

    def code_pairs(self):
        """(us addr, eu addr) of lui/lo pairs and jals in aligned code."""
        rlo, tlo = lo_pairs(self.rm.words), lo_pairs(self.tm.words)
        out = []
        for i, j in self.wp.items():
            if i in rlo and j in tlo and self.wp.get(rlo[i][0]) == tlo[j][0]:
                out.append((rlo[i][1], tlo[j][1]))
            w, x = self.rm.words[i], self.tm.words[j]
            if w >> 26 == 3 and x >> 26 == 3:
                out.append((jump_target(self.rm, w), jump_target(self.tm, x)))
        return out


def spaces(mods):
    """The module whose range an address is in, for each fixed module;
    overlay-local ones are looked up in the overlay itself."""
    fixed = [m for m in mods.values() if not m.overlay]

    def owner(m, a):
        if m.local(a):
            return m
        for f in fixed:
            if f.contains(a):
                return f
        return None
    return owner


def build(rmods, tmods):
    """(VerMap, {module: Alignment})."""
    al = {name: Alignment(rmods[name], tmods[name]) for name in rmods}
    rown, town = spaces(rmods), spaces(tmods)
    # votes: per owner module
    votes = collections.defaultdict(list)
    for name, a in al.items():
        rm, tm = rmods[name], tmods[name]
        for x, y in a.code_pairs():
            ro, to = rown(rm, x), town(tm, y)
            if ro is not None and to is not None and ro.name == to.name:
                votes[ro.name].append((x, y))
    ranges = {}

    def compare_for(rm, tm):
        def compare(a1, a2, b1, b2):
            norm = lambda w, m: "ptr" if m.contains(w) else w
            def word(m, a):
                o = a - m.vram
                return m.blob[o:o + 4]
            ra = [norm(int.from_bytes(word(rm, a), "big"), rm) for a in range(a1 & ~3, a2 & ~3, 4)
                  if 0 <= a - rm.vram < len(rm.blob) - 3]
            ta = [norm(int.from_bytes(word(tm, b), "big"), tm) for b in range(b1 & ~3, b2 & ~3, 4)
                  if 0 <= b - tm.vram < len(tm.blob) - 3]
            sm = difflib.SequenceMatcher(None, ra, ta, autojunk=False)
            return [((a1 & ~3) + 4 * b.a, (a1 & ~3) + 4 * (b.a + b.size), (b1 & ~3) + 4 * b.b)
                    for b in sm.get_matching_blocks() if b.size >= 4]
        return compare

    for name, rm in rmods.items():
        tm, a = tmods[name], al[name]
        rs = []
        # text: the aligned words
        for s, e, t in runs(a.wp):
            rs.append((rm.vram + 4 * s, rm.vram + 4 * e, tm.vram + 4 * t))
        pts = votes.get(name, [])
        extra = []
        for rnd in range(2):
            cur = list(rs)
            # data
            lo, hi = rm.vram + rm.text_end, rm.end
            tlo, thi = tm.vram + tm.text_end, tm.end
            if hi > lo and thi > tlo:
                an = anchors(pts + extra, lo, hi)
                cur += fill(an, lo, hi, tlo, thi, compare_for(rm, tm))
            # bss
            if rm.bss:
                lo, hi = rm.end, rm.extent
                tlo, thi = tm.end, tm.extent
                an = anchors(pts + extra, lo, hi + 1)
                an = [p for p in an if p[0] < hi]
                cur += fill(an, lo, hi, tlo, thi, None)
            # the end of a section is referenced like any address
            cur = merge(cur)
            m = VerMap({name: cur}, {})
            extra = []
            for x in range(rm.vram + rm.text_end, rm.end - 3, 4):
                y = m.to_tgt(name, x)
                if y is None or y % 4 or not 0 <= y - tm.vram < len(tm.blob) - 3:
                    continue
                v = int.from_bytes(rm.blob[x - rm.vram:x - rm.vram + 4], "big")
                u = int.from_bytes(tm.blob[y - tm.vram:y - tm.vram + 4], "big")
                if rown(rm, v) is not None and town(tm, u) is not None:
                    extra.append((v, u))
        # the end of a module (with its bss) is referenced like any address
        ranges[name] = merge(cur + [(rm.extent, rm.extent + 1, tm.extent)])
    # an overlay's map holds only its own addresses; the fixed modules' own
    # are those of the modules (an overlay referring into main_code is a
    # vote for main_code, above)
    for name in list(ranges):
        rm = rmods[name]
        if rm.overlay:
            ranges[name] = [r for r in ranges[name] if rm.contains(r[0])]
    ext = {n: (rmods[n].vram, rmods[n].extent, tmods[n].extent) for n in rmods}
    return VerMap(ranges, ext), al


# ---------------------------------------------------------------------------
# Writing

def write_map(vm, path, tgt):
    lines = [f"# generated by tools/vermap.py: where {REF}'s addresses are in {tgt}.",
             f"# `@ module vram {REF}-end {tgt}-end`: a module's extent (bss included);",
             f"# then `module {REF}-start {REF}-end {tgt}-start` ranges (hex).  An address is",
             "# looked up in its module: an overlay's own, or else a fixed module's."]
    for m, (v, ue, te) in vm.ext.items():
        lines.append(f"@ {m} {v:08X} {ue:08X} {te:08X}")
    for m in vm.ranges:
        for s, e, t in vm.ranges[m]:
            lines.append(f"{m} {s:08X} {e:08X} {t:08X}")
    path.write_text("\n".join(lines) + "\n")


def read_map(path):
    ranges, ext = collections.defaultdict(list), {}
    for line in path.read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        f = line.split()
        if f[0] == "@":
            ext[f[1]] = tuple(int(x, 16) for x in f[2:])
        else:
            ranges[f[0]].append(tuple(int(x, 16) for x in f[1:]))
    return VerMap(ranges, ext)


# ---------------------------------------------------------------------------
# Names

SYMLINE = re.compile(r"^(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")
# the names splat and postsplit make from an address: func_8002A540,
# D_ovl09_01_80044960, jtbl_..., and L80012345 (a code label)
TOKEN = re.compile(r"(?<![\w.])(?:(func|D|jtbl)_|(L))(?:ovl([0-9A-F]{2}_[0-9]{2})_)?"
                   r"([0-9A-F]{8})(?![\w])")


def us_names(vm):
    """{(module, us address): name} from symbol_addrs.us.txt: a symbol is in
    the overlay its name or `segment:` says, else in a fixed module."""
    out = {}
    path = ROOT / f"symbol_addrs.{REF}.txt"
    for line in path.read_text().splitlines() if path.exists() else []:
        m = SYMLINE.match(line.strip())
        if not m:
            continue
        name, addr = m[1], int(m[2], 16)
        seg = re.search(r"segment:(\w+)", line) or re.search(r"\bovl_?([0-9A-F]{2}_\d{2})_", name)
        mod = None
        if seg:
            mod = seg[1] if seg[1].startswith("ovl_") else "ovl_" + seg[1]
        mod = vm.owner(addr, 1, mod)
        if mod:
            out[(mod, addr)] = name
    return out


class Renamer:
    """eu's names (splat's, from eu addresses) to us's: `func_X` where eu
    has what us has at X, the name symbol_addrs.us.txt gives X if it does,
    else `func_Y_eu` for an eu address Y with no us counterpart."""

    def __init__(self, vm, tgt):
        self.vm, self.tgt = vm, tgt
        self.names = us_names(vm)
        self.count = collections.Counter()

    def name(self, m):
        pre, ovl, addr = (m[1] or "L"), m[3], int(m[4], 16)
        mod = self.vm.owner(addr, 2, "ovl_" + ovl if ovl else None)
        if mod is None:
            if self.vm.owner(addr, 1, "ovl_" + ovl if ovl else None):
                return f"{m[0]}_{self.tgt}"   # would read as a us name
            return m[0]     # not in any module: a hardware or fixed address
        us = self.vm.to_ref(mod, addr)
        if us is None:
            self.count[f"{self.tgt} only"] += 1
            return f"{m[0]}_{self.tgt}"
        if (mod, us) in self.names and pre != "L":
            self.count["named"] += 1
            return self.names[(mod, us)]
        self.count["renamed" if us != addr else "same"] += 1
        sep = "_" if pre != "L" else ""
        return f"{pre}{sep}{'ovl' + ovl + '_' if ovl else ''}{us:08X}"

    def text(self, s):
        return TOKEN.sub(self.name, s)


NAME = re.compile(r"^(func|D|jtbl)_(?:ovl([0-9A-F]{2}_[0-9]{2})_)?([0-9A-F]{8})(?:_(\w+))?$")


def version_name(vm, tgt, name):
    """The other way: the name splat gives in `tgt` to what us calls `name`
    (an address name; any other name is the same in every version).
    `func_X_jp` is jp's own X; a us name with no counterpart in `tgt`
    becomes `<name>_us`, which nothing there is called.  tools/split.py
    reads the C files' names through this."""
    m = NAME.match(name)
    if not m:
        return name
    pre, ovl, addr, suffix = m[1], m[2], int(m[3], 16), m[4]
    mid = f"ovl{ovl}_" if ovl else ""
    if suffix == tgt:
        return f"{pre}_{mid}{addr:08X}"
    if suffix:
        return f"{name}_us"     # another version's own: nothing in tgt
    mod = vm.owner(addr, 1, "ovl_" + ovl if ovl else None)
    t = vm.to_tgt(mod, addr) if mod else None
    if t is None:
        return f"{name}_us" if mod else name
    return f"{pre}_{mid}{t:08X}"


def rename_tree(version):
    """Rename every symbol in asm/ and the generated symbol files of
    `version` (what `make extract` leaves) from its addresses to us's.
    Idempotent: a stamp in asm/ says the files were done."""
    if version == REF:
        return
    vm = read_map(map_file(version))
    files = sorted((ROOT / "asm").rglob("*.s")) + [ROOT / f for f in
            ("module_syms_auto.txt", "undefined_syms_auto.txt", "undefined_funcs_auto.txt")
            if (ROOT / f).exists()]
    stamp = ROOT / "asm" / ".vermap"
    if stamp.exists() and all(f.stat().st_mtime <= stamp.stat().st_mtime for f in files):
        print("vermap: names already renamed")
        return
    rn = Renamer(vm, version)
    for f in files:
        t = f.read_text()
        n = rn.text(t)
        if n != t:
            f.write_text(n)
    # the GLOBAL_ASM functions' files are named for them (tools/split.py
    # had splat write them under this version's names); two passes, as a
    # new name can be another file's old one
    moves = []
    for f in (ROOT / "asm").glob("*matchings/**/*.s"):
        new = f.with_name(TOKEN.sub(rn.name, f.stem) + ".s")
        if new != f:
            moves.append((f, new))
    for f, new in moves:
        f.rename(f.with_name(f.name + ".vermap"))
    for f, new in moves:
        f.with_name(f.name + ".vermap").rename(new)
    stamp.write_text("")
    print(f"vermap: {version}'s names renamed to {REF}'s (" +
          ", ".join(f"{v} {k}" for k, v in sorted(rn.count.items())) + ")")


# ---------------------------------------------------------------------------
# Reports

def report(al, tgt, out=sys.stdout):
    tot = collections.Counter()
    t = tgt
    print(f"{'module':<10} {REF:>5} {t:>5} {'ident':>6} {'changed':>8} {REF + ' only':>8} {t + ' only':>8}"
          f" {'ident %':>8}", file=out)
    for name, a in al.items():
        s = a.stats()
        tot.update(s)
        if name.startswith("ovl_") and s["identical"] == s["ref"] == s["tgt"]:
            tot["ovl_same"] += 1
            continue
        print(f"{name:<10} {s['ref']:>5} {s['tgt']:>5} {s['identical']:>6} {s['changed']:>8} "
              f"{s['ref_only']:>8} {s['tgt_only']:>8} {100 * s['identical'] / max(s['ref'], 1):>7.1f}%", file=out)
    print(f"{'total':<10} {tot['ref']:>5} {tot['tgt']:>5} {tot['identical']:>6} {tot['changed']:>8} "
          f"{tot['ref_only']:>8} {tot['tgt_only']:>8} {100 * tot['identical'] / max(tot['ref'], 1):>7.1f}%", file=out)
    print(f"({tot['ovl_same']} overlays have every function identical and are not listed)", file=out)


def list_functions(a, tgt, out=sys.stdout):
    inv_ex = {j: i for i, j in a.exact.items()}
    inv_ch = {j: i for i, j in a.changed.items()}
    for i, f in enumerate(a.rf):
        if i in a.exact:
            g, st = a.tf[a.exact[i]], "identical"
        elif i in a.changed:
            g, st = a.tf[a.changed[i]], "changed"
        else:
            g, st = None, f"{REF}-only"
        print(f"{a.rm.name} {f.addr:08X} {g.addr if g else 0:08X} {st} {f.size}"
              + (f" {g.size}" if g else ""), file=out)
    for j, g in enumerate(a.tf):
        if j not in inv_ex and j not in inv_ch:
            print(f"{a.rm.name} {0:08X} {g.addr:08X} {tgt}-only 0 {g.size}", file=out)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("versions", nargs="*", metavar="VERSION",
                    help=f"the versions to map from {REF} (default: {' '.join(TARGETS)})")
    ap.add_argument("--check", action="store_true", help="fail if vermap.<V>.txt is out of date")
    ap.add_argument("--report", action="store_true", help="alignment statistics per module")
    ap.add_argument("--functions", metavar="MODULE",
                    help="list every function and how it aligned (`all` for every module)")
    ap.add_argument("--rename", metavar="VERSION",
                    help="rename the names in asm/ (as `make extract` leaves it) to us's")
    args = ap.parse_args()
    if args.rename:
        rename_tree(args.rename)
        return
    targets = args.versions or TARGETS
    for v in targets:
        if v not in TARGETS:
            ap.error(f"{v}: not one of {', '.join(TARGETS)}")
    rmods = load_modules(REF)
    for tgt in targets:
        if len(targets) > 1 and (args.report or args.functions):
            print(f"== {REF} -> {tgt}")
        tmods = load_modules(tgt)
        assert list(rmods) == list(tmods), f"{REF}'s and {tgt}'s modules differ"
        vm, al = build(rmods, tmods)
        if args.report:
            report(al, tgt)
            continue
        if args.functions:
            for name, a in al.items():
                if args.functions in ("all", name):
                    list_functions(a, tgt)
            continue
        path = map_file(tgt)
        if args.check:
            import tempfile
            with tempfile.TemporaryDirectory() as td:
                tmp = Path(td) / "map"
                write_map(vm, tmp, tgt)
                if not path.exists() or path.read_text() != tmp.read_text():
                    sys.exit(f"{path.name} out of date; run tools/vermap.py {tgt}")
            print(f"{path.name}: up to date")
            continue
        write_map(vm, path, tgt)
        print(f"{path.name}: {sum(len(r) for r in vm.ranges.values())} ranges")
        report(al, tgt)


if __name__ == "__main__":
    main()
