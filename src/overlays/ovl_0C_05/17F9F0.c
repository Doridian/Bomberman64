#include "common.h"

/*
 * ovl_0C_05's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).  The same skeleton as
 * ovl_0C_03's 17A5B0.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_05_80045AA0;

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
} UnkStruct_ovl0C_05_8004598C;

void func_ovl0C_05_80044658(s32);
void func_ovl0C_05_80044670(s32);
void func_ovl0C_05_800446E0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_05_80044738(void (*)(UnkStructA *), s32);
void func_ovl0C_05_80044740(void (*)(UnkStructA *));
void func_ovl0C_05_80044750(s32, s32, s32);
void func_ovl0C_05_80044790(void (*)(UnkStructA *));
void func_ovl0C_05_800447E0(s32, s32);
void func_ovl0C_05_800447F8(s32);
void func_ovl0C_05_80044808(void);
void func_ovl0C_05_80044810(s32, s32, s32);
void func_ovl0C_05_80044818(void *);
s32 func_ovl0C_05_80044820(s32, s32, s32, s32);
s32 func_ovl0C_05_80044838(void);
void func_ovl0C_05_80044840(s32, void *);
void func_ovl0C_05_80044848(s32);
void func_ovl0C_05_80044850(s32);
void func_ovl0C_05_80044858(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_05_80044868(void);
UnkStructA *func_ovl0C_05_80044898(s32);
void func_ovl0C_05_800448A0(s32);
UnkStructA *func_ovl0C_05_800448D8(s32);
s32 func_ovl0C_05_80044DA0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0C_05_80044DA8(s32);
void func_ovl0C_05_80044E98(f32, f32, f32);
void func_ovl0C_05_80044EB8(f32, f32, f32);
void func_ovl0C_05_80044EC0(f32 *, f32 *, f32 *);
void func_ovl0C_05_80044F50(f32, f32);
s32 func_ovl0C_05_80045008(UnkStructA *, s32, UnkStructA *);
void func_ovl0C_05_80045058(UnkStructA *, s32);
void func_ovl0C_05_80045060(UnkStructA *, s32);
void func_ovl0C_05_80045070(UnkStructA *);
UnkStructA *func_ovl0C_05_80045080(s32, s32, s32, s32);
UnkStructA *func_ovl0C_05_800450A0(s32, s32, f32, f32, f32);
s32 func_ovl0C_05_80045178(UnkStructA *, s32, UnkStructA *);
void func_ovl0C_05_800451A8(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_05_800451B8(void);
void func_ovl0C_05_800451C8(s32);
UnkStructA *func_ovl0C_05_800451D0(void);
void func_ovl0C_05_800451F0(void);
f32 func_ovl0C_05_80045350(f32);
void func_ovl0C_05_80045428(s32);
s32 func_ovl0C_05_80045430(s32);
void func_ovl0C_05_80045510(u32 (*)[3]);
void func_ovl0C_05_800456A8(UnkStructA *, s32, f32);
void func_ovl0C_05_800456B8(s32, s32, s32);
void func_ovl0C_05_80045730(s32);
void func_ovl0C_05_80045750(s32, f32, f32, f32);

void func_ovl0C_05_80043010(void);
void func_ovl0C_05_80043020(void);
void func_ovl0C_05_80043040(void);
void func_ovl0C_05_80043068(void);
void func_ovl0C_05_800430B0(void);
void func_ovl0C_05_80043108(void);
void func_ovl0C_05_80043198(void);
void func_ovl0C_05_800431E0(void);
void func_ovl0C_05_8004326C(void);
void func_ovl0C_05_800432D0(void);
void func_ovl0C_05_80043328(f32);
void func_ovl0C_05_80043370(void);
void func_ovl0C_05_800434A0(void);
void func_ovl0C_05_800434DC(s32, s32, s32, f32, s32);
void func_ovl0C_05_80043504(void);
void func_ovl0C_05_80043554(void);
void func_ovl0C_05_800435A4(void);
void func_ovl0C_05_80043600(void);
static void func_ovl0C_05_800437CC(void);
void func_ovl0C_05_800437D4(void);
void func_ovl0C_05_80043814(void);
void func_ovl0C_05_8004384C(void);
void func_ovl0C_05_80043970(s32);
void func_ovl0C_05_80043B18(UnkStructA *);
void func_ovl0C_05_80043CE4(UnkStructA *);
void func_ovl0C_05_80043EB0(void);
void func_ovl0C_05_80043F34(UnkStructA *);
void func_ovl0C_05_80043FF4(UnkStructA *);
void func_ovl0C_05_80044038(UnkStructA *, s32, s32, f32, f32);
void func_ovl0C_05_80044110(void);
void func_ovl0C_05_80044220(s32, UnkStructA *);
void func_ovl0C_05_80044254(f32, f32, f32);
void func_ovl0C_05_800442B0(void);
void func_ovl0C_05_800442C8(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0C_05_80043018(void);
static void func_ovl0C_05_80043060(void);
static void func_ovl0C_05_800430F8(void);
static void func_ovl0C_05_80043100(void);
static void func_ovl0C_05_8004364C(UnkStruct_ovl0C_05_8004598C *);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0C_05_800430B0() \
    D_ovl0C_05_80045A7C = func_ovl0C_05_80044838(); func_ovl0C_05_80044818(&D_ovl0C_05_80045A70); func_ovl0C_05_80044840(D_ovl0C_05_80045A7C, D_ovl0C_05_80045A60)

/* .bss */
u8 D_ovl0C_05_80045A60[0x10];
Vec3f D_ovl0C_05_80045A70;
s32 D_ovl0C_05_80045A7C;
u8 D_ovl0C_05_80045A80[0x4]; /* unused (func_ovl0C_05_800442C8) */
s32 D_ovl0C_05_80045A84;
s32 D_ovl0C_05_80045A88;
u8 D_ovl0C_05_80045A8C[0x4]; /* unused (func_ovl0C_05_800442C8) */
Vec3f D_ovl0C_05_80045A90;
UnkStructA *D_ovl0C_05_80045A9C;
UnkStruct_ovl0C_05_80045AA0 D_ovl0C_05_80045AA0;

/* .data */
/* passed to func_ovl0C_05_80045510: three 12-byte records */
u32 D_ovl0C_05_80045950[][3] = {
    { 0x910002, 0xE, 4 },
    { 0x900000, 0xE, 4 },
    { 0x940003, 0xE, 4 },
};
/* two 12-byte records, each passed to func_ovl0C_05_800456B8 */
u32 D_ovl0C_05_80045974[][3] = {
    { 0, 5, 0x34F },
    { 1, 0x22, 0xE0 },
};
/* two records, each set up by func_ovl0C_05_8004364C */
UnkStruct_ovl0C_05_8004598C D_ovl0C_05_8004598C[] = {
    { NULL, -1, 0x2B6, 0, 0, -5, -0x400, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x2B7, -0x40, -0x400, 0, 0x400, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0C_05_80044308(void) {
}

static void func_ovl0C_05_80044300(void) {
}

static void func_ovl0C_05_800442F8(void) {
}

static void func_ovl0C_05_800442F0(void) {
}

static void func_ovl0C_05_800442E8(void) {
}

static void func_ovl0C_05_800442E0(void) {
}

static void func_ovl0C_05_800442D8(void) {
}

static void func_ovl0C_05_800442D0(void) {
}

void func_ovl0C_05_800442C8(void) {
    /* a fake: the reference keeps the two unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl0C_05_80045A80[0] = D_ovl0C_05_80045A8C[0];
    }
}

void func_ovl0C_05_800442B0(void) {
    D_ovl0C_05_80045A84 = -1;
    D_ovl0C_05_80045A88 = -1;
}

void func_ovl0C_05_80044254(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_05_80044E98(D_ovl0C_05_80045A90.x, D_ovl0C_05_80045A90.y, D_ovl0C_05_80045A90.z);
    func_ovl0C_05_80044EB8(arg0, arg1, arg2);
    func_ovl0C_05_800451C8(180);
}

void func_ovl0C_05_80044220(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_05_80045750(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_05_80044110(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_05_800451D0();
    func_ovl0C_05_80045750(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_05_80045080(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_05_80044038(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_05_800451F0();
    }
    func_ovl0C_05_80045070(obj);
    func_ovl0C_05_800451B8();
}

void func_ovl0C_05_80044038(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0C_05_80045350((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_05_80045350((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_05_80043FF4(UnkStructA *arg0) {
    func_ovl0C_05_80045060(arg0, 0x01000000);
    func_ovl0C_05_800451A8(func_ovl0C_05_80044110, arg0, 0, 0, 0x150);
}

void func_ovl0C_05_80043F34(UnkStructA *arg0) {
    func_ovl0C_05_800451C8(10);
    func_ovl0C_05_800446E0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_05_800451C8(60);
}

void func_ovl0C_05_80043EB0(void) {
    UnkStructA *obj;
    s32 alpha;
    s32 step;

    func_ovl0C_05_80044848(1);
    func_ovl0C_05_800451C8(10);
    obj = func_ovl0C_05_80044898(func_ovl0C_05_80044838());
    func_ovl0C_05_80045730(0x44);
    func_ovl0C_05_80045058(obj, 0x80000);
    step = 0x11;
    for (alpha = 0xFF; alpha > 0; alpha -= step) {
        obj->unk40->unk36 = alpha;
        func_ovl0C_05_800451F0();
    }
    obj->unk40->unk36 = 0;
    func_ovl0C_05_800451B8();
}

void func_ovl0C_05_80043CE4(UnkStructA *arg0) {
    s32 pad0[1]; /* unused: they put hit at sp+0x38 in a 0x40 frame */
    s32 hit;
    s32 pad1[1];
    f32 x;
    f32 y;
    f32 z;
    UnkStructA *other;
    s32 saved;
    s32 i;

    if (func_ovl0C_05_80045430(0x41A) == 0 && arg0->unk6C == 0.0f && arg0->unk68 == 0.0f) {
        x = arg0->unk40->unk10;
        y = arg0->unk40->unk14;
        z = arg0->unk40->unk18;
        func_ovl0C_05_800456A8(arg0, 0x40, 12.0f);
        hit = 0;
        if (arg0->unk8 & 3) {
            if (arg0->unk8 & 2) {
                for (i = 0; i < 5; i++) {
                    if (func_ovl0C_05_800448D8(i) == arg0) {
                        break;
                    }
                }
                if (i < 5) {
                    other = func_ovl0C_05_80044898(i);
                } else {
                    other = NULL;
                }
            } else {
                for (i = 0; i < 5; i++) {
                    if (func_ovl0C_05_80044898(i) == arg0) {
                        break;
                    }
                }
                if (i < 5) {
                    other = func_ovl0C_05_800448D8(i);
                } else {
                    other = NULL;
                }
            }
        } else {
            other = NULL;
        }
        saved = arg0->unkC;
        arg0->unkC = 0;
        if (other != NULL) {
            if (func_ovl0C_05_80045178(arg0, 0x10, other) != 0) {
                hit = 1;
            }
        } else if (func_ovl0C_05_80045008(arg0, 0x10, other) != 0) {
            hit = 1;
        }
        arg0->unkC = saved;
        if (hit) {
            arg0->unk40->unk10 = x;
            arg0->unk40->unk14 = y;
            arg0->unk40->unk18 = z;
        }
    }
}

void func_ovl0C_05_80043B18(UnkStructA *arg0) {
    s32 pad0[1]; /* unused: they put hit at sp+0x38 in a 0x40 frame */
    s32 hit;
    s32 pad1[1];
    f32 x;
    f32 y;
    f32 z;
    UnkStructA *other;
    s32 saved;
    s32 i;

    if (func_ovl0C_05_80045430(0x41A) == 0 && arg0->unk6C == 0.0f && arg0->unk68 == 0.0f) {
        x = arg0->unk40->unk10;
        y = arg0->unk40->unk14;
        z = arg0->unk40->unk18;
        func_ovl0C_05_800456A8(arg0, 0, 12.0f);
        hit = 0;
        if (arg0->unk8 & 3) {
            if (arg0->unk8 & 2) {
                for (i = 0; i < 5; i++) {
                    if (func_ovl0C_05_800448D8(i) == arg0) {
                        break;
                    }
                }
                if (i < 5) {
                    other = func_ovl0C_05_80044898(i);
                } else {
                    other = NULL;
                }
            } else {
                for (i = 0; i < 5; i++) {
                    if (func_ovl0C_05_80044898(i) == arg0) {
                        break;
                    }
                }
                if (i < 5) {
                    other = func_ovl0C_05_800448D8(i);
                } else {
                    other = NULL;
                }
            }
        } else {
            other = NULL;
        }
        saved = arg0->unkC;
        arg0->unkC = 0;
        if (other != NULL) {
            if (func_ovl0C_05_80045178(arg0, 0x10, other) != 0) {
                hit = 1;
            }
        } else if (func_ovl0C_05_80045008(arg0, 0x10, other) != 0) {
            hit = 1;
        }
        arg0->unkC = saved;
        if (hit) {
            arg0->unk40->unk10 = x;
            arg0->unk40->unk14 = y;
            arg0->unk40->unk18 = z;
        }
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0C_05_80043970(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0C_05_8004384C();
            break;
        case 17:
            func_ovl0C_05_80043600();
            break;
        case 18:
            func_ovl0C_05_800435A4();
            break;
        case 19:
            func_ovl0C_05_80043554();
            break;
        case 20:
            func_ovl0C_05_80043504();
            break;
        case 4:
            func_ovl0C_05_80043370();
            if (D_ovl0C_05_80045AA0.unk0 == 2) {
                func_ovl0C_05_800432D0();
            }
            break;
        case 5:
            if (D_ovl0C_05_80045AA0.unk0 == 2) {
                func_ovl0C_05_800431E0();
            }
            func_ovl0C_05_80044858(D_ovl0C_05_80045AA0.unk4, 3, 4.0f, D_ovl0C_05_80045AA0.unk10, 0, 1, 1);
            break;
        case 0x50:
            func_ovl0C_05_80043108();
            break;
        case 3:
            UNK_MACRO_ovl0C_05_800430B0();
            break;
        case 12:
            func_ovl0C_05_800448A0(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

/* 800437D4 and 80043814 are defined above their caller 8004384C: only then
 * does it pull them, after its statics (IDO -O3's order) */
void func_ovl0C_05_800437D4(void) {
    func_ovl0C_05_80045428(0x400);
    func_ovl0C_05_80045428(0x401);
    func_ovl0C_05_80045428(0x402);
    func_ovl0C_05_80045428(0x403);
    func_ovl0C_05_80045428(0x404);
}

void func_ovl0C_05_80043814(void) {
    func_ovl0C_05_800437D4();
    func_ovl0C_05_80044740(func_ovl0C_05_80043FF4);
    func_ovl0C_05_80044790(func_ovl0C_05_80043F34);
}

void func_ovl0C_05_8004384C(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0C_05_80043814();
    func_ovl0C_05_80045510(D_ovl0C_05_80045950);
    p = D_ovl0C_05_80045974;
    count = 2;
    for (i = 0; i < count; i++) {
        func_ovl0C_05_800456B8((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0C_05_80044658(0x246);
    func_ovl0C_05_80044670(0x250);
    func_ovl0C_05_80044808();
    func_ovl0C_05_80044738(func_ovl0C_05_80043CE4, 1);
    func_ovl0C_05_80044738(func_ovl0C_05_80043B18, 2);
    /* the empty static: its call puts 8004364C before 800437CC, and it is
     * the frame's 8 spare bytes */
    func_ovl0C_05_800437CC();
    func_ovl0C_05_8004364C(&D_ovl0C_05_8004598C[0]);
    func_ovl0C_05_8004364C(&D_ovl0C_05_8004598C[1]);
    if (func_ovl0C_05_80045430(0x41A) != 0) {
        func_ovl0C_05_80044DA8(D_ovl0C_05_8004598C[1].unk4);
        D_ovl0C_05_8004598C[1].unk4 = func_ovl0C_05_80044DA0(D_ovl0C_05_8004598C[1].unk0->unk40, 0, -10, -0x400,
                                                             D_ovl0C_05_8004598C[1].unk10, D_ovl0C_05_8004598C[1].unk12);
    }
}

static void func_ovl0C_05_800437CC(void) {
}

/* a static: IDO passes its argument in s0 */
static void func_ovl0C_05_8004364C(UnkStruct_ovl0C_05_8004598C *arg0) {
    arg0->unk0 = func_ovl0C_05_800450A0(arg0->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0C_05_80045058(arg0->unk0, 0x01080000);
    func_ovl0C_05_80045060(arg0->unk0, 0x02000000);
    if (arg0->unkC != -1 && arg0->unkE != -1 && arg0->unk10 != -1 && arg0->unk12 != -1) {
        arg0->unk4 = func_ovl0C_05_80044DA0(arg0->unk0->unk40, 0, arg0->unkC, arg0->unkE, arg0->unk10, arg0->unk12);
        if (arg0->unk4 == -1) {
            for (;;) {
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

void func_ovl0C_05_80043600(void) {
    func_ovl0C_05_80044810(1, 2, 0xF);
    func_ovl0C_05_800434DC(1, 0x40, 0x40, 0.0f, 1);
}

void func_ovl0C_05_800435A4(void) {
    func_ovl0C_05_80044810(9, 0, 0xF);
    func_ovl0C_05_800434DC(2, 0x40, 0x40, 0.0f, 2);
    func_ovl0C_05_800447E0(0x2C, 0x14);
}

void func_ovl0C_05_80043554(void) {
    func_ovl0C_05_80044810(0x16, 4, 3);
    func_ovl0C_05_800434DC(3, 0x80, 0x80, 0.0f, 2);
}

void func_ovl0C_05_80043504(void) {
    func_ovl0C_05_80044810(9, 0, 0xF);
    func_ovl0C_05_800434DC(4, 0x40, 0x40, 0.0f, 2);
}

void func_ovl0C_05_800434DC(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0C_05_80045AA0.unk0 = arg0;
    D_ovl0C_05_80045AA0.unk4 = arg1;
    D_ovl0C_05_80045AA0.unk8 = arg2;
    D_ovl0C_05_80045AA0.unkC = arg3;
    D_ovl0C_05_80045AA0.unk10 = arg4;
}

void func_ovl0C_05_800434A0(void) {
    func_ovl0C_05_80043370();
    if (D_ovl0C_05_80045AA0.unk0 == 2) {
        func_ovl0C_05_800432D0();
    }
}

void func_ovl0C_05_80043370(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_05_80044868();
    switch (D_ovl0C_05_80045AA0.unk8) {
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
        func_ovl0C_05_80044EB8(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_05_80045AA0.unkC;
        func_ovl0C_05_80044EC0(&sp1C, NULL, NULL);
        func_ovl0C_05_80044EB8(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_05_80044850(D_ovl0C_05_80045AA0.unk4);
    func_ovl0C_05_80044F50(45.0f, 45.1f);
}

void func_ovl0C_05_80043328(f32 arg0) {
    f32 sp1C;

    func_ovl0C_05_80044EC0(&sp1C, NULL, NULL);
    func_ovl0C_05_80044EB8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0C_05_800432D0(void) {
    D_ovl0C_05_80045A9C = func_ovl0C_05_80044898(func_ovl0C_05_80044838());
    func_ovl0C_05_80045058(D_ovl0C_05_80045A9C, 0x80000);
    D_ovl0C_05_80045A9C->unk40->unk36 = 0;
}

void func_ovl0C_05_8004326C(void) {
    if (D_ovl0C_05_80045AA0.unk0 == 2) {
        func_ovl0C_05_800431E0();
    }
    func_ovl0C_05_80044858(D_ovl0C_05_80045AA0.unk4, 3, 4.0f, D_ovl0C_05_80045AA0.unk10, 0, 1, 1);
}

void func_ovl0C_05_800431E0(void) {
    s32 alpha;
    s32 step;

    func_ovl0C_05_80044848(1);
    func_ovl0C_05_80045730(0x45);
    step = 0x11;
    for (alpha = 0; alpha < 0xFF; alpha += step) {
        D_ovl0C_05_80045A9C->unk40->unk36 = alpha;
        func_ovl0C_05_800451F0();
    }
    D_ovl0C_05_80045A9C->unk40->unk36 = 0xFF;
    func_ovl0C_05_80045060(D_ovl0C_05_80045A9C, 0x80000);
    func_ovl0C_05_80044848(0);
}

void func_ovl0C_05_80043198(void) {
    func_ovl0C_05_80044858(D_ovl0C_05_80045AA0.unk4, 3, 4.0f, D_ovl0C_05_80045AA0.unk10, 0, 1, 1);
}

void func_ovl0C_05_80043108(void) {
    func_ovl0C_05_800430F8();
    func_ovl0C_05_80043100();
    if (func_ovl0C_05_80044820(8, 0xF, 9, 0x10) != 0) {
        func_ovl0C_05_800451A8(func_ovl0C_05_80043EB0, 0, 0, 0, 0x130);
        func_ovl0C_05_800447F8(60);
        func_ovl0C_05_80044750(0x29, 0x15, 4);
    }
    if (func_ovl0C_05_80044820(0x16, 2, 0x17, 3) != 0) {
        func_ovl0C_05_80044750(0x29, 0x16, 0);
    }
}

static void func_ovl0C_05_80043100(void) {
}

static void func_ovl0C_05_800430F8(void) {
}

void func_ovl0C_05_800430B0(void) {
    UNK_MACRO_ovl0C_05_800430B0();
}

void func_ovl0C_05_80043068(void) {
    func_ovl0C_05_80043060();
    D_ovl0C_05_80045A7C = func_ovl0C_05_80044838();
    func_ovl0C_05_80044818(&D_ovl0C_05_80045A70);
    func_ovl0C_05_80044840(D_ovl0C_05_80045A7C, D_ovl0C_05_80045A60);
}

static void func_ovl0C_05_80043060(void) {
}

void func_ovl0C_05_80043040(void) {
    func_ovl0C_05_800448A0(1);
}

void func_ovl0C_05_80043020(void) {
    func_ovl0C_05_80043018();
    func_ovl0C_05_800448A0(1);
}

static void func_ovl0C_05_80043018(void) {
}

void func_ovl0C_05_80043010(void) {
}
