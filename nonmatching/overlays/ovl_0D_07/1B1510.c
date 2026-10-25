/*
 * NON_MATCHING: ovl_0D_07's stage object, complete: every function and its data.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 15, eu 15, jp 15
 *
 * Its .data and .rodata match (scratch/tools/datacmp.py), and the .bss has
 * the original's layout. What still differs in us (words):
 * - func_ovl0D_07_80043660 (13): registers only. Event 5 keeps
 *   D_8004671C in v1 where the original has v0; in event 11 the inlined
 *   func_ovl0D_07_80043010 has p0 and p1 in a3 and v1 (the original: v1
 *   and a3). How 80043010 is called decides event 4's register:
 *   with (obj[0], obj[1]) both arguments take a t register for the whole
 *   function and event 4 gets t2 for the original's t0; passing player 0
 *   through `o` and player 1's unk40 leaves only one, as in the original.
 * - func_ovl0D_07_8004342C (2): `mtc1 $zero` comes after `sw $ra` in the
 *   prologue, not before it (no fake moves it).
 */
#include "common.h"

/*
 * ovl_0D_07's stage object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).
 */

/* a model placed on the stage (D_ovl0D_07_800465A0): the object, its
 * collision handle, its model id, its collision box, and its position (in
 * tiles), angles and scale */
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
} UnkStruct_ovl0D_07_800465A0; /* size 0x38 */

/* what the ZeroJump stub 0x2D03 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0xA2];
    /* 0xA2 */ u16 unkA2;
} UnkStruct_ovl0D_07_80046440;

void func_ovl0D_07_800452C0(s32, UnkStructA_40 **); /* 0xD00 */
void func_ovl0D_07_800452D8(f32); /* 0xD03 */
void func_ovl0D_07_80045390(void (*)(UnkStructA *)); /* 0xE03 */
s32 func_ovl0D_07_800453A8(void); /* 0xF01 */
void func_ovl0D_07_80045430(s32, s32); /* 0xF12 */
s32 func_ovl0D_07_80045440(s32); /* 0xF14 */
void func_ovl0D_07_80045448(s32); /* 0xF15 */
void func_ovl0D_07_80045458(void); /* 0x1000 */
void func_ovl0D_07_80045460(s32, s32, s32); /* 0x1001 */
void func_ovl0D_07_80045498(s32); /* 0x1008 */
void func_ovl0D_07_800454A0(s32); /* 0x1009 */
void func_ovl0D_07_800454B8(void); /* 0x100C */
UnkStructA *func_ovl0D_07_800454E8(s32); /* 0x1012 */
void func_ovl0D_07_80045518(s32); /* 0x1018 */
void func_ovl0D_07_80045530(s32, s32); /* 0x101B */
void func_ovl0D_07_80045538(s32, s32); /* 0x101C */
UnkStructA_40 *func_ovl0D_07_80045988(s32, s32); /* 0x1500 */
void func_ovl0D_07_80045990(UnkStructA_40 *); /* 0x1501 */
void func_ovl0D_07_800459C8(UnkStructA_40 *, s32); /* 0x1508 */
void func_ovl0D_07_800459D0(UnkStructA_40 *, s32, s32); /* 0x1509 */
f32 func_ovl0D_07_800459E8(UnkStructA_40 *, s32); /* 0x150C */
s32 func_ovl0D_07_800459F0(UnkStructA_40 *, s32, s32, s32, s32, s32); /* 0x150D */
void func_ovl0D_07_800459F8(s32); /* 0x150E */
void func_ovl0D_07_80045AD8(s32); /* 0x1702 */
void func_ovl0D_07_80045AE8(f32, f32, f32); /* 0x1704 */
void func_ovl0D_07_80045AF0(f32 *, f32 *, f32 *); /* 0x1705 */
void func_ovl0D_07_80045AF8(f32, f32, f32); /* 0x1706 */
void func_ovl0D_07_80045B08(f32, f32, f32); /* 0x1708 */
void func_ovl0D_07_80045B10(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0D_07_80045B48(s32); /* 0x1710 */
void func_ovl0D_07_80045B50(s32); /* 0x1711 */
void func_ovl0D_07_80045C38(f32 *, f32 *, f32 *); /* 0x1803 */
f32 func_ovl0D_07_80045C50(Vec3f *, Vec3f *); /* 0x1806 */
void func_ovl0D_07_80045CA8(UnkStructA *, s32); /* 0x1811 */
void func_ovl0D_07_80045CB0(UnkStructA *, s32); /* 0x1812 */
void func_ovl0D_07_80045CC0(UnkStructA *); /* 0x1814 */
UnkStructA *func_ovl0D_07_80045CD0(s32, s32, s32, s32); /* 0x1816 */
UnkStructA *func_ovl0D_07_80045CF0(s32, s32, f32, f32, f32); /* 0x181A */
void func_ovl0D_07_80045D28(UnkStructA *); /* 0x1821 */
s32 func_ovl0D_07_80045DF8(void (*)(void), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0D_07_80045E00(s32); /* 0x1901 */
void func_ovl0D_07_80045E08(void); /* 0x1902 */
void func_ovl0D_07_80045E10(u16, s32); /* 0x1903 */
void func_ovl0D_07_80045E18(s32); /* 0x1904 */
void *func_ovl0D_07_80045E20(void); /* 0x1905 */
void func_ovl0D_07_80045E40(void); /* 0x1909 */
void func_ovl0D_07_80045E58(u16); /* 0x190C */
void func_ovl0D_07_80045E68(s32, s32, s32); /* 0x190E */
void func_ovl0D_07_80045E70(s32, s32); /* 0x190F */
f32 func_ovl0D_07_80045FA8(f32); /* 0x1D01 */
f64 func_ovl0D_07_80045FB0(void); /* 0x1D02 */
s32 func_ovl0D_07_80045FB8(s32); /* 0x1D03 */
void func_ovl0D_07_80046018(void); /* 0x1D0F */
void func_ovl0D_07_80046020(void); /* 0x1D10 */
void func_ovl0D_07_80046148(s32, s32, s32); /* 0x2201 */
void func_ovl0D_07_80046248(s32, f32, f32, f32, s32); /* 0x2600 */
void func_ovl0D_07_80046380(s32); /* 0x2B00 */
void func_ovl0D_07_80046390(s32); /* 0x2B02 */
void func_ovl0D_07_80046398(void); /* 0x2B03 */
void func_ovl0D_07_800463A0(s32, f32, f32, f32); /* 0x2B04 */
void func_ovl0D_07_80046428(s32, s32, s32, s32, s32); /* 0x2D00 */
UnkStruct_ovl0D_07_80046440 *func_ovl0D_07_80046440(s32); /* 0x2D03 */
void func_ovl0D_07_80046448(s32); /* 0x2D04 */
void func_ovl0D_07_800464F8(void); /* 0x3000 */
void func_ovl0D_07_80046500(void); /* 0x3001 */

void func_ovl0D_07_80043030(void);
void func_ovl0D_07_80043108(void);
void func_ovl0D_07_800432F8(void);
void func_ovl0D_07_8004342C(void);
void func_ovl0D_07_80043660(s32 arg0);
void func_ovl0D_07_80043D80(void);
static void func_ovl0D_07_80043028(void);
static void func_ovl0D_07_80043020(void);
static void func_ovl0D_07_80043018(void);
static f32 func_ovl0D_07_80043010(UnkStructA *obj0, UnkStructA_40 *p1);
static void func_ovl0D_07_80043424(UnkStruct_ovl0D_07_800465A0 *e);
static void func_ovl0D_07_800432F0(UnkStruct_ovl0D_07_800465A0 *e);
void func_ovl0D_07_80044628(void);
void func_ovl0D_07_80044798(void);
void func_ovl0D_07_80044918(void);
void func_ovl0D_07_80044A98(void);
void func_ovl0D_07_80044AF0(void);
void func_ovl0D_07_80044754(UnkStructA *arg0);
void func_ovl0D_07_80044C90(void);

/* .bss */
u8 D_ovl0D_07_800466E0[0x24];
s32 D_ovl0D_07_80046704;
s32 D_ovl0D_07_80046708;
u8 D_ovl0D_07_8004670C[0x4];
Vec3f D_ovl0D_07_80046710;
s32 D_ovl0D_07_8004671C;
UnkStructA_40 *D_ovl0D_07_80046720[5];
s32 D_ovl0D_07_80046734;
s32 D_ovl0D_07_80046738;
UnkStructA_40 *D_ovl0D_07_8004673C;

/* .data */
UnkStruct_ovl0D_07_800465A0 D_ovl0D_07_800465A0 = {
    NULL, -1, 0x16F, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0D_07_80044F4C(void) {
    D_ovl0D_07_800466E0[0] = D_ovl0D_07_8004670C[0];
}

static void func_ovl0D_07_80044F44(void) {
}

static void func_ovl0D_07_80044F3C(void) {
}

static void func_ovl0D_07_80044F34(void) {
}

static void func_ovl0D_07_80044F2C(void) {
}

static void func_ovl0D_07_80044F24(void) {
}

static void func_ovl0D_07_80044F1C(void) {
}

static void func_ovl0D_07_80044F14(void) {
}

static void func_ovl0D_07_80044F0C(void) {
}

static void func_ovl0D_07_80044F04(void) {
}

void func_ovl0D_07_80044EEC(void) {
    D_ovl0D_07_80046704 = -1;
    D_ovl0D_07_80046708 = -1;
}

void func_ovl0D_07_80044E90(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0D_07_80045AE8(D_ovl0D_07_80046710.x, D_ovl0D_07_80046710.y, D_ovl0D_07_80046710.z);
    func_ovl0D_07_80045B08(arg0, arg1, arg2);
    func_ovl0D_07_80045E18(180);
}

void func_ovl0D_07_80044E48(f32 arg0) {
    f32 sp1C;

    func_ovl0D_07_80045B10(&sp1C, NULL, NULL);
    func_ovl0D_07_80045B08(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0D_07_80044E14(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0D_07_800463A0(arg0, p->unk10, p->unk14, p->unk18);
}

/* a task: a pulse at the object's place (the callback's argument) */
void func_ovl0D_07_80044C90(void) {
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 i;
    f32 a;

    obj = func_ovl0D_07_80045E20();
    p = func_ovl0D_07_80045988(0x183, 0);
    p->unkC |= 0x80;
    p->unk36 = 0x80;
    p->unk10 = obj->unk40->unk10;
    p->unk14 = obj->unk40->unk14;
    p->unk18 = obj->unk40->unk18;
    p->unk2C = 0.2f;
    func_ovl0D_07_800463A0(0xB3, p->unk10, p->unk14, p->unk18);
    a = 0.0f;
    for (i = 0; i != 20; i++) {
        p->unk2C = func_ovl0D_07_80045FA8(a) * 1.5f;
        a = a + 9.0f >= 360.0f ? a + 9.0f - 360.0f : a + 9.0f < 0.0f ? a + 9.0f + 360.0f : a + 9.0f;
        func_ovl0D_07_80045E40();
    }
    func_ovl0D_07_80045990(p);
    func_ovl0D_07_80045E08();
}

/* a task: player 2 floats up and down */
void func_ovl0D_07_80044AF0(void) {
    UnkStructA *obj;
    s32 i;
    f32 a;

    obj = func_ovl0D_07_800454E8(1);
    obj->unk68 = obj->unk6C;
    for (i = 0; i < 60; i++) {
        obj->unk40->unk14 -= 6.6666665f;
        func_ovl0D_07_80045E40();
    }
    a = 0.0f;
    for (i = 0; i < 120; i++) {
        obj->unk40->unk14 += 2.0f * func_ovl0D_07_80045FA8(a);
        a = a + 5.0f >= 360.0f ? a + 5.0f - 360.0f : a + 5.0f < 0.0f ? a + 5.0f + 360.0f : a + 5.0f;
        func_ovl0D_07_80045E40();
    }
    for (i = 0; i != 30; i++) {
        obj->unk68 = obj->unk6C;
        obj->unk40->unk14 += 26.666666f;
        func_ovl0D_07_80045E40();
    }
    while (TRUE) {
        obj->unk68 = obj->unk6C;
        func_ovl0D_07_80045E40();
    }
}

void func_ovl0D_07_80044A98(void) {
    if (D_ovl0D_07_8004671C == 0x10) {
        func_ovl0D_07_80045E18(0x280);
        func_ovl0D_07_80046390(10);
    } else {
        func_ovl0D_07_80045E18(45);
        func_ovl0D_07_80046390(18);
    }
    func_ovl0D_07_80045E08();
}

/* a task: a ring growing at the object's place (the task's argument) */
void func_ovl0D_07_80044918(void) {
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 i;

    obj = func_ovl0D_07_80045E20();
    p = func_ovl0D_07_80045988(7, 0);
    p->unkC |= 0x80;
    p->unk10 = obj->unk40->unk10;
    p->unk14 = obj->unk40->unk14;
    p->unk18 = obj->unk40->unk18;
    p->unk36 = 0xDC;
    p->unk28 = 0.1f;
    p->unk2C = 0.1f;
    p->unk30 = 0.1f;
    for (i = 0; i != 180; i++) {
        p->unk30 += 0.08888889f;
        p->unk28 = p->unk2C = p->unk30;
        p->unk36 = p->unk36 - 1.2222222f;
        if (p->unk36 < 0.0f) {
            p->unkC |= 1;
        }
        func_ovl0D_07_80045E40();
    }
    func_ovl0D_07_80045990(p);
    func_ovl0D_07_80045E08();
}

/* a task: the same, faster */
void func_ovl0D_07_80044798(void) {
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 i;

    obj = func_ovl0D_07_80045E20();
    p = func_ovl0D_07_80045988(7, 0);
    p->unkC |= 0x80;
    p->unk10 = obj->unk40->unk10;
    p->unk14 = obj->unk40->unk14;
    p->unk18 = obj->unk40->unk18;
    p->unk36 = 0xC8;
    p->unk28 = 0.1f;
    p->unk2C = 0.1f;
    p->unk30 = 0.1f;
    for (i = 0; i != 30; i++) {
        p->unk30 += 0.6666667f;
        p->unk28 = p->unk2C = p->unk30;
        p->unk36 = p->unk36 - 6.6666665f;
        if (p->unk36 < 0.0f) {
            p->unkC |= 1;
        }
        func_ovl0D_07_80045E40();
    }
    func_ovl0D_07_80045990(p);
    func_ovl0D_07_80045E08();
}

/* above its callback 80044754 in the source: defined with the other helpers,
 * the callbacks come out out of order */
void func_ovl0D_07_8004342C(void) {
    /* fakes: the first keeps the call's argument out of the prologue, the
     * second keeps the static's last stores ahead of the next call */
    if (!D_ovl0D_07_80046704 && !D_ovl0D_07_80046704 && !D_ovl0D_07_80046704) {
    }
    func_ovl0D_07_80043424(&D_ovl0D_07_800465A0);
    if (!D_ovl0D_07_80046704 && !D_ovl0D_07_80046704 && !D_ovl0D_07_80046704) {
    }
    func_ovl0D_07_80045CB0(D_ovl0D_07_800465A0.unk0, 0x80000);
    D_ovl0D_07_8004673C = func_ovl0D_07_80045988(0x207, 0);
    D_ovl0D_07_8004673C->unkC |= 0x80;
    func_ovl0D_07_800452C0(0x170, &D_ovl0D_07_8004673C);
    func_ovl0D_07_80045458();
    func_ovl0D_07_80045390(func_ovl0D_07_80044754);
    func_ovl0D_07_800452D8(-100.0f);
    func_ovl0D_07_80046148(0, 0x28, 0x46);
    D_ovl0D_07_80046734 = 1;
    D_ovl0D_07_80046738 = 0;
    func_ovl0D_07_80046018();
}

/* the stage's callback (func_ovl0D_07_8004342C) */
void func_ovl0D_07_80044754(UnkStructA *arg0) {
    func_ovl0D_07_80045CB0(arg0, 0x01000000);
    func_ovl0D_07_80045DF8(func_ovl0D_07_80044C90, arg0, 0, 0, 0x150);
}

/* a task: one of the five pieces (D_ovl0D_07_80046720) flies off */
void func_ovl0D_07_80044628(void) {
    UnkStructA_40 *p;
    s32 i;
    f32 dx;
    f32 dz;

    p = func_ovl0D_07_80045E20();
    dx = (f32)func_ovl0D_07_80045FB0() * 10.0f;
    dz = (f32)func_ovl0D_07_80045FB0() * 10.0f;
    p->unkC |= 0x80;
    p->unk36 = 0xFF;
    for (i = -60; i != 20; i++) {
        p->unk14 = i * i * -0.11f + 400.0f;
        p->unk1C += dx;
        p->unk36 -= 3;
        p->unk24 += dz;
        func_ovl0D_07_80045E40();
    }
    p->unkC |= 1;
    func_ovl0D_07_80045E08();
}

/* a task: the stage's ending */
void func_ovl0D_07_80043D80(void) {
    UnkStructA *obj;
    UnkStructA *obj2;
    s32 i;
    s32 task;
    f32 y;

    obj = func_ovl0D_07_800454E8(0);
    func_ovl0D_07_80045538(0, 2);
    for (i = 0; i < 120; i++) {
        obj->unk40->unk18 -= 1.6666666f;
        if (D_ovl0D_07_8004671C != 0x1A && D_ovl0D_07_8004671C != 0x1B) {
            func_ovl0D_07_80045E40();
        }
    }
    task = func_ovl0D_07_80045DF8(func_ovl0D_07_80044AF0, NULL, 0, 0, 0x130);
    func_ovl0D_07_80045538(0, 0);
    func_ovl0D_07_80045E18(210);
    func_ovl0D_07_80045E70(0x70, 0x70);
    func_ovl0D_07_80045E18(120);
    func_ovl0D_07_80046380(0x221);
    func_ovl0D_07_80045CA8(D_ovl0D_07_800465A0.unk0, 0x04000000);
    func_ovl0D_07_80045E18(70);
    func_ovl0D_07_80046380(0x21F);
    for (i = 0; i < 5; i++) {
        func_ovl0D_07_80045DF8(func_ovl0D_07_80044628, D_ovl0D_07_80046720[i], 0, 0, 0x130);
    }
    obj->unk68 = 20.0f;
    obj->unk70 = 0.40833336f;
    while (obj->unk68 != 0.0f) {
        func_ovl0D_07_80045E40();
    }
    obj = func_ovl0D_07_800454E8(1);
    obj->unk40->unk10 = 2350.0f;
    if (D_ovl0D_07_8004671C == 0x1B) {
        obj->unk40->unk14 = 600.0f;
        obj->unk40->unk18 = 1655.0f;
    } else {
        obj->unk40->unk14 = 500.0f;
        obj->unk40->unk18 = 1550.0f;
    }
    obj->unk68 = 0.0f;
    func_ovl0D_07_80045E00(task);
    if (D_ovl0D_07_8004671C == 0x1A) {
        func_ovl0D_07_80045AE8(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
        func_ovl0D_07_80045B08(32768.0f, 32768.0f, 630.0f);
        func_ovl0D_07_80045E18(30);
    } else if (D_ovl0D_07_8004671C == 0x1B) {
        obj->unk70 = 0.40833336f;
        obj->unk6C = 8.166667f;
        func_ovl0D_07_80045AE8(obj->unk40->unk10, obj->unk40->unk14 - 50.0f, obj->unk40->unk18);
        func_ovl0D_07_80045B08(350.0f, 32768.0f, 800.0f);
        while (obj->unk40->unk14 > 400.0f) {
            func_ovl0D_07_80045E40();
        }
        func_ovl0D_07_80045538(1, 0x13);
        func_ovl0D_07_80046248(0, obj->unk40->unk10, obj->unk40->unk14 + 50.0f, obj->unk40->unk18, 0);
        func_ovl0D_07_80045530(1, 3);
        for (i = 0; i != 20; i++) {
            obj->unk40->unk18 += 7.5f;
            func_ovl0D_07_80045D28(obj);
            func_ovl0D_07_80045E40();
        }
        func_ovl0D_07_80045CB0(obj, 0x01000000);
        obj2 = func_ovl0D_07_80045CD0(obj->unk28, 0x01000000, 0xC0, 0);
        obj2->unk40->unk10 = obj->unk40->unk10;
        obj2->unk40->unk18 = obj->unk40->unk18;
        obj2->unk40->unk20 = obj->unk40->unk20;
        obj2->unk40->unk24 = obj->unk40->unk24;
        obj2->unk40->unk14 = 50.0f;
        obj2->unk40->unk1C = 90.0f;
        func_ovl0D_07_80045E18(30);
        func_ovl0D_07_800459C8(obj2->unk40, 2);
        func_ovl0D_07_800459D0(obj2->unk40, 1, 0);
        func_ovl0D_07_800459D0(obj2->unk40, 2, 1);
        obj2->unk40->unkC &= ~0x60;
        func_ovl0D_07_80045AE8(obj2->unk40->unk10 + 20.0f, obj2->unk40->unk14, obj2->unk40->unk18 + 80.0f);
        func_ovl0D_07_80045B08(340.0f, 60.0f, 800.0f);
        func_ovl0D_07_80045E18(60);
        func_ovl0D_07_800464F8();
        D_ovl0D_07_80046734 = 0;
        func_ovl0D_07_80045E08();
    } else {
        func_ovl0D_07_80045E18(30);
        func_ovl0D_07_80045AF0(NULL, &y, NULL);
        for (i = 0; i != 180; i++) {
            func_ovl0D_07_80045AE8(32768.0f, i * 1.6666666f + y, 32768.0f);
            func_ovl0D_07_80045E40();
        }
        func_ovl0D_07_80045B08(32768.0f, 32768.0f, 630.0f);
    }
    func_ovl0D_07_800459D0(obj->unk40, 0x1F, 0);
    func_ovl0D_07_800459D0(obj->unk40, -1, 1);
    obj->unk40->unk48->unk4->unk8 |= 0x20;
    obj->unk40->unk48->unk4->unk8 &= ~0x40;
    func_ovl0D_07_80046380(0x1B2);
    while (!(obj->unk40->unk48->unk4->unk8 & 0x40)) {
        func_ovl0D_07_80045E40();
    }
    if (D_ovl0D_07_8004671C == 0x1A) {
        func_ovl0D_07_80045E18(30);
        func_ovl0D_07_800464F8();
        D_ovl0D_07_80046734 = 0;
        func_ovl0D_07_80045E08();
    }
    func_ovl0D_07_80045E18(30);
    func_ovl0D_07_800459D0(obj->unk40, 0x16, 0);
    func_ovl0D_07_800459D0(obj->unk40, -1, 1);
    obj->unk40->unk48->unk4->unk8 |= 0x20;
    obj->unk40->unk48->unk4->unk8 &= ~0x40;
    func_ovl0D_07_80045E18(7);
    obj->unk68 = 20.0f;
    obj->unk70 = 1.6333334f;
    for (i = 0; i != 30; i++) {
        if (i == 5) {
            obj->unk40->unk48->unk4->unk8 |= 0x40;
        }
        obj->unk40->unk18 += 5.0f;
        func_ovl0D_07_80045E40();
    }
    func_ovl0D_07_80046448(1);
    func_ovl0D_07_80045AE8(2350.0f, 100.0f, 2020.0f);
    func_ovl0D_07_80045B08(0.0f, 45.0f, 2220.0f);
    func_ovl0D_07_80045B48(0x10);
    func_ovl0D_07_80045B50(0xF);
    while (obj->unk68 != 0.0f) {
        func_ovl0D_07_80045E40();
    }
    func_ovl0D_07_80045E18(30);
    func_ovl0D_07_80045E68(0x70, 0x70, 0);
    func_ovl0D_07_80045518(1);
    func_ovl0D_07_80045498(0);
    func_ovl0D_07_80045518(0);
    D_ovl0D_07_80046734 = 0;
    func_ovl0D_07_80045430(0x3E, 0x11);
    func_ovl0D_07_80045E58(func_ovl0D_07_80046440(1)->unkA2);
    obj = func_ovl0D_07_800454E8(0);
    obj->unk68 = 0.0f;
    obj->unk70 = 1.6333334f;
    obj->unk6C = 16.333334f;
    obj = func_ovl0D_07_800454E8(1);
    obj->unk68 = 0.0f;
    obj->unk70 = 1.6333334f;
    obj->unk6C = 16.333334f;
    func_ovl0D_07_80045E08();
}


/* the stage's model (D_ovl0D_07_800465A0) placed */
static void func_ovl0D_07_80043424(UnkStruct_ovl0D_07_800465A0 *e) {
    e->unk0 = func_ovl0D_07_80045CF0(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0D_07_80045CA8(e->unk0, 0x01080000);
    func_ovl0D_07_80045CB0(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl0D_07_800459F0(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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

/* the stage's model removed */
static void func_ovl0D_07_800432F0(UnkStruct_ovl0D_07_800465A0 *e) {
    func_ovl0D_07_80045CC0(e->unk0);
    if (e->unkC != 0xFFFF && e->unkE != 0xFFFF && e->unk10 != 0xFFFF && e->unk12 != 0xFFFF) {
        func_ovl0D_07_800459F8(e->unk4);
    }
    e->unk0 = NULL;
    e->unk4 = -1;
}


void func_ovl0D_07_800432F8(void) {
    s32 i;

    if (D_ovl0D_07_8004671C == 0x1A || D_ovl0D_07_8004671C == 0x1B) {
        func_ovl0D_07_80046500();
    }
    if (D_ovl0D_07_8004671C == 0x10 || D_ovl0D_07_8004671C == 0x1A || D_ovl0D_07_8004671C == 0x1B) {
        for (i = 0; i < 5; i++) {
            func_ovl0D_07_80045990(D_ovl0D_07_80046720[i]);
        }
    }
    func_ovl0D_07_800432F0(&D_ovl0D_07_800465A0);
    /* a fake: keeps the static's stores ahead of the next call's argument */
    if (!D_ovl0D_07_80046704 && !D_ovl0D_07_80046704 && !D_ovl0D_07_80046704) {
    }
    func_ovl0D_07_80045990(D_ovl0D_07_8004673C);
    if (D_ovl0D_07_80046738 == 0) {
        func_ovl0D_07_80046020();
    }
}

void func_ovl0D_07_80043108(void) {
    s32 i;
    UnkStructA *obj;

    func_ovl0D_07_80046380(0x224);
    func_ovl0D_07_80045460(0x17, 0, 0x17);
    func_ovl0D_07_800454A0(0);
    func_ovl0D_07_80046428(1, 1, 0x17, 2, 10);
    func_ovl0D_07_80046448(0);
    func_ovl0D_07_80045518(1);
    func_ovl0D_07_80045498(1);
    func_ovl0D_07_80045518(0);
    func_ovl0D_07_800454E8(0)->unk40->unk10 += 50.0f;
    obj = func_ovl0D_07_800454E8(1);
    obj->unk40->unk10 += 50.0f;
    obj->unk40->unk14 += 200.0f;
    func_ovl0D_07_80045E10(func_ovl0D_07_80046440(1)->unkA2, 0);
    for (i = 0; i != 5; i++) {
        D_ovl0D_07_80046720[i] = func_ovl0D_07_80045988(0x171, 0);
        D_ovl0D_07_80046720[i]->unk10 = 2350.0f;
        D_ovl0D_07_80046720[i]->unk14 = 0.0f;
        D_ovl0D_07_80046720[i]->unk18 = i * 600.0f + 350.0f;
    }
    func_ovl0D_07_800454B8();
    func_ovl0D_07_80045B50(0x1F);
    func_ovl0D_07_80045AE8(2350.0f, 138.0f, 1694.0f);
    func_ovl0D_07_80045B08(0.0f, 10.0f, 1500.0f);
    func_ovl0D_07_80045498(1);
}

void func_ovl0D_07_80043030(void) {
    UnkStructA_40 *p;

    func_ovl0D_07_80043028(); /* the stubs' placement (above) */
    func_ovl0D_07_80043020();
    func_ovl0D_07_80043018();
    func_ovl0D_07_80045460(0x17, 0, 0x17);
    func_ovl0D_07_800454A0(0);
    D_ovl0D_07_800465A0.unk0->unk40->unk48->unk4->unk4 =
        func_ovl0D_07_800459E8(D_ovl0D_07_800465A0.unk0->unk40, 0) - 0.01f;
    func_ovl0D_07_80046428(1, 1, 0x17, 0, 0x11);
    p = func_ovl0D_07_800454E8(0)->unk40;
    p->unk10 += 50.0f;
    p = func_ovl0D_07_800454E8(1)->unk40;
    p->unk10 += 50.0f;
    func_ovl0D_07_800454B8();
    func_ovl0D_07_80045B50(0xF);
}

/* the two players face each other (event 11): the angle for player 1. A
 * static: its locals sit below the caller's and the spill, as in the original
 * (`pad` is a word the frame has there: a p1 copy does the same) */
static f32 func_ovl0D_07_80043010(UnkStructA *obj0, UnkStructA_40 *p1) {
    s32 pad;
    UnkStructA_40 *p0;
    Vec3f pos0;
    Vec3f pos1;
    Vec3f angle;

    p0 = obj0->unk40;
    pos0.x = p0->unk10;
    pos0.y = p0->unk14;
    pos0.z = p0->unk18;
    pos1.x = p1->unk10;
    pos1.y = p1->unk14;
    pos1.z = p1->unk18;
    func_ovl0D_07_80045C38(&pos0.x, &pos1.x, &angle.x);
    return angle.x;
}

/* three of the four stubs before func_ovl0D_07_80043030: statics inlined
 * everywhere. Called from 80043030 they come out there; which statics they
 * were, and who called them, isn't known (the first is 80043010's) */
static void func_ovl0D_07_80043018(void) {
}

static void func_ovl0D_07_80043020(void) {
}

static void func_ovl0D_07_80043028(void) {
}


/* the stage object's callback (the entry returns it): what each event does.
 * Last in the source, so it is processed first: it pulls out its callees
 * 80043030-8004342C ahead of itself, in the reverse order of their last calls,
 * which puts 80043010's stub (case 11 calls it last) with 80043030's three */
void func_ovl0D_07_80043660(s32 arg0) {
    UnkStructA *o;
    s32 pad[3]; /* a guess: the frame has three more words here */
    s32 i;
    s32 kind;
    UnkStructA *obj[2];
    Vec3f angle;
    f32 dist;
    Vec3f mid;
    Vec3f pos;

    switch (arg0) {
        case 2:
            D_ovl0D_07_8004671C = func_ovl0D_07_800453A8();
            func_ovl0D_07_8004342C();
            break;
        case 1:
            func_ovl0D_07_800432F8();
            break;
        case 16:
        case 26:
        case 27:
            func_ovl0D_07_80043108();
            break;
        case 17:
            func_ovl0D_07_80043030();
            break;
        case 5:
            if (D_ovl0D_07_8004671C == 0x10 || 0x1A == D_ovl0D_07_8004671C || D_ovl0D_07_8004671C == 0x1B) {
                while (D_ovl0D_07_80046734 != 0) {
                    func_ovl0D_07_80045E40();
                }
                func_ovl0D_07_80045498(0);
            }
            break;
        case 4:
            if (D_ovl0D_07_8004671C != 0x1A && D_ovl0D_07_8004671C != 0x1B) {
                func_ovl0D_07_80045DF8(func_ovl0D_07_80044A98, NULL, 0, 0, 0x130);
            }
            if (D_ovl0D_07_8004671C == 0x10 || 0x1A == D_ovl0D_07_8004671C || D_ovl0D_07_8004671C == 0x1B) {
                func_ovl0D_07_80045DF8(func_ovl0D_07_80043D80, NULL, 0, 0, 0x130);
            }
            break;
        case 11:
            if (func_ovl0D_07_80045440(1) == 3) {
                break;
            }
            func_ovl0D_07_80045498(1);
            func_ovl0D_07_80045E18(30);
            obj[1] = func_ovl0D_07_800454E8(1);
            obj[0] = o = func_ovl0D_07_800454E8(0);
            obj[0]->unk40->unk20 = func_ovl0D_07_80043010(o, obj[1]->unk40);
            func_ovl0D_07_80045AE8(obj[1]->unk40->unk10, obj[1]->unk40->unk14 + 50.0f, obj[1]->unk40->unk18);
            func_ovl0D_07_80045AD8(0);
            func_ovl0D_07_80045AF8(2350.0f, 300.0f, 1550.0f);
            func_ovl0D_07_80045AD8(1);
            mid.x = 2350.0f;
            mid.y = 0.0f;
            mid.z = 1550.0f;
            o = obj[1];
            pos.x = o->unk40->unk10;
            pos.y = o->unk40->unk14;
            pos.z = o->unk40->unk18;
            dist = func_ovl0D_07_80045C50(&mid, &pos);
            func_ovl0D_07_80045B10(&angle.x, NULL, NULL);
            if (dist <= 500.0f) {
                angle.x = angle.x + 180.0f >= 360.0f ? angle.x + 180.0f - 360.0f
                        : angle.x + 180.0f < 0.0f    ? angle.x + 180.0f + 360.0f
                                                     : angle.x + 180.0f;
            }
            obj[1]->unk40->unk20 = angle.x;
            func_ovl0D_07_80045B08(angle.x, 32768.0f, 32768.0f);
            func_ovl0D_07_80045448(50);
            func_ovl0D_07_80046398();
            func_ovl0D_07_80046380(0x21A);
            for (i = 0; i < 32; i++) {
                func_ovl0D_07_80045FB8(0x100);
                kind = (func_ovl0D_07_80045FB8(0x100) & 1) ? 0xC : 0x18;
                func_ovl0D_07_80046248(kind, (obj[1]->unk40->unk10 - 80.0f) + func_ovl0D_07_80045FB0() * 160.0,
                                       obj[1]->unk40->unk14 + func_ovl0D_07_80045FB0() * 50.0 + 50.0,
                                       (obj[1]->unk40->unk18 - 80.0f) + func_ovl0D_07_80045FB0() * 160.0, 0);
                func_ovl0D_07_80045E18(4);
            }
            func_ovl0D_07_80046248(0x14, obj[1]->unk40->unk10, obj[1]->unk40->unk14 + 100.0f, obj[1]->unk40->unk18, 0);
            func_ovl0D_07_80046380(0x1B5);
            func_ovl0D_07_80046380(0x21C);
            func_ovl0D_07_80045DF8(func_ovl0D_07_80044918, obj[1], 0, 0, 0x130);
            func_ovl0D_07_80045DF8(func_ovl0D_07_80044798, obj[1], 0, 0, 0x130);
            func_ovl0D_07_80045E18(10);
            func_ovl0D_07_80045CB0(obj[1], 0x01000000);
            for (i = 0; i != 60; i++) {
                func_ovl0D_07_80045B08(32768.0f, 45.0f, i * 16.666666f + 1500.0f);
                func_ovl0D_07_80045E40();
            }
            func_ovl0D_07_80045E18(60);
            func_ovl0D_07_800454E8(0);
            func_ovl0D_07_80045AE8(obj[0]->unk40->unk10, 50.0f, obj[0]->unk40->unk18);
            func_ovl0D_07_80045AD8(0);
            func_ovl0D_07_80045AF8(2350.0f, 300.0f, 1550.0f);
            func_ovl0D_07_80045AD8(1);
            mid.x = 2350.0f;
            mid.y = 0.0f;
            mid.z = 1550.0f;
            o = obj[0];
            pos.x = o->unk40->unk10;
            pos.y = o->unk40->unk14;
            pos.z = o->unk40->unk18;
            dist = func_ovl0D_07_80045C50(&mid, &pos);
            func_ovl0D_07_80045B10(&angle.x, NULL, NULL);
            if (dist <= 500.0f) {
                angle.x = angle.x + 180.0f >= 360.0f ? angle.x + 180.0f - 360.0f
                        : angle.x + 180.0f < 0.0f    ? angle.x + 180.0f + 360.0f
                                                     : angle.x + 180.0f;
            }
            obj[0]->unk40->unk20 = angle.x;
            func_ovl0D_07_80045B08(angle.x, 32768.0f, 32768.0f);
            func_ovl0D_07_80045498(0);
            func_ovl0D_07_80045448(32);
            func_ovl0D_07_80046020();
            D_ovl0D_07_80046738 = 1;
            break;
    }
}