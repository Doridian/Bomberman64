#include "common.h"

/*
 * ovl_0E_01's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Most of it is ovl_0E_03's
 * code (nonmatching/overlays/ovl_0E_03), with ovl_0E_10's first functions
 * (src/overlays/ovl_0E_10) and ovl_0E_05's D_ovl0E_05_8004615C object
 * (nonmatching/overlays/ovl_0E_05) as D_ovl0E_01_80046BB0.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_01_80046D28;

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
} UnkStruct_ovl0E_01_80046B00; /* size 0x38 */

/* what replaces D_ovl0E_01_80046B00's models once their flags (unk0) are set */
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
} UnkStruct_ovl0E_01_80046B70;

/* the six movers: each record is passed to its task */
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
} UnkStruct_ovl0E_01_800469F8;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl0E_01_80046C58;

/* what func_ovl0E_01_80045808 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_01_80045808;

/* the argument of func_ovl0E_01_80044B5C's task: unk2/unk4 a tile */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} UnkStruct_ovl0E_01_80046D20; /* size 0x8 */

void func_ovl0E_01_800456B8(s32);
void func_ovl0E_01_800456D0(s32);
f32 func_ovl0E_01_800456E0(void);
void func_ovl0E_01_800456F8(s32, s32, s32, s32, s32, s32);
void func_ovl0E_01_80045700(s32, s32, s32, s32, s32, s32, s32);
void func_ovl0E_01_80045710(f32, f32, f32, s32 *, s32);
s32 func_ovl0E_01_80045728(s32, s32, s32);
void func_ovl0E_01_80045740(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_01_800457A0(void (*)(UnkStructA *));
void func_ovl0E_01_800457B0(s32, s32, s32);
void func_ovl0E_01_800457F0(void (*)(UnkStructA *));
UnkStruct_ovl0E_01_80045808 *func_ovl0E_01_80045808(void);
void func_ovl0E_01_80045868(void);
void func_ovl0E_01_80045870(s32, s32, s32);
void func_ovl0E_01_80045878(void *);
s32 func_ovl0E_01_80045880(s32, s32, s32, s32);
s32 func_ovl0E_01_80045888(s32, s32, s32, s32, s32);
s32 func_ovl0E_01_80045898(void);
void func_ovl0E_01_800458A0(s32, f32 *);
void func_ovl0E_01_800458B0(s32);
void func_ovl0E_01_800458B8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_01_800458C8(void);
UnkStructA *func_ovl0E_01_800458F8(s32);
void func_ovl0E_01_80045900(s32);
void func_ovl0E_01_80045DC0(UnkStructA_40 *, s32);
void func_ovl0E_01_80045DC8(UnkStructA_40 *, s32, s32, s32);
f32 func_ovl0E_01_80045DF8(UnkStructA_40 *, s32);
s32 func_ovl0E_01_80045E00(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_01_80045E08(s32);
void func_ovl0E_01_80045E20(s32, s32);
void func_ovl0E_01_80045EF8(f32, f32, f32);
void func_ovl0E_01_80045F18(f32, f32, f32);
void func_ovl0E_01_80045F20(f32 *, f32 *, f32 *);
void func_ovl0E_01_80045FD0(s32);
void func_ovl0E_01_80045FE0(f32, f32, f32);
f32 func_ovl0E_01_80046060(f32 *, f32 *);
s32 func_ovl0E_01_80046068(UnkStructA *, s32);
void func_ovl0E_01_800460B8(UnkStructA *, s32);
void func_ovl0E_01_800460C0(UnkStructA *, s32);
void func_ovl0E_01_800460D0(UnkStructA *);
UnkStructA *func_ovl0E_01_800460E0(s32, s32, s32, s32);
UnkStructA *func_ovl0E_01_800460F0(UnkStructA *);
UnkStructA *func_ovl0E_01_80046100(s32, s32, f32, f32, f32);
void func_ovl0E_01_80046138(UnkStructA *);
UnkStructA *func_ovl0E_01_80046148(UnkStructA *, s32);
void func_ovl0E_01_800461C8(UnkStructA *);
s32 func_ovl0E_01_80046208(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_01_80046218(void);
void func_ovl0E_01_80046228(s32);
void *func_ovl0E_01_80046230(void);
void func_ovl0E_01_80046250(void);
f32 func_ovl0E_01_800463B0(f32);
f32 func_ovl0E_01_800463B8(f32);
s32 func_ovl0E_01_800463C8(s32);
s32 func_ovl0E_01_80046470(s32);
void func_ovl0E_01_80046480(s32);
void func_ovl0E_01_80046488(s32);
s32 func_ovl0E_01_80046490(s32);
void func_ovl0E_01_80046558(s32, s32, s32);
void func_ovl0E_01_80046570(u32 (*)[3]);
void func_ovl0E_01_80046658(s32, f32, f32, f32, s32);
void func_ovl0E_01_80046660(s32, f32 *, s32);
void func_ovl0E_01_80046718(s32, s32, s32);
void func_ovl0E_01_80046790(s32);
void func_ovl0E_01_800467B0(s32, f32, f32, f32);
void func_ovl0E_01_800467B8(s32, f32 *);

void func_ovl0E_01_80043010(void);
void func_ovl0E_01_80043020(void);
void func_ovl0E_01_80043040(void);
void func_ovl0E_01_80043060(void);
s32 func_ovl0E_01_800430B0(UnkStructA *, UnkStructA *);
void func_ovl0E_01_800431C4(void);
void func_ovl0E_01_80043254(UnkStruct_ovl0E_01_80046B70 *);
void func_ovl0E_01_80043310(void);
void func_ovl0E_01_800434EC(void);
void func_ovl0E_01_80043578(void);
void func_ovl0E_01_800435B0(void);
void func_ovl0E_01_8004372C(void);
void func_ovl0E_01_80043774(void);
void func_ovl0E_01_800437E4(void);
void func_ovl0E_01_800438FC(void);
void func_ovl0E_01_80043974(void);
void func_ovl0E_01_800439AC(void);
void func_ovl0E_01_800439D4(UnkStruct_ovl0E_01_80046B00 *);
void func_ovl0E_01_80043A30(f32);
void func_ovl0E_01_80043A78(void);
void func_ovl0E_01_80043B90(void);
void func_ovl0E_01_80043BD0(s32, s32, s32, f32, s32);
void func_ovl0E_01_80043BF8(void);
void func_ovl0E_01_80043C48(void);
void func_ovl0E_01_80043C98(void);
void func_ovl0E_01_80043CE8(void);
void func_ovl0E_01_80043D3C(void);
void func_ovl0E_01_80043D84(void);
void func_ovl0E_01_80043DC8(void);
void func_ovl0E_01_80043E3C(void);
void func_ovl0E_01_80044034(void);
void func_ovl0E_01_80044120(void);
void func_ovl0E_01_8004420C(void);
void func_ovl0E_01_800442F0(void);
void func_ovl0E_01_80044330(void);
void func_ovl0E_01_80044368(void);
void func_ovl0E_01_8004448C(s32);
void func_ovl0E_01_80044634(void);
void func_ovl0E_01_800446A8(void);
void func_ovl0E_01_80044708(UnkStruct_ovl0E_01_80046D20 *, s16, s16);
void func_ovl0E_01_80044980(void);
void func_ovl0E_01_800449B4(void);
void func_ovl0E_01_80044B5C(void);
void func_ovl0E_01_80044E20(void);
void func_ovl0E_01_80045134(UnkStructA *);
void func_ovl0E_01_800451F8(UnkStructA *);
void func_ovl0E_01_80045290(s32, UnkStructA *);
void func_ovl0E_01_800452C4(f32, f32, f32);
void func_ovl0E_01_80045320(void);
void func_ovl0E_01_80045338(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0E_01_80043018(void);
static void func_ovl0E_01_80043724(void);
static void func_ovl0E_01_800437CC(void);
static void func_ovl0E_01_800437D4(void);
static void func_ovl0E_01_800437DC(void);
static void func_ovl0E_01_800442E8(void);
/* takes its record in s0 */
static void func_ovl0E_01_80043294(UnkStruct_ovl0E_01_80046B00 *);
static void func_ovl0E_01_80043EB4(UnkStruct_ovl0E_01_80046B00 *);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_01_8004372C() \
    D_ovl0E_01_80046CFC = func_ovl0E_01_80045898(); func_ovl0E_01_80045878(&D_ovl0E_01_80046CF0); func_ovl0E_01_800458A0(D_ovl0E_01_80046CFC, D_ovl0E_01_80046CE0)

/* .bss */
f32 D_ovl0E_01_80046CE0[4];
Vec3f D_ovl0E_01_80046CF0;
s32 D_ovl0E_01_80046CFC;
u8 D_ovl0E_01_80046D00[0x4]; /* unused (func_ovl0E_01_80045368) */
s32 D_ovl0E_01_80046D04;
s32 D_ovl0E_01_80046D08;
u8 D_ovl0E_01_80046D0C[0x4]; /* unused (func_ovl0E_01_80045368) */
Vec3f D_ovl0E_01_80046D10;
u8 D_ovl0E_01_80046D1C[0x4]; /* unused (func_ovl0E_01_80045368) */
UnkStruct_ovl0E_01_80046D20 D_ovl0E_01_80046D20[1];
UnkStruct_ovl0E_01_80046D28 D_ovl0E_01_80046D28;
UnkStructA *D_ovl0E_01_80046D3C;

/* .data */
/* passed to func_ovl0E_01_80046570: three 12-byte records */
u32 D_ovl0E_01_800469B0[][3] = {
    { 0x9D0000, 0xC000E, 4 },
    { 0x9E0002, 0xE, 4 },
    { 2, 0, 4 },
};
/* three 12-byte records, each passed to func_ovl0E_01_80046718 */
u32 D_ovl0E_01_800469D4[][3] = {
    { 0, 0, 0xDE },
    { 1, 0xD, 0xEB },
    { 2, 0x22, 0xE0 },
};
UnkStruct_ovl0E_01_800469F8 D_ovl0E_01_800469F8[6] = {
    { 0, -1, NULL, 50.0f, -3800.0f, 650.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 1, -1, NULL, 50.0f, -3800.0f, 1050.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 2, -1, NULL, 1150.0f, -3800.0f, 150.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 3, -1, NULL, 1450.0f, -3800.0f, 450.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 4, -1, NULL, 1650.0f, -3800.0f, 1150.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 5, -1, NULL, 1950.0f, -3800.0f, 1150.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
};
UnkStruct_ovl0E_01_80046B00 D_ovl0E_01_80046B00[2] = {
    { NULL, -1, 0xA0, -1, -1, -1, -1, 70.0f, 40.0f, 135.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0xA0, -1, -1, -1, -1, 410.0f, 0.0f, 245.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_01_80046B70 D_ovl0E_01_80046B70[2] = {
    { 0x413, 65.0f, 40.0f, 145.0f, 180.0f, 6, 1, 0xE, 7, 0xF, 1 },
    { 0x414, 415.0f, 0.0f, 235.0f, 0.0f, 0x29, 0, 0x17, 0x2A, 0x18, 1 },
};
UnkStruct_ovl0E_01_80046B00 D_ovl0E_01_80046BB0[1] = {
    { NULL, -1, 0x1AD, -1, -1, -1, -1, 265.0f, 120.0f, 35.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_01_80046B00 D_ovl0E_01_80046BE8[1] = {
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_01_80046B00 D_ovl0E_01_80046C20[1] = {
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_01_80046C58 D_ovl0E_01_80046C58 = { NULL, 2400.0f, 800.0f, 1400.0f };

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0E_01_80045368(void) {
    D_ovl0E_01_80046D00[0] = D_ovl0E_01_80046D0C[0] + D_ovl0E_01_80046D1C[0];
}

/* Its references keep func_ovl0E_01_80045134 and 800451F8 in address order
 * after 80044E20 (ovl_0E_02's 80044D48). The body itself isn't emitted. */
static void func_ovl0E_01_80045360(void) {
    func_ovl0E_01_800457A0(func_ovl0E_01_800451F8);
    func_ovl0E_01_800457F0(func_ovl0E_01_80045134);
}

static void func_ovl0E_01_80045358(void) {
}

static void func_ovl0E_01_80045350(void) {
}

static void func_ovl0E_01_80045348(void) {
}

static void func_ovl0E_01_80045340(void) {
}

void func_ovl0E_01_80045338(void) {
}

void func_ovl0E_01_80045320(void) {
    D_ovl0E_01_80046D04 = -1;
    D_ovl0E_01_80046D08 = -1;
}

void func_ovl0E_01_800452C4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_01_80045EF8(D_ovl0E_01_80046D10.x, D_ovl0E_01_80046D10.y, D_ovl0E_01_80046D10.z);
    func_ovl0E_01_80045F18(arg0, arg1, arg2);
    func_ovl0E_01_80046228(180);
}

void func_ovl0E_01_80045290(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_01_800467B0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_01_800451F8(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_01_800460C0(arg0, 0x01000000);
    func_ovl0E_01_80046660(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_01_80046660(13, pos, 0);
    func_ovl0E_01_800467B8(180, pos);
}

void func_ovl0E_01_80045134(UnkStructA *arg0) {
    func_ovl0E_01_800460C0(arg0, 0x04000000);
    func_ovl0E_01_80046228(10);
    func_ovl0E_01_80045740(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_01_80046790(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_01_80046228(60);
}

void func_ovl0E_01_80044E20(void) {
    UnkStruct_ovl0E_01_800469F8 *rec;
    s32 flag;
    f32 a[3];
    f32 b[3];
    UnkStructA_40 *p;

    rec = func_ovl0E_01_80046230();
    rec->unk8 = func_ovl0E_01_800460E0(0x1BC, 0x0D080040, 0x20, 0);
    rec->unk8->unk40->unkC |= 0x8000;
    func_ovl0E_01_800460B8(rec->unk8, 0x0D080040);
    rec->unk10 = rec->unk28;
    rec->unk8->unk40->unk10 = rec->unkC;
    rec->unk8->unk40->unk14 = rec->unk10;
    rec->unk8->unk40->unk18 = rec->unk14;
    func_ovl0E_01_80045DC0(rec->unk8->unk40, 2);
    func_ovl0E_01_80045DC8(rec->unk8->unk40, 0x1BD, 0, 0);
    func_ovl0E_01_80045DC8(rec->unk8->unk40, 0x1BD, 1, 1);
    rec->unk8->unk30 = 4;
    rec->unk8->unk34 = 50.0f;
    rec->unk8->unk38 = 2500.0f;
    func_ovl0E_01_80046228(func_ovl0E_01_800463C8(60) + 30);
    flag = 0;
    while (TRUE) {
        func_ovl0E_01_800461C8(rec->unk8);
        rec->unk10 += rec->unk18;
        if (rec->unk10 < rec->unk28) {
            rec->unk10 = rec->unk28;
            rec->unk18 = (f32) func_ovl0E_01_800463C8((s32) (rec->unk20 - rec->unk1C)) + rec->unk1C;
            func_ovl0E_01_80046228(func_ovl0E_01_800463C8(60) + 30);
            a[0] = rec->unk8->unk40->unk10;
            a[1] = 0.0f;
            a[2] = rec->unk8->unk40->unk18;
            b[0] = D_ovl0E_01_80046CE0[0];
            b[1] = 0.0f;
            b[2] = D_ovl0E_01_80046CE0[2];
            if (func_ovl0E_01_80046060(a, b) < 800.0f) {
                func_ovl0E_01_800467B0(0x75, rec->unk8->unk40->unk10, rec->unk8->unk40->unk14,
                                       rec->unk8->unk40->unk18);
            }
        }
        rec->unk18 -= rec->unk24;
        /* through a variable: $v0 for both, where the expression gives $t9 */
        p = rec->unk8->unk40;
        p->unk20 += 20.0f;
        p = rec->unk8->unk40;
        p->unk14 = rec->unk10;
        /* never runs: what it did is unknown, but two float constants live
         * across the loop's calls take $f26 and $f28, which the original
         * saves and never uses (ovl_0E_02's 800447F8) */
        if (flag) {
            rec->unkC = 3.0f;
            rec->unk14 = 5.0f;
        }
        func_ovl0E_01_80046250();
    }
}

/* drops the model pair from 10000 at the tile its argument gives */
void func_ovl0E_01_80044B5C(void) {
    UnkStruct_ovl0E_01_80046D20 *arg;
    UnkStruct_ovl0E_01_80046B00 *a;
    UnkStruct_ovl0E_01_80046B00 *b;

    func_ovl0E_01_80046250();
    arg = func_ovl0E_01_80046230();
    a = &D_ovl0E_01_80046BE8[arg->unk0];
    b = &D_ovl0E_01_80046C20[arg->unk0];
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
    func_ovl0E_01_800460B8(a->unk0, 0x01000000);
    func_ovl0E_01_800460B8(b->unk0, 0x01000000);
    while (TRUE) {
        func_ovl0E_01_80046138(a->unk0);
        b->unk0->unk40->unk14 = a->unk0->unk40->unk14;
        if (a->unk0->unk40->unk14 <= func_ovl0E_01_800456E0() ||
            (a->unk0->unk6C == 0.0f && a->unk0->unk68 == 0.0f)) {
            func_ovl0E_01_800460C0(a->unk0, 0x01000000);
            func_ovl0E_01_800460C0(b->unk0, 0x01000000);
            func_ovl0E_01_800467B0(0x7C, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
            func_ovl0E_01_80046658(10, a->unk0->unk40->unk10, a->unk0->unk40->unk14 + 10.0f,
                                   a->unk0->unk40->unk18, 0);
            arg->unk6 |= 1;
            func_ovl0E_01_80046218();
        }
        func_ovl0E_01_80046250();
    }
}

void func_ovl0E_01_80044980(void) {
    func_ovl0E_01_80045FE0(20.0f, 20.0f, 20.0f);
    func_ovl0E_01_80045FD0(120);
}

void func_ovl0E_01_800449B4(void) {
    s16 i;
    s16 j;
    s16 n;
    s32 base;
    s32 range;

    func_ovl0E_01_80046228(300);
    if (func_ovl0E_01_80045808()->unk10 == 0) {
        n = 2;
        base = 480;
        range = 480;
    } else {
        n = 5;
        base = 240;
        range = 240;
    }
    for (i = 0; i < 1; i++) {
        D_ovl0E_01_80046D20[i].unk0 = i;
    }
    while (TRUE) {
        func_ovl0E_01_80044980();
        func_ovl0E_01_80046228(60);
        for (i = 0; i < n; i++) {
            for (j = 0; j < 1; j++) {
                D_ovl0E_01_80046D20[j].unk6 = 0;
            }
            func_ovl0E_01_80044708(D_ovl0E_01_80046D20, 3, 3);
            func_ovl0E_01_80046208(func_ovl0E_01_80044B5C, &D_ovl0E_01_80046D20[0], 0, 0, 0x110);
            func_ovl0E_01_80046250();
            while (TRUE) {
                if (D_ovl0E_01_80046D20[0].unk6 & 1) {
                    break;
                }
                func_ovl0E_01_80046250();
            }
            func_ovl0E_01_80046250();
        }
        func_ovl0E_01_80046228(func_ovl0E_01_800463C8(range) + base);
    }
}

/* picks a tile for each of arg0's entries around the one func_ovl0E_01_80045710
 * gives for func_ovl0E_01_800458A0's position, retrying where
 * func_ovl0E_01_80045728 gives 0xF (at most 6 tries) */
void func_ovl0E_01_80044708(UnkStruct_ovl0E_01_80046D20 *arg0, s16 arg1, s16 arg2) {
    s16 i;
    s16 j;
    s16 tries;
    s16 xs[1];
    s16 ys[1];
    f32 pos[4];
    s32 here[6];
    s32 v[6];

    func_ovl0E_01_800458A0(0, pos);
    func_ovl0E_01_80045710(pos[0], pos[1], pos[2], here, 0);
    for (i = 0, tries = 0; i < 1;) {
        xs[i] = func_ovl0E_01_800463C8(arg1 * 2);
        ys[i] = func_ovl0E_01_800463C8(arg2 * 2);
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
                func_ovl0E_01_80045710(0.0f, 10000.0f, 0.0f, v, 0);
                if ((func_ovl0E_01_80045728(here[0] + (xs[i] - arg1), v[1], here[2] + (ys[i] - arg2)) & 0xF) == 0xF) {
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

void func_ovl0E_01_800446A8(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_ovl0E_01_80046BB0[i].unk0 != NULL) {
            func_ovl0E_01_80043294(&D_ovl0E_01_80046BB0[i]);
        }
    }
}

void func_ovl0E_01_80044634(void) {
    s32 i;

    for (i = 54; i != 0; i--) {
        func_ovl0E_01_80046250();
    }
    func_ovl0E_01_800467B0(0x79, 2600.0f, 1200.0f, 400.0f);
    func_ovl0E_01_80046658(0x10, 2650.0f, 1300.0f, 350.0f, 0);
    func_ovl0E_01_80046218();
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_01_8004448C(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0E_01_80044368();
            break;
        case 16:
            func_ovl0E_01_80043D84();
            break;
        case 17:
            func_ovl0E_01_80043D3C();
            break;
        case 18:
            func_ovl0E_01_80043CE8();
            break;
        case 19:
            func_ovl0E_01_80043C98();
            break;
        case 20:
            func_ovl0E_01_80043C48();
            break;
        case 21:
            func_ovl0E_01_80043BF8();
            break;
        case 4:
            func_ovl0E_01_80043B90();
            break;
        case 5:
            func_ovl0E_01_800439AC();
            break;
        case 0x50:
            func_ovl0E_01_800437E4();
            break;
        case 3:
            func_ovl0E_01_80043774();
            break;
        case 15:
            func_ovl0E_01_800431C4();
            break;
        case 12:
            func_ovl0E_01_80043040();
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_01_80044368(void) {
    UnkStructA *obj;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_01_80044330();
    func_ovl0E_01_80046570(D_ovl0E_01_800469B0);
    func_ovl0E_01_800456B8(0x185);
    obj = func_ovl0E_01_80046100(0x186, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_01_800460B8(obj, 0x01000000);
    p = D_ovl0E_01_800469D4;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl0E_01_80046718((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_01_800456D0(0x190);
    func_ovl0E_01_80045868();
    func_ovl0E_01_8004420C();
    func_ovl0E_01_80044120();
    func_ovl0E_01_80044034();
    func_ovl0E_01_80043E3C();
    func_ovl0E_01_80043DC8();
    func_ovl0E_01_80045E00(obj->unk40, 0, 2, 0x400, 0, 0);
    func_ovl0E_01_80046558(0xFF, 0xA1, 0x1D);
}

void func_ovl0E_01_80044330(void) {
    func_ovl0E_01_800442F0();
    func_ovl0E_01_800457A0(func_ovl0E_01_800451F8);
    func_ovl0E_01_800457F0(func_ovl0E_01_80045134);
}

void func_ovl0E_01_800442F0(void) {
    func_ovl0E_01_800442E8();
    func_ovl0E_01_80046488(0x400);
    func_ovl0E_01_80046488(0x401);
    func_ovl0E_01_80046488(0x402);
    func_ovl0E_01_80046488(0x403);
    func_ovl0E_01_80046488(0x404);
}

static void func_ovl0E_01_800442E8(void) {
}

void func_ovl0E_01_8004420C(void) {
    s32 i;

    func_ovl0E_01_80043060();
    for (i = 0; i < 1; i++) {
        func_ovl0E_01_80043EB4(&D_ovl0E_01_80046BB0[i]);
        func_ovl0E_01_800460B8(D_ovl0E_01_80046BB0[i].unk0, 0x02000000);
        func_ovl0E_01_800460C0(D_ovl0E_01_80046BB0[i].unk0, 0x80000);
        if (D_ovl0E_01_80046BB0[i].unk0->unk40->unk48->unk4->unk4 != 0.0f) {
            while (TRUE) {
            }
        }
    }
}

void func_ovl0E_01_80044120(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 1; i++) {
        func_ovl0E_01_80043EB4(&D_ovl0E_01_80046BE8[i]);
        obj = func_ovl0E_01_800460F0(D_ovl0E_01_80046BE8[i].unk0);
        obj->unk54 = 4.0f;
        obj->unk4C = 4.0f;
        obj->unk40->unk36 = 0xCC;
        func_ovl0E_01_800460C0(D_ovl0E_01_80046BE8[i].unk0, 0x80000);
        func_ovl0E_01_800460C0(D_ovl0E_01_80046BE8[i].unk0, 0x01000000);
        func_ovl0E_01_80043EB4(&D_ovl0E_01_80046C20[i]);
        func_ovl0E_01_800460C0(D_ovl0E_01_80046C20[i].unk0, 0x01000000);
    }
}

/* D_ovl0E_01_80046B00's models, or what replaces them once their flags are set */
void func_ovl0E_01_80044034(void) {
    s32 i;

    func_ovl0E_01_80043060();
    for (i = 0; i < 2; i++) {
        if (func_ovl0E_01_80046490(D_ovl0E_01_80046B70[i].unk0) == 0) {
            func_ovl0E_01_80043EB4(&D_ovl0E_01_80046B00[i]);
            func_ovl0E_01_800460B8(D_ovl0E_01_80046B00[i].unk0, 0x02000000);
            func_ovl0E_01_800460C0(D_ovl0E_01_80046B00[i].unk0, 0x80000);
            D_ovl0E_01_80046B00[i].unk0->unk40->unk20 = D_ovl0E_01_80046B70[i].unk10;
        } else {
            func_ovl0E_01_80043254(&D_ovl0E_01_80046B70[i]);
        }
    }
}

static void func_ovl0E_01_80043EB4(UnkStruct_ovl0E_01_80046B00 *e) {
    e->unk0 = func_ovl0E_01_80046100(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0E_01_800460B8(e->unk0, 0x01080000);
    func_ovl0E_01_800460C0(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl0E_01_80045E00(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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

void func_ovl0E_01_80043E3C(void) {
    UnkStruct_ovl0E_01_800469F8 *rec;
    s16 i;

    for (i = 0, rec = D_ovl0E_01_800469F8; i < 6; i++, rec++) {
        rec->unk4 = func_ovl0E_01_80046208(func_ovl0E_01_80044E20, rec, 0, 0, 0x110);
    }
}

void func_ovl0E_01_80043DC8(void) {
    UnkStructA *obj;

    obj = func_ovl0E_01_80046100(0x323, 0xC0, D_ovl0E_01_80046C58.unk4, D_ovl0E_01_80046C58.unk8,
                                 D_ovl0E_01_80046C58.unkC);
    D_ovl0E_01_80046C58.unk0 = obj;
    obj->unk40->unk20 = 270.0f;
    func_ovl0E_01_800460F0(obj);
    func_ovl0E_01_800460B8(obj, 0x01000010);
}

void func_ovl0E_01_80043D84(void) {
    func_ovl0E_01_80045870(8, 4, 0x1B);
    func_ovl0E_01_80043BD0(0, 0, 0, 0.0f, 0);
}

void func_ovl0E_01_80043D3C(void) {
    func_ovl0E_01_80045870(8, 4, 0x1B);
    func_ovl0E_01_80043BD0(1, 0, 0, 0.0f, 0);
}

void func_ovl0E_01_80043CE8(void) {
    func_ovl0E_01_80045870(0x1A, 3, 1);
    func_ovl0E_01_80043BD0(2, 0x80, 1, 0.0f, 3);
}

void func_ovl0E_01_80043C98(void) {
    func_ovl0E_01_80045870(1, 2, 8);
    func_ovl0E_01_80043BD0(3, 0x40, 0x40, 0.0f, 4);
}

void func_ovl0E_01_80043C48(void) {
    func_ovl0E_01_80045870(6, 1, 0x10);
    func_ovl0E_01_80043BD0(4, 0, 0x80, 0.0f, 3);
}

void func_ovl0E_01_80043BF8(void) {
    func_ovl0E_01_80045870(0x29, 0, 0x16);
    func_ovl0E_01_80043BD0(5, 0x80, 0, 0.0f, 3);
}

void func_ovl0E_01_80043BD0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_01_80046D28.unk0 = arg0;
    D_ovl0E_01_80046D28.unk4 = arg1;
    D_ovl0E_01_80046D28.unk8 = arg2;
    D_ovl0E_01_80046D28.unkC = arg3;
    D_ovl0E_01_80046D28.unk10 = arg4;
}

void func_ovl0E_01_80043B90(void) {
    func_ovl0E_01_80043A78();
    if (func_ovl0E_01_80046490(0x405) != 0) {
        func_ovl0E_01_800439D4(D_ovl0E_01_80046BB0);
        func_ovl0E_01_800434EC();
    }
}

void func_ovl0E_01_80043A78(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_01_800458C8();
    switch (D_ovl0E_01_80046D28.unk8) {
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
        func_ovl0E_01_80045F18(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_01_80046D28.unkC;
        func_ovl0E_01_80045F20(&sp1C, NULL, NULL);
        func_ovl0E_01_80045F18(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_01_800458B0(D_ovl0E_01_80046D28.unk4);
}

void func_ovl0E_01_80043A30(f32 arg0) {
    f32 sp1C;

    func_ovl0E_01_80045F20(&sp1C, NULL, NULL);
    func_ovl0E_01_80045F18(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_01_800439D4(UnkStruct_ovl0E_01_80046B00 *arg0) {
    arg0->unk0->unk40->unk48->unk4->unk4 = func_ovl0E_01_80045DF8(arg0->unk0->unk40, 0) - 0.001f;
}

void func_ovl0E_01_800439AC(void) {
    func_ovl0E_01_80043974();
    func_ovl0E_01_800438FC();
}

void func_ovl0E_01_80043974(void) {
    func_ovl0E_01_80046208(func_ovl0E_01_800449B4, NULL, 0, 0, 0x110);
}

void func_ovl0E_01_800438FC(void) {
    UNK_MACRO_ovl0E_01_8004372C();
    func_ovl0E_01_800458B8(D_ovl0E_01_80046D28.unk4, 3, 4.0f, D_ovl0E_01_80046D28.unk10, 0, 1, 1);
}

void func_ovl0E_01_800437E4(void) {
    func_ovl0E_01_800437CC();
    func_ovl0E_01_800437D4();
    func_ovl0E_01_800437DC();
    if (func_ovl0E_01_80045880(0x19, 1, 0x1C, 1) != 0) {
        D_ovl0E_01_80046D04 = 0x4C;
        D_ovl0E_01_80046D08 = 0x13;
        func_ovl0E_01_800457B0(0x4C, 0x13, 0);
    }
    if (func_ovl0E_01_80045880(1, 8, 1, 9) != 0) {
        D_ovl0E_01_80046D04 = 0x49;
        D_ovl0E_01_80046D08 = 0x13;
        func_ovl0E_01_800457B0(0x49, 0x13, 0);
    }
    if (func_ovl0E_01_80045880(6, 0x10, 7, 0x10) != 0) {
        D_ovl0E_01_80046D04 = 0x4E;
        D_ovl0E_01_80046D08 = 0x12;
        func_ovl0E_01_800457B0(0x4E, 0x12, 0);
    }
    if (func_ovl0E_01_80045880(0x29, 0x16, 0x2A, 0x16) != 0) {
        D_ovl0E_01_80046D04 = 0x4D;
        D_ovl0E_01_80046D08 = 0x12;
        func_ovl0E_01_800457B0(0x4D, 0x12, 0);
    }
}

static void func_ovl0E_01_800437DC(void) {
}

static void func_ovl0E_01_800437D4(void) {
}

static void func_ovl0E_01_800437CC(void) {
}

void func_ovl0E_01_80043774(void) {
    UNK_MACRO_ovl0E_01_8004372C();
    func_ovl0E_01_800435B0();
    func_ovl0E_01_80043310();
}

void func_ovl0E_01_8004372C(void) {
    func_ovl0E_01_80043724();
    UNK_MACRO_ovl0E_01_8004372C();
}

static void func_ovl0E_01_80043724(void) {
}

void func_ovl0E_01_800435B0(void) {
    s32 flags;

    if (D_ovl0E_01_80046BB0[0].unk0->unk40->unk48->unk4->unk4 == 0.0f) {
        D_ovl0E_01_80046D3C->unk30 = 1;
        D_ovl0E_01_80046D3C->unk34 = 50.0f;
        D_ovl0E_01_80046D3C->unk38 = 50.0f;
        D_ovl0E_01_80046D3C->unk40->unk10 = 2600.0f;
        D_ovl0E_01_80046D3C->unk40->unk14 = 1200.0f;
        D_ovl0E_01_80046D3C->unk40->unk18 = 400.0f;
        flags = func_ovl0E_01_80046068(D_ovl0E_01_80046D3C, 0xC0);
        if (flags != 0) {
            if (flags & 0x6000) {
                func_ovl0E_01_80046790(0x7D);
                func_ovl0E_01_800460B8(D_ovl0E_01_80046BB0[0].unk0, 0x04000000);
                func_ovl0E_01_80043578();
            } else {
                func_ovl0E_01_800467B0(0x26, D_ovl0E_01_80046D3C->unk40->unk10, D_ovl0E_01_80046D3C->unk40->unk14,
                                       D_ovl0E_01_80046D3C->unk40->unk18);
            }
        }
    } else if ((D_ovl0E_01_80046BB0[0].unk0->unk40->unkC & 0x40) && func_ovl0E_01_80046490(0x405) == 0) {
        func_ovl0E_01_800434EC();
        func_ovl0E_01_80046480(0x405);
    }
}

void func_ovl0E_01_80043578(void) {
    func_ovl0E_01_80046208(func_ovl0E_01_80044634, NULL, 0, 0, 0x110);
}

void func_ovl0E_01_800434EC(void) {
    func_ovl0E_01_800456F8(0x19, 3, 1, 0x1C, 1, 0x2012);
    func_ovl0E_01_800456F8(0x19, 3, 2, 0x1C, 5, 0x11);
    func_ovl0E_01_80045700(0x19, 4, 2, 0x1C, 5, 5, 0x10);
}

void func_ovl0E_01_80043310(void) {
    UnkStruct_ovl0E_01_80046B70 *p;
    s16 i;
    s32 flags;

    D_ovl0E_01_80046D3C->unk30 = 4;
    D_ovl0E_01_80046D3C->unk34 = 85.0f;
    D_ovl0E_01_80046D3C->unk38 = 400.0f;
    for (i = 0, p = D_ovl0E_01_80046B70; i < 2; i++, p++) {
        if (func_ovl0E_01_80046490(p->unk0) == 0) {
            D_ovl0E_01_80046D3C->unk40->unk10 = p->unk4 * 10.0f;
            D_ovl0E_01_80046D3C->unk40->unk14 = p->unk8 * 10.0f;
            D_ovl0E_01_80046D3C->unk40->unk18 = p->unkC * 10.0f;
            flags = func_ovl0E_01_80046068(D_ovl0E_01_80046D3C, 0xC0);
            if (flags != 0) {
                if (flags & 0x4000) {
                    func_ovl0E_01_800467B0(0x49, D_ovl0E_01_80046D3C->unk40->unk10, D_ovl0E_01_80046D3C->unk40->unk14,
                                           D_ovl0E_01_80046D3C->unk40->unk18);
                    func_ovl0E_01_800460C0(D_ovl0E_01_80046B00[i].unk0, 0x01000000);
                    func_ovl0E_01_80043294(&D_ovl0E_01_80046B00[i]);
                    func_ovl0E_01_80043254(&D_ovl0E_01_80046B70[i]);
                    func_ovl0E_01_80046480(p->unk0);
                } else {
                    func_ovl0E_01_800467B0(0x26, D_ovl0E_01_80046D3C->unk40->unk10, D_ovl0E_01_80046D3C->unk40->unk14,
                                           D_ovl0E_01_80046D3C->unk40->unk18);
                }
            }
        }
    }
}

static void func_ovl0E_01_80043294(UnkStruct_ovl0E_01_80046B00 *e) {
    func_ovl0E_01_800460D0(e->unk0);
    /* 0xFFFF, not -1: never equal to the s16 fields */
    if (e->unkC != 0xFFFF && e->unkE != 0xFFFF && e->unk10 != 0xFFFF && e->unk12 != 0xFFFF) {
        func_ovl0E_01_80045E08(e->unk4);
    }
    e->unk0 = NULL;
    e->unk4 = -1;
}

void func_ovl0E_01_80043254(UnkStruct_ovl0E_01_80046B70 *arg0) {
    func_ovl0E_01_800456F8(arg0->unk14, arg0->unk16, arg0->unk18, arg0->unk1A, arg0->unk1C, arg0->unk1E);
}

void func_ovl0E_01_800431C4(void) {
    if (func_ovl0E_01_80045888(0x17, 2, 0xE, 0x17, 0xF) != 0 &&
        func_ovl0E_01_800430B0(func_ovl0E_01_800458F8(func_ovl0E_01_80045898()), D_ovl0E_01_80046C58.unk0) != 0) {
        if (func_ovl0E_01_80046470(0xA4) != 0) {
            func_ovl0E_01_80045E20(0x291, 1);
        } else {
            func_ovl0E_01_80045E20(0x362, 2);
        }
    }
}

s32 func_ovl0E_01_800430B0(UnkStructA *arg0, UnkStructA *arg1) {
    f32 dz;
    f32 dx;

    func_ovl0E_01_80043060();
    dx = func_ovl0E_01_800463B0(arg0->unk40->unk20) * 80.0f;
    dz = func_ovl0E_01_800463B8(arg0->unk40->unk20);
    D_ovl0E_01_80046D3C->unk30 = 1;
    D_ovl0E_01_80046D3C->unk34 = 30.0f;
    D_ovl0E_01_80046D3C->unk38 = 50.0f;
    D_ovl0E_01_80046D3C->unk40->unk10 = arg0->unk40->unk10 + dx;
    D_ovl0E_01_80046D3C->unk40->unk14 = arg0->unk40->unk14;
    D_ovl0E_01_80046D3C->unk40->unk18 = arg0->unk40->unk18 + dz * 80.0f;
    if (func_ovl0E_01_80046148(D_ovl0E_01_80046D3C, 0x10) != arg1) {
        return FALSE;
    }
    return TRUE;
}

void func_ovl0E_01_80043060(void) {
    if (func_ovl0E_01_80046490(0x400) == 0) {
        D_ovl0E_01_80046D3C = func_ovl0E_01_80046100(-1, 0x80, 0.0f, 0.0f, 0.0f);
        func_ovl0E_01_80046480(0x400);
    }
}

void func_ovl0E_01_80043040(void) {
    func_ovl0E_01_80045900(1);
}

void func_ovl0E_01_80043020(void) {
    func_ovl0E_01_80043018();
    func_ovl0E_01_80045900(1);
}

static void func_ovl0E_01_80043018(void) {
}

void func_ovl0E_01_80043010(void) {
}
