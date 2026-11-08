/*
 * -O3. A texture drawn scaled in tiles: LoadTile per tile, then a
 * TextureRectangle, flipped by the sign of x0 - x1 and y0 - y1. Every
 * function is emitted in the original's order, with the original's stub
 * for the inlined func_8025EC3C. Matching notes:
 * - func_8025E760 is the same LoadTile switch as 7D840's func_80263464.
 *   Its parameters come in the order (gfxp, uls, mode, ult, height, lrs,
 *   lrt, img, width): IPA emits the argument moves in parameter order,
 *   so addiu s0,sp,348 comes first and as1 puts the three moves in the
 *   original's delay slots.
 * - func_8025EC3C takes tw/th by pointer, which keeps them in memory.
 * - Rounding: RNDD adds 0.5f to a double, which gives the original's
 *   separate lui 0x3fe0 constants; `+ 0.5` would share one. Every RNDD s
 *   or t is masked, `(... << 5) & 0xFFFF`, the RNDF ones aren't: the mask
 *   costs no instruction (as1 drops it before the shift) but is one more
 *   ugen temp, which realigns the t6-t9 free list.
 * - func_8025EC44: `if (!scaleX) {}` after the call makes scaleY the
 *   float kept in memory. `pad1 = i + 1` (a dead store) before case 2's
 *   yl line gives i + 1 and j + 1 their expression bits ahead of
 *   ucvt(y1), so uopt's temp slots come out at 0x3C/0x38. `if (flags ==
 *   3) {}` first in the outer body lowers the shared count at node 23
 *   (Chow's addadjacents), so j + 1's split piece reaches the outer head
 *   and lives in v0. `if (!(tileH - i)) {}` after case 1's t line keeps
 *   those temp slots, and `if (!(height)) {}` before the th clamp gives
 *   width a0, height v1. The unused q0/q1 locals are frame slots.
 */
#include "common.h"
#define F3DEX_GBI
#define _SHIFTL(v, s, w) ((unsigned int) (((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define _SHIFTR(v, s, w) ((unsigned int)(((unsigned int)(v) >> (s)) & ((0x01 << (w)) - 1)))
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#include "ultralib/PR/gbi.h"

typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ u16 width;
    /* 0x06 */ u16 height;
    /* 0x08 */ s32 offset;
} TexEntry; /* size 0xC */

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ TexEntry entries[1];
} TexFile;

/* Rounding to nearest: to an int in each arm, or a float/double to convert later. */
#define RNDI(x) ((x) >= 0.0f ? (s32) ((x) + 0.5f) : (s32) ((x) - 0.5f))
#define RNDF(x) ((x) >= 0.0f ? (x) + 0.5f : (x) - 0.5f)
#define RNDD(x) ((x) >= 0.0 ? (x) + 0.5f : (x) - 0.5f)

static void func_8025E760(Gfx **gfxp, s32 uls, s32 mode, s32 ult, s32 height, s32 lrs, s32 lrt, u8 *img, u32 width) {
    Gfx *gfx = *gfxp;

    switch (mode) {
        case 0:
            gDPLoadTextureTile_4b(gfx++, img, G_IM_FMT_CI, width, height, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 1:
            gDPLoadTextureTile(gfx++, img, G_IM_FMT_CI, G_IM_SIZ_8b, width, height, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 2:
            gDPLoadTextureTile(gfx++, img, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 3:
            gDPLoadTextureTile(gfx++, img, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    *gfxp = gfx;
}

static u32 func_8025EC00(u32 a, u32 b) {
    u32 n = a / b;

    if (n * b < a) {
        n++;
    }
    return n;
}

static void func_8025EC3C(s32 mode, s32 *tw, s32 *th) {
    switch (mode) {
        case 0:
            *tw = *th = 64;
            break;
        case 1:
        case 2:
            *tw = 64;
            *th = 32;
            break;
        case 3:
            *tw = *th = 32;
            break;
    }
}

static void func_8025EC44(Gfx **gfxp, s32 x0, s32 y0, s32 x1, s32 y1, s32 mode, u8 *img, u32 width, u32 height) {
    Gfx *gfx;
    s32 nx;
    s32 ny;
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    s32 tileW;
    s32 tileH;
    s32 k;
    s32 pad1;
    s32 flags;
    f32 scaleX;
    f32 scaleY;
    s32 tw;
    s32 th;
    s32 s;
    s32 t;
    s32 dsdx;
    s32 dtdy;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;
    s32 q0;
    s32 q1;

    gfx = *gfxp;

    scaleX = x0 - x1;
    flags = 0;
    if (scaleX > 0.0f) {
        flags = 1;
    } else {
        scaleX = -scaleX;
    }
    scaleX /= width;
    scaleY = y0 - y1;
    if (scaleY > 0.0f) {
        flags |= 2;
    } else {
        scaleY = -scaleY;
    }
    scaleY /= height;
    if (scaleX == 0.0f || scaleY == 0.0f) {
        return;
    }
    func_8025EC3C(mode, &tw, &th);
    nx = func_8025EC00(width, tw);
    ny = func_8025EC00(height, th);
    tileW = tw;
    tileH = th;
    for (j = 0, y = 0; j < ny; j++, y += th) {
        if (flags == 3) {}
        for (i = 0, x = 0, tw = tileW; i < nx; i++, x += tileW) {
            if (width < x + tw) {
                tw = width - x;
            }
            if (!(height)) {}
            if (height < y + th) {
                th = height - y;
            }
            if (tw < 0) {
                tw = 1;
            }
            if (th < 0) {
                th = 1;
            }
            func_8025E760(&gfx, x, mode, y, height, x + tw - 1, y + th - 1, img, width);
            if (!scaleX) {}
            switch (flags) {
                case 0:
                    s = ((s32) RNDD(i * tileW + 0.5) << 5) & 0xFFFF;
                    t = ((s32) RNDD(j * tileH + 0.5) << 5) & 0xFFFF;
                    dsdx = RNDI(tw / scaleX / (tw + 1) * 1023.0f);
                    dtdy = RNDI(th / scaleY / (th + 1) * 1023.0f);
                    xl = RNDI(x0 + x * scaleX);
                    yl = RNDI(y0 + y * scaleY);
                    xh = RNDI(x0 + (x + tw) * scaleX);
                    yh = RNDI(y0 + (y + th) * scaleY);
                    gSPScisTextureRectangle(gfx++, xl << 2, yl << 2, xh << 2, yh << 2, 0, s, t, dsdx, dtdy);
                    break;
                case 1:
                    s = (s32) RNDF((f32) (i * tileW + tileW - 1)) << 5;
                    t = ((s32) RNDD(j * tileH + 0.5) << 5) & 0xFFFF;
                    if (!(tileH - i)) {}
                    dsdx = (s32) RNDF(-1.0f / scaleX * 1023.0f) & 0xFFFF;
                    dtdy = RNDI(th / scaleY / (th + 1) * 1023.0f);
                    k = (nx - i - 1) * tw;
                    xl = RNDI(k * scaleX + x1);
                    yl = RNDI(y0 + y * scaleY);
                    xh = RNDI((k + tileW) * scaleX + x1);
                    yh = RNDI(y0 + (y + th) * scaleY);
                    if (xh >= 0 && yh >= 0) {
                        if (yl < 0) {
                            gSPScisTextureRectangle(gfx++, xl << 2, yl << 2, xh << 2, yh << 2, 0, s, t, dsdx, dtdy);
                        } else {
                            gSPTextureRectangle(gfx++, xl << 2, yl << 2, xh << 2, yh << 2, 0, s, t, dsdx, dtdy);
                        }
                    }
                    break;
                case 2:
                    s = ((s32) RNDD(i * tileW + 0.5) << 5) & 0xFFFF;
                    t = (s32) RNDF((f32) (j * tileH + tileH - 1)) << 5;
                    dsdx = RNDI(tw / scaleX / (tw + 1) * 1023.0f);
                    dtdy = (s32) RNDF(-1.0f / scaleY * 1023.0f) & 0xFFFF;
                    xl = RNDI(x0 + x * scaleX);
                    k = (ny - j - 1) * th;
                    pad1 = i + 1;
                    yl = RNDI(k * scaleY + y1);
                    xh = RNDI(x0 + (x + tw) * scaleX);
                    yh = RNDI((k + tileH) * scaleY + y1);
                    if (xh >= 0 && yh >= 0) {
                        if (xl < 0) {
                            gSPScisTextureRectangle(gfx++, xl << 2, yl << 2, xh << 2, yh << 2, 0, s, t, dsdx, dtdy);
                        } else {
                            gSPTextureRectangle(gfx++, xl << 2, yl << 2, xh << 2, yh << 2, 0, s, t, dsdx, dtdy);
                        }
                    }
                    break;
                case 3:
                    s = (s32) RNDF((f32) ((i + 1) * tileW - 1)) << 5;
                    t = (s32) RNDF((f32) ((j + 1) * tileH - 1)) << 5;
                    dsdx = (s32) RNDF(-1023.0f / scaleX) & 0xFFFF;
                    dtdy = (s32) RNDF(-1023.0f / scaleY) & 0xFFFF;
                    k = (nx - i - 1) * tw;
                    xl = RNDI(k * scaleX + x1);
                    yl = (ny - j - 1) * th;
                    yl = RNDI(yl * scaleY + y1);
                    xh = RNDI((k + tileW) * scaleX + x1);
                    yh = RNDI(((ny - j - 1) * th + tileH) * scaleY + y1);
                    if (xh >= 0 && yh >= 0) {
                        gSPTextureRectangle(gfx++, xl << 2, yl << 2, xh << 2, yh << 2, 0, s, t, dsdx, dtdy);
                    }
                    break;
            }
        }
    }
    *gfxp = gfx;
}

void func_802606C4(Gfx **gdl, TexFile *file, s32 x0, s32 y0, s32 x1, s32 y1, s32 idx) {
    Gfx *gfx;
    TexEntry *e;
    s32 offset;
    u32 width;
    u8 *pal;
    u32 height;
    s32 mode;

    e = file->entries;
    e += idx;
    gfx = *gdl;
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, 0, 1);
    width = e->width;
    height = e->height;
    offset = e->offset;
    switch (e->type) {
        case 0x12:
            e++;
            if (e->type != 0x1A) {
                return;
            }
            pal = (u8 *) file + e->offset;
            gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            gDPLoadTLUT_pal16(gfx++, 0, pal);
            mode = 0;
            break;
        case 0x15:
            e++;
            if (e->type != 0x1A) {
                return;
            }
            pal = (u8 *) file + e->offset;
            gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            gDPLoadTLUT_pal256(gfx++, pal);
            mode = 1;
            break;
        case 0x16:
            gDPSetTextureLUT(gfx++, G_TT_NONE);
            mode = 2;
            break;
        case 0x19:
            gDPSetTextureLUT(gfx++, G_TT_NONE);
            mode = 3;
            break;
        default:
            return;
    }
    func_8025EC44(&gfx, x0, y0, x1, y1, mode, (u8 *) file + offset, width, height);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    *gdl = gfx;
}
