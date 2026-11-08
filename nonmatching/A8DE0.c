/*
 * NON_MATCHING: main_code's A8DE0, complete: the 16 moving objects at
 * 0x800BC770 (their task func_8028E614, the spawn table D_802A1D00 that
 * func_8028E9B8 registers, and the two function tables D_802A1D08 and
 * D_802A1D30). Split from A4CE0 (text_objects.txt has the evidence).
 * Every function and stub is emitted in the original's order. Not built
 * into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 22, eu 22, jp 22
 *
 * func_8028E5E0, func_8028E8A4, func_8028E8E0, func_8028E97C and
 * func_8028E9B8 match; of the statics compared as one run from
 * func_8028E9E0 (16 words), all but four match:
 * - func_8028E6CC (6): the spill of the new id and the argument set-up
 *   around the jalr are scheduled differently.
 * - func_8028F428 (6): `li s4,40` and `move s3,zero` come out in the other
 *   order.
 * - func_8028F5E0 (5): where `sw a0,48(sp)` goes.
 * - func_8028EE78 (3) and func_8028EF58 (2): register choices.
 * D_802A1D08 and D_802A1D30 are defined after the functions so that the
 * function-local D_802A1D00 comes first in .data.
 */
#include "common.h"

/* An effect: a task (D_802A1C40[kind]) drawing one model (16 of them, D_800BC528). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ UnkStructA *unk20;
} UnkStruct_800BC528; /* size 0x24 */

/* An object moved by the D_802A1D08 functions (16 of them, D_800BC770). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ UnkStructA *unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} UnkStruct_800BC770; /* size 0x28 */

s32 func_8022979C(UnkStructA_40 *, s32, s32);
void func_802297B8(UnkStructA_40 *, s32, s32, s32);
s32 func_8022984C(UnkStructA_40 *, s32);
f32 func_80229D3C(UnkStructA_40 *, s32);
void func_8022FC90(UnkStructA *);
UnkStructA *func_80230CB4(s32, s32, s32, s32, s32);
UnkStructA *func_80230E6C(s32, s32);
UnkStructA *func_802311E8(UnkStructA *);
UnkStructA *func_80231274(s32, s32, s32, UnkStructA *);
void func_80231408(UnkStructA *, s32);
void func_80232DB4(UnkStructA *);
s32 func_80234248(s32);
f32 func_80234434(f32);
s32 func_80238A10(void *, void *, s32, s32, s32);
void func_80238EA8(s32);
void func_8023903C(s32);
void func_80239094(void);
void *func_802391F0(void);
void func_80239430(void);
f64 func_8025E63C(void);
s32 func_8026C51C(s32, f32, f32, f32);
s32 func_8026C630(s32, f32 *);
f32 func_8026E938(UnkStructA_40 *);
void func_80291944(UnkStructA *obj, s32 dir, f32 speed);
void func_80297D30(s32, void *);
s32 func_8029217C(UnkStructA *obj, s32 dir, f32 speed, s32 (*cb)(s32));

extern UnkStruct_800BC528 D_800BC528[16];
extern s32 D_800BC768;
extern s32 D_800BC76C;
extern UnkStruct_800BC770 D_800BC770[16];

/* a debris spawn, inlined everywhere with its own frame area (func_8028A978 is its empty stub) */
#define SPAWN(k, x, y, z) { f32 pos[3]; s32 kind; f32 px, py, pz; func_8028A978(); kind = k; px = x; py = y; pz = z; pos[0] = px; pos[1] = py; pos[2] = pz; func_8028A5C4(func_8028A690(kind), kind, pos, 0, 1); }

static s32 func_8028E5E0(s32 arg0);
static s32 func_8028E5EC(s32 arg0);
static void func_8028E614(void);
static void func_8028E6BC();
static s32 func_8028E6C4(void);
s32 func_8028E6CC(s32 kind, f32 *pos, s32 dir);
s32 func_8028E8A4(s32 kind, f32 x, f32 y, f32 z, s32 dir);
void func_8028E8E0(void);
void func_8028E97C(void);
void func_8028E9B8(void);
void func_8028E9E0(void);
static s32 func_8028EAD8(UnkStructA *m, s32 dir, f32 speed, s32 (*cb)(s32));
static s32 func_8028EB28(UnkStruct_800BC770 *o, f32 speed);
static s32 func_8028EB70(UnkStruct_800BC770 *o, s32 limit, f32 speed);
static void func_8028EC00(UnkStruct_800BC770 *o);
static void func_8028EC08(UnkStruct_800BC770 *o, f32 d);
static void func_8028ECB0(UnkStruct_800BC770 *o);
static void func_8028ED18(UnkStruct_800BC770 *o);
static void func_8028ED9C(UnkStruct_800BC770 *o);
static void func_8028EE0C(UnkStruct_800BC770 *o);
static void func_8028EE78(UnkStruct_800BC770 *o, f32 grow, f32 speed, s32 flag, s32 limit);
static void func_8028EF58(UnkStruct_800BC770 *o);
static void func_8028EFE4(UnkStruct_800BC770 *o);
static void func_8028F08C(UnkStruct_800BC770 *o);
static void func_8028F1F0(UnkStruct_800BC770 *o, f32 grow, s32 limit);
static void func_8028F320(UnkStruct_800BC770 *o);
static void func_8028F428(UnkStruct_800BC770 *o);
static void func_8028F55C(UnkStruct_800BC770 *o);
static void func_8028F5E0(UnkStruct_800BC770 *o);
static void func_8028F664(UnkStruct_800BC770 *o, s32 kind, s32 arg2, s32 arg3);
static void func_8028F66C(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
static void func_8028F67C(UnkStruct_800BC770 *o, s32 kind, s32 arg2, s32 arg3, f32 *pos);
static f32 func_8028F710(UnkStruct_800BC770 *o);
static void func_8028F7CC(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
static void func_8028F880(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
static void func_8028F8F8(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
static void func_8028F988(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
static void func_8028FA38(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
static void func_8028FB04(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
static void func_8028FB98(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
static void func_8028FC2C(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
static void func_8028FCE4(UnkStruct_800BC770 *o, s32 arg1, f32 *pos);
void func_8028A81C(s32 kind, f32 x, f32 y, f32 z, s32 arg4);

extern void (*D_802A1D08[])(UnkStruct_800BC770 *);
extern void (*D_802A1D30[])(UnkStruct_800BC770 *, s32, f32 *);

void func_8028E9E0(void) {
    s32 i;

    func_8028E9B8();
    for (i = 0; i < 16; i++) {
        D_800BC770[i].unk0 = -1;
        D_800BC770[i].unk4 = (UnkStructA *) -1;
        D_800BC770[i].unkC = 0;
        D_800BC770[i].unk10 = 0;
        D_800BC770[i].unk14 = 0;
        D_800BC770[i].unk18 = -1;
        D_800BC770[i].unk1C = 0.0f;
        D_800BC770[i].unk20 = 0.0f;
        D_800BC770[i].unk24 = 0.0f;
    }
    D_800BC76C = func_80238A10(func_8028E614, NULL, 0, 0, 0xF0);
}

void func_8028E9B8(void) {
    static void *D_802A1D00[] = { func_8028E8A4, func_8028E6CC };

    func_80297D30(0x2E, D_802A1D00);
}

void func_8028E97C(void) {
    func_8028E8E0();
    if (D_800BC76C != -1) {
        func_80238EA8(D_800BC76C);
    }
}

void func_8028E8E0(void) {
    s32 i;
    UnkStruct_800BC770 *o;

    for (i = 0; i < 16; i++) {
        if (D_800BC770[i].unk0 != -1) {
            o = &D_800BC770[D_800BC770[i].unk0];
            func_8022FC90(o->unk4);
            o->unk0 = -1;
        }
    }
}

s32 func_8028E8A4(s32 kind, f32 x, f32 y, f32 z, s32 dir) {
    f32 pos[3];

    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    return func_8028E6CC(kind, pos, dir);
}

s32 func_8028E6CC(s32 kind, f32 *pos, s32 dir) {
    s32 id;
    UnkStruct_800BC770 *o;

    id = func_8028E6C4();
    if (id == -1) {
        return -1;
    }
    D_800BC770[id].unk0 = id;
    func_8028E6BC();
    o = &D_800BC770[id];
    if (dir == 0) {
        o->unk14 = func_8025E63C() * 8.0 + 1.0;
    } else {
        o->unk14 = dir;
    }
    o->unkC = 0;
    o->unk10 = kind;
    D_802A1D30[kind](o, 0, pos);
    func_80231408(o->unk4, 0x01080000);
    o->unk4->unk40->unk10 = pos[0];
    o->unk4->unk40->unk14 = pos[1];
    o->unk4->unk40->unk18 = pos[2];
    o->unk4->unk58 = pos[0];
    o->unk4->unk5C = pos[1];
    o->unk4->unk60 = pos[2];
    return id;
}

static s32 func_8028E5E0(s32 arg0) {
    return 1;
}

static s32 func_8028E5EC(s32 arg0) {
    if ((arg0 & 0xF) == 0xF || (arg0 & 0x60)) {
        return 0;
    }
    return 1;
}

static void func_8028E614(void) {
    s32 i;

    while (TRUE) {
        for (i = 0; i < 16; i++) {
            if (D_800BC770[i].unk0 != -1) {
                D_802A1D08[D_800BC770[i].unk10](&D_800BC770[i]);
            }
        }
        func_80239094();
    }
}

/* Inlined into 8028E6CC (their stubs are before it). */

static void func_8028E6BC() {
}

static s32 func_8028E6C4(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (D_800BC770[i].unk0 == -1) {
            return i;
        }
    }
    return -1;
}

static s32 func_8028EAD8(UnkStructA *m, s32 dir, f32 speed, s32 (*cb)(s32)) {
    s32 ret;

    ret = func_8029217C(m, dir, speed, cb);
    m->unk58 = m->unk40->unk10;
    m->unk5C = m->unk40->unk14;
    m->unk60 = m->unk40->unk18;
    func_80232DB4(m);
    return ret;
}

static s32 func_8028EB28(UnkStruct_800BC770 *o, f32 speed) {
    if (o->unk14 != 0) {
        return func_8028EAD8(o->unk4, (o->unk14 - 1) << 5, speed, func_8028E5EC);
    }
    return 0;
}

static s32 func_8028EB70(UnkStruct_800BC770 *o, s32 limit, f32 speed) {
    f32 y;

    y = o->unk4->unk40->unk14;
    if (func_8028EB28(o, speed) || o->unk4->unk5C < o->unk4->unk40->unk14) {
        return 1;
    }
    o->unk4->unk40->unk14 = y;
    if (++o->unkC > limit) {
        return 1;
    }
    return 0;
}

static void func_8028EC00(UnkStruct_800BC770 *o) {
}

static void func_8028EC08(UnkStruct_800BC770 *o, f32 d) {
    UnkStructA_40_48_4 *a;

    if (o->unk4->unk40->unk48 != NULL) {
        a = o->unk4->unk40->unk48->unk4;
        a->unk4 += d;
        if (func_80229D3C(o->unk4->unk40, 0) <= (a = o->unk4->unk40->unk48->unk4)->unk4) {
            a->unk4 = 0.0f;
        }
    }
}

static void func_8028ECB0(UnkStruct_800BC770 *o) {
    if (o->unk18 != -1) {
        func_8028A81C(o->unk18, o->unk4->unk40->unk10, o->unk4->unk40->unk14 + 100.0f, o->unk4->unk40->unk18, 0);
        o->unk18 = -1;
    }
    func_8022FC90(o->unk4);
    o->unk0 = -1;
}

static void func_8028ED18(UnkStruct_800BC770 *o) {
    if (func_8028EB70(o, 100, 10.0f)) {
        func_8028ECB0(o);
    } else {
        func_8028EC08(o, 10.0f);
    }
}

static void func_8028ED9C(UnkStruct_800BC770 *o) {
    if (func_8028EB70(o, 100, 12.5f)) {
        func_8028ECB0(o);
    }
}

static void func_8028EE0C(UnkStruct_800BC770 *o) {
    o->unk4->unk40->unk10 = o->unk8->unk40->unk10;
    o->unk4->unk40->unk14 = o->unk8->unk40->unk14;
    o->unk4->unk40->unk18 = o->unk8->unk40->unk18;
    func_8028ECB0(o);
}

static void func_8028EE78(UnkStruct_800BC770 *o, f32 grow, f32 speed, s32 flag, s32 limit) {
    f32 y;

    y = o->unk8->unk40->unk14;
    o->unk4->unk40->unk30 += grow;
    func_80232DB4(o->unk8);
    if (func_8028EAD8(o->unk8, (o->unk14 - 1) << 5, speed * 100.0f / 2.0f,
                      flag ? func_8028E5EC : func_8028E5E0) && flag) {
        func_8028EE0C(o);
        return;
    }
    o->unk8->unk40->unk14 = y;
    if (++o->unkC > limit) {
        func_8028EE0C(o);
    }
}

static void func_8028EF58(UnkStruct_800BC770 *o) {
    func_8028EC08(o, 5.0f);
    func_8028EE78(o, 0.5f, 0.5f, 1, 15);
}

static void func_8028EFE4(UnkStruct_800BC770 *o) {
    if (func_8028EB28(o, 5.0f) || (o->unk4->unk6C == 0.0f && o->unk4->unk68 == 0.0f)) {
        func_8028ECB0(o);
        return;
    }
    if (++o->unkC > 100) {
        func_8028ECB0(o);
    }
}

static void func_8028F08C(UnkStruct_800BC770 *o) {
    if (func_8028EB28(o, 5.0f) || (o->unk4->unk6C == 0.0f && o->unk4->unk68 == 0.0f)) {
        func_8026C51C(0x175, o->unk4->unk40->unk10, o->unk4->unk40->unk14, o->unk4->unk40->unk18);
        func_8028ECB0(o);
        return;
    }
    if (o->unkC == 0) {
        o->unk4->unk40->unk1C = -50.0f;
    } else {
        o->unk4->unk40->unk1C += 2.0f;
        if (o->unk4->unk40->unk1C > 80.0f) {
            o->unk4->unk40->unk1C = 80.0f;
        }
    }
    if (++o->unkC > 100) {
        func_8026C51C(0x175, o->unk4->unk40->unk10, o->unk4->unk40->unk14, o->unk4->unk40->unk18);
        func_8028ECB0(o);
    }
}

static void func_8028F1F0(UnkStruct_800BC770 *o, f32 grow, s32 limit) {
    f32 floor;

    floor = func_8026E938(o->unk8->unk40);
    if (floor == 20000.0f) {
        floor = 0.0f;
    }
    o->unk4->unk40->unk2C += grow;
    o->unk8->unk40->unk14 -= grow * 100.0f * 0.2;
    func_80232DB4(o->unk8);
    if (o->unk8->unk40->unk14 <= floor || ++o->unkC > limit) {
        if (o->unk10 == 8) {
            func_8026C51C(0x175, o->unk4->unk40->unk10, o->unk4->unk40->unk14, o->unk4->unk40->unk18);
        }
        func_8028EE0C(o);
    }
}

static void func_8028F320(UnkStruct_800BC770 *o) {
    func_8028EC08(o, 5.0f);
    func_8028F1F0(o, 1.0f, 50);
    if (o->unkC < 5) {
        o->unk4->unk40->unk28 += 0.3f;
    } else if (o->unkC < 10) {
        o->unk4->unk40->unk28 -= 0.3f;
    } else if (o->unkC >= 20) {
        o->unk4->unk40->unk28 -= 0.03f;
    }
}

static void func_8028F428(UnkStruct_800BC770 *o) {
    if (o->unkC < 10) {
        func_8028EE78(o, 3.2f, 0.8f, 0, 40);
    } else if (o->unkC < 20) {
        func_8028EE78(o, 1.2f, 0.3f, 0, 40);
        o->unk4->unk40->unk28 += 0.14f;
    } else {
        func_8028EE78(o, 0.25f, 0.16666667f, 0, 40);
        o->unk4->unk40->unk28 -= 0.114999995f;
    }
}

static void func_8028F55C(UnkStruct_800BC770 *o) {
    if (o->unkC < 30) {
        o->unkC++;
        return;
    }
    func_8028EC08(o, 5.0f);
    func_8028F1F0(o, 1.0f, 80);
}

static void func_8028F5E0(UnkStruct_800BC770 *o) { if (func_8028EB70(o, 100, 10.0f)) {
        func_8028ECB0(o);
    } else {
        func_8028EC08(o, 10.0f);
    }
}

/* Inlined into the D_802A1D30 functions that make one model (its stub is before 8028F66C). */

static void func_8028F664(UnkStruct_800BC770 *o, s32 kind, s32 arg2, s32 arg3) {
    UnkStructA *m;

    m = func_80231274(kind, arg2, arg3, NULL);
    o->unk4 = m;
    m->unk38 = 0.0f;
}

static void func_8028F66C(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
}

static void func_8028F67C(UnkStruct_800BC770 *o, s32 kind, s32 arg2, s32 arg3, f32 *pos) {
    UnkStructA *m;

    o->unk4 = func_80230E6C(kind, 0);
    m = func_80231274(kind, arg2, arg3, o->unk4);
    o->unk8 = m;
    m->unk38 = 0.0f;
    o->unk8->unk40->unk10 = pos[0];
    o->unk8->unk40->unk14 = pos[1];
    o->unk8->unk40->unk18 = pos[2];
    o->unk8->unk5C = pos[1];
}

static f32 func_8028F710(UnkStruct_800BC770 *o) {
    switch (o->unk14) {
        case 1:
            return 180.0f;
        case 2:
            return 135.0f;
        case 3:
            return 90.0f;
        case 4:
            return 45.0f;
        case 5:
            return 0.0f;
        case 6:
            return 315.0f;
        case 7:
            return 270.0f;
        case 8:
            return 225.0f;
        default:
            return 0.0f;
    }
}

static void func_8028F7CC(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
    func_8028F664(o, 0x102, 0x100, 0x50);
    o->unk4->unk34 = 50;
    func_8028A81C(0xD, pos[0], pos[1] + 50.0f, pos[2], 0);
    o->unk4->unk40->unk20 = func_8028F710(o);
    o->unk18 = 0xC;
    func_8026C630(0x16C, pos);
}

static void func_8028F880(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
    func_8028F664(o, 0x103, 0x80, 0x40);
    func_8028A81C(0, pos[0], pos[1], pos[2], 0);
    o->unk18 = 0;
    func_8026C630(0x16C, pos);
}

static void func_8028F8F8(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
    func_8028F67C(o, 0x104, 0x80, 0x40, pos);
    o->unk4->unk40->unk20 = func_8028F710(o);
    o->unk18 = 7;
    func_8026C630(0x171, pos);
}

static void func_8028F988(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
    func_8028F664(o, 0x105, 0x1000, 0x60);
    o->unk4->unk70 = 0.8166667f;
    o->unk4->unk68 = 20.0f;
    o->unk4->unk40->unk20 = func_8028F710(o);
    func_80231408(func_802311E8(o->unk4), 0x03100000);
    o->unk18 = 0xD;
    func_8026C630(0x16E, pos);
}

static void func_8028FA38(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
    func_8028F664(o, 0x106, 0x80, 0x40);
    func_8028A81C(0xE, pos[0], pos[1], pos[2], 0);
    o->unk4->unk70 = 0.8166667f;
    o->unk4->unk68 = 20.0f;
    o->unk4->unk40->unk20 = func_8028F710(o);
    func_80231408(func_802311E8(o->unk4), 0x03100000);
    o->unk18 = 9;
    func_8026C630(0x16F, pos);
}

static void func_8028FB04(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
    func_8028F67C(o, 0x107, 0x80080, 0x40, pos);
    func_8028A81C(0, pos[0], pos[1], pos[2], 0);
    o->unk18 = 0;
    func_8026C630(0x16D, pos);
}

static void func_8028FB98(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
    func_8028F67C(o, 0x108, 0x80080, 0x40, pos);
    o->unk4->unk40->unk20 = func_8028F710(o);
    o->unk18 = -1;
    func_8026C630(0x16D, pos);
}

static void func_8028FC2C(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
    pos[1] += 20.0f;
    func_8028F67C(o, 0x109, 0x80, 0x40, pos);
    func_8028A81C(4, pos[0], pos[1] + 30.0f, pos[2], 0);
    o->unk18 = 9;
    func_8026C630(0x172, pos);
}

static void func_8028FCE4(UnkStruct_800BC770 *o, s32 arg1, f32 *pos) {
    func_8028F664(o, 0x10A, 0x100, 0x50);
    func_8028A81C(0, pos[0], pos[1], pos[2], 0);
    o->unk4->unk40->unk20 = func_8028F710(o);
    o->unk18 = 0;
    func_8026C630(0x170, pos);
}

void (*D_802A1D08[])(UnkStruct_800BC770 *) = {
    func_8028EC00, func_8028ED18, func_8028ED9C, func_8028EF58, func_8028EFE4,
    func_8028F08C, func_8028F320, func_8028F428, func_8028F55C, func_8028F5E0,
};
void (*D_802A1D30[])(UnkStruct_800BC770 *, s32, f32 *) = {
    func_8028F66C, func_8028F7CC, func_8028F880, func_8028F8F8, func_8028F988,
    func_8028FA38, func_8028FB04, func_8028FB98, func_8028FC2C, func_8028FCE4,
};
