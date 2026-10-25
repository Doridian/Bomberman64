/*
 * NON_MATCHING: ovl_0C_09's game object, complete: every function and its
 * data (.data 0x270, .rodata 0xA0 and .bss 0x60 laid out as the original).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 21 (jp 23 as last recorded; not rebuilt for jp here)
 *
 * Float zeros come in two kinds: the original keeps the zero it compares
 * with (written `0`) in one register and the zero it stores (`0.0f`) in
 * another (80045934, 80044610, 80045060).  The movers 80044610 and
 * 80045060 write 80044588's body out (a macro; their frames have no room
 * for its parameters) with the flag and the drop distance in locals, and
 * 80045060's second flag is an s16.
 *
 * What still differs in us (words):
 * - func_ovl0C_09_80043D08 (21): the prologue's schedule (the constants
 *   and the D_ovl0C_09_80047B10 address come out in another order) and the
 *   store of D_ovl0C_09_80047B00 is one slot later.  ovl_12_03's 8004316C
 *   spelling (macro, fake, static defined above) doesn't give it here.
 *   Tried, none below 21: the macro's statements in any order (y=0 first,
 *   z first, the store before the y+=100), the fake dropped or moved to the
 *   top, all on one line, 100.0f * x, y = y + 100.0f, an f32 local copy of
 *   x, s16 z, and a while loop for the count.  Moving the store earlier
 *   or the z store first is worse (36, 59).
 * - func_ovl0C_09_80044BA4: 0 (`hit = FALSE` shares its line with the
 *   while, which keeps it after the lw of obj->unk40).
 */
#include "common.h"

/*
 * ovl_0C_09's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).  The same skeleton as
 * ovl_0C_04's 17CC20 (ovl_0C_06 and ovl_0C_07 share most of the rest).
 */

/* the handler's state, set by func_ovl0C_09_80043730 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_09_80047B28;

/* an object and a position */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl0C_09_80047818;

/* an object, its position and the limits the movers check it against */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} UnkStruct_ovl0C_09_8004782C;

/* a mover: the tasks func_ovl0C_09_80044610 and func_ovl0C_09_80045060
 * take one (unk0 indexes D_ovl0C_09_8004782C) */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
} UnkStruct_ovl0C_09_8004784C;

/* six lifts, each the task func_ovl0C_09_80045934's */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ UnkStructA *unk8;
    /* 0x0C */ UnkStructA *unkC;
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
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ s32 unk44;
} UnkStruct_ovl0C_09_80047890;

/* what func_ovl0C_09_80047020 is given: an object's 0x40 and two numbers */
typedef struct {
    /* 0x00 */ UnkStructA_40 *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_ovl0C_09_80047020;

void func_ovl0C_09_800464D8(s32);
void func_ovl0C_09_800464F0(s32);
void func_ovl0C_09_80046518(s32, s32, s32, s32, s32, s32);
s32 func_ovl0C_09_80046540(s32);
void func_ovl0C_09_80046560(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_09_800465C0(void (*)(UnkStructA *));
void func_ovl0C_09_800465D0(s32, s32, s32);
void func_ovl0C_09_800465F8(void);
void func_ovl0C_09_80046610(void (*)(UnkStructA *));
void func_ovl0C_09_80046640(s32);
void func_ovl0C_09_80046648(s32);
void func_ovl0C_09_80046660(s32, s32);
void func_ovl0C_09_80046678(s32);
void func_ovl0C_09_80046688(void);
void func_ovl0C_09_80046690(s32, s32, s32);
void func_ovl0C_09_80046698(void *);
s32 func_ovl0C_09_800466A0(s32, s32, s32, s32);
s32 func_ovl0C_09_800466B8(void);
void func_ovl0C_09_800466C0(s32, void *);
void func_ovl0C_09_800466C8(s32);
void func_ovl0C_09_800466D0(s32);
void func_ovl0C_09_800466D8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_09_800466E8(void);
UnkStructA *func_ovl0C_09_80046718(s32);
void func_ovl0C_09_80046720(s32);
void func_ovl0C_09_80046788(void);
void func_ovl0C_09_80046C00(UnkStructA_40 *, s32, s32);
f32 func_ovl0C_09_80046C18(UnkStructA_40 *, s32);
void func_ovl0C_09_80046D18(f32, f32, f32);
void func_ovl0C_09_80046D38(f32, f32, f32);
void func_ovl0C_09_80046D40(f32 *, f32 *, f32 *);
void func_ovl0C_09_80046D80(s32);
void func_ovl0C_09_80046DD0(f32, f32);
s32 func_ovl0C_09_80046E88(UnkStructA *, s32);
void func_ovl0C_09_80046EB0(UnkStructA *);
void func_ovl0C_09_80046EB8(UnkStructA *, UnkStructA *);
void func_ovl0C_09_80046ED8(UnkStructA *, s32);
void func_ovl0C_09_80046EE0(UnkStructA *, s32);
void func_ovl0C_09_80046EF0(UnkStructA *);
UnkStructA *func_ovl0C_09_80046F00(s32, s32, s32, s32);
UnkStructA *func_ovl0C_09_80046F10(UnkStructA *);
UnkStructA *func_ovl0C_09_80046F20(s32, s32, f32, f32, f32);
void func_ovl0C_09_80046F58(UnkStructA *);
void func_ovl0C_09_80046FE8(UnkStructA *);
void func_ovl0C_09_80047020(UnkStruct_ovl0C_09_80047020 *);
s32 func_ovl0C_09_80047028(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_09_80047038(void);
void func_ovl0C_09_80047048(s32);
void *func_ovl0C_09_80047050(void);
s32 func_ovl0C_09_80047070(void);
void func_ovl0C_09_800470A0(s32, s32);
f32 func_ovl0C_09_800471D0(f32);
void func_ovl0C_09_800472A0(s32);
void func_ovl0C_09_800472A8(s32);
s32 func_ovl0C_09_800472B0(s32);
void func_ovl0C_09_80047378(s32, s32, s32);
void func_ovl0C_09_80047390(u32 (*)[3]);
void func_ovl0C_09_80047478(s32, f32, f32, f32, s32);
s32 func_ovl0C_09_80047480(s32, Vec3f *, s32);
void func_ovl0C_09_80047488(s32);
void func_ovl0C_09_800474B8(void);
void func_ovl0C_09_800474C8(f32 *);
void func_ovl0C_09_80047538(s32, s32, s32);
void func_ovl0C_09_80047598(void);
s32 func_ovl0C_09_800475B0(s32);
void func_ovl0C_09_800475D0(s32, f32, f32, f32);
void func_ovl0C_09_800475E0(s32);
void func_ovl0C_09_800475E8(s32, s8);
void func_ovl0C_09_80047728(void);

void func_ovl0C_09_80043010(void);
void func_ovl0C_09_80043020(void);
void func_ovl0C_09_80043040(void);
void func_ovl0C_09_80043068(void);
void func_ovl0C_09_800430B0(void);
void func_ovl0C_09_80043148(void);
void func_ovl0C_09_80043190(void);
void func_ovl0C_09_80043244(void);
void func_ovl0C_09_800432BC(void);
void func_ovl0C_09_80043304(void);
void func_ovl0C_09_80043390(void);
void func_ovl0C_09_800433FC(void *);
void func_ovl0C_09_80043434(void);
void func_ovl0C_09_8004346C(void);
void func_ovl0C_09_800434C0(void);
void func_ovl0C_09_80043518(f32);
void func_ovl0C_09_80043560(void);
void func_ovl0C_09_80043690(void);
void func_ovl0C_09_80043730(s32, s32, s32, f32, s32);
void func_ovl0C_09_80043758(void);
void func_ovl0C_09_800437A8(f32, f32, f32);
void func_ovl0C_09_80043854(f32, f32, f32);
void func_ovl0C_09_800438C8(void);
void func_ovl0C_09_8004392C(void);
void func_ovl0C_09_80043988(void);
void func_ovl0C_09_800439D8(UnkStruct_ovl0C_09_8004782C *);
void func_ovl0C_09_80043A5C(void);
void func_ovl0C_09_80043AA4(void);
void func_ovl0C_09_80043BF0(UnkStructA *, UnkStructA *, f32);
void func_ovl0C_09_80043C40(UnkStruct_ovl0C_09_8004784C *);
void func_ovl0C_09_80043D08(void);
void func_ovl0C_09_80043E08(void);
void func_ovl0C_09_80043E48(void);
void func_ovl0C_09_80043E80(void);
void func_ovl0C_09_80043FB4(s32);
void func_ovl0C_09_8004411C(f32, f32, f32);
void func_ovl0C_09_800441D4(void);
void func_ovl0C_09_8004455C(UnkStructA *);
void func_ovl0C_09_80044588(s32, UnkStructA *, UnkStructA *, f32);
void func_ovl0C_09_80044610(UnkStruct_ovl0C_09_8004784C *);
void func_ovl0C_09_80044A5C(UnkStruct_ovl0C_09_8004784C *, void *);
void func_ovl0C_09_80044AF4(void);
void func_ovl0C_09_80044B6C(void);
void func_ovl0C_09_80044BA4(void);
void func_ovl0C_09_80044DC4(void);
void func_ovl0C_09_80044F38(void);
void func_ovl0C_09_80044FBC(void *);
void func_ovl0C_09_80044FF4(void);
void func_ovl0C_09_80045060(void);
void func_ovl0C_09_8004574C(UnkStruct_ovl0C_09_80047890 *, UnkStructA *, UnkStructA *);
void func_ovl0C_09_800457E8(UnkStruct_ovl0C_09_80047890 *, UnkStructA *);
void func_ovl0C_09_80045934(void);
void func_ovl0C_09_80045DB0(UnkStructA *);
void func_ovl0C_09_80045E70(UnkStructA *);
void func_ovl0C_09_80045EB4(UnkStructA *, s32, s32, f32, f32);
void func_ovl0C_09_80045F8C(void);
void func_ovl0C_09_8004609C(s32, UnkStructA *);
void func_ovl0C_09_800460D0(f32, f32, f32);
void func_ovl0C_09_8004612C(void);
void func_ovl0C_09_80046144(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0C_09_80043018(void);
static void func_ovl0C_09_80043060(void);
static void func_ovl0C_09_80043130(void);
static void func_ovl0C_09_80043138(void);
static void func_ovl0C_09_80043140(void);
static void func_ovl0C_09_80043E00(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (as in ovl_0C_04). */
#define UNK_MACRO_ovl0C_09_80043068() \
    D_ovl0C_09_80047AFC = func_ovl0C_09_800466B8(); func_ovl0C_09_80046698(&D_ovl0C_09_80047AF0); func_ovl0C_09_800466C0(D_ovl0C_09_80047AFC, D_ovl0C_09_80047AE0)

/* .bss */
u8 D_ovl0C_09_80047AE0[0x10];
Vec3f D_ovl0C_09_80047AF0;
s32 D_ovl0C_09_80047AFC;
s32 D_ovl0C_09_80047B00;
s32 D_ovl0C_09_80047B04;
s32 D_ovl0C_09_80047B08;
u8 D_ovl0C_09_80047B0C[0x4]; /* unused (func_ovl0C_09_80046144) */
Vec3f D_ovl0C_09_80047B10;
UnkStructA *D_ovl0C_09_80047B1C;
s16 D_ovl0C_09_80047B20;
u8 D_ovl0C_09_80047B24[0x4]; /* unused (func_ovl0C_09_80046144) */
UnkStruct_ovl0C_09_80047B28 D_ovl0C_09_80047B28;
UnkStructA *D_ovl0C_09_80047B3C;

/* .data */
/* passed to func_ovl0C_09_80047390: three 12-byte records */
u32 D_ovl0C_09_800477D0[][3] = {
    { 0x940002, 0xE, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
/* three 12-byte records, each passed to func_ovl0C_09_80047538 */
u32 D_ovl0C_09_800477F4[][3] = {
    { 0, 0x25, 0xDE },
    { 1, 2, 0xE0 },
    { 2, 4, 0xE2 },
};
UnkStruct_ovl0C_09_80047818 D_ovl0C_09_80047818 = { NULL, 3150.0f, 4600.0f, 2000.0f };
UnkStructA *D_ovl0C_09_80047828 = NULL;
UnkStruct_ovl0C_09_8004782C D_ovl0C_09_8004782C[] = {
    { NULL, 3150.0f, 3900.0f, 1550.0f, 3900.0f, -400.0f, 3150.0f, 1550.0f },
};
UnkStruct_ovl0C_09_8004784C D_ovl0C_09_8004784C = {
    0, NULL, 0x2D, 0x17, 0.0f, 12.0f, 35.0f, 1.0f, 2, 0x435,
    900.0f, 100.0f, 1550.0f, 3150.0f, 1000.0f, 3150.0f, 1750.0f,
};
UnkStruct_ovl0C_09_80047890 D_ovl0C_09_80047890[] = {
    { 0, 0, 0, NULL, NULL, 2450.0f, 100.0f, 550.0f, 100.0f, 1600.0f, 2450.0f, 0.0f, 550.0f, 70.0f,
      0x18, 1, 5, 0x19, 2, 6, 0x80, 0, 0 },
    { 1, 0, 0, NULL, NULL, 1650.0f, 100.0f, 1550.0f, 100.0f, 1600.0f, 1650.0f, 0.0f, 1550.0f, 70.0f,
      0x10, 1, 0xF, 0x11, 2, 0x10, 0x40, 0, 0 },
    { 2, 0, 0, NULL, NULL, 2450.0f, 100.0f, 2550.0f, 100.0f, 1600.0f, 2450.0f, 0.0f, 2550.0f, 70.0f,
      0x18, 1, 0x19, 0x19, 2, 0x1A, 0, 0, 0 },
    { 3, 0, 0, NULL, NULL, 2450.0f, 1800.0f, 1050.0f, 1800.0f, 3300.0f, 2450.0f, 1700.0f, 1050.0f, 80.0f,
      0x18, 3, 0xA, 0x19, 4, 0xB, 0, 0, 0 },
    { 4, 0, 0, NULL, NULL, 2350.0f, 1800.0f, 1550.0f, 1800.0f, 3300.0f, 2350.0f, 1700.0f, 1550.0f, 80.0f,
      0x17, 3, 0xF, 0x18, 4, 0x10, 0x40, 0, 0 },
    { 5, 0, 0, NULL, NULL, 2450.0f, 1800.0f, 2050.0f, 1800.0f, 3300.0f, 2450.0f, 1700.0f, 2050.0f, 80.0f,
      0x18, 3, 0x14, 0x19, 4, 0x15, 0x80, 0, 0 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0C_09_8004617C(void) {
}

static void func_ovl0C_09_80046174(void) {
}

static void func_ovl0C_09_8004616C(void) {
}

static void func_ovl0C_09_80046164(void) {
}

static void func_ovl0C_09_8004615C(void) {
}

static void func_ovl0C_09_80046154(void) {
}

static void func_ovl0C_09_8004614C(void) {
}

void func_ovl0C_09_80046144(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl0C_09_80047B0C[0] = D_ovl0C_09_80047B24[0];
    }
}

void func_ovl0C_09_8004612C(void) {
    D_ovl0C_09_80047B04 = -1;
    D_ovl0C_09_80047B08 = -1;
}

void func_ovl0C_09_800460D0(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_09_80046D18(D_ovl0C_09_80047B10.x, D_ovl0C_09_80047B10.y, D_ovl0C_09_80047B10.z);
    func_ovl0C_09_80046D38(arg0, arg1, arg2);
    func_ovl0C_09_80047048(180);
}

void func_ovl0C_09_8004609C(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_09_800475D0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_09_80045F8C(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_09_80047050();
    func_ovl0C_09_800475D0(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_09_80046F00(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_09_80045EB4(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_09_80047070();
    }
    func_ovl0C_09_80046EF0(obj);
    func_ovl0C_09_80047038();
}

void func_ovl0C_09_80045EB4(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0C_09_800471D0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_09_800471D0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_09_80045E70(UnkStructA *arg0) {
    func_ovl0C_09_80046EE0(arg0, 0x01000000);
    func_ovl0C_09_80047028(func_ovl0C_09_80045F8C, arg0, 0, 0, 0x150);
}

void func_ovl0C_09_80045DB0(UnkStructA *arg0) {
    func_ovl0C_09_80047048(10);
    func_ovl0C_09_80046560(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_09_80047048(60);
}

/* a lift: rises while something stands on it, falls back otherwise */
void func_ovl0C_09_80045934(void) {
    UnkStruct_ovl0C_09_80047890 *rec;
    UnkStructA *obj;
    UnkStructA *player;
    s16 wait;

    rec = func_ovl0C_09_80047050();
    obj = rec->unk8;
    player = func_ovl0C_09_80046718(0);
    obj->unk68 = 0.0f;
    wait = 2;
    obj->unk70 = 1.6333334f;
    while (TRUE) {
        D_ovl0C_09_80047B3C->unk30 = 4;
        D_ovl0C_09_80047B3C->unk34 = 100.0f;
        D_ovl0C_09_80047B3C->unk38 = 100.0f;
        D_ovl0C_09_80047B3C->unk40->unk10 = rec->unk24;
        D_ovl0C_09_80047B3C->unk40->unk14 = rec->unk28;
        D_ovl0C_09_80047B3C->unk40->unk18 = rec->unk2C;
        func_ovl0C_09_80046FE8(rec->unkC);
        if (func_ovl0C_09_80046E88(D_ovl0C_09_80047B3C, 2) != 0) {
            wait = 2;
            rec->unk44 |= 1;
        } else if (wait == 0) {
            rec->unk44 &= ~1;
        } else {
            wait--;
        }
        if (func_ovl0C_09_80046E88(D_ovl0C_09_80047B3C, 0x40) != 0 && (rec->unk44 & 1)) {
            func_ovl0C_09_80046518(rec->unk34, rec->unk36, rec->unk38, rec->unk3A, rec->unk3E, 0x10);
            func_ovl0C_09_80046EE0(rec->unkC, 0x100);
            obj->unk68 = rec->unk30;
        }
        if (obj->unk40->unk14 - obj->unk6C + obj->unk68 <= rec->unk1C) {
            obj->unk6C = 0.0f;
            obj->unk68 = 0.0f;
            obj->unk40->unk14 = rec->unk1C;
            func_ovl0C_09_80046ED8(rec->unkC, 0x100);
        } else {
            obj->unk40->unk14 += obj->unk68;
            obj->unk40->unk14 -= obj->unk6C;
            if (obj->unk6C <= 99.0f) {
                obj->unk6C += obj->unk70;
            } else {
                obj->unk6C = 99.0f;
            }
        }
        if (obj->unk40->unk14 - obj->unk6C + obj->unk68 <= rec->unk1C + 100.0f &&
            obj->unk40->unk14 < player->unk40->unk14 && obj->unk68 == 0) {
            func_ovl0C_09_80046518(rec->unk34, rec->unk36, rec->unk38, rec->unk3A, rec->unk3E, 0x11);
        }
        if (rec->unk44 & 2) {
            player->unk6C = 0;
        }
        func_ovl0C_09_800457E8(rec, obj);
        if (obj->unk6C == 0 && obj->unk68 == 0) {
            func_ovl0C_09_80046518(rec->unk34, rec->unk36, rec->unk38, rec->unk3A, rec->unk3E, 0x11);
            if (rec->unk44 & 2) {
                func_ovl0C_09_80047070();
                rec->unk44 &= ~2;
                func_ovl0C_09_8004455C(player);
                func_ovl0C_09_800466C8(0);
            }
        }
        if (rec->unk20 < obj->unk40->unk14) {
            func_ovl0C_09_80046518(rec->unk34, rec->unk3C, rec->unk38, rec->unk3A, rec->unk3E, 0x11);
            func_ovl0C_09_80047070();
            if (rec->unk44 & 2) {
                func_ovl0C_09_8004574C(rec, obj, player);
            }
            func_ovl0C_09_80047048(60);
            obj->unk40->unk14 = rec->unk20;
            obj->unk6C = 0.0f;
            obj->unk68 = 0.0f;
            player->unk6C = 0.0f;
            player->unk68 = 0.0f;
            func_ovl0C_09_80046518(rec->unk34, rec->unk3C, rec->unk38, rec->unk3A, rec->unk3E, 0x10);
        }
        func_ovl0C_09_80047070();
    }
}

void func_ovl0C_09_800457E8(UnkStruct_ovl0C_09_80047890 *arg0, UnkStructA *arg1) {
    UnkStructA *player;

    if (arg1->unk68 != 0.0f && func_ovl0C_09_80046E88(arg1, 1) != 0) {
        player = func_ovl0C_09_80046718(0);
        if (arg0->unk14 + 100.0f <= player->unk40->unk14 &&
            player->unk40->unk10 < arg0->unk10 + 100.0f && arg0->unk10 - 100.0f < player->unk40->unk10 &&
            player->unk40->unk18 < arg0->unk18 + 100.0f && arg0->unk18 - 100.0f < player->unk40->unk18) {
            func_ovl0C_09_800466C8(1);
            func_ovl0C_09_80046EB8(arg1, player);
            func_ovl0C_09_80046ED8(player, 0x200000);
            player->unk4C = player->unk40->unk10 - arg0->unk10;
            player->unk50 = 100.0f;
            player->unk54 = player->unk40->unk18 - arg0->unk18;
            arg0->unk44 |= 2;
        }
    }
}

void func_ovl0C_09_8004574C(UnkStruct_ovl0C_09_80047890 *arg0, UnkStructA *arg1, UnkStructA *arg2) {
    f32 pos[3];

    arg0->unk44 &= ~2;
    pos[0] = arg2->unk40->unk10;
    pos[1] = arg2->unk40->unk14;
    pos[2] = arg2->unk40->unk18;
    func_ovl0C_09_800474C8(pos);
    func_ovl0C_09_80047598();
    func_ovl0C_09_8004455C(arg2);
    func_ovl0C_09_80047070();
    func_ovl0C_09_800466C8(0);
}

/* func_ovl0C_09_80044588's body, written out where the movers drop their
 * object: the movers' frames have no room for its parameters */
#define UNK_MACRO_ovl0C_09_80044588(flag, a, b, f)                             \
    fl = (flag);                                                               \
    if (fl & 1) {                                                          \
        func_ovl0C_09_800475B0(0x4C);                                          \
        func_ovl0C_09_80046EB8(a, b);                                          \
        func_ovl0C_09_80046ED8(b, 0x200000);                                   \
        (b)->unk4C = 0.0f;                                                     \
        (b)->unk50 = f;                                                        \
        (b)->unk54 = 0.0f;                                                     \
    } else {                                                                   \
        func_ovl0C_09_800475B0(0x4C);                                          \
        func_ovl0C_09_80046EB0(b);                                             \
        func_ovl0C_09_80046EE0(b, 0x200000);                                   \
    }

/* a mover on x and z: carries D_ovl0C_09_8004782C[rec->unk0]'s object
 * across, then drops it */
void func_ovl0C_09_80045060(void) {
    UnkStruct_ovl0C_09_8004784C *rec;
    UnkStructA *obj;
    UnkStructA *other;
    UnkStruct_ovl0C_09_8004782C *lim;
    s16 done;
    f32 dist;
    s32 fl;

    rec = func_ovl0C_09_80047050();
    obj = rec->unk4;
    obj->unk68 = rec->unk18;
    obj->unk70 = rec->unk1C;
    lim = &D_ovl0C_09_8004782C[rec->unk0];
    other = lim->unk0;
    done = FALSE;
    func_ovl0C_09_80046720(1);
    func_ovl0C_09_800475D0(0x48, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
    while (TRUE) {
        obj->unk40->unk10 += rec->unk10;
        obj->unk40->unk18 += rec->unk14;
        if (rec->unk10 != 0) {
            if (rec->unk10 > 0) {
                if (rec->unk34 <= obj->unk40->unk10) {
                    break;
                }
            } else if (obj->unk40->unk10 <= rec->unk34) {
                break;
            }
        }
        if (rec->unk14 != 0) {
            if (rec->unk14 > 0) {
                if (rec->unk38 <= obj->unk40->unk18) {
                    break;
                }
            } else if (obj->unk40->unk18 <= rec->unk38) {
                break;
            }
        }
        func_ovl0C_09_80047070();
    }
    while (TRUE) {
        if (rec->unk2C <= obj->unk40->unk14 + obj->unk6C - obj->unk68) {
            break;
        }
        obj->unk40->unk14 -= obj->unk68;
        obj->unk40->unk14 += obj->unk6C;
        if (obj->unk6C <= 99.0f) {
            obj->unk6C += obj->unk70;
        } else {
            obj->unk6C = 99.0f;
        }
        obj->unk40->unk10 += rec->unk10;
        obj->unk40->unk18 += rec->unk14;
        if (done == FALSE) {
            dist = lim->unk14;
            if (rec->unk10 != 0) {
                if (rec->unk10 > 0) {
                    if (lim->unk18 < obj->unk40->unk10) {
                        done = TRUE;
                        UNK_MACRO_ovl0C_09_80044588(rec->unk20, obj, other, dist);
                    }
                } else if (obj->unk40->unk10 < lim->unk18) {
                    done = TRUE;
                    UNK_MACRO_ovl0C_09_80044588(rec->unk20, obj, other, dist);
                }
            }
            if (rec->unk14 != 0) {
                if (rec->unk14 > 0) {
                    if (lim->unk1C < obj->unk40->unk18) {
                        done = TRUE;
                        UNK_MACRO_ovl0C_09_80044588(rec->unk20, obj, other, dist);
                    }
                } else if (obj->unk40->unk18 < lim->unk1C) {
                    done = TRUE;
                    UNK_MACRO_ovl0C_09_80044588(rec->unk20, obj, other, dist);
                }
            }
        }
        func_ovl0C_09_80047070();
    }
    done = FALSE;
    while (TRUE) {
        if (rec->unk10 != 0) {
            if (rec->unk10 > 0) {
                if (rec->unk3C <= obj->unk40->unk10) {
                    done = TRUE;
                }
            } else if (obj->unk40->unk10 <= rec->unk3C) {
                done = TRUE;
            }
        }
        if (rec->unk14 != 0) {
            if (rec->unk14 > 0) {
                if (rec->unk40 <= obj->unk40->unk18) {
                    done = TRUE;
                }
            } else if (obj->unk40->unk18 <= rec->unk40) {
                done = TRUE;
            }
        }
        if (done == TRUE) {
            func_ovl0C_09_800466C8(0);
            func_ovl0C_09_800472A0(rec->unk24);
            if (func_ovl0C_09_800472B0(0x431) == 0) {
                func_ovl0C_09_800465D0(rec->unk8, rec->unkC, 0);
            } else {
                func_ovl0C_09_80047728();
            }
            func_ovl0C_09_80047038();
        }
        obj->unk40->unk10 += rec->unk10;
        obj->unk40->unk18 += rec->unk14;
        func_ovl0C_09_80047070();
    }
}

void func_ovl0C_09_80044FF4(void) {
    UnkStructA *obj;

    obj = *(UnkStructA **) func_ovl0C_09_80047050();
    obj->unk68 = 0.0f;
    obj->unk70 = 1.6333334f;
    while (TRUE) {
        func_ovl0C_09_80046F58(obj);
        func_ovl0C_09_80047070();
    }
}

void func_ovl0C_09_80044FBC(void *arg0) {
    func_ovl0C_09_80047028(func_ovl0C_09_80045060, arg0, 0, 0, 0x110);
}

void func_ovl0C_09_80044F38(void) {
    UnkStructA *obj;
    s32 alpha;
    s32 step;

    func_ovl0C_09_800466C8(1);
    func_ovl0C_09_80047048(10);
    obj = func_ovl0C_09_80046718(func_ovl0C_09_800466B8());
    func_ovl0C_09_800475B0(0x44);
    func_ovl0C_09_80046ED8(obj, 0x80000);
    step = 0x11;
    for (alpha = 0xFF; alpha > 0; alpha -= step) {
        obj->unk40->unk36 = alpha;
        func_ovl0C_09_80047070();
    }
    obj->unk40->unk36 = 0;
    func_ovl0C_09_80047038();
}

void func_ovl0C_09_80044DC4(void) {
    f32 angle;

    D_ovl0C_09_8004784C.unk4->unk68 = 35.0f;
    D_ovl0C_09_8004784C.unk4->unk70 = 1.6333334f;
    while (TRUE) {
        func_ovl0C_09_80046F58(D_ovl0C_09_8004784C.unk4);
        D_ovl0C_09_8004784C.unk4->unk40->unk18 -= 10.0f;
        if (D_ovl0C_09_8004784C.unk4->unk40->unk18 < 100.0f) {
            break;
        }
        angle = D_ovl0C_09_8004784C.unk4->unk40->unk20 + 20.0f;
        D_ovl0C_09_8004784C.unk4->unk40->unk20 =
            angle >= 360.0f ? angle - 360.0f : angle < 0.0f ? angle + 360.0f : angle;
        func_ovl0C_09_80047070();
    }
    func_ovl0C_09_80046EE0(D_ovl0C_09_8004784C.unk4, 0x01000000);
    func_ovl0C_09_80047038();
}

void func_ovl0C_09_80044BA4(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 hit;
    UnkStruct_ovl0C_09_80047020 snd;

    obj = D_ovl0C_09_80047818.unk0;
    p = obj->unk40;
    func_ovl0C_09_80047048(120);
    D_ovl0C_09_80047818.unk0->unk40->unk18 = 2500.0f;
    func_ovl0C_09_80046ED8(D_ovl0C_09_80047818.unk0, 0x01000000);
    snd.unk0 = p;
    snd.unk4 = 0x213;
    snd.unk8 = 60;
    func_ovl0C_09_80047020(&snd);
    p->unk48->unk4->unk4 = func_ovl0C_09_80046C18(p, 0) - 0.01f;
    hit = FALSE; while (obj->unk40->unk18 > 800.0f) {
        if (obj->unk40->unk18 < 1500.0f && hit == FALSE) {
            func_ovl0C_09_800475B0(0x168);
            hit = TRUE;
            func_ovl0C_09_80047478(20, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
            func_ovl0C_09_800475B0(0x4C);
            func_ovl0C_09_8004455C(D_ovl0C_09_8004782C[0].unk0);
            func_ovl0C_09_80044B6C();
        }
        func_ovl0C_09_80047070();
        obj->unk40->unk18 -= 20.0f;
    }
    func_ovl0C_09_80046EE0(obj, 0x01000000);
    func_ovl0C_09_80047038();
}

void func_ovl0C_09_80044B6C(void) {
    func_ovl0C_09_80047028(func_ovl0C_09_80044DC4, NULL, 0, 0, 0x110);
}

void func_ovl0C_09_80044AF4(void) {
    s16 *count;

    count = func_ovl0C_09_80047050();
    while (*count != 0) {
        func_ovl0C_09_80047070();
        (*count)--;
    }
    func_ovl0C_09_800465D0(D_ovl0C_09_8004784C.unk8, D_ovl0C_09_8004784C.unkC, 0);
    func_ovl0C_09_80047038();
}

void func_ovl0C_09_80044A5C(UnkStruct_ovl0C_09_8004784C *arg0, void *arg1) {
    func_ovl0C_09_80046648(1);
    func_ovl0C_09_80046640(0);
    func_ovl0C_09_800466C8(1);
    func_ovl0C_09_800433FC(arg1);
    func_ovl0C_09_80044610(arg0);
    func_ovl0C_09_800466C8(0);
    D_ovl0C_09_80047B20 = 60;
    func_ovl0C_09_80047028(func_ovl0C_09_80044AF4, &D_ovl0C_09_80047B20, 0, 0, 0x110);
}

/* a mover on z: carries D_ovl0C_09_8004782C[rec->unk0]'s object across */
void func_ovl0C_09_80044610(UnkStruct_ovl0C_09_8004784C *rec) {
    UnkStructA *obj;
    UnkStructA *other;
    UnkStruct_ovl0C_09_8004782C *lim;
    s32 done;
    f32 dist;
    s32 fl;

    obj = rec->unk4;
    obj->unk68 = rec->unk18;
    obj->unk70 = rec->unk1C;
    lim = &D_ovl0C_09_8004782C[rec->unk0];
    other = lim->unk0;
    done = FALSE;
    func_ovl0C_09_800466C8(1);
    while (TRUE) {
        obj->unk40->unk18 += rec->unk14;
        if (rec->unk14 != 0) {
            if (rec->unk14 > 0) {
                if (rec->unk38 <= obj->unk40->unk18) {
                    break;
                }
            } else if (obj->unk40->unk18 <= rec->unk38) {
                break;
            }
        }
        func_ovl0C_09_80047070();
    }
    while (TRUE) {
        if (rec->unk14 > 0) {
            if (rec->unk40 <= obj->unk40->unk18) {
                break;
            }
        } else if (obj->unk40->unk18 <= rec->unk40) {
            break;
        }
        obj->unk40->unk14 -= obj->unk68;
        obj->unk40->unk14 += obj->unk6C;
        if (obj->unk6C <= 99.0f) {
            obj->unk6C += obj->unk70;
        } else {
            obj->unk6C = 99.0f;
        }
        obj->unk40->unk18 += rec->unk14;
        if (done == FALSE && (dist = lim->unk14, rec->unk14 != 0)) {
            if (rec->unk14 > 0) {
                if (lim->unk1C < obj->unk40->unk18) {
                    done = TRUE;
                    UNK_MACRO_ovl0C_09_80044588(rec->unk20, obj, other, dist);
                }
            } else if (obj->unk40->unk18 < lim->unk1C) {
                done = TRUE;
                UNK_MACRO_ovl0C_09_80044588(rec->unk20, obj, other, dist);
            }
        }
        func_ovl0C_09_80047070();
    }
    func_ovl0C_09_80047048(30);
    obj->unk68 = 0;
    obj->unk70 = 1.6333334f;
    while (TRUE) {
        func_ovl0C_09_80046F58(obj);
        if (obj->unk6C == 0 && obj->unk68 == 0) {
            func_ovl0C_09_80047478(20, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
            func_ovl0C_09_80046EE0(obj, 0x01000000);
            func_ovl0C_09_80047048(60);
            func_ovl0C_09_800475B0(0x2C);
            func_ovl0C_09_80043D08();
            func_ovl0C_09_800466C8(0);
            func_ovl0C_09_800472A0(rec->unk24);
            return;
        }
        func_ovl0C_09_80047070();
    }
}

void func_ovl0C_09_80044588(s32 arg0, UnkStructA *arg1, UnkStructA *arg2, f32 arg3) {
    if (arg0 & 1) {
        func_ovl0C_09_800475B0(0x4C);
        func_ovl0C_09_80043BF0(arg1, arg2, arg3);
    } else {
        func_ovl0C_09_800475B0(0x4C);
        func_ovl0C_09_8004455C(arg2);
    }
}

void func_ovl0C_09_8004455C(UnkStructA *arg0) {
    func_ovl0C_09_80046EB0(arg0);
    func_ovl0C_09_80046EE0(arg0, 0x200000);
}

/* the opening: the object at D_ovl0C_09_8004784C rises and carries the
 * camera along */
void func_ovl0C_09_800441D4(void) {
    UnkStructA *obj;
    s32 snd;
    s32 vol;
    f32 dist;
    f32 y;

    func_ovl0C_09_80046648(1);
    func_ovl0C_09_800470A0(0x110, 0x110);
    func_ovl0C_09_800466C8(1);
    obj = D_ovl0C_09_8004784C.unk4;
    func_ovl0C_09_80043BF0(obj, D_ovl0C_09_8004782C[0].unk0, -400.0f);
    snd = func_ovl0C_09_800475B0(0x4E);
    obj->unk40->unk20 = 90.0f;
    while (obj->unk40->unk14 < 3900.0f) {
        obj->unk40->unk14 += 10.0f;
        obj->unk40->unk10 += 4.0f;
        func_ovl0C_09_80046D18(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
        func_ovl0C_09_80047070();
    }
    obj->unk40->unk14 = 3900.0f;
    func_ovl0C_09_8004411C(3150.0f, 4630.0f, obj->unk40->unk18 + 150.0f);
    dist = 62.0f;
    while (obj->unk40->unk10 < 3150.0f) {
        obj->unk40->unk14 += 5.0f;
        obj->unk40->unk10 += 5.0f;
        func_ovl0C_09_80046D18(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
        func_ovl0C_09_80046D38(90.0f, dist, 1800.0f);
        func_ovl0C_09_80047070();
        dist -= 0.2f;
    }
    y = obj->unk40->unk14;
    obj->unk40->unk10 = 3150.0f;
    for (vol = 0x7F; vol != -1; vol -= 2) {
        func_ovl0C_09_800475E8(snd, vol);
        func_ovl0C_09_80047070();
    }
    func_ovl0C_09_800475E8(snd, 0);
    func_ovl0C_09_800475E0(snd);
    while (y > 4300.0f) {
        y -= 5.0f;
        func_ovl0C_09_80046D18(D_ovl0C_09_8004782C[0].unk0->unk40->unk10, y,
                               D_ovl0C_09_8004782C[0].unk0->unk40->unk18);
        func_ovl0C_09_80047070();
    }
    func_ovl0C_09_80047048(30);
    func_ovl0C_09_800475B0(0x2C);
    func_ovl0C_09_80043D08();
    func_ovl0C_09_800472A0(D_ovl0C_09_8004784C.unk24);
    func_ovl0C_09_80047048(30);
    func_ovl0C_09_80047048(120);
    func_ovl0C_09_800465D0(D_ovl0C_09_8004784C.unk8, D_ovl0C_09_8004784C.unkC, 0);
    while (TRUE) {
        func_ovl0C_09_80047070();
    }
}

void func_ovl0C_09_8004411C(f32 arg0, f32 arg1, f32 arg2) {
    D_ovl0C_09_80047818.unk0->unk40->unk10 = D_ovl0C_09_80047828->unk40->unk10 = arg0;
    D_ovl0C_09_80047818.unk0->unk40->unk14 = D_ovl0C_09_80047828->unk40->unk14 = arg1;
    D_ovl0C_09_80047818.unk0->unk40->unk18 = D_ovl0C_09_80047828->unk40->unk18 = arg2;
    func_ovl0C_09_80047028(func_ovl0C_09_80044BA4, &D_ovl0C_09_80047818, 0, 0, 0x110);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0C_09_80043FB4(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0C_09_80043E80();
            break;
        case 17:
            func_ovl0C_09_80043988();
            break;
        case 18:
            func_ovl0C_09_8004392C();
            break;
        case 19:
            func_ovl0C_09_800438C8();
            break;
        case 20:
            func_ovl0C_09_80043758();
            break;
        case 4:
            func_ovl0C_09_80043690();
            break;
        case 5:
            func_ovl0C_09_80043390();
            break;
        case 0x50:
            func_ovl0C_09_80043190();
            break;
        case 3:
            func_ovl0C_09_800430B0();
            break;
        case 12:
            func_ovl0C_09_80046720(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0C_09_80043E08(void) {
    func_ovl0C_09_800472A8(0x400);
    func_ovl0C_09_800472A8(0x401);
    func_ovl0C_09_800472A8(0x402);
    func_ovl0C_09_800472A8(0x403);
    func_ovl0C_09_800472A8(0x404);
}

void func_ovl0C_09_80043E48(void) {
    func_ovl0C_09_80043E08();
    func_ovl0C_09_800465C0(func_ovl0C_09_80045E70);
    func_ovl0C_09_80046610(func_ovl0C_09_80045DB0);
}

void func_ovl0C_09_80043E80(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0C_09_80043E48();
    func_ovl0C_09_80047390(D_ovl0C_09_800477D0);
    func_ovl0C_09_800464D8(0x24A);
    p = D_ovl0C_09_800477F4;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl0C_09_80047538((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0C_09_800464F0(0x254);
    func_ovl0C_09_80046688();
    func_ovl0C_09_80043E00();
    if (func_ovl0C_09_800472B0(0x435) != 0) {
        func_ovl0C_09_80043D08();
    }
    if (func_ovl0C_09_800472B0(0x436) != 0 && func_ovl0C_09_800472B0(0x435) == 0) {
        func_ovl0C_09_800439D8(D_ovl0C_09_8004782C);
        func_ovl0C_09_80043C40(&D_ovl0C_09_8004784C);
    }
    func_ovl0C_09_80043AA4();
    if (func_ovl0C_09_800472B0(0x435) != 0) {
        func_ovl0C_09_800439D8(D_ovl0C_09_8004782C);
        D_ovl0C_09_8004782C[0].unk0->unk40->unk8 = 0x61;
    }
    func_ovl0C_09_80047378(0x37, 0x4D, 0xFF);
}

static void func_ovl0C_09_80043E00(void) {
}

/* Inlined into func_ovl0C_09_80043D08 only, as ovl_12_03's 8004316C. */
#define UNK_MACRO_ovl0C_09_80043D00()                                          \
    D_ovl0C_09_80047B10.x = x * 100.0f;                                        \
    D_ovl0C_09_80047B10.y = 0.0f;                                              \
    for (i = 0; i < count; i++) {                                              \
        D_ovl0C_09_80047B10.y += func_ovl0C_09_80046540(i) * 100.0f;           \
    }                                                                          \
    D_ovl0C_09_80047B10.y += 100.0f;                                           \
    D_ovl0C_09_80047B10.z = z * 100.0f;                                        \
    D_ovl0C_09_80047B00 = func_ovl0C_09_80047480(0x26, &D_ovl0C_09_80047B10, 0)

static void func_ovl0C_09_80043D00(f32 x, s32 z, s32 count) {
    s32 i;

    UNK_MACRO_ovl0C_09_80043D00();
    if (!i && !i) {
    }
}

void func_ovl0C_09_80043D08(void) {
    func_ovl0C_09_80043D00(33.0f, 15, 5);
    func_ovl0C_09_80046518(0x1F, 5, 0xF, 0x20, 0x10, 0x12);
}

void func_ovl0C_09_80043C40(UnkStruct_ovl0C_09_8004784C *arg0) {
    UnkStructA *obj;
    UnkStructA *other;
    UnkStruct_ovl0C_09_8004782C *lim;

    obj = func_ovl0C_09_80046F20(0x2B2, 0xD0, arg0->unk28, arg0->unk2C, arg0->unk30);
    func_ovl0C_09_80046F10(obj);
    func_ovl0C_09_80046ED8(obj, 0x0D000000);
    lim = &D_ovl0C_09_8004782C[arg0->unk0];
    arg0->unk4 = obj;
    other = lim->unk0;
    if (arg0->unk20 & 2) {
        func_ovl0C_09_80043BF0(obj, other, lim->unk14);
    }
}

void func_ovl0C_09_80043BF0(UnkStructA *arg0, UnkStructA *arg1, f32 arg2) {
    func_ovl0C_09_80046EB8(arg0, arg1);
    func_ovl0C_09_80046ED8(arg1, 0x200000);
    arg1->unk4C = 0.0f;
    arg1->unk50 = arg2;
    arg1->unk54 = 0.0f;
}

void func_ovl0C_09_80043AA4(void) {
    UnkStruct_ovl0C_09_80047890 *p;
    UnkStructA *obj;
    s16 i;

    func_ovl0C_09_80043A5C();
    for (i = 0; i < 6; i++) {
        p = &D_ovl0C_09_80047890[i];
        obj = func_ovl0C_09_80046F20(0x2AC, 0xD0, p->unk10, p->unk1C, p->unk18);
        func_ovl0C_09_80046ED8(obj, 0x01000000);
        p->unk8 = obj;
        p->unk44 = 0;
        obj->unk30 = 4;
        obj->unk34 = 100.0f;
        obj->unk38 = 100.0f;
        func_ovl0C_09_80046518(p->unk34, p->unk36, p->unk38, p->unk3A, p->unk3E, 0x11);
        D_ovl0C_09_80047890[i].unkC = func_ovl0C_09_80046F00(-1, 0, 0x50, 0);
        D_ovl0C_09_80047890[i].unkC->unk40->unk10 = D_ovl0C_09_80047890[i].unk10;
        D_ovl0C_09_80047890[i].unkC->unk40->unk14 = D_ovl0C_09_80047890[i].unk1C - 100.0f;
        D_ovl0C_09_80047890[i].unkC->unk40->unk18 = D_ovl0C_09_80047890[i].unk18;
    }
}

void func_ovl0C_09_80043A5C(void) {
    if (func_ovl0C_09_800472B0(0x400) == 0) {
        D_ovl0C_09_80047B3C = func_ovl0C_09_80046F00(-1, 0, 0x20, 0);
        func_ovl0C_09_800472A0(0x400);
    }
}

void func_ovl0C_09_800439D8(UnkStruct_ovl0C_09_8004782C *arg0) {
    UnkStructA *obj;
    UnkStructA *shadow;

    obj = func_ovl0C_09_80046F20(0x2A6, 0xD0, arg0->unk4, arg0->unk10, arg0->unkC);
    shadow = func_ovl0C_09_80046F10(obj);
    shadow->unk54 = 2.0f;
    shadow->unk4C = 2.0f;
    shadow->unk40->unk36 = 0x19;
    func_ovl0C_09_80046ED8(obj, 0x0D080000);
    arg0->unk0 = obj;
    arg0->unk8 = arg0->unk10;
}

void func_ovl0C_09_80043988(void) {
    func_ovl0C_09_80046690(2, 0, 0xF);
    func_ovl0C_09_80043730(1, 0x40, 0x40, 0.0f, 2);
}

void func_ovl0C_09_8004392C(void) {
    func_ovl0C_09_80046690(2, 0, 0xF);
    func_ovl0C_09_80043730(2, 0x40, 0x40, 0.0f, 2);
    func_ovl0C_09_80046660(0x30, 0x14);
}

void func_ovl0C_09_800438C8(void) {
    func_ovl0C_09_80043730(3, 0x40, 0x40, 0.0f, 2);
    func_ovl0C_09_80043854(0.0f, 0.0f, 0.0f);
    func_ovl0C_09_800437A8(0.0f, 0.0f, 0.0f);
}

void func_ovl0C_09_80043854(f32 arg0, f32 arg1, f32 arg2) {
    UnkStructA *obj;

    obj = func_ovl0C_09_80046F20(0x328, 0xC0, arg0, arg1, arg2);
    D_ovl0C_09_80047818.unk0 = obj;
    obj->unk40->unk20 = 180.0f;
    obj->unk40->unkC |= 0x40;
    func_ovl0C_09_80046C00(obj->unk40, 0x16, 0);
}

void func_ovl0C_09_800437A8(f32 arg0, f32 arg1, f32 arg2) {
    UnkStructA *obj;

    D_ovl0C_09_80047828 = obj = func_ovl0C_09_80046F20(0x1CB, 0xD0, arg0, arg1 + 10.0f, arg2);
    func_ovl0C_09_80046ED8(obj, 0x80000);
    obj->unk40->unk1C = -90.0f;
    obj->unk40->unk30 = 0.5f;
    obj->unk40->unk28 = obj->unk40->unk30;
    obj->unk40->unk24 = 90.0f;
    obj->unk40->unk36 = 0;
}

void func_ovl0C_09_80043758(void) {
    func_ovl0C_09_80046690(2, 0, 0xF);
    func_ovl0C_09_80043730(4, 0x40, 0x40, 0.0f, 2);
}

void func_ovl0C_09_80043730(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0C_09_80047B28.unk0 = arg0;
    D_ovl0C_09_80047B28.unk4 = arg1;
    D_ovl0C_09_80047B28.unk8 = arg2;
    D_ovl0C_09_80047B28.unkC = arg3;
    D_ovl0C_09_80047B28.unk10 = arg4;
}

void func_ovl0C_09_80043690(void) {
    func_ovl0C_09_80043560();
    if (D_ovl0C_09_80047B28.unk0 == 2) {
        func_ovl0C_09_800434C0();
    }
    if (D_ovl0C_09_80047B28.unk0 == 3) {
        func_ovl0C_09_8004346C();
        func_ovl0C_09_80043434();
        func_ovl0C_09_800433FC(D_ovl0C_09_8004782C);
    }
}

void func_ovl0C_09_80043560(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_09_800466E8();
    switch (D_ovl0C_09_80047B28.unk8) {
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
        func_ovl0C_09_80046D38(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_09_80047B28.unkC;
        func_ovl0C_09_80046D40(&sp1C, NULL, NULL);
        func_ovl0C_09_80046D38(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_09_800466D0(D_ovl0C_09_80047B28.unk4);
    func_ovl0C_09_80046DD0(45.0f, 45.1f);
}

void func_ovl0C_09_80043518(f32 arg0) {
    f32 sp1C;

    func_ovl0C_09_80046D40(&sp1C, NULL, NULL);
    func_ovl0C_09_80046D38(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0C_09_800434C0(void) {
    D_ovl0C_09_80047B1C = func_ovl0C_09_80046718(func_ovl0C_09_800466B8());
    func_ovl0C_09_80046ED8(D_ovl0C_09_80047B1C, 0x80000);
    D_ovl0C_09_80047B1C->unk40->unk36 = 0;
}

void func_ovl0C_09_8004346C(void) {
    func_ovl0C_09_80046D80(0x7F);
    func_ovl0C_09_80046D18(900.0f, 1000.0f, 1550.0f);
    func_ovl0C_09_80046D38(90.0f, 62.0f, 1800.0f);
}

void func_ovl0C_09_80043434(void) {
    func_ovl0C_09_80047028(func_ovl0C_09_800441D4, NULL, 0, 0, 0x110);
}

void func_ovl0C_09_800433FC(void *arg0) {
    func_ovl0C_09_80047028(func_ovl0C_09_80044FF4, arg0, 0, 0, 0x110);
}

void func_ovl0C_09_80043390(void) {
    if (D_ovl0C_09_80047B28.unk0 == 2) {
        func_ovl0C_09_80043304();
    }
    func_ovl0C_09_800432BC();
    func_ovl0C_09_80043244();
}

void func_ovl0C_09_80043304(void) {
    s32 alpha;
    s32 step;

    func_ovl0C_09_800466C8(1);
    func_ovl0C_09_800475B0(0x45);
    step = 0x11;
    for (alpha = 0; alpha < 0xFF; alpha += step) {
        D_ovl0C_09_80047B1C->unk40->unk36 = alpha;
        func_ovl0C_09_80047070();
    }
    D_ovl0C_09_80047B1C->unk40->unk36 = 0xFF;
    func_ovl0C_09_80046EE0(D_ovl0C_09_80047B1C, 0x80000);
    func_ovl0C_09_800466C8(0);
}

void func_ovl0C_09_800432BC(void) {
    func_ovl0C_09_800466D8(D_ovl0C_09_80047B28.unk4, 3, 4.0f, D_ovl0C_09_80047B28.unk10, 0, 1, 1);
}

void func_ovl0C_09_80043244(void) {
    UnkStruct_ovl0C_09_80047890 *p;
    s16 i;

    for (i = 0, p = D_ovl0C_09_80047890; i < 6; i++, p++) {
        p->unk4 = func_ovl0C_09_80047028(func_ovl0C_09_80045934, p, 0, 0, 0x110);
    }
}

void func_ovl0C_09_80043190(void) {
    if (func_ovl0C_09_800466A0(1, 0xF, 2, 0x10) != 0) {
        func_ovl0C_09_80047028(func_ovl0C_09_80044F38, NULL, 0, 0, 0x130);
        func_ovl0C_09_80046678(60);
        func_ovl0C_09_800465D0(0x2D, 0x14, 4);
    }
    if (func_ovl0C_09_800466A0(0x1F, 0xF, 0x20, 0x10) != 0) {
        func_ovl0C_09_80043148();
    }
}

void func_ovl0C_09_80043148(void) {
    func_ovl0C_09_80043130();
    func_ovl0C_09_80043138();
    func_ovl0C_09_80043140();
    func_ovl0C_09_80046788();
    func_ovl0C_09_800474B8();
    func_ovl0C_09_80047598();
    func_ovl0C_09_80047488(D_ovl0C_09_80047B00);
    func_ovl0C_09_800465F8();
}

static void func_ovl0C_09_80043140(void) {
}

static void func_ovl0C_09_80043138(void) {
}

static void func_ovl0C_09_80043130(void) {
}

void func_ovl0C_09_800430B0(void) {
    UNK_MACRO_ovl0C_09_80043068();
    if (func_ovl0C_09_800472B0(0x404) == 0 && D_ovl0C_09_80047B28.unk0 == 3) {
        func_ovl0C_09_80046640(0);
        func_ovl0C_09_800466C8(1);
    }
    func_ovl0C_09_800472A0(0x404);
}

void func_ovl0C_09_80043068(void) {
    func_ovl0C_09_80043060();
    D_ovl0C_09_80047AFC = func_ovl0C_09_800466B8();
    func_ovl0C_09_80046698(&D_ovl0C_09_80047AF0);
    func_ovl0C_09_800466C0(D_ovl0C_09_80047AFC, D_ovl0C_09_80047AE0);
}

static void func_ovl0C_09_80043060(void) {
}

void func_ovl0C_09_80043040(void) {
    func_ovl0C_09_80046720(1);
}

void func_ovl0C_09_80043020(void) {
    func_ovl0C_09_80043018();
    func_ovl0C_09_80046720(1);
}

static void func_ovl0C_09_80043018(void) {
}

void func_ovl0C_09_80043010(void) {
}
