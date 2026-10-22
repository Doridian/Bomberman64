#!/usr/bin/env python3
"""Self-test for the picture and model converters (tools/assetlib/bm64image.py,
bm64model.py).

Without a ROM (CI runs this): synthetic CI4, CI8 and RGBA32 files go to PNGs
and back byte for byte, and editing a pixel of a PNG changes the built
entry, through the same path `make` uses (assets.build_bank on a directory),
LZSS included.  Adding a colour or resizing moves what follows.  A synthetic
model (texture, palette, vertices, display list, nodes, pose, animation)
goes to its yaml and PNG and back; a vertex and a texel edit change only
those bytes, and a vertex more moves the rest and the references to it.

With baserom.<v>.z64 present (or --rom): every picture entry of bank 0x18
(129 in us and eu) is converted to PNGs and rebuilt to the ROM's own bytes,
and one pixel of a real entry is edited; the same for the 652 models (641, and
the 11 pictures with a model behind them), with
a vertex and a texel edited.

  test_assets.py [--rom us|eu ...]
"""
import argparse
import random
import struct
import sys
import tempfile
from pathlib import Path

import png
import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
import assets  # noqa: E402
import hudson_lzss  # noqa: E402
from assetlib import bm64image as B  # noqa: E402
from assetlib import bm64model as M  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent


def synthetic(rng):
    """A CI4 (odd size, with a pad nibble and a pad), a CI8 and an RGBA32
    frame, in a file with the 02 02 02 02 header."""
    ci4 = {"fmt": "ci4", "w": 5, "h": 3, "pad": None, "palpad": None,
           "palette": [rng.randrange(65536) for _ in range(7)], "palextra": b""}
    ci4["pixels"] = B.ci_pack("ci4", [rng.randrange(7) for _ in range(15)])[:-1] + b"\x07"
    ci4["pad"] = b"junk!"
    ci8 = {"fmt": "ci8", "w": 4, "h": 4, "pad": None, "palpad": None,
           "palette": [rng.randrange(65536) for _ in range(40)], "palextra": b""}
    ci8["pixels"] = bytes(rng.randrange(40) for _ in range(16))
    rgba = {"fmt": "rgba32", "w": 2, "h": 2, "pad": None, "palpad": None,
            "pixels": bytes(rng.randrange(256) for _ in range(16))}
    return {"hdr": None, "hpad": None, "frames": [ci4, ci8, rgba], "model": None}


def to_dir(data, name, d):
    """parse + dump `data` into directory d the way assets.py does."""
    m = B.parse(data)
    y = B.dump(m, name, d)
    (d / f"{name}.img.yaml").write_text(yaml.safe_dump(y, sort_keys=False, default_flow_style=None))


def build_entry(d, name, kind="img"):
    """The entry's bytes as `make` builds them: build_bank, then the entry
    back out of the archive and inflated."""
    (d / "archive.yaml").write_text(yaml.safe_dump({
        "bank": "0x18", "rom": "0x0", "slot": "0x100000", "tail": "",
        "entries": [{"file": f"{name}.{kind}.yaml", "lzss": True}]}))
    bank = assets.build_bank(d)
    off, size = struct.unpack_from(">II", bank, 8)
    data, used = hudson_lzss.decode(bank[assets.TABLE_SIZE + off:assets.TABLE_SIZE + off + size])
    return data


def edit_pixel(path, x, y, value):
    """Set pixel (x, y) of an indexed PNG (or one RGBA texel) to value."""
    w, h, rows, info = png.Reader(filename=str(path)).read()
    rows = [list(r) for r in rows]
    rows[y][x if "palette" in info else 4 * x] = value
    with open(path, "wb") as f:
        kw = {"palette": info["palette"]} if "palette" in info else {"greyscale": False, "alpha": True}
        png.Writer(w, h, bitdepth=info["bitdepth"], **kw).write(f, rows)


def test_synthetic():
    rng = random.Random(64)
    data = B.pack(synthetic(rng))
    assert B.parse(data) is not None, "synthetic file doesn't parse back"
    with tempfile.TemporaryDirectory() as t:
        d = Path(t)
        to_dir(data, "000", d)
        assert build_entry(d, "000") == data, "round trip"

        # a changed pixel changes the entry, and only that pixel
        edit_pixel(d / "000.0.png", 1, 1, 3)
        edit_pixel(d / "000.1.png", 2, 3, 39)
        edit_pixel(d / "000.2.png", 1, 0, 0x5A)
        new = build_entry(d, "000")
        assert len(new) == len(data) and new != data
        a, b = B.parse(data)["frames"], B.parse(new)["frames"]
        assert a[0]["pad"] == b[0]["pad"] and a[0]["pixels"][-1] == b[0]["pixels"][-1]
        assert B.ci_indices("ci4", b[0]["pixels"], 5, 3)[6] == 3
        assert B.ci_indices("ci8", b[1]["pixels"], 4, 4)[14] == 39
        assert b[2]["pixels"][4] == 0x5A
        diff = [i for i in range(len(data)) if data[i] != new[i]]
        assert len(diff) == 3, diff

        # a new colour (a longer palette) grows the entry, the rest follows
        w, h, rows, info = png.Reader(filename=str(d / "000.1.png")).read()
        pal = list(info["palette"]) + [(255, 0, 255, 255)]
        with open(d / "000.1.png", "wb") as f:
            png.Writer(w, h, palette=pal, bitdepth=8).write(f, [list(r) for r in rows])
        bigger = build_entry(d, "000")
        bf = B.parse(bigger)["frames"]
        assert len(bf[1]["palette"]) == 41 and bf[2]["pixels"] == b[2]["pixels"]
        assert bf[1]["palette"][:40] == b[1]["palette"]
    print("synthetic: round trip, pixel edit, palette growth")


def test_rom(version):
    rom = (ROOT / f"baserom.{version}.z64").read_bytes()
    entries, _ = assets.layout.archive_entries(rom, assets.layout.ASSET_BANK)
    n = 0
    first = None
    with tempfile.TemporaryDirectory() as t:
        d = Path(t)
        for i, (at, size) in enumerate(entries):
            data = assets.try_lzss(rom[at:at + size])
            if data is None or not B.is_image(data):
                continue
            name = f"{i:03d}"
            to_dir(data, name, d)
            assert build_entry(d, name) == data, f"entry {i}: round trip"
            assert assets.compress(data) == rom[at:at + size]
            first = first or (i, name, data)
            n += 1
        assert n == 129, f"{n} pictures"
        i, name, data = first
        edit_pixel(d / f"{name}.png" if (d / f"{name}.png").exists() else d / f"{name}.0.png", 0, 0, 1)
        new = build_entry(d, name)
        assert new != data and len(new) == len(data)
    print(f"{version}: {n} pictures rebuild byte for byte; an edit of entry {i} changes the entry")


# ---- models (tools/assetlib/bm64model.py) ----

def synthetic_model(rng):
    """A model with a 16x16 CI4 texture, its palette, four vertices, a
    display list that draws them, a node table, a pose, an animation and
    the type 7 words, as bytes (pack() of a hand-made model)."""
    tile = "cmt=0 maskt=4 shiftt=0 cms=0 masks=4 shifts=0"
    dl = ["settimg fmt=rgba siz=16b width=1 addr=pal_0", "tilesync",
          "settile fmt=rgba siz=4b line=0 tmem=0x100 tile=7 pal=0 " + tile, "loadsync",
          "loadtlut tile=7 colours=16", "pipesync",
          "settimg fmt=ci siz=16b width=1 addr=tex_0",
          "settile fmt=ci siz=16b line=0 tmem=0x0 tile=7 pal=0 " + tile, "loadsync",
          "loadblock uls=0 ult=0 tile=7 lrs=63 dxt=2048", "pipesync",
          "settile fmt=ci siz=4b line=1 tmem=0x0 tile=0 pal=0 " + tile,
          "settilesize uls=0 ult=0 tile=0 lrs=60 lrt=60",
          "vtx v0=0 n=4 addr=vtx_0", "tri2 a=0 b=1 c=2 d=2 e=3 f=0", "enddl"]
    vtx = [[x, y, 0, 0, 32 * x, 32 * y, 255, 255, 255, 255] for x, y in ((0, 0), (16, 0), (16, 16), (0, 16))]
    node = {"draw": 0, "pos": [0.0, 1.5, 0.0], "rot": [0.0, 90.0, 0.0], "scale": [1.0, 1.0, 1.0],
            "next": 0, "child": 0}
    m = {"hdr": M.DEFAULT_HDR, "last": 0,
         "recs": [[0, 0x3F800000, "dl_0"], [1, 0, "nodes_0"], [4, 0, 0], [2, 1, "poses_0"],
                  [3, 1, "anims_0"], [7, 4, "words_0"]],
         "blocks": [
             {"label": "tex_0", "kind": "tex", "align": 8, "bytes": bytes(rng.randrange(256) for _ in range(128))},
             {"label": "pal_0", "kind": "pal", "align": 8, "colours": [rng.randrange(65536) for _ in range(13)]},
             {"label": "vtx_0", "kind": "vtx", "align": 8, "vtx": vtx},
             {"label": "dl_0", "kind": "dl", "align": 8, "cmds": dl},
             {"label": "nodes_0", "kind": "nodes", "align": 8, "nodes": [node]},
             {"label": "poses_0", "kind": "poses", "align": 8, "poses": [
                 {"id": 0, "parts": [{"words": [0, 1], "pos": [0.0] * 3, "rot": [0.0, -60.0, 0.0],
                                      "scale": [1.0] * 3}]}]},
             {"label": "anims_0", "kind": "anims", "align": 8, "anims": [
                 {"id": 0, "length": 60, "tracks": [
                     {"tag": 0x30, "x": 0, "y": 60, "z": 1, "keys": [[0, 0.0], [60, 6.0]]},
                     {"tag": 0x2F, "x": 0, "keys": [[0, 1], [30, 0]]}]}]},
             {"label": "words_0", "kind": "words", "align": 8, "words": [0x11, 0x13, 0x15, 0x35, 0x33, 0x34]}]}
    return M.pack(m)


def model_dir(data, name, d):
    """parse + dump `data` into directory d the way assets.py does."""
    y = M.dump(M.parse(data), name, d)
    (d / f"{name}.mdl.yaml").write_text(M.to_yaml(y))


def model_yaml(d, name):
    return M.from_yaml((d / f"{name}.mdl.yaml").read_text())


def first_vtx(y):
    return next(e for e in y["blocks"] if "vtx" in e)


def test_model_synthetic():
    rng = random.Random(64)
    data = synthetic_model(rng)
    m = M.parse(data)
    kinds = [b["kind"] for b in m["blocks"]]
    assert kinds == ["tex", "pal", "vtx", "dl", "nodes", "poses", "anims", "words"], kinds
    with tempfile.TemporaryDirectory() as t:
        d = Path(t)
        model_dir(data, "000", d)
        assert build_entry(d, "000", "mdl") == data, "model round trip"

        # a vertex coordinate and a texel change the entry, and only them
        y = model_yaml(d, "000")
        first_vtx(y)["vtx"][1][0] = 17
        (d / "000.mdl.yaml").write_text(M.to_yaml(y))
        tex = next(e["label"] for e in y["blocks"] if "fmt" in e)
        edit_pixel(d / M.tex_png("000", tex), 3, 0, 9)
        new = build_entry(d, "000", "mdl")
        assert len(new) == len(data)
        diff = [i for i in range(len(data)) if data[i] != new[i]]
        assert len(diff) == 2, diff
        nm = M.parse(new)
        assert nm["blocks"][2]["vtx"][1][0] == 17
        assert nm["blocks"][0]["bytes"][1] & 15 == 9

        # one more vertex moves what follows, and the references with it
        first_vtx(y)["vtx"].append([8, 8, 8, 0, 0, 0, 255, 255, 255, 255])
        (d / "000.mdl.yaml").write_text(M.to_yaml(y))
        grown = build_entry(d, "000", "mdl")
        assert len(grown) == len(data) + 16
        gm = M.parse(grown)
        # the display list loads four, so a fresh parse sees the fifth as raw
        assert [b["kind"] for b in gm["blocks"]] == kinds[:3] + ["raw"] + kinds[3:]
        assert gm["blocks"][3]["bytes"] == struct.pack(">hhhHhhBBBB", 8, 8, 8, 0, 0, 0, 255, 255, 255, 255)
        assert struct.unpack_from(">I", grown, 0x14)[0] == struct.unpack_from(">I", data, 0x14)[0] + 16
        assert gm["blocks"][4]["cmds"] == nm["blocks"][3]["cmds"]
        assert gm["blocks"][6]["poses"] == m["blocks"][5]["poses"]
    print("synthetic model: round trip, vertex and texel edit, a table that grows")


def test_model_rom(version):
    rom = (ROOT / f"baserom.{version}.z64").read_bytes()
    entries, _ = assets.layout.archive_entries(rom, assets.layout.ASSET_BANK)
    n = 0
    sample = None
    with tempfile.TemporaryDirectory() as t:
        d = Path(t)
        for i, (at, size) in enumerate(entries):
            data = assets.try_lzss(rom[at:at + size])
            if data is None or not M.is_model(data):
                continue
            name = f"{i:03d}"
            model_dir(data, name, d)
            assert build_entry(d, name, "mdl") == data, f"entry {i}: model round trip"
            y = model_yaml(d, name)
            if sample is None and any("fmt" in e for e in y["blocks"]) and any("vtx" in e for e in y["blocks"]):
                sample = (i, name, data)
            n += 1
        assert n == 652, f"{n} models"
        i, name, data = sample
        y = model_yaml(d, name)
        first_vtx(y)["vtx"][0][1] += 1
        (d / f"{name}.mdl.yaml").write_text(M.to_yaml(y))
        tex = next(e["label"] for e in y["blocks"] if "fmt" in e)
        edit_pixel(d / M.tex_png(name, tex), 0, 0, 1)
        new = build_entry(d, name, "mdl")
        assert new != data and len(new) == len(data)
    print(f"{version}: {n} models rebuild byte for byte; a vertex and a texel edit of entry {i} change it")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--rom", nargs="*", choices=("us", "eu"), help="versions to check (default: those present)")
    a = ap.parse_args()
    test_synthetic()
    test_model_synthetic()
    for v in a.rom if a.rom is not None else [v for v in ("us", "eu") if (ROOT / f"baserom.{v}.z64").exists()]:
        test_rom(v)
        test_model_rom(v)


if __name__ == "__main__":
    main()
