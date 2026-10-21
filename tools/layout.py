#!/usr/bin/env python3
"""Work out Bomberman 64's layout from the ROM itself, and write the splat
config for the code image.

  layout.py <version>            write bm64.<version>.yaml
  layout.py --check <version>    check bm64.<version>.yaml against the ROM
  layout.py --print <version>    print the ROM's segment list

The ROM (docs/LAYOUT.md has the details):

- The fixed low part: header, IPL3, boot_code at 0x1000 (up to zerojump,
  whose ROM range boot_code's entry DMAs: lui/addiu pairs at 0x80000458..),
  the segment size table at 0x30000, the file table at 0x30800, and
  main_code at 0x40000, which runs to the last non-zero byte before the
  first bank (rounded up to 16).
- The archives ("banks"): from 0x120000 on, every 0x20000 boundary that
  starts with the header `00002008 00000400` is an archive: a u32 data
  offset (always 0x2008), a u32 capacity (0x400), then (offset, size) u32
  pairs relative to the data offset, ended by 0xFFFFFFFF and filled with
  0xFF up to the data.  Entries are packed back to back.  The bank number
  is ROM offset >> 17; bank 0x18 at 0x300000 is the asset archive, the
  others hold the overlays (entry 0 is the bank's index, the rest are
  LZSS-compressed overlays that run at 0x80043000).  After the last entry
  comes the tail up to the next bank: zeros, sometimes a stray halfword.
  Each archive is built by tools/assets.py.

The code image (`assets/code.bin`, written by `assets.py extract`) is what
splat splits and what the code link rebuilds: the ROM's first 0x120000
bytes as they are, then every overlay inflated, back to back in bank and
entry order.  tools/rom.py builds the ROM from it and the archives.

The config this writes covers the image: the code segments (boot_code,
zerojump, main_code, each overlay) with their text, ZeroJump stub block,
data and bss, and everything else as bins.  A segment's text ends after
its last `jr ra` (or ZeroJump stub), rounded up to 16, but before any RSP
code (a j/jal into IMEM), which belongs to the data.
"""
import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hudson_lzss  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
VERSIONS = ("us", "eu")
ARCHIVE_MAGIC = bytes.fromhex("0000200800000400")
FIRST_BANK = 0x120000
BANK_STEP = 0x20000
ASSET_BANK = 0x300000
CODE_IMAGE = "assets/code.bin"

BOOT_VRAM = 0x80000400
ZEROJUMP_VRAM = 0x00000000   # DMAd to 0x80042000, run through the TLB at 0
MAIN_VRAM = 0x80225800
OVERLAY_VRAM = 0x80043000

# bss the ROM doesn't show (boot_code's comes from its entry).  main_code's
# is from the reference decomp; the overlays' are worked out in stage 2.
MAIN_BSS = 0xE3D0


def u32(d, o):
    return struct.unpack_from(">I", d, o)[0]


def lui_addiu(d, rom, reg):
    """The 32-bit constant built in `reg` by the first lui/addiu pair
    from `rom` on."""
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


def is_bank(name):
    """Whether a ROM segment is an archive (built by tools/assets.py)."""
    return name.startswith("bank")


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


def bank_starts(d):
    banks = [b for b in range(FIRST_BANK, len(d), BANK_STEP)
             if d[b:b + 8] == ARCHIVE_MAGIC]
    assert banks[0] == FIRST_BANK and ASSET_BANK in banks, banks
    return banks


def fixed(d):
    """[(start, name, comment)] of the ROM below the first bank, and
    boot_code's bss size."""
    segs = [
        (0x0, "header", "ROM header"),
        (0x40, "boot", "IPL3 (CIC-NUS-6102)"),
        (0x1000, "boot_code", f"VRAM 0x{BOOT_VRAM:08X}"),
    ]
    # boot_code's entry (0x1050) DMAs zerojump: a2 = ROM start, t6 = end
    zj_start = lui_addiu(d, 0x1054, 6)
    zj_end = lui_addiu(d, 0x1054, 14)
    assert zj_start == 0x1CBC0, hex(zj_start)
    # the entry (0x1000) clears bss: lui/addiu t0 = start, ori t1 = size
    bss = lui_addiu(d, 0x1000, 8)
    assert u32(d, 0x1008) >> 16 == 0x3409, hex(u32(d, 0x1008))
    bss_size = u32(d, 0x1008) & 0xFFFF
    assert bss == BOOT_VRAM + zj_start - 0x1000, hex(bss)
    segs += [
        (zj_start, "zerojump", "DMAd to 0x80042000, TLB-mapped at 0x00000000"),
        (zj_end, "pad_zerojump", "zeros"),
        (0x30000, "segment_sizes", "u8 per 128 KiB ROM segment: size in 2 KiB units"),
        (0x30100, "pad_30100", "zeros"),
        (0x30800, "file_table", "u8 segment, u8 2 KiB offset per file id"),
        (0x31800, "pad_31800", "zeros"),
    ]
    end = FIRST_BANK
    while d[end - 1] == 0:
        end -= 1
    main_end = (end + 15) & ~15
    segs.append((0x40000, "main_code", f"VRAM 0x{MAIN_VRAM:08X}, uncompressed"))
    segs.append((main_end, "pad_main_code", "zeros"))
    return segs, bss_size


def layout(d):
    """[(start, name, comment)] of the whole ROM in order, plus its end."""
    segs, _ = fixed(d)
    banks = bank_starts(d)
    for i, base in enumerate(banks):
        num = base >> 17
        entries, table_end = archive_entries(d, base)
        assert set(d[table_end:base + u32(d, base)]) <= {0xFF}, hex(base)
        what = "asset archive" if base == ASSET_BANK else "overlay archive"
        pos = base + u32(d, base)
        for start, size in entries:
            assert start == pos, hex(base)  # packed back to back
            pos = start + size
        nxt = banks[i + 1] if i + 1 < len(banks) else len(d)
        assert pos <= nxt, hex(base)
        segs.append((base, f"bank{num:02X}",
                     f"{what}, {len(entries)} entries (assets/bank{num:02X}/)"))
    return segs, len(d)


def overlays(d):
    """(bank number, entry number, inflated data) of every overlay."""
    for base in bank_starts(d):
        if base == ASSET_BANK:
            continue
        entries, _ = archive_entries(d, base)
        for j, (at, size) in enumerate(entries[1:], 1):
            data, _ = hudson_lzss.decode(d[:at + size], at)
            yield base >> 17, j, data


def overlay_name(bank, entry):
    return f"ovl_{bank:02X}_{entry:02d}"


def is_stub(b, o):
    """A ZeroJump stub: `jr $zero` with `li $t0, id` in its delay slot."""
    return u32(b, o) == 0x00000008 and b[o + 4:o + 6] == b"\x24\x08"


def text_split(b):
    """(text end, (stub block start, end) or None) of a code module."""
    lim = len(b)
    for o in range(0, len(b), 4):
        w = u32(b, o)
        if w >> 26 in (2, 3) and 0x04001000 <= (w & 0x3FFFFFF) << 2 < 0x04002000:
            lim = o  # RSP code: data from here on
            break
    last = 0
    stubs = None
    o = 0
    while o < lim:
        if is_stub(b, o):
            start = o
            while o < lim and is_stub(b, o):
                o += 8
            if stubs is None or o - start > stubs[1] - stubs[0]:
                stubs = (start, o)
            last = o
            continue
        if u32(b, o) == 0x03E00008:
            last = o + 8
        o += 4
    return (last + 15) & ~15, stubs


def code_segment(name, start, vram, data, bss_size, first_hasm=None,
                 note=None):
    """The YAML lines of one code segment of the image."""
    text_end, stubs = text_split(data)
    subs = []
    pos = 0
    if first_hasm:
        subs.append((0, "hasm", first_hasm[1]))
        pos = first_hasm[0]
    if stubs and stubs[0] < text_end:
        # the block starts 16-aligned; whatever precedes it is code
        s0 = stubs[0] & ~15
        if s0 > pos:
            subs.append((pos, "asm", None))
        subs.append((s0, "hasm", f"{name}_zerojmp"))
        rest = (stubs[1] + 15) & ~15
        if rest < text_end:
            subs.append((rest, "asm", None))
    elif text_end > pos:
        subs.append((pos, "asm", None))
    if text_end < len(data):
        subs.append((text_end, "data", None))
    out = [
        f"  - name: {name}" + (f"  # {note}" if note else ""),
        "    type: code",
        f"    start: 0x{start:X}",
        f"    vram: 0x{vram:08X}",
    ]
    if bss_size:
        out.append(f"    bss_size: 0x{bss_size:X}")
    # Every code segment has a RAM id: an untagged one would be "global",
    # and splat makes one range of all of those, which the overlays'
    # 0x80043000 falls inside.  Segments with different ids see each
    # other's symbols; the overlays share one id and don't.
    if vram != OVERLAY_VRAM:
        out.append(f"    exclusive_ram_id: {name}")
    else:
        out += [
            "    exclusive_ram_id: overlay",
            f"    symbol_name_format: ovl{name[4:]}_$VRAM",
            f"    dir: overlays/{name}",
        ]
    out.append("    subsegments:")
    for off, kind, sub in subs:
        out.append(f"      - [0x{start + off:X}, {kind}" + (f", {sub}]" if sub else "]"))
    if bss_size:
        out.append(f"      - {{type: bss, vram: 0x{vram + len(data):08X}}}")
    return out


def config(version, d):
    """The YAML text of bm64.<version>.yaml, and the image's size."""
    segs, boot_bss = fixed(d)
    starts = [s for s, _, _ in segs] + [FIRST_BANK]
    out = [
        f"name: Bomberman 64 ({version.upper()}) code image",
        f"# Generated by tools/layout.py from baserom.{version}.z64; don't edit by hand.",
        "options:",
        "  platform: n64",
        "  compiler: IDO",
        f"  basename: bm64.{version}",
        "  base_path: .",
        f"  target_path: {CODE_IMAGE}",
        f"  ld_script_path: bm64.{version}.ld",
        "  asset_path: assets",
        "  asm_path: asm",
        "  src_path: src",
        "  build_path: build",
        f"  symbol_addrs_path: [symbol_addrs.{version}.txt]",
        "  undefined_funcs_auto_path: undefined_funcs_auto.txt",
        "  undefined_syms_auto_path: undefined_syms_auto.txt",
        "  find_file_boundaries: yes",
        "  ld_bss_is_noload: yes",
        "  mips_abi_float_regs: o32",
        "  string_encoding: ASCII",
        "segments:",
        "  - name: header",
        "    type: header",
        "    start: 0x0",
    ]
    for (start, name, note), end in zip(segs[1:], starts[2:]):
        blob = d[start:end]
        if name == "boot_code":
            out += code_segment(name, start, BOOT_VRAM, blob, boot_bss,
                                first_hasm=(0x50, "entry"), note=note)
        elif name == "zerojump":
            out += [
                f"  - name: zerojump  # {note}",
                "    type: code",
                f"    start: 0x{start:X}",
                f"    vram: 0x{ZEROJUMP_VRAM:08X}",
                "    exclusive_ram_id: zerojump",
                "    subsegments:",
                f"      - [0x{start:X}, hasm, zerojump]",
            ]
        elif name == "main_code":
            out += code_segment(name, start, MAIN_VRAM, blob, MAIN_BSS, note=note)
        else:
            line = f"  - [0x{start:X}, bin, {name}]"
            out.append(f"{line:<40}# {note}" if note else line)
    pos = FIRST_BANK
    for bank, entry, data in overlays(d):
        out += code_segment(overlay_name(bank, entry), pos, OVERLAY_VRAM, data, 0)
        pos += len(data)
    out.append(f"  - [0x{pos:X}]")
    return "\n".join(out) + "\n", pos


def image(d):
    """The code image's bytes."""
    return d[:FIRST_BANK] + b"".join(data for _, _, data in overlays(d))


def overlay_offsets(cfg_path):
    """{(bank, entry): (start, end)} in the code image, from a config."""
    import yaml
    segs = yaml.safe_load(Path(cfg_path).read_text())["segments"]
    starts = [s["start"] if isinstance(s, dict) else s[0] for s in segs]
    out = {}
    for s, end in zip(segs, starts[1:]):
        if isinstance(s, dict) and s["name"].startswith("ovl_"):
            _, b, e = s["name"].split("_")
            out[(int(b, 16), int(e))] = (s["start"], end)
    return out


def check(version):
    rom = (ROOT / f"baserom.{version}.z64").read_bytes()
    want, size = config(version, rom)
    have = (ROOT / f"bm64.{version}.yaml").read_text()
    if have != want:
        sys.exit(f"bm64.{version}.yaml differs from the ROM's layout; regenerate it")
    segs, _ = layout(rom)
    print(f"bm64.{version}.yaml: matches the ROM ({len(segs)} ROM segments, "
          f"code image 0x{size:X} bytes)")


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
    if args.print:
        segs, end = layout(rom)
        for (a, name, note), b in zip(segs, [s[0] for s in segs[1:]] + [end]):
            print(f"{a:08X}-{b:08X} {b - a:8X} {name:<20} {note or ''}")
        return
    text, _ = config(args.version, rom)
    path = ROOT / f"bm64.{args.version}.yaml"
    path.write_text(text)
    print(path.name)


if __name__ == "__main__":
    main()
