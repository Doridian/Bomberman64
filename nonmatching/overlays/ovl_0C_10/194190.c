/*
 * NON_MATCHING: ovl_0C_10's game object, complete: every function and its
 * data (.data 0x40 and .rodata 0xD0 byte for byte as the original, .bss 0x70).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 166, eu 166, jp 166
 *
 * The text order took care: 80043010 (a static, args in a3/t0) comes first
 * only when every handler callee is defined above the handler, so that the
 * handler pulls them all (last-called first); 80043144 must sit just above
 * 800447A4, or 800447A4 and 800447E4 swap; and 80043F70 calls 80043F2C
 * (inlined) with 80043F2C defined above it: written out instead, 80044D08
 * (with 80044C30) comes out ahead of 800448C0.
 *
 * What still differs in us (words):
 * - func_ovl0C_10_80043450 (122): the frame.  The original's is 0xA8, ours
 *   0xA0; its case 11 locals sit 20 bytes lower and with gaps (obj0 0x90,
 *   pos 0x80, target 0x74, angle 0x68, flag 0x60, task 0x58, snd 0x4C), as if
 *   case 11 were an inlined static.  Ours also stores `flag = FALSE` early
 *   (one word longer) and keeps the distance in f0 where the original has
 *   f14.
 * - func_ovl0C_10_80043F70 (25): the frame, 0x80 where the original's is
 *   0x78.  The inlined call to 80043F2C costs 8 bytes; without it the frame
 *   is right but the text order isn't (above).
 * - func_ovl0C_10_800447E4 (19): no difference of its own: an infinite loop's
 *   dead epilogue is aligned to 16, and the handler's extra word moves it.
 */
#include "common.h"

/*
 * ovl_0C_10's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).  The same skeleton as
 * ovl_0C_04's 17CC20 and ovl_12_06's 25D670.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_10_800466B0;

/* what func_ovl0C_10_80045DB0 is given: an object's 0x40 and two numbers */
typedef struct {
    /* 0x00 */ UnkStructA_40 *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_ovl0C_10_80045DB0;

/* func_ovl0C_10_800448C0's camera moves: a frame count, from, to */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ Vec3f unk4;
    /* 0x10 */ Vec3f unk10;
} UnkStruct_ovl0C_10_80046560;

void func_ovl0C_10_80045268(s32);
void func_ovl0C_10_80045280(s32);
void func_ovl0C_10_800452F0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_10_80045350(void (*)(UnkStructA *));
s32 func_ovl0C_10_80045368(void);
void func_ovl0C_10_800453A0(void (*)(UnkStructA *));
void func_ovl0C_10_800453F0(s32, s32);
s32 func_ovl0C_10_80045400(s32);
void func_ovl0C_10_80045408(s32);
void func_ovl0C_10_80045418(void);
void func_ovl0C_10_80045428(void *);
s32 func_ovl0C_10_80045448(void);
void func_ovl0C_10_80045450(s32, void *);
void func_ovl0C_10_80045458(s32);
void func_ovl0C_10_80045460(s32);
void func_ovl0C_10_80045468(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_10_80045478(void);
void func_ovl0C_10_80045490(s32);
UnkStructA *func_ovl0C_10_800454A8(s32);
void func_ovl0C_10_800454B0(s32);
void func_ovl0C_10_80045990(UnkStructA_40 *, s32, s32);
f32 func_ovl0C_10_800459A8(UnkStructA_40 *, s32);
void func_ovl0C_10_800459D0(s32, s32);
void func_ovl0C_10_800459F8(s32, s32, s32);
void func_ovl0C_10_80045A98(s32);
void func_ovl0C_10_80045AA8(f32, f32, f32);
void func_ovl0C_10_80045AB8(f32, f32, f32);
void func_ovl0C_10_80045AC8(f32, f32, f32);
void func_ovl0C_10_80045AD0(f32 *, f32 *, f32 *);
void func_ovl0C_10_80045B10(s32);
void func_ovl0C_10_80045B60(f32, f32);
void func_ovl0C_10_80045BF8(f32 *, f32 *, f32 *);
void func_ovl0C_10_80045C10(f32 *, f32 *);
void func_ovl0C_10_80045C68(UnkStructA *, s32);
void func_ovl0C_10_80045C70(UnkStructA *, s32);
void func_ovl0C_10_80045C80(UnkStructA *);
UnkStructA *func_ovl0C_10_80045C90(s32, s32, s32, s32);
void func_ovl0C_10_80045CA0(UnkStructA *);
void func_ovl0C_10_80045CE8(UnkStructA *);
void func_ovl0C_10_80045DB0(UnkStruct_ovl0C_10_80045DB0 *);
s32 func_ovl0C_10_80045DB8(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_10_80045DC0(s32);
void func_ovl0C_10_80045DC8(void);
void func_ovl0C_10_80045DD8(s32);
void *func_ovl0C_10_80045DE0(void);
s32 func_ovl0C_10_80045E00(void);
UnkStructC *func_ovl0C_10_80045E40(s32);
void func_ovl0C_10_80045E50(UnkStructC *, s32);
f32 func_ovl0C_10_80045F60(f32);
f32 func_ovl0C_10_80045F68(f32);
void func_ovl0C_10_80045FD8(void);
void func_ovl0C_10_80045FE0(void);
s32 func_ovl0C_10_80046020(s32);
void func_ovl0C_10_80046038(s32);
void func_ovl0C_10_80046108(s32, s32, s32);
void func_ovl0C_10_80046208(s32, f32, f32, f32, s32);
void func_ovl0C_10_80046340(s32);
void func_ovl0C_10_80046350(s32);
void func_ovl0C_10_80046358(void);
void func_ovl0C_10_80046360(s32, f32, f32, f32);
void func_ovl0C_10_800463E8(s32, s32, s32, s32, s32);
void func_ovl0C_10_80046408(s32);
void func_ovl0C_10_800464B8(void);
void func_ovl0C_10_800464C0(void);

void func_ovl0C_10_80043078(void);
void func_ovl0C_10_800430D0(void);
void func_ovl0C_10_80043144(void);
void func_ovl0C_10_800431DC(void);
void func_ovl0C_10_80043278(void);
void func_ovl0C_10_800432F0(void);
void func_ovl0C_10_80043330(void);
void func_ovl0C_10_80043368(void);
void func_ovl0C_10_80043450(s32);
void func_ovl0C_10_80043C0C(UnkStructA *);
void func_ovl0C_10_80043CD4(void);
void func_ovl0C_10_80043CFC(void);
void func_ovl0C_10_80043D44(f32);
void func_ovl0C_10_80043D8C(void);
void func_ovl0C_10_80043EBC(void);
void func_ovl0C_10_80043F04(s32, s32, s32, f32, s32);
void func_ovl0C_10_80043F2C(UnkStructA *);
void func_ovl0C_10_80043F70(void);
void func_ovl0C_10_800447A4(void);
void func_ovl0C_10_800447E4(void);
void func_ovl0C_10_800448C0(void);
void func_ovl0C_10_80044A08(void);
void func_ovl0C_10_80044B90(void);
void func_ovl0C_10_80044C30(UnkStructA *, s32, s32, f32, f32);
void func_ovl0C_10_80044D08(void);
void func_ovl0C_10_80044E18(s32, UnkStructA *);
void func_ovl0C_10_80044E4C(f32, f32, f32);
void func_ovl0C_10_80044EA8(void);
void func_ovl0C_10_80044EC0(void);
static f32 func_ovl0C_10_80043010(UnkStructA_40 *from, UnkStructA_40 *to);
static void func_ovl0C_10_80043070(void);
static void func_ovl0C_10_80043CCC(void);
static void func_ovl0C_10_80043CF4(void);

/* an angle in degrees moved by d and kept in [0, 360) */
#define ANGLE_ADD(a, d) \
    (a) = ((a) + (d) >= 360.0f) ? (a) + (d) - 360.0f : ((a) + (d) < 0.0f) ? (a) + (d) + 360.0f : (a) + (d)
#define ANGLE_SUB(a, d) \
    (a) = ((a) - (d) >= 360.0f) ? (a) - (d) - 360.0f : ((a) < (d)) ? (a) - (d) + 360.0f : (a) - (d)

/* .bss */
u8 D_ovl0C_10_80046670[0x10];
Vec3f D_ovl0C_10_80046680;
s32 D_ovl0C_10_8004668C;
u8 D_ovl0C_10_80046690[0x4]; /* unused (func_ovl0C_10_80044EC0) */
s32 D_ovl0C_10_80046694;
s32 D_ovl0C_10_80046698;
u8 D_ovl0C_10_8004669C[0x4]; /* unused (func_ovl0C_10_80044EC0) */
Vec3f D_ovl0C_10_800466A0;
UnkStructA *D_ovl0C_10_800466AC; /* unused (func_ovl0C_10_80044EC0) */
UnkStruct_ovl0C_10_800466B0 D_ovl0C_10_800466B0;
s32 D_ovl0C_10_800466C4;
s32 D_ovl0C_10_800466C8;
s32 D_ovl0C_10_800466CC;
UnkStructC *D_ovl0C_10_800466D0;

/* .data */
UnkStruct_ovl0C_10_80046560 D_ovl0C_10_80046560[] = {
    { 110.0f, { 410.0f, 347.0f, 1380.0f }, { 2400.0f, 450.0f, 1450.0f } },
    { 100.0f, { -453.0f, 2469.0f, 122.0f }, { -453.0f, 2469.0f, 122.0f } },
};

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0C_10_80044F10(void) {
}

static void func_ovl0C_10_80044F08(void) {
}

static void func_ovl0C_10_80044F00(void) {
}

static void func_ovl0C_10_80044EF8(void) {
}

static void func_ovl0C_10_80044EF0(void) {
}

static void func_ovl0C_10_80044EE8(void) {
}

static void func_ovl0C_10_80044EE0(void) {
}

static void func_ovl0C_10_80044ED8(void) {
}

static void func_ovl0C_10_80044ED0(void) {
}

static void func_ovl0C_10_80044EC8(void) {
}

void func_ovl0C_10_80044EC0(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl0C_10_80046690[0] = D_ovl0C_10_8004669C[0];
        D_ovl0C_10_800466AC = NULL;
    }
}

void func_ovl0C_10_80044EA8(void) {
    D_ovl0C_10_80046694 = -1;
    D_ovl0C_10_80046698 = -1;
}

void func_ovl0C_10_80044E4C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_10_80045AA8(D_ovl0C_10_800466A0.x, D_ovl0C_10_800466A0.y, D_ovl0C_10_800466A0.z);
    func_ovl0C_10_80045AC8(arg0, arg1, arg2);
    func_ovl0C_10_80045DD8(180);
}

void func_ovl0C_10_80044E18(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_10_80046360(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_10_80044D08(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_10_80045DE0();
    func_ovl0C_10_80046360(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_10_80045C90(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_10_80044C30(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_10_80045E00();
    }
    func_ovl0C_10_80045C80(obj);
    func_ovl0C_10_80045DC8();
}

void func_ovl0C_10_80044C30(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0C_10_80045F60((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_10_80045F60((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

/* a task: moves the object it is given along its angle */
void func_ovl0C_10_80044B90(void) {
    UnkStructA_40 *p;
    f32 s;
    f32 c;

    p = ((UnkStructA *) func_ovl0C_10_80045DE0())->unk40;
    while (TRUE) {
        s = func_ovl0C_10_80045F60(p->unk20);
        c = func_ovl0C_10_80045F68(p->unk20);
        p->unk10 += s * 40.0f;
        p->unk18 += c * 40.0f;
        func_ovl0C_10_80045E00();
    }
}

/* a task: the camera follows the object it is given; the player faces it */
void func_ovl0C_10_80044A08(void) {
    UnkStructA *player;
    UnkStructA_40 *p;
    f32 pad0;
    Vec3f target;
    Vec3f pos;
    f32 pad[2];
    f32 angle;

    player = func_ovl0C_10_800454A8(0);
    p = ((UnkStructA *) func_ovl0C_10_80045DE0())->unk40;
    target.x = 2350.0f;
    target.z = 1530.0f;
    target.y = 0.0f;
    while (TRUE) {
        func_ovl0C_10_80045AA8(p->unk10, p->unk14 + 20.0f, p->unk18);
        pos.x = p->unk10;
        pos.y = p->unk14;
        pos.z = p->unk18;
        func_ovl0C_10_80045BF8(&pos.x, &target.x, &angle);
        player->unk40->unk20 = (180.0f + angle >= 360.0f) ? 180.0f + angle - 360.0f : (180.0f + angle < 0.0f) ? 180.0f + angle + 360.0f : 180.0f + angle;
        func_ovl0C_10_80045E00();
    }
}

/* a task: the camera's moves in D_ovl0C_10_80046560 */
void func_ovl0C_10_800448C0(void) {
    UnkStruct_ovl0C_10_80046560 *p;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 n;
    s32 j;

    func_ovl0C_10_80045A98(0);
    for (j = 0; j < 2; j++) {
        p = &D_ovl0C_10_80046560[j];
        x = p->unk4.x;
        n = p->unk0;
        y = p->unk4.y;
        z = p->unk4.z;
        for (i = 0; i < n; i++) {
            x += (p->unk10.x - p->unk4.x) / n;
            y += (p->unk10.y - p->unk4.y) / n;
            z += (p->unk10.z - p->unk4.z) / n;
            func_ovl0C_10_80045AB8(x, y, z);
            func_ovl0C_10_80045E00();
        }
    }
    func_ovl0C_10_80045DC8();
}

/* a task: bobs the object it is given up and down */
void func_ovl0C_10_800447E4(void) {
    UnkStructA *obj;
    f32 angle;

    obj = func_ovl0C_10_80045DE0();
    angle = 0.0f;
    while (TRUE) {
        obj->unk40->unk14 += func_ovl0C_10_80045F68(angle) * 2.0f;
        ANGLE_ADD(angle, 5.0f);
        func_ovl0C_10_80045E00();
    }
}

void func_ovl0C_10_80043144(void) {
    if (D_ovl0C_10_800466C4 != 0x1A && D_ovl0C_10_800466C4 != 0x1B) {
        func_ovl0C_10_80045DB8(func_ovl0C_10_800447A4, NULL, 0, 0, 0x130);
    }
    if (D_ovl0C_10_800466C4 == 0x10 || D_ovl0C_10_800466C4 == 0x1A || D_ovl0C_10_800466C4 == 0x1B) {
        func_ovl0C_10_80045DB8(func_ovl0C_10_80043F70, &D_ovl0C_10_800466C8, 0, 0, 0x130);
    }
}

void func_ovl0C_10_800447A4(void) {
    if (D_ovl0C_10_800466C4 != 0x10) {
        func_ovl0C_10_80045DD8(45);
        func_ovl0C_10_80046350(0x12);
    }
    func_ovl0C_10_80045DC8();
}

void func_ovl0C_10_80043F2C(UnkStructA *arg0) {
    func_ovl0C_10_80045C70(arg0, 0x01000000);
    func_ovl0C_10_80045DB8(func_ovl0C_10_80044D08, arg0, 0, 0, 0x150);
}

void func_ovl0C_10_80043F70(void) {
    s32 *flag;
    s32 task1;
    s32 task2;
    f32 dx;
    f32 dy;
    f32 dz;
    UnkStruct_ovl0C_10_80045DB0 snd;
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 i;

    flag = func_ovl0C_10_80045DE0();
    obj = func_ovl0C_10_80045C90(0x328, 0x01000000, 0xC0, 0);
    func_ovl0C_10_80045C70(obj, 0x04000000);
    func_ovl0C_10_80045CA0(obj);
    p = obj->unk40;
    p->unk10 = 5000.0f;
    p->unk14 = 300.0f;
    p->unk18 = 2000.0f;
    p->unk20 = 270.0f;
    task1 = func_ovl0C_10_80045DB8(func_ovl0C_10_80044B90, obj, 0, 0, 0x130);
    task2 = func_ovl0C_10_80045DB8(func_ovl0C_10_80044A08, obj, 0, 0, 0x130);
    func_ovl0C_10_80045DB8(func_ovl0C_10_800448C0, NULL, 0, 0, 0x130);
    p->unkC |= 0x40;
    func_ovl0C_10_80045990(p, 0x16, 0);
    p->unk48->unk4->unk4 = func_ovl0C_10_800459A8(p, 0) - 0.01f;
    snd.unk0 = p;
    snd.unk4 = 0x20D;
    snd.unk8 = 0xFA;
    func_ovl0C_10_80045DB0(&snd);
    while (p->unk10 > 128.0f) {
        func_ovl0C_10_80045E00();
    }
    while (p->unk20 > 90.0f) {
        p->unk20 -= 2.5f;
        func_ovl0C_10_80045E00();
    }
    p->unk20 = 90.0f;
    while (p->unk10 < 1800.0f) {
        func_ovl0C_10_80045E00();
    }
    snd.unk0 = p;
    snd.unk4 = 0x213;
    snd.unk8 = 0x3C;
    func_ovl0C_10_80045DB0(&snd);
    func_ovl0C_10_80045AB8(2581.0f, 223.0f, 1909.0f);
    if (D_ovl0C_10_800466C4 != 0x1A && D_ovl0C_10_800466C4 != 0x1B) {
        func_ovl0C_10_80046350(10);
    }
    if (D_ovl0C_10_800466C4 != 0x1B) {
        for (i = 0; i < 20; i++) {
            ANGLE_SUB(p->unk20, 4.5f);
            func_ovl0C_10_80045E00();
        }
        p->unk20 = 0.0f;
    }
    func_ovl0C_10_80045DC0(task1);
    if (D_ovl0C_10_800466C4 == 0x1B) {
        dx = (2350.0f - p->unk10) / 50.0f;
        dy = (-42.0f - p->unk14) / 50.0f;
        dz = (818.0f - p->unk18) / 50.0f;
    } else {
        dx = (2350.0f - p->unk10) / 50.0f;
        dy = (0.0f - p->unk14) / 50.0f;
        dz = (1300.0f - p->unk18) / 50.0f;
    }
    func_ovl0C_10_80046360(0x211, p->unk10, p->unk14, p->unk18);
    if (D_ovl0C_10_800466C4 == 0x1B) {
        func_ovl0C_10_80045AB8(3386.0f, 619.0f, 15.0f);
        p->unk20 = 0.0f;
    }
    for (i = 0; i < 50; i++) {
        p->unk48->unk4->unk4 -= func_ovl0C_10_800459A8(p, 0) / 50.0f;
        if (p->unk48->unk4->unk4 < 0.0f) {
            p->unk48->unk4->unk4 = 0.0f;
        }
        p->unk10 += dx;
        p->unk14 += dy;
        p->unk18 += dz;
        func_ovl0C_10_80045AA8(p->unk10, p->unk14, p->unk18);
        func_ovl0C_10_80045E00();
    }
    if (D_ovl0C_10_800466C4 == 0x1B) {
        p->unk20 = 0.0f;
        func_ovl0C_10_80046208(0, p->unk10, p->unk14 + 50.0f, p->unk18, 0);
        obj->unk68 = 0.0f;
        obj->unk70 = 0.8166667f;
        obj->unk6C = 16.333334f;
        while (obj->unk40->unk14 > -460.0f) {
            obj->unk40->unk18 -= 20.0f;
            obj->unk40->unk14 -= obj->unk6C;
            obj->unk6C += obj->unk70;
            func_ovl0C_10_80045E00();
        }
        func_ovl0C_10_80043F2C(obj);
        func_ovl0C_10_80045DD8(30);
        obj = func_ovl0C_10_800454A8(0);
        func_ovl0C_10_80045DC0(task2);
        func_ovl0C_10_80045AA8(obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18);
        func_ovl0C_10_80045A98(1);
        func_ovl0C_10_80045AC8(obj->unk40->unk20, 20.0f, 800.0f);
        func_ovl0C_10_80045DD8(10);
        func_ovl0C_10_80045490(0x20000);
        func_ovl0C_10_80045DD8(30);
        func_ovl0C_10_800464B8();
        D_ovl0C_10_800466C8 = 0;
        func_ovl0C_10_80045DC8();
    }
    func_ovl0C_10_80045DD8(30);
    func_ovl0C_10_80045DC0(task2);
    p->unk20 = 0.0f;
    if (D_ovl0C_10_800466C4 == 0x1A) {
        func_ovl0C_10_80045A98(1);
        func_ovl0C_10_80045AA8(2407.0f, 10.0f, 1630.0f);
        func_ovl0C_10_80045AC8(203.0f, 15.0f, 999.0f);
        func_ovl0C_10_800464B8();
        D_ovl0C_10_800466C8 = 0;
        func_ovl0C_10_80045DC8();
    }
    func_ovl0C_10_80045A98(1);
    func_ovl0C_10_80045AA8(2350.0f, 100.0f, 1630.0f);
    func_ovl0C_10_80045AC8(0.0f, 45.0f, 1180.0f);
    func_ovl0C_10_80045DD8(30);
    if (func_ovl0C_10_80046020(0xA4) != 0) {
        i = 0x332;
    } else {
        i = 0x330;
    }
    func_ovl0C_10_800459F8(i, 1, 180);
    func_ovl0C_10_80045DD8(30);
    func_ovl0C_10_80045C80(obj);
    func_ovl0C_10_800463E8(1, 0, 0x17, 0, 0xD);
    func_ovl0C_10_800454A8(1)->unk40->unk10 += 50.0f;
    func_ovl0C_10_80045460(0);
    func_ovl0C_10_80045478();
    func_ovl0C_10_800453F0(0x31, 0x11);
    *flag = 0;
    func_ovl0C_10_80045DC8();
}

void func_ovl0C_10_80043F04(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0C_10_800466B0.unk0 = arg0;
    D_ovl0C_10_800466B0.unk4 = arg1;
    D_ovl0C_10_800466B0.unk8 = arg2;
    D_ovl0C_10_800466B0.unkC = arg3;
    D_ovl0C_10_800466B0.unk10 = arg4;
}

void func_ovl0C_10_80043EBC(void) {
    func_ovl0C_10_80045468(D_ovl0C_10_800466B0.unk4, 3, 4.0f, D_ovl0C_10_800466B0.unk10, 0, 1, 1);
}

void func_ovl0C_10_80043D8C(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_10_80045478();
    switch (D_ovl0C_10_800466B0.unk8) {
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
        func_ovl0C_10_80045AC8(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_10_800466B0.unkC;
        func_ovl0C_10_80045AD0(&sp1C, NULL, NULL);
        func_ovl0C_10_80045AC8(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_10_80045460(D_ovl0C_10_800466B0.unk4);
    func_ovl0C_10_80045B60(45.0f, 45.1f);
}

void func_ovl0C_10_80043D44(f32 arg0) {
    f32 sp1C;

    func_ovl0C_10_80045AD0(&sp1C, NULL, NULL);
    func_ovl0C_10_80045AC8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0C_10_80043CFC(void) {
    func_ovl0C_10_80043CF4();
    D_ovl0C_10_8004668C = func_ovl0C_10_80045448();
    func_ovl0C_10_80045428(&D_ovl0C_10_80046680);
    func_ovl0C_10_80045450(D_ovl0C_10_8004668C, D_ovl0C_10_80046670);
}

static void func_ovl0C_10_80043CF4(void) {
}

void func_ovl0C_10_80043CD4(void) {
    func_ovl0C_10_80043CCC();
    func_ovl0C_10_800454B0(1);
}

static void func_ovl0C_10_80043CCC(void) {
}

void func_ovl0C_10_80043C0C(UnkStructA *arg0) {
    func_ovl0C_10_80045DD8(10);
    func_ovl0C_10_800452F0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_10_80045DD8(60);
}

void func_ovl0C_10_80043368(void) {
    func_ovl0C_10_80043330();
    func_ovl0C_10_80045268(0x24B);
    func_ovl0C_10_80045280(0x255);
    func_ovl0C_10_80045418();
    func_ovl0C_10_80046108(0x37, 0x4D, 0xFF);
    D_ovl0C_10_800466D0 = func_ovl0C_10_80045E40(0x296);
    func_ovl0C_10_80045E50(D_ovl0C_10_800466D0, 0x20000000);
    D_ovl0C_10_800466D0->unk40 = 0.5f;
    D_ovl0C_10_800466D0->unk44 = D_ovl0C_10_800466D0->unk40 * 0.75f;
    D_ovl0C_10_800466D0->unk3C = D_ovl0C_10_800466D0->unk4C * 0.25f;
    D_ovl0C_10_800466C8 = 1;
    D_ovl0C_10_800466CC = 0;
    func_ovl0C_10_80045FD8();
}

void func_ovl0C_10_80043330(void) {
    func_ovl0C_10_800432F0();
    func_ovl0C_10_80045350(func_ovl0C_10_80043F2C);
    func_ovl0C_10_800453A0(func_ovl0C_10_80043C0C);
}

void func_ovl0C_10_800432F0(void) {
    func_ovl0C_10_80046038(0x400);
    func_ovl0C_10_80046038(0x401);
    func_ovl0C_10_80046038(0x402);
    func_ovl0C_10_80046038(0x403);
    func_ovl0C_10_80046038(0x404);
}

void func_ovl0C_10_80043278(void) {
    func_ovl0C_10_800454A8(0)->unk40->unk10 += 50.0f;
    func_ovl0C_10_80045458(1);
    func_ovl0C_10_80045B10(0x1F);
    func_ovl0C_10_80045AA8(2350.0f, 0.0f, 1530.0f);
    func_ovl0C_10_80045AC8(270.0f, 10.0f, 2000.0f);
}

void func_ovl0C_10_800431DC(void) {
    func_ovl0C_10_800454A8(0)->unk40->unk10 += 50.0f;
    func_ovl0C_10_800463E8(1, 0, 0x17, 0, 0xD);
    func_ovl0C_10_800454A8(1)->unk40->unk10 += 50.0f;
    func_ovl0C_10_80045AC8(0.0f, 45.0f, 1500.0f);
    func_ovl0C_10_80045460(0);
    func_ovl0C_10_80045478();
}

void func_ovl0C_10_800430D0(void) {
    if (D_ovl0C_10_800466C4 == 0x10 || D_ovl0C_10_800466C4 == 0x1A || D_ovl0C_10_800466C4 == 0x1B) {
        while (D_ovl0C_10_800466C8 != 0) {
            func_ovl0C_10_80045E00();
        }
        func_ovl0C_10_80045458(0);
    }
}

void func_ovl0C_10_80043078(void) {
    func_ovl0C_10_80043070();
    if (D_ovl0C_10_800466C4 == 0x1A || D_ovl0C_10_800466C4 == 0x1B) {
        func_ovl0C_10_800464C0();
    }
    if (D_ovl0C_10_800466CC == 0) {
        func_ovl0C_10_80045FE0();
    }
}

static void func_ovl0C_10_80043070(void) {
}

/* A static: its callers pass `from` in a3 and `to` in t0. */
static f32 func_ovl0C_10_80043010(UnkStructA_40 *from, UnkStructA_40 *to) {
    Vec3f a;
    Vec3f b;
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;

    a.x = from->unk10;
    a.y = from->unk14;
    a.z = from->unk18;
    b.x = to->unk10;
    b.y = to->unk14;
    b.z = to->unk18;
    func_ovl0C_10_80045BF8(&a.x, &b.x, &angle);
    return angle;
}
/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0C_10_80043450(s32 arg0) {
    UnkStructA *obj;
    UnkStructA *obj1;
    UnkStructA *obj0;
    UnkStruct_ovl0C_10_80045DB0 snd;
    s32 task;
    s32 flag;
    Vec3f pos;
    Vec3f target;
    f32 angle;
    s32 i;
    f32 d;

    switch (arg0) {
        case 2:
            D_ovl0C_10_800466C4 = func_ovl0C_10_80045368();
            func_ovl0C_10_80043368();
            break;
        case 16:
        case 26:
        case 27:
            func_ovl0C_10_80043278();
            break;
        case 17:
            func_ovl0C_10_800431DC();
            break;
        case 4:
            func_ovl0C_10_80043144();
            break;
        case 5:
            func_ovl0C_10_800430D0();
            break;
        case 1:
            func_ovl0C_10_80043078();
            break;
        case 11:
            func_ovl0C_10_80045458(1);
            func_ovl0C_10_80045B10(0x1F);
            func_ovl0C_10_80046408(0);
            func_ovl0C_10_80045AA8(2350.0f, 100.0f, 1720.0f);
            func_ovl0C_10_80045AC8(0.0f, 45.0f, 2000.0f);
            func_ovl0C_10_80045DD8(2);
            obj1 = func_ovl0C_10_800454A8(1);
            obj0 = func_ovl0C_10_800454A8(0);
            func_ovl0C_10_80045C70(obj1, 0x0C000000);
            func_ovl0C_10_80045990(obj1->unk40, 0, 0);
            func_ovl0C_10_80045990(obj1->unk40, -1, 1);
            func_ovl0C_10_80045C70(obj1, 0x05000000);
            obj = func_ovl0C_10_80045C90(0x328, 0x01000000, 0xC0, 0);
            func_ovl0C_10_80045C70(obj, 0x04000000);
            func_ovl0C_10_80045CA0(obj);
            obj->unk40->unk10 = obj1->unk40->unk10;
            obj->unk40->unk14 = obj1->unk40->unk14;
            obj->unk40->unk18 = obj1->unk40->unk18;
            obj->unk40->unk20 = func_ovl0C_10_80043010(obj->unk40, obj0->unk40);
            if (func_ovl0C_10_80045400(1) == 3) {
                snd.unk0 = obj->unk40;
                snd.unk4 = 0x213;
                snd.unk8 = 0x3C;
                func_ovl0C_10_80045DB0(&snd);
                pos.x = obj0->unk40->unk10;
                pos.y = obj0->unk40->unk14;
                pos.z = obj0->unk40->unk18;
                target.x = 2350.0f;
                target.y = 0.0f;
                target.z = 1550.0f;
                func_ovl0C_10_80045BF8(&pos.x, &target.x, &angle);
                target.x = func_ovl0C_10_80045F60(angle) * 800.0f + pos.x;
                target.y = pos.y;
                target.z = func_ovl0C_10_80045F68(angle) * 800.0f + pos.z;
                pos.x = obj->unk40->unk10;
                pos.y = obj->unk40->unk14;
                pos.z = obj->unk40->unk18;
                func_ovl0C_10_80045BF8(&pos.x, &target.x, &angle);
                func_ovl0C_10_80045C10(&pos.x, &target.x);
                obj->unk68 = 51.0f;
                obj->unk40->unk14 = 0.1f;
                obj->unk70 = 0.8166667f;
                obj->unk6C = 16.333334f;
                for (i = 0; i < 90; i++) {
                    obj->unk40->unk10 += (target.x - pos.x) / 90.0f;
                    obj->unk40->unk18 += (target.z - pos.z) / 90.0f;
                    if (obj->unk40->unk14 < 0.0f) {
                        obj->unk70 = 0.0f;
                        obj->unk68 = 0.0f;
                        obj->unk40->unk14 = 0.0f;
                    } else {
                        func_ovl0C_10_80045CE8(obj);
                    }
                    func_ovl0C_10_80045E00();
                }
                func_ovl0C_10_80046340(0x259);
            }
            obj->unk40->unk20 = func_ovl0C_10_80043010(obj->unk40, obj0->unk40);
            obj0->unk40->unk20 = func_ovl0C_10_80043010(obj0->unk40, obj->unk40);
            func_ovl0C_10_80045AA8(obj->unk40->unk10, 200.0f, obj->unk40->unk18);
            func_ovl0C_10_80045AC8(obj0->unk40->unk20, 20.0f, 800.0f);
            for (i = 0; i < 30; i++) {
                obj->unk40->unk14 += 2.0f;
                func_ovl0C_10_80045E00();
            }
            func_ovl0C_10_80045DD8(30);
            task = func_ovl0C_10_80045DB8(func_ovl0C_10_800447E4, obj, 0, 0, 0x130);
            if (func_ovl0C_10_80046020(0xA4) != 0) {
                i = 0x333;
            } else {
                i = 0x331;
            }
            func_ovl0C_10_800459D0(i, 1);
            func_ovl0C_10_80045458(1);
            func_ovl0C_10_80045DD8(30);
            func_ovl0C_10_80045408(50);
            func_ovl0C_10_80046358();
            func_ovl0C_10_80045DC0(task);
            func_ovl0C_10_80046360(0x211, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
            func_ovl0C_10_80045990(obj->unk40, 0x16, 0);
            func_ovl0C_10_80045C68(obj, 0x04000000);
            func_ovl0C_10_80045C70(obj, 0x08000000);
            while (!(obj->unk40->unkC & 0x40)) {
                func_ovl0C_10_80045E00();
            }
            snd.unk0 = obj->unk40;
            snd.unk4 = 0x20F;
            snd.unk8 = 0x44;
            func_ovl0C_10_80045DB0(&snd);
            flag = TRUE;
            for (i = 0; i < 120; i++) {
                obj->unk40->unk10 += func_ovl0C_10_80045F60(obj->unk40->unk20) * 40.0f;
                obj->unk40->unk18 += func_ovl0C_10_80045F68(obj->unk40->unk20) * 40.0f;
                obj->unk40->unk14 += 5.0f;
                d = obj->unk40->unk10 < obj0->unk40->unk10 ? -(obj->unk40->unk10 - obj0->unk40->unk10)
                                                            : obj->unk40->unk10 - obj0->unk40->unk10;
                if (d < 20.0f && flag) {
                    flag = FALSE;
                    ANGLE_ADD(obj0->unk40->unk20, 180.0f);
                }
                func_ovl0C_10_80045E00();
            }
            obj = func_ovl0C_10_800454A8(0);
            func_ovl0C_10_80045AA8(obj->unk40->unk10, 50.0f, obj->unk40->unk18);
            func_ovl0C_10_80045AC8(obj->unk40->unk20, 20.0f, 800.0f);
            func_ovl0C_10_80045458(0);
            func_ovl0C_10_80045408(32);
            func_ovl0C_10_80045FE0();
            D_ovl0C_10_800466CC = 1;
            break;
    }
}

