#!/usr/bin/env python3
"""Walk every file table in a Bomberman 64 ROM, decompress each compressed
entry, recompress it, and count the entries that come back byte for byte.

A file table (docs/COMPRESSION.md) is 0x2008 bytes of header -- u32 0x2008,
u32 0x400, then (offset, size) pairs ended by 0xFFFFFFFF -- and the entries
after it, at 0x2008 + offset.  An entry is compressed when its stream decodes
to exactly its size (the encoder's output padded to an even length).

  lzss_check.py ROM [--py] [-v]
"""
import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hudson_lzss  # noqa: E402

TABLE_MAGIC = bytes.fromhex("0000200800000400")


def tables(rom):
    """(table offset, [(entry ROM offset, size)])"""
    i = rom.find(TABLE_MAGIC)
    while i != -1:
        ents = []
        o = i + 8
        while struct.unpack_from(">I", rom, o)[0] != 0xFFFFFFFF:
            off, size = struct.unpack_from(">II", rom, o)
            ents.append((i + 0x2008 + off, size))
            o += 8
        yield i, ents
        i = rom.find(TABLE_MAGIC, i + 4)


def try_decode(rom, at, size):
    """The decoded data if the entry is a stream that fills it, else None."""
    if size < 4:
        return None
    try:
        data, used = hudson_lzss.decode(rom[:at + size], at)
    except IndexError:
        return None
    if used + (used & 1) != size or len(data) == 0:
        return None
    return data


def pad(stream):
    return stream + b"\0" * (len(stream) & 1)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("rom")
    ap.add_argument("--py", action="store_true", help="skip the C encoder")
    ap.add_argument("-v", action="store_true")
    a = ap.parse_args()
    rom = Path(a.rom).read_bytes()
    total = raw = ok = 0
    for tbl, ents in tables(rom):
        t_ok = t_c = 0
        for at, size in ents:
            total += 1
            data = try_decode(rom, at, size)
            if data is None:
                raw += 1
                continue
            t_c += 1
            got = pad(hudson_lzss.encode(data, a.py))
            if got == rom[at:at + size]:
                t_ok += 1
            elif a.v:
                print(f"  {at:#x}: {len(got):#x} vs {size:#x}")
        ok += t_ok
        print(f"{tbl:#08x}: {len(ents):4} entries, {t_c:4} compressed, "
              f"{t_ok:4} match")
    print(f"{total} entries: {raw} stored, {total - raw} compressed, "
          f"{ok} recompress exactly")
    return 0 if ok == total - raw else 1


if __name__ == "__main__":
    sys.exit(main())
