/*
 * NON_MATCHING: ovl_17_09's game object, complete but the furthest of these from
 * matching: several statics are inlined where the original calls them,
 * or the other way round.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 1340, eu 1340, jp 1340
 *
 * What still differs in us (words):
 * - func_ovl17_09_80043010 (97): two float stores the original makes in
 *   another order, and a call it makes inline; 13 words short.
 * - func_ovl17_09_80043290 (150): 2 words short (jump targets shift).
 * - func_ovl17_09_80043750 (649): the particle drawing: frame and register
 *   allocation differ throughout; 9 words short.
 * - func_ovl17_09_80044198 (170): frame 0x88, not 0x98, and a callee's
 *   frame 0x18, not 0x28; 15 words short.
 * - func_ovl17_09_80044828 (122), 800448A0 (116), 80044A2C (36): the
 *   original's 80044828 is 0x204 bytes (ours 0xA8: what it calls isn't
 *   inlined the same way), frames 0x40/0x60 against ours 0x58/0x70, and
 *   an argument kept on the stack in the original (sw a1,100(sp)) where
 *   ours moves it to $f12.
 */
#include "common.h"

/*
 * ovl_17_09's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_ovl17_09_Gfx; /* size 0x8 */

/* gbi.h's _SHIFTL */
#define _SHIFTL(v, s, w) ((u32) (((u32) (v) & ((0x01 << (w)) - 1)) << (s)))

/* one of the particles func_ovl17_09_80043750 draws (D_ovl17_09_800463D0) */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl17_09_800463D0; /* size 0x14 */

/* a model placed by func_ovl17_09_8004412C (D_ovl17_09_800462DC) */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl17_09_800462DC; /* size 0x10 */

/* what func_ovl17_09_80045658 returns: offsets into itself */
typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18[8];
    /* 0x20 */ s32 unk20;
} UnkStruct_ovl17_09_80046280;

/* what func_ovl17_09_800450D8 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl17_09_800450D8;

void func_ovl17_09_80044F88(s32);
void func_ovl17_09_80044F90(s32, f32, f32, f32, s32, s32);
void func_ovl17_09_80044FA0(s32);
void func_ovl17_09_80044FD0(s32, s32, s32, s32, s32, s32, s32);
void func_ovl17_09_80044FE0(f32, f32, f32, s32 *, s32);
f32 func_ovl17_09_80045048(UnkStructA_40 *);
void func_ovl17_09_80045068(void (*)(UnkStructA *), s32);
UnkStruct_ovl17_09_800450D8 *func_ovl17_09_800450D8(void);
void func_ovl17_09_80045100(s32);
UnkStructB *func_ovl17_09_80045108(void);
void func_ovl17_09_80045138(void);
UnkStructA *func_ovl17_09_800451C8(s32);
UnkStructA *func_ovl17_09_80045208(s32);
UnkStruct_ovl17_09_80046280 *func_ovl17_09_80045658(s32);
void func_ovl17_09_80045660(s32);
void func_ovl17_09_80045678(UnkStructA *);
s32 func_ovl17_09_800456D0(UnkStructA_40 *, s32, s32, s32, s32, s32);
UnkStructA *func_ovl17_09_800456E8(void (*)(s32, UnkStruct_ovl17_09_Gfx **), s32);
void func_ovl17_09_800457A8(s32);
void func_ovl17_09_800457B8(s32);
void func_ovl17_09_800457C8(f32, f32, f32);
void func_ovl17_09_800457E8(f32, f32, f32);
void func_ovl17_09_800457F0(f32 *, f32 *, f32 *);
void func_ovl17_09_80045830(s32);
void func_ovl17_09_800458D0(Vec3f *);
void func_ovl17_09_800458E0(f32 *);
s32 func_ovl17_09_80045938(UnkStructA *, s32);
void func_ovl17_09_800459A0(UnkStructA *);
UnkStructA *func_ovl17_09_800459A8(s32, s32, s32, s32, s32);
void func_ovl17_09_80045A68(f32);
void func_ovl17_09_80045A70(s32);
s32 func_ovl17_09_80045AA8(UnkStructA *, s32, UnkStructA *);
void func_ovl17_09_80045AD8(void (*)(void), void *, s32, s32, s32);
void func_ovl17_09_80045AF8(s32);
void func_ovl17_09_80045B20(void);
f32 func_ovl17_09_80045C80(f32);
f32 func_ovl17_09_80045C88(f32);
f64 func_ovl17_09_80045C90(void);
s32 func_ovl17_09_80045C98(s32);
void func_ovl17_09_80045D50(s32);
s32 func_ovl17_09_80045D60(s32);
void func_ovl17_09_80045DD8(s32, s32, s32, f32);
void func_ovl17_09_80045E28(s32, s32, s32);
void func_ovl17_09_80045E40(u32 (*)[3]);
void func_ovl17_09_80045F28(s32, f32, f32, f32, s32);
s32 func_ovl17_09_80045F80(UnkStructA *);
s32 func_ovl17_09_80045F88(UnkStructA *);
s32 func_ovl17_09_80045F90(s16);
void func_ovl17_09_80045F98(s16, s32);
void func_ovl17_09_80045FD8(UnkStructA *, s32, f32);
void func_ovl17_09_80046060(s32);
void func_ovl17_09_80046080(s32, f32, f32, f32);

void func_ovl17_09_80043010(void);
static void func_ovl17_09_80043144(UnkStruct_ovl17_09_800463D0 *);
static void func_ovl17_09_8004412C(UnkStruct_ovl17_09_800462DC *);
static s32 func_ovl17_09_80044504(UnkStructA *);
static void func_ovl17_09_8004456C(UnkStructA *, f32);
void func_ovl17_09_80043750(s32, UnkStruct_ovl17_09_Gfx **);
void func_ovl17_09_80044198(void);
void func_ovl17_09_80044828(UnkStructA *);
void func_ovl17_09_800448A0(UnkStructA *);
void func_ovl17_09_80044A2C(UnkStructA *);

/* .bss */
u8 D_ovl17_09_80046390[0x24];
s32 D_ovl17_09_800463B4;
s32 D_ovl17_09_800463B8;
u8 D_ovl17_09_800463BC[0x4];
Vec3f D_ovl17_09_800463C0;
u8 D_ovl17_09_800463CC[0x4];
UnkStruct_ovl17_09_800463D0 D_ovl17_09_800463D0[20];
Vec3f D_ovl17_09_80046560;
UnkStructA *D_ovl17_09_8004656C;
f32 D_ovl17_09_80046570;
f32 D_ovl17_09_80046574;

/* .data */
UnkStruct_ovl17_09_80046280 *D_ovl17_09_80046280 = NULL;
f32 D_ovl17_09_80046284 = 0.0f;
f32 D_ovl17_09_80046288 = 0.0f;
f32 D_ovl17_09_8004628C = 0.0f;
f32 D_ovl17_09_80046290 = 0.0f;
f32 D_ovl17_09_80046294 = 0.0f;
f32 D_ovl17_09_80046298 = 0.0f;
s32 D_ovl17_09_8004629C = 0x40;
s32 D_ovl17_09_800462A0 = 0;
f32 D_ovl17_09_800462A4 = 0.0f;
f32 D_ovl17_09_800462A8 = 0.0f;
f32 D_ovl17_09_800462AC = 0.0f;
f32 D_ovl17_09_800462B0 = 0.0f;
s32 D_ovl17_09_800462B4 = 1;
/* passed to func_ovl17_09_80045E40: three 12-byte records */
u32 D_ovl17_09_800462B8[][3] = {
    { 0xDA0000, 0x100018, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
UnkStruct_ovl17_09_800462DC D_ovl17_09_800462DC[2] = {
    { NULL, 420.0f, 2000.0f, 1800.0f },
    { NULL, 4200.0f, 2000.0f, 1800.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl17_09_80044C30(void) {
    D_ovl17_09_80046390[0] = D_ovl17_09_800463BC[0] + D_ovl17_09_800463CC[0];
}

static void func_ovl17_09_80044C28(void) {
}

static void func_ovl17_09_80044C20(void) {
}

static void func_ovl17_09_80044C18(void) {
}

static void func_ovl17_09_80044C10(void) {
}

static void func_ovl17_09_80044C08(void) {
}

static void func_ovl17_09_80044C00(void) {
}

static void func_ovl17_09_80044BF8(void) {
}

static void func_ovl17_09_80044BF0(void) {
}

static void func_ovl17_09_80044BE8(void) {
}

static void func_ovl17_09_80044BE0(void) {
}

static void func_ovl17_09_80044BD8(void) {
}

static void func_ovl17_09_80044BD0(void) {
}

static void func_ovl17_09_80044BC8(void) {
}

static void func_ovl17_09_80044BC0(void) {
}

static void func_ovl17_09_80044BB8(void) {
}

static void func_ovl17_09_80044BB0(void) {
}

static void func_ovl17_09_80044BA8(void) {
}

static void func_ovl17_09_80044BA0(void) {
}

static void func_ovl17_09_80044B98(void) {
}

static void func_ovl17_09_80044B90(void) {
}

static void func_ovl17_09_80044B88(void) {
}

void func_ovl17_09_80044B70(void) {
    D_ovl17_09_800463B4 = -1;
    D_ovl17_09_800463B8 = -1;
}

void func_ovl17_09_80044B14(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl17_09_800457C8(D_ovl17_09_800463C0.x, D_ovl17_09_800463C0.y, D_ovl17_09_800463C0.z);
    func_ovl17_09_800457E8(arg0, arg1, arg2);
    func_ovl17_09_80045AF8(180);
}

void func_ovl17_09_80044ACC(f32 arg0) {
    f32 sp1C;

    func_ovl17_09_800457F0(&sp1C, NULL, NULL);
    func_ovl17_09_800457E8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl17_09_80044A98(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl17_09_80046080(arg0, p->unk10, p->unk14, p->unk18);
}

static s32 func_ovl17_09_80044504(UnkStructA *obj) {
    s32 idx;
    s32 i;

    idx = -1;
    for (i = 0; i < 4; i++) {
        if (func_ovl17_09_800451C8(i) == obj) {
            idx = i;
            break;
        }
    }
    return idx;
}

static void func_ovl17_09_8004454C(UnkStructA *obj, f32 speed) {
    obj->unk40->unk10 -= speed;
}

static void func_ovl17_09_80044554(UnkStructA *obj, f32 speed) {
    obj->unk40->unk18 += speed;
}

static void func_ovl17_09_8004455C(UnkStructA *obj, f32 speed) {
    obj->unk40->unk10 += speed;
}

static void func_ovl17_09_80044564(UnkStructA *obj, f32 speed) {
    obj->unk40->unk18 -= speed;
}

static void func_ovl17_09_8004456C(UnkStructA *obj, f32 speed) {
    Vec3f pos;
    s32 dir;
    s32 saved;
    s32 hit;
    UnkStructA *other;
    s32 k;

    pos.x = obj->unk40->unk10;
    pos.y = obj->unk40->unk14;
    pos.z = obj->unk40->unk18;
    dir = D_ovl17_09_8004629C;
    if (func_ovl17_09_80045048(obj->unk40) == obj->unk40->unk14) {
        func_ovl17_09_80045FD8(obj, dir, speed);
    } else {
        switch (dir) {
            case 0x00:
                func_ovl17_09_80044564(obj, speed);
                break;
            case 0x20:
                func_ovl17_09_8004455C(obj, speed);
                func_ovl17_09_80044564(obj, speed);
                break;
            case 0x40:
                func_ovl17_09_8004455C(obj, speed);
                break;
            case 0x60:
                func_ovl17_09_80044554(obj, speed);
                func_ovl17_09_8004455C(obj, speed);
                break;
            case 0x80:
                func_ovl17_09_80044554(obj, speed);
                break;
            case 0xA0:
                func_ovl17_09_80044554(obj, speed);
                func_ovl17_09_8004454C(obj, speed);
                break;
            case 0xC0:
                func_ovl17_09_8004454C(obj, speed);
                break;
            case 0xE0:
                func_ovl17_09_80044564(obj, speed);
                func_ovl17_09_8004454C(obj, speed);
                break;
        }
    }
    saved = obj->unkC;
    hit = FALSE;
    other = NULL;
    obj->unkC = 0;
    if (obj->unk8 & 1) {
        other = func_ovl17_09_80045208(func_ovl17_09_80044504(obj));
    } else if (obj->unk8 & 2) {
        k = func_ovl17_09_80045F80(obj);
        if (func_ovl17_09_80045208(k) == obj) {
            other = func_ovl17_09_800451C8(k);
        }
    }
    if (other != NULL) {
        if (func_ovl17_09_80045AA8(obj, 0x10, other) != 0) {
            hit = TRUE;
        }
    } else {
        if (func_ovl17_09_80045938(obj, 0x10) != 0) {
            hit = TRUE;
        }
    }
    obj->unkC = saved;
    if (hit) {
        obj->unk40->unk10 = pos.x;
        obj->unk40->unk14 = pos.y;
        obj->unk40->unk18 = pos.z;
    }
}

void func_ovl17_09_80044A2C(UnkStructA *obj) {
    func_ovl17_09_8004456C(obj, D_ovl17_09_800462A4);
}

void func_ovl17_09_800448A0(UnkStructA *obj) {
    s32 idx;
    s16 k;

    func_ovl17_09_8004456C(obj, D_ovl17_09_800462A4 * 0.42857143f);
    if (obj->unk40->unk10 <= D_ovl17_09_80046570 || D_ovl17_09_80046574 <= obj->unk40->unk10 ||
        obj->unk40->unk14 < -10.0f) {
        func_ovl17_09_80045F28(0x10, obj->unk40->unk10, obj->unk40->unk14 + 150.0f, obj->unk40->unk18, 0);
        if (obj->unk8 & 1) {
            idx = func_ovl17_09_80044504(obj);
            if (idx != -1) {
                k = idx;
                if (func_ovl17_09_80045F90(k) != 0) {
                    func_ovl17_09_80045F98(k, 0);
                }
            }
        } else {
            idx = func_ovl17_09_80045F88(obj);
            if (idx != -1) {
                func_ovl17_09_80045F98(idx, 0);
            }
        }
        obj->unk40->unk14 = -700.0f;
        obj->unk5C = -700.0f;
    }
}

void func_ovl17_09_80044828(UnkStructA *obj) {
    func_ovl17_09_8004456C(obj, D_ovl17_09_800462A4 * 0.42857143f);
}

static void func_ovl17_09_8004412C(UnkStruct_ovl17_09_800462DC *rec) {
    rec->unk0 = func_ovl17_09_800459A8(0x269, -1, 0x01000000, 0xD0, 0);
    rec->unk0->unk40->unk10 = rec->unk4;
    rec->unk0->unk40->unk14 = rec->unk8;
    rec->unk0->unk40->unk18 = rec->unkC;
}

void func_ovl17_09_80044198(void) {
    UnkStructB *b;
    s32 i;
    s32 cell;
    s32 last0;
    s32 last1;

    b = func_ovl17_09_80045108();
    D_ovl17_09_800462DC[0].unk0 = NULL;
    D_ovl17_09_800462DC[1].unk0 = NULL;
    last0 = -1;
    last1 = -1;
    while (b->unk2C > 0) {
        func_ovl17_09_80045AF8(5);
    }
    D_ovl17_09_80046570 = 1410.0f;
    D_ovl17_09_80046574 = 3190.0f;
    func_ovl17_09_80045068(func_ovl17_09_800448A0, 6);
    func_ovl17_09_8004412C(&D_ovl17_09_800462DC[0]);
    func_ovl17_09_8004412C(&D_ovl17_09_800462DC[1]);
    func_ovl17_09_800456D0(D_ovl17_09_800462DC[0].unk0->unk40, 0, 0, 0x400, 0x20, 0x400);
    func_ovl17_09_800456D0(D_ovl17_09_800462DC[1].unk0->unk40, 0, 0, 0x400, 0x20, 0x400);
    D_ovl17_09_800462DC[0].unk0->unk40->unk30 = 6.0f;
    D_ovl17_09_800462DC[0].unk0->unk40->unk24 = -55.0f;
    D_ovl17_09_800462DC[1].unk0->unk40->unk30 = 6.0f;
    D_ovl17_09_800462DC[1].unk0->unk40->unk24 = 55.0f;
    D_ovl17_09_800462DC[1].unk0->unk40->unk20 = 180.0f;
    D_ovl17_09_800462DC[0].unk0->unk40->unk28 = 20.0f;
    D_ovl17_09_800462DC[1].unk0->unk40->unk28 = 20.0f;
    for (i = 0; i < 3600; i++) {
        D_ovl17_09_800462DC[0].unk0->unk40->unk10 += 0.21666667f;
        D_ovl17_09_800462DC[1].unk0->unk40->unk10 -= 0.21666667f;
        D_ovl17_09_80046570 += 0.23f;
        D_ovl17_09_80046574 -= 0.23f;
        func_ovl17_09_80044FE0(D_ovl17_09_80046570 - 100.0f, 0.0f, 1500.0f, &cell, 2);
        if (cell != last0) {
            last0 = cell;
            func_ovl17_09_80044FD0(cell, 0, 9, cell, 5, 0x15, 0x1800);
        }
        func_ovl17_09_80044FE0(D_ovl17_09_80046574 + 100.0f, 0.0f, 1500.0f, &cell, 2);
        if (cell != last1) {
            last1 = cell;
            func_ovl17_09_80044FD0(cell, 0, 9, cell, 5, 0x15, 0x1800);
        }
        func_ovl17_09_80045B20();
    }
    while (TRUE) {
        func_ovl17_09_80045AF8(100);
    }
}

static f32 func_ovl17_09_80043748(f32 v) {
    return v == 0.0f ? 0.0f : 1.0f;
}

void func_ovl17_09_80043750(s32 arg0, UnkStruct_ovl17_09_Gfx **arg1) {
    UnkStruct_ovl17_09_Gfx *gfx;
    UnkStruct_ovl17_09_800463D0 *p;
    f32 oldx;
    f32 oldz;
    f32 s;
    f32 c;
    f32 scale;
    f32 sign;
    f32 dx;
    f64 drift;
    s32 dsdx;
    s32 i;
    f32 view[8];

    gfx = *arg1;
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x00553048; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF279; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xBB000001; g->w1 = 0x80008000; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0x8000; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xFD100000; g->w1 = D_ovl17_09_80046280->unk20 + (u32) D_ovl17_09_80046280; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xE8000000; g->w1 = 0; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xF5000100; g->w1 = 0x07000000; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xF0000000; g->w1 = 0x0703C000; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xFD500000; g->w1 = D_ovl17_09_80046280->unk14 + (u32) D_ovl17_09_80046280; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xF5500000; g->w1 = 0x07000000; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xF3000000; g->w1 = 0x0703F800; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xF5400200; g->w1 = 0; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xF2000000; g->w1 = 0x0003C03C; }
    oldx = D_ovl17_09_80046560.x;
    oldz = D_ovl17_09_80046560.z;
    func_ovl17_09_800458D0(&D_ovl17_09_80046560);
    func_ovl17_09_800458E0(view);
    s = func_ovl17_09_80045C88(view[0]);
    c = func_ovl17_09_80045C80(view[0]);
    D_ovl17_09_80046284 = ((D_ovl17_09_80046560.x - oldx) * s - c * (D_ovl17_09_80046560.z - oldz)) * 0.5f;
    s = func_ovl17_09_80045C88(view[0]);
    c = func_ovl17_09_80045C80(view[0]);
    D_ovl17_09_80046288 = (c * (D_ovl17_09_80046560.x - oldx) + (D_ovl17_09_80046560.z - oldz) * s) * 0.2f;
    scale = 1500.0f / view[2];
    D_ovl17_09_80046284 *= scale;
    D_ovl17_09_80046288 *= scale;
    i = 0;
    if (func_ovl17_09_80045D60(0x407) == 0) {
        goto update;
    }
    do {
        p = &D_ovl17_09_800463D0[i];
        dsdx = 16.0f / (p->unk8 - 1.0f) * 1024.0f;
        {
            UnkStruct_ovl17_09_Gfx *g = gfx++;
            g->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL((u32) (p->unk0 + p->unk8 - 1.0f) << 2, 12, 12) | _SHIFTL((u32) (p->unk4 + p->unk8 - 1.0f) << 2, 0, 12);
            g->w1 = _SHIFTL(0, 24, 3) | _SHIFTL((u32) p->unk0 << 2, 12, 12) | _SHIFTL((u32) p->unk4 << 2, 0, 12);
        }
        { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xB4000000; g->w1 = 0; }
        { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xB3000000; g->w1 = _SHIFTL(dsdx, 16, 16) | _SHIFTL(dsdx, 0, 16); }
    update:
        if (D_ovl17_09_80046294 != 0.0f) {
            p = &D_ovl17_09_800463D0[i];
            s = func_ovl17_09_80045C88(D_ovl17_09_80046298);
            dx = -D_ovl17_09_80046284;
            p->unk0 += dx - (f32) func_ovl17_09_80045C90() * (dx * 0.25f) + D_ovl17_09_8004628C * s;
            sign = func_ovl17_09_80043748(D_ovl17_09_8004628C);
            if (func_ovl17_09_80045C80(D_ovl17_09_80046298) * (sign * D_ovl17_09_8004628C) + D_ovl17_09_80046290 < 0.0f) {
                sign = func_ovl17_09_80043748(D_ovl17_09_8004628C);
                drift = (func_ovl17_09_80045C80(D_ovl17_09_80046298) * (sign * D_ovl17_09_8004628C) + D_ovl17_09_80046290) * 0.5;
            } else {
                sign = func_ovl17_09_80043748(D_ovl17_09_8004628C);
                drift = func_ovl17_09_80045C80(D_ovl17_09_80046298) * (sign * D_ovl17_09_8004628C) + D_ovl17_09_80046290;
            }
            p->unk4 += (p->unkC - D_ovl17_09_80046288) - (f32) func_ovl17_09_80045C90() * ((p->unkC - D_ovl17_09_80046288) * 0.6f) + drift;
            p->unk8 -= 0.1f * (p->unk8 * 0.0625f);
            if (340.0f <= p->unk0 || 240.0f <= p->unk4 || p->unk8 <= 3.0f || p->unk10++ >= 240 || p->unk0 < -20.0f ||
                p->unk4 < -10.0f) {
                func_ovl17_09_80043144(p);
            }
        }
        i++;
    } while (i != 20);
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0x00080000; }
    { UnkStruct_ovl17_09_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0; }
    *arg1 = gfx;
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl17_09_80043290(s32 arg0) {
    s32 i;
    s32 t;
    f32 step;
    UnkStructB *b;

    switch (arg0) {
        case 2:
            func_ovl17_09_80045E40(D_ovl17_09_800462B8);
            func_ovl17_09_80044F88(0x217);
            func_ovl17_09_80044F90(0xDA, 0.0f, 0.0f, 0.0f, 0x50, 0);
            func_ovl17_09_80044FA0(0x221);
            func_ovl17_09_80045138();
            func_ovl17_09_80045100(0);
            func_ovl17_09_80045830(0x7F);
            func_ovl17_09_800457A8(1);
            func_ovl17_09_800457B8(1);
            func_ovl17_09_800457C8(2310.0f, 60.0f, 1400.0f);
            func_ovl17_09_800457E8(0.0f, 55.0f, 2864.0f);
            if (func_ovl17_09_800450D8()->unk10 == 0) {
                D_ovl17_09_800462A8 = 8.5f;
            } else {
                D_ovl17_09_800462A8 = 15.3f;
            }
            D_ovl17_09_800462A0 = 0;
            D_ovl17_09_800462B4 = 1;
            D_ovl17_09_800462A4 = 0.0f;
            func_ovl17_09_80045068(func_ovl17_09_80044A2C, 5);
            func_ovl17_09_80045068(func_ovl17_09_80044828, 6);
            D_ovl17_09_80046280 = func_ovl17_09_80045658(0x258);
            D_ovl17_09_8004656C = func_ovl17_09_800456E8(func_ovl17_09_80043750, -60);
            D_ovl17_09_8004656C->unkC |= 0x210;
            for (i = 0; i < 20; i++) {
                func_ovl17_09_80043144(&D_ovl17_09_800463D0[i]);
                D_ovl17_09_800463D0[i].unk4 = func_ovl17_09_80045C98(240);
            }
            func_ovl17_09_800458D0(&D_ovl17_09_80046560);
            D_ovl17_09_8004628C = 0.0f;
            D_ovl17_09_80046290 = 0.0f;
            D_ovl17_09_80046294 = 1.0f;
            func_ovl17_09_80045D50(0x407);
            D_ovl17_09_800462AC = 0.0f;
            D_ovl17_09_800462B0 = 0.0f;
            func_ovl17_09_80043010();
            func_ovl17_09_80045E28(90, 140, 255);
            break;
        case 4:
            func_ovl17_09_80045A68(50.0f);
            func_ovl17_09_80045A70(40);
            break;
        case 5:
            b = func_ovl17_09_80045108();
            if (b->unk38 == 1 && b->unk0 == 0) {
                func_ovl17_09_80045AD8(func_ovl17_09_80044198, NULL, 0, 0, 0x110);
            }
            break;
        case 1:
            func_ovl17_09_80045678(D_ovl17_09_8004656C);
            func_ovl17_09_80045660(0x258);
            for (i = 0; i < 2; i++) {
                if (D_ovl17_09_800462DC[i].unk0 != NULL) {
                    func_ovl17_09_800459A0(D_ovl17_09_800462DC[i].unk0);
                    D_ovl17_09_800462DC[i].unk0 = NULL;
                }
            }
            func_ovl17_09_80045DD8(0, 0, 0, 0.0f);
            break;
        case 3:
            t = 0;
            if (++D_ovl17_09_800462A0 >= 720) {
                D_ovl17_09_800462A0 = 0;
            } else {
                t = D_ovl17_09_800462A0;
            }
            step = 0.0f;
            if (t >= 160) {
                if (t < 460) {
                    step = D_ovl17_09_800462A8 / 300.0f;
                } else if (t >= 540 && t < 720) {
                    step = -(D_ovl17_09_800462A8 / 180.0f);
                }
            }
            D_ovl17_09_800462A4 += step;
            if (2.0f <= D_ovl17_09_800462A4 && D_ovl17_09_800462B4 == 1) {
                D_ovl17_09_800462B4 = 0;
                func_ovl17_09_80046060(0x89);
            } else if (D_ovl17_09_800462A4 < 2.0f) {
                D_ovl17_09_800462B4 = 1;
            }
            D_ovl17_09_8004628C = D_ovl17_09_800462A4 * 0.5f;
            D_ovl17_09_80046290 = 0.0f;
            if (D_ovl17_09_800462A0 == 0) {
                func_ovl17_09_80043010();
            }
            break;
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

static void func_ovl17_09_80043144(UnkStruct_ovl17_09_800463D0 *p) {
    f32 r;
    f64 t;

    r = func_ovl17_09_80045C90();
    p->unk0 = func_ovl17_09_80045C90() * 370.0 - 50.0;
    t = func_ovl17_09_80045C90();
    p->unk4 = (D_ovl17_09_8004628C < 0.0f ? -D_ovl17_09_8004628C : D_ovl17_09_8004628C) * 30.0f * t;
    if (D_ovl17_09_80046288 <= 0.0f) {
        p->unk4 += (1.0f - r) * 40.0f;
    } else {
        p->unk4 += func_ovl17_09_80045C98(90);
    }
    p->unk10 = 0;
    p->unk8 = r * 12.0f + 4.0f;
    p->unkC = r * r * 5.0f + 0.5f;
}

void func_ovl17_09_80043010(void) {
    D_ovl17_09_8004629C = (func_ovl17_09_80045C98(8) << 5) & 0xF0;
    switch (D_ovl17_09_8004629C) {
        case 0x00:
            D_ovl17_09_80046298 = 270.0f;
            break;
        case 0x20:
            D_ovl17_09_80046298 = 315.0f;
            break;
        case 0x40:
            D_ovl17_09_80046298 = 0.0f;
            break;
        case 0x60:
            D_ovl17_09_80046298 = 45.0f;
            break;
        case 0x80:
            D_ovl17_09_80046298 = 90.0f;
            break;
        case 0xA0:
            D_ovl17_09_80046298 = 135.0f;
            break;
        case 0xC0:
            D_ovl17_09_80046298 = 180.0f;
            break;
        case 0xE0:
            D_ovl17_09_80046298 = 225.0f;
            break;
    }
}
