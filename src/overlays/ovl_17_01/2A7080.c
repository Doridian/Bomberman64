#include "common.h"

/*
 * ovl_17_01's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

/* a model placed in the stage: two rows of three (D_ovl17_01_80045654,
 * D_ovl17_01_800456FC) */
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
} UnkStruct_ovl17_01_80045654; /* size 0x38 */

/* the argument of func_ovl17_01_8004398C's tasks */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} UnkStruct_ovl17_01_80045840; /* size 0x8 */

/* the argument of func_ovl17_01_80043CB4's tasks */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl17_01_80045858; /* size 0x10 */

void func_ovl17_01_80044338(s32);
void func_ovl17_01_80044350(s32);
f32 func_ovl17_01_80044360(void);
void func_ovl17_01_800444B0(s32);
UnkStructB *func_ovl17_01_800444B8(void);
void func_ovl17_01_800444E8(void);
void func_ovl17_01_80044A40(UnkStructA_40 *, s32);
void func_ovl17_01_80044A48(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl17_01_80044A80(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl17_01_80044B58(s32);
void func_ovl17_01_80044B68(s32);
void func_ovl17_01_80044B78(f32, f32, f32);
void func_ovl17_01_80044B98(f32, f32, f32);
void func_ovl17_01_80044BA0(f32 *, f32 *, f32 *);
void func_ovl17_01_80044BE0(s32);
void func_ovl17_01_80044C50(s32);
void func_ovl17_01_80044C60(f32, f32, f32);
void func_ovl17_01_80044D38(UnkStructA *, s32);
void func_ovl17_01_80044D40(UnkStructA *, s32);
void func_ovl17_01_80044D50(UnkStructA *);
UnkStructA *func_ovl17_01_80044D70(UnkStructA *);
UnkStructA *func_ovl17_01_80044D80(s32, s32, f32, f32, f32);
void func_ovl17_01_80044DB8(UnkStructA *);
void func_ovl17_01_80044E48(UnkStructA *);
s32 func_ovl17_01_80044E88(void (*)(void), void *, s32, s32, s32);
void func_ovl17_01_80044E98(void);
void func_ovl17_01_80044EA8(s32);
void *func_ovl17_01_80044EB0(void);
s32 func_ovl17_01_80044ED0(void);
f32 func_ovl17_01_80045030(f32);
s32 func_ovl17_01_80045048(s32);
void func_ovl17_01_80045188(s32, s32, s32, f32);
void func_ovl17_01_800451F0(u32 (*)[3]);
void func_ovl17_01_80045430(s32, f32, f32, f32);

void func_ovl17_01_80043010(void);
void func_ovl17_01_80043034(void);
void func_ovl17_01_800431D8(UnkStruct_ovl17_01_80045840 *, s16, s16);
void func_ovl17_01_80043570(void);
void func_ovl17_01_8004365C(void);
void func_ovl17_01_800438A8(f32, f32, f32, f32);
void func_ovl17_01_8004398C(void);
void func_ovl17_01_80043CB4(void);

/* .bss */
u8 D_ovl17_01_80045800[0x24];
s32 D_ovl17_01_80045824;
s32 D_ovl17_01_80045828;
u8 D_ovl17_01_8004582C[0x4];
Vec3f D_ovl17_01_80045830;
u8 D_ovl17_01_8004583C[0x4];
UnkStruct_ovl17_01_80045840 D_ovl17_01_80045840[3];
UnkStruct_ovl17_01_80045858 D_ovl17_01_80045858[3];

/* .data */
/* passed to func_ovl17_01_800451F0: three 12-byte records */
u32 D_ovl17_01_80045630[][3] = {
    { 0xD30000, 0x10000C, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
UnkStruct_ovl17_01_80045654 D_ovl17_01_80045654[3] = {
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl17_01_80045654 D_ovl17_01_800456FC[3] = {
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl17_01_80043FE8(void) {
    D_ovl17_01_80045800[0] = D_ovl17_01_8004582C[0] + D_ovl17_01_8004583C[0];
}

static void func_ovl17_01_80043FE0(void) {
}

static void func_ovl17_01_80043FD8(void) {
}

static void func_ovl17_01_80043FD0(void) {
}

static void func_ovl17_01_80043FC8(void) {
}

static void func_ovl17_01_80043FC0(void) {
}

static void func_ovl17_01_80043FB8(void) {
}

static void func_ovl17_01_80043FB0(void) {
}

static void func_ovl17_01_80043FA8(void) {
}

static void func_ovl17_01_80043FA0(void) {
}

static void func_ovl17_01_80043F94(void) {
}

void func_ovl17_01_80043F7C(void) {
    D_ovl17_01_80045824 = -1;
    D_ovl17_01_80045828 = -1;
}

void func_ovl17_01_80043F20(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl17_01_80044B78(D_ovl17_01_80045830.x, D_ovl17_01_80045830.y, D_ovl17_01_80045830.z);
    func_ovl17_01_80044B98(arg0, arg1, arg2);
    func_ovl17_01_80044EA8(180);
}

void func_ovl17_01_80043ED8(f32 arg0) {
    f32 sp1C;

    func_ovl17_01_80044BA0(&sp1C, NULL, NULL);
    func_ovl17_01_80044B98(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl17_01_80043EA4(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl17_01_80045430(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl17_01_80043CB4(void) {
    UnkStructA *obj;
    s32 i;
    s16 alpha;
    f32 scale;
    s32 step;
    UnkStruct_ovl17_01_80045858 *arg;

    arg = func_ovl17_01_80044EB0();
    obj = func_ovl17_01_80044D80(0x11A, 0x20, arg->unk4, arg->unk6, arg->unk8);
    func_ovl17_01_80044D38(obj, 0x0D080040);
    arg->unk0 = obj;
    obj->unk40->unkC |= 0x8000;
    obj->unk30 = 1;
    obj->unk34 = 90.0f;
    obj->unk38 = 0.0f;
    func_ovl17_01_80044A40(obj->unk40, 2);
    func_ovl17_01_80044A48(obj->unk40, 0x11B, 0, 0);
    func_ovl17_01_80044A48(obj->unk40, 0x11B, 1, 1);
    obj->unk40->unk28 = 0.5f;
    obj->unk40->unk2C = 0.5f;
    obj->unk40->unk30 = 0.5f;
    obj->unk40->unk36 = 0xFF;
    alpha = 0xFF;
    step = 4;
    for (i = 0; i < 90; i += step) {
        scale = (D_ovl17_01_80045858[0].unkC - 0.5f) * func_ovl17_01_80045030(i) + 0.5f;
        obj->unk40->unk30 = scale;
        obj->unk40->unk2C = scale;
        obj->unk40->unk28 = scale;
        obj->unk40->unk36 = alpha;
        alpha -= 5;
        func_ovl17_01_80044E48(obj);
        func_ovl17_01_80044ED0();
    }
    obj->unk40->unk28 = D_ovl17_01_80045858[0].unkC;
    obj->unk40->unk2C = D_ovl17_01_80045858[0].unkC;
    obj->unk40->unk30 = D_ovl17_01_80045858[0].unkC;
    func_ovl17_01_80044D50(obj);
    arg->unk0 = NULL;
    func_ovl17_01_80044E98();
}

void func_ovl17_01_8004398C(void) {
    UnkStruct_ovl17_01_80045840 *arg;
    UnkStruct_ovl17_01_80045654 *a;
    UnkStruct_ovl17_01_80045654 *b;
    f32 scale;

    func_ovl17_01_80044ED0();
    arg = func_ovl17_01_80044EB0();
    a = &D_ovl17_01_80045654[arg->unk0];
    b = &D_ovl17_01_800456FC[arg->unk0];
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
    func_ovl17_01_80044D38(a->unk0, 0x01000000);
    func_ovl17_01_80044D38(b->unk0, 0x01000000);
    while (TRUE) {
        func_ovl17_01_80044DB8(a->unk0);
        b->unk0->unk40->unk14 = a->unk0->unk40->unk14;
        if (a->unk0->unk40->unk14 <= func_ovl17_01_80044360() ||
            (a->unk0->unk6C == 0.0f && a->unk0->unk68 == 0.0f)) {
            func_ovl17_01_80044D40(a->unk0, 0x01000000);
            func_ovl17_01_80044D40(b->unk0, 0x01000000);
            func_ovl17_01_80045430(0x7C, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
            scale = (1.0f - func_ovl17_01_800444B8()->unk30 / 60.0f) * 1.5f + 2.0f;
            func_ovl17_01_800438A8(a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18, scale);
            arg->unk6 |= 1;
            func_ovl17_01_80044E98();
        }
        func_ovl17_01_80044ED0();
    }
}

void func_ovl17_01_800438A8(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStruct_ovl17_01_80045858 *p;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_ovl17_01_80045858[i].unk0 == NULL) {
            break;
        }
    }
    p = &D_ovl17_01_80045858[i];
    if (p < &D_ovl17_01_80045858[3]) {
        p->unk4 = arg0;
        p->unk6 = arg1;
        p->unk8 = arg2;
        p->unkC = arg3;
        func_ovl17_01_80044E88(func_ovl17_01_80043CB4, p, 0, 0, 0x110);
    }
}

void func_ovl17_01_80043874(void) {
    func_ovl17_01_80044C60(20.0f, 20.0f, 20.0f);
    func_ovl17_01_80044C50(120);
}

void func_ovl17_01_8004365C(void) {
    UnkStructB *b;
    s16 i;
    s16 j;
    s16 n;

    n = 5;
    b = func_ovl17_01_800444B8();
    while (TRUE) {
        if (b->unk2C <= 0) {
            break;
        }
        func_ovl17_01_80044ED0();
    }
    func_ovl17_01_80043570();
    for (i = 0; i < 3; i++) {
        D_ovl17_01_80045840[i].unk0 = i;
    }
    while (TRUE) {
        for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
            D_ovl17_01_80045840[j].unk6 = 0;
        }
        func_ovl17_01_800431D8(D_ovl17_01_80045840, 16, 14);
        func_ovl17_01_80044E88(func_ovl17_01_8004398C, &D_ovl17_01_80045840[0], 0, 0, 0x110);
        func_ovl17_01_80044EA8(func_ovl17_01_80045048(10) + 5);
        func_ovl17_01_80044E88(func_ovl17_01_8004398C, &D_ovl17_01_80045840[1], 0, 0, 0x110);
        func_ovl17_01_80044EA8(func_ovl17_01_80045048(10) + 5);
        func_ovl17_01_80044E88(func_ovl17_01_8004398C, &D_ovl17_01_80045840[2], 0, 0, 0x110);
        func_ovl17_01_80044ED0();
            while (TRUE) {
                if ((D_ovl17_01_80045840[0].unk6 & 1) && (D_ovl17_01_80045840[1].unk6 & 1) &&
                    (D_ovl17_01_80045840[2].unk6 & 1)) {
                    break;
                }
                func_ovl17_01_80044ED0();
            }
        func_ovl17_01_80044ED0();
        }
        func_ovl17_01_80044EA8(func_ovl17_01_80045048(60) + 30);
    }
}

static void func_ovl17_01_800433F0(UnkStruct_ovl17_01_80045654 *e) {
    e->unk0 = func_ovl17_01_80044D80(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl17_01_80044D38(e->unk0, 0x01080000);
    func_ovl17_01_80044D40(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl17_01_80044A80(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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

void func_ovl17_01_80043570(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 3; i++) {
        func_ovl17_01_800433F0(&D_ovl17_01_80045654[i]);
        obj = func_ovl17_01_80044D70(D_ovl17_01_80045654[i].unk0);
        obj->unk54 = 2.0f;
        obj->unk4C = 2.0f;
        obj->unk40->unk36 = 0xCC;
        func_ovl17_01_80044D40(D_ovl17_01_80045654[i].unk0, 0x80000);
        func_ovl17_01_80044D40(D_ovl17_01_80045654[i].unk0, 0x01000000);
        func_ovl17_01_800433F0(&D_ovl17_01_800456FC[i]);
        func_ovl17_01_80044D40(D_ovl17_01_800456FC[i].unk0, 0x01000000);
    }
}

void func_ovl17_01_800431D8(UnkStruct_ovl17_01_80045840 *arg0, s16 arg1, s16 arg2) {
    s32 pad; /* unused: the original's frame is 4 bytes bigger */
    s16 xs[3];
    s16 ys[3];
    s16 i;
    s16 j;
    s16 tries;

    for (i = 0, tries = 0; i < 3;) {
        xs[i] = func_ovl17_01_80045048(arg1);
        ys[i] = func_ovl17_01_80045048(arg2);
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
void func_ovl17_01_8004309C(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl17_01_800451F0(D_ovl17_01_80045630);
            func_ovl17_01_80044338(0x201);
            func_ovl17_01_80044350(0x219);
            func_ovl17_01_800444E8();
            func_ovl17_01_800444B0(0);
            func_ovl17_01_80044BE0(0x7F);
            func_ovl17_01_80044B58(1);
            func_ovl17_01_80044B68(1);
            func_ovl17_01_80044B78(2300.0f, 0.0f, 1420.0f);
            func_ovl17_01_80044B98(0.0f, 55.0f, 2930.0f);
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
            func_ovl17_01_80043034();
            break;
        case 1:
            func_ovl17_01_80045188(0, 0, 0, 0.0f);
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

void func_ovl17_01_80043034(void) {
    UnkStructB *b;

    b = func_ovl17_01_800444B8();
    if (b->unk38 == 1 && b->unk0 == 0) {
        func_ovl17_01_80043010();
        func_ovl17_01_80044E88(func_ovl17_01_8004365C, NULL, 0, 0, 0x110);
    }
}

void func_ovl17_01_80043010(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_ovl17_01_80045858[i].unk0 = NULL;
    }
}
