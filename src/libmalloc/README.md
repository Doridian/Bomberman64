# GNU malloc (gmalloc.c, 1995)

Hudson's allocator in main_code is GNU malloc's single-file build,
`gmalloc.o`. docs/LIBMALLOC.md has the evidence and where it is in the ROM.

## Origin

`gmalloc.c`, `getpagesize.h` and `COPYING.LIB` are the files of those names
in the standalone GNU malloc distribution

- <https://ftp.gnu.org/old-gnu/malloc.tar.gz>
- sha256 `fa7353ea297e1e8e2a1a046583786c4adfbb581f5ec1c8980406b242a5da6ef1`

(`malloc/gmalloc.c`, 1995-01-18; `malloc/getpagesize.h`;
`malloc/COPYING.LIB`), byte for byte. They have **not been changed**: the
file compiles to the ROM's bytes as it is (`-g -mips1 -DSTDC_HEADERS
-DPAGESIZE=0x1000`, see the Makefile), so it needed no decompiling.
`tools/libmalloc_check.py` checks them against the tarball and the
compiled object against every ROM.

The only build-side differences are outside the files: the Makefile maps
the four libc helpers gmalloc.c calls (`sbrk`, `memmove`, `memcpy`,
`memset`) to the game's own functions in `src/40300.c` with `-D`, since
they keep their address names (libultra's `memcpy` is another function).

## Licence

gmalloc.c is Copyright 1990, 1991, 1992, 1993, 1994, 1995 Free Software
Foundation, Inc., written by Mike Haertel (the notices are in the file,
as they came). It is distributed under the GNU Library General Public
License, version 2 or (at your option) any later version; `COPYING.LIB` is
that licence's text.

**It is used here under the GNU General Public License, version 2 or (at
your option) any later version**, as section 3 of the LGPL v2 allows for a
copy of the library. GPL version 3 or later combines with this project's
GNU Affero General Public License version 3 (GPLv3 section 13 / AGPLv3
section 13), so the project as a whole remains AGPL-3.0-or-later while
these files keep their own terms and notices. (As the files themselves
were not edited, their LGPL notices are left in place; this note records
the choice.) That is the usual reading, not legal advice.

## Ours

The stub headers in `include/` (`stddef.h`, `limits.h`, `string.h`,
`sys/param.h`: without them IDO reads the host's `/usr/include`; and
`unistd.h`, sbrk's prototype for the PC port, which compiles gmalloc.c
with `-DHAVE_UNISTD_H`) and `pc_names.h` (the PC port's `#define`s renaming
the allocator's symbols, under `TARGET_PC`) are this project's, under its AGPL-3.0, not GNU
malloc's.
