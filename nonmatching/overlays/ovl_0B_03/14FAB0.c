/*
 * NON_MATCHING: ovl_0B_03's game object (a four-player set-up screen:
 * three rows of animated background pieces, the players' bombers and
 * their option boxes, driven by one big task, 8004386C), complete: every
 * function and its data (.data 0x770 with the big task's two local cursor
 * tables, .bss 0x1140, as the original's sizes). Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 3446, jp 4082
 *
 * A first draft from m2c (wk/ in scratch/0B_03/ of the main checkout has
 * the scripts): functions written last to first. The statics the original
 * passes arguments in its callers' saved registers (80043134, 80043428,
 * 80043464: n in $s2; 80043340: n in $s4, the model in $s5; 8004368C:
 * $s1/$s2; 800464B0: n in $s2; 80043234: the scale in $f20; 80043170: the
 * scale in $f12) take ordinary parameters here, their values read from the
 * asm at each call; 800434BC, 800436EC, 800464B0 and 80046510 are
 * rewritten (m2c stepped struct pointers by bytes). 8004386C is m2c's
 * output with its float-to-unsigned conversions, unset-register reads and
 * the table entries it named as symbols of their own (80048D2C,
 * 80048DA4-80048DEC, 80048E80, 80048E98, 80048EAC-80048EE8, 8004918E)
 * fixed; its gotos and its M2C_FIELD byte offsets are m2c's and only
 * partly checked. The ZeroJump stubs are declared as other drafts declare
 * the same codes. The .bss's unreferenced words (800492E0, 8004930C,
 * 8004A33C, 8004A3FC, 8004A418) are arrays, not yet kept in place.
 *
 * What still differs in us (words): 80043010 21, 80043134 21, 80043170 36,
 * 80043234 15, 800432A0 26, 800432F0 26, 80043340 45, 800433BC 29,
 * 80043428 21, 80043464 28, 800434BC 130, 8004368C 32, 800436EC 85,
 * 8004386C 2758, 800464B0 30, 80046510 156, 80046850 23, 80046918 37,
 * 800469B4/80046C20 73 each, 80046AE8/80046D54 73 each, 80046E8C 57,
 * 80046F78 59, 80047064 68, 80047188 2 (the stub after it isn't drafted),
 * 80047198 79. 80043060, 800431FC, 80043834, 8004730C-800473E4 and the
 * end stubs (800473FC on) match. None of the twins simil_all finds
 * (ovl_0B_02, 17_09, 0B_07) was ported yet; the statics aren't `static`.
 */

#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

typedef struct Inner Inner;

typedef struct {
    u32 w0;
    u32 w1;
} Gfx_ovl0A_01;

/* A text label: the string, its place, its scale and the handle
 * func_ovl0B_03_80048748 returns for it. */
typedef struct {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} Label_ovl0B_03;

/* A box: its centre, its size, its scale and the object drawing it. */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ UnkStructA_40 *unk14;
} Box_ovl0B_03;

/* A model: what func_ovl0B_03_80047E98 makes, where, and the result. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ UnkStructA_40 *unk10;
} Model_ovl0B_03;

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} Pair_ovl0B_03;

/* A menu's cursor positions (the big task's local tables). */
typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} MenuPos_ovl0B_03;

/* An animated piece of the background: its object, the frames left and
 * the step in D_ovl0B_03_80049104. */
typedef struct {
    /* 0x0 */ UnkStructA_40 *unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Anim_ovl0B_03;

#define WRAP_ovl0B_03(x) ((x) >= 360.0f ? (x) - 360.0f : (x) < 0.0f ? (x) + 360.0f : (x))
#define GFX_W_ovl0B_03(pkt, a, b) { Gfx_ovl0A_01 *_g = (pkt); _g->w0 = (a); _g->w1 = (b); }

void func_ovl0B_03_800478B0(s32, s32, s32);
s32 func_ovl0B_03_800478B8(void);
s32 *func_ovl0B_03_80047908(void);
UnkStructB *func_ovl0B_03_80047938(void);
void func_ovl0B_03_80047960(s32, s32, s32);
UnkStructA_40 *func_ovl0B_03_80047E98(s32, s32);
void func_ovl0B_03_80047EA0(UnkStructA_40 *);
void func_ovl0B_03_80047EC0(UnkStructA_40 *, s32);
void func_ovl0B_03_80047EC8(UnkStructA_40 *, s32, s32, s32);
void func_ovl0B_03_80047ED8(UnkStructA_40 *, s32);
void func_ovl0B_03_80047EE0(UnkStructA_40 *, s32, s32);
Inner *func_ovl0B_03_80047F18(void (*)(s32, Gfx_ovl0A_01 **), s32);
s32 func_ovl0B_03_80047F28(UnkStructA_40 *, s32);
void func_ovl0B_03_80047FD8(s32);
void func_ovl0B_03_80047FE8(s32);
void func_ovl0B_03_80047FF8(f32, f32, f32);
void func_ovl0B_03_80048018(f32, f32, f32);
void func_ovl0B_03_80048020(f32 *, f32 *, f32 *);
void func_ovl0B_03_80048060(s32);
s32 func_ovl0B_03_80048308(void (*)(void), void *, s32, s32, s32);
void func_ovl0B_03_80048318(void);
void func_ovl0B_03_80048328(s32);
void func_ovl0B_03_80048350(void);
s32 func_ovl0B_03_800483B8();
s32 func_ovl0B_03_800483C8();
s32 func_ovl0B_03_800483D8(s32);
s32 func_ovl0B_03_800483E8(s32);
s32 func_ovl0B_03_80048448();
s32 func_ovl0B_03_80048450(s32);
f32 func_ovl0B_03_800484B8(f32);
UnkStructA_40 *func_ovl0B_03_80048690(s32 (*)(u8, u16), void *, s32, s32, s32);
void func_ovl0B_03_800486A8(void);
s32 func_ovl0B_03_800486D8();
s32 func_ovl0B_03_800486E0();
void func_ovl0B_03_800486F8(s32);
s32 func_ovl0B_03_80048740(u8 *);
s32 func_ovl0B_03_80048748(u8 *, u16, u16, f32, f32, s32);
void func_ovl0B_03_80048890(s32);
void func_ovl0B_03_800488A0(s32);
void func_ovl0B_03_800488A8(void);
void func_ovl0B_03_800488B0(s32, f32, f32, f32);
s32 func_ovl0B_03_800489F8(s32);

static void func_ovl0B_03_80043010(void);
void func_ovl0B_03_80043060(s32 arg0);
static void func_ovl0B_03_80043134(Box_ovl0B_03 *boxes, s32 n);
static void func_ovl0B_03_80043170(Box_ovl0B_03 *box, f32 scale);
void func_ovl0B_03_800431FC(void);
static s32 func_ovl0B_03_80043234(u8 *str, f32 scale);
static s32 func_ovl0B_03_800432A0(void);
static s32 func_ovl0B_03_800432F0(void);
static void func_ovl0B_03_80043340(Box_ovl0B_03 *boxes, s32 n, s32 model);
static void func_ovl0B_03_800433BC(void);
static void func_ovl0B_03_80043428(Label_ovl0B_03 *labels, s32 n);
static void func_ovl0B_03_80043464(Label_ovl0B_03 *labels, s32 n);
static void func_ovl0B_03_800434BC(void);
static void func_ovl0B_03_8004368C(s32 obj, s32 *vals);
static void func_ovl0B_03_800436EC(s32 n, Box_ovl0B_03 *boxes, s32 alpha);
void func_ovl0B_03_80043834(void);
void func_ovl0B_03_8004386C(void);
static void func_ovl0B_03_800464B0(Model_ovl0B_03 *models, s32 n);
void func_ovl0B_03_80046510(void);
s32 func_ovl0B_03_80046850(u8 arg0, u16 arg1);
void func_ovl0B_03_80046918(s32 arg0, Gfx_ovl0A_01 **arg1);
void func_ovl0B_03_800469B4(void);
void func_ovl0B_03_80046AE8(void);
void func_ovl0B_03_80046C20(void);
void func_ovl0B_03_80046D54(void);
void func_ovl0B_03_80046E8C(void);
void func_ovl0B_03_80046F78(void);
void func_ovl0B_03_80047064(s32 arg0, Gfx_ovl0A_01 **arg1);
void func_ovl0B_03_80047188(void);
static void func_ovl0B_03_80047190(void);
void func_ovl0B_03_80047198(s32 arg0);
void func_ovl0B_03_8004730C(s32 arg0, void *arg1);
void func_ovl0B_03_80047340(f32 arg0);
void func_ovl0B_03_80047388(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0B_03_800473E4(void);
void func_ovl0B_03_800473FC(void);
static void func_ovl0B_03_80047404(void);
static void func_ovl0B_03_8004740C(void);
static void func_ovl0B_03_80047414(void);
static void func_ovl0B_03_8004741C(void);
static void func_ovl0B_03_80047424(void);
static void func_ovl0B_03_8004742C(void);
static void func_ovl0B_03_80047434(void);
static void func_ovl0B_03_8004743C(void);
static void func_ovl0B_03_80047444(void);
static void func_ovl0B_03_8004744C(void);
static void func_ovl0B_03_80047454(void);
static void func_ovl0B_03_8004745C(void);
static void func_ovl0B_03_80047464(void);

/* .data */
u8 D_ovl0B_03_80048AB0[0x38] = {
    0x29, 0x25, 0x1A, 0x32, 0x1E, 0x2B, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00, 0x28, 0x27, 0x00, 0x00, 0x28, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x29, 0x2D, 0x22, 0x28, 0x27, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x28, 0x26, 0x25, 0x1E, 0x2F, 0x1E, 0x25, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x1A, 0x2D, 0x2D, 0x25, 0x1E, 0x00, 0x00,
};
u8 D_ovl0B_03_80048AE8[0xC] = {
    0x13, 0x00, 0x00, 0x00, 0x2D, 0x22, 0x26, 0x1E, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_03_80048AF4[0x6C] = {
    0x12, 0x0F, 0x26, 0x22, 0x27, 0x00, 0x00, 0x00, 0x27, 0x28, 0x0F, 0x25, 0x22, 0x26, 0x22, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x2E, 0x1D, 0x1D, 0x1E, 0x27, 0xFF, 0x0F, 0x0F, 0x0F, 0x1D, 0x1E, 0x1A, 0x2D, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21, 0x28, 0x2C, 0x2D, 0x00, 0x00, 0x00, 0x1C, 0x21, 0x1A, 0x2B, 0x1A, 0x1C, 0x2D, 0x1E, 0x2B, 0x0F, 0x2D, 0x32, 0x29, 0x1E, 0x00, 0x00, 0x1C, 0x28, 0x27, 0x1F, 0x22, 0x20, 0x00, 0x00, 0x1F, 0x22, 0x25, 0x1E, 0x0F, 0x10, 0x00, 0x00, 0x2C, 0x2D, 0x1A, 0x20, 0x1E, 0x0F, 0x2C, 0x1E, 0x25, 0x1E, 0x1C, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x2D, 0x1A, 0x20, 0x1E, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_03_80048B60[0xC0] = {
    0x2E, 0x27, 0x25, 0x22, 0x26, 0x22, 0x2D, 0x1E, 0x1D, 0x00, 0x00, 0x00, 0x1C, 0x48, 0x47, 0x40, 0x4B, 0x3A, 0x4D, 0x4E, 0x45, 0x3A, 0x4D, 0x42, 0x48, 0x47, 0x4C, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x48, 0x3C, 0x44, 0x0F, 0x20, 0x3A, 0x4B, 0x3D, 0x3E, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x49, 0x0F, 0x3A, 0x47, 0x3D, 0x0F, 0x1D, 0x48, 0x50, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x52, 0x4B, 0x3A, 0x46, 0x42, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x4B, 0x3E, 0x3E, 0x3D, 0x52, 0x0F, 0x2D, 0x4B, 0x3A, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D, 0x48, 0x49, 0x0F, 0x2B, 0x4E, 0x45, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x1F, 0x42, 0x3E, 0x45, 0x3D, 0x0F, 0x48, 0x3F, 0x0F, 0x20, 0x4B, 0x3A, 0x4C, 0x4C, 0x00, 0x00, 0x22, 0x47, 0x0F, 0x4D, 0x41, 0x3E, 0x0F, 0x20, 0x4E, 0x4D, 0x4D, 0x3E, 0x4B, 0x00, 0x00, 0x00, 0x2C, 0x3E, 0x3A, 0x0F, 0x2C, 0x42, 0x3C, 0x44, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x45, 0x42, 0x53, 0x53, 0x3A, 0x4B, 0x3D, 0x0F, 0x1B, 0x3A, 0x4D, 0x4D, 0x45, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x48, 0x4C, 0x4D, 0x0F, 0x3A, 0x4D, 0x0F, 0x2C, 0x3E, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D, 0x3E, 0x3A, 0x46, 0x00, 0x00, 0x00, 0x00,
};
Label_ovl0B_03 D_ovl0B_03_80048C20[4] = {
    { (u8 *)D_ovl0B_03_80048AB0 + 0x30, 0, 0x4F, 0, 0x50, 0.6f, 0.6f, 5, 0 },
    { (u8 *)D_ovl0B_03_80048AE8 + 0x4, 0, 0x4F, 0, 0x6E, 0.6f, 0.6f, 5, 0 },
    { (u8 *)D_ovl0B_03_80048AF4 + 0x14, 0, 0x4F, 0, 0x84, 0.6f, 0.6f, 5, 0 },
    { (u8 *)D_ovl0B_03_80048AF4 + 0x28, 0, 0x4F, 0, 0xAA, 0.6f, 0.6f, 5, 0 },
};
Label_ovl0B_03 D_ovl0B_03_80048C90[4] = {
    { (u8 *)D_ovl0B_03_80048AE8, 0, 0xA6, 0, 0x50, 0.6f, 0.6f, 2, 0 },
    { (u8 *)D_ovl0B_03_80048AF4, 0, 0xA6, 0, 0x6E, 0.6f, 0.6f, 2, 0 },
    { (u8 *)D_ovl0B_03_80048AB0 + 0xC, 0, 0xA6, 0, 0x8C, 0.6f, 0.6f, 0, 0 },
    { (u8 *)D_ovl0B_03_80048AB0 + 0xC, 0, 0xA6, 0, 0xAA, 0.6f, 0.6f, 0, 0 },
};
u8 *D_ovl0B_03_80048D00[2] = { D_ovl0B_03_80048AB0 + 0x10, D_ovl0B_03_80048AB0 + 0xC };
Model_ovl0B_03 D_ovl0B_03_80048D08[4] = {
    { 0x32, 0.0f, 0.0f, 0.0f, NULL },
    { 0x33, 0.0f, 85.0f, 0.0f, NULL },
    { 0x34, 115.0f, 0.0f, 0.0f, NULL },
    { 0x34, -115.0f, 0.0f, 0.0f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80048D58[3] = {
    { 160.0f, 84.0f, 160.0f, 50.0f, 0.7f, NULL },
    { 160.0f, 134.0f, 160.0f, 50.0f, 0.7f, NULL },
    { 160.0f, 184.0f, 160.0f, 50.0f, 0.7f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80048DA0[8] = {
    { 85.0f, 170.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 135.0f, 170.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 185.0f, 170.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 235.0f, 170.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 85.0f, 190.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 135.0f, 190.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 185.0f, 190.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 235.0f, 190.0f, 40.0f, 20.0f, 1.0f, NULL },
};
f32 D_ovl0B_03_80048E60[3] = { 114.0f, 170.0f, 190.0f };
Box_ovl0B_03 D_ovl0B_03_80048E6C[1] = {
    { 55.0f, 114.0f, 20.0f, 20.0f, 0.7f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80048E84[1] = {
    { 115.0f, 114.0f, 20.0f, 20.0f, 0.7f, NULL },
};
Model_ovl0B_03 D_ovl0B_03_80048E9C[4] = {
    { 0x49, -75.0f, -10.0f, 0.0f, NULL },
    { 0x49, -24.0f, -10.0f, 0.0f, NULL },
    { 0x49, 24.0f, -10.0f, 0.0f, NULL },
    { 0x49, 75.0f, -10.0f, 0.0f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80048EEC[12] = {
    { 71.7f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 85.0f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 98.299995f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 121.7f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 135.0f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 148.3f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 171.7f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 185.0f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 198.3f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 221.7f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 235.0f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 248.3f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_8004900C[1] = {
    { 160.0f, 136.0f, 160.0f, 20.0f, 1.0f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80049024[2] = {
    { 138.0f, 68.0f, 16.0f, 16.0f, 1.0f, NULL },
    { 138.0f, 198.0f, 16.0f, 16.0f, 1.0f, NULL },
};
Label_ovl0B_03 D_ovl0B_03_80049054[2] = {
    { (u8 *)D_ovl0B_03_80048B60 + 0xB8, 0, 0x90, 0, 0x3C, 0.7f, 0.7f, 2, 0 },
    { (u8 *)D_ovl0B_03_80048B60 + 0xB8, 0, 0x90, 0, 0xBE, 0.7f, 0.7f, 2, 0 },
};
s32 D_ovl0B_03_8004908C[10] = { 0x201, 0x202, 0x206, 0x208, 0x20D, 0x211, 0x212, 0x216, 0x217, 0x218 };
s32 D_ovl0B_03_800490B4[10] = { -1, 0x203, -1, -1, 0x210, -1, 0x215, -1, -1, 0x352 };
f32 D_ovl0B_03_800490DC[10] = { 0.0f, -20.0f, -20.0f, 0.0f, 0.0f, -20.0f, -20.0f, -40.0f, 0.0f, 0.0f };
Pair_ovl0B_03 D_ovl0B_03_80049104[8] = { { 0, 60 }, { 2, 60 }, { 4, 10 }, { 6, 10 }, { 4, 10 }, { 6, 10 }, { 4, 20 }, { 6, 60 } };
u8 D_ovl0B_03_80049144[0x24] = {
    0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0x42, 0x47, 0x40, 0xFF, 0x0F, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_03_80049168[0x2C] = {
    0x1C, 0x48, 0x4E, 0x45, 0x3D, 0x0F, 0x27, 0x48, 0x4D, 0x0F, 0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0xFF, 0x0F, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 *D_ovl0B_03_80049194[10] = { D_ovl0B_03_80048B60 + 0x20, D_ovl0B_03_80048B60 + 0x30, D_ovl0B_03_80048B60 + 0x40, D_ovl0B_03_80048B60 + 0x4C, D_ovl0B_03_80048B60 + 0x5C, D_ovl0B_03_80048B60 + 0x68, D_ovl0B_03_80048B60 + 0x78, D_ovl0B_03_80048B60 + 0x88, D_ovl0B_03_80048B60 + 0x94, D_ovl0B_03_80048B60 + 0xA8 };

/* .bss */
u8 D_ovl0B_03_800492E0[0x24];
s32 D_ovl0B_03_80049304;
s32 D_ovl0B_03_80049308;
u8 D_ovl0B_03_8004930C[4];
f32 D_ovl0B_03_80049310[3];
s32 D_ovl0B_03_8004931C;
u8 D_ovl0B_03_80049320[0x1000];
s32 D_ovl0B_03_8004A320;
UnkStructB *D_ovl0B_03_8004A324;
s32 D_ovl0B_03_8004A328;
s32 D_ovl0B_03_8004A32C;
s32 D_ovl0B_03_8004A330;
UnkStructA_40 *D_ovl0B_03_8004A334;
UnkStructA_40 *D_ovl0B_03_8004A338;
u8 D_ovl0B_03_8004A33C[4];
Anim_ovl0B_03 D_ovl0B_03_8004A340[3][5];
Inner *D_ovl0B_03_8004A3F4;
UnkStructA_40 *D_ovl0B_03_8004A3F8;
u8 D_ovl0B_03_8004A3FC[4];
s32 D_ovl0B_03_8004A400[4];
s32 D_ovl0B_03_8004A410;
s32 D_ovl0B_03_8004A414;
u8 D_ovl0B_03_8004A418[8];

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047464(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004745C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047454(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004744C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047444(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004743C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047434(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004742C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047424(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004741C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047414(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004740C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047404(void) {
}

void func_ovl0B_03_800473FC(void) {

}

void func_ovl0B_03_800473E4(void) {
    D_ovl0B_03_80049304 = -1;
    D_ovl0B_03_80049308 = -1;
}

void func_ovl0B_03_80047388(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0B_03_80047FF8(M2C_FIELD(&D_ovl0B_03_80049310, f32 *, 0), M2C_FIELD(&D_ovl0B_03_80049310, f32 *, 4), M2C_FIELD(&D_ovl0B_03_80049310, f32 *, 8));
    func_ovl0B_03_80048018(arg0, arg1, arg2);
    func_ovl0B_03_80048328(0xB4);
}

void func_ovl0B_03_80047340(f32 arg0) {
    f32 sp1C;

    func_ovl0B_03_80048020(&sp1C, NULL, NULL);
    func_ovl0B_03_80048018(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0B_03_8004730C(s32 arg0, void *arg1) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg1, void **, 0x40);
    func_ovl0B_03_800488B0(arg0, M2C_FIELD(temp_v0, f32 *, 0x10), M2C_FIELD(temp_v0, f32 *, 0x14), M2C_FIELD(temp_v0, f32 *, 0x18));
}

void func_ovl0B_03_80047198(s32 arg0) {
    s32 i;
    s32 j;
    Model_ovl0B_03 *p;

    switch (arg0) {
    case 2:
        D_ovl0B_03_8004931C = func_ovl0B_03_800478B8();
        func_ovl0B_03_800488A0(0x1D);
        return;
    case 16:
        func_ovl0B_03_80048308(func_ovl0B_03_8004386C, NULL, (s32) &D_ovl0B_03_80049320, 0x1000, 0x130);
        func_ovl0B_03_80048308(func_ovl0B_03_80046510, NULL, 0, 0, 0x130);
        return;
    case 1:
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 5; j++) {
                func_ovl0B_03_80047EA0(D_ovl0B_03_8004A340[i][j].unk0);
            }
        }
        for (p = D_ovl0B_03_80048D08, i = 0; i < 4; i++, p++) {
            func_ovl0B_03_80047EA0(p->unk10);
        }
        for (p = D_ovl0B_03_80048E9C, i = 0; i < 4; i++, p++) {
            func_ovl0B_03_80047EA0(p->unk10);
        }
        return;
    case 12:
        func_ovl0B_03_800488A8();
        return;
    case 17:
        func_ovl0B_03_80047190();
        return;
    }
}

static void func_ovl0B_03_80047190(void) {
}

void func_ovl0B_03_80047188(void) {

}

void func_ovl0B_03_80047064(s32 arg0, Gfx_ovl0A_01 **arg1) {
    Gfx_ovl0A_01 *g;

    g = *arg1;
    GFX_W_ovl0B_03(g++, 0xFA000000, 0xFF0080);
    GFX_W_ovl0B_03(g++, 0xFCFFFFFF, 0xFFFDF6FB);
    GFX_W_ovl0B_03(g++, 0xF7000000, 0x10001);
    GFX_W_ovl0B_03(g++,
                   0xF6000000 | (((D_ovl0B_03_8004A414 + 160) & 0x3FF) << 14) |
                       ((((s32) (D_ovl0B_03_8004A414 * 0.72f) + 136) & 0x3FF) << 2),
                   (((160 - D_ovl0B_03_8004A414) & 0x3FF) << 14) |
                       (((136 - (s32) (D_ovl0B_03_8004A414 * 0.72f)) & 0x3FF) << 2));
    *arg1 = g;
}

void func_ovl0B_03_80046F78(void) {
    f32 t;

    for (t = -60.0f; t < 0; t += 1.0f) {
        func_ovl0B_03_80048018(0.0f, 0.0f, t * t * -0.061f + 420.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046E8C(void) {
    f32 t;

    for (t = 0; t > -60.0f; t -= 1.0f) {
        func_ovl0B_03_80048018(0.0f, 0.0f, t * t * -0.061f + 420.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046D54(void) {
    f32 t;
    f32 a;

    a = M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C);
    for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
        M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C) = WRAP_ovl0B_03(t * t * 0.225f + a - 90.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046C20(void) {
    f32 t;
    f32 a;

    a = M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C);
    for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
        M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C) = WRAP_ovl0B_03(t * t * -0.225f + a + 90.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046AE8(void) {
    f32 t;
    f32 a;

    a = M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C);
    for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
        M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C) = WRAP_ovl0B_03(t * t * 0.45f + a - 180.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_800469B4(void) {
    f32 t;
    f32 a;

    a = M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C);
    for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
        M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C) = WRAP_ovl0B_03(t * t * -0.45f + a + 180.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046918(s32 arg0, Gfx_ovl0A_01 **arg1) {
    Gfx_ovl0A_01 *g;

    g = *arg1;
    GFX_W_ovl0B_03(g++, 0xFA000000, 0xFFFFFF80);
    GFX_W_ovl0B_03(g++, 0xFCFFFFFF, 0xFFFDF6FB);
    GFX_W_ovl0B_03(g++, 0xF7000000, 0x10001);
    GFX_W_ovl0B_03(g++, 0xF6000000 | (((D_ovl0B_03_8004A410 + 109) & 0x3FF) << 14) | ((207 & 0x3FF) << 2),
                   (((D_ovl0B_03_8004A410 + 60) & 0x3FF) << 14) | ((68 & 0x3FF) << 2));
    *arg1 = g;
}

s32 func_ovl0B_03_80046850(u8 arg0, u16 arg1) {
    s32 b;
    s32 p;

    b = arg1;
    p = arg0;
    if (b & 1) {
        func_ovl0B_03_80048890(1);
        D_ovl0B_03_8004A320 = -1;
        return 0;
    }
    if (b & 2) {
        func_ovl0B_03_80048890(2);
        D_ovl0B_03_8004A320 = -2;
        return 0;
    }
    if (b & 0x180) {
        if (b & 0x80) {
            D_ovl0B_03_8004A320 = p + 0x10;
            return 0;
        }
        if (b & 0x100) {
            D_ovl0B_03_8004A320 = p + 0x20;
        }
        return 0;
    }
    if (b & 0x60) {
        return 1;
    }
    return 1;
}

void func_ovl0B_03_80046510(void) {
    s32 i;
    s32 j;
    s32 k;
    s32 x;
    s32 y0;
    s32 y1;
    Anim_ovl0B_03 *a;
    UnkStructA_40 *obj;

    func_ovl0B_03_800464B0(D_ovl0B_03_80048D08, 4);
    D_ovl0B_03_80048D08[2].unk10->unkC |= 0x80;
    D_ovl0B_03_80048D08[3].unk10->unkC |= 0x80;
    func_ovl0B_03_800464B0(D_ovl0B_03_80048E9C, 4);
    for (i = 0; i < 4; i++) {
        D_ovl0B_03_80048E9C[i].unk10->unk30 = 0.4f;
        D_ovl0B_03_80048E9C[i].unk10->unk28 = D_ovl0B_03_80048E9C[i].unk10->unk2C = D_ovl0B_03_80048E9C[i].unk10->unk30;
        func_ovl0B_03_80047ED8(D_ovl0B_03_80048E9C[i].unk10, 2);
        func_ovl0B_03_80047EE0(D_ovl0B_03_80048E9C[i].unk10, 1, 0);
        func_ovl0B_03_80047EE0(D_ovl0B_03_80048E9C[i].unk10, 2, 1);
        D_ovl0B_03_80048E9C[i].unk10->unkC |= 0x41;
        func_ovl0B_03_80047EC0(D_ovl0B_03_80048E9C[i].unk10, 0xC);
        for (j = 0; j < 12; j++) {
            func_ovl0B_03_80047EC8(D_ovl0B_03_80048E9C[i].unk10, i + 0x4A, j, j);
        }
        D_ovl0B_03_8004A400[i] = func_ovl0B_03_80047F28(D_ovl0B_03_80048E9C[i].unk10, 0xF);
    }
    y1 = 0x58;
    y0 = 0x18;
    for (i = 0; i < 3; i++) {
        k = i;
        for (j = 0, x = 0; j < 5; j++, x += 0x40) {
            a = &D_ovl0B_03_8004A340[i][j];
            obj = func_ovl0B_03_80047E98(0x30, 0);
            a->unk0 = obj;
            a->unk8 = k & 3;
            a->unk4 = D_ovl0B_03_80049104[k & 3].unk4;
            M2C_FIELD(obj, s32 *, 0x38) = D_ovl0B_03_80049104[k & 3].unk0;
            a->unk0->unk10 = x;
            a->unk0->unk14 = y0;
            a->unk0->unk18 = x + 0x40;
            a->unk0->unk1C = y1;
            a->unk0->unkC |= 0x400;
            k++;
        }
        y1 += 0x40;
        y0 += 0x40;
    }
    while (TRUE) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 5; j++) {
                a = &D_ovl0B_03_8004A340[i][j];
                if (--a->unk4 == 0) {
                    a->unk8++;
                    if (a->unk8 >= 8) {
                        a->unk8 = 0;
                    }
                    a->unk4 = D_ovl0B_03_80049104[a->unk8].unk4;
                    M2C_FIELD(a->unk0, s32 *, 0x38) = D_ovl0B_03_80049104[a->unk8].unk0;
                }
            }
        }
        func_ovl0B_03_80048350();
    }
}

/* The original passes n in $s2 (its callers' register). */
static void func_ovl0B_03_800464B0(Model_ovl0B_03 *models, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        models[i].unk10 = func_ovl0B_03_80047E98(models[i].unk0, 0);
        models[i].unk10->unk10 = models[i].unk4;
        models[i].unk10->unk14 = models[i].unk8;
        models[i].unk10->unk18 = models[i].unkC;
    }
}

void func_ovl0B_03_80043834(void) {
    func_ovl0B_03_80048308(func_ovl0B_03_80046F78, NULL, 0, 0, 0x130);
}

void func_ovl0B_03_800431FC(void) {
    func_ovl0B_03_80048308(func_ovl0B_03_80046E8C, NULL, 0, 0, 0x130);
}

void func_ovl0B_03_80043060(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        func_ovl0B_03_80048308(func_ovl0B_03_80046D54, NULL, 0, 0, 0x130);
        return;
    case 1:
        func_ovl0B_03_80048308(func_ovl0B_03_80046C20, NULL, 0, 0, 0x130);
        return;
    case 2:
        func_ovl0B_03_80048308(func_ovl0B_03_80046AE8, NULL, 0, 0, 0x130);
        return;
    case 3:
        func_ovl0B_03_80048308(func_ovl0B_03_800469B4, NULL, 0, 0, 0x130);
        return;
    }
}

void func_ovl0B_03_8004386C(void) {
    u8 *sp124;
    s32 sp110;
    s32 sp10C;
    s32 sp108;
    s32 sp104;
    MenuPos_ovl0B_03 spCC[6] = { { 71, 87, 0, 2, 0, 0 }, { 71, 117, 1, 3, 0, 0 }, { 71, 147, 2, 4, 0, 0 }, { 71, 177, 3, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } };
    MenuPos_ovl0B_03 spA4[5] = { { 172, 78, 0, 2, 0, 0 }, { 172, 108, 1, 3, 0, 0 }, { 172, 138, 2, 4, 0, 0 }, { 172, 168, 3, 5, 0, 0 }, { 172, 198, 4, 0, 0, 0 } };
    Box_ovl0B_03 (*sp88)[];
    u32 sp84;
    Inner *temp_v0_16;
    u8 *var_s7_3;
    u8 *var_s7_5;
    UnkStructA_40 *temp_t7;
    UnkStructA_40 *temp_v0_18;
    UnkStructA_40 *temp_v0_19;
    UnkStructA_40 *temp_v0_21;
    UnkStructA_40 *temp_v0_22;
    UnkStructA_40 *temp_v0_23;
    UnkStructB **var_s0;
    UnkStructB **var_s0_2;
    UnkStructB *temp_t0;
    UnkStructB *temp_t0_2;
    UnkStructB *temp_t0_3;
    UnkStructB *temp_t0_4;
    UnkStructB *var_v0_2;
    UnkStructB *var_v0_3;
    UnkStructB *var_v0_6;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_ft0;
    f32 temp_ft2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fa0_3;
    f32 var_fa0_4;
    f32 var_fa0_5;
    f32 var_fa0_6;
    f32 var_fs1;
    f32 var_fs1_2;
    f32 var_fs1_3;
    f32 var_fs4;
    f32 var_fs4_2;
    f32 var_fs4_3;
    f32 var_fs4_4;
    f32 var_fs4_5;
    f32 var_fs4_6;
    s16 var_fp;
    s16 var_fp_2;
    s16 var_fp_5;
    s32 *temp_s3;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_fp;
    s32 temp_fp_2;
    s32 temp_fp_3;
    s32 temp_s3_2;
    s32 temp_s3_3;
    s32 temp_s3_4;
    s32 temp_s3_5;
    s32 temp_s3_6;
    s32 temp_s3_7;
    s32 temp_s3_8;
    s32 temp_s4;
    s32 temp_s7;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_v0;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_17;
    s32 temp_v0_20;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_6;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_a1_5;
    s32 var_a1_6;
    s32 var_at;
    s32 var_fp_10;
    s32 var_fp_11;
    s32 var_fp_12;
    s32 var_fp_13;
    s32 var_fp_14;
    s32 var_fp_15;
    s32 var_fp_16;
    s32 var_fp_17;
    s32 var_fp_18;
    s32 var_fp_3;
    s32 var_fp_4;
    s32 var_fp_6;
    s32 var_fp_7;
    s32 var_fp_8;
    s32 var_fp_9;
    s32 var_s3_4;
    s32 var_s7;
    s32 var_s7_2;
    s32 var_s7_4;
    s32 var_s7_7;
    s32 var_s7_8;
    s32 var_t6;
    s32 var_t7;
    s32 var_t8;
    s32 var_t9;
    s32 var_t9_2;
    s32 var_v1_2;
    s32 var_v1_3;
    Label_ovl0B_03 *var_s7_6;
    Box_ovl0B_03 *temp_a0;
    Box_ovl0B_03 *temp_a0_2;
    Box_ovl0B_03 *var_a0;
    Box_ovl0B_03 *var_a0_2;
    Box_ovl0B_03 *var_a1;
    Box_ovl0B_03 *var_s3_2;
    Box_ovl0B_03 *var_s3_3;
    Box_ovl0B_03 *var_v0;
    Box_ovl0B_03 *var_v1;
    u32 var_s3;
    u32 var_s4;
    void *temp_s7_2;
    void *temp_s7_3;
    void *temp_v0_14;
    void *temp_v0_15;
    void *temp_v0_5;
    void *temp_v0_7;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_5;
    void *temp_v1_6;
    void *temp_v1_7;
    void *temp_v1_8;
    u8 *var_v0_4;
    u8 *var_v0_5;
    void *var_v1_4;

    D_ovl0B_03_8004A324 = func_ovl0B_03_80047938();
    func_ovl0B_03_80048060(0x7F);
    func_ovl0B_03_80047FD8(1);
    func_ovl0B_03_80047FF8(0.0f, 10.0f, 0.0f);
    func_ovl0B_03_80047FE8(1);
    func_ovl0B_03_80043834();
    func_ovl0B_03_80048328(0xA);
    D_ovl0B_03_8004A328 = 0;
    temp_s3 = func_ovl0B_03_80047908();
    sp104 = 5;
    if ((func_ovl0B_03_800489F8(2) != 0) || (M2C_FIELD(temp_s3, s32 *, 0x44) != 0)) {
        sp104 = 7;
    }
    if ((func_ovl0B_03_800489F8(1) != 0) || (M2C_FIELD(temp_s3, s32 *, 0x44) != 0)) {
        sp104 = 9;
    }
    var_s3 = 0;
loop_7:
    switch (var_s3) {                               /* switch 1 */
    case 0:                                         /* switch 1 */
        var_fs1 = 0.0f;
        func_ovl0B_03_80043340(D_ovl0B_03_80048D58, 3, 0x31);
        if (360.0f <= 0.0f) {
            var_fa0 = 0.0f - 360.0f;
        } else {
            if (0.0f < 0.0f) {
                var_fs4 = 0.0f + 360.0f;
            } else {
                var_fs4 = 0.0f;
            }
            var_fa0 = var_fs4;
        }
        func_ovl0B_03_80043170(&D_ovl0B_03_80048D58[D_ovl0B_03_8004A324->unk0], (func_ovl0B_03_800484B8(var_fa0) * 0.05f) + 1.0f);
        var_fp = 0;
        do {
            func_ovl0B_03_800436EC(3, D_ovl0B_03_80048D58, var_fp);
            func_ovl0B_03_80048350();
            var_fp += 8;
        } while (var_fp != 0x108);
loop_17:
        temp_s3_2 = func_ovl0B_03_800432F0();
        temp_v0 = func_ovl0B_03_800432A0();
        if (temp_s3_2 & 0x400) {
            temp_v0_2 = D_ovl0B_03_8004A324->unk0;
            if (temp_v0_2 < 2) {
                D_ovl0B_03_8004A324->unk0 = temp_v0_2 + 1;
                func_ovl0B_03_80048890(0);
            }
block_47:
            var_a1 = D_ovl0B_03_80048D58;
            var_a0 = D_ovl0B_03_80048D58;
            do {
                func_ovl0B_03_80043170(var_a0, 0.7f);
                var_a1 = var_a1 + 1;
                var_a0 = var_a1;
            } while (var_a1 != D_ovl0B_03_80048DA0);
            if (var_fs1 >= 360.0f) {
                var_fa0_2 = var_fs1 - 360.0f;
            } else {
                if (var_fs1 < 0.0f) {
                    var_fs4_2 = var_fs1 + 360.0f;
                } else {
                    var_fs4_2 = var_fs1;
                }
                var_fa0_2 = var_fs4_2;
            }
            func_ovl0B_03_80043170(&D_ovl0B_03_80048D58[D_ovl0B_03_8004A324->unk0], (func_ovl0B_03_800484B8(var_fa0_2) * 0.05f) + 1.0f);
            var_fs1 += 4.0f;
            func_ovl0B_03_80048350();
            goto loop_17;
        }
        if (temp_s3_2 & 0x800) {
            if (D_ovl0B_03_8004A324->unk0 > 0) {
                func_ovl0B_03_80048890(0);
                D_ovl0B_03_8004A324->unk0 -= 1;
            }
            goto block_47;
        }
        if (temp_v0 & 0x8000) {
            func_ovl0B_03_80048890(1);
            var_s4 = 1;
            if (D_ovl0B_03_8004A324->unk0 == 2) {
                var_s4 = 2;
            } else {
                func_ovl0B_03_80043060(1);
            }
            var_fp_2 = 0xF8;
            do {
                func_ovl0B_03_800436EC(3, D_ovl0B_03_80048D58, var_fp_2);
                func_ovl0B_03_80048350();
                var_fp_2 -= 8;
            } while (var_fp_2 > 0);
            if (var_s4 == 1) {
                var_s7 = 0;
                func_ovl0B_03_800483B8();
                var_fp_3 = 0;
                do {
                    temp_v0_3 = func_ovl0B_03_800483C8(var_fp_3);
                    var_fp_3 += 1;
                    var_s7 |= temp_v0_3;
                } while (var_fp_3 < 4);
                if (var_s7 & 1) {
                    temp_s3_3 = func_ovl0B_03_80048748(D_ovl0B_03_80049144, 0x42U, 0x6EU, 0.6f, 0.6f, 2);
                    func_ovl0B_03_80048328(2);
                    func_ovl0B_03_80048448();
                    func_ovl0B_03_80048328(2);
                    func_ovl0B_03_800486F8(temp_s3_3);
                    func_ovl0B_03_80048328(4);
                }
                var_fp_4 = 0;
                do {
                    if (func_ovl0B_03_800483C8(var_fp_4) & 1) {
                        temp_v0_4 = func_ovl0B_03_80048450(var_fp_4);
                        if ((temp_v0_4 != 9) && (temp_v0_4 != 7)) {
                            D_ovl0B_03_80049168[0x26] = var_fp_4 + 0x11;
                            func_ovl0B_03_80048890(0x18);
                            temp_s3_4 = func_ovl0B_03_80048748(D_ovl0B_03_80049168, 0x42U, 0x6EU, 0.6f, 0.6f, 3);
                            func_ovl0B_03_80048328(0xB4);
                            func_ovl0B_03_800486F8(temp_s3_4);
                            func_ovl0B_03_80048328(4);
                        }
                    }
                    var_fp_4 += 1;
                } while (var_fp_4 != 4);
            }
            func_ovl0B_03_80043134(D_ovl0B_03_80048D58, 3);
            func_ovl0B_03_80048350();
block_389:
            var_s3 = var_s4;
        default:                                    /* switch 1 */
            func_ovl0B_03_80048350();
            goto loop_7;
        }
        if (temp_v0 & 0x4000) {
            func_ovl0B_03_80048890(0x25);
            func_ovl0B_03_800431FC();
            var_fp_5 = 0xF8;
            do {
                func_ovl0B_03_800436EC(3, D_ovl0B_03_80048D58, var_fp_5);
                func_ovl0B_03_80048350();
                var_fp_5 -= 8;
            } while (var_fp_5 != 0);
            func_ovl0B_03_80043134(D_ovl0B_03_80048D58, 3);
            func_ovl0B_03_800478B0(0x20, 0x11, 0);
loop_46:
            func_ovl0B_03_80048350();
            goto loop_46;
        }
        goto block_47;
    case 1:                                         /* switch 1 */
        func_ovl0B_03_800433BC();
        D_ovl0B_03_8004A3F4 = func_ovl0B_03_80047F18(func_ovl0B_03_80046918, 0);
        M2C_FIELD(D_ovl0B_03_8004A3F4, s32 *, 0xC) = (s32) (M2C_FIELD(D_ovl0B_03_8004A3F4, s32 *, 0xC) | 0x480);
        D_ovl0B_03_8004A410 = D_ovl0B_03_8004A328 * 0x32;
        D_ovl0B_03_8004A32C = 0;
        func_ovl0B_03_80043340(D_ovl0B_03_80048DA0, 8, 0x35);
        func_ovl0B_03_80043340(D_ovl0B_03_80048E6C, 2, 0x39);
        var_v1 = D_ovl0B_03_80048EEC;
        var_s3_2 = D_ovl0B_03_80048EEC;
        do {
            var_s7_2 = 0;
            sp84 = (u32) var_v1;
            sp88 = (Box_ovl0B_03 (*)[]) var_s3_2;
            func_ovl0B_03_80043340(var_s3_2, 3, 0x3A);
            var_s0 = &D_ovl0B_03_8004A324;
            var_v0 = var_v1;
loop_58:
            temp_t7 = var_v0->unk14;
            var_s7_2 += 1;
            var_v0 += 0x18;
            M2C_FIELD(temp_t7, s32 *, 0x38) = 0;
            if (var_s7_2 != 3) {
                goto loop_58;
            }
            var_v1 = &var_v1[3];
            var_s3_2 = &var_s3_2[3];
        } while ((u32) var_v1 < (u32) D_ovl0B_03_8004900C);
        var_s7_3 = (u8 *)D_ovl0B_03_80048E9C;
        var_fp_6 = 0;
        do {
            temp_v0_5 = M2C_FIELD(var_s7_3, void **, 0x10);
            M2C_FIELD(temp_v0_5, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_5, s32 *, 0xC) & ~1);
            if (func_ovl0B_03_80048450(var_fp_6) != 9) {
                (*var_s0)->unk40[var_fp_6] = 0;
            }
            temp_t0 = *var_s0;
            if ((temp_t0->unk4[var_fp_6] == 1) && (temp_t0->unk40[var_fp_6] == 1)) {
                func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[var_fp_6], (*var_s0)->unk50[var_fp_6]);
            } else {
                func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[var_fp_6], NULL);
            }
            var_s0 = &D_ovl0B_03_8004A324;
            var_fp_6 += 1;
            var_s7_3 += 0x14;
        } while (var_fp_6 != 4);
        temp_v1 = D_ovl0B_03_80048E9C[D_ovl0B_03_8004A328].unk10;
        var_fs1_2 = 0.0f;
        M2C_FIELD(temp_v1, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xC) & ~0x40);
        func_ovl0B_03_800434BC();
loop_69:
        temp_s3_5 = func_ovl0B_03_800432F0();
        temp_v0_6 = func_ovl0B_03_800432A0();
        var_s0_2 = (u8 *)D_ovl0B_03_8004A324;
        if (temp_s3_5 & 0x800) {
block_71:
            var_v1_2 = D_ovl0B_03_8004A32C;
            if (var_v1_2 > 0) {
                func_ovl0B_03_80048890(0);
                var_v1_2 = D_ovl0B_03_8004A32C - 1;
                D_ovl0B_03_8004A32C = var_v1_2;
            }
block_152:
            temp_t6 = D_ovl0B_03_8004A328 * 0x32;
            D_ovl0B_03_8004A410 = temp_t6;
            temp_fv0 = D_ovl0B_03_80048E60[var_v1_2];
            temp_fv1 = (f32) temp_t6;
            M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x1C) = temp_fv0;
            D_ovl0B_03_80048E6C->unk0 = temp_fv1 + 60.0f;
            M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x18) = (f32) (temp_fv1 + 110.0f);
            D_ovl0B_03_80048E6C->unk4 = temp_fv0;
            if (var_fs1_2 >= 360.0f) {
                var_fa0_3 = var_fs1_2 - 360.0f;
            } else {
                if (var_fs1_2 < 0.0f) {
                    var_fs4_3 = var_fs1_2 + 360.0f;
                } else {
                    var_fs4_3 = var_fs1_2;
                }
                var_fa0_3 = var_fs4_3;
            }
            func_ovl0B_03_80043170(D_ovl0B_03_80048E6C, (func_ovl0B_03_800484B8(var_fa0_3) * 0.05f) + 0.7f);
            if (var_fs1_2 >= 360.0f) {
                var_fa0_4 = var_fs1_2 - 360.0f;
            } else {
                if (var_fs1_2 < 0.0f) {
                    var_fs4_4 = var_fs1_2 + 360.0f;
                } else {
                    var_fs4_4 = var_fs1_2;
                }
                var_fa0_4 = var_fs4_4;
            }
            func_ovl0B_03_80043170(D_ovl0B_03_80048E84, (func_ovl0B_03_800484B8(var_fa0_4) * 0.05f) + 0.7f);
            var_fs1_2 += 4.0f;
            func_ovl0B_03_800434BC();
            func_ovl0B_03_80048350();
            goto loop_69;
        }
        if (temp_v0_6 & 8) {
            goto block_71;
        }
        if (temp_s3_5 & 0x400) {
block_76:
            if (D_ovl0B_03_8004A32C < 2) {
                func_ovl0B_03_80048890(0);
                D_ovl0B_03_8004A32C += 1;
            }
            if ((D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328] == 0) && (D_ovl0B_03_8004A32C == 2)) {
                D_ovl0B_03_8004A32C = 1;
            }
            var_v1_2 = D_ovl0B_03_8004A32C;
            goto block_152;
        }
        if (temp_v0_6 & 4) {
            goto block_76;
        }
        if (temp_v0_6 & 0x8000) {
            var_v0_2 = D_ovl0B_03_8004A324;
            var_s7_4 = 0;
            var_a1_2 = 0;
            do {
                var_a1_2 += 4;
                if (var_v0_2->unk4[0] != 0) {
                    var_s7_4 += 1;
                }
                var_v0_2 += 4;
            } while (var_a1_2 != 0x10);
            if (var_s7_4 >= 2) {
                func_ovl0B_03_80048890(1);
                var_s4 = 4;
                if (D_ovl0B_03_8004A324->unk0 == 0) {
                    var_s4 = 5;
                }
            } else {
                func_ovl0B_03_80048890(0x18);
                var_v1_2 = D_ovl0B_03_8004A32C;
                goto block_152;
            }
        } else if (temp_v0_6 & 0x4000) {
            var_s4 = 0;
            func_ovl0B_03_80048890(2);
        } else {
            if (temp_v0_6 & 3) {
                var_v1_3 = 0;
            } else {
                var_v1_3 = D_ovl0B_03_8004A32C;
            }
            switch (var_v1_3) {                     /* switch 2; irregular */
            default:                                /* switch 2 */
                var_v1_2 = D_ovl0B_03_8004A32C;
                break;
            case 0:                                 /* switch 2 */
                if ((temp_s3_5 & 0x200) || (temp_v0_6 & 2)) {
                    if (D_ovl0B_03_8004A328 > 0) {
                        func_ovl0B_03_80048890(0);
                        temp_v1_2 = D_ovl0B_03_80048E9C[D_ovl0B_03_8004A328].unk10;
                        M2C_FIELD(temp_v1_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0xC) | 0x40);
                        temp_t8 = D_ovl0B_03_8004A328 - 1;
                        var_v1_4 = D_ovl0B_03_80048E9C[temp_t8].unk10;
                        D_ovl0B_03_8004A328 = temp_t8;
                        var_t9 = M2C_FIELD(var_v1_4, s32 *, 0xC) & ~0x40;
                        goto block_110;
                    }
                } else if (((temp_s3_5 & 0x100) || (temp_v0_6 & 1)) && (D_ovl0B_03_8004A328 < 3)) {
                    func_ovl0B_03_80048890(0);
                    temp_v1_3 = D_ovl0B_03_80048E9C[D_ovl0B_03_8004A328].unk10;
                    M2C_FIELD(temp_v1_3, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1_3, s32 *, 0xC) | 0x40);
                    temp_t8_2 = D_ovl0B_03_8004A328 + 1;
                    var_v1_4 = D_ovl0B_03_80048E9C[temp_t8_2].unk10;
                    D_ovl0B_03_8004A328 = temp_t8_2;
                    var_t9 = M2C_FIELD(var_v1_4, s32 *, 0xC) & ~0x40;
block_110:
                    M2C_FIELD(var_v1_4, s32 *, 0xC) = var_t9;
                }
                var_v1_2 = D_ovl0B_03_8004A32C;
                break;
            case 1:                                 /* switch 2 */
                var_fp_7 = D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328];
                if (temp_s3_5 & 0x200) {
                    func_ovl0B_03_80048890(0);
                    var_fp_7 -= 1;
                    if (var_fp_7 < 0) {
                        var_fp_7 = 2;
                    }
                    if ((func_ovl0B_03_800483D8(D_ovl0B_03_8004A328) & 8) && (var_fp_7 == 1)) {
                        var_fp_7 -= 1;
                    }
                } else if ((temp_s3_5 & 0x100) || (temp_v0_6 & 0x2000)) {
                    func_ovl0B_03_80048890(0);
                    var_fp_7 += 1;
                    if (var_fp_7 >= 3) {
                        var_fp_7 = 0;
                    }
                    if ((func_ovl0B_03_800483D8(D_ovl0B_03_8004A328) & 8) && (var_fp_7 == 1)) {
                        var_fp_7 += 1;
                    }
                }
                D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328] = var_fp_7;
                if ((D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328] == 1) && (D_ovl0B_03_8004A324->unk40[D_ovl0B_03_8004A328] == 1)) {
                    func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[D_ovl0B_03_8004A328], D_ovl0B_03_8004A324->unk50[D_ovl0B_03_8004A328]);
                } else {
                    func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[D_ovl0B_03_8004A328], NULL);
                }
                var_v1_2 = D_ovl0B_03_8004A32C;
                break;
            case 2:                                 /* switch 2 */
                temp_a1 = D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328];
                if (temp_a1 == 2) {
                    var_fp_8 = M2C_FIELD(((u8 *)D_ovl0B_03_8004A324 + (D_ovl0B_03_8004A328 * 4)), s32 *, 0x14);
                    if (temp_s3_5 & 0x200) {
                        func_ovl0B_03_80048890(0);
                        var_fp_8 -= 1;
                        if (var_fp_8 < 0) {
                            var_fp_8 = 2;
                        }
                    } else if ((temp_s3_5 & 0x100) || (temp_v0_6 & 0x2000)) {
                        func_ovl0B_03_80048890(0);
                        var_fp_8 += 1;
                        if (var_fp_8 >= 3) {
                            var_fp_8 = 0;
                        }
                    }
                    M2C_FIELD(((u8 *)D_ovl0B_03_8004A324 + (D_ovl0B_03_8004A328 * 4)), s32 *, 0x14) = var_fp_8;
                } else if (temp_a1 == 1) {
                    var_fp_9 = D_ovl0B_03_8004A324->unk40[D_ovl0B_03_8004A328];
                    temp_a1_2 = temp_s3_5 & 0x300;
                    if (((temp_a1_2 != 0) || (temp_v0_6 & 0x2000)) && (var_fp_9 == 1)) {
                        func_ovl0B_03_80048890(0);
                        var_fp_9 = 0;
                        func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[D_ovl0B_03_8004A328], NULL);
                        goto block_149;
                    }
                    if (((temp_a1_2 != 0) || (temp_v0_6 & 0x2000)) && (var_fp_9 == 0) && (func_ovl0B_03_80048450(D_ovl0B_03_8004A328) == 9)) {
                        func_ovl0B_03_80048890(0);
                        var_fp_9 = 1;
                        func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[D_ovl0B_03_8004A328], D_ovl0B_03_8004A324->unk50[D_ovl0B_03_8004A328]);
block_149:
                        var_s0_2 = (u8 *)D_ovl0B_03_8004A324;
                    }
                    (*var_s0_2)->unk40[D_ovl0B_03_8004A328] = var_fp_9;
                }
                var_v1_2 = D_ovl0B_03_8004A32C;
                break;
            }
            goto block_152;
        }
        var_s7_5 = (u8 *)D_ovl0B_03_80048E9C;
        do {
            temp_v0_7 = M2C_FIELD(var_s7_5, void **, 0x10);
            var_s7_5 += 0x14;
            M2C_FIELD(temp_v0_7, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_7, s32 *, 0xC) | 0x41);
        } while ((u32) var_s7_5 < (u32) D_ovl0B_03_80048EEC);
        func_ovl0B_03_80047EA0((UnkStructA_40 *) D_ovl0B_03_8004A3F4);
        func_ovl0B_03_80043134(D_ovl0B_03_80048DA0, 8);
        func_ovl0B_03_80043134(D_ovl0B_03_80048E6C, 2);
        var_s3_3 = D_ovl0B_03_80048EEC;
        var_a0_2 = D_ovl0B_03_80048EEC;
        do {
            func_ovl0B_03_80043134(var_a0_2, 3);
            var_s3_3 += 0x48;
            var_a0_2 = var_s3_3;
        } while (var_s3_3 != D_ovl0B_03_8004900C);
        if (var_s4 == 0) {
            func_ovl0B_03_80043060(0);
        } else if (var_s4 == 4) {
            func_ovl0B_03_80043060(1);
        } else {
            func_ovl0B_03_80043060(3);
        }
        func_ovl0B_03_80043010();
        goto block_389;
    case 2:                                         /* switch 1 */
        func_ovl0B_03_800433BC();
        func_ovl0B_03_80043464(D_ovl0B_03_80048C20, 4);
        var_fp_10 = 0;
        do {
            switch (var_fp_10) {                    /* switch 3; irregular */
            default:                                /* switch 3 */
                var_s7_6 = &D_ovl0B_03_80048C90[var_fp_10];
                break;
            case 0:                                 /* switch 3 */
                *D_ovl0B_03_80048AE8 = D_ovl0B_03_8004A324->unk24 + 0x10;
                sp124 = D_ovl0B_03_80048AE8;
                var_s7_6 = &D_ovl0B_03_80048C90[var_fp_10];
                break;
            case 1:                                 /* switch 3 */
                temp_v0_8 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28);
                if (temp_v0_8 == 6) {
                    var_s7_6 = &D_ovl0B_03_80048C90[var_fp_10];
                    sp124 = D_ovl0B_03_80048B60;
                } else {
                    *D_ovl0B_03_80048AF4 = temp_v0_8 + 0x10;
                    sp124 = D_ovl0B_03_80048AF4;
                    var_s7_6 = &D_ovl0B_03_80048C90[var_fp_10];
                }
                break;
            case 2:                                 /* switch 3 */
                temp_v0_9 = D_ovl0B_03_8004A324->unk38;
                sp124 = D_ovl0B_03_80048D00[temp_v0_9];
                if (temp_v0_9 != 0) {
                    var_s7_6 = &D_ovl0B_03_80048C90[var_fp_10];
                    var_s7_6->unk14 = 0;
                } else {
                    var_s7_6 = &D_ovl0B_03_80048C90[var_fp_10];
block_192:
                    var_s7_6->unk14 = 1;
                }
                break;
            case 3:                                 /* switch 3 */
                temp_v0_10 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C);
                sp124 = D_ovl0B_03_80048D00[temp_v0_10];
                if (temp_v0_10 != 0) {
                    var_s7_6 = &D_ovl0B_03_80048C90[var_fp_10];
                    var_s7_6->unk14 = 0;
                } else {
                    var_s7_6 = &D_ovl0B_03_80048C90[var_fp_10];
                    goto block_192;
                }
                break;
            }
            temp_ft2 = (f32) func_ovl0B_03_80043234(sp124, 0.6f) + 42.0f;
            var_a1_3 = (u32) temp_ft2;
            var_fp_10 += 1;
            var_s7_6->unk18 = func_ovl0B_03_80048748(sp124, var_a1_3 & 0xFFFF, var_s7_6->unkA, var_s7_6->unkC, var_s7_6->unk10, var_s7_6->unk14);
        } while (var_fp_10 != 4);
        temp_fp = D_ovl0B_03_8004A324->unk24;
        sp110 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28);
        sp10C = D_ovl0B_03_8004A324->unk38;
        sp108 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C);
        func_ovl0B_03_80048690(func_ovl0B_03_80046850, &spCC, 0x130, 0xC, 0xC);
loop_200:
        func_ovl0B_03_800486E0(1);
        if (D_ovl0B_03_8004A320 == -1) {
            var_s4 = 0;
        } else if (D_ovl0B_03_8004A320 == -2) {
            var_s4 = 0;
            D_ovl0B_03_8004A324->unk24 = temp_fp;
            M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) = sp110;
            D_ovl0B_03_8004A324->unk38 = sp10C;
            M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) = sp108;
        } else if (D_ovl0B_03_8004A320 < 0x10) {
            var_s4 = 0;
        } else {
            temp_s3_6 = (D_ovl0B_03_8004A320 & 0xF) - 1;
            temp_s7 = ((s32) (D_ovl0B_03_8004A320 & 0x30) >> 4) - 1;
            switch (temp_s3_6) {                    /* switch 4; irregular */
            case 0:                                 /* switch 4 */
                if (temp_s7 == 0) {
                    var_t8 = temp_s3_6 * 8;
                    if (D_ovl0B_03_8004A324->unk24 >= 2) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_8004A324->unk24 -= 1;
                        goto block_237;
                    }
                } else {
                    var_t8 = temp_s3_6 * 8;
                    if (temp_s7 == 1) {
                        var_t8 = temp_s3_6 * 8;
                        if (D_ovl0B_03_8004A324->unk24 < 5) {
                            func_ovl0B_03_80048890(0);
                            D_ovl0B_03_8004A324->unk24 += 1;
                        default:                    /* switch 4 */
block_237:
                            var_t8 = temp_s3_6 * 8;
                        }
                    }
                }
                break;
            case 1:                                 /* switch 4 */
                if (temp_s7 == 0) {
                    var_t8 = temp_s3_6 * 8;
                    if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) >= 2) {
                        func_ovl0B_03_80048890(0);
                        M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) = (s32) (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) - 1);
                        goto block_237;
                    }
                } else {
                    var_t8 = temp_s3_6 * 8;
                    if (temp_s7 == 1) {
                        var_t8 = temp_s3_6 * 8;
                        if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) < 6) {
                            func_ovl0B_03_80048890(0);
                            M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) = (s32) (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) + 1);
                            goto block_237;
                        }
                    }
                }
                break;
            case 2:                                 /* switch 4 */
                if (temp_s7 == 0) {
                    var_t8 = temp_s3_6 * 8;
                    if (D_ovl0B_03_8004A324->unk38 > 0) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_8004A324->unk38 -= 1;
                        goto block_237;
                    }
                } else {
                    var_t8 = temp_s3_6 * 8;
                    if (temp_s7 == 1) {
                        var_t8 = temp_s3_6 * 8;
                        if (D_ovl0B_03_8004A324->unk38 <= 0) {
                            func_ovl0B_03_80048890(0);
                            D_ovl0B_03_8004A324->unk38 += 1;
                            goto block_237;
                        }
                    }
                }
                break;
            case 3:                                 /* switch 4 */
                if (temp_s7 == 0) {
                    var_t8 = temp_s3_6 * 8;
                    if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) > 0) {
                        func_ovl0B_03_80048890(0);
                        var_t9_2 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) - 1;
                        goto block_236;
                    }
                } else {
                    var_t8 = temp_s3_6 * 8;
                    if (temp_s7 == 1) {
                        var_t8 = temp_s3_6 * 8;
                        if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) <= 0) {
                            func_ovl0B_03_80048890(0);
                            var_t9_2 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) + 1;
block_236:
                            M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) = var_t9_2;
                            goto block_237;
                        }
                    }
                }
                break;
            }
            temp_s7_2 = ((var_t8 - temp_s3_6) * 4) + D_ovl0B_03_80048C90;
            temp_s4 = M2C_FIELD(temp_s7_2, s32 *, 0x18);
            switch (temp_s3_6) {                    /* switch 5; irregular */
            case 0:                                 /* switch 5 */
                sp124 = D_ovl0B_03_80048AE8;
                *D_ovl0B_03_80048AE8 = D_ovl0B_03_8004A324->unk24 + 0x10;
                break;
            case 1:                                 /* switch 5 */
                temp_v0_11 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28);
                if (temp_v0_11 == 6) {
                    sp124 = D_ovl0B_03_80048B60;
                } else {
                    *D_ovl0B_03_80048AF4 = temp_v0_11 + 0x10;
                    sp124 = D_ovl0B_03_80048AF4;
                }
                break;
            case 2:                                 /* switch 5 */
                temp_v0_12 = D_ovl0B_03_8004A324->unk38;
                sp124 = D_ovl0B_03_80048D00[temp_v0_12];
                if (temp_v0_12 != 0) {
                    M2C_FIELD(temp_s7_2, s32 *, 0x14) = 0;
                } else {
block_252:
                    M2C_FIELD(temp_s7_2, s32 *, 0x14) = 1;
                }
                break;
            case 3:                                 /* switch 5 */
                temp_v0_13 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C);
                sp124 = D_ovl0B_03_80048D00[temp_v0_13];
                if (temp_v0_13 != 0) {
                    M2C_FIELD(temp_s7_2, s32 *, 0x14) = 0;
                } else {
                    goto block_252;
                }
                break;
            }
            temp_ft0 = (f32) func_ovl0B_03_80043234(sp124, 0.6f) + 42.0f;
            var_a1_4 = (u32) temp_ft0;
            M2C_FIELD(temp_s7_2, s32 *, 0x18) = func_ovl0B_03_80048748(sp124, var_a1_4 & 0xFFFF, M2C_FIELD(temp_s7_2, u16 *, 0xA), M2C_FIELD(temp_s7_2, f32 *, 0xC), M2C_FIELD(temp_s7_2, f32 *, 0x10), M2C_FIELD(temp_s7_2, s32 *, 0x14));
            func_ovl0B_03_800486F8(temp_s4);
            func_ovl0B_03_80048350();
            goto loop_200;
        }
        func_ovl0B_03_80043428(D_ovl0B_03_80048C20, 4);
        func_ovl0B_03_80043428(D_ovl0B_03_80048C90, 4);
        func_ovl0B_03_800486A8();
        func_ovl0B_03_80048328(2);
        func_ovl0B_03_80043010();
        goto block_389;
    case 3:                                         /* switch 1 */
    case 4:                                         /* switch 1 */
        func_ovl0B_03_800433BC();
        func_ovl0B_03_80043340(D_ovl0B_03_8004900C, 1, 0x38);
        var_v0_3 = D_ovl0B_03_8004A324;
        var_fp_11 = 0;
loop_261:
        var_t7 = var_fp_11 * 4;
        if (var_v0_3->unk4[0] == 0) {
            var_fp_11 += 1;
            var_v0_3 += 4;
            if (var_fp_11 >= 4) {
                var_t7 = var_fp_11 * 4;
            } else {
                goto loop_261;
            }
        }
        D_ovl0B_03_8004A330 = var_fp_11;
        temp_v1_4 = D_ovl0B_03_80048E9C[var_fp_11].unk10;
        var_fp_12 = 0;
        M2C_FIELD(temp_v1_4, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1_4, s32 *, 0xC) & ~0x40);
        func_ovl0B_03_80043340(D_ovl0B_03_80048DA0, 4, 0x35);
        func_ovl0B_03_80043340(D_ovl0B_03_80049024, 2, 0x130);
        M2C_FIELD(D_ovl0B_03_80049024->unk14, s32 *, 0x38) = 0x12;
        M2C_FIELD(D_ovl0B_03_80049024[1].unk14, s32 *, 0x38) = 0x16;
        func_ovl0B_03_80043464(D_ovl0B_03_80049054, 2);
        var_a1_5 = 0;
        do {
            temp_v0_14 = (u8 *)D_ovl0B_03_8004A324 + var_a1_5;
            if (M2C_FIELD(temp_v0_14, s32 *, 4) == 0) {
                M2C_FIELD(temp_v0_14, s32 *, 0x90) = 0;
            }
            temp_s7_3 = (var_fp_12 * 0x14) + &D_ovl0B_03_80048E9C;
            temp_v0_15 = M2C_FIELD(temp_s7_3, void **, 0x10);
            M2C_FIELD(temp_v0_15, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_15, s32 *, 0xC) & ~1);
            M2C_FIELD(M2C_FIELD(temp_s7_3, void **, 0x10), f32 *, 0x14) = (f32) ((f32) M2C_FIELD(((u8 *)D_ovl0B_03_8004A324 + var_a1_5), s32 *, 0x90) * -70.0f);
            temp_a0 = &D_ovl0B_03_80048DA0[var_fp_12];
            M2C_FIELD(temp_a0->unk14, s32 *, 0x38) = (s32) (M2C_FIELD(((u8 *)D_ovl0B_03_8004A324 + var_a1_5), s32 *, 4) * 2);
            temp_a0->unk4 = ((f32) M2C_FIELD(((u8 *)D_ovl0B_03_8004A324 + var_a1_5), s32 *, 0x90) * 76.0f) + 116.0f;
            func_ovl0B_03_80043170(temp_a0, 1.0f);
            var_fp_12 += 1;
            var_a1_5 += 4;
        } while (var_fp_12 != 4);
        temp_v0_16 = func_ovl0B_03_80047F18(func_ovl0B_03_80046918, 0);
        D_ovl0B_03_8004A3F4 = temp_v0_16;
        M2C_FIELD(temp_v0_16, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_16, s32 *, 0xC) | 0x480);
        D_ovl0B_03_8004A410 = D_ovl0B_03_8004A330 * 0x32;
loop_269:
        temp_s3_7 = func_ovl0B_03_800432F0();
        temp_v0_17 = func_ovl0B_03_800432A0();
        if (temp_s3_7 & 0x200) {
block_271:
            if (D_ovl0B_03_8004A330 > 0) {
                func_ovl0B_03_80048890(0);
                temp_v1_5 = D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10;
                M2C_FIELD(temp_v1_5, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1_5, s32 *, 0xC) | 0x40);
                var_fp_13 = D_ovl0B_03_8004A330 - 1;
                if (var_fp_13 >= 0) {
                    var_v0_4 = (u8 *)D_ovl0B_03_8004A324 + (var_fp_13 * 4);
loop_274:
                    if (M2C_FIELD(var_v0_4, s32 *, 4) == 0) {
                        var_fp_13 -= 1;
                        var_v0_4 -= 4;
                        if (var_fp_13 >= 0) {
                            goto loop_274;
                        }
                    }
                }
                var_t6 = D_ovl0B_03_8004A330 * 4;
                if (var_fp_13 >= 0) {
                    D_ovl0B_03_8004A330 = var_fp_13;
                    var_t6 = D_ovl0B_03_8004A330 * 4;
                }
                temp_v1_6 = D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10;
                M2C_FIELD(temp_v1_6, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1_6, s32 *, 0xC) & ~0x40);
            }
block_311:
            M2C_FIELD(D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10, f32 *, 0x14) = (f32) ((f32) D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] * -70.0f);
            temp_a0_2 = &D_ovl0B_03_80048DA0[D_ovl0B_03_8004A330];
            temp_a0_2->unk4 = ((f32) D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] * 76.0f) + 116.0f;
            func_ovl0B_03_80043170(temp_a0_2, 1.0f);
            D_ovl0B_03_8004A410 = D_ovl0B_03_8004A330 * 0x32;
            func_ovl0B_03_80048350();
            goto loop_269;
        }
        if (temp_v0_17 & 2) {
            goto block_271;
        }
        if (temp_s3_7 & 0x100) {
block_281:
            if (D_ovl0B_03_8004A330 < 3) {
                func_ovl0B_03_80048890(0);
                temp_v1_7 = D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10;
                M2C_FIELD(temp_v1_7, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1_7, s32 *, 0xC) | 0x40);
                var_fp_14 = D_ovl0B_03_8004A330 + 1;
                var_at = var_fp_14 < 4;
                if (var_fp_14 < 4) {
                    var_v0_5 = (u8 *)D_ovl0B_03_8004A324 + (var_fp_14 * 4);
loop_284:
                    var_at = var_fp_14 < 4;
                    if (M2C_FIELD(var_v0_5, s32 *, 4) == 0) {
                        var_fp_14 += 1;
                        var_v0_5 += 4;
                        if (var_fp_14 >= 4) {
                            var_at = var_fp_14 < 4;
                        } else {
                            goto loop_284;
                        }
                    }
                }
                if (var_at != 0) {
                    D_ovl0B_03_8004A330 = var_fp_14;
                }
                temp_v1_8 = D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10;
                M2C_FIELD(temp_v1_8, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v1_8, s32 *, 0xC) & ~0x40);
            }
            goto block_311;
        }
        if (temp_v0_17 & 1) {
            goto block_281;
        }
        if (temp_s3_7 & 0x800) {
block_292:
            if (D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] > 0) {
                func_ovl0B_03_80048890(0);
                D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] -= 1;
            }
            goto block_311;
        }
        var_s7_7 = 0;
        if (temp_v0_17 & 8) {
            goto block_292;
        }
        if (temp_s3_7 & 0x400) {
block_296:
            if (D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] <= 0) {
                func_ovl0B_03_80048890(0);
                D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] += 1;
            }
            goto block_311;
        }
        if (temp_v0_17 & 4) {
            goto block_296;
        }
        var_s3_4 = 0;
        if (temp_v0_17 & 0x8000) {
            var_v0_6 = D_ovl0B_03_8004A324;
            var_a1_6 = 0;
            do {
                var_a1_6 += 4;
                if (var_v0_6->unk4[0] != 0) {
                    if (var_v0_6->unk90[0] != 0) {
                        var_s7_7 += 1;
                    } else {
                        var_s3_4 += 1;
                    }
                }
                var_v0_6 += 4;
            } while (var_a1_6 != 0x10);
            if ((var_s7_7 != 0) && (var_s4 = 5, (var_s3_4 != 0))) {
                func_ovl0B_03_80048890(1);
            } else {
                func_ovl0B_03_80048890(0x18);
                goto block_311;
            }
        } else if (temp_v0_17 & 0x4000) {
            var_s4 = 1;
            func_ovl0B_03_80048890(2);
        } else {
            goto block_311;
        }
        if (var_s4 == 1) {
            func_ovl0B_03_80043060(0);
        } else {
            func_ovl0B_03_80043060(1);
        }
        M2C_FIELD(D_ovl0B_03_80048E9C[0].unk10, s32 *, 0xC) = (s32) (M2C_FIELD(D_ovl0B_03_80048E9C[0].unk10, s32 *, 0xC) | 0x41);
        M2C_FIELD(D_ovl0B_03_80048E9C[0].unk10, f32 *, 0x14) = -10.0f;
        D_ovl0B_03_80048DA0[0].unk4 = 170.0f;
        M2C_FIELD(D_ovl0B_03_80048E9C[1].unk10, s32 *, 0xC) = (s32) (M2C_FIELD(D_ovl0B_03_80048E9C[1].unk10, s32 *, 0xC) | 0x41);
        M2C_FIELD(D_ovl0B_03_80048E9C[1].unk10, f32 *, 0x14) = -10.0f;
        D_ovl0B_03_80048DA0[1].unk4 = 170.0f;
        M2C_FIELD(D_ovl0B_03_80048E9C[2].unk10, s32 *, 0xC) = (s32) (M2C_FIELD(D_ovl0B_03_80048E9C[2].unk10, s32 *, 0xC) | 0x41);
        M2C_FIELD(D_ovl0B_03_80048E9C[2].unk10, f32 *, 0x14) = -10.0f;
        D_ovl0B_03_80048DA0[2].unk4 = 170.0f;
        M2C_FIELD(D_ovl0B_03_80048E9C[3].unk10, s32 *, 0xC) = (s32) (M2C_FIELD(D_ovl0B_03_80048E9C[3].unk10, s32 *, 0xC) | 0x41);
        M2C_FIELD(D_ovl0B_03_80048E9C[3].unk10, f32 *, 0x14) = -10.0f;
        D_ovl0B_03_80048DA0[3].unk4 = 170.0f;
        func_ovl0B_03_80043428(D_ovl0B_03_80049054, 2);
        func_ovl0B_03_80043134(D_ovl0B_03_80049024, 2);
        func_ovl0B_03_80043134(D_ovl0B_03_8004900C, 1);
        func_ovl0B_03_80043134(D_ovl0B_03_80048DA0, 4);
        func_ovl0B_03_80047EA0((UnkStructA_40 *) D_ovl0B_03_8004A3F4);
        func_ovl0B_03_80043010();
        goto block_389;
    case 5:                                         /* switch 1 */
        func_ovl0B_03_800433BC();
        temp_v0_18 = func_ovl0B_03_80047E98(D_ovl0B_03_8004908C[D_ovl0B_03_8004A324->unkA0], 0);
        D_ovl0B_03_8004A334 = temp_v0_18;
        temp_v0_18->unkC |= 0x10000;
        D_ovl0B_03_8004A334->unk10 = D_ovl0B_03_800490DC[D_ovl0B_03_8004A324->unkA0] + -921.0f;
        D_ovl0B_03_8004A334->unk14 = 400.0f;
        D_ovl0B_03_8004A334->unk18 = -2000.0f;
        D_ovl0B_03_8004A334->unk1C = 50.0f;
        D_ovl0B_03_8004A334->unk30 = 0.4f;
        temp_fv0_2 = D_ovl0B_03_8004A334->unk30;
        D_ovl0B_03_8004A334->unk2C = temp_fv0_2;
        D_ovl0B_03_8004A334->unk28 = temp_fv0_2;
        temp_t0_2 = D_ovl0B_03_8004A324;
        temp_a0_3 = D_ovl0B_03_800490B4[temp_t0_2->unkA0];
        if (temp_a0_3 != -1) {
            var_fs1_3 = 0.0f;
            temp_v0_19 = func_ovl0B_03_80047E98(temp_a0_3, 0);
            D_ovl0B_03_8004A338 = temp_v0_19;
            temp_v0_19->unkC |= 0x10000;
            D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
            D_ovl0B_03_8004A338->unk14 = D_ovl0B_03_8004A334->unk14;
            D_ovl0B_03_8004A338->unk18 = D_ovl0B_03_8004A334->unk18;
            D_ovl0B_03_8004A338->unk1C = D_ovl0B_03_8004A334->unk1C;
            temp_fa0 = D_ovl0B_03_8004A334->unk28;
            D_ovl0B_03_8004A338->unk30 = temp_fa0;
            D_ovl0B_03_8004A338->unk2C = temp_fa0;
            D_ovl0B_03_8004A338->unk28 = temp_fa0;
        } else {
            var_fs1_3 = 0.0f;
            D_ovl0B_03_8004A338 = NULL;
        }
        var_s7_8 = func_ovl0B_03_80048748(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], func_ovl0B_03_80043234(D_ovl0B_03_80049194[temp_t0_2->unkA0], 1.0f) & 0xFFFF, 0xB4U, 1.0f, 1.0f, 2);
        func_ovl0B_03_80043340(D_ovl0B_03_80048E6C, 2, 0x39);
        M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x1C) = 130.0f;
        D_ovl0B_03_80048E6C->unk0 = 70.0f;
        D_ovl0B_03_80048E6C->unk4 = M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x1C);
        M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x18) = 250.0f;
loop_320:
        temp_s3_8 = func_ovl0B_03_800432F0();
        temp_v0_20 = func_ovl0B_03_800432A0();
        if (D_ovl0B_03_8004A324->unkA0 == 0) {
            M2C_FIELD(D_ovl0B_03_80048E6C[0].unk14, s32 *, 0xC) = (s32) (M2C_FIELD(D_ovl0B_03_80048E6C[0].unk14, s32 *, 0xC) | 1);
        } else {
            M2C_FIELD(D_ovl0B_03_80048E6C[0].unk14, s32 *, 0xC) = (s32) (M2C_FIELD(D_ovl0B_03_80048E6C[0].unk14, s32 *, 0xC) & ~1);
        }
        if (sp104 == D_ovl0B_03_8004A324->unkA0) {
            M2C_FIELD(D_ovl0B_03_80048E84[0].unk14, s32 *, 0xC) = (s32) (M2C_FIELD(D_ovl0B_03_80048E84[0].unk14, s32 *, 0xC) | 1);
        } else {
            M2C_FIELD(D_ovl0B_03_80048E84[0].unk14, s32 *, 0xC) = (s32) (M2C_FIELD(D_ovl0B_03_80048E84[0].unk14, s32 *, 0xC) & ~1);
        }
        if (temp_s3_8 & 0x200) {
            if (D_ovl0B_03_8004A324->unkA0 > 0) {
                func_ovl0B_03_80048890(0);
                var_fp_15 = 0;
                D_ovl0B_03_8004A324->unkA0 -= 1;
                do {
                    D_ovl0B_03_8004A334->unk10 += 125.0f;
                    if (D_ovl0B_03_8004A338 != NULL) {
                        D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                    }
                    func_ovl0B_03_80048350();
                    var_fp_15 += 1;
                } while (var_fp_15 < 0xA);
                func_ovl0B_03_80047EA0(D_ovl0B_03_8004A334);
                if (D_ovl0B_03_8004A338 != NULL) {
                    func_ovl0B_03_80047EA0(D_ovl0B_03_8004A338);
                }
                temp_v0_21 = func_ovl0B_03_80047E98(D_ovl0B_03_8004908C[D_ovl0B_03_8004A324->unkA0], 0);
                D_ovl0B_03_8004A334 = temp_v0_21;
                temp_v0_21->unkC |= 0x10000;
                D_ovl0B_03_8004A334->unk10 = D_ovl0B_03_800490DC[D_ovl0B_03_8004A324->unkA0] + -2171.0f;
                D_ovl0B_03_8004A334->unk14 = 400.0f;
                D_ovl0B_03_8004A334->unk18 = -2000.0f;
                D_ovl0B_03_8004A334->unk1C = 50.0f;
                D_ovl0B_03_8004A334->unk30 = 0.4f;
                temp_fv0_3 = D_ovl0B_03_8004A334->unk30;
                D_ovl0B_03_8004A334->unk2C = temp_fv0_3;
                D_ovl0B_03_8004A334->unk28 = temp_fv0_3;
                temp_t0_3 = D_ovl0B_03_8004A324;
                temp_a0_4 = D_ovl0B_03_800490B4[temp_t0_3->unkA0];
                if (temp_a0_4 != -1) {
                    temp_v0_22 = func_ovl0B_03_80047E98(temp_a0_4, 0);
                    D_ovl0B_03_8004A338 = temp_v0_22;
                    temp_v0_22->unkC |= 0x10000;
                    D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                    D_ovl0B_03_8004A338->unk14 = D_ovl0B_03_8004A334->unk14;
                    D_ovl0B_03_8004A338->unk18 = D_ovl0B_03_8004A334->unk18;
                    D_ovl0B_03_8004A338->unk1C = D_ovl0B_03_8004A334->unk1C;
                    temp_fa0_2 = D_ovl0B_03_8004A334->unk28;
                    D_ovl0B_03_8004A338->unk30 = temp_fa0_2;
                    D_ovl0B_03_8004A338->unk2C = temp_fa0_2;
                    D_ovl0B_03_8004A338->unk28 = temp_fa0_2;
                } else {
                    D_ovl0B_03_8004A338 = NULL;
                }
                temp_fp_2 = var_s7_8;
                var_s7_8 = func_ovl0B_03_80048748(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], func_ovl0B_03_80043234(D_ovl0B_03_80049194[temp_t0_3->unkA0], 1.0f) & 0xFFFF, 0xB4U, 1.0f, 1.0f, 2);
                func_ovl0B_03_800486F8(temp_fp_2);
                var_fp_16 = 0;
                do {
                    D_ovl0B_03_8004A334->unk10 += 125.0f;
                    if (D_ovl0B_03_8004A338 != NULL) {
                        D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                    }
                    func_ovl0B_03_80048350();
                    var_fp_16 += 1;
                } while (var_fp_16 != 0xA);
            }
block_370:
            if (var_fs1_3 >= 360.0f) {
                var_fa0_5 = var_fs1_3 - 360.0f;
            } else {
                if (var_fs1_3 < 0.0f) {
                    var_fs4_5 = var_fs1_3 + 360.0f;
                } else {
                    var_fs4_5 = var_fs1_3;
                }
                var_fa0_5 = var_fs4_5;
            }
            func_ovl0B_03_80043170(D_ovl0B_03_80048E6C, (func_ovl0B_03_800484B8(var_fa0_5) * 0.05f) + 1.0f);
            if (var_fs1_3 >= 360.0f) {
                var_fa0_6 = var_fs1_3 - 360.0f;
            } else {
                if (var_fs1_3 < 0.0f) {
                    var_fs4_6 = var_fs1_3 + 360.0f;
                } else {
                    var_fs4_6 = var_fs1_3;
                }
                var_fa0_6 = var_fs4_6;
            }
            func_ovl0B_03_80043170(D_ovl0B_03_80048E84, (func_ovl0B_03_800484B8(var_fa0_6) * 0.05f) + 1.0f);
            var_fs1_3 += 4.0f;
            func_ovl0B_03_80048350();
            goto loop_320;
        }
        if (temp_s3_8 & 0x100) {
            if (D_ovl0B_03_8004A324->unkA0 < sp104) {
                func_ovl0B_03_80048890(0);
                var_fp_17 = 0;
                D_ovl0B_03_8004A324->unkA0 += 1;
                do {
                    D_ovl0B_03_8004A334->unk10 -= 125.0f;
                    if (D_ovl0B_03_8004A338 != NULL) {
                        D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                    }
                    func_ovl0B_03_80048350();
                    var_fp_17 += 1;
                } while (var_fp_17 < 0xA);
                func_ovl0B_03_80047EA0(D_ovl0B_03_8004A334);
                if (D_ovl0B_03_8004A338 != NULL) {
                    func_ovl0B_03_80047EA0(D_ovl0B_03_8004A338);
                }
                temp_v0_23 = func_ovl0B_03_80047E98(D_ovl0B_03_8004908C[D_ovl0B_03_8004A324->unkA0], 0);
                D_ovl0B_03_8004A334 = temp_v0_23;
                temp_v0_23->unkC |= 0x10000;
                D_ovl0B_03_8004A334->unk10 = D_ovl0B_03_800490DC[D_ovl0B_03_8004A324->unkA0] + 329.0f;
                D_ovl0B_03_8004A334->unk14 = 400.0f;
                D_ovl0B_03_8004A334->unk18 = -2000.0f;
                D_ovl0B_03_8004A334->unk1C = 50.0f;
                D_ovl0B_03_8004A334->unk30 = 0.4f;
                temp_fv0_4 = D_ovl0B_03_8004A334->unk30;
                D_ovl0B_03_8004A334->unk2C = temp_fv0_4;
                D_ovl0B_03_8004A334->unk28 = temp_fv0_4;
                temp_t0_4 = D_ovl0B_03_8004A324;
                temp_a0_5 = D_ovl0B_03_800490B4[temp_t0_4->unkA0];
                if (temp_a0_5 != -1) {
                    D_ovl0B_03_8004A338 = func_ovl0B_03_80047E98(temp_a0_5, 0);
                    D_ovl0B_03_8004A338->unkC |= 0x10000;
                    D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                    D_ovl0B_03_8004A338->unk14 = D_ovl0B_03_8004A334->unk14;
                    D_ovl0B_03_8004A338->unk18 = D_ovl0B_03_8004A334->unk18;
                    D_ovl0B_03_8004A338->unk1C = D_ovl0B_03_8004A334->unk1C;
                    temp_fa0_3 = D_ovl0B_03_8004A334->unk28;
                    D_ovl0B_03_8004A338->unk30 = temp_fa0_3;
                    D_ovl0B_03_8004A338->unk2C = temp_fa0_3;
                    D_ovl0B_03_8004A338->unk28 = temp_fa0_3;
                } else {
                    D_ovl0B_03_8004A338 = NULL;
                }
                temp_fp_3 = var_s7_8;
                var_s7_8 = func_ovl0B_03_80048748(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], func_ovl0B_03_80043234(D_ovl0B_03_80049194[temp_t0_4->unkA0], 1.0f) & 0xFFFF, 0xB4U, 1.0f, 1.0f, 2);
                func_ovl0B_03_800486F8(temp_fp_3);
                var_fp_18 = 0;
                do {
                    D_ovl0B_03_8004A334->unk10 -= 125.0f;
                    if (D_ovl0B_03_8004A338 != NULL) {
                        D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                    }
                    func_ovl0B_03_80048350();
                    var_fp_18 += 1;
                } while (var_fp_18 != 0xA);
            }
            goto block_370;
        }
        if (temp_v0_20 & 0x8000) {
            func_ovl0B_03_80048890(0x25);
            func_ovl0B_03_80047EA0(D_ovl0B_03_8004A334);
            if (D_ovl0B_03_8004A338 != NULL) {
                func_ovl0B_03_80047EA0(D_ovl0B_03_8004A338);
            }
            var_s4 = 6;
            func_ovl0B_03_800486F8(var_s7_8);
            D_ovl0B_03_8004A324->unkA4[0] = 0;
            D_ovl0B_03_8004A324->unkA4[1] = 0;
            D_ovl0B_03_8004A324->unkA4[2] = 0;
            D_ovl0B_03_8004A324->unkA4[3] = 0;
            func_ovl0B_03_800431FC();
            func_ovl0B_03_800478B0(D_ovl0B_03_8004A324->unkA0 + 0x90, 0x10, 0);
        } else if (temp_v0_20 & 0x4000) {
            func_ovl0B_03_80048890(2);
            func_ovl0B_03_80047EA0(D_ovl0B_03_8004A334);
            if (D_ovl0B_03_8004A338 != NULL) {
                func_ovl0B_03_80047EA0(D_ovl0B_03_8004A338);
            }
            func_ovl0B_03_800486F8(var_s7_8);
            if (D_ovl0B_03_8004A324->unk0 == 0) {
                var_s4 = 1;
            } else {
                var_s4 = 4;
            }
        } else {
            goto block_370;
        }
        func_ovl0B_03_80043134(D_ovl0B_03_80048E6C, 2);
        if (var_s4 == 4) {
            func_ovl0B_03_80043060(0);
        } else if (var_s4 != 6) {
            func_ovl0B_03_80043060(2);
        }
        func_ovl0B_03_80043010();
        goto block_389;
    }
}

/* Fades n boxes' objects to alpha (0xF1 and over: opaque). */
static void func_ovl0B_03_800436EC(s32 n, Box_ovl0B_03 *boxes, s32 alpha) {
    s32 i;

    for (i = 0; i < n; i++) {
        boxes[i].unk14->unkC |= 0x80;
        if (alpha >= 0xF1) {
            boxes[i].unk14->unk36 = -1;
            boxes[i].unk14->unkC &= ~0x80;
        } else {
            boxes[i].unk14->unk36 = alpha;
        }
    }
}

/* The original passes obj in $s2 and vals in $s1. */
static void func_ovl0B_03_8004368C(s32 obj, s32 *vals) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (vals == NULL) {
            func_ovl0B_03_80047960(obj, i, 0);
        } else {
            func_ovl0B_03_80047960(obj, i, vals[i]);
        }
    }
}

static void func_ovl0B_03_800434BC(void) {
    s32 i;
    s32 j;
    s32 mode;
    u32 frame;

    for (i = 0; i < 4; i++) {
        mode = D_ovl0B_03_8004A324->unk4[i];
        if (mode != 0 && (func_ovl0B_03_800483D8(i) & 8)) {
            D_ovl0B_03_8004A324->unk4[i] = 2;
            mode = 2;
        }
        frame = mode * 2;
        if (mode == 1) {
            D_ovl0B_03_80048DA0[i + 4].unk14->unkC &= ~1;
            if (D_ovl0B_03_8004A324->unk40[i] == 1) {
                D_ovl0B_03_80048DA0[i + 4].unk14->unkC &= ~0x80;
            } else {
                D_ovl0B_03_80048DA0[i + 4].unk14->unkC |= 0x80;
                D_ovl0B_03_80048DA0[i + 4].unk14->unk36 = 0x80;
            }
        } else {
            D_ovl0B_03_80048DA0[i + 4].unk14->unkC |= 1;
        }
        M2C_FIELD(D_ovl0B_03_80048DA0[i].unk14, s32 *, 0x38) = frame;
        M2C_FIELD(D_ovl0B_03_80048DA0[i + 4].unk14, s32 *, 0x38) = 6;
        for (j = 0; j < 3; j++) {
            D_ovl0B_03_80048EEC[i * 3 + j].unk14->unkC |= 1;
        }
        if (frame == 4) {
            for (j = 0; j < 3; j++) {
                if (M2C_FIELD((u8 *)D_ovl0B_03_8004A324 + i * 4, s32 *, 0x14) >= j) {
                    D_ovl0B_03_80048EEC[i * 3 + j].unk14->unkC &= ~1;
                }
            }
        }
    }
}

/* The original passes n in $s2. */
static void func_ovl0B_03_80043464(Label_ovl0B_03 *labels, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        labels[i].unk18 = func_ovl0B_03_80048748(labels[i].unk0, labels[i].unk6, labels[i].unkA, labels[i].unkC,
                                                 labels[i].unk10, labels[i].unk14);
    }
}

/* The original passes n in $s2. */
static void func_ovl0B_03_80043428(Label_ovl0B_03 *labels, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0B_03_800486F8(labels[i].unk18);
    }
}

static void func_ovl0B_03_800433BC(void) {
    UnkStructA_40 *temp_v0;
    s32 var_s0;

    D_ovl0B_03_8004A3F8 = func_ovl0B_03_80047F18(func_ovl0B_03_80047064, -1);
    D_ovl0B_03_8004A3F8->unkC |= 0x480;
    var_s0 = 5;
    do {
        D_ovl0B_03_8004A414 = var_s0;
        func_ovl0B_03_80048350();
        var_s0 += 0xA;
    } while (var_s0 != 0x73);
    func_ovl0B_03_80048350();
}

/* The original takes n in $s4 and the model in $s5. */
static void func_ovl0B_03_80043340(Box_ovl0B_03 *boxes, s32 n, s32 model) {
    s32 i;

    for (i = 0; i < n; i++) {
        boxes[i].unk14 = func_ovl0B_03_80047E98(model, 0);
        M2C_FIELD(boxes[i].unk14, s32 *, 0x38) = i * 2;
        boxes[i].unk14->unkC &= ~1;
        func_ovl0B_03_80043170(&boxes[i], boxes[i].unk10);
    }
}

static s32 func_ovl0B_03_800432F0(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = 0;
    do {
        if (!(func_ovl0B_03_800483D8(var_s0) & 8)) {
            var_s1 |= func_ovl0B_03_800486D8(var_s0);
        }
        var_s0 += 1;
    } while (var_s0 != 4);
    return var_s1;
}

static s32 func_ovl0B_03_800432A0(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = 0;
    do {
        if (!(func_ovl0B_03_800483D8(var_s0) & 8)) {
            var_s1 |= func_ovl0B_03_800483E8(var_s0);
        }
        var_s0 += 1;
    } while (var_s0 != 4);
    return var_s1;
}

/* The original takes the scale in $f20 (its callers' register). */
static s32 func_ovl0B_03_80043234(u8 *str, f32 scale) {
    return (320.0f - func_ovl0B_03_80048740(str) * scale) / 2;
}

/* The original takes the scale in $f12. */
static void func_ovl0B_03_80043170(Box_ovl0B_03 *box, f32 scale) {
    box->unk10 = scale;
    box->unk14->unk10 = box->unk0 - box->unk8 * scale * 0.5f;
    box->unk14->unk14 = box->unk4 - box->unkC * box->unk10 * 0.5f;
    box->unk14->unk18 = box->unk14->unk10 + box->unk8 * box->unk10;
    box->unk14->unk1C = box->unk14->unk14 + box->unkC * box->unk10;
}

/* The original passes n in $s2 (its callers' register). */
static void func_ovl0B_03_80043134(Box_ovl0B_03 *boxes, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0B_03_80047EA0(boxes[i].unk14);
    }
}

static void func_ovl0B_03_80043010(void) {
    s32 var_s0;

    var_s0 = 0x6E;
    do {
        D_ovl0B_03_8004A414 = var_s0;
        func_ovl0B_03_80048350();
        var_s0 -= 0xA;
    } while (var_s0 != 0);
    func_ovl0B_03_80047EA0(D_ovl0B_03_8004A3F8);
    func_ovl0B_03_80048350();
}
