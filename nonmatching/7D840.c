/*
 * NON_MATCHING: main_code's 7D840, complete: textured rectangles drawn
 * in tiles (a float and an integer variant: setup, wrap of the texture
 * window into up to four rectangles, then a tile loop of LoadTile and
 * TextureRectangle). Every function is emitted in the original's order,
 * with the original's stubs. Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 52, eu 52, jp 52
 *
 * func_80265274 matches: the wrap is the inlined static func_80264F98
 * (a switch writing through r++, called with info.width/height, which
 * gives the original's t1/t2 copies and its 8 bytes of frame), the loop
 * indexes rects[i], and the X dir block assigns scale before dir.
 *
 * Left: func_8026437C (size 0x710 and frame 344 match; 52 words of
 * register choice and schedule): `save` is loaded into v1 (original v0),
 * fw/fh live in $f2 (original $f0), and block 1 loads rects[0].b and
 * orders its multiplies and the info.y0 store differently. The dead
 * float-to-int conversions are kept by `if (func_80263904(fw)) {}` (costs
 * 8 bytes of frame, which the pads account for) and
 * `if (fh - (s32) fh && fh - (s32) fh) {}` (costs none).
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

typedef struct {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} RectF;

typedef struct {
    u32 a;
    u32 b;
    u32 c;
    u32 d;
} RectI;

typedef struct {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 y0;
    /* 0x08 */ f32 x1;
    /* 0x0C */ f32 y1;
    /* 0x10 */ f32 s0;
    /* 0x14 */ f32 t0;
    /* 0x18 */ f32 s1;
    /* 0x1C */ f32 t1;
    /* 0x20 */ s32 mode;
    /* 0x24 */ u8 *img;
    /* 0x28 */ f32 width;
    /* 0x2C */ f32 height;
    /* 0x30 */ f32 scaleX;
    /* 0x34 */ f32 scaleY;
    /* 0x38 */ f32 dirX;
    /* 0x3C */ f32 dirY;
} DrawF;

typedef struct {
    /* 0x00 */ u32 x0;
    /* 0x04 */ u32 y0;
    /* 0x08 */ u32 x1;
    /* 0x0C */ u32 y1;
    /* 0x10 */ u32 s0;
    /* 0x14 */ u32 t0;
    /* 0x18 */ u32 s1;
    /* 0x1C */ u32 t1;
    /* 0x20 */ s32 mode;
    /* 0x24 */ u8 *img;
    /* 0x28 */ u32 width;
    /* 0x2C */ u32 height;
    /* 0x30 */ f32 scaleX;
    /* 0x34 */ f32 scaleY;
    /* 0x38 */ s32 dirX;
    /* 0x3C */ s32 dirY;
} DrawI;

s32 func_802337EC(f32);
int func_802336E4(f32);
int func_80233650(f32, f32);

s32 D_802AD0D0;

static void func_80263040(Gfx **gfxp, s32 xl, s32 yl, s32 xh, s32 yh, s32 tile, s32 s, s32 t, s32 dsdx, s32 dtdy) {
    Gfx *gfx = *gfxp;

    switch ((xl < 0) | ((yl < 0) << 1) | ((xh < 0) << 2) | ((yh < 0) << 3)) {
        case 0:
            gSPTextureRectangle(gfx++, xl, yl, xh, yh, tile, s, t, dsdx, dtdy);
            break;
        case 15:
            break;
        default:
            gSPScisTextureRectangle(gfx++, xl, yl, xh, yh, tile, s, t, dsdx, dtdy);
            break;
    }
    *gfxp = gfx;
}

s32 func_802632DC(f32 x, u32 bits) {
    s32 neg;
    s32 frac;
    s32 ip;
    s32 i;

    if (func_802337EC(x) == -1) {
        neg = 1;
        x *= -1.0f;
    } else {
        neg = 0;
    }
    if (bits > 32) {
        bits = 32;
    }
    frac = 0;
    ip = (s32) x;
    x -= (f32) ip;
    for (i = 0; i < (s32) bits; i++) {
        x += x;
        frac <<= 1;
        if (x >= 1.0f) {
            frac |= 1;
            x -= 1.0f;
        }
    }
    return (neg ? -1 : 1) * ((ip << bits) | frac);
}

static void func_80263464(s32 uls, s32 mode, s32 ult, s32 lrs, s32 lrt, u8 *img, u32 width, Gfx **gfxp, s32 height) {
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

f32 func_80263904(f32 x) {
    return x - (f32) (s32) x;
}

s32 func_8026393C(s32 mode) {
    s32 n;

    switch (mode) {
        case 0:
            n = 16;
            break;
        case 1:
            n = 8;
            break;
        case 2:
            n = 4;
            break;
        case 3:
            n = 2;
            break;
        default:
            while (1) {}
    }
    return n;
}

s32 func_80263994(s32 mode) {
    s32 n;

    switch (mode) {
        case 0:
            n = 0x1000;
            break;
        case 1:
        case 2:
            n = 0x800;
            break;
        case 3:
            n = 0x400;
            break;
        default:
            while (1) {}
    }
    return n;
}

static void func_802639E4(Gfx **gfxp, DrawF *info) {
    s32 w;
    f32 span;
    s32 n;
    s32 c;
    s32 k;
    s32 r;
    s32 pad;
    s32 rows;
    f32 rf;
    f32 y;
    f32 h;
    f32 t0;
    f32 y2;
    s32 a;
    s32 flag;
    s32 b, cc, d, e, f, g, hh;

    w = (u32) info->width;
    span = info->t1 - info->t0;
    n = func_80263994(info->mode);
    c = n / 2;
    k = func_8026393C(info->mode) * 2;
    if (w < c) {
        c = w;
    }
    r = c % k;
    pad = r ? k - r : 0;
    c += pad;
    if (c < k) {
        c = k;
    }
    rows = n / c;
    if (rows > 0x400) {
        rows = 0x400;
    }
    rows -= 2;
    if (func_802336E4(func_80263904(info->t0)) == 0) {
        func_80263904(info->t0);
    }
    y = 0.0f;
    if (span > 0.0f) {
        flag = 1;
        rf = rows;
        do {
            h = rf;
            if (span <= y + rf) {
                h = span - y;
            }
            t0 = info->t0 + y;
            if (info->height - 1.0f <= t0 + h) {
                flag = 0;
            }
            func_80263464(0, info->mode, (s32) t0, (s32) (info->width - 1.0f), (s32) (t0 + h) + flag, info->img, (s32) info->width, gfxp, (s32) info->height);
            a = func_802632DC(info->x0, 2);
            b = func_802632DC(info->y0 + y * info->scaleY, 2);
            cc = func_802632DC(info->x1, 2);
            y2 = y + h;
            d = func_802632DC(info->y0 + y2 * info->scaleY, 2);
            e = func_802632DC(info->s0, 5);
            f = func_802632DC(info->t0 + y, 5);
            g = func_802632DC(info->dirX * (1.0f / info->scaleX), 10);
            hh = func_802632DC(info->dirY * (1.0f / info->scaleY), 10);
            func_80263040(gfxp, a & 0xFFFF, b & 0xFFFF, cc & 0xFFFF, d & 0xFFFF, 0, e & 0xFFF8, f & 0xFFF8, g & 0xFFFF, hh & 0xFFFF);
            y = y2;
        } while (y2 < span);
    }
}

f32 func_80263DC8(f32 a, f32 b) {
    if (func_802337EC(a) != -1) {
        if (func_802337EC(a - b) < 0) {
            return a;
        }
        return a - (f32) (s32) (a / b) * b;
    }
    return a + b;
}

static s32 func_80263E6C(f32 u, f32 v, f32 du, f32 dv, f32 w, f32 h, RectF *r) {
    f32 u0;
    f32 v0;
    f32 u1;
    f32 v1;
    f32 wm;
    f32 hm;
    s32 flags;
    s32 pad5;
    RectF *p;

    u0 = func_80263DC8(u, w);
    v0 = func_80263DC8(v, h);
    u1 = func_80263DC8(u0 + du, w + 1.0f);
    v1 = func_80263DC8(v0 + dv, h + 1.0f);
    if (w <= u0) {
        u0 = w - 0.001f;
    }
    flags = 0;
    wm = w - 0.001f;
    if (h <= v0) {
        v0 = h - 0.001f;
    }
    hm = h - 0.001f;
    if (w <= u1) {
        u1 = wm;
    }
    if (h <= v1) {
        v1 = hm;
    }
    p = r;
    r->a = u0;
    r->b = v0;
    r->c = u1;
    r->d = v1;
    if (u1 < u0) {
        r->c = wm;
    }
    if (v1 < v0) {
        r->d = hm;
    }
    r++;
    if (func_80233650(p->c, wm) && !func_802336E4(p->a)) {
        r->a = 0.0f;
        r->b = v0;
        r->c = du - (p->c - p->a);
        r->d = p->d;
        flags = 1;
    }
    r++;
    if (func_80233650(p->d, hm) && !func_802336E4(p->b)) {
        r->a = u0;
        r->b = 0.0f;
        r->c = u1;
        r->d = dv - (p->d - p->b);
        flags |= 2;
    }
    r++;
    if (flags == 3) {
        r->a = 0.0f;
        r->b = 0.0f;
        r->c = du - (p->c - p->a);
        r->d = dv - (p->d - p->b);
    }
    return flags;
}

s32 func_80264070(Gfx **gfxp, TexFile *file, s32 idx, DrawF *info) {
    Gfx *gfx;
    TexEntry *e;
    s32 offset;
    u32 width;
    u32 height;
    u8 *pal;
    s32 dummy;
    s32 mode;

    gfx = *gfxp;
    e = file->entries;
    e += idx;
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
                return 0;
            }
            pal = (u8 *) file + e->offset;
            gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            gDPLoadTLUT_pal16(gfx++, 0, pal);
            mode = 0;
            break;
        case 0x15:
            e++;
            if (e->type != 0x1A) {
                return 0;
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
            return 0;
    }
    *gfxp = gfx;
    info->width = width;
    info->height = height;
    info->mode = mode;
    info->img = (u8 *) file + offset;
    return 1;
}

static void func_80264A98(Gfx **gfxp, DrawI *info) {
    s32 n;
    s32 pad1;
    s32 du;
    s32 dv;
    s32 cols;
    s32 rows;
    s32 w;
    s32 h;
    s32 j;
    s32 i;
    s32 k;
    s32 r;
    s32 pad;
    s32 uls;
    s32 ult;
    s32 a, b, c, d, e, f, g, hh;

    du = info->s1 - info->s0;
    dv = info->t1 - info->t0;
    n = func_80263994(info->mode);
    cols = n / 2;
    k = func_8026393C(info->mode) * 2;
    if (du + 1 < cols) {
        cols = du;
    }
    cols++;
    r = cols % k;
    pad = r ? k - r : 0;
    cols += pad;
    if (cols != 0) {
        rows = n / cols;
    } else {
        rows = n;
    }
    if (dv < rows) {
        rows = dv;
    }
    if (dv > 0x400) {
        rows = 0x400;
    }
    cols--;
    rows--;
    for (i = 0; i < dv; i += h) {
        if (dv < i + rows) {
            h = dv - i;
        } else {
            h = rows;
        }
        if (h == 0) {
            h = 1;
        }
        for (j = 0; j < du; j += w) {
            w = (du < j + cols) ? du - j : cols;
            if (w == 0) {
                w = 1;
            }
            func_80263464(info->s0 + j, info->mode, info->t0 + i, info->s0 + j + w, info->t0 + i + h, info->img, info->width, gfxp, info->height);
            a = func_802632DC((f32) info->x0 + (f32) j * info->scaleX, 2);
            b = func_802632DC((f32) info->y0 + (f32) i * info->scaleY, 2);
            c = func_802632DC((f32) info->x0 + (f32) (j + w) * info->scaleX, 2);
            d = func_802632DC((f32) info->y0 + (f32) (i + h) * info->scaleY, 2);
            e = func_802632DC((f32) (info->s0 + j), 5);
            f = func_802632DC((f32) (info->t0 + i), 5);
            g = func_802632DC((f32) info->dirX * (1.0f / info->scaleX), 10);
            hh = func_802632DC((f32) info->dirY * (1.0f / info->scaleY), 10);
            func_80263040(gfxp, a & 0xFFFF, b & 0xFFFF, c & 0xFFFF, d & 0xFFFF, 0, e, f, g & 0xFFFF, hh & 0xFFFF);
        }
    }
}

s32 func_80264EF8(f32 x) {
    s32 a = (s32) x;

    if (a < (s32) (x + 0.5f)) {
        return a + 1;
    }
    return a;
}

u32 func_80264F68(u32 a, u32 b) {
    return a - (a / b) * b;
}

static void func_80264F98(RectI *r, u32 u, u32 v, u32 w, u32 h, u32 width, u32 height) {
    u32 u0;
    u32 v0;
    u32 u1;
    u32 v1;

    u0 = func_80264F68(u, width);
    v0 = func_80264F68(v, height);
    u1 = func_80264F68(u0 + w - 1, width);
    v1 = func_80264F68(v0 + h - 1, height);
    switch ((u1 < u0) | ((v1 < v0) << 1)) {
        case 0:
            r->a = u0;
            r->b = v0;
            r->c = u1;
            r->d = v1;
            break;
        case 1:
            r->a = u0;
            r->b = v0;
            r->c = width - 1;
            r->d = v1;
            r++;
            r->a = 0;
            r->b = v0;
            r->c = u1;
            r->d = v1;
            break;
        case 2:
            r->a = u0;
            r->b = v0;
            r->c = u1;
            r->d = height - 1;
            r++;
            r++;
            r->a = u0;
            r->b = 0;
            r->c = u1;
            r->d = v1;
            break;
        case 3:
            r->a = u0;
            r->b = v0;
            r->c = width - 1;
            r->d = height - 1;
            r++;
            r->a = 0;
            r->b = v0;
            r->c = u1;
            r->d = height - 1;
            r++;
            r->a = u0;
            r->b = 0;
            r->c = width - 1;
            r->d = v1;
            r++;
            r->a = 0;
            r->b = 0;
            r->c = u1;
            r->d = v1;
            break;
    }
}

s32 func_80264FA0(Gfx **gfxp, TexFile *file, s32 idx, DrawI *info) {
    Gfx *gfx;
    TexEntry *e;
    s32 offset;
    u32 width;
    u32 height;
    u8 *pal;
    s32 dummy;
    s32 mode;

    gfx = *gfxp;
    e = file->entries;
    e += idx;
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
                return 0;
            }
            pal = (u8 *) file + e->offset;
            gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            gDPLoadTLUT_pal16(gfx++, 0, pal);
            mode = 0;
            break;
        case 0x15:
            e++;
            if (e->type != 0x1A) {
                return 0;
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
            return 0;
    }
    *gfxp = gfx;
    info->width = width;
    info->height = height;
    info->mode = mode;
    info->img = (u8 *) file + offset;
    return 1;
}

static void func_80265C14(void) {
}

void func_80265C04(void) {
    D_802AD0D0 = 1;
}

void func_80265BFC(s32 a) {
}

u32 func_80265AD0(f32 x) {
    u32 a = (u32) x;

    if (a < (u32) (x + 0.5f)) {
        return a + 1;
    }
    return a;
}

f32 func_80265A50(f32 x) {
    s32 a = (s32) x;

    if (a < (s32) (x + 0.5f)) {
        return a + 1;
    }
    return a;
}

void func_80265274(Gfx **gfxp, TexFile *file, s32 x0, s32 y0, s32 x1, s32 y1, u32 u, u32 v, s32 w, s32 h, s32 idx) {
    Gfx *gfx;
    RectI rects[4] = { { -1, -1, -1, -1 }, { -1, -1, -1, -1 }, { -1, -1, -1, -1 }, { -1, -1, -1, -1 } };
    DrawI info;
    f32 dxt;
    f32 dyt;
    s32 i;

    if (x0 == x1 || w == 0 || y0 == y1 || h == 0) {
        return;
    }
    gfx = *gfxp;
    if (!func_80264FA0(&gfx, file, idx, &info)) {
        return;
    }
    func_80264F98(rects, u, v, w, h, info.width, info.height);
    if (info.width < w || info.height < h) {
        while (1) {}
    }
    if (x1 >= x0) {
        info.scaleX = (f32) (x1 - x0) / (f32) w;
        info.dirX = 1;
    } else {
        info.scaleX = (f32) (x0 - x1) / (f32) w;
        info.dirX = -1;
    }
    if (y1 >= y0) {
        info.dirY = 1;
        info.scaleY = (f32) (y1 - y0) / (f32) h;
    } else {
        info.dirY = -1;
        info.scaleY = (f32) (y0 - y1) / (f32) h;
    }
    dxt = (f32) (rects[0].c - rects[0].a) * (f32) info.dirX * info.scaleX;
    dyt = (f32) (rects[0].d - rects[0].b) * (f32) info.dirY * info.scaleY;
    for (i = 0; i < 4; i++) {
        if (rects[i].a != -1 && rects[i].b != -1 && rects[i].c != -1 && rects[i].d != -1) {
            info.x0 = ((i == 1 || i == 3) ? dxt : 0.0f) + (f32) x0;
            info.y0 = ((i == 2 || i == 3) ? dyt : 0.0f) + (f32) y0;
            info.x1 = func_80264EF8((f32) (rects[i].c - rects[i].a + 1) * (f32) info.dirX * info.scaleX) + info.x0;
            info.y1 = func_80264EF8((f32) (rects[i].d - rects[i].b + 1) * (f32) info.dirY * info.scaleY) + info.y0;
            info.s0 = rects[i].a;
            info.t0 = rects[i].b;
            info.s1 = rects[i].c;
            info.t1 = rects[i].d;
            func_80264A98(&gfx, &info);
        }
    }
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    *gfxp = gfx;
}

void func_80264A8C(s32 a) {
    D_802AD0D0 = a;
}

void func_8026437C(Gfx **gfxp, TexFile *file, f32 x0, f32 y0, f32 x1, f32 y1, f32 u, f32 v, f32 w, f32 h, s32 idx) {
    Gfx *gfx;
    f32 fw;
    f32 fh;
    s32 i;
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    s32 flags;
    s32 pad5;
    RectF rects[4] = { { 32768.0f, 32768.0f, 32768.0f, 32768.0f }, { 32768.0f, 32768.0f, 32768.0f, 32768.0f }, { 32768.0f, 32768.0f, 32768.0f, 32768.0f }, { 32768.0f, 32768.0f, 32768.0f, 32768.0f } };
    DrawF info;
    Gfx *save;

    gfx = *gfxp;
    if (func_80233650(x0, x1) || func_802336E4(w) || func_80233650(y0, y1) || func_802336E4(h)) {
        return;
    }
    if (!func_80264070(&gfx, file, idx, &info)) {
        return;
    }
    flags = func_80263E6C(u, v, w, h, info.width, info.height, rects);
    if (D_802AD0D0 == 0) {
        save = gfx;
        gDPSetTextureFilter(gfx++, G_TF_POINT);
    }
    if (info.width < w || info.height < h) {
        gDPSetTextureFilter(save, G_TF_POINT);
        while (1) {}
    }
    if (func_802337EC(x1 - x0) != -1) {
        info.scaleX = (x1 - x0) / w;
        info.dirX = 1;
    } else {
        info.scaleX = (x0 - x1) / w;
        info.dirX = -1;
    }
    if (func_802337EC(y1 - y0) != -1) {
        info.scaleY = (y1 - y0) / h;
        info.dirY = 1;
    } else {
        info.scaleY = (y0 - y1) / h;
        info.dirY = -1;
    }
    fw = (rects[0].c - rects[0].a) - 1.0f;
    if (func_802336E4(rects[0].c - (f32) (s32) rects[0].c) == 0) {
        if (func_80263904(fw)) {}
    }
    fh = (rects[0].d - rects[0].b) - 1.0f;
    if (func_802336E4(rects[0].d - (f32) (s32) rects[0].d) == 0) {
        if (fh - (s32) fh && fh - (s32) fh) {}
    }
    i = 0;
    if (rects[i].a != 32768.0f && rects[i].b != 32768.0f && rects[i].c != 32768.0f && rects[i].d != 32768.0f) {
        if (fh - (s32) fh && fh - (s32) fh) {}
        info.y0 = y0;
        info.x0 = x0;
        info.x1 = (rects[i].c - rects[i].a) * (info.dirX * info.scaleX) + x0;
        info.y1 = (rects[i].d - rects[i].b) * (info.dirY * info.scaleY) + y0;
        if (x1 < info.x1) {
            info.x1 = x1;
        }
        if (y1 < info.y1) {
            info.y1 = y1;
        }
        info.s0 = rects[i].a;
        info.t0 = rects[i].b;
        info.s1 = rects[i].c;
        info.t1 = rects[i].d;
        func_802639E4(&gfx, &info);
    }
    i++;
    if (rects[i].a != 32768.0f && rects[i].b != 32768.0f && rects[i].c != 32768.0f && rects[i].d != 32768.0f) {
        info.x0 = info.x1;
        info.y0 = y0;
        info.x1 = x1;
        info.s0 = rects[i].a;
        info.t0 = rects[i].b;
        info.s1 = rects[i].c;
        info.t1 = rects[i].d;
        func_802639E4(&gfx, &info);
    }
    i++;
    if (rects[i].a != 32768.0f && rects[i].b != 32768.0f && rects[i].c != 32768.0f && rects[i].d != 32768.0f) {
        if (flags == 3) {
            info.x1 = info.x0;
        }
        info.x0 = x0;
        info.y0 = info.y1;
        info.y1 = y1;
        info.s0 = rects[i].a;
        info.t0 = rects[i].b;
        info.s1 = rects[i].c;
        info.t1 = rects[i].d;
        func_802639E4(&gfx, &info);
    }
    i++;
    if (rects[i].a != 32768.0f && rects[i].b != 32768.0f && rects[i].c != 32768.0f && rects[i].d != 32768.0f) {
        info.x0 = info.x1;
        info.x1 = x1;
        info.s0 = rects[i].a;
        info.t0 = rects[i].b;
        info.s1 = rects[i].c;
        info.t1 = rects[i].d;
        func_802639E4(&gfx, &info);
    }
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    *gfxp = gfx;
}
