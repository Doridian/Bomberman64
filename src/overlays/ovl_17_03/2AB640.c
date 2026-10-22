#include "common.h"

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} UnkStruct_ovl17_03_80044DD4;

UnkStructA *func_ovl17_03_80043068(void);
void func_ovl17_03_800432F8(UnkStructA *);
void func_ovl17_03_80043AB8(s32);
void func_ovl17_03_80043AD0(s32);
void func_ovl17_03_80043AE8(f32);
void func_ovl17_03_80043BA0(void (*)(UnkStructA *));
void func_ovl17_03_80043C30(s32);
void func_ovl17_03_80043C68(void);
void func_ovl17_03_800442D8(s32);
void func_ovl17_03_800442E8(s32);
void func_ovl17_03_80044360(s32);
UnkStructC *func_ovl17_03_80044690(s32);
void func_ovl17_03_800446A0(UnkStructC *, s32);
void func_ovl17_03_800447D0(f32, f32);
void func_ovl17_03_80044908(s32, s32, s32, f32);
void func_ovl17_03_80044970(u32 (*)[3]);

void func_ovl17_03_80043414(void);
void func_ovl17_03_8004350C(void);
f32 func_ovl17_03_80043AE0(void);
UnkStructB *func_ovl17_03_80043C38(void);
void func_ovl17_03_800442F8(f32, f32, f32);
void func_ovl17_03_80044318(f32, f32, f32);
void func_ovl17_03_80044320(f32 *, f32 *, f32 *);
void func_ovl17_03_800444B8(UnkStructA *, s32);
void func_ovl17_03_800444C0(UnkStructA *, s32);
void func_ovl17_03_800444D0(UnkStructA *);
UnkStructA *func_ovl17_03_800444E0(s32, s32, s32, s32);
UnkStructA *func_ovl17_03_80044500(s32, s32, f32, f32, f32);
void func_ovl17_03_80044608(void (*)(void), void *, s32, s32, s32);
void func_ovl17_03_80044618(void);
void func_ovl17_03_80044628(s32);
void *func_ovl17_03_80044630(void);
void func_ovl17_03_80044650(void);
f32 func_ovl17_03_800447B0(f32);
void func_ovl17_03_80044BB0(s32, f32, f32, f32);

/* .bss */
u8 D_ovl17_03_80044E40[0x24];
s32 D_ovl17_03_80044E64;
s32 D_ovl17_03_80044E68;
u8 D_ovl17_03_80044E6C[0x4]; /* not referenced here */
Vec3f D_ovl17_03_80044E70;
UnkStructC *D_ovl17_03_80044E7C;

/* .data */
/* passed to func_ovl17_03_80044970: three 12-byte records */
u32 D_ovl17_03_80044DB0[][3] = {
    { 0xD50000, 0x10000C, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
UnkStruct_ovl17_03_80044DD4 D_ovl17_03_80044DD4 = { NULL, 0x207, 0.0f, 0.0f, 0.0f, 500.0f };

void func_ovl17_03_80043010(void) {
    UnkStructB *b;

    b = func_ovl17_03_80043C38();
    if (b->unk38 == 1 && b->unk0 == 0) {
        func_ovl17_03_80044608(func_ovl17_03_8004350C, NULL, 0, 0, 0x110);
    }
}

UnkStructA *func_ovl17_03_80043068(void) {
    UnkStructA *obj;

    D_ovl17_03_80044DD4.unkC = func_ovl17_03_80043AE0() + 200.0f;
    obj = func_ovl17_03_80044500(D_ovl17_03_80044DD4.unk4, 0xD0, D_ovl17_03_80044DD4.unk8,
                                 D_ovl17_03_80044DD4.unkC, D_ovl17_03_80044DD4.unk10);
    func_ovl17_03_800444B8(obj, 0x01000000);
    D_ovl17_03_80044DD4.unk0 = obj;
    return obj;
}

void func_ovl17_03_800430D8(s32 arg0) {
    D_ovl17_03_80044E7C = func_ovl17_03_80044690(arg0);
    func_ovl17_03_800446A0(D_ovl17_03_80044E7C, 0x20000000);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl17_03_80043110(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl17_03_80044970(D_ovl17_03_80044DB0);
            func_ovl17_03_80043AB8(0x206);
            func_ovl17_03_80043AD0(0x21B);
            func_ovl17_03_80043C68();
            D_ovl17_03_80044E7C = func_ovl17_03_80044690(0x296);
            func_ovl17_03_800446A0(D_ovl17_03_80044E7C, 0x20000000);
            D_ovl17_03_80044E7C->unk40 = 0.5f;
            D_ovl17_03_80044E7C->unk44 = D_ovl17_03_80044E7C->unk40 * 0.75f;
            D_ovl17_03_80044E7C->unk3C = D_ovl17_03_80044E7C->unk4C * 0.25f;
            func_ovl17_03_80043C30(0);
            func_ovl17_03_80044360(0x7F);
            func_ovl17_03_800442D8(1);
            func_ovl17_03_800442E8(1);
            func_ovl17_03_800442F8(2356.0f, 128.0f, 1274.0f);
            func_ovl17_03_80044318(0.0f, 35.0f, 3201.0f);
            func_ovl17_03_800447D0(100.0f, 45.0f);
            func_ovl17_03_800444B8(func_ovl17_03_80043068(), 0x80000);
            func_ovl17_03_80043BA0(func_ovl17_03_800432F8);
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
            func_ovl17_03_80043010();
            break;
        case 1:
            func_ovl17_03_80044908(0, 0, 0, 0.0f);
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

void func_ovl17_03_800432F8(UnkStructA *arg0) {
    func_ovl17_03_800444C0(arg0, 0x01000000);
    func_ovl17_03_80044608(func_ovl17_03_80043414, arg0, 0, 0, 0x150);
}

void func_ovl17_03_8004333C(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    /* the ratio is spelled out three times: with a variable for it, IDO
     * spills it to another stack slot */
    arg0->unk40->unk28 = func_ovl17_03_800447B0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl17_03_800447B0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl17_03_80043414(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl17_03_80044630();
    obj = func_ovl17_03_800444E0(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl17_03_8004333C(obj, i, count, 2.0f, 4.0f);
        func_ovl17_03_80044650();
    }
    func_ovl17_03_800444D0(obj);
    func_ovl17_03_80044618();
}

void func_ovl17_03_8004350C(void) {
    UnkStructB *b;
    f32 base;
    f32 acc;
    f32 step;
    f32 x;

    b = func_ovl17_03_80043C38();
    while (TRUE) {
        if (b->unk2C <= 0) {
            break;
        }
        func_ovl17_03_80044650();
    }
    base = func_ovl17_03_80043AE0();
    acc = 0;
    step = (D_ovl17_03_80044DD4.unk14 - base) / 3600.0f;
    while (TRUE) {
        x = base + acc;
        func_ovl17_03_80043AE8(x);
        D_ovl17_03_80044DD4.unk0->unk40->unk14 = D_ovl17_03_80044DD4.unkC + acc;
        if (D_ovl17_03_80044DD4.unk14 < x) {
            func_ovl17_03_80044618();
        }
        acc += step;
        func_ovl17_03_80044650();
    }
}

void func_ovl17_03_80043620(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01: without it arg1 is spilled */
    }
    func_ovl17_03_80044BB0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl17_03_80043654(f32 arg0) {
    f32 sp1C;

    func_ovl17_03_80044320(&sp1C, NULL, NULL);
    func_ovl17_03_80044318(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl17_03_8004369C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl17_03_800442F8(D_ovl17_03_80044E70.x, D_ovl17_03_80044E70.y, D_ovl17_03_80044E70.z);
    func_ovl17_03_80044318(arg0, arg1, arg2);
    func_ovl17_03_80044628(180);
}

void func_ovl17_03_800436F8(void) {
    D_ovl17_03_80044E64 = -1;
    D_ovl17_03_80044E68 = -1;
}

void func_ovl17_03_80043710(void) {
}

void func_ovl17_03_80043718(void) {
}

void func_ovl17_03_80043720(void) {
}

void func_ovl17_03_80043728(void) {
}

void func_ovl17_03_80043730(void) {
}

void func_ovl17_03_80043738(void) {
}

void func_ovl17_03_80043740(void) {
}

void func_ovl17_03_80043748(void) {
}

void func_ovl17_03_80043750(void) {
}

void func_ovl17_03_80043758(void) {
}

void func_ovl17_03_80043760(void) {
}

void func_ovl17_03_80043768(void) {
}
