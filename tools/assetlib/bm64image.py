"""The picture files of asset bank 0x18 ("64" container, kinds 0x12/0x15/0x19).

Layout (docs/ASSETS.md, "The "64" container"; all big-endian):

  0x00  0x36340038            "64" and 0x38
  0x04  N                     number of records
  0x08  4 bytes               02 02 02 02 (kept as `hdr` when different)
  0x0C  type of record 0
  0x10  N records {u32 a, u32 offset, u32 type of the NEXT record}, the last
        record's third word being 0.  The last record is only 8 bytes when N
        is odd: the data starts at align8(0x10 + 12 N - 4) and covers it.

  a pixel record     a = w << 16 | h; type 0x12 CI4, 0x15 CI8, 0x19 RGBA32
                     (or 0x16 RGBA16); at `offset` the w * h texels, row after
                     row with no row padding (CI4: two to a byte, high nibble
                     first, the last byte rounded up)
  a palette record   a = the colour count; type 0x1a; right after the pixel
                     record of a CI picture; `offset` has RGBA16 (5551) colours

A CI picture is a pixel record and a palette record; a file is a list of
such frames and the frames need not share a format (entry 68 mixes CI4 and
CI8).  Blocks sit in record order, each at the 8-aligned offset after the
previous one.  What lies between blocks (and after the last) is zeros unless
the ROM says otherwise; the exceptions are kept as `pad`/`palpad` bytes (hex
in the yaml), never assumed zero (entry 37 has the leftover text "bff 0xff7"
after its pixels, and the unused low nibble of its last byte is 7: `tailnib`).

A frame becomes `NNN.F.png`: an indexed PNG (4 or 8 bits, palette in PLTE,
alpha in tRNS) for CI, 8-bit RGBA for RGBA32 and RGBA16.  RGBA16 colours
widen the way the RDP does (the high bits replicated) and narrow by a shift,
so a PNG written here reads back to the same bytes; alpha is one bit
(>= 128 is opaque).  Everything else is `NNN.img.yaml`.

The same code writes a model's embedded textures (bm64model.py): they are
the same CI4/CI8 pixel blocks and RGBA16 palettes, only found through the
display list (G_SETTIMG / G_LOADBLOCK / G_LOADTLUT) instead of a record
table.  tools/assets.py converts the 11 pictures with a model behind them
with bm64model.py; the `model` handling here is the fallback.
"""
import struct

import png

MAGIC = 0x36340038
T_CI4, T_CI8, T_RGBA16, T_RGBA32, T_PAL = 0x12, 0x15, 0x16, 0x19, 0x1a
FMT = {T_CI4: "ci4", T_CI8: "ci8", T_RGBA16: "rgba16", T_RGBA32: "rgba32"}
TYPE = {v: k for k, v in FMT.items()}
DEFAULT_HDR = bytes([2, 2, 2, 2])
MAX_COLOURS = {"ci4": 16, "ci8": 256}


def align8(x):
    return (x + 7) & ~7


def pixel_bytes(fmt, w, h):
    n = w * h
    return {"ci4": (n + 1) // 2, "ci8": n, "rgba16": 2 * n, "rgba32": 4 * n}[fmt]


def _w5(x):
    return (x << 3) | (x >> 2)


def rgba16_to_rgba(v):
    return (_w5(v >> 11), _w5((v >> 6) & 31), _w5((v >> 1) & 31), 255 if v & 1 else 0)


def rgba_to_rgba16(r, g, b, a):
    return (r >> 3) << 11 | (g >> 3) << 6 | (b >> 3) << 1 | (1 if a >= 128 else 0)


def is_image(data):
    """True if data looks like a picture file (the header's kind)."""
    return (len(data) >= 0x10 and struct.unpack_from(">I", data, 0)[0] == MAGIC
            and struct.unpack_from(">I", data, 12)[0] in FMT)


def parse(data):
    """The file as {'hdr': bytes or None, 'hpad': bytes or None, 'frames':
    [{'fmt', 'w', 'h', 'pixels', 'palette' (u16 list, CI only), 'palextra'
    (bytes), 'pad', 'palpad'}], 'model': None or {...}}.  A pad is None when
    it is the default.  Entries 452-458 are pictures followed by a model's
    directory and data: 'model' holds those records ('recs', their offsets
    made relative to 'rest''s start where they point into it, `rel` listing
    which), 'link' (the type word chaining to them) and 'rest' (the bytes).
    ValueError if the file isn't of this shape or doesn't pack back to the
    same bytes."""
    if struct.unpack_from(">I", data, 0)[0] != MAGIC:
        raise ValueError("not a 64 container")
    n, = struct.unpack_from(">I", data, 4)
    hdr = data[8:12]
    first, = struct.unpack_from(">I", data, 12)
    recs = []
    for i in range(n):
        o = 0x10 + 12 * i
        if i == n - 1:
            a, off = struct.unpack_from(">II", data, o)
            nxt = struct.unpack_from(">I", data, o + 8)[0] if n % 2 == 0 else 0
            recs.append((a, off, nxt))
        else:
            recs.append(struct.unpack_from(">3I", data, o))
    if recs[-1][2] != 0:
        raise ValueError("the last record's type word isn't 0")
    types = [first] + [r[2] for r in recs[:-1]]
    frames = []
    blocks = []     # (offset, length, frame, pad key) in record order
    i = 0
    while i < n and types[i] in FMT:
        fmt = FMT[types[i]]
        a, off, _ = recs[i]
        w, h = a >> 16, a & 0xFFFF
        fr = {"fmt": fmt, "w": w, "h": h, "pad": None, "palpad": None}
        ln = pixel_bytes(fmt, w, h)
        fr["pixels"] = data[off:off + ln]
        if len(fr["pixels"]) != ln:
            raise ValueError(f"record {i}: the pixels run past the end")
        blocks.append((off, ln, fr, "pad"))
        i += 1
        if fmt in MAX_COLOURS:
            if i >= n or types[i] != T_PAL:
                raise ValueError(f"record {i}: a CI frame without a palette")
            c, poff, _ = recs[i]
            if poff + 2 * c > len(data):
                raise ValueError(f"record {i}: {c} colours run past the end")
            fit = min(c, MAX_COLOURS[fmt])
            fr["palette"] = list(struct.unpack_from(f">{fit}H", data, poff))
            fr["palextra"] = data[poff + 2 * fit:poff + 2 * c]     # a count past 16/256
            blocks.append((poff, 2 * c, fr, "palpad"))
            i += 1
        frames.append(fr)
    if not frames:
        raise ValueError("no picture in it")
    m = {"hdr": None if hdr == DEFAULT_HDR else hdr, "hpad": None, "frames": frames,
         "model": None}
    pos = align8(0x10 + 12 * n - 4)
    owner, key = m, "hpad"
    for off, ln, fr, nkey in blocks:
        if off < pos:
            raise ValueError(f"the block at 0x{off:X} overlaps the one before")
        gap = data[pos:off]
        owner[key] = None if gap == bytes(align8(pos) - pos) else gap
        owner, key, pos = fr, nkey, off + ln
    if i < n:
        base = align8(pos)
        mrecs = [list(r) for r in recs[i:]]
        rel = [k for k, r in enumerate(mrecs) if base <= r[1] <= len(data)]
        for k in rel:
            mrecs[k][1] -= base
        m["model"] = {"link": recs[i - 1][2], "recs": mrecs, "rel": rel, "rest": data[base:]}
    else:
        owner[key] = data[pos:] or None
    if pack(m) != data:
        raise ValueError("doesn't pack back to the same bytes")
    return m


def pack(m):
    """The file's bytes.  Offsets come from the sizes, so an edited picture
    (another size, more colours) moves what follows it."""
    recs = []       # [a, offset, next type]
    types = []
    blocks = []     # (record index, bytes, frame, pad key)
    for fr in m["frames"]:
        fmt = fr["fmt"]
        if len(fr["pixels"]) != pixel_bytes(fmt, fr["w"], fr["h"]):
            raise ValueError("the pixel count doesn't match the size")
        types.append(TYPE[fmt])
        recs.append([fr["w"] << 16 | fr["h"], 0, 0])
        blocks.append((len(recs) - 1, fr["pixels"], fr, "pad"))
        if fmt in MAX_COLOURS:
            pal = fr["palette"]
            if len(pal) > MAX_COLOURS[fmt]:
                raise ValueError(f"{len(pal)} colours in a {fmt} palette")
            extra = fr.get("palextra") or b""
            types.append(T_PAL)
            recs.append([len(pal) + len(extra) // 2, 0, 0])
            blocks.append((len(recs) - 1, struct.pack(f">{len(pal)}H", *pal) + extra, fr, "palpad"))
    nimg = len(recs)
    model = m.get("model")
    n = nimg + (len(model["recs"]) if model else 0)
    for i in range(nimg - 1):
        recs[i][2] = types[i + 1]
    if model:
        recs[nimg - 1][2] = model["link"]
    pos = start = align8(0x10 + 12 * n - 4)
    body = bytearray()
    owner, key = m, "hpad"
    for ri, blob, fr, nkey in blocks:
        gap = owner.get(key)
        if gap is None:
            gap = bytes(align8(pos) - pos)
        body += gap
        pos += len(gap)
        recs[ri][1] = pos
        body += blob
        pos += len(blob)
        owner, key = fr, nkey
    if model:
        base = align8(pos)
        body += bytes(base - pos)
        for k, r in enumerate(model["recs"]):
            recs.append([r[0], r[1] + base if k in model["rel"] else r[1], r[2]])
        body += model["rest"]
    else:
        body += owner.get(key) or b""
    table = b"".join(struct.pack(">III", *r) for r in recs)
    if n % 2:
        table = table[:-4]
    head = struct.pack(">II", MAGIC, n) + (m["hdr"] or DEFAULT_HDR) + struct.pack(">I", types[0])
    return (head + table).ljust(start, b"\0") + bytes(body)


# ---- pixels <-> PNG ----

def ci_indices(fmt, pixels, w, h):
    if fmt == "ci8":
        return list(pixels[:w * h])
    out = []
    for b in pixels:
        out += (b >> 4, b & 15)
    return out[:w * h]


def ci_pack(fmt, idx):
    if fmt == "ci8":
        return bytes(idx)
    idx = list(idx) + [0] * (len(idx) & 1)
    return bytes(idx[i] << 4 | idx[i + 1] for i in range(0, len(idx), 2))


def write_png(path, fr):
    """Frame -> PNG file."""
    w, h, fmt = fr["w"], fr["h"], fr["fmt"]
    with open(path, "wb") as f:
        if fmt in MAX_COLOURS:
            idx = ci_indices(fmt, fr["pixels"], w, h)
            pal = [rgba16_to_rgba(c) for c in fr["palette"]]
            # an index past the palette (none in the ROM's pictures so far)
            # needs an entry for the PNG to be valid
            pal += [(0, 0, 0, 0)] * (max(idx + [len(pal) - 1]) + 1 - len(pal))
            pal = pal or [(0, 0, 0, 0)]
            rows = [idx[y * w:(y + 1) * w] for y in range(h)]
            png.Writer(w, h, palette=pal, bitdepth=4 if fmt == "ci4" else 8).write(f, rows)
        else:
            rows = []
            for y in range(h):
                if fmt == "rgba32":
                    rows.append(list(fr["pixels"][y * w * 4:(y + 1) * w * 4]))
                else:
                    row = []
                    for (v,) in struct.iter_unpack(">H", fr["pixels"][y * w * 2:(y + 1) * w * 2]):
                        row += rgba16_to_rgba(v)
                    rows.append(row)
            png.Writer(w, h, greyscale=False, alpha=True, bitdepth=8).write(f, rows)


def read_png(path, fmt):
    """PNG file -> (w, h, pixels, palette or None).  A CI PNG must be
    indexed (4 or 8 bits, any number of colours up to the format's)."""
    w, h, rows, info = png.Reader(filename=str(path)).read()
    if fmt in MAX_COLOURS:
        if "palette" not in info:
            raise ValueError(f"{path}: not an indexed PNG (a {fmt} picture needs one)")
        plte = info["palette"]
        idx = [v for row in rows for v in row]
        if len(plte) > MAX_COLOURS[fmt] or (idx and max(idx) >= MAX_COLOURS[fmt]):
            raise ValueError(f"{path}: more colours than a {fmt} palette holds")
        pal = [rgba_to_rgba16(*(tuple(c) + (255,))[:4]) for c in plte]
        return w, h, ci_pack(fmt, idx), pal
    w, h, rows, info = png.Reader(filename=str(path)).asRGBA8()
    out = bytearray()
    for row in rows:
        row = list(row)
        if fmt == "rgba32":
            out += bytes(row)
        else:
            for i in range(0, len(row), 4):
                out += struct.pack(">H", rgba_to_rgba16(*row[i:i + 4]))
    return w, h, bytes(out), None


# ---- files ----

def frame_name(name, k, nframes):
    return f"{name}.png" if nframes == 1 else f"{name}.{k}.png"


def dump(m, name, out_dir):
    """Write a parsed file's PNGs (and `name.rest.bin`) to out_dir; returns
    the yaml-able dict (`name.img.yaml`'s contents)."""
    frames = []
    for k, fr in enumerate(m["frames"]):
        write_png(out_dir / frame_name(name, k, len(m["frames"])), fr)
        d = {"fmt": fr["fmt"], "w": fr["w"], "h": fr["h"]}
        if "palette" in fr:
            # the PNG's palette is as long as the highest index needs; the
            # picture's own colour count is kept when it is shorter
            idx = ci_indices(fr["fmt"], fr["pixels"], fr["w"], fr["h"])
            if len(fr["palette"]) < max(idx + [0]) + 1 or not fr["palette"]:
                d["colours"] = len(fr["palette"])
            if fr["palextra"]:
                d["palextra"] = fr["palextra"].hex()
        if fr["fmt"] == "ci4" and fr["w"] * fr["h"] % 2 and fr["pixels"][-1] & 15:
            d["tailnib"] = fr["pixels"][-1] & 15   # the unused half of the last byte
        for key in ("pad", "palpad"):
            if fr[key] is not None:
                d[key] = fr[key].hex()
        frames.append(d)
    y = {}
    if m["hdr"] is not None:
        y["hdr"] = m["hdr"].hex()
    if m["hpad"] is not None:
        y["hpad"] = m["hpad"].hex()
    y["frames"] = frames
    if m["model"]:
        mo = m["model"]
        (out_dir / f"{name}.rest.bin").write_bytes(mo["rest"])
        y["model"] = {"link": mo["link"], "recs": mo["recs"], "rel": mo["rel"]}
    return y


def load(y, name, src_dir):
    """The inverse of dump(): the yaml's dict and the files -> a file model."""
    frames = []
    for k, d in enumerate(y["frames"]):
        path = src_dir / frame_name(name, k, len(y["frames"]))
        w, h, pixels, pal = read_png(path, d["fmt"])
        fr = {"fmt": d["fmt"], "w": w, "h": h, "pixels": pixels,
              "pad": bytes.fromhex(d["pad"]) if "pad" in d else None,
              "palpad": bytes.fromhex(d["palpad"]) if "palpad" in d else None}
        if pal is not None:
            if "colours" in d:
                pal = pal[:d["colours"]]
            fr["palette"] = pal
            fr["palextra"] = bytes.fromhex(d.get("palextra", ""))
        if d.get("tailnib") and pixels:
            fr["pixels"] = pixels[:-1] + bytes([pixels[-1] | d["tailnib"]])
        frames.append(fr)
    model = None
    if "model" in y:
        mo = y["model"]
        model = {"link": mo["link"], "recs": [list(r) for r in mo["recs"]], "rel": mo["rel"],
                 "rest": (src_dir / f"{name}.rest.bin").read_bytes()}
    return {"hdr": bytes.fromhex(y["hdr"]) if "hdr" in y else None,
            "hpad": bytes.fromhex(y["hpad"]) if "hpad" in y else None,
            "frames": frames, "model": model}
