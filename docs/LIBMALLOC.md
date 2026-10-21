# libmalloc: Hudson's allocator

main_code's allocator is **GNU malloc's `gmalloc.c`**, the single-file build
(`gmalloc.o`, not the separate objects of `libmalloc.a`), from the 1995
standalone distribution <https://ftp.gnu.org/old-gnu/malloc.tar.gz>
(sha256 `fa7353ea297e1e8e2a1a046583786c4adfbb581f5ec1c8980406b242a5da6ef1`,
Mike Haertel's allocator, "GNU malloc" in the C library of that time). The
earlier decomp (Bomberhackers/bm64) already had it as
`src/libmalloc/gmalloc.c`, `-g -DPAGESIZE=0x1000`; this was verified
independently.

**Certainty: exact.** Compiled with the repo's IDO 5.3 as

```
cc -c -g -mips1 -G 0 -non_shared -Xfullwarn -Xcpluscomm -D_LANGUAGE_C \
   -DSTDC_HEADERS -DPAGESIZE=0x1000 -Wab,-r4300_mul -woff 649,838,712,807 gmalloc.c
```

the object's `.text` is 0x22E0 bytes, and the ROM has 0x22E0 bytes at
`0xB3B70` in **both** US and EU. Every word is identical except the fields a
relocation fills (jal targets, `%hi`/`%lo`): 0 mismatches of 2232 words,
469 relocations. Each symbol resolves to one address at all its references
(and `.data` and `.bss` are contiguous with the right sizes: 0x10 and 0xB0,
ending at main_code's bss end). `-mips2` does not match (2011 words differ).

`tools/libmalloc_check.py` repeats all of this (downloads the tarball into
`build/libmalloc/`, compiles, compares both ROMs, `--write` generates
`symbol_addrs.libmalloc.<v>.txt`). It needs a built `tools/ido`.
Only stub headers (`stddef.h`, `limits.h`, `string.h`, `sys/param.h`) are
ours; without them IDO reads the host's `/usr/include`.

## Where it is

ROM `0xB3B70-0xB5E50` (main_code, vram `0x80299370-0x80299650`). The
functions are at the same addresses in US and EU. The asm continues after
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

Not part of it, and not named yet: Hudson's libc helpers it calls, at the
start of main_code (`sbrk` `80225B00`, `memmove` `80225BB8`, `memcpy`
`80225C44`, `memset` `80225C7C`). They are found by their callers here, not
matched. At `0xBD500`, right after the allocator's `.data`, is a build-date
string (`SAT SEP  6 14:57...`), another object's.

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
`COPYING.LIB`. This repo is AGPL-3.0, and there is no source of the
library in it today (the tool fetches it). For `src/` later:

- LGPLv2 section 3 lets a copy be used under the ordinary GNU GPL (v2 or
  later, here) instead, and GPLv3 combines with AGPLv3 (section 13), so the
  files can go in as GPL-or-later, keeping their copyright notices
  (FSF 1990-1995, Mike Haertel) and a note that the licence was chosen.
  That is the usual reading, not legal advice.
- Matching the ROM needs the 1995 code as is, so it can't be rewritten
  clean-room. Keep it in its own directory (`src/libmalloc/`) with the
  `COPYING.LIB` text and the origin URL and checksum above. Don't take the
  copy in Bomberhackers/bm64: it has no licence of its own (only a notice
  file), take the tarball.
- The PC port: Hudson's allocator links the game's heap layout. If the port
  keeps `gmalloc.c` (a deterministic allocator suits docs/NETPLAY.md), its
  symbols (`malloc`, `free`, `memalign`, ...) clash with the host libc's and
  need renaming (a header of `#define`s under `TARGET_PC`).
