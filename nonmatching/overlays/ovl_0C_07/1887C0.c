/*
 * NON_MATCHING: ovl_0C_07's game object, complete: every function and its
 * data (.data 0x2B0, .rodata 0x170 and .bss 0x60 laid out as the original).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 2, eu 2, jp 2
 *
 * The handler's case 2 calls func_ovl0C_07_80044594 (inlined), whose call
 * of func_ovl0C_07_8004455C then stays a call, and its empty case 0x53
 * is kept (both only together give the handler).
 *
 * What still differs in us (words):
 * - func_ovl0C_07_80044178 (2): the epilogue restores s2, s1, s0; the
 *   original restores s0 first, as in ovl_0C_04's 80043878 (the same
 *   function) and ovl_0C_08's 80043654.  The loop as an index, a constant
 *   count, a for with the pointer step or a do-while are all worse.
 *   Also no change: all 24 local declaration orders, s16/u32/s32/f32
 *   index and pointer types, a while (TRUE) exit, a temp for unk40, the
 *   record set-up as a static taking its pointer (20 words in all), and
 *   41 orders of the final nine stores (49 words or more).
 *   ugen (cc -S) lists the restores s0, s1, s2; as1 reverses them when the
 *   last block ends in a lw, lw, store chain.  A block boundary before the
 *   epilogue (a label, .align or a section switch) or ugen's restores
 *   reversed give the original; no C found does (scratch/epi/).
 */
#include "common.h"

/*
 * ovl_0C_07's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).  ovl_0C_09's skeleton for
 * the camera, the lifts and the movers, ovl_0C_04's object setup.
 */

/* the handler's state, set by func_ovl0C_07_80043CF0 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_07_80047990;

/* a gate: its object, its position, the trigger object's position and the
 * arguments of its map changes (the task func_ovl0C_07_80044B48 takes one) */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
} UnkStruct_ovl0C_07_80047590;

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
} UnkStruct_ovl0C_07_80047608;

/* a mover: the tasks func_ovl0C_07_80044CE0 and func_ovl0C_07_80044DC8
 * take one (unk0 indexes D_ovl0C_07_80047608) */
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
} UnkStruct_ovl0C_07_80047648;

/* three lifts, each the task func_ovl0C_07_80045694's */
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
} UnkStruct_ovl0C_07_800476D0;

/* the stage object func_ovl0C_07_80044178 sets up (ovl_0C_04's
 * D_ovl0C_04_80045D34) */
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
} UnkStruct_ovl0C_07_800477A8;

void func_ovl0C_07_80046238(s32);
void func_ovl0C_07_80046250(s32);
void func_ovl0C_07_80046270(s32, s32, s32, s32);
void func_ovl0C_07_80046278(s32, s32, s32, s32, s32, s32);
void func_ovl0C_07_80046280(s32, s32, s32, s32, s32, s32, s32);
void func_ovl0C_07_800462C0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_07_80046320(void (*)(UnkStructA *));
void func_ovl0C_07_80046330(s32, s32, s32);
void func_ovl0C_07_80046370(void (*)(UnkStructA *));
void func_ovl0C_07_800463A0(s32);
void func_ovl0C_07_800463A8(s32);
void func_ovl0C_07_800463C0(s32, s32);
void func_ovl0C_07_800463E8(void);
void func_ovl0C_07_800463F0(s32, s32, s32);
void func_ovl0C_07_800463F8(void *);
s32 func_ovl0C_07_80046400(s32, s32, s32, s32);
s32 func_ovl0C_07_80046418(void);
void func_ovl0C_07_80046420(s32, void *);
void func_ovl0C_07_80046428(s32);
void func_ovl0C_07_80046430(s32);
void func_ovl0C_07_80046438(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_07_80046440(const char *);
void func_ovl0C_07_80046448(void);
void func_ovl0C_07_80046460(s32);
UnkStructA *func_ovl0C_07_80046478(s32);
void func_ovl0C_07_80046480(s32);
f32 func_ovl0C_07_80046978(UnkStructA_40 *, s32);
s32 func_ovl0C_07_80046980(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0C_07_80046A78(f32, f32, f32);
void func_ovl0C_07_80046A98(f32, f32, f32);
void func_ovl0C_07_80046AA0(f32 *, f32 *, f32 *);
void func_ovl0C_07_80046AE0(s32);
void func_ovl0C_07_80046AF0(s32);
void func_ovl0C_07_80046B30(f32, f32);
void func_ovl0C_07_80046B98(void);
void func_ovl0C_07_80046BA0(void);
s32 func_ovl0C_07_80046BE8(UnkStructA *, s32);
void func_ovl0C_07_80046C10(UnkStructA *);
void func_ovl0C_07_80046C18(UnkStructA *, UnkStructA *);
void func_ovl0C_07_80046C38(UnkStructA *, s32);
void func_ovl0C_07_80046C40(UnkStructA *, s32);
void func_ovl0C_07_80046C50(UnkStructA *);
UnkStructA *func_ovl0C_07_80046C60(s32, s32, s32, s32);
UnkStructA *func_ovl0C_07_80046C70(UnkStructA *);
UnkStructA *func_ovl0C_07_80046C80(s32, s32, f32, f32, f32);
void func_ovl0C_07_80046CB8(UnkStructA *);
void func_ovl0C_07_80046D48(UnkStructA *);
s32 func_ovl0C_07_80046D88(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_07_80046D98(void);
void func_ovl0C_07_80046DA8(s32);
void *func_ovl0C_07_80046DB0(void);
s32 func_ovl0C_07_80046DD0(void);
f32 func_ovl0C_07_80046F30(f32);
void func_ovl0C_07_80047000(s32);
void func_ovl0C_07_80047008(s32);
s32 func_ovl0C_07_80047010(s32);
void func_ovl0C_07_800470F0(u32 (*)[3]);
void func_ovl0C_07_80047108(u32 (*)[3]);
void func_ovl0C_07_80047208(s16, s32);
void func_ovl0C_07_80047210(s16, s32);
void func_ovl0C_07_80047228(f32 *);
void func_ovl0C_07_80047298(s32, s32, s32);
void func_ovl0C_07_800472B8(s32);
void func_ovl0C_07_800472F8(void);
s32 func_ovl0C_07_80047310(s32);
void func_ovl0C_07_80047330(s32, f32, f32, f32);
void func_ovl0C_07_80047340(s32);
void func_ovl0C_07_80047348(s32, s8);
void func_ovl0C_07_80047488(void);
void func_ovl0C_07_80047490(void);

void func_ovl0C_07_80043010(void);
void func_ovl0C_07_80043018(void);
void func_ovl0C_07_80043038(void);
void func_ovl0C_07_80043068(void);
void func_ovl0C_07_80043088(void);
void func_ovl0C_07_800430A8(UnkStruct_ovl0C_07_80047590 *arg0);
void func_ovl0C_07_80043134(UnkStruct_ovl0C_07_80047590 *arg0);
static void func_ovl0C_07_800431B0(void);
void func_ovl0C_07_800431B8(void);
void func_ovl0C_07_80043200(void);
static void func_ovl0C_07_80043278(void);
void func_ovl0C_07_80043280(void *arg0);
void func_ovl0C_07_800432B8(void *arg0);
void func_ovl0C_07_800432F0(UnkStructA *arg0, UnkStructA *arg1, f32 arg2);
void func_ovl0C_07_80043340(UnkStruct_ovl0C_07_80047648 *arg0);
void func_ovl0C_07_80043400(void);
void func_ovl0C_07_80043450(void);
void func_ovl0C_07_8004357C(UnkStruct_ovl0C_07_80047590 *arg0);
void func_ovl0C_07_800435E8(void);
void func_ovl0C_07_80043634(void);
void func_ovl0C_07_800436A0(void);
void func_ovl0C_07_800436D8(void);
void func_ovl0C_07_80043750(void);
void func_ovl0C_07_80043798(void);
void func_ovl0C_07_80043820(UnkStruct_ovl0C_07_80047590 *arg0);
void func_ovl0C_07_800438E4(UnkStruct_ovl0C_07_80047590 *arg0);
void func_ovl0C_07_80043920(UnkStruct_ovl0C_07_80047608 *arg0);
void func_ovl0C_07_800439A4(void);
void func_ovl0C_07_80043A28(void);
void func_ovl0C_07_80043A80(f32 arg0);
void func_ovl0C_07_80043AC8(void);
void func_ovl0C_07_80043BF8(void);
void func_ovl0C_07_80043CF0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4);
static void func_ovl0C_07_80043D18(void);
void func_ovl0C_07_80043D20(UnkStruct_ovl0C_07_80047590 *arg0);
void func_ovl0C_07_80043D7C(s32 arg0);
void func_ovl0C_07_80043E38(void);
void func_ovl0C_07_80043FDC(void);
void func_ovl0C_07_80044024(void);
static void func_ovl0C_07_80044170(void);
void func_ovl0C_07_80044178(void);
void func_ovl0C_07_800443AC(void);
void func_ovl0C_07_8004440C(void);
void func_ovl0C_07_80044474(void);
void func_ovl0C_07_800444C0(void);
void func_ovl0C_07_8004451C(void);
void func_ovl0C_07_8004455C(void);
void func_ovl0C_07_80044594(void);
void func_ovl0C_07_800445B4(s32 arg0);
void func_ovl0C_07_800447AC(void);
void func_ovl0C_07_80044800(void);
void func_ovl0C_07_800448A4(UnkStructA *arg0);
void func_ovl0C_07_800448D0(void);
void func_ovl0C_07_80044B48(void);
void func_ovl0C_07_80044CE0(void);
void func_ovl0C_07_80044D40(s32 arg0, UnkStructA *arg1, UnkStructA *arg2, f32 arg3);
void func_ovl0C_07_80044DC8(void);
void func_ovl0C_07_800454AC(UnkStruct_ovl0C_07_800476D0 *arg0, UnkStructA *arg1, UnkStructA *arg2);
void func_ovl0C_07_80045548(UnkStruct_ovl0C_07_800476D0 *arg0, UnkStructA *arg1);
void func_ovl0C_07_80045694(void);
void func_ovl0C_07_80045B10(UnkStructA *arg0);
void func_ovl0C_07_80045BD0(UnkStructA *arg0);
void func_ovl0C_07_80045C14(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_ovl0C_07_80045CEC(void);
void func_ovl0C_07_80045DFC(s32 arg0, UnkStructA *arg1);
void func_ovl0C_07_80045E30(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0C_07_80045E8C(void);
void func_ovl0C_07_80045EA4(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (as in ovl_0C_04 and ovl_0C_09). */
#define UNK_MACRO_ovl0C_07_800431B8() \
    D_ovl0C_07_8004796C = func_ovl0C_07_80046418(); func_ovl0C_07_800463F8(&D_ovl0C_07_80047960); func_ovl0C_07_80046420(D_ovl0C_07_8004796C, D_ovl0C_07_80047950)

/* .bss */
u8 D_ovl0C_07_80047950[0x10];
Vec3f D_ovl0C_07_80047960;
s32 D_ovl0C_07_8004796C;
u8 D_ovl0C_07_80047970[0x4]; /* unused (func_ovl0C_07_80045EA4) */
s32 D_ovl0C_07_80047974;
s32 D_ovl0C_07_80047978;
u8 D_ovl0C_07_8004797C[0x4]; /* unused (func_ovl0C_07_80045EA4) */
Vec3f D_ovl0C_07_80047980;
u8 D_ovl0C_07_8004798C[0x4]; /* unused (func_ovl0C_07_80045EA4) */
UnkStruct_ovl0C_07_80047990 D_ovl0C_07_80047990;
UnkStructA *D_ovl0C_07_800479A4;
UnkStructA *D_ovl0C_07_800479A8[2];

/* .data */
/* passed to func_ovl0C_07_800470F0: three 12-byte records */
u32 D_ovl0C_07_80047530[][3] = {
    { 0x910002, 0x3000E, 4 },
    { 0x940002, 0xE, 4 },
    { 0x950000, 0xE, 4 },
};
/* passed to func_ovl0C_07_80047108 */
u32 D_ovl0C_07_80047554[][3] = {
    { 0, 4, 0 },
    { 4, 0x960000, 0x84 },
};
/* three 12-byte records, each passed to func_ovl0C_07_80047298 */
u32 D_ovl0C_07_8004756C[][3] = {
    { 0, 0, 0xDE },
    { 1, 0x22, 0xE0 },
    { 2, 5, 0x34F },
};
UnkStruct_ovl0C_07_80047590 D_ovl0C_07_80047590[] = {
    { 0, NULL, 200.0f, 200.0f, 1850.0f, 0x40, 250.0f, 200.0f, 1850.0f, 1, 1, 0x12, 4, 2, 0x13, 1, 1, 0x12, 1,
      0x13, 3, 1, 0x14, 0x17, 0xA010, 3, 1, 0x11, 0x18, 0xA010 },
};
UnkStruct_ovl0C_07_80047608 D_ovl0C_07_80047608[] = {
    { NULL, 1550.0f, 1000.0f, 1850.0f, 1000.0f, -400.0f, 3350.0f, 1850.0f },
    { NULL, 3350.0f, 1000.0f, 1850.0f, 1000.0f, -400.0f, 3350.0f, 1850.0f },
};
UnkStruct_ovl0C_07_80047648 D_ovl0C_07_80047648[] = {
    { 0, NULL, 0x2D, 0x15, 0.0f, 12.0f, 34.0f, 1.0f, 2, 0x439,
      1550.0f, 1500.0f, 1850.0f, 3350.0f, 1450.0f, 3350.0f, 3850.0f },
    { 1, NULL, 0x2D, 0x16, 0.0f, 12.0f, 34.0f, 1.0f, 1, 0x438,
      3350.0f, 2000.0f, 1000.0f, 3350.0f, 1450.0f, 3350.0f, 3850.0f },
};
UnkStruct_ovl0C_07_800476D0 D_ovl0C_07_800476D0[] = {
    { 0, 0, 0, NULL, NULL, 1850.0f, 100.0f, 2250.0f, 100.0f, 700.0f, 1850.0f, 0.0f, 2250.0f, 43.5f,
      0x12, 1, 0x16, 0x13, 3, 0x17, 0x40, 0, 0 },
    { 1, 0, 0, NULL, NULL, 1850.0f, 100.0f, 1850.0f, 100.0f, 900.0f, 1850.0f, 0.0f, 1850.0f, 43.5f,
      0x12, 1, 0x12, 0x13, 4, 0x13, 0x40, 0, 0 },
    { 2, 0, 0, NULL, NULL, 1850.0f, 100.0f, 1450.0f, 100.0f, 700.0f, 1850.0f, 0.0f, 1450.0f, 43.5f,
      0x12, 1, 0xE, 0x13, 3, 0xF, 0x40, 0, 0 },
};
UnkStruct_ovl0C_07_800477A8 D_ovl0C_07_800477A8 = {
    NULL, -1, 0x2B9, -5, -0x400, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
};

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0C_07_80045EE4(void) {
}

static void func_ovl0C_07_80045EDC(void) {
}

static void func_ovl0C_07_80045ED4(void) {
}

static void func_ovl0C_07_80045ECC(void) {
}

static void func_ovl0C_07_80045EC4(void) {
}

static void func_ovl0C_07_80045EBC(void) {
}

static void func_ovl0C_07_80045EB4(void) {
}

static void func_ovl0C_07_80045EAC(void) {
}

void func_ovl0C_07_80045EA4(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl0C_07_80047970[0] = D_ovl0C_07_8004797C[0] + D_ovl0C_07_8004798C[0];
    }
}

void func_ovl0C_07_80045E8C(void) {
    D_ovl0C_07_80047974 = -1;
    D_ovl0C_07_80047978 = -1;
}

void func_ovl0C_07_80045E30(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_07_80046A78(D_ovl0C_07_80047980.x, D_ovl0C_07_80047980.y, D_ovl0C_07_80047980.z);
    func_ovl0C_07_80046A98(arg0, arg1, arg2);
    func_ovl0C_07_80046DA8(180);
}

void func_ovl0C_07_80045DFC(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_07_80047330(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_07_80045CEC(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_07_80046DB0();
    func_ovl0C_07_80047330(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_07_80046C60(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_07_80045C14(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_07_80046DD0();
    }
    func_ovl0C_07_80046C50(obj);
    func_ovl0C_07_80046D98();
}

void func_ovl0C_07_80045C14(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0C_07_80046F30((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_07_80046F30((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_07_80045BD0(UnkStructA *arg0) {
    func_ovl0C_07_80046C40(arg0, 0x01000000);
    func_ovl0C_07_80046D88(func_ovl0C_07_80045CEC, arg0, 0, 0, 0x150);
}

void func_ovl0C_07_80045B10(UnkStructA *arg0) {
    func_ovl0C_07_80046DA8(10);
    func_ovl0C_07_800462C0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_07_80046DA8(60);
}

/* a lift: rises while something stands on it, falls back otherwise */
void func_ovl0C_07_80045694(void) {
    UnkStruct_ovl0C_07_800476D0 *rec;
    UnkStructA *obj;
    UnkStructA *player;
    s16 wait;

    rec = func_ovl0C_07_80046DB0();
    obj = rec->unk8;
    player = func_ovl0C_07_80046478(0);
    obj->unk68 = 0.0f;
    wait = 2;
    obj->unk70 = 1.6333334f;
    while (TRUE) {
        D_ovl0C_07_800479A4->unk30 = 4;
        D_ovl0C_07_800479A4->unk34 = 100.0f;
        D_ovl0C_07_800479A4->unk38 = 100.0f;
        D_ovl0C_07_800479A4->unk40->unk10 = rec->unk24;
        D_ovl0C_07_800479A4->unk40->unk14 = rec->unk28;
        D_ovl0C_07_800479A4->unk40->unk18 = rec->unk2C;
        func_ovl0C_07_80046D48(rec->unkC);
        if (func_ovl0C_07_80046BE8(D_ovl0C_07_800479A4, 2) != 0) {
            wait = 2;
            rec->unk44 |= 1;
        } else if (wait == 0) {
            rec->unk44 &= ~1;
        } else {
            wait--;
        }
        if (func_ovl0C_07_80046BE8(D_ovl0C_07_800479A4, 0x40) != 0 && (rec->unk44 & 1)) {
            func_ovl0C_07_80046278(rec->unk34, rec->unk36, rec->unk38, rec->unk3A, rec->unk3E, 0x10);
            func_ovl0C_07_80046C40(rec->unkC, 0x100);
            obj->unk68 = rec->unk30;
        }
        if (obj->unk40->unk14 - obj->unk6C + obj->unk68 <= rec->unk1C) {
            obj->unk6C = 0.0f;
            obj->unk68 = 0.0f;
            obj->unk40->unk14 = rec->unk1C;
            func_ovl0C_07_80046C38(rec->unkC, 0x100);
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
            func_ovl0C_07_80046278(rec->unk34, rec->unk36, rec->unk38, rec->unk3A, rec->unk3E, 0x11);
        }
        if (rec->unk44 & 2) {
            player->unk6C = 0;
        }
        func_ovl0C_07_80045548(rec, obj);
        if (obj->unk6C == 0 && obj->unk68 == 0) {
            func_ovl0C_07_80046278(rec->unk34, rec->unk36, rec->unk38, rec->unk3A, rec->unk3E, 0x11);
            if (rec->unk44 & 2) {
                func_ovl0C_07_80046DD0();
                rec->unk44 &= ~2;
                func_ovl0C_07_800448A4(player);
                func_ovl0C_07_80046428(0);
            }
        }
        if (rec->unk20 < obj->unk40->unk14) {
            func_ovl0C_07_80046278(rec->unk34, rec->unk3C, rec->unk38, rec->unk3A, rec->unk3E, 0x11);
            func_ovl0C_07_80046DD0();
            if (rec->unk44 & 2) {
                func_ovl0C_07_800454AC(rec, obj, player);
            }
            func_ovl0C_07_80046DA8(60);
            obj->unk40->unk14 = rec->unk20;
            obj->unk6C = 0.0f;
            obj->unk68 = 0.0f;
            player->unk6C = 0.0f;
            player->unk68 = 0.0f;
            func_ovl0C_07_80046278(rec->unk34, rec->unk3C, rec->unk38, rec->unk3A, rec->unk3E, 0x10);
        }
        func_ovl0C_07_80046DD0();
    }
}

void func_ovl0C_07_80045548(UnkStruct_ovl0C_07_800476D0 *arg0, UnkStructA *arg1) {
    UnkStructA *player;

    if (arg1->unk68 != 0.0f && func_ovl0C_07_80046BE8(arg1, 1) != 0) {
        player = func_ovl0C_07_80046478(0);
        if (arg0->unk14 + 100.0f <= player->unk40->unk14 &&
            player->unk40->unk10 < arg0->unk10 + 100.0f && arg0->unk10 - 100.0f < player->unk40->unk10 &&
            player->unk40->unk18 < arg0->unk18 + 100.0f && arg0->unk18 - 100.0f < player->unk40->unk18) {
            func_ovl0C_07_80046428(1);
            func_ovl0C_07_80046C18(arg1, player);
            func_ovl0C_07_80046C38(player, 0x200000);
            player->unk4C = player->unk40->unk10 - arg0->unk10;
            player->unk50 = 100.0f;
            player->unk54 = player->unk40->unk18 - arg0->unk18;
            arg0->unk44 |= 2;
        }
    }
}

void func_ovl0C_07_800454AC(UnkStruct_ovl0C_07_800476D0 *arg0, UnkStructA *arg1, UnkStructA *arg2) {
    f32 pos[3];

    arg0->unk44 &= ~2;
    pos[0] = arg2->unk40->unk10;
    pos[1] = arg2->unk40->unk14;
    pos[2] = arg2->unk40->unk18;
    func_ovl0C_07_80047228(pos);
    func_ovl0C_07_800472F8();
    func_ovl0C_07_800448A4(arg2);
    func_ovl0C_07_80046DD0();
    func_ovl0C_07_80046428(0);
}

/* func_ovl0C_07_80044D40's body, written out where the mover drops its
 * object: the mover's frame has no room for its parameters (as in
 * ovl_0C_09) */
#define UNK_MACRO_ovl0C_07_80044D40(flag, a, b, f)                             \
    fl = (flag);                                                               \
    if (fl & 1) {                                                              \
        func_ovl0C_07_80047310(0x4C);                                          \
        func_ovl0C_07_80046C18(a, b);                                          \
        func_ovl0C_07_80046C38(b, 0x200000);                                   \
        (b)->unk4C = 0.0f;                                                     \
        (b)->unk50 = f;                                                        \
        (b)->unk54 = 0.0f;                                                     \
    } else {                                                                   \
        func_ovl0C_07_80047310(0x4C);                                          \
        func_ovl0C_07_80046C10(b);                                             \
        func_ovl0C_07_80046C40(b, 0x200000);                                   \
    }

/* a mover on x and z: carries D_ovl0C_07_80047608[rec->unk0]'s object
 * across, then drops it */
void func_ovl0C_07_80044DC8(void) {
    UnkStruct_ovl0C_07_80047648 *rec;
    UnkStructA *obj;
    UnkStructA *other;
    UnkStruct_ovl0C_07_80047608 *lim;
    s16 done;
    f32 dist;
    s32 fl;

    rec = func_ovl0C_07_80046DB0();
    obj = rec->unk4;
    obj->unk68 = rec->unk18;
    obj->unk70 = rec->unk1C;
    lim = &D_ovl0C_07_80047608[rec->unk0];
    other = lim->unk0;
    done = FALSE;
    func_ovl0C_07_80046480(1);
    func_ovl0C_07_80047330(0x48, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
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
        func_ovl0C_07_80046DD0();
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
                        UNK_MACRO_ovl0C_07_80044D40(rec->unk20, obj, other, dist);
                    }
                } else if (obj->unk40->unk10 < lim->unk18) {
                    done = TRUE;
                    UNK_MACRO_ovl0C_07_80044D40(rec->unk20, obj, other, dist);
                }
            }
            if (rec->unk14 != 0) {
                if (rec->unk14 > 0) {
                    if (lim->unk1C < obj->unk40->unk18) {
                        done = TRUE;
                        UNK_MACRO_ovl0C_07_80044D40(rec->unk20, obj, other, dist);
                    }
                } else if (obj->unk40->unk18 < lim->unk1C) {
                    done = TRUE;
                    UNK_MACRO_ovl0C_07_80044D40(rec->unk20, obj, other, dist);
                }
            }
        }
        func_ovl0C_07_80046DD0();
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
            func_ovl0C_07_80046428(0);
            func_ovl0C_07_80047000(rec->unk24);
            if (func_ovl0C_07_80047010(0x431) == 0) {
                func_ovl0C_07_80046330(rec->unk8, rec->unkC, 0);
            } else {
                func_ovl0C_07_80047488();
            }
            func_ovl0C_07_80046D98();
        }
        obj->unk40->unk10 += rec->unk10;
        obj->unk40->unk18 += rec->unk14;
        func_ovl0C_07_80046DD0();
    }
}

void func_ovl0C_07_80044D40(s32 arg0, UnkStructA *arg1, UnkStructA *arg2, f32 arg3) {
    if (arg0 & 1) {
        func_ovl0C_07_80047310(0x4C);
        func_ovl0C_07_800432F0(arg1, arg2, arg3);
    } else {
        func_ovl0C_07_80047310(0x4C);
        func_ovl0C_07_800448A4(arg2);
    }
}

void func_ovl0C_07_80044CE0(void) {
    UnkStructA *obj;

    obj = *(UnkStructA **) func_ovl0C_07_80046DB0();
    obj->unk68 = 0.0f;
    obj->unk70 = 1.6333334f;
    while (TRUE) {
        func_ovl0C_07_80046CB8(obj);
        func_ovl0C_07_80046DD0();
    }
}

void func_ovl0C_07_80044B48(void) {
    UnkStruct_ovl0C_07_80047590 *rec;
    UnkStructA_40 *p;

    rec = func_ovl0C_07_80046DB0();
    p = rec->unk4->unk40;
    D_ovl0C_07_800479A8[rec->unk0]->unkC = 0x40;
    while (TRUE) {
        if (D_ovl0C_07_800479A8[rec->unk0]->unk10 & 0x40) {
            func_ovl0C_07_80047000(0x429);
            func_ovl0C_07_80047310(0x53);
            p->unk48->unk4->unk4 = func_ovl0C_07_80046978(p, 0) - 0.01f;
            while (p->unk48->unk4->unk4 > 1.0f) {
                func_ovl0C_07_80046DD0();
                p->unk48->unk4->unk4 -= 1.0f;
            }
            p->unk48->unk4->unk4 = 0.0f;
            func_ovl0C_07_80043820(rec);
            func_ovl0C_07_80046D98();
        }
        func_ovl0C_07_80046DD0();
    }
}

void func_ovl0C_07_800448D0(void) {
    UnkStructA *obj;
    UnkStructA *lift;
    s32 snd;
    s32 vol;

    func_ovl0C_07_800463A8(1);
    func_ovl0C_07_800463A0(0);
    func_ovl0C_07_80046428(1);
    func_ovl0C_07_80043280(&D_ovl0C_07_80047608[0]);
    obj = D_ovl0C_07_80047648[0].unk4;
    snd = func_ovl0C_07_80047310(0x4E);
    while (obj->unk40->unk10 < 3350.0f) {
        obj->unk40->unk10 += 10.0f;
        func_ovl0C_07_80046A78(obj->unk40->unk10, 1200.0f, 1850.0f);
        func_ovl0C_07_80046DD0();
    }
    obj->unk40->unk10 = 3350.0f;
    D_ovl0C_07_80047608[0].unk0->unk6C = 0.0f;
    func_ovl0C_07_80047310(0x4C);
    func_ovl0C_07_800448A4(D_ovl0C_07_80047608[0].unk0);
    for (vol = 0x7F; obj->unk40->unk10 < 4000.0f;) {
        obj->unk40->unk10 += 10.0f;
        obj->unk40->unk14 += 5.0f;
        if (vol > 0) {
            vol -= 3;
            func_ovl0C_07_80047348(snd, vol);
        } else {
            func_ovl0C_07_80047348(snd, 0);
        }
        func_ovl0C_07_80046DD0();
    }
    func_ovl0C_07_80047340(snd);
    func_ovl0C_07_80047000(D_ovl0C_07_80047648[0].unk24);
    func_ovl0C_07_80046330(D_ovl0C_07_80047648[0].unk8, D_ovl0C_07_80047648[0].unkC, 0);
    while (TRUE) {
        func_ovl0C_07_80046DD0();
    }
}

void func_ovl0C_07_800448A4(UnkStructA *arg0) {
    func_ovl0C_07_80046C10(arg0);
    func_ovl0C_07_80046C40(arg0, 0x200000);
}

void func_ovl0C_07_80044800(void) {
    func_ovl0C_07_800463A0(0);
    func_ovl0C_07_80047208(func_ovl0C_07_80046418(), 2);
    func_ovl0C_07_80047210(func_ovl0C_07_80046418(), 8);
    func_ovl0C_07_80046440("WM1 WG1 WAP WSH WDE WB7 ST1 WDNE WB2 ST1 WDE WB1 ST1 WDNE WB0 ST1");
    func_ovl0C_07_80046440("WM1 WG1 WAP WSH M0 ST10 M0 ST30 WDE WB2 ST1 WDNE WB2 ST1 WDE WB0 ST1");
    func_ovl0C_07_80046440("WM1 WG1 WSH ST1");
    func_ovl0C_07_80046460(0x800);
    func_ovl0C_07_80046440("WM1 WG1 WAP WSH ST30 WDE WB12 ST1 WDSE WB2 ST1 WDS WB2 ST1");
    func_ovl0C_07_80046440("WM1 WG1 WAP WSH ST1");
    func_ovl0C_07_80046D98();
}

void func_ovl0C_07_800447AC(void) {
    func_ovl0C_07_80044178();
    func_ovl0C_07_800463F0(0xE, 0, 0x16);
    func_ovl0C_07_80043CF0(1, 0x40, 0x40, 0.0f, 0);
}

void func_ovl0C_07_800445B4(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0C_07_80044594();
            break;
        case 0x11:
            func_ovl0C_07_800443AC();
            break;
        case 0x12:
            func_ovl0C_07_800444C0();
            break;
        case 0x13:
            func_ovl0C_07_80044474();
            break;
        case 0x14:
            func_ovl0C_07_8004440C();
            break;
        case 0x15:
            func_ovl0C_07_800443AC();
            break;
        case 4:
            func_ovl0C_07_80043BF8();
            break;
        case 5:
            func_ovl0C_07_80043798();
            break;
        case 0x50:
            func_ovl0C_07_800435E8();
            break;
        case 0x52:
            func_ovl0C_07_80043450();
            break;
        case 0x53:
            break;
        case 3:
            func_ovl0C_07_80043200();
            break;
        case 0xC:
            func_ovl0C_07_80043068();
            break;
        case 1:
            func_ovl0C_07_80043038();
            break;
    }
}

void func_ovl0C_07_80044594(void) {
    func_ovl0C_07_8004455C();
}

void func_ovl0C_07_8004455C(void) {
    func_ovl0C_07_8004451C();
    func_ovl0C_07_80046320(func_ovl0C_07_80045BD0);
    func_ovl0C_07_80046370(func_ovl0C_07_80045B10);
}

void func_ovl0C_07_8004451C(void) {
    func_ovl0C_07_80047008(0x400);
    func_ovl0C_07_80047008(0x401);
    func_ovl0C_07_80047008(0x402);
    func_ovl0C_07_80047008(0x403);
    func_ovl0C_07_80047008(0x404);
}

void func_ovl0C_07_800444C0(void) {
    func_ovl0C_07_80044178();
    func_ovl0C_07_800463F0(1, 1, 0x12);
    func_ovl0C_07_80043CF0(2, 0x40, 0x80, 0.0f, 4);
}

void func_ovl0C_07_80044474(void) {
    func_ovl0C_07_80044178();
    func_ovl0C_07_80043CF0(3, 0x40, 0x80, 0.0f, 4);
}

void func_ovl0C_07_8004440C(void) {
    func_ovl0C_07_80044178();
    func_ovl0C_07_800463F0(0x22, 4, 0x12);
    func_ovl0C_07_80043CF0(4, 0x40, 0x40, 0.0f, 0);
    func_ovl0C_07_80046BA0();
    func_ovl0C_07_800463C0(0x2E, 0x12);
}

void func_ovl0C_07_800443AC(void) {
    func_ovl0C_07_800472B8(0);
    func_ovl0C_07_80044178();
    func_ovl0C_07_800463F0(5, 1, 0x12);
    func_ovl0C_07_80043CF0(5, 0x40, 0x80, 0.0f, 0);
}

void func_ovl0C_07_80044178(void) {
    UnkStruct_ovl0C_07_800477A8 *rec;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0C_07_800470F0(D_ovl0C_07_80047530);
    func_ovl0C_07_80047108(D_ovl0C_07_80047554);
    func_ovl0C_07_80046238(0x248);
    p = D_ovl0C_07_8004756C;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl0C_07_80047298((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0C_07_80046250(0x252);
    func_ovl0C_07_800463E8();
    func_ovl0C_07_80044170();
    func_ovl0C_07_80044024();
    func_ovl0C_07_80043E38();
    rec = &D_ovl0C_07_800477A8;
    rec->unk0 = func_ovl0C_07_80046C80(rec->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0C_07_80046C38(rec->unk0, 0x01080000);
    func_ovl0C_07_80046C40(rec->unk0, 0x02000000);
    if (rec->unkC != -1 && rec->unkE != -1 && rec->unk10 != -1 && rec->unk12 != -1) {
        rec->unk4 = func_ovl0C_07_80046980(rec->unk0->unk40, 0, rec->unkC, rec->unkE, rec->unk10, rec->unk12);
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

static void func_ovl0C_07_80044170(void) {
}

void func_ovl0C_07_80044024(void) {
    UnkStruct_ovl0C_07_800476D0 *p;
    UnkStructA *obj;
    s16 i;

    func_ovl0C_07_80043FDC();
    for (i = 0; i < 3; i++) {
        p = &D_ovl0C_07_800476D0[i];
        obj = func_ovl0C_07_80046C80(0x2AC, 0xD0, p->unk10, p->unk1C, p->unk18);
        func_ovl0C_07_80046C38(obj, 0x01000000);
        p->unk8 = obj;
        p->unk44 = 0;
        obj->unk30 = 4;
        obj->unk34 = 100.0f;
        obj->unk38 = 100.0f;
        func_ovl0C_07_80046278(p->unk34, p->unk36, p->unk38, p->unk3A, p->unk3E, 0x11);
        D_ovl0C_07_800476D0[i].unkC = func_ovl0C_07_80046C60(-1, 0, 0x50, 0);
        D_ovl0C_07_800476D0[i].unkC->unk40->unk10 = D_ovl0C_07_800476D0[i].unk10;
        D_ovl0C_07_800476D0[i].unkC->unk40->unk14 = D_ovl0C_07_800476D0[i].unk1C - 100.0f;
        D_ovl0C_07_800476D0[i].unkC->unk40->unk18 = D_ovl0C_07_800476D0[i].unk18;
    }
}

void func_ovl0C_07_80043FDC(void) {
    if (func_ovl0C_07_80047010(0x400) == 0) {
        D_ovl0C_07_800479A4 = func_ovl0C_07_80046C60(-1, 0, 0x20, 0);
        func_ovl0C_07_80047000(0x400);
    }
}

void func_ovl0C_07_80043E38(void) {
    UnkStruct_ovl0C_07_80047590 *p;
    f32 angle;
    UnkStructA *obj;
    s16 i;

    for (i = 0; i < 1; i++) {
        func_ovl0C_07_80043D7C(i);
        p = &D_ovl0C_07_80047590[i];
        obj = func_ovl0C_07_80046C80(0x2A9, 0xD0, p->unk8, p->unkC, p->unk10);
        func_ovl0C_07_80046C38(obj, 0x01000000);
        switch (p->unk14) {
            case 0:
                angle = 270.0f;
                break;
            case 0x40:
                angle = 180.0f;
                break;
            case 0x80:
                angle = 90.0f;
                break;
            case 0xC0:
                angle = 0.0f;
                break;
        }
        obj->unk40->unk20 = angle;
        p->unk4 = obj;
        func_ovl0C_07_80043D20(p);
    }
}

void func_ovl0C_07_80043D7C(s32 arg0) {
    D_ovl0C_07_800479A8[arg0] = func_ovl0C_07_80046C60(-1, 0, 0x20, 0);
    D_ovl0C_07_800479A8[arg0]->unk40->unk10 = D_ovl0C_07_80047590[arg0].unk18;
    D_ovl0C_07_800479A8[arg0]->unk40->unk14 = D_ovl0C_07_80047590[arg0].unk1C;
    D_ovl0C_07_800479A8[arg0]->unk40->unk18 = D_ovl0C_07_80047590[arg0].unk20;
    D_ovl0C_07_800479A8[arg0]->unk30 = 1;
    D_ovl0C_07_800479A8[arg0]->unk34 = 200.0f;
    D_ovl0C_07_800479A8[arg0]->unk38 = 100.0f;
}

void func_ovl0C_07_80043D20(UnkStruct_ovl0C_07_80047590 *arg0) {
    func_ovl0C_07_80043D18();
    arg0->unk4->unk40->unk48->unk4->unk4 = func_ovl0C_07_80046978(arg0->unk4->unk40, 0) - 0.0001f;
    func_ovl0C_07_800430A8(arg0);
}

static void func_ovl0C_07_80043D18(void) {
}

void func_ovl0C_07_80043CF0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0C_07_80047990.unk0 = arg0;
    D_ovl0C_07_80047990.unk4 = arg1;
    D_ovl0C_07_80047990.unk8 = arg2;
    D_ovl0C_07_80047990.unkC = arg3;
    D_ovl0C_07_80047990.unk10 = arg4;
}

void func_ovl0C_07_80043BF8(void) {
    func_ovl0C_07_80043AC8();
    if (D_ovl0C_07_80047990.unk0 == 3) {
        func_ovl0C_07_80043A28();
    }
    if (D_ovl0C_07_80047990.unk0 == 5) {
        func_ovl0C_07_800439A4();
    }
    if (func_ovl0C_07_80047010(0x43A) != 0 && func_ovl0C_07_80047010(0x439) == 0) {
        func_ovl0C_07_80043920(&D_ovl0C_07_80047608[0]);
        func_ovl0C_07_80043340(&D_ovl0C_07_80047648[0]);
        if (D_ovl0C_07_80047648[0].unk4 != NULL) {
            D_ovl0C_07_80047648[0].unk4->unk40->unk20 = 90.0f;
        }
    }
    if (func_ovl0C_07_80047010(0x439) != 0 && func_ovl0C_07_80047010(0x438) == 0) {
        func_ovl0C_07_80043920(&D_ovl0C_07_80047608[1]);
    }
    if (D_ovl0C_07_80047990.unk0 == 2) {
        func_ovl0C_07_800438E4(D_ovl0C_07_80047590);
    }
}

void func_ovl0C_07_80043AC8(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_07_80046448();
    switch (D_ovl0C_07_80047990.unk8) {
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
        func_ovl0C_07_80046A98(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_07_80047990.unkC;
        func_ovl0C_07_80046AA0(&sp1C, NULL, NULL);
        func_ovl0C_07_80046A98(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_07_80046430(D_ovl0C_07_80047990.unk4);
    func_ovl0C_07_80046B30(45.0f, 45.1f);
}

void func_ovl0C_07_80043A80(f32 arg0) {
    f32 sp1C;

    func_ovl0C_07_80046AA0(&sp1C, NULL, NULL);
    func_ovl0C_07_80046A98(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0C_07_80043A28(void) {
    func_ovl0C_07_80046AE0(0x7F);
    func_ovl0C_07_80046A78(1550.0f, 1200.0f, 1850.0f);
    func_ovl0C_07_80046A98(-90.0f, 45.0f, 2500.0f);
}

void func_ovl0C_07_800439A4(void) {
    func_ovl0C_07_80046A98(225.0f, 32768.0f, 32768.0f);
    func_ovl0C_07_80046AE0(0xF);
    func_ovl0C_07_80046AF0(2);
    func_ovl0C_07_80046428(1);
    func_ovl0C_07_80047000(0x431);
    func_ovl0C_07_80047000(0x43A);
    func_ovl0C_07_80047000(0x439);
    func_ovl0C_07_80046D88(func_ovl0C_07_80044800, NULL, 0, 0, 0x130);
}

void func_ovl0C_07_80043920(UnkStruct_ovl0C_07_80047608 *arg0) {
    UnkStructA *obj;
    UnkStructA *shadow;

    obj = func_ovl0C_07_80046C80(0x2A6, 0xD0, arg0->unk4, arg0->unk10, arg0->unkC);
    shadow = func_ovl0C_07_80046C70(obj);
    shadow->unk54 = 2.0f;
    shadow->unk4C = 2.0f;
    shadow->unk40->unk36 = 0x19;
    func_ovl0C_07_80046C38(obj, 0x0D080000);
    arg0->unk0 = obj;
    arg0->unk8 = arg0->unk10;
}

void func_ovl0C_07_800438E4(UnkStruct_ovl0C_07_80047590 *arg0) {
    arg0->unk4->unk40->unk48->unk4->unk4 = 0.0f;
    func_ovl0C_07_80043820(arg0);
}

void func_ovl0C_07_80043820(UnkStruct_ovl0C_07_80047590 *arg0) {
    func_ovl0C_07_80046280(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk34, arg0->unk38, 0x10);
    func_ovl0C_07_80046278(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk38, 0x11);
    func_ovl0C_07_80046278(arg0->unk3C, arg0->unk40, arg0->unk44, arg0->unk48, arg0->unk4C, 0x12);
    func_ovl0C_07_80046270(arg0->unk50, arg0->unk54, arg0->unk58, arg0->unk60);
    func_ovl0C_07_80046270(arg0->unk64, arg0->unk68, arg0->unk6C, arg0->unk74);
}

void func_ovl0C_07_80043798(void) {
    func_ovl0C_07_80043750();
    func_ovl0C_07_800436D8();
    if (D_ovl0C_07_80047990.unk0 == 3) {
        func_ovl0C_07_800436A0();
    }
    func_ovl0C_07_80043634();
}

void func_ovl0C_07_80043750(void) {
    func_ovl0C_07_80046438(D_ovl0C_07_80047990.unk4, 3, 4.0f, D_ovl0C_07_80047990.unk10, 0, 1, 1);
}

void func_ovl0C_07_800436D8(void) {
    UnkStruct_ovl0C_07_800476D0 *p;
    s16 i;

    for (i = 0, p = D_ovl0C_07_800476D0; i < 3; i++, p++) {
        p->unk4 = func_ovl0C_07_80046D88(func_ovl0C_07_80045694, p, 0, 0, 0x110);
    }
}

void func_ovl0C_07_800436A0(void) {
    func_ovl0C_07_80046D88(func_ovl0C_07_800448D0, NULL, 0, 0, 0x110);
}

void func_ovl0C_07_80043634(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0C_07_80046D88(func_ovl0C_07_80044B48, &D_ovl0C_07_80047590[i], 0, 0, 0x110);
    }
}

void func_ovl0C_07_800435E8(void) {
    if (func_ovl0C_07_80046400(1, 0x12, 1, 0x13) != 0) {
        func_ovl0C_07_8004357C(D_ovl0C_07_80047590);
        func_ovl0C_07_80046330(0x2D, 0x12, 0);
    }
}

void func_ovl0C_07_8004357C(UnkStruct_ovl0C_07_80047590 *arg0) {
    func_ovl0C_07_80046428(1);
    func_ovl0C_07_80047310(0x4B);
    func_ovl0C_07_80046C38(arg0->unk4, 0x04000000);
    func_ovl0C_07_80046DA8(60);
    func_ovl0C_07_80047310(0x46);
    func_ovl0C_07_800430A8(arg0);
    func_ovl0C_07_80047008(0x429);
    func_ovl0C_07_80046DA8(10);
}

void func_ovl0C_07_80043450(void) {
    if (func_ovl0C_07_80047010(0x439) != 0 && func_ovl0C_07_80047010(0x438) == 0) {
        func_ovl0C_07_800463A8(1);
        func_ovl0C_07_800463A0(0);
        func_ovl0C_07_80046B98();
        func_ovl0C_07_80046480(1);
        func_ovl0C_07_80043400();
        func_ovl0C_07_80046438(0xC0, 3, 4.0f, 0, 1, 1, 1);
        func_ovl0C_07_80046DA8(30);
        func_ovl0C_07_80046460(0x04000000);
        func_ovl0C_07_80043340(&D_ovl0C_07_80047648[1]);
        func_ovl0C_07_800432B8(&D_ovl0C_07_80047648[1]);
        func_ovl0C_07_80043280(&D_ovl0C_07_80047608[1]);
        func_ovl0C_07_80046DA8(90);
        func_ovl0C_07_80046428(1);
        func_ovl0C_07_80046438(0x60, 3, 4.0f, 0, 1, 1, 1);
    }
}

void func_ovl0C_07_80043400(void) {
    func_ovl0C_07_80046AE0(0x7F);
    func_ovl0C_07_80046A78(3300.0f, 1000.0f, 1800.0f);
    func_ovl0C_07_80046A98(-90.0f, 45.0f, 1800.0f);
}

void func_ovl0C_07_80043340(UnkStruct_ovl0C_07_80047648 *arg0) {
    UnkStructA *obj;
    UnkStructA *other;
    UnkStruct_ovl0C_07_80047608 *lim;

    obj = func_ovl0C_07_80046C80(0x2B2, 0xD0, arg0->unk28, arg0->unk2C, arg0->unk30);
    func_ovl0C_07_80046C70(obj);
    func_ovl0C_07_80046C38(obj, 0x0D000000);
    lim = &D_ovl0C_07_80047608[arg0->unk0];
    arg0->unk4 = obj;
    other = lim->unk0;
    if (arg0->unk20 & 2) {
        func_ovl0C_07_800432F0(obj, other, lim->unk14);
    }
}

void func_ovl0C_07_800432F0(UnkStructA *arg0, UnkStructA *arg1, f32 arg2) {
    func_ovl0C_07_80046C18(arg0, arg1);
    func_ovl0C_07_80046C38(arg1, 0x200000);
    arg1->unk4C = 0.0f;
    arg1->unk50 = arg2;
    arg1->unk54 = 0.0f;
}

void func_ovl0C_07_800432B8(void *arg0) {
    func_ovl0C_07_80046D88(func_ovl0C_07_80044DC8, arg0, 0, 0, 0x110);
}

void func_ovl0C_07_80043280(void *arg0) {
    func_ovl0C_07_80043278();
    func_ovl0C_07_80046D88(func_ovl0C_07_80044CE0, arg0, 0, 0, 0x110);
}

static void func_ovl0C_07_80043278(void) {
}

void func_ovl0C_07_80043200(void) {
    UNK_MACRO_ovl0C_07_800431B8();
    if (func_ovl0C_07_80047010(0x404) == 0 && D_ovl0C_07_80047990.unk0 == 2) {
        func_ovl0C_07_80043134(D_ovl0C_07_80047590);
    }
    func_ovl0C_07_80047000(0x404);
}

void func_ovl0C_07_800431B8(void) {
    func_ovl0C_07_800431B0();
    D_ovl0C_07_8004796C = func_ovl0C_07_80046418();
    func_ovl0C_07_800463F8(&D_ovl0C_07_80047960);
    func_ovl0C_07_80046420(D_ovl0C_07_8004796C, D_ovl0C_07_80047950);
}

static void func_ovl0C_07_800431B0(void) {
}

void func_ovl0C_07_80043134(UnkStruct_ovl0C_07_80047590 *arg0) {
    func_ovl0C_07_80046428(1);
    func_ovl0C_07_80046DA8(90);
    func_ovl0C_07_80047310(0x4B);
    func_ovl0C_07_80046C38(arg0->unk4, 0x04000000);
    func_ovl0C_07_80046DA8(60);
    func_ovl0C_07_80047310(0x46);
    func_ovl0C_07_80046DA8(10);
    func_ovl0C_07_800430A8(arg0);
    func_ovl0C_07_80047008(0x429);
    func_ovl0C_07_80046428(0);
}

void func_ovl0C_07_800430A8(UnkStruct_ovl0C_07_80047590 *arg0) {
    func_ovl0C_07_80046280(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk34, arg0->unk38, 0x1F);
    func_ovl0C_07_80046270(arg0->unk50, arg0->unk54, arg0->unk58, arg0->unk5C);
    func_ovl0C_07_80046270(arg0->unk64, arg0->unk68, arg0->unk6C, arg0->unk70);
}

void func_ovl0C_07_80043088(void) {
    func_ovl0C_07_80046480(1);
}

void func_ovl0C_07_80043068(void) {
    func_ovl0C_07_80046480(1);
}

void func_ovl0C_07_80043038(void) {
    if (D_ovl0C_07_80047990.unk0 == 5) {
        func_ovl0C_07_80047490();
    }
}

void func_ovl0C_07_80043018(void) {
    func_ovl0C_07_80047490();
}

void func_ovl0C_07_80043010(void) {
}
