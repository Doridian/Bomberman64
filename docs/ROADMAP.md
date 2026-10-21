# Roadmap

The end state is the one Blast Corps reached (`../BlastCorps`): every ROM
rebuilds byte for byte from one source tree, all of the game's code is C
(no `GLOBAL_ASM` left, and no handwritten asm in the port), the ROM's assets
are editable files that rebuild to the same bytes, and the same C builds a
PC port (native and WebAssembly). Bomberman 64 adds one goal on top: online
multiplayer over WebRTC, native and browser alike (docs/NETPLAY.md).

Versions: **us** (`NBME`) is the working version and **eu** (`NBMP`) builds
from the same C with `#if`s, the way Blast Corps does it (its CLAUDE.md,
"Versions"). See docs/LAYOUT.md for the ROMs and README.md for the hashes.

## Phase 0 — scaffolding (done)

- Repo, submodules (asm-differ, asm-processor, m2c, decomp-permuter), a
  venv with pinned splat64/spimdisasm, IDO 5.3 from decompals'
  static recompilation (`tools/get_ido.sh`).
- `bm64.<v>.sha1` for each ROM, and `make check`.
- The top-level layout of both ROMs (docs/LAYOUT.md, `tools/layout.py`) and
  the Hudson LZSS codec (docs/COMPRESSION.md, `tools/hudson_lzss.py`).

## Phase 1 — stage 1: the ROM as named pieces, matching

**Status:** the first half is done. `bm64.<v>.yaml` splits both ROMs into
1023 bins (every archive entry its own bin, plus the pad and tail bytes),
and `make` relinks them to the sha1. The encoder already matches every
compressed member of both ROMs (`make lzss-check`: 961/961 each). What's
left is wiring the inflated files into the build (below).

`make extract && make` splits each ROM into its segments (header, IPL3,
boot code, main code, the overlay banks, the asset region) and relinks
them, sha1-checked. The configs come from `tools/layout.py`, which reads the
boundaries from the ROM (tables give their own sizes and LZSS streams their
own lengths). They are generated, never hand-edited, as in Blast Corps
(`gen_build_yaml.py`).

The compressed members (overlays, and whatever the asset banks hold) are
inflated to files and re-deflated by `tools/hudson_lzss.py`. The ROM is
then built from the inflated data, which only works if the encoder
reproduces Hudson's output exactly. That is checked for every member
(`hudson_lzss.py check`), the same way BlastCorps' LZSS and gzip are.

## Phase 2 — stage 2: code split and reassembly

- **boot_code** (ROM `0x1000`, VRAM `0x80000400`): the entry point, the
  scheduler, the main loop, libultra, libaudio.
- **zerojump** (ROM `0x1CBC0`, VRAM `0x80042000`): a jump table the
  overlays call through (see bm64's `zerojmp`).
- **main_code** (ROM `0x40000`, VRAM `0x80225800`), uncompressed.
- **overlays**: the banks of LZSS-compressed overlays, many sharing VRAM
  `0x80043000`. Each overlay gets its own splat segment and object
  directory, and its own symbol namespace (`ovl<bank>_<n>_func_XXXXXXXX`),
  because addresses repeat across overlays.

The deliverable is `make` reassembling every code segment from splat's asm
(one `.s` per function under `asm/nonmatchings`, pulled in by
`GLOBAL_ASM`), recompressing the overlays, and matching the sha1. The first
rebuild after that is a `SHIFT=1` build that pads every code segment's
`.text`/`.data`. It proves that nothing depends on an absolute address,
so every pointer splat left as a number gets found. Blast Corps needed
`postsplit.py`, `link_syms.py` and `find_abs.py` for this. Port the parts
that apply rather than rewriting them; modern splat already does some of
it (`migrate_rodata_to_functions`, `ld_bss_is_noload`, `--emit-relocs`
style checks).

Per-object `.data`/`.rodata`/`.bss` (one C file owns its data) is part of
this phase, not later. It is what lets a decompiled file own its data
from its first function onwards.

## Phase 3 — libraries

- Identify the libultra revision (header strings, `__osViInit` tables,
  which `osVi*` modes exist; the reference decomp's split lists the
  objects) and build ultralib for it, IDO with its own flags. Name
  libultra by matching ultralib objects (`gen_symbols.py`/`libmatch.py`
  in Blast Corps).
- Hudson links its own allocator (`libmalloc/gmalloc`, built `-g`) and
  probably an older libaudio. Identify those the same way.
- `symbol_addrs.<module>.<v>.txt` is generated, and only library code gets
  real names until the game's code is understood. Don't guess names.

## Phase 4 — decompilation (us, then eu)

- IDO 5.3, `-mips1` (or `-mips2`: check `MIPS_VERSION`), mostly `-O2`
  with some files `-O3` and a few `-g`, per bm64's Makefile, which is
  good evidence but needs checking per file. The loop is Blast Corps' (m2c,
  `fdiff.py`, the permuter), in docs/DECOMPILING.md once it exists.
- `tools/progress.py` per segment and per overlay.
- eu from the same C: `tools/vermap.py`'s approach (align eu's functions
  to us's by masked bodies, map the data through them) generates eu's
  configs from us's. Names are us's everywhere, and eu-only things get a
  `_eu` suffix.
- Hudson's game code is likely all C. Only libultra's `.s` files are real
  asm, and the port doesn't use those.

## Phase 5 — assets

Inventory the asset banks (models, textures, palettes, animations, the
sound banks and sequences), extract them to editable formats, and rebuild
them matching. The ROM link then places everything by built size, so an
edited asset can change size. Blast Corps' `tools/assets.py` and
`assetlib/` are the template. For the port, the remakeable assets
stay out of the executable and are loaded from the user's ROM at startup
(`ASSET_INIT`, as in Blast Corps).

## Phase 6 — PC port

The same architecture as Blast Corps' port (its docs/PORT.md):

- One CMake build. The game's C, compiled by the host's compiler, in host
  byte order and pointer size. `#ifdef TARGET_PC` in `src/` for port-only
  changes. Native pointers, with `Gfx` as wide as a pointer.
- libultra replaced by a host layer (threads by ucontext or host
  threads, one at a time; VI, PI/DMA, SI/controllers, the EEPROM or
  controller pak as files). The RSP/RDP is a display-list renderer, and
  audio runs through libaudio's C.
- **Overlays:** on the N64 they share VRAM. In the port every overlay is
  linked in at once, with distinct symbols, and "loading" an overlay
  selects its code and resets its data/bss to the ROM's initial values.
  The zerojump table becomes a table of function pointers.
- Reuse is preferred over rewrite. Blast Corps' `port/host`, renderer and
  `libaudio` port are the starting point. Whatever is game-agnostic is
  shared or copied with attribution in NOTICES.md.
- Tests from the beginning: deterministic headless runs against committed
  references (`port/tools/test.py` in Blast Corps), sanitizers, a
  big-endian host and a 32-bit host. The determinism work is also netplay's
  foundation (docs/NETPLAY.md, "Requirements").

## Phase 7 — WebAssembly

emsdk, headless under node for the tests, and a page (`port/web/`) that
asks the player for their own ROM. GitHub Pages builds it from the
repository alone, as Blast Corps' `pages.yml` does.

## Phase 8 — online multiplayer

docs/NETPLAY.md. Its port requirements (determinism, a stepping API,
snapshots and cross-host hashes) start in phase 6. The network code comes
after the port runs battle mode correctly.

## Out of scope, for now

- The **Japan** ROM in this directory (`NHAJ`) is a different game:
  *Bomberman 64* (2001), released only in Japan, and not the Japanese
  release of this one. It is hashed in README.md for completeness. It
  would be its own project.
- *Baku Bomberman* (`NBMJ`, Japan, 1997) is the Japanese release of
  this game. It would be a third version (`jp`) if a dump is added.
