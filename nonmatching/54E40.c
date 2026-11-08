/*
 * NON_MATCHING: main_code's 54E40, complete: 72 functions (us
 * 0x8023A640-0x80243888): tasks spawned through func_80238A10 and
 * func_8022A328, and the display lists of three digit counters. Not
 * built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 5601, eu 5609, jp 5584
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

typedef struct {
    /* 0x00 */ u8 *str;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scale;
    /* 0x0C */ s32 mode;
    /* 0x10 */ s32 handle;
} TextItem; /* size = 0x14 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
} UnkStruct_802AC610; /* size = 0x50 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4[4];
    /* 0x14 */ s32 unk14[4];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40[4];
    /* 0x50 */ s32 unk50[4][4];
    /* 0x90 */ s32 unk90[4];
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ s32 unkA4[4];
    /* 0xB4 */ u8 unkB4[0x34];
    /* 0xE8 */ s32 unkE8[4];
} UnkStruct_802AC660; /* size >= 0xF8 */

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} UnkStruct_8023FD08_48_4;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_8023FD08_48_4 *unk4;
} UnkStruct_8023FD08_48;

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C[0xC];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ u8 unk36[0x12];
    /* 0x48 */ UnkStruct_8023FD08_48 *unk48;
} UnkStruct_8023FD08;

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

void func_802268F4(s32);
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
void func_8027F820(void *);
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
s32 func_802909FC(void *, void (*)());
void func_80245150();
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
extern u8 D_802A01C4[];
extern u8 D_802A01D0[];
extern u8 D_802A01D8[];
extern u8 D_802A01E0[];
extern u8 D_802A039C;
extern u8 D_802A0448[];
extern u8 D_802A04A4[];
extern u8 D_802A04B4[];
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
extern u8 *D_802A08F8[][4];
extern s32 D_802A0958[][4];
extern s32 D_802A09B8[][4];
extern TextItem D_802A0A18[];
extern TextItem D_802A0A68[];
extern TextItem D_802A0A7C[];
extern TextItem D_802A0AB8[];
extern TextItem D_802A0ACC[];
extern TextItem D_802A0B1C[];
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
extern UnkStruct_802AC610 D_802AC610;
extern s32 D_802AC624;
extern s32 D_802AC628;
extern UnkStruct_802AC660 D_802AC660;
extern u8 D_802AC670[];
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
extern UnkStruct_8023FD08 *D_802AC7F8[];
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
static void func_8023AB54(TextItem *items, s32 n);
static void func_8023AB4C(void);
static s32 func_8023AB90(void);
static void func_8023AC38(void);
void func_8023ADD4(s32 arg0);
void func_8023AE6C(s32 arg0, s32 arg1, s32 arg2);
void func_8023AED0(s32 arg0);
s32 func_8023AEDC(s32 arg0);
static void func_8023AF5C(f32 arg0, f32 arg1);
static s32 func_8023B2AC(u8 *str, f32 scale);
static void func_8023B318(TextItem *items, s32 n);
static void func_8023B450(s32 arg0, s32 arg1, u8 *arg2);
static void func_8023B7C0(f32 arg0);
static void func_8023B8D0();
s32 func_8023BBCC(void);
static void func_8023C170(void);
void func_8023C374(void);
static void func_8023CC4C(void);
static void func_8023CA94(void);
void func_8023CC54(s32 arg0);
void func_8023CD1C(void);
static void func_8023D0F0(void);
static void func_8023CECC(void);
static void func_8023D840(void);
static s32 func_8023D0F8(void);
void func_8023D848(void);
static void func_8023D8A0(void);
static void func_8023D9FC(void);
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
s32 func_8023FC00(u8 arg0, u16 arg1);
void func_8023FC80(s32 arg0, u8 **arg1);
void func_8023FD08();
void func_80240F34(void);
void func_80241180(void);
void func_80241550(void);
void func_80241590(s32 arg0, Gfx **gdl);
void func_80241BB0(s32 arg0, Gfx **gdl);
void func_80242268(void);
void func_80242270(s32 arg0, Gfx **gdl);
static void func_80242994(void);
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

#if VERSION_JP
#define func_802811F0 func_802810A0
#define STR_A D_8029FB00_jp
#define STR_B D_8029FB10_jp
#define X_01D8 0x70
#define X_01E0 0x83
extern u8 D_8029FB00_jp[];
extern u8 D_8029FB10_jp[];
#else
#define STR_A D_802A04A4
#define STR_B D_802A04B4
#define X_01D8 func_8023B2AC(D_802A01D8, 0.8f)
#define X_01E0 func_8023B2AC(D_802A01E0, 0.8f)
#endif

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
    if (D_802AC610.unk40 == 0) {
        func_80277DF4(0x407);
        if (M2C_FIELD(D_800AEDF0, s32 *, 0x20) >= 5) {
            M2C_FIELD(D_800AEDF0, s32 *, 0x20) = 4;
        }
    }
    D_802AC610.unk30 = 0;
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

    temp_s2 = func_802811F0(D_802A08EC, 0x140U, 0x6EU, 0.8f, 0.8f, 3U);
    func_8026C964();
    func_8026C660(0x1E9);
    var_s0 = 0xF0;
loop_1:
    if (!(D_802AC5D0 & 0x10)) {
#if VERSION_JP
        func_80280EB0(temp_s2, 0x49, var_s0 & 0xFFFF);
#else
        func_80280EB0(temp_s2, func_8023B2AC(D_802A08EC, 0.8f), var_s0 & 0xFFFF);
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
    var_v0 = ((s32 *) &D_802AC660);
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
    if (D_802AC660.unk0 == 0) {
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

static void func_80242994() {
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
        if (((D_802AC660.unk0 == 0) && (var_s2 != 1)) || ((D_802AC660.unk0 == 1) && (M2C_FIELD(&D_802AC760, s32 *, 0) == 0) && (M2C_FIELD(&D_802AC760, s32 *, 4) == 0))) {
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
        } else if (D_802AC660.unk0 == 0) {
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
    v = D_802AC610.unk30;
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
    v = D_802AC610.unk1C;
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
                if (count == D_802A076C && D_802AC610.unk28 < D_802AC610.unk30) {
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

    if (D_802AC660.unk28 < 6) {
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
                    if (i >= 3 || D_802AC660.unk2C > 0) {
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

    if (D_802AC660.unk28 < 6) {
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
                if (count >= D_802A08D8 + 3 || D_802AC660.unk2C > 0) {
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
    f32 t[3];
    f32 x;
    f32 y;
    f32 z;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 speed;

    func_802350F8(1);
    func_80234F6C(1);
    func_802348B4(&x, &y, &z);
    speed = 8.0f;
    while (TRUE) {
        func_80250338(func_80243DDC(), t);
        if (t[1] < -1000.0f) {
            break;
        }
        dx = (x < t[0]) ? -(x - t[0]) : (x - t[0]);
        dy = (y < t[1]) ? -(y - t[1]) : (y - t[1]);
        dz = (z < t[2]) ? -(z - t[2]) : (z - t[2]);
        if (!(dx > 100.0f) && !(dy > 100.0f) && !(dz > 100.0f)) {
            speed *= 0.9f;
            if (speed < 1.0f) {
                speed = 1.0f;
            }
        }
        if (dx > 1.0f) {
            if (x < t[0]) {
                x += speed;
            } else {
                x -= speed;
            }
        }
        if (dy > 1.0f) {
            if (y < t[1]) {
                y += speed;
            } else {
                y -= speed;
            }
        }
        if (dz > 1.0f) {
            if (z < t[2]) {
                z += speed;
            } else {
                z -= speed;
            }
        }
        func_802346C8(x, y + 50.0f, z);
        func_80239094();
    }
    D_802AC7F0 = 0;
    func_80239430();
}

void func_8023FD08() {
    struct {
        s32 n;
        s32 h[3];
    } t;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 (*v)[4];
    u8 *obj;
    s32 msg;
    void *model;
    u8 buf[16];
    UnkStruct_8023FD08 *o;
    f32 y4;
    f32 y3;
    f32 y2;
    f32 y1;
    f32 dx;
    UnkStruct_8023FD08 **p;
    s32 *q;

    D_802AC5D0 |= 0x90;
    func_80270770(0, 1);
    func_802268F4(0xB);
    func_8026C8E8();
    while (func_8023AB90() == 0) {
        func_80239094();
    }
    if (D_802AC5D0 & 2) {
        func_80239430();
    }
    D_802AC5E8 = D_802AC610.unk4;
    D_802AC5EC = D_802AC610.unk8;
    D_802AC5F0 = 0;
    func_8027F79C();
    func_80246D74(0);
    func_80245280(1);
    func_80247C50(0);
    func_802313DC(func_802443F4(0), 0x40000);
    n = 0;
    for (i = 0; i < 3; i++) {
        if (func_8028A36C((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + i + 0x2C) != 0) {
            n++;
        }
    }
    if (D_802AC5D0 & 0x28) {
        D_802AC80C = D_802AC610.unk2C;
        for (i = 0; i < ((D_802AC610.unk28 >= D_802AC610.unk30) ? 1 : 0) + D_802AC80C; i++) {
            func_8028A3D0((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + i + 0x2C);
        }
    } else {
        D_802AC80C = n - D_802AC610.unk20;
        if (D_802AC610.unk28 >= D_802AC610.unk30) {
            func_8028A3D0((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + 0x30);
        }
    }
    *func_8028A060(1) = D_802AC610.unk38;
    *func_8028A060(5) = D_802AC610.unk18;
    *func_8028A060(5) = D_802AC610.unk18;
    v = (s32 (*)[4]) func_8028A060(0x15);
    if ((D_802AC75C == 0) || (D_802AC610.unk30 < v[D_802AC5E8][D_802AC5EC])) {
        v[D_802AC5E8][D_802AC5EC] = D_802AC610.unk30;
    }
    D_802AC610.unk0 |= 8;
    func_80277484();
    func_8023903C(0x28);
    if (D_802AC5D0 & 0x28) {
        func_8026C93C(0x2D);
    } else {
        func_8026C93C(0x15);
    }
    func_80238DFC(0xD0, 0xF0, 0U);
    obj = func_802443F4(0);
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
    D_802AC610.unk0 &= ~8;
    func_802313DC(obj, 0x08000000);
    func_80231408(obj, 0x04000000);
    M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), s32 *, 0xC) &= ~0x4000;
    func_80229E38(M2C_FIELD(obj, void **, 0x40), 0x16, 0);
    func_80229E38(M2C_FIELD(obj, void **, 0x40), -1, 1);
    func_8022979C((s32) M2C_FIELD(obj, void **, 0x40), 4, 0xE);
    func_8022979C((s32) M2C_FIELD(obj, void **, 0x40), 5, 0xF);
    while (!(M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), s32 *, 0xC) & 0x40)) {
        func_80239094();
    }
    func_8023B318(D_802A0A68, 1);
    func_8023903C(0x5A);
    for (i = 0; i < 16; i++) {
        if (((s32 *) v)[i] == 0) {
            break;
        }
    }
    if ((i == 16) && (func_80295330(0) == 0)) {
        func_80294CE8(0);
        func_80295384();
    }
    i = 0;
    if ((D_802AC5E8 == 5) && (D_802AC5EC == 3) && (func_80295330(2) == 0)) {
        func_80294CE8(2);
        func_80295384();
    }
    for (j = 0; j < 0x78; j++) {
        if (func_8028A36C(j + 0x2C) != 0) {
            i++;
        }
    }
    if (i == 0x78) {
        if (func_80295330(1) == 0) {
            func_80294CE8(1);
            func_80295384();
        }
        func_8028A3D0(8);
        func_8028A3D0(0x13);
        func_8028A3D0(0x1E);
        func_8028A3D0(0x29);
        if ((D_802AC610.unk10 == 1) && (D_802AC610.unk38 < 0x2A31)) {
            func_8028A3D0(0xA);
            func_8028A3D0(0x15);
            func_8028A3D0(0x20);
            func_8028A3D0(0x2B);
        }
    }
    if ((D_802AC5E8 == 5) && (D_802AC5EC == 3) && (D_802AC610.unk38 < 0x2A31)) {
        func_8028A3D0(9);
        func_8028A3D0(0x14);
        func_8028A3D0(0x1F);
        func_8028A3D0(0x2A);
    }
    func_8023903C(0x1E);
    func_8023AB54(D_802A0A68, 1);
    func_8023903C(2);
    if (D_802AC5D0 & 0x28) {
        func_8023B318(D_802A0A7C, 3);
        y4 = 3.4f;
        y3 = -1.5f;
        dx = 3.82f;
        y2 = 110.0f;
        y1 = 140.0f;
    } else {
        func_8023B318(D_802A0A18, 4);
        y4 = 6.6f;
        y3 = -3.3f;
        dx = 5.725f;
        y2 = 120.0f;
        y1 = 180.0f;
    }
    func_8023B450(8, D_802AC610.unk28, buf);
    t.h[0] = func_802811F0(buf, 0xBE, (u32) y1, 0.6f, 0.8f, 3);
    t.n = 1;
    func_8023903C(0x1E);
    model = func_8026CE28(0x19);
    for (i = 0, p = D_802AC7F8; i < D_802AC80C; i++, p++) {
        func_8026C660(0x1E8);
        o = func_8022A6C4(model, 0x40);
        *p = o;
        o->unkC |= 0x100;
        o->unk34 = D_802AC5CC;
        o->unk10 = i * dx + 6.55f;
        o->unk14 = y4;
        o->unk18 = 930.0f;
        o->unk28 = 0.03f;
        o->unk2C = 0.03f;
        o->unk30 = 0.03f;
        if (i != 0) {
            o->unk48->unk4->unk4 = p[-1]->unk48->unk4->unk4;
        }
        func_8023903C(0x1E);
    }
    if (!(D_802AC5D0 & 0x28)) {
        func_8023B450(2, func_80287680(), buf);
        t.h[t.n] = func_802811F0(buf, 0xE2, 0x5A, 0.8f, 0.8f, 2);
        t.n++;
        if ((D_800BE824 == 0) && (func_8028A36C((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + 0x2F) != 0)) {
            p = &D_802AC7F8[i];
            func_8026C660(0x1E8);
            o = func_8022A6C4(model, 0x40);
            *p = o;
            o->unkC |= 0x100;
            o->unk34 = D_802AC5CC;
            o->unk10 = 18.0f;
            o->unk14 = 1.6f;
            o->unk18 = 930.0f;
            o->unk30 = 0.03f;
            o->unk2C = 0.03f;
            o->unk28 = 0.03f;
            if (i != 0) {
                o->unk48->unk4->unk4 = p[-1]->unk48->unk4->unk4;
            }
            i++;
            D_802AC80C++;
        }
    }
    q = &t.h[t.n];
    func_8023903C(0x1E);
    func_8023B450(8, D_802AC610.unk30, buf);
    *q = func_802811F0(buf, 0xA0, (u32) y2, 0.6f, 0.8f, 2);
    t.n++;
    if (D_802AC610.unk28 >= D_802AC610.unk30) {
        p = &D_802AC7F8[i];
        func_8026C660(0x1E8);
        o = func_8022A6C4(model, 0x40);
        *p = o;
        o->unkC |= 0x100;
        o->unk34 = D_802AC5CC;
        o->unk10 = 18.0f;
        o->unk14 = y3;
        o->unk18 = 930.0f;
        o->unk30 = 0.03f;
        o->unk2C = 0.03f;
        o->unk28 = 0.03f;
        if (p != D_802AC7F8) {
            o->unk48->unk4->unk4 = p[-1]->unk48->unk4->unk4;
        }
        D_802AC80C++;
    }
    func_8023903C(0x3C);
    msg = func_802811F0(STR_A, func_8023B2AC(STR_A, 0.6f), 0xD2, 0.6f, 0.6f, 2);
    func_8023903C(2);
    if (func_802947AC() != 0) {
        func_80280DB4(msg);
        func_8023903C(4);
        func_8026C660(0x18);
        msg = func_802811F0(STR_B, func_8023B2AC(STR_B, 0.6f), 0xD2, 0.6f, 0.6f, 0);
        func_8023903C(0xB4);
    }
    func_8023903C(0x3C);
    if ((D_802AC5E8 == 4) && (D_802AC5EC == 3) && (func_8028A36C(0xA4) == 0)) {
        func_8026CB2C();
    }
    func_80280DB4(msg);
    func_8023903C(0x3C);
    if (D_802AC5D0 & 0x28) {
        func_8023AB54(D_802A0A7C, 3);
    } else {
        func_8023AB54(D_802A0A18, 4);
    }
    for (i = 0; i < D_802AC80C; i++) {
        func_8022A1E8(D_802AC7F8[i]);
    }
    func_8026CCBC(0x19);
    for (i = 0; i < t.n; i++) {
        func_80280DB4(t.h[i]);
    }
    func_8023903C(2);
    for (i = 0; i < 16; i++) {
        if (((s32 *) v)[i] == 0) {
            break;
        }
    }
    j = 0;
    for (k = 0; k < 0x78; k++) {
        if (func_8028A36C(k + 0x2C) != 0) {
            j++;
        }
    }
    if (D_802AC75C == 0) {
        if (++D_802AC5EC >= 4) {
            D_802AC5EC = 0;
            if ((++D_802AC5E8 == 4) && (i != 16)) {
                D_802AC5E8 = 0;
            }
        }
    }
    D_802AC610.unk4 = D_802AC5E8;
    D_802AC610.unk8 = D_802AC5EC;
    func_8026C894();
    if (D_802AC7EC != 0) {
        func_80238EA8(D_802AC7EC);
    }
    if (D_802AC7F0 != 0) {
        func_80238EA8(D_802AC7F0);
    }
    if (D_802AC75C == 0) {
        if (D_802AC5E8 == 6) {
            func_8023AE6C(0x1C, 0x10, 0);
        } else if ((D_802AC5E8 == 5) && (D_802AC5EC == 0) && (j < 100)) {
            func_8023AE6C(0x1C, 0x11, 0);
        } else if ((D_802AC5E8 == 5) && (D_802AC5EC == 0) && (j == 100) && (func_8028A36C(0xA4) == 0)) {
            func_8023AE6C(0x21, 0x14, 0);
        } else if (D_802AC5EC == 0) {
            func_8023AE6C(0x21, 0x12, 0);
        } else {
            func_8023AE6C(0x21, 0x11, 0);
        }
    } else if ((D_802AC5E8 == 5) && (D_802AC5EC == 3)) {
        func_8023AE6C(0x1C, 0x10, 0);
    } else if ((D_802AC5E8 == 4) && (D_802AC5EC == 3) && (j < 100)) {
        func_8023AE6C(0x1C, 0x11, 0);
    } else if ((D_802AC5E8 == 4) && (D_802AC5EC == 3) && (j == 100) && (func_8028A36C(0xA4) == 0)) {
        D_802AC5E8 = 5;
        D_802AC610.unk4 = 5;
        D_802AC5EC = 0;
        D_802AC610.unk8 = 0;
        func_8023AE6C(0x21, 0x14, 0);
    } else {
        func_8023AE6C(0x21, 0x11, 0);
    }
    func_80239430();
}

void func_8023FC80(s32 arg0, u8 **arg1) {
    Gfx *gfx;

    gfx = *(Gfx **) arg1;
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0x80);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFDF6FB);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_1000000);
    gDPSetFillColor(gfx++, 0x10001);
    gDPFillRectangle(gfx++, 0, 0, 319, 239);
    *(Gfx **) arg1 = gfx;
}

s32 func_8023FC00(u8 arg0, u16 arg1) {
    s32 temp_v0;

    temp_v0 = arg1;
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
        return 1;
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
    var_v0 = (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) <= func_8026E8B8()) ? 1 : 0;
    if (var_v0 != 0) {
        func_8027F820(temp_v0);
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
    func_802909FC(temp_v0, func_80245150);
    temp_v1 = M2C_FIELD(temp_v0, void **, 0x40);
    M2C_FIELD(temp_v0, f32 *, 0x58) = (f32) M2C_FIELD(temp_v1, f32 *, 0x10);
    M2C_FIELD(temp_v0, f32 *, 0x5C) = (f32) M2C_FIELD(temp_v1, f32 *, 0x14);
    M2C_FIELD(temp_v0, f32 *, 0x60) = (f32) M2C_FIELD(temp_v1, f32 *, 0x18);
    func_80239094();
    goto loop_1;
}

void func_8023F26C() {
    s32 h;
    s32 k;
    s32 id;
    s32 pad1;
    u32 mode;
    s32 pad2;
    void *model;
    s32 pad3[3];
    s32 i;
    s32 task;
    u8 *obj;
    u8 *pl;
    s32 x;
    s32 y;

    D_802A0B94 = 1;
    id = *(s32 *) func_802391F0();
    func_80247C50(id);
    if ((D_802AC5D0 & 4) || ((D_802AC5D0 & 8) && (id != 0))) {
        mode = (&D_802AC858)[id];
        obj = func_802443F4(id);
        if ((D_802AC5D0 & 4) && (D_802AC660.unk0 == 0) && (func_80243EF0(id) == 0)) {
            D_802AC758--;
        }
        if ((D_802AC5D0 & 8) && (D_802AC758 == 1)) {
            func_80245208(0, 1);
        }
    } else {
        mode = D_802AC858;
        obj = func_802443F4(0);
        id = 0;
    }
    func_802313DC(obj, 0x7FFFF);
    ((u32 *) D_802AC868)[id] = mode;
    switch (mode) {
    case 3:
        if (!(D_802AC5D0 & 8) || (id == 0)) {
            func_8026C660(0x1E);
        }
        func_8027F820(obj);
        func_8023903C(0x5A);
        break;
    case 2:
        func_8024364C(obj);
        func_8023903C(0x5A);
        break;
    case 1:
        if ((D_802AC5D0 & 8) && (id != 0)) {
            func_8023EE40((s32) obj);
        } else {
            func_8023EF38(obj);
        }
        break;
    case 0:
        if ((D_802AC5D0 & 8) && (id != 0)) {
            func_8023EE40((s32) obj);
        } else {
            func_8023ECF4(obj);
        }
        break;
    case 5:
        task = func_80238A10(func_8023FAA0, (s32) obj, 0, 0, 0x130);
        func_802362B8(0x7F);
        D_802A0038 = 0;
        if (D_802A01BC != 0) {
            D_802AC7EC = func_80238A10(func_80241180, 0, 0, 0, 0x130);
            D_802AC7F0 = func_80238A10(func_80240F34, 0, 0, 0, 0x130);
        } else {
            D_802AC7F0 = 0;
            D_802AC7EC = 0;
        }
        func_8022979C(M2C_FIELD(obj, s32 *, 0x40), 4, 0xC);
        func_8022979C(M2C_FIELD(obj, s32 *, 0x40), 5, 0xD);
        for (i = 0; i < 20; i++) {
            f32 t = (f32) i / 20.0f;

            M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x30) = 1.0f - t;
            M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x28) = 1.0f - t;
            M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x2C) = t + 1.0f;
            func_80239094();
        }
        if (D_802AC7EC != 0) {
            func_80238EA8(D_802AC7EC);
        }
        func_80238EA8(task);
        break;
    }
    if (D_802AC5D0 & 4) {
        func_802313DC(obj, 0x0507FFFF);
        if (D_802AC660.unk0 == 0) {
            func_802313DC(obj, 0x01000000);
            func_8023903C(2);
            if ((D_802AC660.unk4[id] == 1) && (D_802AC660.unk40[id] == 1)) {
                func_80227EE0(D_802AC660.unkE8[id]);
            }
            func_8025C590(id);
            if ((D_802AC660.unk3C != 0) && (D_802AC660.unk2C > 0) && !(D_802AC5D0 & 0x10)) {
                func_80243E90(id);
                obj = func_8023EB28(id);
                model = func_80231274(-1, 0x01000000, 0xD0, NULL);
                h = func_8028A81C(0x15, 0.0f, 20.0f, 0.0f, (s32) model);
                func_80245208(id, 1);
                pl = D_800AEDF0 + id * 0xC8;
                for (k = 0; k < 60; k++) {
                    if (M2C_FIELD(pl, s32 *, 0x24) == 3) {
                        break;
                    }
                    M2C_FIELD(M2C_FIELD(model, u8 **, 0x40), f32 *, 0x10) = M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x10);
                    M2C_FIELD(M2C_FIELD(model, u8 **, 0x40), f32 *, 0x14) = M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x14);
                    M2C_FIELD(M2C_FIELD(model, u8 **, 0x40), f32 *, 0x18) = M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x18);
                    func_80239094();
                }
                if (M2C_FIELD(pl, s32 *, 0x24) != 3) {
                    func_80245208(id, 0);
                }
                func_8028A4E0(h);
                func_8022FC90(model);
            }
        } else {
            func_802313DC(obj, 0x01000000);
            func_8023903C(2);
            if ((D_802AC660.unk4[id] == 1) && (D_802AC660.unk40[id] == 1)) {
                func_80227EE0(D_802AC660.unkE8[id]);
            }
            func_8025C590(id);
            if (((D_802AC660.unk2C != 0) || (D_802AC660.unk30 != 0)) && !(D_802AC5D0 & 0x10)) {
                func_8023EB28(id);
            }
        }
    } else if (id != 0) {
        D_802AC758--;
        func_8024585C(id);
        func_80245280(1);
        func_8024585C(0);
        if ((D_802AC758 == 0) && (D_800AEE14 != 3)) {
            func_80251534(0);
            func_802313DC(func_802443F4(0), 0x40000);
            func_80247C50(0);
            func_8023E8AC();
        }
    } else if (D_802AC610.unk14 == 0) {
        func_8023E1D8();
    } else {
        if (D_802AC610.unk40 == 0) {
            func_80277DF4(2);
        }
        D_802AC5F0 = 0;
        D_802AC7CC = 0x32;
        func_8026C8E8();
        func_8026C894();
        func_802510F0();
        x = D_802AC5DC;
        y = D_802AC5E0;
        if (!(D_802AC5D0 & 1) && (D_802A01B4 == 0)) {
            D_802AC5D8 = y;
            D_802AC5D4 = x;
            D_802AC5DC = x;
            D_802AC5E0 = y;
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

    temp_s4 = &(((s32 *) &D_802AC660))[arg0];
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
        var_s1 = ((s32 *) &D_802AC660) + (arg0 * 0x10);
        var_s0_2 = 0;
        do {
            func_8023A734(M2C_FIELD(temp_s4, s32 *, 0xE8), var_s0_2, M2C_FIELD(var_s1, s32 *, 0x50));
            var_s0_2 += 1;
            var_s1 += 4;
        } while (var_s0_2 != 4);
    }
    var_a0 = var_s3;
    if (D_802AC660.unk0 == 1) {
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

static void func_8023E8FC(f32 *pos) {
    s32 padA[9];
    f32 x;
    f32 y;
    f32 z;
    s32 ix;
    s32 iz;
    s32 a;
    s32 b;
    struct {
        s32 unk0[4];
        f32 unk10[3];
    } s;
    s32 padB[5];

    while (TRUE) {
        x = ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][0] +
            (s32) ((((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0 + 10][0] - ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][0]) * (f32) func_8025E63C());
        y = ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][1];
        z = ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][2] +
            (s32) ((((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0 + 10][2] - ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][2]) * (f32) func_8025E63C());
        ix = x;
        iz = z;
        a = func_8026D7D8(ix, (s32) y, iz);
        if ((D_802AC660.unkA0 == 0) || (D_802AC660.unkA0 == 6) || (D_802AC660.unkA0 == 7) ||
            (D_802AC660.unkA0 == 9)) {
            b = func_8026D7D8(ix, 0, iz);
        } else {
            b = 0;
        }
        func_8026E338(x, y, z, pos, 0);
        s.unk10[0] = pos[0];
        s.unk10[1] = pos[1];
        s.unk10[2] = pos[2];
        if (a & 0x60) {
            continue;
        }
        if (func_8026E938(&s) == 20000.0f) {
            continue;
        }
        if (((a & 0xF) != 0) && ((a & 0xF) != 1)) {
            continue;
        }
        if (b & 0x60) {
            continue;
        }
        if (((b & 0xF) != 0) && ((b & 0xF) != 1)) {
            continue;
        }
        break;
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
    TextItem *var_v1;
    TextItem *var_v1_2;
    TextItem *var_v1_3;
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
    func_8023B318(D_802A0AB8, 1);
    if (D_802AC628 == 0) {
        func_8023903C(0xB4);
        var_v1 = D_802A0AB8;
        do {
            sp48 = var_v1;
            func_80280DB4(var_v1->handle);
            var_v1++;
        } while (var_v1 < &D_802A0AB8[1]);
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
        var_v1_2 = D_802A0AB8;
        do {
            sp48 = var_v1_2;
            func_80280DB4(var_v1_2->handle);
            var_v1_2++;
        } while (var_v1_2 < &D_802A0AB8[1]);
        func_8023903C(2);
        func_8023B450(2, D_802AC628, &spA4);
        func_8023B318(D_802A0ACC, 4);
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
            temp_t0 = D_802AC610.unk18 - 1;
            D_802AC610.unk18 = temp_t0;
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
        var_v1_3 = D_802A0ACC;
        do {
            sp48 = var_v1_3;
            func_80280DB4(var_v1_3->handle);
            var_v1_3++;
        } while (var_v1_3 < &D_802A0ACC[4]);
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
    D_802AC610.unk0 = 0;
    D_802AC610.unk4 = 0;
    D_802AC610.unk8 = 0;
    D_802AC610.unkC = 0;
    D_802AC610.unk38 = (s32) *func_8028A060(1);
    temp_v1 = *func_8028A060(3);
    if (temp_v1 == 0) {
        D_802AC610.unk10 = 0;
    } else if (temp_v1 == 1) {
        D_802AC610.unk10 = 1;
    }
    D_802AC610.unk14 = 2;
    D_802AC610.unk18 = 3;
    D_802AC610.unk1C = 0;
    D_802AC610.unk2C = 0;
    func_8028A0B4();
    if (D_802AC610.unk40 != 0) {
        M2C_FIELD(D_800AEDF0, s32 *, 0x18) |= 0x200;
        M2C_FIELD(D_800AEDF0, s32 *, 0x18) |= 3;
        func_80278E84(0, 8);
        func_80277AF8(0, 8);
    } else {
        func_80277E1C();
    }
    D_802AC610.unk0 |= 1;
    D_802AC660.unk0 = 0;
    M2C_FIELD(D_800AEDF0, s32 *, 0x14) = 1;
    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        D_802AC660.unk4[var_s0] = 1;
        D_802AC660.unk40[var_s0] = 0;
        D_802AC660.unk90[var_s0] = 0;
        D_802AC660.unkA4[var_s0] = 0;
        D_802AC660.unk14[var_s0] = 1;
        for (var_a0_2 = 0; var_a0_2 < 4; var_a0_2++) {
            D_802AC660.unk50[var_s0][var_a0_2] = 0;
        }
    }
    D_802AC660.unk24 = 3;
    D_802AC660.unk28 = 2;
    D_802AC660.unk2C = 2;
    D_802AC660.unk30 = 0;
    D_802AC660.unk34 = 0x3C;
    D_802AC660.unk38 = 1;
    D_802AC660.unk3C = 1;
    D_802AC660.unkA0 = 0;
    D_802AC5D4 = 0x14;
    D_802AC5D8 = 0x10;
    func_802268F4(2);
    func_802268F4(0x10);
    func_802268F4(4);
    func_802268F4(5);
    D_802A01B8 = 0;
loop_11:
    if (D_802AC5D0 & 1) {
        D_802A01B8 = 0;
        func_802268F4(0xC);
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
        func_802268F4(1);
        func_8027F79C();
        func_8023D8A0();
        func_80239094();
        func_8026BF28(0x7F);
        func_8026BF90(0x7F);
        func_8023D0F8();
        func_8022691C(D_802AC5D4);
        func_802268F4(2);
        func_802268F4(D_802AC5D8);
        func_802268F4(4);
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
        func_802268F4(5);
        D_802AC5D0 &= ~1;
        func_8023C374();
        func_8023ADD4(0);
        if ((D_802AC5D4 >= 0x28) && !(D_802AC610.unk0 & 6)) {
            D_802A01B8 = 1;
        }
        func_8023A640();
    } else if (!(D_802AC5D0 & 0x10) && !(D_802AC5D0 & 2)) {
        if (!(D_802AC5D0 & 0x40) && !(D_802AC5D0 & 0x80)) {
            if ((D_802AC5D0 & 4) && (D_802AC660.unk28 < 6)) {
                temp_t7 = D_802AC660.unk34 - 1;
                D_802AC660.unk34 = temp_t7;
                if (temp_t7 <= 0) {
                    D_802AC660.unk34 = 0x3C;
                    temp_v0 = D_802AC660.unk30 - 1;
                    D_802AC660.unk30 = temp_v0;
                    if (temp_v0 < 0) {
                        temp_t6_2 = D_802AC660.unk2C - 1;
                        D_802AC660.unk30 = 0x3B;
                        D_802AC660.unk2C = temp_t6_2;
                        if (temp_t6_2 == 0) {
                            func_80238A10(func_802434F8, 0, 0, 0, 0x130);
                        }
                        goto block_48;
                    }
                    var_s0 = 0;
                    if (temp_v0 == 0) {
                        var_s0 = 0;
                        if (D_802AC660.unk2C == 0) {
                            func_8023C170();
                            goto block_48;
                        }
                    }
                } else {
                    goto block_48;
                }
            } else {
                D_802AC610.unk34 = (f32) (D_802AC610.unk34 + 1.6666666f);
                if (D_802AC610.unk34 >= 1.0f) {
                    temp_ft0 = (s32) D_802AC610.unk34;
                    D_802AC610.unk30 = (s32) (D_802AC610.unk30 + temp_ft0);
                    D_802AC610.unk34 = (f32) (D_802AC610.unk34 - (f32) temp_ft0);
                }
                D_802AC5F4 += 1.6666666f;
                if (D_802AC5F4 >= 100.0f) {
                    D_802AC610.unk38 = (s32) (D_802AC610.unk38 + 1);
                    D_802AC5F4 -= (f32) (s32) D_802AC5F4;
                }
                if (D_802AC610.unk30 >= 0x05F5E100) {
                    D_802AC610.unk30 = 0x05F5E0FF;
                }
                if (D_802AC610.unk38 >= 0x57E40) {
                    D_802AC610.unk38 = 0x57E3F;
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
                func_802268F4((&D_802AC7A0)[D_802AC608]);
                (&D_802AC7A0)[D_802AC608] = -1;
                var_t9 = D_802AC608 + 1;
            }
            D_802AC608 = var_t9;
            if (var_t9 >= 0xA) {
                D_802AC608 = 0;
            }
            var_s0 += 1;
        } while (var_s0 != 0xA);
        func_802268F4(3);
        func_8023BBCC();
    }
    func_8023903C(1);
    goto loop_11;
}

void func_8023DA04(s32 arg0) {
    s32 temp_v1;

    if (0) {
        func_8023D9FC();
        func_8023D8A0();
    }
    D_802AC5E8 = 0;
    D_802AC5EC = 0;
    D_802AC5F0 = 0;
    D_802AC610.unk0 = 0;
    D_802AC610.unk4 = 0;
    D_802AC610.unk8 = 0;
    D_802AC610.unkC = 0;
    D_802AC610.unk38 = (s32) *func_8028A060(1);
    temp_v1 = *func_8028A060(3);
    switch (temp_v1) {
    case 0:
        D_802AC610.unk10 = 0;
        break;
    case 1:
        D_802AC610.unk10 = 1;
        break;
    }
    D_802AC610.unk14 = 2;
    D_802AC610.unk18 = 3;
    D_802AC610.unk1C = 0;
    D_802AC610.unk2C = 0;
    func_8028A0B4();
    if (D_802AC610.unk40 != 0) {
        M2C_FIELD(D_800AEDF0, s32 *, 0x18) |= 0x200;
        M2C_FIELD(D_800AEDF0, s32 *, 0x18) |= 3;
        func_80278E84(0, 8);
        func_80277AF8(0, 8);
    } else {
        func_80277E1C();
    }
    M2C_FIELD(D_800AEDF0, s32 *, 0x14) = 1;
}

static void func_8023D9FC(void) {
}

static void func_8023D8A0() {
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
    if (0) {
        func_8023D840();
        func_8023D0F8();
    }
}

static void func_8023D840(void) {
}

static s32 func_8023D0F8() {
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

    if (0) {
        func_8023D0F0();
    }
    if ((D_802AC5D0 & 2) && (D_802AC610.unk14 != 0)) {
        D_802AC610.unk14 = (s32) (D_802AC610.unk14 - 1);
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
            D_802AC610.unkC = (s32) (D_802AC5D4 - *(D_802A04C8 + ((D_802AC5E8 * 0x10) + (var_a0_2 * 4))));
        } else {
            D_802AC610.unkC = 0;
        }
        if ((D_802AC610.unk4 == 1) && (D_802AC610.unk8 == 2) && (D_802AC5D4 == 0x3B)) {
            D_802AC5EC = 2;
            D_802AC610.unkC = 2;
            var_a0_2 = 2;
        }
        D_802AC610.unk4 = D_802AC5E8;
        D_802AC610.unk8 = var_a0_2;
        if ((D_802AC5F0 == 0) && (var_s0 == 0)) {
            var_s1 = &D_800BE818;
            var_s0_2 = 0;
            D_802AC610.unk20 = 0;
            do {
                temp_v0 = func_8028A36C((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + var_s0_2 + 0x2C);
                *var_s1 = temp_v0;
                if (temp_v0 != 0) {
                    if (var_s0_2 < 3) {
                        D_802AC610.unk20 = (s32) (D_802AC610.unk20 + 1);
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
            D_802AC610.unk34 = 0.0f;
            D_802AC610.unk38 = (s32) *func_8028A060(1);
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
            D_802AC610.unk30 = 0;
            D_802AC610.unk2C = 0;
        }
        var_t6 = D_802AC5D0 & 0x20;
        if (!(D_802AC610.unk0 & 6)) {
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
            D_802AC610.unk10 = 0;
            func_8023CECC();
            D_802AC610.unk4 = 9;
            D_802AC610.unk8 = 0;
            D_802AC610.unkC = (s32) (D_802AC5D4 - 0x90);
            D_802AC5D0 |= 4;
            var_a0_3 = ((s32 *) &D_802AC660);
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

static void func_8023D0F0(void) {
}

static void func_8023CECC() {
    Rect54E40 *r;
    s32 n;
    s32 i;
    s32 x;

    D_802A0758 = func_8026CE28(0x130);
    D_802A075C = func_8026CE28(0x131);
    if (D_802AC660.unk0 == 0) {
        D_802A0760 = func_8022A328(func_80241BB0, 0x3F, 1, 0, 0);
        func_8023CD1C();
        func_8023CC54(4);
    } else {
        func_8023CD1C();
        func_8023CC54(2);
        for (n = 0, i = 0; i < 4; i++) {
            if ((D_802AC660.unk4[i] != 0) && (D_802AC660.unk90[i] == 0)) {
                n++;
            }
        }
        r = (Rect54E40 *) D_802A0888;
        i = 3;
        x = 0x84;
        do {
            r->xl = x << 2;
            r->xh = (x + 0x10) << 2;
            x += 0x12;
            if ((n + 2) == i) {
                D_802A0838[3] = x + 4;
                x += 0x3A;
            }
            i++;
            r++;
        } while (i < 7);
        ((Rect54E40 *) D_802A084C)[2].xl = (n * 0x12 + 0xAC) << 2;
        ((Rect54E40 *) D_802A084C)[2].xh = (n * 0x12 + 0xBC) << 2;
        x = n + 3;
        n = 3;
        for (i = 0; i < 4; i++) {
            if (D_802AC660.unk4[i] != 0) {
                if (D_802AC660.unk90[i] == 0) {
                    ((Rect54E40 *) D_802A084C)[n++].idx = i * 2;
                } else {
                    ((Rect54E40 *) D_802A084C)[x++].idx = i * 2;
                }
            }
        }
        D_802A0838[4] = x * 0x12 + 0x8C;
        D_802AC7C8 = x;
        D_802A0760 = func_8022A328(func_80241590, 0x3F, 1, 0, 0);
    }
    M2C_FIELD(D_802A0760, s32 *, 0xC) |= 0x210;
}

void func_8023CD1C() {
    s32 n;
    s32 i;
    s32 v;
    s32 d;
    s32 q;
    s32 t;

    n = 0;
    if (D_802AC660.unk28 < 6) {
        v = D_802AC660.unk2C;
        d = 1;
        for (i = 0; i < 1; i++) {
            q = v / d;
            D_802AC770[n++] = q * 2;
            t = q * d;
            if (v >= t) {
                v -= t;
            }
            d /= 10;
        }
        D_802AC770[n++] = 0x14;
        v = D_802AC660.unk30;
        d = 10;
        for (i = 0; i < 2; i++) {
            q = v / d;
            D_802AC770[n++] = q * 2;
            t = q * d;
            if (v >= t) {
                v -= t;
            }
            d /= 10;
        }
    } else {
        D_802AC770[n++] = 0x16;
        D_802AC770[n++] = 0x14;
        D_802AC770[n++] = 0x16;
        D_802AC770[n++] = 0x16;
    }
}

void func_8023CC54(s32 arg0) {
    s32 i;
    s32 j;
    s32 v;
    s32 div;
    s32 d;
    s32 k;
    s32 t;

    if (0) {
        func_8023CC4C();
        func_8023CA94();
    }
    k = 0;
    for (i = 0; i < arg0; i++) {
        v = D_802AC660.unkA4[i];
        div = 1;
        for (j = 0; j < 1; j++) {
            d = v / div;
            ((s32 *) D_802AC780)[k++] = d * 2;
            t = d * div;
            if (v >= t) {
                v -= t;
            }
            div /= 10;
        }
    }
}

static void func_8023CC4C(void) {
}

static void func_8023CA94() {
    u8 *var_s4;
    s32 *var_s1;
    s32 *var_s2;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s5;

    if (D_802AC5D0 & 4) {
        D_802AC660.unk30 = 0;
        D_802AC660.unk34 = 0x3C;
        D_802AC660.unk2C = (s32) D_802AC660.unk28;
        func_80277E1C();
        var_s2 = ((s32 *) &D_802AC660);
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
                var_s1 = (var_s5 * 0x10) + 0x50 + ((s32 *) &D_802AC660);
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
        if (D_802AC660.unk0 == 1) {
            D_802AC610.unk10 = 0;
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

    if (0) {
        func_8023C170();
    }
    if ((D_802AC5F0 != 0) || (D_802AC5D4 < 0x28) || (D_802AC610.unk0 & 6)) {
        D_802AC5D0 &= ~0x10;
        return;
    }
    if (D_802AC5D0 & 4) {
        func_8026C93C(0x1B);
        func_8026C660(0x1E4);
        sp68 = func_802811F0(D_802A01D8, X_01D8, 0x6EU, 0.8f, 0.8f, 0U);
        func_8023903C(0x2B);
        sp64 = func_802811F0(D_802A01E0, X_01E0, 0x6EU, 0.8f, 0.8f, 4U);
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
    D_802A01C4[6] = (s8) (D_802AC5EC + 0x11);
    sp6C = func_802811F0(D_802A01C4, func_8023B2AC(D_802A01C4, 0.8f), 0x3CU, 0.8f, 0.8f, 0U);
    sp68 = func_802811F0(D_802A01D0, func_8023B2AC(D_802A01D0, 0.8f), 0x5AU, 0.8f, 0.8f, 0U);
    temp_a0 = D_802A08F8[D_802AC5E8][D_802AC5EC];
    sp60 = func_802811F0(temp_a0, func_8023B2AC(temp_a0, 0.6f), 0x78U, 0.6f, 0.8f, 0U);
    func_8023AF5C(163.0f, 150.0f);
    if (D_802AC610.unk10 == 0) {
        D_802AC610.unk28 = D_802A0958[D_802AC5E8][D_802AC5EC];
    } else {
        D_802AC610.unk28 = D_802A09B8[D_802AC5E8][D_802AC5EC];
    }
    func_8023B7C0(180.0f);
    func_8023903C(0xB4);
    func_80280DB4(sp6C);
    func_80280DB4(sp68);
    func_80280DB4(sp60);
    func_80280DB4(D_802AC7E4);
    func_80280DB4(D_802AC7E8);
    func_8023AAE4();
    D_802AC75C = func_8028A060(0x15)[D_802AC5E8 * 4 + D_802AC5EC];
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
        if ((D_802AC5E8 == 0) && (D_802AC5EC == 0) && (D_802AC75C == 0) && (D_802AC610.unk30 == 0) && (D_802AC610.unk10 == 0)) {
            func_80238A10(func_80241550, D_802AC5E8 + 3, 0, 0, 9);
        } else {
            func_8026C93C(D_802AC5E8 + 3);
        }
    }
    D_802AC5D0 = temp_v1 & ~0x90;
}

static void func_8023C170() {
    u8 *var_s1;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    u8 *temp_v0_2;

    if (D_802AC660.unk0 == 0) {
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
                *func_8028A060(1) = D_802AC610.unk38;
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

static void func_8023B8D0() {
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
        D_802A0B1C[0].str = D_802A08F8[D_802AC5E8][D_802AC5EC];
    } else {
        D_802A0B1C[0].str = D_802A0448;
    }
    if (D_802AC5D0 & 0x2C) {
        func_8023B318(D_802A0B1C, 1);
        temp_t8 = D_802AC5D0 & 4;
        var_v0 = temp_t8;
        if (temp_t8 == 0) {
            func_8023B7C0(154.0f);
            var_v0 = D_802AC5D0 & 4;
        }
    } else {
        func_8023B450(2, func_80287680(), sp30);
        D_802AC814 = func_802811F0(sp30, 0xDCU, 0x50U, 0.6f, 0.6f, 2U);
        var_s3 = (void *) D_802AC7F8;
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
            func_8023B318(D_802A0B1C, 3);
            func_802814D8(D_802A0B40, 0xFFE8U, 0U);
            var_v0 = D_802AC5D0 & 4;
        } else {
            func_8023B318(D_802A0B1C, 5);
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

    func_8023B450(8, D_802AC610.unk28, &sp24);
    var_s0 = (u32) arg0;
    temp_t7 = var_s0 & 0xFFFF;
    D_802AC7E4 = func_802811F0(&D_802A039C, 0x2DU, temp_t7 & 0xFFFF, 0.6f, 0.8f, 2U);
    D_802AC7E8 = func_802811F0(&sp24, 0xB4U, temp_t7 & 0xFFFF, 0.6f, 0.8f, 3U);
}

static void func_8023B450(s32 n, s32 value, u8 *buf) {
    s32 i;
    s32 div;
    s32 j;
    s32 d;
    s32 t;

    i = 0;
    div = 1;
    for (; i < n - 1; i++) {
        div *= 10;
    }
    j = 0;
    for (i = 0; i < n; i++) {
        d = value / div;
        buf[j++] = d + 0x10;
        t = d * div;
        if (value >= t) {
            value -= t;
        }
        div /= 10;
    }
    buf[j] = 0;
}

static void func_8023B318(TextItem *items, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        items[i].handle = func_802811F0(items[i].str, func_8023B2AC(items[i].str, items[i].scale), (u32) items[i].y, items[i].scale, items[i].scale, items[i].mode);
    }
}

static s32 func_8023B2AC(u8 *str, f32 scale) {
#if VERSION_JP
    s32 n;

    for (n = 0; str[n] != 0; n++) {
    }
    return (320.0f - (f32) (n * 24) * scale) / 2;
#else
    return (320.0f - (f32) func_80280C08(str) * scale) / 2;
#endif
}

static void func_8023AF5C(f32 x, f32 y) {
    u8 buf[4];
    s32 v;
    s32 d;
    s32 i;
    s32 q;
    s32 t;
    u8 *p;
    f32 w;
    f32 x0;
    f32 y0;
    f32 y1;

    v = D_802AC610.unk14;
    d = 10;
    p = buf;
    for (i = 0; i < 2; i++) {
        q = v / d;
        *p++ = q + 0x10;
        t = q * d;
        if (v >= t) {
            v -= t;
        }
        d /= 10;
    }
    *p = 0;
    if (D_800AEE04 >= 2) {
        w = 16.0f;
        D_802AC7E0 = func_8026CE28(0x34E);
        D_802AC7DC = func_8022A6C4(D_802AC7E0, 0x3F);
        x0 = x - 28.0f;
        M2C_FIELD(D_802AC7DC, f32 *, 0x10) = x0 - 28.0f + 16.0f;
        y0 = y + 1.0f;
        M2C_FIELD(D_802AC7DC, f32 *, 0x14) = y0;
        M2C_FIELD(D_802AC7DC, f32 *, 0x18) = x0 - 28.0f + w + 16.0f;
        y1 = y0 + 16.0f;
        M2C_FIELD(D_802AC7DC, f32 *, 0x1C) = y1;
    } else {
        w = 0.0f;
        y0 = y + 1.0f;
        x0 = x - 28.0f;
        D_802AC7E0 = NULL;
        y1 = y0 + 16.0f;
    }
    D_802AC7D0 = func_8026CE28(0x130);
    D_802AC7D4 = func_8022A6C4(D_802AC7D0, 0x3F);
    M2C_FIELD(D_802AC7D4, s32 *, 0xC) |= 0x10;
    M2C_FIELD(D_802AC7D4, f32 *, 0x10) = x0 + w;
    M2C_FIELD(D_802AC7D4, f32 *, 0x14) = y0;
    M2C_FIELD(D_802AC7D4, f32 *, 0x18) = x0 + 16.0f + w;
    M2C_FIELD(D_802AC7D4, f32 *, 0x1C) = y1;
    D_802AC7D8 = func_802811F0(buf, (x - 36.0f) + 24.0f + 8.0f + w, y, 0.6f, 0.8f, 2);
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
    if (0) {
        func_8023AC38();
    }
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

static void func_8023AC38() {
    s32 temp_t9;
    s32 var_t6;
    s32 var_v1;
    TextItem *var_s0;
    TextItem *var_s0_2;
    TextItem *var_s0_3;
    void **var_s0_4;

    if (D_802AC5D0 & 0x2C) {
        var_s0 = D_802A0B1C;
        do {
            func_80280DB4(var_s0->handle);
            var_s0++;
        } while (var_s0 < &D_802A0B1C[1]);
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
            var_s0_2 = D_802A0B1C;
            do {
                func_80280DB4(var_s0_2->handle);
                var_s0_2++;
            } while (var_s0_2 < &D_802A0B1C[3]);
        } else {
            var_s0_3 = D_802A0B1C;
            do {
                func_80280DB4(var_s0_3->handle);
                var_s0_3++;
            } while (var_s0_3 < &D_802A0B1C[5]);
        }
        var_s0_4 = (void *) D_802AC7F8;
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

static void func_8023AB4C(void) {
}

static s32 func_8023AB90(void) {
    s32 id;
    u8 *obj;

    if (0) {
        func_8023AB54(0, 0);
        func_8023AB4C();
    }
    id = func_80243DDC();
    obj = func_802443F4(id);
    if ((M2C_FIELD(D_800AEDF0 + id * 0xC8, s32 *, 0x24) == 3) || (M2C_FIELD(obj, f32 *, 0x68) != 0.0f) ||
        (M2C_FIELD(obj, f32 *, 0x6C) != 0.0f) || (func_80244BA4(id, 0x20) != 0)) {
        return 0;
    }
    return 1;
}

static void func_8023AB54(TextItem *items, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_80280DB4(items[i].handle);
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
            *func_8028A060(1) = D_802AC610.unk38;
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
    return ((s32 *) &D_802AC660);
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
    D_802AC610.unk3C = 0;
    D_802AC610.unk40 = 0;
    D_802AC610.unk44 = 0;
    D_802AC610.unk48 = 0;
    func_8023A640();
    func_802513E0();
}

void func_8023A640() {
    s32 i;

    for (i = 0; i < 10; i++) {
        (&D_802AC7A0)[i] = -1;
    }
    D_802AC608 = 0;
}
