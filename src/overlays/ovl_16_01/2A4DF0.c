#include "common.h"

/*
 * ovl_16_01's game object, built -g (as its entry): every value goes through
 * the stack, each function ends in two `jr ra`, and the returns are branches
 * to the epilogue.  It is the other overlays' template with its debug
 * messages kept (func_ovl16_01_80043020).
 */

/* an object placed in the stage (as ovl_17_01's) */
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
} UnkStruct_ovl16_01_80043020; /* size 0x38 */

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} UnkStruct_ovl16_01_800436B0_4;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_ovl16_01_800436B0_4 *unk4;
} UnkStruct_ovl16_01_800436B0_48;

typedef struct {
    /* 0x00 */ u8 unk0[0x48];
    /* 0x48 */ UnkStruct_ovl16_01_800436B0_48 *unk48;
} UnkStruct_ovl16_01_800436B0_40;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl16_01_800436B0_40 *unk40;
} UnkStruct_ovl16_01_800436B0;

void func_ovl16_01_80043D38(const char *, ...);
void func_ovl16_01_80044068(s32);
void func_ovl16_01_80044080(s32);
s32 func_ovl16_01_800440D0(s32);
void func_ovl16_01_80044158(s32, s32, s32);
void func_ovl16_01_800441F8(void);
void func_ovl16_01_80044200(s32, s32, s32);
void func_ovl16_01_80044208(Vec3f *);
s32 func_ovl16_01_80044228(void);
void func_ovl16_01_80044230(s32, Vec3f *);
void func_ovl16_01_80044238(s32);
void func_ovl16_01_80044258(void);
f32 func_ovl16_01_80044740(void *, s32);
s32 func_ovl16_01_80044748(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl16_01_80044750(s32);
void func_ovl16_01_80044768(s32, s32);
void func_ovl16_01_80044840(f32, f32, f32);
void func_ovl16_01_80044860(f32, f32, f32);
void func_ovl16_01_80044868(f32 *, f32 *, f32 *);
void func_ovl16_01_800448B8(s32);
void func_ovl16_01_80044990(s32, Vec3f *, Vec3f *);
void func_ovl16_01_80044A00(UnkStructA *, s32);
void func_ovl16_01_80044A08(UnkStructA *, s32);
void func_ovl16_01_80044A18(UnkStructA *);
UnkStructA *func_ovl16_01_80044A48(s32, s32, f32, f32, f32);
void func_ovl16_01_80044B68(s32);
void func_ovl16_01_80044B90(void);
void func_ovl16_01_80044D78(s32);
void func_ovl16_01_80044D80(s32);
s32 func_ovl16_01_80044D88(s32);
s32 func_ovl16_01_80044F28(s32, Vec3f *, s32);
void func_ovl16_01_80044F30(s32);
void func_ovl16_01_80044F98(s32, s32, s32);
void func_ovl16_01_80044FA8(s32, f32, f32, f32);
s32 func_ovl16_01_80044FE0(void);
void func_ovl16_01_80045010(s32, f32, f32, f32);

void func_ovl16_01_80043504(void);
void func_ovl16_01_80043B7C(void);
void func_ovl16_01_80043BBC(void);
void func_ovl16_01_80043C6C(void);
void func_ovl16_01_80043C98(void);
void func_ovl16_01_80043CE0(void);
void func_ovl16_01_80043D18(void);

/* .bss */
Vec3f D_ovl16_01_800452A0;
u8 D_ovl16_01_800452AC[0x4];
Vec3f D_ovl16_01_800452B0;
s32 D_ovl16_01_800452BC;
s32 D_ovl16_01_800452C0;
s32 D_ovl16_01_800452C4;
s32 D_ovl16_01_800452C8;
u8 D_ovl16_01_800452CC[0x4];
Vec3f D_ovl16_01_800452D0;

void func_ovl16_01_80043020(UnkStruct_ovl16_01_80043020 *arg0) {
    arg0->unk0 = func_ovl16_01_80044A48(arg0->unk8, 0xC00, 0.0f, 0.0f, 0.0f);
    func_ovl16_01_80044A00(arg0->unk0, 0x01080000);
    func_ovl16_01_80044A08(arg0->unk0, 0x02000000);
    if (arg0->unkC != -1 && arg0->unkE != -1 && arg0->unk10 != -1 && arg0->unk12 != -1) {
        arg0->unk4 = func_ovl16_01_80044748(arg0->unk0->unk40, 0, arg0->unkC, arg0->unkE, arg0->unk10, arg0->unk12);
        if (arg0->unk4 == -1) {
            func_ovl16_01_80043D38("MapObjEntry : EvObjShiftCreate can't entry\n");
            func_ovl16_01_80043D38("request resource %d\n", arg0->unk8);
            func_ovl16_01_80043D38("p->sstep p->smax : %04x %04x\n", arg0->unkC, arg0->unkE);
            func_ovl16_01_80043D38("p->tstep p->tmax : %04x %04x\n", arg0->unk10, arg0->unk12);
            while (TRUE) {
            }
        }
    }
    arg0->unk0->unk40->unk10 = arg0->unk14 * 10.0f;
    arg0->unk0->unk40->unk14 = arg0->unk18 * 10.0f;
    arg0->unk0->unk40->unk18 = arg0->unk1C * 10.0f;
    arg0->unk0->unk40->unk1C = arg0->unk20;
    arg0->unk0->unk40->unk20 = arg0->unk24;
    arg0->unk0->unk40->unk24 = arg0->unk28;
    arg0->unk0->unk40->unk28 = arg0->unk2C;
    arg0->unk0->unk40->unk2C = arg0->unk30;
    arg0->unk0->unk40->unk30 = arg0->unk34;
}

void func_ovl16_01_8004329C(UnkStruct_ovl16_01_80043020 *arg0) {
    func_ovl16_01_80044A18(arg0->unk0);
    /* 0xFFFF where 80043020 has -1: `li at, 0xffff` */
    if (arg0->unkC != 0xFFFF && arg0->unkE != 0xFFFF && arg0->unk10 != 0xFFFF && arg0->unk12 != 0xFFFF) {
        func_ovl16_01_80044750(arg0->unk4);
    }
    arg0->unk0 = NULL;
    arg0->unk4 = -1;
}

s32 func_ovl16_01_80043348(UnkStruct_ovl16_01_80043020 *arg0) {
    if (arg0->unk0->unk40->unk20 == 0.0f) {
        return 0;
    }
    if (arg0->unk0->unk40->unk20 == 90.0f) {
        return 1;
    }
    if (arg0->unk0->unk40->unk20 == 180.0f) {
        return 2;
    }
    if (arg0->unk0->unk40->unk20 == 270.0f || arg0->unk0->unk40->unk20 == -90.0f) {
        return 3;
    }
    return -1;
}

void func_ovl16_01_80043448(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 max;

    switch (arg0) {
        case 0:
            max = arg2[0];
            break;
        case 1:
            max = arg2[1];
            break;
        case 2:
            max = arg2[2];
            break;
    }
    if (*arg1 < 0) {
        *arg1 = 0;
    } else if (*arg1 >= max) {
        *arg1 = max - 1;
    }
}

void func_ovl16_01_80043504(void) {
    D_ovl16_01_800452BC = func_ovl16_01_80044228();
    func_ovl16_01_80044208(&D_ovl16_01_800452B0);
    func_ovl16_01_80044230(D_ovl16_01_800452BC, &D_ovl16_01_800452A0);
}

void func_ovl16_01_80043554(s32 arg0, Vec3f *arg1) {
    func_ovl16_01_80044990(arg0, &D_ovl16_01_800452A0, arg1);
    arg1->y = arg1->y + 90.0f >= 360.0f ? arg1->y + 90.0f - 360.0f
            : arg1->y + 90.0f < 0.0f    ? arg1->y + 90.0f + 360.0f
                                        : arg1->y + 90.0f;
}

void func_ovl16_01_8004363C(UnkStructA *arg0) {
    while (!(arg0->unk40->unkC & 0x40)) {
        func_ovl16_01_80044B90();
    }
}

void func_ovl16_01_800436B0(UnkStruct_ovl16_01_800436B0 *arg0) {
    arg0->unk40->unk48->unk4->unk4 = func_ovl16_01_80044740(arg0->unk40, 0) - 0.001f;
}

void func_ovl16_01_8004370C(u32 (*arg0)[3], s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++, arg0++) {
        func_ovl16_01_80044F98((*arg0)[0], (*arg0)[1], (*arg0)[2]);
    }
}

void func_ovl16_01_80043784(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;

    D_ovl16_01_800452D0.x = arg1 * 100.0f;
    D_ovl16_01_800452D0.y = 0.0f;
    for (i = 0; i < arg2; i++) {
        D_ovl16_01_800452D0.y += func_ovl16_01_800440D0(i) * 100.0f;
    }
    D_ovl16_01_800452D0.y += 100.0f;
    D_ovl16_01_800452D0.z = arg3 * 100.0f;
    D_ovl16_01_800452C0 = func_ovl16_01_80044F28(arg0, &D_ovl16_01_800452D0, 0);
}

void func_ovl16_01_8004389C(void) {
    func_ovl16_01_80044F30(D_ovl16_01_800452C0);
}

void func_ovl16_01_800438CC(s32 arg0, s32 arg1, s32 arg2) {
    D_ovl16_01_800452C4 = arg0;
    D_ovl16_01_800452C8 = arg1;
    func_ovl16_01_80044158(arg0, arg1, arg2);
}

void func_ovl16_01_80043924(void) {
    D_ovl16_01_800452C4 = -1;
    D_ovl16_01_800452C8 = -1;
}

void func_ovl16_01_8004394C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl16_01_80044840(D_ovl16_01_800452D0.x, D_ovl16_01_800452D0.y, D_ovl16_01_800452D0.z);
    func_ovl16_01_80044860(arg0, arg1, arg2);
    func_ovl16_01_80044B68(180);
}

void func_ovl16_01_800439B0(f32 arg0) {
    f32 sp1C;

    func_ovl16_01_80044868(&sp1C, NULL, NULL);
    func_ovl16_01_80044860(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl16_01_80043A00(s32 arg0, UnkStructA *arg1) {
    func_ovl16_01_80045010(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
    return; /* a second branch to the epilogue */
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl16_01_80043A54(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl16_01_80043B7C();
            break;
        case 16:
            break;
        case 4:
            func_ovl16_01_80043BBC();
            break;
        case 5:
            func_ovl16_01_80043C6C();
            break;
        case 0x50:
            break;
        case 0x52:
            break;
        case 0x53:
            break;
        case 3:
            func_ovl16_01_80043C98();
            break;
        case 12:
            func_ovl16_01_80043CE0();
            break;
        case 1:
            func_ovl16_01_80043D18();
            break;
    }
}

void func_ovl16_01_80043B7C(void) {
    func_ovl16_01_80044068(0x233);
    func_ovl16_01_80044080(0x234);
    func_ovl16_01_800441F8();
    func_ovl16_01_80044D80(0x400);
}

void func_ovl16_01_80043BBC(void) {
    func_ovl16_01_80044200(0x17, 0, 0x10);
    func_ovl16_01_80044258();
    func_ovl16_01_80044860(0.0f, 32768.0f, 32768.0f);
    func_ovl16_01_80043504();
    func_ovl16_01_80044F98(0, 7, 0xCE);
    func_ovl16_01_80044FA8(0, D_ovl16_01_800452A0.x, D_ovl16_01_800452A0.y, D_ovl16_01_800452A0.z - 500.0f);
    func_ovl16_01_800448B8(0);
    func_ovl16_01_80044860(0.0f, 45.0f, 32768.0f);
}

void func_ovl16_01_80043C6C(void) {
    func_ovl16_01_80044768(0x269, 3);
}

void func_ovl16_01_80043C98(void) {
    if (func_ovl16_01_80044FE0() == 0) {
        func_ovl16_01_80044D78(0x400);
        func_ovl16_01_80044158(0x20, 0x11, 0);
    }
}

void func_ovl16_01_80043CE0(void) {
    if (func_ovl16_01_80044D88(0x400) != 0) {
        func_ovl16_01_80044238(1);
    }
}

void func_ovl16_01_80043D18(void) {
}
