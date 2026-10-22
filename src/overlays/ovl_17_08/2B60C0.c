#include "common.h"

/*
 * ovl_17_08's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

/* a model placed in the stage: two rows of three (D_ovl17_08_80045A94,
 * D_ovl17_08_80045B3C) */
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
} UnkStruct_ovl17_08_80045A94; /* size 0x38 */

/* the argument of func_ovl17_08_80043DCC's tasks */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} UnkStruct_ovl17_08_80045CA0; /* size 0x8 */

/* the argument of func_ovl17_08_800440F4's tasks */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl17_08_80045CB8; /* size 0x10 */

void func_ovl17_08_80044778(s32);
void func_ovl17_08_80044790(s32);
f32 func_ovl17_08_800447A0(void);
void func_ovl17_08_800448F0(s32);
UnkStructB *func_ovl17_08_800448F8(void);
void func_ovl17_08_80044928(void);
void func_ovl17_08_80044E80(UnkStructA_40 *, s32);
void func_ovl17_08_80044E88(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl17_08_80044EC0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl17_08_80044F98(s32);
void func_ovl17_08_80044FA8(s32);
void func_ovl17_08_80044FB8(f32, f32, f32);
void func_ovl17_08_80044FD8(f32, f32, f32);
void func_ovl17_08_80044FE0(f32 *, f32 *, f32 *);
void func_ovl17_08_80045020(s32);
void func_ovl17_08_80045090(s32);
void func_ovl17_08_800450A0(f32, f32, f32);
void func_ovl17_08_80045178(UnkStructA *, s32);
void func_ovl17_08_80045180(UnkStructA *, s32);
void func_ovl17_08_80045190(UnkStructA *);
UnkStructA *func_ovl17_08_800451B0(UnkStructA *);
UnkStructA *func_ovl17_08_800451C0(s32, s32, f32, f32, f32);
void func_ovl17_08_800451F8(UnkStructA *);
void func_ovl17_08_80045288(UnkStructA *);
s32 func_ovl17_08_800452C8(void (*)(void), void *, s32, s32, s32);
void func_ovl17_08_800452D8(void);
void func_ovl17_08_800452E8(s32);
void *func_ovl17_08_800452F0(void);
s32 func_ovl17_08_80045310(void);
f32 func_ovl17_08_80045470(f32);
s32 func_ovl17_08_80045488(s32);
void func_ovl17_08_800455C8(s32, s32, s32, f32);
void func_ovl17_08_80045618(s32, s32, s32);
void func_ovl17_08_80045630(u32 (*)[3]);
void func_ovl17_08_80045870(s32, f32, f32, f32);

void func_ovl17_08_80043010(void);
void func_ovl17_08_80043034(void);
void func_ovl17_08_8004309C(void);
void func_ovl17_08_800432D4(void);
void func_ovl17_08_80043630(UnkStruct_ovl17_08_80045CA0 *, s16, s16);
void func_ovl17_08_800439C8(void);
void func_ovl17_08_80043AB4(void);
void func_ovl17_08_80043CE8(f32, f32, f32, f32);
void func_ovl17_08_80043DCC(void);
void func_ovl17_08_800440F4(void);

/* .bss */
u8 D_ovl17_08_80045C60[0x24];
s32 D_ovl17_08_80045C84;
s32 D_ovl17_08_80045C88;
u8 D_ovl17_08_80045C8C[0x4];
Vec3f D_ovl17_08_80045C90;
u8 D_ovl17_08_80045C9C[0x4];
UnkStruct_ovl17_08_80045CA0 D_ovl17_08_80045CA0[3];
UnkStruct_ovl17_08_80045CB8 D_ovl17_08_80045CB8[3];
f32 D_ovl17_08_80045CE8;
f32 D_ovl17_08_80045CEC;
f32 D_ovl17_08_80045CF0;
f32 D_ovl17_08_80045CF4;
f32 D_ovl17_08_80045CF8;
f32 D_ovl17_08_80045CFC;
f32 D_ovl17_08_80045D00;
f32 D_ovl17_08_80045D04;
f32 D_ovl17_08_80045D08;
s32 D_ovl17_08_80045D0C;

/* .data */
/* passed to func_ovl17_08_80045630: three 12-byte records */
u32 D_ovl17_08_80045A70[][3] = {
    { 0xD90000, 0x10000C, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
UnkStruct_ovl17_08_80045A94 D_ovl17_08_80045A94[3] = {
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl17_08_80045A94 D_ovl17_08_80045B3C[3] = {
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl17_08_80044428(void) {
    D_ovl17_08_80045C60[0] = D_ovl17_08_80045C8C[0] + D_ovl17_08_80045C9C[0];
}

static void func_ovl17_08_80044420(void) {
}

static void func_ovl17_08_80044418(void) {
}

static void func_ovl17_08_80044410(void) {
}

static void func_ovl17_08_80044408(void) {
}

static void func_ovl17_08_80044400(void) {
}

static void func_ovl17_08_800443F8(void) {
}

static void func_ovl17_08_800443F0(void) {
}

static void func_ovl17_08_800443E8(void) {
}

static void func_ovl17_08_800443E0(void) {
}

static void func_ovl17_08_800443D4(void) {
}

void func_ovl17_08_800443BC(void) {
    D_ovl17_08_80045C84 = -1;
    D_ovl17_08_80045C88 = -1;
}

void func_ovl17_08_80044360(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl17_08_80044FB8(D_ovl17_08_80045C90.x, D_ovl17_08_80045C90.y, D_ovl17_08_80045C90.z);
    func_ovl17_08_80044FD8(arg0, arg1, arg2);
    func_ovl17_08_800452E8(180);
}

void func_ovl17_08_80044318(f32 arg0) {
    f32 sp1C;

    func_ovl17_08_80044FE0(&sp1C, NULL, NULL);
    func_ovl17_08_80044FD8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl17_08_800442E4(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl17_08_80045870(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl17_08_800440F4(void) {
    UnkStructA *obj;
    s32 i;
    s16 alpha;
    f32 scale;
    s32 step;
    UnkStruct_ovl17_08_80045CB8 *arg;

    arg = func_ovl17_08_800452F0();
    obj = func_ovl17_08_800451C0(0x11A, 0x20, arg->unk4, arg->unk6, arg->unk8);
    func_ovl17_08_80045178(obj, 0x0D080040);
    arg->unk0 = obj;
    obj->unk40->unkC |= 0x8000;
    obj->unk30 = 1;
    obj->unk34 = 90.0f;
    obj->unk38 = 0.0f;
    func_ovl17_08_80044E80(obj->unk40, 2);
    func_ovl17_08_80044E88(obj->unk40, 0x11B, 0, 0);
    func_ovl17_08_80044E88(obj->unk40, 0x11B, 1, 1);
    obj->unk40->unk28 = 0.5f;
    obj->unk40->unk2C = 0.5f;
    obj->unk40->unk30 = 0.5f;
    obj->unk40->unk36 = 0xFF;
    alpha = 0xFF;
    step = 4;
    for (i = 0; i < 90; i += step) {
        scale = (D_ovl17_08_80045CB8[0].unkC - 0.5f) * func_ovl17_08_80045470(i) + 0.5f;
        obj->unk40->unk30 = scale;
        obj->unk40->unk2C = scale;
        obj->unk40->unk28 = scale;
        obj->unk40->unk36 = alpha;
        alpha -= 5;
        func_ovl17_08_80045288(obj);
        func_ovl17_08_80045310();
    }
    obj->unk40->unk28 = D_ovl17_08_80045CB8[0].unkC;
    obj->unk40->unk2C = D_ovl17_08_80045CB8[0].unkC;
    obj->unk40->unk30 = D_ovl17_08_80045CB8[0].unkC;
    func_ovl17_08_80045190(obj);
    arg->unk0 = NULL;
    func_ovl17_08_800452D8();
}

void func_ovl17_08_80043DCC(void) {
    UnkStruct_ovl17_08_80045CA0 *arg;
    UnkStruct_ovl17_08_80045A94 *a;
    UnkStruct_ovl17_08_80045A94 *b;
    f32 scale;

    func_ovl17_08_80045310();
    arg = func_ovl17_08_800452F0();
    a = &D_ovl17_08_80045A94[arg->unk0];
    b = &D_ovl17_08_80045B3C[arg->unk0];
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
    func_ovl17_08_80045178(a->unk0, 0x01000000);
    func_ovl17_08_80045178(b->unk0, 0x01000000);
    while (TRUE) {
        func_ovl17_08_800451F8(a->unk0);
        b->unk0->unk40->unk14 = a->unk0->unk40->unk14;
        if (a->unk0->unk40->unk14 <= func_ovl17_08_800447A0() ||
            (a->unk0->unk6C == 0.0f && a->unk0->unk68 == 0.0f)) {
            func_ovl17_08_80045180(a->unk0, 0x01000000);
            func_ovl17_08_80045180(b->unk0, 0x01000000);
            func_ovl17_08_80045870(0x7C, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
            scale = (1.0f - func_ovl17_08_800448F8()->unk30 / 60.0f) * 1.5f + 2.0f;
            func_ovl17_08_80043CE8(a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18, scale);
            arg->unk6 |= 1;
            func_ovl17_08_800452D8();
        }
        func_ovl17_08_80045310();
    }
}

void func_ovl17_08_80043CE8(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStruct_ovl17_08_80045CB8 *p;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_ovl17_08_80045CB8[i].unk0 == NULL) {
            break;
        }
    }
    p = &D_ovl17_08_80045CB8[i];
    if (p < &D_ovl17_08_80045CB8[3]) {
        p->unk4 = arg0;
        p->unk6 = arg1;
        p->unk8 = arg2;
        p->unkC = arg3;
        func_ovl17_08_800452C8(func_ovl17_08_800440F4, p, 0, 0, 0x110);
    }
}

void func_ovl17_08_80043CB4(void) {
    func_ovl17_08_800450A0(20.0f, 20.0f, 20.0f);
    func_ovl17_08_80045090(120);
}

void func_ovl17_08_80043AB4(void) {
    UnkStructB *b;
    s16 i;
    s16 j;
    s16 n;

    n = 5;
    b = func_ovl17_08_800448F8();
    while (TRUE) {
        if (b->unk2C <= 0) {
            break;
        }
        func_ovl17_08_80045310();
    }
    func_ovl17_08_800439C8();
    for (i = 0; i < 3; i++) {
        D_ovl17_08_80045CA0[i].unk0 = i;
    }
    while (TRUE) {
        for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
            D_ovl17_08_80045CA0[j].unk6 = 0;
        }
        func_ovl17_08_80043630(D_ovl17_08_80045CA0, 14, 14);
        func_ovl17_08_800452C8(func_ovl17_08_80043DCC, &D_ovl17_08_80045CA0[0], 0, 0, 0x110);
        func_ovl17_08_800452E8(func_ovl17_08_80045488(10) + 5);
        func_ovl17_08_800452C8(func_ovl17_08_80043DCC, &D_ovl17_08_80045CA0[1], 0, 0, 0x110);
        func_ovl17_08_800452E8(func_ovl17_08_80045488(10) + 5);
        func_ovl17_08_800452C8(func_ovl17_08_80043DCC, &D_ovl17_08_80045CA0[2], 0, 0, 0x110);
        func_ovl17_08_80045310();
            while (TRUE) {
                if ((D_ovl17_08_80045CA0[0].unk6 & 1) && (D_ovl17_08_80045CA0[1].unk6 & 1) &&
                    (D_ovl17_08_80045CA0[2].unk6 & 1)) {
                    break;
                }
                func_ovl17_08_80045310();
            }
        func_ovl17_08_80045310();
        }
        func_ovl17_08_800452E8(func_ovl17_08_80045488(60) + 30);
    }
}

static void func_ovl17_08_80043848(UnkStruct_ovl17_08_80045A94 *e) {
    e->unk0 = func_ovl17_08_800451C0(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl17_08_80045178(e->unk0, 0x01080000);
    func_ovl17_08_80045180(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl17_08_80044EC0(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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

void func_ovl17_08_800439C8(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 3; i++) {
        func_ovl17_08_80043848(&D_ovl17_08_80045A94[i]);
        obj = func_ovl17_08_800451B0(D_ovl17_08_80045A94[i].unk0);
        obj->unk54 = 2.0f;
        obj->unk4C = 2.0f;
        obj->unk40->unk36 = 0xCC;
        func_ovl17_08_80045180(D_ovl17_08_80045A94[i].unk0, 0x80000);
        func_ovl17_08_80045180(D_ovl17_08_80045A94[i].unk0, 0x01000000);
        func_ovl17_08_80043848(&D_ovl17_08_80045B3C[i]);
        func_ovl17_08_80045180(D_ovl17_08_80045B3C[i].unk0, 0x01000000);
    }
}

void func_ovl17_08_80043630(UnkStruct_ovl17_08_80045CA0 *arg0, s16 arg1, s16 arg2) {
    s32 pad; /* unused: the original's frame is 4 bytes bigger */
    s16 xs[3];
    s16 ys[3];
    s16 i;
    s16 j;
    s16 tries;

    for (i = 0, tries = 0; i < 3;) {
        xs[i] = func_ovl17_08_80045488(arg1);
        ys[i] = func_ovl17_08_80045488(arg2);
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
        arg0[i].unk2 = xs[i] + 16.0f;
        arg0[i].unk4 = ys[i] + 8.0f;
    }
}

void func_ovl17_08_800432D4(void) {
    while (TRUE) {
        if (D_ovl17_08_80045D0C != 0) {
            D_ovl17_08_80045CE8 += D_ovl17_08_80045CEC;
            if (D_ovl17_08_80045CE8 >= 89.9f && D_ovl17_08_80045CEC > 0.0f) {
                D_ovl17_08_80045CE8 = 89.9f;
            }
            if (D_ovl17_08_80045CE8 <= 15.0f && D_ovl17_08_80045CEC < 0.0f) {
                D_ovl17_08_80045CE8 = 15.0f;
            }
            D_ovl17_08_80045CEC += D_ovl17_08_80045CF0;
            if (D_ovl17_08_80045CEC >= 0.15f && D_ovl17_08_80045CF0 > 0.0f) {
                D_ovl17_08_80045CF0 = -D_ovl17_08_80045CF0;
            }
            if (D_ovl17_08_80045CEC <= -0.15f && D_ovl17_08_80045CF0 < 0.0f) {
                D_ovl17_08_80045CF0 = -D_ovl17_08_80045CF0;
            }
            D_ovl17_08_80045CF4 += D_ovl17_08_80045CF8;
            D_ovl17_08_80045CF8 += D_ovl17_08_80045CFC;
            if (D_ovl17_08_80045CF8 >= 1.0f && D_ovl17_08_80045CFC > 0.0f) {
                D_ovl17_08_80045CFC = -D_ovl17_08_80045CFC;
            }
            if (D_ovl17_08_80045CF8 <= -1.0f && D_ovl17_08_80045CFC < 0.0f) {
                D_ovl17_08_80045CFC = -D_ovl17_08_80045CFC;
            }
            D_ovl17_08_80045D00 += D_ovl17_08_80045D04;
            D_ovl17_08_80045D04 += D_ovl17_08_80045D08;
            if (D_ovl17_08_80045D04 >= 1.0f && D_ovl17_08_80045D08 > 0.0f) {
                D_ovl17_08_80045D08 = -D_ovl17_08_80045D08;
            }
            if (D_ovl17_08_80045D04 <= -1.0f && D_ovl17_08_80045D08 < 0.0f) {
                D_ovl17_08_80045D08 = -D_ovl17_08_80045D08;
            }
            func_ovl17_08_80044FD8(32768.0f, D_ovl17_08_80045CE8, 32768.0f);
            func_ovl17_08_80044FB8(D_ovl17_08_80045CF4, D_ovl17_08_80045D00, 32768.0f);
        }
        func_ovl17_08_800452E8(2);
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl17_08_80043154(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl17_08_80045630(D_ovl17_08_80045A70);
            func_ovl17_08_80044778(0x216);
            func_ovl17_08_80044790(0x220);
            func_ovl17_08_80044928();
            func_ovl17_08_800448F0(0);
            func_ovl17_08_80045020(0x7F);
            func_ovl17_08_80044F98(1);
            func_ovl17_08_80044FA8(1);
            func_ovl17_08_80044FB8(2300.0f, -25.0f, 1400.0f);
            func_ovl17_08_80044FD8(0.0f, 55.0f, 2894.0f);
            func_ovl17_08_80045618(200, 200, 255);
            D_ovl17_08_80045D0C = 0;
            func_ovl17_08_8004309C();
            break;
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
            func_ovl17_08_80043034();
            break;
        case 1:
            func_ovl17_08_800455C8(0, 0, 0, 0.0f);
            break;
        case 3:
            if (D_ovl17_08_80045D0C == 0) {
                D_ovl17_08_80045D0C++;
            }
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

void func_ovl17_08_8004309C(void) {
    D_ovl17_08_80045CE8 = 55.0f;
    D_ovl17_08_80045CEC = 0.15f;
    D_ovl17_08_80045CF0 = -0.001f;
    D_ovl17_08_80045CF4 = 2300.0f;
    D_ovl17_08_80045CF8 = 1.0f;
    D_ovl17_08_80045CFC = -0.01f;
    D_ovl17_08_80045D00 = -25.0f;
    D_ovl17_08_80045D04 = 1.0f;
    D_ovl17_08_80045D08 = -0.01f;
    func_ovl17_08_800452C8(func_ovl17_08_800432D4, NULL, 0, 0, 0x130);
}

void func_ovl17_08_80043034(void) {
    UnkStructB *b;

    b = func_ovl17_08_800448F8();
    if (b->unk38 == 1 && b->unk0 == 0) {
        func_ovl17_08_80043010();
        func_ovl17_08_800452C8(func_ovl17_08_80043AB4, NULL, 0, 0, 0x110);
    }
}

void func_ovl17_08_80043010(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_ovl17_08_80045CB8[i].unk0 = NULL;
    }
}
