#!/usr/bin/env python3
"""Build the ROM from the code image and the archives.

  rom.py <version> --image build/<v>/code.bin --out build/<v>/bm64.<v>.z64

The ROM is the image's first 0x120000 bytes (header, boot, boot_code,
zerojump, the two tables, main_code), then every archive in ROM order, each
built by tools/assets.py from assets/bankNN/.  An overlay entry comes from
the image instead (where bm64.<v>.yaml puts it), so a rebuilt overlay goes
into the ROM recompressed.  The header checksum is recomputed last.

Two tables tie the archives to the code, and are checked here:

- the segment size table (0x30000): byte n is the size of ROM segment n
  (n << 17) in 2 KiB units, 0 meaning 0x80000; every overlay bank has to
  fit (the asset archive is read entry by entry, not as a segment);
- the file table (0x30800): per file id, the segment and 2 KiB offset of
  the archive whose index lists it; every overlay id has to point at its
  bank.

They are data in the image for now; when banks can move, this is where
they get written.
"""
import argparse
import sys
from pathlib import Path

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
import assets  # noqa: E402
import layout  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
SEGMENT_SIZES = 0x30000
FILE_TABLE = 0x30800


def check_tables(image, banks):
    """banks: [(rom start, built bytes, index or None)]"""
    sizes = image[SEGMENT_SIZES:SEGMENT_SIZES + 0x100]
    files = image[FILE_TABLE:FILE_TABLE + 0x1000]
    bad = []
    for base, data, index in banks:
        seg = base >> 17
        room = (sizes[seg] << 11) or 0x80000
        used = len(data.rstrip(b"\0"))
        if used > room and base != layout.ASSET_BANK:
            bad.append(f"bank{seg:02X}: 0x{used:X} bytes, its table size is 0x{room:X}")
        for e in (index or {}).get("overlays", []):
            fseg, foff = files[2 * e["file"]], files[2 * e["file"] + 1]
            if (fseg << 17) + (foff << 11) != base:
                bad.append(f"file {e['file']}: table points at "
                           f"0x{(fseg << 17) + (foff << 11):X}, it is in bank{seg:02X}")
    if bad:
        sys.exit("tables don't match the archives:\n  " + "\n  ".join(bad))


def build(version, image_path, assets_dir, out):
    image = Path(image_path).read_bytes()
    offsets = layout.overlay_offsets(ROOT / f"bm64.{version}.yaml")
    rom = bytearray(image[:layout.FIRST_BANK])
    built = []
    for d in assets.bank_dirs(Path(assets_dir)):
        info = yaml.safe_load((d / "archive.yaml").read_text())
        base, num = int(info["rom"], 0), int(info["bank"], 0)
        override = {e: image[a:b] for (bk, e), (a, b) in offsets.items() if bk == num}
        data = assets.build_bank(d, override)
        if len(rom) != base:
            sys.exit(f"{d.name}: starts at 0x{base:X}, the ROM so far ends at 0x{len(rom):X}")
        rom += data
        index = d / "index.yaml"
        built.append((base, data, yaml.safe_load(index.read_text()) if index.exists() else None))
    check_tables(image, built)
    Path(out).write_bytes(rom)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("version", choices=layout.VERSIONS)
    ap.add_argument("--image", required=True)
    ap.add_argument("--assets", default=ROOT / "assets")
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    build(a.version, a.image, a.assets, a.out)


if __name__ == "__main__":
    main()
