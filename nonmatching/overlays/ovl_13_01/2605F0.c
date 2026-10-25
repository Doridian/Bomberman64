/*
 * NON_MATCHING: ovl_13_01's game object (a boss fight, as far as the code
 * shows: a body (D_ovl13_01_8004C338) with two side parts, two jointed
 * chains of links ending in heads (D_ovl13_01_8004C31C and
 * D_ovl13_01_8004C348[3]), a hit counter per part (8004C28C-8004C29C,
 * doubled-up with event flag 0x41F), the attack moves 80043878-800455D0
 * chosen by 8004899C, the camera (8004C388/8004C3A8) and the intro and
 * end scripts), complete: every function and its data (.data 0x20,
 * .bss 0x1F0 as the original). Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 5887, eu ?, jp ?
 *
 * A first draft from m2c (with the ZeroJump prototypes the other drafts give
 * the same codes), made to compile: vectors as Vec3f, the pointer loops over
 * the link tables as index loops, the ZeroJump calls m2c left unprototyped
 * given their arguments, 800430CC static (its argument comes in its callers'
 * $s0). Most functions are m2c's logic as it came; 8004636C and 80045F14 are
 * rewritten as loops, 800431D4's 300-frame move keeps 300.0f in a variable.
 * The 14 stubs (two `jr ra` in a row): 8004A200 and 8004A4AC-BC are
 * inlined-once statics before their callers; 8004A898-8004A8E0 are the ten
 * unused statics after the tail, defined first in ascending order.
 *
 * Source order: not simply the reverse of the address order. With every
 * definition in descending order IDO emitted 800473A8, 80048B6C and others
 * far from their places (9232 words); the order below is the one
 * scratch/13_01/climb.py found by moving one definition at a time (5895).
 * Still out of place: 800430CC after 80043124, 800473A8 and 80048418 after
 * 80048B6C, 8004956C before 80049158; most of the words of 800473A8,
 * 80048418, 800490DC, 800493EC, 800481D0 and 800471D8 are that.
 *
 * What still differs in us (words): 800473A8 940, 80049870 467, 800446FC
 * 393, 80048418 373, 80043878 348, 80044160 331, 800477C0 299, 800450B4
 * 282, 800490DC 261, 80045F14 237, 800431D4 230, 800455D0 218, 800471D8
 * 173, 800493EC 166, 800481D0 153, 80048E2C 142, 800491B4 131, 80047CB4
 * 113, 80048BB0 112, 800475EC 112; under 50 each: 8004306C, 80043124,
 * 80043608, 80043830, 8004400C, 80045538, 80045B0C, 80045C60, 80045C9C,
 * 80045DAC, 8004636C, 800465FC, 80046800, 80046C2C, 80046DC4, 80046E00,
 * 80046FA8, 80047144, 80047F74, 80048AF0, 8004956C, 800496E0, 8004A088,
 * 8004A208, 8004A2D4, 8004A4C4. The other 36 match. .text is 0x150
 * short of the original's, .rodata 0x10 long.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

/* What func_ovl13_01_8004B620 links two models with (D_ovl13_01_8004C2C0-8004C308). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Link_ovl13_01;

/* The camera move ZeroJump 0x170B takes: two vectors' steps and their changes. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC[3];
    /* 0x18 */ f32 unk18[3];
    /* 0x24 */ f32 unk24[3];
    /* 0x30 */ f32 unk30[3];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
} Move_ovl13_01;

void func_ovl13_01_8004AC48(s32 *); /* 0xC02 */
void func_ovl13_01_8004AC50(s32); /* 0xD00 */
f32 func_ovl13_01_8004AC60(void); /* 0xD02 */
s32 func_ovl13_01_8004ACC8(f32, f32, f32); /* 0xD0F */
f32 func_ovl13_01_8004ACF8(UnkStructA_40 *); /* 0xD15 */
void func_ovl13_01_8004AD18(void (*)(UnkStructA *), s32); /* 0xE02 */
void func_ovl13_01_8004AD20(void (*)(UnkStructA *)); /* 0xE03 */
void func_ovl13_01_8004AD58(void); /* 0xF05 */
void func_ovl13_01_8004AD70(void (*)(UnkStructA *)); /* 0xF08 */
s32 *func_ovl13_01_8004AD88(void); /* 0xF0B */
void func_ovl13_01_8004ADA0(s32); /* 0xF0E */
void func_ovl13_01_8004ADB0(s32); /* 0xF10 */
void func_ovl13_01_8004ADE8(void); /* 0x1000 */
void func_ovl13_01_8004ADF8(void *); /* 0x1002 */
s32 func_ovl13_01_8004AE18(void); /* 0x1006 */
void func_ovl13_01_8004AE20(s32, void *); /* 0x1007 */
void func_ovl13_01_8004AE28(s32); /* 0x1008 */
void func_ovl13_01_8004AE40(const char *); /* 0x100B */
UnkStructA * func_ovl13_01_8004AE78(s32); /* 0x1012 */
UnkStructA * func_ovl13_01_8004AEB8(s32); /* 0x101A */
void func_ovl13_01_8004AED8(s32); /* 0x101E */
s32 func_ovl13_01_8004AF00(s32); /* 0x1023 */
void func_ovl13_01_8004B340(UnkStructA_40 *, s32); /* 0x1505 */
void func_ovl13_01_8004B348(UnkStructA_40 *, s32, s32, s32); /* 0x1506 */
void func_ovl13_01_8004B360(UnkStructA_40 *, s32, s32); /* 0x1509 */
f32 func_ovl13_01_8004B378(UnkStructA_40 *, s32); /* 0x150C */
void func_ovl13_01_8004B390(UnkStructA_40 *, s32, s32); /* 0x150F */
void func_ovl13_01_8004B468(s32); /* 0x1702 */
void func_ovl13_01_8004B478(f32, f32, f32); /* 0x1704 */
void func_ovl13_01_8004B488(f32, f32, f32); /* 0x1706 */
void func_ovl13_01_8004B498(f32, f32, f32); /* 0x1708 */
void func_ovl13_01_8004B4A0(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl13_01_8004B4B0(Move_ovl13_01 *, s32, s32); /* 0x170B */
void func_ovl13_01_8004B4D0(void); /* 0x170F */
void func_ovl13_01_8004B4D8(s32); /* 0x1710 */
void func_ovl13_01_8004B4E0(s32); /* 0x1711 */
void func_ovl13_01_8004B4F0(s32); /* 0x1713 */
void func_ovl13_01_8004B518(f32 *); /* 0x1718 */
void func_ovl13_01_8004B528(f32, f32, f32, f32); /* 0x171A */
void func_ovl13_01_8004B530(f32, f32); /* 0x171B */
void func_ovl13_01_8004B540(void *); /* 0x171D */
void func_ovl13_01_8004B568(void *); /* 0x1722 */
void func_ovl13_01_8004B570(f32 *); /* 0x1723 */
void func_ovl13_01_8004B580(f32 *); /* 0x1725 */
void func_ovl13_01_8004B588(f32 *); /* 0x1726 */
void func_ovl13_01_8004B590(f32 *); /* 0x1727 */
void func_ovl13_01_8004B5C8(f32 *, f32 *, f32 *); /* 0x1803 */
void func_ovl13_01_8004B5D0(f32 *, f32 *); /* 0x1804 */
f32 func_ovl13_01_8004B5E0(f32 *, f32 *); /* 0x1806 */
s32 func_ovl13_01_8004B5E8(UnkStructA *, s32); /* 0x1807 */
void func_ovl13_01_8004B608(UnkStructA *, s32); /* 0x180B */
void func_ovl13_01_8004B620(UnkStructA *, UnkStructA *, Link_ovl13_01 *, s32); /* 0x180E */
void func_ovl13_01_8004B630(s32); /* 0x1810 */
void func_ovl13_01_8004B638(UnkStructA *, s32); /* 0x1811 */
void func_ovl13_01_8004B640(UnkStructA *, s32); /* 0x1812 */
void func_ovl13_01_8004B650(UnkStructA *); /* 0x1814 */
UnkStructA * func_ovl13_01_8004B660(s32, s32, s32, UnkStructA *); /* 0x1816 */
void func_ovl13_01_8004B6B8(UnkStructA *); /* 0x1821 */
void func_ovl13_01_8004B708(UnkStructA *, f32 *); /* 0x182B */
void func_ovl13_01_8004B710(UnkStructA *, UnkStructA *); /* 0x182C */
void func_ovl13_01_8004B748(UnkStructA *); /* 0x1833 */
s32 func_ovl13_01_8004B758(UnkStructA *, s32, UnkStructA *); /* 0x1835 */
void func_ovl13_01_8004B768(s32 *); /* 0x1837 */
void func_ovl13_01_8004B770(void); /* 0x1838 */
void func_ovl13_01_8004B778(void); /* 0x1839 */
s32 func_ovl13_01_8004B788(void (*)(), void *, s32, s32, s32); /* 0x1900 */
void func_ovl13_01_8004B798(void); /* 0x1902 */
void func_ovl13_01_8004B7A8(s32); /* 0x1904 */
void *func_ovl13_01_8004B7B0(void); /* 0x1905 */
s32 func_ovl13_01_8004B7D0(void); /* 0x1909 */
UnkStructC *func_ovl13_01_8004B810(s32); /* 0x1A00 */
void func_ovl13_01_8004B820(UnkStructC *, s32); /* 0x1A02 */
f32 func_ovl13_01_8004B930(f32); /* 0x1D00 */
f32 func_ovl13_01_8004B938(f32); /* 0x1D01 */
f64 func_ovl13_01_8004B940(void); /* 0x1D02 */
s32 func_ovl13_01_8004B948(s32); /* 0x1D03 */
s32 func_ovl13_01_8004B970(f32, f32); /* 0x1D08 */ /* unknown */
s32 func_ovl13_01_8004B978(f32); /* 0x1D09 */ /* unknown */
s32 func_ovl13_01_8004B988(f32, f32); /* 0x1D0B */
void func_ovl13_01_8004B9A0(void); /* 0x1D0E */
void func_ovl13_01_8004B9A8(void); /* 0x1D0F */
void func_ovl13_01_8004B9B0(void); /* 0x1D10 */
void func_ovl13_01_8004B9B8(f32 *); /* 0x1D11 */
void func_ovl13_01_8004B9C0(void); /* 0x1D12 */
s32 func_ovl13_01_8004B9F0(s32); /* 0x1E04 */
void func_ovl13_01_8004BA00(s32); /* 0x1E06 */
void func_ovl13_01_8004BA08(s32); /* 0x1E07 */
s32 func_ovl13_01_8004BA10(s32); /* 0x1E08 */
void func_ovl13_01_8004BA40(f32, s32, s32, s32); /* 0x1F03 */
void func_ovl13_01_8004BA88(s32, s32, s32, f32); /* 0x2004 */
void func_ovl13_01_8004BAE0(s32); /* 0x2202 */
void func_ovl13_01_8004BAE8(s32); /* 0x2203 */
void func_ovl13_01_8004BBE0(s32, f32 *, s32); /* 0x2601 */
void func_ovl13_01_8004BC88(UnkStructA *, s32, f32); /* 0x2901 */
void func_ovl13_01_8004BD10(s32); /* 0x2B00 */
void func_ovl13_01_8004BD20(s32); /* 0x2B02 */
void func_ovl13_01_8004BD28(void); /* 0x2B03 */
void func_ovl13_01_8004BD30(s32, f32, f32, f32); /* 0x2B04 */
void func_ovl13_01_8004BE88(void); /* 0x3000 */
void func_ovl13_01_8004BE90(void); /* 0x3001 */

/* .bss */
Vec3f D_ovl13_01_8004C200;
u8 D_ovl13_01_8004C20C[4];
Vec3f D_ovl13_01_8004C210;
s32 D_ovl13_01_8004C21C;
u8 D_ovl13_01_8004C220[4];
s32 D_ovl13_01_8004C224;
s32 D_ovl13_01_8004C228;
u8 D_ovl13_01_8004C22C[4];
Vec3f D_ovl13_01_8004C230;
s32 *D_ovl13_01_8004C23C;
Vec3f D_ovl13_01_8004C240;
f32 D_ovl13_01_8004C24C;
f32 D_ovl13_01_8004C250;
UnkStructA *D_ovl13_01_8004C254;
UnkStructA *D_ovl13_01_8004C258;
UnkStructA *D_ovl13_01_8004C25C;
Vec3f D_ovl13_01_8004C260;
u8 D_ovl13_01_8004C26C[4];
s32 D_ovl13_01_8004C270[3];
UnkStructC *D_ovl13_01_8004C27C;
s32 D_ovl13_01_8004C280;
s32 D_ovl13_01_8004C284;
s32 D_ovl13_01_8004C288;
s32 D_ovl13_01_8004C28C;
s32 D_ovl13_01_8004C290;
s32 D_ovl13_01_8004C294;
s32 D_ovl13_01_8004C298;
s32 D_ovl13_01_8004C29C;
s32 D_ovl13_01_8004C2A0;
f32 D_ovl13_01_8004C2A4;
f32 D_ovl13_01_8004C2A8;
s32 D_ovl13_01_8004C2AC;
Vec3f D_ovl13_01_8004C2B0;
f32 D_ovl13_01_8004C2BC;
Link_ovl13_01 D_ovl13_01_8004C2C0;
u8 D_ovl13_01_8004C2D4[4];
Link_ovl13_01 D_ovl13_01_8004C2D8;
u8 D_ovl13_01_8004C2EC[4];
Link_ovl13_01 D_ovl13_01_8004C2F0;
u8 D_ovl13_01_8004C304[4];
Link_ovl13_01 D_ovl13_01_8004C308;
UnkStructA *D_ovl13_01_8004C31C;
UnkStructA *D_ovl13_01_8004C320;
UnkStructA *D_ovl13_01_8004C324;
UnkStructA *D_ovl13_01_8004C328;
u8 D_ovl13_01_8004C32C[4];
UnkStructA *D_ovl13_01_8004C330[2];
UnkStructA *D_ovl13_01_8004C338;
UnkStructA *D_ovl13_01_8004C33C;
UnkStructA *D_ovl13_01_8004C340;
u8 D_ovl13_01_8004C344[4];
UnkStructA *D_ovl13_01_8004C348[4];
UnkStructA *D_ovl13_01_8004C358;
UnkStructA *D_ovl13_01_8004C35C;
UnkStructA *D_ovl13_01_8004C360;
u8 D_ovl13_01_8004C364[4];
Vec3f D_ovl13_01_8004C368;
u8 D_ovl13_01_8004C374[4];
Vec3f D_ovl13_01_8004C378;
u8 D_ovl13_01_8004C384[4];
Vec3f D_ovl13_01_8004C388;
u8 D_ovl13_01_8004C394[4];
Vec3f D_ovl13_01_8004C398;
u8 D_ovl13_01_8004C3A4[4];
Vec3f D_ovl13_01_8004C3A8;
s32 D_ovl13_01_8004C3B4;
f32 D_ovl13_01_8004C3B8;
s32 D_ovl13_01_8004C3BC;
s32 D_ovl13_01_8004C3C0;
s32 D_ovl13_01_8004C3C4;
u32 D_ovl13_01_8004C3C8;
s32 D_ovl13_01_8004C3CC;
s32 D_ovl13_01_8004C3D0;
s32 D_ovl13_01_8004C3D4;
s32 D_ovl13_01_8004C3D8;
u8 D_ovl13_01_8004C3DC[4];
Vec3f D_ovl13_01_8004C3E0;
u8 D_ovl13_01_8004C3EC[4];

void func_ovl13_01_80043010(void);
void func_ovl13_01_8004306C(s32 arg0);
static void func_ovl13_01_800430CC(UnkStructA *arg0);
void func_ovl13_01_80043124(s32 arg0, UnkStructA *arg1);
void func_ovl13_01_80043158(void);
void func_ovl13_01_800431D4(void);
void func_ovl13_01_80043608(void);
void func_ovl13_01_8004377C(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
s32 func_ovl13_01_800437FC(UnkStructA *arg0);
s32 func_ovl13_01_80043830(void);
void func_ovl13_01_80043878(void);
f32 func_ovl13_01_80043F88(s32 arg0);
void func_ovl13_01_8004400C(f32 arg0);
void func_ovl13_01_80044118(void);
void func_ovl13_01_80044160(s32 arg0);
void func_ovl13_01_800446B0(void);
void func_ovl13_01_800446FC(void);
void func_ovl13_01_80044F3C(void *arg0);
void func_ovl13_01_80044F74(void);
void func_ovl13_01_800450B4(s32 arg0);
void func_ovl13_01_80045538(void);
void func_ovl13_01_800455D0(s32 arg0);
void func_ovl13_01_80045B0C(void);
f32 func_ovl13_01_80045C60(f32 arg0, f32 arg1);
void func_ovl13_01_80045C9C(void);
void func_ovl13_01_80045D80(void *arg0, s32 arg1);
void func_ovl13_01_80045DAC(UnkStructA **arg0, f32 *arg1, f32 *arg2);
void func_ovl13_01_80045F14(void);
void func_ovl13_01_800462DC(void);
void func_ovl13_01_8004636C(void);
void func_ovl13_01_800465FC(f32 *arg0, f32 *arg1);
void func_ovl13_01_80046800(void);
void func_ovl13_01_800468A0(void);
void func_ovl13_01_800468F0(void);
void func_ovl13_01_80046940(void);
void func_ovl13_01_800469C8(void);
void func_ovl13_01_80046A50(void);
void func_ovl13_01_80046AD8(void);
void func_ovl13_01_80046B60(void);
void func_ovl13_01_80046BB0(void);
void func_ovl13_01_80046C00(void *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void func_ovl13_01_80046C2C(void);
s32 func_ovl13_01_80046DC4(UnkStructA *arg0);
void func_ovl13_01_80046E00(void);
void func_ovl13_01_80046FA8(f32 *arg0);
void func_ovl13_01_80047144(void);
void func_ovl13_01_800471D8(void);
void func_ovl13_01_800473A8(void);
void func_ovl13_01_80047570(void);
void func_ovl13_01_800475EC(UnkStructA *arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl13_01_800477C0(void);
void func_ovl13_01_80047CB4(void *arg0);
void func_ovl13_01_80047F74(void);
void func_ovl13_01_800481D0(void);
void func_ovl13_01_80048418(void);
void func_ovl13_01_8004863C(void);
void func_ovl13_01_800486B8(u32 arg0, s32 arg1);
void func_ovl13_01_8004874C(void);
void func_ovl13_01_8004899C(void);
void func_ovl13_01_80048AF0(UnkStructA *arg0);
void func_ovl13_01_80048B6C(UnkStructA *arg0);
void func_ovl13_01_80048BB0(void);
void func_ovl13_01_80048E2C(void);
void func_ovl13_01_800490DC(void);
void func_ovl13_01_80049158(UnkStructA *arg0);
void func_ovl13_01_800491B4(UnkStructA *arg0, f32 *arg1);
void func_ovl13_01_800493EC(UnkStructA *arg0);
void func_ovl13_01_8004956C(void);
void func_ovl13_01_800496E0(UnkStructA *arg0, s32 *arg1, s32 *arg2, void (*arg3)());
void func_ovl13_01_800497DC(UnkStructA *arg0, s32 *arg1, s32 *arg2);
void func_ovl13_01_80049870(void);
void func_ovl13_01_8004A088(void);
void func_ovl13_01_8004A17C(void);
void func_ovl13_01_8004A1B8(void);
void func_ovl13_01_8004A208(void);
void func_ovl13_01_8004A2D4(void);
void func_ovl13_01_8004A39C(void);
void func_ovl13_01_8004A3E8(void);
void func_ovl13_01_8004A4C4(void);
void func_ovl13_01_8004A6FC(s32 arg0);
void func_ovl13_01_8004A7DC(f32 arg0);
void func_ovl13_01_8004A824(f32 arg0, f32 arg1, f32 arg2);
void func_ovl13_01_8004A880(void);

/* .data */
u32 D_ovl13_01_8004BF30 = 3;
s32 D_ovl13_01_8004BF34 = 0;
s32 D_ovl13_01_8004BF38 = 0;
s32 D_ovl13_01_8004BF3C = 0;
s32 D_ovl13_01_8004BF40 = 0;
s32 D_ovl13_01_8004BF44 = 0;

/* unused: the stubs IDO -O3 leaves after the tail */
static void func_ovl13_01_8004A898(void) {
}

static void func_ovl13_01_8004A8A0(void) {
}

static void func_ovl13_01_8004A8A8(void) {
}

static void func_ovl13_01_8004A8B0(void) {
}

static void func_ovl13_01_8004A8B8(void) {
}

static void func_ovl13_01_8004A8C0(void) {
}

static void func_ovl13_01_8004A8C8(void) {
}

static void func_ovl13_01_8004A8D0(void) {
}

static void func_ovl13_01_8004A8D8(void) {
}

static void func_ovl13_01_8004A8E0(void) {
}

void func_ovl13_01_8004A880(void) {
    D_ovl13_01_8004C224 = -1;
    D_ovl13_01_8004C228 = -1;
}

void func_ovl13_01_8004A824(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl13_01_8004B478(D_ovl13_01_8004C230.x, D_ovl13_01_8004C230.y, D_ovl13_01_8004C230.z);
    func_ovl13_01_8004B498(arg0, arg1, arg2);
    func_ovl13_01_8004B7A8(0xB4);
}

void func_ovl13_01_8004A7DC(f32 arg0) {
    f32 sp1C;

    func_ovl13_01_8004B4A0(&sp1C, NULL, NULL);
    func_ovl13_01_8004B498(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl13_01_8004A6FC(s32 arg0) {
    switch (arg0) {
    case 2:
        func_ovl13_01_8004A4C4();
    case 17:
    default:
        break;
    case 4:
        func_ovl13_01_8004A3E8();
        break;
    case 5:
        func_ovl13_01_8004A2D4();
        break;
    case 3:
        func_ovl13_01_8004A208();
        break;
    case 11:
        func_ovl13_01_8004B9B0();
        func_ovl13_01_8004BA00(0x401);
        break;
    case 1:
        if (func_ovl13_01_8004BA10(0x401) == 0) {
            func_ovl13_01_8004B9B0();
        }
        func_ovl13_01_8004B778();
        if (*D_ovl13_01_8004C23C & 2) {
            func_ovl13_01_8004BE90();
        }
        break;
    }
}

static void func_ovl13_01_8004A4BC(void) {
}

static void func_ovl13_01_8004A4B4(void) {
}

static void func_ovl13_01_8004A4AC(void) {
}

void func_ovl13_01_8004A4C4(void) {
    UnkStructC *temp_v0;

    func_ovl13_01_8004A4BC();
    func_ovl13_01_8004A4B4();
    func_ovl13_01_8004A4AC();
    D_ovl13_01_8004C254 = func_ovl13_01_8004B660(0x292, 0x01000000, 0xD0, NULL);
    D_ovl13_01_8004C25C = func_ovl13_01_8004B660(0x294, 0x01080000, 0xD0, NULL);
    D_ovl13_01_8004C258 = func_ovl13_01_8004B660(0x293, 0x01080000, 0xD0, NULL);
    D_ovl13_01_8004C25C->unk40->unk36 = 0xB2;
    D_ovl13_01_8004C258->unk40->unk36 = D_ovl13_01_8004C25C->unk40->unk36;
    func_ovl13_01_8004AC50(0x295);
    func_ovl13_01_8004ADE8();
    func_ovl13_01_8004AE78(func_ovl13_01_8004AE18())->unk40->unk20 = 180.0f;
    func_ovl13_01_8004A088();
    func_ovl13_01_8004AC48(D_ovl13_01_8004C270);
    D_ovl13_01_8004C260.y = 0.0f;
    D_ovl13_01_8004C260.x = ((f32) ((s32) D_ovl13_01_8004C270[0] / 2) * 100.0f) - 50.0f;
    D_ovl13_01_8004C260.z = (f32) (((f32) ((s32) D_ovl13_01_8004C270[2] / 2) * 100.0f) - 50.0f);
    func_ovl13_01_8004AD20(func_ovl13_01_80048B6C);
    func_ovl13_01_8004AD18(func_ovl13_01_800493EC, 5);
    func_ovl13_01_8004AD70(func_ovl13_01_80049158);
    temp_v0 = func_ovl13_01_8004B810(0x296);
    D_ovl13_01_8004C27C = temp_v0;
    func_ovl13_01_8004B820(temp_v0, 0x20000000);
    D_ovl13_01_8004C27C->unk40 = 0.5f;
    D_ovl13_01_8004C27C->unk44 = D_ovl13_01_8004C27C->unk40 * 0.75f;
    D_ovl13_01_8004C27C->unk3C = D_ovl13_01_8004C27C->unk4C * 0.25f;
    D_ovl13_01_8004C21C = func_ovl13_01_8004AE18();
    func_ovl13_01_8004ADF8(&D_ovl13_01_8004C210.x);
    func_ovl13_01_8004AE20(D_ovl13_01_8004C21C, &D_ovl13_01_8004C200.x);
    func_ovl13_01_8004B770();
    func_ovl13_01_8004B9A8();
    func_ovl13_01_80049870();
}

void func_ovl13_01_8004A3E8(void) {
    func_ovl13_01_8004ADB0(0);
    func_ovl13_01_8004B4E0(0x1F);
    func_ovl13_01_8004B4F0(2);
    func_ovl13_01_8004B530(25.0f, 25.0f);
    func_ovl13_01_8004B498(0.0f, 25.0f, 2500.0f);
    D_ovl13_01_8004C24C = 1.0f;
    D_ovl13_01_8004C250 = 600.0f;
    func_ovl13_01_8004B630(0);
    func_ovl13_01_80043608();
    if (*D_ovl13_01_8004C23C & 2) {
        func_ovl13_01_8004B788(func_ovl13_01_8004956C, NULL, 0, 0, 0x130);
    }
    func_ovl13_01_8004B9C0();
}

void func_ovl13_01_8004A39C(void) {
    if (*D_ovl13_01_8004C23C & 2) {
        func_ovl13_01_8004B788(func_ovl13_01_8004956C, NULL, 0, 0, 0x130);
    }
}

void func_ovl13_01_8004A2D4(void) {
    D_ovl13_01_8004C21C = func_ovl13_01_8004AE18();
    func_ovl13_01_8004ADF8(&D_ovl13_01_8004C210.x);
    func_ovl13_01_8004AE20(D_ovl13_01_8004C21C, &D_ovl13_01_8004C200.x);
    func_ovl13_01_800431D4();
    func_ovl13_01_8004B9A0();
    func_ovl13_01_8004B768(&D_ovl13_01_8004C28C);
    if (func_ovl13_01_8004BA10(0x400) != 0) {
        if (!(*D_ovl13_01_8004C23C & 2)) {
            func_ovl13_01_8004BD20(0x13);
        }
    } else {
        func_ovl13_01_8004BA00(0x400);
    }
    func_ovl13_01_8004B788(func_ovl13_01_800490DC, (void *)0x11, 0, 0, 0x150);
}

void func_ovl13_01_800493EC(UnkStructA *arg0) {
    Vec3f sp3C;
    Vec3f sp30;
    s32 temp_t5;
    s32 temp_v1;
    Vec3f *temp_a1;

    if (func_ovl13_01_8004BA10(0x415) != 0) {
        func_ovl13_01_8004B708(arg0, &sp30.x);
        func_ovl13_01_8004B5C8(&D_ovl13_01_8004C388.x, &sp30.x, &sp3C.x);
        if (!(D_ovl13_01_8004C388.y < sp30.y) && !(sp3C.z > 1000.0f)) {
            func_ovl13_01_800491B4(arg0, &sp3C.x);
            if (arg0->unk68 == 0.0f) {
                if (arg0->unk6C == 0.0f) {
                    temp_v1 = D_ovl13_01_8004C284;
                    if ((temp_v1 == D_ovl13_01_8004C288) && (D_ovl13_01_8004C280 < 0xA)) {
                        D_ovl13_01_8004C280 += 1;
                        func_ovl13_01_8004B708(arg0, &(&D_ovl13_01_8004C3E0)[D_ovl13_01_8004C288].x);
                        temp_a1 = &(&D_ovl13_01_8004C3E0)[D_ovl13_01_8004C288];
                        temp_a1->y += 25.0f;
                        func_ovl13_01_8004B788(func_ovl13_01_80048E2C, temp_a1, 0, 0, 0x150);
                    }
                    temp_t5 = temp_v1 + 1;
                    D_ovl13_01_8004C284 = temp_t5;
                    if (temp_t5 >= 0xA) {
                        D_ovl13_01_8004C284 = 0;
                    }
                }
            }
        }
    }
}

void func_ovl13_01_80049158(UnkStructA *arg0) {
    func_ovl13_01_80043124(0x1E, D_ovl13_01_8004C31C);
    func_ovl13_01_8004BD10(0xDB);
    func_ovl13_01_8004B788(func_ovl13_01_80048BB0, arg0, 0, 0, 0x150);
    func_ovl13_01_8004B7A8(0x78);
}

static void func_ovl13_01_8004A200(void) {
}

void func_ovl13_01_8004A208(void) {
    s32 temp_t7;

    func_ovl13_01_8004A200();
    if ((func_ovl13_01_8004ACF8(func_ovl13_01_8004AE78(func_ovl13_01_8004AE18())->unk40) != 20000.0f) || !(D_ovl13_01_8004C200.y < 0.0f)) {
        D_ovl13_01_8004C21C = func_ovl13_01_8004AE18();
        func_ovl13_01_8004ADF8(&D_ovl13_01_8004C210.x);
        func_ovl13_01_8004AE20(D_ovl13_01_8004C21C, &D_ovl13_01_8004C200.x);
    }
    func_ovl13_01_8004BA00(0x420);
    temp_t7 = D_ovl13_01_8004C288 + 1;
    D_ovl13_01_8004C288 = temp_t7;
    if (temp_t7 >= 0xA) {
        D_ovl13_01_8004C288 = 0;
    }
    D_ovl13_01_8004C284 = 0;
}

void func_ovl13_01_8004A1B8(void) {
    func_ovl13_01_8004B778();
    if (*D_ovl13_01_8004C23C & 2) {
        func_ovl13_01_8004BE90();
    }
}

void func_ovl13_01_8004A17C(void) {
    if (*D_ovl13_01_8004C23C & 2) {
        func_ovl13_01_8004BE90();
    }
}

void func_ovl13_01_8004A088(void) {
    s32 *temp_v0;

    func_ovl13_01_8004BA08(0x43F);
    func_ovl13_01_8004BA08(0x43E);
    func_ovl13_01_8004BA08(0x43D);
    func_ovl13_01_8004BA08(0x43C);
    func_ovl13_01_8004BA08(0x43B);
    func_ovl13_01_8004BA08(0x41F);
    func_ovl13_01_8004BA08(0x41E);
    func_ovl13_01_8004BA08(0x41D);
    func_ovl13_01_8004BA08(0x41C);
    func_ovl13_01_8004BA08(0x41B);
    func_ovl13_01_8004BA00(0x41A);
    func_ovl13_01_8004BA08(0x419);
    func_ovl13_01_8004BA08(0x418);
    func_ovl13_01_8004BA00(0x416);
    func_ovl13_01_8004BA08(0x417);
    func_ovl13_01_8004BA00(0x415);
    func_ovl13_01_8004BA08(0x420);
    func_ovl13_01_8004BA00(0x414);
    func_ovl13_01_8004BA00(0x413);
    func_ovl13_01_8004BA08(0x412);
    func_ovl13_01_8004BA08(0x411);
    func_ovl13_01_8004BA08(0x401);
    temp_v0 = func_ovl13_01_8004AD88();
    D_ovl13_01_8004C23C = temp_v0;
    if (M2C_FIELD(temp_v0, s32 *, 0x10) == 0) {
        func_ovl13_01_8004BA00(0x41F);
    }
}

void func_ovl13_01_80049870(void) {
    UnkStructA **var_s2;
    UnkStructA **var_s2_2;
    UnkStructA *temp_s3;
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_10;
    UnkStructA *temp_v0_11;
    UnkStructA *temp_v0_12;
    UnkStructA *temp_v0_13;
    UnkStructA *temp_v0_2;
    UnkStructA *temp_v0_3;
    UnkStructA *temp_v0_4;
    UnkStructA *temp_v0_5;
    UnkStructA *temp_v0_6;
    UnkStructA *temp_v0_7;
    UnkStructA *temp_v0_8;
    UnkStructA *temp_v0_9;
    UnkStructA *var_s1;
    UnkStructA *var_s1_2;
    UnkStructA *var_s3;
    UnkStructA_40 *temp_v1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 var_s0;

    D_ovl13_01_8004C3C4 = 0x10;
    if (func_ovl13_01_8004BA10(0x41F) != 0) {
        D_ovl13_01_8004C3C4 *= 2;
    }
    D_ovl13_01_8004C2A8 = 0.5f;
    D_ovl13_01_8004C2AC = 1;
    D_ovl13_01_8004C2A4 = 1.0f;
    D_ovl13_01_8004C2A0 = 1;
    D_ovl13_01_8004C284 = 0;
    D_ovl13_01_8004C288 = 0;
    D_ovl13_01_8004C280 = 0;
    D_ovl13_01_8004C3C0 = 0;
    if (func_ovl13_01_8004BA10(0x41F) != 0) {
        D_ovl13_01_8004C28C = 6;
        D_ovl13_01_8004C290 = 4;
        D_ovl13_01_8004C294 = 4;
        D_ovl13_01_8004C298 = 2;
        D_ovl13_01_8004C29C = 2;
    } else {
        D_ovl13_01_8004C28C = 8;
        D_ovl13_01_8004C290 = 4;
        D_ovl13_01_8004C294 = 4;
        D_ovl13_01_8004C298 = 4;
        D_ovl13_01_8004C29C = 4;
    }
    D_ovl13_01_8004C378.x = (f32) D_ovl13_01_8004C200.x;
    D_ovl13_01_8004C378.y = (f32) (D_ovl13_01_8004C200.y + 300.0f);
    D_ovl13_01_8004C378.z = (f32) (D_ovl13_01_8004C200.z - 1200.0f);
    D_ovl13_01_8004C368.x = (f32) D_ovl13_01_8004C378.x;
    D_ovl13_01_8004C368.y = (f32) D_ovl13_01_8004C378.y;
    D_ovl13_01_8004C388.x = D_ovl13_01_8004C378.x;
    D_ovl13_01_8004C388.y = (f32) D_ovl13_01_8004C378.y;
    D_ovl13_01_8004C388.z = (f32) D_ovl13_01_8004C378.z;
    D_ovl13_01_8004C368.z = (f32) (D_ovl13_01_8004C378.z - 7000.0f);
    D_ovl13_01_8004C3A8.x = 0.0f;
    D_ovl13_01_8004C3A8.y = 0.0f;
    D_ovl13_01_8004C3A8.z = 0.0f;
    D_ovl13_01_8004C398.x = D_ovl13_01_8004C388.x;
    D_ovl13_01_8004C398.y = (f32) D_ovl13_01_8004C388.y;
    D_ovl13_01_8004C398.z = (f32) D_ovl13_01_8004C388.z;
    D_ovl13_01_8004C3C8 = 6;
    D_ovl13_01_8004C3CC = 0;
    func_ovl13_01_8004B788(func_ovl13_01_8004899C, NULL, 0, 0, 0x110);
    func_ovl13_01_8004B788(func_ovl13_01_80048418, NULL, 0, 0, 0x130);
    D_ovl13_01_8004C2C0.unk0 = 0x10002;
    D_ovl13_01_8004C2C0.unk8 = 0.0f;
    D_ovl13_01_8004C2D8.unk0 = 0x10002;
    D_ovl13_01_8004C2D8.unk8 = 0.0f;
    D_ovl13_01_8004C2C0.unk10 = 0.9f;
    D_ovl13_01_8004C2C0.unk4 = 70.0f;
    D_ovl13_01_8004C2C0.unkC = 1.0f;
    D_ovl13_01_8004C2D8.unk4 = 5.0f;
    D_ovl13_01_8004C2D8.unk10 = 0.9f;
    D_ovl13_01_8004C2D8.unkC = 0.45f;
    D_ovl13_01_8004C2BC = D_ovl13_01_8004C2C0.unkC;
    D_ovl13_01_8004C2F0.unk0 = 0x10002;
    D_ovl13_01_8004C2F0.unk8 = 0.0f;
    D_ovl13_01_8004C308.unk0 = 0x10002;
    D_ovl13_01_8004C308.unk8 = 0.0f;
    D_ovl13_01_8004C2F0.unk10 = 0.9f;
    D_ovl13_01_8004C308.unk10 = 0.9f;
    D_ovl13_01_8004C2F0.unkC = 0.4f;
    D_ovl13_01_8004C308.unkC = 0.4f;
    D_ovl13_01_8004C2F0.unk4 = 70.0f;
    D_ovl13_01_8004C308.unk4 = 60.0f;
    temp_v0 = func_ovl13_01_8004B660(0x297, 0x01008010, 0x30, NULL);
    D_ovl13_01_8004C338 = temp_v0;
    temp_v0->unk30 = 1;
    temp_v0->unk38 = 0.0f;
    temp_v0->unkC = 0x7E42;
    temp_v0->unk34 = 150.0f;
    func_ovl13_01_8004B340(temp_v0->unk40, 8);
    func_ovl13_01_80046AD8();
    func_ovl13_01_800469C8();
    temp_v0_2 = func_ovl13_01_8004B660(-1, 0x608010, 0xC0, D_ovl13_01_8004C338);
    D_ovl13_01_8004C358 = temp_v0_2;
    temp_v0_2->unk4C = -400.0f;
    D_ovl13_01_8004C358->unk50 = 0.0f;
    D_ovl13_01_8004C358->unk54 = 100.0f;
    D_ovl13_01_8004C358->unk40->unk30 = 2.0f;
    temp_v1 = D_ovl13_01_8004C358->unk40;
    temp_fv0 = temp_v1->unk30;
    temp_v1->unk2C = temp_fv0;
    D_ovl13_01_8004C358->unk40->unk28 = temp_fv0;
    D_ovl13_01_8004C358->unkC = 0x7E42;
    temp_v0_3 = func_ovl13_01_8004B660(-1, 0x608010, 0xC0, D_ovl13_01_8004C338);
    D_ovl13_01_8004C35C = temp_v0_3;
    temp_v0_3->unk4C = D_ovl13_01_8004C358->unk4C * -1.0f;
    D_ovl13_01_8004C35C->unk50 = D_ovl13_01_8004C358->unk50;
    D_ovl13_01_8004C35C->unk54 = D_ovl13_01_8004C358->unk54;
    temp_fv0_2 = D_ovl13_01_8004C358->unk40->unk28;
    D_ovl13_01_8004C35C->unk40->unk30 = temp_fv0_2;
    D_ovl13_01_8004C35C->unk40->unk2C = temp_fv0_2;
    D_ovl13_01_8004C35C->unk40->unk28 = temp_fv0_2;
    D_ovl13_01_8004C35C->unkC = D_ovl13_01_8004C358->unkC;
    temp_v0_4 = func_ovl13_01_8004B660(-1, 0x400000, 0x30, temp_v0);
    D_ovl13_01_8004C320 = temp_v0_4;
    temp_v0_4->unk54 = 70.0f;
    temp_v0_4->unk4C = 0.0f;
    temp_v0_4->unk50 = 25.0f;
    temp_v0_5 = func_ovl13_01_8004B660(-1, 0x500000, 0x30, temp_v0_4);
    D_ovl13_01_8004C324 = temp_v0_5;
    temp_v0_5->unk4C = 0.0f;
    temp_v0_5->unk50 = 0.0f;
    M2C_FIELD(temp_v0_5, void **, 0x3C) = &D_ovl13_01_8004C2D8;
    temp_v0_5->unk54 = 5.0f;
    temp_v0_6 = func_ovl13_01_8004B660(-1, 0x800000, 0x30, temp_v0_5);
    D_ovl13_01_8004C328 = temp_v0_6;
    var_s1 = temp_v0_6;
    temp_v0_6->unk4C = 0.0f;
    temp_v0_6->unk50 = 0.0f;
    M2C_FIELD(temp_v0_6, void **, 0x3C) = &D_ovl13_01_8004C2D8;
    temp_v0_6->unk54 = 5.0f;
    for (var_s0 = 0; var_s0 < 2; var_s0++) {
        temp_s3 = var_s1;
        var_s1 = D_ovl13_01_8004C330[var_s0] = func_ovl13_01_8004B660(var_s0 + 0x29E, 0x01000000, 0x30, var_s1);
        func_ovl13_01_8004B620(temp_s3, var_s1, &D_ovl13_01_8004C2C0, 0x150);
        var_s1->unk4C = 0.0f;
        var_s1->unk50 = 0.0f;
        var_s1->unk54 = 70.0f;
    }
    temp_v0_8 = func_ovl13_01_8004B660(0x29C, 0x01008010, 0x30, var_s1);
    D_ovl13_01_8004C31C = temp_v0_8;
    temp_v0_8->unk30 = 1;
    temp_v0_8->unk38 = 0.0f;
    temp_v0_8->unk4C = 0.0f;
    temp_v0_8->unk50 = 0.0f;
    temp_v0_8->unk54 = 70.0f;
    temp_v0_8->unkC = 0x7E42;
    temp_v0_8->unk34 = 50.0f;
    func_ovl13_01_8004B620(var_s1, temp_v0_8, &D_ovl13_01_8004C2C0, 0x150);
    func_ovl13_01_8004B608(temp_v0_8, 0x30);
    func_ovl13_01_8004B340(temp_v0_8->unk40, 2);
    func_ovl13_01_80046BB0();
    func_ovl13_01_8004306C(0);
    temp_v0_9 = func_ovl13_01_8004B660(-1, 0x400020, 0x30, temp_v0_8);
    D_ovl13_01_8004C360 = temp_v0_9;
    temp_v0_9->unk38 = 0.0f;
    temp_v0_9->unk4C = 0.0f;
    temp_v0_9->unk50 = 0.0f;
    temp_v0_9->unk54 = 125.0f;
    temp_v0_10 = func_ovl13_01_8004B660(-1, 0x400000, 0x30, D_ovl13_01_8004C338);
    D_ovl13_01_8004C33C = temp_v0_10;
    M2C_FIELD(temp_v0_10, void **, 0x3C) = &D_ovl13_01_8004C2F0;
    temp_v0_10->unk50 = -40.0f;
    temp_v0_10->unk4C = 0.0f;
    temp_v0_10->unk54 = -60.0f;
    temp_v0_11 = func_ovl13_01_8004B660(-1, 0x500000, 0x30, temp_v0_10);
    D_ovl13_01_8004C340 = temp_v0_11;
    var_s1_2 = temp_v0_11;
    temp_v0_11->unk50 = 0.0f;
    M2C_FIELD(temp_v0_11, void **, 0x3C) = &D_ovl13_01_8004C2F0;
    temp_v0_11->unk4C = 180.0f;
    temp_v0_11->unk54 = 5.0f;
    var_s3 = var_s1_2;
    for (var_s0 = 0; var_s0 < 3; var_s0++) {
        var_s1_2 = D_ovl13_01_8004C348[var_s0] = func_ovl13_01_8004B660(0x2A0, 0x01000000, 0x30, var_s1_2);
        func_ovl13_01_8004B620(var_s3, var_s1_2, &D_ovl13_01_8004C2F0, 0x150);
        var_s3 = var_s1_2;
    }
    temp_v0_13 = D_ovl13_01_8004C348[3] = func_ovl13_01_8004B660(0x2A1, 0x01008010, 0x30, var_s1_2);
    temp_v0_13->unk30 = 1;
    temp_v0_13->unk38 = 0.0f;
    temp_v0_13->unkC = 0x7E42;
    temp_v0_13->unk34 = 50.0f;
    func_ovl13_01_8004B620(var_s1_2, temp_v0_13, &D_ovl13_01_8004C308, 0x150);
    func_ovl13_01_8004B608(temp_v0_13, 0x30);
    func_ovl13_01_8004B340(temp_v0_13->unk40, 2);
    func_ovl13_01_800468F0();
}

void func_ovl13_01_800497DC(UnkStructA *arg0, s32 *arg1, s32 *arg2) {
    func_ovl13_01_8004BA40(arg0->unk4C, *arg1, (*arg2)++, 7);
    func_ovl13_01_8004BA40(arg0->unk50, *arg1, (*arg2)++, 7);
    func_ovl13_01_8004BA40(arg0->unk54, *arg1, (*arg2)++, 7);
}

void func_ovl13_01_8004956C(void) {
    s32 sp1C;
    s32 var_v0;

    func_ovl13_01_8004AE28(1);
    if (func_ovl13_01_8004BA10(0x420) == 0) {
        do {
            func_ovl13_01_8004B7D0();
        } while (func_ovl13_01_8004BA10(0x420) == 0);
    }
    func_ovl13_01_8004AE28(1);
    func_ovl13_01_8004ADA0(0);
    func_ovl13_01_8004AED8(1);
    if (func_ovl13_01_8004B9F0(0xA4) != 0) {
        func_ovl13_01_8004AE40("WM1 WAP WG1 WSH M1 M6 ST1");
        func_ovl13_01_8004B7A8(0x1E);
        func_ovl13_01_8004AE40("WM1 WAP WG1 WSH WDE WB2 ST1");
        var_v0 = 0;
        do {
            sp1C = var_v0;
            func_ovl13_01_8004AE40("WM1 WAP WG1 WSH WDW WB4 ST1 WDE WB4 ST1");
            var_v0 += 1;
        } while (var_v0 != 2);
        func_ovl13_01_8004AE40("WM1 WAP WG1 WSH WDW WB2 ST1");
        if (D_ovl13_01_8004C388.z < D_ovl13_01_8004C260.z) {
            func_ovl13_01_8004AE40("WM1 WAP WG1 WSH WDN WB0 ST1");
        } else {
            func_ovl13_01_8004AE40("WM1 WAP WG1 WSH WDS WB0 ST1");
        }
        func_ovl13_01_8004B7A8(0x3C);
        func_ovl13_01_8004AE40("WM1 WAP WG1 WSH M2 ST8 M4 ST1 WDW WB4 ST1 WDE WB0 ST1");
        func_ovl13_01_8004B7A8(0x78);
    } else {
        func_ovl13_01_8004B7A8(0x3C);
        func_ovl13_01_8004AE40("WM1 WAP WG1 WSL WDE WB1 ST1 WSM WDE WB2 ST1 WSH WDE WB3 ST1");
        func_ovl13_01_8004B7A8(0x3C);
        func_ovl13_01_8004AED8(0);
        func_ovl13_01_8004B7D0();
        func_ovl13_01_8004AE40("WM1 WAP WG1 WSH WDW WB20");
        func_ovl13_01_8004B7A8(0x78);
    }
    func_ovl13_01_8004BE88();
    func_ovl13_01_8004B798();
}

void func_ovl13_01_800491B4(UnkStructA *arg0, f32 *arg1) {
    f32 sp40;
    s32 sp34;
    UnkStructA *temp_v0;
    UnkStructA *var_a2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv1;
    s32 temp_ft2;
    s32 var_a1;

    temp_fv1 = arg1[2];
    arg1[1] = 0.0f;
    temp_fv0 = 1.0f - (temp_fv1 / 1000.0f);
    arg1[2] = (f32) (temp_fv1 * 0.01f);
    arg1[2] = (f32) (arg1[2] * (temp_fv0 * temp_fv0));
    func_ovl13_01_8004B708(arg0, &sp40);
    temp_fv0_2 = arg1[0] + 22.5f;
    if (temp_fv0_2 >= 360.0f) {
        var_fv1 = temp_fv0_2 - 360.0f;
    } else {
        if (temp_fv0_2 < 0.0f) {
            var_fa0 = temp_fv0_2 + 360.0f;
        } else {
            var_fa0 = temp_fv0_2;
        }
        var_fv1 = var_fa0;
    }
    temp_ft2 = (s32) (var_fv1 / 45.0f);
    var_a1 = temp_ft2;
    switch (temp_ft2) {
    case 0:
        var_a1 = 0x80;
        break;
    case 1:
        var_a1 = 0x60;
        break;
    case 2:
        var_a1 = 0x40;
        break;
    case 3:
        var_a1 = 0x20;
        break;
    case 4:
        var_a1 = 0;
        break;
    case 5:
        var_a1 = 0xE0;
        break;
    case 6:
        var_a1 = 0xC0;
        break;
    case 7:
        var_a1 = 0xA0;
        break;
    }
    func_ovl13_01_8004BC88(arg0, var_a1, arg1[2]);
    var_a2 = NULL;
    if (arg0->unk8 & 3) {
        temp_v0 = func_ovl13_01_8004AEB8(func_ovl13_01_8004AE18());
        var_a2 = temp_v0;
        if (arg0->unk8 & 2) {
            if (temp_v0 == arg0) {
                var_a2 = func_ovl13_01_8004AE78(func_ovl13_01_8004AE18());
            } else {
                var_a2 = NULL;
            }
        }
    }
    sp34 = arg0->unkC;
    arg0->unkC = 0;
    if (var_a2 != NULL) {
        if (func_ovl13_01_8004B758(arg0, 0x10, var_a2) != 0) {
            func_ovl13_01_8004B710((UnkStructA *) &sp40, arg0);
        }
    } else if (func_ovl13_01_8004B5E8(arg0, 0x10) != 0) {
        func_ovl13_01_8004B710((UnkStructA *) &sp40, arg0);
    }
    arg0->unkC = sp34;
}

void func_ovl13_01_800490DC(void) {
    void *sp1C;

    sp1C = func_ovl13_01_8004B7B0();
    if (func_ovl13_01_8004BA10(0x420) == 0) {
        do {
            func_ovl13_01_8004B7D0();
        } while (func_ovl13_01_8004BA10(0x420) == 0);
    }
    if (!(*D_ovl13_01_8004C23C & 2)) {
        func_ovl13_01_8004BD20((s32) sp1C);
    }
    func_ovl13_01_8004B798();
}

void func_ovl13_01_80048E2C(void) {
    Vec3f sp70;
    Vec3f sp60;
    UnkStructA *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    UnkStructA_40 *temp_v0_6;
    UnkStructA_40 *temp_v0_7;
    f32 *temp_v0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_ft3;
    s32 var_s0;

    temp_v0 = func_ovl13_01_8004B7B0();
    func_ovl13_01_8004B5C8(&D_ovl13_01_8004C388.x, temp_v0, &sp60.x);
    sp60.y = 0.0f;
    sp60.z *= 0.02f;
    if (func_ovl13_01_8004B948(1) != 0) {
        var_ft3 = (f32) ((f64) sp60.x + (20.0 * func_ovl13_01_8004B940()));
    } else {
        var_ft3 = (f32) ((f64) sp60.x + (-20.0 * func_ovl13_01_8004B940()));
    }
    sp60.x = var_ft3;
    func_ovl13_01_8004B5D0(&sp60.x, &sp70.x);
    temp_v0_2 = func_ovl13_01_8004B660(0x11D, 0x01080000, 0xD0, NULL);
    func_ovl13_01_8004B710((UnkStructA *) temp_v0, temp_v0_2);
    temp_v0_3 = temp_v0_2->unk40;
    temp_v0_3->unk14 = temp_v0_3->unk14;
    temp_v0_4 = temp_v0_2->unk40;
    temp_v0_4->unkC |= 0x8000;
    func_ovl13_01_8004B340(temp_v0_2->unk40, 1);
    func_ovl13_01_8004B348(temp_v0_2->unk40, 0x11E, 0, 0);
    temp_v0_2->unk40->unk30 = 1.0f;
    temp_v0_5 = temp_v0_2->unk40;
    temp_fv0 = temp_v0_5->unk30;
    temp_v0_5->unk2C = temp_fv0;
    var_s0 = 0;
    temp_v0_2->unk40->unk28 = temp_fv0;
    do {
        temp_fv0_2 = (f32) var_s0 / 30.0f;
        temp_v0_2->unk40->unk36 = (s16) (s32) ((1.0f - temp_fv0_2) * 255.0f);
        func_ovl13_01_8004B390(temp_v0_2->unk40, 0, (s32) (3.0f * temp_fv0_2));
        temp_v0_6 = temp_v0_2->unk40;
        temp_v0_6->unk10 += sp70.x;
        temp_v0_7 = temp_v0_2->unk40;
        temp_v0_7->unk18 += sp70.z;
        func_ovl13_01_8004B7D0();
        var_s0 += 1;
    } while (var_s0 != 0x1E);
    D_ovl13_01_8004C280 -= 1;
    func_ovl13_01_8004B650(temp_v0_2);
    func_ovl13_01_8004B798();
}

void func_ovl13_01_80048BB0(void) {
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;

    temp_v0 = func_ovl13_01_8004B7B0();
    temp_v0_2 = func_ovl13_01_8004B660(temp_v0->unk28, 0x400000, 0xD0, D_ovl13_01_8004C360);
    temp_v0_2->unk4C = 0.0f;
    temp_v0_2->unk50 = 0.0f;
    temp_v0_2->unk54 = -50.0f;
    temp_v1 = D_ovl13_01_8004C3BC;
    if (temp_v1 != 1) {
        do {
            temp_v0->unk40->unk10 = temp_v0_2->unk40->unk10;
            temp_v0->unk40->unk14 = temp_v0_2->unk40->unk14;
            temp_v0->unk40->unk18 = temp_v0_2->unk40->unk18;
            temp_v0->unk40->unk1C = temp_v0_2->unk40->unk1C + 90.0f;
            temp_v0->unk40->unk20 = temp_v0_2->unk40->unk20;
            temp_v0->unk40->unk24 = temp_v0_2->unk40->unk24;
            func_ovl13_01_8004B7D0();
        } while (D_ovl13_01_8004C3BC != 1);
    }
    if (temp_v1 != 0) {
        do {
            temp_v0->unk40->unk10 = temp_v0_2->unk40->unk10;
            temp_v0->unk40->unk14 = temp_v0_2->unk40->unk14;
            temp_v0->unk40->unk18 = temp_v0_2->unk40->unk18;
            temp_v0->unk40->unk1C = temp_v0_2->unk40->unk1C + 90.0f;
            temp_v0->unk40->unk20 = temp_v0_2->unk40->unk20;
            temp_v0->unk40->unk24 = temp_v0_2->unk40->unk24;
            func_ovl13_01_8004B7D0();
        } while (D_ovl13_01_8004C3BC != 0);
    }
    var_v0 = 0;
    if (temp_v0->unk40->unk14 <= func_ovl13_01_8004AC60()) {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        do {
            func_ovl13_01_8004B6B8(temp_v0);
            func_ovl13_01_8004B7D0();
            var_v0_2 = 0;
            if (temp_v0->unk40->unk14 <= func_ovl13_01_8004AC60()) {
                var_v0_2 = 1;
            }
        } while (var_v0_2 == 0);
    }
    if (temp_v0->unk8 & 1) {
        func_ovl13_01_8004BA08(0x41A);
    }
    func_ovl13_01_80048AF0(temp_v0);
    func_ovl13_01_8004B650(temp_v0_2);
    func_ovl13_01_8004B798();
}

void func_ovl13_01_80048AF0(UnkStructA *arg0) {
    UnkStructA_40 *temp_v0;
    s16 temp_v1;
    s32 var_s0;

    func_ovl13_01_8004B638(arg0, 0x80000);
    var_s0 = 0;
    do {
        func_ovl13_01_8004B6B8(arg0);
        temp_v0 = arg0->unk40;
        temp_v1 = temp_v0->unk36 - 4;
        if (temp_v1 >= 0) {
            temp_v0->unk36 = temp_v1;
        }
        func_ovl13_01_8004B7D0();
        var_s0 += 1;
    } while (var_s0 != 0x3C);
}

void func_ovl13_01_80048418(void) {
    s32 i;
    UnkStructA_40_48_4 *temp_v0;
    f32 temp_fv0;
    f32 var_fv1;

loop_1:
    func_ovl13_01_800481D0();
    func_ovl13_01_80046800();
    func_ovl13_01_800477C0();
    func_ovl13_01_800475EC(D_ovl13_01_8004C324, 60.0f, 45.0f, -70.0f);
    func_ovl13_01_800475EC(D_ovl13_01_8004C328, 60.0f, 45.0f, -70.0f);
    for (i = 0; i < 2; i++) {
        func_ovl13_01_800475EC(D_ovl13_01_8004C330[i], 60.0f, 45.0f, -70.0f);
    }
    func_ovl13_01_800475EC(D_ovl13_01_8004C31C, 60.0f, 45.0f, -70.0f);
    func_ovl13_01_80047570();
    D_ovl13_01_8004C398.x = D_ovl13_01_8004C388.x;
    D_ovl13_01_8004C398.y = (f32) D_ovl13_01_8004C388.y;
    D_ovl13_01_8004C398.z = (f32) D_ovl13_01_8004C388.z;
    func_ovl13_01_800473A8();
    temp_fv0 = func_ovl13_01_8004B378(D_ovl13_01_8004C338->unk40, 0);
    temp_v0 = D_ovl13_01_8004C338->unk40->unk48->unk4;
    var_fv1 = temp_v0->unk4;
    if (temp_fv0 <= var_fv1) {
        var_fv1 -= temp_fv0;
    } else if (var_fv1 < 0.0f) {
        var_fv1 += temp_fv0;
    }
    temp_v0->unk4 = var_fv1;
    func_ovl13_01_8004B7D0();
    goto loop_1;
}

void func_ovl13_01_800473A8(void) {
    f32 sp1C;

    func_ovl13_01_800496E0(D_ovl13_01_8004C338, &D_ovl13_01_8004C28C, &D_ovl13_01_8004BF34, NULL);
    func_ovl13_01_800496E0(D_ovl13_01_8004C358, &D_ovl13_01_8004C290, &D_ovl13_01_8004BF38, func_ovl13_01_80046A50);
    func_ovl13_01_800496E0(D_ovl13_01_8004C35C, &D_ovl13_01_8004C294, &D_ovl13_01_8004BF3C, func_ovl13_01_80046940);
    func_ovl13_01_800496E0(D_ovl13_01_8004C31C, &D_ovl13_01_8004C298, &D_ovl13_01_8004BF40, func_ovl13_01_80046B60);
    func_ovl13_01_800496E0(D_ovl13_01_8004C348[3], &D_ovl13_01_8004C29C, &D_ovl13_01_8004BF44, func_ovl13_01_800468A0);
    if ((func_ovl13_01_8004BA10(0x41E) == 0) && (D_ovl13_01_8004C290 == 0)) {
        func_ovl13_01_8004BA00(0x41E);
        func_ovl13_01_8004B708(D_ovl13_01_8004C358, &sp1C);
        func_ovl13_01_8004B9B8(&sp1C);
    }
    if ((func_ovl13_01_8004BA10(0x41D) == 0) && (D_ovl13_01_8004C294 == 0)) {
        func_ovl13_01_8004BA00(0x41D);
        func_ovl13_01_8004B708(D_ovl13_01_8004C35C, &sp1C);
        func_ovl13_01_8004B9B8(&sp1C);
    }
    if ((func_ovl13_01_8004BA10(0x41C) == 0) && (D_ovl13_01_8004C298 == 0)) {
        func_ovl13_01_8004BA00(0x41C);
        func_ovl13_01_8004B708(D_ovl13_01_8004C31C, &sp1C);
        func_ovl13_01_8004B9B8(&sp1C);
    }
    if (func_ovl13_01_8004BA10(0x41B) == 0) {
        if (D_ovl13_01_8004C29C == 0) {
            func_ovl13_01_8004BA00(0x41B);
            func_ovl13_01_8004B708(D_ovl13_01_8004C348[3], &sp1C);
            func_ovl13_01_8004B9B8(&sp1C);
        }
    }
}

void func_ovl13_01_800496E0(UnkStructA *arg0, s32 *arg1, s32 *arg2, void (*arg3)()) {
    s32 sp24;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;
    s32 var_v1;

    if (*arg1 != 0) {
        temp_v0 = *arg2;
        if (temp_v0 == 0) {
            temp_v0_2 = func_ovl13_01_80046DC4(arg0);
            var_v1 = temp_v0_2;
            if (temp_v0_2 != 0) {
                if (arg0 == D_ovl13_01_8004C338) {
                    sp24 = temp_v0_2;
                    func_ovl13_01_80043124(0xC0, D_ovl13_01_8004C31C);
                    var_v1 = sp24;
                }
                var_v0 = *arg1 - var_v1;
                *arg1 = var_v0;
                if (var_v0 < 0) {
                    *arg1 = 0;
                    var_v0 = 0;
                }
                if ((var_v0 == 0) && (arg3 != NULL)) {
                    arg3();
                }
                func_ovl13_01_8004B788(func_ovl13_01_80046C2C, arg0, 0, 0, 0x150);
                *arg2 = 0x78;
            }
        } else {
            *arg2 = temp_v0 - 1;
        }
    }
}

void func_ovl13_01_80048B6C(UnkStructA *arg0) {
    if (arg0->unk8 & 1) {
        func_ovl13_01_8004BA08(0x41A);
    }
    func_ovl13_01_80048AF0(arg0);
}

void func_ovl13_01_8004899C(void) {
    func_ovl13_01_80043F88(0);
    if (func_ovl13_01_8004BA10(0x420) == 0) {
        do {
            func_ovl13_01_8004B7D0();
        } while (func_ovl13_01_8004BA10(0x420) == 0);
    }
    if ((*D_ovl13_01_8004C23C & 2) && (func_ovl13_01_8004B9F0(0xA4) != 0)) {
        func_ovl13_01_800450B4(0x78);
    }
    if (D_ovl13_01_8004C28C != 0) {
        do {
            func_ovl13_01_8004874C();
            func_ovl13_01_800486B8(D_ovl13_01_8004C3C8, D_ovl13_01_8004C3CC);
            if ((func_ovl13_01_80043830() >= 2) && (D_ovl13_01_8004C28C > 0)) {
                func_ovl13_01_80044160(1);
            }
        } while (D_ovl13_01_8004C28C != 0);
    }
    func_ovl13_01_80045538();
    func_ovl13_01_8004BA08(0x41A);
    D_ovl13_01_8004C240.x = 0.0f;
    D_ovl13_01_8004C240.y = 0.0f;
    D_ovl13_01_8004C240.z = 0.0f;
    func_ovl13_01_8004B518(&D_ovl13_01_8004C240.x);
    func_ovl13_01_8004ADB0(1);
    func_ovl13_01_8004863C();
    func_ovl13_01_8004AD58();
    func_ovl13_01_8004B798();
}

void func_ovl13_01_8004874C(void) {
    u32 sp24;
    u32 temp_v0;

    if (D_ovl13_01_8004C3C8 != 2) {
        D_ovl13_01_8004BF30 = D_ovl13_01_8004C3C8;
        D_ovl13_01_8004C3C8 = 2;
        D_ovl13_01_8004C3CC = func_ovl13_01_8004B948(0xF0) + 0x3C;
    } else {
        temp_v0 = func_ovl13_01_8004B948(0xA);
        sp24 = temp_v0;
        switch (temp_v0) {
        case 0:
            if (D_ovl13_01_8004BF30 != 3) {
                D_ovl13_01_8004C3C8 = 3;
                D_ovl13_01_8004C3CC = 0;
            } else if (func_ovl13_01_8004B948(1) != 0) {
                D_ovl13_01_8004C3C8 = 1;
                D_ovl13_01_8004C3CC = 0;
            } else {
                D_ovl13_01_8004C3C8 = 0;
                D_ovl13_01_8004C3CC = 0x3C;
            }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            D_ovl13_01_8004C3C8 = 1;
            D_ovl13_01_8004C3CC = 0;
            break;
        default:
            D_ovl13_01_8004C3C8 = 0;
            D_ovl13_01_8004C3CC = 0x3C;
            break;
        }
        if ((func_ovl13_01_8004BA10(0x41F) != 0) && (sp24 == 1)) {
            D_ovl13_01_8004C3C8 = 3;
            D_ovl13_01_8004C3CC = 0;
        }
    }
    if (func_ovl13_01_8004BA10(0x41B) == 0) {
        if ((((f32) M2C_FIELD(D_ovl13_01_8004C23C, s32 *, 0x30) / (f32) M2C_FIELD(D_ovl13_01_8004C23C, s32 *, 0x28)) >= 0.5f) && (func_ovl13_01_8004BA10(0x412) == 0)) {
            D_ovl13_01_8004C3C8 = 3;
            D_ovl13_01_8004C3CC = 0;
            func_ovl13_01_8004BA00(0x412);
        }
        if ((((f32) M2C_FIELD(D_ovl13_01_8004C23C, s32 *, 0x30) / (f32) M2C_FIELD(D_ovl13_01_8004C23C, s32 *, 0x28)) >= 0.75f) && (func_ovl13_01_8004BA10(0x411) == 0)) {
            D_ovl13_01_8004C3C8 = 3;
            D_ovl13_01_8004C3CC = 0;
            func_ovl13_01_8004BA00(0x411);
        }
    }
    if (M2C_FIELD(D_ovl13_01_8004C23C, s32 *, 0) & 2) {
        if (func_ovl13_01_8004B9F0(0xA4) != 0) {
            D_ovl13_01_8004C3C8 = 1;
            D_ovl13_01_8004C3CC = 0;
        } else {
            D_ovl13_01_8004C3C8 = 0;
            D_ovl13_01_8004C3CC = 0x3C;
        }
    }
}

void func_ovl13_01_800486B8(u32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
        func_ovl13_01_800455D0(arg1);
        return;
    case 2:
        func_ovl13_01_800450B4(arg1);
        return;
    case 3:
        func_ovl13_01_800446FC();
        return;
    case 1:
        func_ovl13_01_80043878();
        return;
    case 5:
        func_ovl13_01_80045538();
        return;
    default:
        func_ovl13_01_8004B7D0();
        return;
    }
}

void func_ovl13_01_8004863C(void) {
    s32 var_s0;

    var_s0 = 0;
    if (func_ovl13_01_8004BA10(0x41E) != 0) {
        var_s0 = 1;
    }
    if (func_ovl13_01_8004BA10(0x41D) != 0) {
        var_s0 += 1;
    }
    if (func_ovl13_01_8004BA10(0x41C) != 0) {
        var_s0 += 1;
    }
    if (func_ovl13_01_8004BA10(0x41B) != 0) {
        var_s0 += 1;
    }
    M2C_FIELD(D_ovl13_01_8004C23C, s32 *, 0x2C) = var_s0;
}

void func_ovl13_01_800481D0(void) {
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;

    switch (D_ovl13_01_8004C2AC) {                  /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        break;
    case 1:                                         /* switch 1 */
        func_ovl13_01_80046FA8(&D_ovl13_01_8004C200.x);
        break;
    case 2:                                         /* switch 1 */
        func_ovl13_01_80046FA8(&D_ovl13_01_8004C2B0.x);
        break;
    }
    if (func_ovl13_01_8004BA10(0x417) != 0) {
        D_ovl13_01_8004C338->unk40->unk14 = D_ovl13_01_8004C388.y;
        func_ovl13_01_8004B6B8(D_ovl13_01_8004C338);
        D_ovl13_01_8004C388.y = D_ovl13_01_8004C338->unk40->unk14;
    }
    func_ovl13_01_8004B710((UnkStructA *) &D_ovl13_01_8004C388.x, D_ovl13_01_8004C338);
    switch (D_ovl13_01_8004C3B4) {                  /* switch 2; irregular */
    case 2:                                         /* switch 2 */
    case 3:                                         /* switch 2 */
        break;
    case 0:                                         /* switch 2 */
        func_ovl13_01_80045C9C();
        func_ovl13_01_80047144();
        func_ovl13_01_80047F74();
        break;
    case 1:                                         /* switch 2 */
        func_ovl13_01_80046E00();
        break;
    }
    if (D_ovl13_01_8004C3A8.y >= 360.0f) {
        D_ovl13_01_8004C3A8.y = (f32) (D_ovl13_01_8004C3A8.y - 360.0f);
    } else {
        if (D_ovl13_01_8004C3A8.y < 0.0f) {
            var_fv1 = D_ovl13_01_8004C3A8.y + 360.0f;
        } else {
            var_fv1 = D_ovl13_01_8004C3A8.y;
        }
        D_ovl13_01_8004C3A8.y = var_fv1;
    }
    if (D_ovl13_01_8004C3A8.x >= 360.0f) {
        D_ovl13_01_8004C3A8.x -= 360.0f;
    } else {
        if (D_ovl13_01_8004C3A8.x < 0.0f) {
            var_fv1_2 = D_ovl13_01_8004C3A8.x + 360.0f;
        } else {
            var_fv1_2 = D_ovl13_01_8004C3A8.x;
        }
        D_ovl13_01_8004C3A8.x = var_fv1_2;
    }
    if (D_ovl13_01_8004C3A8.z >= 360.0f) {
        D_ovl13_01_8004C3A8.z = (f32) (D_ovl13_01_8004C3A8.z - 360.0f);
    } else {
        if (D_ovl13_01_8004C3A8.z < 0.0f) {
            var_fv1_3 = D_ovl13_01_8004C3A8.z + 360.0f;
        } else {
            var_fv1_3 = D_ovl13_01_8004C3A8.z;
        }
        D_ovl13_01_8004C3A8.z = var_fv1_3;
    }
    D_ovl13_01_8004C338->unk40->unk1C = D_ovl13_01_8004C3A8.y;
    D_ovl13_01_8004C338->unk40->unk20 = D_ovl13_01_8004C3A8.x;
    D_ovl13_01_8004C338->unk40->unk24 = D_ovl13_01_8004C3A8.z;
}

void func_ovl13_01_80047F74(void) {
    Vec3f sp3C;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fa1;
    f32 var_fv1;
    f32 var_fv1_2;

    if (func_ovl13_01_8004BA10(0x414) != 0) {
        func_ovl13_01_8004B5C8(&D_ovl13_01_8004C398.x, &D_ovl13_01_8004C388.x, &sp3C.x);
        if (sp3C.x >= 0.0f) {
            if (sp3C.x <= 180.0f) {
                var_fa0 = sp3C.x;
            } else {
                goto block_5;
            }
        } else {
block_5:
            var_fa0 = (360.0f - sp3C.x) * -1.0f;
        }
        if (D_ovl13_01_8004C3A8.x >= 0.0f) {
            if (D_ovl13_01_8004C3A8.x <= 180.0f) {
                var_fv1 = D_ovl13_01_8004C3A8.x;
            } else {
                goto block_10;
            }
        } else {
block_10:
            var_fv1 = (360.0f - D_ovl13_01_8004C3A8.x) * -1.0f;
        }
        if (sp3C.z <= 1.0f) {
            var_fa0_2 = -30.0f;
            sp3C.y = 0.0f;
        } else {
            temp_fv0 = var_fa0 - var_fv1;
            sp3C.y -= 90.0f;
            if (temp_fv0 <= 90.0f) {
                if (temp_fv0 >= -90.0f) {
                    var_fa0_2 = 0.0f;
                } else {
                    goto block_17;
                }
            } else {
block_17:
                var_fa0_2 = -60.0f;
            }
        }
        if (D_ovl13_01_8004C3A8.y >= 0.0f) {
            if (D_ovl13_01_8004C3A8.y <= 180.0f) {
                var_fv1_2 = D_ovl13_01_8004C3A8.y;
            } else {
                goto block_22;
            }
        } else {
block_22:
            var_fv1_2 = (360.0f - D_ovl13_01_8004C3A8.y) * -1.0f;
        }
        temp_fv0_2 = var_fa0_2 - var_fv1_2;
        var_fa1 = temp_fv0_2;
        if (var_fv1_2 <= var_fa0_2) {
            if (temp_fv0_2 > 3.0f) {
                var_fa1 = 3.0f;
            } else if (temp_fv0_2 <= 0.05f) {
                goto block_31;
            }
        } else if (temp_fv0_2 < -3.0f) {
            var_fa1 = -3.0f;
        } else if (temp_fv0_2 >= -0.05f) {
block_31:
            var_fa1 = 0.0f;
        }
        D_ovl13_01_8004C3A8.y = (f32) (D_ovl13_01_8004C3A8.y + var_fa1);
        func_ovl13_01_80047CB4(&sp3C.x);
    }
}

void func_ovl13_01_80047CB4(void *arg0) {
    f32 sp34;
    f32 sp1C;
    UnkStructA_40 *var_a0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv1;

    if (func_ovl13_01_8004BA10(0x413) != 0) {
        var_a0 = D_ovl13_01_8004C338->unk40;
        temp_fv0 = M2C_FIELD(arg0, f32 *, 4);
        temp_fv1 = var_a0->unk48->unk4->unk4;
        if (temp_fv0 >= 0.0f) {
            if (temp_fv0 > 67.5f) {
                if (temp_fv1 <= 45.0f) {
                    if ((temp_fv1 + 2.0f) > 45.0f) {
                        sp34 = temp_fv1;
                        func_ovl13_01_80043124(0xD4, D_ovl13_01_8004C338);
                        var_a0 = D_ovl13_01_8004C338->unk40;
                    }
                }
                var_fv1 = temp_fv1 + 2.0f;
            } else {
                if (temp_fv1 <= 48.0f) {
                    if ((temp_fv1 + 1.0f) > 48.0f) {
                        sp34 = temp_fv1;
                        func_ovl13_01_80043124(0xD3, D_ovl13_01_8004C338);
                        var_a0 = D_ovl13_01_8004C338->unk40;
                    }
                }
                var_fv1 = temp_fv1 + 1.0f;
            }
        } else if (temp_fv0 < -10.0f) {
            if (temp_fv1 <= 40.0f) {
                if ((temp_fv1 + 1.0f) >= 40.0f) {
                    var_fv1 = 40.0f;
                } else {
                    goto block_18;
                }
            } else {
block_18:
                temp_fv0_2 = temp_fv1 + 1.0f;
                if ((temp_fv1 <= 48.0f) && (temp_fv0_2 > 48.0f)) {
                    sp1C = temp_fv0_2;
                    func_ovl13_01_80043124(0xD3, D_ovl13_01_8004C338);
                    var_a0 = D_ovl13_01_8004C338->unk40;
                }
                var_fv1 = temp_fv0_2;
            }
        } else {
            if (temp_fv1 <= 48.0f) {
                if ((temp_fv1 + 1.0f) > 48.0f) {
                    sp34 = temp_fv1;
                    func_ovl13_01_80043124(0xD3, D_ovl13_01_8004C338);
                    var_a0 = D_ovl13_01_8004C338->unk40;
                }
            }
            var_fv1 = temp_fv1 + 1.0f;
        }
        sp34 = var_fv1;
        temp_fv0_3 = func_ovl13_01_8004B378(var_a0, 0);
        var_fa0 = var_fv1;
        if (temp_fv0_3 <= var_fv1) {
            var_fa0 = var_fv1 - temp_fv0_3;
        } else if (var_fv1 < 0.0f) {
            var_fa0 = var_fv1 + temp_fv0_3;
        }
        D_ovl13_01_8004C338->unk40->unk48->unk4->unk4 = var_fa0;
    }
}

void func_ovl13_01_800477C0(void) {
    f32 sp58;
    f32 sp54;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 temp_ft4;
    f32 temp_ft4_2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv0_7;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fa1;
    f32 var_fa1_2;
    f32 var_ft3;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    f32 var_fv1_4;
    f32 var_fv1_5;
    f32 var_fv1_6;

    switch (D_ovl13_01_8004C2A0) {                  /* irregular */
    case 0:
        sp58 = 0.0f;
        sp54 = D_ovl13_01_8004C324->unk40->unk20;
        break;
    case 1:
        func_ovl13_01_8004B708(D_ovl13_01_8004C324, &sp3C);
        sp30 = D_ovl13_01_8004C200.x;
        if (D_ovl13_01_8004C3C8 == 0) {
            var_ft3 = D_ovl13_01_8004C200.y;
            goto block_11;
        }
        if (D_ovl13_01_8004C3C8 == 1) {
            sp34 = D_ovl13_01_8004C200.y;
        } else {
            var_ft3 = D_ovl13_01_8004C200.y + 51.0f;
block_11:
            sp34 = var_ft3;
        }
        sp38 = D_ovl13_01_8004C200.z;
        func_ovl13_01_8004B5C8(&sp3C, &sp30, &sp54);
        temp_fv0 = (sp58 - 90.0f) + -7.5f;
        if (temp_fv0 >= 360.0f) {
            sp58 = temp_fv0 - 360.0f;
        } else {
            if (temp_fv0 < 0.0f) {
                var_fv1 = temp_fv0 + 360.0f;
            } else {
                var_fv1 = temp_fv0;
            }
            sp58 = var_fv1;
        }
        break;
    case 2:
        sp54 = D_ovl13_01_8004C324->unk40->unk20;
        sp58 = D_ovl13_01_8004C324->unk40->unk1C;
        break;
    }
    temp_fv0_2 = D_ovl13_01_8004C324->unk40->unk20;
    if (temp_fv0_2 >= 0.0f) {
        if (temp_fv0_2 <= 180.0f) {
            var_fv1_2 = temp_fv0_2;
        } else {
            goto block_24;
        }
    } else {
block_24:
        var_fv1_2 = (360.0f - temp_fv0_2) * -1.0f;
    }
    temp_fv0_3 = sp54 - var_fv1_2;
    if (temp_fv0_3 >= 0.0f) {
        if (temp_fv0_3 <= 180.0f) {
            var_fa1 = temp_fv0_3;
            sp54 = temp_fv0_3;
        } else {
            goto block_29;
        }
    } else {
block_29:
        sp54 = temp_fv0_3;
        var_fa1 = (360.0f - temp_fv0_3) * -1.0f;
    }
    temp_ft4 = D_ovl13_01_8004C328->unk4C;
    if (temp_ft4 >= 0.0f) {
        if (temp_ft4 <= 180.0f) {
            var_fv1_3 = temp_ft4;
        } else {
            goto block_34;
        }
    } else {
block_34:
        var_fv1_3 = (360.0f - temp_ft4) * -1.0f;
    }
    temp_fv0_4 = var_fa1 - var_fv1_3;
    var_fa0 = temp_fv0_4;
    if (temp_fv0_4 > 180.0f) {
        var_fa0 = temp_fv0_4 - 360.0f;
    }
    if (var_fa0 < -180.0f) {
        var_fa0 += 360.0f;
    }
    if (var_fa0 >= 0.0f) {
        var_fv0 = D_ovl13_01_8004C2A4;
        if (var_fv0 < var_fa0) {
            goto block_43;
        }
    } else {
        var_fv0 = D_ovl13_01_8004C2A4 * -1.0f;
        if (var_fa0 < var_fv0) {
block_43:
            var_fa0 = var_fv0;
        }
    }
    temp_fv0_5 = temp_ft4 + var_fa0;
    if (temp_fv0_5 >= 360.0f) {
        D_ovl13_01_8004C328->unk4C = temp_fv0_5 - 360.0f;
    } else {
        if (temp_fv0_5 < 0.0f) {
            var_fv1_4 = temp_fv0_5 + 360.0f;
        } else {
            var_fv1_4 = temp_fv0_5;
        }
        D_ovl13_01_8004C328->unk4C = var_fv1_4;
    }
    if (sp58 >= 0.0f) {
        if (sp58 <= 180.0f) {
            var_fa1_2 = sp58;
        } else {
            goto block_54;
        }
    } else {
block_54:
        var_fa1_2 = (360.0f - sp58) * -1.0f;
    }
    temp_ft4_2 = D_ovl13_01_8004C328->unk50;
    if (temp_ft4_2 >= 0.0f) {
        if (temp_ft4_2 <= 180.0f) {
            var_fv1_5 = temp_ft4_2;
        } else {
            goto block_59;
        }
    } else {
block_59:
        var_fv1_5 = (360.0f - temp_ft4_2) * -1.0f;
    }
    temp_fv0_6 = var_fa1_2 - var_fv1_5;
    var_fa0_2 = temp_fv0_6;
    if (temp_fv0_6 > 180.0f) {
        var_fa0_2 = temp_fv0_6 - 360.0f;
    }
    if (var_fa0_2 < -180.0f) {
        var_fa0_2 += 360.0f;
    }
    if (var_fa0_2 >= 0.0f) {
        var_fv0_2 = D_ovl13_01_8004C2A4;
        if (var_fv0_2 < var_fa0_2) {
            goto block_68;
        }
    } else {
        var_fv0_2 = D_ovl13_01_8004C2A4 * -1.0f;
        if (var_fa0_2 < var_fv0_2) {
block_68:
            var_fa0_2 = var_fv0_2;
        }
    }
    temp_fv0_7 = temp_ft4_2 + var_fa0_2;
    if (temp_fv0_7 >= 360.0f) {
        D_ovl13_01_8004C328->unk50 = temp_fv0_7 - 360.0f;
        return;
    }
    if (temp_fv0_7 < 0.0f) {
        var_fv1_6 = temp_fv0_7 + 360.0f;
    } else {
        var_fv1_6 = temp_fv0_7;
    }
    D_ovl13_01_8004C328->unk50 = var_fv1_6;
}

void func_ovl13_01_800475EC(UnkStructA *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 var_fv1;
    f32 var_fv1_2;

    temp_fv0 = arg0->unk4C;
    if (temp_fv0 >= 0.0f) {
        if (temp_fv0 <= 180.0f) {
            arg0->unk4C = temp_fv0;
        } else {
            goto block_4;
        }
    } else {
block_4:
        arg0->unk4C = (360.0f - temp_fv0) * -1.0f;
    }
    temp_fv0_2 = arg0->unk50;
    if (temp_fv0_2 >= 0.0f) {
        if (temp_fv0_2 <= 180.0f) {
            arg0->unk50 = temp_fv0_2;
        } else {
            goto block_9;
        }
    } else {
block_9:
        arg0->unk50 = (360.0f - temp_fv0_2) * -1.0f;
    }
    temp_fv1 = arg1 * -1.0f;
    if (arg1 < arg0->unk4C) {
        arg0->unk4C = arg1;
    }
    if (arg0->unk4C < temp_fv1) {
        arg0->unk4C = temp_fv1;
    }
    if (arg2 < arg0->unk50) {
        arg0->unk50 = arg2;
    }
    if (arg0->unk50 < arg3) {
        arg0->unk50 = arg3;
    }
    temp_fv0_3 = arg0->unk4C;
    if (temp_fv0_3 >= 360.0f) {
        arg0->unk4C = temp_fv0_3 - 360.0f;
    } else {
        if (temp_fv0_3 < 0.0f) {
            var_fv1 = temp_fv0_3 + 360.0f;
        } else {
            var_fv1 = temp_fv0_3;
        }
        arg0->unk4C = var_fv1;
    }
    temp_fv0_4 = arg0->unk50;
    if (temp_fv0_4 >= 360.0f) {
        arg0->unk50 = temp_fv0_4 - 360.0f;
        return;
    }
    if (temp_fv0_4 < 0.0f) {
        var_fv1_2 = temp_fv0_4 + 360.0f;
    } else {
        var_fv1_2 = temp_fv0_4;
    }
    arg0->unk50 = var_fv1_2;
}

void func_ovl13_01_80047570(void) {
    f32 var_fa0;
    f32 var_fv0;

    var_fv0 = D_ovl13_01_8004C2BC - D_ovl13_01_8004C2C0.unkC;
    if (var_fv0 >= 0.0f) {
        var_fa0 = 0.05f;
        if (var_fv0 > 0.05f) {
            goto block_4;
        }
    } else {
        var_fa0 = -0.05f;
        if (var_fv0 < -0.05f) {
block_4:
            var_fv0 = var_fa0;
        }
    }
    D_ovl13_01_8004C2C0.unkC = (f32) (D_ovl13_01_8004C2C0.unkC + var_fv0);
}

void func_ovl13_01_800471D8(void) {
    Vec3f sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    UnkStructA *temp_s6;
    UnkStructA_40 *temp_v0;
    f32 temp_fv1;
    s32 var_s0;

    func_ovl13_01_8004B708(func_ovl13_01_8004B7B0(), &sp64.x);
    sp64.y += 100.0f;
    temp_s6 = func_ovl13_01_8004B660(0x306, 0x01000000, 0xD0, NULL);
    temp_s6->unk40->unk1C = (f32) (func_ovl13_01_8004B940() * 360.0);
    temp_s6->unk40->unk20 = (f32) (func_ovl13_01_8004B940() * 360.0);
    temp_s6->unk40->unk24 = (f32) (func_ovl13_01_8004B940() * 360.0);
    temp_s6->unk40->unk30 = 0.3f;
    temp_v0 = temp_s6->unk40;
    temp_fv1 = temp_v0->unk30;
    temp_v0->unk2C = temp_fv1;
    temp_s6->unk40->unk28 = temp_fv1;
    sp58 = (f32) (func_ovl13_01_8004B940() * 360.0);
    sp54 = 10.0f;
    sp5C = 40.0f;
    sp60 = 0.0f;
    sp50 = (10.0f / 60.0f) * -1.0f;
    func_ovl13_01_8004BD30(0xDC, sp64.x, sp64.y, sp64.z);
    var_s0 = 0;
    do {
        func_ovl13_01_8004377C(&sp64.x, &sp58, &sp54, &sp50);
        func_ovl13_01_8004B710((UnkStructA *) &sp64.x, temp_s6);
        func_ovl13_01_8004B7D0();
        var_s0 += 1;
    } while (var_s0 != 0x3C);
    func_ovl13_01_8004B650(temp_s6);
    func_ovl13_01_8004B798();
}

void func_ovl13_01_80047144(void) {
    f32 sp18;
    UnkStructA_40 *temp_a0;
    f32 temp_fv1;

    temp_a0 = D_ovl13_01_8004C338->unk40;
    sp18 = temp_a0->unk48->unk4->unk4;
    temp_fv1 = func_ovl13_01_8004B930(360.0f * (1.0f - (sp18 / func_ovl13_01_8004B378(temp_a0, 0)))) * 300.0f;
    D_ovl13_01_8004C35C->unk50 = temp_fv1;
    D_ovl13_01_8004C358->unk50 = temp_fv1;
}

void func_ovl13_01_80046FA8(f32 *arg0) {
    Vec3f sp34;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1;

    sp34.z = 0.0f;
    sp34.y = 0.0f;
    sp34.x = 0.0f;
    func_ovl13_01_8004B5C8(&D_ovl13_01_8004C388.x, arg0, &sp34.x);
    if (sp34.x >= 0.0f) {
        if (sp34.x <= 180.0f) {
            var_ft4 = sp34.x;
        } else {
            goto block_4;
        }
    } else {
block_4:
        var_ft4 = (360.0f - sp34.x) * -1.0f;
    }
    if (D_ovl13_01_8004C3A8.x >= 0.0f) {
        if (D_ovl13_01_8004C3A8.x <= 180.0f) {
            var_fa0 = D_ovl13_01_8004C3A8.x;
        } else {
            goto block_9;
        }
    } else {
block_9:
        var_fa0 = (360.0f - D_ovl13_01_8004C3A8.x) * -1.0f;
    }
    temp_fv1 = var_ft4 - var_fa0;
    var_fv0 = temp_fv1;
    if (temp_fv1 >= 180.0f) {
        var_fv0 = temp_fv1 - 360.0f;
    }
    if (var_fv0 < -180.0f) {
        var_fv0 += 360.0f;
    }
    if (var_fv0 >= 0.0f) {
        var_fv1 = D_ovl13_01_8004C2A8;
        if (var_fv1 < var_fv0) {
            goto block_18;
        }
    } else {
        var_fv1 = D_ovl13_01_8004C2A8 * -1.0f;
        if (var_fv0 < var_fv1) {
block_18:
            var_fv0 = var_fv1;
        }
    }
    D_ovl13_01_8004C3A8.x += var_fv0;
}

void func_ovl13_01_80046E00(void) {
    Vec3f sp34;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_ft5;
    f32 var_fv1;
    f32 var_fv1_2;

    if (func_ovl13_01_8004BA10(0x414) != 0) {
        func_ovl13_01_8004B5C8(&D_ovl13_01_8004C398.x, &D_ovl13_01_8004C388.x, &sp34.x);
        if (sp34.z <= 1.0f) {
            var_ft5 = D_ovl13_01_8004C3A8.y * -1.0f;
        } else {
            temp_fv0 = sp34.y - 90.0f;
            if (temp_fv0 >= 360.0f) {
                var_ft5 = temp_fv0 - 360.0f;
            } else {
                if (sp34.y < 90.0f) {
                    var_fv1 = temp_fv0 + 360.0f;
                } else {
                    var_fv1 = temp_fv0;
                }
                var_ft5 = var_fv1;
            }
        }
        if (sp34.x >= 0.0f) {
            if (sp34.x <= 180.0f) {
                var_fa0 = sp34.x;
            } else {
                goto block_13;
            }
        } else {
block_13:
            var_fa0 = (360.0f - sp34.x) * -1.0f;
        }
        if (D_ovl13_01_8004C3A8.x >= 0.0f) {
            if (D_ovl13_01_8004C3A8.x <= 180.0f) {
                var_fv1_2 = D_ovl13_01_8004C3A8.x;
            } else {
                goto block_18;
            }
        } else {
block_18:
            var_fv1_2 = (360.0f - D_ovl13_01_8004C3A8.x) * -1.0f;
        }
        temp_fv0 = var_fa0 - var_fv1_2;
        if ((temp_fv0 > 10.0f) || (temp_fv0 < -10.0f)) {
        }
        D_ovl13_01_8004C3A8.x = sp34.x;
        D_ovl13_01_8004C3A8.y = (f32) (var_ft5 * -1.0f);
    }
}

s32 func_ovl13_01_80046DC4(UnkStructA *arg0) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = arg0->unk10;
    var_v1 = 0;
    if (temp_v0 & 0x40) {
        var_v1 = 1;
        if (temp_v0 & 0x2000) {
            var_v1 = 2;
        }
        if (temp_v0 & 0x4000) {
            return var_v1 + 1;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return var_v1;
    }
    return var_v1;
}

void func_ovl13_01_80046C2C(void) {
    Vec3f sp50;
    s32 sp48;
    s32 var_s0;
    s32 var_s4;
    void *temp_v0;

    temp_v0 = func_ovl13_01_8004B7B0();
    if (temp_v0 == D_ovl13_01_8004C338) {
        sp48 = D_ovl13_01_8004C28C;
    }
    var_s4 = sp48;
    if (temp_v0 == D_ovl13_01_8004C358) {
        var_s4 = D_ovl13_01_8004C290;
    }
    if (temp_v0 == D_ovl13_01_8004C35C) {
        var_s4 = D_ovl13_01_8004C294;
    }
    var_s0 = 0;
    if (temp_v0 == D_ovl13_01_8004C31C) {
        var_s4 = D_ovl13_01_8004C298;
    }
    if (temp_v0 == D_ovl13_01_8004C348[3]) {
        var_s4 = D_ovl13_01_8004C29C;
    }
    do {
        sp50.x = func_ovl13_01_8004B938((f32) func_ovl13_01_8004B940() * 360.0f) * 100.0f;
        sp50.y = func_ovl13_01_8004B938((f32) func_ovl13_01_8004B940() * 360.0f) * 100.0f;
        sp50.z = func_ovl13_01_8004B938((f32) func_ovl13_01_8004B940() * 360.0f) * 100.0f;
        func_ovl13_01_8004BBE0(8, &sp50.x, (s32) temp_v0);
        if (var_s4 == 0) {
            func_ovl13_01_8004BBE0(8, &sp50.x, (s32) temp_v0);
        }
        func_ovl13_01_8004B7A8(0xF);
        var_s0 += 1;
    } while (var_s0 != 8);
    func_ovl13_01_8004B798();
}

void func_ovl13_01_80046C00(void *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, f32 *, 4) = arg2;
    M2C_FIELD(arg0, f32 *, 8) = arg3;
    M2C_FIELD(arg0, f32 *, 0xC) = arg4;
    M2C_FIELD(arg0, f32 *, 0x10) = arg5;
}

void func_ovl13_01_80046BB0(void) {
    func_ovl13_01_8004B348(D_ovl13_01_8004C31C->unk40, 0x29D, 0, 0);
    func_ovl13_01_8004B348(D_ovl13_01_8004C31C->unk40, 0x29D, 1, 1);
}

void func_ovl13_01_80046B60(void) {
    func_ovl13_01_8004B348(D_ovl13_01_8004C31C->unk40, 0x29D, 0, 2);
    func_ovl13_01_8004B348(D_ovl13_01_8004C31C->unk40, 0x29D, 1, 3);
}

void func_ovl13_01_80046AD8(void) {
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x298, 0, 0);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x298, 1, 1);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x29A, 4, 0);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x29A, 5, 1);
}

void func_ovl13_01_80046A50(void) {
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x298, 0, 2);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x298, 1, 3);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x29A, 4, 2);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x29A, 5, 3);
}

void func_ovl13_01_800469C8(void) {
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x299, 2, 0);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x299, 3, 1);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x29B, 6, 0);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x29B, 7, 1);
}

void func_ovl13_01_80046940(void) {
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x299, 2, 2);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x299, 3, 3);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x29B, 6, 2);
    func_ovl13_01_8004B348(D_ovl13_01_8004C338->unk40, 0x29B, 7, 3);
}

void func_ovl13_01_800468F0(void) {
    func_ovl13_01_8004B348(D_ovl13_01_8004C348[3]->unk40, 0x2A2, 0, 0);
    func_ovl13_01_8004B348(D_ovl13_01_8004C348[3]->unk40, 0x2A2, 1, 1);
}

void func_ovl13_01_800468A0(void) {
    func_ovl13_01_8004B348(D_ovl13_01_8004C348[3]->unk40, 0x2A2, 0, 2);
    func_ovl13_01_8004B348(D_ovl13_01_8004C348[3]->unk40, 0x2A2, 1, 3);
}

void func_ovl13_01_80046800(void) {
    Vec3f sp24;
    f32 sp18[2];
    f32 temp_ft4;

    if (func_ovl13_01_8004BA10(0x41A) != 0) {
        func_ovl13_01_8004B590(sp18);
        sp24.x = D_ovl13_01_8004C200.x;
        temp_ft4 = func_ovl13_01_8004B930(sp18[1]) * (D_ovl13_01_8004C250 * 0.5f);
        sp24.z = D_ovl13_01_8004C200.z;
        sp24.y = temp_ft4 + (D_ovl13_01_8004C200.y + 450.0f);
        func_ovl13_01_8004B568(&sp24.x);
        func_ovl13_01_800465FC(&sp24.x, sp18);
        func_ovl13_01_8004B588(sp18);
    }
}

void func_ovl13_01_800465FC(f32 *arg0, f32 *arg1) {
    Vec3f sp38;
    Vec3f sp2C;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;

    sp2C.x = D_ovl13_01_8004C388.x;
    sp2C.y = D_ovl13_01_8004C388.y - 200.0f;
    sp2C.z = D_ovl13_01_8004C388.z;
    func_ovl13_01_8004B5C8(&sp2C.x, arg0, &sp38.x);
    temp_fv0 = sp38.y - 90.0f;
    if (temp_fv0 >= 360.0f) {
        sp38.y = temp_fv0 - 360.0f;
    } else {
        if (sp38.y < 90.0f) {
            var_fv1 = temp_fv0 + 360.0f;
        } else {
            var_fv1 = temp_fv0;
        }
        sp38.y = var_fv1;
    }
    if (sp38.x >= 0.0f) {
        if (sp38.x <= 180.0f) {
            var_ft4 = sp38.x;
        } else {
            goto block_10;
        }
    } else {
block_10:
        var_ft4 = (360.0f - sp38.x) * -1.0f;
    }
    temp_fa1 = arg1[0];
    if (temp_fa1 >= 0.0f) {
        if (temp_fa1 <= 180.0f) {
            var_fv1_2 = temp_fa1;
        } else {
            goto block_15;
        }
    } else {
block_15:
        var_fv1_2 = (360.0f - temp_fa1) * -1.0f;
    }
    temp_fa0 = var_ft4 - var_fv1_2;
    var_fv0 = temp_fa0;
    if (temp_fa0 >= 180.0f) {
        var_fv0 = temp_fa0 - 360.0f;
    }
    if (var_fv0 < -180.0f) {
        var_fv0 += 360.0f;
    }
    temp_fa0_2 = -1.0f * D_ovl13_01_8004C24C;
    if (D_ovl13_01_8004C24C < var_fv0) {
        var_fv0 = D_ovl13_01_8004C24C;
    }
    if (var_fv0 < temp_fa0_2) {
        var_fv0 = temp_fa0_2;
    }
    if ((var_fv0 < -0.01f) || (var_fv0 > 0.01f)) {
        arg1[0] = (f32) (temp_fa1 + var_fv0);
    }
    arg1[1] = sp38.y;
}

void func_ovl13_01_8004636C(void) {
    s32 *flag;
    s32 i;
    s32 j;

    flag = func_ovl13_01_8004B7B0();
    func_ovl13_01_8004306C(0);
    func_ovl13_01_8004B638(D_ovl13_01_8004C31C, 0x04000000);
    for (j = 0; j < D_ovl13_01_8004C3C4 && *flag != 0; j++) {
        func_ovl13_01_8004B788(func_ovl13_01_80045F14, (void *)1, 0, 0, 0x150);
        for (i = 0; i < 5 && *flag != 0; i++) {
            func_ovl13_01_8004B7D0();
        }
    }
    if (*flag != 0) {
        func_ovl13_01_80043124(0xD1, D_ovl13_01_8004C31C);
    }
    while (*flag != 0) {
        func_ovl13_01_8004B788(func_ovl13_01_80045F14, NULL, 0, 0, 0x150);
        for (i = 0; i < 5 && *flag != 0; i++) {
            func_ovl13_01_8004B7D0();
        }
    }
    if (D_ovl13_01_8004C28C > 0) {
        func_ovl13_01_8004306C(1);
        func_ovl13_01_8004B638(D_ovl13_01_8004C31C, 0x04000000);
        while (!(D_ovl13_01_8004C31C->unk40->unkC & 0x40) && D_ovl13_01_8004C28C > 0) {
            func_ovl13_01_8004B788(func_ovl13_01_80045F14, (void *)1, 0, 0, 0x150);
            for (i = 0; i < 5 && D_ovl13_01_8004C28C > 0; i++) {
                func_ovl13_01_8004B7D0();
            }
        }
    }
    func_ovl13_01_8004B798();
}

void func_ovl13_01_800462DC(void) {
    s32 *temp_s1;

    temp_s1 = func_ovl13_01_8004B7B0();
    func_ovl13_01_8004306C(0);
    func_ovl13_01_8004B638(D_ovl13_01_8004C31C, 0x04000000);
    if (*temp_s1 != 0) {
        do {
            func_ovl13_01_8004B788(func_ovl13_01_80045F14, (void *)1, 0, 0, 0x150);
            func_ovl13_01_8004B7A8(5);
        } while (*temp_s1 != 0);
    }
    func_ovl13_01_8004B798();
}

void func_ovl13_01_80045F14(void) {
    Vec3f spA8;
    Vec3f spC0;
    Vec3f spB4;
    UnkStructA *spCC;
    f32 sp8C;
    UnkStructA_40 *temp_v0;
    f32 temp_fs5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fs2;
    f32 var_fs4;
    f32 var_ft1;
    f32 var_ft1_2;
    s32 var_s0;
    s32 var_s3;
    void *temp_s4;

    if (D_ovl13_01_8004C3C0 < 0x14) {
        D_ovl13_01_8004C3C0 += 1;
        temp_s4 = func_ovl13_01_8004B7B0();
        func_ovl13_01_80045DAC(&spCC, &spB4.x, &spC0.x);
        if (temp_s4 == NULL) {
            var_s3 = 0x5A;
            var_fs4 = 10.0f;
            var_fs2 = 22.222221f;
            sp8C = -0.24691357f;
            if (func_ovl13_01_8004BA10(0x41F) != 0) {
                var_fs4 = 10.0f * 0.75f;
                var_fs2 = 22.222221f * 0.75f;
                sp8C = -0.24691357f * 0.75f;
            }
        } else {
            func_ovl13_01_8004B640(spCC, 0x80);
            var_fs4 = 1.0f;
            var_fs2 = 5.5555553f;
            var_s3 = 0x3C;
            sp8C = -0.06172839f;
            if (func_ovl13_01_8004B948(1) != 0) {
                var_ft1 = (f32) ((f64) spC0.x + (func_ovl13_01_8004B940() * 45.0 * 0.5));
            } else {
                var_ft1 = (f32) ((f64) spC0.x - (func_ovl13_01_8004B940() * 45.0 * 0.5));
            }
            spC0.x = var_ft1;
            if (func_ovl13_01_8004B948(1) != 0) {
                var_ft1_2 = (f32) ((f64) spC0.y + (func_ovl13_01_8004B940() * 45.0 * GLUE_F64(0x3FE00000U, 0U)));
            } else {
                var_ft1_2 = (f32) ((f64) spC0.y - (func_ovl13_01_8004B940() * 45.0 * GLUE_F64(0x3FE00000U, 0U)));
            }
            spC0.y = var_ft1_2;
        }
        temp_fs5 = var_fs2;
        for (var_s0 = 0; var_s0 < var_s3; var_s0++) {
            if ((func_ovl13_01_8004ACC8(spB4.x, spB4.y, spB4.z) & 0xF) == 0xF) {
                break;
            }
            {
                spCC->unk40->unk36 = 0x7F;
                if (temp_s4 == NULL) {
                    func_ovl13_01_8004B748(spCC);
                    temp_fv0 = (var_fs4 * 0.3f) + ((1.0f - (var_fs2 / temp_fs5)) * (var_fs4 * 0.7f));
                    spCC->unk40->unk30 = temp_fv0;
                    spCC->unk40->unk2C = temp_fv0;
                    spCC->unk40->unk28 = temp_fv0;
                } else {
                    spCC->unk40->unk30 = var_fs4;
                    temp_v0 = spCC->unk40;
                    temp_fv0_2 = temp_v0->unk30;
                    temp_v0->unk2C = temp_fv0_2;
                    spCC->unk40->unk28 = temp_fv0_2;
                }
                func_ovl13_01_8004B710((UnkStructA *) &spB4.x, spCC);
                spC0.z = var_fs2;
                var_fs2 += sp8C;
                func_ovl13_01_8004B5D0(&spC0.x, &spA8.x);
                spB4.x += spA8.x;
                spB4.y += spA8.y;
                spB4.z += spA8.z;
                func_ovl13_01_8004B7D0();
            }
        }
        D_ovl13_01_8004C3C0 -= 1;
        func_ovl13_01_8004B650(spCC);
        func_ovl13_01_8004B798();
    }
}

void func_ovl13_01_80045DAC(UnkStructA **arg0, f32 *arg1, f32 *arg2) {
    UnkStructA *sp24;
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v1;

    temp_v0 = func_ovl13_01_8004B660(0x118, 0x01080080, 0x40, NULL);
    sp24 = temp_v0;
    temp_v1 = temp_v0->unk40;
    temp_v1->unkC |= 0x8000;
    temp_v0->unk34 = 20.0f;
    temp_v0->unk38 = 0.0f;
    temp_v0->unk40->unk36 = 0;
    func_ovl13_01_8004B340(temp_v0->unk40, 1);
    func_ovl13_01_8004B348(sp24->unk40, 0x119, 0, 0);
    arg2[0] = D_ovl13_01_8004C31C->unk40->unk20;
    arg2[2] = 100.0f;
    arg2[1] = (f32) ((D_ovl13_01_8004C31C->unk40->unk1C * -1.0f) + -15.0f);
    func_ovl13_01_8004B5D0(arg2, arg1);
    arg1[0] += D_ovl13_01_8004C31C->unk40->unk10;
    arg1[1] = (f32) (arg1[1] + D_ovl13_01_8004C31C->unk40->unk14);
    arg1[2] = (f32) (arg1[2] + D_ovl13_01_8004C31C->unk40->unk18);
    *arg0 = sp24;
}

void func_ovl13_01_80045D80(void *arg0, s32 arg1) {
    func_ovl13_01_8004B348(M2C_FIELD(arg0, UnkStructA_40 **, 0x40), 0x119, 0, arg1);
}

void func_ovl13_01_80045C9C(void) {
    f32 sp18;
    UnkStructA_40 *temp_a0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa1;

    if (func_ovl13_01_8004BA10(0x416) != 0) {
        temp_a0 = D_ovl13_01_8004C338->unk40;
        sp18 = temp_a0->unk48->unk4->unk4;
        temp_fv0 = func_ovl13_01_8004B378(temp_a0, 0);
        temp_fv1 = sp18 - 13.0f;
        var_fa1 = temp_fv1;
        if (temp_fv0 <= temp_fv1) {
            var_fa1 = temp_fv1 - temp_fv0;
        } else if (temp_fv1 < 0.0f) {
            var_fa1 = temp_fv1 + temp_fv0;
        }
        D_ovl13_01_8004C338->unk40->unk14 = (func_ovl13_01_8004B930(360.0f * (var_fa1 / temp_fv0)) * 100.0f) + D_ovl13_01_8004C388.y;
    }
}

f32 func_ovl13_01_80045C60(f32 arg0, f32 arg1) {
    f32 var_fa0;

    var_fa0 = arg0;
    if (arg1 <= var_fa0) {
        return var_fa0 - arg1;
    }
    if (var_fa0 < 0.0f) {
        var_fa0 += arg1;
    }
    return var_fa0;
}

void func_ovl13_01_80045B0C(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv1;
    s32 *temp_s0;

    temp_s0 = func_ovl13_01_8004B7B0();
    temp_v0 = func_ovl13_01_8004B660(0x116, 0x01200000, 0xD0, D_ovl13_01_8004C31C);
    temp_v0->unk40->unk30 = 3.0f;
    temp_v1 = temp_v0->unk40;
    temp_fv1 = temp_v1->unk30;
    temp_v1->unk2C = temp_fv1;
    temp_v0->unk40->unk28 = temp_fv1;
    temp_v0->unk50 = 0.0f;
    func_ovl13_01_80043124(0xD9, D_ovl13_01_8004C31C);
    if (*temp_s0 != 0) {
        do {
            temp_v0_2 = temp_v0->unk40;
            temp_fv0 = temp_v0_2->unk20 + 5.0f;
            if (temp_fv0 >= 360.0f) {
                temp_v0_2->unk20 = temp_fv0 - 360.0f;
            } else {
                if (temp_fv0 < 0.0f) {
                    var_fv1 = temp_fv0 + 360.0f;
                } else {
                    var_fv1 = temp_fv0;
                }
                temp_v0_2->unk20 = var_fv1;
            }
            func_ovl13_01_8004B7D0();
        } while (*temp_s0 != 0);
    }
    func_ovl13_01_8004B650(temp_v0);
    func_ovl13_01_8004B798();
}

void func_ovl13_01_800455D0(s32 arg0) {
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    f32 sp4C;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s1;

    func_ovl13_01_8004B5C8(&D_ovl13_01_8004C260.x, &D_ovl13_01_8004C388.x, &sp54.x);
    sp54.y = 0.0f;
    sp54.z = 20.0f;
    func_ovl13_01_8004B5D0(&sp54.x, &sp60.x);
    if (D_ovl13_01_8004C388.y < 1800.0f) {
        do {
            D_ovl13_01_8004C388.x += sp60.x;
            D_ovl13_01_8004C388.y += 20.0f;
            D_ovl13_01_8004C388.z = (f32) (D_ovl13_01_8004C388.z + sp60.z);
            func_ovl13_01_8004B7D0();
        } while (D_ovl13_01_8004C388.y < 1800.0f);
    }
    func_ovl13_01_80043124(0xBF, D_ovl13_01_8004C31C);
    sp54.x = (f32) ((func_ovl13_01_8004B940() * 120.0) + 120.0);
    if (func_ovl13_01_8004B948(1) != 0) {
        sp54.x += 180.0f;
    }
    if (sp54.x >= 360.0f) {
        sp54.x -= 360.0f;
    } else {
        if (sp54.x < 0.0f) {
            var_fv1 = sp54.x + 360.0f;
        } else {
            var_fv1 = sp54.x;
        }
        sp54.x = var_fv1;
    }
    sp54.y = 20.0f;
    sp54.z = 800.0f;
    func_ovl13_01_8004B5D0(&sp54.x, &sp6C.x);
    sp6C.x += D_ovl13_01_8004C200.x;
    sp6C.y += D_ovl13_01_8004C200.y;
    sp6C.z += D_ovl13_01_8004C200.z;
    func_ovl13_01_8004B5C8(&D_ovl13_01_8004C388.x, &sp6C.x, &sp54.x);
    temp_fv0 = sp54.y - 90.0f;
    if (temp_fv0 >= 360.0f) {
        sp54.y = temp_fv0 - 360.0f;
    } else {
        if (sp54.y < 90.0f) {
            var_fv1_2 = temp_fv0 + 360.0f;
        } else {
            var_fv1_2 = temp_fv0;
        }
        sp54.y = var_fv1_2;
    }
    var_fs0 = sp54.z / 45.0f;
    D_ovl13_01_8004C2A8 = 4.0f;
    var_s1 = 0;
    D_ovl13_01_8004C2A4 = 4.0f;
    sp4C = (var_fs0 / 90.0f) * -1.0f;
loop_17:
    if ((func_ovl13_01_80043830() >= 2) || (D_ovl13_01_8004C28C <= 0)) {
        D_ovl13_01_8004C2A8 = 0.5f;
    } else {
        sp54.z = var_fs0;
        var_fs0 += sp4C;
        func_ovl13_01_8004B5D0(&sp54.x, &sp60.x);
        D_ovl13_01_8004C388.x += sp60.x;
        D_ovl13_01_8004C388.y = (f32) (D_ovl13_01_8004C388.y + sp60.y);
        D_ovl13_01_8004C388.z = (f32) (D_ovl13_01_8004C388.z + sp60.z);
        func_ovl13_01_8004B7D0();
        var_s1 += 1;
        if (var_s1 == 0x5A) {
            D_ovl13_01_8004C2A8 = 0.5f;
        } else {
            goto loop_17;
        }
    }
    D_ovl13_01_8004C2A4 = 1.0f;
    if (func_ovl13_01_8004BA10(0x41F) != 0) {
        D_ovl13_01_8004C2A8 = 0.0f;
        D_ovl13_01_8004C2A4 = 0.0f;
    }
    D_ovl13_01_8004C3D0 = (D_ovl13_01_8004C3C4 * 5) + arg0;
    func_ovl13_01_8004B788(func_ovl13_01_8004636C, &D_ovl13_01_8004C3D0, 0, 0, 0x150);
    if ((D_ovl13_01_8004C3D0 > 0) && (func_ovl13_01_80043830() < 2) && (D_ovl13_01_8004C28C > 0)) {
loop_27:
        func_ovl13_01_8004B7D0();
        temp_v1 = D_ovl13_01_8004C3D0 - 1;
        D_ovl13_01_8004C3D0 = temp_v1;
        if ((temp_v1 > 0) && (func_ovl13_01_80043830() < 2)) {
            if (D_ovl13_01_8004C28C > 0) {
                goto loop_27;
            }
        }
    }
    if (D_ovl13_01_8004C3D0 < 0) {
        D_ovl13_01_8004C3D0 = 0;
    }
    D_ovl13_01_8004C3D4 = 0x78;
    if (func_ovl13_01_8004BA10(0x41F) != 0) {
        D_ovl13_01_8004C3D4 = (s32) ((f64) D_ovl13_01_8004C3D4 * 1.5);
    }
    if ((D_ovl13_01_8004C3D4 > 0) && (func_ovl13_01_80043830() < 2) && (D_ovl13_01_8004C28C > 0)) {
loop_37:
        func_ovl13_01_8004B7D0();
        temp_v1_2 = D_ovl13_01_8004C3D4 - 1;
        D_ovl13_01_8004C3D4 = temp_v1_2;
        if (temp_v1_2 > 0) {
            if (func_ovl13_01_80043830() < 2) {
                if (D_ovl13_01_8004C28C <= 0) {

                } else {
                    goto loop_37;
                }
            }
        }
    }
    D_ovl13_01_8004C2A8 = 0.5f;
    D_ovl13_01_8004C2A4 = 1.0f;
    D_ovl13_01_8004C3D0 = 0;
}

void func_ovl13_01_80045538(void) {
    D_ovl13_01_8004C3D8 = 1;
    func_ovl13_01_8004B788(func_ovl13_01_800462DC, &D_ovl13_01_8004C3D8, 0, 0, 0x150);
    func_ovl13_01_8004B788(func_ovl13_01_80044F74, &D_ovl13_01_8004C3D8, 0, 0, 0x150);
    func_ovl13_01_800450B4(-1);
    func_ovl13_01_80043124(0xD6, D_ovl13_01_8004C31C);
    func_ovl13_01_80044160(0);
    func_ovl13_01_8004BA08(0x413);
    D_ovl13_01_8004C3D8 = 0;
}

void func_ovl13_01_800450B4(s32 arg0) {
    Vec3f sp78;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fs0;
    f32 var_fs0_2;
    f32 var_fs2;
    f32 var_fs3;
    f32 var_fs3_2;
    f32 var_ft4;
    f32 var_ft4_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;
    f32 var_fv1;
    s32 var_s0;
    s32 var_s3;

    var_s3 = arg0;
    func_ovl13_01_8004B5C8(&D_ovl13_01_8004C200.x, &D_ovl13_01_8004C388.x, &sp78.x);
    temp_fv1 = sp78.y - 90.0f;
    if (temp_fv1 >= 360.0f) {
        sp78.y = temp_fv1 - 360.0f;
    } else {
        if (sp78.y < 90.0f) {
            var_fv0 = temp_fv1 + 360.0f;
        } else {
            var_fv0 = temp_fv1;
        }
        sp78.y = var_fv0;
    }
    do {
        var_fs0 = (f32) ((func_ovl13_01_8004B940() * 90.0) + 135.0);
        if (func_ovl13_01_8004B948(1) != 0) {
            var_fs0 += 180.0f;
        }
        if (var_fs0 >= 360.0f) {
            var_fs0_2 = var_fs0 - 360.0f;
        } else {
            if (var_fs0 < 0.0f) {
                var_fv0_2 = var_fs0 + 360.0f;
            } else {
                var_fv0_2 = var_fs0;
            }
            var_fs0_2 = var_fv0_2;
        }
        if (var_fs0_2 >= 0.0f) {
            if (var_fs0_2 <= 180.0f) {
                var_ft4 = var_fs0_2;
            } else {
                goto block_19;
            }
        } else {
block_19:
            var_ft4 = (360.0f - var_fs0_2) * -1.0f;
        }
        if (sp78.x >= 0.0f) {
            if (sp78.x <= 180.0f) {
                var_fv0_3 = sp78.x;
            } else {
                goto block_24;
            }
        } else {
block_24:
            var_fv0_3 = (360.0f - sp78.x) * -1.0f;
        }
        temp_fs0 = var_ft4 - var_fv0_3;
        var_fs2 = temp_fs0;
    } while (func_ovl13_01_8004B970(temp_fs0, 15.0f) != 0);
    if (var_s3 != -1) {
        var_fs3 = (f32) (func_ovl13_01_8004B940() * 30.0);
        var_fv1 = (f32) ((func_ovl13_01_8004B940() * 500.0) + 2000.0);
    } else {
        var_fs3 = 30.0f;
        var_fv1 = 1100.0f;
        var_s3 = 0xF0;
    }
    if (temp_fs0 > 180.0f) {
        var_fs2 = temp_fs0 - 360.0f;
    }
    if (var_fs2 < -180.0f) {
        var_fs2 += 360.0f;
    }
    if (var_fs2 > 90.0f) {
        var_s3 += 0x5A;
    }
    if (var_fs2 < -90.0f) {
        var_s3 += 0x5A;
    }
    if (var_fs3 >= 0.0f) {
        if (var_fs3 <= 180.0f) {
            var_ft4_2 = var_fs3;
        } else {
            goto block_42;
        }
    } else {
block_42:
        var_ft4_2 = (360.0f - var_fs3) * -1.0f;
    }
    if (sp78.y >= 0.0f) {
        if (sp78.y <= 180.0f) {
            var_fv0_4 = sp78.y;
        } else {
            goto block_47;
        }
    } else {
block_47:
        var_fv0_4 = (360.0f - sp78.y) * -1.0f;
    }
    temp_fs0_2 = var_ft4_2 - var_fv0_4;
    temp_fv0 = (f32) var_s3;
    var_fs3_2 = temp_fs0_2;
    temp_fs2 = var_fs2 / temp_fv0;
    if (temp_fs0_2 > 180.0f) {
        var_fs3_2 = temp_fs0_2 - 360.0f;
    }
    if (var_fs3_2 < -180.0f) {
        var_fs3_2 += 360.0f;
    }
    var_s0 = 0;
    if (var_s3 > 0) {
loop_53:
        if (func_ovl13_01_8004B978(temp_fs2) != 0) {
            var_s0 = var_s3;
        }
        if (func_ovl13_01_80043830() < 2) {
            func_ovl13_01_8004B5D0(&sp78.x, &D_ovl13_01_8004C388.x);
            D_ovl13_01_8004C388.x += D_ovl13_01_8004C200.x;
            D_ovl13_01_8004C388.y = (f32) (D_ovl13_01_8004C388.y + D_ovl13_01_8004C200.y);
            D_ovl13_01_8004C388.z = (f32) (D_ovl13_01_8004C388.z + D_ovl13_01_8004C200.z);
            sp78.x += temp_fs2;
            sp78.z += (var_fv1 - sp78.z) / temp_fv0;
            sp78.y += var_fs3_2 / temp_fv0;
            func_ovl13_01_8004B7D0();
            var_s0 += 1;
            if (var_s0 < var_s3) {
                goto loop_53;
            }
        }
    }
}

void func_ovl13_01_80044F74(void) {
    s32 *temp_v0;
    s32 var_s1;

    var_s1 = 0;
    temp_v0 = func_ovl13_01_8004B7B0();
    if (*temp_v0 != 0) {
        do {
            func_ovl13_01_8004B788(func_ovl13_01_80046C2C, D_ovl13_01_8004C338, 0, 0, 0x150);
            func_ovl13_01_8004B788(func_ovl13_01_80046C2C, D_ovl13_01_8004C358, 0, 0, 0x150);
            func_ovl13_01_8004B788(func_ovl13_01_80046C2C, D_ovl13_01_8004C35C, 0, 0, 0x150);
            func_ovl13_01_8004B788(func_ovl13_01_80046C2C, D_ovl13_01_8004C348[3], 0, 0, 0x150);
            if (var_s1 < 2) {
                var_s1 += 1;
                func_ovl13_01_80043124(0xC0, D_ovl13_01_8004C31C);
            }
            func_ovl13_01_8004B7A8(0x78);
        } while (*temp_v0 != 0);
    }
    func_ovl13_01_8004B798();
}

void func_ovl13_01_80044F3C(void *arg0) {
    func_ovl13_01_8004B788(func_ovl13_01_80046C2C, arg0, 0, 0, 0x150);
}

void func_ovl13_01_800446FC(void) {
    Vec3f sp84;
    Vec3f spA8;
    Vec3f spB4;
    f32 sp7C;
    s32 sp78;
    s32 sp74;
    f32 sp4C;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_fa0_10;
    f32 var_fa0_2;
    f32 var_fa0_3;
    f32 var_fa0_4;
    f32 var_fa0_5;
    f32 var_fa0_6;
    f32 var_fa0_7;
    f32 var_fa0_8;
    f32 var_fa0_9;
    f32 var_fa1;
    f32 var_fa1_2;
    f32 var_fa1_3;
    f32 var_fa1_4;
    f32 var_fa1_5;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 var_v1;

    D_ovl13_01_8004C2A8 = 1.0f;
    func_ovl13_01_8004B5C8(&D_ovl13_01_8004C260.x, &D_ovl13_01_8004C388.x, &spB4.x);
    temp_fv0 = spB4.x + 90.0f;
    if (temp_fv0 >= 360.0f) {
        var_fa0 = temp_fv0 - 360.0f;
    } else {
        if (temp_fv0 < 0.0f) {
            var_fa1 = temp_fv0 + 360.0f;
        } else {
            var_fa1 = temp_fv0;
        }
        var_fa0 = var_fa1;
    }
    if (var_fa0 < 180.0f) {
        spB4.x = 0.0f;
    } else {
        spB4.x = 180.0f;
    }
    spB4.y = 10.0f;
    spB4.z = 40.0f;
    func_ovl13_01_8004B5D0(&spB4.x, &sp84.x);
    if (func_ovl13_01_8004B5E0(&D_ovl13_01_8004C260.x, &D_ovl13_01_8004C388.x) < 7000.0f) {
        do {
            D_ovl13_01_8004C388.x += sp84.x;
            D_ovl13_01_8004C388.y = (f32) (D_ovl13_01_8004C388.y + sp84.y);
            D_ovl13_01_8004C388.z = (f32) (D_ovl13_01_8004C388.z + sp84.z);
            func_ovl13_01_8004B7D0();
        } while (func_ovl13_01_8004B5E0(&D_ovl13_01_8004C260.x, &D_ovl13_01_8004C388.x) < 7000.0f);
    }
    D_ovl13_01_8004C24C = 5.0f;
    func_ovl13_01_800446B0();
    func_ovl13_01_80043124(0xBF, D_ovl13_01_8004C31C);
    D_ovl13_01_8004C2A0 = 0;
    sp74 = func_ovl13_01_80043F88(1);
    func_ovl13_01_8004B638(D_ovl13_01_8004C338, 0x04000000);
    func_ovl13_01_8004B5C8(&D_ovl13_01_8004C388.x, &D_ovl13_01_8004C260.x, &spA8.x);
    temp_fv0_2 = spA8.y - 90.0f;
    if (temp_fv0_2 >= 360.0f) {
        var_fa1_2 = temp_fv0_2 - 360.0f;
    } else {
        if (spA8.y < 90.0f) {
            var_fa0_2 = temp_fv0_2 + 360.0f;
        } else {
            var_fa0_2 = temp_fv0_2;
        }
        var_fa1_2 = var_fa0_2;
    }
    if (var_fa1_2 >= 0.0f) {
        if (temp_fv0_2 >= 360.0f) {
            var_fa0_3 = temp_fv0_2 - 360.0f;
        } else {
            if (spA8.y < 90.0f) {
                var_fa1_3 = temp_fv0_2 + 360.0f;
            } else {
                var_fa1_3 = temp_fv0_2;
            }
            var_fa0_3 = var_fa1_3;
        }
        if (var_fa0_3 <= 180.0f) {
            if (temp_fv0_2 >= 360.0f) {
                var_fa0_4 = temp_fv0_2 - 360.0f;
            } else {
                if (spA8.y < 90.0f) {
                    var_fa0_5 = temp_fv0_2 + 360.0f;
                } else {
                    var_fa0_5 = temp_fv0_2;
                }
                var_fa0_4 = var_fa0_5;
            }
        } else {
            goto block_32;
        }
    } else {
block_32:
        if (temp_fv0_2 >= 360.0f) {
            var_fv1 = temp_fv0_2 - 360.0f;
        } else {
            if (spA8.y < 90.0f) {
                var_fa0_6 = temp_fv0_2 + 360.0f;
            } else {
                var_fa0_6 = temp_fv0_2;
            }
            var_fv1 = var_fa0_6;
        }
        var_fa0_4 = (360.0f - var_fv1) * -1.0f;
    }
    temp_fv1 = var_fa0_4 * -1.0f;
    if ((temp_fv1 >= 0.0f) && (temp_fv1 <= 180.0f)) {
        var_fa1_4 = temp_fv1;
        spA8.y = temp_fv1;
    } else {
        spA8.y = temp_fv1;
        var_fa1_4 = (360.0f - temp_fv1) * -1.0f;
    }
    if ((D_ovl13_01_8004C3A8.y >= 0.0f) && (D_ovl13_01_8004C3A8.y <= 180.0f)) {
        var_fa0_7 = D_ovl13_01_8004C3A8.y;
    } else {
        var_fa0_7 = (360.0f - D_ovl13_01_8004C3A8.y) * -1.0f;
    }
    var_v1 = 0;
    if (sp74 > 0) {
        sp4C = (var_fa1_4 - var_fa0_7) / (f32) sp74;
        do {
            sp78 = var_v1;
            D_ovl13_01_8004C3A8.y = D_ovl13_01_8004C3A8.y + sp4C;
            func_ovl13_01_8004B7D0();
            var_v1 += 1;
        } while (var_v1 != sp74);
    }
    func_ovl13_01_8004BA00(0x414);
    var_fs0 = 0.0f;
    temp_fv0_3 = spB4.x + 180.0f;
    if (temp_fv0_3 >= 360.0f) {
        var_fs1 = temp_fv0_3 - 360.0f;
    } else {
        if (temp_fv0_3 < 0.0f) {
            var_fa0_8 = temp_fv0_3 + 360.0f;
        } else {
            var_fa0_8 = temp_fv0_3;
        }
        var_fs1 = var_fa0_8;
    }
    sp7C = D_ovl13_01_8004C338->unk70 * 0.2f;
    if (func_ovl13_01_8004B5E0(&D_ovl13_01_8004C260.x, &D_ovl13_01_8004C388.x) > 100.0f) {
loop_57:
        if (func_ovl13_01_80043830() < 2) {
            func_ovl13_01_8004B5C8(&D_ovl13_01_8004C388.x, &D_ovl13_01_8004C260.x, &spA8.x);
            temp_fv0_4 = spA8.y - 90.0f;
            if (temp_fv0_4 >= 360.0f) {
                spA8.y = temp_fv0_4 - 360.0f;
            } else {
                if (spA8.y < 90.0f) {
                    var_fa0_9 = temp_fv0_4 + 360.0f;
                } else {
                    var_fa0_9 = temp_fv0_4;
                }
                spA8.y = var_fa0_9;
            }
            if ((var_fs1 >= 0.0f) && (var_fs1 <= 180.0f)) {
                var_fa1_5 = var_fs1;
            } else {
                var_fa1_5 = (360.0f - var_fs1) * -1.0f;
            }
            if ((D_ovl13_01_8004C3A8.x >= 0.0f) && (D_ovl13_01_8004C3A8.x <= 180.0f)) {
                var_fa0_10 = D_ovl13_01_8004C3A8.x;
            } else {
                var_fa0_10 = (360.0f - D_ovl13_01_8004C3A8.x) * -1.0f;
            }
            temp_fv1_2 = var_fa1_5 - var_fa0_10;
            var_fv0 = temp_fv1_2;
            if (temp_fv1_2 > 180.0f) {
                var_fv0 = temp_fv1_2 - 360.0f;
            }
            if (var_fv0 < -180.0f) {

            }
            spA8.z = var_fs0;
            var_fs0 += sp7C;
            func_ovl13_01_8004B5D0(&spA8.x, &sp84.x);
            D_ovl13_01_8004C388.x += sp84.x;
            D_ovl13_01_8004C388.y = (f32) (D_ovl13_01_8004C388.y + sp84.y);
            D_ovl13_01_8004C388.z = (f32) (D_ovl13_01_8004C388.z + sp84.z);
            func_ovl13_01_8004B7D0();
            if (func_ovl13_01_8004B5E0(&D_ovl13_01_8004C260.x, &D_ovl13_01_8004C388.x) > 100.0f) {
                goto loop_57;
            }
        }
    }
    var_fv1_2 = spA8.y;
    if ((var_fv1_2 >= 0.0f) && (var_fv1_2 <= 180.0f)) {

    } else {
        var_fv1_2 = (360.0f - var_fv1_2) * -1.0f;
    }
    spA8.y = var_fv1_2;
    sp7C = D_ovl13_01_8004C338->unk70 * -0.4f;
    func_ovl13_01_80043F88(2);
    func_ovl13_01_8004B638(D_ovl13_01_8004C338, 0x04000000);
    D_ovl13_01_8004C2A8 = 0.5f;
    if (var_fs0 >= 0.0f) {
loop_83:
        if (func_ovl13_01_80043830() < 2) {
            if (spA8.y < 70.0f) {
                spA8.y += 1.0f;
            }
            spA8.z = var_fs0;
            var_fs0 += sp7C;
            func_ovl13_01_8004B5D0(&spA8.x, &sp84.x);
            D_ovl13_01_8004C388.x += sp84.x;
            D_ovl13_01_8004C388.y = (f32) (D_ovl13_01_8004C388.y + sp84.y);
            D_ovl13_01_8004C388.z = (f32) (D_ovl13_01_8004C388.z + sp84.z);
            func_ovl13_01_8004B7D0();
            if (var_fs0 >= 0.0f) {
                goto loop_83;
            }
        }
    }
    if (func_ovl13_01_80043830() >= 2) {
        func_ovl13_01_80043F88(0);
        func_ovl13_01_8004BA00(0x416);
        func_ovl13_01_8004BA00(0x413);
        D_ovl13_01_8004C2A0 = 1;
        D_ovl13_01_8004C24C = 1.0f;
        D_ovl13_01_8004C2A8 = 0.5f;
        D_ovl13_01_8004C2A4 = 1.0f;
        func_ovl13_01_80044160(1);
        return;
    }
    func_ovl13_01_800430CC(D_ovl13_01_8004C338);
    D_ovl13_01_8004C2A0 = 1;
    func_ovl13_01_80044118();
    D_ovl13_01_8004C24C = 1.0f;
    D_ovl13_01_8004C2A8 = 0.5f;
    D_ovl13_01_8004C2A4 = 1.0f;
    func_ovl13_01_8004B7A8(0x5A);
}

void func_ovl13_01_800446B0(void) {
    func_ovl13_01_8004BA08(0x413);
    func_ovl13_01_8004400C(13.0f);
    func_ovl13_01_8004BA08(0x416);
    func_ovl13_01_8004BA08(0x414);
    func_ovl13_01_8004400C(0.0f);
}

void func_ovl13_01_80044160(s32 arg0) {
    Vec3f sp64;
    Vec3f sp58;
    s32 sp84;
    f32 sp74;
    f32 sp70;
    s32 i;
    f32 temp_fv0;
    s32 var_s3;
    s32 var_s4;

    func_ovl13_01_8004BA08(0x415);
    temp_fv0 = D_ovl13_01_8004C338->unk70;
    sp70 = temp_fv0;
    D_ovl13_01_8004C338->unk70 = temp_fv0 * 0.4f;
    sp74 = D_ovl13_01_8004C2BC;
    D_ovl13_01_8004C2BC = 0.45f;
    func_ovl13_01_8004B5C8(&D_ovl13_01_8004C260.x, &D_ovl13_01_8004C388.x, &sp58.x);
    sp58.y = 0.0f;
    sp58.z = 20.0f;
    func_ovl13_01_8004B5D0(&sp58.x, &sp64.x);
    func_ovl13_01_8004BA00(0x417);
    if (D_ovl13_01_8004C3B4 == 2) {
        func_ovl13_01_8004400C(func_ovl13_01_8004B378(D_ovl13_01_8004C338->unk40, 0) - 0.001f);
        func_ovl13_01_80043F88(0);
    }
    sp84 = arg0;
    func_ovl13_01_8004B788(func_ovl13_01_80045B0C, &sp84, 0, 0, 0x150);
    func_ovl13_01_8004B7D0();
    if (arg0 != 0) {
        if ((D_ovl13_01_8004C388.y > -3000.0f) && (D_ovl13_01_8004C338->unk6C != 0.0f)) {
loop_5:
            D_ovl13_01_8004C388.x += sp64.x;
            D_ovl13_01_8004C388.z = (f32) (D_ovl13_01_8004C388.z + sp64.z);
            func_ovl13_01_8004B7D0();
            if (D_ovl13_01_8004C388.y > -3000.0f) {
                if (D_ovl13_01_8004C338->unk6C != 0.0f) {
                    goto loop_5;
                }
            }
        }
        sp84 = 0;
        func_ovl13_01_8004B7D0();
        func_ovl13_01_8004BA08(0x417);
        func_ovl13_01_8004BA00(0x415);
        D_ovl13_01_8004C338->unk68 = 0.0f;
        D_ovl13_01_8004C338->unk6C = D_ovl13_01_8004C338->unk68;
        D_ovl13_01_8004C2BC = sp74;
        D_ovl13_01_8004C338->unk70 = sp70;
        while (D_ovl13_01_8004C388.y < 600.0f) {
            D_ovl13_01_8004C2A0 = 2;
            D_ovl13_01_8004C388.y += 30.0f;
            func_ovl13_01_8004B7D0();
        }
    } else {
        func_ovl13_01_8004BD28();
        func_ovl13_01_8004B638(D_ovl13_01_8004C338, 0x80000);
        for (i = 0; i < 2; i++) {
            func_ovl13_01_8004B638(D_ovl13_01_8004C330[i], 0x80000);
        }
        func_ovl13_01_8004B638(D_ovl13_01_8004C31C, 0x80000);
        for (i = 0; i < 4; i++) {
            func_ovl13_01_8004B638(D_ovl13_01_8004C348[i], 0x80000);
        }
        var_s4 = 0;
        for (var_s3 = 0; var_s3 < 0x50 && D_ovl13_01_8004C338->unk6C != 0.0f; var_s3++) {
            if ((var_s4 == 0) && (var_s3 > 40.0)) {
                var_s4 = 1;
                func_ovl13_01_8004BA08(0x41A);
            }
            D_ovl13_01_8004C338->unk40->unk36 = (1.0f - ((f32) var_s3 / 80.0f)) * 255.0f;
            for (i = 0; i < 2; i++) {
                D_ovl13_01_8004C330[i]->unk40->unk36 = D_ovl13_01_8004C338->unk40->unk36;
            }
            D_ovl13_01_8004C31C->unk40->unk36 = D_ovl13_01_8004C338->unk40->unk36;
            D_ovl13_01_8004C348[0]->unk40->unk36 = D_ovl13_01_8004C338->unk40->unk36;
            D_ovl13_01_8004C348[1]->unk40->unk36 = D_ovl13_01_8004C338->unk40->unk36;
            D_ovl13_01_8004C348[2]->unk40->unk36 = D_ovl13_01_8004C338->unk40->unk36;
            D_ovl13_01_8004C348[3]->unk40->unk36 = D_ovl13_01_8004C338->unk40->unk36;
            func_ovl13_01_8004B7D0();
        }
        func_ovl13_01_8004BA08(0x417);
        func_ovl13_01_8004B640(D_ovl13_01_8004C338, 0x01000000);
        for (i = 0; i < 2; i++) {
            func_ovl13_01_8004B640(D_ovl13_01_8004C330[i], 0x01000000);
        }
        func_ovl13_01_8004B640(D_ovl13_01_8004C31C, 0x01000000);
        for (i = 0; i < 4; i++) {
            func_ovl13_01_8004B640(D_ovl13_01_8004C348[i], 0x01000000);
        }
    }
    D_ovl13_01_8004C2A0 = 1;
}

void func_ovl13_01_80044118(void) {
    func_ovl13_01_8004BA00(0x414);
    func_ovl13_01_80043F88(0);
    func_ovl13_01_8004400C(13.0f);
    func_ovl13_01_8004BA00(0x416);
    func_ovl13_01_8004BA00(0x413);
}

void func_ovl13_01_8004400C(f32 arg0) {
    UnkStructA_40_48_4 *temp_v0;
    f32 temp_fv0;
    f32 var_fs0;
    s32 var_s0;

    temp_fv0 = func_ovl13_01_80043F88(D_ovl13_01_8004C3B4);
    D_ovl13_01_8004C338->unk40->unk48->unk4->unk4 = D_ovl13_01_8004C3B8;
    var_s0 = 0;
    if (D_ovl13_01_8004C3B8 <= arg0) {
        var_fs0 = arg0 - D_ovl13_01_8004C3B8;
    } else {
        var_fs0 = (temp_fv0 - D_ovl13_01_8004C3B8) + arg0;
    }
    do {
        func_ovl13_01_8004B7D0();
        var_s0 += 1;
        temp_v0 = D_ovl13_01_8004C338->unk40->unk48->unk4;
        temp_v0->unk4 += var_fs0 / 30.0f;
    } while (var_s0 != 0x1E);
    D_ovl13_01_8004C338->unk40->unk48->unk4->unk4 = arg0;
}

f32 func_ovl13_01_80043F88(s32 arg0) {
    D_ovl13_01_8004C3B8 = D_ovl13_01_8004C338->unk40->unk48->unk4->unk4;
    func_ovl13_01_8004B360(D_ovl13_01_8004C338->unk40, arg0, 0);
    func_ovl13_01_8004B640(D_ovl13_01_8004C338, 0x0C000000);
    D_ovl13_01_8004C3B4 = arg0;
    return func_ovl13_01_8004B378(D_ovl13_01_8004C338->unk40, 0);
}

void func_ovl13_01_80043878(void) {
    Vec3f sp58;
    Vec3f sp7C;
    Vec3f sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fa1_2;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    f32 var_fv1_4;
    s32 var_s0;
    s32 var_s0_2;

    if (func_ovl13_01_8004B948(1) != 0) {
        sp7C.x = 0.0f;
    } else {
        sp7C.x = 180.0f;
    }
    sp7C.y = 30.0f;
    sp7C.z = 1500.0f;
    func_ovl13_01_8004B5C8(&D_ovl13_01_8004C200.x, &D_ovl13_01_8004C388.x, &sp70.x);
    temp_fv0 = sp70.y - 90.0f;
    if (temp_fv0 >= 360.0f) {
        sp70.y = temp_fv0 - 360.0f;
    } else {
        if (sp70.y < 90.0f) {
            var_fv1 = temp_fv0 + 360.0f;
        } else {
            var_fv1 = temp_fv0;
        }
        sp70.y = var_fv1;
    }
    if (sp7C.x >= 0.0f) {
        if (sp7C.x <= 180.0f) {
            var_fa1 = sp7C.x;
        } else {
            goto block_14;
        }
    } else {
block_14:
        var_fa1 = (360.0f - sp7C.x) * -1.0f;
    }
    if (sp70.x >= 0.0f) {
        if (sp70.x <= 180.0f) {
            var_fv1_2 = sp70.x;
        } else {
            goto block_19;
        }
    } else {
block_19:
        var_fv1_2 = (360.0f - sp70.x) * -1.0f;
    }
    temp_fv0_2 = var_fa1 - var_fv1_2;
    var_ft4 = temp_fv0_2;
    if (temp_fv0_2 > 180.0f) {
        var_ft4 = temp_fv0_2 - 360.0f;
    }
    if (var_ft4 < -180.0f) {
        var_ft4 += 360.0f;
    }
    if (sp7C.y >= 0.0f) {
        if (sp7C.y <= 180.0f) {
            var_fa1_2 = sp7C.y;
        } else {
            goto block_28;
        }
    } else {
block_28:
        var_fa1_2 = (360.0f - sp7C.y) * -1.0f;
    }
    if (sp70.y >= 0.0f) {
        if (sp70.y <= 180.0f) {
            var_fv1_3 = sp70.y;
        } else {
            goto block_33;
        }
    } else {
block_33:
        var_fv1_3 = (360.0f - sp70.y) * -1.0f;
    }
    temp_fv0_3 = var_fa1_2 - var_fv1_3;
    var_fa0 = temp_fv0_3;
    if (temp_fv0_3 > 180.0f) {
        var_fa0 = temp_fv0_3 - 360.0f;
    }
    if (var_fa0 < -180.0f) {
        var_fa0 += 360.0f;
    }
    var_s0 = 0;
    sp64 = var_ft4 / 120.0f;
    sp68 = var_fa0 / 120.0f;
    sp6C = (sp7C.z - sp70.z) / 120.0f;
loop_39:
    if (func_ovl13_01_80043830() < 2) {
        func_ovl13_01_8004B5D0(&sp70.x, &D_ovl13_01_8004C388.x);
        if (func_ovl13_01_8004B988(sp70.x, sp7C.x) == 0) {
            D_ovl13_01_8004C388.x += D_ovl13_01_8004C200.x;
            D_ovl13_01_8004C388.y = (f32) (D_ovl13_01_8004C388.y + D_ovl13_01_8004C200.y);
            D_ovl13_01_8004C388.z = (f32) (D_ovl13_01_8004C388.z + D_ovl13_01_8004C200.z);
            sp70.y += sp68;
            sp70.x += sp64;
            sp70.z += sp6C;
            func_ovl13_01_8004B7D0();
            var_s0 += 1;
            if (var_s0 == 0x78) {
                goto block_43;
            }
            goto loop_39;
        }
block_43:
        D_ovl13_01_8004C2A8 = 2.0f;
        D_ovl13_01_8004C2A0 = 1;
        D_ovl13_01_8004C2A4 = 4.0f;
        func_ovl13_01_80043124(0xBF, D_ovl13_01_8004C31C);
        if (func_ovl13_01_8004BA10(0x41F) != 0) {
            func_ovl13_01_8004B7A8(0x5A);
        } else {
            func_ovl13_01_8004B7A8(0x28);
        }
        D_ovl13_01_8004C2A0 = 1;
        D_ovl13_01_8004C2A4 = 0.0f;
        sp58.x = D_ovl13_01_8004C200.x;
        sp58.y = D_ovl13_01_8004C200.y + 12.75f;
        sp58.z = D_ovl13_01_8004C200.z;
        func_ovl13_01_8004B5C8(&D_ovl13_01_8004C388.x, &sp58.x, &sp7C.x);
        temp_fv0_4 = sp7C.y - 90.0f;
        if (temp_fv0_4 >= 360.0f) {
            sp7C.y = temp_fv0_4 - 360.0f;
        } else {
            if (sp7C.y < 90.0f) {
                var_fv1_4 = temp_fv0_4 + 360.0f;
            } else {
                var_fv1_4 = temp_fv0_4;
            }
            sp7C.y = var_fv1_4;
        }
        D_ovl13_01_8004C2A8 = 0.0f;
        sp4C = 70.0f;
        var_fv0 = 70.0f;
        if (func_ovl13_01_8004BA10(0x41F) != 0) {
            D_ovl13_01_8004C2A8 = 0.0f;
            var_fv0 = 70.0f * 1.5f;
        }
        temp_fv1 = 1150.0f / (var_fv0 * 0.5f);
        sp54 = temp_fv1;
        sp50 = (temp_fv1 / var_fv0) * -1.0f;
        func_ovl13_01_8004BA08(0x415);
        func_ovl13_01_8004306C(0);
        func_ovl13_01_8004B638(D_ovl13_01_8004C31C, 0x04000000);
        if (func_ovl13_01_8004B5E0(&D_ovl13_01_8004C388.x, &D_ovl13_01_8004C260.x) < 2000.0f) {
loop_55:
            if (sp54 > 0.0f) {
                func_ovl13_01_8004B748(D_ovl13_01_8004C360);
            }
            if ((func_ovl13_01_80043830() >= 2) || (D_ovl13_01_8004C28C <= 0)) {
                D_ovl13_01_8004C2A8 = 0.5f;
                if (D_ovl13_01_8004C3BC != 1) {
                    func_ovl13_01_8004306C(1);
                    func_ovl13_01_8004B638(D_ovl13_01_8004C31C, 0x04000000);
                }
            } else {
                if ((D_ovl13_01_8004C3BC != 1) && (sp54 <= 0.0f)) {
                    func_ovl13_01_8004306C(1);
                    func_ovl13_01_8004B638(D_ovl13_01_8004C31C, 0x04000000);
                    var_s0_2 = 0;
                    if (func_ovl13_01_8004AF00(func_ovl13_01_8004AE18()) != 0) {
                        do {
                            func_ovl13_01_8004B788(func_ovl13_01_800471D8, D_ovl13_01_8004C31C, 0, 0, 0x150);
                            var_s0_2 += 1;
                        } while (var_s0_2 != 2);
                    }
                }
                func_ovl13_01_8004377C(&D_ovl13_01_8004C388.x, &sp7C.x, &sp54, &sp50);
                func_ovl13_01_8004B7D0();
                if (!(func_ovl13_01_8004B5E0(&D_ovl13_01_8004C388.x, &D_ovl13_01_8004C260.x) < 2000.0f)) {

                } else {
                    goto loop_55;
                }
            }
        }
        D_ovl13_01_8004C2A0 = 1;
        func_ovl13_01_8004BA00(0x415);
        D_ovl13_01_8004C2A8 = 0.5f;
        D_ovl13_01_8004C2A4 = 1.0f;
    }
}

s32 func_ovl13_01_80043830(void) {
    s32 sp1C;
    s32 temp_v0;
    s32 var_v1;

    sp1C = func_ovl13_01_800437FC(D_ovl13_01_8004C31C);
    temp_v0 = func_ovl13_01_800437FC(D_ovl13_01_8004C338);
    var_v1 = sp1C;
    if (var_v1 < temp_v0) {
        var_v1 = temp_v0;
    }
    return var_v1;
}

s32 func_ovl13_01_800437FC(UnkStructA *arg0) {
    s32 ret = 0;

    if ((arg0->unk10 & 2) && (arg0->unk10 & 0x1E00)) {
        ret = (arg0->unk10 & 0x2000) ? 2 : 1;
    }
    return ret;
}

void func_ovl13_01_8004377C(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    Vec3f sp1C;

    arg1[2] = (f32) *arg2;
    *arg2 += *arg3;
    func_ovl13_01_8004B5D0(arg1, &sp1C.x);
    arg0[0] += sp1C.x;
    arg0[1] = (f32) (arg0[1] + sp1C.y);
    arg0[2] = (f32) (arg0[2] + sp1C.z);
}

void func_ovl13_01_80043608(void) {
    f32 sp20;

    if (func_ovl13_01_8004BA10(0x400) == 0) {
        D_ovl13_01_8004C388.x = D_ovl13_01_8004C368.x;
        D_ovl13_01_8004C388.y = (f32) D_ovl13_01_8004C368.y;
        D_ovl13_01_8004C388.z = (f32) D_ovl13_01_8004C368.z;
        D_ovl13_01_8004C398.x = D_ovl13_01_8004C388.x;
        D_ovl13_01_8004C398.y = (f32) D_ovl13_01_8004C388.y;
        D_ovl13_01_8004C398.z = (f32) D_ovl13_01_8004C388.z;
        func_ovl13_01_8004BA08(0x41A);
        func_ovl13_01_8004B540(D_ovl13_01_8004C31C);
        func_ovl13_01_8004B4D8(0x30);
        func_ovl13_01_8004B478(D_ovl13_01_8004C388.x, D_ovl13_01_8004C388.y, D_ovl13_01_8004C388.z);
        func_ovl13_01_8004B468(0);
        func_ovl13_01_8004B488(D_ovl13_01_8004C388.x + 1500.0f, D_ovl13_01_8004C388.y - 1000.0f, D_ovl13_01_8004C388.z + 4000.0f);
        sp20 = func_ovl13_01_8004B5E0(&D_ovl13_01_8004C260.x, &D_ovl13_01_8004C388.x);
        func_ovl13_01_8004B528(D_ovl13_01_8004C260.x, D_ovl13_01_8004C260.z, sp20, func_ovl13_01_8004B5E0(&D_ovl13_01_8004C260.x, &D_ovl13_01_8004C388.x) + 100.0f);
        D_ovl13_01_8004C240.y = 90.0f;
        D_ovl13_01_8004C240.x = 0.0f;
        D_ovl13_01_8004C240.z = 200.0f;
        func_ovl13_01_8004B518(&D_ovl13_01_8004C240.x);
        func_ovl13_01_8004BA88(0, 0, 0, 100.0f);
    }
}

void func_ovl13_01_800431D4(void) {
    s32 sp124;
    f32 sp11C;
    f32 frames;
    Vec3f sp108;
    Vec3f spFC;
    Move_ovl13_01 sp74;
    s32 sp70;
    s32 sp6C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fs3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s3;
    s32 var_s4;

    if (func_ovl13_01_8004BA10(0x400) == 0) {
        func_ovl13_01_8004B788(func_ovl13_01_80043010, NULL, 0, 0, 0x150);
        var_fs3 = 100.0f;
        var_s3 = 0;
        var_s4 = 0;
        var_s0 = 0;
        frames = 300.0f;
        sp11C = (D_ovl13_01_8004C378.z - D_ovl13_01_8004C368.z) / frames;
        if (D_ovl13_01_8004C388.z < D_ovl13_01_8004C378.z) {
            var_s1 = sp124;
            sp70 = frames * 0.95f;
            sp6C = frames * 0.25f;
            do {
                func_ovl13_01_8004BA88(0, 0, 0, var_fs3);
                D_ovl13_01_8004C388.z = (f32) (D_ovl13_01_8004C388.z + sp11C);
                if (var_fs3 > 0.0f) {
                    var_fs3 -= 2.5f;
                }
                if (var_fs3 <= 0.0f) {
                    var_fs3 = 0.0f;
                }
                if (sp6C < var_s0) {
                    if (var_s4 == 0) {
                        var_s4 = 1;
                        func_ovl13_01_8004B788(func_ovl13_01_80043158, NULL, 0, 0, 0x150);
                    }
                }
                if ((sp70 < var_s0) && (var_s3 == 0)) {
                    var_s3 = 1;
                    var_s1 = 0xBF;
                    func_ovl13_01_8004B540(NULL);
                    func_ovl13_01_8004B4E0(0x30);
                    func_ovl13_01_8004B570(&spFC.x);
                    func_ovl13_01_8004B580(&sp108.x);
                    temp_fv0 = (2300.0f - spFC.x) / 60.0f;
                    sp74.unk0 = 0x78;
                    sp74.unk4 = 1;
                    temp_fv1 = (856.0f - spFC.y) / 60.0f;
                    sp74.unk8 = 0;
                    sp74.unk3C = 0;
                    sp74.unk40 = 0;
                    sp74.unkC[0] = temp_fv0;
                    sp74.unkC[1] = temp_fv1;
                    temp_fa0 = (1500.0f - spFC.z) / 60.0f;
                    sp74.unk18[0] = (temp_fv0 / 120.0f) * -1.0f;
                    sp74.unkC[2] = temp_fa0;
                    sp74.unk18[1] = (temp_fv1 / 120.0f) * -1.0f;
                    temp_fa1 = (2300.0f - sp108.x) / 60.0f;
                    sp74.unk18[2] = (temp_fa0 / 120.0f) * -1.0f;
                    temp_ft4 = (1772.0f - sp108.y) / 60.0f;
                    sp74.unk24[0] = temp_fa1;
                    sp74.unk24[1] = temp_ft4;
                    temp_ft5 = (3900.0f - sp108.z) / 60.0f;
                    sp74.unk30[0] = (temp_fa1 / 120.0f) * -1.0f;
                    sp74.unk24[2] = temp_ft5;
                    sp74.unk30[1] = (temp_ft4 / 120.0f) * -1.0f;
                    sp74.unk30[2] = (temp_ft5 / 120.0f) * -1.0f;
                    func_ovl13_01_8004B4B0(&sp74, 0x170, 0);
                    func_ovl13_01_8004BAE0(1);
                    func_ovl13_01_8004BAE8(0xBF);
                }
                func_ovl13_01_8004B7D0();
                var_s0 += 1;
            } while (D_ovl13_01_8004C388.z < D_ovl13_01_8004C378.z);
            sp124 = var_s1;
        }
        var_s1_2 = sp124;
        func_ovl13_01_8004B4D0();
        func_ovl13_01_8004B488(2300.0f, 1772.0f, 3900.0f);
        D_ovl13_01_8004C24C = 1.0f;
        func_ovl13_01_8004B468(1);
        func_ovl13_01_8004BA00(0x41A);
        if (var_s1_2 >= 0) {
            do {
                func_ovl13_01_8004BAE8(var_s1_2);
                func_ovl13_01_8004B7D0();
                var_s1_2 -= 8;
            } while (var_s1_2 >= 0);
        }
        func_ovl13_01_8004BAE0(0);
        if (func_ovl13_01_8004B9F0(0xA4) != 0) {
            func_ovl13_01_8004B7A8(0xA);
        }
    }
}

void func_ovl13_01_80043158(void) {
    func_ovl13_01_8004306C(0);
    func_ovl13_01_8004B638(D_ovl13_01_8004C31C, 0x04000000);
    func_ovl13_01_8004B7A8(0x14);
    func_ovl13_01_80043124(0xD8, D_ovl13_01_8004C31C);
    func_ovl13_01_800430CC(D_ovl13_01_8004C31C);
    func_ovl13_01_8004306C(1);
    func_ovl13_01_8004B638(D_ovl13_01_8004C31C, 0x04000000);
    func_ovl13_01_8004B798();
}

void func_ovl13_01_80043124(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *temp_v0;

    temp_v0 = arg1->unk40;
    func_ovl13_01_8004BD30(arg0, temp_v0->unk10, temp_v0->unk14, temp_v0->unk18);
}

static void func_ovl13_01_800430CC(UnkStructA *arg0) {
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x40)) {
        do {
            func_ovl13_01_8004B7D0();
        } while (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x40));
    }
}

void func_ovl13_01_8004306C(s32 arg0) {
    D_ovl13_01_8004C3BC = arg0;
    func_ovl13_01_8004B360(D_ovl13_01_8004C31C->unk40, arg0, 0);
    func_ovl13_01_8004B640(D_ovl13_01_8004C31C, 0x0C000000);
    func_ovl13_01_8004B378(D_ovl13_01_8004C31C->unk40, 0);
}

void func_ovl13_01_80043010(void) {
    if (!(*D_ovl13_01_8004C23C & 2)) {
        if (func_ovl13_01_8004B9F0(0xA4) == 0) {
            func_ovl13_01_8004B7A8(0x73);
        }
        func_ovl13_01_8004BD20(0x2A);
    }
    func_ovl13_01_8004B798();
}

