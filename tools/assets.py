#!/usr/bin/env python3
"""Bomberman 64's archives ("banks") as editable files, and back.

  assets.py extract <version>               ROM -> assets/bankNN/, checked,
                                            and the code image assets/code.bin
  assets.py build <version> --out DIR       assets/bankNN/ -> DIR/bankNN.bin

Every archive (docs/LAYOUT.md) becomes a directory `assets/bankNN/`:

- `archive.yaml`: the entries in order, each `{file, lzss}`, the bank's slot
  size (up to the next bank, or the ROM's end), and the non-zero start of
  its tail (the stray halfword some tails carry, as hex);
- one file per entry: `NN.bin` holds an LZSS entry inflated, `NN.raw` a
  stored one byte for byte;
- in an overlay bank, entry 0 is the bank's index (a count, then one
  `(u16 file id, u8 entry)` per overlay) and is written as `index.yaml`
  when it rebuilds to the same bytes.  bank0B's count (9) is more than
  the 7 records it has; `count` keeps such a count.

`extract` also writes the code image (tools/layout.py): what splat splits
and the code link rebuilds.  tools/rom.py builds the ROM from the rebuilt
image and these archives, taking the overlays from the image (`build_bank`'s
`override`).

`build` recompresses every LZSS entry (tools/hudson_lzss.py reproduces
Hudson's encoder exactly, docs/COMPRESSION.md) and packs the bank: the
0x2008-byte table, the entries back to back (each compressed one padded to
an even size), the tail, and zeros to the slot's end. A bank that outgrows
its slot is an error: code finds banks by number (ROM >> 17) and the asset
archive by address, so a bank can't move until stage 2 makes those
references symbols.

`extract` writes the files, builds them back and fails unless every bank
comes out as the ROM's bytes.
"""
import argparse
import struct
import sys
from pathlib import Path

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hudson_lzss  # noqa: E402
import layout  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
TABLE_SIZE = 0x2008
CAPACITY = 0x400


def banks(rom):
    """(bank number, ROM start, slot end) for every archive."""
    segs, end = layout.layout(rom)
    starts = [s for s, name, _ in segs if layout.is_bank(name)]
    for i, base in enumerate(starts):
        yield base >> 17, base, starts[i + 1] if i + 1 < len(starts) else end


def try_lzss(blob):
    """blob inflated, if it is exactly one padded LZSS stream, else None."""
    if len(blob) < 4:
        return None
    try:
        data, used = hudson_lzss.decode(blob)
    except IndexError:
        return None
    if used + (used & 1) != len(blob) or not data:
        return None
    return data


def compress(data):
    s = hudson_lzss.encode(data)
    return s + b"\0" * (len(s) & 1)


def parse_index(blob):
    """An overlay bank's entry 0, as YAML-able data, or None if it doesn't
    rebuild exactly."""
    if not blob:
        return None
    n = min(blob[0], (len(blob) - 1) // 3)
    ents = [{"file": struct.unpack_from(">H", blob, 1 + 3 * i)[0],
             "entry": blob[3 + 3 * i]} for i in range(n)]
    idx = {"overlays": ents, "size": len(blob)}
    if blob[0] != n:
        idx["count"] = blob[0]
    return idx if pack_index(idx) == blob else None


def pack_index(idx):
    out = bytearray([idx.get("count", len(idx["overlays"]))])
    for e in idx["overlays"]:
        out += struct.pack(">HB", e["file"], e["entry"])
    return bytes(out.ljust(idx["size"], b"\0"))


def pack_bank(entries, tail, slot):
    """entries: the entries' ROM bytes in order."""
    table = bytearray(struct.pack(">II", TABLE_SIZE, CAPACITY))
    off = 0
    for e in entries:
        table += struct.pack(">II", off, len(e))
        off += len(e)
    table += b"\xff\xff\xff\xff"
    if len(table) > TABLE_SIZE:
        raise ValueError(f"{len(entries)} entries: more than the table holds")
    out = bytes(table.ljust(TABLE_SIZE, b"\xff")) + b"".join(entries) + tail
    if len(out) > slot:
        raise ValueError(f"0x{len(out):X} bytes, slot is 0x{slot:X}")
    return out.ljust(slot, b"\0")


def extract_bank(rom, num, base, slot_end, out_dir):
    entries, _ = layout.archive_entries(rom, base)
    width = 3 if len(entries) > 100 else 2
    out_dir.mkdir(parents=True, exist_ok=True)
    manifest = []
    end = base + TABLE_SIZE
    for i, (at, size) in enumerate(entries):
        blob = rom[at:at + size]
        end = at + size
        data = try_lzss(blob)
        if data is not None and compress(data) != blob:
            sys.exit(f"bank{num:02X} entry {i}: inflates but doesn't recompress "
                     "to the ROM's bytes")
        if i == 0 and base != layout.ASSET_BANK and data is None:
            idx = parse_index(blob)
            if idx is not None:
                (out_dir / "index.yaml").write_text(yaml.safe_dump(idx, sort_keys=False))
                manifest.append({"file": "index.yaml", "lzss": False})
                continue
        name = f"{i:0{width}d}.{'bin' if data is not None else 'raw'}"
        (out_dir / name).write_bytes(data if data is not None else blob)
        manifest.append({"file": name, "lzss": data is not None})
    tail = rom[end:slot_end].rstrip(b"\0")
    info = {
        "bank": f"0x{num:02X}",
        "rom": f"0x{base:X}",
        "slot": f"0x{slot_end - base:X}",
        "tail": tail.hex(),
        "entries": manifest,
    }
    (out_dir / "archive.yaml").write_text(
        f"# bank{num:02X}: written by tools/assets.py extract\n"
        + yaml.safe_dump(info, sort_keys=False))


def build_bank(src_dir, override=None):
    """The bank's bytes.  override: {entry number: inflated bytes} used in
    place of the files (the overlays from the rebuilt code image)."""
    info = yaml.safe_load((src_dir / "archive.yaml").read_text())
    blobs = []
    for i, e in enumerate(info["entries"]):
        path = src_dir / e["file"]
        if override and i in override:
            assert e["lzss"], (src_dir, i)
            blobs.append(compress(override[i]))
        elif path.suffix == ".yaml":
            blobs.append(pack_index(yaml.safe_load(path.read_text())))
        elif e["lzss"]:
            blobs.append(compress(path.read_bytes()))
        else:
            blobs.append(path.read_bytes())
    try:
        return pack_bank(blobs, bytes.fromhex(info["tail"]), int(info["slot"], 0))
    except ValueError as err:
        sys.exit(f"{src_dir.name}: {err}")


def bank_dirs(assets):
    return sorted(p.parent for p in assets.glob("bank*/archive.yaml"))


def cmd_extract(version, assets):
    rom = (ROOT / f"baserom.{version}.z64").read_bytes()
    n = 0
    for num, base, slot_end in banks(rom):
        d = assets / f"bank{num:02X}"
        extract_bank(rom, num, base, slot_end, d)
        if build_bank(d) != rom[base:slot_end]:
            sys.exit(f"{d}: doesn't rebuild to the ROM's bytes")
        n += 1
    (assets / "code.bin").write_bytes(layout.image(rom))
    print(f"{n} banks extracted to {assets}/, all rebuild exactly; "
          f"code image in {assets}/code.bin")


def cmd_build(assets, out):
    out.mkdir(parents=True, exist_ok=True)
    for d in bank_dirs(assets):
        (out / f"{d.name}.bin").write_bytes(build_bank(d))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("cmd", choices=("extract", "build"))
    ap.add_argument("version", choices=layout.VERSIONS)
    ap.add_argument("--assets", type=Path, default=ROOT / "assets")
    ap.add_argument("--out", type=Path)
    a = ap.parse_args()
    if a.cmd == "extract":
        cmd_extract(a.version, a.assets)
    else:
        if a.out is None:
            ap.error("build needs --out")
        cmd_build(a.assets, a.out)


if __name__ == "__main__":
    main()
