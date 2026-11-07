/*
 * NON_MATCHING: main_code's 7B2D0, complete (no data): func_80260AD8 draws
 * a texture-file entry (CI4 with a 16-colour TLUT, CI8 with a 256-colour
 * one, or two direct formats) as a grid of textured quads, loading each
 * tile with a one-texel border, flipped per its last argument.
 * func_80260AD0 is the 8-byte stub IDO -O3 leaves of the inlined static
 * drawer. Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING
 * drafts").
 * flags: -O3
 * differing words: us 98, eu 98, jp 98
 *
 * func_80260AD8 has the original's size (0x11EC) and frame (0x210); the
 * rest is colouring and slots. What still differs in us:
 * - the entry pointer: the original reuses $v1 for e++ (lw t1,12(v1);
 *   addiu v1,v1,12); this puts e in $t1 and the type in $t2.
 * - colouring: vtx in $t4 and lrt in $t3 (the original has them the other
 *   way round).
 * - switch (mode) case 0 stores th before tw (as in 7C4D0).
 * - the flip block's homes sit 4 bytes low (x0 at 236(sp), original
 *   240(sp)): the original has one word less in the scopes before the
 *   flip block (the GBI macros' _g homes) and one more after it. The
 *   block declares x0 last so the other seven line up with the original.
 * The vertex stores' cn[1] = cn[0] chain is there for uopt: it splits
 * the store run into blocks by size, and the chain moves the split so the
 * gSPVertex temporaries keep the original's priority.
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

static void func_80260AD0(Gfx **gfxp, Vtx *vtx, s32 mode, u8 *img, u32 width, u32 height, u8 flip) {
    Gfx *gfx = *gfxp;
    s32 nx;
    s32 ny;
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    s32 xend;
    s32 yend;
    s32 uls;
    s32 ult;
    s32 tw;
    s32 th;
    s32 tileW;
    s32 lrs;
    s32 lrt;

    switch (mode) {
        case 0:
            tw = 56;
            th = 56;
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
    y = 0;
    for (j = 0; j < ny; j++) {
        tw = tileW;
        for (i = 0, x = 0; i < nx; i++) {
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
            xend = x + tw;
            yend = y + th;
            uls = x;
            ult = y;
            lrs = xend;
            lrt = yend;
            if (--uls < 0) {
                uls = 0;
            }
            if (++lrs >= width) {
                lrs = width - 1;
            }
            if (--ult < 0) {
                ult = 0;
            }
            if (++lrt >= height) {
                lrt = height - 1;
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
                s32 x1;
                s32 y0;
                s32 y1;
                s32 s0;
                s32 s1;
                s32 t0;
                s32 t1;
                s32 x0;

                switch (flip) {
                    case 0:
                        x0 = x;
                        y0 = height - yend;
                        x1 = xend;
                        y1 = height - y;
                        s0 = TC(x0 - 0.5);
                        t0 = TC(height - (y0 - 0.5));
                        s1 = TC(x1 - 0.5);
                        t1 = TC(height - (y1 - 0.5));
                        break;
                    case 1:
                        x0 = width - xend;
                        y0 = height - yend;
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
                        x1 = xend;
                        y1 = yend;
                        s0 = TC(x0 - 0.5);
                        t0 = TC(y0 - 0.5);
                        s1 = TC(x1 - 0.5);
                        t1 = TC(y1 - 0.5);
                        break;
                    case 3:
                        x0 = width - xend;
                        y0 = y;
                        x1 = width - x;
                        y1 = yend;
                        s0 = TC(width - (x0 - 0.5));
                        t0 = TC(y0 - 0.5);
                        s1 = TC(width - (x1 - 0.5));
                        t1 = TC(y1 - 0.5);
                        break;
                }
                vtx[0].v.ob[0] = x0 & 0xFFFF;
                vtx[0].v.ob[1] = y0 & 0xFFFF;
                vtx[0].v.tc[0] = s0 & 0xFFFF;
                vtx[0].v.tc[1] = t0 & 0xFFFF;
                vtx[1].v.ob[1] = y0 & 0xFFFF;
                vtx[1].v.tc[1] = t0 & 0xFFFF;
                vtx[3].v.ob[0] = x0 & 0xFFFF;
                vtx[3].v.tc[0] = s0 & 0xFFFF;
                vtx[0].v.ob[2] = 0;
                vtx[0].v.flag = 0;
                vtx[0].v.cn[0] = 0xFF;
                vtx[0].v.cn[1] = 0xFF;
                vtx[0].v.cn[2] = 0xFF;
                vtx[0].v.cn[3] = 0xFF;
                vtx[1].v.ob[0] = x1 & 0xFFFF;
                vtx[1].v.ob[2] = 0;
                vtx[1].v.flag = 0;
                vtx[1].v.tc[0] = s1 & 0xFFFF;
                vtx[1].v.cn[0] = 0xFF;
                vtx[1].v.cn[1] = 0xFF;
                vtx[1].v.cn[2] = 0xFF;
                vtx[1].v.cn[3] = 0xFF;
                vtx[2].v.ob[0] = x1 & 0xFFFF;
                vtx[2].v.ob[1] = y1 & 0xFFFF;
                vtx[2].v.ob[2] = 0;
                vtx[2].v.flag = 0;
                vtx[2].v.tc[0] = s1 & 0xFFFF;
                vtx[2].v.tc[1] = t1 & 0xFFFF;
                vtx[2].v.cn[1] = vtx[2].v.cn[0] = 0xFF;
                vtx[2].v.cn[2] = 0xFF;
                vtx[2].v.cn[3] = 0xFF;
                vtx[3].v.ob[1] = y1 & 0xFFFF;
                vtx[3].v.ob[2] = 0;
                vtx[3].v.flag = 0;
                vtx[3].v.tc[1] = t1 & 0xFFFF;
                vtx[3].v.cn[0] = 0xFF;
                vtx[3].v.cn[1] = 0xFF;
                vtx[3].v.cn[2] = 0xFF;
                vtx[3].v.cn[3] = 0xFF;
                vtx += 4;
                gSPVertex(gfx++, vtx - 4, 4, 0);
                gSP1Triangle(gfx++, 0, 1, 2, 0);
                gSP1Triangle(gfx++, 0, 2, 3, 0);
            }
            x += tileW;
        }
        y += th;
    }
    *gfxp = gfx;
}

void func_80260AD8(Gfx **gdl, Vtx *vtx, TexFile *base, s32 idx, u8 flip) {
    Gfx *gfx;
    TexEntry *e;
    s32 offset;
    u32 width;
    u32 height;
    u8 *pal;
    s32 dummy2;
    s32 mode;

    e = &base->entries[idx];
    gfx = *gdl;
    offset = e->offset;
    width = e->width;
    height = e->height;
    switch (e->type) {
        case 0x12:
            e++;
            if (e->type != 0x1A) {
                return;
            }
            pal = (u8 *) base + e->offset;
            gDPLoadTLUT_pal16(gfx++, 0, pal);
            mode = 0;
            break;
        case 0x15:
            e++;
            if (e->type != 0x1A) {
                return;
            }
            pal = (u8 *) base + e->offset;
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
    func_80260AD0(&gfx, vtx, mode, (u8 *) base + offset, width, height, flip);
    *gdl = gfx;
}
