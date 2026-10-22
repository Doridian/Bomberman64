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
- **`-O3` objects show it in their code**, so an object can be classed
  before any C is written (m2c on its asm: "saved_reg_*" or "unset
  register" in its output is the giveaway). IDO 5.3 `-O3` (umerge/uopt
  across the file):
  - inlines a file's small functions into their callers in that file, and
    still emits them (40FB0: func_80226860 holds func_80226818's and
    func_802267E0's bodies; 53D70's func_802395A8 holds four copies of
    func_8023957C);
  - allocates registers across calls within the file: a caller keeps a
    value in a caller-saved register across a call to a function of the
    file that doesn't touch it (9BFD0: func_80282034 keeps `a1` in `t2`
    across func_80281FA0), a callee reads its caller's `s` registers, and
    a `static` callee may take an argument in a non-argument register
    (ACA00: func_802922A4 passes func_80292200 its second argument in `t0`);
  - emits the functions in the order it processes them: last to first in
    the source, except that a function's callees from the same file come
    out just before it if they haven't yet. So the source order is the
    reverse of the object's (40FB0.c is written last function first).
  - moves a float argument that arrives in an integer register straight
    to a float register (`mtc1 $a2, $f16`), where `-O2` stores it to its
    home slot and reloads it (`sw $a2, 8($sp)` ... `lwc1`). A function
    taking three floats shows it at once (4DE50's func_80234500, 4ED50's
    func_802346C8).
  Seen so far: 40FB0, 4DE50, 4ED50, 9BFD0, 995C0, 86680, 53D70, 9A5F0 and
  ACA00 are `-O3`; 404C0, 5E090, 87190, 87730, 99F40, A4860 and B11F0 are
  `-O2` (no
  inlining between functions that call each other, no cross-call
  registers; A4860's func_8028A318 calls three small functions of its
  own file and inlines none). asm-processor can't do `-O3`, so an `-O3`
  object is C only once all of its functions are.
- **IDO allocates expression temporaries per source line.** A function
  that builds display-list commands matched only with each command on
  one line, as gbi.h's macros expand (87730's func_8026D2C4); written one
  statement per line, the later commands' constants land in `t0`-`t5`
  instead of `t6`-`t9`.
- **`-g`** for main_code's entry (`main_code_entry.c`, func_80225800):
  every value goes through the stack and the return is branched to; `-O1`,
  `-O2` and `-O0` don't give it. bm64 builds its 40000.c `-g` too. Hudson's
  `gmalloc` is `-g` in bm64 as well (another agent's area).
- asm-processor can't do `-g` with `-mips1` and GLOBAL_ASM; a `-g` file has
  to be all C before it builds (the Makefile compiles a file without
  GLOBAL_ASM directly).
- Character signedness: IDO's default (unsigned `char`, `lbu`) matched
  40300's string functions, so no `-signed`.

## Hudson's C: patterns that have mattered

- **Array indexing, not pointer walking.** Loops are `for (i = 0; i < N;
  i++)` over `D_xxx[i].field`, written out each time (87190's
  func_8026CE28 matched only once its `entry` pointer became
  `D_800A7F30[i]` everywhere). IDO turns them into pointer loops itself
  and unrolls a constant-count loop by 4, the remainder iterations first
  (99F40's 6-map and 7-callback loops; 404C0's 8-file loops).
- **`break` loops aren't unrolled, `return` loops are.** A search loop
  that returns from inside is unrolled; one that `break`s isn't (87190's
  func_8026CBD4 vs func_8026CC34).
- **The index after the loop.** After `for (i = 0; i < 4; i++)` over
  `D[i]`, the code goes on with `D[i]` (the fifth entry), and IDO keeps
  the loop's pointer for it (B11F0's func_802972D0 and func_80297ADC);
  writing `D[4]` loads the address afresh.
- **Ternaries.** `return a > 0.0f ? 1 : a < 0.0f ? -1 : 0;` is how the
  sign functions are written (4DE50); as `if`s the -1 comes out on a
  different path.
- **Narrow parameters show.** A `u16`/`s16` parameter makes IDO store
  `$a0` to `0($sp)` in a leaf function and start its temporaries at `$t7`
  (4ED50's func_80236ACC).
- **One exit for a found case.** `if (...) { ... } else { ... } return i;`
  rather than two returns (404C0's func_80226460).
- **Constants of different types are kept apart.** Storing -1 into an
  `s32`, a pointer and a `u32` field takes three registers (87190's
  func_8026C990); that is how the fields' types show.
- **Comparison operands come out reversed**: `D != x` gives `beq x, D`,
  and `a + b` gives `addu` with the operands as IDO evaluated them, which
  is usually the source order reversed; flip one when only the operand
  order of a `beq`/`addu` differs.
- **Unused-looking arguments are passed through.** A wrapper whose callee
  takes more arguments than it sets usually took them itself
  (5E090's func_80243BA8, 9BFD0's func_80281900: the `a` registers are
  left as they came in).
- **Busy-waits on a flag** are `while (flag) { func_80297DC0(); }`, and an
  "impossible" argument is trapped with `while (1) {}` (A4860).
- **Callbacks** keep their argument: `D_802B01F8[arg1 - 1](arg0)`
  (99F40), where the array starts one entry after the symbol the asm
  indexes from.

## Versions

eu builds from the same C. Its config comes from its own ROM, and an
object is C in eu when `src/` has a file of the eu object's name, which
for now is the same image offset as in us (true for every C object so
far: main_code's code up to 0xA4860 and ovl_09_01 sit at the same places
in both). Two things differ:

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

A module's `.data`, `.rodata` and `.bss` are cut per object where the C
shows them, the way Blast Corps did it, except that the cut points come
from the compiler, not from a heuristic on the data (one that put the
boundary above every stored-to address and below every jump table and
float constant disagreed with the reference decomp in 26 of 95 overlays).

**How the cut works.** IDO pads each of a file's sections to 16, and the
link lays out every object's `.data` in text order, then every object's
`.rodata` (strings and other early constants, then `.late_rodata`: jump
tables, floats and doubles), then, in the bss section, every object's
`.bss`. So once an object's C defines all of its data, its section sizes
say where the next object's start. `data_split.txt` lists them: per
module, the C objects from its first on, with the sizes IDO builds them
to (`<module> <object> <.data> <.rodata> <.bss>`), and, per version,
where the objects' `.data` start if something else comes first
(main_code's RSP code) and where their `.rodata` start (the module's
.data/.rodata boundary), when the list doesn't cover the whole module.
`tools/layout.py` cuts the module's block from those: a `.data`,
`.rodata` and `.bss` subsegment for each listed object, and asm for the
rest, `data` up to the boundary (the link keeps it before the `.rodata`),
`rodata` after it and one `bss` block. The cut stops at the first object
not listed; everything after it stays asm, however much of it is C. The
ZeroJump stub block has no data and is skipped. Where every object of a
module is listed, the boundary is the compiler's and layout.py checks the
sizes add up to the block (and takes the module's bss size from them).

Cut so far (us and eu alike):

| module | objects | .data/.rodata boundary |
|---|---|---|
| ovl_09_01 | all: `ovl_09_01_entry`, `120010` (.data 0x30, .rodata 0x50: the handler's jump table, .bss 0x50) | 0x80044990 (the compiler's) |
| main_code | `main_code_entry`, `40040` (.data 0x30: two tables), `40300` (.data 0x10: the bump pointer) after the RSP code at 0x8029D250-0x8029F570 | not shown yet: none of the three has .rodata |

The sizes are the same in both versions as long as the C is; an object
whose data differs between them will need a version column.

**Making an object own its data:**

1. Decompile the object's functions, and write its `.data` and `.bss`
   definitions: `tools/data_c.py <module> <start> <end> [--c src/<object>.c]`
   prints them from the extracted asm for a VRAM run of the data block or
   of the bss (types from the file's `extern`s, `u8` arrays otherwise),
   and `tools/inline_rodata.py src/<object>.c` turns `extern` strings,
   floats and doubles into literals. The run is the object's own: from
   where the previous object's ends to the next 16-byte boundary its
   references and padding show.
2. `make`, then `tools/data_split.py us --add <module> <object>` appends
   its built sizes. Check the line: its `.rodata` is only the C
   functions' share until the object owns it (step 3), so a file with
   GLOBAL_ASM functions that have jump tables or constants needs the size
   from the ROM. Give the module's `@us`/`@eu` `rodata=` start if the
   object has .rodata and isn't the module's last.
3. `tools/layout.py us && tools/layout.py eu`, `make clean`, extract and
   `make` for both versions. splat now writes the GLOBAL_ASM functions'
   jump tables and constants into their `.s` (`.late_rodata`), which
   asm-processor puts into the object, and the asm block shrinks by the
   object's share. `tools/data_split.py <v>` checks every listed object's
   sizes against its build.

What mattered:

- An object is listed only once its C defines all of its `.data` and
  `.bss` (GLOBAL_ASM can't bring those, only `.rodata`). A wrong size
  shifts every later cut, and the sha1 catches it.
- IDO lays `.data` out in definition order, `.bss` in the order it first
  sees each variable (defined or used; an extern doesn't count), so the
  `.bss` definitions go before the first function. Unreferenced bytes
  between variables are `u8 D_<address>[n]` arrays (120010.c has two).
  A table's trailing zeros may be its own or the section's padding to 16:
  the bytes are the same, so pick the one the code suggests and say so.
- A `switch` gets its jump table only when its cases are dense enough:
  120010.c's handler needs all of cases 1 to 17, most of them empty
  (Blast Corps: "Empty cases still count toward IDO's jump-table
  decision").
- Defining a variable in its own file didn't change the code that uses it
  (40300's bump pointer, 40040's tables), so the `extern` can simply
  become the definition.
- Local declaration order sets stack slots: 40040's `count` had to come
  first.
- A C object changes nothing in a shifted build: the `SHIFT=1` image with
  the cut is byte-identical to the one built from the asm alone, and
  `ld_fix.py`'s data pad still goes at the module's `_DATA_START`.

**Objects not in the cut** (any object after the first one not listed)
still can't produce data: no string literals, no float or double
constants IDO puts in `.rodata` (one with the low 16 bits zero is built
with `lui` and is fine: 80420's `32768.0f`), no `switch` that becomes a
jump table, no `static` or initialized globals. Check with
`mips-linux-gnu-objdump -h build/us/src/<object>.c.o`: `.data`, `.rodata`
and `.bss` must be empty. Their variables are `extern`, named
`D_<us address>`, and defined by the asm blocks.

The next candidates are the objects that extend a cut (main_code's
`404C0`) and each overlay's first object after its entry, where nothing
before it needs a size. Library objects have known sizes from their
reference builds, but boot_code starts with its handwritten entry, and
main_code's libraries come after most of its game code, so they don't
help yet.
