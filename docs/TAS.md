# TAS movies as a validation run

TASVideos has three movies of this game, all on *Baku Bomberman* (jp,
`NBMJ`). Played headless, a movie is a long, input-driven run through
every system of the game, and two ROMs (the original and a rebuilt or
shifted one) can be compared along it. `tools/tas.py` plays them on the
system's mupen64plus 2.6.0 with our two plugins. **None of them syncs to
the end**: the current any% desyncs in its first stage (below). The tool
still gives a repeatable 78,000-frame run that a rebuilt ROM has to follow
exactly.

```
tools/tas.py fetch                       # download the movies into build/tas/movies/
tools/tas.py info 4908M                  # what the movie is and needs
tools/tas.py run 4908M baserom.jp.z64 --json build/tas/orig.json
tools/tas.py check 4908M build/jp/bm64.jp.z64 build/jp-shift/bm64.jp.z64
tools/tas.py compare a.json b.json
tools/bizhawk_core.sh                    # BizHawk 2.8's own core, for --bizhawk
```

Run them under `nice -n 10`. A full run of 4908M takes about a minute.

## The movies

The files aren't in the repository. `tas.py fetch` downloads each from its
publication's download handler (TASVideos asks not to link the files
directly) and checks the sha1s recorded in `tools/tas.py` (`MOVIES`).

| id | movie | emulator | length |
| --- | --- | --- | --- |
| [4908M](https://tasvideos.org/4908M) | any% by zvsp, 21:40.57 (current) | BizHawk 2.8, `.bk2` | 78,034 frames |
| [2053M](https://tasvideos.org/2053M) | any% by Nahoc, 23:38.55 (obsoleted) | mupen64-rr 8, `.m64` | 80,481 samples, 85,113 VIs |
| [2350M](https://tasvideos.org/2350M) | "100%" by zvsp, 1:01:36.02 | mupen64-rr, `.m64` | 206,947 samples, 221,761 VIs |

**4908M** (`Header.txt`, `SyncSettings.json`): core Mupen64Plus (BizHawk's
fork of the 2013 mupen64plus), `Core` 1 (mupen's cached interpreter),
`Rsp` 0 (HLE), `VideoPlugin` 4 (GLideN64, copying the colour and depth
buffers back to RDRAM), `DisableExpansionSlot` true, controller 1 plugged
in without a pak, 2-4 unplugged. Its log has one line per frame, and a
frame is a VI: BizHawk stops the core at every vertical interrupt, whether
or not the game read the controller (lag frames are in the log too, their
input unread). BizHawk runs two frames after power-on before the movie's
first. The movie soft-resets at frame 521 (the "game restart": the hard
mode file is saved, then the reset skips the opening). The stick is the
axes, or full tilt from the "A Up/Down/Left/Right" buttons.

**2053M, 2350M** (`.m64` version 3): one sample per read of controller 1
(Mupen64 0.5's PIF), 8 MiB, Glide64 and Jabo's audio. Sample 318 of both
is 0xC000, mupen64-rr's soft reset.

## How the core is set up

`tools/tas.py` (`play()`) matches what can be matched in 2.6.0:

- **Frame length.** BizHawk's core times a frame as (V_SYNC + 1) lines of
  1500 counts, 789000 counts at NTSC's V_SYNC. 2.6.0 divides its VI clock
  by 60 and the lines, 811092 counts: 3% more CPU time a frame, so fewer
  lag frames. The clock isn't a setting, so at ROM open (m64p_vicount.c's
  `vicount_romopen()`) `tas.py` finds `struct vi_controller` in the core's
  memory (by the clock and the refresh rate) and sets the clock to
  1500 × 60 × 526. Frames are then 789000 counts, measured (`--vi core`
  leaves it).
- **Core parameters** (emu_ram.py's `Session`): `RandomizeInterrupt` off,
  `CountPerOp` 2 and `SiDmaDuration` 0x900 (BizHawk's core has both fixed),
  `R4300Emulator` from the movie, `DisableExtraMem` from the movie.
- **EEPROM:** BizHawk's blank one is zeros, 2.6.0's is 0xFF; the run starts
  from a zeroed file.
- **Controller:** BizHawk's input plugin (`mupen64plus-input-bkm`) answers
  the joybus itself for a controller without a pak: status `05 00 00`.
  2.6.0's own controller says `05 00 02`. m64p_inputscript.c does what bkm
  does (`--no-raw` for the core's).
- **Input:** a read during VI n gets movie frame n − 2 (`--offset`); the
  reset is issued at the start of its frame, as BizHawk does. `.m64`:
  sample k at the k-th read.
- **The RDP interrupt.** A real video plugin raises MI_INTR_DP when a
  display list has a full sync, and the core then delivers DP_INT.
  Without it this game submits one display list and never another (it
  waits for the RDP), which changes its timing completely. m64p_vicount.c
  now walks each display list for `G_RDPFULLSYNC` (`vicount_dp(1)`,
  `--dp`); every one of this game's has one. `shift-check` doesn't turn it
  on, so it runs as before.

Checkpoints, every VI: the overlay at 0x80043000 (identified against the
overlays of the ROM being run), the stage timer (`D_802AC640`, 0x802AB870
in jp, the clock shown in stages; it runs on through a lost life and
starts over with the next stage, so its value then is the stage's time, as
the clear screen shows), the resets, and the VIs where the game didn't
read the controller. For a build the timer's address comes from its ELF.

## How far 4908M syncs

On 2.6.0, set up as above, the run follows the publication's encode
through power-on, the title, mode and file select, the hard-mode file
saved and the reset at frame 521, the title again, the file select (Data 1
now the hard file), the world select (Blue Resort) and the first stage's
map and start (overlays `ovl_0B_01`, `ovl_0A_05`, `ovl_0B_06`, reset,
`ovl_0B_01`, `ovl_0A_05`, `ovl_0B_01`, `ovl_0B_06`, `ovl_0B_02`, then
`ovl_0D_01` at VI 1301). The stage timer starts at VI 1603.

It desyncs at the stage's first move, around movie frame 1610. In the
encode Bomberman lifts his first bomb (stage timer 46) and throws it over
the gate; here the bomb stays where it was put and he walks on. He loses
his lives, it's game over at VI ~4500, the continue countdown runs out, and
from VI 5385 the game is in its attract loop (the opening, `ovl_0A_02`
and `ovl_0A_01`; the title; the demos `ovl_0D_01`, `ovl_0E_09`,
`ovl_0F_01`, `ovl_0C_02`) to the end of the movie. The first stage time
should be 1431 (the encode's clear screen); it's never reached.

What was ruled out, each giving the same game over at VI 5385 (or the same
VI shifted by the change):

- the VI clock (BizHawk's or 2.6.0's), the EEPROM fill (00 or FF), bkm's
  controller or the core's, the pure, cached or recompiling CPU, the RDP
  interrupt never, on full sync or always;
- the input offset, from −50 to +20 VIs from the stage's load on (the
  game over moves with it, frame for frame);
- the random number generator: the game seeds it from `osGetTime()` when
  main_code starts, and its state differs between cores, but setting its
  index to other values at VI 1400, 4500 or 5392 changes nothing before
  5385;
- **BizHawk's own core.** `tools/bizhawk_core.sh` builds BizHawk 2.8's
  mupen64plus fork for Linux (a shim for its Win32 frame-advance semaphore;
  sha256-pinned source), and `tas.py run --bizhawk build/tas/bizhawk/dist`
  drives it the way BizHawk does (frame advance, two frames before the
  movie, resets between frames). It reproduces the save trick and the
  menus and fails the same way, at VI 5385.

So the cause isn't 2.6.0's core: both cores with our plugins miss the same
input. It is a timing question: dropping the single C-Up press at movie
frame 1361 (the camera, just after the stage's load) lets the 2.6.0 run
survive to VI 10634 (but not BizHawk's core), which says that a press's
effect depends on the exact frame state when it lands. What our runs
don't have of BizHawk's is its video plugin, GLideN64: the RDP itself
(colour and depth written to RDRAM, which these plugins never write) and
the moments it raises the DP interrupt. A headless run without a renderer
can't reproduce that, so this is as far as it goes on mupen64plus 2.6.0
with our plugins: the menus, the reset and the stage's start, about movie
frame 1606 of 78034.

The `.m64` movies desync before their reset: Mupen64 0.5 read the
controller at other moments during boot, so the samples land elsewhere
(the reset sample 318 comes at the title, VI 464). Their parser and the
per-read playback are there, unverified.

## As a validation run

Though it desyncs, the run is exactly repeatable, so it is still a
check: a rebuilt ROM has to give the same checkpoints at the same VIs.
`build/jp/bm64.jp.z64` (byte for byte the original) does, all 80 of them.
The shifted build (`build/jp-shift/bm64.jp.z64`, unpinned) follows the
original through the first 14 checkpoints exactly (boot, reset, menus,
the stage, the game over and the opening at VI 7289), with one controller read fewer; then the attract loop's scenes come a few VIs earlier or
later (VI 8301 against 8306). That is the same timing effect as in
`shift-check` (the bigger DMAs change the cycle count and the RNG seed),
so `check --slack N` accepts a drift of N VIs. There is no `make` target:
until a movie syncs to the end, `make shift-check` is the check, and this
is a longer smoke test.
