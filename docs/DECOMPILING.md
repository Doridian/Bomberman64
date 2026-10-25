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
  (`include/PR/ultratypes.h`), `uintptr_t`, `VERSION_US`/`VERSION_EU`/`VERSION_JP`.
  Declarations shared between files go in `include/functions.h` and
  `include/variables.h`; a name only one file uses is declared there.

To start an object:

```
tools/c_stub.py us 80420                 # src/80420.c, every function GLOBAL_ASM
tools/layout.py us && tools/layout.py eu && tools/layout.py jp # the object becomes `c`
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
tools/progress.py                                # per module, overlays per bank (--overlays: each); +drafts counts nonmatching/ too
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

## NON_MATCHING drafts

An `-O3` object can't keep GLOBAL_ASM functions: IDO inlines, orders and
allocates across the whole file (below), so its functions come out right
only with all of them C, and it goes into `src/` only once every one
matches. A complete draft that comes
within a few instructions goes into `nonmatching/` instead, at the path
it will have in `src/` (`nonmatching/overlays/ovl_0E_12/1D6120.c`, plus
its `_entry.c` if drafted). Nothing builds it into the ROM: the object
stays asm, every sha1 is unchanged, and the C is there for the PC port and
for the next matching pass. It is outside `src/` because `tools/layout.py`
makes any `src/<seg>/<obj>.c` a C object. An `-O2` or `-g` object doesn't
go there: its unmatched functions stay GLOBAL_ASM in `src/`.

Each draft starts with a comment giving its flags, the words that still
differ per version, and what differs, function by function:

```
/*
 * NON_MATCHING: ovl_0E_12's game object, complete; not in the ROM.
 * flags: -O3
 * differing words: us 5, jp 5
 *
 * - func_ovl0E_12_80043164 (3 words): ...
 */
```

`tools/nonmatching.py [draft.c ...]` compiles every draft (or the ones
named) with its flags and compares it with the extracted version's
original, function by function (`tools/fcmp.py`'s comparison, which it
imports): the functions that match, those that differ with their word
counts, and the total. A function already C in `src/` is found in the
linked build's map, so `make` first. `make nonmatching-check` runs it with
`--check`, which fails if a draft doesn't compile or differs in more words
than its header records for the version, so a change to a shared header
or a tool can't silently make a draft worse. When a draft gets better,
lower its number.

Once a draft matches in every version, it moves to `src/` as any C object
does: `git mv` it, drop the header's NON_MATCHING lines, add it to the
Makefile's `O3_C_FILES` (and `MIPS2_C_FILES` if `-mips2`), regenerate the
configs (`tools/layout.py`) and extract again, then give it its data
(below). Until then `data_split.txt` doesn't list it: its data stays in the
module's asm blocks, though the draft defines it.

## Compiler flags: the evidence

- **`-mips1`** for Hudson's game code: main_code's text up to its ZeroJump
  block and every overlay never read a loaded register in the next
  instruction (a nop or a scheduled instruction fills each load delay
  slot; the few hits a scan finds are loads in a branch's delay slot) and
  never use branch-likely. boot_code's libraries do both: they are
  `-mips2`, as libultra is. So are the objects after main_code's ZeroJump
  block (`B3B70` on: `beql`), Hudson's allocator and other library code
  (phase 3). Compiling 40300.c `-mips2` changes it. The game's own C there
  (`B6680`, render-mode and combiner strings, matrix rotations) is listed
  in the Makefile's `MIPS2_C_FILES`.
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
    In detail (small test files): the callees come out in the reverse
    order of their last calls; a `static` is emitted only that way, when
    its first caller is (its stub too, if it was inlined everywhere); a
    global at its own turn, unless a caller processed before it pulled it
    out. A helper defined above its caller (processed after it) therefore
    sits just before the caller, one defined below at its own place:
    9A5F0's text-drawing helpers come out ahead of their caller in the
    object, so they are above it in the source. A global is inlined only
    if small (4E030's func_80233C30 isn't); a `static` of the same size
    is.
  - moves a float argument that arrives in an integer register straight
    to a float register (`mtc1 $a2, $f16`), where `-O2` stores it to its
    home slot and reloads it (`sw $a2, 8($sp)` ... `lwc1`). A function
    taking three floats shows it at once (4DE50's func_80234500, 4ED50's
    func_802346C8).
  Seen so far: 40FB0, 412F0, 41FD0, 4DE50, 4E030 (4DE50's second half:
  its wrappers call 4DE50's compares with a `jal`, which -O3 would inline
  in one file), 4ED50, 52270 (jp's func_8023876C has no TV-type
  switch: `#if VERSION_JP`), 530C0, 53D70, 86680, 995C0, 9A5F0, 9BFD0, ACA00,
  AFBF0, B6680 (`-mips2`), ovl_0A_02-05's, ovl_0C_03's, ovl_0E_09's, ovl_12_02's, ovl_12_04's, ovl_17_01's and ovl_17_10's objects are `-O3`; 404C0, 5E090, 87190, 87730,
  99F40, A4860 and B11F0 are `-O2` (no
  inlining between functions that call each other, no cross-call
  registers; A4860's func_8028A318 calls three small functions of its
  own file and inlines none); 54BE0 (one function) builds the same at
  both. B2410 (setjmp/longjmp) and B2500 (`mtc0` WatchLo) are handwritten
  asm. asm-processor can't do `-O3`, so an `-O3`
  object is C only once all of its functions are.
- **Arguments kept in `t` registers mean `-O3`.** A non-leaf function
  that copies an argument to a `t` register on entry (`move t0, a0`) and
  spills it to its home slot only around a call is `-O3`; IDO 5.3 `-O2`
  stores every such argument to its home slot in the prologue and reloads
  it (`sw a0, 32(sp)` ... `lw`), however the C is written. That puts the
  `-O2` list above in doubt: 404C0's func_80225FB8 matches only at `-O3`
  (with an unused local ahead of its `entry` struct for the frame), and the
  whole of 404C0 written last function first matches at `-O3` but for one
  register in func_80225EBC (`lui a3` where ours is `lui a2`; drafts in
  scratch/main_code/ of the main checkout). 85A10 (func_8026B72C's
  argument; func_8026B238 uses `s` registers it never saves), B11F0
  (func_80297564's `move t4, a1`) and A2840 (func_802884D4 reads `f16`
  unset) show it too. Their GLOBAL_ASM functions are the ones `-O2` can't
  give; 87190, 87730, 99F40 and A4860 match their remaining functions at
  `-O2` so far (A4860's func_8028A154 inlines func_8028A08C at `-O3`).
  78CA0 (func_8025E5EC keeps `&D_802ACFE0` in `a3` across a `jal` to
  its own file's func_8025E4A0), 7D840 (func_802639E4 passes
  func_80263040 arguments in `t1`-`t4`) and 96540 (func_8027C5E0 keeps
  `a0` in `t3` across a `jal` to func_8027C560) are `-O3` too: a value
  left in a caller-saved register across a call into the same file
  shows it as surely.
- **Banks 0x0C-0x17's overlays are `-O3` too**: ovl_0C_03, 12_02 and
  12_04 written last function first and built `-O3` match with plain calls
  where their earlier `-O2` C needed `pad[]` locals and `if (1)`s, and
  their callbacks (an argument kept in `t0`) match. ovl_17_01 (17_06 and
  17_08 share its code) passes a static's argument in saved registers.
  The bss: at `-O3` IDO lays out only the bss variables the file
  references, so the unused 4-byte fillers would go to common and the
  variables after them move. Each object ends in a row of `jr ra; nop`
  stubs, the statics nothing calls, and IDO drops an unused static's body
  but still counts what it refers to; so the last of them refers to the
  fillers (ovl_17_01's func_ovl17_01_80043FE8, ovl_0C_03's
  func_ovl0C_03_80043F74), and they stay in `.bss` where the original has
  them. What else the template showed:
  - the empty `jr ra; nop` after 80043010, 80043040 and 800430B0 are empty
    statics called by the next function;
  - a function that registers the callbacks pulls them out ahead of itself
    when it is processed at its own turn (ovl_12_02's 80043608); defined
    above the handler, it is pulled out by its caller instead and the
    callbacks stay after the handler;
  - 12_02's and 12_04's `80043258`/`80043170` (the handler's case 5) keep
    the other overlays' `unk0 == 2` test with an empty body: without it
    they are small enough to be inlined into their callers.
  - ovl_12_03 (draft in nonmatching/) inlines one body into three
    functions with a single stub: a static (`8004316C`) called only by the
    small global after its stub (`80043174`), which is inlined in turn.
    Called directly from a second function the static isn't inlined
    anywhere. Its parameters' order fixed a caller's frame, and values
    the original converts or multiplies at run time (`z * 100.0f` with
    `z` an int) are its parameters. A loop over a table that keeps the
    counter in the lower `s` register indexes the table (`tbl[i].x`)
    rather than taking `p = &tbl[i]`.
  ovl_0C_08 is still `-O2` with two GLOBAL_ASM functions: at `-O3` all of
  it matches but func_ovl0C_08_80043654 (the object setup inlined, as a
  static taking the struct's address, with 8004361C called from it), whose
  epilogue restores `s2`, `s1`, `s0` where the original restores `s0`
  first (nonmatching/overlays/ovl_0C_08/18D110.c).
  Bank 0x0E's bigger overlays (ovl_0E_09, and the drafts of 0E_05 and
  0E_12 in nonmatching/) add:
  - the set-up function the handler calls (case 2) registers the two
    callbacks; at its own turn it pulls them out ahead of the movers' tasks
    defined between them. Defined above those tasks (0E_09's 80043968 just
    above 80043D50), it is pulled out by the handler and the callbacks stay
    at the end (`scratch/bank0E/place.py` tries a function at every place);
  - the movers' tasks (`while (TRUE)` loops) start their loop on the same
    line as their set-up: `for (doneZ = 0, doneX = 0, rec->unkE =
    rec->unkC;;)` where the same statements on lines of their own put the
    table's `addiu` after the zeroing; 80043094's `i = 0; do {` likewise;
  - a store whose value is also a call's argument can come out of the
    call (`rec->unk8 = func(...); obj = rec->unk8;`, not the reverse);
  - an argument nobody sets is a register the caller happened to hold:
    80043F8C's `func_ovl0E_09_80045508(obj)` gets `a1 = 2` from its
    compares (declared with two parameters, the 2 goes into `a2`);
  - the collision checks compare `s16` fields with `0xFFFF`, never true
    (`ori $s, $zero, 0xFFFF`), where the set-up compares with `-1`.
- **`-O3` and `static`.** The rest of what IDO does at `-O3` follows from
  it processing the file as a whole:
  - a `static` function may get its own calling convention: arguments in
    `t` or `s` registers (ACA00's func_80292200: `t0`; 995C0's
    func_8027F4B0: `s1`, using `s0` unsaved), an unused first argument
    passed in its home slot (9BFD0's func_80281FA0: the callers' `sw $a0,
    0($sp)`), and its callers keep values in the `t` registers it
    doesn't touch (9BFD0: arg1 in `t2`). A static has no symbol in the
    object;
  - a static inlined into every caller still leaves an empty `jr ra; nop`
    where it would have gone, just before its first caller: splat shows
    it as an empty function, or as a second `jr ra` at the end of the
    previous one (995C0's func_8027F0B4/func_8027F0BC, 53D70's
    func_8023A310, 4E030's 0x80234230-40). Each stub is a helper to
    write;
  - a function that calls itself last becomes a loop (tail recursion):
    AFBF0's func_8029608C ends in `func_8029608C(x, y)` for two of its
    cases. Written as a `while (1)` with the arguments reassigned, the
    same code comes out but its entry block is scheduled differently
    (the loop's first load goes before the hoisted constants, not after
    them); a loop whose only difference is the prologue's order may be
    one of these;
  - a function holding `while (1) {}` isn't inlined (`for (;;) {}` is):
    53D70's func_8023957C, four copies in func_802395A8;
  - small callees are inlined by size, and dead code counts (a function
    that isn't inlined in the original but is in the C was bigger);
  - each inlined call adds its parameters' stack slots to the caller's
    frame, and every local gets a slot in declaration order, from the top
    down, even when it lives in a register: the declaration order fixes
    the frame. The order of an inlined static's parameters sets its
    spill slots too (ACA00's func_80292410 takes `(blob, entry)`);
  - where an inlined static is defined matters even though the functions
    come out in the same order: 9A5F0's func_80281278 got its loop's
    constants after the pointers' set-up (as1 orders the preheader
    differently) until its static was defined above it rather than below;
  - a function-local static is reached with `lui`/`%lo` at every access,
    where a global (extern or defined) gets its address kept in a
    register: 86680's two counters and 4ED50's constants are their
    functions' statics. A local static table a function registers also
    keeps that function from being inlined (530C0's, 4ED50's
    func_80234550);
  - a callee's declaration moves the caller's registers: 4ED50's
    func_80236658 matched only with func_80239094 undeclared (an implicit
    `int` function; as `void`, a temporary leaves `v0` for `a0`), 86680's
    func_8026C77C only with func_8026A754 returning `s32`.
  - a small global is inlined too, its own copy still emitted: B6680's
    func_8029BF30 ends in `func_8029BE80(gfx, v | b)` (the word stores come
    out second word first), and a statement whose value is dead still
    takes a temporary register: its last `if (*p++ == '1') v |= 0;` (the
    render mode's TEX_EDGE, 0 since it stopped being 0x8000) keeps the
    final pointer increment and moves every later `t` register by one;
  - a spilled value lands in an array's slot when the array holds it:
    B6680's rotations pass the radians through `tmp[0]` (`t = angle *
    DEG; tmp[0] = t; s = sinf(tmp[0]);`), which is where the original
    spills them; the frame also counts named temporaries (func_8029C680's
    four products `a`-`d`).
  - a function whose address is taken (a task or a callback) counts as a
    callee for the order: it comes out before the function taking its
    address, unless some address-taken function of the file takes an
    address itself (ovl_17_01's 3034 → 365C → 398C, ovl_17_10's 3034 →
    3E14 → 412C); then they mostly come out at their own turn. In more
    detail (ovl_0F_03 and ovl_0F_10 bear this out): a function's
    address-taken functions come out after all its direct callees,
    together, at the earliest reference in the source; among them, the
    references made in its inlined statics (in the statics' definition
    order) and then its own come out as that list reversed; statics
    nothing uses come out at the very end, in file order
    (`scratch/ovl_0F_03/order.py` lists a draft's functions and stubs at
    their addresses). A function that is address-taken and itself takes
    addresses (ovl_0F_04's 80044084) emits, at its turn, every
    address-taken function not yet out, in the reverse of the order their
    first references appear in the source (statics and unused statics
    included), then itself; one whose own address nothing takes doesn't.
    That block can't give every order: ovl_0F_04's original has functions
    at their own turns that a block would emit reversed, and what stops the
    block there isn't known (its header; `scratch/ovl_0F_04/ord/` searches
    definition orders);
  - whether a static is inlined depends on its size and on its caller's:
    ovl_17_10's func_80044464 stays a call (with its `s`-register
    convention) only because its caller writes its x and z steps out
    itself; with those steps in statics it was inlined;
  - `if (a && a && a) {}` (a fake, with a comment) ends a block without
    code: ovl_17_10's handler needs it to keep a call from being
    scheduled into the stores before it; a chained assignment (`x =
    p->unk10 = rec->unk4;`) and a ternary repeating its operand (`a = a +
    5.0f >= 360.0f ? a + 5.0f - 360.0f : ...`) each fixed a register
    choice there. The fake must test a variable the function doesn't
    otherwise use: ovl_0D_05's func_80043210 (its first call's
    `lui`/`lw a0` not scheduled into the prologue, the delay slot a `nop`)
    matched with `if (!D_80046154 && ...) {}` at its top, where testing the
    call's own argument only moved that load into the fake's block;
  - a function pulls its static callees in the reverse order of their
    last calls, so a static last called after another static N comes out
    just before N: ovl_0D_05's stub before func_8004352C is a static that
    func_80043790 calls at its very end, after its last call of 8004352C;
  - an empty static with no parameters still adds a 4-byte slot to its
    caller's frame (8004352C's frame was 8 bytes too big while its stub
    was an empty static it called); called inside an `if`, the same
    static fixed ovl_0D_04's func_80044D98 frame;
  - a small function the handler calls can stay a call only by being
    bigger: ovl_0D_04's func_80044840 calls its empty static twice (a
    fake), where once it was inlined into the handler;
  - a global empty function a static calls is inlined and still emitted;
    defined above the static's caller it comes out pulled, between the
    statics, defined below it comes out at its own turn (ovl_0D_04's
    func_80043F1C between 80043EA8 and 80043F24). The same holds for a
    non-empty global: ovl_0D_04's func_80043478 comes out after
    800433F0 (pulled by 800435AC) only when defined above 800435AC.
    ovl_10_13's handler cases 800460E0-800468BC are globals defined
    above the handler: they stay calls and come out between the
    cut-scene statics and the handler, as in the original (as statics
    they were inlined; defined below, they came out ahead of the
    statics). tools/fcmp.py compares statics with the function before
    them, and those emitted first (no symbol before them) from the
    object's start, named by its `.mdebug`; `scratch/10_13/allf.py`
    counts every static on its own;
  - a big global that the original both inlines into a caller and emits
    whole is too big to inline as one global, and as a static it isn't
    emitted on its own: a global one-call wrapper around a static holding
    the code does both (ovl_0D_03's 80043770, inlined into its handler's
    case 3, 1025 to 791 words).
  Bank 0x0D's stage overlays (drafts of 0D_04 and 0D_05 in
  nonmatching/, not matching yet) add: ZeroJump 0xD08 (a position to its tile)
  fills 6 words, so its buffer is `s32 pos[6]` (that fixed two frames);
  0x1820 returns `s32` (only then does its caller keep its temporaries in
  `v1`); float products of constants propagated from locals are not
  folded (`x = 170.0f; e->unk14 = x; ... = x * 10.0f` gives a `mul.s`);
  an angle-to-direction `if` chain is a `static s32` helper.
  `tools/fcmp.py` and `tools/mkperm.py` compile `-mips1`; for a `-mips2`
  object (`MIPS2_C_FILES`), pass them `-mips2`. mkperm.py's `IMAGE_OFFSET`
  is the object's text start, not the function's: with the function's,
  every base score is meaningless.
  The decomp-permuter normally strips a file to the one function, which
  undoes all of this: keep the other definitions (mark them `inline` for
  the permuter and strip the keyword in its compile.sh) and score against
  the whole object.
- **IDO allocates expression temporaries per source line.** A function
  that builds display-list commands matched only with each command on
  one line, as gbi.h's macros expand (87730's func_8026D2C4); written one
  statement per line, the later commands' constants land in `t0`-`t5`
  instead of `t6`-`t9`. A macro of several commands (gSPSetLights2,
  gDPLoadTextureBlock) is one line too. Write gbi.h's `_SHIFTL` masks as
  the macro does: 9BFD0's colour matched only with its first component
  masked too (`(r & 0xFF) << 24`), 412F0's rectangles only with the
  `(u32)` casts.
- **`-g`** for main_code's entry (`main_code_entry.c`, func_80225800):
  every value goes through the stack and the return is branched to; `-O1`,
  `-O2` and `-O0` don't give it. bm64 builds its 40000.c `-g` too. Hudson's
  `gmalloc` is `-g` in bm64 as well (another agent's area). All of
  ovl_16_01 is `-g` (its entry too: the return's `jr ra` is followed by
  the two that end every `-g` function, which makes the entry's file 0x20
  bytes, `tools/layout.py`'s first_function_end()); a `return;` at the end
  of a void function is one more branch to the epilogue.
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
- **Some loops do walk a pointer.** Where the asm keeps both a counter and
  a pointer stepped by the element size (52270's searches over its eight
  threads), the C has both: `p = D; for (i = 0; i < 8; i++, p++)`.
  Indexing `D[i]` gives a pointer compared against the end, or offsets
  from one base in the unrolled copies.
- **Unused-looking arguments are passed through.** A wrapper whose callee
  takes more arguments than it sets usually took them itself
  (5E090's func_80243BA8, 9BFD0's func_80281900: the `a` registers are
  left as they came in).
- **Busy-waits on a flag** are `while (flag) { func_80297DC0(); }`, and an
  "impossible" argument is trapped with `while (1) {}` (A4860).
- **Truth values are `int`.** `return a <= b && -b <= a;` matched as an
  `int` function (4DE50); as `s32` (`long`) IDO builds it in `v1` and
  moves it. `int` and `long` differ elsewhere too: `arg3 + c * size` adds
  its operands in the other order when `arg3` is a `long` parameter
  (9A5F0's func_80280274 matched only with `int arg3`).
- **A constant part of a local is set early.** 9A5F0's func_802807A8
  reloads its `u8` argument into `a3` only with `offset = 8;` before the
  file is opened and `offset += arg1 * 32;` after; any one expression
  for the offset puts it in `a1`.
- **Float literals keep their type.** `x * 2` multiplies by a 2.0
  constant where `x * 2.0f` becomes `add.s`; an angle wraps as
  `a >= 360.0f ? a - 360.0f : a < 0.0f ? a + 360.0f : a` (or the same as
  if/else with a temporary, ovl_09's handlers).
- **Function-local statics and aggregate initializers are `.data`.**
  53D70's func_80239D6C's local pattern, 530C0's exported function table,
  4ED50's constants: the object owns them, in its function's place (after
  the globals defined before that function in the source).
- **Re-read instead of a copy.** 86680's angle matched with the wrap
  applied to the expression itself (`*angle = WRAP(270.0f - a + b)`), not
  to a temporary; ACA00's palette fade with every use of the colour as
  `*src`, not a local copy.
- **Defining a variable can change the code.** 412F0's two stores into
  its own .bss share a `lui` only when the variables are defined in the
  file (as1 knows they're near), so it defines its .bss.
- **Callbacks** keep their argument: `D_802B01F8[arg1 - 1](arg0)`
  (99F40), where the array starts one entry after the symbol the asm
  indexes from.
- **Two float zeros.** Where the original keeps the zero it compares
  against and the zero it stores in two saved registers (an extra saved
  float pair in the prologue), the comparisons are written with an int
  `0` and the stores with `0.0f`: ovl_0C_09's 80045934, 282 words to 19.
  The same goes for other constants: `dz * 50` keeps the multiplier apart
  from a stored `50.0f` (ovl_0C_06's 800430A8). A `0.0f` argument can
  pin 0.0f in `$f20` for the whole function (a bigger frame, `$f20`
  saved). The original passed ints: `func(13, 0, 8, &pos, 0)` (ovl_10_07's
  800458C4, 58 words to 0). In an eased move (`t += 90.0f / n`) the loop
  test is `t < 90.0f` where the original keeps 90.0 in one saved register
  for the division and the test, and `t < 90` where the test reloads it
  each time (ovl_0C_01's 80043248 and 80044080).
- **Check the delay slot of every `jal`.** m2c gave
  `func_ovl0C_01_80049BA0(void)`, but its callers load `a0 = 0x15` in the
  delay slot; with `(s32)` and the argument, several functions matched.
- **A function far too big with nothing inlined: check the `.bss` types.**
  A generated `.bss` that split two `f32[10]` arrays into scalars and
  `s32[6]` pieces turned ovl_10_06's 80047D14 into a pointer walk (0x2CC
  bytes against 0xFC); with the arrays, `for (i = 0; i < 10; i++)`
  matched.
- **A callee's prototype can decide inlining.** ovl_10_06's 8004322C
  stayed a call only once `func_ovl10_06_8004A380` was declared taking
  its `s32` argument.
- **Arguments moved from float registers held across a branch** (`mfc1`
  after a `beqz`) were read into float locals before the `if`, not in its
  condition (ovl_10_06's 80044D00, 119 words to 0, with an
  `(f32, f32, f32)` prototype).
- **Rewrite a cut-scene as Hudson wrote loops** rather than tuning m2c's
  C: `for` loops, `obj->unk40->x` re-read at every use, no temporaries,
  and one variable where m2c split two values whose lives don't overlap
  (that also gives the original's saved register). ovl_12_05's 800434C8
  went from 866 words to 2 this way; the last big step was using `i`
  rather than `j` in one loop. Three `f32` locals m2c passes as
  `(Vec3f *)&spXX` are one `Vec3f`. `li v0,5000; bnez; nop; b; li
  v0,8000` is `s->unk10 == 0 ? 8000 : 5000`.
- **A callee's return type picks `v0` or `v1`.** After a call to a
  function that returns a value, used or not, the next temporary goes in
  `v1`. Declaring the ZeroJump stub 8004A148 `s32 (s32)` fixed ovl_10_13's
  80047418 and four loads in 80047A0C.
- **`slti` or `bne` in a counted loop follows the counter's life.** IDO
  turns `i < N` into `!= N` (with N in a saved register) only when the
  counter lives in that loop alone. m2c gives each loop its own counter;
  one `i` shared by the loops, as the original had, restores `slti`
  (ovl_10_13's 80048BBC, and 80043070 where the counter is also reused
  for a count).
- **The order of a call and an increment** is in the delay slots: `a0 =
  i + 44` in the `jal`'s and `i++` in the next branch's means the call
  comes first, whatever m2c wrote. An angle macro's step as an int
  (`ANGLE_SUB(p->unk1C, 5)`) moves the constant's reload to the loop's
  tail (80047A0C).
- **Get the statics' order right first.** tools/fcmp.py counts each run
  of statics with the named function before it, so statics out of order
  cost hundreds of words that aren't in their code. m2c's gotos can
  reorder them: rewriting ovl_0B_03's 8004386C cases 1 and 5 as
  `while (TRUE)` loops (an if/else chain over the buttons, the redraw at
  the end) put the statics it calls in the original's order (about 400
  words).
- **More from ovl_0B_03:** unused m2c locals still take frame slots at
  -O3 (30 of them made 8004386C's frame 120 bytes too big); a float loop
  whose entry test the original keeps is a `for` with float constants
  (m2c's `if (0.0f <= 20.0f) do {} while` is folded away); a loop's end
  pointer as `base + size` with `sltu` came from a static inlined at two
  call sites; `temp + 8` on a `Gfx *` steps 64 bytes, so write display
  lists one macro per command.
- **Name static stubs for where they're emitted.** A group of empty
  static stubs comes out in IDO's order (often reversed), and fcmp finds
  statics by their `.mdebug` names, so a stub named for another stub's
  address makes "not in the original" count the whole object against it.
  ovl_0A_01's stubs, renamed to the addresses they land at, took it from
  4920 words to 776 (`scratch/0A_01/procs.py` lists the draft's procedures
  next to the original's).
- **Check m2c's calls, globals and constants before tuning.** Diff every
  `jal` target, global and `lui` immediate against the asm first: two of
  ovl_12_05's functions had another function's body or a twin's
  constants, about 200 words between them.
- **Every declared scalar takes a frame slot in a big -O3 function,** even
  one kept in a register, laid out from the top of the frame down in
  declaration order. A frame too big means too many locals: merge ones
  whose lives don't overlap (ovl_12_05's 80044534), or move them into
  the pad slots below an array (800434C8). An extra parameter on a static
  inlined into it costs the caller 8 bytes the same way (ovl_0A_01).
- **Nops before an epilogue after an infinite loop are alignment.** IDO
  puts that unreachable epilogue on a 32-byte boundary in the object, so
  more nops than the original means the code before it has a different
  length; it fixes itself once that matches.
- **A count passed to a static** gives the original's `slt`/`bnez` where
  a constant limit gives `bne` (ovl_0A_01's 8004607C, called as
  `(1, LIGHTS)`).
- **Source order picks the order of constant loads.** Setting a float
  after a call instead of before it changed which `lui at` came first
  (ovl_0A_01's 80044A2C, 156 words to 11).
- **A twin's C carries the twin's constants.** `scratch/tools/simil_all.py`
  compares mnemonics, so a function that scores 1.00 may pass other
  immediates (ovl_10_10's 800442B8 passes `0x28, 0x2E, 2, 0x10` where
  ovl_10_06's needs `0x28, 0x2C, 1, 0xF`) or call another function
  (ovl_10_13's 800477E8 against ovl_12_05's 80047DA4). Diff a copied
  function after compiling.
- **Strings come out in definition order.** An object's `.rodata` strings
  follow the order their functions are defined, not emitted: ovl_10_06's
  came out right only with 800430A8 defined above 80048FE8, and
  ovl_10_13's with 80046DD8 above 80046E50.
- **A ternary with equal arms keeps a constant out of a saved register.**
  An infinite loop's `0x01000000` was hoisted into `s3` (a bigger frame);
  `p->unk28 ? 0x01000000 : 0x01000000` leaves it a `lui` in a delay slot
  (ovl_0C_01's 80047A60, 136 words to 36).
- **Re-read a global after each call** where m2c keeps it in a temporary
  and the original reloads it (ovl_0C_01's 80046224, 51 words to 0).
  `D = f(); D->x |= 0x80;` keeps `&D` in a register (`lui/addiu a1;
  sw v0, 0(a1)`), where a local copy gives `lui at; sw` (ovl_10_13's
  800468BC).
- **Declaration order picks the saved float registers.** Which value gets
  which `$f2x`, and which is spilled, follows the order the locals are
  declared and first assigned. A file of small functions compiles in
  about 0.1 s, so trying every order (with pads) is cheap:
  `scratch/0C_01b/perm.py` (ovl_0C_01's 80043C20 and the eased moves).
- **Check m2c's local types.** Counters it gives as `s32` may be `s16`
  (an `sll`/`sra` pair after each change), and a volume it gives as `s8`
  may be `s32`, narrowed only by the callee's prototype (ovl_0C_06's
  80046CF0, 8004696C and 800458D8).
- **m2c can get behaviour wrong, not just style.** It wrote
  `var_s0 += 0x30` on a struct pointer (steps 0x30 records; `p++` is
  right and matched ovl_0C_02's 80043338), and `+= 1; if (>= 6)` where
  the `slti` sits before the increment in its delay slot
  (`if (wait++ >= 6)`, 80046924). IDO compiles a leftover `M2C_ERROR(...)`
  as an implicit call, so grep for it after a clean compile. Its
  `cfc1`/`& 0x78` blocks are a float-to-`u32` conversion: `(u32)f`.
- **A constant computed at run time was a variable.** Where the original
  multiplies `22.0f * 100.0f` at run time or converts an int 14 with
  `cvt`, the source had `tx = 22.0f; tz = 14; n = 5;` just before use. A
  variable loop limit also keeps `slt` rather than `bne` and stops the
  limit being hoisted into a saved register (ovl_0C_02's 80046DD0, 343
  words to 180).
- **A call after a loop that sits before the loop body** belongs inside
  it, as `if (...) { call; break; }` (80046DD0, 180 to 29).
- **A `beq` chain over consecutive values** is an `if (x != 7 && ... &&
  x != 12)` chain, not a switch, which would become a jump table.
  Branch order also follows the test's polarity: `== 0 || ...` and
  `!= 0 && ...` lay the blocks out differently (80045898).
- **Locals placed between pads.** Some frames need padding on both sides
  of a local: `s32 pad; s32 moved; s32 pad2;` (800477B0, 800475BC).
- **Walking the parameter.** A list kept in its own stack slot apart
  from the loop pointer means the loop advances the parameter itself, and
  a copy taken at the top is what's kept for later (ovl_0C_06's
  80043544, 97 words to 0).
- **Loops:** `while (TRUE) { if (cond) break; ... }` rather than
  `while (!cond)`; re-reading `D[i].x` after a call rather than keeping
  a pointer removed a duplicated register (ovl_0C_09's 80043AA4, 84 words
  to 0), while other loops walk a pointer (`for (i = 0, p = D; i < 6;
  i++, p++)`, its 80043244). A body repeated in callers whose frames
  leave no room for a callee's parameters is a macro (its 80044610 and
  80045060).
- **Source lines steer the scheduler.** Where two instruction orders are
  equally good, IDO's choice depends on which statements share a line.
  Joining statements onto one line, or into one macro (which expands to a
  single line), fixed ovl_0E_13's 80043444 (`UNK_MACRO_ovl0E_13_80043444`)
  and two words of ovl_0E_12's 80043164. Try it on a store/load order
  that no reordering of statements fixes.
- **Saved registers nothing uses come from dead code IDO removes late.**
  A callee-saved register the prologue saves and the body never touches
  was allocated before a branch was found dead. ovl_0E_02's 800447F8
  (and ovl_0E_03's 80044B78, ovl_0E_05's 800443B4) saves `$f26`-`$f29`
  for nothing: `flag = 0;` before its loop and
  `if (flag) { ...two float constants... }` inside it reproduces that.
  Constant propagation removes the branch only after the loop's
  invariants (the constants) were given registers. Dead code after an
  infinite loop, unused locals and `if (0)` don't do it, because they
  go too early. Such a flag takes a stack slot like any local. Where
  several loops share the saved floats, each loop needs its own dead
  `if (flag)` (ovl_0C_02's 80046B68: 152 words to 4 with all three
  loops, 10 with one).
  In -O3 objects the other source is a static callee: the caller saves
  what the callee uses unsaved (86680's func_8026C0A8). So a function
  that uses callee-saved registers without saving them is a static
  (`scratch/12_05/p2/sav.py` lists them); making ovl_12_05's 80043018
  static fixed its handler's prologue.
- **An empty `if` can keep a parameter in a register.** Bank 0x10's
  80043924 (ovl_10_09; 10_07, 10_08 and 10_12 have it) loads arg0 into
  `v1` at the end of both arms of an `if` and keeps it for the loops
  after them; without help IDO reloads it in each loop's preheader and
  lays the blocks out differently. `if (arg0) {}` where the arms meet
  reproduces it (95 words to 0 in each, found by the permuter): a use of
  the parameter that IDO removes only after register allocation.
  `arg0 * 0` in a loop's indices does much the same, less cleanly.
- **Unsolved: a block boundary with no branch.** Two misses come from
  how as1 schedules a block, not from ugen, so `cc -c -S` (ugen's
  `u.out.s`, before as1) shows them. In each, adding a single label to
  `u.out.s` reproduces the original:
  - The camera set-up (ovl_0C_09's 80043D08, and ovl_0E_04, 12_01 and
    12_03) needs a label after its hoisted invariants.
  - The object set-up's epilogue (ovl_0C_07's 80044178, ovl_0C_08,
    ovl_0C_04 and ovl_0E_13) needs a label before it, or as1 reverses
    the s0-s2 restores after a `lw`, `lw`, `sw` chain.
  Matched functions that restore s0 first reach their epilogue as a
  branch target. No C has been found that leaves the label without a
  branch. A flag that is always zero doesn't do it: ugen folds the test
  and its label together, and an empty `if (x) {}` on a parameter, local
  or global, at any statement, doesn't either (2200 variants,
  `scratch/emptyif/`). The scripts are in `scratch/0C_09/d08_block/` and
  `scratch/epi/`.

## Versions

eu and jp build from the same C. Each version's config comes from its own
ROM; the C files, the flags and the names are us's. So far every C
object matches all three unchanged (eu's and jp's differences lie
elsewhere: docs/LAYOUT.md, "EU" and "JP"), except `85A10`, whose
`func_8026B9CC` (jp's differs) is still GLOBAL_ASM: a changed function
keeps us's name, so one GLOBAL_ASM line serves every version.

- **Objects.** Outside us a text object is named for the us image offset
  of the same code (`tools/layout.py` through `vermap.<v>.txt`): `5E090`
  is jp's `0x5DDE0`, and `src/5E090.c` is that object in all three. An
  object only jp has would be `<jp offset>_jp`. Where jp's padding
  doesn't show a boundary us's does, us's is used; where jp's object
  starts elsewhere, text_objects.txt says so (`main_code 9A5F0 jp=9A340`,
  docs/LAYOUT.md, "Stage 2").
- **Names.** eu's and jp's asm carries us's names: `make extract` renames
  splat's address names through `vermap.<v>.txt` (`tools/vermap.py`,
  docs/LAYOUT.md, "The US to EU map", "The US to JP map"), so a C file's
  names mean the same things in every version. What us doesn't have is
  `func_<address>_jp` (`_eu`), at jp's own address. `tools/split.py`
  reads the C file's names as the version's when splat runs, so the
  GLOBAL_ASM `.s` files come out in eu and jp too, under us's names.
- **Code.** Where a version's code really differs, the C gets `#if
  VERSION_JP` (or `VERSION_EU`), with us's code as the default:
  `#if VERSION_JP ... #else <us> #endif`. Keep the other versions'
  bodies next to us's, not in other files.

What a decompiler has to do for jp (and eu):

1. Before starting an object, look at it in the map: `tools/vermap.py
   --functions <module> jp` lists every function as `identical`,
   `changed`, `us-only` or `jp-only` (with the us and jp addresses). An
   object whose functions are all identical needs nothing; most are.
   jp differs in main_code's `52270`, `54E40`, `5E3F0`, `6BBE0`, `85A10`,
   `96540`, `9A5F0`, `AD3D0`, boot_code's `2350`, and the overlays
   `ovl_0A_06`, `ovl_0B_01`-`ovl_0B_07`, `ovl_14_02`, `ovl_15_02`
   (docs/LAYOUT.md, "JP"). eu differs in `54E40` and `96540` only.
2. After the C matches us: `tools/layout.py <v>`, `make clean`, `make
   VERSION=<v> extract` and `make VERSION=<v>` for eu and jp (and
   `tools/data_split.py <v>` for an object in the data cut). A changed
   function shows as a sha1 mismatch: `tools/fdiff.py` works in jp's
   tree as in us's.
3. A changed function gets its jp body under `#if VERSION_JP`. A
   function only us has goes under `#if !VERSION_JP`; one only jp has is
   written under its `_jp` name under `#if VERSION_JP`, where jp's link
   order puts it.
4. A GLOBAL_ASM line under `#if` works. asm-processor runs before the
   preprocessor and reads every GLOBAL_ASM line, `#if`'d or not, so a
   `.s` the other version's extract never wrote would stop the build.
   The Makefile's C rule therefore runs a file with GLOBAL_ASM through
   `tools/version_ifs.py <VERSION_X> in.c -o build/.../x.c.vi.c` first
   (ported from Blast Corps). It decides every `#if`/`#ifdef`/`#ifndef`/
   `#elif`/`#else` whose condition names only `VERSION_*` macros, blanks
   the directives and the branches not taken (line numbers stay), and
   leaves every other line, other conditionals included, for the
   compiler; asm-processor compiles the `.vi.c`. A condition mixing
   `VERSION_*` with other macros is passed through (and then its
   GLOBAL_ASM lines are not hidden). Files without GLOBAL_ASM skip the
   step; `PERMUTER=1` compiles the file as is. The `.d` file still comes
   from the original source. A changed function keeps us's name in jp (the
   map), so it needs no `#if` while it is GLOBAL_ASM: each version's
   extract fills the same `.s` with its own code (`src/85A10.c`'s
   `func_8026B9CC`). The `#if`s are for a `.s` only one version has (a
   `_jp` function), and for a function written as C in one version while
   the other stays GLOBAL_ASM.
5. Data: `data_split.txt` takes `@jp` placement lines like `@us`/`@eu`
   (the module's data start, an object's `.data`/`.rodata`/`.bss` start);
   `tools/vermap.py`'s map gives jp's addresses (boot_code's data is 0x20
   lower in jp, main_code's objects' `.data` starts at `0x8029EC50`). An
   object whose data differs in jp (strings: jp's text is in another
   encoding, docs/ASSETS.md) needs its definitions `#if`'d and jp's own
   sizes: `<module> @jp <object> sizes=<.data>,<.rodata>,<.bss>`
   (`tools/data_split.py jp --add <module> <object>` writes it), as
   AFBF0's (its strings make jp's `.data` 0xE60 against us's 0xE70) and
   9A5F0's (jp has no proportional font: `.data` 0x40, no `.bss`).

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

Cut so far (the same in us, eu and jp):

| module | objects | .data/.rodata boundary |
|---|---|---|
| ovl_09_01 | all: `ovl_09_01_entry`, `120010` (.data 0x30, .rodata 0x50: the handler's jump table, .bss 0x50) | 0x80044990 (the compiler's) |
| main_code | `main_code_entry`, `40040` (.data 0x30: two tables), `40300` (.data 0x10: the bump pointer) after the RSP code at 0x8029D250-0x8029F570 | not shown yet: none of the three has .rodata |

The sizes are the same in every version as long as the C is. Where a
version's C builds to other sizes (`#if VERSION_JP` data: jp's text), a
`<module> @<version> <object> sizes=<.data>,<.rodata>,<.bss>` line gives
that version's, in place of the size line's: `tools/layout.py` cuts or
places the object with them, and `tools/data_split.py <version>` checks
the version's build against them. `tools/data_split.py <version> --add
<module> <object>` on an object listed already writes the line if that
version's build differs. A sizes line alone doesn't place an object; its
placement lines do.

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
   from the ROM. Give the module's `@us`/`@eu`/`@jp` `rodata=` start if the
   object has .rodata and isn't the module's last.
3. `tools/layout.py <v>` for us, eu and jp, `make clean`, extract and
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
  between variables are `u8 D_<address>[n]` arrays (120010.c has two),
  except where IDO aligns: it puts a 16-byte `.bss` array 8-aligned, so
  4E030's gap between an `s32` and its pointer array is its own doing.
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
before it needs a size.

**Objects placed on their own.** A library object after the game's code
can't join the cut, so data_split.txt can place its sections where the
ROM has them instead: a size line as above, plus per version
`<module> @<v> <object> data=<vram> rodata=<vram> bss=<vram>` for the
sections it has. `tools/data_split.py <v> --place <module> <object>
[--ref <object file>]` prints both lines, finding the addresses from the
object's `%hi`/`%lo` relocations against the ROM and checking the bytes.
`tools/layout.py` carves those subsegments out of the asm blocks (the asm
before a placed `.data` becomes `data`, since the link puts every .data
before every .rodata). libultra's objects use this where their code needs
the data in the same file (docs/LIBULTRA.md, "Data"). So do the game's
objects after main_code's cut that have jump tables, strings or
constants (995C0, 54BE0: `.rodata` only), or whose `.data`/`.bss` is all
their own (53D70, 530C0, 412F0, AFBF0: all three sections, jp's .data
its own size); everything else they use stays `extern`.
Build the object once (the link fails, the `.o` is there), run `--place`
for each version with `--ref build/us/src/<object>.c.o`, add the lines,
regenerate the configs and extract again. `--place` finds an object named
by its image offset (`995C0`) as well as a named one.
