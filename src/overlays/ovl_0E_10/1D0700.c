#include "common.h"

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_10_800455A0;

void func_ovl0E_10_80043BFC(UnkStructA *);
void func_ovl0E_10_80043CC0(UnkStructA *);
void func_ovl0E_10_80044220(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_10_80044280(void (*)(UnkStructA *));
void func_ovl0E_10_800442D0(void (*)(UnkStructA *));
void func_ovl0E_10_80044358(void *);
s32 func_ovl0E_10_80044378(void);
void func_ovl0E_10_80044380(s32, void *);
void func_ovl0E_10_80044390(s32);
void func_ovl0E_10_80044398(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_10_800443A8(void);
void func_ovl0E_10_800443E0(s32);
void func_ovl0E_10_800449D8(f32, f32, f32);
void func_ovl0E_10_800449F8(f32, f32, f32);
void func_ovl0E_10_80044A00(f32 *, f32 *, f32 *);
void func_ovl0E_10_80044BA0(UnkStructA *, s32);
UnkStructA *func_ovl0E_10_80044BE0(s32, s32, f32, f32, f32);
void func_ovl0E_10_80044D08(s32);
void func_ovl0E_10_80044F60(s32);
void func_ovl0E_10_80044F68(s32);
s32 func_ovl0E_10_80044F70(s32);
void func_ovl0E_10_80045140(s32, f32 *, s32);
void func_ovl0E_10_80045270(s32);
void func_ovl0E_10_80045290(s32, f32, f32, f32);
void func_ovl0E_10_80045298(s32, f32 *);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_10_8004325C() \
    D_ovl0E_10_8004557C = func_ovl0E_10_80044378(); func_ovl0E_10_80044358(&D_ovl0E_10_80045570); func_ovl0E_10_80044380(D_ovl0E_10_8004557C, D_ovl0E_10_80045560)

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl0E_10_800454E4;

void func_ovl0E_10_80044198(s32);
void func_ovl0E_10_800441B0(s32);
void func_ovl0E_10_80044290(s32, s32, s32);
void func_ovl0E_10_80044348(void);
void func_ovl0E_10_80044350(s32, s32, s32);
s32 func_ovl0E_10_80044360(s32, s32, s32, s32);
s32 func_ovl0E_10_80044368(s32, s32, s32, s32, s32);
UnkStructA *func_ovl0E_10_800443D8(s32);
void func_ovl0E_10_800448E0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_10_80044900(s32, s32);
void func_ovl0E_10_80044B98(UnkStructA *, s32);
void func_ovl0E_10_80044BD0(UnkStructA *);
UnkStructA *func_ovl0E_10_80044C28(UnkStructA *, s32);
f32 func_ovl0E_10_80044E90(f32);
f32 func_ovl0E_10_80044E98(f32);
s32 func_ovl0E_10_80044F50(s32);
void func_ovl0E_10_80045028(s32, s32, s32, s32, s32);
void func_ovl0E_10_80045038(s32, s32, s32);
void func_ovl0E_10_80045050(u32 (*)[3]);
void func_ovl0E_10_800451F8(s32, s32, s32);

/* The five stores are one line too: IDO orders them by line otherwise. */
#define UNK_MACRO_ovl0E_10_800455A0(a, b, c, d, e) \
    D_ovl0E_10_800455A0.unk0 = (a); D_ovl0E_10_800455A0.unk4 = (b); D_ovl0E_10_800455A0.unk8 = (c); D_ovl0E_10_800455A0.unkC = (d); D_ovl0E_10_800455A0.unk10 = (e)

/* .bss */
u8 D_ovl0E_10_80045560[0x10];
Vec3f D_ovl0E_10_80045570;
s32 D_ovl0E_10_8004557C;
u8 D_ovl0E_10_80045580[0x4]; /* split for alignment */
s32 D_ovl0E_10_80045584;
s32 D_ovl0E_10_80045588;
u8 D_ovl0E_10_8004558C[0x4]; /* not referenced here */
Vec3f D_ovl0E_10_80045590;
u8 D_ovl0E_10_8004559C[0x4]; /* not referenced here */
UnkStruct_ovl0E_10_800455A0 D_ovl0E_10_800455A0;
UnkStructA *D_ovl0E_10_800455B4;
u8 D_ovl0E_10_800455B8[0x8]; /* split for alignment */

/* .data */
/* passed to func_ovl0E_10_80045050: three 12-byte records */
u32 D_ovl0E_10_80045490[][3] = {
    { 0xA10002, 0xE, 4 },
    { 0xA40002, 0xE, 4 },
    { 0, 0, 4 },
};
/* four 12-byte records, each passed to func_ovl0E_10_800451F8 */
u32 D_ovl0E_10_800454B4[][3] = {
    { 0, 0xE, 0xEC },
    { 1, 0xD, 0xEB },
    { 2, 0x22, 0xE0 },
    { 3, 0xF, 0xED },
};
UnkStruct_ovl0E_10_800454E4 D_ovl0E_10_800454E4 = { NULL, 2700.0f, 1200.0f, 1100.0f };

void func_ovl0E_10_80043010(void) {
}

void func_ovl0E_10_80043018(void) {
}

void func_ovl0E_10_80043020(void) {
    func_ovl0E_10_800443E0(1);
}

void func_ovl0E_10_80043040(void) {
    func_ovl0E_10_800443E0(1);
}

void func_ovl0E_10_80043060(void) {
    if (func_ovl0E_10_80044F70(0x400) == 0) {
        D_ovl0E_10_800455B4 = func_ovl0E_10_80044BE0(-1, 0x80, 0.0f, 0.0f, 0.0f);
        func_ovl0E_10_80044F60(0x400);
    }
}

s32 func_ovl0E_10_800430B0(UnkStructA *arg0, UnkStructA *arg1) {
    f32 dz;
    f32 dx;

    func_ovl0E_10_80043060();
    dx = func_ovl0E_10_80044E90(arg0->unk40->unk20) * 80.0f;
    dz = func_ovl0E_10_80044E98(arg0->unk40->unk20);
    D_ovl0E_10_800455B4->unk30 = 1;
    D_ovl0E_10_800455B4->unk34 = 30.0f;
    D_ovl0E_10_800455B4->unk38 = 50.0f;
    D_ovl0E_10_800455B4->unk40->unk10 = arg0->unk40->unk10 + dx;
    D_ovl0E_10_800455B4->unk40->unk14 = arg0->unk40->unk14;
    D_ovl0E_10_800455B4->unk40->unk18 = arg0->unk40->unk18 + dz * 80.0f;
    if (func_ovl0E_10_80044C28(D_ovl0E_10_800455B4, 0x10) != arg1) {
        return FALSE;
    }
    return TRUE;
}

void func_ovl0E_10_800431C4(void) {
    if (func_ovl0E_10_80044368(0x1A, 1, 0xA, 0x1B, 0xC) != 0 &&
        func_ovl0E_10_800430B0(func_ovl0E_10_800443D8(func_ovl0E_10_80044378()), D_ovl0E_10_800454E4.unk0) != 0) {
        if (func_ovl0E_10_80044F50(0xA4) != 0) {
            func_ovl0E_10_80044900(0x291, 1);
        } else {
            func_ovl0E_10_80044900(0x363, 3);
        }
    }
}

void func_ovl0E_10_80043254(void) {
}

void func_ovl0E_10_8004325C(void) {
    UNK_MACRO_ovl0E_10_8004325C();
}

void func_ovl0E_10_800432A4(void) {
    UNK_MACRO_ovl0E_10_8004325C();
}

void func_ovl0E_10_800432EC(void) {
}

void func_ovl0E_10_800432F4(void) {
}

void func_ovl0E_10_800432FC(void) {
}

void func_ovl0E_10_80043304(void) {
    if (func_ovl0E_10_80044360(4, 1, 5, 1) != 0) {
        D_ovl0E_10_80045584 = 0x52;
        D_ovl0E_10_80045588 = 0x12;
        func_ovl0E_10_80044290(0x52, 0x12, 0);
    }
    if (func_ovl0E_10_80044360(0x11, 1, 0x12, 1) != 0) {
        D_ovl0E_10_80045584 = 0x52;
        D_ovl0E_10_80045588 = 0x13;
        func_ovl0E_10_80044290(0x52, 0x13, 0);
    }
    if (func_ovl0E_10_80044360(3, 0x16, 3, 0x17) != 0) {
        D_ovl0E_10_80045584 = 0x53;
        D_ovl0E_10_80045588 = 0x12;
        func_ovl0E_10_80044290(0x53, 0x12, 0);
    }
    if (func_ovl0E_10_80044360(2, 0x1E, 3, 0x1E) != 0) {
        D_ovl0E_10_80045584 = 0x50;
        D_ovl0E_10_80045588 = 0x12;
        func_ovl0E_10_80044290(0x50, 0x12, 0);
    }
    if (func_ovl0E_10_80044360(0x11, 0x1D, 0x12, 0x1D) != 0) {
        D_ovl0E_10_80045584 = 0x50;
        D_ovl0E_10_80045588 = 0x13;
        func_ovl0E_10_80044290(0x50, 0x13, 0);
    }
}

void func_ovl0E_10_8004345C(void) {
    UNK_MACRO_ovl0E_10_8004325C();
    func_ovl0E_10_80044398(D_ovl0E_10_800455A0.unk4, 3, 4.0f, D_ovl0E_10_800455A0.unk10, 0, 1, 1);
}

void func_ovl0E_10_800434D4(void) {
    func_ovl0E_10_8004345C();
}

void func_ovl0E_10_800434F4(f32 arg0) {
    f32 sp1C;

    func_ovl0E_10_80044A00(&sp1C, NULL, NULL);
    func_ovl0E_10_800449F8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_10_8004353C(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_10_800443A8();
    switch (D_ovl0E_10_800455A0.unk8) {
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
        func_ovl0E_10_800449F8(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_10_800455A0.unkC;
        func_ovl0E_10_80044A00(&sp1C, NULL, NULL);
        func_ovl0E_10_800449F8(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_10_80044390(D_ovl0E_10_800455A0.unk4);
}

void func_ovl0E_10_80043654(void) {
    func_ovl0E_10_8004353C();
}

void func_ovl0E_10_80043674(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_10_800455A0.unk0 = arg0;
    D_ovl0E_10_800455A0.unk4 = arg1;
    D_ovl0E_10_800455A0.unk8 = arg2;
    D_ovl0E_10_800455A0.unkC = arg3;
    D_ovl0E_10_800455A0.unk10 = arg4;
}

void func_ovl0E_10_8004369C(void) {
    func_ovl0E_10_80044350(0x12, 5, 0x1D);
    UNK_MACRO_ovl0E_10_800455A0(6, 0, 0x80, 0.0f, 1);
}

void func_ovl0E_10_800436EC(void) {
    func_ovl0E_10_80044350(3, 4, 0x1E);
    UNK_MACRO_ovl0E_10_800455A0(5, 0, 1, 0.0f, 1);
}

void func_ovl0E_10_80043738(void) {
    func_ovl0E_10_80044350(3, 2, 0x16);
    UNK_MACRO_ovl0E_10_800455A0(4, 0x40, 0xC0, 0.0f, 1);
}

void func_ovl0E_10_8004378C(void) {
    func_ovl0E_10_80044350(0x11, 3, 1);
    UNK_MACRO_ovl0E_10_800455A0(3, 0x80, 0, 0.0f, 1);
}

void func_ovl0E_10_800437DC(void) {
    func_ovl0E_10_80044350(4, 4, 1);
    UNK_MACRO_ovl0E_10_800455A0(2, 0x80, 0, 0.0f, 1);
}

void func_ovl0E_10_8004382C(void) {
    func_ovl0E_10_80044350(4, 4, 0);
    UNK_MACRO_ovl0E_10_800455A0(1, 0x80, 0, 0.0f, 0);
}

void func_ovl0E_10_80043878(void) {
    UnkStructA *obj;

    obj = func_ovl0E_10_80044BE0(0x323, 0xC0, D_ovl0E_10_800454E4.unk4, D_ovl0E_10_800454E4.unk8,
                                 D_ovl0E_10_800454E4.unkC);
    D_ovl0E_10_800454E4.unk0 = obj;
    obj->unk40->unk20 = 270.0f;
    func_ovl0E_10_80044BD0(obj);
    func_ovl0E_10_80044B98(obj, 0x01000010);
}

void func_ovl0E_10_800438EC(void) {
}

void func_ovl0E_10_800438F4(void) {
    func_ovl0E_10_80044F68(0x400);
    func_ovl0E_10_80044F68(0x401);
    func_ovl0E_10_80044F68(0x402);
    func_ovl0E_10_80044F68(0x403);
    func_ovl0E_10_80044F68(0x404);
}

void func_ovl0E_10_80043934(void) {
    func_ovl0E_10_800438F4();
    func_ovl0E_10_80044280(func_ovl0E_10_80043CC0);
    func_ovl0E_10_800442D0(func_ovl0E_10_80043BFC);
}

void func_ovl0E_10_8004396C(void) {
    UnkStructA *obj;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_10_800438F4();
    func_ovl0E_10_80044280(func_ovl0E_10_80043CC0);
    func_ovl0E_10_800442D0(func_ovl0E_10_80043BFC);
    func_ovl0E_10_80045050(D_ovl0E_10_80045490);
    func_ovl0E_10_80044198(0x19B);
    obj = func_ovl0E_10_80044BE0(0x19C, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_10_80044B98(obj, 0x01000000);
    p = D_ovl0E_10_800454B4;
    count = 4;
    for (i = 0; i < count; i++) {
        func_ovl0E_10_800451F8((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_10_800441B0(0x1A6);
    func_ovl0E_10_80044348();
    func_ovl0E_10_80043878();
    func_ovl0E_10_800448E0(obj->unk40, 0, 2, 0x400, 0, 0);
    func_ovl0E_10_80045028(0x398, 0x3DE, 0xFF, 0x87, 0x1F);
    func_ovl0E_10_80045038(0xFF, 0xA1, 0x1D);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_10_80043A8C(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0E_10_8004396C();
            break;
        case 17:
            func_ovl0E_10_8004382C();
            break;
        case 18:
            func_ovl0E_10_800437DC();
            break;
        case 19:
            func_ovl0E_10_8004378C();
            break;
        case 20:
            func_ovl0E_10_80043738();
            break;
        case 21:
            func_ovl0E_10_800436EC();
            break;
        case 22:
            func_ovl0E_10_8004369C();
            break;
        case 4:
            func_ovl0E_10_8004353C();
            break;
        case 5:
            func_ovl0E_10_8004345C();
            break;
        case 0x50:
            func_ovl0E_10_80043304();
            break;
        case 3:
            UNK_MACRO_ovl0E_10_8004325C();
            break;
        case 15:
            func_ovl0E_10_800431C4();
            break;
        case 12:
            func_ovl0E_10_800443E0(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_10_80043BFC(UnkStructA *arg0) {
    func_ovl0E_10_80044BA0(arg0, 0x04000000);
    func_ovl0E_10_80044D08(10);
    func_ovl0E_10_80044220(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_10_80045270(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_10_80044D08(60);
}

void func_ovl0E_10_80043CC0(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_10_80044BA0(arg0, 0x01000000);
    func_ovl0E_10_80045140(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_10_80045140(13, pos, 0);
    func_ovl0E_10_80045298(180, pos);
}

void func_ovl0E_10_80043D58(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01: without it arg1 is spilled */
    }
    func_ovl0E_10_80045290(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_10_80043D8C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_10_800449D8(D_ovl0E_10_80045590.x, D_ovl0E_10_80045590.y, D_ovl0E_10_80045590.z);
    func_ovl0E_10_800449F8(arg0, arg1, arg2);
    func_ovl0E_10_80044D08(180);
}

void func_ovl0E_10_80043DE8(void) {
    D_ovl0E_10_80045584 = -1;
    D_ovl0E_10_80045588 = -1;
}

void func_ovl0E_10_80043E00(void) {
}

void func_ovl0E_10_80043E08(void) {
}

void func_ovl0E_10_80043E10(void) {
}

void func_ovl0E_10_80043E18(void) {
}

void func_ovl0E_10_80043E20(void) {
}

void func_ovl0E_10_80043E28(void) {
}

void func_ovl0E_10_80043E30(void) {
}

void func_ovl0E_10_80043E38(void) {
}

void func_ovl0E_10_80043E40(void) {
}
