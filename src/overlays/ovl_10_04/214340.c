#include "common.h"

/*
 * ovl_10_04's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). It is ovl_10_02's object
 * (20D660.c) with other numbers: four of its setup functions don't call
 * 80044AC0 (ovl_10_02's 80044AE0), and 80043028 and 80043404 pass other
 * values. The task functions (800432B0-80043388, 80044234-80044344, with the
 * strings "trap task:entry failed" and "task_entry>%d:%s") are in every one
 * of bank 0x10's overlays.
 */

/* What func_ovl10_04_800453E0 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl10_04_800453E0;

/* What func_ovl10_04_800454A0 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_04_80045F60;

void func_ovl10_04_80044588(const char *, ...);
void func_ovl10_04_800448C8(s32);
void func_ovl10_04_800448D0(s32, f32, f32, f32, s32, s32);
void func_ovl10_04_800448E0(s32);
f32 func_ovl10_04_80044988(UnkStructA_40 *);
void func_ovl10_04_80044990(s32);
void func_ovl10_04_800449B0(void (*)(UnkStructA *));
void func_ovl10_04_800449C0(s32, s32, s32);
void func_ovl10_04_80044A00(void (*)(UnkStructA *));
void func_ovl10_04_80044A78(void);
void func_ovl10_04_80044A80(s32, s32, s32);
s32 func_ovl10_04_80044A90(s32, s32, s32, s32);
s32 func_ovl10_04_80044AA8(void);
void func_ovl10_04_80044AC8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_04_80044AD8(void);
UnkStructA *func_ovl10_04_80044B08(s32);
void func_ovl10_04_80044B10(s32);
void func_ovl10_04_80044FF0(UnkStructA_40 *, s32, s32);
f32 func_ovl10_04_80045008(UnkStructA_40 *, s32);
void func_ovl10_04_80045020(UnkStructA_40 *, s32, s32);
void func_ovl10_04_80045108(f32, f32, f32);
void func_ovl10_04_80045128(f32, f32, f32);
void func_ovl10_04_80045130(f32 *, f32 *, f32 *);
void func_ovl10_04_80045170(s32);
f32 func_ovl10_04_80045270(Vec3f *, Vec3f *);
s32 func_ovl10_04_80045278(UnkStructA *, s32);
void func_ovl10_04_800452C8(void *, s32);
void func_ovl10_04_800452D0(UnkStructA *, s32);
void func_ovl10_04_800452E0(UnkStructA *);
UnkStructA *func_ovl10_04_800452F0(s32, s32, s32, s32);
void *func_ovl10_04_80045320(s32, s32, UnkStructA *);
void func_ovl10_04_80045348(UnkStructA *);
void func_ovl10_04_80045398(UnkStructA *, Vec3f *);
UnkStruct_ovl10_04_800453E0 *func_ovl10_04_800453E0(UnkStructA *, s32);
void func_ovl10_04_80045418(void (*)(void), s32, s32, s32, s32);
void func_ovl10_04_80045438(s32);
void func_ovl10_04_80045460(void);
UnkStruct_ovl10_04_80045F60 *func_ovl10_04_800454A0(void);
void func_ovl10_04_800454B0(UnkStruct_ovl10_04_80045F60 *, s32);
f32 func_ovl10_04_800455C0(f32);
s32 func_ovl10_04_800455D8(s32);
s32 *func_ovl10_04_800456B0(void);
void func_ovl10_04_80045718(s32, s32, s32, f32);
void func_ovl10_04_80045740(s32, s32, s32);
void func_ovl10_04_80045780(u32 (*)[3]);
void func_ovl10_04_80045868(s32, f32, f32, f32, s32);
void func_ovl10_04_80045870(s32, Vec3f *, s32);
void func_ovl10_04_80045910(UnkStructA *, s32, f32, s32 (*)(s32));
void func_ovl10_04_80045928(s32, s32, s32);
void func_ovl10_04_800459A0(s32);
void func_ovl10_04_800459C0(s32, f32, f32, f32);

void func_ovl10_04_80043010(void);
void func_ovl10_04_80043028(void);
void func_ovl10_04_80043150(void);
void func_ovl10_04_80043170(void);
void func_ovl10_04_800431C0(void);
void func_ovl10_04_80043210(void);
void func_ovl10_04_80043260(void);
s32 func_ovl10_04_800432B0(void (*)(void));
void func_ovl10_04_80043328(void);
void func_ovl10_04_80043388(void);
void func_ovl10_04_80043404(void);
void func_ovl10_04_800434FC(s32);
void func_ovl10_04_800435C0(UnkStructA *);
void func_ovl10_04_800435E0(s32);
void func_ovl10_04_80043740(void);
void func_ovl10_04_80043998(s32);
void func_ovl10_04_80043BE0(void);
void func_ovl10_04_80043D1C(UnkStructA *);
s32 func_ovl10_04_80044060(s32);
void func_ovl10_04_8004407C(UnkStructA *);
void func_ovl10_04_800440FC(UnkStructA *);
void func_ovl10_04_80044168(void);
void func_ovl10_04_800441A4(void);
void func_ovl10_04_80044234(void (*)(void));
void func_ovl10_04_80044250(s32);
void func_ovl10_04_8004426C(s32);
void func_ovl10_04_80044280(void);
s32 func_ovl10_04_8004429C(void (*)(void));
void func_ovl10_04_800442E0(void (*)(void));
s32 func_ovl10_04_8004430C(void (*)(void), const char *);
void func_ovl10_04_80044344(void);
void func_ovl10_04_80044438(s32, UnkStructA *);
void func_ovl10_04_8004446C(f32);
void func_ovl10_04_800444B4(f32, f32, f32);
void func_ovl10_04_80044510(void);
void func_ovl10_04_80044528(void);

static void func_ovl10_04_80043018(void);
static void func_ovl10_04_80043020(void);
static void func_ovl10_04_80043148(void);

/* .bss */
u8 D_ovl10_04_80045D10[0x24];
s32 D_ovl10_04_80045D34;
s32 D_ovl10_04_80045D38;
u8 D_ovl10_04_80045D3C[0x4]; /* unused (func_ovl10_04_80044528) */
Vec3f D_ovl10_04_80045D40;
s32 D_ovl10_04_80045D4C;
s32 D_ovl10_04_80045D50;
u8 D_ovl10_04_80045D54[0x4]; /* unused (func_ovl10_04_80044528) */
/* the tasks: a countdown and a function each */
s32 D_ovl10_04_80045D58[64];
s32 D_ovl10_04_80045E58; /* the running task */
u8 D_ovl10_04_80045E5C[0x4]; /* unused (func_ovl10_04_80044528) */
void (*D_ovl10_04_80045E60[64])(void);
UnkStruct_ovl10_04_80045F60 *D_ovl10_04_80045F60;
u8 D_ovl10_04_80045F64[0x4]; /* unused (func_ovl10_04_80044528) */
UnkStructA *D_ovl10_04_80045F68[8];
void *D_ovl10_04_80045F88[8];
s32 D_ovl10_04_80045FA8;
u8 D_ovl10_04_80045FAC[0x4]; /* unused (func_ovl10_04_80044528) */
s32 D_ovl10_04_80045FB0[8];
s32 D_ovl10_04_80045FD0[8];
s32 D_ovl10_04_80045FF0[4];

/* .data */
s32 D_ovl10_04_80045BC0[8] = { 0, 5, 4, 1, 2, 7, 6, 3 };
s32 D_ovl10_04_80045BE0[8] = { 0, 20, 20, 10, 20, 20, 20, 30 };
s32 D_ovl10_04_80045C00[8] = { 90, 190, 310, 350, 480, 580, 780, 940 };

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_04_80044578(void) {
}

static void func_ovl10_04_80044570(void) {
}

static void func_ovl10_04_80044568(void) {
}

static void func_ovl10_04_80044560(void) {
}

static void func_ovl10_04_80044558(void) {
}

static void func_ovl10_04_80044550(void) {
}

static void func_ovl10_04_80044548(void) {
}

static void func_ovl10_04_80044540(void) {
}

static void func_ovl10_04_80044538(void) {
}

static void func_ovl10_04_80044530(void) {
}

void func_ovl10_04_80044528(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_04_80045D10[0] = D_ovl10_04_80045D3C[0] + D_ovl10_04_80045D54[0] + D_ovl10_04_80045E5C[0] +
                                 D_ovl10_04_80045F64[0] + D_ovl10_04_80045FAC[0];
    }
}

void func_ovl10_04_80044510(void) {
    D_ovl10_04_80045D34 = -1;
    D_ovl10_04_80045D38 = -1;
}

void func_ovl10_04_800444B4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_04_80045108(D_ovl10_04_80045D40.x, D_ovl10_04_80045D40.y, D_ovl10_04_80045D40.z);
    func_ovl10_04_80045128(arg0, arg1, arg2);
    func_ovl10_04_80045438(180);
}

void func_ovl10_04_8004446C(f32 arg0) {
    f32 sp1C;

    func_ovl10_04_80045130(&sp1C, NULL, NULL);
    func_ovl10_04_80045128(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_04_80044438(s32 arg0, UnkStructA *arg1) {
    func_ovl10_04_800459C0(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_04_80044344(void) {
    s32 i;

    D_ovl10_04_80045D4C = 0;
    D_ovl10_04_80045D50 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_04_80045E60[i] != NULL) {
                D_ovl10_04_80045E58 = i;
                if (D_ovl10_04_80045D58[i] == 0) {
                    D_ovl10_04_80045E60[i]();
                } else {
                    D_ovl10_04_80045D58[i]--;
                }
            }
        }
        D_ovl10_04_80045D4C++;
        D_ovl10_04_80045D4C &= 3;
        func_ovl10_04_80045460();
    }
}

/* Defined above its caller 8004432C, which pulls it out among the earlier
 * functions all the same: only so does its string come first in .rodata. */
s32 func_ovl10_04_800432B0(void (*arg0)(void)) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_04_80045E60[i] == NULL) {
            D_ovl10_04_80045E60[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_04_80044588("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_04_8004430C(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_04_800432B0(arg0);
    func_ovl10_04_80044588("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_04_800442E0(void (*arg0)(void)) {
    D_ovl10_04_80045E60[func_ovl10_04_8004429C(arg0)] = NULL;
}

s32 func_ovl10_04_8004429C(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_04_80045E60[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_04_80044280(void) {
    D_ovl10_04_80045E60[D_ovl10_04_80045E58] = NULL;
}

void func_ovl10_04_8004426C(s32 arg0) {
    D_ovl10_04_80045E60[arg0] = NULL;
}

void func_ovl10_04_80044250(s32 arg0) {
    D_ovl10_04_80045D58[D_ovl10_04_80045E58] = arg0;
}

void func_ovl10_04_80044234(void (*arg0)(void)) {
    D_ovl10_04_80045E60[D_ovl10_04_80045E58] = arg0;
}

void func_ovl10_04_800441A4(void) {
    D_ovl10_04_80045F60 = func_ovl10_04_800454A0();
    func_ovl10_04_800454B0(D_ovl10_04_80045F60, 0x20000001);
    D_ovl10_04_80045F60->unk40 = 0.5f;
    D_ovl10_04_80045F60->unk44 = D_ovl10_04_80045F60->unk40 * 0.75f;
    D_ovl10_04_80045F60->unk18 = 0.1f;
    D_ovl10_04_80045F60->unk1C = -0.1f;
}

void func_ovl10_04_80044168(void) {
    s32 *p;

    p = func_ovl10_04_800456B0();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_04_800440FC(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_04_80045170(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_04_80045348(arg0);
        func_ovl10_04_80045460();
    }
}

void func_ovl10_04_8004407C(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_04_80045718(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_04_800452D0(arg0, 0x01000000);
        func_ovl10_04_80045438(5);
        func_ovl10_04_80045718(0, 0, 0, 0.0f);
        func_ovl10_04_80045398(arg0, &pos);
        func_ovl10_04_80045870(12, &pos, 0);
    }
}

s32 func_ovl10_04_80044060(s32 arg0) {
    s32 ret;

    ret = 0;
    if ((arg0 & 0xF) != 0xF) {
        ret = 1;
    }
    return ret;
}

void func_ovl10_04_80043D1C(UnkStructA *arg0) {
    s32 i;

    func_ovl10_04_80045170(15);
    i = 0;
    func_ovl10_04_80044FF0(arg0->unk40, 0x11, 0);
    func_ovl10_04_80045020(arg0->unk40, 4, 12);
    func_ovl10_04_80045020(arg0->unk40, 5, 13);
    func_ovl10_04_80045868(0, arg0->unk40->unk10, arg0->unk40->unk14 + 100.0f, arg0->unk40->unk18, 0);
    arg0->unk68 = 40.0f;
    arg0->unk70 = 1.6333334f;
    func_ovl10_04_800459A0(0x1E);
    while (TRUE) {
        func_ovl10_04_80045910(arg0, 0, 0.0f, func_ovl10_04_80044060);
        if (arg0->unk40->unk14 > 700.0f) {
            arg0->unk40->unk14 = 700.0f;
            arg0->unk68 = 0.0f;
            arg0->unk6C = 0.0f;
        }
        arg0->unk40->unk1C += 20.0f;
        if (arg0->unk40->unk1C >= 360.0f) {
            arg0->unk40->unk1C = 0.0f;
        }
        arg0->unk40->unk10 -= func_ovl10_04_800455C0(arg0->unk40->unk1C);
        func_ovl10_04_80045460();
        if (++i >= 200) {
            break;
        }
        if (arg0->unk40->unk14 < 700.0f && arg0->unk6C == 0.0f) {
            break;
        }
    }
    if (arg0->unk40->unk1C >= 90.0f && arg0->unk40->unk1C < 270.0f) {
        arg0->unk40->unk1C = 180.0f;
        arg0->unk40->unk14 = func_ovl10_04_80044988(arg0->unk40) + 70.0f;
    } else {
        arg0->unk40->unk1C = 0.0f;
        arg0->unk40->unk14 = func_ovl10_04_80044988(arg0->unk40);
    }
    func_ovl10_04_80044FF0(arg0->unk40, 0x13, 0);
    func_ovl10_04_800452D0(arg0, 0x0C000000);
    arg0->unk40->unk48->unk4->unk8 |= 0x20;
    arg0->unk40->unk48->unk4->unk8 |= 0x40;
    arg0->unk40->unk48->unk4->unk4 = func_ovl10_04_80045008(arg0->unk40, 0) - 0.1f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl10_04_80045438(0x50);
}

void func_ovl10_04_80043BE0(void) {
    s32 i;

    if (D_ovl10_04_80045FA8 == 180) {
        for (i = 0; i < 8; i++) {
            if (D_ovl10_04_80045BE0[i] != 0) {
                D_ovl10_04_80045FB0[i] = func_ovl10_04_800455D8(D_ovl10_04_80045BE0[i]) + D_ovl10_04_80045C00[i] + 180;
            } else {
                D_ovl10_04_80045FB0[i] = D_ovl10_04_80045C00[i] + 180;
            }
        }
    }
    if (D_ovl10_04_80045FA8 >= 180) {
        for (i = 0; i < 8; i++) {
            if (D_ovl10_04_80045FA8 == D_ovl10_04_80045FB0[i]) {
                func_ovl10_04_80043998(D_ovl10_04_80045BC0[i]);
            }
        }
    }
    func_ovl10_04_80043740();
    D_ovl10_04_80045FA8++;
    if (D_ovl10_04_80045FA8 == 1180) {
        D_ovl10_04_80045FA8 = 180;
    }
}

void func_ovl10_04_80043998(s32 arg0) {
    s32 i;
    s32 sp54[2] = { 0xAB, 0xAC };
    s32 sp4C[2] = { 0xB8, 0xB9 };
    f32 sp2C[8] = { 700.0f, 1800.0f, 1300.0f, 2400.0f, 1150.0f, 2250.0f, 850.0f, 1950.0f };

    for (i = 0; i < 8; i++) {
        if (D_ovl10_04_80045F68[i] == NULL) {
            D_ovl10_04_80045F68[i] = func_ovl10_04_800452F0(sp54[(s32)(arg0 * 0.25f)], 0x01000070, 0x30, 0);
            D_ovl10_04_80045F68[i]->unk40->unk10 = -1600.0f;
            D_ovl10_04_80045F68[i]->unk40->unk14 = 100.0f;
            D_ovl10_04_80045F68[i]->unk40->unk18 = sp2C[arg0];
            D_ovl10_04_80045FD0[i] = arg0;
            if ((s32)(arg0 * 0.25f) == 0) {
                D_ovl10_04_80045F68[i]->unk30 = 1;
                D_ovl10_04_80045F68[i]->unk34 = 150.0f;
                D_ovl10_04_80045F68[i]->unk38 = 120.0f;
            } else {
                D_ovl10_04_80045F68[i]->unk30 = 8;
                D_ovl10_04_80045F68[i]->unk34 = 300.0f;
                D_ovl10_04_80045F68[i]->unk38 = 1600.0f;
            }
            D_ovl10_04_80045F88[i] = func_ovl10_04_80045320(sp4C[(s32)(arg0 * 0.25f)], 0x01200000, D_ovl10_04_80045F68[i]);
            func_ovl10_04_800452C8(D_ovl10_04_80045F88[i], 0x80000);
            D_ovl10_04_80045FF0[i] = 0;
            break;
        }
    }
}

void func_ovl10_04_80043740(void) {
    s32 i;
    UnkStruct_ovl10_04_800453E0 *p;
    s32 pad; /* unused: the original's frame has the slot */
    f32 x;

    for (i = 0; i < 8; i++) {
        if (D_ovl10_04_80045F68[i] != NULL && D_ovl10_04_80045FA8 % 2 == i % 2) {
            func_ovl10_04_800435E0(i);
            if (D_ovl10_04_80045FD0[i] < 4) {
                x = D_ovl10_04_80045F68[i]->unk40->unk10;
                D_ovl10_04_80045F68[i]->unk40->unk10 = x + 42.5f;
            } else {
                D_ovl10_04_80045F68[i]->unk40->unk10 += 34.0f;
            }
            p = func_ovl10_04_800453E0(D_ovl10_04_80045F68[i], 7);
            if (p != NULL) {
                if (p->unk8 & 1) {
                    p->unk10 = 0x20;
                }
                if (p->unk8 & 4) {
                    p->unk10 = 0x40;
                }
                if (p->unk8 & 2) {
                    p->unk10 = 0x20;
                }
            }
            if (D_ovl10_04_80045FD0[i] < 4 && func_ovl10_04_80045278(D_ovl10_04_80045F68[i], 0x20) != 0) {
                D_ovl10_04_80045F68[i]->unk40->unk10 = x;
            }
            if (D_ovl10_04_80045F68[i]->unk40->unk10 > 5600.0f) {
                func_ovl10_04_800435C0(D_ovl10_04_80045F68[i]);
                D_ovl10_04_80045F68[i] = NULL;
            }
        }
    }
}

void func_ovl10_04_800435E0(s32 arg0) {
    Vec3f pos;
    Vec3f target;
    f32 dist;

    func_ovl10_04_80045398(D_ovl10_04_80045F68[arg0], &pos);
    if ((s32)(D_ovl10_04_80045FD0[arg0] * 0.25f) == 1) {
        pos.x += 1600.0f;
    }
    func_ovl10_04_80045398(func_ovl10_04_80044B08(func_ovl10_04_80044AA8()), &target);
    dist = func_ovl10_04_80045270(&pos, &target);
    if (D_ovl10_04_80045FF0[arg0] == 0 && dist <= 1000.0f) {
        D_ovl10_04_80045FF0[arg0]++;
        if ((s32)(D_ovl10_04_80045FD0[arg0] * 0.25f) == 0) {
            func_ovl10_04_800459A0(0x92);
        } else {
            func_ovl10_04_800459A0(0x93);
        }
    }
}

void func_ovl10_04_800435C0(UnkStructA *arg0) {
    func_ovl10_04_800452E0(arg0);
}

void func_ovl10_04_800434FC(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl10_04_80043404();
            break;
        case 17:
            func_ovl10_04_80043260();
            break;
        case 18:
            func_ovl10_04_80043210();
            break;
        case 19:
            func_ovl10_04_800431C0();
            break;
        case 20:
            func_ovl10_04_80043170();
            break;
        case 4:
            func_ovl10_04_80043150();
            break;
        case 0x50:
            func_ovl10_04_80043028();
            break;
    }
}

/* passed to func_ovl10_04_80045780: three 12-byte records and an end */
u32 D_ovl10_04_80045C50[][3] = {
    { 0xA60002, 0xE, 4 },
    { 0xA70001, 0xE, 4 },
    { 0xB70000, 0xE, 4 },
    { 0, 0, 0 },
};

void func_ovl10_04_80043404(void) {
    func_ovl10_04_80045780(D_ovl10_04_80045C50);
    func_ovl10_04_80045928(0, 0, 0xDE);
    func_ovl10_04_80045928(1, 0x11, 0xEF);
    func_ovl10_04_80045928(2, 0x1A, 0xF8);
    func_ovl10_04_80045928(3, 0x1B, 0xF9);
    func_ovl10_04_800448C8(0x1D8);
    func_ovl10_04_800448D0(0x1D9, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_04_800448D0(0x1DB, 0.0f, 0.0f, 0.0f, 0x60, 0);
    func_ovl10_04_80045740(0xF, 0x7E, 0);
    func_ovl10_04_800448E0(0x1E4);
    func_ovl10_04_80044990(0xF);
    func_ovl10_04_80044A78();
    func_ovl10_04_80043388();
    func_ovl10_04_80043328();
    func_ovl10_04_800449B0(func_ovl10_04_800440FC);
}

void func_ovl10_04_80043388(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_04_80045E60[i] = NULL;
        D_ovl10_04_80045D58[i] = 0;
    }
    func_ovl10_04_80045418(func_ovl10_04_80044344, 0, 0, 0, 0x110);
}

void func_ovl10_04_80043328(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_ovl10_04_80045F68[i] = NULL;
    }
    D_ovl10_04_80045FA8 = 0;
    func_ovl10_04_80044A00(func_ovl10_04_80043D1C);
    func_ovl10_04_800432B0(func_ovl10_04_80043BE0);
}

void func_ovl10_04_80043260(void) {
    func_ovl10_04_80044A80(0x2C, 1, 10);
    func_ovl10_04_80044AC8(0xC0, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_04_80043210(void) {
    func_ovl10_04_80044A80(0x2C, 1, 21);
    func_ovl10_04_80044AC8(0xC0, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_04_800431C0(void) {
    func_ovl10_04_80044A80(3, 1, 10);
    func_ovl10_04_80044AC8(0x40, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_04_80043170(void) {
    func_ovl10_04_80044A80(3, 1, 21);
    func_ovl10_04_80044AC8(0x40, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_04_80043150(void) {
    func_ovl10_04_80043148();
    func_ovl10_04_80044AD8();
}

static void func_ovl10_04_80043148(void) {
}

void func_ovl10_04_80043028(void) {
    func_ovl10_04_80043018();
    func_ovl10_04_80043020();
    func_ovl10_04_80044B10(1);
    if (func_ovl10_04_80044A90(0x2C, 6, 0x2E, 0xE) != 0) {
        D_ovl10_04_80045D34 = 0x6A;
        D_ovl10_04_80045D38 = 0x13;
        func_ovl10_04_800449C0(0x6A, 0x13, 0);
    }
    if (func_ovl10_04_80044A90(0x2C, 0x11, 0x2E, 0x19) != 0) {
        D_ovl10_04_80045D34 = 0x6A;
        D_ovl10_04_80045D38 = 0x14;
        func_ovl10_04_800449C0(0x6A, 0x14, 0);
    }
    if (func_ovl10_04_80044A90(1, 6, 3, 0xE) != 0) {
        D_ovl10_04_80045D34 = 0x6C;
        D_ovl10_04_80045D38 = 0x11;
        func_ovl10_04_800449C0(0x6C, 0x11, 0);
    }
    if (func_ovl10_04_80044A90(1, 0x11, 3, 0x19) != 0) {
        D_ovl10_04_80045D34 = 0x6C;
        D_ovl10_04_80045D38 = 0x12;
        func_ovl10_04_800449C0(0x6C, 0x12, 0);
    }
}

static void func_ovl10_04_80043020(void) {
}

static void func_ovl10_04_80043018(void) {
}

void func_ovl10_04_80043010(void) {
}
