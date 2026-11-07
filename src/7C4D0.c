/*
 * main_code's 7C4D0, IDO -O3; it matches in us, eu and jp. Its data:
 * .rodata 0x20 (func_80261CD0's jump table), placed where the ROM has
 * it; no .data or .bss.
 *
 * func_80262DE8 draws a texture-file entry (CI4 with a 16-colour TLUT,
 * CI8 with a 256-colour one, RGBA16 or RGBA32) through func_80261CD0,
 * which draws an image as a grid of textured quads, loading each tile
 * with a one-texel border, placed by an alignment code and flipped per
 * its flip argument (7B2D0's drawer, not inlined). The code is the same
 * in every version.
 *
 * Both functions match. Levers in func_80261CD0:
 * - the vertices are written through vtx->, with vtx++ after each one
 *   (more uses of vtx: it outranks the GBI temporaries and gets $t4);
 * - x + tw and y + th are written out, not held in locals (two more
 *   coloured expressions put pz & 0xFFFF's temp at 140(sp)); pad0 and
 *   pad1 keep their frame words;
 * - per vertex tc[0] before tc[1] (register order), but on one line for
 *   vertices 0-2 (as1's store order), as are ob[0] and ob[1] of vertices
 *   1 and 2; vertex 3 writes tc[1] first and ob[1] last;
 * - tw = th = 56 (store order), y += th and x += tileW in the for heads,
 *   for (j = 0, y = 0; ...) (loop head order);
 * - ult = y decremented in a later block (cross-block copy propagation)
 *   gives y - 1 its late slot.
 */
#include "common.h"
#define F3DEX_GBI
#define _SHIFTL(v, s, w) ((unsigned int) (((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define _SHIFTR(v, s, w) ((unsigned int)(((unsigned int)(v) >> (s)) & ((0x01 << (w)) - 1)))
#include "ultralib/PR/gbi.h"

/* One entry of a texture file's table (12 bytes, after a 12-byte header). */
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

#define ROUND(x) ((x) >= 0.0 ? (x) + 0.5f : (x) - 0.5f)
#define TC(x) ((u16) ((s32) ROUND(x) << 6))

void func_80261CD0(Gfx **gfxp, Vtx *vtx, s32 mode, u8 *img, u32 width, u32 height, u8 align, u8 flip, s32 px, s32 py, s32 pz) {
    Gfx *gfx = *gfxp;
    s32 nx;
    s32 ny;
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    s32 pad0;
    s32 pad1;
    s32 uls;
    s32 ult;
    s32 ox;
    s32 oy;
    s32 lrs;
    s32 tw;
    s32 th;
    s32 tileW;
    s32 lrt;

    switch (mode) {
        case 0:
            tw = th = 56;
            break;
        case 1:
        case 2:
            tw = 56;
            th = 24;
            break;
        case 3:
            tw = 24;
            th = 24;
            break;
    }
    nx = width / tw;
    tileW = tw;
    ny = height / th;
    if (nx * tw < width) {
        nx++;
    }
    if (ny * th < height) {
        ny++;
    }
    switch (align) {
        case 0:
            ox = px - (width >> 1);
            oy = py - (height >> 1);
            break;
        case 1:
            ox = px;
            oy = py - height;
            break;
        case 2:
            ox = px - width;
            oy = py - height;
            break;
        case 3:
            ox = px;
            oy = py;
            break;
        case 4:
            ox = px - width;
            oy = py;
            break;
        default:
            ox = px - (width >> 1);
            oy = py - (height >> 1);
            break;
    }
    for (j = 0, y = 0; j < ny; j++, y += th) {
        tw = tileW;
        for (i = 0, x = 0; i < nx; i++, x += tileW) {
            if (width < x + tw) {
                tw = width - x;
            }
            if (height < y + th) {
                th = height - y;
            }
            if (tw < 0) {
                tw = 1;
            }
            if (th < 0) {
                th = 1;
            }
            uls = x;
            ult = y;
            lrs = x + tw;
            lrt = y + th;
            if (--uls < 0) {
                uls = 0;
            }
            if (++lrs >= width) {
                lrs = width - 2;
            }
            if (--ult < 0) {
                ult = 0;
            }
            if (++lrt >= height) {
                lrt = height - 2;
            }
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
            {
                s32 x0;
                s32 x1;
                s32 y0;
                s32 y1;
                s32 s0;
                s32 s1;
                s32 t0;
                s32 t1;

                switch (flip) {
                    case 0:
                        x0 = x;
                        y0 = height - (y + th);
                        x1 = x + tw;
                        y1 = height - y;
                        s0 = TC(x0 - 0.5);
                        t0 = TC(height - (y0 - 0.5));
                        s1 = TC(x1 - 0.5);
                        t1 = TC(height - (y1 - 0.5));
                        break;
                    case 1:
                        x0 = width - (x + tw);
                        y0 = height - (y + th);
                        x1 = width - x;
                        y1 = height - y;
                        s0 = TC(width - (x0 - 0.5));
                        t0 = TC(height - (y0 - 0.5));
                        s1 = TC(width - (x1 - 0.5));
                        t1 = TC(height - (y1 - 0.5));
                        break;
                    case 2:
                        x0 = x;
                        y0 = y;
                        x1 = x + tw;
                        y1 = y + th;
                        s0 = TC(x0 - 0.5);
                        t0 = TC(y0 - 0.5);
                        s1 = TC(x1 - 0.5);
                        t1 = TC(y1 - 0.5);
                        break;
                    case 3:
                        x0 = width - (x + tw);
                        y0 = y;
                        x1 = width - x;
                        y1 = y + th;
                        s0 = TC(width - (x0 - 0.5));
                        t0 = TC(y0 - 0.5);
                        s1 = TC(width - (x1 - 0.5));
                        t1 = TC(y1 - 0.5);
                        break;
                }
                vtx->v.ob[0] = (x0 + ox) & 0xFFFF;
                vtx->v.ob[1] = (y0 + oy) & 0xFFFF;
                vtx->v.ob[2] = pz & 0xFFFF;
                vtx->v.cn[3] = 0xFF;
                vtx->v.cn[2] = 0xFF;
                vtx->v.cn[1] = 0xFF;
                vtx->v.cn[0] = 0xFF;
                vtx->v.tc[0] = s0 & 0xFFFF; vtx->v.tc[1] = t0 & 0xFFFF;
                vtx->v.flag = 0;
                vtx++;
                vtx->v.ob[0] = (x1 + ox) & 0xFFFF; vtx->v.ob[1] = (y0 + oy) & 0xFFFF;
                vtx->v.ob[2] = pz & 0xFFFF;
                vtx->v.cn[3] = 0xFF;
                vtx->v.cn[2] = 0xFF;
                vtx->v.cn[1] = 0xFF;
                vtx->v.cn[0] = 0xFF;
                vtx->v.tc[0] = s1 & 0xFFFF; vtx->v.tc[1] = t0 & 0xFFFF;
                vtx->v.flag = 0;
                vtx++;
                vtx->v.ob[0] = (x1 + ox) & 0xFFFF; vtx->v.ob[1] = (y1 + oy) & 0xFFFF;
                vtx->v.ob[2] = pz & 0xFFFF;
                vtx->v.cn[3] = 0xFF;
                vtx->v.cn[2] = 0xFF;
                vtx->v.cn[1] = 0xFF;
                vtx->v.cn[0] = 0xFF;
                vtx->v.tc[0] = s1 & 0xFFFF; vtx->v.tc[1] = t1 & 0xFFFF;
                vtx->v.flag = 0;
                vtx++;
                vtx->v.ob[0] = (x0 + ox) & 0xFFFF;
                vtx->v.ob[2] = pz & 0xFFFF;
                vtx->v.cn[3] = 0xFF;
                vtx->v.cn[2] = 0xFF;
                vtx->v.cn[1] = 0xFF;
                vtx->v.cn[0] = 0xFF;
                vtx->v.tc[1] = t1 & 0xFFFF;
                vtx->v.tc[0] = s0 & 0xFFFF;
                vtx->v.flag = 0;
                vtx->v.ob[1] = (y1 + oy) & 0xFFFF;
                vtx++;
                gSPVertex(gfx++, vtx - 4, 4, 0);
                gSP1Triangle(gfx++, 0, 1, 2, 0);
                gSP1Triangle(gfx++, 0, 2, 3, 0);
            }
        }
    }
    *gfxp = gfx;
}

void func_80262DE8(Gfx **gdl, Vtx *vtx, u8 *base, s32 idx, u8 align, u8 flip, s32 px, s32 py, s32 pz) {
    Gfx *gfx = *gdl;
    TexEntry *e = &((TexFile *) base)->entries[idx];
    u32 width = e->width;
    u32 height = e->height;
    s32 offset = e->offset;
    u8 *pal;
    s32 dummy;
    s32 mode;

    switch (e->type) {
        case 0x12:
            e++;
            if (e->type != 0x1A) {
                return;
            }
            pal = (u8 *) ((u32) base + e->offset);
            gDPLoadTLUT_pal16(gfx++, 0, pal);
            mode = 0;
            break;
        case 0x15:
            e++;
            if (e->type != 0x1A) {
                return;
            }
            pal = (u8 *) ((u32) base + e->offset);
            gDPLoadTLUT_pal256(gfx++, pal);
            mode = 1;
            break;
        case 0x16:
            mode = 2;
            break;
        case 0x19:
            mode = 3;
            break;
        default:
            return;
    }
    func_80261CD0(&gfx, vtx, mode, base + offset, width, height, align, flip, px, py, pz);
    *gdl = gfx;
}
