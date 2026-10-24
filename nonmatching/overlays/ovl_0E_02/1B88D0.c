/*
 * NON_MATCHING: ovl_0E_02's game object, complete: every function and its data
 * (.data 0x360 and .rodata 0x60 as the original; .bss laid out as the
 * original's labels, 0x5C where the overlay table gives 0x50); .text 0x10
 * short of 0x1D50.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 185, eu 185, jp 185
 *
 * What still differs in us (words):
 * - func_ovl0E_02_800447F8 (185): ovl_0E_05's 800443B4 (the same code and
 *   the same difference): the original also saves $f26-$f29, which nothing
 *   uses, and is 4 words longer; everything after the prologue is shifted.
 */
#include "common.h"

/*
 * ovl_0E_02's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Much of it is ovl_0E_05's
 * code (nonmatching/overlays/ovl_0E_05) and ovl_17_10's (func_ovl0E_02_80044308
 * and what it calls, with one model pair where ovl_17_10 has three).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_02_800467A8;

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
} UnkStruct_ovl0E_02_80046684; /* size 0x38 */

/* the four movers: each record is passed to its task */
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
} UnkStruct_ovl0E_02_800463DC;

/* the nine other movers: two sets of speeds, chosen by func_ovl0E_02_800451F8()->unk10 */
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
} UnkStruct_ovl0E_02_8004648C;

/* what func_ovl0E_02_800451F8 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_02_800451F8;

/* the argument of func_ovl0E_02_800444BC's task: unk2/unk4 a tile */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} UnkStruct_ovl0E_02_800467A0; /* size 0x8 */

void func_ovl0E_02_800450A8(s32);
void func_ovl0E_02_800450C0(s32);
f32 func_ovl0E_02_800450D0(void);
void func_ovl0E_02_80045100(f32, f32, f32, s32 *, s32);
s32 func_ovl0E_02_80045118(s32, s32, s32);
void func_ovl0E_02_80045130(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_02_80045190(void (*)(UnkStructA *));
void func_ovl0E_02_800451A0(s32, s32, s32);
void func_ovl0E_02_800451E0(void (*)(UnkStructA *));
UnkStruct_ovl0E_02_800451F8 *func_ovl0E_02_800451F8(void);
void func_ovl0E_02_80045258(void);
void func_ovl0E_02_80045260(s32, s32, s32);
void func_ovl0E_02_80045268(void *);
s32 func_ovl0E_02_80045270(s32, s32, s32, s32);
s32 func_ovl0E_02_80045288(void);
void func_ovl0E_02_80045290(s32, f32 *);
void func_ovl0E_02_800452A0(s32);
void func_ovl0E_02_800452A8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_02_800452B8(void);
void func_ovl0E_02_800452F0(s32);
void func_ovl0E_02_800457B0(UnkStructA_40 *, s32);
void func_ovl0E_02_800457B8(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl0E_02_800457F0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_02_800458E8(f32, f32, f32);
void func_ovl0E_02_80045908(f32, f32, f32);
void func_ovl0E_02_80045910(f32 *, f32 *, f32 *);
void func_ovl0E_02_800459C0(s32);
void func_ovl0E_02_800459D0(f32, f32, f32);
f32 func_ovl0E_02_80045A50(f32 *, f32 *);
void func_ovl0E_02_80045AA8(UnkStructA *, s32);
void func_ovl0E_02_80045AB0(UnkStructA *, s32);
UnkStructA *func_ovl0E_02_80045AD0(s32, s32, s32, s32);
UnkStructA *func_ovl0E_02_80045AE0(UnkStructA *);
UnkStructA *func_ovl0E_02_80045AF0(s32, s32, f32, f32, f32);
void func_ovl0E_02_80045B28(UnkStructA *);
void func_ovl0E_02_80045BB8(UnkStructA *);
s32 func_ovl0E_02_80045BF8(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_02_80045C08(void);
void func_ovl0E_02_80045C18(s32);
void *func_ovl0E_02_80045C20(void);
void func_ovl0E_02_80045C40(void);
s32 func_ovl0E_02_80045DB8(s32);
void func_ovl0E_02_80045E78(s32);
void func_ovl0E_02_80045F48(s32, s32, s32);
void func_ovl0E_02_80045F60(u32 (*)[3]);
void func_ovl0E_02_80046048(s32, f32, f32, f32, s32);
void func_ovl0E_02_80046050(s32, f32 *, s32);
void func_ovl0E_02_80046108(s32, s32, s32);
void func_ovl0E_02_80046180(s32);
void func_ovl0E_02_800461A0(s32, f32, f32, f32);
void func_ovl0E_02_800461A8(s32, f32 *);

void func_ovl0E_02_80043010(void);
void func_ovl0E_02_80043020(void);
void func_ovl0E_02_80043040(void);
void func_ovl0E_02_80043068(void);
void func_ovl0E_02_800430B0(void);
void func_ovl0E_02_80043110(void);
void func_ovl0E_02_800431A8(void);
void func_ovl0E_02_80043220(void);
void func_ovl0E_02_80043258(void);
void func_ovl0E_02_80043300(f32);
void func_ovl0E_02_80043348(void);
void func_ovl0E_02_80043460(void);
void func_ovl0E_02_80043480(s32, s32, s32, f32, s32);
void func_ovl0E_02_800434A8(void);
void func_ovl0E_02_800434FC(void);
void func_ovl0E_02_80043550(void);
void func_ovl0E_02_8004359C(void);
void func_ovl0E_02_800437C0(void);
void func_ovl0E_02_800438AC(void);
void func_ovl0E_02_800438B4(void);
void func_ovl0E_02_800438F4(void);
void func_ovl0E_02_8004392C(void);
void func_ovl0E_02_80043A50(s32);
void func_ovl0E_02_80043C08(void);
void func_ovl0E_02_8004405C(UnkStruct_ovl0E_02_800467A0 *, s16, s16);
void func_ovl0E_02_800442D4(void);
void func_ovl0E_02_80044308(void);
void func_ovl0E_02_800444BC(void);
void func_ovl0E_02_80044780(void);
void func_ovl0E_02_800447F8(void);
void func_ovl0E_02_80044B14(UnkStructA *);
void func_ovl0E_02_80044BD8(UnkStructA *);
void func_ovl0E_02_80044C70(s32, UnkStructA *);
void func_ovl0E_02_80044CA4(f32, f32, f32);
void func_ovl0E_02_80044D00(void);
void func_ovl0E_02_80044D18(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0E_02_80043018(void);
static void func_ovl0E_02_80043060(void);
static void func_ovl0E_02_800430F8(void);
static void func_ovl0E_02_80043100(void);
static void func_ovl0E_02_80043108(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_02_80043068() \
    D_ovl0E_02_8004677C = func_ovl0E_02_80045288(); func_ovl0E_02_80045268(&D_ovl0E_02_80046770); func_ovl0E_02_80045290(D_ovl0E_02_8004677C, D_ovl0E_02_80046760)

/* func_ovl0E_02_80043258's body, also written out in the handler's case 5:
 * IDO doesn't inline the function there (nor func_ovl0E_02_800431A8 into
 * it), but the original has both inlined. */
#define UNK_MACRO_ovl0E_02_80043258()                                                                      \
    if (func_ovl0E_02_800451F8()->unk10 != 0) {                                                           \
        func_ovl0E_02_80043220();                                                                         \
    }                                                                                                     \
    UNK_MACRO_ovl0E_02_80043068();                                                                        \
    func_ovl0E_02_800452A8(D_ovl0E_02_800467A8.unk4, 3, 4.0f, D_ovl0E_02_800467A8.unk10, 0, 1, 1)

/* .bss */
f32 D_ovl0E_02_80046760[4];
Vec3f D_ovl0E_02_80046770;
s32 D_ovl0E_02_8004677C;
u8 D_ovl0E_02_80046780[0x4]; /* unused (func_ovl0E_02_80044D50) */
s32 D_ovl0E_02_80046784;
s32 D_ovl0E_02_80046788;
Vec3f D_ovl0E_02_80046790;
UnkStruct_ovl0E_02_800467A0 D_ovl0E_02_800467A0[1];
UnkStruct_ovl0E_02_800467A8 D_ovl0E_02_800467A8;

/* .data */
/* passed to func_ovl0E_02_80045F60: three 12-byte records */
u32 D_ovl0E_02_800463A0[][3] = {
    { 0x9D0000, 0xC000E, 4 },
    { 0x9E0003, 0xE, 4 },
    { 0x9E0002, 0xE, 4 },
};
/* two 12-byte records, each passed to func_ovl0E_02_80046108 */
u32 D_ovl0E_02_800463C4[][3] = {
    { 0, 0, 0xDE },
    { 1, 0xD, 0xEB },
};
UnkStruct_ovl0E_02_800463DC D_ovl0E_02_800463DC[4] = {
    { 0, -1, NULL, 750.0f, -3800.0f, 1750.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 1, -1, NULL, 1450.0f, -3800.0f, 1850.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 2, -1, NULL, 2250.0f, -3800.0f, 550.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
    { 3, -1, NULL, 2850.0f, -3800.0f, 50.0f, 90.0f, 80.0f, 90.0f, 1.6333334f, -3800.0f },
};
UnkStruct_ovl0E_02_8004648C D_ovl0E_02_8004648C[9] = {
    { NULL, 1650.0f, -3800.0f, -3800.0f, 2550.0f, 180.0f, 175.0f, 185.0f, 3.0f, 450.0f, 0, 120.0f, 125.0f, 1.5f },
    { NULL, 1950.0f, -3800.0f, -3800.0f, 2550.0f, 175.0f, 170.0f, 180.0f, 3.0f, 320.0f, 1, 170.0f, 180.0f, 3.0f },
    { NULL, 2250.0f, -3800.0f, -3800.0f, 2550.0f, 170.0f, 165.0f, 175.0f, 3.0f, 200.0f, 0, 115.0f, 120.0f, 1.5f },
    { NULL, 2350.0f, -3800.0f, -3800.0f, 250.0f, 185.0f, 180.0f, 190.0f, 3.0f, 830.0f, 0, 125.0f, 130.0f, 1.5f },
    { NULL, 2550.0f, -3800.0f, -3800.0f, 1050.0f, 170.0f, 165.0f, 175.0f, 3.0f, 115.0f, 0, 115.0f, 120.0f, 1.5f },
    { NULL, 2850.0f, -3800.0f, -3800.0f, 250.0f, 180.0f, 175.0f, 185.0f, 3.0f, 680.0f, 0, 120.0f, 125.0f, 1.5f },
    { NULL, 2850.0f, -3800.0f, -3800.0f, 1050.0f, 175.0f, 170.0f, 180.0f, 3.0f, 200.0f, 1, 170.0f, 180.0f, 3.0f },
    { NULL, 3150.0f, -3800.0f, -3800.0f, 1050.0f, 175.0f, 170.0f, 180.0f, 3.0f, 290.0f, 0, 120.0f, 125.0f, 1.5f },
    { NULL, 3350.0f, -3800.0f, -3800.0f, 250.0f, 175.0f, 170.0f, 180.0f, 3.0f, 550.0f, 0, 120.0f, 125.0f, 1.5f },
};
UnkStruct_ovl0E_02_80046684 D_ovl0E_02_80046684[1] = {
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_02_80046684 D_ovl0E_02_800466BC[1] = {
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0E_02_80044D50(void) {
    D_ovl0E_02_80046780[0] = 0;
}

/* Its references keep func_ovl0E_02_80044B14 and 80044BD8 in address order
 * after 800447F8; without them IDO puts the two (whose addresses
 * 8004392C's inlined 800438F4 takes) before 800447F8 and 80044780, as in
 * ovl_0E_11's 80044BC8. The body itself isn't emitted. */
static void func_ovl0E_02_80044D48(void) {
    func_ovl0E_02_80045190(func_ovl0E_02_80044BD8);
    func_ovl0E_02_800451E0(func_ovl0E_02_80044B14);
}

static void func_ovl0E_02_80044D40(void) {
}

static void func_ovl0E_02_80044D38(void) {
}

static void func_ovl0E_02_80044D30(void) {
}

static void func_ovl0E_02_80044D28(void) {
}

static void func_ovl0E_02_80044D20(void) {
}

void func_ovl0E_02_80044D18(void) {
}

void func_ovl0E_02_80044D00(void) {
    D_ovl0E_02_80046784 = -1;
    D_ovl0E_02_80046788 = -1;
}

void func_ovl0E_02_80044CA4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_02_800458E8(D_ovl0E_02_80046790.x, D_ovl0E_02_80046790.y, D_ovl0E_02_80046790.z);
    func_ovl0E_02_80045908(arg0, arg1, arg2);
    func_ovl0E_02_80045C18(180);
}

void func_ovl0E_02_80044C70(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_02_800461A0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_02_80044BD8(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_02_80045AB0(arg0, 0x01000000);
    func_ovl0E_02_80046050(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_02_80046050(13, pos, 0);
    func_ovl0E_02_800461A8(180, pos);
}

void func_ovl0E_02_80044B14(UnkStructA *arg0) {
    func_ovl0E_02_80045AB0(arg0, 0x04000000);
    func_ovl0E_02_80045C18(10);
    func_ovl0E_02_80045130(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_02_80046180(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_02_80045C18(60);
}

void func_ovl0E_02_800447F8(void) {
    f32 pad[5];
    UnkStruct_ovl0E_02_800463DC *rec;
    f32 a[3];
    f32 b[3];
    f32 pad2[1];

    rec = func_ovl0E_02_80045C20();
    rec->unk8 = func_ovl0E_02_80045AD0(0x1BC, 0x0D080040, 0x20, 0);
    rec->unk8->unk40->unkC |= 0x8000;
    func_ovl0E_02_80045AA8(rec->unk8, 0x0D080040);
    rec->unk10 = rec->unk28;
    rec->unk8->unk40->unk10 = rec->unkC;
    rec->unk8->unk40->unk14 = rec->unk10;
    rec->unk8->unk40->unk18 = rec->unk14;
    func_ovl0E_02_800457B0(rec->unk8->unk40, 2);
    func_ovl0E_02_800457B8(rec->unk8->unk40, 0x1BD, 0, 0);
    func_ovl0E_02_800457B8(rec->unk8->unk40, 0x1BD, 1, 1);
    rec->unk8->unk30 = 4;
    rec->unk8->unk34 = 50.0f;
    rec->unk8->unk38 = 2500.0f;
    func_ovl0E_02_80045C18(func_ovl0E_02_80045DB8(60) + 30);
    while (TRUE) {
        func_ovl0E_02_80045BB8(rec->unk8);
        rec->unk10 += rec->unk18;
        if (rec->unk10 < rec->unk28) {
            rec->unk10 = rec->unk28;
            rec->unk18 = (f32) func_ovl0E_02_80045DB8((s32) (rec->unk20 - rec->unk1C)) + rec->unk1C;
            func_ovl0E_02_80045C18(func_ovl0E_02_80045DB8(60) + 30);
            a[0] = rec->unk8->unk40->unk10;
            a[1] = 0.0f;
            a[2] = rec->unk8->unk40->unk18;
            b[0] = D_ovl0E_02_80046760[0];
            b[1] = 0.0f;
            b[2] = D_ovl0E_02_80046760[2];
            if (func_ovl0E_02_80045A50(a, b) < 800.0f) {
                func_ovl0E_02_800461A0(0x75, rec->unk8->unk40->unk10, rec->unk8->unk40->unk14,
                                       rec->unk8->unk40->unk18);
            }
        }
        rec->unk18 -= rec->unk24;
        rec->unk8->unk40->unk20 += 20.0f;
        rec->unk8->unk40->unk14 = rec->unk10;
        func_ovl0E_02_80045C40();
    }
}

void func_ovl0E_02_80044780(void) {
    UnkStruct_ovl0E_02_800463DC *rec;
    s16 i;

    for (i = 0, rec = D_ovl0E_02_800463DC; i < 4; i++, rec++) {
        rec->unk4 = func_ovl0E_02_80045BF8(func_ovl0E_02_800447F8, rec, 0, 0, 0x110);
    }
}

/* drops the model pair from 10000 at the tile its argument gives */
void func_ovl0E_02_800444BC(void) {
    UnkStruct_ovl0E_02_800467A0 *arg;
    UnkStruct_ovl0E_02_80046684 *a;
    UnkStruct_ovl0E_02_80046684 *b;

    func_ovl0E_02_80045C40();
    arg = func_ovl0E_02_80045C20();
    a = &D_ovl0E_02_80046684[arg->unk0];
    b = &D_ovl0E_02_800466BC[arg->unk0];
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
    func_ovl0E_02_80045AA8(a->unk0, 0x01000000);
    func_ovl0E_02_80045AA8(b->unk0, 0x01000000);
    while (TRUE) {
        func_ovl0E_02_80045B28(a->unk0);
        b->unk0->unk40->unk14 = a->unk0->unk40->unk14;
        if (a->unk0->unk40->unk14 <= func_ovl0E_02_800450D0() ||
            (a->unk0->unk6C == 0.0f && a->unk0->unk68 == 0.0f)) {
            func_ovl0E_02_80045AB0(a->unk0, 0x01000000);
            func_ovl0E_02_80045AB0(b->unk0, 0x01000000);
            func_ovl0E_02_800461A0(0x7C, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
            func_ovl0E_02_80046048(10, a->unk0->unk40->unk10, a->unk0->unk40->unk14 + 10.0f,
                                   a->unk0->unk40->unk18, 0);
            arg->unk6 |= 1;
            func_ovl0E_02_80045C08();
        }
        func_ovl0E_02_80045C40();
    }
}

void func_ovl0E_02_800442D4(void) {
    func_ovl0E_02_800459D0(20.0f, 20.0f, 20.0f);
    func_ovl0E_02_800459C0(120);
}

void func_ovl0E_02_80044308(void) {
    s16 i;
    s16 j;
    s16 n;
    s32 base;
    s32 range;

    func_ovl0E_02_80045C18(300);
    if (func_ovl0E_02_800451F8()->unk10 == 0) {
        n = 2;
        base = 480;
        range = 480;
    } else {
        n = 5;
        base = 240;
        range = 240;
    }
    for (i = 0; i < 1; i++) {
        D_ovl0E_02_800467A0[i].unk0 = i;
    }
    while (TRUE) {
        func_ovl0E_02_800442D4();
        func_ovl0E_02_80045C18(60);
        for (i = 0; i < n; i++) {
            for (j = 0; j < 1; j++) {
                D_ovl0E_02_800467A0[j].unk6 = 0;
            }
            func_ovl0E_02_8004405C(D_ovl0E_02_800467A0, 3, 3);
            func_ovl0E_02_80045BF8(func_ovl0E_02_800444BC, &D_ovl0E_02_800467A0[0], 0, 0, 0x110);
            func_ovl0E_02_80045C40();
            while (TRUE) {
                if (D_ovl0E_02_800467A0[0].unk6 & 1) {
                    break;
                }
                func_ovl0E_02_80045C40();
            }
            func_ovl0E_02_80045C40();
        }
        func_ovl0E_02_80045C18(func_ovl0E_02_80045DB8(range) + base);
    }
}

/* picks a tile for each of arg0's entries around the one func_ovl0E_02_80045100
 * gives for func_ovl0E_02_80045290's position, retrying where
 * func_ovl0E_02_80045118 gives 0xF (at most 6 tries) */
void func_ovl0E_02_8004405C(UnkStruct_ovl0E_02_800467A0 *arg0, s16 arg1, s16 arg2) {
    s16 i;
    s16 j;
    s16 tries;
    s16 xs[1];
    s16 ys[1];
    f32 pos[4];
    s32 here[6];
    s32 v[6];

    func_ovl0E_02_80045290(0, pos);
    func_ovl0E_02_80045100(pos[0], pos[1], pos[2], here, 0);
    for (i = 0, tries = 0; i < 1;) {
        xs[i] = func_ovl0E_02_80045DB8(arg1 * 2);
        ys[i] = func_ovl0E_02_80045DB8(arg2 * 2);
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
                func_ovl0E_02_80045100(0.0f, 10000.0f, 0.0f, v, 0);
                if ((func_ovl0E_02_80045118(here[0] + (xs[i] - arg1), v[1], here[2] + (ys[i] - arg2)) & 0xF) == 0xF) {
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

void func_ovl0E_02_80043C08(void) {
    f32 pad[3];
    UnkStruct_ovl0E_02_8004648C *rec;
    s32 up;
    f32 a[3];
    f32 b[3];
    f32 pad2[1];

    rec = func_ovl0E_02_80045C20();
    rec->unk0 = func_ovl0E_02_80045AD0(0x1BE, 0x01000040, 0x20, 0);
    func_ovl0E_02_80045AE0(rec->unk0);
    rec->unk8 = rec->unkC;
    rec->unk0->unk40->unk10 = rec->unk4;
    rec->unk0->unk40->unk14 = rec->unk8;
    rec->unk0->unk40->unk18 = rec->unk10;
    rec->unk0->unk30 = 1;
    rec->unk0->unk34 = 50.0f;
    rec->unk0->unk38 = 0;
    if (func_ovl0E_02_800451F8()->unk10 == 0) {
        rec->unk14 = (f32) func_ovl0E_02_80045DB8((s32) (rec->unk30 - rec->unk2C)) + rec->unk2C;
    } else {
        rec->unk14 = (f32) func_ovl0E_02_80045DB8((s32) (rec->unk1C - rec->unk18)) + rec->unk18;
    }
    func_ovl0E_02_80045C18(func_ovl0E_02_80045DB8(60) + 30);
    up = 0;
    while (TRUE) {
        func_ovl0E_02_80045BB8(rec->unk0);
        rec->unk8 += rec->unk14;
        if (rec->unk8 < rec->unkC) {
            rec->unk8 = rec->unkC;
            if (func_ovl0E_02_800451F8()->unk10 == 0) {
                rec->unk14 = (f32) func_ovl0E_02_80045DB8((s32) (rec->unk30 - rec->unk2C)) + rec->unk2C;
            } else {
                rec->unk14 = (f32) func_ovl0E_02_80045DB8((s32) (rec->unk1C - rec->unk18)) + rec->unk18;
            }
            if (func_ovl0E_02_800451F8()->unk10 == 0) {
                up = 0;
                func_ovl0E_02_80045C18(func_ovl0E_02_80045DB8(60) + 180);
            } else {
                func_ovl0E_02_80045C18(func_ovl0E_02_80045DB8(60) + 90);
                up = 0;
            }
            a[0] = rec->unk0->unk40->unk10;
            a[1] = 0.0f;
            a[2] = rec->unk0->unk40->unk18;
            b[0] = D_ovl0E_02_80046760[0];
            b[1] = 0.0f;
            b[2] = D_ovl0E_02_80046760[2];
            if (func_ovl0E_02_80045A50(a, b) < 700.0f) {
                func_ovl0E_02_800461A0(0x7B, rec->unk0->unk40->unk10, rec->unk0->unk40->unk14,
                                       rec->unk0->unk40->unk18);
            }
        }
        if (func_ovl0E_02_800451F8()->unk10 == 0) {
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
            func_ovl0E_02_80046048(7, rec->unk4, rec->unk8 + 100.0f, rec->unk10, 0);
        }
        rec->unk0->unk40->unk14 = rec->unk8;
        func_ovl0E_02_80045C40();
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_02_80043A50(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0E_02_8004392C();
            break;
        case 17:
            func_ovl0E_02_80043550();
            break;
        case 18:
            func_ovl0E_02_800434FC();
            break;
        case 19:
            func_ovl0E_02_800434A8();
            break;
        case 4:
            func_ovl0E_02_80043460();
            break;
        case 5:
            UNK_MACRO_ovl0E_02_80043258();
            break;
        case 0x50:
            func_ovl0E_02_80043110();
            break;
        case 3:
            func_ovl0E_02_800430B0();
            break;
        case 12:
            func_ovl0E_02_80043040();
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_02_8004392C(void) {
    UnkStructA *obj;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_02_800438F4();
    func_ovl0E_02_80045F60(D_ovl0E_02_800463A0);
    func_ovl0E_02_800450A8(0x187);
    obj = func_ovl0E_02_80045AF0(0x188, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_02_80045AA8(obj, 0x01000000);
    p = D_ovl0E_02_800463C4;
    count = 2;
    for (i = 0; i < count; i++) {
        func_ovl0E_02_80046108((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_02_800450C0(0x191);
    func_ovl0E_02_80045258();
    if (func_ovl0E_02_800451F8()->unk10 != 0) {
        func_ovl0E_02_800437C0();
    }
    func_ovl0E_02_8004359C();
    func_ovl0E_02_800457F0(obj->unk40, 0, 2, 0x400, 0, 0);
    func_ovl0E_02_80045F48(0xFF, 0xA1, 0x1D);
}

void func_ovl0E_02_800438F4(void) {
    func_ovl0E_02_800438B4();
    func_ovl0E_02_80045190(func_ovl0E_02_80044BD8);
    func_ovl0E_02_800451E0(func_ovl0E_02_80044B14);
}

void func_ovl0E_02_800438B4(void) {
    func_ovl0E_02_80045E78(0x400);
    func_ovl0E_02_80045E78(0x401);
    func_ovl0E_02_80045E78(0x402);
    func_ovl0E_02_80045E78(0x403);
    func_ovl0E_02_80045E78(0x404);
}

void func_ovl0E_02_800438AC(void) {
}

static void func_ovl0E_02_80043640(UnkStruct_ovl0E_02_80046684 *e) {
    e->unk0 = func_ovl0E_02_80045AF0(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0E_02_80045AA8(e->unk0, 0x01080000);
    func_ovl0E_02_80045AB0(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl0E_02_800457F0(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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

void func_ovl0E_02_800437C0(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 1; i++) {
        func_ovl0E_02_80043640(&D_ovl0E_02_80046684[i]);
        obj = func_ovl0E_02_80045AE0(D_ovl0E_02_80046684[i].unk0);
        obj->unk54 = 4.0f;
        obj->unk4C = 4.0f;
        obj->unk40->unk36 = 0xCC;
        func_ovl0E_02_80045AB0(D_ovl0E_02_80046684[i].unk0, 0x80000);
        func_ovl0E_02_80045AB0(D_ovl0E_02_80046684[i].unk0, 0x01000000);
        func_ovl0E_02_80043640(&D_ovl0E_02_800466BC[i]);
        func_ovl0E_02_80045AB0(D_ovl0E_02_800466BC[i].unk0, 0x01000000);
    }
}

void func_ovl0E_02_8004359C(void) {
    UnkStruct_ovl0E_02_800451F8 *state;
    UnkStruct_ovl0E_02_8004648C *rec;
    s16 i;

    state = func_ovl0E_02_800451F8();
    for (i = 0, rec = D_ovl0E_02_8004648C; i < 9; i++, rec++) {
        if (state->unk10 != 0 || rec->unk28 != 1) {
            func_ovl0E_02_80045BF8(func_ovl0E_02_80043C08, rec, 0, 0, 0x110);
        }
    }
}

void func_ovl0E_02_80043550(void) {
    func_ovl0E_02_80045260(0, 2, 0x16);
    func_ovl0E_02_80043480(1, 0x40, 1, 0.0f, 0);
}

void func_ovl0E_02_800434FC(void) {
    func_ovl0E_02_80045260(1, 2, 0x16);
    func_ovl0E_02_80043480(2, 0x40, 1, -90.0f, 2);
}

void func_ovl0E_02_800434A8(void) {
    func_ovl0E_02_80045260(0x2E, 1, 0x17);
    func_ovl0E_02_80043480(3, 0xC0, 1, 0.0f, 2);
}

void func_ovl0E_02_80043480(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_02_800467A8.unk0 = arg0;
    D_ovl0E_02_800467A8.unk4 = arg1;
    D_ovl0E_02_800467A8.unk8 = arg2;
    D_ovl0E_02_800467A8.unkC = arg3;
    D_ovl0E_02_800467A8.unk10 = arg4;
}

void func_ovl0E_02_80043460(void) {
    func_ovl0E_02_80043348();
}

void func_ovl0E_02_80043348(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_02_800452B8();
    switch (D_ovl0E_02_800467A8.unk8) {
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
        func_ovl0E_02_80045908(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_02_800467A8.unkC;
        func_ovl0E_02_80045910(&sp1C, NULL, NULL);
        func_ovl0E_02_80045908(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_02_800452A0(D_ovl0E_02_800467A8.unk4);
}

void func_ovl0E_02_80043300(f32 arg0) {
    f32 sp1C;

    func_ovl0E_02_80045910(&sp1C, NULL, NULL);
    func_ovl0E_02_80045908(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_02_80043258(void) {
    UNK_MACRO_ovl0E_02_80043258();
}

void func_ovl0E_02_80043220(void) {
    func_ovl0E_02_80045BF8(func_ovl0E_02_80044308, NULL, 0, 0, 0x110);
}

void func_ovl0E_02_800431A8(void) {
    UNK_MACRO_ovl0E_02_80043068();
    func_ovl0E_02_800452A8(D_ovl0E_02_800467A8.unk4, 3, 4.0f, D_ovl0E_02_800467A8.unk10, 0, 1, 1);
}

void func_ovl0E_02_80043110(void) {
    func_ovl0E_02_800430F8();
    func_ovl0E_02_80043100();
    func_ovl0E_02_80043108();
    if (func_ovl0E_02_80045270(1, 0x16, 1, 0x17) != 0) {
        D_ovl0E_02_80046784 = 0x4A;
        D_ovl0E_02_80046788 = 0x13;
        func_ovl0E_02_800451A0(0x4A, 0x13, 0);
    }
    if (func_ovl0E_02_80045270(0x2E, 0x16, 0x2E, 0x17) != 0) {
        D_ovl0E_02_80046784 = 0x48;
        D_ovl0E_02_80046788 = 0x13;
        func_ovl0E_02_800451A0(0x48, 0x13, 0);
    }
}

static void func_ovl0E_02_80043108(void) {
}

static void func_ovl0E_02_80043100(void) {
}

static void func_ovl0E_02_800430F8(void) {
}

void func_ovl0E_02_800430B0(void) {
    UNK_MACRO_ovl0E_02_80043068();
    func_ovl0E_02_80043010();
}

void func_ovl0E_02_80043068(void) {
    func_ovl0E_02_80043060();
    UNK_MACRO_ovl0E_02_80043068();
}

static void func_ovl0E_02_80043060(void) {
}

void func_ovl0E_02_80043040(void) {
    func_ovl0E_02_800452F0(1);
}

void func_ovl0E_02_80043020(void) {
    func_ovl0E_02_80043018();
    func_ovl0E_02_800452F0(1);
}

static void func_ovl0E_02_80043018(void) {
}

void func_ovl0E_02_80043010(void) {
}
