# Compression and file tables

Everything in the ROM from `0x120000` on is in **file tables**, and almost
every entry in them is compressed with **Hudson's LZSS**. `tools/hudson_lzss.py`
compresses and decompresses it, and `tools/lzss_check.py ROM` checks the
encoder against a ROM. Below `0x120000` (boot, the boot segment at `0x1000`,
the main code at `0x40000`) nothing is compressed.

## The stream

It is Haruhiko Okumura's `LZSS.C` (1989) with different constants and a
zero-filled window:

| field | value |
| --- | --- |
| header | big-endian u32: the decompressed size |
| window | `N = 1024` bytes, all zero, first written at `N - F = 958` |
| flags | one byte per 8 items, least significant bit first; `1` = literal byte, `0` = match |
| match | two bytes `lo, hi`: position `lo \| (hi & 0xC0) << 2`, length `(hi & 0x3F) + 3` (3–66, `F = 66`, `THRESHOLD = 2`) |
| end | none: the decoder stops at the size; the last flag byte's spare bits are 0 |

A match's position is an absolute window position, not a distance, the same
as in Okumura's code. Matches can reach back into the initial zeros.

## The encoder

`encode()` is Okumura's binary-tree encoder, changed only in the constants,
the zero fill, and the bit layout of the match's second byte. Taking it
unchanged reproduces every compressed entry exactly. That means his tree
(the 256 roots by first byte), his tie-breaking (the first node found at a
new length wins, and a full `F`-byte match replaces the old node), and the
`F` insertions of the zero-filled positions before the first byte. No
variant search was needed.

The Python encoder runs at about 15 s/MB. `tools/src/hudson_lzss.c` is the
same encoder in C, and `hudson_lzss.py` uses it through ctypes when
`build/tools/libhudson_lzss.so` exists (or `$HUDSON_LZSS_LIB` points to it):

    cc -O2 -shared -fPIC -o build/tools/libhudson_lzss.so tools/src/hudson_lzss.c

With it a whole-ROM check takes about 5 s instead of 90 s. `--py` forces the
Python path.

## File tables

A table starts on a 0x20000 boundary:

| offset | content |
| --- | --- |
| `0x0` | u32 `0x2008`: where the entries start, from the table |
| `0x4` | u32 `0x400`: the number of slots (`0x400 × 8 = 0x2000`) |
| `0x8` | `(u32 offset, u32 size)` per entry, offsets from `0x2008`, ended by `0xFFFFFFFF`, rest `0xFF` |
| `0x2008` | the entries, packed back to back |

Each compressed entry is the stream padded with one zero byte to an even
size. The `size` field includes that byte.

Both ROMs have the same 15 tables:

- **`0x120000`–`0x2E0000`: 14 overlay banks** (`0x220000` is skipped because
  `0x200000`'s bank runs past it). Entry 0 of each bank is stored, not
  compressed. It is an index: a count byte, then one `(u16 file id, u8 entry
  number)` per remaining entry, padded to even (e.g. `0x120000`: count 4, ids
  `0x14`–`0x17`). The other entries are compressed code overlays (109 entries
  in all, 95 of them compressed).
- **`0x300000`: the asset table**, 873 entries to the end of the data (US
  `0x7B75A4`, EU `0x7B7F1C`). Seven entries are stored. Two of them start
  with `S2`/`T2`-style magic (`0x30A898`, 1 MB; `0x407978`, 1 MB; probably
  sound bank data), and the other five are small. The rest are compressed.

The gaps between tables are zeros, with one exception. Seven tables (and
the US ROM's tail) have a stray u16 eight bytes past their last entry
(`0x4009`, `0x4011`, …), left over from Hudson's build tool. A ROM builder has to keep the
ROM's pad bytes rather than zero-fill.

## Results

`tools/lzss_check.py` on each ROM:

| ROM | entries | stored | compressed | recompress exactly |
| --- | --- | --- | --- | --- |
| us | 982 | 21 | 961 | **961** |
| eu | 982 | 21 | 961 | **961** |

Nothing is left unresolved for the stream. Still open: what the stored
`S2`/`T2` blobs and the five small stored assets are, and what the file
ids in the overlay index mean (which loader reads them).
