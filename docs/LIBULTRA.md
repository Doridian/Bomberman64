# libultra

Bomberman 64 links Nintendo's libultra and libaudio into boot_code
(`0x80001A50` to the end of its text, `0x80019F80`), and some gu and libm
into main_code (`0x8029B650-0x8029D0E0` and the data they use). This page
says which revision it is, how the names are found, and what doesn't
match. The tools are Blast Corps' (`../BlastCorps`, the same scripts
adapted to one code image).

## Workflow

```
tools/build_ultralib.sh                    # build/ultralib: libultra_rom 2.0D-2.0L
tools/libmatch.py us --scan build/ultralib/build/{D,E,F,G,H,I,J,K,L}/libultra_rom
make libultra-ref                          # build/libultra_bm64: src/libultra on its own
tools/libmatch.py us build/ultralib/build/I/libultra_rom build/libultra_bm64    # names with evidence
tools/gen_symbols.py us build/ultralib/build/I/libultra_rom build/libultra_bm64 # writes the files below
tools/layout.py us                         # the config, with the new boundaries
make clean && make VERSION=us extract && make VERSION=us
```

and the same for eu and jp. `build_ultralib.sh` clones decompals/ultralib at a
fixed commit (the one Blast Corps uses) and builds `libultra_rom` for every
revision with IDO 5.3 and ultralib's own flags. Its voice library fails to
build on some hosts; the game doesn't link it, so the script carries on.
`libmatch.py` makes its code image from `baserom.<v>.z64`, so it works
whichever version is extracted.

`make libultra-ref` compiles every file in `src/libultra` with the
library's flags into `build/libultra_bm64/src/<dir>/<file>.o`, without
an extract: those objects are this game's libultra revision, matched like
ultralib's builds (they compile to the ROM's bytes, so they match
exactly). Passing both directories to gen_symbols.py names what only this
game's revision has, and gives its objects' bounds. (`make clean` removes
`build/`, ultralib's builds with it; keep a copy elsewhere, or rebuild.)

`gen_symbols.py` writes, for boot_code and main_code:

- `symbol_addrs.<module>.<v>.txt`: one name per line, below a marker line
  (lines above it are kept for names given by hand). The tag says how it
  was found: `lib=exact` (the body matches a reference object),
  `lib=fuzzy` (it differs by a few instructions), `lib=ref` (a matched
  function calls or references it by that name). Every name carries
  `segment:<module>`, since every code segment has its own RAM id. The
  boot parameters in low RDRAM (`osTvType`, `osRomBase`, `osResetType`,
  `osAppNMIBuffer`) are in no segment, so they're `absolute:True`, and
  `tools/ld_fix.py` defines them for the link. splat reads `name:value`
  words as attributes, which is why the tags use `=`.
- `lib_objects.<v>.txt`: where matched library objects start and end.
  `tools/layout.py` splits the text there too, as well as where IDO's
  padding shows a boundary. This adds 63 objects in each version (334 to
  397 in us): libultra objects whose last function ends on a 16-byte
  boundary. A `start` line names the object (`src/io/controller.o`);
  where one object ends and the next starts, the start is kept. An
  object whose source is in `src/libultra` (`io/controller.c`, or `.s`)
  becomes a `c` (or `hasm`) subsegment of that name,
  `libultra/io/controller`, built from it.

`tools/layout.py` lists every `symbol_addrs.*.<v>.txt` in the config. Run
`make clean` before extracting again after the names change, because
`postsplit.py` keeps what an earlier run wrote to `module_syms_auto.txt`.

Overlays aren't named. Two of them (`ovl_0A_02`, `ovl_0A_05`) carry their
own `osSpTaskYield` and `__osSpSetStatus`, and `ovl_0A_04` has two bodies
that match `osSpTaskYield`. All overlays link at 0x80043000 into one
image, so a plain name would clash, and overlay names carry the bank and
entry (docs/ROADMAP.md, phase 2).

## The revision: 2.0I

At the commit used, ultralib's sources only tell 2.0J, 2.0K and 2.0L
apart from everything before (`BUILD_VERSION < VERSION_J`). Its D to I
builds have the same code. So the most this can say is "2.0I, or an
earlier 2.0 that builds the same", and 2.0I is the build that has been
checked against real archives. `libmatch.py --scan` counts the function
bodies (6 words or more) that match exactly somewhere:

| build | D-I | J | K | L |
| --- | --- | --- | --- | --- |
| us | 319 | 173 | 169 | 169 |
| eu | 319 | 173 | 169 | 169 |
| jp | 319 | 173 | 169 | 169 |

Every function whose body differs between I and J matches I and not J:
`osInitialize`, `__osViInit`, `osCreateViManager`, `osViSetMode`,
`__osDisableInt`, the libc functions (`sprintf`, `_Printf`, `_Litob`,
`_Ldtob`, built `-O3` before 2.0J and `-O2` after), all of libaudio
(`-O3` before J), the controller pak (`osPfs*`), and gu (`guLookAt`,
`guMtxXFMF`). Blast Corps, earlier in 1997, has libc built
`-O1`, which no ultralib revision does. Bomberman 64's is built as in 2.0I.

The three versions link the same libultra. EU's and JP's text is byte for
byte US's. Only a 0x60-byte gap of zeros between two link units sits
elsewhere (after `osUnmapTLBAll` in EU, after `osSetThreadPri` in US,
between `__ll_rshift` and `bzero` in JP), so `osInitialize` and
`osSetThreadPri` are 0x60 later in EU. (JP's boot_code is 0x10 shorter
before them: one game function is.) gen_symbols.py gives jp the same 424
names, and the C in `src/libultra` matches jp unchanged. The PAL/MPAL handling is
libultra's own: `__osViInit` picks `osViModePalLan1`, `osViModeMpalLan1`
or `osViModeNtscLan1` from `osTvType`.

The link order is not 2.0I's archive order. The 23 `alSeqp*` objects come
in the order `delete, setseq, getseq, play, stop, getstate, setbank, ...`,
while ultralib's `base/I/libultra_rom.txt` lists them alphabetically. The game may have been linked from a differently ordered
archive (another SDK release), or with the objects named on the command
line. The Bomberhackers/bm64 split has the same order.

## What is named

| | us | eu | jp |
| --- | --- | --- | --- |
| boot_code functions | 370 | 370 | 370 |
| boot_code data | 54 | 54 | 54 |
| main_code functions | 12 | 12 | 12 |
| main_code data | 1 (`__libm_qnan_f`) | 1 | 1 |

In boot_code, 366 names are `lib=exact`, 56 `lib=ref` and 2 `lib=fuzzy`
(the counts include data). A function placed by a reference before its
own body matched still gets its body match (and names what it
references), so most of the library is `exact`.
`alSeqp*` and `alCSP*` functions have identical bodies (one object each,
for the two sequence players), so the body alone can't place them. Each
family is linked as a run next to its own player (`seqplayer.o`,
`csplayer.o`) and to the functions of its family that did match uniquely
(`alSeqpLoop`, `alCSPGetTempo`). `libmatch.py` places each such name in
the run whose nearest placed neighbour is of its own family
(`resolve_twins`).

Static functions have no symbol in the objects, so they keep their
address names, but a whole-object match covers their code (an object
that starts with a static, such as `xprintf.o`, is matched whole too).
The fuzzy names are `osCreateScheduler` and `osScAddClient` (0.95 and
0.93), in the game's copy of the SDK's sample scheduler (`sched.c`,
compiled with the game and with asserts, at `0x800014B0`).

## What 2.0I doesn't reproduce

No ultralib build matches these, because ultralib's D to H builds are
2.0I's code: its sources only tell 2.0J and later apart, and its README
supports 2.0I to 2.0L. They are an older revision's code (2.0I flags,
older sources), one Hudson patch, and a few objects that are 2.0I's but
couldn't be placed. All of them are now in `src/libultra` (see "Sources"),
matching in us and eu.

**An older SI, PI and controller pak layer.** The evidence that it
predates 2.0I:

- `osPfsReSizeFile` (`0x8000FA20`, `io/pfsresizefile.c`): the SDK's
  function reference says it "was removed from the N64 operating system
  OS2.0I or later" ([ultra64.ca](https://ultra64.ca/files/documentation/online-manuals/functions_reference_manual_2.0i/os/osPfsReSizeFile.html)).
  ultralib has no source for it; it is decompiled from the game in the
  style of the pre-2.0J `osPfsAllocateFile`/`osPfsDeleteFile`.
- EEPROM (`io/conteep*.c`, `0x80003C10-0x800046E0`): 4K only (no 16K
  case; `osEepromProbe` returns 1 for any EEPROM), the address checked
  before the SI is taken, the PIF RAM filled with 0xFF before each read.
  This is the form in Blast Corps (early 1997), which links an older
  libultra than any ultralib build.
- Rumble Pak (`io/motor.c`, `0x800046E0-0x80004CF0`): `osMotorStop`/
  `osMotorStart`/`osMotorInit` without ultralib's pre-2.0J
  `__osMotorinitialized`, checking the pak's reply against fixed CRCs
  (0, 0xEB), and no 0xFE probe in `osMotorInit`.
- The PIF RAM is cleared word by word, all 16 words, before each command
  is packed (`__osPackRequestData`, `__osPackReadData`,
  `__osPackResetData`, `__osPackRamRead/WriteData`, `__osPfsRequestData`,
  `__osEepStatus`), and `osContStartReadData` fills it with 0xFF before
  the read, as in Blast Corps. `osContReset` sets `__osContLastCmd` last
  and writes no end marker; `__osPfsGetStatus` asks all four channels
  (one function, `io/pfsgetstatus.c`, where 2.0I asks one).
- `osContInit` and `osEepromLong*` compute their waits through
  `osClockRate` (`OS_USEC_TO_CYCLES` in `src/libultra/libultra_bm64.h`):
  `__ll_mul` then `__ull_div` by 1000000, where 2.0I's `os_convert.h`
  folds the clock into a constant.
- `__osPfsReleasePages` frees the page it stops at without checking its
  bank; `osPfsReadWriteFile` doesn't reject an empty directory entry;
  `osPfsReFormat` returns without releasing the SI when
  `__osPfsGetStatus` fails.
- `osPfsInitPak` never reads the pack's ID block (it checksums the stack,
  so `__osCheckPackId` falls back on the backup IDs). No ultralib
  revision has this: an SDK bug fixed by 2.0I, or Hudson's change; the
  code doesn't say which.
- `osCartRomInit` and `osLeoDiskInit` don't set the handle's `speed`;
  `osEPiRawReadIo`/`WriteIo` only wait for the PI (no `EPI_SYNC`).
- `osAiSetNextBuffer` tests `(end & 0x3FFF) == 0x2000` for the hardware
  bug, where 2.0I tests `(end & 0x1FFF) == 0`.
- `__osException` (`os/exceptasm.s`) is 2.0I's but for one instruction:
  the SP interrupt is acknowledged with `SP_CLR_INTR` alone, where 2.0I
  also clears signal 3.

Other objects of the same layer are 2.0I's exactly (`osContStartQuery`,
`osContSetCh`, `osPfsChecker`, `contpfs.c`,
`osPfsInit`), and `osContInit` already sends `CONT_CMD_REQUEST_STATUS`
where Blast Corps' sends `CONT_CMD_RESET`. So the game links a libultra
between Blast Corps' and 2.0I: 2.0I's build flags (libc `-O3`) and most of
2.0I's code, with an SI/PI/controller pak layer from just before it (2.0G
or 2.0H would fit, but no archive of those is at hand to check against).

**Hudson's `alSynStartVoiceParams`** (`0x80001A50`, linked with the
game's sound code rather than with libaudio): 2.0I's function without its
`fxmix` fix-up, and with every voice centred (`AL_PAN_CENTER`) when bit 0
of the game's `D_8001C4B0` is set (func_80001A04 sets it). Built `-O3`
like libaudio.

**2.0I's own, but unplaced:** `sndplayer.c`'s static functions
(`0x8000C080-0x8000C654`, `_handleEvent` and the rest), `xprintf.c`'s
`_Putfld` (`0x80012DE0`) and `xldtob.c`'s `_Genld` (`0x80019310`) match
2.0I byte for byte; they are static, so no symbol named them, and
`libmatch.py` now matches such objects whole.

Still asm: `osUnmapTLBAll` (`0x80003190`, `unmaptlball.s`) is an older
revision too (all 31 entries, `bnezl`), but EU's 0x60-byte link gap
follows it, which a source object can't carry. `osPiGetDeviceType` and
`alSndpGetSound` (`0x80005480`, `0x8000C8D0`) match 2.0I but are two
instructions long, too short to place by body.

## Sources

`src/libultra/<dir>/<file>.c` (or `.s`) is ultralib's file of that name
at the pinned commit, with this game's differences, each described at
the top of the file (NOTICES.md has the attribution). They are built with
ultralib's headers (`include/ultralib`, `BUILD_VERSION=VERSION_I`) and
2.0I's `libultra_rom` flags: `-mips2`, `-O1`, `-O3` for `audio/`, `libc/`
and `gu/`. `os/exceptasm.s` is assembled by IDO (`-mips3 -O1`, which
schedules it), its symbol table rewritten by strip for GNU ld and the
object relabelled mips2 (`tools/elf_mips2.py`).

`-O1` code is sensitive to the source's line breaks: a loop body on the
loop's line schedules differently (`contramwrite.c`), and statement order
picks the temporary registers (`osPfsReSizeFile`'s bookkeeping after
`__osPfsDeclearPage`).

## Data

boot_code's data can't be cut from the module's start (the game's code
comes first), so library objects are placed on their own:
`data_split.txt` gives an object's section sizes and, per version, where
each of its sections is (`tools/data_split.py <v> --place boot_code
libultra/<dir>/<file>` finds that from the object's `%hi`/`%lo`
relocations and checks the bytes). `tools/layout.py` cuts them out of the
asm blocks. Only objects that need it are placed:

- those whose code depends on defining a variable in the same file: IDO
  shares one `lui` between fields of a variable it defines but not of an
  extern (`CartRomHandle`, `LeoDiskHandle`), and function-level statics
  (`osAiSetNextBuffer`'s `hdwrBugFlag`);
- those with jump tables, strings or constants in `.rodata` (`sndplayer`,
  `xprintf`, `xldtob`, `exceptasm`).

The others refer to their variables as externs, defined by the asm data
(`__osContPifRam`, `__osEepPifRam`, `__osPfsPifRam`, the motor buffers,
`__osContinitialized`, ...), with the names gen_symbols.py gives them.
The addresses are the same in both versions (the 0x60 gap is in the
text).

## libaudio

libaudio is 2.0I's, as built in `libultra_rom` (`-O3`). It is not an
older or different audio library. These match whole: synthesizer,
drvrNew, envmixer, load (ADPCM and raw16), resample, reverb, aux and main
bus, save, events, sequence and compact-sequence parsing (`seq.c`,
`cseq.c`), both sequence players with all their `alSeqp*`/`alCSP*`
objects, bank file setup, heap and cents, and the sound player
(`sndplayer.c`, whose static event handler only lacked a name). Only
`alSynStartVoiceParams` differs: Hudson's patch (above). The audio microcode
is in main_code's data (docs/LAYOUT.md, "Stage 2").
