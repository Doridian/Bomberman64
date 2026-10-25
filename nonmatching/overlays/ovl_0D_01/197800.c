/*
 * NON_MATCHING: ovl_0D_01's stage object, complete: all 47 functions and the
 * stubs the inlined statics leave in their places (every function and stub
 * at the original's address up to 80043134's group; the later ones within a
 * few words), .data 0x3E0 and .bss 0x70 as the original.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 1089
 *
 * The sibling of ovl_0D_04 and ovl_0D_06 (nonmatching/overlays): the gate
 * code (800444E0, 800448D4), the model tables, the setup's loops and the
 * camera statics are theirs, renamed (scratch/0D_03/xlate.py). The layout
 * rules that placed every stub: a global the setup (or 80044F00, 800439CC)
 * calls comes out between its statics only when defined above it, so
 * 8004553C, 800454F8, 800455B8, 80044E2C, 80044EC4 and 800438C0 sit above
 * their callers; 80044D74 stays a call from the handler only with its two
 * stubs as empty statics called before each block (as statics holding the
 * blocks it was inlined, +27 words in the handler). What still differs in
 * us (fcmp counts a static with the function before it):
 * - func_ovl0D_01_80043134 (310): 2 words short; register allocation of the
 *   two probes and the fade loop (the loop's 1900.0 is hoisted into $fs2 in
 *   the original).
 * - func_ovl0D_01_800455E0 (253, the 7 loop statics with it): 4 words long.
 * - func_ovl0D_01_800448D4 (198, its 3 statics with it): 21 words short;
 *   the original indexes the gates at run time (i*8-i)*8 and steps the flags
 *   with a pointer; ours strength-reduces both.
 * - func_ovl0D_01_80044154 (134): 1 word long.
 * - func_ovl0D_01_80044F00 (92, the 5 loop statics with it): 2 words long.
 * - func_ovl0D_01_80044428 (67, 80044464 to 800444E0 with it), 8004363C
 *   (16, 800434BC with it; 800436C8 is 1 word short), 80043744 (9: 2 words
 *   long), 800439CC (4), 80043D3C (4), 80045A00 (2): register allocation.
 */
#include "common.h"

/*
 * ovl_0D_01's stage object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).
 * ovl_0D_04 and ovl_0D_06 (nonmatching/overlays) are its siblings.
 */

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} Anim2_0D01;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ Anim2_0D01 *unk4;
} Anim_0D01;

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
    /* 0x48 */ Anim_0D01 *unk48;
} Obj40_0D01;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18[0x10];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ Obj40_0D01 *unk40;
} Obj_0D01;

/* a model placed on the stage (as in ovl_0D_04 and ovl_0D_06) */
typedef struct {
    /* 0x00 */ Obj_0D01 *obj;
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
} Ent_0D01;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Trio_0D01;

typedef struct {
    f32 x, y, z, w;
} Vec4f_0D01;

/* passed to func_ovl0D_01_80046AE0 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18[5];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s32 unk30[5];
} Move_0D01;

/* what ZeroJump 0x3106 returns (as in ovl_0A_05) */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ UnkStructA_40 *unkC;
} Rec_0D01;

void func_ovl0D_01_80046268(s32); /* 0xC00 */
void func_ovl0D_01_80046278(s32 *); /* 0xC02 */
void func_ovl0D_01_800462A8(s32, s32, s32, s32, s32, s32); /* 0xD05 */
void func_ovl0D_01_800462B0(s32, s32, s32, s32, s32, s32, s32); /* 0xD06 */
void func_ovl0D_01_800462C0(f32, f32, f32, s32 *, s32); /* 0xD08 */
s32 func_ovl0D_01_800462D0(s32); /* 0xD0A */
void func_ovl0D_01_800462E0(s32); /* 0xD0C */
void func_ovl0D_01_800462E8(void); /* 0xD0D */
void func_ovl0D_01_80046330(s32); /* 0xD16 */
s32 func_ovl0D_01_80046338(s32); /* 0xE00 */
void func_ovl0D_01_80046340(s32, s32, s32, s32, s32, s32, s32, s32); /* 0xE01 */
void func_ovl0D_01_80046350(void (*)(Obj_0D01 *)); /* 0xE03 */
void func_ovl0D_01_80046360(s32, s32, s32); /* 0xF00 */
s32 func_ovl0D_01_80046368(void); /* 0xF01 */
void func_ovl0D_01_80046388(void); /* 0xF05 */
void func_ovl0D_01_800463B0(s32); /* 0xF0A */
s32 *func_ovl0D_01_800463B8(void); /* 0xF0B */
void func_ovl0D_01_800463D0(s32); /* 0xF0E */
void func_ovl0D_01_800463D8(s32); /* 0xF0F */
void func_ovl0D_01_800463F0(s32, s32); /* 0xF12 */
void func_ovl0D_01_80046418(void); /* 0x1000 */
void func_ovl0D_01_80046420(s32, s32, s32); /* 0x1001 */
void func_ovl0D_01_80046428(void *); /* 0x1002 */
s32 func_ovl0D_01_80046430(s32, s32, s32, s32); /* 0x1003 */
s32 func_ovl0D_01_80046438(s32, s32, s32, s32, s32); /* 0x1004 */
s32 func_ovl0D_01_80046448(void); /* 0x1006 */
void func_ovl0D_01_80046450(s32, void *); /* 0x1007 */
void func_ovl0D_01_80046458(s32); /* 0x1008 */
void func_ovl0D_01_80046460(s32); /* 0x1009 */
void func_ovl0D_01_80046468(s32, s32, f32, s32, s32, s32, s32); /* 0x100A */
void func_ovl0D_01_80046470(const char *); /* 0x100B */
void func_ovl0D_01_80046478(void); /* 0x100C */
void func_ovl0D_01_80046480(s32); /* 0x100D */
void func_ovl0D_01_80046490(s32); /* 0x100F */
void func_ovl0D_01_80046518(void); /* 0x1020 */
void func_ovl0D_01_80046950(UnkStructA_40 *); /* 0x1501 */
void func_ovl0D_01_80046990(Obj40_0D01 *, s32, s32); /* 0x1509 */
f32 func_ovl0D_01_800469A8(Obj40_0D01 *, s32); /* 0x150C */
s32 func_ovl0D_01_800469B0(Obj40_0D01 *, s32, s32, s32, s32, s32); /* 0x150D */
void func_ovl0D_01_800469B8(s32); /* 0x150E */
void func_ovl0D_01_800469D0(s32, s32); /* 0x1511 */
void func_ovl0D_01_80046AA8(f32, f32, f32); /* 0x1704 */
void func_ovl0D_01_80046AC8(f32, f32, f32); /* 0x1708 */
void func_ovl0D_01_80046AD0(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0D_01_80046AE0(Move_0D01 *, s32, s32); /* 0x170B */
s32 func_ovl0D_01_80046AF8(void); /* 0x170E */
void func_ovl0D_01_80046B00(void); /* 0x170F */
void func_ovl0D_01_80046B08(s32); /* 0x1710 */
void func_ovl0D_01_80046B10(s32); /* 0x1711 */
void func_ovl0D_01_80046B20(s32); /* 0x1713 */
void func_ovl0D_01_80046B48(f32 *); /* 0x1718 */
void func_ovl0D_01_80046B58(f32, f32, f32, f32); /* 0x171A */
void func_ovl0D_01_80046B60(f32, f32); /* 0x171B */
void func_ovl0D_01_80046B68(f32, f32, f32, f32); /* 0x171C */
void func_ovl0D_01_80046B80(s32); /* 0x171F */
void func_ovl0D_01_80046B90(f32, f32, f32); /* 0x1721 */
void func_ovl0D_01_80046B98(void *); /* 0x1722 */
void func_ovl0D_01_80046BC8(void); /* 0x1728 */
void func_ovl0D_01_80046BD0(void); /* 0x1729 */
void func_ovl0D_01_80046C00(f32 *, f32 *); /* 0x1804 */
s32 func_ovl0D_01_80046C18(Obj_0D01 *, s32); /* 0x1807 */
s32 func_ovl0D_01_80046C20(Obj_0D01 *, s32); /* 0x1808 */
void func_ovl0D_01_80046C68(Obj_0D01 *, s32); /* 0x1811 */
void func_ovl0D_01_80046C70(Obj_0D01 *, s32); /* 0x1812 */
void func_ovl0D_01_80046C80(Obj_0D01 *); /* 0x1814 */
Obj_0D01 *func_ovl0D_01_80046C90(s32, s32, s32, s32); /* 0x1816 */
void func_ovl0D_01_80046CA0(Obj_0D01 *); /* 0x1818 */
Obj_0D01 *func_ovl0D_01_80046CB0(s32, s32, f32, f32, f32); /* 0x181A */
void func_ovl0D_01_80046DB8(void (*)(void), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0D_01_80046DC8(void); /* 0x1902 */
void func_ovl0D_01_80046DD8(s32); /* 0x1904 */
void *func_ovl0D_01_80046DE0(void); /* 0x1905 */
void func_ovl0D_01_80046E00(void); /* 0x1909 */
f32 func_ovl0D_01_80046F60(f32); /* 0x1D00 */
f64 func_ovl0D_01_80046F70(void); /* 0x1D02 */
s32 func_ovl0D_01_80047020(s32); /* 0x1E04 */
void func_ovl0D_01_80047030(s32); /* 0x1E06 */
s32 func_ovl0D_01_80047040(s32); /* 0x1E08 */
s32 *func_ovl0D_01_80047050(s32); /* 0x1E0A */
void func_ovl0D_01_800470A8(s32); /* 0x2002 */
void func_ovl0D_01_800470B0(void); /* 0x2003 */
void func_ovl0D_01_800470B8(s32, s32, s32, f32); /* 0x2004 */
void func_ovl0D_01_800470E0(s32, s32, s32); /* 0x2101 */
void func_ovl0D_01_80047100(s32); /* 0x2200 */
void func_ovl0D_01_80047108(s32, s32, s32); /* 0x2201 */
void func_ovl0D_01_80047120(u32 (*)[3]); /* 0x2300 */
void func_ovl0D_01_80047138(u32 (*)[3]); /* 0x2303 */
s32 func_ovl0D_01_80047210(s32, f32 *, s32); /* 0x2601 */
void func_ovl0D_01_80047218(s32); /* 0x2602 */
void func_ovl0D_01_80047248(void); /* 0x2704 */
void func_ovl0D_01_800472C8(s32, s32, s32); /* 0x2A00 */
void func_ovl0D_01_80047328(void); /* 0x2A0C */
void func_ovl0D_01_80047340(s32); /* 0x2B00 */
void func_ovl0D_01_80047360(s32, f32, f32, f32); /* 0x2B04 */
void func_ovl0D_01_80047370(s32); /* 0x2B06 */
void func_ovl0D_01_800474B8(void); /* 0x3000 */
void func_ovl0D_01_800474C0(void); /* 0x3001 */
void func_ovl0D_01_800474F0(s32); /* 0x3103 */
void func_ovl0D_01_800474F8(void); /* 0x3104 */
s32 func_ovl0D_01_80047500(void); /* 0x3105 */
Rec_0D01 *func_ovl0D_01_80047508(s32); /* 0x3106 */
void func_ovl0D_01_80047518(s32); /* 0x3108 */
void func_ovl0D_01_80047520(void); /* 0x3109 */
void func_ovl0D_01_80047528(void); /* 0x310A */

#define UNK_MACRO_ovl0D_01_800448D4() \
    D_ovl0D_01_80047AEC = func_ovl0D_01_80046448(); func_ovl0D_01_80046428(&D_ovl0D_01_80047AE0); func_ovl0D_01_80046450(D_ovl0D_01_80047AEC, &D_ovl0D_01_80047AD0)

static void func_ovl0D_01_80043EFC(void);
static void func_ovl0D_01_800434BC(Ent_0D01 *);
static void func_ovl0D_01_800436C8(Ent_0D01 *);
static void func_ovl0D_01_800437C8(s32, s32, s32, s32);
static void func_ovl0D_01_80043868(Obj_0D01 *);
static void func_ovl0D_01_80043944(Ent_0D01 *);
static void func_ovl0D_01_80043CF8(Obj_0D01 *);
static void func_ovl0D_01_80044464(s32, s32 *, s32 *);
static s32 func_ovl0D_01_800444D8(f32);
static void func_ovl0D_01_800444E0(Ent_0D01 *);
static void func_ovl0D_01_800448BC(Ent_0D01 *, s32);
static void func_ovl0D_01_800448C4(void);
static void func_ovl0D_01_800448CC(void);
static void func_ovl0D_01_80044D64(void);
static void func_ovl0D_01_80044D6C(void);
static void func_ovl0D_01_80044E04(void);
static void func_ovl0D_01_80044E0C(void);
static void func_ovl0D_01_80044E14(void);
static void func_ovl0D_01_80044E1C(void);
static void func_ovl0D_01_80044E24(void);
static void func_ovl0D_01_80045088(void);
static void func_ovl0D_01_800454F0(void);
static void func_ovl0D_01_80045580(void);
static void func_ovl0D_01_80045588(void);
static void func_ovl0D_01_80045590(void);
static void func_ovl0D_01_80045598(void);
static void func_ovl0D_01_800455A0(void);
static void func_ovl0D_01_800455A8(void);
static void func_ovl0D_01_800455B0(void);
static void func_ovl0D_01_800455D0(Trio_0D01 *, s32);
static void func_ovl0D_01_800455D8(void);
static void func_ovl0D_01_80045F14(void);

void func_ovl0D_01_80043010(void);
void func_ovl0D_01_80043098(void);
void func_ovl0D_01_80043100(s32, Obj_0D01 *);
void func_ovl0D_01_80043134(void);
void func_ovl0D_01_8004363C(void);
void func_ovl0D_01_80043744(void);
void func_ovl0D_01_8004376C(f32, f32, f32);
void func_ovl0D_01_800438C0(void);
void func_ovl0D_01_800439CC(void);
void func_ovl0D_01_80043D3C(void);
void func_ovl0D_01_80043DDC(void);
void func_ovl0D_01_80043E1C(s32, s32);
void func_ovl0D_01_80043E90(void);
void func_ovl0D_01_80043F04(f32, f32, f32, f32, s32);
void func_ovl0D_01_80044038(void);
void func_ovl0D_01_800443BC(void);
void func_ovl0D_01_80044154(void);
void func_ovl0D_01_80044408(void);
void func_ovl0D_01_80044428(void);
void func_ovl0D_01_800448D4(void);
void func_ovl0D_01_80044C0C(void);
void func_ovl0D_01_80044CB0(void);
void func_ovl0D_01_80044D74(void);
void func_ovl0D_01_80044EC4(void);
void func_ovl0D_01_80044E2C(void);
void func_ovl0D_01_80044F00(void);
void func_ovl0D_01_80045090(void);
void func_ovl0D_01_800450C0(void);
void func_ovl0D_01_80045164(void);
void func_ovl0D_01_800451F4(void);
void func_ovl0D_01_80045270(f32);
void func_ovl0D_01_800452B8(void);
void func_ovl0D_01_80045408(void);
void func_ovl0D_01_80045430(void);
void func_ovl0D_01_80045458(void);
void func_ovl0D_01_80045480(void);
void func_ovl0D_01_800454A8(void);
void func_ovl0D_01_800454F8(void);
void func_ovl0D_01_8004553C(void);
void func_ovl0D_01_800455B8(void);
void func_ovl0D_01_800455E0(void);
void func_ovl0D_01_80045A00(s32);
void func_ovl0D_01_80045BB4(void);
void func_ovl0D_01_80045C60(void);
void func_ovl0D_01_80045CFC(Obj_0D01 *);
void func_ovl0D_01_80045D40(Obj_0D01 *, s32, s32, f32, f32);
void func_ovl0D_01_80045E18(void);

/* .bss */
Vec4f_0D01 D_ovl0D_01_80047AD0;
Vec3f D_ovl0D_01_80047AE0;
s32 D_ovl0D_01_80047AEC;
s32 D_ovl0D_01_80047AF0;
s32 D_ovl0D_01_80047AF4;
s32 D_ovl0D_01_80047AF8;
u8 D_ovl0D_01_80047AFC[0x4]; /* unused */
Vec3f D_ovl0D_01_80047B00;
Obj_0D01 *D_ovl0D_01_80047B0C;
s32 D_ovl0D_01_80047B10;
s32 D_ovl0D_01_80047B14;
s32 D_ovl0D_01_80047B18[3];
s32 D_ovl0D_01_80047B24;
s32 D_ovl0D_01_80047B28;
s32 *D_ovl0D_01_80047B2C;
Vec3f D_ovl0D_01_80047B30;

/* .data */
u32 D_ovl0D_01_80047560[][3] = {
    { 0x990002, 0x6000E, 4 },
    { 0x9A0002, 0xE, 4 },
    { 0x970001, 0xF, 0x2004 },
};
u32 D_ovl0D_01_80047584[][3] = {
    { 0, 4, 0 },
    { 4, 0x980000, 0x84 },
};
Ent_0D01 D_ovl0D_01_8004759C[1] = {
    { NULL, -1, 0x148, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D01 D_ovl0D_01_800475D4[1] = {
    { NULL, -1, 0x146, -1, -1, -1, -1, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D01 D_ovl0D_01_8004760C[2] = {
    { NULL, -1, 0x14C, 0, 0x400, 0x20, 0x400, 290.0f, 140.0f, -100.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14D, 0, 0x400, 0x20, 0x400, 140.0f, 45.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D01 D_ovl0D_01_8004767C[2] = {
    { NULL, -1, 0x14B, 0, 0x400, 0x20, 0x400, 350.0f, 140.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14B, -1, -1, -1, -1, 130.0f, 45.0f, 40.0f, 0.0f, 270.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D01 D_ovl0D_01_800476EC[2] = {
    { NULL, -1, 0x15E, -1, -1, -1, -1, 270.0f, 60.0f, 40.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x15C, -1, -1, -1, -1, 460.0f, 120.0f, 80.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
s32 D_ovl0D_01_8004775C[2] = { 0x400, 0x422 };
Ent_0D01 D_ovl0D_01_80047764[1] = {
    { NULL, -1, 0x14A, -1, -1, -1, -1, 140.0f, -20.0f, 40.0f, 0.0f, -90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D01 D_ovl0D_01_8004779C[2] = {
    { NULL, -1, 0x149, -1, -1, -1, -1, 130.0f, 60.0f, 20.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x149, -1, -1, -1, -1, 200.0f, 40.0f, 190.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D01 D_ovl0D_01_8004780C[1] = {
    { NULL, -1, 0x15F, -1, -1, -1, -1, 130.0f, 40.0f, 260.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Trio_0D01 D_ovl0D_01_80047844[6] = {
    { 0, 7, 0xE5 },
    { 1, 2, 0xE0 },
    { 2, 9, 0xE7 },
    { 3, 9, 0xE7 },
    { 4, 8, 0xE6 },
    { 5, 0, 0xDE },
};
Ent_0D01 D_ovl0D_01_8004788C[1] = {
    { NULL, -1, 0x147, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D01 D_ovl0D_01_800478C4[1] = {
    { NULL, -1, 0x323, -1, -1, -1, -1, 130.0f, 60.0f, 100.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Move_0D01 D_ovl0D_01_800478FC = { 0x708, 1, 0, 0.0f, 0.0f, 0.0f, { 0 }, -1.0f };

/* (unused) */
static void func_ovl0D_01_80045F14(void) {
}

void func_ovl0D_01_80045E18(void) {
    Obj_0D01 *self;
    Obj_0D01 *o;
    s32 i;
    s32 n;

    self = func_ovl0D_01_80046DE0();
    o = func_ovl0D_01_80046C90(0x183, 0x11080000, 0xD0, 0);
    o->unk40->unk10 = self->unk40->unk10;
    o->unk40->unk14 = self->unk40->unk14;
    o->unk40->unk18 = self->unk40->unk18;
    n = 20;
    func_ovl0D_01_80043100(0xB3, o);
    for (i = 0; i < n; i++) {
        func_ovl0D_01_80045D40(o, i, 20, 2.0f, 4.0f);
        func_ovl0D_01_80046E00();
    }
    func_ovl0D_01_80046C80(o);
    func_ovl0D_01_80046DC8();
}

void func_ovl0D_01_80045D40(Obj_0D01 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0D_01_80046F60((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0D_01_80046F60((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

/* the callback func_ovl0D_01_800455E0 registers */
void func_ovl0D_01_80045CFC(Obj_0D01 *arg0) {
    func_ovl0D_01_80046C70(arg0, 0x01000000);
    func_ovl0D_01_80046DB8(func_ovl0D_01_80045E18, arg0, 0, 0, 0x150);
}

/* a task: the scripted run when the second exit is open */
void func_ovl0D_01_80045C60(void) {
    func_ovl0D_01_80046458(1);
    while (func_ovl0D_01_80047040(0x424) == 0) {
        func_ovl0D_01_80046E00();
    }
    func_ovl0D_01_80046458(1);
    func_ovl0D_01_800463D0(0);
    func_ovl0D_01_80046AE0(&D_ovl0D_01_800478FC, 0x170, 0);
    func_ovl0D_01_80046470("WM1 WAP WG1 WSH WDE WB6 ST1 WDN WB0 ST1 M1 ST1 M6 ST30");
    func_ovl0D_01_80046470("WM1 WAP WG1 WSH WDN WB5 ST10 M2 ST1 WDS WB3 ST1 WDN WB0 ST120 WB10");
    func_ovl0D_01_80046DD8(90);
    func_ovl0D_01_800474B8();
    func_ovl0D_01_80046DC8();
}

/* a task: the scripted run when the first exit is open */
void func_ovl0D_01_80045BB4(void) {
    func_ovl0D_01_80046458(1);
    while (func_ovl0D_01_80047040(0x424) == 0) {
        func_ovl0D_01_80046E00();
    }
    func_ovl0D_01_80046458(1);
    func_ovl0D_01_800463D0(0);
    func_ovl0D_01_80046470("WM1 WAP WG1 WSH ST1 WDN WB3 ST1 WDNE WB5 ST1");
    func_ovl0D_01_80047518(0x14);
    func_ovl0D_01_800474F0(1);
    while (func_ovl0D_01_80047500() != 0) {
        func_ovl0D_01_80046E00();
    }
    func_ovl0D_01_80047520();
    func_ovl0D_01_80046DC8();
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0D_01_80045A00(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0D_01_800455E0();
            break;
        case 17:
            func_ovl0D_01_800454A8();
            break;
        case 18:
            func_ovl0D_01_80045480();
            break;
        case 19:
            func_ovl0D_01_80045458();
            break;
        case 20:
            func_ovl0D_01_80045430();
            break;
        case 26:
            func_ovl0D_01_80045408();
            break;
        case 27:
            func_ovl0D_01_80045408();
            break;
        case 4:
            func_ovl0D_01_800452B8();
            break;
        case 5:
            func_ovl0D_01_800450C0();
            break;
        case 0x50:
            func_ovl0D_01_80044D74();
            break;
        case 0x52:
            func_ovl0D_01_80044CB0();
            break;
        case 0x53:
            func_ovl0D_01_80044C0C();
            break;
        case 15:
            func_ovl0D_01_80043010();
            break;
        case 3:
            func_ovl0D_01_800448D4();
            break;
        case 12:
            func_ovl0D_01_80045090();
            break;
        case 1:
            func_ovl0D_01_80044F00();
            break;
    }
}

void func_ovl0D_01_8004553C(void) {
    if (*D_ovl0D_01_80047B2C & 2) {
        func_ovl0D_01_80046420(0x27, 3, 0xF);
        func_ovl0D_01_80046460(0x40);
    }
}

void func_ovl0D_01_800454F8(void) {
    if (*D_ovl0D_01_80047B2C & 4) {
        func_ovl0D_01_80046420(0x1D, 2, 0x1C);
        func_ovl0D_01_80046460(0);
    }
}

void func_ovl0D_01_800455B8(void) {
    D_ovl0D_01_80047AF4 = -1;
    D_ovl0D_01_80047AF8 = -1;
}

void func_ovl0D_01_800455E0(void) {
    func_ovl0D_01_800455D8();
    func_ovl0D_01_80047120(D_ovl0D_01_80047560);
    func_ovl0D_01_80047138(D_ovl0D_01_80047584);
    func_ovl0D_01_80046268(0x13A);
    if (func_ovl0D_01_80047040(0x407) != 0) {
        D_ovl0D_01_80047844[2].unk4 = 0xA;
        D_ovl0D_01_80047844[2].unk8 = 0xE8;
    }
    if (func_ovl0D_01_80047040(0x408) != 0) {
        D_ovl0D_01_80047844[3].unk4 = 0x24;
        D_ovl0D_01_80047844[3].unk8 = 0xE8;
    }
    func_ovl0D_01_800455D0(D_ovl0D_01_80047844, 6);
    func_ovl0D_01_800462E0(0x140);
    func_ovl0D_01_80046418();
    D_ovl0D_01_80047B30.x = 32768.0f;
    D_ovl0D_01_80047B30.y = 32768.0f;
    D_ovl0D_01_80047B30.z = 32768.0f;
    func_ovl0D_01_80046278(D_ovl0D_01_80047B18);
    D_ovl0D_01_80047B0C = func_ovl0D_01_80046CB0(-1, 0x80, 0.0f, 0.0f, 0.0f);
    D_ovl0D_01_80047B0C->unkC = 0x3FFFF;
    func_ovl0D_01_800463B0(0);
    func_ovl0D_01_80047100(1);
    func_ovl0D_01_80046330(0x201F);
    func_ovl0D_01_80046350(func_ovl0D_01_80045CFC);
    func_ovl0D_01_800455B8();
    D_ovl0D_01_80047B2C = func_ovl0D_01_800463B8();
    func_ovl0D_01_800455B0();
    func_ovl0D_01_800448CC();
    func_ovl0D_01_800455A8();
    func_ovl0D_01_800455A0();
    D_ovl0D_01_80047B10 = 0;
    D_ovl0D_01_80047B14 = 0;
    func_ovl0D_01_80045598();
    func_ovl0D_01_80045590();
    func_ovl0D_01_80045588();
    func_ovl0D_01_80045580();
    func_ovl0D_01_80044408();
    func_ovl0D_01_800462E8();
    func_ovl0D_01_800434BC(D_ovl0D_01_800478C4);
    func_ovl0D_01_80046C70(D_ovl0D_01_800478C4[0].obj, 0x80000);
    func_ovl0D_01_80046C68(D_ovl0D_01_800478C4[0].obj, 0x02000000);
    func_ovl0D_01_80046CA0(D_ovl0D_01_800478C4[0].obj);
    func_ovl0D_01_8004553C();
    func_ovl0D_01_800454F8();
    func_ovl0D_01_800454F0();
}

static void func_ovl0D_01_800455D8(void) {
}

static void func_ovl0D_01_800455D0(Trio_0D01 *t, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0D_01_800472C8(t->unk0, t->unk4, t->unk8);
        t++;
    }
}

static void func_ovl0D_01_800455B0(void) {
    func_ovl0D_01_80046B58(2400.0f, 1600, 800.0f, 1600.0f);
    func_ovl0D_01_80046B68(1600.0f, 1600.0f, 3200.0f, 1600.0f);
}

static void func_ovl0D_01_800455A8(void) {
    Ent_0D01 *p;

    for (p = D_ovl0D_01_8004760C; p < D_ovl0D_01_8004760C + 2; p++) {
        func_ovl0D_01_800434BC(p);
        p->obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_01_800455A0(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_ovl0D_01_800434BC(&D_ovl0D_01_8004767C[i]);
        D_ovl0D_01_8004767C[i].obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_01_80045598(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_ovl0D_01_800434BC(&D_ovl0D_01_800476EC[i]);
        func_ovl0D_01_80046C68(D_ovl0D_01_800476EC[i].obj, 0x02000000);
        func_ovl0D_01_80046C70(D_ovl0D_01_800476EC[i].obj, 0x80000);
    }
}

static void func_ovl0D_01_80045590(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (func_ovl0D_01_80047040(D_ovl0D_01_8004775C[i]) != 0) {
            func_ovl0D_01_80043CF8(D_ovl0D_01_800476EC[i].obj);
            func_ovl0D_01_80046C70(D_ovl0D_01_800476EC[i].obj, 0x02000000);
            func_ovl0D_01_800444E0(&D_ovl0D_01_800476EC[i]);
        }
    }
}

static void func_ovl0D_01_80045588(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0D_01_800434BC(&D_ovl0D_01_80047764[i]);
        func_ovl0D_01_80046C70(D_ovl0D_01_80047764[i].obj, 0x80000);
    }
}

static void func_ovl0D_01_80045580(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_ovl0D_01_800434BC(&D_ovl0D_01_8004779C[i]);
        func_ovl0D_01_80046C70(D_ovl0D_01_8004779C[i].obj, 0x80000);
    }
}

static void func_ovl0D_01_800454F0(void) {
}

void func_ovl0D_01_800454A8(void) {
    func_ovl0D_01_80046420(0x2D, 5, 2);
    func_ovl0D_01_80046420(0xF, 5, 0x16);
    func_ovl0D_01_80046420(0x12, 3, 2);
}

void func_ovl0D_01_80045480(void) {
    func_ovl0D_01_80046420(0x2D, 5, 0);
}

void func_ovl0D_01_80045458(void) {
    func_ovl0D_01_80046420(0x26, 5, 1);
}

void func_ovl0D_01_80045430(void) {
    func_ovl0D_01_80046420(0x26, 1, 1);
}

void func_ovl0D_01_80045408(void) {
    func_ovl0D_01_80046420(0xD, 3, 2);
}

void func_ovl0D_01_800452B8(void) {
    func_ovl0D_01_800434BC(D_ovl0D_01_8004759C);
    func_ovl0D_01_80046C70(D_ovl0D_01_8004759C[0].obj, 0x80000);
    func_ovl0D_01_800434BC(D_ovl0D_01_800475D4);
    func_ovl0D_01_80043DDC();
    func_ovl0D_01_80043D3C();
    func_ovl0D_01_8004363C();
    func_ovl0D_01_80046478();
    if (!(*D_ovl0D_01_80047B2C & 2)) {
        switch (func_ovl0D_01_80046368()) {
            case 16:
            case 17:
                func_ovl0D_01_80046AC8(0.0f, 32768.0f, 32768.0f);
                break;
            case 18:
            case 19:
                func_ovl0D_01_80045270(-90.0f);
                break;
            case 26:
                func_ovl0D_01_80047340(0x6A);
                break;
        }
    }
    func_ovl0D_01_800470E0(0, 0x72, 0x37);
    func_ovl0D_01_800451F4();
    func_ovl0D_01_80045164();
}

void func_ovl0D_01_80045270(f32 arg0) {
    f32 sp1C;

    func_ovl0D_01_80046AD0(&sp1C, NULL, NULL);
    func_ovl0D_01_80046AC8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0D_01_800451F4(void) {
    if (*D_ovl0D_01_80047B2C & 2) {
        func_ovl0D_01_80046AC8(45.0f, 32768.0f, 32768.0f);
        func_ovl0D_01_80046DB8(func_ovl0D_01_80045C60, NULL, 0, 0, 0x130);
        func_ovl0D_01_80046B10(0xF);
        func_ovl0D_01_80046B20(2);
    }
}

void func_ovl0D_01_80045164(void) {
    if (*D_ovl0D_01_80047B2C & 4) {
        func_ovl0D_01_80046AC8(45.0f, 32768.0f, 32768.0f);
        func_ovl0D_01_80046DB8(func_ovl0D_01_80045BB4, NULL, 0, 0, 0x130);
        func_ovl0D_01_80046B10(0xF);
        func_ovl0D_01_80046B20(1);
        func_ovl0D_01_800470B8(0, 0, 0, 0.0f);
    }
}

void func_ovl0D_01_800450C0(void) {
    switch (func_ovl0D_01_80046368()) {
        case 18:
            func_ovl0D_01_80046468(0x80, 3, 8.5f, 3, 0, 1, 1);
            func_ovl0D_01_80046458(0);
            break;
        case 19:
            func_ovl0D_01_800463F0(0x38, 0x14);
            break;
        case 26:
            func_ovl0D_01_80046DD8(30);
            func_ovl0D_01_800463F0(0x38, 0x1B);
            break;
    }
}

void func_ovl0D_01_80045090(void) {
    func_ovl0D_01_80045088();
    if (D_ovl0D_01_80047AF4 == 0x39) {
        func_ovl0D_01_80046458(1);
    }
}

static void func_ovl0D_01_80045088(void) {
}

void func_ovl0D_01_80044EC4(void) {
    if (*D_ovl0D_01_80047B2C & 2) {
        func_ovl0D_01_800474C0();
    }
}

void func_ovl0D_01_80044E2C(void) {
    Rec_0D01 *r;

    if (*D_ovl0D_01_80047B2C & 4) {
        func_ovl0D_01_80047508(0)->unkC->unkC |= 1;
        func_ovl0D_01_80047108(0, 0, 0);
        func_ovl0D_01_800474F8();
        r = func_ovl0D_01_80047508(4);
        if (r->unkC != NULL) {
            func_ovl0D_01_80046950(r->unkC);
        }
        r->unkC = NULL;
        func_ovl0D_01_80047528();
    }
}

void func_ovl0D_01_80044F00(void) {
    func_ovl0D_01_80044EC4();
    func_ovl0D_01_80044E2C();
    func_ovl0D_01_80044E24();
    func_ovl0D_01_80044E1C();
    func_ovl0D_01_80044E14();
    func_ovl0D_01_80044E0C();
    func_ovl0D_01_80044E04();
    func_ovl0D_01_800436C8(D_ovl0D_01_8004759C);
    func_ovl0D_01_80043744();
}

static void func_ovl0D_01_80044E24(void) {
    Ent_0D01 *p;

    func_ovl0D_01_80046C80(D_ovl0D_01_80047B0C);
    for (p = D_ovl0D_01_8004760C; p < D_ovl0D_01_8004760C + 2; p++) {
        if (p->obj != NULL) {
            func_ovl0D_01_800436C8(p);
        }
    }
}

static void func_ovl0D_01_80044E1C(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0D_01_8004767C[i].obj != NULL) {
            func_ovl0D_01_800436C8(&D_ovl0D_01_8004767C[i]);
        }
    }
}

static void func_ovl0D_01_80044E14(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0D_01_800476EC[i].obj != NULL) {
            func_ovl0D_01_800436C8(&D_ovl0D_01_800476EC[i]);
        }
    }
}

static void func_ovl0D_01_80044E0C(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_ovl0D_01_80047764[i].obj != NULL) {
            func_ovl0D_01_800436C8(&D_ovl0D_01_80047764[i]);
        }
    }
}

static void func_ovl0D_01_80044E04(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0D_01_8004779C[i].obj != NULL) {
            func_ovl0D_01_800436C8(&D_ovl0D_01_8004779C[i]);
        }
    }
}

void func_ovl0D_01_80044D74(void) {
    func_ovl0D_01_80044D6C();
    if (func_ovl0D_01_80046430(0x2C, 0, 0x2E, 0) != 0) {
        D_ovl0D_01_80047AF4 = 0x39;
        D_ovl0D_01_80047AF8 = 0x11;
        func_ovl0D_01_80046360(0x39, 0x11, 0);
    }
    func_ovl0D_01_80044D64();
    if (func_ovl0D_01_80046430(7, 0x1A, 7, 0x1D) != 0) {
        func_ovl0D_01_80047218(D_ovl0D_01_80047AF0);
        func_ovl0D_01_80044428();
        func_ovl0D_01_80046388();
    }
}

static void func_ovl0D_01_80044D6C(void) {
}

static void func_ovl0D_01_80044D64(void) {
}

void func_ovl0D_01_80044CB0(void) {
    if (func_ovl0D_01_80046430(0x11, 0x16, 0x11, 0x17) != 0 || func_ovl0D_01_80046430(0x13, 0x19, 0x19, 0x19) != 0) {
        func_ovl0D_01_80046C68(D_ovl0D_01_8004759C[0].obj, 0x01000000);
        func_ovl0D_01_80046B60(70.0f, 45.0f);
        func_ovl0D_01_80046AC8(32768.0f, 45.0f, 32768.0f);
        D_ovl0D_01_80047B30.z = 150.0f;
        func_ovl0D_01_80046B48(&D_ovl0D_01_80047B30.x);
    }
    func_ovl0D_01_800443BC();
    func_ovl0D_01_800439CC();
}

void func_ovl0D_01_80044C0C(void) {
    if (func_ovl0D_01_80046430(0x12, 0x16, 0x12, 0x17) != 0 || func_ovl0D_01_80046430(0x13, 0x17, 0x19, 0x17) != 0) {
        func_ovl0D_01_80046C70(D_ovl0D_01_8004759C[0].obj, 0x01000000);
        func_ovl0D_01_80046B60(85.0f, 84.0f);
        func_ovl0D_01_80046AC8(32768.0f, 84.0f, 32768.0f);
        D_ovl0D_01_80047B30.z = 1.0f;
        func_ovl0D_01_80046B48(&D_ovl0D_01_80047B30.x);
    }
}

/* the gates: each opens when something hits it */
void func_ovl0D_01_800448D4(void) {
    s32 i;

    /* a fake (as in ovl_0D_06's 80044808): keeps the first call out of the prologue */
    if (!D_ovl0D_01_80047560 && !D_ovl0D_01_80047560 && !D_ovl0D_01_80047560) {
    }
    func_ovl0D_01_800448CC();
    func_ovl0D_01_800448C4();
    for (i = 0; i < 2; i++) {
        if (D_ovl0D_01_8004775C[i] != 0x400 || func_ovl0D_01_80047040(0x407) != 0) {
            func_ovl0D_01_800448BC(&D_ovl0D_01_800476EC[i], D_ovl0D_01_8004775C[i]);
        }
    }
}

static void func_ovl0D_01_800448CC(void) {
    UNK_MACRO_ovl0D_01_800448D4();
}

static void func_ovl0D_01_800448C4(void) {
    func_ovl0D_01_80047030(0x424);
}

static void func_ovl0D_01_800448BC(Ent_0D01 *e, s32 flag) {
    Vec3f dir;
    Vec3f pos;
    s32 r;

    if (!(e->obj->unk8 & 0x04000000)) {
        D_ovl0D_01_80047B0C->unk30 = 1;
        D_ovl0D_01_80047B0C->unk34 = 75.0f;
        D_ovl0D_01_80047B0C->unk38 = 50.0f;
        dir.x = e->obj->unk40->unk20 + 90.0f;
        dir.y = 0.0f;
        dir.z = 100.0f;
        func_ovl0D_01_80046C00(&dir.x, &pos.x);
        D_ovl0D_01_80047B0C->unk40->unk10 = e->obj->unk40->unk10 + pos.x;
        D_ovl0D_01_80047B0C->unk40->unk14 = e->obj->unk40->unk14 + pos.y;
        D_ovl0D_01_80047B0C->unk40->unk18 = e->obj->unk40->unk18 + pos.z;
        r = func_ovl0D_01_80046C18(D_ovl0D_01_80047B0C, 0x40);
        if (r != 0) {
            if ((r & 0x6000) && func_ovl0D_01_80047040(flag) == 0 &&
                !(e->obj->unk8 & 0x04000000)) {
                func_ovl0D_01_80046C68(e->obj, 0x04000000);
                func_ovl0D_01_80046C70(e->obj, 0x02000000);
                func_ovl0D_01_80047360(0x60, D_ovl0D_01_80047B0C->unk40->unk10, D_ovl0D_01_80047B0C->unk40->unk14, D_ovl0D_01_80047B0C->unk40->unk18);
            } else if (func_ovl0D_01_80047040(flag) == 0) {
                func_ovl0D_01_80047360(0x26, D_ovl0D_01_80047B0C->unk40->unk10, D_ovl0D_01_80047B0C->unk40->unk14, D_ovl0D_01_80047B0C->unk40->unk18);
            }
        }
    } else if ((e->obj->unk40->unkC & 0x40) && func_ovl0D_01_80047040(flag) == 0) {
        func_ovl0D_01_800444E0(e);
        func_ovl0D_01_80047030(flag);
        func_ovl0D_01_80047340(0x68);
    }
}

/* the tiles under a gate: solid, and the frame around its opening */
static void func_ovl0D_01_800444E0(Ent_0D01 *e) {
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
    Obj40_0D01 *p;

    p = e->obj->unk40;
    func_ovl0D_01_800462C0(p->unk10, p->unk14, p->unk18, grid, 0);
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
    dir = func_ovl0D_01_800444D8(e->obj->unk40->unk20);
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
    func_ovl0D_01_80044464(0, D_ovl0D_01_80047B18, &x0);
    func_ovl0D_01_80044464(1, D_ovl0D_01_80047B18, &y0);
    func_ovl0D_01_80044464(2, D_ovl0D_01_80047B18, &z0);
    func_ovl0D_01_80044464(0, D_ovl0D_01_80047B18, &x1);
    func_ovl0D_01_80044464(1, D_ovl0D_01_80047B18, &y1);
    func_ovl0D_01_80044464(2, D_ovl0D_01_80047B18, &z1);
    func_ovl0D_01_80044464(0, D_ovl0D_01_80047B18, &x2);
    func_ovl0D_01_80044464(2, D_ovl0D_01_80047B18, &z2);
    func_ovl0D_01_80044464(0, D_ovl0D_01_80047B18, &x3);
    func_ovl0D_01_80044464(2, D_ovl0D_01_80047B18, &z3);
    func_ovl0D_01_800462B0(x0, y0, z0, x1, y1, z1, 0x10);
    func_ovl0D_01_800462A8(x0, y0 + 1, z0, x1, z1, 0x11);
    func_ovl0D_01_800462A8(x0, y0, z0, x1, z1, 0xF);
    func_ovl0D_01_800462A8(x2, y0, z2, x3, z3, 0x11);
    func_ovl0D_01_800462A8(x2, y0 + 1, z2, x3, z3, 0x10);
}

static s32 func_ovl0D_01_800444D8(f32 a) {
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

static void func_ovl0D_01_80044464(s32 axis, s32 *size, s32 *v) {
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

void func_ovl0D_01_80044428(void) {
    s32 *p;

    p = func_ovl0D_01_80047050(0x19);
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

/* a global wrapper around the static (docs/DECOMPILING.md, ovl_0D_03's 80043770) */
void func_ovl0D_01_80044408(void) {
    func_ovl0D_01_80044154();
}

void func_ovl0D_01_800443BC(void) {
    if (func_ovl0D_01_80046430(0xD, 2, 0xD, 2) != 0 && func_ovl0D_01_80047040(0x408) == 0) {
        func_ovl0D_01_80044038();
    }
}

void func_ovl0D_01_80044154(void) {
    D_ovl0D_01_80047B24 = func_ovl0D_01_80046338(0x155);
    D_ovl0D_01_80047B28 = func_ovl0D_01_80046338(0x154);
    if (func_ovl0D_01_80047040(0x407) != 0) {
        func_ovl0D_01_80046C70(D_ovl0D_01_8004760C[0].obj, 0x01000000);
        D_ovl0D_01_8004760C[1].unk18 = 15.0f;
        D_ovl0D_01_8004760C[1].obj->unk40->unk14 = D_ovl0D_01_8004760C[1].unk18 * 10.0f;
        func_ovl0D_01_80046C70(D_ovl0D_01_8004767C[0].obj, 0x01000000);
        func_ovl0D_01_80046C70(D_ovl0D_01_8004767C[1].obj, 0x01000000);
        func_ovl0D_01_80046340(D_ovl0D_01_80047B24, 0, 0, D_ovl0D_01_80047B18[0] - 1, D_ovl0D_01_80047B18[2] - 1, 0, 1, 0);
        func_ovl0D_01_800462B0(0xD, 0, 4, 0xD, 0, 9, 0x11);
        func_ovl0D_01_800462B0(0xE, 0, 4, 0xE, 1, 9, 0x11);
        func_ovl0D_01_800462B0(0xE, 0, 4, 0xE, 0, 9, 0x1F);
    }
    if (func_ovl0D_01_80047040(0x408) != 0) {
        func_ovl0D_01_80046C70(D_ovl0D_01_8004760C[0].obj, 0x01000000);
        func_ovl0D_01_80046C70(D_ovl0D_01_8004760C[1].obj, 0x01000000);
        func_ovl0D_01_80046C70(D_ovl0D_01_8004767C[0].obj, 0x01000000);
        func_ovl0D_01_80046C70(D_ovl0D_01_8004767C[1].obj, 0x01000000);
        func_ovl0D_01_80046990(D_ovl0D_01_80047764[0].obj->unk40, 1, 0);
        func_ovl0D_01_80043CF8(D_ovl0D_01_80047764[0].obj);
        func_ovl0D_01_80043CF8(D_ovl0D_01_8004779C[0].obj);
        func_ovl0D_01_80046340(D_ovl0D_01_80047B28, 0, 0, D_ovl0D_01_80047B18[0] - 1, D_ovl0D_01_80047B18[2] - 1, 0, 0, 0);
        func_ovl0D_01_80043944(&D_ovl0D_01_8004779C[0]);
        func_ovl0D_01_80043E90();
        if (func_ovl0D_01_80046368() == 26) {
            func_ovl0D_01_80046BD0();
        }
        func_ovl0D_01_80046B98(&D_ovl0D_01_80047AD0);
    }
}

/* the first gate opens */
void func_ovl0D_01_80044038(void) {
    func_ovl0D_01_80043F04(1300.0f, 600.0f, 400.0f, 270.0f, 0xC0);
    func_ovl0D_01_80046990(D_ovl0D_01_80047764[0].obj->unk40, 1, 0);
    func_ovl0D_01_80046C68(D_ovl0D_01_80047764[0].obj, 0x04000000);
    func_ovl0D_01_80046C68(D_ovl0D_01_8004779C[0].obj, 0x04000000);
    func_ovl0D_01_80046C68(D_ovl0D_01_8004760C[1].obj, 0x04000000);
    func_ovl0D_01_80046990(D_ovl0D_01_8004767C[1].obj->unk40, 0, 0);
    func_ovl0D_01_80046C68(D_ovl0D_01_8004767C[1].obj, 0x04000000);
    func_ovl0D_01_80046340(D_ovl0D_01_80047B28, 0, 0, D_ovl0D_01_80047B18[0] - 1, D_ovl0D_01_80047B18[2] - 1, 0, 0, 0);
    func_ovl0D_01_80043944(&D_ovl0D_01_8004779C[0]);
    func_ovl0D_01_80043E90();
    func_ovl0D_01_80047030(0x408);
    func_ovl0D_01_80043E1C(0x38, 0x1A);
}

/* a gate opening: the camera goes to it */
void func_ovl0D_01_80043F04(f32 x, f32 y, f32 z, f32 ang, s32 arg4) {
    func_ovl0D_01_80043EFC();
    func_ovl0D_01_800463D0(0);
    func_ovl0D_01_80046458(1);
    func_ovl0D_01_80046B10(0xF);
    if (func_ovl0D_01_80046AF8() == 1) {
        func_ovl0D_01_80046B00();
    }
    func_ovl0D_01_80046518();
    func_ovl0D_01_80047248();
    func_ovl0D_01_80047328();
    func_ovl0D_01_80046DD8(60);
    func_ovl0D_01_80046480(1);
    func_ovl0D_01_80047340(0x29);
    func_ovl0D_01_800463D8(1);
    func_ovl0D_01_80046490(0x40);
    func_ovl0D_01_80046468(arg4, 6, 8.5f, 0, 1, 1, 0);
    func_ovl0D_01_80046458(1);
    func_ovl0D_01_80046DD8(30);
    func_ovl0D_01_80046BC8();
    func_ovl0D_01_80046B10(0x7F);
    func_ovl0D_01_80046AA8(x, y, z);
    func_ovl0D_01_80046AC8(ang, 45.0f, 32768.0f);
    func_ovl0D_01_80046B20(0);
    func_ovl0D_01_80046DD8(15);
    func_ovl0D_01_80047340(0x69);
    func_ovl0D_01_80046DD8(15);
    func_ovl0D_01_80047340(0x6F);
}

static void func_ovl0D_01_80043EFC(void) {
}

void func_ovl0D_01_80043E90(void) {
    func_ovl0D_01_800462B0(0xE, 0, 4, 0xE, 0, 9, 0x11);
    func_ovl0D_01_800462B0(0xE, 1, 4, 0xE, 1, 9, 0x10);
}

void func_ovl0D_01_80043E1C(s32 arg0, s32 arg1) {
    func_ovl0D_01_80046468(0x200, 5, 1.1111f, 1, 0, 0, 0);
    func_ovl0D_01_80046458(1);
    func_ovl0D_01_80046DD8(30);
    func_ovl0D_01_800470A8(2);
    func_ovl0D_01_800470B0();
    func_ovl0D_01_80046360(arg0, arg1, 1);
}

void func_ovl0D_01_80043DDC(void) {
    func_ovl0D_01_800434BC(D_ovl0D_01_8004780C);
    func_ovl0D_01_80046C70(D_ovl0D_01_8004780C[0].obj, 0x80000);
}

void func_ovl0D_01_80043D3C(void) {
    if (func_ovl0D_01_80047040(0x406) != 0) {
        func_ovl0D_01_800437C8(7, 2, 0x1B, 0x26);
        func_ovl0D_01_80043CF8(D_ovl0D_01_8004779C[1].obj);
        func_ovl0D_01_80043944(&D_ovl0D_01_8004779C[1]);
        func_ovl0D_01_80043CF8(D_ovl0D_01_8004780C[0].obj);
        func_ovl0D_01_800438C0();
    }
}

static void func_ovl0D_01_80043CF8(Obj_0D01 *o) {
    o->unk40->unk48->unk4->unk4 = func_ovl0D_01_800469A8(o->unk40, 0) - 0.001f;
}

void func_ovl0D_01_800438C0(void) {
    func_ovl0D_01_800462A8(8, 2, 0x1A, 0xC, 0x1D, 0x11);
    func_ovl0D_01_800462A8(8, 3, 0x1A, 0xC, 0x1D, 0x10);
    func_ovl0D_01_800462A8(8, 4, 0x1A, 0xC, 0x1D, 0x10);
}

/* the second gate's switch: the camera shows the gate opening */
void func_ovl0D_01_800439CC(void) {
    if (func_ovl0D_01_80047040(0x406) == 0) {
        if (func_ovl0D_01_80046430(0x14, 0x13, 0x14, 0x13) != 0) {
            func_ovl0D_01_800463D0(0);
            func_ovl0D_01_80046458(1);
            func_ovl0D_01_80046B10(0xF);
            if (func_ovl0D_01_80046AF8() == 1) {
                func_ovl0D_01_80046B00();
            }
            func_ovl0D_01_80046518();
            func_ovl0D_01_80047248();
            func_ovl0D_01_80047328();
            func_ovl0D_01_80046DD8(60);
            func_ovl0D_01_800463D8(1);
            func_ovl0D_01_80046480(1);
            func_ovl0D_01_80047340(0x29);
            func_ovl0D_01_80046468(0x80, 6, 8.5f, 0, 1, 1, 0);
            func_ovl0D_01_80046458(1);
            func_ovl0D_01_80046DD8(30);
            func_ovl0D_01_80046BC8();
            func_ovl0D_01_80046B10(0x7F);
            func_ovl0D_01_80046AA8(2000.0f, 700.0f, 1800.0f);
            func_ovl0D_01_80046AC8(45.0f, 45.0f, 800.0f);
            func_ovl0D_01_80046DD8(30);
            func_ovl0D_01_80046C68(D_ovl0D_01_8004759C[0].obj, 0x01000000);
            func_ovl0D_01_80047340(0x6F);
            func_ovl0D_01_80046C68(D_ovl0D_01_8004779C[1].obj, 0x04000000);
            func_ovl0D_01_80043944(&D_ovl0D_01_8004779C[1]);
            func_ovl0D_01_80046468(0x200, 5, 1.1111f, 1, 0, 0, 0);
            func_ovl0D_01_80046458(1);
            func_ovl0D_01_80043868(D_ovl0D_01_8004779C[1].obj);
            func_ovl0D_01_80047340(0x6B);
            func_ovl0D_01_80046C68(D_ovl0D_01_8004780C[0].obj, 0x04000000);
            func_ovl0D_01_80046C70(D_ovl0D_01_8004780C[0].obj, 0x02000000);
            func_ovl0D_01_800438C0();
            func_ovl0D_01_80046AA8(1000.0f, 750.0f, 2500.0f);
            func_ovl0D_01_80046AC8(315.0f, 30.0f, 3500.0f);
            func_ovl0D_01_80043868(D_ovl0D_01_8004780C[0].obj);
            func_ovl0D_01_80047370(0x6B);
            func_ovl0D_01_80047340(0x6C);
            func_ovl0D_01_80046B90(10.0f, 10.0f, 10.0f);
            func_ovl0D_01_80046B80(60);
            func_ovl0D_01_80046DD8(60);
            func_ovl0D_01_80047340(0x2C);
            func_ovl0D_01_800437C8(7, 2, 0x1B, 0x26);
            func_ovl0D_01_8004376C(315.0f, 45.0f, 1500.0f);
            func_ovl0D_01_80046C70(D_ovl0D_01_8004759C[0].obj, 0x01000000);
            func_ovl0D_01_80046E00();
            func_ovl0D_01_80046BD0();
            func_ovl0D_01_80046B98(&D_ovl0D_01_80047AD0);
            func_ovl0D_01_80046B08(0x1F);
            func_ovl0D_01_80047030(0x406);
            func_ovl0D_01_800463D8(0);
            func_ovl0D_01_800463D0(1);
            func_ovl0D_01_80046458(0);
        }
    }
}

static void func_ovl0D_01_80043944(Ent_0D01 *e) {
    s32 pos[6];
    Obj40_0D01 *p;

    p = e->obj->unk40;
    func_ovl0D_01_800462C0(p->unk10, p->unk14, p->unk18, pos, 0);
    func_ovl0D_01_800462A8(pos[0], pos[1], pos[2], pos[0], pos[2], 0x11);
    func_ovl0D_01_800462A8(pos[0], pos[1] + 1, pos[2], pos[0], pos[2], 0x10);
}

/* waits for the object's animation to end */
static void func_ovl0D_01_80043868(Obj_0D01 *o) {
    while (!(o->unk40->unkC & 0x40)) {
        func_ovl0D_01_80046E00();
    }
}

/* the camera: x tiles across, above the n rows' heights, z tiles down */
static void func_ovl0D_01_800437C8(s32 x, s32 n, s32 z, s32 id) {
    s32 i;

    D_ovl0D_01_80047B00.x = x * 100.0f;
    D_ovl0D_01_80047B00.y = 0.0f;
    for (i = 0; i < n; i++) {
        D_ovl0D_01_80047B00.y += func_ovl0D_01_800462D0(i) * 100.0f;
    }
    D_ovl0D_01_80047B00.y += 100.0f;
    D_ovl0D_01_80047B00.z = z * 100.0f;
    D_ovl0D_01_80047AF0 = func_ovl0D_01_80047210(id, &D_ovl0D_01_80047B00.x, 0);
}

void func_ovl0D_01_8004376C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0D_01_80046AA8(D_ovl0D_01_80047B00.x, D_ovl0D_01_80047B00.y, D_ovl0D_01_80047B00.z);
    func_ovl0D_01_80046AC8(arg0, arg1, arg2);
    func_ovl0D_01_80046DD8(180);
}

void func_ovl0D_01_80043744(void) {
    func_ovl0D_01_800436C8(D_ovl0D_01_8004780C);
}

static void func_ovl0D_01_800436C8(Ent_0D01 *arg0) {
    func_ovl0D_01_80046C80(arg0->obj);
    if (arg0->unkC != -1 && arg0->unkE != -1 && arg0->unk10 != -1 && arg0->unk12 != -1) {
        func_ovl0D_01_800469B8(arg0->unk4);
    }
    arg0->obj = NULL;
    arg0->unk4 = -1;
}

/* the exit's model: it fades out (the task) unless it already has */
void func_ovl0D_01_8004363C(void) {
    func_ovl0D_01_800434BC(D_ovl0D_01_8004788C);
    func_ovl0D_01_80046C70(D_ovl0D_01_8004788C[0].obj, 0x02080000);
    if (func_ovl0D_01_80047040(0x425) != 0) {
        func_ovl0D_01_80046C70(D_ovl0D_01_8004788C[0].obj, 0x01000000);
        func_ovl0D_01_80043098();
    } else {
        func_ovl0D_01_80046DB8(func_ovl0D_01_80043134, NULL, 0, 0, 0x130);
    }
}

static void func_ovl0D_01_800434BC(Ent_0D01 *arg0) {
    arg0->obj = func_ovl0D_01_80046CB0(arg0->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0D_01_80046C68(arg0->obj, 0x01080000);
    func_ovl0D_01_80046C70(arg0->obj, 0x02000000);
    if (arg0->unkC != -1 && arg0->unkE != -1 && arg0->unk10 != -1 && arg0->unk12 != -1) {
        arg0->unk4 = func_ovl0D_01_800469B0(arg0->obj->unk40, 0, arg0->unkC, arg0->unkE, arg0->unk10, arg0->unk12);
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

/* a task: waits for something to hit the exit, then fades its model out */
void func_ovl0D_01_80043134(void) {
    Vec3f pos;
    s32 i;
    s32 n;

    while (TRUE) {
        D_ovl0D_01_80047B0C->unk30 = 1;
        D_ovl0D_01_80047B0C->unk34 = 75.0f;
        D_ovl0D_01_80047B0C->unk38 = 50.0f;
        D_ovl0D_01_80047B0C->unk40->unk10 = 2000.0f;
        D_ovl0D_01_80047B0C->unk40->unk14 = 400.0f;
        D_ovl0D_01_80047B0C->unk40->unk18 = 2300.0f;
        D_ovl0D_01_80047B0C->unk14 = 0;
        if (func_ovl0D_01_80046C20(D_ovl0D_01_80047B0C, 0x4040) != 0) {
            break;
        }
        if (func_ovl0D_01_80046C20(D_ovl0D_01_80047B0C, 0x40) != 0) {
            func_ovl0D_01_80043100(0x26, D_ovl0D_01_80047B0C);
        }
        func_ovl0D_01_80046DD8(5);
        D_ovl0D_01_80047B0C->unk30 = 1;
        D_ovl0D_01_80047B0C->unk34 = 75.0f;
        D_ovl0D_01_80047B0C->unk38 = 50.0f;
        D_ovl0D_01_80047B0C->unk40->unk10 = 2300.0f;
        D_ovl0D_01_80047B0C->unk40->unk14 = 400.0f;
        D_ovl0D_01_80047B0C->unk40->unk18 = 2300.0f;
        D_ovl0D_01_80047B0C->unk14 = 0;
        if (func_ovl0D_01_80046C20(D_ovl0D_01_80047B0C, 0x4040) != 0) {
            break;
        }
        if (func_ovl0D_01_80046C20(D_ovl0D_01_80047B0C, 0x40) != 0) {
            func_ovl0D_01_80043100(0x26, D_ovl0D_01_80047B0C);
        }
        func_ovl0D_01_80046DD8(5);
    }
    func_ovl0D_01_80047360(0x63, 2150.0f, 800.0f, 2400.0f);
    func_ovl0D_01_80046C68(D_ovl0D_01_8004788C[0].obj, 0x80000);
    D_ovl0D_01_8004788C[0].obj->unk40->unk36 = 0xFF;
    n = 10;
    for (i = 0; i < 120; i++) {
        n++;
        D_ovl0D_01_8004788C[0].obj->unk40->unk36 = (1.0f - i / 120.0f) * 255.0f;
        if (n >= 11) {
            pos.x = func_ovl0D_01_80046F70() * 600.0 + 1900.0;
            pos.y = func_ovl0D_01_80046F70() * 500.0 + 500.0;
            pos.z = 2500.0f;
            func_ovl0D_01_80047210(0x14, &pos.x, 0);
            n = 0;
        }
        func_ovl0D_01_80046E00();
    }
    func_ovl0D_01_80046C70(D_ovl0D_01_8004788C[0].obj, 0x01000000);
    func_ovl0D_01_80043098();
    func_ovl0D_01_80047030(0x425);
    func_ovl0D_01_80046DC8();
}

void func_ovl0D_01_80043100(s32 arg0, Obj_0D01 *arg1) {
    Obj40_0D01 *p;

    p = arg1->unk40;
    func_ovl0D_01_80047360(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0D_01_80043098(void) {
    func_ovl0D_01_800462B0(0x13, 3, 0x18, 0x19, 5, 0x18, 0x10);
    func_ovl0D_01_800462A8(0x13, 2, 0x18, 0x19, 0x18, 0x11);
}

void func_ovl0D_01_80043010(void) {
    if (func_ovl0D_01_80046438(0xE, 3, 0xA, 0xE, 0xA) != 0 || func_ovl0D_01_80046438(0xD, 3, 0xB, 0xD, 0xB) != 0) {
        if (func_ovl0D_01_80047020(0xA4) != 0) {
            func_ovl0D_01_800469D0(0x291, 1);
        } else {
            func_ovl0D_01_800469D0(0x290, 2);
        }
    }
}
