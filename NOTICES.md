# Notices

This project's own code is licensed under the GNU Affero General Public
License, version 3 or later: see [LICENSE](LICENSE).

Some files in the repository are not the project's own work. Each entry
says where they come from and on what terms they are here.

| Component | Where it is | Terms |
| --- | --- | --- |
| decompals/ultralib (libultra reconstruction) | `include/ultralib/`, `src/libultra/` | no licence file; see below |
| Blast Corps decomp tools | `tools/elf_mips2.py` and others adapted from `../BlastCorps` | AGPL-3.0, same author |

---

## libultra: decompals/ultralib

`include/ultralib/` is a copy of the `include/` directory of
[decompals/ultralib](https://github.com/decompals/ultralib) at commit
`e24c836796df4bf520ff8b11a5c9d2cea3a66cbd` (the one
`tools/build_ultralib.sh` builds). Most files under `src/libultra/` start
from that commit's `src/` file of the same name and carry this game's
differences, each described at the top of the file; a few
(`io/pfsresizefile.c`, and the older revisions' code in `io/conteep*.c`,
`io/contreaddata.c`, `io/motor.c`) are decompiled from the game in
ultralib's style. Several of the older-revision forms were first matched
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

## Blast Corps decomp

Tools adapted from `../BlastCorps` (`tools/libmatch.py`,
`tools/gen_symbols.py`, `tools/elf_mips2.py`, ...) are the same author's
work under AGPL-3.0, like this project.
