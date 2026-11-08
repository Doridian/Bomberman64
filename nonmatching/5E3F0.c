/*
 * NON_MATCHING: main_code's 5E3F0, complete: 155 functions (us
 * 0x80243BF0-0x802513D8) around a table of five 0xC8-byte entries,
 * D_800AEDF0[5] (an object in unk28, flag words in unk10 and unk68), the
 * current entry in D_802AC894. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 11755, eu 11755, jp 11646
 *
 * A first draft: functions in the reverse of the ROM's order (IDO -O3
 * emits last to first); 0x80243BF0-0x802457D8 by hand, most of the rest
 * m2c's, with the fixes the -O3 build needs. 47 of 155 match in us.
 * The object is -O3: its small getters and flag tests are inlined into
 * every caller and still emitted, and the inlined copies are what give
 * the original its registers:
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
 * Left: register and scheduling differences nearly everywhere else, and
 * the large m2c functions (8024E088, 8024891C, 8024D8C4, 8024B444,
 * 80246F00, 8024A0DC) are still m2c's shape. 802506B8's fill loop of the
 * ten 255-entry tables isn't unrolled in the original (this one is), and
 * jp's 8024E088 and 8024FFF0 differ from us's (no #if yet).
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
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s32 unk8C;
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
    /* 0xC0 */ s32 unkC0;
    /* 0xC4 */ s32 unkC4;
} UnkStruct_800AEDF0; /* size 0xC8 */

extern UnkStruct_800AEDF0 D_800AEDF0[5];

typedef struct {
    s32 v[8];
} Tbl8i_5E3F0;

typedef struct {
    f32 v[8];
} Tbl8f_5E3F0;

typedef struct {
    s32 v[4];
} Tbl4_5E3F0;

typedef struct {
    s32 v[3];
} Tbl3_5E3F0;


void free(void *);
s32 func_8022979C(s32, s32, s32);
void func_802297B8(s32, s32, s32, s32);
s32 func_8022984C(s32);
f32 func_80229D3C(void *, s32);
void func_80229E38(void *, s32, s32);
s32 func_80229F74(s32);
s32 func_8022DF68(s32, s32);
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
s32 func_80271540(s32);
s32 func_80271BB8(s32);
void func_802727D8(s32);
void func_802733C8(void *);
s32 func_802741D8(void);
s32 func_80274994(s32);
s32 func_80274F64(s32);
s32 func_80274F8C(s16, f32, f32, f32, s16);
s32 func_80275C7C(s32, s32, s32);
s32 func_8027750C(s32);
s32 func_802775D8(s32);
s32 func_8027799C(s32);
s32 func_80277CEC(s32);
s32 func_80278E84(s32, s32);
s32 func_8027B0BC(s32);
void func_8027B39C(s16, s16);
void func_8027F820(void);
void func_8027F858(s32, s32);
void func_80282144(s32, s32, s32, f32);
void func_80282934(void);
void * func_802867E4(s32, f32, f32, f32);
s32 func_80287008(s32, s32, s32);
s32 func_802871D0(s32);
s32 func_8028A4E0(s32);
s32 func_8028A7CC(s32, f32 *, s32);
void func_8028A81C(s32, f32, f32, f32, s32);
s32 func_802909FC(s32);
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
extern f32 D_802ACA10[];
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
extern f32 D_802ACEC8[];
extern void * D_802ACF04;
extern u8 D_802ACF08[][0x10];
extern void **D_802ACF58;
extern void * D_802ACF5C;
extern s32 * D_802ACF60;
extern s32 D_802ACF68[];

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
s32 func_80245690(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
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
void func_80246D74(s16 arg0);
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
void func_80249E30(s16 arg0);
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
void func_8024B1CC(s16 arg0);
void func_8024B444(s32 arg0, f32 *arg1);
void func_8024BBA4(s32 arg0);
void func_8024BC20(s32 arg0);
void func_8024BC94(s32 arg0);
void func_8024BD1C(s32 arg0);
void func_8024BF04(s32 arg0);
void func_8024BFE0(s32 arg0);
void func_8024C04C(s16 arg0);
void func_8024C0D8(s32 arg0);
void func_8024C1E8(s32 arg0);
void func_8024C29C(s32 arg0);
void func_8024C314(void);
void func_8024C334(s32 arg0, s32 arg1, u16 arg2, f32 *arg3);
s32 func_8024C4EC(UnkObj *obj, s32 arg1);
void func_8024C53C(s32 arg0, void *arg1);
void func_8024C804(s32 arg0);
void func_8024C884(s32 arg0, f32 arg1, s32 arg2);
void func_8024CC58(s16 arg0);
void func_8024CEB8(s32 arg0);
void func_8024D108(s32 arg0, s32 arg1);
void func_8024D20C(s16 arg0);
void func_8024D374(s32 arg0);
s32 func_8024D41C(f32 key);
s32 func_8024D50C(void *arg0);
void func_8024D540(s32 arg0, f32 *arg1);
void func_8024D5D0(f32 *arg0);
void func_8024D8C4(f32 *arg0);
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
    UnkObj *temp_a1;
    UnkStruct_800AEDF0 *temp_v0;

    temp_a1 = ((UnkObj *)func_802443F4(func_80243DDC()));
    temp_v0 = &D_800AEDF0[func_80243DDC()];
    temp_a1->unk40->unk10 = temp_v0->unk0;
    temp_a1->unk40->unk14 = temp_v0->unk4;
    temp_a1->unk40->unk18 = temp_v0->unk8;
    M2C_FIELD(temp_a1->unk40, f32 *, 0x20) = (f32) temp_v0->unkC;
}

void func_802512C0(s32 arg0, s32 arg1, s32 arg2) {
    func_802511EC(func_80243DDC(), arg0, arg1, arg2);
}

void func_802511EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 sp34[3];
    UnkObj *temp_a0;
    UnkStruct_800AEDF0 *temp_v1;

    func_8026E338((f32) arg1, (f32) arg2, (f32) arg3, sp34, 0);
    temp_v1 = &D_800AEDF0[arg0];
    temp_a0 = temp_v1->unk28;
    if (temp_a0 != NULL) {
        temp_a0->unk40->unk10 = sp34[0];
        temp_a0->unk40->unk14 = sp34[1];
        temp_a0->unk40->unk18 = sp34[2];
        temp_v1->unk0 = -10000.0f;
        temp_v1->unk4 = -10000.0f;
        temp_v1->unk8 = -10000.0f;
        return;
    }
    temp_v1->unk0 = sp34[0];
    temp_v1->unk4 = sp34[1];
    temp_v1->unk8 = sp34[2];
}

void func_802511C4() {
    func_80237664();
    func_802362D4(0x1F);
}

void func_80251134(s32 arg0) {
    UnkStruct_800AEDF0 *temp_a3;
    s32 var_v1;

    temp_a3 = &D_800AEDF0[arg0];
    var_v1 = func_80244BA4(arg0, 0x1000);
    if (var_v1 != 0) {
        func_80247A54(arg0, func_8022F4AC((s32) temp_a3->unk28, 2, temp_a3->unk4C), 0, 0);
        func_80244354(arg0, 0x1020, 1);
    }
}

void func_802510F0() {
    s32 var_a0;
    s32 var_s0;

    var_s0 = 0;
    var_a0 = 0;
    do {
        func_80247848(var_a0, 0);
        var_s0 += 1;
        var_a0 = var_s0;
    } while (var_s0 != 5);
}

void func_802510C8() {
    func_80247C50(func_80243DDC());
}

void func_80250E2C(s32 arg0) {
    s32 spBC;
    s32 spA4[3];
    f32 sp98[3];
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp74;
    f32 sp70;
    UnkStruct_800AEDF0 *temp_s1;
    s32 temp_t1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v1;
    void *temp_a0;
    void *temp_v1;
    void *temp_v1_2;

    temp_a0 = ((UnkObj *)func_802443F4(func_80243DDC()));
    spBC = func_80243DDC();
    func_8022F808(temp_a0, &sp8C);
    func_80247C50(spBC);
    temp_v1 = M2C_FIELD(temp_a0, void **, 0x40);
    func_8026DCAC(M2C_FIELD(temp_v1, f32 *, 0x10), M2C_FIELD(temp_v1, f32 *, 0x14), M2C_FIELD(temp_v1, f32 *, 0x18), spA4, 2);
    func_8026E338((f32) spA4[0], (f32) spA4[1], (f32) spA4[2], sp98, 0);
    temp_t1 = spBC * 4;
    D_802ACA10[(temp_t1) / 4] = 0;
    sp80 = sp98[0];
    sp84 = sp98[1];
    sp88 = sp98[2];
    if (M2C_BITWISE(f32, func_8022DF68((s32) &sp8C, (s32) &sp80)) > 0.0f) {
        func_8022FF58(&sp8C, &sp80, &sp70);
        sp74 -= 90.0f;
        temp_v0 = func_80243F50(sp70);
        D_802AC8BC = temp_v0;
        D_802AC8C0 = temp_v0;
        D_802ACA24 = 4.0f;
        D_802AC95C = 3;
        D_802AC968[(temp_t1) / 4] = 1;
        temp_v1_2 = M2C_FIELD(temp_a0, void **, 0x40);
        func_8026DCAC(M2C_FIELD(temp_v1_2, f32 *, 0x10), M2C_FIELD(temp_v1_2, f32 *, 0x14), M2C_FIELD(temp_v1_2, f32 *, 0x18), spA4, 2);
        func_8026E338((f32) spA4[0], (f32) spA4[1], (f32) spA4[2], sp98, 0);
        D_802ACA28 = sp98[0];
        D_802ACA2C = sp98[1];
        D_802ACA8C = sp98[2];
        func_80244354(spBC, 0x10420, 1);
        D_802AC918[(temp_t1) / 4] = 0;
        func_802313DC(temp_a0, 0x40000);
        if (arg0 != 0) {
            temp_s1 = &D_800AEDF0[spBC];
            var_v1 = func_80244BA4(spBC, 0x400);
            if (var_v1 != 0) {
                do {
                    var_s0 = 0;
                    func_80239094();
                    if ((temp_s1->unk10 & 0x400) == 0x400) {
                        var_s0 = 1;
                    }
                } while (var_s0 != 0);
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
    s32 id = D_802AC894;
    s32 i;
    s32 n;
    s32 c;

    for (i = 0; i < 255; i++) {
        D_800AF1D8[i] = -1;
        D_800AF5D8[i] = -1;
        D_802ACA90[i] = -1.0f;
        D_800AF9D8[i] = -1;
        D_800AFDD8[i] = -1;
        D_800B01D8[i] = -1;
        D_800B05D8[i] = -1;
        D_800B09D8[i] = -1;
        D_800B0DD8[i] = -1;
        D_800B11D8[i] = -1;
    }
    n = 0;
    c = *str;
    if (c != 0) {
        do {
            D_800AF1D8[n] = c;
            switch (*str) {
            case 'W':
            case 'w':
                switch (*++str) {
                case 'D':
                case 'd':
                    switch (*++str) {
                    case 'N':
                    case 'n':
                        switch (str[1]) {
                        case 'E':
                        case 'e':
                            D_800AF5D8[n] = 0x20;
                            str++;
                            break;
                        case 'W':
                        case 'w':
                            D_800AF5D8[n] = 0xE0;
                            str++;
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
                        switch (str[1]) {
                        case 'E':
                        case 'e':
                            D_800AF5D8[n] = 0x60;
                            str++;
                            break;
                        case 'W':
                        case 'w':
                            D_800AF5D8[n] = 0xA0;
                            str++;
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
                    switch (*++str) {
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
                    switch (*++str) {
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
                    if (*++str == '1') {
                        D_800B01D8[n] = 1;
                    } else {
                        D_800B01D8[n] = 0;
                    }
                    break;
                case 'G':
                case 'g':
                    if (*++str == '1') {
                        D_800B05D8[n] = 1;
                    } else {
                        D_800B05D8[n] = 0;
                    }
                    break;
                case 'B':
                case 'b':
                    if (str[1] >= '0' && str[1] <= '9') {
                        D_800AFDD8[n] = 0;
                    }
                    while (str[1] >= '0' && str[1] <= '9') {
                        str++;
                        D_800AFDD8[n] *= 10;
                        D_800AFDD8[n] += *str - '0';
                    }
                    n++;
                    break;
                }
                break;
            case 'S':
            case 's':
                D_800B09D8[n] = str[1];
                c = *++str;
                if (c == 'T' || c == 't') {
                    if (str[1] >= '0' && str[1] <= '9') {
                        D_800B0DD8[n] = 0;
                    }
                    while (str[1] >= '0' && str[1] <= '9') {
                        str++;
                        D_800B0DD8[n] *= 10;
                        D_800B0DD8[n] += *str - '0';
                    }
                    n++;
                }
                break;
            case 'M':
            case 'm':
                D_800B11D8[n] = *++str;
                n++;
                break;
            }
            c = *++str;
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
    s32 sp64;
    s32 sp48[3];
    s32 sp44;
    s32 sp40;
    f64 temp_fv0;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    void *temp_a0;
    void *temp_v0;

    temp_a0 = D_800AEDF0[arg0].unk28;
    temp_fv0 = (f64) M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x40), f32 *, 0x20);
    if (((temp_fv0 >= 0.0) && (temp_fv0 < 22.5)) || ((temp_fv0 >= 337.5) && (temp_fv0 < 360.0))) {
        sp40 = 1;
        sp44 = 0;
    }
    var_t0 = sp44;
    var_t1 = sp40;
    if ((temp_fv0 >= 22.5) && (temp_fv0 < 67.5)) {
        var_t0 = 1;
        var_t1 = 1;
    }
    if ((temp_fv0 >= 67.5) && (temp_fv0 < 112.5)) {
        var_t0 = 1;
        var_t1 = 0;
    }
    if ((temp_fv0 >= 112.5) && (temp_fv0 < 157.5)) {
        var_t0 = 1;
        var_t1 = -1;
    }
    if ((temp_fv0 >= 157.5) && (temp_fv0 < 202.5)) {
        var_t0 = 0;
        var_t1 = -1;
    }
    if ((temp_fv0 >= 202.5) && (temp_fv0 < 247.5)) {
        var_t0 = -1;
        var_t1 = -1;
    }
    if ((temp_fv0 >= 247.5) && (temp_fv0 < 292.5)) {
        var_t0 = -1;
        var_t1 = 0;
    }
    if ((temp_fv0 >= 292.5) && (temp_fv0 < 337.5)) {
        var_t0 = -1;
        var_t1 = 1;
    }
    temp_v0 = M2C_FIELD(temp_a0, void **, 0x40);
    sp64 = 0;
    sp40 = var_t1;
    sp44 = var_t0;
    func_8026DCAC(M2C_FIELD(temp_v0, f32 *, 0x10), M2C_FIELD(temp_v0, f32 *, 0x14), M2C_FIELD(temp_v0, f32 *, 0x18), sp48, 2);
    var_t2 = sp64;
    if (!(func_8026D7D8(sp48[0] + sp44, sp48[1], sp48[2] + sp40) & 0x4000)) {
        var_t2 = 1;
    }
    return var_t2;
}

void func_80250338(s32 arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = ((UnkObj *)func_802443F4(arg0));
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x40), f32 *, 0x10);
    M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x40), f32 *, 0x14);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x40), f32 *, 0x18);
}

void func_802502BC(s32 arg0) {
    UnkObj *sp24;
    UnkStruct_800AEDF0 *sp18;
    UnkStruct_800AEDF0 *temp_a3;

    temp_a3 = &D_800AEDF0[arg0];
    sp18 = temp_a3;
    sp24 = temp_a3->unk28;
    func_80243D90(0x90, 1, (s32) temp_a3);
    temp_a3->unk78 = 0x4B0;
    func_80231408(sp24, 0x40);
    func_80246C3C(arg0, 1, 1);
}

void func_802500D4() {
    void *objs[4];
    Tbl4_5E3F0 tbl;
    f32 pos[3];
    f32 off[3];
    UnkStruct_800AEDF0 *p;
    void **o;
    UnkObj *obj;
    s32 r;

    tbl = *(Tbl4_5E3F0 *)D_802A0E08;
    for (p = D_800AEDF0, o = objs; p < &D_800AEDF0[4]; p++, o++) {
        *o = NULL;
        if (p->unk14 != 0 && p->unk24 != 0) {
            r = func_80234248(3);
            if (r != 0) {
                obj = p->unk28;
                pos[2] = 50.0f;
                pos[1] = 0.0f;
                pos[0] = M2C_FIELD(obj->unk40, f32 *, 0x20);
                func_8022FEAC(pos, off);
                *o = func_80231274(-1, tbl.v[r], 0x60, NULL);
                ((UnkObj *)*o)->unk40->unk10 = obj->unk40->unk10 + off[0];
                ((UnkObj *)*o)->unk40->unk14 = obj->unk40->unk14 + off[1];
                ((UnkObj *)*o)->unk40->unk18 = obj->unk40->unk18 + off[2];
                func_8022E884((s32)*o, (s32)obj);
            }
        }
    }
    func_80239094();
    for (o = objs; o != &objs[4]; o++) {
        if (*o != NULL) {
            func_8022FC90(*o);
        }
    }
    func_80239430();
}

void func_8024FFF0() {
    UnkStruct_800AEDF0 *p;
    s32 i;

    for (;;) {
        for (i = 0, p = D_800AEDF0; i != 5; i++, p++) {
            if ((p->unk24 == 1 || p->unk24 == 2) && p->unk28 != NULL) {
                func_8024E088(i);
            }
        }
        if (FLAG_SET(D_802AC9E8, 1)) {
            func_80247614();
        }
        func_80239094();
    }
}

void func_8024E088(s32 arg0) {
    u16 sp126;
    u16 sp124;
    s32 sp120;
    s32 sp11C;
    s32 sp114;
    s32 sp110;
    s32 sp108;
    s32 spFC;
    s32 spF0;
    s32 spD8[3];
    f32 spD4;
    f32 spD0;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    s32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp84[3];
    f32 sp78;
    s32 sp74;
    void *sp6C;
    s32 sp68;
    f32 sp58[4];
    s32 sp44;
    UnkStruct_800AEDF0 *sp40;
    s32 sp3C;                                       /* compiler-managed */
    f32 *sp2C;
    UnkStruct_800AEDF0 *temp_v0_2;
    f32 *temp_a1;
    f32 temp_ft3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    f64 temp_fv0_3;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_a2_6;
    s32 temp_t1;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_18;
    s32 temp_v0_21;
    s32 temp_v0_22;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 var_a0;
    s32 var_a2;
    s32 var_t4;
    s32 var_t7;
    s32 var_v0;
    s32 var_v1;
    void *temp_a2_5;
    void *temp_v0;
    void *temp_v0_12;
    void *temp_v0_15;
    void *temp_v0_16;
    void *temp_v0_17;
    void *temp_v0_19;
    void *temp_v0_20;
    void *temp_v0_23;
    void *temp_v0_24;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_9;

    temp_v0 = func_802443F4(0);
    if (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) != -10000.0f) {
        if (func_802441AC(temp_v0) == arg0) {

        }
        temp_v0_2 = &D_800AEDF0[arg0];
        sp40 = temp_v0_2;
        temp_v0_2->unkC = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20);
        if (func_80244BA4(arg0, 0x200000) != 0) {
            func_802733C8(temp_v0);
        }
        temp_v0_3 = M2C_FIELD(temp_v0, void **, 0x40);
        func_8026DCAC(M2C_FIELD(temp_v0_3, f32 *, 0x10), M2C_FIELD(temp_v0_3, f32 *, 0x14), M2C_FIELD(temp_v0_3, f32 *, 0x18), spD8, 2);
        D_802AC8A4 = func_8026DC74(spD8[1]);
        sp11C = func_8026D7D8(spD8[0], spD8[1], spD8[2]);
        if ((func_80244BA4(arg0, 0x400) != 0) && (sp40->unk48 == 0)) {
            sp11C = 1;
        }
        if ((M2C_FIELD(temp_v0, s32 *, 0x10) & 0x20) && (func_80244BA4(arg0, 0x10000) == 0)) {
            func_80248148(arg0, 2);
        }
        temp_a2 = M2C_FIELD(temp_v0, s32 *, 0x10);
        if (((temp_a2 & 0x40) || (temp_a2 & 0x80)) && (func_80244BA4(arg0, 0x10000) == 0)) {
            func_80248148(arg0, 1);
        }
        if ((M2C_FIELD(temp_v0, s32 *, 0x10) & 0x100) && (func_80244BA4(arg0, 0x10000) == 0)) {
            func_80248148(arg0, 0);
        }
        sp108 = D_802AC5D0 & 4;
        temp_v0_4 = func_8023A834();
        D_802ACF5C = temp_v0_4;
        if ((sp108 != 0) && (M2C_FIELD(temp_v0_4, s32 *, 0x2C) == 0) && (M2C_FIELD(temp_v0_4, s32 *, 0x30) == 0x3B) && (func_80243EB4(arg0, 0x200) != 0)) {
            if (M2C_FIELD(temp_v0, void **, 0x44) != NULL) {
                if (func_80244BA4(arg0, 0x1000) == 0) {
                    func_80247F90(func_802441AC(M2C_FIELD(temp_v0, void **, 0x44)));
                }
            }
            func_80248148(arg0, 5);
        }
        temp_a2_2 = M2C_FIELD(temp_v0, s32 *, 0x10);
        var_t7 = temp_a2_2 * 2;
        if (temp_a2_2 & 0x1E00) {
            func_80249648(arg0, M2C_FIELD(temp_v0, UnkObj **, 0x20), temp_a2_2);
            var_t7 = M2C_FIELD(temp_v0, s32 *, 0x10) * 2;
        }
        if (var_t7 < 0) {
            if (func_80244BA4(arg0, 0x01000000) == 0) {
                func_8027F820();
                func_80248148(arg0, 3);
            }
        }
        if (sp40->unk24 != 3) {
            sp126 = 0;
            sp124 = 0;
            spFC = arg0;
            spBC = 0.0f;
            if (func_80243EB4(0, arg0) != 0) {
                spFC = sp40->unkA4;
                if (sp40->unk24 == 1) {
                    func_80239880(arg0, 0, &sp90);
                } else {
                    temp_v0_5 = (arg0 * 0x10) + &D_802ACF08;
                    sp98 = M2C_FIELD(temp_v0_5, f32 *, 8);
                    sp94 = M2C_FIELD(temp_v0_5, f32 *, 4);
                    sp90 = M2C_FIELD(temp_v0_5, f32 *, 0);
                }
            }
            if (func_80244BA4(arg0, 0x1000) == 0) {
                if (M2C_FIELD(temp_v0, void **, 0x44) == NULL) {
                    goto block_42;
                }
            } else {
block_42:
                if (D_800AEDF0[spFC].unk24 == 1) {
                    func_80239880(spFC, 0, &spB4);
                    sp126 = func_80239FF8(spFC);
                    sp124 = func_802399AC(spFC);
                } else {
                    temp_v0_6 = (spFC * 0x10) + &D_802ACF08;
                    spBC = M2C_FIELD(temp_v0_6, f32 *, 8);
                    spB8 = M2C_FIELD(temp_v0_6, f32 *, 4);
                    spB4 = M2C_FIELD(temp_v0_6, f32 *, 0);
                    sp126 = M2C_FIELD(temp_v0_6, u16 *, 0xC);
                    sp124 = M2C_FIELD(temp_v0_6, u16 *, 0xE);
                }
            }
            if (func_802452AC(arg0, 0x02000C20) != 0) {
                temp_t3 = sp126 & 0x4000;
                sp44 = temp_t3;
                if ((temp_t3 != 0) && (sp124 & 0x8000) && (func_802452AC(arg0, 0x0840A182) != 0) && (func_80243EB4(arg0, 8) == 0) && (func_80243EB4(arg0, 0x80) == 0)) {
                    if (func_80243EB4(arg0, 0x200) == 0) {
                        if (!(sp11C & 0x4000) && (func_80274994((s32) (s16) arg0) != 0)) {
                            func_80249FD4(arg0, 1);
                        } else {
                            goto block_56;
                        }
                    } else {
                        goto block_57;
                    }
                } else {
block_56:
block_57:
                    sp3C = (s32) sp124;
                    if (((s32) sp124 & 0x8000) && (sp44 == 0) && (func_802452AC(arg0, 0x4000C3) != 0) && (func_80243EB4(arg0, 8) == 0) && (func_80243EB4(arg0, 0x80) == 0) && (func_80243EB4(arg0, 0x200) == 0)) {
                        temp_v0_7 = func_8022F550((s32) temp_v0, 2);
                        sp74 = temp_v0_7;
                        if ((temp_v0_7 != 0) && (temp_v0_7 == sp40->unk4C)) {
                            if (M2C_FIELD(temp_v0, f32 *, 0x6C) == 0.0f) {
                                temp_v0_8 = func_8022F550((s32) temp_v0, 2);
                                sp74 = temp_v0_8;
                                func_80249810(arg0, temp_v0_8, 2);
                            }
                        } else {
                            temp_v0_9 = M2C_FIELD(temp_v0, void **, 0x40);
                            temp_v0_10 = func_80274F8C(M2C_FIELD(sp40, s16 *, 0x1A), M2C_FIELD(temp_v0_9, f32 *, 0x10), M2C_FIELD(temp_v0_9, f32 *, 0x14), M2C_FIELD(temp_v0_9, f32 *, 0x18), (s16) arg0);
                            if (temp_v0_10 != 0) {
                                func_80247928(arg0, M2C_FIELD(temp_v0_10, s32 *, 0x1C));
                                func_8026C660(0xA);
                            }
                        }
                    }
                    var_a0 = arg0 << 0x10;
                    if (!(sp3C & 0x4000)) {
                        if (func_80243E18(2) != 0) {
                            if (!(D_802AC9EC & 7) && (M2C_FIELD(temp_v0, void **, 0x44) == NULL)) {
                                var_a0 = arg0 << 0x10;
                                if (func_802452AC(arg0, 0x1180) != 0) {
                                    goto block_75;
                                }
                            }
                        }
                    } else {
block_75:
                        temp_t1 = var_a0 >> 0x10;
                        sp44 = temp_t1;
                        if (func_80270714(temp_t1) == 0) {
                            func_802313DC(temp_v0, 1);
                            temp_v0_11 = func_80271540((s16) arg0);
                            sp68 = temp_v0_11;
                            M2C_FIELD(temp_v0_11, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_11, s32 *, 0xC) | 0x10);
                            func_80231408(temp_v0, 1);
                            if (sp68 != 0) {
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
            if (func_802452AC(arg0, 0x02000400) != 0) {
                sp3C = (s32) sp124;
                if (sp124 & 0x10) {
                    func_802712C4(func_8027799C((s32) func_80274F64((s32) (s16) arg0)));
                }
                if (sp3C & 0x2000) {
                    func_8027750C((s32) (s16) arg0);
                }
            }
            sp120 = 1;
            spD4 = 0.0f;
            if (func_80244BA4(arg0, 0x400) != 0) {
                if (func_802452AC(arg0, 0x1C0) != 0) {
                    func_8024D8C4(sp58);
                    spD4 = sp58[0];
                    sp120 = sp58[1];
                    if ((D_802AC968[arg0] & 1) == 1) {
                        if (D_802AC97C == 0) {
                            M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = 0.0f;
                            M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), void **, 0x48), void **, 4), f32 *, 0x10) = 0.0f;
                            temp_v0_12 = M2C_FIELD(temp_v0, void **, 0x40);
                            M2C_FIELD(temp_v0_12, f32 *, 0x14) = (f32) (M2C_FIELD(temp_v0_12, f32 *, 0x14) + sp58[3]);
                        }
                    }
                }
            }
            if (func_80244BA4(arg0, 2) != 0) {
                func_8024D540(arg0, sp58);
                spD4 = sp58[0];
                sp120 = sp58[1];
            }
            if (func_8023372C(spBC, 0.001f) == 0) {
                func_80234858(&sp9C, &spA0, &spA4);
                if ((spA0 >= 180.0f) && (spA0 < 360.0f) && (D_802AC9F4 != 0)) {
                    temp_fv0 = 180.0f - spB4;
                    if (temp_fv0 >= 360.0f) {
                        spB4 = temp_fv0 - 360.0f;
                    } else {
                        if (spB4 > 180.0f) {
                            var_fv1 = temp_fv0 + 360.0f;
                        } else {
                            var_fv1 = temp_fv0;
                        }
                        spB4 = var_fv1;
                    }
                }
                temp_fv0_2 = spB4 + sp9C;
                if (temp_fv0_2 >= 360.0f) {
                    var_fa1 = temp_fv0_2 - 360.0f;
                } else {
                    if (temp_fv0_2 < 0.0f) {
                        var_fv1_2 = temp_fv0_2 + 360.0f;
                    } else {
                        var_fv1_2 = temp_fv0_2;
                    }
                    var_fa1 = var_fv1_2;
                }
                spA8 = M2C_BITWISE(s32, var_fa1);
                if (func_802452AC(M2C_BITWISE(s32, spA0), M2C_BITWISE(s32, var_fa1)) != 0) {
                    if ((spBC > 20.0f) && (spBC < 35.0f)) {
                        spD4 = 2.0f;
                    }
                    if ((spBC >= 35.0f) && (spBC < 60.0f)) {
                        spD4 = 4.0f;
                    }
                    if (spBC >= 60.0f) {
                        spD4 = 8.5f;
                    }
                    if (spD4 > 0.0f) {
                        temp_fv0_3 = (f64) var_fa1;
                        if (((temp_fv0_3 >= 0.0) && (temp_fv0_3 < 22.5)) || ((temp_fv0_3 >= 337.5) && (temp_fv0_3 < 360.0))) {
                            sp120 = 0x80;
                            spD0 = 0.0f;
                        }
                        var_v0 = sp120;
                        var_fv1_3 = spD0;
                        if ((temp_fv0_3 >= 22.5) && (temp_fv0_3 < 67.5)) {
                            var_fv1_3 = 45.0f;
                            var_v0 = 0x60;
                        }
                        if ((temp_fv0_3 >= 67.5) && (temp_fv0_3 < 112.5)) {
                            var_fv1_3 = 90.0f;
                            var_v0 = 0x40;
                        }
                        if ((temp_fv0_3 >= 112.5) && (temp_fv0_3 < 157.5)) {
                            var_fv1_3 = 135.0f;
                            var_v0 = 0x20;
                        }
                        if ((temp_fv0_3 >= 157.5) && (temp_fv0_3 < 202.5)) {
                            var_fv1_3 = 180.0f;
                            var_v0 = 0;
                        }
                        if ((temp_fv0_3 >= 202.5) && (temp_fv0_3 < 247.5)) {
                            var_fv1_3 = 225.0f;
                            var_v0 = 0xE0;
                        }
                        if ((temp_fv0_3 >= 247.5) && (temp_fv0_3 < 292.5)) {
                            var_fv1_3 = 270.0f;
                            var_v0 = 0xC0;
                        }
                        if ((temp_fv0_3 >= 292.5) && (temp_fv0_3 < 337.5)) {
                            var_fv1_3 = 315.0f;
                            var_v0 = 0xA0;
                        }
                        sp120 = var_v0;
                        spD0 = var_fv1_3;
                        if (func_80244BA4(M2C_BITWISE(s32, spBC), M2C_BITWISE(s32, var_fa1)) == 0) {
                            func_8024A6B4(arg0, var_fv1_3);
                        }
                        if (func_80243EB4(arg0, 4) != 0) {
                            spD4 *= 0.5f;
                        }
                        if (func_80243EB4(arg0, 1) != 0) {
                            spD4 *= 4.0f;
                        }
                        if (func_80243EB4(arg0, 0x200) != 0) {
                            spD4 *= 0.8f;
                        }
                        if (func_8024D50C((void *) sp40->unk2C) != 0) {
                            spD4 *= 0.8f;
                        }
                    }
                }
            }
            if ((func_80243EB4(arg0, 0x20) != 0) && (func_80244BA4(arg0, 0x20) == 0)) {
                temp_ft3 = 8.5f - spD4;
                spD4 = temp_ft3;
                if (temp_ft3 < 2.0f) {
                    spD4 = 0.0f;
                }
                if (sp120 == 1) {
                    temp_v0_13 = func_8024D41C(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20));
                    sp120 = temp_v0_13;
                    if (temp_v0_13 == -1) {
                        sp120 = 1;
                        spD4 = 0.0f;
                    }
                }
            }
            if ((M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) - func_8026E938(M2C_FIELD(temp_v0, void **, 0x40))) > 500.0f) {
                if (func_80244BA4(arg0, 0x400000) == 0) {
                    if ((M2C_FIELD(temp_v0, f32 *, 0x6C) > 2.0f) && (sp40->unk50 == 0) && (M2C_FIELD(temp_v0, s32 *, 8) & 0x01000000)) {
                        func_8026C660(0x1B);
                        sp40->unk50 = 1;
                    }
                }
            }
            if ((M2C_FIELD(temp_v0, f32 *, 0x6C) > 32.0f) && (func_802452AC(arg0, 0x60000A) != 0)) {
                func_8024D374(arg0);
            }
            if (M2C_FIELD(temp_v0, f32 *, 0x6C) == 0.0f) {
                if (func_80244BA4(arg0, 8) != 0) {
                    func_8024D20C((s16) arg0);
                }
            }
            if (func_80244BA4(arg0, 0x4000) != 0) {
                spD4 *= 0.3f;
            }
            if (func_802452AC(arg0, 0x31C2) != 0) {
                if (spD4 > 0.0f) {
                    if (spD4 < 4.0f) {
                        if (func_80244BA4(arg0, 0x8000) == 0) {
                            if (func_802443CC(arg0) != 1) {
                                func_802444B8(arg0, 1);
                            }
                        } else if (func_802443CC(arg0) != 0xD) {
                            func_802444B8(arg0, 0xD);
                        }
                    }
                }
                if (spD4 >= 4.0f) {
                    if (spD4 < 8.5f) {
                        if (func_80244BA4(arg0, 0x8000) == 0) {
                            if (func_802443CC(arg0) != 2) {
                                func_802444B8(arg0, 2);
                            }
                        } else if (func_802443CC(arg0) != 0xE) {
                            func_802444B8(arg0, 0xE);
                        }
                    }
                }
                if (spD4 >= 8.5f) {
                    if (func_80244BA4(arg0, 0x8000) == 0) {
                        if (func_802443CC(arg0) != 3) {
                            func_802444B8(arg0, 3);
                        }
                    } else if (func_802443CC(arg0) != 0xF) {
                        func_802444B8(arg0, 0xF);
                    }
                }
                if (spD4 == 0.0f) {
                    temp_v0_14 = func_802443CC(arg0);
                    switch (temp_v0_14) {
                    case 1:
                    case 2:
                    case 3:
                        func_8024D108(arg0, temp_v0_14);
                        func_802444B8(arg0, 0);
                        break;
                    case 13:
                    case 14:
                    case 15:
                        func_8024D108(arg0, temp_v0_14);
                        func_802444B8(arg0, 0xC);
                        break;
                    }
                }
                func_8024CEB8(arg0);
            }
            if (M2C_FIELD(temp_v0, s32 *, 8) & 0x20000) {
                func_802727D8(sp40->unk40);
            } else {
                if (func_80244BA4(arg0, 0x80) != 0) {
                    func_8024CC58((s16) arg0);
                }
                if (func_80244BA4(arg0, 0x40) != 0) {
                    func_8024C884(M2C_BITWISE(s32, spBC), M2C_BITWISE(f32, arg0), M2C_BITWISE(s32, spBC));
                }
                if (func_80244BA4(arg0, 0x200) != 0) {
                    func_8024C804(arg0);
                }
                if (func_80244BA4(arg0, 0x100) != 0) {
                    func_8024C53C(arg0, (arg0 * 0xC) + &D_802ACF68);
                }
                if ((func_80244BA4(arg0, 0x02000000) == 0) && (func_80244BA4(arg0, 0x1000) != 0)) {
                    func_8024C334(arg0, sp74, sp124, &spB4);
                }
                if (func_80244BA4(arg0, 0x02000000) == 0) {
                    if (func_80244BA4(arg0, 0x10000) != 0) {
                        func_8024C29C(arg0);
                    }
                }
                if (func_80244BA4(arg0, 0x2000) != 0) {
                    func_8024C1E8(arg0);
                }
                if (func_80244BA4(arg0, 0x20000) != 0) {
                    func_8024C0D8(arg0);
                }
                if (func_80244BA4(arg0, 0x8000) != 0) {
                    func_8024C04C((s16) arg0);
                }
                if (func_80244BA4(arg0, 0x04000000) != 0) {
                    func_8024BFE0(arg0);
                }
                if (func_80243EB4(arg0, 0x400) != 0) {
                    func_8024BF04(arg0);
                }
                if (func_80244BA4(arg0, 0x08000000) != 0) {
                    func_8024BD1C(arg0);
                }
                if (func_80243EB4(arg0, 0x10000) != 0) {
                    func_8024BC94(arg0);
                }
                if (func_80243EB4(arg0, 0x20000) != 0) {
                    func_8024BC20(arg0);
                }
                if (func_80243EB4(arg0, 0x200000) != 0) {
                    func_8024BBA4(arg0);
                }
                if (func_80243EB4(arg0, 2) != 0) {
                    func_8024B444(arg0, sp58);
                    spD4 = sp58[0];
                    sp120 = sp58[1];
                }
                if (func_80243EB4(arg0, 0x10) != 0) {
                    func_8024B1CC((s16) arg0);
                }
                if (func_80243EB4(arg0, 0x100) != 0) {
                    func_8024B028(arg0);
                }
                if (func_80243EB4(arg0, 0x40) != 0) {
                    func_8024AFD4(arg0);
                }
                if (func_80243EB4(arg0, 0x2000) != 0) {
                    func_8024AF24(arg0, &sp90);
                }
                if ((func_80244BA4(arg0, 0x800) != 0) && (func_80244BA4(arg0, 0x80000) == 0)) {
                    if (func_80243EB4(arg0, 0x8000) != 0) {
                        if (func_80244BA4(arg0, 0x400) == 0) {
                            func_8024ABA8(arg0);
                        }
                    } else {
                        func_8024ABA8(arg0);
                    }
                }
                if ((func_80244BA4(arg0, 0x80000) != 0) && (func_80244BA4(arg0, 0x400) == 0)) {
                    func_80249AD4(D_802AC980[arg0]);
                }
                if (func_80243EB4(arg0, 0x2000) != 0) {
                    sp6C = func_802443F4(sp40->unkA8);
                }
                if (func_802452AC(arg0, 0x600000) != 0) {
                    if (sp120 != 1) {
                        func_80291944(temp_v0, sp120, spD4);
                    }
                }
                temp_t6 = sp11C & 0x1C00;
                if (temp_t6 != 0) {
                    func_8027F858((s32) temp_v0, temp_t6 >> 0xA);
                }
                if ((func_802452AC(arg0, 0x600000) != 0) && (sp40->unk48 == 1)) {
                    func_80230914(temp_v0);
                }
                temp_a2_3 = sp40->unk2C;
                if (temp_a2_3 != 0) {
                    func_80231434((void *) temp_a2_3);
                }
                if (func_80243EB4(arg0, 0x2000) != 0) {
                    func_80231434(sp6C);
                }
                sp110 = 0;
                D_802AC9E4 = arg0;
                temp_a2_4 = sp40->unk2C;
                if (temp_a2_4 != 0) {
                    func_8022F808((void *) temp_a2_4, sp84);
                    sp114 = 0;
                    var_a2 = sp40->unk2C;
                    var_v1 = M2C_FIELD(var_a2, s32 *, 8);
                    var_t4 = var_v1 & 2;
                    if (var_v1 & 1) {
                        sp114 = func_802909FC(var_a2);
                        var_a2 = sp40->unk2C;
                        var_v1 = M2C_FIELD(var_a2, s32 *, 8);
                        var_t4 = var_v1 & 2;
                    }
                    if (var_t4 != 0) {
                        sp114 = func_802909FC(var_a2);
                        var_a2 = sp40->unk2C;
                        var_v1 = M2C_FIELD(var_a2, s32 *, 8);
                    }
                    if (var_v1 & 4) {
                        sp114 = func_802909FC(var_a2);
                        var_a2 = sp40->unk2C;
                        var_v1 = M2C_FIELD(var_a2, s32 *, 8);
                    }
                    if (var_v1 & 8) {
                        sp114 = func_802909FC(var_a2);
                    }
                    if (sp114 != 0) {
                        temp_v0_15 = M2C_FIELD(temp_v0, void **, 0x40);
                        M2C_FIELD(temp_v0_15, f32 *, 0x10) = (f32) (M2C_FIELD(temp_v0_15, f32 *, 0x10) + (M2C_FIELD(M2C_FIELD(sp40->unk2C, void **, 0x40), f32 *, 0x10) - sp84[0]));
                        temp_v0_16 = M2C_FIELD(temp_v0, void **, 0x40);
                        M2C_FIELD(temp_v0_16, f32 *, 0x18) = (f32) (M2C_FIELD(temp_v0_16, f32 *, 0x18) + (M2C_FIELD(M2C_FIELD(sp40->unk2C, void **, 0x40), f32 *, 0x18) - sp84[2]));
                        sp3C = func_80245150;
                        temp_fv0_4 = func_8026EAF8(temp_v0);
                        if (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) < temp_fv0_4) {
                            spC0 = temp_fv0_4;
                            func_80244354(arg0, 8, 0);
                            M2C_FIELD(temp_v0, f32 *, 0x6C) = 0.0f;
                        }
                        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = temp_fv0_4;
                        func_8022F808(temp_v0, &sp78);
                        temp_a1 = (f32 *)((u8 *)temp_v0 + 0x58);
                        sp2C = temp_a1;
                        if (M2C_BITWISE(f32, func_8022DF68((s32) &sp78, (s32) temp_a1)) >= 100.0f) {
                            func_80232BA0(sp2C, temp_v0);
                        }
                        if (func_802909FC((s32) temp_v0) != 0) {
                            if ((M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) < M2C_FIELD(temp_v0, f32 *, 0x5C)) && (M2C_FIELD(temp_v0, f32 *, 0x68) < M2C_FIELD(temp_v0, f32 *, 0x6C))) {
                                func_80244C30((s16) arg0, 1);
                                func_802444B8(arg0, 0);
                            }
                            M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = (f32) sp40->unkC;
                            func_80244354(arg0, 0x08000000, 0);
                        }
                        sp110 = 1;
                    }
                }
                if (func_80243EB4(arg0, 0x2000) != 0) {
                    sp3C = func_80245150;
                    temp_v0_17 = func_802443F4(sp40->unkA8);
                    sp6C = temp_v0_17;
                    func_8022F808(temp_v0_17, sp84);
                    temp_v0_18 = func_802909FC((s32) sp6C);
                    spF0 = temp_v0_18;
                    if (temp_v0_18 != 0) {
                        temp_v0_19 = M2C_FIELD(temp_v0, void **, 0x40);
                        M2C_FIELD(temp_v0_19, f32 *, 0x10) = (f32) (M2C_FIELD(temp_v0_19, f32 *, 0x10) + (M2C_FIELD(M2C_FIELD(sp6C, void **, 0x40), f32 *, 0x10) - sp84[0]));
                        temp_v0_20 = M2C_FIELD(temp_v0, void **, 0x40);
                        M2C_FIELD(temp_v0_20, f32 *, 0x18) = (f32) (M2C_FIELD(temp_v0_20, f32 *, 0x18) + (M2C_FIELD(M2C_FIELD(sp6C, void **, 0x40), f32 *, 0x18) - sp84[2]));
                        sp2C = (f32 *)((u8 *)temp_v0 + 0x58);
                        temp_fv0_5 = func_8026EAF8(temp_v0);
                        if (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) < temp_fv0_5) {
                            spC0 = temp_fv0_5;
                            func_80244354(arg0, 8, 0);
                            M2C_FIELD(temp_v0, f32 *, 0x6C) = 0.0f;
                        }
                        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = temp_fv0_5;
                        func_8022F808(temp_v0, &sp78);
                        if (M2C_BITWISE(f32, func_8022DF68((s32) &sp78, (s32) sp2C)) >= 150.0f) {
                            func_80232BA0(sp2C, temp_v0);
                        }
                        if (func_802909FC((s32) temp_v0) != 0) {
                            M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = (f32) sp40->unkC;
                            func_80244354(arg0, 0x08000000, 0);
                        }
                        sp110 += 1;
                    }
                }
                if (sp110 == 0) {
                    func_802909FC((s32) temp_v0);
                }
                func_80249A30(arg0);
                if (func_80244BA4(arg0, 1) != 0) {
                    func_802498D4(arg0, spD4);
                }
                func_8026E938(M2C_FIELD(temp_v0, void **, 0x40));
                D_802ACF60 = func_8023A840();
                if ((M2C_FIELD(temp_v0, f32 *, 0x5C) - M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14)) > 15.0f) {
                    func_80244354(arg0, 0x4000, 1);
                } else if (func_80244BA4(arg0, 0x4000) != 0) {
                    func_80244354(arg0, 0x4000, 0);
                }
                temp_v0_21 = func_8022F4AC((s32) temp_v0, 2, sp40->unk4C);
                if ((temp_v0_21 != 0) && (M2C_FIELD(temp_v0_21, s32 *, 0x44) == 0) && (func_80244BA4(arg0, 1) == 0) && (M2C_FIELD(temp_v0, f32 *, 0x6C) == 0.0f)) {
                    func_802497D8(arg0);
                }
                temp_v0_22 = func_8022F4AC((s32) temp_v0, 0x1E00, sp40->unk4C);
                if (temp_v0_22 != 0) {
                    func_80249648(arg0, (UnkObj *) temp_v0_22, M2C_FIELD(temp_v0_22, s32 *, 8));
                }
                func_8024891C(arg0);
                sp74 = func_8022F4AC((s32) temp_v0, 0x10, sp40->unk4C);
                if ((func_80243EB4(arg0, 0x2000) != 0) && (sp74 == func_802443F4(sp40->unkA8))) {
                    sp74 = 0;
                }
                if (sp74 != 0) {
                    temp_v0_23 = (arg0 * 0xC) + &D_802ACF68;
                    M2C_FIELD(temp_v0_23, f32 *, 0) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) - M2C_FIELD(temp_v0, f32 *, 0x58));
                    M2C_FIELD(temp_v0_23, f32 *, 4) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) - M2C_FIELD(temp_v0, f32 *, 0x5C));
                    M2C_FIELD(temp_v0_23, f32 *, 8) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) - M2C_FIELD(temp_v0, f32 *, 0x60));
                    func_80232BA0((f32 *)((u8 *)temp_v0 + 0x58), temp_v0);
                    if (func_80244BA4(arg0, 2) != 0) {
                        func_8024878C(arg0);
                        M2C_FIELD(temp_v0, f32 *, 0x68) = 0.0f;
                        M2C_FIELD(temp_v0, f32 *, 0x70) = 1.6333334f;
                    }
                    if ((M2C_FIELD(temp_v0, f32 *, 0x6C) > 0.0f) && (M2C_FIELD(temp_v0, void **, 0x44) == NULL)) {
                        if (M2C_FIELD(M2C_FIELD(sp74, void **, 0x40), f32 *, 0x14) < M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14)) {
                            if (func_80244BA4(arg0, 2) != 0) {
                                var_fa0 = sp40->unkC + 180.0f;
                                if (var_fa0 >= 360.0f) {
                                    var_fa0 -= 360.0f;
                                }
                            } else {
                                var_fa0 = sp40->unkC;
                            }
                            sp40->unk40 = func_802700EC((s32) temp_v0, sp74, func_80243F50(var_fa0), 0x41000000);
                            func_80244354(arg0, 0x2100, 0);
                            if ((func_80244BA4(arg0, 0x80) != 0) || (func_80244BA4(arg0, 0x40) != 0)) {
                                func_80244C30((s16) arg0, 1);
                            }
                            func_80244354(arg0, 0x400020, 1);
                            if (func_80244BA4(arg0, 0x8000) == 0) {
                                func_802444B8(arg0, 0x13);
                            } else {
                                func_802444B8(arg0, 0x14);
                            }
                            if (func_80243EB4(arg0, 0x2000) != 0) {
                                func_80247F90(arg0);
                            }
                        }
                    }
                    if ((func_80244BA4(arg0, 0x8000) == 0) || (sp114 == 0)) {
                        if (func_80243EB4(arg0, 0x2000) != 0) {
                            if (spF0 != 0) {
                                goto block_351;
                            }
                        }
                    } else {
block_351:
                        if (func_80244BA4(arg0, 0x08000000) != 0) {
                            func_80244354(arg0, 0x08000000, 0);
                            M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = M2C_BITWISE(f32, sp40->unk64);
                        }
                    }
                }
                temp_a2_5 = sp40->unk2C;
                if ((temp_a2_5 != NULL) && (M2C_FIELD(temp_a2_5, s32 *, 8) & 0x10)) {
                    func_80231434(temp_a2_5);
                    sp74 = func_8022F4AC(sp40->unk2C, 0x10, (s32) temp_v0);
                    if (func_80244BA4(arg0, 0x400) != 0) {
                        sp74 = 0;
                    }
                    if (sp74 != 0) {
                        temp_a2_6 = sp40->unk2C;
                        sp2C = (f32 *)((u8 *)temp_v0 + 0x58);
                        func_80232BA0(temp_a2_6 + 0x58, (void *) temp_a2_6);
                        func_80232BA0(sp2C, temp_v0);
                        if (func_80244BA4(arg0, 0x08000000) != 0) {
                            func_80244354(arg0, 0x08000000, 0);
                            M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = M2C_BITWISE(f32, sp40->unk64);
                        }
                        if (M2C_FIELD(temp_v0, f32 *, 0x6C) > 0.0f) {
                            func_80244C30((s16) arg0, 0);
                        }
                    }
                }
                if (func_80243EB4(arg0, 0x2000) != 0) {
                    temp_v0_24 = func_802443F4(sp40->unkA8);
                    sp6C = temp_v0_24;
                    func_80231434(temp_v0_24);
                    sp74 = func_8022F4AC((s32) sp6C, 0x10, (s32) temp_v0);
                    if (func_80244BA4(arg0, 0x400) != 0) {
                        sp74 = 0;
                    }
                    if (sp74 != 0) {
                        if ((M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) < M2C_FIELD(temp_v0, f32 *, 0x5C)) && (M2C_FIELD(temp_v0, f32 *, 0x68) < M2C_FIELD(temp_v0, f32 *, 0x6C))) {
                            func_80247F90(arg0);
                        } else {
                            sp2C = (f32 *)((u8 *)temp_v0 + 0x58);
                            func_80232BA0((f32 *)((u8 *)sp6C + 0x58), sp6C);
                            func_80232BA0(sp2C, temp_v0);
                            if (func_80244BA4(arg0, 0x08000000) != 0) {
                                func_80244354(arg0, 0x08000000, 0);
                                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = M2C_BITWISE(f32, sp40->unk64);
                                if (M2C_FIELD(temp_v0, f32 *, 0x6C) > 0.0f) {
                                    func_80247F90(arg0);
                                }
                            }
                        }
                    }
                }
                if (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) < 0.0f) {
                    func_80270770((s16) arg0, 1);
                }
            }
            if ((func_80244BA4(arg0, 0x400) == 0) && (func_80244BA4(arg0, 8) == 0)) {
                if (func_80244BA4(arg0, 0x2000) == 0) {
                    func_8024857C(arg0);
                }
            }
            sp40->unk64 = sp40->unk60;
        }
    }
}

void func_8024D8C4(f32 *arg0) {
    f32 spE4;
    f32 spDC;
    f32 spD4;
    UnkObj *spD0;
    f32 spC4[2];
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spAC[3];
    f32 spA4;
    f32 spA0;
    s32 sp88[3];
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    UnkStruct_800AEDF0 *sp2C;
    UnkModel *temp_v0_2;
    UnkObj *temp_a0;
    UnkStruct_800AEDF0 *temp_t4;
    UnkStruct_800AEDF0 *temp_v1;
    UnkStruct_800AEDF0 *var_t4;
    f32 var_ft4;
    f32 var_ft5;
    f32 var_ft5_2;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 *temp_v0_3;
    s32 temp_a3;
    s32 temp_t7;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    temp_v0 = D_802AC968[func_80243DDC()];
    temp_a3 = temp_v0 & 1;
    sp84 = (temp_v0 >> 1) & 1;
    if (temp_a3 != 0) {
        M2C_FIELD(arg0, s32 *, 8) = (s32) D_802AC95C;
    } else {
        M2C_FIELD(arg0, s32 *, 8) = 3;
    }
    M2C_FIELD(arg0, f32 *, 0xC) = 0.0f;
    temp_v1 = &D_800AEDF0[func_80243DDC()];
    temp_a0 = temp_v1->unk28;
    sp2C = temp_v1;
    sp7C = func_80243DDC();
    sp80 = temp_a3;
    spD0 = temp_a0;
    func_8022F808(temp_a0, spC4);
    spB8 = D_802ACA28;
    if ((D_802AC8BC == 0x100) || (D_802AC8BC == 0x200)) {
        spBC = D_802ACA2C;
    } else {
        spBC = spC4[1];
    }
    spC0 = D_802ACA8C;
    spD4 = M2C_FIELD(spD0->unk40, f32 *, 0x20);
    func_8022FF58(spC4, &spB8, &spA0);
    spA4 -= 90.0f;
    var_ft5 = spD4;
    var_fv1 = M2C_BITWISE(f32, func_8022DF68((s32) spC4, (s32) &spB8));
    if (sp80 != 0) {
        M2C_FIELD(arg0, s32 *, 4) = (s32) D_802AC8BC;
    } else {
        spE4 = var_fv1;
        M2C_FIELD(arg0, s32 *, 4) = func_80243F50(spA0);
    }
    if (!(D_802ACA24 < var_fv1)) {
        var_v0 = 0;
        if ((sp2C->unk10 & 0x4000) == 0x4000) {
            var_v0 = 1;
        }
        if (var_v0 != 0) {
            goto block_14;
        }
        M2C_FIELD(arg0, f32 *, 0) = var_fv1;
    } else {
block_14:
        M2C_FIELD(arg0, f32 *, 0) = D_802ACA24;
    }
    var_v1 = 0;
    if ((sp2C->unk10 & 0x2000) == 0x2000) {
        var_v1 = 1;
    }
    if (var_v1 != 0) {
        M2C_FIELD(arg0, f32 *, 0) = 0.0f;
    }
    if (M2C_FIELD(arg0, s32 *, 8) != 3) {
        spE4 = var_fv1;
        spD4 = var_ft5;
        func_8024D5D0(arg0);
    }
    if (((D_802AC8BC != 0x100) && (D_802AC8BC != 0x200)) || (sp80 != 1)) {
        if (var_fv1 >= 1.0f) {
            spE4 = var_fv1;
            spD4 = var_ft5;
            M2C_FIELD(arg0, s32 *, 4) = func_80243F50(spA0);
        }
    }
    if (var_fv1 <= 1.0f) {
        if (sp80 == 0) {
            var_ft4 = 0.0f;
            var_fv1_2 = 0.0f;
            spDC = 0.0f;
            switch (D_802AC8BC) {                   /* switch 1; irregular */
            case 0x0:                               /* switch 1 */
                var_ft5 = 180.0f;
                var_ft4 = (f32) -D_802AC8C4;
                break;
            case 0x80:                              /* switch 1 */
                var_ft5 = 0.0f;
                var_ft4 = (f32) D_802AC8C4;
                break;
            case 0xC0:                              /* switch 1 */
                var_ft5 = 270.0f;
                var_fv1_2 = (f32) -D_802AC8C4;
                break;
            case 0x40:                              /* switch 1 */
                var_ft5 = 90.0f;
                var_fv1_2 = (f32) D_802AC8C4;
                break;
            case 0x20:                              /* switch 1 */
                var_ft5 = 135.0f;
                var_fv1_2 = (f32) D_802AC8C4;
                var_ft4 = (f32) -D_802AC8C4;
                break;
            case 0xE0:                              /* switch 1 */
                var_ft5 = 225.0f;
                var_ft4 = (f32) -D_802AC8C4;
                var_fv1_2 = var_ft4;
                break;
            case 0x60:                              /* switch 1 */
                var_ft5 = 45.0f;
                var_ft4 = (f32) D_802AC8C4;
                var_fv1_2 = var_ft4;
                break;
            case 0xA0:                              /* switch 1 */
                var_ft5 = 315.0f;
                var_ft4 = (f32) D_802AC8C4;
                var_fv1_2 = (f32) -D_802AC8C4;
                break;
            case 0x100:                             /* switch 1 */
                spDC = (f32) D_802AC8C4;
                break;
            case 0x200:                             /* switch 1 */
                spDC = (f32) -D_802AC8C4;
                break;
            }
            temp_v0_2 = spD0->unk40;
            spD4 = var_ft5;
            func_8026DCAC(temp_v0_2->unk10 + (var_fv1_2 * 100.0f), temp_v0_2->unk14 + (spDC * 100.0f), temp_v0_2->unk18 + (var_ft4 * 100.0f), sp88, 2);
            func_8026E338((f32) sp88[0], (f32) sp88[1], (f32) sp88[2], spAC, 0);
            D_802ACA28 = spAC[0];
            D_802ACA2C = spAC[1];
            D_802ACA8C = spAC[2];
            func_8024A6B4(sp7C, spD4);
            var_ft5_2 = spD4;
        } else {
            switch (D_802AC8BC) {                   /* switch 2; irregular */
            case 0x0:                               /* switch 2 */
                var_ft5 = 180.0f;
                break;
            case 0x80:                              /* switch 2 */
                var_ft5 = 0.0f;
                break;
            case 0xC0:                              /* switch 2 */
                var_ft5 = 270.0f;
                break;
            case 0x40:                              /* switch 2 */
                var_ft5 = 90.0f;
                break;
            case 0x20:                              /* switch 2 */
                var_ft5 = 135.0f;
                break;
            case 0xE0:                              /* switch 2 */
                var_ft5 = 225.0f;
                break;
            case 0x60:                              /* switch 2 */
                var_ft5 = 45.0f;
                break;
            case 0xA0:                              /* switch 2 */
                var_ft5 = 315.0f;
                break;
            }
            spD0->unk40->unk10 = D_802ACA28;
            if ((D_802AC8BC == 0x100) || (D_802AC8BC == 0x200)) {
                spD0->unk40->unk14 = D_802ACA2C;
            }
            spD0->unk40->unk18 = D_802ACA8C;
            spD4 = var_ft5;
            func_80244354(sp7C, 0x420, 0);
            var_v1_2 = 0;
            if ((sp2C->unk10 & 0x02000000) == 0x02000000) {
                var_v1_2 = 1;
            }
            if (var_v1_2 == 0) {
                spD4 = var_ft5;
                func_80244354(sp7C, 0x10000, 0);
            }
            sp2C->unk48 = 1;
            M2C_FIELD(spD0, f32 *, 0x70) = 1.6333334f;
            spD4 = var_ft5;
            func_8024D108(sp7C, sp2C->unk44);
            var_ft5_2 = var_ft5;
        }
        M2C_FIELD(arg0, f32 *, 0) = 0.0f;
        spD0->unk40->unk10 = spB8;
        spD0->unk40->unk18 = spC0;
        if (D_802AC8BC != 0x100) {
            if (D_802AC8BC != 0x200) {
                M2C_FIELD(spD0->unk40, f32 *, 0x20) = var_ft5_2;
            }
        }
        sp80 += 1;
    }
    temp_t7 = sp7C * 4;
    temp_t4 = temp_t7 + &D_802ACA10;
    D_802AC968[(temp_t7) / 4] = (sp84 * 2) + sp80;
    sp2C = temp_t4;
    var_v1_3 = temp_t4->unk0;
    var_t4 = temp_t4;
    if (!(var_v1_3 & 3)) {
        func_8022F808(spD0, spC4);
        temp_v0_3 = func_8023A840();
        D_802ACF60 = temp_v0_3;
        if (!(*temp_v0_3 & 2)) {
            func_802775D8((s32) spC4);
        }
        func_80282934();
        var_v1_3 = M2C_BITWISE(s32, sp2C->unk0);
        var_t4 = sp2C;
    }
    var_t4->unk0 = M2C_BITWISE(f32, (var_v1_3 + 1));
}

void func_8024D5D0(f32 *arg0) {
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp28;
    f32 temp_ft4;
    f32 var_fa0;
    f32 var_ft5;
    f64 temp_fv0;
    f64 temp_fv0_2;
    f64 temp_fv1;
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    temp_v1 = M2C_FIELD(arg0, s32 *, 8);
    sp6C = M2C_FIELD(arg0, f32 *, 0);
    switch (temp_v0) {                              /* switch 1; irregular */
    default:                                        /* switch 1 */
        var_fa0 = sp64;
        break;
    case 0x0:                                       /* switch 1 */
        var_fa0 = 180.0f;
        break;
    case 0x20:                                      /* switch 1 */
        var_fa0 = 135.0f;
        break;
    case 0x40:                                      /* switch 1 */
        var_fa0 = 90.0f;
        break;
    case 0x60:                                      /* switch 1 */
        var_fa0 = 45.0f;
        break;
    case 0x80:                                      /* switch 1 */
        var_fa0 = 0.0f;
        break;
    case 0xA0:                                      /* switch 1 */
        var_fa0 = 315.0f;
        break;
    case 0xC0:                                      /* switch 1 */
        var_fa0 = 270.0f;
        break;
    case 0xE0:                                      /* switch 1 */
        var_fa0 = 225.0f;
        break;
    }
    switch (temp_v1) {                              /* switch 2 */
    case 1:                                         /* switch 2 */
        sp68 = 0.0f;
        var_fa0 = 0.0f;
        break;
    case 2:                                         /* switch 2 */
        sp68 = 45.0f;
        break;
    case 3:                                         /* switch 2 */
        sp68 = 90.0f;
        break;
    case 4:                                         /* switch 2 */
        sp68 = 135.0f;
        break;
    case 5:                                         /* switch 2 */
        var_fa0 = 0.0f;
        sp68 = 180.0f;
        break;
    }
    sp64 = var_fa0;
    sp28 = func_80234434(var_fa0);
    sp48 = func_80234434(sp68) * (sp6C * sp28);
    sp44 = func_80234408(sp68) * sp6C;
    sp28 = func_80234408(var_fa0);
    temp_ft4 = func_80234434(sp68) * (sp6C * sp28);
    temp_fv1 = (f64) sp48;
    var_ft5 = temp_ft4;
    if ((temp_fv1 < 0.01) && (temp_fv1 > -0.01)) {
        sp48 = 0.0f;
    }
    temp_fv0 = (f64) sp44;
    if ((temp_fv0 < 0.01) && (temp_fv0 > -0.01)) {
        sp44 = 0.0f;
    }
    temp_fv0_2 = (f64) temp_ft4;
    if ((temp_fv0_2 < 0.01) && (temp_fv0_2 > -0.01)) {
        var_ft5 = 0.0f;
    }
    sp58 = 0.0f;
    sp5C = 0.0f;
    sp60 = 0.0f;
    sp50 = 0.0f;
    sp54 = var_ft5;
    sp4C = sp48;
    func_8022FF58(&sp58, &sp4C, &sp64);
    M2C_FIELD(arg0, s32 *, 4) = func_80243F50(sp64);
    M2C_FIELD(arg0, f32 *, 0) = sp6C;
    M2C_FIELD(arg0, f32 *, 0xC) = sp44;
}

void func_8024D540(s32 arg0, f32 *arg1) {
    UnkObj *temp_a2;
    UnkStruct_800AEDF0 *temp_v1;

    temp_v1 = &D_800AEDF0[arg0];
    M2C_FIELD(arg1, f32 *, 0) = D_802ACA44;
    M2C_FIELD(arg1, s32 *, 4) = (s32) temp_v1->unkA0;
    temp_a2 = temp_v1->unk28;
    if ((M2C_FIELD(temp_a2, f32 *, 0x68) == 0.0f) && (temp_a2->unk6C == 0.0f)) {
        func_8024878C((s32) temp_a2);
    }
}

s32 func_8024D50C(void *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if ((arg0 != NULL) && (M2C_FIELD(arg0, s32 *, 8) & 4) && (D_802AC5D0 & 4)) {
        var_v1 = 1;
    }
    return var_v1;
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
    s32 temp_a0;
    s32 var_v1;
    s32 var_v1_2;

    func_80244354(0x100, 0, 0);
    temp_a0 = D_800AEDF0[arg0].unk10;
    var_v1 = 0;
    if ((temp_a0 & 0x1000) == 0x1000) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        var_v1_2 = 0;
        if (!(temp_a0 & 0x8080)) {
            var_v1_2 = 1;
        }
        if (var_v1_2 != 0) {
            func_802444B8(arg0, 0xA);
        } else {
            func_802444B8(arg0, 0x12);
        }
        func_80244354(arg0, 8, 1);
    }
}

void func_8024D20C(s16 arg0) {
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
    UnkObj *sp34;
    s32 sp30;
    s32 sp18;
    UnkObj *temp_a3;
    UnkStruct_800AEDF0 *temp_v1;
    f32 temp_fv0;
    f32 var_fv1;
    s32 temp_t0;
    s32 temp_v0;
    s32 var_a1;

    temp_v1 = &D_800AEDF0[arg0];
    temp_t0 = arg0 * 4;
    temp_a3 = temp_v1->unk28;
    D_802AC9F8[(temp_t0) / 4] = arg1;
    temp_v0 = temp_v1->unk44;
    var_fv1 = 0.0f;
    switch (temp_v0) {
    case 1:
    case 2:
    case 3:
        var_a1 = 0;
        break;
    case 13:
    case 14:
    case 15:
        var_a1 = 1;
        break;
    default:
        var_a1 = -1;
        break;
    }
    if (var_a1 != -1) {
        sp18 = temp_t0;
        sp34 = temp_a3;
        sp30 = var_a1;
        temp_fv0 = func_80229D3C(temp_a3->unk40, var_a1);
        var_fv1 = M2C_FIELD((M2C_FIELD(M2C_FIELD(temp_a3->unk40, void **, 0x48), s32 *, 4) + (var_a1 * 0xC)), f32 *, 4) + 1.0f;
        if (temp_fv0 <= var_fv1) {
            var_fv1 -= temp_fv0;
        }
    }
    D_802ACA78[(temp_t0) / 4] = var_fv1;
}

void func_8024CEB8(s32 arg0) {
    UnkObj *sp44;
    f32 sp2C[3];
    UnkObj *temp_a3;
    UnkStruct_800AEDF0 *temp_v1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    s32 *temp_v0_2;
    s32 temp_v0;
    s32 var_a2;
    s32 var_v1;

    temp_v1 = &D_800AEDF0[arg0];
    temp_v0 = temp_v1->unk44;
    temp_a3 = temp_v1->unk28;
    var_a2 = 0;
    switch (temp_v0) {
    case 1:
    case 13:
        temp_fv0 = (f32) (s32) M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_a3->unk40, void **, 0x48), void **, 4), f32 *, 0x10);
        if ((temp_fv0 == 12.0f) || (temp_fv0 == 36.0f)) {
block_10:
            var_a2 = 1;
        }
        break;
    case 2:
    case 14:
        temp_fv0_2 = (f32) (s32) M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_a3->unk40, void **, 0x48), void **, 4), f32 *, 0x10);
        if ((temp_fv0_2 == 0.0f) || (temp_fv0_2 == 20.0f)) {
            goto block_10;
        }
        break;
    case 3:
    case 15:
        temp_fv0_3 = (f32) (s32) M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_a3->unk40, void **, 0x48), void **, 4), f32 *, 0x10);
        if ((temp_fv0_3 == 0.0f) || (temp_fv0_3 == 16.0f)) {
            goto block_10;
        }
        break;
    }
    if (var_a2 != 0) {
        sp44 = temp_a3;
        temp_v0_2 = func_8023A840();
        D_802ACF60 = temp_v0_2;
        var_v1 = M2C_FIELD(temp_v0_2, s32 *, 4);
        if ((var_v1 == 3) && (M2C_FIELD(temp_v0_2, s32 *, 8) == 0)) {
            sp44 = temp_a3;
            func_8026C660(0x30);
            var_v1 = M2C_FIELD(D_802ACF60, s32 *, 4);
        }
        if (var_v1 == 0) {
            func_8022F808(temp_a3, sp2C);
            if ((func_8026DF74(sp2C[0], sp2C[1], sp2C[2]) & 0x1C00) == 0x400) {
                func_8026C660(0x31);
            }
        }
    }
}

void func_8024CC58(s16 arg0) {
    UnkObj *sp64;
    s32 sp60;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 *sp24;
    UnkStruct_800AEDF0 *temp_s1;
    f32 *temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_v1;
    void *var_v0;

    var_v1 = 0;
    temp_s1 = &D_800AEDF0[arg0];
    sp64 = temp_s1->unk28;
    if ((temp_s1->unk68 & 0x2000) == 0x2000) {
        var_v1 = 1;
    }
    if (var_v1 != 0) {
        temp_v1 = temp_s1->unkA4;
        temp_v0 = &D_802ACE90[temp_v1];
        sp24 = temp_v0;
        sp58 = 70.0f;
        sp54 = *temp_v0;
        sp50 = 180.0f;
        func_8022FEAC(&sp50, ((UnkObj *)func_802443F4(temp_v1))->unk4C);
        *sp24 -= 1.0f;
    }
    var_v0 = M2C_FIELD(M2C_FIELD(sp64->unk40, void **, 0x48), void **, 4);
    if ((M2C_FIELD(var_v0, f32 *, 4) == 2.0f) && !(temp_s1->unk38 & 0x80)) {
        if (temp_s1->unk3C == 0) {
            sp24 = (f32 *) arg0;
            temp_v0_2 = func_80271540((s32) arg0);
            if (temp_v0_2 != 0) {
                sp60 = temp_v0_2;
                func_80271BB8((s32) sp24);
                temp_s1->unk2C = sp60;
            } else {
                func_80244354((s32) arg0, 0xA0, 0);
                func_802444B8((s32) arg0, 0);
                temp_s1->unk2C = 0;
            }
        } else {
            sp24 = (f32 *) arg0;
            func_802741D8();
            temp_v0_3 = func_80270714((s32) sp24);
            temp_s1->unk2C = temp_v0_3;
            if (temp_v0_3 == 0) {
                func_80244354((s32) arg0, 0xA0, 0);
                func_802444B8((s32) arg0, 0);
            }
        }
        temp_s1->unk38 |= 0x80;
        var_v0 = M2C_FIELD(M2C_FIELD(sp64->unk40, void **, 0x48), void **, 4);
    }
    if ((M2C_FIELD(var_v0, s32 *, 8) & 0x40) && (func_80277CEC((s32) arg0) != 0)) {
        func_80244354((s32) arg0, 0xA0, 0);
        func_80244354((s32) arg0, 0x8000, 1);
        func_802444B8((s32) arg0, 0xC);
    }
    temp_v0_4 = temp_s1->unk2C;
    if ((temp_v0_4 != 0) && ((s32) sp64 != M2C_FIELD(temp_v0_4, s32 *, 0x44))) {
        func_80244C30(arg0, 0);
    }
}

void func_8024C884(s32 arg0, f32 arg1, s32 arg2) {
    s32 sp90;
    s32 sp8C;
    UnkObj *sp84;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    UnkStruct_800AEDF0 *sp20;
    UnkObj *temp_v1;
    UnkStruct_800AEDF0 *temp_a3;
    UnkStruct_800AEDF0 *var_a3;
    f32 var_fa0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_at;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    void *temp_v0_3;

    M2C_FIELD(&sp90, s32 *, 0) = M2C_FIELD(&D_802A0D94, s32 *, 0);
    M2C_FIELD(&sp90, s32 *, 4) = (s32) M2C_FIELD(&D_802A0D94, s32 *, 4);
    var_fa0 = arg1;
    M2C_FIELD(&sp90, s32 *, 0xC) = (s32) M2C_FIELD(&D_802A0D94, s32 *, 0xC);
    M2C_FIELD(&sp90, s32 *, 8) = (s32) M2C_FIELD(&D_802A0D94, s32 *, 8);
    if (arg2 & 0x4000) {
        temp_a3 = &D_800AEDF0[arg0];
        temp_a3->unkAC += 1;
    }
    var_a3 = &D_800AEDF0[arg0];
    temp_v1 = var_a3->unk28;
    sp84 = temp_v1;
    if ((M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v1->unk40, void **, 0x48), void **, 4), f32 *, 4) == 12.0f) && !(var_a3->unk38 & 0x40)) {
        var_v1 = func_80244BA4(arg0, 0x80000);
        if (var_v1 != 0) {
            temp_v0 = var_a3->unk80;
            switch (temp_v0) {                      /* irregular */
            case 1:
                var_fa0 = 0.0f;
                break;
            case 2:
                var_fa0 = 10.0f;
                break;
            case 3:
                var_fa0 = 60.0f;
                break;
            }
        }
        sp20 = var_a3;
        arg1 = var_fa0;
        if (M2C_FIELD(func_8023A840(), s32 *, 0x48) == 1) {
            var_v1_2 = func_80244BA4(arg0, 0x80000);
            if (var_v1_2 == 0) {
                temp_v0_2 = var_a3->unkAC;
                if (temp_v0_2 < 6) {
                    sp8C = 1;
                }
                var_v1_3 = sp8C;
                if (temp_v0_2 >= 6) {
                    var_at = temp_v0_2 < 0xD;
                    if (temp_v0_2 < 0xD) {
                        var_v1_3 = 2;
                        goto block_24;
                    }
                } else {
block_24:
                    var_at = temp_v0_2 < 0xD;
                }
                if (var_at == 0) {
                    goto block_35;
                }
            } else {
                goto block_28;
            }
        } else {
block_28:
            if (arg1 < 10.0f) {
                sp8C = 1;
            }
            var_v1_3 = sp8C;
            if (arg1 >= 10.0f) {
                if (arg1 < 60.0f) {
                    var_v1_3 = 2;
                }
            }
            if (arg1 >= 60.0f) {
block_35:
                var_v1_3 = 3;
            }
        }
        sp8C = var_v1_3;
        sp20 = var_a3;
        func_8026C660(0x20);
        func_80270770((s16) arg0, (s16) var_v1_3);
        var_a3->unk2C = 0;
        if ((D_802AC5D0 & 4) || (arg0 == 0)) {
            sp20 = var_a3;
            func_802479F0(&sp90);
            var_a3 = sp20;
        } else {
            sp20 = var_a3;
            func_8026C660(0x20);
        }
        var_a3->unk38 |= 0x40;
    }
    temp_v0_3 = M2C_FIELD(M2C_FIELD(sp84->unk40, void **, 0x48), void **, 4);
    if ((M2C_FIELD(temp_v0_3, s32 *, 8) & 0x40) || ((M2C_FIELD(temp_v0_3, f32 *, 4) < 12.0f) && (var_a3->unk2C == 0))) {
        sp20 = var_a3;
        func_80244354(arg0, 0x60, 0);
        func_802444B8(arg0, 0);
        var_v1_4 = func_80243EB4(arg0, 0x2000);
        if (var_v1_4 != 0) {
            sp7C = 70.0f;
            sp78 = 60.0f;
            sp74 = 180.0f;
            func_8022FEAC(&sp74, ((UnkObj *)func_802443F4(var_a3->unkA4)) + 0x4C);
        }
    }
}

void func_8024C804(s32 arg0) {
    UnkStruct_800AEDF0 *sp18;
    UnkStruct_800AEDF0 *temp_v1;

    temp_v1 = &D_800AEDF0[arg0];
    sp18 = temp_v1;
    if (func_8024C4EC(temp_v1->unk28, 2) != temp_v1->unk4C) {
        sp18 = temp_v1;
        func_80244354(arg0, 0x200, 0);
        temp_v1->unk4C = 0;
    }
}

void func_8024C53C(s32 arg0, void *arg1) {
    s32 sp5C;
    UnkObj *sp58;
    s32 sp54;
    f32 sp48;
    UnkStruct_800AEDF0 *sp1C;
    UnkModel *temp_v0;
    UnkModel *temp_v0_2;
    UnkModel *temp_v0_3;
    UnkObj *temp_v1;
    UnkStruct_800AEDF0 *temp_t4;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_a3;
    s32 var_v1;

    M2C_FIELD(&sp5C, s32 *, 0) = M2C_FIELD(&D_802A0DB4, s32 *, 0);
    M2C_FIELD(&sp5C, s32 *, 8) = (s32) M2C_FIELD(&D_802A0DB4, s32 *, 8);
    M2C_FIELD(&sp5C, s32 *, 4) = (s32) M2C_FIELD(&D_802A0DB4, s32 *, 4);
    M2C_FIELD(&sp5C, s32 *, 0xC) = (s32) M2C_FIELD(&D_802A0DB4, s32 *, 0xC);
    M2C_FIELD(&sp5C, s32 *, 0x10) = (s32) M2C_FIELD(&D_802A0DB4, s32 *, 0x10);
    temp_t4 = &D_800AEDF0[arg0];
    sp1C = temp_t4;
    temp_v1 = temp_t4->unk28;
    sp58 = temp_v1;
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v1->unk40, void **, 0x48), void **, 4), f32 *, 4) == 11.0f) {
        if (!(temp_t4->unk38 & 0x100)) {
            func_8022F808(temp_v1, &sp48);
            if (sp1C->unkBC == 1) {
                temp_v0 = sp58->unk40;
                temp_v0->unk10 += M2C_FIELD(arg1, f32 *, 0);
                temp_v0_2 = sp58->unk40;
                temp_v0_2->unk14 += M2C_FIELD(arg1, f32 *, 4);
                temp_v0_3 = sp58->unk40;
                temp_v0_3->unk18 += M2C_FIELD(arg1, f32 *, 8);
            }
            temp_v0_4 = func_8024C4EC(sp58, 2);
            if (temp_v0_4 != 0) {
                if ((D_802AC5D0 & 4) || (arg0 == 0)) {
                    sp54 = temp_v0_4;
                    func_802479F0(&sp5C);
                    var_a3 = sp54;
                } else {
                    sp54 = temp_v0_4;
                    func_8026C660(0x1F);
                    var_a3 = temp_v0_4;
                }
                sp54 = var_a3;
                func_80275C7C((s32) (s16) arg0, sp54, (s32) func_802704F8(M2C_FIELD(sp58->unk40, f32 *, 0x20)));
            }
            func_80232BA0(&sp48, sp58);
            sp1C->unk38 |= 0x100;
        }
    }
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(sp58->unk40, void **, 0x48), void **, 4), s32 *, 8) & 0x40) {
        func_80244354(arg0, 0x100, 0);
        var_v1 = 0;
        if ((sp1C->unk10 & 0x8000) == 0x8000) {
            var_v1 = 1;
        }
        if (var_v1 == 0) {
            func_802444B8(arg0, 0);
        } else {
            func_802444B8(arg0, 0xC);
        }
        temp_v0_5 = func_8024C4EC(sp58, 2);
        if (temp_v0_5 != 0) {
            sp1C->unk4C = temp_v0_5;
            func_80244354(arg0, 0x200, 1);
        } else {
            func_80244354(arg0, 0x200, 0);
            sp1C->unk4C = 0;
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
    UnkStruct_800AEDF0 *sp20;
    f32 *sp18;
    UnkStruct_800AEDF0 *temp_v1;
    f32 *temp_v0_2;
    s32 *temp_a1;
    s32 *temp_v0;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a2;
    s32 var_v0;
    s32 var_v0_2;

    temp_v1 = &D_800AEDF0[arg0];
    var_a2 = temp_v1->unk10;
    var_v0 = 0;
    if ((var_a2 & 2) == 2) {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        if (!(temp_v1->unk38 & 0x1000)) {
            sp20 = temp_v1;
            func_802444B8(arg0, 8);
            var_a2 = temp_v1->unk10;
            temp_v1->unk38 |= 0x1000;
        }
    }
    var_v0_2 = 0;
    if (!(var_a2 & 0x600002)) {
        var_v0_2 = 1;
    }
    var_a0 = 0;
    if (var_v0_2 != 0) {
        temp_a1 = &D_802AC8D0[arg0];
        *temp_a1 -= 1;
    }
    temp_v1_2 = arg0 * 4;
    if ((var_a2 & 0x400000) == 0x400000) {
        var_a0 = 1;
    }
    if ((var_a0 == 0) && ((f64) M2C_FIELD(arg3, f32 *, 8) > 60.0)) {
        temp_v0 = temp_v1_2 + &D_802AC900;
        if (M2C_FIELD(arg3, f32 *, 0) != D_802ACA30[(temp_v1_2) / 4]) {
            *temp_v0 -= 1;
        }
    }
    temp_v0_2 = temp_v1_2 + &D_802ACA30;
    if ((*(temp_v1_2 + &D_802AC8D0) == 0) || (D_802AC900[(temp_v1_2) / 4] == 0)) {
        sp18 = temp_v0_2;
        func_80247A54(arg0, arg1, 0x1E, 1);
    }
    *temp_v0_2 = M2C_FIELD(arg3, f32 *, 0);
}

void func_8024C314() {
    func_802444B8(8, 0);
}

void func_8024C29C(s32 arg0) {
    void *sp1C;
    s32 *temp_v0;
    s32 temp_a1;
    s32 temp_t9;

    temp_v0 = &D_802AC918[arg0];
    temp_a1 = *temp_v0;
    if (temp_a1 > 0) {
        temp_t9 = temp_a1 - 1;
        *temp_v0 = temp_t9;
        if (temp_t9 == 0) {
            sp1C = ((UnkObj *)func_802443F4(arg0));
            func_80244354(0x10000, 0, 0);
            func_802313DC(sp1C, 0x40000);
        }
    }
}

void func_8024C1E8(s32 arg0) {
    UnkStruct_800AEDF0 *sp18;
    UnkStruct_800AEDF0 *temp_a3;
    s32 var_v1;

    temp_a3 = &D_800AEDF0[arg0];
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_a3->unk28->unk40, void **, 0x48), void **, 4), s32 *, 8) & 0x40) {
        sp18 = temp_a3;
        func_80244354(0x2020, 0, (s32) temp_a3);
        var_v1 = func_80244BA4(arg0, 0x8000);
        if (var_v1 == 0) {
            func_802444B8(arg0, 0);
        } else {
            func_802444B8(arg0, 0xC);
        }
    }
}

void func_8024C0D8(s32 arg0) {
    void *sp1C;
    f32 *temp_v1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 *temp_v0;
    s32 temp_a0;
    s32 temp_t3;
    void *temp_a1;

    temp_a0 = arg0 * 4;
    temp_v1 = temp_a0 + &D_802ACA60;
    temp_a1 = D_800AEDF0[arg0].unk28;
    *temp_v1 += 16.0f;
    temp_fv0 = *temp_v1;
    if (temp_fv0 >= 360.0f) {
        M2C_FIELD(M2C_FIELD(temp_a1, void **, 0x40), f32 *, 0x20) = (f32) (temp_fv0 - 360.0f);
    } else {
        M2C_FIELD(M2C_FIELD(temp_a1, void **, 0x40), f32 *, 0x20) = temp_fv0;
    }
    temp_fv0_2 = D_802ACA48[(temp_a0) / 4];
    temp_v0 = temp_a0 + &D_802AC930;
    if ((*temp_v1 - temp_fv0_2) > 360.0f) {
        *temp_v1 = temp_fv0_2;
        temp_t3 = *temp_v0 - 1;
        *temp_v0 = temp_t3;
        if (temp_t3 == 0) {
            M2C_FIELD(M2C_FIELD(temp_a1, void **, 0x40), f32 *, 0x20) = temp_fv0_2;
            sp1C = temp_a1;
            func_80244354(arg0, 0x20020, 0);
            func_802313DC(sp1C, 0x40000);
            func_8024796C(arg0, 0x3C);
        }
    }
}

void func_8024C04C(s16 arg0) {
    UnkStruct_800AEDF0 *sp20;

    sp20 = &D_800AEDF0[arg0];
    if (func_80270714((s32) arg0) == 0) {
        func_80244354((s32) arg0, 0x8000, 0);
        func_802444B8((s32) arg0, 0);
        sp20->unk2C = 0;
        func_80244354((s32) arg0, 0x120, 0);
    }
}

void func_8024BFE0(s32 arg0) {
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(((UnkObj *)func_802443F4(arg0)), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40) {
        func_80244354(0x04000020, 0, 0);
    }
}

void func_8024BF04(s32 arg0) {
    UnkStruct_800AEDF0 *sp28;
    UnkModel *temp_v0;
    UnkStruct_800AEDF0 *temp_v1;

    temp_v1 = &D_800AEDF0[arg0];
    if (temp_v1->unk2C != 0) {
        temp_v0 = temp_v1->unk28->unk40;
        sp28 = temp_v1;
        if (func_80274F8C(M2C_FIELD(temp_v1, s16 *, 0x1A), temp_v0->unk10, temp_v0->unk14, temp_v0->unk18, (s16) arg0) == 0) {
            if (func_802712A8(func_802703B4(temp_v1->unk2C) + 0x64, 0x80) != 0) {
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
    UnkStruct_800AEDF0 *sp18;
    UnkModel *temp_v0;
    UnkModel *temp_v0_2;
    UnkModel *temp_v0_3;
    UnkObj *temp_a1;
    UnkStruct_800AEDF0 *temp_v1;
    s32 temp_a0;
    s32 temp_fv0;
    s32 temp_fv0_2;
    s32 var_fv0;

    temp_v1 = &D_800AEDF0[arg0];
    temp_fv0 = temp_v1->unk64;
    temp_a1 = temp_v1->unk28;
    if (M2C_BITWISE(f32, temp_fv0) > 360.0f) {
        temp_v1->unk64 = M2C_BITWISE(s32, (M2C_BITWISE(f32, temp_fv0) - 360.0f));
    }
    if (M2C_BITWISE(f32, temp_v1->unk64) < 0.0f) {
        temp_v1->unk64 = M2C_BITWISE(s32, (M2C_BITWISE(f32, temp_v1->unk64) + 360.0f));
    }
    temp_v1->unk60 = M2C_BITWISE(s32, (M2C_BITWISE(f32, temp_v1->unk60) + M2C_BITWISE(f32, temp_v1->unk5C)));
    M2C_FIELD(temp_a1->unk40, s32 *, 0x20) = (s32) temp_v1->unk60;
    if (M2C_BITWISE(f32, temp_v1->unk60) > 360.0f) {
        temp_v0 = temp_a1->unk40;
        M2C_FIELD(temp_v0, s32 *, 0x20) = M2C_BITWISE(s32, (M2C_BITWISE(f32, M2C_FIELD(temp_v0, s32 *, 0x20)) - 360.0f));
    }
    if (M2C_BITWISE(f32, temp_v1->unk60) < 0.0f) {
        temp_v0_2 = temp_a1->unk40;
        M2C_FIELD(temp_v0_2, s32 *, 0x20) = M2C_BITWISE(s32, (M2C_BITWISE(f32, M2C_FIELD(temp_v0_2, s32 *, 0x20)) + 360.0f));
    }
    temp_fv0_2 = temp_v1->unk5C;
    if (((M2C_BITWISE(f32, temp_fv0_2) > 0.0f) && (M2C_BITWISE(f32, temp_v1->unk58) <= M2C_BITWISE(f32, temp_v1->unk60))) || ((M2C_BITWISE(f32, temp_fv0_2) < 0.0f) && (M2C_BITWISE(f32, temp_v1->unk60) <= M2C_BITWISE(f32, temp_v1->unk58)))) {
        M2C_FIELD(temp_a1->unk40, s32 *, 0x20) = temp_v1->unk58;
        temp_v0_3 = temp_a1->unk40;
        var_fv0 = M2C_FIELD(temp_v0_3, s32 *, 0x20);
        if (M2C_BITWISE(f32, var_fv0) >= 360.0f) {
            M2C_FIELD(temp_v0_3, s32 *, 0x20) = M2C_BITWISE(s32, (M2C_BITWISE(f32, var_fv0) - 360.0f));
            var_fv0 = M2C_FIELD(temp_a1->unk40, s32 *, 0x20);
        }
        if (M2C_BITWISE(f32, var_fv0) < 0.0f) {
            M2C_FIELD(temp_a1->unk40, f32 *, 0x20) = (f32) (M2C_BITWISE(f32, var_fv0) + 360.0f);
        }
        sp18 = temp_v1;
        func_80244354(0x43B40000, 0, 0x08000000);
    }
    temp_a0 = temp_v1->unk2C;
    if (temp_a0 != 0) {
        func_80231434((void *) temp_a0);
    }
}

void func_8024BC94(s32 arg0) {
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(((UnkObj *)func_802443F4(arg0)), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40) {
        func_80244354(0x20, 0, 0);
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
        func_80244354(0x20, 0, 0);
        func_80243D90(arg0, 0x200000, 0);
    }
}

void func_8024B444(s32 arg0, f32 *arg1) {
    UnkObj *spF4;
    s32 spF0;
    f32 spD8;
    f32 spCC;
    s32 spC8;                                       /* compiler-managed */
    f32 spC4;
    f32 spC0;
    s32 spBC;
    UnkModel *temp_v0;
    UnkModel *temp_v0_2;
    UnkModel *temp_v0_3;
    UnkModel *temp_v0_5;
    UnkModel *temp_v0_6;
    UnkObj *temp_a2;
    UnkObj *temp_s2;
    UnkStruct_800AEDF0 *temp_s6;
    UnkStruct_800AEDF0 *temp_v1;
    UnkStruct_800AEDF0 *temp_v1_2;
    s32 temp_a3;
    s32 temp_fv0;
    s32 temp_fv1;
    s32 temp_v0_4;
    s32 var_s0;
    s32 var_s5;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;

    M2C_FIELD(arg1, s32 *, 4) = 0;
    M2C_FIELD(arg1, f32 *, 0) = 0.0f;
    temp_s6 = &D_800AEDF0[arg0];
    temp_s2 = temp_s6->unk28;
    var_v1 = func_80243EB4(arg0, 0x2000);
    if (var_v1 != 0) {
        temp_a3 = temp_s6->unkA8;
        if (M2C_FIELD(temp_s2->unk40, f32 *, 0x28) > 1.0f) {
            temp_v1 = &D_800AEDF0[temp_a3];
            if (M2C_BITWISE(f32, temp_v1->unkC4) == 8.0f) {
                temp_v1->unkC4 = 0x40C00000;
            }
            if (M2C_BITWISE(f32, temp_v1->unkC4) == -8.0f) {
                temp_v1->unkC4 = -0x3F400000;
            }
        }
        temp_v1_2 = &D_800AEDF0[temp_a3];
        if (M2C_FIELD(temp_s2->unk40, f32 *, 0x28) < 1.0f) {
            if (M2C_BITWISE(f32, temp_v1_2->unkC4) == 6.0f) {
                temp_v1_2->unkC4 = 0x41000000;
            }
            if (M2C_BITWISE(f32, temp_v1_2->unkC4) == -6.0f) {
                temp_v1_2->unkC4 = -0x3F000000;
            }
        }
        temp_fv0 = temp_v1_2->unkC0;
        temp_a2 = temp_v1_2->unk28;
        temp_v1_2->unkC0 = M2C_BITWISE(s32, (M2C_BITWISE(f32, temp_fv0) + M2C_BITWISE(f32, temp_v1_2->unkC4)));
        spBC = temp_a3;
        spF0 = temp_fv0;
        spC4 = 60.0f;
        spF4 = temp_a2;
        spC8 = temp_v1_2->unkC0;
        spC0 = 180.0f;
        func_8022FEAC(&spC0, temp_a2->unk4C);
        func_80231434(spF4);
    }
    temp_v0 = temp_s2->unk40;
    M2C_FIELD(temp_v0, f32 *, 0x28) = (f32) (M2C_FIELD(temp_v0, f32 *, 0x28) + M2C_BITWISE(f32, temp_s6->unk6C));
    temp_v0_2 = temp_s2->unk40;
    M2C_FIELD(temp_v0_2, f32 *, 0x2C) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 0x2C) + M2C_BITWISE(f32, temp_s6->unk6C));
    temp_v0_3 = temp_s2->unk40;
    M2C_FIELD(temp_v0_3, f32 *, 0x30) = (f32) (M2C_FIELD(temp_v0_3, f32 *, 0x30) + M2C_BITWISE(f32, temp_s6->unk6C));
    temp_v0_4 = func_8022F4AC((s32) temp_s2, 0x10, temp_s6->unk4C);
    if (temp_v0_4 != 0) {
        func_8022F808(temp_s2, &spD8);
        func_8022F808((void *) temp_v0_4, &spCC);
        var_s5 = 0;
        spC4 = 0.0f;
        spC0 = 0.0f;
        spC8 = 0x40A00000;
loop_16:
        var_s0 = 0;
loop_17:
        func_80232BA0(&spD8, temp_s2);
        func_80291944(temp_s2, var_s0 << 5, M2C_BITWISE(f32, spC8));
        if (func_802909FC((s32) temp_s2) == 0) {
            var_s0 += 1;
            if (func_8022F4AC((s32) temp_s2, 0x10, temp_s6->unk4C) == 0) {
                temp_v0_5 = temp_s2->unk40;
                M2C_FIELD(temp_s2, f32 *, 0x58) = (f32) temp_v0_5->unk10;
                M2C_FIELD(temp_s2, f32 *, 0x5C) = (f32) temp_v0_5->unk14;
                M2C_FIELD(temp_s2, f32 *, 0x60) = (f32) temp_v0_5->unk18;
            } else {
                goto block_21;
            }
        } else {
            var_s0 += 1;
block_21:
            if (var_s0 == 8) {
                var_s5 += 1;
                spC8 = M2C_BITWISE(f32, spC8) + 2.0f;
                if (var_s5 >= 0x32) {
                    func_80232BA0(&spD8, temp_s2);
                    do {
loop_24:
                        temp_v0_6 = temp_s2->unk40;
                        temp_v0_6->unk14 += 10.0f;
                        if (func_802909FC((s32) temp_s2) != 0) {
                            goto loop_24;
                        }
                    } while (func_8022F4AC((s32) temp_s2, 0x10, temp_s6->unk4C) != 0);
                    func_80247D74(arg0, 22.5f, 8.0f, 1, NULL);
                } else {
                    goto loop_16;
                }
            } else {
                goto loop_17;
            }
        }
        func_8022F808(temp_s2, &spCC);
        M2C_FIELD(arg1, f32 *, 0) = M2C_BITWISE(f32, func_8022DF68((s32) &spD8, (s32) &spCC));
        var_v1_2 = func_80243EB4(arg0, 0x2000);
        if (var_v1_2 != 0) {
            D_800AEDF0[spBC].unkC0 = spF0;
            spC8 = spF0;
            spC4 = 60.0f;
            spC0 = 180.0f;
            func_8022FEAC(&spC0, spF4->unk4C);
            func_80231434(spF4);
        }
    }
    M2C_FIELD(temp_s6->unkB0, f32 *, 0x4C) = (f32) M2C_FIELD(temp_s2->unk40, f32 *, 0x28);
    M2C_FIELD(temp_s6->unkB0, f32 *, 0x54) = (f32) M2C_FIELD(temp_s2->unk40, f32 *, 0x30);
    temp_fv1 = temp_s6->unk6C;
    if (((M2C_BITWISE(f32, temp_fv1) > 0.0f) && (M2C_BITWISE(f32, temp_s6->unk70) <= M2C_FIELD(temp_s2->unk40, f32 *, 0x28))) || ((M2C_BITWISE(f32, temp_fv1) < 0.0f) && (M2C_FIELD(temp_s2->unk40, f32 *, 0x28) <= M2C_BITWISE(f32, temp_s6->unk70)))) {
        M2C_FIELD(temp_s2->unk40, s32 *, 0x28) = temp_s6->unk70;
        M2C_FIELD(temp_s2->unk40, f32 *, 0x2C) = M2C_BITWISE(f32, temp_s6->unk70);
        M2C_FIELD(temp_s2->unk40, f32 *, 0x30) = M2C_BITWISE(f32, temp_s6->unk70);
        M2C_FIELD(temp_s6->unkB0, f32 *, 0x4C) = (f32) M2C_FIELD(temp_s2->unk40, f32 *, 0x28);
        M2C_FIELD(temp_s6->unkB0, f32 *, 0x54) = (f32) M2C_FIELD(temp_s2->unk40, f32 *, 0x30);
        if (M2C_BITWISE(f32, temp_s6->unk6C) > 0.0f) {
            func_80243D90(arg0, 2, 0);
            if (M2C_FIELD(temp_s2->unk40, f32 *, 0x28) == 1.0f) {
                func_80243D90(arg0, 1, 0);
                if ((((temp_s6->unk68 & 8) | 0xA0) == 0) && !(temp_s6->unk18 & 0x404)) {
                    func_80243D90(arg0, 0x10, 0);
                }
            } else {
                var_v1_3 = func_80243EB4(arg0, 0x2000);
                if (var_v1_3 != 0) {
                    spC8 = 0x42C80000;
                    spC4 = 60.0f;
                    spC0 = 180.0f;
                    func_8022FEAC(&spC0, D_800AEDF0[temp_s6->unkA8].unk28 + 0x4C);
                }
            }
        }
        if (M2C_BITWISE(f32, temp_s6->unk6C) < 0.0f) {
            func_80243D90(arg0, 2, 0);
            if (M2C_FIELD(temp_s2->unk40, f32 *, 0x28) == 1.0f) {
                func_80243D90(arg0, 4, 0);
                if (((temp_s6->unk68 & 8) | 0xA0) == 0) {
                    if (!(temp_s6->unk18 & 0x404)) {
                        func_80243D90(arg0, 0x10, 0);
                    }
                }
            } else {
                var_v1_4 = func_80243EB4(arg0, 0x2000);
                if (var_v1_4 != 0) {
                    spC8 = 0x41F00000;
                    spC4 = 60.0f;
                    spC0 = 180.0f;
                    func_8022FEAC(&spC0, D_800AEDF0[temp_s6->unkA8].unk28 + 0x4C);
                }
            }
        }
        func_80243D90(arg0, 2, 0);
    }
    temp_s6->unk74 += 1;
}

void func_8024B1CC(s16 arg0) {
    UnkObj *sp2C;
    UnkModel *temp_v0;
    UnkStruct_800AEDF0 *temp_s0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_t2;
    s32 var_t3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_6;
    s32 var_v1_7;
    s32 var_v1_8;

    temp_s0 = &D_800AEDF0[arg0];
    temp_a0 = temp_s0->unk78 - 1;
    temp_s0->unk78 = temp_a0;
    sp2C = temp_s0->unk28;
    if (temp_a0 == 0) {
        temp_a0_2 = temp_s0->unk68;
        var_v1 = 0;
        if ((temp_a0_2 & 4) == 4) {
            var_v1 = 1;
        }
        var_t2 = temp_a0_2 & 1;
        if (var_v1 != 0) {
            func_80270770(arg0, 1);
            temp_s0->unk2C = 0;
            func_8024694C((s32) arg0, 1, 0);
            func_80243D90((s32) arg0, 4, 0);
            var_t2 = temp_s0->unk68 & 1;
        }
        var_v1_2 = 0;
        if (var_t2 == 1) {
            var_v1_2 = 1;
        }
        var_t3 = temp_s0->unk68 & 0x80;
        if (var_v1_2 != 0) {
            func_80270770(arg0, 1);
            temp_s0->unk2C = 0;
            func_8024694C((s32) arg0, 2, 0);
            func_80243D90((s32) arg0, 1, 0);
            var_t3 = temp_s0->unk68 & 0x80;
        }
        var_v1_3 = 0;
        if (var_t3 == 0x80) {
            var_v1_3 = 1;
        }
        if (var_v1_3 != 0) {
            func_802313DC(sp2C, 0x40);
            func_80243D90((s32) arg0, 0x80, 0);
            var_v1_4 = func_80244BA4(arg0, 0x10000);
            if (var_v1_4 == 0) {
                func_80248148((s32) arg0, 1);
            }
        }
        var_v1_5 = func_80243EB4(arg0, 0x100);
        if (var_v1_5 != 0) {
            func_80246C3C((s32) arg0, 0, 0);
        }
        var_v1_6 = func_80243EB4(arg0, 8);
        if (var_v1_6 != 0) {
            func_80243D90((s32) arg0, 8, 0);
        }
        var_v1_7 = func_80243EB4(arg0, 0x20);
        if (var_v1_7 != 0) {
            func_80243D90((s32) arg0, 0x20, 0);
        }
        func_80243D90((s32) arg0, 0x10, 0);
        temp_s0->unk18 &= ~0x404;
        func_8026C660(0x1ED);
        return;
    }
    var_v1_8 = func_80243EB4(arg0, 0x80);
    if ((var_v1_8 != 0) && !(temp_a0 & 3)) {
        temp_v0 = sp2C->unk40;
        func_8028A81C(7, temp_v0->unk10, temp_v0->unk14 + 100.0f, temp_v0->unk18, 0);
    }
}

void func_8024B028(s32 arg0) {
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    UnkStruct_800AEDF0 *sp20;
    UnkStruct_800AEDF0 *temp_v1;
    s32 temp_fv1;
    s32 temp_fv1_2;
    s32 temp_t7;
    s32 temp_v0;
    s32 var_a0;

    temp_v1 = &D_800AEDF0[arg0];
    temp_fv1 = temp_v1->unk88;
    temp_v0 = temp_v1->unk84;
    temp_v1->unk8C = M2C_BITWISE(s32, (M2C_BITWISE(f32, temp_v1->unk8C) + M2C_BITWISE(f32, temp_fv1)));
    switch (temp_v0) {                              /* irregular */
    case 1:
        sp4C = 0x1F;
        sp48 = 0;
block_7:
        sp44 = 0;
        break;
    case 2:
        sp44 = 4;
        sp48 = 4;
        sp4C = 4;
        break;
    case 3:
        sp48 = 0x1F;
        sp4C = 0x1F;
        goto block_7;
    }
    if ((M2C_BITWISE(f32, temp_v1->unk8C) > 1.0f) && (M2C_BITWISE(f32, temp_fv1) > 0.0f)) {
        temp_v1->unk8C = 0x3F800000;
        temp_v1->unk88 = M2C_BITWISE(s32, -M2C_BITWISE(f32, temp_fv1));
    }
    if (M2C_BITWISE(f32, temp_v1->unk8C) < 0.0f) {
        temp_fv1_2 = temp_v1->unk88;
        if (M2C_BITWISE(f32, temp_fv1_2) < 0.0f) {
            temp_v1->unk8C = 0;
            temp_v1->unk88 = M2C_BITWISE(s32, -M2C_BITWISE(f32, temp_fv1_2));
        }
    }
    sp20 = temp_v1;
    func_8029279C(temp_v1->unk28->unk40, sp4C, sp48, sp44, M2C_BITWISE(f32, temp_v1->unk8C));
    temp_t7 = temp_v1->unk90 - 1;
    temp_v1->unk90 = temp_t7;
    if (temp_t7 != 0) {
        var_a0 = func_80243EB4(arg0, 0x10);
        if (var_a0 == 0) {
            goto block_18;
        }
    } else {
block_18:
        func_80246C3C(arg0, 0, 0);
    }
}

void func_8024AFD4(s32 arg0) {
    UnkStruct_800AEDF0 *temp_v0;
    s32 temp_t9;

    temp_v0 = &D_800AEDF0[arg0];
    temp_t9 = temp_v0->unk7C - 1;
    temp_v0->unk7C = temp_t9;
    if (temp_t9 == 0) {
        func_80243D90(0x40, 0, 0);
    }
}

void func_8024AF24(s32 arg0, f32 *arg1) {
    s32 *temp_a0;
    s32 *temp_v0;
    s32 temp_v1;

    temp_v1 = arg0 * 4;
    temp_a0 = temp_v1 + &D_802AC998;
    *temp_a0 -= 1;
    if ((f64) M2C_FIELD(arg1, f32 *, 8) > 60.0) {
        temp_v0 = temp_v1 + &D_802AC9B0;
        if (M2C_FIELD(arg1, f32 *, 0) != D_802ACA30[(temp_v1) / 4]) {
            *temp_v0 -= 1;
        }
    }
    if ((*temp_a0 == 0) || (D_802AC9B0[(temp_v1) / 4] == 0)) {
        func_80247F90(arg0);
    }
}

void func_8024ABA8(s32 arg0) {
    s32 sp2C;
    s32 *temp_v1;
    s32 *temp_v1_7;
    s32 temp_a1;
    s32 temp_t0;
    s32 temp_t6;
    s32 temp_v0;
    s32 temp_v1_11;
    s32 var_t3;
    s32 var_t4;
    s32 var_v0;
    void *temp_v1_10;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_5;
    void *temp_v1_6;
    void *temp_v1_8;
    void *temp_v1_9;

    temp_a1 = D_802AC960;
    if (temp_a1 != 0) {
        temp_v0 = temp_a1 * 4;
        temp_v1 = &D_800AF1D8[temp_a1];
        if (M2C_FIELD(temp_v1, s32 *, 0) == -1) {
            M2C_FIELD(temp_v1, s32 *, 0) = M2C_FIELD(temp_v1, s32 *, -4);
        }
        temp_v1_2 = temp_v0 + &D_800AF5D8;
        if (M2C_FIELD(temp_v1_2, s32 *, 0) == -1) {
            M2C_FIELD(temp_v1_2, s32 *, 0) = (s32) M2C_FIELD(temp_v1_2, s32 *, -4);
        }
        temp_v1_3 = temp_v0 + &D_802ACA90;
        if (M2C_FIELD(temp_v1_3, f32 *, 0) == -1.0f) {
            M2C_FIELD(temp_v1_3, f32 *, 0) = (f32) M2C_FIELD(temp_v1_3, f32 *, -4);
        }
        temp_v1_4 = temp_v0 + &D_800AF9D8;
        if (M2C_FIELD(temp_v1_4, s32 *, 0) == -1) {
            M2C_FIELD(temp_v1_4, s32 *, 0) = (s32) M2C_FIELD(temp_v1_4, s32 *, -4);
        }
        temp_v1_5 = temp_v0 + &D_800AFDD8;
        if (M2C_FIELD(temp_v1_5, s32 *, 0) == -1) {
            M2C_FIELD(temp_v1_5, s32 *, 0) = (s32) M2C_FIELD(temp_v1_5, s32 *, -4);
        }
        temp_v1_6 = temp_v0 + &D_800B01D8;
        if (M2C_FIELD(temp_v1_6, s32 *, 0) == -1) {
            M2C_FIELD(temp_v1_6, s32 *, 0) = (s32) M2C_FIELD(temp_v1_6, s32 *, -4);
        }
        temp_v1_7 = &D_800B05D8[temp_a1];
        if (M2C_FIELD(temp_v1_7, s32 *, 0) == -1) {
            M2C_FIELD(temp_v1_7, s32 *, 0) = M2C_FIELD(temp_v1_7, s32 *, -4);
        }
        temp_v1_8 = temp_v0 + &D_800B09D8;
        if (M2C_FIELD(temp_v1_8, s32 *, 0) == -1) {
            M2C_FIELD(temp_v1_8, s32 *, 0) = (s32) M2C_FIELD(temp_v1_8, s32 *, -4);
        }
        temp_v1_9 = temp_v0 + &D_800B0DD8;
        if (M2C_FIELD(temp_v1_9, s32 *, 0) == -1) {
            M2C_FIELD(temp_v1_9, s32 *, 0) = (s32) M2C_FIELD(temp_v1_9, s32 *, -4);
        }
        temp_v1_10 = temp_v0 + &D_800B11D8;
        var_v0 = temp_a1 * 4;
        if (M2C_FIELD(temp_v1_10, s32 *, 0) == -1) {
            M2C_FIELD(temp_v1_10, s32 *, 0) = (s32) M2C_FIELD(temp_v1_10, s32 *, -4);
            goto block_21;
        }
    } else {
block_21:
        var_v0 = temp_a1 * 4;
    }
    temp_t6 = D_800AF1D8[(var_v0) / 4];
    switch (temp_t6) {                              /* switch 1 */
    case 0x57:                                      /* switch 1 */
    case 0x77:                                      /* switch 1 */
        func_8024A824(D_800AF5D8[(var_v0) / 4], D_800AF9D8[(var_v0) / 4], D_802ACA90[(var_v0) / 4], D_800AFDD8[(var_v0) / 4], 0, D_800B01D8[(var_v0) / 4], D_800B05D8[(var_v0) / 4]);
    default:                                        /* switch 1 */
block_44:
        var_t4 = temp_a1 + 1;
        break;
    case 0x53:                                      /* switch 1 */
    case 0x73:                                      /* switch 1 */
        temp_v1_11 = D_800B09D8[(var_v0) / 4];
        if ((temp_v1_11 == 0x54) || (var_t4 = temp_a1 + 1, (temp_v1_11 == 0x74))) {
            func_8024A0DC(0x40000, temp_a1);
            goto block_44;
        }
        break;
    case 0x4D:                                      /* switch 1 */
    case 0x6D:                                      /* switch 1 */
        temp_t0 = D_800B11D8[(var_v0) / 4];
        switch (temp_t0) {                          /* switch 2 */
        case 0x30:                                  /* switch 2 */
            sp2C = 0x200;
            break;
        case 0x31:                                  /* switch 2 */
            var_t3 = 0x80;
block_42:
            sp2C = var_t3;
            break;
        case 0x32:                                  /* switch 2 */
            sp2C = 0x40;
            break;
        case 0x33:                                  /* switch 2 */
            sp2C = 0x100000;
            break;
        case 0x34:                                  /* switch 2 */
            sp2C = 0x800;
            break;
        case 0x35:                                  /* switch 2 */
            sp2C = 0x4000;
            break;
        case 0x36:                                  /* switch 2 */
            sp2C = 0x400;
            break;
        case 0x37:                                  /* switch 2 */
            sp2C = 0x10000;
            break;
        case 0x38:                                  /* switch 2 */
            sp2C = 0x20000;
            break;
        case 0x39:                                  /* switch 2 */
            sp2C = 0x200000;
            break;
        case 0x41:                                  /* switch 2 */
            sp2C = 0x400000;
            break;
        case 0x42:                                  /* switch 2 */
            var_t3 = 0x04000000;
            goto block_42;
        }
        func_8024A0DC(sp2C, temp_a1);
        goto block_44;
    }
    D_802AC960 = var_t4;
    if (D_800AF1D8[D_802AC960] == -2) {
        func_80244354(arg0, 0x800, 0);
    }
}

void func_8024A824(s32 arg0, s32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 spBC;
    f32 spB8;
    f32 spB4;
    s32 sp9C[3];
    f32 sp90[3];
    f32 sp84[2];
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    UnkObj *sp74;
    f32 sp68;
    UnkStruct_800AEDF0 *sp30;
    UnkModel *temp_v0;
    UnkObj *temp_a0;
    UnkStruct_800AEDF0 *temp_a1;
    f32 var_ft2;
    s32 temp_s0;
    s32 var_s0;
    s32 var_v1;

    temp_s0 = func_80243DDC() * 4;
    temp_a0 = ((UnkObj *)func_802443F4(func_80243DDC()));
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
    temp_a1 = &D_800AEDF0[func_80243DDC()];
    temp_a1->unk48 = arg6;
    if (arg6 == 0) {
        M2C_FIELD(temp_a0, f32 *, 0x70) = 0.0f;
    }
    D_802AC968[(temp_s0) / 4] = arg5 * 2;
    temp_v0 = temp_a0->unk40;
    sp74 = temp_a0;
    spBC = func_80243DDC();
    sp30 = temp_a1;
    func_8026DCAC(temp_v0->unk10, temp_v0->unk14, temp_v0->unk18, sp9C, 2);
    func_8026E338((f32) sp9C[0], (f32) sp9C[1], (f32) sp9C[2], sp90, 0);
    D_802ACA28 = sp90[0];
    D_802ACA2C = sp90[1];
    D_802ACA8C = sp90[2];
    D_802ACA10[(temp_s0) / 4] = 0;
    func_8022F808(sp74, sp84);
    sp78 = sp90[0];
    sp7C = sp84[1];
    sp80 = sp90[2];
    spB4 = M2C_BITWISE(f32, func_8022DF68((s32) sp84, (s32) &sp78));
    func_80244354(spBC, 0x10420, 1);
    D_802AC918[(temp_s0) / 4] = 0;
    func_802313DC(sp74, 0x40000);
    func_80247C50(spBC);
    if (spB4 > 0.0f) {
        func_8022FF58(sp84, &sp78, &sp68);
        D_802AC8C0 = func_80243F50(sp68);
    } else {
        D_802AC8C0 = D_802AC8BC;
    }
    if (D_802AC8BC != 0x100) {
        if (D_802AC8BC != 0x200) {
            switch (D_802AC8C0) {                   /* irregular */
            case 0x0:
                spB8 = 180.0f;
                break;
            case 0x80:
                var_ft2 = 0.0f;
block_33:
                spB8 = var_ft2;
                break;
            case 0xC0:
                spB8 = 270.0f;
                break;
            case 0x40:
                spB8 = 90.0f;
                break;
            case 0x20:
                spB8 = 135.0f;
                break;
            case 0xE0:
                spB8 = 225.0f;
                break;
            case 0x60:
                spB8 = 45.0f;
                break;
            case 0xA0:
                var_ft2 = 315.0f;
                goto block_33;
            }
            func_8024A6B4(spBC, spB8);
        }
    }
    if (arg4 != 0) {
        var_v1 = 0;
        if ((sp30->unk10 & 0x400) == 0x400) {
            var_v1 = 1;
        }
        if (var_v1 != 0) {
            do {
                var_s0 = 0;
                func_80239094();
                if ((sp30->unk10 & 0x400) == 0x400) {
                    var_s0 = 1;
                }
            } while (var_s0 != 0);
        }
    }
}

void func_8024A6B4(s32 arg0, f32 arg1) {
    UnkObj *temp_a1;
    UnkStruct_800AEDF0 *temp_v1;
    f32 temp_fa1;
    f32 var_fv1;
    s32 var_fa0;

    temp_v1 = &D_800AEDF0[arg0];
    temp_a1 = temp_v1->unk28;
    if (arg1 != M2C_FIELD(temp_a1->unk40, f32 *, 0x20)) {
        temp_v1->unk58 = M2C_BITWISE(s32, arg1);
        temp_v1->unk64 = M2C_BITWISE(s32, M2C_FIELD(temp_a1->unk40, f32 *, 0x20));
        temp_fa1 = M2C_FIELD(temp_a1->unk40, f32 *, 0x20);
        if (temp_fa1 < arg1) {
            var_fv1 = temp_fa1;
            var_fa0 = temp_v1->unk58;
        } else {
            var_fa0 = M2C_BITWISE(s32, temp_fa1);
            var_fv1 = M2C_BITWISE(f32, temp_v1->unk58);
        }
        if (((var_fv1 + 360.0f) - M2C_BITWISE(f32, var_fa0)) < (M2C_BITWISE(f32, var_fa0) - var_fv1)) {
            if (var_fv1 == M2C_BITWISE(f32, temp_v1->unk58)) {
                temp_v1->unk58 = M2C_BITWISE(s32, (M2C_BITWISE(f32, temp_v1->unk58) + 360.0f));
            } else {
                temp_v1->unk58 = M2C_BITWISE(s32, (M2C_BITWISE(f32, temp_v1->unk58) - 360.0f));
            }
            if (M2C_BITWISE(f32, temp_v1->unk58) == -360.0f) {
                temp_v1->unk58 = 0x43B40000;
            }
        }
        if (M2C_FIELD(temp_a1->unk40, f32 *, 0x20) < M2C_BITWISE(f32, temp_v1->unk58)) {
            temp_v1->unk5C = 0x41A00000;
        } else {
            temp_v1->unk5C = -0x3E600000;
        }
        temp_v1->unk60 = M2C_FIELD(temp_a1->unk40, s32 *, 0x20);
        func_80244354(var_fa0, 0x43B40000, 0x08000000);
    }
}

void func_8024A0DC(s32 arg0) {
    UnkObj *spBC;
    s32 sp94[3];
    s32 sp38;
    UnkStruct_800AEDF0 *sp34;
    s32 sp30;
    UnkModel *temp_v0;
    UnkModel *temp_v0_3;
    UnkObj *temp_v1_3;
    UnkStruct_800AEDF0 *temp_v1;
    UnkStruct_800AEDF0 *temp_v1_2;
    UnkStruct_800AEDF0 *temp_v1_4;
    s32 temp_a3;
    s32 temp_s0;
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;

    temp_s0 = func_80243DDC();
    temp_t8 = temp_s0 * 4;
    D_802AC980[(temp_t8) / 4] = arg0;
    sp38 = temp_t8;
    spBC = ((UnkObj *)func_802443F4(temp_s0));
    switch (arg0) {                                 /* irregular */
    case 0x200:
        if (func_80232D18(spBC, 2) != 0) {
            func_80244354(temp_s0, 0x200, 0);
            D_800AEDF0[temp_s0].unk4C = 0;
            func_80249810(temp_s0, func_8022F550((s32) spBC, 2), 2);
        } else {
            temp_v0 = spBC->unk40;
            temp_v1 = &D_800AEDF0[temp_s0];
            sp34 = temp_v1;
            temp_a3 = M2C_FIELD(func_80274F8C(M2C_FIELD(temp_v1, s16 *, 0x1A), temp_v0->unk10, temp_v0->unk14, temp_v0->unk18, 0), s32 *, 0x1C);
            temp_v1->unk4C = temp_a3;
            func_80244354(temp_s0, 0x200, 1);
        }
        break;
    case 0x80:
        sp30 = (s32) (s16) temp_s0;
        if (func_80270714((s32) (s16) temp_s0) == 0) {
            temp_v0_2 = func_80271540((s16) temp_s0);
            temp_v1_2 = &D_800AEDF0[temp_s0];
            temp_v1_2->unk2C = temp_v0_2;
            if (temp_v0_2 != 0) {
                func_80249FD4(temp_s0, 0);
                func_80244354(temp_s0, 0x90000, 1);
                D_802AC918[(sp38) / 4] = 0;
                func_802313DC(spBC, 0x40000);
            } else {
                temp_v0_3 = spBC->unk40;
                sp34 = temp_v1_2;
                func_8026DCAC(temp_v0_3->unk10, temp_v0_3->unk14, temp_v0_3->unk18, sp94, 2);
                temp_t4 = func_8026D7D8(sp94[0], sp94[1], sp94[2]) & 0x4000;
                var_a0 = 0;
                if (!(sp34->unk10 & 0x8100)) {
                    var_a0 = 1;
                }
                if ((var_a0 != 0) && (temp_t4 == 0)) {
                    if (func_80274994((s16) temp_s0) != 0) {
                        func_80249FD4(temp_s0, 1);
                    }
                }
                func_80244354(temp_s0, 0x90000, 1);
                D_802AC918[(sp38) / 4] = 0;
                func_802313DC(spBC, 0x40000);
            }
        }
        break;
    case 0x40:
        if (func_80270714((s32) (s16) temp_s0) != 0) {
            func_80244354(temp_s0, 0x80000, 1);
            func_80249F5C(temp_s0);
        }
        break;
    case 0x40000:
        D_802AC9C8[(sp38) / 4] = D_800B0DD8[D_802AC960];
        func_80244354(temp_s0, 0x90020, 1);
        D_802AC918[(sp38) / 4] = 0;
        func_802313DC(spBC, 0x40000);
        break;
    case 0x100000:
        temp_v1_3 = ((UnkObj *)func_802443F4(temp_s0));
        spBC = temp_v1_3;
        M2C_FIELD(temp_v1_3, f32 *, 0x68) = 40.0f;
        func_80244354(temp_s0, 0x90020, 1);
        D_802AC918[(sp38) / 4] = 0;
        func_802313DC(spBC, 0x40000);
        break;
    case 0x4000000:
        func_80244354(temp_s0, 0x90000, 1);
        D_802AC918[(sp38) / 4] = 0;
        func_802313DC(spBC, 0x40000);
        func_80244354(temp_s0, 0x04000020, 1);
        func_802444B8(temp_s0, 0x15);
        break;
    case 0x400:
        func_80244354(temp_s0, 0x90000, 1);
        func_80243D90(temp_s0, 0x400, 1);
        func_80244354(temp_s0, 0x20, 1);
        break;
    case 0x800:
        func_8027750C((s32) (s16) temp_s0);
        break;
    case 0x4000:
        func_802712C4(func_8027799C((s32) func_80274F64((s32) (s16) temp_s0)));
        break;
    case 0x10000:
        func_80244354(temp_s0, 0x80000, 1);
        func_80249E30((s16) temp_s0);
        break;
    case 0x20000:
        func_80244354(temp_s0, 0x80000, 1);
        func_80249D74(temp_s0);
        break;
    case 0x200000:
        func_80244354(temp_s0, 0x80000, 1);
        func_80249D30(temp_s0);
        break;
    case 0x400000:
        if ((D_802AC8BC != 0) && (D_802AC8BC != 0x20) && (D_802AC8BC != 0x40) && (D_802AC8BC != 0x60) && (D_802AC8BC != 0x80) && (D_802AC8BC != 0xA0)) {

        }
        func_80244354(temp_s0, 0x420, 0);
        temp_v1_4 = &D_800AEDF0[temp_s0];
        var_a0_2 = func_80244BA4(temp_s0, 0x02000000);
        if (var_a0_2 == 0) {
            sp34 = temp_v1_4;
            func_80244354(temp_s0, 0x10000, 0);
        }
        temp_v1_4->unk48 = 1;
        M2C_FIELD(spBC, f32 *, 0x70) = 1.6333334f;
        break;
    }
}

void func_80249FD4(s32 arg0, s32 arg1) {
    s32 sp30;
    UnkStruct_800AEDF0 *sp18;
    UnkStruct_800AEDF0 *var_a1;
    s32 var_v1;

    M2C_FIELD(&sp30, s32 *, 0) = M2C_FIELD(&D_802A0DA4, s32 *, 0);
    M2C_FIELD(&sp30, s32 *, 4) = (s32) M2C_FIELD(&D_802A0DA4, s32 *, 4);
    M2C_FIELD(&sp30, s32 *, 0xC) = (s32) M2C_FIELD(&D_802A0DA4, s32 *, 0xC);
    M2C_FIELD(&sp30, s32 *, 8) = (s32) M2C_FIELD(&D_802A0DA4, s32 *, 8);
    func_802444B8(arg0, 4);
    func_80244354(arg0, 0xA0, 1);
    var_a1 = &D_800AEDF0[arg0];
    var_a1->unk3C = arg1;
    if ((D_802AC5D0 & 4) || (var_a1 == D_800AEDF0)) {
        sp18 = var_a1;
        func_802479F0(&sp30);
        var_a1 = sp18;
    }
    var_v1 = func_80243EB4(arg0, 0x2000);
    if (var_v1 != 0) {
        D_802ACE90[var_a1->unkA4] = 60.0f;
    }
    var_a1->unk38 &= ~0x80;
}

void func_80249F5C(s32 arg0) {
    UnkStruct_800AEDF0 *temp_v0;

    func_802444B8(6, 0);
    func_80244354(arg0, 0x60, 1);
    func_80244354(arg0, 0x8000, 0);
    temp_v0 = &D_800AEDF0[arg0];
    temp_v0->unkAC = 0;
    temp_v0->unk38 &= ~0x40;
}

void func_80249F24(s32 arg0) {
    func_80244354(0x04000020, 1, 0);
    func_802444B8(arg0, 0x15);
}

void func_80249EEC(s32 arg0) {
    func_80243D90(0x400, 1, 0);
    func_80244354(arg0, 0x20, 1);
}

void func_80249E30(s16 arg0) {
    UnkStruct_800AEDF0 *sp24;
    UnkStruct_800AEDF0 *temp_a2;
    s32 var_v1;

    temp_a2 = &D_800AEDF0[arg0];
    var_v1 = func_80244BA4(arg0, 0x40);
    if (var_v1 != 0) {
        sp24 = temp_a2;
        func_80270770(arg0, 1);
        temp_a2->unk2C = 0;
    }
    func_80244354((s32) arg0, 0x148, 0);
    func_80244354((s32) arg0, 0x20, 1);
    func_80243D90((s32) arg0, 0x10000, 1);
    func_802444B8((s32) arg0, 0x17);
}

void func_80249D74(s32 arg0) {
    UnkObj *sp34;
    UnkStruct_800AEDF0 *sp18;
    UnkObj *temp_a3;
    UnkStruct_800AEDF0 *temp_v1;
    s32 temp_v0;
    s32 var_a1;

    temp_v1 = &D_800AEDF0[arg0];
    var_a1 = func_80243EB4(arg0, 0x20000);
    if (var_a1 == 0) {
        temp_a3 = temp_v1->unk28;
        sp18 = temp_v1;
        sp34 = temp_a3;
        func_80243D90(0x20000, 1, (s32) temp_a3);
        temp_v1->unkB8 = 0x3C;
        temp_v0 = func_80231274(0x4E, 0x11200000, 0xD0, temp_a3);
        temp_v1->unkB4 = temp_v0;
        M2C_FIELD(temp_v0, f32 *, 0x4C) = 0.0f;
        M2C_FIELD(temp_v1->unkB4, f32 *, 0x50) = 200.0f;
        M2C_FIELD(temp_v1->unkB4, f32 *, 0x54) = 0.0f;
    }
}

void func_80249D30(s32 arg0) {
    func_80244354(0x20, 1, 0);
    func_80243D90(arg0, 0x200000, 1);
    func_802444B8(arg0, 0x18);
}

void func_80249AD4(s32 arg0) {
    s32 sp78;
    UnkStruct_800AEDF0 *sp18;
    UnkStruct_800AEDF0 *temp_a3;
    s32 *temp_v0;
    s32 temp_a1;
    s32 temp_t0;
    s32 temp_t9;
    s32 temp_v1;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;

    temp_v1 = func_80243DDC() * 4;
    temp_a1 = D_802AC980[(temp_v1) / 4];
    temp_t0 = func_80243DDC();
    switch (temp_a1) {                              /* irregular */
    case 0x40000:
        temp_v0 = temp_v1 + &D_802AC9C8;
        temp_t9 = *temp_v0 - 1;
        *temp_v0 = temp_t9;
        if (temp_t9 == 0) {
            func_80244354(temp_t0, 0x80020, 0);
            return;
        }
        return;
    case 0x100000:
        temp_a3 = &D_800AEDF0[temp_t0];
        if (M2C_FIELD(temp_a3->unk28, f32 *, 0x68) == 0.0f) {
            sp78 = temp_t0;
            sp18 = temp_a3;
            func_80244354(temp_t0, D_802AC980[temp_t0] | 0x80020, 0);
            var_v1 = func_80244BA4(temp_t0, 0x02000000);
            if (var_v1 == 0) {
                func_80244354(temp_t0, 0x10000, 0);
                return;
            }
        }
        break;
    case 0x400:
    case 0x4000:
    case 0x10000:
    case 0x4000000:
        sp78 = temp_t0;
        func_80244354(temp_t0, 0x80000, 0);
        var_v1_2 = func_80244BA4(temp_t0, 0x02000000);
        if (var_v1_2 == 0) {
            func_80244354(temp_t0, 0x10000, 0);
            return;
        }
        break;
    default:
        var_v1_3 = 0;
        if (temp_a1 == (D_800AEDF0[func_80243DDC()].unk10 & temp_a1)) {
            var_v1_3 = 1;
        }
        if (var_v1_3 == 0) {
            sp78 = temp_t0;
            func_80244354(temp_t0, D_802AC980[temp_t0] | 0x80000, 0);
            var_v1_4 = func_80244BA4(temp_t0, 0x02000000);
            if (var_v1_4 == 0) {
                func_80244354(temp_t0, 0x10000, 0);
            }
        }
        break;
    }
}

void func_80249A30(s32 arg0) {
    s32 sp38[3];
    void *temp_v0;

    temp_v0 = M2C_FIELD(((UnkObj *)func_802443F4(arg0)), void **, 0x40);
    func_8026DCAC(M2C_FIELD(temp_v0, f32 *, 0x10), M2C_FIELD(temp_v0, f32 *, 0x14), M2C_FIELD(temp_v0, f32 *, 0x18), sp38, 2);
    if (func_8026E278(func_8026D7D8(sp38[0], sp38[1], sp38[2])) != 0) {
        func_80244354(arg0, 0x10, 1);
        return;
    }
    func_80244354(arg0, 0x10, 0);
}

void func_802498D4(s32 arg0, f32 arg1) {
    UnkObj *sp54;
    s32 sp50;
    UnkStruct_800AEDF0 *sp20;
    UnkObj *temp_a0;
    UnkStruct_800AEDF0 *temp_t0;
    s32 *temp_v0_2;
    s32 temp_a0_2;
    s32 temp_t3;
    s32 temp_v0;
    s32 var_v1;
    s32 var_v1_2;

    temp_t0 = &D_800AEDF0[arg0];
    temp_a0 = temp_t0->unk28;
    sp20 = temp_t0;
    sp54 = temp_a0;
    temp_v0 = func_8022F4AC((s32) temp_a0, 2, temp_t0->unk4C);
    if ((temp_v0 != 0) && (arg1 > 0.0f)) {
        temp_v0_2 = &D_802AC948[arg0];
        temp_t3 = *temp_v0_2 - 1;
        *temp_v0_2 = temp_t3;
        if (temp_t3 == 0) {
            sp50 = temp_v0;
            sp20 = temp_t0;
            func_80244354(arg0, 1, 0);
            if (temp_v0 != 0) {
                temp_a0_2 = temp_t0->unk10;
                var_v1 = 0;
                if (!(temp_a0_2 & 0x11C0)) {
                    var_v1 = 1;
                }
                if (var_v1 != 0) {
                    if (sp54->unk6C == 0.0f) {
                        func_80249810(arg0, temp_v0, 1);
                    } else {
                        var_v1_2 = 0;
                        if ((temp_a0_2 & 0x10000) == 0x10000) {
                            var_v1_2 = 1;
                        }
                        if (var_v1_2 == 0) {
                            func_80247D74(arg0, 22.5f, 8.0f, 1, NULL);
                        }
                    }
                }
            }
        }
    } else {
        func_80244354(arg0, 1, 0);
    }
}

void func_80249810(s32 arg0, s32 arg1, s32 arg2) {
    UnkStruct_800AEDF0 *sp18;                       /* compiler-managed */
    UnkStruct_800AEDF0 *temp_a3;
    s32 var_v1;

    temp_a3 = &D_800AEDF0[arg0];
    var_v1 = func_80244BA4(arg0, 0x8000);
    if (var_v1 == 0) {
        sp18 = temp_a3;
        func_802444B8(7, (s32) temp_a3);
    } else {
        sp18 = temp_a3;
        func_802444B8(0x10, (s32) temp_a3);
    }
    sp18 = (s32 *) temp_a3;
    func_80244354(arg0, 0x120, 1);
    M2C_FIELD((s32 *) temp_a3, s32 *, 0x38) = (s32) (M2C_FIELD((s32 *) temp_a3, s32 *, 0x38) & ~0x100);
    M2C_FIELD((s32 *) temp_a3, s32 *, 0x30) = arg1;
    M2C_FIELD((s32 *) temp_a3, s32 *, 0xBC) = arg2;
}

void func_802497D8(s32 arg0) {
    D_802AC948[arg0] = 2;
    func_80244354(1, 1, 0);
}

void func_80249648(s32 arg0, UnkObj *arg1, s32 arg2) {
    UnkStruct_800AEDF0 *sp20;
    UnkStruct_800AEDF0 *temp_t8;
    s32 temp_v0;
    s32 var_v1;

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
    UnkObj *sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    UnkStruct_800AEDF0 *sp28;
    s32 sp24;
    s32 *sp20;
    UnkStruct_800AEDF0 *temp_t8;
    s32 *temp_a3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    temp_t8 = &D_800AEDF0[arg0];
    sp28 = temp_t8;
    sp54 = temp_t8->unk28;
    var_v1 = func_80244BA4(arg0, 0x1000);
    if (var_v1 == 0) {
        var_v1_2 = arg0 * 4;
        if (arg1 != 0) {
            var_v1_2 = arg0 * 4;
            if (arg1 != 1) {
                var_v1_2 = arg0 * 4;
                if (arg1 != 2) {
                    var_v1_2 = arg0 * 4;
                } else {
                    D_802AC8D0[(var_v1_2) / 4] = 0x12C;
                    D_802AC900[(var_v1_2) / 4] = 0x1E;
                }
            } else {
                D_802AC8D0[(var_v1_2) / 4] = 0x258;
                D_802AC900[(var_v1_2) / 4] = 0x32;
            }
        } else {
            D_802AC8D0[(var_v1_2) / 4] = 0x4B0;
            D_802AC900[(var_v1_2) / 4] = 0x50;
        }
        sp24 = var_v1_2;
        func_80247848(arg0, 1);
        var_v1_3 = var_v1_2;
        temp_a3 = var_v1_3 + &D_802AC8E8;
        sp4C = 80.0f;
        sp48 = 0.0f;
        sp50 = 0.0f;
        if (*temp_a3 == -1) {
            sp24 = var_v1_3;
            sp20 = temp_a3;
            var_v1_3 = sp24;
            *sp20 = func_8028A7CC(5, &sp48, (s32) sp54);
        }
        sp24 = var_v1_3;
        func_8022979C((s32) sp54->unk40, 4, 0xC);
        func_8022979C((s32) sp54->unk40, 5, 0xD);
        D_802ACA30[(var_v1_3) / 4] = 0.0f;
    }
    func_80244354(arg0, 0x1C0, 0);
    func_80244354(arg0, 0x1020, 1);
    sp28->unk38 &= ~0x1000;
}

void func_8024891C(s32 arg0) {
    s32 sp2DC;
    s32 sp2D4;
    s32 sp2CC;
    s32 sp2C8;
    s32 sp2C4;
    UnkObj *sp2C0;
    s32 sp2BC;
    UnkObj *sp2B8;
    UnkObj *sp2B4;
    f32 sp2B0;
    f32 sp2AC;
    f32 sp2A8;
    UnkStruct_800AEDF0 *sp28;
    UnkStruct_800AEDF0 *sp24;
    UnkStruct_800AEDF0 *sp20;
    UnkObj *temp_a0;
    UnkStruct_800AEDF0 *temp_t2;
    UnkStruct_800AEDF0 *temp_t2_2;
    UnkStruct_800AEDF0 *temp_t3;
    UnkStruct_800AEDF0 *var_a3;
    UnkStruct_800AEDF0 *var_t0;
    UnkStruct_800AEDF0 *var_t2;
    UnkStruct_800AEDF0 *var_t3;
    f32 temp_fv1;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t6;
    s32 var_t7;
    s32 var_v0;
    s32 var_v0_10;
    s32 var_v0_11;
    s32 var_v0_12;
    s32 var_v0_13;
    s32 var_v0_14;
    s32 var_v0_15;
    s32 var_v0_16;
    s32 var_v0_17;
    s32 var_v0_18;
    s32 var_v0_19;
    s32 var_v0_20;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    s32 var_v0_9;
    s32 var_v1;
    s32 var_v1_10;
    s32 var_v1_11;
    s32 var_v1_12;
    s32 var_v1_13;
    s32 var_v1_14;
    s32 var_v1_15;
    s32 var_v1_16;
    s32 var_v1_17;
    s32 var_v1_18;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_6;
    s32 var_v1_7;
    s32 var_v1_8;
    s32 var_v1_9;

    temp_t3 = &D_800AEDF0[arg0];
    temp_a0 = temp_t3->unk28;
    sp28 = temp_t3;
    sp2C0 = temp_a0;
    temp_v0 = func_8022F550((s32) temp_a0, 1);
    if (temp_v0 != 0) {
        sp2BC = temp_v0;
        sp28 = temp_t3;
        var_t3 = temp_t3;
        var_a2 = var_t3->unk68;
        sp2DC = func_802441AC((void *) temp_v0);
        var_v1 = 0;
        if ((var_a2 & 0x10) == 0x10) {
            var_v1 = 1;
        }
        if (var_v1 == 0) {
            var_v0 = func_80243EB4(sp2DC, 0x10);
            if (var_v0 != 0) {
                goto block_7;
            }
        } else {
block_7:
            var_v0_2 = 0;
            if ((var_a2 & 0x200) == 0x200) {
                var_v0_2 = 1;
            }
            if (var_v0_2 == 0) {
                var_t2 = &D_800AEDF0[sp2DC];
                temp_a1 = var_t2->unk68;
                var_v0_3 = 0;
                if ((temp_a1 & 0x200) == 0x200) {
                    var_v0_3 = 1;
                }
                if (var_v0_3 == 0) {
                    var_v0_4 = 0;
                    if ((var_a2 & 0x80) == 0x80) {
                        var_v0_4 = 1;
                    }
                    if (var_v0_4 == 0) {
                        var_v0_5 = 0;
                        if ((temp_a1 & 0x80) == 0x80) {
                            var_v0_5 = 1;
                        }
                        if (var_v0_5 == 0) {
                            var_v0_6 = 0;
                            if ((var_a2 & 0x40) == 0x40) {
                                var_v0_6 = 1;
                            }
                            if (var_v0_6 == 0) {
                                var_v0_7 = 0;
                                if ((temp_a1 & 0x40) == 0x40) {
                                    var_v0_7 = 1;
                                }
                                if (var_v0_7 == 0) {
                                    temp_v0_2 = var_t3->unk18;
                                    temp_a0_2 = var_t2->unk18 & 0x404;
                                    var_t3->unk68 = var_a2 & ~0x3F;
                                    var_t3->unk18 = temp_v0_2 & ~0x404;
                                    sp2CC = temp_a1 & 0x3D;
                                    temp_t6 = var_t2->unk18 & ~0x404;
                                    temp_t4 = var_t2->unk68 & ~0x3F;
                                    temp_a3 = var_a2 & 0x3D;
                                    var_t2->unk68 = temp_t4;
                                    var_t2->unk18 = temp_t6;
                                    var_t2->unk18 = temp_t6 | (temp_v0_2 & 0x404);
                                    var_t2->unk68 = temp_t4 | temp_a3;
                                    temp_a2 = var_t3->unk68 | sp2CC;
                                    var_t3->unk18 |= temp_a0_2;
                                    var_t3->unk68 = temp_a2;
                                    var_v0_8 = 0;
                                    if ((temp_a2 & 4) == 4) {
                                        var_v0_8 = 1;
                                    }
                                    if (var_v0_8 == 0) {
                                        var_v1_2 = 0;
                                        if ((temp_a2 & 1) == 1) {
                                            var_v1_2 = 1;
                                        }
                                        if (var_v1_2 == 0) {
                                            if (temp_a3 & 4) {
                                                sp2D4 = temp_a3;
                                                sp20 = var_t2;
                                                sp28 = var_t3;
                                                func_8024694C(arg0, 1, 0);
                                            }
                                            if (temp_a3 & 1) {
                                                sp20 = var_t2;
                                                sp28 = var_t3;
                                                func_8024694C(arg0, 2, 0);
                                            }
                                        }
                                    }
                                    var_a2_2 = var_t3->unk68;
                                    var_v0_9 = 0;
                                    if ((var_a2_2 & 0x40) == 0x40) {
                                        var_v0_9 = 1;
                                    }
                                    if (var_v0_9 == 0) {
                                        var_v1_3 = 0;
                                        if ((var_a2_2 & 4) == 4) {
                                            var_v1_3 = 1;
                                        }
                                        if (var_v1_3 != 0) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_8024694C(arg0, 1, 1);
                                            var_a2_2 = var_t3->unk68;
                                        }
                                        var_v1_4 = 0;
                                        if ((var_a2_2 & 1) == 1) {
                                            var_v1_4 = 1;
                                        }
                                        if (var_v1_4 != 0) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_8024694C(arg0, 2, 1);
                                            var_a2_2 = var_t3->unk68;
                                        }
                                        var_v1_5 = 0;
                                        if ((var_a2_2 & 8) == 8) {
                                            var_v1_5 = 1;
                                        }
                                        var_t6 = var_a2_2 & 0x20;
                                        if (var_v1_5 != 0) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_802488C0(arg0);
                                            var_t6 = var_t3->unk68 & 0x20;
                                        }
                                        var_v1_6 = 0;
                                        if (var_t6 == 0x20) {
                                            var_v1_6 = 1;
                                        }
                                        if (var_v1_6 != 0) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_80248864(arg0);
                                        }
                                        if (var_t3->unk18 & 0x404) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_80246C3C(arg0, 3, 1);
                                        }
                                    }
                                    temp_a1_2 = var_t2->unk68;
                                    var_v0_10 = 0;
                                    if ((temp_a1_2 & 4) == 4) {
                                        var_v0_10 = 1;
                                    }
                                    if (var_v0_10 == 0) {
                                        var_v1_7 = 0;
                                        if ((temp_a1_2 & 1) == 1) {
                                            var_v1_7 = 1;
                                        }
                                        if (var_v1_7 == 0) {
                                            if (sp2CC & 4) {
                                                sp20 = var_t2;
                                                sp28 = var_t3;
                                                func_8024694C(sp2DC, 1, 0);
                                            }
                                            if (sp2CC & 1) {
                                                sp20 = var_t2;
                                                sp28 = var_t3;
                                                func_8024694C(sp2DC, 2, 0);
                                            }
                                        }
                                    }
                                    var_a1 = var_t2->unk68;
                                    var_v1_8 = 0;
                                    if ((var_a1 & 0x40) == 0x40) {
                                        var_v1_8 = 1;
                                    }
                                    if (var_v1_8 == 0) {
                                        var_v1_9 = 0;
                                        if ((var_a1 & 4) == 4) {
                                            var_v1_9 = 1;
                                        }
                                        if (var_v1_9 != 0) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_8024694C(sp2DC, 1, 1);
                                            var_a1 = var_t2->unk68;
                                        }
                                        var_v1_10 = 0;
                                        if ((var_a1 & 1) == 1) {
                                            var_v1_10 = 1;
                                        }
                                        if (var_v1_10 != 0) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_8024694C(sp2DC, 2, 1);
                                            var_a1 = var_t2->unk68;
                                        }
                                        var_v1_11 = 0;
                                        if ((var_a1 & 8) == 8) {
                                            var_v1_11 = 1;
                                        }
                                        var_t7 = var_a1 & 0x20;
                                        if (var_v1_11 != 0) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_802488C0(sp2DC);
                                            var_a1 = var_t2->unk68;
                                            var_t7 = var_a1 & 0x20;
                                        }
                                        var_v1_12 = 0;
                                        if (var_t7 == 0x20) {
                                            var_v1_12 = 1;
                                        }
                                        if (var_v1_12 != 0) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_80248864(sp2DC);
                                        }
                                        if (var_t2->unk18 & 0x404) {
                                            sp20 = var_t2;
                                            sp28 = var_t3;
                                            func_80246C3C(sp2DC, 3, 1);
                                        }
                                    }
                                    sp20 = var_t2;
                                    sp28 = var_t3;
                                    func_80243D90(arg0, 0x40, 1);
                                    var_t3->unk7C = 0x1E;
                                    func_80243D90(sp2DC, 0x40, 1);
                                    var_t2->unk7C = 0x1E;
                                    var_a2 = var_t3->unk68;
                                }
                            }
                        }
                    }
                }
            }
        }
        temp_a0_3 = var_a2 & 0x200;
        sp2C8 = -1;
        var_v0_11 = 0;
        if (temp_a0_3 == 0x200) {
            var_v0_11 = 1;
        }
        if (var_v0_11 != 0) {
            var_v0_12 = 0;
            if ((var_t3->unk10 & 0x1000) == 0x1000) {
                var_v0_12 = 1;
            }
            if (var_v0_12 == 0) {
                temp_t2 = &D_800AEDF0[sp2DC];
                temp_a1_3 = temp_t2->unk68;
                var_v0_13 = 0;
                if ((temp_a1_3 & 0x2000) == 0x2000) {
                    var_v0_13 = 1;
                }
                if (var_v0_13 == 0) {
                    var_v0_14 = 0;
                    if ((temp_a1_3 & 0x200) == 0x200) {
                        var_v0_14 = 1;
                    }
                    if (var_v0_14 == 0) {
                        var_v0_15 = 0;
                        if ((temp_a1_3 & 0x80) == 0x80) {
                            var_v0_15 = 1;
                        }
                        if (var_v0_15 == 0) {
                            if ((temp_t2->unk14 != 0) && (M2C_FIELD(sp2C0, s32 *, 0x44) == 0)) {
                                if (sp2C0->unk6C == 0.0f) {
                                    sp2C8 = sp2DC;
                                    sp2C4 = arg0;
                                }
                            }
                        }
                    }
                }
            }
        }
        var_v1_13 = 0;
        if ((var_a2 & 0x2000) == 0x2000) {
            var_v1_13 = 1;
        }
        if (var_v1_13 == 0) {
            var_v1_14 = 0;
            if ((var_a2 & 0x80) == 0x80) {
                var_v1_14 = 1;
            }
            if (var_v1_14 == 0) {
                var_v1_15 = 0;
                if (temp_a0_3 == 0x200) {
                    var_v1_15 = 1;
                }
                if (var_v1_15 == 0) {
                    if (var_t3->unk14 != 0) {
                        temp_t2_2 = &D_800AEDF0[sp2DC];
                        var_v1_16 = func_802452AC(sp2DC, 0x401000);
                        if (var_v1_16 != 0) {
                            var_v1_17 = func_80243EB4(sp2DC, 0x200);
                            if ((var_v1_17 != 0) && (M2C_FIELD(sp2BC, s32 *, 0x44) == 0) && (sp2C0->unk6C == 0.0f)) {
                                sp2C8 = arg0;
                                sp2C4 = sp2DC;
                            }
                        }
                    }
                }
            }
        }
        if (sp2C8 != -1) {
            var_t0 = &D_800AEDF0[sp2C8];
            var_a3 = &D_800AEDF0[sp2C4];
            sp2B8 = var_t0->unk28;
            sp2B4 = var_a3->unk28;
            if (var_t0->unk2C != 0) {
                sp24 = var_a3;
                sp28 = var_t0;
                func_80244C30((s16) sp2C8, 1);
            }
            if (var_a3->unk2C != 0) {
                sp24 = var_a3;
                sp28 = var_t0;
                func_80244C30((s16) sp2C4, 1);
            }
            sp24 = var_a3;
            sp28 = var_t0;
            func_80243D90(sp2C8, 0x2000, 1);
            var_t0->unkA4 = sp2C4;
            func_80232AC8((s32) sp2B8, (s32) sp2B4);
            func_80231408(sp2B4, 0x600000);
            var_a3->unkC0 = 0x428C0000;
            temp_v1 = var_t0->unk68;
            var_v0_16 = 0;
            if ((temp_v1 & 2) == 2) {
                var_v0_16 = 1;
            }
            if (var_v0_16 == 0) {
                var_v0_17 = 0;
                if ((temp_v1 & 4) == 4) {
                    var_v0_17 = 1;
                }
                if (var_v0_17 != 0) {
                    var_a3->unkC0 = M2C_BITWISE(s32, (M2C_BITWISE(f32, var_a3->unkC0) + 30.0f));
                }
                var_v0_18 = func_80243EB4(sp2C8, 1);
                if (var_v0_18 != 0) {
                    var_a3->unkC0 = M2C_BITWISE(s32, (M2C_BITWISE(f32, var_a3->unkC0) - 40.0f));
                }
            } else {
                var_v0_19 = 0;
                temp_fv1 = (f32) var_t0->unk74;
                if ((temp_v1 & 4) == 4) {
                    var_v0_19 = 1;
                }
                if (var_v0_19 != 0) {
                    if (M2C_BITWISE(f32, var_t0->unk6C) > 0.0f) {
                        var_a3->unkC0 = M2C_BITWISE(s32, (M2C_BITWISE(f32, var_a3->unkC0) + (6.0f * temp_fv1)));
                    }
                    if (M2C_BITWISE(f32, var_t0->unk6C) < 0.0f) {
                        var_a3->unkC0 = M2C_BITWISE(s32, (M2C_BITWISE(f32, var_a3->unkC0) + (6.0f * (4.0f - temp_fv1))));
                    }
                }
                var_v0_20 = func_80243EB4(sp2C8, 1);
                if (var_v0_20 != 0) {
                    if (M2C_BITWISE(f32, var_t0->unk6C) > 0.0f) {
                        var_a3->unkC0 = M2C_BITWISE(s32, (M2C_BITWISE(f32, var_a3->unkC0) + (-8.0f * temp_fv1)));
                    }
                    if (M2C_BITWISE(f32, var_t0->unk6C) < 0.0f) {
                        var_a3->unkC0 = M2C_BITWISE(s32, ((4.0f - temp_fv1) * -8.0f));
                    }
                }
            }
            D_802ACE90[sp2C4] = 60.0f;
            var_v1_18 = 0;
            sp2AC = 60.0f;
            sp2B0 = M2C_BITWISE(f32, var_a3->unkC0);
            if ((var_t0->unk10 & 0x40) == 0x40) {
                var_v1_18 = 1;
            }
            if (var_v1_18 != 0) {
                sp2AC = 37.0f;
            }
            sp28 = var_t0;
            sp2A8 = 180.0f;
            func_8022FEAC(&sp2A8, sp2B4->unk4C);
            M2C_FIELD(sp2B4, f32 *, 0x70) = 0.0f;
            func_802444B8(sp2C4, 0x12);
            temp_t6_2 = sp2C8 * 4;
            D_802AC998[(temp_t6_2) / 4] = 0x258;
            D_802AC9B0[(temp_t6_2) / 4] = 0x32;
            sp28->unkA8 = sp2C4;
            func_80244354(sp2C4, 2, 0);
        }
    }
}

void func_802488C0(s32 arg0) {
    func_80243D90(0x18, 1, 0);
    D_800AEDF0[arg0].unk78 = 0x4B0;
    func_80246C3C(arg0, 3, 1);
}

void func_80248864(s32 arg0) {
    func_80243D90(0x30, 1, 0);
    D_800AEDF0[arg0].unk78 = 0x4B0;
    func_80246C3C(arg0, 3, 1);
}

void func_8024878C(s32 arg0) {
    UnkStruct_800AEDF0 *sp18;
    UnkStruct_800AEDF0 *temp_a3;
    s32 temp_a0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    func_80244354(2, 0, 0);
    temp_a3 = &D_800AEDF0[arg0];
    var_v1 = func_80244BA4(arg0, 0x1000);
    if (var_v1 == 0) {
        sp18 = temp_a3;
        func_80244354(arg0, 0x20, 0);
        temp_a0 = temp_a3->unk10;
        var_v1_2 = 0;
        if (!(temp_a0 & 0x20C0)) {
            var_v1_2 = 1;
        }
        if (var_v1_2 == 0) {
            var_v1_3 = 0;
            if ((temp_a0 & 0x8000) == 0x8000) {
                var_v1_3 = 1;
            }
            if (var_v1_3 == 0) {
                func_802444B8(arg0, 0);
                return;
            }
            func_802444B8(arg0, 0xC);
        }
    }
}

void func_8024857C(s32 arg0) {
    s32 sp60[5];
    UnkStruct_800AEDF0 *sp28;
    UnkModel *temp_v0;
    UnkStruct_800AEDF0 *temp_t1;
    s32 *temp_v0_2;
    s32 *temp_v0_3;
    s32 *temp_v0_4;
    s32 *temp_v0_5;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    temp_t1 = &D_800AEDF0[arg0];
    temp_v0 = temp_t1->unk28->unk40;
    sp28 = temp_t1;
    func_8026DCAC(temp_v0->unk10, temp_v0->unk14, temp_v0->unk18, sp60, 2);
    var_v1 = 1;
    if (sp60[4] == 0.0f) {
        var_v1 = func_8026D7D8(sp60[0], sp60[1], sp60[2]) & 0xF;
    }
    switch (var_v1) {                               /* irregular */
    case 2:
        temp_v0_2 = &D_802AC8A8[arg0];
        if (!(*temp_v0_2 & 1)) {
            *temp_v0_2 = 1;
            func_80243824(0x50);
            var_v1_2 = 0;
            if ((sp28->unk10 & 0x1000) == 0x1000) {
                var_v1_2 = 1;
            }
            if (var_v1_2 != 0) {
                func_80247C50(arg0);
            }
        }
        break;
    case 9:
        var_v1_3 = 0;
        if ((sp28->unk10 & 0x10000) == 0x10000) {
            var_v1_3 = 1;
        }
        if (var_v1_3 == 0) {
            if (!(D_802AC8A8[arg0] & 2)) {
                func_80248148(arg0, 4);
            }
        }
        break;
    case 10:
        temp_v0_3 = &D_802AC8A8[arg0];
        if (!(*temp_v0_3 & 4)) {
            *temp_v0_3 = 4;
            func_80243824(0x52);
        }
        break;
    case 11:
        temp_v0_4 = &D_802AC8A8[arg0];
        if (!(*temp_v0_4 & 8)) {
            *temp_v0_4 = 8;
            func_80243824(0x53);
        }
        break;
    default:
        temp_v0_5 = &D_802AC8A8[arg0];
        if (*temp_v0_5 != 0) {
            *temp_v0_5 = 0;
        }
        break;
    }
}

void func_80248148(s32 arg0, s32 arg1) {
    UnkObj *sp6C;
    s32 sp68;
    s32 sp60;
    UnkStruct_800AEDF0 *sp28;
    s32 sp24;
    s32 *sp20;
    UnkModel *temp_v0_4;
    UnkStruct_800AEDF0 *temp_v0;
    s32 *temp_v0_3;
    s32 *temp_v1;
    s32 temp_a0;
    s32 temp_v0_2;
    s32 temp_v0_5;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    u32 temp_t2;
    void *temp_a0_2;
    void *temp_a0_3;

    temp_v0 = &D_800AEDF0[arg0];
    if (temp_v0->unk24 != 3) {
        if ((arg1 == 3) || (arg1 == 5)) {
            temp_v0->unk14 = 0;
        } else {
            temp_v0->unk14 -= 1;
        }
        sp28 = temp_v0;
        func_802444B8(0, arg1);
        sp6C = sp28->unk28;
        func_80244354(arg0, 0x21C0, 0);
        sp68 = D_802AC5D0 & 4;
        sp24 = (s32) (s16) arg0;
        func_80270770((s16) arg0, 1);
        temp_v1 = &D_802AC8E8[arg0];
        sp28->unk2C = 0;
        temp_a0 = *temp_v1;
        if (temp_a0 != -1) {
            sp20 = temp_v1;
            func_8028A4E0(temp_a0);
            *temp_v1 = -1;
            func_8022979C((s32) sp6C->unk40, 4, 4);
            func_8022979C((s32) sp6C->unk40, 5, 5);
        }
        func_80247848(arg0, 0);
        if (sp28->unk14 == 0) {
            if (func_8023A870(arg0, arg1) != 0) {
                if (sp68 != 0) {
                    var_v1 = 0;
                    if ((sp28->unk68 & 0x2000) == 0x2000) {
                        var_v1 = 1;
                    }
                    if (var_v1 != 0) {
                        func_80247F90(arg0);
                    }
                    temp_a0_2 = M2C_FIELD(sp6C, void **, 0x44);
                    if (temp_a0_2 != NULL) {
                        temp_v0_2 = func_802441AC(temp_a0_2);
                        sp60 = temp_v0_2;
                        func_80244C30((s16) temp_v0_2, 0);
                        func_802444B8(sp60, 0);
                        func_80243D90(sp60, 0x2000, 0);
                        func_802313DC(sp6C, 0x600000);
                    }
                    var_v1_2 = 0;
                    if ((sp28->unk68 & 0x200) == 0x200) {
                        var_v1_2 = 1;
                    }
                    if (var_v1_2 == 0) {
                        func_8027B0BC((s32) (s16) arg0);
                    }
                }
                func_802313DC(sp6C, 1);
                sp28->unk24 = 3;
                var_v0 = 0;
                if (sp6C->unk6C > 0.0f) {
                    var_v0 = sp28->unk10 & 0x400000;
                }
                sp28->unk10 = var_v0;
            } else {
                func_80244354(arg0, 0x161, 0);
                sp28->unk14 = 1;
            }
        } else {
            sp28->unk2C = 0;
            temp_v0_3 = func_8023A840();
            D_802ACF60 = temp_v0_3;
            if (M2C_FIELD(temp_v0_3, s32 *, 0x10) != 0) {
                if (sp68 != 0) {
                    goto block_28;
                }
                temp_v0_4 = sp6C->unk40;
                func_8028A81C(6, temp_v0_4->unk10, temp_v0_4->unk14 + 200.0f, temp_v0_4->unk18, 0);
            } else {
block_28:
                func_8027B39C(4, (s16) arg0);
            }
            func_80247CD0(arg0, 3);
            func_8026C660(0x1D);
            if (arg0 == 1) {
                temp_t2 = M2C_FIELD(D_802ACF60, u32 *, 4);
                switch (temp_t2) {
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
            if (arg0 == 2) {
                if (M2C_FIELD(D_802ACF60, u32 *, 4) == 5) {
                    func_8026C660(0x1BA);
                }
            }
            temp_a0_3 = M2C_FIELD(sp6C, void **, 0x44);
            if (temp_a0_3 != NULL) {
                temp_v0_5 = func_802441AC(temp_a0_3);
                sp60 = temp_v0_5;
                func_80244C30((s16) temp_v0_5, 1);
                func_802444B8(sp60, 0);
                func_80243D90(sp60, 0x2000, 0);
                func_802313DC(sp6C, 0x600000);
            }
        }
        func_80247C50(arg0);
    }
}

void func_80247F90(s32 arg0) {
    UnkObj *sp84;
    UnkObj *sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    UnkModel *temp_v0;
    UnkObj *temp_a2;
    UnkStruct_800AEDF0 *temp_s0;
    s32 temp_a0;
    s32 var_t2;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    temp_s0 = &D_800AEDF0[arg0];
    sp80 = temp_s0->unk28;
    temp_a2 = ((UnkObj *)func_802443F4(temp_s0->unkA8));
    sp7C = M2C_BITWISE(f32, temp_s0->unkC0) + 100.0f;
    sp78 = 60.0f;
    sp74 = 180.0f;
    sp84 = temp_a2;
    func_8022FEAC(&sp74, temp_a2->unk4C);
    func_80231434(sp84);
    func_80232AA8((s32) sp84);
    func_802313DC(sp84, 0x600000);
    temp_a0 = temp_s0->unk10;
    var_v1 = 0;
    if ((temp_a0 & 0x80) == 0x80) {
        var_v1 = 1;
    }
    var_t2 = temp_a0 & 0x1000;
    if (var_v1 != 0) {
        func_80244C30((s16) arg0, 0);
        var_t2 = temp_s0->unk10 & 0x1000;
    }
    var_v1_2 = 0;
    if (var_t2 == 0x1000) {
        var_v1_2 = 1;
    }
    if (var_v1_2 == 0) {
        func_80244354(arg0, 0x20, 0);
    }
    func_80243D90(arg0, 0x2000, 0);
    var_v1_3 = func_80244BA4(arg0, 0x80);
    if (var_v1_3 != 0) {
        func_802444B8(temp_s0->unkA8, 0xC);
    } else {
        func_802444B8(temp_s0->unkA8, 0);
    }
    temp_v0 = sp84->unk40;
    temp_v0->unk14 += 5.0f;
    func_80247D74(temp_s0->unkA8, 22.5f, 8.0f, 1, sp80);
    M2C_FIELD(sp84, f32 *, 0x70) = 1.6333334f;
    func_80244354(arg0, 0x21C0, 0);
}

void func_80247D74(s32 arg0, f32 arg1, f32 arg2, s32 arg3, UnkObj *arg4) {
    UnkObj *sp5C;
    f32 sp4C[3];
    f32 sp44[2];
    f32 sp40;
    f32 sp34;
    UnkStruct_800AEDF0 *sp1C;
    UnkObj *temp_v1;
    UnkStruct_800AEDF0 *temp_t9;
    f32 temp_fv0;
    f32 var_fa0;
    s32 var_t2;
    s32 var_t3;
    s32 var_t7;

    temp_t9 = &D_800AEDF0[arg0];
    sp1C = temp_t9;
    temp_v1 = temp_t9->unk28;
    M2C_FIELD(temp_v1, f32 *, 0x68) = arg1;
    D_802ACA44 = arg2;
    D_802AC8C8 = arg3;
    if (arg4 != NULL) {
        var_t7 = 0;
        if (arg3 == 1) {
            sp5C = temp_v1;
            func_8022F808(temp_v1, sp4C);
            func_8022F808(arg4, &sp40);
            sp44[0] = sp4C[1];
            if (sp4C[0] == sp40) {
                if (sp4C[2] == sp44[1]) {
                    var_fa0 = -1.0f;
                } else {
                    goto block_6;
                }
            } else {
block_6:
                func_8022FF58(sp4C, &sp40, &sp34);
                var_t2 = 0;
                if (sp34 >= 180.0f) {
                    var_t2 = 1;
                }
                var_t3 = 0;
                var_fa0 = (sp34 + 180.0f) - (360.0f * (f32) var_t2);
                if (var_fa0 >= 180.0f) {
                    var_t3 = 1;
                }
                M2C_FIELD(sp5C->unk40, f32 *, 0x20) = (f32) ((var_fa0 + 180.0f) - (360.0f * (f32) var_t3));
            }
        } else {
            temp_fv0 = M2C_FIELD(temp_v1->unk40, f32 *, 0x20);
            if (temp_fv0 >= 180.0f) {
                var_t7 = 1;
            }
            var_fa0 = (temp_fv0 + 180.0f) - (360.0f * (f32) var_t7);
        }
    } else {
        var_fa0 = M2C_FIELD(temp_v1->unk40, f32 *, 0x20);
    }
    sp1C->unkA0 = func_80243F50(var_fa0);
    if ((arg3 == 1) && (arg4 != NULL)) {
        func_802444B8(arg0, 0xB);
        func_80244354(arg0, 0xA0C8, 0);
        func_80270770((s16) arg0, 1);
        sp1C->unk2C = 0;
        sp1C->unk2C = 0;
    }
    func_80244354(arg0, 0x22, 1);
}

void func_80247CD0(s32 arg0, s32 arg1) {
    s32 sp18;
    f32 *temp_v0;
    s32 temp_v1;
    void *temp_a0;

    temp_v1 = arg0 * 4;
    D_802AC930[(temp_v1) / 4] = arg1;
    sp18 = temp_v1;
    func_80244354(0x30020, 1, 0);
    temp_a0 = ((UnkObj *)func_802443F4(arg0));
    D_802AC918[(temp_v1) / 4] = 0;
    temp_v0 = temp_v1 + &D_802ACA48;
    *temp_v0 = M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x40), f32 *, 0x20);
    D_802ACA60[(temp_v1) / 4] = *temp_v0;
    func_80231408(temp_a0, 0x40000);
}

void func_80247C50(s32 arg0) {
    UnkStruct_800AEDF0 *temp_a3;
    s32 var_v1;

    temp_a3 = &D_800AEDF0[arg0];
    var_v1 = func_80244BA4(arg0, 0x1000);
    if (var_v1 != 0) {
        func_80247A54(arg0, func_8022F4AC((s32) temp_a3->unk28, 2, temp_a3->unk4C), 0, 1);
    }
}

void func_80247A54(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Tbl3_5E3F0 tbl;
    UnkObj *obj;
    UnkStruct_800AEDF0 *p;
    s32 other;

    tbl = *(Tbl3_5E3F0 *)D_802A0D88;
    p = &D_800AEDF0[arg0];
    obj = p->unk28;
    if (func_80244BA4(arg0, 0x200000)) {
        other = (s16)func_802441AC(M2C_FIELD(obj, void **, 0x44));
        func_80270770(other, 1);
        D_800AEDF0[other].unk2C = 0;
        p->unk2C = 0;
    }
    if (arg3 != 0) {
        if (!(D_802AC5D0 & 0x10)) {
            if ((D_802AC5D0 & 4) || arg0 == 0) {
                func_802479F0(tbl.v);
            }
        }
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
    func_80244354(0x108, 0, 0);
    func_80244354(arg0, 0x10000, 1);
    D_802AC918[arg0] = arg1;
    func_80231408(sp1C, 0x40000);
}

void func_80247928(s32 arg0, s32 arg1) {
    D_800AEDF0[arg0].unk4C = arg1;
    func_80244354(0x200, 1, 0);
}

void func_80247848(s32 arg0, s32 arg1) {
    UnkStruct_800AEDF0 *temp_v0;
    UnkStruct_800AEDF0 *temp_v0_2;
    s32 temp_t0;
    s32 temp_t6;
    s32 temp_v1;
    s32 temp_v1_2;

    if (arg1 != 0) {
        temp_v0 = &D_800AEDF0[arg0];
        temp_v1 = temp_v0->unk54;
        if (temp_v1 == 0) {
            temp_t0 = D_802AC9DC + 1;
            temp_v0->unk54 = temp_v1 + 1;
            D_802AC9DC = temp_t0;
            if (temp_t0 == 1) {
                D_802AC9E0 = func_8026C660(0x21);
            }
        }
    } else {
        temp_v0_2 = &D_800AEDF0[arg0];
        temp_v1_2 = temp_v0_2->unk54;
        if (temp_v1_2 != 0) {
            temp_t6 = D_802AC9DC - 1;
            temp_v0_2->unk54 = temp_v1_2 - 1;
            D_802AC9DC = temp_t6;
            if (temp_t6 == 0) {
                func_8026BE80(D_802AC9E0);
                D_802AC9E0 = -1;
            }
        }
    }
}

void func_80247614() {
    s32 temp_a0;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 var_t0;
    s32 var_t5;
    s32 var_t9;
    s32 var_v1;
    s32 var_v1_10;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_6;
    s32 var_v1_7;
    s32 var_v1_8;
    s32 var_v1_9;

    temp_t7 = D_802AC9EC - 1;
    D_802AC9EC = temp_t7;
    if (temp_t7 == 0) {
        var_v1 = func_80243E18(0x20);
        var_t9 = D_802AC9E8 & 0x40;
        if (var_v1 != 0) {
            func_80246F00(0x20, 0);
            var_t9 = D_802AC9E8 & 0x40;
        }
        var_v1_2 = 0;
        if (var_t9 == 0x40) {
            var_v1_2 = 1;
        }
        if (var_v1_2 != 0) {
            func_80246F00(0x40, 0);
        }
        var_v1_3 = func_80243E18(0x10);
        if (var_v1_3 != 0) {
            func_80246F00(0x10, 0);
        }
        var_v1_4 = func_80243E18(0x80);
        if (var_v1_4 != 0) {
            func_80246F00(0x80, 0);
        }
        var_v1_5 = func_80243E18(4);
        if (var_v1_5 != 0) {
            func_80246F00(4, 0);
        }
        var_v1_6 = func_80243E18(2);
        if (var_v1_6 != 0) {
            func_80246F00(2, 0);
        }
        D_802AC9EC = 0;
        D_802AC9E8 = 0;
    }
    temp_a0 = D_802AC9E8;
    var_v1_7 = 0;
    if ((temp_a0 & 0x40) == 0x40) {
        var_v1_7 = 1;
    }
    var_t5 = temp_a0 & 0x10;
    if (var_v1_7 != 0) {
        func_80246808();
        var_t5 = D_802AC9E8 & 0x10;
    }
    var_v1_8 = 0;
    if (var_t5 == 0x10) {
        var_v1_8 = 1;
    }
    if (var_v1_8 != 0) {
        temp_t7_2 = D_802AC9F0 - 1;
        D_802AC9F0 = temp_t7_2;
        if (temp_t7_2 == 0) {
            func_80246078();
        }
    }
    var_v1_9 = 0;
    if ((temp_a0 & 0x80) == 0x80) {
        var_v1_9 = 1;
    }
    var_t0 = temp_a0 & 4;
    if (var_v1_9 != 0) {
        func_80246018();
        var_t0 = D_802AC9E8 & 4;
    }
    var_v1_10 = 0;
    if (var_t0 == 4) {
        var_v1_10 = 1;
    }
    if (var_v1_10 != 0) {
        func_80245FD4();
    }
}

void func_80246F00(s32 arg0, s32 arg1) {
    s32 sp88;
    s32 sp78;
    s32 sp74;
    f32 sp68[2];
    f32 sp64;
    UnkStruct_800AEDF0 *var_s0;
    UnkStruct_800AEDF0 *var_s0_2;
    s16 var_s1;
    s16 var_s1_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_v1;
    s32 var_v1_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_v1;
    void *var_s0_3;

    if (arg1 != 0) {
        var_v1 = func_80243E18(1);
        if (var_v1 == 0) {
            goto block_4;
        }
    } else {
block_4:
        if (arg0 != 4) {
            var_s1 = 0;
            switch (arg0) {                         /* irregular */
            case 0x20:
                var_s1_2 = 0;
                if (arg1 != 0) {
                    var_s0 = D_800AEDF0;
                    do {
                        temp_v0 = var_s0->unk24;
                        if ((temp_v0 == 1) || (temp_v0 == 2)) {
                            temp_v0_2 = var_s0->unk18;
                            temp_t2 = temp_v0_2 | 0x200;
                            var_s0->unk18 = temp_t2;
                            var_s0->unk18 = temp_t2 | 1;
                            var_s0->unk94 = temp_v0_2;
                            var_s0->unk98 = var_s0->unk20;
                            func_80278E84((s32) var_s1_2, 8);
                        }
                        var_s1_2 += 1;
                        var_s0 += 1;
                    } while (var_s1_2 != 4);
                } else {
                    if ((D_800AEDF0[0].unk24 == 1) || (D_800AEDF0[0].unk24 == 2)) {
                        D_800AEDF0[0].unk18 = D_800AEDF0[0].unk94;
                        D_800AEDF0[0].unk20 = D_800AEDF0[0].unk98;
                    }
                    if ((D_800AEDF0[1].unk24 == 1) || (D_800AEDF0[1].unk24 == 2)) {
                        D_800AEDF0[1].unk18 = D_800AEDF0[1].unk94;
                        D_800AEDF0[1].unk20 = D_800AEDF0[1].unk98;
                    }
                    if ((D_800AEDF0[2].unk24 == 1) || (D_800AEDF0[2].unk24 == 2)) {
                        D_800AEDF0[2].unk18 = D_800AEDF0[2].unk94;
                        D_800AEDF0[2].unk20 = D_800AEDF0[2].unk98;
                    }
                    if ((D_800AEDF0[3].unk24 == 1) || (D_800AEDF0[3].unk24 == 2)) {
                        D_800AEDF0[3].unk18 = D_800AEDF0[3].unk94;
                        D_800AEDF0[3].unk20 = D_800AEDF0[3].unk98;
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
            case 0x8:
                var_s0_2 = D_800AEDF0;
                do {
                    if ((var_s0_2->unk14 != 0) && ((temp_v0_3 = var_s0_2->unk24, (temp_v0_3 == 1)) || (temp_v0_3 == 2))) {
                        var_v1_2 = 0;
                        if ((var_s0_2->unk68 & 0x200) == 0x200) {
                            var_v1_2 = 1;
                        }
                        if (var_v1_2 == 0) {
                            func_80246D74(var_s1);
                            func_8024694C((s32) var_s1, 1, arg1);
                        }
                    }
                    var_s1 += 1;
                    var_s0_2 += 1;
                } while (var_s1 != 4);
                D_802AC9EC = 0;
                D_802AC9E8 = 0;
                break;
            }
        } else if (arg1 != 0) {
            sp88 = func_80234248(0xD) + 0x11;
            temp_s0 = func_80234248(D_800B15D8 - 1);
            func_8026E338((f32) sp88, (f32) temp_s0, (f32) (func_80234248(0xA) + 0xA), &sp64, 0);
            temp_v0_4 = func_802867E4(3, sp64, sp68[0], sp68[1]);
            D_802ACF58 = temp_v0_4;
            if (temp_v0_4 != 0) {
                var_s0_3 = *(void **)temp_v0_4;
                sp78 = M2C_FIELD(var_s0_3, s32 *, 8);
loop_51:
                M2C_FIELD(M2C_FIELD(*D_802ACF58, void **, 0x40), f32 *, 0x14) = func_8026E938(M2C_FIELD(var_s0_3, void **, 0x40));
                func_802313DC(*D_802ACF58, sp78);
                func_80231408(*D_802ACF58, 0x10);
                temp_v1 = M2C_FIELD(*D_802ACF58, void **, 0x40);
                sp74 = func_80232D18(*D_802ACF58, 0x10);
                temp_v0_5 = func_8026DF74(M2C_FIELD(temp_v1, f32 *, 0x10), M2C_FIELD(temp_v1, f32 *, 0x14), M2C_FIELD(temp_v1, f32 *, 0x18));
                temp_t1 = temp_v0_5 & 0x2000;
                temp_t2_2 = temp_v0_5 & 0x60;
                if (sp74 != 0) {
                    M2C_FIELD(*D_802ACF58, s32 *, 0x10) = 0;
                    M2C_FIELD(*D_802ACF58, s32 *, 0x14) = 0;
                    M2C_FIELD(*D_802ACF58, s32 *, 0x24) = 0;
                }
                if (temp_t1 != 0) {
block_59:
                    sp88 = func_80234248(0xD) + 0x11;
                    temp_s0_2 = func_80234248(D_800B15D8 - 1);
                    func_8026E338((f32) sp88, (f32) temp_s0_2, (f32) (func_80234248(0xA) + 0xA), &sp64, 0);
                    M2C_FIELD(M2C_FIELD(*D_802ACF58, void **, 0x40), f32 *, 0x10) = sp64;
                    M2C_FIELD(M2C_FIELD(*D_802ACF58, void **, 0x40), f32 *, 0x14) = sp68[0];
                    M2C_FIELD(M2C_FIELD(*D_802ACF58, void **, 0x40), f32 *, 0x18) = sp68[1];
                    var_s0_3 = *D_802ACF58;
                    goto loop_51;
                }
                if (temp_t2_2 != 0) {
                    goto block_59;
                }
                if ((temp_v0_5 & 0xF) != 1) {
                    goto block_59;
                }
                temp_s0_3 = *D_802ACF58;
                if (M2C_FIELD(M2C_FIELD(temp_s0_3, void **, 0x40), f32 *, 0x14) == 20000.0f) {
                    goto block_59;
                }
                if (sp74 != 0) {
                    goto block_59;
                }
                func_80231408(temp_s0_3, sp78 | 0x80000);
                temp_s0_4 = *D_802ACF58;
                func_8022F808(temp_s0_4, (f32 *)((u8 *)temp_s0_4 + 0x58));
                func_8026C660(0x1EA);
            } else {
                arg0 = 0x10;
                func_80246078();
            }
        } else if (!(func_802871D0(D_802ACF58) & 3)) {
            func_8022F808(*D_802ACF58, &sp64);
            sp68[0] += 100.0f;
            func_8028A7CC(1, &sp64, 0);
            M2C_FIELD(M2C_FIELD(*D_802ACF58, void **, 0x40), f32 *, 0x14) = func_8026E8B8();
            func_802313DC(*D_802ACF58, 0x01000000);
            temp_s0_5 = *D_802ACF58;
            func_8022F808(temp_s0_5, (f32 *)((u8 *)temp_s0_5 + 0x58));
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

void func_80246D74(s16 arg0) {
    UnkObj *sp24;
    UnkStruct_800AEDF0 *temp_s1;
    s32 var_t3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;

    temp_s1 = &D_800AEDF0[arg0];
    var_v1 = 0;
    sp24 = temp_s1->unk28;
    if ((temp_s1->unk68 & 4) == 4) {
        var_v1 = 1;
    }
    if (var_v1 != 0) {
        func_80270770(arg0, 1);
        temp_s1->unk2C = 0;
        func_8024694C((s32) arg0, 1, 0);
    }
    var_v1_2 = func_80243EB4(arg0, 1);
    if (var_v1_2 != 0) {
        func_80270770(arg0, 1);
        temp_s1->unk2C = 0;
        func_8024694C((s32) arg0, 2, 0);
    }
    var_v1_3 = func_80243EB4(arg0, 0x80);
    var_t3 = temp_s1->unk68 & 0x100;
    if (var_v1_3 != 0) {
        func_802313DC(sp24, 0x40);
        var_t3 = temp_s1->unk68 & 0x100;
    }
    var_v1_4 = 0;
    if (var_t3 == 0x100) {
        var_v1_4 = 1;
    }
    if (var_v1_4 != 0) {
        func_80246C3C((s32) arg0, 0, 0);
    }
    func_80243D90((s32) arg0, 0xB9, 0);
    var_v1_5 = func_80243E18(1);
    if (var_v1_5 == 0) {
        func_80243D90((s32) arg0, 4, 0);
    }
    temp_s1->unk18 &= ~0x404;
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
        temp_v1->unk8C = 0;
        temp_v1->unk88 = 0x3E4CCCCD;
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
    s32 sp94;
    UnkStruct_800AEDF0 *sp1C;
    UnkObj *temp_a0;
    UnkStruct_800AEDF0 *temp_t0;
    UnkStruct_800AEDF0 *temp_v1;
    f32 var_fv0;
    s32 temp_t4;
    s32 temp_t8;
    s32 var_t4;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    var_v0 = 0;
    temp_t0 = &D_800AEDF0[arg0];
    temp_t8 = temp_t0->unk68 & 0x2000;
    if (temp_t8 == 0x2000) {
        var_v0 = 1;
    }
    var_t4 = sp94;
    if (var_v0 != 0) {
        temp_t4 = temp_t0->unkA8;
        sp94 = temp_t4;
        var_t4 = temp_t4;
    }
    if (arg1 == 2) {
        if (arg2 != 0) {
            var_v1 = 0;
            temp_t0->unk6C = 0xBDCCCCCD;
            temp_t0->unk70 = 0x3F000000;
            if (temp_t8 == 0x2000) {
                var_v1 = 1;
            }
            if (var_v1 != 0) {
                D_800AEDF0[var_t4].unkC4 = -0x3F000000;
            }
            sp1C = temp_t0;
            sp94 = var_t4;
            func_80243D90(arg0, 0x11, temp_t8);
        } else {
            var_v0_2 = 0;
            temp_t0->unk6C = 0x3DCCCCCD;
            temp_t0->unk70 = 0x3F800000;
            if (temp_t8 == 0x2000) {
                var_v0_2 = 1;
            }
            if (var_v0_2 != 0) {
                D_800AEDF0[var_t4].unkC4 = 0x41000000;
            }
        }
    } else if (arg2 != 0) {
        var_v1_2 = 0;
        temp_t0->unk6C = 0x3DCCCCCD;
        temp_t0->unk70 = 0x3FC00000;
        if (temp_t8 == 0x2000) {
            var_v1_2 = 1;
        }
        if (var_v1_2 != 0) {
            D_800AEDF0[var_t4].unkC4 = 0x40C00000;
        }
        sp1C = temp_t0;
        sp94 = var_t4;
        func_80243D90(arg0, 0x14, temp_t8);
    } else {
        var_v0_3 = 0;
        temp_t0->unk6C = 0xBDCCCCCD;
        temp_t0->unk70 = 0x3F800000;
        if (temp_t8 == 0x2000) {
            var_v0_3 = 1;
        }
        if (var_v0_3 != 0) {
            D_800AEDF0[var_t4].unkC4 = -0x3F400000;
        }
    }
    if (arg2 != 0) {
        if (D_802AC9E8 == 0) {
            temp_t0->unk78 = 0x4B0;
        } else {
            temp_t0->unk78 = 0x708;
        }
    }
    var_v1_3 = func_80243EB4(arg0, 0x2000);
    if (var_v1_3 != 0) {
        temp_a0 = temp_t0->unk28;
        temp_v1 = &D_800AEDF0[var_t4];
        temp_v1->unkC0 = 0x428C0000;
        var_fv0 = M2C_FIELD(temp_a0->unk40, f32 *, 0x28);
        if (var_fv0 > 1.0f) {
            temp_v1->unkC0 = M2C_BITWISE(s32, (M2C_BITWISE(f32, temp_v1->unkC0) + 30.0f));
            var_fv0 = M2C_FIELD(temp_a0->unk40, f32 *, 0x28);
        }
        if (var_fv0 < 1.0f) {
            temp_v1->unkC0 = M2C_BITWISE(s32, (M2C_BITWISE(f32, temp_v1->unkC0) - 40.0f));
        }
    }
    sp1C = temp_t0;
    func_80243D90(arg0, 2, 1);
    func_80270770((s16) arg0, 1);
    temp_t0->unk2C = 0;
    temp_t0->unk74 = 0;
}

void func_80246938() {
    D_802AC9EC = 0;
    D_802AC9E8 = 0;
}

void func_80246808() {
    s32 temp_t2;

    func_80282144((s32) D_802ACEA4, (s32) D_802ACEA8, (s32) D_802ACEAC, 50.0f);
    D_802ACEA4 += D_802ACEBC;
    D_802ACEA8 += D_802ACEC0;
    temp_t2 = D_802AC9F0 - 1;
    D_802ACEAC += D_802ACEC4;
    D_802AC9F0 = temp_t2;
    if (temp_t2 == 0) {
        D_802ACEA4 = D_802ACEB0;
        D_802ACEA8 = D_802ACEB4;
        D_802ACEAC = D_802ACEB8;
        func_8024663C();
    }
}

void func_8024663C() {
    f32 temp_fv0;
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    do {
        temp_v0 = func_80234248(7);
        D_802ACEB8 = (f32) (temp_v0 & 1) * 255.0f;
        D_802ACEB0 = (f32) ((s32) (temp_v0 & 2) >> 1) * 255.0f;
        D_802ACEB4 = (f32) ((s32) (temp_v0 & 4) >> 2) * 255.0f;
        func_80234248(2);
        D_802AC9F0 = 0xF;
        temp_fv0 = (f32) 0xF;
        D_802ACEBC = (D_802ACEB0 - D_802ACEA4) / temp_fv0;
        D_802ACEC0 = (D_802ACEB4 - D_802ACEA8) / temp_fv0;
        D_802ACEC4 = (D_802ACEB8 - D_802ACEAC) / temp_fv0;
        if ((D_802ACEBC != 0.0f) || (D_802ACEC0 != 0.0f) || (D_802ACEC4 != 0.0f)) {
            var_s0 = 1;
        }
        var_s0 = 0;
    } while (var_s0 == 0);
}

void func_80246604() {
    s32 temp_t7;

    temp_t7 = D_802AC9F0 - 1;
    D_802AC9F0 = temp_t7;
    if (temp_t7 == 0) {
        func_80246078();
    }
}

void func_80246078() {
    s32 used[5];
    s32 n;
    s32 cnt;
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

    cnt = 0;
    n = 0;
    for (i = 0; i < 4; i++) {
        p = &D_800AEDF0[i];
        if ((p->unk24 == 1 || p->unk24 == 2) && p->unk14 != 0 && !func_80244BA4(i, 0x1000) && !func_80243EF0(i)) {
            obj = p->unk28;
            x[n] = obj->unk40->unk10;
            y[n] = obj->unk40->unk14;
            z[n] = obj->unk40->unk18;
            used[n] = 0;
            r[n] = M2C_FIELD(obj->unk40, f32 *, 0x20);
            flags[i] = M2C_FIELD(obj, s32 *, 8);
            func_802313DC(obj, flags[i]);
            func_80231408(obj, 0x01000010);
            n++;
        }
    }
    for (i = 0; i < 4; i++) {
        p = &D_800AEDF0[i];
        k = 0;
        if ((p->unk24 == 1 || p->unk24 == 2) && p->unk14 != 0 && !func_80244BA4(i, 0x1000) && !func_80243EF0(i)) {
            do {
                j = func_80234248(n - 1);
                if (used[j] == 0) {
                    obj = p->unk28;
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
            if (func_80232D18(p->unk28, 0x10) != 0) {
                cnt++;
            }
            if (p->unk2C != 0 && func_80232D18((void *)p->unk2C, 0x10) != 0) {
                cnt++;
            }
            if (func_80243EB4(i, 0x2000) && func_80232D18(D_800AEDF0[p->unkA8].unk28, 0x10) != 0) {
                cnt++;
            }
        }
    }
    m = 0;
    for (i = 0; i != 4; i++) {
        p = &D_800AEDF0[i];
        obj = p->unk28;
        if ((p->unk24 == 1 || p->unk24 == 2) && p->unk14 != 0 && !func_80244BA4(i, 0x1000) && !func_80243EF0(i)) {
            if (cnt == 0) {
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
    s32 temp_t7;

    temp_t7 = D_802AC9F0 - 1;
    D_802AC9F0 = temp_t7;
    if (temp_t7 == 0) {
        func_80238A10(func_802500D4, 0, 0, 0, 0x130);
        D_802AC9F0 = 0xB4;
    }
}

void func_80245FD4() {
    if (func_802871D0(D_802ACF58) & 3) {
        D_802AC9EC = 0;
        func_80245FA0(5, 0);
    }
}

void func_80245FA0(s32 arg0, s32 arg1) {
    s32 var_v0;

    if (arg1 == 1) {
        var_v0 = D_802AC9E8 | arg0;
    } else {
        var_v0 = D_802AC9E8 & (arg0 ^ -1);
    }
    D_802AC9E8 = var_v0;
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
    UnkStruct_800AEDF0 *var_s1;
    s32 var_s0;
    void *temp_v0;

    D_802AC894 = 0;
    temp_v0 = malloc(0x1000);
    D_802ACF04 = temp_v0;
    D_802AC898 = func_80238A10(func_8024FFF0, 0, (s32) temp_v0, 0x1000, 0x70);
    var_s1 = D_800AEDF0;
    var_s0 = 0;
    do {
        if (var_s1->unk24 != 0) {
            var_s1->unk68 = 0;
            func_802459BC(var_s0);
        }
        var_s0 += 1;
        var_s1 += 1;
    } while (var_s0 != 5);
    func_80237664();
    func_802362D4(0x1F);
    D_802AC8BC = 0;
    D_802ACA24 = 2.0f;
    D_802AC95C = 3;
    D_802AC97C = 1;
    D_802AC9DC = 0;
    D_802AC9E0 = -1;
    D_802AC9E8 = 0;
    if (D_802AC5D0 & 4) {
        func_80287008(3, 0x1C, 0xD2);
    }
}

void func_802459BC(s32 arg0) {
    s32 sp38;
    UnkModel *temp_v0_2;
    UnkObj *temp_s0;
    UnkObj *temp_v0;
    UnkStruct_800AEDF0 *temp_s2;
    s32 temp_s0_2;
    s32 var_s0;
    s32 var_s1;
    s32 var_v1;
    void *temp_v0_3;

    temp_v0 = func_80231274(0x49, 0x0D000011, 0x70, NULL);
    temp_s2 = &D_800AEDF0[arg0];
    temp_s2->unk28 = temp_v0;
    temp_v0->unk40->unk10 = temp_s2->unk0;
    temp_s2->unk28->unk40->unk14 = temp_s2->unk4;
    temp_s2->unk28->unk40->unk18 = temp_s2->unk8;
    M2C_FIELD(temp_s2->unk28->unk40, f32 *, 0x20) = (f32) temp_s2->unkC;
    M2C_FIELD(temp_s2->unk28, s32 *, 0x30) = 1;
    M2C_FIELD(temp_s2->unk28, f32 *, 0x34) = 30.0f;
    M2C_FIELD(temp_s2->unk28, f32 *, 0x38) = 51.0f;
    temp_s2->unk28->unk6C = 0.0f;
    M2C_FIELD(temp_s2->unk28, f32 *, 0x70) = 1.6333334f;
    M2C_FIELD(temp_s2->unk28, f32 *, 0x68) = 0.0f;
    M2C_FIELD(temp_s2->unk28, s32 *, 0xC) = 0x1FF0;
    func_80229F74((s32) temp_s2->unk28->unk40);
    func_8022984C((s32) temp_s2->unk28->unk40);
    var_v1 = func_80243EB4(arg0, 0x200);
    var_s1 = sp38;
    if (var_v1 != 0) {
        temp_s0 = temp_s2->unk28;
        func_8022979C((s32) temp_s0->unk40, 4, 4);
        func_8022979C((s32) temp_s0->unk40, 5, 5);
        func_80231408(temp_s0, 0x80000);
        M2C_FIELD(temp_s0->unk40, s16 *, 0x36) = 0x80;
        temp_v0_2 = temp_s0->unk40;
        M2C_FIELD(temp_v0_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 0xC) | 0x1000);
        var_s1 = sp38;
    }
    var_s0 = 0;
    do {
        switch (arg0) {                             /* irregular */
        case 0:
            var_s1 = 0x4A;
            break;
        case 1:
            var_s1 = 0x4B;
            break;
        case 2:
            var_s1 = 0x4C;
            break;
        case 3:
            var_s1 = 0x4D;
            break;
        }
        func_802297B8((s32) temp_s2->unk28->unk40, var_s1, var_s0, var_s0);
        var_s0 += 1;
    } while (var_s0 != 0xC);
    sp38 = var_s1;
    temp_s0_2 = arg0 * 4;
    temp_s2->unkB0 = func_802311E8(temp_s2->unk28);
    D_802AC8A8[(temp_s0_2) / 4] = 1;
    D_802AC89C = 0;
    D_802AC8A0 = 0;
    func_802444B8(arg0, 0);
    D_802AC8E8[(temp_s0_2) / 4] = -1;
    D_802ACA78[(temp_s0_2) / 4] = 0.0f;
    temp_s2->unk10 = 0;
    temp_s2->unk68 &= 0x200;
    temp_s2->unk2C = 0;
    temp_s2->unk48 = 1;
    temp_s2->unk4C = 0;
    temp_s2->unk50 = 0;
    temp_s2->unk54 = 0;
    temp_s2->unk80 = 3;
    temp_s2->unk9C = 0;
    temp_s2->unkA4 = 0;
    temp_s2->unkA8 = 0;
    temp_s2->unkB4 = 0;
    temp_s2->unk38 = 0;
    temp_s2->unk18 &= ~0x404;
    temp_s2->unk74 = 0;
    temp_s2->unk40 = 0;
    temp_v0_3 = (arg0 * 0x10) + &D_802ACF08;
    M2C_FIELD(temp_v0_3, s16 *, 0xC) = 0;
    M2C_FIELD(temp_v0_3, s16 *, 0xE) = 0;
    M2C_FIELD(temp_v0_3, f32 *, 8) = 0.0f;
    M2C_FIELD(temp_v0_3, f32 *, 4) = 0.0f;
    M2C_FIELD(temp_v0_3, f32 *, 0) = 0.0f;
}

void func_80245868() {
    UnkObj *temp_a0;
    UnkObj *temp_a0_2;
    UnkStruct_800AEDF0 *var_s0;
    UnkStruct_800AEDF0 *var_s0_2;

    func_802362B8(0x7F);
    D_802AC9F4 = 0;
    var_s0 = D_800AEDF0;
    do {
        if (var_s0->unk24 != 0) {
            temp_a0 = var_s0->unk28;
            if ((temp_a0 != NULL) && (M2C_FIELD(temp_a0, s32 *, 0x44) != 0)) {
                func_80232AA8((s32) temp_a0);
            }
        }
        var_s0 += 1;
    } while ((u32) var_s0 < (u32) &D_800AEDF0[5]);
    var_s0_2 = D_800AEDF0;
    do {
        if (var_s0_2->unk24 != 0) {
            temp_a0_2 = var_s0_2->unk28;
            if (temp_a0_2 != NULL) {
                func_8022FC90(temp_a0_2);
                var_s0_2->unk28 = NULL;
                D_802AC894 = -1;
                var_s0_2->unkC = 0.0f;
            }
        }
        var_s0_2 += 1;
    } while (var_s0_2 != &D_800AEDF0[5]);
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
    s32 sp24;

    sp24 = func_80243DDC();
    func_802454F8(func_80243DDC(), (func_80243DDC() * 0xC) + &D_802ACEC8);
    func_80245430((sp24 * 0xC) + &D_802ACEC8, arg0, arg1, arg2, arg3);
}

s32 func_802456FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp1C;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a3;
    void *temp_a0;

    sp1C = func_80243DDC();
    func_802454F8(func_80243DDC(), (func_80243DDC() * 0xC) + &D_802ACEC8);
    temp_a0 = (sp1C * 0xC) + &D_802ACEC8;
    temp_v0 = M2C_FIELD(temp_a0, s32 *, 0);
    var_a3 = 0;
    var_a1 = 0;
    if (temp_v0 >= arg0) {
        temp_v1 = M2C_FIELD(temp_a0, s32 *, 8);
        if ((temp_v1 >= arg2) && (arg3 >= temp_v0) && (arg4 >= temp_v1)) {
            var_a1 = 1;
        }
    }
    if ((var_a1 != 0) && (arg1 == M2C_FIELD(temp_a0, s32 *, 4))) {
        var_a3 = 1;
    }
    return var_a3;
}

s32 func_80245690(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_a1;
    s32 temp_t0;
    s32 var_v0;
    s32 var_v1;

    temp_t0 = M2C_FIELD(arg0, s32 *, 0);
    var_v1 = 0;
    var_v0 = 0;
    if (temp_t0 >= arg1) {
        temp_a1 = M2C_FIELD(arg0, s32 *, 8);
        if ((temp_a1 >= arg3) && (arg4 >= temp_t0) && (arg5 >= temp_a1)) {
            var_v0 = 1;
        }
    }
    if ((var_v0 != 0) && (arg2 == M2C_FIELD(arg0, s32 *, 4))) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 func_802455A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp1C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a3;
    void *temp_a0;

    sp1C = func_80243DDC();
    func_802454F8(func_80243DDC(), (func_80243DDC() * 0xC) + &D_802ACEC8);
    temp_a0 = (sp1C * 0xC) + &D_802ACEC8;
    temp_v0 = M2C_FIELD(temp_a0, s32 *, 0);
    var_a3 = 0;
    var_a1 = 0;
    if (temp_v0 >= arg0) {
        temp_v1 = M2C_FIELD(temp_a0, s32 *, 8);
        if ((temp_v1 >= arg2) && (arg3 >= temp_v0) && (arg5 >= temp_v1)) {
            var_a1 = 1;
        }
    }
    if (var_a1 != 0) {
        temp_v0_2 = M2C_FIELD(temp_a0, s32 *, 4);
        if (temp_v0_2 >= arg1) {
            if (arg4 >= temp_v0_2) {
                var_a3 = 1;
            }
        }
    }
    return var_a3;
}

void func_8024557C(s32 *arg0) {
    func_802454F8(func_80243DDC(), arg0);
}

void func_802454F8(s32 arg0, s32 *arg1) {
    s32 out[3];
    UnkModel *m = ((UnkObj *) D_800AEDF0[arg0].unk28)->unk40;

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
    UnkStruct_800AEDF0 *p;
    void *obj;

    if (id != -1) {
        p = &D_800AEDF0[id];
        obj = p->unk28;
        func_80244354(id, 0x02010000, arg0);
        D_802AC918[id] = 0;
        func_802313DC(obj, 0x40000);
        if (arg0 == 1) {
            func_802313DC(obj, 0x40000);
            if (FLAG_CLEAR(p->unk10, 0x21C0) && p->unk14 > 0) {
                if (!FLAG_SET(p->unk10, 0x8000)) {
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
        obj = D_800AEDF0[arg0].unk28;
        func_80244354(arg0, 0x02010000, arg1);
        D_802AC918[arg0] = 0;
        func_802313DC(obj, 0x40000);
    }
}

s32 func_80245150(s32 arg0) {
    UnkStruct_800AEDF0 *p = &D_800AEDF0[D_802AC9E4];

    if (p->unk48 != 0) {
        if (func_8026E608(arg0, 0x11) == 1) {
            if (FLAG_SET(p->unk68, 0x80) && (arg0 & 0x60)) {
                return 1;
            }
            return 0;
        }
    }
    return 1;
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
    UnkStruct_800AEDF0 *p = &D_800AEDF0[arg0];
    s32 flag;
    UnkObj *obj;
    f32 vec[3];
    UnkObj *other;

    if (p->unk2C != 0) {
        obj = p->unk28;
        func_80270770(arg0, arg1);
        p->unk2C = 0;
        p->unk2C = 0;
        func_80270BA4(obj);
        flag = func_80244BA4(arg0, 0x400000);
        if (flag) {
            func_802444B8(arg0, 0x13);
        }
        func_80244354(arg0, 0xA040, 0);
        flag = func_80244BA4(arg0, 0x400000);
        if (!flag) {
            func_80244354(arg0, 0x20, 0);
        }
        flag = func_80243EB4(arg0, 0x2000);
        if (flag) {
            other = D_800AEDF0[p->unkA4].unk28;
            vec[2] = 70.0f;
            vec[1] = 60.0f;
            vec[0] = 180.0f;
            func_8022FEAC(vec, other->unk4C);
        }
        func_80244354(arg0, 0x100, 0);
    }
    flag = func_80244BA4(arg0, 0x80);
    if (flag) {
        func_802444B8(arg0, 0);
    }
    func_80244354(arg0, 0x80, 0);
}

void func_80244BE0(s32 arg0, s32 arg1) {
    func_80270770(arg0, arg1);
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
    s32 sp20;
    u32 sp1C;
    UnkObj *sp18;
    UnkModel *temp_v0;
    UnkObj *temp_a2;
    UnkStruct_800AEDF0 *temp_v1;
    s32 var_a1;
    s32 var_a3;
    void *temp_v0_10;
    void *temp_v0_11;
    void *temp_v0_12;
    void *temp_v0_13;
    void *temp_v0_14;
    void *temp_v0_15;
    void *temp_v0_16;
    void *temp_v0_17;
    void *temp_v0_18;
    void *temp_v0_19;
    void *temp_v0_20;
    void *temp_v0_21;
    void *temp_v0_22;
    void *temp_v0_23;
    void *temp_v0_24;
    void *temp_v0_25;
    void *temp_v0_26;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;

    temp_v1 = &D_800AEDF0[arg0];
    temp_a2 = temp_v1->unk28;
    temp_v1->unk44 = arg1;
    switch (arg1) {                                 /* switch 1 */
    case 0:                                         /* switch 1 */
        var_a1 = 0;
        var_a3 = -1;
        sp1C = 3;
        break;
    case 1:                                         /* switch 1 */
        var_a1 = 1;
        var_a3 = 2;
        sp1C = 5;
        break;
    case 2:                                         /* switch 1 */
        var_a1 = 3;
        var_a3 = 4;
        sp1C = 5;
        break;
    case 3:                                         /* switch 1 */
        var_a1 = 5;
        var_a3 = 6;
        sp1C = 5;
        break;
    case 4:                                         /* switch 1 */
        var_a1 = 7;
        var_a3 = -1;
block_27:
        sp1C = 0;
        break;
    case 5:                                         /* switch 1 */
        var_a1 = -1;
        var_a3 = -1;
        break;
    case 6:                                         /* switch 1 */
        var_a1 = 0xB;
        var_a3 = -1;
        goto block_27;
    case 7:                                         /* switch 1 */
        var_a1 = 0xA;
        var_a3 = -1;
        goto block_27;
    case 8:                                         /* switch 1 */
        var_a1 = 0x11;
        var_a3 = -1;
        sp1C = 3;
        break;
    case 10:                                        /* switch 1 */
        var_a1 = 0xC;
        var_a3 = -1;
        goto block_27;
    case 9:                                         /* switch 1 */
        var_a1 = 0xD;
        var_a3 = -1;
        goto block_27;
    case 11:                                        /* switch 1 */
        var_a1 = 0x10;
        var_a3 = -1;
        goto block_27;
    case 12:                                        /* switch 1 */
        var_a1 = 9;
        var_a3 = -1;
        sp1C = 4;
        break;
    case 13:                                        /* switch 1 */
        var_a1 = 8;
        var_a3 = 2;
        sp1C = 6;
        break;
    case 14:                                        /* switch 1 */
        var_a1 = 8;
        var_a3 = 4;
        sp1C = 6;
        break;
    case 15:                                        /* switch 1 */
        var_a1 = 8;
        var_a3 = 6;
        sp1C = 6;
        break;
    case 16:                                        /* switch 1 */
        var_a1 = 0xF;
        var_a3 = -1;
        goto block_27;
    case 18:                                        /* switch 1 */
        var_a1 = 8;
        var_a3 = -1;
        goto block_27;
    case 17:                                        /* switch 1 */
        var_a1 = 0xE;
        var_a3 = -1;
        goto block_27;
    case 19:                                        /* switch 1 */
        var_a1 = 0x12;
        var_a3 = -1;
        goto block_27;
    case 20:                                        /* switch 1 */
        var_a1 = 8;
        var_a3 = 0x15;
        sp1C = 2;
        break;
    case 21:                                        /* switch 1 */
        var_a1 = 0x16;
        var_a3 = -1;
        sp1C = 2;
        break;
    case 23:                                        /* switch 1 */
        var_a1 = 0x18;
        var_a3 = -1;
        goto block_27;
    case 24:                                        /* switch 1 */
        var_a1 = 0x19;
        var_a3 = -1;
        goto block_27;
    default:                                        /* switch 1 */
        var_a1 = -1;
        var_a3 = -1;
        goto block_27;
    }
    sp20 = var_a3;
    sp18 = temp_a2;
    func_80229E38(temp_a2->unk40, var_a1, 0);
    func_80229E38(temp_a2->unk40, sp20, 1);
    temp_v0 = temp_a2->unk40;
    M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) | 0x4000);
    switch (sp1C) {                                 /* switch 2 */
    case 0:                                         /* switch 2 */
        temp_v0_2 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_2, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 8) | 0x20);
        temp_v0_3 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_3, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_3, s32 *, 8) & ~0x40);
        temp_v0_4 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_4, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_4, s32 *, 0x14) & ~0x20);
        temp_v0_5 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_5, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_5, s32 *, 0x14) & ~0x40);
        return;
    case 2:                                         /* switch 2 */
        temp_v0_6 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_6, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_6, s32 *, 8) | 0x20);
        temp_v0_7 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_7, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_7, s32 *, 8) & ~0x40);
        temp_v0_8 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_8, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_8, s32 *, 0x14) & ~0x20);
        temp_v0_9 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_9, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_9, s32 *, 0x14) & ~0x40);
        return;
    case 3:                                         /* switch 2 */
        temp_v0_10 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_10, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_10, s32 *, 8) & ~0x20);
        temp_v0_11 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_11, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_11, s32 *, 8) & ~0x40);
        temp_v0_12 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_12, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_12, s32 *, 0x14) & ~0x20);
        temp_v0_13 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_13, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_13, s32 *, 0x14) & ~0x40);
        return;
    case 4:                                         /* switch 2 */
        temp_v0_14 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_14, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_14, s32 *, 8) | 0x20);
        temp_v0_15 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_15, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_15, s32 *, 8) | 0x40);
        temp_v0_16 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_16, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_16, s32 *, 0x14) | 0x20);
        temp_v0_17 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_17, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_17, s32 *, 0x14) | 0x40);
        return;
    case 5:                                         /* switch 2 */
        temp_v0_18 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_18, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_18, s32 *, 8) & ~0x20);
        temp_v0_19 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_19, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_19, s32 *, 8) & ~0x40);
        sp18 = temp_a2;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4), f32 *, 4) = func_8024441C(arg0, arg1);
        temp_v0_20 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_20, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_20, s32 *, 0x14) & ~0x20);
        temp_v0_21 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_21, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_21, s32 *, 0x14) & ~0x40);
        temp_v0_22 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_22, f32 *, 0x10) = (f32) M2C_FIELD(temp_v0_22, f32 *, 4);
        return;
    case 6:                                         /* switch 2 */
        temp_v0_23 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_23, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_23, s32 *, 8) | 0x20);
        temp_v0_24 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_24, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_24, s32 *, 8) | 0x40);
        temp_v0_25 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_25, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_25, s32 *, 0x14) & ~0x20);
        temp_v0_26 = M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4);
        M2C_FIELD(temp_v0_26, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_26, s32 *, 0x14) & ~0x40);
        sp18 = temp_a2;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_a2->unk40, void **, 0x48), void **, 4), f32 *, 0x10) = func_8024441C(arg0, arg1);
        /* fallthrough */
    default:                                        /* switch 2 */
        return;
    }
}

f32 func_8024441C(s32 arg0, s32 arg1) {
    f32 ret = 0.0f;
    UnkStruct_800AEDF0 *p;
    s32 v;

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
    UnkStruct_800AEDF0 *p = &D_800AEDF0[arg0];
    s32 v = p->unk10;

    if (arg2 == 1) {
        v |= arg1;
    } else {
        v &= arg1 ^ -1;
    }
    p->unk10 = v;
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
    s32 id;

    id = func_80243DDC();
    func_8027750C(id);
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
    UnkStruct_800AEDF0 *p = &D_800AEDF0[arg0];
    s32 v = p->unk68;

    if (arg2 == 1) {
        v |= arg1;
    } else {
        v &= arg1 ^ -1;
    }
    p->unk68 = v;
}

void *func_80243D7C(s32 arg0) {
    return D_802ACF08[arg0];
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
