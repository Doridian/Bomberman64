/*
 * NON_MATCHING: ovl_0B_02's game object (a picture book of six groups of
 * models turned page by page, with a timer, a set of option boxes and the
 * groups' background tasks; the ending's camera move 80045C30), complete:
 * every function and its data (.data 0x8E0 as the original, the last 0x60
 * of it 800431C4's local table). Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 3418, eu ?, jp ?
 * jp has no `#if VERSION_JP` yet.
 *
 * A first draft from m2c (with a context of the ZeroJump prototypes the
 * other drafts give the same codes), every function rewritten by hand:
 * the logic is the original's, the big functions' schedules aren't.
 * Source order is the reverse of the address order. The statics take
 * arguments in their callers' registers: 80043018 and 800443DC (n in $s2),
 * 80043150 ($s2, $s3), 80043054 and 80043F4C (i in $s1), 80043EF8 ($a1,
 * with an unused first parameter), 800430C4 ($f12), 80044424 ($f20);
 * 800472C0 and 80043FC4 are static too (they use saved registers their
 * callers save, so the handler saves $s0-$fp and $f20-$f27). The 22 stubs
 * (two `jr ra` in a row): 80043010, 80043FBC, 800443D4 and 800472A0-B8 are
 * inlined-once statics before their callers; 80047C14-80047C7C are the 14
 * unused stubs after the tail, and the four group tasks in
 * D_ovl0B_02_8004A150 (80047C84-800481E8, static, referred to only from
 * .data) come out after them in definition order, then 800482D0 (it
 * stores to the unreferenced .bss to keep it out of common).
 * 800470B0/800471A8 are ovl_0B_03's 80046E8C/80046F78 (a loop test against
 * an int 0); 80043018-80043150 and 80044424 are ovl_0B_03's
 * 80043134-80043340 and 80043234 with a 0x20-byte box; 80046418 is
 * ovl_12_05's 80046990.
 *
 * Many of the differing words are the sign of a relocated %lo: the
 * .data and .rodata addresses only come right once .text has the
 * original's size. .rodata is 0x10 short.
 *
 * What still differs in us (words):
 * - 800431C4 712: 0xA0 bytes too long.
 * - 80043E10 296: with the statics after it (80043EF8-80044424); 80044424
 *   is inlined into both its callers here (8 bytes where the original has
 *   0x6C), whether static, defined above its caller or called from a dead
 *   static; 80043FC4 is 0x18 bytes too long.
 * - 80044490 1064: 0x10C too long (80044424's two inlined copies are part).
 * - 800454F0 407, 80046B8C 117 (0xC short), 80046EFC 38 (registers),
 *   80046100 20 (8 long), 800469C8 9, 80046418 4, 80045C30 3.
 * - 800471A8 374: with 800472A0-800472C0 (800472C0 0x10 too long).
 * - 800478EC 48 (4 bytes long); 80047BFC 326: with the stubs and the four
 *   group tasks (80047C84 0xC long, 80047E98 0xC short, 800481E8 8 short).
 * - 80043010-80043150, 80045F10-80046014, 80046258, 800462C8,
 *   800467D0-800468C4, 80047020, 800470B0, 80047B24-80047BA0 match.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

#define ANGLE_ADD(a, d) \
    (a) = ((a) + (d) >= 360.0f) ? (a) + (d) - 360.0f : ((a) + (d) < 0.0f) ? (a) + (d) + 360.0f : (a) + (d)
#define ANGLE_SUB(a, d) \
    (a) = ((a) - (d) >= 360.0f) ? (a) - (d) - 360.0f : ((a) < (d)) ? (a) - (d) + 360.0f : (a) - (d)
#define WRAP(x) ((x) >= 360.0f ? (x) - 360.0f : (x) < 0.0f ? (x) + 360.0f : (x))

typedef struct {
    u32 w0;
    u32 w1;
} Gfx_ovl0B_02;

/* A box: its centre, its size, its scale, the model and frame, and the
 * object drawing it. */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ UnkStructA_40 *unk1C;
} Box_ovl0B_02;

/* A model at a place, and its object. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ UnkStructA_40 *unk10;
} Model_ovl0B_02;

/* A piece of a group: its model, place, object, frame, colour, angles and
 * scale. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ UnkStructA_40 *unk10;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
} Piece_ovl0B_02;

/* A group of pieces and the angle steps between its pages. */
typedef struct {
    /* 0x0 */ Piece_ovl0B_02 *unk0;
    /* 0x4 */ f32 (*unk4)[2];
    /* 0x8 */ s32 unk8;
} Group_ovl0B_02;

/* What func_ovl0B_02_80048778 returns. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x2C];
    /* 0x38 */ s32 unk38;
} Save_ovl0B_02;

s32 func_ovl0B_02_800482F0(u8 *, const char *, s32); /* 0x101 */
void func_ovl0B_02_80048720(s32, s32, s32); /* 0xF00 */
s32 func_ovl0B_02_80048728(void); /* 0xF01 */
s32 func_ovl0B_02_80048738(void); /* 0xF03 */
Save_ovl0B_02 *func_ovl0B_02_80048778(void); /* 0xF0B */
void func_ovl0B_02_80048788(void); /* 0xF0D */
void func_ovl0B_02_80048790(s32); /* 0xF0E */
u32 func_ovl0B_02_80048CF8(s32); /* 0x1400 */
void func_ovl0B_02_80048D00(s32); /* 0x1401 */
UnkStructA_40 *func_ovl0B_02_80048D08(s32, s32); /* 0x1500 */
void func_ovl0B_02_80048D10(UnkStructA_40 *); /* 0x1501 */
f32 func_ovl0B_02_80048D68(UnkStructA_40 *, s32); /* 0x150C */
UnkStructA_40 *func_ovl0B_02_80048D88(void (*)(UnkStructA_40 *, Gfx_ovl0B_02 **), s32); /* 0x1510 */
s32 func_ovl0B_02_80048D98(UnkStructA_40 *, s32); /* 0x1512 */
void func_ovl0B_02_80048DA0(s32, s32, s32); /* 0x1513 */
void func_ovl0B_02_80048DA8(s32); /* 0x1514 */
void func_ovl0B_02_80048E48(s32); /* 0x1700 */
void func_ovl0B_02_80048E58(s32); /* 0x1702 */
void func_ovl0B_02_80048E68(f32, f32, f32); /* 0x1704 */
void func_ovl0B_02_80048E88(f32, f32, f32); /* 0x1708 */
void func_ovl0B_02_80048E90(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0B_02_80048ED0(s32); /* 0x1711 */
void func_ovl0B_02_80049020(s32); /* 0x1810 */
void func_ovl0B_02_80049028(UnkStructA *, s32); /* 0x1811 */
void func_ovl0B_02_80049040(UnkStructA *); /* 0x1814 */
UnkStructA *func_ovl0B_02_80049050(s32, s32, s32, UnkStructA *); /* 0x1816 */
s32 func_ovl0B_02_80049178(void (*)(), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0B_02_80049180(s32); /* 0x1901 */
void func_ovl0B_02_80049188(void); /* 0x1902 */
void func_ovl0B_02_80049198(s32); /* 0x1904 */
void *func_ovl0B_02_800491A0(void); /* 0x1905 */
s32 func_ovl0B_02_800491C0(void); /* 0x1909 */
UnkStructC *func_ovl0B_02_80049200(s32); /* 0x1A00 */
void func_ovl0B_02_80049210(UnkStructC *, s32); /* 0x1A02 */
f32 func_ovl0B_02_80049320(f32); /* 0x1D00 */
f32 func_ovl0B_02_80049328(f32); /* 0x1D01 */
f64 func_ovl0B_02_80049330(void); /* 0x1D02 */
s32 func_ovl0B_02_80049338(s32); /* 0x1D03 */
void func_ovl0B_02_80049340(f32, f32); /* 0x1D04 */
s32 func_ovl0B_02_800493E0(s32); /* 0x1E04 */
s32 (*func_ovl0B_02_80049410(s32))[4]; /* 0x1E0A */
void func_ovl0B_02_80049470(void); /* 0x2003 */
void func_ovl0B_02_80049480(s32, s32, s32, s32); /* 0x2005 */
void func_ovl0B_02_80049490(s32, s32, s32, s32); /* 0x2007 */
UnkStructA_40 *func_ovl0B_02_80049500(s32 (*)(u8, u16), void *, s32, s32, s32); /* 0x2400 */
void func_ovl0B_02_80049518(void); /* 0x2403 */
void func_ovl0B_02_80049520(void); /* 0x2404 */
s32 func_ovl0B_02_80049530(void); /* 0x2406 */
void func_ovl0B_02_80049568(s32); /* 0x2502 */
s32 func_ovl0B_02_800495B0(u8 *); /* 0x250B */
s32 func_ovl0B_02_800495B8(u8 *, u16, u16, f32, f32, s32); /* 0x250C */
void func_ovl0B_02_800495C8(s32, f32, f32, f32, s32); /* 0x2600 */
void func_ovl0B_02_800495E0(void); /* 0x2603 */
void func_ovl0B_02_80049700(s32); /* 0x2B00 */
void func_ovl0B_02_80049710(s32); /* 0x2B02 */
void func_ovl0B_02_80049718(void); /* 0x2B03 */
void func_ovl0B_02_80049720(s32, f32, f32, f32); /* 0x2B04 */
void func_ovl0B_02_80049840(void); /* 0x2F0A */

/* .bss */
u8 D_ovl0B_02_8004A380[0x1C]; /* not referenced here */
s32 D_ovl0B_02_8004A39C[2];
s32 D_ovl0B_02_8004A3A4[2];
u8 D_ovl0B_02_8004A3AC[4];
s32 D_ovl0B_02_8004A3B0;
s32 D_ovl0B_02_8004A3B4;
Vec3f D_ovl0B_02_8004A3B8;
s32 D_ovl0B_02_8004A3C4;
s32 D_ovl0B_02_8004A3C8;
s32 D_ovl0B_02_8004A3CC;
s32 D_ovl0B_02_8004A3D0;
s32 D_ovl0B_02_8004A3D4;
s32 D_ovl0B_02_8004A3D8;
s32 D_ovl0B_02_8004A3DC;
Save_ovl0B_02 *D_ovl0B_02_8004A3E0;
s32 D_ovl0B_02_8004A3E4;
UnkStructA_40 *D_ovl0B_02_8004A3E8[2];
UnkStructA_40 *D_ovl0B_02_8004A3F0[20];
s32 D_ovl0B_02_8004A440;
s32 D_ovl0B_02_8004A444;
s32 D_ovl0B_02_8004A448;
s32 D_ovl0B_02_8004A44C;
UnkStructC *D_ovl0B_02_8004A450[4];

void func_ovl0B_02_80044490(void);
void func_ovl0B_02_800431C4(void);
void func_ovl0B_02_80043E10(void);
void func_ovl0B_02_800454F0(void);
void func_ovl0B_02_80045C30(void);
void func_ovl0B_02_80045F10(void);
void func_ovl0B_02_80045F58(void);
void func_ovl0B_02_80046014(void);
void func_ovl0B_02_80046100(void);
s32 func_ovl0B_02_80046258(u8 arg0, u16 arg1);
void func_ovl0B_02_800462C8(void);
void func_ovl0B_02_80046418(void);
void func_ovl0B_02_800467D0(void);
void func_ovl0B_02_8004686C(void);
void func_ovl0B_02_800468C4(void);
void func_ovl0B_02_800469C8(void);
void func_ovl0B_02_80046B8C(void);
void func_ovl0B_02_80046EFC(UnkStructA_40 *arg0, Gfx_ovl0B_02 **arg1);
void func_ovl0B_02_80047020(void);
void func_ovl0B_02_800470B0(void);
void func_ovl0B_02_800471A8(void);
static void func_ovl0B_02_800472C0(void);
static void func_ovl0B_02_80047C84(void);
static void func_ovl0B_02_80047E98(void);
static void func_ovl0B_02_80048018(void);
static void func_ovl0B_02_800481E8(void);

/* .data */
u8 D_ovl0B_02_80049920[0xC] = { 0x2A, 0x4E, 0x42, 0x4D, 0x0F, 0x20, 0x3A, 0x46, 0x3E, 0xF7, 0x00, 0x00 };
u8 D_ovl0B_02_8004992C[0xC] = { 0x0F, 0x27, 0x28, 0x0F, 0x0F, 0x0F, 0x0F, 0x32, 0x1E, 0x2C, 0x00, 0x00 };
u8 D_ovl0B_02_80049938[0xC] = { 0x29, 0x45, 0x3A, 0x52, 0x0F, 0x2D, 0x42, 0x46, 0x3E, 0x00, 0x00, 0x00 };
u8 D_ovl0B_02_80049944[0xC] = { 0x10, 0x10, 0x41, 0xF8, 0x10, 0x10, 0x46, 0xF8, 0x00, 0x00, 0x00, 0x00 };
Box_ovl0B_02 D_ovl0B_02_80049950[5] = {
    { 79.0f, 44.0f, 90.0f, 40.0f, 1.0f, 0x37, 2, NULL },
    { 50.0f, 110.0f, 20.0f, 20.0f, 1.0f, 0x39, 0, NULL },
    { 270.0f, 110.0f, 20.0f, 20.0f, 1.0f, 0x39, 2, NULL },
    { 160.0f, 50.0f, 20.0f, 20.0f, 1.0f, 0x39, 4, NULL },
    { 160.0f, 170.0f, 20.0f, 20.0f, 1.0f, 0x39, 6, NULL }
};
Box_ovl0B_02 D_ovl0B_02_800499F0[3] = {
    { 79.0f, 44.0f, 90.0f, 40.0f, 1.0f, 0x37, 4, NULL },
    { 174.0f, 201.0f, 20.0f, 20.0f, 1.0f, 0x39, 0, NULL },
    { 299.0f, 201.0f, 20.0f, 20.0f, 1.0f, 0x39, 2, NULL }
};
Model_ovl0B_02 D_ovl0B_02_80049A50[2] = {
    { 0x27, 120.0f, -950.0f, -1160.0f, NULL },
    { 0x2C, 0.0f, 45.0f, 0.0f, NULL }
};
Piece_ovl0B_02 D_ovl0B_02_80049A78[29] = {
    { 0x2D, 0.0f, -100.0f, -120.0f, NULL, 0, 2, 0, 0, 0, 325.0f, 345.0f, 1.2f },
    { 0x2D, 0.0f, -100.0f, -120.0f, NULL, 0, 0, 0, 0, 0, 325.0f, 345.0f, 1.2f },
    { 0x2D, 0.0f, -100.0f, -120.0f, NULL, 0, 3, 0, 0, 0, 325.0f, 345.0f, 1.2f },
    { 0x2D, 0.0f, -100.0f, -120.0f, NULL, 0, 1, 0, 0, 0, 325.0f, 345.0f, 1.2f },
    { 0x2D, 0.0f, -100.0f, -120.0f, NULL, 0, 4, 0, 0, 0, 325.0f, 345.0f, 1.2f },
    { 0x27, 0.0f, -100.0f, -120.0f, NULL, 0, 0x14, 0, 0, 0, 345.0f, 135.0f, 1.2f },
    { 0x27, 0.0f, -100.0f, -120.0f, NULL, 0, 0x17, 0, 0, 0, 345.0f, 135.0f, 1.2f },
    { 0x27, 0.0f, -100.0f, -120.0f, NULL, 0, 0x15, 0, 0, 0, 345.0f, 135.0f, 1.2f },
    { 0x27, 0.0f, -100.0f, -120.0f, NULL, 0, 0x16, 0, 0, 0, 345.0f, 135.0f, 1.2f },
    { 0x2A, 0.0f, -100.0f, -120.0f, NULL, 0, -1, 0, 0, 0, 345.0f, 135.0f, 1.2f },
    { 0x2E, 0.0f, -100.0f, -120.0f, NULL, 0, 1, 0, 0, 0, 325.0f, 55.0f, 1.2f },
    { 0x2E, 0.0f, -100.0f, -120.0f, NULL, 0, 2, 0, 0, 0, 325.0f, 55.0f, 1.2f },
    { 0x2E, 0.0f, -100.0f, -120.0f, NULL, 0, 4, 0, 0, 0, 325.0f, 55.0f, 1.2f },
    { 0x2E, 0.0f, -100.0f, -120.0f, NULL, 0, 0, 0, 0, 0, 325.0f, 55.0f, 1.2f },
    { 0x2E, 0.0f, -100.0f, -120.0f, NULL, 0, -1, 0, 0, 0, 325.0f, 55.0f, 1.2f },
    { 0x2F, 0.0f, -100.0f, -120.0f, NULL, 0, 0, 0, 0, 0, 335.0f, 320.0f, 1.2f },
    { 0x2F, 0.0f, -100.0f, -120.0f, NULL, 0, 2, 0, 0, 0, 335.0f, 320.0f, 1.2f },
    { 0x2F, 0.0f, -100.0f, -120.0f, NULL, 0, 1, 0, 0, 0, 335.0f, 320.0f, 1.2f },
    { 0x2F, 0.0f, -100.0f, -120.0f, NULL, 0, 4, 0, 0, 0, 335.0f, 320.0f, 1.2f },
    { 0x2F, 0.0f, -100.0f, -120.0f, NULL, 0, 3, 0, 0, 0, 335.0f, 320.0f, 1.2f },
    { 0x27, 0.0f, -110.0f, -65.0f, NULL, 0, 0xD, 0, 0, 0, 345.0f, 340.0f, 0.3f },
    { 0x27, 0.0f, -110.0f, -65.0f, NULL, 0, 0xC, 0, 0, 0, 345.0f, 340.0f, 0.3f },
    { 0x27, 0.0f, -110.0f, -65.0f, NULL, 0, 0xB, 0, 0, 0, 345.0f, 340.0f, 0.3f },
    { 0x27, 0.0f, -110.0f, -65.0f, NULL, 0, 0xE, 0, 0, 0, 345.0f, 340.0f, 0.3f },
    { 0x27, 0.0f, -110.0f, -65.0f, NULL, 0, 0xF, 0, 0, 0, 345.0f, 340.0f, 0.3f },
    { 0x27, 0.0f, -100.0f, -80.0f, NULL, 0, 0x11, 0, 0, 0, 345.0f, 25.0f, 0.5f },
    { 0x27, 0.0f, -100.0f, -80.0f, NULL, 0, 0x12, 0, 0, 0, 345.0f, 25.0f, 0.5f },
    { 0x27, 0.0f, -100.0f, -80.0f, NULL, 0, 0x10, 0, 0, 0, 345.0f, 25.0f, 0.5f },
    { 0x27, 0.0f, -100.0f, -80.0f, NULL, 0, 0x13, 0, 0, 0, 345.0f, 25.0f, 0.5f }
};
f32 D_ovl0B_02_8004A05C[6][3][2] = {
    { { 30.0f, -10.0f }, { -30.0f, -20.0f }, { 25.0f, -30.0f } },
    { { -20.0f, 90.0f }, { 10.0f, 50.0f }, { 15.0f, 130.0f } },
    { { 10.0f, -20.0f }, { 20.0f, -45.0f }, { 40.0f, 5.0f } },
    { { 25.0f, 104.0f }, { 30.0f, -120.0f }, { -10.0f, 55.0f } },
    { { 11.0f, 0.0f }, { 15.0f, -50.0f }, { 10.0f, 0.0f } },
    { { -20.0f, 90.0f }, { 10.0f, 50.0f }, { 30.0f, 0.0f } }
};
Group_ovl0B_02 D_ovl0B_02_8004A0EC[6] = {
    { &D_ovl0B_02_80049A78[0], D_ovl0B_02_8004A05C[0], 5 },
    { &D_ovl0B_02_80049A78[5], D_ovl0B_02_8004A05C[1], 5 },
    { &D_ovl0B_02_80049A78[10], D_ovl0B_02_8004A05C[2], 5 },
    { &D_ovl0B_02_80049A78[15], D_ovl0B_02_8004A05C[3], 5 },
    { &D_ovl0B_02_80049A78[20], D_ovl0B_02_8004A05C[4], 5 },
    { &D_ovl0B_02_80049A78[25], D_ovl0B_02_8004A05C[5], 4 },
};
s32 D_ovl0B_02_8004A134[4] = { 5, 2, 4, 3 };
s32 D_ovl0B_02_8004A144[3] = { 0, 1, 2 };
void (*D_ovl0B_02_8004A150[6])(void) = {
    func_ovl0B_02_80047C84, func_ovl0B_02_80047E98, func_ovl0B_02_80048018, func_ovl0B_02_800481E8, NULL, NULL,
};
Vec3f D_ovl0B_02_8004A168[3] = {
    { 69.0f, -1050.0f, -1147.0f },
    { 134.0f, -949.0f, -1185.0f },
    { 242.0f, -923.0f, -1254.0f },
};
u16 D_ovl0B_02_8004A18C[8] = { 0x64, 0x82, 0, 2, 0xAC, 0x82, 0, 0x100 };

/* unused: the stubs IDO -O3 leaves after the tail */
static void func_ovl0B_02_80047C14(void) {
}

static void func_ovl0B_02_80047C1C(void) {
}

static void func_ovl0B_02_80047C24(void) {
}

static void func_ovl0B_02_80047C2C(void) {
}

static void func_ovl0B_02_80047C34(void) {
}

static void func_ovl0B_02_80047C3C(void) {
}

static void func_ovl0B_02_80047C44(void) {
}

static void func_ovl0B_02_80047C4C(void) {
}

static void func_ovl0B_02_80047C54(void) {
}

static void func_ovl0B_02_80047C5C(void) {
}

static void func_ovl0B_02_80047C64(void) {
}

static void func_ovl0B_02_80047C6C(void) {
}

static void func_ovl0B_02_80047C74(void) {
}

static void func_ovl0B_02_80047C7C(void) {
}

/* The tasks in D_ovl0B_02_8004A150, one per group: they run until
 * D_ovl0B_02_8004A448 is set. */
static void func_ovl0B_02_80047C84(void) {
    UnkStructA *obj;
    f32 angle;

    obj = func_ovl0B_02_80049050(0x29, 0x01000000, 0xD0, NULL);
    func_ovl0B_02_80049028(obj, 0x0C000000);
    obj->unk40->unk30 = 0.3f;
    obj->unk40->unk28 = obj->unk40->unk2C = obj->unk40->unk30;
    angle = 0.0f;
    while (D_ovl0B_02_8004A448 == 0) {
        obj->unk40->unk20 = angle - 90.0 >= 360.0 ? angle - 90.0 - 360.0 : angle < 90.0 ? angle - 90.0 + 360.0 : angle - 90.0;
        obj->unk40->unk10 = func_ovl0B_02_80049320(angle) * 140.0f + 19.0f;
        obj->unk40->unk14 = -480.0f;
        obj->unk40->unk18 = func_ovl0B_02_80049328(angle) * 140.0f + -716.0f;
        ANGLE_SUB(angle, 1.0f);
        func_ovl0B_02_800491C0();
    }
    func_ovl0B_02_80049040(obj);
    func_ovl0B_02_80049188();
}

static void func_ovl0B_02_80047E98(void) {
    s32 i;

    while (D_ovl0B_02_8004A448 == 0) {
        func_ovl0B_02_800495C8(0x19, func_ovl0B_02_80049320(func_ovl0B_02_80049330() * 0.0) * 50.0f + 19.0f, -580.0f,
                               func_ovl0B_02_80049328(func_ovl0B_02_80049330() * 0.0) * 50.0f + -716.0f, 0);
        for (i = 0; i < func_ovl0B_02_80049338(80) + 50; i++) {
            if (D_ovl0B_02_8004A448 != 0) {
                break;
            }
            func_ovl0B_02_800491C0();
        }
    }
    func_ovl0B_02_800495E0();
    func_ovl0B_02_80049188();
}

static void func_ovl0B_02_80048018(void) {
    s32 i;
    s32 j;
    s32 x;

    while (D_ovl0B_02_8004A448 == 0) {
        for (x = 120, j = 0; j < 2; j++) {
            func_ovl0B_02_80049178(func_ovl0B_02_80046B8C, (void *) x, 0, 0, 0x130);
            x += 30;
            for (i = 0; i < func_ovl0B_02_80049338(20) + 20; i++) {
                if (D_ovl0B_02_8004A448 != 0) {
                    break;
                }
                func_ovl0B_02_800491C0();
            }
            i = 0;
        }
        for (x = 240, j = 0; j < 2; j++) {
            func_ovl0B_02_80049178(func_ovl0B_02_80046B8C, (void *) x, 0, 0, 0x130);
            x -= 30;
            for (i = 0; i < func_ovl0B_02_80049338(20) + 20; i++) {
                if (D_ovl0B_02_8004A448 != 0) {
                    break;
                }
                func_ovl0B_02_800491C0();
            }
            i = 0;
        }
        for (; i < func_ovl0B_02_80049338(120) + 80; i++) {
            if (D_ovl0B_02_8004A448 != 0) {
                break;
            }
            func_ovl0B_02_800491C0();
        }
    }
    func_ovl0B_02_80049188();
}

static void func_ovl0B_02_800481E8(void) {
    s32 i;

    while (D_ovl0B_02_8004A448 == 0) {
        for (i = 0; i != 4; i++) {
            func_ovl0B_02_80049178(func_ovl0B_02_800469C8, NULL, 0, 0, 0x130);
        }
        for (i = 0; i < func_ovl0B_02_80049338(10) + 10; i++) {
            if (D_ovl0B_02_8004A448 != 0) {
                break;
            }
            func_ovl0B_02_800491C0();
        }
    }
    func_ovl0B_02_80049188();
}

/* unused: the stub IDO -O3 leaves at the end of the object; it refers to
 * the .bss nothing else uses, which would otherwise be common */
static void func_ovl0B_02_800482D0(void) {
    D_ovl0B_02_8004A380[0] = 0;
}

void func_ovl0B_02_80047BFC(void) {
    D_ovl0B_02_8004A3B0 = -1;
    D_ovl0B_02_8004A3B4 = -1;
}

void func_ovl0B_02_80047BA0(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0B_02_80048E68(D_ovl0B_02_8004A3B8.x, D_ovl0B_02_8004A3B8.y, D_ovl0B_02_8004A3B8.z);
    func_ovl0B_02_80048E88(arg0, arg1, arg2);
    func_ovl0B_02_80049198(0xB4);
}

void func_ovl0B_02_80047B58(f32 arg0) {
    f32 sp1C;

    func_ovl0B_02_80048E90(&sp1C, NULL, NULL);
    func_ovl0B_02_80048E88(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0B_02_80047B24(s32 arg0, UnkStructA *arg1) {
    func_ovl0B_02_80049720(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

static void func_ovl0B_02_800443DC(Piece_ovl0B_02 *pieces, s32 n);

void func_ovl0B_02_800478EC(s32 arg0) {
    s32 i;

    switch (arg0) {
        case 2:
            D_ovl0B_02_8004A3CC = func_ovl0B_02_80048728();
            break;
        case 16:
        case 17:
            func_ovl0B_02_800472C0();
            func_ovl0B_02_80049178(func_ovl0B_02_80045F10, NULL, 0, 0, 0x130);
            break;
        case 18:
            func_ovl0B_02_800472C0();
            func_ovl0B_02_80049178(func_ovl0B_02_800454F0, NULL, 0, 0, 0x130);
            break;
        case 19:
            func_ovl0B_02_800472C0();
            func_ovl0B_02_80049178(func_ovl0B_02_800454F0, NULL, 0, 0, 0x130);
            break;
        case 20:
            func_ovl0B_02_80048790(0);
            func_ovl0B_02_80049178(func_ovl0B_02_80045C30, NULL, 0, 0, 0x130);
            break;
        case 1:
            if (D_ovl0B_02_8004A3CC != 0x14) {
                func_ovl0B_02_800443DC(D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4].unk0,
                                       D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4].unk8);
                func_ovl0B_02_80049180(D_ovl0B_02_8004A444);
                for (i = 0; i < 2; i++) {
                    func_ovl0B_02_80048D10(D_ovl0B_02_80049A50[i].unk10);
                }
                for (i = 0; i < 20; i++) {
                    func_ovl0B_02_80048D10(D_ovl0B_02_8004A3F0[i]);
                }
            }
            break;
        default:
            break;
    }
}

static void func_ovl0B_02_80043FC4(void);

static void func_ovl0B_02_800472B8(void) {
}

static void func_ovl0B_02_800472B0(void) {
}

static void func_ovl0B_02_800472A8(void) {
}

static void func_ovl0B_02_800472A0(void) {
}

static void func_ovl0B_02_800472C0(void) {
    s32 (*tbl)[4];
    s32 i;
    s32 j;
    s32 n;

    func_ovl0B_02_800472A0();
    func_ovl0B_02_800472A8();
    func_ovl0B_02_800472B0();
    func_ovl0B_02_800472B8();
    func_ovl0B_02_80049020(0);
    func_ovl0B_02_80049340(45.0f, 50.0f);
    D_ovl0B_02_8004A3E0 = func_ovl0B_02_80048778();
    for (i = 0; i < 4; i++) {
        for (j = 0; j != 5; j++) {
            D_ovl0B_02_8004A3F0[i * 5 + j] = func_ovl0B_02_80048D08(0x37, 0);
            D_ovl0B_02_8004A3F0[i * 5 + j]->unk10 = j * 64.0f;
            D_ovl0B_02_8004A3F0[i * 5 + j]->unk14 = i * 64.0f;
            D_ovl0B_02_8004A3F0[i * 5 + j]->unk18 = j * 64.0f + 64.0f;
            D_ovl0B_02_8004A3F0[i * 5 + j]->unk1C = i * 64.0f + 64.0f;
            D_ovl0B_02_8004A3F0[i * 5 + j]->unkC |= 0x400;
        }
    }
    for (i = 0; i < 2; i++) {
        D_ovl0B_02_80049A50[i].unk10 = func_ovl0B_02_80048D08(D_ovl0B_02_80049A50[i].unk0, 0);
        D_ovl0B_02_80049A50[i].unk10->unk10 = D_ovl0B_02_80049A50[i].unk4;
        D_ovl0B_02_80049A50[i].unk10->unk14 = D_ovl0B_02_80049A50[i].unk8;
        D_ovl0B_02_80049A50[i].unk10->unk18 = D_ovl0B_02_80049A50[i].unkC;
    }
    D_ovl0B_02_8004A444 = func_ovl0B_02_80049178(func_ovl0B_02_800468C4, D_ovl0B_02_80049A50[0].unk10, 0, 0, 0x130);
    D_ovl0B_02_8004A440 = func_ovl0B_02_80048D98(D_ovl0B_02_80049A50[0].unk10, 0x19);
    D_ovl0B_02_80049A50[0].unk10->unkC |= 0x11000;
    D_ovl0B_02_80049A50[0].unk10->unk1C = -20.0f;
    D_ovl0B_02_80049A50[1].unk10->unk1C = -45.0f;
    D_ovl0B_02_8004A3D4 = D_ovl0B_02_8004A3E0->unk4;
    if (D_ovl0B_02_8004A3D4 == -1) {
        D_ovl0B_02_8004A3D4 = 0;
    }
    D_ovl0B_02_8004A3D8 = D_ovl0B_02_8004A3E0->unk8;
    if (D_ovl0B_02_8004A3D8 == -1) {
        D_ovl0B_02_8004A3D8 = 0;
    }
    tbl = func_ovl0B_02_80049410(0x15);
    for (i = 0; i < 4; i++) {
        n = 0;
        for (j = 0; j != 4; j++) {
            if (tbl[i][j] != 0) {
                n++;
            }
        }
        if (n == 4) {
            func_ovl0B_02_80048DA0(D_ovl0B_02_8004A440, D_ovl0B_02_8004A134[i], 0x4F);
        }
    }
    for (i = 0; i < 16; i++) {
        if (tbl[0][i] == 0) {
            break;
        }
    }
    D_ovl0B_02_8004A3DC = D_ovl0B_02_8004A3D4;
    if (D_ovl0B_02_8004A3CC == 0x12 && i != 16) {
        D_ovl0B_02_8004A3D4 &= 3;
        func_ovl0B_02_80049710(2);
    } else if (D_ovl0B_02_8004A3CC == 0x12 && i == 16) {
        D_ovl0B_02_8004A3D4 = 4;
    } else {
        func_ovl0B_02_80049710(2);
    }
    if ((D_ovl0B_02_8004A3CC != 0x12 && D_ovl0B_02_8004A3D4 < 4) || (D_ovl0B_02_8004A3CC == 0x12 && D_ovl0B_02_8004A3D4 < 5)) {
        D_ovl0B_02_80049A50[0].unk10->unk20 =
            D_ovl0B_02_8004A3DC * -90.0f - 10.0f >= 360.0f ? D_ovl0B_02_8004A3DC * -90.0f - 10.0f - 360.0f
            : D_ovl0B_02_8004A3DC * -90.0f < 10.0f ? D_ovl0B_02_8004A3DC * -90.0f - 10.0f + 360.0f
            : D_ovl0B_02_8004A3DC * -90.0f - 10.0f;
        D_ovl0B_02_8004A3DC &= 3;
    } else {
        D_ovl0B_02_8004A3DC = 0;
        D_ovl0B_02_80049A50[0].unk10->unk20 = 350.0f;
        if (D_ovl0B_02_8004A3D4 == 4) {
            D_ovl0B_02_80049A50[0].unk10->unk14 -= 1065.0f;
            D_ovl0B_02_80049A50[0].unk10->unk10 -= 120.0f;
        } else if (D_ovl0B_02_8004A3D4 == 5) {
            D_ovl0B_02_80049A50[0].unk10->unk10 -= 120.0f;
            D_ovl0B_02_80049A50[0].unk10->unk14 -= 2865.0f;
            D_ovl0B_02_80049A50[0].unk10->unk18 += 800.0f;
        }
    }
    func_ovl0B_02_80043FC4();
    if (D_ovl0B_02_8004A3CC == 0x11) {
        D_ovl0B_02_80049A50[0].unk10->unkC |= 0x81;
        for (i = 0; i < D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4].unk8; i++) {
            D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4].unk0[i].unk10->unkC &= ~1;
        }
        D_ovl0B_02_8004A3E4 = 1;
    } else {
        for (i = 0; i < D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4].unk8; i++) {
            D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4].unk0[i].unk10->unkC |= 1;
        }
        D_ovl0B_02_8004A3E4 = 0;
    }
    func_ovl0B_02_80048ED0(0x7F);
    func_ovl0B_02_80048E48(1);
    func_ovl0B_02_80048E68(0.0f, 45.0f, 0.0f);
    func_ovl0B_02_80048E58(1);
    func_ovl0B_02_80049178(func_ovl0B_02_800471A8, NULL, 0, 0, 0x130);
}

void func_ovl0B_02_800471A8(void) {
    f32 t;

    for (t = -60.0f; t < 0; t += 1.0f) {
        func_ovl0B_02_80048E88(0.0f, 45.0f, t * t * -0.061f + 420.0f);
        func_ovl0B_02_800491C0();
    }
    func_ovl0B_02_80049188();
}

void func_ovl0B_02_800470B0(void) {
    f32 t;

    for (t = 0; t > -60.0f; t -= 1.0f) {
        func_ovl0B_02_80048E88(0.0f, 45.0f, t * t * -0.061f + 420.0f);
        func_ovl0B_02_800491C0();
    }
    func_ovl0B_02_80049188();
}

void func_ovl0B_02_80047020(void) {
    UnkStructA_40 *obj;
    s32 i;

    obj = func_ovl0B_02_800491A0();
    func_ovl0B_02_80049198(4);
    for (i = 0; i != 8; i++) {
        obj->unk1C += 3.75;
        func_ovl0B_02_800491C0();
    }
    func_ovl0B_02_80049188();
}

/* A piece's display list (the callback of the objects 80043FC4 makes). */
void func_ovl0B_02_80046EFC(UnkStructA_40 *arg0, Gfx_ovl0B_02 **arg1) {
    Piece_ovl0B_02 *p = M2C_FIELD(arg0, Piece_ovl0B_02 **, 0x40);
    Gfx_ovl0B_02 *gfx = *arg1;
    u32 *e = (u32 *) (p->unk14 + p->unk18 * 12 + 12);

    { Gfx_ovl0B_02 *g = gfx++; g->w0 = 0xBC000806; g->w1 = p->unk14; }
    if (arg0->unkC & 0x80) {
        { Gfx_ovl0B_02 *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x055079F8; }
        { Gfx_ovl0B_02 *g = gfx++; g->w0 = 0xF8000000; g->w1 = (arg0->unk36 & 0xFF) | ~0xFF; }
    } else {
        { Gfx_ovl0B_02 *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0xF5005178; }
        { Gfx_ovl0B_02 *g = gfx++; g->w0 = 0xF8000000; g->w1 = (p->unk1C << 24) | ((p->unk20 & 0xFF) << 16) | ((p->unk24 & 0xFF) << 8) | (arg0->unk36 & 0xFF); }
    }
    { Gfx_ovl0B_02 *g = gfx++; g->w0 = 0x06000000; g->w1 = e[2] + p->unk14; }
    *arg1 = gfx;
}

void func_ovl0B_02_80046B8C(void) {
    f32 x;
    UnkStructA *a;
    UnkStructA *b;
    f32 dy;
    f32 dx;
    s32 i;

    x = (s32) func_ovl0B_02_800491A0();
    a = func_ovl0B_02_80049050(0x1B6, 0x01080000, 0xD0, NULL);
    b = func_ovl0B_02_80049050(0x1B7, 0x01080000, 0xD0, NULL);
    a->unk40->unk10 = b->unk40->unk10 = 19.0f;
    a->unk40->unk14 = b->unk40->unk14 = -580.0f;
    a->unk40->unk18 = b->unk40->unk18 = -686.0f;
    a->unk40->unk30 = 0.1f;
    a->unk40->unk28 = a->unk40->unk2C = a->unk40->unk30;
    b->unk40->unk30 = 0.1f;
    b->unk40->unk28 = b->unk40->unk2C = b->unk40->unk30;
    func_ovl0B_02_80049028(a, 0x80000);
    func_ovl0B_02_80049028(b, 0x80000);
    a->unk40->unk36 = b->unk40->unk36 = 0xC8;
    dy = func_ovl0B_02_80049330() + 6.0;
    dx = func_ovl0B_02_80049330() * 2.0;
    func_ovl0B_02_800495C8(0x19, 19.0f, -580.0f, -776.0f, 0);
    for (i = 0; i != 60; i++) {
        if (D_ovl0B_02_8004A448 != 0) {
            break;
        }
        a->unk40->unk10 += func_ovl0B_02_80049320(x) * dx;
        a->unk40->unk14 += dy;
        b->unk40->unk10 += func_ovl0B_02_80049320(x) * dx;
        b->unk40->unk14 += dy;
        dy -= 0.13333334f;
        func_ovl0B_02_800491C0();
        a->unk40->unk36 -= 3.3333333f;
        b->unk40->unk36 -= 3.3333333f;
    }
    func_ovl0B_02_800495E0();
    func_ovl0B_02_80049040(a);
    func_ovl0B_02_80049040(b);
    func_ovl0B_02_80049188();
}

void func_ovl0B_02_800469C8(void) {
    UnkStructA *obj;
    f32 dy;
    s32 i;

    obj = func_ovl0B_02_80049050(0x2C7, 0x01000000, 0xD0, NULL);
    obj->unk40->unk10 = func_ovl0B_02_80049320(func_ovl0B_02_80049330() * 360.0) * 100.0f + 19.0f;
    obj->unk40->unk14 = -480.0f;
    obj->unk40->unk18 = func_ovl0B_02_80049328(func_ovl0B_02_80049330() * 360.0) * 100.0f + -716.0f;
    obj->unk40->unk30 = 0.2f;
    obj->unk40->unk28 = obj->unk40->unk2C = obj->unk40->unk30;
    dy = (f32) (func_ovl0B_02_80049330() * 40.0 + 80.0) / 30.0f;
    for (i = 0; i != 30; i++) {
        obj->unk40->unk14 -= dy;
        obj->unk40->unk10 -= 1.6666666f;
        if (D_ovl0B_02_8004A448 != 0) {
            break;
        }
        func_ovl0B_02_800491C0();
    }
    func_ovl0B_02_80049040(obj);
    func_ovl0B_02_80049188();
}

void func_ovl0B_02_800468C4(void) {
    UnkStructA_40 *obj;
    f32 angle;

    obj = func_ovl0B_02_800491A0();
    angle = 0.0f;
    while (TRUE) {
        obj->unk14 += func_ovl0B_02_80049328(WRAP(angle)) * 0.5f;
        angle += 1.0f;
        func_ovl0B_02_800491C0();
    }
}

void func_ovl0B_02_8004686C(void) {
    UnkStructA_40 *src;
    UnkStructA_40 *obj;

    src = D_ovl0B_02_80049A50[0].unk10;
    obj = func_ovl0B_02_800491A0();
    while (TRUE) {
        obj->unk14 = src->unk14;
        func_ovl0B_02_800491C0();
    }
}

void func_ovl0B_02_800467D0(void) {
    UnkStructA_40 *obj;

    obj = func_ovl0B_02_800491A0();
    while (TRUE) {
        obj->unk10 = D_ovl0B_02_80049A50[0].unk10->unk10;
        obj->unk14 = D_ovl0B_02_80049A50[0].unk10->unk14 + 1034.0f;
        obj->unk18 = D_ovl0B_02_80049A50[0].unk10->unk18;
        func_ovl0B_02_800491C0();
    }
}

void func_ovl0B_02_80046418(void) {
    UnkStructA_40 *src;
    UnkStructA *obj;
    f32 angle;
    f32 dist;
    f32 dx;
    f32 dz;
    f32 rx;
    s32 i;
    f32 ry;
    f32 rz;

    func_ovl0B_02_80049198(func_ovl0B_02_80049338(0x10) + 1);
    src = D_ovl0B_02_80049A50[0].unk10;
    obj = func_ovl0B_02_80049050(0x11F, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = src->unk10;
    obj->unk40->unk14 = src->unk14 + 1034.0f;
    obj->unk40->unk18 = src->unk18;
    angle = func_ovl0B_02_80049330() * 360.0;
    dist = func_ovl0B_02_80049330() * 200.0 + 600.0;
    dx = func_ovl0B_02_80049320(angle) * dist;
    dz = func_ovl0B_02_80049328(angle) * (dist * 1.2f);
    rx = func_ovl0B_02_80049330() * 10.0 + 10.0;
    ry = func_ovl0B_02_80049330() * 10.0 + 10.0;
    rz = func_ovl0B_02_80049330() * 10.0 + 10.0;
    obj->unk40->unk28 = func_ovl0B_02_80049330() + 3.0;
    obj->unk40->unk2C = func_ovl0B_02_80049330() + 3.0;
    obj->unk40->unk30 = func_ovl0B_02_80049330() + 3.0;
    obj->unk40->unk36 = 0xFA;
    for (i = 0; i != 90; i++) {
        obj->unk40->unk10 += dx / 90.0f;
        obj->unk40->unk14 += dz / 90.0f;
        ANGLE_ADD(obj->unk40->unk1C, rx);
        ANGLE_ADD(obj->unk40->unk20, ry);
        ANGLE_ADD(obj->unk40->unk24, rz);
        obj->unk40->unk36 -= 2.7222223f;
        func_ovl0B_02_800491C0();
    }
    func_ovl0B_02_80049040(obj);
    func_ovl0B_02_80049188();
}

static void func_ovl0B_02_800430C4(Box_ovl0B_02 *box, f32 scale);

void func_ovl0B_02_800462C8(void) {
    f32 angle;
    s32 i;

    angle = 0.0f;
    while (TRUE) {
        for (i = 1; i != 5; i++) {
            func_ovl0B_02_800430C4(&D_ovl0B_02_80049950[i], func_ovl0B_02_80049328(WRAP(angle)) * 0.05f + 0.9f);
        }
        angle += 4.0f;
        func_ovl0B_02_800491C0();
    }
}

s32 func_ovl0B_02_80046258(u8 arg0, u16 arg1) {
    if (arg1 & 1) {
        func_ovl0B_02_80049700(1);
        D_ovl0B_02_8004A3D0 = arg0;
        return 0;
    }
    if (arg1 & 2) {
        func_ovl0B_02_80049700(2);
        D_ovl0B_02_8004A3D0 = -1;
        return 0;
    }
    return 1;
}

void func_ovl0B_02_80046100(void) {
    f32 angle;
    s32 i;

    angle = 0.0f;
    while (TRUE) {
        for (i = 1; i != 3; i++) {
            func_ovl0B_02_800430C4(&D_ovl0B_02_800499F0[i], func_ovl0B_02_80049328(WRAP(angle)) * 0.05f + 0.9f);
        }
        angle += 4.0f;
        func_ovl0B_02_800491C0();
    }
}

void func_ovl0B_02_80046014(void) {
    UnkStructA_40 *obj;

    obj = func_ovl0B_02_800491A0();
    while (obj->unk48->unk4->unk4 < func_ovl0B_02_80048D68(obj, 0)) {
        func_ovl0B_02_800491C0();
        obj->unk48->unk4->unk4 += 2.0f;
    }
    obj->unk48->unk4->unk4 = func_ovl0B_02_80048D68(obj, 0) - 0.01f;
    func_ovl0B_02_80049188();
}

void func_ovl0B_02_80045F58(void) {
    UnkStructA_40 *obj;

    obj = func_ovl0B_02_800491A0();
    while (obj->unk48->unk4->unk4 > 2.0f) {
        func_ovl0B_02_800491C0();
        obj->unk48->unk4->unk4 -= 2.0f;
    }
    obj->unk48->unk4->unk4 = 0.0f;
    func_ovl0B_02_80049188();
}

void func_ovl0B_02_80045F10(void) {
    func_ovl0B_02_80049198(0x3C);
    func_ovl0B_02_80049178(func_ovl0B_02_80044490, NULL, 0, 0, 0x130);
    func_ovl0B_02_80049188();
}

void func_ovl0B_02_80045C30(void) {
    UnkStructA_40 *model;
    UnkStructA_40 *obj;
    f32 y;
    s32 anim;
    s32 i;

    model = func_ovl0B_02_80048D08(0x27, 0);
    anim = func_ovl0B_02_80048D98(model, 0x19);
    for (i = 0; i < 4; i++) {
        func_ovl0B_02_80048DA0(anim, D_ovl0B_02_8004A134[i], 0x4F);
    }
    obj = func_ovl0B_02_80048D08(0x328, 0);
    y = 827.0f;
    obj->unk14 = 1400.0f;
    obj->unk20 = 45.0f;
    obj->unk18 = 200.0f;
    func_ovl0B_02_80048E68(0.0f, y, 0.0f);
    func_ovl0B_02_80048E88(0.0f, 30.0f, 3070.0f);
    D_ovl0B_02_8004A450[0] = func_ovl0B_02_80049200(0x296);
    func_ovl0B_02_80049210(D_ovl0B_02_8004A450[0], 0x20000000);
    D_ovl0B_02_8004A450[0]->unk40 = 0.5f;
    D_ovl0B_02_8004A450[0]->unk44 = D_ovl0B_02_8004A450[0]->unk40 * 0.75f;
    D_ovl0B_02_8004A450[0]->unk3C = D_ovl0B_02_8004A450[0]->unk4C * 0.25f;
    func_ovl0B_02_80048E58(0);
    for (i = 0; i < 300; i++) {
        y += 5.3333335f;
        obj->unk20 += 0.45f;
        obj->unk14 += 3.6666667f;
        func_ovl0B_02_80048E68(0.0f, y, 0.0f);
        func_ovl0B_02_800491C0();
    }
    for (i = 0; i != 120; i++) {
        obj->unk14 += 1.6666666f;
        obj->unk1C += 0.75f;
        obj->unk28 -= 0.008333334f;
        obj->unk2C -= 0.008333334f;
        obj->unk30 -= 0.008333334f;
        func_ovl0B_02_800491C0();
    }
    func_ovl0B_02_80049718();
    func_ovl0B_02_80049490(0, 0, 0, 0x20);
    func_ovl0B_02_80049470();
    func_ovl0B_02_80049840();
    func_ovl0B_02_80048DA8(anim);
    func_ovl0B_02_80048D10(obj);
    func_ovl0B_02_80048D10(model);
    func_ovl0B_02_80048720(0x21, 0x10, 1);
    func_ovl0B_02_80049188();
}

void func_ovl0B_02_800454F0(void) {
    UnkStructA_40 *star;
    UnkStructA_40 *model;
    s32 pad;
    s32 anim;
    s32 task;
    s32 pad2[2];
    s32 starTask;
    s32 (*tbl)[4];
    UnkStructA_40 *obj;
    f32 t;
    s32 dir;
    s32 i;
    s32 j;

    if (D_ovl0B_02_8004A3D4 < 5) {
        obj = D_ovl0B_02_80049A50[0].unk10;
        tbl = func_ovl0B_02_80049410(0x15);
        ANGLE_ADD(obj->unk20, 90.0f);
        dir = (D_ovl0B_02_8004A3DC - 1) & 3;
        if (D_ovl0B_02_8004A3CC != 0x13) {
            func_ovl0B_02_80048DA0(D_ovl0B_02_8004A440, D_ovl0B_02_8004A134[dir], -1);
        }
        for (t = 0.0f; t < 120.0f; t += 1.0f) {
            obj->unk10 += 1.8333334f;
            obj->unk14 += -3.8333333f;
            obj->unk18 += -1.4166666f;
            obj->unk20 += -0.41666666f;
            func_ovl0B_02_800491C0();
        }
        if (D_ovl0B_02_8004A3CC != 0x13) {
            func_ovl0B_02_80048DA0(D_ovl0B_02_8004A440, D_ovl0B_02_8004A134[dir], 0x4F);
            model = func_ovl0B_02_80048D08(0x2B, 0);
            model->unkC |= 0x10000;
            model->unk10 = obj->unk10;
            model->unk14 = obj->unk14;
            model->unk18 = obj->unk18;
            model->unk20 = obj->unk20;
            model->unk1C = obj->unk1C;
            model->unk24 = obj->unk24;
            model->unk20 += 90.0f * dir;
            anim = func_ovl0B_02_80048D98(model, 5);
            task = func_ovl0B_02_80049178(func_ovl0B_02_8004686C, model, 0, 0, 0x130);
            func_ovl0B_02_80049198(0x3C);
            for (i = 0; i < 3; i++) {
                for (j = 0; j != 5; j++) {
                    if (func_ovl0B_02_80049338(0x100) & 1) {
                        func_ovl0B_02_80049700(0x34);
                    } else {
                        func_ovl0B_02_80049700(0x33);
                    }
                    func_ovl0B_02_800495C8(0x14, (0.5 - func_ovl0B_02_80049330()) * 100.0 + D_ovl0B_02_8004A168[i].x,
                                           (0.5 - func_ovl0B_02_80049330()) * 100.0 + D_ovl0B_02_8004A168[i].y,
                                           D_ovl0B_02_8004A168[i].z, 0);
                    func_ovl0B_02_80049198(10);
                }
                func_ovl0B_02_80048DA0(anim, D_ovl0B_02_8004A144[i], 0x4F);
                func_ovl0B_02_800491C0();
            }
            func_ovl0B_02_80049700(0x35);
            func_ovl0B_02_80049180(task);
            func_ovl0B_02_80048DA8(anim);
            func_ovl0B_02_80048D10(model);
            func_ovl0B_02_80049198(0x3C);
        }
        for (i = 0; i < 16; i++) {
            if (tbl[0][i] == 0) {
                break;
            }
        }
        if (D_ovl0B_02_8004A3CC == 0x12 && i == 16) {
            star = func_ovl0B_02_80048D08(7, 0);
            star->unkC |= 1;
            star->unk30 = 8.0f;
            star->unk28 = 8.0f;
            star->unk2C = 15.0f;
            starTask = func_ovl0B_02_80049178(func_ovl0B_02_800467D0, star, 0, 0, 0x130);
        }
        for (; t < 60.0f; t += 1.0f) {
            if (D_ovl0B_02_8004A3CC == 0x12 && i == 16) {
                obj->unk10 -= 5.6666665f;
                obj->unk14 -= 10.083333f;
                obj->unk18 -= -2.8333333f;
                obj->unk20 -= 0.6666667f;
            } else {
                obj->unk10 -= 3.6666667f;
                obj->unk14 -= -7.6666665f;
                obj->unk18 -= -2.8333333f;
                obj->unk20 -= 0.6666667f;
            }
            func_ovl0B_02_800491C0();
        }
        if (D_ovl0B_02_8004A3CC == 0x12 && i == 16) {
            func_ovl0B_02_80049700(0x2DC);
            star->unkC &= ~1;
            star->unkC |= 0x80;
            star->unk36 = 0;
            for (j = 0; j < 120; j++) {
                star->unk36 += 1.0666667f;
                func_ovl0B_02_800491C0();
            }
            for (j = 0; j < 10; j++) {
                star->unkC &= ~1;
                func_ovl0B_02_80049198(3);
                star->unkC |= 1;
                func_ovl0B_02_80049198(3);
            }
            star->unkC |= 1;
            func_ovl0B_02_80049490(0xFF, 0xFF, 0xFF, 8);
            func_ovl0B_02_80049470();
            func_ovl0B_02_80049700(0x2DF);
            for (j = 0; j != 24; j++) {
                func_ovl0B_02_80049178(func_ovl0B_02_80046418, NULL, 0, 0, 0x130);
            }
            func_ovl0B_02_80049180(starTask);
            func_ovl0B_02_80048D10(star);
            func_ovl0B_02_80049480(0xFF, 0xFF, 0xFF, 0x20);
            func_ovl0B_02_80049470();
            func_ovl0B_02_80049198(0x78);
            func_ovl0B_02_80049710(2);
        }
    }
    func_ovl0B_02_80049178(func_ovl0B_02_80044490, NULL, 0, 0, 0x130);
    func_ovl0B_02_80049188();
}

static s32 func_ovl0B_02_80044424(u8 *str, f32 scale);
static void func_ovl0B_02_80043018(Box_ovl0B_02 *boxes, s32 n);
static void func_ovl0B_02_80043150(Box_ovl0B_02 *boxes, s32 n);
static void func_ovl0B_02_80043EF8(s32 unused, s32 i);
static UnkStructA_40 *func_ovl0B_02_80043F4C(s32 i);

void func_ovl0B_02_80044490(void) {
    s32 (*tbl)[4];
    s32 all;
    s32 task;
    UnkStructA_40 *mark;
    Group_ovl0B_02 *g;
    Piece_ovl0B_02 *pieces;
    s32 buttons;
    s32 i;
    s32 n;
    s32 a;
    s32 b;
    s32 alpha;
    f32 t;
    f32 x;
    f32 y;

    tbl = func_ovl0B_02_80049410(0x15);
    n = 0;
    for (i = 0; i < 4; i++) {
        if (tbl[i][0] != 0) {
            n++;
        }
        if (tbl[i][1] != 0) {
            n++;
        }
        if (tbl[i][2] != 0) {
            n++;
        }
        if (tbl[i][3] != 0) {
            n++;
        }
    }
    if (n == 16) {
        all = 1;
    } else {
        all = 0;
    }
    if (D_ovl0B_02_8004A3E4 == 0) {
        D_ovl0B_02_8004A3D8 = 0;
        g = &D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4];
        for (i = 0; i < g->unk8; i++) {
            g->unk0[i].unk10->unk1C = D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4].unk0[i].unk28;
            g->unk0[i].unk10->unk20 = D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4].unk0[i].unk2C;
        }
        mark = func_ovl0B_02_80043F4C(D_ovl0B_02_8004A3D4);
        func_ovl0B_02_80049198(0xC);
        func_ovl0B_02_80043150(D_ovl0B_02_80049950, 5);
        task = func_ovl0B_02_80049178(func_ovl0B_02_800462C8, NULL, 0, 0, 0x130);
        func_ovl0B_02_80043EF8(0, D_ovl0B_02_8004A3D4);
        func_ovl0B_02_800482F0(D_ovl0B_02_8004A3AC, "%02d", D_ovl0B_02_8004A3E0->unk38 / 3600);
        for (i = 0; i < 2; i++) {
            D_ovl0B_02_80049944[i] = D_ovl0B_02_8004A3AC[i] - 0x20;
        }
        func_ovl0B_02_800482F0(D_ovl0B_02_8004A3AC, "%02d", D_ovl0B_02_8004A3E0->unk38 % 3600 / 60);
        for (i = 0; i < 2; i++) {
            D_ovl0B_02_80049944[i + 4] = D_ovl0B_02_8004A3AC[i] - 0x20;
        }
        D_ovl0B_02_8004A39C[0] = func_ovl0B_02_800495B8(D_ovl0B_02_80049938, 0x2D, 0xAA, 0.6f, 0.6f, 5);
        D_ovl0B_02_8004A3A4[0] = func_ovl0B_02_800495B8(D_ovl0B_02_80049944, 0x2D, 0xBE, 0.6f, 0.6f, 5);
    }
    while (TRUE) {
        g = &D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4];
        pieces = g->unk0;
        buttons = func_ovl0B_02_80049530();
        if (D_ovl0B_02_8004A3E4 == 0) {
            if ((all && D_ovl0B_02_8004A3D4 < 4) ||
                (D_ovl0B_02_8004A3D4 == 4 && tbl[4][3] != 0 && func_ovl0B_02_800493E0(0xA4) != 0)) {
                D_ovl0B_02_80049950[3].unk1C->unkC &= ~1;
            } else {
                D_ovl0B_02_80049950[3].unk1C->unkC |= 1;
            }
            if (D_ovl0B_02_8004A3D4 >= 4) {
                D_ovl0B_02_80049950[4].unk1C->unkC &= ~1;
            } else {
                D_ovl0B_02_80049950[4].unk1C->unkC |= 1;
            }
            if (D_ovl0B_02_8004A3D4 < 4) {
                D_ovl0B_02_80049950[1].unk1C->unkC &= ~1;
                D_ovl0B_02_80049950[2].unk1C->unkC &= ~1;
            } else {
                D_ovl0B_02_80049950[1].unk1C->unkC |= 1;
                D_ovl0B_02_80049950[2].unk1C->unkC |= 1;
            }
        }
        if ((func_ovl0B_02_80048738() & 0x8000) || D_ovl0B_02_8004A3E4 != 0) {
            if (D_ovl0B_02_8004A3E4 == 0) {
                func_ovl0B_02_80049700(1);
                func_ovl0B_02_80049180(task);
                func_ovl0B_02_80049568(D_ovl0B_02_8004A39C[0]);
                func_ovl0B_02_80049568(D_ovl0B_02_8004A3A4[0]);
                func_ovl0B_02_80043018(D_ovl0B_02_80049950, 5);
                D_ovl0B_02_8004A448 = 1;
                func_ovl0B_02_80048D10(mark);
                D_ovl0B_02_80049A50[0].unk10->unkC |= 0x80;
                D_ovl0B_02_80049A50[0].unk10->unk36 = 0;
                for (i = 0; i < g->unk8; i++) {
                    pieces[i].unk10->unkC &= ~1;
                    pieces[i].unk10->unkC |= 0x1080;
                }
                for (alpha = 0xFF; alpha != -1; alpha -= 4) {
                    D_ovl0B_02_80049A50[0].unk10->unk36 = alpha;
                    for (i = 0; i < g->unk8; i++) {
                        pieces[i].unk10->unk36 = 0xFF - alpha;
                        pieces[i].unk10->unk28 = pieces[i].unk10->unk2C = pieces[i].unk10->unk30 =
                            (0x200 - alpha) * pieces[0].unk30 * 0.001953125f;
                    }
                    func_ovl0B_02_800491C0();
                }
            }
            D_ovl0B_02_8004A3E4 = 0;
            D_ovl0B_02_80049A50[0].unk10->unkC |= 1;
            for (i = 0; i < g->unk8; i++) {
                pieces[i].unk10->unk36 = 0;
                pieces[i].unk10->unkC &= ~0x1080;
                pieces[i].unk20 = 0xFF;
            }
            func_ovl0B_02_80049178(func_ovl0B_02_800431C4, NULL, 0, 0, 0x130);
            func_ovl0B_02_80049188();
            continue;
        }
        if (func_ovl0B_02_80048738() & 0x4000) {
            func_ovl0B_02_800491C0();
            a = func_ovl0B_02_800495B8(D_ovl0B_02_80049920, func_ovl0B_02_80044424(D_ovl0B_02_80049920, 0.8f), 100, 0.8f, 0.8f, 3);
            b = func_ovl0B_02_800495B8(D_ovl0B_02_8004992C, func_ovl0B_02_80044424(D_ovl0B_02_8004992C, 0.8f), 120, 0.8f, 0.8f, 2);
            func_ovl0B_02_80049500(func_ovl0B_02_80046258, D_ovl0B_02_8004A18C, 0x130, 0xC, 0xC);
            func_ovl0B_02_80049520();
            func_ovl0B_02_80049518();
            func_ovl0B_02_80049568(a);
            func_ovl0B_02_80049568(b);
            if (D_ovl0B_02_8004A3D0 == 2) {
                func_ovl0B_02_80049180(task);
                func_ovl0B_02_80049568(D_ovl0B_02_8004A39C[0]);
                func_ovl0B_02_80049568(D_ovl0B_02_8004A3A4[0]);
                func_ovl0B_02_80043018(D_ovl0B_02_80049950, 5);
                func_ovl0B_02_80048D10(mark);
                D_ovl0B_02_8004A448 = 1;
                func_ovl0B_02_80049700(0x25);
                func_ovl0B_02_80049718();
                func_ovl0B_02_80049178(func_ovl0B_02_800470B0, NULL, 0, 0, 0x130);
                D_ovl0B_02_80049A50[0].unk10->unkC |= 0x80;
                for (alpha = 0xFF; alpha != -1; alpha -= 8) {
                    D_ovl0B_02_80049A50[0].unk10->unk36 = alpha;
                    func_ovl0B_02_800491C0();
                }
                D_ovl0B_02_80049A50[0].unk10->unkC |= 1;
                func_ovl0B_02_80048720(0x20, 0x11, 0);
                while (TRUE) {
                    func_ovl0B_02_800491C0();
                }
            }
            continue;
        }
        if ((buttons & 0x100) && D_ovl0B_02_8004A3D4 < 4) {
            func_ovl0B_02_80049700(0);
            func_ovl0B_02_800443DC(pieces, g->unk8);
            D_ovl0B_02_8004A448 = 1;
            D_ovl0B_02_8004A3D4++;
            if (D_ovl0B_02_8004A3D4 >= 4) {
                D_ovl0B_02_8004A3D4 = 0;
            }
            func_ovl0B_02_80043FC4();
            func_ovl0B_02_80048D10(mark);
            mark = func_ovl0B_02_80043F4C(D_ovl0B_02_8004A3D4);
            x = D_ovl0B_02_80049A50[0].unk10->unk20;
            for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
                D_ovl0B_02_80049A50[0].unk10->unk20 =
                    t * t * 0.225f + x - 90.0f >= 360.0f ? t * t * 0.225f + x - 90.0f - 360.0f
                    : t * t * 0.225f + x < 90.0f ? t * t * 0.225f + x - 90.0f + 360.0f
                    : t * t * 0.225f + x - 90.0f;
                func_ovl0B_02_800491C0();
            }
            func_ovl0B_02_80043EF8(0, D_ovl0B_02_8004A3D4);
            continue;
        }
        if ((buttons & 0x200) && D_ovl0B_02_8004A3D4 < 4) {
            func_ovl0B_02_80049700(0);
            func_ovl0B_02_800443DC(pieces, g->unk8);
            D_ovl0B_02_8004A448 = 1;
            D_ovl0B_02_8004A3D4--;
            if (D_ovl0B_02_8004A3D4 < 0) {
                D_ovl0B_02_8004A3D4 = 3;
            }
            func_ovl0B_02_80043FC4();
            func_ovl0B_02_80048D10(mark);
            mark = func_ovl0B_02_80043F4C(D_ovl0B_02_8004A3D4);
            x = D_ovl0B_02_80049A50[0].unk10->unk20;
            for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
                D_ovl0B_02_80049A50[0].unk10->unk20 = WRAP(t * t * -0.225f + x + 90.0f);
                func_ovl0B_02_800491C0();
            }
            func_ovl0B_02_80043EF8(0, D_ovl0B_02_8004A3D4);
            continue;
        }
        if ((buttons & 0x800) && ((D_ovl0B_02_8004A3D4 < 4 && all) ||
                                  (D_ovl0B_02_8004A3D4 == 4 && tbl[4][3] != 0 && func_ovl0B_02_800493E0(0xA4) != 0))) {
            func_ovl0B_02_80049700(0);
            func_ovl0B_02_80048D10(mark);
            func_ovl0B_02_800443DC(pieces, g->unk8);
            D_ovl0B_02_8004A448 = 1;
            if (D_ovl0B_02_8004A3D4 == 4) {
                D_ovl0B_02_8004A3D4 = 5;
                func_ovl0B_02_80043FC4();
                mark = func_ovl0B_02_80043F4C(D_ovl0B_02_8004A3D4);
                x = D_ovl0B_02_80049A50[0].unk10->unk14;
                y = D_ovl0B_02_80049A50[0].unk10->unk18;
                for (t = 40.0f; t >= 0.0f; t -= 1.0f) {
                    D_ovl0B_02_80049A50[0].unk10->unk14 = (t * t * 1.125f - 1800.0f) + x;
                    D_ovl0B_02_80049A50[0].unk10->unk18 = y - (t * t * 0.05f - 800.0f);
                    func_ovl0B_02_800491C0();
                }
                func_ovl0B_02_80043EF8(0, D_ovl0B_02_8004A3D4);
            } else {
                D_ovl0B_02_8004A3DC = D_ovl0B_02_8004A3D4;
                D_ovl0B_02_8004A3D4 = 4;
                func_ovl0B_02_80043FC4();
                mark = func_ovl0B_02_80043F4C(D_ovl0B_02_8004A3D4);
                x = D_ovl0B_02_80049A50[0].unk10->unk14;
                y = D_ovl0B_02_80049A50[0].unk10->unk10;
                for (t = 40.0f; t >= 0.0f; t -= 1.0f) {
                    D_ovl0B_02_80049A50[0].unk10->unk14 = (t * t * 0.67f - 1065.0f) + x;
                    D_ovl0B_02_80049A50[0].unk10->unk10 = (t * t * 0.075f - 120.0f) + y;
                    func_ovl0B_02_800491C0();
                }
                func_ovl0B_02_80043EF8(0, D_ovl0B_02_8004A3D4);
            }
            continue;
        }
        if ((buttons & 0x400) && D_ovl0B_02_8004A3D4 >= 4) {
            func_ovl0B_02_80049700(0);
            func_ovl0B_02_80048D10(mark);
            func_ovl0B_02_800443DC(pieces, g->unk8);
            D_ovl0B_02_8004A448 = 1;
            if (D_ovl0B_02_8004A3D4 == 5) {
                D_ovl0B_02_8004A3D4 = 4;
                func_ovl0B_02_80043FC4();
                mark = func_ovl0B_02_80043F4C(D_ovl0B_02_8004A3D4);
                x = D_ovl0B_02_80049A50[0].unk10->unk14;
                y = D_ovl0B_02_80049A50[0].unk10->unk18;
                for (t = 40.0f; t >= 0.0f; t -= 1.0f) {
                    D_ovl0B_02_80049A50[0].unk10->unk14 = x - (t * t * 1.125f - 1800.0f);
                    D_ovl0B_02_80049A50[0].unk10->unk18 = (t * t * 0.05f - 800.0f) + y;
                    func_ovl0B_02_800491C0();
                }
                func_ovl0B_02_80043EF8(0, D_ovl0B_02_8004A3D4);
            } else {
                D_ovl0B_02_8004A3D4 = D_ovl0B_02_8004A3DC;
                func_ovl0B_02_80043FC4();
                mark = func_ovl0B_02_80043F4C(D_ovl0B_02_8004A3D4);
                x = D_ovl0B_02_80049A50[0].unk10->unk14;
                y = D_ovl0B_02_80049A50[0].unk10->unk10;
                for (t = 40.0f; t >= 0.0f; t -= 1.0f) {
                    D_ovl0B_02_80049A50[0].unk10->unk14 = x - (t * t * 0.67f - 1065.0f);
                    D_ovl0B_02_80049A50[0].unk10->unk10 = y - (t * t * 0.075f - 120.0f);
                    func_ovl0B_02_800491C0();
                }
                func_ovl0B_02_80043EF8(0, D_ovl0B_02_8004A3D4);
            }
            continue;
        }
        func_ovl0B_02_800491C0();
    }
}

/* The original takes the scale in $f20 (its callers' register). */
static s32 func_ovl0B_02_80044424(u8 *str, f32 scale) {
    return (320.0f - func_ovl0B_02_800495B0(str) * scale) / 2;
}

static void func_ovl0B_02_800443D4(void) {
}

/* The original passes n in $s2 (its callers' register). */
static void func_ovl0B_02_800443DC(Piece_ovl0B_02 *pieces, s32 n) {
    s32 i;

    func_ovl0B_02_800443D4();
    for (i = 0; i < n; i++) {
        func_ovl0B_02_80048D00(pieces[i].unk0);
        func_ovl0B_02_80048D10(pieces[i].unk10);
    }
}

static void func_ovl0B_02_80043FBC(void) {
}

/* Makes the current group's pieces and turns them to the current page. */
static void func_ovl0B_02_80043FC4(void) {
    Group_ovl0B_02 *g;
    Piece_ovl0B_02 *pieces;
    UnkStructA_40 *obj;
    u32 dl;
    s32 n;
    s32 i;
    s32 j;

    func_ovl0B_02_80043FBC();
    g = &D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4];
    n = g->unk8;
    pieces = g->unk0;
    for (i = 0; i < n; i++) {
        dl = func_ovl0B_02_80048CF8(pieces[i].unk0);
        if (pieces[i].unk18 == -1) {
            obj = pieces[i].unk10 = func_ovl0B_02_80048D08(pieces[i].unk0, 0);
            obj->unkC |= 0x40;
        } else {
            obj = pieces[i].unk10 = func_ovl0B_02_80048D88(func_ovl0B_02_80046EFC, 0);
            pieces[i].unk14 = dl;
            M2C_FIELD(obj, Piece_ovl0B_02 **, 0x40) = &pieces[i];
            M2C_FIELD(obj, s32 *, 0x38) = pieces[i].unk18;
        }
        obj->unk10 = pieces[i].unk4;
        obj->unk14 = pieces[i].unk8;
        obj->unk18 = pieces[i].unkC;
        obj->unk1C = pieces[i].unk28;
        obj->unk20 = pieces[i].unk2C;
        obj->unkC |= 0x10000;
        obj->unk28 = obj->unk2C = obj->unk30 = pieces[i].unk30;
    }
    if (D_ovl0B_02_8004A3D4 == 2 && D_ovl0B_02_8004A3D8 > 0) {
        pieces[4].unk10->unk48->unk4->unk4 = func_ovl0B_02_80048D68(pieces[4].unk10, 0) - 0.01f;
    }
    if (D_ovl0B_02_8004A3D8 != 0) {
        for (j = 0; j < D_ovl0B_02_8004A3D8; j++) {
            for (i = 0; i != n; i++) {
                pieces[i].unk10->unk1C = WRAP(g->unk4[j][0] + pieces[i].unk10->unk1C);
                pieces[i].unk10->unk20 = WRAP(g->unk4[j][1] + pieces[i].unk10->unk20);
            }
        }
    }
    for (i = 0; i < n; i++) {
        pieces[i].unk10->unkC &= ~0x1080;
        pieces[i].unk10->unk36 = 0;
        pieces[i].unk20 = 0xFF;
        pieces[i].unk10->unkC |= 1;
    }
}

/* The original takes i in $s1 (its callers' register). */
static UnkStructA_40 *func_ovl0B_02_80043F4C(s32 i) {
    UnkStructA_40 *obj;

    obj = func_ovl0B_02_80048D08(0x36, 0);
    M2C_FIELD(obj, s32 *, 0x38) = i * 2;
    obj->unk10 = 186.0f;
    obj->unk14 = 186.0f;
    obj->unk1C = 186.0f;
    obj->unk18 = 286.0f;
    func_ovl0B_02_80049178(func_ovl0B_02_80047020, obj, 0, 0, 0x130);
    return obj;
}

/* Starts the group's task (D_ovl0B_02_8004A150). */
static void func_ovl0B_02_80043EF8(s32 unused, s32 i) {
    D_ovl0B_02_8004A448 = 0;
    if (D_ovl0B_02_8004A150[i] != NULL) {
        D_ovl0B_02_8004A44C = func_ovl0B_02_80049178(D_ovl0B_02_8004A150[i], NULL, 0, 0, 0x130);
    }
}

/* Blinks the current page's piece. */
void func_ovl0B_02_80043E10(void) {
    UnkStructA_40 *obj;
    s16 alpha;

    while (TRUE) {
        obj = D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4].unk0[D_ovl0B_02_8004A3D8].unk10;
        for (alpha = 0; alpha < 0x80; alpha += 8) {
            obj->unk36 = alpha;
            func_ovl0B_02_800491C0();
        }
        for (alpha = 0x80; alpha != 0; alpha -= 8) {
            obj->unk36 = alpha;
            func_ovl0B_02_800491C0();
        }
    }
}

static UnkStructA_40 *func_ovl0B_02_80043054(s32 i);

/* The pages of a group. */
void func_ovl0B_02_800431C4(void) {
    s32 next[6][4] = {
        { 0x28, 0x31, 0x2D, 0x88 },
        { 0x38, 0x3E, 0x3C, 0x89 },
        { 0x48, 0x56, 0x50, 0x8A },
        { 0x58, 0x62, 0x5E, 0x8B },
        { 0x68, 0x8C, 0x6E, 0x74 },
        { 0x78, 0x8D, 0x7B, 0x7E },
    };
    UnkStructA_40 *marks[5];
    UnkStructA_40 *m;
    s32 task;
    Group_ovl0B_02 *g;
    Piece_ovl0B_02 *pieces;
    s32 buttons;
    s32 n;
    s32 i;
    s32 alpha;
    f32 t;
    f32 a;
    f32 b;

    func_ovl0B_02_80043150(D_ovl0B_02_800499F0, 3);
    D_ovl0B_02_8004A3C8 = func_ovl0B_02_80049178(func_ovl0B_02_80046100, NULL, 0, 0, 0x130);
    D_ovl0B_02_8004A3E8[0] = func_ovl0B_02_80043054(D_ovl0B_02_8004A3D8);
    for (n = 0; n != 4; n++) {
        if (func_ovl0B_02_80049410(0x15)[D_ovl0B_02_8004A3D4][n] == 0) {
            break;
        }
    }
    for (i = 0; i != 5; i++) {
        marks[i] = m = func_ovl0B_02_80048D08(0x19, 0);
        if (func_ovl0B_02_800493E0(D_ovl0B_02_8004A3D4 * 20 + D_ovl0B_02_8004A3D8 * 5 + i + 0x2C) != 0) {
            m->unkC |= 0x10000;
        } else {
            m->unkC |= 0x11080;
            m->unk36 = 0x50;
        }
        m->unk1C = 315.0f;
        m->unk14 = 72.0f;
        m->unk18 = 123.0f;
        m->unk28 = m->unk2C = m->unk30 = 0.18f;
        m->unk10 = i * 20.0f + -78.5f;
    }
    if (n >= 4) {
        D_ovl0B_02_8004A3C4 = 3;
    } else {
        D_ovl0B_02_8004A3C4 = n;
    }
    task = func_ovl0B_02_80049178(func_ovl0B_02_80043E10, NULL, 0, 0, 0x130);
    g = &D_ovl0B_02_8004A0EC[D_ovl0B_02_8004A3D4];
    pieces = g->unk0;
    func_ovl0B_02_80049198(0xC);
    while (TRUE) {
        buttons = func_ovl0B_02_80049530();
        if ((buttons & 0x100) && D_ovl0B_02_8004A3D8 < D_ovl0B_02_8004A3C4) {
            if (D_ovl0B_02_8004A3D8 < 3) {
                func_ovl0B_02_80049700(0);
                pieces[D_ovl0B_02_8004A3D8].unk10->unk36 = 0;
                D_ovl0B_02_8004A3D8++;
                if (D_ovl0B_02_8004A3D4 == 2 && D_ovl0B_02_8004A3D8 == 1) {
                    func_ovl0B_02_80049178(func_ovl0B_02_80046014, pieces[4].unk10, 0, 0, 0x130);
                }
                func_ovl0B_02_80048D10(D_ovl0B_02_8004A3E8[0]);
                D_ovl0B_02_8004A3E8[0] = func_ovl0B_02_80043054(D_ovl0B_02_8004A3D8);
                for (i = 0; i != 5; i++) {
                    if (func_ovl0B_02_800493E0(D_ovl0B_02_8004A3D4 * 20 + D_ovl0B_02_8004A3D8 * 5 + i + 0x2C) != 0) {
                        marks[i]->unkC &= ~0x1080;
                    } else {
                        marks[i]->unkC |= 0x1080;
                        marks[i]->unk36 = 0x50;
                    }
                }
                a = pieces[0].unk10->unk1C;
                b = pieces[0].unk10->unk20;
                for (t = 40.0f; t >= 0.0f; t -= 1.0f) {
                    for (i = 0; i < g->unk8; i++) {
                        pieces[i].unk10->unk1C = WRAP(g->unk4[D_ovl0B_02_8004A3D8 - 1][0] + (a + -g->unk4[D_ovl0B_02_8004A3D8 - 1][0] / 1600.0f * t * t));
                        pieces[i].unk10->unk20 = WRAP(g->unk4[D_ovl0B_02_8004A3D8 - 1][1] + (b + -g->unk4[D_ovl0B_02_8004A3D8 - 1][1] / 1600.0f * t * t));
                    }
                    func_ovl0B_02_800491C0();
                }
            }
        } else if (buttons & 0x200) {
            if (D_ovl0B_02_8004A3D8 > 0) {
                func_ovl0B_02_80049700(0);
                pieces[D_ovl0B_02_8004A3D8].unk10->unk36 = 0;
                if (D_ovl0B_02_8004A3D4 == 2 && D_ovl0B_02_8004A3D8 == 1) {
                    func_ovl0B_02_80049178(func_ovl0B_02_80045F58, pieces[4].unk10, 0, 0, 0x130);
                }
                D_ovl0B_02_8004A3D8--;
                func_ovl0B_02_80048D10(D_ovl0B_02_8004A3E8[0]);
                D_ovl0B_02_8004A3E8[0] = func_ovl0B_02_80043054(D_ovl0B_02_8004A3D8);
                for (i = 0; i != 5; i++) {
                    if (func_ovl0B_02_800493E0(D_ovl0B_02_8004A3D4 * 20 + D_ovl0B_02_8004A3D8 * 5 + i + 0x2C) != 0) {
                        marks[i]->unkC &= ~0x1080;
                    } else {
                        marks[i]->unkC |= 0x1080;
                        marks[i]->unk36 = 0x50;
                    }
                }
                a = pieces[0].unk10->unk1C;
                b = pieces[0].unk10->unk20;
                for (t = 40.0f; t >= 0.0f; t -= 1.0f) {
                    for (i = 0; i < g->unk8; i++) {
                        pieces[i].unk10->unk1C = (a + g->unk4[D_ovl0B_02_8004A3D8][0] / 1600.0f * t * t) - g->unk4[D_ovl0B_02_8004A3D8][0] >= 360.0f
                            ? (a + g->unk4[D_ovl0B_02_8004A3D8][0] / 1600.0f * t * t) - g->unk4[D_ovl0B_02_8004A3D8][0] - 360.0f
                            : (a + g->unk4[D_ovl0B_02_8004A3D8][0] / 1600.0f * t * t) < g->unk4[D_ovl0B_02_8004A3D8][0]
                            ? (a + g->unk4[D_ovl0B_02_8004A3D8][0] / 1600.0f * t * t) - g->unk4[D_ovl0B_02_8004A3D8][0] + 360.0f
                            : (a + g->unk4[D_ovl0B_02_8004A3D8][0] / 1600.0f * t * t) - g->unk4[D_ovl0B_02_8004A3D8][0];
                        pieces[i].unk10->unk20 = (b + g->unk4[D_ovl0B_02_8004A3D8][1] / 1600.0f * t * t) - g->unk4[D_ovl0B_02_8004A3D8][1] >= 360.0f
                            ? (b + g->unk4[D_ovl0B_02_8004A3D8][1] / 1600.0f * t * t) - g->unk4[D_ovl0B_02_8004A3D8][1] - 360.0f
                            : (b + g->unk4[D_ovl0B_02_8004A3D8][1] / 1600.0f * t * t) < g->unk4[D_ovl0B_02_8004A3D8][1]
                            ? (b + g->unk4[D_ovl0B_02_8004A3D8][1] / 1600.0f * t * t) - g->unk4[D_ovl0B_02_8004A3D8][1] + 360.0f
                            : (b + g->unk4[D_ovl0B_02_8004A3D8][1] / 1600.0f * t * t) - g->unk4[D_ovl0B_02_8004A3D8][1];
                    }
                    func_ovl0B_02_800491C0();
                }
            }
        } else if (func_ovl0B_02_80048738() & 0x4000) {
            func_ovl0B_02_80049700(2);
            func_ovl0B_02_80049180(task);
            func_ovl0B_02_80043018(D_ovl0B_02_800499F0, 3);
            func_ovl0B_02_80049180(D_ovl0B_02_8004A3C8);
            func_ovl0B_02_80048D10(D_ovl0B_02_8004A3E8[0]);
            for (i = 0; i < 5; i++) {
                func_ovl0B_02_80048D10(marks[i]);
            }
            D_ovl0B_02_80049A50[0].unk10->unkC &= ~1;
            for (i = 0; i < g->unk8; i++) {
                pieces[i].unk10->unk36 = 0xFF;
                pieces[i].unk10->unkC |= 0x1080;
            }
            for (alpha = 0xFF; alpha > 0; alpha -= 4) {
                D_ovl0B_02_80049A50[0].unk10->unk36 = 0xFF - alpha;
                for (i = 0; i < g->unk8; i++) {
                    pieces[i].unk10->unk36 = alpha;
                    pieces[i].unk10->unk28 = pieces[i].unk10->unk2C = pieces[i].unk10->unk30 =
                        (alpha + 0x100) * pieces[0].unk30 * 0.001953125f;
                }
                func_ovl0B_02_800491C0();
            }
            D_ovl0B_02_80049A50[0].unk10->unkC &= ~0x80;
            for (i = 0; i < g->unk8; i++) {
                pieces[i].unk10->unkC |= 1;
            }
            func_ovl0B_02_80049178(func_ovl0B_02_80044490, NULL, 0, 0, 0x130);
            func_ovl0B_02_80049188();
        } else if (func_ovl0B_02_80048738() & 0x8000) {
            func_ovl0B_02_80049180(task);
            func_ovl0B_02_80049700(0x25);
            func_ovl0B_02_80049718();
            func_ovl0B_02_80048788();
            func_ovl0B_02_80048D10(D_ovl0B_02_8004A3E8[0]);
            func_ovl0B_02_80049180(D_ovl0B_02_8004A3C8);
            for (i = 0; i < 3; i++) {
                func_ovl0B_02_80048D10(D_ovl0B_02_800499F0[i].unk1C);
            }
            for (i = 0; i < 5; i++) {
                func_ovl0B_02_80048D10(marks[i]);
            }
            func_ovl0B_02_80049178(func_ovl0B_02_800470B0, NULL, 0, 0, 0x130);
            for (i = 0; i < g->unk8; i++) {
                pieces[i].unk10->unk36 = 0xFF;
                pieces[i].unk10->unkC |= 0x1080;
            }
            for (alpha = 0xFF; alpha > 0; alpha -= 8) {
                for (i = 0; i < g->unk8; i++) {
                    pieces[i].unk10->unk36 = alpha;
                }
                func_ovl0B_02_800491C0();
            }
            for (i = 0; i < g->unk8; i++) {
                pieces[i].unk10->unkC |= 1;
            }
            func_ovl0B_02_80048720(next[D_ovl0B_02_8004A3D4][D_ovl0B_02_8004A3D8], 0x10, 0);
            while (TRUE) {
                func_ovl0B_02_800491C0();
            }
        }
        func_ovl0B_02_800491C0();
    }
}

/* The original takes n in $s2 and the boxes in $s3 (its callers'
 * registers). */
static void func_ovl0B_02_80043150(Box_ovl0B_02 *boxes, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        boxes[i].unk1C = func_ovl0B_02_80048D08(boxes[i].unk14, 0);
        M2C_FIELD(boxes[i].unk1C, s32 *, 0x38) = boxes[i].unk18;
        boxes[i].unk1C->unk28 = boxes[i].unk8;
        boxes[i].unk1C->unk2C = boxes[i].unkC;
        func_ovl0B_02_800430C4(&boxes[i], boxes[i].unk10);
    }
}

/* The original takes the scale in $f12. */
static void func_ovl0B_02_800430C4(Box_ovl0B_02 *box, f32 scale) {
    box->unk10 = scale;
    box->unk1C->unk10 = box->unk0 - box->unk8 * scale * 0.5f;
    box->unk1C->unk14 = box->unk4 - box->unkC * box->unk10 * 0.5f;
    box->unk1C->unk18 = box->unk1C->unk10 + box->unk8 * box->unk10;
    box->unk1C->unk1C = box->unk1C->unk14 + box->unkC * box->unk10;
}

/* The original takes i in $s1 (its callers' register). */
static UnkStructA_40 *func_ovl0B_02_80043054(s32 i) {
    UnkStructA_40 *obj;

    obj = func_ovl0B_02_80048D08(0x28, 0);
    M2C_FIELD(obj, s32 *, 0x38) = i * 2;
    obj->unk10 = 186.0f;
    obj->unk14 = 186.0f;
    obj->unk1C = 186.0f;
    obj->unk18 = 286.0f;
    func_ovl0B_02_80049178(func_ovl0B_02_80047020, obj, 0, 0, 0x130);
    return obj;
}

static void func_ovl0B_02_80043010(void) {
}

/* The original passes n in $s2 (its callers' register). */
static void func_ovl0B_02_80043018(Box_ovl0B_02 *boxes, s32 n) {
    s32 i;

    func_ovl0B_02_80043010();
    for (i = 0; i < n; i++) {
        func_ovl0B_02_80048D10(boxes[i].unk1C);
    }
}
