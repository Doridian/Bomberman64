/*
 * NON_MATCHING: ovl_0E_13's game object, complete: every function and its data
 * (.data 0x530, .rodata 0x80, .bss 0x60 as the original); .text 0x20
 * short of 0x2150. Much of it is ovl_0E_09's code.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 177, eu 177, jp 177
 *
 * What still differs in us (words):
 * - func_ovl0E_13_80043110 (48), 80043444 (68), 8004439C (52): the D80
 *   position set-up (UNK_MACRO_ovl0E_13_80043110): the original keeps &D80
 *   in s1 for every access to .y; ours stores .y through `lui at` in the
 *   loop and after it, 3 instructions more per site.
 * - func_ovl0E_13_80043940 (2): the epilogue restores s1 before s0 (the
 *   original s0 first), as in ovl_0C_08's 80043654.
 * - func_ovl0E_13_80044780 (7): only the alignment nops at the end, from
 *   the size difference above.
 */
#include "common.h"

/*
 * ovl_0E_13's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_13_80046D90;

/* the nine movers' records: each is passed to its task */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ UnkStructA *unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} UnkStruct_ovl0E_13_80046A3C;

/* a mover's path: fifteen points */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
} UnkStruct_ovl0E_13_80046B5C;

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
} UnkStruct_ovl0E_13_80046800;

/* a switch: its flag and where it is */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl0E_13_800469F8;

/* UnkStructA_40 with the pointer at 0x48 */
typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} UnkStruct_ovl0E_13_48_4;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_ovl0E_13_48_4 *unk4;
} UnkStruct_ovl0E_13_48;

typedef struct {
    /* 0x00 */ u8 unk0[0x48];
    /* 0x48 */ UnkStruct_ovl0E_13_48 *unk48;
} UnkStruct_ovl0E_13_40;

void func_ovl0E_13_800454A8(s32);
void func_ovl0E_13_800454C0(s32);
f32 func_ovl0E_13_800454D0(void);
void func_ovl0E_13_800454E8(s32, s32, s32, s32, s32, s32);
s32 func_ovl0E_13_80045510(s32);
void func_ovl0E_13_80045530(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_13_80045590(void (*)(UnkStructA *));
void func_ovl0E_13_800455A0(s32, s32, s32);
void func_ovl0E_13_800455C8(void);
void func_ovl0E_13_800455E0(void (*)(UnkStructA *));
void func_ovl0E_13_80045610(s32);
void func_ovl0E_13_80045618(s32);
void func_ovl0E_13_80045658(void);
void func_ovl0E_13_80045660(s32, s32, s32);
void func_ovl0E_13_80045668(void *);
s32 func_ovl0E_13_80045670(s32, s32, s32, s32);
s32 func_ovl0E_13_80045688(void);
void func_ovl0E_13_80045690(s32, void *);
void func_ovl0E_13_800456A0(s32);
void func_ovl0E_13_800456A8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_13_800456B8(void);
void func_ovl0E_13_800456F0(s32);
f32 func_ovl0E_13_80045BE8(UnkStructA_40 *, s32);
s32 func_ovl0E_13_80045BF0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_13_80045BF8(s32);
void func_ovl0E_13_80045CE8(f32, f32, f32);
void func_ovl0E_13_80045D08(f32, f32, f32);
void func_ovl0E_13_80045D10(f32 *, f32 *, f32 *);
void func_ovl0E_13_80045D48(s32);
void func_ovl0E_13_80045D50(s32);
void func_ovl0E_13_80045DD8(void *);
void func_ovl0E_13_80045E08(void);
void func_ovl0E_13_80045E10(void);
f32 func_ovl0E_13_80045E50(f32 *, void *);
s32 func_ovl0E_13_80045E58(UnkStructA *, s32);
void func_ovl0E_13_80045EA8(UnkStructA *, s32);
void func_ovl0E_13_80045EB0(UnkStructA *, s32);
void func_ovl0E_13_80045EC0(UnkStructA *);
UnkStructA *func_ovl0E_13_80045EF0(s32, s32, f32, f32, f32);
void func_ovl0E_13_80045F28(UnkStructA *);
void func_ovl0E_13_80045FB8(UnkStructA *);
s32 func_ovl0E_13_80045FF8(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_13_80046000(s32);
void func_ovl0E_13_80046008(void);
void func_ovl0E_13_80046018(s32);
void *func_ovl0E_13_80046020(void);
void func_ovl0E_13_80046040(void);
void func_ovl0E_13_80046270(s32);
void func_ovl0E_13_80046278(s32);
s32 func_ovl0E_13_80046280(s32);
void func_ovl0E_13_80046338(s32, s32, s32, s32, s32);
void func_ovl0E_13_80046348(s32, s32, s32);
void func_ovl0E_13_80046360(u32 (*)[3]);
void func_ovl0E_13_80046448(s32, f32, f32, f32, s32);
s32 func_ovl0E_13_80046450(s32, f32 *, s32);
void func_ovl0E_13_80046458(s32);
void func_ovl0E_13_80046508(s32, s32, s32);
void func_ovl0E_13_80046560(f32 *);
void func_ovl0E_13_80046580(s32);
void func_ovl0E_13_800465A0(s32, f32, f32, f32);
void func_ovl0E_13_800465A8(s32, f32 *);

void func_ovl0E_13_80043010(void);
void func_ovl0E_13_80043018(void);
void func_ovl0E_13_800430A8(void);
void func_ovl0E_13_800430C8(void);
void func_ovl0E_13_800430E8(void);
void func_ovl0E_13_80043110(void);
void func_ovl0E_13_800431E4(void);
void func_ovl0E_13_80043244(void);
void func_ovl0E_13_80043444(void);
s32 func_ovl0E_13_80043754(void);
void func_ovl0E_13_80043940(s16);
void func_ovl0E_13_80043A30(void);
void func_ovl0E_13_80043BD8(void);
void func_ovl0E_13_80043BE0(void);
void func_ovl0E_13_80043C28(void);
void func_ovl0E_13_80043C90(void);
void func_ovl0E_13_80043CD4(void);
void func_ovl0E_13_80043D78(void);
void func_ovl0E_13_80043DF0(void);
void func_ovl0E_13_80043E2C(void);
void func_ovl0E_13_80043E54(void);
void func_ovl0E_13_80043EA8(f32);
void func_ovl0E_13_80043EF0(void);
void func_ovl0E_13_80044008(void);
void func_ovl0E_13_80044048(s32, s32, s32, f32, s32);
void func_ovl0E_13_80044070(void);
void func_ovl0E_13_800440C0(void);
void func_ovl0E_13_80044108(void);
void func_ovl0E_13_80044158(void);
void func_ovl0E_13_8004424C(void);
void func_ovl0E_13_80044294(void);
void func_ovl0E_13_8004431C(void);
void func_ovl0E_13_80044324(void);
void func_ovl0E_13_80044364(void);
void func_ovl0E_13_8004439C(void);
void func_ovl0E_13_80044590(s32);
void func_ovl0E_13_800446F0(void);
void func_ovl0E_13_80044780(void);
void func_ovl0E_13_80044848(UnkStruct_ovl0E_13_80046A3C *, UnkStructA *);
void func_ovl0E_13_80044894(UnkStruct_ovl0E_13_80046A3C *);
void func_ovl0E_13_800449CC(void);
void func_ovl0E_13_80044F30(UnkStructA *);
void func_ovl0E_13_80044FF4(UnkStructA *);
void func_ovl0E_13_8004508C(s32, UnkStructA *);
void func_ovl0E_13_800450C0(f32, f32, f32);
void func_ovl0E_13_8004511C(void);
void func_ovl0E_13_80045134(void);

static void func_ovl0E_13_800437B8(UnkStruct_ovl0E_13_80046800 *);
static void func_ovl0E_13_800437C0(UnkStruct_ovl0E_13_80046800 *);
static void func_ovl0E_13_80043CCC(void);
static void func_ovl0E_13_80043C78(void);
static void func_ovl0E_13_80043C80(void);
static void func_ovl0E_13_80043C88(void);
static void func_ovl0E_13_80043108(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_13_80043BE0() \
    D_ovl0E_13_80046D6C = func_ovl0E_13_80045688(); func_ovl0E_13_80045668(&D_ovl0E_13_80046D60); func_ovl0E_13_80045690(D_ovl0E_13_80046D6C, D_ovl0E_13_80046D50)

/* the position of something at tile (22, ?, 30), set up in three places */
#define UNK_MACRO_ovl0E_13_80043110()                                                    \
    {                                                                                    \
        f32 unit;                                                                        \
        s32 i;                                                                           \
        s32 n;                                                                           \
        unit = 100.0f;                                                                   \
        D_ovl0E_13_80046D80.x = 22.0f * unit;                                            \
        D_ovl0E_13_80046D80.y = 0.0f;                                                    \
        n = 3;                                                                           \
        for (i = 0; i < n; i++) {                                                        \
            D_ovl0E_13_80046D80.y += func_ovl0E_13_80045510(i) * unit;                   \
        }                                                                                \
        D_ovl0E_13_80046D80.y += unit;                                                   \
        D_ovl0E_13_80046D80.z = (n * 10) * unit;                                         \
        D_ovl0E_13_80046D70 = func_ovl0E_13_80046450(0x27, &D_ovl0E_13_80046D80.x, 0);   \
    }

/* .bss */
u8 D_ovl0E_13_80046D50[0x10];
Vec3f D_ovl0E_13_80046D60;
s32 D_ovl0E_13_80046D6C;
s32 D_ovl0E_13_80046D70;
s32 D_ovl0E_13_80046D74;
s32 D_ovl0E_13_80046D78;
u8 D_ovl0E_13_80046D7C[0x4]; /* unused (func_ovl0E_13_80045154) */
Vec3f D_ovl0E_13_80046D80;
u8 D_ovl0E_13_80046D8C[0x4]; /* unused (func_ovl0E_13_80045154) */
UnkStruct_ovl0E_13_80046D90 D_ovl0E_13_80046D90;
UnkStructA *D_ovl0E_13_80046DA4;

/* .data */
/* passed to func_ovl0E_13_80046360: three 12-byte records */
u32 D_ovl0E_13_800467A0[][3] = {
    { 0xA20002, 0xE, 4 },
    { 0x9F0002, 0xE, 4 },
    { 0, 0, 4 },
};
/* five 12-byte records, each passed to func_ovl0E_13_80046508 */
u32 D_ovl0E_13_800467C4[][3] = {
    { 0, 0x22, 0xE0 },
    { 1, 0xE, 0xEC },
    { 2, 0, 0xDE },
    { 3, 0xD, 0xEB },
    { 4, 0xF, 0xED },
};
UnkStruct_ovl0E_13_80046800 D_ovl0E_13_80046800[1] = {
    { NULL, -1, 0x1B8, -1, -1, -1, -1, 200.0f, 210.0f, 260.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_13_80046800 D_ovl0E_13_80046838[4] = {
    { NULL, -1, 0x1B9, -1, -1, -1, -1, 190.0f, 160.0f, 260.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B9, -1, -1, -1, -1, 190.0f, 160.0f, 290.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B9, -1, -1, -1, -1, 260.0f, 160.0f, 260.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B9, -1, -1, -1, -1, 260.0f, 160.0f, 290.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_13_80046800 D_ovl0E_13_80046918[4] = {
    { NULL, -1, 0x1BA, -1, -1, -1, -1, 190.0f, 160.0f, 260.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1BA, -1, -1, -1, -1, 190.0f, 160.0f, 290.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1BA, -1, -1, -1, -1, 260.0f, 160.0f, 260.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1BA, -1, -1, -1, -1, 260.0f, 160.0f, 290.0f, 0.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_13_800469F8 D_ovl0E_13_800469F8[4] = {
    { 0x40F, 190.0f, 160.0f, 260.0f },
    { 0x410, 190.0f, 160.0f, 290.0f },
    { 0x411, 260.0f, 160.0f, 260.0f },
    { 0x412, 260.0f, 160.0f, 290.0f },
};
s32 D_ovl0E_13_80046A38 = -1;
UnkStruct_ovl0E_13_80046A3C D_ovl0E_13_80046A3C[9] = {
    { 0, -1, NULL, 0, 0, 0, 550.0f, 2000.0f, 2449.0f },
    { 1, -1, NULL, 0, 0, 0, 550.0f, 2000.0f, 2449.0f },
    { 2, -1, NULL, 0, 0, 0, 550.0f, 2000.0f, 2449.0f },
    { 3, -1, NULL, 0, 0, 0, 550.0f, 2000.0f, 2449.0f },
    { 4, -1, NULL, 0, 0, 0, 550.0f, 2000.0f, 2449.0f },
    { 5, -1, NULL, 0, 0, 0, 550.0f, 2000.0f, 2449.0f },
    { 6, -1, NULL, 0, 0, 0, 550.0f, 2000.0f, 2449.0f },
    { 7, -1, NULL, 0, 0, 0, 550.0f, 2000.0f, 2449.0f },
    { 8, -1, NULL, 0, 0, 0, 550.0f, 2000.0f, 2449.0f },
};
UnkStruct_ovl0E_13_80046B5C D_ovl0E_13_80046B5C[15] = {
    { 0.0f, -10.0f, 180.0f, 550.0f, 1200.0f, 0, 2 },
    { 7.071068f, -7.071068f, 135.0f, 1000.0f, 750.0f, 1, 2 },
    { 10.0f, 0.0f, 90.0f, 4200.0f, 750.0f, 1, 0 },
    { 7.071068f, 7.071068f, 45.0f, 4550.0f, 1100.0f, 1, 1 },
    { 0.0f, 10.0f, 0.0f, 4550.0f, 2300.0f, 0, 1 },
    { -7.071068f, 7.071068f, 315.0f, 4100.0f, 2750.0f, 2, 1 },
    { -10.0f, 0.0f, 270.0f, 1000.0f, 2750.0f, 2, 0 },
    { -7.071068f, -7.071068f, 225.0f, 550.0f, 2300.0f, 2, 2 },
    { 0.0f, -10.0f, 180.0f, 550.0f, 1200.0f, 0, 2 },
    { 7.071068f, -7.071068f, 135.0f, 1000.0f, 750.0f, 1, 2 },
    { 10.0f, 0.0f, 90.0f, 4200.0f, 750.0f, 1, 0 },
    { 7.071068f, 7.071068f, 45.0f, 4550.0f, 1100.0f, 1, 1 },
    { 0.0f, 10.0f, 0.0f, 4550.0f, 2300.0f, 0, 1 },
    { -7.071068f, 7.071068f, 315.0f, 4100.0f, 2750.0f, 2, 1 },
    { -10.0f, 0.0f, 270.0f, 2800.0f, 2750.0f, 2, 0 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0E_13_80045154(void) {
    D_ovl0E_13_80046D7C[0] = D_ovl0E_13_80046D8C[0];
}

static void func_ovl0E_13_8004514C(void) {
}

static void func_ovl0E_13_80045144(void) {
}

static void func_ovl0E_13_8004513C(void) {
}

void func_ovl0E_13_80045134(void) {
}

void func_ovl0E_13_8004511C(void) {
    D_ovl0E_13_80046D74 = -1;
    D_ovl0E_13_80046D78 = -1;
}

void func_ovl0E_13_800450C0(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_13_80045CE8(D_ovl0E_13_80046D80.x, D_ovl0E_13_80046D80.y, D_ovl0E_13_80046D80.z);
    func_ovl0E_13_80045D08(arg0, arg1, arg2);
    func_ovl0E_13_80046018(180);
}

void func_ovl0E_13_8004508C(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_13_800465A0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_13_80044FF4(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_13_80045EB0(arg0, 0x01000000);
    func_ovl0E_13_80046450(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_13_80046450(13, pos, 0);
    func_ovl0E_13_800465A8(180, pos);
}

void func_ovl0E_13_80044F30(UnkStructA *arg0) {
    func_ovl0E_13_80045EB0(arg0, 0x04000000);
    func_ovl0E_13_80046018(10);
    func_ovl0E_13_80045530(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_13_80046580(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_13_80046018(60);
}

void func_ovl0E_13_800449CC(void) {
    s16 moving;
    s32 pad; /* unused: the original's frame has one more slot */
    UnkStruct_ovl0E_13_80046A3C *rec;
    UnkStructA *obj;
    s16 doneX;
    s16 doneZ;
    s32 flags;
    f32 pos[3];

    moving = 0;
    rec = func_ovl0E_13_80046020();
    rec->unk8 = func_ovl0E_13_80045EF0(0x1BB, 0x30, rec->unk14, rec->unk18, rec->unk1C);
    obj = rec->unk8;
    func_ovl0E_13_80045EA8(obj, 0x0F000020);
    obj->unk30 = 1;
    obj->unk34 = 70.0f;
    obj->unk68 = 0.0f;
    obj->unk38 = 50.0f;
    obj->unk70 = 1.6333334f;
    rec->unk10 = 0;
    /* the set-up in the loop's header: on lines of their own, IDO schedules
     * the table's address after it */
    for (doneZ = 0, doneX = 0, rec->unkE = rec->unkC;;) {
        if (D_ovl0E_13_80046B5C[rec->unkE].unk14 == 0) {
            doneX = 1;
        }
        if (D_ovl0E_13_80046B5C[rec->unkE].unk14 == 1 && D_ovl0E_13_80046B5C[rec->unkE].unkC <= obj->unk40->unk10) {
            obj->unk40->unk10 = D_ovl0E_13_80046B5C[rec->unkE].unkC;
            doneX = 1;
        }
        if (D_ovl0E_13_80046B5C[rec->unkE].unk14 == 2 && obj->unk40->unk10 <= D_ovl0E_13_80046B5C[rec->unkE].unkC) {
            obj->unk40->unk10 = D_ovl0E_13_80046B5C[rec->unkE].unkC;
            doneX = 1;
        }
        if (D_ovl0E_13_80046B5C[rec->unkE].unk16 == 0) {
            doneZ = 1;
        }
        if (D_ovl0E_13_80046B5C[rec->unkE].unk16 == 1 && D_ovl0E_13_80046B5C[rec->unkE].unk10 <= obj->unk40->unk18) {
            obj->unk40->unk18 = D_ovl0E_13_80046B5C[rec->unkE].unk10;
            doneZ = 1;
        }
        if (D_ovl0E_13_80046B5C[rec->unkE].unk16 == 2 && obj->unk40->unk18 <= D_ovl0E_13_80046B5C[rec->unkE].unk10) {
            obj->unk40->unk18 = D_ovl0E_13_80046B5C[rec->unkE].unk10;
            doneZ = 1;
        }
        if (doneX == 1 && doneZ != 0) {
            rec->unkE++;
            if (rec->unkE >= 15) {
                rec->unkE = 0;
            }
        }
        obj->unk40->unk20 = D_ovl0E_13_80046B5C[rec->unkE].unk8;
        if (moving == 1) {
            obj->unk40->unk10 += D_ovl0E_13_80046B5C[rec->unkE].unk0;
            obj->unk40->unk18 += D_ovl0E_13_80046B5C[rec->unkE].unk4;
        }
        func_ovl0E_13_80045F28(obj);
        if (obj->unk6C == 0.0f && obj->unk68 == 0.0f) {
            moving = 1;
        }
        if (rec->unk10 > 0) {
            rec->unk10--;
        }
        if (rec->unk10 <= 0) {
            pos[0] = obj->unk40->unk10;
            pos[1] = obj->unk40->unk14;
            pos[2] = obj->unk40->unk18;
            if (func_ovl0E_13_80045E50(pos, D_ovl0E_13_80046D50) < 1200.0f) {
                func_ovl0E_13_800465A8(0x77, pos);
                rec->unk10 = 30;
            }
        }
        func_ovl0E_13_80045FB8(obj);
        flags = func_ovl0E_13_80045E58(obj, 0xC0);
        if (flags != 0) {
            if (flags & 0x6000) {
                func_ovl0E_13_80046448(0x14, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
                func_ovl0E_13_80046448(0x12, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
                func_ovl0E_13_800465A0(0x168, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
                pos[0] = obj->unk40->unk10;
                pos[1] = obj->unk40->unk14;
                pos[2] = obj->unk40->unk18;
                func_ovl0E_13_80046560(pos);
                func_ovl0E_13_80044848(rec, obj);
            } else {
                func_ovl0E_13_800465A0(0x26, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
            }
        }
        if (obj->unk40->unk14 <= func_ovl0E_13_800454D0()) {
            func_ovl0E_13_80044894(rec);
        }
        doneZ = 0;
        doneX = 0;
        func_ovl0E_13_80046040();
    }
}

void func_ovl0E_13_80044894(UnkStruct_ovl0E_13_80046A3C *arg0) {
    UnkStructA *obj;
    f32 floor;

    floor = func_ovl0E_13_800454D0();
    obj = arg0->unk8;
    while (TRUE) {
        obj->unk40->unk14 -= 4.0f;
        if (obj->unk40->unk14 <= floor - 200.0f || floor == -25500.0f) {
            func_ovl0E_13_80044848(arg0, obj);
        }
        func_ovl0E_13_80046040();
    }
}

void func_ovl0E_13_80044848(UnkStruct_ovl0E_13_80046A3C *arg0, UnkStructA *arg1) {
    func_ovl0E_13_80045EB0(arg1, 0x01000000);
    func_ovl0E_13_80045EC0(arg1);
    arg0->unk4 = -1;
    arg0->unk8 = NULL;
    func_ovl0E_13_80046008();
}

void func_ovl0E_13_8004439C(void) {
    UnkStructA *obj;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_13_80044324();
    func_ovl0E_13_80045590(func_ovl0E_13_80044FF4);
    func_ovl0E_13_800455E0(func_ovl0E_13_80044F30);
    func_ovl0E_13_80046360(D_ovl0E_13_800467A0);
    func_ovl0E_13_800454A8(0x1A2);
    obj = func_ovl0E_13_80045EF0(0x1A3, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_13_80045EA8(obj, 0x01000000);
    p = D_ovl0E_13_800467C4;
    count = 5;
    for (i = 0; i < count; i++) {
        func_ovl0E_13_80046508((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_13_800454C0(0x1A9);
    func_ovl0E_13_80045658();
    func_ovl0E_13_80044294();
    func_ovl0E_13_8004424C();
    if (func_ovl0E_13_80046280(0x40E) == 0) {
        func_ovl0E_13_80044158();
    } else {
        UNK_MACRO_ovl0E_13_80043110();
    }
    func_ovl0E_13_80045BF0(obj->unk40, 0, 0, 0, 2, 0x400);
    func_ovl0E_13_80046338(0x37A, 0x3DE, 0xFF, 0x87, 0x1F);
    func_ovl0E_13_80046348(0xFF, 0xA1, 0x1D);
}

void func_ovl0E_13_80044780(void) {
    UnkStruct_ovl0E_13_80046A3C *rec;
    s16 i;

    while (TRUE) {
        rec = D_ovl0E_13_80046A3C;
        for (i = 0; i < 9; i++, rec++) {
            if (rec->unk8 == NULL) {
                break;
            }
        }
        if (i < 9) {
            rec->unk4 = func_ovl0E_13_80045FF8(func_ovl0E_13_800449CC, rec, 0, 0, 0x110);
            func_ovl0E_13_80046018(300);
        }
        func_ovl0E_13_80046040();
    }
}

void func_ovl0E_13_800446F0(void) {
    UnkStruct_ovl0E_13_80046A3C *rec;
    s16 i;

    func_ovl0E_13_8004424C();
    D_ovl0E_13_80046A38 = -1;
    for (i = 0, rec = D_ovl0E_13_80046A3C; i < 9; i++, rec++) {
        if (rec->unk8 == NULL) {
            rec->unk4 = func_ovl0E_13_80045FF8(func_ovl0E_13_800449CC, rec, 0, 0, 0x110);
        }
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_13_80044590(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0E_13_8004439C();
            break;
        case 17:
            func_ovl0E_13_800440C0();
            break;
        case 18:
            func_ovl0E_13_80044070();
            break;
        case 4:
            func_ovl0E_13_80044008();
            break;
        case 5:
            func_ovl0E_13_80043E2C();
            break;
        case 0x50:
            func_ovl0E_13_80043CD4();
            break;
        case 3:
            func_ovl0E_13_80043C28();
            break;
        case 12:
            func_ovl0E_13_800430E8();
            break;
        case 1:
            func_ovl0E_13_800430A8();
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_13_80044364(void) {
    func_ovl0E_13_80044324();
    func_ovl0E_13_80045590(func_ovl0E_13_80044FF4);
    func_ovl0E_13_800455E0(func_ovl0E_13_80044F30);
}

void func_ovl0E_13_80044324(void) {
    func_ovl0E_13_80046278(0x400);
    func_ovl0E_13_80046278(0x401);
    func_ovl0E_13_80046278(0x402);
    func_ovl0E_13_80046278(0x403);
    func_ovl0E_13_80046278(0x404);
}

void func_ovl0E_13_8004431C(void) {
}

void func_ovl0E_13_80044294(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0E_13_800437C0(&D_ovl0E_13_80046800[i]);
        func_ovl0E_13_80045EA8(D_ovl0E_13_80046800[i].unk0, 0x02000000);
        func_ovl0E_13_80045EB0(D_ovl0E_13_80046800[i].unk0, 0x80000);
    }
}

void func_ovl0E_13_8004424C(void) {
    s16 i;

    D_ovl0E_13_80046A38 = -1;
    for (i = 0; i < 9; i++) {
        D_ovl0E_13_80046A3C[i].unk0 = i;
        D_ovl0E_13_80046A3C[i].unk4 = -1;
        D_ovl0E_13_80046A3C[i].unk8 = NULL;
    }
}

void func_ovl0E_13_80044158(void) {
    s32 i;

    func_ovl0E_13_80044108();
    for (i = 0; i < 4; i++) {
        if (func_ovl0E_13_80046280(D_ovl0E_13_800469F8[i].unk0) != 0) {
            func_ovl0E_13_800437C0(&D_ovl0E_13_80046918[i]);
            func_ovl0E_13_80045EA8(D_ovl0E_13_80046918[i].unk0, 0x02000000);
            func_ovl0E_13_80045EB0(D_ovl0E_13_80046918[i].unk0, 0x80000);
        } else {
            func_ovl0E_13_800437C0(&D_ovl0E_13_80046838[i]);
            func_ovl0E_13_80045EA8(D_ovl0E_13_80046838[i].unk0, 0x02000000);
            func_ovl0E_13_80045EB0(D_ovl0E_13_80046838[i].unk0, 0x80000);
        }
    }
}

void func_ovl0E_13_80044108(void) {
    if (func_ovl0E_13_80046280(0x400) == 0) {
        D_ovl0E_13_80046DA4 = func_ovl0E_13_80045EF0(-1, 0x80, 0.0f, 0.0f, 0.0f);
        func_ovl0E_13_80046270(0x400);
    }
}

void func_ovl0E_13_800440C0(void) {
    func_ovl0E_13_80045660(0x11, 4, 0x1B);
    func_ovl0E_13_80044048(1, 0, 0, 0.0f, 0);
}

void func_ovl0E_13_80044070(void) {
    func_ovl0E_13_80045660(0x2B, 0, 0x1E);
    func_ovl0E_13_80044048(2, 0, 0x80, 0.0f, 3);
}

void func_ovl0E_13_80044048(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_13_80046D90.unk0 = arg0;
    D_ovl0E_13_80046D90.unk4 = arg1;
    D_ovl0E_13_80046D90.unk8 = arg2;
    D_ovl0E_13_80046D90.unkC = arg3;
    D_ovl0E_13_80046D90.unk10 = arg4;
}

void func_ovl0E_13_80044008(void) {
    func_ovl0E_13_80043EF0();
    if (func_ovl0E_13_80046280(0x40E) != 0) {
        func_ovl0E_13_80043E54();
        func_ovl0E_13_800431E4();
    }
}

void func_ovl0E_13_80043EF0(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_13_800456B8();
    switch (D_ovl0E_13_80046D90.unk8) {
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
        func_ovl0E_13_80045D08(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_13_80046D90.unkC;
        func_ovl0E_13_80045D10(&sp1C, NULL, NULL);
        func_ovl0E_13_80045D08(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_13_800456A0(D_ovl0E_13_80046D90.unk4);
}

void func_ovl0E_13_80043EA8(f32 arg0) {
    f32 sp1C;

    func_ovl0E_13_80045D10(&sp1C, NULL, NULL);
    func_ovl0E_13_80045D08(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_13_80043E54(void) {
    ((UnkStruct_ovl0E_13_40 *) D_ovl0E_13_80046800[0].unk0->unk40)->unk48->unk4->unk4 =
        func_ovl0E_13_80045BE8(D_ovl0E_13_80046800[0].unk0->unk40, 0) - 0.001f;
}

void func_ovl0E_13_80043E2C(void) {
    func_ovl0E_13_80043DF0();
    func_ovl0E_13_80043D78();
}

void func_ovl0E_13_80043DF0(void) {
    D_ovl0E_13_80046A38 = func_ovl0E_13_80045FF8(func_ovl0E_13_80044780, NULL, 0, 0, 0x110);
}

void func_ovl0E_13_80043D78(void) {
    UNK_MACRO_ovl0E_13_80043BE0();
    func_ovl0E_13_800456A8(D_ovl0E_13_80046D90.unk4, 3, 4.0f, D_ovl0E_13_80046D90.unk10, 0, 1, 1);
}

void func_ovl0E_13_80043C90(void) {
    if (func_ovl0E_13_80046280(0x40E) != 0) {
        func_ovl0E_13_80046458(D_ovl0E_13_80046D70);
    }
    func_ovl0E_13_800455C8();
}

void func_ovl0E_13_80043CD4(void) {
    func_ovl0E_13_80043CCC();
    if (func_ovl0E_13_80045670(0x2B, 0x1E, 0x2C, 0x1E) != 0) {
        D_ovl0E_13_80046D74 = 0x50;
        D_ovl0E_13_80046D78 = 0x15;
        func_ovl0E_13_800455A0(0x50, 0x15, 0);
    }
    if (func_ovl0E_13_80045670(0x16, 0x1E, 0x17, 0x1F) != 0) {
        func_ovl0E_13_80045EB0(D_ovl0E_13_80046800[0].unk0, 0x02000000);
        func_ovl0E_13_80043C90();
    }
    func_ovl0E_13_80043C88();
    func_ovl0E_13_80043C80();
    func_ovl0E_13_80043C78();
}

static void func_ovl0E_13_80043CCC(void) {
}

static void func_ovl0E_13_80043C88(void) {
}

static void func_ovl0E_13_80043C80(void) {
}

static void func_ovl0E_13_80043C78(void) {
}

void func_ovl0E_13_80043C28(void) {
    UNK_MACRO_ovl0E_13_80043BE0();
    func_ovl0E_13_80043A30();
}

void func_ovl0E_13_80043BE0(void) {
    UNK_MACRO_ovl0E_13_80043BE0();
}

void func_ovl0E_13_80043BD8(void) {
}

void func_ovl0E_13_80043A30(void) {
    UnkStruct_ovl0E_13_800469F8 *sw;
    s16 i;

    D_ovl0E_13_80046DA4->unk30 = 1;
    D_ovl0E_13_80046DA4->unk34 = 50.0f;
    D_ovl0E_13_80046DA4->unk38 = 50.0f;
    for (i = 0, sw = D_ovl0E_13_800469F8; i < 4; i++, sw++) {
        if (func_ovl0E_13_80046280(sw->unk0) == 0) {
            D_ovl0E_13_80046DA4->unk40->unk10 = sw->unk4 * 10.0f;
            D_ovl0E_13_80046DA4->unk40->unk14 = sw->unk8 * 10.0f;
            D_ovl0E_13_80046DA4->unk40->unk18 = sw->unkC * 10.0f;
            if (func_ovl0E_13_80045E58(D_ovl0E_13_80046DA4, 0x40) != 0) {
                func_ovl0E_13_800465A0(0x49, D_ovl0E_13_80046DA4->unk40->unk10, D_ovl0E_13_80046DA4->unk40->unk14,
                                       D_ovl0E_13_80046DA4->unk40->unk18);
                func_ovl0E_13_80046448(0xF, sw->unk4 * 10.0f, sw->unk8 * 10.0f + 10, sw->unkC * 10.0f, 0);
                func_ovl0E_13_80043940(i);
                func_ovl0E_13_80046270(sw->unk0);
                if (func_ovl0E_13_80043754() != 0) {
                    func_ovl0E_13_80043444();
                }
            }
        }
    }
}

void func_ovl0E_13_80043940(s16 arg0) {
    UnkStruct_ovl0E_13_80046800 *e;
    UnkStruct_ovl0E_13_80046800 *f;

    e = &D_ovl0E_13_80046918[arg0];
    f = &D_ovl0E_13_80046838[arg0];
    func_ovl0E_13_800437C0(e);
    func_ovl0E_13_80045EA8(e->unk0, 0x02000000);
    func_ovl0E_13_80046040();
    func_ovl0E_13_800437B8(f);
}

static void func_ovl0E_13_800437C0(UnkStruct_ovl0E_13_80046800 *e) {
    e->unk0 = func_ovl0E_13_80045EF0(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0E_13_80045EA8(e->unk0, 0x01080000);
    func_ovl0E_13_80045EB0(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl0E_13_80045BF0(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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

static void func_ovl0E_13_800437B8(UnkStruct_ovl0E_13_80046800 *e) {
    func_ovl0E_13_80045EB0(e->unk0, 0x01000000);
    func_ovl0E_13_80045EC0(e->unk0);
    /* 0xFFFF, not -1: never equal to the s16 fields */
    if (e->unkC != 0xFFFF && e->unkE != 0xFFFF && e->unk10 != 0xFFFF && e->unk12 != 0xFFFF) {
        func_ovl0E_13_80045BF8(e->unk4);
    }
    e->unk0 = NULL;
    e->unk4 = -1;
}

s32 func_ovl0E_13_80043754(void) {
    if (func_ovl0E_13_80046280(0x40F) == 0 || func_ovl0E_13_80046280(0x410) == 0 ||
        func_ovl0E_13_80046280(0x411) == 0 || func_ovl0E_13_80046280(0x412) == 0) {
        return 0;
    }
    return 1;
}

void func_ovl0E_13_80043444(void) {
    f32 a;
    f32 y;
    f32 z;
    f32 c;
    f32 b;
    s16 i;

    func_ovl0E_13_80046018(30);
    func_ovl0E_13_80045618(1);
    func_ovl0E_13_80045610(0);
    func_ovl0E_13_80046018(30);
    func_ovl0E_13_80045E08();
    func_ovl0E_13_80045D50(0x7F);
    func_ovl0E_13_80045CE8(2200.0f, 1600.0f, 2800.0f);
    func_ovl0E_13_80045D08(135.0f, 30.0f, 3500.0f);
    func_ovl0E_13_80046018(30);
    func_ovl0E_13_80043244();
    func_ovl0E_13_80046018(30);
    a = 135.0f;
    y = 1600.0f;
    z = 2800.0f;
    c = 3500.0f;
    b = 30.0f;
    for (i = 60; i > 0; i--) {
        func_ovl0E_13_80045CE8(2250.0f, y, z);
        func_ovl0E_13_80045D08(a, b, c);
        func_ovl0E_13_80046040();
        a += 0.75f;
        y += -3.3333333f;
        z += 16.666666f;
        c += -41.666668f;
        b += 0.5f;
    }
    func_ovl0E_13_80046018(30);
    z = 3800.0f;
    c = 1000.0f;
    for (i = 60; i > 0; i--) {
        func_ovl0E_13_80045CE8(2250.0f, 1400.0f, z);
        func_ovl0E_13_80045D08(180.0f, 60.0f, c);
        func_ovl0E_13_80046040();
        z += -13.333333f;
        c += 16.666666f;
    }
    func_ovl0E_13_80046018(10);
    func_ovl0E_13_80046580(0x2C);
    UNK_MACRO_ovl0E_13_80043110();
    func_ovl0E_13_80046018(120);
    func_ovl0E_13_80045E10();
    func_ovl0E_13_80045DD8(D_ovl0E_13_80046D50);
    func_ovl0E_13_80045D48(0x1F);
    func_ovl0E_13_80045618(0);
    func_ovl0E_13_80045610(1);
}

void func_ovl0E_13_80043244(void) {
    s16 i;
    s16 alpha;

    func_ovl0E_13_80046580(0x7A);
    func_ovl0E_13_80045EA8(D_ovl0E_13_80046800[0].unk0, 0x04000000);
    func_ovl0E_13_80046040();
    for (i = 0; i < 4; i++) {
        func_ovl0E_13_80045EA8(D_ovl0E_13_80046918[i].unk0, 0x80000);
        func_ovl0E_13_80046448(0xF, D_ovl0E_13_80046918[i].unk14 * 10.0f, D_ovl0E_13_80046918[i].unk18 * 10.0f + 10,
                               D_ovl0E_13_80046918[i].unk1C * 10.0f, 0);
    }
    for (alpha = 0xFF; alpha >= 0; alpha -= 30) {
        for (i = 0; i < 4; i++) {
            D_ovl0E_13_80046918[i].unk0->unk40->unk36 = alpha;
            func_ovl0E_13_80046040();
        }
    }
    func_ovl0E_13_80046018(10);
    func_ovl0E_13_800465A0(0x82, D_ovl0E_13_80046800[0].unk14 * 10.0f, D_ovl0E_13_80046800[0].unk18 * 10.0f,
                           D_ovl0E_13_80046800[0].unk1C * 10.0f);
    while (!(D_ovl0E_13_80046800[0].unk0->unk40->unkC & 0x40)) {
        func_ovl0E_13_80046040();
    }
    func_ovl0E_13_800431E4();
    func_ovl0E_13_80046270(0x40E);
}

void func_ovl0E_13_800431E4(void) {
    func_ovl0E_13_800454E8(0x13, 3, 0x1A, 0x1A, 0x1D, 0x11);
    func_ovl0E_13_800454E8(0x13, 4, 0x19, 0x1A, 0x1C, 0x10);
}

void func_ovl0E_13_80043110(void) {
    func_ovl0E_13_80043108();
    UNK_MACRO_ovl0E_13_80043110();
}

static void func_ovl0E_13_80043108(void) {
}

void func_ovl0E_13_800430E8(void) {
    func_ovl0E_13_800456F0(1);
}

void func_ovl0E_13_800430C8(void) {
    func_ovl0E_13_800456F0(1);
}

void func_ovl0E_13_800430A8(void) {
    func_ovl0E_13_80043018();
}

void func_ovl0E_13_80043018(void) {
    s16 i;

    /* one line, as in func_ovl0E_13_800449CC's loop */
    i = 0; do {
        if (D_ovl0E_13_80046A3C[i].unk4 != -1) {
            func_ovl0E_13_80046000(D_ovl0E_13_80046A3C[i].unk4);
        }
        i++;
    } while (i < 9);
    if (D_ovl0E_13_80046A38 != -1) {
        func_ovl0E_13_80046000(D_ovl0E_13_80046A38);
    }
}

void func_ovl0E_13_80043010(void) {
}
