"""The model files of asset bank 0x18 ("64" container, record types < 0x10).

The container (docs/ASSETS.md, "The "64" container" and "Models"; all
big-endian) is the pictures' (bm64image.py): a 0x10-byte header, N 12-byte
records, the data.  Each record is {a, offset, type of the NEXT record}; the
header's word at 0x0C is the type of record 0, and when N is odd the last
record is 8 bytes.  A model's record types, from the code that reads them:

  0  a display list        func_8022D58C: gSPSegment(2, file), gSPDisplayList(file + offset)
  5  a display list drawn with the matrix of func_8022928C pushed (a billboard)
  6  a display list after the code's own DL (D_8029FCC8) and a G_SETTILESIZE
     from D_802A2D50 (a scrolling texture); G_TEXTURE and the texgen bit
     are cleared after it
  8  a display list with G_TEXTURE_GEN set (an environment map)
  1  the node table: `a` is the root node, `offset` the table (func_8022D414)
  2  base poses   (func_8022AF1C)
  3  animations   (func_8022AF1C)
  4  {0, 0}, read by nothing (an end marker before 2, 3, 7)
  7  {4, offset}: six u32s (func_8022AF1C copies them only if a == 4)

`a` is 1.0 (0x3F800000) in every display list record and nothing reads it.
A record's index is what the node table and the objects (`obj->0x38`)
name, and func_8022A6C4 picks what to draw: the record of type 1 if there
is one (a hierarchy), else the first record with a type below 0x10.

Node (0x30 bytes, func_8022D414 / func_8022D280):
  0x00 s32  record to draw (-1: none)
  0x04 f32  translation x, y, z  (applied when not all 0)
  0x10 f32  rotation x, y, z     (applied when not all 0)
  0x1C f32  scale x, y, z        (1.0; the static draw doesn't read it)
  0x28 s32  next sibling, relative to this node's index (0: none)
  0x2C s32  first child, relative (0: none)

Base poses (type 2, `a` groups): {u32 id, u32 m}, then m times {u32 c,
c u32s, 9 f32s}.  Animations (type 3, `a` clips): {u32 id, u32 m, u32
length}, then m tracks: {0x2F, u32 c, u32 x, c times {u32, u32}} or {0x30,
u32 x, u32 y, u32 c, u32 z, c times {u32 frame, f32 value}}.

Everything else is found through the display lists: G_VTX (16-byte
vertices), G_SETTIMG + G_LOADBLOCK/G_LOADTILE + G_SETTILE (textures),
G_SETTIMG + G_LOADTLUT (palettes), G_DL (more display lists).  All of them
address the file as segment 2.

parse() cuts the file into blocks in file order (the header, then display
lists, vertex runs, textures, palettes, the node table, the poses, the
animations, the type 7 words, and `raw` for whatever is left), decodes
each and makes every segment 2 address (in the records and the display
lists) a reference to a block, `label+delta`.  pack() lays the blocks out
again (each block that started 8-aligned is 8-aligned again, with zeros
in between) and resolves the references, so a block may change size.
"""
import bisect
import struct

import yaml

from . import bm64image as IMG

MAGIC = 0x36340038
DL_TYPES = (0, 5, 6, 8)
T_NODES, T_POSES, T_ANIMS, T_END, T_T7 = 1, 2, 3, 4, 7
DEFAULT_HDR = bytes([2, 2, 2, 2])
# record types whose offset is a place in the file (type 4's is left over
# junk, "0000" and the like, and stays a number)
REF_TYPES = DL_TYPES + (T_NODES, T_POSES, T_ANIMS, T_T7)
ALIGNED = 8

FMTS = ["rgba", "yuv", "ci", "ia", "i", "fmt5", "fmt6", "fmt7"]
SIZS = ["4b", "8b", "16b", "32b"]
BITS = [4, 8, 16, 32]


def u32(d, o):
    return struct.unpack_from(">I", d, o)[0]


def is_model(data):
    """A "64" container whose first record isn't a picture."""
    return (len(data) >= 0x10 and u32(data, 0) == MAGIC
            and u32(data, 12) < 0x10)


# ---- floats ----

def f2y(bits):
    """A float's bits as YAML: the float if it reads back to the same bits."""
    v = struct.unpack(">f", struct.pack(">I", bits))[0]
    if v == v and struct.unpack(">I", struct.pack(">f", v))[0] == bits:
        return v
    return f"0x{bits:08X}"


def y2f(v):
    if isinstance(v, str):
        return int(v, 0)
    return struct.unpack(">I", struct.pack(">f", float(v)))[0]


# ---- display list commands ----
# opcode: (name, [(field, word, shift, width, kind)], has an address in w1)
# kind: "d" decimal, "x" hex, "fmt"/"siz" names, "+1" decimal stored minus 1,
# "x2" a vertex index stored doubled
_TILE = ("tile", 1, 24, 3, "d")
CMDS = {
    0x01: ("mtx", [("params", 0, 16, 8, "x"), ("len", 0, 0, 16, "d")], True),
    0x03: ("movemem", [("index", 0, 16, 8, "x"), ("len", 0, 0, 16, "d")], True),
    0x04: ("vtx", [("v0", 0, 16, 8, "x2"), ("n", 0, 10, 6, "d"), ("size", 0, 0, 10, "+1")], True),
    0x06: ("dl", [("branch", 0, 16, 8, "d")], True),
    0xB1: ("tri2", [("a", 0, 16, 8, "x2"), ("b", 0, 8, 8, "x2"), ("c", 0, 0, 8, "x2"),
                    ("d", 1, 16, 8, "x2"), ("e", 1, 8, 8, "x2"), ("f", 1, 0, 8, "x2")], False),
    0xB3: ("rdphalf_2", [("data", 1, 0, 32, "x")], False),
    0xB4: ("rdphalf_1", [("data", 1, 0, 32, "x")], False),
    0xB6: ("cleargeometrymode", [("mode", 1, 0, 32, "x")], False),
    0xB7: ("setgeometrymode", [("mode", 1, 0, 32, "x")], False),
    0xB8: ("enddl", [], False),
    0xB9: ("setothermode_l", [("shift", 0, 8, 8, "d"), ("len", 0, 0, 8, "d"),
                              ("data", 1, 0, 32, "x")], False),
    0xBA: ("setothermode_h", [("shift", 0, 8, 8, "d"), ("len", 0, 0, 8, "d"),
                              ("data", 1, 0, 32, "x")], False),
    0xBB: ("texture", [("level", 0, 11, 3, "d"), ("tile", 0, 8, 3, "d"), ("on", 0, 0, 8, "d"),
                       ("s", 1, 16, 16, "x"), ("t", 1, 0, 16, "x")], False),
    0xBC: ("moveword", [("offset", 0, 8, 16, "x"), ("index", 0, 0, 8, "d"),
                        ("data", 1, 0, 32, "x")], False),
    0xBD: ("popmtx", [("param", 1, 0, 32, "d")], False),
    0xBE: ("culldl", [("first", 0, 0, 16, "x2"), ("last", 1, 0, 32, "x2")], False),
    0xBF: ("tri1", [("flag", 1, 24, 8, "d"), ("a", 1, 16, 8, "x2"), ("b", 1, 8, 8, "x2"),
                    ("c", 1, 0, 8, "x2")], False),
    0xE4: ("texrect", [("xh", 0, 12, 12, "d"), ("yh", 0, 0, 12, "d"), _TILE,
                       ("xl", 1, 12, 12, "d"), ("yl", 1, 0, 12, "d")], False),
    0xE6: ("loadsync", [], False),
    0xE7: ("pipesync", [], False),
    0xE8: ("tilesync", [], False),
    0xE9: ("fullsync", [], False),
    0xF0: ("loadtlut", [_TILE, ("colours", 1, 14, 10, "+1")], False),
    0xF2: ("settilesize", [("uls", 0, 12, 12, "d"), ("ult", 0, 0, 12, "d"), _TILE,
                           ("lrs", 1, 12, 12, "d"), ("lrt", 1, 0, 12, "d")], False),
    0xF3: ("loadblock", [("uls", 0, 12, 12, "d"), ("ult", 0, 0, 12, "d"), _TILE,
                         ("lrs", 1, 12, 12, "d"), ("dxt", 1, 0, 12, "d")], False),
    0xF4: ("loadtile", [("uls", 0, 12, 12, "d"), ("ult", 0, 0, 12, "d"), _TILE,
                        ("lrs", 1, 12, 12, "d"), ("lrt", 1, 0, 12, "d")], False),
    0xF5: ("settile", [("fmt", 0, 21, 3, "fmt"), ("siz", 0, 19, 2, "siz"), ("line", 0, 9, 9, "d"),
                       ("tmem", 0, 0, 9, "x"), _TILE, ("pal", 1, 20, 4, "d"),
                       ("cmt", 1, 18, 2, "d"), ("maskt", 1, 14, 4, "d"), ("shiftt", 1, 10, 4, "d"),
                       ("cms", 1, 8, 2, "d"), ("masks", 1, 4, 4, "d"), ("shifts", 1, 0, 4, "d")],
           False),
    0xF6: ("fillrect", [("xl", 0, 12, 12, "d"), ("yl", 0, 0, 12, "d"),
                        ("xh", 1, 12, 12, "d"), ("yh", 1, 0, 12, "d")], False),
    0xF7: ("fillcolor", [("color", 1, 0, 32, "x")], False),
    0xF8: ("fogcolor", [("color", 1, 0, 32, "x")], False),
    0xF9: ("blendcolor", [("color", 1, 0, 32, "x")], False),
    0xFA: ("primcolor", [("minlevel", 0, 8, 8, "d"), ("lodfrac", 0, 0, 8, "d"),
                         ("color", 1, 0, 32, "x")], False),
    0xFB: ("envcolor", [("color", 1, 0, 32, "x")], False),
    0xFC: ("setcombine", [("mux0", 0, 0, 24, "x"), ("mux1", 1, 0, 32, "x")], False),
    0xFD: ("settimg", [("fmt", 0, 21, 3, "fmt"), ("siz", 0, 19, 2, "siz"),
                       ("width", 0, 0, 12, "+1")], True),
    0xFE: ("setzimg", [], True),
    0xFF: ("setcimg", [("fmt", 0, 21, 3, "fmt"), ("siz", 0, 19, 2, "siz"),
                       ("width", 0, 0, 12, "+1")], True),
}
BY_NAME = {v[0]: (k, v[1], v[2]) for k, v in CMDS.items()}


def _fval(raw, kind):
    if kind == "+1":
        return raw + 1
    if kind == "x2":
        return raw >> 1
    return raw


def _fraw(val, kind):
    if kind == "+1":
        return val - 1
    if kind == "x2":
        return val << 1
    return val


def _fstr(val, kind):
    if kind == "x":
        return f"0x{val:X}"
    if kind == "fmt":
        return FMTS[val]
    if kind == "siz":
        return SIZS[val]
    return str(val)


def cmd_fields(w0, w1):
    """(name, [(field, value, kind)], address or None) if the command
    decodes and encodes back to the same words, else None."""
    op = w0 >> 24
    if op not in CMDS:
        return None
    name, fields, addr = CMDS[op]
    vals = []
    words = [op << 24, 0]
    for f, w, sh, wd, kind in fields:
        raw = ((w0, w1)[w] >> sh) & ((1 << wd) - 1)
        if kind == "x2" and raw & 1:
            return None
        vals.append((f, _fval(raw, kind), kind))
        words[w] |= raw << sh
    if addr:
        words[1] = w1
    if (words[0], words[1]) != (w0, w1):
        return None
    return name, vals, (w1 if addr else None)


def cmd_text(w0, w1, ref):
    """One command as text; ref(address) gives the address's text."""
    d = cmd_fields(w0, w1)
    if d is None:
        return f"raw 0x{w0:08X} 0x{w1:08X}"
    name, vals, addr = d
    if name == "vtx" and vals[2][1] == 16 * vals[1][1]:
        vals = vals[:2]     # the byte count, when it is the usual 16 n
    parts = [name] + [f"{f}={_fstr(v, k)}" for f, v, k in vals]
    if addr is not None:
        parts.append(f"addr={ref(addr)}")
    return " ".join(parts)


def cmd_words(text, resolve):
    """The inverse of cmd_text(); resolve(text) gives an address."""
    parts = text.split()
    if parts[0] == "raw":
        return int(parts[1], 0), int(parts[2], 0)
    if parts[0] not in BY_NAME:
        raise ValueError(f"unknown command {parts[0]!r}")
    op, fields, addr = BY_NAME[parts[0]]
    kv = dict(p.split("=", 1) for p in parts[1:])
    if parts[0] == "vtx" and "size" not in kv:
        kv["size"] = str(16 * int(kv["n"], 0))
    words = [op << 24, 0]
    for f, w, sh, wd, kind in fields:
        v = kv.pop(f)
        if kind == "fmt":
            val = FMTS.index(v)
        elif kind == "siz":
            val = SIZS.index(v)
        else:
            val = int(v, 0)
        raw = _fraw(val, kind)
        if not 0 <= raw < 1 << wd:
            raise ValueError(f"{text}: {f} out of range")
        words[w] |= raw << sh
    if addr:
        words[1] = resolve(kv.pop("addr"))
    if kv:
        raise ValueError(f"{text}: unknown fields {sorted(kv)}")
    return words[0], words[1]


# ---- the container ----

def read_header(d):
    n = u32(d, 4)
    if n == 0 or 0x10 + 12 * n - 4 > len(d):
        raise ValueError("bad record count")
    types = [u32(d, 12)]
    recs = []
    for i in range(n):
        o = 0x10 + 12 * i
        a, off = struct.unpack_from(">II", d, o)
        if i < n - 1:
            types.append(u32(d, o + 8))
        recs.append([types[i], a, off])
    last = u32(d, 0x10 + 12 * n - 4) if n % 2 == 0 else 0
    return recs, last, 0x10 + 12 * n - (4 if n % 2 else 0)


class _Walk:
    """What the display lists and records point at: claims (start, end,
    kind, info)."""

    def __init__(self, d, recs):
        self.d = d
        self.claims = []
        self.dls = set()
        for t, a, off in recs:
            if t in DL_TYPES:
                self.dl(off)
        for t, a, off in recs:
            if t == T_NODES:
                self.claim(off, off + 0x30 * _node_count(d, off, a), "nodes")
            elif t == T_POSES:
                self.claim(off, _poses_end(d, off, a), "poses")
            elif t == T_ANIMS:
                self.claim(off, off + _anims(d[off:], a)[1], "anims")
            elif t == T_T7 and a == 4:
                self.claim(off, off + 24, "words")

    def claim(self, s, e, kind, info=None):
        if not 0 <= s < e <= len(self.d):
            raise ValueError(f"{kind} at 0x{s:X}-0x{e:X} out of the file")
        self.claims.append((s, e, kind, info))

    def dl(self, off):
        if off in self.dls:
            return
        self.dls.add(off)
        d = self.d
        p = off
        timg = None
        tlut = None
        load = None         # (offset, bytes) of the last load from segment 2
        while True:
            if p + 8 > len(d) or p < 0x10:
                raise ValueError(f"display list at 0x{off:X} runs out of the file")
            w0, w1 = struct.unpack_from(">II", d, p)
            p += 8
            c = w0 >> 24
            seg, a = w1 >> 24, w1 & 0xFFFFFF
            if c == 0xB8:
                break
            if c == 0x06:
                if seg == 2:
                    self.dl(a)
                if (w0 >> 16) & 0xFF == 1:
                    break
            elif c == 0x04 and seg == 2:
                n = (w0 >> 10) & 0x3F
                self.claim(a, a + 16 * n, "vtx")
            elif c == 0xFD:
                timg = ((w0 >> 21) & 7, (w0 >> 19) & 3, (w0 & 0xFFF) + 1, w1)
                load = None
            elif c == 0xF0 and timg and timg[3] >> 24 == 2:
                cnt = ((w1 >> 14) & 0x3FF) + 1
                tlut = timg[3] & 0xFFFFFF
                # the load may read past the colours, even past the file
                self.claim(tlut, min(tlut + 2 * cnt, len(d)), "pal")
            elif c == 0xF3 and timg and timg[3] >> 24 == 2:
                texels = ((w1 >> 12) & 0xFFF) + 1
                load = (timg[3] & 0xFFFFFF, (texels << timg[1]) >> 1)
            elif c == 0xF4 and timg and timg[3] >> 24 == 2:
                rows = ((w1 & 0xFFF) >> 2) + 1
                load = (timg[3] & 0xFFFFFF, rows * ((timg[2] << timg[1]) >> 1), timg[2])
            elif c == 0xF5 and load and (w1 >> 24) & 7 != 7:
                fmt, siz = (w0 >> 21) & 7, (w0 >> 19) & 3
                if len(load) == 3:
                    width = load[2]
                else:
                    width = ((w0 >> 9) & 0x1FF) * 64 // BITS[siz]
                pal = tlut if fmt == 2 else None
                pal = (pal, (w1 >> 20) & 15) if pal is not None else None
                self.claim(load[0], load[0] + load[1], "tex", (FMTS[fmt], siz, width, pal))
                load = None
        self.claim(off, p, "dl")


def _partition(d, hdr_end, claims):
    """Blocks [start, end, kind, infos] covering hdr_end..len(d), from the
    claims; ValueError if two kinds overlap."""
    by = {}
    for s, e, k, info in claims:
        by.setdefault((s, k), []).append((e, info))
    items = sorted(((s, max(e for e, _ in v), k, [i for _, i in v if i is not None])
                    for (s, k), v in by.items()), key=lambda x: (x[0], x[1]))
    # a palette's G_LOADTLUT may read past its colours, into what follows
    starts = sorted({s for s, e, k, _ in items})
    out = []
    for s, e, k, infos in items:
        if s < hdr_end:
            raise ValueError(f"{k} at 0x{s:X} is inside the header")
        if k == "pal":
            nxt = [x for x in starts if x > s]
            if nxt and nxt[0] < e:
                e = nxt[0]
        if out and s < out[-1][1]:
            prev = out[-1]
            if prev[2] == k and k in ("vtx", "dl"):
                prev[1] = max(prev[1], e)
                continue
            if prev[2] == k and k == "tex" and e <= prev[1]:
                continue        # a smaller load of the same texture
            raise ValueError(f"{prev[2]} at 0x{prev[0]:X}-0x{prev[1]:X} overlaps "
                             f"{k} at 0x{s:X}-0x{e:X}")
        if out and s == out[-1][1] and k == "vtx" and out[-1][2] == "vtx":
            out[-1][1] = e      # adjacent vertex loads make one table
            continue
        out.append([s, e, k, infos])
    # what nothing claims
    blocks = []
    pos = hdr_end
    for s, e, k, infos in out:
        # zeros up to an 8-aligned block are its alignment, not a block
        if s > pos and not (s % ALIGNED == 0 and s - pos < ALIGNED and not any(d[pos:s])):
            blocks.append([pos, s, "raw", []])
        blocks.append([s, e, k, infos])
        pos = e
    if pos < len(d):
        blocks.append([pos, len(d), "raw", []])
    return blocks


def _label(kind, start):
    return f"{kind}_{start:04X}"


class Refs:
    """Offsets <-> `label+delta` over a list of blocks [(label, start, end)]."""

    def __init__(self, spans, hdr_end, size):
        self.spans = spans
        self.starts = [s for _, s, _ in spans]
        self.hdr_end = hdr_end
        self.size = size

    def name(self, off):
        if off < self.hdr_end or off > self.size:
            return None
        i = bisect.bisect_right(self.starts, off) - 1
        if i < 0:
            return None
        label, s, e = self.spans[i]
        if off == s:
            return label
        return f"{label}+0x{off - s:X}"

    def seg2(self, w1):
        if w1 >> 24 == 2:
            n = self.name(w1 & 0xFFFFFF)
            if n is not None:
                return n
        return f"0x{w1:08X}"


def _seg2(text, where):
    """A display list's address: `label[+0xN]` is in segment 2."""
    if text[0].isdigit():
        return int(text, 0)
    return 0x02000000 | _resolve(text, where)


def _resolve(text, where):
    """`label`, `label+0xN` or a number, to a number."""
    if text[0].isdigit():
        return int(text, 0)
    label, _, delta = text.partition("+")
    if label not in where:
        raise ValueError(f"no block {label!r}")
    return where[label] + (int(delta, 0) if delta else 0)


# ---- block contents ----

def _vtx_rows(b):
    return [list(struct.unpack_from(">hhhHhhBBBB", b, o)) for o in range(0, len(b), 16)]


def _vtx_bytes(rows):
    return b"".join(struct.pack(">hhhHhhBBBB", *r) for r in rows)


def _nodes(b):
    out = []
    for o in range(0, len(b), 0x30):
        w = struct.unpack_from(">i9Iii", b, o)
        out.append({"draw": w[0], "pos": [f2y(x) for x in w[1:4]], "rot": [f2y(x) for x in w[4:7]],
                    "scale": [f2y(x) for x in w[7:10]], "next": w[10], "child": w[11]})
    return out


def _nodes_bytes(nodes):
    return b"".join(struct.pack(">i9Iii", n["draw"], *[y2f(x) for x in n["pos"] + n["rot"] + n["scale"]],
                                n["next"], n["child"]) for n in nodes)


def _poses(b, count):
    out = []
    p = 0
    for _ in range(count):
        pid, m = struct.unpack_from(">II", b, p)
        p += 8
        parts = []
        for _ in range(m):
            c = u32(b, p)
            words = list(struct.unpack_from(f">{c}I", b, p + 4))
            p += 4 + 4 * c
            fl = [f2y(x) for x in struct.unpack_from(">9I", b, p)]
            p += 0x24
            parts.append({"words": words, "pos": fl[0:3], "rot": fl[3:6], "scale": fl[6:9]})
        out.append({"id": pid, "parts": parts})
    if p != len(b):
        raise ValueError("poses don't fill their block")
    return out


def _poses_bytes(poses):
    out = bytearray()
    for g in poses:
        out += struct.pack(">II", g["id"], len(g["parts"]))
        for pt in g["parts"]:
            out += struct.pack(f">I{len(pt['words'])}I", len(pt["words"]), *pt["words"])
            out += struct.pack(">9I", *[y2f(x) for x in pt["pos"] + pt["rot"] + pt["scale"]])
    return bytes(out)


def _anims(b, count):
    out = []
    p = 0
    for _ in range(count):
        aid, m, length = struct.unpack_from(">III", b, p)
        p += 12
        tracks = []
        for _ in range(m):
            tag = u32(b, p)
            if tag == 0x2F:
                c, x = struct.unpack_from(">II", b, p + 4)
                p += 12
                keys = [list(struct.unpack_from(">II", b, p + 8 * k)) for k in range(c)]
                p += 8 * c
                tracks.append({"tag": tag, "x": x, "keys": keys})
            elif tag == 0x30:
                x, y, c, z = struct.unpack_from(">IIII", b, p + 4)
                p += 0x14
                keys = []
                for k in range(c):
                    fr, v = struct.unpack_from(">II", b, p + 8 * k)
                    keys.append([fr, f2y(v)])
                p += 8 * c
                tracks.append({"tag": tag, "x": x, "y": y, "z": z, "keys": keys})
            else:
                raise ValueError(f"animation track tag 0x{tag:X}")
        out.append({"id": aid, "length": length, "tracks": tracks})
    return out, p


def _anims_bytes(anims):
    out = bytearray()
    for a in anims:
        out += struct.pack(">III", a["id"], len(a["tracks"]), a["length"])
        for t in a["tracks"]:
            if t["tag"] == 0x2F:
                out += struct.pack(">III", 0x2F, len(t["keys"]), t["x"])
                for k in t["keys"]:
                    out += struct.pack(">II", *k)
            else:
                out += struct.pack(">IIIII", 0x30, t["x"], t["y"], len(t["keys"]), t["z"])
                for fr, v in t["keys"]:
                    out += struct.pack(">II", fr, y2f(v))
    return bytes(out)


def _poses_end(d, off, count):
    p = off
    for _ in range(count):
        m = u32(d, p + 4)
        p += 8
        for _ in range(m):
            p += 4 + 4 * u32(d, p) + 0x24
            if p > len(d):
                raise ValueError("poses run out of the file")
    return p


def _node_count(d, off, root):
    """The node table's length: the nodes reachable from the root."""
    seen = set()
    todo = [root]
    while todo:
        i = todo.pop()
        if i in seen:
            continue
        if not 0 <= i < 4096 or off + 0x30 * (i + 1) > len(d):
            raise ValueError(f"node {i} out of the table")
        seen.add(i)
        nxt, child = struct.unpack_from(">ii", d, off + 0x30 * i + 0x28)
        if nxt:
            todo.append(i + nxt)
        if child:
            todo.append(i + child)
    return max(seen) + 1


# ---- textures ----

def _tex_frame(blk, pal_colours):
    """The texture block as a bm64image frame, or None if it isn't one
    (a format the PNG code doesn't do, or a size that doesn't divide)."""
    fmt, siz, width, pal = blk["info"]
    key = {("ci", 0): "ci4", ("ci", 1): "ci8", ("rgba", 2): "rgba16", ("rgba", 3): "rgba32"}.get((fmt, siz))
    if key is None or width <= 0:
        return None
    nbits = 8 * len(blk["bytes"])
    if nbits % (width * BITS[siz]):
        return None
    h = nbits // (width * BITS[siz])
    fr = {"fmt": key, "w": width, "h": h, "pixels": blk["bytes"], "pad": None, "palpad": None}
    if key in IMG.MAX_COLOURS:
        fr["palette"] = pal_colours if pal_colours is not None else [
            IMG.rgba_to_rgba16(v, v, v, 255) for v in
            (range(0, 256, 17) if key == "ci4" else range(256))]
        fr["palextra"] = b""
    return fr


# ---- parse / pack ----

def parse(data):
    """The file as {'hdr', 'last', 'recs': [[type, a, ref]], 'blocks':
    [{'label', 'kind', 'align', 'bytes', ...decoded...}]}.  ValueError if
    it isn't a model this understands, or doesn't pack back exactly."""
    if not is_model(data):
        raise ValueError("not a model")
    recs, last, hdr_end = read_header(data)
    walk = _Walk(data, recs)
    parts = _partition(data, hdr_end, walk.claims)
    blocks = []
    for s, e, k, infos in parts:
        b = {"label": _label(k, s), "kind": k, "start": s, "bytes": data[s:e],
             "align": ALIGNED if s % ALIGNED == 0 else 1}
        if k == "tex":
            b["info"] = infos[0]
        blocks.append(b)
    refs = Refs([(b["label"], b["start"], b["start"] + len(b["bytes"])) for b in blocks],
                hdr_end, len(data))
    m = {"hdr": data[8:12], "last": last,
         "recs": [[t, a, (refs.name(off) if t in REF_TYPES else None) or off]
                  for t, a, off in recs],
         "blocks": blocks}
    rec_counts = {t: a for t, a, _ in recs}
    for b in blocks:
        _decode(b, refs, rec_counts)
    if pack(m) != data:
        raise ValueError("doesn't pack back to the same bytes")
    return m


def _decode(b, refs, counts):
    k, raw = b["kind"], b["bytes"]
    try:
        if k == "dl":
            if len(raw) % 8:
                raise ValueError
            b["cmds"] = [cmd_text(*struct.unpack_from(">II", raw, o), refs.seg2)
                         for o in range(0, len(raw), 8)]
        elif k == "vtx":
            if len(raw) % 16:
                raise ValueError
            b["vtx"] = _vtx_rows(raw)
        elif k == "nodes":
            b["nodes"] = _nodes(raw)
        elif k == "poses":
            b["poses"] = _poses(raw, counts[T_POSES])
        elif k == "anims":
            b["anims"], n = _anims(raw, counts[T_ANIMS])
            if n != len(raw):
                raise ValueError
        elif k == "words":
            b["words"] = list(struct.unpack(">6I", raw))
        elif k == "pal":
            if len(raw) % 2:
                raise ValueError
            b["colours"] = list(struct.unpack(f">{len(raw) // 2}H", raw))
        else:
            return
    except (ValueError, struct.error, KeyError):
        b["kind"] = "raw"     # keep the bytes
        return
    if not (_dl_same(b) if k == "dl" else _encode(b, None) == raw):
        b["kind"] = "raw"


def _encode(b, where):
    k = b["kind"]
    if k == "vtx":
        return _vtx_bytes(b["vtx"])
    if k == "nodes":
        return _nodes_bytes(b["nodes"])
    if k == "poses":
        return _poses_bytes(b["poses"])
    if k == "anims":
        return _anims_bytes(b["anims"])
    if k == "words":
        return struct.pack(">6I", *b["words"])
    if k == "pal":
        return struct.pack(f">{len(b['colours'])}H", *b["colours"])
    return b["bytes"]


def _dl_same(b):
    """At decode time the addresses aren't placed yet: check the commands
    without their addresses (pack() checks the whole file)."""
    raw = b["bytes"]
    for i, c in enumerate(b["cmds"]):
        w0, w1 = cmd_words(c, lambda t: 0)
        r0, r1 = struct.unpack_from(">II", raw, 8 * i)
        if w0 != r0 or (w1 != r1 and not c.split()[-1].startswith("addr=")):
            return False
    return True


def _size(b):
    if b["kind"] == "dl":
        return 8 * len(b["cmds"])
    return len(_encode(b, None))


def pack(m):
    """The file's bytes.  Blocks are placed in order, each 8-aligned one
    on a multiple of 8, and the references resolved."""
    recs = m["recs"]
    n = len(recs)
    hdr_end = 0x10 + 12 * n - (4 if n % 2 else 0)
    where = {}
    pos = hdr_end
    for b in m["blocks"]:
        if b.get("align", 1) > 1:
            pos = (pos + b["align"] - 1) & -b["align"]
        if b["label"] in where:
            raise ValueError(f"two blocks are called {b['label']}")
        where[b["label"]] = pos
        pos += _size(b)
    body = bytearray()
    for b in m["blocks"]:
        body += bytes(where[b["label"]] - hdr_end - len(body))
        if b["kind"] == "dl":
            for c in b["cmds"]:
                body += struct.pack(">II", *cmd_words(c, lambda t: _seg2(t, where)))
        else:
            body += _encode(b, where)
    out = bytearray(struct.pack(">II", MAGIC, n) + (m["hdr"] or DEFAULT_HDR)
                    + struct.pack(">I", recs[0][0]))
    for i, (t, a, ref) in enumerate(recs):
        off = ref if isinstance(ref, int) else _resolve(ref, where)
        nxt = recs[i + 1][0] if i + 1 < n else m["last"]
        out += struct.pack(">III", a, off, nxt)
    return bytes(out[:hdr_end]) + bytes(body)


# ---- files: NNN.mdl.yaml and a PNG per texture ----

def _hexa(v):
    return f"0x{v:08X}"


def tex_png(name, label):
    return f"{name}.{label}.png"


def _pal_slices(m):
    """{texture label: (palette label, first colour, owner)}: the palette a
    CI texture is drawn with (the last G_LOADTLUT before it, from colour
    16 * the tile's palette for CI4), and whether its PNG is the one the
    palette is built from (the first texture that shows all of it)."""
    pals = {b["start"]: b for b in m["blocks"] if b["kind"] == "pal"}
    out = {}
    owned = set()
    for b in m["blocks"]:
        if b["kind"] != "tex" or b["info"][3] is None or _tex_frame(b, []) is None:
            continue
        poff, idx = b["info"][3]
        pb = pals.get(poff)
        if pb is None:
            continue
        ci4 = b["info"][1] == 0
        first = 16 * idx if ci4 else 0
        own = (first == 0 and pb["label"] not in owned
               and len(pb["colours"]) <= (16 if ci4 else 256))
        if own:
            owned.add(pb["label"])
        out[b["label"]] = (pb["label"], first, own)
    return out


def dump(m, name, out_dir):
    """Write the model's textures as PNGs to out_dir; returns the yaml-able
    dict (NNN.mdl.yaml's contents)."""
    y = {}
    if m["hdr"] != DEFAULT_HDR:
        y["hdr"] = m["hdr"].hex()
    if m["last"]:
        y["last"] = m["last"]
    y["records"] = [{"type": t, "a": _hexa(a), "at": ref if isinstance(ref, str) else _hexa(ref)}
                    for t, a, ref in m["recs"]]
    slices = _pal_slices(m)
    pals = {b["label"]: b for b in m["blocks"] if b["kind"] == "pal"}
    owners = {}
    blocks = []
    for b in m["blocks"]:
        k = b["kind"]
        e = {"label": b["label"]}
        if b.get("align", 1) != ALIGNED:
            e["align"] = b.get("align", 1)
        if k == "tex":
            sl = slices.get(b["label"])
            colours = None
            if sl:
                colours = pals[sl[0]]["colours"][sl[1]:sl[1] + (16 if b["info"][1] == 0 else 256)]
            fr = _tex_frame(b, colours)
            if fr is None:
                k = "raw"
            else:
                IMG.write_png(out_dir / tex_png(name, b["label"]), fr)
                e.update(fmt=fr["fmt"], w=fr["w"], h=fr["h"])
                if sl:
                    e["pal"] = sl[0] if not sl[1] else f"{sl[0]}+{sl[1]}"
                    if sl[2]:
                        e["owner"] = True
                        owners[sl[0]] = b["label"]
        if k == "pal":
            if b["label"] in owners or any(v[0] == b["label"] and v[2] for v in slices.values()):
                e["colours"] = len(b["colours"])
            else:
                e["colours"] = [f"{c:04X}" for c in b["colours"]]
        elif k == "dl":
            e["dl"] = b["cmds"]
        elif k in ("vtx", "nodes", "poses", "anims"):
            e[k] = b[k]
        elif k == "words":
            e["words"] = [_hexa(w) for w in b["words"]]
        elif k == "raw":
            raw = b["bytes"]
            if any(raw):
                e["raw"] = raw.hex()
            else:
                e["zeros"] = len(raw)
        blocks.append(e)
    y["blocks"] = blocks
    return y


_KEYS = ("dl", "vtx", "nodes", "poses", "anims", "words", "raw", "zeros")


def load(y, name, src_dir):
    """The inverse of dump(): the yaml's dict and the PNGs -> a model for
    pack()."""
    m = {"hdr": bytes.fromhex(y["hdr"]) if "hdr" in y else DEFAULT_HDR,
         "last": y.get("last", 0),
         "recs": [[r["type"], int(r["a"], 0),
                   int(r["at"], 0) if r["at"][:1].isdigit() else r["at"]] for r in y["records"]],
         "blocks": []}
    pal_from = {}       # palette label -> the colours of its owner's PNG
    texs = {}
    for e in y["blocks"]:
        if "fmt" in e:
            w, h, pixels, pal = IMG.read_png(src_dir / tex_png(name, e["label"]), e["fmt"])
            texs[e["label"]] = pixels
            if e.get("owner"):
                pal_from[e["pal"]] = pal
    for e in y["blocks"]:
        b = {"label": e["label"], "align": e.get("align", ALIGNED)}
        if "fmt" in e:
            b.update(kind="tex", bytes=texs[e["label"]])
        elif "colours" in e:
            c = e["colours"]
            if isinstance(c, int):
                pal = pal_from[e["label"]]
                if len(pal) < c:
                    raise ValueError(f"{name} {e['label']}: the PNG has {len(pal)} colours, "
                                     f"the palette {c}")
                c = pal[:c]
            else:
                c = [int(x, 16) for x in c]
            b.update(kind="pal", colours=c)
        else:
            key = next(k for k in _KEYS if k in e)
            if key == "dl":
                b.update(kind="dl", cmds=e["dl"])
            elif key == "words":
                b.update(kind="words", words=[int(w, 0) for w in e["words"]])
            elif key == "raw":
                b.update(kind="raw", bytes=bytes.fromhex(e["raw"]))
            elif key == "zeros":
                b.update(kind="raw", bytes=bytes(e["zeros"]))
            else:
                b.update(kind=key, **{key: e[key]})
        m["blocks"].append(b)
    return m


# ---- YAML ----

class Flow(list):
    """A list YAML writes on one line."""


class FlowMap(dict):
    """A mapping YAML writes on one line."""


_BASE = getattr(yaml, "CSafeDumper", yaml.SafeDumper)


class Dumper(_BASE):
    pass


Dumper.add_representer(Flow, lambda d, v: d.represent_sequence(
    "tag:yaml.org,2002:seq", v, flow_style=True))
Dumper.add_representer(FlowMap, lambda d, v: d.represent_mapping(
    "tag:yaml.org,2002:map", v.items(), flow_style=True))
Loader = getattr(yaml, "CSafeLoader", yaml.SafeLoader)


def _styled(y):
    """dump()'s dict with the short things on one line: records, a vertex,
    a texture's or a palette's entry, a node's vectors, a key."""
    def node(n):
        return {k: Flow(v) if isinstance(v, list) else v for k, v in n.items()}
    out = {k: v for k, v in y.items() if k not in ("records", "blocks")}
    out["records"] = [FlowMap(r) for r in y["records"]]
    blocks = []
    for e in y["blocks"]:
        if "vtx" in e:
            e = dict(e, vtx=[Flow(r) for r in e["vtx"]])
        elif "nodes" in e:
            e = dict(e, nodes=[FlowMap(node(n)) for n in e["nodes"]])
        elif "poses" in e:
            e = dict(e, poses=[{"id": g["id"], "parts": [FlowMap(node(p)) for p in g["parts"]]}
                               for g in e["poses"]])
        elif "anims" in e:
            e = dict(e, anims=[dict(a, tracks=[dict(t, keys=[Flow(k) for k in t["keys"]])
                                               for t in a["tracks"]]) for a in e["anims"]])
        elif "words" in e:
            e = dict(e, words=Flow(e["words"]))
        elif "dl" in e or "raw" in e:
            pass
        else:
            e = FlowMap(e)
        if "colours" in e and isinstance(e["colours"], list):
            e = FlowMap(e)
        blocks.append(e)
    out["blocks"] = blocks
    return out


def to_yaml(y, comment=""):
    return comment + yaml.dump(_styled(y), Dumper=Dumper, sort_keys=False,
                               default_flow_style=False, width=120)


def from_yaml(text):
    return yaml.load(text, Loader=Loader)
