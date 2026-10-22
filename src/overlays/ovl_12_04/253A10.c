#include "common.h"

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl12_04_800450B0;

void func_ovl12_04_80043E88(void *);
s32 func_ovl12_04_80043EA8(void);
void func_ovl12_04_80043EB0(s32, void *);
void func_ovl12_04_80043EC0(s32);
void func_ovl12_04_80043ED8(void);
void func_ovl12_04_80043F10(s32);
void func_ovl12_04_80044508(f32, f32, f32);
void func_ovl12_04_80044528(f32, f32, f32);
void func_ovl12_04_80044530(f32 *, f32 *, f32 *);
void func_ovl12_04_80044838(s32);
void func_ovl12_04_80044A98(s32);
void func_ovl12_04_80044DC0(s32, f32, f32, f32);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl12_04_800430B0() \
    D_ovl12_04_8004508C = func_ovl12_04_80043EA8(); func_ovl12_04_80043E88(&D_ovl12_04_80045080); func_ovl12_04_80043EB0(D_ovl12_04_8004508C, D_ovl12_04_80045070)

void func_ovl12_04_80043750(UnkStructA *);
void func_ovl12_04_80043810(UnkStructA *);
void func_ovl12_04_80043CC8(s32);
void func_ovl12_04_80043CE0(s32);
void func_ovl12_04_80043D50(UnkStructA_40 *, f32 *, f32 *);
void func_ovl12_04_80043DB0(void (*)(UnkStructA *));
void func_ovl12_04_80043DC0(s32, s32, s32);
void func_ovl12_04_80043E00(void (*)(UnkStructA *));
void func_ovl12_04_80043E78(void);
void func_ovl12_04_80043E80(s32, s32, s32);
s32 func_ovl12_04_80043E90(s32, s32, s32, s32);
void func_ovl12_04_80043EC8(s32, s32, f32, s32, s32, s32, s32);
s32 func_ovl12_04_80043F48(s32);
void func_ovl12_04_80044570(s32);
s32 func_ovl12_04_80044678(UnkStructA *, s32);
void func_ovl12_04_800446D0(UnkStructA *, s32);
void func_ovl12_04_80044748(UnkStructA *);
s32 func_ovl12_04_800447E8(UnkStructA *, s32, s32);
void func_ovl12_04_80044860(void);
UnkStructA *func_ovl12_04_800448A0(s32);
void func_ovl12_04_800448B0(UnkStructA *, s32);
void func_ovl12_04_80044B40(s32, s32, s32);
void func_ovl12_04_80044B80(u32 (*)[3]);
void func_ovl12_04_80044B98(u32 (*)[3]);
void func_ovl12_04_80044D18(UnkStructA *, s32, f32);
void func_ovl12_04_80044D28(s32, s32, s32);

/* The five stores are one line too: IDO orders them by line otherwise. */
#define UNK_MACRO_ovl12_04_800450B0(a, b, c, d, e) \
    D_ovl12_04_800450B0.unk0 = (a); D_ovl12_04_800450B0.unk4 = (b); D_ovl12_04_800450B0.unk8 = (c); D_ovl12_04_800450B0.unkC = (d); D_ovl12_04_800450B0.unk10 = (e)

/* .bss */
u8 D_ovl12_04_80045070[0x10];
Vec3f D_ovl12_04_80045080;
s32 D_ovl12_04_8004508C;
u8 D_ovl12_04_80045090[0x4]; /* split for alignment */
s32 D_ovl12_04_80045094;
s32 D_ovl12_04_80045098;
u8 D_ovl12_04_8004509C[0x4]; /* not referenced here */
Vec3f D_ovl12_04_800450A0;
u8 D_ovl12_04_800450AC[0x4]; /* not referenced here */
UnkStruct_ovl12_04_800450B0 D_ovl12_04_800450B0;

/* .data */
/* passed to func_ovl12_04_80044B80: three 12-byte records */
u32 D_ovl12_04_80044FC0[][3] = {
    { 0x970000, 0xF, 0x2004 },
    { 0xCF0000, 0xE, 4 },
    { 0xD00002, 0xF, 4 },
};
/* passed to func_ovl12_04_80044B98 */
u32 D_ovl12_04_80044FE4[][3] = {
    { 0x980000, 0x84, 0 },
    { 4, 0, 4 },
};
/* two 12-byte records, each passed to func_ovl12_04_80044D28 */
u32 D_ovl12_04_80044FFC[][3] = {
    { 0, 0x21, 0xFF },
    { 1, 0x1F, 0xFD },
};

void func_ovl12_04_80043010(void) {
}

void func_ovl12_04_80043018(void) {
}

void func_ovl12_04_80043020(void) {
    func_ovl12_04_80043F10(1);
}

void func_ovl12_04_80043040(void) {
    func_ovl12_04_80043F10(1);
}

void func_ovl12_04_80043060(void) {
}

void func_ovl12_04_80043068(void) {
    D_ovl12_04_8004508C = func_ovl12_04_80043EA8();
    func_ovl12_04_80043E88(&D_ovl12_04_80045080);
    func_ovl12_04_80043EB0(D_ovl12_04_8004508C, D_ovl12_04_80045070);
}

void func_ovl12_04_800430B0(void) {
    UNK_MACRO_ovl12_04_800430B0();
}

void func_ovl12_04_800430F8(void) {
}

void func_ovl12_04_80043100(void) {
}

void func_ovl12_04_80043108(void) {
    if (func_ovl12_04_80043E90(0x1D, 1, 0x1E, 2) != 0) {
        func_ovl12_04_80043DC0(0x7B, 0x12, 0);
    }
    if (func_ovl12_04_80043E90(0xC, 0x16, 0xD, 0x17) != 0) {
        func_ovl12_04_80043DC0(0x7B, 0x12, 0);
    }
}

void func_ovl12_04_80043170(void) {
    func_ovl12_04_80043EC8(D_ovl12_04_800450B0.unk4, 3, 4.0f, D_ovl12_04_800450B0.unk10, 0, 1, 1);
}

void func_ovl12_04_800431B8(void) {
    func_ovl12_04_80043170();
}

void func_ovl12_04_800431D8(f32 arg0) {
    f32 sp1C;

    func_ovl12_04_80044530(&sp1C, NULL, NULL);
    func_ovl12_04_80044528(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl12_04_80043220(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl12_04_80043ED8();
    switch (D_ovl12_04_800450B0.unk8) {
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
        func_ovl12_04_80044528(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl12_04_800450B0.unkC;
        func_ovl12_04_80044530(&sp1C, NULL, NULL);
        func_ovl12_04_80044528(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl12_04_80043EC0(D_ovl12_04_800450B0.unk4);
}

void func_ovl12_04_80043338(void) {
    func_ovl12_04_80043220();
}

void func_ovl12_04_80043358(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl12_04_800450B0.unk0 = arg0;
    D_ovl12_04_800450B0.unk4 = arg1;
    D_ovl12_04_800450B0.unk8 = arg2;
    D_ovl12_04_800450B0.unkC = arg3;
    D_ovl12_04_800450B0.unk10 = arg4;
}

void func_ovl12_04_80043380(void) {
    func_ovl12_04_80043E80(0x1D, 4, 2);
    UNK_MACRO_ovl12_04_800450B0(2, 0x80, 0, 0.0f, 2);
}

void func_ovl12_04_800433CC(void) {
    func_ovl12_04_80043E80(0x13, 4, 7);
    UNK_MACRO_ovl12_04_800450B0(1, 0x80, 0, 0.0f, 0);
}

void func_ovl12_04_80043418(void) {
}

void func_ovl12_04_80043420(void) {
    func_ovl12_04_80044A98(0x400);
    func_ovl12_04_80044A98(0x401);
    func_ovl12_04_80044A98(0x402);
    func_ovl12_04_80044A98(0x403);
    func_ovl12_04_80044A98(0x404);
}

void func_ovl12_04_80043460(void) {
    UnkStructA *obj;

    func_ovl12_04_80043420();
    func_ovl12_04_80043DB0(func_ovl12_04_80043810);
    func_ovl12_04_80043E00(func_ovl12_04_80043750);
    obj = func_ovl12_04_800448A0(0x2E5);
    func_ovl12_04_800448B0(obj, 0x20000001);
    obj->unk18 = 0.03f;
    obj->unk1C = 0.0f;
}

void func_ovl12_04_800434CC(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl12_04_80043460();
    func_ovl12_04_80044B80(D_ovl12_04_80044FC0);
    func_ovl12_04_80044B98(D_ovl12_04_80044FE4);
    func_ovl12_04_80043CC8(0x2DA);
    p = D_ovl12_04_80044FFC;
    count = 2;
    for (i = 0; i < count; i++) {
        func_ovl12_04_80044D28((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl12_04_80043CE0(0x2E2);
    func_ovl12_04_80043E78();
    func_ovl12_04_80044B40(0, 0x72, 0x37);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl12_04_80043570(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl12_04_800434CC();
            break;
        case 17:
            func_ovl12_04_800433CC();
            break;
        case 18:
            func_ovl12_04_80043380();
            break;
        case 4:
            func_ovl12_04_80043220();
            break;
        case 5:
            func_ovl12_04_80043170();
            break;
        case 0x50:
            func_ovl12_04_80043108();
            break;
        case 3:
            UNK_MACRO_ovl12_04_800430B0();
            break;
        case 12:
            func_ovl12_04_80043F10(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl12_04_80043690(UnkStructA *arg0) {
    s32 hit;
    s32 t;

    func_ovl12_04_80044D18(arg0, 0, 5.0f);
    hit = FALSE;
    if (arg0->unk8 & 1) {
        t = func_ovl12_04_80043F48(func_ovl12_04_80043EA8());
        if (t != 0) {
            if (func_ovl12_04_800447E8(arg0, 0x10, t) != 0) {
                hit = TRUE;
            }
        } else if (func_ovl12_04_80044678(arg0, 0x10) != 0) {
            hit = TRUE;
        }
    } else if (func_ovl12_04_80044678(arg0, 0x10) != 0) {
        hit = TRUE;
    }
    if (hit) {
        func_ovl12_04_80044D18(arg0, 0x80, 5.0f);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/overlays/ovl_12_04/253A10/func_ovl12_04_80043750.s")

void func_ovl12_04_80043810(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl12_04_80044570(0x10);
    }
    func_ovl12_04_800446D0(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        func_ovl12_04_80044748(arg0);
        func_ovl12_04_80044860();
    }
}

void func_ovl12_04_80043888(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01: without it arg1 is spilled */
    }
    func_ovl12_04_80044DC0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl12_04_800438BC(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl12_04_80044508(D_ovl12_04_800450A0.x, D_ovl12_04_800450A0.y, D_ovl12_04_800450A0.z);
    func_ovl12_04_80044528(arg0, arg1, arg2);
    func_ovl12_04_80044838(180);
}

void func_ovl12_04_80043918(void) {
    D_ovl12_04_80045094 = -1;
    D_ovl12_04_80045098 = -1;
}

void func_ovl12_04_80043930(void) {
}

void func_ovl12_04_80043938(void) {
}

void func_ovl12_04_80043940(void) {
}

void func_ovl12_04_80043948(void) {
}

void func_ovl12_04_80043950(void) {
}

void func_ovl12_04_80043958(void) {
}

void func_ovl12_04_80043960(void) {
}

void func_ovl12_04_80043968(void) {
}

void func_ovl12_04_80043970(void) {
}

void func_ovl12_04_80043978(void) {
}
