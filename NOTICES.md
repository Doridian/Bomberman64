# Notices

This project's own code is licensed under the GNU Affero General Public
License, version 3 or later: see [LICENSE](LICENSE).

Some files in the repository are not the project's own work. Each entry
says where they come from and on what terms they are here.

| Component | Where it is | Terms |
| --- | --- | --- |
| decompals/ultralib (libultra reconstruction) | `include/ultralib/`, `src/libultra/` | no licence file; see below |
| GNU malloc (`gmalloc.c`, 1995) | `src/libmalloc/` | GNU GPL v2 or later (from the LGPL v2 or later); see below |
| Blast Corps decomp tools | `tools/elf_mips2.py` and others adapted from `../BlastCorps` | AGPL-3.0, same author |

---

## libultra: decompals/ultralib

`include/ultralib/` is a copy of the `include/` directory of
[decompals/ultralib](https://github.com/decompals/ultralib) at commit
`e24c836796df4bf520ff8b11a5c9d2cea3a66cbd` (the one
`tools/build_ultralib.sh` builds). The files under `src/libultra/` are
that commit's `src/` files of the same name (the `.c` and `.s` files and
the private headers beside them): most are unchanged, and those that
carry this game's differences describe them at the top of the file; a
few (`io/pfsresizefile.c`, and the older revisions' code in
`io/conteep*.c`, `io/contreaddata.c`, `io/motor.c`) are decompiled from
the game in ultralib's style. Several of the older-revision forms were first matched
in the Blast Corps decomp (`../BlastCorps/blastcorps/src/libultra`, the same
author's project), which reconstructs them from ultralib too.

ultralib is a reverse-engineered reconstruction of Nintendo's N64 SDK
library (libultra), and many of its headers keep the SDK's original
Silicon Graphics / Nintendo copyright notices. At the commit used, and on
its default branch when this was written, the ultralib repository has **no
LICENSE file** and its README states no licence. So there is no explicit
grant for this code: it is kept in the repository, as decomp projects
usually do, because the matching build needs it and with this attribution,
but it is not covered by this project's AGPL, and the files' original
notices are kept as they are.

The PC port must not depend on it: the N64 build keeps `src/libultra` and
`include/ultralib` because it has to match the ROM, and the port replaces
the library over the same interface (as Blast Corps' docs/DISTRIBUTION.md,
"Replacing the SDK parts", does).

## GNU malloc

`src/libmalloc/gmalloc.c`, `getpagesize.h` and `COPYING.LIB` are the files
of those names in GNU malloc's standalone distribution,
<https://ftp.gnu.org/old-gnu/malloc.tar.gz> (sha256
`fa7353ea297e1e8e2a1a046583786c4adfbb581f5ec1c8980406b242a5da6ef1`),
unchanged: Hudson's allocator is that file's `gmalloc.o`
(docs/LIBMALLOC.md). gmalloc.c is Copyright 1990-1995 Free Software
Foundation, Inc., written by Mike Haertel, and its notices are kept as they
are.

It is licensed under the GNU Library General Public License, version 2 or
(at your option) any later version (`src/libmalloc/COPYING.LIB`). This
project uses it under the **GNU General Public License, version 2 or later**
instead, as section 3 of the LGPL v2 allows, and GPL v3 or later combines
with the project's AGPL-3.0 (section 13 of each). `src/libmalloc/README.md`
records the origin, the checksum and this choice. The directory's stub
headers (`include/`) and `pc_names.h` are the project's own (AGPL-3.0).

## Blast Corps decomp

Tools adapted from `../BlastCorps` (`tools/libmatch.py`,
`tools/gen_symbols.py`, `tools/elf_mips2.py`, ...) are the same author's
work under AGPL-3.0, like this project.
