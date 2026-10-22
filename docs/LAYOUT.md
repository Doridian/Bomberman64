# ROM layout

The map of Bomberman 64 (1997), US (`NBME`) and EU (`NBMP`).
`tools/layout.py <version>` derives it from the ROM and writes
`bm64.<version>.yaml`, the splat config of the code image ("Stage 2",
below). `tools/assets.py` splits the archives into their entries
(`assets/bankNN/`) and builds them back. `tools/layout.py --check
<version>` checks that the config still matches what the ROM says, and
`tools/layout.py --print <version>` prints the ROM's segment list.

Both ROMs are 8 MiB, CIC-NUS-6102, entry point `0x80000400`.

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

## The US to EU map

`tools/vermap.py` aligns eu's code to us's from the two ROMs and writes
`vermap.eu.txt` (generated and committed, like the configs; `make vermap`
regenerates it, `tools/vermap.py --check` checks it, `--report` and
`--functions [module]` show what it found). The overlays pair up by bank
and entry (both ROMs have the same 95, the same sizes). Per module, the
functions (a start after each return that no branch or jump table crosses,
and every jal target) are aligned on their bodies with the linker-filled
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
| boot_code | 266 | 263 | 3 (`800018A8`, `80003190`, `80003470`) | 0 | 0 |
| main_code | 1048 | 1043 | 5 (`8023D8A0`, `8023E1D8`, `8023EF38`, `8027C4F4`, `8027C5E0`) | 0 | 0 |
| 95 overlays | 5524 | 5524 | 0 | 0 | 0 |
| total | 6838 | 6830 (99.9%) | 8 | 0 | 0 |

Every function is paired, so the map has no eu-only function and no
us-only one. The three overlays that differ (`ovl_0B_01`, `ovl_10_13`,
`ovl_12_05`: 1, 7 and 6 words) differ only in lui/lo halves of addresses in
main_code, which moved; their data is the same. In main_code, 53 data words
differ in content (what the map pairs): 48 timing values from `802A0958` to
`802A0A14` (eu's are 1.2 times us's, or so: 50 Hz), one word at `802A1528`
and 4 words of text at `802A2D00` on. The map is 114 ranges (boot_code 5, main_code 13, one for every
other module), covering all of the text and data and the bss as far as the
anchors reach; what a range does not cover is named from its eu address.

## Loaders

The ROM is cut into 128 KiB **segments**, numbered `ROM >> 17`: segment 0
is boot_code and zerojump, segment 2 main_code, segments 9-0x17 the
overlay banks, 0x18 the asset archive.

- **The segment size table** (0x30000, 0x100 bytes): byte n is segment
  n's size in 2 KiB units, where 0 means 0x80000. It is mostly each
  bank's size rounded up to 2 KiB. Exceptions: bank 0x16 has 0x40 although
  its contents fit in 0x07, the asset archive has 0, and the bytes from
  0x19 on are filler (0x20 is 0x6F in us, 0x70 in eu, the rest 0x40).
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
  padding after a function shows an object boundary, and where a matched
  libultra object starts or ends (`lib_objects.<v>.txt`), unless a branch
  crosses it.
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
- The file table's stale ids (in no bank's index).
- Text object boundaries the padding doesn't show (functions that end on a
  16-byte boundary), in the game's own code. In libultra, matching found
  them (`lib_objects.<v>.txt`, docs/LIBULTRA.md).
