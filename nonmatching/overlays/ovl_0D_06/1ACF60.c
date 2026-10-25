/*
 * NON_MATCHING: ovl_0D_06's stage object, complete: all 45 functions, the
 * stubs the inlined statics leave in their places, .data 0x4C0, .rodata
 * 0x70 and .bss 0x60 as the original (sizes; .text 0x2A00 of 0x2A30).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 723, eu 723, jp 723
 *
 * The sibling of ovl_0D_04 (nonmatching/overlays/ovl_0D_04): its gate code
 * (80044414, 80044808, 800440AC) and model tables are the same. What still
 * differs in us (fcmp counts a static with the function before it):
 * - func_ovl0D_06_8004305C (77; 11 words short): the original keeps the
 *   index of D_ovl0D_06_800470BC/80047164 in s0 and multiplies it at run
 *   time (&D[2] as i*56), computes 180.0f*10.0f at run time and spills
 *   200.0f to the stack (frame 0x48, ours 0x30); ovl_0D_04's 80043700 has
 *   the same problem.
 * - func_ovl0D_06_80044808 (172): as ovl_0D_04's 80044318 (frame, s
 *   register numbering).
 * - func_ovl0D_06_8004401C (127; 2 words long, 800440AC with it): the
 *   loop over D_ovl0D_06_8004739C ends at the symbol 8004740C in the
 *   original; ours adds 0x70 to a saved base (an extra s register).
 * - func_ovl0D_06_8004518C (138): the inlined loops' scheduling and s
 *   registers; one word long.
 * - func_ovl0D_06_80043500 (56; 8004355C and 800435FC with it), 80043D60
 *   (20; 1 word short), 80043824 (16), 80044D50 (47; 1 word long),
 *   8004435C (67; 80044398 and 80044414 with it): register allocation and
 *   scheduling, s register parameters of the statics.
 *   Tried without gain: n's temporary in 80043824 (split statement, float
 *   temporary, decrement) and the order of its locals (16 as drafted, 20-22
 *   with the other orders); 80043D60's switch as
 *   an if chain, with case 0 dropped or as default, and with the case
 *   blocks reordered (all 140+ words). The 80043500 diff is the temporaries'
 *   numbers in 800435FC's twelve 7-argument calls (original t0-t5, ours
 *   reuses t6-t9). 80044D50's extra s3 comes from the loops over
 *   D_800470BC and D_8004739C; the pointer-to-index rewrites of those
 *   loops were not scored (their anchor text occurs twice).
 * - func_ovl0D_06_800458F8 (3): the padding after the last function.
 */
#include "common.h"

/*
 * ovl_0D_06's stage object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).
 * ovl_0D_04's object (nonmatching/overlays/ovl_0D_04) is its sibling.
 */

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} Anim2_0D06;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ Anim2_0D06 *unk4;
} Anim_0D06;

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
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 unk38[0x10];
    /* 0x48 */ Anim_0D06 *unk48;
} Obj40_0D06;

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
    /* 0x40 */ Obj40_0D06 *unk40;
} Obj_0D06;

/* a model placed on the stage (as in ovl_0D_04) */
typedef struct {
    /* 0x00 */ Obj_0D06 *obj;
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
} Ent_0D06;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Trio_0D06;

typedef struct {
    f32 x, y, z, w;
} Vec4f_0D06;

/* passed to func_ovl0D_06_80046600 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18[11];
} Move_0D06;

void func_ovl0D_06_80045D88(s32); /* 0xC00 */
void func_ovl0D_06_80045D98(s32 *); /* 0xC02 */
void func_ovl0D_06_80045DC8(s32, s32, s32, s32, s32, s32); /* 0xD05 */
void func_ovl0D_06_80045DD0(s32, s32, s32, s32, s32, s32, s32); /* 0xD06 */
void func_ovl0D_06_80045DE0(f32, f32, f32, s32 *, s32); /* 0xD08 */
s32 func_ovl0D_06_80045DF0(s32); /* 0xD0A */
void func_ovl0D_06_80045E00(s32); /* 0xD0C */
void func_ovl0D_06_80045E08(void); /* 0xD0D */
f32 func_ovl0D_06_80045E48(Obj40_0D06 *); /* 0xD15 */
void func_ovl0D_06_80045E50(s32); /* 0xD16 */
s32 func_ovl0D_06_80045E58(s32); /* 0xE00 */
void func_ovl0D_06_80045E60(s32, s32, s32, s32, s32, s32, s32, s32); /* 0xE01 */
void func_ovl0D_06_80045E70(void (*)(Obj_0D06 *)); /* 0xE03 */
void func_ovl0D_06_80045E80(s32, s32, s32); /* 0xF00 */
s32 func_ovl0D_06_80045E88(void); /* 0xF01 */
void func_ovl0D_06_80045EA8(void); /* 0xF05 */
void func_ovl0D_06_80045ED0(s32); /* 0xF0A */
s32 *func_ovl0D_06_80045ED8(void); /* 0xF0B */
void func_ovl0D_06_80045EF0(s32); /* 0xF0E */
void func_ovl0D_06_80045EF8(s32); /* 0xF0F */
void func_ovl0D_06_80045F38(void); /* 0x1000 */
void func_ovl0D_06_80045F40(s32, s32, s32); /* 0x1001 */
void func_ovl0D_06_80045F48(void *); /* 0x1002 */
s32 func_ovl0D_06_80045F50(s32, s32, s32, s32); /* 0x1003 */
s32 func_ovl0D_06_80045F58(s32, s32, s32, s32, s32); /* 0x1004 */
s32 func_ovl0D_06_80045F68(void); /* 0x1006 */
void func_ovl0D_06_80045F70(s32, void *); /* 0x1007 */
void func_ovl0D_06_80045F78(s32); /* 0x1008 */
void func_ovl0D_06_80045F80(s32); /* 0x1009 */
void func_ovl0D_06_80045F88(s32, s32, f32, s32, s32, s32, s32); /* 0x100A */
void func_ovl0D_06_80045F98(void); /* 0x100C */
void func_ovl0D_06_80045FA0(s32); /* 0x100D */
void func_ovl0D_06_80045FB0(s32); /* 0x100F */
Obj_0D06 *func_ovl0D_06_80045FC8(s32); /* 0x1012 */
void func_ovl0D_06_80046038(void); /* 0x1020 */
void func_ovl0D_06_800464B0(Obj40_0D06 *, s32, s32); /* 0x1509 */
f32 func_ovl0D_06_800464C8(Obj40_0D06 *, s32); /* 0x150C */
s32 func_ovl0D_06_800464D0(Obj40_0D06 *, s32, s32, s32, s32, s32); /* 0x150D */
void func_ovl0D_06_800464D8(s32); /* 0x150E */
void func_ovl0D_06_800464F0(s32, s32); /* 0x1511 */
void func_ovl0D_06_800465C8(f32, f32, f32); /* 0x1704 */
void func_ovl0D_06_800465E8(f32, f32, f32); /* 0x1708 */
void func_ovl0D_06_800465F0(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0D_06_80046600(Move_0D06 *, s32, s32); /* 0x170B */
s32 func_ovl0D_06_80046618(void); /* 0x170E */
void func_ovl0D_06_80046620(void); /* 0x170F */
void func_ovl0D_06_80046628(s32); /* 0x1710 */
void func_ovl0D_06_80046630(s32); /* 0x1711 */
void func_ovl0D_06_80046640(s32); /* 0x1713 */
void func_ovl0D_06_80046678(f32, f32, f32, f32); /* 0x171A */
void func_ovl0D_06_80046688(f32, f32, f32, f32); /* 0x171C */
void func_ovl0D_06_800466A0(s32); /* 0x171F */
void func_ovl0D_06_800466B0(f32, f32, f32); /* 0x1721 */
void func_ovl0D_06_800466B8(void *); /* 0x1722 */
void func_ovl0D_06_800466E8(void); /* 0x1728 */
void func_ovl0D_06_800466F0(void); /* 0x1729 */
void func_ovl0D_06_800466F8(f32, f32); /* 0x172A */
void func_ovl0D_06_80046720(f32 *, f32 *); /* 0x1804 */
s32 func_ovl0D_06_80046738(Obj_0D06 *, s32); /* 0x1807 */
void func_ovl0D_06_80046788(Obj_0D06 *, s32); /* 0x1811 */
void func_ovl0D_06_80046790(Obj_0D06 *, s32); /* 0x1812 */
void func_ovl0D_06_800467A0(Obj_0D06 *); /* 0x1814 */
Obj_0D06 *func_ovl0D_06_800467B0(s32, s32, s32, s32); /* 0x1816 */
void func_ovl0D_06_800467C0(Obj_0D06 *); /* 0x1818 */
Obj_0D06 *func_ovl0D_06_800467D0(s32, s32, f32, f32, f32); /* 0x181A */
void func_ovl0D_06_800468D8(void (*)(void), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0D_06_800468E8(void); /* 0x1902 */
void func_ovl0D_06_800468F8(s32); /* 0x1904 */
void *func_ovl0D_06_80046900(void); /* 0x1905 */
void func_ovl0D_06_80046920(void); /* 0x1909 */
f32 func_ovl0D_06_80046A80(f32); /* 0x1D00 */
s32 func_ovl0D_06_80046B40(s32); /* 0x1E04 */
void func_ovl0D_06_80046B50(s32); /* 0x1E06 */
void func_ovl0D_06_80046B58(s32); /* 0x1E07 */
s32 func_ovl0D_06_80046B60(s32); /* 0x1E08 */
s32 *func_ovl0D_06_80046B70(s32); /* 0x1E0A */
void func_ovl0D_06_80046BC8(s32); /* 0x2002 */
void func_ovl0D_06_80046BD0(void); /* 0x2003 */
void func_ovl0D_06_80046C00(s32, s32, s32); /* 0x2101 */
void func_ovl0D_06_80046C20(s32); /* 0x2200 */
void func_ovl0D_06_80046C40(u32 (*)[3]); /* 0x2300 */
void func_ovl0D_06_80046C58(u32 (*)[3]); /* 0x2303 */
s32 func_ovl0D_06_80046D30(s32, f32 *, s32); /* 0x2601 */
void func_ovl0D_06_80046D38(s32); /* 0x2602 */
void func_ovl0D_06_80046D68(void); /* 0x2704 */
void func_ovl0D_06_80046DE8(s32, s32, s32); /* 0x2A00 */
void func_ovl0D_06_80046E48(void); /* 0x2A0C */
void func_ovl0D_06_80046E60(s32); /* 0x2B00 */
void func_ovl0D_06_80046E80(s32, f32, f32, f32); /* 0x2B04 */

s32 func_ovl0D_06_80043214(void);
void func_ovl0D_06_80043500(f32, f32, f32);
void func_ovl0D_06_8004340C(void);
void func_ovl0D_06_80043824(void);
void func_ovl0D_06_80043C98(void);
void func_ovl0D_06_80043D60(void);
void func_ovl0D_06_8004401C(void);
void func_ovl0D_06_8004422C(void);
void func_ovl0D_06_8004435C(void);
void func_ovl0D_06_80044808(void);
void func_ovl0D_06_80044B14(void);
void func_ovl0D_06_80044BF0(void);
void func_ovl0D_06_80044D50(void);
void func_ovl0D_06_80044E70(void);
void func_ovl0D_06_80044EAC(void);
void func_ovl0D_06_80044F4C(f32);
void func_ovl0D_06_80044F94(void);
void func_ovl0D_06_8004507C(void);
void func_ovl0D_06_800450A4(void);
void func_ovl0D_06_800450EC(void);
void func_ovl0D_06_80045114(void);
void func_ovl0D_06_80045164(void);
void func_ovl0D_06_8004518C(void);
void func_ovl0D_06_80045510(s32);
void func_ovl0D_06_8004566C(Obj_0D06 *);
void func_ovl0D_06_800456B0(Obj_0D06 *, s32, s32, f32, f32);
void func_ovl0D_06_800431E0(s32, Obj_0D06 *);
void func_ovl0D_06_80045788(void);
void func_ovl0D_06_80045884(s32, s32);
void func_ovl0D_06_800458F8(f32, f32, f32, f32, s32);

static void func_ovl0D_06_80043010(void);
static void func_ovl0D_06_80043018(Obj_0D06 *);
void func_ovl0D_06_8004305C(void);
static void func_ovl0D_06_800431D8(void);
void func_ovl0D_06_80043318(s32, s32);
static void func_ovl0D_06_800433B4(Obj_0D06 *);
static void func_ovl0D_06_8004355C(s32, s32, s32, s32);
static void func_ovl0D_06_800435FC(void);
static void func_ovl0D_06_80043FA0(Ent_0D06 *);
static void func_ovl0D_06_800440AC(Ent_0D06 *);
static void func_ovl0D_06_80044398(s32, s32 *, s32 *);
static s32 func_ovl0D_06_8004440C(f32);
static void func_ovl0D_06_80044414(Ent_0D06 *);
static void func_ovl0D_06_80044E68(void);
static void func_ovl0D_06_8004517C(Trio_0D06 *, s32);
static void func_ovl0D_06_80045184(void);
static void func_ovl0D_06_80044BE0(void);
static void func_ovl0D_06_80044BE8(void);
static void func_ovl0D_06_80044D30(void);
static void func_ovl0D_06_80044D38(void);
static void func_ovl0D_06_80044D40(void);
static void func_ovl0D_06_80044D48(void);
static void func_ovl0D_06_800447F0(void);
static void func_ovl0D_06_800447F8(void);
static void func_ovl0D_06_80044800(void);
static void func_ovl0D_06_80045154(void);
static void func_ovl0D_06_8004514C(void);
static void func_ovl0D_06_80045144(void);
static void func_ovl0D_06_80045134(void);
static void func_ovl0D_06_8004515C(void);
static void func_ovl0D_06_8004513C(void);

#define UNK_MACRO_ovl0D_06_80044808() \
    D_ovl0D_06_800475CC = func_ovl0D_06_80045F68(); func_ovl0D_06_80045F48(&D_ovl0D_06_800475C0); func_ovl0D_06_80045F70(D_ovl0D_06_800475CC, &D_ovl0D_06_800475B0)

/* .bss */
Vec4f_0D06 D_ovl0D_06_800475B0;
Vec3f D_ovl0D_06_800475C0;
s32 D_ovl0D_06_800475CC;
s32 D_ovl0D_06_800475D0;
s32 D_ovl0D_06_800475D4;
s32 D_ovl0D_06_800475D8;
u8 D_ovl0D_06_800475DC[0x4]; /* unused */
Vec3f D_ovl0D_06_800475E0;
Obj_0D06 *D_ovl0D_06_800475EC;
s32 D_ovl0D_06_800475F0;
s32 D_ovl0D_06_800475F4;
s32 D_ovl0D_06_800475F8[3];
s32 D_ovl0D_06_80047604;
s32 *D_ovl0D_06_80047608;

/* .data */
u32 D_ovl0D_06_80047080[][3] = {
    { 0x9A0002, 0x6000E, 4 },
    { 0x970001, 0xF, 0x2004 },
    { 0x9B0002, 0xE, 4 },
};
u32 D_ovl0D_06_800470A4[][3] = {
    { 0, 4, 0x980000 },
    { 0x84, 0, 4 },
};
Ent_0D06 D_ovl0D_06_800470BC[3] = {
    { NULL, -1, 0x153, 0, 0x400, 0x20, 0x400, 160.0f, 20.0f, 40.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x151, 0, 0x400, 0x20, 0x400, 160.0f, 160.0f, -10.0f, 0.0f, 90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14C, 0, 0x400, 0x20, 0x400, 140.0f, 20.0f, 170.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D06 D_ovl0D_06_80047164[4] = {
    { NULL, -1, 0x14B, 0, 0x400, 0x20, 0x400, 460.0f, 20.0f, 120.0f, 0.0f, 90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14B, -1, -1, -1, -1, 260.0f, 160.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14B, -1, -1, -1, -1, 160.0f, 20.0f, 270.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14B, -1, -1, -1, -1, 470.0f, -20.0f, 270.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D06 D_ovl0D_06_80047244[2] = {
    { NULL, -1, 0x15C, -1, -1, -1, -1, 440.0f, 40.0f, 120.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x15C, -1, -1, -1, -1, 210.0f, 40.0f, 230.0f, 0.0f, -90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
s32 D_ovl0D_06_800472B4[2] = { 0x404, 0x405 };
Ent_0D06 D_ovl0D_06_800472BC[1] = {
    { NULL, -1, 0x14A, -1, -1, -1, -1, 260.0f, 110.0f, -10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D06 D_ovl0D_06_800472F4[1] = {
    { NULL, -1, 0x163, -1, -1, -1, -1, 170.0f, -20.0f, 170.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D06 D_ovl0D_06_8004732C[1] = {
    { NULL, -1, 0x162, -1, -1, -1, -1, 220.0f, 0.0f, 40.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D06 D_ovl0D_06_80047364[1] = {
    { NULL, -1, 0x166, -1, -1, -1, -1, 200.0f, -39.0f, 160.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D06 D_ovl0D_06_8004739C[2] = {
    { NULL, -1, 0x164, 0, 0x400, 0x20, 0x400, 180.0f, 215.0f, 15.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x164, -1, -1, -1, -1, 180.0f, 95.0f, 130.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D06 D_ovl0D_06_8004740C[1] = {
    { NULL, -1, 0x165, 0, 0x400, -0x20, -0x400, 180.0f, 215.0f, 30.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D06 D_ovl0D_06_80047444[1] = {
    { NULL, -1, 0x168, -1, -1, -1, -1, 230.0f, 40.0f, 180.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Move_0D06 D_ovl0D_06_8004747C = { 0, 1, 1 };
Trio_0D06 D_ovl0D_06_800474C0[6] = {
    { 0, 7, 0xE5 },
    { 1, 9, 0xE7 },
    { 2, 9, 0xE7 },
    { 3, 9, 0xE7 },
    { 4, 8, 0xE6 },
    { 5, 1, 0xDE },
};
Ent_0D06 D_ovl0D_06_80047508[1] = {
    { NULL, -1, 0x323, -1, -1, -1, -1, 150.0f, 40.0f, 270.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};

/* a gate opening: the camera goes to it */
void func_ovl0D_06_800458F8(f32 x, f32 y, f32 z, f32 ang, s32 arg4) {
    func_ovl0D_06_80045EF0(0);
    func_ovl0D_06_80045F78(1);
    func_ovl0D_06_80046630(0xF);
    if (func_ovl0D_06_80046618() == 1) {
        func_ovl0D_06_80046620();
    }
    func_ovl0D_06_80046038();
    func_ovl0D_06_80046D68();
    func_ovl0D_06_80046E48();
    func_ovl0D_06_800468F8(60);
    func_ovl0D_06_80045FA0(1);
    func_ovl0D_06_80046E60(0x29);
    func_ovl0D_06_80045EF8(1);
    func_ovl0D_06_80045FB0(0x40);
    func_ovl0D_06_80045F88(arg4, 6, 8.5f, 0, 1, 1, 0);
    func_ovl0D_06_80045F78(1);
    func_ovl0D_06_800468F8(30);
    func_ovl0D_06_800466E8();
    func_ovl0D_06_80046630(0x7F);
    func_ovl0D_06_800465C8(x, y, z);
    func_ovl0D_06_800465E8(ang, 45.0f, 32768.0f);
    func_ovl0D_06_80046640(0);
    func_ovl0D_06_800468F8(15);
    func_ovl0D_06_80046E60(0x69);
    func_ovl0D_06_800468F8(15);
    func_ovl0D_06_80046E60(0x6F);
}

void func_ovl0D_06_80045884(s32 arg0, s32 arg1) {
    func_ovl0D_06_80045F88(0x200, 5, 1.1111f, 1, 0, 0, 0);
    func_ovl0D_06_80045F78(1);
    func_ovl0D_06_800468F8(30);
    func_ovl0D_06_80046BC8(2);
    func_ovl0D_06_80046BD0();
    func_ovl0D_06_80045E80(arg0, arg1, 1);
}

void func_ovl0D_06_80045788(void) {
    Obj_0D06 *self;
    Obj_0D06 *o;
    s32 i;
    s32 n;

    self = func_ovl0D_06_80046900();
    o = func_ovl0D_06_800467B0(0x183, 0x11080000, 0xD0, 0);
    o->unk40->unk10 = self->unk40->unk10;
    o->unk40->unk14 = self->unk40->unk14;
    o->unk40->unk18 = self->unk40->unk18;
    n = 20;
    func_ovl0D_06_800431E0(0xB3, o);
    for (i = 0; i < n; i++) {
        func_ovl0D_06_800456B0(o, i, 20, 2.0f, 4.0f);
        func_ovl0D_06_80046920();
    }
    func_ovl0D_06_800467A0(o);
    func_ovl0D_06_800468E8();
}

void func_ovl0D_06_800456B0(Obj_0D06 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0D_06_80046A80((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0D_06_80046A80((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

/* the callback func_ovl0D_06_8004518C registers */
void func_ovl0D_06_8004566C(Obj_0D06 *arg0) {
    func_ovl0D_06_80046790(arg0, 0x01000000);
    func_ovl0D_06_800468D8(func_ovl0D_06_80045788, arg0, 0, 0, 0x150);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0D_06_80045510(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0D_06_8004518C();
            break;
        case 16:
            func_ovl0D_06_800450A4();
            break;
        case 17:
            func_ovl0D_06_800450EC();
            break;
        case 18:
            func_ovl0D_06_80045114();
            break;
        case 24:
            func_ovl0D_06_8004507C();
            break;
        case 4:
            func_ovl0D_06_80044F94();
            break;
        case 5:
            func_ovl0D_06_80044EAC();
            break;
        case 0x50:
            func_ovl0D_06_80044BF0();
            break;
        case 0x53:
            break;
        case 15:
            func_ovl0D_06_80044B14();
            break;
        case 3:
            func_ovl0D_06_80044808();
            break;
        case 12:
            func_ovl0D_06_80044E70();
            break;
        case 1:
            func_ovl0D_06_80044D50();
            break;
    }
}

void func_ovl0D_06_80045164(void) {
    D_ovl0D_06_800475D4 = -1;
    D_ovl0D_06_800475D8 = -1;
}

void func_ovl0D_06_8004518C(void) {
    func_ovl0D_06_80045184();
    func_ovl0D_06_80046C40(D_ovl0D_06_80047080);
    func_ovl0D_06_80046C58(D_ovl0D_06_800470A4);
    func_ovl0D_06_80045D88(0x13F);
    if (func_ovl0D_06_80046B60(0x409) != 0) {
        D_ovl0D_06_800474C0[1].unk4 = 0x24;
        D_ovl0D_06_800474C0[1].unk8 = 0xE8;
        D_ovl0D_06_800474C0[2].unk4 = 0xB;
        D_ovl0D_06_800474C0[2].unk8 = 0xE9;
    }
    func_ovl0D_06_8004517C(D_ovl0D_06_800474C0, 6);
    func_ovl0D_06_80045E00(0x145);
    func_ovl0D_06_80045F38();
    func_ovl0D_06_80045D98(D_ovl0D_06_800475F8);
    D_ovl0D_06_800475EC = func_ovl0D_06_800467D0(-1, 0x80, 0.0f, 0.0f, 0.0f);
    D_ovl0D_06_800475EC->unkC = 0x3FFFF;
    func_ovl0D_06_80045ED0(0);
    func_ovl0D_06_80046C20(1);
    func_ovl0D_06_80045E50(0x201F);
    func_ovl0D_06_80045E70(func_ovl0D_06_8004566C);
    func_ovl0D_06_80045164();
    D_ovl0D_06_80047608 = func_ovl0D_06_80045ED8();
    func_ovl0D_06_80046C20(1);
    func_ovl0D_06_8004515C();
    func_ovl0D_06_80044800();
    func_ovl0D_06_80045154();
    func_ovl0D_06_8004514C();
    D_ovl0D_06_800475F0 = 0;
    D_ovl0D_06_800475F4 = 0;
    func_ovl0D_06_80045144();
    func_ovl0D_06_8004513C();
    func_ovl0D_06_80045134();
    func_ovl0D_06_8004305C();
    func_ovl0D_06_8004422C();
    func_ovl0D_06_80043D60();
    func_ovl0D_06_80045E08();
    func_ovl0D_06_800440AC(D_ovl0D_06_80047508);
    func_ovl0D_06_80046790(D_ovl0D_06_80047508[0].obj, 0x80000);
    func_ovl0D_06_80046788(D_ovl0D_06_80047508[0].obj, 0x02000000);
    func_ovl0D_06_800467C0(D_ovl0D_06_80047508[0].obj);
}

static void func_ovl0D_06_80045184(void) {
}

static void func_ovl0D_06_8004517C(Trio_0D06 *t, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0D_06_80046DE8(t->unk0, t->unk4, t->unk8);
        t++;
    }
}

static void func_ovl0D_06_80045154(void) {
    Ent_0D06 *p;

    for (p = D_ovl0D_06_800470BC; p < D_ovl0D_06_800470BC + 3; p++) {
        func_ovl0D_06_800440AC(p);
        p->obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_06_8004514C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_ovl0D_06_800440AC(&D_ovl0D_06_80047164[i]);
        D_ovl0D_06_80047164[i].obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_06_80045144(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_ovl0D_06_800440AC(&D_ovl0D_06_80047244[i]);
        func_ovl0D_06_80046788(D_ovl0D_06_80047244[i].obj, 0x02000000);
        func_ovl0D_06_80046790(D_ovl0D_06_80047244[i].obj, 0x80000);
    }
}

static void func_ovl0D_06_80045134(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0D_06_800440AC(&D_ovl0D_06_800472BC[i]);
        func_ovl0D_06_80046790(D_ovl0D_06_800472BC[i].obj, 0x80000);
    }
}

static void func_ovl0D_06_8004515C(void) {
    func_ovl0D_06_80046678(2400.0f, 1600, 800.0f, 1600.0f);
    func_ovl0D_06_80046688(1600.0f, 1600.0f, 3200.0f, 1600.0f);
}

static void func_ovl0D_06_8004513C(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (func_ovl0D_06_80046B60(D_ovl0D_06_800472B4[i]) != 0) {
            func_ovl0D_06_80043018(D_ovl0D_06_80047244[i].obj);
            func_ovl0D_06_80046790(D_ovl0D_06_80047244[i].obj, 0x02000000);
            func_ovl0D_06_80044414(&D_ovl0D_06_80047244[i]);
        }
    }
}

void func_ovl0D_06_80045114(void) {
    func_ovl0D_06_800450A4();
}

void func_ovl0D_06_800450EC(void) {
    func_ovl0D_06_80045F40(0x2E, 0, 0x15);
}

void func_ovl0D_06_800450A4(void) {
    func_ovl0D_06_80045F40(0x22, 5, 1);
    func_ovl0D_06_80045F40(0x17, 4, 0x12);
    func_ovl0D_06_80045F40(0x1B, 0, 7);
}

void func_ovl0D_06_8004507C(void) {
    func_ovl0D_06_80045F40(0x22, 5, 0);
}

void func_ovl0D_06_80044F94(void) {
    func_ovl0D_06_80045F98();
    func_ovl0D_06_80046628(0x40);
    func_ovl0D_06_800466F8(400.0f, 800.0f);
    func_ovl0D_06_80046C00(0x2D, 0x6E, 0x2C);
    switch (func_ovl0D_06_80045E88()) {
        case 17:
            func_ovl0D_06_80045F80(0xC0);
            func_ovl0D_06_80044F4C(0.0f);
            break;
        case 24:
            func_ovl0D_06_80045F80(0x80);
            func_ovl0D_06_80044F4C(90.0f);
            break;
    }
}

void func_ovl0D_06_80044F4C(f32 arg0) {
    f32 sp1C;

    func_ovl0D_06_800465F0(&sp1C, NULL, NULL);
    func_ovl0D_06_800465E8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0D_06_80044EAC(void) {
    switch (func_ovl0D_06_80045E88()) {
        case 17:
            func_ovl0D_06_80045F88(0xC0, 3, 8.5f, 5, 0, 1, 1);
            func_ovl0D_06_80045F78(0);
            break;
        case 24:
            func_ovl0D_06_80045F88(0x80, 3, 8.5f, 1, 0, 1, 1);
            func_ovl0D_06_80045F78(0);
            break;
    }
}

void func_ovl0D_06_80044E70(void) {
    func_ovl0D_06_80044E68();
    if (D_ovl0D_06_800475D4 == 0x3B || D_ovl0D_06_800475D4 == 0x3C) {
        func_ovl0D_06_80045F78(1);
    }
}

static void func_ovl0D_06_80044E68(void) {
}

void func_ovl0D_06_80044D50(void) {
    func_ovl0D_06_80044D48();
    func_ovl0D_06_80044D40();
    func_ovl0D_06_80044D38();
    func_ovl0D_06_80044D30();
    func_ovl0D_06_8004401C();
}

static void func_ovl0D_06_80044D48(void) {
    Ent_0D06 *p;

    func_ovl0D_06_800467A0(D_ovl0D_06_800475EC);
    for (p = D_ovl0D_06_800470BC; p < D_ovl0D_06_800470BC + 3; p++) {
        if (p->obj != NULL) {
            func_ovl0D_06_80043FA0(p);
        }
    }
}

static void func_ovl0D_06_80044D40(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_ovl0D_06_80047164[i].obj != NULL) {
            func_ovl0D_06_80043FA0(&D_ovl0D_06_80047164[i]);
        }
    }
}

static void func_ovl0D_06_80044D38(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0D_06_80047244[i].obj != NULL) {
            func_ovl0D_06_80043FA0(&D_ovl0D_06_80047244[i]);
        }
    }
}

static void func_ovl0D_06_80044D30(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_ovl0D_06_800472BC[i].obj != NULL) {
            func_ovl0D_06_80043FA0(&D_ovl0D_06_800472BC[i]);
        }
    }
}

static void func_ovl0D_06_80044BE8(void) {
    if (func_ovl0D_06_80045F50(0x2F, 7, 0x2F, 0xC) != 0) {
        func_ovl0D_06_80046B50(0x420);
        func_ovl0D_06_80046B58(0x426);
        D_ovl0D_06_800475D4 = 0x3C;
        D_ovl0D_06_800475D8 = 0x12;
        func_ovl0D_06_80045E80(0x3C, 0x12, 0);
    }
}

static void func_ovl0D_06_80044BE0(void) {
    if (func_ovl0D_06_80045F50(0x2E, 0x14, 0x2E, 0x15) != 0) {
        func_ovl0D_06_80046B58(0x420);
        D_ovl0D_06_800475D4 = 0x3C;
        D_ovl0D_06_800475D8 = 0x12;
        func_ovl0D_06_80045E80(0x3C, 0x12, 0);
    }
}

void func_ovl0D_06_80044BF0(void) {
    func_ovl0D_06_80044BE8();
    func_ovl0D_06_80044BE0();
    if (func_ovl0D_06_80045F50(0x22, 0, 0x23, 0) != 0) {
        D_ovl0D_06_800475D4 = 0x3B;
        D_ovl0D_06_800475D8 = 0x18;
        func_ovl0D_06_80045E80(0x3B, 0x18, 0);
    }
    if (func_ovl0D_06_80045F50(0x13, 0x10, 0x13, 0x10) != 0) {
        if (func_ovl0D_06_80046B60(0x415) != 0) {
            func_ovl0D_06_80046D38(D_ovl0D_06_800475D0);
        }
        func_ovl0D_06_8004435C();
        func_ovl0D_06_80045EA8();
    }
}

void func_ovl0D_06_80044B14(void) {
    s32 n;

    if (func_ovl0D_06_80045F58(0xF, 2, 0x1A, 0xF, 0x1A) != 0) {
        if (func_ovl0D_06_80046B40(0xA4) != 0) {
            func_ovl0D_06_800464F0(0x291, 1);
        } else {
            n = 0;
            if (func_ovl0D_06_80046B60(0x413) != 0) {
                n = 1;
            }
            if (func_ovl0D_06_80046B60(0x414) != 0) {
                n++;
            }
            if (func_ovl0D_06_80046B60(0x415) != 0) {
                n++;
            }
            if (n < 3) {
                func_ovl0D_06_800464F0(0x28E, 2);
            } else {
                func_ovl0D_06_800464F0(0x28F, 2);
            }
        }
    }
}

/* the gates: each opens when something hits it */
void func_ovl0D_06_80044808(void) {
    func_ovl0D_06_80044800();
    func_ovl0D_06_800447F8();
    func_ovl0D_06_800447F0();
}

static void func_ovl0D_06_80044800(void) {
    UNK_MACRO_ovl0D_06_80044808();
}

static void func_ovl0D_06_800447F8(void) {
    func_ovl0D_06_80046B50(0x424);
}

static void func_ovl0D_06_800447F0(void) {
    s32 i;
    s32 flag;
    s32 r;
    Vec3f dir;
    Vec3f pos;

    for (i = 0; i < 2; i++) {
        flag = D_ovl0D_06_800472B4[i];
        if (!(D_ovl0D_06_80047244[i].obj->unk8 & 0x04000000)) {
            D_ovl0D_06_800475EC->unk30 = 1;
            D_ovl0D_06_800475EC->unk34 = 75.0f;
            D_ovl0D_06_800475EC->unk38 = 50.0f;
            dir.y = 0.0f;
            dir.z = 100.0f;
            dir.x = D_ovl0D_06_80047244[i].obj->unk40->unk20 + 90.0f;
            func_ovl0D_06_80046720(&dir.x, &pos.x);
            D_ovl0D_06_800475EC->unk40->unk10 = D_ovl0D_06_80047244[i].obj->unk40->unk10 + pos.x;
            D_ovl0D_06_800475EC->unk40->unk14 = D_ovl0D_06_80047244[i].obj->unk40->unk14 + pos.y;
            D_ovl0D_06_800475EC->unk40->unk18 = D_ovl0D_06_80047244[i].obj->unk40->unk18 + pos.z;
            r = func_ovl0D_06_80046738(D_ovl0D_06_800475EC, 0x40);
            if (r != 0) {
                if ((r & 0x6000) && func_ovl0D_06_80046B60(flag) == 0 &&
                    !(D_ovl0D_06_80047244[i].obj->unk8 & 0x04000000)) {
                    func_ovl0D_06_80046788(D_ovl0D_06_80047244[i].obj, 0x04000000);
                    func_ovl0D_06_80046790(D_ovl0D_06_80047244[i].obj, 0x02000000);
                    func_ovl0D_06_80046E80(0x60, D_ovl0D_06_800475EC->unk40->unk10, D_ovl0D_06_800475EC->unk40->unk14, D_ovl0D_06_800475EC->unk40->unk18);
                } else if (func_ovl0D_06_80046B60(flag) == 0) {
                    func_ovl0D_06_80046E80(0x26, D_ovl0D_06_800475EC->unk40->unk10, D_ovl0D_06_800475EC->unk40->unk14, D_ovl0D_06_800475EC->unk40->unk18);
                }
            }
        } else if ((D_ovl0D_06_80047244[i].obj->unk40->unkC & 0x40) && func_ovl0D_06_80046B60(flag) == 0) {
            func_ovl0D_06_80044414(&D_ovl0D_06_80047244[i]);
            func_ovl0D_06_80046B50(flag);
            func_ovl0D_06_80046E60(0x68);
        }
    }
}

static s32 func_ovl0D_06_8004440C(f32 a) {
    if (0.0f == a) {
        return 0;
    } else if (90.0f == a) {
        return 1;
    } else if (180.0f == a) {
        return 2;
    } else if (270.0f == a || -90.0f == a) {
        return 3;
    }
    return -1;
}

/* the tiles under a gate: solid, and the frame around its opening */
static void func_ovl0D_06_80044414(Ent_0D06 *e) {
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
    Obj40_0D06 *p;

    p = e->obj->unk40;
    func_ovl0D_06_80045DE0(p->unk10, p->unk14, p->unk18, grid, 0);
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
    dir = func_ovl0D_06_8004440C(e->obj->unk40->unk20);
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
    func_ovl0D_06_80044398(0, D_ovl0D_06_800475F8, &x0);
    func_ovl0D_06_80044398(1, D_ovl0D_06_800475F8, &y0);
    func_ovl0D_06_80044398(2, D_ovl0D_06_800475F8, &z0);
    func_ovl0D_06_80044398(0, D_ovl0D_06_800475F8, &x1);
    func_ovl0D_06_80044398(1, D_ovl0D_06_800475F8, &y1);
    func_ovl0D_06_80044398(2, D_ovl0D_06_800475F8, &z1);
    func_ovl0D_06_80044398(0, D_ovl0D_06_800475F8, &x2);
    func_ovl0D_06_80044398(2, D_ovl0D_06_800475F8, &z2);
    func_ovl0D_06_80044398(0, D_ovl0D_06_800475F8, &x3);
    func_ovl0D_06_80044398(2, D_ovl0D_06_800475F8, &z3);
    func_ovl0D_06_80045DD0(x0, y0, z0, x1, y1, z1, 0x10);
    func_ovl0D_06_80045DC8(x0, y0 + 1, z0, x1, z1, 0x11);
    func_ovl0D_06_80045DC8(x0, y0, z0, x1, z1, 0xF);
    func_ovl0D_06_80045DC8(x2, y0, z2, x3, z3, 0x11);
    func_ovl0D_06_80045DC8(x2, y0 + 1, z2, x3, z3, 0x10);
}

static void func_ovl0D_06_80044398(s32 axis, s32 *size, s32 *v) {
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

void func_ovl0D_06_8004435C(void) {
    s32 *p;

    p = func_ovl0D_06_80046B70(0x1B);
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl0D_06_8004422C(void) {
    s32 i;

    func_ovl0D_06_800440AC(D_ovl0D_06_800472F4);
    func_ovl0D_06_80046790(D_ovl0D_06_800472F4[0].obj, 0x80000);
    func_ovl0D_06_800440AC(D_ovl0D_06_8004732C);
    func_ovl0D_06_80046790(D_ovl0D_06_8004732C[0].obj, 0x80000);
    func_ovl0D_06_800440AC(D_ovl0D_06_80047364);
    func_ovl0D_06_80046790(D_ovl0D_06_80047364[0].obj, 0x80000);
    for (i = 0; i < 2; i++) {
        func_ovl0D_06_800440AC(&D_ovl0D_06_8004739C[i]);
        D_ovl0D_06_8004739C[i].obj->unk40->unk36 = 0x80;
    }
    func_ovl0D_06_800440AC(D_ovl0D_06_8004740C);
    D_ovl0D_06_8004740C[0].obj->unk40->unk36 = 0x80;
    func_ovl0D_06_800440AC(D_ovl0D_06_80047444);
    func_ovl0D_06_80046788(D_ovl0D_06_80047444[0].obj, 0x02000000);
    func_ovl0D_06_80046790(D_ovl0D_06_80047444[0].obj, 0x80000);
    if (func_ovl0D_06_80046B60(0x415) == 0) {
        func_ovl0D_06_800468D8(func_ovl0D_06_80043C98, NULL, 0, 0, 0x130);
    }
}

static void func_ovl0D_06_800440AC(Ent_0D06 *arg0) {
    arg0->obj = func_ovl0D_06_800467D0(arg0->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0D_06_80046788(arg0->obj, 0x01080000);
    func_ovl0D_06_80046790(arg0->obj, 0x02000000);
    if (arg0->unkC != -1 && arg0->unkE != -1 && arg0->unk10 != -1 && arg0->unk12 != -1) {
        arg0->unk4 = func_ovl0D_06_800464D0(arg0->obj->unk40, 0, arg0->unkC, arg0->unkE, arg0->unk10, arg0->unk12);
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

void func_ovl0D_06_8004401C(void) {
    Ent_0D06 *p;

    func_ovl0D_06_80043FA0(D_ovl0D_06_800472F4);
    func_ovl0D_06_80043FA0(D_ovl0D_06_8004732C);
    func_ovl0D_06_80043FA0(D_ovl0D_06_80047364);
    for (p = D_ovl0D_06_8004739C; p != D_ovl0D_06_8004739C + 2; p++) {
        if (p->obj != NULL) {
            func_ovl0D_06_80043FA0(p);
        }
    }
    func_ovl0D_06_80043FA0(D_ovl0D_06_8004740C);
}

static void func_ovl0D_06_80043FA0(Ent_0D06 *arg0) {
    func_ovl0D_06_800467A0(arg0->obj);
    if (arg0->unkC != -1 && arg0->unkE != -1 && arg0->unk10 != -1 && arg0->unk12 != -1) {
        func_ovl0D_06_800464D8(arg0->unk4);
    }
    arg0->obj = NULL;
    arg0->unk4 = -1;
}

void func_ovl0D_06_80043D60(void) {
    s32 n;

    n = 0;
    if (func_ovl0D_06_80046B60(0x413) != 0) {
        n = 1;
    }
    if (func_ovl0D_06_80046B60(0x414) != 0) {
        n++;
    }
    if (func_ovl0D_06_80046B60(0x415) != 0) {
        n++;
    }
    switch (n) {
        case 0:
            break;
        case 1:
        case 2:
            func_ovl0D_06_80043318(0x11, 0x10);
            D_ovl0D_06_8004732C[0].obj->unk40->unk10 -= n * 100.0f;
            D_ovl0D_06_8004732C[0].obj->unk40->unk48->unk4->unk4 = 0.0f;
            func_ovl0D_06_80043318(0x1F, 0x1F);
            break;
        case 3:
            func_ovl0D_06_8004355C(0x13, 4, 0x10, 0x25);
            func_ovl0D_06_80043318(0x11, 0x10);
            D_ovl0D_06_8004732C[0].obj->unk40->unk10 -= 300.0f;
            func_ovl0D_06_80043318(0x11, 0x10);
            D_ovl0D_06_8004732C[0].obj->unk40->unk10 -= 200.0f;
            D_ovl0D_06_8004732C[0].obj->unk40->unk48->unk4->unk4 = 0.0f;
            func_ovl0D_06_80043318(0x1F, 0x1F);
            func_ovl0D_06_800435FC();
            func_ovl0D_06_80043018(D_ovl0D_06_800472F4[0].obj);
            func_ovl0D_06_80043018(D_ovl0D_06_80047364[0].obj);
            func_ovl0D_06_80043018(D_ovl0D_06_8004740C[0].obj);
            func_ovl0D_06_80043018(D_ovl0D_06_8004739C[1].obj);
            func_ovl0D_06_80043018(D_ovl0D_06_80047444[0].obj);
            func_ovl0D_06_80046790(D_ovl0D_06_8004739C[0].obj, 0x01000000);
            break;
    }
}

void func_ovl0D_06_80043C98(void) {
    while (func_ovl0D_06_80046B60(0x415) == 0) {
        if (func_ovl0D_06_80043214() != 0 && func_ovl0D_06_80046B60(0x409) != 0) {
            if (func_ovl0D_06_80046B60(0x413) != 0 && func_ovl0D_06_80046B60(0x414) != 0) {
                func_ovl0D_06_80043824();
            } else {
                func_ovl0D_06_8004340C();
                if (func_ovl0D_06_80046B60(0x413) == 0) {
                    func_ovl0D_06_80046B50(0x413);
                } else {
                    func_ovl0D_06_80046B50(0x414);
                }
            }
        }
        func_ovl0D_06_800468F8(8);
    }
    func_ovl0D_06_800468E8();
}

void func_ovl0D_06_80043824(void) {
    Obj_0D06 *o;
    f32 y;
    s32 n;

    func_ovl0D_06_80045EF0(0);
    func_ovl0D_06_80045F78(1);
    func_ovl0D_06_80046630(0xF);
    if (func_ovl0D_06_80046618() == 1) {
        func_ovl0D_06_80046620();
    }
    func_ovl0D_06_80045EF8(1);
    func_ovl0D_06_800468F8(30);
    func_ovl0D_06_800466E8();
    func_ovl0D_06_80046630(0x7F);
    func_ovl0D_06_800465C8(1900.0f, 1500.0f, 700.0f);
    func_ovl0D_06_800465E8(45.0f, 45.0f, 2300.0f);
    func_ovl0D_06_800468F8(30);
    func_ovl0D_06_80046E80(0x65, 2000.0f, 0.0f, 600.0f);
    func_ovl0D_06_80046788(D_ovl0D_06_800472F4[0].obj, 0x04000000);
    func_ovl0D_06_800464B0(D_ovl0D_06_8004732C[0].obj->unk40, 1, 0);
    func_ovl0D_06_80046788(D_ovl0D_06_8004732C[0].obj, 0x04000000);
    func_ovl0D_06_80046788(D_ovl0D_06_80047364[0].obj, 0x04000000);
    func_ovl0D_06_80046788(D_ovl0D_06_80047444[0].obj, 0x04000000);
    func_ovl0D_06_80046788(D_ovl0D_06_8004739C[1].obj, 0x04000000);
    func_ovl0D_06_80046788(D_ovl0D_06_8004740C[0].obj, 0x04000000);
    func_ovl0D_06_800466B0(2.0f, 2.0f, 2.0f);
    func_ovl0D_06_800466A0(-1);
    func_ovl0D_06_800433B4(D_ovl0D_06_8004732C[0].obj);
    func_ovl0D_06_80046790(D_ovl0D_06_8004739C[0].obj, 0x01000000);
    func_ovl0D_06_80046E60(0x6D);
    func_ovl0D_06_800466B0(10.0f, 10.0f, 10.0f);
    func_ovl0D_06_800466A0(30);
    func_ovl0D_06_800468F8(1);
    func_ovl0D_06_80046E60(0x6E);
    func_ovl0D_06_800468F8(89);
    n = (s32) (func_ovl0D_06_800464C8(D_ovl0D_06_8004739C[1].obj->unk40, 0) - D_ovl0D_06_8004739C[1].obj->unk40->unk48->unk4->unk4) - 1;
    D_ovl0D_06_8004747C.unk0 = n;
    D_ovl0D_06_8004747C.unkC = 300.0f / n;
    D_ovl0D_06_8004747C.unk10 = -1000.0f / n;
    D_ovl0D_06_8004747C.unk14 = 1000.0f / n;
    func_ovl0D_06_80046600(&D_ovl0D_06_8004747C, 8, 0);
    func_ovl0D_06_800433B4(D_ovl0D_06_8004739C[1].obj);
    func_ovl0D_06_80046E60(0x70);
    func_ovl0D_06_800465C8(2200.0f, 500.0f, 1700.0f);
    func_ovl0D_06_800433B4(D_ovl0D_06_8004732C[0].obj);
    func_ovl0D_06_80046E60(0x71);
    func_ovl0D_06_80043318(0x11, 0x10);
    D_ovl0D_06_8004732C[0].obj->unk40->unk10 -= 300.0f;
    func_ovl0D_06_80043318(0x1F, 0x1F);
    D_ovl0D_06_8004732C[0].obj->unk40->unk10 += 300.0f;
    func_ovl0D_06_800435FC();
    if (func_ovl0D_06_80045F50(0x14, 0x10, 0x1A, 0x10) != 0) {
        o = func_ovl0D_06_80045FC8(func_ovl0D_06_80045F68());
        y = o->unk40->unk14;
        o->unk40->unk14 = 1400.0f;
        o->unk40->unk14 = func_ovl0D_06_80045E48(o->unk40);
        if (o->unk40->unk14 < y) {
            o->unk40->unk14 = y;
        }
    }
    func_ovl0D_06_800468F8(30);
    func_ovl0D_06_80046E60(0x2C);
    func_ovl0D_06_8004355C(0x13, 4, 0x10, 0x25);
    func_ovl0D_06_800465C8(D_ovl0D_06_800475E0.x, D_ovl0D_06_800475E0.y, D_ovl0D_06_800475E0.z);
    func_ovl0D_06_800465E8(45.0f, 45.0f, 1500.0f);
    func_ovl0D_06_800468F8(180);
    func_ovl0D_06_800466F0();
    func_ovl0D_06_800466B8(&D_ovl0D_06_800475B0);
    func_ovl0D_06_80046628(0x1F);
    func_ovl0D_06_80046B50(0x415);
    func_ovl0D_06_80046600(NULL, 0x170, 0);
    func_ovl0D_06_80045EF8(0);
    func_ovl0D_06_80045EF0(1);
    func_ovl0D_06_80045F78(0);
}

static void func_ovl0D_06_800435FC(void) {
    func_ovl0D_06_80045DD0(0x11, 2, 0x11, 0x13, 2, 0x13, 0x11);
    func_ovl0D_06_80045DD0(0x12, 2, 0x12, 0x12, 2, 0x12, 0x10);
    func_ovl0D_06_80045DD0(0x11, 3, 0x11, 0x13, 3, 0x13, 0x10);
    func_ovl0D_06_80045DD0(0x14, 0, 0x10, 0x1A, 1, 0x10, 0x1F);
    func_ovl0D_06_80045DD0(0x14, 1, 0x10, 0x1A, 1, 0x10, 0x1F);
    func_ovl0D_06_80045DD0(0x14, 2, 0x10, 0x17, 2, 0x10, 0x1F);
    func_ovl0D_06_80045DD0(0x18, 2, 0x10, 0x19, 2, 0x10, 0x16);
    func_ovl0D_06_80045DD0(0x1A, 2, 0x10, 0x1A, 2, 0x10, 0x11);
    func_ovl0D_06_80045DD0(0x17, 2, 0x11, 0x1C, 2, 0x11, 0x11);
    func_ovl0D_06_80045DD0(0x14, 3, 0x10, 0x17, 3, 0x10, 0x16);
    func_ovl0D_06_80045DD0(0x18, 3, 0x10, 0x1A, 3, 0x10, 0x10);
    func_ovl0D_06_80045DD0(0x17, 3, 0x11, 0x1C, 3, 0x11, 0x10);
}

/* the camera: x tiles across, above the n rows' heights, z tiles down */
static void func_ovl0D_06_8004355C(s32 x, s32 n, s32 z, s32 id) {
    s32 i;

    D_ovl0D_06_800475E0.x = x * 100.0f;
    D_ovl0D_06_800475E0.y = 0.0f;
    for (i = 0; i < n; i++) {
        D_ovl0D_06_800475E0.y += func_ovl0D_06_80045DF0(i) * 100.0f;
    }
    D_ovl0D_06_800475E0.y += 100.0f;
    D_ovl0D_06_800475E0.z = z * 100.0f;
    D_ovl0D_06_800475D0 = func_ovl0D_06_80046D30(id, &D_ovl0D_06_800475E0.x, 0);
}

void func_ovl0D_06_80043500(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0D_06_800465C8(D_ovl0D_06_800475E0.x, D_ovl0D_06_800475E0.y, D_ovl0D_06_800475E0.z);
    func_ovl0D_06_800465E8(arg0, arg1, arg2);
    func_ovl0D_06_800468F8(180);
}

void func_ovl0D_06_8004340C(void) {
    func_ovl0D_06_80046E80(0x65, 2000.0f, 0.0f, 600.0f);
    func_ovl0D_06_800466B0(2.0f, 2.0f, 2.0f);
    func_ovl0D_06_800466A0(-1);
    func_ovl0D_06_800464B0(D_ovl0D_06_8004732C[0].obj->unk40, 0, 0);
    func_ovl0D_06_80046788(D_ovl0D_06_8004732C[0].obj, 0x04000000);
    func_ovl0D_06_800433B4(D_ovl0D_06_8004732C[0].obj);
    func_ovl0D_06_80046790(D_ovl0D_06_8004732C[0].obj, 0x04000000);
    func_ovl0D_06_800466A0(0);
    func_ovl0D_06_80043318(0x11, 0x10);
    D_ovl0D_06_8004732C[0].obj->unk40->unk48->unk4->unk4 = 0.0f;
    D_ovl0D_06_8004732C[0].obj->unk40->unk10 -= 100.0f;
    func_ovl0D_06_80043318(0x1F, 0x1F);
}

/* waits for the object's animation to end */
static void func_ovl0D_06_800433B4(Obj_0D06 *o) {
    while (!(o->unk40->unkC & 0x40)) {
        func_ovl0D_06_80046920();
    }
}

void func_ovl0D_06_80043318(s32 a, s32 b) {
    s32 pos[6];
    Obj40_0D06 *p;

    p = D_ovl0D_06_8004732C[0].obj->unk40;
    func_ovl0D_06_80045DE0(p->unk10, p->unk14, p->unk18, pos, 0);
    func_ovl0D_06_80045DD0(pos[0], pos[1], pos[2], pos[0] + 2, pos[1], pos[2] + 5, a);
    func_ovl0D_06_80045DD0(pos[0], pos[1] + 1, pos[2], pos[0] + 2, pos[1] + 5, pos[2] + 5, b);
}

s32 func_ovl0D_06_80043214(void) {
    s32 r;

    D_ovl0D_06_800475EC->unk40->unk10 = D_ovl0D_06_8004732C[0].obj->unk40->unk10 + 150.0f;
    D_ovl0D_06_800475EC->unk40->unk14 = D_ovl0D_06_8004732C[0].obj->unk40->unk14;
    D_ovl0D_06_800475EC->unk40->unk18 = D_ovl0D_06_8004732C[0].obj->unk40->unk18 + 250.0f;
    D_ovl0D_06_800475EC->unk30 = 1;
    D_ovl0D_06_800475EC->unk34 = 150.0f;
    D_ovl0D_06_800475EC->unk38 = 150.0f;
    r = func_ovl0D_06_80046738(D_ovl0D_06_800475EC, 0x40);
    if (r & 0x40) {
        if ((r & 0x2000) || (r & 0x4000)) {
            return 1;
        }
        func_ovl0D_06_800431E0(0x26, D_ovl0D_06_800475EC);
        return 0;
    }
    return 0;
}

void func_ovl0D_06_800431E0(s32 arg0, Obj_0D06 *arg1) {
    Obj40_0D06 *p;

    func_ovl0D_06_800431D8();
    p = arg1->unk40;
    func_ovl0D_06_80046E80(arg0, p->unk10, p->unk14, p->unk18);
}

static void func_ovl0D_06_800431D8(void) {
}

void func_ovl0D_06_8004305C(void) {
    s32 i;

    if (func_ovl0D_06_80046B60(0x409) != 0) {
        func_ovl0D_06_80043018(D_ovl0D_06_800472BC[0].obj);
        D_ovl0D_06_80047604 = func_ovl0D_06_80045E58(0x15B);
        func_ovl0D_06_80045E60(D_ovl0D_06_80047604, 0, 0, D_ovl0D_06_800475F8[0] - 1, D_ovl0D_06_800475F8[2] - 1, 0, 0, 0);
        func_ovl0D_06_80046790(D_ovl0D_06_800470BC[0].obj, 0x01000000);
        i = 1;
        D_ovl0D_06_800470BC[i].unk18 = 180.0f;
        D_ovl0D_06_800470BC[i].obj->unk40->unk14 = D_ovl0D_06_800470BC[i].unk18 * 10.0f;
        i = 2;
        D_ovl0D_06_800470BC[i].unk18 = 20.0f;
        D_ovl0D_06_800470BC[i].obj->unk40->unk14 = D_ovl0D_06_800470BC[i].unk18 * 10.0f;
        func_ovl0D_06_80046790(D_ovl0D_06_80047164[0].obj, 0x01000000);
        func_ovl0D_06_80046790(D_ovl0D_06_80047164[1].obj, 0x01000000);
        i = 2;
        D_ovl0D_06_80047164[i].unk18 = 20.0f;
        D_ovl0D_06_80047164[i].obj->unk40->unk14 = D_ovl0D_06_80047164[i].unk18 * 10.0f;
        i++;
        func_ovl0D_06_80046790(D_ovl0D_06_80047164[i].obj, 0x01000000);
    }
}

static void func_ovl0D_06_80043018(Obj_0D06 *o) {
    func_ovl0D_06_80043010();
    o->unk40->unk48->unk4->unk4 = func_ovl0D_06_800464C8(o->unk40, 0) - 0.001f;
}

static void func_ovl0D_06_80043010(void) {
}
