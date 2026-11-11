/*
 * NON_MATCHING: main_code's A4CE0, complete: the 16 effects at
 * 0x800BC528 (func_8028A5C4 starts one with its coroutine from
 * D_802A1C40, func_8028A4E0 stops one, func_8028A87C registers the
 * spawners) and the effect coroutines themselves. Every function and stub
 * is emitted in the original's order and at the original's size. Not
 * built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 0, eu 0, jp 0
 *
 * Every function matches (the statics are compared as one run from
 * func_8028A8A4).
 * - func_8028BD20's spawn loop: a fake "if (pos == (f32 *) (i * i) ||
 *   i == 5) {}" at the top of SPAWN1 (n is the loop counter). Without it
 *   kind (save 15) is coloured before i (10.3) and takes s2. The i * i
 *   lifts i to 17. The pos use keeps &pos above e, and the extra 5 keeps
 *   the loop bound above e, against the block the fake adds to the loop
 *   (each alone leaves e in s4 or s5). as1 deletes the fake's code.
 * - func_8028D094 declares d first: the order of the declarations sets
 *   m's frame slot (112, not 116).
 * - Tied float constants are coloured in the order they first appear in
 *   the loop: func_8028BD20's `t += 1.0f` comes after the unk24 update.
 * - The coroutines and table functions are referenced only from .data,
 *   so they are statics: the globals come out first (reversed), the
 *   statics after in source order.
 * - func_8028A9CC (the kill), func_8028AB0C (the scale) and func_8028A978
 *   (a debris spawn) are inlined everywhere and leave stubs. IDO inlines a
 *   static called from several places only if it holds at most one call:
 *   the kill is the four stores and func_8022FC90, each caller calling
 *   func_80239430 after it. func_8028B670 and func_8028BD20 write the kill
 *   out (the inlined static costs them 8 frame bytes). The spawn makes two
 *   calls, so SPAWN/SPAWN1 are macros with block locals, padded to the
 *   original's 40-byte areas, around an empty K&R stub. The `do {} while
 *   (0);` after func_8028A5C4 stands for the inlined static's exit label:
 *   uopt marks v0 used in the block after a call to a function returning
 *   a value, and the empty block takes that mark, so the code after the
 *   spawn may keep m->unk40 in v0 as the original does.
 * - func_8028AB14: the original keeps 1.0 in three registers (fs2 for the
 *   scale, fs3 for t, fs5 for e->unk10) and so doesn't hoist 255.0f.
 *   uopt keys a float constant by its spelling, so `1`, `1.0f` and `1.f`
 *   are three constants with one value.
 * - func_8028CC18: both 30s spelt alike (one constant, fs3), e->unk10's
 *   1.0 spelt apart from t's step, and a dead `if (t == 0.05f) {}` in the
 *   loop: the uses put 0.05 (fs1) and 0.1 (fs2) ahead of the tied 30.
 * - The static parameter orders (func_8028A9D4 (out, kind, e, mode),
 *   func_8028A5C4 (slot, kind, pos, arg4, arg3), func_8028AB14's scale
 *   before alpha, func_8028B670's dz before dx) come from which argument
 *   the callers set up first; `= 1` where the original keeps 1.0 apart
 *   from another 1.0f (int and float constants are separate to uopt).
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
/* SPAWN1's n is the caller's loop counter, for a fake (see the header) */
#define SPAWN1(n, k, x, y, z) { s32 kind; f32 px, py, pz; s32 pad[2]; f32 pos[3]; s32 pad2; if (pos == (f32 *) (n * n) || n == 5) {} func_8028A978(); kind = k; px = x; py = y; pz = z; pos[0] = px; pos[1] = py; pos[2] = pz; func_8028A5C4(func_8028A690(kind), kind, pos, 0, 1); do {} while (0); }
#define SPAWN(k, x, y, z) { s32 kind; f32 px, py, pz; s32 pad[3]; f32 pos[3]; func_8028A978(); kind = k; px = x; py = y; pz = z; pos[0] = px; pos[1] = py; pos[2] = pz; func_8028A5C4(func_8028A690(kind), kind, pos, 0, 1); do {} while (0); }

s32 func_8028A4E0(s32 arg0);
void func_8028A584(void);
static s32 func_8028A5C4(s32 slot, s32 kind, f32 *pos, s32 arg4, s32 arg3);
static s32 func_8028A690(s32 kind);
void func_8028A7CC(s32 kind, f32 *pos, s32 arg2);
void func_8028A81C(s32 kind, f32 x, f32 y, f32 z, s32 arg4);
void func_8028A87C(void);
void func_8028A8A4(void);
static void func_8028A978();
static void func_8028A980(UnkStructA *m, f32 d);
static void func_8028A9CC(UnkStruct_800BC528 *e);
static void func_8028A9D4(UnkStructA **out, s32 kind, UnkStruct_800BC528 *e, s32 mode);
static f32 func_8028AB04(s32 dir);
static void func_8028AB0C(UnkStructA *m, f32 s);
static void func_8028AB14(UnkStruct_800BC528 *e, s32 kind, s32 anim, f32 scale, f32 alpha, f32 duration);
static void func_8028AFCC(UnkStruct_800BC528 *e, f32 scale);
static void func_8028B2CC(UnkStruct_800BC528 *e, f32 grow);
static void func_8028B4DC(UnkStruct_800BC528 *e, f32 angle);
static void func_8028B670(UnkStruct_800BC528 *e, s32 kind, s32 mode, f32 scale, f32 dz, f32 dx);
static void func_8028BD20(UnkStruct_800BC528 *e, f32 speed1, f32 speed2, f32 rate, f32 scale);
static void func_8028C02C(UnkStruct_800BC528 *e, f32 scale);
static void func_8028C2B4(void);
static void func_8028C58C(void);
static void func_8028C8C8(void);
static void func_8028CC18(void);
static void func_8028CF38(void);
static void func_8028D024(void);
static void func_8028D094(void);
static void func_8028D2F0(void);
static void func_8028D3A0(void);
static void func_8028D450(void);
static void func_8028D4F4(void);
static void func_8028D598(void);
static void func_8028D634(void);
static void func_8028D714(void);
static void func_8028D7FC(void);
static void func_8028D8E4(void);
static void func_8028D9C8(void);
static void func_8028DAAC(void);
static void func_8028DB94(void);
static void func_8028DC7C(void);
static void func_8028DD2C(void);
static void func_8028DDDC(void);
static void func_8028DEC8(void);
static void func_8028DFAC(void);
static void func_8028E090(void);
static void func_8028E17C(void);
static void func_8028E25C(void);
static void func_8028E344(void);
static void func_8028E364(void);
static void func_8028E400(void);
static void func_8028E4A0(void);
static void func_8028E540(void);

void *D_802A1C40[] = {
    func_8028C2B4, func_8028C58C, func_8028C8C8, func_8028CC18, func_8028CF38, func_8028D024,
    func_8028D094, func_8028D2F0, func_8028D3A0, func_8028D450, func_8028D4F4, func_8028D598,
    func_8028D634, func_8028D714, func_8028D7FC, func_8028D8E4, func_8028D9C8, func_8028DAAC,
    func_8028DB94, func_8028DC7C, func_8028DD2C, func_8028DDDC, func_8028DEC8, func_8028DFAC,
    func_8028E090, func_8028E17C, func_8028E25C, func_8028E344, func_8028E344, func_8028E344,
    func_8028E344, func_8028E344, func_8028E344, func_8028E344, func_8028E344, func_8028E344,
    func_8028E344, func_8028E364, func_8028E400, func_8028E4A0, func_8028E540,
};

void func_8028A8A4(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_800BC528[i].unk0 = -1;
        D_800BC528[i].unk4 = -1;
        D_800BC528[i].unk8 = 0;
        D_800BC528[i].unkC = 0;
        D_800BC528[i].unk10 = 0.0f;
        D_800BC528[i].unk14 = 0.0f;
        D_800BC528[i].unk18 = 0.0f;
        D_800BC528[i].unk1C = 0;
        D_800BC528[i].unk20 = NULL;
    }
    D_800BC768 = 0;
    func_8028A87C();
}

void func_8028A87C(void) {
    static void *D_802A1CE4[] = { func_8028A81C, func_8028A7CC, func_8028A4E0, func_8028A584, NULL, NULL, NULL };

    func_80297D30(0x26, D_802A1CE4);
}

void func_8028A81C(s32 kind, f32 x, f32 y, f32 z, s32 arg4) {
    f32 pos[3];

    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    func_8028A5C4(func_8028A690(kind), kind, pos, arg4, 0);
}

void func_8028A7CC(s32 kind, f32 *pos, s32 arg2) {
    func_8028A5C4(func_8028A690(kind), kind, pos, arg2, 0);
}

void func_8028A584(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        func_8028A4E0(i);
    }
}

s32 func_8028A4E0(s32 arg0) {
    if (arg0 == -1) {
        return 0;
    }
    if (D_800BC528[arg0].unk0 == -1) {
        return 0;
    }
    D_800BC528[arg0].unk0 = -1;
    if (D_800BC528[arg0].unk20 != NULL) {
        func_8022FC90(D_800BC528[arg0].unk20);
        D_800BC528[arg0].unk20 = NULL;
    }
    if (D_800BC528[arg0].unk4 != -1) {
        func_80238EA8(D_800BC528[arg0].unk4);
        D_800BC528[arg0].unk4 = -1;
    }
    return 1;
}

static s32 func_8028A5C4(s32 slot, s32 kind, f32 *pos, s32 arg4, s32 arg3) {
    UnkStruct_800BC528 *e;

    if (slot == -1) {
        return -1;
    }
    if (slot >= 100) {
        slot -= 100;
        e = &D_800BC528[slot];
        e->unk0 = 2;
    } else {
        e = &D_800BC528[slot];
        e->unk0 = 1;
    }
    e->unk10 = pos[0];
    e->unk14 = pos[1];
    e->unk18 = pos[2];
    e->unk8 = arg3;
    e->unk1C = arg4;
    e->unkC = kind;
    e->unk4 = func_80238A10(D_802A1C40[kind], e, 0, 0, 0x150);
    return slot;
}

static s32 func_8028A690(s32 kind) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (D_800BC528[i].unk0 == -1) {
            if (kind == 0x13 || kind == 0x14 || kind == 0xD || kind == 0xE || kind == 0xC) {
                return i += 100;
            }
            return i;
        }
    }
    for (i = 0; i < 16; i++) {
        D_800BC768++;
        if (D_800BC768 >= 16) {
            D_800BC768 -= 16;
        }
        if (D_800BC528[D_800BC768].unk0 == 2) {
            func_8028A4E0(D_800BC768);
            if (kind == 0x13 || kind == 0x14 || kind == 0xD || kind == 0xE || kind == 0xC) {
                return D_800BC768 + 100;
            }
            return D_800BC768;
        }
    }
    return -1;
}

static void func_8028A978() {
}

static void func_8028A980(UnkStructA *m, f32 d) {
    m->unk40->unk28 += d;
    m->unk40->unk2C += d;
    m->unk40->unk30 += d;
}

static void func_8028A9CC(UnkStruct_800BC528 *e) {
    e->unk0 = -1;
    e->unk4 = -1;
    func_8022FC90(e->unk20);
    e->unk20 = NULL;
}

static void func_8028A9D4(UnkStructA **out, s32 kind, UnkStruct_800BC528 *e, s32 mode) {
    UnkStructA *m;

    if (mode == 0) {
        *out = func_80230E6C(kind, e->unk1C);
    } else if (mode == 1) {
        *out = m = func_80230CB4(kind, -1, 0, 0x20, e->unk1C);
        m->unk38 = 0.0f;
    }
    if (e->unk1C == 0) {
        func_80231408(*out, 0x03000000);
        (*out)->unk40->unk10 = e->unk10;
        (*out)->unk40->unk14 = e->unk14;
        (*out)->unk40->unk18 = e->unk18;
    } else {
        func_80231408(*out, 0x03200000);
        (*out)->unk4C = e->unk10;
        (*out)->unk50 = e->unk14;
        (*out)->unk54 = e->unk18;
    }
    (*out)->unk58 = e->unk10;
    (*out)->unk5C = e->unk14;
    (*out)->unk60 = e->unk18;
    e->unk20 = *out;
}

/* Inlined helpers (their stubs are the 8-byte returns after 8028A8A4/8028A980/8028A9D4). */

static f32 func_8028AB04(s32 dir) {
    switch (dir) {
        case 2:
            return 180.0f;
        case 3:
            return 135.0f;
        case 4:
            return 90.0f;
        case 5:
            return 45.0f;
        case 6:
            return 0.0f;
        case 7:
            return 315.0f;
        case 0:
            return 270.0f;
        case 1:
            return 225.0f;
        default:
            return 0.0f;
    }
}

static void func_8028AB0C(UnkStructA *m, f32 s) {
    m->unk40->unk28 = s;
    m->unk40->unk2C = s;
    m->unk40->unk30 = s;
}

static void func_8028AB14(UnkStruct_800BC528 *e, s32 kind, s32 anim, f32 scale, f32 alpha, f32 duration) {
    f32 t;
    s32 step;
    UnkStructA *m;

    step = 1;
    t = 0.0f;
    func_8028A9D4(&m, kind, e, 0);
    m->unk40->unkC |= 0x8000;
    func_80231408(m, 0x80000);
    func_8022984C(m->unk40, 1);
    func_802297B8(m->unk40, anim, 0, 0);
    func_8028AB0C(m, scale);
    e->unk10 = alpha / 100.0f;
    while (t < duration) {
        switch (kind) {
            case 0x114:
                if (t < 10.0f) {
                    func_8028A980(m, 0.1f);
                } else {
                    if (t < 20.0f) {
                        if (step == 1) {
                            step++;
                            func_8028AB0C(m, 1);
                            e->unk10 = 1.0f;
                            func_802297B8(m->unk40, anim, 0, 1);
                        }
                        e->unk10 += -0.02f;
                    } else {
                        e->unk10 += -0.15f;
                    }
                    func_8028A980(m, 0.06666667f);
                }
                break;
            case 0x123:
                if (t < 10.0f) {
                    if (t >= 7.0f) {
                        e->unk10 += -0.26f;
                    }
                    func_8028A980(m, 0.3f);
                } else {
                    if (t < 50.0f) {
                        if (step == 1) {
                            step++;
                            func_8028AB0C(m, 2.0f);
                            e->unk10 = 1.0f;
                            func_802297B8(m->unk40, anim, 0, 1);
                        }
                    } else if (t < 60.0f) {
                        e->unk10 += -0.098000005f;
                    } else {
                        t -= 1.f;
                    }
                    func_8028A980(m, 0.02f);
                }
                break;
            case 0x127:
                if (t < 8.0f) {
                    func_8028A980(m, 0.0625f);
                } else if (t < 14.0f) {
                    if (step == 1) {
                        step++;
                        func_802297B8(m->unk40, anim, 0, 1);
                    }
                    if (t >= 11.0f) {
                        e->unk10 += -0.16666666f;
                    }
                    func_8028A980(m, 0.14999999f);
                } else {
                    if (step == 2) {
                        step++;
                        func_802297B8(m->unk40, anim, 0, 2);
                    }
                    if (t >= 16.0f) {
                        e->unk10 += -0.24f;
                    }
                    func_8028A980(m, 0.075f);
                }
                break;
        }
        t += 1.f;
        m->unk40->unk36 = e->unk10 * 255.0f;
        func_80239094();
    }
    func_8028A9CC(e);
    func_80239430();
}

static void func_8028AFCC(UnkStruct_800BC528 *e, f32 scale) {
    f32 t;
    s32 step;
    UnkStructA *m;

    step = 1;
    t = 0.0f;
    func_8028A9D4(&m, 0x118, e, 0);
    m->unk40->unkC |= 0x8000;
    func_80231408(m, 0x80000);
    e->unk10 = 1.0f;
    func_8022984C(m->unk40, 1);
    func_802297B8(m->unk40, 0x119, 0, 0);
    func_8028AB0C(m, scale);
    while (t < 32.0f) {
        if (step == 1 && (s32) t >= 9) {
            func_8022979C(m->unk40, 0, 1);
            step++;
        } else if (step == 2 && (s32) t >= 17) {
            func_8022979C(m->unk40, 0, 2);
            step++;
        } else if (step == 3 && (s32) t >= 25) {
            func_8022979C(m->unk40, 0, 3);
            step++;
        }
        if (t < 17.0f) {
            func_8028A980(m, 0.02f);
        } else if (t < 24.0f) {
            func_8028A980(m, 0.02f);
            e->unk10 += -0.02857142857142857;
        } else if (t < 32.0f) {
            func_8028A980(m, 0.02f);
            e->unk10 += -0.075;
        }
        m->unk40->unk36 = e->unk10 * 255.0f;
        if (m->unk40->unk36 < 0) {
            m->unk40->unk36 = 0;
        }
        t += 1.2f;
        func_80239094();
    }
    func_8028A9CC(e);
    func_80239430();
}

static void func_8028B2CC(UnkStruct_800BC528 *e, f32 grow) {
    f32 t;
    UnkStructA *m;

    t = 0.0f;
    func_8028A9D4(&m, 0x11A, e, 1);
    m->unk40->unkC |= 0x8000;
    func_80231408(m, 0x0C080040);
    func_8022984C(m->unk40, 2);
    func_802297B8(m->unk40, 0x11B, 0, 0);
    func_802297B8(m->unk40, 0x11B, 1, 1);
    func_8028AB0C(m, 0.25f);
    e->unk10 = 1.0f;
    m->unk34 = 90.0f;
    while (t < 30.0f) {
        if (t < 10) {
            e->unk10 += -0.02f;
            func_8028A980(m, grow / 10.0f);
        } else {
            e->unk10 += -0.02f;
            func_8028A980(m, 0.02f);
        }
        m->unk40->unk36 = e->unk10 * 255.0f;
        if (m->unk40->unk36 < 0) {
            m->unk40->unk36 = 0;
        }
        func_80232DB4(m);
        func_80239094();
        t += 1.5f;
    }
    func_8028A9CC(e);
    func_80239430();
}

static void func_8028B4DC(UnkStruct_800BC528 *e, f32 angle) {
    f32 t;
    UnkStructA *m;

    t = 0.0f;
    func_8028A9D4(&m, 0x11C, e, 0);
    func_80231408(m, 0x80000);
    e->unk10 = 1;
    func_8028AB0C(m, 1.5f);
    m->unk40->unk20 = angle;
    while (1) {
        if (t < 60.0f) {
            e->unk10 += -0.005f;
            func_8028A980(m, -0.0050000004f);
            t += 1.0f;
        } else if (t < 120.0f) {
            e->unk10 += 0.005f;
            func_8028A980(m, 0.0050000004f);
            t += 1.0f;
        } else {
            t -= 120.0f;
        }
        m->unk40->unk36 = e->unk10 * 255.0f;
        func_80239094();
    }
}

/* Spawns a child effect of the same kind at (x, y, z) (inlined; its stub is at 8028A978). */

static void func_8028B670(UnkStruct_800BC528 *e, s32 kind, s32 mode, f32 scale, f32 dz, f32 dx) {
    UnkStructA *m;
    s32 step;
    f32 t;
    s32 dir;
    s32 pad;

    step = 1;
    t = 0.0f;
    dir = func_80234248(7);
    func_8028A9D4(&m, kind, e, 0);
    m->unk40->unkC |= 0x8000;
    func_80231408(m, 0x80000);
    e->unk10 = 1.0f;
    func_8028AB0C(m, scale);
    if (e->unk8 == 0) {
        if (mode == 1) {
            SPAWN(e->unkC, m->unk40->unk10 - dx, m->unk40->unk14, m->unk40->unk18 - dz);
            SPAWN(e->unkC, m->unk40->unk10 + dx, m->unk40->unk14, m->unk40->unk18 - dz);
            SPAWN(e->unkC, m->unk40->unk10 - dx, m->unk40->unk14, m->unk40->unk18 + dz);
            m->unk40->unk10 += dx;
            m->unk40->unk18 += dz;
        }
        if (mode == 2) {
            SPAWN(e->unkC, m->unk40->unk10 + dx, m->unk40->unk14 + 130.0f, m->unk40->unk18 - dz);
            SPAWN(e->unkC, m->unk40->unk10 - dx, m->unk40->unk14 + 260.0f, m->unk40->unk18 + dz);
        } else {
            m->unk40->unk10 -= dx;
            m->unk40->unk18 += dz * 0.5f;
        }
    }
    func_8022984C(m->unk40, 1);
    func_802297B8(m->unk40, kind + 1, 0, 0);
    if (mode == 1) {
        m->unk70 = 0.0f;
    }
    while (t < 24.0f) {
        if (step == 1 && (s32) t >= 2) {
            if (e->unk8 == 0 && mode == 0) {
                SPAWN(e->unkC, m->unk40->unk10 + dx * 2, m->unk40->unk14, m->unk40->unk18 - dz * 0.1f);
            }
            step++;
        } else if (step == 2 && (s32) t >= 4) {
            if (e->unk8 == 0 && mode == 0) {
                SPAWN(e->unkC, m->unk40->unk10 + dx * 0.9, m->unk40->unk14, m->unk40->unk18 - dz);
            }
            step++;
        } else if (step == 3 && (s32) t >= 9) {
            func_8022979C(m->unk40, 0, 1);
            step++;
        } else if (step == 4 && (s32) t >= 17) {
            func_8022979C(m->unk40, 0, 2);
            step++;
        }
        if (mode != 3) {
            func_8028A980(m, 0.05f);
        }
        if (t > 8.0f) {
            e->unk10 += -0.059375;
        }
        if (mode == 1) {
            func_80291944(m, dir << 5, 1.5f);
            func_8028A980(m, 0.02f);
        } else if (mode == 2 && t > 16.0f) {
            func_8028A980(m, 0.018f);
        }
        m->unk40->unk36 = e->unk10 * 255.0f;
        if (m->unk40->unk36 < 0) {
            m->unk40->unk36 = 0;
        }
        t += 1.0f;
        func_80239094();
    }
    e->unk0 = -1;
    e->unk4 = -1;
    func_8022FC90(e->unk20);
    e->unk20 = NULL;
    func_80239430();
}

/* 0..7 to an angle (inlined into 8028BD20; its stub is after 8028A9D4). */

static void func_8028BD20(UnkStruct_800BC528 *e, f32 speed1, f32 speed2, f32 rate, f32 scale) {
    s32 dir;
    s32 i;
    UnkStructA *m;
    f32 t;

    t = 0.0f;
    dir = func_80234248(7);
    func_8028A9D4(&m, 0x11F, e, 0);
    func_80231408(m, 0x80000);
    if (e->unk8 == 0) {
        for (i = 0; i < 5; i++) {
            SPAWN1(i, e->unkC, m->unk40->unk10, m->unk40->unk14, m->unk40->unk18);
        }
    }
    m->unk40->unk20 = func_8028AB04(dir) + 30.0f;
    m->unk70 = 1.6333334f * rate;
    m->unk68 = 20.0f;
    func_8028AB0C(m, scale);
    e->unk10 = 1;
    while (t < 30.0f) {
        if (t < 10.0f) {
            func_80291944(m, dir << 5, speed1);
        } else {
            if (t > 20.0f) {
                e->unk10 += -0.08f;
            }
            func_80291944(m, dir << 5, speed2);
        }
        m->unk40->unk1C += 5.0f;
        m->unk40->unk24 += 20;
        t += 1.0f;
        m->unk40->unk36 = e->unk10 * 255.0f;
        func_8023903C(1);
    }
    e->unk0 = -1;
    e->unk4 = -1;
    func_8022FC90(e->unk20);
    e->unk20 = NULL;
    func_80239430();
}

static void func_8028C02C(UnkStruct_800BC528 *e, f32 scale) {
    UnkStructA *m;
    f32 t;
    s32 step;

    step = 1;
    t = 0.0f;
    func_8028A9D4(&m, 0x120, e, 0);
    func_80231408(m, 0x80000);
    func_8022984C(m->unk40, 2);
    func_802297B8(m->unk40, 0x121, 0, 0);
    func_802297B8(m->unk40, 0x121, 1, 1);
    e->unk10 = 1.0f;
    func_8028AB0C(m, scale);
    while (t < 26.0f) {
        if (step == 1 && t >= 7.0f) {
            step++;
            func_802297B8(m->unk40, 0x121, 0, 2);
            func_802297B8(m->unk40, 0x121, 1, 3);
        } else if (step == 2 && t >= 14.0f) {
            step++;
            func_802297B8(m->unk40, 0x121, 0, 4);
            func_802297B8(m->unk40, 0x121, 1, 5);
        } else if (step == 3 && t >= 20.0f) {
            step++;
            func_802297B8(m->unk40, 0x121, 0, 6);
            func_802297B8(m->unk40, 0x121, 1, 7);
        }
        func_8028A980(m, 0.05f);
        if (t > 14.0f) {
            e->unk10 += -0.04166666666666667;
        }
        m->unk40->unk36 = e->unk10 * 255.0f;
        t += 1.0f;
        func_80239094();
    }
    func_8028A9CC(e);
    func_80239430();
}

static void func_8028C2B4(void) {
    UnkStruct_800BC528 *e;
    f32 t;
    UnkStructA *m;
    s32 step;

    step = 1;
    t = 0.0f;
    e = func_802391F0();
    func_8028A9D4(&m, 0x10C, e, 0);
    func_80231408(m, 0x80000);
    func_8022984C(m->unk40, 2);
    func_802297B8(m->unk40, 0x10D, 0, 0);
    func_802297B8(m->unk40, 0x10D, 1, 1);
    func_8028AB0C(m, 0.25f);
    e->unk10 = 1.0f;
    while (t < 20.0f) {
        if (t < 5.0f) {
            func_8028A980(m, 0.15f);
        } else if (step == 1) {
            step++;
            func_8028AB0C(m, 1.0f);
            func_802297B8(m->unk40, 0x10D, 0, 2);
            func_802297B8(m->unk40, 0x10D, 1, 3);
        } else {
            func_8028A980(m, 0.053333335f);
            if (t >= 10.0f) {
                e->unk10 += -0.05714285714285714;
            }
        }
        m->unk40->unk14 += 1;
        m->unk40->unk36 = e->unk10 * 255.0f;
        t += 1;
        func_80239094();
    }
    func_8028A9CC(e);
    func_80239430();
}

static void func_8028C58C(void) {
    UnkStruct_800BC528 *e;
    f32 t;
    UnkStructA *m;
    s32 step;

    step = 1;
    t = 0.0f;
    e = func_802391F0();
    func_8028A9D4(&m, 0x10E, e, 0);
    func_80231408(m, 0x80000);
    func_8022984C(m->unk40, 2);
    func_802297B8(m->unk40, 0x10F, 0, 0);
    func_802297B8(m->unk40, 0x10F, 1, 1);
    e->unk10 = 1.0f;
    while (t < 14.0f) {
        if (step == 1 && t > 2.0f) {
            step++;
            func_802297B8(m->unk40, 0x10F, 0, 2);
            func_802297B8(m->unk40, 0x10F, 1, 3);
        } else if (step == 2 && t > 5.0f) {
            step++;
            func_802297B8(m->unk40, 0x10F, 0, 4);
            func_802297B8(m->unk40, 0x10F, 1, 5);
            func_8028AB0C(m, 0.65f);
        } else if (step == 3 && t >= 11.0f) {
            step++;
            func_802297B8(m->unk40, 0x10F, 0, 6);
            func_802297B8(m->unk40, 0x10F, 1, 7);
        }
        if (t > 5.0f) {
            func_8028A980(m, 0.12f);
            if (t > 8.0f) {
                e->unk10 += -0.13333333333333333;
            }
        }
        m->unk40->unk36 = e->unk10 * 255.0f;
        t += 1.0f;
        func_80239094();
    }
    func_8028A9CC(e);
    func_80239430();
}

static void func_8028C8C8(void) {
    UnkStruct_800BC528 *e;
    f32 t;
    UnkStructA *m;
    s32 step;

    step = 1;
    t = 0.0f;
    e = func_802391F0();
    func_8028A9D4(&m, 0x110, e, 0);
    func_80231408(m, 0x80000);
    func_8022984C(m->unk40, 2);
    func_802297B8(m->unk40, 0x111, 0, 0);
    func_802297B8(m->unk40, 0x111, 1, 1);
    e->unk10 = 1;
    while (t < 20.0f) {
        if (t < 4.0f) {
            e->unk10 += -0.0125f;
        } else if (t < 8.0f) {
            m->unk40->unk28 -= 0.225f;
            m->unk40->unk2C += 0.375f;
            e->unk10 += -0.0125f;
        } else if (t < 12.0f) {
            if (step == 1) {
                step++;
                func_802297B8(m->unk40, 0x111, 0, 2);
                func_802297B8(m->unk40, 0x111, 1, 3);
                func_8028AB0C(m, 1.0f);
            }
            func_8028A980(m, 0.125f);
            e->unk10 += -0.05f;
        } else {
            if (step == 2) {
                step++;
                func_802297B8(m->unk40, 0x111, 0, 4);
                func_802297B8(m->unk40, 0x111, 1, 5);
            }
            func_8028A980(m, 0.125f);
            e->unk10 += -0.05f;
        }
        t += 1.0f;
        m->unk40->unk36 = e->unk10 * 255.0f;
        func_80239094();
    }
    func_8028A9CC(e);
    func_80239430();
}

static void func_8028CC18(void) {
    UnkStruct_800BC528 *e;
    f32 t;
    UnkStructA *m;
    s32 step;

    step = 1;
    t = 0.0f;
    e = func_802391F0();
    func_8028A9D4(&m, 0x112, e, 0);
    func_80231408(m, 0x80000);
    func_8022984C(m->unk40, 2);
    func_802297B8(m->unk40, 0x113, 0, 0);
    func_802297B8(m->unk40, 0x113, 1, 1);
    func_8028AB0C(m, 0.01f);
    e->unk10 = 1.f;
    while (t < 30.0f) {
        if (t == 0.05f) {}
        if (t < 20.0f) {
            if (step == 1) {
                step++;
            }
            func_8028A980(m, 0.075f);
        } else if (t < 25.0f) {
            if (step == 2) {
                step++;
                func_802297B8(m->unk40, 0x113, 0, 2);
                func_802297B8(m->unk40, 0x113, 1, 3);
            } else {
                e->unk10 += -0.02f;
            }
            func_8028A980(m, 0.05f);
        } else if (t < 30.0f) {
            if (step == 3) {
                step++;
                func_802297B8(m->unk40, 0x113, 0, 4);
                func_802297B8(m->unk40, 0x113, 1, 5);
            } else {
                e->unk10 += -0.1;
            }
            func_8028A980(m, 0.05f);
        }
        t += 1.0f;
        m->unk40->unk36 = e->unk10 * 255.0f;
        func_80239094();
    }
    func_8028A9CC(e);
    func_80239430();
}

static void func_8028CF38(void) {
    func_8028AB14(func_802391F0(), 0x114, 0x115, 0.5f, 100.0f, 25.0f);
}

static void func_8028D024(void) {
    UnkStructA *m;

    func_8028A9D4(&m, 0x116, func_802391F0(), 0);
    func_80231408(m, 0x0C000000);
    while (TRUE) {
        func_80239094();
    }
}

static void func_8028D094(void) {
    f32 d;
    UnkStructA *m;
    UnkStruct_800BC528 *e;
    f32 t;

    t = 0.0f;
    e = func_802391F0();
    func_8028A9D4(&m, 0x117, e, 0);
    func_80231408(m, 0x80000);
    e->unk10 = 1;
    func_8028AB0C(m, 0.25f);
    while (t < 72.0f) {
        d = func_80234434(7.5f * t) * 3.0f;
        m->unk40->unk10 += d;
        m->unk40->unk18 -= d * 0.5f;
        m->unk40->unk14 += 1.2f;
        if (t < 36.0f) {
            e->unk10 += -0.0055555557f;
        } else {
            e->unk10 += -0.019444443f;
        }
        func_8028A980(m, 0.010416667f);
        t += 1.0f;
        m->unk40->unk36 = e->unk10 * 255.0f;
        func_80239094();
    }
    func_8028A9CC(e);
    func_80239430();
}

static void func_8028D2F0(void) {
    func_8028AFCC(func_802391F0(), 2.0f);
}

static void func_8028D3A0(void) {
    func_8028AFCC(func_802391F0(), 4.0f);
}

static void func_8028D450(void) {
    func_8028B2CC(func_802391F0(), 0.8f);
}

static void func_8028D4F4(void) {
    func_8028B2CC(func_802391F0(), 1.6f);
}

static void func_8028D598(void) {
    func_8028B4DC(func_802391F0(), 0.0f);
}

static void func_8028D634(void) {
    func_8028B670(func_802391F0(), 0x11D, 1, 0.3f, 0.0f, 0.0f);
}

static void func_8028D714(void) {
    func_8028B670(func_802391F0(), 0x11D, 0, 0.7f, 90.0f, 40.0f);
}

static void func_8028D7FC(void) {
    func_8028B670(func_802391F0(), 0x11D, 0, 1.5f, 170.0f, 80.0f);
}

static void func_8028D8E4(void) {
    func_8028B670(func_802391F0(), 0x11D, 2, 2.3f, 30.0f, 30.0f);
}

static void func_8028D9C8(void) {
    func_8028B670(func_802391F0(), 0x11D, 1, 2.0f, 60.0f, 60.0f);
}

static void func_8028DAAC(void) {
    func_8028BD20(func_802391F0(), 18.0f, 5.0f, 0.6f, 1.7f);
}

static void func_8028DB94(void) {
    func_8028BD20(func_802391F0(), 15.0f, 3.0f, 0.8f, 1.3f);
}

static void func_8028DC7C(void) {
    func_8028C02C(func_802391F0(), 5.5f);
}

static void func_8028DD2C(void) {
    func_8028C02C(func_802391F0(), 2.0f);
}

static void func_8028DDDC(void) {
    func_8028AB14(func_802391F0(), 0x123, 0x124, 0.75f, 80.0f, 61.0f);
}

static void func_8028DEC8(void) {
    func_8028B670(func_802391F0(), 0x125, 1, 2.0f, 60.0f, 60.0f);
}

static void func_8028DFAC(void) {
    func_8028B670(func_802391F0(), 0x125, 2, 2.3f, 30.0f, 30.0f);
}

static void func_8028E090(void) {
    func_8028AB14(func_802391F0(), 0x127, 0x128, 0.3f, 100.0f, 14.0f);
}

static void func_8028E17C(void) {
    func_8028B670(func_802391F0(), 0x11D, 3, 1.0f, 0.0f, 0.0f);
}

static void func_8028E25C(void) {
    func_8028BD20(func_802391F0(), 20.0f, 8.0f, 0.6f, 5.0f);
}

static void func_8028E344(void) {
    func_80239430();
}

static void func_8028E364(void) {
    func_8028B4DC(func_802391F0(), 0.0f);
}

static void func_8028E400(void) {
    func_8028B4DC(func_802391F0(), 90.0f);
}

static void func_8028E4A0(void) {
    func_8028B4DC(func_802391F0(), 180.0f);
}

static void func_8028E540(void) {
    func_8028B4DC(func_802391F0(), 270.0f);
}
