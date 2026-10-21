# Bomberman 64 decompilation

A matching decompilation of Bomberman 64 (Hudson, 1997), aimed at a PC port
(native and WebAssembly) with online multiplayer over WebRTC. The model is
the Blast Corps decomp in `../BlastCorps`: same goals, same rules, and its
tools are the first place to look before writing a new one. docs/ROADMAP.md
has the phases. Phases 0 (scaffolding) and 1 (stage 1: the ROM built from
its pieces, archives from inflated files) are done. Nothing is
disassembled or decompiled yet.

## Versions

`VERSION` is `us` (`NBME`, the working version) or `eu` (`NBMP`). Both build
from one tree, and eu's differences will be `#if`s in the same C
(`VERSION_US`/`VERSION_EU`), with us's names everywhere, as in Blast Corps.
The `NHAJ` ROM in this directory is a different game (*Bomberman 64*,
2001), and it is not a version.

## Build

```
make setup                     # once: submodules, .env venv, IDO 5.3, LZSS helper
make VERSION=us extract        # splat split, after the baserom sha1 check
make VERSION=us                # relink, sha1-checked
make VERSION=us lzss-check     # encoder reproduces every compressed member
```

`extract` has splat cut the fixed segments into `assets/*.bin`. Then
`tools/assets.py extract` turns each archive (`bankNN`) into
`assets/bankNN/` (inflated `NN.bin`, stored `NN.raw`, `index.yaml`,
`archive.yaml`) and fails unless it rebuilds exactly. `make` rebuilds the
archives into `build/<v>/archives/` and links the ROM from those. Banks
are fixed at their ROM slots until stage 2 symbolizes the code's
references to them (docs/ROADMAP.md, phase 1, "Not yet").

`asm/` and `assets/` hold one version at a time. The Makefile refuses to
build a version other than the one in `.version`, so `make clean` first.

## Rules that already apply

- **The sha1 is the arbiter.** `bm64.<v>.sha1` is the original ROM. Every
  change keeps `make` passing for both versions.
- **Configs are generated.** `bm64.<v>.yaml` comes from `tools/layout.py
  <v>`, which reads the archives out of the ROM. Change the generator,
  not the yaml, then run `tools/layout.py --check <v>`.
- **Pad bytes are data.** Archive tails sometimes carry a stray halfword
  (docs/LAYOUT.md). They are kept (`tail` in `assets/bankNN/archive.yaml`), never assumed zero.
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
