/*
 * NON_MATCHING: ovl_14_01's game object, complete; not in the ROM.
 * flags: -O3
 * differing words: us 5225, eu 5225, jp 5225
 *
 * The text is the same in every version (only jp's ZeroJump numbers
 * differ). 47 of 89 functions match. m2c output (with the ZeroJump
 * prototypes of the other drafts, scratch/newovl2/protos.h, and the
 * file's own in own.h) made to compile, then tuned by hand
 * (scratch/newovl2/r/).
 *
 * Order: every function and stub comes out at the original's place
 * (8004B908 and 8004B820 defined below 8004B500, 800431C4 and 80043250
 * above 800432D8, which pulls them with the static 800431F8). Statics:
 * 800431F8 (takes the object in $s0), the stubs 80043680, 8004B38C/94,
 * 8004B680/88/90 (K&R empty statics inlined in the next function) and the
 * nine unused ones 8004BB04-8004BB44. 80045008 is not a stub: it is
 * 80044FDC's own `jr ra` (a branch target). 8004697C calls 80045124,
 * which IDO inlines (non-static, same file).
 *
 * Data: .data (the two Vec3f[5] paths at 8004D190/8004D1CC, a word at
 * 8004D208) and .bss defined; the four command strings are literals.
 * The bss types are partly guesses (Vec3f groups, the 3-link chains
 * D_8004D560/5A0); fillers keep the addresses. 8004D62C-8004D640 are six
 * separate f32s (the original stores each with its own lui).
 *
 * What still differs, in large: 80046CE8, 80048DE8, 80046004, 800457F0,
 * 8004A11C, 800432D8, 800445D8, 80047E44 (m2c's temporaries and pointer
 * walks: frames too big; m2c's split f32 triples are Vec3f locals where
 * that helped). 8004A914 is clean C (212: D_8004D4F0 and D_8004D6C8 go
 * through an address register in the original, the angle Vec3f sits 4
 * bytes lower). 80049814 is clean C (185: the original keeps l in its home
 * slot and p in $s0 from the start; frame 64 vs 40).
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define WRAP360(x) ((x) >= 360.0f ? (x) - 360.0f : ((x) < 0.0f ? (x) + 360.0f : (x)))

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Link_ovl14_01;

void func_ovl14_01_8004BE98(s32); /* 0xC00 */
void func_ovl14_01_8004BEA8(s32 *); /* 0xC02 */
void func_ovl14_01_8004BEB0(s32); /* 0xD00 */ /* also: void (s32, UnkStructA_40 **) x1 */
f32 func_ovl14_01_8004BEC0(void); /* 0xD02 */
s32 func_ovl14_01_8004BF00(s32); /* 0xD0A */
void func_ovl14_01_8004BF80(void (*)(UnkStructA *)); /* 0xE03 */ /* also: void (void (*)(Obj_0D02 *)) x1; void (void (*)(Obj_0D04 *)) x1; void (void (*)(Obj_0D06 *)) x1 */
void func_ovl14_01_8004BFB8(void); /* 0xF05 */
void func_ovl14_01_8004BFD0(void (*)(UnkStructA *)); /* 0xF08 */
s32 *func_ovl14_01_8004BFE8(void); /* 0xF0B */ /* also: s32 * (void) x3; Save_ovl0B_02 *(void) x1; UnkStruct_ovl0B_05_80046820 *(void) x1 */
void func_ovl14_01_8004C000(s32); /* 0xF0E */
void func_ovl14_01_8004C010(s32); /* 0xF10 */
void func_ovl14_01_8004C048(void); /* 0x1000 */
void func_ovl14_01_8004C058(void *); /* 0x1002 */
s32 func_ovl14_01_8004C078(void); /* 0x1006 */
void func_ovl14_01_8004C080(s32, void *); /* 0x1007 */
void func_ovl14_01_8004C088(s32); /* 0x1008 */
void func_ovl14_01_8004C0A0(const char *); /* 0x100B */
void func_ovl14_01_8004C0A8(void); /* 0x100C */
UnkStructA * func_ovl14_01_8004C0D8(s32); /* 0x1012 */ /* also: Obj02 * (s32) x1; Obj03 * (s32) x1; UnkStruct_ovl0A_05_80048CA0 *(s32) x1 */
void func_ovl14_01_8004C138(s32); /* 0x101E */
void func_ovl14_01_8004C5A0(UnkStructA_40 *, s32); /* 0x1505 */ /* also: void (Obj *, s32) x1; void (UnkStruct_ovl0A_02_80047A20_Inner *, s32) x1; void (UnkStruct_ovl0A_03_80047E20_Inner *, s32) x1 */
void func_ovl14_01_8004C5A8(UnkStructA_40 *, s32, s32, s32); /* 0x1506 */ /* also: void (Obj *, s32, s32, s32) x1; void (UnkStruct_ovl0A_02_80047A20_Inner *, s32, s32, s32) x1; void (UnkStruct_ovl0A_03_80047E20_Inner *, s32, s32, s32) x1 */
void func_ovl14_01_8004C5C0(UnkStructA_40 *, s32, s32); /* 0x1509 */ /* also: void (Obj *, s32, s32) x1; void (UnkStruct_ovl0A_02_80047A20_Inner *, s32, s32) x1; void (UnkStruct_ovl0A_03_80047E20_Inner *, s32, s32) x1 */
f32 func_ovl14_01_8004C5D8(UnkStructA_40 *, s32); /* 0x150C */ /* also: f32 (UnkStruct_ovl0A_02_80047A20_Inner *, s32) x1; f32 (UnkStruct_ovl0A_03_80047E20_Inner *, s32) x1; f32 (UnkStruct_ovl0A_05_80048CA0_Inner *, s32) x1 */
void func_ovl14_01_8004C6D8(f32, f32, f32); /* 0x1704 */
void func_ovl14_01_8004C6F8(f32, f32, f32); /* 0x1708 */
void func_ovl14_01_8004C700(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl14_01_8004C740(s32); /* 0x1711 */
void func_ovl14_01_8004C750(s32); /* 0x1713 */
void func_ovl14_01_8004C778(Vec3f *); /* 0x1718 */
void func_ovl14_01_8004C788(f32, f32, f32, f32); /* 0x171A */
void func_ovl14_01_8004C790(f32, f32); /* 0x171B */
void func_ovl14_01_8004C798(f32, f32, f32, f32); /* 0x171C */
void func_ovl14_01_8004C7F0(f32 *); /* 0x1727 */
void func_ovl14_01_8004C828(Vec3f *, Vec3f *, Vec3f *); /* 0x1803 */
void func_ovl14_01_8004C830(Vec3f *, Vec3f *); /* 0x1804 */
s32 func_ovl14_01_8004C848(UnkStructA *, s32); /* 0x1807 */ /* also: s32 (Obj_0D02 *, s32) x1; s32 (Obj_0D04 *, s32) x1; s32 (Obj_0D06 *, s32) x1 */
s32 func_ovl14_01_8004C860(s32, s32); /* 0x180A */
void func_ovl14_01_8004C868(UnkStructA *, s32); /* 0x180B */ /* also: void (Obj_0D02 *, s32) x1; void (Obj05 *, s32) x1; void (Obj_0D03 *, s32) x1 */
void func_ovl14_01_8004C880(UnkStructA *, UnkStructA *, Link_ovl14_01 *, s32); /* 0x180E */ /* also: void (UnkStructA *, UnkStructA *, Link_ovl13_01 *, s32) x1 */
void func_ovl14_01_8004C890(s32); /* 0x1810 */
void func_ovl14_01_8004C898(UnkStructA *, s32); /* 0x1811 */ /* also: void (Obj02 *, s32) x1; void (Obj03 *, s32) x1; void (UnkStruct_ovl0A_05_80048CA0 *, s32) x1 */
void func_ovl14_01_8004C8A0(UnkStructA *, s32); /* 0x1812 */ /* also: void (Obj02 *, s32) x1; void (Obj03 *, s32) x1; void (UnkStruct_ovl0A_05_80048CA0 *, s32) x1 */
void func_ovl14_01_8004C8B0(UnkStructA *); /* 0x1814 */ /* also: void (Obj02 *) x1; void (Obj03 *) x1; void (UnkStruct_ovl0A_05_80048CA0 *) x1 */
UnkStructA *func_ovl14_01_8004C8C0(s32, s32, s32, UnkStructA *); /* 0x1816 */ /* also: Obj02 * (s32, s32, s32, Obj02 *) x1; Obj03 * (s32, s32, s32, Obj03 *) x1; UnkStruct_ovl0A_05_80048CA0 *(s32, s32, s32, UnkStruct_ovl0A_05_80048CA0 *) x1 */
UnkStructA *func_ovl14_01_8004C8D0(UnkStructA *); /* 0x1818 */ /* also: void (Obj02 *) x1; void (Obj03 *) x1; Obj_0D02 *(Obj_0D02 *) x1 */
UnkStructA *func_ovl14_01_8004C8F0(s32, s32, UnkStructA *); /* 0x181C */
void func_ovl14_01_8004C918(UnkStructA *); /* 0x1821 */ /* also: void (Obj02 *) x1; void (Obj_0D02 *) x1; void (Obj_0D03 *) x1 */
UnkStructA *func_ovl14_01_8004C920(UnkStructA *, s32); /* 0x1822 */
void func_ovl14_01_8004C968(UnkStructA *, f32 *); /* 0x182B */ /* also: void (Obj02 *, f32 *) x1; void (Obj03 *, f32 *) x1; void (UnkStruct_ovl0A_05_80048CA0 *, f32 *) x1 */
void func_ovl14_01_8004C9A8(UnkStructA *); /* 0x1833 */
void func_ovl14_01_8004C9C8(s32 *); /* 0x1837 */
void func_ovl14_01_8004C9D0(void); /* 0x1838 */
void func_ovl14_01_8004C9D8(void); /* 0x1839 */
s32 func_ovl14_01_8004C9E8(void (*)(), void *, s32, s32, s32); /* 0x1900 */ /* also: void (void (*)(void), void *, s32, s32, s32) x6; s32 (void (*)(void), void *, s32, s32, s32) x4; s32 (void (*)(), void *, void *, s32, s32) x1 */
void func_ovl14_01_8004C9F8(void); /* 0x1902 */
void func_ovl14_01_8004CA08(s32); /* 0x1904 */ /* also: s32 (s32) x1 */
void *func_ovl14_01_8004CA10(void); /* 0x1905 */ /* also: Obj02 * (void) x1; Obj03 * (void) x1; UnkStruct_ovl0A_05_80048CA0 *(void) x1 */
s32 func_ovl14_01_8004CA30(void); /* 0x1909 */ /* also: void (void) x8 */
f32 func_ovl14_01_8004CB90(f32); /* 0x1D00 */
f32 func_ovl14_01_8004CB98(f32); /* 0x1D01 */
f64 func_ovl14_01_8004CBA0(void); /* 0x1D02 */
s32 func_ovl14_01_8004CBA8(s32); /* 0x1D03 */
void func_ovl14_01_8004CBB0(f32, f32); /* 0x1D04 */
void func_ovl14_01_8004CC00(void); /* 0x1D0E */
void func_ovl14_01_8004CC08(void); /* 0x1D0F */
void func_ovl14_01_8004CC10(void); /* 0x1D10 */
void func_ovl14_01_8004CC18(f32 *); /* 0x1D11 */
void func_ovl14_01_8004CC20(void); /* 0x1D12 */
s32 func_ovl14_01_8004CC50(s32); /* 0x1E04 */
void func_ovl14_01_8004CC60(s32); /* 0x1E06 */
void func_ovl14_01_8004CC68(s32); /* 0x1E07 */
s32 func_ovl14_01_8004CC70(s32); /* 0x1E08 */
void func_ovl14_01_8004CCE8(s32, s32, s32, f32); /* 0x2004 */
void func_ovl14_01_8004CD30(s32); /* 0x2200 */
void func_ovl14_01_8004CD40(s32); /* 0x2202 */
void func_ovl14_01_8004CD48(s32); /* 0x2203 */
void func_ovl14_01_8004CE40(s32, f32 *, s32); /* 0x2601 */ /* also: s32 (s32, f32 *, s32) x3; void (s32, f32 *, Obj_0D02 *) x1; void (s32, f32 *, Obj_0D03 *) x1 */
void func_ovl14_01_8004CE60(void *); /* 0x2701 */ /* also: void (UnkStruct_ovl0A_05_80048CA0 *) x1 */
s32 func_ovl14_01_8004CF70(s32); /* 0x2B00 */ /* also: s32 (s32) x6 */
void func_ovl14_01_8004CF80(s32); /* 0x2B02 */
void func_ovl14_01_8004CF88(void); /* 0x2B03 */
s32 func_ovl14_01_8004CF90(s32, f32, f32, f32); /* 0x2B04 */ /* also: void (s32, s32, s32, s32) x7 */
void func_ovl14_01_8004CF98(s32, f32 *); /* 0x2B05 */
void func_ovl14_01_8004CFA0(s32); /* 0x2B06 */
s32 func_ovl14_01_8004D000(void *, s32, s32, s32, f32); /* 0x2C03 */
void func_ovl14_01_8004D0E8(void); /* 0x3000 */
void func_ovl14_01_8004D0F0(void); /* 0x3001 */

/* .bss */
Vec3f D_ovl14_01_8004D4A0;
u8 D_ovl14_01_8004D4AC[4];
Vec3f D_ovl14_01_8004D4B0;
s32 D_ovl14_01_8004D4BC;
u8 D_ovl14_01_8004D4C0[4];
s32 D_ovl14_01_8004D4C4;
s32 D_ovl14_01_8004D4C8;
u8 D_ovl14_01_8004D4CC[4];
Vec3f D_ovl14_01_8004D4D0;
Vec3f *D_ovl14_01_8004D4DC;
s32 * D_ovl14_01_8004D4E0;
s32 D_ovl14_01_8004D4E4;
s32 D_ovl14_01_8004D4E8;
s32 D_ovl14_01_8004D4EC;
s32 D_ovl14_01_8004D4F0;
u8 D_ovl14_01_8004D4F4[4];
Vec3f D_ovl14_01_8004D4F8;
u8 D_ovl14_01_8004D504[4];
Vec3f D_ovl14_01_8004D508;
u8 D_ovl14_01_8004D514[4];
Vec3f D_ovl14_01_8004D518;
u8 D_ovl14_01_8004D524[4];
s32 D_ovl14_01_8004D528;
u8 D_ovl14_01_8004D52C[4];
s32 D_ovl14_01_8004D530;
f32 D_ovl14_01_8004D534;
f32 D_ovl14_01_8004D538;
s32 D_ovl14_01_8004D53C;
s32 D_ovl14_01_8004D540;
s32 D_ovl14_01_8004D544;
s32 D_ovl14_01_8004D548;
s32 D_ovl14_01_8004D54C;
s32 D_ovl14_01_8004D550;
s32 D_ovl14_01_8004D554;
s32 D_ovl14_01_8004D558;
u8 D_ovl14_01_8004D55C[4];
Link_ovl14_01 D_ovl14_01_8004D560[3];
u8 D_ovl14_01_8004D59C[4];
Link_ovl14_01 D_ovl14_01_8004D5A0[3];
UnkStructA * D_ovl14_01_8004D5DC;
UnkStructA * D_ovl14_01_8004D5E0;
UnkStructA * D_ovl14_01_8004D5E4;
UnkStructA * D_ovl14_01_8004D5E8;
UnkStructA * D_ovl14_01_8004D5EC;
UnkStructA * D_ovl14_01_8004D5F0;
UnkStructA * D_ovl14_01_8004D5F4;
UnkStructA * D_ovl14_01_8004D5F8;
u8 D_ovl14_01_8004D5FC[4];
UnkStructA *D_ovl14_01_8004D600[5];
s32 D_ovl14_01_8004D614;
UnkStructA *D_ovl14_01_8004D618[5];
f32 D_ovl14_01_8004D62C;
f32 D_ovl14_01_8004D630;
f32 D_ovl14_01_8004D634;
f32 D_ovl14_01_8004D638;
f32 D_ovl14_01_8004D63C;
f32 D_ovl14_01_8004D640;
s32 D_ovl14_01_8004D644;
s32 D_ovl14_01_8004D648;
s32 D_ovl14_01_8004D64C;
s32 D_ovl14_01_8004D650;
u8 D_ovl14_01_8004D654[4];
s32 D_ovl14_01_8004D658[5];
s32 D_ovl14_01_8004D66C;
s32 D_ovl14_01_8004D670[5];
f32 D_ovl14_01_8004D684;
f32 D_ovl14_01_8004D688;
u8 D_ovl14_01_8004D68C[4];
Vec3f D_ovl14_01_8004D690;
u8 D_ovl14_01_8004D69C[4];
Vec3f D_ovl14_01_8004D6A0;
u8 D_ovl14_01_8004D6AC[4];
Vec3f D_ovl14_01_8004D6B0;
s32 D_ovl14_01_8004D6BC;
u32 D_ovl14_01_8004D6C0;
s32 D_ovl14_01_8004D6C4;
s32 D_ovl14_01_8004D6C8;
s32 D_ovl14_01_8004D6CC;
Vec3f D_ovl14_01_8004D6D0;
s32 D_ovl14_01_8004D6DC;
Vec3f D_ovl14_01_8004D6E0;
u8 D_ovl14_01_8004D6EC[4];
Vec3f D_ovl14_01_8004D6F0[8];
s32 D_ovl14_01_8004D750[4];

void func_ovl14_01_80043010(UnkStructA **arg0, Link_ovl14_01 *arg1);
s32 func_ovl14_01_800431C4(s32 arg0, UnkStructA *arg1);
static void func_ovl14_01_800431F8(UnkStructA *obj);
void func_ovl14_01_80043250(s32 arg0);
void func_ovl14_01_800432D8(void);
void func_ovl14_01_80043624(void);
void func_ovl14_01_80043688(UnkStructA **arg0, Link_ovl14_01 *arg1);
void func_ovl14_01_800437B8(void);
void func_ovl14_01_800438D8(void);
void func_ovl14_01_800439AC(Vec3f *arg0, UnkStructA *arg1);
void func_ovl14_01_80043B20(void);
void func_ovl14_01_80043CC0(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_ovl14_01_80043D98(void);
void func_ovl14_01_80043F10(void);
void func_ovl14_01_80044104(void);
void func_ovl14_01_80044540(Vec3f *arg0);
void func_ovl14_01_800445D8(void);
void func_ovl14_01_800449C0(void);
void func_ovl14_01_80044B38(Vec3f *arg0, s32 arg1);
void func_ovl14_01_80044D50(Vec3f *arg0, f32 arg1);
s32 func_ovl14_01_80044FDC(void);
void func_ovl14_01_80045010(void);
void func_ovl14_01_80045124(void *arg0);
void func_ovl14_01_8004515C(void);
void func_ovl14_01_80045474(void);
void func_ovl14_01_800455AC(void);
void func_ovl14_01_800457F0(void);
void func_ovl14_01_80045D7C(void);
void func_ovl14_01_80045FA0(void *arg0);
void func_ovl14_01_80045FD8(void);
void func_ovl14_01_80046004(s32 arg0);
void func_ovl14_01_8004654C(void);
void func_ovl14_01_80046648(UnkStructA **arg0, Link_ovl14_01 *arg1);
void func_ovl14_01_800467C0(UnkStructA **arg0, Link_ovl14_01 *arg1);
void func_ovl14_01_8004697C(void);
s32 func_ovl14_01_80046AE8(void);
void func_ovl14_01_80046B98(s32 arg0, f32 arg1);
s32 func_ovl14_01_80046C38(void);
void func_ovl14_01_80046CE8(void);
s32 func_ovl14_01_80047344(void);
void func_ovl14_01_8004739C(s32 arg0);
void func_ovl14_01_80047594(Vec3f *arg0, s32 arg1);
void func_ovl14_01_8004769C(s32 arg0);
void func_ovl14_01_800476F8(f32 arg0, f32 arg1, s32 arg2);
void func_ovl14_01_80047730(s32 arg0);
void func_ovl14_01_80047798(s32 arg0);
void func_ovl14_01_800477EC(s32 arg0);
void func_ovl14_01_80047978(UnkStructA *arg0);
void func_ovl14_01_80047A10(void);
void func_ovl14_01_80047CDC(void);
void func_ovl14_01_80047E44(void);
void func_ovl14_01_800481B8(s32 arg0);
void func_ovl14_01_80048454(void);
void func_ovl14_01_800487A8(void);
void func_ovl14_01_8004882C(void);
void func_ovl14_01_800488B0(void);
void func_ovl14_01_80048ABC(UnkStructA **arg0, Link_ovl14_01 *arg1);
void func_ovl14_01_80048CE8(Vec3f *arg0, s32 arg1);
void *func_ovl14_01_80048D48(void *arg0);
void func_ovl14_01_80048DE8(s32 arg0);
void func_ovl14_01_80049368(s32 arg0);
void func_ovl14_01_800494C8(void);
void func_ovl14_01_80049618(void);
void func_ovl14_01_80049814(s32 arg0, UnkStructA **arg1, Link_ovl14_01 *arg2);
void func_ovl14_01_80049B70(void);
void func_ovl14_01_80049BC0(void);
void func_ovl14_01_80049BE0(u32 arg0, s32 arg1);
void func_ovl14_01_80049CF4(void);
void func_ovl14_01_80049F2C(void);
void func_ovl14_01_80049FA8(void);
s32 func_ovl14_01_8004A0CC(UnkStructA *arg0);
void func_ovl14_01_8004A11C(void);
void func_ovl14_01_8004A4E0(void);
void func_ovl14_01_8004A760(void);
void func_ovl14_01_8004A914(void);
void func_ovl14_01_8004AF68(void);
void func_ovl14_01_8004B024(UnkStructA *arg0);
void func_ovl14_01_8004B26C(void);
void func_ovl14_01_8004B2A8(void);
void func_ovl14_01_8004B39C(void);
void func_ovl14_01_8004B3EC(void);
void func_ovl14_01_8004B4B4(void);
void func_ovl14_01_8004B500(void);
void func_ovl14_01_8004B698(void);
void func_ovl14_01_8004B820(s32 arg0);
void func_ovl14_01_8004B908(void);
void func_ovl14_01_8004B9CC(void);
void func_ovl14_01_8004BA48(f32 arg0);
void func_ovl14_01_8004BA90(f32 arg0, f32 arg1, f32 arg2);
void func_ovl14_01_8004BAEC(void);

/* .data */
Vec3f D_ovl14_01_8004D190[5] = {
    { 1852.0f, 500.0f, 350.0f },
    { 1852.0f, 440.22833f, 355.22934f },
    { 1852.0f, 191.1796f, 377.01746f },
    { 1852.0f, 191.1796f, 437.01746f },
    { 1851.9995f, 190.63454f, 857.0171f }
};
Vec3f D_ovl14_01_8004D1CC[5] = {
    { 2848.0f, 500.0f, 350.0f },
    { 2848.0f, 440.22833f, 355.22934f },
    { 2847.999f, 191.1796f, 377.01746f },
    { 2847.999f, 191.1796f, 437.01746f },
    { 2847.9988f, 190.63454f, 857.0171f }
};
s32 D_ovl14_01_8004D208 = 0;

/* unused: the stubs IDO -O3 leaves after the tail */
static void func_ovl14_01_8004BB04(void) {
}

static void func_ovl14_01_8004BB0C(void) {
}

static void func_ovl14_01_8004BB14(void) {
}

static void func_ovl14_01_8004BB1C(void) {
}

static void func_ovl14_01_8004BB24(void) {
}

static void func_ovl14_01_8004BB2C(void) {
}

static void func_ovl14_01_8004BB34(void) {
}

static void func_ovl14_01_8004BB3C(void) {
}

static void func_ovl14_01_8004BB44(void) {
}

void func_ovl14_01_8004BAEC(void) {
    D_ovl14_01_8004D4C4 = -1;
    D_ovl14_01_8004D4C8 = -1;
}

void func_ovl14_01_8004BA90(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl14_01_8004C6D8(D_ovl14_01_8004D4D0.x, D_ovl14_01_8004D4D0.y, D_ovl14_01_8004D4D0.z);
    func_ovl14_01_8004C6F8(arg0, arg1, arg2);
    func_ovl14_01_8004CA08(0xB4);
}

void func_ovl14_01_8004BA48(f32 arg0) {
    f32 sp1C;

    func_ovl14_01_8004C700(&sp1C, NULL, NULL);
    func_ovl14_01_8004C6F8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl14_01_8004B9CC(void) {
    void *sp1C;

    sp1C = func_ovl14_01_8004CA10();
    if (func_ovl14_01_8004CC70(0x413) == 0) {
        do {
            func_ovl14_01_8004CA30();
        } while (func_ovl14_01_8004CC70(0x413) == 0);
    }
    if (!(*D_ovl14_01_8004D4E0 & 2)) {
        func_ovl14_01_8004CF80((s32) sp1C);
    }
    func_ovl14_01_8004C9F8();
}

static void func_ovl14_01_8004B690() {
}

static void func_ovl14_01_8004B688() {
}

static void func_ovl14_01_8004B680() {
}

void func_ovl14_01_8004B698(void) {
    func_ovl14_01_8004B690();
    func_ovl14_01_8004B688();
    func_ovl14_01_8004B680();
    func_ovl14_01_8004BE98(0x1D1);
    func_ovl14_01_8004BEB0(0x1D2);
    func_ovl14_01_8004C048();
    func_ovl14_01_8004C0D8(func_ovl14_01_8004C078())->unk40->unk20 = 180.0f;
    func_ovl14_01_8004BF80(func_ovl14_01_80047978);
    func_ovl14_01_8004BFD0(func_ovl14_01_8004B024);
    func_ovl14_01_8004BEA8(&D_ovl14_01_8004D528);
    D_ovl14_01_8004D518.x = ((f32) ((s32) D_ovl14_01_8004D528 / 2) * 100.0f) - 50.0f;
    func_ovl14_01_8004BF00(0);
    D_ovl14_01_8004D518.y = 0.0f;
    D_ovl14_01_8004D518.z = ((f32) ((s32) D_ovl14_01_8004D530 / 2) * 100.0f) - 50.0f;
    func_ovl14_01_8004CD30(0);
    D_ovl14_01_8004D534 = 0.0f;
    D_ovl14_01_8004D538 = -90.0f;
    func_ovl14_01_8004CBB0(D_ovl14_01_8004D534, D_ovl14_01_8004D538);
    func_ovl14_01_8004C9E8(func_ovl14_01_8004A760, NULL, 0, 0, 0x150);
    func_ovl14_01_8004AF68();
    func_ovl14_01_8004C9D0();
    func_ovl14_01_8004CC08();
    func_ovl14_01_8004A914();
}

void func_ovl14_01_8004B908(void) {
    func_ovl14_01_8004C088(1);
    if (func_ovl14_01_8004CC70(0x413) == 0) {
        do {
            func_ovl14_01_8004CA30();
        } while (func_ovl14_01_8004CC70(0x413) == 0);
    }
    func_ovl14_01_8004C088(1);
    func_ovl14_01_8004C000(0);
    if (func_ovl14_01_8004CC50(0xA4) != 0) {
        func_ovl14_01_8004C138(1);
        func_ovl14_01_8004C0A0("WM1 WAP WG1 M1 ST1 M6 ST20 WSH WDNE WB2 ST10 M2 ST8 M4 ST1");
        func_ovl14_01_8004C0A0("WM1 WAP WG1 M1 ST1 M6 ST20 WSH WDE WB4 ST10 M2 ST8 M4 ST1");
        func_ovl14_01_8004C0A0("WM1 WAP WG1 WSH WDSW WB7 ST1 WDS WB0 M1 ST1 M6 ST10 M2 ST8 M4 ST60 MB ST1");
        func_ovl14_01_8004CA08(0x5A);
    } else {
        func_ovl14_01_8004C0A0("WM1 WAP WG1 M1 ST1 M6 ST20 WSH WDNE WB2 ST20 M2 ST8 M4 ST1 WSH WDSW WB4 ST1 WSH WDNW WB3 ST1");
        func_ovl14_01_8004CA08(0x28);
    }
    func_ovl14_01_8004D0E8();
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_8004B820(s32 arg0) {
    switch (arg0) {
    case 2:
        func_ovl14_01_8004B698();
        return;
    case 4:
        func_ovl14_01_8004B500();
        return;
    case 5:
        func_ovl14_01_8004B3EC();
        return;
    case 3:
        func_ovl14_01_8004CC60(0x413);
        D_ovl14_01_8004D4BC = func_ovl14_01_8004C078(); func_ovl14_01_8004C058(&D_ovl14_01_8004D4B0);
        func_ovl14_01_8004C080(D_ovl14_01_8004D4BC, &D_ovl14_01_8004D4A0);
        return;
    case 11:
        func_ovl14_01_8004CC10();
        func_ovl14_01_8004CC60(0x401);
        return;
    case 1:
        if (func_ovl14_01_8004CC70(0x401) == 0) {
            func_ovl14_01_8004CC10();
        }
        func_ovl14_01_8004B2A8();
        /* fallthrough */
    case 17:
        break;
    default:
        return;
    }
}

void func_ovl14_01_8004B500(void) {
    func_ovl14_01_8004C890(0);
    func_ovl14_01_8004C0A8();
    func_ovl14_01_8004C010(0);
    func_ovl14_01_8004C740(0xF);
    func_ovl14_01_8004C750(2);
    func_ovl14_01_8004C788(D_ovl14_01_8004D518.x, D_ovl14_01_8004D518.z, 100.0f, 400.0f);
    func_ovl14_01_8004C798(D_ovl14_01_8004D518.x, D_ovl14_01_8004D518.z, D_ovl14_01_8004D518.x, D_ovl14_01_8004D518.z);
    func_ovl14_01_8004C790(25.0f, 25.0f);
    func_ovl14_01_8004C6F8(32768.0f, 25.0f, 2500.0f);
    func_ovl14_01_8004C6D8(2300.0f, 500.0f, 1600.0f);
    D_ovl14_01_8004D508.x = 0.0f;
    D_ovl14_01_8004D508.y = 90.0f;
    D_ovl14_01_8004D508.z = 400.0f;
    func_ovl14_01_8004C778(&D_ovl14_01_8004D508);
    D_ovl14_01_8004D4F8.x = 0.0f;
    D_ovl14_01_8004D4F8.y = 25.0f;
    D_ovl14_01_8004D4F8.z = 2500.0f;
    func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
    func_ovl14_01_8004C6F8(0.0f, D_ovl14_01_8004D4F8.y, 2500.0f);
    func_ovl14_01_800437B8();
    if (*D_ovl14_01_8004D4E0 & 2) {
        func_ovl14_01_8004C9E8(func_ovl14_01_8004B908, NULL, 0, 0, 0x130);
    }
    func_ovl14_01_8004CC20();
}

void func_ovl14_01_8004B4B4(void) {
    if (*D_ovl14_01_8004D4E0 & 2) {
        func_ovl14_01_8004C9E8(func_ovl14_01_8004B908, NULL, 0, 0, 0x130);
    }
}

void func_ovl14_01_8004B3EC(void) {
    func_ovl14_01_800432D8();
    D_ovl14_01_8004D4BC = func_ovl14_01_8004C078(); func_ovl14_01_8004C058(&D_ovl14_01_8004D4B0);
    func_ovl14_01_8004C080(D_ovl14_01_8004D4BC, &D_ovl14_01_8004D4A0);
    func_ovl14_01_8004CC00();
    func_ovl14_01_8004C9C8(&D_ovl14_01_8004D548);
    if (func_ovl14_01_8004CC70(0x400) != 0) {
        if (!(*D_ovl14_01_8004D4E0 & 2)) {
            func_ovl14_01_8004CF80(0x13);
        }
    } else {
        func_ovl14_01_8004CC60(0x400);
    }
    func_ovl14_01_8004C9E8(func_ovl14_01_8004B9CC, (void *)0x11, 0, 0, 0x150);
}

static void func_ovl14_01_8004B394() {
}

static void func_ovl14_01_8004B38C() {
}

void func_ovl14_01_8004B39C(void) {
    func_ovl14_01_8004B394();
    func_ovl14_01_8004B38C();
    func_ovl14_01_8004CC60(0x413);
    D_ovl14_01_8004D4BC = func_ovl14_01_8004C078(); func_ovl14_01_8004C058(&D_ovl14_01_8004D4B0);
    func_ovl14_01_8004C080(D_ovl14_01_8004D4BC, &D_ovl14_01_8004D4A0);
}

void func_ovl14_01_8004B2A8(void) {
    if (D_ovl14_01_8004D4E4 != -1) {
        func_ovl14_01_8004CFA0(D_ovl14_01_8004D4E4);
        D_ovl14_01_8004D4E4 = -1;
    }
    if (D_ovl14_01_8004D4E8 != -1) {
        func_ovl14_01_8004CFA0(D_ovl14_01_8004D4E8);
        D_ovl14_01_8004D4E8 = -1;
    }
    if (D_ovl14_01_8004D4EC != -1) {
        func_ovl14_01_8004CFA0(D_ovl14_01_8004D4EC);
        D_ovl14_01_8004D4EC = -1;
    }
    if (D_ovl14_01_8004D4F0 != -1) {
        func_ovl14_01_8004CFA0(D_ovl14_01_8004D4F0);
        D_ovl14_01_8004D4F0 = -1;
    }
    func_ovl14_01_8004C9D8();
    if (*D_ovl14_01_8004D4E0 & 2) {
        func_ovl14_01_8004D0F0();
    }
}

void func_ovl14_01_8004B26C(void) {
    if (*D_ovl14_01_8004D4E0 & 2) {
        func_ovl14_01_8004D0F0();
    }
}

void func_ovl14_01_8004B024(UnkStructA *arg0) {
    Vec3f sp5C;
    Vec3f sp50;
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    s32 var_v1;
    s32 var_v1_2;

    func_ovl14_01_800431C4(0x1E, arg0);
    func_ovl14_01_8004C828(&D_ovl14_01_8004D518, &D_ovl14_01_8004D4A0, &sp50);
    sp50.y = 0.0f;
    sp50.z = 10.0f;
    func_ovl14_01_8004C830(&sp50, &sp5C);
    arg0->unk68 = 50.0f;
    var_fs0 = (f32) (func_ovl14_01_8004CBA0() * 20.0);
    var_fs1 = (f32) (func_ovl14_01_8004CBA0() * 20.0);
    var_fs2 = (f32) (func_ovl14_01_8004CBA0() * 20.0);
    if (func_ovl14_01_8004CBA8(1) != 0) {
        var_fs0 *= -1.0f;
    }
    if (func_ovl14_01_8004CBA8(1) != 0) {
        var_fs1 *= -1.0f;
    }
    if (func_ovl14_01_8004CBA8(1) != 0) {
        var_fs2 *= -1.0f;
    }
    var_v1 = 0;
    if (arg0->unk40->unk14 <= func_ovl14_01_8004BEC0()) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        do {
            arg0->unk40->unk10 += sp5C.x;
            temp_v0 = arg0->unk40;
            temp_v0->unk18 += sp5C.z;
            temp_v0_2 = arg0->unk40;
            temp_v0_2->unk20 += var_fs1;
            temp_v0_3 = arg0->unk40;
            temp_v0_3->unk1C += var_fs0;
            temp_v0_4 = arg0->unk40;
            temp_v0_4->unk24 += var_fs2;
            func_ovl14_01_8004C918(arg0);
            func_ovl14_01_8004CA30();
            var_v1_2 = 0;
            if (arg0->unk40->unk14 <= func_ovl14_01_8004BEC0()) {
                var_v1_2 = 1;
            }
        } while (var_v1_2 == 0);
    }
    func_ovl14_01_80047978(arg0);
}

void func_ovl14_01_8004AF68(void) {
    func_ovl14_01_8004CC68(0x43F);
    func_ovl14_01_8004CC68(0x43E);
    func_ovl14_01_8004CC68(0x41F);
    func_ovl14_01_8004CC68(0x41E);
    func_ovl14_01_8004CC68(0x41D);
    func_ovl14_01_8004CC68(0x41C);
    func_ovl14_01_8004CC68(0x41B);
    func_ovl14_01_8004CC68(0x41A);
    func_ovl14_01_8004CC68(0x419);
    func_ovl14_01_8004CC68(0x418);
    func_ovl14_01_8004CC68(0x413);
    func_ovl14_01_8004CC68(0x417);
    func_ovl14_01_8004CC60(0x415);
    func_ovl14_01_8004CC68(0x414);
    func_ovl14_01_8004CC68(0x401);
    D_ovl14_01_8004D4E0 = func_ovl14_01_8004BFE8();
    if (D_ovl14_01_8004D4E0[4] == 0) {
        func_ovl14_01_8004CC60(0x41F);
    }
}

void func_ovl14_01_8004A914(void) {
    Vec3f angle;
    s32 i;
    s32 pad;

    D_ovl14_01_8004D4E4 = -1;
    D_ovl14_01_8004D4E8 = -1;
    D_ovl14_01_8004D4F0 = -1;
    D_ovl14_01_8004D4EC = -1;
    D_ovl14_01_8004D6C0 = 0;
    D_ovl14_01_8004D6C4 = 0;
    D_ovl14_01_8004D53C = 0;
    D_ovl14_01_8004D540 = 0;
    D_ovl14_01_8004D544 = 6;
    D_ovl14_01_8004D548 = 14;
    D_ovl14_01_8004D54C = 8;
    D_ovl14_01_8004D550 = 8;
    D_ovl14_01_8004D554 = 4;
    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        D_ovl14_01_8004D544 -= 4;
        D_ovl14_01_8004D548 -= 4;
        D_ovl14_01_8004D54C /= 2;
        D_ovl14_01_8004D550 /= 2;
        D_ovl14_01_8004D554 /= 2;
    }
    D_ovl14_01_8004D6A0.x = D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.z = 0.0f;
    D_ovl14_01_8004D6BC = 0;
    D_ovl14_01_8004D6B0.x = D_ovl14_01_8004D518.x;
    D_ovl14_01_8004D6B0.y = D_ovl14_01_8004D518.y + -300.0f;
    D_ovl14_01_8004D6B0.z = D_ovl14_01_8004D518.z;
    angle.x = 180.0f;
    angle.y = 0.0f;
    angle.z = 1200.0f;
    for (i = 0; i < 8; i++) {
        func_ovl14_01_8004C830(&angle, &D_ovl14_01_8004D6F0[i]);
        D_ovl14_01_8004D6F0[i].x += D_ovl14_01_8004D6B0.x;
        D_ovl14_01_8004D6F0[i].y += D_ovl14_01_8004D6B0.y;
        D_ovl14_01_8004D6F0[i].z += D_ovl14_01_8004D6B0.z;
        angle.x = WRAP360(angle.x + 45.0f);
    }
    D_ovl14_01_8004D6C8 = 0;
    D_ovl14_01_8004D6CC = 0;
    D_ovl14_01_8004D690.x = D_ovl14_01_8004D6F0[D_ovl14_01_8004D6C8].x;
    D_ovl14_01_8004D690.y = D_ovl14_01_8004D6F0[D_ovl14_01_8004D6C8].y;
    D_ovl14_01_8004D690.z = D_ovl14_01_8004D6F0[D_ovl14_01_8004D6C8].z;
    D_ovl14_01_8004D62C = 31.0f;
    D_ovl14_01_8004D630 = 31.0f;
    D_ovl14_01_8004D634 = 31.0f;
    D_ovl14_01_8004D684 = 0.0f;
    D_ovl14_01_8004D638 = 0;
    D_ovl14_01_8004D63C = 0;
    D_ovl14_01_8004D640 = 0;
    D_ovl14_01_8004D688 = 0.0f;
    D_ovl14_01_8004D5E8 = func_ovl14_01_8004C8C0(0x1C4, 0x01008014, 0xC0, NULL);
    D_ovl14_01_8004D5E8->unk30 = 2;
    D_ovl14_01_8004D5E8->unk34 = 300.0f;
    D_ovl14_01_8004D5E8->unk38 = 900.0f;
    D_ovl14_01_8004D5E8->unkC = 0x2002;
    D_ovl14_01_8004D5E8->unk40->unk10 = D_ovl14_01_8004D690.x;
    D_ovl14_01_8004D5E8->unk58 = D_ovl14_01_8004D5E8->unk40->unk10;
    D_ovl14_01_8004D5E8->unk40->unk14 = D_ovl14_01_8004D690.y;
    D_ovl14_01_8004D5E8->unk5C = D_ovl14_01_8004D5E8->unk40->unk14;
    D_ovl14_01_8004D5E8->unk40->unk18 = D_ovl14_01_8004D690.z;
    D_ovl14_01_8004D5E8->unk60 = D_ovl14_01_8004D5E8->unk40->unk18;
    D_ovl14_01_8004D5DC = func_ovl14_01_8004C8F0(0x1CA, 0x01400000, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5E0 = func_ovl14_01_8004C8F0(-1, 0x400000, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5E0->unk50 = 800.0f;
    M2C_FIELD(D_ovl14_01_8004D5E0, Link_ovl14_01 **, 0x3C) = D_ovl14_01_8004D560;
    D_ovl14_01_8004D5F4 = func_ovl14_01_8004C8F0(-1, 0x400000, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5F4->unk50 = 800.0f;
    D_ovl14_01_8004D5F4->unk54 = 490.0f;
    func_ovl14_01_8004C868(D_ovl14_01_8004D5F4, 0xD0);
    D_ovl14_01_8004D5E4 = func_ovl14_01_8004C8F0(-1, 0x01600000, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5E4->unk50 = 550.0f;
    D_ovl14_01_8004D5E4->unk54 = 250.0f;
    D_ovl14_01_8004D5E4->unk40->unk30 = 3.0f;
    D_ovl14_01_8004D5E4->unk40->unk28 = D_ovl14_01_8004D5E4->unk40->unk2C = D_ovl14_01_8004D5E4->unk40->unk30;
    D_ovl14_01_8004D5EC = func_ovl14_01_8004C8F0(0x1C5, 0x01400000, D_ovl14_01_8004D5DC);
    D_ovl14_01_8004D5EC->unk50 = 900.0f;
    D_ovl14_01_8004D5F0 = func_ovl14_01_8004C8F0(0x1C6, 0x01408010, D_ovl14_01_8004D5EC);
    D_ovl14_01_8004D5F0->unk50 = 80.0f;
    D_ovl14_01_8004D5F0->unk30 = 4;
    D_ovl14_01_8004D5F0->unk34 = 100.0f;
    D_ovl14_01_8004D5F0->unk38 = 150.0f;
    D_ovl14_01_8004D5F0->unkC = 0x2002;
    func_ovl14_01_80049814(0x1C8, D_ovl14_01_8004D600, D_ovl14_01_8004D560);
    func_ovl14_01_80049814(0x1C9, D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
    func_ovl14_01_80043010(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
    func_ovl14_01_80043010(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
    func_ovl14_01_8004C9E8(func_ovl14_01_80049FA8, NULL, 0, 0, 0x110);
    func_ovl14_01_8004C9E8(func_ovl14_01_8004A11C, NULL, 0, 0, 0x110);
    func_ovl14_01_8004C9E8(func_ovl14_01_80043B20, NULL, 0, 0, 0x150);
}

void func_ovl14_01_8004A760(void) {
    f32 temp_fs0;
    f32 temp_fs2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fs0;
    f32 var_fs0_2;
    f32 var_fs4;
    f32 var_fs5;
    f64 temp_fs1;

    var_fs4 = 0.0f;
    var_fs5 = 0.0f;
loop_1:
    var_fs5 = WRAP360(var_fs5 + 0.1f);
    var_fs4 = WRAP360(var_fs4 + 0.2f);
    temp_fs2 = func_ovl14_01_8004CB90(var_fs5);
    temp_fs1 = func_ovl14_01_8004CBA0();
    temp_fs0 = func_ovl14_01_8004CB90(var_fs4);
    func_ovl14_01_8004CBB0(((f32) temp_fs1 * 3.0f * temp_fs2) + D_ovl14_01_8004D534, ((f32) func_ovl14_01_8004CBA0() * 3.0f * temp_fs0) + D_ovl14_01_8004D538);
    func_ovl14_01_8004CA30();
    goto loop_1;
}

void func_ovl14_01_8004A4E0(void) {
    Vec3f sp50_v;
    s32 sp48;
    UnkStructA *temp_v0;
    f32 temp_fv1;
    s32 var_s1;
    s32 var_s3;

    temp_v0 = func_ovl14_01_8004CA10();
    if (temp_v0 == D_ovl14_01_8004D5E8) {
        sp48 = D_ovl14_01_8004D548;
    }
    var_s3 = sp48;
    if (temp_v0 == D_ovl14_01_8004D5F0) {
        var_s3 = D_ovl14_01_8004D554;
    }
    if (temp_v0 == D_ovl14_01_8004D600[4]) {
        var_s3 = D_ovl14_01_8004D54C;
    }
    if (temp_v0 == D_ovl14_01_8004D618[4]) {
        var_s3 = D_ovl14_01_8004D550;
    }
    if (var_s3 != 0) {
        func_ovl14_01_800431C4(0x101, temp_v0);
        if (temp_v0 == D_ovl14_01_8004D5E8) {
            func_ovl14_01_800431C4(0xC3, D_ovl14_01_8004D5DC);
        }
    }
    var_s1 = 0;
    do {
        sp50_v.x = func_ovl14_01_8004CB98((f32) func_ovl14_01_8004CBA0() * 360.0f) * 200.0f;
        sp50_v.y = func_ovl14_01_8004CB98((f32) func_ovl14_01_8004CBA0() * 360.0f) * 200.0f;
        temp_fv1 = func_ovl14_01_8004CB98((f32) func_ovl14_01_8004CBA0() * 360.0f) * 200.0f;
        sp50_v.z = temp_fv1;
        if (temp_v0 == D_ovl14_01_8004D5E8) {
            sp50_v.x *= 2.0f;
            sp50_v.z = 2.0f * temp_fv1;
            sp50_v.y += 500.0f;
        }
        if (var_s3 != 0) {
            func_ovl14_01_800439AC(&sp50_v, temp_v0);
        } else {
            sp50_v.x += temp_v0->unk40->unk10;
            sp50_v.y += temp_v0->unk40->unk14;
            sp50_v.z += temp_v0->unk40->unk18;
            if (temp_v0 == D_ovl14_01_8004D5E8) {
                if (var_s1 < 0xE) {
                    if (func_ovl14_01_8004CBA8(1) != 0) {
                        func_ovl14_01_8004CF70(0xC9);
                    } else {
                        func_ovl14_01_8004CF70(0x102);
                    }
                } else {
                    func_ovl14_01_8004CF70(0xC7);
                }
            }
            func_ovl14_01_8004CE40(0x13, (f32 *)&sp50_v, 0);
        }
        func_ovl14_01_8004CA08(8);
        var_s1 += 1;
    } while (var_s1 != 0xF);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_8004A11C(void) {
    Vec3f sp8C_v;
    s32 sp74;
    s32 sp70;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_fp;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;

    sp70 = 0;
    var_s5 = 0;
    var_s6 = 0;
    var_s7 = 0;
    var_fp = 0;
    sp74 = 0;
loop_1:
    if ((sp70 == 0) && (D_ovl14_01_8004D548 == 0)) {
        sp70 = 1;
        func_ovl14_01_8004CF88();
    }
    D_ovl14_01_8004D5E8->unk40->unk10 = D_ovl14_01_8004D690.x;
    D_ovl14_01_8004D5E8->unk40->unk14 = D_ovl14_01_8004D690.x;
    D_ovl14_01_8004D5E8->unk40->unk18 = D_ovl14_01_8004D690.z;
    D_ovl14_01_8004D5E8->unk40->unk1C = D_ovl14_01_8004D6A0.y;
    D_ovl14_01_8004D5E8->unk40->unk20 = D_ovl14_01_8004D6A0.y;
    D_ovl14_01_8004D5E8->unk40->unk24 = D_ovl14_01_8004D6A0.z;
    temp_v0 = D_ovl14_01_8004D548;
    if (temp_v0 != 0) {
        if (var_fp == 0) {
            temp_v0_2 = func_ovl14_01_8004A0CC(D_ovl14_01_8004D5E8);
            temp_t2 = D_ovl14_01_8004D548 - temp_v0_2;
            D_ovl14_01_8004D548 = temp_t2;
            if (temp_t2 < 0) {
                D_ovl14_01_8004D548 = 0;
            }
            if (temp_v0_2 != 0) {
                var_fp = 0x78;
                func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, D_ovl14_01_8004D5E8, 0, 0, 0x150);
            }
        } else {
            var_fp -= 1;
        }
        if ((temp_v0 < 0xE) && (D_ovl14_01_8004D554 != 0) && (func_ovl14_01_8004CC70(0x419) != 0)) {
            if (sp74 == 0) {
                sp8C_v.x = D_ovl14_01_8004D5F0->unk40->unk10;
                sp8C_v.y = D_ovl14_01_8004D5F0->unk40->unk14 + 210.0f;
                sp8C_v.z = D_ovl14_01_8004D5F0->unk40->unk18;
                func_ovl14_01_8004CE40(0xE, (f32 *)&sp8C_v, 0);
                sp74 = D_ovl14_01_8004D548 * 0xF;
            } else {
                sp74 -= 1;
            }
        }
    }
    if (D_ovl14_01_8004D54C != 0) {
        if (var_s7 == 0) {
            temp_v0_3 = func_ovl14_01_8004A0CC(D_ovl14_01_8004D600[4]);
            temp_t6 = D_ovl14_01_8004D54C - temp_v0_3;
            D_ovl14_01_8004D54C = temp_t6;
            if (temp_t6 < 0) {
                D_ovl14_01_8004D54C = 0;
            }
            if (temp_v0_3 != 0) {
                var_s7 = 0x78;
                func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, D_ovl14_01_8004D600[4], 0, 0, 0x150);
            }
        } else {
            var_s7 -= 1;
        }
    }
    if (D_ovl14_01_8004D550 != 0) {
        if (var_s6 == 0) {
            temp_v0_4 = func_ovl14_01_8004A0CC(D_ovl14_01_8004D618[4]);
            temp_t1 = D_ovl14_01_8004D550 - temp_v0_4;
            D_ovl14_01_8004D550 = temp_t1;
            if (temp_t1 < 0) {
                D_ovl14_01_8004D550 = 0;
            }
            if (temp_v0_4 != 0) {
                var_s6 = 0x78;
                func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, D_ovl14_01_8004D618[4], 0, 0, 0x150);
            }
        } else {
            var_s6 -= 1;
        }
    }
    if (D_ovl14_01_8004D554 != 0) {
        if (var_s5 == 0) {
            temp_v0_5 = func_ovl14_01_8004A0CC(D_ovl14_01_8004D5F0);
            temp_t6_2 = D_ovl14_01_8004D554 - temp_v0_5;
            D_ovl14_01_8004D554 = temp_t6_2;
            if (temp_t6_2 < 0) {
                D_ovl14_01_8004D554 = 0;
            }
            if (temp_v0_5 != 0) {
                var_s5 = 0x78;
                func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, D_ovl14_01_8004D5F0, 0, 0, 0x150);
            }
        } else {
            var_s5 -= 1;
        }
    }
    func_ovl14_01_800445D8();
    func_ovl14_01_80044104();
    func_ovl14_01_8004CA30();
    goto loop_1;
}

s32 func_ovl14_01_8004A0CC(UnkStructA *arg0) {
    s32 flags;
    s32 n;

    flags = func_ovl14_01_8004C848(arg0, 0x40);
    if (flags & 0x6000) {
        n = 1;
        if (flags & 0x2000) {
            n = 2;
        }
        if (flags & 0x4000) {
            n++;
        }
    } else {
        n = 0;
    }
    return n;
}

void func_ovl14_01_80049FA8(void) {
    while (func_ovl14_01_8004CC70(0x413) == 0) {
        func_ovl14_01_8004CA30();
    }
    D_ovl14_01_8004D6C0 = 0;
    D_ovl14_01_8004D6C4 = 0;
    func_ovl14_01_80045010();
    while (D_ovl14_01_8004D548 != 0 && D_ovl14_01_8004D544 != 0) {
        func_ovl14_01_80049CF4();
        func_ovl14_01_80049BE0(D_ovl14_01_8004D6C0, D_ovl14_01_8004D6C4);
        func_ovl14_01_8004697C();
        D_ovl14_01_8004D6C0 = 0;
        D_ovl14_01_8004D6C4 = 0;
        func_ovl14_01_80045010();
        func_ovl14_01_8004697C();
    }
    func_ovl14_01_8004C010(1);
    func_ovl14_01_8004515C();
    func_ovl14_01_8004CC68(0x415);
    func_ovl14_01_80049F2C();
    func_ovl14_01_8004BFB8();
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80049F2C(void) {
    s32 var_s0;

    var_s0 = 0;
    if (func_ovl14_01_8004CC70(0x41E) != 0) {
        var_s0 = 1;
    }
    if (func_ovl14_01_8004CC70(0x41D) != 0) {
        var_s0 += 1;
    }
    if (func_ovl14_01_8004CC70(0x41C) != 0) {
        var_s0 += 1;
    }
    if (func_ovl14_01_8004CC70(0x417) != 0) {
        var_s0 += 1;
    }
    M2C_FIELD(D_ovl14_01_8004D4E0, s32 *, 0x2C) = var_s0;
}

void func_ovl14_01_80049CF4(void) {
    u32 temp_v0;

    D_ovl14_01_8004D6C0 = 0xA;
    D_ovl14_01_8004D6C4 = 0;
    if ((D_ovl14_01_8004D54C != 0) && (D_ovl14_01_8004D550 != 0)) {
        if (func_ovl14_01_8004CBA0() < 0.4000000059604645) {
            D_ovl14_01_8004D6C0 = 1;
            D_ovl14_01_8004D6C4 = 0;
        } else {
            D_ovl14_01_8004D6C0 = 2;
            D_ovl14_01_8004D6C4 = 1;
            if (func_ovl14_01_8004CC70(0x41F) == 0) {
                D_ovl14_01_8004D6C4 += func_ovl14_01_8004CBA8(1) + 1;
            }
        }
    } else {
        temp_v0 = func_ovl14_01_8004CBA8(9);
        switch (temp_v0) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (D_ovl14_01_8004D554 != 0) {
                D_ovl14_01_8004D6C0 = 4;
                D_ovl14_01_8004D6C4 = func_ovl14_01_8004CBA8(4) + 4;
            } else {
            case 4:
            case 5:
            case 6:
            case 7:
                if ((D_ovl14_01_8004D54C != 0) || (D_ovl14_01_8004D550 != 0)) {
                    D_ovl14_01_8004D6C0 = 2;
                    D_ovl14_01_8004D6C4 = 1;
                    if (func_ovl14_01_8004CC70(0x41F) == 0) {
                        D_ovl14_01_8004D6C4 += func_ovl14_01_8004CBA8(1) + 1;
                    }
                } else {
                default:
                    D_ovl14_01_8004D6C0 = 3;
                    if (func_ovl14_01_8004CC70(0x41F) != 0) {
                        D_ovl14_01_8004D6C4 = func_ovl14_01_8004CBA8(1) + 1;
                    } else {
                        D_ovl14_01_8004D6C4 = func_ovl14_01_8004CBA8(2) + 3;
                        if ((func_ovl14_01_8004CBA8(0x1F) == 0) && (func_ovl14_01_8004CC70(0x418) != 0)) {
                            D_ovl14_01_8004D6C4 = 0xA;
                        }
                    }
                }
            }
            break;
        }
    }
    if (*D_ovl14_01_8004D4E0 & 2) {
        if (func_ovl14_01_8004CC50(0xA4) != 0) {
            D_ovl14_01_8004D6C0 = 1;
            D_ovl14_01_8004D6C4 = 0;
        } else {
            D_ovl14_01_8004D6C0 = 2;
            D_ovl14_01_8004D6C4 = 1;
        }
    }
}

void func_ovl14_01_80049BE0(u32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
        func_ovl14_01_80045010();
        return;
    case 3:
        func_ovl14_01_800477EC(arg1);
        return;
    case 4:
        func_ovl14_01_800481B8(arg1);
        return;
    case 1:
        func_ovl14_01_800488B0();
        return;
    case 2:
        func_ovl14_01_80049368(arg1);
        return;
    case 6:
        func_ovl14_01_80046B98(0, 1.0f);
        func_ovl14_01_80046004(arg1);
        return;
    case 7:
        func_ovl14_01_800467C0(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        return;
    case 8:
        func_ovl14_01_800467C0(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
        return;
    case 9:
        func_ovl14_01_8004515C();
        return;
    case 10:
        func_ovl14_01_8004CA30();
        return;
    case 5:
        func_ovl14_01_80046CE8();
        /* fallthrough */
    default:
        return;
    }
}

void func_ovl14_01_80049BC0(void) {
    func_ovl14_01_8004CA30();
}

void func_ovl14_01_80049B70(void) {
    Vec3f pos;

    pos.x = D_ovl14_01_8004D6D0.x;
    pos.y = D_ovl14_01_8004D6D0.y;
    pos.z = D_ovl14_01_8004D6D0.z;
    func_ovl14_01_80044B38(&pos, D_ovl14_01_8004D6DC);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80049814(s32 id, UnkStructA **parts, Link_ovl14_01 *links) {
    UnkStructA **p;
    Link_ovl14_01 *l;
    UnkStructA *o;
    Vec3f *v;
    f32 s;
    s32 i;

    p = parts;
    *p = func_ovl14_01_8004C8F0(-1, 0x400000, D_ovl14_01_8004D5E0);
    if (id == 0x1C8) {
        (*p)->unk4C = -498.0f;
        D_ovl14_01_8004D4DC = D_ovl14_01_8004D190;
    } else {
        (*p)->unk4C = 498.0f;
        D_ovl14_01_8004D4DC = D_ovl14_01_8004D1CC;
    }
    M2C_FIELD(*p, Link_ovl14_01 **, 0x3C) = links;
    p++;
    *p = func_ovl14_01_8004C8F0(-1, 0x500000, p[-1]);
    (*p)->unk50 = 0.0f;
    (*p)->unk54 = 60.0f;
    p++;
    M2C_FIELD(p[-1], Link_ovl14_01 **, 0x3C) = links;
    *p = func_ovl14_01_8004C8F0(0x1C7, 0x01000000, p[-1]);
    func_ovl14_01_8004C880(p[-1], *p, links, 0x150);
    func_ovl14_01_8004C8D0(*p);
    l = links + 1;
    p++;
    *p = func_ovl14_01_8004C8F0(-1, 0, p[-1]);
    (*p)->unk50 = 0.0f;
    (*p)->unk54 = 60.0f;
    func_ovl14_01_8004C880(p[-1], *p, l, 0x150);
    l++;
    p++;
    *p = func_ovl14_01_8004C8F0(id, 0x01008000, p[-1]);
    (*p)->unk54 = 420.0f;
    (*p)->unk50 = 0.0f;
    (*p)->unk30 = 1;
    (*p)->unk34 = 160.0f;
    (*p)->unk38 = 0.0f;
    func_ovl14_01_8004C880(p[-1], *p, l, 0x150);
    o = func_ovl14_01_8004C8D0(*p);
    s = (*p)->unk34 / 50.0f;
    o->unk54 = s;
    o->unk4C = s;
    func_ovl14_01_80043010(parts, links);
    v = D_ovl14_01_8004D4DC;
    p = parts;
    for (i = 0; i < 5; i++) {
        (*p)->unk40->unk10 = v->x;
        (*p)->unk40->unk14 = v->y;
        (*p)->unk40->unk18 = v->z;
        v++;
        p++;
    }
    D_ovl14_01_8004D4DC = v;
}

void func_ovl14_01_80049618(void) {
    Vec3f sp74_v;
    Vec3f sp68_v;
    Vec3f sp5C;
    Link_ovl14_01 *var_s0;
    UnkStructA *var_s3;
    f32 temp_fs0;
    s32 var_s1;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;

    if (func_ovl14_01_8004CA10() == (void *)0x1C8) {
        var_s3 = D_ovl14_01_8004D600[4];
        var_s0 = D_ovl14_01_8004D560;
    } else {
        var_s3 = D_ovl14_01_8004D618[4];
        var_s0 = D_ovl14_01_8004D5A0;
    }
    sp74_v.y = D_ovl14_01_8004D6E0.y;
    sp74_v.x = D_ovl14_01_8004D6E0.x;
    sp68_v.y = D_ovl14_01_8004D4A0.y + 150.0f;
    sp74_v.z = D_ovl14_01_8004D6E0.z;
    sp68_v.x = D_ovl14_01_8004D4A0.x;
    sp68_v.z = D_ovl14_01_8004D4A0.z;
    func_ovl14_01_8004C828(&sp74_v, &sp68_v, &sp5C);
    var_s2 = 0;
    var_s1 = 0;
    var_v0 = 1;
    temp_fs0 = ((sp5C.z - 790.0f) / 14.0f) / 3.0f;
    if ((D_ovl14_01_8004D544 == 0) || (D_ovl14_01_8004D548 == 0)) {

    } else {
        var_v0 = 0;
    }
    if (var_v0 == 0) {
loop_8:
        var_s0->unk4 += temp_fs0;
        M2C_FIELD(var_s0, f32 *, 0x18) = (f32) (M2C_FIELD(var_s0, f32 *, 0x18) + temp_fs0);
        M2C_FIELD(var_s0, f32 *, 0x2C) = (f32) (M2C_FIELD(var_s0, f32 *, 0x2C) + temp_fs0);
        if ((var_s2 == 0) && (func_ovl14_01_8004C860((s32) var_s3, func_ovl14_01_8004C0D8(func_ovl14_01_8004C078())) != 0)) {
            var_s2 = 1;
            func_ovl14_01_8004C8A0(var_s3, 0x1E00);
        }
        func_ovl14_01_8004CA30();
        var_s1 += 1;
        if (var_s1 < 0xE) {
            if ((D_ovl14_01_8004D544 == 0) || (var_v0_2 = 0, (D_ovl14_01_8004D548 == 0))) {
                var_v0_2 = 1;
            }
            if (var_v0_2 == 0) {
                goto loop_8;
            }
        }
    }
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800494C8(void) {
    Link_ovl14_01 *var_s0;
    f32 temp_fs0;
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;

    var_s1 = 0;
    if (func_ovl14_01_8004CA10() == (void *)0x1C8) {
        var_s0 = D_ovl14_01_8004D560;
    } else {
        var_s0 = D_ovl14_01_8004D5A0;
    }
    if ((D_ovl14_01_8004D544 == 0) || (var_v0 = 0, (D_ovl14_01_8004D548 == 0))) {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        temp_fs0 = ((790.0f - (var_s0->unk4 + M2C_FIELD(var_s0, f32 *, 0x18) + M2C_FIELD(var_s0, f32 *, 0x2C))) / 30.0f) / 3.0f;
loop_8:
        var_s0->unk4 += temp_fs0;
        M2C_FIELD(var_s0, f32 *, 0x18) = (f32) (M2C_FIELD(var_s0, f32 *, 0x18) + temp_fs0);
        M2C_FIELD(var_s0, f32 *, 0x2C) = (f32) (M2C_FIELD(var_s0, f32 *, 0x2C) + temp_fs0);
        func_ovl14_01_8004CA30();
        var_s1 += 1;
        if (var_s1 < 0x1E) {
            if ((D_ovl14_01_8004D544 == 0) || (var_v0_2 = 0, (D_ovl14_01_8004D548 == 0))) {
                var_v0_2 = 1;
            }
            if (var_v0_2 == 0) {
                goto loop_8;
            }
        }
    }
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80049368(s32 arg0) {
    Vec3f sp44;
    Vec3f sp38;
    Vec3f sp2C_v;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fv1;

    sp2C_v.x = D_ovl14_01_8004D690.x;
    sp2C_v.y = D_ovl14_01_8004D690.y;
    sp2C_v.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_800431C4(0xC2, D_ovl14_01_8004D5DC);
    func_ovl14_01_8004C828(&D_ovl14_01_8004D6B0, &D_ovl14_01_8004D690, &sp38);
    temp_fv0 = sp38.y - 90.0f;
    if (temp_fv0 >= 360.0f) {
        var_fv1 = temp_fv0 - 360.0f;
    } else {
        if (sp38.y < 90.0f) {
            var_fa0 = temp_fv0 + 360.0f;
        } else {
            var_fa0 = temp_fv0;
        }
        var_fv1 = var_fa0;
    }
    sp38.y = var_fv1 - 5.0f;
    sp38.z += 200.0f;
    func_ovl14_01_8004C830(&sp38, &sp44);
    sp44.x = sp44.x + D_ovl14_01_8004D6B0.x;
    sp44.y += D_ovl14_01_8004D6B0.y;
    sp44.z += D_ovl14_01_8004D6B0.z;
    func_ovl14_01_80047594(&sp44, 0x1E);
    func_ovl14_01_8004882C();
    func_ovl14_01_80048DE8(arg0);
    func_ovl14_01_800487A8();
    func_ovl14_01_80047594(&sp2C_v, 0x1E);
    D_ovl14_01_8004D690.x = sp2C_v.x;
    D_ovl14_01_8004D690.y = sp2C_v.y;
    D_ovl14_01_8004D690.z = sp2C_v.z;
}

void func_ovl14_01_80048DE8(s32 arg0) {
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    Vec3f spC0_v;
    void (*sp58)();
    f32 var_ft2;
    f64 temp_fv0;
    f64 temp_fv0_2;
    f64 temp_fv1;
    f64 temp_fv1_2;
    f64 temp_fv1_3;
    f64 var_fv0;
    f64 var_fv0_2;
    f64 var_fv0_3;
    s32 temp_s2;
    s32 temp_v0_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    void *temp_v0;
    void *var_s0;

    func_ovl14_01_80044B38(&D_ovl14_01_8004D4A0, 0xA);
    D_ovl14_01_8004D6E0.x = (f32) D_ovl14_01_8004D5F4->unk40->unk10;
    D_ovl14_01_8004D6E0.y = (f32) D_ovl14_01_8004D5F4->unk40->unk14;
    D_ovl14_01_8004D6E0.z = (f32) D_ovl14_01_8004D5F4->unk40->unk18;
    var_s0 = (void *)0x1C9;
    if (func_ovl14_01_8004CBA8(1) != 0) {
        var_s0 = (void *)0x1C8;
    }
    var_s2 = 0;
    var_s3 = 0;
    if (arg0 > 0) {
        if ((D_ovl14_01_8004D544 == 0) || (var_v0 = 0, (D_ovl14_01_8004D548 == 0))) {
            var_v0 = 1;
        }
        if (var_v0 == 0) {
loop_8:
            temp_v0 = func_ovl14_01_80048D48(var_s0);
            var_s0 = temp_v0;
            if (temp_v0 != NULL) {
                sp58 = func_ovl14_01_800494C8;
                func_ovl14_01_800431C4(0xF6, D_ovl14_01_8004D5DC);
                spEC = 0.0f;
                spE8 = 0.0f;
                spE4 = 0.0f;
                spE0 = 0.0f;
                spDC = 0.0f;
                spD8 = 0.0f;
                spC0_v.y = D_ovl14_01_8004D4A0.y;
                spD0 = D_ovl14_01_8004D4A0.y;
                spC0_v.x = D_ovl14_01_8004D4A0.x;
                spC0_v.z = D_ovl14_01_8004D4A0.z;
                spCC = D_ovl14_01_8004D690.x;
                spD4 = D_ovl14_01_8004D690.z;
                func_ovl14_01_8004C828((Vec3f *) &spCC, &spC0_v, (Vec3f *) &spE4);
                temp_fv0 = (f64) spE8;
                temp_fv1 = temp_fv0 - 90.0;
                if (temp_fv1 >= 360.0) {
                    spE8 = (f32) (temp_fv1 - 360.0);
                } else {
                    if (temp_fv0 < 90.0) {
                        var_fv0 = temp_fv1 + 360.0;
                    } else {
                        var_fv0 = temp_fv1;
                    }
                    spE8 = (f32) var_fv0;
                }
                if (var_s0 == (void *)0x1C8) {
                    temp_fv1_2 = (f64) spE4 + 90.0;
                    if (temp_fv1_2 >= 360.0) {
                        var_ft2 = (f32) (temp_fv1_2 - 360.0);
                        goto block_28;
                    }
                    if (temp_fv1_2 < 0.0) {
                        var_fv0_2 = temp_fv1_2 + 360.0;
                    } else {
                        var_fv0_2 = temp_fv1_2;
                    }
                    spE4 = (f32) var_fv0_2;
                } else {
                    temp_fv0_2 = (f64) spE4;
                    temp_fv1_3 = temp_fv0_2 - 90.0;
                    if (temp_fv1_3 >= 360.0) {
                        spE4 = (f32) (temp_fv1_3 - 360.0);
                    } else {
                        if (temp_fv0_2 < 90.0) {
                            var_fv0_3 = temp_fv1_3 + 360.0;
                        } else {
                            var_fv0_3 = temp_fv1_3;
                        }
                        var_ft2 = (f32) var_fv0_3;
block_28:
                        spE4 = var_ft2;
                    }
                }
                func_ovl14_01_8004C830((Vec3f *) &spE4, (Vec3f *) &spD8);
                spD8 += D_ovl14_01_8004D690.x;
                spDC += D_ovl14_01_8004D690.y;
                spE0 += D_ovl14_01_8004D690.z;
                func_ovl14_01_80048CE8((Vec3f *) &spD8, 0xE);
                if (var_s0 == (void *)0x1C8) {
                    func_ovl14_01_80048ABC(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
                } else {
                    func_ovl14_01_80048ABC(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
                }
                func_ovl14_01_8004CA08(0xA);
                func_ovl14_01_8004C9E8(func_ovl14_01_80049618, var_s0, 0, 0, 0x150);
                func_ovl14_01_8004CA08(0x14);
                func_ovl14_01_8004C9E8(sp58, var_s0, 0, 0, 0x150);
                func_ovl14_01_80044B38(&D_ovl14_01_8004D4A0, 0x1E);
                D_ovl14_01_8004D6E0.x = (f32) D_ovl14_01_8004D5F4->unk40->unk10;
                D_ovl14_01_8004D6E0.y = (f32) D_ovl14_01_8004D5F4->unk40->unk14;
                D_ovl14_01_8004D6E0.z = (f32) D_ovl14_01_8004D5F4->unk40->unk18;
                func_ovl14_01_80043010(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
                func_ovl14_01_80043010(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
                temp_v0_2 = func_ovl14_01_80046AE8();
                var_s3 += 1;
                var_s2 = temp_v0_2;
                if ((var_s3 < arg0) && (temp_v0_2 == 0)) {
                    if ((D_ovl14_01_8004D544 == 0) || (var_v0_2 = 0, (D_ovl14_01_8004D548 == 0))) {
                        var_v0_2 = 1;
                    }
                    if (var_v0_2 == 0) {
                        goto loop_8;
                    }
                }
            }
        }
    }
    func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0x14);
    if (var_s2 == 0) {
        if ((D_ovl14_01_8004D544 == 0) || (var_v0_3 = 0, (D_ovl14_01_8004D548 == 0))) {
            var_v0_3 = 1;
        }
        if (var_v0_3 == 0) {
            var_s3_2 = 0;
            func_ovl14_01_8004C9E8(func_ovl14_01_80045474, NULL, 0, 0, 0x110);
            func_ovl14_01_8004C9E8(func_ovl14_01_80045474, (void *)1, 0, 0, 0x110);
            if (var_s2 == 0) {
                if ((D_ovl14_01_8004D544 == 0) || (var_v0_4 = 0, (D_ovl14_01_8004D548 == 0))) {
                    var_v0_4 = 1;
                }
                if (var_v0_4 == 0) {
loop_48:
                    temp_s2 = func_ovl14_01_80046AE8();
                    func_ovl14_01_8004CA30();
                    var_s3_2 += 1;
                    if ((var_s3_2 < 0xF0) && (temp_s2 == 0)) {
                        if ((D_ovl14_01_8004D544 == 0) || (var_v0_5 = 0, (D_ovl14_01_8004D548 == 0))) {
                            var_v0_5 = 1;
                        }
                        if (var_v0_5 == 0) {
                            goto loop_48;
                        }
                    }
                }
            }
        }
    }
    func_ovl14_01_8004697C();
}

void *func_ovl14_01_80048D48(void *arg0) {
    if ((D_ovl14_01_8004D54C == 0) && (D_ovl14_01_8004D550 == 0)) {
        return NULL;
    }
    if ((D_ovl14_01_8004D54C != 0) && (D_ovl14_01_8004D550 != 0)) {
        if (arg0 == (void *)0x1C8) {
            return (void *)0x1C9;
        }
        return (void *)0x1C8;
    }
    if (!(*D_ovl14_01_8004D4E0 & 2)) {
        if (D_ovl14_01_8004D54C != 0) {
            return (void *)0x1C8;
        }
        return (void *)0x1C9;
    }
    return (void *)0x1C8;
}

void func_ovl14_01_80048CE8(Vec3f *arg0, s32 arg1) {
    D_ovl14_01_8004D6D0.x = (f32) arg0->x;
    D_ovl14_01_8004D6D0.y = (f32) arg0->y;
    D_ovl14_01_8004D6D0.z = (f32) arg0->z;
    D_ovl14_01_8004D6DC = arg1;
    func_ovl14_01_8004C9E8(func_ovl14_01_80049B70, NULL, 0, 0, 0x150);
}

void func_ovl14_01_80048ABC(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    Vec3f sp40;
    Vec3f sp34_v;
    Vec3f sp28_v;
    Link_ovl14_01 *temp_a3;
    f32 var_fa0;

    arg1->unk0 = 2;
    M2C_FIELD(arg1, s32 *, 0x14) = 2;
    temp_a3 = arg1 + 0x28;
    arg1->unkC = 1.0f;
    M2C_FIELD(arg1, f32 *, 0x20) = 1.0f;
    arg1->unk10 = 0.0f;
    arg1->unk8 = 0.0f;
    M2C_FIELD(arg1, f32 *, 0x24) = 0.0f;
    M2C_FIELD(arg1, f32 *, 0x1C) = 0.0f;
    arg1->unk4 = 250.0f;
    M2C_FIELD(arg1, f32 *, 0x18) = 60.0f;
    M2C_FIELD(arg1, s32 *, 0x28) = 0x10002;
    temp_a3->unkC = 1.0f;
    temp_a3->unk10 = 0.0f;
    temp_a3->unk8 = 0.0f;
    temp_a3->unk4 = 420.0f;
    sp34_v.x = D_ovl14_01_8004D5F4->unk40->unk10;
    sp34_v.y = D_ovl14_01_8004D5F4->unk40->unk14;
    sp28_v.y = D_ovl14_01_8004D4A0.y + 150.0f;
    sp28_v.x = D_ovl14_01_8004D4A0.x;
    sp34_v.z = D_ovl14_01_8004D5F4->unk40->unk18;
    sp28_v.z = D_ovl14_01_8004D4A0.z;
    func_ovl14_01_8004C828(&sp34_v, &sp28_v, &sp40);
    func_ovl14_01_8004C8A0(arg0[1], 0x500000);
    func_ovl14_01_8004C898(arg0[1], 0x300000);
    if (sp40.y >= 360.0f) {
        arg0[1]->unk50 = sp40.y - 360.0f;
    } else {
        if (sp40.y < 0.0f) {
            var_fa0 = sp40.y + 360.0f;
        } else {
            var_fa0 = sp40.y;
        }
        arg0[1]->unk50 = var_fa0;
    }
    arg0[1]->unk4C = sp40.x;
    func_ovl14_01_8004C8A0(arg0[3], 0x500000);
    arg0[3]->unk50 = 0.0f;
    func_ovl14_01_8004C8A0(arg0[4], 0x30);
    func_ovl14_01_8004C898(arg0[4], 0xC00);
    func_ovl14_01_8004C8A0(arg0[4], 0x10);
    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        func_ovl14_01_8004C8A0(arg0[4], 0x400);
    } else {
        func_ovl14_01_8004C8A0(arg0[4], 0x800);
    }
    arg0[4]->unk40->unk28 = 1.0f;
    arg0[4]->unk40->unk2C = 1.0f;
    arg0[4]->unk40->unk30 = 1.0f;
}

void func_ovl14_01_800488B0(void) {
    Vec3f sp64_v;
    Vec3f sp58_v;
    s32 sp54;
    Vec3f sp2C_v;
    Vec3f sp1C_v;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    sp58_v.y = D_ovl14_01_8004D690.y + -300.0f;
    sp58_v.x = D_ovl14_01_8004D690.x;
    sp64_v.x = D_ovl14_01_8004D690.x;
    sp64_v.y = D_ovl14_01_8004D690.y;
    sp58_v.z = D_ovl14_01_8004D690.z;
    sp64_v.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_80047594(&sp58_v, 0x1E);
    var_a1 = 0;
    if (D_ovl14_01_8004D554 != 0) {
        var_a1 = 1;
    }
    if (D_ovl14_01_8004D54C != 0) {
        var_a1 += 1;
    }
    if (D_ovl14_01_8004D550 != 0) {
        var_a1 += 1;
    }
    sp54 = var_a1;
    func_ovl14_01_8004882C();
    func_ovl14_01_80048454();
    func_ovl14_01_800487A8();
    if ((D_ovl14_01_8004D544 == 0) || (var_v0 = 0, (D_ovl14_01_8004D548 == 0))) {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        sp54 = var_a1;
        func_ovl14_01_8004CA08(0x3C);
        var_v1 = 0;
        if (D_ovl14_01_8004D554 != 0) {
            var_v1 = 1;
        }
        if (D_ovl14_01_8004D54C != 0) {
            var_v1 += 1;
        }
        if (D_ovl14_01_8004D550 != 0) {
            var_v1 += 1;
        }
        if (var_a1 != var_v1) {
            func_ovl14_01_80047730(0x1E);
            sp2C_v.x = sp64_v.x;
            sp2C_v.z = sp64_v.z;
            sp2C_v.y = D_ovl14_01_8004D690.y;
            func_ovl14_01_80047594(&sp2C_v, 0x1E);
            func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0xA);
            sp1C_v.y = D_ovl14_01_8004D6B0.y;
            sp1C_v.x = D_ovl14_01_8004D690.x;
            sp1C_v.z = D_ovl14_01_8004D690.z;
            func_ovl14_01_800431C4(0xFD, D_ovl14_01_8004D5DC);
            func_ovl14_01_80047594(&sp1C_v, 0x3C);
        } else {
            func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0xA);
            func_ovl14_01_80047594(&sp64_v, 0x1E);
        }
        D_ovl14_01_8004D690.x = sp64_v.x;
        D_ovl14_01_8004D690.x = sp64_v.y;
        D_ovl14_01_8004D690.z = sp64_v.z;
        return;
    }
    func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0x3C);
}

void func_ovl14_01_8004882C(void) {
    s32 i;

    func_ovl14_01_8004CC60(0x414);
    for (i = 0; i < 10; i++) {
        D_ovl14_01_8004D684 += 0.05f;
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004CC68(0x414);
}

void func_ovl14_01_800487A8(void) {
    s32 i;

    func_ovl14_01_8004CC60(0x414);
    for (i = 0; i < 10; i++) {
        D_ovl14_01_8004D684 -= 0.05f;
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004CC68(0x414);
}

void func_ovl14_01_80048454(void) {
    f32 sp84;
    Vec3f sp68;
    Vec3f sp5C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_s0;
    s32 var_v0;
    s32 var_v0_2;

    func_ovl14_01_80044B38(&D_ovl14_01_8004D4A0, 0xA);
    func_ovl14_01_80046648(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
    func_ovl14_01_80046648(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
    if (func_ovl14_01_8004CBA8(1) != 0) {
        var_fs2 = 2.0f;
    } else {
        var_fs2 = -2.0f;
    }
    if (func_ovl14_01_8004CBA8(1) != 0) {
        sp84 = 0.5f;
    } else {
        sp84 = -0.5f;
    }
    if (*D_ovl14_01_8004D4E0 & 2) {
        var_fs2 = -2.0f;
        sp84 = -0.5f;
    }
    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        var_fs2 *= 0.5f;
    }
    func_ovl14_01_8004C828(&D_ovl14_01_8004D518, &D_ovl14_01_8004D690, &sp68);
    temp_fv0 = sp68.y - 90.0f;
    if (temp_fv0 >= 360.0f) {
        sp68.y = temp_fv0 - 360.0f;
    } else {
        if (sp68.y < 90.0f) {
            var_fv1 = temp_fv0 + 360.0f;
        } else {
            var_fv1 = temp_fv0;
        }
        sp68.y = var_fv1;
    }
    var_fs1 = 0.0f;
    D_ovl14_01_8004D4E4 = func_ovl14_01_800431C4(0xF5, D_ovl14_01_8004D5DC);
    if (0.0f < 360.0f) {
        if ((D_ovl14_01_8004D544 == 0) || (var_v0 = 0, (D_ovl14_01_8004D548 == 0))) {
            var_v0 = 1;
        }
        if (var_v0 == 0) {
loop_21:
            D_ovl14_01_8004D6A0.x = WRAP360(D_ovl14_01_8004D6A0.x + var_fs2);
            func_ovl14_01_8004C830(&sp68, &sp5C);
            temp_fa0 = D_ovl14_01_8004D518.y + sp5C.y;
            temp_fa1 = D_ovl14_01_8004D518.z + sp5C.z;
            D_ovl14_01_8004D690.x = D_ovl14_01_8004D518.x + sp5C.x;
            D_ovl14_01_8004D690.y = temp_fa0;
            D_ovl14_01_8004D690.z = temp_fa1;
            sp68.x = sp68.x + sp84;
            temp_s0 = func_ovl14_01_80046AE8();
            func_ovl14_01_8004CA30();
            var_fs1 += 0.5f;
            if ((var_fs1 < 360.0f) && (temp_s0 == 0)) {
                if ((D_ovl14_01_8004D544 == 0) || (var_v0_2 = 0, (D_ovl14_01_8004D548 == 0))) {
                    var_v0_2 = 1;
                }
                if (var_v0_2 == 0) {
                    goto loop_21;
                }
            }
        }
    }
    func_ovl14_01_8004CFA0(D_ovl14_01_8004D4E4);
    D_ovl14_01_8004D4E4 = -1;
    func_ovl14_01_8004697C();
    func_ovl14_01_80043010(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
    func_ovl14_01_80043010(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
}

void func_ovl14_01_800481B8(s32 arg0) {
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s6;

    var_s2 = 0;
    var_s3 = 0;
    func_ovl14_01_8004C8A0(D_ovl14_01_8004D5F0, 0x400000);
    func_ovl14_01_8004C898(D_ovl14_01_8004D5F0, 0x200000);
    var_s6 = 0x1E;
    var_s0 = 0;
    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        var_s6 = (s32) ((f32) 0x1E * 1.5f);
    }
    var_s1 = 0;
    if ((arg0 > 0) && (D_ovl14_01_8004D548 != 0)) {
loop_5:
        D_ovl14_01_8004D5F0->unk40->unk28 = func_ovl14_01_8004CB90(((f32) var_s0 / (f32) var_s6) * 180.0f) + 1.0f;
        temp_v0 = D_ovl14_01_8004D5F0->unk40;
        temp_v0->unk30 = temp_v0->unk28;
        if (var_s6 < var_s0) {
            var_s0 = 0;
            func_ovl14_01_8004C9E8(func_ovl14_01_80047E44, NULL, 0, 0, 0x110);
            var_s1 += 1;
            D_ovl14_01_8004D6BC += 1;
        }
        var_s2 = func_ovl14_01_80047344();
        var_s3 = func_ovl14_01_80046AE8();
        func_ovl14_01_8004CA30();
        var_s0 += 1;
        if ((var_s1 < arg0) && (var_s2 == 0) && (var_s3 == 0) && (D_ovl14_01_8004D548 != 0)) {
            goto loop_5;
        }
    }
    D_ovl14_01_8004D5F0->unk40->unk30 = 1.0f;
    temp_v0_2 = D_ovl14_01_8004D5F0->unk40;
    temp_v0_2->unk28 = temp_v0_2->unk30;
    func_ovl14_01_8004C8A0(D_ovl14_01_8004D5F0, 0x200000);
    func_ovl14_01_8004C898(D_ovl14_01_8004D5F0, 0x400000);
    if ((D_ovl14_01_8004D6BC != 0) && (var_s2 == 0) && (var_s3 == 0)) {
loop_14:
        var_s2 = func_ovl14_01_80047344();
        var_s3 = func_ovl14_01_80046AE8();
        func_ovl14_01_8004CA30();
        if ((D_ovl14_01_8004D6BC != 0) && (var_s2 == 0)) {
            if (var_s3 == 0) {
                goto loop_14;
            }
        }
    }
    func_ovl14_01_8004697C();
    if ((var_s2 != 0) && (var_s3 == 0)) {
        func_ovl14_01_80046CE8();
    }
}

void func_ovl14_01_80047E44(void) {
    Vec3f sp50_v;
    Vec3f sp44_v;
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_2;
    UnkStructA *temp_v0_3;
    UnkStructA_40 *temp_v1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f64 temp_ft2;
    s32 var_v0;
    s32 var_v0_2;

    temp_v0 = func_ovl14_01_8004C8C0(0x1B6, 0x01000080, 0x40, NULL);
    temp_v0->unk34 = 100.0f;
    temp_v0->unk38 = 100.0f;
    temp_v0_2 = func_ovl14_01_8004C8C0(0x1B7, 0x480000, 0xD0, temp_v0);
    temp_v0_2->unk54 = 5.0f;
    temp_v0_3 = func_ovl14_01_8004C8D0(temp_v0);
    temp_fv0 = temp_v0->unk34 / 50.0f;
    temp_v0_3->unk54 = temp_fv0;
    temp_v0_3->unk4C = temp_fv0;
    temp_v0->unk40->unk10 = D_ovl14_01_8004D5F0->unk40->unk10;
    temp_v0->unk40->unk14 = D_ovl14_01_8004D5F0->unk40->unk14 + 100.0f;
    temp_v0->unk40->unk18 = D_ovl14_01_8004D5F0->unk40->unk18;
    sp44_v.x = temp_v0->unk40->unk10;
    sp44_v.y = temp_v0->unk40->unk14 + 100.0f;
    sp44_v.z = temp_v0->unk40->unk18;
    func_ovl14_01_8004CE40(0xE, (f32 *)&sp44_v, 0);
    temp_ft2 = func_ovl14_01_8004CBA0() * 100.0 * 360.0;
    sp50_v.y = 0.0f;
    sp50_v.x = (f32) temp_ft2;
    sp50_v.z = (f32) (func_ovl14_01_8004CBA0() * 100.0 * 6.0);
    func_ovl14_01_8004C830(&sp50_v, &sp44_v);
    func_ovl14_01_800431C4(0xF9, temp_v0);
    temp_v0->unk68 = 60.0f;
loop_1:
    temp_v1 = temp_v0->unk40;
    var_v0 = 0;
    if (temp_v1->unk14 <= func_ovl14_01_8004BEC0()) {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        temp_fv0_2 = temp_v0->unk68;
        if (temp_fv0_2 != 0.0f) {
            if ((temp_fv0_2 <= temp_v0->unk6C) && !(temp_v0_2->unk8 & 0x01000000)) {
                temp_v1->unk10 = D_ovl14_01_8004D518.x + sp44_v.x;
                temp_v0->unk40->unk18 = D_ovl14_01_8004D518.z + sp44_v.z;
                func_ovl14_01_8004C898(temp_v0_2, 0x01000000);
            }
            func_ovl14_01_8004C918(temp_v0);
            func_ovl14_01_8004C9A8(temp_v0);
            func_ovl14_01_8004CA30();
            goto loop_1;
        }
    }
    var_v0_2 = 0;
    if (temp_v0->unk40->unk14 <= func_ovl14_01_8004BEC0()) {
        var_v0_2 = 1;
    }
    if (var_v0_2 != 0) {
        func_ovl14_01_80047978(temp_v0);
    } else {
        func_ovl14_01_800431C4(0xFA, temp_v0);
        sp44_v.x = temp_v0->unk40->unk10;
        sp44_v.y = temp_v0->unk40->unk14 + 10.0f;
        sp44_v.z = temp_v0->unk40->unk18;
        func_ovl14_01_8004CE40(0xA, (f32 *)&sp44_v, 0);
    }
    D_ovl14_01_8004D6BC -= 1;
    func_ovl14_01_8004C8B0(temp_v0);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80047CDC(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv1;
    s32 *temp_s0;

    temp_s0 = func_ovl14_01_8004CA10();
    temp_v0 = func_ovl14_01_8004C8C0(0x116, 0x01200000, 0xD0, D_ovl14_01_8004D5EC);
    temp_v0->unk40->unk30 = 5.0f;
    temp_v1 = temp_v0->unk40;
    temp_fv1 = temp_v1->unk30;
    temp_v1->unk2C = temp_fv1;
    temp_v0->unk40->unk28 = temp_fv1;
    temp_v0->unk50 = 0.0f;
    D_ovl14_01_8004D4E8 = func_ovl14_01_8004CF70(0x107);
    if (*temp_s0 != 0) {
        do {
            temp_v0_2 = temp_v0->unk40;
            temp_v0_2->unk20 = WRAP360(temp_v0_2->unk20 + 5.0f);
            func_ovl14_01_8004CA30();
        } while (*temp_s0 != 0);
    }
    func_ovl14_01_8004CFA0(D_ovl14_01_8004D4E8);
    D_ovl14_01_8004D4E8 = -1;
    func_ovl14_01_8004C8B0(temp_v0);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80047A10(void) {
    Vec3f sp4C_v;
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 var_fs1;
    s32 var_s1;
    s32 var_v1;
    s32 var_v1_2;

    temp_v0 = func_ovl14_01_8004C8C0(0x1C6, 0x01008800, 0x60, NULL);
    temp_v0->unk30 = 4;
    temp_v0->unk34 = 100.0f;
    temp_v0->unk38 = 200.0f;
    temp_v0_2 = func_ovl14_01_8004C8D0(temp_v0);
    temp_fv0 = temp_v0->unk34 / 50.0f;
    var_fs1 = 50.0f;
    var_s1 = 0;
    temp_v0_2->unk54 = temp_fv0;
    temp_v0_2->unk4C = temp_fv0;
    temp_fv0_2 = D_ovl14_01_8004D5F0->unk40->unk10;
    temp_v0->unk40->unk10 = temp_fv0_2;
    sp4C_v.x = temp_fv0_2;
    temp_fv0_3 = D_ovl14_01_8004D5F0->unk40->unk18;
    temp_v0->unk40->unk18 = temp_fv0_3;
    sp4C_v.x = (D_ovl14_01_8004D518.x - sp4C_v.x) / 100.0f;
    sp4C_v.z = (D_ovl14_01_8004D518.z - temp_fv0_3) / 100.0f;
    do {
        temp_v0->unk68 = var_fs1;
        if (var_s1 >= 3) {
            func_ovl14_01_8004C898(temp_v0, 0x40000);
            func_ovl14_01_8004C8A0(temp_v0, 0x8810);
        }
loop_3:
        temp_v0_3 = temp_v0->unk40;
        var_v1 = 0;
        if (temp_v0_3->unk14 <= func_ovl14_01_8004BEC0()) {
            var_v1 = 1;
        }
        if (var_v1 != 0) {
            var_s1 = 5;
        } else if (temp_v0->unk68 == 0.0f) {
            if (var_s1 < 2) {
                func_ovl14_01_800431C4(0x111, temp_v0);
            }
        } else {
            temp_v0_3->unk10 += sp4C_v.x;
            temp_v0_4 = temp_v0->unk40;
            temp_v0_4->unk18 += sp4C_v.z;
            func_ovl14_01_8004C918(temp_v0);
            func_ovl14_01_8004CA30();
            goto loop_3;
        }
        var_s1 += 1;
        sp4C_v.x *= 0.7f;
        var_fs1 *= 0.7f;
        sp4C_v.z *= 0.7f;
    } while (var_s1 < 5);
    temp_v0_5 = temp_v0->unk40;
    var_v1_2 = 0;
    if (temp_v0_5->unk14 <= func_ovl14_01_8004BEC0()) {
        var_v1_2 = 1;
    }
    if (var_v1_2 != 0) {
        func_ovl14_01_80047978(temp_v0);
    } else {
        sp4C_v.x = temp_v0_5->unk10;
        sp4C_v.y = temp_v0->unk40->unk14 + 100.0f;
        sp4C_v.z = temp_v0->unk40->unk18;
        func_ovl14_01_8004CE40(0xF, (f32 *)&sp4C_v, 0);
    }
    func_ovl14_01_8004C8B0(temp_v0);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80047978(UnkStructA *arg0) {
    Vec3f pos;

    pos.x = arg0->unk40->unk10;
    pos.y = arg0->unk40->unk14 + 100.0f;
    pos.z = arg0->unk40->unk18;
    func_ovl14_01_8004C8A0(arg0, 0x01000000);
    func_ovl14_01_8004CE40(7, (f32 *)&pos, 0);
    pos.y += 100.0f;
    func_ovl14_01_8004CE40(0xD, (f32 *)&pos, 0);
    func_ovl14_01_8004CF98(0xB4, (f32 *)&pos);
}

void func_ovl14_01_800477EC(s32 arg0) {
    Vec3f sp5C_v;
    Vec3f sp4C_v;
    Vec3f sp34_v;
    Vec3f sp24_v;
    Vec3f *temp_v1;
    Vec3f *temp_v1_2;
    s32 temp_v0;
    s32 temp_v0_2;

    func_ovl14_01_80047730(0x3C);
    temp_v0 = func_ovl14_01_8004CBA8(7);
    temp_v1 = &D_ovl14_01_8004D6F0[temp_v0];
    D_ovl14_01_8004D6CC = temp_v0;
    sp5C_v.y = D_ovl14_01_8004D690.y;
    sp5C_v.x = temp_v1->x;
    sp5C_v.z = temp_v1->z;
    func_ovl14_01_80047594(&sp5C_v, 0x1E);
    D_ovl14_01_8004D6C8 = D_ovl14_01_8004D6CC;
    func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0x1E);
    sp4C_v.y = D_ovl14_01_8004D6F0[0].y - 600.0f;
    sp4C_v.x = D_ovl14_01_8004D690.x;
    sp4C_v.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_80047594(&sp4C_v, 0x1E);
    func_ovl14_01_8004739C(D_ovl14_01_8004D6C4);
    func_ovl14_01_80047730(0x1E);
    temp_v0_2 = func_ovl14_01_8004CBA8(7);
    temp_v1_2 = &D_ovl14_01_8004D6F0[temp_v0_2];
    D_ovl14_01_8004D6CC = temp_v0_2;
    sp34_v.x = temp_v1_2->x;
    sp34_v.z = temp_v1_2->z;
    sp34_v.y = D_ovl14_01_8004D690.y;
    func_ovl14_01_80047594(&sp34_v, 0x1E);
    D_ovl14_01_8004D6C8 = D_ovl14_01_8004D6CC;
    func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0x1E);
    sp24_v.y = D_ovl14_01_8004D6B0.y;
    sp24_v.x = D_ovl14_01_8004D690.x;
    sp24_v.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_800431C4(0xFD, D_ovl14_01_8004D5DC);
    func_ovl14_01_80047594(&sp24_v, 0x3C);
}

void func_ovl14_01_80047798(s32 arg0) {
    Vec3f pos;

    pos.x = D_ovl14_01_8004D690.x;
    pos.y = D_ovl14_01_8004D6F0[0].y - 600.0f;
    pos.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_80047594(&pos, arg0);
}

void func_ovl14_01_80047730(s32 arg0) {
    Vec3f pos;

    pos.x = D_ovl14_01_8004D690.x;
    pos.y = D_ovl14_01_8004D6F0[0].y - 1000.0f;
    pos.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_800431C4(0xFC, D_ovl14_01_8004D5DC);
    func_ovl14_01_80047594(&pos, arg0);
}

void func_ovl14_01_800476F8(f32 arg0, f32 arg1, s32 arg2) {
    Vec3f pos;

    pos.x = arg0;
    pos.z = arg1;
    pos.y = D_ovl14_01_8004D690.y;
    func_ovl14_01_80047594(&pos, arg2);
}

void func_ovl14_01_8004769C(s32 arg0) {
    Vec3f pos;

    pos.x = D_ovl14_01_8004D690.x;
    pos.y = D_ovl14_01_8004D6B0.y;
    pos.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_800431C4(0xFD, D_ovl14_01_8004D5DC);
    func_ovl14_01_80047594(&pos, arg0);
}

void func_ovl14_01_80047594(Vec3f *arg0, s32 arg1) {
    Vec3f sp44;
    Vec3f sp38;
    s32 i;

    func_ovl14_01_8004C828(&D_ovl14_01_8004D690, arg0, &sp38);
    sp38.y = WRAP360(sp38.y - 90.0f);
    sp38.z /= (f32) arg1;
    func_ovl14_01_8004C830(&sp38, &sp44);
    for (i = 0; i < arg1; i++) {
        D_ovl14_01_8004D690.x += sp44.x;
        D_ovl14_01_8004D690.y += sp44.y;
        D_ovl14_01_8004D690.z += sp44.z;
        func_ovl14_01_8004CA30();
    }
}

void func_ovl14_01_8004739C(s32 arg0) {
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s5;
    s32 var_v0;
    s32 var_v0_2;

    var_s1 = 0;
    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        var_s5 = 0x64;
    } else {
        var_s5 = 0x3C;
    }
    var_s3 = 0;
    var_s2 = 0;
    if (arg0 > 0) {
        if ((D_ovl14_01_8004D544 == 0) || (var_v0 = 0, (D_ovl14_01_8004D548 == 0))) {
            var_v0 = 1;
        }
        var_s0 = var_s5 + 1;
        if (var_v0 == 0) {
loop_8:
            if (var_s5 < var_s0) {
                func_ovl14_01_8004C9E8(func_ovl14_01_80045474, D_ovl14_01_8004D208, 0, 0, 0x110);
                D_ovl14_01_8004D208 = (void *) ((s32) D_ovl14_01_8004D208 ^ 1);
                var_s0 = 0;
                var_s2 += 1;
            }
            var_s3 = func_ovl14_01_80047344();
            var_s1 = func_ovl14_01_80046AE8();
            func_ovl14_01_8004CA30();
            if ((var_s2 < arg0) && (var_s3 == 0) && (var_s1 == 0)) {
                if ((D_ovl14_01_8004D544 == 0) || (var_v0_2 = 0, (D_ovl14_01_8004D548 == 0))) {
                    var_v0_2 = 1;
                }
                var_s0 += 1;
                if (var_v0_2 == 0) {
                    goto loop_8;
                }
            }
        }
    }
    var_s0_2 = 0;
    if ((var_s3 == 0) && (var_s1 == 0) && (D_ovl14_01_8004D548 != 0)) {
loop_20:
        var_s3 = func_ovl14_01_80047344();
        var_s1 = func_ovl14_01_80046AE8();
        func_ovl14_01_8004CA30();
        var_s0_2 += 1;
        if ((var_s0_2 < 0x12C) && (var_s3 == 0) && (var_s1 == 0)) {
            if (D_ovl14_01_8004D548 != 0) {
                goto loop_20;
            }
        }
    }
    func_ovl14_01_8004697C();
    if ((var_s3 != 0) && (var_s1 == 0)) {
        func_ovl14_01_80046CE8();
    }
}

s32 func_ovl14_01_80047344(void) {
    s32 flags;

    flags = 0;
    if (D_ovl14_01_8004D554 != 0) {
        flags = D_ovl14_01_8004D5F0->unk10;
    }
    flags |= D_ovl14_01_8004D5E8->unk10;
    if ((flags & 0x2002) == 0x2002) {
        flags = 1;
    } else {
        flags = 0;
    }
    return flags;
}

void func_ovl14_01_80046CE8(void) {
    s32 spCC;
    s32 spC4;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA0;
    f32 sp9C;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;

    if ((D_ovl14_01_8004D544 == 0) || (var_v0 = 0, (D_ovl14_01_8004D548 == 0))) {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        D_ovl14_01_8004D6C0 = 5;
        func_ovl14_01_8004CC60(0x418);
        func_ovl14_01_8004CC60(0x41B);
        spCC = 1;
        var_s3 = 0;
        var_s2 = 0;
        var_fs1 = 0.0f;
        var_fs2 = 0.0f;
        spAC = 3.0f;
        spB4 = D_ovl14_01_8004D6A0.y;
        spB0 = D_ovl14_01_8004D6A0.x;
        if (func_ovl14_01_8004CBA8(1) != 0) {
            spAC = 3.0f * -1.0f;
        }
        spA8 = 6.0f;
        if (func_ovl14_01_8004CBA8(1) != 0) {
            spA8 = 6.0f * -1.0f;
        }
        spA0 = D_ovl14_01_8004D690.y;
        sp9C = ((D_ovl14_01_8004D6B0.y - 230.0f) - D_ovl14_01_8004D690.y) / 60.0f;
        func_ovl14_01_80043250(0);
        func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
        func_ovl14_01_8004C9E8(func_ovl14_01_80047CDC, &spCC, 0, 0, 0x150);
        var_s0 = 0;
        if ((D_ovl14_01_8004D544 == 0) || (var_v0_2 = 0, (D_ovl14_01_8004D548 == 0))) {
            var_v0_2 = 1;
        }
        if (var_v0_2 == 0) {
loop_13:
            D_ovl14_01_8004D690.y += sp9C;
            temp_fv1 = var_fs2 + spAC;
            D_ovl14_01_8004D6A0.y = (f32) ((func_ovl14_01_8004CB90(var_fs2) * 10.0f) + spB4);
            if (temp_fv1 >= 360.0f) {
                var_fs2 = temp_fv1 - 360.0f;
            } else {
                if (temp_fv1 < 0.0f) {
                    var_fv0 = temp_fv1 + 360.0f;
                } else {
                    var_fv0 = temp_fv1;
                }
                var_fs2 = var_fv0;
            }
            temp_fv1_2 = var_fs1 + spA8;
            D_ovl14_01_8004D6A0.x = (func_ovl14_01_8004CB90(var_fs1) * 10.0f) + spB0;
            if (temp_fv1_2 >= 360.0f) {
                var_fs1 = temp_fv1_2 - 360.0f;
            } else {
                if (temp_fv1_2 < 0.0f) {
                    var_fv0_2 = temp_fv1_2 + 360.0f;
                } else {
                    var_fv0_2 = temp_fv1_2;
                }
                var_fs1 = var_fv0_2;
            }
            var_s3 = func_ovl14_01_80046AE8();
            if (var_s0 >= 0x1F) {
                var_s2 = func_ovl14_01_80046C38();
            } else {
                var_s2 = 0;
            }
            func_ovl14_01_8004CA30();
            var_s0 += 1;
            if ((var_s0 < 0x3C) && (var_s2 == 0)) {
                if (var_s3 == 0) {
                    if ((D_ovl14_01_8004D544 == 0) || (var_v0_3 = 0, (D_ovl14_01_8004D548 == 0))) {
                        var_v0_3 = 1;
                    }
                    if (var_v0_3 != 0) {

                    } else {
                        goto loop_13;
                    }
                }
            }
        }
        spC4 = 0x12C;
        var_s0_2 = 0;
        if (func_ovl14_01_8004CC70(0x41F) != 0) {
            spC4 = (s32) ((f64) 0x12C * 1.5);
        }
        if ((spC4 > 0) && (var_s2 == 0) && (var_s3 == 0)) {
            if ((D_ovl14_01_8004D544 == 0) || (var_v0_4 = 0, (D_ovl14_01_8004D548 == 0))) {
                var_v0_4 = 1;
            }
            if (var_v0_4 == 0) {
loop_45:
                temp_fv1_3 = var_fs2 + spAC;
                D_ovl14_01_8004D6A0.y = (f32) ((func_ovl14_01_8004CB90(var_fs2) * 10.0f) + spB4);
                if (temp_fv1_3 >= 360.0f) {
                    var_fs2 = temp_fv1_3 - 360.0f;
                } else {
                    if (temp_fv1_3 < 0.0f) {
                        var_fv0_3 = temp_fv1_3 + 360.0f;
                    } else {
                        var_fv0_3 = temp_fv1_3;
                    }
                    var_fs2 = var_fv0_3;
                }
                temp_fv1_4 = var_fs1 + spA8;
                D_ovl14_01_8004D6A0.x = (func_ovl14_01_8004CB90(var_fs1) * 10.0f) + spB0;
                if (temp_fv1_4 >= 360.0f) {
                    var_fs1 = temp_fv1_4 - 360.0f;
                } else {
                    if (temp_fv1_4 < 0.0f) {
                        var_fv0_4 = temp_fv1_4 + 360.0f;
                    } else {
                        var_fv0_4 = temp_fv1_4;
                    }
                    var_fs1 = var_fv0_4;
                }
                var_s2 = func_ovl14_01_80046C38();
                var_s3 = func_ovl14_01_80046AE8();
                func_ovl14_01_8004CA30();
                var_s0_2 += 1;
                if ((var_s0_2 < spC4) && (var_s2 == 0) && (var_s3 == 0)) {
                    if ((D_ovl14_01_8004D544 == 0) || (var_v0_5 = 0, (D_ovl14_01_8004D548 == 0))) {
                        var_v0_5 = 1;
                    }
                    if (var_v0_5 == 0) {
                        goto loop_45;
                    }
                }
            }
        }
        spCC = 0;
        var_s0_3 = 0;
        if (D_ovl14_01_8004D548 == 0) {
            func_ovl14_01_8004CA08(0x3C);
        }
        if (var_s3 != 0) {
            func_ovl14_01_80043250(1);
            func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
            func_ovl14_01_8004697C();
        } else {
            func_ovl14_01_80043250(1);
            func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
        }
        if ((var_s2 != 0) && (var_s3 == 0)) {
            if ((D_ovl14_01_8004D544 == 0) || (var_v0_6 = 0, (D_ovl14_01_8004D548 == 0))) {
                var_v0_6 = 1;
            }
            if (var_v0_6 == 0) {
                func_ovl14_01_80046004(var_s2);
            }
        }
        temp_fs2 = (spB4 - D_ovl14_01_8004D6A0.y) / 16.0f;
        sp9C = (spA0 - D_ovl14_01_8004D690.y) / 16.0f;
        temp_fs1 = (spB0 - D_ovl14_01_8004D6A0.x) / 16.0f;
        do {
            D_ovl14_01_8004D6A0.y = (f32) (D_ovl14_01_8004D6A0.y + temp_fs2);
            D_ovl14_01_8004D6A0.x += temp_fs1;
            D_ovl14_01_8004D690.y += sp9C;
            func_ovl14_01_8004CA30();
            var_s0_3 += 1;
        } while (var_s0_3 != 0x10);
        D_ovl14_01_8004D690.y = spA0;
        D_ovl14_01_8004D6A0.y = spB4;
        D_ovl14_01_8004D6A0.x = spB0;
        func_ovl14_01_8004CC68(0x41B);
    }
}

s32 func_ovl14_01_80046C38(void) {
    UnkStructA *obj;
    s32 ret;
    s32 flags;
    Vec3f pos;

    obj = func_ovl14_01_8004C920(D_ovl14_01_8004D5E4, 2);
    if (obj == NULL) {
        return 0;
    }
    flags = obj->unk8;
    if (flags & 0x10000) {
        return 0;
    }
    ret = 1;
    if (flags & 0x2000) {
        ret = 2;
    }
    if (func_ovl14_01_8004CC70(0x417) == 0) {
        func_ovl14_01_8004C968(obj, (f32 *)&pos);
        func_ovl14_01_8004CC18((f32 *)&pos);
    }
    func_ovl14_01_8004CC60(0x417);
    func_ovl14_01_80046B98(obj->unk28, obj->unk40->unk28);
    func_ovl14_01_8004CE60(obj);
    return ret;
}

void func_ovl14_01_80046B98(s32 arg0, f32 arg1) {
    UnkStructA *o;

    D_ovl14_01_8004D5F8 = func_ovl14_01_8004C8C0(arg0, 0x01600000, 0xD0, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5F8->unk50 = 550.0f;
    D_ovl14_01_8004D5F8->unk54 = 250.0f;
    D_ovl14_01_8004D5F8->unk40->unk28 = arg1;
    D_ovl14_01_8004D5F8->unk40->unk2C = arg1;
    D_ovl14_01_8004D5F8->unk40->unk30 = arg1;
}

s32 func_ovl14_01_80046AE8(void) {
    func_ovl14_01_8004CC60(0x41A);
    if ((D_ovl14_01_8004D554 <= 0) && (func_ovl14_01_8004CC70(0x41E) == 0)) {
        return 1;
    }
    if ((D_ovl14_01_8004D54C <= 0) && (func_ovl14_01_8004CC70(0x41D) == 0)) {
        return 1;
    }
    if ((D_ovl14_01_8004D550 <= 0) && (func_ovl14_01_8004CC70(0x41C) == 0)) {
        return 1;
    }
    func_ovl14_01_8004CC68(0x41A);
    return 0;
}

void func_ovl14_01_8004697C(void) {
    Vec3f sp34;

    if ((D_ovl14_01_8004D54C <= 0) && (func_ovl14_01_8004CC70(0x41D) == 0)) {
        func_ovl14_01_80045124(D_ovl14_01_8004D600[4]);
        func_ovl14_01_800467C0(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        func_ovl14_01_8004CC60(0x41D);
        func_ovl14_01_8004C968(D_ovl14_01_8004D600[0], (f32 *)&sp34);
        func_ovl14_01_8004CC18((f32 *)&sp34);
    }
    if ((D_ovl14_01_8004D550 <= 0) && (func_ovl14_01_8004CC70(0x41C) == 0)) {
        func_ovl14_01_80045124(D_ovl14_01_8004D618[4]);
        func_ovl14_01_800467C0(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
        func_ovl14_01_8004CC60(0x41C);
        func_ovl14_01_8004C968(D_ovl14_01_8004D618[0], (f32 *)&sp34);
        func_ovl14_01_8004CC18((f32 *)&sp34);
    }
    if (D_ovl14_01_8004D554 <= 0) {
        if (func_ovl14_01_8004CC70(0x41E) == 0) {
            func_ovl14_01_80045124(D_ovl14_01_8004D5F0);
            func_ovl14_01_8004654C();
            func_ovl14_01_8004CC60(0x41E);
            func_ovl14_01_8004C968(D_ovl14_01_8004D5F0, (f32 *)&sp34);
            func_ovl14_01_8004CC18((f32 *)&sp34);
        }
    }
}

void func_ovl14_01_800467C0(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    f32 sp40;
    f32 sp3C;
    f32 var_fs0;
    f32 var_fs0_2;
    s32 var_s0;
    s32 var_s0_2;

    sp40 = D_ovl14_01_8004D6A0.y;
    sp3C = D_ovl14_01_8004D6A0.x;
    if (arg1 == D_ovl14_01_8004D560) {
        var_fs0 = -45.0f;
    } else {
        var_fs0 = 45.0f;
    }
    func_ovl14_01_80046648(arg0, arg1);
    if (*arg0 == M2C_FIELD(D_ovl14_01_8004D600, UnkStructA **, 0)) {
        func_ovl14_01_800431C4(0xFE, M2C_FIELD(D_ovl14_01_8004D600, UnkStructA **, 0x10));
    } else {
        func_ovl14_01_800431C4(0xFE, D_ovl14_01_8004D618[4]);
    }
    var_s0 = 0;
    do {
        D_ovl14_01_8004D6A0.x += var_fs0 / 10.0f;
        D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.y + -1.0f;
        func_ovl14_01_8004CA30();
        var_s0 += 1;
    } while (var_s0 < 0xA);
    func_ovl14_01_80043688(arg0, arg1);
    func_ovl14_01_8004CA08(0x1E);
    var_s0_2 = 0;
    if (arg1 == D_ovl14_01_8004D560) {
        var_fs0_2 = 45.0f;
    } else {
        var_fs0_2 = -45.0f;
    }
    do {
        D_ovl14_01_8004D6A0.x += var_fs0_2 / 30.0f;
        D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.y + 0.33333334f;
        func_ovl14_01_8004CA30();
        var_s0_2 += 1;
    } while (var_s0_2 != 0x1E);
    D_ovl14_01_8004D6A0.y = sp40;
    D_ovl14_01_8004D6A0.x = sp3C;
}

void func_ovl14_01_80046648(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    Link_ovl14_01 *sp24;
    Link_ovl14_01 *temp_a2;

    sp24 = arg1;
    arg1->unk0 = 2;
    M2C_FIELD(arg1, s32 *, 0x14) = 2;
    temp_a2 = arg1 + 0x28;
    arg1->unk10 = 0.9f;
    arg1->unkC = 0.3f;
    arg1->unk4 = 250.0f;
    arg1->unk8 = 0.0f;
    M2C_FIELD(arg1, f32 *, 0x24) = 0.0f;
    M2C_FIELD(arg1, f32 *, 0x1C) = 0.0f;
    M2C_FIELD(arg1, f32 *, 0x20) = 1.0f;
    M2C_FIELD(arg1, f32 *, 0x18) = 60.0f;
    M2C_FIELD(arg1, s32 *, 0x28) = 0x10002;
    temp_a2->unk10 = 0.9f;
    temp_a2->unkC = 0.3f;
    temp_a2->unk8 = 0.0f;
    temp_a2->unk4 = 420.0f;
    func_ovl14_01_8004C8A0(arg0[1], 0x300000);
    func_ovl14_01_8004C898(arg0[1], 0x500000);
    arg0[1]->unk50 = 0.0f;
    if (sp24 == D_ovl14_01_8004D560) {
        arg0[1]->unk4C = -90.0f;
    } else {
        arg0[1]->unk4C = 90.0f;
    }
    func_ovl14_01_8004C8A0(arg0[3], 0x500000);
    arg0[3]->unk50 = 0.0f;
    func_ovl14_01_8004C898(arg0[4], 0x30);
    func_ovl14_01_8004C8A0(arg0[4], 0xC00);
    arg0[4]->unk40->unk28 = 1.0f;
    arg0[4]->unk40->unk2C = 1.0f;
    arg0[4]->unk40->unk30 = 1.0f;
}

void func_ovl14_01_8004654C(void) {
    f32 sp38;
    s32 var_s0;
    s32 var_s0_2;

    func_ovl14_01_800431C4(0xFE, D_ovl14_01_8004D5F0);
    func_ovl14_01_8004C8A0(D_ovl14_01_8004D5F0, 0x01000000);
    func_ovl14_01_8004C9E8(func_ovl14_01_80047A10, NULL, 0, 0, 0x150);
    var_s0 = 0;
    sp38 = D_ovl14_01_8004D6A0.y;
    do {
        D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.y + -2.0f;
        func_ovl14_01_8004CA30();
        var_s0 += 1;
    } while (var_s0 < 0xA);
    func_ovl14_01_8004CA08(0x1E);
    var_s0_2 = 0;
    do {
        D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.y + 0.6666667f;
        func_ovl14_01_8004CA30();
        var_s0_2 += 1;
    } while (var_s0_2 != 0x1E);
    D_ovl14_01_8004D6A0.y = sp38;
}

void func_ovl14_01_80046004(s32 arg0) {
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp8C;
    f32 sp84;
    f32 sp80;
    f32 sp78;
    f32 sp74;
    UnkStructA *temp_s3;
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_2;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs2;
    s32 temp_ft1;
    s32 temp_t8;
    s32 var_s1;

    spB0 = D_ovl14_01_8004D5DC->unk4C;
    spB4 = D_ovl14_01_8004D5DC->unk50;
    spB8 = D_ovl14_01_8004D5DC->unk54;
    spA4 = D_ovl14_01_8004D5E0->unk4C;
    spA8 = D_ovl14_01_8004D5E0->unk50;
    spAC = D_ovl14_01_8004D5E0->unk54;
    var_fs2 = 0.0f;
    sp98 = D_ovl14_01_8004D5EC->unk4C;
    sp9C = D_ovl14_01_8004D5EC->unk50;
    sp8C = 0.0f;
    sp84 = 0.0f;
    sp80 = 0.0f;
    sp78 = 0.0f;
    sp74 = 0.0f;
    spA0 = D_ovl14_01_8004D5EC->unk54;
    func_ovl14_01_800431F8(D_ovl14_01_8004D5DC);
    func_ovl14_01_8004CA08(0x1E);
    temp_v0 = func_ovl14_01_8004C8C0(0x1CD, 0x01280000, 0xD0, D_ovl14_01_8004D5E8);
    temp_v0->unk50 = 450.0f;
    temp_v0_2 = func_ovl14_01_8004C8C0(0x1CE, 0x01280000, 0xD0, D_ovl14_01_8004D5DC);
    temp_v0_2->unk40->unk20 = D_ovl14_01_8004D6A0.x;
    temp_s3 = func_ovl14_01_8004C8C0(0x1CD, 0x01280000, 0xD0, D_ovl14_01_8004D5EC);
    func_ovl14_01_8004CC60(0x414);
    D_ovl14_01_8004D62C = 31.0f;
    D_ovl14_01_8004D630 = 31.0f;
    D_ovl14_01_8004D634 = 31.0f;
    D_ovl14_01_8004D684 = 0.0f;
    D_ovl14_01_8004D638 = 31.0f;
    D_ovl14_01_8004D63C = 31.0f;
    D_ovl14_01_8004D640 = 31.0f;
    D_ovl14_01_8004D688 = 0.0f;
    func_ovl14_01_800431C4(0xFF, D_ovl14_01_8004D5DC);
    var_s1 = 0;
    do {
        D_ovl14_01_8004D5DC->unk50 = (func_ovl14_01_8004CB90(var_fs2) * 100.0f) + spB4;
        D_ovl14_01_8004D5DC->unk54 = (func_ovl14_01_8004CB90(sp8C) * -50.0f) + spB8;
        D_ovl14_01_8004D5E0->unk50 = (func_ovl14_01_8004CB90(sp84) * 100.0f) + spA8;
        D_ovl14_01_8004D5E0->unk54 = (func_ovl14_01_8004CB90(sp80) * -50.0f) + spAC;
        D_ovl14_01_8004D5EC->unk50 = (func_ovl14_01_8004CB90(sp78) * 50.0f) + sp9C;
        D_ovl14_01_8004D5EC->unk54 = (func_ovl14_01_8004CB90(sp74) * -25.0f) + spA0;
        temp_fs1 = (f32) var_s1 / 30.0f;
        temp_fs0 = 180.0f * temp_fs1;
        var_fs2 = temp_fs0;
        sp8C = temp_fs0;
        sp84 = temp_fs0;
        sp80 = temp_fs0;
        sp78 = temp_fs0;
        sp74 = temp_fs0;
        temp_fa1 = func_ovl14_01_8004CB90(temp_fs1 * 90.0f) + 1.0f;
        temp_v0->unk40->unk28 = temp_fa1;
        temp_v0->unk40->unk30 = temp_fa1;
        temp_fv1 = temp_v0->unk40->unk30 * 0.5f;
        temp_s3->unk40->unk28 = temp_fv1;
        temp_s3->unk40->unk30 = temp_fv1;
        temp_fv1_2 = temp_v0->unk40->unk30;
        temp_v0_2->unk40->unk28 = temp_fv1_2;
        temp_ft1 = (s32) ((1.0f - temp_fs1) * 255.0f);
        temp_v0_2->unk40->unk30 = temp_fv1_2;
        temp_v0->unk40->unk36 = (s16) temp_ft1;
        temp_s3->unk40->unk36 = (s16) temp_ft1;
        temp_v0_2->unk40->unk36 = (s16) temp_ft1;
        D_ovl14_01_8004D684 = func_ovl14_01_8004CB90(temp_fs0);
        D_ovl14_01_8004D688 = D_ovl14_01_8004D684;
        func_ovl14_01_8004CA30();
        var_s1 += 1;
    } while (var_s1 != 0x1E);
    func_ovl14_01_8004C8B0(temp_v0);
    func_ovl14_01_8004C8B0(temp_v0_2);
    func_ovl14_01_8004C8B0(temp_s3);
    func_ovl14_01_8004CC68(0x414);
    D_ovl14_01_8004D62C = 31.0f;
    D_ovl14_01_8004D630 = 31.0f;
    D_ovl14_01_8004D634 = 31.0f;
    D_ovl14_01_8004D684 = 0.0f;
    D_ovl14_01_8004D638 = 0.0f;
    D_ovl14_01_8004D63C = 0.0f;
    D_ovl14_01_8004D640 = 0.0f;
    D_ovl14_01_8004D688 = 0.0f;
    D_ovl14_01_8004D5DC->unk4C = spB0;
    D_ovl14_01_8004D5DC->unk50 = spB4;
    D_ovl14_01_8004D5DC->unk54 = spB8;
    D_ovl14_01_8004D5E0->unk4C = spA4;
    D_ovl14_01_8004D5E0->unk50 = spA8;
    D_ovl14_01_8004D5E0->unk54 = spAC;
    D_ovl14_01_8004D5EC->unk4C = sp98;
    D_ovl14_01_8004D5EC->unk50 = sp9C;
    D_ovl14_01_8004D5EC->unk54 = spA0;
    temp_t8 = D_ovl14_01_8004D544 - arg0;
    D_ovl14_01_8004D544 = temp_t8;
    if (temp_t8 < 0) {
        D_ovl14_01_8004D544 = 0;
    }
    func_ovl14_01_8004C8B0(D_ovl14_01_8004D5F8);
    D_ovl14_01_8004D5F8 = NULL;
}

void func_ovl14_01_80045FD8(void) {
    func_ovl14_01_8004C8B0(D_ovl14_01_8004D5F8);
    D_ovl14_01_8004D5F8 = NULL;
}

void func_ovl14_01_80045FA0(void *arg0) {
    func_ovl14_01_8004C9E8(func_ovl14_01_80045474, arg0, 0, 0, 0x110);
}

void func_ovl14_01_80045D7C(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    f32 temp_fv0;
    f32 var_fs0;
    s32 var_s0;
    s32 var_s0_2;
    void *temp_s0;

    temp_s0 = func_ovl14_01_8004CA10();
    temp_v0 = func_ovl14_01_8004C8C0(0xA, 0x480000, 0xD0, D_ovl14_01_8004D5EC);
    if (temp_s0 == NULL) {
        temp_v0->unk4C = -70.0f;
    } else {
        temp_v0->unk4C = 70.0f;
    }
    temp_v0->unk50 = 35.0f;
    temp_v0->unk54 = 300.0f;
    func_ovl14_01_8004CA30();
    func_ovl14_01_8004C898(temp_v0, 0x01000000);
    func_ovl14_01_8004C8A0(temp_v0, 0x400000);
    temp_v0->unk40->unk36 = 0;
    temp_v0->unk40->unk1C = 90.0f;
    var_s0 = 0;
    do {
        temp_fv0 = (f32) var_s0 / 10.0f;
        var_fs0 = (temp_fv0 * 4.7f) + 0.3f;
        temp_v0->unk40->unk30 = var_fs0;
        temp_v0_2 = temp_v0->unk40;
        temp_v0_2->unk28 = temp_v0_2->unk30;
        temp_v0->unk40->unk36 = (s16) (s32) (temp_fv0 * 255.0f);
        func_ovl14_01_8004CA30();
        var_s0 += 1;
    } while (var_s0 < 0xA);
    var_s0_2 = 0x14;
    do {
        var_fs0 += 0.05f;
        temp_v0->unk40->unk30 = var_fs0;
        temp_v0_3 = temp_v0->unk40;
        temp_v0_3->unk28 = temp_v0_3->unk30;
        temp_v0->unk40->unk36 = (s16) (s32) (((f32) var_s0_2 / 20.0f) * 255.0f);
        func_ovl14_01_8004CA30();
        var_s0_2 -= 1;
    } while (var_s0_2 != 0);
    func_ovl14_01_8004C8B0(temp_v0);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800457F0(void) {
    f32 spB0;
    Vec3f spA4_v;
    Vec3f sp98;
    Vec3f sp8C;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fs4;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    s32 *var_s5;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_s2_2;
    void *temp_s0;

    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        var_fs4 = 4.0f;
    } else {
        var_fs4 = 6.8f;
    }
    temp_s0 = func_ovl14_01_8004CA10();
    temp_v0 = func_ovl14_01_8004C8C0(0x1CB, 0x480080, 0x40, D_ovl14_01_8004D5EC);
    temp_v0->unk30 = 2;
    temp_v0->unk38 = 100.0f;
    temp_v0->unk34 = 50.0f;
    if (temp_s0 == NULL) {
        var_s5 = &D_ovl14_01_8004D4F0;
        temp_v0->unk4C = -70.0f;
    } else {
        var_s5 = &D_ovl14_01_8004D4EC;
        temp_v0->unk4C = 70.0f;
    }
    temp_v0->unk54 = 100.0f;
    temp_v0->unk50 = 35.0f;
    spA4_v.x = D_ovl14_01_8004D4A0.x;
    spA4_v.y = D_ovl14_01_8004D4A0.y;
    spA4_v.z = D_ovl14_01_8004D4A0.z;
    func_ovl14_01_8004CA08(3);
    *var_s5 = func_ovl14_01_800431C4(0xF8, temp_v0);
    func_ovl14_01_8004C898(temp_v0, 0x01000000);
    func_ovl14_01_8004C8A0(temp_v0, 0x400000);
    func_ovl14_01_8004C968(temp_v0, &spB0);
    func_ovl14_01_8004C828((Vec3f *) &spB0, &spA4_v, &sp8C);
    temp_fv0 = sp8C.y - 180.0f;
    if (temp_fv0 >= 360.0f) {
        var_fv1 = temp_fv0 - 360.0f;
    } else {
        if (sp8C.y < 180.0f) {
            var_fa0 = temp_fv0 + 360.0f;
        } else {
            var_fa0 = temp_fv0;
        }
        var_fv1 = var_fa0;
    }
    sp8C.y = var_fv1 * -1.0f;
    var_s0 = 0;
    temp_v0->unk40->unk20 = sp8C.x;
    temp_v0->unk40->unk1C = sp8C.y;
    var_s2 = 0;
    do {
        if ((func_ovl14_01_8004CC70(0x41B) != 0) || (func_ovl14_01_8004CC70(0x41A) != 0) || (D_ovl14_01_8004D548 == 0)) {
            func_ovl14_01_8004CFA0(*var_s5);
            *var_s5 = -1;
            func_ovl14_01_8004C8B0(temp_v0);
            func_ovl14_01_8004C9F8();
        }
        temp_v0->unk40->unk36 = (s16) (s32) (((f32) var_s2 / 10.0f) * 255.0f);
        temp_v0_2 = temp_v0->unk40;
        temp_v0_2->unk2C += 1.0f;
        temp_v0_3 = temp_v0->unk40;
        temp_fv0_2 = sp8C.z * 0.01f;
        if (temp_fv0_2 < temp_v0_3->unk2C) {
            temp_v0_3->unk2C = temp_fv0_2;
            if (var_s0 >= 5) {
                sp7C = spA4_v.y + 50.0f;
                var_s0 = 0;
                sp78 = spA4_v.x;
                sp80 = spA4_v.z;
                func_ovl14_01_8004CE40(7, &sp78, 0);
            }
            var_s0 += 1;
        }
        func_ovl14_01_8004C9A8(temp_v0);
        func_ovl14_01_8004CA30();
        var_s2 += 1;
    } while (var_s2 < 0xA);
    var_s0_2 = 0;
    var_s2_2 = 0;
loop_23:
    if ((func_ovl14_01_8004CC70(0x41B) == 0) && (func_ovl14_01_8004CC70(0x41A) == 0) && (D_ovl14_01_8004D548 != 0)) {
        func_ovl14_01_8004C828(&spA4_v, &D_ovl14_01_8004D4A0, &sp8C);
        temp_fv0_3 = sp8C.y - 90.0f;
        if (temp_fv0_3 >= 360.0f) {
            sp8C.y = temp_fv0_3 - 360.0f;
        } else {
            if (sp8C.y < 90.0f) {
                var_fv1_2 = temp_fv0_3 + 360.0f;
            } else {
                var_fv1_2 = temp_fv0_3;
            }
            sp8C.y = var_fv1_2;
        }
        if (var_fs4 < sp8C.z) {
            sp8C.z = var_fs4;
        }
        func_ovl14_01_8004C830(&sp8C, &sp98);
        spA4_v.x += sp98.x;
        spA4_v.y += sp98.y;
        spA4_v.z += sp98.z;
        func_ovl14_01_8004C968(temp_v0, &spB0);
        func_ovl14_01_8004C828((Vec3f *) &spB0, &spA4_v, &sp8C);
        temp_fv0_4 = sp8C.y - 180.0f;
        if (temp_fv0_4 >= 360.0f) {
            var_fv1_3 = temp_fv0_4 - 360.0f;
        } else {
            if (sp8C.y < 180.0f) {
                var_fa0_2 = temp_fv0_4 + 360.0f;
            } else {
                var_fa0_2 = temp_fv0_4;
            }
            var_fv1_3 = var_fa0_2;
        }
        sp8C.y = var_fv1_3 * -1.0f;
        temp_v0->unk40->unk20 = sp8C.x;
        temp_v0->unk40->unk1C = sp8C.y;
        temp_v0->unk40->unk2C = sp8C.z * 0.01f;
        if (var_s0_2 >= 5) {
            var_s0_2 = 0;
            sp7C = spA4_v.y + 50.0f;
            sp78 = spA4_v.x;
            sp80 = spA4_v.z;
            func_ovl14_01_8004CE40(7, &sp78, 0);
        }
        var_s0_2 += 1;
        func_ovl14_01_8004C9A8(temp_v0);
        func_ovl14_01_8004CA30();
        var_s2_2 += 1;
        if (var_s2_2 != 0x28) {
            goto loop_23;
        }
    }
    func_ovl14_01_8004CFA0(*var_s5);
    *var_s5 = -1;
    func_ovl14_01_8004C8B0(temp_v0);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800455AC(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    f32 temp_fv0;
    s32 var_s0;
    void *temp_s0;

    temp_s0 = func_ovl14_01_8004CA10();
    temp_v0 = func_ovl14_01_8004C8C0(0x1CB, 0x480000, 0xD0, D_ovl14_01_8004D5EC);
    if (temp_s0 == NULL) {
        temp_v0->unk4C = -70.0f;
    } else {
        temp_v0->unk4C = 70.0f;
    }
    temp_v0->unk50 = 35.0f;
    temp_v0->unk54 = 150.0f;
    func_ovl14_01_8004CA08(1);
    temp_v0->unk40->unk28 = 0.25f;
    temp_v0->unk40->unk2C = 7.0f;
    temp_v0->unk40->unk30 = 0.25f;
    temp_v0->unk40->unk1C = (f32) ((func_ovl14_01_8004CBA0() * 120.0) + 30.0);
    temp_v0_2 = temp_v0->unk40;
    temp_v0_2->unk20 = (f32) ((f64) temp_v0_2->unk20 + ((func_ovl14_01_8004CBA0() * 120.0) - 60.0));
    func_ovl14_01_8004C898(temp_v0, 0x01000000);
    func_ovl14_01_8004C8A0(temp_v0, 0x400000);
    var_s0 = 0;
loop_4:
    if ((func_ovl14_01_8004CC70(0x41B) == 0) && (func_ovl14_01_8004CC70(0x41A) == 0)) {
        temp_fv0 = (f32) var_s0 / 30.0f;
        temp_v0->unk40->unk2C = ((1.0f - temp_fv0) * 7.0f) + 0.1f;
        temp_v0->unk40->unk36 = (s16) (s32) (temp_fv0 * 255.0f);
        func_ovl14_01_8004CA30();
        var_s0 += 1;
        if (var_s0 != 0x1E) {
            goto loop_4;
        }
    }
    func_ovl14_01_8004C8B0(temp_v0);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80045474(void) {
    s32 j;
    s32 i;
    void *obj;

    obj = func_ovl14_01_8004CA10();
    func_ovl14_01_800431C4(0xF7, D_ovl14_01_8004D5EC);
    j = 4;
    for (i = 0; i < 90; i++) {
        if ((D_ovl14_01_8004D548 == 0) || (func_ovl14_01_8004CC70(0x41B) != 0) || (func_ovl14_01_8004CC70(0x41A) != 0)) {
            func_ovl14_01_8004C9F8();
        }
        if (++j >= 5) {
            func_ovl14_01_8004C9E8(func_ovl14_01_800455AC, obj, 0, 0, 0x150);
            j = 0;
        }
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004C9E8(func_ovl14_01_80045D7C, obj, 0, 0, 0x150);
    func_ovl14_01_8004C9E8(func_ovl14_01_800457F0, obj, 0, 0, 0x110);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_8004515C(void) {
    f32 sp78;
    f32 temp_fs5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fv0;
    f32 var_fv0_2;
    s32 var_s0;
    s32 var_s1;

    D_ovl14_01_8004D6C0 = 9;
    func_ovl14_01_80043250(0);
    func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
    func_ovl14_01_8004CC60(0x419);
    func_ovl14_01_8004CC60(0x414);
    temp_fs5 = D_ovl14_01_8004D6A0.y;
    D_ovl14_01_8004D550 = 0;
    D_ovl14_01_8004D54C = 0;
    D_ovl14_01_8004D548 = 0;
    D_ovl14_01_8004D554 = 0;
    var_s0 = 0x78;
    var_fs1 = 0.0f;
    var_fs2 = 0.0f;
    sp78 = D_ovl14_01_8004D6A0.x;
    func_ovl14_01_800431C4(0x100, D_ovl14_01_8004D5E8);
    var_s1 = 0;
    do {
        temp_fv0 = D_ovl14_01_8004D688 + 0.01f;
        if (temp_fv0 < 1.0f) {
            D_ovl14_01_8004D688 = temp_fv0;
        } else {
            func_ovl14_01_8004CC68(0x414);
        }
        D_ovl14_01_8004D690.y += -1.6666666f;
        temp_fv1 = var_fs2 + 4.0f;
        D_ovl14_01_8004D6A0.y = (f32) ((func_ovl14_01_8004CB90(var_fs2) * 10.0f) + temp_fs5);
        if (temp_fv1 >= 360.0f) {
            var_fs2 = temp_fv1 - 360.0f;
        } else {
            if (temp_fv1 < 0.0f) {
                var_fv0 = temp_fv1 + 360.0f;
            } else {
                var_fv0 = temp_fv1;
            }
            var_fs2 = var_fv0;
        }
        temp_fv1_2 = var_fs1 + 10.0f;
        var_s0 += 1;
        D_ovl14_01_8004D6A0.x = (func_ovl14_01_8004CB90(var_fs1) * 10.0f) + sp78;
        if (temp_fv1_2 >= 360.0f) {
            var_fs1 = temp_fv1_2 - 360.0f;
        } else {
            if (temp_fv1_2 < 0.0f) {
                var_fv0_2 = temp_fv1_2 + 360.0f;
            } else {
                var_fv0_2 = temp_fv1_2;
            }
            var_fs1 = var_fv0_2;
        }
        if (var_s0 >= 0x79) {
            func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, D_ovl14_01_8004D5F0, 0, 0, 0x150);
            func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, M2C_FIELD(D_ovl14_01_8004D618, void **, 0x10), 0, 0, 0x150);
            func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, D_ovl14_01_8004D600[4], 0, 0, 0x150);
            func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, D_ovl14_01_8004D5E8, 0, 0, 0x150);
            var_s0 = 0;
        }
        func_ovl14_01_8004CA30();
        var_s1 += 1;
    } while (var_s1 != 0x258);
}

void func_ovl14_01_80045124(void *arg0) {
    func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, arg0, 0, 0, 0x150);
}

void func_ovl14_01_80045010(void) {
    s32 temp_t4;
    s32 temp_t5;
    s32 var_v0;
    s32 var_v0_2;

    if ((D_ovl14_01_8004D544 == 0) || (var_v0 = 0, (D_ovl14_01_8004D548 == 0))) {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        if (func_ovl14_01_8004CBA8(1) != 0) {
            D_ovl14_01_8004D6CC = D_ovl14_01_8004D6C8 + 1;
        } else {
            D_ovl14_01_8004D6CC = D_ovl14_01_8004D6C8 - 1;
        }
        if (*D_ovl14_01_8004D4E0 & 2) {
            D_ovl14_01_8004D6CC = D_ovl14_01_8004D6C8 - 1;
        }
        var_v0_2 = D_ovl14_01_8004D6CC;
        temp_t4 = var_v0_2 + 8;
        if (var_v0_2 < 0) {
            D_ovl14_01_8004D6CC = temp_t4;
            var_v0_2 = temp_t4;
        }
        temp_t5 = var_v0_2 - 8;
        if (var_v0_2 >= 8) {
            D_ovl14_01_8004D6CC = temp_t5;
            var_v0_2 = temp_t5;
        }
        func_ovl14_01_80044D50(&D_ovl14_01_8004D6F0[var_v0_2], 8.5f);
        D_ovl14_01_8004D6C8 = D_ovl14_01_8004D6CC;
        func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0x1E);
    }
}

s32 func_ovl14_01_80044FDC(void) {
    if ((D_ovl14_01_8004D544 == 0) || (D_ovl14_01_8004D548 == 0)) {
        return 1;
    }
    return 0;
}

void func_ovl14_01_80044D50(Vec3f *arg0, f32 arg1) {
    Vec3f sp94;
    Vec3f sp88;
    f32 sp80;
    s32 sp78;
    f32 sp74;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fs1;
    f32 var_fs2;

    func_ovl14_01_8004C828(&D_ovl14_01_8004D690, arg0, &sp94);
    sp80 = sp94.z;
    func_ovl14_01_80044B38(arg0, 0x14);
    sp78 = 1;
    func_ovl14_01_8004C9E8(func_ovl14_01_800449C0, &sp78, 0, 0, 0x150);
    var_fs1 = 0.0f;
    var_fs2 = 0.0f;
    sp74 = D_ovl14_01_8004D6A0.x;
    if (sp80 >= 0.0f) {
        do {
            func_ovl14_01_8004C828(&D_ovl14_01_8004D690, arg0, &sp94);
            temp_fv0 = sp94.y - 90.0f;
            if (temp_fv0 >= 360.0f) {
                sp94.y = temp_fv0 - 360.0f;
            } else {
                if (sp94.y < 90.0f) {
                    var_fa0 = temp_fv0 + 360.0f;
                } else {
                    var_fa0 = temp_fv0;
                }
                sp94.y = var_fa0;
            }
            if (arg1 < sp94.z) {
                sp94.z = arg1;
            }
            func_ovl14_01_8004C830(&sp94, &sp88);
            D_ovl14_01_8004D690.x += sp88.x;
            D_ovl14_01_8004D690.z += sp88.z;
            temp_fv1 = var_fs1 + 6.0f;
            D_ovl14_01_8004D6A0.x = (func_ovl14_01_8004CB90(var_fs1) * 20.0f) + sp74;
            if (temp_fv1 >= 360.0f) {
                var_fs1 = temp_fv1 - 360.0f;
            } else {
                if (temp_fv1 < 0.0f) {
                    var_fa0_2 = temp_fv1 + 360.0f;
                } else {
                    var_fa0_2 = temp_fv1;
                }
                var_fs1 = var_fa0_2;
            }
            func_ovl14_01_8004CA30();
            var_fs2 += arg1;
        } while (var_fs2 <= sp80);
    }
    sp78 = 0;
    D_ovl14_01_8004D690.x = arg0->x;
    D_ovl14_01_8004D690.z = arg0->z;
    do {
        func_ovl14_01_8004CA30();
    } while (sp78 != -1);
}

void func_ovl14_01_80044B38(Vec3f *arg0, s32 arg1) {
    Vec3f sp5C_v;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fs1;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    s32 var_s0;

    if (D_ovl14_01_8004D6A0.x >= 360.0f) {
        D_ovl14_01_8004D6A0.x -= 360.0f;
    } else {
        if (D_ovl14_01_8004D6A0.x < 0.0f) {
            var_fv1 = D_ovl14_01_8004D6A0.x + 360.0f;
        } else {
            var_fv1 = D_ovl14_01_8004D6A0.x;
        }
        D_ovl14_01_8004D6A0.x = var_fv1;
    }
    sp5C_v.z = 0.0f;
    sp5C_v.y = 0.0f;
    sp5C_v.x = 0.0f;
    func_ovl14_01_8004C828(&D_ovl14_01_8004D690, arg0, &sp5C_v);
    if (sp5C_v.x >= 0.0f) {
        var_fa1 = 180.0f;
        if (sp5C_v.x <= 180.0f) {
            var_fa0 = sp5C_v.x;
        } else {
            goto block_10;
        }
    } else {
block_10:
        var_fa1 = 180.0f;
        var_fa0 = (360.0f - sp5C_v.x) * -1.0f;
    }
    if ((D_ovl14_01_8004D6A0.x >= 0.0f) && (D_ovl14_01_8004D6A0.x <= var_fa1)) {
        var_fv1_2 = D_ovl14_01_8004D6A0.x;
    } else {
        var_fv1_2 = (360.0f - D_ovl14_01_8004D6A0.x) * -1.0f;
    }
    temp_fv0 = var_fa0 - var_fv1_2;
    var_fs1 = temp_fv0;
    if (var_fa1 <= temp_fv0) {
        var_fs1 = temp_fv0 - 360.0f;
    }
    var_s0 = 0;
    if (var_fs1 < -180.0f) {
        var_fs1 += 360.0f;
    }
    if (arg1 > 0) {
        do {
            D_ovl14_01_8004D6A0.x += var_fs1 / (f32) arg1;
            if (D_ovl14_01_8004D6A0.x >= 360.0f) {
                D_ovl14_01_8004D6A0.x -= 360.0f;
            } else {
                if (D_ovl14_01_8004D6A0.x < 0.0f) {
                    var_fv1_3 = D_ovl14_01_8004D6A0.x + 360.0f;
                } else {
                    var_fv1_3 = D_ovl14_01_8004D6A0.x;
                }
                D_ovl14_01_8004D6A0.x = var_fv1_3;
            }
            func_ovl14_01_8004CA30();
            var_s0 += 1;
        } while (var_s0 != arg1);
    }
}

void func_ovl14_01_800449C0(void) {
    f32 temp_fs3;
    f32 temp_fv1;
    f32 var_fs0;
    f32 var_fv0;
    s32 *temp_s1;

    var_fs0 = 0.0f;
    temp_fs3 = D_ovl14_01_8004D690.y;
    temp_s1 = func_ovl14_01_8004CA10();
    func_ovl14_01_800431C4(0xFB, D_ovl14_01_8004D5E8);
loop_1:
    temp_fv1 = var_fs0 + 6.0f;
    D_ovl14_01_8004D690.y = (func_ovl14_01_8004CB90(var_fs0) * 50.0f) + temp_fs3;
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
    if (!(var_fs0 > 180.0f)) {
block_9:
        func_ovl14_01_8004CA30();
        goto loop_1;
    }
    func_ovl14_01_800431C4(0xFB, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D690.y = temp_fs3;
    var_fs0 -= 180.0f;
    if (*temp_s1 != 0) {
        goto block_9;
    }
    *temp_s1 = -1;
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800445D8(void) {
    Vec3f sp3C;
    f32 sp34;
    f32 sp30;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    f32 var_fv1_4;
    s32 var_v0;

    if (func_ovl14_01_8004CC70(0x413) != 0) {
        if (func_ovl14_01_8004CC70(0x415) != 0) {
            if (D_ovl14_01_8004D4F8.x >= 360.0f) {
                D_ovl14_01_8004D4F8.x = (f32) (D_ovl14_01_8004D4F8.x - 360.0f);
            } else {
                if (D_ovl14_01_8004D4F8.x < 0.0f) {
                    var_fv1 = D_ovl14_01_8004D4F8.x + 360.0f;
                } else {
                    var_fv1 = D_ovl14_01_8004D4F8.x;
                }
                D_ovl14_01_8004D4F8.x = var_fv1;
            }
            if (D_ovl14_01_8004D4F8.y >= 360.0f) {
                D_ovl14_01_8004D4F8.y = (f32) (D_ovl14_01_8004D4F8.y - 360.0f);
            } else {
                if (D_ovl14_01_8004D4F8.y < 0.0f) {
                    var_fv1_2 = D_ovl14_01_8004D4F8.y + 360.0f;
                } else {
                    var_fv1_2 = D_ovl14_01_8004D4F8.y;
                }
                D_ovl14_01_8004D4F8.y = var_fv1_2;
            }
            func_ovl14_01_8004C828(&D_ovl14_01_8004D690, &D_ovl14_01_8004D518, &sp3C);
            temp_fv0 = sp3C.y - 90.0f;
            if (temp_fv0 >= 360.0f) {
                sp3C.y = temp_fv0 - 360.0f;
            } else {
                if (sp3C.y < 90.0f) {
                    var_fv1_3 = temp_fv0 + 360.0f;
                } else {
                    var_fv1_3 = temp_fv0;
                }
                sp3C.y = var_fv1_3;
            }
            func_ovl14_01_8004C700(&sp34, NULL, &sp30);
            if (sp3C.x >= 0.0f) {
                if (sp3C.x <= 180.0f) {
                    var_ft4 = sp3C.x;
                } else {
                    goto block_24;
                }
            } else {
block_24:
                var_ft4 = (360.0f - sp3C.x) * -1.0f;
            }
            if (sp34 >= 0.0f) {
                if (sp34 <= 180.0f) {
                    var_fv1_4 = sp34;
                } else {
                    goto block_29;
                }
            } else {
block_29:
                var_fv1_4 = (360.0f - sp34) * -1.0f;
            }
            temp_fa0 = var_ft4 - var_fv1_4;
            var_fv0 = temp_fa0;
            var_v0 = 0;
            if (temp_fa0 > 180.0f) {
                var_fv0 = temp_fa0 - 360.0f;
            }
            if (var_fv0 < -180.0f) {
                var_fv0 += 360.0f;
            }
            if ((f64) var_fv0 < 0.0) {
                var_v0 = 1;
                var_fv0 *= -1.0f;
            }
            if (var_fv0 > 5.0f) {
                var_fv0 = 5.0f;
            }
            if (var_v0 != 0) {
                var_fv0 *= -1.0f;
            }
            D_ovl14_01_8004D4F8.x = (f32) (sp34 + var_fv0);
            switch (D_ovl14_01_8004D6C0) {
            case 2:
            case 4:
                if (D_ovl14_01_8004D4F8.y > 8.0f) {
                    D_ovl14_01_8004D4F8.y = (f32) (D_ovl14_01_8004D4F8.y - 1.0f);
                }
                break;
            case 1:
                if (D_ovl14_01_8004D4F8.y < 50.0f) {
                    D_ovl14_01_8004D4F8.y = (f32) (D_ovl14_01_8004D4F8.y + 1.0f);
                }
                break;
            default:
            case 3:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                if ((D_ovl14_01_8004D4F8.y < 24.0f) || (D_ovl14_01_8004D4F8.y > 26.0f)) {
                    if (D_ovl14_01_8004D4F8.y > 25.0f) {
                        D_ovl14_01_8004D4F8.y = (f32) (D_ovl14_01_8004D4F8.y - 1.0f);
                    } else {
                        D_ovl14_01_8004D4F8.y = (f32) (D_ovl14_01_8004D4F8.y + 1.0f);
                    }
                }
                break;
            }
            func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
            func_ovl14_01_8004C6F8(D_ovl14_01_8004D4F8.x, 32768.0f, D_ovl14_01_8004D4F8.z);
        }
    }
}

void func_ovl14_01_80044540(Vec3f *arg0) {
    Vec3f sp1C;

    arg0->y = 0.0f;
    arg0->z *= 0.75f;
    func_ovl14_01_8004C830(arg0, &sp1C);
    func_ovl14_01_8004C788(D_ovl14_01_8004D690.x + sp1C.x, D_ovl14_01_8004D690.z + sp1C.z, 100.0f, 110.0f);
    func_ovl14_01_8004C798(D_ovl14_01_8004D690.x + sp1C.x, D_ovl14_01_8004D690.z + sp1C.z, D_ovl14_01_8004D690.x + sp1C.x, D_ovl14_01_8004D690.z + sp1C.z);
}

void func_ovl14_01_80044104(void) {
    s32 i;

    if (func_ovl14_01_8004CC70(0x414) != 0) {
        D_ovl14_01_8004D644 = func_ovl14_01_8004D000(D_ovl14_01_8004D5DC->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
        D_ovl14_01_8004D64C = func_ovl14_01_8004D000(D_ovl14_01_8004D5F0->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
        D_ovl14_01_8004D648 = func_ovl14_01_8004D000(D_ovl14_01_8004D5E8->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
        for (i = 0; i < 5; i++) {
            if (D_ovl14_01_8004D600[i]->unk28 != -1) {
                D_ovl14_01_8004D658[i] = func_ovl14_01_8004D000(D_ovl14_01_8004D600[i]->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
            }
        }
        for (i = 0; i < 5; i++) {
            if (D_ovl14_01_8004D618[i]->unk28 != -1) {
                D_ovl14_01_8004D670[i] = func_ovl14_01_8004D000(D_ovl14_01_8004D618[i]->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
            }
        }
        D_ovl14_01_8004D650 = func_ovl14_01_8004D000(D_ovl14_01_8004D5EC->unk40, D_ovl14_01_8004D638, D_ovl14_01_8004D63C, D_ovl14_01_8004D640, D_ovl14_01_8004D688);
    }
}

void func_ovl14_01_80043F10(void) {
    Vec3f sp70;
    UnkStructA *temp_s1;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fs3;
    s32 var_s0;
    void *temp_s0;

    D_ovl14_01_8004D540 += 1;
    temp_s0 = func_ovl14_01_8004CA10();
    temp_s1 = func_ovl14_01_8004C8C0(0x1CC, 0x11280000, 0xD0, D_ovl14_01_8004D5E8);
    func_ovl14_01_8004C828((Vec3f *) &D_ovl14_01_8004D5E8->unk58, &D_ovl14_01_8004D690, &sp70);
    var_fs0 = 0.0f;
    var_fs1 = 500.0f;
    var_fs2 = 0.1f;
    var_fs3 = 0.2f;
    if (temp_s0 == NULL) {
        var_fs2 = 0.1f * -1.0f;
        var_fs3 = 0.2f * -1.0f;
    }
    var_s0 = 0;
    do {
        temp_s1->unk4C = func_ovl14_01_8004CB90(sp70.x + var_fs0) * var_fs1;
        temp_s1->unk50 = func_ovl14_01_8004BEC0() - D_ovl14_01_8004D5E8->unk40->unk14;
        temp_s1->unk54 = func_ovl14_01_8004CB98(sp70.x + var_fs0) * var_fs1;
        var_fs0 += var_fs2;
        var_fs2 += var_fs3;
        var_fs1 -= 4.0f;
        func_ovl14_01_80043CC0(temp_s1, var_s0, 0x1E, 1.0f, 1.75f);
        func_ovl14_01_8004CA30();
        var_s0 += 1;
    } while (var_s0 != 0x28);
    D_ovl14_01_8004D540 -= 1;
    func_ovl14_01_8004C8B0(temp_s1);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80043D98(void) {
    Vec3f sp54;
    Vec3f sp48_v;
    UnkStructA *temp_s1;
    f32 temp_fs0;
    f32 temp_ft3;
    s32 var_s0;

    D_ovl14_01_8004D540 += 1;
    temp_s1 = func_ovl14_01_8004C8C0(0x1CC, 0x11080000, 0xD0, NULL);
    temp_ft3 = (f32) func_ovl14_01_8004CBA8(0x23) * 10.0f;
    sp48_v.y = 0.0f;
    sp48_v.x = temp_ft3;
    sp48_v.z = 500.0f;
    temp_fs0 = func_ovl14_01_8004BEC0();
    func_ovl14_01_8004C830(&sp48_v, &sp54);
    temp_s1->unk40->unk10 = D_ovl14_01_8004D5E8->unk40->unk10 + sp54.x;
    temp_s1->unk40->unk14 = sp54.y + temp_fs0;
    var_s0 = 0;
    temp_s1->unk40->unk18 = D_ovl14_01_8004D5E8->unk40->unk18 + sp54.z;
    do {
        func_ovl14_01_80043CC0(temp_s1, var_s0, 0x1E, 1.0f, 1.75f);
        func_ovl14_01_8004CA30();
        var_s0 += 1;
    } while (var_s0 != 0x28);
    D_ovl14_01_8004D540 -= 1;
    func_ovl14_01_8004C8B0(temp_s1);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80043CC0(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    f32 t;
    f32 u;

    t = (f32) arg1 / (f32) arg2;
    u = t;
    arg0->unk40->unk28 = func_ovl14_01_8004CB90(t * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl14_01_8004CB90(u * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - u) * 193.0f) + 0x40;
}

void func_ovl14_01_80043B20(void) {
    UnkStructA_40 *temp_v1;
    s32 var_s0;
    void *var_s1;

    var_s1 = NULL;
    var_s0 = 0x8000;
loop_1:
    var_s0 += 1;
    if (D_ovl14_01_8004D540 < 0xC) {
        temp_v1 = D_ovl14_01_8004D5E8->unk40;
        if (((D_ovl14_01_8004D5E8->unk58 != temp_v1->unk10) || (D_ovl14_01_8004D5E8->unk60 != temp_v1->unk18)) && (func_ovl14_01_8004BEC0() < (D_ovl14_01_8004D690.y + 1100.0f))) {
            if (var_s0 >= 7) {
                func_ovl14_01_8004C9E8(func_ovl14_01_80043F10, var_s1, 0, 0, 0x150);
                var_s1 = (void *) ((s32) var_s1 ^ 1);
                goto block_10;
            }
        } else if ((D_ovl14_01_8004D5E8->unk5C != D_ovl14_01_8004D5E8->unk40->unk14) && (var_s0 >= 5)) {
            func_ovl14_01_8004C9E8(func_ovl14_01_80043D98, NULL, 0, 0, 0x150);
block_10:
            var_s0 = 0;
        }
    }
    func_ovl14_01_8004CA30();
    goto loop_1;
}

void func_ovl14_01_800439AC(Vec3f *arg0, UnkStructA *arg1) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    f32 temp_fv0;

    if (D_ovl14_01_8004D53C < 0x11) {
        temp_v0 = func_ovl14_01_8004C8C0(0x1CF, 0x01000000, 0xD0, arg1);
        if (arg1 == NULL) {
            temp_v0->unk40->unk10 = arg0->x;
            temp_v0->unk40->unk14 = arg0->y;
            temp_v0->unk40->unk18 = arg0->z;
        } else {
            func_ovl14_01_8004C898(temp_v0, 0x200000);
            temp_v0->unk4C = arg0->x;
            temp_v0->unk50 = arg0->y;
            temp_v0->unk54 = arg0->z;
        }
        temp_v0->unk40->unk36 = 0xFF;
        temp_v0->unk40->unk30 = 2.0f;
        temp_v0_2 = temp_v0->unk40;
        temp_fv0 = temp_v0_2->unk30;
        temp_v0_2->unk2C = temp_fv0;
        temp_v0->unk40->unk28 = temp_fv0;
        func_ovl14_01_8004C5A0(temp_v0->unk40, 2);
        func_ovl14_01_8004C5A8(temp_v0->unk40, 0x1D0, 0, 0);
        func_ovl14_01_8004C5A8(temp_v0->unk40, 0x1D0, 1, 1);
        func_ovl14_01_8004C9E8(func_ovl14_01_800438D8, temp_v0, 0, 0, 0x150);
        D_ovl14_01_8004D53C += 1;
    }
}

void func_ovl14_01_800438D8(void) {
    UnkStructA *temp_s2;
    f32 var_fs0;
    s32 var_s0;

    var_fs0 = 0.0f;
    temp_s2 = func_ovl14_01_8004CA10();
    var_s0 = 0;
    do {
        func_ovl14_01_8004C5A8(temp_s2->unk40, 0x1D0, 0, (s32) var_fs0 * 2);
        var_fs0 += 0.25f;
        func_ovl14_01_8004CA30();
        var_s0 += 1;
    } while (var_s0 != 0x10);
    func_ovl14_01_8004C8B0(temp_s2);
    D_ovl14_01_8004D53C -= 1;
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800437B8(void) {
    UnkStructA *temp_s0;

    if (func_ovl14_01_8004CC70(0x400) == 0) {
        func_ovl14_01_8004CCE8(0, 0, 0, 100.0f);
        D_ovl14_01_8004D688 = 1.0f;
        func_ovl14_01_80043688(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        func_ovl14_01_80043688(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
        func_ovl14_01_80043250(0);
        temp_s0 = D_ovl14_01_8004D5DC;
        temp_s0->unk40->unk48->unk4->unk4 = func_ovl14_01_8004C5D8(temp_s0->unk40, 0) - 0.001f;
        func_ovl14_01_8004CC60(0x414);
        D_ovl14_01_8004D4F8.y = 8.0f;
        func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
        func_ovl14_01_8004C6F8(0.0f, D_ovl14_01_8004D4F8.y, 2500.0f);
        D_ovl14_01_8004D4F8.y = -10.0f;
        func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
        func_ovl14_01_8004C6F8(0.0f, D_ovl14_01_8004D4F8.y, 1300.0f);
    }
}

static void func_ovl14_01_80043680() {
}

void func_ovl14_01_80043688(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    Link_ovl14_01 *temp_a2;

    func_ovl14_01_80043680();
    arg1->unk0 = 1;
    M2C_FIELD(arg1, s32 *, 0x14) = 1;
    temp_a2 = arg1 + 0x28;
    arg1->unk10 = 0.9f;
    M2C_FIELD(arg1, f32 *, 0x24) = 0.9f;
    arg1->unkC = 0.1f;
    M2C_FIELD(arg1, f32 *, 0x20) = 0.1f;
    arg1->unk8 = 0.5f;
    M2C_FIELD(arg1, f32 *, 0x1C) = 0.5f;
    arg1->unk4 = 250.0f;
    M2C_FIELD(arg1, f32 *, 0x18) = 60.0f;
    M2C_FIELD(arg1, s32 *, 0x28) = 1;
    temp_a2->unk10 = 0.9f;
    temp_a2->unkC = 0.1f;
    temp_a2->unk8 = 0.5f;
    temp_a2->unk4 = 420.0f;
    func_ovl14_01_8004C8A0(arg0[1], 0xF00000);
    func_ovl14_01_8004C898(arg0[1], 0x500000);
    arg0[1]->unk50 = -90.0f;
    arg0[1]->unk54 = 60.0f;
    func_ovl14_01_8004C8A0(arg0[3], 0xF00000);
    func_ovl14_01_8004C898(arg0[3], 0x500000);
    arg0[3]->unk50 = -90.0f;
    arg0[3]->unk4C = 0.0f;
    func_ovl14_01_8004C8A0(arg0[4], 0xF00C30);
    arg0[4]->unk40->unk1C = 90.0f;
}

void func_ovl14_01_80043624(void) {
    if (!(*D_ovl14_01_8004D4E0 & 2)) {
        if (func_ovl14_01_8004CC50(0xA4) == 0) {
            func_ovl14_01_8004CA08(0x28);
        }
        func_ovl14_01_8004CF80(0x2A);
    }
    func_ovl14_01_8004C9F8();
}

s32 func_ovl14_01_800431C4(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *temp_v0;

    temp_v0 = arg1->unk40;
    return func_ovl14_01_8004CF90(arg0, temp_v0->unk10, temp_v0->unk14, temp_v0->unk18);
}

void func_ovl14_01_80043250(s32 arg0) {
    func_ovl14_01_8004C5C0(D_ovl14_01_8004D5DC->unk40, arg0, 0);
    D_ovl14_01_8004D558 = (s32) (func_ovl14_01_8004C5D8(D_ovl14_01_8004D5DC->unk40, 0) - 0.001f);
    func_ovl14_01_8004C8A0(D_ovl14_01_8004D5DC, 0x04000000);
}

void func_ovl14_01_800432D8(void) {
    f32 sp68;
    Vec3f sp50_v;
    f32 sp48;
    f32 sp44;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fs0;
    f32 var_fs1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s2;

    if (func_ovl14_01_8004CC70(0x400) == 0) {
        func_ovl14_01_8004C9E8(func_ovl14_01_80043624, NULL, 0, 0, 0x150);
        var_s0 = 0;
        do {
            func_ovl14_01_8004CA30();
            func_ovl14_01_8004CCE8(0, 0, 0, 100.0f * (1.0f - ((f32) var_s0 / 120.0f)));
            var_s0 += 1;
        } while (var_s0 < 0x78);
        func_ovl14_01_8004CCE8(0, 0, 0, 0.0f);
        func_ovl14_01_800431C4(0x10D, D_ovl14_01_8004D5DC);
        func_ovl14_01_80043250(1);
        func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
        func_ovl14_01_800431F8(D_ovl14_01_8004D5DC);
        func_ovl14_01_800431C4(0x10E, D_ovl14_01_8004D5F0);
        var_s0_2 = 0;
        do {
            D_ovl14_01_8004D688 = 1.0f - ((f32) var_s0_2 / 60.0f);
            func_ovl14_01_8004CA30();
            var_s0_2 += 1;
        } while (var_s0_2 < 0x3C);
        func_ovl14_01_80043010(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        func_ovl14_01_80043010(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
        func_ovl14_01_8004CA08(0x3C);
        func_ovl14_01_8004C7F0((f32 *)&sp50_v);
        if (sp50_v.y >= 0.0f) {
            if (sp50_v.y <= 180.0f) {
                var_fa0 = sp50_v.y;
            } else {
                goto block_9;
            }
        } else {
block_9:
            var_fa0 = (360.0f - sp50_v.y) * -1.0f;
        }
        var_fs1 = (2500.0f - sp50_v.z) / 30.0f;
        var_fs0 = (25.0f - var_fa0) / 30.0f;
        sp48 = var_fs0;
        sp68 = (var_fs1 / 60.0f) * -1.0f;
        func_ovl14_01_8004CD40(1);
        var_s2 = 0xBF;
        func_ovl14_01_8004CD48(0xBF);
        var_s0_3 = 0;
        sp44 = (sp48 / 60.0f) * -1.0f;
        do {
            D_ovl14_01_8004D4F8.y = (f32) (D_ovl14_01_8004D4F8.y + var_fs0);
            func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
            temp_fv0 = sp50_v.z + var_fs1;
            temp_fa1 = sp50_v.y + var_fs0;
            sp50_v.y = temp_fa1;
            sp50_v.z = temp_fv0;
            var_fs0 += sp44;
            var_fs1 += sp68;
            func_ovl14_01_8004C6F8(32768.0f, temp_fa1, temp_fv0);
            func_ovl14_01_8004C790(temp_fa1, temp_fa1);
            D_ovl14_01_8004D4F8.y = sp50_v.y;
            func_ovl14_01_8004CA30();
            var_s0_3 += 1;
        } while (var_s0_3 != 0x3C);
        do {
            func_ovl14_01_8004CD48(var_s2);
            func_ovl14_01_8004CA30();
            var_s2 -= 8;
        } while (var_s2 >= 0);
        func_ovl14_01_8004CD40(0);
        if (func_ovl14_01_8004CC50(0xA4) != 0) {
            func_ovl14_01_8004CA08(0x5A);
        }
        func_ovl14_01_8004CC68(0x414);
    }
}


static void func_ovl14_01_800431F8(UnkStructA *obj) {
    while (!(obj->unk40->unkC & 0x40)) {
        func_ovl14_01_8004CA30();
    }
}


void func_ovl14_01_80043010(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    UnkStructA **temp_s0;
    UnkStructA **temp_s0_2;

    if (arg1 == D_ovl14_01_8004D560) {
        if (D_ovl14_01_8004D54C == 0) {

        } else {
            goto block_4;
        }
    } else if (D_ovl14_01_8004D550 != 0) {
block_4:
        arg1->unk0 = 2;
        arg1->unk10 = 0.0f;
        M2C_FIELD(arg1, s32 *, 0x14) = 2;
        M2C_FIELD(arg1, s32 *, 0x28) = 0x10002;
        arg1->unk8 = 0.0f;
        M2C_FIELD(arg1, f32 *, 0x24) = 0.0f;
        M2C_FIELD(arg1, f32 *, 0x20) = 0.0f;
        M2C_FIELD(arg1, f32 *, 0x1C) = 0.0f;
        arg1->unkC = 0.1f;
        arg1->unk4 = 250.0f;
        M2C_FIELD(arg1, f32 *, 0x18) = 60.0f;
        M2C_FIELD(arg1, f32 *, 0x38) = 0.9f;
        M2C_FIELD(arg1, f32 *, 0x34) = 0.3f;
        M2C_FIELD(arg1, f32 *, 0x30) = 0.01f;
        M2C_FIELD(arg1, f32 *, 0x2C) = 420.0f;
        temp_s0 = arg0 + 4;
        func_ovl14_01_8004C8A0(arg0[1], 0x300000);
        func_ovl14_01_8004C898(arg0[1], 0x500000);
        arg0[1]->unk50 = -85.0f;
        temp_s0_2 = temp_s0 + 8;
        arg0[1]->unk4C = 0.0f;
        func_ovl14_01_8004C898(M2C_FIELD(temp_s0, UnkStructA **, 8), 0x500000);
        M2C_FIELD(temp_s0, UnkStructA **, 8)->unk50 = 0.0f;
        M2C_FIELD(M2C_FIELD((temp_s0_2 + 4), void **, -4), f32 *, 0x4C) = 0.0f;
        func_ovl14_01_8004C8A0(M2C_FIELD(temp_s0_2, UnkStructA **, 4), 0xC30);
        M2C_FIELD(temp_s0_2, UnkStructA **, 4)->unk40->unk28 = 1.0f;
        M2C_FIELD(temp_s0_2, UnkStructA **, 4)->unk40->unk2C = 1.0f;
        M2C_FIELD(temp_s0_2, UnkStructA **, 4)->unk40->unk30 = 1.0f;
        M2C_FIELD(temp_s0_2, UnkStructA **, 4)->unk40->unk1C = 90.0f;
        func_ovl14_01_8004C898(M2C_FIELD(temp_s0_2, UnkStructA **, 4), 0x10);
    }
}

