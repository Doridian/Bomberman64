#!/usr/bin/env python3
"""Inventory of what the archives hold (phase 5, docs/ASSETS.md).

  inventory.py [us|eu ...]            summary (counts by class per bank)
  inventory.py --entries [us|eu]      one line per entry
  inventory.py --csv DIR              write DIR/inventory.<version>.csv
  inventory.py --check DIR            fail if those files are out of date
  inventory.py --diff                 entries that differ between us and eu

It reads the ROMs (baserom.<v>.z64), not assets/, so both versions work
without `make extract`. Research only: nothing here changes the build.

What it classifies. Overlay banks (0x09-0x17) are code: entry 0 is the
bank's index, the rest are overlays; they are listed as `code` and not
looked into. Bank 0x18 is the asset archive (873 entries). For each of its
entries, from the bytes alone:

  model       a "64" container (u32 0x36340038) with F3DEX display lists
              in it: the scanner finds the display lists, follows their
              G_VTX / G_SETTIMG / G_LOADTLUT, and sizes the textures from
              G_SETTILE / G_SETTILESIZE / G_LOADBLOCK
  model_nodl  a "64" container with no display list (collision shapes?)
  image       a "64" container of images: CI4 (kind 0x12), CI8 (0x15) or
              RGBA32 (0x19), each frame a pixel block and a palette
  stage_map   a plain table (byte 0 = a count) of tile maps, 5 + n*k bytes
  sound_seq   entry 32, "S2": MIDI-like sequences, an ALBankFile ("B1")
              and its samples
  sound_wave  entry 33, "T2": a table of 762 8-byte records, then waves
  audio_data  entries 71, 72: 32-byte blocks (not understood)
  table       small stored tables (entries 220, 221, 267)

The "64" container (docs/ASSETS.md, "The 64 container"): magic 0x3634,
u16 0x38, u32 N, 4 bytes of 02 (or 0), u32 kind, then N 12-byte records from
0x10: {u32, u32 offset, u32}. The display lists address the file as segment
2 (G_VTX/G_SETTIMG addresses 0x02xxxxxx are offsets into it).
"""
import argparse
import csv
import io
import struct
import sys
from collections import Counter, OrderedDict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import assets  # noqa: E402
import layout  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
MAGIC64 = bytes.fromhex("36340038")
KIND_IMAGE = {0x12: "ci4", 0x15: "ci8", 0x19: "rgba32"}
FMT = ("rgba", "yuv", "ci", "ia", "i")
SIZ = (4, 8, 16, 32)       # bits per texel
RAW_SOUND = {32: "sound_seq", 33: "sound_wave"}
RAW_AUDIO = {71: "audio_data", 72: "audio_data"}


def be32(d, o):
    return struct.unpack_from(">I", d, o)[0]


# ---------------------------------------------------------------------------
# F3DEX (1.21 "NoN", the microcode in main_code at 0xBF2F0) display lists

def _even_idx(v, n):
    return all(((v >> (8 * i)) & 0xFF) % 2 == 0 and ((v >> (8 * i)) & 0xFF) <= 0x7E
               for i in range(n))


def valid_cmd(d, o):
    """Whether the 8 bytes at o can be one F3DEX command with sane
    arguments. The checks are tight on purpose: data that happens to look
    like a command must not become a display list."""
    w0, w1 = struct.unpack_from(">II", d, o)
    c = w0 >> 24
    seg = w1 >> 24
    if c == 0x04:      # G_VTX: n vertices, (n * 16 - 1) bytes
        n = (w0 >> 10) & 0x3F
        v0 = (w0 >> 16) & 0xFF
        return (n >= 1 and (w0 & 0x3FF) == n * 16 - 1 and v0 % 2 == 0
                and v0 // 2 + n <= 32 and 1 <= seg <= 15 and w1 & 7 == 0)
    if c == 0xBF:      # G_TRI1
        return w0 == 0xBF000000 and seg == 0 and _even_idx(w1, 3)
    if c == 0xB1:      # G_TRI2
        return _even_idx(w0, 3) and seg == 0 and _even_idx(w1, 3)
    if c == 0xB8:
        return w0 == 0xB8000000 and w1 == 0
    if c == 0x06:      # G_DL (call or branch)
        return w0 in (0x06000000, 0x06010000) and 1 <= seg <= 15
    if c == 0x01:      # G_MTX
        return (w0 & 0xFFFF) == 0x40 and 1 <= seg <= 15 or seg == 0x80
    if c == 0x03:      # G_MOVEMEM
        return 1 <= seg <= 15
    if c == 0xBC:      # G_MOVEWORD: index in the low byte
        return (w0 & 0xFF) in (0, 2, 4, 6, 8, 0xA, 0xC, 0xE)
    if c == 0xBB:      # G_TEXTURE
        return (w0 & 0x00FF0000) == 0 and (w0 & 0xFF) in (0, 1, 2)
    if c in (0xB6, 0xB7):
        return w0 & 0xFFFFFF == 0
    if c in (0xB9, 0xBA):   # G_SETOTHERMODE_L/H
        return (w0 >> 16) & 0xFF == 0 and (w0 & 0xFF) != 0
    if c in (0xE6, 0xE7, 0xE8, 0xE9):
        return w0 == c << 24 and w1 == 0
    if c == 0xFD:      # G_SETTIMG
        return w0 & 0x7F000 == 0 and seg <= 15
    if c in (0xF5, 0xF3, 0xF2, 0xF0):
        return w1 >> 27 == 0 and (c != 0xF0 or w0 == 0xF0000000)
    if c == 0xFC:
        return True
    if c in (0xF7, 0xF8, 0xF9, 0xFB):
        return w0 & 0xFFFFFF == 0
    if c == 0xFA:
        return True
    if c in (0xBD, 0xBE):
        return True
    return False


STRONG = {0x04, 0xBF, 0xB1, 0xB8, 0xFD, 0xF5, 0xF3, 0xFC, 0xE7, 0xBB, 0xBC, 0x06, 0xF2, 0xF0, 0xE6, 0xE8}


def find_display_lists(d):
    """[(start, end)] of runs of valid commands that look like display
    lists (several distinct kinds of command, and a vertex load, a triangle
    or an end)."""
    runs = []
    o = 0
    n = len(d)
    while o + 8 <= n:
        if not valid_cmd(d, o):
            o += 8
            continue
        s = o
        while o + 8 <= n and valid_cmd(d, o):
            o += 8
        cmds = [d[x] for x in range(s, o, 8)]
        strong = {c for c in cmds if c in STRONG}
        if len(cmds) >= 3 and len(strong) >= 2 and strong & {0x04, 0xBF, 0xB1, 0xB8}:
            runs.append((s, o))
    return runs


def parse_display_lists(d, runs):
    """What the display lists reference.

    Returns a dict: vtx [(offset, n)], textures [(offset, bytes, fmt, bits,
    w, h)], palettes [(offset, colours)], segs {segment: count} for
    references outside segment 2 (textures supplied by other assets),
    ext [(segment, fmt, bits, w, h)], tris, cmds {name: count}."""
    out = {"vtx": [], "tex": [], "pal": [], "segs": Counter(), "ext": [],
           "tris": 0, "ncmd": 0, "ndl": len(runs), "enddl": 0}
    for s, e in runs:
        timg = None            # (fmt, siz, addr)
        loads = {}             # tile -> (addr, bytes) of the last load into it
        tile = {}              # tile -> (fmt, siz, line, tmem)
        last = None            # last texture load: (addr, bytes)
        for x in range(s, e, 8):
            w0, w1 = struct.unpack_from(">II", d, x)
            c = w0 >> 24
            out["ncmd"] += 1
            if c == 0x04:
                n = (w0 >> 10) & 0x3F
                seg, off = w1 >> 24, w1 & 0xFFFFFF
                if seg == 2 and off + 16 * n <= len(d):
                    out["vtx"].append((off, n))
                else:
                    out["segs"][seg] += 1
            elif c == 0xBF:
                out["tris"] += 1
            elif c == 0xB1:
                out["tris"] += 2
            elif c == 0xB8:
                out["enddl"] += 1
            elif c == 0xFD:
                timg = ((w0 >> 21) & 7, (w0 >> 19) & 3, w1)
            elif c == 0xF5:
                t = (w1 >> 24) & 7
                tile[t] = ((w0 >> 21) & 7, (w0 >> 19) & 3, (w0 >> 9) & 0x1FF, w0 & 0x1FF)
            elif c == 0xF3 and timg:      # G_LOADBLOCK
                texels = ((w1 >> 12) & 0xFFF) + 1
                nbytes = (texels << timg[1]) >> 1
                last = (timg[2], nbytes, timg[0], timg[1], "block")
            elif c == 0xF0 and timg:      # G_LOADTLUT
                count = (((w1 >> 12) & 0xFFF) >> 2) + 1
                seg, off = timg[2] >> 24, timg[2] & 0xFFFFFF
                if seg == 2 and off + 2 * count <= len(d):
                    out["pal"].append((off, count))
                else:
                    out["segs"][seg] += 1
            elif c == 0xF2:                # G_SETTILESIZE: the image's size
                t = (w1 >> 24) & 7
                if t in tile and last and t != 7:
                    fmt, siz = tile[t][0], tile[t][1]
                    w = (((w1 >> 12) & 0xFFF) - ((w0 >> 12) & 0xFFF) >> 2) + 1
                    h = (((w1 & 0xFFF) - (w0 & 0xFFF)) >> 2) + 1
                    seg, off = last[0] >> 24, last[0] & 0xFFFFFF
                    if seg == 2 and off + last[1] <= len(d):
                        out["tex"].append((off, last[1], FMT[fmt] if fmt < 5 else "?", SIZ[siz], w, h))
                    else:
                        out["segs"][seg] += 1
                        out["ext"].append((seg, FMT[fmt] if fmt < 5 else "?", SIZ[siz], w, h))
    return out


def merge_ranges(rs):
    out = []
    for a, b in sorted(rs):
        if out and a <= out[-1][1]:
            out[-1][1] = max(out[-1][1], b)
        else:
            out.append([a, b])
    return out


def uniq(items):
    return sorted(set(items))


# ---------------------------------------------------------------------------
# classification of one asset-archive entry

def records(d):
    """The container's N 12-byte records from 0x10, as (a, offset, b)."""
    n = be32(d, 4)
    out = []
    for i in range(n):
        o = 0x10 + 12 * i
        if o + 12 > len(d):
            break
        out.append(struct.unpack_from(">3I", d, o))
    return out


def classify_image(d, kind):
    recs = records(d)
    fmt = KIND_IMAGE[kind]
    # a record is {w << 16 | h, offset, ...} for a pixel block and {colours,
    # offset, ...} for the palette after it (a CI image's palette follows
    # its pixels, 16 or 256 colours of RGBA16)
    frames = []
    pals = 0
    for a, off, b in recs:
        w, h = a >> 16, a & 0xFFFF
        if w and h and 0 < off < len(d):
            frames.append((w, h))
        elif a and a < 0x10000 and off < len(d):
            pals += 1
    dims = Counter(frames)
    desc = ", ".join("%dx%d" % k + ("x%d" % v if v > 1 else "") for k, v in sorted(dims.items()))
    detail = "%s %s" % (fmt, desc)
    if fmt != "rgba32":
        detail += ", %d palettes" % pals
    return "image", fmt, detail, {"frames": len(frames), "pals": pals}


def classify_model(d):
    runs = find_display_lists(d)
    kind = be32(d, 12)
    n = be32(d, 4)
    if not runs:
        return "model_nodl", "kind%X" % kind, "N=%d, no display list" % n, {}
    p = parse_display_lists(d, runs)
    cover = merge_ranges([(0, 0x10 + 12 * n)] + runs + [(o, o + 16 * c) for o, c in p["vtx"]]
                         + [(o, o + b) for o, b, *_ in p["tex"]] + [(o, o + 2 * c) for o, c in p["pal"]])
    covered = sum(b - a for a, b in cover)
    nvtx = sum(c for o, c in {(o, c) for o, c in p["vtx"]})
    tex = uniq([(o, b, f, bits, w, h) for o, b, f, bits, w, h in p["tex"]])
    pals = uniq(p["pal"])
    formats = Counter("%s%d" % (f, bits) for o, b, f, bits, w, h in tex)
    parts = ["N=%d" % n, "%d dl" % len(runs), "%d tri" % p["tris"], "%d vtx" % nvtx]
    if tex:
        parts.append("tex " + " ".join("%s%d:%d" % (f, bits, c) for (f, bits), c in sorted(
            Counter((f, bits) for o, b, f, bits, w, h in tex).items())))
    if pals:
        parts.append("%d pal" % len(pals))
    ext = Counter(p["segs"])
    ext.pop(2, None)
    if ext:
        parts.append("ext seg " + ",".join(str(s) for s in sorted(ext)))
    parts.append("%d%% known" % (100 * covered // len(d)))
    info = {"ndl": len(runs), "tris": p["tris"], "vtx": nvtx, "tex": len(tex), "pal": len(pals),
            "formats": formats, "ext": sorted(ext), "known": covered, "size": len(d),
            "ext_tex": sorted(set(p["ext"]))}
    return "model", "kind%X" % kind, ", ".join(parts), info


def classify_asset(i, data, lzss):
    """(class, subtype, detail, info) of asset-archive entry i."""
    if i in RAW_SOUND:
        cls = RAW_SOUND[i]
        if cls == "sound_seq":
            n = struct.unpack_from(">H", data, 2)[0]
            return cls, "S2", "%d sequences + ALBankFile (B1 at 0x470)" % n, {}
        n = struct.unpack_from(">H", data, 2)[0]
        return cls, "T2", "%d records of 8 bytes, then waves" % n, {}
    if i in RAW_AUDIO:
        return "audio_data", "blocks", "%d blocks of 32 bytes after an 8-byte header" % ((len(data) - 8) // 32), {}
    if data[:4] == MAGIC64:
        kind = be32(data, 12)
        if kind in KIND_IMAGE:
            return classify_image(data, kind)
        return classify_model(data)
    # the stored tables and the stage maps
    if not lzss:
        return "table", "raw", "stored, %d bytes" % len(data), {}
    n = data[0]
    if 1 <= n <= 8 and len(data) >= 8 and data[5:7] in (b"\x06\x04", b"\x04\x04", b"\x02\x02"):
        per = (len(data) - 5) / n
        detail = "count %d x %d bytes, header %s" % (n, per, data[:8].hex()) if per == int(per) else \
            "count %d, %d bytes (not a multiple), header %s" % (n, len(data) - 5, data[:8].hex())
        return "stage_map", "%d" % n, detail, {"count": n}
    return "unknown", "", "first bytes " + data[:8].hex(), {}


def classify_asset_bank(entries, rom):
    rows = []
    for i, (at, size) in enumerate(entries):
        blob = rom[at:at + size]
        data = assets.try_lzss(blob)
        lzss = data is not None
        if data is None:
            data = blob
        cls, sub, detail, info = classify_asset(i, data, lzss)
        rows.append(OrderedDict(bank="18", entry=i, rom="%X" % at, stored=size, size=len(data),
                                lzss=int(lzss), cls=cls, sub=sub, detail=detail, _info=info))
    return rows


def classify_overlay_bank(num, entries, rom):
    rows = []
    for i, (at, size) in enumerate(entries):
        blob = rom[at:at + size]
        data = assets.try_lzss(blob)
        if i == 0 and data is None:
            rows.append(OrderedDict(bank="%02X" % num, entry=i, rom="%X" % at, stored=size, size=size,
                                    lzss=0, cls="code", sub="index", detail="overlay index (count byte, u16 id + u8 entry)",
                                    _info={}))
            continue
        rows.append(OrderedDict(bank="%02X" % num, entry=i, rom="%X" % at, stored=size,
                                size=len(data) if data is not None else size,
                                lzss=int(data is not None), cls="code", sub="overlay",
                                detail="overlay, not inspected", _info={}))
    return rows


def inventory(version):
    rom = (ROOT / f"baserom.{version}.z64").read_bytes()
    rows = []
    for num, base, slot_end in assets.banks(rom):
        entries, _ = layout.archive_entries(rom, base)
        if base == layout.ASSET_BANK:
            rows += classify_asset_bank(entries, rom)
        else:
            rows += classify_overlay_bank(num, entries, rom)
    return rows


# ---------------------------------------------------------------------------
# output

COLUMNS = ("bank", "entry", "rom", "stored", "size", "lzss", "cls", "sub", "detail")


def summary(rows):
    out = io.StringIO()
    banks = OrderedDict()
    for r in rows:
        banks.setdefault(r["bank"], []).append(r)
    out.write("bank  entries  bytes(inflated)  classes\n")
    for b, rs in banks.items():
        c = Counter(r["cls"] for r in rs)
        out.write("%-5s %7d  %15d  %s\n" % (b, len(rs), sum(r["size"] for r in rs),
                                            ", ".join("%s %d" % kv for kv in sorted(c.items()))))
    asset = banks.get("18", [])
    if asset:
        out.write("\nasset archive (bank 18), class / subtype:\n")
        c = Counter((r["cls"], r["sub"]) for r in asset)
        for (cls, sub), n in sorted(c.items()):
            size = sum(r["size"] for r in asset if r["cls"] == cls and r["sub"] == sub)
            out.write("  %-10s %-8s %4d entries %9d bytes\n" % (cls, sub, n, size))
        models = [r for r in asset if r["cls"] == "model"]
        out.write("\nmodels: %d display lists, %d triangles, %d vertices, %d textures, %d palettes\n" % (
            sum(r["_info"]["ndl"] for r in models), sum(r["_info"]["tris"] for r in models),
            sum(r["_info"]["vtx"] for r in models), sum(r["_info"]["tex"] for r in models),
            sum(r["_info"]["pal"] for r in models)))
        fmts = Counter()
        for r in models:
            fmts.update(r["_info"]["formats"])
        out.write("  embedded textures by format: " + ", ".join("%s %d" % kv for kv in sorted(fmts.items())) + "\n")
        ext = Counter()
        for r in models:
            ext.update(r["_info"]["ext"])
        out.write("  models that use segments other than 2: " + ", ".join(
            "seg %d: %d" % kv for kv in sorted(ext.items())) + "\n")
        known = sum(r["_info"]["known"] for r in models)
        total = sum(r["_info"]["size"] for r in models)
        out.write("  bytes the scanner accounts for: %d of %d (%.1f%%)\n" % (known, total, 100.0 * known / total))
    return out.getvalue()


def entry_lines(rows):
    out = io.StringIO()
    for r in rows:
        out.write("%s %3d %7X %8d %8d %s %-10s %-7s %s\n" % (
            r["bank"], r["entry"], int(r["rom"], 16), r["stored"], r["size"], "z" if r["lzss"] else "-",
            r["cls"], r["sub"], r["detail"]))
    return out.getvalue()


def csv_text(rows):
    out = io.StringIO()
    w = csv.writer(out, lineterminator="\n")
    w.writerow(COLUMNS)
    for r in rows:
        w.writerow([r[c] for c in COLUMNS])
    return out.getvalue()


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("versions", nargs="*", choices=layout.VERSIONS)
    ap.add_argument("--entries", action="store_true", help="one line per entry")
    ap.add_argument("--csv", type=Path, help="write inventory.<v>.csv into this directory")
    ap.add_argument("--check", type=Path, help="fail if inventory.<v>.csv there is out of date")
    ap.add_argument("--diff", action="store_true", help="list the entries that differ between us and eu")
    a = ap.parse_args()
    versions = a.versions or list(layout.VERSIONS)
    results = {v: inventory(v) for v in versions}
    status = 0
    for v, rows in results.items():
        if a.csv:
            a.csv.mkdir(parents=True, exist_ok=True)
            (a.csv / f"inventory.{v}.csv").write_text(csv_text(rows))
        elif a.check:
            path = a.check / f"inventory.{v}.csv"
            if not path.exists() or path.read_text() != csv_text(rows):
                print(f"{path}: out of date (run tools/inventory.py --csv {a.check})", file=sys.stderr)
                status = 1
        elif a.entries:
            print(f"# {v}")
            print(entry_lines(rows), end="")
        elif not a.diff:
            print(f"# {v}")
            print(summary(rows))
    if a.diff:
        if not {"us", "eu"} <= set(results):
            ap.error("--diff needs both versions")
        for line in diff_versions():
            print(line)
    sys.exit(status)


def diff_versions():
    """Entries (archive and bank number) whose inflated contents differ
    between us and eu."""
    roms = {v: (ROOT / f"baserom.{v}.z64").read_bytes() for v in layout.VERSIONS}
    out = []
    for num, base, slot_end in assets.banks(roms["us"]):
        ents = {}
        for v in layout.VERSIONS:
            ents[v] = layout.archive_entries(roms[v], base)[0]
        if len(ents["us"]) != len(ents["eu"]):
            out.append("bank %02X: %d entries in us, %d in eu" % (num, len(ents["us"]), len(ents["eu"])))
            continue
        for i, ((au, su), (ae, se)) in enumerate(zip(ents["us"], ents["eu"])):
            bu, be = roms["us"][au:au + su], roms["eu"][ae:ae + se]
            if bu != be:
                du, de = assets.try_lzss(bu), assets.try_lzss(be)
                out.append("bank %02X entry %d: us %d bytes, eu %d bytes (inflated %s / %s)" % (
                    num, i, su, se, len(du) if du is not None else "stored", len(de) if de is not None else "stored"))
    return out


if __name__ == "__main__":
    main()
