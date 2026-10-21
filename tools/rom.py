#!/usr/bin/env python3
"""Build the ROM from the code image and the archives.

  rom.py <version> --image build/<v>/code.bin --elf build/<v>/bm64.<v>.elf
         --out build/<v>/bm64.<v>.z64

The ROM is the image's first 0x120000 bytes (header, boot, boot_code,
zerojump, the two tables, main_code), then every archive in ROM order, each
built by tools/assets.py from assets/bankNN/.  An overlay entry comes from
the image instead (where the link put it: ovl_*_ROM_START/END), so a
rebuilt overlay goes into the ROM recompressed.  The header checksum is recomputed last.

Two tables tie the ROM's layout to the code:

- the segment size table (0x30000): byte n is the size of ROM segment n
  (n << 17) in 2 KiB units, 0 meaning 0x80000.  It is written here, from
  the build: segment 0 (boot_code and zerojump) from zerojump's end;
  main_code's two bytes from the link (2: what the boot thread reloads, up
  to main_code_PERSIST_START; 3: the rest, loaded once); an overlay bank's
  from its built size.  A byte is never lowered below the ROM's value
  except main_code's (bank 0x16's is 0x40 for 0x3800 bytes), and the
  asset archive's (0) is left alone: it is read entry by entry.
- the file table (0x30800): per file id, the segment and 2 KiB offset of
  the archive whose index lists it.  Banks don't move yet, so it is only
  checked: every overlay id has to point at its bank.
"""
import argparse
import subprocess
import sys
from pathlib import Path

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
import assets  # noqa: E402
import layout  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
SEGMENT_SIZES = 0x30000
FILE_TABLE = 0x30800


def units(size):
    """A size in the table's 2 KiB units (0x80000 is 0: both loaders read
    0 as 0x80000)."""
    n = (size + 0x7FF) >> 11
    if n == 0x100:
        return 0
    if n > 0xFF:
        sys.exit(f"0x{size:X} bytes doesn't fit the segment size table")
    return n


def elf_symbols(elf):
    out = {}
    nm = subprocess.run(["mips-linux-gnu-nm", elf], capture_output=True, check=True, text=True)
    for line in nm.stdout.splitlines():
        p = line.split()
        if len(p) == 3:
            out[p[2]] = int(p[0], 16)
    return out


def write_sizes(rom, syms, banks):
    """Fill in the segment size table in rom (the image's fixed part)."""
    sizes = rom[SEGMENT_SIZES:SEGMENT_SIZES + 0x100]
    sizes[0] = max(sizes[0], units(syms["zerojump_ROM_END"]))
    main = syms["main_code_ROM_START"] >> 17
    reload = syms["main_code_PERSIST_START"] - syms["main_code_VRAM"]
    assert reload % 0x800 == 0, hex(reload)
    sizes[main] = units(reload)
    sizes[main + 1] = units(syms["main_code_ROM_END"] - syms["main_code_ROM_START"] - reload)
    for base, data, _ in banks:
        if base != layout.ASSET_BANK:
            seg = base >> 17
            sizes[seg] = max(sizes[seg], units(len(data.rstrip(b"\0"))))
    rom[SEGMENT_SIZES:SEGMENT_SIZES + 0x100] = sizes


def check_tables(image, banks):
    """banks: [(rom start, built bytes, index or None)]"""
    files = image[FILE_TABLE:FILE_TABLE + 0x1000]
    bad = []
    for base, data, index in banks:
        seg = base >> 17
        for e in (index or {}).get("overlays", []):
            fseg, foff = files[2 * e["file"]], files[2 * e["file"] + 1]
            if (fseg << 17) + (foff << 11) != base:
                bad.append(f"file {e['file']}: table points at "
                           f"0x{(fseg << 17) + (foff << 11):X}, it is in bank{seg:02X}")
    if bad:
        sys.exit("tables don't match the archives:\n  " + "\n  ".join(bad))


def overlay_offsets(syms):
    """{(bank, entry): (start, end)} of the overlays in the linked image."""
    out = {}
    for name, start in syms.items():
        if name.startswith("ovl_") and name.endswith("_ROM_START"):
            _, b, e, _, _ = name.split("_")
            out[(int(b, 16), int(e))] = (start, syms[name[:-len("START")] + "END"])
    return out


def build(version, image_path, elf, assets_dir, out):
    image = Path(image_path).read_bytes()
    syms = elf_symbols(elf)
    offsets = overlay_offsets(syms)
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
    write_sizes(rom, syms, built)
    Path(out).write_bytes(rom)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("version", choices=layout.VERSIONS)
    ap.add_argument("--image", required=True)
    ap.add_argument("--elf", required=True, help="the code link, for the size table")
    ap.add_argument("--assets", default=ROOT / "assets")
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    build(a.version, a.image, a.elf, a.assets, a.out)


if __name__ == "__main__":
    main()
