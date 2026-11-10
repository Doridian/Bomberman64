/*
 * NON_MATCHING: main_code's 5E3F0, complete: 155 functions (us
 * 0x80243BF0-0x802513D8) around a table of five 0xC8-byte entries,
 * D_800AEDF0[5] (an object in unk28, flag words in unk10 and unk68), the
 * current entry in D_802AC894. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 1509, eu 1509, jp 1508
 *
 * A first draft: functions in the reverse of the ROM's order (IDO -O3
 * emits last to first); 0x80243BF0-0x802457D8 by hand, most of the rest
 * m2c's, with the fixes the -O3 build needs. The object is -O3: its
 * small getters and flag tests are inlined into every caller and still
 * emitted, and the inlined copies are what give the original its
 * registers:
 * - func_80243DDC (D_802AC894 through a variable, so in v1) in place of
 *   every read of D_802AC894: the wrappers that pass it (80243DEC,
 *   802443A0, 802450DC, 80245280, 8024557C, 80245F74, 8025068C) match
 *   only with the call;
 * - func_802443F4 (unk28 through a variable) for D_800AEDF0[i].unk28;
 * - func_80244BA4/func_80243EB4/func_802452AC/func_80243E18 for the
 *   `v = 0; if ((x & f) == f) v = 1;` tests of unk10, unk68 and D_802AC9E8
 *   (80244E04 goes from 64 differing words to 10 with them).
 * func_8024A0DC is called without its argument (80250DC8 leaves a0 as
 * it is), so it has no prototype here.
 * The entry's unk58-unk64, unk6C, unk88, unk8C, unkC0 and unkC4 are
 * floats. An empty `if (!X && !X) {}` on a memory load at the top of a
 * function (X = D_800AEDF0[arg0].unk10, D_802AC9E8 or D_802AC8D0[arg0])
 * only uses up ugen temporaries: it puts the t-registers of 8024ABA8,
 * 8024AF24 and others in step with the original's.
 * 8024E088 is in clean C (frame and shape the original's); jp's
 * differences there are `#if VERSION_JP` arms. 80246F00 is in clean C
 * too: one switch in the original's case order, the arg1 == 0 copy of
 * case 0x20 a loop over D_800AEDF0[i] (uopt unrolls it to absolute
 * addresses), func_80243EF0 inlined for case 8's test. Its call of
 * func_80246D74 passes the s16 index unextended, so func_80246D74 has
 * only a `()` prototype; it copies its argument into a local first
 * (`move s0,a0`, then `sll/sra` for func_80270770's s16).
 * Left: register and scheduling differences nearly everywhere else, and
 * the large m2c functions (8024891C, 8024D8C4, 802444B8,
 * 8024A0DC) are still m2c's shape. 802506B8's fill loop of the
 * ten 255-entry tables isn't unrolled in the original (this one is).
 * func_80244354 is inlined into its leaf callers (8024A6B4, 80247928)
 * here but not in the original.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
#define FLAG_SET(x, f) ((((x) & (f)) == (f)) ? 1 : 0)
#define FLAG_CLEAR(x, f) (!((x) & (f)) ? 1 : 0)

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
} UnkModel;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkModel *unk40;
    /* 0x44 */ u8 unk44[0x4C - 0x44];
    /* 0x4C */ f32 unk4C[3];
    /* 0x58 */ u8 unk58[0x6C - 0x58];
    /* 0x6C */ f32 unk6C;
} UnkObj;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ UnkObj *unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s32 unkB0;
    /* 0xB4 */ s32 unkB4;
    /* 0xB8 */ s32 unkB8;
    /* 0xBC */ s32 unkBC;
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
} UnkStruct_800AEDF0; /* size 0xC8 */

extern UnkStruct_800AEDF0 D_800AEDF0[5];

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
} Sub88b;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ Sub88b *unk4;
} Sub88a;

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 unk24[0x48 - 0x24];
    /* 0x48 */ Sub88a *unk48;
} Mdl88;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[8];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ UnkObj *unk20;
    /* 0x24 */ u8 unk24[0x40 - 0x24];
    /* 0x40 */ Mdl88 *unk40;
    /* 0x44 */ void *unk44;
    /* 0x48 */ u8 unk48[4];
    /* 0x4C */ f32 unk4C[3];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ u8 unk64[4];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} Obj88;

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10[0x1A - 0x10];
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 unk1C[0x24 - 0x1C];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ Obj88 *unk2C;
    /* 0x30 */ u8 unk30[0x40 - 0x30];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44[4];
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 unk54[0x60 - 0x54];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ u8 unk68[0xA4 - 0x68];
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ u8 unkAC[0xC8 - 0xAC];
} E88;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} Res58;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
} PadState;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
} Ctl58;

#define WRAP360(x) (((x) >= 360.0f) ? (x) - 360.0f : (((x) < 0.0f) ? (x) + 360.0f : (x)))

typedef struct {
    s32 v[8];
} Tbl8i_5E3F0;

typedef struct {
    f32 v[8];
} Tbl8f_5E3F0;

typedef struct {
    s32 v[4];
} Tbl4_5E3F0;
typedef struct { s32 v[5]; } Tbl5_5E3F0;

typedef struct {
    s32 v[3];
} Tbl3_5E3F0;
typedef struct { s32 x, y, z, w; f32 h; } Cell5_5E3F0;


void free(void *);
s32 func_8022979C(s32, s32, s32);
void func_802297B8(s32, s32, s32, s32);
s32 func_8022984C(s32, s32);
f32 func_80229D3C(void *, s32);
void func_80229E38(void *, s32, s32);
s32 func_80229F74(s32, s32);
f32 func_8022DF68(f32 *, f32 *);
s32 func_8022E884(s32, s32);
s32 func_8022F4AC(s32, s32, s32);
s32 func_8022F550(s32, s32);
void func_8022F808(void *, f32 *);
void func_8022FC90(void *);
void func_8022FEAC(f32 *, f32 *);
void func_8022FF58(f32 *, f32 *, f32 *);
void func_80230914(void *);
s32 func_802311E8(void *);
void * func_80231274(s32, s32, s32, void *);
void func_802313DC(void *, s32);
void func_80231408(void *, s32);
void func_80231434(void *);
s32 func_80232AA8(s32);
s32 func_80232AC8(s32, s32);
void func_80232BA0(f32 *, void *);
s32 func_80232D18(void *, s32);
s32 func_8023372C(f32, f32);
s32 func_80234248(s32);
f32 func_80234408(f32);
f32 func_80234434(f32);
void func_80234858(f32 *, f32 *, f32 *);
void func_802362B8(s32);
void func_802362D4(s32);
void func_80237664(void);
s32 func_80238A10(void *, s32, s32, s32, s32);
void func_80238EA8(s32);
void func_8023903C(s32);
void func_80239094(void);
void func_80239430(void);
void func_80239880(s32, s32, f32 *);
s32 func_802399AC(s32);
s32 func_80239FF8(s32);
void * func_8023A834(void);
void * func_8023A840(void);
s32 func_8023A870(s32, s32);
s32 func_80243824(s32);
void func_802506B8(u8 *);
void func_8026BE80(s32);
s32 func_8026C660(s32);
s32 func_8026D7D8(s32, s32, s32);
s32 func_8026DC74(s32);
void func_8026DCAC(f32, f32, f32, void *, s32);
s32 func_8026DF74(f32, f32, f32);
s32 func_8026E278(s32);
void func_8026E338(f32, f32, f32, f32 *, s32);
s32 func_8026E608(s32, s32);
f32 func_8026E8B8(void);
f32 func_8026E938(void *);
f32 func_8026EAF8(void *);
s32 func_8026EF50(f32, f32, f32);
s32 func_802700EC(s32, s32, s32, s32);
s32 func_802703B4(s32);
s32 func_802704F8(f32);
s32 func_80270714(s32);
s32 func_80270770(s16, s16);
void func_80270BA4(void *);
s32 func_802712A8(s32 *, s32);
s32 func_802712C4(s32);
s32 func_80271540(s16);
s32 func_80271BB8(s32);
void func_802727D8(s32);
void func_802733C8(void *);
s32 func_802741D8(s16);
s32 func_80274994(s32);
s32 func_80274F64(s32);
s32 func_80274F8C(s16, f32, f32, f32, s32);
s32 func_80275C7C(s32, s32, s32);
s32 func_8027750C(s32);
s32 func_802775D8(s32);
s32 func_8027799C(s32);
s32 func_80277CEC(s32);
s32 func_80278E84(s32, s32);
s32 func_8027B0BC(s32);
void func_8027B39C(s16, s16);
void func_8027F820(void *);
void func_8027F858(s32, s32);
void func_80282144(s32, s32, s32, f32);
void func_80282934(void);
void * func_802867E4(s32, f32, f32, f32);
s32 func_80287008(s32, s32, s32);
s32 func_802871D0(s32);
s32 func_8028A4E0(s32);
s32 func_8028A7CC(s32, f32 *, s32);
void func_8028A81C(s32, f32, f32, f32, s32);
s32 func_802909FC(void *, void *);
s32 func_80277378();
s32 func_8027B480();
void func_80291944(void *, s32, f32);
void func_802926EC(void *);
s32 func_8029279C(void *, s32, s32, s32, f32);
void func_80297D30(s32, void *);
void * malloc(s32);

extern s32 D_800AF1D8[];
extern s32 D_800AF5D8[];
extern s32 D_800AF9D8[];
extern s32 D_800AFDD8[];
extern s32 D_800B01D8[];
extern s32 D_800B05D8[];
extern s32 D_800B09D8[];
extern s32 D_800B0DD8[];
extern s32 D_800B11D8[];
extern s32 D_800B15D4[];
extern u8 D_800B15D8;
extern s32 D_802A01B0;
extern s32 D_802A0D88[];
extern s32 D_802A0D94[];
extern s32 D_802A0DA4[];
extern s32 D_802A0DB4[];
extern s32 D_802A0DC8[];
extern s32 D_802A0DE8[];
extern s32 D_802A0E08[];
extern s32 D_802A0E18[];
extern s32 D_802A0E38[];
extern u8 D_802A0E58[];
extern s32 D_802AC5D0;
extern s32 D_802AC890;
extern s32 D_802AC894;
extern s32 D_802AC898;
extern s32 D_802AC89C;
extern s32 D_802AC8A0;
extern s32 D_802AC8A4;
extern s32 D_802AC8A8[];
extern s32 D_802AC8BC;
extern s32 D_802AC8C0;
extern s32 D_802AC8C4;
extern s32 D_802AC8C8;
extern s32 D_802AC8D0[];
extern s32 D_802AC8E8[];
extern s32 D_802AC900[];
extern s32 D_802AC918[];
extern s32 D_802AC930[];
extern s32 D_802AC948[];
extern s32 D_802AC95C;
extern s32 D_802AC960;
extern s32 D_802AC968[];
extern s32 D_802AC97C;
extern s32 D_802AC980[];
extern s32 D_802AC998[];
extern s32 D_802AC9B0[];
extern s32 D_802AC9C8[];
extern s32 D_802AC9DC;
extern s32 D_802AC9E0;
extern s32 D_802AC9E4;
extern s32 D_802AC9E8;
extern s32 D_802AC9EC;
extern s32 D_802AC9F0;
extern s32 D_802AC9F4;
extern s32 D_802AC9F8[];
extern s32 D_802ACA10[];
extern f32 D_802ACA24;
extern f32 D_802ACA28;
extern f32 D_802ACA2C;
extern f32 D_802ACA30[];
extern f32 D_802ACA44;
extern f32 D_802ACA48[];
extern f32 D_802ACA60[];
extern f32 D_802ACA78[];
extern f32 D_802ACA8C;
extern f32 D_802ACA90[];
extern f32 D_802ACE90[];
extern f32 D_802ACEA4;
extern f32 D_802ACEA8;
extern f32 D_802ACEAC;
extern f32 D_802ACEB0;
extern f32 D_802ACEB4;
extern f32 D_802ACEB8;
extern f32 D_802ACEBC;
extern f32 D_802ACEC0;
extern f32 D_802ACEC4;
extern s32 D_802ACEC8[][3];
extern void * D_802ACF04;
extern PadState D_802ACF08[];
extern UnkObj **D_802ACF58;
extern void * D_802ACF5C;
extern s32 * D_802ACF60;
extern f32 D_802ACF68[][3];

void func_80243BF0(void);
void func_80243D20(s32 arg0);
s32 func_80243D2C(s32 arg0);
s32 *func_80243D54(s32 arg0);
void *func_80243D7C(s32 arg0);
void func_80243D90(s32 arg0, s32 arg1, s32 arg2);
s32 func_80243DDC(void);
void func_80243DEC(s32 arg0);
s32 func_80243E18(s32 arg0);
s32 func_80243E3C(void);
void func_80243E60(void);
void func_80243E90(s32 arg0);
s32 func_80243EB4(s32 arg0, s32 arg1);
s32 func_80243EF0(s32 arg0);
void func_80243F2C(s32 arg0, s32 arg1);
s32 func_80243F50(f32 arg0);
s32 func_802441AC(void *arg0);
void func_802441F4(void *arg0, s32 arg1, s32 *arg2, f32 *arg3);
s32 func_802442A8(s32 arg0);
s32 func_802442D0(s32 arg0);
s32 func_802442F8(void);
void func_80244308(void *arg0);
void func_80244354(s32 arg0, s32 arg1, s32 arg2);
void func_802443A0(s32 arg0);
s32 func_802443CC(s32 arg0);
s32 func_802443F4(s32 arg0);
f32 func_8024441C(s32 arg0, s32 arg1);
void func_802444B8(s32 arg0, s32 arg1);
s32 func_80244BA4(s32 arg0, s32 arg1);
void func_80244BE0(s32 arg0, s32 arg1);
void func_80244C30(s32 arg0, s32 arg1);
void func_80244E04(void *arg0);
s32 func_80244F34(void *arg0, s32 arg1);
s32 func_80244FF8(UnkObj *arg0);
void func_802450DC(s32 arg0);
void func_8024512C(s32 arg0, s32 arg1);
s32 func_80245150(s32 arg0);
void func_80245208(s32 arg0, s32 arg1);
void func_80245280(s32 arg0);
s32 func_802452AC(s32 arg0, s32 arg1);
void func_802452E8(s32 arg0);
s32 func_80245408(s32 arg0);
s32 func_80245430(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_80245480(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_802454F8(s32 arg0, s32 *arg1);
void func_8024557C(s32 *arg0);
s32 func_802455A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_80245690(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_802456FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_802457D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8024585C(s32 arg0);
void func_80245868(void);
void func_802459BC(s32 arg0);
void func_80245CDC(void);
void func_80245DFC(void);
void func_80245E1C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2);
void func_80245E2C(s32 arg0, s32 arg1);
void func_80245F74(s32 arg0);
void func_80245FA0(s32 arg0, s32 arg1);
void func_80245FD4(void);
void func_80246018(void);
void func_80246078(void);
void func_80246604(void);
void func_8024663C(void);
void func_80246808(void);
void func_80246938(void);
void func_8024694C(s32 arg0, s32 arg1, s32 arg2);
void func_80246C3C(s32 arg0, s32 arg1, s32 arg2);
void func_80246D74();
void func_80246F00(s32 arg0, s32 arg1);
void func_80247614(void);
void func_80247848(s32 arg0, s32 arg1);
void func_80247928(s32 arg0, s32 arg1);
void func_8024796C(s32 arg0, s32 arg1);
void func_802479F0(s32 *arg0);
void func_80247A54(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80247C50(s32 arg0);
void func_80247CD0(s32 arg0, s32 arg1);
void func_80247D74(s32 arg0, f32 arg1, f32 arg2, s32 arg3, UnkObj *arg4);
void func_80247F90(s32 arg0);
void func_80248148(s32 arg0, s32 arg1);
void func_8024857C(s32 arg0);
void func_8024878C(s32 arg0);
void func_80248864(s32 arg0);
void func_802488C0(s32 arg0);
void func_8024891C(s32 arg0);
void func_8024946C(s32 arg0, s32 arg1);
void func_80249648(s32 arg0, UnkObj *arg1, s32 arg2);
void func_802497D8(s32 arg0);
void func_80249810(s32 arg0, s32 arg1, s32 arg2);
void func_802498D4(s32 arg0, f32 arg1);
void func_80249A30(s32 arg0);
void func_80249AD4(s32 arg0);
void func_80249D30(s32 arg0);
void func_80249D74(s32 arg0);
void func_80249E30(s32 arg0);
void func_80249EEC(s32 arg0);
void func_80249F24(s32 arg0);
void func_80249F5C(s32 arg0);
void func_80249FD4(s32 arg0, s32 arg1);
void func_8024A0DC();
void func_8024A6B4(s32 arg0, f32 arg1);
void func_8024A824(s32 arg0, s32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_8024ABA8(s32 arg0);
void func_8024AF24(s32 arg0, f32 *arg1);
void func_8024AFD4(s32 arg0);
void func_8024B028(s32 arg0);
void func_8024B1CC(s32 arg0);
void func_8024B444(s32 arg0, f32 *arg1);
void func_8024BBA4(s32 arg0);
void func_8024BC20(s32 arg0);
void func_8024BC94(s32 arg0);
void func_8024BD1C(s32 arg0);
void func_8024BF04(s32 arg0);
void func_8024BFE0(s32 arg0);
void func_8024C04C(s32 arg0);
void func_8024C0D8(s32 arg0);
void func_8024C1E8(s32 arg0);
void func_8024C29C(s32 arg0);
void func_8024C314(s32 arg0);
void func_8024C334(s32 arg0, s32 arg1, u16 arg2, f32 *arg3);
s32 func_8024C4EC(UnkObj *obj, s32 arg1);
void func_8024C53C(s32 arg0, void *arg1);
void func_8024C804(s32 arg0);
void func_8024C884(s32 arg0, f32 arg1, s32 arg2);
void func_8024CC58(s32 arg0);
void func_8024CEB8(s32 arg0);
void func_8024D108(s32 arg0, s32 arg1);
void func_8024D20C(s32 arg0);
void func_8024D374(s32 arg0);
s32 func_8024D41C(f32 key);
s32 func_8024D50C(void *arg0);
void func_8024D540(s32 arg0, f32 *arg1);
void func_8024D5D0(Ctl58 *arg0);
void func_8024D8C4(Ctl58 *arg0);
void func_8024E088(s32 arg0);
void func_8024FFF0(void);
void func_802500D4(void);
void func_802502BC(s32 arg0);
void func_80250338(s32 arg0, void *arg1);
s32 func_80250398(s32 arg0);
void func_8025068C(s32 arg0);
void func_802506B8(u8 *str);
void func_80250DC8(void);
void func_80250E2C(s32 arg0);
void func_802510C8(void);
void func_802510F0(void);
void func_80251134(s32 arg0);
void func_802511C4(void);
void func_802511EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_802512C0(s32 arg0, s32 arg1, s32 arg2);
void func_802512F8(void);
void func_80251368(s32 arg0);
s32 func_802513BC(void);
void func_802513CC(void);

void func_802513CC() {
    D_802AC890 = 0;
}

s32 func_802513BC() {
    return D_802AC890;
}

void func_80251368(s32 arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(((UnkObj *)func_802443F4(arg0)), void **, 0x40);
    func_8026EF50(M2C_FIELD(temp_v0, f32 *, 0x10), M2C_FIELD(temp_v0, f32 *, 0x14), M2C_FIELD(temp_v0, f32 *, 0x18));
}

void func_802512F8() {
    s32 id;
    UnkObj *obj;

    id = func_80243DDC();
    obj = (UnkObj *)func_802443F4(id);
    obj->unk40->unk10 = D_800AEDF0[id].unk0;
    obj->unk40->unk14 = D_800AEDF0[id].unk4;
    obj->unk40->unk18 = D_800AEDF0[id].unk8;
    obj->unk40->unk20 = D_800AEDF0[id].unkC;
}

void func_802512C0(s32 arg0, s32 arg1, s32 arg2) {
    func_802511EC(func_80243DDC(), arg0, arg1, arg2);
}

void func_802511EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 pos[3];
    UnkObj *obj;

    func_8026E338(arg1, arg2, arg3, pos, 0);
    obj = (UnkObj *)func_802443F4(arg0);
    if (obj != NULL) {
        obj->unk40->unk10 = pos[0];
        obj->unk40->unk14 = pos[1];
        obj->unk40->unk18 = pos[2];
        D_800AEDF0[arg0].unk0 = -10000.0f;
        D_800AEDF0[arg0].unk4 = -10000.0f;
        D_800AEDF0[arg0].unk8 = -10000.0f;
    } else {
        D_800AEDF0[arg0].unk0 = pos[0];
        D_800AEDF0[arg0].unk4 = pos[1];
        D_800AEDF0[arg0].unk8 = pos[2];
    }
}

void func_802511C4() {
    func_80237664();
    func_802362D4(0x1F);
}

void func_80251134(s32 arg0) {
    if (func_80244BA4(arg0, 0x1000)) {
        func_80247A54(arg0, func_8022F4AC((s32)func_802443F4(arg0), 2, D_800AEDF0[arg0].unk4C), 0, 0);
        func_80244354(arg0, 0x1020, 1);
    }
}

void func_802510F0() {
    s32 i;

    for (i = 0; i < 5; i++) {
        func_80247848(i, 0);
    }
}

void func_802510C8() {
    func_80247C50(func_80243DDC());
}

void func_80250E2C(s32 arg0) {
    s32 id;
    s32 pad[3];
    s32 ipos[3];
    f32 fpos[3];
    f32 cur[3];
    f32 tgt[3];
    s32 pad2[2];
    f32 dir[2];
    Obj88 *obj;
    s32 v;

    id = func_80243DDC();
    obj = (Obj88 *)func_802443F4(id);
    func_8022F808(obj, cur);
    func_80247C50(id);
    func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, ipos, 2);
    func_8026E338(ipos[0], ipos[1], ipos[2], fpos, 0);
    D_802ACA10[id] = 0;
    tgt[0] = fpos[0];
    tgt[1] = fpos[1];
    tgt[2] = fpos[2];
    if (func_8022DF68(cur, tgt) > 0.0f) {
        func_8022FF58(cur, tgt, dir);
        dir[1] -= 90.0f;
        D_802AC8C0 = D_802AC8BC = func_80243F50(dir[0]);
        D_802ACA24 = 4.0f;
        D_802AC95C = 3;
        D_802AC968[id] = 1;
        func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, ipos, 2);
        func_8026E338(ipos[0], ipos[1], ipos[2], fpos, 0);
        D_802ACA28 = fpos[0];
        D_802ACA2C = fpos[1];
        D_802ACA8C = fpos[2];
        func_80244354(id, 0x10420, 1);
        D_802AC918[id] = 0;
        func_802313DC(obj, 0x40000);
        if (arg0 != 0) {
            while (func_80244BA4(id, 0x400)) {
                func_80239094();
            }
        }
    }
}

void func_80250DC8() {
    s32 var_v1;

    var_v1 = func_80243EB4(func_80243DDC(), 0x8000);
    if (var_v1 == 0) {
        func_8024A0DC();
    }
}

void func_802506B8(u8 *str) {
    s32 pad[1];
    u8 *s;
    s32 id = func_80243DDC();
    s32 n;
    s32 c;

    if (!str && !str) {}
    for (n = 0; n < 255; n++) {
        D_800AF1D8[n] = -1;
        D_800AF5D8[n] = -1;
        D_802ACA90[n] = -1.0f;
        D_800AF9D8[n] = -1;
        D_800AFDD8[n] = -1;
        D_800B01D8[n] = -1;
        D_800B05D8[n] = -1;
        D_800B09D8[n] = -1;
        D_800B0DD8[n] = -1;
        D_800B11D8[n] = -1;
    }
    n = 0;
    s = str;
    if (*s != 0) {
        c = *s;
        do {
            D_800AF1D8[n] = c;
            switch (*s) {
            case 'W':
            case 'w':
                switch (*++s) {
                case 'D':
                case 'd':
                    switch (*++s) {
                    case 'N':
                    case 'n':
                        switch (s[1]) {
                        case 'E':
                        case 'e':
                            D_800AF5D8[n] = 0x20;
                            s++;
                            break;
                        case 'W':
                        case 'w':
                            D_800AF5D8[n] = 0xE0;
                            s++;
                            break;
                        default:
                            D_800AF5D8[n] = 0;
                            break;
                        }
                        break;
                    case 'E':
                    case 'e':
                        D_800AF5D8[n] = 0x40;
                        break;
                    case 'S':
                    case 's':
                        switch (s[1]) {
                        case 'E':
                        case 'e':
                            D_800AF5D8[n] = 0x60;
                            s++;
                            break;
                        case 'W':
                        case 'w':
                            D_800AF5D8[n] = 0xA0;
                            s++;
                            break;
                        default:
                            D_800AF5D8[n] = 0x80;
                            break;
                        }
                        break;
                    case 'W':
                    case 'w':
                        D_800AF5D8[n] = 0xC0;
                        break;
                    case 'U':
                    case 'u':
                        D_800AF5D8[n] = 0x100;
                        break;
                    case 'D':
                    case 'd':
                        D_800AF5D8[n] = 0x200;
                        break;
                    }
                    break;
                case 'S':
                case 's':
                    switch (*++s) {
                    case 'L':
                    case 'l':
                        D_802ACA90[n] = 2.0f;
                        break;
                    case 'M':
                    case 'm':
                        D_802ACA90[n] = 4.0f;
                        break;
                    case 'H':
                    case 'h':
                        D_802ACA90[n] = 8.5f;
                        break;
                    case 'S':
                    case 's':
                        D_802ACA90[n] = 1.1111f;
                        break;
                    }
                    break;
                case 'A':
                case 'a':
                    switch (*++s) {
                    case 'O':
                    case 'o':
                        D_800AF9D8[n] = 1;
                        break;
                    case 'A':
                    case 'a':
                        D_800AF9D8[n] = 2;
                        break;
                    case 'P':
                    case 'p':
                        D_800AF9D8[n] = 3;
                        break;
                    case 'B':
                    case 'b':
                        D_800AF9D8[n] = 4;
                        break;
                    case 'D':
                    case 'd':
                        D_800AF9D8[n] = 5;
                        break;
                    }
                    break;
                case 'M':
                case 'm':
                    if (*++s == '1') {
                        D_800B01D8[n] = 1;
                    } else {
                        D_800B01D8[n] = 0;
                    }
                    break;
                case 'G':
                case 'g':
                    if (*++s == '1') {
                        D_800B05D8[n] = 1;
                    } else {
                        D_800B05D8[n] = 0;
                    }
                    break;
                case 'B':
                case 'b':
                    if (s[1] >= '0' && s[1] <= '9') {
                        D_800AFDD8[n] = 0;
                    }
                    while (s[1] >= '0' && s[1] <= '9') {
                        s++;
                        D_800AFDD8[n] *= 10;
                        D_800AFDD8[n] += *s - '0';
                    }
                    n++;
                    break;
                }
                break;
            case 'S':
            case 's':
                D_800B09D8[n] = s[1];
                c = *++s;
                if (c == 'T' || c == 't') {
                    if (s[1] >= '0' && s[1] <= '9') {
                        D_800B0DD8[n] = 0;
                    }
                    while (s[1] >= '0' && s[1] <= '9') {
                        s++;
                        D_800B0DD8[n] *= 10;
                        D_800B0DD8[n] += *s - '0';
                    }
                    n++;
                }
                break;
            case 'M':
            case 'm':
                D_800B11D8[n] = *++s;
                n++;
                break;
            }
            c = *++s;
        } while (c != 0);
    }
    D_800AF1D8[n] = -2;
    func_80244354(id, 0x800, 1);
    D_802AC960 = 0;
    if (func_80243EB4(id, 0x8000)) {
        while (func_80244BA4(id, 0x800) || func_80244BA4(id, 0x80000) || func_80244BA4(id, 0x400)) {
            func_80239094();
        }
    } else {
        while (func_80244BA4(id, 0x800)) {
            func_80239094();
        }
    }
}

void func_8025068C(s32 arg0) {
    D_800AEDF0[func_80243DDC()].unk80 = arg0;
}

s32 func_80250398(s32 arg0) {
    s32 ret = 0;
    UnkObj *obj = (UnkObj *)func_802443F4(arg0);
    s32 pad[3];
    s32 c[3];
    s32 dx;
    s32 dz;

    if ((obj->unk40->unk20 >= 0.0 && obj->unk40->unk20 < 22.5) || (obj->unk40->unk20 >= 337.5 && obj->unk40->unk20 < 360.0)) {
        dx = 0;
        dz = 1;
    }
    if (obj->unk40->unk20 >= 22.5 && obj->unk40->unk20 < 67.5) {
        dx = 1;
        dz = 1;
    }
    if (obj->unk40->unk20 >= 67.5 && obj->unk40->unk20 < 112.5) {
        dx = 1;
        dz = 0;
    }
    if (obj->unk40->unk20 >= 112.5 && obj->unk40->unk20 < 157.5) {
        dx = 1;
        dz = -1;
    }
    if (obj->unk40->unk20 >= 157.5 && obj->unk40->unk20 < 202.5) {
        dx = 0;
        dz = -1;
    }
    if (obj->unk40->unk20 >= 202.5 && obj->unk40->unk20 < 247.5) {
        dx = -1;
        dz = -1;
    }
    if (obj->unk40->unk20 >= 247.5 && obj->unk40->unk20 < 292.5) {
        dx = -1;
        dz = 0;
    }
    if (obj->unk40->unk20 >= 292.5 && obj->unk40->unk20 < 337.5) {
        dx = -1;
        dz = 1;
    }
    func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, c, 2);
    if (!(func_8026D7D8(c[0] + dx, c[1], c[2] + dz) & 0x4000)) {
        ret = 1;
    }
    return ret;
}

void func_80250338(s32 arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = ((UnkObj *)func_802443F4(arg0));
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x40), f32 *, 0x10);
    M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x40), f32 *, 0x14);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x40), f32 *, 0x18);
}

void func_802502BC(s32 arg0) {
    UnkObj *obj;

    obj = (UnkObj *)func_802443F4(arg0);
    func_80243D90(arg0, 0x90, 1);
    D_800AEDF0[arg0].unk78 = 1200;
    func_80231408(obj, 0x40);
    func_80246C3C(arg0, 1, 1);
}

void func_802500D4() {
    UnkObj *objs[4];
    s32 pad[2];
    Tbl4_5E3F0 tbl;
    f32 pos[3];
    f32 off[3];
    s32 pad3[2];
    s32 i;
    s32 r;
    UnkObj *obj;

    tbl = *(Tbl4_5E3F0 *)D_802A0E08;
    for (i = 0; i < 4; i++) {
        objs[i] = NULL;
        if (D_800AEDF0[i].unk14 != 0 && D_800AEDF0[i].unk24 != 0) {
            r = func_80234248(3);
            if (!r && !r) {}
            if (r != 0) {
                obj = D_800AEDF0[i].unk28;
                pos[2] = 50.0f;
                pos[1] = 0.0f;
                pos[0] = obj->unk40->unk20;
                func_8022FEAC(pos, off);
                objs[i] = (UnkObj *)func_80231274(-1, tbl.v[r], 0x60, NULL);
                objs[i]->unk40->unk10 = obj->unk40->unk10 + off[0];
                objs[i]->unk40->unk14 = obj->unk40->unk14 + off[1];
                objs[i]->unk40->unk18 = obj->unk40->unk18 + off[2];
                func_8022E884((s32)objs[i], (s32)obj);
            }
        }
    }
    func_80239094();
    for (i = 0; i < 4; i++) {
        if (objs[i] != NULL) {
            func_8022FC90(objs[i]);
        }
    }
    func_80239430();
}

void func_8024FFF0() {
    UnkStruct_800AEDF0 *p;
    s32 i;

    for (;;) {
        for (i = 0; i != 5; i++) {
            if ((D_800AEDF0[i].unk24 == 1 || D_800AEDF0[i].unk24 == 2) && D_800AEDF0[i].unk28 != NULL) {
                func_8024E088(i);
            }
        }
        if (func_80243E18(1)) {
            func_80247614();
        }
        func_80239094();
    }
}

#define EN ((E88 *)&D_800AEDF0[arg0])
void func_8024E088(s32 arg0) {
    u16 sp126;
    u16 sp124;
    s32 sp120;
    s32 sp11C;
    s32 pad118;
    s32 sp114;
    s32 sp110;
    s32 pad10C;
    s32 sp108;
    s32 pad100[2];
    s32 spFC;
    s32 padF4[2];
    s32 spF0;
    s32 padE4[3];
    s32 spD8[3];
    f32 spD4;
    f32 spD0;
    s32 padC4[3];
    f32 spC0;
    f32 spB4[3];
    s32 padAC[2];
    f32 ang;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp90[3];
    f32 sp84[3];
    f32 sp78[3];
    Obj88 *sp74;
    s32 pad70;
    Obj88 *sp6C;
    s32 *sp68;
    Res58 sp58;
    Obj88 *obj;
    Obj88 *r;

    obj = (Obj88 *)func_802443F4(arg0);
    if (obj->unk40->unk10 != -10000.0f) {
        if (func_802441AC(obj) == arg0) {
            if (obj->unk58 == obj->unk40->unk10) {
                if (obj->unk40->unk14 == obj->unk5C) {
                    if (obj->unk40->unk18 == obj->unk60) {
                        sp120 = 0;
                    }
                }
            }
        }
        EN->unkC = obj->unk40->unk20;
        if (func_80244BA4(arg0, 0x200000)) {
            func_802733C8(obj);
        }
        func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, spD8, 2);
        D_802AC8A4 = func_8026DC74(spD8[1]);
        sp11C = func_8026D7D8(spD8[0], spD8[1], spD8[2]);
        if (func_80244BA4(arg0, 0x400) && EN->unk48 == 0) {
            sp11C = 1;
        }
        if ((obj->unk10 & 0x20) && !func_80244BA4(arg0, 0x10000)) {
            func_80248148(arg0, 2);
        }
        if (((obj->unk10 & 0x40) || (obj->unk10 & 0x80)) && !func_80244BA4(arg0, 0x10000)) {
            func_80248148(arg0, 1);
        }
        if ((obj->unk10 & 0x100) && !func_80244BA4(arg0, 0x10000)) {
            func_80248148(arg0, 0);
        }
        sp108 = D_802AC5D0 & 4;
        D_802ACF5C = func_8023A834();
        if (sp108 && ((s32 *)D_802ACF5C)[0x2C / 4] == 0 && ((s32 *)D_802ACF5C)[0x30 / 4] == 0x3B &&
            func_80243EB4(arg0, 0x200)) {
            if (obj->unk44 != NULL && !func_80244BA4(arg0, 0x1000)) {
                func_80247F90(func_802441AC(obj->unk44));
            }
            func_80248148(arg0, 5);
        }
        if (obj->unk10 & 0x1E00) {
            func_80249648(arg0, obj->unk20, obj->unk10);
        }
        if ((obj->unk10 & 0x40000000) && !func_80244BA4(arg0, 0x1000000)) {
            func_8027F820(obj);
            func_80248148(arg0, 3);
        }
#if VERSION_JP
        {
#else
        if (EN->unk24 != 3) {
#endif
            sp126 = 0;
            sp124 = 0;
            spFC = arg0;
            spB4[2] = 0.0f;
            if (func_80243EB4(arg0, 0x2000)) {
                spFC = EN->unkA4;
                if (EN->unk24 == 1) {
                    func_80239880(arg0, 0, sp90);
                } else {
                    sp90[2] = D_802ACF08[arg0].unk8;
                    sp90[1] = D_802ACF08[arg0].unk4;
                    sp90[0] = D_802ACF08[arg0].unk0;
                }
            }
            if (func_80244BA4(arg0, 0x1000) || obj->unk44 == NULL) {
                if (D_800AEDF0[spFC].unk24 == 1) {
                    func_80239880(spFC, 0, spB4);
                    sp126 = func_80239FF8(spFC);
                    sp124 = func_802399AC(spFC);
                } else {
                    spB4[2] = D_802ACF08[spFC].unk8;
                    spB4[1] = D_802ACF08[spFC].unk4;
                    spB4[0] = D_802ACF08[spFC].unk0;
                    sp126 = D_802ACF08[spFC].unkC;
                    sp124 = D_802ACF08[spFC].unkE;
                }
            }
            if (func_802452AC(arg0, 0x2000C20)) {
                if ((sp126 & 0x4000) && (sp124 & 0x8000) && func_802452AC(arg0, 0x840A182) &&
                    !func_80243EB4(arg0, 8) && !func_80243EB4(arg0, 0x80) && !func_80243EB4(arg0, 0x200) &&
                    !(sp11C & 0x4000) && func_80274994((s16)arg0)) {
                    func_80249FD4(arg0, 1);
                } else {
                    if ((sp124 & 0x8000) && !(sp126 & 0x4000) && func_802452AC(arg0, 0x4000C3) &&
                        !func_80243EB4(arg0, 8) && !func_80243EB4(arg0, 0x80) && !func_80243EB4(arg0, 0x200)) {
                        sp74 = (Obj88 *)func_8022F550((s32)obj, 2);
                        if (sp74 != NULL && (s32)sp74 == EN->unk4C) {
                            if (obj->unk6C == 0.0f) {
                                sp74 = (Obj88 *)func_8022F550((s32)obj, 2);
                                func_80249810(arg0, (s32)sp74, 2);
                            }
                        } else {
                            r = (Obj88 *)func_80274F8C(EN->unk1A, obj->unk40->unk10, obj->unk40->unk14,
                                                       obj->unk40->unk18, arg0);
                            if (r != NULL) {
                                func_80247928(arg0, r->unk1C);
                                func_8026C660(0xA);
                            }
                        }
                    }
                    if ((sp124 & 0x4000) ||
                        (func_80243E18(2) && !(D_802AC9EC & 7) && obj->unk44 == NULL &&
                         func_802452AC(arg0, 0x1180))) {
                        if (!func_80270714((s16)arg0)) {
                            func_802313DC(obj, 1);
                            sp68 = (s32 *)func_80271540((s16)arg0);
                            sp68[3] |= 0x10;
                            func_80231408(obj, 1);
                            if (sp68 != NULL) {
                                func_80249FD4(arg0, 0);
                            } else {
                                func_80243824(0xF);
                            }
                        } else {
                            func_80249F5C(arg0);
                        }
                    }
                }
            }
            if (func_802452AC(arg0, 0x2000400)) {
                if (sp124 & 0x10) {
                    func_802712C4(func_8027799C((s16)func_80274F64((s16)arg0)));
                }
                if (sp124 & 0x2000) {
                    func_8027750C((s16)arg0);
                }
            }
            sp120 = 1;
            spD4 = 0.0f;
            if (func_80244BA4(arg0, 0x400) && func_802452AC(arg0, 0x1C0)) {
                func_8024D8C4((Ctl58 *)&sp58);
                spD4 = sp58.unk0;
                sp120 = sp58.unk4;
                if ((D_802AC968[arg0] & 1) == 1 && D_802AC97C == 0) {
                    obj->unk40->unk48->unk4->unk4 = 0.0f;
                    obj->unk40->unk48->unk4->unk10 = 0.0f;
                    obj->unk40->unk14 += sp58.unkC;
                }
            }
            if (func_80244BA4(arg0, 2)) {
                func_8024D540(arg0, (f32 *)&sp58);
                spD4 = sp58.unk0;
                sp120 = sp58.unk4;
            }
            if (!func_8023372C(spB4[2], 0.001f)) {
                func_80234858(&sp9C, &spA0, &spA4);
                if (spA0 >= 180.0f && spA0 < 360.0f && D_802AC9F4 != 0) {
                    spB4[0] = WRAP360(180.0f - spB4[0]);
                }
                ang = WRAP360(spB4[0] + sp9C);
                if (!spA0 && !spA0) {}
                if (func_802452AC(arg0, 0x2000C20)) {
                    if (spB4[2] > 20.0f && spB4[2] < 35.0f) {
                        spD4 = 2.0f;
                    }
                    if (spB4[2] >= 35.0f && spB4[2] < 60.0f) {
                        spD4 = 4.0f;
                    }
                    if (spB4[2] >= 60.0f) {
                        spD4 = 8.5f;
                    }
                    if (spD4 > 0.0f) {
                        if ((ang >= 0.0 && ang < 22.5) || (ang >= 337.5 && ang < 360.0)) {
                            sp120 = 0x80;
                            spD0 = 0.0f;
                        }
                        if (ang >= 22.5 && ang < 67.5) {
                            spD0 = 45.0f;
                            sp120 = 0x60;
                        }
                        if (ang >= 67.5 && ang < 112.5) {
                            spD0 = 90.0f;
                            sp120 = 0x40;
                        }
                        if (ang >= 112.5 && ang < 157.5) {
                            spD0 = 135.0f;
                            sp120 = 0x20;
                        }
                        if (ang >= 157.5 && ang < 202.5) {
                            spD0 = 180.0f;
                            sp120 = 0;
                        }
                        if (ang >= 202.5 && ang < 247.5) {
                            spD0 = 225.0f;
                            sp120 = 0xE0;
                        }
                        if (ang >= 247.5 && ang < 292.5) {
                            spD0 = 270.0f;
                            sp120 = 0xC0;
                        }
                        if (ang >= 292.5 && ang < 337.5) {
                            spD0 = 315.0f;
                            sp120 = 0xA0;
                        }
                        if (!func_80244BA4(arg0, 0x8000000)) {
                            func_8024A6B4(arg0, spD0);
                        }
                        if (func_80243EB4(arg0, 4)) {
                            spD4 *= 0.5f;
                        }
                        if (func_80243EB4(arg0, 1)) {
                            spD4 *= 4.0f;
                        }
                        if (func_80243EB4(arg0, 0x200)) {
                            spD4 *= 0.8f;
                        }
                        if (func_8024D50C((void *)EN->unk2C)) {
                            spD4 *= 0.8f;
                        }
                    }
                }
            }
            if (func_80243EB4(arg0, 0x20) && !func_80244BA4(arg0, 0x20)) {
                spD4 = 8.5f - spD4;
                if (spD4 < 2.0f) {
                    spD4 = 0.0f;
                }
                if (sp120 == 1) {
                    sp120 = func_8024D41C(obj->unk40->unk20);
                    if (sp120 == -1) {
                        sp120 = 1;
                        spD4 = 0.0f;
                    }
                }
            }
            if (obj->unk40->unk14 - func_8026E938(obj->unk40) > 500.0f) {
                if (!func_80244BA4(arg0, 0x400000) && obj->unk6C > 2.0f && EN->unk50 == 0 &&
                    (obj->unk8 & 0x1000000)) {
                    func_8026C660(0x1B);
                    EN->unk50 = 1;
                }
            }
            if (obj->unk6C > 32.0f && func_802452AC(arg0, 0x60000A)) {
                func_8024D374(arg0);
            }
            if (obj->unk6C == 0.0f && func_80244BA4(arg0, 8)) {
                func_8024D20C(arg0);
            }
            if (func_80244BA4(arg0, 0x4000)) {
                spD4 *= 0.3f;
            }
            if (func_802452AC(arg0, 0x31C2)) {
                if (spD4 > 0.0f && spD4 < 4.0f) {
                    if (!func_80244BA4(arg0, 0x8000)) {
                        if (func_802443CC(arg0) != 1) {
                            func_802444B8(arg0, 1);
                        }
                    } else if (func_802443CC(arg0) != 0xD) {
                        func_802444B8(arg0, 0xD);
                    }
                }
                if (spD4 >= 4.0f && spD4 < 8.5f) {
                    if (!func_80244BA4(arg0, 0x8000)) {
                        if (func_802443CC(arg0) != 2) {
                            func_802444B8(arg0, 2);
                        }
                    } else if (func_802443CC(arg0) != 0xE) {
                        func_802444B8(arg0, 0xE);
                    }
                }
                if (spD4 >= 8.5f) {
                    if (!func_80244BA4(arg0, 0x8000)) {
                        if (func_802443CC(arg0) != 3) {
                            func_802444B8(arg0, 3);
                        }
                    } else if (func_802443CC(arg0) != 0xF) {
                        func_802444B8(arg0, 0xF);
                    }
                }
                if (spD4 == 0.0f) {
                    sp110 = func_802443CC(arg0);
                    switch (sp110) {
                        case 1:
                        case 2:
                        case 3:
                            func_8024D108(arg0, sp110);
                            func_802444B8(arg0, 0);
                            break;
                        case 13:
                        case 14:
                        case 15:
                            func_8024D108(arg0, sp110);
                            func_802444B8(arg0, 0xC);
                            break;
                    }
                }
                func_8024CEB8(arg0);
            }
            if (obj->unk8 & 0x20000) {
                func_802727D8(EN->unk40);
            } else {
                if (func_80244BA4(arg0, 0x80)) {
                    func_8024CC58(arg0);
                }
                if (func_80244BA4(arg0, 0x40)) {
                    func_8024C884(arg0, spB4[2], sp126);
                }
                if (func_80244BA4(arg0, 0x200)) {
                    func_8024C804(arg0);
                }
                if (func_80244BA4(arg0, 0x100)) {
                    func_8024C53C(arg0, D_802ACF68[arg0]);
                }
                if (!func_80244BA4(arg0, 0x2000000) && func_80244BA4(arg0, 0x1000)) {
                    func_8024C334(arg0, (s32)sp74, sp124, spB4);
                }
                if (!func_80244BA4(arg0, 0x2000000) && func_80244BA4(arg0, 0x10000)) {
                    func_8024C29C(arg0);
                }
                if (func_80244BA4(arg0, 0x2000)) {
                    func_8024C1E8(arg0);
                }
                if (func_80244BA4(arg0, 0x20000)) {
                    func_8024C0D8(arg0);
                }
                if (func_80244BA4(arg0, 0x8000)) {
                    func_8024C04C(arg0);
                }
                if (func_80244BA4(arg0, 0x4000000)) {
                    func_8024BFE0(arg0);
                }
                if (func_80243EB4(arg0, 0x400)) {
                    func_8024BF04(arg0);
                }
                if (func_80244BA4(arg0, 0x8000000)) {
                    func_8024BD1C(arg0);
                }
                if (func_80243EB4(arg0, 0x10000)) {
                    func_8024BC94(arg0);
                }
                if (func_80243EB4(arg0, 0x20000)) {
                    func_8024BC20(arg0);
                }
                if (func_80243EB4(arg0, 0x200000)) {
                    func_8024BBA4(arg0);
                }
                if (func_80243EB4(arg0, 2)) {
                    func_8024B444(arg0, (f32 *)&sp58);
                    spD4 = sp58.unk0;
                    sp120 = sp58.unk4;
                }
                if (func_80243EB4(arg0, 0x10)) {
                    func_8024B1CC(arg0);
                }
                if (func_80243EB4(arg0, 0x100)) {
                    func_8024B028(arg0);
                }
                if (func_80243EB4(arg0, 0x40)) {
                    func_8024AFD4(arg0);
                }
                if (func_80243EB4(arg0, 0x2000)) {
                    func_8024AF24(arg0, sp90);
                }
                if (func_80244BA4(arg0, 0x800) && !func_80244BA4(arg0, 0x80000)) {
                    if (func_80243EB4(arg0, 0x8000)) {
                        if (!func_80244BA4(arg0, 0x400)) {
                            func_8024ABA8(arg0);
                        }
                    } else {
                        func_8024ABA8(arg0);
                    }
                }
                if (func_80244BA4(arg0, 0x80000) && !func_80244BA4(arg0, 0x400)) {
                    func_80249AD4(D_802AC980[arg0]);
                }
                if (func_80243EB4(arg0, 0x2000)) {
                    sp6C = (Obj88 *)func_802443F4(EN->unkA8);
                }
                if (func_802452AC(arg0, 0x600000) && sp120 != 1) {
                    func_80291944(obj, sp120, spD4);
                }
                if (sp11C & 0x1C00) {
                    func_8027F858((s32)obj, (sp11C & 0x1C00) >> 10);
                }
                if (func_802452AC(arg0, 0x600000) && EN->unk48 == 1) {
                    func_80230914(obj);
                }
                if (EN->unk2C != NULL) {
                    func_80231434(EN->unk2C);
                }
                if (func_80243EB4(arg0, 0x2000)) {
                    func_80231434(sp6C);
                }
                sp110 = 0;
                D_802AC9E4 = arg0;
                if (EN->unk2C != NULL) {
                    func_8022F808(EN->unk2C, sp84);
                    sp114 = 0;
                    if (EN->unk2C->unk8 & 1) {
                        sp114 = func_802909FC(EN->unk2C, func_80245150);
                    }
                    if (EN->unk2C->unk8 & 2) {
                        sp114 = func_802909FC(EN->unk2C, func_80277378);
                    }
                    if (EN->unk2C->unk8 & 4) {
                        sp114 = func_802909FC(EN->unk2C, func_80245150);
                    }
                    if (EN->unk2C->unk8 & 8) {
                        sp114 = func_802909FC(EN->unk2C, func_8027B480);
                    }
                    if (sp114 != 0) {
                        obj->unk40->unk10 += EN->unk2C->unk40->unk10 - sp84[0];
                        obj->unk40->unk18 += EN->unk2C->unk40->unk18 - sp84[2];
                        spC0 = func_8026EAF8(obj);
                        if (obj->unk40->unk14 < spC0) {
                            func_80244354(arg0, 8, 0);
                            obj->unk6C = 0.0f;
                        }
                        obj->unk40->unk14 = spC0;
                        func_8022F808(obj, sp78);
                        if (func_8022DF68(sp78, &obj->unk58) >= 100.0f) {
                            func_80232BA0(&obj->unk58, obj);
                        }
                        if (func_802909FC(obj, func_80245150)) {
                            if (obj->unk40->unk14 < obj->unk5C && obj->unk68 < obj->unk6C) {
                                func_80244C30(arg0, 1);
                                func_802444B8(arg0, 0);
                            }
                            obj->unk40->unk20 = EN->unkC;
                            func_80244354(arg0, 0x8000000, 0);
                        }
                        sp110 = 1;
                    }
                }
                if (func_80243EB4(arg0, 0x2000)) {
                    sp6C = (Obj88 *)func_802443F4(EN->unkA8);
                    func_8022F808(sp6C, sp84);
                    spF0 = func_802909FC(sp6C, func_80245150);
                    if (spF0 != 0) {
                        obj->unk40->unk10 += sp6C->unk40->unk10 - sp84[0];
                        obj->unk40->unk18 += sp6C->unk40->unk18 - sp84[2];
                        spC0 = func_8026EAF8(obj);
                        if (obj->unk40->unk14 < spC0) {
                            func_80244354(arg0, 8, 0);
                            obj->unk6C = 0.0f;
                        }
                        obj->unk40->unk14 = spC0;
                        func_8022F808(obj, sp78);
                        if (func_8022DF68(sp78, &obj->unk58) >= 150.0f) {
                            func_80232BA0(&obj->unk58, obj);
                        }
                        if (func_802909FC(obj, func_80245150)) {
                            obj->unk40->unk20 = EN->unkC;
                            func_80244354(arg0, 0x8000000, 0);
                        }
                        sp110++;
                    }
                }
                if (sp110 == 0) {
                    func_802909FC(obj, func_80245150);
                }
                func_80249A30(arg0);
                if (func_80244BA4(arg0, 1)) {
                    func_802498D4(arg0, spD4);
                }
                func_8026E938(obj->unk40);
                D_802ACF60 = func_8023A840();
                if (obj->unk5C - obj->unk40->unk14 > 15.0f) {
                    func_80244354(arg0, 0x4000, 1);
                } else if (func_80244BA4(arg0, 0x4000)) {
                    func_80244354(arg0, 0x4000, 0);
                }
#if VERSION_JP
                if (obj->unk40->unk14 < 0.0f && !func_80244BA4(arg0, 0x20)) {
                    func_80244354(arg0, 0x20, 1);
                    func_80270770((s16)arg0, 1);
                }
#endif
                r = (Obj88 *)func_8022F4AC((s32)obj, 2, EN->unk4C);
                if (r != NULL && r->unk44 == NULL && !func_80244BA4(arg0, 1) && obj->unk6C == 0.0f) {
                    func_802497D8(arg0);
                }
                r = (Obj88 *)func_8022F4AC((s32)obj, 0x1E00, EN->unk4C);
                if (r != NULL) {
                    func_80249648(arg0, (UnkObj *)r, r->unk8);
                }
                func_8024891C(arg0);
                sp74 = (Obj88 *)func_8022F4AC((s32)obj, 0x10, EN->unk4C);
                if (func_80243EB4(arg0, 0x2000) && sp74 == (Obj88 *)func_802443F4(EN->unkA8)) {
                    sp74 = NULL;
                }
                if (sp74 != NULL) {
                    D_802ACF68[arg0][0] = obj->unk40->unk10 - obj->unk58;
                    D_802ACF68[arg0][1] = obj->unk40->unk14 - obj->unk5C;
                    D_802ACF68[arg0][2] = obj->unk40->unk18 - obj->unk60;
                    func_80232BA0(&obj->unk58, obj);
                    if (func_80244BA4(arg0, 2)) {
                        func_8024878C(arg0);
                        obj->unk68 = 0.0f;
                        obj->unk70 = 1.6333334f;
                    }
                    if (obj->unk6C > 0.0f && obj->unk44 == NULL && sp74->unk40->unk14 < obj->unk40->unk14) {
                        if (func_80244BA4(arg0, 2)) {
                            spD0 = EN->unkC + 180.0f;
                            if (spD0 >= 360.0f) {
                                spD0 -= 360.0f;
                            }
                        } else {
                            spD0 = EN->unkC;
                        }
                        EN->unk40 = func_802700EC((s32)obj, (s32)sp74, func_80243F50(spD0), 0x41000000);
                        func_80244354(arg0, 0x2100, 0);
                        if (func_80244BA4(arg0, 0x80) || func_80244BA4(arg0, 0x40)) {
                            func_80244C30(arg0, 1);
                        }
                        func_80244354(arg0, 0x400020, 1);
                        if (!func_80244BA4(arg0, 0x8000)) {
                            func_802444B8(arg0, 0x13);
                        } else {
                            func_802444B8(arg0, 0x14);
                        }
                        if (func_80243EB4(arg0, 0x2000)) {
                            func_80247F90(arg0);
                        }
                    }
                    if ((func_80244BA4(arg0, 0x8000) && sp114 != 0) || (func_80243EB4(arg0, 0x2000) && spF0 != 0)) {
                        if (func_80244BA4(arg0, 0x8000000)) {
                            func_80244354(arg0, 0x8000000, 0);
                            obj->unk40->unk20 = EN->unk64;
                        }
                    }
                }
                if (EN->unk2C != NULL && (EN->unk2C->unk8 & 0x10)) {
                    func_80231434(EN->unk2C);
                    sp74 = (Obj88 *)func_8022F4AC((s32)EN->unk2C, 0x10, (s32)obj);
                    if (func_80244BA4(arg0, 0x400)) {
                        sp74 = NULL;
                    }
                    if (sp74 != NULL) {
                        func_80232BA0(&EN->unk2C->unk58, EN->unk2C);
                        func_80232BA0(&obj->unk58, obj);
                        if (func_80244BA4(arg0, 0x8000000)) {
                            func_80244354(arg0, 0x8000000, 0);
                            obj->unk40->unk20 = EN->unk64;
                        }
                        if (obj->unk6C > 0.0f) {
                            func_80244C30(arg0, 0);
                        }
                    }
                }
                if (func_80243EB4(arg0, 0x2000)) {
                    sp6C = (Obj88 *)func_802443F4(EN->unkA8);
                    func_80231434(sp6C);
                    sp74 = (Obj88 *)func_8022F4AC((s32)sp6C, 0x10, (s32)obj);
                    if (func_80244BA4(arg0, 0x400)) {
                        sp74 = NULL;
                    }
                    if (sp74 != NULL) {
                        if (obj->unk40->unk14 < obj->unk5C && obj->unk68 < obj->unk6C) {
                            func_80247F90(arg0);
                        } else {
                            func_80232BA0(&sp6C->unk58, sp6C);
                            func_80232BA0(&obj->unk58, obj);
                            if (func_80244BA4(arg0, 0x8000000)) {
                                func_80244354(arg0, 0x8000000, 0);
                                obj->unk40->unk20 = EN->unk64;
                                if (obj->unk6C > 0.0f) {
                                    func_80247F90(arg0);
                                }
                            }
                        }
                    }
                }
#if !VERSION_JP
                if (obj->unk40->unk14 < 0.0f) {
                    func_80270770((s16)arg0, 1);
                }
#endif
            }
            if (!func_80244BA4(arg0, 0x400) && !func_80244BA4(arg0, 8) && !func_80244BA4(arg0, 0x2000)) {
                func_8024857C(arg0);
            }
            EN->unk64 = EN->unk60;
        }
    }
}
#undef EN

void func_8024D8C4(Ctl58 *arg0) {
    f32 dist;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 angle;
    Obj88 *obj;
    f32 pos[3];
    f32 target[3];
    f32 res[3];
    f32 rot[3];
    f32 unused[3];
    s32 ipos[3];
    s32 b1;
    s32 b0;
    s32 id;
    s32 pad[3];

    id = func_80243DDC();
    b0 = D_802AC968[id] & 1;
    b1 = (D_802AC968[id] >> 1) & 1;
    if (b0) {
        arg0->unk8 = D_802AC95C;
    } else {
        arg0->unk8 = 3;
    }
    arg0->unkC = 0.0f;
    obj = (Obj88 *)func_802443F4(id);
    func_8022F808(obj, pos);
    target[0] = D_802ACA28;
    if (D_802AC8BC == 0x100 || D_802AC8BC == 0x200) {
        target[1] = D_802ACA2C;
    } else {
        target[1] = pos[1];
    }
    if (!D_802ACA8C && !D_802ACA8C) {}
    target[2] = D_802ACA8C;
    angle = obj->unk40->unk20;
    func_8022FF58(pos, target, rot);
    rot[1] -= 90.0f;
    dist = func_8022DF68(pos, target);
    if (b0) {
        arg0->unk4 = D_802AC8BC;
    } else {
        arg0->unk4 = func_80243F50(rot[0]);
    }
    if (D_802ACA24 < dist || func_80244BA4(id, 0x4000)) {
        arg0->unk0 = D_802ACA24;
    } else {
        arg0->unk0 = dist;
    }
    if (func_80244BA4(id, 0x2000)) {
        arg0->unk0 = 0.0f;
    }
    if (arg0->unk8 != 3) {
        func_8024D5D0(arg0);
    }
    if ((D_802AC8BC != 0x100 && D_802AC8BC != 0x200) || b0 != 1) {
        if (dist >= 1.0f) {
            arg0->unk4 = func_80243F50(rot[0]);
        if (!dist && !dist) {}
        }
    }
    if (dist <= 1.0f) {
        if (!b0) {
            dz = 0.0f;
            dx = 0.0f;
            dy = 0.0f;
            switch (D_802AC8BC) {
            case 0x0:
                angle = 180.0f;
                dz = -D_802AC8C4;
                break;
            case 0x80:
                angle = 0.0f;
                dz = D_802AC8C4;
                break;
            case 0xC0:
                angle = 270.0f;
                dx = -D_802AC8C4;
                break;
            case 0x40:
                angle = 90.0f;
                dx = D_802AC8C4;
                break;
            case 0x20:
                angle = 135.0f;
                dx = D_802AC8C4;
                dz = -D_802AC8C4;
                break;
            case 0xE0:
                angle = 225.0f;
                dx = dz = -D_802AC8C4;
                break;
            case 0x60:
                angle = 45.0f;
                dx = dz = D_802AC8C4;
                break;
            case 0xA0:
                angle = 315.0f;
                dz = D_802AC8C4;
                dx = -D_802AC8C4;
                break;
            case 0x100:
                dy = D_802AC8C4;
                break;
            case 0x200:
                dy = -D_802AC8C4;
                break;
            }
            func_8026DCAC(obj->unk40->unk10 + dx * 100.0f, obj->unk40->unk14 + dy * 100.0f,
                          obj->unk40->unk18 + dz * 100.0f, ipos, 2);
            func_8026E338(ipos[0], ipos[1], ipos[2], res, 0);
            D_802ACA28 = res[0];
            D_802ACA2C = res[1];
            D_802ACA8C = res[2];
            func_8024A6B4(id, angle);
        } else {
            switch (D_802AC8BC) {
            case 0x0:
                angle = 180.0f;
                break;
            case 0x80:
                angle = 0.0f;
                break;
            case 0xC0:
                angle = 270.0f;
                break;
            case 0x40:
                angle = 90.0f;
                break;
            case 0x20:
                angle = 135.0f;
                break;
            case 0xE0:
                angle = 225.0f;
                break;
            case 0x60:
                angle = 45.0f;
                break;
            case 0xA0:
                angle = 315.0f;
                break;
            }
            obj->unk40->unk10 = D_802ACA28;
            if (D_802AC8BC == 0x100 || D_802AC8BC == 0x200) {
                obj->unk40->unk14 = D_802ACA2C;
            }
            obj->unk40->unk18 = D_802ACA8C;
            func_80244354(id, 0x420, 0);
            if (!func_80244BA4(id, 0x2000000)) {
                func_80244354(id, 0x10000, 0);
            }
            D_800AEDF0[id].unk48 = 1;
            obj->unk70 = 1.6333334f;
            func_8024D108(id, D_800AEDF0[id].unk44);
        }
        arg0->unk0 = 0.0f;
        obj->unk40->unk10 = target[0];
        obj->unk40->unk18 = target[2];
        if (D_802AC8BC != 0x100 && D_802AC8BC != 0x200) {
            obj->unk40->unk20 = angle;
        }
        b0++;
    }
    D_802AC968[id] = b1 * 2 + b0;
    if (!(D_802ACA10[id] & 3)) {
        func_8022F808(obj, pos);
        D_802ACF60 = func_8023A840();
        if (!(*D_802ACF60 & 2)) {
            func_802775D8((s32)pos);
        }
        func_80282934();
    }
    D_802ACA10[id]++;
}

void func_8024D5D0(Ctl58 *arg0) {
    f32 dist;
    f32 pitch;
    f32 yaw;
    f32 org[3];
    f32 vec[3];
    f32 x;
    f32 y;
    f32 z;
    s32 dir;
    s32 tilt;
    s32 pad[1];
    f32 angle;
    f32 s;

    if (!yaw && !yaw) {}
    if (!arg0->unk0 && !arg0->unk0) {}
    dir = arg0->unk4;
    tilt = arg0->unk8;
    dist = arg0->unk0;
    switch (dir) {
    case 0x0:
        angle = 180.0f;
        break;
    case 0x20:
        angle = 135.0f;
        break;
    case 0x40:
        angle = 90.0f;
        break;
    case 0x60:
        angle = 45.0f;
        break;
    case 0x80:
        angle = 0.0f;
        break;
    case 0xA0:
        angle = 315.0f;
        break;
    case 0xC0:
        angle = 270.0f;
        break;
    case 0xE0:
        angle = 225.0f;
        break;
    }
    switch (tilt) {
    case 1:
        pitch = 0.0f;
        angle = 0.0f;
        break;
    case 2:
        pitch = 45.0f;
        break;
    case 3:
        pitch = 90.0f;
        break;
    case 4:
        pitch = 135.0f;
        break;
    case 5:
        angle = 0.0f;
        pitch = 180.0f;
        break;
    }
    yaw = angle;
    s = func_80234434(yaw);
    x = func_80234434(pitch) * (dist * s);
    y = func_80234408(pitch) * dist;
    s = func_80234408(yaw);
    z = func_80234434(pitch) * (dist * s);
    if (x < 0.01 && x > -0.01) {
        x = 0.0f;
    }
    if (y < 0.01 && y > -0.01) {
        y = 0.0f;
    }
    if (z < 0.01 && z > -0.01) {
        z = 0.0f;
    }
    org[0] = 0.0f;
    org[1] = 0.0f;
    org[2] = 0.0f;
    vec[1] = 0.0f;
    vec[2] = z;
    vec[0] = x;
    func_8022FF58(org, vec, &yaw);
    arg0->unk4 = func_80243F50(yaw);
    arg0->unk0 = dist;
    arg0->unkC = y;
}

void func_8024D540(s32 arg0, f32 *arg1) {
    Obj88 *obj;

    arg1[0] = D_802ACA44;
    ((s32 *)arg1)[1] = D_800AEDF0[arg0].unkA0;
    obj = (Obj88 *)func_802443F4(arg0);
    if (obj->unk68 == 0.0f && obj->unk6C == 0.0f) {
        func_8024878C((s32)obj);
    }
}

s32 func_8024D50C(void *arg0) {
    s32 ret = 0;

    if (arg0 != NULL) {
        s32 v = D_802AC5D0 & 4;
        if ((M2C_FIELD(arg0, s32 *, 8) & 4) && v) {
            ret = 1;
        }
    }
    return ret;
}

s32 func_8024D41C(f32 key) {
    Tbl8i_5E3F0 vals;
    Tbl8f_5E3F0 keys;
    s32 i;
    s32 r;

    vals = *(Tbl8i_5E3F0 *)D_802A0DC8;
    keys = *(Tbl8f_5E3F0 *)D_802A0DE8;
    r = -1;
    for (i = 0; i < 8 && r == -1; i++) {
        if (key == keys.v[i]) {
            r = vals.v[i];
        }
    }
    return r;
}

void func_8024D374(s32 arg0) {
    func_80244354(arg0, 0x100, 0);
    if (!func_80244BA4(arg0, 0x1000)) {
        if (func_802452AC(arg0, 0x8080)) {
            func_802444B8(arg0, 0xA);
        } else {
            func_802444B8(arg0, 0x12);
        }
        func_80244354(arg0, 8, 1);
    }
}

void func_8024D20C(s32 arg0) {
    UnkObj *sp64;
    UnkStruct_800AEDF0 *sp20;
    UnkModel *temp_v0;
    UnkObj *temp_v1;
    UnkStruct_800AEDF0 *temp_t8;
    s16 var_a3;
    s32 temp_a0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    temp_t8 = &D_800AEDF0[arg0];
    sp20 = temp_t8;
    var_a3 = arg0;
    var_v1 = func_80244BA4(arg0, 0x40);
    if (var_v1 != 0) {
        func_80270770(var_a3, 1);
        var_a3 = (s16) (s32) arg0;
        sp20->unk2C = 0;
    }
    arg0 = (s32) var_a3;
    func_80244354((s32) var_a3, 0x148, 0);
    func_80244354((s32) arg0, 0x2020, 1);
    temp_a0 = sp20->unk10;
    var_v1_2 = 0;
    if ((temp_a0 & 0x8000) == 0x8000) {
        var_v1_2 = 1;
    }
    if (var_v1_2 == 0) {
        var_v1_3 = 0;
        if ((temp_a0 & 0x80) == 0x80) {
            var_v1_3 = 1;
        }
        if (var_v1_3 == 0) {
            func_802444B8((s32) arg0, 9);
        } else {
            goto block_11;
        }
    } else {
block_11:
        func_802444B8((s32) arg0, 0x11);
    }
    temp_v1 = sp20->unk28;
    sp64 = temp_v1;
    temp_v0 = temp_v1->unk40;
    func_8028A81C(0xC, temp_v0->unk10, temp_v0->unk14 + 20.0f, temp_v0->unk18, 0);
    if (M2C_FIELD(sp64, s32 *, 8) & 0x01000000) {
        func_8026C660(0x1C);
    }
    sp20->unk50 = 0;
}

void func_8024D108(s32 arg0, s32 arg1) {
    s32 pad[2];
    UnkObj *o;
    s32 anim;
    s32 pad2[2];
    UnkStruct_800AEDF0 *e = &D_800AEDF0[arg0];
    f32 len;
    f32 t;

    o = e->unk28;
    D_802AC9F8[arg0] = arg1;
    t = 0.0f;
    switch (e->unk44) {
        case 1:
        case 2:
        case 3:
            anim = 0;
            break;
        case 13:
        case 14:
        case 15:
            anim = 1;
            break;
        default:
            anim = -1;
            break;
    }
    if (anim != -1) {
        len = func_80229D3C(o->unk40, anim);
        t = M2C_FIELD(M2C_FIELD(M2C_FIELD(o->unk40, void **, 0x48), s32 *, 4) + anim * 0xC, f32 *, 4) + 1.0f;
        if (len <= t) {
            t -= len;
        }
    }
    D_802ACA78[arg0] = t;
}

void func_8024CEB8(s32 arg0) {
    Obj88 *obj;
    s32 pad[3];
    f32 pos[3];
    UnkStruct_800AEDF0 *p;
    s32 hit;
    s32 v;

    p = &D_800AEDF0[arg0];
    obj = (Obj88 *)p->unk28;
    hit = 0;
    v = p->unk44;
    if (!p && !p) {}
    switch (v) {
    case 1:
    case 13:
        v = obj->unk40->unk48->unk4->unk10;
        if (v == 12.0f || v == 36.0f) {
            hit = 1;
        }
        break;
    case 2:
    case 14:
        v = obj->unk40->unk48->unk4->unk10;
        if (v == 0.0f || v == 20.0f) {
            hit = 1;
        }
        break;
    case 3:
    case 15:
        v = obj->unk40->unk48->unk4->unk10;
        if (v == 0.0f || v == 16.0f) {
            hit = 1;
        }
        break;
    }
    if (D_802ACF60) {}
    if (hit) {
        D_802ACF60 = func_8023A840();
        if (D_802ACF60[1] == 3 && D_802ACF60[2] == 0) {
            func_8026C660(0x30);
        }
        if (D_802ACF60[1] == 0) {
            func_8022F808(obj, pos);
            if ((func_8026DF74(pos[0], pos[1], pos[2]) & 0x1C00) == 0x400) {
                func_8026C660(0x31);
            }
        }
    }
}

void func_8024CC58(s32 arg0) {
    Obj88 *obj;
    s32 r;
    s32 pad;
    f32 vec[3];
    UnkStruct_800AEDF0 *p;
    s32 i;

    p = &D_800AEDF0[arg0];
    obj = (Obj88 *)func_802443F4(arg0);
    if (i) {}
    if (func_80243EB4(arg0, 0x2000)) {
        i = p->unkA4;
        vec[2] = 70.0f;
        vec[1] = D_802ACE90[i];
        vec[0] = 180.0f;
        func_8022FEAC(vec, D_800AEDF0[i].unk28->unk4C);
        D_802ACE90[i] -= 1.0f;
    }
    if (obj->unk40->unk48->unk4->unk4 == 2.0f && !(p->unk38 & 0x80)) {
        if (p->unk3C == 0) {
            r = func_80271540((s16)arg0);
            if (r != 0) {
                func_80271BB8((s16)arg0);
                p->unk2C = r;
            } else {
                func_80244354(arg0, 0xA0, 0);
                func_802444B8(arg0, 0);
                p->unk2C = 0;
            }
        } else {
            func_802741D8((s16)arg0);
            p->unk2C = func_80270714((s16)arg0);
            if (p->unk2C == 0) {
                func_80244354(arg0, 0xA0, 0);
                func_802444B8(arg0, 0);
            }
        }
        p->unk38 |= 0x80;
    }
    if ((obj->unk40->unk48->unk4->unk8 & 0x40) && func_80277CEC(arg0)) {
        func_80244354(arg0, 0xA0, 0);
        func_80244354(arg0, 0x8000, 1);
        func_802444B8(arg0, 0xC);
    }
    if (p->unk2C != 0 && (s32)obj != M2C_FIELD(p->unk2C, s32 *, 0x44)) {
        func_80244C30(arg0, 0);
    }
}

void func_8024C884(s32 arg0, f32 arg1, s32 arg2) {
    Tbl4_5E3F0 tbl;
    s32 level;
    s32 pad;
    Obj88 *obj;
    s32 pad2;
    f32 vec[3];
    s32 pad3[2];

    tbl = *(Tbl4_5E3F0 *)D_802A0D94;
    if (arg2 & 0x4000) {
        D_800AEDF0[arg0].unkAC++;
    }
    obj = (Obj88 *)func_802443F4(arg0);
    if (obj->unk40->unk48->unk4->unk4 == 12.0f && !(D_800AEDF0[arg0].unk38 & 0x40)) {
        if (func_80244BA4(arg0, 0x80000)) {
            switch (D_800AEDF0[arg0].unk80) {
            case 1:
                arg1 = 0.0f;
                break;
            case 2:
                arg1 = 10.0f;
                break;
            case 3:
                arg1 = 60.0f;
                break;
            }
        }
        if (*(s32 *)((u8 *)func_8023A840() + 0x48) == 1 && !func_80244BA4(arg0, 0x80000)) {
            if (D_800AEDF0[arg0].unkAC < 6) {
                level = 1;
            }
            if (D_800AEDF0[arg0].unkAC >= 6 && D_800AEDF0[arg0].unkAC < 13) {
                level = 2;
            }
            if (D_800AEDF0[arg0].unkAC >= 13) {
                level = 3;
            }
        } else {
            if (arg1 < 10.0f) {
                level = 1;
            }
            if (arg1 >= 10.0f && arg1 < 60.0f) {
                level = 2;
            }
            if (arg1 >= 60.0f) {
                level = 3;
            }
        }
        func_8026C660(0x20);
        func_80270770((s16)arg0, (s16)level);
        D_800AEDF0[arg0].unk2C = 0;
        if ((D_802AC5D0 & 4) || arg0 == 0) {
            func_802479F0(tbl.v);
        } else {
            func_8026C660(0x20);
        }
        D_800AEDF0[arg0].unk38 |= 0x40;
    if (!obj && !obj) {}
    }
    if ((obj->unk40->unk48->unk4->unk8 & 0x40) ||
        (obj->unk40->unk48->unk4->unk4 < 12.0f && D_800AEDF0[arg0].unk2C == 0)) {
        func_80244354(arg0, 0x60, 0);
        func_802444B8(arg0, 0);
        if (func_80243EB4(arg0, 0x2000)) {
            vec[2] = 70.0f;
            vec[1] = 60.0f;
            vec[0] = 180.0f;
            func_8022FEAC(vec, ((Obj88 *)func_802443F4(D_800AEDF0[arg0].unkA4))->unk4C);
        }
    }
}

void func_8024C804(s32 arg0) {
    if (func_8024C4EC((UnkObj *)func_802443F4(arg0), 2) != D_800AEDF0[arg0].unk4C) {
        func_80244354(arg0, 0x200, 0);
        D_800AEDF0[arg0].unk4C = 0;
    }
}

void func_8024C53C(s32 arg0, void *arg1) {
    Tbl5_5E3F0 tbl;
    Obj88 *obj;
    s32 r;
    f32 pos[3];
    s32 pad[2];

    tbl = *(Tbl5_5E3F0 *)D_802A0DB4;
    obj = (Obj88 *)func_802443F4(arg0);
    if (obj->unk40->unk48->unk4->unk4 == 11.0f && !(D_800AEDF0[arg0].unk38 & 0x100)) {
        func_8022F808(obj, pos);
        if (D_800AEDF0[arg0].unkBC == 1) {
            obj->unk40->unk10 += ((f32 *)arg1)[0];
            obj->unk40->unk14 += ((f32 *)arg1)[1];
            obj->unk40->unk18 += ((f32 *)arg1)[2];
        }
        r = func_8024C4EC((UnkObj *)obj, 2);
        if (r != 0) {
            if ((D_802AC5D0 & 4) || arg0 == 0) {
                func_802479F0(tbl.v);
            } else {
                func_8026C660(0x1F);
            }
            func_80275C7C((s16)arg0, r, (s16)func_802704F8(obj->unk40->unk20));
        }
        func_80232BA0(pos, obj);
        D_800AEDF0[arg0].unk38 |= 0x100;
    }
    if (obj->unk40->unk48->unk4->unk8 & 0x40) {
        func_80244354(arg0, 0x100, 0);
        if (!func_80244BA4(arg0, 0x8000)) {
            func_802444B8(arg0, 0);
        } else {
            func_802444B8(arg0, 0xC);
        }
        r = func_8024C4EC((UnkObj *)obj, 2);
        if (r != 0) {
            D_800AEDF0[arg0].unk4C = r;
            func_80244354(arg0, 0x200, 1);
        } else {
            func_80244354(arg0, 0x200, 0);
            D_800AEDF0[arg0].unk4C = 0;
        }
        func_80244354(arg0, 0x20, 0);
    }
}

s32 func_8024C4EC(UnkObj *obj, s32 arg1) {
    s32 r;

    M2C_FIELD(obj, s32 *, 0xC) &= ~0x1E00;
    r = func_8022F550((s32)obj, 2);
    M2C_FIELD(obj, s32 *, 0xC) |= 0x1E00;
    return r;
}

void func_8024C334(s32 arg0, s32 arg1, u16 arg2, f32 *arg3) {
    UnkStruct_800AEDF0 *e = &D_800AEDF0[arg0];

    if (!FLAG_SET(e->unk10, 2)) {
        if (!(e->unk38 & 0x1000)) {
            func_802444B8(arg0, 8);
            e->unk38 |= 0x1000;
        }
    }
    if (FLAG_CLEAR(e->unk10, 0x600002)) {
        D_802AC8D0[arg0]--;
    }
    if (!FLAG_SET(e->unk10, 0x400000) && arg3[2] > 60.0) {
        if (arg3[0] != D_802ACA30[arg0]) {
            D_802AC900[arg0]--;
        }
    }
    if (D_802AC8D0[arg0] == 0 || D_802AC900[arg0] == 0) {
        func_80247A54(arg0, arg1, 30, 1);
    }
    D_802ACA30[arg0] = arg3[0];
}

void func_8024C314(s32 arg0) {
    func_802444B8(arg0, 8);
}

void func_8024C29C(s32 arg0) {
    UnkObj *o;

    if (D_802AC918[arg0] > 0) {
        if (--D_802AC918[arg0] == 0) {
            o = (UnkObj *)func_802443F4(arg0);
            func_80244354(arg0, 0x10000, 0);
            func_802313DC(o, 0x40000);
        }
    }
}

void func_8024C1E8(s32 arg0) {
    if (((Obj88 *)func_802443F4(arg0))->unk40->unk48->unk4->unk8 & 0x40) {
        func_80244354(arg0, 0x2020, 0);
        if (!func_80244BA4(arg0, 0x8000)) {
            func_802444B8(arg0, 0);
        } else {
            func_802444B8(arg0, 0xC);
        }
    }
}

void func_8024C0D8(s32 arg0) {
    UnkObj *o = (UnkObj *)func_802443F4(arg0);
    f32 *p = &D_802ACA60[arg0];
    f32 t;

    *p += 16.0f;
    if (*p >= 360.0f) {
        o->unk40->unk20 = *p - 360.0f;
    } else {
        o->unk40->unk20 = *p;
    }
    t = D_802ACA48[arg0];
    if (*p - t > 360.0f) {
        *p = t;
        if (--D_802AC930[arg0] == 0) {
            o->unk40->unk20 = t;
            func_80244354(arg0, 0x20020, 0);
            func_802313DC(o, 0x40000);
            func_8024796C(arg0, 60);
        }
    }
}

void func_8024C04C(s32 arg0) {
    s32 id;
    s32 pad2;
    UnkStruct_800AEDF0 *p;

    id = arg0;
    p = &D_800AEDF0[id];
    if (!p) {}
    if (func_80270714((s16)id) == 0) {
        func_80244354(id, 0x8000, 0);
        func_802444B8(id, 0);
        p->unk2C = 0;
        func_80244354(id, 0x120, 0);
    }
}

void func_8024BFE0(s32 arg0) {
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(((UnkObj *)func_802443F4(arg0)), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40) {
        func_80244354(arg0, 0x04000020, 0);
    }
}

void func_8024BF04(s32 arg0) {
    UnkStruct_800AEDF0 *p = &D_800AEDF0[arg0];
    UnkObj *obj = (UnkObj *)func_802443F4(arg0);

    if (p->unk2C != 0) {
        if (func_80274F8C(M2C_FIELD(p, s16 *, 0x1A), obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, arg0) == 0) {
            if (func_802712A8(func_802703B4(p->unk2C) + 0x64, 0x80) != 0) {
                func_80243D90(arg0, 0x400, 0);
                func_80244354(arg0, 0x20, 0);
            }
        }
    } else {
        func_80243D90(arg0, 0x400, 0);
        func_80244354(arg0, 0x20, 0);
    }
}

void func_8024BD1C(s32 arg0) {
    UnkStruct_800AEDF0 *e = &D_800AEDF0[arg0];
    UnkObj *o = e->unk28;

    if (!D_800AEDF0[arg0].unk10 && !D_800AEDF0[arg0].unk10) {}
    if (e->unk64 > 360.0f) {
        e->unk64 -= 360.0f;
    }
    if (e->unk64 < 0.0f) {
        e->unk64 += 360.0f;
    }
    e->unk60 += e->unk5C;
    o->unk40->unk20 = e->unk60;
    if (e->unk60 > 360.0f) {
        o->unk40->unk20 -= 360.0f;
    }
    if (e->unk60 < 0.0f) {
        o->unk40->unk20 += 360.0f;
    }
    if ((e->unk5C > 0.0f && e->unk58 <= e->unk60) || (e->unk5C < 0.0f && e->unk60 <= e->unk58)) {
        o->unk40->unk20 = e->unk58;
        if (o->unk40->unk20 >= 360.0f) {
            o->unk40->unk20 -= 360.0f;
        }
        if (o->unk40->unk20 < 0.0f) {
            o->unk40->unk20 += 360.0f;
        }
        func_80244354(arg0, 0x8000000, 0);
    }
    if (e->unk2C != 0) {
        func_80231434((void *)e->unk2C);
    }
}

void func_8024BC94(s32 arg0) {
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(((UnkObj *)func_802443F4(arg0)), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40) {
        func_80244354(arg0, 0x20, 0);
        func_80243D90(arg0, 0x10000, 0);
        func_802444B8(arg0, 0);
    }
}

void func_8024BC20(s32 arg0) {
    UnkStruct_800AEDF0 *sp1C;
    UnkStruct_800AEDF0 *temp_v0;
    s32 temp_t9;

    temp_v0 = &D_800AEDF0[arg0];
    temp_t9 = temp_v0->unkB8 - 1;
    temp_v0->unkB8 = temp_t9;
    if (temp_t9 == 0) {
        sp1C = temp_v0;
        func_8022FC90((void *) temp_v0->unkB4);
        temp_v0->unkB4 = 0;
        func_80243D90(arg0, 0x20000, 0);
    }
}

void func_8024BBA4(s32 arg0) {
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(((UnkObj *)func_802443F4(arg0)), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40) {
        func_80244354(arg0, 0x20, 0);
        func_80243D90(arg0, 0x200000, 0);
    }
}

void func_8024B444(s32 arg0, f32 *arg1) {
    s32 pad0[2];
    UnkObj *o2;
    f32 old;
    s32 pad1[3];
    f32 posA[3];
    f32 posB[3];
    f32 vec[3];
    s32 other;
    s32 pad2[4];
    UnkStruct_800AEDF0 *e;
    UnkObj *o;
    s32 found;
    s32 i;
    s32 j;

    M2C_FIELD(arg1, s32 *, 4) = 0;
    arg1[0] = 0.0f;
    e = &D_800AEDF0[arg0];
    o = e->unk28;
    if (func_80243EB4(arg0, 0x2000)) {
        other = e->unkA8;
        if (o->unk40->unk28 > 1.0f) {
            if (D_800AEDF0[other].unkC4 == 8.0f) {
                D_800AEDF0[other].unkC4 = 6.0f;
            }
            if (D_800AEDF0[other].unkC4 == -8.0f) {
                D_800AEDF0[other].unkC4 = -6.0f;
            }
        }
        if (o->unk40->unk28 < 1.0f) {
            if (D_800AEDF0[other].unkC4 == 6.0f) {
                D_800AEDF0[other].unkC4 = 8.0f;
            }
            if (D_800AEDF0[other].unkC4 == -6.0f) {
                D_800AEDF0[other].unkC4 = -8.0f;
            }
        }
        old = D_800AEDF0[other].unkC0;
        D_800AEDF0[other].unkC0 += D_800AEDF0[other].unkC4;
        o2 = (UnkObj *)func_802443F4(other);
        vec[2] = D_800AEDF0[other].unkC0;
        vec[1] = 60.0f;
        vec[0] = 180.0f;
        func_8022FEAC(vec, o2->unk4C);
        func_80231434(o2);
    }
    o->unk40->unk28 += e->unk6C;
    o->unk40->unk2C += e->unk6C;
    o->unk40->unk30 += e->unk6C;
    found = func_8022F4AC((s32)o, 0x10, e->unk4C);
    if (found != 0) {
        func_8022F808(o, posA);
        func_8022F808((void *)found, posB);
        vec[1] = 0.0f;
        vec[0] = 0.0f;
        vec[2] = 5.0f;
        for (j = 0; j < 50; j++) {
            for (i = 0; i != 8; i++) {
                func_80232BA0(posA, o);
                func_80291944(o, i << 5, vec[2]);
                if (!func_802909FC(o, func_80245150) && !func_8022F4AC((s32)o, 0x10, e->unk4C)) {
                    M2C_FIELD(o, f32 *, 0x58) = o->unk40->unk10;
                    M2C_FIELD(o, f32 *, 0x5C) = o->unk40->unk14;
                    M2C_FIELD(o, f32 *, 0x60) = o->unk40->unk18;
                    goto found;
                }
            }
            vec[2] += 2.0f;
        }
        func_80232BA0(posA, o);
        do {
            o->unk40->unk14 += 10.0f;
        } while (func_802909FC(o, func_80245150) || func_8022F4AC((s32)o, 0x10, e->unk4C));
        func_80247D74(arg0, 22.5f, 8.0f, 1, NULL);
    found:
        func_8022F808(o, posB);
        arg1[0] = func_8022DF68(posA, posB);
        if (func_80243EB4(arg0, 0x2000)) {
            D_800AEDF0[other].unkC0 = old;
            vec[2] = old;
            vec[1] = 60.0f;
            vec[0] = 180.0f;
            func_8022FEAC(vec, o2->unk4C);
            func_80231434(o2);
        }
    }
    M2C_FIELD(e->unkB0, f32 *, 0x4C) = o->unk40->unk28;
    M2C_FIELD(e->unkB0, f32 *, 0x54) = o->unk40->unk30;
    if ((e->unk6C > 0.0f && e->unk70 <= o->unk40->unk28) || (e->unk6C < 0.0f && o->unk40->unk28 <= e->unk70)) {
        o->unk40->unk28 = e->unk70;
        o->unk40->unk2C = e->unk70;
        o->unk40->unk30 = e->unk70;
        M2C_FIELD(e->unkB0, f32 *, 0x4C) = o->unk40->unk28;
        M2C_FIELD(e->unkB0, f32 *, 0x54) = o->unk40->unk30;
        if (e->unk6C > 0.0f) {
            func_80243D90(arg0, 2, 0);
            if (o->unk40->unk28 == 1.0f) {
                func_80243D90(arg0, 1, 0);
                if (!(e->unk68 & 8 | 0xA0) && !(e->unk18 & 0x404)) {
                    func_80243D90(arg0, 0x10, 0);
                }
            } else if (func_80243EB4(arg0, 0x2000)) {
                vec[2] = 100.0f;
                vec[1] = 60.0f;
                vec[0] = 180.0f;
                func_8022FEAC(vec, D_800AEDF0[e->unkA8].unk28->unk4C);
            }
        }
        if (e->unk6C < 0.0f) {
            func_80243D90(arg0, 2, 0);
            if (o->unk40->unk28 == 1.0f) {
                func_80243D90(arg0, 4, 0);
                if (!(e->unk68 & 8 | 0xA0) && !(e->unk18 & 0x404)) {
                    func_80243D90(arg0, 0x10, 0);
                }
            } else if (func_80243EB4(arg0, 0x2000)) {
                vec[2] = 30.0f;
                vec[1] = 60.0f;
                vec[0] = 180.0f;
                func_8022FEAC(vec, D_800AEDF0[e->unkA8].unk28->unk4C);
            }
        }
        func_80243D90(arg0, 2, 0);
    }
    e->unk74++;
}

void func_8024B1CC(s32 arg0) {
    UnkObj *obj;
    UnkStruct_800AEDF0 *p;
    s32 t;

    p = &D_800AEDF0[arg0];
    obj = (UnkObj *)func_802443F4(arg0);
    t = --p->unk78;
    if (t == 0) {
        if (func_80243EB4(arg0, 4)) {
            func_80270770((s16)arg0, 1);
            p->unk2C = 0;
            func_8024694C(arg0, 1, 0);
            func_80243D90(arg0, 4, 0);
        }
        if (func_80243EB4(arg0, 1)) {
            func_80270770((s16)arg0, 1);
            p->unk2C = 0;
            func_8024694C(arg0, 2, 0);
            func_80243D90(arg0, 1, 0);
        }
        if (func_80243EB4(arg0, 0x80)) {
            func_802313DC(obj, 0x40);
            func_80243D90(arg0, 0x80, 0);
            if (!func_80244BA4(arg0, 0x10000)) {
                func_80248148(arg0, 1);
            }
        }
        if (func_80243EB4(arg0, 0x100)) {
            func_80246C3C(arg0, 0, 0);
        }
        if (func_80243EB4(arg0, 8)) {
            func_80243D90(arg0, 8, 0);
        }
        if (func_80243EB4(arg0, 0x20)) {
            func_80243D90(arg0, 0x20, 0);
        }
        func_80243D90(arg0, 0x10, 0);
        p->unk18 &= ~0x404;
        func_8026C660(0x1ED);
        return;
    }
    if (func_80243EB4(arg0, 0x80) && !(t & 3)) {
        func_8028A81C(7, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
    }
}

void func_8024B028(s32 arg0) {
    s32 r;
    s32 g;
    s32 b;
    s32 pad[2];
    UnkStruct_800AEDF0 *e = &D_800AEDF0[arg0];
    UnkObj *o = e->unk28;

    e->unk8C += e->unk88;
    switch (e->unk84) {
        case 1:
            r = 0x1F;
            g = 0;
            b = 0;
            break;
        case 2:
            b = 4;
            g = 4;
            r = 4;
            break;
        case 3:
            g = 0x1F;
            r = 0x1F;
            b = 0;
            break;
    }
    if (e->unk8C > 1.0f && e->unk88 > 0.0f) {
        e->unk8C = 1.0f;
        e->unk88 = -e->unk88;
    }
    if (e->unk8C < 0.0f && e->unk88 < 0.0f) {
        e->unk8C = 0.0f;
        e->unk88 = -e->unk88;
    }
    func_8029279C(o->unk40, r, g, b, e->unk8C);
    if (--e->unk90 == 0 || !func_80243EB4(arg0, 0x10)) {
        func_80246C3C(arg0, 0, 0);
    }
}

void func_8024AFD4(s32 arg0) {
    if (--D_800AEDF0[arg0].unk7C == 0) {
        func_80243D90(arg0, 0x40, 0);
    }
}

void func_8024AF24(s32 arg0, f32 *arg1) {
    if (!D_800AEDF0[arg0].unk10 && !D_800AEDF0[arg0].unk10) {}
    D_802AC998[arg0]--;
    if (arg1[2] > 60.0 && arg1[0] != D_802ACA30[arg0]) {
        D_802AC9B0[arg0]--;
    }
    if (D_802AC998[arg0] == 0 || D_802AC9B0[arg0] == 0) {
        func_80247F90(arg0);
    }
}

void func_8024ABA8(s32 arg0) {
    s32 flag;

    if (!D_800AEDF0[arg0].unk10 && !D_800AEDF0[arg0].unk10) {}
    if (D_802AC960 != 0) {
        if (D_800AF1D8[D_802AC960] == -1) {
            D_800AF1D8[D_802AC960] = D_800AF1D8[D_802AC960 - 1];
        }
        if (D_800AF5D8[D_802AC960] == -1) {
            D_800AF5D8[D_802AC960] = D_800AF5D8[D_802AC960 - 1];
        }
        if (D_802ACA90[D_802AC960] == -1.0f) {
            D_802ACA90[D_802AC960] = D_802ACA90[D_802AC960 - 1];
        }
        if (D_800AF9D8[D_802AC960] == -1) {
            D_800AF9D8[D_802AC960] = D_800AF9D8[D_802AC960 - 1];
        }
        if (D_800AFDD8[D_802AC960] == -1) {
            D_800AFDD8[D_802AC960] = D_800AFDD8[D_802AC960 - 1];
        }
        if (D_800B01D8[D_802AC960] == -1) {
            D_800B01D8[D_802AC960] = D_800B01D8[D_802AC960 - 1];
        }
        if (D_800B05D8[D_802AC960] == -1) {
            D_800B05D8[D_802AC960] = D_800B05D8[D_802AC960 - 1];
        }
        if (D_800B09D8[D_802AC960] == -1) {
            D_800B09D8[D_802AC960] = D_800B09D8[D_802AC960 - 1];
        }
        if (D_800B0DD8[D_802AC960] == -1) {
            D_800B0DD8[D_802AC960] = D_800B0DD8[D_802AC960 - 1];
        }
        if (D_800B11D8[D_802AC960] == -1) {
            D_800B11D8[D_802AC960] = D_800B11D8[D_802AC960 - 1];
        }
    }
    switch (D_800AF1D8[D_802AC960]) {
        case 'W':
        case 'w':
            func_8024A824(D_800AF5D8[D_802AC960], D_800AF9D8[D_802AC960], D_802ACA90[D_802AC960],
                          D_800AFDD8[D_802AC960], 0, D_800B01D8[D_802AC960], D_800B05D8[D_802AC960]);
            break;
        case 'S':
        case 's':
            if (D_800B09D8[D_802AC960] == 'T' || D_800B09D8[D_802AC960] == 't') {
                func_8024A0DC(0x40000);
            }
            break;
        case 'M':
        case 'm':
            switch (D_800B11D8[D_802AC960]) {
                case '0':
                    flag = 0x200;
                    break;
                case '1':
                    flag = 0x80;
                    break;
                case '2':
                    flag = 0x40;
                    break;
                case '3':
                    flag = 0x100000;
                    break;
                case '4':
                    flag = 0x800;
                    break;
                case '5':
                    flag = 0x4000;
                    break;
                case '6':
                    flag = 0x400;
                    break;
                case '7':
                    flag = 0x10000;
                    break;
                case '8':
                    flag = 0x20000;
                    break;
                case '9':
                    flag = 0x200000;
                    break;
                case 'A':
                    flag = 0x400000;
                    break;
                case 'B':
                    flag = 0x4000000;
                    break;
            }
            func_8024A0DC(flag);
            break;
    }
    D_802AC960++;
    if (D_800AF1D8[D_802AC960] == -2) {
        func_80244354(arg0, 0x800, 0);
    }
}

void func_8024A824(s32 arg0, s32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 id;
    f32 angle;
    f32 dist;
    s32 pad[3];
    s32 ipos[3];
    f32 fpos[3];
    f32 cur[3];
    f32 tgt[3];
    Obj88 *obj;
    s32 pad2[2];
    f32 dir;

    id = func_80243DDC();
    obj = (Obj88 *)func_802443F4(id);
    if (arg0 != 0x400) {
        D_802AC8BC = arg0;
    }
    if (arg2 != 32768.0f) {
        D_802ACA24 = arg2;
    }
    if (arg1 != 6) {
        D_802AC95C = arg1;
    }
    D_802AC8C4 = arg3;
    if (arg5 != 6) {
        D_802AC97C = arg5;
    }
    D_800AEDF0[id].unk48 = arg6;
    if (arg6 == 0) {
        obj->unk70 = 0.0f;
    }
    D_802AC968[id] = arg5 * 2;
    func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, ipos, 2);
    func_8026E338(ipos[0], ipos[1], ipos[2], fpos, 0);
    D_802ACA28 = fpos[0];
    D_802ACA2C = fpos[1];
    D_802ACA8C = fpos[2];
    D_802ACA10[id] = 0;
    func_8022F808(obj, cur);
    tgt[0] = fpos[0];
    tgt[1] = cur[1];
    tgt[2] = fpos[2];
    dist = func_8022DF68(cur, tgt);
    func_80244354(id, 0x10420, 1);
    D_802AC918[id] = 0;
    func_802313DC(obj, 0x40000);
    func_80247C50(id);
    if (dist > 0.0f) {
        func_8022FF58(cur, tgt, &dir);
        D_802AC8C0 = func_80243F50(dir);
    } else {
        D_802AC8C0 = D_802AC8BC;
    }
    if (D_802AC8BC != 0x100 && D_802AC8BC != 0x200) {
        switch (D_802AC8C0) {
        case 0x0:
            angle = 180.0f;
            break;
        case 0x80:
            angle = 0.0f;
            break;
        case 0xC0:
            angle = 270.0f;
            break;
        case 0x40:
            angle = 90.0f;
            break;
        case 0x20:
            angle = 135.0f;
            break;
        case 0xE0:
            angle = 225.0f;
            break;
        case 0x60:
            angle = 45.0f;
            break;
        case 0xA0:
            angle = 315.0f;
            break;
        }
        func_8024A6B4(id, angle);
    }
    if (arg4 != 0) {
        while (func_80244BA4(id, 0x400)) {
            func_80239094();
        }
    }
}

void func_8024A6B4(s32 arg0, f32 arg1) {
    UnkStruct_800AEDF0 *e = &D_800AEDF0[arg0];
    UnkObj *o = (UnkObj *)func_802443F4(arg0);
    f32 lo;
    f32 hi;

    if (arg1 != o->unk40->unk20) {
        e->unk58 = arg1;
        e->unk64 = o->unk40->unk20;
        if (o->unk40->unk20 < arg1) {
            lo = o->unk40->unk20;
            hi = e->unk58;
        } else {
            hi = o->unk40->unk20;
            lo = e->unk58;
        }
        if ((lo + 360.0f) - hi < hi - lo) {
            if (lo == e->unk58) {
                e->unk58 += 360.0f;
            } else {
                e->unk58 -= 360.0f;
            }
            if (e->unk58 == -360.0f) {
                e->unk58 = 360.0f;
            }
        }
        if (o->unk40->unk20 < e->unk58) {
            e->unk5C = 20.0f;
        } else {
            e->unk5C = -20.0f;
        }
        e->unk60 = o->unk40->unk20;
        func_80244354(arg0, 0x8000000, 1);
    }
}

void func_8024A0DC(s32 arg0) {
    Obj88 *obj;
    s32 pad[7];
    s32 ipos[3];
    s32 pad2[4];
    s32 id;
    s32 flags;
    s32 off;
    s16 sid;

    id = func_80243DDC();
    D_802AC980[id] = arg0;
    off = id * 4;
    obj = (Obj88 *)func_802443F4(id);
    switch (arg0) {
    case 0x200:
        if (func_80232D18(obj, 2) != 0) {
            func_80244354(id, 0x200, 0);
            D_800AEDF0[id].unk4C = 0;
            func_80249810(id, func_8022F550((s32)obj, 2), 2);
        } else {
            D_800AEDF0[id].unk4C = ((Obj88 *)func_80274F8C(((E88 *)&D_800AEDF0[id])->unk1A, obj->unk40->unk10,
                                                           obj->unk40->unk14, obj->unk40->unk18, 0))->unk1C;
            func_80244354(id, 0x200, 1);
        }
        break;
    case 0x80:
        sid = id;
        if (!func_80270714(sid)) {
            D_800AEDF0[id].unk2C = func_80271540(sid);
            if (!id && !id) {}
            if (D_800AEDF0[id].unk2C != 0) {
                func_80249FD4(id, 0);
                func_80244354(id, 0x90000, 1);
                *(s32 *)((u8 *)D_802AC918 + off) = 0;
                func_802313DC(obj, 0x40000);
            } else {
                func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, ipos, 2);
                flags = func_8026D7D8(ipos[0], ipos[1], ipos[2]);
                if (func_802452AC(id, 0x8100) && !(flags & 0x4000)) {
                    if (func_80274994(sid)) {
                        func_80249FD4(id, 1);
                    }
                }
                func_80244354(id, 0x90000, 1);
                *(s32 *)((u8 *)D_802AC918 + off) = 0;
                func_802313DC(obj, 0x40000);
            }
        }
        break;
    case 0x40:
        if (func_80270714((s16)id)) {
            func_80244354(id, 0x80000, 1);
            func_80249F5C(id);
        }
        break;
    case 0x40000:
        *(s32 *)((u8 *)D_802AC9C8 + off) = D_800B0DD8[D_802AC960];
        func_80244354(id, 0x90020, 1);
        *(s32 *)((u8 *)D_802AC918 + off) = 0;
        func_802313DC(obj, 0x40000);
        break;
    case 0x100000:
        obj = (Obj88 *)func_802443F4(id);
        obj->unk68 = 40.0f;
        func_80244354(id, 0x90020, 1);
        *(s32 *)((u8 *)D_802AC918 + off) = 0;
        func_802313DC(obj, 0x40000);
        break;
    case 0x4000000:
        func_80244354(id, 0x90000, 1);
        if (!off && !off) {}
        *(s32 *)((u8 *)D_802AC918 + off) = 0;
        func_802313DC(obj, 0x40000);
        func_80244354(id, 0x04000020, 1);
        func_802444B8(id, 0x15);
        break;
    case 0x400:
        func_80244354(id, 0x90000, 1);
        func_80243D90(id, 0x400, 1);
        func_80244354(id, 0x20, 1);
        break;
    case 0x800:
        func_8027750C((s16)id);
        break;
    case 0x4000:
        func_802712C4(func_8027799C((s16)func_80274F64((s16)id)));
        break;
    case 0x10000:
        func_80244354(id, 0x80000, 1);
        func_80249E30(id);
        break;
    case 0x20000:
        func_80244354(id, 0x80000, 1);
        func_80249D74(id);
        break;
    case 0x200000:
        func_80244354(id, 0x80000, 1);
        func_80249D30(id);
        break;
    case 0x400000:
        if (D_802AC8BC != 0 && D_802AC8BC != 0x20 && D_802AC8BC != 0x40 && D_802AC8BC != 0x60 &&
            D_802AC8BC != 0x80 && D_802AC8BC != 0xA0) {
        if (!flags && !flags) {}
        if (!obj && !obj) {}
        }
        func_80244354(id, 0x420, 0);
        if (!func_80244BA4(id, 0x02000000)) {
            func_80244354(id, 0x10000, 0);
        }
        D_800AEDF0[id].unk48 = 1;
        obj->unk70 = 1.6333334f;
        break;
    }
    if (off) {}
}

void func_80249FD4(s32 arg0, s32 arg1) {
    Tbl4_5E3F0 tbl;
    UnkStruct_800AEDF0 *p;

    tbl = *(Tbl4_5E3F0 *)D_802A0DA4;
    func_802444B8(arg0, 4);
    func_80244354(arg0, 0xA0, 1);
    p = &D_800AEDF0[arg0];
    p->unk3C = arg1;
    if ((D_802AC5D0 & 4) || p == D_800AEDF0) {
        func_802479F0(tbl.v);
    }
    if (func_80243EB4(arg0, 0x2000)) {
        D_802ACE90[p->unkA4] = 60.0f;
    }
    p->unk38 &= ~0x80;
}

void func_80249F5C(s32 arg0) {
    UnkStruct_800AEDF0 *temp_v0;

    func_802444B8(arg0, 6);
    func_80244354(arg0, 0x60, 1);
    func_80244354(arg0, 0x8000, 0);
    temp_v0 = &D_800AEDF0[arg0];
    temp_v0->unkAC = 0;
    temp_v0->unk38 &= ~0x40;
}

void func_80249F24(s32 arg0) {
    func_80244354(arg0, 0x04000020, 1);
    func_802444B8(arg0, 0x15);
}

void func_80249EEC(s32 arg0) {
    func_80243D90(arg0, 0x400, 1);
    func_80244354(arg0, 0x20, 1);
}

void func_80249E30(s32 arg0) {
    s32 pad[4];

    if (func_80244BA4(arg0, 0x40)) {
        func_80270770((s16)arg0, 1);
        D_800AEDF0[arg0].unk2C = 0;
    }
    func_80244354(arg0, 0x148, 0);
    func_80244354(arg0, 0x20, 1);
    func_80243D90(arg0, 0x10000, 1);
    func_802444B8(arg0, 0x17);
}

void func_80249D74(s32 arg0) {
    UnkObj *o;

    if (!func_80243EB4(arg0, 0x20000)) {
        o = (UnkObj *)func_802443F4(arg0);
        func_80243D90(arg0, 0x20000, 1);
        D_800AEDF0[arg0].unkB8 = 60;
        D_800AEDF0[arg0].unkB4 = (s32)func_80231274(0x4E, 0x11200000, 0xD0, o);
        M2C_FIELD(D_800AEDF0[arg0].unkB4, f32 *, 0x4C) = 0.0f;
        M2C_FIELD(D_800AEDF0[arg0].unkB4, f32 *, 0x50) = 200.0f;
        M2C_FIELD(D_800AEDF0[arg0].unkB4, f32 *, 0x54) = 0.0f;
    }
}

void func_80249D30(s32 arg0) {
    func_80244354(arg0, 0x20, 1);
    func_80243D90(arg0, 0x200000, 1);
    func_802444B8(arg0, 0x18);
}

void func_80249AD4(s32 arg0) {
    s32 cur = func_80243DDC();
    s32 flag = D_802AC980[cur];
    UnkStruct_800AEDF0 *e;

    switch (flag) {
        case 0x40000:
            if (--D_802AC9C8[cur] == 0) {
                func_80244354(cur, 0x80020, 0);
            }
            break;
        case 0x100000:
            e = &D_800AEDF0[cur];
            if (M2C_FIELD(e->unk28, f32 *, 0x68) == 0.0f) {
                func_80244354(cur, D_802AC980[cur] | 0x80020, 0);
                if (!FLAG_SET(e->unk10, 0x2000000)) {
                    func_80244354(cur, 0x10000, 0);
                }
            }
            break;
        case 0x400:
        case 0x4000:
        case 0x10000:
        case 0x4000000:
            func_80244354(cur, 0x80000, 0);
            if (!func_80244BA4(cur, 0x2000000)) {
                func_80244354(cur, 0x10000, 0);
            }
            break;
        default:
            if (!func_80244BA4(cur, flag)) {
                func_80244354(cur, D_802AC980[cur] | 0x80000, 0);
                if (!func_80244BA4(cur, 0x2000000)) {
                    func_80244354(cur, 0x10000, 0);
                }
            }
            break;
    }
}

void func_80249A30(s32 arg0) {
    s32 ipos[3];
    UnkObj *obj;

    obj = (UnkObj *)func_802443F4(arg0);
    func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, ipos, 2);
    if (func_8026E278(func_8026D7D8(ipos[0], ipos[1], ipos[2]))) {
        func_80244354(arg0, 0x10, 1);
    } else {
        func_80244354(arg0, 0x10, 0);
    }
}

void func_802498D4(s32 arg0, f32 arg1) {
    UnkObj *obj;
    s32 r;

    obj = (UnkObj *)func_802443F4(arg0);
    r = func_8022F4AC((s32)obj, 2, D_800AEDF0[arg0].unk4C);
    if (r != 0 && arg1 > 0.0f) {
        if (--D_802AC948[arg0] == 0) {
            func_80244354(arg0, 1, 0);
            if (r != 0 && func_802452AC(arg0, 0x11C0)) {
                if (obj->unk6C == 0.0f) {
                    func_80249810(arg0, r, 1);
                } else if (!func_80244BA4(arg0, 0x10000)) {
                    func_80247D74(arg0, 22.5f, 8.0f, 1, NULL);
                }
            }
        }
    } else {
        func_80244354(arg0, 1, 0);
    }
}

void func_80249810(s32 arg0, s32 arg1, s32 arg2) {
    if (!func_80244BA4(arg0, 0x8000)) {
        func_802444B8(arg0, 7);
    } else {
        func_802444B8(arg0, 0x10);
    }
    func_80244354(arg0, 0x120, 1);
    D_800AEDF0[arg0].unk38 &= ~0x100;
    D_800AEDF0[arg0].unk30 = arg1;
    D_800AEDF0[arg0].unkBC = arg2;
}

void func_802497D8(s32 arg0) {
    D_802AC948[arg0] = 2;
    func_80244354(arg0, 1, 1);
}

void func_80249648(s32 arg0, UnkObj *arg1, s32 arg2) {
    UnkStruct_800AEDF0 *sp20;
    UnkStruct_800AEDF0 *temp_t8;
    s32 temp_v0;
    s32 var_v1;

    if (!D_800AEDF0[arg0].unk10 && !D_800AEDF0[arg0].unk10) {}
    temp_t8 = &D_800AEDF0[arg0];
    sp20 = temp_t8;
    var_v1 = func_802452AC(arg0, 0x610400);
    if (var_v1 != 0) {
        if (!(D_802A01B0 & 2) && (arg2 & 0x1E00) && (M2C_FIELD(sp20->unk28, s32 *, 0x44) == 0)) {
            if ((D_802AC5D0 & 4) || (arg0 == 0)) {
                func_8026C660(0x196);
            }
            func_80247D74(arg0, 14.0f, 6.0f, 1, arg1);
            sp20->unk9C = arg2;
            func_80244354(arg0, 0x2108, 0);
            temp_v0 = sp20->unk9C;
            if (temp_v0 & 0x200) {
                func_8024946C(arg0, 0);
            } else if (temp_v0 & 0x400) {
                func_8024946C(arg0, 1);
            } else if (temp_v0 & 0x800) {
                func_8024946C(arg0, 2);
            } else if (temp_v0 & 0x1000) {
                func_80247C50(arg0);
            }
            sp20->unk9C = 0;
        }
    }
}

void func_8024946C(s32 arg0, s32 arg1) {
    UnkObj *o;
    f32 pos[3];
    s32 pad[2];
    UnkStruct_800AEDF0 *e = &D_800AEDF0[arg0];

    o = e->unk28;
    if (!func_80244BA4(arg0, 0x1000)) {
        switch (arg1) {
            case 0:
                D_802AC8D0[arg0] = 1200;
                D_802AC900[arg0] = 80;
                break;
            case 1:
                D_802AC8D0[arg0] = 600;
                D_802AC900[arg0] = 50;
                break;
            case 2:
                D_802AC8D0[arg0] = 300;
                D_802AC900[arg0] = 30;
                break;
        }
        func_80247848(arg0, 1);
        pos[0] = 0.0f;
        pos[1] = 80.0f;
        pos[2] = 0.0f;
        if (D_802AC8E8[arg0] == -1) {
            D_802AC8E8[arg0] = func_8028A7CC(5, pos, (s32)o);
        }
        func_8022979C((s32)o->unk40, 4, 12);
        func_8022979C((s32)o->unk40, 5, 13);
        D_802ACA30[arg0] = 0.0f;
    }
    func_80244354(arg0, 0x1C0, 0);
    func_80244354(arg0, 0x1020, 1);
    e->unk38 &= ~0x1000;
}

void func_8024891C(s32 arg0) {
    s32 other;
    s32 p18;
    s32 p68;
    s32 q18;
    s32 q68;
    s32 a;
    s32 b;
    Obj88 *obj;
    Obj88 *hit;
    Obj88 *oa;
    Obj88 *ob;
    f32 vec[3];
    f32 f;

    obj = (Obj88 *)func_802443F4(arg0);

    hit = (Obj88 *)func_8022F550((s32)obj, 1);
    if (hit != NULL) {
        other = func_802441AC(hit);
        if ((func_80243EB4(arg0, 0x10) || func_80243EB4(other, 0x10)) && !func_80243EB4(arg0, 0x200) &&
            !func_80243EB4(other, 0x200) && !func_80243EB4(arg0, 0x80) && !func_80243EB4(other, 0x80) &&
            !func_80243EB4(arg0, 0x40) && !func_80243EB4(other, 0x40)) {
            p18 = D_800AEDF0[arg0].unk18 & 0x404;
            q18 = D_800AEDF0[other].unk18 & 0x404;
            p68 = D_800AEDF0[arg0].unk68 & 0x3D;
            q68 = D_800AEDF0[other].unk68 & 0x3D;
            D_800AEDF0[arg0].unk68 &= ~0x3F;
            D_800AEDF0[arg0].unk18 &= ~0x404;
            D_800AEDF0[other].unk68 &= ~0x3F;
            D_800AEDF0[other].unk18 &= ~0x404;
            D_800AEDF0[other].unk18 |= p18;
            D_800AEDF0[other].unk68 |= p68;
            D_800AEDF0[arg0].unk18 |= q18;
            D_800AEDF0[arg0].unk68 |= q68;
            if (!func_80243EB4(arg0, 4) && !func_80243EB4(arg0, 1)) {
                if (p68 & 4) {
                    func_8024694C(arg0, 1, 0);
                }
                if (p68 & 1) {
                    func_8024694C(arg0, 2, 0);
                }
            }
            if (!func_80243EB4(arg0, 0x40)) {
                if (func_80243EB4(arg0, 4)) {
                    func_8024694C(arg0, 1, 1);
                }
                if (func_80243EB4(arg0, 1)) {
                    func_8024694C(arg0, 2, 1);
                }
                if (func_80243EB4(arg0, 8)) {
                    func_802488C0(arg0);
                }
                if (func_80243EB4(arg0, 0x20)) {
                    func_80248864(arg0);
                }
                if (D_800AEDF0[arg0].unk18 & 0x404) {
                    func_80246C3C(arg0, 3, 1);
                }
            }
            if (!func_80243EB4(other, 4) && !func_80243EB4(other, 1)) {
                if (q68 & 4) {
                    func_8024694C(other, 1, 0);
                }
                if (q68 & 1) {
                    func_8024694C(other, 2, 0);
                }
            }
            if (!func_80243EB4(other, 0x40)) {
                if (func_80243EB4(other, 4)) {
                    func_8024694C(other, 1, 1);
                }
                if (func_80243EB4(other, 1)) {
                    func_8024694C(other, 2, 1);
                }
                if (func_80243EB4(other, 8)) {
                    func_802488C0(other);
                }
                if (func_80243EB4(other, 0x20)) {
                    func_80248864(other);
                }
                if (D_800AEDF0[other].unk18 & 0x404) {
                    func_80246C3C(other, 3, 1);
                }
            }
            func_80243D90(arg0, 0x40, 1);
            D_800AEDF0[arg0].unk7C = 30;
            func_80243D90(other, 0x40, 1);
            D_800AEDF0[other].unk7C = 30;
        }
        a = -1;
        if (func_80243EB4(arg0, 0x200) && !func_80244BA4(arg0, 0x1000) && !func_80243EB4(other, 0x2000) &&
            !func_80243EB4(other, 0x200) && !func_80243EB4(other, 0x80) && D_800AEDF0[other].unk14 != 0 &&
            obj->unk44 == NULL && obj->unk6C == 0.0f) {
            a = other;
            b = arg0;
        }
        if (!func_80243EB4(arg0, 0x2000) && !func_80243EB4(arg0, 0x80) && !func_80243EB4(arg0, 0x200) &&
            D_800AEDF0[arg0].unk14 != 0 && func_802452AC(other, 0x401000) && func_80243EB4(other, 0x200) &&
            hit->unk44 == NULL && obj->unk6C == 0.0f) {
            a = arg0;
            b = other;
        }
        if (a != -1) {
            oa = (Obj88 *)func_802443F4(a);
            ob = (Obj88 *)func_802443F4(b);
            if (D_800AEDF0[a].unk2C != 0) {
                func_80244C30(a, 1);
            }
            if (D_800AEDF0[b].unk2C != 0) {
                func_80244C30(b, 1);
            }
            func_80243D90(a, 0x2000, 1);
            D_800AEDF0[a].unkA4 = b;
            func_80232AC8((s32)oa, (s32)ob);
            func_80231408(ob, 0x600000);
            D_800AEDF0[b].unkC0 = 70.0f;
            if (!func_80243EB4(a, 2)) {
                if (func_80243EB4(a, 4)) {
                    D_800AEDF0[b].unkC0 += 30.0f;
                }
                if (func_80243EB4(a, 1)) {
                    D_800AEDF0[b].unkC0 -= 40.0f;
                }
            } else {
                f = D_800AEDF0[a].unk74;
                if (func_80243EB4(a, 4)) {
                    if (D_800AEDF0[a].unk6C > 0.0f) {
                        D_800AEDF0[b].unkC0 += 6.0f * f;
                    }
                    if (D_800AEDF0[a].unk6C < 0.0f) {
                        D_800AEDF0[b].unkC0 += 6.0f * (4.0f - f);
                    }
                }
                if (func_80243EB4(a, 1)) {
                    if (D_800AEDF0[a].unk6C > 0.0f) {
                        D_800AEDF0[b].unkC0 += -8.0f * f;
                    }
                    if (D_800AEDF0[a].unk6C < 0.0f) {
                        D_800AEDF0[b].unkC0 = (4.0f - f) * -8.0f;
                    }
                }
            }
            D_802ACE90[b] = 60.0f;
            vec[1] = 60.0f;
            vec[2] = D_800AEDF0[b].unkC0;
            if (func_80244BA4(a, 0x40)) {
                vec[1] = 37.0f;
            }
            vec[0] = 180.0f;
            func_8022FEAC(vec, ob->unk4C);
            ob->unk70 = 0.0f;
            func_802444B8(b, 0x12);
            D_802AC998[a] = 600;
            D_802AC9B0[a] = 50;
            D_800AEDF0[a].unkA8 = b;
            func_80244354(b, 2, 0);
        }
    }
}

void func_802488C0(s32 arg0) {
    func_80243D90(arg0, 0x18, 1);
    D_800AEDF0[arg0].unk78 = 0x4B0;
    func_80246C3C(arg0, 3, 1);
}

void func_80248864(s32 arg0) {
    func_80243D90(arg0, 0x30, 1);
    D_800AEDF0[arg0].unk78 = 0x4B0;
    func_80246C3C(arg0, 3, 1);
}

void func_8024878C(s32 arg0) {
    func_80244354(arg0, 2, 0);
    if (!func_80244BA4(arg0, 0x1000)) {
        func_80244354(arg0, 0x20, 0);
        if (!func_802452AC(arg0, 0x20C0)) {
            if (!func_80244BA4(arg0, 0x8000)) {
                func_802444B8(arg0, 0);
            } else {
                func_802444B8(arg0, 0xC);
            }
        }
    }
}

void func_8024857C(s32 arg0) {
    s32 pad;
    Cell5_5E3F0 c;
    UnkObj *obj;
    s32 r;

    obj = (UnkObj *)func_802443F4(arg0);
    func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, &c, 2);
    if (c.h == 0.0f) {
        r = func_8026D7D8(c.x, c.y, c.z) & 0xF;
    } else {
        r = 1;
    }
    switch (r) {
    case 2:
        if (!(D_802AC8A8[arg0] & 1)) {
            D_802AC8A8[arg0] = 1;
            func_80243824(0x50);
            if (func_80244BA4(arg0, 0x1000)) {
                func_80247C50(arg0);
            }
        }
        break;
    case 9:
        if (!func_80244BA4(arg0, 0x10000) && !(D_802AC8A8[arg0] & 2)) {
            func_80248148(arg0, 4);
        }
        break;
    case 10:
        if (!(D_802AC8A8[arg0] & 4)) {
            D_802AC8A8[arg0] = 4;
            func_80243824(0x52);
        }
        break;
    case 11:
        if (!(D_802AC8A8[arg0] & 8)) {
            D_802AC8A8[arg0] = 8;
            func_80243824(0x53);
        }
        break;
    default:
        if (D_802AC8A8[arg0] != 0) {
            D_802AC8A8[arg0] = 0;
        }
        break;
    }
}

void func_80248148(s32 arg0, s32 arg1) {
    Obj88 *obj;
    s32 link;
    s32 pad;
    s32 other;
    s32 pad2[5];

    if (D_800AEDF0[arg0].unk24 != 3) {
        if (arg1 == 3 || arg1 == 5) {
            D_800AEDF0[arg0].unk14 = 0;
        } else {
            D_800AEDF0[arg0].unk14--;
        }
        func_802444B8(arg0, 0);
        if (!D_800AEDF0[arg0].unk28 && !D_800AEDF0[arg0].unk28) {}
        if (!D_802ACF60 && !D_802ACF60) {}
        obj = (Obj88 *)D_800AEDF0[arg0].unk28;
        func_80244354(arg0, 0x21C0, 0);
        link = D_802AC5D0 & 4;
        if (!link && !link) {}
        func_80270770((s16)arg0, 1);
        D_800AEDF0[arg0].unk2C = 0;
        if (D_802AC8E8[arg0] != -1) {
            func_8028A4E0(D_802AC8E8[arg0]);
            D_802AC8E8[arg0] = -1;
            func_8022979C((s32)obj->unk40, 4, 4);
            func_8022979C((s32)obj->unk40, 5, 5);
        }
        func_80247848(arg0, 0);
        if (!arg1 && !arg1) {}
        if (D_800AEDF0[arg0].unk14 == 0) {
            if (func_8023A870(arg0, arg1)) {
                if (link) {
                    if (func_80243EB4(arg0, 0x2000)) {
                        func_80247F90(arg0);
                    }
                    if (obj->unk44 != NULL) {
                        other = func_802441AC(obj->unk44);
                        func_80244C30(other, 0);
                        func_802444B8(other, 0);
                        func_80243D90(other, 0x2000, 0);
                        func_802313DC(obj, 0x600000);
                    }
                    if (!D_800AEDF0[arg0].unk2C && !D_800AEDF0[arg0].unk2C) {}
                    if (!func_80243EB4(arg0, 0x200)) {
                        func_8027B0BC((s16)arg0);
                    }
                }
                func_802313DC(obj, 1);
                D_800AEDF0[arg0].unk24 = 3;
                D_800AEDF0[arg0].unk10 = (obj->unk6C > 0.0f) ? (D_800AEDF0[arg0].unk10 & 0x400000) : 0;
            } else {
                func_80244354(arg0, 0x161, 0);
                D_800AEDF0[arg0].unk14 = 1;
            }
        } else {
            D_800AEDF0[arg0].unk2C = 0;
            D_802ACF60 = func_8023A840();
            if (D_802ACF60[4] != 0 && !link) {
                func_8028A81C(6, obj->unk40->unk10, obj->unk40->unk14 + 200.0f, obj->unk40->unk18, 0);
            } else {
                func_8027B39C(4, (s16)arg0);
            }
            func_80247CD0(arg0, 3);
            func_8026C660(0x1D);
            if (arg0 == 1) {
                switch ((u32)D_802ACF60[1]) {
                case 0:
                case 5:
                    func_8026C660(0x1CD);
                    break;
                case 1:
                    func_8026C660(0x1B4);
                    break;
                case 2:
                    func_8026C660(0x1B7);
                    break;
                case 3:
                    func_8026C660(0x1BA);
                    break;
                case 4:
                    func_8026C660(0x1C5);
                    break;
                }
            }
            if (arg0 == 2 && D_802ACF60[1] == 5) {
                func_8026C660(0x1BA);
            }
            if (obj->unk44 != NULL) {
                other = func_802441AC(obj->unk44);
                func_80244C30(other, 1);
                func_802444B8(other, 0);
                func_80243D90(other, 0x2000, 0);
                func_802313DC(obj, 0x600000);
            }
        }
        func_80247C50(arg0);
    }
}

void func_80247F90(s32 arg0) {
    Obj88 *other;
    UnkObj *self;
    f32 vec[3];
    UnkStruct_800AEDF0 *p;

    p = &D_800AEDF0[arg0];
    if (p->unk28) {}
    self = p->unk28;
    other = (Obj88 *)func_802443F4(p->unkA8);
    vec[2] = p->unkC0 + 100.0f;
    vec[1] = 60.0f;
    vec[0] = 180.0f;
    func_8022FEAC(vec, other->unk4C);
    func_80231434(other);
    func_80232AA8((s32)other);
    func_802313DC(other, 0x600000);
    if (func_80244BA4(arg0, 0x80)) {
        func_80244C30(arg0, 0);
    }
    if (!func_80244BA4(arg0, 0x1000)) {
        func_80244354(arg0, 0x20, 0);
    }
    func_80243D90(arg0, 0x2000, 0);
    if (func_80244BA4(arg0, 0x80)) {
        func_802444B8(p->unkA8, 0xC);
    } else {
        func_802444B8(p->unkA8, 0);
    }
    other->unk40->unk14 += 5.0f;
    func_80247D74(p->unkA8, 22.5f, 8.0f, 1, self);
    other->unk70 = 1.6333334f;
    func_80244354(arg0, 0x21C0, 0);
}

void func_80247D74(s32 arg0, f32 arg1, f32 arg2, s32 arg3, UnkObj *arg4) {
    UnkObj *obj;
    s32 pad;
    f32 a[3];
    f32 b[3];
    s32 pad2[2];
    f32 dir;
    s32 pad3[3];
    f32 angle;
    UnkStruct_800AEDF0 *p;

    p = &D_800AEDF0[arg0];
    obj = p->unk28;
    ((Obj88 *)obj)->unk68 = arg1;
    D_802ACA44 = arg2;
    D_802AC8C8 = arg3;
    if (arg4 != NULL) {
        if (arg3 == 1) {
            func_8022F808(obj, a);
            func_8022F808(arg4, b);
            b[1] = a[1];
            if (a[0] == b[0] && a[2] == b[2]) {
                angle = -1.0f;
            } else {
                func_8022FF58(a, b, &dir);
                angle = (dir + 180.0f) - 360.0f * (dir >= 180.0f);
                obj->unk40->unk20 = (angle + 180.0f) - 360.0f * (angle >= 180.0f);
            }
        } else {
            angle = (obj->unk40->unk20 + 180.0f) - 360.0f * (obj->unk40->unk20 >= 180.0f);
        }
    } else {
        angle = obj->unk40->unk20;
    if (!arg4 && !arg4) {}
    }
    p->unkA0 = func_80243F50(angle);
    if (arg3 == 1 && arg4 != NULL) {
        func_802444B8(arg0, 0xB);
        func_80244354(arg0, 0xA0C8, 0);
        if (!obj && !obj) {}
        func_80270770((s16)arg0, 1);
        p->unk2C = 0;
        p->unk2C = 0;
    }
    func_80244354(arg0, 0x22, 1);
}

void func_80247CD0(s32 arg0, s32 arg1) {
    UnkObj *o;

    D_802AC930[arg0] = arg1;
    func_80244354(arg0, 0x30020, 1);
    o = func_802443F4(arg0);
    D_802AC918[arg0] = 0;
    D_802ACA48[arg0] = o->unk40->unk20;
    D_802ACA60[arg0] = D_802ACA48[arg0];
    func_80231408(o, 0x40000);
}

void func_80247C50(s32 arg0) {
    if (func_80244BA4(arg0, 0x1000)) {
        func_80247A54(arg0, func_8022F4AC((s32)func_802443F4(arg0), 2, D_800AEDF0[arg0].unk4C), 0, 1);
    }
}

void func_80247A54(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Tbl3_5E3F0 tbl;
    s32 pad;
    UnkObj *obj;
    UnkStruct_800AEDF0 *p;
    s32 other;

    tbl = *(Tbl3_5E3F0 *)D_802A0D88;
    p = &D_800AEDF0[arg0];
    obj = (UnkObj *)func_802443F4(arg0);
    if (func_80244BA4(arg0, 0x200000)) {
        other = func_802441AC(M2C_FIELD(obj, void **, 0x44));
        func_80270770((s16)other, 1);
        D_800AEDF0[other].unk2C = 0;
        p->unk2C = 0;
    }
    if (arg3 != 0 && !(D_802AC5D0 & 0x10) && ((D_802AC5D0 & 4) || arg0 == 0)) {
        func_802479F0(tbl.v);
    }
    func_80244354(arg0, 0x1020, 0);
    func_802444B8(arg0, 0);
    if (arg2 != 0) {
        func_8024796C(arg0, arg2);
    }
    if (arg1 != 0) {
        p->unk4C = arg1;
        func_80244354(arg0, 0x200, 1);
    }
    if (D_802AC8E8[arg0] != -1) {
        if (!p->unk2C && !p->unk2C) {}
        func_8028A4E0(D_802AC8E8[arg0]);
        D_802AC8E8[arg0] = -1;
    }
    func_8022979C((s32)obj->unk40, 4, 4);
    func_8022979C((s32)obj->unk40, 5, 5);
    func_80247848(arg0, 0);
}

void func_802479F0(s32 *arg0) {
    s32 *var_v0;
    s32 var_v1;

    var_v1 = 0;
    if (*arg0 != -1) {
        var_v0 = arg0;
        do {
            var_v1 += 1;
            var_v0 += 1;
        } while (var_v0[0] != -1);
    }
    func_8026C660(arg0[func_80234248(var_v1 - 1)]);
}

void func_8024796C(s32 arg0, s32 arg1) {
    void *sp1C;

    sp1C = ((UnkObj *)func_802443F4(arg0));
    func_80244354(arg0, 0x108, 0);
    func_80244354(arg0, 0x10000, 1);
    D_802AC918[arg0] = arg1;
    func_80231408(sp1C, 0x40000);
}

void func_80247928(s32 arg0, s32 arg1) {
    D_800AEDF0[arg0].unk4C = arg1;
    func_80244354(arg0, 0x200, 1);
}

void func_80247848(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        if (D_800AEDF0[arg0].unk54 == 0) {
            D_800AEDF0[arg0].unk54++;
            if (++D_802AC9DC == 1) {
                D_802AC9E0 = func_8026C660(0x21);
            }
        }
    } else {
        if (D_800AEDF0[arg0].unk54 != 0) {
            D_800AEDF0[arg0].unk54--;
            if (--D_802AC9DC == 0) {
                func_8026BE80(D_802AC9E0);
                D_802AC9E0 = -1;
            }
        }
    }
}

void func_80247614() {
    if (--D_802AC9EC == 0) {
        if (func_80243E18(0x20)) {
            func_80246F00(0x20, 0);
        }
        if (func_80243E18(0x40)) {
            func_80246F00(0x40, 0);
        }
        if (func_80243E18(0x10)) {
            func_80246F00(0x10, 0);
        }
        if (func_80243E18(0x80)) {
            func_80246F00(0x80, 0);
        }
        if (func_80243E18(4)) {
            func_80246F00(4, 0);
        }
        if (func_80243E18(2)) {
            func_80246F00(2, 0);
        }
        D_802AC9EC = 0;
        D_802AC9E8 = 0;
    }
    if (func_80243E18(0x40)) {
        func_80246808();
    }
    if (func_80243E18(0x10) && --D_802AC9F0 == 0) {
        func_80246078();
    }
    if (func_80243E18(0x80)) {
        func_80246018();
    }
    if (func_80243E18(4)) {
        func_80245FD4();
    }
}

void func_80246F00(s32 arg0, s32 arg1) {
    s32 pad0;
    s32 x;
    s32 pad[3];
    s32 flags;
    s32 hit;
    s32 pad1;
    f32 pos[3];
    UnkStruct_800AEDF0 *e;
    s32 i;
    s32 r;
    UnkObj *obj;

    if (arg1 == 0 || !func_80243E18(1)) {
        switch (arg0) {
        case 0x20:
            if (arg1 != 0) {
                for (i = 0; i < 4; i++) {
                    e = &D_800AEDF0[i];
                    if (e->unk24 == 1 || e->unk24 == 2) {
                        e->unk94 = e->unk18;
                        e->unk98 = e->unk20;
                        e->unk18 |= 0x200;
                        e->unk18 |= 1;
                        func_80278E84((s16)i, 8);
                    }
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (D_800AEDF0[i].unk24 == 1 || D_800AEDF0[i].unk24 == 2) {
                        D_800AEDF0[i].unk18 = D_800AEDF0[i].unk94;
                        D_800AEDF0[i].unk20 = D_800AEDF0[i].unk98;
                    }
                }
            }
            break;
        case 0x40:
            if (arg1 != 0) {
                D_802ACEA4 = 0.0f;
                D_802ACEA8 = 0.0f;
                D_802ACEAC = 0.0f;
                func_8024663C();
            } else {
                func_80282144(0, 0, 0, 0.0f);
            }
            break;
        case 0x10:
            if (arg1 != 0) {
                func_80246078();
            }
            break;
        case 0x80:
            if (arg1 != 0) {
                func_80238A10(func_802500D4, 0, 0, 0, 0x130);
                D_802AC9F0 = 0xB4;
            }
            break;
        case 8:
            for (i = 0; i < 4; i++) {
                e = &D_800AEDF0[i];
                if (e->unk14 != 0 && (e->unk24 == 1 || e->unk24 == 2)) {
                    if (!func_80243EF0(i)) {
                        func_80246D74(i);
                        func_8024694C(i, 1, arg1);
                    }
                }
            }
            D_802AC9EC = 0;
            D_802AC9E8 = 0;
            break;
        case 4:
            if (arg1 != 0) {
                x = func_80234248(13) + 17;
                func_8026E338(x, func_80234248(D_800B15D8 - 1), func_80234248(10) + 10, pos, 0);
                D_802ACF58 = func_802867E4(3, pos[0], pos[1], pos[2]);
                if (D_802ACF58 != NULL) {
                    obj = *D_802ACF58;
                    flags = M2C_FIELD(obj, s32 *, 8);
                    while (1) {
                        (*D_802ACF58)->unk40->unk14 = func_8026E938(obj->unk40);
                        func_802313DC(*D_802ACF58, flags);
                        func_80231408(*D_802ACF58, 0x10);
                        hit = func_80232D18(*D_802ACF58, 0x10);
                        obj = *D_802ACF58;
                        r = func_8026DF74(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
                        if (hit) {
                            M2C_FIELD(*D_802ACF58, s32 *, 0x10) = 0;
                            M2C_FIELD(*D_802ACF58, s32 *, 0x14) = 0;
                            M2C_FIELD(*D_802ACF58, s32 *, 0x24) = 0;
                        }
                        if (!(r & 0x2000) && !(r & 0x60) && (r & 0xF) == 1) {
                            obj = *D_802ACF58;
                            if (obj->unk40->unk14 != 20000.0f && !hit) {
                                func_80231408(obj, flags | 0x80000);
                                obj = *D_802ACF58;
                                func_8022F808(obj, (f32 *)obj->unk58);
                                func_8026C660(0x1EA);
                                break;
                            }
                        }
                        x = func_80234248(13) + 17;
                        func_8026E338(x, func_80234248(D_800B15D8 - 1), func_80234248(10) + 10, pos, 0);
                        (*D_802ACF58)->unk40->unk10 = pos[0];
                        (*D_802ACF58)->unk40->unk14 = pos[1];
                        (*D_802ACF58)->unk40->unk18 = pos[2];
                        obj = *D_802ACF58;
                    }
                } else {
                    arg0 = 0x10;
                    func_80246078();
                }
            } else if (!(func_802871D0((s32)D_802ACF58) & 3)) {
                func_8022F808(*D_802ACF58, pos);
                pos[1] += 100.0f;
                func_8028A7CC(1, pos, 0);
                (*D_802ACF58)->unk40->unk14 = func_8026E8B8();
                func_802313DC(*D_802ACF58, 0x01000000);
                obj = *D_802ACF58;
                func_8022F808(obj, (f32 *)obj->unk58);
            }
            break;
        }
        func_80245FA0(arg0, arg1);
    }
    if (arg1 != 0) {
        D_802AC9EC = 0x708;
    }
    func_80245FA0(1, arg1);
    if (arg0 == 8) {
        D_802AC9EC = 0;
        D_802AC9E8 = 0;
    }
}

void func_80246D74(s32 arg0) {
    UnkObj *obj;
    s32 id = arg0;
    UnkStruct_800AEDF0 *p = &D_800AEDF0[id];

    obj = (UnkObj *)func_802443F4(id);
    if (func_80243EB4(id, 4)) {
        func_80270770(id, 1);
        p->unk2C = 0;
        func_8024694C(id, 1, 0);
    }
    if (func_80243EB4(id, 1)) {
        func_80270770(id, 1);
        p->unk2C = 0;
        func_8024694C(id, 2, 0);
    }
    if (func_80243EB4(id, 0x80)) {
        func_802313DC(obj, 0x40);
    }
    if (func_80243EB4(id, 0x100)) {
        func_80246C3C(id, 0, 0);
    }
    func_80243D90(id, 0xB9, 0);
    if (!func_80243E18(1)) {
        func_80243D90(id, 4, 0);
    }
    p->unk18 &= ~0x404;
}

void func_80246C3C(s32 arg0, s32 arg1, s32 arg2) {
    UnkObj *sp4C;
    UnkStruct_800AEDF0 *sp20;
    UnkObj *temp_a3;
    UnkStruct_800AEDF0 *temp_v1;
    s32 var_a0;
    s32 var_a0_2;

    temp_v1 = &D_800AEDF0[arg0];
    temp_a3 = temp_v1->unk28;
    if (arg2 != 0) {
        sp20 = temp_v1;
        sp4C = temp_a3;
        func_80243D90(0x100, 1, (s32) temp_a3);
        temp_v1->unk8C = 0.0f;
        temp_v1->unk88 = 0.2f;
        temp_v1->unk84 = arg1;
        func_8029279C(sp4C->unk40, 0, 0, 0, 0.0f);
        var_a0 = 0;
        temp_v1->unk90 = 0x3C;
        if ((temp_v1->unk68 & 0x80) == 0x80) {
            var_a0 = 1;
        }
        if (var_a0 != 0) {
            temp_v1->unk90 = 0x4B0;
        }
        if (temp_v1->unk18 & 0x404) {
            sp20 = temp_v1;
            func_80243D90(arg0, 0x10, 1);
            temp_v1->unk78 = 0x4B0;
        }
    } else {
        var_a0_2 = func_80243EB4(arg0, 0x100);
        if (var_a0_2 != 0) {
            func_802926EC(temp_a3->unk40);
            func_80243D90(arg0, 0x100, 0);
        }
    }
}

void func_8024694C(s32 arg0, s32 arg1, s32 arg2) {
    s32 other;
    UnkObj *obj;
    UnkStruct_800AEDF0 *q;
    s32 pad[5];

    if (func_80243EB4(arg0, 0x2000)) {
        other = D_800AEDF0[arg0].unkA8;
    }
    if (arg1 == 2) {
        if (arg2 != 0) {
            D_800AEDF0[arg0].unk6C = -0.1f;
            D_800AEDF0[arg0].unk70 = 0.5f;
            if (func_80243EB4(arg0, 0x2000)) {
                D_800AEDF0[other].unkC4 = -8.0f;
            }
            func_80243D90(arg0, 0x11, arg2);
        } else {
            D_800AEDF0[arg0].unk6C = 0.1f;
            D_800AEDF0[arg0].unk70 = 1.0f;
            if (func_80243EB4(arg0, 0x2000)) {
                D_800AEDF0[other].unkC4 = 8.0f;
            }
        }
    } else if (arg2 != 0) {
        D_800AEDF0[arg0].unk6C = 0.1f;
        D_800AEDF0[arg0].unk70 = 1.5f;
        if (func_80243EB4(arg0, 0x2000)) {
            D_800AEDF0[other].unkC4 = 6.0f;
        }
        func_80243D90(arg0, 0x14, arg2);
    } else {
        D_800AEDF0[arg0].unk6C = -0.1f;
        D_800AEDF0[arg0].unk70 = 1.0f;
        if (func_80243EB4(arg0, 0x2000)) {
            D_800AEDF0[other].unkC4 = -6.0f;
        }
    }
    if (arg2 != 0) {
        if (D_802AC9E8 == 0) {
            D_800AEDF0[arg0].unk78 = 1200;
        } else {
            D_800AEDF0[arg0].unk78 = 1800;
        }
    }
    if (func_80243EB4(arg0, 0x2000)) {
        if (D_800AEDF0[arg0].unk28) {}
        obj = D_800AEDF0[arg0].unk28;
        if (!obj && !obj) {}
        q = &D_800AEDF0[other];
        q->unkC0 = 70.0f;
        if (obj->unk40->unk28 > 1.0f) {
            q->unkC0 += 30.0f;
        }
        if (obj->unk40->unk28 < 1.0f) {
            q->unkC0 -= 40.0f;
        }
    }
    func_80243D90(arg0, 2, 1);
    func_80270770((s16)arg0, 1);
    D_800AEDF0[arg0].unk2C = 0;
    D_800AEDF0[arg0].unk74 = 0;
}

void func_80246938() {
    D_802AC9EC = 0;
    D_802AC9E8 = 0;
}

void func_80246808() {
    func_80282144((s32)D_802ACEA4, (s32)D_802ACEA8, (s32)D_802ACEAC, 50.0f);
    D_802ACEA4 += D_802ACEBC;
    D_802ACEA8 += D_802ACEC0;
    D_802ACEAC += D_802ACEC4;
    if (--D_802AC9F0 == 0) {
        D_802ACEA4 = D_802ACEB0;
        D_802ACEA8 = D_802ACEB4;
        D_802ACEAC = D_802ACEB8;
        func_8024663C();
    }
}

void func_8024663C() {
    s32 r;
    s32 done;

    do {
        done = 0;
        r = func_80234248(7);
        D_802ACEB8 = (r & 1) * 255.0f;
        D_802ACEB0 = ((r & 2) >> 1) * 255.0f;
        D_802ACEB4 = ((r & 4) >> 2) * 255.0f;
        func_80234248(2);
        D_802AC9F0 = 15;
        D_802ACEBC = (D_802ACEB0 - D_802ACEA4) / (f32)D_802AC9F0;
        D_802ACEC0 = (D_802ACEB4 - D_802ACEA8) / (f32)D_802AC9F0;
        D_802ACEC4 = (D_802ACEB8 - D_802ACEAC) / (f32)D_802AC9F0;
        if (D_802ACEBC != 0.0f || D_802ACEC0 != 0.0f || D_802ACEC4 != 0.0f) {
            done = 1;
        }
    } while (!done);
}

void func_80246604() {
    if (--D_802AC9F0 == 0) {
        func_80246078();
    }
}

void func_80246078() {
    s32 pad0[2];
    s32 used[5];
    s32 c[4];
    s32 pad1;
    s32 flags[5];
    f32 x[5];
    f32 y[5];
    f32 z[5];
    f32 r[5];
    f32 pos[3];
    UnkStruct_800AEDF0 *p;
    UnkObj *obj;
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 pad2[21];

    c[0] = 0;
    c[3] = 0;
    for (i = 0; i < 4; i++) {
        p = &D_800AEDF0[i];
        if ((p->unk24 == 1 || p->unk24 == 2) && p->unk14 != 0 && !func_80244BA4(i, 0x1000) && !func_80243EF0(i)) {
            if (!j && !j) {}
            obj = p->unk28;
            x[c[3]] = obj->unk40->unk10;
            y[c[3]] = obj->unk40->unk14;
            z[c[3]] = obj->unk40->unk18;
            used[c[3]] = 0;
            r[c[3]] = M2C_FIELD(obj->unk40, f32 *, 0x20);
            flags[i] = M2C_FIELD(obj, s32 *, 8);
            func_802313DC(obj, flags[i]);
            func_80231408(obj, 0x01000010);
            c[3]++;
        }
    }
    if (!p && !p) {}
    for (i = 0; i < 4; i++) {
        p = &D_800AEDF0[i];
        k = 0;
        if ((p->unk24 == 1 || p->unk24 == 2) && p->unk14 != 0 && !func_80244BA4(i, 0x1000) && !func_80243EF0(i)) {
            do {
                if (!c[3] && !c[3]) {}
                j = func_80234248(c[3] - 1);
                if (used[j] == 0) {
                    obj = p->unk28;
                    if (!obj && !obj) {}
                    obj->unk40->unk10 = x[j];
                    obj->unk40->unk14 = y[j];
                    obj->unk40->unk18 = z[j];
                    M2C_FIELD(obj->unk40, f32 *, 0x20) = r[j];
                    if (p->unk2C != 0) {
                        func_80231434((void *)p->unk2C);
                    }
                    if (func_80244BA4(i, 0x2000)) {
                        func_80231434(D_800AEDF0[p->unkA8].unk28);
                    }
                    k++;
                    used[j]++;
                }
            } while (k == 0);
        }
    }
    for (i = 0; i < 4; i++) {
        p = &D_800AEDF0[i];
        if ((p->unk24 == 1 || p->unk24 == 2) && p->unk14 != 0 && !func_80244BA4(i, 0x1000) && !func_80243EF0(i)) {
            if (!j && !j) {}
            if (func_80232D18(p->unk28, 0x10) != 0) {
                c[0]++;
            }
            if (p->unk2C != 0 && func_80232D18((void *)p->unk2C, 0x10) != 0) {
                c[0]++;
            }
            if (func_80243EB4(i, 0x2000) && func_80232D18(D_800AEDF0[p->unkA8].unk28, 0x10) != 0) {
                c[0]++;
            }
        }
    }
    m = 0;
    for (i = 0; i != 4; i++) {
        p = &D_800AEDF0[i];
        obj = p->unk28;
        if ((p->unk24 == 1 || p->unk24 == 2) && p->unk14 != 0 && !func_80244BA4(i, 0x1000) && !func_80243EF0(i)) {
            if (c[0] == 0) {
                func_8022F808(obj, pos);
                pos[1] += 50.0f;
                func_8028A7CC(2, pos, 0);
                func_8022F808(obj, (f32 *)((u8 *)obj + 0x58));
            } else {
                obj->unk40->unk10 = x[m];
                obj->unk40->unk14 = y[m];
                obj->unk40->unk18 = z[m];
                M2C_FIELD(obj->unk40, f32 *, 0x20) = r[m];
                m++;
            }
            func_80231408(obj, flags[i]);
        }
    }
    D_802AC9F0 = 300;
}

void func_80246018() {
    if (--D_802AC9F0 == 0) {
        func_80238A10(func_802500D4, 0, 0, 0, 0x130);
        D_802AC9F0 = 180;
    }
}

void func_80245FD4() {
    if (func_802871D0(D_802ACF58) & 3) {
        D_802AC9EC = 0;
        func_80245FA0(5, 0);
    }
}

void func_80245FA0(s32 arg0, s32 arg1) {
    s32 v;

    if (!D_800AEDF0[arg0].unk10) {}
    v = D_802AC9E8;

    if (arg1 == 1) {
        v |= arg0;
    } else {
        v &= arg0 ^ -1;
    }
    D_802AC9E8 = v;
}

void func_80245F74(s32 arg0) {
    func_80245E2C(func_80243DDC(), arg0);
}

void func_80245E2C(s32 arg0, s32 arg1) {
    Tbl8i_5E3F0 keys;
    Tbl8f_5E3F0 vals;
    UnkStruct_800AEDF0 *p;
    s32 i;
    f32 v;

    keys = *(Tbl8i_5E3F0 *)D_802A0E18;
    vals = *(Tbl8f_5E3F0 *)D_802A0E38;
    v = -1.0f;
    for (i = 0; i < 8 && v == -1.0f; i++) {
        if (arg1 == keys.v[i]) {
            v = vals.v[i];
        }
    }
    if (v != -1.0f) {
        p = &D_800AEDF0[arg0];
        p->unkC = v;
        if (arg0 != -1) {
            M2C_FIELD(p->unk28->unk40, f32 *, 0x20) = v;
        }
    }
}

void func_80245E1C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {

}

void func_80245DFC() {
    func_80245CDC();
}

void func_80245CDC() {
    s32 i;
    s32 v;

    D_802AC894 = 0;
    D_802ACF04 = malloc(0x1000);
    D_802AC898 = func_80238A10(func_8024FFF0, 0, (s32) D_802ACF04, 0x1000, 0x70);
    for (i = 0; i < 5; i++) {
        if (D_800AEDF0[i].unk24 != 0) {
            D_800AEDF0[i].unk68 = 0;
            func_802459BC(i);
        }
    }
    func_80237664();
    func_802362D4(0x1F);
    D_802AC8BC = 0;
    D_802ACA24 = 2.0f;
    D_802AC95C = 3;
    D_802AC97C = 1;
    D_802AC9DC = 0;
    D_802AC9E0 = -1;
    D_802AC9E8 = 0;
    v = D_802AC5D0;
    if (v & 4) {
        func_80287008(3, 0x1C, 0xD2);
    }
}

void func_802459BC(s32 arg0) {
    s32 pad;
    s32 m;
    UnkStruct_800AEDF0 *p;
    UnkObj *v;
    Obj88 *obj;
    s32 i;

    v = func_80231274(0x49, 0x0D000011, 0x70, NULL);
    p = &D_800AEDF0[arg0];
    p->unk28 = v;
    v->unk40->unk10 = p->unk0;
    p->unk28->unk40->unk14 = p->unk4;
    p->unk28->unk40->unk18 = p->unk8;
    p->unk28->unk40->unk20 = p->unkC;
    M2C_FIELD(p->unk28, s32 *, 0x30) = 1;
    M2C_FIELD(p->unk28, f32 *, 0x34) = 30.0f;
    M2C_FIELD(p->unk28, f32 *, 0x38) = 51.0f;
    p->unk28->unk6C = 0.0f;
    M2C_FIELD(p->unk28, f32 *, 0x70) = 1.6333334f;
    M2C_FIELD(p->unk28, f32 *, 0x68) = 0.0f;
    M2C_FIELD(p->unk28, s32 *, 0xC) = 0x1FF0;
    func_80229F74((s32)p->unk28->unk40, 2);
    func_8022984C((s32)p->unk28->unk40, 12);
    if (func_80243EB4(arg0, 0x200)) {
        obj = (Obj88 *)p->unk28;
        func_8022979C((s32)obj->unk40, 4, 4);
        func_8022979C((s32)obj->unk40, 5, 5);
        func_80231408(obj, 0x80000);
        M2C_FIELD(obj->unk40, s16 *, 0x36) = 0x80;
        obj->unk40->unkC |= 0x1000;
    }
    for (i = 0; i < 12; i++) {
        switch (arg0) {
        case 0:
            m = 0x4A;
            break;
        case 1:
            m = 0x4B;
            break;
        case 2:
            m = 0x4C;
            break;
        case 3:
            m = 0x4D;
            break;
        }
        func_802297B8((s32)p->unk28->unk40, m, i, i);
    }
    p->unkB0 = func_802311E8(p->unk28);
    D_802AC8A8[arg0] = 1;
    D_802AC89C = 0;
    D_802AC8A0 = 0;
    func_802444B8(arg0, 0);
    D_802AC8E8[arg0] = -1;
    D_802ACA78[arg0] = 0.0f;
    p->unk10 = 0;
    p->unk68 &= 0x200;
    p->unk2C = 0;
    p->unk48 = 1;
    p->unk4C = 0;
    p->unk50 = 0;
    p->unk54 = 0;
    p->unk80 = 3;
    p->unk9C = 0;
    p->unkA4 = 0;
    p->unkA8 = 0;
    p->unkB4 = 0;
    p->unk38 = 0;
    p->unk18 &= ~0x404;
    p->unk74 = 0;
    p->unk40 = 0;
    D_802ACF08[arg0].unkC = 0;
    D_802ACF08[arg0].unkE = 0;
    D_802ACF08[arg0].unk8 = 0.0f;
    D_802ACF08[arg0].unk4 = 0.0f;
    D_802ACF08[arg0].unk0 = 0.0f;
}

void func_80245868() {
    s32 i;

    func_802362B8(0x7F);
    D_802AC9F4 = 0;
    for (i = 0; i < 5; i++) {
        if (D_800AEDF0[i].unk24 != 0 && func_802443F4(i) != 0 && *(s32 *)((u8 *)D_800AEDF0[i].unk28 + 0x44) != 0) {
            func_80232AA8((s32) D_800AEDF0[i].unk28);
        }
    }
    for (i = 0; i < 5; i++) {
        if (D_800AEDF0[i].unk24 != 0 && func_802443F4(i) != 0) {
            func_8022FC90(D_800AEDF0[i].unk28);
            D_800AEDF0[i].unk28 = NULL;
            D_802AC894 = -1;
            D_800AEDF0[i].unkC = 0.0f;
        }
    }
    if (D_802AC898 != 0) {
        func_80238EA8(D_802AC898);
        D_802AC898 = 0;
    }
    if (D_802ACF04 != NULL) {
        free(D_802ACF04);
        D_802ACF04 = NULL;
    }
}

void func_8024585C(s32 arg0) {
    D_802AC894 = arg0;
}

void func_802457D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 id = func_80243DDC();

    func_8024557C(D_802ACEC8[id]);
    func_80245430(D_802ACEC8[id], arg0, arg1, arg2, arg3);
}

s32 func_802456FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 id = func_80243DDC();

    func_8024557C(D_802ACEC8[id]);
    return func_80245690(D_802ACEC8[id], arg0, arg1, arg2, arg3, arg4);
}

s32 func_80245690(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 ret = 0;

    if (func_80245430(arg0, arg1, arg3, arg4, arg5) && arg2 == arg0[1]) {
        ret = 1;
    }
    return ret;
}

s32 func_802455A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 id = func_80243DDC();

    func_8024557C(D_802ACEC8[id]);
    return func_80245480(D_802ACEC8[id], arg0, arg1, arg2, arg3, arg4, arg5);
}

void func_8024557C(s32 *arg0) {
    func_802454F8(func_80243DDC(), arg0);
}

void func_802454F8(s32 arg0, s32 *arg1) {
    s32 pad[3];
    s32 out[3];
    UnkModel *m = ((UnkObj *)func_802443F4(arg0))->unk40;

    func_8026DCAC(m->unk10, m->unk14, m->unk18, out, 2);
    arg1[0] = out[0];
    arg1[1] = out[1];
    arg1[2] = out[2];
}

s32 func_80245480(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 ret = 0;

    if (func_80245430(arg0, arg1, arg3, arg4, arg6) && arg0[1] >= arg2 && arg5 >= arg0[1]) {
        ret = 1;
    }
    return ret;
}

s32 func_80245430(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 ret = 0;

    if (arg0[0] >= arg1 && arg0[2] >= arg2 && arg3 >= arg0[0] && arg4 >= arg0[2]) {
        ret = 1;
    }
    return ret;
}

s32 func_80245408(s32 arg0) {
    return D_800AEDF0[arg0].unk10;
}

void func_802452E8(s32 arg0) {
    s32 id = func_80243DDC();
    void *obj;
    s32 pad;

    if (id != -1) {
        obj = (void *)func_802443F4(id);
        func_80244354(id, 0x02010000, arg0);
        D_802AC918[id] = 0;
        func_802313DC(obj, 0x40000);
        if (arg0 == 1) {
            func_802313DC(obj, 0x40000);
            if (func_802452AC(id, 0x21C0) && D_800AEDF0[id].unk14 > 0) {
                if (!func_80244BA4(id, 0x8000)) {
                    func_802444B8(id, 0);
                } else {
                    func_802444B8(id, 0xC);
                }
            }
        }
    }
}

s32 func_802452AC(s32 arg0, s32 arg1) {
    s32 ret = 0;

    if (!(D_800AEDF0[arg0].unk10 & arg1)) {
        ret = 1;
    }
    return ret;
}

void func_80245280(s32 arg0) {
    func_80245208(func_80243DDC(), arg0);
}

void func_80245208(s32 arg0, s32 arg1) {
    void *obj;

    if (arg0 != -1) {
        obj = (void *)func_802443F4(arg0);
        func_80244354(arg0, 0x02010000, arg1);
        D_802AC918[arg0] = 0;
        func_802313DC(obj, 0x40000);
    }
}

s32 func_80245150(s32 arg0) {
    s32 ret;
    s32 id = D_802AC9E4;

    if (D_800AEDF0[id].unk48 != 0) {
        if (func_8026E608(arg0, 0x11) == 1) {
            if (func_80243EB4(id, 0x80) && (arg0 & 0x60)) {
                ret = 1;
            } else {
                ret = 0;
            }
        } else {
            ret = 1;
        }
    } else {
        ret = 1;
    }
    return ret;
}

void func_8024512C(s32 arg0, s32 arg1) {
    D_800AEDF0[arg0].unk14 = arg1;
}

void func_802450DC(s32 arg0) {
    s32 id = func_80243DDC();

    func_80244354(id, 0x20, 1);
    func_8023903C(arg0);
    func_80244354(id, 0x20, 0);
}

s32 func_80244FF8(UnkObj *arg0) {
    s32 ret = 0;
    s32 id;
    UnkStruct_800AEDF0 *p;
    s32 flag;

    func_802313DC(arg0, 0x400);
    id = func_802441AC(arg0);
    func_80244354(id, 0x400000, 0);
    p = &D_800AEDF0[id];
    flag = func_80244BA4(id, 0x1000);
    if (flag) {
        flag = func_80243EB4(id, 0x2000);
        if (!flag) {
            arg0->unk6C = 1.0f;
            ret = 1;
            func_80244354(id, 0x200000, 1);
            func_80270BA4(arg0);
            func_802313DC(arg0, 0x20000);
        }
    }
    return ret;
}

s32 func_80244F34(void *arg0, s32 arg1) {
    s32 id = func_802441AC(arg0);
    s32 flag;

    D_800AEDF0[id].unk40 = arg1;
    func_80231408(arg0, 0x400);
    func_80244354(id, 0x200000, 0);
    func_80244354(id, 0x400000, 1);
    flag = func_80244BA4(id, 0x80);
    if (flag) {
        func_80244C30(id, 1);
    }
    return 1;
}

void func_80244E04(void *arg0) {
    s32 id;
    s32 pad[11];
    UnkStruct_800AEDF0 *p;
    s32 flag;

    func_802313DC(arg0, 0x400);
    id = func_802441AC(arg0);
    func_80244354(id, 0x400000, 0);
    p = &D_800AEDF0[id];
    flag = func_80244BA4(id, 0x1000);
    if (!flag) {
        flag = func_80244BA4(id, 0x80);
        if (flag) {
            func_80244C30(id, 1);
        }
        func_80244354(id, 0x20, 0);
        flag = func_80244BA4(id, 0x8000);
        if (!flag) {
            func_802444B8(id, 0);
        } else {
            func_802444B8(id, 0xC);
        }
    } else {
        func_802444B8(id, 8);
    }
    p->unk40 = 0;
}

void func_80244C30(s32 arg0, s32 arg1) {
    UnkObj *obj;
    s32 pad;
    f32 vec[3];
    s32 pad2[2];
    UnkStruct_800AEDF0 *p;

    p = &D_800AEDF0[arg0];
    if (p->unk2C != 0) {
        obj = (UnkObj *)func_802443F4(arg0);
        func_80270770((s16)arg0, (s16)arg1);
        if (!obj && !obj) {}
        p->unk2C = 0;
        p->unk2C = 0;
        func_80270BA4(obj);
        if (func_80244BA4(arg0, 0x400000)) {
            func_802444B8(arg0, 0x13);
        }
        func_80244354(arg0, 0xA040, 0);
        if (!func_80244BA4(arg0, 0x400000)) {
            func_80244354(arg0, 0x20, 0);
        }
        if (func_80243EB4(arg0, 0x2000)) {
            vec[2] = 70.0f;
            vec[1] = 60.0f;
            vec[0] = 180.0f;
            func_8022FEAC(vec, ((UnkObj *)func_802443F4(p->unkA4))->unk4C);
        }
        func_80244354(arg0, 0x100, 0);
    }
    if (func_80244BA4(arg0, 0x80)) {
        func_802444B8(arg0, 0);
    }
    func_80244354(arg0, 0x80, 0);
}

void func_80244BE0(s32 arg0, s32 arg1) {
    func_80270770((s16)arg0, (s16)arg1);
    D_800AEDF0[arg0].unk2C = 0;
}

s32 func_80244BA4(s32 arg0, s32 arg1) {
    s32 ret = 0;

    if (arg1 == (D_800AEDF0[arg0].unk10 & arg1)) {
        ret = 1;
    }
    return ret;
}

void func_802444B8(s32 arg0, s32 arg1) {
    s32 anim1;
    s32 anim2;
    s32 mode;
    Obj88 *obj;

    D_800AEDF0[arg0].unk44 = arg1;
    obj = (Obj88 *)func_802443F4(arg0);
    switch (arg1) {
    case 0:
        anim1 = 0;
        anim2 = -1;
        mode = 3;
        break;
    case 1:
        anim1 = 1;
        anim2 = 2;
        mode = 5;
        break;
    case 2:
        anim1 = 3;
        anim2 = 4;
        mode = 5;
        break;
    case 3:
        anim1 = 5;
        anim2 = 6;
        mode = 5;
        break;
    case 4:
        anim1 = 7;
        anim2 = -1;
        mode = 0;
        break;
    case 5:
        anim1 = -1;
        anim2 = -1;
        break;
    case 6:
        anim1 = 0xB;
        anim2 = -1;
        mode = 0;
        break;
    case 7:
        anim1 = 0xA;
        anim2 = -1;
        mode = 0;
        break;
    case 8:
        anim1 = 0x11;
        anim2 = -1;
        mode = 3;
        break;
    case 10:
        anim1 = 0xC;
        anim2 = -1;
        mode = 0;
        break;
    case 9:
        anim1 = 0xD;
        anim2 = -1;
        mode = 0;
        break;
    case 11:
        anim1 = 0x10;
        anim2 = -1;
        mode = 0;
        break;
    case 12:
        anim1 = 9;
        anim2 = -1;
        mode = 4;
        break;
    case 13:
        anim1 = 8;
        anim2 = 2;
        mode = 6;
        break;
    case 14:
        anim1 = 8;
        anim2 = 4;
        mode = 6;
        break;
    case 15:
        anim1 = 8;
        anim2 = 6;
        mode = 6;
        break;
    case 16:
        anim1 = 0xF;
        anim2 = -1;
        mode = 0;
        break;
    case 18:
        anim1 = 8;
        anim2 = -1;
        mode = 0;
        break;
    case 17:
        anim1 = 0xE;
        anim2 = -1;
        mode = 0;
        break;
    case 19:
        anim1 = 0x12;
        anim2 = -1;
        mode = 0;
        break;
    case 20:
        anim1 = 8;
        anim2 = 0x15;
        mode = 2;
        break;
    case 21:
        anim1 = 0x16;
        anim2 = -1;
        mode = 2;
        break;
    case 23:
        anim1 = 0x18;
        anim2 = -1;
        mode = 0;
        break;
    case 24:
        anim1 = 0x19;
        anim2 = -1;
        mode = 0;
        break;
    default:
        anim1 = -1;
        anim2 = -1;
        mode = 0;
        break;
    }
    func_80229E38(obj->unk40, anim1, 0);
    func_80229E38(obj->unk40, anim2, 1);
    obj->unk40->unkC |= 0x4000;
    switch (mode) {
    case 0:
        obj->unk40->unk48->unk4->unk8 |= 0x20;
        obj->unk40->unk48->unk4->unk8 &= ~0x40;
        obj->unk40->unk48->unk4->unk14 &= ~0x20;
        obj->unk40->unk48->unk4->unk14 &= ~0x40;
        break;
    case 2:
        obj->unk40->unk48->unk4->unk8 |= 0x20;
        obj->unk40->unk48->unk4->unk8 &= ~0x40;
        obj->unk40->unk48->unk4->unk14 &= ~0x20;
        obj->unk40->unk48->unk4->unk14 &= ~0x40;
        break;
    case 3:
        obj->unk40->unk48->unk4->unk8 &= ~0x20;
        obj->unk40->unk48->unk4->unk8 &= ~0x40;
        obj->unk40->unk48->unk4->unk14 &= ~0x20;
        obj->unk40->unk48->unk4->unk14 &= ~0x40;
        break;
    case 4:
        obj->unk40->unk48->unk4->unk8 |= 0x20;
        obj->unk40->unk48->unk4->unk8 |= 0x40;
        obj->unk40->unk48->unk4->unk14 |= 0x20;
        obj->unk40->unk48->unk4->unk14 |= 0x40;
        break;
    case 5:
        obj->unk40->unk48->unk4->unk8 &= ~0x20;
        obj->unk40->unk48->unk4->unk8 &= ~0x40;
        obj->unk40->unk48->unk4->unk4 = func_8024441C(arg0, arg1);
        obj->unk40->unk48->unk4->unk14 &= ~0x20;
        obj->unk40->unk48->unk4->unk14 &= ~0x40;
        obj->unk40->unk48->unk4->unk10 = obj->unk40->unk48->unk4->unk4;
        break;
    case 6:
        obj->unk40->unk48->unk4->unk8 |= 0x20;
        obj->unk40->unk48->unk4->unk8 |= 0x40;
        obj->unk40->unk48->unk4->unk14 &= ~0x20;
        obj->unk40->unk48->unk4->unk14 &= ~0x40;
        obj->unk40->unk48->unk4->unk10 = func_8024441C(arg0, arg1);
        break;
    }
}

f32 func_8024441C(s32 arg0, s32 arg1) {
    f32 ret = 0.0f;
    UnkStruct_800AEDF0 *p;
    s32 v;

    if (!D_800AEDF0[arg0].unk10 && !D_800AEDF0[arg0].unk10) {}
    if (arg1 == D_802AC9F8[arg0]) {
        p = &D_800AEDF0[arg0];
        v = p->unk44;
        switch (v) {
            case 1:
            case 2:
            case 3:
                v = 0;
                break;
            case 13:
            case 14:
            case 15:
                v = 1;
                break;
            default:
                v = -1;
                break;
        }
        if (v != -1) {
            ret = D_802ACA78[arg0];
        }
    }
    return ret;
}

s32 func_802443F4(s32 arg0) {
    s32 ret;

    ret = D_800AEDF0[arg0].unk28;
    return ret;
}

s32 func_802443CC(s32 arg0) {
    return D_800AEDF0[arg0].unk44;
}

void func_802443A0(s32 arg0) {
    s32 id;

    id = func_80243DDC();
    func_80244354(id, 0x01000000, arg0);
}

void func_80244354(s32 arg0, s32 arg1, s32 arg2) {
    s32 v = D_800AEDF0[arg0].unk10;

    if (arg2 == 1) {
        v |= arg1;
    } else {
        v &= arg1 ^ -1;
    }
    D_800AEDF0[arg0].unk10 = v;
    if (0) {
        func_80237664();
    }
}

void func_80244308(void *arg0) {
    func_8022F4AC(arg0, 0x10, D_800AEDF0[func_802441AC(arg0)].unk4C);
}

s32 func_802442F8() {
    return D_802A01B0;
}

s32 func_802442D0(s32 arg0) {
    return D_800AEDF0[arg0].unk20;
}

s32 func_802442A8(s32 arg0) {
    return D_800AEDF0[arg0].unk4C;
}

void func_802441F4(void *arg0, s32 arg1, s32 *arg2, f32 *arg3) {
    f32 x;
    f32 pos[3];
    f32 rot[3];
    f32 v[3];

    *arg2 = arg1;
    *arg3 = 0.0f;
    func_80239880(func_802441AC(arg0), 0, pos);
    func_80234858(&v[0], &v[1], &v[2]);
    if (pos[2] >= 20.0f) {
        x = pos[0] + v[0];
        if (x >= 360.0f) {
            x -= 360.0f;
        }
        *arg2 = func_80243F50(x);
        *arg3 = 8.5f;
    }
}

s32 func_802441AC(void *arg0) {
    s32 ret = -1;
    s32 i = 0;

    do {
        if (arg0 == D_800AEDF0[i].unk28) {
            ret = i;
        }
        i++;
    } while (i < 5 && ret == -1);
    return ret;
}

s32 func_80243F50(f32 arg0) {
    s32 ret;

    if ((arg0 >= 0.0 && arg0 < 22.5) || (arg0 >= 337.5 && arg0 < 360.0)) {
        ret = 0x80;
    }
    if (arg0 >= 22.5 && arg0 < 67.5) {
        ret = 0x60;
    }
    if (arg0 >= 67.5 && arg0 < 112.5) {
        ret = 0x40;
    }
    if (arg0 >= 112.5 && arg0 < 157.5) {
        ret = 0x20;
    }
    if (arg0 >= 157.5 && arg0 < 202.5) {
        ret = 0;
    }
    if (arg0 >= 202.5 && arg0 < 247.5) {
        ret = 0xE0;
    }
    if (arg0 >= 247.5 && arg0 < 292.5) {
        ret = 0xC0;
    }
    if (arg0 >= 292.5 && arg0 < 337.5) {
        ret = 0xA0;
    }
    if (arg0 == -1.0f) {
        ret = 1;
    }
    return ret;
}

void func_80243F2C(s32 arg0, s32 arg1) {
    D_800AEDF0[arg0].unk24 = arg1;
}

s32 func_80243EF0(s32 arg0) {
    s32 ret = 0;

    if ((D_800AEDF0[arg0].unk68 & 0x200) == 0x200) {
        ret = 1;
    }
    return ret;
}

s32 func_80243EB4(s32 arg0, s32 arg1) {
    s32 ret = 0;

    if (arg1 == (D_800AEDF0[arg0].unk68 & arg1)) {
        ret = 1;
    }
    return ret;
}

void func_80243E90(s32 arg0) {
    func_80243D90(arg0, 0x200, 1);
}

void func_80243E60() {
    func_8027750C((s16)func_80243DDC());
}

s32 func_80243E3C() {
    s32 ret = 0;

    if ((D_802AC9E8 & 2) == 2) {
        ret = 1;
    }
    return ret;
}

s32 func_80243E18(s32 arg0) {
    s32 ret = 0;

    if (arg0 == (D_802AC9E8 & arg0)) {
        ret = 1;
    }
    return ret;
}

void func_80243DEC(s32 arg0) {
    s32 id;

    id = func_80243DDC();
    func_80243D90(id, 0x8000, arg0);
}

s32 func_80243DDC() {
    s32 ret;

    ret = D_802AC894;
    return ret;
}

void func_80243D90(s32 arg0, s32 arg1, s32 arg2) {
    s32 v = D_800AEDF0[arg0].unk68;

    if (arg2 == 1) {
        v |= arg1;
    } else {
        v &= arg1 ^ -1;
    }
    D_800AEDF0[arg0].unk68 = v;
}

void *func_80243D7C(s32 arg0) {
    return &D_802ACF08[arg0];
}

s32 *func_80243D54(s32 arg0) {
    return &D_800AEDF0[arg0].unk10;
}

s32 func_80243D2C(s32 arg0) {
    return D_800AEDF0[arg0].unk14;
}

void func_80243D20(s32 arg0) {
    D_802AC9F4 = arg0;
}

void func_80243BF0() {
    s32 i;

    func_80297D30(0x10, D_802A0E58);
    for (i = 0; i < 5; i++) {
        D_800AEDF0[i].unk28 = 0;
        D_800AEDF0[i].unk18 = 0x200;
        D_800AEDF0[i].unk24 = 0;
        D_800AEDF0[i].unk0 = D_800AEDF0[i].unk4 = D_800AEDF0[i].unk8 = 0.0f;
        D_800AEDF0[i].unk10 = 0;
        D_800AEDF0[i].unkC = 0.0f;
    }
    D_800AEDF0[0].unk24 = 1;
    D_802AC894 = -1;
    D_802AC9F4 = 0;
}
