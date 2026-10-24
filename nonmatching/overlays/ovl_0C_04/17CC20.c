/*
 * NON_MATCHING: ovl_0C_04's game object, complete: every function and its
 * data (.text 0x15C0, .data 0x160, .rodata 0x60 as the original), with
 * ovl_0C_05's skeleton.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 12
 *
 * What still differs in us (words):
 * - func_ovl0C_04_80043878 (2): the epilogue restores s2, s1, s0; the
 *   original restores s0 first, as in ovl_0C_08's 80043654 and ovl_0E_13's
 *   80043940 (the setup of D_ovl0C_04_80045D34 is inlined there: a static
 *   taking its address does the same).
 * - func_ovl0C_04_80043FC0 (10): D_ovl0C_04_80045C58's address for the
 *   first call goes in v1 and is scheduled ahead of the task argument's
 *   copy; the original reuses v0 after it.
 */
#include "common.h"

/*
 * ovl_0C_04's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).  The same skeleton as
 * ovl_0C_03's 17A5B0 and ovl_0C_05's 17F9F0.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_04_80045E10;

/* one record, set up by the setup function's inlined static */
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
} UnkStruct_ovl0C_04_80045D34;

/* the task func_ovl0C_04_80043FC0's record */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s32 unk28;
} UnkStruct_ovl0C_04_80045C58;

/* a chain of records (unk2 is the next one's index, 0 ends it), each the
 * task func_ovl0C_04_80043D3C's */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
} UnkStruct_ovl0C_04_80045C84;

void func_ovl0C_04_80044918(s32);
void func_ovl0C_04_80044930(s32);
void func_ovl0C_04_80044958(s32, s32, s32, s32, s32, s32);
void func_ovl0C_04_80044960(s32, s32, s32, s32, s32, s32, s32);
void func_ovl0C_04_800449A0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_04_80044A00(void (*)(UnkStructA *));
void func_ovl0C_04_80044A10(s32, s32, s32);
void func_ovl0C_04_80044A50(void (*)(UnkStructA *));
void func_ovl0C_04_80044AA0(s32, s32);
void func_ovl0C_04_80044AB8(s32);
void func_ovl0C_04_80044AC8(void);
void func_ovl0C_04_80044AD0(s32, s32, s32);
void func_ovl0C_04_80044AD8(void *);
s32 func_ovl0C_04_80044AE0(s32, s32, s32, s32);
s32 func_ovl0C_04_80044AF8(void);
void func_ovl0C_04_80044B00(s32, void *);
void func_ovl0C_04_80044B08(s32);
void func_ovl0C_04_80044B10(s32);
void func_ovl0C_04_80044B18(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_04_80044B28(void);
UnkStructA *func_ovl0C_04_80044B58(s32);
void func_ovl0C_04_80044B60(s32);
s32 func_ovl0C_04_80045060(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0C_04_80045158(f32, f32, f32);
void func_ovl0C_04_80045178(f32, f32, f32);
void func_ovl0C_04_80045180(f32 *, f32 *, f32 *);
void func_ovl0C_04_80045210(f32, f32);
void func_ovl0C_04_80045318(UnkStructA *, s32);
void func_ovl0C_04_80045320(UnkStructA *, s32);
void func_ovl0C_04_80045330(UnkStructA *);
UnkStructA *func_ovl0C_04_80045340(s32, s32, s32, s32);
UnkStructA *func_ovl0C_04_80045360(s32, s32, f32, f32, f32);
void func_ovl0C_04_80045398(UnkStructA *);
void func_ovl0C_04_80045468(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_04_80045478(void);
void func_ovl0C_04_80045488(s32);
void *func_ovl0C_04_80045490(void);
/* returning a value: as void, 80043FC0's loop gets v0 where it has v1 */
s32 func_ovl0C_04_800454B0(void);
f32 func_ovl0C_04_80045610(f32);
void func_ovl0C_04_800456E0(s32);
void func_ovl0C_04_800456E8(s32);
s32 func_ovl0C_04_800456F0(s32);
void func_ovl0C_04_800457D0(u32 (*)[3]);
void func_ovl0C_04_800458B8(s32, f32, f32, f32, s32);
void func_ovl0C_04_80045978(s32, s32, s32);
void func_ovl0C_04_800459F0(s32);
void func_ovl0C_04_80045A10(s32, f32, f32, f32);

void func_ovl0C_04_80043010(void);
void func_ovl0C_04_80043020(void);
void func_ovl0C_04_80043040(void);
void func_ovl0C_04_80043068(void);
void func_ovl0C_04_800430B0(void);
void func_ovl0C_04_80043108(void);
void func_ovl0C_04_80043170(void);
void func_ovl0C_04_800431E8(void);
void func_ovl0C_04_80043230(void);
void func_ovl0C_04_800432BC(void);
void func_ovl0C_04_80043338(void);
void func_ovl0C_04_80043390(f32);
void func_ovl0C_04_800433D8(void);
void func_ovl0C_04_80043508(void);
void func_ovl0C_04_80043544(s32, s32, s32, f32, s32);
void func_ovl0C_04_8004356C(void);
void func_ovl0C_04_800435B8(void);
void func_ovl0C_04_80043610(void);
static void func_ovl0C_04_8004365C(void);
void func_ovl0C_04_80043664(void);
void func_ovl0C_04_80043720(void);
static void func_ovl0C_04_800437F8(void);
void func_ovl0C_04_80043800(void);
void func_ovl0C_04_80043840(void);
void func_ovl0C_04_80043878(void);
void func_ovl0C_04_80043ACC(s32);
void func_ovl0C_04_80043C7C(void);
void func_ovl0C_04_80043D00(void);
void func_ovl0C_04_80043D3C(void);
void func_ovl0C_04_80043FC0(void);
void func_ovl0C_04_800441EC(UnkStructA *);
void func_ovl0C_04_800442AC(UnkStructA *);
void func_ovl0C_04_800442F0(UnkStructA *, s32, s32, f32, f32);
void func_ovl0C_04_800443C8(void);
void func_ovl0C_04_800444D8(s32, UnkStructA *);
void func_ovl0C_04_8004450C(f32, f32, f32);
void func_ovl0C_04_80044568(void);
void func_ovl0C_04_80044580(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0C_04_80043018(void);
static void func_ovl0C_04_80043060(void);
static void func_ovl0C_04_800430F8(void);
static void func_ovl0C_04_80043100(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0C_04_800430B0() \
    D_ovl0C_04_80045DEC = func_ovl0C_04_80044AF8(); func_ovl0C_04_80044AD8(&D_ovl0C_04_80045DE0); func_ovl0C_04_80044B00(D_ovl0C_04_80045DEC, D_ovl0C_04_80045DD0)

/* .bss */
u8 D_ovl0C_04_80045DD0[0x10];
Vec3f D_ovl0C_04_80045DE0;
s32 D_ovl0C_04_80045DEC;
u8 D_ovl0C_04_80045DF0[0x4]; /* unused (func_ovl0C_04_80044580) */
s32 D_ovl0C_04_80045DF4;
s32 D_ovl0C_04_80045DF8;
u8 D_ovl0C_04_80045DFC[0x4]; /* unused (func_ovl0C_04_80044580) */
Vec3f D_ovl0C_04_80045E00;
UnkStructA *D_ovl0C_04_80045E0C;
UnkStruct_ovl0C_04_80045E10 D_ovl0C_04_80045E10;

/* .data */
/* passed to func_ovl0C_04_800457D0: three 12-byte records */
u32 D_ovl0C_04_80045C10[][3] = {
    { 0x910002, 0xE, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
/* three 12-byte records, each passed to func_ovl0C_04_80045978 */
u32 D_ovl0C_04_80045C34[][3] = {
    { 0, 5, 0x34F },
    { 1, 0x23, 0xE2 },
    { 2, 0x26, 0xF5 },
};
UnkStruct_ovl0C_04_80045C58 D_ovl0C_04_80045C58[] = {
    { NULL, 2950.0f, 500.0f, 750.0f, 0x1B, 3, 8, 0x20, 0x14, 90.0f, 0 },
};
UnkStruct_ovl0C_04_80045C84 D_ovl0C_04_80045C84[] = {
    { 0, 1, NULL, 3200.0f, 0.0f, 1000.0f, 0x20, 0, 0xA, 2, 0x401, 0x410 },
    { 1, 2, NULL, 3200.0f, 0.0f, 1500.0f, 0x20, 0, 0xF, 2, 0x402, 0x410 },
    { 2, 3, NULL, 3200.0f, 0.0f, 2000.0f, 0x20, 0, 0x14, 2, 0x403, 0x410 },
    { 3, 0, NULL, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0 },
};
UnkStruct_ovl0C_04_80045D34 D_ovl0C_04_80045D34 = {
    NULL, -1, 0x2B5, -5, -0x400, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
};

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0C_04_800445C0(void) {
}

static void func_ovl0C_04_800445B8(void) {
}

static void func_ovl0C_04_800445B0(void) {
}

static void func_ovl0C_04_800445A8(void) {
}

static void func_ovl0C_04_800445A0(void) {
}

static void func_ovl0C_04_80044598(void) {
}

static void func_ovl0C_04_80044590(void) {
}

static void func_ovl0C_04_80044588(void) {
}

void func_ovl0C_04_80044580(void) {
    /* a fake: the reference keeps the two unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl0C_04_80045DF0[0] = D_ovl0C_04_80045DFC[0];
    }
}

void func_ovl0C_04_80044568(void) {
    D_ovl0C_04_80045DF4 = -1;
    D_ovl0C_04_80045DF8 = -1;
}

void func_ovl0C_04_8004450C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_04_80045158(D_ovl0C_04_80045E00.x, D_ovl0C_04_80045E00.y, D_ovl0C_04_80045E00.z);
    func_ovl0C_04_80045178(arg0, arg1, arg2);
    func_ovl0C_04_80045488(180);
}

void func_ovl0C_04_800444D8(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_04_80045A10(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_04_800443C8(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_04_80045490();
    func_ovl0C_04_80045A10(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_04_80045340(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_04_800442F0(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_04_800454B0();
    }
    func_ovl0C_04_80045330(obj);
    func_ovl0C_04_80045478();
}

void func_ovl0C_04_800442F0(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0C_04_80045610((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_04_80045610((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_04_800442AC(UnkStructA *arg0) {
    func_ovl0C_04_80045320(arg0, 0x01000000);
    func_ovl0C_04_80045468(func_ovl0C_04_800443C8, arg0, 0, 0, 0x150);
}

void func_ovl0C_04_800441EC(UnkStructA *arg0) {
    func_ovl0C_04_80045488(10);
    func_ovl0C_04_800449A0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_04_80045488(60);
}

void func_ovl0C_04_80043FC0(void) {
    UnkStruct_ovl0C_04_80045C58 *rec;
    UnkStructA *obj;
    f32 dist;
    f32 speed;
    s16 alpha;

    rec = func_ovl0C_04_80045490();
    obj = rec->unk0;
    func_ovl0C_04_80044958(D_ovl0C_04_80045C58->unk10, D_ovl0C_04_80045C58->unk14, D_ovl0C_04_80045C58->unk18,
                           D_ovl0C_04_80045C58->unk1C, D_ovl0C_04_80045C58->unk20, 0x10);
    if (rec->unk28 != 0) {
        for (dist = 0.0f, speed = 0.0f; dist < 25.0f; speed += 0.5f) {
            func_ovl0C_04_800454B0();
            dist += speed;
            obj->unk40->unk24 += speed;
        }
        obj->unk40->unk24 = 25.0f;
        func_ovl0C_04_80045A10(0x43, 1600.0f, 700.0f, 2750.0f);
    }
    func_ovl0C_04_80045318(rec->unk0, 0x80000);
    obj->unk68 = 0.0f;
    obj->unk70 = 1.6333334f;
    alpha = 0xFF;
    while (TRUE) {
        alpha -= 10;
        if (rec->unk28 == 0) {
            func_ovl0C_04_80045398(obj);
        }
        if (alpha < 0) {
            if (rec->unk28 == 0) {
                func_ovl0C_04_80045A10(0x43, 3000.0f, 500.0f, 1400.0f);
            }
            alpha = 0;
            func_ovl0C_04_80045320(rec->unk0, 0x01000000);
            if (rec->unk28 != 0) {
                func_ovl0C_04_80044958(0xE, 4, 0x19, 0xF, 0x1A, 0x11);
            }
            func_ovl0C_04_80045330(rec->unk0);
            func_ovl0C_04_80045478();
        }
        rec->unk0->unk40->unk36 = alpha;
        func_ovl0C_04_800454B0();
    }
}

void func_ovl0C_04_80043D3C(void) {
    UnkStruct_ovl0C_04_80045C84 *rec;
    UnkStructA *obj;
    s16 alpha;
    s32 i;

    rec = func_ovl0C_04_80045490();
    obj = rec->unk4;
    obj->unk30 = 4;
    obj->unkC = 0xC0;
    obj->unk34 = 50.0f;
    obj->unk38 = 100.0f;
    while (TRUE) {
        if ((obj->unk10 & 0xC0) && func_ovl0C_04_800456F0(rec->unk24) == 0) {
            func_ovl0C_04_800456E0(rec->unk24);
            func_ovl0C_04_800458B8(0xF, rec->unk8, rec->unkC, rec->unk10, 0);
            func_ovl0C_04_800459F0(0x49);
            func_ovl0C_04_80045318(rec->unk4, 0x80000);
            alpha = 0xFF;
            while (TRUE) {
                alpha -= 10;
                if (alpha < 0) {
                    alpha = 0;
                    func_ovl0C_04_80045320(rec->unk4, 0x01000000);
                    func_ovl0C_04_80044960(rec->unk14, rec->unk20, rec->unk1C, rec->unk14, rec->unk18, rec->unk1C, 0x10);
                    func_ovl0C_04_80044958(rec->unk14, rec->unk18, rec->unk1C, rec->unk14, rec->unk1C, 0x11);
                    /* indexed: a pointer walk keeps &D_ovl0C_04_80045C84[0] in
                     * one register where the original materializes it */
                    i = 0;
                    while (D_ovl0C_04_80045C84[i].unk2 != 0) {
                        if (func_ovl0C_04_800456F0(D_ovl0C_04_80045C84[i].unk24) == 0) {
                            break;
                        }
                        i = D_ovl0C_04_80045C84[i].unk2;
                    }
                    if (D_ovl0C_04_80045C84[i].unk2 == 0 && func_ovl0C_04_800456F0(rec->unk28) == 0) {
                        func_ovl0C_04_800456E0(rec->unk28);
                        func_ovl0C_04_80043D00();
                    }
                    func_ovl0C_04_80045330(rec->unk4);
                    func_ovl0C_04_80045478();
                }
                rec->unk4->unk40->unk36 = alpha;
                func_ovl0C_04_800454B0();
            }
        }
        func_ovl0C_04_800454B0();
    }
}

void func_ovl0C_04_80043D00(void) {
    func_ovl0C_04_80045468(func_ovl0C_04_80043FC0, D_ovl0C_04_80045C58, 0, 0, 0x110);
}

void func_ovl0C_04_80043C7C(void) {
    UnkStructA *obj;
    s32 alpha;
    s32 step;

    func_ovl0C_04_80044B08(1);
    func_ovl0C_04_80045488(10);
    obj = func_ovl0C_04_80044B58(func_ovl0C_04_80044AF8());
    func_ovl0C_04_800459F0(0x44);
    func_ovl0C_04_80045318(obj, 0x80000);
    step = 0x11;
    for (alpha = 0xFF; alpha > 0; alpha -= step) {
        obj->unk40->unk36 = alpha;
        func_ovl0C_04_800454B0();
    }
    obj->unk40->unk36 = 0;
    func_ovl0C_04_80045478();
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0C_04_80043ACC(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0C_04_80043878();
            break;
        case 17:
            func_ovl0C_04_80043610();
            break;
        case 18:
            func_ovl0C_04_800435B8();
            break;
        case 19:
            func_ovl0C_04_8004356C();
            break;
        case 4:
            func_ovl0C_04_800433D8();
            if (D_ovl0C_04_80045E10.unk0 == 2) {
                func_ovl0C_04_80043338();
            }
            break;
        case 5:
            if (D_ovl0C_04_80045E10.unk0 == 2) {
                func_ovl0C_04_80043230();
            }
            func_ovl0C_04_80044B18(D_ovl0C_04_80045E10.unk4, 3, 4.0f, D_ovl0C_04_80045E10.unk10, 0, 1, 1);
            if (func_ovl0C_04_800456F0(0x410) == 0) {
                func_ovl0C_04_80043170();
            }
            break;
        case 0x50:
            func_ovl0C_04_80043108();
            break;
        case 3:
            UNK_MACRO_ovl0C_04_800430B0();
            break;
        case 12:
            func_ovl0C_04_80044B60(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

/* 80043800, 80043840, 80043720 and 80043664 are defined above their caller
 * 80043878, as in ovl_0C_05: it pulls them out after itself in its call
 * order (with the two empty statics).  80043720 and 80043664 are not
 * static: as statics IDO inlines them. */
void func_ovl0C_04_80043800(void) {
    func_ovl0C_04_800456E8(0x400);
    func_ovl0C_04_800456E8(0x401);
    func_ovl0C_04_800456E8(0x402);
    func_ovl0C_04_800456E8(0x403);
    func_ovl0C_04_800456E8(0x404);
}

void func_ovl0C_04_80043840(void) {
    func_ovl0C_04_80043800();
    func_ovl0C_04_80044A00(func_ovl0C_04_800442AC);
    func_ovl0C_04_80044A50(func_ovl0C_04_800441EC);
}

void func_ovl0C_04_80043720(void) {
    UnkStruct_ovl0C_04_80045C58 *p;
    UnkStructA *obj;
    s16 i;

    for (i = 0; i < 1; i++) {
        p = &D_ovl0C_04_80045C58[i];
        obj = func_ovl0C_04_80045360(0x2AA, 0xD0, p->unk4, p->unk8, p->unkC);
        func_ovl0C_04_80045318(obj, 0x01000000);
        p->unk0 = obj;
        obj->unk40->unk20 = p->unk24;
        func_ovl0C_04_80044958(D_ovl0C_04_80045C58->unk10, D_ovl0C_04_80045C58->unk14, D_ovl0C_04_80045C58->unk18,
                               D_ovl0C_04_80045C58->unk1C, D_ovl0C_04_80045C58->unk20, 0x11);
    }
}

void func_ovl0C_04_80043664(void) {
    UnkStruct_ovl0C_04_80045C84 *p;
    UnkStructA *obj;

    for (p = D_ovl0C_04_80045C84; p->unk2 != 0; p++) {
        if (func_ovl0C_04_800456F0(p->unk24) == 0) {
            obj = func_ovl0C_04_80045360(0x2AB, 0x20, p->unk8, p->unkC, p->unk10);
            func_ovl0C_04_80045318(obj, 0x01000000);
            p->unk4 = obj;
            func_ovl0C_04_80044960(p->unk14, p->unk20, p->unk1C, p->unk14, p->unk18, p->unk1C, 0x1F);
        }
    }
}

void func_ovl0C_04_80043878(void) {
    UnkStruct_ovl0C_04_80045D34 *rec;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0C_04_80043840();
    func_ovl0C_04_800457D0(D_ovl0C_04_80045C10);
    p = D_ovl0C_04_80045C34;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl0C_04_80045978((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0C_04_80044918(0x245);
    func_ovl0C_04_80044930(0x24F);
    func_ovl0C_04_80044AC8();
    func_ovl0C_04_800437F8();
    if (func_ovl0C_04_800456F0(0x410) == 0) {
        func_ovl0C_04_80043720();
        func_ovl0C_04_80043664();
    }
    func_ovl0C_04_8004365C();
    rec = &D_ovl0C_04_80045D34;
    rec->unk0 = func_ovl0C_04_80045360(rec->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0C_04_80045318(rec->unk0, 0x01080000);
    func_ovl0C_04_80045320(rec->unk0, 0x02000000);
    if (rec->unkC != -1 && rec->unkE != -1 && rec->unk10 != -1 && rec->unk12 != -1) {
        rec->unk4 = func_ovl0C_04_80045060(rec->unk0->unk40, 0, rec->unkC, rec->unkE, rec->unk10, rec->unk12);
        if (rec->unk4 == -1) {
            for (;;) {
            }
        }
    }
    rec->unk0->unk40->unk10 = rec->unk14 * 10.0f;
    rec->unk0->unk40->unk14 = rec->unk18 * 10.0f;
    rec->unk0->unk40->unk18 = rec->unk1C * 10.0f;
    rec->unk0->unk40->unk1C = rec->unk20;
    rec->unk0->unk40->unk20 = rec->unk24;
    rec->unk0->unk40->unk24 = rec->unk28;
    rec->unk0->unk40->unk28 = rec->unk2C;
    rec->unk0->unk40->unk2C = rec->unk30;
    rec->unk0->unk40->unk30 = rec->unk34;
}

/* the empty statics 80043878 calls: their stubs are where the original
 * has them */
static void func_ovl0C_04_800437F8(void) {
}

static void func_ovl0C_04_8004365C(void) {
}

void func_ovl0C_04_80043610(void) {
    func_ovl0C_04_80044AD0(0x17, 2, 0x1C);
    func_ovl0C_04_80043544(1, 0, 0, 0.0f, 2);
}

void func_ovl0C_04_800435B8(void) {
    func_ovl0C_04_80044AD0(0x17, 2, 0x1C);
    func_ovl0C_04_80043544(2, 0, 0, 0.0f, 2);
    func_ovl0C_04_80044AA0(0x2B, 0x13);
}

void func_ovl0C_04_8004356C(void) {
    func_ovl0C_04_80044AD0(0x17, 2, 0x1C);
    func_ovl0C_04_80043544(3, 0, 0, 0.0f, 2);
}

void func_ovl0C_04_80043544(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0C_04_80045E10.unk0 = arg0;
    D_ovl0C_04_80045E10.unk4 = arg1;
    D_ovl0C_04_80045E10.unk8 = arg2;
    D_ovl0C_04_80045E10.unkC = arg3;
    D_ovl0C_04_80045E10.unk10 = arg4;
}

void func_ovl0C_04_80043508(void) {
    func_ovl0C_04_800433D8();
    if (D_ovl0C_04_80045E10.unk0 == 2) {
        func_ovl0C_04_80043338();
    }
}

void func_ovl0C_04_800433D8(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_04_80044B28();
    switch (D_ovl0C_04_80045E10.unk8) {
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
        func_ovl0C_04_80045178(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_04_80045E10.unkC;
        func_ovl0C_04_80045180(&sp1C, NULL, NULL);
        func_ovl0C_04_80045178(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_04_80044B10(D_ovl0C_04_80045E10.unk4);
    func_ovl0C_04_80045210(45.0f, 45.1f);
}

void func_ovl0C_04_80043390(f32 arg0) {
    f32 sp1C;

    func_ovl0C_04_80045180(&sp1C, NULL, NULL);
    func_ovl0C_04_80045178(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0C_04_80043338(void) {
    D_ovl0C_04_80045E0C = func_ovl0C_04_80044B58(func_ovl0C_04_80044AF8());
    func_ovl0C_04_80045318(D_ovl0C_04_80045E0C, 0x80000);
    D_ovl0C_04_80045E0C->unk40->unk36 = 0;
}

void func_ovl0C_04_800432BC(void) {
    if (D_ovl0C_04_80045E10.unk0 == 2) {
        func_ovl0C_04_80043230();
    }
    func_ovl0C_04_80044B18(D_ovl0C_04_80045E10.unk4, 3, 4.0f, D_ovl0C_04_80045E10.unk10, 0, 1, 1);
    if (func_ovl0C_04_800456F0(0x410) == 0) {
        func_ovl0C_04_80043170();
    }
}

void func_ovl0C_04_80043230(void) {
    s32 alpha;
    s32 step;

    func_ovl0C_04_80044B08(1);
    func_ovl0C_04_800459F0(0x45);
    step = 0x11;
    for (alpha = 0; alpha < 0xFF; alpha += step) {
        D_ovl0C_04_80045E0C->unk40->unk36 = alpha;
        func_ovl0C_04_800454B0();
    }
    D_ovl0C_04_80045E0C->unk40->unk36 = 0xFF;
    func_ovl0C_04_80045320(D_ovl0C_04_80045E0C, 0x80000);
    func_ovl0C_04_80044B08(0);
}

void func_ovl0C_04_800431E8(void) {
    func_ovl0C_04_80044B18(D_ovl0C_04_80045E10.unk4, 3, 4.0f, D_ovl0C_04_80045E10.unk10, 0, 1, 1);
}

void func_ovl0C_04_80043170(void) {
    UnkStruct_ovl0C_04_80045C84 *p;

    for (p = D_ovl0C_04_80045C84; p->unk2 != 0; p++) {
        if (func_ovl0C_04_800456F0(p->unk24) == 0) {
            func_ovl0C_04_80045468(func_ovl0C_04_80043D3C, p, 0, 0, 0x110);
        }
    }
}

void func_ovl0C_04_80043108(void) {
    func_ovl0C_04_800430F8();
    func_ovl0C_04_80043100();
    if (func_ovl0C_04_80044AE0(0x17, 0x1C, 0x18, 0x1D) != 0) {
        func_ovl0C_04_80045468(func_ovl0C_04_80043C7C, 0, 0, 0, 0x130);
        func_ovl0C_04_80044AB8(60);
        func_ovl0C_04_80044A10(0x29, 0x14, 4);
    }
}

static void func_ovl0C_04_80043100(void) {
}

static void func_ovl0C_04_800430F8(void) {
}

void func_ovl0C_04_800430B0(void) {
    UNK_MACRO_ovl0C_04_800430B0();
}

void func_ovl0C_04_80043068(void) {
    func_ovl0C_04_80043060();
    D_ovl0C_04_80045DEC = func_ovl0C_04_80044AF8();
    func_ovl0C_04_80044AD8(&D_ovl0C_04_80045DE0);
    func_ovl0C_04_80044B00(D_ovl0C_04_80045DEC, D_ovl0C_04_80045DD0);
}

static void func_ovl0C_04_80043060(void) {
}

void func_ovl0C_04_80043040(void) {
    func_ovl0C_04_80044B60(1);
}

void func_ovl0C_04_80043020(void) {
    func_ovl0C_04_80043018();
    func_ovl0C_04_80044B60(1);
}

static void func_ovl0C_04_80043018(void) {
}

void func_ovl0C_04_80043010(void) {
}
