/*
 * NON_MATCHING: main_code's B11F0, complete first draft.
 * flags: -O3
 * (-O3: func_80297564 keeps its argument in t4, func_80296C10 in t0.)
 * differing words: us 31, eu 31, jp 31
 *
 * 22 of 25 functions match. Left: func_80296B3C (5, t1 for a2),
 * func_80296C10 (11, the original keeps y in s0) and func_80296D4C (15,
 * frame 0x98 with dw/dh spilled at 0x60/0x64). func_80297114 matched once
 * its entry pointer came from the getter func_80296BEC (inlined: its
 * parameter is a variable, coloured v1).
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

void func_80226E40(s32);
u16 *func_80226E4C(s32);
void func_8022946C(void *, s32, void *);
void func_8023903C(s32);
void func_8023AA78(s32);
void func_8023AE6C(s32, s32, s32);
void func_8023AED0(s32);
s32 func_80238A10(void *, s32, s32, s32, s32);
void func_80239094(void);
void func_8026D3AC(void *);
void *func_8026D4B0(void *, s32);
void func_80282144(s32, s32, s32, f32);
void func_8028A0B4(void);
void *func_8022A328(void *, s32, s32, s32, s32);
void free(void *);
void *malloc(s32);
void func_80227D50(s32, s32, s32, s32, s32);
void func_802276C8(s32);
void func_802276D4(s32);
void func_802276E0(s32, s32, s32);
void func_802276FC(s32);
void func_80227870(void);
void func_802346C8(f32, f32, f32);
void func_80234778(f32, f32, f32);
void func_802362B8(s32);
void func_80238EA8(s32);
void func_80239430(void);
s32 func_80239FF8(s32);
s32 *func_8023A840(void);
void func_80243DEC(s32);
void func_80261CD0(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_8026BEB0(void);
void func_8026C8E8(void);
void func_80277E1C(void);

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_80297564; /* size 0x8 */

/* the game object func_8022A6C4 and func_8022A328 make */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 unk30[6];
    /* 0x36 */ s16 unk36;
} UnkStruct_80297858;

/* a picture: its header, then 320x240 16-bit pixels */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u16 unk18[320 * 240];
} UnkStruct_80296D4C;

typedef struct {
    /* 0x000 */ void *unk0;
    /* 0x004 */ s32 unk4;
    /* 0x008 */ s32 unk8;
    /* 0x00C */ UnkStruct_80297858 *unkC;
    /* 0x010 */ u8 unk10[0xA00];
} UnkStruct_802B03C0; /* size 0xA10 */

extern void *D_1000000;
extern s32 D_802A2C70;
extern s32 D_802A2C74[];
extern s32 D_802A2C88[];
extern s32 D_802A2C9C[];
extern u8 D_802A2CB0[];
extern f32 D_802A4740;
extern f32 D_802A4744;
extern s32 D_802B03A0;
extern s32 D_802B03A4;
extern s32 D_802B03A8;
extern UnkStruct_802B03C0 *D_802B03B0[4];
extern UnkStruct_802B03C0 D_802B03C0[5];
extern s32 D_802AC5C0;
extern s32 D_802AC5D0;
extern s32 D_802B3614;
extern s32 D_802B3610;

void func_80297858(UnkStruct_80297858 *arg0, UnkStruct_80297564 **arg1);
void func_80297564(void *arg0, UnkStruct_80297564 **arg1);
void func_80297114(void);
void func_80297A34(void);
UnkStruct_802B03C0 *func_80296BEC(s32 arg0);

void func_80297ADC(void) {
    s32 *flags = func_8023A840();
    s32 i;

    *flags |= 4;
    func_8028A0B4();
    func_80277E1C();
    func_80243DEC(0);
    D_802B03A0 = 0;
    D_802B3614 = func_80238A10(func_80297A34, 0, 0, 0, 9);
    D_802B03A4 = 0;
    if (D_802A2C70 != 0) {
        *flags &= ~8;
    } else {
        *flags |= 8;
        D_802B03A8 = 0;
        for (i = 0; i < 4; i++) {
            D_802B03B0[i] = NULL;
            D_802B03C0[i].unk4 = 0x94;
            D_802B03C0[i].unk8 = 0x6F;
            D_802B03C0[i].unk0 = malloc(0x8058);
            D_802B03C0[i].unkC = NULL;
        }
        D_802B03C0[i].unk0 = malloc(0x25818);
        D_802B03C0[i].unkC = NULL;
    }
}

void func_80297A34(void) {
    while (1) {
        if ((func_80239FF8(0) & 0x1000) && !(D_802AC5D0 & 1)) {
            break;
        }
        func_80239094();
    }
    func_8023AA78(1);
    func_80226E40(1);
    D_802B03A0 = 1;
    func_8023AED0(0x20);
    func_8026C8E8();
    func_8023AE6C(0x20, 0x11, 4);
    D_802B3614 = -1;
    func_80239430();
}

void func_80297858(UnkStruct_80297858 *arg0, UnkStruct_80297564 **arg1) {
    Gfx *gfx = (Gfx *) *arg1;

    { UnkStruct_80297564 *g = (UnkStruct_80297564 *) gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFDF6FB; }
    { UnkStruct_80297564 *g = (UnkStruct_80297564 *) gfx++; g->w0 = 0xB900031D; g->w1 = 0x0F0A4000; }
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, &D_1000000);
    gDPSetFillColor(gfx++, 0x10001);
    gDPSetPrimColor(gfx++, 0, 0, (s32) arg0->unk20, (s32) arg0->unk24, (s32) arg0->unk28, 255);
    gDPFillRectangle(gfx++, (s32) arg0->unk10, (s32) arg0->unk14, (s32) arg0->unk18, (s32) arg0->unk1C);
    *arg1 = (UnkStruct_80297564 *) gfx;
}

UnkStruct_80297858 *func_80297804(void) {
    UnkStruct_80297858 *obj = func_8022A328(func_80297858, 0x3F, 1, 0, 0);

    if (obj != NULL) {
        obj->unkC |= 0x410;
        return obj;
    }
    return NULL;
}

void func_802977E4(void *arg0) {
    func_8022A1E8(arg0);
}

void func_80297564(void *arg0, UnkStruct_80297564 **arg1) {
    s32 i;
    UnkStruct_802B03C0 *e;
    UnkStruct_80297564 *gfx = *arg1;

    if (D_802B03A8 != 0) {
        for (i = 0; i < 4; i++) {
            if (arg0 == D_802B03B0[i]->unkC) {
                e = D_802B03B0[i];
                break;
            }
        }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xBA001402; g->w1 = 0; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x552078; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xB6000000; g->w1 = 0x2000; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xB7000000; g->w1 = 0x20205; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xBB000001; g->w1 = 0x80008000; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xBA000C02; g->w1 = 0x2000; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF87C; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0x80000; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xBA001102; g->w1 = 0; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xBA001001; g->w1 = 0; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xBA000903; g->w1 = 0xC00; }
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xBC000806; g->w1 = 0; }
        func_80261CD0(&gfx, e->unk10, 2, (s32) e->unk0, e->unk4, e->unk8, 0, 0, 0, 0, 0);
        { UnkStruct_80297564 *g = gfx++; g->w0 = 0xB7000000; g->w1 = 0x2000; }
        *arg1 = gfx;
    }
}

void func_8029750C(s32 arg0) {
    D_802B3610 = 1;
    func_8023AA78(1);
    func_8023AED0(10);
    func_80238A10(func_80297114, 0, 0, 0, 0x150);
}

void func_802974E0(void) {
    func_80282144(0, 0, 0, 0.0f);
}

s32 func_802974D0(void) {
    return D_802B3610;
}

s32 func_802974C0(void) {
    return D_802B03A0;
}

void func_8029738C(void);

void func_80297498(void) {
    D_802B03A0 = 1;
    func_8029738C();
}

void func_802972D0(void);

void func_8029738C(void) {
    s32 *flags = func_8023A840();

    func_80243DEC(0);
    if (D_802B03A0 != 0) {
        func_8026C8E8();
        func_8026BEB0();
        *flags &= ~0xC;
        func_8028A0B4();
        if (D_802A2C70 == 0) {
            func_802972D0();
        }
        if (D_802B3614 != -1) {
            func_80238EA8(D_802B3614);
        }
        func_8023AA78(0);
        func_80227D50(D_802AC5C0, 8, 6, 0x130, 0xE4);
        func_802276D4(0);
        func_80282144(0, 0, 0, 0.0f);
        if (D_802A2C70 == 0) {
            D_802A2C70 = 1;
        } else {
            D_802A2C70 = 0;
        }
    }
}

void func_80297240(UnkStruct_802B03C0 *arg0);

void func_802972D0(void) {
    UnkStruct_802B03C0 **p;
    s32 i;

    for (p = D_802B03B0; p < D_802B03B0 + 4; p++) {
        if (*p != NULL) {
            func_80297240(*p);
        }
    }
    for (i = 0; i < 4; i++) {
        free(D_802B03C0[i].unk0);
        D_802B03C0[i].unk0 = NULL;
    }
    if (D_802B03C0[i].unkC != NULL) {
        func_8026D3AC(D_802B03C0[i].unkC);
        D_802B03C0[i].unkC = NULL;
    }
    if (D_802B03C0[i].unk0 != NULL) {
        free(D_802B03C0[i].unk0);
        D_802B03C0[i].unk0 = NULL;
    }
}

void func_80297240(UnkStruct_802B03C0 *arg0) {
    s32 i;

    if (arg0->unkC != NULL) {
        for (i = 0; arg0 != D_802B03B0[i]; i++) {
        }
        if (i < 4) {
            D_802B03B0[i] = NULL;
            func_8026D3AC(arg0->unkC);
            arg0->unkC = NULL;
            D_802B03A8--;
        }
    }
}

s32 func_80296B3C(UnkStruct_802B03C0 *arg0);
void func_80296D4C(u16 *arg0, UnkStruct_80296D4C *arg1, UnkStruct_80297858 **arg2);

void func_80297114(void) {
    UnkStruct_802B03C0 *e;

    func_80296D4C(D_802B03C0[D_802B03A4].unk0, D_802B03C0[4].unk0, &D_802B03C0[4].unkC);
    func_802362B8(0x10);
    func_802346C8(0.0f, 0.0f, 0.0f);
    func_80234778(0.0f, 0.0f, 1000.0f);
    e = func_80296BEC(D_802B03A4);
    func_80296B3C(e);
    e->unkC->unk10 = 0.0f;
    e->unkC->unk14 = D_802A4740;
    e->unkC->unk18 = D_802A4744;
    e->unkC->unkC |= 0x81;
    D_802B03A4++;
    func_8023AA78(0);
    D_802B3610 = 0;
    func_80239430();
}

void func_80296C10(u16 *arg0, s32 x, s32 y, s32 w, s32 h);

void func_80296D4C(u16 *arg0, UnkStruct_80296D4C *arg1, UnkStruct_80297858 **arg2) {
    f32 x = 8.0f;
    f32 y = 6.0f;
    f32 w = 304.0f;
    f32 h = 228.0f;
    f32 dx;
    f32 dy;
    f32 dw;
    f32 dh;
    UnkStruct_80297858 *obj;
    u16 *src;
    u16 *dst;
    s32 i;

    func_80226E40(0);
    func_802276FC(0);
    func_80227870();
    func_8023903C(10);
    src = func_80226E4C(1);
    arg1->unk4 = 1;
    arg1->unk0 = 0x36340037;
    arg1->unk8 = 4;
    arg1->unk9 = 4;
    arg1->unkA = 4;
    arg1->unkB = 4;
    arg1->unkC = 0x16;
    arg1->unk10 = 320;
    arg1->unk12 = 240;
    arg1->unk14 = 0x18;
    dst = arg1->unk18;
    for (i = 0; i < 320 * 240; i++) {
        *dst++ = *src++ | 1;
    }
    func_80297D60(arg1, 0x25818);
    obj = func_8022A6C4(arg1, 0x9C);
    obj->unk36 = -1;
    obj->unkC |= 0x80;
    obj->unk20 = 8.0f;
    obj->unk24 = 6.0f;
    obj->unk28 = 304.0f;
    obj->unk2C = 228.0f;
    *arg2 = obj;
    func_80226E40(1);
    func_802276FC(1);
    func_802276E0(0, 0, 0);
    func_802276D4(1);
    func_802276C8(0x40);
    dx = (86.0f - x) / 40.0f;
    dy = (72.0f - y) / 40.0f;
    dw = (148.0f - w) / 40.0f;
    dh = (111.0f - h) / 40.0f;
    for (i = 0; i < 40; i++) {
        func_80227D50(D_802AC5C0, (s32) x + 2, (s32) y + 2, (s32) w - 2, (s32) h - 2);
        obj->unk10 = x;
        obj->unk14 = y;
        obj->unk18 = x + w;
        obj->unk1C = y + h;
        x += dx;
        y += dy;
        w += dw;
        h += dh;
        func_80239094();
    }
    func_80282144(0, 0, 0, 100.0f);
    func_80227D50(D_802AC5C0, 8, 6, 0x130, 0xE4);
    func_8023903C(4);
    func_802276D4(0);
    func_80296C10(arg0, 0x56, 0x48, 0x94, 0x6F);
}

void func_80296C10(u16 *arg0, s32 x, s32 y, s32 w, s32 h) {
    u16 *start;
    u16 *src;
    s32 i;
    s32 j;

    func_80226E40(0);
    func_8023903C(8);
    src = func_80226E4C(1);
    start = arg0;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            *arg0++ = src[x + i + (y + j) * 320] | 1;
        }
    }
    func_80297D60(start, w * 2 * h);
    func_80226E40(1);
}

UnkStruct_802B03C0 *func_80296BEC(s32 arg0) {
    return &D_802B03C0[arg0];
}

s32 func_80296B3C(UnkStruct_802B03C0 *arg0) {
    s32 i;

    if ((arg0->unkC = func_8026D4B0(func_80297564, 0)) != NULL) {
        for (i = 0; D_802B03B0[i] != NULL; i++) {
        }
        func_8022946C(arg0->unkC, 0x44 - i, arg0);
        D_802B03A8++;
        D_802B03B0[i] = arg0;
        return 1;
    }
    return 0;
}

void func_80296AD8(s32 arg0) {
    s32 i;

    for (i = 0; i < arg0; i++) {
        if (D_802B03A0 == 0) {
            func_80239094();
        }
    }
}

void func_80296A80(void) {
    func_8023AE6C(D_802A2C74[D_802B03A4], D_802A2C88[D_802B03A4], D_802A2C9C[D_802B03A4]);
    func_8028A0B4();
}

void func_80296A34(void) {
    if (D_802A2C70 == 0) {
        func_8023AE6C(0x1B, 0x10, 0);
    } else {
        func_8023AE6C(0x1A, 0x10, 4);
    }
}

s32 func_80296A24(void) {
    return D_802A2C70;
}

void func_80296A18(s32 arg0) {
    D_802A2C70 = arg0;
}

void func_802969F0(void) {
    func_80297D30(49, D_802A2CB0);
}
