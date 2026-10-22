#include "common.h"

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_08_800455E0;

void func_ovl0C_08_80043AA4(UnkStructA *);
void func_ovl0C_08_80043B64(UnkStructA *);
void func_ovl0C_08_80043C80(void);
void func_ovl0C_08_800442B0(void (*)(UnkStructA *));
void func_ovl0C_08_80044300(void (*)(UnkStructA *));
void func_ovl0C_08_80044388(void *);
s32 func_ovl0C_08_800443A8(void);
void func_ovl0C_08_800443B0(s32, void *);
void func_ovl0C_08_800443C8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_08_80044410(s32);
void func_ovl0C_08_80044A08(f32, f32, f32);
void func_ovl0C_08_80044A28(f32, f32, f32);
void func_ovl0C_08_80044A30(f32 *, f32 *, f32 *);
void func_ovl0C_08_80044BD0(UnkStructA *, s32);
void func_ovl0C_08_80044D18(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_08_80044D38(s32);
f32 func_ovl0C_08_80044EC0(f32);
void func_ovl0C_08_80044F98(s32);
void func_ovl0C_08_800452C0(s32, f32, f32, f32);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0C_08_800430B0() \
    D_ovl0C_08_800455BC = func_ovl0C_08_800443A8(); func_ovl0C_08_80044388(&D_ovl0C_08_800455B0); func_ovl0C_08_800443B0(D_ovl0C_08_800455BC, D_ovl0C_08_800455A0)

void func_ovl0C_08_80043A20(void);
void func_ovl0C_08_800441C8(s32);
void func_ovl0C_08_800441E0(s32);
void func_ovl0C_08_80044250(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_08_800442C0(s32, s32, s32);
void func_ovl0C_08_80044350(s32, s32);
void func_ovl0C_08_80044368(s32);
void func_ovl0C_08_80044378(void);
void func_ovl0C_08_80044380(s32, s32, s32);
s32 func_ovl0C_08_80044390(s32, s32, s32, s32);
void func_ovl0C_08_800443B8(s32);
void func_ovl0C_08_800443C0(s32);
void func_ovl0C_08_800443D8(void);
UnkStructA *func_ovl0C_08_80044408(s32);
s32 func_ovl0C_08_80044910(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0C_08_80044AC0(f32, f32);
void func_ovl0C_08_80044BC8(UnkStructA *, s32);
void func_ovl0C_08_80044BE0(UnkStructA *);
UnkStructA *func_ovl0C_08_80044BF0(s32, s32, s32, s32);
UnkStructA *func_ovl0C_08_80044C10(s32, s32, f32, f32, f32);
void func_ovl0C_08_80044D28(void);
UnkStructA *func_ovl0C_08_80044D40(void);
void func_ovl0C_08_80044D60(void);
void func_ovl0C_08_80045080(u32 (*)[3]);
void func_ovl0C_08_80045228(s32, s32, s32);
void func_ovl0C_08_800452A0(s32);

/* The five stores are one line too: IDO orders them by line otherwise. */
#define UNK_MACRO_ovl0C_08_800455E0(a, b, c, d, e) \
    D_ovl0C_08_800455E0.unk0 = (a); D_ovl0C_08_800455E0.unk4 = (b); D_ovl0C_08_800455E0.unk8 = (c); D_ovl0C_08_800455E0.unkC = (d); D_ovl0C_08_800455E0.unk10 = (e)

/* .bss */
u8 D_ovl0C_08_800455A0[0x10];
Vec3f D_ovl0C_08_800455B0;
s32 D_ovl0C_08_800455BC;
u8 D_ovl0C_08_800455C0[0x4]; /* split for alignment */
s32 D_ovl0C_08_800455C4;
s32 D_ovl0C_08_800455C8;
u8 D_ovl0C_08_800455CC[0x4]; /* not referenced here */
Vec3f D_ovl0C_08_800455D0;
UnkStructA *D_ovl0C_08_800455DC;
UnkStruct_ovl0C_08_800455E0 D_ovl0C_08_800455E0;

/* .data */
/* passed to func_ovl0C_08_80045080: three 12-byte records */
u32 D_ovl0C_08_800454C0[][3] = {
    { 0x940002, 0xE, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
/* two 12-byte records, each passed to func_ovl0C_08_80045228 */
u32 D_ovl0C_08_800454E4[][3] = {
    { 0, 0, 0xDE },
    { 1, 0x22, 0xE0 },
};
/* An object's setup: the object, func_ovl0C_08_80044910's result, the
 * object's kind, four arguments for func_ovl0C_08_80044910 (none -1) and
 * nine floats (position / 10, then two sets of three). */
UnkStructA *D_ovl0C_08_800454FC = NULL;
s32 D_ovl0C_08_80045500 = -1;
s32 D_ovl0C_08_80045504 = 0x2BA;
s16 D_ovl0C_08_80045508[2] = { -5, -0x400 };
s16 D_ovl0C_08_8004550C[2] = { 0, 0 };
f32 D_ovl0C_08_80045510 = 0.0f;
f32 D_ovl0C_08_80045514 = 0.0f;
f32 D_ovl0C_08_80045518 = 0.0f;
f32 D_ovl0C_08_8004551C = 0.0f;
f32 D_ovl0C_08_80045520 = 0.0f;
f32 D_ovl0C_08_80045524 = 0.0f;
f32 D_ovl0C_08_80045528 = 1.0f;
f32 D_ovl0C_08_8004552C = 1.0f;
f32 D_ovl0C_08_80045530 = 1.0f;

void func_ovl0C_08_80043010(void) {
}

void func_ovl0C_08_80043018(void) {
}

void func_ovl0C_08_80043020(void) {
    func_ovl0C_08_80044410(1);
}

void func_ovl0C_08_80043040(void) {
    func_ovl0C_08_80044410(1);
}

void func_ovl0C_08_80043060(void) {
}

void func_ovl0C_08_80043068(void) {
    D_ovl0C_08_800455BC = func_ovl0C_08_800443A8();
    func_ovl0C_08_80044388(&D_ovl0C_08_800455B0);
    func_ovl0C_08_800443B0(D_ovl0C_08_800455BC, D_ovl0C_08_800455A0);
}

void func_ovl0C_08_800430B0(void) {
    UNK_MACRO_ovl0C_08_800430B0();
}

void func_ovl0C_08_800430F8(void) {
}

void func_ovl0C_08_80043100(void) {
}

void func_ovl0C_08_80043108(void) {
    if (func_ovl0C_08_80044390(0x17, 0x18, 0x18, 0x19) != 0) {
        func_ovl0C_08_80044D18(func_ovl0C_08_80043A20, 0, 0, 0, 0x130);
        func_ovl0C_08_80044368(60);
        func_ovl0C_08_800442C0(0x2D, 0x13, 4);
    }
}

void func_ovl0C_08_80043170(void) {
    func_ovl0C_08_800443C8(D_ovl0C_08_800455E0.unk4, 3, 4.0f, D_ovl0C_08_800455E0.unk10, 0, 1, 1);
}

void func_ovl0C_08_800431B8(void) {
    s32 alpha;
    s32 step;

    func_ovl0C_08_800443B8(1);
    func_ovl0C_08_800452A0(0x45);
    step = 0x11;
    for (alpha = 0; alpha < 0xFF; alpha += step) {
        D_ovl0C_08_800455DC->unk40->unk36 = alpha;
        func_ovl0C_08_80044D60();
    }
    D_ovl0C_08_800455DC->unk40->unk36 = 0xFF;
    func_ovl0C_08_80044BD0(D_ovl0C_08_800455DC, 0x80000);
    func_ovl0C_08_800443B8(0);
}

void func_ovl0C_08_80043244(void) {
    if (D_ovl0C_08_800455E0.unk0 == 2) {
        func_ovl0C_08_800431B8();
    }
    func_ovl0C_08_800443C8(D_ovl0C_08_800455E0.unk4, 3, 4.0f, D_ovl0C_08_800455E0.unk10, 0, 1, 1);
}

void func_ovl0C_08_800432A8(void) {
    D_ovl0C_08_800455DC = func_ovl0C_08_80044408(func_ovl0C_08_800443A8());
    func_ovl0C_08_80044BC8(D_ovl0C_08_800455DC, 0x80000);
    D_ovl0C_08_800455DC->unk40->unk36 = 0;
}

void func_ovl0C_08_80043300(f32 arg0) {
    f32 sp1C;

    func_ovl0C_08_80044A30(&sp1C, NULL, NULL);
    func_ovl0C_08_80044A28(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0C_08_80043348(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_08_800443D8();
    switch (D_ovl0C_08_800455E0.unk8) {
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
        func_ovl0C_08_80044A28(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_08_800455E0.unkC;
        func_ovl0C_08_80044A30(&sp1C, NULL, NULL);
        func_ovl0C_08_80044A28(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_08_800443C0(D_ovl0C_08_800455E0.unk4);
    func_ovl0C_08_80044AC0(45.0f, 45.1f);
}

void func_ovl0C_08_80043478(void) {
    func_ovl0C_08_80043348();
    if (D_ovl0C_08_800455E0.unk0 == 2) {
        func_ovl0C_08_800432A8();
    }
}

void func_ovl0C_08_800434B4(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0C_08_800455E0.unk0 = arg0;
    D_ovl0C_08_800455E0.unk4 = arg1;
    D_ovl0C_08_800455E0.unk8 = arg2;
    D_ovl0C_08_800455E0.unkC = arg3;
    D_ovl0C_08_800455E0.unk10 = arg4;
}

void func_ovl0C_08_800434DC(void) {
    func_ovl0C_08_80044380(0x17, 0, 0x19);
    UNK_MACRO_ovl0C_08_800455E0(3, 0, 0, 0.0f, 2);
}

void func_ovl0C_08_80043528(void) {
    func_ovl0C_08_80044380(0x17, 0, 0x19);
    UNK_MACRO_ovl0C_08_800455E0(2, 0, 0, 0.0f, 2);
    func_ovl0C_08_80044350(0x2F, 0x13);
}

void func_ovl0C_08_80043580(void) {
    func_ovl0C_08_80044380(0x17, 0, 0x19);
    UNK_MACRO_ovl0C_08_800455E0(1, 0, 0, 0.0f, 2);
}

void func_ovl0C_08_800435CC(void) {
}

void func_ovl0C_08_800435D4(void) {
}

void func_ovl0C_08_800435DC(void) {
    func_ovl0C_08_80044F98(0x400);
    func_ovl0C_08_80044F98(0x401);
    func_ovl0C_08_80044F98(0x402);
    func_ovl0C_08_80044F98(0x403);
    func_ovl0C_08_80044F98(0x404);
}

void func_ovl0C_08_8004361C(void) {
    func_ovl0C_08_800435DC();
    func_ovl0C_08_800442B0(func_ovl0C_08_80043B64);
    func_ovl0C_08_80044300(func_ovl0C_08_80043AA4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/overlays/ovl_0C_08/18D110/func_ovl0C_08_80043654.s")

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0C_08_80043888(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0C_08_80043654();
            break;
        case 17:
            func_ovl0C_08_80043580();
            break;
        case 18:
            func_ovl0C_08_80043528();
            break;
        case 19:
            func_ovl0C_08_800434DC();
            break;
        case 4:
            func_ovl0C_08_80043348();
            if (D_ovl0C_08_800455E0.unk0 == 2) {
                func_ovl0C_08_800432A8();
            }
            break;
        case 5:
            if (D_ovl0C_08_800455E0.unk0 == 2) {
                func_ovl0C_08_800431B8();
            }
            func_ovl0C_08_800443C8(D_ovl0C_08_800455E0.unk4, 3, 4.0f, D_ovl0C_08_800455E0.unk10, 0, 1, 1);
            break;
        case 0x50:
            func_ovl0C_08_80043108();
            break;
        case 3:
            UNK_MACRO_ovl0C_08_800430B0();
            break;
        case 12:
            func_ovl0C_08_80044410(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0C_08_80043A20(void) {
    UnkStructA *obj;
    s32 alpha;
    s32 step;

    func_ovl0C_08_800443B8(1);
    func_ovl0C_08_80044D38(10);
    obj = func_ovl0C_08_80044408(func_ovl0C_08_800443A8());
    func_ovl0C_08_800452A0(0x44);
    func_ovl0C_08_80044BC8(obj, 0x80000);
    step = 0x11;
    for (alpha = 0xFF; alpha > 0; alpha -= step) {
        obj->unk40->unk36 = alpha;
        func_ovl0C_08_80044D60();
    }
    obj->unk40->unk36 = 0;
    func_ovl0C_08_80044D28();
}

#pragma GLOBAL_ASM("asm/nonmatchings/overlays/ovl_0C_08/18D110/func_ovl0C_08_80043AA4.s")

void func_ovl0C_08_80043B64(UnkStructA *arg0) {
    func_ovl0C_08_80044BD0(arg0, 0x01000000);
    func_ovl0C_08_80044D18(func_ovl0C_08_80043C80, arg0, 0, 0, 0x150);
}

void func_ovl0C_08_80043BA8(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    /* the ratio is spelled out three times: with a variable for it, IDO
     * spills it to another stack slot */
    arg0->unk40->unk28 = func_ovl0C_08_80044EC0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_08_80044EC0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_08_80043C80(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_08_80044D40();
    func_ovl0C_08_800452C0(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_08_80044BF0(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_08_80043BA8(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_08_80044D60();
    }
    func_ovl0C_08_80044BE0(obj);
    func_ovl0C_08_80044D28();
}

void func_ovl0C_08_80043D90(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01: without it arg1 is spilled */
    }
    func_ovl0C_08_800452C0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_08_80043DC4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_08_80044A08(D_ovl0C_08_800455D0.x, D_ovl0C_08_800455D0.y, D_ovl0C_08_800455D0.z);
    func_ovl0C_08_80044A28(arg0, arg1, arg2);
    func_ovl0C_08_80044D38(180);
}

void func_ovl0C_08_80043E20(void) {
    D_ovl0C_08_800455C4 = -1;
    D_ovl0C_08_800455C8 = -1;
}

void func_ovl0C_08_80043E38(void) {
}

void func_ovl0C_08_80043E40(void) {
}

void func_ovl0C_08_80043E48(void) {
}

void func_ovl0C_08_80043E50(void) {
}

void func_ovl0C_08_80043E58(void) {
}

void func_ovl0C_08_80043E60(void) {
}

void func_ovl0C_08_80043E68(void) {
}

void func_ovl0C_08_80043E70(void) {
}

void func_ovl0C_08_80043E78(void) {
}
