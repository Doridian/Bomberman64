/*
 * NON_MATCHING: ovl_12_01's game object, complete: every function and its data.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 29, eu 29, jp 29
 *
 * The text is the original's size and order, and .data/.rodata/.bss
 * build to the original's bytes (0x120, 0x170, 0x60). What still differs
 * (words; the same in all three), both as in ovl_12_03's draft:
 * - func_ovl12_01_80043190 (27): the inlined func_ovl12_01_80043188 is
 *   scheduled differently: the original saves s1/s2 and sets the count
 *   before computing x, stores y before x, and stores the result of
 *   func_ovl12_01_80045EE0 before the epilogue; ours puts that store in
 *   the epilogue. The copies inlined into func_ovl12_01_80043468 and
 *   func_ovl12_01_800441AC match. Parameter order, statement order and a
 *   body with locals in place of the static don't help.
 * - func_ovl12_01_80043754 (2): the `lui a0` of D_ovl12_01_800464E0 is
 *   scheduled before `sw ra`; the original has it after (one or two empty
 *   statics, a static holding the calls, a local copy: no change).
 * The entry (ovl_12_01_entry, `return func_ovl12_01_80044350;`) goes to
 * src/ with it.
 */
#include "common.h"

/*
 * ovl_12_01's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Its code is ovl_12_03's
 * (nonmatching/overlays/ovl_12_03/250B70.c) with other set pieces.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl12_01_80046500;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
} UnkStruct_ovl12_01_80046290;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
} UnkStruct_ovl12_01_800462F0;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl12_01_80046318;

/* an object and where it is made */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl12_01_8004632C;

void func_ovl12_01_80044F38(s32);
void func_ovl12_01_80044F50(s32);
void func_ovl12_01_80044F78(s32, s32, s32, s32, s32, s32);
void func_ovl12_01_80044F80(s32, s32, s32, s32, s32, s32, s32);
s32 func_ovl12_01_80044FA0(s32);
void func_ovl12_01_80044FC0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl12_01_80045020(void (*)(UnkStructA *));
void func_ovl12_01_80045030(s32, s32, s32);
void func_ovl12_01_80045058(void);
void func_ovl12_01_80045070(void (*)(UnkStructA *));
void func_ovl12_01_800450A0(s32);
void func_ovl12_01_800450E8(void);
void func_ovl12_01_800450F0(s32, s32, s32);
void func_ovl12_01_800450F8(void *);
s32 func_ovl12_01_80045100(s32, s32, s32, s32);
s32 func_ovl12_01_80045118(void);
void func_ovl12_01_80045120(s32, void *);
void func_ovl12_01_80045128(s32);
void func_ovl12_01_80045130(s32);
void func_ovl12_01_80045138(s32, s32, f32, s32, s32, s32, s32);
void func_ovl12_01_80045140(const char *);
void func_ovl12_01_80045148(void);
void func_ovl12_01_80045160(s32);
void func_ovl12_01_80045180(s32);
void func_ovl12_01_800451D0(s32);
void func_ovl12_01_800451E8(void);
void func_ovl12_01_80045640(UnkStructA_40 *, s32);
void func_ovl12_01_80045648(UnkStructA_40 *, s32, s32, s32);
f32 func_ovl12_01_80045678(UnkStructA_40 *, s32);
void func_ovl12_01_80045778(f32, f32, f32);
void func_ovl12_01_80045798(f32, f32, f32);
void func_ovl12_01_800457A0(f32 *, f32 *, f32 *);
void func_ovl12_01_800457D8(s32);
void func_ovl12_01_800457E0(s32);
void func_ovl12_01_800457F0(s32);
void func_ovl12_01_80045868(void *);
void func_ovl12_01_80045898(void);
void func_ovl12_01_800458A0(void);
void func_ovl12_01_80045938(UnkStructA *, s32);
void func_ovl12_01_80045940(UnkStructA *, s32);
void func_ovl12_01_80045950(UnkStructA *);
UnkStructA *func_ovl12_01_80045980(s32, s32, f32, f32, f32);
void func_ovl12_01_800459B8(UnkStructA *);
void func_ovl12_01_80045A88(void (*)(void), s32, s32, s32, s32);
void func_ovl12_01_80045A98(void);
void func_ovl12_01_80045AA8(s32);
void func_ovl12_01_80045AD0(void);
UnkStructA *func_ovl12_01_80045B10(s32);
void func_ovl12_01_80045B20(UnkStructA *, s32);
void func_ovl12_01_80045D00(s32);
void func_ovl12_01_80045D08(s32);
s32 func_ovl12_01_80045D10(s32);
void func_ovl12_01_80045DB0(s32, s32, s32);
void func_ovl12_01_80045DF0(u32 (*)[3]);
void func_ovl12_01_80045E08(u32 (*)[3]);
s32 func_ovl12_01_80045EE0(s32, Vec3f *, s32);
void func_ovl12_01_80045EE8(s32);
void func_ovl12_01_80045F08(s16, s32);
void func_ovl12_01_80045F10(s16, s32);
void func_ovl12_01_80045F98(s32, s32, s32);
void func_ovl12_01_80046010(s32);
void func_ovl12_01_80046030(s32, f32, f32, f32);
void func_ovl12_01_80046188(void);
void func_ovl12_01_80046190(void);

void func_ovl12_01_80043010(void);
void func_ovl12_01_80043018(void);
void func_ovl12_01_80043038(void);
void func_ovl12_01_80043058(void);
void func_ovl12_01_800430A8(void);
void func_ovl12_01_800430C8(void);
void func_ovl12_01_800430F0(void);
void func_ovl12_01_80043138(void);
void func_ovl12_01_80043190(void);
void func_ovl12_01_80043264(void);
void func_ovl12_01_800432A0(UnkStruct_ovl12_01_80046290 *);
void func_ovl12_01_80043324(UnkStruct_ovl12_01_80046290 *);
void func_ovl12_01_8004336C(void);
void func_ovl12_01_800433A4(void);
void func_ovl12_01_800433DC(void);
void func_ovl12_01_80043468(void);
void func_ovl12_01_800436F8(void);
void func_ovl12_01_80043754(void);
void func_ovl12_01_80043784(void);
void func_ovl12_01_80043850(void);
void func_ovl12_01_80043910(void);
void func_ovl12_01_80043958(void);
void func_ovl12_01_80043978(void);
void func_ovl12_01_800439E4(void);
void func_ovl12_01_80043A44(f32);
void func_ovl12_01_80043A8C(void);
void func_ovl12_01_80043BA4(void);
void func_ovl12_01_80043C00(s32, s32, s32, f32, s32);
void func_ovl12_01_80043C28(void);
void func_ovl12_01_80043C78(void);
void func_ovl12_01_80043CC8(void);
void func_ovl12_01_80043D18(void);
void func_ovl12_01_80043D64(void);
void func_ovl12_01_80043DAC(void);
void func_ovl12_01_80043E60(void);
void func_ovl12_01_80043EC4(void);
void func_ovl12_01_80043FF4(void);
void func_ovl12_01_800440F8(void);
void func_ovl12_01_80044100(void);
void func_ovl12_01_80044140(void);
void func_ovl12_01_800441AC(void);
void func_ovl12_01_80044350(s32);
void func_ovl12_01_80044530(void);
void func_ovl12_01_80044644(void);
void func_ovl12_01_800447D4(UnkStructA *);
void func_ovl12_01_800447EC(void);
void func_ovl12_01_80044830(void);
void func_ovl12_01_8004490C(void);
void func_ovl12_01_800449CC(UnkStructA *);
void func_ovl12_01_80044A8C(UnkStructA *);
void func_ovl12_01_80044B04(s32, UnkStructA *);
void func_ovl12_01_80044B38(f32, f32, f32);
void func_ovl12_01_80044B94(void);
void func_ovl12_01_80044BAC(void);

/* statics inlined everywhere: each leaves a `jr ra; nop` just before its
 * first caller */
static void func_ovl12_01_800430E8(void);
static void func_ovl12_01_80043180(void);
static void func_ovl12_01_80043188(f32, s32, s32);
static void func_ovl12_01_8004374C(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl12_01_80043138() \
    D_ovl12_01_800464DC = func_ovl12_01_80045118(); func_ovl12_01_800450F8(&D_ovl12_01_800464D0); func_ovl12_01_80045120(D_ovl12_01_800464DC, D_ovl12_01_800464C0)

/* .bss */
u8 D_ovl12_01_800464C0[0x10];
Vec3f D_ovl12_01_800464D0;
s32 D_ovl12_01_800464DC;
s32 D_ovl12_01_800464E0;
s32 D_ovl12_01_800464E4;
s32 D_ovl12_01_800464E8[2]; /* the second word unused */
/* a position (func_ovl12_01_80043188, func_ovl12_01_80044B38); the last
 * word unused */
f32 D_ovl12_01_800464F0[4];
UnkStruct_ovl12_01_80046500 D_ovl12_01_80046500;

/* .data */
/* passed to func_ovl12_01_80045DF0: three 12-byte records */
u32 D_ovl12_01_80046230[][3] = {
    { 0x970001, 0xF, 4 },
    { 0xCF0001, 0xE, 4 },
    { 0xD00003, 0xF, 4 },
};
/* passed to func_ovl12_01_80045E08: two 12-byte records */
u32 D_ovl12_01_80046254[][3] = {
    { 0x980000, 0x84, 0 },
    { 4, 0, 4 },
};
/* three 12-byte records, each passed to func_ovl12_01_80045F98 */
u32 D_ovl12_01_8004626C[][3] = {
    { 0, 0x21, 0xFF },
    { 1, 0x1F, 0xFD },
    { 2, 0x20, 0xFE },
};
UnkStruct_ovl12_01_80046290 D_ovl12_01_80046290[] = {
    { NULL, 4200.0f, 0.0f, 1900.0f, 0x2A, 2, 0, 0x13, 0x2B, 0, 0, 0x13 },
    { NULL, 4200.0f, 400.0f, 2300.0f, 0x2A, 4, 2, 0x17, 0x2B, 2, 0, 0x17 },
    { NULL, 4100.0f, 200.0f, 2500.0f, 0x29, 3, 1, 0x19, 0x2A, 1, 0, 0x19 },
};
UnkStruct_ovl12_01_800462F0 D_ovl12_01_800462F0[] = {
    { NULL, 3900.0f, 0.0f, 1500.0f, 4200.0f, 0.0f, 1500.0f, 0x27, 0, 0xF, 0x28, 0x10 },
};
UnkStruct_ovl12_01_80046318 D_ovl12_01_80046318 = { NULL, 2350.0f, 602.0f, 1550.0f, 0x409 };
UnkStruct_ovl12_01_8004632C D_ovl12_01_8004632C = { NULL, 4500.0f, 450.0f, 1550.0f };
UnkStruct_ovl12_01_8004632C D_ovl12_01_8004633C = { NULL, 3700.0f, 0.0f, 600.0f };

/* unused: the stubs IDO -O3 leaves at the end of the object. IDO drops
 * an unused static's body but counts the addresses it takes: with
 * func_ovl12_01_800447D4 and func_ovl12_01_800447EC address-taken they
 * come out among the tasks and callbacks (after the handler, in address
 * order), as in the original; unreferenced, they come out after
 * func_ovl12_01_80044A8C. Which stub takes them and how is a guess. */
static void func_ovl12_01_80044BE4(void) {
    func_ovl12_01_80045070(func_ovl12_01_800447D4);
    func_ovl12_01_80045A88(func_ovl12_01_800447EC, 0, 0, 0, 0);
}

static void func_ovl12_01_80044BDC(void) {
}

static void func_ovl12_01_80044BD4(void) {
}

static void func_ovl12_01_80044BCC(void) {
}

static void func_ovl12_01_80044BC4(void) {
}

static void func_ovl12_01_80044BBC(void) {
}

static void func_ovl12_01_80044BB4(void) {
}

void func_ovl12_01_80044BAC(void) {
}

void func_ovl12_01_80044B94(void) {
    D_ovl12_01_800464E4 = -1;
    D_ovl12_01_800464E8[0] = -1;
}

void func_ovl12_01_80044B38(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl12_01_80045778(D_ovl12_01_800464F0[0], D_ovl12_01_800464F0[1], D_ovl12_01_800464F0[2]);
    func_ovl12_01_80045798(arg0, arg1, arg2);
    func_ovl12_01_80045AA8(180);
}

void func_ovl12_01_80044B04(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl12_01_80046030(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl12_01_80044A8C(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl12_01_800457E0(0x10);
    }
    func_ovl12_01_80045940(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        func_ovl12_01_800459B8(arg0);
        func_ovl12_01_80045AD0();
    }
}

void func_ovl12_01_800449CC(UnkStructA *arg0) {
    func_ovl12_01_80045AA8(10);
    func_ovl12_01_80044FC0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl12_01_80045AA8(60);
}

/* a task (func_ovl12_01_800433A4): moves D_ovl12_01_800462F0[0]'s object
 * along x for 120 frames */
void func_ovl12_01_8004490C(void) {
    s16 i;

    for (i = 0; i < 120; i++) {
        D_ovl12_01_800462F0[0].unk0->unk40->unk10 -= 2.5f;
        func_ovl12_01_80045AD0();
    }
    func_ovl12_01_80044F78(D_ovl12_01_800462F0[0].unk1C, D_ovl12_01_800462F0[0].unk1E, D_ovl12_01_800462F0[0].unk20,
                           D_ovl12_01_800462F0[0].unk22, D_ovl12_01_800462F0[0].unk24, 0x11);
    func_ovl12_01_80045A98();
    while (TRUE) {
        func_ovl12_01_80045AD0();
    }
}

/* a task (func_ovl12_01_8004336C): scales D_ovl12_01_8004632C's object
 * down to nothing. The stores after the loop are of an int 0: with 0.0f
 * IDO reuses the loop's 0.0f register for them. */
void func_ovl12_01_80044830(void) {
    UnkStructA *obj;
    f32 s;

    obj = D_ovl12_01_8004632C.unk0;
    for (s = 1.0f; s > 0.0f; s -= 0.04f) {
        obj->unk40->unk28 = s;
        obj->unk40->unk2C = s;
        obj->unk40->unk30 = s;
        func_ovl12_01_80045AD0();
    }
    obj->unk40->unk28 = 0;
    obj->unk40->unk2C = 0;
    obj->unk40->unk30 = 0;
    func_ovl12_01_80045940(obj, 0x01000000);
    func_ovl12_01_80045A98();
}

void func_ovl12_01_800447EC(void) {
    func_ovl12_01_80044F80(6, 0, 0xF, 8, 1, 0x10, 0x1410);
}

void func_ovl12_01_800447D4(UnkStructA *arg0) {
    arg0->unk68 = 10.0f;
    arg0->unk6C = 0.0f;
}

/* a task (func_ovl12_01_800439E4): the camera moves. The counters count down (`i = 0; i < 121;
 * i++` keeps a second counter in s1). */
void func_ovl12_01_80044644(void) {
    s32 i;
    f32 z;
    f32 a;

    func_ovl12_01_800450A0(0);
    func_ovl12_01_80045140("WM1 WG1 WAP WSH ST1");
    for (i = 121, z = 2000.0f; i != 0; i--) {
        func_ovl12_01_80045798(32768.0f, 32768.0f, z);
        func_ovl12_01_80045AD0();
        z += 8.333333f;
    }
    for (i = 121, z = 3000.0f, a = 345.0f; i != 0; i--) {
        func_ovl12_01_80045798(32768.0f, a, z);
        func_ovl12_01_80045AD0();
        z += 8.333333f;
        a += 0.29166666f;
    }
    for (i = 241, z = 4000.0f, a = 270.0f; i != 0; i--) {
        func_ovl12_01_80045798(a, 32768.0f, z);
        func_ovl12_01_80045AD0();
        z += 8.333333f;
        a += 0.083333336f;
    }
    for (i = 241, z = 6000.0f; i != 0; i--) {
        func_ovl12_01_80045798(32768.0f, 32768.0f, z);
        func_ovl12_01_80045AD0();
        z += 8.333333f;
    }
    func_ovl12_01_80045AA8(30);
    func_ovl12_01_80046188();
    func_ovl12_01_80045A98();
}

/* a task (func_ovl12_01_80043978): the messages */
void func_ovl12_01_80044530(void) {
    func_ovl12_01_800450A0(0);
    func_ovl12_01_80045F08(func_ovl12_01_80045118(), 2);
    func_ovl12_01_80045F10(func_ovl12_01_80045118(), 8);
    func_ovl12_01_80045140("WM1 WG1 WAP WSH M0 ST10 M0 ST1");
    func_ovl12_01_80045AA8(35);
    func_ovl12_01_80045160(0x4000);
    func_ovl12_01_80045140("WM1 WG1 WAP WSH M1 ST10");
    func_ovl12_01_800451D0(1);
    func_ovl12_01_80045160(0x400);
    func_ovl12_01_80045140("WM1 WG1 WAP WSH ST60 M2 ST10");
    func_ovl12_01_80045140("WM1 WG1 WAP WSH M0 ST10 M0 ST1");
    func_ovl12_01_80045AA8(21);
    func_ovl12_01_80045160(0x4000);
    func_ovl12_01_80045140("WM1 WG1 WAP WSH M0 ST10 M0 ST1");
    func_ovl12_01_80045AA8(24);
    func_ovl12_01_80045160(0x4000);
    func_ovl12_01_80045140("WM1 WG1 WAP WSH M0 ST10 M0 ST1");
    func_ovl12_01_80045AA8(14);
    func_ovl12_01_80045160(0x4000);
    func_ovl12_01_80045140("WM1 WG1 WAP WSH ST20 WDS WB1");
    func_ovl12_01_80045AA8(180);
    func_ovl12_01_80046188();
    func_ovl12_01_80045A98();
}

void func_ovl12_01_80044140(void) {
    UnkStructA *obj;

    func_ovl12_01_80044100();
    func_ovl12_01_80045020(func_ovl12_01_80044A8C);
    func_ovl12_01_80045070(func_ovl12_01_800449CC);
    obj = func_ovl12_01_80045B10(0x2E5);
    func_ovl12_01_80045B20(obj, 0x20000001);
    obj->unk18 = 0.03f;
    obj->unk1C = 0.0f;
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl12_01_80044350(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl12_01_800441AC();
            break;
        case 16:
            func_ovl12_01_80043D64();
            break;
        case 17:
            func_ovl12_01_80043D18();
            break;
        case 18:
            func_ovl12_01_80043CC8();
            break;
        case 19:
            func_ovl12_01_80043C78();
            break;
        case 20:
            func_ovl12_01_80043C28();
            break;
        case 4:
            func_ovl12_01_80043BA4();
            break;
        case 5:
            func_ovl12_01_80043910();
            break;
        case 0x50:
            func_ovl12_01_80043850();
            break;
        case 0x52:
            func_ovl12_01_800436F8();
            break;
        case 3:
            UNK_MACRO_ovl12_01_80043138();
            break;
        case 12:
            func_ovl12_01_80045180(1);
            break;
        case 1:
            func_ovl12_01_80043058();
            break;
        case 0x53:
            break;
    }
}

void func_ovl12_01_800441AC(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl12_01_80044140();
    func_ovl12_01_80045DF0(D_ovl12_01_80046230);
    func_ovl12_01_80045E08(D_ovl12_01_80046254);
    func_ovl12_01_80044F38(0x2D9);
    p = D_ovl12_01_8004626C;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl12_01_80045F98((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl12_01_80044F50(0x2DF);
    func_ovl12_01_800450E8();
    func_ovl12_01_80043FF4();
    func_ovl12_01_80043EC4();
    if (func_ovl12_01_80045D10(0x409)) {
        func_ovl12_01_80043264();
        func_ovl12_01_80043190();
    }
    func_ovl12_01_800433DC();
    func_ovl12_01_80043E60();
    func_ovl12_01_80043DAC();
    func_ovl12_01_80045DB0(0, 0x72, 0x37);
}

void func_ovl12_01_80044100(void) {
    func_ovl12_01_80045D08(0x400);
    func_ovl12_01_80045D08(0x401);
    func_ovl12_01_80045D08(0x402);
    func_ovl12_01_80045D08(0x403);
    func_ovl12_01_80045D08(0x404);
}

void func_ovl12_01_800440F8(void) {
}

void func_ovl12_01_80043FF4(void) {
    s16 i;
    UnkStruct_ovl12_01_80046290 *p;
    UnkStructA *obj;

    for (i = 0; i < 3; i++) {
        p = &D_ovl12_01_80046290[i];
        obj = func_ovl12_01_80045980(0x316, 0xD0, p->unk4, p->unk8, p->unkC);
        func_ovl12_01_80045938(obj, 0x01000000);
        p->unk0 = obj;
        if (func_ovl12_01_80045D10(0x409)) {
            p->unk0->unk40->unk48->unk4->unk4 = func_ovl12_01_80045678(p->unk0->unk40, 0) - 0.001f;
            func_ovl12_01_80043324(p);
            func_ovl12_01_800432A0(p);
        }
    }
}

void func_ovl12_01_80043EC4(void) {
    s16 i;
    UnkStructA *obj;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < 1; i++) {
        if (func_ovl12_01_80045D10(0x409)) {
            x = D_ovl12_01_800462F0[i].unk4;
            y = D_ovl12_01_800462F0[i].unk8;
            z = D_ovl12_01_800462F0[i].unkC;
        } else {
            x = D_ovl12_01_800462F0[i].unk10;
            y = D_ovl12_01_800462F0[i].unk14;
            z = D_ovl12_01_800462F0[i].unk18;
            func_ovl12_01_80044F78(D_ovl12_01_800462F0[i].unk1C, D_ovl12_01_800462F0[i].unk1E,
                                   D_ovl12_01_800462F0[i].unk20, D_ovl12_01_800462F0[i].unk22,
                                   D_ovl12_01_800462F0[i].unk24, 0x10);
        }
        obj = func_ovl12_01_80045980(0x31D, 0xD0, x, y, z);
        func_ovl12_01_80045938(obj, 0x01000000);
        D_ovl12_01_800462F0[i].unk0 = obj;
    }
}

void func_ovl12_01_80043E60(void) {
    UnkStructA *obj;

    if (func_ovl12_01_80045D10(0x409) == 0) {
        obj = func_ovl12_01_80045980(0x31C, 0xD0, D_ovl12_01_8004632C.unk4, D_ovl12_01_8004632C.unk8,
                                     D_ovl12_01_8004632C.unkC);
        func_ovl12_01_80045938(obj, 0x01000000);
        D_ovl12_01_8004632C.unk0 = obj;
    }
}

void func_ovl12_01_80043DAC(void) {
    UnkStructA *obj;

    obj = func_ovl12_01_80045980(0x31E, 0xD0, D_ovl12_01_8004633C.unk4, D_ovl12_01_8004633C.unk8,
                                 D_ovl12_01_8004633C.unkC);
    if (obj != NULL) {
        func_ovl12_01_80045938(obj, 0x01080000);
        D_ovl12_01_8004633C.unk0 = obj;
        obj->unk40->unkC |= 0x8000;
        obj->unk40->unk20 = 90.0f;
        func_ovl12_01_80045640(obj->unk40, 2);
        func_ovl12_01_80045648(obj->unk40, 0x31F, 0, 0);
        func_ovl12_01_80045648(obj->unk40, 0x31F, 1, 1);
    }
}

void func_ovl12_01_80043D64(void) {
    func_ovl12_01_800450F0(3, 0, 0xF);
    func_ovl12_01_80043C00(0, 0x80, 0, 0.0f, 0);
}

void func_ovl12_01_80043D18(void) {
    func_ovl12_01_800450F0(0xE, 3, 0xF);
    func_ovl12_01_80043C00(1, 0x80, 0, 0.0f, 0);
}

void func_ovl12_01_80043CC8(void) {
    func_ovl12_01_800450F0(0x26, 0, 8);
    func_ovl12_01_80043C00(2, 0xC0, 0x80, 0.0f, 2);
}

void func_ovl12_01_80043C78(void) {
    func_ovl12_01_800450F0(0xC, 3, 0x10);
    func_ovl12_01_80043C00(3, 0xC0, 0x40, 0.0f, 0);
}

void func_ovl12_01_80043C28(void) {
    func_ovl12_01_800450F0(0xC, 3, 0x10);
    func_ovl12_01_80043C00(4, 0x80, 0x40, 0.0f, 0);
}

void func_ovl12_01_80043C00(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl12_01_80046500.unk0 = arg0;
    D_ovl12_01_80046500.unk4 = arg1;
    D_ovl12_01_80046500.unk8 = arg2;
    D_ovl12_01_80046500.unkC = arg3;
    D_ovl12_01_80046500.unk10 = arg4;
}

/* Defined above func_ovl12_01_80043BA4, which pulls them out ahead of
 * itself (func_ovl12_01_80043A44 pulled by func_ovl12_01_80043A8C, which
 * inlines it: its parameter's slot is the 8 bytes ovl_12_03's draft pads
 * its frame with). */
void func_ovl12_01_80043978(void) {
    func_ovl12_01_80045798(-90.0f, 32768.0f, 32768.0f);
    func_ovl12_01_800457E0(0xF);
    func_ovl12_01_800457F0(1);
    func_ovl12_01_80045128(1);
    func_ovl12_01_80045A88(func_ovl12_01_80044530, 0, 0, 0, 0x130);
}

void func_ovl12_01_800439E4(void) {
    func_ovl12_01_80045798(270.0f, 345.0f, 2000.0f);
    func_ovl12_01_800457E0(0x7F);
    func_ovl12_01_80045128(1);
    func_ovl12_01_80045A88(func_ovl12_01_80044644, 0, 0, 0, 0x130);
}

void func_ovl12_01_80043A44(f32 arg0) {
    f32 sp1C;

    func_ovl12_01_800457A0(&sp1C, NULL, NULL);
    func_ovl12_01_80045798(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl12_01_80043A8C(void) {
    f32 angle;

    func_ovl12_01_80045148();
    switch (D_ovl12_01_80046500.unk8) {
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
        func_ovl12_01_80045798(angle, 32768.0f, 32768.0f);
    } else {
        func_ovl12_01_80043A44(D_ovl12_01_80046500.unkC);
    }
    func_ovl12_01_80045130(D_ovl12_01_80046500.unk4);
}

void func_ovl12_01_80043BA4(void) {
    func_ovl12_01_80043A8C();
    if (D_ovl12_01_80046500.unk0 == 3) {
        func_ovl12_01_800439E4();
    }
    if (D_ovl12_01_80046500.unk0 == 4) {
        func_ovl12_01_80043978();
    }
}

void func_ovl12_01_80043958(void) {
    func_ovl12_01_80043910();
}

void func_ovl12_01_80043910(void) {
    /* empty, as in ovl_12_02's func_ovl12_02_80043258: without the test
     * the function is small enough to be inlined into the handler and
     * func_ovl12_01_80043958, where the original calls it */
    if (D_ovl12_01_80046500.unk0 == 2) {
    }
    func_ovl12_01_80045138(D_ovl12_01_80046500.unk4, 3, 4.0f, D_ovl12_01_80046500.unk10, 0, 1, 1);
}

void func_ovl12_01_80043850(void) {
    if (func_ovl12_01_80045100(0x25, 7, 0x26, 8) != 0) {
        func_ovl12_01_80043784();
        func_ovl12_01_80045138(0, 3, 4.0f, 5, 0, 1, 1);
        func_ovl12_01_800451E8();
        func_ovl12_01_80045AA8(120);
        func_ovl12_01_80045030(0x79, 0x12, 4);
    }
    if (func_ovl12_01_80045100(0x2E, 0xF, 0x2E, 0x10) != 0) {
        func_ovl12_01_80045130(0xC0);
        func_ovl12_01_80043754();
    }
}

void func_ovl12_01_80043784(void) {
    func_ovl12_01_80044F78(0x25, 0, 5, 0x26, 5, 0x1F);
    func_ovl12_01_80044F78(0x25, 0, 6, 0x26, 6, 0x14);
    func_ovl12_01_80044F78(0x25, 1, 4, 0x26, 4, 0x1F);
    func_ovl12_01_80044F78(0x25, 1, 5, 0x26, 5, 0x14);
    func_ovl12_01_80044F78(0x25, 2, 4, 0x26, 4, 0x14);
}

void func_ovl12_01_80043754(void) {
    func_ovl12_01_8004374C();
    func_ovl12_01_80045EE8(D_ovl12_01_800464E0);
    func_ovl12_01_80045058();
}

static void func_ovl12_01_8004374C(void) {
}

/* Defined above func_ovl12_01_800436F8, which pulls it out (and it its own
 * callees, defined below it) ahead of itself. */
void func_ovl12_01_80043468(void) {
    func_ovl12_01_80045128(1);
    func_ovl12_01_80046010(0x29);
    func_ovl12_01_80045AA8(10);
    func_ovl12_01_80045D00(0x409);
    func_ovl12_01_80045950(D_ovl12_01_80046318.unk0);
    func_ovl12_01_800433DC();
    func_ovl12_01_80045AA8(30);
    func_ovl12_01_80045898();
    func_ovl12_01_800457E0(0x7F);
    func_ovl12_01_80045778(4500.0f, 0.0f, 2000.0f);
    func_ovl12_01_80045798(-90.0f, 60.0f, 3000.0f);
    func_ovl12_01_80046010(0xB0);
    func_ovl12_01_800433A4();
    func_ovl12_01_80045938(D_ovl12_01_80046290[0].unk0, 0x04000000);
    func_ovl12_01_80045938(D_ovl12_01_80046290[1].unk0, 0x04000000);
    func_ovl12_01_80045938(D_ovl12_01_80046290[2].unk0, 0x04000000);
    for (;;) {
        if (D_ovl12_01_80046290[0].unk0->unk40->unkC & 0x40) {
            break;
        }
        func_ovl12_01_80045AD0();
    }
    func_ovl12_01_8004336C();
    func_ovl12_01_80043324(&D_ovl12_01_80046290[0]);
    func_ovl12_01_80043324(&D_ovl12_01_80046290[1]);
    func_ovl12_01_80043324(&D_ovl12_01_80046290[2]);
    func_ovl12_01_800432A0(&D_ovl12_01_80046290[0]);
    func_ovl12_01_800432A0(&D_ovl12_01_80046290[1]);
    func_ovl12_01_800432A0(&D_ovl12_01_80046290[2]);
    func_ovl12_01_80043264();
    func_ovl12_01_80045AA8(30);
    func_ovl12_01_80046010(0x2C);
    func_ovl12_01_80043190();
    func_ovl12_01_80045AA8(90);
    func_ovl12_01_80043180();
    func_ovl12_01_80045128(0);
}

void func_ovl12_01_800433DC(void) {
    s32 id;
    UnkStructA *obj;

    if (func_ovl12_01_80045D10(0x409) == 0) {
        id = 0x1B3;
    } else {
        id = 0x1B0;
    }
    obj = func_ovl12_01_80045980(id, 0xD0, D_ovl12_01_80046318.unk4, D_ovl12_01_80046318.unk8,
                                 D_ovl12_01_80046318.unkC);
    if (obj != NULL) {
        obj->unk40->unk28 = 2.0f;
        obj->unk40->unk30 = 2.0f;
        func_ovl12_01_80045938(obj, 0x01000000);
        D_ovl12_01_80046318.unk0 = obj;
    }
}

void func_ovl12_01_800433A4(void) {
    func_ovl12_01_80045A88(func_ovl12_01_8004490C, 0, 0, 0, 0x110);
}

void func_ovl12_01_8004336C(void) {
    func_ovl12_01_80045A88(func_ovl12_01_80044830, 0, 0, 0, 0x110);
}

void func_ovl12_01_80043324(UnkStruct_ovl12_01_80046290 *arg0) {
    func_ovl12_01_80044F80(arg0->unk10, arg0->unk12, arg0->unk16, arg0->unk18, arg0->unk1A, arg0->unk1E, 0x10);
}

void func_ovl12_01_800432A0(UnkStruct_ovl12_01_80046290 *arg0) {
    s32 y;

    func_ovl12_01_80044F78(arg0->unk10, arg0->unk14, arg0->unk16, arg0->unk18, arg0->unk1E, 0x11);
    y = arg0->unk14 - 1;
    if (y >= 0) {
        func_ovl12_01_80044F80(arg0->unk10, y, arg0->unk16, arg0->unk18, arg0->unk1C, arg0->unk1E, 0x1F);
    }
}

void func_ovl12_01_80043264(void) {
    func_ovl12_01_80044F78(0x2D, 1, 0xF, 0x2D, 0x10, 0x11);
}

void func_ovl12_01_80043190(void) {
    func_ovl12_01_80043188(45.0f, 16, 1);
}

/* Inlined into func_ovl12_01_80043190 only; that one is inlined into its
 * callers in turn (ovl_12_03's func_ovl12_03_8004316C). */
static void func_ovl12_01_80043188(f32 x, s32 z, s32 count) {
    s32 i;

    D_ovl12_01_800464F0[0] = x * 100.0f;
    D_ovl12_01_800464F0[1] = 0.0f;
    for (i = 0; i < count; i++) {
        D_ovl12_01_800464F0[1] += func_ovl12_01_80044FA0(i) * 100.0f;
    }
    D_ovl12_01_800464F0[1] += 100.0f;
    D_ovl12_01_800464F0[2] = z * 100.0f;
    D_ovl12_01_800464E0 = func_ovl12_01_80045EE0(0x28, (Vec3f *) D_ovl12_01_800464F0, 0);
}

static void func_ovl12_01_80043180(void) {
    func_ovl12_01_800458A0();
    func_ovl12_01_80045868(D_ovl12_01_800464C0);
    func_ovl12_01_800457D8(0x1F);
}

void func_ovl12_01_800436F8(void) {
    if (func_ovl12_01_80045100(0x17, 0xF, 0x18, 0x10) != 0 && func_ovl12_01_80045D10(0x409) == 0) {
        func_ovl12_01_800451E8();
        func_ovl12_01_80043468();
    }
}

void func_ovl12_01_80043138(void) {
    UNK_MACRO_ovl12_01_80043138();
}

void func_ovl12_01_800430F0(void) {
    func_ovl12_01_800430E8();
    D_ovl12_01_800464DC = func_ovl12_01_80045118();
    func_ovl12_01_800450F8(&D_ovl12_01_800464D0);
    func_ovl12_01_80045120(D_ovl12_01_800464DC, D_ovl12_01_800464C0);
}

static void func_ovl12_01_800430E8(void) {
}

void func_ovl12_01_800430C8(void) {
    func_ovl12_01_80045180(1);
}

void func_ovl12_01_800430A8(void) {
    func_ovl12_01_80045180(1);
}

void func_ovl12_01_80043058(void) {
    if (D_ovl12_01_80046500.unk0 == 3) {
        func_ovl12_01_80043018();
    }
    if (D_ovl12_01_80046500.unk0 == 4) {
        func_ovl12_01_80043038();
    }
}

void func_ovl12_01_80043038(void) {
    func_ovl12_01_80046190();
}

void func_ovl12_01_80043018(void) {
    func_ovl12_01_80046190();
}

void func_ovl12_01_80043010(void) {
}
