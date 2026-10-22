/* A mupen64plus video plugin that draws nothing and counts frames.
 *
 * The core calls a video plugin's UpdateScreen once per vertical interrupt;
 * this one counts those calls and, at the frame set by vicount_set(), calls
 * back into the front end (tools/emu_ram.py), which reads RDRAM and either
 * sets the next frame (vicount_at()) or stops the run.  The core's own
 * frame callback only fires from a real plugin's buffer swap, so a
 * headless run needs this.  vicount_romopen() sets a callback for RomOpen,
 * which the core calls after it has set up the machine and before the
 * game's first instruction (tools/tas.py adjusts the core there).
 *
 *   cc -O2 -shared -fPIC -o build/tools/m64p_vicount.so tools/src/m64p_vicount.c
 */
#include <stddef.h>
#include <stdint.h>

typedef void (*frame_cb)(unsigned int frame);

static unsigned int frames;
static unsigned int target;
static frame_cb callback;
static void (*romopen_cb)(void);
static unsigned int *mi_intr;
static const uint32_t *rdram, *dmem;
static int dp_on_dlist;
static unsigned int dlists, fullsyncs;

/* the start of the core's GFX_INFO, the same in every core version */
typedef struct {
    unsigned char *header, *rdram, *dmem, *imem;
    unsigned int *mi_intr_reg;
} gfx_info_head;

/* A real video plugin raises the RDP's interrupt (MI_INTR_DP) when a
 * display list has a full sync (gDPFullSync), and the core then delivers
 * DP_INT.  vicount_dp(1) does that: it walks the task's display list
 * (F3D/F3DEX or F3DEX2 commands: branches, calls, segments) looking for
 * G_RDPFULLSYNC.  vicount_dp(2) raises it after every display list.  By
 * default it never does, as before. */
void vicount_dp(int on) { dp_on_dlist = on; }

/* (display lists, display lists with a full sync) so far */
unsigned int vicount_dlists(void) { return dlists; }
unsigned int vicount_fullsyncs(void) { return fullsyncs; }

static uint32_t ram32(uint32_t addr) { return rdram[(addr & 0x7FFFFF) >> 2]; }

static int has_fullsync(void)
{
    uint32_t seg[16] = { 0 }, stack[32];
    int sp = 0;
    uint32_t pc = dmem[0xFF0 / 4] & 0x7FFFFF; /* OSTask.data_ptr */
    for (int n = 0; n < 1000000; n++) {
        uint32_t w0 = ram32(pc), w1 = ram32(pc + 4);
        pc += 8;
        switch (w0 >> 24) {
        case 0xE9: /* G_RDPFULLSYNC */
            return 1;
        case 0x06: /* G_DL (F3D, F3DEX) */
        case 0xDE: /* G_DL (F3DEX2) */
            if (((w0 >> 16) & 0xFF) == 0) {
                if (sp == 32)
                    return 0;
                stack[sp++] = pc;
            }
            pc = (seg[(w1 >> 24) & 15] + (w1 & 0xFFFFFF)) & 0x7FFFFF;
            break;
        case 0xB8: /* G_ENDDL (F3D, F3DEX) */
        case 0xDF: /* G_ENDDL (F3DEX2) */
            if (sp == 0)
                return 0;
            pc = stack[--sp];
            break;
        case 0xBC: /* G_MOVEWORD (F3D, F3DEX): index in the low byte */
            if ((w0 & 0xFF) == 6)
                seg[((w0 >> 8) & 0xFFFF) / 4 & 15] = w1 & 0xFFFFFF;
            break;
        case 0xDB: /* G_MOVEWORD (F3DEX2) */
            if (((w0 >> 16) & 0xFF) == 6)
                seg[(w0 & 0xFFFF) / 4 & 15] = w1 & 0xFFFFFF;
            break;
        }
    }
    return 0;
}

unsigned int vicount_frames(void) { return frames; }

void vicount_set(unsigned int at, frame_cb cb)
{
    frames = 0;
    target = at;
    callback = cb;
}

void vicount_at(unsigned int at) { target = at; }

void vicount_romopen(void (*cb)(void)) { romopen_cb = cb; }

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

int InitiateGFX(gfx_info_head info)
{
    mi_intr = info.mi_intr_reg;
    rdram = (const uint32_t *)info.rdram;
    dmem = (const uint32_t *)info.dmem;
    return 1;
}
int RomOpen(void)
{
    if (romopen_cb)
        romopen_cb();
    return 1;
}
void RomClosed(void) {}
void ChangeWindow(void) {}
void MoveScreen(int x, int y) { (void)x, (void)y; }
void ProcessDList(void)
{
    int full = rdram && dmem && has_fullsync();
    dlists++;
    fullsyncs += full;
    if (mi_intr && (dp_on_dlist == 2 || (dp_on_dlist == 1 && full)))
        *mi_intr |= 0x20; /* MI_INTR_DP */
}
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
