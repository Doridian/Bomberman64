# Assets

What the archives hold, how the game finds it, and what is known about each
format. This is phase 5's first step, the inventory: research only, nothing
here is converted or rebuilt yet. Offsets and addresses are US's (`NBME`)
unless said otherwise; the EU differences are in "US and EU" below.

```
tools/inventory.py                  summary per bank (both versions)
tools/inventory.py --entries us     one line per entry
tools/inventory.py --csv docs       writes docs/inventory.us.csv, inventory.eu.csv
tools/inventory.py --check docs     fails if those files are out of date
tools/inventory.py --diff           the entries that differ between us and eu
```

It reads `baserom.<v>.z64` itself (through `tools/assets.py` and
`tools/layout.py`), so it needs no `make extract`, and it takes about three
seconds. Run it with `.env/bin/python3` (it imports `yaml` through
`assets.py`). The classification is by content only, and the heuristics
(the display list scanner above all) are in the file's comments.

## What there is

Everything that is not code is in one archive, **bank 0x18** (`0x300000`,
873 entries, 4.9 MB stored, 10.2 MB inflated). The other 14 archives
(banks 0x09-0x17, 95 overlays and their 14 index entries) are code and are
not looked into: `docs/LAYOUT.md` has them. Outside the archives there is
no asset data: the ROM below 0x120000 is the two code modules, zerojump and
the two tables (the segment size table and the file table, LAYOUT.md,
"Loaders"). The RSP microcode is in main_code's data (`0xBF2F0`, "RSP Gfx
ucode F3DEX.NoN 1.21", ROM `0xBF2F0`).

Counts by class, bank 0x18 (`tools/inventory.py us`):

| class | entries | stored | inflated | what it is |
| --- | ---: | ---: | ---: | --- |
| `model` | 639 | 2.14 MB | 5.03 MB | "64" container with F3DEX display lists (543 kind 0, 69 kind 5, 15 kind 8, 11 kind 6, 1 kind 1) |
| `image` | 129 | 0.50 MB | 1.72 MB | "64" container of pictures: 81 CI4, 31 CI8, 17 RGBA32 |
| `stage_map` | 96 | 0.09 MB | 1.26 MB | tile maps, a count byte and `n` records (not decoded) |
| `sound_seq` | 1 | 1.04 MB | 1.04 MB | entry 32, `"S2"`: 47 MIDI-like sequences and an ALBankFile |
| `sound_wave` | 1 | 1.08 MB | 1.08 MB | entry 33, `"T2"`: a table of 762 8-byte records, then waves |
| `audio_data` | 2 | 86 KB | 86 KB | entries 71, 72: 32-byte blocks (not understood) |
| `table` | 3 | 3.8 KB | 3.8 KB | entries 220, 221, 267, stored, read in place (not decoded) |
| `model_nodl` | 2 | | | entries 79, 472: a "64" container without a display list |

866 entries are Hudson-LZSS (`docs/COMPRESSION.md`); the 7 stored ones are
32, 33, 71, 72, 220, 221, 267. There is nothing else: no separate palette,
vertex or animation entries, no font entries (the fonts are images, and the
text is in main_code, below), no level geometry separate from the models.
EU has the same 873 entries in the same classes.

## How the game finds an entry

There are four ways, in increasing order of how raw they are.

**1. Overlays** (banks 0x09-0x17) go through the file table: LAYOUT.md,
"Loaders". The overlay loader is `func_8022691C(id)`.

**2. The asset archive's open-file API** (`40FB0.s`, `404C0.s`). The asset
archive is the one the game keeps open: `func_80226860` (called once at
startup) loads the file table and makes `0x300000` the open archive;
`func_802266E8(base)` opens an archive (it reads the 8-byte header,
`0x2008, 0x400`, to `D_8014B000`, and puts the table at `D_802A5300 =
base + 8`); `func_802267E0(n)` and `func_802267B0(a)` switch the open
archive to bank `n` (`n << 17`) or address `a`. An **entry id is the entry
number**: `func_80226604(id, flags)` opens it into one of the open-file
slots (0x14 bytes at `D_8014B808`: `{id, rom address, position, size,
flags}`), `func_8022616C(dst, size, count, handle)` reads from it through a
1 KiB buffer (`D_8014B8A8`, filled by `func_802260A8`), `func_80226304`
reads a byte, `func_80225CCC` seeks, `func_80226368` closes. The id's
high byte is the page of the archive's table (256 entries of 8 bytes, 0x800
bytes), and `func_80225E2C` swaps the right page in. The entry's offset and
size are just the `(offset, size)` pairs of LAYOUT.md.

**3. The asset cache** is how nearly everything is loaded: zerojump module
**0x14**, registered by `func_8026C990` with `D_802A13D0 = { func_8026CE28,
func_8026CCBC }`. Function 0 (call stub `li $t0, 0x1400`, or
`func_8026CE28` directly from main_code) is `get(id)`: it looks `id` up in
a 100-slot cache (`D_800A7F30`, 0x10 bytes per slot: `{id, pointer,
?, reference count}`), and on a miss opens the entry (`func_802267E0(0x18)`,
`func_80226604(id, 1)`), reads the u32 size, allocates it
(`func_802998EC`), and inflates it from the open file with
`func_80292BD0`, the streaming LZSS decoder. It returns the inflated
pointer. Function 1 releases it. So **an entry that goes through the cache
is always LZSS**: that is why the 7 stored entries are the other kind.

**4. Stored entries** are read raw: the sound init `func_8026C77C`
(`86680.s`) opens entries `0x20` and `0x21` (32 and 33), takes the
ROM address from each open file (offset 4) and hands it to the audio
code (`func_802690DC` for 32, `func_80267730` for 33), which reads the
ROM itself. Entries `0xDC` and `0xDD` (220, 221) and `0x10B` (267) are
opened and read with `func_80226604` / `func_8022616C` directly
(`93850.s`, `9CAB0.s`, `A2840.s`). Entries 71 and 72 are not LZSS either,
so they are read the same way; nothing with an immediate id was found.

Callers with an immediate id (found by scanning the asm for calls of the
cache's `get` with `li $a0, id` just before: 38 call sites in main_code and
the overlays, 9 distinct ids): 25 (call sites 0x80233E08, 0x8023B9CC, 0x802405A4), 62
(0x80242AE8), 63 (0x8023C25C), 304 and 305
(0x8023B0E4, 0x8023CED4, ...; CI4 sprite sheets of 16x16 x 11
and 10x18 x 13, so most likely digits), 600 (overlays 0F_01-0F_04 and 17_09; a CI4
16x16), 814 (0x8025D38C), 831 (0x80295D78; a CI8 215x45
picture), 846 (0x8022DEB0, 0x8023B02C; a CI4 16x16). All the other
ids come from tables or computations (18 of those 38 call sites load the
id from a register or memory). Only 6 of the 95 overlays (0B_02, 0F_01-0F_04,
17_09) call the cache's stub at all; how the others get their models is
open (below).

### Segments

The microcode is **F3DEX 1.21 (NoN)**: `RSP Gfx ucode F3DEX.NoN     1.21
Yoshitaka Yasumoto Nintendo.` at `0xBF2F0`. The commands in the data fit
F3DEX 1.x and not F3DEX2: `G_VTX` is `0x04` with `n << 10 | (16n - 1)`,
`G_TRI1` `0xBF`, `G_TRI2` `0xB1`, `G_ENDDL` `0xB8`, `G_TEXTURE` `0xBB`,
`G_MOVEWORD` `0xBC` with the index in the low byte, `G_SETOTHERMODE_L/H`
`0xB9/0xBA` (`bc00 200a rrggbb00` is a light colour set by MOVEWORD, as
F3DEX 1.x lights are).

The display lists address memory through segments, set by
`G_MOVEWORD G_MW_SEGMENT` (`0xBC000006 | seg << 10`, "`gSPSegment`"):

| segment | what the code puts there |
| --- | --- |
| 0 | 0 |
| 1 | a colour framebuffer: `0x100000 + 0x25800 * n` (320x240x2), set each frame at the start of `func_80227464` (`412F0.s`); the screen-capture textures use it |
| 2 | **the model itself**: the draw code (`func_8022D58C`, `47A80.s`; `func_80297564`, `B11F0.s`) writes `gSPSegment(2, asset pointer)` before each object's display lists. All offsets inside a model (`G_VTX`, `G_SETTIMG`, `G_DL`) are `0x02xxxxxx` and relative to the start of the inflated entry |
| 3..14 | the object's **external textures**: `func_802289C0` (`426E0.s`) walks the object's list of `{texture asset pointer, frame index}` and sets segment 3, 4, ... to `asset + record[frame].offset` (the 12-byte record's second word, below). A model's display list refers to them as `0x03000000` (`G_SETTIMG` and `G_LOADTLUT`) |

36 models use segment 3, 23 segment 4, and a few use up to 14 (entries 60,
73, 377, 389, 639, 663, ...).

## The "64" container

770 entries (all but the 103 above) start with `36 34 00 38`: `"64"` and a
u16 `0x38` (the game builds the same container at run time for screen
captures, `func_802957C0` and `func_80280814`, with magic `0x36340037`;
nothing checks the magic). The header:

| offset | meaning |
| --- | --- |
| 0x00 | `0x36340038` |
| 0x04 | `N`, the number of 12-byte records |
| 0x08 | 4 bytes: `02 02 02 02` in nearly all (0 in a few) |
| 0x0C | `kind` (u32) |
| 0x10 | `N` records of 12 bytes, `{u32 a, u32 offset, u32 b}` |

`kind` selects what the file is. The records are the file's directory;
offsets are from the start of the entry and the data follows the records.

### Images (129 entries)

`kind` is the pixel format: **0x12 CI4** (81 entries), **0x15 CI8** (31),
**0x19 RGBA32** (17), and **0x16 RGBA16** (the run-time screen capture,
never in the ROM). The records come in pairs for CI images: `{w << 16 | h,
offset of the pixel block, 0x1a}` and then `{colours, offset of the
palette, 0x12}`; an RGBA32 file has just the pixel records. The pixel
block is `w * h / 2` (CI4), `w * h` (CI8) or `w * h * 4` (RGBA32) bytes
rounded up to 8 and the palette (16 or 256 RGBA16 colours) follows it. Many
files are several frames of the same size (a sprite sheet: 24x24 x 12, 100x30 x 6, 16x16
x 11, ...), each with its own palette, and `func_802289C0` picks the
frame. Sizes in use: 16x16, 32x32, 64x64, 256 wide backgrounds (256x96,
256x192, 256x288, 256x384, 320x320, 320x240), a few odd pictures (151x19,
174x13, 264x197, 215x45). The RGBA32 files of 32x32 x 1 (12, 61, 511, 676,
...) are single-colour fills, and 35 is a 320x160 fill: probably
placeholders for textures the game draws into (they have one record and
a 0x18-byte header, where the others have 0x10 + 12 N).

### Models (639 entries)

A model is a header, display lists, the vertices and textures they use,
and a tail. `kind` is 0 (543), 5 (69), 8 (15), 6 (11) or 1 (1); what it
selects is not known (kind 0 is the plain case, 5 and 8 have more
records). The directory's first records are `{0x3f800000, offset of a
display list, ?}` (a float 1.0 and one record per display list: the
parts, or levels of detail, of the model); then come a few records whose
shape differs (`{0, offset, 4}` is a table of 0x30-byte nodes that start
`ff ff ff ff` and hold floats (1.0, 1.0, 1.0 at +0x1C: a scale); `{n, offset, 3}` and `{n, offset, 7}` look
like animation data; the last, `{4, offset, ...}`, points to a constant list
`0x11, 0x13, 0x15, 0x35, 0x33, 0x34, ...` that is the same in every model
checked). Two of the directory's entries are ASCII (`"    "`, `"# 1"`), so
the directory is not a plain array of the same record and `N` counts more
than the display lists. This part is the least understood.

What the scanner finds, over all 639 models (`tools/inventory.py us`):

| | count |
| --- | ---: |
| display lists | 2796 |
| triangles | 60243 |
| vertices (as loaded, `G_VTX` ranges counted once) | 121640 |
| textures embedded in the model | 2038 (CI4 1779, CI8 253, RGBA32 6) |
| palettes embedded | 2092 |
| bytes accounted for (header, display lists, vertices, textures, palettes) | 88.6% |

The textures, from `G_SETTIMG` / `G_SETTILE` / `G_SETTILESIZE` /
`G_LOADBLOCK`: 32x32 CI4 (1472 of them: 16 colours, 512 bytes), 32x32
CI8 (221), 16x16 CI4 (186), 64x64 CI4 (52), and a handful of 16x32,
32x16, 16x8, 32x64, 64x32, 128x32 CI4 and CI8. Palettes are loaded with
`G_LOADTLUT` from inside the model. Vertices are 16 bytes (`Vtx`: x, y, z
s16, flag, s, t, and four bytes of colour or normal) and sit, in the
files looked at, just before the display list that loads them. A
`G_VTX` loads up to 32 (the F3DEX 1.x vertex buffer), and many
display lists set the lights with `G_MOVEWORD(LIGHTCOL)`. The other 11%
is the tail: the node table and
whatever the `{n, offset, 3}` and `{n, offset, 7}` records point at (the
biggest, entries 800 and 639, are 70-80% tail: 800 has 57 KB from 0x68B0 to
0x15AA0 behind a `{0x64, 0x68B0, 3}` record, which is the biggest
candidate for animation data).

Models with no display list: 79 (280 bytes: 0x20 vertices after a
`{1.0, 0xC8, 0x20}` record, nothing draws it) and 472 (168 bytes, three
records, `0x30303030` where a record's second word is). They look like
collision or hit shapes.

### Stage maps (96 entries)

Byte 0 is a count `n` (1 to 6), bytes 1-4 are `00 00 00 xx` (`xx`: 0x02,
0x0A, 0x0E, 0x86, 0x8C, 0xA0, ...: a small id; 313 is `10 00 08 0A`),
bytes 5-6 are `06 04` (`04 04` in 307 and 309, `02 02` in 313), then `n`
records of **3123 bytes** each (2707, 2915 for the 04 04 ones, 523 for
313; 599 is 5729 bytes with n = 3, not a multiple). A record is two-byte
cells (`10 00`, `11 00`, `1f 00`, `16 00`, with a flag byte of `0x20` on
some) in rows of 0x80 bytes, each row started by a counter (`01 00 00`,
`02 00 00`, ...). The values are tile or block types and the shape fits a
Bomberman stage: the debug strings in main_code (`*** MAP INFORMATION
***`, `Layer :%d`, `Size  :%d x %d`, `Layer Unit`) print a map's layers
and size, so these are very likely the maps. How a record divides into
layers, and the meaning of the codes, is open.

### The stored tables (220, 221, 267)

Entry 220 (2882 bytes) is a **directory and its data**: 64 records of 7
bytes, `{u8 group (1-10), u8 kind (1 or 3), u8 number, u16 offset, u16
length}`, where each offset is the previous offset plus the previous length
(0, 0x1E, 0x51, 0x72, ...; the last ends at 2433), then 2434 bytes
those offsets point into (the records' lengths are 18 to 54). 221 (820
bytes) is 41 records of 20 bytes of small parameters
(`18 00 00 00 00 00 00 00 00 46 00 8C 01 00 30 01 04 05 3C 07`; the last
two are almost empty). 267 (92 bytes) is a table of small signed values
(`0A 03 72 FF F7 00 37 00 5A A0 08 2D ...`), not decoded. All three are
read in place with the open-file API (above), so they are configuration
tables (character or enemy parameters, perhaps), not data that goes
through the cache.

## Sound (entries 32 and 33, 2.1 MB)

**Entry 32, `S2`** (1,036,512 bytes in US, stored): `"S2"`, a u16 count of
0x2F, and 47 `(offset, size)` u32 pairs, sorted by nothing in particular,
pointing at the end of the file (0xE0D28 onward, and a few at 0xF4xxx). The
pairs address **MIDI-like sequences**: each starts with a u32 `0x44`, a
table of 16 track offsets (u32s, relative to the sequence), `0x1E0` (the
division, 480 ticks), and then events: `00 ff 51 04 92 ff` is a tempo
meta-event (`FF 51`, three bytes, with a delta time of 0 in front), `00
c0 66` a program change, `1e b0 07 78` a volume controller. Then, at 0x17C,
47 records of 16 bytes (`{volume | 0xFFFF, 0x470, 0x9448, 0x98B8}`: the
three constants are the starts of the regions below) and then, at **0x470, an
ALBankFile**: `42 31` (`"B1"`, the revision), a count of 3 banks and
their offsets (0x9020, 0x9228, 0x9248), libultra's `ALBank`,
`ALInstrument`, `ALSound` structures with their pointers relative to the
bank file. Raw samples (ADPCM-looking data) fill 0x98B8 to 0xE0D28.

**Entry 33, `T2`** (1,080,664 bytes, stored): `"T2"`, a u16 count of 0x2FA
(762), then 762 records of 8 bytes: `{u16 flags|index, u16 level, u16 index,
u16 rate}`; the last u16 is a sample rate in Hz (0x3E80 = 16000, 0x5622 =
22050, 0x2B11 = 11025, 0x4E20 = 20000, ...). After that (from 0x17D4) there
is a second header of offsets (0x17F8, 0xA830, 0xC028, 0xF4230, 0x100258)
and the wave data. How the three (S2's ALBankFile, T2's table, T2's data)
fit together is not worked out: libultra's ALBankFile points at its waves
by offset into a `.tbl`, and T2 is the obvious `.tbl`, but T2's own table
and S2's 0x98B8-0xE0D28 region do not fit that alone.

**Entries 71 and 72** (73,992 and 12,392 bytes, stored) are 8 bytes of
header (`00000000 00000108`, `00000000 00000068`) and then 32-byte blocks
(2312 and 387) that start with `00 00` and look like frames of coded audio
or of a table. 72 is mostly zeros. Unknown.

## Text and fonts

There is no text in the archive. The game's text is in **main_code's
data** (`0xBA9E8` to `0xBCCA8`): stage and menu names (`Untouchable`,
`Treasure`, `Switches`, `Bridges`, `Artemis`, `Avenger`, `Blizzard`, ...,
`Continue`, `Credits`, `Failure`) and the credits. It is **ASCII minus 0x27**
(`A` is 0x1A, `a` is 0x3A; a space stays 0x20): a custom encoding the
drawing code maps to the font sprites (the mapping was found by decoding
the strings, not from the code that reads them). The fonts are pictures: entries 304
and 305 (CI4 sprite sheets: 16x16 x 11 and 10x18 x 13) are digits and
symbols, and the large CI4 pictures are screens with their text drawn in
(the 256x96..256x384 backgrounds).

## US and EU

The 873 entries are the same in both versions except **entry 32**: 0xFDA58
bytes in EU against 0xFD0E0 (0x978 longer). Its 47 sub-blocks are the
same except two sequences: number 1 (0x28D0 bytes in US, 0x3150 in EU,
0x880 longer) and number 26 (0xF90, 0x1088, 0xF8 longer). Everything
else, the ALBankFile and the samples, is the same. There is no language
data: the text strings in main_code are identical in both versions (the
only difference is the build date string), and no asset is localised. So
the EU differences are sound (a different arrangement for 50 Hz, or
different music) and code. Three overlays also differ in content only
(bank 0x0B entry 1, bank 0x10 entry 13, bank 0x12 entry 5: same
compressed size), LAYOUT.md.

## Evidence and how to check

- Every number above is from `tools/inventory.py` (`docs/inventory.us.csv`
  and `.eu.csv`, one row per entry of every bank) or from the code at the
  addresses named. The code's asset path is `40FB0.s`, `404C0.s`,
  `87190.s` (the cache), `AD3D0.s` (the LZSS decoder), `86680.s` (sound
  init), `426E0.s` / `47A80.s` (the segments).
- Display lists: a run of 8-byte words is a display list only if every
  command's arguments are plausible (a `G_VTX` count and size that agree,
  triangle indices even and at most 0x7E, segment numbers 1-15, ...) and
  it holds a vertex load, a triangle or an end. 2796 runs; the model
  entries with none are 79 and 472. The textures check: sizes come out
  as powers of two, the byte counts as `w * h * bpp / 8`, and the palettes
  as 16 or 256 colours.
- Every LZSS entry inflates and recompresses to the ROM's bytes
  (`tools/assets.py extract`, `make lzss-check`).

## Open questions

1. **The model directory.** What `a` and `b` of each record mean, what
   `kind` means, the node table's 0x30-byte layout, the two ASCII
   "records", and whether `N` is just the sum of the sections. The code that
   walks it is `func_8022D58C`/`func_802289C0`/`func_8022D414`; reading
   them is the way in.
2. **Animation.** There is no animation entry. Whatever drives the models is
   in the tails (the `{n, offset, 3}` and `{n, offset, 7}` sections) or
   in the stage-map-like tables, or in the overlays' code.
3. **Which id is which.** Only 9 ids have immediate callers. The overlays'
   (and main_code's) asset id tables are the next thing to find: a table of
   u16/u32 ids below 873 in the `.data` of an overlay or main_code, indexed
   by a character, a stage, a menu. `docs/inventory.us.csv` gives each
   entry's class, so a table of ids shows what it points at.
4. **Stage maps.** The record layout (3123 bytes: layers and rows), the cell
   codes, and why 307, 309, 313 and 599 differ.
5. **The stored tables** 220, 221, 267 and the audio blocks 71, 72.
6. **Sound.** How S2's ALBankFile, S2's 0x98B8-0xE0D28 region and T2
   relate; T2's second header; the encoding of the samples (VADPCM, as
   libultra's would be, or something else); why the sequence blocks are
   not `ALSeqFile`s. The `func_802690DC` and `func_80267730` code is the way in.
7. **Kinds 1, 4** and the `00`-first-word records (79, 472).
8. **EU's longer sequences** (S2 sub-blocks 1 and 26): what was added.
9. **Unreferenced entries.** Some entries may be used by nothing in the
   code; a complete id table (3) will show it.

## What phase 5 needs next (proposals, nothing is done)

- `tools/assets.py` could split the 64 containers into `assets/bank18/`
  files (`NNN.png`, `NNN.yaml`, `NNN.dl`) the way Blast Corps' did, with
  the bytes it cannot explain kept as `rest` (the tail, the stray header
  bytes) so that a round trip is exact. The images are the easy first
  step: CI4/CI8 plus a palette, RGBA16 palette colours, RGBA32 pixels, each
  frame to a PNG; the record table and the 8-byte rounding are
  regenerated. Models need the directory (open question 1) before they
  can be rebuilt; until then a model is a `.dl` listing of its display
  lists, a `.vtx` of its vertices, and a `rest` blob.
- The ROM link places the bank by its contents' sizes: `rom.py` already packs
  archives from `assets/bankNN/` and refuses a bank that outgrows its
  slot. Bank 0x18's slot is 0x500000 (`0x300000-0x800000`) and US's
  contents end at `0x7B75A4`, so 0x48A5C bytes (290 KB) of room is left; an
  edited asset that grows costs the rest of the archive its position,
  which is fine because only the table of offsets changes (`0x300000`,
  segment 0x18, is hard-coded in `40FB0.s` and nowhere else).
- For the PC port: the archive can be read from the user's ROM at startup
  (the open-file API above is the only reader; the cache's `get(id)` is
  the one entry point that matters), models need the segment 2/3.. rules,
  and the display lists need a F3DEX 1.x renderer (the same as Blast Corps'
  if it is F3DEX 1.x too).
