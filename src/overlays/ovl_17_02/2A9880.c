#include "common.h"

void func_ovl17_02_80044278(f32, f32, f32);
void func_ovl17_02_80044298(f32, f32, f32);
void func_ovl17_02_800442A0(f32 *, f32 *, f32 *);
void func_ovl17_02_800445A8(s32);
void func_ovl17_02_80044B30(s32, f32, f32, f32);

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} UnkStruct_ovl17_02_80044D54;

void func_ovl17_02_8004327C(UnkStructA *);
void func_ovl17_02_80043398(void);
void func_ovl17_02_80043490(void);
void func_ovl17_02_80043A38(s32);
void func_ovl17_02_80043A50(s32);
f32 func_ovl17_02_80043A60(void);
void func_ovl17_02_80043A68(f32);
void func_ovl17_02_80043B20(void (*)(UnkStructA *));
void func_ovl17_02_80043BB0(s32);
UnkStructB *func_ovl17_02_80043BB8(void);
void func_ovl17_02_80043BE8(void);
void func_ovl17_02_80044258(s32);
void func_ovl17_02_80044268(s32);
void func_ovl17_02_80044278(f32, f32, f32);
void func_ovl17_02_80044298(f32, f32, f32);
void func_ovl17_02_800442E0(s32);
void func_ovl17_02_80044438(UnkStructA *, s32);
void func_ovl17_02_80044440(UnkStructA *, s32);
void func_ovl17_02_80044450(UnkStructA *);
UnkStructA *func_ovl17_02_80044460(s32, s32, s32, s32);
UnkStructA *func_ovl17_02_80044480(s32, s32, f32, f32, f32);
void func_ovl17_02_80044588(void (*)(void), void *, s32, s32, s32);
void func_ovl17_02_80044598(void);
void *func_ovl17_02_800445B0(void);
void func_ovl17_02_800445D0(void);
f32 func_ovl17_02_80044730(f32);
void func_ovl17_02_80044888(s32, s32, s32, f32);
void func_ovl17_02_800448F0(u32 (*)[3]);

/* .bss */
u8 D_ovl17_02_80044DC0[0x24];
s32 D_ovl17_02_80044DE4;
s32 D_ovl17_02_80044DE8;
u8 D_ovl17_02_80044DEC[0x4]; /* not referenced here */
Vec3f D_ovl17_02_80044DF0;
u8 D_ovl17_02_80044DFC[0x4]; /* not referenced here */

/* .data */
/* passed to func_ovl17_02_800448F0: three 12-byte records */
u32 D_ovl17_02_80044D30[][3] = {
    { 0xD40000, 0xC000C, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
UnkStruct_ovl17_02_80044D54 D_ovl17_02_80044D54 = { NULL, 0x204, 0.0f, 0.0f, 0.0f, 800.0f };

void func_ovl17_02_80043010(void) {
    UnkStructB *b;

    b = func_ovl17_02_80043BB8();
    if (b->unk38 == 1 && b->unk0 == 0) {
        func_ovl17_02_80044588(func_ovl17_02_80043490, NULL, 0, 0, 0x110);
    }
}

UnkStructA *func_ovl17_02_80043068(void) {
    UnkStructA *obj;

    D_ovl17_02_80044D54.unkC = func_ovl17_02_80043A60() + 200.0f;
    obj = func_ovl17_02_80044480(D_ovl17_02_80044D54.unk4, 0xD0, D_ovl17_02_80044D54.unk8,
                                 D_ovl17_02_80044D54.unkC, D_ovl17_02_80044D54.unk10);
    func_ovl17_02_80044438(obj, 0x01000000);
    D_ovl17_02_80044D54.unk0 = obj;
    return obj;
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl17_02_800430D8(s32 arg0) {
    UnkStructA *obj;
    UnkStructA *obj2;

    switch (arg0) {
        case 2:
            func_ovl17_02_800448F0(D_ovl17_02_80044D30);
            func_ovl17_02_80043A38(0x202);
            obj = func_ovl17_02_80044460(0x203, 0x01000000, 0xD0, 0);
            obj->unk40->unk10 = 0.0f;
            obj->unk40->unk14 = 0.0f;
            obj->unk40->unk18 = 0.0f;
            func_ovl17_02_80043A50(0x21A);
            func_ovl17_02_80043BE8();
            func_ovl17_02_80043BB0(0);
            func_ovl17_02_800442E0(0x7F);
            func_ovl17_02_80044258(1);
            func_ovl17_02_80044268(1);
            func_ovl17_02_80044278(2365.0f, 350.0f, 1354.0f);
            func_ovl17_02_80044298(0.0f, 42.6f, 3600.0f);
            obj2 = func_ovl17_02_80043068();
            func_ovl17_02_80044438(obj2, 0x80000);
            obj2->unk40->unk36 = 0x99;
            func_ovl17_02_80043B20(func_ovl17_02_8004327C);
            break;
        case 3:
        case 4:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            break;
        case 5:
            func_ovl17_02_80043010();
            break;
        case 1:
            func_ovl17_02_80044888(0, 0, 0, 0.0f);
            break;
        case 0x50:
            break;
        case 0x51:
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl17_02_8004327C(UnkStructA *arg0) {
    func_ovl17_02_80044440(arg0, 0x01000000);
    func_ovl17_02_80044588(func_ovl17_02_80043398, arg0, 0, 0, 0x150);
}

void func_ovl17_02_800432C0(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    /* the ratio is spelled out three times: with a variable for it, IDO
     * spills it to another stack slot */
    arg0->unk40->unk28 = func_ovl17_02_80044730((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl17_02_80044730((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl17_02_80043398(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl17_02_800445B0();
    obj = func_ovl17_02_80044460(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl17_02_800432C0(obj, i, count, 2.0f, 4.0f);
        func_ovl17_02_800445D0();
    }
    func_ovl17_02_80044450(obj);
    func_ovl17_02_80044598();
}

void func_ovl17_02_80043490(void) {
    UnkStructB *b;
    f32 base;
    f32 acc;
    f32 step;
    f32 x;

    b = func_ovl17_02_80043BB8();
    while (TRUE) {
        if (b->unk2C <= 0) {
            break;
        }
        func_ovl17_02_800445D0();
    }
    base = func_ovl17_02_80043A60();
    acc = 0;
    step = (D_ovl17_02_80044D54.unk14 - base) / 3600.0f;
    while (TRUE) {
        x = base + acc;
        func_ovl17_02_80043A68(x);
        D_ovl17_02_80044D54.unk0->unk40->unk14 = D_ovl17_02_80044D54.unkC + acc;
        if (D_ovl17_02_80044D54.unk14 < x) {
            func_ovl17_02_80044598();
        }
        acc += step;
        func_ovl17_02_800445D0();
    }
}

void func_ovl17_02_800435A0(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01: without it arg1 is spilled */
    }
    func_ovl17_02_80044B30(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl17_02_800435D4(f32 arg0) {
    f32 sp1C;

    func_ovl17_02_800442A0(&sp1C, NULL, NULL);
    func_ovl17_02_80044298(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl17_02_8004361C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl17_02_80044278(D_ovl17_02_80044DF0.x, D_ovl17_02_80044DF0.y, D_ovl17_02_80044DF0.z);
    func_ovl17_02_80044298(arg0, arg1, arg2);
    func_ovl17_02_800445A8(180);
}

void func_ovl17_02_80043678(void) {
    D_ovl17_02_80044DE4 = -1;
    D_ovl17_02_80044DE8 = -1;
}

void func_ovl17_02_80043690(void) {
}

void func_ovl17_02_80043698(void) {
}

void func_ovl17_02_800436A0(void) {
}

void func_ovl17_02_800436A8(void) {
}

void func_ovl17_02_800436B0(void) {
}

void func_ovl17_02_800436B8(void) {
}

void func_ovl17_02_800436C0(void) {
}

void func_ovl17_02_800436C8(void) {
}

void func_ovl17_02_800436D0(void) {
}

void func_ovl17_02_800436D8(void) {
}

void func_ovl17_02_800436E0(void) {
}

void func_ovl17_02_800436E8(void) {
}
