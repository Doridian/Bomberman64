# Bomberman 64 decompilation

A matching decompilation of Bomberman 64 (Hudson, 1997), aimed at a PC port
(native and WebAssembly) with online multiplayer over WebRTC. The model is
the Blast Corps decomp in `../BlastCorps`: same goals, same rules, and its
tools are the first place to look before writing a new one. docs/ROADMAP.md
has the phases. Phases 0-2 are done: the ROM is built from its pieces
(stage 1) and every code segment from splat's asm (stage 2), and a
shifted build runs the same as the original. Phase 3 has libultra named
(2.0I, docs/LIBULTRA.md) and Hudson's allocator identified (GNU
gmalloc, docs/LIBMALLOC.md). Phase 4's C pipeline works
(docs/DECOMPILING.md), with a few objects decompiled. Each module's
`.data`/`.rodata`/`.bss` is cut per object as far as its C objects from
its first on are listed in `data_split.txt` (docs/DECOMPILING.md, "Data").

## Versions

`VERSION` is `us` (`NBME`, the working version), `eu` (`NBMP`) or `jp`
(`NBMJ`, *Baku Bomberman*). All three build from one tree, and the
others' differences are `#if`s in the same C
(`VERSION_US`/`VERSION_EU`/`VERSION_JP`), with us's names everywhere, as
in Blast Corps. jp differs the most: text, pictures, voices, and some
code (docs/LAYOUT.md, "JP"). The `NHAJ` ROM in this directory is a
different game (*Bomberman 64*, 2001), and it is not a version.

## Build

```
make setup                     # once: submodules, .env venv, IDO 5.3, LZSS helper
make VERSION=us extract        # baserom sha1 check, archives, code image, splat, postsplit
make VERSION=us                # assemble, link, build the ROM, sha1-checked
make VERSION=us lzss-check     # encoder reproduces every compressed member
make VERSION=jp                # the same for eu and jp (make clean between versions)
make vermap                    # regenerate vermap.eu.txt and vermap.jp.txt (needs the ROMs); extract renames with them
make VERSION=us SHIFT=1        # shifted build in build/us-shift/, not sha1-checked
make VERSION=us shift-check    # both, run in mupen64plus (system or $M64P_DIR), state compared
tools/tas.py check 4908M build/jp/bm64.jp.z64 build/jp-shift/bm64.jp.z64  # a TAS on two ROMs (docs/TAS.md)
tools/find_abs.py us           # addresses left without a relocation (should be 0)
tools/progress.py              # how much is C (docs/DECOMPILING.md has the loop)
tools/data_split.py us         # data_split.txt's sizes against the built C objects
tools/data_c.py <mod> <lo> <hi>  # C definitions for a run of asm data or bss
tools/build_ultralib.sh        # libultra reference objects in build/ultralib
tools/gen_symbols.py us build/ultralib/build/I/libultra_rom  # library names
tools/libmalloc_check.py       # gmalloc against all three ROMs
tools/test_assets.py --rom us eu jp  # every picture and model rebuilds
tools/inventory.py --check docs  # docs/inventory.<v>.csv up to date
```

After `gen_symbols.py`, run `tools/layout.py <v>` (the new object
boundaries) and `make clean` before extracting again. docs/LIBULTRA.md has
the workflow.

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

`shift-check` uses the system's mupen64plus (core and rsp-hle), or the
official Linux bundle unpacked, with `M64P_DIR` pointing at it. It uses
two small plugins of ours (`tools/src/m64p_*.c`): no video, and a
scripted controller (`tools/inputs/menus.txt`, from a blank save through
the opening into the first stage). Runs are exactly repeatable, so any
difference in the modules' data fails. The game seeds its RNG from the
cycle counter (`osGetTime()` in main_code's init), which a bigger build
legitimately changes, so both ROMs run with that seed pinned
(`tools/shift_check.py` has the details, and why bss isn't compared).
Run emulator and build commands under `nice -n 10`, headless.

## Rules that already apply

- **The sha1 is the arbiter.** `bm64.<v>.sha1` is the original ROM. Every
  change keeps `make` passing for every version.
- **Configs are generated.** `bm64.<v>.yaml` comes from `tools/layout.py
  <v>`, which reads the archives out of the ROM. Change the generator,
  not the yaml, then run `tools/layout.py --check <v>`.
- **Pad bytes are data.** Archive tails sometimes carry a stray halfword
  (docs/LAYOUT.md). They are kept (`tail` in `assets/bankNN/archive.yaml`),
  never assumed zero.
- **Nothing absolute.** After a change to the split or the tools,
  `tools/find_abs.py <v>` must report 0 and `make shift-check` must pass,
  for every version. A new kind of reference splat leaves as a number gets
  a rule in `postsplit.py`, not a hand-edited asm file (extract
  regenerates them).
- **Fixed places stay fixed.** The entries (0x80000400, 0x80225800,
  0x80043000), zerojump's page, ROM segment 2 for main_code, the tables at
  0x30000/0x30800 and the bank slots are what the loaders hard-code.
  `ld_fix.py` keeps them, and the shift pads go after the entries.
- **The LZSS encoder must stay exact.** `make lzss-check` on every ROM
  after any change to `tools/hudson_lzss.py` or `tools/src/hudson_lzss.c`.
  The Python and C encoders must agree (docs/COMPRESSION.md).
- **eu and jp have us's names.** `vermap.<v>.txt` is generated by
  `tools/vermap.py` (`--check` verifies it), and `make VERSION=<v>
  extract` renames the version's symbols with it (docs/LAYOUT.md, "The
  US to EU map"); what us lacks is `..._eu`/`..._jp`. Text objects are
  named for us's offset of the same code (`tools/layout.py`), so a C
  file is one object everywhere. Names go in `symbol_addrs.us.txt` and
  reach the others by themselves.
- **Library names are generated.** `symbol_addrs.<module>.<v>.txt` and
  `lib_objects.<v>.txt` come from `tools/gen_symbols.py` (below its marker
  line); names given by hand go above the marker or in
  `symbol_addrs.<v>.txt`.
- **Don't guess names.** Only libraries get real names, from matching.
  Everything else keeps `func_`/`D_` address names (us's addresses in
  every version). Overlays share VRAM `0x80043000`, so their names carry
  the bank and entry (docs/ROADMAP.md, phase 2).
- **C must match in every version.** A C file is built for us, eu and
  jp; version differences are `#if VERSION_EU`/`#if VERSION_JP`, with
  us's code as the default. Their asm carries us's names
  (`tools/vermap.py`), so the C uses us's names in all three
  (docs/DECOMPILING.md, "Versions").
- **Data sizes come from the compiler.** `data_split.txt` lists a
  module's C objects from its first on with the section sizes IDO builds
  them to (`tools/data_split.py` checks them), and `tools/layout.py` cuts
  the module's data at those. An object is listed only once its C defines
  all its `.data` and `.bss`; one outside a module's cut defines no data
  (docs/DECOMPILING.md, "Data").
- **Port-only changes are `#ifdef TARGET_PC`.** The port must stay
  deterministic from the start: docs/NETPLAY.md, "Requirements", lists
  what online play needs from it.
- Straight to `main`; no branches.

## Pointers

- docs/LAYOUT.md: the ROM map, the archive format, US↔EU and US↔JP differences.
- docs/COMPRESSION.md: Hudson's LZSS stream and encoder.
- docs/LIBULTRA.md: the libultra revision, the matching, what doesn't match.
- docs/ROADMAP.md: phases 1–8.
- docs/DECOMPILING.md: C files, flags, m2c/fdiff/permuter, eu and jp, data.
- docs/TAS.md: TASVideos' movies played headless (`tools/tas.py`); how far they sync (not to the end).
- docs/NETPLAY.md: WebRTC (libdatachannel, the browser's WebRTC,
  matchbox-compatible signaling), lockstep then rollback.
- Bomberhackers/bm64 (GitHub) is an earlier US decomp against a
  decompressed ROM. Its splat.yaml and per-file IDO flags are useful
  evidence, but it has no license, so don't copy its code.
