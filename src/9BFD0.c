#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10[0x24];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
} UnkStruct_802A1A80;

/* A display list command (gbi.h's Gfx, as two words).  The commands are
 * written as gbi.h's macros expand, one per line; the colour's first
 * component is masked like the others (_SHIFTL), which sets its
 * registers. */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_80281FA0; /* size 0x8 */

void *func_8022A328(void *, s32, s32, s32, s32);
s32 func_80238A10(void *, s32, s32, s32, s32);
void func_80238EA8(s32);
void func_8023903C(s32);
void func_80239094(void);
void func_80239430(void);
void func_802817F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void (*arg5)(void));
void func_80281B10(void);
static void func_80281FA0(s32 arg0, UnkStruct_80281FA0 **arg1);
void func_80281C00(void);
void func_80281CF0(void);
void func_80281DD8(void);
void func_80281E70(void);
void func_80281F0C(void);
void func_80282034(s32 arg0, UnkStruct_80281FA0 **arg1);
void func_802820BC(s32 arg0, UnkStruct_80281FA0 **arg1);

extern u8 D_1000000[];
extern UnkStruct_802A1A80 *D_802A1A80;
extern UnkStruct_802A1A80 *D_802A1A84;
extern u8 D_802A1A88[];
extern s32 D_802AC5CC;
extern s32 D_802B0230;
extern s32 D_802B0234;
extern s32 D_802B0238;
extern s32 D_802B023C;
extern s32 D_802B0240;
extern s32 D_802B0244;
extern s32 D_802B0248;
extern s32 D_802B024C;
extern s32 D_802B0250;

void func_80282144(s32 arg0, s32 arg1, s32 arg2, f32 arg3) {
    f32 alpha;

    if (D_802A1A84 == NULL) {
        D_802A1A84 = func_8022A328(func_802820BC, 0x9B, 1, 0, 0);
        D_802A1A84->unkC |= 0x90;
    } else if (arg3 == 0.0f) {
        func_8022A1E8(D_802A1A84);
        D_802A1A84 = NULL;
        return;
    }
    alpha = (255.0f * arg3) / 100.0f;
    if (alpha >= 0.0f) {
        alpha += 0.5f;
    } else {
        alpha -= 0.5f;
    }
    D_802A1A84->unk36 = alpha;
    if (D_802A1A84->unk36 == 0xFF) {
        D_802A1A84->unk36 = -1;
    }
    D_802B0244 = arg0;
    D_802B0248 = arg1;
    D_802B024C = arg2;
}

void func_802820BC(s32 arg0, UnkStruct_80281FA0 **arg1) {
    UnkStruct_80281FA0 *gfx = *arg1;

    { UnkStruct_80281FA0 *g = gfx++; g->w0 = 0xFA000000; g->w1 = ((D_802B0244 & 0xFF) << 24) | ((D_802B0248 & 0xFF) << 16) | ((D_802B024C & 0xFF) << 8) | 0xFF; }
    func_80281FA0(arg0, &gfx);
    *arg1 = gfx;
}

void func_80282034(s32 arg0, UnkStruct_80281FA0 **arg1) {
    UnkStruct_80281FA0 *gfx = *arg1;

    { UnkStruct_80281FA0 *g = gfx++; g->w0 = 0xFA000000; g->w1 = ((D_802B0230 & 0xFF) << 24) | ((D_802B0234 & 0xFF) << 16) | ((D_802B0238 & 0xFF) << 8) | 0xFF; }
    func_80281FA0(arg0, &gfx);
    *arg1 = gfx;
}

/* static, and taking the callers' unused arg0: IDO -O3 passes that in its
 * home slot (the callers' `sw $a0, 0($sp)`) and the display list in $a0,
 * and the callers keep their arg1 in $t2 across the call. */
static void func_80281FA0(s32 arg0, UnkStruct_80281FA0 **arg1) {
    UnkStruct_80281FA0 *gfx = *arg1;

    { UnkStruct_80281FA0 *g = gfx++; g->w0 = 0xB9000401; g->w1 = 0; }
    { UnkStruct_80281FA0 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFDF6FB; }
    { UnkStruct_80281FA0 *g = gfx++; g->w0 = 0xFF10013F; g->w1 = (u32) D_1000000; }
    { UnkStruct_80281FA0 *g = gfx++; g->w0 = 0xF7000000; g->w1 = 0x10001; }
    { UnkStruct_80281FA0 *g = gfx++; g->w0 = 0xF64FC3BC; g->w1 = 0; }
    { UnkStruct_80281FA0 *g = gfx++; g->w0 = 0xB9000401; g->w1 = 0x10; }
    *arg1 = gfx;
}

void func_80281F0C(void) {
    while (D_802A1A80->unk36 >= 0) {
        func_8023903C(D_802B023C);
        D_802A1A80->unk36 -= 8;
    }
    func_8022A1E8(D_802A1A80);
    D_802A1A80 = NULL;
    D_802B0240 = 0;
    func_80239430();
}

void func_80281E70(void) {
    while (D_802A1A80->unk36 < 0xFF) {
        func_8023903C(D_802B023C);
        D_802A1A80->unk36 += 8;
    }
    func_8022A1E8(D_802A1A80);
    D_802A1A80 = NULL;
    D_802B0240 = 0;
    func_80239430();
}

void func_80281DD8(void) {
    while (D_802A1A80->unk36 < 0xFF) {
        func_8023903C(D_802B023C);
        D_802A1A80->unk36 += 8;
    }
    D_802A1A80->unk36 = -1;
    D_802B0240 = 0;
    func_80239430();
}

void func_80281CF0(void) {
    s32 i;
    f32 alpha;
    f32 step;

    alpha = D_802A1A80->unk36;
    step = alpha / D_802B023C;
    for (i = 0; i < D_802B023C; i++) {
        D_802A1A80->unk36 = alpha;
        alpha -= step;
        func_80239094();
    }
    func_8022A1E8(D_802A1A80);
    D_802A1A80 = NULL;
    D_802B0240 = 0;
    func_80239430();
}

void func_80281C00(void) {
    s32 i;
    f32 alpha;
    f32 step;

    step = 255.0f / D_802B023C;
    alpha = D_802A1A80->unk36;
    for (i = 0; i < D_802B023C; i++) {
        D_802A1A80->unk36 = alpha;
        alpha += step;
        func_80239094();
    }
    func_8022A1E8(D_802A1A80);
    D_802A1A80 = NULL;
    D_802B0240 = 0;
    func_80239430();
}

void func_80281B10(void) {
    s32 i;
    f32 alpha;
    f32 step;

    step = 255.0f / D_802B023C;
    alpha = D_802A1A80->unk36;
    for (i = 0; i < D_802B023C; i++) {
        D_802A1A80->unk36 = alpha;
        alpha += step;
        func_80239094();
    }
    D_802A1A80->unk36 = -1;
    D_802B0240 = 0;
    func_80239430();
}

void func_80281AE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_802817F8(arg0, arg1, arg2, arg3, 0xFF, func_80281CF0);
}

void func_80281AB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_802817F8(arg0, arg1, arg2, arg3, 0, func_80281C00);
}

void func_80281A88(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_802817F8(arg0, arg1, arg2, arg3, 0, func_80281B10);
}

void func_80281A40(void) {
    while (D_802B0240 != 0) {
        func_80239094();
    }
}

void func_80281A00(s32 arg0) {
    func_802817F8(0, 0, 0, arg0, 0xFF, func_80281F0C);
}

void func_802819D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_802817F8(arg0, arg1, arg2, arg3, 0xFF, func_80281F0C);
}

void func_80281994(s32 arg0) {
    func_802817F8(0, 0, 0, arg0, 0, func_80281E70);
}

void func_80281968(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_802817F8(arg0, arg1, arg2, arg3, 0, func_80281E70);
}

void func_8028192C(s32 arg0) {
    func_802817F8(0, 0, 0, arg0, 0, func_80281DD8);
}

void func_80281900(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_802817F8(arg0, arg1, arg2, arg3, 0, func_80281DD8);
}

void func_802817F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void (*arg5)(void)) {
    if (D_802B0240 != 0) {
        func_80238EA8(D_802B0250);
    }
    D_802B0240 = 1;
    if (D_802A1A80 == NULL) {
        D_802A1A80 = func_8022A328(func_80282034, 0x9F, 1, 0, 0);
        D_802A1A80->unkC |= 0x90;
        D_802A1A80->unk34 = D_802AC5CC;
    }
    D_802A1A80->unk36 = arg4;
    D_802B0230 = arg0;
    D_802B0234 = arg1;
    D_802B0238 = arg2;
    D_802B023C = arg3;
    D_802B0250 = func_80238A10(arg5, 0, 0, 0, 0x400);
}

void func_802817D0(void) {
    func_80297D30(32, D_802A1A88);
}
