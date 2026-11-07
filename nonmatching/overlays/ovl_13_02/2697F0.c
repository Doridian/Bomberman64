/*
 * NON_MATCHING: ovl_13_02's game object, complete; not in the ROM.
 * flags: -O3
 * differing words: us 5955, eu 5955, jp 5955
 * 25 of 84 functions match (the text is the same in every version).
 * Still differs: the large functions are m2c output only (80046E10,
 * 80049F68, 800489C0, 80048504, 80045AB8, 80043E64, 80048FBC, ...);
 * the original's statics (80043970, 8004521C, 800460C0, 80049400,
 * 8004A8E0, 8004BBE4, 8004BD28) are global here, because making them
 * static without reordering the file puts them in the wrong place
 * (6249 words); the inlined stubs 80044628, 8004B524, 8004B820/28/30
 * and the ten at 8004BE60-8004BEA8 are empty statics.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

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
    /* 0x04 */ s32 unk4;
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
void func_ovl13_02_8004CAC0(); /* 0x1715 */ /* unknown */
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
UnkStructA * D_ovl13_02_8004DE50;
u8 D_ovl13_02_8004DE54[0xC];
void * D_ovl13_02_8004DE60;
void * D_ovl13_02_8004DE64;
UnkStructA * D_ovl13_02_8004DE68;
UnkStructA * D_ovl13_02_8004DE6C;
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
void func_ovl13_02_80043970(void);
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
void func_ovl13_02_800484B4(UnkStructA *arg0, s32 arg1);
void func_ovl13_02_80048504(void);
void func_ovl13_02_800489C0(s32 arg0);
void func_ovl13_02_80048FBC(s32 arg0);
void func_ovl13_02_80049400(void);
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
void func_ovl13_02_8004B52C(void);
void func_ovl13_02_8004B57C(void);
void func_ovl13_02_8004B644(void);
void func_ovl13_02_8004B690(void);
void func_ovl13_02_8004B838(void);
void func_ovl13_02_8004BAFC(s32 arg0);
void func_ovl13_02_8004BBE4(void);
void func_ovl13_02_8004BD28(void);
void func_ovl13_02_8004BDA4(f32 arg0);
void func_ovl13_02_8004BDEC(f32 arg0, f32 arg1, f32 arg2);
void func_ovl13_02_8004BE48(void);

/* .data */
u8 D_ovl13_02_8004D4F0[8] = { 0 };
Move_ovl13_02 D_ovl13_02_8004D4F8[2] = {
    { 0xF0, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D4F8[1] },
    { 0, 2, 0, { 32768.0f, 32768.0f, 32768.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D4F8[0], NULL }
};
Move_ovl13_02 D_ovl13_02_8004D580[2] = {
    { 0xF0, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D580[1] },
    { 0, 2, 0, { 32768.0f, 32768.0f, 32768.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D580[0], NULL }
};
Move_ovl13_02 D_ovl13_02_8004D608[3] = {
    { 0xC0, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D608[1] },
    { 0x30, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D608[0], &D_ovl13_02_8004D608[2] },
    { 0, 2, 0, { 32768.0f, 32768.0f, 32768.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D608[1], NULL }
};
Move_ovl13_02 D_ovl13_02_8004D6D4[7] = {
    { 0x30, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D6D4[1] },
    { 0x12C, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D6D4[0], &D_ovl13_02_8004D6D4[2] },
    { 0xC0, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D6D4[1], &D_ovl13_02_8004D6D4[3] },
    { 0, 2, 0, { 32768.0f, 32768.0f, 32768.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D6D4[2], NULL },
    { 0x1E, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 33.333332f, 0.0f }, { 0.0f, 0.0f, 0.0f }, NULL, &D_ovl13_02_8004D6D4[5] },
    { 0x3C, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D6D4[4], &D_ovl13_02_8004D6D4[6] },
    { 0x1E, 1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, -33.333332f, -0.0f }, { 0.0f, 0.0f, 0.0f }, &D_ovl13_02_8004D6D4[5], NULL }
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

void func_ovl13_02_8004BD28(void) {
    void *sp1C;

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

void func_ovl13_02_8004BBE4(void) {
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
        D_ovl13_02_8004DCAC = func_ovl13_02_8004C3D8();
        func_ovl13_02_8004C3B8(&D_ovl13_02_8004DCA0);
        func_ovl13_02_8004C3E0(D_ovl13_02_8004DCAC, &D_ovl13_02_8004DC90);
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
    UnkStructA *temp_v0;

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
    temp_v0 = func_ovl13_02_8004CC20(-1, 0, 0xD0, NULL);
    D_ovl13_02_8004DCF4 = temp_v0;
    temp_v0->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
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
    D_ovl13_02_8004DCAC = func_ovl13_02_8004C3D8();
    func_ovl13_02_8004C3B8(&D_ovl13_02_8004DCA0);
    func_ovl13_02_8004C3E0(D_ovl13_02_8004DCAC, &D_ovl13_02_8004DC90);
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
}

void func_ovl13_02_8004B52C(void) {
    func_ovl13_02_8004B524();
    func_ovl13_02_8004CFC0(0x424);
    D_ovl13_02_8004DCAC = func_ovl13_02_8004C3D8();
    func_ovl13_02_8004C3B8(&D_ovl13_02_8004DCA0);
    func_ovl13_02_8004C3E0(D_ovl13_02_8004DCAC, &D_ovl13_02_8004DC90);
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
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;

    temp_v0 = arg0->unk40;
    temp_v0->unk10 += M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 0);
    temp_v0_2 = arg0->unk40;
    temp_v0_2->unk14 += M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 4);
    temp_v0_3 = arg0->unk40;
    temp_v0_3->unk18 += M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 8);
}

void func_ovl13_02_8004B298(UnkStructA *arg0) {
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;

    func_ovl13_02_80043098(0x1E, arg0);
    func_ovl13_02_8004CC00(arg0, 0x04000000);
    arg0->unk40->unk48->unk4->unk4 = 0.0f;
    temp_v0 = arg0->unk40;
    temp_v0->unk28 *= 3.5f;
    temp_v0_2 = arg0->unk40;
    temp_v0_2->unk30 *= 3.5f;
    temp_v0_3 = arg0->unk40;
    temp_v0_3->unk2C *= 0.1f;
    temp_v0_4 = arg0->unk40;
    temp_v0_4->unk14 += 20.0f;
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
    temp_v0 = func_ovl13_02_8004C348();
    D_ovl13_02_8004DCDC = temp_v0;
    if (M2C_FIELD(temp_v0, s32 *, 0x10) == 0) {
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
    M2C_FIELD(&D_ovl13_02_8004DCE0, f32 *, 4) = 90.0f;
    M2C_FIELD(&D_ovl13_02_8004DCE0, f32 *, 0) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DCE0, f32 *, 8) = 200.0f;
    func_ovl13_02_8004CAD8(&D_ovl13_02_8004DCE0);
    func_ovl13_02_8004CAD0(1500.0f);
    func_ovl13_02_8004C370(0);
}

void func_ovl13_02_8004AF1C(void) {
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_2;
    f32 temp_ft3;

    M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 8) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 8) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 4) = (f32) M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 8);
    M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4) = (f32) M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 8);
    temp_ft3 = M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4);
    D_ovl13_02_8004DCFC = NULL;
    M2C_FIELD(&D_ovl13_02_8004DD00, UnkStructA **, 0) = NULL;
    M2C_FIELD(&D_ovl13_02_8004DD00, s32 *, 4) = 0;
    M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 0) = temp_ft3;
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
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *temp_v0_2;
    f32 temp_fs0;
    f32 temp_fv0;

    temp_fs0 = func_ovl13_02_8004C938(D_ovl13_02_8004DCFC->unk40, 0) - 0.001f;
    if (func_ovl13_02_8004C940(D_ovl13_02_8004DD00->unk40, 0, 0, 0x400, 0x20, 0x400) == -1) {
        func_ovl13_02_8004BEB8("shift entry err\n");
    }
loop_3:
    D_ovl13_02_8004DCFC->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 0) + M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    D_ovl13_02_8004DCFC->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 4);
    D_ovl13_02_8004DCFC->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 8) + M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8);
    D_ovl13_02_8004DCFC->unk40->unk1C = M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4);
    D_ovl13_02_8004DD00->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 0) + M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    D_ovl13_02_8004DD00->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 4);
    D_ovl13_02_8004DD00->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DD30, f32 *, 8) + M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8);
    D_ovl13_02_8004DD00->unk40->unk1C = M2C_FIELD(&D_ovl13_02_8004DD20, f32 *, 4);
    temp_v0 = D_ovl13_02_8004DCFC->unk40->unk48->unk4;
    temp_v0->unk4 += D_ovl13_02_8004DD3C;
    temp_v0_2 = D_ovl13_02_8004DCFC->unk40->unk48->unk4;
    temp_fv0 = temp_v0_2->unk4;
    if (temp_fs0 < temp_fv0) {
        temp_v0_2->unk4 = temp_fv0 - temp_fs0;
    }
    func_ovl13_02_8004CD90();
    goto loop_3;
}

void func_ovl13_02_8004AB3C(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    y = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    x = (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0) - 500.0f) + 50.0f;
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
    s32 sp78[3];
    UnkStructA **sp60;
    UnkStructA **temp_a1;
    UnkStructA *temp_s1;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    UnkStructA_40 *temp_v0_6;
    UnkStructA_40 *temp_v0_7;
    UnkStructA_40 *temp_v0_8;
    f32 var_fs2;
    f32 var_fs4;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s0_2;

    temp_v0 = func_ovl13_02_8004CD70();
    temp_a1 = &D_ovl13_02_8004DD68[temp_v0];
    if (D_ovl13_02_8004DD68[temp_v0] != NULL) {
        temp_s1 = *temp_a1;
        temp_v0_2 = temp_s1->unk40;
        sp60 = temp_a1;
        func_ovl13_02_8004C250(temp_v0_2->unk10, temp_v0_2->unk14, temp_v0_2->unk18, sp78, 0);
        var_s0 = 0;
        do {
            temp_v0_3 = temp_s1->unk40;
            temp_v0_3->unk14 -= 1.0f;
            temp_v0_4 = temp_s1->unk40;
            temp_v0_4->unk18 += 2.0f;
            func_ovl13_02_8004CD90();
            var_s0 += 1;
        } while (var_s0 < 0x1E);
        func_ovl13_02_8004C238(sp78[0], sp78[1], sp78[2] - 3, sp78[0], sp78[2] + 2, 0);
        if (func_ovl13_02_8004CF08(1) != 0) {
            var_fs4 = 5.0f;
        } else {
            var_fs4 = -5.0f;
        }
        var_s0_2 = 0;
        if (func_ovl13_02_8004CF08(1) != 0) {
            var_fs2 = 5.0f;
        } else {
            var_fs2 = -5.0f;
        }
        do {
            temp_v0_5 = temp_s1->unk40;
            temp_v0_5->unk1C += var_fs4;
            temp_v0_6 = temp_s1->unk40;
            temp_v0_6->unk20 += var_fs2;
            temp_v0_7 = temp_s1->unk40;
            temp_v0_7->unk14 -= 1.0f;
            temp_v0_8 = temp_s1->unk40;
            temp_v0_8->unk18 += 15.0f;
            if ((f64) var_s0_2 > 60.0) {
                func_ovl13_02_8004CBF8(temp_s1, 0x40000);
            }
            func_ovl13_02_8004CD90();
            var_s0_2 += 1;
        } while (var_s0_2 != 0x78);
        func_ovl13_02_8004CC10(temp_s1);
        *sp60 = NULL;
    }
    func_ovl13_02_8004CD58();
}

s32 func_ovl13_02_8004A844(void) {
    s32 sp40[3];
    s32 var_s0;
    s32 var_s1;
    s32 var_v0;

    func_ovl13_02_8004C250(M2C_FIELD(&D_ovl13_02_8004DC90, f32 *, 0), M2C_FIELD(&D_ovl13_02_8004DC90, f32 *, 4), M2C_FIELD(&D_ovl13_02_8004DC90, f32 *, 8), sp40, 2);
    var_s1 = 0;
    var_s0 = -2;
    do {
        var_s0 += 1;
        if (func_ovl13_02_8004C268(sp40[0] + var_s0, sp40[1], sp40[2]) & 0xF) {
            var_s1 += 1;
        }
    } while (var_s0 != 3);
    var_v0 = 0;
    if (var_s1 >= 3) {
        var_v0 = 1;
    }
    return var_v0;
}

void func_ovl13_02_80049F68(void) {
    s32 sp34;
    UnkStructA **temp_s0;
    UnkStructA **temp_s0_2;
    UnkStructA **temp_s0_3;
    UnkStructA **temp_s0_4;
    UnkStructA **temp_s0_5;
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_10;
    UnkStructA *temp_v0_11;
    UnkStructA *temp_v0_12;
    UnkStructA *temp_v0_13;
    UnkStructA *temp_v0_14;
    UnkStructA *temp_v0_2;
    UnkStructA *temp_v0_3;
    UnkStructA *temp_v0_4;
    UnkStructA *temp_v0_5;
    UnkStructA *temp_v0_6;
    UnkStructA *temp_v0_7;
    UnkStructA *temp_v0_8;
    UnkStructA *temp_v0_9;
    UnkStructA_40 *temp_t0;
    UnkStructA_40 *temp_t0_2;
    UnkStructA_40 *temp_v1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;

    func_ovl13_02_80049D50();
    func_ovl13_02_800499A0();
    D_ovl13_02_8004DCF8 = -1;
    D_ovl13_02_8004DE24 = 0xA;
    D_ovl13_02_8004DE28 = 8;
    D_ovl13_02_8004DE2C = 8;
    if (func_ovl13_02_8004CFD0(0x418) != 0) {
        D_ovl13_02_8004DE24 -= 2;
        D_ovl13_02_8004DE28 = (s32) D_ovl13_02_8004DE28 / 2;
        D_ovl13_02_8004DE2C = (s32) D_ovl13_02_8004DE2C / 2;
    }
    D_ovl13_02_8004DE34 = 0;
    D_ovl13_02_8004DE74 = 2.5f;
    D_ovl13_02_8004DE78 = 2.5f;
    D_ovl13_02_8004DE30 = 0;
    D_ovl13_02_8004DE38 = 1;
    D_ovl13_02_8004DEF0 = 0.0f;
    D_ovl13_02_8004DEF4 = 0.0f;
    D_ovl13_02_8004DEF8 = 0.0f;
    D_ovl13_02_8004DEE4 = 0.0f;
    D_ovl13_02_8004DEE8 = 0.0f;
    D_ovl13_02_8004DEEC = 0.8166667f;
    M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 8) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0) = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) = (f32) M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8);
    M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = 330.0f;
    D_ovl13_02_8004DEFC = 0.0f;
    D_ovl13_02_8004DF00 = 50.0f;
    D_ovl13_02_8004DF04 = 2.0f;
    D_ovl13_02_8004DF08 = 10.0f;
    D_ovl13_02_8004DF0C = 1.0f;
    D_ovl13_02_8004DF10 = 12.0f;
    temp_v0 = func_ovl13_02_8004CC20(0x179, 0x01008004, 0x30, NULL);
    D_ovl13_02_8004DE3C = temp_v0;
    func_ovl13_02_8004CC00(temp_v0, 0x0E000000);
    D_ovl13_02_8004DE3C->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    D_ovl13_02_8004DE3C->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    D_ovl13_02_8004DE3C->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    D_ovl13_02_8004DE3C->unk40->unk1C = 330.0f;
    temp_v0_2 = func_ovl13_02_8004CC20(-1, 0x01600000, 0xC0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE40 = temp_v0_2;
    temp_v0_2->unk4C = 0.0f;
    D_ovl13_02_8004DE40->unk50 = 0.0f;
    D_ovl13_02_8004DE40->unk54 = 0.0f;
    D_ovl13_02_8004DE40->unk38 = 0.0f;
    D_ovl13_02_8004DE40->unk34 = 24.0f;
    D_ovl13_02_8004DE40->unk40->unk30 = 18.0f;
    temp_v1 = D_ovl13_02_8004DE40->unk40;
    temp_fv0 = temp_v1->unk30;
    temp_v1->unk2C = temp_fv0;
    D_ovl13_02_8004DE40->unk40->unk28 = temp_fv0;
    D_ovl13_02_8004DE40->unkC = 0x6040;
    temp_v0_3 = func_ovl13_02_8004CC20(-1, 0x01600010, 0xC0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE44 = temp_v0_3;
    temp_v0_3->unk4C = 0.0f;
    D_ovl13_02_8004DE44->unk50 = -100.0f;
    D_ovl13_02_8004DE44->unk54 = 450.0f;
    D_ovl13_02_8004DE44->unk38 = 0.0f;
    D_ovl13_02_8004DE44->unk34 = 24.0f;
    D_ovl13_02_8004DE44->unk40->unk30 = 15.0f;
    temp_t0 = D_ovl13_02_8004DE44->unk40;
    temp_fv0_2 = temp_t0->unk30;
    temp_t0->unk2C = temp_fv0_2;
    D_ovl13_02_8004DE44->unk40->unk28 = temp_fv0_2;
    D_ovl13_02_8004DE44->unkC = D_ovl13_02_8004DE40->unkC;
    D_ovl13_02_8004DE48 = func_ovl13_02_8004CC20(-1, 0, 0xD0, D_ovl13_02_8004DE3C);
    temp_v0_4 = func_ovl13_02_8004CC20(-1, 0x408004, 0xC0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE4C = temp_v0_4;
    temp_v0_4->unk4C = 0.0f;
    D_ovl13_02_8004DE4C->unk50 = 0.0f;
    D_ovl13_02_8004DE4C->unk54 = -500.0f;
    D_ovl13_02_8004DE4C->unk38 = 0.0f;
    D_ovl13_02_8004DE4C->unk34 = 100.0f;
    D_ovl13_02_8004DE4C->unkC = D_ovl13_02_8004DE40->unkC;
    temp_v0_5 = func_ovl13_02_8004CC20(-1, 0x01600000, 0xC0, D_ovl13_02_8004DE3C);
    D_ovl13_02_8004DE70 = temp_v0_5;
    temp_v0_5->unk4C = 0.0f;
    D_ovl13_02_8004DE70->unk50 = -350.0f;
    D_ovl13_02_8004DE70->unk54 = 500.0f;
    D_ovl13_02_8004DE70->unk38 = 0.0f;
    D_ovl13_02_8004DE70->unk34 = 24.0f;
    D_ovl13_02_8004DE70->unk40->unk30 = 12.0f;
    temp_t0_2 = D_ovl13_02_8004DE70->unk40;
    temp_fv0_3 = temp_t0_2->unk30;
    temp_t0_2->unk2C = temp_fv0_3;
    D_ovl13_02_8004DE70->unk40->unk28 = temp_fv0_3;
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
    temp_v0_6 = func_ovl13_02_8004CC20(0x177, 0x400000, 0xD0, D_ovl13_02_8004DE3C);
    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x1C) = temp_v0_6;
    temp_v0_6->unk4C = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x1C)->unk50 = -35.0f;
    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x1C)->unk54 = 680.0f;
    M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x1C), Link_ovl13_02 **, 0x3C) = &D_ovl13_02_8004DEB0;
    temp_v0_7 = func_ovl13_02_8004CC20(0x177, 0, 0xD0, NULL);
    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0) = temp_v0_7;
    func_ovl13_02_80049F1C(temp_v0_7);
    func_ovl13_02_8004CBE0(D_ovl13_02_8004DE6C, M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0), &D_ovl13_02_8004DEB0, 0x150);
    func_ovl13_02_8004CBF8(M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0), 0x500000);
    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0)->unk4C = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0)->unk50 = 40.0f;
    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0)->unk54 = 220.0f;
    sp34 = 1;
    temp_v0_8 = func_ovl13_02_8004CC20(0x177, 0, 0xD0, D_ovl13_02_8004DE6C);
    temp_s0 = &(&D_ovl13_02_8004DE50)[sp34];
    M2C_FIELD(temp_s0, UnkStructA **, 0) = temp_v0_8;
    func_ovl13_02_80049F1C(temp_v0_8);
    func_ovl13_02_8004CBE0(M2C_FIELD(temp_s0, UnkStructA **, -4), M2C_FIELD(temp_s0, UnkStructA **, 0), &D_ovl13_02_8004DEB0, 0x150);
    temp_s0_2 = temp_s0 + 4;
    temp_v0_9 = func_ovl13_02_8004CC20(0x178, 0, 0xD0, NULL);
    M2C_FIELD(temp_s0, UnkStructA **, 4) = temp_v0_9;
    func_ovl13_02_80049F1C(temp_v0_9);
    func_ovl13_02_8004CBE0(M2C_FIELD(temp_s0_2, UnkStructA **, -4), M2C_FIELD(temp_s0, UnkStructA **, 4), &D_ovl13_02_8004DE98, 0x150);
    temp_s0_3 = temp_s0_2 + 4;
    temp_v0_10 = func_ovl13_02_8004CC20(0x178, 0, 0xD0, NULL);
    M2C_FIELD(temp_s0_2, UnkStructA **, 4) = temp_v0_10;
    func_ovl13_02_80049F1C(temp_v0_10);
    func_ovl13_02_8004CBE0(M2C_FIELD(temp_s0_3, UnkStructA **, -4), M2C_FIELD(temp_s0_2, UnkStructA **, 4), &D_ovl13_02_8004DE98, 0x150);
    temp_s0_4 = temp_s0_3 + 4;
    temp_v0_11 = func_ovl13_02_8004CC20(0x17E, 0, 0xD0, NULL);
    M2C_FIELD(temp_s0_3, UnkStructA **, 4) = temp_v0_11;
    func_ovl13_02_80049F1C(temp_v0_11);
    func_ovl13_02_8004CBE0(M2C_FIELD(temp_s0_4, UnkStructA **, -4), M2C_FIELD(temp_s0_3, UnkStructA **, 4), &D_ovl13_02_8004DE80, 0x150);
    temp_s0_5 = temp_s0_4 + 4;
    temp_v0_12 = func_ovl13_02_8004CC20(0x17C, 0, 0xD0, NULL);
    M2C_FIELD(temp_s0_4, UnkStructA **, 4) = temp_v0_12;
    func_ovl13_02_80049F1C(temp_v0_12);
    func_ovl13_02_8004CBE0(M2C_FIELD(temp_s0_5, UnkStructA **, -4), M2C_FIELD(temp_s0_4, UnkStructA **, 4), &D_ovl13_02_8004DE80, 0x150);
    temp_v0_13 = func_ovl13_02_8004CC20(0x180, 0, 0x30, NULL);
    M2C_FIELD(temp_s0_5, UnkStructA **, 4) = temp_v0_13;
    func_ovl13_02_80049F1C(temp_v0_13);
    func_ovl13_02_8004CBE0(M2C_FIELD((temp_s0_5 + 4), UnkStructA **, -4), M2C_FIELD(temp_s0_5, UnkStructA **, 4), &D_ovl13_02_8004DE80, 0x150);
    func_ovl13_02_8004CBC8(M2C_FIELD(temp_s0_5, UnkStructA **, 4), 0x30);
    func_ovl13_02_8004CBF8(M2C_FIELD(temp_s0_5, UnkStructA **, 4), 0x8000);
    M2C_FIELD(temp_s0_5, UnkStructA **, 4)->unk38 = 0.0f;
    M2C_FIELD(temp_s0_5, UnkStructA **, 4)->unk34 = 150.0f;
    M2C_FIELD(temp_s0_5, UnkStructA **, 4)->unkC = D_ovl13_02_8004DE40->unkC;
    temp_v0_14 = func_ovl13_02_8004CC30(M2C_FIELD(temp_s0_5, UnkStructA **, 4));
    temp_fv0_4 = M2C_FIELD(temp_s0_5, UnkStructA **, 4)->unk34 / 50.0f;
    temp_v0_14->unk54 = temp_fv0_4;
    temp_v0_14->unk4C = temp_fv0_4;
    func_ovl13_02_8004C900(D_ovl13_02_8004DE3C->unk40, 4);
    func_ovl13_02_8004636C();
    func_ovl13_02_800463BC();
    func_ovl13_02_8004C900(D_ovl13_02_8004DE68->unk40, 2);
    func_ovl13_02_8004C900(M2C_FIELD(D_ovl13_02_8004DE64, UnkStructA_40 **, 0x40), 2);
    func_ovl13_02_8004C900(M2C_FIELD(D_ovl13_02_8004DE60, UnkStructA_40 **, 0x40), 2);
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
    f32 sp4;
    f32 temp_fa1;
    f32 temp_ft5;

    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) - 1400.0f);
    temp_fa1 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0) - 300.0f;
    temp_ft5 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0) + 300.0f;
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0xC) = temp_fa1;
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x18) = temp_ft5;
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x24) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 4) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x10) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x1C) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x28) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x14) = (f32) M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x20) = (f32) M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x2C) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) - 1700.0f);
    sp4 = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x2C);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x30) = temp_fa1;
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x3C) = temp_ft5;
    M2C_FIELD(&D_ovl13_02_8004DF60, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x34) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x40) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DF60, f32 *, 4) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x38) = sp4;
    M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0x44) = sp4;
    M2C_FIELD(&D_ovl13_02_8004DF60, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + 1100.0f);
    M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4) + 2500.0f);
    M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) - 1800.0f);
    M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 4) = 500.0f;
    M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) + 4000.0f);
    M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4) + 800.0f);
    M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) - 2400.0f);
    M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4) + 100.0f);
    M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DFC0, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DFC0, f32 *, 4) = (f32) M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4);
    M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 8) = (f32) M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 8);
    M2C_FIELD(&D_ovl13_02_8004DFD0, f32 *, 0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0);
    M2C_FIELD(&D_ovl13_02_8004DFC0, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) - 1300.0f);
    M2C_FIELD(&D_ovl13_02_8004DFD0, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4) - 600.0f);
    M2C_FIELD(&D_ovl13_02_8004DFD0, f32 *, 8) = (f32) M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8);
}

void func_ovl13_02_800499A0(void) {
    f32 sp28;
    f32 sp20;
    f32 sp1C;
    f32 sp14;
    f32 spC;
    f32 sp8;
    f32 sp4;
    f32 temp_ft0;
    f32 temp_ft2;
    f32 temp_ft3;
    f32 temp_ft3_2;

    temp_ft2 = (f32) D_ovl13_02_8004D4F8->unk0;
    sp28 = M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 0);
    sp20 = temp_ft2;
    sp1C = M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 4);
    sp14 = M2C_FIELD(&D_ovl13_02_8004DF70, f32 *, 8);
    D_ovl13_02_8004D4F8->unk24[0] = (sp28 - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0)) / sp20;
    D_ovl13_02_8004D4F8->unk24[1] = (sp1C - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4)) / temp_ft2;
    D_ovl13_02_8004D4F8->unk24[2] = (sp14 - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8)) / sp20;
    D_ovl13_02_8004D4F8->unk24[0] += -20.833334f;
    D_ovl13_02_8004D4F8->unk30[0] = 0.17433752f;
    D_ovl13_02_8004D4F8[1].unk24[0] = sp28;
    D_ovl13_02_8004D4F8[1].unk24[1] = sp1C;
    sp20 = (f32) M2C_FIELD(D_ovl13_02_8004D4F8, s32 *, 0x88);
    D_ovl13_02_8004D4F8[1].unk24[2] = sp14;
    M2C_FIELD(D_ovl13_02_8004D4F8, f32 *, 0xAC) = (f32) ((M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0) - sp28) / sp20);
    M2C_FIELD(D_ovl13_02_8004D4F8, f32 *, 0xB0) = (f32) ((M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4) - sp1C) / sp20);
    M2C_FIELD(D_ovl13_02_8004D4F8, f32 *, 0xB4) = (f32) ((M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8) - sp14) / sp20);
    M2C_FIELD(D_ovl13_02_8004D4F8, f32 *, 0xAC) = (f32) (M2C_FIELD(D_ovl13_02_8004D4F8, f32 *, 0xAC) + -20.833334f);
    temp_ft3 = (f32) D_ovl13_02_8004D608->unk0;
    sp20 = temp_ft3;
    M2C_FIELD(D_ovl13_02_8004D4F8, f32 *, 0xB8) = 0.17433752f;
    M2C_FIELD(D_ovl13_02_8004D4F8, f32 *, 0xF0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0);
    M2C_FIELD(D_ovl13_02_8004D4F8, f32 *, 0xF4) = (f32) M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4);
    M2C_FIELD(D_ovl13_02_8004D4F8, f32 *, 0xF8) = (f32) M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8);
    D_ovl13_02_8004D608->unk24[0] = (M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0)) / sp20;
    D_ovl13_02_8004D608->unk24[1] = (M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4)) / sp20;
    D_ovl13_02_8004D608->unk24[2] = (M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 8) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8)) / temp_ft3;
    D_ovl13_02_8004D608->unk24[0] += -26.041666f;
    temp_ft3_2 = (f32) D_ovl13_02_8004D608[1].unk0;
    D_ovl13_02_8004D608->unk30[0] = 0.2726876f;
    sp20 = M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 0);
    spC = temp_ft3_2;
    sp8 = M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 4);
    sp4 = M2C_FIELD(&D_ovl13_02_8004DFA0, f32 *, 8);
    D_ovl13_02_8004D608[1].unk24[0] = (sp20 - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0)) / spC;
    D_ovl13_02_8004D608[2].unk24[0] = sp20;
    D_ovl13_02_8004D608[1].unk24[1] = (sp8 - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 4)) / temp_ft3_2;
    D_ovl13_02_8004D608[2].unk24[1] = sp8;
    D_ovl13_02_8004D608[2].unk24[2] = sp4;
    D_ovl13_02_8004D608[1].unk24[2] = (sp4 - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 8)) / spC;
    spC = (f32) M2C_FIELD(D_ovl13_02_8004D608, s32 *, 0xCC);
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0xF0) = (f32) ((M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0) - sp20) / spC);
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0xF4) = (f32) ((M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 4) - sp8) / spC);
    temp_ft0 = (f32) M2C_FIELD(D_ovl13_02_8004D608, s32 *, 0x154);
    sp20 = temp_ft0;
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0xF8) = (f32) ((M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 8) - sp4) / spC);
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0x178) = (f32) ((M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0) - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 0)) / sp20);
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0x17C) = (f32) ((M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4) - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 4)) / sp20);
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0x180) = (f32) ((M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8) - M2C_FIELD(&D_ovl13_02_8004DF90, f32 *, 8)) / temp_ft0);
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0x178) = (f32) (M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0x178) + -26.041666f);
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0x184) = 0.2726876f;
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0x1BC) = (f32) M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0);
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0x1C0) = (f32) M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4);
    M2C_FIELD(D_ovl13_02_8004D608, f32 *, 0x1C4) = (f32) M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8);
    D_ovl13_02_8004D8B0.unk24[0] = (M2C_FIELD(&D_ovl13_02_8004DFD0, f32 *, 0) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 0)) / 30.0f;
    D_ovl13_02_8004D8B0.unk24[1] = (M2C_FIELD(&D_ovl13_02_8004DFD0, f32 *, 4) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 4)) / 30.0f;
    D_ovl13_02_8004D8F4.unk24[0] = (f32) (D_ovl13_02_8004D8B0.unk24[0] * -1.0f);
    D_ovl13_02_8004D8B0.unk24[2] = (M2C_FIELD(&D_ovl13_02_8004DFD0, f32 *, 8) - M2C_FIELD(&D_ovl13_02_8004DD58, f32 *, 8)) / 30.0f;
    D_ovl13_02_8004D8F4.unk24[1] = (f32) (D_ovl13_02_8004D8B0.unk24[1] * -1.0f);
    D_ovl13_02_8004D8F4.unk24[2] = (f32) (D_ovl13_02_8004D8B0.unk24[2] * -1.0f);
}

void func_ovl13_02_8004980C(void) {
    s32 sp3C;
    s32 temp_s1;
    s32 temp_t3;

    if (func_ovl13_02_8004CFD0(0x424) == 0) {
        do {
            func_ovl13_02_8004CD90();
        } while (func_ovl13_02_8004CFD0(0x424) == 0);
    }
    if (*D_ovl13_02_8004DCDC & 2) {
        if (func_ovl13_02_8004CFB0(0xA4) != 0) {
            func_ovl13_02_80046E10(2);
        } else {
            func_ovl13_02_800480EC(2);
        }
    }
    D_ovl13_02_8004DE38 = 0xC;
    sp3C = 0xC;
    if (D_ovl13_02_8004DE24 > 0) {
        do {
            temp_s1 = D_ovl13_02_8004DE30;
            D_ovl13_02_8004DE30 = 0;
            func_ovl13_02_80048FBC(sp3C);
            D_ovl13_02_8004DE30 = temp_s1;
            func_ovl13_02_800496A0(&D_ovl13_02_8004DE30, &sp3C);
            func_ovl13_02_80049468(&D_ovl13_02_8004DE30, &sp3C);
            temp_t3 = func_ovl13_02_8004CF08(3) + D_ovl13_02_8004DE24 + 1;
            D_ovl13_02_8004DE38 = temp_t3;
            sp3C = temp_t3;
        } while (D_ovl13_02_8004DE24 > 0);
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
    s32 list[6];
    s32 n;
    s32 i;

    if (D_ovl13_02_8004DE24 > 0) {
        for (i = 0; i < 6; i++) {
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
        switch (list[func_ovl13_02_8004CF08(n - 1)]) {
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

void func_ovl13_02_80049400(void) {
    void *sp1C;

    sp1C = func_ovl13_02_8004CD70();
    func_ovl13_02_8004CD68((func_ovl13_02_8004CF08(2) * 0xA) + 0xA);
    func_ovl13_02_8004D2F0((s32) sp1C, M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0), M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4), M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8));
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_80048FBC(s32 arg0) {
    void (*sp7C)();
    f32 *temp_a1;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    s32 var_s4;
    s32 var_s5;

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
    var_s4 = 0;
    var_s5 = 0;
    D_ovl13_02_8004DF10 = 12.0f;
    if (arg0 > 0) {
        sp7C = func_ovl13_02_80049400;
        do {
            D_ovl13_02_8004DEF4 = 0.0f;
            D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 = 0.0f;
            func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
            temp_a1 = (var_s4 * 0xC) + &D_ovl13_02_8004DF18;
            temp_fs0 = (M2C_FIELD(temp_a1, f32 *, 0) - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0)) / D_ovl13_02_8004DEF0;
            temp_fs1 = (M2C_FIELD(temp_a1, f32 *, 4) - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4)) / D_ovl13_02_8004DEF0;
            temp_fs2 = (M2C_FIELD(temp_a1, f32 *, 8) - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8)) / D_ovl13_02_8004DEF0;
            if (func_ovl13_02_8004CBA0(&D_ovl13_02_8004DEC8, temp_a1) > 300.0f) {
                if (func_ovl13_02_8004CF08(1) != 0) {
                    func_ovl13_02_8004CD48(sp7C, (void *)0xF1, 0, 0, 0x150);
                } else {
                    func_ovl13_02_8004CD48(sp7C, (void *)0xF2, 0, 0, 0x150);
                }
            } else if (func_ovl13_02_8004CF08(1) != 0) {
                func_ovl13_02_8004CD48(sp7C, (void *)0xED, 0, 0, 0x150);
            } else {
                func_ovl13_02_8004CD48(sp7C, (void *)0xEE, 0, 0, 0x150);
            }
            if (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40) && (D_ovl13_02_8004DE30 == 0)) {
loop_11:
                M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0) += temp_fs0;
                M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + temp_fs1);
                M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + temp_fs2);
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
                    D_ovl13_02_8004DE34 = 0;
                } else {
                    func_ovl13_02_8004CD90();
                    if (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40) && (D_ovl13_02_8004DE30 == 0)) {
                        goto loop_11;
                    }
                }
            }
            var_s5 += 1;
            var_s4 = func_ovl13_02_8004CF08(5);
        } while (var_s5 < arg0);
    }
    func_ovl13_02_8004CFC8(0x41D);
}

void func_ovl13_02_800489C0(s32 arg0) {
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    s32 var_s0;
    s32 var_s1;
    s32 var_s5;

    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x08000000);
    func_ovl13_02_8004511C();
    spA8 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    spA0 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    spA4 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    func_ovl13_02_800430CC(&spA0, 0x1E, 1);
    func_ovl13_02_8004CA70(D_ovl13_02_8004D4F8, 0x170, 0);
    spA0 = M2C_FIELD(&D_ovl13_02_8004DF60, f32 *, 0);
    spA4 = 500.0f;
    spA8 = M2C_FIELD(&D_ovl13_02_8004DF60, f32 *, 8);
    func_ovl13_02_80044F0C(&spA0, 0xB4, 10.0f);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    func_ovl13_02_8004CB00(NULL);
    func_ovl13_02_8004CAA0(0x20);
    spA8 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    spA0 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    spA4 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    func_ovl13_02_800434C0(&spA0);
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
        func_ovl13_02_8004CA70(D_ovl13_02_8004D580, 0x170, 0);
        spA0 = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0);
        spA4 = 500.0f;
        spA8 = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8);
        func_ovl13_02_80044F0C(&spA0, 0xB4, 20.0f);
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
        spA8 = 0.0f;
        spA4 = 0.0f;
        spA0 = 0.0f;
        sp94 = 0.0f;
        sp98 = 30.0f;
        sp9C = 100.0f;
        func_ovl13_02_8004CB90(&sp94, &spA0);
        spA0 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
        spA4 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
        spA8 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
        func_ovl13_02_800434C0(&spA0);
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
        if (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
            do {
                func_ovl13_02_8004CD90();
            } while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40));
        }
    }
}

void func_ovl13_02_80048504(void) {
    UnkStructA *sp8C;
    f32 sp80[3];
    f32 sp74[3];
    f32 sp68[3];
    UnkStructA *temp_s1;
    UnkStructA *temp_s2;
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv1;
    f32 var_ft4;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_v0;
    s32 var_v0_2;

    temp_s2 = func_ovl13_02_8004CC20(0x183, 0x11080000, 0xD0, NULL);
    temp_s1 = func_ovl13_02_8004CC20(0x182, 0x01080000, 0x60, NULL);
    if (func_ovl13_02_8004CFD0(0x418) != 0) {
        func_ovl13_02_8004CBF8(temp_s1, 0x800);
    } else {
        func_ovl13_02_8004CBF8(temp_s1, 0x8400);
    }
    sp8C = func_ovl13_02_8004CC30(temp_s1);
    sp74[2] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + -450.0f;
    sp74[0] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp74[1] = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    func_ovl13_02_8004CB88(&sp74[0], &D_ovl13_02_8004DC90, &sp68[0]);
    if (func_ovl13_02_8004CF08(1) != 0) {
        var_ft4 = (f32) ((f64) sp68[0] + (func_ovl13_02_8004CF00() * 15.0));
    } else {
        var_ft4 = (f32) ((f64) sp68[0] - (func_ovl13_02_8004CF00() * 15.0));
    }
    sp68[0] = var_ft4;
    sp68[1] = 0.0f;
    sp68[2] = 300.0f;
    func_ovl13_02_8004CB90(&sp68[0], &sp80[0]);
    temp_s2->unk40->unk10 = sp80[0] + sp74[0];
    temp_s2->unk40->unk14 = sp74[1];
    temp_s2->unk40->unk18 = sp80[2] + sp74[2];
    temp_s2->unk40->unk36 = 0xFF;
    temp_s1->unk40->unk10 = sp80[0] + sp74[0];
    temp_s1->unk40->unk14 = sp74[1];
    temp_s1->unk40->unk18 = sp80[2] + sp74[2];
    temp_s1->unk40->unk36 = 0x80;
    temp_s1->unk68 = (f32) ((func_ovl13_02_8004CF00() * 30.0) + 30.0);
    sp68[2] = (f32) ((func_ovl13_02_8004CF00() * 5.0) + 5.0);
    func_ovl13_02_8004CB90(&sp68[0], &sp80[0]);
    var_s0 = 0;
loop_7:
    if (var_s0 < 0x14) {
        func_ovl13_02_8004564C(temp_s2, var_s0, 0x14, 2.5f, 5.0f);
    } else {
        func_ovl13_02_8004CC00(temp_s2, 0x01000000);
    }
    temp_v0 = temp_s1->unk40;
    temp_v0->unk10 += sp80[0];
    temp_v0_2 = temp_s1->unk40;
    temp_v0_2->unk18 += sp80[2];
    func_ovl13_02_8004CC78(temp_s1);
    var_v0 = 0;
    if (temp_s1->unk40->unk14 <= func_ovl13_02_8004C220()) {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        if (temp_s1->unk68 == 0.0f) {
            func_ovl13_02_8004CC10(sp8C);
        } else if (func_ovl13_02_8004CBA8(temp_s1, 3) != 0) {
            func_ovl13_02_8004CD90();
        } else {
            func_ovl13_02_8004CD90();
            var_s0 += 1;
            goto loop_7;
        }
    }
    func_ovl13_02_8004CC00(temp_s1, 0x800);
    var_v0_2 = 0;
    if (temp_s1->unk40->unk14 <= func_ovl13_02_8004C220()) {
        var_v0_2 = 1;
    }
    if (var_v0_2 != 0) {
        func_ovl13_02_800484B4(temp_s1, 0x3FFFF);
        func_ovl13_02_8004CC00(temp_s1, 0x01000000);
        func_ovl13_02_8004CD90();
    } else {
        var_s0_2 = 0;
        func_ovl13_02_8004CC00(temp_s1, 0x3FFFF);
        do {
            temp_fs0 = (f32) var_s0_2 / 20.0f;
            temp_fs1 = temp_fs0 * 180.0f;
            temp_fv1 = (2.0f * func_ovl13_02_8004CEF0(temp_fs1)) + 1.0f;
            temp_s1->unk40->unk28 = temp_fv1;
            temp_s1->unk40->unk30 = temp_fv1;
            temp_s1->unk40->unk2C = func_ovl13_02_8004CEF8(temp_fs1) + 0.1f;
            temp_s1->unk40->unk36 = (s16) (s32) ((1.0f - temp_fs0) * 128.0f);
            func_ovl13_02_8004CD90();
            var_s0_2 += 1;
        } while (var_s0_2 != 0x14);
    }
    func_ovl13_02_8004CC10(temp_s1);
    func_ovl13_02_8004CC10(temp_s2);
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_800484B4(UnkStructA *arg0, s32 arg1) {
    func_ovl13_02_8004CC00(arg0, 0x01000000);
    func_ovl13_02_80043098(0xB3, arg0);
    func_ovl13_02_8004CD48(func_ovl13_02_800460C0, arg0, 0, 0, 0x150);
}

void func_ovl13_02_800480EC(s32 arg0) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x08000000);
    func_ovl13_02_8004511C();
    func_ovl13_02_8004CA70(D_ovl13_02_8004D608, 0x170, 0);
    sp44 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp4C = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    sp48 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    func_ovl13_02_800430CC(&sp44, 0x1E, 1);
    sp44 = M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 0);
    sp48 = 500.0f;
    sp4C = M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 8);
    func_ovl13_02_80044F0C(&sp44, 0xF0, 10.0f);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    func_ovl13_02_8004CB00(D_ovl13_02_8004DE3C);
    func_ovl13_02_8004CA98(0x20);
    func_ovl13_02_8004CAC0(0x42480000);
    D_ovl13_02_8004DE50->unk50 = 10.0f;
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
    sp44 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0);
    sp48 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 4) + 5000.0f;
    sp4C = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8);
    func_ovl13_02_800430CC((f32 *)0x3F7FBE77, (s32) &sp44, 0x3C);
    sp44 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp48 = func_ovl13_02_8004C220() + 10.0f;
    sp4C = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    func_ovl13_02_80044F0C(&sp44, 0xF, 20.0f);
    func_ovl13_02_8004CFC8(0x41E);
    func_ovl13_02_8004CFC8(0x41F);
    func_ovl13_02_8004CFC0(0x41A);
    func_ovl13_02_80047EEC();
    func_ovl13_02_8004CB00(NULL);
    func_ovl13_02_8004CAA0(0x20);
    func_ovl13_02_8004CAC0(0x41200000);
    func_ovl13_02_80047C60(arg0);
    func_ovl13_02_8004799C();
    func_ovl13_02_8004CD48(func_ovl13_02_800446B0, NULL, 0, 0, 0x110);
    func_ovl13_02_8004CFC8(0x41A);
    func_ovl13_02_8004CA70(D_ovl13_02_8004D6D4, 0x170, 0);
    sp44 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp48 = 500.0f;
    sp4C = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    func_ovl13_02_80044F0C(&sp44, 0x1E, 20.0f);
    func_ovl13_02_8004CFC0(0x41E);
    func_ovl13_02_8004362C(0);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x0C000000);
    sp44 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp4C = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    sp48 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    func_ovl13_02_800430CC(&sp44, 0x3C, 1);
    sp44 = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0);
    sp48 = 500.0f;
    sp4C = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8);
    func_ovl13_02_80044F0C(&sp44, 0xF0, 20.0f);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    func_ovl13_02_8004CA90();
    sp4C = 0.0f;
    sp48 = 0.0f;
    sp44 = 0.0f;
    sp38 = 0.0f;
    sp3C = 30.0f;
    sp40 = 100.0f;
    func_ovl13_02_8004CB90(&sp38, &sp44);
    sp44 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp48 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    sp4C += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    func_ovl13_02_800434C0(&sp44);
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
    func_ovl13_02_80043040(D_ovl13_02_8004DE3C);
}

void func_ovl13_02_80047EEC(void) {
    f32 temp_fs3;
    f32 temp_fv1;
    f32 var_fs0;
    f32 var_fv0;
    s32 var_s0;
    s32 var_s1;

    func_ovl13_02_8004362C(2);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    D_ovl13_02_8004DEE4 = 55.0f;
    D_ovl13_02_8004DEE8 = 0.0f;
    temp_fs3 = D_ovl13_02_8004DED8;
    var_s0 = 0;
    var_s1 = 0;
    var_fs0 = 0.0f;
    do {
        D_ovl13_02_8004DED8 = (func_ovl13_02_8004CEF0(var_fs0) * (((f32) var_s0 / 60.0f) * 45.0f)) + temp_fs3;
        temp_fv1 = var_fs0 + 12.0f;
        if (temp_fv1 >= 360.0f) {
            var_fs0 = temp_fv1 - 360.0f;
        } else {
            if (temp_fv1 < 0.0f) {
                var_fv0 = temp_fv1 + 360.0f;
            } else {
                var_fv0 = temp_fv1;
            }
            var_fs0 = var_fv0;
        }
        if ((func_ovl13_02_8004C220() <= D_ovl13_02_8004DE3C->unk40->unk14) && (var_s1 == 0)) {
            var_s1 = 1;
            func_ovl13_02_8004CD48(func_ovl13_02_80045460, NULL, 0, 0, 0x150);
            func_ovl13_02_80043098(0xE6, D_ovl13_02_8004DE3C);
        }
        func_ovl13_02_8004CD90();
        var_s0 += 1;
    } while (var_s0 != 0x3C);
    D_ovl13_02_8004DED8 = temp_fs3;
}

void func_ovl13_02_80047C60(s32 arg0) {
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *temp_v0_2;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv1;
    s32 var_s0;
    s32 var_s5;

    func_ovl13_02_8004362C(3);
    D_ovl13_02_8004DEEC *= 0.1f;
    temp_fs2 = D_ovl13_02_8004DEF0 / 30.0f;
    func_ovl13_02_80043098(0xDE, D_ovl13_02_8004DE3C);
    var_s5 = 0;
    if (arg0 > 0) {
        do {
            D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 = 0.0f;
            func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
            temp_fs3 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
            func_ovl13_02_8004CD68(5);
            var_s0 = 0;
loop_3:
            temp_v0 = D_ovl13_02_8004DE3C->unk40->unk48->unk4;
            temp_v0->unk4 += temp_fs2;
            temp_v0_2 = D_ovl13_02_8004DE3C->unk40->unk48->unk4;
            temp_fv1 = temp_v0_2->unk4;
            if (D_ovl13_02_8004DEF0 < temp_fv1) {
                temp_v0_2->unk4 = temp_fv1 - D_ovl13_02_8004DEF0;
            }
            temp_fv0 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - 12.0f;
            if (temp_fv0 >= 360.0f) {
                D_ovl13_02_8004DEDC = temp_fv0 - 360.0f;
            } else {
                if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) < 12.0f) {
                    var_fv1 = temp_fv0 + 360.0f;
                } else {
                    var_fv1 = temp_fv0;
                }
                M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = var_fv1;
            }
            func_ovl13_02_8004CD90();
            var_s0 += 1;
            if (var_s0 != 0x1E) {
                goto loop_3;
            }
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = temp_fs3;
            func_ovl13_02_8004CD48(func_ovl13_02_80044AB4, func_ovl13_02_80044CC8(), 0, 0, 0x110);
            var_s5 += 1;
        } while (var_s5 != arg0);
    }
    D_ovl13_02_8004DEEC *= 10.0f;
}

void func_ovl13_02_8004799C(void) {
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *temp_v0_2;
    f32 temp_fs3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fv0;

    func_ovl13_02_8004362C(4);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x0C000000);
    D_ovl13_02_8004DE50->unk50 = 40.0f;
    temp_fs3 = D_ovl13_02_8004DEF0 / 60.0f;
    if (D_ovl13_02_8004DEE4 != 0.0f) {
        do {
            temp_v0 = D_ovl13_02_8004DE3C->unk40->unk48->unk4;
            temp_v0->unk4 += temp_fs3;
            temp_v0_2 = D_ovl13_02_8004DE3C->unk40->unk48->unk4;
            temp_fv1 = temp_v0_2->unk4;
            if (D_ovl13_02_8004DEF0 < temp_fv1) {
                temp_v0_2->unk4 = temp_fv1 - D_ovl13_02_8004DEF0;
            }
            if (!(M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) <= (70.0f + 6.0f)) || !((70.0f - 6.0f) <= M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4))) {
                temp_fv1_2 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - 6.0f;
                if (temp_fv1_2 >= 360.0f) {
                    D_ovl13_02_8004DEDC = temp_fv1_2 - 360.0f;
                } else {
                    if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) < 6.0f) {
                        var_fv0 = temp_fv1_2 + 360.0f;
                    } else {
                        var_fv0 = temp_fv1_2;
                    }
                    M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = var_fv0;
                }
            }
            func_ovl13_02_8004CD90();
        } while (D_ovl13_02_8004DEE4 != 0.0f);
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
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    s32 sp12C;
    f32 sp124;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp104;
    s32 spFC;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *var_v1;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_t4;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s7;
    s32 var_t5;

    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x08000000);
    func_ovl13_02_8004511C();
    sp138 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    sp130 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp134 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    func_ovl13_02_800430CC(&sp130, 0x1E, 1);
    func_ovl13_02_8004CA70(&D_ovl13_02_8004D8B0, 0x170, 0);
    sp130 = M2C_FIELD(&D_ovl13_02_8004DFC0, f32 *, 0);
    sp134 = 500.0f;
    sp138 = M2C_FIELD(&D_ovl13_02_8004DFC0, f32 *, 8);
    func_ovl13_02_80044F0C(&sp130, 0x3C, 10.0f);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    sp138 = 0.0f;
    sp134 = 0.0f;
    sp130 = 0.0f;
    sp13C = 0.0f;
    sp140 = 400.0f;
    sp144 = 100.0f;
    func_ovl13_02_8004CB90(&sp13C, &sp130);
    sp130 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp134 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    sp138 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    func_ovl13_02_800434C0(&sp130);
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
    if (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
        do {
            func_ovl13_02_8004CD90();
        } while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40));
    }
    func_ovl13_02_8004362C(5);
    func_ovl13_02_8004CFC8(0x41E);
    func_ovl13_02_8004CFC0(0x41D);
    func_ovl13_02_8004CFC0(0x41C);
    func_ovl13_02_8004CBF8(M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18), 0x30);
    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk38 = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk34 = 100.0f;
    if (func_ovl13_02_8004CFD0(0x418) != 0) {
        M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk38 *= 0.6f;
        M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk34 *= 0.6f;
    }
    sp12C = 0;
    if (arg0 > 0) {
        var_s7 = spFC;
        do {
            if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) >= 360.0f) {
                M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) -= 360.0f;
            } else {
                if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) < 0.0f) {
                    var_fv1 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) + 360.0f;
                } else {
                    var_fv1 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0);
                }
                M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) = var_fv1;
            }
            func_ovl13_02_800430CC(&D_ovl13_02_8004DC90, 0xA, 0);
            func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
            D_ovl13_02_8004DE3C->unk40->unk48->unk4->unk4 = 0.0f;
            D_ovl13_02_8004DEF4 = 0.0f;
            temp_fs0 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
            D_ovl13_02_8004DEB0.unkC = 0.5f;
            D_ovl13_02_8004DEB0.unk8 = 0.5f;
            D_ovl13_02_8004DEB0.unk0 = 2;
            D_ovl13_02_8004DE98.unkC = 0.5f;
            D_ovl13_02_8004DE98.unk8 = 0.5f;
            D_ovl13_02_8004DE98.unk0 = 2;
            D_ovl13_02_8004DE80.unkC = 0.5f;
            D_ovl13_02_8004DE80.unk8 = 0.5f;
            D_ovl13_02_8004DE80.unk0 = 2;
            D_ovl13_02_8004DEB0.unk10 = 0.999f;
            D_ovl13_02_8004DE98.unk10 = 0.999f;
            D_ovl13_02_8004DE80.unk10 = 0.999f;
            sp104 = M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0)->unk50;
            func_ovl13_02_8004D2D0(0xDE);
            var_v1 = D_ovl13_02_8004DE3C->unk40;
            if (!(var_v1->unkC & 0x40)) {
loop_13:
                M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = (f32) (temp_fs0 - (func_ovl13_02_8004CEF0((var_v1->unk48->unk4->unk4 / D_ovl13_02_8004DEF0) * 180.0f) * 45.0f));
                temp_v0 = func_ovl13_02_800461E0();
                var_s7 = temp_v0;
                if (temp_v0 != 0) {
                    func_ovl13_02_8004CFC8(0x41D);
                    func_ovl13_02_8004CFC8(0x41C);
                    func_ovl13_02_8004CFC0(0x419);
                    func_ovl13_02_800467D8(var_s7);
                    sp12C = arg0;
                } else {
                    func_ovl13_02_8004CD90();
                    var_v1 = D_ovl13_02_8004DE3C->unk40;
                    if (!(var_v1->unkC & 0x40)) {
                        goto loop_13;
                    }
                }
            }
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = temp_fs0;
            if (var_s7 == 0) {
                sp110 = M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x1C), void **, 0x40), f32 *, 0x10);
                var_s0 = 0;
                sp114 = M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x1C), void **, 0x40), f32 *, 0x14);
                sp118 = M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x1C), void **, 0x40), f32 *, 0x18);
                func_ovl13_02_8004CB88(&sp110, &D_ovl13_02_8004DC90, &sp11C);
                var_fv0 = sp124;
                if (var_fv0 <= 700.0f) {
                    var_fv0 = 700.0f;
                }
                if (var_fv0 > 1400.0f) {
                    var_fv0 = 1400.0f;
                }
                temp_fv0 = (var_fv0 - 700.0f) * 0.01f;
                sp124 = temp_fv0;
                var_t5 = (u32) temp_fv0;
                switch (var_t5) {
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
                M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk5C = 0.0f;
loop_35:
                temp_v0_2 = M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk40;
                if ((temp_v0_2->unk14 <= (D_ovl13_02_8004DD14 + 50.0f)) && ((func_ovl13_02_8004C268((s32) (temp_v0_2->unk10 * 0.01f), 1, (s32) (temp_v0_2->unk18 * 0.01f)) & 0xF) == 1)) {
                    func_ovl13_02_8004CB20(10.0f, 10.0f, 10.0f);
                    func_ovl13_02_8004CB10(0x1E);
                    func_ovl13_02_80043098(0xDF, M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18));
                } else {
                    M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk5C = M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk40->unk14;
                    func_ovl13_02_8004CD90();
                    var_s0 += 1;
                    if (var_s0 != 0x14) {
                        goto loop_35;
                    }
                }
                if (func_ovl13_02_8004CFD0(0x418) != 0) {
                    func_ovl13_02_8004CD68(0x1E);
                } else {
                    func_ovl13_02_8004CD68(0xA);
                }
                M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0)->unk50 = sp104;
            }
            temp_t4 = sp12C + 1;
            sp12C = temp_t4;
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
        } while (temp_t4 < arg0);
        spFC = var_s7;
    }
    if (D_ovl13_02_8004DE24 > 0) {
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
        func_ovl13_02_8004CFC8(0x41D);
        func_ovl13_02_8004CFC8(0x41C);
        func_ovl13_02_8004CC00(M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18), 0x30);
        M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk38 = 0.0f;
        M2C_FIELD(&D_ovl13_02_8004DE50, UnkStructA **, 0x18)->unk34 = 150.0f;
        func_ovl13_02_8004CFC0(0x41E);
        func_ovl13_02_8004362C(0);
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x0C000000);
        func_ovl13_02_8004511C();
        func_ovl13_02_8004CA70(&D_ovl13_02_8004D8F4, 0x170, 0);
        sp130 = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0);
        sp134 = 500.0f;
        sp138 = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8);
        func_ovl13_02_80044F0C(&sp130, 0x3C, 20.0f);
        func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
        sp140 = 30.0f;
        sp138 = 0.0f;
        sp134 = 0.0f;
        sp130 = 0.0f;
        sp13C = 0.0f;
        sp144 = 100.0f;
        func_ovl13_02_8004CB90(&sp13C, &sp130);
        sp130 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
        sp134 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
        sp138 += M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
        func_ovl13_02_800434C0(&sp130);
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x08000000);
        if (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40)) {
            do {
                func_ovl13_02_8004CD90();
            } while (!(D_ovl13_02_8004DE3C->unk40->unkC & 0x40));
        }
    }
}

void func_ovl13_02_80046D7C(s32 arg0, f32 arg1) {
    f32 temp_fs0;
    s32 var_s0;

    var_s0 = 0;
    temp_fs0 = (arg1 - D_ovl13_02_8004DE50->unk50) / (f32) arg0;
    if (arg0 > 0) {
        do {
            D_ovl13_02_8004DE50->unk50 += temp_fs0;
            func_ovl13_02_8004CD90();
            var_s0 += 1;
        } while (var_s0 != arg0);
    }
}

void func_ovl13_02_80046B34(s32 arg0) {
    f32 sp5C;
    UnkStructA *temp_a0;
    UnkStructA_40 *var_v0;
    f32 temp_fs0;
    f32 temp_fs5;
    f32 temp_fv1;
    f32 var_fs1;
    f32 var_fv0;

    func_ovl13_02_8004362C(6);
    var_fs1 = 0.0f;
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    temp_fs5 = 2.0f * (360.0f / D_ovl13_02_8004DEF0);
    D_ovl13_02_8004DE80.unk8 = 0.8f;
    D_ovl13_02_8004DE98.unk8 = 0.8f;
    D_ovl13_02_8004DEB0.unk8 = 0.8f;
    D_ovl13_02_8004DE80.unkC = 0.11f;
    D_ovl13_02_8004DE98.unkC = 0.11f;
    D_ovl13_02_8004DEB0.unkC = 0.11f;
    D_ovl13_02_8004DE80.unk10 = 0.99999f;
    D_ovl13_02_8004DE98.unk10 = 0.99999f;
    D_ovl13_02_8004DEB0.unk10 = 0.99999f;
    sp5C = D_ovl13_02_8004DED8;
    func_ovl13_02_8004D2D0(0xDD);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    temp_a0 = D_ovl13_02_8004DE3C;
    var_v0 = temp_a0->unk40;
    if (!(var_v0->unkC & 0x40)) {
        do {
            temp_fs0 = (1.0f - (var_v0->unk48->unk4->unk4 / D_ovl13_02_8004DEF0)) * 30.0f;
            temp_fv1 = var_fs1 + temp_fs5;
            D_ovl13_02_8004DED8 = (func_ovl13_02_8004CEF0(var_fs1) * temp_fs0) + sp5C;
            if (temp_fv1 >= 360.0f) {
                var_fs1 = temp_fv1 - 360.0f;
            } else {
                if (temp_fv1 < 0.0f) {
                    var_fv0 = temp_fv1 + 360.0f;
                } else {
                    var_fv0 = temp_fv1;
                }
                var_fs1 = var_fv0;
            }
            func_ovl13_02_8004CD90();
            var_v0 = D_ovl13_02_8004DE3C->unk40;
        } while (!(var_v0->unkC & 0x40));
    }
    D_ovl13_02_8004DE24 -= arg0;
    D_ovl13_02_8004DED8 = sp5C;
    func_ovl13_02_8004CC00(temp_a0, 0x04000000);
}

void func_ovl13_02_800467D8(s32 arg0) {
    f32 sp90;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    UnkStructA *temp_a2;
    UnkStructA_40 *var_v1;
    f32 temp_fs0;
    f32 temp_fs5;
    f32 temp_ft4;
    f32 temp_fv1;
    f32 var_fs1;
    f32 var_fv0;
    s32 var_s0;
    s32 var_s1;

    func_ovl13_02_8004362C(7);
    var_fs1 = 0.0f;
    temp_fs5 = 2.0f * (360.0f / D_ovl13_02_8004DEF0);
    var_s1 = 0;
    var_s0 = 0;
    sp90 = D_ovl13_02_8004DE3C->unk40->unk28;
    do {
        sp80 = D_ovl13_02_8004DE70->unk40->unk10;
        temp_ft4 = D_ovl13_02_8004DE70->unk40->unk14 + 400.0f;
        sp84 = temp_ft4;
        sp88 = D_ovl13_02_8004DE70->unk40->unk18 + 400.0f;
        sp80 += D_ovl13_02_8004D938[func_ovl13_02_8004CF08(5)];
        sp84 = temp_ft4 + D_ovl13_02_8004D938[func_ovl13_02_8004CF08(5)];
        if (var_s0 >= 0x11) {
            var_s0 = 0;
            func_ovl13_02_8004D1A0(0xE, &sp80, 0);
        }
        func_ovl13_02_8004CD90();
        var_s1 += 1;
        var_s0 += 1;
    } while (var_s1 != 0x78);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    func_ovl13_02_8004CD68((s32) (D_ovl13_02_8004DEF0 * 0.3f));
    func_ovl13_02_80043098(0xB, D_ovl13_02_8004DE3C);
    func_ovl13_02_80043098(0xE3, D_ovl13_02_8004DE3C);
    func_ovl13_02_8004D2D0(0xDD);
    temp_a2 = D_ovl13_02_8004DE3C;
    var_v1 = temp_a2->unk40;
    if (!(var_v1->unkC & 0x40)) {
        do {
            temp_fs0 = (1.0f - (var_v1->unk48->unk4->unk4 / D_ovl13_02_8004DEF0)) * 1.5f;
            temp_fv1 = var_fs1 + temp_fs5;
            D_ovl13_02_8004DE3C->unk40->unk28 = (func_ovl13_02_8004CEF0(var_fs1) * temp_fs0) + sp90;
            if (temp_fv1 >= 360.0f) {
                var_fs1 = temp_fv1 - 360.0f;
            } else {
                if (temp_fv1 < 0.0f) {
                    var_fv0 = temp_fv1 + 360.0f;
                } else {
                    var_fv0 = temp_fv1;
                }
                var_fs1 = var_fv0;
            }
            func_ovl13_02_8004CD90();
            var_v1 = D_ovl13_02_8004DE3C->unk40;
        } while (!(var_v1->unkC & 0x40));
    }
    D_ovl13_02_8004DE24 -= arg0;
    temp_a2->unk40->unk28 = sp90;
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
}

void func_ovl13_02_8004640C(void) {
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB4;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    UnkStructA *temp_a0;
    UnkStructA_40 *var_v0;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fs1;
    f32 var_fs1_2;
    f32 var_fs2;
    s32 var_s0;

    func_ovl13_02_8004D2E8();
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
    temp_fs0 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
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
    var_fs1 = 0.0f;
    func_ovl13_02_8004D2D0(0xE7);
    var_s0 = 0;
    do {
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = (f32) (temp_fs0 - var_fs1);
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + -10.0f);
        var_fs1 += 4.0f;
        func_ovl13_02_8004CD90();
        var_s0 += 1;
    } while (var_s0 != 0x14);
    func_ovl13_02_8004CFC8(0x41F);
    func_ovl13_02_8004631C();
    func_ovl13_02_8004362C(8);
    func_ovl13_02_8004CBF8(D_ovl13_02_8004DE3C, 0x04000000);
    temp_a0 = D_ovl13_02_8004DE3C;
    spC4 = (360.0f / D_ovl13_02_8004DEF0) * 1.5f;
    D_ovl13_02_8004DE80.unk0 = 2;
    D_ovl13_02_8004DE98.unk0 = 2;
    D_ovl13_02_8004DEB0.unk0 = 2;
    D_ovl13_02_8004DE80.unk8 = 0.3f;
    D_ovl13_02_8004DE98.unk8 = 0.3f;
    D_ovl13_02_8004DEB0.unk8 = 0.3f;
    spA4 = 80.0f / D_ovl13_02_8004DEF0;
    D_ovl13_02_8004DE80.unkC = 0.1f;
    D_ovl13_02_8004DE98.unkC = 0.1f;
    D_ovl13_02_8004DEB0.unkC = 0.1f;
    D_ovl13_02_8004DE80.unk10 = 0.9f;
    D_ovl13_02_8004DE98.unk10 = 0.9f;
    D_ovl13_02_8004DEB0.unk10 = 0.9f;
    spB4 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
    spC0 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0);
    spBC = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 8);
    var_v0 = temp_a0->unk40;
    var_fs2 = 0.0f;
    var_fs1_2 = 0.0f;
    if (!(var_v0->unkC & 0x40)) {
        do {
            M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + -10.0f);
            temp_fs0_2 = (1.0f - (var_v0->unk48->unk4->unk4 / D_ovl13_02_8004DEF0)) * 15.0f;
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = (f32) (spB4 + var_fs1_2);
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) = (func_ovl13_02_8004CEF0(var_fs2) * temp_fs0_2) + spC0;
            temp_fv1 = var_fs2 + spC4;
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 8) = (f32) ((func_ovl13_02_8004CEF0(var_fs2) * temp_fs0_2) + spBC);
            if (temp_fv1 >= 360.0f) {
                var_fs2 = temp_fv1 - 360.0f;
            } else {
                if (temp_fv1 < 0.0f) {
                    var_fa0 = temp_fv1 + 360.0f;
                } else {
                    var_fa0 = temp_fv1;
                }
                var_fs2 = var_fa0;
            }
            temp_fv0 = var_fs1_2 + spA4;
            if (temp_fv0 >= 360.0f) {
                var_fs1_2 = temp_fv0 - 360.0f;
            } else {
                if (temp_fv0 < 0.0f) {
                    var_fa0_2 = temp_fv0 + 360.0f;
                } else {
                    var_fa0_2 = temp_fv0;
                }
                var_fs1_2 = var_fa0_2;
            }
            func_ovl13_02_8004CD90();
            var_v0 = D_ovl13_02_8004DE3C->unk40;
        } while (!(var_v0->unkC & 0x40));
    }
    func_ovl13_02_8004CC00(temp_a0, 0x04000000);
    spA0 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 100.0f;
    sp98 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp9C = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
    func_ovl13_02_800430CC(&sp98, 0x3C, 1);
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
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x18), UnkStructA_40 **, 0x40), 0x181, 0, 0);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x18), UnkStructA_40 **, 0x40), 0x181, 1, 1);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x14), UnkStructA_40 **, 0x40), 0x17D, 0, 0);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x14), UnkStructA_40 **, 0x40), 0x17D, 1, 1);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x10), UnkStructA_40 **, 0x40), 0x17F, 0, 0);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x10), UnkStructA_40 **, 0x40), 0x17F, 1, 1);
}

s32 func_ovl13_02_800461E0(void) {
    s32 sp2C;
    UnkStructA *sp28;
    f32 sp1C;
    UnkStructA *temp_v0;
    s32 var_v1;

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
    void *spA8;                                     /* compiler-managed */
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp74;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_fp;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;

    var_fp = 0;
    spA8 = NULL;
    var_s4 = 0;
    var_s2 = 0;
    var_s3 = 0;
    sp6C = 0;
    temp_v1 = func_ovl13_02_8004CF08(0x3C) + 0x1E;
    sp64 = temp_v1;
    sp68 = temp_v1;
loop_1:
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
    var_fp += 1;
    D_ovl13_02_8004DE48->unk40->unk14 = func_ovl13_02_8004C220();
    D_ovl13_02_8004DE48->unk40->unk18 = D_ovl13_02_8004DE3C->unk40->unk18;
    if ((var_fp >= 6) && (func_ovl13_02_8004CFD0(0x41F) != 0)) {
        func_ovl13_02_8004CD48(func_ovl13_02_80045724, spA8, 0, 0, 0x150);
        var_fp = 0;
        spA8 = (s32) spA8 ^ 1;
    }
    if (func_ovl13_02_8004CFD0(0x41E) != 0) {
        func_ovl13_02_800459D0(&D_ovl13_02_8004DEF0, &D_ovl13_02_8004DEF4, &D_ovl13_02_8004DEC8, &D_ovl13_02_8004DED8, D_ovl13_02_8004DEFC, D_ovl13_02_8004DF04, D_ovl13_02_8004DF0C, D_ovl13_02_8004DF00, D_ovl13_02_8004DF08, D_ovl13_02_8004DF10);
    }
    D_ovl13_02_8004DEF4 += D_ovl13_02_8004DEF8;
    if (D_ovl13_02_8004DEF0 <= D_ovl13_02_8004DEF4) {
        D_ovl13_02_8004DEF4 -= D_ovl13_02_8004DEF0;
    }
    if ((func_ovl13_02_8004CFD0(0x41D) != 0) && (var_s4 == 0) && (D_ovl13_02_8004DE24 > 0)) {
        D_ovl13_02_8004DE34 = func_ovl13_02_800458D8(D_ovl13_02_8004DE40);
        D_ovl13_02_8004DE34 |= func_ovl13_02_800458D8(D_ovl13_02_8004DE44);
        if (func_ovl13_02_8004CFD0(0x41C) != 0) {
            temp_t8 = D_ovl13_02_8004DE24 - D_ovl13_02_8004DE34;
            D_ovl13_02_8004DE24 = temp_t8;
            if (temp_t8 < 0) {
                D_ovl13_02_8004DE24 = 0;
            }
            var_s4 = 0x78;
            if ((func_ovl13_02_8004CFD0(0x439) != 0) && (D_ovl13_02_8004DE24 <= 0)) {
                D_ovl13_02_8004DE24 = 1;
            }
            D_ovl13_02_8004DE34 = 0;
        }
    }
    if (var_s4 != 0) {
        var_s4 -= 1;
    }
    temp_v0 = func_ovl13_02_800458D8(D_ovl13_02_8004DE68);
    if ((temp_v0 != 0) && (D_ovl13_02_8004DE2C > 0) && (var_s2 == 0)) {
        D_ovl13_02_8004DE2C -= temp_v0;
        var_v1 = D_ovl13_02_8004DE2C;
        if (var_v1 < 0) {
            D_ovl13_02_8004DE2C = 0;
            var_v1 = 0;
        }
        var_s2 = 0x78;
        if (var_v1 <= 0) {
            func_ovl13_02_8004591C();
            func_ovl13_02_8004CC00(D_ovl13_02_8004DE68, 0x3FFFF);
            func_ovl13_02_8004CCC8(D_ovl13_02_8004DE68, &sp74);
            func_ovl13_02_8004CF78(&sp74);
            var_s2 = 0x78;
        }
    }
    if (var_s2 != 0) {
        if (var_s2 >= 0x6F) {
            sp8C = D_ovl13_02_8004DE68->unk40->unk10;
            sp90 = D_ovl13_02_8004DE68->unk40->unk14;
            sp94 = D_ovl13_02_8004DE68->unk40->unk18;
            func_ovl13_02_8004D1A0(8, &sp8C, 0);
        }
        var_s2 -= 1;
    }
    temp_v0_2 = func_ovl13_02_800458D8(D_ovl13_02_8004DE4C);
    if ((temp_v0_2 != 0) && (D_ovl13_02_8004DE28 > 0) && (var_s3 == 0)) {
        D_ovl13_02_8004DE28 -= temp_v0_2;
        var_v1_2 = D_ovl13_02_8004DE28;
        if (var_v1_2 < 0) {
            D_ovl13_02_8004DE28 = 0;
            var_v1_2 = 0;
        }
        var_s3 = 0x78;
        if (var_v1_2 <= 0) {
            func_ovl13_02_80045888();
            func_ovl13_02_8004CC00(D_ovl13_02_8004DE4C, 0x8010);
            func_ovl13_02_8004CCC8(D_ovl13_02_8004DE4C, &sp74);
            func_ovl13_02_8004CF78(&sp74);
            var_s3 = 0x78;
        }
    }
    if (var_s3 != 0) {
        if (var_s3 >= 0x6F) {
            sp80 = D_ovl13_02_8004DE4C->unk40->unk10;
            sp84 = D_ovl13_02_8004DE4C->unk40->unk14;
            sp88 = D_ovl13_02_8004DE4C->unk40->unk18;
            func_ovl13_02_8004D1A0(8, &sp80, 0);
        }
        var_s3 -= 1;
    }
    if ((func_ovl13_02_800445C8() != 0) && (sp6C == 0)) {
        sp6C = 1;
        func_ovl13_02_8004CF78(&D_ovl13_02_8004DC90);
    }
    var_v0 = 0;
    if ((M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + 500.0f) <= func_ovl13_02_8004C220()) {
        var_v0 = 1;
    }
    if ((var_v0 != 0) && (D_ovl13_02_8004DE24 != 0)) {
        temp_t4 = sp68 + 1;
        sp68 = temp_t4;
        if (sp64 < temp_t4) {
            sp68 = 0;
            sp64 = func_ovl13_02_8004CF08(0x3C) + 0x1E;
            func_ovl13_02_80043098(0xF0, D_ovl13_02_8004DE3C);
        }
    }
    func_ovl13_02_8004CD90();
    goto loop_1;
}

void func_ovl13_02_800459D0(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    f32 sp1C;
    f32 temp_fv0;

    temp_fv0 = (*arg1 / *arg0) * 360.0f;
    sp1C = temp_fv0;
    D_ovl13_02_8004DE3C->unk40->unk10 = (func_ovl13_02_8004CEF0(temp_fv0 * arg4) * arg7) + M2C_FIELD(arg2, f32 *, 0);
    D_ovl13_02_8004DE3C->unk40->unk14 = (func_ovl13_02_8004CEF0(sp1C * arg5) * arg8) + M2C_FIELD(arg2, f32 *, 4);
    D_ovl13_02_8004DE3C->unk40->unk20 = (func_ovl13_02_8004CEF0(sp1C * arg6) * arg9) + *arg3;
}

void func_ovl13_02_8004591C(void) {
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x18), UnkStructA_40 **, 0x40), 0x181, 0, 2);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x18), UnkStructA_40 **, 0x40), 0x181, 1, 3);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x14), UnkStructA_40 **, 0x40), 0x17D, 0, 2);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x14), UnkStructA_40 **, 0x40), 0x17D, 1, 3);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x10), UnkStructA_40 **, 0x40), 0x17F, 0, 2);
    func_ovl13_02_8004C908(M2C_FIELD(M2C_FIELD(&D_ovl13_02_8004DE50, void **, 0x10), UnkStructA_40 **, 0x40), 0x17F, 1, 3);
}

s32 func_ovl13_02_800458D8(UnkStructA *arg0) {
    s32 temp_v1;
    s32 var_a0;
    s32 var_v0;

    temp_v1 = arg0->unk10;
    if (!(temp_v1 & 0x40)) {
        return 0;
    }
    var_a0 = 1;
    if (temp_v1 & 0x2000) {
        var_a0 = 2;
    }
    var_v0 = var_a0;
    if (temp_v1 & 0x4000) {
        var_v0 = var_a0 + 1;
    }
    return var_v0;
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
    var_s1 = 0;
    temp_v0->unk54 = 825.0f;
    do {
        func_ovl13_02_8004564C(temp_v0, var_s1, 0x1E, D_ovl13_02_8004DE74, D_ovl13_02_8004DE78);
        if (temp_s5 != NULL) {
            temp_v0->unk4C += 2.0f;
        } else {
            temp_v0->unk4C -= 2.0f;
        }
        temp_v0->unk54 -= 4.0f;
        func_ovl13_02_8004CD90();
        var_s1 += 1;
    } while (var_s1 != 0x1E);
    func_ovl13_02_8004CC10(temp_v0);
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_8004564C(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    f32 sp1C;
    f32 temp_fv0;

    temp_fv0 = (f32) arg1 / (f32) arg2;
    sp1C = temp_fv0;
    arg0->unk40->unk28 = func_ovl13_02_8004CEF0(temp_fv0 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl13_02_8004CEF0(sp1C * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - sp1C) * 63.0f) + 0x80;
}

void func_ovl13_02_80045460(void) {
    UnkStructA *objs[24];
    Vec3f a;
    Vec3f pos;
    s32 i;

    for (i = 0; i < 24; i++) {
        objs[i] = func_ovl13_02_8004CC20(-1, 0, 0xD0, NULL);
    }
    a.y = 0.0f;
    a.x = 0.0f;
    a.z = 800.0f;
    for (i = 0; i < 24; i++) {
        pos.x = 0.0f;
        pos.y = 0.0f;
        pos.z = 0.0f;
        func_ovl13_02_8004CB90(&a.x, &pos.x);
        objs[i]->unk40->unk10 = D_ovl13_02_8004DC90.x + pos.x;
        objs[i]->unk40->unk14 = D_ovl13_02_8004DC90.y + pos.y;
        objs[i]->unk40->unk18 = D_ovl13_02_8004DC90.z + pos.z;
        objs[i]->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0) + pos.x;
        objs[i]->unk40->unk14 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + pos.y;
        objs[i]->unk40->unk14 = func_ovl13_02_8004C220();
        objs[i]->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + pos.z;
        func_ovl13_02_8004CD48(func_ovl13_02_800460C0, objs[i], 0, 0, 0x150);
        a.x += 15.0f;
    }
    func_ovl13_02_8004CD90();
    for (i = 0; i < 24; i++) {
        func_ovl13_02_8004CC10(objs[i]);
    }
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_8004521C(void) {
    UnkStructA *objs[24];
    Vec3f a;
    Vec3f pos[24];
    s32 n;
    s32 i;
    s32 k;
    s32 wait;

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
    k = 0;
    for (i = 0, wait = 4; i != n; i++, wait++) {
        if (wait >= 4) {
            objs[k]->unk40->unk10 = pos[k].x + D_ovl13_02_8004DC90.x;
            objs[k]->unk40->unk14 = pos[k].y + D_ovl13_02_8004DC90.y;
            objs[k]->unk40->unk18 = pos[k].z + D_ovl13_02_8004DC90.z;
            objs[k]->unk40->unk10 = pos[k].x + M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
            objs[k]->unk40->unk14 = pos[k].y + M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
            objs[k]->unk40->unk18 = pos[k].z + M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
            func_ovl13_02_8004CD48(func_ovl13_02_800460C0, objs[k], 0, 0, 0x150);
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
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 temp_fs0;
    s32 var_s0;

    sp40 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
    sp44 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + -500.0f;
    sp48 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
    func_ovl13_02_8004CD48(func_ovl13_02_8004521C, (void *)0x43, 0, 0, 0x150);
    func_ovl13_02_800430CC(&sp40, 0x30, 1);
    func_ovl13_02_8004CFC8(0x41F);
    temp_fs0 = (500.0f - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4)) / 64.0f;
    func_ovl13_02_80043098(0xE5, D_ovl13_02_8004DE3C);
    var_s0 = 0;
    do {
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + temp_fs0);
        func_ovl13_02_8004CD90();
        var_s0 += 1;
    } while (var_s0 != 0x40);
}

void func_ovl13_02_80044F0C(f32 *arg0, s32 arg1, f32 arg2) {
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp58;
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *temp_v0_2;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_fa0;
    s32 var_s1;

    temp_fv1 = (f32) arg1;
    temp_fs1 = (M2C_FIELD(arg0, f32 *, 0) - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0)) / temp_fv1;
    sp58 = temp_fv1;
    temp_fs2 = (M2C_FIELD(arg0, f32 *, 4) - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4)) / temp_fv1;
    temp_fs3 = (M2C_FIELD(arg0, f32 *, 8) - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8)) / temp_fv1;
    func_ovl13_02_8004CB88(&D_ovl13_02_8004DEC8, arg0, &sp68);
    temp_fv0 = sp6C - 90.0f;
    if (temp_fv0 >= 360.0f) {
        sp6C = temp_fv0 - 360.0f;
    } else {
        if (sp6C < 90.0f) {
            var_fa0 = temp_fv0 + 360.0f;
        } else {
            var_fa0 = temp_fv0;
        }
        sp6C = var_fa0;
    }
    temp_fv0_2 = sp70 / sp58;
    sp70 = temp_fv0_2;
    func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x04000000);
    var_s1 = 0;
    if (arg1 > 0) {
        do {
            M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0) += temp_fs1;
            M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + temp_fs2);
            M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + temp_fs3);
            temp_v0 = D_ovl13_02_8004DE3C->unk40->unk48->unk4;
            temp_v0->unk4 += temp_fv0_2 / arg2;
            temp_v0_2 = D_ovl13_02_8004DE3C->unk40->unk48->unk4;
            temp_fv0_3 = temp_v0_2->unk4;
            if (D_ovl13_02_8004DEF0 < temp_fv0_3) {
                temp_v0_2->unk4 = temp_fv0_3 - D_ovl13_02_8004DEF0;
            }
            func_ovl13_02_8004CD90();
            var_s1 += 1;
        } while (var_s1 != arg1);
    }
}

void func_ovl13_02_80044E64(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = func_ovl13_02_8004C220();
    temp_fv1 = *arg0;
    if ((temp_fv1 + (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) - *arg1)) <= temp_fv0) {
        *arg1 = 0.0f;
        *arg0 = 0.0f;
        D_ovl13_02_8004DECC = temp_fv0;
        return;
    }
    M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) + temp_fv1);
    M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) - *arg1);
    *arg1 += *arg2;
}

s32 func_ovl13_02_80044CC8(void) {
    s32 i;
    s32 found;
    f32 min;
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
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    f32 *temp_s0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    s32 var_s0;
    void *temp_s4;

    temp_s4 = func_ovl13_02_8004CD70();
    temp_v0 = func_ovl13_02_8004CC20(0x184, 0x01000100, 0x50, NULL);
    temp_v0->unk30 = 4;
    temp_v0->unk34 = 6.0f;
    temp_v0->unk38 = 90.0f;
    temp_v0->unk40->unk10 = M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 0);
    temp_v0->unk40->unk14 = D_ovl13_02_8004DECC - 700.0f;
    temp_v0->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 8);
    temp_v0->unk40->unk20 = 180.0f;
    temp_s0 = &D_ovl13_02_8004DDB8[(s32) temp_s4].x;
    temp_fs1 = M2C_FIELD(temp_s0, f32 *, 0) - M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 0);
    temp_fs2 = (func_ovl13_02_8004C220() - temp_v0->unk40->unk14) / 120.0f;
    temp_fs3 = (M2C_FIELD(temp_s0, f32 *, 8) - M2C_FIELD(&D_ovl13_02_8004DF80, f32 *, 8)) / 120.0f;
    func_ovl13_02_80043098(0xE1, temp_v0);
    var_s0 = 0;
    do {
        temp_v0_2 = temp_v0->unk40;
        temp_v0_2->unk10 += temp_fs1 / 120.0f;
        temp_v0_3 = temp_v0->unk40;
        temp_v0_3->unk14 += temp_fs2;
        temp_v0_4 = temp_v0->unk40;
        temp_v0_4->unk18 += temp_fs3;
        temp_v0_5 = temp_v0->unk40;
        temp_v0_5->unk2C += 0.041666668f;
        if (var_s0 == 0x77) {
            func_ovl13_02_80044990((s32) temp_s4);
        }
        func_ovl13_02_8004CD90();
        var_s0 += 1;
    } while (var_s0 != 0xB4);
    func_ovl13_02_8004CC10(temp_v0);
    func_ovl13_02_8004CD58();
}

void func_ovl13_02_80044990(s32 arg0) {
    s32 step;
    s32 i;
    s32 said;

    if (D_ovl13_02_8004DC90.x <= D_ovl13_02_8004DDB8[arg0].x) {
        step = 1;
        i = arg0 + 1;
    } else {
        step = -1;
        i = arg0;
    }
    said = 0;
    for (; i < 10 && i >= 0; i += step) {
        if (D_ovl13_02_8004DD90[i] == 0) {
            if (said == 0) {
                said = 1;
                func_ovl13_02_80043098(0xE8, D_ovl13_02_8004DD68[i]);
            }
            func_ovl13_02_8004CD48(func_ovl13_02_8004A8E0, (void *) i, 0, 0, 0x150);
            D_ovl13_02_8004DD90[i] = 1;
        }
    }
}

void func_ovl13_02_800448E4(void) {
    UnkStructA *temp_v0;

    temp_v0 = func_ovl13_02_8004CC20(0x175, 0x80000, 0xD0, NULL);
    D_ovl13_02_8004DFAC = temp_v0;
    temp_v0->unk40->unk36 = 0xBF;
    func_ovl13_02_8004C940(D_ovl13_02_8004DFAC->unk40, 0, 0, 0x400, 0x40, 0x400);
    D_ovl13_02_8004DFAC->unk40->unk10 = D_ovl13_02_8004DD10;
    D_ovl13_02_8004DFAC->unk40->unk14 = func_ovl13_02_8004C220();
    M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 0) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 4) = 0.0f;
    M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 8) = 0.0f;
}

void func_ovl13_02_800446B0(void) {
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    f32 temp_fv0;
    f32 var_fv1;
    s32 var_s0;
    s32 var_s2;

    func_ovl13_02_8004CBF8(D_ovl13_02_8004DFAC, 0x01000000);
    D_ovl13_02_8004DFAC->unk40->unk18 = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8);
    D_ovl13_02_8004DFAC->unk40->unk2C = 0.2f;
    var_s2 = 0;
    var_s0 = 0;
    D_ovl13_02_8004DFBC = ((M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8) - 1000.0f) - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8)) / 300.0f;
    do {
        temp_v0 = D_ovl13_02_8004DFAC->unk40;
        temp_v0->unk18 += D_ovl13_02_8004DFBC;
        temp_v0_2 = D_ovl13_02_8004DFAC->unk40;
        temp_v0_2->unk2C += 0.004333333f;
        temp_fv0 = M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8);
        var_fv1 = D_ovl13_02_8004DFAC->unk40->unk18;
        if ((var_fv1 <= (temp_fv0 + 600.0f)) && (var_s2 == 0)) {
            var_s2 = 1;
            func_ovl13_02_8004D2D0(0xE2);
            var_fv1 = D_ovl13_02_8004DFAC->unk40->unk18;
        }
        if ((var_fv1 <= (temp_fv0 + 300.0f)) && ((temp_fv0 - 300.0f) <= var_fv1)) {
            M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 8) = -12.75f;
        } else {
            M2C_FIELD(&D_ovl13_02_8004DFB0, f32 *, 8) = 0.0f;
        }
        func_ovl13_02_8004CD90();
        var_s0 += 1;
    } while (var_s0 != 0x12C);
    func_ovl13_02_8004CC00(D_ovl13_02_8004DFAC, 0x01000000);
    func_ovl13_02_8004CD58();
}

static void func_ovl13_02_80044628(void) {
}

void func_ovl13_02_80044630(void) {
    s32 sp1C;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    func_ovl13_02_80044628();
    var_v1 = 0;
    if (D_ovl13_02_8004DE28 <= 0) {
        var_v1 = 1;
    }
    if (D_ovl13_02_8004DE2C <= 0) {
        var_v1 += 1;
    }
    sp1C = var_v1;
    var_v1_2 = var_v1;
    if (func_ovl13_02_8004CFD0(0x419) != 0) {
        var_v1_2 += 1;
    }
    sp1C = var_v1_2;
    var_v1_3 = var_v1_2;
    if (func_ovl13_02_800445C8() != 0) {
        var_v1_3 += 1;
    }
    M2C_FIELD(D_ovl13_02_8004DCDC, s32 *, 0x2C) = var_v1_3;
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
    f32 top;
    f32 bottom;
    s32 i;
    s32 best;
    f32 min;
    f32 d;
    f32 f;
    f32 a;
    u8 c;

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
    cur[1] = 0.0f;
    want[1] = 0.0f;
    cur[0] = 270.0f;
    want[0] = 270.0f;
    cur[2] = 2000.0f;
    want[2] = 2000.0f;
    tgt.y = objs[0]->unk40->unk14;
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
        cam.z = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + 1000.0f;
        cam.x = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0);
        cam.y = M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4);
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
        a = want[1] - 90.0f;
        cur[2] += (want[2] - cur[2]) * 0.1f;
        cur[1] = (a >= 360.0f) ? a - 360.0f : (want[1] < 90.0f) ? a + 360.0f : a;
        func_ovl13_02_8004CF10(cur[0], cur[1]);
        d = cur[2];
        if (d > 2000.0f) {
            d = 2000.0f;
        }
        f = 1.0f - (d / 2000.0f);
        c = (1.0f - f) * 128.0f;
        cur[2] = d;
        func_ovl13_02_8004D078((s32) (127.0f * f) + 0x80, c, c);
        func_ovl13_02_8004CD90();
    }
}

void func_ovl13_02_80043B64(f32 *arg0, f32 *arg1, f32 arg2, f32 *arg3) {
    f32 sp40;
    f32 sp3C;
    f32 sp24;
    f32 temp_ft5;
    f32 temp_ft5_2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    f32 var_ft4_2;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;

    func_ovl13_02_8004CB88(arg0, arg3, &sp3C);
    temp_fv0 = sp40 - 90.0f;
    if (temp_fv0 >= 360.0f) {
        sp40 = temp_fv0 - 360.0f;
    } else {
        if (sp40 < 90.0f) {
            var_fv1 = temp_fv0 + 360.0f;
        } else {
            var_fv1 = temp_fv0;
        }
        sp40 = var_fv1;
    }
    if (sp3C >= 0.0f) {
        if (sp3C <= 180.0f) {
            var_ft4 = sp3C;
        } else {
            goto block_10;
        }
    } else {
block_10:
        var_ft4 = (360.0f - sp3C) * -1.0f;
    }
    temp_ft5 = M2C_FIELD(arg1, f32 *, 0);
    if (temp_ft5 >= 0.0f) {
        if (temp_ft5 <= 180.0f) {
            var_fv1_2 = temp_ft5;
        } else {
            goto block_15;
        }
    } else {
block_15:
        var_fv1_2 = (360.0f - temp_ft5) * -1.0f;
    }
    temp_fv0_2 = var_ft4 - var_fv1_2;
    var_fa1 = temp_fv0_2;
    if (temp_fv0_2 > 180.0f) {
        var_fa1 = temp_fv0_2 - 360.0f;
    }
    if (var_fa1 < -180.0f) {
        var_fa1 += 360.0f;
    }
    if (var_fa1 >= 0.0f) {
        if (arg2 < var_fa1) {
            var_fa1 = arg2;
        }
    } else {
        temp_fv0_3 = arg2 * -1.0f;
        if (var_fa1 < temp_fv0_3) {
            var_fa1 = temp_fv0_3;
        }
    }
    if (sp40 >= 0.0f) {
        if (sp40 <= 180.0f) {
            var_ft4_2 = sp40;
            sp24 = temp_ft5;
        } else {
            goto block_29;
        }
    } else {
block_29:
        sp24 = temp_ft5;
        var_ft4_2 = (360.0f - sp40) * -1.0f;
    }
    temp_ft5_2 = M2C_FIELD(arg1, f32 *, 4);
    if (temp_ft5_2 >= 0.0f) {
        if (temp_ft5_2 <= 180.0f) {
            var_fv1_3 = temp_ft5_2;
        } else {
            goto block_34;
        }
    } else {
block_34:
        var_fv1_3 = (360.0f - temp_ft5_2) * -1.0f;
    }
    temp_fv0_4 = var_ft4_2 - var_fv1_3;
    var_fa0 = temp_fv0_4;
    if (temp_fv0_4 > 180.0f) {
        var_fa0 = temp_fv0_4 - 360.0f;
    }
    var_fv0 = arg2;
    if (var_fa0 < -180.0f) {
        var_fa0 += 360.0f;
    }
    if (var_fa0 >= 0.0f) {
        if (var_fv0 < var_fa0) {
            goto block_43;
        }
    } else {
        var_fv0 = arg2 * -1.0f;
        if (var_fa0 < var_fv0) {
block_43:
            var_fa0 = var_fv0;
        }
    }
    M2C_FIELD(arg1, f32 *, 0) = sp24 + var_fa1;
    M2C_FIELD(arg1, f32 *, 4) = (f32) (temp_ft5_2 + var_fa0);
}

void func_ovl13_02_800439DC(void) {
    f32 sp18;

    if (func_ovl13_02_8004CFD0(0x400) == 0) {
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 8) - 4000.0f);
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4) = 500.0f;
        M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 0) = M2C_FIELD(&D_ovl13_02_8004DF18, f32 *, 0);
        func_ovl13_02_8004CA38(2300.0f, 1000.0f, -1800.0f);
        func_ovl13_02_8004CA28(1);
        func_ovl13_02_8004CA58(305.0f, 45.0f, 1707.337f);
        sp18 = func_ovl13_02_8004CBA0(&D_ovl13_02_8004DD10, &D_ovl13_02_8004DEC8);
        func_ovl13_02_8004CAE8(M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 0), M2C_FIELD(&D_ovl13_02_8004DD10, f32 *, 8), sp18, func_ovl13_02_8004CBA0(&D_ovl13_02_8004DD10, &D_ovl13_02_8004DEC8) + 100.0f);
        func_ovl13_02_8004CAD0(0.0f);
        func_ovl13_02_8004CAA0(0x10);
        func_ovl13_02_8004CFC8(0x41F);
        D_ovl13_02_8004DFE0.unk0 = 0x186;
        D_ovl13_02_8004DFE0.unk4 = 1;
        D_ovl13_02_8004DFE0.unk8 = 1;
        D_ovl13_02_8004DFE0.unkC[0] = 0.0f;
        D_ovl13_02_8004DFE0.unkC[1] = 1.7948718f;
        D_ovl13_02_8004DFE0.unkC[2] = 8.717949f;
        D_ovl13_02_8004DFE0.unk18[0] = 0.0f;
        D_ovl13_02_8004DFE0.unk18[1] = 0.0f;
        D_ovl13_02_8004DFE0.unk18[2] = 0.0f;
        D_ovl13_02_8004DFE0.unk24[0] = -0.77698714f;
        D_ovl13_02_8004DFE0.unk3C = 0;
        D_ovl13_02_8004DFE0.unk40 = 0;
        D_ovl13_02_8004DFE0.unk24[2] = 0.0f;
        D_ovl13_02_8004DFE0.unk30[0] = 0.0f;
        D_ovl13_02_8004DFE0.unk30[1] = 0.0f;
        D_ovl13_02_8004DFE0.unk30[2] = 0.0f;
        D_ovl13_02_8004DFE0.unk24[1] = -0.033815384f;
    }
}

void func_ovl13_02_80043970(void) {
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

void func_ovl13_02_80043698(void) {
    f32 var_fs0;
    s32 var_s0;
    s32 var_s1;

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
        var_fs0 = 22.222221f;
        var_s0 = 0;
        do {
            M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) = (f32) (M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 8) + var_fs0);
            var_fs0 += (22.222221f / 360.0f) * -1.0f;
            if (var_s0 == 0x78) {
                func_ovl13_02_8004CA70(&D_ovl13_02_8004DFE0, 0x170, 0);
            }
            func_ovl13_02_8004CD90();
            var_s0 += 1;
        } while (var_s0 != 0x168);
        func_ovl13_02_8004D0A0(1);
        var_s1 = 0xBF;
        func_ovl13_02_8004D0A8(0xBF);
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
        do {
            func_ovl13_02_8004D0A8(var_s1);
            func_ovl13_02_8004CD90();
            var_s1 -= 8;
        } while (var_s1 >= 0);
        func_ovl13_02_8004D0A0(0);
        func_ovl13_02_8004CC00(D_ovl13_02_8004DE3C, 0x0C000000);
    }
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
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 temp_fs1;
    s32 var_s0;

    sp48 = M2C_FIELD(arg0, f32 *, 0);
    sp4C = M2C_FIELD(arg0, f32 *, 4);
    sp50 = M2C_FIELD(arg0, f32 *, 8);
    func_ovl13_02_800430CC(&sp48, 0x30, 1);
    temp_fs1 = (D_ovl13_02_8004DD14 - M2C_FIELD(&D_ovl13_02_8004DEC8, f32 *, 4)) / 64.0f;
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
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp34;
    f32 sp30;
    s32 sp2C;
    f32 sp1C;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fa1;
    f32 var_fa1_2;
    f32 var_fa1_3;
    f32 var_ft4;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    f32 var_fv1_4;
    f32 var_fv1_5;
    f32 var_fv1_6;
    f32 var_fv1_7;
    f32 var_fv1_8;
    s32 var_v1;

    if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) >= 360.0f) {
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) -= 360.0f;
    } else {
        if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) < 0.0f) {
            var_fv1 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) + 360.0f;
        } else {
            var_fv1 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0);
        }
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) = var_fv1;
    }
    if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) >= 360.0f) {
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - 360.0f);
    } else {
        if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) < 0.0f) {
            var_fv1_2 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) + 360.0f;
        } else {
            var_fv1_2 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
        }
        M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = var_fv1_2;
    }
    sp44 = 0.0f;
    sp3C = 0.0f;
    sp40 = 0.0f;
    func_ovl13_02_8004CB88(&D_ovl13_02_8004DEC8, arg0, &sp3C);
    if (sp3C >= 0.0f) {
        if (sp3C <= 180.0f) {
            var_fa1 = sp3C;
        } else {
            goto block_16;
        }
    } else {
block_16:
        var_fa1 = (360.0f - sp3C) * -1.0f;
    }
    if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) >= 0.0f) {
        if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) <= 180.0f) {
            var_fv1_3 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0);
        } else {
            goto block_21;
        }
    } else {
block_21:
        var_fv1_3 = (360.0f - M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0)) * -1.0f;
    }
    sp1C = (f32) arg1;
    sp30 = (var_fa1 - var_fv1_3) / sp1C;
    if (arg2 != 0) {
        temp_fv0 = sp40 - 90.0f;
        if (temp_fv0 >= 360.0f) {
            var_ft4 = temp_fv0 - 360.0f;
        } else {
            if (sp40 < 90.0f) {
                var_fv1_4 = temp_fv0 + 360.0f;
            } else {
                var_fv1_4 = temp_fv0;
            }
            var_ft4 = var_fv1_4;
        }
        if (!(var_ft4 >= 0.0f) || !(var_ft4 <= 180.0f)) {
            var_ft4 = (360.0f - var_ft4) * -1.0f;
        }
        temp_ft4 = var_ft4 * -1.0f;
        if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) >= 0.0f) {
            if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) <= 180.0f) {
                var_fv1_5 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
            } else {
                goto block_36;
            }
        } else {
block_36:
            var_fv1_5 = (360.0f - M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4)) * -1.0f;
        }
        temp_fv0_2 = temp_ft4 - var_fv1_5;
        sp40 = temp_ft4;
        if (temp_fv0_2 >= 360.0f) {
            var_fa1_2 = temp_fv0_2 - 360.0f;
        } else {
            if (temp_fv0_2 < 0.0f) {
                var_fv1_6 = temp_fv0_2 + 360.0f;
            } else {
                var_fv1_6 = temp_fv0_2;
            }
            var_fa1_2 = var_fv1_6;
        }
        if (!(var_fa1_2 >= 0.0f) || !(var_fa1_2 <= 180.0f)) {
            var_fa1_2 = (360.0f - var_fa1_2) * -1.0f;
        }
        sp34 = var_fa1_2 / sp1C;
    }
    var_fa1_3 = sp34;
    var_v1 = 0;
    if (arg1 > 0) {
        do {
            M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) += sp30;
            if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) >= 360.0f) {
                M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) -= 360.0f;
            } else {
                if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) < 0.0f) {
                    var_fv1_7 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) + 360.0f;
                } else {
                    var_fv1_7 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0);
                }
                M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 0) = var_fv1_7;
            }
            if (arg2 != 0) {
                M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) + var_fa1_3);
                if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) >= 360.0f) {
                    M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = (f32) (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) - 360.0f);
                } else {
                    if (M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) < 0.0f) {
                        var_fv1_8 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) + 360.0f;
                    } else {
                        var_fv1_8 = M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4);
                    }
                    M2C_FIELD(&D_ovl13_02_8004DED8, f32 *, 4) = var_fv1_8;
                }
            }
            sp2C = var_v1;
            sp34 = var_fa1_3;
            func_ovl13_02_8004CD90();
            var_v1 += 1;
        } while (var_v1 != arg1);
    }
}

void func_ovl13_02_80043098(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *temp_v0;

    temp_v0 = arg1->unk40;
    func_ovl13_02_8004D2F0(arg0, temp_v0->unk10, temp_v0->unk14, temp_v0->unk18);
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
