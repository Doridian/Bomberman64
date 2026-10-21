# Decompiling

How a text object becomes C, and what has mattered for matching so far.
The loop and the tools are Blast Corps' (`../BlastCorps`, its
docs/DECOMPILING.md), adapted to one code image with overlays.

## The pipeline

- **A C file per text object.** An object is C when `src/` has its file,
  named as the asm is: `src/40300.c` for main_code's `asm/40300.s`,
  `src/main_code_entry.c`, `src/overlays/ovl_09_01/ovl_09_01_entry.c`.
  `tools/layout.py` makes such an object a `c` subsegment (`c_source()`),
  so the config still comes only from the generator: regenerate it and
  `layout.py --check` after adding or removing a file.
- **GLOBAL_ASM.** A function not yet decompiled is a line
  `#pragma GLOBAL_ASM("asm/nonmatchings/<object>/<function>.s")`. On
  extract, splat writes those `.s` files for every function of a `c`
  object that the C file doesn't define. asm-processor
  (`tools/asm-processor/build.py`) compiles the C and assembles the
  GLOBAL_ASM functions in their places. A file with no GLOBAL_ASM left is
  compiled by IDO directly.
- **Compiler.** IDO 5.3 (`tools/ido/5.3/cc`, decompals' static
  recompilation), `-G 0 -Xfullwarn -Xcpluscomm -nostdinc -non_shared
  -Wab,-r4300_mul -mips1 -32` and `-O2` by default. Per-file levels are
  lists in the Makefile (`G_C_FILES`, `O3_C_FILES`), the same in every
  version. `include/common.h` is included by every file: the ultra64 types
  (`include/PR/ultratypes.h`), `uintptr_t`, `VERSION_US`/`VERSION_EU`.
  Declarations shared between files go in `include/functions.h` and
  `include/variables.h`; a name only one file uses is declared there.

To start an object:

```
tools/c_stub.py us 80420                 # src/80420.c, every function GLOBAL_ASM
tools/layout.py us && tools/layout.py eu # the object becomes `c`
rm -rf asm && make VERSION=us extract    # splat writes asm/nonmatchings/80420/
make VERSION=us                          # still sha1-matching
```

Then, per function:

```
tools/m2c.sh func_80265C9C                       # a first draft
# replace the GLOBAL_ASM line with the C, then
make VERSION=us; tools/fdiff.py func_80265C9C    # OK, or a diff
tools/permute.sh func_80265C20 draft.c           # when it's close
nice -n 10 .env/bin/python3 tools/decomp-permuter/permuter.py -j16 permuter/nonmatchings/func_80265C20
tools/progress.py                                # per module, overlays per bank (--overlays: each)
```

- `tools/fdiff.py <function>` diffs the function in `assets/code.bin`
  against `build/<v>/code.bin`. The original's range is where the name says
  the function was, so one that came out longer still diffs against
  itself; branch targets are shown relative to the function and `jal`
  targets masked. `tools/asm-differ/diff.py -mw <function>` works too
  (`diff_settings.py`).
- `tools/m2c.sh` and `tools/permute.sh` need the function's `.s` in
  `asm/nonmatchings/`, so it must still be GLOBAL_ASM when the tree was
  extracted. Splat writes no `.s` for a function the C defines; to get one
  back, put the GLOBAL_ASM line back and re-extract.
- A C object changes nothing in a shifted build: the `SHIFT=1` image of
  the tree with the C should be byte-identical to the one built from the
  asm alone (`cmp` the two `build/<v>-shift/code.bin`), which is quicker
  than `make shift-check` and catches what `find_abs.py` can't (the shift
  pad after a module's entry went missing when the entry became C, until
  `ld_fix.py` matched `.c.o` too).
- The permuter's "fake" matches (`if (1) {}` and the like) are accepted
  with a comment saying so; prefer a natural spelling when one is found.

## Compiler flags: the evidence

- **`-mips1`** for Hudson's game code: main_code's text up to its ZeroJump
  block and every overlay never read a loaded register in the next
  instruction (a nop or a scheduled instruction fills each load delay
  slot; the few hits a scan finds are loads in a branch's delay slot) and
  never use branch-likely. boot_code's libraries do both: they are
  `-mips2`, as libultra is. So are the objects after main_code's ZeroJump
  block (`B3B70` on: `beql`), Hudson's allocator and other library code
  (phase 3). Compiling 40300.c `-mips2` changes it.
- **`-O2`**, not `-O3`, for 40300 and 80420: the same C at `-O3` gives the
  same function bodies but in the reverse order within the object (IDO 5.3
  `-O3` emits a file's functions last to first), and at `-O1` the code
  differs. The Bomberhackers/bm64 Makefile builds at `-O2` with a list of
  `-O3` files (10D0, 13F0, sched, 412F0, 41FD0, 52270, 530C0) and a note
  that "a majority of the gamecode" may be `-O3`. That is evidence, not
  proof: check each object, the function order is the quickest test.
- **`-g`** for main_code's entry (`main_code_entry.c`, func_80225800):
  every value goes through the stack and the return is branched to; `-O1`,
  `-O2` and `-O0` don't give it. bm64 builds its 40000.c `-g` too. Hudson's
  `gmalloc` is `-g` in bm64 as well (another agent's area).
- asm-processor can't do `-g` with `-mips1` and GLOBAL_ASM; a `-g` file has
  to be all C before it builds (the Makefile compiles a file without
  GLOBAL_ASM directly).
- Character signedness: IDO's default (unsigned `char`, `lbu`) matched
  40300's string functions, so no `-signed`.

## Versions

eu builds from the same C. Its config comes from its own ROM, and an
object is C in eu when `src/` has a file of the eu object's name, which
for now is the same image offset as in us (true for all four C objects:
main_code's code up to 0x80420 and ovl_09_01 sit at the same places in
both). Two things differ:

- **Names.** eu's asm carries us's names: `make extract` for eu renames
  splat's address names through `vermap.eu.txt` (`tools/vermap.py`,
  docs/LAYOUT.md, "The US to EU map"), so a C file's names mean the same
  things in both versions.
- **Code.** Where eu's code really differs, the C gets `#if VERSION_EU`.
  asm-processor reads GLOBAL_ASM lines before the preprocessor, so a
  version-specific GLOBAL_ASM needs Blast Corps' `version_ifs.py` first
  (not needed yet). Once eu's objects stop lining up with us's offsets,
  the object names come from vermap too.

## Data

Each module's `.data`/`.rodata` is still one asm `rodata` block and its
`.bss` one `bss` block (docs/ROADMAP.md, phase 2, "Not yet"). Until a
module's data is split per object:

- **A C function must not produce data.** No string literals, no float or
  double constants IDO puts in `.rodata` (one with the low 16 bits zero is
  built with `lui` and is fine: 80420's `32768.0f`), no `switch` that
  becomes a jump table, no `static` or initialized globals. Check with
  `mips-linux-gnu-objdump -h build/us/src/<object>.c.o`: `.data`,
  `.rodata` and `.bss` must be empty. The functions decompiled so far are
  chosen that way.
- **Variables are `extern`,** named `D_<us address>`, and defined by the
  asm blocks.

How the split will work, object by object, as in Blast Corps:

1. An object's data is the run of the module's data block that its C
   compiles to. IDO puts a file's `.data`, then `.rodata` (early, then
   `.late_rodata`), then `.bss`, each padded to 16, and the link lays the
   objects' sections out in text order. So once one object's C defines
   all of its data, its `.data` size is known, and so is where the next
   object's starts.
2. `tools/layout.py` then cuts the module's block at those points: a
   `.data`/`.rodata`/`.bss` subsegment per C object, and an asm `data` /
   `rodata` / `bss` block for each run still unclaimed (as Blast Corps'
   `gen_code_yaml.py` does). The cut points come from a list of object
   sizes that grows as files are decompiled, not from a heuristic on the
   data (the jump-table/float heuristic disagrees with the reference
   decomp in 26 of 95 overlays).
3. `data_c.py` and `bss_c.py` (Blast Corps) write a file's definitions
   from its asm block while the block is still asm, and `inline_rodata.py`
   turns `extern` constants into literals once the file owns its `.rodata`.
   Their rules carry over: IDO lays `.data` out in definition order, `.bss`
   in order of first use, aligns each variable by its type and pads the
   section to 16.

The first candidates are the objects at the start of a module, where
nothing before them needs a size: main_code's `main_code_entry` (no data
at `-g`), then `40040`, `40300`. An overlay's first C object after its
entry is the easiest start of all, since each overlay's data block begins
with that object's data.
