# libmalloc: Hudson's allocator

main_code's allocator is **GNU malloc's `gmalloc.c`**, the single-file build
(`gmalloc.o`, not the separate objects of `libmalloc.a`), from the 1995
standalone distribution <https://ftp.gnu.org/old-gnu/malloc.tar.gz>
(sha256 `fa7353ea297e1e8e2a1a046583786c4adfbb581f5ec1c8980406b242a5da6ef1`,
Mike Haertel's allocator, "GNU malloc" in the C library of that time). The
earlier decomp (Bomberhackers/bm64) already had it as
`src/libmalloc/gmalloc.c`, `-g -DPAGESIZE=0x1000`; this was verified
independently.

It is in the ROM build as source: `src/libmalloc/gmalloc.c` is the
tarball's file, unchanged, built in us, eu and jp (see "Source").

**Certainty: exact.** Compiled with the repo's IDO 5.3 as

```
cc -c -g -mips1 -G 0 -non_shared -Xfullwarn -Xcpluscomm -D_LANGUAGE_C \
   -DSTDC_HEADERS -DPAGESIZE=0x1000 -Wab,-r4300_mul -woff 649,838,712,807 gmalloc.c
```

the object's `.text` is 0x22E0 bytes, and the ROM has 0x22E0 bytes at
`0xB3B70` in **both** US and EU, and at `0xB3250` in JP. Every word is identical except the fields a
relocation fills (jal targets, `%hi`/`%lo`): 0 mismatches of 2232 words,
469 relocations. Each symbol resolves to one address at all its references
(and `.data` and `.bss` are contiguous with the right sizes: 0x10 and 0xB0,
ending at main_code's bss end). `-mips2` does not match (2011 words differ).

`tools/libmalloc_check.py` repeats all of this on its own, without an
extract: it downloads the tarball into `build/libmalloc/` and checks that
`src/libmalloc`'s `gmalloc.c`, `getpagesize.h` and `COPYING.LIB` are its
files byte for byte, compiles `src/libmalloc/gmalloc.c`, compares every ROM,
and `--write` generates `symbol_addrs.libmalloc.<v>.txt`. It needs a built
`tools/ido`. Only the stub headers (`src/libmalloc/include/`: `stddef.h`,
`limits.h`, `string.h`, `sys/param.h`) are ours; without them IDO reads the
host's `/usr/include`.

## Where it is

ROM `0xB3B70-0xB5E50` (main_code, vram `0x80299370-0x80299650`). The
functions are at the same addresses in US and EU (in JP, 0x920 lower: from
`0x80298A50`). The asm continues after
`0xB5E50` with other code, not part of the allocator.

| function | address | size | | function | address | size |
| --- | --- | --- | --- | --- | --- | --- |
| `valloc` | 80299370 | 0x60 | | `_free_internal` | 8029A3F4 | 0x9D8 |
| `align` (static) | 802993D0 | 0xC8 | | `free` | 8029ADCC | 0xCC |
| `initialize` (static) | 80299498 | 0x148 | | `cfree` | 8029AE98 | 0x30 |
| `morecore` (static) | 802995E0 | 0x30C | | `realloc` | 8029AEC8 | 0x4CC |
| `malloc` | 802998EC | 0xA60 | | `calloc` | 8029B394 | 0x7C |
| `_malloc` | 8029A34C | 0x38 | | `__default_morecore` | 8029B410 | 0x58 |
| `_free` | 8029A384 | 0x30 | | `memalign` | 8029B468 | 0x1E8 |
| `_realloc` | 8029A3B4 | 0x40 | | | | |

Data (US; EU's bss is 0x10 lower, from `_heapbase` at `802B3610`):

- `.data` at `802A2CF0` (ROM `0xBD4F0`, in the `B7A50` rodata block):
  `__morecore` (= `__default_morecore`), `_aligned_blocks`.
- `.bss` at `802B3620-802B36D0`: `_heapbase`, `_heapinfo`, `_heapindex`,
  `_heaplimit`, `_fraghead` (0x60), `_chunks_used`, `_bytes_used`,
  `_chunks_free`, `_bytes_free`, the hooks (`__after_morecore_hook`,
  `__malloc_initialized`, `__malloc_initialize_hook`, `__free_hook`,
  `__malloc_hook`, `__realloc_hook`, `__memalign_hook`) and the statics
  `pagesize` (`802B36BC`) and `heapsize` (`802B36C0`).

Not part of it: Hudson's libc helpers it calls, at the start of
main_code (`sbrk` `80225B00`, `memmove` `80225BB8`, `memcpy` `80225C44`,
`memset` `80225C7C`), which are the game's C in `src/40300.c` and keep
their address names (they are found by their callers here, not matched,
and libultra's `memcpy` in boot_code is another function). At `0xBD500`,
right after the allocator's `.data`, is a build-date string
(`SAT SEP  6 14:57...`), another object's.

## Source

`src/libmalloc/gmalloc.c` is a `c` text object of main_code
(`libmalloc/gmalloc`): `tools/layout.py` (`malloc_object()`) starts it at
the first function of `symbol_addrs.libmalloc.<v>.txt` once the file is
there, and it ends where libultra's `gu/lookat` starts. The Makefile builds
it as the check does, `-g -mips1` with `-DSTDC_HEADERS -DPAGESIZE=0x1000`
and the stub headers (`src/libmalloc/include`), and maps the four helpers'
names to the game's with `-D` (`-Dmemcpy=func_80225C44` and so on), so the
file needs no change. Its `.data` (0x10) and `.bss` (0xB0) are placed on
their own in `data_split.txt` (docs/DECOMPILING.md, "Objects placed on
their own"): `.data` at `802A2CF0` (jp `802A1F30`), right after `B11F0`'s,
and `.bss` from `802B3620` (eu `802B3610`, jp `802B2840`) to main_code's
bss end, right after `B11F0`'s.

IDO's `-g` leaves the three static functions (`align`, `initialize`,
`morecore`) as undefined, sized symbols in the object, with the calls
relocated against `.text`; nothing references the undefined entries, so
the link ignores them.

The PC port keeps the allocator (a deterministic heap suits
docs/NETPLAY.md), but its global names would clash with the host libc's:
`src/libmalloc/pc_names.h` renames them under `TARGET_PC` (`malloc` to
`bm64_malloc`, ...), for the port to force-include (`-include`) when it
compiles gmalloc.c and the game's C; gmalloc.c stays as it is.

## Names

`symbol_addrs.libmalloc.<v>.txt` (generated, with `segment:main_code`:
splat ignores symbols without it in an `exclusive_ram_id` segment) holds
all of the above, with the source's names. `tools/layout.py` lists it
next to `symbol_addrs.<v>.txt`. After changing a symbol file, delete
`module_syms_auto.txt` and the other `*auto*.txt` before `extract`:
postsplit keeps what an earlier run moved.

## Licence

The sources are LGPL: every file says "GNU Library General Public License
... version 2, or (at your option) any later version", and the tarball has
`COPYING.LIB`. This repo is AGPL-3.0. How `src/libmalloc/` is in it
(`src/libmalloc/README.md` and NOTICES.md say the same):

- LGPLv2 section 3 lets a copy be used under the ordinary GNU GPL (v2 or
  later, here) instead, and GPLv3 combines with AGPLv3 (section 13), so the
  files are used as GPL-or-later, keeping their copyright notices
  (FSF 1990-1995, Mike Haertel), with a note that the licence was chosen.
  That is the usual reading, not legal advice.
- Matching the ROM needs the 1995 code as is, so it can't be rewritten
  clean-room. It is in its own directory (`src/libmalloc/`) with the
  `COPYING.LIB` text and the origin URL and checksum above, taken from the
  tarball, not from the copy in Bomberhackers/bm64 (it has no licence of
  its own, only a notice file).
- The files are unchanged (`tools/libmalloc_check.py` checks them against
  the tarball); the stub headers and `pc_names.h` are the project's own.
