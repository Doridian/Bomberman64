# Online multiplayer (plan)

Bomberman 64's battle mode is up to four players on one console. The port
turns that into online play. Each player runs the game, only controller
inputs cross the network, and every peer simulates the same frames. The
transport is WebRTC data channels, from both the native build and the browser
build, so a browser player and a native player can be in the same match. The
model is what [matchbox](https://github.com/johanhelsing/matchbox) plus
[GGRS](https://github.com/gschup/ggrs) give a Rust game:

| layer              | Rust analogue      | here                                                         |
| ---                | ---                | ---                                                          |
| signaling server   | `matchbox_server`  | speak matchbox's websocket protocol, so its server works as is |
| peer transport     | `matchbox_socket`  | libdatachannel natively, the browser's `RTCPeerConnection` in wasm |
| session / rollback | GGRS               | a small C session layer in `port/net/`                      |
| game               | your `World`       | the decompiled game, stepped one frame at a time            |

Nothing here is written yet. It depends on the port (docs/ROADMAP.md, phases
6–7), and the determinism work below starts with the port itself. Adding it
afterwards would be much harder.

## Requirements the port has to meet first

Online play is only as good as the port's determinism. These are port
requirements from day one, tested by `--deterministic`/`--replay`, as in
Blast Corps' port:

1. **The game advances by inputs alone.** A frame of game logic is a pure
   function of (state, four controllers' inputs). The audio thread, the
   video interrupt, the wall clock and the host's frame rate can't reach
   game state. Where the game reads `osGetCount`, VI counters or the
   retrace count as a timer or RNG seed, the port feeds it a value derived
   from the frame number.
2. **One logic step can be run on demand.** The host drives
   `port_step(inputs[4])` and gets one game frame back, with rendering
   optional. Rollback re-simulates several frames inside one host frame
   without drawing them.
3. **Lag frames are game frames too.** If the game's logic runs once per
   N retraces, or skips under load, the step's unit is whatever the logic
   loop uses, and the netplay layer counts in those units.
4. **Bit-identical floats across hosts.** x86-64, arm64 and wasm32 must
   produce the same bits: `-ffp-contract=off`, no x87 (SSE2 on 32-bit x86),
   no `-ffast-math`, and our own `sinf`/`cosf`/`sqrtf` where the game uses
   libultra's (those are C and get decompiled anyway). Never call the host's
   libm from game logic.
5. **The state can be saved and restored.** All mutable game state lives in
   regions the port knows: the game's `.data`/`.bss`, its heap (Hudson's
   allocator works out of fixed arenas), and the overlay that is loaded.
   A snapshot is a `memcpy` of those regions. Pointers are native, so a
   snapshot only means anything in the process that made it, which is all
   rollback needs.
6. **A state hash that crosses hosts.** Desync detection compares a hash
   across peers, and pointers differ between a 64-bit native peer and a
   wasm32 one. The hash therefore covers a pointer-free view: the player
   records, the bomb and fire grids, the RNG state and the timers, each
   chosen field by field once the structs are known (docs/TYPES.md when it
   exists). A replay test that runs two different hosts, such as native
   and node, must give identical hashes every frame.

## Phases

1. **Input plumbing.** Four logical controllers fed from the host every
   step, from local devices, a replay file, or the network. Battle mode
   only, first.
2. **Loopback harness.** Two (or four) game instances in one process,
   exchanging inputs through a simulated lossy, delayed link with
   comparing hashes every frame. Any desync fails CI. This is where
   determinism bugs are found, without a network.
3. **Delay-based lockstep over WebRTC.** Every peer waits until it has
   every player's input for frame *n*, with a fixed input delay of 2–3
   frames. It is simple and always correct, so it becomes the fallback.
4. **Rollback.** Each peer predicts the missing inputs (repeat the last
   one), simulates ahead, and on a misprediction restores the snapshot and
   re-simulates. It needs (2) and (5) to be cheap: the snapshot size
   decides how many frames of rollback fit in 16 ms, so it is measured
   early.
5. **Lobby.** Room codes over the signaling server, peer slots mapped to
   battle-mode player numbers, spectators (inputs only, no rollback), and
   a disconnected player handed to the game's own CPU AI.

## Transport

- **Native:** [libdatachannel](https://github.com/paullouisageneau/libdatachannel)
  (MPL-2.0, C API `rtc/rtc.h`), vendored under `port/third_party/` and
  built by the port's CMake. It brings its own ICE (libjuice), SCTP
  (usrsctp) and DTLS (OpenSSL or mbedTLS).
- **Browser:** the same C API over the browser's WebRTC
  ([datachannel-wasm](https://github.com/paullouisageneau/datachannel-wasm)
  is the reference for the binding), so `port/net/` has one code path.
- Data channels are **unreliable and unordered** (`maxRetransmits = 0`).
  Each packet carries the sender's last ~8 frames of input plus an ack
  of the newest frame it has seen from each peer, so a lost packet costs
  nothing. Ordering and reliability are the session layer's job, as in
  GGRS.
- **Signaling:** a websocket client for matchbox's protocol (JSON
  `IdAssigned`/`NewPeer`/`PeerLeft`/`Signal` messages carrying SDP and
  ICE). That lets a deployed `matchbox_server` serve as the lobby server,
  including the browser build's. STUN by default, TURN configurable.
- Native-to-browser and native-to-native matches use the same wire
  format. A version and ROM hash handshake refuses a mismatched peer:
  us and eu don't simulate alike, because EU is 50 Hz with PAL timings.

## Open questions

- Is the battle-mode logic a fixed step per retrace, or does it scale by
  elapsed frames like many N64 games? This decides what "a frame" is for
  (3) above. Answer it during the decompile of the main loop.
- Overlay swaps mid-match (the results screen and the next round) have to
  be part of the snapshot or at match boundaries only.
- Battle mode is one shared arena view, so every peer draws the same
  picture. Menus before the match (character and rule select) are driven
  by all four controllers too, so the session covers them, or the lobby
  replaces them and starts the match with agreed settings.
