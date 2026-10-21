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
tools/libmatch.py us build/ultralib/build/I/libultra_rom    # names with evidence
tools/gen_symbols.py us build/ultralib/build/I/libultra_rom # writes the files below
tools/layout.py us                         # the config, with the new boundaries
make clean && make VERSION=us extract && make VERSION=us
```

and the same for eu. `build_ultralib.sh` clones decompals/ultralib at a
fixed commit (the one Blast Corps uses) and builds `libultra_rom` for every
revision with IDO 5.3 and ultralib's own flags. Its voice library fails to
build on some hosts; the game doesn't link it, so the script carries on.
`libmatch.py` makes its code image from `baserom.<v>.z64`, so it works
whichever version is extracted.

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
  boundary.

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

Every function whose body differs between I and J matches I and not J:
`osInitialize`, `__osViInit`, `osCreateViManager`, `osViSetMode`,
`__osDisableInt`, the libc functions (`sprintf`, `_Printf`, `_Litob`,
`_Ldtob`, built `-O3` before 2.0J and `-O2` after), all of libaudio
(`-O3` before J), the controller pak (`osPfs*`), and gu (`guLookAt`,
`guMtxXFMF`). Blast Corps, earlier in 1997, has libc built
`-O1`, which no ultralib revision does. Bomberman 64's is built as in 2.0I.

The two versions link the same libultra. EU's text is byte for byte US's.
Only a 0x60-byte gap of zeros between two link units sits elsewhere (after
`osUnmapTLBAll` in EU, after `osSetThreadPri` in US), so `osInitialize`
and `osSetThreadPri` are 0x60 later in EU. The PAL/MPAL handling is
libultra's own: `__osViInit` picks `osViModePalLan1`, `osViModeMpalLan1`
or `osViModeNtscLan1` from `osTvType`.

The link order is not 2.0I's archive order. The 23 `alSeqp*` objects come
in the order `delete, setseq, getseq, play, stop, getstate, setbank, ...`,
while ultralib's `base/I/libultra_rom.txt` lists them alphabetically. The game may have been linked from a differently ordered
archive (another SDK release), or with the objects named on the command
line. The Bomberhackers/bm64 split has the same order.

## What is named

| | us | eu |
| --- | --- | --- |
| boot_code functions | 347 | 347 |
| boot_code data | 34 | 34 |
| main_code functions | 12 | 12 |
| main_code data | 1 (`__libm_qnan_f`) | 1 |

In boot_code, 248 names are `lib=exact`, 130 `lib=ref` and 3 `lib=fuzzy`
(the counts include data).
`alSeqp*` and `alCSP*` functions have identical bodies (one object each,
for the two sequence players), so the body alone can't place them. Each
family is linked as a run next to its own player (`seqplayer.o`,
`csplayer.o`) and to the functions of its family that did match uniquely
(`alSeqpLoop`, `alCSPGetTempo`). `libmatch.py` places each such name in
the run whose nearest placed neighbour is of its own family
(`resolve_twins`).

Static functions have no symbol in the objects, so they keep their
address names, but a whole-object match covers their code. The fuzzy
names are `osCreateScheduler` and `osScAddClient` (0.95 and 0.93), in the
game's copy of the SDK's sample scheduler (`sched.c`, compiled with the
game and with asserts, at `0x800014B0`), and `osPfsReFormat` (0.99).

## What doesn't match

About 0x11A00 of boot_code's 0x17E00 bytes of non-zero text are exactly
matched library code. The rest is the game's own code before
`0x80001A50`, plus these library parts, which no ultralib revision
reproduces (D to L, checked by similarity):

- `alSynStartVoiceParams` (`0x80001A50`), placed by reference. It sits
  before `osMapTLB`, apart from the rest of libaudio. The reference decomp's
  split guesses it is a Hudson override.
- EEPROM (`0x80003C10-0x80004CF0`: `osEepromProbe`, `osEepromRead`,
  `osEepromWrite`, the long read/write and code after them). The best
  candidate is `__osEepStatus` at 0.69.
- The controller (`0x800056A0-0x80005E38`: `osContInit` 0.71,
  `osContStartReadData`, `osContGetReadData`, `osContReset` 0.92),
  `__osContRamRead`/`Write` (`0x80013F00-0x80014600`), and some controller
  pak code (`osPfsReFormat`, `__osPfsReleasePages`, `osPfsReadWriteFile`,
  `__osPfsRequestData`, `__osPfsGetStatus`, and `0x8000FA20-0x800106A0`).
- `osCartRomInit` (0.95), `osLeoDiskInit` (0.92), `osEPiRawWriteIo`/`ReadIo`.
- `__osException` (`exceptasm.s`, `0x80011310`). `__osExceptionPreamble`
  matches.
- `alSndp*`'s static event handler (`0x8000C080-0x8000C654`). Every public
  `alSndp*` function matches by body, but `sndplayer.o` as a whole doesn't.
- `0x80012DE0-0x8001344C` and `0x80019310-0x80019874`, next to libc.

Apart from the libaudio pieces and the exception handler, these are I/O
files that changed across releases. They point to a libultra that isn't
exactly any ultralib build: 2.0I flags, with an older (or patched)
SI/PI/EEPROM layer. Their names are
placed only where a matched function's relocations give them (`lib=ref`).
To match them, decompile them from the asm against 2.0I's sources.

## libaudio

libaudio is 2.0I's, as built in `libultra_rom` (`-O3`). It is not an
older or different audio library. These match whole: synthesizer,
drvrNew, envmixer, load (ADPCM and raw16), resample, reverb, aux and main
bus, save, events, sequence and compact-sequence parsing (`seq.c`,
`cseq.c`), both sequence players with all their `alSeqp*`/`alCSP*`
objects, bank file setup, heap and cents. Only `alSynStartVoiceParams`
and the sound player's static handler differ (above). The audio microcode
is in main_code's data (docs/LAYOUT.md, "Stage 2").
