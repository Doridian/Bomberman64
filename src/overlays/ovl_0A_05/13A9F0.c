#include "common.h"

/*
 * ovl_0A_05's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).  Statics
 * inlined into every caller leave a `jr ra; nop` stub just before their first
 * caller; the unused ones at the end of the object leave one each.
 *
 * The four window slides (func_ovl0A_05_800438A0, 80043EE8, 800442DC and
 * 800446AC) clamp inside the stopping test's `if`, put the curve's start in
 * x and copy it to cx only after the steps are worked out: that gives the
 * original's registers and its block order.  In func_ovl0A_05_80046A1C the
 * three stored 0.0s are double literals, so each is materialized on its own
 * rather than taken from the register holding `zero`.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStruct_ovl0A_05_Anim2;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_ovl0A_05_Anim2 *unk4;
} UnkStruct_ovl0A_05_Anim;

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
    /* 0x48 */ UnkStruct_ovl0A_05_Anim *unk48;
} UnkStruct_ovl0A_05_80048CA0_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x1C];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[0x14];
    /* 0x40 */ UnkStruct_ovl0A_05_80048CA0_Inner *unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 unk48[4];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ u8 unk60[8];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} UnkStruct_ovl0A_05_80048CA0;

typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x1C];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
} UnkStruct_ovl0A_05_80048E50;

/* what ZeroJump 0x1500 returns: a screen rectangle with its size */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
} UnkStruct_ovl0A_05_80048958;

/* what ZeroJump 0x3100 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
} UnkStruct_ovl0A_05_800494E8;

/* what ZeroJump 0x3106 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ UnkStruct_ovl0A_05_80048958 *unkC;
} UnkStruct_ovl0A_05_80049518;

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0A_05_B04_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl0A_05_B04_Inner *unk40;
} UnkStruct_ovl0A_05_B04;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl0A_05;

void func_ovl0A_05_80047F30(const char *); /* 0x100 */
void func_ovl0A_05_80048290(s32); /* 0xD00 */
void func_ovl0A_05_80048370(s32, s32, s32); /* 0xF00 */
s32 func_ovl0A_05_80048378(void); /* 0xF01 */
void func_ovl0A_05_800483E0(s32); /* 0xF0E */
void func_ovl0A_05_80048418(s32); /* 0xF15 */
void func_ovl0A_05_80048428(void); /* 0x1000 */
void func_ovl0A_05_80048430(s32, s32, s32); /* 0x1001 */
void func_ovl0A_05_80048438(void *); /* 0x1002 */
s32 func_ovl0A_05_80048458(void); /* 0x1006 */
void func_ovl0A_05_80048460(s32, void *); /* 0x1007 */
void func_ovl0A_05_80048468(s32); /* 0x1008 */
void func_ovl0A_05_80048480(const char *); /* 0x100B */
void func_ovl0A_05_80048488(void); /* 0x100C */
UnkStruct_ovl0A_05_80048CA0 *func_ovl0A_05_800484B8(s32); /* 0x1012 */
void func_ovl0A_05_80048508(s32, s32); /* 0x101C */
UnkStruct_ovl0A_05_80048958 *func_ovl0A_05_80048958(s32, s32); /* 0x1500 */
void func_ovl0A_05_80048960(UnkStruct_ovl0A_05_80048958 *); /* 0x1501 */
void func_ovl0A_05_80048970(UnkStruct_ovl0A_05_80048CA0_Inner *, s32); /* 0x1503 */
void func_ovl0A_05_80048998(UnkStruct_ovl0A_05_80048CA0_Inner *, s32); /* 0x1508 */
void func_ovl0A_05_800489A0(UnkStruct_ovl0A_05_80048CA0_Inner *, s32, s32); /* 0x1509 */
f32 func_ovl0A_05_800489B8(UnkStruct_ovl0A_05_80048CA0_Inner *, s32); /* 0x150C */
void func_ovl0A_05_80048AA8(s32); /* 0x1702 */
void func_ovl0A_05_80048AB8(f32, f32, f32); /* 0x1704 */
void func_ovl0A_05_80048AC8(f32, f32, f32); /* 0x1706 */
void func_ovl0A_05_80048AD8(f32, f32, f32); /* 0x1708 */
void func_ovl0A_05_80048AE0(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0A_05_80048AF0(u32 *, s32, s32); /* 0x170B */
void func_ovl0A_05_80048B18(s32); /* 0x1710 */
void func_ovl0A_05_80048B20(s32); /* 0x1711 */
void func_ovl0A_05_80048B30(s32); /* 0x1713 */
void func_ovl0A_05_80048B50(f32); /* 0x1717 */
void func_ovl0A_05_80048B58(f32 *); /* 0x1718 */
void func_ovl0A_05_80048B68(f32, f32, f32, f32); /* 0x171A */
void func_ovl0A_05_80048B70(f32, f32); /* 0x171B */
void func_ovl0A_05_80048B78(f32, f32, f32, f32); /* 0x171C */
void func_ovl0A_05_80048B80(UnkStruct_ovl0A_05_80048CA0 *); /* 0x171D */
void func_ovl0A_05_80048BC0(f32 *); /* 0x1725 */
void func_ovl0A_05_80048C08(f32 *, f32 *, f32 *); /* 0x1803 */
void func_ovl0A_05_80048C50(UnkStruct_ovl0A_05_80048CA0 *); /* 0x180C */
void func_ovl0A_05_80048C58(UnkStruct_ovl0A_05_80048CA0 *, UnkStruct_ovl0A_05_80048CA0 *); /* 0x180D */
void func_ovl0A_05_80048C78(UnkStruct_ovl0A_05_80048CA0 *, s32); /* 0x1811 */
void func_ovl0A_05_80048C80(UnkStruct_ovl0A_05_80048CA0 *, s32); /* 0x1812 */
void func_ovl0A_05_80048C90(UnkStruct_ovl0A_05_80048CA0 *); /* 0x1814 */
UnkStruct_ovl0A_05_80048CA0 *func_ovl0A_05_80048CA0(s32, s32, s32, UnkStruct_ovl0A_05_80048CA0 *); /* 0x1816 */
void func_ovl0A_05_80048D48(UnkStruct_ovl0A_05_80048CA0 *, f32 *); /* 0x182B */
void func_ovl0A_05_80048D50(UnkStruct_ovl0A_05_80048CA0 *, UnkStruct_ovl0A_05_80048CA0 *); /* 0x182C */
UnkStruct_ovl0A_05_80048CA0 *func_ovl0A_05_80048D80(s32, Vec3f_ovl0A_05 *, Vec3f_ovl0A_05 *); /* 0x1832 */
s32 func_ovl0A_05_80048DC8(void (*)(), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0A_05_80048DD8(void); /* 0x1902 */
void func_ovl0A_05_80048DE8(s32); /* 0x1904 */
UnkStruct_ovl0A_05_80048CA0 *func_ovl0A_05_80048DF0(void); /* 0x1905 */
s32 func_ovl0A_05_80048E10(void); /* 0x1909 */
UnkStruct_ovl0A_05_80048E50 *func_ovl0A_05_80048E50(s32); /* 0x1A00 */
void func_ovl0A_05_80048E60(UnkStruct_ovl0A_05_80048E50 *, s32); /* 0x1A02 */
f32 func_ovl0A_05_80048F70(f32); /* 0x1D00 */
void func_ovl0A_05_80049040(s32); /* 0x1E06 */
void func_ovl0A_05_80049048(s32); /* 0x1E07 */
s32 func_ovl0A_05_80049050(s32); /* 0x1E08 */
void func_ovl0A_05_800490A8(s32); /* 0x2000 */
void func_ovl0A_05_800490C8(s32, s32, s32, f32); /* 0x2004 */
void func_ovl0A_05_80049108(s32, s32, s32, s32, s32); /* 0x2104 */
void func_ovl0A_05_80049120(s32); /* 0x2202 */
void func_ovl0A_05_80049128(s32); /* 0x2203 */
void func_ovl0A_05_80049220(s32, f32 *, s32); /* 0x2601 */
void func_ovl0A_05_80049240(UnkStruct_ovl0A_05_80048CA0 *); /* 0x2701 */
void func_ovl0A_05_80049360(s32); /* 0x2B02 */
void func_ovl0A_05_80049370(s32, s32, s32, s32); /* 0x2B04 */
UnkStruct_ovl0A_05_800494E8 *func_ovl0A_05_800494E8(void); /* 0x3100 */
void func_ovl0A_05_800494F0(UnkStruct_ovl0A_05_800494E8 *); /* 0x3101 */
void func_ovl0A_05_80049508(void); /* 0x3104 */
UnkStruct_ovl0A_05_80049518 *func_ovl0A_05_80049518(s32); /* 0x3106 */
void func_ovl0A_05_80049530(void); /* 0x3109 */
void func_ovl0A_05_80049538(void); /* 0x310A */
void func_ovl0A_05_80049540(void); /* 0x310B */
void func_ovl0A_05_80049548(void); /* 0x310C */

/* .bss */
Vec3f_ovl0A_05 D_ovl0A_05_800498D0;
u8 D_ovl0A_05_800498DC[4];
Vec3f_ovl0A_05 D_ovl0A_05_800498E0;
s32 D_ovl0A_05_800498EC;
u8 D_ovl0A_05_800498F0[4];
s32 D_ovl0A_05_800498F4;
s32 D_ovl0A_05_800498F8;
u8 D_ovl0A_05_800498FC[4];
Vec3f_ovl0A_05 D_ovl0A_05_80049900;
UnkStruct_ovl0A_05_80048958 *D_ovl0A_05_8004990C;
UnkStruct_ovl0A_05_80048958 *D_ovl0A_05_80049910;
UnkStruct_ovl0A_05_80048958 *D_ovl0A_05_80049914;
UnkStruct_ovl0A_05_80048958 *D_ovl0A_05_80049918;
UnkStruct_ovl0A_05_80048E50 *D_ovl0A_05_8004991C;
s32 D_ovl0A_05_80049920;
UnkStruct_ovl0A_05_80048CA0 *D_ovl0A_05_80049924;
UnkStruct_ovl0A_05_80048E50 *D_ovl0A_05_80049928;
u8 D_ovl0A_05_8004992C[4];
UnkStruct_ovl0A_05_80049518 *D_ovl0A_05_80049930[4];
UnkStruct_ovl0A_05_80048CA0 *D_ovl0A_05_80049940;
UnkStruct_ovl0A_05_80048CA0 *D_ovl0A_05_80049944;
UnkStruct_ovl0A_05_80048CA0 *D_ovl0A_05_80049948;
UnkStruct_ovl0A_05_80048CA0 *D_ovl0A_05_8004994C;
UnkStruct_ovl0A_05_80048CA0 *D_ovl0A_05_80049950[4];
UnkStruct_ovl0A_05_800494E8 *D_ovl0A_05_80049960;
UnkStruct_ovl0A_05_80048CA0 *D_ovl0A_05_80049964;
UnkStruct_ovl0A_05_80048CA0 *D_ovl0A_05_80049968;
u8 D_ovl0A_05_8004996C[4];
Vec3f_ovl0A_05 D_ovl0A_05_80049970;
u8 D_ovl0A_05_8004997C[4];

/* .data */
Vec3f_ovl0A_05 D_ovl0A_05_80049570 = { 5000.0f, 5000.0f, 5000.0f };
f32 D_ovl0A_05_8004957C[4] = { 1.0f, -1.0f, 1.0f, -1.0f };
f32 D_ovl0A_05_8004958C[4] = { 1.0f, -1.0f, -1.0f, 1.0f };
f32 D_ovl0A_05_8004959C[4][6] = {
    { 280.0f, 0.0f, 0.0f, -70.0f, 0.0f, 0.0f },
    { 0.0f, -250.0f, 0.0f, 0.0f, 18.75f, 0.0f },
    { -280.0f, 0.0f, 0.0f, 70.0f, 0.0f, 0.0f },
    { 0.0f, 250.0f, 100.0f, 0.0f, 0.0f, 100.0f },
};
f32 D_ovl0A_05_800495FC[5] = { 153.0f, 0.0f, 0.0f, 255.0f, 255.0f };
f32 D_ovl0A_05_80049610[5] = { 0.0f, 153.0f, 0.0f, 255.0f, 255.0f };
f32 D_ovl0A_05_80049624[5] = { 0.0f, 0.0f, 153.0f, 255.0f, 255.0f };
f32 D_ovl0A_05_80049638[5][8] = {
    { 0.0f, 72.0f, 0.0f, 144.0f, 0.0f, 72.0f, 320.0f, 144.0f },
    { 128.0f, 0.0f, 192.0f, 0.0f, 128.0f, 0.0f, 192.0f, 240.0f },
    { 320.0f, 72.0f, 320.0f, 144.0f, 0.0f, 72.0f, 320.0f, 144.0f },
    { 153.59999f, 240.0f, 166.4f, 240.0f, 153.59999f, 0.0f, 166.4f, 240.0f },
    { 153.59999f, 0.0f, 166.4f, 240.0f, 0.0f, 0.0f, 320.0f, 240.0f },
};
u32 D_ovl0A_05_800496D8[18] = {
    180, 1, 1, 0, 0, 0, 0, 0, 0, 0x40400000, 0xBF1C71C7, 0xC131C71C, 0xBC888889, 0x3B5E7FAF, 0x3D7CD6E9, 0, 0, 0,
};

void func_ovl0A_05_80043150(void);
void func_ovl0A_05_8004333C(void);
void func_ovl0A_05_800438A0(void);
void func_ovl0A_05_80043EE8(void);
void func_ovl0A_05_800442DC(void);
void func_ovl0A_05_800446AC(void);
void func_ovl0A_05_80044984(void);
void func_ovl0A_05_800450B4(void);
void func_ovl0A_05_80045310(void);
void func_ovl0A_05_80045350(void);
void func_ovl0A_05_800459C8(void);
void func_ovl0A_05_800461C8(void);
void func_ovl0A_05_80046248(void);
void func_ovl0A_05_80046400(void);
void func_ovl0A_05_80046558(void);
void func_ovl0A_05_800467FC(void);
void func_ovl0A_05_8004704C(void);

void func_ovl0A_05_80043010(void);
void func_ovl0A_05_80043068(void);
void func_ovl0A_05_800430D0(void);
static void func_ovl0A_05_80044BC4(UnkStruct_ovl0A_05_80048CA0 *obj);
void func_ovl0A_05_80044D28(void);
void func_ovl0A_05_80044C08(void);
void func_ovl0A_05_80044F80(void);
void func_ovl0A_05_80044FD0(void);
void func_ovl0A_05_80045568(void);
void func_ovl0A_05_8004571C(void);
void func_ovl0A_05_800458BC(void);
void func_ovl0A_05_800458DC(UnkStruct_ovl0A_05_80048CA0 *obj, f32 *from, f32 *to);
void func_ovl0A_05_8004599C(void);
static void func_ovl0A_05_80045C00(UnkStruct_ovl0A_05_80048CA0 *obj);
void func_ovl0A_05_80045C58(void);
void func_ovl0A_05_80045D90(void);
void func_ovl0A_05_80045E38(void);
void func_ovl0A_05_80045E58(void);
void func_ovl0A_05_80045EF0(void);
void func_ovl0A_05_800460C8(void);
static void func_ovl0A_05_800461C0(void);
void func_ovl0A_05_800469EC(void);
void func_ovl0A_05_80046A1C(void);
void func_ovl0A_05_80046DFC(void);
void func_ovl0A_05_8004702C(void);
void func_ovl0A_05_800473A0(void);
void func_ovl0A_05_800474B0(void);
void func_ovl0A_05_800475E8(void);
void func_ovl0A_05_80047608(void);
void func_ovl0A_05_800478B0(void);
void func_ovl0A_05_8004794C(void);
static void func_ovl0A_05_80047A88(void);
void func_ovl0A_05_80047A90(void);
static void func_ovl0A_05_80047AB0(void);
static void func_ovl0A_05_80047AB8(void);
void func_ovl0A_05_80047AC0(void);
void func_ovl0A_05_80047AF4(s32 arg0);
void func_ovl0A_05_80047BE0(void);
void func_ovl0A_05_80047DF4(s32 arg0, UnkStruct_ovl0A_05_B04 *arg1);
void func_ovl0A_05_80047E28(f32 arg0);
void func_ovl0A_05_80047E70(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_05_80047ECC(void);
void func_ovl0A_05_80047EE4(void);
static void func_ovl0A_05_80047EEC(void);
static void func_ovl0A_05_80047EF4(void);
static void func_ovl0A_05_80047EFC(void);
static void func_ovl0A_05_80047F04(void);
static void func_ovl0A_05_80047F0C(void);
static void func_ovl0A_05_80047F14(void);
static void func_ovl0A_05_80047F1C(void);
static void func_ovl0A_05_80047F24(void);

static void func_ovl0A_05_80047F24(void) {
}

static void func_ovl0A_05_80047F1C(void) {
}

static void func_ovl0A_05_80047F14(void) {
}

static void func_ovl0A_05_80047F0C(void) {
}

static void func_ovl0A_05_80047F04(void) {
}

static void func_ovl0A_05_80047EFC(void) {
}

static void func_ovl0A_05_80047EF4(void) {
}

/* Unused: IDO -O3 drops their bodies and leaves a `jr ra` each; they
 * stand for whatever referenced the .bss the code doesn't (or it
 * becomes common). */
static void func_ovl0A_05_80047EEC(void) {
    D_ovl0A_05_800498DC[0] = 0;
    D_ovl0A_05_800498F0[0] = 0;
    D_ovl0A_05_800498FC[0] = 0;
    D_ovl0A_05_8004992C[0] = 0;
    D_ovl0A_05_8004996C[0] = 0;
    D_ovl0A_05_8004997C[0] = 0;
}

void func_ovl0A_05_80047EE4(void) {
}

void func_ovl0A_05_80047ECC(void) {
    D_ovl0A_05_800498F4 = -1;
    D_ovl0A_05_800498F8 = -1;
}

void func_ovl0A_05_80047E70(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0A_05_80048AB8(D_ovl0A_05_80049900.x, D_ovl0A_05_80049900.y, D_ovl0A_05_80049900.z);
    func_ovl0A_05_80048AD8(arg0, arg1, arg2);
    func_ovl0A_05_80048DE8(0xB4);
}

void func_ovl0A_05_80047E28(f32 arg0) {
    f32 sp1C;

    func_ovl0A_05_80048AE0(&sp1C, NULL, NULL);
    func_ovl0A_05_80048AD8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0A_05_80047DF4(s32 arg0, UnkStruct_ovl0A_05_B04 *arg1) {
    UnkStruct_ovl0A_05_B04_Inner *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01's func_ovl09_01_800431C8 */
    }
    func_ovl0A_05_80049370(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0A_05_80047BE0(void) {
    D_ovl0A_05_8004990C->unk10 = 71.0f;
    D_ovl0A_05_8004990C->unk14 = 13.0f;
    D_ovl0A_05_8004990C->unk18 = D_ovl0A_05_8004990C->unk10 + D_ovl0A_05_8004990C->unk28;
    D_ovl0A_05_8004990C->unk1C = D_ovl0A_05_8004990C->unk14 + D_ovl0A_05_8004990C->unk2C;
    D_ovl0A_05_8004990C->unkC &= ~1;
    D_ovl0A_05_80049910->unk10 = 29.0f;
    D_ovl0A_05_80049910->unk14 = 78.0f;
    D_ovl0A_05_80049910->unk18 = D_ovl0A_05_80049910->unk10 + D_ovl0A_05_80049910->unk28;
    D_ovl0A_05_80049910->unk1C = D_ovl0A_05_80049910->unk14 + D_ovl0A_05_80049910->unk2C;
    D_ovl0A_05_80049910->unkC &= ~1;
    D_ovl0A_05_80049914->unk10 = 127.0f;
    D_ovl0A_05_80049914->unk14 = 54.0f;
    D_ovl0A_05_80049914->unk18 = D_ovl0A_05_80049914->unk10 + D_ovl0A_05_80049914->unk28;
    D_ovl0A_05_80049914->unk1C = D_ovl0A_05_80049914->unk14 + D_ovl0A_05_80049914->unk2C;
    D_ovl0A_05_80049914->unkC &= ~1;
    D_ovl0A_05_80049918->unk10 = 164.0f;
    D_ovl0A_05_80049918->unk14 = 88.0f;
    D_ovl0A_05_80049918->unk18 = D_ovl0A_05_80049918->unk10 + D_ovl0A_05_80049918->unk28;
    D_ovl0A_05_80049918->unk1C = D_ovl0A_05_80049918->unk14 + D_ovl0A_05_80049918->unk2C;
    D_ovl0A_05_80049918->unkC &= ~1;
    func_ovl0A_05_80048E60(D_ovl0A_05_8004991C, 0x20000000);
    D_ovl0A_05_8004991C->unk18 = 0.0625f;
    D_ovl0A_05_8004991C->unk1C = 0.0f;
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0A_05_80047AF4(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0A_05_80047AC0();
            break;
        case 16:
            func_ovl0A_05_800478B0();
            break;
        case 17:
            func_ovl0A_05_800474B0();
            break;
        case 18:
            func_ovl0A_05_80046DFC();
            break;
        case 19:
            func_ovl0A_05_800460C8();
            break;
        case 20:
            func_ovl0A_05_80045D90();
            break;
        case 21:
            func_ovl0A_05_8004571C();
            break;
        case 22:
            func_ovl0A_05_80044D28();
            break;
        case 3:
            func_ovl0A_05_80047A90();
            break;
        case 1:
            func_ovl0A_05_8004794C();
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            break;
    }
}

void func_ovl0A_05_80047AC0(void) {
    func_ovl0A_05_80047AB0();
    func_ovl0A_05_80047AB8();
    func_ovl0A_05_80049048(0x400);
    func_ovl0A_05_80049048(0x401);
    D_ovl0A_05_80049920 = func_ovl0A_05_80048378();
}

static void func_ovl0A_05_80047AB8(void) {
}

static void func_ovl0A_05_80047AB0(void) {
}

void func_ovl0A_05_80047A90(void) {
    func_ovl0A_05_80047A88();
}

static void func_ovl0A_05_80047A88(void) {
    func_ovl0A_05_80049040(0x400);
}

void func_ovl0A_05_8004794C(void) {
    switch (D_ovl0A_05_80049920) {
        case 16:
            func_ovl0A_05_800475E8();
            break;
        case 17:
            func_ovl0A_05_8004702C();
            break;
        case 18:
            func_ovl0A_05_800469EC();
            break;
        case 19:
            func_ovl0A_05_80045E38();
            break;
        case 20:
            func_ovl0A_05_800458BC();
            break;
        case 21:
            func_ovl0A_05_80044F80();
            break;
        case 22:
            func_ovl0A_05_80043068();
            break;
    }
}

void func_ovl0A_05_800478B0(void) {
    func_ovl0A_05_80048DC8(func_ovl0A_05_80047608, NULL, 0, 0, 0x150);
    func_ovl0A_05_80045568();
    func_ovl0A_05_80048290(0x2E3);
    func_ovl0A_05_80048428();
    func_ovl0A_05_80048430(0x17, 0, 5);
    func_ovl0A_05_80048B20(0x7F);
    func_ovl0A_05_80048B30(1);
    func_ovl0A_05_80048AB8(2300.0f, 0.0f, 1000.0f);
    func_ovl0A_05_80048AD8(0.0f, 15.0f, 1500.0f);
}

void func_ovl0A_05_80047608(void) {
    UnkStruct_ovl0A_05_80048CA0 *obj;
    s32 played;
    s32 i;
    Vec3f_ovl0A_05 scale;
    f32 pos[3];
    f32 dst[3];
    f32 dx;
    f32 dy;
    f32 dz;

    scale = D_ovl0A_05_80049570;
    func_ovl0A_05_80048468(1);
    while (!func_ovl0A_05_80049050(0x400)) {
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048468(1);
    func_ovl0A_05_800483E0(0);
    func_ovl0A_05_80048480("WM1 WAP WG1 WSH WDS WB4 ST1 M1 ST10");
    func_ovl0A_05_800461C0();
    obj = func_ovl0A_05_80048D80(2, &D_ovl0A_05_800498D0, &scale);
    func_ovl0A_05_80048DE8(10);
    func_ovl0A_05_80049360(0x1A);
    func_ovl0A_05_80048480("M2");
    func_ovl0A_05_80048DE8(12);
    func_ovl0A_05_80048D48(obj, pos);
    func_ovl0A_05_80049240(obj);
    obj = func_ovl0A_05_80048CA0(0, 0x01000000, 0xD0, NULL);
    func_ovl0A_05_80048D50(pos, obj);
    func_ovl0A_05_80048E10();
    func_ovl0A_05_80048BC0(dst);
    dst[1] -= 60.0f;
    dx = (dst[0] - pos[0]) / 120.0f;
    dy = (dst[1] - pos[1]) / 120.0f;
    dz = (dst[2] - pos[2]) / 120.0f;
    played = 0;
    for (i = 0; i < 120; i++) {
        obj->unk40->unk10 += dx;
        obj->unk40->unk14 += dy;
        obj->unk40->unk18 += dz;
        if (played == 0 && i > 54.0) {
            played = 1;
            func_ovl0A_05_80048418(0x20);
            func_ovl0A_05_80049530();
        }
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048DE8(30);
    func_ovl0A_05_80048C90(obj);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_800475E8(void) {
    func_ovl0A_05_80049538();
}

void func_ovl0A_05_800474B0(void) {
    s32 i;

    func_ovl0A_05_80048DC8(func_ovl0A_05_800473A0, NULL, 0, 0, 0x150);
    func_ovl0A_05_80048B20(0x10);
    func_ovl0A_05_80048AB8(0.0f, 0.0f, 0.0f);
    func_ovl0A_05_80048AD8(0.0f, 0.0f, 1000.0f);
    for (i = 0; i < 4; i++) {
        D_ovl0A_05_80049930[i] = func_ovl0A_05_80049518(i);
        D_ovl0A_05_80049930[i]->unkC->unkC &= ~1;
        D_ovl0A_05_80049930[i]->unkC->unk10 = 0.0f;
        D_ovl0A_05_80049930[i]->unkC->unk14 = -8.92f;
        D_ovl0A_05_80049930[i]->unkC->unk18 = 573.0f;
    }
}

void func_ovl0A_05_800473A0(void) {
    s32 i;
    UnkStruct_ovl0A_05_80049518 *slot;

    func_ovl0A_05_80048468(1);
    while (!func_ovl0A_05_80049050(0x400)) {
        func_ovl0A_05_80048E10();
    }
    for (i = 0; i < 4; i++) {
        func_ovl0A_05_80048DC8(func_ovl0A_05_8004704C, (void *) i, 0, 0, 0x150);
    }
    func_ovl0A_05_80049508();
    slot = func_ovl0A_05_80049518(4);
    func_ovl0A_05_80048960(slot->unkC);
    slot->unkC = NULL;
    while (!func_ovl0A_05_80049050(0x401)) {
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_800490C8(0, 0, 0, 100.0f);
    func_ovl0A_05_80048DE8(1);
    func_ovl0A_05_80048370(0x1B, 0x12, 3);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_8004704C(void) {
    s32 pad[2]; /* unused: the original frame has these slots */
    s32 idx;
    UnkStruct_ovl0A_05_80049518 *slot;
    f32 sx;
    f32 sy;
    f32 x0;
    f32 y0;
    f32 t;
    f32 u;
    f32 a;
    f32 b;

    idx = (s32) func_ovl0A_05_80048DF0();
    slot = D_ovl0A_05_80049930[idx];
    sx = D_ovl0A_05_8004957C[idx];
    sy = D_ovl0A_05_8004958C[idx];
    x0 = slot->unkC->unk10;
    y0 = slot->unkC->unk14;
    for (t = 0.0f; t < 60.0f; t += 1.0f) {
        u = t / 60.0f;
        a = 270.0f * u + 180.0f;
        b = 90.0f * u;
        slot->unkC->unk10 = func_ovl0A_05_80048F70(a) * 74.73f * sx *func_ovl0A_05_80048F70(b);
        slot->unkC->unk14 = func_ovl0A_05_80048F70(a) * 56.0f * sy *func_ovl0A_05_80048F70(b) + -8.92f;
        func_ovl0A_05_80048E10();
    }
    slot->unkC->unk10 = 74.73f * sx + x0;
    slot->unkC->unk14 = 56.0f * sy + y0;
    x0 = slot->unkC->unk10;
    y0 = slot->unkC->unk14;
    func_ovl0A_05_80048DE8(20);
    for (t = 0.0f; t < 30.0f; t += 1.0f) {
        u = t / 30.0f;
        slot->unkC->unk10 = u * 40.0f * sx + x0;
        slot->unkC->unk14 = u * 40.0f * sy + y0;
        slot->unkC->unk28 = slot->unkC->unk2C = (1.0f - u) * 0.9f + 0.1f;
        slot->unkC->unk1C += 10.0f * sx * -1.0f;
        slot->unkC->unk20 += 10.0f * sy;
        func_ovl0A_05_80048E10();
    }
    slot->unkC->unkC |= 1;
    func_ovl0A_05_80049040(0x401);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_8004702C(void) {
    func_ovl0A_05_80049538();
}

void func_ovl0A_05_80046DFC(void) {
    s32 i;

    func_ovl0A_05_80049548();
    func_ovl0A_05_80048B20(0x10);
    func_ovl0A_05_80048AB8(0.0f, 75.0f, -100.0f);
    func_ovl0A_05_80048AD8(0.0f, 0.0f, 500.0f);
    D_ovl0A_05_80049960 = func_ovl0A_05_800494E8();
    D_ovl0A_05_80049960->unk20 = 0.0f;
    D_ovl0A_05_80049960->unk24 = 0.0f;
    D_ovl0A_05_80049960->unk28 = 0.0f;
    D_ovl0A_05_80049960->unk10 = 0.0f;
    D_ovl0A_05_80049960->unk14 = 0.0f;
    D_ovl0A_05_80049960->unk18 = 0.0f;
    D_ovl0A_05_80049960->unk1C = 0.0f;
    D_ovl0A_05_80049940 = func_ovl0A_05_80048CA0(0x320, 0, 0xD0, NULL);
    D_ovl0A_05_80049940->unk40->unk20 = 0.0f;
    D_ovl0A_05_80049944 = func_ovl0A_05_80048CA0(0x321, 0, 0xD0, NULL);
    D_ovl0A_05_80049948 = func_ovl0A_05_80048CA0(0x322, 0, 0xD0, NULL);
    D_ovl0A_05_80049948->unk40->unk20 =
        (D_ovl0A_05_80049940->unk40->unk20 * -1.0f) >= 360.0f ? (D_ovl0A_05_80049940->unk40->unk20 * -1.0f) - 360.0f
        : (D_ovl0A_05_80049940->unk40->unk20 * -1.0f) < 0.0f ? (D_ovl0A_05_80049940->unk40->unk20 * -1.0f) + 360.0f
        : (D_ovl0A_05_80049940->unk40->unk20 * -1.0f);
    D_ovl0A_05_8004994C = func_ovl0A_05_80048CA0(0x324, 0, 0xD0, NULL);
    D_ovl0A_05_80049950[0] = D_ovl0A_05_80049940;
    D_ovl0A_05_80049950[1] = D_ovl0A_05_80049944;
    D_ovl0A_05_80049950[2] = D_ovl0A_05_80049948;
    D_ovl0A_05_80049950[3] = D_ovl0A_05_8004994C;
    for (i = 0; i < 4; i++) {
        func_ovl0A_05_80048D50(D_ovl0A_05_8004959C[i], D_ovl0A_05_80049950[i]);
    }
    func_ovl0A_05_80048DC8(func_ovl0A_05_80046A1C, NULL, 0, 0, 0x150);
}

void func_ovl0A_05_80046A1C(void) {
    s32 i;
    f32 zero;

    func_ovl0A_05_80048468(1);
    while (!func_ovl0A_05_80049050(0x400)) {
        func_ovl0A_05_80048E10();
    }
    zero = 0.0f;
    func_ovl0A_05_800490C8(0, 0, 0, zero);

    for (i = 0; i < 3; i++) {
        func_ovl0A_05_80048DC8(func_ovl0A_05_800467FC, (void *) i, 0, 0, 0x150);
        func_ovl0A_05_80048DE8(20);
        func_ovl0A_05_80048DC8(func_ovl0A_05_80046558, (void *) i, 0, 0, 0x150);
        func_ovl0A_05_80048DE8(25);
        func_ovl0A_05_80045C00(D_ovl0A_05_80049950[i]);
        func_ovl0A_05_80048DE8(30);
        func_ovl0A_05_80048C80(D_ovl0A_05_80049950[i], 0x01000000);
        D_ovl0A_05_80049960->unk10 = zero;
        D_ovl0A_05_80049960->unk14 = zero;
        D_ovl0A_05_80049960->unk18 = zero;
        D_ovl0A_05_80049960->unk1C = zero;
    }
    func_ovl0A_05_80048DC8(func_ovl0A_05_800467FC, (void *) (i + 10), 0, 0, 0x150);
    func_ovl0A_05_80048DE8(20);
    func_ovl0A_05_80048DC8(func_ovl0A_05_800467FC, (void *) (i + 11), 0, 0, 0x150);
    func_ovl0A_05_80048DE8(20);
    D_ovl0A_05_80049960->unk10 = zero;
    D_ovl0A_05_80049960->unk14 = zero;
    D_ovl0A_05_80049960->unk18 = zero;
    D_ovl0A_05_80049960->unk1C = zero;
    func_ovl0A_05_800490C8(0xFF, 0xFF, 0xFF, 100.0f);
    func_ovl0A_05_80048DE8(10);
    func_ovl0A_05_80048AB8(zero, 75.0f, zero);
    func_ovl0A_05_80048AD8(zero, 21.0f, 600.0f);
    func_ovl0A_05_80048C78(D_ovl0A_05_80049940, 0x01000000);
    D_ovl0A_05_80049940->unk40->unk10 = -100.0f;
    D_ovl0A_05_80049940->unk40->unk14 = zero;
    D_ovl0A_05_80049940->unk40->unk18 = 0.0;
    func_ovl0A_05_80044BC4(D_ovl0A_05_80049940);
    func_ovl0A_05_80048C78(D_ovl0A_05_80049944, 0x01000000);
    D_ovl0A_05_80049944->unk40->unk10 = 0.0;
    D_ovl0A_05_80049944->unk40->unk14 = zero;
    D_ovl0A_05_80049944->unk40->unk18 = -200.0f;
    func_ovl0A_05_80044BC4(D_ovl0A_05_80049944);
    func_ovl0A_05_80048C78(D_ovl0A_05_80049948, 0x01000000);
    D_ovl0A_05_80049948->unk40->unk10 = 100.0f;
    D_ovl0A_05_80049948->unk40->unk14 = zero;
    D_ovl0A_05_80049948->unk40->unk18 = 0.0;
    func_ovl0A_05_80044BC4(D_ovl0A_05_80049948);
    for (i = 0; i < 30; i++) {
        func_ovl0A_05_800490C8(0xFF, 0xFF, 0xFF, (1.0f - ((f32) i / 30.0f)) * 100.0f);
        func_ovl0A_05_80048E10();
    }
    i = 3;
    func_ovl0A_05_80048DC8(func_ovl0A_05_80046558, (void *) i, 0, 0, 0x150);
    func_ovl0A_05_80048DE8(25);
    func_ovl0A_05_80045C00(D_ovl0A_05_80049950[i]);
    func_ovl0A_05_80048DE8(30);
    func_ovl0A_05_80048DE8(30);
    func_ovl0A_05_80048418(8);
    func_ovl0A_05_80048370(0x1B, 0x14, 0);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_800469EC(void) {
    func_ovl0A_05_800494F0(D_ovl0A_05_80049960);
    func_ovl0A_05_80049538();
}

void func_ovl0A_05_800467FC(void) {
    s32 n;
    f32 pad; /* unused: the original frame has this slot */
    s32 i;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
    f32 dx0;
    f32 dy0;
    f32 dx1;
    f32 dy1;

    i = (s32) func_ovl0A_05_80048DF0();
    n = 20;
    if (i >= 10) {
        i -= 10;
        n = 10;
    }
    D_ovl0A_05_80049960->unk20 = D_ovl0A_05_800495FC[i];
    D_ovl0A_05_80049960->unk24 = D_ovl0A_05_80049610[i];
    D_ovl0A_05_80049960->unk28 = D_ovl0A_05_80049624[i];
    D_ovl0A_05_80049960->unk10 = D_ovl0A_05_80049638[i][0];
    D_ovl0A_05_80049960->unk14 = D_ovl0A_05_80049638[i][1];
    D_ovl0A_05_80049960->unk18 = D_ovl0A_05_80049638[i][2];
    D_ovl0A_05_80049960->unk1C = D_ovl0A_05_80049638[i][3];
    x0 = D_ovl0A_05_80049638[i][0];
    y0 = D_ovl0A_05_80049638[i][1];
    x1 = D_ovl0A_05_80049638[i][2];
    y1 = D_ovl0A_05_80049638[i][3];
    dx0 = (D_ovl0A_05_80049638[i][4] - D_ovl0A_05_80049638[i][0]) / n;
    dy0 = (D_ovl0A_05_80049638[i][5] - D_ovl0A_05_80049638[i][1]) / n;
    dx1 = (D_ovl0A_05_80049638[i][6] - D_ovl0A_05_80049638[i][2]) / n;
    dy1 = (D_ovl0A_05_80049638[i][7] - D_ovl0A_05_80049638[i][3]) / n;
    for (i = 0; i < n; i++) {
        D_ovl0A_05_80049960->unk10 = x0;
        x0 += dx0;
        D_ovl0A_05_80049960->unk14 = y0;
        y0 += dy0;
        D_ovl0A_05_80049960->unk18 = x1;
        x1 += dx1;
        D_ovl0A_05_80049960->unk1C = y1;
        y1 += dy1;
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048DE8(55);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_80046558(void) {
    s32 idx;
    s32 k;
    s32 i;
    s32 anim;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 ax;
    f32 ay;
    f32 az;

    idx = (s32) func_ovl0A_05_80048DF0();
    dx = (D_ovl0A_05_8004959C[idx][3] - D_ovl0A_05_8004959C[idx][0]) / 12.5f;
    dy = (D_ovl0A_05_8004959C[idx][4] - D_ovl0A_05_8004959C[idx][1]) / 12.5f;
    dz = (D_ovl0A_05_8004959C[idx][5] - D_ovl0A_05_8004959C[idx][2]) / 12.5f;
    ax = (dx / 25.0f) * -1.0f;
    ay = (dy / 25.0f) * -1.0f;
    az = (dz / 25.0f) * -1.0f;
    switch (D_ovl0A_05_80049950[idx]->unk28) {
        case 0x320:
            anim = 0x23;
            break;
        case 0x321:
            anim = 0;
            break;
        case 0x322:
            anim = 0;
            break;
        case 0x324:
            anim = 0;
            break;
    }
    func_ovl0A_05_800489A0(D_ovl0A_05_80049950[idx]->unk40, anim, 0);
    D_ovl0A_05_80049950[idx]->unk40->unk48->unk4->unk4 = 0.0f;
    func_ovl0A_05_80048C78(D_ovl0A_05_80049950[idx], 0x01000000);
    k = 4;
    for (i = 0; i < 25; i++) {
        k++;
        D_ovl0A_05_80049950[idx]->unk40->unk10 += dx;
        dx += ax;
        D_ovl0A_05_80049950[idx]->unk40->unk14 += dy;
        dy += ay;
        D_ovl0A_05_80049950[idx]->unk40->unk18 += dz;
        dz += az;
        if (k >= 5) {
            k = 0;
            func_ovl0A_05_80048DC8(func_ovl0A_05_80046400, D_ovl0A_05_80049950[idx], 0, 0, 0x150);
        }
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048C78(D_ovl0A_05_80049950[idx], 0x04000000);
    func_ovl0A_05_80045C00(D_ovl0A_05_80049950[idx]);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_80046400(void) {
    UnkStruct_ovl0A_05_80048CA0 *src;
    UnkStruct_ovl0A_05_80048CA0 *obj;
    f32 t;

    src = func_ovl0A_05_80048DF0();
    obj = func_ovl0A_05_80048CA0(src->unk28, 0x01080000, 0xD0, NULL);
    func_ovl0A_05_80048970(obj->unk40, 0x3F);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    obj->unk40->unk20 = src->unk40->unk20;
    for (t = 0.0f; t < 20.0f; t += 1.0f) {
        obj->unk40->unk36 = (1.0f - (t / 20.0f)) * 200.0f;
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048C90(obj);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_80046248(void) {
    f32 pos[3];
    f32 t;
    f32 from[3];
    f32 *src;
    UnkStruct_ovl0A_05_80048CA0 *obj;
    s32 i;
    f32 d;
    f32 a;

    src = func_ovl0A_05_80048DF0();
    pos[0] = src[0];
    pos[1] = src[1];
    pos[2] = src[2];
    obj = func_ovl0A_05_80048CA0(0x1CB, 0x01480000, 0xD0, NULL);
    obj->unk40->unk30 = 0.4f;
    obj->unk40->unk28 = obj->unk40->unk30;
    d = 50.0f;
    from[0] = 400.0f;
    from[1] = 4000.0f;
    from[2] = -800.0f;
    pos[1] += d;
    func_ovl0A_05_80049220(7, pos, 0);
    pos[1] -= d;
    func_ovl0A_05_80048D50(from, obj);
    for (i = 0; i < 30; i++) {
        t = (f32) i / 30.0f;
        a = (1.0f - t) * 191.25f;
        obj->unk40->unk36 = a;
        func_ovl0A_05_800458DC(obj, from, pos);
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048C90(obj);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_800461C8(void) {
    while (1) {
        func_ovl0A_05_800461C0();
        func_ovl0A_05_80048E10();
    }
}

static void func_ovl0A_05_800461C0(void) {
    D_ovl0A_05_800498EC = func_ovl0A_05_80048458();
    func_ovl0A_05_80048438(&D_ovl0A_05_800498E0);
    func_ovl0A_05_80048460(D_ovl0A_05_800498EC, &D_ovl0A_05_800498D0);
}

void func_ovl0A_05_800460C8(void) {
    func_ovl0A_05_80048DC8(func_ovl0A_05_80045E58, NULL, 0, 0, 0x150);
    func_ovl0A_05_80048DC8(func_ovl0A_05_800461C8, NULL, 0, 0, 0x110);
    func_ovl0A_05_80048DC8(func_ovl0A_05_80045EF0, NULL, 0, 0, 0x150);
    func_ovl0A_05_80045568();
    func_ovl0A_05_80048290(0x2E3);
    func_ovl0A_05_80048428();
    func_ovl0A_05_80048430(0x14, 0, 4);
    func_ovl0A_05_80048488();
    func_ovl0A_05_80048B20(0x7F);
    func_ovl0A_05_80048B18(0x10);
    func_ovl0A_05_80048B30(1);
    func_ovl0A_05_80048AA8(0);
    func_ovl0A_05_80048AC8(3365.0f, 780.0f, 2200.0f);
    func_ovl0A_05_800490C8(0, 0, 0, 100.0f);
}

void func_ovl0A_05_80045EF0(void) {
    Vec3f_ovl0A_05 pos;

    func_ovl0A_05_80048468(1);
    while (!func_ovl0A_05_80049050(0x400)) {
        func_ovl0A_05_80048E10();
    }
    while (1) {
        func_ovl0A_05_80048DE8(20);
        pos.x = D_ovl0A_05_800498D0.x;
        pos.y = D_ovl0A_05_800498D0.y;
        pos.z = D_ovl0A_05_800498D0.z;
        func_ovl0A_05_80048DE8(20);
        func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
        func_ovl0A_05_80048DE8(10);
        pos.x = D_ovl0A_05_800498D0.x;
        pos.y = D_ovl0A_05_800498D0.y;
        pos.z = D_ovl0A_05_800498D0.z;
        func_ovl0A_05_80048DE8(30);
        func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
        func_ovl0A_05_80048DE8(20);
        pos.x = D_ovl0A_05_800498D0.x;
        pos.y = D_ovl0A_05_800498D0.y;
        pos.z = D_ovl0A_05_800498D0.z;
        func_ovl0A_05_80048DE8(10);
        func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
        func_ovl0A_05_80048DE8(10);
        pos.x = D_ovl0A_05_800498D0.x;
        pos.y = D_ovl0A_05_800498D0.y;
        pos.z = D_ovl0A_05_800498D0.z;
        func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
        func_ovl0A_05_80048DE8(5);
        pos.x = D_ovl0A_05_800498D0.x;
        pos.y = D_ovl0A_05_800498D0.y;
        pos.z = D_ovl0A_05_800498D0.z;
        func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
    }
}

void func_ovl0A_05_80045E58(void) {
    func_ovl0A_05_80048468(1);
    while (!func_ovl0A_05_80049050(0x400)) {
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_800490C8(0, 0, 0, 0.0f);
    func_ovl0A_05_800490A8(1);
    func_ovl0A_05_80048468(1);
    func_ovl0A_05_800483E0(0);
    func_ovl0A_05_80048480("WM1 WAP WG1 WSH WDS WB2 ST1 WDSE WB1 ST1                                        WDS WB2 ST1 WDSW WB2 ST1 WDS WB10 ST1");
    func_ovl0A_05_80048370(0x1B, 0x14, 0);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_80045E38(void) {
    func_ovl0A_05_80049538();
}

void func_ovl0A_05_80045D90(void) {
    func_ovl0A_05_80048DC8(func_ovl0A_05_80045C58, NULL, 0, 0, 0x150);
    D_ovl0A_05_80049968 = func_ovl0A_05_80048CA0(0x328, 0x01000000, 0xD0, NULL);
    func_ovl0A_05_800489A0(D_ovl0A_05_80049968->unk40, 0x16, 0);
    func_ovl0A_05_80048B20(0x7F);
    func_ovl0A_05_80048AB8(0.0f, 75.0f, 0.0f);
    func_ovl0A_05_80048AA8(0);
    func_ovl0A_05_80048AC8(600.0f, 290.0f, 700.0f);
}

void func_ovl0A_05_80045C58(void) {
    func_ovl0A_05_80048468(1);
    while (!func_ovl0A_05_80049050(0x400)) {
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048C80(D_ovl0A_05_80049968, 0x08000000);
    func_ovl0A_05_80048C78(D_ovl0A_05_80049968, 0x04000000);
    func_ovl0A_05_80045C00(D_ovl0A_05_80049968);
    func_ovl0A_05_80048B80(D_ovl0A_05_80049968);
    func_ovl0A_05_80048B18(0x30);
    D_ovl0A_05_80049970.x = 0.0f;
    D_ovl0A_05_80049970.y = 90.0f;
    D_ovl0A_05_80049970.z = 10.0f;
    func_ovl0A_05_80048B58(&D_ovl0A_05_80049970.x);
    func_ovl0A_05_80048B50(2.0f * D_ovl0A_05_80049970.z);
    func_ovl0A_05_80048B78(0, 0, 10000.0f, 10000.0f);
    func_ovl0A_05_80048DC8(func_ovl0A_05_800459C8, NULL, 0, 0, 0x150);
    func_ovl0A_05_80048DE8(40);
    func_ovl0A_05_80048418(8);
    func_ovl0A_05_80048370(0x1B, 0x15, 0);
    func_ovl0A_05_80048DD8();
}

/* Waits for the object's animation to end; IDO passes obj in s0. */
static void func_ovl0A_05_80045C00(UnkStruct_ovl0A_05_80048CA0 *obj) {
    while (!(obj->unk40->unkC & 0x40)) {
        func_ovl0A_05_80048E10();
    }
}

void func_ovl0A_05_800459C8(void) {
    s32 i;
    f32 v;
    f32 s;
    f32 dv;
    UnkStruct_ovl0A_05_80048CA0 *objs[2];
    s32 pad1; /* unused: the original's frame has these slots */
    f32 b[3];
    f32 a[3];
    s32 pad2[2]; /* unused, as pad1 */

    for (i = 0; i < 2; i++) {
        objs[i] = func_ovl0A_05_80048CA0(0x1CB, 0x01480000, 0xD0, NULL);
        objs[i]->unk40->unk30 = 0.1f;
        objs[i]->unk40->unk28 = objs[i]->unk40->unk30;
        objs[i]->unk40->unk36 = 0xBF;
    }
    func_ovl0A_05_80048D48(D_ovl0A_05_80049968, a);
    dv = 5.0f;
    v = 0.0f;
    a[1] += 60.0f;
    while (1) {
        D_ovl0A_05_80049968->unk40->unk18 += v;
        v += dv;
        if (v > 60.0f) {
            v = 60.0f;
        }
        s = 1.0f;
        for (i = 0; i < 2; i++) {
            func_ovl0A_05_80048D48(D_ovl0A_05_80049968, b);
            a[1] = b[1] += 60.0f;
            a[0] = b[0] += 150.0f * s;
            func_ovl0A_05_800458DC(objs[i], b, a);
            func_ovl0A_05_80048D50(b, objs[i]);
            s *= -1.0f;
            objs[i]->unk40->unk36--;
            if (objs[i]->unk40->unk36 < 0) {
                objs[i]->unk40->unk36 = 0;
            }
        }
        func_ovl0A_05_80048E10();
    }
}

void func_ovl0A_05_8004599C(void) {
    func_ovl0A_05_80048CA0(0x1CB, 0x01480000, 0xD0, NULL);
}

void func_ovl0A_05_800458DC(UnkStruct_ovl0A_05_80048CA0 *obj, f32 *from, f32 *to) {
    f32 ang[3];

    func_ovl0A_05_80048C08(from, to, ang);
    obj->unk40->unk20 = ang[0];
    obj->unk40->unk1C = ((ang[1] - 180.0f) >= 360.0f ? (ang[1] - 180.0f) - 360.0f
                         : (ang[1] - 180.0f) < 0.0f ? (ang[1] - 180.0f) + 360.0f : (ang[1] - 180.0f)) * -1.0f;
    obj->unk40->unk2C = ang[2] / 100.0f;
}

void func_ovl0A_05_800458BC(void) {
    func_ovl0A_05_80049538();
}

void func_ovl0A_05_8004571C(void) {
    func_ovl0A_05_80048DC8(func_ovl0A_05_80044FD0, NULL, 0, 0, 0x150);
    func_ovl0A_05_80045568();
    func_ovl0A_05_80048290(0x2E3);
    func_ovl0A_05_80048428();
    func_ovl0A_05_80048430(0x14, 0, 4);
    func_ovl0A_05_80048488();
    D_ovl0A_05_80049964 = func_ovl0A_05_800484B8(func_ovl0A_05_80048458());
    func_ovl0A_05_80048B20(0x7F);
    func_ovl0A_05_80048B80(D_ovl0A_05_80049964);
    func_ovl0A_05_80048B18(0x30);
    D_ovl0A_05_80049970.x = 0.0f;
    D_ovl0A_05_80049970.y = 90.0f;
    D_ovl0A_05_80049970.z = 10.0f;
    func_ovl0A_05_80048B58(&D_ovl0A_05_80049970.x);
    func_ovl0A_05_80048B50(2.0f * D_ovl0A_05_80049970.z);
    func_ovl0A_05_80048B78(0, 0, 10000.0f, 10000.0f);
    func_ovl0A_05_80048B68(0, 0, 10000.0f, 10000.0f);
    func_ovl0A_05_80048B70(90.0f, 0.0f);
    func_ovl0A_05_80048AD8(-225.0f, 60.0f, 2500.0f);
    D_ovl0A_05_80049968 = func_ovl0A_05_80048CA0(0x328, 0, 0xD0, NULL);
    func_ovl0A_05_800489A0(D_ovl0A_05_80049968->unk40, 0x16, 0);
    func_ovl0A_05_80044BC4(D_ovl0A_05_80049968);
    func_ovl0A_05_800490C8(0, 0, 0, 100.0f);
}

void func_ovl0A_05_80045568(void) {
    s32 i;
    s32 j;
    f32 z;
    f32 x;
    UnkStruct_ovl0A_05_80048CA0 *obj;

    D_ovl0A_05_80049924 = func_ovl0A_05_80048CA0(0x2DE, 0x01000000, 0xD0, NULL);
    D_ovl0A_05_80049924->unk40->unk10 -= 50.0f;
    for (i = 0, z = -2.0f; i < 5; i++, z += 1.0f) {
        for (x = -2.0f, j = 0; j < 5; j++, x += 1.0f) {
            if (i != 2 || j != 2) {
                obj = func_ovl0A_05_80048CA0(0x2DE, 0x01200000, 0xD0, D_ovl0A_05_80049924);
                obj->unk54 = 1400.0f * z;
                obj->unk4C = 1400.0f * x;
            }
        }
    }
    func_ovl0A_05_80049108(0x384, 0x3C0, 0, 0, 0);
    D_ovl0A_05_80049928 = func_ovl0A_05_80048E50(0x357);
    func_ovl0A_05_80048E60(D_ovl0A_05_80049928, 0x20000000);
    D_ovl0A_05_80049928->unk40 = 1.0f;
    D_ovl0A_05_80049928->unk44 = D_ovl0A_05_80049928->unk40 * 0.75f;
}

void func_ovl0A_05_80045350(void) {
    s32 n;
    s32 i;
    f32 v;

    n = (s32) func_ovl0A_05_80048DF0();
    func_ovl0A_05_80048C78(D_ovl0A_05_80049968, 0x01000000);
    D_ovl0A_05_80049968->unk40->unk10 = 2000.0f;
    D_ovl0A_05_80049968->unk40->unk14 = 200.0f;
    D_ovl0A_05_80049968->unk40->unk18 = 1400.0f;
    D_ovl0A_05_80049968->unk40->unk20 = 90.0f;
    D_ovl0A_05_80049968->unk40->unk10 -= 60.0f * n;
    for (i = 0; i < n; i++) {
        D_ovl0A_05_80049968->unk40->unk10 += 60.0f;
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048DC8(func_ovl0A_05_80045310, NULL, 0, 0, 0x150);
    v = 0.0f;
    func_ovl0A_05_80048C78(D_ovl0A_05_80049964, 0x400000);
    func_ovl0A_05_80048C58(D_ovl0A_05_80049968, D_ovl0A_05_80049964);
    D_ovl0A_05_80049964->unk50 = 60.0f;
    while (1) {
        D_ovl0A_05_80049968->unk40->unk10 += 60.0f;
        D_ovl0A_05_80049968->unk40->unk14 += v;
        v += 5.0f;
        if (v > 30.0f) {
            v = 30.0f;
        }
        func_ovl0A_05_80048E10();
    }
}

void func_ovl0A_05_80045310(void) {
    func_ovl0A_05_80048DE8(10);
    func_ovl0A_05_80048418(8);
    func_ovl0A_05_80048370(0x1B, 0x16, 0);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_800450B4(void) {
    Vec3f_ovl0A_05 pos;

    func_ovl0A_05_80048468(1);
    while (!func_ovl0A_05_80049050(0x400)) {
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048DE8(20);
    pos.x = D_ovl0A_05_800498D0.x;
    pos.y = D_ovl0A_05_800498D0.y;
    pos.z = D_ovl0A_05_800498D0.z;
    func_ovl0A_05_80048DE8(20);
    func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
    func_ovl0A_05_80048DE8(10);
    pos.x = D_ovl0A_05_800498D0.x;
    pos.y = D_ovl0A_05_800498D0.y;
    pos.z = D_ovl0A_05_800498D0.z;
    func_ovl0A_05_80048DE8(30);
    func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
    func_ovl0A_05_80048DE8(20);
    pos.x = D_ovl0A_05_800498D0.x;
    pos.y = D_ovl0A_05_800498D0.y;
    pos.z = D_ovl0A_05_800498D0.z;
    func_ovl0A_05_80048DE8(10);
    func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
    func_ovl0A_05_80048DE8(10);
    pos.x = D_ovl0A_05_800498D0.x;
    pos.y = D_ovl0A_05_800498D0.y;
    pos.z = D_ovl0A_05_800498D0.z;
    func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
    func_ovl0A_05_80048DE8(5);
    pos.x = D_ovl0A_05_800498D0.x;
    pos.y = D_ovl0A_05_800498D0.y;
    pos.z = D_ovl0A_05_800498D0.z;
    func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
    D_ovl0A_05_80049964->unk68 = 30.0f;
    func_ovl0A_05_80048508(func_ovl0A_05_80048458(), 0xB);
    func_ovl0A_05_80048DC8(func_ovl0A_05_80045350, (void *) 30, 0, 0, 0x150);
    while (1) {
        pos.x = D_ovl0A_05_800498D0.x;
        pos.y = 0.0f;
        pos.z = D_ovl0A_05_800498D0.z;
        func_ovl0A_05_80048DE8(5);
        func_ovl0A_05_80048DC8(func_ovl0A_05_80046248, &pos, 0, 0, 0x150);
        func_ovl0A_05_80048DE8(8);
    }
}

void func_ovl0A_05_80044FD0(void) {
    func_ovl0A_05_80048468(1);
    while (!func_ovl0A_05_80049050(0x400)) {
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_800490C8(0, 0, 0, 0.0f);
    func_ovl0A_05_800490A8(1);
    func_ovl0A_05_80048468(1);
    func_ovl0A_05_800483E0(0);
    func_ovl0A_05_80048AF0(D_ovl0A_05_800496D8, 0x170, 0);
    func_ovl0A_05_80048DC8(func_ovl0A_05_800461C8, NULL, 0, 0, 0x110);
    func_ovl0A_05_80048DC8(func_ovl0A_05_800450B4, NULL, 0, 0, 0x150);
    func_ovl0A_05_80048480("WSH W1 WG1 WDS WAP WB10 ST1");
    func_ovl0A_05_80048DE8(60);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_80044F80(void) {
    if (D_ovl0A_05_80049964->unk44 != 0) {
        func_ovl0A_05_80048C50(D_ovl0A_05_80049964);
        func_ovl0A_05_80048C80(D_ovl0A_05_80049964, 0xF00000);
    }
    func_ovl0A_05_80049538();
}

void func_ovl0A_05_80044C08(void) {
    D_ovl0A_05_8004990C = func_ovl0A_05_80048958(0x353, 1);
    D_ovl0A_05_8004990C->unkC |= 1;
    D_ovl0A_05_80049914 = func_ovl0A_05_80048958(0x355, 2);
    D_ovl0A_05_80049914->unkC |= 1;
    D_ovl0A_05_80049918 = func_ovl0A_05_80048958(0x356, 3);
    D_ovl0A_05_80049918->unkC |= 1;
    D_ovl0A_05_80049910 = func_ovl0A_05_80048958(0x354, 4);
    D_ovl0A_05_80049910->unkC |= 1;
    D_ovl0A_05_8004991C = func_ovl0A_05_80048E50(0x296);
    func_ovl0A_05_80048E60(D_ovl0A_05_8004991C, 1);
    D_ovl0A_05_8004991C->unk18 = 0.0f;
    D_ovl0A_05_8004991C->unk1C = 0.0f;
    D_ovl0A_05_8004991C->unk40 = 0.5f;
    D_ovl0A_05_8004991C->unk44 = D_ovl0A_05_8004991C->unk40 * 0.75f;
    D_ovl0A_05_8004991C->unk3C = 32.0f;
}

void func_ovl0A_05_80044D28(void) {
    f32 zero;

    func_ovl0A_05_80044C08();
    func_ovl0A_05_80048DC8(func_ovl0A_05_800430D0, NULL, 0, 0, 0x150);
    D_ovl0A_05_80049968 = func_ovl0A_05_80048CA0(0x328, 0, 0xD0, NULL);
    func_ovl0A_05_800489A0(D_ovl0A_05_80049968->unk40, 0x16, 0);
    func_ovl0A_05_80044BC4(D_ovl0A_05_80049968);
    zero = 0.0f;
    D_ovl0A_05_80049968->unk40->unk18 = zero;
    D_ovl0A_05_80049968->unk40->unk10 = D_ovl0A_05_80049968->unk40->unk18;
    D_ovl0A_05_80049968->unk40->unk14 = 1000.0f;
    func_ovl0A_05_80048290(0x2E3);
    func_ovl0A_05_80048428();
    D_ovl0A_05_80049964 = func_ovl0A_05_800484B8(func_ovl0A_05_80048458());
    func_ovl0A_05_80048998(D_ovl0A_05_80049964->unk40, 2);
    func_ovl0A_05_80048C78(D_ovl0A_05_80049964, 0x400000);
    func_ovl0A_05_80048C58(D_ovl0A_05_80049968, D_ovl0A_05_80049964);
    D_ovl0A_05_80049964->unk50 = 60.0f;
    func_ovl0A_05_80048B78(zero, zero, 10000.0f, 10000.0f);
    func_ovl0A_05_80048B68(zero, zero, 10000.0f, 10000.0f);
    func_ovl0A_05_80048B20(0x7F);
    func_ovl0A_05_80048B70(90.0f, zero);
    func_ovl0A_05_80048AB8(-200.0f, D_ovl0A_05_80049968->unk40->unk14 + 100.0f, zero);
    func_ovl0A_05_80048AA8(1);
    func_ovl0A_05_80048AD8(315.0f, 30.0f, 1500.0f);
    D_ovl0A_05_80049928 = func_ovl0A_05_80048E50(0x357);
    func_ovl0A_05_80048E60(D_ovl0A_05_80049928, 0x20000001);
    D_ovl0A_05_80049928->unk40 = 1.0f;
    D_ovl0A_05_80049928->unk44 = D_ovl0A_05_80049928->unk40 * 0.75f;
    D_ovl0A_05_80049928->unk18 = zero;
    D_ovl0A_05_80049928->unk1C = zero;
    func_ovl0A_05_800490C8(0, 0, 0, 100.0f);
}

/* IDO passes obj in s0. */
static void func_ovl0A_05_80044BC4(UnkStruct_ovl0A_05_80048CA0 *obj) {
    obj->unk40->unk48->unk4->unk4 = func_ovl0A_05_800489B8(obj->unk40, 0) - 0.001f;
}

void func_ovl0A_05_80044984(void) {
    f32 a;
    f32 b;
    f32 d;
    s32 i;

    b = 0.0f;
    a = 0.0f;
    while (D_ovl0A_05_80049964->unk40->unk10 != D_ovl0A_05_80049964->unk58
           || D_ovl0A_05_80049964->unk40->unk14 != D_ovl0A_05_80049964->unk5C) {
        d = D_ovl0A_05_80049964->unk40->unk10 - D_ovl0A_05_80049964->unk58;
        if (a < d) {
            a = d;
        }
        d = D_ovl0A_05_80049964->unk40->unk14 - D_ovl0A_05_80049964->unk5C;
        if (d < b) {
            b = d;
        }
        D_ovl0A_05_80049928->unk18 = a * 0.4f;
        D_ovl0A_05_80049928->unk1C = b * 0.05f;
        func_ovl0A_05_80048E10();
    }
    while (D_ovl0A_05_80049964->unk40->unk10 == D_ovl0A_05_80049964->unk58
           && D_ovl0A_05_80049964->unk40->unk14 == D_ovl0A_05_80049964->unk5C) {
        func_ovl0A_05_80048E10();
    }
    a = D_ovl0A_05_80049928->unk18;
    b = D_ovl0A_05_80049928->unk1C;
    for (i = 0; i < 60; i++) {
        D_ovl0A_05_80049928->unk18 = a;
        a += 0.05f;
        D_ovl0A_05_80049928->unk1C = b;
        b += 0.0002f;
    }
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_800446AC(void) {
    f32 cx;
    f32 cy;
    f32 dx;
    f32 dy;
    s32 i;
    f32 t;
    f32 s;
    f32 x;

    func_ovl0A_05_80048DE8(20);
    func_ovl0A_05_80049120(1);
    func_ovl0A_05_80049128(0xBF);
    D_ovl0A_05_80049910->unk10 = 229.0f;
    D_ovl0A_05_80049910->unk14 = 126.0f;
    D_ovl0A_05_80049910->unk18 = D_ovl0A_05_80049910->unk10 + D_ovl0A_05_80049910->unk28;
    D_ovl0A_05_80049910->unk1C = D_ovl0A_05_80049910->unk14 + D_ovl0A_05_80049910->unk2C;
    D_ovl0A_05_80049910->unkC &= ~1;
    x = D_ovl0A_05_80049910->unk10 + D_ovl0A_05_80049910->unk28 * 0.5f;
    cy = D_ovl0A_05_80049910->unk14 + D_ovl0A_05_80049910->unk2C * 0.5f;
    dx = (29.0f - D_ovl0A_05_80049910->unk10) / 40.0f;
    dy = (78.0f - D_ovl0A_05_80049910->unk14) / 40.0f;
    cx = x;
    for (i = 0; i < 40; i++) {
        t = (f32) i / 39.0f;
        cx += dx;
        x = func_ovl0A_05_80048F70(180.0f * t) * 64.0f + cx;
        cy += dy;
        s = (1.0f - t) * 3.0f + 1.0f;
        D_ovl0A_05_80049910->unk10 = x - D_ovl0A_05_80049910->unk28 * s * 0.5f;
        D_ovl0A_05_80049910->unk14 = cy - D_ovl0A_05_80049910->unk2C * s * 0.5f;
        D_ovl0A_05_80049910->unk18 = D_ovl0A_05_80049910->unk28 * s * 0.5f + x;
        D_ovl0A_05_80049910->unk1C = D_ovl0A_05_80049910->unk2C * s * 0.5f + cy;
        func_ovl0A_05_80048E10();
    }
    D_ovl0A_05_80049910->unk10 = 29.0f;
    D_ovl0A_05_80049910->unk14 = 78.0f;
    D_ovl0A_05_80049910->unk18 = D_ovl0A_05_80049910->unk10 + D_ovl0A_05_80049910->unk28;
    D_ovl0A_05_80049910->unk1C = D_ovl0A_05_80049910->unk14 + D_ovl0A_05_80049910->unk2C;
    func_ovl0A_05_80048370(0x20, 0x11, 4);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_800442DC(void) {
    f32 t;
    f32 x;
    f32 dx;
    f32 dy;
    f32 cx;
    f32 cy;
    s32 i;
    f32 sx;
    f32 sy;

    D_ovl0A_05_80049918->unk10 = 364.0f;
    D_ovl0A_05_80049918->unk14 = 136.0f;
    D_ovl0A_05_80049918->unk18 = D_ovl0A_05_80049918->unk10 + D_ovl0A_05_80049918->unk28;
    D_ovl0A_05_80049918->unk1C = D_ovl0A_05_80049918->unk14 + D_ovl0A_05_80049918->unk2C;
    D_ovl0A_05_80049918->unkC &= ~1;
    while (1) {
        D_ovl0A_05_80049918->unk10 += -10.0f;
        D_ovl0A_05_80049918->unk14 += 1.0f;
        D_ovl0A_05_80049918->unk18 = D_ovl0A_05_80049918->unk10 + D_ovl0A_05_80049918->unk28;
        D_ovl0A_05_80049918->unk1C = D_ovl0A_05_80049918->unk14 + D_ovl0A_05_80049918->unk2C;
        if (D_ovl0A_05_80049918->unk10 <= 164.0f) {
            D_ovl0A_05_80049918->unk10 = 164.0f;
            D_ovl0A_05_80049918->unk18 = D_ovl0A_05_80049918->unk10 + D_ovl0A_05_80049918->unk28;
            x = D_ovl0A_05_80049918->unk10 + D_ovl0A_05_80049918->unk28 * 0.5f;
            cy = D_ovl0A_05_80049918->unk14 + D_ovl0A_05_80049918->unk2C * 0.5f;
            break;
        }
        func_ovl0A_05_80048E10();
    }
    dx = (164.0f - D_ovl0A_05_80049918->unk10) / 40.0f;
    dy = (88.0f - D_ovl0A_05_80049918->unk14) / 40.0f;
    cx = x;
    for (i = 0; i < 40; i++) {
        t = (f32) i / 39.0f;
        cx += dx;
        x = func_ovl0A_05_80048F70(180.0f * t) * 64.0f + cx;
        cy += dy;
        sx = func_ovl0A_05_80048F70(t * -1080.0f) * (0.5f * (1.0f - t)) + 1.0f;
        sy = func_ovl0A_05_80048F70(t * 1080.0f) * (0.5f * (1.0f - t)) + 1.0f;
        D_ovl0A_05_80049918->unk10 = x - D_ovl0A_05_80049918->unk28 * sx * 0.5f;
        D_ovl0A_05_80049918->unk14 = cy - D_ovl0A_05_80049918->unk2C * sy * 0.5f;
        D_ovl0A_05_80049918->unk18 = D_ovl0A_05_80049918->unk28 * sx * 0.5f + x;
        D_ovl0A_05_80049918->unk1C = D_ovl0A_05_80049918->unk2C * sy * 0.5f + cy;
        func_ovl0A_05_80048E10();
    }
    D_ovl0A_05_80049918->unk10 = 164.0f;
    D_ovl0A_05_80049918->unk14 = 88.0f;
    D_ovl0A_05_80049918->unk18 = D_ovl0A_05_80049918->unk10 + D_ovl0A_05_80049918->unk28;
    D_ovl0A_05_80049918->unk1C = D_ovl0A_05_80049918->unk14 + D_ovl0A_05_80049918->unk2C;
    func_ovl0A_05_80048DC8(func_ovl0A_05_800446AC, NULL, 0, 0, 0x150);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_80043EE8(void) {
    f32 t;
    f32 x;
    f32 dx;
    f32 dy;
    f32 cx;
    f32 cy;
    s32 i;
    f32 sx;
    f32 sy;

    D_ovl0A_05_80049914->unk10 = 327.0f;
    D_ovl0A_05_80049914->unk14 = 102.0f;
    D_ovl0A_05_80049914->unk18 = D_ovl0A_05_80049914->unk10 + D_ovl0A_05_80049914->unk28;
    D_ovl0A_05_80049914->unk1C = D_ovl0A_05_80049914->unk14 + D_ovl0A_05_80049914->unk2C;
    D_ovl0A_05_80049914->unkC &= ~1;
    while (1) {
        D_ovl0A_05_80049914->unk10 += -10.0f;
        D_ovl0A_05_80049914->unk14 += 1.0f;
        D_ovl0A_05_80049914->unk18 = D_ovl0A_05_80049914->unk10 + D_ovl0A_05_80049914->unk28;
        D_ovl0A_05_80049914->unk1C = D_ovl0A_05_80049914->unk14 + D_ovl0A_05_80049914->unk2C;
        if (D_ovl0A_05_80049914->unk10 <= 127.0f) {
            D_ovl0A_05_80049914->unk10 = 127.0f;
            D_ovl0A_05_80049914->unk18 = D_ovl0A_05_80049914->unk10 + D_ovl0A_05_80049914->unk28;
            x = D_ovl0A_05_80049914->unk10 + D_ovl0A_05_80049914->unk28 * 0.5f;
            cy = D_ovl0A_05_80049914->unk14 + D_ovl0A_05_80049914->unk2C * 0.5f;
            break;
        }
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048DC8(func_ovl0A_05_800442DC, NULL, 0, 0, 0x150);
    dx = (127.0f - D_ovl0A_05_80049914->unk10) / 40.0f;
    dy = (54.0f - D_ovl0A_05_80049914->unk14) / 40.0f;
    cx = x;
    for (i = 0; i < 40; i++) {
        t = (f32) i / 39.0f;
        cx += dx;
        x = func_ovl0A_05_80048F70(180.0f * t) * 64.0f + cx;
        cy += dy;
        sx = func_ovl0A_05_80048F70(t * -1080.0f) * (0.5f * (1.0f - t)) + 1.0f;
        sy = func_ovl0A_05_80048F70(t * 1080.0f) * (0.5f * (1.0f - t)) + 1.0f;
        D_ovl0A_05_80049914->unk10 = x - D_ovl0A_05_80049914->unk28 * sx * 0.5f;
        D_ovl0A_05_80049914->unk14 = cy - D_ovl0A_05_80049914->unk2C * sy * 0.5f;
        D_ovl0A_05_80049914->unk18 = D_ovl0A_05_80049914->unk28 * sx * 0.5f + x;
        D_ovl0A_05_80049914->unk1C = D_ovl0A_05_80049914->unk2C * sy * 0.5f + cy;
        func_ovl0A_05_80048E10();
    }
    D_ovl0A_05_80049914->unk10 = 127.0f;
    D_ovl0A_05_80049914->unk14 = 54.0f;
    D_ovl0A_05_80049914->unk18 = D_ovl0A_05_80049914->unk10 + D_ovl0A_05_80049914->unk28;
    D_ovl0A_05_80049914->unk1C = D_ovl0A_05_80049914->unk14 + D_ovl0A_05_80049914->unk2C;
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_800438A0(void) {
    f32 dx;
    f32 s;
    f32 x;
    f32 sy;
    f32 sx;
    f32 ax;
    f32 t;
    f32 dy;
    s32 i;
    f32 y;
    s32 *flag;
    f32 cx;

    flag = func_ovl0A_05_80048DF0();
    x = 200.0f;
    y = 55.0f;
    D_ovl0A_05_8004990C->unkC &= ~1;
    D_ovl0A_05_8004990C->unk10 = x - D_ovl0A_05_8004990C->unk28 * 0.25f * 0.5f;
    D_ovl0A_05_8004990C->unk14 = y - D_ovl0A_05_8004990C->unk2C * 0.25f * 0.5f;
    D_ovl0A_05_8004990C->unk18 = D_ovl0A_05_8004990C->unk28 * 0.25f * 0.5f + x;
    D_ovl0A_05_8004990C->unk1C = D_ovl0A_05_8004990C->unk2C * 0.25f * 0.5f + y;
    while (*flag) {
        func_ovl0A_05_80048E10();
    }
    dx = -2.0f;
    dy = 0.5f;
    ax = -0.1f;
    for (i = 0; i < 10; i++) {
        x += dx;
        y += dy;
        dx += ax;
        dy += 0.05f;
        D_ovl0A_05_8004990C->unk10 = x - D_ovl0A_05_8004990C->unk28 * 0.25f * 0.5f;
        D_ovl0A_05_8004990C->unk14 = y - D_ovl0A_05_8004990C->unk2C * 0.25f * 0.5f;
        D_ovl0A_05_8004990C->unk18 = D_ovl0A_05_8004990C->unk28 * 0.25f * 0.5f + x;
        D_ovl0A_05_8004990C->unk1C = D_ovl0A_05_8004990C->unk2C * 0.25f * 0.5f + y;
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048DC8(func_ovl0A_05_80043EE8, NULL, 0, 0, 0x150);
    for (i = 0; i < 25; i++) {
        y += dy;
        dy += 0.05f;
        x += dx;
        dx += ax;
        s = ((f32) i * 0.75f) / 25.0f + 0.25f;
        D_ovl0A_05_8004990C->unk10 = x - D_ovl0A_05_8004990C->unk28 * s * 0.5f;
        D_ovl0A_05_8004990C->unk14 = y - D_ovl0A_05_8004990C->unk2C * s * 0.5f;
        D_ovl0A_05_8004990C->unk18 = D_ovl0A_05_8004990C->unk28 * s * 0.5f + x;
        D_ovl0A_05_8004990C->unk1C = D_ovl0A_05_8004990C->unk2C * s * 0.5f + y;
        func_ovl0A_05_80048E10();
    }
    s = 1.0f;
    ax = 0.0f;
    while (1) {
        x += dx;
        y += dy;
        dx += ax;
        dy += ax;
        D_ovl0A_05_8004990C->unk10 = x - D_ovl0A_05_8004990C->unk28 * s * 0.5f;
        D_ovl0A_05_8004990C->unk14 = y - D_ovl0A_05_8004990C->unk2C * s * 0.5f;
        D_ovl0A_05_8004990C->unk18 = D_ovl0A_05_8004990C->unk28 * s * 0.5f + x;
        D_ovl0A_05_8004990C->unk1C = D_ovl0A_05_8004990C->unk2C * s * 0.5f + y;
        if (D_ovl0A_05_8004990C->unk10 <= 32.0f) {
            D_ovl0A_05_8004990C->unk10 = 32.0f;
            D_ovl0A_05_8004990C->unk18 = D_ovl0A_05_8004990C->unk28 * s;
            x = D_ovl0A_05_8004990C->unk10 + D_ovl0A_05_8004990C->unk28 * s * 0.5f;
            break;
        }
        func_ovl0A_05_80048E10();
    }
    dx = (71.0f - D_ovl0A_05_8004990C->unk10) / 60.0f;
    dy = (13.0f - D_ovl0A_05_8004990C->unk14) / 60.0f;
    cx = x;
    for (i = 0; i < 60; i++) {
        cx += dx;
        t = (f32) i / 59.0f;
        x = func_ovl0A_05_80048F70(180.0f * t) * 64.0f + cx;
        y += dy;
        sx = func_ovl0A_05_80048F70(t * -1080.0f) * (0.5f * (1.0f - t)) + 1.0f;
        sy = func_ovl0A_05_80048F70(t * 1080.0f) * (0.5f * (1.0f - t)) + 1.0f;
        D_ovl0A_05_8004990C->unk10 = x - D_ovl0A_05_8004990C->unk28 * sx * 0.5f;
        D_ovl0A_05_8004990C->unk14 = y - D_ovl0A_05_8004990C->unk2C * sy * 0.5f;
        D_ovl0A_05_8004990C->unk18 = D_ovl0A_05_8004990C->unk28 * sx * 0.5f + x;
        D_ovl0A_05_8004990C->unk1C = D_ovl0A_05_8004990C->unk2C * sy * 0.5f + y;
        func_ovl0A_05_80048E10();
    }
    D_ovl0A_05_8004990C->unk10 = 71.0f;
    D_ovl0A_05_8004990C->unk14 = 13.0f;
    D_ovl0A_05_8004990C->unk18 = D_ovl0A_05_8004990C->unk10 + D_ovl0A_05_8004990C->unk28;
    D_ovl0A_05_8004990C->unk1C = D_ovl0A_05_8004990C->unk14 + D_ovl0A_05_8004990C->unk2C;
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_8004333C(void) {
    s32 pad; /* unused: the original frame has this slot */
    s32 flag;
    s32 i;
    f32 v;
    f32 len;

    flag = 1;
    func_ovl0A_05_80048C80(D_ovl0A_05_80049964, 0xF00000);
    func_ovl0A_05_80048C50(D_ovl0A_05_80049964);
    D_ovl0A_05_80049964->unk40->unk20 = 270.0f;
    D_ovl0A_05_80049964->unk68 = 8.0f;
    D_ovl0A_05_80049964->unk6C = 0.01f;
    D_ovl0A_05_80049964->unk70 *= 0.05f;
    for (i = 0; i < 20; i++) {
        D_ovl0A_05_80049964->unk40->unk10 += 5.0f;
        func_ovl0A_05_80048E10();
    }
    D_ovl0A_05_80049964->unk68 = 0.001f;
    D_ovl0A_05_80049964->unk6C = 0.001f;
    D_ovl0A_05_80049964->unk70 = 0.0f;
    func_ovl0A_05_800489A0(D_ovl0A_05_80049964->unk40, 7, 0);
    D_ovl0A_05_80049964->unk40->unk48->unk4->unk8 |= 0x20;
    D_ovl0A_05_80049964->unk40->unk48->unk4->unk8 &= ~0x40;
    func_ovl0A_05_800489A0(D_ovl0A_05_80049964->unk40, 6, 1);
    D_ovl0A_05_80049964->unk40->unk48->unk4->unk14 |= 0x20;
    D_ovl0A_05_80049964->unk40->unk48->unk4->unk14 &= ~0x40;
    len = func_ovl0A_05_800489B8(D_ovl0A_05_80049964->unk40, 1);
    while (!(D_ovl0A_05_80049964->unk40->unk48->unk4->unk8 & 0x40)) {
        if (len * 0.25f <= D_ovl0A_05_80049964->unk40->unk48->unk4->unk10) {
            D_ovl0A_05_80049964->unk40->unk48->unk4->unk14 |= 0x40;
        }
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048DC8(func_ovl0A_05_800438A0, &flag, 0, 0, 0x150);
    func_ovl0A_05_800489A0(D_ovl0A_05_80049964->unk40, 0xB, 0);
    D_ovl0A_05_80049964->unk40->unk48->unk4->unk8 |= 0x20;
    D_ovl0A_05_80049964->unk40->unk48->unk4->unk8 &= ~0x40;
    while (!(D_ovl0A_05_80049964->unk40->unk48->unk4->unk8 & 0x40)) {
        func_ovl0A_05_80048E10();
    }
    flag = 0;
    func_ovl0A_05_800489A0(D_ovl0A_05_80049964->unk40, 0xC, 0);
    D_ovl0A_05_80049964->unk40->unk48->unk4->unk8 |= 0x20;
    D_ovl0A_05_80049964->unk40->unk48->unk4->unk8 &= ~0x40;
    while (!(D_ovl0A_05_80049964->unk40->unk48->unk4->unk8 & 0x40)) {
        func_ovl0A_05_80048E10();
    }
    v = 0;
    for (i = 0; i < 60; i++) {
        D_ovl0A_05_80049964->unk40->unk10 += v;
        D_ovl0A_05_80049964->unk40->unk14 += v;
        v += 0.4f;
        if (v > 10.0f) {
            v = 10.0f;
        }
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048C80(D_ovl0A_05_80049964, 0x01000000);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_80043150(void) {
    s32 n;
    s32 i;
    f32 v;

    func_ovl0A_05_800490C8(0, 0, 0, 0.0f);
    func_ovl0A_05_800490A8(1);
    n = (s32) func_ovl0A_05_80048DF0();
    func_ovl0A_05_80048C78(D_ovl0A_05_80049968, 0x01000000);
    D_ovl0A_05_80049968->unk40->unk18 -= 60.0f * n;
    for (i = 0; i < n; i++) {
        D_ovl0A_05_80049968->unk40->unk18 += 60.0f;
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048DC8(func_ovl0A_05_8004333C, NULL, 0, 0, 0x150);
    func_ovl0A_05_80048DC8(func_ovl0A_05_80044984, NULL, 0, 0, 0x150);
    v = 0.0f;
    for (i = 0; i < 30; i++) {
        D_ovl0A_05_80049968->unk40->unk18 += 60.0f;
        D_ovl0A_05_80049968->unk40->unk14 += v;
        v += 5.0f;
        if (v > 30.0f) {
            v = 30.0f;
        }
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048C80(D_ovl0A_05_80049968, 0x01000000);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_800430D0(void) {
    func_ovl0A_05_80048468(1);
    while (!func_ovl0A_05_80049050(0x400)) {
        func_ovl0A_05_80048E10();
    }
    func_ovl0A_05_80048468(1);
    func_ovl0A_05_800483E0(0);
    func_ovl0A_05_80048DC8(func_ovl0A_05_80043150, (void *) 30, 0, 0, 0x150);
    func_ovl0A_05_80048DD8();
}

void func_ovl0A_05_80043068(void) {
    func_ovl0A_05_80049120(0);
    func_ovl0A_05_80043010();
    func_ovl0A_05_80049540();
}

void func_ovl0A_05_80043010(void) {
    func_ovl0A_05_80048960(D_ovl0A_05_8004990C);
    func_ovl0A_05_80048960(D_ovl0A_05_80049910);
    func_ovl0A_05_80048960(D_ovl0A_05_80049914);
    func_ovl0A_05_80048960(D_ovl0A_05_80049918);
}

