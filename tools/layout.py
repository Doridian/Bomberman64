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
# zerojump is DMAd to 0x80042000 and runs through the TLB at virtual 0.  It
# is split at its physical address: at 0, every zero word in the data
# would look like a pointer to it.
ZEROJUMP_VRAM = 0x80042000
MAIN_VRAM = 0x80225800
OVERLAY_VRAM = 0x80043000

# bss the ROM doesn't show.  boot_code's comes from its entry; main_code's
# is from the reference decomp (and covers every reference past its end);
# an overlay's is the extent of its references past its end (bss_size()).
MAIN_BSS = 0xE3D0
OVERLAY_SPACE = 0x20000   # the loader invalidates this much at 0x80043000

# opcodes that take rs + a signed 16-bit immediate: addiu, loads, stores
LO_OPS = {0x09, 0x20, 0x21, 0x23, 0x24, 0x25, 0x27, 0x28, 0x29, 0x2B,
          0x31, 0x35, 0x39, 0x3D, 0x37, 0x3F}


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


def writes(w):
    """The register an instruction writes, as far as pairing cares."""
    op = w >> 26
    if op == 0:
        return (w >> 11) & 31
    if op in (0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x20, 0x21,
              0x23, 0x24, 0x25, 0x27, 0x37):
        return (w >> 16) & 31
    if op == 3:
        return 31
    return None


def lui_pair(b, off, end):
    """The address a lui at b[off] makes with its pair (the next instruction
    that adds an immediate to its register or uses it as a base, before the
    register is written again), or None.  ori pairs are constants (IDO
    builds addresses with addiu)."""
    w = u32(b, off)
    reg, hi = (w >> 16) & 31, (w & 0xFFFF) << 16
    for o in range(off + 4, min(end, off + 4 * 64), 4):
        x = u32(b, o)
        op, rs = x >> 26, (x >> 21) & 31
        if op in LO_OPS and rs == reg:
            lo = x & 0xFFFF
            return (hi + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
        if x == 0x03E00008 or writes(x) == reg or (op == 0x0D and rs == reg):
            return None
    return None


def refs(b, vram):
    """Every address a module's code (lui pairs) and data (words) makes."""
    text_end, _ = text_split(b)
    out = set()
    for o in range(0, text_end, 4):
        if u32(b, o) >> 26 == 0x0F:
            a = lui_pair(b, o, text_end)
            if a is not None:
                out.add(a)
    for o in range(text_end, len(b) - 3, 4):
        out.add(u32(b, o))
    return out


def bss_size(b, vram, limit):
    """How far past its end, up to vram + limit, a module refers: its bss,
    rounded up to 16 (a reference is to the start of an object, so one
    more word is taken for the object it starts)."""
    end = vram + len(b)
    past = [a for a in refs(b, vram) if end <= a < vram + limit]
    return ((max(past) + 4 - end + 15) & ~15) if past else 0


def first_function_end(b):
    """The end of a module's first function (after its jr ra and delay
    slot), rounded up to 16: the module's entry, which the loader jumps to,
    so it is an object of its own and a shifted build pads after it."""
    for o in range(0, len(b), 4):
        if u32(b, o) == 0x03E00008:
            return (o + 8 + 15) & ~15
    raise ValueError("no jr ra")


def code_segment(name, start, vram, data, bss_size, first_hasm=None,
                 note=None, persist=None):
    """The YAML lines of one code segment of the image.  persist: the
    offset of main_code's part that is loaded once (see fixed())."""
    text_end, stubs = text_split(data)
    subs = []
    if first_hasm:
        subs.append((0, "hasm", first_hasm[1]))
        pos = first_hasm[0]
    else:
        pos = first_function_end(data)
        subs.append((0, "asm", f"{name}_entry"))
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
        # .data and .rodata as one block until the per-object split; as
        # rodata, so that spimdisasm labels the jump tables in it
        subs.append((text_end, "rodata", None))
    if persist is not None:
        assert text_end <= persist < len(data), hex(persist)
        subs.append((persist, "rodata", f"{name}_persist"))
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
            strings = blob.index(b"ZeroJump")
            assert strings % 16 == 0, hex(strings)
            out += [
                f"  - name: zerojump  # {note}",
                "    type: code",
                f"    start: 0x{start:X}",
                f"    vram: 0x{ZEROJUMP_VRAM:08X}",
                "    exclusive_ram_id: zerojump",
                "    subsegments:",
                f"      - [0x{start:X}, hasm, zerojump]",
                # its error strings follow the code (as text, but they
                # don't decode as instructions)
                f"      - [0x{start + strings:X}, rodata, zerojump_strings]",
            ]
        elif name == "main_code":
            # the boot thread reloads main_code up to segment_sizes[2] * 2 KiB
            # each time round, and loads the rest once (segment_sizes[3])
            persist = d[0x30000 + (start >> 17)] << 11
            out += code_segment(name, start, MAIN_VRAM, blob, MAIN_BSS, note=note,
                                persist=persist)
        else:
            line = f"  - [0x{start:X}, bin, {name}]"
            out.append(f"{line:<40}# {note}" if note else line)
    pos = FIRST_BANK
    for bank, entry, data in overlays(d):
        bss = bss_size(data, OVERLAY_VRAM, OVERLAY_SPACE)
        out += code_segment(overlay_name(bank, entry), pos, OVERLAY_VRAM, data, bss)
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
