#include "common.h"

/*
 * ovl_10_02's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). The task functions
 * (800432D0-800433A8, 80044254-80044364, with the strings "trap task:entry
 * failed" and "task_entry>%d:%s") are in every one of bank 0x10's overlays.
 */

/* What func_ovl10_02_80045400 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl10_02_80045400;

/* What func_ovl10_02_800454C0 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_02_80045F80;

void func_ovl10_02_800445A8(const char *, ...);
void func_ovl10_02_800448E8(s32);
void func_ovl10_02_800448F0(s32, f32, f32, f32, s32, s32);
void func_ovl10_02_80044900(s32);
f32 func_ovl10_02_800449A8(UnkStructA_40 *);
void func_ovl10_02_800449B0(s32);
void func_ovl10_02_800449D0(void (*)(UnkStructA *));
void func_ovl10_02_800449E0(s32, s32, s32);
void func_ovl10_02_80044A20(void (*)(UnkStructA *));
void func_ovl10_02_80044A98(void);
void func_ovl10_02_80044AA0(s32, s32, s32);
s32 func_ovl10_02_80044AB0(s32, s32, s32, s32);
s32 func_ovl10_02_80044AC8(void);
void func_ovl10_02_80044AE0(s32);
void func_ovl10_02_80044AE8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_02_80044AF8(void);
UnkStructA *func_ovl10_02_80044B28(s32);
void func_ovl10_02_80044B30(s32);
void func_ovl10_02_80045010(UnkStructA_40 *, s32, s32);
f32 func_ovl10_02_80045028(UnkStructA_40 *, s32);
void func_ovl10_02_80045040(UnkStructA_40 *, s32, s32);
void func_ovl10_02_80045128(f32, f32, f32);
void func_ovl10_02_80045148(f32, f32, f32);
void func_ovl10_02_80045150(f32 *, f32 *, f32 *);
void func_ovl10_02_80045190(s32);
f32 func_ovl10_02_80045290(Vec3f *, Vec3f *);
s32 func_ovl10_02_80045298(UnkStructA *, s32);
void func_ovl10_02_800452E8(void *, s32);
void func_ovl10_02_800452F0(UnkStructA *, s32);
void func_ovl10_02_80045300(UnkStructA *);
UnkStructA *func_ovl10_02_80045310(s32, s32, s32, s32);
void *func_ovl10_02_80045340(s32, s32, UnkStructA *);
void func_ovl10_02_80045368(UnkStructA *);
void func_ovl10_02_800453B8(UnkStructA *, Vec3f *);
UnkStruct_ovl10_02_80045400 *func_ovl10_02_80045400(UnkStructA *, s32);
void func_ovl10_02_80045438(void (*)(void), s32, s32, s32, s32);
void func_ovl10_02_80045458(s32);
void func_ovl10_02_80045480(void);
UnkStruct_ovl10_02_80045F80 *func_ovl10_02_800454C0(void);
void func_ovl10_02_800454D0(UnkStruct_ovl10_02_80045F80 *, s32);
f32 func_ovl10_02_800455E0(f32);
s32 func_ovl10_02_800455F8(s32);
s32 *func_ovl10_02_800456D0(void);
void func_ovl10_02_80045738(s32, s32, s32, f32);
void func_ovl10_02_80045760(s32, s32, s32);
void func_ovl10_02_800457A0(u32 (*)[3]);
void func_ovl10_02_80045888(s32, f32, f32, f32, s32);
void func_ovl10_02_80045890(s32, Vec3f *, s32);
void func_ovl10_02_80045930(UnkStructA *, s32, f32, s32 (*)(s32));
void func_ovl10_02_80045948(s32, s32, s32);
void func_ovl10_02_800459C0(s32);
void func_ovl10_02_800459E0(s32, f32, f32, f32);

void func_ovl10_02_80043010(void);
void func_ovl10_02_80043028(void);
void func_ovl10_02_80043150(void);
void func_ovl10_02_80043170(void);
void func_ovl10_02_800431C8(void);
void func_ovl10_02_80043220(void);
void func_ovl10_02_80043278(void);
s32 func_ovl10_02_800432D0(void (*)(void));
void func_ovl10_02_80043348(void);
void func_ovl10_02_800433A8(void);
void func_ovl10_02_80043424(void);
void func_ovl10_02_8004351C(s32);
void func_ovl10_02_800435E0(UnkStructA *);
void func_ovl10_02_80043600(s32);
void func_ovl10_02_80043760(void);
void func_ovl10_02_800439B8(s32);
void func_ovl10_02_80043C00(void);
void func_ovl10_02_80043D3C(UnkStructA *);
s32 func_ovl10_02_80044080(s32);
void func_ovl10_02_8004409C(UnkStructA *);
void func_ovl10_02_8004411C(UnkStructA *);
void func_ovl10_02_80044188(void);
void func_ovl10_02_800441C4(void);
void func_ovl10_02_80044254(void (*)(void));
void func_ovl10_02_80044270(s32);
void func_ovl10_02_8004428C(s32);
void func_ovl10_02_800442A0(void);
s32 func_ovl10_02_800442BC(void (*)(void));
void func_ovl10_02_80044300(void (*)(void));
s32 func_ovl10_02_8004432C(void (*)(void), const char *);
void func_ovl10_02_80044364(void);
void func_ovl10_02_80044458(s32, UnkStructA *);
void func_ovl10_02_8004448C(f32);
void func_ovl10_02_800444D4(f32, f32, f32);
void func_ovl10_02_80044530(void);
void func_ovl10_02_80044548(void);

static void func_ovl10_02_80043018(void);
static void func_ovl10_02_80043020(void);
static void func_ovl10_02_80043148(void);

/* .bss */
u8 D_ovl10_02_80045D30[0x24];
s32 D_ovl10_02_80045D54;
s32 D_ovl10_02_80045D58;
u8 D_ovl10_02_80045D5C[0x4]; /* unused (func_ovl10_02_80044548) */
Vec3f D_ovl10_02_80045D60;
s32 D_ovl10_02_80045D6C;
s32 D_ovl10_02_80045D70;
u8 D_ovl10_02_80045D74[0x4]; /* unused (func_ovl10_02_80044548) */
/* the tasks: a countdown and a function each */
s32 D_ovl10_02_80045D78[64];
s32 D_ovl10_02_80045E78; /* the running task */
u8 D_ovl10_02_80045E7C[0x4]; /* unused (func_ovl10_02_80044548) */
void (*D_ovl10_02_80045E80[64])(void);
UnkStruct_ovl10_02_80045F80 *D_ovl10_02_80045F80;
u8 D_ovl10_02_80045F84[0x4]; /* unused (func_ovl10_02_80044548) */
UnkStructA *D_ovl10_02_80045F88[8];
void *D_ovl10_02_80045FA8[8];
s32 D_ovl10_02_80045FC8;
u8 D_ovl10_02_80045FCC[0x4]; /* unused (func_ovl10_02_80044548) */
s32 D_ovl10_02_80045FD0[8];
s32 D_ovl10_02_80045FF0[8];
s32 D_ovl10_02_80046010[4];

/* .data */
s32 D_ovl10_02_80045BE0[8] = { 0, 5, 4, 1, 2, 7, 6, 3 };
s32 D_ovl10_02_80045C00[8] = { 0, 20, 20, 10, 20, 20, 20, 30 };
s32 D_ovl10_02_80045C20[8] = { 90, 190, 310, 350, 480, 580, 780, 940 };

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_02_80044598(void) {
}

static void func_ovl10_02_80044590(void) {
}

static void func_ovl10_02_80044588(void) {
}

static void func_ovl10_02_80044580(void) {
}

static void func_ovl10_02_80044578(void) {
}

static void func_ovl10_02_80044570(void) {
}

static void func_ovl10_02_80044568(void) {
}

static void func_ovl10_02_80044560(void) {
}

static void func_ovl10_02_80044558(void) {
}

static void func_ovl10_02_80044550(void) {
}

void func_ovl10_02_80044548(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_02_80045D30[0] = D_ovl10_02_80045D5C[0] + D_ovl10_02_80045D74[0] + D_ovl10_02_80045E7C[0] +
                                 D_ovl10_02_80045F84[0] + D_ovl10_02_80045FCC[0];
    }
}

void func_ovl10_02_80044530(void) {
    D_ovl10_02_80045D54 = -1;
    D_ovl10_02_80045D58 = -1;
}

void func_ovl10_02_800444D4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_02_80045128(D_ovl10_02_80045D60.x, D_ovl10_02_80045D60.y, D_ovl10_02_80045D60.z);
    func_ovl10_02_80045148(arg0, arg1, arg2);
    func_ovl10_02_80045458(180);
}

void func_ovl10_02_8004448C(f32 arg0) {
    f32 sp1C;

    func_ovl10_02_80045150(&sp1C, NULL, NULL);
    func_ovl10_02_80045148(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_02_80044458(s32 arg0, UnkStructA *arg1) {
    func_ovl10_02_800459E0(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_02_80044364(void) {
    s32 i;

    D_ovl10_02_80045D6C = 0;
    D_ovl10_02_80045D70 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_02_80045E80[i] != NULL) {
                D_ovl10_02_80045E78 = i;
                if (D_ovl10_02_80045D78[i] == 0) {
                    D_ovl10_02_80045E80[i]();
                } else {
                    D_ovl10_02_80045D78[i]--;
                }
            }
        }
        D_ovl10_02_80045D6C++;
        D_ovl10_02_80045D6C &= 3;
        func_ovl10_02_80045480();
    }
}

/* Defined above its caller 8004432C, which pulls it out among the earlier
 * functions all the same: only so does its string come first in .rodata. */
s32 func_ovl10_02_800432D0(void (*arg0)(void)) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_02_80045E80[i] == NULL) {
            D_ovl10_02_80045E80[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_02_800445A8("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_02_8004432C(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_02_800432D0(arg0);
    func_ovl10_02_800445A8("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_02_80044300(void (*arg0)(void)) {
    D_ovl10_02_80045E80[func_ovl10_02_800442BC(arg0)] = NULL;
}

s32 func_ovl10_02_800442BC(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_02_80045E80[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_02_800442A0(void) {
    D_ovl10_02_80045E80[D_ovl10_02_80045E78] = NULL;
}

void func_ovl10_02_8004428C(s32 arg0) {
    D_ovl10_02_80045E80[arg0] = NULL;
}

void func_ovl10_02_80044270(s32 arg0) {
    D_ovl10_02_80045D78[D_ovl10_02_80045E78] = arg0;
}

void func_ovl10_02_80044254(void (*arg0)(void)) {
    D_ovl10_02_80045E80[D_ovl10_02_80045E78] = arg0;
}

void func_ovl10_02_800441C4(void) {
    D_ovl10_02_80045F80 = func_ovl10_02_800454C0();
    func_ovl10_02_800454D0(D_ovl10_02_80045F80, 0x20000001);
    D_ovl10_02_80045F80->unk40 = 0.5f;
    D_ovl10_02_80045F80->unk44 = D_ovl10_02_80045F80->unk40 * 0.75f;
    D_ovl10_02_80045F80->unk18 = 0.1f;
    D_ovl10_02_80045F80->unk1C = -0.1f;
}

void func_ovl10_02_80044188(void) {
    s32 *p;

    p = func_ovl10_02_800456D0();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_02_8004411C(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_02_80045190(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_02_80045368(arg0);
        func_ovl10_02_80045480();
    }
}

void func_ovl10_02_8004409C(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_02_80045738(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_02_800452F0(arg0, 0x01000000);
        func_ovl10_02_80045458(5);
        func_ovl10_02_80045738(0, 0, 0, 0.0f);
        func_ovl10_02_800453B8(arg0, &pos);
        func_ovl10_02_80045890(12, &pos, 0);
    }
}

s32 func_ovl10_02_80044080(s32 arg0) {
    s32 ret;

    ret = 0;
    if ((arg0 & 0xF) != 0xF) {
        ret = 1;
    }
    return ret;
}

void func_ovl10_02_80043D3C(UnkStructA *arg0) {
    s32 i;

    func_ovl10_02_80045190(15);
    i = 0;
    func_ovl10_02_80045010(arg0->unk40, 0x11, 0);
    func_ovl10_02_80045040(arg0->unk40, 4, 12);
    func_ovl10_02_80045040(arg0->unk40, 5, 13);
    func_ovl10_02_80045888(0, arg0->unk40->unk10, arg0->unk40->unk14 + 100.0f, arg0->unk40->unk18, 0);
    arg0->unk68 = 40.0f;
    arg0->unk70 = 1.6333334f;
    func_ovl10_02_800459C0(0x1E);
    while (TRUE) {
        func_ovl10_02_80045930(arg0, 0, 0.0f, func_ovl10_02_80044080);
        if (arg0->unk40->unk14 > 700.0f) {
            arg0->unk40->unk14 = 700.0f;
            arg0->unk68 = 0.0f;
            arg0->unk6C = 0.0f;
        }
        arg0->unk40->unk1C += 20.0f;
        if (arg0->unk40->unk1C >= 360.0f) {
            arg0->unk40->unk1C = 0.0f;
        }
        arg0->unk40->unk10 -= func_ovl10_02_800455E0(arg0->unk40->unk1C);
        func_ovl10_02_80045480();
        if (++i >= 200) {
            break;
        }
        if (arg0->unk40->unk14 < 700.0f && arg0->unk6C == 0.0f) {
            break;
        }
    }
    if (arg0->unk40->unk1C >= 90.0f && arg0->unk40->unk1C < 270.0f) {
        arg0->unk40->unk1C = 180.0f;
        arg0->unk40->unk14 = func_ovl10_02_800449A8(arg0->unk40) + 70.0f;
    } else {
        arg0->unk40->unk1C = 0.0f;
        arg0->unk40->unk14 = func_ovl10_02_800449A8(arg0->unk40);
    }
    func_ovl10_02_80045010(arg0->unk40, 0x13, 0);
    func_ovl10_02_800452F0(arg0, 0x0C000000);
    arg0->unk40->unk48->unk4->unk8 |= 0x20;
    arg0->unk40->unk48->unk4->unk8 |= 0x40;
    arg0->unk40->unk48->unk4->unk4 = func_ovl10_02_80045028(arg0->unk40, 0) - 0.1f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl10_02_80045458(0x50);
}

void func_ovl10_02_80043C00(void) {
    s32 i;

    if (D_ovl10_02_80045FC8 == 180) {
        for (i = 0; i < 8; i++) {
            if (D_ovl10_02_80045C00[i] != 0) {
                D_ovl10_02_80045FD0[i] = func_ovl10_02_800455F8(D_ovl10_02_80045C00[i]) + D_ovl10_02_80045C20[i] + 180;
            } else {
                D_ovl10_02_80045FD0[i] = D_ovl10_02_80045C20[i] + 180;
            }
        }
    }
    if (D_ovl10_02_80045FC8 >= 180) {
        for (i = 0; i < 8; i++) {
            if (D_ovl10_02_80045FC8 == D_ovl10_02_80045FD0[i]) {
                func_ovl10_02_800439B8(D_ovl10_02_80045BE0[i]);
            }
        }
    }
    func_ovl10_02_80043760();
    D_ovl10_02_80045FC8++;
    if (D_ovl10_02_80045FC8 == 1180) {
        D_ovl10_02_80045FC8 = 180;
    }
}

void func_ovl10_02_800439B8(s32 arg0) {
    s32 i;
    s32 sp54[2] = { 0xAB, 0xAC };
    s32 sp4C[2] = { 0xB8, 0xB9 };
    f32 sp2C[8] = { 700.0f, 1800.0f, 1300.0f, 2400.0f, 1150.0f, 2250.0f, 850.0f, 1950.0f };

    for (i = 0; i < 8; i++) {
        if (D_ovl10_02_80045F88[i] == NULL) {
            D_ovl10_02_80045F88[i] = func_ovl10_02_80045310(sp54[(s32)(arg0 * 0.25f)], 0x01000070, 0x30, 0);
            D_ovl10_02_80045F88[i]->unk40->unk10 = -1600.0f;
            D_ovl10_02_80045F88[i]->unk40->unk14 = 100.0f;
            D_ovl10_02_80045F88[i]->unk40->unk18 = sp2C[arg0];
            D_ovl10_02_80045FF0[i] = arg0;
            if ((s32)(arg0 * 0.25f) == 0) {
                D_ovl10_02_80045F88[i]->unk30 = 1;
                D_ovl10_02_80045F88[i]->unk34 = 150.0f;
                D_ovl10_02_80045F88[i]->unk38 = 120.0f;
            } else {
                D_ovl10_02_80045F88[i]->unk30 = 8;
                D_ovl10_02_80045F88[i]->unk34 = 300.0f;
                D_ovl10_02_80045F88[i]->unk38 = 1600.0f;
            }
            D_ovl10_02_80045FA8[i] = func_ovl10_02_80045340(sp4C[(s32)(arg0 * 0.25f)], 0x01200000, D_ovl10_02_80045F88[i]);
            func_ovl10_02_800452E8(D_ovl10_02_80045FA8[i], 0x80000);
            D_ovl10_02_80046010[i] = 0;
            break;
        }
    }
}

void func_ovl10_02_80043760(void) {
    s32 i;
    UnkStruct_ovl10_02_80045400 *p;
    s32 pad; /* unused: the original's frame has the slot */
    f32 x;

    for (i = 0; i < 8; i++) {
        if (D_ovl10_02_80045F88[i] != NULL && D_ovl10_02_80045FC8 % 2 == i % 2) {
            func_ovl10_02_80043600(i);
            if (D_ovl10_02_80045FF0[i] < 4) {
                x = D_ovl10_02_80045F88[i]->unk40->unk10;
                D_ovl10_02_80045F88[i]->unk40->unk10 = x + 42.5f;
            } else {
                D_ovl10_02_80045F88[i]->unk40->unk10 += 34.0f;
            }
            p = func_ovl10_02_80045400(D_ovl10_02_80045F88[i], 7);
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
            if (D_ovl10_02_80045FF0[i] < 4 && func_ovl10_02_80045298(D_ovl10_02_80045F88[i], 0x20) != 0) {
                D_ovl10_02_80045F88[i]->unk40->unk10 = x;
            }
            if (D_ovl10_02_80045F88[i]->unk40->unk10 > 5600.0f) {
                func_ovl10_02_800435E0(D_ovl10_02_80045F88[i]);
                D_ovl10_02_80045F88[i] = NULL;
            }
        }
    }
}

void func_ovl10_02_80043600(s32 arg0) {
    Vec3f pos;
    Vec3f target;
    f32 dist;

    func_ovl10_02_800453B8(D_ovl10_02_80045F88[arg0], &pos);
    if ((s32)(D_ovl10_02_80045FF0[arg0] * 0.25f) == 1) {
        pos.x += 1600.0f;
    }
    func_ovl10_02_800453B8(func_ovl10_02_80044B28(func_ovl10_02_80044AC8()), &target);
    dist = func_ovl10_02_80045290(&pos, &target);
    if (D_ovl10_02_80046010[arg0] == 0 && dist <= 1000.0f) {
        D_ovl10_02_80046010[arg0]++;
        if ((s32)(D_ovl10_02_80045FF0[arg0] * 0.25f) == 0) {
            func_ovl10_02_800459C0(0x92);
        } else {
            func_ovl10_02_800459C0(0x93);
        }
    }
}

void func_ovl10_02_800435E0(UnkStructA *arg0) {
    func_ovl10_02_80045300(arg0);
}

void func_ovl10_02_8004351C(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl10_02_80043424();
            break;
        case 17:
            func_ovl10_02_80043278();
            break;
        case 18:
            func_ovl10_02_80043220();
            break;
        case 19:
            func_ovl10_02_800431C8();
            break;
        case 20:
            func_ovl10_02_80043170();
            break;
        case 4:
            func_ovl10_02_80043150();
            break;
        case 0x50:
            func_ovl10_02_80043028();
            break;
    }
}

/* passed to func_ovl10_02_800457A0: three 12-byte records and an end */
u32 D_ovl10_02_80045C70[][3] = {
    { 0xA60002, 0xE, 4 },
    { 0xA70001, 0xE, 4 },
    { 0xB70000, 0xE, 4 },
    { 0, 0, 0 },
};

void func_ovl10_02_80043424(void) {
    func_ovl10_02_800457A0(D_ovl10_02_80045C70);
    func_ovl10_02_80045948(0, 0, 0xDE);
    func_ovl10_02_80045948(1, 0x11, 0xEF);
    func_ovl10_02_80045948(2, 0x1A, 0xF8);
    func_ovl10_02_80045948(3, 0x1B, 0xF9);
    func_ovl10_02_800448E8(0x1D8);
    func_ovl10_02_800448F0(0x1D9, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_02_800448F0(0x1DA, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_02_80045760(0xF, 0x7E, 0);
    func_ovl10_02_80044900(0x1E2);
    func_ovl10_02_800449B0(0xF);
    func_ovl10_02_80044A98();
    func_ovl10_02_800433A8();
    func_ovl10_02_80043348();
    func_ovl10_02_800449D0(func_ovl10_02_8004411C);
}

void func_ovl10_02_800433A8(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_02_80045E80[i] = NULL;
        D_ovl10_02_80045D78[i] = 0;
    }
    func_ovl10_02_80045438(func_ovl10_02_80044364, 0, 0, 0, 0x110);
}

void func_ovl10_02_80043348(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_ovl10_02_80045F88[i] = NULL;
    }
    D_ovl10_02_80045FC8 = 0;
    func_ovl10_02_80044A20(func_ovl10_02_80043D3C);
    func_ovl10_02_800432D0(func_ovl10_02_80043C00);
}

void func_ovl10_02_80043278(void) {
    func_ovl10_02_80044AA0(0x2C, 1, 10);
    func_ovl10_02_80044AE0(0xC0);
    func_ovl10_02_80044AE8(0xC0, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_02_80043220(void) {
    func_ovl10_02_80044AA0(0x2C, 1, 21);
    func_ovl10_02_80044AE0(0xC0);
    func_ovl10_02_80044AE8(0xC0, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_02_800431C8(void) {
    func_ovl10_02_80044AA0(3, 1, 10);
    func_ovl10_02_80044AE0(0x40);
    func_ovl10_02_80044AE8(0x40, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_02_80043170(void) {
    func_ovl10_02_80044AA0(3, 1, 21);
    func_ovl10_02_80044AE0(0x40);
    func_ovl10_02_80044AE8(0x40, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_02_80043150(void) {
    func_ovl10_02_80043148();
    func_ovl10_02_80044AF8();
}

static void func_ovl10_02_80043148(void) {
}

void func_ovl10_02_80043028(void) {
    func_ovl10_02_80043018();
    func_ovl10_02_80043020();
    func_ovl10_02_80044B30(1);
    if (func_ovl10_02_80044AB0(0x2C, 6, 0x2E, 0xE) != 0) {
        D_ovl10_02_80045D54 = 0x68;
        D_ovl10_02_80045D58 = 0x11;
        func_ovl10_02_800449E0(0x68, 0x11, 0);
    }
    if (func_ovl10_02_80044AB0(0x2C, 0x11, 0x2E, 0x19) != 0) {
        D_ovl10_02_80045D54 = 0x68;
        D_ovl10_02_80045D58 = 0x12;
        func_ovl10_02_800449E0(0x68, 0x12, 0);
    }
    if (func_ovl10_02_80044AB0(1, 6, 3, 0xE) != 0) {
        D_ovl10_02_80045D54 = 0x6A;
        D_ovl10_02_80045D58 = 0x11;
        func_ovl10_02_800449E0(0x6A, 0x11, 0);
    }
    if (func_ovl10_02_80044AB0(1, 0x11, 3, 0x19) != 0) {
        D_ovl10_02_80045D54 = 0x6A;
        D_ovl10_02_80045D58 = 0x12;
        func_ovl10_02_800449E0(0x6A, 0x12, 0);
    }
}

static void func_ovl10_02_80043020(void) {
}

static void func_ovl10_02_80043018(void) {
}

void func_ovl10_02_80043010(void) {
}
