/*
 * NON_MATCHING: ovl_0D_04's stage object, complete: all 43 functions; .data 0x350
 * and .bss 0x60 as the original, and the stubs' places.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 512, eu 684, jp 512 (eu not re-measured)
 *
 * The gate 80044318 matches in us: its loop calls the per-gate static
 * 80044300 (Ent, flag), as ovl_0D_02's 800434F8 does, with a fake that
 * reads D_ovl0D_04_80047044 (ovl_0D_02's 80043510 reads 47A40); its locals
 * are dir, pos, r with dir.x set first.
 *
 * What still differs in us (words):
 * - func_ovl0D_04_80043700 (179): the original builds &CCC[1] at run time
 *   (`li v1,1` then *56) and CCC[2] as +0x38, and multiplies constants at
 *   run time (x*10 with x in a register); 4 words long.
 * - func_ovl0D_04_80043C50 (92): the original reaches CCC[0]/CCC[1] with
 *   %lo(sym+off) and no reload; ours keeps &CCC in s1 and reloads.
 * - func_ovl0D_04_80043E70 (67; the static 80043F24 with it): s register
 *   numbering of the case temporaries (original x0 s0, x1 s1, z1 s2, z0 s3)
 *   and the float compares' operand order (`c.eq.s const, a`).
 * - func_ovl0D_04_80044D98 (174): &C24 kept in s4 between the 0x18 branch
 *   and the first loop (the original recomputes it); the camera's 1600.0f
 *   in $f16 as in ovl_0D_05.
 */
#include "common.h"

/*
 * ovl_0D_04's stage object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).
 */

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} Anim2_0D04;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ Anim2_0D04 *unk4;
} Anim_0D04;

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
    /* 0x48 */ Anim_0D04 *unk48;
} Obj40_0D04;

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
    /* 0x40 */ Obj40_0D04 *unk40;
} Obj_0D04;

/* a model placed on the stage: the object, its collision handle, its model
 * id, its collision box, and its position (in tiles), angles and scale */
typedef struct {
    /* 0x00 */ Obj_0D04 *obj;
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
} Ent_0D04;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Trio_0D04;

typedef struct {
    f32 x, y, z, w;
} Vec4f_0D04;

void func_ovl0D_04_80045908(s32); /* 0xC00 */
void func_ovl0D_04_80045918(s32 *); /* 0xC02 */
void func_ovl0D_04_80045948(s32, s32, s32, s32, s32, s32); /* 0xD05 */
void func_ovl0D_04_80045950(s32, s32, s32, s32, s32, s32, s32); /* 0xD06 */
void func_ovl0D_04_80045960(f32, f32, f32, s32 *, s32); /* 0xD08 */
void func_ovl0D_04_80045980(s32); /* 0xD0C */
void func_ovl0D_04_80045988(void); /* 0xD0D */
void func_ovl0D_04_800459D0(s32); /* 0xD16 */
s32 func_ovl0D_04_800459D8(s32); /* 0xE00 */
void func_ovl0D_04_800459E0(s32, s32, s32, s32, s32, s32, s32, s32); /* 0xE01 */
void func_ovl0D_04_800459F0(void (*)(Obj_0D04 *)); /* 0xE03 */
void func_ovl0D_04_80045A00(s32, s32, s32); /* 0xF00 */
s32 func_ovl0D_04_80045A08(void); /* 0xF01 */
void func_ovl0D_04_80045A50(s32); /* 0xF0A */
s32 *func_ovl0D_04_80045A58(void); /* 0xF0B */
void func_ovl0D_04_80045A70(s32); /* 0xF0E */
void func_ovl0D_04_80045A78(s32); /* 0xF0F */
void func_ovl0D_04_80045A90(s32, s32); /* 0xF12 */
void func_ovl0D_04_80045AB8(void); /* 0x1000 */
void func_ovl0D_04_80045AC0(s32, s32, s32); /* 0x1001 */
void func_ovl0D_04_80045AC8(void *); /* 0x1002 */
s32 func_ovl0D_04_80045AD0(s32, s32, s32, s32); /* 0x1003 */
s32 func_ovl0D_04_80045AE8(void); /* 0x1006 */
void func_ovl0D_04_80045AF0(s32, void *); /* 0x1007 */
void func_ovl0D_04_80045AF8(s32); /* 0x1008 */
void func_ovl0D_04_80045B00(s32); /* 0x1009 */
void func_ovl0D_04_80045B08(s32, s32, f32, s32, s32, s32, s32); /* 0x100A */
void func_ovl0D_04_80045B18(void); /* 0x100C */
void func_ovl0D_04_80045B20(s32); /* 0x100D */
void func_ovl0D_04_80045B30(s32); /* 0x100F */
void func_ovl0D_04_80045BB8(void); /* 0x1020 */
void func_ovl0D_04_80046030(Obj40_0D04 *, s32, s32); /* 0x1509 */
f32 func_ovl0D_04_80046048(Obj40_0D04 *, s32); /* 0x150C */
s32 func_ovl0D_04_80046050(Obj40_0D04 *, s32, s32, s32, s32, s32); /* 0x150D */
void func_ovl0D_04_80046058(s32); /* 0x150E */
void func_ovl0D_04_80046148(f32, f32, f32); /* 0x1704 */
void func_ovl0D_04_80046168(f32, f32, f32); /* 0x1708 */
void func_ovl0D_04_80046170(f32 *, f32 *, f32 *); /* 0x1709 */
s32 func_ovl0D_04_80046198(void); /* 0x170E */
void func_ovl0D_04_800461A0(void); /* 0x170F */
void func_ovl0D_04_800461A8(s32); /* 0x1710 */
void func_ovl0D_04_800461B0(s32); /* 0x1711 */
void func_ovl0D_04_800461C0(s32); /* 0x1713 */
void func_ovl0D_04_800461F8(f32, f32, f32, f32); /* 0x171A */
void func_ovl0D_04_80046208(f32, f32, f32, f32); /* 0x171C */
void func_ovl0D_04_80046238(void *); /* 0x1722 */
void func_ovl0D_04_80046268(void); /* 0x1728 */
void func_ovl0D_04_80046270(void); /* 0x1729 */
void func_ovl0D_04_80046278(f32, f32); /* 0x172A */
void func_ovl0D_04_800462A0(f32 *, f32 *); /* 0x1804 */
s32 func_ovl0D_04_800462B8(Obj_0D04 *, s32); /* 0x1807 */
void func_ovl0D_04_80046308(Obj_0D04 *, s32); /* 0x1811 */
void func_ovl0D_04_80046310(Obj_0D04 *, s32); /* 0x1812 */
void func_ovl0D_04_80046320(Obj_0D04 *); /* 0x1814 */
Obj_0D04 *func_ovl0D_04_80046330(s32, s32, s32, s32); /* 0x1816 */
Obj_0D04 *func_ovl0D_04_80046350(s32, s32, f32, f32, f32); /* 0x181A */
void func_ovl0D_04_80046458(void (*)(void), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0D_04_80046468(void); /* 0x1902 */
void func_ovl0D_04_80046478(s32); /* 0x1904 */
void *func_ovl0D_04_80046480(void); /* 0x1905 */
void func_ovl0D_04_800464A0(void); /* 0x1909 */
f32 func_ovl0D_04_80046600(f32); /* 0x1D00 */
void func_ovl0D_04_800466D0(s32); /* 0x1E06 */
s32 func_ovl0D_04_800466E0(s32); /* 0x1E08 */
void func_ovl0D_04_80046748(s32); /* 0x2002 */
void func_ovl0D_04_80046750(void); /* 0x2003 */
void func_ovl0D_04_80046780(s32, s32, s32); /* 0x2101 */
void func_ovl0D_04_800467A0(s32); /* 0x2200 */
void func_ovl0D_04_800467C0(u32 (*)[3]); /* 0x2300 */
void func_ovl0D_04_800468E8(void); /* 0x2704 */
void func_ovl0D_04_80046968(s32, s32, s32); /* 0x2A00 */
void func_ovl0D_04_800469C8(void); /* 0x2A0C */
void func_ovl0D_04_800469E0(s32); /* 0x2B00 */
void func_ovl0D_04_80046A00(s32, f32, f32, f32); /* 0x2B04 */

void func_ovl0D_04_80043190(void);
void func_ovl0D_04_80043338(s32, s32);
void func_ovl0D_04_800433AC(void);
void func_ovl0D_04_80043478(f32, f32, f32, f32, s32);
void func_ovl0D_04_800435AC(void);
void func_ovl0D_04_80043700(void);
void func_ovl0D_04_80043A8C(void);
void func_ovl0D_04_80043AD8(void);
void func_ovl0D_04_80043C50(void);
void func_ovl0D_04_80043DF0(void);
void func_ovl0D_04_80043E70(void);
void func_ovl0D_04_80044318(void);
void func_ovl0D_04_80044624(void);
void func_ovl0D_04_800446E8(void);
void func_ovl0D_04_80044840(void);
void func_ovl0D_04_8004488C(void);
void func_ovl0D_04_80044964(void);
void func_ovl0D_04_80044A84(f32);
void func_ovl0D_04_80044ACC(void);
void func_ovl0D_04_80044C20(void);
void func_ovl0D_04_80044C48(void);
void func_ovl0D_04_80044C70(void);
void func_ovl0D_04_80044C98(void);
void func_ovl0D_04_80044CC0(void);
void func_ovl0D_04_80044CE8(void);
void func_ovl0D_04_80044D10(void);
void func_ovl0D_04_80044D70(void);
void func_ovl0D_04_80044D98(void);
void func_ovl0D_04_80045160(s32);
void func_ovl0D_04_800452F8(Obj_0D04 *);
void func_ovl0D_04_8004533C(Obj_0D04 *, s32, s32, f32, f32);
void func_ovl0D_04_80045414(s32, Obj_0D04 *);
void func_ovl0D_04_80045448(void);
void func_ovl0D_04_80045544(f32, f32, f32);

static void func_ovl0D_04_80043010(Ent_0D04 *);
static void func_ovl0D_04_800433F0(Ent_0D04 *);
static void func_ovl0D_04_800436BC(Obj_0D04 *);
static void func_ovl0D_04_80043EA8(s32, s32 *, s32 *);
static s32 func_ovl0D_04_80043F1C(f32);
static void func_ovl0D_04_80043F24(Ent_0D04 *);
static void func_ovl0D_04_80044644(Ent_0D04 *);
static void func_ovl0D_04_800446C0(void);
static void func_ovl0D_04_800446C8(void);
static void func_ovl0D_04_800446D0(void);
static void func_ovl0D_04_800446D8(void);
static void func_ovl0D_04_800446E0(void);
static void func_ovl0D_04_80044300(Ent_0D04 *, s32);
static void func_ovl0D_04_80044308(void);
static void func_ovl0D_04_80044310(void);
static void func_ovl0D_04_80043AD0(void);
static void func_ovl0D_04_80044838(void);
static void func_ovl0D_04_80044884(void);
static void func_ovl0D_04_80044D38(void);
static void func_ovl0D_04_80044D40(void);
static void func_ovl0D_04_80044D48(void);
static void func_ovl0D_04_80044D50(void);
static void func_ovl0D_04_80044D58(void);
static void func_ovl0D_04_80044D60(void);
static void func_ovl0D_04_80044D68(void);
static void func_ovl0D_04_80044D88(Trio_0D04 *, s32);
static void func_ovl0D_04_80044D90(void);
static void func_ovl0D_04_800455A0(void);
static void func_ovl0D_04_800455A8(void);
static void func_ovl0D_04_800455B0(void);
static void func_ovl0D_04_800455B8(void);

#define UNK_MACRO_ovl0D_04_80044318() \
    D_ovl0D_04_8004703C = func_ovl0D_04_80045AE8(); func_ovl0D_04_80045AC8(&D_ovl0D_04_80047030); func_ovl0D_04_80045AF0(D_ovl0D_04_8004703C, &D_ovl0D_04_80047020)

/* .bss */
Vec4f_0D04 D_ovl0D_04_80047020;
Vec3f D_ovl0D_04_80047030;
s32 D_ovl0D_04_8004703C;
u8 D_ovl0D_04_80047040[0x4]; /* unused (func_ovl0D_04_800455B8) */
s32 D_ovl0D_04_80047044;
s32 D_ovl0D_04_80047048;
u8 D_ovl0D_04_8004704C[0x4]; /* unused (func_ovl0D_04_800455B8) */
Vec3f D_ovl0D_04_80047050;
Obj_0D04 *D_ovl0D_04_8004705C;
s32 D_ovl0D_04_80047060;
s32 D_ovl0D_04_80047064;
s32 D_ovl0D_04_80047068[3];
s32 D_ovl0D_04_80047074;
s32 *D_ovl0D_04_80047078;

/* .data */
/* passed to func_ovl0D_04_800467C0: three 12-byte records */
u32 D_ovl0D_04_80046C00[][3] = {
    { 0x9C0002, 0xE, 4 },
    { 0x990002, 0xE, 4 },
    { 0x9B0002, 0xE, 4 },
};
Ent_0D04 D_ovl0D_04_80046C24[3] = {
    { NULL, -1, 0x150, 0, 0x400, 0x20, 0x400, 180.0f, 35.0f, 190.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x151, 0, 0x400, 0x20, 0x400, 20.0f, 20.0f, 100.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14F, 0, 0x400, 0x20, 0x400, 300.0f, -80.0f, 310.0f, 0.0f, 270.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D04 D_ovl0D_04_80046CCC[3] = {
    { NULL, -1, 0x14B, 0, 0x400, 0x20, 0x400, 180.0f, 35.0f, 300.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14B, -1, -1, -1, -1, 440.0f, 55.0f, 200.0f, 0.0f, 90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14B, -1, -1, -1, -1, 170.0f, 20.0f, 10.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D04 D_ovl0D_04_80046D74[1] = {
    { NULL, -1, 0x15C, -1, -1, -1, -1, 60.0f, 60.0f, 250.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
s32 D_ovl0D_04_80046DAC[1] = { 0x403 };
Ent_0D04 D_ovl0D_04_80046DB0[2] = {
    { NULL, -1, 0x14A, -1, -1, -1, -1, 180.0f, -15.0f, 290.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14A, -1, -1, -1, -1, 20.0f, -30.0f, 200.0f, 0.0f, -90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D04 D_ovl0D_04_80046E20[2] = {
    { NULL, -1, 0x149, -1, -1, -1, -1, 240.0f, 80.0f, 290.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x149, -1, -1, -1, -1, 20.0f, 60.0f, 190.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
s32 D_ovl0D_04_80046E90[2] = { 0x407, 0x409 };
Ent_0D04 D_ovl0D_04_80046E98[1] = {
    { NULL, -1, 0x162, -1, -1, -1, -1, -30.0f, -140.0f, 160.0f, 0.0f, -90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent_0D04 D_ovl0D_04_80046ED0[1] = {
    { NULL, -1, 0x167, 0, 0x400, 0x20, 0x400, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Trio_0D04 D_ovl0D_04_80046F08[5] = {
    { 0, 9, 0xE7 },
    { 1, 10, 0xE8 },
    { 2, 2, 0xE0 },
    { 3, 8, 0xE6 },
    { 4, 0, 0xDE },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0D_04_800455B8(void) {
    D_ovl0D_04_80047040[0] = D_ovl0D_04_8004704C[0];
}

static void func_ovl0D_04_800455B0(void) {
}

static void func_ovl0D_04_800455A8(void) {
}

static void func_ovl0D_04_800455A0(void) {
}

void func_ovl0D_04_80045544(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0D_04_80046148(D_ovl0D_04_80047050.x, D_ovl0D_04_80047050.y, D_ovl0D_04_80047050.z);
    func_ovl0D_04_80046168(arg0, arg1, arg2);
    func_ovl0D_04_80046478(180);
}

void func_ovl0D_04_80045448(void) {
    Obj_0D04 *self;
    Obj_0D04 *o;
    s32 i;
    s32 n;

    self = func_ovl0D_04_80046480();
    o = func_ovl0D_04_80046330(0x183, 0x11080000, 0xD0, 0);
    o->unk40->unk10 = self->unk40->unk10;
    o->unk40->unk14 = self->unk40->unk14;
    o->unk40->unk18 = self->unk40->unk18;
    n = 20;
    func_ovl0D_04_80045414(0xB3, o);
    for (i = 0; i < n; i++) {
        func_ovl0D_04_8004533C(o, i, 20, 2.0f, 4.0f);
        func_ovl0D_04_800464A0();
    }
    func_ovl0D_04_80046320(o);
    func_ovl0D_04_80046468();
}

void func_ovl0D_04_80045414(s32 arg0, Obj_0D04 *arg1) {
    Obj40_0D04 *p;

    p = arg1->unk40;
    func_ovl0D_04_80046A00(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0D_04_8004533C(Obj_0D04 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0D_04_80046600((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0D_04_80046600((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

/* the callback func_ovl0D_04_80044D98 registers */
void func_ovl0D_04_800452F8(Obj_0D04 *arg0) {
    func_ovl0D_04_80046310(arg0, 0x01000000);
    func_ovl0D_04_80046458(func_ovl0D_04_80045448, arg0, 0, 0, 0x150);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0D_04_80045160(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0D_04_80044D98();
            break;
        case 16:
            func_ovl0D_04_80045AC0(0x1C, 4, 0x1D);
            break;
        case 18:
            func_ovl0D_04_80045AC0(0x2A, 2, 0x1E);
            break;
        case 19:
            func_ovl0D_04_80045AC0(0x1E, 2, 0x1C);
            break;
        case 20:
            func_ovl0D_04_80045AC0(0x1C, 4, 0x1D);
            break;
        case 24:
            func_ovl0D_04_80045AC0(2, 0, 0x1D);
            break;
        case 26:
        case 28:
            func_ovl0D_04_80045AC0(0x18, 4, 0x1D);
            break;
        case 27:
        case 29:
            func_ovl0D_04_80045AC0(2, 3, 0x13);
            break;
        case 4:
            func_ovl0D_04_80044ACC();
            break;
        case 5:
            func_ovl0D_04_80044964();
            break;
        case 0x50:
            func_ovl0D_04_8004488C();
            break;
        case 0x52:
            func_ovl0D_04_80043DF0();
            break;
        case 3:
            func_ovl0D_04_80044318();
            break;
        case 12:
            func_ovl0D_04_80044840();
            break;
        case 1:
            func_ovl0D_04_800446E8();
            break;
    }
}

void func_ovl0D_04_80044D70(void) {
    D_ovl0D_04_80047044 = -1;
    D_ovl0D_04_80047048 = -1;
}

void func_ovl0D_04_80044D98(void) {
    func_ovl0D_04_800467C0(D_ovl0D_04_80046C00);
    func_ovl0D_04_80045908(0x13D);
    if (func_ovl0D_04_800466E0(0x407) != 0) {
        D_ovl0D_04_80046F08[1].unk4 = 9;
        D_ovl0D_04_80046F08[1].unk8 = 0xE7;
    }
    func_ovl0D_04_80044D88(D_ovl0D_04_80046F08, 5);
    func_ovl0D_04_80045980(0x143);
    func_ovl0D_04_80045AB8();
    if (func_ovl0D_04_80045A08() == 24) {
        func_ovl0D_04_800466D0(0x421);
        func_ovl0D_04_80044D90();
        D_ovl0D_04_80046C24[2].unk8 = 0x153;
        D_ovl0D_04_80046C24[2].unk14 = -30.0f;
        D_ovl0D_04_80046C24[2].unk18 = -120.0f;
        D_ovl0D_04_80046C24[2].unk1C = 100.0f;
        D_ovl0D_04_80046C24[2].unk24 = 270.0f;
    }
    func_ovl0D_04_80045918(D_ovl0D_04_80047068);
    D_ovl0D_04_8004705C = func_ovl0D_04_80046350(-1, 0x80, 0.0f, 0.0f, 0.0f);
    D_ovl0D_04_8004705C->unkC = 0x3FFFF;
    func_ovl0D_04_80045A50(0);
    func_ovl0D_04_800467A0(1);
    func_ovl0D_04_800459D0(0x201F);
    func_ovl0D_04_800459F0(func_ovl0D_04_800452F8);
    func_ovl0D_04_80044D70();
    D_ovl0D_04_80047078 = func_ovl0D_04_80045A58();
    func_ovl0D_04_800467A0(1);
    func_ovl0D_04_80044D40();
    func_ovl0D_04_80044310();
    func_ovl0D_04_80044D68();
    func_ovl0D_04_80044D60();
    D_ovl0D_04_80047060 = 0;
    D_ovl0D_04_80047064 = 0;
    func_ovl0D_04_80044D58();
    func_ovl0D_04_80044D38();
    func_ovl0D_04_80044D50();
    func_ovl0D_04_80044D48();
    func_ovl0D_04_80043E70();
    func_ovl0D_04_80045988();
}

static void func_ovl0D_04_80044D90(void) {
}

static void func_ovl0D_04_80044D88(Trio_0D04 *t, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0D_04_80046968(t->unk0, t->unk4, t->unk8);
        t++;
    }
}

static void func_ovl0D_04_80044D68(void) {
    Ent_0D04 *p;

    for (p = D_ovl0D_04_80046C24; p < D_ovl0D_04_80046C24 + 3; p++) {
        func_ovl0D_04_80043010(p);
        p->obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_04_80044D60(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_ovl0D_04_80043010(&D_ovl0D_04_80046CCC[i]);
        D_ovl0D_04_80046CCC[i].obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_04_80044D58(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0D_04_80043010(&D_ovl0D_04_80046D74[i]);
        func_ovl0D_04_80046308(D_ovl0D_04_80046D74[i].obj, 0x02000000);
        func_ovl0D_04_80046310(D_ovl0D_04_80046D74[i].obj, 0x80000);
    }
}

static void func_ovl0D_04_80044D50(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_ovl0D_04_80043010(&D_ovl0D_04_80046DB0[i]);
        func_ovl0D_04_80046310(D_ovl0D_04_80046DB0[i].obj, 0x80000);
    }
}

static void func_ovl0D_04_80044D48(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_ovl0D_04_80043010(&D_ovl0D_04_80046E20[i]);
        func_ovl0D_04_80046310(D_ovl0D_04_80046E20[i].obj, 0x80000);
    }
}

static void func_ovl0D_04_80044D40(void) {
    func_ovl0D_04_800461F8(2400.0f, 1600, 800.0f, 1600.0f);
    func_ovl0D_04_80046208(1600.0f, 1600.0f, 3200.0f, 1600.0f);
}

static void func_ovl0D_04_80044D38(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (func_ovl0D_04_800466E0(D_ovl0D_04_80046DAC[i]) != 0) {
            func_ovl0D_04_800436BC(D_ovl0D_04_80046D74[i].obj);
            func_ovl0D_04_80046310(D_ovl0D_04_80046D74[i].obj, 0x02000000);
            func_ovl0D_04_80043F24(&D_ovl0D_04_80046D74[i]);
        }
    }
}

void func_ovl0D_04_80044D10(void) {
    func_ovl0D_04_80045AC0(0x1C, 4, 0x1D);
}

void func_ovl0D_04_80044CE8(void) {
    func_ovl0D_04_80045AC0(0x2A, 2, 0x1E);
}

void func_ovl0D_04_80044CC0(void) {
    func_ovl0D_04_80045AC0(0x1E, 2, 0x1C);
}

void func_ovl0D_04_80044C98(void) {
    func_ovl0D_04_80045AC0(0x1C, 4, 0x1D);
}

void func_ovl0D_04_80044C70(void) {
    func_ovl0D_04_80045AC0(2, 0, 0x1D);
}

void func_ovl0D_04_80044C48(void) {
    func_ovl0D_04_80045AC0(0x18, 4, 0x1D);
}

void func_ovl0D_04_80044C20(void) {
    func_ovl0D_04_80045AC0(2, 3, 0x13);
}

void func_ovl0D_04_80044ACC(void) {
    func_ovl0D_04_80043190();
    func_ovl0D_04_80045B18();
    func_ovl0D_04_800461A8(0x40);
    func_ovl0D_04_80046278(400.0f, 800.0f);
    if (func_ovl0D_04_800466E0(0x421) == 0) {
        func_ovl0D_04_80046780(0x2D, 0x6E, 0x2C);
    } else {
        func_ovl0D_04_80046780(-0x2D, 0x6E, 0x2C);
    }
    switch (func_ovl0D_04_80045A08()) {
        case 18:
        case 19:
            func_ovl0D_04_80045B00(0);
            func_ovl0D_04_80044A84(-90.0f);
            break;
        case 24:
            func_ovl0D_04_80045B00(0x40);
            func_ovl0D_04_80044A84(-90.0f);
            break;
        case 20:
            func_ovl0D_04_80046168(0.0f, 32768.0f, 32768.0f);
            break;
        case 26:
        case 27:
            func_ovl0D_04_800469E0(0x6A);
            break;
    }
}

void func_ovl0D_04_80044A84(f32 arg0) {
    f32 sp1C;

    func_ovl0D_04_80046170(&sp1C, NULL, NULL);
    func_ovl0D_04_80046168(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0D_04_80044964(void) {
    switch (func_ovl0D_04_80045A08()) {
        case 18:
            func_ovl0D_04_80045B08(0, 3, 8.5f, 5, 0, 1, 1);
            func_ovl0D_04_80045AF8(0);
            break;
        case 19:
            func_ovl0D_04_80045B08(0, 3, 8.5f, 5, 0, 1, 1);
            func_ovl0D_04_80045AF8(0);
            break;
        case 24:
            func_ovl0D_04_80045B08(0x40, 3, 8.5f, 7, 0, 1, 1);
            func_ovl0D_04_80045AF8(0);
            break;
        case 26:
            func_ovl0D_04_80045A90(0x3B, 0x1C);
            func_ovl0D_04_80046478(30);
            break;
        case 27:
            func_ovl0D_04_80045A90(0x3B, 0x1D);
            func_ovl0D_04_80046478(30);
            break;
    }
}

void func_ovl0D_04_8004488C(void) {
    func_ovl0D_04_80044884();
    if (func_ovl0D_04_80045AD0(0x29, 0x1E, 0x2A, 0x1E) != 0) {
        D_ovl0D_04_80047044 = 0x39;
        D_ovl0D_04_80047048 = 0x14;
        func_ovl0D_04_80045A00(0x39, 0x14, 0);
    }
    if (func_ovl0D_04_80045AD0(0x1E, 0x1C, 0x1F, 0x1C) != 0) {
        D_ovl0D_04_80047044 = 0x3A;
        D_ovl0D_04_80047048 = 0x14;
        func_ovl0D_04_80045A00(0x3A, 0x14, 0);
    }
    if (func_ovl0D_04_80045AD0(2, 0x1C, 2, 0x1D) != 0) {
        D_ovl0D_04_80047044 = 0x3D;
        D_ovl0D_04_80047048 = 0x18;
        func_ovl0D_04_80045A00(0x3D, 0x18, 0);
    }
}

void func_ovl0D_04_80044840(void) {
    func_ovl0D_04_80044838();
    func_ovl0D_04_80044838();
    if (D_ovl0D_04_80047044 == 0x39 || D_ovl0D_04_80047044 == 0x3A || D_ovl0D_04_80047044 == 0x3D) {
        func_ovl0D_04_80045AF8(1);
    }
}

static void func_ovl0D_04_80044838(void) {
}

static void func_ovl0D_04_80044884(void) {
}

void func_ovl0D_04_800446E8(void) {
    if (!D_ovl0D_04_80047044 && !D_ovl0D_04_80047044 && !D_ovl0D_04_80047044) {
    }
    func_ovl0D_04_800446C0();
    func_ovl0D_04_800446C8();
    func_ovl0D_04_800446D0();
    func_ovl0D_04_800446D8();
    func_ovl0D_04_800446E0();
    func_ovl0D_04_80044644(D_ovl0D_04_80046E98);
}

static void func_ovl0D_04_800446E0(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0D_04_80046E20[i].obj != NULL) {
            func_ovl0D_04_80044644(&D_ovl0D_04_80046E20[i]);
        }
    }
}

static void func_ovl0D_04_800446D8(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0D_04_80046DB0[i].obj != NULL) {
            func_ovl0D_04_80044644(&D_ovl0D_04_80046DB0[i]);
        }
    }
}

static void func_ovl0D_04_800446D0(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_ovl0D_04_80046D74[i].obj != NULL) {
            func_ovl0D_04_80044644(&D_ovl0D_04_80046D74[i]);
        }
    }
}

static void func_ovl0D_04_800446C8(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_ovl0D_04_80046CCC[i].obj != NULL) {
            func_ovl0D_04_80044644(&D_ovl0D_04_80046CCC[i]);
        }
    }
}

static void func_ovl0D_04_800446C0(void) {
    Ent_0D04 *p;

    func_ovl0D_04_80046320(D_ovl0D_04_8004705C);
    for (p = D_ovl0D_04_80046C24; p < D_ovl0D_04_80046C24 + 3; p++) {
        if (p->obj != NULL) {
            func_ovl0D_04_80044644(p);
        }
    }
}

static void func_ovl0D_04_80044644(Ent_0D04 *arg0) {
    func_ovl0D_04_80046320(arg0->obj);
    if (arg0->unkC != 0xFFFF && arg0->unkE != 0xFFFF && arg0->unk10 != 0xFFFF && arg0->unk12 != 0xFFFF) {
        func_ovl0D_04_80046058(arg0->unk4);
    }
    arg0->obj = NULL;
    arg0->unk4 = -1;
}

void func_ovl0D_04_80044624(void) {
    func_ovl0D_04_80043DF0();
}

static s32 func_ovl0D_04_80043F1C(f32 a) {
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

void func_ovl0D_04_80044318(void) {
    s32 i;

    /* a fake (as in ovl_0D_02's 80043510): keeps the first call out of the prologue */
    if (!D_ovl0D_04_80047044 && !D_ovl0D_04_80047044 && !D_ovl0D_04_80047044) {
    }
    func_ovl0D_04_80044310();
    func_ovl0D_04_80044308();
    for (i = 0; i < 1; i++) {
        func_ovl0D_04_80044300(&D_ovl0D_04_80046D74[i], D_ovl0D_04_80046DAC[i]);
    }
}

static void func_ovl0D_04_80044310(void) {
    UNK_MACRO_ovl0D_04_80044318();
}

static void func_ovl0D_04_80044308(void) {
    func_ovl0D_04_800466D0(0x424);
}

static void func_ovl0D_04_80044300(Ent_0D04 *e, s32 flag) {
    Vec3f dir;
    Vec3f pos;
    s32 r;

    if (!(e->obj->unk8 & 0x04000000)) {
        D_ovl0D_04_8004705C->unk30 = 1;
        D_ovl0D_04_8004705C->unk34 = 75.0f;
        D_ovl0D_04_8004705C->unk38 = 50.0f;
        dir.x = e->obj->unk40->unk20 + 90.0f;
        dir.y = 0.0f;
        dir.z = 100.0f;
        func_ovl0D_04_800462A0(&dir.x, &pos.x);
        D_ovl0D_04_8004705C->unk40->unk10 = e->obj->unk40->unk10 + pos.x;
        D_ovl0D_04_8004705C->unk40->unk14 = e->obj->unk40->unk14 + pos.y;
        D_ovl0D_04_8004705C->unk40->unk18 = e->obj->unk40->unk18 + pos.z;
        r = func_ovl0D_04_800462B8(D_ovl0D_04_8004705C, 0x40);
        if (r != 0) {
            if ((r & 0x6000) && func_ovl0D_04_800466E0(flag) == 0 &&
                !(e->obj->unk8 & 0x04000000)) {
                func_ovl0D_04_80046308(e->obj, 0x04000000);
                func_ovl0D_04_80046310(e->obj, 0x02000000);
                func_ovl0D_04_80046A00(0x60, D_ovl0D_04_8004705C->unk40->unk10, D_ovl0D_04_8004705C->unk40->unk14, D_ovl0D_04_8004705C->unk40->unk18);
            } else if (func_ovl0D_04_800466E0(flag) == 0) {
                func_ovl0D_04_80046A00(0x26, D_ovl0D_04_8004705C->unk40->unk10, D_ovl0D_04_8004705C->unk40->unk14, D_ovl0D_04_8004705C->unk40->unk18);
            }
        }
    } else if ((e->obj->unk40->unkC & 0x40) && func_ovl0D_04_800466E0(flag) == 0) {
        func_ovl0D_04_80043F24(e);
        func_ovl0D_04_800466D0(flag);
        func_ovl0D_04_800469E0(0x68);
    }
}

/* the tiles under a gate: solid, and the frame around its opening */
static void func_ovl0D_04_80043F24(Ent_0D04 *e) {
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
    Obj40_0D04 *p;

    p = e->obj->unk40;
    func_ovl0D_04_80045960(p->unk10, p->unk14, p->unk18, grid, 0);
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
    dir = func_ovl0D_04_80043F1C(e->obj->unk40->unk20);
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
    func_ovl0D_04_80043EA8(0, D_ovl0D_04_80047068, &x0);
    func_ovl0D_04_80043EA8(1, D_ovl0D_04_80047068, &y0);
    func_ovl0D_04_80043EA8(2, D_ovl0D_04_80047068, &z0);
    func_ovl0D_04_80043EA8(0, D_ovl0D_04_80047068, &x1);
    func_ovl0D_04_80043EA8(1, D_ovl0D_04_80047068, &y1);
    func_ovl0D_04_80043EA8(2, D_ovl0D_04_80047068, &z1);
    func_ovl0D_04_80043EA8(0, D_ovl0D_04_80047068, &x2);
    func_ovl0D_04_80043EA8(2, D_ovl0D_04_80047068, &z2);
    func_ovl0D_04_80043EA8(0, D_ovl0D_04_80047068, &x3);
    func_ovl0D_04_80043EA8(2, D_ovl0D_04_80047068, &z3);
    func_ovl0D_04_80045950(x0, y0, z0, x1, y1, z1, 0x10);
    func_ovl0D_04_80045948(x0, y0 + 1, z0, x1, z1, 0x11);
    func_ovl0D_04_80045948(x0, y0, z0, x1, z1, 0xF);
    func_ovl0D_04_80045948(x2, y0, z2, x3, z3, 0x11);
    func_ovl0D_04_80045948(x2, y0 + 1, z2, x3, z3, 0x10);
}

static void func_ovl0D_04_80043EA8(s32 axis, s32 *size, s32 *v) {
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

void func_ovl0D_04_80043E70(void) {
    func_ovl0D_04_80043C50();
    if (func_ovl0D_04_800466E0(0x421) != 0) {
        func_ovl0D_04_80043700();
    }
}

void func_ovl0D_04_80043DF0(void) {
    if (func_ovl0D_04_80045AD0(0x18, 0x1D, 0x18, 0x1D) != 0 && func_ovl0D_04_800466E0(0x407) == 0) {
        func_ovl0D_04_80043AD8();
    }
    if (func_ovl0D_04_80045AD0(2, 0x13, 2, 0x13) != 0 && func_ovl0D_04_800466E0(0x409) == 0) {
        func_ovl0D_04_800435AC();
    }
}

void func_ovl0D_04_80043C50(void) {
    D_ovl0D_04_80047074 = func_ovl0D_04_800459D8(0x159);
    func_ovl0D_04_80046310(D_ovl0D_04_80046CCC[1].obj, 0x01000000);
    if (func_ovl0D_04_800466E0(0x407) != 0) {
        D_ovl0D_04_80046C24[0].unk18 = 55.0f;
        D_ovl0D_04_80046C24[0].obj->unk40->unk14 = D_ovl0D_04_80046C24[0].unk18 * 10.0f;
        func_ovl0D_04_80046310(D_ovl0D_04_80046C24[2].obj, 0x01000000);
        func_ovl0D_04_80046310(D_ovl0D_04_80046CCC[0].obj, 0x01000000);
        func_ovl0D_04_80046308(D_ovl0D_04_80046CCC[1].obj, 0x01000000);
        D_ovl0D_04_80046CCC[1].unk18 = 55.0f;
        D_ovl0D_04_80046CCC[1].obj->unk40->unk14 = D_ovl0D_04_80046CCC[1].unk18 * 10.0f;
        func_ovl0D_04_800436BC(D_ovl0D_04_80046DB0[0].obj);
        func_ovl0D_04_800436BC(D_ovl0D_04_80046E20[0].obj);
        func_ovl0D_04_800459E0(D_ovl0D_04_80047074, 0, 0, D_ovl0D_04_80047068[0] - 1, D_ovl0D_04_80047068[2] - 1, 0, 2, 0);
        func_ovl0D_04_800433F0(&D_ovl0D_04_80046E20[0]);
        func_ovl0D_04_80043A8C();
        if (func_ovl0D_04_80045A08() == 26) {
            func_ovl0D_04_80046270();
        }
        func_ovl0D_04_80046238(&D_ovl0D_04_80047020);
    }
}

void func_ovl0D_04_80043AD8(void) {
    func_ovl0D_04_80043AD0();
    func_ovl0D_04_80043478(2200.0f, 900.0f, 3000.0f, 0.0f, 0xC0);
    func_ovl0D_04_800469E0(0x69);
    func_ovl0D_04_80046030(D_ovl0D_04_80046DB0[0].obj->unk40, 0, 0);
    func_ovl0D_04_80046308(D_ovl0D_04_80046DB0[0].obj, 0x04000000);
    func_ovl0D_04_80046308(D_ovl0D_04_80046E20[0].obj, 0x04000000);
    func_ovl0D_04_80046308(D_ovl0D_04_80046C24[0].obj, 0x04000000);
    func_ovl0D_04_80046030(D_ovl0D_04_80046CCC[0].obj->unk40, 1, 0);
    func_ovl0D_04_80046308(D_ovl0D_04_80046CCC[0].obj, 0x04000000);
    func_ovl0D_04_80046030(D_ovl0D_04_80046CCC[1].obj->unk40, 1, 0);
    func_ovl0D_04_80046308(D_ovl0D_04_80046CCC[1].obj, 0x04000000);
    func_ovl0D_04_800459E0(D_ovl0D_04_80047074, 0, 0, D_ovl0D_04_80047068[0] - 1, D_ovl0D_04_80047068[2] - 1, 0, 2, 0);
    func_ovl0D_04_800433F0(&D_ovl0D_04_80046E20[0]);
    func_ovl0D_04_80043A8C();
    func_ovl0D_04_800466D0(0x407);
    func_ovl0D_04_80043338(0x3B, 0x1A);
}

void func_ovl0D_04_80043A8C(void) {
    func_ovl0D_04_80045950(0x12, 1, 0x1D, 0x17, 2, 0x1D, 0x1F);
}

static void func_ovl0D_04_80043AD0(void) {
}

void func_ovl0D_04_80043700(void) {
    Ent_0D04 *e;

    D_ovl0D_04_80046C24[0].unk18 = 55.0f;
    D_ovl0D_04_80046C24[0].obj->unk40->unk14 = D_ovl0D_04_80046C24[0].unk18 * 10.0f;
    D_ovl0D_04_80046C24[1].unk18 = 20.0f;
    D_ovl0D_04_80046C24[1].obj->unk40->unk14 = D_ovl0D_04_80046C24[1].unk18 * 10.0f;
    D_ovl0D_04_80046C24[2].unk18 = -120.0f;
    D_ovl0D_04_80046C24[2].obj->unk40->unk14 = D_ovl0D_04_80046C24[2].unk18 * 10.0f;
    func_ovl0D_04_80046308(D_ovl0D_04_80046C24[2].obj, 0x01000000);
    func_ovl0D_04_80046308(D_ovl0D_04_80046CCC[0].obj, 0x01000000);
    D_ovl0D_04_80046CCC[0].unk14 = 170.0f;
    D_ovl0D_04_80046CCC[0].obj->unk40->unk10 = 170.0f * 10.0f;
    D_ovl0D_04_80046CCC[0].unk18 = 20.0f;
    D_ovl0D_04_80046CCC[0].obj->unk40->unk14 = 20.0f * 10.0f;
    D_ovl0D_04_80046CCC[0].unk1C = 10.0f;
    D_ovl0D_04_80046CCC[0].obj->unk40->unk18 = 10.0f * 10.0f;
    D_ovl0D_04_80046CCC[0].obj->unk40->unk20 = 180.0f;
    e = &D_ovl0D_04_80046CCC[1];
    func_ovl0D_04_80046308(e->obj, 0x01000000);
    e->unk14 = 10.0f;
    e->obj->unk40->unk10 = 10.0f * 10.0f;
    e->unk18 = 20.0f;
    e->obj->unk40->unk14 = 20.0f * 10.0f;
    e->unk1C = 200.0f;
    e->obj->unk40->unk18 = 200.0f * 10.0f;
    e->obj->unk40->unk20 = 270.0f;
    e++;
    func_ovl0D_04_80046308(e->obj, 0x01000000);
    e->unk14 = -110.0f;
    e->obj->unk40->unk10 = -110.0f * 10.0f;
    e->unk18 = -120.0f;
    e->obj->unk40->unk14 = -120.0f * 10.0f;
    e->unk1C = 390.0f;
    e->obj->unk40->unk18 = 390.0f * 10.0f;
    e->obj->unk40->unk20 = 0.0f;
    func_ovl0D_04_800436BC(D_ovl0D_04_80046DB0[0].obj);
    func_ovl0D_04_800436BC(D_ovl0D_04_80046E20[0].obj);
    if (func_ovl0D_04_800466E0(0x409) != 0) {
        D_ovl0D_04_80046C24[1].unk18 = 40.0f;
        D_ovl0D_04_80046C24[1].obj->unk40->unk14 = D_ovl0D_04_80046C24[1].unk18 * 10.0f;
        func_ovl0D_04_80046310(D_ovl0D_04_80046C24[2].obj, 0x01000000);
        D_ovl0D_04_80046CCC[0].unk18 = 40.0f;
        D_ovl0D_04_80046CCC[0].obj->unk40->unk14 = D_ovl0D_04_80046CCC[0].unk18 * 10.0f;
        func_ovl0D_04_80046310(D_ovl0D_04_80046CCC[1].obj, 0x01000000);
        func_ovl0D_04_80046310(D_ovl0D_04_80046CCC[2].obj, 0x01000000);
        func_ovl0D_04_80046030(D_ovl0D_04_80046DB0[1].obj->unk40, 0, 0);
        func_ovl0D_04_800436BC(D_ovl0D_04_80046DB0[1].obj);
        func_ovl0D_04_800436BC(D_ovl0D_04_80046E20[1].obj);
        func_ovl0D_04_800433F0(&D_ovl0D_04_80046E20[1]);
        func_ovl0D_04_800433AC();
        if (func_ovl0D_04_80045A08() == 27) {
            func_ovl0D_04_80046270();
        }
        func_ovl0D_04_80046238(&D_ovl0D_04_80047020);
    }
}

static void func_ovl0D_04_800436BC(Obj_0D04 *o) {
    o->unk40->unk48->unk4->unk4 = func_ovl0D_04_80046048(o->unk40, 0) - 0.001f;
}

/* a gate opening: the camera goes to it and the tiles are freed */
void func_ovl0D_04_80043478(f32 x, f32 y, f32 z, f32 ang, s32 arg4) {
    func_ovl0D_04_80045A70(0);
    func_ovl0D_04_80045AF8(1);
    func_ovl0D_04_800461B0(0xF);
    if (func_ovl0D_04_80046198() == 1) {
        func_ovl0D_04_800461A0();
    }
    func_ovl0D_04_80045BB8();
    func_ovl0D_04_800468E8();
    func_ovl0D_04_800469C8();
    func_ovl0D_04_80046478(60);
    func_ovl0D_04_80045B20(1);
    func_ovl0D_04_800469E0(0x29);
    func_ovl0D_04_80045A78(1);
    func_ovl0D_04_80045B30(0x40);
    func_ovl0D_04_80045B08(arg4, 6, 8.5f, 0, 1, 1, 0);
    func_ovl0D_04_80045AF8(1);
    func_ovl0D_04_80046478(30);
    func_ovl0D_04_80046268();
    func_ovl0D_04_800461B0(0x7F);
    func_ovl0D_04_80046148(x, y, z);
    func_ovl0D_04_80046168(ang, 45.0f, 32768.0f);
    func_ovl0D_04_800461C0(0);
    func_ovl0D_04_80046478(15);
    func_ovl0D_04_800469E0(0x69);
    func_ovl0D_04_80046478(15);
    func_ovl0D_04_800469E0(0x6F);
}

void func_ovl0D_04_800435AC(void) {
    func_ovl0D_04_80043478(200.0f, 700.0f, 2200.0f, 270.0f, 0x80);
    func_ovl0D_04_800469E0(0x69);
    func_ovl0D_04_80046030(D_ovl0D_04_80046DB0[1].obj->unk40, 0, 0);
    func_ovl0D_04_80046308(D_ovl0D_04_80046DB0[1].obj, 0x04000000);
    func_ovl0D_04_80046308(D_ovl0D_04_80046E20[1].obj, 0x04000000);
    func_ovl0D_04_80046308(D_ovl0D_04_80046C24[1].obj, 0x04000000);
    func_ovl0D_04_80046030(D_ovl0D_04_80046CCC[1].obj->unk40, 2, 0);
    func_ovl0D_04_80046308(D_ovl0D_04_80046CCC[1].obj, 0x04000000);
    func_ovl0D_04_800433F0(&D_ovl0D_04_80046E20[1]);
    func_ovl0D_04_800433AC();
    func_ovl0D_04_800466D0(0x409);
    func_ovl0D_04_80043338(0x3B, 0x1B);
}

static void func_ovl0D_04_800433F0(Ent_0D04 *e) {
    s32 pos[6];
    Obj40_0D04 *p;

    p = e->obj->unk40;
    func_ovl0D_04_80045960(p->unk10, p->unk14, p->unk18, pos, 0);
    func_ovl0D_04_80045948(pos[0], pos[1], pos[2], pos[0], pos[2], 0x11);
    func_ovl0D_04_80045948(pos[0], pos[1] + 1, pos[2], pos[0], pos[2], 0x10);
}

void func_ovl0D_04_800433AC(void) {
    func_ovl0D_04_80045950(2, 0, 0x14, 2, 1, 0x19, 0x1F);
}

void func_ovl0D_04_80043338(s32 arg0, s32 arg1) {
    func_ovl0D_04_80045B08(0x200, 5, 1.1111f, 1, 0, 0, 0);
    func_ovl0D_04_80045AF8(1);
    func_ovl0D_04_80046478(30);
    func_ovl0D_04_80046748(2);
    func_ovl0D_04_80046750();
    func_ovl0D_04_80045A00(arg0, arg1, 1);
}

void func_ovl0D_04_80043190(void) {
    s32 n;

    func_ovl0D_04_80043010(D_ovl0D_04_80046E98);
    func_ovl0D_04_80046310(D_ovl0D_04_80046E98[0].obj, 0x80000);
    n = 0;
    if (func_ovl0D_04_800466E0(0x413) != 0) {
        n = 1;
    }
    if (func_ovl0D_04_800466E0(0x414) != 0) {
        n++;
    }
    if (func_ovl0D_04_800466E0(0x415) != 0) {
        n++;
    }
    if (n == 3) {
        D_ovl0D_04_80046ED0[0].unk8 = 0x152;
        D_ovl0D_04_80046ED0[0].unkC = 0x20;
        D_ovl0D_04_80046ED0[0].unk10 = 0;
    }
    func_ovl0D_04_80043010(D_ovl0D_04_80046ED0);
    D_ovl0D_04_80046ED0[0].obj->unk40->unk36 = 0x7F;
    switch (n) {
        case 0:
            break;
        case 1:
        case 2:
            D_ovl0D_04_80046E98[0].obj->unk40->unk18 -= n * 100.0f;
            D_ovl0D_04_80046E98[0].obj->unk40->unk48->unk4->unk4 = 0.0f;
            break;
        case 3:
            D_ovl0D_04_80046E98[0].obj->unk40->unk18 -= 500.0f;
            D_ovl0D_04_80046E98[0].obj->unk40->unk48->unk4->unk4 = 0.0f;
            break;
    }
}

static void func_ovl0D_04_80043010(Ent_0D04 *arg0) {
    arg0->obj = func_ovl0D_04_80046350(arg0->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0D_04_80046308(arg0->obj, 0x01080000);
    func_ovl0D_04_80046310(arg0->obj, 0x02000000);
    if (arg0->unkC != -1 && arg0->unkE != -1 && arg0->unk10 != -1 && arg0->unk12 != -1) {
        arg0->unk4 = func_ovl0D_04_80046050(arg0->obj->unk40, 0, arg0->unkC, arg0->unkE, arg0->unk10, arg0->unk12);
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
