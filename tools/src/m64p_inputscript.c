/* A mupen64plus input plugin that plays a script on controller 1.
 *
 * inputscript_set() gives it a frame counter (m64p_vicount.c's
 * vicount_frames) and a list of (frame, buttons) steps, sorted by frame:
 * from each step's frame on, controller 1 holds that step's buttons (the
 * BUTTONS word of m64p_plugin.h: 0x80 A, 0x40 B, 0x20 Z, 0x10 START, the
 * stick in the top two bytes).  Controllers 2-4 are unplugged.  The same
 * script gives the same run, which tools/shift_check.py relies on.
 *
 *   cc -O2 -shared -fPIC -o build/tools/m64p_inputscript.so tools/src/m64p_inputscript.c
 */
#include <stddef.h>
#include <stdint.h>

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

void inputscript_set(frame_fn now, const unsigned int *frames, const unsigned int *buttons, int n)
{
    frame_now = now;
    step_frames = frames;
    step_buttons = buttons;
    steps = n;
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
        info.Controls[i].Present = i == 0;
        info.Controls[i].RawData = 0;
        info.Controls[i].Plugin = 1; /* PLUGIN_NONE: no pak */
        info.Controls[i].Type = 0;   /* CONT_TYPE_STANDARD */
    }
}

void GetKeys(int control, unsigned int *keys)
{
    unsigned int now = frame_now ? frame_now() : 0, held = 0;
    if (control == 0)
        for (int i = 0; i < steps && step_frames[i] <= now; i++)
            held = step_buttons[i];
    *keys = held;
}

int RomOpen(void) { return 1; }
void RomClosed(void) {}
void ControllerCommand(int control, unsigned char *command) { (void)control, (void)command; }
void ReadController(int control, unsigned char *command) { (void)control, (void)command; }
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
