#include "common.h"

/*
 * ovl_17_06's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

/* a model placed in the stage: two rows of three (D_ovl17_06_80045694,
 * D_ovl17_06_8004573C) */
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
} UnkStruct_ovl17_06_80045694; /* size 0x38 */

/* the argument of func_ovl17_06_800439CC's tasks */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} UnkStruct_ovl17_06_80045880; /* size 0x8 */

/* the argument of func_ovl17_06_80043CF4's tasks */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl17_06_80045898; /* size 0x10 */

void func_ovl17_06_80044378(s32);
void func_ovl17_06_80044390(s32);
f32 func_ovl17_06_800443A0(void);
void func_ovl17_06_800444F0(s32);
UnkStructB *func_ovl17_06_800444F8(void);
void func_ovl17_06_80044528(void);
void func_ovl17_06_80044A80(UnkStructA_40 *, s32);
void func_ovl17_06_80044A88(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl17_06_80044AC0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl17_06_80044B98(s32);
void func_ovl17_06_80044BA8(s32);
void func_ovl17_06_80044BB8(f32, f32, f32);
void func_ovl17_06_80044BD8(f32, f32, f32);
void func_ovl17_06_80044BE0(f32 *, f32 *, f32 *);
void func_ovl17_06_80044C20(s32);
void func_ovl17_06_80044C90(s32);
void func_ovl17_06_80044CA0(f32, f32, f32);
void func_ovl17_06_80044D78(UnkStructA *, s32);
void func_ovl17_06_80044D80(UnkStructA *, s32);
void func_ovl17_06_80044D90(UnkStructA *);
UnkStructA *func_ovl17_06_80044DB0(UnkStructA *);
UnkStructA *func_ovl17_06_80044DC0(s32, s32, f32, f32, f32);
void func_ovl17_06_80044DF8(UnkStructA *);
void func_ovl17_06_80044E88(UnkStructA *);
s32 func_ovl17_06_80044EC8(void (*)(void), void *, s32, s32, s32);
void func_ovl17_06_80044ED8(void);
void func_ovl17_06_80044EE8(s32);
void *func_ovl17_06_80044EF0(void);
s32 func_ovl17_06_80044F10(void);
f32 func_ovl17_06_80045070(f32);
s32 func_ovl17_06_80045088(s32);
void func_ovl17_06_800451C8(s32, s32, s32, f32);
void *func_ovl17_06_80044F50(s32);
void func_ovl17_06_80044F60(void *, s32);
void func_ovl17_06_80045230(u32 (*)[3]);
void func_ovl17_06_80045470(s32, f32, f32, f32);

void func_ovl17_06_80043010(void);
void func_ovl17_06_80043034(void);
void func_ovl17_06_8004309C(s32);
void func_ovl17_06_80043234(UnkStruct_ovl17_06_80045880 *, s16, s16);
void func_ovl17_06_800435CC(void);
void func_ovl17_06_800436B8(void);
void func_ovl17_06_800438E8(f32, f32, f32, f32);
void func_ovl17_06_800439CC(void);
void func_ovl17_06_80043CF4(void);

/* .bss */
u8 D_ovl17_06_80045840[0x24];
s32 D_ovl17_06_80045864;
s32 D_ovl17_06_80045868;
u8 D_ovl17_06_8004586C[0x4];
Vec3f D_ovl17_06_80045870;
void *D_ovl17_06_8004587C;
UnkStruct_ovl17_06_80045880 D_ovl17_06_80045880[3];
UnkStruct_ovl17_06_80045898 D_ovl17_06_80045898[3];

/* .data */
/* passed to func_ovl17_06_80045230: three 12-byte records */
u32 D_ovl17_06_80045670[][3] = {
    { 0xD70000, 0x8000C, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
UnkStruct_ovl17_06_80045694 D_ovl17_06_80045694[3] = {
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B6, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl17_06_80045694 D_ovl17_06_8004573C[3] = {
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B7, -1, -1, -1, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl17_06_80044028(void) {
    D_ovl17_06_80045840[0] = D_ovl17_06_8004586C[0];
}

static void func_ovl17_06_80044020(void) {
}

static void func_ovl17_06_80044018(void) {
}

static void func_ovl17_06_80044010(void) {
}

static void func_ovl17_06_80044008(void) {
}

static void func_ovl17_06_80044000(void) {
}

static void func_ovl17_06_80043FF8(void) {
}

static void func_ovl17_06_80043FF0(void) {
}

static void func_ovl17_06_80043FE8(void) {
}

static void func_ovl17_06_80043FE0(void) {
}

static void func_ovl17_06_80043FD4(void) {
}

void func_ovl17_06_80043FBC(void) {
    D_ovl17_06_80045864 = -1;
    D_ovl17_06_80045868 = -1;
}

void func_ovl17_06_80043F60(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl17_06_80044BB8(D_ovl17_06_80045870.x, D_ovl17_06_80045870.y, D_ovl17_06_80045870.z);
    func_ovl17_06_80044BD8(arg0, arg1, arg2);
    func_ovl17_06_80044EE8(180);
}

void func_ovl17_06_80043F18(f32 arg0) {
    f32 sp1C;

    func_ovl17_06_80044BE0(&sp1C, NULL, NULL);
    func_ovl17_06_80044BD8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl17_06_80043EE4(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl17_06_80045470(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl17_06_80043CF4(void) {
    UnkStructA *obj;
    s32 i;
    s16 alpha;
    f32 scale;
    s32 step;
    UnkStruct_ovl17_06_80045898 *arg;

    arg = func_ovl17_06_80044EF0();
    obj = func_ovl17_06_80044DC0(0x11A, 0x20, arg->unk4, arg->unk6, arg->unk8);
    func_ovl17_06_80044D78(obj, 0x0D080040);
    arg->unk0 = obj;
    obj->unk40->unkC |= 0x8000;
    obj->unk30 = 1;
    obj->unk34 = 90.0f;
    obj->unk38 = 0.0f;
    func_ovl17_06_80044A80(obj->unk40, 2);
    func_ovl17_06_80044A88(obj->unk40, 0x11B, 0, 0);
    func_ovl17_06_80044A88(obj->unk40, 0x11B, 1, 1);
    obj->unk40->unk28 = 0.5f;
    obj->unk40->unk2C = 0.5f;
    obj->unk40->unk30 = 0.5f;
    obj->unk40->unk36 = 0xFF;
    alpha = 0xFF;
    step = 4;
    for (i = 0; i < 90; i += step) {
        scale = (D_ovl17_06_80045898[0].unkC - 0.5f) * func_ovl17_06_80045070(i) + 0.5f;
        obj->unk40->unk30 = scale;
        obj->unk40->unk2C = scale;
        obj->unk40->unk28 = scale;
        obj->unk40->unk36 = alpha;
        alpha -= 5;
        func_ovl17_06_80044E88(obj);
        func_ovl17_06_80044F10();
    }
    obj->unk40->unk28 = D_ovl17_06_80045898[0].unkC;
    obj->unk40->unk2C = D_ovl17_06_80045898[0].unkC;
    obj->unk40->unk30 = D_ovl17_06_80045898[0].unkC;
    func_ovl17_06_80044D90(obj);
    arg->unk0 = NULL;
    func_ovl17_06_80044ED8();
}

void func_ovl17_06_800439CC(void) {
    UnkStruct_ovl17_06_80045880 *arg;
    UnkStruct_ovl17_06_80045694 *a;
    UnkStruct_ovl17_06_80045694 *b;
    f32 scale;

    func_ovl17_06_80044F10();
    arg = func_ovl17_06_80044EF0();
    a = &D_ovl17_06_80045694[arg->unk0];
    b = &D_ovl17_06_8004573C[arg->unk0];
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
    func_ovl17_06_80044D78(a->unk0, 0x01000000);
    func_ovl17_06_80044D78(b->unk0, 0x01000000);
    while (TRUE) {
        func_ovl17_06_80044DF8(a->unk0);
        b->unk0->unk40->unk14 = a->unk0->unk40->unk14;
        if (a->unk0->unk40->unk14 <= func_ovl17_06_800443A0() ||
            (a->unk0->unk6C == 0.0f && a->unk0->unk68 == 0.0f)) {
            func_ovl17_06_80044D80(a->unk0, 0x01000000);
            func_ovl17_06_80044D80(b->unk0, 0x01000000);
            func_ovl17_06_80045470(0x7C, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
            scale = (1.0f - func_ovl17_06_800444F8()->unk30 / 60.0f) * 1.5f + 2.0f;
            func_ovl17_06_800438E8(a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18, scale);
            arg->unk6 |= 1;
            func_ovl17_06_80044ED8();
        }
        func_ovl17_06_80044F10();
    }
}

void func_ovl17_06_800438E8(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStruct_ovl17_06_80045898 *p;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_ovl17_06_80045898[i].unk0 == NULL) {
            break;
        }
    }
    p = &D_ovl17_06_80045898[i];
    if (p < &D_ovl17_06_80045898[3]) {
        p->unk4 = arg0;
        p->unk6 = arg1;
        p->unk8 = arg2;
        p->unkC = arg3;
        func_ovl17_06_80044EC8(func_ovl17_06_80043CF4, p, 0, 0, 0x110);
    }
}

void func_ovl17_06_800438B4(void) {
    func_ovl17_06_80044CA0(20.0f, 20.0f, 20.0f);
    func_ovl17_06_80044C90(120);
}

void func_ovl17_06_800436B8(void) {
    UnkStructB *b;
    s16 i;
    s16 j;
    s16 n;

    n = 5;
    b = func_ovl17_06_800444F8();
    while (TRUE) {
        if (b->unk2C <= 0) {
            break;
        }
        func_ovl17_06_80044F10();
    }
    func_ovl17_06_800435CC();
    for (i = 0; i < 3; i++) {
        D_ovl17_06_80045880[i].unk0 = i;
    }
    while (TRUE) {
        for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
            D_ovl17_06_80045880[j].unk6 = 0;
        }
        func_ovl17_06_80043234(D_ovl17_06_80045880, 15, 11);
        func_ovl17_06_80044EC8(func_ovl17_06_800439CC, &D_ovl17_06_80045880[0], 0, 0, 0x110);
        func_ovl17_06_80044EE8(func_ovl17_06_80045088(10) + 5);
        func_ovl17_06_80044EC8(func_ovl17_06_800439CC, &D_ovl17_06_80045880[1], 0, 0, 0x110);
        func_ovl17_06_80044EE8(func_ovl17_06_80045088(10) + 5);
        func_ovl17_06_80044EC8(func_ovl17_06_800439CC, &D_ovl17_06_80045880[2], 0, 0, 0x110);
        func_ovl17_06_80044F10();
            while (TRUE) {
                if ((D_ovl17_06_80045880[0].unk6 & 1) && (D_ovl17_06_80045880[1].unk6 & 1) &&
                    (D_ovl17_06_80045880[2].unk6 & 1)) {
                    break;
                }
                func_ovl17_06_80044F10();
            }
        func_ovl17_06_80044F10();
        }
        func_ovl17_06_80044EE8(func_ovl17_06_80045088(60) + 30);
    }
}

static void func_ovl17_06_8004344C(UnkStruct_ovl17_06_80045694 *e) {
    e->unk0 = func_ovl17_06_80044DC0(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl17_06_80044D78(e->unk0, 0x01080000);
    func_ovl17_06_80044D80(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl17_06_80044AC0(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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

void func_ovl17_06_800435CC(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 3; i++) {
        func_ovl17_06_8004344C(&D_ovl17_06_80045694[i]);
        obj = func_ovl17_06_80044DB0(D_ovl17_06_80045694[i].unk0);
        obj->unk54 = 2.0f;
        obj->unk4C = 2.0f;
        obj->unk40->unk36 = 0xCC;
        func_ovl17_06_80044D80(D_ovl17_06_80045694[i].unk0, 0x80000);
        func_ovl17_06_80044D80(D_ovl17_06_80045694[i].unk0, 0x01000000);
        func_ovl17_06_8004344C(&D_ovl17_06_8004573C[i]);
        func_ovl17_06_80044D80(D_ovl17_06_8004573C[i].unk0, 0x01000000);
    }
}

void func_ovl17_06_80043234(UnkStruct_ovl17_06_80045880 *arg0, s16 arg1, s16 arg2) {
    s32 pad; /* unused: the original's frame is 4 bytes bigger */
    s16 xs[3];
    s16 ys[3];
    s16 i;
    s16 j;
    s16 tries;

    for (i = 0, tries = 0; i < 3;) {
        xs[i] = func_ovl17_06_80045088(arg1);
        ys[i] = func_ovl17_06_80045088(arg2);
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
        arg0[i].unk4 = ys[i] + 9.0f;
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl17_06_800430D4(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl17_06_80045230(D_ovl17_06_80045670);
            func_ovl17_06_80044378(0x211);
            func_ovl17_06_80044390(0x21E);
            func_ovl17_06_80044528();
            func_ovl17_06_8004309C(0x296);
            func_ovl17_06_800444F0(0);
            func_ovl17_06_80044C20(0x7F);
            func_ovl17_06_80044B98(1);
            func_ovl17_06_80044BA8(1);
            func_ovl17_06_80044BB8(2350.0f, 205.0f, 1612.0f);
            func_ovl17_06_80044BD8(0.0f, 40.0f, 2900.0f);
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
            func_ovl17_06_80043034();
            break;
        case 1:
            func_ovl17_06_800451C8(0, 0, 0, 0.0f);
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

void func_ovl17_06_8004309C(s32 arg0) {
    D_ovl17_06_8004587C = func_ovl17_06_80044F50(arg0);
    func_ovl17_06_80044F60(D_ovl17_06_8004587C, 0x20000000);
}

void func_ovl17_06_80043034(void) {
    UnkStructB *b;

    b = func_ovl17_06_800444F8();
    if (b->unk38 == 1 && b->unk0 == 0) {
        func_ovl17_06_80043010();
        func_ovl17_06_80044EC8(func_ovl17_06_800436B8, NULL, 0, 0, 0x110);
    }
}

void func_ovl17_06_80043010(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_ovl17_06_80045898[i].unk0 = NULL;
    }
}
