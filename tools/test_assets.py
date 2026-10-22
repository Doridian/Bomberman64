#!/usr/bin/env python3
"""Self-test for the picture converter (tools/assetlib/bm64image.py).

Without a ROM (CI runs this): synthetic CI4, CI8 and RGBA32 files go to PNGs
and back byte for byte, and editing a pixel of a PNG changes the built
entry, through the same path `make` uses (assets.build_bank on a directory),
LZSS included.  Adding a colour or resizing moves what follows.

With baserom.<v>.z64 present (or --rom): every picture entry of bank 0x18
(129 in us and eu) is converted to PNGs and rebuilt to the ROM's own bytes,
and one pixel of a real entry is edited.

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


def build_entry(d, name):
    """The entry's bytes as `make` builds them: build_bank, then the entry
    back out of the archive and inflated."""
    (d / "archive.yaml").write_text(yaml.safe_dump({
        "bank": "0x18", "rom": "0x0", "slot": "0x100000", "tail": "",
        "entries": [{"file": f"{name}.img.yaml", "lzss": True}]}))
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
        assert len(bf[1]["palette"]) == 41 and bf[2]["pixels"] == b[2]["pixels"] and bf[1]["palette"][:40] == b[1]["palette"]
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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--rom", nargs="*", choices=("us", "eu"), help="versions to check (default: those present)")
    a = ap.parse_args()
    test_synthetic()
    for v in a.rom if a.rom is not None else [v for v in ("us", "eu") if (ROOT / f"baserom.{v}.z64").exists()]:
        test_rom(v)


if __name__ == "__main__":
    main()
