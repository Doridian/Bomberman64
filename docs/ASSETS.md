# Assets

What the archives hold, how the game finds it, and what is known about each
format. This started as phase 5's inventory; the pictures ("Pictures as
PNGs") and the models ("Models as yaml") are converted to editable files
and rebuilt, the rest is still research. Offsets and addresses are US's
(`NBME`) unless said otherwise; the EU differences are in "US and EU" below.

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

A model is the container's header and records, then display lists, the
vertices, textures and palettes they load, and (for a hierarchy) a node
table, poses and animations. The records are a chain (as in the
pictures, below): each is `{a, offset, type of the next record}`, the
header's `kind` word is the type of record 0, and the last record's third
word is 0, or missing when `N` is odd. So `kind` is only the first
record's type (0 for 543 files, 5, 8, 6 or 1 for the others). The types,
from the code that reads them (`func_8022D58C` and `func_8022D414` in
`47A80.s` draw, `func_8022A6C4` and `func_8022AF1C` in `426E0.s` set up an
object):

| type | `a` | offset points to | read by |
| ---: | --- | --- | --- |
| 0 | 1.0 | a display list | `func_8022D58C`: `gSPSegment(2, file)`, `gSPDisplayList(file + offset)` |
| 5 | 1.0 | a display list, drawn under a pushed matrix that undoes the rotation (`func_8022928C` inverts the 3x3 of the current matrix times `D_802A5418` and drops the translation): a billboard | `func_8022D58C` |
| 6 | 1.0 | a display list, drawn after the code's own `D_8029FCC8` and a `G_SETTILESIZE` from `D_802A2D50` (a moving texture); the next record of another type gets `G_TEXTURE` off and texgen cleared | `func_8022D58C` |
| 8 | 1.0 | a display list, drawn with `G_TEXTURE_GEN` (0x40000) set (an environment map) | `func_8022D58C` |
| 1 | the root node | the node table | `func_8022D414`, recursively |
| 4 | 0 | nothing: the offset is left-over junk (`"0000"`, `"  0 "`, 41, ...) | nobody; it ends the parts before 2, 3, 7 |
| 2 | the number of pose groups | the poses | `func_8022AF1C` |
| 3 | the number of animations | the animations | `func_8022AF1C` |
| 7 | 4 | six u32s: `0x11, 0x13, 0x15, 0x35, 0x33, 0x34` in all 638 | `func_8022AF1C`, only when `a` is 4 |

The `a` of a display list record (1.0) is read by nothing found. An
object (`D_800A0D00`, 0x50 bytes) holds the file (`+0x3C`) and a record
index (`+0x38`); `func_8022A6C4` chooses it: the type 1 record if there is
one, else the first record of a type below 0x10, and with a type 3 record
the object is animated (`func_8022AF1C` builds the animation set,
`func_8022D1D0` its node tree). The ASCII words the inventory saw "in the
directory" are type 4's offsets.

**The node** (0x30 bytes, `func_8022D414` and `func_8022D280`): `s32` the
record to draw (-1: none); `f32[3]` a translation and `f32[3]` a rotation,
each applied only when not all zero (`func_8029CA80`, `func_8029C7A8`);
`f32[3]` a scale (1.0 in all 3442 nodes; the static draw doesn't read it);
`s32` the next sibling and `s32` the first child, both relative to the
node's own index (0: none). The table is as long as what the root reaches.

**Poses** (type 2, `func_8022AF1C`): `a` groups of `{u32 id, u32 m}` and
`m` parts of `{u32 c, c u32s, f32[9]}`. The nine floats are a translation,
a rotation and a scale (1.0 in all 5663); the u32s are all below the node
count (node indices, in pairs mostly).

**Animations** (type 3): `a` clips of `{u32 id, u32 m, u32 length}` and `m`
tracks, each `{0x30, u32 x, u32 y, u32 c, u32 z}` and `c` keys of `{u32
frame, f32 value}`, or `{0x2F, u32 c, u32 x}` and `c` pairs of u32s
(`func_8022AF1C` reads exactly these two shapes and nothing else). In all
289 tracks of the first kind `x` is 0, `y` is the clip's length and the
frames are sorted and within it; `z` is below the node count in 263.
Lengths are 1 to 1500 frames (60, 30, 75, 120 most often;
`func_8022827C` advances a clip's frame by 1.0 per call). The 0x2F
tracks' pairs (242 tracks) are not understood (open question 2).

Display lists are F3DEX 1.21 and address the model as segment 2: `G_VTX`
loads 16-byte vertices, `G_SETTIMG` + `G_LOADBLOCK` (or `G_LOADTILE`) +
the render tile's `G_SETTILE` a texture (its width is the tile's line,
its height the load's size), `G_SETTIMG` + `G_LOADTLUT` a palette (the
load's count is often 256 while the palette has fewer colours: the load
reads on into what follows, even past the file's end in 279), `G_DL` more
lists. Everything a model holds is reached that way, except 20 KB in 15
files that nothing in the file points at (below, "Models as yaml").

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

Models with no display list: **472** (168 bytes) is an empty hierarchy, a
node table of two nodes that draw nothing (`-1`), the type 4 record and
the six words: a placeholder. **79** (280 bytes) has one record, of type
4 (`{1.0, 0xC8}`), so nothing draws it; at 0xC8 there is a display list in
the older **Fast3D** encoding (`G_VTX` as `04 70 00 80`, the count less one
in bits 20-23; `G_TRI1` indices times 10, `00 00 0a 14`) with its addresses
in segment 0 (raw file offsets: vertices at 0x18 and 0x48). A leftover
from an earlier version of the engine; it stays raw bytes.

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
- The model format: the display list scanner's counts above are the
  inventory's heuristic; bm64model.py walks the display lists from the
  records instead (2689 lists, every command known, every byte placed but
  20 KB) and checks that each file packs back to itself. The numbers in
  "Models" (3442 nodes, 5663 pose parts, 289 + 242 tracks, ...) are from
  parsing all 652 files.

## Open questions

1. **The model format** is answered ("Models" above, "Models as yaml"
   below). Left: what the six words of the type 7 record (`0x11, 0x13,
   0x15, 0x35, 0x33, 0x34` everywhere) select (`func_8022AF1C` copies them
   to the animation set's `+0x00` and `+0x0C`); what the code's own display
   list `D_8029FCC8` does for a type 6 record; what the 20 KB that nothing in
   their files points at are for (textures and palettes in 241, 800, 389,
   ..., most likely swapped in by code); the model-swap table `D_80098C18`
   (five slots of `{count, object, files, record indices}`, `func_802280F4`)
   that `func_8022D58C` draws in place of an object's own record.
2. **Animation** is in the models (type 2 poses and type 3 animations, both
   decoded and editable). Left: what the tracks mean: a 0x30 track's `z`
   (below the node count in 263 of 289: a node, or a node and a channel),
   the 0x2F tracks' pairs, the poses' u32s (node indices, mostly in pairs),
   the ids; the players are `func_8022C8B8`, `func_8022BB88` and
   `func_8022827C` (`426E0.s`).
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
7. **Kinds 1, 4** are answered: the header's `kind` is the first record's
   type, 4 is an end marker, 79 is a Fast3D leftover and 472 an empty
   hierarchy ("Models").
8. **EU's longer sequences** (S2 sub-blocks 1 and 26): what was added.
9. **Unreferenced entries.** Some entries may be used by nothing in the
   code; a complete id table (3) will show it.

## Pictures as PNGs (phase 5, done)

`make extract` turns the 118 picture entries of bank 0x18 into PNGs, and
`make` builds them back into the same bytes (then recompresses the entry);
the other 11 pictures are in front of a model and go with it ("Models as
yaml"):
`tools/assetlib/bm64image.py` is the converter, `tools/assets.py` calls it,
`tools/test_assets.py` tests it (`make`-free; it reads baserom.*.z64 if present).

```
assets/bank18/NNN.img.yaml     the entry's metadata (archive.yaml lists it in place of NNN.bin)
assets/bank18/NNN.png          one frame;  NNN.F.png  frame F of several (366 PNGs in all)
assets/bank18/NNN.rest.bin     the model part of a hybrid, if the model converter can't take it (none)
```

- **CI4 and CI8** are indexed PNGs (4 and 8 bits) with the picture's palette
  in `PLTE` and the alpha bit in `tRNS`. **RGBA32** is an 8-bit RGBA PNG.
  RGBA16 colours widen the way the RDP does (5 bits to 8 by replicating the
  high bits) and narrow by a shift, so a PNG written by the tool reads back
  to the same bytes. Alpha is one bit: 128 and up is opaque.
- **Edit** a pixel or the palette in any editor that keeps an indexed PNG
  (GIMP, Aseprite; not "convert to RGB"), run `make`, and the entry
  changes. Palette entries are the PLTE's, so a CI4 picture can have up to
  16 and a CI8 up to 256; the picture's size is the PNG's. Everything after
  the edited frame moves with its size (offsets and the record table are
  regenerated, 8-aligned), and the archive build already lets an entry grow
  inside its slot.
- **`NNN.img.yaml`** has one line per frame, `{fmt, w, h}`, plus what a PNG
  can't carry, only when it isn't the default: `pad`/`palpad` (the bytes
  after the pixels or the palette, if not zeros up to the next multiple of
  8), `tailnib` (the unused low nibble of the last byte of an odd-sized CI4
  picture), `colours` (a palette shorter than the highest index used),
  `palextra` (palette bytes past 16 or 256 colours), `hdr` (header bytes
  8-11 if not `02 02 02 02`), and `model` for the hybrids.

### What the format turned out to be

Found while converting (the earlier text above is right but incomplete):

- **The records are a chain.** Each record is `{a, offset, type of the next
  record}`, the header's word at 0x0C is the type of record 0, and the last
  record's third word is 0. Types: `0x12` CI4 pixels, `0x15` CI8 pixels,
  `0x19` RGBA32 pixels, `0x16` RGBA16 pixels, `0x1a` a palette. So **the
  file's `kind` is only its first frame's format**: entry 68 mixes CI4 and
  CI8 frames (as do 304, 74-77, 452, ...), and the pair `{w << 16 | h,
  off, 0x1a}, {colours, off, next format}` is just the chain.
- When the record count `N` is odd the last record is 8 bytes and the data
  starts at `align8(0x10 + 12 N - 4)`: that is why the RGBA32 files of one
  frame have the pixels at 0x18 and only `0x10 + 8` bytes of table.
- The palette's count is the real number of colours (5, 6, 15, ...), not 16
  or 256. Pixel indices past it occur (872: indices up to 8 with 5 colours);
  the PNG palette is then padded up to the highest index and `colours`
  keeps 5. Entry 378 has a CI8 palette count of 290 (`palextra`).
- Pixel data is **packed, with no row padding**: 37 (151x19 CI4, "PRESS
  START") reads right only that way, and its odd last nibble is `7`.
  Between the 1435 pixel bytes and the palette it has the leftover text
  `bff 0xff7` (`pad`); 872 has 7 stray bytes after a palette.
- **11 "image" entries are hybrids** (452-458, 512, 803, 808, 838): the
  kind word says CI, the records start as pictures, and then the chain
  continues with `{0x3f800000, offset, ...}` model records, a model whose
  textures are the pictures at the front. The converter makes PNGs of the
  pictures and keeps the model records and its bytes (`NNN.rest.bin`)
  untouched; offsets in those records that point into the rest are stored
  relative to it (`model.rel` in the yaml), so they follow when a picture
  changes size. This was the stopgap until the models were decoded: now
  `tools/assets.py` converts the 11 with bm64model.py (pictures, model and
  display lists in one yaml), and bm64image.py's handling is the fallback.

### Reuse by the PC port

The port loads assets from the user's ROM at startup (`ASSET_INIT`, as in
Blast Corps): it inflates entries with `tools/hudson_lzss.py`'s algorithm
(C in the port) and needs the pictures as texel data, not PNG files. The
converter is written for that: `bm64image.parse(bytes)` gives
`{frames: [{fmt, w, h, pixels, palette}]}` and `pack()` is its inverse, both
pure functions on bytes and plain data with no build-tree knowledge; PNG is
only `write_png`/`read_png`/`dump`/`load`. A port that wants the user's
modded assets can read the same `NNN.img.yaml` + PNGs through `load()`.

## Models as yaml (phase 5, done)

`make extract` turns the 641 model entries of bank 0x18, and the 11 picture
files with a model behind them, into a yaml each and a PNG per texture, and
`make` builds them back into the same bytes: `tools/assetlib/bm64model.py`
is the converter, `tools/assets.py` calls it (an entry it couldn't take
would stay `NNN.bin`: none in us or eu), `tools/test_assets.py` tests it.

```
assets/bank18/NNN.mdl.yaml          the records and the blocks (archive.yaml lists it in place of NNN.bin)
assets/bank18/NNN.tex_XXXX.png      a texture (2202 PNGs in all)
```

**The yaml** has `records`, the chain (`{type, a, at}`), and `blocks`, the
file after the header in order. A block's label is its kind and its
offset in the ROM's file (`dl_06B8`, `vtx_08B8`, `tex_0058`); labels are
names and don't change when a block moves. `at` and every segment 2
address in a display list are a label, or `label+0xN` inside a block. An
address in another segment (3 to 14, the external textures) stays a
number, and so does type 4's junk offset.

| block | in the yaml |
| --- | --- |
| display list | `dl:`, one command per line, `name field=value ...`: `vtx v0=0 n=8 addr=vtx_08B8+0x180`, `tri2 a=0 b=1 c=2 d=2 e=3 f=0`, `settile fmt=ci siz=8b line=4 ...`, `loadtlut tile=7 colours=256`, `settimg fmt=ci siz=16b width=1 addr=tex_0058`, `moveword offset=0x20 index=10 data=0xFFFFFF00`, ... (F3DEX 1.21's opcodes; vertex indices as indices, not doubled; `raw 0xW0 0xW1` for a pair that isn't a known command: none in the ROM) |
| vertices | `vtx:`, one `[x, y, z, flag, s, t, r, g, b, a]` per vertex (r, g, b are a normal on lit models) |
| texture | `{fmt, w, h, pal, owner}` and `NNN.tex_XXXX.png`: CI4/CI8 indexed with their palette, RGBA16/32 as RGBA, as for the pictures |
| palette | `{colours: N}`: N colours, taken from the PLTE of the texture marked `owner` (the first texture drawn with all of it); a palette no texture shows would be a list of RGBA16 hex values (none) |
| node table | `nodes:`, `{draw, pos, rot, scale, next, child}` per node |
| poses | `poses:`, groups `{id, parts: [{words, pos, rot, scale}]}` |
| animations | `anims:`, `{id, length, tracks}`; a track is `{tag: 48, x, y, z, keys: [[frame, value]]}` or `{tag: 47, x, keys: [[u32, u32]]}` |
| type 7 | `words:`, the six u32s |
| anything else | `raw:` (hex) or `zeros:` (a count) |

Floats are written as YAML floats when they read back to the same bits
(all of them in the ROM), else as hex.

**Layout.** `pack()` puts each block after the one before; a block that
started on a multiple of 8 does so again, with zeros in between (the
ROM's zero gaps before an 8-aligned block are exactly that and aren't
kept; any other gap is a `raw` block). Then it resolves the labels. So a
block can grow or shrink, more vertices, a bigger texture, a longer
display list, and everything after it moves with the references to it.
What stays the editor's job: the commands that load a block (`vtx`'s
`n`, a texture's `loadblock`/`settile`/`settilesize` for another size,
`loadtlut`'s count) and, in the 11 hybrids, a picture record's `a` (`w <<
16 | h`, a colour count).

**How a file is cut** (`parse()`): the records give the display lists,
the node table (as long as what the root reaches), the poses and the
animations (whose shapes give their lengths), the type 7 words and, in
the hybrids, the pictures. Walking every display list (and the ones it
calls) gives the vertex runs (`G_VTX`), the palettes (`G_SETTIMG` +
`G_LOADTLUT`) and the textures (`G_SETTIMG` + `G_LOADBLOCK` or
`G_LOADTILE`, then the render tile's `G_SETTILE`: the width is the tile's
line, or the `G_SETTIMG` width for `G_LOADTILE`, and the height the load's
size; a CI texture's palette is the last `G_LOADTLUT` before it). Loads
of the same kind that overlap or touch are one block (vertex runs, a
smaller load of a texture); a palette is cut where the next block starts.
A block that doesn't decode and encode back to its bytes stays `raw`
(none), and `parse()` fails unless `pack()` gives back the input. In us
and eu: 2689 display lists, 2689 vertex blocks (1.95 MB), 2202 textures
(CI4 1883, CI8 313, RGBA32 6; 1.31 MB), 2196 palettes, 319 node tables,
125 pose and 125 animation blocks, 638 type 7 blocks, and 16 `raw` blocks
(20 KB) in 15 files: 79's Fast3D list ("Models"), and textures with their
palettes that nothing in their file loads (241: 7408 bytes, 800: 7728, 389,
391, 393, 395, 397 and 529: 528 each, 395 and 418: 544, ...).

**Edit** a vertex, a node, a key or a command in the yaml, a texel or a
palette colour in the owner's PNG (an indexed PNG stays indexed), and
`make`. A texture that isn't its palette's owner shows the palette in its
PNG, but its PLTE is ignored (a CI4 texture drawn with colours 16 n and on
of a bigger palette, `settile pal=n`, is never an owner).

### Reuse by the PC port (models)

`parse(bytes)` and `pack(model)` are pure functions on bytes and plain
data, like the pictures': a parsed model has its records, its display lists
as command text (`cmd_words()` gives the words back, with a resolver for
the labels), vertex rows, nodes, poses and animations. A port can draw a
model the way `func_8022D58C` does with any F3DEX 1.x display list
renderer, segment 2 being the inflated file, and animate it from the
decoded poses and tracks once their meaning is known (open question 2).

## Not yet

Stage maps, the stored tables and the sound entries are still
`NNN.bin`/`NNN.raw`. What they need:

- The ROM link places the bank by its contents' sizes: `rom.py` already packs
  archives from `assets/bankNN/` and refuses a bank that outgrows its
  slot. Bank 0x18's slot is 0x500000 (`0x300000-0x800000`) and US's
  contents end at `0x7B75A4`, so 0x48A5C bytes (290 KB) of room is left; an
  edited asset that grows costs the rest of the archive its position,
  which is fine because only the table of offsets changes (`0x300000`,
  segment 0x18, is hard-coded in `40FB0.s` and nowhere else).
- For the PC port: models need the segment 2/3.. rules, and the display
  lists need a F3DEX 1.x renderer (the same as Blast Corps' if it is
  F3DEX 1.x too), and the animation tracks' meaning (open question 2).
