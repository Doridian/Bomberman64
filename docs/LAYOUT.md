# ROM layout

The map of Bomberman 64 (1997), US (`NBME`), EU (`NBMP`) and JP
(`NBMJ`, *Baku Bomberman*).
`tools/layout.py <version>` derives it from the ROM and writes
`bm64.<version>.yaml`, the splat config of the code image ("Stage 2",
below). `tools/assets.py` splits the archives into their entries
(`assets/bankNN/`) and builds them back. `tools/layout.py --check
<version>` checks that the config still matches what the ROM says, and
`tools/layout.py --print <version>` prints the ROM's segment list.

All three ROMs are 8 MiB, CIC-NUS-6102, entry point `0x80000400`.

## US

| ROM range | VRAM | size | kind | notes |
| --- | --- | --- | --- | --- |
| `000000-000040` | | 0x40 | header | |
| `000040-001000` | `A4000040` | 0xFC0 | boot | IPL3 (6102) |
| `001000-01CBC0` | `80000400` | 0x1BBC0 | code+data | **boot_code**: entry, scheduler (`sched.c`), libultra, audio library. IPL3 copies the first MiB from 0x1000 to 0x80000400; the entry clears bss `8001BFC0-80028460` (0xC4A0) and jumps to `800019A0` |
| `01CBC0-01CCF0` | `80042000` | 0x130 | code+data | **zerojump**: boot_code's entry DMAs it to `80042000`; `osMapTLB` maps it at virtual `00000000`. "ZeroJump Error : unset segment/function" strings |
| `01CCF0-030000` | | | pad | zeros |
| `030000-030100` | `80024820` | 0x100 | data | **segment size table** ("Loaders", below): boot_code DMAs it into its bss |
| `030100-030800` | | | pad | zeros |
| `030800-031800` | `8019B0D0` | 0x1000 | data | **file table** ("Loaders"): main_code DMAs it |
| `031800-040000` | | | pad | zeros |
| `040000-0BFB00` | `80225800` | 0x7FB00 | code+data | **main_code**, uncompressed, ROM segment 2. Its init clears its bss, `802A5300-802B36D0` (0xE3D0) |
| `0BFB00-120000` | | | pad | zeros |
| `120000-2EF0CE` | `80043000` | | compressed archives | overlay banks 0x09-0x17 (below); an overlay is inflated to `80043000` and runs there |
| `2EF0CE-300000` | | | pad | bank 0x17's tail |
| `300000-7B75A4` | | | compressed archive | bank 0x18: the asset archive, 873 entries. main_code opens it by ROM address (`lui a0,0x30`) |
| `7B75A4-800000` | | | pad | zeros, plus a stray halfword at `7B75AA` |

### Archives ("banks")

Every 0x20000 boundary from `0x120000` that starts with `00002008 00000400`
is an archive:

- a u32 data offset (always 0x2008), then a u32 capacity (0x400 entries);
- `(offset, size)` u32 pairs, relative to the data offset, ended by
  `FFFFFFFF` and padded with `FF` up to `+0x2008`;
- the entries, packed back to back with no alignment (odd sizes are
  common);
- a tail of zeros up to the next bank. Some tails have a stray halfword at
  the 8-aligned end + 2, left over from Hudson's build tool. It is kept as
  data (`tail` in `assets/bankNN/archive.yaml`). The values (`4009`,
  `4011`, `1009`) aren't the bank number. They look like stale buffer
  contents.

The bank number is `ROM >> 17`, the same numbers 0x30800's table uses. Bank
0x10 (at `0x200000`) is 0x2B7F6 bytes and runs over `0x220000`, so there is
no bank 0x11.

| bank | ROM | entries | end |
| --- | --- | --- | --- |
| 09 | `120000` | 5 | `124DD2` |
| 0A | `140000` | 7 | `15473C` |
| 0B | `160000` | 8 | `1780BE` |
| 0C | `180000` | 11 | `19A9C4` |
| 0D | `1A0000` | 8 | `1B2B5A` |
| 0E | `1C0000` | 16 | `1DA8B4` |
| 0F | `1E0000` | 11 | `1F7ECA` |
| 10 | `200000` | 14 | `22B7F6` |
| 12 | `240000` | 7 | `24D7DC` |
| 13 | `260000` | 3 | `26ED4C` |
| 14 | `280000` | 3 | `290C06` |
| 15 | `2A0000` | 3 | `2B2D76` |
| 16 | `2C0000` | 2 | `2C30B6` |
| 17 | `2E0000` | 11 | `2EF0CE` |
| 18 | `300000` | 873 | `7B75A4` (EU `7B7F1C`) |

In an overlay bank, entry 0 is a small uncompressed header (4-0x2E bytes).
The others are LZSS-compressed overlays (`docs/COMPRESSION.md`). In the
reference decomp each one is a sub-overlay linked at `80043000`.

In the asset archive, 831 of the 873 entries begin with a plausible
decompressed-size word (LZSS). The other 42 have their own headers. Entry 32,
at `30A898` and 0xFD0E0 bytes, starts with `"S2"`, a u16 count of 0x2F, and
then offset/size pairs. It is the largest entry, and it is the only asset
that differs between US and EU.

## EU

Same layout and same segment list as US. These parts differ:

| piece | US | EU | what differs |
| --- | --- | --- | --- |
| header | | | name `BOMBERMAN64E`, code `NBMP`, CRCs |
| boot_code | `1000-1CBC0` | same size | Its libultra is the same objects, byte for byte (docs/LIBULTRA.md). Only the 0x60 bytes of zeros between two link units sit elsewhere: US has them after `osSetThreadPri` (`4150-41B0`), EU between `osUnmapTLBAll` and `osInitialize` (`3DE0-3E40`), so `osInitialize` and `osSetThreadPri` are 0x60 later in EU. Two small game functions at `25A0`/`2614` change size by 4 (`tools/vermap.py`, below, sees them as one changed function at `800018A8`, and the moved gap as two functions changing size). From `1BCE4` (data) on, the two are the same |
| rom header table | | | one byte (`30021`) |
| main_code | `40000-BFB00` | `40000-BFAF0` | 0x10 shorter, in the data. The text is the same size, and its 1048 functions are at the same addresses: 3267 words differ, nearly all lui/lo halves of addresses that moved (0x10 or 8 bytes, in the data from `8029FC4C` on), and 5 functions really changed (about 11 words) |
| overlay banks | | | same headers and sizes. Bank 0x0B entry 1, bank 0x10 entry 13 and bank 0x12 entry 5 differ in content (same compressed size) |
| asset archive | | | entry 32 (`"S2"` container) is 0xFDA58 bytes, 0x978 longer, so every later entry moves by 0x978 and the archive ends at `7B7F1C`. EU has no stray halfword in the tail |

## JP

*Baku Bomberman* (`NBMJ`), the Japanese release. The same layout and the
same segment list as US: the same banks with the same entries, the same
95 overlays, the same file table, the same loaders. Almost everything has
moved, though, because text, pictures and some code differ:

| piece | US | JP | what differs |
| --- | --- | --- | --- |
| header | | | name `BAKU-BOMBERMAN`, code `NBMJ`, CRCs |
| boot_code | `1000-1CBC0` | `1000-1CBA0` | 0x20 shorter. One game function at `800018A8` (in object `2350`) is 4 words shorter. The libultra objects are the same, byte for byte (docs/LIBULTRA.md), except that the 0x60-byte zero gap between two link units sits between `__ll_rshift` and `bzero` (`80012CD0-80012D30`), not after `osSetThreadPri`. zerojump is at `1CBA0`, boot_code's bss is `8001BFA0-80028440` |
| segment size table | | | byte 2 `FE` (main_code is reloaded whole), byte 3 `8D`, bank 0x0B's `30` (US `31`), filler byte 0x21 `88` |
| main_code | `40000-BFB00` | `40000-BED30` | 0xDD0 shorter: text `0xB7130` (US `0xB7A50`, 0x920 less), data 0x4B0 less, bss `802A4530-802B28F0`. 19 functions changed, 8 us-only and 5 jp-only (below); 4 ZeroJump stubs fewer |
| overlay banks | | | every overlay but `ovl_16_01` (which has no ZeroJump block) differs: each has 4 ZeroJump stubs fewer (ids 0x1208, 0x250B-0x250D, in every module), and 10 have changed code (below); most banks are a little shorter (0x13 and 0x16 keep their size, 0x15 is longer) |
| asset archive | 873 entries, to `7B75A4` | 870 entries, to `7C3B18` | the same entry numbers, without us's last three (pictures); 46 entries differ (docs/ASSETS.md, "US and JP"); the tail has a stray `4009` |

Tails: the stray halfwords are in banks 09, 0B, 0C, 0E, 15, 16, 17 and 18
(`4009`, `1009` in bank 0x16; US has them in 09, 0C, 0E, 10, 14, 15, 16
and 18); `assets/bankNN/
archive.yaml` keeps them as for US.

**The boot thread and main_code.** jp's main_code (0x7ED30 bytes) ends
before the page the boot thread loads once, so all of it is reloaded each
time round (`table[2]` = 0xFE: 0x7F000 bytes) and the config has no
`main_code_persist`. The one-time load is `table[3]` = 0x8D units (0x46800
bytes) from `0xBF000`, which is all zeros (the pad up to 0x120000): it
clears `802A4800-802EB000` once. `tools/rom.py` writes byte 2 from the
link and keeps byte 3 as the ROM has it.

The C files match jp unchanged so far: none of the decompiled functions
differ. What differs (from `tools/vermap.py --functions <module> jp`):

- **boot_code**: `800018A8` (98 words, 94 in jp), the moved link gap.
- **main_code**: changed functions in objects `52270`, `54E40` (8
  functions, three of them among the five that differ in eu), `5E3F0`,
  `6BBE0`, `85A10`, `96540` (eu's other two), `9A5F0`, `AD3D0`. In `9A5F0` us has 6 functions jp lacks (the
  proportional font: `func_8028014C`, `func_80280358`, `func_80280BD0`,
  `func_80280C08`, `func_802811F0`, and an inlined static's stub) and jp
  one of its own (`func_802800B4_jp`, where us has `func_80280358`); jp
  moved `func_8028124C` and `func_80280DB4` to the end of the file, which
  starts the object 0x190 bytes before what us's start maps to
  (text_objects.txt). The ZeroJump block has 706 stubs (710 in us).
- **overlays**: `ovl_0A_06`, `ovl_0B_01`-`ovl_0B_07` (title, menus and the
  like: `ovl_0B_04` and `ovl_0B_06` are largely rewritten), `ovl_14_02`,
  `ovl_15_02`. The other 85 have every function identical; their data
  (text) and their stub blocks differ.

## The US to EU map

`tools/vermap.py` aligns eu's code to us's from the two ROMs and writes
`vermap.eu.txt` (generated and committed, like the configs; `make vermap`
regenerates it, `tools/vermap.py --check` checks it, `--report` and
`--functions [module]` show what it found). The overlays pair up by bank
and entry (both ROMs have the same 95, the same sizes). Per module, the
functions (a start after each return that no branch or jump table crosses,
every jal target, and every entry of a table of functions: a table in the
data whose entries all are where a function can start, such as the
exports a module hands func_80297D30; at `-O3` a function inlined
everywhere is named only there) are aligned on their bodies with the linker-filled
fields masked (jal targets, lui/lo immediates); what is left pairs by
identical body in any order, then by similarity ("changed"). Every jal and
lui/lo pair in aligned code is a (us, eu) address pair, and the pairs most
code agrees on anchor the ranges of `vermap.eu.txt` (`module us-start
us-end eu-start`, one address space per overlay and one for the fixed
modules).

`make extract` for eu then runs `vermap.py --rename eu` after postsplit:
every `func_X`/`D_X`/`jtbl_X`/`LX` splat made from an eu address becomes
us's name for that thing (`func_<us address>`, or the name in
`symbol_addrs.us.txt`, so names added there flow into eu), and an eu
address with no us counterpart `..._eu`. It is done on the text of the
finished asm, all names at once, so an eu name cannot clash with a us name
at another address. It needs only `vermap.eu.txt`, not the us ROM.
Nothing is assembled differently (`make VERSION=eu` still matches, and
`find_abs.py eu` is 0).

What the alignment finds (functions, ZeroJump stub blocks not counted):

| module | functions | identical | changed | us only | eu only |
| --- | --- | --- | --- | --- | --- |
| boot_code | 443 | 438 | 5 (`800018F8`, `80001A04`, `80001A14`, `80003190`, `80003470`) | 0 | 0 |
| main_code | 1735 | 1730 | 5 (`8023DB0C`, `8023E1D8`, `8023FD08`, `8027C4F4`, `8027C788`) | 0 | 0 |
| 95 overlays | 5628 | 5628 | 0 | 0 | 0 |
| total | 7806 | 7796 (99.9%) | 10 | 0 | 0 |

Every function is paired, so the map has no eu-only function and no
us-only one. The three overlays that differ (`ovl_0B_01`, `ovl_10_13`,
`ovl_12_05`: 1, 7 and 6 words) differ only in lui/lo halves of addresses in
main_code, which moved; their data is the same. In main_code, 53 data words
differ in content (what the map pairs): 48 timing values from `802A0958` to
`802A0A14` (eu's are 1.2 times us's, or so: 50 Hz), one word at `802A1528`
and 4 words of text at `802A2D00` on. The map is 114 ranges (boot_code 5, main_code 13, one for every
other module), covering all of the text and data and the bss as far as the
anchors reach; what a range does not cover is named from its eu address.

## The US to JP map

The same tool maps jp: `vermap.jp.txt` (`tools/vermap.py jp`, `make
vermap` writes both maps, `--check` checks both). Everything above
applies, with `_jp` for what us lacks. Two things the eu map didn't need:

- **ZeroJump stubs** are aligned one by one, by their ids, so that a
  module's block maps around the four stubs jp lacks.
- **A changed function keeps its name**: its start is paired with its
  counterpart's even where the words inside don't align.

And splat has to find the C files' functions in jp: `tools/split.py` runs
splat with the names it reads from a C file (functions defined,
GLOBAL_ASM lines) turned into jp's (`vermap.version_name()`), so it writes
the GLOBAL_ASM functions' `.s` files, and `vermap.py --rename` then gives
those files (and their contents) us's names. `tools/layout.py` names jp's
text objects for us's image offsets through the map (`5E090` is jp's
`0x5DDE0`), and takes us's object boundaries where jp's padding doesn't
show them (`5E090` starts right after a function that ends 16-aligned in
jp), so each C file is the same object in both.

What the alignment finds (functions, ZeroJump stubs not counted):

| module | us | jp | identical | changed | us only | jp only |
| --- | --- | --- | --- | --- | --- | --- |
| boot_code | 443 | 442 | 439 | 2 (`80001A04`, `80003470`) | 2 (`80001A14`, `80012D14`) | 1 |
| main_code | 1735 | 1730 | 1709 | 20 | 6 | 1 |
| 95 overlays | 5628 | 5618 | 5552 | 61 | 15 | 5 |
| total | 7806 | 7790 | 7700 (98.6%) | 83 | 23 | 7 |

Per overlay (the 85 others are all identical):

| overlay | us | jp | identical | changed | us only | jp only |
| --- | --- | --- | --- | --- | --- | --- |
| ovl_0A_06 | 51 | 51 | 46 | 5 | 0 | 0 |
| ovl_0B_01 | 38 | 38 | 34 | 4 | 0 | 0 |
| ovl_0B_02 | 63 | 63 | 61 | 2 | 0 | 0 |
| ovl_0B_03 | 50 | 50 | 48 | 2 | 0 | 0 |
| ovl_0B_04 | 107 | 105 | 79 | 25 | 3 | 1 |
| ovl_0B_05 | 47 | 47 | 45 | 2 | 0 | 0 |
| ovl_0B_06 | 98 | 90 | 73 | 14 | 11 | 3 |
| ovl_0B_07 | 28 | 28 | 25 | 2 | 1 | 1 |
| ovl_14_02 | 167 | 167 | 165 | 2 | 0 | 0 |
| ovl_15_02 | 146 | 146 | 143 | 3 | 0 | 0 |

boot_code's `80003470` and `80012D14` are the moved link gap (the
function cutter counts the zeros with the function before them), not
code. The map is 979 ranges, many of them single words in data that
moved by different amounts (each of jp's strings is shorter or longer
than us's). After a jp extract, 226 names are `_jp`.

Functions that only moved pair by their identical bodies, once a table of
functions shows where they start: jp's 9A5F0 has `func_8028124C` and
`func_80280DB4` (and so `func_802809A0`, `func_802809F0`, `func_80280A40`,
which -O3 emits before their caller) at its start, and
`func_80280274`, us's glyph loader without the remapping, pairs as
changed.

## Loaders

The ROM is cut into 128 KiB **segments**, numbered `ROM >> 17`: segment 0
is boot_code and zerojump, segment 2 main_code, segments 9-0x17 the
overlay banks, 0x18 the asset archive.

- **The segment size table** (0x30000, 0x100 bytes): byte n is segment
  n's size in 2 KiB units, where 0 means 0x80000. It is mostly each
  bank's size rounded up to 2 KiB. Exceptions: bank 0x16 has 0x40 although
  its contents fit in 0x07, the asset archive has 0, and the bytes from
  0x19 on are filler (0x21 is 0x6F in us, 0x70 in eu, 0x88 in jp, the
  rest 0x40).
  `0x800007F0(seg, dst)` DMAs `seg << 17` for that size.
- **The boot thread** (0x80001750) DMAs the table, then ROM
  `0x40000 + table[2] * 2K` for `table[3] * 2K` bytes (0xBF800-0xC0000)
  to 0x802A5000, once. It then loops forever: load segment `*0x80024818`
  (initially 2) to 0x80225800 and call it. Each time round, main_code is
  reloaded up to `table[2] * 2K` (0x7F800). Its tail from 0xBF800 on is
  loaded once and survives the reloads (`main_code_persist` in the
  config); main_code's bss lies in that page's zero tail and past it.
- **The file table** (0x30800, 0x1000 bytes): two bytes per file id, the
  segment and then an offset in 2 KiB units. The overlay loader
  `0x8022691C(id)` opens the archive at `seg << 17 + off << 11`, reads its
  entry 0 (the index) to 0x8019C0D0, looks `id` up there to get the entry
  number, and inflates that entry to 0x80043000. It switches the open
  archive back to 0x300000, calls 0x80043000, and keeps the pointer that
  returns at 0x802A532C. Every overlay id is in its bank's index, and the
  table points it at that bank (offset 0). Some ids in the table are in no
  index (24, for one) and look stale. bank0B's index says 9 entries but
  has 7 records.
- **ZeroJump:** the 0x130-byte zerojump is DMAd to 0x80042000 and mapped
  by the TLB at virtual 0. A call is `jr $zero` with `li $t0, id` in the
  delay slot: the high byte picks a module's table (registered with
  `0x80001A30(n, table)` into 0x8001BFC0[n]), the low byte the function.
  An unset entry prints "ZeroJump Error : unset segment/function".
  main_code and every overlay carry a full block of these stubs
  (`00000008 2408xxxx` pairs, about 0x1640 bytes).
- **An overlay's entry** (0x80043000) returns its main function (0x80043010).

## Stage 2: the code image

What splat splits and the code link rebuilds is not the ROM but the
**code image** (`assets/code.bin`, written by `assets.py extract`): the
ROM below 0x120000 as it is, then all 95 overlays inflated, back to back in
bank and entry order (0x19F7D0 bytes; every overlay is a multiple of 16).
`tools/rom.py` builds the ROM from the rebuilt image and the archives:
the image's first 0x120000 bytes, then the banks, with each overlay entry
taken from where the link put it and recompressed. It writes the segment
size table from the link, and checks the file table.

In the config (`tools/layout.py`):

- **The code segments** are boot_code (VRAM 0x80000400, `entry` hasm, bss
  from the entry's clear), zerojump (at its physical 0x80042000, hasm,
  its strings as rodata), main_code (bss from its init's clear) and
  `ovl_BB_EE` for each overlay (VRAM 0x80043000, one shared
  `exclusive_ram_id`, names `func_ovlBB_EE_XXXXXXXX`, bss from the extent
  of its references past its end). Every code segment has a RAM id: splat
  makes one range of all untagged segments, which 0x80043000 would fall
  inside.
- **Text** ends after a module's last `jr ra` or ZeroJump stub, rounded
  up to 16, and before any RSP code (the first j/jal into IMEM,
  0x04001000-0x04002000: main_code's data from 0xB7A50 is RSP microcode).
  That agrees with the reference decomp for boot_code (0x1AB80),
  main_code (0xB7A50) and all 95 overlays. Each module's first function
  (its entry) is an object of its own, as is the ZeroJump stub block
  (`<module>_zerojmp`). The rest of the text is split where IDO's 16-byte
  padding after a function shows an object boundary, where a matched
  libultra object starts or ends (`lib_objects.<v>.txt`), and where
  `text_objects.txt` says an object starts, unless a branch crosses it.
  `text_objects.txt` is for the boundaries the padding can't show (the
  function before ends on a 16-byte boundary) that the code shows another
  way: one line per object, `<module> <us image offset>` (its name), with
  the reason in a comment; eu's and jp's addresses come from the map, so
  the object has the same name and C file everywhere. main_code's `4E030`
  is one: 4DE50's seven float compares are `-O3`, and 4E030's wrappers
  call them with a `jal`, which `-O3` would have inlined within one file.
  A line can also give a version's own start (`main_code 9A5F0
  jp=9A340`): jp's 9A5F0 moved two functions to the end of its source, so
  `-O3` emits them, and the callees they pull along, first, and the object
  starts before the code us's start maps to; that address is then no
  boundary.
- **Data** is cut per object where the C shows it (`data_split.txt`,
  docs/DECOMPILING.md, "Data"): a `.data`, `.rodata` and `.bss`
  subsegment for each C object listed there, from the module's first
  object on, and asm for the rest: `data` before the module's
  .data/.rodata boundary, `rodata` after it (one `rodata` block where
  nothing is cut, so that spimdisasm labels the jump tables), one `bss`
  block. main_code's RSP code (0xB7A50-0xB9D70) is an asm `data` block
  before its objects' .data. Plus `main_code_persist` from main_code's
  persistent part on.

`tools/ld_fix.py` turns splat's linker script into the build's. Splat
would place every segment after the one before. Instead, the pads link
nothing and the ROM position jumps to the next fixed start (with an
ASSERT), and `main_code_persist` starts 2 KiB-aligned. `SHIFT=1` adds the
pads that move everything after each module's entry.

## Compiler and library hints

- IDO 5.3. Hudson's game code (main_code up to its ZeroJump block, the
  overlays) is `-mips1`, `-O2` where checked so far, main_code's entry
  `-g`; boot_code's libraries and main_code's code after the ZeroJump
  block are `-mips2`. docs/DECOMPILING.md has the evidence. The reference
  decomp (Bomberhackers/bm64) agrees, with more files at `-O3`.
- libultra is 2.0I as ultralib builds it (`libultra_rom`, IDO 5.3, its
  own flags), with some objects from a different revision; libaudio is
  the same 2.0I one. docs/LIBULTRA.md has the evidence and what doesn't
  match. There is no libultra version string. The scheduler's assert
  strings (`sched.c`, `sc->curRSPTask`) are the SDK's sample scheduler,
  compiled with the game. boot_code has a 0x60-byte zero gap between two
  link units (US before `sprintf`, `4150-41B0`).
- EU links the same libultra (see boot_code above), NTSC/PAL handling
  included: `osInitialize` and `__osViInit` are identical.

## Uncertain

- What the size table's filler bytes (0x19 on) and bank 0x16's oversized
  entry mean, if anything. They are kept as the ROM has them.
- jp's size table byte 3 (0x8D: the boot thread clears 0x46800 bytes past
  main_code once): whether Hudson's tool meant it, or it is stale.
- The file table's stale ids (in no bank's index).
- Text object boundaries the padding doesn't show (functions that end on a
  16-byte boundary), in the game's own code, until the C shows them
  (`text_objects.txt`). In libultra, matching found them
  (`lib_objects.<v>.txt`, docs/LIBULTRA.md).
