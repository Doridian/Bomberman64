/*
 * NON_MATCHING: main_code's 54E40, complete: 72 functions (us
 * 0x8023A640-0x80243888): tasks spawned through func_80238A10 and
 * func_8022A328, and the display lists of three digit counters. Not
 * built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 8550, eu 8551, jp 8564
 *
 * A first draft: m2c's functions in the reverse of the ROM's order (IDO
 * -O3 emits last to first), with the fixes the -O3 build needs; 26 of 72
 * match in us. It is one object: the only callee emitted after its
 * caller is func_8024364C (called by func_8023F26C), and the IPA statics
 * (func_8023AB54, B2AC, B318, B450 take arguments in s2/fs0/t0, called by
 * func_8023FD08; func_8023E8FC in s4, called by func_80242FB4) tie
 * 0x8023AB54-0x80242FB4 together, so no 16-aligned cut is possible.
 *
 * The emission order is the original's. IDO -O3 emits the global
 * functions in reverse source order, each after its callees (depth
 * first, the callees last called first); statics only come out as
 * callees. With an indirect call in the file (func_8024364C's hook
 * D_802AC768), taking a function's address is no edge; the indirect
 * caller calls every function whose address code takes, in the reverse
 * order of their first reference in the source (references in .data
 * don't count). So func_8024364C is defined just below func_8023F26C (its
 * turn starts the run func_8023F26C .. func_802434F8), and
 * func_80243824, the first function in the file, holds dead references
 * that set that order; dead calls (seen by umerge, removed by uopt) pull
 * func_8023AB54 into func_8023AB90, func_8023B2AC into func_8023B318,
 * func_8023EB28 into func_8023ECEC and func_80242268 into func_80242270.
 * - func_80241590, 80241BB0, 80242270 (digit counters over 16x16
 *   pictures) are written with the GBI macros (gDPLoadTLUT_pal256/pal16,
 *   gDPLoadTextureBlock_4b, gDPLoadTextureTile_4b, gSPTextureRectangle)
 *   over TexFile (7C4D0's) D_802A0758 and D_802A075C; the digits go to
 *   D_802AC770 as entry indices (digit * 2). func_80242270's original
 *   frame is 0x128 with only 0x34 used.
 * - The IPA statics (func_8023AB54, AF5C, B2AC, B318, B450, B7C0, E8FC,
 *   EB28, ECF4, EE40, EF38) are static; func_8023AF5C takes its first
 *   argument in fs5 and its second at 0x4(sp) of the caller.
 * - jp: func_802434F8 calls func_802810A0 (us's wrapper func_802811F0
 *   doesn't exist) with the x fixed; the other uses of func_802811F0
 *   (func_8023FD08, 8023F26C) and jp's own text in func_8023AEDC,
 *   8023C374 and 8023ECEC have no jp arm yet.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

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

/* A picture drawn by func_80242270: its entry and its rectangle. */
typedef struct {
    /* 0x00 */ s32 idx;
    /* 0x04 */ s32 xl;
    /* 0x08 */ s32 yl;
    /* 0x0C */ s32 xh;
    /* 0x10 */ s32 yh;
} Rect54E40; /* size 0x14 */

s32 func_802810A0(u8 *, u16, u16, f32, f32, u8);

void func_802268F4(void);
void func_8022691C(s32);
void func_802276E0(s32, s32, s32);
void func_802276FC(s32);
void func_80227870(void);
void func_80227C18(void);
void func_80227EE0(s32);
void func_80227F88(void);
void func_80228008(s32, s32, s32);
s32 func_802280F4(s32, s32);
void func_80229280(s32);
s32 func_8022979C(s32, s32, s32);
void func_80229E38(void *, s32, s32);
void * func_8022A328(void *, s32, s32, s32, s32);
s32 func_8022F550(s32, s32);
void func_8022FC90(void *);
void func_8022FDE8(void);
void func_80230914(void *);
void * func_80231274(s32, s32, s32, void *);
void func_802313DC(void *, s32);
void func_80231408(void *, s32);
s32 func_80232D18(void *, s32);
void func_802346C8(f32, f32, f32);
void func_80234778(f32, f32, f32);
void func_80234858(f32 *, f32 *, f32 *);
void func_802348B4(f32 *, f32 *, f32 *);
s32 func_80234DD4(f32, f32, f32, void *);
void func_80234F6C(s32);
void func_802350F8(s32);
void func_80236218(s32);
s32 func_802362A8(void);
void func_802362B8(s32);
void func_80236B7C(void);
s32 func_80238A10(void *, s32, s32, s32, s32);
s32 func_80238CF8(s32, s32);
s32 func_80238DFC(s32, s32, u32);
void func_80238EA8(s32);
s32 func_80238F40(s32, s32);
void func_8023903C(s32);
void func_80239094(void);
s32 func_802391F0(void);
void func_80239430(void);
s32 func_802399AC(s32);
s32 func_80239FF8(s32);
u8 func_8023A038(s32);
void func_80243A30(void);
s32 func_80243DDC(void);
void func_80243E90(s32);
s32 func_80243EF0(s32);
s32 func_802441AC(void *);
void * func_802443F4(s32);
void func_802444B8(s32, s32);
s32 func_80244BA4(s32, s32);
void func_80244C30(s32, s32);
void func_80245208(s32, s32);
void func_80245280(s32);
void func_802452E8(s32);
void func_8024585C(s32);
void func_80245868(void);
void func_802459BC(s32);
void func_80246D74(s16);
void func_80247C50(s32);
void func_80250338(s32, void *);
void func_802510F0(void);
void func_802513E0(void);
void func_802514CC(void);
void func_80251534(s32);
void func_80251804(s32);
void func_8025C590(s32);
f64 func_8025E63C(void);
void func_8026BF28(s8);
void func_8026BF68(s8);
void func_8026BF90(s8);
void func_8026C394(void);
s32 func_8026C660(s32);
void func_8026C6D0(s32);
void func_8026C894(void);
void func_8026C8E8(void);
void func_8026C93C(s32);
void func_8026C964(void);
void func_8026CB2C(void);
void func_8026CF90(void);
void func_8026D5B4(s32);
s32 func_8026D7D8(s32, s32, s32);
void func_8026DCAC(f32, f32, f32, void *, s32);
void func_8026E338(f32, f32, f32, f32 *, s32);
f32 func_8026E8B8(void);
f32 func_8026E938(void *);
void func_8026F02C(void);
s32 func_80270770(s16, s16);
void func_80277484(void);
void func_8027783C(void);
void func_80277AF8(s16, s16);
void func_80277DF4(s16);
void func_80277E1C(void);
s32 func_80278E84(s32, s32);
void func_8027BBC4(void);
void func_8027EBCC(void);
s32 func_8027EFA8(void);
void func_8027F400(void);
void func_8027F428(void);
void func_8027F658(void *, void *, u16, u16, u16);
void func_8027F79C(void);
void func_8027F820(void);
void func_8027F858(s32, s32);
void func_8027FC08(void);
s32 func_80280C08(u8 *);
s32 func_80280DB4(s32);
void func_80280EB0(s32, u16, u16);
s32 func_802811F0(u8 *, u16, u16, f32, f32, u8);
void func_802814D8(s32, u16, u16);
void func_80281A40(void);
void func_80281A88(s32, s32, s32, s32);
void func_80281AE0(s32, s32, s32, s32);
void func_802822B0(s32);
void func_80282430(void *, s32, s32);
void * func_802867E4(s32, f32, f32, f32);
void func_80286E60(void);
void func_80286EF0(void);
s32 func_80286F04(void);
s32 func_80287008(s32, s32, s32);
s32 func_802871D0(s32);
s32 func_80287680(void);
void func_8028785C(void);
s32 * func_8028A060(s32);
void func_8028A0B4(void);
s32 func_8028A36C(s32);
void func_8028A3D0(s32);
void func_8028A428(s32);
s32 func_8028A4E0(s32);
void func_8028A584(void);
s32 func_8028A81C(s32, f32, f32, f32, s32);
s32 func_8028E8E0(void);
s32 func_802909FC(s32);
void func_80291944(void *, s32, f32);
void func_8029236C(void);
void func_802923CC(void);
s32 func_8029279C(void *, s32, s32, s32, f32);
s32 func_802947AC(void);
s32 func_80294CE8(s32);
s32 func_80295330(s32);
void func_80295384(void);

extern u8 D_1000000[];
extern u8 D_800AEBBC[];
extern u8 D_800AED4C[];
extern u8 D_800AEDF0[];
extern s32 D_800AEE04;
extern s32 D_800AEE14;
extern s32 D_800AEE58;
extern s32 D_800AEEDC;
extern s32 D_800AEF20;
extern s32 D_800AEFA4;
extern s32 D_800AEFE8;
extern s32 D_800AF06C;
extern s32 D_800AF0B0;
extern u8 D_800BD000[];
extern s32 D_800BE818;
extern s32 D_800BE824;
extern u8 D_800BE830[];
extern s32 D_802A0038;
extern s32 D_802A01B0;
extern s32 D_802A01B4;
extern s32 D_802A01B8;
extern s32 D_802A01BC;
extern s32 D_802A01C0;
extern u8 D_802A01C4;
extern u8 D_802A01D0;
extern u8 D_802A01D8;
extern u8 D_802A01E0;
extern u8 D_802A039C;
extern u8 D_802A0448;
extern u8 D_802A04A4;
extern u8 D_802A04B4;
extern u8 D_802A04C8[];
extern u8 D_802A063C[];
extern s32 D_802A0654;
extern u8 D_802A0658[];
extern u8 D_802A0748[];
extern u8 D_802A0750[];
extern TexFile *D_802A0758;
extern TexFile *D_802A075C;
extern u8 *D_802A0760;
extern s32 D_802A0764[2];
extern s32 D_802A076C[2];
extern Rect54E40 D_802A0774[2];
extern s32 D_802A079C[7];
extern s32 D_802A07B8[7];
extern Rect54E40 D_802A07D4[5];
extern s32 D_802A0838[5];
extern u8 D_802A084C[];
extern u8 D_802A0888[];
extern s32 D_802A08D8[5];
extern u8 D_802A08E4[];
extern u8 D_802A08EC[];
extern u8 D_802A08F8[];
extern u8 D_802A0958[];
extern u8 D_802A09B8[];
extern u8 *D_802A0A18;
extern u8 *D_802A0A68;
extern u8 *D_802A0A7C;
extern u8 *D_802A0AB8;
extern u8 *D_802A0ACC;
extern u8 *D_802A0B1C;
extern s32 D_802A0B40;
extern s32 D_802A0B80;
extern u8 D_802A0B84[];
extern s32 D_802A0B94;
extern u8 D_802A0B98[];
extern u8 D_802A0BA8[];
extern u8 D_802A0C00[];
extern u8 D_802A0C2C[];
extern u8 D_802A0CB0[];
extern u8 D_802A0CC8[];
extern u8 D_802A0CF4[];
extern s32 D_802AC5CC;
extern s32 D_802AC5D0;
extern s32 D_802AC5D4;
extern s32 D_802AC5D8;
extern s32 D_802AC5DC;
extern s32 D_802AC5E0;
extern s32 D_802AC5E4;
extern s32 D_802AC5E8;
extern s32 D_802AC5EC;
extern s32 D_802AC5F0;
extern f32 D_802AC5F4;
extern f32 D_802AC5F8;
extern f32 D_802AC5FC;
extern f32 D_802AC600;
extern s32 D_802AC604;
extern s32 D_802AC608;
extern s32 D_802AC610;
extern s32 D_802AC614;
extern s32 D_802AC618;
extern s32 D_802AC620;
extern s32 D_802AC624;
extern s32 D_802AC628;
extern s32 D_802AC630;
extern s32 D_802AC638;
extern s32 D_802AC63C;
extern s32 D_802AC640;
extern s32 D_802AC648;
extern s32 D_802AC650;
extern s32 D_802AC660;
extern u8 D_802AC670[];
extern s32 D_802AC688;
extern s32 D_802AC68C;
extern s32 D_802AC690;
extern s32 D_802AC69C;
extern u8 D_802AC6A0[];
extern u8 D_802AC714[];
extern s32 D_802AC758;
extern s32 D_802AC75C;
extern s32 D_802AC760;
extern s32 (*D_802AC768)(void *);
extern s32 D_802AC770[10];
extern u8 D_802AC780[];
extern s32 D_802AC798;
extern s32 D_802AC7A0;
extern s32 D_802AC7A4;
extern u8 D_802AC7A8[];
extern s32 D_802AC7C8;
extern s32 D_802AC7CC;
extern void *D_802AC7D0;
extern void *D_802AC7D4;
extern s32 D_802AC7D8;
extern void *D_802AC7DC;
extern void *D_802AC7E0;
extern s32 D_802AC7E4;
extern s32 D_802AC7E8;
extern s32 D_802AC7EC;
extern s32 D_802AC7F0;
extern void *D_802AC7F8;
extern s32 D_802AC80C;
extern s32 D_802AC810;
extern s32 D_802AC814;
extern void *D_802AC818;
extern u8 D_802AC820[];
extern u8 D_802AC828[];
extern s32 D_802AC850;
extern s32 D_802AC854;
extern u32 D_802AC858;
extern u8 D_802AC868[];

void func_8023A640(void);
void func_8023A68C(void);
void func_8023A734(s32 arg0, s32 arg1, s32 arg2);
s32 *func_8023A834(void);
s32 *func_8023A840(void);
void func_8023A84C(s32 arg0);
void func_8023A858(s32 arg0);
void func_8023A864(s32 arg0);
s32 func_8023A870(s32 arg0, s32 arg1);
s32 func_8023AA60(s32 arg0);
void func_8023AA78(s32 arg0);
void func_8023AAE4(void);
static void func_8023AB54(u8 **arg0, s32 arg1);
s32 func_8023AB90(void);
void func_8023AC38(void);
void func_8023ADD4(s32 arg0);
void func_8023AE6C(s32 arg0, s32 arg1, s32 arg2);
void func_8023AED0(s32 arg0);
s32 func_8023AEDC(s32 arg0);
static void func_8023AF5C(f32 arg0, f32 arg1);
static s32 func_8023B2AC(f32 arg0);
static void func_8023B318(u8 **arg0, s32 arg1);
static void func_8023B450(s32 arg0, s32 arg1, u8 *arg2);
static void func_8023B7C0(f32 arg0);
void func_8023B8D0();
s32 func_8023BBCC(void);
void func_8023C170(void);
void func_8023C374(void);
void func_8023CA94(void);
void func_8023CC54(s32 arg0);
void func_8023CD1C(void);
void func_8023CECC(void);
s32 func_8023D0F8(void);
void func_8023D848(void);
void func_8023D8A0(void);
void func_8023DA04(s32 arg0);
void func_8023DB0C(void);
void func_8023E1D8(void);
void func_8023E8AC(void);
static void func_8023E8FC(f32 *arg0);
static void *func_8023EB28(s32 arg0);
void func_8023ECEC(void);
static void func_8023ECF4(u8 *arg0);
static void func_8023EE40(s32 arg0);
static void func_8023EF38(u8 *arg0);
void func_8023F26C(void);
void func_8023FAA0(void);
s32 func_8023FC00(u8 arg0, s32 arg1);
void func_8023FC80(s32 arg0, u8 **arg1);
void func_8023FD08();
void func_80240F34(void);
void func_80241180(void);
void func_80241550(void);
void func_80241590(s32 arg0, Gfx **gdl);
void func_80241BB0(s32 arg0, Gfx **gdl);
void func_80242268(void);
void func_80242270(s32 arg0, Gfx **gdl);
void func_80242994(void);
void func_80242DA8(void);
void func_80242FB4();
void func_802434F8();
void func_8024364C(u8 *arg0);
void func_8024368C(s32 (*arg0)(void *));
void func_80243698(s32 arg0);
void func_80243718(void);
void func_80243790(void);
s32 func_80243798(s32 arg0);
void func_802437C0(void);
void func_802437E0(void);
s32 func_80243800(void);
void func_80243810(s32 arg0, s32 arg1);
void func_80243824(s32 arg0);

void func_80243824(s32 arg0) {
    s32 *var_a1;
    s32 var_v1;

    if (0) {
        func_80238A10(func_802434F8, 0, 0, 0, 0);
        func_80238A10(func_80242FB4, 0, 0, 0, 0);
        func_80238A10(func_80242DA8, 0, 0, 0, 0);
        func_80238A10(func_80242270, 0, 0, 0, 0);
        func_80238A10(func_80241BB0, 0, 0, 0, 0);
        func_80238A10(func_80241590, 0, 0, 0, 0);
        func_80238A10(func_80241550, 0, 0, 0, 0);
        func_80238A10(func_80241180, 0, 0, 0, 0);
        func_80238A10(func_80240F34, 0, 0, 0, 0);
        func_80238A10(func_8023FD08, 0, 0, 0, 0);
        func_80238A10(func_8023FC80, 0, 0, 0, 0);
        func_80238A10(func_8023FC00, 0, 0, 0, 0);
        func_80238A10(func_8023FAA0, 0, 0, 0, 0);
        func_80238A10(func_8023F26C, 0, 0, 0, 0);
        func_80238A10(func_8023DB0C, 0, 0, 0, 0);
    }
    var_a1 = &(&D_802AC7A0)[D_802AC608];
    var_v1 = 0;
loop_1:
    var_v1 += 1;
    if (*var_a1 != -1) {
        var_a1 = (void *) ((u8 *)var_a1 + 4);
        if ((u32) var_a1 >= (u32) &D_802AC7C8) {
            var_a1 = &D_802AC7A0;
        }
        if (var_v1 != 0xA) {
            goto loop_1;
        }
    }
    *var_a1 = arg0;
}

void func_80243810(s32 arg0, s32 arg1) {
    D_802AC5DC = arg0;
    D_802AC5E0 = arg1;
}

s32 func_80243800() {
    return D_802AC5D8;
}

void func_802437E0() {
    func_80239FF8(0);
}

void func_802437C0() {
    func_802399AC(0);
}

s32 func_80243798(s32 arg0) {
    if (((arg0 & 0xF) == 0xF) || (arg0 & 0x60)) {
        return 0;
    }
    return 1;
}

void func_80243790() {

}

void func_80243718() {
    func_8028A0B4();
    if (D_802AC650 == 0) {
        func_80277DF4(0x407);
        if (M2C_FIELD(D_800AEDF0, s32 *, 0x20) >= 5) {
            M2C_FIELD(D_800AEDF0, s32 *, 0x20) = 4;
        }
    }
    D_802AC640 = 0;
    func_80286EF0();
    D_802AC5D0 |= 0x90;
}

void func_80243698(s32 arg0) {
    if (arg0 != 0) {
        D_802AC5D0 |= 0x40;
        func_80245280(1);
        func_80238DFC(0xB0, 0x3CF, 0U);
        return;
    }
    if (arg0 == 0) {
        D_802AC5D0 &= ~0x40;
        func_80245280(0);
        func_80238CF8(0xB0, 0x3CF);
    }
}

void func_8024368C(s32 (*arg0)(void *)) {
    D_802AC768 = arg0;
}

void func_802434F8() {
    s32 temp_s2;
    s32 var_s0;

#if VERSION_JP
    temp_s2 = func_802810A0(D_802A08EC, 0x140, 0x6E, 0.8f, 0.8f, 3);
#else
    temp_s2 = func_802811F0(D_802A08EC, 0x140U, 0x6EU, 0.8f, 0.8f, 3U);
#endif
    func_8026C964();
    func_8026C660(0x1E9);
    var_s0 = 0xF0;
loop_1:
    if (!(D_802AC5D0 & 0x10)) {
#if VERSION_JP
        func_80280EB0(temp_s2, 0x49, var_s0 & 0xFFFF);
#else
        func_80280EB0(temp_s2, (s32) ((320.0f - ((f32) func_80280C08(D_802A08EC) * 0.8f)) / 2.0f) & 0xFFFF, var_s0 & 0xFFFF);
#endif
        func_80239094();
        var_s0 -= 4;
        if (var_s0 != 0) {
            goto loop_1;
        }
    }
    func_8026C93C(0x1C);
    func_80280DB4(temp_s2);
    func_80239430();
}

void func_80242FB4() {
    s32 spA4;
    s32 spA0;
    u8 *sp98;
    s32 sp94;
    f32 sp88[3];
    s32 sp78;
    f32 *temp_s1;
    f32 temp_ft1;
    s32 *var_v0;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    u8 *temp_v0_4;
    s32 temp_v0_7;
    s32 temp_v1_2;
    u8 *var_s1;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s3;
    s32 var_s5;
    u8 temp_v1_3;
    void **var_s0;
    u8 *temp_a0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_8;
    u8 *temp_v1;
    u8 *var_s0_2;
    u8 *var_s0_3;

    var_s3 = 5;
    temp_v0 = func_802391F0();
    temp_a0 = temp_v0 - 1;
    var_s5 = temp_a0;
    func_80287008(temp_a0, 0x19, temp_v0 + 0x1D);
    temp_v0_2 = var_s5 * 4;
    var_s0 = (var_s5 * 0x14) + D_802AC828;
    temp_s1 = temp_v0_2 + D_802A0748;
    var_s2 = 0;
    do {
        temp_v0_3 = func_80231274(0x130, 0x01000000, 0xD0, NULL);
        *var_s0 = temp_v0_3;
        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 0x40), f32 *, 0x10) = (f32) *temp_s1;
        temp_ft1 = ((f32) var_s2 * 24.0f) + 40.0f;
        var_s2 += 1;
        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 0x40), f32 *, 0x14) = temp_ft1;
        var_s0 += 4;
        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 0x40), f32 *, 0x18) = (f32) (*temp_s1 + 16.0f);
        temp_v1 = M2C_FIELD(temp_v0_3, void **, 0x40);
        M2C_FIELD(temp_v1, f32 *, 0x1C) = (f32) (M2C_FIELD(temp_v1, f32 *, 0x14) + 16.0f);
        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 0x40), s32 *, 0x38) = (s32) *(temp_v0_2 + D_802A0750);
    } while (var_s2 != 5);
    var_s1 = sp98;
    sp78 = var_s5 * 4;
loop_3:
    var_v0 = &D_802AC660;
loop_4:
    if ((M2C_FIELD(var_v0, s32 *, 4) != 0) && (var_s5 == M2C_FIELD(var_v0, s32 *, 0x90))) {
        spA0 = 0;
        sp94 = var_s3;
        spA4 = var_s5;
        func_8023E8FC(sp88);
        var_s2_2 = spA0;
        var_s3 = sp94;
        var_s5 = spA4;
        func_80286EF0();
        temp_v0_4 = (u8 *) func_802867E4(var_s5, sp88[0], sp88[1] + 1500.0f, sp88[2]);
        var_s1 = temp_v0_4;
        if (temp_v0_4 == 0) {
            func_80239094();
            goto loop_3;
        }
        *(u8 **)(D_802AC820 + sp78) = var_s1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_s1, void **, 0), void **, 0x40), f32 *, 0x10) = sp88[0];
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_s1, void **, 0), void **, 0x40), f32 *, 0x18) = sp88[2];
        if (func_8022F550((s32) M2C_FIELD(var_s1, void **, 0), 0x10) != 0) {
            do {
                temp_v0_5 = M2C_FIELD(M2C_FIELD(var_s1, void **, 0), void **, 0x40);
                M2C_FIELD(temp_v0_5, f32 *, 0x14) = (f32) (M2C_FIELD(temp_v0_5, f32 *, 0x14) + 100.0f);
            } while (func_8022F550((s32) M2C_FIELD(var_s1, void **, 0), 0x10) != 0);
        }
        M2C_FIELD(var_s1, s8 *, 0x6D) = (s8) var_s3;
        func_80282430((void *) var_s1, 0xF, 3);
        M2C_FIELD(var_s1, s16 *, 0x6E) = 0x3C;
        M2C_FIELD(var_s1, s8 *, 0x78) = 1;
        func_80231408(M2C_FIELD(var_s1, void **, 0), 0x0C040000);
    } else {
        var_v0 = (void *) ((u8 *)var_v0 + 4);
        if ((s32) var_v0 == (s32) D_802AC670) {
            var_s2_2 = 0;
        } else {
            goto loop_4;
        }
    }
loop_13:
    temp_v1_2 = func_802871D0(var_s1) & 3;
    if (temp_v1_2 == 3) {
        var_s3 = (s32) M2C_FIELD(var_s1, u8 *, 0x6D);
        goto loop_3;
    }
    if ((temp_v1_2 == 0) && (var_s3 != 0)) {
        if ((M2C_FIELD(var_s1, u8 *, 0x7A) & 0xF) == 3) {
            temp_v1_3 = M2C_FIELD(var_s1, u8 *, 0x6D);
            if (var_s3 != temp_v1_3) {
                if ((var_s3 - temp_v1_3) > 0) {
                    var_s0_2 = (var_s5 * 0x14) + (var_s3 * 4) + D_802AC828;
                    do {
                        func_8022FC90(M2C_FIELD(var_s0_2, void **, -4));
                        var_s2_2 += 1;
                        var_s0_2 -= 4;
                    } while (var_s2_2 < (var_s3 - M2C_FIELD(var_s1, u8 *, 0x6D)));
                }
                temp_v0_6 = M2C_FIELD(var_s1, void **, 0x68);
                if (temp_v0_6 != NULL) {
                    M2C_FIELD(temp_v0_6, f32 *, 0x1C) = 0.0f;
                }
                temp_a0_2 = M2C_FIELD(M2C_FIELD(var_s1, void **, 0), void **, 0x44);
                if (temp_a0_2 != NULL) {
                    temp_v0_7 = func_802441AC(temp_a0_2);
                    func_80244C30(temp_v0_7, 0);
                    func_802444B8(temp_v0_7, 0);
                }
                sp98 = var_s1;
                spA0 = 0;
                sp94 = (s32) M2C_FIELD(var_s1, u8 *, 0x6D);
                spA4 = var_s5;
                func_8023E8FC(sp88);
                var_s1 = sp98;
                var_s2_2 = spA0;
                var_s3 = sp94;
                var_s5 = spA4;
                M2C_FIELD(M2C_FIELD(*(void **)var_s1, void **, 0x40), f32 *, 0x10) = sp88[0];
                M2C_FIELD(M2C_FIELD(*(void **)var_s1, void **, 0x40), f32 *, 0x14) = (f32) (sp88[1] + 600.0f);
                M2C_FIELD(M2C_FIELD(*(void **)var_s1, void **, 0x40), f32 *, 0x18) = sp88[2];
                if (func_8022F550((s32) *(void **)var_s1, 0x10) != 0) {
                    do {
                        temp_v0_8 = M2C_FIELD(*(void **)var_s1, void **, 0x40);
                        M2C_FIELD(temp_v0_8, f32 *, 0x14) = (f32) (M2C_FIELD(temp_v0_8, f32 *, 0x14) + 100.0f);
                    } while (func_8022F550((s32) *(void **)var_s1, 0x10) != 0);
                }
            }
        }
        func_80239094();
        goto loop_13;
    }
    if ((var_s3 - M2C_FIELD(var_s1, u8 *, 0x6D)) > 0) {
        var_s0_3 = (var_s5 * 0x14) + (var_s3 * 4) + D_802AC828;
        do {
            func_8022FC90(M2C_FIELD(var_s0_3, void **, -4));
            var_s2_2 += 1;
            var_s0_3 -= 4;
        } while (var_s2_2 < (var_s3 - M2C_FIELD(var_s1, u8 *, 0x6D)));
    }
    *(s32 *)((u8 *)&D_802AC760 + sp78) = 0;
    func_80239430();
}

void func_80242DA8() {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;

    D_802AC850 = 0;
    D_802AC854 = 0;
    if (D_802AC660 == 0) {
        temp_v1 = D_802AC758;
        if (temp_v1 >= 2) {
            do {
                func_80239094();
            } while (D_802AC758 >= 2);
        }
        var_s0 = 0;
        if (temp_v1 > 0) {
loop_5:
            if ((func_80243EF0(var_s0) != 0) || ((temp_v0 = M2C_FIELD((D_800AEDF0 + (var_s0 * 0xC8)), s32 *, 0x24), (temp_v0 != 1)) && (temp_v0 != 2))) {
                var_s0 += 1;
                if (var_s0 != 4) {
                    goto loop_5;
                }
            }
            D_802AC850 = 1;
            func_8023903C(0x1E);
            if ((func_80243EF0(var_s0) == 0) && ((temp_v0_2 = M2C_FIELD((D_800AEDF0 + (var_s0 * 0xC8)), s32 *, 0x24), (temp_v0_2 == 1)) || (temp_v0_2 == 2))) {
                func_8024585C(var_s0);
                func_80247C50(var_s0);
                func_802452E8(1);
            }
        }
    } else {
        if ((M2C_FIELD(&D_802AC760, s32 *, 0) != 0) && (M2C_FIELD(&D_802AC760, s32 *, 4) != 0)) {
loop_15:
            func_80239094();
            if (M2C_FIELD(&D_802AC760, s32 *, 0) != 0) {
                if (M2C_FIELD(&D_802AC760, s32 *, 4) == 0) {

                } else {
                    goto loop_15;
                }
            }
        }
        D_802AC850 = 1;
        func_8023903C(0x3C);
        if ((M2C_FIELD(&D_802AC760, s32 *, 0) != 0) || (M2C_FIELD(&D_802AC760, s32 *, 4) != 0)) {
            func_80238DFC(0xD0, 0xD0, 0U);
        }
    }
    func_80242994();
    func_80239430();
}

void func_80242994() {
    u8 *var_s1;
    u8 *var_s1_2;
    u8 *var_s1_3;
    s32 *var_v0;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s2;
    u8 *temp_v0_3;

    if (D_802AC854 == 0) {
        D_802AC5D0 |= 0x10;
        func_80238DFC(0x70, 0x70, 0U);
        func_802510F0();
        var_s1 = D_800AEDF0;
        var_s0 = 0;
        do {
            temp_v0 = M2C_FIELD(var_s1, s32 *, 0x24);
            if ((temp_v0 == 1) || (temp_v0 == 2)) {
                func_8024585C(var_s0);
                func_80247C50(var_s0);
                func_802452E8(1);
            }
            var_s0 += 1;
            var_s1 += 0xC8;
        } while (var_s0 < 4);
        var_s1_2 = D_800AEDF0;
        var_s0_2 = 0;
        var_s2 = 0;
        do {
            temp_v0_2 = M2C_FIELD(var_s1_2, s32 *, 0x24);
            if ((temp_v0_2 != 0) && (temp_v0_2 != 3) && (func_80243EF0(var_s0_2) == 0)) {
                var_s2 += 1;
            }
            var_s0_2 += 1;
            var_s1_2 += 0xC8;
        } while (var_s0_2 < 4);
        if (((D_802AC660 == 0) && (var_s2 != 1)) || ((D_802AC660 == 1) && (M2C_FIELD(&D_802AC760, s32 *, 0) == 0) && (M2C_FIELD(&D_802AC760, s32 *, 4) == 0))) {
            func_8023903C(0x3C);
            func_8026C660(0x1E6);
            func_8023903C(0x32);
            func_8026C93C(0x21);
            func_8023903C(0x3C);
            temp_v0_3 = func_8022A6C4(func_8026CE28(0x3E), 0);
            M2C_FIELD(temp_v0_3, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_3, s32 *, 0xC) | 0x100);
            M2C_FIELD(temp_v0_3, f32 *, 0x28) = 0.1f;
            M2C_FIELD(temp_v0_3, f32 *, 0x2C) = 0.1f;
            M2C_FIELD(temp_v0_3, f32 *, 0x30) = 0.1f;
            M2C_FIELD(temp_v0_3, s16 *, 0x34) = (s16) D_802AC5CC;
            M2C_FIELD(temp_v0_3, f32 *, 0x10) = 0.0f;
            M2C_FIELD(temp_v0_3, f32 *, 0x14) = 0.0f;
            M2C_FIELD(temp_v0_3, f32 *, 0x18) = 0.0f;
            var_s0_3 = 0;
            do {
                if (var_s0_3 == 0x28) {
                    func_8026C660(0x1DD);
                }
                M2C_FIELD(temp_v0_3, f32 *, 0x18) = (f32) ((f32) var_s0_3 * 7.4074073f);
                func_80239094();
                var_s0_3 += 1;
            } while (var_s0_3 != 0x87);
            func_8022A1E8(temp_v0_3);
            func_8026CCBC(0x3E);
            func_8026C8E8();
            func_8026C894();
            temp_v1 = D_802AC5D4;
            temp_a0 = D_802AC5D8;
            if (!(D_802AC5D0 & 1) && (D_802A01B4 == 0)) {
                D_802AC5D4 = temp_v1;
                D_802AC5DC = temp_v1;
                D_802AC5D8 = temp_a0;
                D_802AC5E0 = temp_a0;
                D_802AC5D0 |= 1;
                goto block_39;
            }
        } else if (D_802AC660 == 0) {
            func_8026C660(0x1E5);
            func_8023903C(0x3C);
            func_8026C8E8();
            func_8026C894();
            var_s1_3 = D_800AEDF0;
            var_s0_4 = 0;
loop_26:
            temp_v0_4 = M2C_FIELD(var_s1_3, s32 *, 0x24);
            if ((temp_v0_4 == 0) || (temp_v0_4 == 3) || (func_80243EF0(var_s0_4) != 0)) {
                var_s0_4 += 1;
                var_s1_3 += 0xC8;
                if (var_s0_4 != 4) {
                    goto loop_26;
                }
            }
            if (!(D_802AC5D0 & 1)) {
                if (D_802A01B4 == 0) {
                    D_802AC5D4 = 0x22;
                    D_802AC5DC = D_802AC5D4;
                    D_802AC5D8 = var_s0_4 + 0x11;
                    D_802AC5E0 = D_802AC5D8;
                    D_802AC5D0 |= 1;
                    goto block_39;
                }
            }
        } else {
            func_8023903C(0x3C);
            func_8026C660(0x1E5);
            func_8023903C(0x3C);
            func_8026C8E8();
            func_8026C894();
            var_v0 = &D_802AC760;
            var_s0_5 = 0;
loop_34:
            if (*var_v0 != 1) {
                var_s0_5 += 1;
                var_v0 = (void *) ((u8 *)var_v0 + 4);
                if (var_s0_5 != 2) {
                    goto loop_34;
                }
            }
            if (!(D_802AC5D0 & 1)) {
                if (D_802A01B4 == 0) {
                    D_802AC5D4 = 0x22;
                    D_802AC5DC = D_802AC5D4;
                    D_802AC5D8 = var_s0_5 + 0x16;
                    D_802AC5E0 = D_802AC5D8;
                    D_802AC5D0 |= 1;
block_39:
                    D_802AC5E4 = 0;
                }
            }
        }
    }
}

void func_80242270(s32 arg0, Gfx **gdl) {
    Gfx *gfx;
    Rect54E40 *r;
    TexEntry *e;
    s32 *digit;
    s32 *count;
    s32 *xs;
    s32 n;
    s32 x;
    s32 i;
    s32 j;
    s32 v;
    s32 div;
    s32 d;
    s32 *p;
    s32 t;

    if (0) {
        func_80242268();
    }
    v = M2C_FIELD(&D_802AC610, s32 *, 0x30);
    div = 10000000;
    p = D_802AC770;
    i = 0;
    do {
        d = v / div;
        *p++ = d * 2;
        t = d * div;
        if (v >= t) {
            v -= t;
        }
        i++;
        div /= 10;
    } while (i < 8);
    v = M2C_FIELD(&D_802AC610, s32 *, 0x1C);
    div = 10;
    i = 0;
    do {
        d = v / div;
        *p++ = d * 2;
        t = d * div;
        if (v >= t) {
            v -= t;
        }
        i++;
        div /= 10;
    } while (i != 2);
    gfx = *gdl;
    gDPSetRenderMode(gfx++, 0x553048, 0);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFCF279);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, 1);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    r = D_802A0774;
    do {
        gDPLoadTLUT_pal256(gfx++, (u8 *) D_802A0758 + D_802A0758->entries[r->idx + 1].offset);
        gDPLoadTextureBlock_4b(gfx++, (u8 *) D_802A0758 + D_802A0758->entries[r->idx].offset, G_IM_FMT_CI, 16, 16, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx++, r->xl, r->yl, r->xh, r->yh, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
        r++;
    } while (r != D_802A0774 + 2);
    n = 0;
    count = D_802A076C;
    xs = D_802A0764;
    do {
        x = *xs;
        j = 0;
        if (*count > 0) {
            digit = &D_802AC770[n];
            e = D_802A075C->entries;
            do {
                n++;
                if (count == D_802A076C && M2C_FIELD(&D_802AC610, s32 *, 0x28) < M2C_FIELD(&D_802AC610, s32 *, 0x30)) {
                    gDPLoadTLUT_pal16(gfx++, 0, (u8 *) D_802A075C + e[25].offset);
                } else {
                    gDPLoadTLUT_pal16(gfx++, 0, (u8 *) D_802A075C + e[1].offset);
                }
                gDPLoadTextureTile_4b(gfx++, (u8 *) D_802A075C + e[*digit].offset, G_IM_FMT_CI, 10, 18, 0, 0, 9, 17, 0,
                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, x << 2, 22 << 2, (x + 10) << 2, 40 << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
                j++;
                digit++;
                x += 10;
            } while (j < *count);
        }
        count++;
        xs++;
    } while (count != D_802A076C + 2);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    *gdl = gfx;
}

void func_80242268() {

}

void func_80241BB0(s32 arg0, Gfx **gdl) {
    Gfx *gfx;
    Rect54E40 *r;
    u8 *pl;
    TexEntry *e;
    s32 *count;
    s32 *xs;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;

    if (D_802AC688 < 6) {
        func_8023CD1C();
    }
    r = D_802A07D4;
    pl = D_800AEDF0;
    i = 0;
    k = 0;
    do {
        if (M2C_FIELD(pl, s32 *, 0x24) == 3 || func_80243EF0(i) != 0) {
            r->idx = k + 8;
        } else {
            r->idx = k;
        }
        i++;
        pl += 0xC8;
        r++;
        k += 2;
    } while (i < 4);
    gfx = *gdl;
    gDPSetRenderMode(gfx++, 0x553048, 0);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFCF279);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, 1);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    i = 0;
    do {
        if (i == 0 || *(D_800AED4C + i * 0xC8) != 0) {
            e = D_802A0758->entries;
            r = &D_802A07D4[i];
            gDPLoadTLUT_pal256(gfx++, (u8 *) D_802A0758 + e[r->idx + 1].offset);
            gDPLoadTextureBlock_4b(gfx++, (u8 *) D_802A0758 + e[r->idx].offset, G_IM_FMT_CI, 16, 16, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx++, r->xl, r->yl, r->xh, r->yh, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
        }
        i++;
    } while (i != 5);
    n = 0;
    count = D_802A07B8;
    xs = D_802A079C;
    i = 0;
    do {
        x = *xs;
        j = 0;
        if (*count > 0) {
            do {
                j++;
                if (i < 3 || *(D_800AEBBC + i * 0xC8) != 0) {
                    e = D_802A075C->entries;
                    if (i >= 3 || D_802AC68C > 0) {
                        gDPLoadTLUT_pal16(gfx++, 0, (u8 *) D_802A075C + e[1].offset);
                    } else {
                        gDPLoadTLUT_pal16(gfx++, 0, (u8 *) D_802A075C + e[25].offset);
                    }
                    gDPLoadTextureTile_4b(gfx++, (u8 *) D_802A075C + e[D_802AC770[n]].offset, G_IM_FMT_CI, 10, 18, 0, 0, 9, 17, 0,
                                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    gSPTextureRectangle(gfx++, x << 2, 22 << 2, (x + 10) << 2, 40 << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
                }
                x += 10;
                n++;
            } while (j < *count);
        }
        i++;
        xs++;
        count++;
    } while (i != 7);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    *gdl = gfx;
}

void func_80241590(s32 arg0, Gfx **gdl) {
    Gfx *gfx;
    Rect54E40 *r;
    TexEntry *e;
    s32 *digit;
    s32 *count;
    s32 *xs;
    s32 n;
    s32 x;
    s32 i;
    s32 j;

    if (D_802AC688 < 6) {
        func_8023CD1C();
    }
    gfx = *gdl;
    gDPSetRenderMode(gfx++, 0x553048, 0);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFCF279);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, 1);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    i = 0;
    if (D_802AC7C8 > 0) {
        r = (Rect54E40 *) D_802A084C;
        do {
            gDPLoadTLUT_pal256(gfx++, (u8 *) D_802A0758 + D_802A0758->entries[r->idx + 1].offset);
            gDPLoadTextureBlock_4b(gfx++, (u8 *) D_802A0758 + D_802A0758->entries[r->idx].offset, G_IM_FMT_CI, 16, 16, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx++, r->xl, r->yl, r->xh, r->yh, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
            i++;
            r++;
        } while (i < D_802AC7C8);
    }
    n = 0;
    count = D_802A08D8;
    xs = D_802A0838;
    do {
        x = *xs;
        j = 0;
        if (*count > 0) {
            digit = &D_802AC770[n];
            e = D_802A075C->entries;
            do {
                n++;
                if (count >= D_802A08D8 + 3 || D_802AC68C > 0) {
                    gDPLoadTLUT_pal16(gfx++, 0, (u8 *) D_802A075C + e[1].offset);
                } else {
                    gDPLoadTLUT_pal16(gfx++, 0, (u8 *) D_802A075C + e[25].offset);
                }
                gDPLoadTextureTile_4b(gfx++, (u8 *) D_802A075C + e[*digit].offset, G_IM_FMT_CI, 10, 18, 0, 0, 9, 17, 0,
                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, x << 2, 22 << 2, (x + 10) << 2, 40 << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
                j++;
                digit++;
                x += 10;
            } while (j < *count);
        }
        count++;
        xs++;
    } while (count != D_802A08D8 + 5);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    *gdl = gfx;
}

void func_80241550() {
    s32 sp1C;

    sp1C = func_802391F0();
    func_8023903C(0x78);
    func_8026C93C(sp1C);
    func_80239430();
}

void func_80241180() {
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp78;
    s32 sp5C;
    f32 temp_fs2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fv0;
    s32 var_s0;
    u8 *temp_a3;
    u8 *temp_s1;

    temp_s1 = func_802443F4(0);
    func_802350F8(1);
    func_80234F6C(1);
    func_80234858(&sp8C, &sp88, &sp84);
    sp78 = 3.0f;
    temp_a3 = M2C_FIELD(temp_s1, void **, 0x40);
    temp_fv0 = M2C_FIELD(temp_a3, f32 *, 0x20);
    var_fs1 = 30.0f;
    if (sp8C < temp_fv0) {
        var_fs2 = -(sp8C - temp_fv0);
    } else {
        var_fs2 = sp8C - temp_fv0;
    }
    if (var_fs2 > 180.0f) {
        temp_fv1 = sp8C + 360.0f;
        if (temp_fv1 < temp_fv0) {
            var_fs2 = -(temp_fv1 - temp_fv0);
        } else {
            var_fs2 = temp_fv1 - temp_fv0;
        }
    }
    temp_fv0_2 = sp84 / 30.0f;
    temp_fs2 = var_fs2 / temp_fv0_2;
    sp5C = (s32) (180.0f / temp_fv0_2);
    var_s0 = func_80234DD4(sp8C, sp88, sp84, temp_a3);
    if (sp84 > 600.0f) {
        do {
            temp_fv0_3 = sp84 - var_fs1;
            sp84 = temp_fv0_3;
            if (temp_fv0_3 < 900.0f) {
                var_fs1 *= 0.9f;
                if (var_fs1 < 1.0f) {
                    var_fs1 = 1.0f;
                }
            }
            if (sp88 > 25.0f) {
                sp88 -= 0.08f;
            }
            sp78 *= 0.9f;
            var_fv0 = sp8C - M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x20);
            if (var_fv0 < 0.0f) {
                var_fa0 = sp8C;
                var_fv0 += 360.0f;
            } else {
                var_fa0 = sp8C;
                if (var_fv0 >= 360.0f) {
                    var_fv0 -= 360.0f;
                }
            }
            if (var_s0 != 0) {
                var_fa0 += (f32) sp5C;
            } else if (var_fv0 >= 15.0f) {
                if (var_fv0 <= 180.0f) {
                    var_fa0 -= temp_fs2;
                } else {
                    goto block_25;
                }
            } else {
block_25:
                if ((var_fv0 > 180.0f) && (var_fv0 <= 345.0f)) {
                    var_fa0 += temp_fs2;
                }
            }
            if (var_fa0 < 0.0f) {
                var_fa0_2 = var_fa0 + 360.0f;
                goto block_32;
            }
            sp8C = var_fa0;
            if (var_fa0 >= 360.0f) {
                var_fa0_2 = var_fa0 - 360.0f;
block_32:
                sp8C = var_fa0_2;
            }
            sp80 = sp8C;
            if (func_80234DD4(sp8C, sp88, sp84, M2C_FIELD(temp_s1, void **, 0x40)) != 0) {
                if (var_s0 == 0) {

                }
            } else {
                var_s0 = 0;
            }
            func_80234778(sp8C, sp88, sp84);
            func_80239094();
        } while (sp84 > 600.0f);
    }
    D_802AC7EC = 0;
    func_80239430();
}

void func_80240F34() {
    f32 sp6C[3];
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fs0;
    f32 var_ft4;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv1;

    func_802350F8(1);
    func_80234F6C(1);
    func_802348B4(&sp68, &sp64, &sp60);
    var_fs0 = 8.0f;
loop_1:
    func_80250338(func_80243DDC(), sp6C);
    var_fa0 = sp68;
    if (!(sp6C[1] < -1000.0f)) {
        var_fv1 = sp64;
        if (var_fa0 < sp6C[0]) {
            var_fa1 = -(var_fa0 - sp6C[0]);
        } else {
            var_fa1 = var_fa0 - sp6C[0];
        }
        var_fv0 = sp60;
        if (var_fv1 < sp6C[1]) {
            var_ft4 = -(var_fv1 - sp6C[1]);
        } else {
            var_ft4 = var_fv1 - sp6C[1];
        }
        if (var_fv0 < sp6C[2]) {
            var_ft5 = -(var_fv0 - sp6C[2]);
        } else {
            var_ft5 = var_fv0 - sp6C[2];
        }
        if (!(var_fa1 > 100.0f) && !(var_ft4 > 100.0f) && !(var_ft5 > 100.0f)) {
            var_fs0 *= 0.9f;
            if (var_fs0 < 1.0f) {
                var_fs0 = 1.0f;
            }
        }
        if (var_fa1 > 1.0f) {
            if (var_fa0 < sp6C[0]) {
                var_fa0 += var_fs0;
            } else {
                var_fa0 -= var_fs0;
            }
        }
        if (var_ft4 > 1.0f) {
            if (var_fv1 < sp6C[1]) {
                var_fv1 += var_fs0;
            } else {
                var_fv1 -= var_fs0;
            }
        }
        if (var_ft5 > 1.0f) {
            if (var_fv0 < sp6C[2]) {
                var_fv0 += var_fs0;
            } else {
                var_fv0 -= var_fs0;
            }
        }
        sp60 = var_fv0;
        sp64 = var_fv1;
        sp68 = var_fa0;
        func_802346C8(var_fa0, var_fv1 + 50.0f, var_fv0);
        func_80239094();
        goto loop_1;
    }
    D_802AC7F0 = 0;
    func_80239430();
}

void func_8023FD08() {
    s32 spA4;
    s32 spA0;
    s32 sp98;
    s32 sp94;
    s32 sp90;
    u8 *sp88;
    s32 sp84;
    u8 *sp80;
    u8 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    void **sp4C;                                    /* compiler-managed */
    f32 var_ft3;
    f32 var_fv0;
    s32 *temp_v0;
    s32 *var_v1_2;
    s32 *var_v1_5;
    s32 *var_v1_6;
    s32 temp_t7;
    s32 temp_t9;
    s32 temp_v0_3;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_a2_5;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s3_3;
    s32 var_s3_4;
    s32 var_s3_5;
    s32 var_s3_6;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_7;
    void **temp_v1;
    void **temp_v1_2;
    void **var_a1;
    void **var_v1_3;
    void **var_v1_4;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;

    D_802AC5D0 |= 0x90;
    func_80270770(0, 1);
    func_802268F4();
    func_8026C8E8();
    if (func_8023AB90() == 0) {
        do {
            func_80239094();
        } while (func_8023AB90() == 0);
    }
    if (D_802AC5D0 & 2) {
        func_80239430();
    }
    D_802AC5E8 = M2C_FIELD(&D_802AC610, s32 *, 4);
    D_802AC5EC = M2C_FIELD(&D_802AC610, s32 *, 8);
    D_802AC5F0 = 0;
    func_8027F79C();
    func_80246D74(0);
    func_80245280(1);
    func_80247C50(0);
    func_802313DC(func_802443F4(0), 0x40000);
    var_s3 = 0;
    var_v1 = 0;
    do {
        sp90 = var_v1;
        var_s3 += 1;
        if (func_8028A36C((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + var_s3 + 0x2C) != 0) {
            var_v1 += 1;
        }
    } while (var_s3 < 3);
    if (D_802AC5D0 & 0x28) {
        D_802AC80C = D_802AC63C;
        var_s3_2 = 0;
        if (D_802AC638 >= D_802AC640) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        if ((var_v0 + D_802AC80C) > 0) {
            do {
                func_8028A3D0((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + var_s3_2 + 0x2C);
                var_s3_2 += 1;
                if (M2C_FIELD(&D_802AC610, s32 *, 0x28) >= M2C_FIELD(&D_802AC610, s32 *, 0x30)) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
            } while (var_s3_2 < (var_v0_2 + D_802AC80C));
        }
    } else {
        D_802AC80C = var_v1 - D_802AC630;
        if (D_802AC638 >= D_802AC640) {
            func_8028A3D0((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + 0x30);
        }
    }
    var_s3_3 = 0;
    *func_8028A060(1) = D_802AC648;
    *func_8028A060(5) = D_802AC628;
    *func_8028A060(5) = D_802AC628;
    temp_v0 = func_8028A060(0x15);
    if ((D_802AC75C == 0) || (M2C_FIELD(&D_802AC610, s32 *, 0x30) < *((u8 *)temp_v0 + (D_802AC5E8 * 0x10) + (D_802AC5EC * 4)))) {
        *((u8 *)temp_v0 + (D_802AC5E8 * 0x10) + (D_802AC5EC * 4)) = M2C_FIELD(&D_802AC610, s32 *, 0x30);
    }
    M2C_FIELD(&D_802AC610, s32 *, 0) |= 8;
    func_80277484();
    func_8023903C(0x28);
    if (D_802AC5D0 & 0x28) {
        func_8026C93C(0x2D);
    } else {
        func_8026C93C(0x15);
    }
    func_80238DFC(0xD0, 0xF0, 0U);
    sp88 = func_802443F4(0);
    func_802362B8(0x7F);
    D_802A0038 = 0;
    if (D_802A01BC != 0) {
        D_802AC7EC = func_80238A10(func_80241180, 0, 0, 0, 0x401);
        D_802AC7F0 = func_80238A10(func_80240F34, 0, 0, 0, 0x401);
    } else {
        D_802AC7F0 = 0;
        D_802AC7EC = 0;
    }
    func_8023903C(0x1E);
    M2C_FIELD(&D_802AC610, s32 *, 0) &= ~8;
    func_802313DC(sp88, 0x08000000);
    func_80231408(sp88, 0x04000000);
    temp_v0_2 = M2C_FIELD(sp88, void **, 0x40);
    M2C_FIELD(temp_v0_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 0xC) & ~0x4000);
    func_80229E38(M2C_FIELD(sp88, void **, 0x40), 0x16, 0);
    func_80229E38(M2C_FIELD(sp88, void **, 0x40), -1, 1);
    func_8022979C((s32) M2C_FIELD(sp88, void **, 0x40), 4, 0xE);
    func_8022979C((s32) M2C_FIELD(sp88, void **, 0x40), 5, 0xF);
    if (!(M2C_FIELD(M2C_FIELD(sp88, void **, 0x40), s32 *, 0xC) & 0x40)) {
        do {
            func_80239094();
        } while (!(M2C_FIELD(M2C_FIELD(sp88, void **, 0x40), s32 *, 0xC) & 0x40));
    }
    func_8023B318(&D_802A0A68, 1);
    func_8023903C(0x5A);
loop_32:
    var_v0_3 = var_s3_3 ^ 0x10;
    if (*var_v1_2 != 0) {
        var_s3_3 += 1;
        var_v1_2 = (void *) ((u8 *)var_v1_2 + 4);
        if (var_s3_3 >= 0x10) {
            var_v0_3 = var_s3_3 ^ 0x10;
        } else {
            goto loop_32;
        }
    }
    var_s3_4 = 0;
    if ((var_v0_3 == 0) && (func_80295330(0) == 0)) {
        func_80294CE8(0);
        func_80295384();
    }
    if (D_802AC5E8 == 5) {
        var_a2 = 0;
        if (D_802AC5EC == 3) {
            var_a2 = 0;
            if (func_80295330(2) == 0) {
                func_80294CE8(2);
                func_80295384();
                goto block_42;
            }
        }
    } else {
block_42:
        var_a2 = 0;
    }
    var_a0 = 0x2C;
    do {
        sp98 = var_a2;
        var_a2 += 1;
        if (func_8028A36C(var_a0) != 0) {
            var_s3_4 += 1;
        }
        var_a0 = var_a2 + 0x2C;
    } while (var_a2 != 0x78);
    var_s3_5 = 0;
    if ((var_s3_4 ^ 0x78) == 0) {
        if (func_80295330(1) == 0) {
            func_80294CE8(1);
            func_80295384();
        }
        func_8028A3D0(8);
        func_8028A3D0(0x13);
        func_8028A3D0(0x1E);
        func_8028A3D0(0x29);
        if ((D_802AC620 == 1) && (D_802AC648 < 0x2A31)) {
            func_8028A3D0(0xA);
            func_8028A3D0(0x15);
            func_8028A3D0(0x20);
            func_8028A3D0(0x2B);
        }
    }
    if ((D_802AC5E8 == 5) && (D_802AC5EC == 3) && (D_802AC648 < 0x2A31)) {
        func_8028A3D0(9);
        func_8028A3D0(0x14);
        func_8028A3D0(0x1F);
        func_8028A3D0(0x2A);
    }
    func_8023903C(0x1E);
    func_8023AB54(&D_802A0A68, 1);
    func_8023903C(2);
    if (D_802AC5D0 & 0x28) {
        func_8023B318(&D_802A0A7C, 3);
        var_ft3 = 110.0f;
        var_fv0 = 140.0f;
        sp68 = 3.4f;
        sp64 = -1.5f;
        sp58 = 3.82f;
    } else {
        func_8023B318(&D_802A0A18, 4);
        var_ft3 = 120.0f;
        var_fv0 = 180.0f;
        sp68 = 6.6f;
        sp64 = -3.3f;
        sp58 = 5.725f;
    }
    sp60 = var_ft3;
    sp5C = var_fv0;
    func_8023B450(8, D_802AC638, &sp70);
    var_a2_2 = (u32) sp5C;
    temp_v0_3 = func_802811F0(&sp70, 0xBEU, var_a2_2 & 0xFFFF, 0.6f, 0.8f, 3U);
    spA0 = 1;
    spA4 = temp_v0_3;
    func_8023903C(0x1E);
    sp80 = func_8026CE28(0x19);
    if (D_802AC80C > 0) {
        var_v1_3 = &D_802AC7F8;
        do {
            sp4C = var_v1_3;
            func_8026C660(0x1E8);
            temp_v0_4 = func_8022A6C4(sp80, 0x40);
            M2C_FIELD(var_v1_3, void **, 0) = temp_v0_4;
            M2C_FIELD(temp_v0_4, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_4, s32 *, 0xC) | 0x100);
            M2C_FIELD(temp_v0_4, s16 *, 0x34) = (s16) D_802AC5CC;
            M2C_FIELD(temp_v0_4, f32 *, 0x10) = (f32) (((f32) var_s3_5 * sp58) + 6.55f);
            M2C_FIELD(temp_v0_4, f32 *, 0x14) = sp68;
            M2C_FIELD(temp_v0_4, f32 *, 0x28) = 0.03f;
            M2C_FIELD(temp_v0_4, f32 *, 0x2C) = 0.03f;
            M2C_FIELD(temp_v0_4, f32 *, 0x30) = 0.03f;
            M2C_FIELD(temp_v0_4, f32 *, 0x18) = 930.0f;
            if (var_s3_5 != 0) {
                M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v0_4, void **, 0x48), void **, 4), f32 *, 4) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_v1_3, void **, -4), void **, 0x48), void **, 4), f32 *, 4);
            }
            sp4C = var_v1_3;
            func_8023903C(0x1E);
            var_s3_5 += 1;
            var_v1_3 += 4;
        } while (var_s3_5 < D_802AC80C);
    }
    if (!(D_802AC5D0 & 0x28)) {
        func_8023B450(2, func_80287680(), &sp70);
        (&spA4)[spA0] = func_802811F0(&sp70, 0xE2U, 0x5AU, 0.8f, 0.8f, 2U);
        spA0 += 1;
        if ((D_800BE824 == 0) && (func_8028A36C((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + 0x2F) != 0)) {
            temp_v1 = &(&D_802AC7F8)[var_s3_5];
            sp4C = temp_v1;
            func_8026C660(0x1E8);
            temp_v0_5 = func_8022A6C4(sp80, 0x40);
            M2C_FIELD(temp_v1, void **, 0) = temp_v0_5;
            M2C_FIELD(temp_v0_5, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_5, s32 *, 0xC) | 0x100);
            M2C_FIELD(temp_v0_5, s16 *, 0x34) = (s16) D_802AC5CC;
            M2C_FIELD(temp_v0_5, f32 *, 0x10) = 18.0f;
            M2C_FIELD(temp_v0_5, f32 *, 0x14) = 1.6f;
            M2C_FIELD(temp_v0_5, f32 *, 0x18) = 930.0f;
            M2C_FIELD(temp_v0_5, f32 *, 0x30) = 0.03f;
            M2C_FIELD(temp_v0_5, f32 *, 0x2C) = 0.03f;
            M2C_FIELD(temp_v0_5, f32 *, 0x28) = 0.03f;
            if (var_s3_5 != 0) {
                M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v0_5, void **, 0x48), void **, 4), f32 *, 4) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v1, void **, -4), void **, 0x48), void **, 4), f32 *, 4);
            }
            var_s3_5 += 1;
            D_802AC80C += 1;
        }
    }
    sp4C = &(&spA4)[spA0];
    func_8023903C(0x1E);
    func_8023B450(8, D_802AC640, &sp70);
    var_a2_3 = (u32) sp60;
    *sp4C = func_802811F0(&sp70, 0xA0U, var_a2_3 & 0xFFFF, 0.6f, 0.8f, 2U);
    spA0 += 1;
    if (D_802AC638 >= D_802AC640) {
        temp_v1_2 = &(&D_802AC7F8)[var_s3_5];
        sp4C = temp_v1_2;
        func_8026C660(0x1E8);
        temp_v0_6 = func_8022A6C4(sp80, 0x40);
        M2C_FIELD(temp_v1_2, void **, 0) = temp_v0_6;
        M2C_FIELD(temp_v0_6, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_6, s32 *, 0xC) | 0x100);
        M2C_FIELD(temp_v0_6, s16 *, 0x34) = (s16) D_802AC5CC;
        M2C_FIELD(temp_v0_6, f32 *, 0x10) = 18.0f;
        M2C_FIELD(temp_v0_6, f32 *, 0x14) = sp64;
        M2C_FIELD(temp_v0_6, f32 *, 0x18) = 930.0f;
        M2C_FIELD(temp_v0_6, f32 *, 0x30) = 0.03f;
        M2C_FIELD(temp_v0_6, f32 *, 0x2C) = 0.03f;
        M2C_FIELD(temp_v0_6, f32 *, 0x28) = 0.03f;
        if ((void *) temp_v1_2 != (void *) &D_802AC7F8) {
            M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v0_6, void **, 0x48), void **, 4), f32 *, 4) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v1_2, void **, -4), void **, 0x48), void **, 4), f32 *, 4);
        }
        D_802AC80C += 1;
    }
    var_s3_6 = 0;
    func_8023903C(0x3C);
    sp84 = func_802811F0(&D_802A04A4, func_8023B2AC(0.6f) & 0xFFFF, 0xD2U, 0.6f, 0.6f, 2U);
    func_8023903C(2);
    if (func_802947AC() != 0) {
        func_80280DB4(sp84);
        func_8023903C(4);
        func_8026C660(0x18);
        sp84 = func_802811F0(&D_802A04B4, func_8023B2AC(0.6f) & 0xFFFF, 0xD2U, 0.6f, 0.6f, 0U);
        func_8023903C(0xB4);
    }
    func_8023903C(0x3C);
    if (D_802AC5E8 == 4) {
        if ((D_802AC5EC == 3) && (func_8028A36C(0xA4) == 0)) {
            func_8026CB2C();
        }
    }
    func_80280DB4(sp84);
    func_8023903C(0x3C);
    if (D_802AC5D0 & 0x28) {
        func_8023AB54(&D_802A0A7C, 3);
    } else {
        func_8023AB54(&D_802A0A18, 4);
    }
    if (D_802AC80C > 0) {
        var_v1_4 = &D_802AC7F8;
        do {
            sp4C = var_v1_4;
            func_8022A1E8(*var_v1_4);
            var_s3_6 += 1;
            var_v1_4 += 4;
        } while (var_s3_6 < D_802AC80C);
        var_s3_6 = 0;
    }
    func_8026CCBC(0x19);
    var_v1_5 = &spA4;
    if (spA0 > 0) {
        do {
            sp4C = var_v1_5;
            func_80280DB4(*var_v1_5);
            var_s3_6 += 1;
            var_v1_5 = (void *) ((u8 *)var_v1_5 + 4);
        } while (var_s3_6 != spA0);
    }
    func_8023903C(2);
    var_a1 = NULL;
loop_103:
    if (*var_v1_6 != 0) {
        var_a1 += 4;
        var_v1_6 = (void *) ((u8 *)var_v1_6 + 4);
        if (var_a1 != (void **)0x40) {
            goto loop_103;
        }
    }
    var_v1_7 = 0;
    var_a2_4 = 0;
    var_a0_2 = 0x2C;
    do {
        sp94 = var_v1_7;
        sp4C = var_a1;
        sp98 = var_a2_4;
        var_v1_7 += 1;
        if (func_8028A36C(var_a0_2) != 0) {
            var_a2_4 += 1;
        }
        var_a0_2 = var_v1_7 + 0x2C;
    } while (var_v1_7 != 0x78);
    if (D_802AC75C == 0) {
        temp_t9 = D_802AC5EC + 1;
        D_802AC5EC = temp_t9;
        if (temp_t9 >= 4) {
            D_802AC5EC = 0;
            temp_t7 = D_802AC5E8 + 1;
            D_802AC5E8 = temp_t7;
            if ((temp_t7 == 4) && (var_a1 != (void **)0x40)) {
                D_802AC5E8 = 0;
            }
        }
    }
    D_802AC614 = D_802AC5E8;
    sp98 = var_a2_4;
    D_802AC618 = D_802AC5EC;
    func_8026C894();
    var_a2_5 = var_a2_4;
    if (D_802AC7EC != 0) {
        sp98 = var_a2_5;
        func_80238EA8(D_802AC7EC);
    }
    if (D_802AC7F0 != 0) {
        sp98 = var_a2_5;
        func_80238EA8(D_802AC7F0);
    }
    if (D_802AC75C == 0) {
        if (D_802AC5E8 == 6) {
            func_8023AE6C(0x1C, 0x10, 0);
        } else if ((D_802AC5E8 == 5) && (D_802AC5EC == 0) && (var_a2_5 < 0x64)) {
            func_8023AE6C(0x1C, 0x11, 0);
        } else if ((D_802AC5E8 == 5) && (D_802AC5EC == 0) && (var_a2_5 == 0x64) && (func_8028A36C(0xA4) == 0)) {
            func_8023AE6C(0x21, 0x14, 0);
        } else if (D_802AC5EC == 0) {
            func_8023AE6C(0x21, 0x12, 0);
        } else {
            func_8023AE6C(0x21, 0x11, 0);
        }
    } else if ((D_802AC5E8 == 5) && (D_802AC5EC == 3)) {
        func_8023AE6C(0x1C, 0x10, 0);
    } else if ((D_802AC5E8 == 4) && (D_802AC5EC == 3) && (var_a2_5 < 0x64)) {
        func_8023AE6C(0x1C, 0x11, 0);
    } else if ((D_802AC5E8 == 4) && (D_802AC5EC == 3)) {
        if (var_a2_5 == 0x64) {
            if (func_8028A36C(0xA4) == 0) {
                D_802AC5E8 = 5;
                D_802AC614 = 5;
                D_802AC5EC = 0;
                D_802AC618 = 0;
                func_8023AE6C(0x21, 0x14, 0);
            } else {
                goto block_145;
            }
        } else {
            goto block_146;
        }
    } else {
block_145:
block_146:
        func_8023AE6C(0x21, 0x11, 0);
    }
    func_80239430();
}

void func_8023FC80(s32 arg0, u8 **arg1) {
    u8 *temp_a0;
    u8 *temp_a2;
    u8 *temp_a3;
    u8 *temp_t0;
    u8 *temp_v1;

    temp_v1 = *arg1;
    temp_a0 = temp_v1 + 8;
    M2C_FIELD(temp_v1, s32 *, 4) = 0x80;
    M2C_FIELD(temp_v1, s32 *, 0) = 0xFA000000;
    temp_a2 = temp_a0 + 8;
    M2C_FIELD(temp_v1, s32 *, 8) = 0xFCFFFFFF;
    M2C_FIELD(temp_a0, s32 *, 4) = 0xFFFDF6FB;
    temp_a3 = temp_a2 + 8;
    M2C_FIELD(temp_a0, s32 *, 8) = 0xFF10013F;
    M2C_FIELD(temp_a2, M2C_UNK **, 4) = D_1000000;
    temp_t0 = temp_a3 + 8;
    M2C_FIELD(temp_a2, s32 *, 8) = 0xF7000000;
    M2C_FIELD(temp_a3, s32 *, 4) = 0x10001;
    M2C_FIELD(temp_a3, s32 *, 8) = 0xF64FC3BC;
    M2C_FIELD(temp_t0, s32 *, 4) = 0;
    *arg1 = temp_t0 + 8;
}

s32 func_8023FC00(u8 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg1 & 0xFFFF;
    if (temp_v0 & 1) {
        func_8026C660(1);
        D_802AC810 = (s32) arg0;
        return 0;
    }
    if (temp_v0 & 6) {
        func_8026C660(2);
        D_802AC810 = -1;
        return 0;
    }
    if (temp_v0 & 0x78) {

    }
    return 1;
}

void func_8023FAA0() {
    s32 sp44[3];
    s32 temp_v1_2;
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_3;

    temp_v0 = func_802391F0();
    M2C_FIELD(temp_v0, f32 *, 0x70) = 1.6333334f;
    M2C_FIELD(temp_v0, f32 *, 0x6C) = 16.333334f;
loop_1:
    var_v0 = 0;
    if (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) <= func_8026E8B8()) {
        var_v0 = 1;
    }
    if (var_v0 != 0) {
        func_8027F820();
loop_5:
        func_80239094();
        goto loop_5;
    }
    func_80291944(temp_v0, 1, 0.0f);
    temp_v1 = M2C_FIELD(temp_v0, void **, 0x40);
    func_8026DCAC(M2C_FIELD(temp_v1, f32 *, 0x10), M2C_FIELD(temp_v1, f32 *, 0x14), M2C_FIELD(temp_v1, f32 *, 0x18), sp44, 2);
    temp_v1_2 = func_8026D7D8(sp44[0], sp44[1], sp44[2]) & 0x1C00;
    if (temp_v1_2 != 0) {
        func_8027F858((s32) temp_v0, temp_v1_2 >> 0xA);
    }
    func_80230914(temp_v0);
    func_802909FC((s32) temp_v0);
    temp_v1_3 = M2C_FIELD(temp_v0, void **, 0x40);
    M2C_FIELD(temp_v0, f32 *, 0x58) = (f32) M2C_FIELD(temp_v1_3, f32 *, 0x10);
    M2C_FIELD(temp_v0, f32 *, 0x5C) = (f32) M2C_FIELD(temp_v1_3, f32 *, 0x14);
    M2C_FIELD(temp_v0, f32 *, 0x60) = (f32) M2C_FIELD(temp_v1_3, f32 *, 0x18);
    func_80239094();
    goto loop_1;
}

void func_8023F26C() {
    s32 spB4;
    s32 spB0;
    s32 spAC;
    u32 spA4;
    u8 *sp9C;
    s32 sp8C;
    s32 sp88;
    s32 sp6C;                                       /* compiler-managed */
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_a0;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    u8 *temp_s5;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_a0;
    u8 *var_s5;
    u8 *var_t0;

    D_802A0B94 = 1;
    temp_a0 = *(s32 *) func_802391F0();
    spAC = temp_a0;
    func_80247C50(temp_a0);
    if ((D_802AC5D0 & 4) || ((D_802AC5D0 & 8) && (spAC != 0))) {
        sp6C = spAC * 4;
        spA4 = (&D_802AC858)[spAC];
        var_s5 = func_802443F4(spAC);
        if ((D_802AC5D0 & 4) && (D_802AC660 == 0) && (func_80243EF0(spAC) == 0)) {
            D_802AC758 -= 1;
        }
        if (D_802AC5D0 & 8) {
            if (D_802AC758 == 1) {
                func_80245208(0, 1);
            }
        }
    } else {
        spA4 = D_802AC858;
        var_s5 = func_802443F4(0);
        spAC = 0;
        sp6C = 0;
    }
    func_802313DC(var_s5, 0x7FFFF);
    *(D_802AC868 + sp6C) = spA4;
    switch (spA4) {
    case 3:
        if (!(D_802AC5D0 & 8) || (spAC == 0)) {
            func_8026C660(0x1E);
        }
        func_8027F820();
        func_8023903C(0x5A);
        break;
    case 2:
        func_8024364C(var_s5);
        func_8023903C(0x5A);
        break;
    case 1:
        if ((D_802AC5D0 & 8) && (spAC != 0)) {
            func_8023EE40((s32) var_s5);
        } else {
            func_8023EF38(var_s5);
        }
        break;
    case 0:
        if ((D_802AC5D0 & 8) && (spAC != 0)) {
            func_8023EE40((s32) var_s5);
        } else {
            func_8023ECF4(var_s5);
        }
        break;
    case 5:
        sp88 = func_80238A10(func_8023FAA0, (s32) var_s5, 0, 0, 0x130);
        func_802362B8(0x7F);
        D_802A0038 = 0;
        if (D_802A01BC != 0) {
            D_802AC7EC = func_80238A10(func_80241180, 0, 0, 0, 0x130);
            D_802AC7F0 = func_80238A10(func_80240F34, 0, 0, 0, 0x130);
        } else {
            D_802AC7F0 = 0;
            D_802AC7EC = 0;
        }
        func_8022979C(M2C_FIELD(var_s5, s32 *, 0x40), 4, 0xC);
        func_8022979C(M2C_FIELD(var_s5, s32 *, 0x40), 5, 0xD);
        var_v1 = 0;
        do {
            temp_fv0 = (f32) var_v1 / 20.0f;
            temp_fv1 = 1.0f - temp_fv0;
            M2C_FIELD(M2C_FIELD(var_s5, s32 *, 0x40), f32 *, 0x30) = temp_fv1;
            M2C_FIELD(M2C_FIELD(var_s5, s32 *, 0x40), f32 *, 0x28) = temp_fv1;
            M2C_FIELD(M2C_FIELD(var_s5, s32 *, 0x40), f32 *, 0x2C) = (f32) (temp_fv0 + 1.0f);
            sp8C = var_v1;
            func_80239094();
            var_v1 += 1;
        } while (var_v1 != 0x14);
        if (D_802AC7EC != 0) {
            func_80238EA8(D_802AC7EC);
        }
        func_80238EA8(sp88);
        break;
    }
    if (D_802AC5D0 & 4) {
        func_802313DC(var_s5, 0x0507FFFF);
        if (D_802AC660 == 0) {
            func_802313DC(var_s5, 0x01000000);
            func_8023903C(2);
            temp_v1 = sp6C + &D_802AC660;
            if (M2C_FIELD(temp_v1, s32 *, 4) == 1) {
                if (M2C_FIELD(temp_v1, s32 *, 0x40) == 1) {
                    func_80227EE0(M2C_FIELD(temp_v1, s32 *, 0xE8));
                }
            }
            func_8025C590(spAC);
            if ((D_802AC69C != 0) && (D_802AC68C > 0) && !(D_802AC5D0 & 0x10)) {
                func_80243E90(spAC);
                temp_s5 = func_8023EB28(spAC);
                temp_v0 = func_80231274(-1, 0x01000000, 0xD0, NULL);
                sp9C = temp_v0;
                spB4 = func_8028A81C(0x15, 0.0f, 20.0f, 0.0f, (s32) temp_v0);
                func_80245208(spAC, 1);
                var_t0 = sp9C;
                var_a0 = (spAC * 0xC8) + D_800AEDF0;
                var_v1_2 = 0;
loop_45:
                var_v0 = M2C_FIELD(var_a0, s32 *, 0x24);
                if (var_v0 != 3) {
                    M2C_FIELD(M2C_FIELD(var_t0, void **, 0x40), f32 *, 0x10) = (f32) M2C_FIELD(M2C_FIELD(temp_s5, void **, 0x40), f32 *, 0x10);
                    M2C_FIELD(M2C_FIELD(var_t0, void **, 0x40), f32 *, 0x14) = (f32) M2C_FIELD(M2C_FIELD(temp_s5, void **, 0x40), f32 *, 0x14);
                    M2C_FIELD(M2C_FIELD(var_t0, void **, 0x40), f32 *, 0x18) = (f32) M2C_FIELD(M2C_FIELD(temp_s5, void **, 0x40), f32 *, 0x18);
                    sp9C = var_t0;
                    sp6C = var_a0;
                    spB0 = var_v1_2;
                    func_80239094();
                    var_v1_2 += 1;
                    if (var_v1_2 == 0x3C) {
                        var_v0 = M2C_FIELD(var_a0, s32 *, 0x24);
                    } else {
                        goto loop_45;
                    }
                }
                if (var_v0 != 3) {
                    sp9C = var_t0;
                    func_80245208(spAC, 0);
                }
                sp9C = var_t0;
                func_8028A4E0(spB4);
                func_8022FC90(sp9C);
            }
        } else {
            func_802313DC(var_s5, 0x01000000);
            func_8023903C(2);
            temp_v1_2 = sp6C + &D_802AC660;
            if ((M2C_FIELD(temp_v1_2, s32 *, 4) == 1) && (M2C_FIELD(temp_v1_2, s32 *, 0x40) == 1)) {
                func_80227EE0(M2C_FIELD(temp_v1_2, s32 *, 0xE8));
            }
            func_8025C590(spAC);
            if (((D_802AC68C != 0) || (D_802AC690 != 0)) && !(D_802AC5D0 & 0x10)) {
                func_8023EB28(spAC);
            }
        }
    } else if (spAC != 0) {
        D_802AC758 -= 1;
        func_8024585C(spAC);
        func_80245280(1);
        func_8024585C(0);
        if ((D_802AC758 == 0) && (D_800AEE14 != 3)) {
            func_80251534(0);
            func_802313DC(func_802443F4(0), 0x40000);
            func_80247C50(0);
            func_8023E8AC();
        }
    } else if (M2C_FIELD(&D_802AC610, s32 *, 0x14) == 0) {
        func_8023E1D8();
    } else {
        if (M2C_FIELD(&D_802AC610, s32 *, 0x40) == 0) {
            func_80277DF4(2);
        }
        D_802AC5F0 = 0;
        D_802AC7CC = 0x32;
        func_8026C8E8();
        func_8026C894();
        func_802510F0();
        if (!(D_802AC5D0 & 1) && (D_802A01B4 == 0)) {
            D_802AC5D8 = D_802AC5E0;
            D_802AC5D4 = D_802AC5DC;
            D_802AC5DC = D_802AC5DC;
            D_802AC5E0 = D_802AC5E0;
            D_802AC5D0 |= 1;
            D_802AC5E4 = 0;
        }
    }
    D_802A0B94 = 0;
    func_80239430();
}

void func_8024364C(u8 *arg0) {
    func_802362B8(0x7F);
    if (D_802AC768 != NULL) {
        D_802AC768(arg0);
    }
}

static void func_8023EF38(u8 *arg0) {
    f64 temp_fs0;
    f64 temp_fs0_2;
    s32 temp_s3;
    s32 var_s0;
    s32 var_s0_2;
    u8 *temp_v0;

    func_802313DC(arg0, 0x0C000000);
    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) & ~0x4000);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), 0x14, 0);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), -1, 1);
    temp_s3 = func_80238A10(func_8023FAA0, (s32) arg0, 0, 0, 0x130);
    func_802362B8(0x7F);
    D_802A0038 = 0;
    if (D_802A01BC != 0) {
        D_802AC7EC = func_80238A10(func_80241180, 0, 0, 0, 0x130);
        D_802AC7F0 = func_80238A10(func_80240F34, 0, 0, 0, 0x130);
    } else {
        D_802AC7F0 = 0;
        D_802AC7EC = 0;
    }
    func_8026C660(0x1E);
    func_8022979C((s32) M2C_FIELD(arg0, void **, 0x40), 4, 0xC);
    func_8022979C((s32) M2C_FIELD(arg0, void **, 0x40), 5, 0xD);
    func_8029279C(M2C_FIELD(arg0, void **, 0x40), 0, 0, 0, 0.7f);
    func_80239094();
    func_80231408(arg0, 0x04000000);
    M2C_FIELD(arg0, f32 *, 0x68) = 13.0f;
    var_s0 = 0;
    M2C_FIELD(arg0, f32 *, 0x70) = 0.40833336f;
    do {
        temp_fs0 = func_8025E63C();
        func_8028A81C(7, ((f32) temp_fs0 * 100.0f) - 50.0f, 100.0f, ((f32) func_8025E63C() * 100.0f) - 50.0f, (s32) arg0);
        func_8023903C(8);
        var_s0 += 1;
    } while (var_s0 < 8);
    var_s0_2 = 0;
    do {
        temp_fs0_2 = func_8025E63C();
        func_8028A81C(0xD, ((f32) temp_fs0_2 * 50.0f) - 25.0f, 70.0f, ((f32) func_8025E63C() * 50.0f) - 25.0f, (s32) arg0);
        func_8023903C(8);
        var_s0_2 += 1;
    } while (var_s0_2 != 8);
    func_8023903C(0x3C);
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41) && ((M2C_FIELD(arg0, f32 *, 0x68) != 0.0f) || (M2C_FIELD(arg0, f32 *, 0x6C) != 0.0f))) {
loop_10:
        func_80239094();
        if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41)) {
            if ((M2C_FIELD(arg0, f32 *, 0x68) != 0.0f) || (M2C_FIELD(arg0, f32 *, 0x6C) != 0.0f)) {
                goto loop_10;
            }
        }
    }
    func_80238EA8(temp_s3);
    func_8023903C(0x3C);
    if (D_802AC7EC != 0) {
        func_80238EA8(D_802AC7EC);
    }
}

static void func_8023EE40(s32 arg0) {
    s32 temp_s1;
    u8 *temp_v0;

    temp_s1 = func_80238A10(func_8023FAA0, arg0, 0, 0, 0x130);
    func_802313DC((void *) arg0, 0x0C000000);
    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) & ~0x4000);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), 0x14, 0);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), -1, 1);
    if (D_802AC758 < 2) {
        func_802362B8(0x7F);
    }
    func_80231408((void *) arg0, 0x04000000);
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41)) {
        do {
            func_80239094();
        } while (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41));
    }
    func_80238EA8(temp_s1);
    func_8023903C(0x3C);
}

static void func_8023ECF4(u8 *arg0) {
    s32 temp_s1;
    u8 *temp_v0;

    func_802362B8(0x7F);
    D_802A0038 = 0;
    if (D_802A01BC != 0) {
        func_80238A10(func_80241180, 0, 0, 0, 0x130);
        func_80238A10(func_80240F34, 0, 0, 0, 0x130);
    }
    func_802313DC(arg0, 0x08000000);
    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) & ~0x4000);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), 0x13, 0);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), -1, 1);
    func_8022979C((s32) M2C_FIELD(arg0, void **, 0x40), 4, 0xC);
    func_8022979C((s32) M2C_FIELD(arg0, void **, 0x40), 5, 0xD);
    func_8026C660(0x1E);
    temp_s1 = func_80238A10(func_8023FAA0, (s32) arg0, 0, 0, 0x130);
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41)) {
        do {
            func_80239094();
        } while (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41));
    }
    func_80238EA8(temp_s1);
    func_8023903C(0x3C);
}

void func_8023ECEC() {
    if (0) {
        func_8023EB28(0);
    }

}

static void *func_8023EB28(s32 arg0) {
    u8 *sp34;
    f32 sp28[3];
    s32 *temp_s4;
    s32 temp_v1;
    s32 var_s0_2;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_a0;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s3;

    temp_s4 = &(&D_802AC660)[arg0];
    if (M2C_FIELD(temp_s4, s32 *, 4) == 1) {
        var_s0 = (arg0 * 0xC8) + D_800AEDF0;
        M2C_FIELD(var_s0, s32 *, 0x24) = 1;
    } else {
        var_s0 = (arg0 * 0xC8) + D_800AEDF0;
        M2C_FIELD(var_s0, s32 *, 0x24) = 2;
    }
    func_802459BC(arg0);
    M2C_FIELD(var_s0, s32 *, 0x18) = 0x200;
    M2C_FIELD(var_s0, s32 *, 0x1C) = 2;
    M2C_FIELD(var_s0, s32 *, 0x20) = 3;
    M2C_FIELD(var_s0, s32 *, 0x14) = 1;
    temp_v0 = func_802443F4(arg0);
    temp_v1 = M2C_FIELD(temp_s4, s32 *, 4);
    var_s3 = temp_v0;
    if (temp_v1 == 2) {
        *(D_800BD000 + (arg0 * 0x128)) = temp_v0;
    }
    if ((temp_v1 == 1) && (M2C_FIELD(temp_s4, s32 *, 0x40) == 1)) {
        M2C_FIELD(temp_s4, s32 *, 0xE8) = func_802280F4(M2C_FIELD(var_s3, s32 *, 0x40), 0xF);
        var_s1 = &D_802AC660 + (arg0 * 0x10);
        var_s0_2 = 0;
        do {
            func_8023A734(M2C_FIELD(temp_s4, s32 *, 0xE8), var_s0_2, M2C_FIELD(var_s1, s32 *, 0x50));
            var_s0_2 += 1;
            var_s1 += 4;
        } while (var_s0_2 != 4);
    }
    var_a0 = var_s3;
    if (D_802AC660 == 1) {
        sp34 = var_s3;
        func_8023E8FC(sp28);
        var_s3 = sp34;
        M2C_FIELD(M2C_FIELD(var_s3, void **, 0x40), f32 *, 0x10) = sp28[0];
        M2C_FIELD(M2C_FIELD(var_s3, void **, 0x40), f32 *, 0x14) = (f32) (sp28[1] + 600.0f);
        M2C_FIELD(M2C_FIELD(var_s3, void **, 0x40), f32 *, 0x18) = sp28[2];
        var_a0 = var_s3;
    }
    if (func_80232D18(var_a0, 0x10) != 0) {
        do {
            temp_v0_2 = M2C_FIELD(var_s3, void **, 0x40);
            M2C_FIELD(temp_v0_2, f32 *, 0x14) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 0x14) + 100.0f);
        } while (func_80232D18(var_s3, 0x10) != 0);
    }
    return var_s3;
}

static void func_8023E8FC(f32 *arg0) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    M2C_UNK sp44;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    s32 temp_ft2;
    s32 temp_ft3;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_t6;
    u8 *temp_s0;
    u8 *temp_s0_2;

loop_1:
    temp_s0 = D_802A0658 + (M2C_FIELD(&D_802AC660, s32 *, 0xA0) * 0xC);
    temp_fv1 = M2C_FIELD(temp_s0, f32 *, 0);
    temp_fs1 = M2C_FIELD(temp_s0, f32 *, 4);
    temp_fs0 = temp_fv1 + (f32) (s32) ((f32) func_8025E63C() * (M2C_FIELD(temp_s0, f32 *, 0x78) - temp_fv1));
    temp_s0_2 = D_802A0658 + (M2C_FIELD(&D_802AC660, s32 *, 0xA0) * 0xC);
    temp_fv1_2 = M2C_FIELD(temp_s0_2, f32 *, 8);
    temp_fs2 = temp_fv1_2 + (f32) (s32) ((f32) func_8025E63C() * (M2C_FIELD(temp_s0_2, f32 *, 0x80) - temp_fv1_2));
    temp_ft2 = (s32) temp_fs0;
    temp_ft3 = (s32) temp_fs2;
    temp_s3 = func_8026D7D8(temp_ft2, (s32) temp_fs1, temp_ft3);
    if ((M2C_FIELD(&D_802AC660, s32 *, 0xA0) == 0) || (M2C_FIELD(&D_802AC660, s32 *, 0xA0) == 6) || (M2C_FIELD(&D_802AC660, s32 *, 0xA0) == 7) || (var_s0 = 0, (M2C_FIELD(&D_802AC660, s32 *, 0xA0) == 9))) {
        var_s0 = func_8026D7D8(temp_ft2, 0, temp_ft3);
    }
    func_8026E338(temp_fs0, temp_fs1, temp_fs2, arg0, 0);
    sp54 = M2C_FIELD(arg0, f32 *, 0);
    sp58 = M2C_FIELD(arg0, f32 *, 4);
    sp5C = M2C_FIELD(arg0, f32 *, 8);
    if (temp_s3 & 0x60) {
        goto loop_1;
    }
    if (func_8026E938(&sp44) == 20000.0f) {
        goto loop_1;
    }
    temp_v0 = temp_s3 & 0xF;
    var_t6 = var_s0 & 0x60;
    if (temp_v0 != 0) {
        if (temp_v0 == 1) {
            var_t6 = var_s0 & 0x60;
        } else {
            goto loop_1;
        }
    }
    if (var_t6 != 0) {
        goto loop_1;
    }
    temp_v0_2 = var_s0 & 0xF;
    if (temp_v0_2 != 0) {
        if (temp_v0_2 == 1) {

        } else {
            goto loop_1;
        }
    }
}

void func_8023E8AC() {
    if (func_8023AB90() != 0) {
        func_80245280(1);
    }
    func_80238A10(func_8023FD08, 0, 0, 0, 0x130);
}

void func_8023E1D8() {
    s32 spC4;
    s32 spC0;
    u8 spA4;
    s32 *sp4C;
    u8 **sp48;
    s32 *var_v0;
    s32 temp_t0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1;
    s32 var_s2;
    u8 **var_v1;
    u8 **var_v1_2;
    u8 **var_v1_3;
    u8 *temp_v0;

    var_v0 = &D_800BE818;
    var_s0 = 0;
    do {
        if (*var_v0 != 0) {
            sp4C = var_v0;
            func_8028A3D0((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + var_s0 + 0x2C);
        } else {
            sp4C = var_v0;
            func_8028A428((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + var_s0 + 0x2C);
        }
        var_s0 += 1;
        var_v0 = (void *) ((u8 *)var_v0 + 4);
    } while (var_s0 < 5);
    var_s0_2 = 0;
    do {
        if (*(D_800BE830 + ((var_s0_2 / 8) * 4)) & (1 << (var_s0_2 % 8))) {
            func_8028A3D0(var_s0_2);
        } else {
            func_8028A428(var_s0_2);
        }
        var_s0_2 += 1;
    } while (var_s0_2 != 0x2C);
    func_8026C8E8();
    D_802AC5F0 = 0;
    func_8023B318(&D_802A0AB8, 1);
    if (D_802AC628 == 0) {
        func_8023903C(0xB4);
        var_v1 = &D_802A0AB8;
        do {
            sp48 = var_v1;
            func_80280DB4(M2C_FIELD(var_v1, s32 *, 0x10));
            var_v1 += 0x14;
        } while ((u32) var_v1 < (u32) (&D_802A0AB8 + 0x14));
        if (!(D_802AC5D0 & 1)) {
            if (D_802A01B4 == 0) {
                D_802AC5D4 = 0x20;
                D_802AC5DC = 0x20;
                D_802AC5D8 = 0x11;
                D_802AC5E0 = 0x11;
                D_802AC5D0 |= 1;
                D_802AC5E4 = 0;
            }
        }
    } else {
        func_8023903C(0xB4);
        var_v1_2 = &D_802A0AB8;
        do {
            sp48 = var_v1_2;
            func_80280DB4(M2C_FIELD(var_v1_2, s32 *, 0x10));
            var_v1_2 += 0x14;
        } while ((u32) var_v1_2 < (u32) (&D_802A0AB8 + 0x14));
        func_8023903C(2);
        func_8023B450(2, D_802AC628, &spA4);
        func_8023B318(&D_802A0ACC, 4);
        spC4 = func_802811F0(&spA4, 0xBEU, 0xA0U, 0.6f, 0.6f, 2U);
        func_8023B450(1, 9, &spA4);
        spC0 = func_802811F0(&spA4, 0xD6U, 0x50U, 0.8f, 0.8f, 2U);
        temp_v0 = func_8022A6C4(func_8026CE28(0x130), 0x40);
        M2C_FIELD(temp_v0, f32 *, 0x10) = 123.0f;
        M2C_FIELD(temp_v0, f32 *, 0x14) = 108.0f;
        M2C_FIELD(temp_v0, f32 *, 0x18) = 137.0f;
        M2C_FIELD(temp_v0, f32 *, 0x1C) = 122.0f;
        func_8026C93C(0x26);
        var_s0_3 = 0;
        var_s1 = 9;
        var_s2 = 0;
loop_19:
        temp_v0_2 = func_8027EFA8();
        if ((temp_v0_2 & 0x800) && (var_s2 == 1)) {
            var_s2 = 0;
            M2C_FIELD(temp_v0, f32 *, 0x14) = 108.0f;
            M2C_FIELD(temp_v0, f32 *, 0x1C) = 122.0f;
            goto block_31;
        }
        if ((temp_v0_2 & 0x400) && (var_s2 == 0)) {
            var_s2 = 1;
            M2C_FIELD(temp_v0, f32 *, 0x14) = 126.0f;
            M2C_FIELD(temp_v0, f32 *, 0x1C) = 140.0f;
block_31:
            var_s0_3 += 1;
            goto block_32;
        }
        if (func_802399AC(0) & 0x8000) {
            func_8026C660(1);
            if (var_s2 == 0) {
                D_802AC810 = 1;
            } else {
                D_802AC810 = -1;
            }
        } else {
            var_s0_3 += 1;
            if (func_802399AC(0) & 0x4000) {
                D_802AC810 = -1;
            } else {
block_32:
                if (var_s0_3 >= 0x3C) {
                    var_s1 -= 1;
                    var_s0_3 = 0;
                    if (var_s1 < 0) {
                        D_802AC810 = -1;
                    } else {
                        func_80280DB4(spC0);
                        func_8023B450(1, var_s1, &spA4);
                        spC0 = func_802811F0(&spA4, 0xD6U, 0x50U, 0.8f, 0.8f, 2U);
                        func_8026C660(0x37);
                        goto block_36;
                    }
                } else {
block_36:
                    func_80239094();
                    goto loop_19;
                }
            }
        }
        func_8022A1E8(temp_v0);
        func_8026CCBC(0x130);
        if (D_802AC810 == 1) {
            func_80280DB4(spC4);
            func_8023903C(2);
            temp_t0 = M2C_FIELD(&D_802AC610, s32 *, 0x18) - 1;
            M2C_FIELD(&D_802AC610, s32 *, 0x18) = temp_t0;
            func_8023B450(2, temp_t0, &spA4);
            spC4 = func_802811F0(&spA4, 0xBEU, 0xA0U, 0.6f, 0.6f, 2U);
            func_8023903C(0x3C);
            D_800AEE04 = 1;
            D_802AC624 = 2;
            temp_v1 = D_802AC5D0 & ~2;
            D_802AC5D0 = temp_v1;
            if (!(temp_v1 & 1) && (D_802A01B4 == 0)) {
                D_802AC5D4 = 0x21;
                D_802AC5DC = 0x21;
                D_802AC5D8 = 0x11;
                D_802AC5E0 = 0x11;
                D_802AC5D0 = temp_v1 | 1;
                goto block_44;
            }
        } else {
            func_8023903C(0x3C);
            if (!(D_802AC5D0 & 1) && (D_802A01B4 == 0)) {
                D_802AC5D4 = 0x20;
                D_802AC5DC = 0x20;
                D_802AC5D8 = 0x11;
                D_802AC5E0 = 0x11;
                D_802AC5D0 |= 1;
block_44:
                D_802AC5E4 = 0;
            }
        }
        var_v1_3 = &D_802A0ACC;
        do {
            sp48 = var_v1_3;
            func_80280DB4(M2C_FIELD(var_v1_3, s32 *, 0x10));
            var_v1_3 += 0x14;
        } while ((u32) var_v1_3 < (u32) (&D_802A0ACC + 0x50));
        func_80280DB4(spC4);
        func_80280DB4(spC0);
    }
    D_802AC7CC = 0x3C;
    func_8026C8E8();
    func_8026C894();
    func_8023903C(2);
}

void func_8023DB0C() {
    s32 *var_v0;
    s32 *var_v1;
    s32 temp_ft0;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t7;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_t9;

    D_802AC5E8 = 0;
    D_802AC5EC = 0;
    D_802AC5F0 = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 4) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 8) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0xC) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0x38) = (s32) *func_8028A060(1);
    temp_v1 = *func_8028A060(3);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(&D_802AC610, s32 *, 0x10) = 0;
        break;
    case 1:
        M2C_FIELD(&D_802AC610, s32 *, 0x10) = 1;
        break;
    }
    M2C_FIELD(&D_802AC610, s32 *, 0x14) = 2;
    M2C_FIELD(&D_802AC610, s32 *, 0x18) = 3;
    M2C_FIELD(&D_802AC610, s32 *, 0x1C) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0x2C) = 0;
    func_8028A0B4();
    if (M2C_FIELD(&D_802AC610, s32 *, 0x40) != 0) {
        temp_t6 = M2C_FIELD(D_800AEDF0, s32 *, 0x18) | 0x200;
        M2C_FIELD(D_800AEDF0, s32 *, 0x18) = temp_t6;
        M2C_FIELD(D_800AEDF0, s32 *, 0x18) = (s32) (temp_t6 | 3);
        func_80278E84(0, 8);
        func_80277AF8(0, 8);
    } else {
        func_80277E1C();
    }
    var_v0 = &D_802AC660;
    M2C_FIELD(&D_802AC610, s32 *, 0) |= 1;
    M2C_FIELD(&D_802AC660, s32 *, 0) = 0;
    var_v1 = &D_802AC660;
    M2C_FIELD(D_800AEDF0, s32 *, 0x14) = 1;
    do {
        M2C_FIELD(var_v1, s32 *, 4) = 1;
        M2C_FIELD(var_v1, s32 *, 0x40) = 0;
        M2C_FIELD(var_v1, s32 *, 0x90) = 0;
        M2C_FIELD(var_v1, s32 *, 0xA4) = 0;
        M2C_FIELD(var_v1, s32 *, 0x14) = 1;
        var_v0 = (void *) ((u8 *)var_v0 + 0x10);
        var_v1 = (void *) ((u8 *)var_v1 + 4);
        M2C_FIELD(var_v0, s32 *, 0x4C) = 0;
        M2C_FIELD(var_v0, s32 *, 0x48) = 0;
        M2C_FIELD(var_v0, s32 *, 0x44) = 0;
        M2C_FIELD(var_v0, s32 *, 0x40) = 0;
    } while ((s32) var_v0 != (s32) D_802AC6A0);
    M2C_FIELD(&D_802AC660, s32 *, 0x24) = 3;
    M2C_FIELD(&D_802AC660, s32 *, 0x28) = 2;
    M2C_FIELD(&D_802AC660, s32 *, 0x2C) = 2;
    M2C_FIELD(&D_802AC660, s32 *, 0x30) = 0;
    M2C_FIELD(&D_802AC660, s32 *, 0x34) = 0x3C;
    M2C_FIELD(&D_802AC660, s32 *, 0x38) = 1;
    M2C_FIELD(&D_802AC660, s32 *, 0x3C) = 1;
    M2C_FIELD(&D_802AC660, s32 *, 0xA0) = 0;
    D_802AC5D4 = 0x14;
    D_802AC5D8 = 0x10;
    func_802268F4();
    func_802268F4();
    func_802268F4();
    func_802268F4();
    D_802A01B8 = 0;
loop_11:
    if (D_802AC5D0 & 1) {
        D_802A01B8 = 0;
        func_802268F4();
        if (!(D_802AC5E4 & 1)) {
            var_a0 = 0;
            if (D_802AC5E4 & 4) {
                var_a0 = 0xFF;
            }
            func_80281A88(var_a0, var_a0, var_a0, D_802AC7CC);
            func_80281A40();
        }
        if (D_802A01C0 != 0) {
            func_802350F8(1);
            func_80234F6C(1);
            func_80234778(D_802AC5F8, D_802AC5FC, D_802AC600);
            D_802A01C0 = 0;
        }
        func_8026BF68(0);
        func_8029236C();
        func_802923CC();
        func_802268F4();
        func_8027F79C();
        func_8023D8A0();
        func_80239094();
        func_8026BF28(0x7F);
        func_8026BF90(0x7F);
        func_8023D0F8();
        func_8022691C(D_802AC5D4);
        func_802268F4();
        func_802268F4();
        func_802268F4();
        func_8023ADD4(1);
        func_80229280(0);
        func_8023CA94();
        if (!(D_802AC5E4 & 2)) {
            if (D_802AC5E4 & 4) {
                var_a0_2 = 0xFF;
            } else {
                var_a0_2 = 0;
            }
            func_80281AE0(var_a0_2, var_a0_2, var_a0_2, D_802AC7CC);
            func_80281A40();
        }
        D_802AC7CC = 0x20;
        func_802268F4();
        D_802AC5D0 &= ~1;
        func_8023C374();
        func_8023ADD4(0);
        if ((D_802AC5D4 >= 0x28) && !(M2C_FIELD(&D_802AC610, s32 *, 0) & 6)) {
            D_802A01B8 = 1;
        }
        func_8023A640();
    } else if (!(D_802AC5D0 & 0x10) && !(D_802AC5D0 & 2)) {
        if (!(D_802AC5D0 & 0x40) && !(D_802AC5D0 & 0x80)) {
            if ((D_802AC5D0 & 4) && (M2C_FIELD(&D_802AC660, s32 *, 0x28) < 6)) {
                temp_t7 = M2C_FIELD(&D_802AC660, s32 *, 0x34) - 1;
                M2C_FIELD(&D_802AC660, s32 *, 0x34) = temp_t7;
                if (temp_t7 <= 0) {
                    M2C_FIELD(&D_802AC660, s32 *, 0x34) = 0x3C;
                    temp_v0 = M2C_FIELD(&D_802AC660, s32 *, 0x30) - 1;
                    M2C_FIELD(&D_802AC660, s32 *, 0x30) = temp_v0;
                    if (temp_v0 < 0) {
                        temp_t6_2 = M2C_FIELD(&D_802AC660, s32 *, 0x2C) - 1;
                        M2C_FIELD(&D_802AC660, s32 *, 0x30) = 0x3B;
                        M2C_FIELD(&D_802AC660, s32 *, 0x2C) = temp_t6_2;
                        if (temp_t6_2 == 0) {
                            func_80238A10(func_802434F8, 0, 0, 0, 0x130);
                        }
                        goto block_48;
                    }
                    var_s0 = 0;
                    if (temp_v0 == 0) {
                        var_s0 = 0;
                        if (M2C_FIELD(&D_802AC660, s32 *, 0x2C) == 0) {
                            func_8023C170();
                            goto block_48;
                        }
                    }
                } else {
                    goto block_48;
                }
            } else {
                M2C_FIELD(&D_802AC610, f32 *, 0x34) = (f32) (M2C_FIELD(&D_802AC610, f32 *, 0x34) + 1.6666666f);
                if (M2C_FIELD(&D_802AC610, f32 *, 0x34) >= 1.0f) {
                    temp_ft0 = (s32) M2C_FIELD(&D_802AC610, f32 *, 0x34);
                    M2C_FIELD(&D_802AC610, s32 *, 0x30) = (s32) (M2C_FIELD(&D_802AC610, s32 *, 0x30) + temp_ft0);
                    M2C_FIELD(&D_802AC610, f32 *, 0x34) = (f32) (M2C_FIELD(&D_802AC610, f32 *, 0x34) - (f32) temp_ft0);
                }
                D_802AC5F4 += 1.6666666f;
                if (D_802AC5F4 >= 100.0f) {
                    M2C_FIELD(&D_802AC610, s32 *, 0x38) = (s32) (M2C_FIELD(&D_802AC610, s32 *, 0x38) + 1);
                    D_802AC5F4 -= (f32) (s32) D_802AC5F4;
                }
                if (M2C_FIELD(&D_802AC610, s32 *, 0x30) >= 0x05F5E100) {
                    M2C_FIELD(&D_802AC610, s32 *, 0x30) = 0x05F5E0FF;
                }
                if (M2C_FIELD(&D_802AC610, s32 *, 0x38) >= 0x57E40) {
                    M2C_FIELD(&D_802AC610, s32 *, 0x38) = 0x57E3F;
                }
                goto block_48;
            }
        } else {
block_48:
            var_s0 = 0;
        }
        do {
            var_t9 = D_802AC608 + 1;
            if ((&D_802AC7A0)[D_802AC608] != -1) {
                func_802268F4();
                (&D_802AC7A0)[D_802AC608] = -1;
                var_t9 = D_802AC608 + 1;
            }
            D_802AC608 = var_t9;
            if (var_t9 >= 0xA) {
                D_802AC608 = 0;
            }
            var_s0 += 1;
        } while (var_s0 != 0xA);
        func_802268F4();
        func_8023BBCC();
    }
    func_8023903C(1);
    goto loop_11;
}

void func_8023DA04(s32 arg0) {
    s32 temp_t2;
    s32 temp_v1;

    D_802AC5E8 = 0;
    D_802AC5EC = 0;
    D_802AC5F0 = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 4) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 8) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0xC) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0x38) = (s32) *func_8028A060(1);
    temp_v1 = *func_8028A060(3);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(&D_802AC610, s32 *, 0x10) = 0;
        break;
    case 1:
        M2C_FIELD(&D_802AC610, s32 *, 0x10) = 1;
        break;
    }
    M2C_FIELD(&D_802AC610, s32 *, 0x14) = 2;
    M2C_FIELD(&D_802AC610, s32 *, 0x18) = 3;
    M2C_FIELD(&D_802AC610, s32 *, 0x1C) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0x2C) = 0;
    func_8028A0B4();
    if (M2C_FIELD(&D_802AC610, s32 *, 0x40) != 0) {
        temp_t2 = M2C_FIELD(D_800AEDF0, s32 *, 0x18) | 0x200;
        M2C_FIELD(D_800AEDF0, s32 *, 0x18) = temp_t2;
        M2C_FIELD(D_800AEDF0, s32 *, 0x18) = (s32) (temp_t2 | 3);
        func_80278E84(0, 8);
        func_80277AF8(0, 8);
    } else {
        func_80277E1C();
    }
    M2C_FIELD(D_800AEDF0, s32 *, 0x14) = 1;
}

void func_8023D8A0() {
    s32 var_s0;

    func_8026C394();
    func_8026CF90();
    func_80243A30();
    func_8028A584();
    func_8027BBC4();
    func_8027783C();
    func_8028E8E0();
    func_80286E60();
    func_80286F04();
    func_802822B0(3);
    func_8027EBCC();
    func_80227F88();
    var_s0 = 0;
    do {
        func_80247C50(var_s0);
        var_s0 += 1;
    } while (var_s0 != 4);
    func_80245868();
    func_8026F02C();
    func_8027FC08();
    func_8028785C();
    func_80238F40(0x110, 0x3CF);
    func_8022FDE8();
    func_8023D848();
    func_802514CC();
    func_8026D5B4(0);
    func_80236B7C();
    if (D_802A0758 != NULL) {
        func_8026CCBC(0x130);
        D_802A0758 = NULL;
    }
    if (D_802A075C != NULL) {
        func_8026CCBC(0x131);
        D_802A075C = NULL;
    }
    if (D_802A0760 != NULL) {
        func_8022A1E8(D_802A0760);
        D_802A0760 = NULL;
    }
    func_8026CB2C();
}

void func_8023D848() {
    func_80227C18();
    func_80227870();
    func_802276FC(1);
    func_802276E0(0, 0, 0);
    D_802AC768 = NULL;
    D_802AC798 = 0;
    D_802A01BC = 1;
}

s32 func_8023D0F8() {
    f32 sp54;
    u8 *var_v0;
    u8 *var_v0_3;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fv1;
    s32 *var_a0_3;
    s32 *var_s1;
    s32 *var_v0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_t6;
    s32 var_t7;
    s32 var_t8;
    u8 *temp_v0_2;

    if ((D_802AC5D0 & 2) && (M2C_FIELD(&D_802AC610, s32 *, 0x14) != 0)) {
        M2C_FIELD(&D_802AC610, s32 *, 0x14) = (s32) (M2C_FIELD(&D_802AC610, s32 *, 0x14) - 1);
        M2C_FIELD(D_800AEDF0, s32 *, 0x14) = 1;
        var_s0 = 1;
        D_802AC7CC = 0x20;
    } else {
        var_s0 = 0;
    }
    D_802AC5D0 &= ~0x6E;
    D_800AEE14 = 0;
    D_800AEE58 = 0;
    D_800AEEDC = 0;
    D_800AEF20 = 0;
    D_800AEFA4 = 0;
    D_800AEFE8 = 0;
    D_800AF06C = 0;
    D_800AF0B0 = 0;
    M2C_FIELD(D_800AEDF0, s32 *, 0x24) = 1;
    M2C_FIELD(D_800AEDF0, s32 *, 0x344) = 0;
    func_80234858(&sp54, NULL, NULL);
    temp_fv0 = (f32) ((s32) (sp54 / 45.0f) * 0x2D);
    if (temp_fv0 >= 360.0f) {
        var_fa0 = temp_fv0 - 360.0f;
    } else {
        if (temp_fv0 < 0.0f) {
            var_fv1 = temp_fv0 + 360.0f;
        } else {
            var_fv1 = temp_fv0;
        }
        var_fa0 = var_fv1;
    }
    func_80234778(var_fa0, 32768.0f, 32768.0f);
    if (D_802AC5F0 == 0) {
        func_80236218(1);
        D_802A0038 = 0;
    }
    D_802AC758 = 0;
    var_v0 = D_802A04C8;
    var_a0 = 0;
loop_13:
    temp_a1 = M2C_FIELD(var_v0, s32 *, 4);
    D_802AC5E8 = var_a0;
    if (D_802AC5D4 == temp_a1) {
        D_802AC5EC = 1;
        goto block_24;
    }
    temp_a2 = M2C_FIELD(var_v0, s32 *, 0xC);
    if (D_802AC5D4 == temp_a2) {
        D_802AC5EC = 3;
        goto block_24;
    }
    if ((D_802AC5D4 >= M2C_FIELD(var_v0, s32 *, 0)) && (D_802AC5D4 < M2C_FIELD(var_v0, s32 *, 8))) {
        D_802AC5EC = 0;
        goto block_24;
    }
    if ((D_802AC5D4 >= M2C_FIELD(var_v0, s32 *, 8)) && (D_802AC5D4 < temp_a1) && (D_802AC5D4 < temp_a2)) {
        D_802AC5EC = 2;
block_24:
        var_a0_2 = D_802AC5EC;
        if ((var_a0_2 == 0) || (var_a0_2 == 2)) {
            M2C_FIELD(&D_802AC610, s32 *, 0xC) = (s32) (D_802AC5D4 - *(D_802A04C8 + ((D_802AC5E8 * 0x10) + (var_a0_2 * 4))));
        } else {
            M2C_FIELD(&D_802AC610, s32 *, 0xC) = 0;
        }
        if ((M2C_FIELD(&D_802AC610, s32 *, 4) == 1) && (M2C_FIELD(&D_802AC610, s32 *, 8) == 2) && (D_802AC5D4 == 0x3B)) {
            D_802AC5EC = 2;
            M2C_FIELD(&D_802AC610, s32 *, 0xC) = 2;
            var_a0_2 = 2;
        }
        M2C_FIELD(&D_802AC610, s32 *, 4) = D_802AC5E8;
        M2C_FIELD(&D_802AC610, s32 *, 8) = var_a0_2;
        if ((D_802AC5F0 == 0) && (var_s0 == 0)) {
            var_s1 = &D_800BE818;
            var_s0_2 = 0;
            M2C_FIELD(&D_802AC610, s32 *, 0x20) = 0;
            do {
                temp_v0 = func_8028A36C((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + var_s0_2 + 0x2C);
                *var_s1 = temp_v0;
                if (temp_v0 != 0) {
                    if (var_s0_2 < 3) {
                        M2C_FIELD(&D_802AC610, s32 *, 0x20) = (s32) (M2C_FIELD(&D_802AC610, s32 *, 0x20) + 1);
                    }
                } else {
                    *var_s1 = 0;
                }
                var_s0_2 += 1;
                var_s1 = (void *) ((u8 *)var_s1 + 4);
            } while (var_s0_2 < 5);
            var_s0_3 = 0;
            do {
                if (func_8028A36C(var_s0_3) != 0) {
                    var_v0_2 = D_800BE830 + ((var_s0_3 / 8) * 4);
                    var_t8 = *var_v0_2 | (1 << (var_s0_3 % 8));
                } else {
                    var_v0_2 = D_800BE830 + ((var_s0_3 / 8) * 4);
                    var_t8 = *var_v0_2 & ~(1 << (var_s0_3 % 8));
                }
                *var_v0_2 = var_t8;
                var_s0_3 += 1;
            } while (var_s0_3 != 0x2C);
            D_802AC5F4 = 0.0f;
            M2C_FIELD(&D_802AC610, f32 *, 0x34) = 0.0f;
            M2C_FIELD(&D_802AC610, s32 *, 0x38) = (s32) *func_8028A060(1);
            var_a0_2 = D_802AC5EC;
        }
        if ((D_802AC5E8 == 4) || (D_802AC5E8 == 5)) {
            if (var_a0_2 == 3) {
                D_802AC5D0 |= 8;
            } else if (var_a0_2 == 1) {
                var_t7 = D_802AC5D0 | 0x20;
                goto block_56;
            }
        } else if (var_a0_2 == 1) {
            D_802AC5D0 |= 8;
        } else if (var_a0_2 == 3) {
            var_t7 = D_802AC5D0 | 0x20;
block_56:
            D_802AC5D0 = var_t7;
        }
        if (D_802AC5D0 & 0x28) {
            M2C_FIELD(&D_802AC610, s32 *, 0x30) = 0;
            M2C_FIELD(&D_802AC610, s32 *, 0x2C) = 0;
        }
        var_t6 = D_802AC5D0 & 0x20;
        if (!(M2C_FIELD(&D_802AC610, s32 *, 0) & 6)) {
            D_802A0758 = func_8026CE28(0x130);
            D_802A075C = func_8026CE28(0x131);
            temp_v0_2 = func_8022A328(func_80242270, 0x3F, 1, 0, 0);
            D_802A0760 = temp_v0_2;
            M2C_FIELD(temp_v0_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 0xC) | 0x210);
            var_t6 = D_802AC5D0 & 0x20;
        }
        if (var_t6 != 0) {
            func_8026C6D0(1);
            func_8026BF68(M2C_FIELD((D_802A0654 + (D_802AC5E8 * 4)), s8 *, 3));
            return 0;
        }
        func_8026C6D0(0);
        func_8026BF68(M2C_FIELD((*(D_802A063C + (D_802AC5E8 * 4)) + (D_802AC5D4 * 4) + -(*(D_802A04C8 + (D_802AC5E8 * 0x10)) * 4)), s8 *, 3));
        return 0;
    }
    var_a0 += 1;
    var_v0 += 0x10;
    if (var_a0 == 6) {
        if ((D_802AC5D4 >= 0x90) && (D_802AC5D4 < 0x9A)) {
            func_8028A0B4();
            M2C_FIELD(&D_802AC610, s32 *, 0x10) = 0;
            func_8023CECC();
            M2C_FIELD(&D_802AC610, s32 *, 4) = 9;
            M2C_FIELD(&D_802AC610, s32 *, 8) = 0;
            M2C_FIELD(&D_802AC610, s32 *, 0xC) = (s32) (D_802AC5D4 - 0x90);
            D_802AC5D0 |= 4;
            var_a0_3 = &D_802AC660;
            var_v0_3 = D_800AEDF0;
            do {
                temp_v1 = M2C_FIELD(var_a0_3, s32 *, 4);
                var_a0_3 = (void *) ((u8 *)var_a0_3 + 4);
                if (temp_v1 == 0) {
                    M2C_FIELD(var_v0_3, s32 *, 0x24) = 0;
                } else {
                    D_802AC758 += 1;
                    if (temp_v1 == 1) {
                        M2C_FIELD(var_v0_3, s32 *, 0x24) = 1;
                    } else {
                        M2C_FIELD(var_v0_3, s32 *, 0x24) = 2;
                    }
                }
                var_v0_3 += 0xC8;
            } while ((s32) var_a0_3 != (s32) D_802AC670);
            func_8026C6D0(0);
            func_8026BF68(4);
            return 1;
        }
        func_8026BF68(0);
        return -1;
    }
    goto loop_13;
}

void func_8023CECC() {
    u8 *var_v1_2;
    s32 *var_v1;
    s32 *var_v1_3;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_v0;
    s32 var_v0_2;

    D_802A0758 = func_8026CE28(0x130);
    D_802A075C = func_8026CE28(0x131);
    if (D_802AC660 == 0) {
        D_802A0760 = func_8022A328(func_80241BB0, 0x3F, 1, 0, 0);
        func_8023CD1C();
        func_8023CC54(4);
    } else {
        func_8023CD1C();
        func_8023CC54(2);
        var_v1 = &D_802AC660;
        var_a2 = 0;
        do {
            if ((M2C_FIELD(var_v1, s32 *, 4) != 0) && (M2C_FIELD(var_v1, s32 *, 0x90) == 0)) {
                var_a2 += 1;
            }
            var_v1 = (void *) ((u8 *)var_v1 + 4);
        } while ((u32) var_v1 < (u32) D_802AC670);
        var_v1_2 = D_802A0888;
        var_a0 = 3;
        var_v0 = 0x84;
        do {
            M2C_FIELD(var_v1_2, s32 *, 4) = (s32) (var_v0 * 4);
            M2C_FIELD(var_v1_2, s32 *, 0xC) = (s32) ((var_v0 + 0x10) * 4);
            var_v0 += 0x12;
            if ((var_a2 + 2) == var_a0) {
                M2C_FIELD(&D_802A0838, s32 *, 0xC) = (s32) (var_v0 + 4);
                var_v0 += 0x3A;
            }
            var_a0 += 1;
            var_v1_2 += 0x14;
        } while (var_a0 < 7);
        temp_lo = var_a2 * 0x12;
        var_v0_2 = var_a2 + 3;
        var_a2_2 = 3;
        var_v1_3 = &D_802AC660;
        var_a0_2 = 0;
        M2C_FIELD(D_802A084C, s32 *, 0x2C) = (s32) ((temp_lo + 0xAC) * 4);
        M2C_FIELD(D_802A084C, s32 *, 0x34) = (s32) ((temp_lo + 0xBC) * 4);
        do {
            if (M2C_FIELD(var_v1_3, s32 *, 4) != 0) {
                temp_a1 = var_a0_2 * 2;
                if (M2C_FIELD(var_v1_3, s32 *, 0x90) == 0) {
                    temp_lo_2 = var_a2_2 * 0x14;
                    var_a2_2 += 1;
                    *(D_802A084C + temp_lo_2) = temp_a1;
                } else {
                    temp_lo_3 = var_v0_2 * 0x14;
                    var_v0_2 += 1;
                    *(D_802A084C + temp_lo_3) = temp_a1;
                }
            }
            var_a0_2 += 1;
            var_v1_3 = (void *) ((u8 *)var_v1_3 + 4);
        } while (var_a0_2 != 4);
        M2C_FIELD(&D_802A0838, s32 *, 0x10) = (s32) ((var_v0_2 * 0x12) + 0x8C);
        D_802AC7C8 = var_v0_2;
        D_802A0760 = func_8022A328(func_80241590, 0x3F, 1, 0, 0);
    }
    M2C_FIELD(D_802A0760, s32 *, 0xC) = (s32) (M2C_FIELD(D_802A0760, s32 *, 0xC) | 0x210);
}

void func_8023CD1C() {
    s32 *var_a1;
    s32 *var_a1_2;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;

    if (M2C_FIELD(&D_802AC660, s32 *, 0x28) < 6) {
        var_v0 = M2C_FIELD(&D_802AC660, s32 *, 0x2C);
        var_v1 = 1;
        var_a1 = D_802AC770;
        var_a0 = 0;
        do {
            temp_lo = var_v0 / var_v1;
            var_a1 = (void *) ((u8 *)var_a1 + 4);
            M2C_FIELD(var_a1, s32 *, -4) = (s32) (temp_lo * 2);
            if (var_v0 >= (temp_lo * var_v1)) {
                var_v0 %= var_v1;
            }
            var_a0 += 1;
            var_v1 = var_v1 / 10;
        } while (var_a0 <= 0);
        var_v0_2 = M2C_FIELD(&D_802AC660, s32 *, 0x30);
        M2C_FIELD(var_a1, s32 *, 0) = 0x14;
        var_a1_2 = (u8 *)var_a1 + 4;
        var_v1_2 = 0xA;
        var_a0_2 = 0;
        do {
            temp_lo_2 = var_v0_2 / var_v1_2;
            var_a1_2 = (void *) ((u8 *)var_a1_2 + 4);
            M2C_FIELD(var_a1_2, s32 *, -4) = (s32) (temp_lo_2 * 2);
            if (var_v0_2 >= (temp_lo_2 * var_v1_2)) {
                var_v0_2 %= var_v1_2;
            }
            var_a0_2 += 1;
            var_v1_2 = var_v1_2 / 10;
        } while (var_a0_2 != 2);
        return;
    }
    D_802AC770[0] = 0x16;
    D_802AC770[1] = 0x14;
    D_802AC770[2] = 0x16;
    D_802AC770[3] = 0x16;
}

void func_8023CC54(s32 arg0) {
    u8 *var_t0;
    s32 *var_a1;
    s32 temp_lo;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    s32 var_v1;

    var_v1 = 0;
    if (arg0 > 0) {
        var_t0 = D_802AC780;
        var_a1 = &D_802AC660;
        do {
            var_v0 = M2C_FIELD(var_a1, s32 *, 0xA4);
            var_a2 = 1;
            var_a3 = 0;
loop_3:
            temp_lo = var_v0 / var_a2;
            var_t0 += 4;
            M2C_FIELD(var_t0, s32 *, -4) = (s32) (temp_lo * 2);
            if (var_v0 >= (temp_lo * var_a2)) {
                var_v0 %= var_a2;
            }
            var_a3 += 1;
            var_a2 = var_a2 / 10;
            if (var_a3 != 1) {
                goto loop_3;
            }
            var_v1 += 1;
            var_a1 = (void *) ((u8 *)var_a1 + 4);
        } while (var_v1 != arg0);
    }
}

void func_8023CA94() {
    u8 *var_s4;
    s32 *var_s1;
    s32 *var_s2;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s5;

    if (D_802AC5D0 & 4) {
        M2C_FIELD(&D_802AC660, s32 *, 0x30) = 0;
        M2C_FIELD(&D_802AC660, s32 *, 0x34) = 0x3C;
        M2C_FIELD(&D_802AC660, s32 *, 0x2C) = (s32) M2C_FIELD(&D_802AC660, s32 *, 0x28);
        func_80277E1C();
        var_s2 = &D_802AC660;
        var_s4 = D_800AEDF0;
        var_s5 = 0;
        do {
            temp_v0 = M2C_FIELD(var_s2, s32 *, 4);
            M2C_FIELD(var_s4, s32 *, 0x20) = 3;
            M2C_FIELD(var_s4, s32 *, 0x14) = 1;
            M2C_FIELD(var_s4, s32 *, 0x98) = 3;
            M2C_FIELD(var_s2, s32 *, 0xB4) = (s32) (M2C_FIELD(var_s2, s32 *, 0xB4) & ~2);
            M2C_FIELD(var_s4, s32 *, 0x94) = (s32) M2C_FIELD(var_s4, s32 *, 0x18);
            if (temp_v0 == 2) {
                func_80251804(var_s5);
                M2C_FIELD(var_s2, s32 *, 0xB4) = (s32) (M2C_FIELD(var_s2, s32 *, 0xB4) | 8);
            } else if ((temp_v0 == 1) && (M2C_FIELD(var_s2, s32 *, 0x40) == 1)) {
                M2C_FIELD(var_s2, s32 *, 0xE8) = func_802280F4(M2C_FIELD(func_802443F4(var_s5), s32 *, 0x40), 0xF);
                var_s0 = 0;
                var_s1 = (var_s5 * 0x10) + 0x50 + &D_802AC660;
                do {
                    func_8023A734(M2C_FIELD(var_s2, s32 *, 0xE8), var_s0, *var_s1);
                    var_s0 += 1;
                    var_s1 = (void *) ((u8 *)var_s1 + 4);
                } while (var_s0 != 4);
            }
            var_s5 += 1;
            var_s4 += 0xC8;
            var_s2 = (void *) ((u8 *)var_s2 + 4);
        } while (var_s5 != 4);
        if (M2C_FIELD(&D_802AC660, s32 *, 0) == 1) {
            D_802AC620 = 0;
            M2C_FIELD(&D_802AC760, s32 *, 0) = 1;
            M2C_FIELD(&D_802AC760, s32 *, 4) = 1;
            M2C_FIELD(D_802AC820, s32 *, 4) = 0;
            M2C_FIELD(D_802AC820, s32 *, 0) = 0;
            func_80238A10(func_80242FB4, 1, 0, 0, 0x130);
            func_80238A10(func_80242FB4, 2, 0, 0, 0x130);
        }
        func_80238A10(func_80242DA8, 0, 0, 0, 0x130);
    }
}

void func_8023C374() {
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 temp_v1;
    u8 *temp_a0;

    if ((D_802AC5F0 != 0) || (D_802AC5D4 < 0x28) || (M2C_FIELD(&D_802AC610, s32 *, 0) & 6)) {
        D_802AC5D0 &= ~0x10;
        return;
    }
    if (D_802AC5D0 & 4) {
        func_8026C93C(0x1B);
        func_8026C660(0x1E4);
        sp68 = func_802811F0(&D_802A01D8, (s32) ((320.0f - ((f32) func_80280C08(&D_802A01D8) * 0.8f)) / 2.0f) & 0xFFFF, 0x6EU, 0.8f, 0.8f, 0U);
        func_8023903C(0x2B);
        sp64 = func_802811F0(&D_802A01E0, (s32) ((320.0f - ((f32) func_80280C08(&D_802A01E0) * 0.8f)) / 2.0f) & 0xFFFF, 0x6EU, 0.8f, 0.8f, 4U);
        func_80280DB4(sp68);
        func_8023903C(0x23);
        func_80280DB4(sp64);
        func_8023903C(3);
        D_802AC5D0 &= ~0x90;
        return;
    }
    if (!(D_802AC5D0 & 0x28)) {
        func_8026C93C(0x18);
    }
    func_8023903C(0x1E);
    D_802AC5F0 = 1;
    M2C_FIELD(&D_802A01C4, s8 *, 6) = (s8) (D_802AC5EC + 0x11);
    sp6C = func_802811F0(&D_802A01C4, (s32) ((320.0f - ((f32) func_80280C08(&D_802A01C4) * 0.8f)) / 2.0f) & 0xFFFF, 0x3CU, 0.8f, 0.8f, 0U);
    temp_a0 = *(D_802A08F8 + ((D_802AC5E8 * 0x10) + (D_802AC5EC * 4)));
    sp68 = func_802811F0(&D_802A01D0, (s32) ((320.0f - ((f32) func_80280C08(&D_802A01D0) * 0.8f)) / 2.0f) & 0xFFFF, 0x5AU, 0.8f, 0.8f, 0U);
    sp60 = func_802811F0(temp_a0, (s32) ((320.0f - ((f32) func_80280C08(temp_a0) * 0.6f)) / 2.0f) & 0xFFFF, 0x78U, 0.6f, 0.8f, 0U);
    func_8023AF5C(163.0f, 150.0f);
    if (M2C_FIELD(&D_802AC610, s32 *, 0x10) == 0) {
        M2C_FIELD(&D_802AC610, s32 *, 0x28) = (s32) *(D_802A0958 + ((D_802AC5E8 * 0x10) + (D_802AC5EC * 4)));
    } else {
        M2C_FIELD(&D_802AC610, s32 *, 0x28) = (s32) *(D_802A09B8 + ((D_802AC5E8 * 0x10) + (D_802AC5EC * 4)));
    }
    func_8023B7C0(180.0f);
    func_8023903C(0xB4);
    func_80280DB4(sp6C);
    func_80280DB4(sp68);
    func_80280DB4(sp60);
    func_80280DB4(D_802AC7E4);
    func_80280DB4(D_802AC7E8);
    func_8023AAE4();
    D_802AC75C = *(func_8028A060(0x15) + (D_802AC5E8 * 0x10) + (D_802AC5EC * 4));
    func_8023903C(2);
    temp_v1 = D_802AC5D0;
    if (temp_v1 & 8) {
        if (D_802AC5E8 == 0) {
            func_8026C93C(0xE);
        } else if (D_802AC5E8 == 4) {
            if ((D_802AC5D8 == 0x10) || (D_802AC5D8 == 0x11)) {
                func_8026C93C(0xC);
            } else if ((D_802AC5D8 == 0x12) || (D_802AC5D8 == 0x13)) {
                func_8026C93C(0xD);
            }
        } else if (D_802AC5E8 == 5) {
            if ((D_802AC5D8 == 0x10) || (D_802AC5D8 == 0x11)) {
                func_8026C93C(0xF);
            } else if ((D_802AC5D8 == 0x12) || (D_802AC5D8 == 0x13)) {
                func_8026C93C(0x10);
            }
        } else {
            func_8026C93C(0xB);
        }
    } else if (!(temp_v1 & 0x20)) {
        if ((D_802AC5E8 == 0) && (D_802AC5EC == 0) && (D_802AC75C == 0) && (D_802AC640 == 0) && (D_802AC620 == 0)) {
            func_80238A10(func_80241550, D_802AC5E8 + 3, 0, 0, 9);
        } else {
            func_8026C93C(D_802AC5E8 + 3);
        }
    }
    D_802AC5D0 = temp_v1 & ~0x90;
}

void func_8023C170() {
    u8 *var_s1;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    u8 *temp_v0_2;

    if (D_802AC660 == 0) {
        if (D_802AC758 >= 2) {
            goto block_5;
        }
    } else if (M2C_FIELD(&D_802AC760, s32 *, 0) == 1) {
        if (M2C_FIELD(&D_802AC760, s32 *, 4) == 1) {
block_5:
            D_802AC854 = 1;
            func_802510F0();
            func_8026C660(0x1E7);
            func_8026C93C(0x2E);
            var_s1 = D_800AEDF0;
            var_s0 = 0;
            do {
                temp_v0 = M2C_FIELD(var_s1, s32 *, 0x24);
                if ((temp_v0 != 3) && (temp_v0 != 0)) {
                    func_8024585C(var_s0);
                    func_80247C50(var_s0);
                    func_802452E8(1);
                }
                var_s0 += 1;
                var_s1 += 0xC8;
            } while (var_s0 < 4);
            func_80238DFC(0xD0, 0xD0, 0U);
            func_8024585C(0);
            func_8023903C(0x3C);
            func_8026C660(0x1E1);
            temp_v0_2 = func_8022A6C4(func_8026CE28(0x3F), 0);
            M2C_FIELD(temp_v0_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 0xC) | 0x100);
            M2C_FIELD(temp_v0_2, f32 *, 0x28) = 0.1f;
            M2C_FIELD(temp_v0_2, f32 *, 0x2C) = 0.1f;
            M2C_FIELD(temp_v0_2, f32 *, 0x30) = 0.1f;
            M2C_FIELD(temp_v0_2, s16 *, 0x34) = (s16) D_802AC5CC;
            M2C_FIELD(temp_v0_2, f32 *, 0x10) = 0.0f;
            M2C_FIELD(temp_v0_2, f32 *, 0x14) = 0.0f;
            M2C_FIELD(temp_v0_2, f32 *, 0x18) = 0.0f;
            var_s0_2 = 0;
            do {
                M2C_FIELD(temp_v0_2, f32 *, 0x18) = (f32) ((f32) var_s0_2 * 11.111111f);
                func_80239094();
                var_s0_2 += 1;
            } while (var_s0_2 != 0x5A);
            func_8022A1E8(temp_v0_2);
            func_8026CCBC(0x3F);
            func_8026C8E8();
            func_8026C894();
            temp_v1 = D_802AC5D4;
            temp_a0 = D_802AC5D8;
            if (!(D_802AC5D0 & 1) && (D_802A01B4 == 0)) {
                D_802AC5D4 = temp_v1;
                D_802AC5DC = temp_v1;
                D_802AC5D8 = temp_a0;
                D_802AC5E0 = temp_a0;
                D_802AC5D0 |= 1;
                D_802AC5E4 = 0;
            }
        }
    }
}

s32 func_8023BBCC() {
    s32 *sp7C;
    s32 *var_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_v0;
    u8 *temp_v0;

    if ((D_802A0B80 != 0) || (D_802A01B8 == 0)) {
        return 1;
    }
    if (D_802AC5D0 & 4) {
        var_v0 = func_8023AEDC(1);
    } else {
        var_v0 = func_8023AEDC(0);
    }
    if (!(var_v0 & 0x1000)) {
        return 1;
    }
    func_8026C660(0x2F);
    D_802A0B80 = 1;
    func_8023AA78(1);
    func_80239094();
    if (func_802362A8() & 0xF) {
        func_80238CF8(0x401, 0x401);
        func_80238CF8(0x90, 0x90);
        func_80238CF8(0x170, 0x170);
    }
    temp_v0 = func_8022A328(func_8023FC80, 0x9D, 1, 0, 0);
    D_802AC818 = temp_v0;
    M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) | 0x80);
    func_8023B8D0();
    func_8026BF90(0x40);
    if (D_802AC5D0 & 0x2C) {
        var_a0 = 0;
        if (D_802AC5D0 & 4) {
            var_a0 = 1;
        }
        if (!(func_8023AEDC(var_a0) & 0x1000)) {
            do {
                func_80239094();
                var_a0_2 = 0;
                if (D_802AC5D0 & 4) {
                    var_a0_2 = 1;
                }
            } while (!(func_8023AEDC(var_a0_2) & 0x1000));
        }
        func_8026C660(2);
        func_8026BF90(0x7F);
        func_8023AC38();
        func_8022A1E8(D_802AC818);
        func_8023903C(2);
        func_8023AA78(0);
    } else {
        func_802443F4(func_80243DDC());
        if ((D_802AC75C == 0) || (func_8023AB90() == 0)) {
            if (!(func_8023AEDC(0) & 0x1000)) {
                do {
                    func_80239094();
                } while (!(func_8023AEDC(0) & 0x1000));
            }
            func_8026C660(2);
            func_8026BF90(0x7F);
            func_8023AC38();
            func_8022A1E8(D_802AC818);
            func_8023903C(2);
            func_8023AA78(0);
        } else {
            func_8027F658(func_8023FC00, D_802A0B84, 0x130U, 0xEU, 0xEU);
            func_8027F400();
            func_8027F428();
            if (D_802AC810 == 2) {
                func_8023903C(0x3C);
                func_8023AA78(0);
                D_802A01B8 = 0;
                D_802AC7CC = 0x3C;
                func_8026C8E8();
                func_8026C894();
                var_v0_2 = &D_800BE818;
                var_s0 = 0;
                do {
                    if (*var_v0_2 != 0) {
                        sp7C = var_v0_2;
                        func_8028A3D0((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + var_s0 + 0x2C);
                    } else {
                        sp7C = var_v0_2;
                        func_8028A428((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + var_s0 + 0x2C);
                    }
                    var_s0 += 1;
                    var_v0_2 = (void *) ((u8 *)var_v0_2 + 4);
                } while (var_s0 < 5);
                var_s0_2 = 0;
                do {
                    if (*(D_800BE830 + ((var_s0_2 / 8) * 4)) & (1 << (var_s0_2 % 8))) {
                        func_8028A3D0(var_s0_2);
                    } else {
                        func_8028A428(var_s0_2);
                    }
                    var_s0_2 += 1;
                } while (var_s0_2 != 0x2C);
                *func_8028A060(1) = D_802AC648;
                if (!(D_802AC5D0 & 1) && (D_802A01B4 == 0)) {
                    D_802AC5D4 = 0x21;
                    D_802AC5DC = 0x21;
                    D_802AC5D8 = 0x11;
                    D_802AC5E0 = 0x11;
                    D_802AC5D0 |= 1;
                    D_802AC5E4 = 0;
                }
                func_8023ADD4(1);
                func_80229280(1);
                D_802AC5F0 = 0;
                func_8023AC38();
                func_8022A1E8(D_802AC818);
                D_802AC5D0 |= 0x80;
            } else {
                func_8026BF90(0x7F);
                func_8023AC38();
                func_8022A1E8(D_802AC818);
                func_8023903C(2);
                func_8023AA78(0);
            }
        }
    }
    D_802A0B80 = 0;
    return 0;
}

void func_8023B8D0() {
    u8 sp30[8];
    s32 sp38;
    f32 temp_ft1;
    s32 temp_t8;
    s32 var_s1;
    s32 var_s2;
    s32 var_v0;
    void **var_s3;
    u8 *temp_v0;

    if (!(D_802AC5D0 & 4)) {
        D_802A0B1C = *(D_802A08F8 + ((D_802AC5E8 * 0x10) + (D_802AC5EC * 4)));
    } else {
        D_802A0B1C = &D_802A0448;
    }
    if (D_802AC5D0 & 0x2C) {
        func_8023B318(&D_802A0B1C, 1);
        temp_t8 = D_802AC5D0 & 4;
        var_v0 = temp_t8;
        if (temp_t8 == 0) {
            func_8023B7C0(154.0f);
            var_v0 = D_802AC5D0 & 4;
        }
    } else {
        func_8023B450(2, func_80287680(), sp30);
        D_802AC814 = func_802811F0(sp30, 0xDCU, 0x50U, 0.6f, 0.6f, 2U);
        var_s3 = &D_802AC7F8;
        var_s1 = 0;
        var_s2 = 0;
        sp38 = func_8026CE28(0x19);
        do {
            temp_v0 = func_8022A6C4(sp38, 0x40);
            *var_s3 = temp_v0;
            var_s3 += 4;
            if ((func_8028A36C((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + var_s1 + 0x2C) != 0) || ((var_s1 == 3) && (*(&D_800BE818 + var_s2) != 0))) {
                M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) | 0x100);
            } else {
                M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) | 0x1180);
                M2C_FIELD(temp_v0, s16 *, 0x36) = 0x64;
            }
            temp_ft1 = (f32) var_s1;
            var_s1 += 1;
            var_s2 += 4;
            M2C_FIELD(temp_v0, f32 *, 0x14) = 9.95f;
            M2C_FIELD(temp_v0, f32 *, 0x18) = 900.3f;
            M2C_FIELD(temp_v0, f32 *, 0x28) = 0.05f;
            M2C_FIELD(temp_v0, f32 *, 0x2C) = 0.05f;
            M2C_FIELD(temp_v0, f32 *, 0x10) = (f32) ((temp_ft1 * 5.8f) + 0.65f);
            M2C_FIELD(temp_v0, f32 *, 0x30) = 0.05f;
            M2C_FIELD(temp_v0, s16 *, 0x34) = (s16) D_802AC5CC;
        } while (var_s1 != 5);
        func_8023B7C0(154.0f);
        if ((D_802AC75C == 0) || (func_8023AB90() == 0)) {
            func_8023B318(&D_802A0B1C, 3);
            func_802814D8(D_802A0B40, 0xFFE8U, 0U);
            var_v0 = D_802AC5D0 & 4;
        } else {
            func_8023B318(&D_802A0B1C, 5);
            func_802814D8(D_802A0B40, 0xFFE8U, 0U);
            var_v0 = D_802AC5D0 & 4;
        }
    }
    if (var_v0 == 0) {
        func_8023AF5C(160.0f, 125.0f);
    }
}

static void func_8023B7C0(f32 arg0) {
    u8 sp24;
    s32 temp_t7;
    s32 var_s0;

    func_8023B450(8, D_802AC638, &sp24);
    var_s0 = (u32) arg0;
    temp_t7 = var_s0 & 0xFFFF;
    D_802AC7E4 = func_802811F0(&D_802A039C, 0x2DU, temp_t7 & 0xFFFF, 0.6f, 0.8f, 2U);
    D_802AC7E8 = func_802811F0(&sp24, 0xB4U, temp_t7 & 0xFFFF, 0.6f, 0.8f, 3U);
}

static void func_8023B450(s32 arg0, s32 arg1, u8 *arg2) {
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_lo_4;
    s32 temp_lo_5;
    s32 temp_lo_6;
    s32 temp_lo_7;
    s32 temp_lo_8;
    s32 temp_t1;
    s32 temp_t6;
    s32 var_a1;
    s32 var_t0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a3;
    u8 *temp_a3_2;
    u8 *temp_a3_3;
    u8 *var_a3;
    u8 *var_a3_2;

    var_t0 = arg1;
    temp_a1 = arg0 - 1;
    var_v0 = 0;
    var_v1 = 1;
    if (temp_a1 > 0) {
        temp_t6 = (arg0 - 1) & 3;
        if (temp_t6 != 0) {
            do {
                var_v0 += 1;
                var_v1 *= 0xA;
            } while (temp_t6 != var_v0);
            if (var_v0 != temp_a1) {
                goto block_5;
            }
        } else {
block_5:
            do {
                var_v0 += 4;
                var_v1 = var_v1 * 0xA * 0xA * 0xA * 0xA;
            } while (var_v0 != temp_a1);
        }
        var_v0 = 0;
    }
    var_a1 = 0;
    if (arg0 > 0) {
        temp_t1 = arg0 & 3;
        if (temp_t1 != 0) {
            var_a3 = arg2;
            do {
                temp_lo = var_t0 / var_v1;
                var_a1 += 1;
                var_a3 += 1;
                M2C_FIELD(var_a3, s8 *, -1) = (s8) (temp_lo + 0x10);
                if (var_t0 >= (temp_lo * var_v1)) {
                    var_t0 %= var_v1;
                }
                var_v0 += 1;
                var_v1 = var_v1 / 10;
            } while (temp_t1 != var_v0);
            if (var_v0 != arg0) {
                goto block_15;
            }
        } else {
block_15:
            var_a3_2 = &arg2[var_a1];
            do {
                temp_lo_2 = var_t0 / var_v1;
                temp_a3 = var_a3_2 + 1;
                M2C_FIELD(temp_a3, s8 *, -1) = (s8) (temp_lo_2 + 0x10);
                if (var_t0 >= (temp_lo_2 * var_v1)) {
                    var_t0 %= var_v1;
                }
                temp_lo_3 = var_v1 / 10;
                temp_a3_2 = temp_a3 + 1;
                temp_lo_4 = var_t0 / temp_lo_3;
                M2C_FIELD(temp_a3_2, s8 *, -1) = (s8) (temp_lo_4 + 0x10);
                if (var_t0 >= (temp_lo_4 * temp_lo_3)) {
                    var_t0 %= temp_lo_3;
                }
                temp_lo_5 = temp_lo_3 / 10;
                temp_a3_3 = temp_a3_2 + 1;
                temp_lo_6 = var_t0 / temp_lo_5;
                M2C_FIELD(temp_a3_3, s8 *, -1) = (s8) (temp_lo_6 + 0x10);
                if (var_t0 >= (temp_lo_6 * temp_lo_5)) {
                    var_t0 %= temp_lo_5;
                }
                temp_lo_7 = temp_lo_5 / 10;
                var_a1 = var_a1 + 1 + 1 + 1 + 1;
                var_a3_2 = temp_a3_3 + 1;
                temp_lo_8 = var_t0 / temp_lo_7;
                M2C_FIELD(var_a3_2, s8 *, -1) = (s8) (temp_lo_8 + 0x10);
                if (var_t0 >= (temp_lo_8 * temp_lo_7)) {
                    var_t0 %= temp_lo_7;
                }
                var_v0 += 4;
                var_v1 = temp_lo_7 / 10;
            } while (var_v0 != arg0);
        }
    }
    arg2[var_a1] = 0;
}

static void func_8023B318(u8 **arg0, s32 arg1) {
    f32 temp_fs0;
    f32 temp_ft2;
    f32 temp_fv0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_s1;
    u16 temp_a1;
    u8 **var_s0;

    if (0) {
        func_8023B2AC(0);
    }
    var_s1 = 0;
    if (arg1 > 0) {
        var_s0 = arg0;
        do {
            temp_fs0 = M2C_FIELD(var_s0, f32 *, 8);
            temp_ft2 = M2C_FIELD(var_s0, f32 *, 4);
            temp_a1 = (s32) ((320.0f - ((f32) func_80280C08(M2C_FIELD(var_s0, u8 **, 0)) * temp_fs0)) / 2.0f) & 0xFFFF;
            var_a2 = (u32) temp_ft2;
            temp_fv0 = M2C_FIELD(var_s0, f32 *, 8);
            temp_v0 = func_802811F0(M2C_FIELD(var_s0, u8 **, 0), temp_a1, var_a2 & 0xFFFF, temp_fv0, temp_fv0, (u8) M2C_FIELD(var_s0, s32 *, 0xC));
            var_s1 += 1;
            var_s0 += 0x14;
            M2C_FIELD(var_s0, s32 *, -4) = temp_v0;
        } while (var_s1 != arg1);
    }
}

static s32 func_8023B2AC(f32 arg0) {
    return (s32) ((320.0f - ((f32) func_80280C08(0 /* FIXME unset $a0 */) * arg0)) / 2.0f);
}

static void func_8023AF5C(f32 arg0, f32 arg1) {
    u8 sp4C;
    f32 temp_ft2;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fs3;
    s32 temp_lo;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_a2_2;
    u8 *var_a3;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;

    var_a0 = D_802AC624;
    var_a1 = 0xA;
    var_a3 = &sp4C;
    var_a2 = 0;
    do {
        temp_lo = var_a0 / var_a1;
        var_a3 += 1;
        M2C_FIELD(var_a3, s8 *, -1) = (s8) (temp_lo + 0x10);
        if (var_a0 >= (temp_lo * var_a1)) {
            var_a0 %= var_a1;
        }
        var_a2 += 1;
        var_a1 = var_a1 / 10;
    } while (var_a2 != 2);
    M2C_FIELD(var_a3, u8 *, 0) = 0;
    if (D_800AEE04 >= 2) {
        var_fs3 = 16.0f;
        temp_v0 = func_8026CE28(0x34E);
        D_802AC7E0 = temp_v0;
        temp_v0_2 = func_8022A6C4(temp_v0, 0x3F);
        var_fs1 = arg0 - 28.0f;
        temp_fv0 = var_fs1 - 28.0f;
        D_802AC7DC = temp_v0_2;
        M2C_FIELD(temp_v0_2, f32 *, 0x10) = (f32) (temp_fv0 + 16.0f);
        var_fs0 = arg1 + 1.0f;
        M2C_FIELD(D_802AC7DC, f32 *, 0x14) = var_fs0;
        M2C_FIELD(D_802AC7DC, f32 *, 0x18) = (f32) (temp_fv0 + 16.0f + 16.0f);
        var_fs2 = var_fs0 + 16.0f;
        M2C_FIELD(D_802AC7DC, f32 *, 0x1C) = var_fs2;
    } else {
        var_fs3 = 0.0f;
        var_fs0 = arg1 + 1.0f;
        var_fs1 = arg0 - 28.0f;
        D_802AC7E0 = NULL;
        var_fs2 = var_fs0 + 16.0f;
    }
    temp_v0_3 = func_8026CE28(0x130);
    D_802AC7D0 = temp_v0_3;
    temp_v0_4 = func_8022A6C4(temp_v0_3, 0x3F);
    D_802AC7D4 = temp_v0_4;
    M2C_FIELD(temp_v0_4, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_4, s32 *, 0xC) | 0x10);
    M2C_FIELD(D_802AC7D4, f32 *, 0x10) = (f32) (var_fs1 + var_fs3);
    M2C_FIELD(D_802AC7D4, f32 *, 0x14) = var_fs0;
    M2C_FIELD(D_802AC7D4, f32 *, 0x18) = (f32) (var_fs1 + 16.0f + var_fs3);
    temp_ft2 = (arg0 - 36.0f) + 24.0f + 8.0f + var_fs3;
    M2C_FIELD(D_802AC7D4, f32 *, 0x1C) = var_fs2;
    var_a1_2 = (u32) temp_ft2;
    var_a2_2 = (u32) arg1;
    D_802AC7D8 = func_802811F0(&sp4C, var_a1_2 & 0xFFFF, var_a2_2 & 0xFFFF, 0.6f, 0.8f, 2U);
}

s32 func_8023AEDC(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    if (arg0 != 0) {
        var_s0 = 0;
        do {
            if (!(func_8023A038(var_s0) & 8)) {
                var_s1 |= func_802399AC(var_s0);
            }
            var_s0 += 1;
        } while (var_s0 != 4);
    } else {
        var_s1 = func_802399AC(0);
    }
    return var_s1;
}

void func_8023AED0(s32 arg0) {
    D_802AC7CC = arg0;
}

void func_8023AE6C(s32 arg0, s32 arg1, s32 arg2) {
    if (!(D_802AC5D0 & 1) && (D_802A01B4 == 0)) {
        D_802AC5D4 = arg0;
        D_802AC5DC = arg0;
        D_802AC5D8 = arg1;
        D_802AC5E0 = arg1;
        D_802AC5D0 |= 1;
        D_802AC5E4 = arg2;
    }
}

void func_8023ADD4(s32 arg0) {
    if ((arg0 != 0) && (D_802A01B4 == 0)) {
        D_802A01B4 = 1;
        func_80238DFC(0x70, 0x70, 0U);
        func_80238DFC(0xD0, 0xF0, 0U);
        return;
    }
    if ((arg0 == 0) && (D_802A01B4 != 0)) {
        D_802A01B4 = 0;
        func_80238CF8(0x70, 0x70);
        func_80238CF8(0xD0, 0xF0);
        func_80238CF8(0x90, 0x90);
    }
}

void func_8023AC38() {
    s32 temp_t9;
    s32 var_t6;
    s32 var_v1;
    u8 **var_s0;
    u8 **var_s0_2;
    u8 **var_s0_3;
    void **var_s0_4;

    if (D_802AC5D0 & 0x2C) {
        var_s0 = &D_802A0B1C;
        do {
            func_80280DB4(M2C_FIELD(var_s0, s32 *, 0x10));
            var_s0 += 0x14;
        } while ((u32) var_s0 < (u32) (&D_802A0B1C + 0x14));
        temp_t9 = D_802AC5D0 & 4;
        var_v1 = temp_t9;
        if (temp_t9 == 0) {
            func_80280DB4(D_802AC7E4);
            func_80280DB4(D_802AC7E8);
            var_t6 = D_802AC5D0 & 4;
            goto block_15;
        }
    } else {
        if ((D_802AC75C == 0) || (func_8023AB90() == 0)) {
            var_s0_2 = &D_802A0B1C;
            do {
                func_80280DB4(M2C_FIELD(var_s0_2, s32 *, 0x10));
                var_s0_2 += 0x14;
            } while ((u32) var_s0_2 < (u32) (&D_802A0B1C + 0x3C));
        } else {
            var_s0_3 = &D_802A0B1C;
            do {
                func_80280DB4(M2C_FIELD(var_s0_3, s32 *, 0x10));
                var_s0_3 += 0x14;
            } while ((u32) var_s0_3 < (u32) (&D_802A0B1C + 0x64));
        }
        var_s0_4 = &D_802AC7F8;
        do {
            func_8022A1E8(*var_s0_4);
            var_s0_4 += 4;
        } while ((void *) var_s0_4 != (void *) &D_802AC80C);
        func_8026CCBC(0x19);
        func_80280DB4(D_802AC814);
        func_80280DB4(D_802AC7E4);
        func_80280DB4(D_802AC7E8);
        var_t6 = D_802AC5D0 & 4;
block_15:
        var_v1 = var_t6;
    }
    if (var_v1 == 0) {
        func_8023AAE4();
    }
}

s32 func_8023AB90() {
    s32 temp_v0;
    s32 var_v0;
    u8 *temp_v0_2;

    if (0) {
        func_8023AB54(0, 0);
    }
    temp_v0 = func_80243DDC();
    temp_v0_2 = func_802443F4(temp_v0);
    if ((*(&D_800AEE14 + (temp_v0 * 0xC8)) == 3) || (M2C_FIELD(temp_v0_2, f32 *, 0x68) != 0.0f) || (M2C_FIELD(temp_v0_2, f32 *, 0x6C) != 0.0f) || (var_v0 = 1, (func_80244BA4(temp_v0, 0x20) != 0))) {
        var_v0 = 0;
    }
    return var_v0;
}

static void func_8023AB54(u8 **arg0, s32 arg1) {
    s32 var_s0;
    u8 **var_s1;

    var_s0 = 0;
    if (arg1 > 0) {
        var_s1 = arg0;
        do {
            func_80280DB4(M2C_FIELD(var_s1, s32 *, 0x10));
            var_s0 += 1;
            var_s1 += 0x14;
        } while (var_s0 != arg1);
    }
}

void func_8023AAE4() {
    func_8022A1E8(D_802AC7D4);
    func_8026CCBC(0x130);
    if (D_802AC7E0 != NULL) {
        func_8022A1E8(D_802AC7DC);
        func_8026CCBC(0x34E);
    }
    func_80280DB4(D_802AC7D8);
}

void func_8023AA78(s32 arg0) {
    if (arg0 != 0) {
        func_80238DFC(0x30, 0x3CF, 0U);
        func_80238DFC(0x401, 0x403, 0U);
        func_80229280(1);
        return;
    }
    func_80238CF8(0x30, 0x3CF);
    func_80238CF8(0x401, 0x403);
    func_80229280(0);
}

s32 func_8023AA60(s32 arg0) {
    return *(D_802AC868 + (arg0 * 4));
}

s32 func_8023A870(s32 arg0, s32 arg1) {
    u8 *sp34;
    s32 temp_t5;
    s32 temp_v1;
    s32 var_t0;
    u8 *temp_v0;
    u8 *temp_v0_2;

    if (!(D_802A01B0 & 2)) {
        if (!(D_802AC5D0 & 1)) {
            func_80245208(arg0, 1);
            sp34 = func_802443F4(arg0);
            *func_8028A060(1) = D_802AC648;
            temp_v1 = D_802AC5D0;
            if ((temp_v1 & 4) || ((temp_v1 & 8) && (arg0 != 0))) {
                temp_t5 = arg0 * 4;
                *(D_802AC714 + temp_t5) = 2;
                func_802313DC(sp34, 0x7FFFF);
                D_802A01BC = 0;
            } else {
                if (D_802A01BC != 0) {
                    func_802350F8(1);
                    func_80234F6C(1);
                    func_80234858(&D_802AC5F8, &D_802AC5FC, &D_802AC600);
                    D_802A01C0 = 1;
                    if (D_802AC5D0 & 8) {
                        func_80251534(0);
                    }
                }
                D_802A01B8 = 0;
                var_t0 = arg0 * 4;
                D_802AC5D0 = temp_v1 | 0x92;
            }
            temp_v0 = M2C_FIELD(sp34, void **, 0x40);
            M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) & ~0x4000);
            temp_v0_2 = M2C_FIELD(sp34, void **, 0x40);
            M2C_FIELD(temp_v0_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 0xC) | 0x40);
            if (arg1 == 4) {
                arg1 = D_802AC798;
            }
            *(&D_802AC858 + var_t0) = arg1;
            func_80238A10(func_8023F26C, (s32) (var_t0 + D_802A0B98), 0, 0, 0x130);
            return 1;
        }
        /* Duplicate return node #15. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

void func_8023A864(s32 arg0) {
    D_802A01B8 = arg0;
}

void func_8023A858(s32 arg0) {
    D_802A01BC = arg0;
}

void func_8023A84C(s32 arg0) {
    D_802AC798 = arg0;
}

s32 *func_8023A840() {
    return &D_802AC610;
}

s32 *func_8023A834() {
    return &D_802AC660;
}

void func_8023A734(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (arg1 * 0x2C) + D_802A0BA8;
    temp_v1 = arg2 * 4;
    func_80228008(arg0, *(D_802A0CB0 + (arg1 * 4)), *(temp_v0 + temp_v1));
    if ((s32) temp_v0 == (s32) D_802A0BA8) {
        if (*(D_802A0CC8 + temp_v1) != 0) {
            func_80228008(arg0, 8, -1);
            return;
        }
        func_80228008(arg0, 8, 0x4F);
        return;
    }
    if ((s32) temp_v0 == (s32) D_802A0C00) {
        func_80228008(arg0, 5, M2C_FIELD((D_802A0BA8 + temp_v1), s32 *, 0xB0));
        return;
    }
    if ((s32) temp_v0 == (s32) D_802A0C2C) {
        func_80228008(arg0, 0xC, M2C_FIELD((D_802A0BA8 + temp_v1), s32 *, 0xDC));
    }
}

void func_8023A68C() {
    func_80297D30(0xF, D_802A0CF4);
    D_802AC604 = func_80238A10(func_8023DB0C, 0, 0, 0, 9);
    D_802AC5D0 = 0x90;
    D_802A01B4 = 0;
    D_802A01B8 = 0;
    D_802A01BC = 1;
    D_802AC7CC = 0x20;
    M2C_FIELD(&D_802AC610, s32 *, 0x3C) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0x40) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0x44) = 0;
    M2C_FIELD(&D_802AC610, s32 *, 0x48) = 0;
    func_8023A640();
    func_802513E0();
}

void func_8023A640() {
    u8 *var_v1;

    var_v1 = D_802AC7A8;
    D_802AC7A4 = -1;
    D_802AC7A4 = -1;
    do {
        var_v1 += 0x10;
        M2C_FIELD(var_v1, s32 *, -0xC) = -1;
        M2C_FIELD(var_v1, s32 *, -8) = -1;
        M2C_FIELD(var_v1, s32 *, -4) = -1;
        M2C_FIELD(var_v1, s32 *, -0x10) = -1;
    } while ((void *) var_v1 != (void *) &D_802AC7C8);
    D_802AC608 = 0;
}
