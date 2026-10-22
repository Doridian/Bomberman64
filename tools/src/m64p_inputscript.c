/* A mupen64plus input plugin that plays a script or a movie.
 *
 * Script (tools/emu_ram.py, tools/shift_check.py): inputscript_set() gives
 * it a frame counter (m64p_vicount.c's vicount_frames) and a list of
 * (frame, buttons) steps, sorted by frame: from each step's frame on,
 * controller 1 holds that step's buttons (the BUTTONS word of
 * m64p_plugin.h: 0x80 A, 0x40 B, 0x20 Z, 0x10 START, the stick in the top
 * two bytes).  Controllers 2-4 are unplugged.
 *
 * Movie (tools/tas.py): inputscript_movie() gives it one BUTTONS word per
 * controller per movie frame (keys[frame * 4 + controller]).  By frame,
 * a poll during VI n (after the n-th UpdateScreen) reads movie frame
 * n - offset, which is how BizHawk's movies count; inputscript_offset()
 * moves that mapping during the run.  By poll, as mupen64-rr's .m64
 * movies count, each read of the first plugged-in controller takes the
 * next frame (a sample of 0xC000 is mupen64-rr's soft reset:
 * inputscript_reset_wanted()).  Outside the movie, no buttons.
 *
 * inputscript_controllers() plugs in controllers (a bit mask, before the
 * run) and picks how they answer: the core's own standard controller, or
 * "raw" (a bit mask too), where this plugin answers the joybus commands
 * itself the way BizHawk's mupen64plus-input-bkm does for a controller
 * without a pak: status 05 00 00, and the buttons as the core would.  The
 * core's own controller says 05 00 02 (no pak) instead.
 *
 * The same script or movie gives the same run every time.
 *
 *   cc -O2 -shared -fPIC -o build/tools/m64p_inputscript.so tools/src/m64p_inputscript.c
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int Present;
    int RawData;
    int Plugin;
    int Type;
} CONTROL;

typedef struct {
    CONTROL *Controls;
} CONTROL_INFO;

typedef unsigned int (*frame_fn)(void);

static frame_fn frame_now;
static const unsigned int *step_frames;
static const unsigned int *step_buttons;
static int steps;

static const unsigned int *movie_keys;
static unsigned int movie_frames;
static int movie_offset;
static int movie_by_poll;
static unsigned int polls;      /* reads of the first plugged-in controller */
static unsigned int last_poll;  /* the frame counter at the last one */
static int reset_wanted;        /* a .m64 sample asked for a reset */

static int present = 1;
static int raw;

void inputscript_set(frame_fn now, const unsigned int *frames, const unsigned int *buttons, int n)
{
    frame_now = now;
    step_frames = frames;
    step_buttons = buttons;
    steps = n;
}

void inputscript_movie(frame_fn now, const unsigned int *keys, unsigned int frames, int offset, int by_poll)
{
    frame_now = now;
    movie_keys = keys;
    movie_frames = frames;
    movie_offset = offset;
    movie_by_poll = by_poll;
    polls = 0;
}

void inputscript_offset(int offset) { movie_offset = offset; }

void inputscript_controllers(int present_mask, int raw_mask)
{
    present = present_mask;
    raw = raw_mask & present_mask;
}

unsigned int inputscript_polls(void) { return polls; }

/* mupen64-rr marks a soft reset as a sample of 0xC000 (both reserved
 * bits): the controller reads no buttons then, and the front end resets */
int inputscript_reset_wanted(void)
{
    int r = reset_wanted;
    reset_wanted = 0;
    return r;
}
unsigned int inputscript_last_poll(void) { return last_poll; }

static int first_present(void)
{
    for (int i = 0; i < 4; i++)
        if (present >> i & 1)
            return i;
    return -1;
}

static unsigned int keys_for(int control)
{
    unsigned int now = frame_now ? frame_now() : 0, held = 0;
    if (control == first_present()) {
        polls++;
        last_poll = now;
    }
    if (movie_keys) {
        long f = movie_by_poll ? (long)polls - 1 : (long)now - movie_offset;
        unsigned int k = f >= 0 && f < (long)movie_frames ? movie_keys[f * 4 + control] : 0;
        if (movie_by_poll && k == 0xC000) {
            reset_wanted = 1;
            k = 0;
        }
        return k;
    }
    if (control == 0)
        for (int i = 0; i < steps && step_frames[i] <= now; i++)
            held = step_buttons[i];
    return held;
}

int PluginStartup(void *core, void *ctx, void *debug)
{
    (void)core, (void)ctx, (void)debug;
    return 0;
}

int PluginShutdown(void) { return 0; }

int PluginGetVersion(int *type, int *version, int *api, const char **name, int *caps)
{
    if (type) *type = 4; /* M64PLUGIN_INPUT */
    if (version) *version = 0x010000;
    if (api) *api = 0x020100;
    if (name) *name = "inputscript";
    if (caps) *caps = 0;
    return 0;
}

void InitiateControllers(CONTROL_INFO info)
{
    for (int i = 0; i < 4; i++) {
        info.Controls[i].Present = present >> i & 1;
        info.Controls[i].RawData = raw >> i & 1;
        info.Controls[i].Plugin = 1; /* PLUGIN_NONE: no pak */
        info.Controls[i].Type = 0;   /* CONT_TYPE_STANDARD */
    }
}

void GetKeys(int control, unsigned int *keys)
{
    *keys = keys_for(control);
}

/* bkm's DataCRC, for pak reads and writes without a pak */
static unsigned char data_crc(const unsigned char *data, int len)
{
    unsigned char rem = data[0];
    int byte = 1, bit = 0;
    while (byte <= len) {
        int high = (rem & 0x80) != 0;
        rem = (unsigned char)(rem << 1);
        rem += (byte < len && data[byte] & (0x80 >> bit)) ? 1 : 0;
        rem ^= high ? 0x85 : 0;
        bit++;
        byte += bit / 8;
        bit %= 8;
    }
    return rem;
}

/* raw controllers: Command[0] is the tx length, [1] the rx length, [2]
 * the command, then its rx bytes */
void ReadController(int control, unsigned char *command)
{
    if (control < 0 || !(raw >> control & 1))
        return;
    switch (command[2]) {
    case 0x00: /* status */
    case 0xFF: /* reset */
        command[3] = 0x05;
        command[4] = 0x00;
        command[5] = 0x00; /* no pak */
        break;
    case 0x01: { /* buttons, in the host's order, as the core stores them */
        unsigned int k = keys_for(control);
        memcpy(command + 3, &k, 4);
        break;
    }
    case 0x02: /* pak read, pak write */
    case 0x03:
        command[5 + 32] = data_crc(command + 5, 32);
        break;
    }
}

int RomOpen(void) { return 1; }
void RomClosed(void) {}
void ControllerCommand(int control, unsigned char *command) { (void)control, (void)command; }
void SDL_KeyDown(int mod, int sym) { (void)mod, (void)sym; }
void SDL_KeyUp(int mod, int sym) { (void)mod, (void)sym; }
void RenderCallback(void) {}
void SendVRUWord(uint16_t length, uint16_t *word, uint8_t lang) { (void)length, (void)word, (void)lang; }
void SetMicState(int state) { (void)state; }
void ReadVRUResults(uint16_t *e, uint16_t *n, uint16_t *m, uint16_t *v, uint16_t *l, uint16_t *r)
{
    *e = *n = *m = *v = *l = *r = 0;
}
void ClearVRUWords(uint8_t length) { (void)length; }
void SetVRUWordMask(uint8_t length, uint8_t *mask) { (void)length, (void)mask; }
