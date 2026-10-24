#include "common.h"

/*
 * ovl_17_10's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

/* a model placed in the stage: two rows of three (D_ovl17_10_800464C8,
 * D_ovl17_10_80046570) */
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
} UnkStruct_ovl17_10_800464C8; /* size 0x38 */

/* the argument of func_ovl17_10_8004412C's tasks */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} UnkStruct_ovl17_10_80046730; /* size 0x8 */

/* a model moved by func_ovl17_10_80043754's task (D_ovl17_10_80046618) */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
} UnkStruct_ovl17_10_80046618; /* size 0x10 */

/* a model moved by func_ovl17_10_800434CC's tasks (D_ovl17_10_80046628) */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
} UnkStruct_ovl17_10_80046628; /* size 0xC */

/* the argument of func_ovl17_10_80044AC8's tasks */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl17_10_80046748; /* size 0x10 */

void func_ovl17_10_80045198(s32);
void func_ovl17_10_800451B0(s32);
f32 func_ovl17_10_800451C0(void);
void func_ovl17_10_80045310(s32);
UnkStructB *func_ovl17_10_80045318(void);
void func_ovl17_10_80045348(void);
void func_ovl17_10_800458A0(UnkStructA_40 *, s32);
void func_ovl17_10_800458A8(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl17_10_800458E0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl17_10_800459B8(s32);
void func_ovl17_10_800459C8(s32);
void func_ovl17_10_800459D8(f32, f32, f32);
void func_ovl17_10_800459F8(f32, f32, f32);
void func_ovl17_10_80045A00(f32 *, f32 *, f32 *);
void func_ovl17_10_80045A40(s32);
void func_ovl17_10_80045AB0(s32);
void func_ovl17_10_80045AC0(f32, f32, f32);
void func_ovl17_10_80045B98(UnkStructA *, s32);
void func_ovl17_10_80045BA0(UnkStructA *, s32);
void func_ovl17_10_80045BB0(UnkStructA *);
UnkStructA *func_ovl17_10_80045BD0(UnkStructA *);
UnkStructA *func_ovl17_10_80045BE0(s32, s32, f32, f32, f32);
void func_ovl17_10_80045C18(UnkStructA *);
void func_ovl17_10_80045CA8(UnkStructA *);
s32 func_ovl17_10_80045CE8(void (*)(void), void *, s32, s32, s32);
void func_ovl17_10_80045CF8(void);
void func_ovl17_10_80045D08(s32);
void *func_ovl17_10_80045D10(void);
s32 func_ovl17_10_80045D30(void);
f32 func_ovl17_10_80045E90(f32);
s32 func_ovl17_10_80045EA8(s32);
void func_ovl17_10_80045FE8(s32, s32, s32, f32);
void func_ovl17_10_80046050(u32 (*)[3]);
void func_ovl17_10_80045278(void (*)(UnkStructA *), s32);
void func_ovl17_10_80045280(void (*)(UnkStructA *));
UnkStructA *func_ovl17_10_800453D8(s32);
UnkStructA *func_ovl17_10_80045418(s32);
s32 func_ovl17_10_80045B48(UnkStructA *, s32);
s32 func_ovl17_10_80045CB8(UnkStructA *, s32, UnkStructA *);
f32 func_ovl17_10_80045E98(f32);
s32 func_ovl17_10_80046190(UnkStructA *);
void func_ovl17_10_80046290(s32, f32, f32, f32);

void func_ovl17_10_80043010(void);
void func_ovl17_10_80043034(void);
void func_ovl17_10_80043990(UnkStruct_ovl17_10_80046730 *, s16, s16);
void func_ovl17_10_80043D28(void);
void func_ovl17_10_80043E14(void);
void func_ovl17_10_80044048(f32, f32, f32, f32);
void func_ovl17_10_8004412C(void);
void func_ovl17_10_80044AC8(void);
void func_ovl17_10_8004309C(void);
void func_ovl17_10_80043158(void);
void func_ovl17_10_800431C8(void);
void func_ovl17_10_80043288(void);
void func_ovl17_10_800434CC(void);
void func_ovl17_10_80043754(void);
void func_ovl17_10_80043970(UnkStructA *);
void func_ovl17_10_8004455C(UnkStructA *);
void func_ovl17_10_80044564(UnkStructA *);

/* .bss */
u8 D_ovl17_10_800466F0[0x24];
s32 D_ovl17_10_80046714;
s32 D_ovl17_10_80046718;
u8 D_ovl17_10_8004671C[0x4];
Vec3f D_ovl17_10_80046720;
u8 D_ovl17_10_8004672C[0x4];
UnkStruct_ovl17_10_80046730 D_ovl17_10_80046730[3];
UnkStruct_ovl17_10_80046748 D_ovl17_10_80046748[3];

/* .data */
f32 D_ovl17_10_80046490 = 0.01f;
f32 D_ovl17_10_80046494 = 0.1f;
s32 D_ovl17_10_80046498 = 0;
s32 D_ovl17_10_8004649C = 0;
UnkStructA *D_ovl17_10_800464A0 = NULL;
/* passed to func_ovl17_10_80046050: three 12-byte records */
u32 D_ovl17_10_800464A4[][3] = {
    { 0xDB0000, 0x6000C, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
UnkStruct_ovl17_10_800464C8 D_ovl17_10_800464C8[3] = {
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl17_10_800464C8 D_ovl17_10_80046570[3] = {
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
UnkStruct_ovl17_10_80046618 D_ovl17_10_80046618[1] = {
    { NULL, 1000, -500, 500, 3500, 2500, 0 },
};
UnkStruct_ovl17_10_80046628 D_ovl17_10_80046628[5] = {
    { NULL, 1200, -100, 400 },
    { NULL, 1000, -200, 500 },
    { NULL, 1000, -100, 200 },
    { NULL, 900, -500, 400 },
    { NULL, 800, -300, 300 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl17_10_80044E40(void) {
    D_ovl17_10_800466F0[0] = D_ovl17_10_8004671C[0] + D_ovl17_10_8004672C[0];
}

static void func_ovl17_10_80044E38(void) {
}

static void func_ovl17_10_80044E30(void) {
}

static void func_ovl17_10_80044E28(void) {
}

static void func_ovl17_10_80044E20(void) {
}

static void func_ovl17_10_80044E18(void) {
}

static void func_ovl17_10_80044E10(void) {
}

static void func_ovl17_10_80044E08(void) {
}

static void func_ovl17_10_80044E00(void) {
}

static void func_ovl17_10_80044DF8(void) {
}

static void func_ovl17_10_80044DF0(void) {
}

static void func_ovl17_10_80044DE8(void) {
}

static void func_ovl17_10_80044DE0(void) {
}

static void func_ovl17_10_80044DD8(void) {
}

static void func_ovl17_10_80044DD0(void) {
}

static void func_ovl17_10_80044DC8(void) {
}

static void func_ovl17_10_80044DC0(void) {
}

static void func_ovl17_10_80044DB8(void) {
}

static void func_ovl17_10_80044DB0(void) {
}

static void func_ovl17_10_80044DA8(void) {
}

void func_ovl17_10_80044D90(void) {
    D_ovl17_10_80046714 = -1;
    D_ovl17_10_80046718 = -1;
}

void func_ovl17_10_80044D34(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl17_10_800459D8(D_ovl17_10_80046720.x, D_ovl17_10_80046720.y, D_ovl17_10_80046720.z);
    func_ovl17_10_800459F8(arg0, arg1, arg2);
    func_ovl17_10_80045D08(180);
}

void func_ovl17_10_80044CEC(f32 arg0) {
    f32 sp1C;

    func_ovl17_10_80045A00(&sp1C, NULL, NULL);
    func_ovl17_10_800459F8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl17_10_80044CB8(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl17_10_80046290(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl17_10_80044AC8(void) {
    UnkStructA *obj;
    s32 i;
    s16 alpha;
    f32 scale;
    s32 step;
    UnkStruct_ovl17_10_80046748 *arg;

    arg = func_ovl17_10_80045D10();
    obj = func_ovl17_10_80045BE0(0x11A, 0x20, arg->unk4, arg->unk6, arg->unk8);
    func_ovl17_10_80045B98(obj, 0x0D080040);
    arg->unk0 = obj;
    obj->unk40->unkC |= 0x8000;
    obj->unk30 = 1;
    obj->unk34 = 90.0f;
    obj->unk38 = 0.0f;
    func_ovl17_10_800458A0(obj->unk40, 2);
    func_ovl17_10_800458A8(obj->unk40, 0x11B, 0, 0);
    func_ovl17_10_800458A8(obj->unk40, 0x11B, 1, 1);
    obj->unk40->unk28 = 0.5f;
    obj->unk40->unk2C = 0.5f;
    obj->unk40->unk30 = 0.5f;
    obj->unk40->unk36 = 0xFF;
    alpha = 0xFF;
    step = 4;
    for (i = 0; i < 90; i += step) {
        scale = (D_ovl17_10_80046748[0].unkC - 0.5f) * func_ovl17_10_80045E90(i) + 0.5f;
        obj->unk40->unk30 = scale;
        obj->unk40->unk2C = scale;
        obj->unk40->unk28 = scale;
        obj->unk40->unk36 = alpha;
        alpha -= 5;
        func_ovl17_10_80045CA8(obj);
        func_ovl17_10_80045D30();
    }
    obj->unk40->unk28 = D_ovl17_10_80046748[0].unkC;
    obj->unk40->unk2C = D_ovl17_10_80046748[0].unkC;
    obj->unk40->unk30 = D_ovl17_10_80046748[0].unkC;
    func_ovl17_10_80045BB0(obj);
    arg->unk0 = NULL;
    func_ovl17_10_80045CF8();
}

static void func_ovl17_10_8004454C(s16 hi, s16 lo, Vec3f *vel) {
    vel->x = hi * 0.002f;
    vel->z = lo * 0.002f;
}

static UnkStructA_40 *func_ovl17_10_80044554(UnkStructA *obj) {
    return obj->unk40;
}

static s32 func_ovl17_10_80044464(UnkStructA *obj) {
    s32 saved;
    s32 hit;
    UnkStructA *other;
    s32 idx;
    s32 i;
    s32 k;

    saved = obj->unkC;
    hit = FALSE;
    other = NULL;
    obj->unkC = 0;
    if (obj->unk8 & 1) {
        idx = -1;
        for (i = 0; i < 4; i++) {
            if (func_ovl17_10_800453D8(i) == obj) {
                idx = i;
                break;
            }
        }
        other = func_ovl17_10_80045418(idx);
    } else if (obj->unk8 & 2) {
        k = func_ovl17_10_80046190(obj);
        if (func_ovl17_10_80045418(k) == obj) {
            other = func_ovl17_10_800453D8(k);
        }
    }
    if (other != NULL) {
        if (func_ovl17_10_80045CB8(obj, 0x10, other) != 0) {
            hit = TRUE;
        }
    } else {
        if (func_ovl17_10_80045B48(obj, 0x10) != 0) {
            hit = TRUE;
        }
    }
    obj->unkC = saved;
    return hit;
}

static void func_ovl17_10_80044454(UnkStructA *obj, f32 vx, f32 vz) {
    obj->unk64 = ((s16) (vx * 500.0f) << 16) | ((s16) (vz * 500.0f) & 0xFFFF);
}

static void func_ovl17_10_8004445C(UnkStructA *obj, f32 x, f32 y, f32 z) {
    func_ovl17_10_80044454(obj, 0.0f, 0.0f);
    obj->unk40->unk10 = x;
    obj->unk40->unk14 = y;
    obj->unk40->unk18 = z;
}

void func_ovl17_10_80044564(UnkStructA *obj) {
    Vec3f vel;
    f32 dx;
    f32 dz;
    Vec3f pos;

    dx = obj->unk40->unk10 - obj->unk58;
    dz = obj->unk40->unk18 - obj->unk60;
    if (obj->unk8 & 1) {
        D_ovl17_10_8004649C = 1;
        D_ovl17_10_800464A0 = obj;
    } else {
        D_ovl17_10_8004649C = 0;
        D_ovl17_10_800464A0 = NULL;
    }
    if (obj->unk68 != 0.0f || obj->unk6C != 0.0f) {
        func_ovl17_10_8004455C(obj);
        return;
    }
    pos.x = obj->unk40->unk10;
    pos.y = obj->unk40->unk14;
    pos.z = obj->unk40->unk18;
    func_ovl17_10_8004454C(obj->unk64 >> 16, obj->unk64 & 0xFFFF, &vel);
    if ((s32) dx != (s32) vel.x) {
        obj->unk40->unk10 = obj->unk58;
        if ((s32) dx < (s32) vel.x) {
            vel.x -= (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl17_10_80046494 : D_ovl17_10_80046490);
            if (vel.x < dx) {
                vel.x = dx;
            }
        } else if ((s32) vel.x < (s32) dx) {
            vel.x += (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl17_10_80046494 : D_ovl17_10_80046490);
            if (dx < vel.x) {
                vel.x = dx;
            }
        }
        func_ovl17_10_80044554(obj)->unk10 += vel.x;
    }
    if ((s32) dz != (s32) vel.z) {
        obj->unk40->unk18 = obj->unk60;
        if ((s32) dz < (s32) vel.z) {
            vel.z -= (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl17_10_80046494 : D_ovl17_10_80046490);
            if (vel.z < dz) {
                vel.z = dz;
            }
        } else if ((s32) vel.z < (s32) dz) {
            vel.z += (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl17_10_80046494 : D_ovl17_10_80046490);
            if (dz < vel.z) {
                vel.z = dz;
            }
        }
        func_ovl17_10_80044554(obj)->unk18 += vel.z;
    }
    if (func_ovl17_10_80044464(obj)) {
        func_ovl17_10_8004445C(obj, pos.x, pos.y, pos.z);
    } else {
        func_ovl17_10_80044454(obj, vel.x, vel.z);
    }
}

void func_ovl17_10_8004455C(UnkStructA *arg0) {
    arg0->unk64 = 0;
}

void func_ovl17_10_80044048(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStruct_ovl17_10_80046748 *p;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_ovl17_10_80046748[i].unk0 == NULL) {
            break;
        }
    }
    p = &D_ovl17_10_80046748[i];
    if (p < &D_ovl17_10_80046748[3]) {
        p->unk4 = arg0;
        p->unk6 = arg1;
        p->unk8 = arg2;
        p->unkC = arg3;
        func_ovl17_10_80045CE8(func_ovl17_10_80044AC8, p, 0, 0, 0x110);
    }
}

void func_ovl17_10_8004412C(void) {
    UnkStruct_ovl17_10_80046730 *arg;
    UnkStruct_ovl17_10_800464C8 *a;
    UnkStruct_ovl17_10_800464C8 *b;
    f32 scale;

    func_ovl17_10_80045D30();
    arg = func_ovl17_10_80045D10();
    a = &D_ovl17_10_800464C8[arg->unk0];
    b = &D_ovl17_10_80046570[arg->unk0];
    a->unk0->unk40->unk10 = arg->unk2 * 100.0f;
    b->unk0->unk40->unk10 = a->unk0->unk40->unk10;
    a->unk0->unk40->unk14 = 3000.0f;
    b->unk0->unk40->unk14 = a->unk0->unk40->unk14;
    a->unk0->unk40->unk18 = arg->unk4 * 100.0f;
    b->unk0->unk40->unk18 = a->unk0->unk40->unk18 + 10.0f;
    b->unk0->unk68 = 0.0f;
    a->unk0->unk68 = b->unk0->unk68;
    b->unk0->unk70 = 1.6333334f;
    a->unk0->unk70 = b->unk0->unk70;
    func_ovl17_10_80045B98(a->unk0, 0x01000000);
    func_ovl17_10_80045B98(b->unk0, 0x01000000);
    while (TRUE) {
        func_ovl17_10_80045C18(a->unk0);
        b->unk0->unk40->unk14 = a->unk0->unk40->unk14;
        if (a->unk0->unk40->unk14 <= func_ovl17_10_800451C0() ||
            (a->unk0->unk6C == 0.0f && a->unk0->unk68 == 0.0f)) {
            func_ovl17_10_80045BA0(a->unk0, 0x01000000);
            func_ovl17_10_80045BA0(b->unk0, 0x01000000);
            func_ovl17_10_80046290(0x7C, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
            scale = (1.0f - func_ovl17_10_80045318()->unk30 / 60.0f) * 1.5f + 2.0f;
            func_ovl17_10_80044048(a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18, scale);
            arg->unk6 |= 1;
            func_ovl17_10_80045CF8();
        }
        func_ovl17_10_80045D30();
    }
}

void func_ovl17_10_80044014(void) {
    func_ovl17_10_80045AC0(20.0f, 20.0f, 20.0f);
    func_ovl17_10_80045AB0(120);
}

void func_ovl17_10_80043E14(void) {
    UnkStructB *b;
    s16 i;
    s16 j;
    s16 n;

    n = 5;
    b = func_ovl17_10_80045318();
    while (TRUE) {
        if (b->unk2C <= 0) {
            break;
        }
        func_ovl17_10_80045D30();
    }
    func_ovl17_10_80043D28();
    for (i = 0; i < 3; i++) {
        D_ovl17_10_80046730[i].unk0 = i;
    }
    while (TRUE) {
        for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
            D_ovl17_10_80046730[j].unk6 = 0;
        }
        func_ovl17_10_80043990(D_ovl17_10_80046730, 16, 14);
        func_ovl17_10_80045CE8(func_ovl17_10_8004412C, &D_ovl17_10_80046730[0], 0, 0, 0x110);
        func_ovl17_10_80045D08(func_ovl17_10_80045EA8(10) + 5);
        func_ovl17_10_80045CE8(func_ovl17_10_8004412C, &D_ovl17_10_80046730[1], 0, 0, 0x110);
        func_ovl17_10_80045D08(func_ovl17_10_80045EA8(10) + 5);
        func_ovl17_10_80045CE8(func_ovl17_10_8004412C, &D_ovl17_10_80046730[2], 0, 0, 0x110);
        func_ovl17_10_80045D30();
            while (TRUE) {
                if ((D_ovl17_10_80046730[0].unk6 & 1) && (D_ovl17_10_80046730[1].unk6 & 1) &&
                    (D_ovl17_10_80046730[2].unk6 & 1)) {
                    break;
                }
                func_ovl17_10_80045D30();
            }
        func_ovl17_10_80045D30();
        }
        func_ovl17_10_80045D08(func_ovl17_10_80045EA8(60) + 30);
    }
}

static void func_ovl17_10_80043BA8(UnkStruct_ovl17_10_800464C8 *e) {
    e->unk0 = func_ovl17_10_80045BE0(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl17_10_80045B98(e->unk0, 0x01080000);
    func_ovl17_10_80045BA0(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl17_10_800458E0(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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

void func_ovl17_10_80043D28(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 3; i++) {
        func_ovl17_10_80043BA8(&D_ovl17_10_800464C8[i]);
        obj = func_ovl17_10_80045BD0(D_ovl17_10_800464C8[i].unk0);
        obj->unk54 = 2.0f;
        obj->unk4C = 2.0f;
        obj->unk40->unk36 = 0xCC;
        func_ovl17_10_80045BA0(D_ovl17_10_800464C8[i].unk0, 0x80000);
        func_ovl17_10_80045BA0(D_ovl17_10_800464C8[i].unk0, 0x01000000);
        func_ovl17_10_80043BA8(&D_ovl17_10_80046570[i]);
        func_ovl17_10_80045BA0(D_ovl17_10_80046570[i].unk0, 0x01000000);
    }
}

void func_ovl17_10_80043990(UnkStruct_ovl17_10_80046730 *arg0, s16 arg1, s16 arg2) {
    s32 pad; /* unused: the original's frame is 4 bytes bigger */
    s16 xs[3];
    s16 ys[3];
    s16 i;
    s16 j;
    s16 tries;

    for (i = 0, tries = 0; i < 3;) {
        xs[i] = func_ovl17_10_80045EA8(arg1);
        ys[i] = func_ovl17_10_80045EA8(arg2);
        if (tries++ >= 6) {
            xs[i] = arg1;
            ys[i] = arg2;
            tries = 0;
            i++;
        } else {
            for (j = 0; j < i; j++) {
                if (xs[i] == xs[j] && ys[i] == ys[j]) {
                    break;
                }
            }
            if (j < i) {
                tries++;
            } else {
                tries = 0;
                i++;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        arg0[i].unk2 = xs[i] + 15.0f;
        arg0[i].unk4 = ys[i] + 8.0f;
    }
}

/* The overlay's handler: the entry returns it to the loader. */

void func_ovl17_10_80043970(UnkStructA *arg0) {
    func_ovl17_10_80045BA0(arg0, 0x01000000);
}

void func_ovl17_10_80043754(void) {
    UnkStruct_ovl17_10_80046618 *rec;
    f32 a;
    f32 x;
    f32 z;

    rec = func_ovl17_10_80045D10();
    while (TRUE) {
        x = rec->unk0->unk40->unk10 = rec->unk4;
        z = rec->unk0->unk40->unk18 = rec->unk8;
        for (a = 15.0f; a < 140.0f; a += 0.1f) {
            rec->unk0->unk40->unk10 = func_ovl17_10_80045E90(a) * 2000.0f + x;
            rec->unk0->unk40->unk18 = func_ovl17_10_80045E98(a) * 2000.0f + z;
            rec->unk0->unk40->unk20 = a + 90.0f;
            func_ovl17_10_80045D30();
        }
        x = rec->unk0->unk40->unk10 = rec->unkA;
        z = rec->unk0->unk40->unk18 = rec->unkC;
        for (a = 145.0f; a < 280.0f; a += 0.1f) {
            rec->unk0->unk40->unk10 = func_ovl17_10_80045E90(a) * 2000.0f + x;
            rec->unk0->unk40->unk18 = func_ovl17_10_80045E98(a) * 2000.0f + z;
            rec->unk0->unk40->unk20 = a + 90.0f;
            func_ovl17_10_80045D30();
        }
    }
}

void func_ovl17_10_800434CC(void) {
    UnkStruct_ovl17_10_80046628 *rec;
    UnkStructA_40 *p;
    f32 speed;
    f32 a;
    f32 cx;
    f32 cz;

    rec = func_ovl17_10_80045D10();
    p = rec->unk0->unk40;
    func_ovl17_10_80045D08(func_ovl17_10_80045EA8(60) + 30);
    speed = 10.0f;
    while (TRUE) {
        p->unk10 = rec->unk4;
        p->unk18 = rec->unk8;
        p->unk20 = 135.0f;
        while (TRUE) {
            p->unk10 += speed;
            p->unk18 += speed;
            if (p->unk10 > 2200.0f) {
                a = 315.0f;
                break;
            }
            func_ovl17_10_80045D30();
        }
        cx = p->unk10 + 200.0f;
        cz = p->unk18 - 200.0f;
        while (TRUE) {
            if (a > 45.0f && a < 315.0f) {
                break;
            }
            p->unk10 = func_ovl17_10_80045E90(a) * 282.8f + cx;
            p->unk18 = func_ovl17_10_80045E98(a) * 282.8f + cz;
            p->unk20 = a + 180.0f;
            func_ovl17_10_80045D30();
            a = a + 5.0f >= 360.0f ? a + 5.0f - 360.0f : a + 5.0f < 0.0f ? a + 5.0f + 360.0f : a + 5.0f;
        }
        a = speed + 5.0f;
        while (TRUE) {
            p->unk10 += a;
            p->unk18 -= a;
            if (p->unk10 > 4000.0f) {
                break;
            }
            func_ovl17_10_80045D30();
        }
        func_ovl17_10_80045D08(func_ovl17_10_80045EA8(120) + 60);
    }
}

static void func_ovl17_10_800432F8(void) {
    func_ovl17_10_80045B98(func_ovl17_10_80045BE0(0x352, 0x50, 0.0f, 0.0f, 0.0f), 0x01080000);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl17_10_80043300(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl17_10_80046050(D_ovl17_10_800464A4);
            func_ovl17_10_80045198(0x218);
            func_ovl17_10_800432F8();
            func_ovl17_10_800451B0(0x222);
            func_ovl17_10_80045348();
            func_ovl17_10_80045310(0);
            func_ovl17_10_80045A40(0x7F);
            func_ovl17_10_800459B8(1);
            func_ovl17_10_800459C8(1);
            func_ovl17_10_800459D8(2305.0f, 60.0f, 1480.0f);
            func_ovl17_10_800459F8(0.0f, 60.0f, 2800.0f);
            func_ovl17_10_80045278(func_ovl17_10_8004455C, 2);
            func_ovl17_10_80045280(func_ovl17_10_80043970);
            break;
        case 3:
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
        case 4:
            D_ovl17_10_80046490 = 0.3f;
            D_ovl17_10_80046494 = 0.5f;
            D_ovl17_10_80046498 = 0;
            if (arg0 && arg0 && arg0) { /* fake: without it the next call is scheduled into these stores */
            }
            func_ovl17_10_80045278(func_ovl17_10_80044564, 1);
            func_ovl17_10_80043288();
            func_ovl17_10_80043158();
            break;
        case 5:
            func_ovl17_10_80043034();
            break;
        case 1:
            func_ovl17_10_80045FE8(0, 0, 0, 0.0f);
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

void func_ovl17_10_80043288(void) {
    s32 i;

    func_ovl17_10_800431C8();
    for (i = 0; i < 1; i++) {
        func_ovl17_10_80045CE8(func_ovl17_10_80043754, &D_ovl17_10_80046618[i], 0, 0, 0x110);
    }
}

void func_ovl17_10_800431C8(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 1; i++) {
        obj = func_ovl17_10_80045BE0(0x350, 0xD0, D_ovl17_10_80046618[i].unk4, D_ovl17_10_80046618[i].unk6,
                                     D_ovl17_10_80046618[i].unk8);
        obj->unk40->unk20 = 90.0f;
        func_ovl17_10_80045B98(obj, 0x0D000000);
        D_ovl17_10_80046618[i].unk0 = obj;
    }
}

void func_ovl17_10_80043158(void) {
    s32 i;

    func_ovl17_10_8004309C();
    for (i = 0; i < 5; i++) {
        func_ovl17_10_80045CE8(func_ovl17_10_800434CC, &D_ovl17_10_80046628[i], 0, 0, 0x110);
    }
}

void func_ovl17_10_8004309C(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 5; i++) {
        obj = func_ovl17_10_80045BE0(0x351, 0xD0, D_ovl17_10_80046628[i].unk4, D_ovl17_10_80046628[i].unk6,
                                     D_ovl17_10_80046628[i].unk8);
        obj->unk40->unk20 = 0.0f;
        func_ovl17_10_80045B98(obj, 0x01000000);
        D_ovl17_10_80046628[i].unk0 = obj;
    }
}

void func_ovl17_10_80043034(void) {
    UnkStructB *b;

    b = func_ovl17_10_80045318();
    if (b->unk38 == 1 && b->unk0 == 0) {
        func_ovl17_10_80043010();
        func_ovl17_10_80045CE8(func_ovl17_10_80043E14, NULL, 0, 0, 0x110);
    }
}

void func_ovl17_10_80043010(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_ovl17_10_80046748[i].unk0 = NULL;
    }
}

