/*
 * NON_MATCHING: ovl_0E_04's game object, complete: every function and its data
 * (.data 0x410, .rodata 0xB0 and .bss 0x60 as the original); .text 0x30
 * short of 0x23F0.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 216, eu 216, jp 216
 *
 * What still differs in us (words):
 * - func_ovl0E_04_80044EB4 (195): ovl_0E_05's 800443B4 (the same code and
 *   the same difference): the original also saves $f26-$f29, which nothing
 *   uses, and is 12 words longer; everything after the prologue is shifted.
 * - func_ovl0E_04_800439A4 (17): ovl_12_01's 80043190 (the same camera
 *   set-up, func_ovl0E_04_8004399C): the original saves s1/s2 and sets
 *   &D_ovl0E_04_80046F30 and the count before computing x, and stores y
 *   before x. The copies inlined into func_ovl0E_04_80043DD4 and
 *   func_ovl0E_04_80044274 match.
 * - func_ovl0E_04_80043158 (2): ovl_12_01's 80043754: the `lui a0` of
 *   D_ovl0E_04_80046F20 is scheduled before `sw ra`; the original has it
 *   after.
 * - func_ovl0E_04_80043B4C (2): ovl_0E_05's 80043860: `move a1,s4` is
 *   scheduled into a load delay slot where the original has it in a call's
 *   delay slot.
 */
#include "common.h"

/*
 * ovl_0E_04's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Much of it is ovl_0E_05's
 * code (nonmatching/overlays/ovl_0E_05) and ovl_0E_02's, with ovl_12_01's
 * camera set-up (func_ovl0E_04_8004399C).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_04_80046F40;

/* an object placed at set-up, with a collision box (unkC-unk12, -1 for none) */
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
} UnkStruct_ovl0E_04_80046D70;

/* the eight movers: each record is passed to its task */
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
} UnkStruct_ovl0E_04_80046A88;

/* the other movers: two sets of speeds, chosen by func_ovl0E_04_80045898()->unk10 */
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
} UnkStruct_ovl0E_04_80046BE8;

/* three objects that are swapped for another model when their flag (unk20)
 * is set, and back after a while (unk1C) */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ UnkStructA *unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} UnkStruct_ovl0E_04_80046DE0;

/* what func_ovl0E_04_80045898 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_04_80045898;

void func_ovl0E_04_80045748(s32);
void func_ovl0E_04_80045760(s32);
void func_ovl0E_04_80045788(s32, s32, s32, s32, s32, s32);
s32 func_ovl0E_04_800457B0(s32);
void func_ovl0E_04_800457D0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_04_80045830(void (*)(UnkStructA *));
void func_ovl0E_04_80045840(s32, s32, s32);
void func_ovl0E_04_80045868(void);
void func_ovl0E_04_80045880(void (*)(UnkStructA *));
UnkStruct_ovl0E_04_80045898 *func_ovl0E_04_80045898(void);
void func_ovl0E_04_800458B0(s32);
void func_ovl0E_04_800458B8(s32);
void func_ovl0E_04_800458F8(void);
void func_ovl0E_04_80045900(s32, s32, s32);
void func_ovl0E_04_80045908(void *);
s32 func_ovl0E_04_80045910(s32, s32, s32, s32);
s32 func_ovl0E_04_80045928(void);
void func_ovl0E_04_80045930(s32, void *);
void func_ovl0E_04_80045938(s32);
void func_ovl0E_04_80045940(s32);
void func_ovl0E_04_80045948(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_04_80045950(const char *);
void func_ovl0E_04_80045958(void);
void func_ovl0E_04_80045990(s32);
void func_ovl0E_04_800459F8(void);
void func_ovl0E_04_80045E50(UnkStructA_40 *, s32);
void func_ovl0E_04_80045E58(UnkStructA_40 *, s32, s32, s32);
f32 func_ovl0E_04_80045E88(UnkStructA_40 *, s32);
s32 func_ovl0E_04_80045E90(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_04_80045E98(s32);
void func_ovl0E_04_80045F88(f32, f32, f32);
void func_ovl0E_04_80045FA8(f32, f32, f32);
void func_ovl0E_04_80045FB0(f32 *, f32 *, f32 *);
void func_ovl0E_04_80045FE8(s32);
void func_ovl0E_04_80045FF0(s32);
void func_ovl0E_04_80046000(s32);
void func_ovl0E_04_80046078(void *);
void func_ovl0E_04_800460A8(void);
void func_ovl0E_04_800460B0(void);
f32 func_ovl0E_04_800460F0(f32 *, f32 *);
void func_ovl0E_04_80046148(UnkStructA *, s32);
void func_ovl0E_04_80046150(UnkStructA *, s32);
void func_ovl0E_04_80046160(UnkStructA *);
UnkStructA *func_ovl0E_04_80046170(s32, s32, s32, s32);
void func_ovl0E_04_80046180(UnkStructA *);
UnkStructA *func_ovl0E_04_80046190(s32, s32, f32, f32, f32);
void func_ovl0E_04_80046258(UnkStructA *);
s32 func_ovl0E_04_80046298(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_04_800462A8(void);
void func_ovl0E_04_800462B8(s32);
void *func_ovl0E_04_800462C0(void);
void func_ovl0E_04_800462E0(void);
s32 func_ovl0E_04_80046458(s32);
void func_ovl0E_04_80046510(s32);
void func_ovl0E_04_80046518(s32);
s32 func_ovl0E_04_80046520(s32);
void func_ovl0E_04_800465E8(s32, s32, s32);
void func_ovl0E_04_80046600(u32 (*)[3]);
void func_ovl0E_04_800466E8(s32, f32, f32, f32, s32);
s32 func_ovl0E_04_800466F0(s32, f32 *, s32);
void func_ovl0E_04_800466F8(s32);
void func_ovl0E_04_800467A8(s32, s32, s32);
void func_ovl0E_04_80046820(s32);
void func_ovl0E_04_80046840(s32, f32, f32, f32);
void func_ovl0E_04_80046848(s32, f32 *);
void func_ovl0E_04_80046998(void);
void func_ovl0E_04_800469A0(void);

void func_ovl0E_04_80043010(void);
void func_ovl0E_04_80043018(void);
void func_ovl0E_04_80043038(void);
void func_ovl0E_04_80043068(void);
void func_ovl0E_04_80043088(void);
void func_ovl0E_04_800430B0(void);
void func_ovl0E_04_800430F8(void);
void func_ovl0E_04_80043158(void);
void func_ovl0E_04_80043190(void);
void func_ovl0E_04_80043264(void);
void func_ovl0E_04_800432FC(void);
void func_ovl0E_04_80043374(void);
void func_ovl0E_04_8004339C(void);
void func_ovl0E_04_80043408(void);
void func_ovl0E_04_80043468(UnkStruct_ovl0E_04_80046D70 *);
void func_ovl0E_04_800434C4(f32);
void func_ovl0E_04_8004350C(void);
void func_ovl0E_04_80043624(void);
void func_ovl0E_04_80043680(s32, s32, s32, f32, s32);
void func_ovl0E_04_800436A8(void);
void func_ovl0E_04_800436F8(void);
void func_ovl0E_04_80043748(void);
void func_ovl0E_04_8004379C(void);
void func_ovl0E_04_80043840(s16, s16);
void func_ovl0E_04_80043908(void);
void func_ovl0E_04_800439A4(void);
void func_ovl0E_04_80043AFC(void);
void func_ovl0E_04_80043B4C(void);
void func_ovl0E_04_80043D5C(void);
void func_ovl0E_04_80043D9C(void);
void func_ovl0E_04_80043DD4(void);
void func_ovl0E_04_80043FB8(s32);
void func_ovl0E_04_80044124(void);
void func_ovl0E_04_80044170(void);
void func_ovl0E_04_80044274(void);
void func_ovl0E_04_8004447C(void);
void func_ovl0E_04_800444B4(void);
void func_ovl0E_04_80044540(void);
void func_ovl0E_04_80044670(void);
void func_ovl0E_04_80044924(void);
void func_ovl0E_04_80044988(void);
void func_ovl0E_04_800449E8(void);
void func_ovl0E_04_80044E3C(void);
void func_ovl0E_04_80044EB4(void);
void func_ovl0E_04_800451D4(UnkStructA *);
void func_ovl0E_04_80045298(UnkStructA *);
void func_ovl0E_04_80045330(s32, UnkStructA *);
void func_ovl0E_04_80045364(f32, f32, f32);
void func_ovl0E_04_800453C0(void);
void func_ovl0E_04_800453D8(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0E_04_800430A8(void);
static void func_ovl0E_04_80043AF4(void);
static void func_ovl0E_04_80043D54(void);
static void func_ovl0E_04_80043140(void);
static void func_ovl0E_04_80043148(void);
static void func_ovl0E_04_80043150(void);
static void func_ovl0E_04_80043188(void);
/* the camera's position, inlined into its three callers */
static void func_ovl0E_04_8004399C(f32, s32, s32);
/* takes its record in s0 */
static void func_ovl0E_04_80043A78(UnkStruct_ovl0E_04_80046D70 *);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_04_800430B0() \
    D_ovl0E_04_80046F1C = func_ovl0E_04_80045928(); func_ovl0E_04_80045908(&D_ovl0E_04_80046F10); func_ovl0E_04_80045930(D_ovl0E_04_80046F1C, D_ovl0E_04_80046F00)

/* .bss */
f32 D_ovl0E_04_80046F00[4];
Vec3f D_ovl0E_04_80046F10;
s32 D_ovl0E_04_80046F1C;
s32 D_ovl0E_04_80046F20;
s32 D_ovl0E_04_80046F24;
s32 D_ovl0E_04_80046F28;
u8 D_ovl0E_04_80046F2C[0x4]; /* unused (func_ovl0E_04_800453F8) */
f32 D_ovl0E_04_80046F30[3];
u8 D_ovl0E_04_80046F3C[0x4]; /* unused (func_ovl0E_04_800453F8) */
UnkStruct_ovl0E_04_80046F40 D_ovl0E_04_80046F40;
UnkStructA *D_ovl0E_04_80046F54;

/* .data */
/* passed to func_ovl0E_04_80046600: three 12-byte records */
u32 D_ovl0E_04_80046A40[][3] = {
    { 0x9D0000, 0xC000E, 4 },
    { 0x9E0002, 0xE, 4 },
    { 2, 0, 4 },
};
/* three 12-byte records, each passed to func_ovl0E_04_800467A8 */
u32 D_ovl0E_04_80046A64[][3] = {
    { 0, 0, 0xDE },
    { 1, 0xD, 0xEB },
    { 2, 0x22, 0xE0 },
};
UnkStruct_ovl0E_04_80046A88 D_ovl0E_04_80046A88[8] = {
    { 0, -1, NULL, 250.0f, -4100.0f, 1050.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4100.0f },
    { 1, -1, NULL, 550.0f, -4100.0f, 950.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4100.0f },
    { 2, -1, NULL, 650.0f, -4100.0f, 650.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4100.0f },
    { 3, -1, NULL, 850.0f, -4100.0f, 950.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4100.0f },
    { 4, -1, NULL, 1150.0f, -4100.0f, 950.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4100.0f },
    { 5, -1, NULL, 3250.0f, -4100.0f, 2250.0f, 90.0f, 88.0f, 90.0f, 1.6333334f, -4100.0f },
    { 6, -1, NULL, 3550.0f, -4100.0f, 2550.0f, 90.0f, 90.0f, 90.0f, 1.6333334f, -4100.0f },
    { 7, -1, NULL, 4050.0f, -4100.0f, 2850.0f, 90.0f, 88.0f, 90.0f, 1.6333334f, -4100.0f },
};
UnkStruct_ovl0E_04_80046BE8 D_ovl0E_04_80046BE8[7] = {
    { NULL, 650.0f, -2100.0f, -2100.0f, 1150.0f, 140.0f, 135.0f, 145.0f, 3.0f, 400.0f, 0, 95.0f, 105.0f, 1.5f },
    { NULL, 950.0f, -2100.0f, -2100.0f, 1050.0f, 140.0f, 135.0f, 145.0f, 3.0f, 400.0f, 0, 95.0f, 105.0f, 1.5f },
    { NULL, 1250.0f, -2100.0f, -2100.0f, 1150.0f, 140.0f, 135.0f, 145.0f, 3.0f, 400.0f, 0, 95.0f, 105.0f, 1.5f },
    { NULL, 2750.0f, -2100.0f, -2100.0f, 2550.0f, 170.0f, 165.0f, 175.0f, 3.0f, 1500.0f, 1, 165.0f, 175.0f, 3.0f },
    { NULL, 3150.0f, -2100.0f, -2100.0f, 2550.0f, 160.0f, 155.0f, 165.0f, 3.0f, 1100.0f, 1, 155.0f, 165.0f, 3.0f },
    { NULL, 3550.0f, -2100.0f, -2100.0f, 2250.0f, 150.0f, 145.0f, 155.0f, 3.0f, 800.0f, 1, 145.0f, 155.0f, 3.0f },
    { NULL, 3550.0f, -2100.0f, -2100.0f, 2550.0f, 150.0f, 145.0f, 155.0f, 3.0f, 800.0f, 1, 145.0f, 155.0f, 3.0f },
};
UnkStruct_ovl0E_04_80046D70 D_ovl0E_04_80046D70[2] = {
    { NULL, -1, 0x1AE, -1, -1, -1, -1, 90.0f, 40.0f, 15.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1AF, -1, -1, -1, -1, 90.0f, 0.0f, 40.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_04_80046DE0 D_ovl0E_04_80046DE0[3] = {
    { 0, -1, NULL, 670.0f, 400.0f, 430.0f, 0.0f, 0, 0x401 },
    { 1, -1, NULL, 1200.0f, 400.0f, 650.0f, 315.0f, 0, 0x402 },
    { 2, -1, NULL, 1420.0f, 600.0f, 1000.0f, 270.0f, 0, 0x403 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0E_04_800453F8(void) {
    D_ovl0E_04_80046F2C[0] = D_ovl0E_04_80046F3C[0];
}

static void func_ovl0E_04_800453F0(void) {
}

static void func_ovl0E_04_800453E8(void) {
}

static void func_ovl0E_04_800453E0(void) {
}

void func_ovl0E_04_800453D8(void) {
}

void func_ovl0E_04_800453C0(void) {
    D_ovl0E_04_80046F24 = -1;
    D_ovl0E_04_80046F28 = -1;
}

void func_ovl0E_04_80045364(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_04_80045F88(D_ovl0E_04_80046F30[0], D_ovl0E_04_80046F30[1], D_ovl0E_04_80046F30[2]);
    func_ovl0E_04_80045FA8(arg0, arg1, arg2);
    func_ovl0E_04_800462B8(180);
}

void func_ovl0E_04_80045330(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_04_80046840(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_04_80045298(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_04_80046150(arg0, 0x01000000);
    func_ovl0E_04_800466F0(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_04_800466F0(13, pos, 0);
    func_ovl0E_04_80046848(180, pos);
}

void func_ovl0E_04_800451D4(UnkStructA *arg0) {
    func_ovl0E_04_80046150(arg0, 0x04000000);
    func_ovl0E_04_800462B8(10);
    func_ovl0E_04_800457D0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_04_80046820(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_04_800462B8(60);
}

void func_ovl0E_04_80044EB4(void) {
    f32 pad[5];
    UnkStruct_ovl0E_04_80046A88 *rec;
    f32 a[3];
    f32 b[3];
    f32 pad2[1];

    rec = func_ovl0E_04_800462C0();
    rec->unk8 = func_ovl0E_04_80046170(0x1BC, 0x0D080040, 0x20, 0);
    rec->unk8->unk40->unkC |= 0x8000;
    func_ovl0E_04_80046148(rec->unk8, 0x0D080040);
    rec->unk10 = rec->unk28;
    rec->unk8->unk40->unk10 = rec->unkC;
    rec->unk8->unk40->unk14 = rec->unk10;
    rec->unk8->unk40->unk18 = rec->unk14;
    func_ovl0E_04_80045E50(rec->unk8->unk40, 2);
    func_ovl0E_04_80045E58(rec->unk8->unk40, 0x1BD, 0, 0);
    func_ovl0E_04_80045E58(rec->unk8->unk40, 0x1BD, 1, 1);
    rec->unk8->unk30 = 4;
    rec->unk8->unk34 = 50.0f;
    rec->unk8->unk38 = 2500.0f;
    func_ovl0E_04_800462B8(func_ovl0E_04_80046458(60) + 30);
    while (TRUE) {
        func_ovl0E_04_80046258(rec->unk8);
        rec->unk10 += rec->unk18;
        if (rec->unk10 < rec->unk28) {
            rec->unk10 = rec->unk28;
            rec->unk18 = (f32) func_ovl0E_04_80046458((s32) (rec->unk20 - rec->unk1C)) + rec->unk1C;
            func_ovl0E_04_800462B8(func_ovl0E_04_80046458(60) + 30);
            a[0] = rec->unk8->unk40->unk10;
            a[1] = 0.0f;
            a[2] = rec->unk8->unk40->unk18;
            b[0] = D_ovl0E_04_80046F00[0];
            b[1] = 0.0f;
            b[2] = D_ovl0E_04_80046F00[2];
            if (func_ovl0E_04_800460F0(a, b) < 800.0f) {
                func_ovl0E_04_80046840(0x75, rec->unk8->unk40->unk10, rec->unk8->unk40->unk14,
                                       rec->unk8->unk40->unk18);
            }
        }
        rec->unk18 -= rec->unk24;
        rec->unk8->unk40->unk20 += 20.0f;
        rec->unk8->unk40->unk14 = rec->unk10;
        func_ovl0E_04_800462E0();
    }
}

void func_ovl0E_04_80043D9C(void) {
    func_ovl0E_04_80043D5C();
    func_ovl0E_04_80045830(func_ovl0E_04_80045298);
    func_ovl0E_04_80045880(func_ovl0E_04_800451D4);
}

void func_ovl0E_04_80044E3C(void) {
    UnkStruct_ovl0E_04_80046A88 *rec;
    s16 i;

    for (i = 0, rec = D_ovl0E_04_80046A88; i < 8; i++, rec++) {
        rec->unk4 = func_ovl0E_04_80046298(func_ovl0E_04_80044EB4, rec, 0, 0, 0x110);
    }
}

void func_ovl0E_04_800449E8(void) {
    f32 pad[3];
    UnkStruct_ovl0E_04_80046BE8 *rec;
    s32 up;
    f32 a[3];
    f32 b[3];
    f32 pad2[1];

    rec = func_ovl0E_04_800462C0();
    rec->unk0 = func_ovl0E_04_80046170(0x1BE, 0x01000040, 0x20, 0);
    func_ovl0E_04_80046180(rec->unk0);
    rec->unk8 = rec->unkC;
    rec->unk0->unk40->unk10 = rec->unk4;
    rec->unk0->unk40->unk14 = rec->unk8;
    rec->unk0->unk40->unk18 = rec->unk10;
    rec->unk0->unk30 = 1;
    rec->unk0->unk34 = 50.0f;
    rec->unk0->unk38 = 0;
    if (func_ovl0E_04_80045898()->unk10 == 0) {
        rec->unk14 = (f32) func_ovl0E_04_80046458((s32) (rec->unk30 - rec->unk2C)) + rec->unk2C;
    } else {
        rec->unk14 = (f32) func_ovl0E_04_80046458((s32) (rec->unk1C - rec->unk18)) + rec->unk18;
    }
    func_ovl0E_04_800462B8(func_ovl0E_04_80046458(60) + 30);
    up = 0;
    while (TRUE) {
        func_ovl0E_04_80046258(rec->unk0);
        rec->unk8 += rec->unk14;
        if (rec->unk8 < rec->unkC) {
            rec->unk8 = rec->unkC;
            if (func_ovl0E_04_80045898()->unk10 == 0) {
                rec->unk14 = (f32) func_ovl0E_04_80046458((s32) (rec->unk30 - rec->unk2C)) + rec->unk2C;
            } else {
                rec->unk14 = (f32) func_ovl0E_04_80046458((s32) (rec->unk1C - rec->unk18)) + rec->unk18;
            }
            if (func_ovl0E_04_80045898()->unk10 == 0) {
                up = 0;
                func_ovl0E_04_800462B8(func_ovl0E_04_80046458(60) + 180);
            } else {
                func_ovl0E_04_800462B8(func_ovl0E_04_80046458(60) + 90);
                up = 0;
            }
            a[0] = rec->unk0->unk40->unk10;
            a[1] = 0.0f;
            a[2] = rec->unk0->unk40->unk18;
            b[0] = D_ovl0E_04_80046F00[0];
            b[1] = 0.0f;
            b[2] = D_ovl0E_04_80046F00[2];
            if (func_ovl0E_04_800460F0(a, b) < 700.0f) {
                func_ovl0E_04_80046840(0x7B, rec->unk0->unk40->unk10, rec->unk0->unk40->unk14,
                                       rec->unk0->unk40->unk18);
            }
        }
        if (func_ovl0E_04_80045898()->unk10 == 0) {
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
            func_ovl0E_04_800466E8(7, rec->unk4, rec->unk8 + 100.0f, rec->unk10, 0);
        }
        rec->unk0->unk40->unk14 = rec->unk8;
        func_ovl0E_04_800462E0();
    }
}

void func_ovl0E_04_80044988(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0E_04_80046D70[i].unk0 != NULL) {
            func_ovl0E_04_80043A78(&D_ovl0E_04_80046D70[i]);
        }
    }
}

void func_ovl0E_04_80044924(void) {
    s32 i;

    for (i = 52; i != 0; i--) {
        func_ovl0E_04_800462E0();
    }
    func_ovl0E_04_80046820(0x80);
    func_ovl0E_04_800466E8(0x10, 850.0f, 500.0f, 850.0f, 0);
    func_ovl0E_04_800462A8();
}

void func_ovl0E_04_80044670(void) {
    UnkStruct_ovl0E_04_80046DE0 *rec;
    UnkStructA *obj;
    s32 i;

    rec = func_ovl0E_04_800462C0();
    obj = rec->unk8;
    obj->unk30 = 1;
    obj->unk34 = 50.0f;
    obj->unk38 = 100.0f;
    while (TRUE) {
        if (func_ovl0E_04_80046520(0x417) != 0) {
            func_ovl0E_04_800462A8();
        }
        if (func_ovl0E_04_80046520(rec->unk20) != 0) {
            rec->unk1C--;
            if (rec->unk1C <= 0) {
                func_ovl0E_04_80046160(obj);
                i = 0;
                func_ovl0E_04_80043840(rec->unk0, 0);
                obj = rec->unk8;
                obj->unk30 = 1;
                obj->unk34 = 50.0f;
                obj->unk38 = 100.0f;
                func_ovl0E_04_80046148(obj, 0x04000000);
                func_ovl0E_04_80046518(rec->unk20);
                while (!(obj->unk40->unkC & 0x40)) {
                    if (i == 25) {
                        func_ovl0E_04_80046820(0x7F);
                    }
                    func_ovl0E_04_800462E0();
                    i++;
                }
                func_ovl0E_04_80046820(0x2A);
            }
        } else {
            obj->unkC = 2;
            if (obj->unk10 & 2) {
                func_ovl0E_04_80046160(obj);
                i = 0;
                func_ovl0E_04_80043840(rec->unk0, 1);
                obj = rec->unk8;
                obj->unk30 = 1;
                obj->unk34 = 50.0f;
                obj->unk38 = 100.0f;
                func_ovl0E_04_80046148(obj, 0x04000000);
                while (!(obj->unk40->unkC & 0x40)) {
                    if (i == 25) {
                        func_ovl0E_04_80046820(0x7F);
                    }
                    func_ovl0E_04_800462E0();
                    i++;
                }
                func_ovl0E_04_80046820(0x29);
                func_ovl0E_04_80046510(rec->unk20);
                if (func_ovl0E_04_80046520(0x401) != 0 && func_ovl0E_04_80046520(0x402) != 0 &&
                    func_ovl0E_04_80046520(0x403) != 0) {
                    func_ovl0E_04_80046510(0x417);
                    func_ovl0E_04_80044540();
                }
                if (func_ovl0E_04_80045898()->unk10 == 0) {
                    rec->unk1C = 1200;
                } else {
                    rec->unk1C = 360;
                }
            }
        }
        func_ovl0E_04_800462E0();
    }
}

void func_ovl0E_04_80044540(void) {
    func_ovl0E_04_800444B4();
    func_ovl0E_04_80046148(D_ovl0E_04_80046D70[0].unk0, 0x04000000);
    func_ovl0E_04_80046820(0x7D);
    func_ovl0E_04_8004447C();
    func_ovl0E_04_80046150(D_ovl0E_04_80046D70[1].unk0, 0x01000000);
    func_ovl0E_04_800466E8(0xD, D_ovl0E_04_80046D70[1].unk0->unk40->unk10,
                           D_ovl0E_04_80046D70[1].unk0->unk40->unk14 + 100.0f,
                           D_ovl0E_04_80046D70[1].unk0->unk40->unk18, 0);
    func_ovl0E_04_800466E8(0xD, D_ovl0E_04_80046D70[1].unk0->unk40->unk10,
                           D_ovl0E_04_80046D70[1].unk0->unk40->unk14 + 300.0f,
                           D_ovl0E_04_80046D70[1].unk0->unk40->unk18, 0);
    while (!(D_ovl0E_04_80046D70[0].unk0->unk40->unkC & 0x40)) {
        func_ovl0E_04_800462E0();
    }
    func_ovl0E_04_80043408();
    func_ovl0E_04_80044274();
    func_ovl0E_04_80046510(0x406);
}

void func_ovl0E_04_800444B4(void) {
    func_ovl0E_04_800459F8();
    func_ovl0E_04_80045990(1);
    func_ovl0E_04_800462B8(30);
    func_ovl0E_04_800458B8(1);
    func_ovl0E_04_800458B0(0);
    func_ovl0E_04_800460A8();
    func_ovl0E_04_80045FF0(0x7F);
    func_ovl0E_04_80045F88(900.0f, 400.0f, 1000.0f);
    func_ovl0E_04_80045FA8(-45.0f, 30.0f, 2500.0f);
    func_ovl0E_04_800462B8(30);
}

void func_ovl0E_04_8004447C(void) {
    func_ovl0E_04_80046298(func_ovl0E_04_80044924, NULL, 0, 0, 0x110);
}

void func_ovl0E_04_80044274(void) {
    f32 a;
    f32 c;
    f32 z;

    for (a = -45.0f, c = 2500.0f, z = 1000.0f; a < 0.0f; a += 0.75f, c -= 25.0f, z -= 13.333333f) {
        func_ovl0E_04_80045F88(900.0f, 400.0f, z);
        func_ovl0E_04_80045FA8(a, 30.0f, c);
        func_ovl0E_04_800462E0();
    }
    func_ovl0E_04_800462B8(20);
    func_ovl0E_04_80046820(0x2C);
    func_ovl0E_04_800439A4();
    func_ovl0E_04_800462B8(120);
    func_ovl0E_04_800460B0();
    func_ovl0E_04_80046078(D_ovl0E_04_80046F00);
    func_ovl0E_04_80045FE8(0x1F);
    func_ovl0E_04_800458B8(0);
    func_ovl0E_04_800458B0(1);
    func_ovl0E_04_80045990(0);
}

void func_ovl0E_04_80044170(void) {
    f32 a;

    func_ovl0E_04_800458B0(0);
    func_ovl0E_04_80045950("WM1 WG1 WAP WSH WDS WB7 ST1 WDW WB12 ST1");
    func_ovl0E_04_80045950("WM1 WG1 WAP WSH ST1");
    for (a = 45.0f; a < 225.0f; a += 0.5f) {
        func_ovl0E_04_80045FA8(a, 32768.0f, 32768.0f);
        func_ovl0E_04_800462E0();
    }
    func_ovl0E_04_80045FA8(225.0f, 32768.0f, 32768.0f);
    func_ovl0E_04_800462B8(30);
    func_ovl0E_04_80046998();
    func_ovl0E_04_800462A8();
}

void func_ovl0E_04_80044124(void) {
    func_ovl0E_04_80045900(0, 0, 0x14);
    func_ovl0E_04_80043680(1, 0x40, 1, 0.0f, 0);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_04_80043FB8(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0E_04_80043DD4();
            break;
        case 17:
            func_ovl0E_04_800436A8();
            break;
        case 18:
            func_ovl0E_04_80043748();
            break;
        case 19:
            func_ovl0E_04_800436F8();
            break;
        case 20:
            func_ovl0E_04_800436A8();
            break;
        case 4:
            func_ovl0E_04_80043624();
            break;
        case 5:
            func_ovl0E_04_80043374();
            break;
        case 0x50:
            func_ovl0E_04_80043190();
            break;
        case 3:
            func_ovl0E_04_800430F8();
            break;
        case 12:
            func_ovl0E_04_80043088();
            break;
        case 1:
            func_ovl0E_04_80043038();
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_04_80043D5C(void) {
    func_ovl0E_04_80043D54();
    func_ovl0E_04_80046518(0x400);
    func_ovl0E_04_80046518(0x401);
    func_ovl0E_04_80046518(0x402);
    func_ovl0E_04_80046518(0x403);
    func_ovl0E_04_80046518(0x404);
}

static void func_ovl0E_04_80043D54(void) {
}

void func_ovl0E_04_80043B4C(void) {
    s32 i;

    func_ovl0E_04_80043AFC();
    for (i = 0; i < 2; i++) {
        D_ovl0E_04_80046D70[i].unk0 = func_ovl0E_04_80046190(D_ovl0E_04_80046D70[i].unk8, 0xD0, 0.0f, 0.0f, 0.0f);
        func_ovl0E_04_80046148(D_ovl0E_04_80046D70[i].unk0, 0x01080000);
        func_ovl0E_04_80046150(D_ovl0E_04_80046D70[i].unk0, 0x02000000);
        if (D_ovl0E_04_80046D70[i].unkC != -1 && D_ovl0E_04_80046D70[i].unkE != -1 && D_ovl0E_04_80046D70[i].unk10 != -1 && D_ovl0E_04_80046D70[i].unk12 != -1) {
            D_ovl0E_04_80046D70[i].unk4 = func_ovl0E_04_80045E90(D_ovl0E_04_80046D70[i].unk0->unk40, 0, D_ovl0E_04_80046D70[i].unkC, D_ovl0E_04_80046D70[i].unkE, D_ovl0E_04_80046D70[i].unk10, D_ovl0E_04_80046D70[i].unk12);
            if (D_ovl0E_04_80046D70[i].unk4 == -1) {
                while (TRUE) {
                }
            }
        }
        D_ovl0E_04_80046D70[i].unk0->unk40->unk10 = D_ovl0E_04_80046D70[i].unk14 * 10.0f;
        D_ovl0E_04_80046D70[i].unk0->unk40->unk14 = D_ovl0E_04_80046D70[i].unk18 * 10.0f;
        D_ovl0E_04_80046D70[i].unk0->unk40->unk18 = D_ovl0E_04_80046D70[i].unk1C * 10.0f;
        D_ovl0E_04_80046D70[i].unk0->unk40->unk1C = D_ovl0E_04_80046D70[i].unk20;
        D_ovl0E_04_80046D70[i].unk0->unk40->unk20 = D_ovl0E_04_80046D70[i].unk24;
        D_ovl0E_04_80046D70[i].unk0->unk40->unk24 = D_ovl0E_04_80046D70[i].unk28;
        D_ovl0E_04_80046D70[i].unk0->unk40->unk28 = D_ovl0E_04_80046D70[i].unk2C;
        D_ovl0E_04_80046D70[i].unk0->unk40->unk2C = D_ovl0E_04_80046D70[i].unk30;
        D_ovl0E_04_80046D70[i].unk0->unk40->unk30 = D_ovl0E_04_80046D70[i].unk34;
        func_ovl0E_04_80046150(D_ovl0E_04_80046D70[i].unk0, 0x80000);
    }
}

void func_ovl0E_04_80043AFC(void) {
    func_ovl0E_04_80043AF4();
    if (func_ovl0E_04_80046520(0x400) == 0) {
        D_ovl0E_04_80046F54 = func_ovl0E_04_80046190(-1, 0x80, 0.0f, 0.0f, 0.0f);
        func_ovl0E_04_80046510(0x400);
    }
}

static void func_ovl0E_04_80043AF4(void) {
}

static void func_ovl0E_04_80043A78(UnkStruct_ovl0E_04_80046D70 *e) {
    func_ovl0E_04_80046160(e->unk0);
    /* 0xFFFF, not -1: never equal to the s16 fields */
    if (e->unkC != 0xFFFF && e->unkE != 0xFFFF && e->unk10 != 0xFFFF && e->unk12 != 0xFFFF) {
        func_ovl0E_04_80045E98(e->unk4);
    }
    e->unk0 = NULL;
    e->unk4 = -1;
}

void func_ovl0E_04_80043DD4(void) {
    UnkStructA *obj;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_04_80043D9C();
    func_ovl0E_04_80046600(D_ovl0E_04_80046A40);
    func_ovl0E_04_80045748(0x18B);
    obj = func_ovl0E_04_80046190(0x18C, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_04_80046148(obj, 0x01000000);
    p = D_ovl0E_04_80046A64;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl0E_04_800467A8((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_04_80045760(0x193);
    func_ovl0E_04_800458F8();
    func_ovl0E_04_80043B4C();
    if (func_ovl0E_04_80046520(0x406) != 0) {
        if (D_ovl0E_04_80046D70[1].unk0 != NULL) {
            func_ovl0E_04_80043A78(&D_ovl0E_04_80046D70[1]);
        }
        func_ovl0E_04_800439A4();
    }
    func_ovl0E_04_80043908();
    func_ovl0E_04_8004379C();
    func_ovl0E_04_80045E90(obj->unk40, 0, 2, 0x400, 0, 0);
    func_ovl0E_04_800465E8(0xFF, 0xA1, 0x1D);
}

void func_ovl0E_04_800439A4(void) {
    func_ovl0E_04_8004399C(9.0f, 2, 1);
}

/* Inlined into func_ovl0E_04_800439A4 only, which is inlined into its
 * callers in turn (ovl_12_01's func_ovl12_01_80043188).
 * The empty test after the body is a fake (the permuter's, in ovl_12_01):
 * the branch IDO folds away still ends the block. */
#define UNK_MACRO_ovl0E_04_8004399C()                                                     \
    D_ovl0E_04_80046F30[0] = x * 100.0f;                                                  \
    D_ovl0E_04_80046F30[1] = 0.0f;                                                        \
    for (i = 0; i < count; i++) {                                                         \
        D_ovl0E_04_80046F30[1] += func_ovl0E_04_800457B0(i) * 100.0f;                     \
    }                                                                                     \
    D_ovl0E_04_80046F30[1] += 100.0f;                                                     \
    D_ovl0E_04_80046F30[2] = z * 100.0f;                                                  \
    D_ovl0E_04_80046F20 = func_ovl0E_04_800466F0(0x25, D_ovl0E_04_80046F30, 0)

static void func_ovl0E_04_8004399C(f32 x, s32 z, s32 count) {
    s32 i;

    UNK_MACRO_ovl0E_04_8004399C();
    if (!i && !i) {
    }
}

void func_ovl0E_04_80043908(void) {
    s16 flag;
    s16 i;

    if (func_ovl0E_04_80046520(0x406) != 0) {
        flag = 0;
    } else {
        flag = 1;
        func_ovl0E_04_80046518(0x401);
        func_ovl0E_04_80046518(0x402);
        func_ovl0E_04_80046518(0x403);
        func_ovl0E_04_80046518(0x417);
    }
    for (i = 0; i < 3; i++) {
        func_ovl0E_04_80043840(i, flag);
    }
}

void func_ovl0E_04_80043840(s16 idx, s16 flag) {
    s32 model;
    UnkStructA *obj;

    if (flag) {
        model = 0x1BF;
    } else {
        model = 0x1C0;
    }
    obj = func_ovl0E_04_80046190(model, 0xC0, D_ovl0E_04_80046DE0[idx].unkC, D_ovl0E_04_80046DE0[idx].unk10, D_ovl0E_04_80046DE0[idx].unk14);
    D_ovl0E_04_80046DE0[idx].unk8 = obj;
    func_ovl0E_04_80046148(obj, 0x01008010);
    obj->unk40->unk20 = D_ovl0E_04_80046DE0[idx].unk18;
    obj->unk30 = 1;
    obj->unk34 = 50.0f;
    obj->unk38 = 100.0f;
}

void func_ovl0E_04_8004379C(void) {
    UnkStruct_ovl0E_04_80045898 *state;
    UnkStruct_ovl0E_04_80046BE8 *rec;
    s16 i;

    state = func_ovl0E_04_80045898();
    for (i = 0, rec = D_ovl0E_04_80046BE8; i < 7; i++, rec++) {
        if (state->unk10 != 0 || rec->unk28 != 1) {
            func_ovl0E_04_80046298(func_ovl0E_04_800449E8, rec, 0, 0, 0x110);
        }
    }
}

void func_ovl0E_04_80043748(void) {
    func_ovl0E_04_80045900(1, 0, 0x14);
    func_ovl0E_04_80043680(2, 0x40, 1, -90.0f, 2);
}

void func_ovl0E_04_800436F8(void) {
    func_ovl0E_04_80045900(0x2E, 1, 0x13);
    func_ovl0E_04_80043680(3, 0xC0, 0xC0, 0.0f, 2);
}

void func_ovl0E_04_800436A8(void) {
    func_ovl0E_04_80045900(0x23, 2, 0x13);
    func_ovl0E_04_80043680(4, 0x80, 0xE0, 0.0f, 0);
}

void func_ovl0E_04_80043680(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_04_80046F40.unk0 = arg0;
    D_ovl0E_04_80046F40.unk4 = arg1;
    D_ovl0E_04_80046F40.unk8 = arg2;
    D_ovl0E_04_80046F40.unkC = arg3;
    D_ovl0E_04_80046F40.unk10 = arg4;
}

void func_ovl0E_04_80043624(void) {
    func_ovl0E_04_8004350C();
    if (func_ovl0E_04_80046520(0x406) != 0) {
        func_ovl0E_04_80043468(D_ovl0E_04_80046D70);
        func_ovl0E_04_80043408();
    }
    if (D_ovl0E_04_80046F40.unk0 == 4) {
        func_ovl0E_04_8004339C();
    }
}

void func_ovl0E_04_8004350C(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_04_80045958();
    switch (D_ovl0E_04_80046F40.unk8) {
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
        func_ovl0E_04_80045FA8(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_04_80046F40.unkC;
        func_ovl0E_04_80045FB0(&sp1C, NULL, NULL);
        func_ovl0E_04_80045FA8(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_04_80045940(D_ovl0E_04_80046F40.unk4);
}

void func_ovl0E_04_800434C4(f32 arg0) {
    f32 sp1C;

    func_ovl0E_04_80045FB0(&sp1C, NULL, NULL);
    func_ovl0E_04_80045FA8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_04_80043468(UnkStruct_ovl0E_04_80046D70 *arg0) {
    arg0->unk0->unk40->unk48->unk4->unk4 = func_ovl0E_04_80045E88(arg0->unk0->unk40, 0) - 1.0f;
}

void func_ovl0E_04_80043408(void) {
    func_ovl0E_04_80045788(8, 1, 2, 0xA, 8, 0x11);
    func_ovl0E_04_80045788(8, 0, 2, 0xA, 6, 0x1F);
}

void func_ovl0E_04_8004339C(void) {
    func_ovl0E_04_80045FA8(45.0f, 32768.0f, 32768.0f);
    func_ovl0E_04_80045FF0(0xF);
    func_ovl0E_04_80046000(1);
    func_ovl0E_04_80045938(1);
    func_ovl0E_04_80046298(func_ovl0E_04_80044170, NULL, 0, 0, 0x130);
}

void func_ovl0E_04_80043374(void) {
    func_ovl0E_04_800432FC();
    func_ovl0E_04_80043264();
}

void func_ovl0E_04_800432FC(void) {
    UNK_MACRO_ovl0E_04_800430B0();
    func_ovl0E_04_80045948(D_ovl0E_04_80046F40.unk4, 3, 4.0f, D_ovl0E_04_80046F40.unk10, 0, 1, 1);
}

void func_ovl0E_04_80043264(void) {
    s16 i;

    if (func_ovl0E_04_80046520(0x406) == 0) {
        for (i = 0; i < 3; i++) {
            func_ovl0E_04_80046298(func_ovl0E_04_80044670, &D_ovl0E_04_80046DE0[i], 0, 0, 0x110);
        }
    }
}

void func_ovl0E_04_80043190(void) {
    func_ovl0E_04_80043188();
    if (func_ovl0E_04_80045910(1, 0x13, 1, 0x14) != 0) {
        D_ovl0E_04_80046F24 = 0x4A;
        D_ovl0E_04_80046F28 = 0x12;
        func_ovl0E_04_80045840(0x4A, 0x12, 0);
    }
    if (func_ovl0E_04_80045910(0x2E, 0x12, 0x2E, 0x13) != 0) {
        D_ovl0E_04_80046F24 = 0x4C;
        D_ovl0E_04_80046F28 = 0x12;
        func_ovl0E_04_80045840(0x4C, 0x12, 0);
    }
    if (func_ovl0E_04_80045910(8, 1, 0xA, 1) != 0) {
        func_ovl0E_04_80045940(0x80);
        func_ovl0E_04_80043158();
    }
}

static void func_ovl0E_04_80043188(void) {
}

void func_ovl0E_04_80043158(void) {
    func_ovl0E_04_80043140();
    func_ovl0E_04_80043148();
    func_ovl0E_04_80043150();
    func_ovl0E_04_800466F8(D_ovl0E_04_80046F20);
    func_ovl0E_04_80045868();
}

static void func_ovl0E_04_80043150(void) {
}

static void func_ovl0E_04_80043148(void) {
}

static void func_ovl0E_04_80043140(void) {
}

void func_ovl0E_04_800430F8(void) {
    UNK_MACRO_ovl0E_04_800430B0();
}

void func_ovl0E_04_800430B0(void) {
    func_ovl0E_04_800430A8();
    UNK_MACRO_ovl0E_04_800430B0();
}

static void func_ovl0E_04_800430A8(void) {
}

void func_ovl0E_04_80043088(void) {
    func_ovl0E_04_80045990(1);
}

void func_ovl0E_04_80043068(void) {
    func_ovl0E_04_80045990(1);
}

void func_ovl0E_04_80043038(void) {
    if (D_ovl0E_04_80046F40.unk0 == 4) {
        func_ovl0E_04_800469A0();
    }
}

void func_ovl0E_04_80043018(void) {
    func_ovl0E_04_800469A0();
}

void func_ovl0E_04_80043010(void) {
}
