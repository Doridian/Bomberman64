#include "common.h"

/*
 * ovl_0E_05's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_05_80046250;

/* what UnkStructA_40's 0x48 points to (func_ovl0E_05_8004345C) */
typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} UnkStruct_ovl0E_05_48_4;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_ovl0E_05_48_4 *unk4;
} UnkStruct_ovl0E_05_48;

/* UnkStructA_40 with the pointer at 0x48 */
typedef struct {
    /* 0x00 */ u8 unk0[0x48];
    /* 0x48 */ UnkStruct_ovl0E_05_48 *unk48;
} UnkStruct_ovl0E_05_40;

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
} UnkStruct_ovl0E_05_8004615C;

/* the nine movers: each record is passed to its task */
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
} UnkStruct_ovl0E_05_80045F98;

/* the other mover: two sets of speeds, chosen by func_ovl0E_05_80044DA8()->unk10 */
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
} UnkStruct_ovl0E_05_80046124;

/* what func_ovl0E_05_80044DA8 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_05_80044DA8;

void func_ovl0E_05_80044918(const char *);
void func_ovl0E_05_80044C58(s32);
void func_ovl0E_05_80044C70(s32);
void func_ovl0E_05_80044C98(s32, s32, s32, s32, s32, s32);
void func_ovl0E_05_80044CA0(s32, s32, s32, s32, s32, s32, s32);
void func_ovl0E_05_80044CE0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_05_80044D40(void (*)(UnkStructA *));
void func_ovl0E_05_80044D50(s32, s32, s32);
void func_ovl0E_05_80044D90(void (*)(UnkStructA *));
UnkStruct_ovl0E_05_80044DA8 *func_ovl0E_05_80044DA8(void);
void func_ovl0E_05_80044E08(void);
void func_ovl0E_05_80044E10(s32, s32, s32);
void func_ovl0E_05_80044E18(void *);
s32 func_ovl0E_05_80044E20(s32, s32, s32, s32);
s32 func_ovl0E_05_80044E38(void);
void func_ovl0E_05_80044E40(s32, void *);
void func_ovl0E_05_80044E50(s32);
void func_ovl0E_05_80044E58(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_05_80044E68(void);
void func_ovl0E_05_80044EA0(s32);
void func_ovl0E_05_80045360(UnkStructA_40 *, s32);
void func_ovl0E_05_80045368(UnkStructA_40 *, s32, s32, s32);
f32 func_ovl0E_05_80045398(UnkStructA_40 *, s32);
s32 func_ovl0E_05_800453A0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_05_800453A8(s32);
void func_ovl0E_05_80045498(f32, f32, f32);
void func_ovl0E_05_800454B8(f32, f32, f32);
void func_ovl0E_05_800454C0(f32 *, f32 *, f32 *);
f32 func_ovl0E_05_80045600(f32 *, f32 *);
s32 func_ovl0E_05_80045608(UnkStructA *, s32);
void func_ovl0E_05_80045658(UnkStructA *, s32);
void func_ovl0E_05_80045660(UnkStructA *, s32);
void func_ovl0E_05_80045670(UnkStructA *);
UnkStructA *func_ovl0E_05_80045680(s32, s32, s32, s32);
void func_ovl0E_05_80045690(UnkStructA *);
UnkStructA *func_ovl0E_05_800456A0(s32, s32, f32, f32, f32);
void func_ovl0E_05_80045768(UnkStructA *);
s32 func_ovl0E_05_800457A8(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_05_800457B8(void);
void func_ovl0E_05_800457C8(s32);
void *func_ovl0E_05_800457D0(void);
void func_ovl0E_05_800457F0(void);
s32 func_ovl0E_05_80045968(s32);
void func_ovl0E_05_80045A20(s32);
void func_ovl0E_05_80045A28(s32);
s32 func_ovl0E_05_80045A30(s32);
void func_ovl0E_05_80045AF8(s32, s32, s32);
void func_ovl0E_05_80045B10(u32 (*)[3]);
void func_ovl0E_05_80045BF8(s32, f32, f32, f32, s32);
void func_ovl0E_05_80045C00(s32, f32 *, s32);
void func_ovl0E_05_80045CB8(s32, s32, s32);
void func_ovl0E_05_80045D30(s32);
void func_ovl0E_05_80045D50(s32, f32, f32, f32);
void func_ovl0E_05_80045D58(s32, f32 *);

void func_ovl0E_05_80043010(void);
void func_ovl0E_05_80043020(void);
void func_ovl0E_05_80043040(void);
void func_ovl0E_05_80043060(void);
void func_ovl0E_05_800430C8(void);
void func_ovl0E_05_80043100(void);
void func_ovl0E_05_8004327C(void);
void func_ovl0E_05_800432C4(void);
void func_ovl0E_05_8004332C(void);
void func_ovl0E_05_800433C4(void);
void func_ovl0E_05_8004343C(void);
void func_ovl0E_05_8004345C(UnkStruct_ovl0E_05_8004615C *);
void func_ovl0E_05_800434B8(f32);
void func_ovl0E_05_80043500(void);
void func_ovl0E_05_80043618(void);
void func_ovl0E_05_80043658(s32, s32, s32, f32, s32);
void func_ovl0E_05_80043680(void);
void func_ovl0E_05_800436CC(void);
void func_ovl0E_05_8004371C(void);
void func_ovl0E_05_80043768(void);
void func_ovl0E_05_80043808(void);
void func_ovl0E_05_80043810(void);
void func_ovl0E_05_80043860(void);
void func_ovl0E_05_80043ABC(void);
void func_ovl0E_05_80043AC4(void);
void func_ovl0E_05_80043B04(void);
void func_ovl0E_05_80043B3C(void);
void func_ovl0E_05_80043C48(s32);
void func_ovl0E_05_80043DA0(void);
void func_ovl0E_05_80043E10(void);
void func_ovl0E_05_80043E18(void);
void func_ovl0E_05_80043EDC(void);
void func_ovl0E_05_8004433C(void);
void func_ovl0E_05_800443B4(void);
void func_ovl0E_05_800446D4(UnkStructA *);
void func_ovl0E_05_80044798(UnkStructA *);
void func_ovl0E_05_80044830(s32, UnkStructA *);
void func_ovl0E_05_80044864(f32, f32, f32);
void func_ovl0E_05_800448C0(void);
void func_ovl0E_05_800448D8(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0E_05_80043018(void);
static void func_ovl0E_05_80043274(void);
static void func_ovl0E_05_80043314(void);
static void func_ovl0E_05_8004331C(void);
static void func_ovl0E_05_80043324(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_05_8004327C() \
    D_ovl0E_05_8004622C = func_ovl0E_05_80044E38(); func_ovl0E_05_80044E18(&D_ovl0E_05_80046220); func_ovl0E_05_80044E40(D_ovl0E_05_8004622C, D_ovl0E_05_80046210)

/* .bss */
f32 D_ovl0E_05_80046210[4];
Vec3f D_ovl0E_05_80046220;
s32 D_ovl0E_05_8004622C;
u8 D_ovl0E_05_80046230[0x4]; /* unused (func_ovl0E_05_80044908) */
s32 D_ovl0E_05_80046234;
s32 D_ovl0E_05_80046238;
u8 D_ovl0E_05_8004623C[0x4]; /* unused (func_ovl0E_05_80044908) */
Vec3f D_ovl0E_05_80046240;
u8 D_ovl0E_05_8004624C[0x4]; /* unused (func_ovl0E_05_80044908) */
UnkStruct_ovl0E_05_80046250 D_ovl0E_05_80046250;
UnkStructA *D_ovl0E_05_80046264;

/* .data */
/* passed to func_ovl0E_05_80045B10: three 12-byte records */
u32 D_ovl0E_05_80045F50[][3] = {
    { 0x9D0001, 0x6000E, 4 },
    { 0x9E0003, 0xE, 4 },
    { 2, 0, 4 },
};
/* three 12-byte records, each passed to func_ovl0E_05_80045CB8 */
u32 D_ovl0E_05_80045F74[][3] = {
    { 0, 0, 0xDE },
    { 1, 0x22, 0xE0 },
    { 2, 0xD, 0xEB },
};
UnkStruct_ovl0E_05_80045F98 D_ovl0E_05_80045F98[9] = {
    { 0, -1, NULL, 250.0f, -4000.0f, 150.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4000.0f },
    { 1, -1, NULL, 250.0f, -4000.0f, 950.0f, 90.0f, 85.0f, 90.0f, 1.6333334f, -4000.0f },
    { 2, -1, NULL, 650.0f, -4000.0f, 350.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4000.0f },
    { 3, -1, NULL, 650.0f, -4000.0f, 1650.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4000.0f },
    { 4, -1, NULL, 850.0f, -4000.0f, 850.0f, 90.0f, 85.0f, 90.0f, 1.6333334f, -4000.0f },
    { 5, -1, NULL, 1150.0f, -4000.0f, 1150.0f, 90.0f, 85.0f, 90.0f, 1.6333334f, -4000.0f },
    { 6, -1, NULL, 1250.0f, -4000.0f, 50.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4000.0f },
    { 7, -1, NULL, 1850.0f, -4000.0f, 250.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -4000.0f },
    { 8, -1, NULL, 1950.0f, -4000.0f, 850.0f, 90.0f, 85.0f, 90.0f, 1.6333334f, -4000.0f },
};
UnkStruct_ovl0E_05_80046124 D_ovl0E_05_80046124[1] = {
    { NULL, 550.0f, -2100.0f, -2100.0f, 550.0f, 140.0f, 135.0f, 145.0f, 3.0f, 490.0f, 1, 135.0f, 145.0f, 3.0f },
};
UnkStruct_ovl0E_05_8004615C D_ovl0E_05_8004615C[1] = {
    { NULL, -1, 0x1AC, -1, -1, -1, -1, 155.0f, 40.0f, 135.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0E_05_80044908(void) {
    D_ovl0E_05_80046230[0] = D_ovl0E_05_8004623C[0] + D_ovl0E_05_8004624C[0];
}

static void func_ovl0E_05_80044900(void) {
}

static void func_ovl0E_05_800448F8(void) {
}

static void func_ovl0E_05_800448F0(void) {
}

static void func_ovl0E_05_800448E8(void) {
}

static void func_ovl0E_05_800448E0(void) {
}

void func_ovl0E_05_800448D8(void) {
}

void func_ovl0E_05_800448C0(void) {
    D_ovl0E_05_80046234 = -1;
    D_ovl0E_05_80046238 = -1;
}

void func_ovl0E_05_80044864(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_05_80045498(D_ovl0E_05_80046240.x, D_ovl0E_05_80046240.y, D_ovl0E_05_80046240.z);
    func_ovl0E_05_800454B8(arg0, arg1, arg2);
    func_ovl0E_05_800457C8(180);
}

void func_ovl0E_05_80044830(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_05_80045D50(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_05_80044798(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_05_80045660(arg0, 0x01000000);
    func_ovl0E_05_80045C00(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_05_80045C00(13, pos, 0);
    func_ovl0E_05_80045D58(180, pos);
}

void func_ovl0E_05_800446D4(UnkStructA *arg0) {
    func_ovl0E_05_80045660(arg0, 0x04000000);
    func_ovl0E_05_800457C8(10);
    func_ovl0E_05_80044CE0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_05_80045D30(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_05_800457C8(60);
}

void func_ovl0E_05_800443B4(void) {
    UnkStruct_ovl0E_05_80045F98 *rec;
    s32 flag;
    f32 a[3];
    f32 b[3];
    UnkStructA_40 *p;

    rec = func_ovl0E_05_800457D0();
    rec->unk8 = func_ovl0E_05_80045680(0x1BC, 0x0D080040, 0x20, 0);
    rec->unk8->unk40->unkC |= 0x8000;
    func_ovl0E_05_80045658(rec->unk8, 0x0D080040);
    rec->unk10 = rec->unk28;
    rec->unk8->unk40->unk10 = rec->unkC;
    rec->unk8->unk40->unk14 = rec->unk10;
    rec->unk8->unk40->unk18 = rec->unk14;
    func_ovl0E_05_80045360(rec->unk8->unk40, 2);
    func_ovl0E_05_80045368(rec->unk8->unk40, 0x1BD, 0, 0);
    func_ovl0E_05_80045368(rec->unk8->unk40, 0x1BD, 1, 1);
    rec->unk8->unk30 = 4;
    rec->unk8->unk34 = 50.0f;
    rec->unk8->unk38 = 2500.0f;
    func_ovl0E_05_800457C8(func_ovl0E_05_80045968(60) + 30);
    flag = 0;
    while (TRUE) {
        func_ovl0E_05_80045768(rec->unk8);
        rec->unk10 += rec->unk18;
        if (rec->unk10 < rec->unk28) {
            rec->unk10 = rec->unk28;
            rec->unk18 = (f32) func_ovl0E_05_80045968((s32) (rec->unk20 - rec->unk1C)) + rec->unk1C;
            func_ovl0E_05_800457C8(func_ovl0E_05_80045968(60) + 30);
            a[0] = rec->unk8->unk40->unk10;
            a[1] = 0.0f;
            a[2] = rec->unk8->unk40->unk18;
            b[0] = D_ovl0E_05_80046210[0];
            b[1] = 0.0f;
            b[2] = D_ovl0E_05_80046210[2];
            if (func_ovl0E_05_80045600(a, b) < 800.0f) {
                func_ovl0E_05_80045D50(0x75, rec->unk8->unk40->unk10, rec->unk8->unk40->unk14,
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
         * saves and never uses */
        if (flag) {
            rec->unkC = 3.0f;
            rec->unk14 = 5.0f;
        }
        func_ovl0E_05_800457F0();
    }
}

void func_ovl0E_05_80043B3C(void) {
    UnkStructA *obj;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_05_80043AC4();
    func_ovl0E_05_80044D40(func_ovl0E_05_80044798);
    func_ovl0E_05_80044D90(func_ovl0E_05_800446D4);
    func_ovl0E_05_80045B10(D_ovl0E_05_80045F50);
    func_ovl0E_05_80044C58(0x18D);
    obj = func_ovl0E_05_800456A0(0x18E, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_05_80045658(obj, 0x01000000);
    p = D_ovl0E_05_80045F74;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl0E_05_80045CB8((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_05_80044C70(0x194);
    func_ovl0E_05_80044E08();
    func_ovl0E_05_80043860();
    func_ovl0E_05_80043768();
    func_ovl0E_05_800453A0(obj->unk40, 0, 2, 0x400, 0, 0);
    func_ovl0E_05_80045AF8(0xFF, 0xA1, 0x1D);
}

void func_ovl0E_05_8004433C(void) {
    UnkStruct_ovl0E_05_80045F98 *rec;
    s16 i;

    for (i = 0, rec = D_ovl0E_05_80045F98; i < 9; i++, rec++) {
        rec->unk4 = func_ovl0E_05_800457A8(func_ovl0E_05_800443B4, rec, 0, 0, 0x110);
    }
}

void func_ovl0E_05_80043EDC(void) {
    f32 pad[3];
    UnkStruct_ovl0E_05_80046124 *rec;
    s32 up;
    f32 a[3];
    f32 b[3];
    f32 pad2[1];

    rec = func_ovl0E_05_800457D0();
    rec->unk0 = func_ovl0E_05_80045680(0x1BE, 0x01000040, 0x20, 0);
    func_ovl0E_05_80045690(rec->unk0);
    rec->unk8 = rec->unkC;
    rec->unk0->unk40->unk10 = rec->unk4;
    rec->unk0->unk40->unk14 = rec->unk8;
    rec->unk0->unk40->unk18 = rec->unk10;
    rec->unk0->unk30 = 1;
    rec->unk0->unk34 = 50.0f;
    rec->unk0->unk38 = 0;
    if (func_ovl0E_05_80044DA8()->unk10 == 0) {
        rec->unk14 = (f32) func_ovl0E_05_80045968((s32) (rec->unk30 - rec->unk2C)) + rec->unk2C;
    } else {
        rec->unk14 = (f32) func_ovl0E_05_80045968((s32) (rec->unk1C - rec->unk18)) + rec->unk18;
    }
    func_ovl0E_05_800457C8(func_ovl0E_05_80045968(60) + 30);
    up = 0;
    while (TRUE) {
        func_ovl0E_05_80045768(rec->unk0);
        rec->unk8 += rec->unk14;
        if (rec->unk8 < rec->unkC) {
            rec->unk8 = rec->unkC;
            if (func_ovl0E_05_80044DA8()->unk10 == 0) {
                rec->unk14 = (f32) func_ovl0E_05_80045968((s32) (rec->unk30 - rec->unk2C)) + rec->unk2C;
            } else {
                rec->unk14 = (f32) func_ovl0E_05_80045968((s32) (rec->unk1C - rec->unk18)) + rec->unk18;
            }
            if (func_ovl0E_05_80044DA8()->unk10 == 0) {
                up = 0;
                func_ovl0E_05_800457C8(func_ovl0E_05_80045968(60) + 180);
            } else {
                func_ovl0E_05_800457C8(func_ovl0E_05_80045968(60) + 90);
                up = 0;
            }
            a[0] = rec->unk0->unk40->unk10;
            a[1] = 0.0f;
            a[2] = rec->unk0->unk40->unk18;
            b[0] = D_ovl0E_05_80046210[0];
            b[1] = 0.0f;
            b[2] = D_ovl0E_05_80046210[2];
            if (func_ovl0E_05_80045600(a, b) < 700.0f) {
                func_ovl0E_05_80045D50(0x7B, rec->unk0->unk40->unk10, rec->unk0->unk40->unk14,
                                       rec->unk0->unk40->unk18);
            }
        }
        if (func_ovl0E_05_80044DA8()->unk10 == 0) {
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
            func_ovl0E_05_80045BF8(7, rec->unk4, rec->unk8 + 100.0f, rec->unk10, 0);
        }
        rec->unk0->unk40->unk14 = rec->unk8;
        func_ovl0E_05_800457F0();
    }
}

void func_ovl0E_05_80043E18(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_ovl0E_05_8004615C[i].unk0 != NULL) {
            func_ovl0E_05_80045670(D_ovl0E_05_8004615C[i].unk0);
            /* 0xFFFF, not -1: never equal to the s16 fields */
            if (D_ovl0E_05_8004615C[i].unkC != 0xFFFF && D_ovl0E_05_8004615C[i].unkE != 0xFFFF && D_ovl0E_05_8004615C[i].unk10 != 0xFFFF && D_ovl0E_05_8004615C[i].unk12 != 0xFFFF) {
                func_ovl0E_05_800453A8(D_ovl0E_05_8004615C[i].unk4);
            }
            D_ovl0E_05_8004615C[i].unk0 = NULL;
            D_ovl0E_05_8004615C[i].unk4 = -1;
        }
    }
}

void func_ovl0E_05_80043E10(void) {
}

void func_ovl0E_05_80043DA0(void) {
    s32 i;

    for (i = 54; i != 0; i--) {
        func_ovl0E_05_800457F0();
    }
    func_ovl0E_05_80045D50(0x79, 1600.0f, 400.0f, 1400.0f);
    func_ovl0E_05_80045BF8(0x10, 1550.0f, 500.0f, 1350.0f, 0);
    func_ovl0E_05_800457B8();
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_05_80043C48(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0E_05_80043B3C();
            break;
        case 17:
            func_ovl0E_05_8004371C();
            break;
        case 18:
            func_ovl0E_05_800436CC();
            break;
        case 19:
            func_ovl0E_05_80043680();
            break;
        case 4:
            func_ovl0E_05_80043618();
            break;
        case 5:
            func_ovl0E_05_8004343C();
            break;
        case 0x50:
            func_ovl0E_05_8004332C();
            break;
        case 3:
            func_ovl0E_05_800432C4();
            break;
        case 12:
            func_ovl0E_05_80043040();
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_05_80043B04(void) {
    func_ovl0E_05_80043AC4();
    func_ovl0E_05_80044D40(func_ovl0E_05_80044798);
    func_ovl0E_05_80044D90(func_ovl0E_05_800446D4);
}

void func_ovl0E_05_80043AC4(void) {
    func_ovl0E_05_80045A28(0x400);
    func_ovl0E_05_80045A28(0x401);
    func_ovl0E_05_80045A28(0x402);
    func_ovl0E_05_80045A28(0x403);
    func_ovl0E_05_80045A28(0x404);
}

void func_ovl0E_05_80043ABC(void) {
}

void func_ovl0E_05_80043860(void) {
    s32 i;

    func_ovl0E_05_80043810();
    for (i = 0; i < 1; i++) {
        D_ovl0E_05_8004615C[i].unk0 = func_ovl0E_05_800456A0(D_ovl0E_05_8004615C[i].unk8, 0xD0, 0.0f, 0.0f, 0.0f);
        func_ovl0E_05_80045658(D_ovl0E_05_8004615C[i].unk0, 0x01080000);
        func_ovl0E_05_80045660(D_ovl0E_05_8004615C[i].unk0, 0x02000000);
        if (D_ovl0E_05_8004615C[i].unkC != -1 && D_ovl0E_05_8004615C[i].unkE != -1 && D_ovl0E_05_8004615C[i].unk10 != -1 && D_ovl0E_05_8004615C[i].unk12 != -1) {
            D_ovl0E_05_8004615C[i].unk4 = func_ovl0E_05_800453A0(D_ovl0E_05_8004615C[i].unk0->unk40, 0, D_ovl0E_05_8004615C[i].unkC, D_ovl0E_05_8004615C[i].unkE, D_ovl0E_05_8004615C[i].unk10, D_ovl0E_05_8004615C[i].unk12);
            if (D_ovl0E_05_8004615C[i].unk4 == -1) {
                while (TRUE) {
                }
            }
        }
        D_ovl0E_05_8004615C[i].unk0->unk40->unk10 = D_ovl0E_05_8004615C[i].unk14 * 10.0f;
        D_ovl0E_05_8004615C[i].unk0->unk40->unk14 = D_ovl0E_05_8004615C[i].unk18 * 10.0f;
        D_ovl0E_05_8004615C[i].unk0->unk40->unk18 = D_ovl0E_05_8004615C[i].unk1C * 10.0f;
        D_ovl0E_05_8004615C[i].unk0->unk40->unk1C = D_ovl0E_05_8004615C[i].unk20;
        D_ovl0E_05_8004615C[i].unk0->unk40->unk20 = D_ovl0E_05_8004615C[i].unk24;
        D_ovl0E_05_8004615C[i].unk0->unk40->unk24 = D_ovl0E_05_8004615C[i].unk28;
        D_ovl0E_05_8004615C[i].unk0->unk40->unk28 = D_ovl0E_05_8004615C[i].unk2C;
        D_ovl0E_05_8004615C[i].unk0->unk40->unk2C = D_ovl0E_05_8004615C[i].unk30;
        D_ovl0E_05_8004615C[i].unk0->unk40->unk30 = D_ovl0E_05_8004615C[i].unk34;
        /* a fake (ends the block): without it `move a1` for the next call is
         * scheduled into a load delay slot above, not the call's delay slot */
        if (!D_ovl0E_05_8004615C[i].unkE && !D_ovl0E_05_8004615C[i].unkE && !D_ovl0E_05_8004615C[i].unkE) {
        }
        func_ovl0E_05_80045658(D_ovl0E_05_8004615C[i].unk0, 0x02000000);
        func_ovl0E_05_80045660(D_ovl0E_05_8004615C[i].unk0, 0x80000);
        if (((UnkStruct_ovl0E_05_40 *) D_ovl0E_05_8004615C[i].unk0->unk40)->unk48->unk4->unk4 != 0.0f) {
            func_ovl0E_05_80044918("init time error\n");
            while (TRUE) {
            }
        }
    }
}

void func_ovl0E_05_80043810(void) {
    if (func_ovl0E_05_80045A30(0x400) == 0) {
        D_ovl0E_05_80046264 = func_ovl0E_05_800456A0(-1, 0x80, 0.0f, 0.0f, 0.0f);
        func_ovl0E_05_80045A20(0x400);
    }
}

void func_ovl0E_05_80043808(void) {
}

void func_ovl0E_05_80043768(void) {
    UnkStruct_ovl0E_05_80044DA8 *state;
    UnkStruct_ovl0E_05_80046124 *rec;
    s16 i;

    state = func_ovl0E_05_80044DA8();
    for (i = 0, rec = D_ovl0E_05_80046124; i < 1; i++, rec++) {
        if (state->unk10 != 0 || rec->unk28 != 1) {
            func_ovl0E_05_800457A8(func_ovl0E_05_80043EDC, rec, 0, 0, 0x110);
        }
    }
}

void func_ovl0E_05_8004371C(void) {
    func_ovl0E_05_80044E10(0, 0, 5);
    func_ovl0E_05_80043658(1, 0x40, 1, 0.0f, 0);
}

void func_ovl0E_05_800436CC(void) {
    func_ovl0E_05_80044E10(1, 2, 5);
    func_ovl0E_05_80043658(2, 0x40, 1, 0.0f, 2);
}

void func_ovl0E_05_80043680(void) {
    func_ovl0E_05_80044E10(0x19, 1, 0x1D);
    func_ovl0E_05_80043658(3, 0, 1, 0.0f, 3);
}

void func_ovl0E_05_80043658(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_05_80046250.unk0 = arg0;
    D_ovl0E_05_80046250.unk4 = arg1;
    D_ovl0E_05_80046250.unk8 = arg2;
    D_ovl0E_05_80046250.unkC = arg3;
    D_ovl0E_05_80046250.unk10 = arg4;
}

void func_ovl0E_05_80043618(void) {
    func_ovl0E_05_80043500();
    if (func_ovl0E_05_80045A30(0x407) != 0) {
        func_ovl0E_05_8004345C(D_ovl0E_05_8004615C);
        func_ovl0E_05_80043060();
    }
}

void func_ovl0E_05_80043500(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_05_80044E68();
    switch (D_ovl0E_05_80046250.unk8) {
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
        func_ovl0E_05_800454B8(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_05_80046250.unkC;
        func_ovl0E_05_800454C0(&sp1C, NULL, NULL);
        func_ovl0E_05_800454B8(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_05_80044E50(D_ovl0E_05_80046250.unk4);
}

void func_ovl0E_05_800434B8(f32 arg0) {
    f32 sp1C;

    func_ovl0E_05_800454C0(&sp1C, NULL, NULL);
    func_ovl0E_05_800454B8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_05_8004345C(UnkStruct_ovl0E_05_8004615C *arg0) {
    ((UnkStruct_ovl0E_05_40 *) arg0->unk0->unk40)->unk48->unk4->unk4 = func_ovl0E_05_80045398(arg0->unk0->unk40, 0) - 1.0f;
}

void func_ovl0E_05_8004343C(void) {
    func_ovl0E_05_800433C4();
}

void func_ovl0E_05_800433C4(void) {
    UNK_MACRO_ovl0E_05_8004327C();
    func_ovl0E_05_80044E58(D_ovl0E_05_80046250.unk4, 3, 4.0f, D_ovl0E_05_80046250.unk10, 0, 1, 1);
}

void func_ovl0E_05_8004332C(void) {
    func_ovl0E_05_80043314();
    func_ovl0E_05_8004331C();
    func_ovl0E_05_80043324();
    if (func_ovl0E_05_80044E20(1, 5, 1, 6) != 0) {
        D_ovl0E_05_80046234 = 0x4B;
        D_ovl0E_05_80046238 = 0x13;
        func_ovl0E_05_80044D50(0x4B, 0x13, 0);
    }
    if (func_ovl0E_05_80044E20(0x18, 0x1D, 0x1B, 0x1D) != 0) {
        D_ovl0E_05_80046234 = 0x48;
        D_ovl0E_05_80046238 = 0x12;
        func_ovl0E_05_80044D50(0x48, 0x12, 0);
    }
}

static void func_ovl0E_05_80043324(void) {
}

static void func_ovl0E_05_8004331C(void) {
}

static void func_ovl0E_05_80043314(void) {
}

void func_ovl0E_05_800432C4(void) {
    UNK_MACRO_ovl0E_05_8004327C();
    func_ovl0E_05_80043100();
}

void func_ovl0E_05_8004327C(void) {
    func_ovl0E_05_80043274();
    UNK_MACRO_ovl0E_05_8004327C();
}

static void func_ovl0E_05_80043274(void) {
}

void func_ovl0E_05_80043100(void) {
    s32 flags;

    if (((UnkStruct_ovl0E_05_40 *) D_ovl0E_05_8004615C[0].unk0->unk40)->unk48->unk4->unk4 == 0.0f) {
        D_ovl0E_05_80046264->unk30 = 1;
        D_ovl0E_05_80046264->unk34 = 50.0f;
        D_ovl0E_05_80046264->unk38 = 50.0f;
        D_ovl0E_05_80046264->unk40->unk10 = 1600.0f;
        D_ovl0E_05_80046264->unk40->unk14 = 400.0f;
        D_ovl0E_05_80046264->unk40->unk18 = 1400.0f;
        flags = func_ovl0E_05_80045608(D_ovl0E_05_80046264, 0xC0);
        if (flags != 0) {
            if (flags & 0x6000) {
                func_ovl0E_05_80045D30(0x7D);
                func_ovl0E_05_80045658(D_ovl0E_05_8004615C[0].unk0, 0x04000000);
                func_ovl0E_05_800430C8();
            } else {
                func_ovl0E_05_80045D50(0x26, D_ovl0E_05_80046264->unk40->unk10, D_ovl0E_05_80046264->unk40->unk14,
                                       D_ovl0E_05_80046264->unk40->unk18);
            }
        }
    } else if ((D_ovl0E_05_8004615C[0].unk0->unk40->unkC & 0x40) && func_ovl0E_05_80045A30(0x407) == 0) {
        func_ovl0E_05_80043060();
        func_ovl0E_05_80045A20(0x407);
    }
}

void func_ovl0E_05_800430C8(void) {
    func_ovl0E_05_800457A8(func_ovl0E_05_80043DA0, NULL, 0, 0, 0x110);
}

void func_ovl0E_05_80043060(void) {
    func_ovl0E_05_80044C98(0xE, 1, 5, 0x11, 0xF, 0x11);
    func_ovl0E_05_80044CA0(0xE, 2, 5, 0x11, 6, 0xF, 0x10);
}

void func_ovl0E_05_80043040(void) {
    func_ovl0E_05_80044EA0(1);
}

void func_ovl0E_05_80043020(void) {
    func_ovl0E_05_80043018();
    func_ovl0E_05_80044EA0(1);
}

static void func_ovl0E_05_80043018(void) {
}

void func_ovl0E_05_80043010(void) {
}
