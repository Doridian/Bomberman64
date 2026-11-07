/*
 * NON_MATCHING: ovl_13_02's game object, complete; not in the ROM.
 * flags: -O3
 * differing words: us 17, eu 17, jp 17
 * 77 of 80 functions match (fcmp folds each static into the function
 * before it; the text is the same in every version).
 * Still differs: 800458D8 swaps $v0 and $v1 between its flags and
 * the 0x40 test (the count reuses arg0, which the original has in $a0);
 * 80046E10 colours DE80/DE98/DEB0 into $s1-$s3 in the opposite order
 * of the first stores; 80048FBC only in its folded static 80049400
 * ($v0 for $v1 as the base of the DEC8 loads).
 * 80043040, 80043970, 80049400, 8004BBE4 and 8004BD28 are static and
 * come out in the original's order: 80043040 (its argument in $s0),
 * 80043970 and 80049400 each hold a dead call to their referrer
 * (80043098 for 80043040), and 8004BD28 a dead use of its own address
 * (so it is first in the reverse order the deferred address-taken
 * statics are flushed in). 8004521C, 800460C0 and 8004A8E0 are
 * global, as static they break that order or their temporaries. The
 * inlined stubs 8004B524, 8004B820/28/30 and the ten at
 * 8004BE60-8004BEA8 are empty statics.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define A180(v) (((v) >= 0.0f && (v) <= 180.0f) ? (v) : (360.0f - (v)) * -1.0f)
#define W360(v) (((v) >= 360.0f) ? (v) - 360.0f : ((v) < 0.0f) ? (v) + 360.0f : (v))

typedef struct {
    u32 w0;
    u32 w1;
} Gfx_ovl13_02;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Link_ovl13_02;

/* A camera move for ZeroJump 0x170B: a list of steps linked both ways. */
typedef struct Move_ovl13_02 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC[3];
    /* 0x18 */ f32 unk18[3];
    /* 0x24 */ f32 unk24[3];
    /* 0x30 */ f32 unk30[3];
    /* 0x3C */ struct Move_ovl13_02 *unk3C;
    /* 0x40 */ struct Move_ovl13_02 *unk40;
} Move_ovl13_02;

/* D_ovl13_02_8004DE80, DE98 and DEB0. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
} Sub18_ovl13_02;

void func_ovl13_02_8004BEB8(const char *); /* 0x100 */
void func_ovl13_02_8004C208(s32 *); /* 0xC02 */
void func_ovl13_02_8004C210(s32); /* 0xD00 */ /* also: void (s32, UnkStructA_40 **) x1 */
f32 func_ovl13_02_8004C220(void); /* 0xD02 */
void func_ovl13_02_8004C228(f32); /* 0xD03 */
void func_ovl13_02_8004C238(s32, s32, s32, s32, s32, s32); /* 0xD05 */
void func_ovl13_02_8004C250(f32, f32, f32, s32 *, s32); /* 0xD08 */
s32 func_ovl13_02_8004C260(s32); /* 0xD0A */
s32 func_ovl13_02_8004C268(s32, s32, s32); /* 0xD0B */
void func_ovl13_02_8004C2D8(void (*)(UnkStructA *), s32); /* 0xE02 */
void func_ovl13_02_8004C2E0(void (*)(UnkStructA *)); /* 0xE03 */ /* also: void (void (*)(Obj_0D01 *)) x1; void (void (*)(Obj_0D02 *)) x1; void (void (*)(Obj_0D03 *)) x1 */
void func_ovl13_02_8004C318(void); /* 0xF05 */
void func_ovl13_02_8004C330(void (*)(UnkStructA *)); /* 0xF08 */
s32 *func_ovl13_02_8004C348(void); /* 0xF0B */ /* also: s32 * (void) x3; Save_ovl0B_02 *(void) x1; UnkStruct_ovl0B_01_80044C58 *(void) x1 */
void func_ovl13_02_8004C360(s32); /* 0xF0E */
void func_ovl13_02_8004C370(s32); /* 0xF10 */
void func_ovl13_02_8004C3A8(void); /* 0x1000 */
void func_ovl13_02_8004C3B8(void *); /* 0x1002 */
s32 func_ovl13_02_8004C3D8(void); /* 0x1006 */
void func_ovl13_02_8004C3E0(s32, void *); /* 0x1007 */
void func_ovl13_02_8004C3E8(s32); /* 0x1008 */
void func_ovl13_02_8004C400(const char *); /* 0x100B */
UnkStructA * func_ovl13_02_8004C438(s32); /* 0x1012 */ /* also: Obj02 * (s32) x1; Obj03 * (s32) x1; UnkStruct_ovl0A_05_80048CA0 *(s32) x1 */
void func_ovl13_02_8004C498(s32); /* 0x101E */
void func_ovl13_02_8004C900(UnkStructA_40 *, s32); /* 0x1505 */ /* also: void (Obj *, s32) x1; void (Inner *, s32) x1; void (UnkStruct_ovl0A_02_80047A20_Inner *, s32) x1 */
void func_ovl13_02_8004C908(UnkStructA_40 *, s32, s32, s32); /* 0x1506 */ /* also: void (Obj *, s32, s32, s32) x1; void (Inner *, s32, s32, s32) x1; void (UnkStruct_ovl0A_02_80047A20_Inner *, s32, s32, s32) x1 */
void func_ovl13_02_8004C920(UnkStructA_40 *, s32, s32); /* 0x1509 */ /* also: void (Obj *, s32, s32) x1; void (Inner *, s32, s32) x1; void (UnkStruct_ovl0A_02_80047A20_Inner *, s32, s32) x1 */
f32 func_ovl13_02_8004C938(UnkStructA_40 *, s32); /* 0x150C */ /* also: f32 (Inner *, s32) x1; f32 (UnkStruct_ovl0A_02_80047A20_Inner *, s32) x1; f32 (UnkStruct_ovl0A_03_80047E20_Inner *, s32) x1 */
s32 func_ovl13_02_8004C940(UnkStructA_40 *, s32, s32, s32, s32, s32); /* 0x150D */ /* also: s32 (Obj40_0D01 *, s32, s32, s32, s32, s32) x1; s32 (Obj40_0D04 *, s32, s32, s32, s32, s32) x1; s32 (Obj40_0D06 *, s32, s32, s32, s32, s32) x1 */
void func_ovl13_02_8004C950(UnkStructA_40 *, s32, s32); /* 0x150F */ /* also: void (UnkStruct_ovl0A_03_80047E20_Inner *, s32, s32) x1 */
void func_ovl13_02_8004CA18(s32); /* 0x1700 */
void func_ovl13_02_8004CA28(s32); /* 0x1702 */
void func_ovl13_02_8004CA38(f32, f32, f32); /* 0x1704 */
void func_ovl13_02_8004CA48(f32, f32, f32); /* 0x1706 */
void func_ovl13_02_8004CA58(f32, f32, f32); /* 0x1708 */
void func_ovl13_02_8004CA60(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl13_02_8004CA70(Move_ovl13_02 *, s32, s32); /* 0x170B */ /* also: void (u32 *, s32, s32) x1; void (Move_0D01 *, s32, s32) x1; void (Cam_0D03 *, s32, s32) x1 */
void func_ovl13_02_8004CA90(void); /* 0x170F */
void func_ovl13_02_8004CA98(s32); /* 0x1710 */
void func_ovl13_02_8004CAA0(s32); /* 0x1711 */
void func_ovl13_02_8004CAC0(f32); /* 0x1715 */
void func_ovl13_02_8004CAD0(f32); /* 0x1717 */
void func_ovl13_02_8004CAD8(f32 *); /* 0x1718 */
void func_ovl13_02_8004CAE8(f32, f32, f32, f32); /* 0x171A */
void func_ovl13_02_8004CB00(void *); /* 0x171D */ /* also: void (UnkStruct_ovl0A_05_80048CA0 *) x1 */
void func_ovl13_02_8004CB10(s32); /* 0x171F */
void func_ovl13_02_8004CB20(f32, f32, f32); /* 0x1721 */
void func_ovl13_02_8004CB28(void *); /* 0x1722 */ /* also: void (f32 *) x1 */
void func_ovl13_02_8004CB38(); /* 0x1724 */ /* unknown */
void func_ovl13_02_8004CB88(f32 *, f32 *, f32 *); /* 0x1803 */
void func_ovl13_02_8004CB90(f32 *, f32 *); /* 0x1804 */
f32 func_ovl13_02_8004CBA0(f32 *, f32 *); /* 0x1806 */ /* also: f32 (Vec3f *, Vec3f *) x1 */
s32 func_ovl13_02_8004CBA8(UnkStructA *, s32); /* 0x1807 */ /* also: s32 (Obj_0D01 *, s32) x1; s32 (Obj_0D02 *, s32) x1; s32 (Obj_0D03 *, s32) x1 */
void func_ovl13_02_8004CBC8(UnkStructA *, s32); /* 0x180B */ /* also: void (Obj_0D02 *, s32) x1; void (Obj_0D03 *, s32) x1; void (Obj05 *, s32) x1 */
void func_ovl13_02_8004CBE0(UnkStructA *, UnkStructA *, Link_ovl13_02 *, s32); /* 0x180E */
void func_ovl13_02_8004CBF8(UnkStructA *, s32); /* 0x1811 */ /* also: void (Obj *, s32) x1; void (Obj02 *, s32) x1; void (Obj03 *, s32) x1 */
void func_ovl13_02_8004CC00(UnkStructA *, s32); /* 0x1812 */ /* also: void (Obj *, s32) x1; void (Obj02 *, s32) x1; void (Obj03 *, s32) x1 */
void func_ovl13_02_8004CC10(UnkStructA *); /* 0x1814 */ /* also: void (Obj *) x1; void (Obj02 *) x1; void (Obj03 *) x1 */
UnkStructA *func_ovl13_02_8004CC20(s32, s32, s32, UnkStructA *); /* 0x1816 */ /* also: UnkStructA * (s32, s32, s32, UnkStructA *) x1; Obj * (s32, s32, s32, Obj *) x1; Obj02 * (s32, s32, s32, Obj02 *) x1 */
UnkStructA *func_ovl13_02_8004CC30(UnkStructA *); /* 0x1818 */ /* also: void (Obj02 *) x1; void (Obj03 *) x1; UnkStructA * (UnkStructA *) x1 */
void func_ovl13_02_8004CC78(UnkStructA *); /* 0x1821 */ /* also: void (Obj02 *) x1; void (Obj_0D02 *) x1; void (Obj_0D03 *) x1 */
UnkStructA *func_ovl13_02_8004CC80(UnkStructA *, s32); /* 0x1822 */
void func_ovl13_02_8004CCC8(UnkStructA *, f32 *); /* 0x182B */ /* also: void (Obj02 *, f32 *) x1; void (Obj03 *, f32 *) x1; void (UnkStruct_ovl0A_05_80048CA0 *, f32 *) x1 */
void func_ovl13_02_8004CD28(s32 *); /* 0x1837 */
void func_ovl13_02_8004CD30(void); /* 0x1838 */
void func_ovl13_02_8004CD38(void); /* 0x1839 */
s32 func_ovl13_02_8004CD48(void (*)(), void *, s32, s32, s32); /* 0x1900 */ /* also: void (void (*)(void), void *, s32, s32, s32) x6; s32 (void (*)(void), void *, s32, s32, s32) x4; s32 (void (*)(), void *, void *, s32, s32) x1 */
void func_ovl13_02_8004CD58(void); /* 0x1902 */
void func_ovl13_02_8004CD68(s32); /* 0x1904 */
void *func_ovl13_02_8004CD70(void); /* 0x1905 */ /* also: Obj * (void) x1; Obj02 * (void) x1; Obj03 * (void) x1 */
s32 func_ovl13_02_8004CD90(void); /* 0x1909 */ /* also: void (void) x8 */
f32 func_ovl13_02_8004CEF0(f32); /* 0x1D00 */
f32 func_ovl13_02_8004CEF8(f32); /* 0x1D01 */
f64 func_ovl13_02_8004CF00(void); /* 0x1D02 */
s32 func_ovl13_02_8004CF08(s32); /* 0x1D03 */
void func_ovl13_02_8004CF10(f32, f32); /* 0x1D04 */
void func_ovl13_02_8004CF60(void); /* 0x1D0E */
void func_ovl13_02_8004CF68(void); /* 0x1D0F */
void func_ovl13_02_8004CF70(void); /* 0x1D10 */
void func_ovl13_02_8004CF78(f32 *); /* 0x1D11 */
void func_ovl13_02_8004CF80(void); /* 0x1D12 */
s32 func_ovl13_02_8004CFB0(s32); /* 0x1E04 */
void func_ovl13_02_8004CFC0(s32); /* 0x1E06 */
void func_ovl13_02_8004CFC8(s32); /* 0x1E07 */
s32 func_ovl13_02_8004CFD0(s32); /* 0x1E08 */
void func_ovl13_02_8004D078(u8, u8, u8); /* 0x2102 */
void func_ovl13_02_8004D088(s32, s32, s32, s32, s32); /* 0x2104 */
void func_ovl13_02_8004D098(s32, s32, s32); /* 0x2201 */
void func_ovl13_02_8004D0A0(s32); /* 0x2202 */
void func_ovl13_02_8004D0A8(s32); /* 0x2203 */
void func_ovl13_02_8004D1A0(s32, f32 *, s32); /* 0x2601 */ /* also: s32 (s32, f32 *, s32) x3; void (s32, f32 *, Obj_0D02 *) x1; void (s32, f32 *, Obj_0D03 *) x1 */
void func_ovl13_02_8004D1C0(void *); /* 0x2701 */
s32 func_ovl13_02_8004D2D0(s32); /* 0x2B00 */ /* also: s32 (s32) x5 */
void func_ovl13_02_8004D2E0(s32); /* 0x2B02 */
void func_ovl13_02_8004D2E8(void); /* 0x2B03 */
void func_ovl13_02_8004D2F0(s32, f32, f32, f32); /* 0x2B04 */ /* also: void (s32, s32, s32, s32) x7 */
void func_ovl13_02_8004D300(s32); /* 0x2B06 */
void func_ovl13_02_8004D448(void); /* 0x3000 */
void func_ovl13_02_8004D450(void); /* 0x3001 */

/* .bss */
Vec3f D_ovl13_02_8004DC90;
u8 D_ovl13_02_8004DC9C[4];
s32 D_ovl13_02_8004DCA0[3];
s32 D_ovl13_02_8004DCAC;
u8 D_ovl13_02_8004DCB0[0x4];
s32 D_ovl13_02_8004DCB4;
s32 D_ovl13_02_8004DCB8;
u8 D_ovl13_02_8004DCBC[0x4];
s32 D_ovl13_02_8004DCC0[4];
s32 D_ovl13_02_8004DCD0;
u8 D_ovl13_02_8004DCD4[0x4];
s32 D_ovl13_02_8004DCD8;
s32 * D_ovl13_02_8004DCDC;
f32 D_ovl13_02_8004DCE0;
u8 D_ovl13_02_8004DCE4[0x8];
f32 D_ovl13_02_8004DCEC;
f32 D_ovl13_02_8004DCF0;
UnkStructA * D_ovl13_02_8004DCF4;
s32 D_ovl13_02_8004DCF8;
UnkStructA * D_ovl13_02_8004DCFC;
UnkStructA * D_ovl13_02_8004DD00;
u8 D_ovl13_02_8004DD04[0x4];
f32 D_ovl13_02_8004DD08;
u8 D_ovl13_02_8004DD0C[0x4];
f32 D_ovl13_02_8004DD10;
f32 D_ovl13_02_8004DD14;
u8 D_ovl13_02_8004DD18[0x8];
s32 D_ovl13_02_8004DD20[4];
s32 D_ovl13_02_8004DD30[3];
f32 D_ovl13_02_8004DD3C;
s32 D_ovl13_02_8004DD40[2];
s32 D_ovl13_02_8004DD48[4];
s32 D_ovl13_02_8004DD58[4];
UnkStructA *D_ovl13_02_8004DD68[10];
s32 D_ovl13_02_8004DD90[10];
Vec3f D_ovl13_02_8004DDB8[9];
s32 D_ovl13_02_8004DE24;
s32 D_ovl13_02_8004DE28;
s32 D_ovl13_02_8004DE2C;
s32 D_ovl13_02_8004DE30;
s32 D_ovl13_02_8004DE34;
s32 D_ovl13_02_8004DE38;
UnkStructA * D_ovl13_02_8004DE3C;
UnkStructA * D_ovl13_02_8004DE40;
UnkStructA * D_ovl13_02_8004DE44;
UnkStructA * D_ovl13_02_8004DE48;
UnkStructA * D_ovl13_02_8004DE4C;
UnkStructA *D_ovl13_02_8004DE50[8];
UnkStructA * D_ovl13_02_8004DE70;
f32 D_ovl13_02_8004DE74;
f32 D_ovl13_02_8004DE78;
u8 D_ovl13_02_8004DE7C[0x4];
Sub18_ovl13_02 D_ovl13_02_8004DE80;
Sub18_ovl13_02 D_ovl13_02_8004DE98;
Sub18_ovl13_02 D_ovl13_02_8004DEB0;
f32 D_ovl13_02_8004DEC8;
f32 D_ovl13_02_8004DECC;
u8 D_ovl13_02_8004DED0[0x8];
f32 D_ovl13_02_8004DED8;
f32 D_ovl13_02_8004DEDC;
u8 D_ovl13_02_8004DEE0[0x4];
f32 D_ovl13_02_8004DEE4;
f32 D_ovl13_02_8004DEE8;
f32 D_ovl13_02_8004DEEC;
f32 D_ovl13_02_8004DEF0;
f32 D_ovl13_02_8004DEF4;
f32 D_ovl13_02_8004DEF8;
f32 D_ovl13_02_8004DEFC;
f32 D_ovl13_02_8004DF00;
f32 D_ovl13_02_8004DF04;
f32 D_ovl13_02_8004DF08;
f32 D_ovl13_02_8004DF0C;
f32 D_ovl13_02_8004DF10;
u8 D_ovl13_02_8004DF14[0x4];
s32 D_ovl13_02_8004DF18[18];
s32 D_ovl13_02_8004DF60[4];
s32 D_ovl13_02_8004DF70[4];
s32 D_ovl13_02_8004DF80[4];
s32 D_ovl13_02_8004DF90[4];
s32 D_ovl13_02_8004DFA0[3];
UnkStructA * D_ovl13_02_8004DFAC;
s32 D_ovl13_02_8004DFB0[3];
f32 D_ovl13_02_8004DFBC;
s32 D_ovl13_02_8004DFC0[4];
s32 D_ovl13_02_8004DFD0[4];
Move_ovl13_02 D_ovl13_02_8004DFE0;

void func_ovl13_02_80043010(void);
static void func_ovl13_02_80043040(UnkStructA *arg0);
void func_ovl13_02_80043098(s32 arg0, UnkStructA *arg1);
void func_ovl13_02_800430CC(f32 *arg0, s32 arg1, s32 arg2);
void func_ovl13_02_800434C0(f32 *arg0);
void func_ovl13_02_800435D4(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl13_02_8004362C(s32 arg0);
void func_ovl13_02_80043698(void);
static void func_ovl13_02_80043970(void);
void func_ovl13_02_800439DC(void);
void func_ovl13_02_80043B64(f32 *arg0, f32 *arg1, f32 arg2, f32 *arg3);
void func_ovl13_02_80043E64(void);
void func_ovl13_02_800444F0(void);
s32 func_ovl13_02_800445C8(void);
void func_ovl13_02_80044630(void);
void func_ovl13_02_800446B0(void);
void func_ovl13_02_800448E4(void);
void func_ovl13_02_80044990(s32 arg0);
void func_ovl13_02_80044AB4(void);
s32 func_ovl13_02_80044CC8(void);
void func_ovl13_02_80044E64(f32 *arg0, f32 *arg1, f32 *arg2);
void func_ovl13_02_80044F0C(f32 *arg0, s32 arg1, f32 arg2);
void func_ovl13_02_8004511C(void);
void func_ovl13_02_8004521C(void);
void func_ovl13_02_80045460(void);
void func_ovl13_02_8004564C(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_ovl13_02_80045724(void);
void func_ovl13_02_80045888(void);
s32 func_ovl13_02_800458D8(UnkStructA *arg0);
void func_ovl13_02_8004591C(void);
void func_ovl13_02_800459D0(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
void func_ovl13_02_80045AB8(void);
void func_ovl13_02_800460C0(void);
s32 func_ovl13_02_800461E0(void);
void func_ovl13_02_80046268(void);
void func_ovl13_02_8004631C(void);
void func_ovl13_02_8004636C(void);
void func_ovl13_02_800463BC(void);
void func_ovl13_02_8004640C(void);
void func_ovl13_02_800467D8(s32 arg0);
void func_ovl13_02_80046B34(s32 arg0);
void func_ovl13_02_80046D7C(s32 arg0, f32 arg1);
void func_ovl13_02_80046E10(s32 arg0);
void func_ovl13_02_8004799C(void);
void func_ovl13_02_80047C60(s32 arg0);
void func_ovl13_02_80047EEC(void);
void func_ovl13_02_800480EC(s32 arg0);
void func_ovl13_02_800484B4();
void func_ovl13_02_80048504(void);
void func_ovl13_02_800489C0(s32 arg0);
void func_ovl13_02_80048FBC(s32 arg0);
static void func_ovl13_02_80049400(void);
void func_ovl13_02_80049468(s32 *arg0, s32 *arg1);
void func_ovl13_02_80049504(s32 *arg0, s32 *arg1);
void func_ovl13_02_80049564(s32 *arg0, s32 *arg1);
void func_ovl13_02_800495FC(s32 *arg0, s32 *arg1);
void func_ovl13_02_80049650(s32 *arg0, s32 *arg1);
void func_ovl13_02_800496A0(s32 *arg0, s32 *arg1);
void func_ovl13_02_8004980C(void);
void func_ovl13_02_800499A0(void);
void func_ovl13_02_80049D50(void);
void func_ovl13_02_80049F1C(UnkStructA *arg0);
void func_ovl13_02_80049F68(void);
s32 func_ovl13_02_8004A844(void);
void func_ovl13_02_8004A8E0(void);
void func_ovl13_02_8004AB3C(void);
void func_ovl13_02_8004ACF8(void);
void func_ovl13_02_8004AF1C(void);
void func_ovl13_02_8004B108(void);
void func_ovl13_02_8004B1BC(void);
void func_ovl13_02_8004B298(UnkStructA *arg0);
void func_ovl13_02_8004B360(UnkStructA *arg0);
void func_ovl13_02_8004B3B4(void);
void func_ovl13_02_8004B3F0(void);
static void func_ovl13_02_8004B524(void);
void func_ovl13_02_8004B52C(void);
void func_ovl13_02_8004B57C(void);
void func_ovl13_02_8004B644(void);
void func_ovl13_02_8004B690(void);
void func_ovl13_02_8004B838(void);
void func_ovl13_02_8004BAFC(s32 arg0);
static void func_ovl13_02_8004BBE4(void);
static void func_ovl13_02_8004BD28(void);
void func_ovl13_02_8004BDA4(f32 arg0);
void func_ovl13_02_8004BDEC(f32 arg0, f32 arg1, f32 arg2);
void func_ovl13_02_8004BE48(void);

/* .data */
u8 D_ovl13_02_8004D4F0[8] = { 0 };
Move_ovl13_02 D_ovl13_02_8004D4F8[4] = {
    { 0xF0, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D4F8[1] },
    { 0, 2, 0, { 32768.0f, 32768.0f, 32768.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D4F8[0], NULL },
    { 0xF0, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D4F8[3] },
    { 0, 2, 0, { 32768.0f, 32768.0f, 32768.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D4F8[2], NULL }
};
Move_ovl13_02 D_ovl13_02_8004D608[10] = {
    { 0xC0, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D608[1] },
    { 0x30, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D608[0], &D_ovl13_02_8004D608[2] },
    { 0, 2, 0, { 32768.0f, 32768.0f, 32768.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D608[1], NULL },
    { 0x30, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D608[4] },
    { 0x12C, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D608[3], &D_ovl13_02_8004D608[5] },
    { 0xC0, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D608[4], &D_ovl13_02_8004D608[6] },
    { 0, 2, 0, { 32768.0f, 32768.0f, 32768.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D608[5], NULL },
    { 0x1E, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 33.333332f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D608[8] },
    { 0x3C, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D608[7], &D_ovl13_02_8004D608[9] },
    { 0x1E, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, -33.333332f, -0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D608[8], NULL }
};
Move_ovl13_02 D_ovl13_02_8004D8B0 = { 0x1E, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, NULL };
Move_ovl13_02 D_ovl13_02_8004D8F4 = { 0x1E, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, NULL };
f32 D_ovl13_02_8004D938[6] = { -200.0f, -100.0f, -0.0f, 200.0f, 100.0f, 0.0f };

/* unused: the stubs IDO -O3 leaves after the tail */
static void func_ovl13_02_8004BE60(void) {
}

static void func_ovl13_02_8004BE68(void) {
}

static void func_ovl13_02_8004BE70(void) {
}

static void func_ovl13_02_8004BE78(void) {
}

static void func_ovl13_02_8004BE80(void) {
}

static void func_ovl13_02_8004BE88(void) {
}

static void func_ovl13_02_8004BE90(void) {
}

static void func_ovl13_02_8004BE98(void) {
}

static void func_ovl13_02_8004BEA0(void) {
}

static void func_ovl13_02_8004BEA8(void) {
}

void func_ovl13_02_8004BE48(void) {
    D_ovl13_02_8004DCB4 = -1;
    D_ovl13_02_8004DCB8 = -1;
}

void func_ovl13_02_8004BDEC(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl13_02_8004CA38(M2C_FIELD(&D_ovl13_02_8004DCC0, f32 *, 0), M2C_FIELD(&D_ovl13_02_8004DCC0, f32 *, 4), M2C_FIELD(&D_ovl13_02_8004DCC0, f32 *, 8));
    func_ovl13_02_8004CA58(arg0, arg1, arg2);
    func_ovl13_02_8004CD68(0xB4);
}

void func_ovl13_02_8004BDA4(f32 arg0) {
    f32 sp1C;

    func_ovl13_02_8004CA60(&sp1C, NULL, NULL);
    func_ovl13_02_8004CA58(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl13_02_80048FBC(s32 arg0) {
    s32 pad[8];
    f32 *p;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 k;
    s32 i;

    func_ovl13_02_8004CFC0(0x41D);
    func_ovl13_02_8004362C(0);
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    D_ovl13_02_8004DE80.unk8 = 0.8f;
    D_ovl13_02_8004DE98.unk8 = 0.8f;
    D_ovl13_02_8004DEB0.unk8 = 0.8f;
    D_ovl13_02_8004DE80.unkC = 0.11f;
    D_ovl13_02_8004DE98.unkC = 0.11f;
    D_ovl13_02_8004DEB0.unkC = 0.11f;
    D_ovl13_02_8004DE80.unk10 = 0.999f;
    D_ovl13_02_8004DE98.unk10 = 0.999f;
    D_ovl13_02_8004DEB0.unk10 = 0.999f;
    D_ovl13_02_8004DEF8 = 1.0f;
    D_ovl13_02_8004DEFC = 0.0f;
    D_ovl13_02_8004DF00 = 50.0f;
    D_ovl13_02_8004DF04 = 2.0f;
    D_ovl13_02_8004DF08 = 10.0f;
    D_ovl13_02_8004DF0C = 1.0f;
    D_ovl13_02_8004DF10 = 12.0f;
    k = 0;
    for (i = 0; i < arg0; i++) {
        D_ovl13_02_8004DEF4 = 0.0f;
        D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 = 0.0f;
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
        p = (f32 *) ((Vec3f *) D_ovl13_02_8004DF18 + k);
        dx = (p[0] - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0)) / D_ovl13_02_8004DEF0;
        dy = (p[1] - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4)) / D_ovl13_02_8004DEF0;
        dz = (p[2] - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8)) / D_ovl13_02_8004DEF0;
        if (func_ovl13_02_8004CBA0(&D_ovl13_02_8004DEC8, p) > 300.0f) {
            if (func_ovl13_02_8004CF08(1) != 0) {
                func_ovl13_02_8004CD48(func_ovl13_02_80049400, (void *)0xF1, 0, 0, 0x150);
            } else {
                func_ovl13_02_8004CD48(func_ovl13_02_80049400, (void *)0xF2, 0, 0, 0x150);
            }
        } else if (func_ovl13_02_8004CF08(1) != 0) {
            func_ovl13_02_8004CD48(func_ovl13_02_80049400, (void *)0xED, 0, 0, 0x150);
        } else {
            func_ovl13_02_8004CD48(func_ovl13_02_80049400, (void *)0xEE, 0, 0, 0x150);
        }
        while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40) && (D_ovl13_02_8004DE30 == 0)) {
            M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0) += dx;
            M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) += dy;
            M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) += dz;
            if (D_ovl13_02_8004DE34 != 0) {
                func_ovl13_02_8004CFC8(0x41E);
                func_ovl13_02_80046B34(D_ovl13_02_8004DE34);
                func_ovl13_02_8004CFC0(0x41E);
                i = arg0;
                D_ovl13_02_8004DE80.unk0 = 2;
                D_ovl13_02_8004DE98.unk0 = 2;
                D_ovl13_02_8004DEB0.unk0 = 2;
                D_ovl13_02_8004DE80.unk8 = 0.8f;
                D_ovl13_02_8004DE80.unkC = 0.11f;
                D_ovl13_02_8004DE80.unk10 = 0.999f;
                D_ovl13_02_8004DE98.unk8 = 0.8f;
                D_ovl13_02_8004DE98.unkC = 0.11f;
                D_ovl13_02_8004DE98.unk10 = 0.999f;
                D_ovl13_02_8004DEB0.unk8 = 0.8f;
                D_ovl13_02_8004DEB0.unkC = 0.11f;
                D_ovl13_02_8004DEB0.unk10 = 0.999f;
                D_ovl13_02_8004DE34 = 0;
                break;
            }
            func_ovl13_02_8004CD90();
        }
        k = func_ovl13_02_8004CF08(5);
    }
    func_ovl13_02_8004CFC8(0x41D);
}

static void func_ovl13_02_8004BD28(void) {
    void *sp1C;

    if (0) { func_ovl13_02_8004CD48(func_ovl13_02_8004BD28, (void *)0x28, 0, 0, 0x150); }
    sp1C = func_ovl13_02_8004CD70();
    if (func_ovl13_02_8004CFD0(0x424) == 0) {
        do {
            func_ovl13_02_8004CD90();
        } while (func_ovl13_02_8004CFD0(0x424) == 0);
    }
    if (!(*D_ovl13_02_8004DCDC & 2)) {
        func_ovl13_02_8004D2E0((s32) sp1C);
    }
    func_ovl13_02_8004CD58();
}

static void func_ovl13_02_8004BBE4(void) {
    s32 var_s0;

    func_ovl13_02_8004C3E8(1);
    if (func_ovl13_02_8004CFD0(0x424) == 0) {
        do {
            func_ovl13_02_8004CD90();
        } while (func_ovl13_02_8004CFD0(0x424) == 0);
    }
    func_ovl13_02_8004C3E8(1);
    func_ovl13_02_8004C360(0);
    func_ovl13_02_8004C498(1);
    if (func_ovl13_02_8004CFB0(0xA4) != 0) {
        func_ovl13_02_8004C400("WM1 WAP WG1 M1 ST1 M6 ST10 WSH WDN WB2 ST1 M2 ST8 M4 ST1");
        func_ovl13_02_8004CD68(0xB4);
        func_ovl13_02_8004C400("WM1 WAP WG1 M1 ST1 M4 ST10 WSH WDSW WB4 ST1");
        func_ovl13_02_8004C400("WM1 WAP WG1 M1 ST1 M4 ST10 WSH WDNE WB4 ST1 WDN WB0 ST30 M2 ST60 MB");
        func_ovl13_02_8004CD68(0x78);
    } else {
        func_ovl13_02_8004C400("WM1 WAP WG1 M1 ST1 M6 ST10 WSH WDN WB2 ST1 M2 ST8 M4 ST1");
        func_ovl13_02_8004CD68(0x1E);
        var_s0 = 0;
        do {
            func_ovl13_02_8004C400("WM1 WAP WG1 WDE WB0 ST20 WDW WB0 ST20");
            var_s0 += 1;
        } while (var_s0 != 2);
        func_ovl13_02_8004C400("WM1 WAP WG1 WDN WB0 ST20 M8 ST30");
        func_ovl13_02_8004CD68(0xAA);
        func_ovl13_02_8004C400("WM1 WAP WG1 WDS WB0 ST1");
        func_ovl13_02_8004CD68(0x3C);
        func_ovl13_02_8004C498(0);
        func_ovl13_02_8004CD90();
        func_ovl13_02_8004C400("WM1 WAP WG1 WSH WDW WB4 ST1 WSH WDE WB6 ST1");
        func_ovl13_02_8004CD68(0x3C);
    }
    func_ovl13_02_8004D448();
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_8004BAFC(s32 arg0) {
    switch (arg0) {
    case 2:
        func_ovl13_02_8004B838();
        return;
    case 4:
        func_ovl13_02_8004B690();
        return;
    case 5:
        func_ovl13_02_8004B57C();
        return;
    case 3:
        func_ovl13_02_8004CFC0(0x424);
        func_ovl13_02_8004B524();
        return;
    case 11:
        func_ovl13_02_8004CF70();
        func_ovl13_02_8004CFC0(0x401);
        return;
    case 1:
        if (func_ovl13_02_8004CFD0(0x401) == 0) {
            func_ovl13_02_8004CF70();
        }
        func_ovl13_02_8004B3F0();
        /* fallthrough */
    case 17:
    default:
        return;
    }
}

static void func_ovl13_02_8004B820(void) {
}

static void func_ovl13_02_8004B828(void) {
}

static void func_ovl13_02_8004B830(void) {
}

void func_ovl13_02_8004B838(void) {
    func_ovl13_02_8004B820();
    func_ovl13_02_8004B828();
    func_ovl13_02_8004B830();
    func_ovl13_02_8004B1BC();
    func_ovl13_02_8004C210(0x176);
    func_ovl13_02_8004C3A8();
    func_ovl13_02_8004C438(func_ovl13_02_8004C3D8())->unk40->unk20 = 180.0f;
    D_ovl13_02_8004DD08 = (f32) func_ovl13_02_8004C260(0) * 100.0f;
    func_ovl13_02_8004D098(0, 0x80, 0xFF);
    func_ovl13_02_8004D098(0, 0, 0);
    func_ovl13_02_8004D088(0x3DF, 0x3E4, 0, 0, 0);
    func_ovl13_02_8004C208(&D_ovl13_02_8004DCD0);
    M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0) = ((f32) ((s32) D_ovl13_02_8004DCD0 / 2) * 100.0f) - 50.0f;
    M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4) = (f32) ((f32) func_ovl13_02_8004C260(0) * 100.0f);
    M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) = (f32) (((f32) ((s32) D_ovl13_02_8004DCD8 / 2) * 100.0f) - 50.0f);
    D_ovl13_02_8004DCF4 = func_ovl13_02_8004CC20(-1, 0, 0xD0, NULL);
    D_ovl13_02_8004DCF4->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    D_ovl13_02_8004DCF4->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    D_ovl13_02_8004DCF4->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8);
    func_ovl13_02_8004C228(D_ovl13_02_8004DD08 + -50.0f);
    func_ovl13_02_8004C2E0(func_ovl13_02_800484B4);
    D_ovl13_02_8004DCEC = -45.0f;
    D_ovl13_02_8004DCF0 = 30.0f;
    func_ovl13_02_8004CF10(D_ovl13_02_8004DCEC, D_ovl13_02_8004DCF0);
    M2C_FIELD(&D_ovl13_02_8004DD48, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4) + 300.0f);
    M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4) + 1200.0f);
    M2C_FIELD(&D_ovl13_02_8004DD48, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DD48, f32 *, 8) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8);
    M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + 1500.0f);
    func_ovl13_02_8004B108();
    D_ovl13_02_8004DCAC = func_ovl13_02_8004C3D8();
    func_ovl13_02_8004AB3C();
    func_ovl13_02_8004CD30();
    func_ovl13_02_8004CF68();
    func_ovl13_02_80049F68();
    func_ovl13_02_8004AF1C();
    func_ovl13_02_800448E4();
    func_ovl13_02_8004C2D8(func_ovl13_02_8004B360, 5);
    func_ovl13_02_8004C330(func_ovl13_02_8004B298);
}

void func_ovl13_02_8004B690(void) {
    D_ovl13_02_8004DCF8 = func_ovl13_02_8004D2D0(0xE4);
    func_ovl13_02_8004CB28(&D_ovl13_02_8004DD48);
    func_ovl13_02_8004CB38(&D_ovl13_02_8004DD58);
    func_ovl13_02_8004362C(0);
    D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 = 0.0f;
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    D_ovl13_02_8004DEF8 = 1.0f;
    D_ovl13_02_8004DEFC = 0.0f;
    D_ovl13_02_8004DF00 = 50.0f;
    D_ovl13_02_8004DF04 = 2.0f;
    D_ovl13_02_8004DF08 = 10.0f;
    D_ovl13_02_8004DF0C = 1.0f;
    D_ovl13_02_8004DF10 = 12.0f;
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    D_ovl13_02_8004DE80.unk8 = 0.8f;
    D_ovl13_02_8004DE98.unk8 = 0.8f;
    D_ovl13_02_8004DEB0.unk8 = 0.8f;
    D_ovl13_02_8004DE80.unkC = 0.11f;
    D_ovl13_02_8004DE98.unkC = 0.11f;
    D_ovl13_02_8004DEB0.unkC = 0.11f;
    D_ovl13_02_8004DE80.unk10 = 0.999f;
    D_ovl13_02_8004DE98.unk10 = 0.999f;
    D_ovl13_02_8004DEB0.unk10 = 0.999f;
    D_ovl13_02_8004DEF4 = 0.0f;
    func_ovl13_02_800439DC();
    if (*D_ovl13_02_8004DCDC & 2) {
        func_ovl13_02_8004CD48(func_ovl13_02_8004BBE4, NULL, 0, 0, 0x130);
    }
    func_ovl13_02_8004CF80();
}

void func_ovl13_02_8004B644(void) {
    if (*D_ovl13_02_8004DCDC & 2) {
        func_ovl13_02_8004CD48(func_ovl13_02_8004BBE4, NULL, 0, 0, 0x130);
    }
}

void func_ovl13_02_8004B57C(void) {
    func_ovl13_02_8004B524();
    func_ovl13_02_80043698();
    func_ovl13_02_8004CF60();
    func_ovl13_02_8004CD28(&D_ovl13_02_8004DE24);
    if (func_ovl13_02_8004CFD0(0x400) != 0) {
        if (!(*D_ovl13_02_8004DCDC & 2)) {
            func_ovl13_02_8004D2E0(0x13);
        }
    } else {
        func_ovl13_02_8004CFC0(0x400);
    }
    func_ovl13_02_8004CD48(func_ovl13_02_8004BD28, (void *)0x28, 0, 0, 0x150);
}

static void func_ovl13_02_8004B524(void) {
    D_ovl13_02_8004DCAC = func_ovl13_02_8004C3D8();
    func_ovl13_02_8004C3B8(&D_ovl13_02_8004DCA0);
    func_ovl13_02_8004C3E0(D_ovl13_02_8004DCAC, &D_ovl13_02_8004DC90);
}

void func_ovl13_02_8004B52C(void) {
    func_ovl13_02_8004CFC0(0x424);
    func_ovl13_02_8004B524();
}

void func_ovl13_02_8004B3F0(void) {
    s32 i;

    if (D_ovl13_02_8004DCF8 != -1) {
        func_ovl13_02_8004D300(D_ovl13_02_8004DCF8);
    }
    func_ovl13_02_8004CA28(1);
    func_ovl13_02_8004CA98(0xF);
    if (D_ovl13_02_8004DCFC != NULL) {
        func_ovl13_02_8004CC10(D_ovl13_02_8004DCFC);
    }
    if (D_ovl13_02_8004DD00 != NULL) {
        func_ovl13_02_8004CC10(D_ovl13_02_8004DD00);
    }
    for (i = 0; i < 10; i++) {
        if (D_ovl13_02_8004DD68[i] != NULL) {
            func_ovl13_02_8004CC10(D_ovl13_02_8004DD68[i]);
        }
    }
    D_ovl13_02_8004DE24 = 0;
    D_ovl13_02_8004DE28 = 0;
    D_ovl13_02_8004DE2C = 0;
    D_ovl13_02_8004DE80.unk0 = 0;
    D_ovl13_02_8004DE98.unk0 = 0;
    D_ovl13_02_8004DEB0.unk0 = 0;
    func_ovl13_02_8004CC10(D_ovl13_02_8004DE3C);
    func_ovl13_02_8004CC10(D_ovl13_02_8004DFAC);
    func_ovl13_02_8004CD38();
    if (*D_ovl13_02_8004DCDC & 2) {
        func_ovl13_02_8004D450();
    }
}

void func_ovl13_02_8004B3B4(void) {
    if (*D_ovl13_02_8004DCDC & 2) {
        func_ovl13_02_8004D450();
    }
}

void func_ovl13_02_8004B360(UnkStructA *arg0) {
    arg0->unk40->unk10 += M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 0);
    arg0->unk40->unk14 += M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 4);
    arg0->unk40->unk18 += M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 8);
}

void func_ovl13_02_8004B298(UnkStructA *arg0) {
    func_ovl13_02_80043098(0x1E, arg0);
    func_ovl13_02_8004CC00(arg0, 0x04000000);
    arg0->unk40->unk48->unk4->unk4 = 0.0f;
    arg0->unk40->unk28 *= 3.5f;
    arg0->unk40->unk30 *= 3.5f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl13_02_8004CD68(0x3C);
}

void func_ovl13_02_8004B1BC(void) {
    s32 *temp_v0;

    func_ovl13_02_8004CFC8(0x43F);
    func_ovl13_02_8004CFC8(0x43E);
    func_ovl13_02_8004CFC8(0x43D);
    func_ovl13_02_8004CFC8(0x43C);
    func_ovl13_02_8004CFC8(0x43A);
    func_ovl13_02_8004CFC8(0x439);
    func_ovl13_02_8004CFC8(0x438);
    func_ovl13_02_8004CFC8(0x437);
    func_ovl13_02_8004CFC8(0x436);
    func_ovl13_02_8004CFC0(0x41F);
    func_ovl13_02_8004CFC0(0x41E);
    func_ovl13_02_8004CFC8(0x41D);
    func_ovl13_02_8004CFC8(0x41C);
    func_ovl13_02_8004CFC8(0x41B);
    func_ovl13_02_8004CFC8(0x41A);
    func_ovl13_02_8004CFC8(0x419);
    func_ovl13_02_8004CFC8(0x424);
    func_ovl13_02_8004CFC8(0x417);
    func_ovl13_02_8004CFC8(0x401);
    D_ovl13_02_8004DCDC = func_ovl13_02_8004C348();
    if (M2C_FIELD(D_ovl13_02_8004DCDC, s32 *, 0x10) == 0) {
        func_ovl13_02_8004CFC0(0x418);
    }
}

void func_ovl13_02_8004B108(void) {
    func_ovl13_02_8004CA18(1);
    func_ovl13_02_8004CA28(0);
    func_ovl13_02_8004CA38(M2C_FIELD(&D_ovl13_02_8004DD48, f32 *, 0), M2C_FIELD(&D_ovl13_02_8004DD48, f32 *, 4), M2C_FIELD(&D_ovl13_02_8004DD48, f32 *, 8));
    func_ovl13_02_8004CA48(M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0), M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4), M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8));
    func_ovl13_02_8004CAA0(0x7F);
    func_ovl13_02_8004CA98(0x10);
    M2C_FIELD(&D_ovl13_02_8004DCE0, f32 *, 0) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DCE0, f32 *, 4) = 90.0f;
    M2C_FIELD(&D_ovl13_02_8004DCE0, f32 *, 8) = 200.0f;
    func_ovl13_02_8004CAD8(&D_ovl13_02_8004DCE0);
    func_ovl13_02_8004CAD0(1500.0f);
    func_ovl13_02_8004C370(0);
}

void func_ovl13_02_8004AF1C(void) {
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_2;

    M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 8) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 4) = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 8);
    M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 0) = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 8) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4) = M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 8);
    M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 0) = M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4);
    D_ovl13_02_8004DCFC = NULL;
    M2C_FIELD(&D_ovl13_02_8004DD00, UnkStructA **, 0) = NULL;
    M2C_FIELD(&D_ovl13_02_8004DD00, s32 *, 4) = 0;
    M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4) = 0.0f;
    D_ovl13_02_8004DD3C = 6.0f;
    M2C_FIELD(&D_ovl13_02_8004DD40, f32 *, 0) = 0.5f;
    M2C_FIELD(&D_ovl13_02_8004DD40, f32 *, 4) = 0.25f;
    temp_v0 = func_ovl13_02_8004CC20(0x173, 0x01000000, 0xD0, NULL);
    D_ovl13_02_8004DCFC = temp_v0;
    func_ovl13_02_8004CC00(temp_v0, 0x0E000000);
    D_ovl13_02_8004DCFC->unk40->unk10 = 0.0f;
    D_ovl13_02_8004DCFC->unk40->unk14 = 0.0f;
    D_ovl13_02_8004DCFC->unk40->unk18 = 0.0f;
    D_ovl13_02_8004DCFC->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    D_ovl13_02_8004DCFC->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8);
    temp_v0_2 = func_ovl13_02_8004CC20(0x174, 0x01080000, 0xD0, NULL);
    M2C_FIELD(&D_ovl13_02_8004DD00, UnkStructA **, 0) = temp_v0_2;
    func_ovl13_02_8004CC00(temp_v0_2, 0x0E000000);
    M2C_FIELD(&D_ovl13_02_8004DD00, UnkStructA **, 0)->unk40->unk10 = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DD00, UnkStructA **, 0)->unk40->unk14 = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DD00, UnkStructA **, 0)->unk40->unk18 = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DD00, UnkStructA **, 0)->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DD00, UnkStructA **, 0)->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8);
    func_ovl13_02_8004CD48(func_ovl13_02_8004ACF8, NULL, 0, 0, 0x150);
    func_ovl13_02_8004CD48(func_ovl13_02_80043E64, NULL, 0, 0, 0x150);
}

void func_ovl13_02_8004ACF8(void) {
    f32 temp_fs0;

    temp_fs0 = func_ovl13_02_8004C938(D_ovl13_02_8004DCFC->unk40, 0) - 0.001f;
    if (func_ovl13_02_8004C940(D_ovl13_02_8004DD00->unk40, 0, 0, 0x400, 0x20, 0x400) == -1) {
        func_ovl13_02_8004BEB8("shift entry err\n");
    }
loop_3:
    D_ovl13_02_8004DCFC->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0) + M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 0);
    D_ovl13_02_8004DCFC->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 4);
    D_ovl13_02_8004DCFC->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 8);
    D_ovl13_02_8004DCFC->unk40->unk1C = M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4);
    D_ovl13_02_8004DD00->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0) + M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 0);
    D_ovl13_02_8004DD00->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 4);
    D_ovl13_02_8004DD00->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 8);
    D_ovl13_02_8004DD00->unk40->unk1C = M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4);
    D_ovl13_02_8004DCFC->unk40->unk48->unk4->unk4 += D_ovl13_02_8004DD3C;
    if (temp_fs0 < D_ovl13_02_8004DCFC->unk40->unk48->unk4->unk4) {
        D_ovl13_02_8004DCFC->unk40->unk48->unk4->unk4 -= temp_fs0;
    }
    func_ovl13_02_8004CD90();
    goto loop_3;
}

void func_ovl13_02_8004AB3C(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    x = (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0) - 500.0f) + 50.0f;
    y = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    z = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + 50.0f;
    for (i = 0; i < 10; i++) {
        D_ovl13_02_8004DD68[i] = func_ovl13_02_8004CC20(0x172, 0x01000000, 0xD0, NULL);
        func_ovl13_02_8004CC00(D_ovl13_02_8004DD68[i], 0x0C000000);
        D_ovl13_02_8004DD68[i]->unk40->unk10 = (i * 100.0f) + x;
        D_ovl13_02_8004DD68[i]->unk40->unk14 = y;
        D_ovl13_02_8004DD68[i]->unk40->unk18 = z;
        D_ovl13_02_8004DD90[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        D_ovl13_02_8004DDB8[i].x = D_ovl13_02_8004DD68[i]->unk40->unk10 + 50.0f;
        D_ovl13_02_8004DDB8[i].y = func_ovl13_02_8004C220();
        D_ovl13_02_8004DDB8[i].z = D_ovl13_02_8004DD68[i]->unk40->unk18;
    }
}

void func_ovl13_02_8004A8E0(void) {
    s32 pad[3];
    s32 p[3];
    UnkStructA *obj;
    s32 i;
    s32 n;
    f32 dx;
    f32 dz;

    n = func_ovl13_02_8004CD70();
    if (D_ovl13_02_8004DD68[n] != NULL) {
        obj = D_ovl13_02_8004DD68[n];
        func_ovl13_02_8004C250(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, p, 0);
        for (i = 0; i < 30; i++) {
            obj->unk40->unk14 -= 1.0f;
            obj->unk40->unk18 += 2.0f;
            func_ovl13_02_8004CD90();
        }
        func_ovl13_02_8004C238(p[0], p[1], p[2] - 3, p[0], p[2] + 2, 0);
        dx = func_ovl13_02_8004CF08(1) ? 5.0f : -5.0f;
        dz = func_ovl13_02_8004CF08(1) ? 5.0f : -5.0f;
        for (i = 0; i < 120; i++) {
            obj->unk40->unk1C += dx;
            obj->unk40->unk20 += dz;
            obj->unk40->unk14 -= 1.0f;
            obj->unk40->unk18 += 15.0f;
            if (i > 60.0) {
                func_ovl13_02_8004CBF8(obj, 0x40000);
            }
            func_ovl13_02_8004CD90();
        }
        func_ovl13_02_8004CC10(obj);
        D_ovl13_02_8004DD68[n] = NULL;
    }
    func_ovl13_02_8004CD58();
}

s32 func_ovl13_02_8004A844(void) {
    Vec3f pad;
    s32 p[3];
    s32 i;
    s32 n;
    s32 r;

    func_ovl13_02_8004C250(M2C_FIELD(&D_ovl13_02_8004DC90, f32 *, 0), M2C_FIELD(&D_ovl13_02_8004DC90, f32 *, 4), M2C_FIELD(&D_ovl13_02_8004DC90, f32 *, 8), p, 2);
    n = 0;
    for (i = -2; i < 3; i++) {
        if (func_ovl13_02_8004C268(p[0] + i, p[1], p[2]) & 0xF) {
            n++;
        }
    }
    if (n >= 3) {
        return 1;
    }
    return 0;
}

void func_ovl13_02_80049F68(void) {
    s32 i;
    UnkStructA *obj;

    func_ovl13_02_80049D50();
    func_ovl13_02_800499A0();
    D_ovl13_02_8004DCF8 = -1;
    D_ovl13_02_8004DE24 = 10;
    D_ovl13_02_8004DE28 = 8;
    D_ovl13_02_8004DE2C = 8;
    if (func_ovl13_02_8004CFD0(0x418) != 0) {
        D_ovl13_02_8004DE24 -= 2;
        D_ovl13_02_8004DE28 /= 2;
        D_ovl13_02_8004DE2C /= 2;
    }
    D_ovl13_02_8004DE34 = 0;
    D_ovl13_02_8004DE74 = 2.5;
    D_ovl13_02_8004DE78 = 2.5f;
    D_ovl13_02_8004DE30 = 0;
    D_ovl13_02_8004DE38 = 1;
    D_ovl13_02_8004DEF0 = 0.0f;
    D_ovl13_02_8004DEF4 = 0.0f;
    D_ovl13_02_8004DEF8 = 0.0f;
    D_ovl13_02_8004DEE4 = 0.0f;
    D_ovl13_02_8004DEE8 = 0.0f;
    D_ovl13_02_8004DEEC = 0.8166667f;
    (&D_ovl13_02_8004DEC8)[0] = ((f32 *) D_ovl13_02_8004DF18)[0];
    (&D_ovl13_02_8004DEC8)[1] = ((f32 *) D_ovl13_02_8004DF18)[1];
    (&D_ovl13_02_8004DEC8)[2] = ((f32 *) D_ovl13_02_8004DF18)[2];
    (&D_ovl13_02_8004DED8)[0] = 0.0f;
    (&D_ovl13_02_8004DED8)[1] = 330.0f;
    (&D_ovl13_02_8004DED8)[2] = 0.0f;
    D_ovl13_02_8004DEFC = 0.0f;
    D_ovl13_02_8004DF00 = 50.0f;
    D_ovl13_02_8004DF04 = 2.0f;
    D_ovl13_02_8004DF08 = 10.0f;
    D_ovl13_02_8004DF0C = 1.0f;
    D_ovl13_02_8004DF10 = 12.0f;
    D_ovl13_02_8004DE3C = func_ovl13_02_8004CC20(0x179, 0x01008004, 0x30, NULL);
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x0E000000);
    D_ovl13_02_8004DE3C->unk40->unk10 = (&D_ovl13_02_8004DEC8)[0];
    D_ovl13_02_8004DE3C->unk40->unk14 = (&D_ovl13_02_8004DEC8)[1];
    D_ovl13_02_8004DE3C->unk40->unk18 = (&D_ovl13_02_8004DEC8)[2];
    D_ovl13_02_8004DE3C->unk40->unk1C = 330.0f;
    D_ovl13_02_8004DE40 = func_ovl13_02_8004CC20(-1, 0x01600000, 0xC0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE40->unk4C = 0.0f;
    D_ovl13_02_8004DE40->unk50 = 0.0f;
    D_ovl13_02_8004DE40->unk54 = 0.0f;
    D_ovl13_02_8004DE40->unk38 = 0.0f;
    D_ovl13_02_8004DE40->unk34 = 24.0f;
    D_ovl13_02_8004DE40->unk40->unk30 = 18.0f;
    D_ovl13_02_8004DE40->unk40->unk28 = D_ovl13_02_8004DE40->unk40->unk2C = D_ovl13_02_8004DE40->unk40->unk30;
    D_ovl13_02_8004DE40->unkC = 0x6040;
    D_ovl13_02_8004DE44 = func_ovl13_02_8004CC20(-1, 0x01600010, 0xC0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE44->unk4C = 0.0f;
    D_ovl13_02_8004DE44->unk50 = -100.0f;
    D_ovl13_02_8004DE44->unk54 = 450.0f;
    D_ovl13_02_8004DE44->unk38 = 0.0f;
    D_ovl13_02_8004DE44->unk34 = 24.0f;
    D_ovl13_02_8004DE44->unk40->unk30 = 15.0f;
    D_ovl13_02_8004DE44->unk40->unk28 = D_ovl13_02_8004DE44->unk40->unk2C = D_ovl13_02_8004DE44->unk40->unk30;
    D_ovl13_02_8004DE44->unkC = D_ovl13_02_8004DE40->unkC;
    D_ovl13_02_8004DE48 = func_ovl13_02_8004CC20(-1, 0, 0xD0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE4C = func_ovl13_02_8004CC20(-1, 0x408004, 0xC0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE4C->unk4C = 0.0f;
    D_ovl13_02_8004DE4C->unk50 = 0;
    D_ovl13_02_8004DE4C->unk54 = -500.0f;
    D_ovl13_02_8004DE4C->unk38 = 0;
    D_ovl13_02_8004DE4C->unk34 = 100.0f;
    D_ovl13_02_8004DE4C->unkC = D_ovl13_02_8004DE40->unkC;
    D_ovl13_02_8004DE70 = func_ovl13_02_8004CC20(-1, 0x01600000, 0xC0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE70->unk4C = 0.0f;
    D_ovl13_02_8004DE70->unk50 = -350.0f;
    D_ovl13_02_8004DE70->unk54 = 500.0f;
    D_ovl13_02_8004DE70->unk38 = 0.0f;
    D_ovl13_02_8004DE70->unk34 = 24.0f;
    D_ovl13_02_8004DE70->unk40->unk30 = 12.0f;
    D_ovl13_02_8004DE70->unk40->unk28 = D_ovl13_02_8004DE70->unk40->unk2C = D_ovl13_02_8004DE70->unk40->unk30;
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    D_ovl13_02_8004DE80.unk8 = 0.8f;
    D_ovl13_02_8004DE98.unk8 = 0.8f;
    D_ovl13_02_8004DEB0.unk8 = 0.8f;
    D_ovl13_02_8004DE80.unkC = 0.11f;
    D_ovl13_02_8004DE98.unkC = 0.11f;
    D_ovl13_02_8004DEB0.unkC = 0.11f;
    D_ovl13_02_8004DE80.unk10 = 0.999f;
    D_ovl13_02_8004DE98.unk10 = 0.999f;
    D_ovl13_02_8004DEB0.unk10 = 0.999f;
    D_ovl13_02_8004DE80.unk4 = 120.0f;
    D_ovl13_02_8004DE98.unk4 = 160.0f;
    D_ovl13_02_8004DEB0.unk4 = 220.0f;
    D_ovl13_02_8004DE50[7] = func_ovl13_02_8004CC20(0x177, 0x400000, 0xD0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE50[7]->unk4C = 0.0f;
    D_ovl13_02_8004DE50[7]->unk50 = -35.0f;
    D_ovl13_02_8004DE50[7]->unk54 = 680.0f;
    M2C_FIELD(D_ovl13_02_8004DE50[7], Sub18_ovl13_02 **, 0x3C) = &D_ovl13_02_8004DEB0;
    i = 0;
    D_ovl13_02_8004DE50[i] = func_ovl13_02_8004CC20(0x177, 0, 0xD0, NULL);
    func_ovl13_02_80049F1C(D_ovl13_02_8004DE50[i]);
    func_ovl13_02_8004CBE0(D_ovl13_02_8004DE50[7], D_ovl13_02_8004DE50[i], (Link_ovl13_02 *) &D_ovl13_02_8004DEB0, 0x150);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE50[i], 0x500000);
    D_ovl13_02_8004DE50[i]->unk4C = 0.0f;
    D_ovl13_02_8004DE50[i]->unk50 = 40.0f;
    D_ovl13_02_8004DE50[i]->unk54 = 220.0f;
    i++;
    D_ovl13_02_8004DE50[i] = func_ovl13_02_8004CC20(0x177, 0, 0xD0, D_ovl13_02_8004DE50[7]);
    func_ovl13_02_80049F1C(D_ovl13_02_8004DE50[i]);
    func_ovl13_02_8004CBE0(D_ovl13_02_8004DE50[i - 1], D_ovl13_02_8004DE50[i], (Link_ovl13_02 *) &D_ovl13_02_8004DEB0, 0x150);
    i++;
    D_ovl13_02_8004DE50[i] = func_ovl13_02_8004CC20(0x178, 0, 0xD0, NULL);
    func_ovl13_02_80049F1C(D_ovl13_02_8004DE50[i]);
    func_ovl13_02_8004CBE0(D_ovl13_02_8004DE50[i - 1], D_ovl13_02_8004DE50[i], (Link_ovl13_02 *) &D_ovl13_02_8004DE98, 0x150);
    i++;
    D_ovl13_02_8004DE50[i] = func_ovl13_02_8004CC20(0x178, 0, 0xD0, NULL);
    func_ovl13_02_80049F1C(D_ovl13_02_8004DE50[i]);
    func_ovl13_02_8004CBE0(D_ovl13_02_8004DE50[i - 1], D_ovl13_02_8004DE50[i], (Link_ovl13_02 *) &D_ovl13_02_8004DE98, 0x150);
    i++;
    D_ovl13_02_8004DE50[i] = func_ovl13_02_8004CC20(0x17E, 0, 0xD0, NULL);
    func_ovl13_02_80049F1C(D_ovl13_02_8004DE50[i]);
    func_ovl13_02_8004CBE0(D_ovl13_02_8004DE50[i - 1], D_ovl13_02_8004DE50[i], (Link_ovl13_02 *) &D_ovl13_02_8004DE80, 0x150);
    i++;
    D_ovl13_02_8004DE50[i] = func_ovl13_02_8004CC20(0x17C, 0, 0xD0, NULL);
    func_ovl13_02_80049F1C(D_ovl13_02_8004DE50[i]);
    func_ovl13_02_8004CBE0(D_ovl13_02_8004DE50[i - 1], D_ovl13_02_8004DE50[i], (Link_ovl13_02 *) &D_ovl13_02_8004DE80, 0x150);
    i++;
    D_ovl13_02_8004DE50[i] = func_ovl13_02_8004CC20(0x180, 0, 0x30, NULL);
    func_ovl13_02_80049F1C(D_ovl13_02_8004DE50[i]);
    func_ovl13_02_8004CBE0(D_ovl13_02_8004DE50[i - 1], D_ovl13_02_8004DE50[i], (Link_ovl13_02 *) &D_ovl13_02_8004DE80, 0x150);
    func_ovl13_02_8004CBC8(D_ovl13_02_8004DE50[i], 0x30);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE50[i], 0x8000);
    D_ovl13_02_8004DE50[i]->unk38 = 0;
    D_ovl13_02_8004DE50[i]->unk34 = 150.0f;
    D_ovl13_02_8004DE50[i]->unkC = D_ovl13_02_8004DE40->unkC;
    obj = func_ovl13_02_8004CC30(D_ovl13_02_8004DE50[i]);
    obj->unk4C = obj->unk54 = D_ovl13_02_8004DE50[i]->unk34 / 50.0f;
    func_ovl13_02_8004C900(D_ovl13_02_8004DE3C->unk40, 4);
    func_ovl13_02_8004636C();
    func_ovl13_02_800463BC();
    func_ovl13_02_8004C900(D_ovl13_02_8004DE50[6]->unk40, 2);
    func_ovl13_02_8004C900(D_ovl13_02_8004DE50[5]->unk40, 2);
    func_ovl13_02_8004C900(D_ovl13_02_8004DE50[4]->unk40, 2);
    func_ovl13_02_80046268();
    func_ovl13_02_8004CD48(func_ovl13_02_8004980C, NULL, 0, 0, 0x130);
    func_ovl13_02_8004CD48(func_ovl13_02_80045AB8, NULL, 0, 0, 0x130);
}

void func_ovl13_02_80049F1C(UnkStructA *arg0) {
    func_ovl13_02_8004CBF8(arg0, 0x01000000);
    func_ovl13_02_8004CC00(arg0, 0x0E000000);
    func_ovl13_02_8004CBC8(arg0, 0xD0);
    arg0->unk38 = 0.0f;
}

void func_ovl13_02_80049D50(void) {
    s32 pad;

    ((Vec3f *) D_ovl13_02_8004DF18)[0].x = (*(Vec3f *) &D_ovl13_02_8004DD10).x;
    ((Vec3f *) D_ovl13_02_8004DF18)[0].y = (*(Vec3f *) &D_ovl13_02_8004DD10).y;
    ((Vec3f *) D_ovl13_02_8004DF18)[0].z = (*(Vec3f *) &D_ovl13_02_8004DD10).z - 1400.0f;
    ((Vec3f *) D_ovl13_02_8004DF18)[1].x = (*(Vec3f *) &D_ovl13_02_8004DD10).x - 300.0f;
    ((Vec3f *) D_ovl13_02_8004DF18)[1].y = (*(Vec3f *) &D_ovl13_02_8004DD10).y;
    ((Vec3f *) D_ovl13_02_8004DF18)[1].z = ((Vec3f *) D_ovl13_02_8004DF18)[0].z;
    ((Vec3f *) D_ovl13_02_8004DF18)[2].x = (*(Vec3f *) &D_ovl13_02_8004DD10).x + 300.0f;
    ((Vec3f *) D_ovl13_02_8004DF18)[2].y = (*(Vec3f *) &D_ovl13_02_8004DD10).y;
    ((Vec3f *) D_ovl13_02_8004DF18)[2].z = ((Vec3f *) D_ovl13_02_8004DF18)[0].z;
    ((Vec3f *) D_ovl13_02_8004DF18)[3].x = (*(Vec3f *) &D_ovl13_02_8004DD10).x;
    ((Vec3f *) D_ovl13_02_8004DF18)[3].y = (*(Vec3f *) &D_ovl13_02_8004DD10).y;
    ((Vec3f *) D_ovl13_02_8004DF18)[3].z = (*(Vec3f *) &D_ovl13_02_8004DD10).z - 1700.0f;
    ((Vec3f *) D_ovl13_02_8004DF18)[4].x = (*(Vec3f *) &D_ovl13_02_8004DD10).x - 300.0f;
    ((Vec3f *) D_ovl13_02_8004DF18)[4].y = (*(Vec3f *) &D_ovl13_02_8004DD10).y;
    ((Vec3f *) D_ovl13_02_8004DF18)[4].z = ((Vec3f *) D_ovl13_02_8004DF18)[3].z;
    ((Vec3f *) D_ovl13_02_8004DF18)[5].x = (*(Vec3f *) &D_ovl13_02_8004DD10).x + 300.0f;
    ((Vec3f *) D_ovl13_02_8004DF18)[5].y = (*(Vec3f *) &D_ovl13_02_8004DD10).y;
    ((Vec3f *) D_ovl13_02_8004DF18)[5].z = ((Vec3f *) D_ovl13_02_8004DF18)[3].z;
    ((Vec3f *) D_ovl13_02_8004DF60)->x = (*(Vec3f *) &D_ovl13_02_8004DD10).x;
    ((Vec3f *) D_ovl13_02_8004DF60)->y = (*(Vec3f *) &D_ovl13_02_8004DD10).y;
    ((Vec3f *) D_ovl13_02_8004DF60)->z = (*(Vec3f *) &D_ovl13_02_8004DD10).z + 1100.0f;
    ((Vec3f *) D_ovl13_02_8004DF70)->x = (*(Vec3f *) &D_ovl13_02_8004DD10).x;
    ((Vec3f *) D_ovl13_02_8004DF70)->y = (*(Vec3f *) &D_ovl13_02_8004DD10).y + 2500.0f;
    ((Vec3f *) D_ovl13_02_8004DF70)->z = (*(Vec3f *) &D_ovl13_02_8004DD10).z - 1800.0f;
    ((Vec3f *) D_ovl13_02_8004DF80)->x = (*(Vec3f *) &D_ovl13_02_8004DD10).x;
    ((Vec3f *) D_ovl13_02_8004DF80)->y = 500.0f;
    ((Vec3f *) D_ovl13_02_8004DF80)->z = (*(Vec3f *) &D_ovl13_02_8004DD10).z + 4000.0f;
    ((Vec3f *) D_ovl13_02_8004DF90)->x = (*(Vec3f *) &D_ovl13_02_8004DD10).x;
    ((Vec3f *) D_ovl13_02_8004DF90)->y = (*(Vec3f *) &D_ovl13_02_8004DD10).y + 800.0f;
    ((Vec3f *) D_ovl13_02_8004DF90)->z = (*(Vec3f *) &D_ovl13_02_8004DD10).z - 2400.0f;
    ((Vec3f *) D_ovl13_02_8004DFA0)->x = ((Vec3f *) D_ovl13_02_8004DF90)->x;
    ((Vec3f *) D_ovl13_02_8004DFA0)->y = (*(Vec3f *) &D_ovl13_02_8004DD10).y + 100.0f;
    ((Vec3f *) D_ovl13_02_8004DFA0)->z = ((Vec3f *) D_ovl13_02_8004DF90)->z;
    ((Vec3f *) D_ovl13_02_8004DFC0)->x = (*(Vec3f *) &D_ovl13_02_8004DD10).x;
    ((Vec3f *) D_ovl13_02_8004DFC0)->y = (*(Vec3f *) &D_ovl13_02_8004DD10).y;
    ((Vec3f *) D_ovl13_02_8004DFC0)->z = (*(Vec3f *) &D_ovl13_02_8004DD10).z - 1300.0f;
    ((Vec3f *) D_ovl13_02_8004DFD0)->x = ((Vec3f *) D_ovl13_02_8004DD58)->x;
    ((Vec3f *) D_ovl13_02_8004DFD0)->y = ((Vec3f *) D_ovl13_02_8004DD58)->y - 600.0f;
    ((Vec3f *) D_ovl13_02_8004DFD0)->z = ((Vec3f *) D_ovl13_02_8004DD58)->z;
}

void func_ovl13_02_800499A0(void) {
    s32 pad;
    D_ovl13_02_8004D4F8[0].unk24[0] = (M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 0 * 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0 * 4)) / D_ovl13_02_8004D4F8[0].unk0;
    D_ovl13_02_8004D4F8[0].unk24[1] = (M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 1 * 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 1 * 4)) / D_ovl13_02_8004D4F8[0].unk0;
    D_ovl13_02_8004D4F8[0].unk24[2] = (M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 2 * 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 2 * 4)) / D_ovl13_02_8004D4F8[0].unk0;
    D_ovl13_02_8004D4F8[0].unk24[0] += -20.833334f;
    D_ovl13_02_8004D4F8[0].unk30[0] = 0.17433752f;
    D_ovl13_02_8004D4F8[1].unk24[0] = M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 0 * 4);
    D_ovl13_02_8004D4F8[1].unk24[1] = M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 1 * 4);
    D_ovl13_02_8004D4F8[1].unk24[2] = M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 2 * 4);
    D_ovl13_02_8004D4F8[2].unk24[0] = (M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0 * 4) - M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 0 * 4)) / D_ovl13_02_8004D4F8[2].unk0;
    D_ovl13_02_8004D4F8[2].unk24[1] = (M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 1 * 4) - M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 1 * 4)) / D_ovl13_02_8004D4F8[2].unk0;
    D_ovl13_02_8004D4F8[2].unk24[2] = (M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 2 * 4) - M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 2 * 4)) / D_ovl13_02_8004D4F8[2].unk0;
    D_ovl13_02_8004D4F8[2].unk24[0] += -20.833334f;
    D_ovl13_02_8004D4F8[2].unk30[0] = 0.17433752f;
    D_ovl13_02_8004D4F8[3].unk24[0] = M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0 * 4);
    D_ovl13_02_8004D4F8[3].unk24[1] = M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 1 * 4);
    D_ovl13_02_8004D4F8[3].unk24[2] = M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 2 * 4);
    D_ovl13_02_8004D608[0].unk24[0] = (M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0 * 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0 * 4)) / D_ovl13_02_8004D608[0].unk0;
    D_ovl13_02_8004D608[0].unk24[1] = (M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 1 * 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 1 * 4)) / D_ovl13_02_8004D608[0].unk0;
    D_ovl13_02_8004D608[0].unk24[2] = (M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 2 * 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 2 * 4)) / D_ovl13_02_8004D608[0].unk0;
    D_ovl13_02_8004D608[0].unk24[0] += -26.041666f;
    D_ovl13_02_8004D608[0].unk30[0] = 0.2726876f;
    D_ovl13_02_8004D608[1].unk24[0] = (M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 0 * 4) - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0 * 4)) / D_ovl13_02_8004D608[1].unk0;
    D_ovl13_02_8004D608[1].unk24[1] = (M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 1 * 4) - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 1 * 4)) / D_ovl13_02_8004D608[1].unk0;
    D_ovl13_02_8004D608[1].unk24[2] = (M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 2 * 4) - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 2 * 4)) / D_ovl13_02_8004D608[1].unk0;
    D_ovl13_02_8004D608[2].unk24[0] = M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 0 * 4);
    D_ovl13_02_8004D608[2].unk24[1] = M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 1 * 4);
    D_ovl13_02_8004D608[2].unk24[2] = M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 2 * 4);
    D_ovl13_02_8004D608[3].unk24[0] = (M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0 * 4) - M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 0 * 4)) / D_ovl13_02_8004D608[3].unk0;
    D_ovl13_02_8004D608[3].unk24[1] = (M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 1 * 4) - M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 1 * 4)) / D_ovl13_02_8004D608[3].unk0;
    D_ovl13_02_8004D608[3].unk24[2] = (M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 2 * 4) - M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 2 * 4)) / D_ovl13_02_8004D608[3].unk0;
    D_ovl13_02_8004D608[5].unk24[0] = (M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0 * 4) - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0 * 4)) / D_ovl13_02_8004D608[5].unk0;
    D_ovl13_02_8004D608[5].unk24[1] = (M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 1 * 4) - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 1 * 4)) / D_ovl13_02_8004D608[5].unk0;
    D_ovl13_02_8004D608[5].unk24[2] = (M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 2 * 4) - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 2 * 4)) / D_ovl13_02_8004D608[5].unk0;
    D_ovl13_02_8004D608[5].unk24[0] += -26.041666f;
    D_ovl13_02_8004D608[5].unk30[0] = 0.2726876f;
    D_ovl13_02_8004D608[6].unk24[0] = M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0 * 4);
    D_ovl13_02_8004D608[6].unk24[1] = M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 1 * 4);
    D_ovl13_02_8004D608[6].unk24[2] = M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 2 * 4);
    D_ovl13_02_8004D8B0.unk24[0] = (M2C_FIELD(&D_ovl13_02_8004DFD0, f32 *, 0 * 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0 * 4)) / 30.0f;
    D_ovl13_02_8004D8B0.unk24[1] = (M2C_FIELD(&D_ovl13_02_8004DFD0, f32 *, 1 * 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 1 * 4)) / 30.0f;
    D_ovl13_02_8004D8B0.unk24[2] = (M2C_FIELD(&D_ovl13_02_8004DFD0, f32 *, 2 * 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 2 * 4)) / 30.0f;
    (&D_ovl13_02_8004D8B0)[1].unk24[0] = D_ovl13_02_8004D8B0.unk24[0] * -1.0f;
    (&D_ovl13_02_8004D8B0)[1].unk24[1] = D_ovl13_02_8004D8B0.unk24[1] * -1.0f;
    (&D_ovl13_02_8004D8B0)[1].unk24[2] = D_ovl13_02_8004D8B0.unk24[2] * -1.0f;
}

void func_ovl13_02_8004980C(void) {
    s32 n;
    s32 save;

    while (func_ovl13_02_8004CFD0(0x424) == 0) {
        func_ovl13_02_8004CD90();
    }
    if (*D_ovl13_02_8004DCDC & 2) {
        if (func_ovl13_02_8004CFB0(0xA4) != 0) {
            func_ovl13_02_80046E10(2);
        } else {
            func_ovl13_02_800480EC(2);
        }
    }
    n = D_ovl13_02_8004DE38 = 0xC;
    while (D_ovl13_02_8004DE24 > 0) {
        save = D_ovl13_02_8004DE30;
        D_ovl13_02_8004DE30 = 0;
        func_ovl13_02_80048FBC(n);
        D_ovl13_02_8004DE30 = save;
        func_ovl13_02_800496A0(&D_ovl13_02_8004DE30, &n);
        func_ovl13_02_80049468(&D_ovl13_02_8004DE30, &n);
        n = D_ovl13_02_8004DE38 = func_ovl13_02_8004CF08(3) + D_ovl13_02_8004DE24 + 1;
    }
    func_ovl13_02_8004CFC8(0x41E);
    func_ovl13_02_8004640C();
    func_ovl13_02_8004CFC0(0x41E);
    func_ovl13_02_8004CFC0(0x41B);
    func_ovl13_02_8004CD48(func_ovl13_02_800444F0, NULL, 0, 0, 0x150);
    func_ovl13_02_80044630();
    func_ovl13_02_8004CD68(0xB4);
    func_ovl13_02_8004C370(1);
    func_ovl13_02_8004C318();
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_800496A0(s32 *arg0, s32 *arg1) {
    s32 list[8];
    s32 n;
    s32 i;

    if (D_ovl13_02_8004DE24 > 0) {
        for (i = 0; i < 8; i++) {
            list[i] = -1;
        }
        n = 0;
        if ((D_ovl13_02_8004DE2C <= 0) || (*arg0 != 2)) {
            for (i = 0; i < 1; i++) {
                list[n++] = 2;
            }
        }
        if (D_ovl13_02_8004DE28 > 0) {
            for (i = 0; i < 2; i++) {
                list[n++] = 1;
            }
        }
        if (D_ovl13_02_8004DE2C > 0) {
            for (i = 0; i < 5; i++) {
                list[n++] = 3;
            }
        }
        n--;
        switch (list[func_ovl13_02_8004CF08(n)]) {
        case 2:
            func_ovl13_02_80049564(arg0, arg1);
            return;
        case 1:
            func_ovl13_02_800495FC(arg0, arg1);
            return;
        case 3:
            func_ovl13_02_80049504(arg0, arg1);
            break;
        }
    }
}

void func_ovl13_02_80049650(s32 *arg0, s32 *arg1) {
    *arg0 = 0;
    *arg1 = func_ovl13_02_8004CF08(4) + 8;
    if (func_ovl13_02_8004CFD0(0x418) != 0) {
        *arg1 = 0xC;
    }
}

void func_ovl13_02_800495FC(s32 *arg0, s32 *arg1) {
    *arg0 = 1;
    *arg1 = func_ovl13_02_8004CF08(3) + 3;
    if (func_ovl13_02_8004CFD0(0x418) != 0) {
        *arg1 = 3;
    }
}

void func_ovl13_02_80049564(s32 *arg0, s32 *arg1) {
    *arg0 = 2;
    *arg1 = 1;
    if (D_ovl13_02_8004DE28 != 0) {
        *arg1 += func_ovl13_02_8004CF08(1);
        if (D_ovl13_02_8004DE24 < 5) {
            if (func_ovl13_02_8004CFD0(0x418) == 0) {
                *arg1 = func_ovl13_02_8004CF08(3) + 1;
            }
        }
    }
}

void func_ovl13_02_80049504(s32 *arg0, s32 *arg1) {
    *arg0 = 3;
    if (func_ovl13_02_8004CFD0(0x418) != 0) {
        *arg1 = func_ovl13_02_8004CF08(2) + 1;
        return;
    }
    *arg1 = func_ovl13_02_8004CF08(5) + 1;
}

void func_ovl13_02_80049468(s32 *arg0, s32 *arg1) {
    s32 temp_v0;

    if (D_ovl13_02_8004DE24 > 0) {
        temp_v0 = *arg0;
        switch (temp_v0) {                          /* irregular */
        case 0:
            func_ovl13_02_80048FBC(*arg1);
            return;
        case 1:
            func_ovl13_02_800489C0(*arg1);
            return;
        case 2:
            func_ovl13_02_800480EC(*arg1);
            return;
        case 3:
            func_ovl13_02_80046E10(*arg1);
            break;
        }
    }
}

static void func_ovl13_02_80049400(void) {
    void *sp1C;

    if (0) { func_ovl13_02_80048FBC(0); }
    sp1C = func_ovl13_02_8004CD70();
    func_ovl13_02_8004CD68((func_ovl13_02_8004CF08(2) * 0xA) + 0xA);
    func_ovl13_02_8004D2F0((s32) sp1C, M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0), M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4), M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8));
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_800489C0(s32 arg0) {
    s32 padt[1];
    f32 spA0[3];
    f32 sp94[3];
    f32 pad[7];
    s32 var_s0;
    s32 var_s1;
    s32 var_s5;

    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x08000000);
    func_ovl13_02_8004511C();
    spA0[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    spA0[1] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    spA0[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    func_ovl13_02_800430CC(&spA0[0], 0x1E, 1);
    func_ovl13_02_8004CA70(D_ovl13_02_8004D4F8, 0x170, 0);
    spA0[0] = M2C_FIELD(&D_ovl13_02_8004DF60, f32 *, 0);
    spA0[1] = 500.0f;
    spA0[2] = M2C_FIELD(&D_ovl13_02_8004DF60, f32 *, 8);
    func_ovl13_02_80044F0C(&spA0[0], 0xB4, 10.0f);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    func_ovl13_02_8004CB00(NULL);
    func_ovl13_02_8004CAA0(0x20);
    spA0[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    spA0[1] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    spA0[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    func_ovl13_02_800434C0(&spA0[0]);
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
    if (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
        do {
            func_ovl13_02_8004CD90();
        } while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40));
    }
    func_ovl13_02_8004CFC0(0x41D);
    func_ovl13_02_8004D2D0(0xDE);
    func_ovl13_02_8004362C(1);
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    D_ovl13_02_8004DE80.unk8 = 0.8f;
    D_ovl13_02_8004DE98.unk8 = 0.8f;
    D_ovl13_02_8004DEB0.unk8 = 0.8f;
    D_ovl13_02_8004DE80.unkC = 0.11f;
    D_ovl13_02_8004DE98.unkC = 0.11f;
    D_ovl13_02_8004DEB0.unkC = 0.11f;
    D_ovl13_02_8004DE80.unk10 = 0.999f;
    D_ovl13_02_8004DE98.unk10 = 0.999f;
    D_ovl13_02_8004DEB0.unk10 = 0.999f;
    D_ovl13_02_8004DEF8 = 1.0f;
    D_ovl13_02_8004DEFC = 0.0f;
    D_ovl13_02_8004DF00 = 20.0f;
    D_ovl13_02_8004DF04 = 2.0f;
    D_ovl13_02_8004DF08 = 10.0f;
    D_ovl13_02_8004DF0C = 4.0f;
    var_s0 = 5;
    var_s1 = 0x1E;
    var_s5 = 0;
    D_ovl13_02_8004DF10 = 0.0f;
    if (arg0 > 0) {
        do {
            D_ovl13_02_8004DEF4 = 0.0f;
            D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 = 0.0f;
            func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
            if (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
loop_5:
                var_s0 += 1;
                if (var_s0 >= 6) {
                    func_ovl13_02_8004CD48(func_ovl13_02_80048504, NULL, 0, 0, 0x150);
                    var_s0 = 0;
                }
                var_s1 += 1;
                if (var_s1 >= 0x1F) {
                    func_ovl13_02_8004D2D0(0xE0);
                    var_s1 = 0;
                }
                if (D_ovl13_02_8004DE34 != 0) {
                    func_ovl13_02_8004CFC8(0x41E);
                    func_ovl13_02_80046B34(D_ovl13_02_8004DE34);
                    func_ovl13_02_8004CFC0(0x41E);
                    var_s5 = arg0;
                    D_ovl13_02_8004DE80.unk0 = 2;
                    D_ovl13_02_8004DE98.unk0 = 2;
                    D_ovl13_02_8004DEB0.unk0 = 2;
                    D_ovl13_02_8004DE80.unk8 = 0.8f;
                    D_ovl13_02_8004DE80.unkC = 0.11f;
                    D_ovl13_02_8004DE80.unk10 = 0.999f;
                    D_ovl13_02_8004DE98.unk8 = 0.8f;
                    D_ovl13_02_8004DE98.unkC = 0.11f;
                    D_ovl13_02_8004DE98.unk10 = 0.999f;
                    D_ovl13_02_8004DEB0.unk8 = 0.8f;
                    D_ovl13_02_8004DEB0.unkC = 0.11f;
                    D_ovl13_02_8004DEB0.unk10 = 0.999f;
                } else {
                    func_ovl13_02_8004CD90();
                    if (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
                        goto loop_5;
                    }
                }
            }
            var_s5 += 1;
        } while (var_s5 < arg0);
    }
    D_ovl13_02_8004DE34 = 0;
    func_ovl13_02_8004CFC8(0x41D);
    if (D_ovl13_02_8004DE24 > 0) {
        D_ovl13_02_8004DEF8 = 1.0f;
        D_ovl13_02_8004DEFC = 0.0f;
        D_ovl13_02_8004DF00 = 50.0f;
        D_ovl13_02_8004DF04 = 2.0f;
        D_ovl13_02_8004DF08 = 10.0f;
        D_ovl13_02_8004DF0C = 1.0f;
        D_ovl13_02_8004DF10 = 12.0f;
        func_ovl13_02_8004362C(0);
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x0C000000);
        func_ovl13_02_8004511C();
        func_ovl13_02_8004CA70(&D_ovl13_02_8004D4F8[2], 0x170, 0);
        spA0[0] = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0);
        spA0[1] = 500.0f;
        spA0[2] = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8);
        func_ovl13_02_80044F0C(&spA0[0], 0xB4, 20.0f);
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
        spA0[2] = 0.0f;
        spA0[1] = 0.0f;
        spA0[0] = 0.0f;
        sp94[0] = 0.0f;
        sp94[1] = 30.0f;
        sp94[2] = 100.0f;
        func_ovl13_02_8004CB90(&sp94[0], &spA0[0]);
        spA0[0] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
        spA0[1] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
        spA0[2] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
        func_ovl13_02_800434C0(&spA0[0]);
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
        if (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
            do {
                func_ovl13_02_8004CD90();
            } while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40));
        }
    }
}

void func_ovl13_02_80048504(void) {
    UnkStructA *obj;
    UnkStructA *spr;
    UnkStructA *shadow;
    f32 vel[3];
    f32 pos[3];
    f32 ang[3];
    s32 i;
    f32 t;

    spr = func_ovl13_02_8004CC20(0x183, 0x11080000, 0xD0, NULL);
    obj = func_ovl13_02_8004CC20(0x182, 0x01080000, 0x60, NULL);
    if (func_ovl13_02_8004CFD0(0x418) != 0) {
        func_ovl13_02_8004CBF8(obj, 0x800);
    } else {
        func_ovl13_02_8004CBF8(obj, 0x8400);
    }
    shadow = func_ovl13_02_8004CC30(obj);
    pos[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    pos[1] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    pos[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + -450.0f;
    func_ovl13_02_8004CB88(pos, &D_ovl13_02_8004DC90, ang);
    if (func_ovl13_02_8004CF08(1) != 0) {
        ang[0] += func_ovl13_02_8004CF00() * 15.0;
    } else {
        ang[0] -= func_ovl13_02_8004CF00() * 15.0;
    }
    ang[1] = 0.0f;
    ang[2] = 300.0f;
    func_ovl13_02_8004CB90(ang, vel);
    spr->unk40->unk10 = pos[0] + vel[0];
    spr->unk40->unk14 = pos[1];
    spr->unk40->unk18 = pos[2] + vel[2];
    spr->unk40->unk36 = 0xFF;
    obj->unk40->unk10 = pos[0] + vel[0];
    obj->unk40->unk14 = pos[1];
    obj->unk40->unk18 = pos[2] + vel[2];
    obj->unk40->unk36 = 0x80;
    obj->unk68 = func_ovl13_02_8004CF00() * 30.0 + 30.0;
    ang[2] = func_ovl13_02_8004CF00() * 5.0 + 5.0;
    func_ovl13_02_8004CB90(ang, vel);
    for (i = 0; ; i++) {
        if (i < 20) {
            func_ovl13_02_8004564C(spr, i, 20, 2.5f, 5.0f);
        } else {
            func_ovl13_02_8004CC00(spr, 0x01000000);
        }
        obj->unk40->unk10 += vel[0];
        obj->unk40->unk18 += vel[2];
        func_ovl13_02_8004CC78(obj);
        if (((obj->unk40->unk14 <= func_ovl13_02_8004C220()) ? 1 : 0)) {
            break;
        }
        if (obj->unk68 == 0.0f) {
            func_ovl13_02_8004CC10(shadow);
            break;
        }
        if (func_ovl13_02_8004CBA8(obj, 3) != 0) {
            func_ovl13_02_8004CD90();
            break;
        }
        func_ovl13_02_8004CD90();
    }
    func_ovl13_02_8004CC00(obj, 0x800);
    if (((obj->unk40->unk14 <= func_ovl13_02_8004C220()) ? 1 : 0)) {
        func_ovl13_02_800484B4(obj);
        func_ovl13_02_8004CC00(obj, 0x01000000);
        func_ovl13_02_8004CD90();
    } else {
        func_ovl13_02_8004CC00(obj, 0x3FFFF);
        for (i = 0; i < 20; i++) {
            t = (f32) i / 20.0f;
            obj->unk40->unk30 = obj->unk40->unk28 = 2.0f * func_ovl13_02_8004CEF0(t * 180.0f) + 1.0f;
            obj->unk40->unk2C = func_ovl13_02_8004CEF8(t * 180.0f) + 0.1f;
            obj->unk40->unk36 = (1.0f - t) * 128.0f;
            func_ovl13_02_8004CD90();
        }
    }
    func_ovl13_02_8004CC10(obj);
    func_ovl13_02_8004CC10(spr);
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_800484B4(arg0) UnkStructA *arg0; {
    func_ovl13_02_8004CC00(arg0, 0x01000000);
    func_ovl13_02_80043098(0xB3, arg0);
    func_ovl13_02_8004CD48(func_ovl13_02_800460C0, arg0, 0, 0, 0x150);
}

void func_ovl13_02_800480EC(s32 arg0) {
    f32 sp44[3];
    f32 sp38[3];
    f32 pad[3];

    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x08000000);
    func_ovl13_02_8004511C();
    func_ovl13_02_8004CA70(D_ovl13_02_8004D608, 0x170, 0);
    sp44[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp44[1] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    sp44[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    func_ovl13_02_800430CC(sp44, 0x1E, 1);
    sp44[0] = M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 0);
    sp44[1] = 500.0f;
    sp44[2] = M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 8);
    func_ovl13_02_80044F0C(sp44, 0xF0, 10.0f);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    func_ovl13_02_8004CB00(D_ovl13_02_8004DE3C);
    func_ovl13_02_8004CA98(0x20);
    func_ovl13_02_8004CAC0(50.0f);
    D_ovl13_02_8004DE50[0]->unk50 = 10.0f;
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    D_ovl13_02_8004DE80.unk8 = 0.8f;
    D_ovl13_02_8004DE98.unk8 = 0.8f;
    D_ovl13_02_8004DEB0.unk8 = 0.8f;
    D_ovl13_02_8004DE80.unkC = 0.22f;
    D_ovl13_02_8004DE98.unkC = 0.22f;
    D_ovl13_02_8004DEB0.unkC = 0.22f;
    D_ovl13_02_8004DE80.unk10 = 0.999f;
    D_ovl13_02_8004DE98.unk10 = 0.999f;
    D_ovl13_02_8004DEB0.unk10 = 0.999f;
    sp44[0] = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    sp44[1] = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4) + 5000.0f;
    sp44[2] = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8);
    func_ovl13_02_800430CC(sp44, 0x3C, 1);
    sp44[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp44[1] = func_ovl13_02_8004C220() + 10.0f;
    sp44[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    func_ovl13_02_80044F0C(sp44, 0xF, 20.0f);
    func_ovl13_02_8004CFC8(0x41E);
    func_ovl13_02_8004CFC8(0x41F);
    func_ovl13_02_8004CFC0(0x41A);
    func_ovl13_02_80047EEC();
    func_ovl13_02_8004CB00(NULL);
    func_ovl13_02_8004CAA0(0x20);
    func_ovl13_02_8004CAC0(10.0f);
    func_ovl13_02_80047C60(arg0);
    func_ovl13_02_8004799C();
    func_ovl13_02_8004CD48(func_ovl13_02_800446B0, NULL, 0, 0, 0x110);
    func_ovl13_02_8004CFC8(0x41A);
    func_ovl13_02_8004CA70(&D_ovl13_02_8004D608[3], 0x170, 0);
    sp44[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp44[1] = 500.0f;
    sp44[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    func_ovl13_02_80044F0C(sp44, 0x1E, 20.0f);
    func_ovl13_02_8004CFC0(0x41E);
    func_ovl13_02_8004362C(0);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x0C000000);
    sp44[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp44[1] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    sp44[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    func_ovl13_02_800430CC(sp44, 0x3C, 1);
    sp44[0] = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0);
    sp44[1] = 500.0f;
    sp44[2] = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8);
    func_ovl13_02_80044F0C(sp44, 0xF0, 20.0f);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    func_ovl13_02_8004CA90();
    sp44[2] = 0.0f;
    sp44[1] = 0.0f;
    sp44[0] = 0.0f;
    sp38[0] = 0.0f;
    sp38[1] = 30.0f;
    sp38[2] = 100.0f;
    func_ovl13_02_8004CB90(sp38, sp44);
    sp44[0] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp44[1] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    sp44[2] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    func_ovl13_02_800434C0(sp44);
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
    func_ovl13_02_80043040(D_ovl13_02_8004DE3C);
}

void func_ovl13_02_80047EEC(void) {
    f32 y;
    f32 a;
    s32 i;
    s32 done;
    f32 t;

    func_ovl13_02_8004362C(2);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    D_ovl13_02_8004DEE4 = 55.0f;
    D_ovl13_02_8004DEE8 = 0.0f;
    y = D_ovl13_02_8004DED8;
    for (i = 0, done = 0, a = 0.0f; i < 60; i++) {
        t = (f32) i / 60.0f;
        D_ovl13_02_8004DED8 = func_ovl13_02_8004CEF0(a) * (t * 45.0f) + y;
        a = W360(a + 12.0f);
        if (func_ovl13_02_8004C220() <= D_ovl13_02_8004DE3C->unk40->unk14 && done == 0) {
            func_ovl13_02_8004CD48(func_ovl13_02_80045460, NULL, 0, 0, 0x150);
            done = 1;
            func_ovl13_02_80043098(0xE6, D_ovl13_02_8004DE3C);
        }
        func_ovl13_02_8004CD90();
    }
    D_ovl13_02_8004DED8 = y;
}

void func_ovl13_02_80047C60(s32 arg0) {
    f32 da;
    f32 ry;
    f32 step;
    s32 i;
    s32 j;

    func_ovl13_02_8004362C(3);
    da = D_ovl13_02_8004DEF0 / 30.0f;
    D_ovl13_02_8004DEEC *= 0.1f;
        step = 12.0f;
    func_ovl13_02_80043098(0xDE, D_ovl13_02_8004DE3C);
    for (j = 0; j < arg0; j++) {
        D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 = 0.0f;
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
        ry = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
        func_ovl13_02_8004CD68(5);
        for (i = 0; i < 30; i++) {
            D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 += da;
            if (D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 > D_ovl13_02_8004DEF0) {
                D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 -= D_ovl13_02_8004DEF0;
            }
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = ((M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - step) >= 360.0f) ? (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - step) - 360.0f : (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) < step) ? (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - step) + 360.0f : (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - step);
            func_ovl13_02_8004CD90();
        }
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = ry;
        func_ovl13_02_8004CD48(func_ovl13_02_80044AB4, func_ovl13_02_80044CC8(), 0, 0, 0x110);
    }
    D_ovl13_02_8004DEEC *= 10.0f;
}

void func_ovl13_02_8004799C(void) {
    f32 da;
    f32 tgt;
    f32 step;

    func_ovl13_02_8004362C(4);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x0C000000);
    D_ovl13_02_8004DE50[0]->unk50 = 40.0f;
    da = D_ovl13_02_8004DEF0 / 60.0f;
    tgt = 70.0f;
    step = 6.0f;
    while (D_ovl13_02_8004DEE4 != 0.0f) {
        D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 += da;
        if (D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 > D_ovl13_02_8004DEF0) {
            D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 -= D_ovl13_02_8004DEF0;
        }
        if (!(M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) <= tgt + step && tgt - step <= M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4))) {
                M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = ((M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - step) >= 360.0f) ? (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - step) - 360.0f : (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) < step) ? (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - step) + 360.0f : (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - step);
        }
        func_ovl13_02_8004CD90();
    }
    func_ovl13_02_80043098(0xE5, D_ovl13_02_8004DE3C);
    func_ovl13_02_8004CD48(func_ovl13_02_80045460, NULL, 0, 0, 0x150);
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    D_ovl13_02_8004DE80.unk8 = 0.8f;
    D_ovl13_02_8004DE98.unk8 = 0.8f;
    D_ovl13_02_8004DEB0.unk8 = 0.8f;
    D_ovl13_02_8004DE80.unkC = 0.11f;
    D_ovl13_02_8004DE98.unkC = 0.11f;
    D_ovl13_02_8004DEB0.unkC = 0.11f;
    D_ovl13_02_8004DE80.unk10 = 0.999f;
    D_ovl13_02_8004DE98.unk10 = 0.999f;
    D_ovl13_02_8004DEB0.unk10 = 0.999f;
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
}

void func_ovl13_02_80046E10(s32 arg0) {
    f32 a[3];
    f32 v[3];
    s32 i;
    UnkStructA_40 *o;
    f32 d[3];
    f32 p[3];
    f32 ang;
    s32 j;
    f32 save;
    f32 w;
    s32 found;
    s32 pad[34];

    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x08000000);
    func_ovl13_02_8004511C();
    v[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    v[1] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    v[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    func_ovl13_02_800430CC(v, 0x1E, 1);
    func_ovl13_02_8004CA70(&D_ovl13_02_8004D8B0, 0x170, 0);
    v[0] = M2C_FIELD(&D_ovl13_02_8004DFC0, f32 *, 0);
    v[1] = 500.0f;
    v[2] = M2C_FIELD(&D_ovl13_02_8004DFC0, f32 *, 8);
    func_ovl13_02_80044F0C(v, 0x3C, 10.0f);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    v[2] = 0.0f;
    v[1] = 0.0f;
    v[0] = 0.0f;
    a[0] = 0.0f;
    a[1] = 400.0f;
    a[2] = 100.0f;
    func_ovl13_02_8004CB90(a, v);
    v[0] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    v[1] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    v[2] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    func_ovl13_02_800434C0(v);
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
    while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
        func_ovl13_02_8004CD90();
    }
    func_ovl13_02_8004362C(5);
    func_ovl13_02_8004CFC8(0x41E);
    func_ovl13_02_8004CFC0(0x41D);
    func_ovl13_02_8004CFC0(0x41C);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE50[6], 0x30);
    D_ovl13_02_8004DE50[6]->unk38 = 0.0f;
    D_ovl13_02_8004DE50[6]->unk34 = 100.0f;
    if (func_ovl13_02_8004CFD0(0x418) != 0) {
        D_ovl13_02_8004DE50[6]->unk38 *= 0.6f;
        D_ovl13_02_8004DE50[6]->unk34 *= 0.6f;
    }
    for (i = 0; i < arg0; i++) {
        if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) >= 360.0f) {
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) -= 360.0f;
        } else {
            if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) < 0.0f) {
                w = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) + 360.0f;
            } else {
                w = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0);
            }
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) = w;
        }
        func_ovl13_02_800430CC((f32 *) &D_ovl13_02_8004DC90, 0xA, 0);
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
        D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 = 0.0f;
        D_ovl13_02_8004DEF4 = 0.0f;
        ang = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
        save = D_ovl13_02_8004DE50[0]->unk50;
        D_ovl13_02_8004DE80.unkC = 0.5f;
        D_ovl13_02_8004DE80.unk8 = 0.5f;
        D_ovl13_02_8004DE80.unk0 = 2;
        D_ovl13_02_8004DE98.unkC = 0.5f;
        D_ovl13_02_8004DE98.unk8 = 0.5f;
        D_ovl13_02_8004DE98.unk0 = 2;
        D_ovl13_02_8004DEB0.unkC = 0.5f;
        D_ovl13_02_8004DEB0.unk8 = 0.5f;
        D_ovl13_02_8004DEB0.unk0 = 2;
        D_ovl13_02_8004DEB0.unk10 = 0.999f;
        D_ovl13_02_8004DE98.unk10 = 0.999f;
        D_ovl13_02_8004DE80.unk10 = 0.999f;
        func_ovl13_02_8004D2D0(0xDE);
        while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = ang - func_ovl13_02_8004CEF0((D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 / D_ovl13_02_8004DEF0) * 180.0f) * 45.0f;
            found = func_ovl13_02_800461E0();
            if (found != 0) {
                func_ovl13_02_8004CFC8(0x41D);
                func_ovl13_02_8004CFC8(0x41C);
                func_ovl13_02_8004CFC0(0x419);
                func_ovl13_02_800467D8(found);
                i = arg0;
                break;
            }
            func_ovl13_02_8004CD90();
        }
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = ang;
        if (found == 0) {
            p[0] = D_ovl13_02_8004DE50[7]->unk40->unk10;
            p[1] = D_ovl13_02_8004DE50[7]->unk40->unk14;
            p[2] = D_ovl13_02_8004DE50[7]->unk40->unk18;
            func_ovl13_02_8004CB88(p, (f32 *) &D_ovl13_02_8004DC90, d);
            if (d[2] <= 700.0f) {
                d[2] = 700.0f;
            }
            if (d[2] > 1400.0f) {
                d[2] = 1400.0f;
            }
            d[2] -= 700.0f;
            d[2] *= 0.01f;
            switch ((u32) d[2]) {
            case 0:
                func_ovl13_02_80046D7C(0xA, 20.0f);
                D_ovl13_02_8004DEB0.unk10 = 0.99f;
                D_ovl13_02_8004DEB0.unk0 = 0x100002;
                D_ovl13_02_8004DE98.unk10 = 0.99f;
                D_ovl13_02_8004DE98.unk0 = 0x100002;
                D_ovl13_02_8004DE80.unk10 = 0.99f;
                D_ovl13_02_8004DE80.unk0 = 0x100002;
                D_ovl13_02_8004DEB0.unk8 = 5.0f;
                D_ovl13_02_8004DE98.unk8 = 5.0f;
                D_ovl13_02_8004DE80.unk8 = 5.0f;
                D_ovl13_02_8004DE80.unkC = 0.4f;
                D_ovl13_02_8004DE98.unkC = 0.4f;
                D_ovl13_02_8004DEB0.unkC = 0.4f;
                break;
            case 1:
                func_ovl13_02_80046D7C(0xA, 0.0f);
                D_ovl13_02_8004DE80.unk0 = 0x100002;
                D_ovl13_02_8004DE80.unkC = 0.5f;
                D_ovl13_02_8004DE80.unk10 = 0.99f;
                D_ovl13_02_8004DE98.unk0 = 0x100002;
                D_ovl13_02_8004DE98.unkC = 0.5f;
                D_ovl13_02_8004DE98.unk10 = 0.99f;
                D_ovl13_02_8004DEB0.unk0 = 0x100002;
                D_ovl13_02_8004DEB0.unkC = 0.5f;
                D_ovl13_02_8004DEB0.unk10 = 0.99f;
                D_ovl13_02_8004DE80.unk8 = 4.0f;
                D_ovl13_02_8004DE98.unk8 = 4.0f;
                D_ovl13_02_8004DEB0.unk8 = 4.0f;
                break;
            case 2:
                func_ovl13_02_80046D7C(0xA, -10.0f);
                D_ovl13_02_8004DE80.unk0 = 0x100002;
                D_ovl13_02_8004DE80.unkC = 0.5f;
                D_ovl13_02_8004DE80.unk10 = 0.99f;
                D_ovl13_02_8004DE98.unk0 = 0x100002;
                D_ovl13_02_8004DE98.unkC = 0.5f;
                D_ovl13_02_8004DE98.unk10 = 0.99f;
                D_ovl13_02_8004DEB0.unk0 = 0x100002;
                D_ovl13_02_8004DEB0.unkC = 0.5f;
                D_ovl13_02_8004DEB0.unk10 = 0.99f;
                D_ovl13_02_8004DE80.unk8 = 3.0f;
                D_ovl13_02_8004DE98.unk8 = 3.0f;
                D_ovl13_02_8004DEB0.unk8 = 3.0f;
                break;
            case 3:
                func_ovl13_02_80046D7C(0xA, -30.0f);
                D_ovl13_02_8004DEB0.unk10 = 0.99f;
                D_ovl13_02_8004DEB0.unk0 = 0x100002;
                D_ovl13_02_8004DE98.unk10 = 0.99f;
                D_ovl13_02_8004DE98.unk0 = 0x100002;
                D_ovl13_02_8004DE80.unk10 = 0.99f;
                D_ovl13_02_8004DE80.unk0 = 0x100002;
                D_ovl13_02_8004DEB0.unk8 = 2.0f;
                D_ovl13_02_8004DE98.unk8 = 2.0f;
                D_ovl13_02_8004DE80.unk8 = 2.0f;
                D_ovl13_02_8004DE80.unkC = 0.6f;
                D_ovl13_02_8004DE98.unkC = 0.6f;
                D_ovl13_02_8004DEB0.unkC = 0.6f;
                break;
            case 4:
                func_ovl13_02_80046D7C(0xA, -40.0f);
                D_ovl13_02_8004DEB0.unk10 = 0.99f;
                D_ovl13_02_8004DEB0.unk0 = 0x100002;
                D_ovl13_02_8004DE98.unk10 = 0.99f;
                D_ovl13_02_8004DE98.unk0 = 0x100002;
                D_ovl13_02_8004DE80.unk10 = 0.99f;
                D_ovl13_02_8004DE80.unk0 = 0x100002;
                D_ovl13_02_8004DEB0.unk8 = 1.0f;
                D_ovl13_02_8004DE98.unk8 = 1.0f;
                D_ovl13_02_8004DE80.unk8 = 1.0f;
                D_ovl13_02_8004DE80.unkC = 0.6f;
                D_ovl13_02_8004DE98.unkC = 0.6f;
                D_ovl13_02_8004DEB0.unkC = 0.6f;
                break;
            default:
                func_ovl13_02_80046D7C(0xA, -50.0f);
                D_ovl13_02_8004DEB0.unk10 = 0.99f;
                D_ovl13_02_8004DEB0.unk0 = 0x100002;
                D_ovl13_02_8004DE98.unk10 = 0.99f;
                D_ovl13_02_8004DE98.unk0 = 0x100002;
                D_ovl13_02_8004DE80.unk10 = 0.99f;
                D_ovl13_02_8004DE80.unk0 = 0x100002;
                D_ovl13_02_8004DE80.unkC = 0.93f;
                D_ovl13_02_8004DE98.unkC = 0.93f;
                D_ovl13_02_8004DEB0.unkC = 0.93f;
                D_ovl13_02_8004DE80.unk8 = 1.0f;
                D_ovl13_02_8004DE98.unk8 = 1.0f;
                D_ovl13_02_8004DEB0.unk8 = 1.0f;
                break;
            }
            D_ovl13_02_8004DE50[6]->unk5C = 0.0f;
            for (j = 0; j < 20; j++) {
                if (((o = D_ovl13_02_8004DE50[6]->unk40)->unk14 <= (D_ovl13_02_8004DD14 + 50.0f)) && ((func_ovl13_02_8004C268((s32) (o->unk10 * 0.01f), 1, (s32) (o->unk18 * 0.01f)) & 0xF) == 1)) {
                    func_ovl13_02_8004CB20(10.0f, 10.0f, 10.0f);
                    func_ovl13_02_8004CB10(0x1E);
                    func_ovl13_02_80043098(0xDF, D_ovl13_02_8004DE50[6]);
                    break;
                }
                D_ovl13_02_8004DE50[6]->unk5C = D_ovl13_02_8004DE50[6]->unk40->unk14;
                func_ovl13_02_8004CD90();
            }
            if (func_ovl13_02_8004CFD0(0x418) != 0) {
                func_ovl13_02_8004CD68(0x1E);
            } else {
                func_ovl13_02_8004CD68(0xA);
            }
            D_ovl13_02_8004DE50[0]->unk50 = save;
        }
        D_ovl13_02_8004DE80.unk0 = 2;
        D_ovl13_02_8004DE98.unk0 = 2;
        D_ovl13_02_8004DEB0.unk0 = 2;
        D_ovl13_02_8004DEB0.unk8 = 0.8f;
        D_ovl13_02_8004DE98.unk8 = 0.8f;
        D_ovl13_02_8004DE80.unk8 = 0.8f;
        D_ovl13_02_8004DEB0.unkC = 0.11f;
        D_ovl13_02_8004DE98.unkC = 0.11f;
        D_ovl13_02_8004DE80.unkC = 0.11f;
        D_ovl13_02_8004DE80.unk10 = 0.999f;
        D_ovl13_02_8004DE98.unk10 = 0.999f;
        D_ovl13_02_8004DEB0.unk10 = 0.999f;
    }
    if (D_ovl13_02_8004DE24 > 0) {
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
        func_ovl13_02_8004CFC8(0x41D);
        func_ovl13_02_8004CFC8(0x41C);
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE50[6], 0x30);
        D_ovl13_02_8004DE50[6]->unk38 = 0.0f;
        D_ovl13_02_8004DE50[6]->unk34 = 150.0f;
        func_ovl13_02_8004CFC0(0x41E);
        func_ovl13_02_8004362C(0);
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x0C000000);
        func_ovl13_02_8004511C();
        func_ovl13_02_8004CA70(&D_ovl13_02_8004D8F4, 0x170, 0);
        v[0] = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0);
        v[1] = 500.0f;
        v[2] = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8);
        func_ovl13_02_80044F0C(v, 0x3C, 20.0f);
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
        v[2] = 0.0f;
        v[1] = 0.0f;
        v[0] = 0.0f;
        a[0] = 0.0f;
        a[1] = 30.0f;
        a[2] = 100.0f;
        func_ovl13_02_8004CB90(a, v);
        v[0] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
        v[1] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
        v[2] += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
        func_ovl13_02_800434C0(v);
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
        while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
            func_ovl13_02_8004CD90();
        }
    }
}

void func_ovl13_02_80046D7C(s32 arg0, f32 arg1) {
    f32 temp_fs0;
    s32 var_s0;

    var_s0 = 0;
    temp_fs0 = (arg1 - D_ovl13_02_8004DE50[0]->unk50) / (f32) arg0;
    if (arg0 > 0) {
        do {
            D_ovl13_02_8004DE50[0]->unk50 += temp_fs0;
            func_ovl13_02_8004CD90();
            var_s0 += 1;
        } while (var_s0 != arg0);
    }
}

void func_ovl13_02_80046B34(s32 arg0) {
    f32 k;
    f32 da;
    f32 rx;
    f32 a;

    func_ovl13_02_8004362C(6);
    a = 0.0f;
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    da = 2.0f * (360.0f / D_ovl13_02_8004DEF0);
    D_ovl13_02_8004DE80.unk8 = 0.8f;
    D_ovl13_02_8004DE98.unk8 = 0.8f;
    D_ovl13_02_8004DEB0.unk8 = 0.8f;
    D_ovl13_02_8004DE80.unkC = 0.11f;
    D_ovl13_02_8004DE98.unkC = 0.11f;
    D_ovl13_02_8004DEB0.unkC = 0.11f;
    D_ovl13_02_8004DE80.unk10 = 0.99999f;
    D_ovl13_02_8004DE98.unk10 = 0.99999f;
    D_ovl13_02_8004DEB0.unk10 = 0.99999f;
    rx = D_ovl13_02_8004DED8;
    func_ovl13_02_8004D2D0(0xDD);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
        k = 1.0f - (D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 / D_ovl13_02_8004DEF0);
        k *= 30.0f;
        D_ovl13_02_8004DED8 = func_ovl13_02_8004CEF0(a) * k + rx;
        a = W360(a + da);
        func_ovl13_02_8004CD90();
    }
    D_ovl13_02_8004DE24 -= arg0;
    D_ovl13_02_8004DED8 = rx;
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
}

void func_ovl13_02_800467D8(s32 arg0) {
    f32 k;
    f32 da;
    f32 a;
    f32 scale;
    s32 n;
    f32 pos[3];
    s32 i;

    func_ovl13_02_8004362C(7);
    a = 0.0f;
    da = 2.0f * (360.0f / D_ovl13_02_8004DEF0);
    scale = D_ovl13_02_8004DE3C->unk40->unk28;
    for (i = 0, n = 0; i < 120; i++) {
        pos[0] = D_ovl13_02_8004DE70->unk40->unk10;
        pos[1] = D_ovl13_02_8004DE70->unk40->unk14 + 400.0f;
        pos[2] = D_ovl13_02_8004DE70->unk40->unk18 + 400.0f;
        pos[0] += D_ovl13_02_8004D938[func_ovl13_02_8004CF08(5)];
        pos[1] += D_ovl13_02_8004D938[func_ovl13_02_8004CF08(5)];
        if (n >= 17) {
            func_ovl13_02_8004D1A0(0xE, pos, 0);
            n = 0;
        }
        func_ovl13_02_8004CD90();
        n++;
    }
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    func_ovl13_02_8004CD68((s32) (D_ovl13_02_8004DEF0 * 0.3f));
    func_ovl13_02_80043098(0xB, D_ovl13_02_8004DE3C);
    func_ovl13_02_80043098(0xE3, D_ovl13_02_8004DE3C);
    func_ovl13_02_8004D2D0(0xDD);
    while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
        k = 1.0f - (D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 / D_ovl13_02_8004DEF0);
        k *= 1.5f;
        D_ovl13_02_8004DE3C->unk40->unk28 = func_ovl13_02_8004CEF0(a) * k + scale;
        a = W360(a + da);
        func_ovl13_02_8004CD90();
    }
    D_ovl13_02_8004DE24 -= arg0;
    D_ovl13_02_8004DE3C->unk40->unk28 = scale;
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
}

void func_ovl13_02_8004640C(void) {
    s32 i;
    f32 y;
    f32 da;
    f32 x;
    f32 z;
    f32 r;
    f32 ry;
    f32 a;
    f32 rad;
    s32 pad0;
    f32 dr;
    f32 pos[3];
    s32 pad1[10];

    func_ovl13_02_8004D2E8();
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
    y = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    D_ovl13_02_8004DE80.unkC = 0.5f;
    D_ovl13_02_8004DE98.unkC = 0.5f;
    D_ovl13_02_8004DEB0.unkC = 0.5f;
    D_ovl13_02_8004DE80.unk8 = 0.1f;
    D_ovl13_02_8004DE98.unk8 = 0.1f;
    D_ovl13_02_8004DEB0.unk8 = 0.1f;
    D_ovl13_02_8004DE80.unk10 = 0.9f;
    D_ovl13_02_8004DE98.unk10 = 0.9f;
    D_ovl13_02_8004DEB0.unk10 = 0.9f;
    r = 0.0f;
    func_ovl13_02_8004D2D0(0xE7);
    for (i = 0; i < 20; i++) {
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = y - r;
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) += -10.0f;
        r += 4.0f;
        func_ovl13_02_8004CD90();
    }
    func_ovl13_02_8004CFC8(0x41F);
    func_ovl13_02_8004631C();
    func_ovl13_02_8004362C(8);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    da = (360.0f / D_ovl13_02_8004DEF0) * 1.5f;
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    D_ovl13_02_8004DE80.unk8 = 0.3f;
    D_ovl13_02_8004DE98.unk8 = 0.3f;
    D_ovl13_02_8004DEB0.unk8 = 0.3f;
    dr = 80.0f / D_ovl13_02_8004DEF0;
    D_ovl13_02_8004DE80.unkC = 0.1f;
    D_ovl13_02_8004DE98.unkC = 0.1f;
    D_ovl13_02_8004DEB0.unkC = 0.1f;
    D_ovl13_02_8004DE80.unk10 = 0.9f;
    D_ovl13_02_8004DE98.unk10 = 0.9f;
    D_ovl13_02_8004DEB0.unk10 = 0.9f;
    ry = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
    x = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0);
    z = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 8);
    a = 0.0f;
    r = 0.0f;
    while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
        rad = 1.0f - D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 / D_ovl13_02_8004DEF0;
        rad *= 15.0f;
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) += -10.0f;
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = ry + r;
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) = func_ovl13_02_8004CEF0(a) * rad + x;
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 8) = func_ovl13_02_8004CEF0(a) * rad + z;
        a = W360(a + da);
        r = W360(r + dr);
        func_ovl13_02_8004CD90();
    }
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
    pos[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    pos[1] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    pos[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 100.0f;
    func_ovl13_02_800430CC(pos, 0x3C, 1);
}

void func_ovl13_02_800463BC(void) {
    func_ovl13_02_8004C908(D_ovl13_02_8004DE3C->unk40, 0x17A, 0, 0);
    func_ovl13_02_8004C908(D_ovl13_02_8004DE3C->unk40, 0x17A, 1, 1);
}

void func_ovl13_02_8004636C(void) {
    func_ovl13_02_8004C908(D_ovl13_02_8004DE3C->unk40, 0x17B, 2, 0);
    func_ovl13_02_8004C908(D_ovl13_02_8004DE3C->unk40, 0x17B, 3, 1);
}

void func_ovl13_02_8004631C(void) {
    func_ovl13_02_8004C908(D_ovl13_02_8004DE3C->unk40, 0x17B, 2, 2);
    func_ovl13_02_8004C908(D_ovl13_02_8004DE3C->unk40, 0x17B, 3, 3);
}

void func_ovl13_02_80046268(void) {
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[6], UnkStructA_40 **, 0x40), 0x181, 0, 0);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[6], UnkStructA_40 **, 0x40), 0x181, 1, 1);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[5], UnkStructA_40 **, 0x40), 0x17D, 0, 0);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[5], UnkStructA_40 **, 0x40), 0x17D, 1, 1);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[4], UnkStructA_40 **, 0x40), 0x17F, 0, 0);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[4], UnkStructA_40 **, 0x40), 0x17F, 1, 1);
}

s32 func_ovl13_02_800461E0(void) {
    s32 var_v1;
    UnkStructA *sp28;
    s32 sp2C;
    UnkStructA *temp_v0;
    f32 sp1C;

    temp_v0 = func_ovl13_02_8004CC80(D_ovl13_02_8004DE70, 2);
    sp28 = temp_v0;
    if (temp_v0 == NULL) {
        return 0;
    }
    var_v1 = 2;
    if (temp_v0->unk8 & 0x2000) {
        var_v1 = 4;
    }
    sp2C = var_v1;
    if (func_ovl13_02_8004CFD0(0x419) == 0) {
        func_ovl13_02_8004CCC8(sp28, &sp1C);
        func_ovl13_02_8004CF78(&sp1C);
    }
    func_ovl13_02_8004D1C0(sp28);
    return sp2C;
}

void func_ovl13_02_800460C0(void) {
    UnkStructA *temp_v0;
    f32 var_fs0;
    f32 var_fs1;
    s32 var_s0;
    s32 var_s1;
    void *temp_s0;

    temp_s0 = func_ovl13_02_8004CD70();
    temp_v0 = func_ovl13_02_8004CC20(0x183, 0x11080000, 0xD0, NULL);
    temp_v0->unk40->unk10 = M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x40), f32 *, 0x10);
    temp_v0->unk40->unk14 = M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x40), f32 *, 0x14);
    temp_v0->unk40->unk18 = M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x40), f32 *, 0x18);
    if (M2C_FIELD(temp_s0, s32 *, 0x28) == -1) {
        var_fs0 = 3.0f;
        var_fs1 = 8.0f;
        var_s1 = 0x28;
    } else {
        var_fs0 = 2.0f;
        var_fs1 = 4.0f;
        var_s1 = 0x14;
    }
    var_s0 = 0;
    if (var_s1 > 0) {
        do {
            func_ovl13_02_8004564C(temp_v0, var_s0, var_s1, var_fs0, var_fs1);
            func_ovl13_02_8004CD90();
            var_s0 += 1;
        } while (var_s0 != var_s1);
    }
    func_ovl13_02_8004CC10(temp_v0);
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_80045AB8(void) {
    s32 k;
    void *tog;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 n;
    f32 a[3];
    f32 b[3];
    f32 c[3];
    s32 r0;
    s32 said;
    s32 cnt;
    s32 lim;

    k = 0;
    tog = NULL;
    t1 = 0;
    t2 = 0;
    t3 = 0;
    said = 0;
    cnt = lim = func_ovl13_02_8004CF08(0x3C) + 0x1E;
    for (;;) {
        if (func_ovl13_02_8004CFD0(0x41A) != 0) {
            func_ovl13_02_80044E64(&D_ovl13_02_8004DEE4, &D_ovl13_02_8004DEE8, &D_ovl13_02_8004DEEC);
        }
        D_ovl13_02_8004DE3C->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
        D_ovl13_02_8004DE3C->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
        D_ovl13_02_8004DE3C->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
        D_ovl13_02_8004DE3C->unk40->unk1C = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
        D_ovl13_02_8004DE3C->unk40->unk20 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0);
        D_ovl13_02_8004DE3C->unk40->unk24 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 8);
        D_ovl13_02_8004DE48->unk40->unk10 = D_ovl13_02_8004DE3C->unk40->unk10;
        D_ovl13_02_8004DE48->unk40->unk14 = func_ovl13_02_8004C220() + 50.0f;
        D_ovl13_02_8004DE48->unk40->unk14 = func_ovl13_02_8004C220();
        D_ovl13_02_8004DE48->unk40->unk18 = D_ovl13_02_8004DE3C->unk40->unk18;
        if ((++k >= 6) && (func_ovl13_02_8004CFD0(0x41F) != 0)) {
            func_ovl13_02_8004CD48(func_ovl13_02_80045724, tog, 0, 0, 0x150);
            k = 0;
            tog = (void *) ((s32) tog ^ 1);
        }
        if (func_ovl13_02_8004CFD0(0x41E) != 0) {
            func_ovl13_02_800459D0(&D_ovl13_02_8004DEF0, &D_ovl13_02_8004DEF4, &D_ovl13_02_8004DEC8, &D_ovl13_02_8004DED8, D_ovl13_02_8004DEFC, D_ovl13_02_8004DF04, D_ovl13_02_8004DF0C, D_ovl13_02_8004DF00, D_ovl13_02_8004DF08, D_ovl13_02_8004DF10);
        }
        D_ovl13_02_8004DEF4 += D_ovl13_02_8004DEF8;
        if (D_ovl13_02_8004DEF0 <= D_ovl13_02_8004DEF4) {
            D_ovl13_02_8004DEF4 -= D_ovl13_02_8004DEF0;
        }
        if ((func_ovl13_02_8004CFD0(0x41D) != 0) && (t1 == 0) && (D_ovl13_02_8004DE24 > 0)) {
            D_ovl13_02_8004DE34 = func_ovl13_02_800458D8(D_ovl13_02_8004DE40);
            D_ovl13_02_8004DE34 |= func_ovl13_02_800458D8(D_ovl13_02_8004DE44);
            if (func_ovl13_02_8004CFD0(0x41C) != 0) {
                D_ovl13_02_8004DE24 -= D_ovl13_02_8004DE34;
                if (D_ovl13_02_8004DE24 < 0) {
                    D_ovl13_02_8004DE24 = 0;
                }
                t1 = 0x78;
                if ((func_ovl13_02_8004CFD0(0x439) != 0) && (D_ovl13_02_8004DE24 <= 0)) {
                    D_ovl13_02_8004DE24 = 1;
                }
                D_ovl13_02_8004DE34 = 0;
            }
        }
        if (t1 != 0) {
            t1 -= 1;
        }
        n = func_ovl13_02_800458D8(D_ovl13_02_8004DE50[6]);
        if ((n != 0) && (D_ovl13_02_8004DE2C > 0) && (t2 == 0)) {
            D_ovl13_02_8004DE2C -= n;
            if (D_ovl13_02_8004DE2C < 0) {
                D_ovl13_02_8004DE2C = 0;
            }
            if (D_ovl13_02_8004DE2C <= 0) {
                func_ovl13_02_8004591C();
                func_ovl13_02_8004CC00(D_ovl13_02_8004DE50[6], 0x3FFFF);
                func_ovl13_02_8004CCC8(D_ovl13_02_8004DE50[6], &c[0]);
                func_ovl13_02_8004CF78(&c[0]);
            }
            t2 = 0x78;
        }
        if (t2 != 0) {
            if (t2 >= 0x6F) {
                a[0] = D_ovl13_02_8004DE50[6]->unk40->unk10;
                a[1] = D_ovl13_02_8004DE50[6]->unk40->unk14;
                a[2] = D_ovl13_02_8004DE50[6]->unk40->unk18;
                func_ovl13_02_8004D1A0(8, &a[0], 0);
            }
            t2 -= 1;
        }
        n = func_ovl13_02_800458D8(D_ovl13_02_8004DE4C);
        if ((n != 0) && (D_ovl13_02_8004DE28 > 0) && (t3 == 0)) {
            D_ovl13_02_8004DE28 -= n;
            if (D_ovl13_02_8004DE28 < 0) {
                D_ovl13_02_8004DE28 = 0;
            }
            if (D_ovl13_02_8004DE28 <= 0) {
                func_ovl13_02_80045888();
                func_ovl13_02_8004CC00(D_ovl13_02_8004DE4C, 0x8010);
                func_ovl13_02_8004CCC8(D_ovl13_02_8004DE4C, &c[0]);
                func_ovl13_02_8004CF78(&c[0]);
            }
            t3 = 0x78;
        }
        if (t3 != 0) {
            if (t3 >= 0x6F) {
                b[0] = D_ovl13_02_8004DE4C->unk40->unk10;
                b[1] = D_ovl13_02_8004DE4C->unk40->unk14;
                b[2] = D_ovl13_02_8004DE4C->unk40->unk18;
                func_ovl13_02_8004D1A0(8, &b[0], 0);
            }
            t3 -= 1;
        }
        if ((func_ovl13_02_800445C8() != 0) && (said == 0)) {
            func_ovl13_02_8004CF78(&D_ovl13_02_8004DC90.x);
            said = 1;
        }
        r0 = (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + 500.0f) <= func_ovl13_02_8004C220() ? 1 : 0;
        if ((r0 != 0) && (D_ovl13_02_8004DE24 != 0)) {
            if (++cnt > lim) {
                cnt = 0;
                lim = func_ovl13_02_8004CF08(0x3C) + 0x1E;
                func_ovl13_02_80043098(0xF0, D_ovl13_02_8004DE3C);
            }
        }
        func_ovl13_02_8004CD90();
    }
}

void func_ovl13_02_800459D0(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    f32 t;

    t = (*arg1 / *arg0) * 360.0f;
    D_ovl13_02_8004DE3C->unk40->unk10 = arg2[0] + (func_ovl13_02_8004CEF0(t * arg4) * arg7);
    D_ovl13_02_8004DE3C->unk40->unk14 = arg2[1] + (func_ovl13_02_8004CEF0(t * arg5) * arg8);
    D_ovl13_02_8004DE3C->unk40->unk20 = *arg3 + (func_ovl13_02_8004CEF0(t * arg6) * arg9);
}

void func_ovl13_02_8004591C(void) {
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[6], UnkStructA_40 **, 0x40), 0x181, 0, 2);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[6], UnkStructA_40 **, 0x40), 0x181, 1, 3);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[5], UnkStructA_40 **, 0x40), 0x17D, 0, 2);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[5], UnkStructA_40 **, 0x40), 0x17D, 1, 3);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[4], UnkStructA_40 **, 0x40), 0x17F, 0, 2);
    func_ovl13_02_8004C908(M2C_FIELD(D_ovl13_02_8004DE50[4], UnkStructA_40 **, 0x40), 0x17F, 1, 3);
}

s32 func_ovl13_02_800458D8(UnkStructA *arg0) {
    s32 flags;
    s32 r;

    flags = arg0->unk10;
    r = flags & 0x40;
    if (r == 0) {
        return r;
    }
    /* the count lives in arg0's register: the parameter is reused */
    arg0 = (UnkStructA *) 1;
    if (flags & 0x2000) {
        arg0 = (UnkStructA *) 2;
    }
    if (flags & 0x4000) {
        arg0 = (UnkStructA *) ((s32) arg0 + 1);
    }
    return (s32) arg0;
}

void func_ovl13_02_80045888(void) {
    func_ovl13_02_8004C908(D_ovl13_02_8004DE3C->unk40, 0x17A, 0, 2);
    func_ovl13_02_8004C908(D_ovl13_02_8004DE3C->unk40, 0x17A, 1, 3);
}

void func_ovl13_02_80045724(void) {
    UnkStructA *temp_v0;
    s32 var_s1;
    void *temp_s5;

    temp_s5 = func_ovl13_02_8004CD70();
    temp_v0 = func_ovl13_02_8004CC20(0x183, 0x11380000, 0xD0, D_ovl13_02_8004DE48);
    if (temp_s5 != NULL) {
        temp_v0->unk4C = 1.0f;
    } else {
        temp_v0->unk4C = -1.0f;
    }
    temp_v0->unk50 = 90.0f;
    temp_v0->unk54 = 825.0f;
    for (var_s1 = 0; var_s1 < 0x1E; var_s1++) {
        func_ovl13_02_8004564C(temp_v0, var_s1, 0x1E, D_ovl13_02_8004DE74, D_ovl13_02_8004DE78);
        if (temp_s5 != NULL) {
            temp_v0->unk4C += 2.0f;
        } else {
            temp_v0->unk4C -= 2.0f;
        }
        temp_v0->unk54 -= 4.0f;
        func_ovl13_02_8004CD90();
    }
    func_ovl13_02_8004CC10(temp_v0);
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_8004564C(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl13_02_8004CEF0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl13_02_8004CEF0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl13_02_80045460(void) {
    s32 i;
    UnkStructA *objs[24];
    UnkStructA *obj;
    Vec3f a;
    Vec3f pos;

    for (i = 0; i < 24; i++) {
        objs[i] = func_ovl13_02_8004CC20(-1, 0, 0xD0, NULL);
    }
    a.y = 0.0f;
    a.x = 0.0f;
    a.z = 800.0f;
    for (i = 0; i < 24; i++) {
        obj = objs[i];
        pos.x = 0.0f;
        pos.y = 0.0f;
        pos.z = 0.0f;
        func_ovl13_02_8004CB90(&a.x, &pos.x);
        obj->unk40->unk10 = D_ovl13_02_8004DC90.x + pos.x;
        obj->unk40->unk14 = D_ovl13_02_8004DC90.y + pos.y;
        obj->unk40->unk18 = D_ovl13_02_8004DC90.z + pos.z;
        obj->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0) + pos.x;
        obj->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + pos.y;
        obj->unk40->unk14 = func_ovl13_02_8004C220();
        obj->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + pos.z;
        func_ovl13_02_8004CD48(func_ovl13_02_800460C0, obj, 0, 0, 0x150);
        a.x += 15.0f;
    }
    func_ovl13_02_8004CD90();
    for (i = 0; i < 24; i++) {
        func_ovl13_02_8004CC10(objs[i]);
    }
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_8004521C(void) {
    s32 pad[2];
    UnkStructA *objs[24];
    s32 i;
    Vec3f a;
    Vec3f pos[24];
    s32 n;
    s32 k;
    s32 wait;
    UnkStructA *obj;

    n = (s32) func_ovl13_02_8004CD70();
    a.y = 0.0f;
    a.x = 0.0f;
    a.z = 800.0f;
    for (i = 0; i < 24; i++) {
        objs[i] = func_ovl13_02_8004CC20(0, 0, 0xD0, NULL);
        pos[i].z = 0.0f;
        pos[i].y = 0.0f;
        pos[i].x = 0.0f;
        func_ovl13_02_8004CB90(&a.x, &pos[i].x);
        a.x += 15.0f;
    }
    for (i = 0, k = 0, wait = 3; i < n; i++) {
        wait++;
        if (wait >= 4) {
            obj = objs[k];
            obj->unk40->unk10 = pos[k].x + D_ovl13_02_8004DC90.x;
            obj->unk40->unk14 = pos[k].y + D_ovl13_02_8004DC90.y;
            obj->unk40->unk18 = pos[k].z + D_ovl13_02_8004DC90.z;
            obj->unk40->unk10 = pos[k].x + ((Vec3f *) &D_ovl13_02_8004DEC8)->x;
            obj->unk40->unk14 = pos[k].y + ((Vec3f *) &D_ovl13_02_8004DEC8)->y;
            obj->unk40->unk18 = pos[k].z + ((Vec3f *) &D_ovl13_02_8004DEC8)->z;
            func_ovl13_02_8004CD48(func_ovl13_02_800460C0, obj, 0, 0, 0x150);
            k = func_ovl13_02_8004CF08(0x17);
            wait = 0;
        }
        func_ovl13_02_8004CD90();
    }
    for (i = 0; i < 24; i++) {
        func_ovl13_02_8004CC10(objs[i]);
    }
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_8004511C(void) {
    f32 temp_fs0;
    f32 sp40[3];
    s32 var_s0;

    sp40[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp40[1] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + -500.0f;
    sp40[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    func_ovl13_02_8004CD48(func_ovl13_02_8004521C, (void *)0x43, 0, 0, 0x150);
    func_ovl13_02_800430CC(&sp40[0], 0x30, 1);
    func_ovl13_02_8004CFC8(0x41F);
    temp_fs0 = (500.0f - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4)) / 64;
    func_ovl13_02_80043098(0xE5, D_ovl13_02_8004DE3C);
    for (var_s0 = 0; var_s0 < 0x40; var_s0++) {
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + temp_fs0);
        func_ovl13_02_8004CD90();
    }
}

void func_ovl13_02_80044F0C(f32 *arg0, s32 arg1, f32 arg2) {
    s32 i;
    f32 d;
    f32 dz;
    f32 ang[3];
    f32 dy;
    f32 dx;

    dx = (arg0[0] - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0)) / (f32) arg1;
    dy = (arg0[1] - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4)) / (f32) arg1;
    dz = (arg0[2] - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8)) / (f32) arg1;
    func_ovl13_02_8004CB88(&D_ovl13_02_8004DEC8, arg0, ang);
    ang[1] = ((ang[1] - 90.0f) >= 360.0f) ? (ang[1] - 90.0f) - 360.0f : (ang[1] < 90.0f) ? (ang[1] - 90.0f) + 360.0f : (ang[1] - 90.0f);
    ang[2] /= (f32) arg1;
    d = ang[2] / arg2;
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
    for (i = 0; i < arg1; i++) {
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0) += dx;
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) += dy;
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) += dz;
        D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 += d;
        if (D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 > D_ovl13_02_8004DEF0) {
            D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 -= D_ovl13_02_8004DEF0;
        }
        func_ovl13_02_8004CD90();
    }
}

void func_ovl13_02_80044E64(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 temp_fv0;

    temp_fv0 = func_ovl13_02_8004C220();
    if (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) - *arg1 + *arg0 <= temp_fv0) {
        *arg1 = 0.0f;
        *arg0 = 0.0f;
        D_ovl13_02_8004DECC = temp_fv0;
        return;
    }
    M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) += *arg0;
    M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) -= *arg1;
    *arg1 += *arg2;
}

s32 func_ovl13_02_80044CC8(void) {
    s32 i;
    f32 min;
    s32 found;
    f32 d;

    min = 20000.0f;
    for (i = 0; i < 9; i++) {
        d = D_ovl13_02_8004DC90.x - D_ovl13_02_8004DDB8[i].x;
        if (d < 0.0f) {
            d *= -1.0f;
        }
        if (d < min) {
            min = d;
            found = i;
        }
    }
    return found;
}

void func_ovl13_02_80044AB4(void) {
    s32 idx;
    UnkStructA *obj;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    idx = (s32) func_ovl13_02_8004CD70();
    obj = func_ovl13_02_8004CC20(0x184, 0x01000100, 0x50, NULL);
    obj->unk30 = 4;
    obj->unk34 = 6.0f;
    obj->unk38 = 90.0f;
    obj->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 0);
    obj->unk40->unk14 = D_ovl13_02_8004DECC - 700.0f;
    obj->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 8);
    obj->unk40->unk20 = 180.0f;
    dx = D_ovl13_02_8004DDB8[idx].x - M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 0);
    dy = func_ovl13_02_8004C220() - obj->unk40->unk14;
    dz = D_ovl13_02_8004DDB8[idx].z - M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 8);
    dx /= 120.0f;
    dy /= 120.0f;
    dz /= 120.0f;
    func_ovl13_02_80043098(0xE1, obj);
    for (i = 0; i < 180; i++) {
        obj->unk40->unk10 += dx;
        obj->unk40->unk14 += dy;
        obj->unk40->unk18 += dz;
        obj->unk40->unk2C += 0.041666668f;
        if (i == 119) {
            func_ovl13_02_80044990(idx);
        }
        func_ovl13_02_8004CD90();
    }
    func_ovl13_02_8004CC10(obj);
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_80044990(s32 arg0) {
    s32 step;
    s32 i;
    s32 said;
    s32 j;

    if (D_ovl13_02_8004DC90.x <= D_ovl13_02_8004DDB8[arg0].x) {
        step = 1;
        j = arg0 + 1;
    } else {
        step = -1;
        j = arg0;
    }
    said = 0;
    for (i = j; i < 10 && i >= 0; i += step) {
        if (D_ovl13_02_8004DD90[i] == 0) {
            if (said == 0) {
                func_ovl13_02_80043098(0xE8, D_ovl13_02_8004DD68[i]);
                said = 1;
            }
            func_ovl13_02_8004CD48(func_ovl13_02_8004A8E0, (void *) i, 0, 0, 0x150);
            D_ovl13_02_8004DD90[i] = 1;
        }
    }
}

void func_ovl13_02_800448E4(void) {
    D_ovl13_02_8004DFAC = func_ovl13_02_8004CC20(0x175, 0x80000, 0xD0, NULL);
    D_ovl13_02_8004DFAC->unk40->unk36 = 0xBF;
    func_ovl13_02_8004C940(D_ovl13_02_8004DFAC->unk40, 0, 0, 0x400, 0x40, 0x400);
    D_ovl13_02_8004DFAC->unk40->unk10 = D_ovl13_02_8004DD10;
    D_ovl13_02_8004DFAC->unk40->unk14 = func_ovl13_02_8004C220();
    M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 0) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 4) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 8) = 0.0f;
}

void func_ovl13_02_800446B0(void) {
    s32 played;
    s32 i;

    func_ovl13_02_8004CBF8(D_ovl13_02_8004DFAC, 0x01000000);
    D_ovl13_02_8004DFAC->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    D_ovl13_02_8004DFAC->unk40->unk2C = 0.2f;
    played = 0;
    D_ovl13_02_8004DFBC = ((M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) - 1000.0f) - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8)) / 300.0f;
    for (i = 0; i < 300; i++) {
        D_ovl13_02_8004DFAC->unk40->unk18 += D_ovl13_02_8004DFBC;
        D_ovl13_02_8004DFAC->unk40->unk2C += 0.004333333f;
        if ((D_ovl13_02_8004DFAC->unk40->unk18 <= M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + 600.0f) && (played == 0)) {
            played = 1;
            func_ovl13_02_8004D2D0(0xE2);
        }
        if ((D_ovl13_02_8004DFAC->unk40->unk18 <= M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + 300.0f) && (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) - 300.0f <= D_ovl13_02_8004DFAC->unk40->unk18)) {
            M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 8) = -12.75f;
        } else {
            M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 8) = 0.0f;
        }
        func_ovl13_02_8004CD90();
    }
    func_ovl13_02_8004CC00(D_ovl13_02_8004DFAC, 0x01000000);
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_80044630(void) {
    s32 n;

    n = 0;
    if (D_ovl13_02_8004DE28 <= 0) {
        n = 1;
    }
    if (D_ovl13_02_8004DE2C <= 0) {
        n++;
    }
    if (func_ovl13_02_8004CFD0(0x419) != 0) {
        n++;
    }
    if (func_ovl13_02_800445C8() != 0) {
        n++;
    }
    M2C_FIELD(D_ovl13_02_8004DCDC, s32 *, 0x2C) = n;
}

s32 func_ovl13_02_800445C8(void) {
    s32 i;
    s32 n;

    n = 0;
    for (i = 0; i < 10; i++) {
        n += D_ovl13_02_8004DD90[i];
    }
    if (n >= 9) {
        return 1;
    }
    return 0;
}

void func_ovl13_02_800444F0(void) {
    D_ovl13_02_8004DEFC = 0.0f;
    D_ovl13_02_8004DF00 = 50.0f;
    D_ovl13_02_8004DF04 = 2.0f;
    D_ovl13_02_8004DF08 = 100.0f;
    D_ovl13_02_8004DF0C = 0.0f;
    D_ovl13_02_8004DF10 = 12.0f;
    D_ovl13_02_8004DEF0 = 360.0f;
    D_ovl13_02_8004DEF4 = 1.0f;
    D_ovl13_02_8004DEF8 = 1.0f;
loop_1:
    M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) - 4.0f);
    func_ovl13_02_8004CD90();
    goto loop_1;
}

void func_ovl13_02_80043E64(void) {
    UnkStructA *objs[5];
    f32 ph[5];
    Vec3f tgt;
    Vec3f cam;
    f32 cur[3];
    f32 want[3];
    s32 i;
    s32 best;
    f32 min;
    f32 top;
    f32 bottom;
    f32 d;
    f32 e;

    top = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + 9000.0f;
    bottom = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + -9000.0f;
    func_ovl13_02_8004D078(0x80, 0x80, 0x80);
    for (i = 0; i < 5; i++) {
        objs[i] = func_ovl13_02_8004CC20(0x118, 0x01080000, 0xD0, NULL);
        objs[i]->unk40->unkC |= 0x8000;
        objs[i]->unk40->unk30 = 4.0f;
        objs[i]->unk40->unk28 = objs[i]->unk40->unk2C = objs[i]->unk40->unk30;
        func_ovl13_02_8004C900(objs[i]->unk40, 1);
        func_ovl13_02_8004C908(objs[i]->unk40, 0x119, 0, 0);
        objs[i]->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0) - 800.0f;
        objs[i]->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4) + 300.0f;
        objs[i]->unk40->unk18 = (i * 3600.0f) + top;
        ph[i] = 0.0f;
    }
    tgt.x = objs[0]->unk40->unk10;
    tgt.y = objs[0]->unk40->unk14;
    cur[1] = 0.0f;
    want[1] = 0.0f;
    cur[0] = 270.0f;
    want[0] = 270.0f;
    cur[2] = 2000.0f;
    want[2] = 2000.0f;
    while (TRUE) {
        for (i = 0; i < 5; i++) {
            objs[i]->unk40->unk18 -= D_ovl13_02_8004DD3C * 5.0f;
            if (objs[i]->unk40->unk18 < bottom) {
                objs[i]->unk40->unk18 = top;
            }
            ph[i] += 0.1 + 0.1 * func_ovl13_02_8004CF00() * (f32) (i + 1);
            if (ph[i] > 4.0f) {
                ph[i] -= 4.0f;
            }
            func_ovl13_02_8004C950(objs[i]->unk40, 0, (s32) ph[i]);
            objs[i]->unk40->unk36 = (func_ovl13_02_8004CEF0(ph[i] * 0.25f * 180.0f) * 128.0f) + 128.0f;
        }
        min = 10000.0f;
        best = 0;
        cam.x = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
        cam.y = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
        cam.z = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
        for (i = 0; i < 5; i++) {
            if (objs[i]->unk40->unk18 <= cam.z) {
                d = cam.z - objs[i]->unk40->unk18;
            } else {
                d = objs[i]->unk40->unk18 - cam.z;
            }
            if (d < min) {
                min = d;
                best = i;
            }
        }
        func_ovl13_02_8004CCC8(objs[best], &tgt.x);
        func_ovl13_02_80043B64(&cam.x, cur, 10.0f, &tgt.x);
        func_ovl13_02_8004CB88(&cam.x, &tgt.x, want);
        cur[2] += (want[2] - cur[2]) * 0.1f;
        cur[1] = (want[1] - 90.0f >= 360.0f) ? want[1] - 90.0f - 360.0f : (want[1] < 90.0f) ? want[1] - 90.0f + 360.0f : want[1] - 90.0f;
        func_ovl13_02_8004CF10(cur[0], cur[1]);
        if (cur[2] > 2000.0f) {
            cur[2] = 2000.0f;
        }
        e = 1.0f - (cur[2] / 2000.0f);
        func_ovl13_02_8004D078((s32) (127.0f * e) + 0x80, (u8) ((1.0f - e) * 128.0f), (u8) ((1.0f - e) * 128.0f));
        func_ovl13_02_8004CD90();
    }
}

void func_ovl13_02_80043B64(f32 *arg0, f32 *arg1, f32 arg2, f32 *arg3) {
    f32 ang[3];
    f32 dx;
    f32 dy;
    f32 pad[1];

    func_ovl13_02_8004CB88(arg0, arg3, ang);
    ang[1] = ((ang[1] - 90.0f) >= 360.0f) ? (ang[1] - 90.0f) - 360.0f : (ang[1] < 90.0f) ? (ang[1] - 90.0f) + 360.0f : (ang[1] - 90.0f);
    dx = ((0 <= ang[0] && ang[0] <= 180.0f) ? ang[0] : (360.0f - ang[0]) * -1.0f)
       - ((0 <= arg1[0] && arg1[0] <= 180.0f) ? arg1[0] : (360.0f - arg1[0]) * -1.0f);
    if (dx > 180.0f) {
        dx -= 360.0f;
    }
    if (dx < -180.0f) {
        dx += 360.0f;
    }
    if (dx >= 0.0f) {
        if (dx > arg2) {
            dx = arg2;
        }
    } else if (dx < arg2 * -1.0f) {
        dx = arg2 * -1.0f;
    }
    dy = ((0 <= ang[1] && ang[1] <= 180.0f) ? ang[1] : (360.0f - ang[1]) * -1.0f)
       - ((0 <= arg1[1] && arg1[1] <= 180.0f) ? arg1[1] : (360.0f - arg1[1]) * -1.0f);
    if (dy > 180.0f) {
        dy -= 360.0f;
    }
    if (dy < -180.0f) {
        dy += 360.0f;
    }
    if (dy >= 0.0f) {
        if (dy > arg2) {
            dy = arg2;
        }
    } else if (dy < arg2 * -1.0f) {
        dy = arg2 * -1.0f;
    }
    arg1[0] += dx;
    arg1[1] += dy;
}

void func_ovl13_02_800439DC(void) {
    if (func_ovl13_02_8004CFD0(0x400) == 0) {
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0) = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0);
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = 500.0f;
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8) - 4000.0f);
        func_ovl13_02_8004CA38(2300.0f, 1000.0f, -1800.0f);
        func_ovl13_02_8004CA28(1);
        func_ovl13_02_8004CA58(305.0f, 45.0f, 1707.337f);
        func_ovl13_02_8004CAE8(M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0), M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8), func_ovl13_02_8004CBA0(&D_ovl13_02_8004DD10, &D_ovl13_02_8004DEC8), func_ovl13_02_8004CBA0(&D_ovl13_02_8004DD10, &D_ovl13_02_8004DEC8) + 100.0f);
        func_ovl13_02_8004CAD0(0.0f);
        func_ovl13_02_8004CAA0(0x10);
        func_ovl13_02_8004CFC8(0x41F);
        D_ovl13_02_8004DFE0.unk0 = 0x186;
        D_ovl13_02_8004DFE0.unk4 = 1;
        D_ovl13_02_8004DFE0.unk8 = 1;
        D_ovl13_02_8004DFE0.unkC[0] = 0;
        D_ovl13_02_8004DFE0.unkC[1] = 1.7948718f;
        D_ovl13_02_8004DFE0.unkC[2] = 8.717949f;
        D_ovl13_02_8004DFE0.unk18[0] = 0.0f;
        D_ovl13_02_8004DFE0.unk18[1] = 0.0f;
        D_ovl13_02_8004DFE0.unk18[2] = 0.0f;
        D_ovl13_02_8004DFE0.unk24[0] = -0.77698714f;
        D_ovl13_02_8004DFE0.unk24[1] = -0.033815384f;
        D_ovl13_02_8004DFE0.unk24[2] = 0;
        D_ovl13_02_8004DFE0.unk30[0] = 0.0f;
        D_ovl13_02_8004DFE0.unk30[1] = 0.0f;
        D_ovl13_02_8004DFE0.unk30[2] = 0.0f;
        D_ovl13_02_8004DFE0.unk3C = 0;
        D_ovl13_02_8004DFE0.unk40 = 0;
    }
}

void func_ovl13_02_80043698(void) {
    f32 v;
    f32 k;
    s32 i;
    s32 j;

    if (func_ovl13_02_8004CFD0(0x400) == 0) {
        func_ovl13_02_8004CD48(func_ovl13_02_80043970, NULL, 0, 0, 0x150);
        func_ovl13_02_8004362C(0);
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x0C000000);
        D_ovl13_02_8004DE80.unk0 = 2;
        D_ovl13_02_8004DE98.unk0 = 2;
        D_ovl13_02_8004DEB0.unk0 = 2;
        D_ovl13_02_8004DE80.unk8 = 0.8f;
        D_ovl13_02_8004DE98.unk8 = 0.8f;
        D_ovl13_02_8004DEB0.unk8 = 0.8f;
        D_ovl13_02_8004DE80.unkC = 0.11f;
        D_ovl13_02_8004DE98.unkC = 0.11f;
        D_ovl13_02_8004DEB0.unkC = 0.11f;
        D_ovl13_02_8004DE80.unk10 = 0.999f;
        D_ovl13_02_8004DE98.unk10 = 0.999f;
        D_ovl13_02_8004DEB0.unk10 = 0.999f;
        D_ovl13_02_8004DEF8 = 1.0f;
        D_ovl13_02_8004DEFC = 0.0f;
        D_ovl13_02_8004DF00 = 50.0f;
        D_ovl13_02_8004DF04 = 2.0f;
        D_ovl13_02_8004DF08 = 10.0f;
        D_ovl13_02_8004DF0C = 1.0f;
        D_ovl13_02_8004DF10 = 12.0f;
        k = 22.222221f;
        v = k;
        for (i = 0; i < 360; i++) {
            M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) += v;
            v += (k / 360.0f) * -1.0f;
            if (i == 120) {
                func_ovl13_02_8004CA70(&D_ovl13_02_8004DFE0, 0x170, 0);
            }
            func_ovl13_02_8004CD90();
        }
        func_ovl13_02_8004D0A0(1);
        j = 0xBF;
        func_ovl13_02_8004D0A8(j);
        func_ovl13_02_8004CD48(func_ovl13_02_80043010, NULL, 0, 0, 0x150);
        func_ovl13_02_800434C0(&D_ovl13_02_8004DC90);
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
        func_ovl13_02_80043040(D_ovl13_02_8004DE3C);
        func_ovl13_02_8004CA90();
        func_ovl13_02_8004CA38(2300.0f, 1700.0f, 1600.0f);
        func_ovl13_02_8004CA58(1.975f, 31.812f, 1707.337f);
        func_ovl13_02_8004CA28(0);
        func_ovl13_02_8004CA98(0x10);
        func_ovl13_02_8004CAD0(1500.0f);
        for (; j >= 0; j -= 8) {
            func_ovl13_02_8004D0A8(j);
            func_ovl13_02_8004CD90();
        }
        func_ovl13_02_8004D0A0(0);
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x0C000000);
    }
}

static void func_ovl13_02_80043970(void) {
    if (0) { func_ovl13_02_80043698(); }
    if (!(*D_ovl13_02_8004DCDC & 2)) {
        if (func_ovl13_02_8004CFB0(0xA4) == 0) {
            func_ovl13_02_8004CD68(0xE6);
        } else {
            func_ovl13_02_8004CD68(0x64);
        }
        func_ovl13_02_8004D2E0(0x2A);
    }
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_8004362C(s32 arg0) {
    func_ovl13_02_8004C920(D_ovl13_02_8004DE3C->unk40, arg0, 0);
    D_ovl13_02_8004DEF0 = func_ovl13_02_8004C938(D_ovl13_02_8004DE3C->unk40, 0) - 0.001f;
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
}

void func_ovl13_02_800435D4(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_ovl13_02_8004DE80.unk0 = arg0;
    D_ovl13_02_8004DE98.unk0 = arg0;
    D_ovl13_02_8004DEB0.unk0 = arg0;
    D_ovl13_02_8004DE80.unk8 = arg1;
    D_ovl13_02_8004DE98.unk8 = arg1;
    D_ovl13_02_8004DEB0.unk8 = arg1;
    D_ovl13_02_8004DE80.unkC = arg2;
    D_ovl13_02_8004DE98.unkC = arg2;
    D_ovl13_02_8004DEB0.unkC = arg2;
    D_ovl13_02_8004DE80.unk10 = arg3;
    D_ovl13_02_8004DE98.unk10 = arg3;
    D_ovl13_02_8004DEB0.unk10 = arg3;
}

void func_ovl13_02_800434C0(f32 *arg0) {
    f32 temp_fs1;
    f32 sp48[3];
    s32 var_s0;

    sp48[0] = M2C_FIELD(arg0, f32 *, 0);
    sp48[1] = M2C_FIELD(arg0, f32 *, 4);
    sp48[2] = M2C_FIELD(arg0, f32 *, 8);
    func_ovl13_02_800430CC(&sp48[0], 0x30, 1);
    temp_fs1 = (D_ovl13_02_8004DD14 - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4)) / 64;
    func_ovl13_02_8004CD48(func_ovl13_02_8004521C, (void *)0x40, 0, 0, 0x150);
    func_ovl13_02_80043098(0xE6, D_ovl13_02_8004DE3C);
    var_s0 = 0;
    do {
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + temp_fs1);
        if ((f64) var_s0 >= 32.0) {
            func_ovl13_02_8004CFC0(0x41F);
        }
        func_ovl13_02_8004CD90();
        var_s0 += 1;
    } while (var_s0 != 0x40);
}

void func_ovl13_02_800430CC(f32 *arg0, s32 arg1, s32 arg2) {
    f32 sp3C[3];
    f32 pad;
    f32 dy;
    f32 dx;
    s32 i;

    M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) = W360(M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0));
    M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = W360(M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4));
    sp3C[2] = sp3C[0] = sp3C[1] = 0.0f;
    func_ovl13_02_8004CB88(&D_ovl13_02_8004DEC8, arg0, sp3C);
    dx = (A180(sp3C[0]) - A180(M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0))) / (f32) arg1;
    if (arg2 != 0) {
        sp3C[1] = (sp3C[1] - 90.0f >= 360.0f) ? sp3C[1] - 90.0f - 360.0f : (sp3C[1] < 90.0f) ? sp3C[1] - 90.0f + 360.0f : sp3C[1] - 90.0f;
        if (!(sp3C[1] >= 0.0f && sp3C[1] <= 180.0f)) {
            sp3C[1] = (360.0f - sp3C[1]) * -1.0f;
        }
        sp3C[1] *= -1.0f;
        dy = sp3C[1] - A180(M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4));
        dy = W360(dy);
        if (!(dy >= 0.0f && dy <= 180.0f)) {
            dy = (360.0f - dy) * -1.0f;
        }
        dy /= (f32) arg1;
    }
    for (i = 0; i < arg1; i++) {
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) += dx;
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) = W360(M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0));
        if (arg2 != 0) {
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) += dy;
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = W360(M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4));
        }
        func_ovl13_02_8004CD90();
    }
}

void func_ovl13_02_80043098(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *temp_v0;

    temp_v0 = arg1->unk40;
    func_ovl13_02_8004D2F0(arg0, temp_v0->unk10, temp_v0->unk14, temp_v0->unk18);
    if (0) { func_ovl13_02_80043040(D_ovl13_02_8004DE3C); }
}

static void func_ovl13_02_80043040(UnkStructA *arg0) {
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x40)) {
        do {
            func_ovl13_02_8004CD90();
        } while (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x40));
    }
}

void func_ovl13_02_80043010(void) {
    func_ovl13_02_8004CD68(0x3C);
    func_ovl13_02_8004D2D0(0xDE);
    func_ovl13_02_8004CD58();
}

