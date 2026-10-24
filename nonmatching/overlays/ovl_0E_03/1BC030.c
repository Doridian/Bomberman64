/*
 * NON_MATCHING: ovl_0E_03's game object, complete: every function and its data
 * (.data 0x490, .rodata 0x70 and .bss 0x60 as the original); .text 0x20
 * short of 0x20C0.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 188, eu 188, jp 188
 *
 * What still differs in us (words):
 * - func_ovl0E_03_80044B78 (185): ovl_0E_02's 800447F8 and ovl_0E_05's
 *   800443B4 (the same code and the same difference): the original also
 *   saves $f26-$f29, which nothing uses, and is 8 words longer (4 saves,
 *   4 restores); everything after the prologue is shifted.
 * - func_ovl0E_03_800430A8 (3): ovl_0E_12's 80043164: `sll t4,s3,5` (the
 *   next call's &D_80046B78[i]) is scheduled before the stores to unk0 and
 *   unk4; the original has it after them. Store order, one line or two, and
 *   the call on their line don't move it.
 */
#include "common.h"

/*
 * ovl_0E_03's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Most of it is ovl_0E_02's
 * code (nonmatching/overlays/ovl_0E_02), with ovl_0E_12's object that a flag
 * replaces (func_ovl0E_03_800430A8, 80043AB8; nonmatching/overlays/ovl_0E_12).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_03_80046C58;

/* a model placed at set-up, with a collision box (unkC-unk12, -1 for none) */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
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
} UnkStruct_ovl0E_03_80046AD0; /* size 0x38 */

/* what replaces D_ovl0E_03_80046B40's model once its flag (unk0) is set */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
} UnkStruct_ovl0E_03_80046B78;

/* the ten movers: each record is passed to its task */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ UnkStructA *unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
} UnkStruct_ovl0E_03_80046758;

/* the eight other movers: two sets of speeds, chosen by func_ovl0E_03_80045568()->unk10 */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
} UnkStruct_ovl0E_03_80046910;

/* what func_ovl0E_03_80045568 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_03_80045568;

/* the argument of func_ovl0E_03_8004483C's task: unk2/unk4 a tile */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} UnkStruct_ovl0E_03_80046C50; /* size 0x8 */

void func_ovl0E_03_80045418(s32);
void func_ovl0E_03_80045430(s32);
f32 func_ovl0E_03_80045440(void);
void func_ovl0E_03_80045458(s32, s32, s32, s32, s32, s32);
void func_ovl0E_03_80045470(f32, f32, f32, s32 *, s32);
s32 func_ovl0E_03_80045488(s32, s32, s32);
void func_ovl0E_03_800454A0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_03_80045500(void (*)(UnkStructA *));
void func_ovl0E_03_80045510(s32, s32, s32);
void func_ovl0E_03_80045550(void (*)(UnkStructA *));
UnkStruct_ovl0E_03_80045568 *func_ovl0E_03_80045568(void);
void func_ovl0E_03_800455C8(void);
void func_ovl0E_03_800455D0(s32, s32, s32);
void func_ovl0E_03_800455D8(void *);
s32 func_ovl0E_03_800455E0(s32, s32, s32, s32);
s32 func_ovl0E_03_800455F8(void);
void func_ovl0E_03_80045600(s32, f32 *);
void func_ovl0E_03_80045610(s32);
void func_ovl0E_03_80045618(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_03_80045628(void);
void func_ovl0E_03_80045660(s32);
void func_ovl0E_03_80045B20(UnkStructA_40 *, s32);
void func_ovl0E_03_80045B28(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl0E_03_80045B60(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_03_80045B68(s32);
void func_ovl0E_03_80045C58(f32, f32, f32);
void func_ovl0E_03_80045C78(f32, f32, f32);
void func_ovl0E_03_80045C80(f32 *, f32 *, f32 *);
void func_ovl0E_03_80045D30(s32);
void func_ovl0E_03_80045D40(f32, f32, f32);
f32 func_ovl0E_03_80045DC0(f32 *, f32 *);
s32 func_ovl0E_03_80045DC8(UnkStructA *, s32);
void func_ovl0E_03_80045E18(UnkStructA *, s32);
void func_ovl0E_03_80045E20(UnkStructA *, s32);
void func_ovl0E_03_80045E30(UnkStructA *);
UnkStructA *func_ovl0E_03_80045E40(s32, s32, s32, s32);
UnkStructA *func_ovl0E_03_80045E50(UnkStructA *);
UnkStructA *func_ovl0E_03_80045E60(s32, s32, f32, f32, f32);
void func_ovl0E_03_80045E98(UnkStructA *);
void func_ovl0E_03_80045F28(UnkStructA *);
s32 func_ovl0E_03_80045F68(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_03_80045F78(void);
void func_ovl0E_03_80045F88(s32);
void *func_ovl0E_03_80045F90(void);
void func_ovl0E_03_80045FB0(void);
s32 func_ovl0E_03_80046128(s32);
void func_ovl0E_03_800461E0(s32);
void func_ovl0E_03_800461E8(s32);
s32 func_ovl0E_03_800461F0(s32);
void func_ovl0E_03_800462B8(s32, s32, s32);
void func_ovl0E_03_800462D0(u32 (*)[3]);
void func_ovl0E_03_800463B8(s32, f32, f32, f32, s32);
void func_ovl0E_03_800463C0(s32, f32 *, s32);
void func_ovl0E_03_80046478(s32, s32, s32);
void func_ovl0E_03_800464F0(s32);
void func_ovl0E_03_80046510(s32, f32, f32, f32);
void func_ovl0E_03_80046518(s32, f32 *);

void func_ovl0E_03_80043010(void);
void func_ovl0E_03_80043020(void);
void func_ovl0E_03_80043040(void);
void func_ovl0E_03_80043060(UnkStruct_ovl0E_03_80046B78 *);
void func_ovl0E_03_800430A8(void);
void func_ovl0E_03_800432F0(void);
void func_ovl0E_03_80043338(void);
void func_ovl0E_03_800433A0(void);
void func_ovl0E_03_80043478(void);
void func_ovl0E_03_800434F0(void);
void func_ovl0E_03_80043528(void);
void func_ovl0E_03_80043550(f32);
void func_ovl0E_03_80043598(void);
void func_ovl0E_03_800436B0(void);
void func_ovl0E_03_800436D0(s32, s32, s32, f32, s32);
void func_ovl0E_03_800436F8(void);
void func_ovl0E_03_8004374C(void);
void func_ovl0E_03_800437A4(void);
void func_ovl0E_03_800437F8(void);
void func_ovl0E_03_80043844(void);
void func_ovl0E_03_80043A68(void);
void func_ovl0E_03_80043AB8(void);
void func_ovl0E_03_80043BA4(void);
void func_ovl0E_03_80043C90(void);
void func_ovl0E_03_80043C98(void);
void func_ovl0E_03_80043CD8(void);
void func_ovl0E_03_80043D10(void);
void func_ovl0E_03_80043E2C(s32);
void func_ovl0E_03_80043F7C(void);
void func_ovl0E_03_800443DC(UnkStruct_ovl0E_03_80046C50 *, s16, s16);
void func_ovl0E_03_80044654(void);
void func_ovl0E_03_80044688(void);
void func_ovl0E_03_8004483C(void);
void func_ovl0E_03_80044B00(void);
void func_ovl0E_03_80044B78(void);
void func_ovl0E_03_80044E94(UnkStructA *);
void func_ovl0E_03_80044F58(UnkStructA *);
void func_ovl0E_03_80044FF0(s32, UnkStructA *);
void func_ovl0E_03_80045024(f32, f32, f32);
void func_ovl0E_03_80045080(void);
void func_ovl0E_03_80045098(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0E_03_80043018(void);
static void func_ovl0E_03_800430A0(void);
static void func_ovl0E_03_800432E8(void);
static void func_ovl0E_03_800438E8(UnkStruct_ovl0E_03_80046AD0 *);
static void func_ovl0E_03_80043388(void);
static void func_ovl0E_03_80043390(void);
static void func_ovl0E_03_80043398(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_03_800432F0() \
    D_ovl0E_03_80046C2C = func_ovl0E_03_800455F8(); func_ovl0E_03_800455D8(&D_ovl0E_03_80046C20); func_ovl0E_03_80045600(D_ovl0E_03_80046C2C, D_ovl0E_03_80046C10)

/* .bss */
f32 D_ovl0E_03_80046C10[4];
Vec3f D_ovl0E_03_80046C20;
s32 D_ovl0E_03_80046C2C;
u8 D_ovl0E_03_80046C30[0x4]; /* unused (func_ovl0E_03_800450C8) */
s32 D_ovl0E_03_80046C34;
s32 D_ovl0E_03_80046C38;
u8 D_ovl0E_03_80046C3C[0x4]; /* unused (func_ovl0E_03_800450C8) */
Vec3f D_ovl0E_03_80046C40;
u8 D_ovl0E_03_80046C4C[0x4]; /* unused (func_ovl0E_03_800450C8) */
UnkStruct_ovl0E_03_80046C50 D_ovl0E_03_80046C50[1];
UnkStruct_ovl0E_03_80046C58 D_ovl0E_03_80046C58;
UnkStructA *D_ovl0E_03_80046C6C;

/* .data */
/* passed to func_ovl0E_03_800462D0: three 12-byte records */
u32 D_ovl0E_03_80046710[][3] = {
    { 0x9D0000, 0x7000E, 4 },
    { 0x9E0002, 0xE, 4 },
    { 2, 0, 4 },
};
/* three 12-byte records, each passed to func_ovl0E_03_80046478 */
u32 D_ovl0E_03_80046734[][3] = {
    { 0, 0, 0xDE },
    { 1, 0xD, 0xEB },
    { 2, 0x22, 0xE0 },
};
UnkStruct_ovl0E_03_80046758 D_ovl0E_03_80046758[10] = {
    { 0, -1, NULL, 650.0f, -3800.0f, 2450.0f, 93.0f, 93.0f, 93.0f, 1.6333334f, -3800.0f },
    { 1, -1, NULL, 750.0f, -3800.0f, 2650.0f, 93.0f, 92.0f, 93.0f, 1.6333334f, -3800.0f },
    { 2, -1, NULL, 650.0f, -3800.0f, 2850.0f, 93.0f, 93.0f, 93.0f, 1.6333334f, -3800.0f },
    { 3, -1, NULL, 1450.0f, -3800.0f, 2450.0f, 90.0f, 85.0f, 90.0f, 1.6333334f, -3800.0f },
    { 4, -1, NULL, 1350.0f, -3800.0f, 2650.0f, 90.0f, 85.0f, 90.0f, 1.6333334f, -3800.0f },
    { 5, -1, NULL, 1450.0f, -3800.0f, 2850.0f, 90.0f, 85.0f, 90.0f, 1.6333334f, -3800.0f },
    { 6, -1, NULL, 2150.0f, -3800.0f, 150.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 7, -1, NULL, 2150.0f, -3800.0f, 550.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 8, -1, NULL, 2150.0f, -3800.0f, 950.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 9, -1, NULL, 2150.0f, -3800.0f, 1350.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
};
UnkStruct_ovl0E_03_80046910 D_ovl0E_03_80046910[8] = {
    { NULL, 650.0f, -3800.0f, -3800.0f, 2450.0f, 190.0f, 185.0f, 195.0f, 3.0f, 1200.0f, 0, 130.0f, 135.0f, 1.5f },
    { NULL, 650.0f, -3800.0f, -3800.0f, 2850.0f, 190.0f, 185.0f, 195.0f, 3.0f, 1200.0f, 0, 130.0f, 135.0f, 1.5f },
    { NULL, 750.0f, -3800.0f, -3800.0f, 2650.0f, 190.0f, 185.0f, 195.0f, 3.0f, 1200.0f, 0, 130.0f, 135.0f, 1.5f },
    { NULL, 1400.0f, -3800.0f, -3800.0f, 2550.0f, 180.0f, 175.0f, 185.0f, 3.0f, 800.0f, 0, 125.0f, 130.0f, 1.5f },
    { NULL, 1400.0f, -3800.0f, -3800.0f, 2750.0f, 180.0f, 175.0f, 185.0f, 3.0f, 800.0f, 0, 125.0f, 130.0f, 1.5f },
    { NULL, 2150.0f, -3800.0f, -3800.0f, 550.0f, 180.0f, 175.0f, 185.0f, 3.0f, 0.0f, 0, 115.0f, 120.0f, 1.5f },
    { NULL, 2150.0f, -3800.0f, -3800.0f, 950.0f, 180.0f, 175.0f, 185.0f, 3.0f, 0.0f, 0, 115.0f, 120.0f, 1.5f },
    { NULL, 2150.0f, -3800.0f, -3800.0f, 1349.0f, 180.0f, 175.0f, 185.0f, 3.0f, 0.0f, 0, 115.0f, 120.0f, 1.5f },
};
UnkStruct_ovl0E_03_80046AD0 D_ovl0E_03_80046AD0[1] = {
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_03_80046AD0 D_ovl0E_03_80046B08[1] = {
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_03_80046AD0 D_ovl0E_03_80046B40[1] = {
    { NULL, -1, 0xA0, -1, -1, -1, -1, 355.0f, -10.0f, 150.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_03_80046B78 D_ovl0E_03_80046B78[1] = {
    { 0x415, 365.0f, -10.0f, 155.0f, 270.0f, 0x24, 0, 0xF, 0x25, 0x10, 1 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0E_03_800450C8(void) {
    D_ovl0E_03_80046C30[0] = D_ovl0E_03_80046C3C[0] + D_ovl0E_03_80046C4C[0];
}

/* Its references keep func_ovl0E_03_80044E94 and 80044F58 in address order
 * after 80044B78 (ovl_0E_02's 80044D48). The body itself isn't emitted. */
static void func_ovl0E_03_800450C0(void) {
    func_ovl0E_03_80045500(func_ovl0E_03_80044F58);
    func_ovl0E_03_80045550(func_ovl0E_03_80044E94);
}

static void func_ovl0E_03_800450B8(void) {
}

static void func_ovl0E_03_800450B0(void) {
}

static void func_ovl0E_03_800450A8(void) {
}

static void func_ovl0E_03_800450A0(void) {
}


void func_ovl0E_03_80045098(void) {
}

void func_ovl0E_03_80045080(void) {
    D_ovl0E_03_80046C34 = -1;
    D_ovl0E_03_80046C38 = -1;
}

void func_ovl0E_03_80045024(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_03_80045C58(D_ovl0E_03_80046C40.x, D_ovl0E_03_80046C40.y, D_ovl0E_03_80046C40.z);
    func_ovl0E_03_80045C78(arg0, arg1, arg2);
    func_ovl0E_03_80045F88(180);
}

void func_ovl0E_03_80044FF0(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_03_80046510(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_03_80044F58(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_03_80045E20(arg0, 0x01000000);
    func_ovl0E_03_800463C0(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_03_800463C0(13, pos, 0);
    func_ovl0E_03_80046518(180, pos);
}

void func_ovl0E_03_80044E94(UnkStructA *arg0) {
    func_ovl0E_03_80045E20(arg0, 0x04000000);
    func_ovl0E_03_80045F88(10);
    func_ovl0E_03_800454A0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_03_800464F0(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_03_80045F88(60);
}

void func_ovl0E_03_80044B78(void) {
    f32 pad[5];
    UnkStruct_ovl0E_03_80046758 *rec;
    f32 a[3];
    f32 b[3];
    f32 pad2[1];

    rec = func_ovl0E_03_80045F90();
    rec->unk8 = func_ovl0E_03_80045E40(0x1BC, 0x0D080040, 0x20, 0);
    rec->unk8->unk40->unkC |= 0x8000;
    func_ovl0E_03_80045E18(rec->unk8, 0x0D080040);
    rec->unk10 = rec->unk28;
    rec->unk8->unk40->unk10 = rec->unkC;
    rec->unk8->unk40->unk14 = rec->unk10;
    rec->unk8->unk40->unk18 = rec->unk14;
    func_ovl0E_03_80045B20(rec->unk8->unk40, 2);
    func_ovl0E_03_80045B28(rec->unk8->unk40, 0x1BD, 0, 0);
    func_ovl0E_03_80045B28(rec->unk8->unk40, 0x1BD, 1, 1);
    rec->unk8->unk30 = 4;
    rec->unk8->unk34 = 50.0f;
    rec->unk8->unk38 = 2500.0f;
    func_ovl0E_03_80045F88(func_ovl0E_03_80046128(60) + 30);
    while (TRUE) {
        func_ovl0E_03_80045F28(rec->unk8);
        rec->unk10 += rec->unk18;
        if (rec->unk10 < rec->unk28) {
            rec->unk10 = rec->unk28;
            rec->unk18 = (f32) func_ovl0E_03_80046128((s32) (rec->unk20 - rec->unk1C)) + rec->unk1C;
            func_ovl0E_03_80045F88(func_ovl0E_03_80046128(60) + 30);
            a[0] = rec->unk8->unk40->unk10;
            a[1] = 0.0f;
            a[2] = rec->unk8->unk40->unk18;
            b[0] = D_ovl0E_03_80046C10[0];
            b[1] = 0.0f;
            b[2] = D_ovl0E_03_80046C10[2];
            if (func_ovl0E_03_80045DC0(a, b) < 800.0f) {
                func_ovl0E_03_80046510(0x75, rec->unk8->unk40->unk10, rec->unk8->unk40->unk14,
                                       rec->unk8->unk40->unk18);
            }
        }
        rec->unk18 -= rec->unk24;
        rec->unk8->unk40->unk20 += 20.0f;
        rec->unk8->unk40->unk14 = rec->unk10;
        func_ovl0E_03_80045FB0();
    }
}

void func_ovl0E_03_80044B00(void) {
    UnkStruct_ovl0E_03_80046758 *rec;
    s16 i;

    for (i = 0, rec = D_ovl0E_03_80046758; i < 10; i++, rec++) {
        rec->unk4 = func_ovl0E_03_80045F68(func_ovl0E_03_80044B78, rec, 0, 0, 0x110);
    }
}

/* drops the model pair from 10000 at the tile its argument gives */
void func_ovl0E_03_8004483C(void) {
    UnkStruct_ovl0E_03_80046C50 *arg;
    UnkStruct_ovl0E_03_80046AD0 *a;
    UnkStruct_ovl0E_03_80046AD0 *b;

    func_ovl0E_03_80045FB0();
    arg = func_ovl0E_03_80045F90();
    a = &D_ovl0E_03_80046AD0[arg->unk0];
    b = &D_ovl0E_03_80046B08[arg->unk0];
    a->unk0->unk40->unk10 = arg->unk2 * 100.0f;
    b->unk0->unk40->unk10 = a->unk0->unk40->unk10;
    a->unk0->unk40->unk14 = 10000.0f;
    b->unk0->unk40->unk14 = a->unk0->unk40->unk14;
    a->unk0->unk40->unk18 = arg->unk4 * 100.0f;
    b->unk0->unk40->unk18 = a->unk0->unk40->unk18 + 10.0f;
    b->unk0->unk68 = 0.0f;
    a->unk0->unk68 = b->unk0->unk68;
    b->unk0->unk70 = 1.6333334f;
    a->unk0->unk70 = b->unk0->unk70;
    func_ovl0E_03_80045E18(a->unk0, 0x01000000);
    func_ovl0E_03_80045E18(b->unk0, 0x01000000);
    while (TRUE) {
        func_ovl0E_03_80045E98(a->unk0);
        b->unk0->unk40->unk14 = a->unk0->unk40->unk14;
        if (a->unk0->unk40->unk14 <= func_ovl0E_03_80045440() ||
            (a->unk0->unk6C == 0.0f && a->unk0->unk68 == 0.0f)) {
            func_ovl0E_03_80045E20(a->unk0, 0x01000000);
            func_ovl0E_03_80045E20(b->unk0, 0x01000000);
            func_ovl0E_03_80046510(0x7C, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
            func_ovl0E_03_800463B8(10, a->unk0->unk40->unk10, a->unk0->unk40->unk14 + 10.0f,
                                   a->unk0->unk40->unk18, 0);
            arg->unk6 |= 1;
            func_ovl0E_03_80045F78();
        }
        func_ovl0E_03_80045FB0();
    }
}

void func_ovl0E_03_80044654(void) {
    func_ovl0E_03_80045D40(20.0f, 20.0f, 20.0f);
    func_ovl0E_03_80045D30(120);
}

void func_ovl0E_03_80044688(void) {
    s16 i;
    s16 j;
    s16 n;
    s32 base;
    s32 range;

    func_ovl0E_03_80045F88(300);
    if (func_ovl0E_03_80045568()->unk10 == 0) {
        n = 2;
        base = 480;
        range = 480;
    } else {
        n = 5;
        base = 240;
        range = 240;
    }
    for (i = 0; i < 1; i++) {
        D_ovl0E_03_80046C50[i].unk0 = i;
    }
    while (TRUE) {
        func_ovl0E_03_80044654();
        func_ovl0E_03_80045F88(60);
        for (i = 0; i < n; i++) {
            for (j = 0; j < 1; j++) {
                D_ovl0E_03_80046C50[j].unk6 = 0;
            }
            func_ovl0E_03_800443DC(D_ovl0E_03_80046C50, 3, 3);
            func_ovl0E_03_80045F68(func_ovl0E_03_8004483C, &D_ovl0E_03_80046C50[0], 0, 0, 0x110);
            func_ovl0E_03_80045FB0();
            while (TRUE) {
                if (D_ovl0E_03_80046C50[0].unk6 & 1) {
                    break;
                }
                func_ovl0E_03_80045FB0();
            }
            func_ovl0E_03_80045FB0();
        }
        func_ovl0E_03_80045F88(func_ovl0E_03_80046128(range) + base);
    }
}

/* picks a tile for each of arg0's entries around the one func_ovl0E_03_80045470
 * gives for func_ovl0E_03_80045600's position, retrying where
 * func_ovl0E_03_80045488 gives 0xF (at most 6 tries) */
void func_ovl0E_03_800443DC(UnkStruct_ovl0E_03_80046C50 *arg0, s16 arg1, s16 arg2) {
    s16 i;
    s16 j;
    s16 tries;
    s16 xs[1];
    s16 ys[1];
    f32 pos[4];
    s32 here[6];
    s32 v[6];

    func_ovl0E_03_80045600(0, pos);
    func_ovl0E_03_80045470(pos[0], pos[1], pos[2], here, 0);
    for (i = 0, tries = 0; i < 1;) {
        xs[i] = func_ovl0E_03_80046128(arg1 * 2);
        ys[i] = func_ovl0E_03_80046128(arg2 * 2);
        if (tries++ >= 6) {
            xs[i] = arg1;
            ys[i] = arg2;
            tries = 0;
            i++;
        } else {
            for (j = 0; j < i; j++) {
                if (xs[i] == xs[j] && ys[i] == ys[j]) {
                    break;
                }
            }
            if (j < i) {
                tries++;
            } else {
                func_ovl0E_03_80045470(0.0f, 10000.0f, 0.0f, v, 0);
                if ((func_ovl0E_03_80045488(here[0] + (xs[i] - arg1), v[1], here[2] + (ys[i] - arg2)) & 0xF) == 0xF) {
                    tries++;
                } else {
                    tries = 0;
                    i++;
                }
            }
        }
    }
    for (i = 0; i < 1; i++) {
        arg0[i].unk2 = here[0] + (xs[i] - arg1);
        arg0[i].unk4 = here[2] + (ys[i] - arg2);
    }
}

void func_ovl0E_03_80043F7C(void) {
    f32 pad[3];
    UnkStruct_ovl0E_03_80046910 *rec;
    s32 up;
    f32 a[3];
    f32 b[3];
    f32 pad2[1];

    rec = func_ovl0E_03_80045F90();
    rec->unk0 = func_ovl0E_03_80045E40(0x1BE, 0x01000040, 0x20, 0);
    func_ovl0E_03_80045E50(rec->unk0);
    rec->unk8 = rec->unkC;
    rec->unk0->unk40->unk10 = rec->unk4;
    rec->unk0->unk40->unk14 = rec->unk8;
    rec->unk0->unk40->unk18 = rec->unk10;
    rec->unk0->unk30 = 1;
    rec->unk0->unk34 = 50.0f;
    rec->unk0->unk38 = 0;
    if (func_ovl0E_03_80045568()->unk10 == 0) {
        rec->unk14 = (f32) func_ovl0E_03_80046128((s32) (rec->unk30 - rec->unk2C)) + rec->unk2C;
    } else {
        rec->unk14 = (f32) func_ovl0E_03_80046128((s32) (rec->unk1C - rec->unk18)) + rec->unk18;
    }
    func_ovl0E_03_80045F88(func_ovl0E_03_80046128(60) + 30);
    up = 0;
    while (TRUE) {
        func_ovl0E_03_80045F28(rec->unk0);
        rec->unk8 += rec->unk14;
        if (rec->unk8 < rec->unkC) {
            rec->unk8 = rec->unkC;
            if (func_ovl0E_03_80045568()->unk10 == 0) {
                rec->unk14 = (f32) func_ovl0E_03_80046128((s32) (rec->unk30 - rec->unk2C)) + rec->unk2C;
            } else {
                rec->unk14 = (f32) func_ovl0E_03_80046128((s32) (rec->unk1C - rec->unk18)) + rec->unk18;
            }
            if (func_ovl0E_03_80045568()->unk10 == 0) {
                up = 0;
                func_ovl0E_03_80045F88(func_ovl0E_03_80046128(60) + 180);
            } else {
                func_ovl0E_03_80045F88(func_ovl0E_03_80046128(60) + 90);
                up = 0;
            }
            a[0] = rec->unk0->unk40->unk10;
            a[1] = 0.0f;
            a[2] = rec->unk0->unk40->unk18;
            b[0] = D_ovl0E_03_80046C10[0];
            b[1] = 0.0f;
            b[2] = D_ovl0E_03_80046C10[2];
            if (func_ovl0E_03_80045DC0(a, b) < 700.0f) {
                func_ovl0E_03_80046510(0x7B, rec->unk0->unk40->unk10, rec->unk0->unk40->unk14,
                                       rec->unk0->unk40->unk18);
            }
        }
        if (func_ovl0E_03_80045568()->unk10 == 0) {
            rec->unk14 -= rec->unk34;
        } else {
            rec->unk14 -= rec->unk20;
        }
        if ((rec->unk24 < rec->unk8 && up == 0) || (rec->unk8 < rec->unk24 && up == 1)) {
            if (up == 1) {
                up = 0;
            } else {
                up = 1;
            }
            func_ovl0E_03_800463B8(7, rec->unk4, rec->unk8 + 100.0f, rec->unk10, 0);
        }
        rec->unk0->unk40->unk14 = rec->unk8;
        func_ovl0E_03_80045FB0();
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_03_80043E2C(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0E_03_80043D10();
            break;
        case 17:
            func_ovl0E_03_800437F8();
            break;
        case 18:
            func_ovl0E_03_800437A4();
            break;
        case 19:
            func_ovl0E_03_8004374C();
            break;
        case 20:
            func_ovl0E_03_800436F8();
            break;
        case 4:
            func_ovl0E_03_800436B0();
            break;
        case 5:
            func_ovl0E_03_80043528();
            break;
        case 0x50:
            func_ovl0E_03_800433A0();
            break;
        case 3:
            func_ovl0E_03_80043338();
            break;
        case 12:
            func_ovl0E_03_80043040();
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_03_80043D10(void) {
    UnkStructA *obj;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_03_80043CD8();
    func_ovl0E_03_800462D0(D_ovl0E_03_80046710);
    func_ovl0E_03_80045418(0x189);
    obj = func_ovl0E_03_80045E60(0x18A, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_03_80045E18(obj, 0x01000000);
    p = D_ovl0E_03_80046734;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl0E_03_80046478((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_03_80045430(0x192);
    func_ovl0E_03_800455C8();
    func_ovl0E_03_80043BA4();
    func_ovl0E_03_80043AB8();
    func_ovl0E_03_80043844();
    func_ovl0E_03_80045B60(obj->unk40, 0, 0, 0, 2, 0x400);
    func_ovl0E_03_800462B8(0xFF, 0xA1, 0x1D);
}

void func_ovl0E_03_80043CD8(void) {
    func_ovl0E_03_80043C98();
    func_ovl0E_03_80045500(func_ovl0E_03_80044F58);
    func_ovl0E_03_80045550(func_ovl0E_03_80044E94);
}

void func_ovl0E_03_80043C98(void) {
    func_ovl0E_03_800461E8(0x400);
    func_ovl0E_03_800461E8(0x401);
    func_ovl0E_03_800461E8(0x402);
    func_ovl0E_03_800461E8(0x403);
    func_ovl0E_03_800461E8(0x404);
}

void func_ovl0E_03_80043C90(void) {
}

void func_ovl0E_03_80043BA4(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 1; i++) {
        func_ovl0E_03_800438E8(&D_ovl0E_03_80046AD0[i]);
        obj = func_ovl0E_03_80045E50(D_ovl0E_03_80046AD0[i].unk0);
        obj->unk54 = 4.0f;
        obj->unk4C = 4.0f;
        obj->unk40->unk36 = 0xCC;
        func_ovl0E_03_80045E20(D_ovl0E_03_80046AD0[i].unk0, 0x80000);
        func_ovl0E_03_80045E20(D_ovl0E_03_80046AD0[i].unk0, 0x01000000);
        func_ovl0E_03_800438E8(&D_ovl0E_03_80046B08[i]);
        func_ovl0E_03_80045E20(D_ovl0E_03_80046B08[i].unk0, 0x01000000);
    }
}

void func_ovl0E_03_80043A68(void) {
    if (func_ovl0E_03_800461F0(0x400) == 0) {
        D_ovl0E_03_80046C6C = func_ovl0E_03_80045E60(-1, 0x80, 0.0f, 0.0f, 0.0f);
        func_ovl0E_03_800461E0(0x400);
    }
}

/* D_ovl0E_03_80046B40's model, or what replaces it once its flag is set */
void func_ovl0E_03_80043AB8(void) {
    s32 i;

    func_ovl0E_03_80043A68();
    for (i = 0; i < 1; i++) {
        if (func_ovl0E_03_800461F0(D_ovl0E_03_80046B78[i].unk0) == 0) {
            func_ovl0E_03_800438E8(&D_ovl0E_03_80046B40[i]);
            func_ovl0E_03_80045E18(D_ovl0E_03_80046B40[i].unk0, 0x02000000);
            func_ovl0E_03_80045E20(D_ovl0E_03_80046B40[i].unk0, 0x80000);
            D_ovl0E_03_80046B40[i].unk0->unk40->unk20 = D_ovl0E_03_80046B78[i].unk10;
        } else {
            func_ovl0E_03_80043060(&D_ovl0E_03_80046B78[i]);
        }
    }
}

static void func_ovl0E_03_800438E8(UnkStruct_ovl0E_03_80046AD0 *e) {
    e->unk0 = func_ovl0E_03_80045E60(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0E_03_80045E18(e->unk0, 0x01080000);
    func_ovl0E_03_80045E20(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl0E_03_80045B60(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
        if (e->unk4 == -1) {
            while (TRUE) {
            }
        }
    }
    e->unk0->unk40->unk10 = e->unk14 * 10.0f;
    e->unk0->unk40->unk14 = e->unk18 * 10.0f;
    e->unk0->unk40->unk18 = e->unk1C * 10.0f;
    e->unk0->unk40->unk1C = e->unk20;
    e->unk0->unk40->unk20 = e->unk24;
    e->unk0->unk40->unk24 = e->unk28;
    e->unk0->unk40->unk28 = e->unk2C;
    e->unk0->unk40->unk2C = e->unk30;
    e->unk0->unk40->unk30 = e->unk34;
}

void func_ovl0E_03_80043844(void) {
    UnkStruct_ovl0E_03_80045568 *state;
    UnkStruct_ovl0E_03_80046910 *rec;
    s16 i;

    state = func_ovl0E_03_80045568();
    for (i = 0, rec = D_ovl0E_03_80046910; i < 8; i++, rec++) {
        if (state->unk10 != 0 || rec->unk28 != 1) {
            func_ovl0E_03_80045F68(func_ovl0E_03_80043F7C, rec, 0, 0, 0x110);
        }
    }
}

void func_ovl0E_03_800437F8(void) {
    func_ovl0E_03_800455D0(0x17, 0, 0xC);
    func_ovl0E_03_800436D0(1, 0x80, 0x80, 0.0f, 0);
}

void func_ovl0E_03_800437A4(void) {
    func_ovl0E_03_800455D0(6, 1, 1);
    func_ovl0E_03_800436D0(2, 0x80, 1, 90.0f, 2);
}

void func_ovl0E_03_8004374C(void) {
    func_ovl0E_03_800455D0(0x28, 1, 1);
    func_ovl0E_03_800436D0(3, 0x80, 1, 90.0f, 2);
}

void func_ovl0E_03_800436F8(void) {
    func_ovl0E_03_800455D0(0x26, 0, 0x10);
    func_ovl0E_03_800436D0(4, 0xC0, 0x40, 0.0f, 3);
}

void func_ovl0E_03_800436D0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_03_80046C58.unk0 = arg0;
    D_ovl0E_03_80046C58.unk4 = arg1;
    D_ovl0E_03_80046C58.unk8 = arg2;
    D_ovl0E_03_80046C58.unkC = arg3;
    D_ovl0E_03_80046C58.unk10 = arg4;
}

void func_ovl0E_03_800436B0(void) {
    func_ovl0E_03_80043598();
}

void func_ovl0E_03_80043598(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_03_80045628();
    switch (D_ovl0E_03_80046C58.unk8) {
        case 0:
            angle = 0.0f;
            break;
        case 0x80:
            angle = 180.0f;
            break;
        case 0xC0:
            angle = 90.0f;
            break;
        case 0x40:
            angle = 270.0f;
            break;
        case 1:
        default:
            angle = 360.0f;
            break;
    }
    if (angle != 360.0f) {
        func_ovl0E_03_80045C78(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_03_80046C58.unkC;
        func_ovl0E_03_80045C80(&sp1C, NULL, NULL);
        func_ovl0E_03_80045C78(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_03_80045610(D_ovl0E_03_80046C58.unk4);
}

void func_ovl0E_03_80043550(f32 arg0) {
    f32 sp1C;

    func_ovl0E_03_80045C80(&sp1C, NULL, NULL);
    func_ovl0E_03_80045C78(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_03_80043528(void) {
    func_ovl0E_03_800434F0();
    func_ovl0E_03_80043478();
}

void func_ovl0E_03_800434F0(void) {
    func_ovl0E_03_80045F68(func_ovl0E_03_80044688, NULL, 0, 0, 0x110);
}

void func_ovl0E_03_80043478(void) {
    UNK_MACRO_ovl0E_03_800432F0();
    func_ovl0E_03_80045618(D_ovl0E_03_80046C58.unk4, 3, 4.0f, D_ovl0E_03_80046C58.unk10, 0, 1, 1);
}

void func_ovl0E_03_800433A0(void) {
    func_ovl0E_03_80043388();
    func_ovl0E_03_80043390();
    func_ovl0E_03_80043398();
    if (func_ovl0E_03_800455E0(6, 1, 7, 1) != 0) {
        D_ovl0E_03_80046C34 = 0x4B;
        D_ovl0E_03_80046C38 = 0x12;
        func_ovl0E_03_80045510(0x4B, 0x12, 0);
    }
    if (func_ovl0E_03_800455E0(0x28, 1, 0x29, 1) != 0) {
        D_ovl0E_03_80046C34 = 0x49;
        D_ovl0E_03_80046C38 = 0x12;
        func_ovl0E_03_80045510(0x49, 0x12, 0);
    }
    if (func_ovl0E_03_800455E0(0x26, 0xF, 0x26, 0x10) != 0) {
        D_ovl0E_03_80046C34 = 0x4F;
        D_ovl0E_03_80046C38 = 0x12;
        func_ovl0E_03_80045510(0x4F, 0x12, 0);
    }
}

static void func_ovl0E_03_80043398(void) {
}

static void func_ovl0E_03_80043390(void) {
}

static void func_ovl0E_03_80043388(void) {
}

void func_ovl0E_03_80043338(void) {
    UNK_MACRO_ovl0E_03_800432F0();
    func_ovl0E_03_800430A8();
}

void func_ovl0E_03_800432F0(void) {
    func_ovl0E_03_800432E8();
    UNK_MACRO_ovl0E_03_800432F0();
}

static void func_ovl0E_03_800432E8(void) {
}

void func_ovl0E_03_800430A8(void) {
    UnkStruct_ovl0E_03_80046B78 *p;
    s16 i;
    s32 flags;

    func_ovl0E_03_800430A0();
    D_ovl0E_03_80046C6C->unk30 = 4;
    D_ovl0E_03_80046C6C->unk34 = 85.0f;
    D_ovl0E_03_80046C6C->unk38 = 400.0f;
    for (i = 0, p = D_ovl0E_03_80046B78; i < 1; i++, p++) {
        if (func_ovl0E_03_800461F0(p->unk0) == 0) {
            D_ovl0E_03_80046C6C->unk40->unk10 = p->unk4 * 10.0f;
            D_ovl0E_03_80046C6C->unk40->unk14 = p->unk8 * 10.0f;
            D_ovl0E_03_80046C6C->unk40->unk18 = p->unkC * 10.0f;
            flags = func_ovl0E_03_80045DC8(D_ovl0E_03_80046C6C, 0xC0);
            if (flags != 0) {
                if (flags & 0x4000) {
                    func_ovl0E_03_80046510(0x49, D_ovl0E_03_80046C6C->unk40->unk10, D_ovl0E_03_80046C6C->unk40->unk14,
                                           D_ovl0E_03_80046C6C->unk40->unk18);
                    func_ovl0E_03_80045E20(D_ovl0E_03_80046B40[i].unk0, 0x01000000);
                    func_ovl0E_03_80045E30(D_ovl0E_03_80046B40[i].unk0);
                    /* 0xFFFF, not -1: never equal to the s16 fields */
                    if (D_ovl0E_03_80046B40[i].unkC != 0xFFFF && D_ovl0E_03_80046B40[i].unkE != 0xFFFF &&
                        D_ovl0E_03_80046B40[i].unk10 != 0xFFFF && D_ovl0E_03_80046B40[i].unk12 != 0xFFFF) {
                        func_ovl0E_03_80045B68(D_ovl0E_03_80046B40[i].unk4);
                    }
                    D_ovl0E_03_80046B40[i].unk0 = NULL;
                    D_ovl0E_03_80046B40[i].unk4 = -1;
                    func_ovl0E_03_80043060(&D_ovl0E_03_80046B78[i]);
                    func_ovl0E_03_800461E0(p->unk0);
                } else {
                    func_ovl0E_03_80046510(0x26, D_ovl0E_03_80046C6C->unk40->unk10, D_ovl0E_03_80046C6C->unk40->unk14,
                                           D_ovl0E_03_80046C6C->unk40->unk18);
                }
            }
        }
    }
}

static void func_ovl0E_03_800430A0(void) {
}

void func_ovl0E_03_80043060(UnkStruct_ovl0E_03_80046B78 *arg0) {
    func_ovl0E_03_80045458(arg0->unk14, arg0->unk16, arg0->unk18, arg0->unk1A, arg0->unk1C, arg0->unk1E);
}

void func_ovl0E_03_80043040(void) {
    func_ovl0E_03_80045660(1);
}

void func_ovl0E_03_80043020(void) {
    func_ovl0E_03_80043018();
    func_ovl0E_03_80045660(1);
}

static void func_ovl0E_03_80043018(void) {
}

void func_ovl0E_03_80043010(void) {
}
