# The PC port

Phase 6 (docs/ROADMAP.md) has not started. The architecture is Blast
Corps' (`../BlastCorps/docs/PORT.md`: "The build", "Memory model", "Where
pointers are 8 bytes", "The overlay", "The asm data as C", "The platform
layer"). This file says what the decompilation gives a port now and what
the host side has to supply.

## Readiness

As of 2026-11-13. All the game's code is C: boot_code, main_code and every
overlay in `src/`, ovl_0B_04's in `nonmatching/` (a complete draft a port
can use as it is). `tools/host_check.py` checks what follows; the counts
are us's, and eu and jp's are the same unless a line says otherwise.

### The C on a host compiler

`host_check.py compile` compiles every game C file (src/ but libultra, and
nonmatching/: 256 files) with `-DTARGET_PC -fsyntax-only` and the errors
for C a host can't take (`-Werror=implicit-function-declaration`,
`-Werror=int-conversion`, `-Werror=incompatible-pointer-types`), with clang
and gcc, `-m32` and `-m64`. **0 errors**, in us, eu and jp.

- `-std=gnu89` to `-std=gnu17` all work. C23 (gcc 15's default) doesn't:
  13 files have K&R declarations, `f()`, whose calls pass arguments.
- gmalloc is compiled as the Makefile does (`-DSTDC_HEADERS
  -DPAGESIZE=0x1000 -Dsbrk=func_80225B00 ...`) plus `-DHAVE_UNISTD_H`
  (sbrk's prototype, `src/libmalloc/include/unistd.h`) and `-include
  src/libmalloc/pc_names.h`, which the game's files that call the
  allocator also need (`malloc` → `bm64_malloc`...).
- The only header the check replaces is gbi.h, with a display list's
  words as wide as a pointer (the port's own SDK headers, as in Blast
  Corps' `port/include/sdk`).
- No `GLOBAL_ASM` or other asm-processor pragma is left. IDO's matching
  tricks stay: `#line` in 45 files (a host takes them, but its diagnostics
  and debug information then name other lines), K&R definitions, `if (1)
  {}` and the like.

What it took (commit "src: the game's C compiles on a host"; IDO's
output is unchanged in every version):

| class | sites | change |
|---|---|---|
| int/pointer and incompatible pointer conversions (calls, assignments, returns; 16 `const char[]` strings) | 229 in 25 files | explicit casts |
| static function declared non-static first | 20 (9CAB0) | `static` declarations |
| implicit declarations | func_80239094 (4ED50); gmalloc's sbrk | a `void` declaration under `TARGET_PC` (IDO's code needs the implicit `int`); the unistd.h stub |
| an argument IDO passes by leaving it in `$a0` | 5 | passed under `TARGET_PC`: func_8029547C's strlen of its text (AFBF0), func_8027EDC8's func_80239F70 (995C0), func_80250DC8's func_8024A0DC (5E3F0: ZeroJump 0x100F's flag, from its callers), ovl_10_01's and ovl_10_05's ZeroJump 0x1A00 (func_80287DC0, 0x1FD) |
| pointers in 32-bit initializers (64-bit only) | 47A80's Gfx, AFBF0's 146 text entries, 80580's audio configs | `uintptr_t` words; `TextArg` (a pointer in the port); the configs as structures (ALSynConfig, ALSeqpConfig, amConfig) under `TARGET_PC` |
| gmalloc's `size_t`/`ptrdiff_t` stubs, 32 bits | 1 | the host's under `TARGET_PC` |

### 32-bit hosts and 64-bit hosts

`host_check.py layout` lays out every struct whose fields carry their N64
offsets in comments (669) as clang does for the host:

- **-m32 -malign-double: all 669 match** (without `-malign-double` one
  doesn't: 85A10's audio manager, whose thread is an array of `u64`). The
  game's C needs nothing more on a host whose pointers are 4 bytes:
  i386, armhf, wasm32 (phase 7).
- **-m64: 305 differ.** A 64-bit build needs Blast Corps' pointer pass
  ("Where pointers are 8 bytes") first. What it has to go through:
  617 casts between pointers and integers in 64 files (5E3F0 143,
  6BBE0 95, 8A7A0 60, 54E40 45; `-Wpointer-to-int-cast` and the like),
  2273 `M2C_FIELD` accesses at N64 offsets in 15 files (6BBE0 1437,
  ovl_13_02 254, 54E40 121, 48600 101, 80580 72, 8A7A0 58), and the
  declarations below that disagree on pointer or integer.

So the first port build should be 32-bit (`-m32 -malign-double`, as Blast
Corps' i386 build), then wasm32; native 64-bit after the pointer pass.

### Declarations across files

`host_check.py decls` reads clang's AST of every file. No call passes
fewer arguments than its callee's definition takes (the 5 above were the
direct ones). Declarations of another shape than the definition: 131
parameters integer for pointer or the reverse, 42 returns likewise, 144
returns `void` on one side (76 declared with a value but defined `void`:
a caller that uses it reads whatever `$v0` held), 15 parameter counts
(unused or variadic). None mixes float and integer, and no call through a
declaration without a prototype passes a float.

### Handwritten code

What is still asm, and what replaces it in the port:

| asm | what it is | in the port |
|---|---|---|
| `entry` (0x80000400) | clears boot_code's bss, sets `$sp`, jumps to func_800019A0 | the host's `main`, which calls func_800019A0 |
| `2630` func_80001A30 | `D_8001BFC0[id] = table` (IDO's code for it is 5 instructions, not these 6) | C under `TARGET_PC` in src/1050.c |
| `zerojump` func_80042000 | the ZeroJump dispatcher at virtual 0 | "ZeroJump", below |
| `*_zerojmp` | each module's 711 stubs (`jr $zero; li $t0, id`) | "ZeroJump", below |
| `B2410` func_80297C10, func_80297C7C | setjmp and longjmp, for the cooperative tasks (530C0) | not the host's alone: func_80238A10 makes a task by writing its entry and a stack top (0x800 bytes in the task, or the caller's) into the buffer as `ra` and `sp`, and func_80239208 reads `sp` back (the stack check). The port needs a coroutine per task with a host-sized stack (ucontext, fibers, threads run one at a time: Blast Corps' "Threads without ucontext"), and 530C0's switches under `TARGET_PC` |
| `B2500` func_80297D00, func_80297D20 | WatchLo set and clear (4E030, 40040) | no-ops |
| `3D90` func_80003190, `6080` func_80005480, `D4D0` func_8000C8D0 | osUnmapTLBAll, osPiGetDeviceType, alSndpGetSound | the host libultra |
| `4150` func_80003550 | a lone `nop`, no `jr` (nothing refers to it) | nothing |
| libultra's `.s` | exceptions, cache, TLB, `bcopy`/`bzero`, sqrtf | the host libultra |

### ZeroJump

The C calls 5781 ZeroJump stubs (jp 5771), each by its module's name
(`func_80297D38`, `func_ovl0A_02_80047220`). `host_check.py zerojump`
resolves each id: the high byte is a table registered with
func_80001A30 (boot_code: libultra's and its own) or main_code's stub 0
(func_80297D30), 47 tables, each id by one table only, and
every table is C or asm data. So a port can bind every stub to its
function when it builds (or keep `D_8001BFC0` and dispatch through it).
Only 0x1F03 (ovl_13_01's func_ovl13_01_8004BA40) has no table: the N64
would stop in the ZeroJump error there.

The stubs' declarations against the functions they reach: 235 expect a
value from a `void` function, 153 a return of another class, 142 pass an
integer for a pointer or the reverse, 15 are declared without a prototype,
19 pass fewer arguments (the ovl_10 overlays' 0x1A00 and 0x1E0A calls in
functions nothing calls; the two live ones are fixed), 95 reach libultra. A generator
binding the stubs needs one prototype per stub: 3 of main_code's are
declared in two ways (func_80297D50, func_80297D90, func_80297D98).

### The data still asm

All the overlays' data is C but ovl_0B_04's, whose C is still in
nonmatching/. What is left (`asm/data`, us):

| module | section | labels the game's C uses | bytes | pointer words | the rest |
|---|---|---|---|---|---|
| boot_code | .data | 1 (`D_8001A3B0`, the VI modes) | 3360 | 1 | 10 labels, 304 bytes, libultra's (thread queues, VI modes) |
| boot_code | .bss | 0 | | | 15 labels, 5492 bytes, libultra's |
| main_code | .data/.rodata | 117 | 16055 | 257 | 10 labels (322 bytes) nothing names; 16 bytes libm's |
| main_code | .bss | 272 | 31846 | | 41 labels (746 bytes) nothing names |
| ovl_0B_04 | .rodata | 49 | 5215 | 137 | 44 labels (1087 bytes, 65 words to code labels): IDO's jump tables and floats, which the C has of its own |
| ovl_0B_04 | .bss | 19 | 448 | | 15 labels (96 bytes) |
| zerojump | .rodata | | 136 | | its error strings |

A generator like Blast Corps' `port/tools/asm2c.py` (the extracted asm as
typed C at build time) covers it if it types each label from the C's
declaration, which most have: 199 scalars, 114 scalar arrays, 60 structs,
40 pointers or pointer arrays. It needs more for:

- **Words declared as bytes.** 51 labels (16 KB) are `u8[]` in the C but
  words in the asm: main_code's RSP microcode (`D_8029D250`, `D_8029D320`,
  `D_8029E750`, 9 KB: nothing reads it on a host), the ZeroJump module
  tables (15, e.g. `D_8029FD40`: functions), 3 display lists in main_code's
  .data (`D_8029F6D8`, `D_8029F718`, `D_8029F7A0`, 240 bytes; a `Gfx` with
  pointer-wide words in the port, and 412F0 writes `D_8029F7A0`'s address
  into a list as `u32`), and tables of words and floats (`D_802A0658`).
  These need a type of their own (Blast Corps' inventory).
- **Two declarations.** 5 labels are declared differently in two files
  (`D_802A5300`, `D_802A5418`, `D_802AC760`, `D_802ACF08`, `D_802AFE84`).
- **Labels inside a variable.** `D_802ABA9C` and `D_802AC33C` are the task
  list heads' `unk89C` (530C0), ovl_0B_04's `D_ovl0B_04_8004A1A0` and
  `_8004A1E4` the like: aliases at an offset.
- **Pointer words in integers.** `D_802A0654` and `D_802A0B40` are `int` in
  the C and hold addresses.

### Addresses outside every section

133 names the C uses are fixed RAM addresses that no section has
(`undefined_syms_auto.txt`): the work area `D_80063000`-`D_800BEA60`
(120 names: most of the game's state), `D_80100000`, the archive's page
cache and files `D_8014B000`-`D_8014C8D0`, `D_8019A8D0`-`D_8019C2E0` (the
archive index at `0x8019C0D0`; the audio heap, 86680's func_8026A754
call), `D_801E56C0`, `D_802B36D0` and the 1 MiB sbrk arena `D_80300000`.
The port makes them regions (Blast Corps' `port_regions.h`), sized from
the address map and typed from the C. Besides: `D_1000000` and `D_200000`
are segment addresses (Blast Corps' proxies), and `zerojump_ROM_START`/`END`
the linker's.

### Overlays

`host_check.py link` compiles all 256 files to 64-bit objects and links
them as one: **no global is defined twice** among 8919 (8909 in jp), all 95
overlays included: their names carry the bank and entry. Loading an
overlay in the port is restoring its variables, which are all C (but
ovl_0B_04's), so a Blast Corps-style table of them can come from the
objects.

### What the host supplies

From the link (us): libultra's 224 names (jp 223), 94 `os*`, 113 `al*`,
6 `gu*`, `sinf`, `fcos`, `sqrtf`, `sprintf`, `memcpy` and the `long long`
helpers (libaudio's C can be ultralib's, as Blast Corps' `port/libaudio`);
the asm and ZeroJump above; the asm data (378 labels); the regions (135).
The host's compiler adds `memset` (a struct cleared), and the allocator's
names are gmalloc's through pc_names.h, not the host libc's.

The host layer has to meet, from the C:

- **Busy-waits** on what another thread changes: 80580's two (sound player
  flags `D_802AD238` and `D_802AD660`, in func_8026A5BC) and 85A10's
  func_8026B7A8, which waits for the audio thread to count `D_802AF95C` up
  to a number of frames. With the threads run one at a time each
  needs the other thread's turn (Blast Corps' `port_spin_wait()`).
- **The cooperative tasks** (above): every `func_80239094` is a task
  switch.
- **The RNG seed** from `osGetTime` (docs/NETPLAY.md, "Requirements").
