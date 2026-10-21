# ROM layout

The top-level map of Bomberman 64 (1997), US (`NBME`) and EU (`NBMP`).
`tools/layout.py <version>` derives it from the ROM and writes
`bm64.<version>.yaml`, a splat config that splits the whole ROM into bins
(26 segments in each version, one per archive). `tools/assets.py` splits
the archives into their entries (`assets/bankNN/`) and builds them back.
`tools/layout.py --check <version>` checks
that the config covers the ROM with no gaps or overlaps and still matches
what the ROM says. Splitting with splat64 and relinking those bins gives back
both ROMs, sha1 for sha1.

Both ROMs are 8 MiB, CIC-NUS-6102, entry point `0x80000400`.

## US

| ROM range | VRAM | size | kind | notes |
| --- | --- | --- | --- | --- |
| `000000-000040` | | 0x40 | header | |
| `000040-001000` | `A4000040` | 0xFC0 | boot | IPL3 (6102) |
| `001000-01CBC0` | `80000400` | 0x1BBC0 | code+data | **boot_code**: entry, scheduler (`sched.c`), libultra, audio library. The entry clears bss `8001BFC0-80028460` (0xC4A0) and jumps to `80001A20` |
| `01CBC0-01CCF0` | `80042000` | 0x130 | code+data | **zerojump**: boot_code's entry DMAs it to `80042000`; `osMapTLB` maps it at virtual `00000000`. "ZeroJump Error : unset segment/function" strings |
| `01CCF0-030000` | | | pad | zeros |
| `030000-030100` | `80024820` | 0x100 | data | ROM header table: boot_code DMAs it (in its bss). Bytes 2/3 are a start/length in 2 KiB units for a piece of main_code (`0x40000 + n<<11` to `0x80225800 + n<<11`) |
| `030100-030800` | | | pad | zeros |
| `030800-031800` | `8019B0D0` | 0x1000 | data | bank table: main_code DMAs it. u16s holding bank numbers (`ROM >> 17`, 0x09-0x17) |
| `031800-040000` | | | pad | zeros |
| `040000-0BFB00` | `80225800` | 0x7FB00 | code+data | **main_code**, uncompressed. bss `802A5300` + 0xE3D0 (reference decomp) |
| `0BFB00-120000` | | | pad | zeros |
| `120000-2EF0CE` | `80043000` | | compressed archives | overlay banks 0x09-0x17 (below). main_code DMAs 0x20000 bytes to `80043000`; the overlays run there |
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
| boot_code | `1000-1CBC0` | same size | Its libultra differs. US has `osUnmapTLBAll`/`osInitialize` at `3D90`/`3DE0`, before the nop padding at `414C`. EU lacks them there, so its first text block is 0x370 shorter (padding at `3DD0`), and its later text is longer by the same amount, which suggests a newer or PAL `osInitialize` elsewhere. Two small functions at `25A0`/`2614` change size by 4. From `1BCE4` (data) on, the two are the same |
| rom header table | | | one byte (`30021`) |
| main_code | `40000-BFB00` | `40000-BFAF0` | 0x10 shorter. Many scattered differences, mostly relocation low halves (moved data) plus real code changes |
| overlay banks | | | same headers and sizes. Bank 0x0B entry 1, bank 0x10 entry 13 and bank 0x12 entry 5 differ in content (same compressed size) |
| asset archive | | | entry 32 (`"S2"` container) is 0xFDA58 bytes, 0x978 longer, so every later entry moves by 0x978 and the archive ends at `7B7F1C`. EU has no stray halfword in the tail |

## Compiler and library hints

- The reference decomp (Bomberhackers/bm64) builds with IDO 5.3 at `-O2`,
  `-mips1`, with some files at `-O3` and one at `-g`, and matches with that.
  Not re-verified here beyond the IDO-style code (`jr ra` with filled delay
  slots, `lui`/`addiu` pairs, `$at` stores).
- There is no libultra version string. The scheduler's assert strings
  (`sched.c`, `sc->curRSPTask`) are the SDK's sample scheduler. boot_code
  has a nop-padded gap before `sprintf` (US `414C-41B0`), so two separately
  aligned link units meet there.
- EU's libultra is not US's (see boot_code above). Expect a PAL or newer
  `osInitialize` and different VI handling.

## Uncertain

- What the bytes of the `0x30000` table mean, beyond 2/3. The US value
  (`ff 01`) would load only `BF800-C0000`, so main_code's main load is
  elsewhere and has not been traced.
- main_code's end is "last non-zero byte before 0x120000, rounded up to 16".
  That agrees with the reference's bss start (`802A5300` = `80225800` +
  0x7FB00) for US. EU's bss would start at `802A52F0`, which is unchecked.
- The overlay VRAM `80043000` comes from the reference and from a 0x20000
  DMA in main_code, not from a traced load of each overlay.
