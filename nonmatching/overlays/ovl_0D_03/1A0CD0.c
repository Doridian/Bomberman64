/*
 * NON_MATCHING: ovl_0D_03's stage object, complete: all 30 functions and the
 * stubs the inlined statics leave in their places (every function and stub
 * at the original's address up to 80043FA0's group; see below), .data and
 * .bss as the original.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 1025, jp 1025
 *
 * ovl_0D_02's sibling (nonmatching/overlays/ovl_0D_02, renamed by
 * scratch/0D_03/ren02.py): most functions are 0D_02's. What still differs
 * in us (fcmp counts a static with the function before it):
 * - func_ovl0D_03_80044CBC (238; the handler): the original inlines the
 *   gates' code (80043770's body) into case 3; here it stays a call, so the
 *   handler is 0x134 bytes, not 0x3C0, and every later function is shifted.
 *   Tried without gain: 80043770 without its fake, defined above the
 *   handler, and case 3 written out (then 80043758 is no longer inlined).
 * - func_ovl0D_03_8004305C (432 with the gate statics after it): 26 words
 *   short; the original keeps the entity indices 1 and 2 in s0 (an
 *   inlined static's parameter, as it seems) and spills 175.0f * 10.0f.
 * - func_ovl0D_03_8004419C (193, with 800441C4 to 80044588): 80044588 is
 *   5 words short.
 * - func_ovl0D_03_80044AA8 (54): 3 words short.
 * - func_ovl0D_03_80043C44 (103): 1 word short.
 * - func_ovl0D_03_80045EF0 (5): as ovl_0D_02's 8004596C (the timer
 *   static's grid[] place).
 */
#include "common.h"

/*
 * ovl_0D_03's stage object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).
 * ovl_0D_02 is its closest sibling (nonmatching/overlays), then 0D_04, 0D_05
 * and 0D_06.
 */

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10[0x18];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ UnkStructA_40 *unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ u8 unk50[4];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 unk58[0x10];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
} Obj_0D03;

/* a model placed on the stage (as in ovl_0D_04) */
typedef struct {
    /* 0x00 */ Obj_0D03 *obj;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
} Ent_0D03;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Trio_0D03;

typedef struct {
    f32 x, y, z, w;
} Vec4f_0D03;


/* passed to func_ovl0D_03_80047260 (as in ovl_0D_06) */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18[3];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s32 unk28[7];
} Cam_0D03;

void func_ovl0D_03_800469E8(s32); /* 0xC00 */
void func_ovl0D_03_800469F8(s32 *); /* 0xC02 */
void func_ovl0D_03_80046A28(s32, s32, s32, s32, s32, s32); /* 0xD05 */
void func_ovl0D_03_80046A30(s32, s32, s32, s32, s32, s32, s32); /* 0xD06 */
void func_ovl0D_03_80046A40(f32, f32, f32, s32 *, s32); /* 0xD08 */
void func_ovl0D_03_80046A48(f32, f32, f32, s32 *, s32); /* 0xD09 */
s32 func_ovl0D_03_80046A58(s32, s32, s32); /* 0xD0B */
void func_ovl0D_03_80046A60(s32); /* 0xD0C */
void func_ovl0D_03_80046A68(void); /* 0xD0D */
void func_ovl0D_03_80046AB0(s32); /* 0xD16 */
s32 func_ovl0D_03_80046AB8(s32); /* 0xE00 */
void func_ovl0D_03_80046AC0(s32, s32, s32, s32, s32, s32, s32, s32); /* 0xE01 */
void func_ovl0D_03_80046AD0(void (*)(Obj_0D03 *)); /* 0xE03 */
void func_ovl0D_03_80046AE0(s32, s32, s32); /* 0xF00 */
s32 func_ovl0D_03_80046AE8(void); /* 0xF01 */
void func_ovl0D_03_80046B30(s32); /* 0xF0A */
s32 *func_ovl0D_03_80046B38(void); /* 0xF0B */
void func_ovl0D_03_80046B50(s32); /* 0xF0E */
void func_ovl0D_03_80046B58(s32); /* 0xF0F */
void func_ovl0D_03_80046B98(void); /* 0x1000 */
void func_ovl0D_03_80046BA0(s32, s32, s32); /* 0x1001 */
void func_ovl0D_03_80046BA8(void *); /* 0x1002 */
s32 func_ovl0D_03_80046BB0(s32, s32, s32, s32); /* 0x1003 */
s32 func_ovl0D_03_80046BC8(void); /* 0x1006 */
void func_ovl0D_03_80046BD0(s32, void *); /* 0x1007 */
void func_ovl0D_03_80046BD8(s32); /* 0x1008 */
void func_ovl0D_03_80046BE0(s32); /* 0x1009 */
void func_ovl0D_03_80046BE8(s32, s32, f32, s32, s32, s32, s32); /* 0x100A */
void func_ovl0D_03_80046BF0(const char *); /* 0x100B */
void func_ovl0D_03_80046BF8(void); /* 0x100C */
void func_ovl0D_03_80046C00(s32); /* 0x100D */
void func_ovl0D_03_80046C10(s32); /* 0x100F */
void func_ovl0D_03_80046C80(s32); /* 0x101D */
void func_ovl0D_03_80046C98(void); /* 0x1020 */
f32 func_ovl0D_03_80047128(UnkStructA_40 *, s32); /* 0x150C */
s32 func_ovl0D_03_80047130(UnkStructA_40 *, s32, s32, s32, s32, s32); /* 0x150D */
void func_ovl0D_03_80047138(s32); /* 0x150E */
void func_ovl0D_03_80047228(f32, f32, f32); /* 0x1704 */
void func_ovl0D_03_80047248(f32, f32, f32); /* 0x1708 */
void func_ovl0D_03_80047250(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0D_03_80047260(Cam_0D03 *, s32, s32); /* 0x170B */
s32 func_ovl0D_03_80047278(void); /* 0x170E */
void func_ovl0D_03_80047280(void); /* 0x170F */
void func_ovl0D_03_80047288(s32); /* 0x1710 */
void func_ovl0D_03_80047290(s32); /* 0x1711 */
void func_ovl0D_03_800472A0(s32); /* 0x1713 */
void func_ovl0D_03_800472D8(f32, f32, f32, f32); /* 0x171A */
void func_ovl0D_03_800472E8(f32, f32, f32, f32); /* 0x171C */
void func_ovl0D_03_80047300(s32); /* 0x171F */
void func_ovl0D_03_80047310(f32, f32, f32); /* 0x1721 */
void func_ovl0D_03_80047348(void); /* 0x1728 */
void func_ovl0D_03_80047358(f32, f32); /* 0x172A */
void func_ovl0D_03_80047378(f32 *, f32 *, f32 *); /* 0x1803 */
void func_ovl0D_03_80047380(f32 *, f32 *); /* 0x1804 */
s32 func_ovl0D_03_80047398(Obj_0D03 *, s32); /* 0x1807 */
void func_ovl0D_03_800473B8(Obj_0D03 *, s32); /* 0x180B */
void func_ovl0D_03_800473E8(Obj_0D03 *, s32); /* 0x1811 */
void func_ovl0D_03_800473F0(Obj_0D03 *, s32); /* 0x1812 */
void func_ovl0D_03_80047400(Obj_0D03 *); /* 0x1814 */
Obj_0D03 *func_ovl0D_03_80047408(s32, s32, s32, s32, s32); /* 0x1815 */
Obj_0D03 *func_ovl0D_03_80047410(s32, s32, s32, s32); /* 0x1816 */
Obj_0D03 *func_ovl0D_03_80047420(Obj_0D03 *); /* 0x1818 */
Obj_0D03 *func_ovl0D_03_80047430(s32, s32, f32, f32, f32); /* 0x181A */
s32 func_ovl0D_03_80047460(Obj_0D03 *, f32 *, f32 *, f32 *); /* 0x1820 */
void func_ovl0D_03_80047468(Obj_0D03 *); /* 0x1821 */
void func_ovl0D_03_800474B8(Obj_0D03 *, f32 *); /* 0x182B */
void func_ovl0D_03_800474C0(void *, Obj_0D03 *); /* 0x182C */
void func_ovl0D_03_80047538(void (*)(void), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0D_03_80047548(void); /* 0x1902 */
void func_ovl0D_03_80047558(s32); /* 0x1904 */
void *func_ovl0D_03_80047560(void); /* 0x1905 */
void func_ovl0D_03_80047580(void); /* 0x1909 */
f32 func_ovl0D_03_800476E0(f32); /* 0x1D00 */
f64 func_ovl0D_03_800476F0(void); /* 0x1D02 */
s32 func_ovl0D_03_800476F8(s32); /* 0x1D03 */
void func_ovl0D_03_800477B0(s32); /* 0x1E06 */
s32 func_ovl0D_03_800477C0(s32); /* 0x1E08 */
void func_ovl0D_03_80047828(s32); /* 0x2002 */
void func_ovl0D_03_80047830(void); /* 0x2003 */
void func_ovl0D_03_80047860(s32, s32, s32); /* 0x2101 */
void func_ovl0D_03_80047880(s32); /* 0x2200 */
void func_ovl0D_03_800478A0(u32 (*)[3]); /* 0x2300 */
void func_ovl0D_03_800478B8(u32 (*)[3]); /* 0x2303 */
void func_ovl0D_03_80047990(s32, f32 *, Obj_0D03 *); /* 0x2601 */
void func_ovl0D_03_800479B8(s16, s32); /* 0x2702 */
void func_ovl0D_03_800479C0(s16, s32); /* 0x2703 */
void func_ovl0D_03_800479C8(void); /* 0x2704 */
void func_ovl0D_03_80047A00(s32, s16, s16, s16); /* 0x2800 */
void func_ovl0D_03_80047A08(s32, f32, f32, f32); /* 0x2801 */
void func_ovl0D_03_80047A48(s32, s32, s32); /* 0x2A00 */
void func_ovl0D_03_80047A80(s32, s32, s32, s32); /* 0x2A07 */
void func_ovl0D_03_80047AA8(void); /* 0x2A0C */
void func_ovl0D_03_80047AC0(s32); /* 0x2B00 */
void func_ovl0D_03_80047AE0(s32, f32, f32, f32); /* 0x2B04 */
void func_ovl0D_03_80047AE8(s32, f32 *); /* 0x2B05 */
void func_ovl0D_03_80047C38(void); /* 0x3000 */
void func_ovl0D_03_80047C40(void); /* 0x3001 */

void func_ovl0D_03_8004305C(void);
void func_ovl0D_03_80043770(void);
void func_ovl0D_03_80043A84(void);
void func_ovl0D_03_80043B5C(void);
void func_ovl0D_03_80043C44(void);
void func_ovl0D_03_80043DE4(void);
void func_ovl0D_03_80043E28(void);
void func_ovl0D_03_80043EC8(void);
void func_ovl0D_03_80043F58(f32);
void func_ovl0D_03_80043FA0(void);
void func_ovl0D_03_80044110(void);
void func_ovl0D_03_80044138(void);
void func_ovl0D_03_80044174(void);
void func_ovl0D_03_8004419C(void);
void func_ovl0D_03_80044A3C(void);
void func_ovl0D_03_80044A88(void);
void func_ovl0D_03_80044AA8(void);
void func_ovl0D_03_80044CBC(s32);
void func_ovl0D_03_8004507C(void);
void func_ovl0D_03_80045224(Obj_0D03 *);
void func_ovl0D_03_80045268(Obj_0D03 *, s32, s32, f32, f32);
void func_ovl0D_03_80045340(s32, Obj_0D03 *);
void func_ovl0D_03_80045374(void);
void func_ovl0D_03_80045470(void);
void func_ovl0D_03_800457F8(void);
void func_ovl0D_03_80045B24(void);
void func_ovl0D_03_80045EF0(void);
void func_ovl0D_03_80046474(s32, s32);
void func_ovl0D_03_800464E8(f32, f32, f32, f32, s32);
void func_ovl0D_03_8004661C(f32, f32, f32);

static void func_ovl0D_03_80043010(Obj_0D03 *);
static void func_ovl0D_03_80043054(void);
static void func_ovl0D_03_80043300(s32, s32 *, s32 *);
static s32 func_ovl0D_03_80043374(f32);
static void func_ovl0D_03_8004337C(Ent_0D03 *);
static void func_ovl0D_03_80043758(Ent_0D03 *, s32);
static void func_ovl0D_03_80043760(void);
static void func_ovl0D_03_80043768(void);
static void func_ovl0D_03_80043A7C(void);
static void func_ovl0D_03_80043B98(Ent_0D03 *);
static void func_ovl0D_03_80043C14(void);
static void func_ovl0D_03_80043C1C(void);
static void func_ovl0D_03_80043C24(void);
static void func_ovl0D_03_80043C2C(void);
static void func_ovl0D_03_80043C34(void);
static void func_ovl0D_03_80043C3C(void);
static void func_ovl0D_03_80043DDC(void);
static void func_ovl0D_03_800441BC(void);
static void func_ovl0D_03_800441C4(s32);
static void func_ovl0D_03_80044314(s32);
static void func_ovl0D_03_8004431C(Ent_0D03 *);
static void func_ovl0D_03_8004449C(Vec3f *, Vec3f (*)[4]);
static void func_ovl0D_03_800444A4(void);
static void func_ovl0D_03_800444AC(void);
static void func_ovl0D_03_800444B4(Ent_0D03 *);
static void func_ovl0D_03_80044558(void);
static void func_ovl0D_03_80044560(void);
static void func_ovl0D_03_80044568(void);
static void func_ovl0D_03_80044570(void);
static void func_ovl0D_03_80044578(void);
static void func_ovl0D_03_80044580(void);
static void func_ovl0D_03_80044588(void);
static void func_ovl0D_03_80044AA0(void);
static void func_ovl0D_03_80045EE0(Ent_0D03 *, s32);
static void func_ovl0D_03_80045EE8(Ent_0D03 *, s32 *);
static void func_ovl0D_03_80046678(void);
static void func_ovl0D_03_80046680(void);
static void func_ovl0D_03_80046688(void);
static void func_ovl0D_03_80046690(void);
static void func_ovl0D_03_80046698(void);

#define UNK_MACRO_ovl0D_03_80043770() \
    D_ovl0D_03_8004815C = func_ovl0D_03_80046BC8(); func_ovl0D_03_80046BA8(&D_ovl0D_03_80048150); func_ovl0D_03_80046BD0(D_ovl0D_03_8004815C, &D_ovl0D_03_80048140)

/* .bss */
Vec4f_0D03 D_ovl0D_03_80048140;
Vec3f D_ovl0D_03_80048150;
s32 D_ovl0D_03_8004815C;
s32 D_ovl0D_03_80048164;
s32 D_ovl0D_03_80048168;
u8 D_ovl0D_03_8004816C[0x4]; /* unused (func_ovl0D_03_80046698) */
Vec3f D_ovl0D_03_80048170;
Obj_0D03 *D_ovl0D_03_8004817C;
s32 D_ovl0D_03_80048180;
s32 D_ovl0D_03_80048184;
s32 D_ovl0D_03_80048188[3];
s32 D_ovl0D_03_80048194;
s32 D_ovl0D_03_80048198;
s32 D_ovl0D_03_8004819C;
s32 *D_ovl0D_03_800481A0;
u8 D_ovl0D_03_800481A4[0x4]; /* unused (func_ovl0D_03_80046698) */
/* where the debris of D_ovl0D_03_80047F94 falls: three rows of four */
Vec3f D_ovl0D_03_800481A8[1][3][4];

/* .data */
/* passed to func_ovl0D_03_800478A0: three 12-byte records */
u32 D_ovl0D_03_80047CE0[][3] = {
    { 0x9A0002, 0x8000E, 4 },
    { 0x9B0002, 0xE, 4 },
    { 0x970001, 0xF, 0x2004 },
};
/* passed to func_ovl0D_03_800478B8 */
u32 D_ovl0D_03_80047D04[][3] = {
    { 0, 4, 0 },
    { 4, 0x980000, 0x84 },
};
Ent_0D03 D_ovl0D_03_80047D1C[3] = {
    { NULL, -1, 0x14F, 0, 0x400, 0x20, 0x400, 10.0f, 60.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14D, 0, 0x400, 0x20, 0x400, 470.0f, -75.0f, 270.0f, 0.0f, 90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14C, 0, 0x400, 0x20, 0x400, -100.0f, 155.0f, 135.0f, 0.0f, 90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D03 D_ovl0D_03_80047DC4[3] = {
    { NULL, -1, 0x14B, 0, 0x400, 0x20, 0x400, 0.0f, 155.0f, 130.0f, 0.0f, 90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14B, -1, -1, -1, -1, 460.0f, 20.0f, 60.0f, 0.0f, 90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14B, -1, -1, -1, -1, 500.0f, -75.0f, 280.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
/* the gates */
Ent_0D03 D_ovl0D_03_80047E6C[2] = {
    { NULL, -1, 0x15D, -1, -1, -1, -1, 150.0f, 80.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x15D, -1, -1, -1, -1, 170.0f, 80.0f, 200.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
/* the flags set once each gate is open */
s32 D_ovl0D_03_80047EDC[2] = { 0x401, 0x402 };
Ent_0D03 D_ovl0D_03_80047EE4[1] = {
    { NULL, -1, 0x14A, -1, -1, -1, -1, -10.0f, 105.0f, 80.0f, 0.0f, -90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D03 D_ovl0D_03_80047F1C[2] = {
    { NULL, -1, 0x161, -1, -1, -1, -1, 260.0f, 100.0f, 90.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x161, -1, -1, -1, -1, 90.0f, 100.0f, 90.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
/* the flags set once each of D_ovl0D_03_80047F1C is done */
s32 D_ovl0D_03_80047F8C[2] = { 0x40E, 0x423 };
Ent_0D03 D_ovl0D_03_80047F94[1] = {
    { NULL, -1, 0x160, -1, -1, -1, -1, 170.0f, 80.0f, 240.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
/* the corner of D_ovl0D_03_800481A8's rows */
Vec3f D_ovl0D_03_80047FCC[1] = {
    { 160.0f, 85.0f, 240.0f },
};
/* the flag set once D_ovl0D_03_80047F94 is done */
s32 D_ovl0D_03_80047FD8[1] = { 0x419 };
Trio_0D03 D_ovl0D_03_80047FDC[5] = {
    { 0, 9, 0xE7 },
    { 1, 8, 0xE6 },
    { 2, 2, 0xE0 },
    { 3, 1, 0xDE },
    { 4, 9, 0xE7 },
};
Cam_0D03 D_ovl0D_03_80048018 = { 0x708, 1, 1, 0.0f, 0.0f, 0.0f, { 0, 0, 0 }, 0.1875f };

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0D_03_80046698(void) {
    D_ovl0D_03_8004816C[0] = D_ovl0D_03_800481A4[0];
}

static void func_ovl0D_03_80046690(void) {
}

static void func_ovl0D_03_80046688(void) {
}

static void func_ovl0D_03_80046680(void) {
}

static void func_ovl0D_03_80046678(void) {
}

void func_ovl0D_03_8004661C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0D_03_80047228(D_ovl0D_03_80048170.x, D_ovl0D_03_80048170.y, D_ovl0D_03_80048170.z);
    func_ovl0D_03_80047248(arg0, arg1, arg2);
    func_ovl0D_03_80047558(180);
}

/* unused here (ovl_0D_04's 80043478) */
void func_ovl0D_03_800464E8(f32 x, f32 y, f32 z, f32 ang, s32 arg4) {
    func_ovl0D_03_80046B50(0);
    func_ovl0D_03_80046BD8(1);
    func_ovl0D_03_80047290(0xF);
    if (func_ovl0D_03_80047278() == 1) {
        func_ovl0D_03_80047280();
    }
    func_ovl0D_03_80046C98();
    func_ovl0D_03_800479C8();
    func_ovl0D_03_80047AA8();
    func_ovl0D_03_80047558(60);
    func_ovl0D_03_80046C00(1);
    func_ovl0D_03_80047AC0(0x29);
    func_ovl0D_03_80046B58(1);
    func_ovl0D_03_80046C10(0x40);
    func_ovl0D_03_80046BE8(arg4, 6, 8.5f, 0, 1, 1, 0);
    func_ovl0D_03_80046BD8(1);
    func_ovl0D_03_80047558(30);
    func_ovl0D_03_80047348();
    func_ovl0D_03_80047290(0x7F);
    func_ovl0D_03_80047228(x, y, z);
    func_ovl0D_03_80047248(ang, 45.0f, 32768.0f);
    func_ovl0D_03_800472A0(0);
    func_ovl0D_03_80047558(15);
    func_ovl0D_03_80047AC0(0x69);
    func_ovl0D_03_80047558(15);
    func_ovl0D_03_80047AC0(0x6F);
}

/* unused here (ovl_0D_06's 80045884) */
void func_ovl0D_03_80046474(s32 arg0, s32 arg1) {
    func_ovl0D_03_80046BE8(0x200, 5, 1.1111f, 1, 0, 0, 0);
    func_ovl0D_03_80046BD8(1);
    func_ovl0D_03_80047558(30);
    func_ovl0D_03_80047828(2);
    func_ovl0D_03_80047830();
    func_ovl0D_03_80046AE0(arg0, arg1, 1);
}

/* the task of each of D_ovl0D_03_80047F1C (its index is the argument) */
void func_ovl0D_03_80045EF0(void) {
    s32 idx;
    Ent_0D03 *e;
    s32 flag;
    Vec3f pos;
    s32 grid[6];
    s32 cnt;
    s32 r;
    f32 ang;
    Vec3f tgt;
    s32 pad;
    s32 timer;

    idx = (s32) func_ovl0D_03_80047560();
    e = &D_ovl0D_03_80047F1C[idx];
    flag = D_ovl0D_03_80047F8C[idx];
    pos.x = e->unk14 * 10.0f + 150.0f;
    pos.y = e->unk18 * 10.0f;
    pos.z = e->unk1C * 10.0f + 150.0f;
    cnt = 0;
    timer = 240 / (idx + 1);
    func_ovl0D_03_80046A40(pos.x, pos.y, pos.z, grid, 0);
    while (func_ovl0D_03_800477C0(flag) == 0) {
        if (e->obj == NULL) {
            break;
        }
        e->obj->unk40->unk10 = pos.x;
        e->obj->unk40->unk18 = pos.z;
        tgt.x = D_ovl0D_03_80048140.x;
        tgt.y = pos.y;
        tgt.z = D_ovl0D_03_80048140.z;
        func_ovl0D_03_80047378(&pos.x, &tgt.x, &ang);
        e->obj->unk40->unk20 = ang;
        if (func_ovl0D_03_800477C0(0x424) != 0) {
            func_ovl0D_03_80045EE8(e, &timer);
        }
        if (idx == (cnt >> 2)) {
            cnt = 0;
            r = func_ovl0D_03_80047398(e->obj, 0x40);
            if (r & 0x40) {
                if ((r & 0x2000) || (r & 0x4000)) {
                    func_ovl0D_03_80045EE0(e, flag);
                } else {
                    func_ovl0D_03_80045340(0x26, e->obj);
                }
            }
        }
        cnt++;
        func_ovl0D_03_80047580();
    }
    func_ovl0D_03_80047548();
}

/* every few seconds, when the player is near, the model throws a bomb */
static void func_ovl0D_03_80045EE8(Ent_0D03 *e, s32 *timer) {
    UnkStructA_40 *p;
    s32 grid[6];

    if (*timer == 0) {
        p = e->obj->unk40;
        func_ovl0D_03_80046A40(p->unk10, p->unk14, p->unk18, grid, 0);
        if (func_ovl0D_03_80046BB0(grid[0] - 12, grid[2] - 12, grid[0] + 12, grid[2] + 12) != 0 &&
            func_ovl0D_03_80046BB0(grid[0] - 2, grid[2] - 2, grid[0] + 2, grid[2] + 2) == 0) {
            func_ovl0D_03_80047538(func_ovl0D_03_80045B24, e, 0, 0, 0x110);
            func_ovl0D_03_80047310(10.0f, 10.0f, 10.0f);
            func_ovl0D_03_80047300(60);
        }
        *timer = (D_ovl0D_03_800481A0[4] != 0) ? 240 : 360;
    } else {
        (*timer)--;
    }
}

/* a model's hit: it fades out, scattering debris, and its tiles become solid */
static void func_ovl0D_03_80045EE0(Ent_0D03 *e, s32 flag) {
    s32 i;
    s32 k;
    Vec3f v;
    Obj_0D03 *o;

    o = e->obj;
    k = 5;
    func_ovl0D_03_800473E8(o, 0x80000);
    func_ovl0D_03_80045340(0x73, o);
    for (i = 0; i < 30; i++) {
        o->unk40->unk36 = (u8) ((1.0f - i / 30.0f) * 255.0f);
        if (++k >= 6) {
            k = 0;
            func_ovl0D_03_800474B8(o, &v.x);
            if (func_ovl0D_03_800476F8(1) != 0) {
                v.x += 300.0 * func_ovl0D_03_800476F0();
            } else {
                v.x -= 300.0 * func_ovl0D_03_800476F0();
            }
            v.y += 100.0 + 300.0 * func_ovl0D_03_800476F0();
            if (func_ovl0D_03_800476F8(1) != 0) {
                v.z += 300.0 * func_ovl0D_03_800476F0();
            } else {
                v.z -= 300.0 * func_ovl0D_03_800476F0();
            }
            func_ovl0D_03_80047990(20, &v.x, NULL);
        }
        func_ovl0D_03_80047580();
    }
    func_ovl0D_03_800473F0(o, 0x01080000);
    func_ovl0D_03_800444B4(e);
    func_ovl0D_03_800477B0(flag);
}

/* the task a model's hit starts: a bomb flies from it to the player */
void func_ovl0D_03_80045B24(void) {
    Vec3f tmp;
    Vec3f dir;
    Vec3f pos;
    Ent_0D03 *e;
    Obj_0D03 *o;
    Obj_0D03 *o2;
    s32 n;
    f32 dx;
    f32 dz;

    e = func_ovl0D_03_80047560();
    o = func_ovl0D_03_80047408(0, 0, 0x01000210, 0x60, 0);
    o2 = func_ovl0D_03_80047420(o);
    o2->unk4C = 1.5f;
    o2->unk54 = 1.5f;
    o->unk40->unk30 = 1.5f;
    o->unk40->unk2C = 1.5f;
    o->unk40->unk28 = 1.5f;
    dir.x = e->obj->unk40->unk20;
    dir.y = 60.0f;
    dir.z = 500.0f;
    func_ovl0D_03_80047380(&dir.x, &pos.x);
    pos.x += e->obj->unk40->unk10;
    pos.y += e->obj->unk40->unk14;
    pos.z += e->obj->unk40->unk18;
    o->unk40->unk10 = pos.x;
    o->unk40->unk14 = pos.y;
    o->unk40->unk18 = pos.z;
    func_ovl0D_03_80047990(7, &pos.x, NULL);
    func_ovl0D_03_80047990(14, &pos.x, NULL);
    func_ovl0D_03_80047580();
    func_ovl0D_03_80047AE8(0x61, &pos.x);
    o->unk68 = 100.0f;
    o->unk70 = 1.2250001f;
    o->unk6C = 0.0f;
    o->unk74 = 1000.0f;
    n = 0;
    while ((D_ovl0D_03_80048140.y < o->unk40->unk14 || o->unk6C < o->unk68) && o->unk68 != 0.0f) {
        func_ovl0D_03_80047460(o, &o->unk68, &o->unk6C, &o->unk70);
        n++;
    }
    o->unk40->unk14 = pos.y;
    o->unk6C = 0.0f;
    o->unk68 = 100.0f;
    dx = (D_ovl0D_03_80048140.x - pos.x) / n;
    dz = (D_ovl0D_03_80048140.z - pos.z) / n;
    while (o->unk68 != 0.0f) {
        o->unk40->unk10 += dx;
        o->unk40->unk18 += dz;
        func_ovl0D_03_80047460(o, &o->unk68, &o->unk6C, &o->unk70);
        func_ovl0D_03_80047580();
    }
    func_ovl0D_03_800473F0(o, 0x01000000);
    pos.x = o->unk40->unk10;
    pos.y = o->unk40->unk14 + 5.0f;
    pos.z = o->unk40->unk18;
    func_ovl0D_03_80047990(10, &pos.x, NULL);
    func_ovl0D_03_80047AE8(0x62, &pos.x);
    func_ovl0D_03_80047400(o);
    func_ovl0D_03_80047548();
}

/* the task of each of D_ovl0D_03_80047F94 (its index is the argument):
 * once hit, it burns for three seconds, throwing debris */
void func_ovl0D_03_800457F8(void) {
    s32 idx;
    s32 i;
    s32 r;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;

    idx = (s32) func_ovl0D_03_80047560();
    do {
        func_ovl0D_03_80047558(idx + 7);
        D_ovl0D_03_8004817C->unk30 = 1;
        D_ovl0D_03_8004817C->unk34 = 50.0f;
        D_ovl0D_03_8004817C->unk38 = 50.0f;
        D_ovl0D_03_8004817C->unk40->unk10 = D_ovl0D_03_80047F94[idx].obj->unk40->unk10 + -300.0f;
        D_ovl0D_03_8004817C->unk40->unk14 = D_ovl0D_03_80047F94[idx].obj->unk40->unk14 + 200.0f;
        D_ovl0D_03_8004817C->unk40->unk18 = D_ovl0D_03_80047F94[idx].obj->unk40->unk18 + 200.0f;
    } while (func_ovl0D_03_80047398(D_ovl0D_03_8004817C, 0x40) == 0);
    func_ovl0D_03_800477B0(D_ovl0D_03_80047FD8[idx]);
    func_ovl0D_03_800441C4(idx);
    func_ovl0D_03_80043B98(&D_ovl0D_03_80047F94[idx]);
    t0 = 180;
    t1 = 180;
    t2 = 180;
    t3 = 180;
    func_ovl0D_03_80047AE8(0x63, &D_ovl0D_03_800481A8[idx][1][2].x);
    for (i = 0; i < 180; i++) {
        t3++;
        r = func_ovl0D_03_800476F8(11);
        if (t3 >= 31) {
            func_ovl0D_03_80047990(20, &D_ovl0D_03_800481A8[idx][0][r].x, NULL);
            t3 = 0;
        }
        t2++;
        r = func_ovl0D_03_800476F8(11);
        if (t2 >= 31) {
            func_ovl0D_03_80047990(17, &D_ovl0D_03_800481A8[idx][0][r].x, NULL);
            t2 = 0;
        }
        t1++;
        r = func_ovl0D_03_800476F8(11);
        if (t1 >= 17) {
            func_ovl0D_03_80047990(14, &D_ovl0D_03_800481A8[idx][0][r].x, NULL);
            t1 = 0;
        }
        t0++;
        r = func_ovl0D_03_800476F8(11);
        if (t0 >= 33) {
            func_ovl0D_03_80047538(func_ovl0D_03_80045470, &D_ovl0D_03_800481A8[idx][0][r], 0, 0, 0x150);
            t0 = 0;
        }
        func_ovl0D_03_80047580();
    }
    func_ovl0D_03_80047548();
}

/* a piece of debris (the argument is where it starts) */
void func_ovl0D_03_80045470(void) {
    Vec3f *start;
    Vec3f v;
    Obj_0D03 *o;
    s32 model;
    f32 spin;
    s32 k;
    f32 fall;
    f32 s;

    start = func_ovl0D_03_80047560();
    switch (func_ovl0D_03_800476F8(2)) {
        case 0:
            model = 0xDE;
            break;
        case 1:
            model = 0xE0;
            break;
        case 2:
            model = 0xE6;
            break;
    }
    o = func_ovl0D_03_80047410(model, 0x01000000, 0xD0, 0);
    func_ovl0D_03_800474C0(start, o);
    o->unk40->unk20 = func_ovl0D_03_800476F0() * 360.0;
    fall = func_ovl0D_03_800476F0() * 2 + 3.0;
    if (func_ovl0D_03_800476F8(1) != 0) {
        spin = 10.0f;
    } else {
        spin = -10.0f;
    }
    k = 20;
    o->unk68 = func_ovl0D_03_800476F0() * 10.0 + 20.0;
    while (o->unk68 != 0.0f) {
        o->unk40->unk18 -= fall;
        o->unk40->unk20 += spin;
        func_ovl0D_03_80047468(o);
        if (++k >= 21) {
            k = 0;
            if (func_ovl0D_03_800476F8(1) != 0) {
                v.x = 50.0f;
            } else {
                v.x = -50.0f;
            }
            v.y = func_ovl0D_03_800476F0() * 50.0;
            if (func_ovl0D_03_800476F8(1) != 0) {
                v.z = 50.0f;
            } else {
                v.z = -50.0f;
            }
            func_ovl0D_03_80047990(7, &v.x, o);
        }
        func_ovl0D_03_80047580();
    }
    func_ovl0D_03_800474B8(o, &v.x);
    func_ovl0D_03_80047AE0(0x168, v.x, v.y, v.z);
    func_ovl0D_03_80047990(13, &v.x, NULL);
    for (s = 1.0f; s > 0.1f; s -= 0.025f) {
        o->unk40->unk20 += spin;
        o->unk40->unk30 = s;
        o->unk40->unk28 = o->unk40->unk2C = o->unk40->unk30;
        func_ovl0D_03_80047580();
    }
    if (func_ovl0D_03_800476F8(1) != 0) {
        func_ovl0D_03_80047A08(7, o->unk40->unk10, o->unk40->unk14, o->unk40->unk18);
    } else {
        func_ovl0D_03_80047A08(8, o->unk40->unk10, o->unk40->unk14, o->unk40->unk18);
    }
    func_ovl0D_03_80047400(o);
    func_ovl0D_03_80047548();
}

/* the task func_ovl0D_03_80045224 starts: a hit model shrinks away */
void func_ovl0D_03_80045374(void) {
    Obj_0D03 *self;
    Obj_0D03 *o;
    s32 i;
    s32 n;

    self = func_ovl0D_03_80047560();
    o = func_ovl0D_03_80047410(0x183, 0x11080000, 0xD0, 0);
    o->unk40->unk10 = self->unk40->unk10;
    o->unk40->unk14 = self->unk40->unk14;
    o->unk40->unk18 = self->unk40->unk18;
    n = 20;
    func_ovl0D_03_80045340(0xB3, o);
    for (i = 0; i < n; i++) {
        func_ovl0D_03_80045268(o, i, 20, 2.0f, 4.0f);
        func_ovl0D_03_80047580();
    }
    func_ovl0D_03_80047400(o);
    func_ovl0D_03_80047548();
}

void func_ovl0D_03_80045340(s32 arg0, Obj_0D03 *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0D_03_80047AE0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0D_03_80045268(Obj_0D03 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0D_03_800476E0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0D_03_800476E0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

/* the stage's callback (func_ovl0D_03_80044AA8 registers it) */
void func_ovl0D_03_80045224(Obj_0D03 *arg0) {
    func_ovl0D_03_800473F0(arg0, 0x01000000);
    func_ovl0D_03_80047538(func_ovl0D_03_80045374, arg0, 0, 0, 0x150);
}


/* the cutscene once a gate opens (func_ovl0D_03_80043EC8 starts it) */
void func_ovl0D_03_8004507C(void) {
    while (func_ovl0D_03_800477C0(0x424) == 0) {
        func_ovl0D_03_80047580();
    }
    func_ovl0D_03_80046BD8(1);
    func_ovl0D_03_80046B50(0);
    func_ovl0D_03_80047260(&D_ovl0D_03_80048018, 0x170, 0);
    func_ovl0D_03_800479B8(func_ovl0D_03_80046BC8(), 2);
    func_ovl0D_03_800479C0(func_ovl0D_03_80046BC8(), 6);
    func_ovl0D_03_80046C80(3);
    func_ovl0D_03_80046BF0("WSH WAP WG1 WDS WB0 ST60");
    func_ovl0D_03_80047558(30);
    func_ovl0D_03_80046C10(0x80);
    func_ovl0D_03_80047558(40);
    func_ovl0D_03_80046C10(0x400);
    func_ovl0D_03_80047558(60);
    func_ovl0D_03_80046C10(0x40);
    func_ovl0D_03_80047558(50);
    func_ovl0D_03_80046C10(0x80);
    func_ovl0D_03_80047558(40);
    func_ovl0D_03_80046C10(0x400);
    func_ovl0D_03_80047558(60);
    func_ovl0D_03_80046C10(0x40);
    func_ovl0D_03_80047558(50);
    func_ovl0D_03_80046C80(2);
    func_ovl0D_03_80046C10(0x80);
    func_ovl0D_03_80047558(70);
    func_ovl0D_03_80046C10(0x40);
    func_ovl0D_03_80047558(50);
    func_ovl0D_03_80046BF0("WSH WAP WG1 WDS WB0 ST30");
    func_ovl0D_03_80047558(5);
    func_ovl0D_03_80046C10(0x800);
    func_ovl0D_03_80047580();
    func_ovl0D_03_80046C10(0x800);
    func_ovl0D_03_80047580();
    func_ovl0D_03_80046C10(0x800);
    func_ovl0D_03_80047558(120);
    func_ovl0D_03_80046BF0("WSH WAP WG1 WDS WB3 ST1 WDE WB10 ST1");
    func_ovl0D_03_80047558(30);
    func_ovl0D_03_80047C38();
    func_ovl0D_03_80047548();
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0D_03_80044CBC(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0D_03_80044AA8();
            break;
        case 16:
            func_ovl0D_03_8004419C();
            break;
        case 18:
            func_ovl0D_03_80044174();
            break;
        case 19:
            func_ovl0D_03_80044138();
            break;
        case 20:
            func_ovl0D_03_80044110();
            break;
        case 4:
            func_ovl0D_03_80043FA0();
            break;
        case 5:
            func_ovl0D_03_80043E28();
            break;
        case 0x50:
            func_ovl0D_03_80043A84();
            break;
        case 3:
            func_ovl0D_03_80043770();
            break;
        case 12:
            func_ovl0D_03_80043DE4();
            break;
        case 1:
            func_ovl0D_03_80043C44();
            break;
    }
}

void func_ovl0D_03_80044A88(void) {
    D_ovl0D_03_80048164 = -1;
    D_ovl0D_03_80048168 = -1;
}

void func_ovl0D_03_80044A3C(void) {
    if (*D_ovl0D_03_800481A0 & 2) {
        func_ovl0D_03_800477B0(0x407);
        func_ovl0D_03_800477B0(0x40E);
        func_ovl0D_03_800477B0(0x423);
    }
}

/* the stage's set-up (the handler's case 2) */
void func_ovl0D_03_80044AA8(void) {
    s32 i;
    Trio_0D03 *t;

    func_ovl0D_03_800478A0(D_ovl0D_03_80047CE0);
    func_ovl0D_03_800478B8(D_ovl0D_03_80047D04);
    func_ovl0D_03_800469E8(0x13C);
    if (func_ovl0D_03_80046AE8() == 0x13) {
        func_ovl0D_03_800477B0(0x407);
        func_ovl0D_03_800477B0(0x40E);
        func_ovl0D_03_800477B0(0x423);
    }
    func_ovl0D_03_80046A60(0x142);
    func_ovl0D_03_80046B98();
    func_ovl0D_03_800469F8(D_ovl0D_03_80048188);
    /* the probe: an invisible object moved about to test for hits */
    D_ovl0D_03_8004817C = func_ovl0D_03_80047430(-1, 0x80, 0.0f, 0.0f, 0.0f);
    D_ovl0D_03_8004817C->unkC = 0x3FFFF;
    func_ovl0D_03_80046B30(0);
    func_ovl0D_03_80047880(1);
    func_ovl0D_03_80046AB0(0x201F);
    func_ovl0D_03_80046AD0(func_ovl0D_03_80045224);
    func_ovl0D_03_80044AA0();
    func_ovl0D_03_80044588();
    func_ovl0D_03_8004305C();
    if (func_ovl0D_03_800477C0(0x407) != 0) {
        D_ovl0D_03_80047FDC[1].unk4 = 0x24;
        D_ovl0D_03_80047FDC[1].unk8 = 0xE8;
        D_ovl0D_03_80047FDC[4].unk4 = 0xB;
        D_ovl0D_03_80047FDC[4].unk8 = 0xE9;
    }
    t = D_ovl0D_03_80047FDC;
    for (i = 0; i < 5; i++) {
        func_ovl0D_03_80047A48(t->unk0, t->unk4, t->unk8);
        t++;
    }
    func_ovl0D_03_80046A68();
}

static void func_ovl0D_03_80044AA0(void) {
    func_ovl0D_03_80044A88();
    D_ovl0D_03_800481A0 = func_ovl0D_03_80046B38();
    func_ovl0D_03_80044A3C();
}

/* the models, as the flags already set leave them */
static void func_ovl0D_03_80044588(void) {
    s32 i;

    func_ovl0D_03_80044580();
    func_ovl0D_03_80044578();
    func_ovl0D_03_80044570();
    func_ovl0D_03_80044568();
    D_ovl0D_03_80048180 = 0;
    D_ovl0D_03_80048184 = 0;
    func_ovl0D_03_80044560();
    func_ovl0D_03_80044558();
    for (i = 0; i < 1; i++) {
        func_ovl0D_03_8004431C(&D_ovl0D_03_80047EE4[i]);
        func_ovl0D_03_800473F0(D_ovl0D_03_80047EE4[i].obj, 0x80000);
    }
    for (i = 0; i < 2; i++) {
        if (func_ovl0D_03_800477C0(D_ovl0D_03_80047F8C[i]) == 0) {
            func_ovl0D_03_8004431C(&D_ovl0D_03_80047F1C[i]);
            func_ovl0D_03_800473E8(D_ovl0D_03_80047F1C[i].obj, 0x02000000);
            func_ovl0D_03_800473F0(D_ovl0D_03_80047F1C[i].obj, 0x80000);
            func_ovl0D_03_800473B8(D_ovl0D_03_80047F1C[i].obj, 0xC0);
            D_ovl0D_03_80047F1C[i].obj->unk30 = 4;
            D_ovl0D_03_80047F1C[i].obj->unk34 = 200.0f;
            D_ovl0D_03_80047F1C[i].obj->unk38 = 300.0f;
            func_ovl0D_03_80047538(func_ovl0D_03_80045EF0, (void *) i, 0, 0, 0x110);
        } else {
            func_ovl0D_03_800444B4(&D_ovl0D_03_80047F1C[i]);
        }
    }
    func_ovl0D_03_800444AC();
    func_ovl0D_03_800444A4();
    func_ovl0D_03_800441BC();
}

static void func_ovl0D_03_80044580(void) {
    func_ovl0D_03_800472D8(2400.0f, 1600.0f, 800.0f, 1600.0f);
    func_ovl0D_03_800472E8(1600.0f, 1600.0f, 3200.0f, 1600.0f);
}

static void func_ovl0D_03_80044578(void) {
    UNK_MACRO_ovl0D_03_80043770();
}

static void func_ovl0D_03_80044570(void) {
    Ent_0D03 *p;

    for (p = D_ovl0D_03_80047D1C; p < D_ovl0D_03_80047D1C + 3; p++) {
        func_ovl0D_03_8004431C(p);
        p->obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_03_80044568(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_ovl0D_03_8004431C(&D_ovl0D_03_80047DC4[i]);
        D_ovl0D_03_80047DC4[i].obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_03_80044560(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_ovl0D_03_8004431C(&D_ovl0D_03_80047E6C[i]);
        func_ovl0D_03_800473E8(D_ovl0D_03_80047E6C[i].obj, 0x02000000);
        func_ovl0D_03_800473F0(D_ovl0D_03_80047E6C[i].obj, 0x80000);
    }
}

/* the gates: open already if their flags are set */
static void func_ovl0D_03_80044558(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (func_ovl0D_03_800477C0(D_ovl0D_03_80047EDC[i]) != 0) {
            func_ovl0D_03_80043010(D_ovl0D_03_80047E6C[i].obj);
            func_ovl0D_03_800473F0(D_ovl0D_03_80047E6C[i].obj, 0x02000000);
            func_ovl0D_03_8004337C(&D_ovl0D_03_80047E6C[i]);
        }
    }
}

/* the rows of points the debris of D_ovl0D_03_80047F94 falls from */
static void func_ovl0D_03_8004449C(Vec3f *corner, Vec3f (*rows)[4]) {
    s32 j;
    s32 k;

    for (j = 0; j < 3; j++) {
        for (k = 0; k < 4; k++) {
            rows[j][k].x = corner->x * 10.0f - k * 200.0f;
            rows[j][k].y = corner->y * 10.0f + j * 200.0f;
            rows[j][k].z = corner->z * 10.0f - 100.0f;
        }
    }
}


static void func_ovl0D_03_800444AC(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0D_03_8004449C(&D_ovl0D_03_80047FCC[i], D_ovl0D_03_800481A8[i]);
    }
}

/* the model of D_ovl0D_03_80047F94: done if its flag is set */
static void func_ovl0D_03_800444A4(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0D_03_8004431C(&D_ovl0D_03_80047F94[i]);
        if (func_ovl0D_03_800477C0(D_ovl0D_03_80047FD8[i]) == 0) {
            func_ovl0D_03_80047538(func_ovl0D_03_800457F8, (void *) i, 0, 0, 0x110);
        } else if (func_ovl0D_03_800477C0(D_ovl0D_03_80047FD8[i]) != 0) {
            func_ovl0D_03_80044314(i);
        }
    }
}

static void func_ovl0D_03_80044314(s32 i) {
    func_ovl0D_03_800441C4(i);
    func_ovl0D_03_80043B98(&D_ovl0D_03_80047F94[i]);
}

static void func_ovl0D_03_800444B4(Ent_0D03 *arg0) {
    s32 pos[6];

    func_ovl0D_03_80046A40(arg0->unk14 * 10.0f, arg0->unk18 * 10.0f, arg0->unk1C * 10.0f, pos, 0);
    func_ovl0D_03_80046A28(pos[0], pos[1], pos[2], pos[0] + 3, pos[2] + 3, 0x11);
    func_ovl0D_03_80046A28(pos[0], pos[1] + 1, pos[2], pos[0] + 3, pos[2] + 3, 0x10);
}

static void func_ovl0D_03_8004431C(Ent_0D03 *arg0) {
    arg0->obj = func_ovl0D_03_80047430(arg0->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0D_03_800473E8(arg0->obj, 0x01080000);
    func_ovl0D_03_800473F0(arg0->obj, 0x02000000);
    if (arg0->unkC != -1 && arg0->unkE != -1 && arg0->unk10 != -1 && arg0->unk12 != -1) {
        arg0->unk4 = func_ovl0D_03_80047130(arg0->obj->unk40, 0, arg0->unkC, arg0->unkE, arg0->unk10, arg0->unk12);
        if (arg0->unk4 == -1) {
            while (1) {
            }
        }
    }
    arg0->obj->unk40->unk10 = arg0->unk14 * 10.0f;
    arg0->obj->unk40->unk14 = arg0->unk18 * 10.0f;
    arg0->obj->unk40->unk18 = arg0->unk1C * 10.0f;
    arg0->obj->unk40->unk1C = arg0->unk20;
    arg0->obj->unk40->unk20 = arg0->unk24;
    arg0->obj->unk40->unk24 = arg0->unk28;
    arg0->obj->unk40->unk28 = arg0->unk2C;
    arg0->obj->unk40->unk2C = arg0->unk30;
    arg0->obj->unk40->unk30 = arg0->unk34;
}

/* the tile under one of D_ovl0D_03_80047F94 once it is done */
static void func_ovl0D_03_800441C4(s32 idx) {
    s32 grid[6];
    s32 type;
    UnkStructA_40 *p;
    s32 pos[3];

    p = D_ovl0D_03_80047F94[idx].obj->unk40;
    func_ovl0D_03_80046A40(p->unk10 + -300.0f, p->unk14 + 200.0f, p->unk18 + 200.0f, grid, 0);
    grid[2] -= 1;
    type = func_ovl0D_03_80046A58(grid[0], grid[1], grid[2]);
    func_ovl0D_03_80046A30(grid[0], grid[1], grid[2], grid[0], grid[1], grid[2], 0x1F);
    type = ((type >> 7) & 7) - 2;
    func_ovl0D_03_80046A48(grid[0], grid[1], grid[2], pos, 0);
    func_ovl0D_03_80047A80(type, pos[0], pos[1], pos[2]);
    if (D_ovl0D_03_800481A0[4] != 0) {
        func_ovl0D_03_80047A00(0x46, grid[0], grid[1], grid[2] - 1);
    }
}


static void func_ovl0D_03_800441BC(void) {
}

void func_ovl0D_03_8004419C(void) {
    func_ovl0D_03_80044138();
}

void func_ovl0D_03_80044174(void) {
    func_ovl0D_03_80046BA0(0x10, 4, 0);
}

void func_ovl0D_03_80044138(void) {
    if (!(*D_ovl0D_03_800481A0 & 2)) {
        func_ovl0D_03_80046BA0(0xE, 4, 0x16);
    }
}

void func_ovl0D_03_80044110(void) {
    func_ovl0D_03_80046BA0(0, 5, 2);
}

void func_ovl0D_03_80043FA0(void) {
    func_ovl0D_03_80046BF8();
    func_ovl0D_03_80047288(0x40);
    func_ovl0D_03_80047358(400.0f, 800.0f);
    func_ovl0D_03_800472E8(1600.0f, 1600.0f, 3040.0f, 1200.0f);
    if (!(*D_ovl0D_03_800481A0 & 2)) {
        switch (func_ovl0D_03_80046AE8()) {
            case 18:
                func_ovl0D_03_80046BE0(0x80);
                func_ovl0D_03_80043F58(0.0f);
                break;
            case 20:
                func_ovl0D_03_80046BE0(0x40);
                func_ovl0D_03_80043F58(90.0f);
                break;
            case 19:
                func_ovl0D_03_80047248(135.0f, 32768.0f, 32768.0f);
                break;
            default:
                func_ovl0D_03_80047248(0.0f, 32768.0f, 32768.0f);
                break;
        }
    }
    func_ovl0D_03_80047860(0x37, 0x72, 0);
    func_ovl0D_03_80043EC8();
}

void func_ovl0D_03_80043F58(f32 arg0) {
    f32 sp1C;

    func_ovl0D_03_80047250(&sp1C, NULL, NULL);
    func_ovl0D_03_80047248(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0D_03_80043EC8(void) {
    if (*D_ovl0D_03_800481A0 & 2) {
        func_ovl0D_03_80046BA0(0xF, 2, 0x10);
        func_ovl0D_03_80046BF8();
        func_ovl0D_03_80047248(135.0f, 32768.0f, 32768.0f);
        func_ovl0D_03_80047538(func_ovl0D_03_8004507C, NULL, 0, 0, 0x130);
        func_ovl0D_03_80047290(0xF);
        func_ovl0D_03_800472A0(1);
    }
}

void func_ovl0D_03_80043E28(void) {
    switch (func_ovl0D_03_80046AE8()) {
        case 18:
            func_ovl0D_03_80046BE8(0x80, 3, 8.5f, 3, 0, 1, 1);
            func_ovl0D_03_80046BD8(0);
            break;
        case 20:
            func_ovl0D_03_80046BE8(0x40, 3, 8.5f, 1, 0, 1, 1);
            func_ovl0D_03_80046BD8(0);
            break;
    }
}

void func_ovl0D_03_80043DE4(void) {
    func_ovl0D_03_80043DDC();
    func_ovl0D_03_80043DDC();
    if (D_ovl0D_03_80048164 == 0x38 || D_ovl0D_03_80048164 == 0x39 || D_ovl0D_03_80048164 == 0x3B) {
        func_ovl0D_03_80046BD8(1);
    }
}

static void func_ovl0D_03_80043DDC(void) {
}

/* the stage's clean-up (the handler's case 1) */
void func_ovl0D_03_80043C44(void) {
    func_ovl0D_03_80043C14();
    func_ovl0D_03_80043C1C();
    func_ovl0D_03_80043C24();
    func_ovl0D_03_80043C2C();
    func_ovl0D_03_80043C34();
    func_ovl0D_03_80043C3C();
    func_ovl0D_03_80043B5C();
}

static void func_ovl0D_03_80043C3C(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_ovl0D_03_80047F94[i].obj != NULL) {
            func_ovl0D_03_80043B98(&D_ovl0D_03_80047F94[i]);
        }
    }
}

static void func_ovl0D_03_80043C34(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0D_03_80047F1C[i].obj != NULL) {
            func_ovl0D_03_80043B98(&D_ovl0D_03_80047F1C[i]);
        }
    }
}

static void func_ovl0D_03_80043C2C(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_ovl0D_03_80047EE4[i].obj != NULL) {
            func_ovl0D_03_80043B98(&D_ovl0D_03_80047EE4[i]);
        }
    }
}

static void func_ovl0D_03_80043C24(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0D_03_80047E6C[i].obj != NULL) {
            func_ovl0D_03_80043B98(&D_ovl0D_03_80047E6C[i]);
        }
    }
}

static void func_ovl0D_03_80043C1C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_ovl0D_03_80047DC4[i].obj != NULL) {
            func_ovl0D_03_80043B98(&D_ovl0D_03_80047DC4[i]);
        }
    }
}

static void func_ovl0D_03_80043C14(void) {
    Ent_0D03 *p;

    func_ovl0D_03_80047400(D_ovl0D_03_8004817C);
    for (p = D_ovl0D_03_80047D1C; p < D_ovl0D_03_80047D1C + 3; p++) {
        if (p->obj != NULL) {
            func_ovl0D_03_80043B98(p);
        }
    }
}

static void func_ovl0D_03_80043B98(Ent_0D03 *arg0) {
    func_ovl0D_03_80047400(arg0->obj);
    if (arg0->unkC != 0xFFFF && arg0->unkE != 0xFFFF && arg0->unk10 != 0xFFFF && arg0->unk12 != 0xFFFF) {
        func_ovl0D_03_80047138(arg0->unk4);
    }
    arg0->obj = NULL;
    arg0->unk4 = -1;
}

void func_ovl0D_03_80043B5C(void) {
    if (*D_ovl0D_03_800481A0 & 2) {
        func_ovl0D_03_80047C40();
    }
}


void func_ovl0D_03_80043A84(void) {
    func_ovl0D_03_80043A7C();
    if (func_ovl0D_03_80046BB0(0x2F, 1, 0x2F, 6) != 0) {
        D_ovl0D_03_80048164 = 0x38;
        D_ovl0D_03_80048168 = 0x13;
        func_ovl0D_03_80046AE0(0x38, 0x13, 0);
    }
    if (func_ovl0D_03_80046BB0(0xF, 0, 0x11, 0) != 0) {
        D_ovl0D_03_80048164 = 0x39;
        D_ovl0D_03_80048168 = 0x13;
        func_ovl0D_03_80046AE0(0x39, 0x13, 0);
    }
    if (func_ovl0D_03_80046BB0(0, 1, 0, 2) != 0) {
        D_ovl0D_03_80048164 = 0x3B;
        D_ovl0D_03_80048168 = 0x13;
        func_ovl0D_03_80046AE0(0x3B, 0x13, 0);
    }
}

static void func_ovl0D_03_80043A7C(void) {
}

/* the gates: each opens when something hits it */
void func_ovl0D_03_80043770(void) {
    s32 i;

    /* a fake (as in ovl_0D_05's 80043210): keeps the first call out of the prologue */
    if (!D_ovl0D_03_80048180 && !D_ovl0D_03_80048180 && !D_ovl0D_03_80048180) {
    }
    func_ovl0D_03_80043768();
    func_ovl0D_03_80043760();
    for (i = 0; i < 2; i++) {
        func_ovl0D_03_80043758(&D_ovl0D_03_80047E6C[i], D_ovl0D_03_80047EDC[i]);
    }
}

static void func_ovl0D_03_80043768(void) {
    UNK_MACRO_ovl0D_03_80043770();
}

static void func_ovl0D_03_80043760(void) {
    func_ovl0D_03_800477B0(0x424);
}

static void func_ovl0D_03_80043758(Ent_0D03 *e, s32 flag) {
    Vec3f dir;
    Vec3f pos;
    s32 r;

    if (!(e->obj->unk8 & 0x04000000)) {
        D_ovl0D_03_8004817C->unk30 = 1;
        D_ovl0D_03_8004817C->unk34 = 75.0f;
        D_ovl0D_03_8004817C->unk38 = 50.0f;
        dir.x = e->obj->unk40->unk20 + 90.0f;
        dir.y = 0.0f;
        dir.z = 100.0f;
        func_ovl0D_03_80047380(&dir.x, &pos.x);
        D_ovl0D_03_8004817C->unk40->unk10 = e->obj->unk40->unk10 + pos.x;
        D_ovl0D_03_8004817C->unk40->unk14 = e->obj->unk40->unk14 + pos.y;
        D_ovl0D_03_8004817C->unk40->unk18 = e->obj->unk40->unk18 + pos.z;
        r = func_ovl0D_03_80047398(D_ovl0D_03_8004817C, 0x40);
        if (r != 0) {
            if ((r & 0x6000) && func_ovl0D_03_800477C0(flag) == 0 &&
                !(e->obj->unk8 & 0x04000000)) {
                func_ovl0D_03_800473E8(e->obj, 0x04000000);
                func_ovl0D_03_800473F0(e->obj, 0x02000000);
                func_ovl0D_03_80047AE0(0x60, D_ovl0D_03_8004817C->unk40->unk10, D_ovl0D_03_8004817C->unk40->unk14, D_ovl0D_03_8004817C->unk40->unk18);
            } else if (func_ovl0D_03_800477C0(flag) == 0) {
                func_ovl0D_03_80047AE0(0x26, D_ovl0D_03_8004817C->unk40->unk10, D_ovl0D_03_8004817C->unk40->unk14, D_ovl0D_03_8004817C->unk40->unk18);
            }
        }
    } else if ((e->obj->unk40->unkC & 0x40) && func_ovl0D_03_800477C0(flag) == 0) {
        func_ovl0D_03_8004337C(e);
        func_ovl0D_03_800477B0(flag);
        func_ovl0D_03_80047AC0(0x68);
    }
}

static s32 func_ovl0D_03_80043374(f32 a) {
    if (a == 0.0f) {
        return 0;
    } else if (a == 90.0f) {
        return 1;
    } else if (a == 180.0f) {
        return 2;
    } else if (a == 270.0f || a == -90.0f) {
        return 3;
    }
    return -1;
}

/* the tiles under the gate: solid, and the frame around its opening */
static void func_ovl0D_03_8004337C(Ent_0D03 *e) {
    s32 grid[6];
    s32 x0;
    s32 y0;
    s32 z0;
    s32 x1;
    s32 y1;
    s32 z1;
    s32 x2;
    s32 z2;
    s32 x3;
    s32 z3;
    s32 len;
    s32 dir;
    UnkStructA_40 *p;

    p = e->obj->unk40;
    func_ovl0D_03_80046A40(p->unk10, p->unk14, p->unk18, grid, 0);
    x0 = grid[0];
    y0 = grid[1];
    z0 = grid[2];
    switch (e->obj->unk28) {
        case 0x15C:
            len = 5;
            break;
        case 0x15D:
            len = 7;
            break;
        case 0x15E:
            len = 10;
            break;
        default:
            while (1) {
            }
    }
    y1 = grid[1] + 2;
    dir = func_ovl0D_03_80043374(e->obj->unk40->unk20);
    switch (dir) {
        case 0:
            x0 = grid[0] - 1;
            x1 = x0 + 4;
            z1 = grid[2] + len;
            x2 = x0 + 1;
            x3 = x1 - 1;
            z2 = grid[2];
            z3 = z1;
            break;
        case 1:
            z1 = grid[2] + 1;
            z0 = grid[2] - 4;
            x1 = grid[0] + len;
            x3 = x1;
            z2 = z0 + 1;
            z3 = z1 - 1;
            x2 = grid[0];
            break;
        case 2:
            x1 = grid[0] + 1;
            x0 = grid[0] - 3;
            z0 = grid[2] - len;
            x2 = x0 + 1;
            x3 = x1 - 1;
            z2 = z0;
            z1 = grid[2];
            z3 = grid[2];
            break;
        case 3:
            z1 = grid[2] + 3;
            z0 = grid[2] - 1;
            x0 = grid[0] - len;
            x2 = x0;
            z2 = z0 + 1;
            z3 = z1 - 1;
            x3 = grid[0];
            x1 = grid[0];
            break;
    }
    func_ovl0D_03_80043300(0, D_ovl0D_03_80048188, &x0);
    func_ovl0D_03_80043300(1, D_ovl0D_03_80048188, &y0);
    func_ovl0D_03_80043300(2, D_ovl0D_03_80048188, &z0);
    func_ovl0D_03_80043300(0, D_ovl0D_03_80048188, &x1);
    func_ovl0D_03_80043300(1, D_ovl0D_03_80048188, &y1);
    func_ovl0D_03_80043300(2, D_ovl0D_03_80048188, &z1);
    func_ovl0D_03_80043300(0, D_ovl0D_03_80048188, &x2);
    func_ovl0D_03_80043300(2, D_ovl0D_03_80048188, &z2);
    func_ovl0D_03_80043300(0, D_ovl0D_03_80048188, &x3);
    func_ovl0D_03_80043300(2, D_ovl0D_03_80048188, &z3);
    func_ovl0D_03_80046A30(x0, y0, z0, x1, y1, z1, 0x10);
    func_ovl0D_03_80046A28(x0, y0 + 1, z0, x1, z1, 0x11);
    func_ovl0D_03_80046A28(x0, y0, z0, x1, z1, 0xF);
    func_ovl0D_03_80046A28(x2, y0, z2, x3, z3, 0x11);
    func_ovl0D_03_80046A28(x2, y0 + 1, z2, x3, z3, 0x10);
}

static void func_ovl0D_03_80043300(s32 axis, s32 *size, s32 *v) {
    s32 max;

    switch (axis) {
        case 0:
            max = size[0];
            break;
        case 1:
            max = size[1];
            break;
        case 2:
            max = size[2];
            break;
    }
    if (*v < 0) {
        *v = 0;
    } else if (*v >= max) {
        *v = max - 1;
    }
}


/* the models' state from the flags already set */
void func_ovl0D_03_8004305C(void) {
    if (func_ovl0D_03_800477C0(0x407) != 0) {
        func_ovl0D_03_80043054();
        func_ovl0D_03_80043010(D_ovl0D_03_80047EE4[0].obj);
        func_ovl0D_03_800473F0(D_ovl0D_03_80047D1C[0].obj, 0x01000000);
        D_ovl0D_03_80047D1C[1].unk18 = -105.0f;
        D_ovl0D_03_80047D1C[1].obj->unk40->unk14 = -105.0f * 10.0f;
        D_ovl0D_03_80047D1C[2].unk18 = 175.0f;
        D_ovl0D_03_80047D1C[2].obj->unk40->unk14 = 175.0f * 10.0f;
        func_ovl0D_03_800473F0(D_ovl0D_03_80047DC4[0].obj, 0x01000000);
        func_ovl0D_03_800473F0(D_ovl0D_03_80047DC4[1].obj, 0x01000000);
        func_ovl0D_03_800473F0(D_ovl0D_03_80047DC4[2].obj, 0x01000000);
    }
    if (func_ovl0D_03_800477C0(0x408) != 0) {
        func_ovl0D_03_800473F0(D_ovl0D_03_80047D1C[0].obj, 0x01000000);
        func_ovl0D_03_800473F0(D_ovl0D_03_80047D1C[1].obj, 0x01000000);
        D_ovl0D_03_80047D1C[2].unk18 = 175.0f;
        D_ovl0D_03_80047D1C[2].obj->unk40->unk14 = 175.0f * 10.0f;
        func_ovl0D_03_800473F0(D_ovl0D_03_80047DC4[0].obj, 0x01000000);
        func_ovl0D_03_800473F0(D_ovl0D_03_80047DC4[1].obj, 0x01000000);
        func_ovl0D_03_800473F0(D_ovl0D_03_80047DC4[2].obj, 0x01000000);
    }
}

/* the pictures of the 0x407 state */
static void func_ovl0D_03_80043054(void) {
    D_ovl0D_03_80048194 = func_ovl0D_03_80046AB8(0x156);
    D_ovl0D_03_80048198 = func_ovl0D_03_80046AB8(0x157);
    D_ovl0D_03_8004819C = func_ovl0D_03_80046AB8(0x158);
    func_ovl0D_03_80046AC0(D_ovl0D_03_80048194, 0, 0, D_ovl0D_03_80048188[0] - 1, D_ovl0D_03_80048188[2] - 1, 0, 0, 0);
    func_ovl0D_03_80046AC0(D_ovl0D_03_80048198, 0, 0, D_ovl0D_03_80048188[0] - 1, D_ovl0D_03_80048188[2] - 1, 0, 1, 0);
    func_ovl0D_03_80046AC0(D_ovl0D_03_8004819C, 0, 0, D_ovl0D_03_80048188[0] - 1, D_ovl0D_03_80048188[2] - 1, 0, 2, 0);
}

/* an open gate: its door at the top */
static void func_ovl0D_03_80043010(Obj_0D03 *o) {
    o->unk40->unk48->unk4->unk4 = func_ovl0D_03_80047128(o->unk40, 0) - 0.001f;
}
