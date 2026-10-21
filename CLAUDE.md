# Bomberman 64 decompilation

A matching decompilation of Bomberman 64 (Hudson, 1997), aimed at a PC port
(native and WebAssembly) with online multiplayer over WebRTC. The model is
the Blast Corps decomp in `../BlastCorps`: same goals, same rules, and its
tools are the first place to look before writing a new one. docs/ROADMAP.md
has the phases. Phases 0-2 are done: the ROM is built from its pieces
(stage 1) and every code segment from splat's asm (stage 2), and a
shifted build runs the same as the original. Not yet: per-object
`.data`/`.rodata`/`.bss` (phase 2, "Not yet"), libraries (phase 3), and no
C at all.

## Versions

`VERSION` is `us` (`NBME`, the working version) or `eu` (`NBMP`). Both build
from one tree, and eu's differences will be `#if`s in the same C
(`VERSION_US`/`VERSION_EU`), with us's names everywhere, as in Blast Corps.
The `NHAJ` ROM in this directory is a different game (*Bomberman 64*,
2001), and it is not a version.

## Build

```
make setup                     # once: submodules, .env venv, IDO 5.3, LZSS helper
make VERSION=us extract        # baserom sha1 check, archives, code image, splat, postsplit
make VERSION=us                # assemble, link, build the ROM, sha1-checked
make VERSION=us lzss-check     # encoder reproduces every compressed member
make VERSION=us SHIFT=1        # shifted build in build/us-shift/, not sha1-checked
make VERSION=us shift-check    # both, run in mupen64plus ($M64P_DIR), state compared
tools/find_abs.py us           # addresses left without a relocation (should be 0)
```

`extract` turns each archive (`bankNN`) into `assets/bankNN/` (inflated
`NN.bin`, stored `NN.raw`, `index.yaml`, `archive.yaml`; checked to
rebuild) and writes the code image `assets/code.bin`: the ROM below
0x120000, then every overlay inflated. splat splits the image
(`bm64.<v>.yaml`), and `tools/postsplit.py` makes what splat left as
numbers relative to labels. `make` links the image from the asm
(`tools/ld_fix.py` keeps the ROM's fixed positions), and `tools/rom.py`
packs the ROM from it and the archives. It recompresses the overlays and
writes the segment size table. docs/LAYOUT.md, "Loaders" and "Stage 2",
has the details.

`asm/` and `assets/` hold one version at a time. The Makefile refuses to
build a version other than the one in `.version`, so `make clean` first.

`shift-check` needs the official mupen64plus Linux bundle unpacked, with
`M64P_DIR` pointing at it. It uses two small plugins of ours
(`tools/src/m64p_*.c`): no video, and a scripted controller
(`tools/inputs/menus.txt`). Runs are exactly repeatable, so any
difference fails.

## Rules that already apply

- **The sha1 is the arbiter.** `bm64.<v>.sha1` is the original ROM. Every
  change keeps `make` passing for both versions.
- **Configs are generated.** `bm64.<v>.yaml` comes from `tools/layout.py
  <v>`, which reads the archives out of the ROM. Change the generator,
  not the yaml, then run `tools/layout.py --check <v>`.
- **Pad bytes are data.** Archive tails sometimes carry a stray halfword
  (docs/LAYOUT.md). They are kept (`tail` in `assets/bankNN/archive.yaml`),
  never assumed zero.
- **Nothing absolute.** After a change to the split or the tools,
  `tools/find_abs.py <v>` must report 0 and `make shift-check` must pass,
  for both versions. A new kind of reference splat leaves as a number gets
  a rule in `postsplit.py`, not a hand-edited asm file (extract
  regenerates them).
- **Fixed places stay fixed.** The entries (0x80000400, 0x80225800,
  0x80043000), zerojump's page, ROM segment 2 for main_code, the tables at
  0x30000/0x30800 and the bank slots are what the loaders hard-code.
  `ld_fix.py` keeps them, and the shift pads go after the entries.
- **The LZSS encoder must stay exact.** `make lzss-check` on both ROMs
  after any change to `tools/hudson_lzss.py` or `tools/src/hudson_lzss.c`.
  The Python and C encoders must agree (docs/COMPRESSION.md).
- **Don't guess names.** Only libraries get real names, from matching.
  Everything else keeps `func_`/`D_` address names (us's addresses in
  every version). Overlays share VRAM `0x80043000`, so their names carry
  the bank and entry (docs/ROADMAP.md, phase 2).
- **Port-only changes are `#ifdef TARGET_PC`.** The port must stay
  deterministic from the start: docs/NETPLAY.md, "Requirements", lists
  what online play needs from it.
- Straight to `main`; no branches.

## Pointers

- docs/LAYOUT.md: the ROM map, the archive format, US↔EU differences.
- docs/COMPRESSION.md: Hudson's LZSS stream and encoder.
- docs/ROADMAP.md: phases 1–8.
- docs/NETPLAY.md: WebRTC (libdatachannel, the browser's WebRTC,
  matchbox-compatible signaling), lockstep then rollback.
- Bomberhackers/bm64 (GitHub) is an earlier US decomp against a
  decompressed ROM. Its splat.yaml and per-file IDO flags are useful
  evidence, but it has no license, so don't copy its code.
