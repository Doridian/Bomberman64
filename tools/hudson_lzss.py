#!/usr/bin/env python3
"""Hudson's LZSS, as Bomberman 64 stores its overlays and assets.

It is Haruhiko Okumura's LZSS.C (1989) with N = 1024, F = 66, THRESHOLD = 2
and the window filled with zeros instead of spaces:

- a big-endian u32, the decompressed size, then the stream;
- a flag byte, read least significant bit first: 1 is a literal byte, 0 a
  two-byte match;
- a match is `lo, hi`: window position `lo | (hi & 0xC0) << 2`, length
  `(hi & 0x3F) + 3` (3 to 66);
- the window is 1024 zero bytes, written from 958 (N - F) on;
- there is no terminator: the decoder stops at the size, and the stream
  ends with the flag byte's last used bit (no padding).

encode() is Okumura's binary-tree encoder, with his tree and his
tie-breaking (the earliest node found at a length wins, a full-length match
replaces the old node); see docs/COMPRESSION.md for what it reproduces.
A C version of the same encoder (tools/src/hudson_lzss.c) is used when it
has been built, since this one is slow.

  hudson_lzss.py decompress IN OUT [--offset N]
  hudson_lzss.py compress IN OUT
"""
import argparse
import ctypes
import os
import struct
import sys
from pathlib import Path

N = 1024
F = 66
THRESHOLD = 2
NIL = N


def decode(src, pos=0):
    """Decompress the stream at src[pos:].  Returns (data, bytes consumed,
    including the size word)."""
    size = struct.unpack_from(">I", src, pos)[0]
    p = pos + 4
    window = bytearray(N)
    r = N - F
    out = bytearray()
    flags = 0
    while len(out) < size:
        flags >>= 1
        if not flags & 0x100:
            flags = 0xFF00 | src[p]
            p += 1
        if flags & 1:
            c = src[p]
            p += 1
            out.append(c)
            window[r] = c
            r = (r + 1) & (N - 1)
        else:
            lo, hi = src[p], src[p + 1]
            p += 2
            off = lo | (hi & 0xC0) << 2
            for k in range((hi & 0x3F) + THRESHOLD + 1):
                c = window[(off + k) & (N - 1)]
                out.append(c)
                window[r] = c
                r = (r + 1) & (N - 1)
    return bytes(out[:size]), p - pos


def _encode_py(data):
    text = bytearray(N + F - 1)
    lson = [NIL] * (N + 1)
    rson = [NIL] * (N + 257)
    dad = [NIL] * (N + 1)
    ml = mp = 0

    def insert(r):
        nonlocal ml, mp
        cmp = 1
        p = N + 1 + text[r]
        rson[r] = lson[r] = NIL
        ml = 0
        while True:
            if cmp >= 0:
                if rson[p] != NIL:
                    p = rson[p]
                else:
                    rson[p] = r
                    dad[r] = p
                    return
            else:
                if lson[p] != NIL:
                    p = lson[p]
                else:
                    lson[p] = r
                    dad[r] = p
                    return
            i = 1
            while i < F:
                cmp = text[r + i] - text[p + i]
                if cmp:
                    break
                i += 1
            if i > ml:
                mp = p
                ml = i
                if ml >= F:
                    break
        dad[r] = dad[p]
        lson[r] = lson[p]
        rson[r] = rson[p]
        dad[lson[p]] = r
        dad[rson[p]] = r
        if rson[dad[p]] == p:
            rson[dad[p]] = r
        else:
            lson[dad[p]] = r
        dad[p] = NIL

    def delete(p):
        if dad[p] == NIL:
            return
        if rson[p] == NIL:
            q = lson[p]
        elif lson[p] == NIL:
            q = rson[p]
        else:
            q = lson[p]
            if rson[q] != NIL:
                while rson[q] != NIL:
                    q = rson[q]
                rson[dad[q]] = lson[q]
                dad[lson[q]] = dad[q]
                lson[q] = lson[p]
                dad[lson[p]] = q
            rson[q] = rson[p]
            dad[rson[p]] = q
        dad[q] = dad[p]
        if rson[dad[p]] == p:
            rson[dad[p]] = q
        else:
            lson[dad[p]] = q
        dad[p] = NIL

    out = bytearray(struct.pack(">I", len(data)))
    if not data:
        return bytes(out)
    code = bytearray(17)
    cbp = 1
    mask = 1
    s = 0
    r = N - F
    pos = 0
    n = min(F, len(data))
    text[r:r + n] = data[:n]
    pos = n
    for i in range(1, F + 1):
        insert(r - i)
    insert(r)
    length = n
    while length > 0:
        if ml > length:
            ml = length
        if ml <= THRESHOLD:
            ml = 1
            code[0] |= mask
            code[cbp] = text[r]
            cbp += 1
        else:
            code[cbp] = mp & 0xFF
            code[cbp + 1] = ((mp >> 2) & 0xC0) | (ml - (THRESHOLD + 1))
            cbp += 2
        mask = (mask << 1) & 0xFF
        if mask == 0:
            out += code[:cbp]
            code[0] = 0
            cbp = mask = 1
        last = ml
        i = 0
        while i < last and pos < len(data):
            c = data[pos]
            pos += 1
            delete(s)
            text[s] = c
            if s < F - 1:
                text[s + N] = c
            s = (s + 1) & (N - 1)
            r = (r + 1) & (N - 1)
            insert(r)
            i += 1
        while i < last:
            i += 1
            delete(s)
            s = (s + 1) & (N - 1)
            r = (r + 1) & (N - 1)
            length -= 1
            if length:
                insert(r)
    if cbp > 1:
        out += code[:cbp]
    return bytes(out)


_lib = None


def _load_c():
    global _lib
    if _lib is None:
        _lib = False
        here = Path(__file__).resolve().parent
        for cand in (os.environ.get("HUDSON_LZSS_LIB"),
                     here.parent / "build/tools/libhudson_lzss.so"):
            if cand and Path(cand).exists():
                lib = ctypes.CDLL(str(cand))
                lib.hudson_lzss_encode.restype = ctypes.c_size_t
                lib.hudson_lzss_encode.argtypes = [
                    ctypes.c_char_p, ctypes.c_size_t, ctypes.c_char_p]
                _lib = lib
                break
    return _lib or None


def encode(data, force_py=False):
    """Compress data (with the size word)."""
    lib = None if force_py else _load_c()
    if lib is None:
        return _encode_py(bytes(data))
    buf = ctypes.create_string_buffer(4 + len(data) * 9 // 8 + 16)
    n = lib.hudson_lzss_encode(bytes(data), len(data), buf)
    return buf.raw[:n]


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    d = sub.add_parser("decompress")
    d.add_argument("input")
    d.add_argument("output")
    d.add_argument("--offset", type=lambda x: int(x, 0), default=0)
    c = sub.add_parser("compress")
    c.add_argument("input")
    c.add_argument("output")
    c.add_argument("--py", action="store_true", help="skip the C encoder")
    a = ap.parse_args()
    src = Path(a.input).read_bytes()
    if a.cmd == "decompress":
        data, used = decode(src, a.offset)
        Path(a.output).write_bytes(data)
        print(f"{used:#x} bytes -> {len(data):#x}", file=sys.stderr)
    else:
        Path(a.output).write_bytes(encode(src, a.py))


if __name__ == "__main__":
    main()
