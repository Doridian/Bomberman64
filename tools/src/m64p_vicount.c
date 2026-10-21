/* A mupen64plus video plugin that draws nothing and counts frames.
 *
 * The core calls a video plugin's UpdateScreen once per vertical interrupt;
 * this one counts those calls and, at the frame set by vicount_set(), calls
 * back into the front end (tools/emu_ram.py), which reads RDRAM and stops
 * the run.  The core's own frame callback only fires from a real plugin's
 * buffer swap, so a headless run needs this.
 *
 *   cc -O2 -shared -fPIC -o build/tools/m64p_vicount.so tools/src/m64p_vicount.c
 */
#include <stddef.h>

typedef void (*frame_cb)(unsigned int frame);

static unsigned int frames;
static unsigned int target;
static frame_cb callback;

unsigned int vicount_frames(void) { return frames; }

void vicount_set(unsigned int at, frame_cb cb)
{
    frames = 0;
    target = at;
    callback = cb;
}

int PluginStartup(void *core, void *ctx, void *debug)
{
    (void)core, (void)ctx, (void)debug;
    return 0;
}

int PluginShutdown(void) { return 0; }

int PluginGetVersion(int *type, int *version, int *api, const char **name, int *caps)
{
    if (type) *type = 2; /* M64PLUGIN_GFX */
    if (version) *version = 0x010000;
    if (api) *api = 0x020200;
    if (name) *name = "vicount";
    if (caps) *caps = 0;
    return 0;
}

int InitiateGFX(void *info) { (void)info; return 1; }
int RomOpen(void) { return 1; }
void RomClosed(void) {}
void ChangeWindow(void) {}
void MoveScreen(int x, int y) { (void)x, (void)y; }
void ProcessDList(void) {}
void ProcessRDPList(void) {}
void ShowCFB(void) {}
void ViStatusChanged(void) {}
void ViWidthChanged(void) {}
void ReadScreen2(void *dest, int *w, int *h, int front) { (void)dest, (void)front; *w = *h = 0; }
void SetRenderingCallback(void (*cb)(int)) { (void)cb; }
void ResizeVideoOutput(int w, int h) { (void)w, (void)h; }
void FBRead(unsigned int addr) { (void)addr; }
void FBWrite(unsigned int addr, unsigned int size) { (void)addr, (void)size; }
void FBGetFrameBufferInfo(void *info) { (void)info; }

void UpdateScreen(void)
{
    if (++frames == target && callback)
        callback(frames);
}
