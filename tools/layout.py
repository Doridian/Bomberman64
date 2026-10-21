#!/usr/bin/env python3
"""Work out Bomberman 64's top-level ROM layout from the ROM itself, and
write the stage-1 splat config (every piece a `bin`).

  layout.py <version>            write bm64.<version>.yaml
  layout.py --check <version>    check that bm64.<version>.yaml covers the
                                 ROM exactly (no gaps, no overlaps, every
                                 segment inside the ROM)
  layout.py --print <version>    print the segment list

What it reads (docs/LAYOUT.md has the details):

- The fixed low part: header, IPL3, boot_code at 0x1000 (to the start of
  zerojump, whose ROM range boot_code's entry DMAs: lui/addiu pairs at
  0x80000458..), the two ROM tables at 0x30000 and 0x30800, and main_code
  at 0x40000, which runs to the last non-zero byte before the first bank
  (rounded up to 16).
- The archives ("banks"): from 0x120000 on, every 0x20000 boundary that
  starts with the header `00002008 00000400` is an archive: a u32 data
  offset (always 0x2008), a u32 capacity (0x400), then (offset, size) u32
  pairs relative to the data offset, ended by 0xFFFFFFFF and filled with
  0xFF up to the data.  Entries are packed back to back.  The bank number
  is ROM offset >> 17 (0x30800's table holds them that way); bank 0x18 at
  0x300000 is the asset archive, the others hold the overlays.
- After an archive's last entry comes its tail up to the next bank (or the
  ROM's end): zeros, sometimes with one stray halfword at the 8-aligned
  end + 2 (left over from the build tool); it is kept as a bin.
"""
import argparse
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
VERSIONS = ("us", "eu")
ARCHIVE_MAGIC = bytes.fromhex("0000200800000400")
FIRST_BANK = 0x120000
BANK_STEP = 0x20000
ASSET_BANK = 0x300000


def u32(d, o):
    return struct.unpack_from(">I", d, o)[0]


def lui_addiu(d, rom, reg):
    """The 32-bit constant built in `reg` by the first lui/addiu pair
    from `rom` on (boot_code's entry, 0x1050)."""
    hi = lo = None
    for o in range(rom, rom + 0x40, 4):
        w = u32(d, o)
        op, rs, rt, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
        if op == 0x0F and rt == reg and hi is None:
            hi = imm
        elif op == 0x09 and rs == reg and rt == reg and hi is not None:
            lo = imm - 0x10000 if imm & 0x8000 else imm
            break
    assert hi is not None and lo is not None, hex(rom)
    return ((hi << 16) + lo) & 0xFFFFFFFF


def archive_entries(d, base):
    """(rom offset, size) of each entry of the archive at `base`, and the end
    of its table."""
    data = base + u32(d, base)
    o = base + 8
    out = []
    while True:
        off, size = struct.unpack_from(">II", d, o)
        if off == 0xFFFFFFFF:
            return out, o
        out.append((data + off, size))
        o += 8


def layout(d):
    """[(start, name, comment)] in ROM order, plus the ROM's end."""
    segs = [
        (0x0, "header", "ROM header"),
        (0x40, "boot", "IPL3 (CIC-NUS-6102)"),
        (0x1000, "boot_code", "VRAM 0x80000400; bss 0x8001BFC0..0x80028460"),
    ]
    # boot_code's entry (0x1050) DMAs zerojump: a2 = ROM start, t6 = end
    zj_start = lui_addiu(d, 0x1054, 6)
    zj_end = lui_addiu(d, 0x1054, 14)
    assert zj_start == 0x1CBC0, hex(zj_start)
    segs.append((zj_start, "zerojump", "loaded to 0x80042000, TLB-mapped at 0x00000000"))
    segs.append((zj_end, "pad_zerojump", "zeros"))
    segs.append((0x30000, "rom_header_table", "0x100 bytes, DMAd to 0x80024820 by boot_code"))
    segs.append((0x30100, "pad_30100", "zeros"))
    segs.append((0x30800, "bank_table", "0x1000 bytes, DMAd to 0x8019B0D0 by main_code; bank numbers"))
    segs.append((0x31800, "pad_31800", "zeros"))
    end = FIRST_BANK
    while d[end - 1] == 0:
        end -= 1
    main_end = (end + 15) & ~15
    segs.append((0x40000, "main_code", "VRAM 0x80225800, uncompressed"))
    segs.append((main_end, "pad_main_code", "zeros"))

    banks = [b for b in range(FIRST_BANK, len(d), BANK_STEP)
             if d[b:b + 8] == ARCHIVE_MAGIC]
    assert banks[0] == FIRST_BANK and ASSET_BANK in banks, banks
    for i, base in enumerate(banks):
        num = base >> 17
        entries, table_end = archive_entries(d, base)
        assert set(d[table_end:base + u32(d, base)]) <= {0xFF}, hex(base)
        what = "asset archive" if base == ASSET_BANK else "overlay archive"
        segs.append((base, f"bank{num:02X}", f"{what}: header, {len(entries)} entries"))
        width = 3 if len(entries) > 100 else 2
        pos = base + u32(d, base)
        for j, (start, size) in enumerate(entries):
            assert start == pos, (hex(base), j)  # packed back to back
            segs.append((start, f"bank{num:02X}_{j:0{width}d}", None))
            pos = start + size
        nxt = banks[i + 1] if i + 1 < len(banks) else len(d)
        assert pos <= nxt, hex(base)
        if pos < nxt:
            stray = any(d[pos:nxt])
            segs.append((pos, f"bank{num:02X}_tail",
                         "zeros and a stray halfword" if stray else "zeros"))
    return segs, len(d)


def write_yaml(version, segs, end):
    out = [
        f"name: Bomberman 64 ({version.upper()})",
        f"# Generated by tools/layout.py from baserom.{version}.z64; don't edit by hand.",
        "options:",
        "  platform: n64",
        "  compiler: IDO",
        f"  basename: bm64.{version}",
        "  base_path: .",
        f"  target_path: baserom.{version}.z64",
        f"  ld_script_path: bm64.{version}.ld",
        "  asset_path: assets",
        "segments:",
        "  - name: header",
        "    type: header",
        "    start: 0x0",
    ]
    for start, name, note in segs[1:]:
        line = f"  - [0x{start:X}, bin, {name}]"
        if note:
            line = f"{line:<40}# {note}"
        out.append(line)
    out.append(f"  - [0x{end:X}]")
    path = ROOT / f"bm64.{version}.yaml"
    path.write_text("\n".join(out) + "\n")
    return path


def read_yaml(version):
    import yaml
    cfg = yaml.safe_load((ROOT / f"bm64.{version}.yaml").read_text())
    starts = []
    for s in cfg["segments"]:
        if isinstance(s, dict):
            starts.append((s["start"], s["name"]))
        else:
            starts.append((s[0], s[2] if len(s) > 2 else None))
    return starts


def check(version):
    rom = (ROOT / f"baserom.{version}.z64").read_bytes()
    segs = read_yaml(version)
    if segs[0][0] != 0:
        sys.exit("first segment doesn't start at 0")
    if segs[-1][1] is not None or segs[-1][0] != len(rom):
        sys.exit(f"last entry must be the ROM's end [0x{len(rom):X}]")
    pieces = []
    for (a, name), (b, _) in zip(segs, segs[1:]):
        if b <= a:
            sys.exit(f"{name}: 0x{a:X} is not before 0x{b:X} (overlap or empty)")
        pieces.append(rom[a:b])
    if b"".join(pieces) != rom:
        sys.exit("the segments don't concatenate to the ROM")
    # and the config still matches what the ROM says
    want, end = layout(rom)
    if [(s, n) for s, n, _ in want] + [(end, None)] != segs:
        sys.exit(f"bm64.{version}.yaml differs from the ROM's layout; regenerate it")
    print(f"bm64.{version}.yaml: {len(segs) - 1} segments cover the ROM exactly")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("version", choices=VERSIONS)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--print", action="store_true")
    args = ap.parse_args()
    if args.check:
        check(args.version)
        return
    rom = (ROOT / f"baserom.{args.version}.z64").read_bytes()
    segs, end = layout(rom)
    if args.print:
        for (a, name, note), b in zip(segs, [s[0] for s in segs[1:]] + [end]):
            print(f"{a:08X}-{b:08X} {b - a:8X} {name:<20} {note or ''}")
        return
    print(write_yaml(args.version, segs, end).name)


if __name__ == "__main__":
    main()
