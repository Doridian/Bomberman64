#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 unk34[2];
    /* 0x36 */ s16 unk36;
} UnkStruct_ovl0E_08_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x30];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ UnkStruct_ovl0E_08_Inner *unk40;
    /* 0x44 */ u8 unk44[0x28];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} UnkStruct_ovl0E_08_Obj;

typedef struct {
    /* 0x00 */ UnkStruct_ovl0E_08_Obj *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl0E_08_80045300;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_08_800453A0;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl0E_08_80045390;

void func_ovl0E_08_80043838(void);
void func_ovl0E_08_80043988(void);
void func_ovl0E_08_80043A40(UnkStruct_ovl0E_08_Obj *);
void func_ovl0E_08_80043B04(UnkStruct_ovl0E_08_Obj *);
void func_ovl0E_08_80043FD8(s32);
void func_ovl0E_08_80043FF0(s32);
void func_ovl0E_08_80044060(UnkStruct_ovl0E_08_Inner *, s32 *, s32 *);
void func_ovl0E_08_800440C0(void (*)(UnkStruct_ovl0E_08_Obj *));
void func_ovl0E_08_800440D0(s32, s32, s32);
void func_ovl0E_08_80044110(void (*)(UnkStruct_ovl0E_08_Obj *));
void func_ovl0E_08_80044188(void);
void func_ovl0E_08_80044190(s32, s32, s32);
void func_ovl0E_08_80044198(void *);
s32 func_ovl0E_08_800441A0(s32, s32, s32, s32);
s32 func_ovl0E_08_800441B8(void);
void func_ovl0E_08_800441C0(s32, void *);
void func_ovl0E_08_800441D0(s32);
void func_ovl0E_08_800441D8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_08_800441E8(void);
void func_ovl0E_08_80044220(s32);
void func_ovl0E_08_800446E0(UnkStruct_ovl0E_08_Inner *, s32);
void func_ovl0E_08_800446E8(UnkStruct_ovl0E_08_Inner *, s32, s32, s32);
void func_ovl0E_08_80044818(f32, f32, f32);
void func_ovl0E_08_80044838(f32, f32, f32);
void func_ovl0E_08_80044840(f32 *, f32 *, f32 *);
s32 func_ovl0E_08_80044988(UnkStruct_ovl0E_08_Obj *, s32);
void func_ovl0E_08_800449D8(UnkStruct_ovl0E_08_Obj *, s32);
void func_ovl0E_08_800449E0(UnkStruct_ovl0E_08_Obj *, s32);
UnkStruct_ovl0E_08_Obj *func_ovl0E_08_80044A20(s32, s32, f32, f32, f32);
void func_ovl0E_08_80044B28(void (*)(void), s32, s32, s32, s32);
void func_ovl0E_08_80044B38(void);
void func_ovl0E_08_80044B48(s32);
void func_ovl0E_08_80044B70(void);
void func_ovl0E_08_80044DA0(s32);
void func_ovl0E_08_80044DA8(s32);
s32 func_ovl0E_08_80044DB0(s32);
void func_ovl0E_08_80044E68(s32, s32, s32, s32, s32);
void func_ovl0E_08_80044E90(u32 (*)[3]);
void func_ovl0E_08_80044F80(s32, f32 *, s32);
void func_ovl0E_08_80045038(s32, s32, s32);
void func_ovl0E_08_800450B0(s32);
void func_ovl0E_08_800450D0(s32, f32, f32, f32);
void func_ovl0E_08_800450D8(s32, f32 *);

/* .bss, in first-seen order (docs/DECOMPILING.md, "Data") */
u8 D_ovl0E_08_80045360[0x10];
Vec3f_ovl0E_08_80045390 D_ovl0E_08_80045370;
s32 D_ovl0E_08_8004537C;
u8 D_ovl0E_08_80045380[4]; /* not referenced here */
s32 D_ovl0E_08_80045384;
s32 D_ovl0E_08_80045388;
u8 D_ovl0E_08_8004538C[4]; /* not referenced here */
Vec3f_ovl0E_08_80045390 D_ovl0E_08_80045390;
u8 D_ovl0E_08_8004539C[4]; /* not referenced here */
UnkStruct_ovl0E_08_800453A0 D_ovl0E_08_800453A0;
UnkStruct_ovl0E_08_Obj *D_ovl0E_08_800453B4;
u8 D_ovl0E_08_800453B8[8]; /* not referenced here */

/* .data */
/* passed to func_ovl0E_08_80044E90: three 12-byte records */
u32 D_ovl0E_08_800452D0[][3] = {
    { 0x9D0000, 0xE, 4 },
    { 0x9E0002, 0xE, 4 },
    { 2, 0, 4 },
};
/* one 12-byte record, each passed to func_ovl0E_08_80045038 */
u32 D_ovl0E_08_800452F4[][3] = {
    { 0, 0x10, 0xEE },
};
UnkStruct_ovl0E_08_80045300 D_ovl0E_08_80045300 = { NULL, 300.0f, 200.0f, 1300.0f };

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot).  It is
 * used four times here. */
#define UNK_MACRO_ovl0E_08_80043068() \
    D_ovl0E_08_8004537C = func_ovl0E_08_800441B8(); func_ovl0E_08_80044198(&D_ovl0E_08_80045370); func_ovl0E_08_800441C0(D_ovl0E_08_8004537C, D_ovl0E_08_80045360)

/* The five stores are one line too: IDO orders them by line otherwise. */
#define UNK_MACRO_ovl0E_08_800453A0(a, b, c, d, e) \
    D_ovl0E_08_800453A0.unk0 = (a); D_ovl0E_08_800453A0.unk4 = (b); D_ovl0E_08_800453A0.unk8 = (c); D_ovl0E_08_800453A0.unkC = (d); D_ovl0E_08_800453A0.unk10 = (e)

void func_ovl0E_08_80043010(void) {
}

void func_ovl0E_08_80043018(void) {
}

void func_ovl0E_08_80043020(void) {
    func_ovl0E_08_80044220(1);
}

void func_ovl0E_08_80043040(void) {
    func_ovl0E_08_80044220(1);
}

void func_ovl0E_08_80043060(void) {
}

void func_ovl0E_08_80043068(void) {
    UNK_MACRO_ovl0E_08_80043068();
}

void func_ovl0E_08_800430B0(void) {
    UNK_MACRO_ovl0E_08_80043068();
}

void func_ovl0E_08_800430F8(void) {
}

void func_ovl0E_08_80043100(void) {
}

void func_ovl0E_08_80043108(void) {
}

void func_ovl0E_08_80043110(void) {
    if (func_ovl0E_08_800441A0(9, 0x11, 0xA, 0x11) != 0) {
        D_ovl0E_08_80045384 = 0x4A;
        D_ovl0E_08_80045388 = 0x14;
        func_ovl0E_08_800440D0(0x4A, 0x14, 0);
    }
}

void func_ovl0E_08_80043168(void) {
    UNK_MACRO_ovl0E_08_80043068();
    func_ovl0E_08_800441D8(D_ovl0E_08_800453A0.unk4, 3, 4.0f, D_ovl0E_08_800453A0.unk10, 0, 1, 1);
}

void func_ovl0E_08_800431E0(void) {
    func_ovl0E_08_80043168();
}

void func_ovl0E_08_80043200(f32 arg0) {
    f32 sp1C;

    func_ovl0E_08_80044840(&sp1C, NULL, NULL);
    func_ovl0E_08_80044838(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_08_80043248(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_08_800441E8();
    switch (D_ovl0E_08_800453A0.unk8) {
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
        func_ovl0E_08_80044838(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_08_800453A0.unkC;
        func_ovl0E_08_80044840(&sp1C, NULL, NULL);
        func_ovl0E_08_80044838(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_08_800441D0(D_ovl0E_08_800453A0.unk4);
}

void func_ovl0E_08_80043360(void) {
    func_ovl0E_08_80043248();
}

void func_ovl0E_08_80043380(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_08_800453A0.unk0 = arg0;
    D_ovl0E_08_800453A0.unk4 = arg1;
    D_ovl0E_08_800453A0.unk8 = arg2;
    D_ovl0E_08_800453A0.unkC = arg3;
    D_ovl0E_08_800453A0.unk10 = arg4;
}

void func_ovl0E_08_800433A8(void) {
    func_ovl0E_08_80044190(9, 0, 0x11);
    UNK_MACRO_ovl0E_08_800453A0(2, 0, 0x80, 0.0f, 3);
}

void func_ovl0E_08_800433F8(void) {
    func_ovl0E_08_80044190(9, 0, 0x11);
    UNK_MACRO_ovl0E_08_800453A0(1, 0, 0x80, 0.0f, 3);
}

void func_ovl0E_08_80043448(void) {
    func_ovl0E_08_80044B28(func_ovl0E_08_80043838, 0, 0, 0, 0x130);
}

void func_ovl0E_08_80043480(void) {
}

void func_ovl0E_08_80043488(void) {
    func_ovl0E_08_80044DA8(0x400);
    func_ovl0E_08_80044DA8(0x401);
    func_ovl0E_08_80044DA8(0x402);
    func_ovl0E_08_80044DA8(0x403);
    func_ovl0E_08_80044DA8(0x404);
}

void func_ovl0E_08_800434C8(void) {
    func_ovl0E_08_80043488();
    func_ovl0E_08_800440C0(func_ovl0E_08_80043B04);
    func_ovl0E_08_80044110(func_ovl0E_08_80043A40);
}

void func_ovl0E_08_80043500(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_08_80043488();
    func_ovl0E_08_800440C0(func_ovl0E_08_80043B04);
    func_ovl0E_08_80044110(func_ovl0E_08_80043A40);
    func_ovl0E_08_80044E90(D_ovl0E_08_800452D0);
    func_ovl0E_08_80043FD8(0x18F);
    /* the count in a variable, as in ovl_0F_06 */
    p = D_ovl0E_08_800452F4;
    count = 1;
    for (i = 0; i < count; i++) {
        func_ovl0E_08_80045038((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_08_80043FF0(0x197);
    func_ovl0E_08_80044188();
    func_ovl0E_08_80044B28(func_ovl0E_08_80043838, 0, 0, 0, 0x130);
    func_ovl0E_08_80044E68(0x352, 0x3A2, 0, 0, 0);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_08_800435D8(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0E_08_80043500();
            break;
        case 17:
            func_ovl0E_08_800433F8();
            break;
        case 18:
            func_ovl0E_08_800433A8();
            break;
        case 4:
            func_ovl0E_08_80043248();
            break;
        case 5:
            func_ovl0E_08_80043168();
            break;
        case 0x50:
            func_ovl0E_08_80043110();
            break;
        case 3:
            UNK_MACRO_ovl0E_08_80043068();
            break;
        case 12:
            func_ovl0E_08_80044220(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_08_800436F8(void) {
    UnkStruct_ovl0E_08_Obj *obj;

    obj = func_ovl0E_08_80044A20(0x118, 0xC0, D_ovl0E_08_80045300.unk4, D_ovl0E_08_80045300.unk8,
                                 D_ovl0E_08_80045300.unkC);
    D_ovl0E_08_80045300.unk0 = obj;
    obj->unk40->unkC |= 0x8000;
    obj->unk40->unk36 = 0x80;
    obj->unk40->unk28 = 1.5f;
    obj->unk40->unk2C = 4.0f;
    obj->unk40->unk30 = 1.0f;
    func_ovl0E_08_800449D8(obj, 0x01080000);
    func_ovl0E_08_800446E0(obj->unk40, 1);
    func_ovl0E_08_800446E8(obj->unk40, 0x119, 0, 0);
    func_ovl0E_08_80044B28(func_ovl0E_08_80043988, 0, 0, 0, 0x130);
}

void func_ovl0E_08_800437E8(void) {
    if (func_ovl0E_08_80044DB0(0x400) == 0) {
        D_ovl0E_08_800453B4 = func_ovl0E_08_80044A20(-1, 0x80, 0.0f, 0.0f, 0.0f);
        func_ovl0E_08_80044DA0(0x400);
    }
}

void func_ovl0E_08_80043838(void) {
    s32 a;
    s32 b;
    s32 i;

    func_ovl0E_08_800437E8();
    while (TRUE) {
        D_ovl0E_08_800453B4->unk30 = 1;
        D_ovl0E_08_800453B4->unk34 = 50.0f;
        D_ovl0E_08_800453B4->unk38 = 50.0f;
        D_ovl0E_08_800453B4->unk40->unk10 = D_ovl0E_08_80045300.unk4;
        D_ovl0E_08_800453B4->unk40->unk14 = 0.0f;
        D_ovl0E_08_800453B4->unk40->unk18 = D_ovl0E_08_80045300.unkC;
        if (func_ovl0E_08_80044988(D_ovl0E_08_800453B4, 0x4000) & 0x40) {
            break;
        }
        func_ovl0E_08_80044B70();
    }
    b = 0x3A2;
    a = 0x352;
    for (i = 0; i < 30; i++) {
        func_ovl0E_08_80044E68(a, b, 0, 0, 0);
        b += 2;
        a += 4;
        func_ovl0E_08_80044B70();
    }
    func_ovl0E_08_800436F8();
    func_ovl0E_08_80044B38();
}

void func_ovl0E_08_80043988(void) {
    while (TRUE) {
        func_ovl0E_08_800446E8(D_ovl0E_08_80045300.unk0->unk40, 0x119, 0, 0);
        func_ovl0E_08_80044B48(10);
        func_ovl0E_08_800446E8(D_ovl0E_08_80045300.unk0->unk40, 0x119, 0, 1);
        func_ovl0E_08_80044B48(10);
        func_ovl0E_08_800446E8(D_ovl0E_08_80045300.unk0->unk40, 0x119, 0, 2);
        func_ovl0E_08_80044B48(10);
        func_ovl0E_08_800446E8(D_ovl0E_08_80045300.unk0->unk40, 0x119, 0, 3);
        func_ovl0E_08_80044B48(10);
    }
}

void func_ovl0E_08_80043A40(UnkStruct_ovl0E_08_Obj *arg0) {
    func_ovl0E_08_800449E0(arg0, 0x04000000);
    func_ovl0E_08_80044B48(10);
    func_ovl0E_08_80044060(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_08_800450B0(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_08_80044B48(60);
}

void func_ovl0E_08_80043B04(UnkStruct_ovl0E_08_Obj *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_08_800449E0(arg0, 0x01000000);
    func_ovl0E_08_80044F80(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_08_80044F80(13, pos, 0);
    func_ovl0E_08_800450D8(180, pos);
}

void func_ovl0E_08_80043B9C(s32 arg0, UnkStruct_ovl0E_08_Obj *arg1) {
    UnkStruct_ovl0E_08_Inner *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01: without it arg1 is spilled */
    }
    func_ovl0E_08_800450D0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_08_80043BD0(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_08_80044818(D_ovl0E_08_80045390.x, D_ovl0E_08_80045390.y, D_ovl0E_08_80045390.z);
    func_ovl0E_08_80044838(arg0, arg1, arg2);
    func_ovl0E_08_80044B48(180);
}

void func_ovl0E_08_80043C2C(void) {
    D_ovl0E_08_80045384 = -1;
    D_ovl0E_08_80045388 = -1;
}

void func_ovl0E_08_80043C44(void) {
}

void func_ovl0E_08_80043C4C(void) {
}

void func_ovl0E_08_80043C54(void) {
}

void func_ovl0E_08_80043C5C(void) {
}

void func_ovl0E_08_80043C64(void) {
}

void func_ovl0E_08_80043C6C(void) {
}

void func_ovl0E_08_80043C74(void) {
}

void func_ovl0E_08_80043C7C(void) {
}

void func_ovl0E_08_80043C84(void) {
}
