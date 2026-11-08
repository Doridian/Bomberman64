/*
 * NON_MATCHING: main_code's AA580 ("move.c"), complete: an object's
 * movement over the tile grid (func_802909FC steps it and resolves the
 * walls, slopes and edges around it; func_80291944 turns it toward a
 * direction; func_8029217C does both; func_802921C4 registers the three).
 * Every function is emitted in the original's order. Not built into the
 * ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 254, eu 254, jp 254
 *
 * func_802921C4 and func_8029217C match; of the statics (compared as one
 * run from func_8028FD80, 402 words), func_8028FD88 matches. The inlined
 * static named func_8029085C is the one whose stub is there.
 * - func_8028FFA8 (static, two inlined halves): the original keeps branch
 *   A's values in s1/s3 and branch B's in s0/s3/s5 with b = 0 hoisted
 *   above the else; its locals sit at 0x7C/0x44 against our 0x8C/0x4C.
 *   One result variable returned once (rather than a return per branch)
 *   took it from 258 words to 87.
 * - func_80290498 (static): frame 0xA0 against the original's 0xA8.
 * - func_80290708 (static): reads an uninitialised dy at 0x18(sp), as
 *   the original does; register choices differ. Four inlined statics'
 *   stubs come before func_8029087C in the original, one in ours.
 * - func_802909FC: frame and slots match (the callback lives in the
 *   context at 0x30; pads in the locals). The direction index comes out
 *   in v0 in the original (a1 in ours: perhaps an inlined static's
 *   result, but a static with branches isn't inlined here); in the
 *   corner case the original doesn't fold r = 1 | 2 into 3; the spill of
 *   c is at 0x58 against our 0x54.
 * - func_80291944: the join after the sdir reload and the bc1f delay
 *   slots are scheduled differently, which moves every later branch.
 *
 * p2 (1701 -> 849 in every version; per function, jp allf: FFA8 51,
 * 90498 16, 90708 0 (matches), stubs 6, 09FC 246, 1944 359):
 * - 09FC: the quadrant result goes into dx (not i) for the FD88 call;
 *   the corner case builds r = 0; r |= 1 ...; r |= 2 (uopt's one-pass
 *   constant propagation keeps the ori/move unfolded), then res |= r.
 *   Removing the unused i makes it worse.
 * - 1944: "t1.unk8 - 1 == t2.unk8" forms for the e tests.
 * - 90490/90498: an empty static func_80290490(s32 c) called once
 *   (inlined: its stub, +8 frame bytes) and the slope test as an inline
 *   if-chain on (code & 0xF): 143 -> 16 words. pos[] declared before tmp.
 * - 90708 matches: switch (mode) for dy, "5 == c", and the result
 *   masked at assignment (t2 = func_8026D7D8(...) & 0xF).
 * - FFA8: passes code2 & 0xF into func_8028FFA8_b (IPA argument
 *   registers follow the callee's colouring), which switches on it.
 * Left: three stubs before 9087C (statics inlined into 9087C keep it
 * matching, so they could go there); 90498 keeps t in s6 where the
 * original has a1 spilled at 160(sp) (frame 152 vs 168); FFA8's frame
 * 168 vs 160 (v_A 140 vs 124; dropping flag gives 160 but costs);
 * 09FC's quadrant in a3 vs v0, obj in v0 vs v1, the 0.0f not shared in
 * f0, arg setup before the 90708 calls; 1944's fast path reloads sdir
 * and branches past the join's lwc1 f0 (perhaps uopt PRE).
 *
 * p3 (849 -> 472 in every version; jp allf: FFA8 51, 90498 16 plus its
 * 4-byte size, stubs 0, 09FC 225, 1944 0 (matches in all three)):
 * - Stubs: three K&R empty statics (static void f() {}, no frame cost)
 *   defined just before 9087C and called first thing in 09FC give the
 *   four stubs there; the static run is 0xC78 against 0xC7C, the last
 *   4 bytes being 90498's missing spill.
 * - 1944: a bare ";" (or do {} while (0);) after the if/else at the end
 *   of the first else arm makes a join block of its own, where the
 *   original reloads sdir: 359 -> 112. The e tests as
 *   "t1.unk8 - 1 == t2.unk8" / "t1.unk8 + 1 == t2.unk8" (same for unk0)
 *   then match the rest.
 * - 09FC: the quadrant goes into i, passed as func_8028FD88(&dirA, i ^ 0,
 *   1) (i * 1 also works; | 0, + 0, & ~0 and casts don't): the identity
 *   op drops the a1 precolour, so i takes v0 and obj v1 as in the
 *   original. 246 -> 225.
 * - 90498: the instrumented uopt shows t (lr 19) costing 3 in a1/t-regs
 *   and 0 in s6/s7/fp (firstUseCost 18.5 isn't charged for them in this
 *   o3opt static), so t takes s6 and no spill/frame bytes appear. Tried
 *   without effect: declaration order, wrapping t's call in 90490,
 *   ternary/split returns, extra blocks everywhere, a non-inlined 90490.
 * Left: 90498's t (the 4 bytes shift every later static, ~170 words by
 * position); 09FC's c slot (0x54 vs 0x58), the corner 0.0f in f0 and r in
 * a0 vs v1, arg order before the 90708 calls, the sw v0,300(sp) schedule;
 * FFA8 (not looked at this pass).
 *
 * p4 (472 -> 254 in every version; jp allf: FFA8 29, 90498 0 (matches),
 * stubs 0, 09FC 225, 1944 0; the static run is now 0xC7C as original):
 * - 90498: a volatile struct local (volatile struct { s32 a, b, c, d; }
 *   sv;) with "sv.c = t | 0;" right after "if (res != 0) {" and
 *   "t = sv.c;" at the join reproduces the caller-saved spill exactly
 *   (frame 168, slot 160(sp), t in a1). "| 0" stops copy propagation so
 *   the stored register is a1, not v0 (* 1, ^ 0, + 0 don't). A volatile
 *   scalar goes to the frame bottom and shifts the locals; an array
 *   element adds an addiu. 472 -> 371.
 * - Stubs: the three K&R stubs called right after func_8029087C(&ctx)
 *   (not first thing in 09FC) still emit before 9087C and stop shifting
 *   the run: 371 -> 276.
 * - FFA8's dispatcher as "(code & 0xF) == 7 || (code & 0xF) == 8 || ..."
 *   (no c variable) gives the const-first beq order; in half B
 *   "dir->unk8 != -b", "ABS(ctx->unk24) > ABS(ctx->unk1C)" (larger side
 *   first) set the load order and t-regs; in half A "u = ...;" before
 *   "fb = b;". 51 -> 29.
 * - uopt (p4/uo, instrumented): s-regs cost 0 in an eb70=1 static; the
 *   func_8026E338 call forbids a1/a2 for every lr live across it; an lr
 *   splits when save * n <= mincost. Without effect or worse: a
 *   4-param wrapper static (frame 168 but locals +16), the slope test
 *   as a static, a switch dispatcher (881), "(c = code & 0xF) == 7".
 * Left: FFA8's frame 168 vs 160 (v_A 140 vs 124, v_B 76 vs 68, flag
 * read at 184 vs 176), half A's float registers (orig fb f2, u f0, ab
 * f12, 50.0 temp f18, unk24 loaded early), half B's end (obj v1 vs v0,
 * mul.s f2,f16,f0 operand order twice); 09FC's 225 as listed under p3.
 */
#include "common.h"

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Vec3i;

/* What func_802909FC works on (its 0x118), handed to its statics. */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s32 (*unk30)(s32);
} UnkStruct_802909FC;

/* What func_8026E938 reads (UnkStructA_40's shape), 0x50 bytes. */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C[0x34];
} UnkStruct_80290498;

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ u8 unkC[0xC];
} UnkStruct_8026DCAC; /* size 0x18 */

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1[0xC33];
} UnkStruct_800B15D8; /* size 0xC34 */

extern UnkStruct_800B15D8 D_800B15D8[];

void func_80230914(UnkStructA *);
f32 func_80234408(f32);
f32 func_80234434(f32);
void func_80239094(void);
s32 func_8026D7D8(s32, s32, s32);
void func_8026DCAC(f32, f32, f32, UnkStruct_8026DCAC *, s32);
void func_8026E338(f32, f32, f32, f32 *, s32);
void func_8026E6E4(UnkStructA_40 *, f32 *, f32 *);
f32 func_8026E938(void *);
f32 func_8026EAF8(UnkStructA *);
s32 func_8026EE18(f32);
void func_80297D38(const char *, ...);

s32 func_802909FC(UnkStructA *obj, s32 (*cb)(s32));
void func_80291944(UnkStructA *obj, s32 dir, f32 speed);
void func_8029217C(UnkStructA *obj, s32 dir, f32 speed, s32 (*cb)(s32));

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

void *D_802A1D60[] = { func_8029217C, func_80291944, func_802909FC, NULL };

void func_802921C4(void) {
    func_80297D30(0x29, D_802A1D60);
}


static void func_8028FD80(s32 dir) {
    func_80297D38("move.c [Error] : move direction is inadequate 0x%02x\n", dir);
    for (;;) {
        func_80239094();
    }
}

static void func_8028FD88(Vec3i *out, s32 dir, s32 mode) {
    if (mode == 0) {
        switch (dir) {
            case 1:
                out->unk0 = 0;
                out->unk4 = 0;
                out->unk8 = 0;
                break;
            case 0x00:
                out->unk0 = 0;
                out->unk4 = 0;
                out->unk8 = -1;
                break;
            case 0x20:
                out->unk0 = 1;
                out->unk4 = 0;
                out->unk8 = -1;
                break;
            case 0x40:
                out->unk0 = 1;
                out->unk4 = 0;
                out->unk8 = 0;
                break;
            case 0x60:
                out->unk0 = 1;
                out->unk4 = 0;
                out->unk8 = 1;
                break;
            case 0x80:
                out->unk0 = 0;
                out->unk4 = 0;
                out->unk8 = 1;
                break;
            case 0xA0:
                out->unk0 = -1;
                out->unk4 = 0;
                out->unk8 = 1;
                break;
            case 0xC0:
                out->unk0 = -1;
                out->unk4 = 0;
                out->unk8 = 0;
                break;
            case 0xE0:
                out->unk0 = -1;
                out->unk4 = 0;
                out->unk8 = -1;
                break;
            default:
                func_8028FD80(dir);
                break;
        }
    } else if (mode == 1) {
        switch (dir) {
            case 0:
                out->unk0 = 0;
                out->unk4 = 0;
                out->unk8 = 0;
                break;
            case 1:
                out->unk8 = -1;
                out->unk0 = 0;
                out->unk4 = 0;
                break;
            case 2:
                out->unk8 = -1;
                out->unk0 = 1;
                out->unk4 = 0;
                break;
            case 3:
                out->unk0 = 1;
                out->unk4 = 0;
                out->unk8 = 0;
                break;
            case 4:
                out->unk0 = 1;
                out->unk4 = 0;
                out->unk8 = 1;
                break;
            case 5:
                out->unk0 = 0;
                out->unk4 = 0;
                out->unk8 = 1;
                break;
            case 6:
                out->unk0 = -1;
                out->unk4 = 0;
                out->unk8 = 1;
                break;
            case 7:
                out->unk0 = -1;
                out->unk4 = 0;
                out->unk8 = 0;
                break;
            case 8:
                out->unk0 = -1;
                out->unk8 = -1;
                out->unk4 = 0;
                break;
        }
    }
}

static s32 func_8028FFA8_a(UnkStruct_802909FC *ctx, s32 code) {
    Vec3i v;
    s32 a;
    s32 b;
    f32 u;
    f32 w;
    f32 ab;
    f32 fb;
    UnkStructA *obj;

    a = 0;
    b = 0;
    func_8028FD88(&v, ctx->unk28, 0);
    switch (code) {
        case 7:
            a = -1;
            b = -1;
            break;
        case 8:
            a = -1;
            b = 1;
            break;
        case 12:
            a = 1;
            b = -1;
            break;
        case 13:
            a = 1;
            b = 1;
            break;
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    u = ctx->unk1C - a * 50.0f;
    fb = b;
    obj = ctx->unk0;
    ab = a * b;
    w = -a * ((200.0f + fb * ((ctx->unk24 - fb * 50.0f) - ab * u)) * 0.5f) - u;
    ctx->unk4 = obj->unk58 + w;
    ctx->unkC = obj->unk60 + ab * w;
    return 0x13;
}

static s32 func_8028FFA8_b(UnkStruct_802909FC *ctx, Vec3i *dir, s32 code2, s32 flag) {
    Vec3i v;
    s32 a;
    s32 b;
    s32 res;
    f32 dx;
    f32 dz;
    f32 t;
    UnkStructA *obj;

    a = 0;
    b = 0;
    res = 0;
    func_8028FD88(&v, ctx->unk28, 0);
    switch (code2) {
        case 7:
            a = -1;
            b = -1;
            break;
        case 8:
            a = -1;
            b = 1;
            break;
        case 12:
            a = 1;
            b = -1;
            break;
        case 13:
            a = 1;
            b = 1;
            break;
    }
    if (a == 0 || b == 0) {
        return res;
    }
    if (flag == 0) {
        if (a == dir->unk0) {
            if (dir->unk8 != -b || !(ABS(ctx->unk24) > ABS(ctx->unk1C))) {
                res = 1;
            }
        } else if (dir->unk0 == -a && b == dir->unk8) {
            if (ABS(ctx->unk24) > ABS(ctx->unk1C)) {
                res = 1;
            }
        }
    } else {
        if (b == dir->unk8) {
            if (dir->unk0 != -a || !(ABS(ctx->unk1C) > ABS(ctx->unk24))) {
                res = 2;
            }
        } else if (dir->unk8 == -b && a == dir->unk0) {
            if (ABS(ctx->unk1C) > ABS(ctx->unk24)) {
                res = 2;
            }
        }
    }
    if (res == 0) {
        return res;
    }
    obj = ctx->unk0;
    dx = ctx->unk4 - obj->unk58;
    dz = ctx->unkC - obj->unk60;
    res = 0;
    if (v.unk0 == a) {
        t = a * dx;
        res = 1;
        ctx->unkC -= b * t * 0.70710677f;
        ctx->unk4 -= a * t * 0.29289323f;
    }
    if (v.unk8 == b) {
        t = b * dz;
        res |= 2;
        ctx->unk4 -= a * t * 0.70710677f;
        ctx->unkC -= b * t * 0.29289323f;
    }
    return res;
}

static s32 func_8028FFA8(s32 code, UnkStruct_802909FC *ctx, Vec3i *dir, s32 code2, s32 flag) {
    s32 res;

    if ((code & 0xF) == 7 || (code & 0xF) == 8 || (code & 0xF) == 12 || (code & 0xF) == 13) {
        res = func_8028FFA8_a(ctx, code & 0xF);
    } else {
        res = func_8028FFA8_b(ctx, dir, code2 & 0xF, flag);
    }
    return res;
}

static void func_80290490(s32 c) {
}

static s32 func_80290498(UnkStruct_802909FC *ctx, s32 dx, s32 dy, s32 dz, s32 code) {
    volatile struct { s32 a, b, c, d; } sv;
    f32 pos[3];
    UnkStruct_80290498 tmp;
    s32 t;
    s32 slope;
    s32 res;
    f32 h;

    func_80290490(code);
    t = func_8026D7D8(ctx->unk10 + dx, ctx->unk14 + dy, ctx->unk18 + dz);
    slope = 0;
    res = 0;
    if ((code & 0xF) == 3 || (code & 0xF) == 4 || (code & 0xF) == 5 || (code & 0xF) == 6) {
        slope = 1;
    }
    switch (t & 0xF) {
        case 3:
            if (!slope && dy != -1 && ((dz == 0 && dx != 0) || dz == -1)) {
                res = 1;
            }
            break;
        case 4:
            if (!slope && dy != -1 && ((dz == 0 && dx != 0) || dz == 1)) {
                res = 1;
            }
            break;
        case 5:
            if (!slope && dy != -1 && ((dx == 0 && dz != 0) || dx == -1)) {
                res = 1;
            }
            break;
        case 6:
            if (!slope && dy != -1 && ((dx == 0 && dz != 0) || dx == 1)) {
                res = 1;
            }
            break;
        case 7:
            if (dx == 1 || dz == 1) {
                res = 2;
            }
            break;
        case 8:
            if (dx == 1 || dz == -1) {
                res = 2;
            }
            break;
        case 12:
            if (dx == -1 || dz == 1) {
                res = 2;
            }
            break;
        case 13:
            if (dx == -1 || dz == -1) {
                res = 2;
            }
            break;
    }
    if (res != 0) {
        sv.c = t | 0;
        if (res == 1) {
            h = func_8026EAF8(ctx->unk0);
            func_8026E338(ctx->unk10 + dx, ctx->unk14 + dy, ctx->unk18 + dz, pos, 0);
            tmp.unk10 = pos[0];
            tmp.unk14 = pos[1];
            tmp.unk18 = pos[2];
            if (h <= func_8026E938(&tmp)) {
                res = 2;
            }
        }
        t = sv.c;
        if (res == 2) {
            t = (t & ~0xF) | 0xF;
        }
    }
    return t;
}

static s32 func_80290708(s32 mode, UnkStruct_802909FC *ctx, Vec3i *dir, Vec3i *dirB, s32 code) {
    s32 res;
    s32 dy;
    s32 t1;
    s32 t2;
    s32 c;

    res = 0;
    switch (mode) {
        case 0:
            dy = 0;
            break;
        case 2:
            dy = -1;
            break;
    }
    t1 = func_8026D7D8(ctx->unk10 + dir->unk0, ctx->unk14 + dy, ctx->unk18) & 0xF;
    t2 = func_8026D7D8(ctx->unk10, ctx->unk14 + dy, ctx->unk18 + dir->unk8) & 0xF;
    c = code & 0xF;
    if ((5 == c && dirB->unk0 != -1 && dir->unk0 == 1 && t1 != 5) ||
        (c == 6 && dirB->unk0 != 1 && dir->unk0 == -1 && t1 != 6)) {
        res = 1;
    }
    if ((c == 3 && dirB->unk8 != -1 && dir->unk8 == 1 && t2 != 3) ||
        (c == 4 && dirB->unk8 != 1 && dir->unk8 == -1 && t2 != 4)) {
        res |= 2;
    }
    return res;
}

static void func_80290864() {
}

static void func_8029086C() {
}

static void func_80290874() {
}

static void func_8029087C(UnkStruct_802909FC *ctx) {
    UnkStructA *obj = ctx->unk0;
    UnkStructA_40 *p = obj->unk40;

    if (obj->unk58 < p->unk10) {
        if (obj->unk60 < p->unk18) {
            ctx->unk28 = 0x60;
        } else if (p->unk18 < obj->unk60) {
            ctx->unk28 = 0x20;
        } else {
            ctx->unk28 = 0x40;
        }
        ctx->unk2C = ctx->unk0->unk40->unk10 - ctx->unk0->unk58;
    } else if (p->unk10 < obj->unk58) {
        if (obj->unk60 < p->unk18) {
            ctx->unk28 = 0xA0;
        } else if (p->unk18 < obj->unk60) {
            ctx->unk28 = 0xE0;
        } else {
            ctx->unk28 = 0xC0;
        }
        ctx->unk2C = ctx->unk0->unk58 - ctx->unk0->unk40->unk10;
    } else if (obj->unk60 < p->unk18) {
        ctx->unk28 = 0x80;
        ctx->unk2C = obj->unk40->unk18 - obj->unk60;
    } else if (p->unk18 < obj->unk60) {
        ctx->unk28 = 0;
        ctx->unk2C = obj->unk60 - obj->unk40->unk18;
    } else {
        ctx->unk28 = 1;
        ctx->unk2C = 0.0f;
    }
}

static void func_8029085C(UnkStruct_802909FC *ctx, f32 angle) {
    ctx->unk10 = (ctx->unk0->unk40->unk10 + 50.0f) * 0.01f;
    ctx->unk18 = (ctx->unk0->unk40->unk18 + 50.0f) * 0.01f;
    ctx->unk14 = func_8026EE18(ctx->unk8 + angle);
}

#define func_802909FC_slope(c) ((c) == 3 || (c) == 4 || (c) == 5 || (c) == 6)

s32 func_802909FC(UnkStructA *obj, s32 (*cb)(s32)) {
    s32 i;
    UnkStruct_802909FC ctx;
    f32 fx;
    f32 fz;
    f32 angle;
    f32 sdir;
    s32 r;
    s32 pad1;
    Vec3i dirA;
    UnkStructA_40 *p;
    s32 pad2[4];
    s32 code;
    s32 codeX;
    s32 codeZ;
    s32 codeXZ;
    s32 yx;
    s32 yz;
    s32 res;
    Vec3i dirB;
    s32 dx;
    s32 dz;
    s32 below;
    s32 pad3;
    s32 code2;
    s32 pad4[2];
    f32 save[3];
    f32 h1;
    f32 h2;
    s32 pad5;
    f32 a;
    f32 b;
    s32 pad7;
    s32 c;
    s32 pad6;

    ctx.unk0 = obj;
    ctx.unk4 = obj->unk40->unk10;
    ctx.unk8 = obj->unk40->unk14;
    ctx.unkC = obj->unk40->unk18;
    func_8029087C(&ctx);
    func_80290864();
    func_8029086C();
    func_80290874();
    ctx.unk30 = cb;
    angle = 0.0f;
    sdir = 0.0f;
    if (ctx.unk0->unk6C == 0.0f && ctx.unk0->unk68 == 0.0f) {
        func_8026E6E4(ctx.unk0->unk40, &angle, &sdir);
    }
    func_8029085C(&ctx, angle);
    ctx.unk1C = ctx.unk4 - (s32) (ctx.unk4 * 0.01f) * 100.0f;
    if (ctx.unk4 < -50.0f) {
        ctx.unk1C += 100.0f;
    }
    ctx.unk24 = ctx.unkC - (s32) (ctx.unkC * 0.01f) * 100.0f;
    if (ctx.unkC < -50.0f) {
        ctx.unk24 += 100.0f;
    }
    if (ctx.unk1C >= 50.0f) {
        ctx.unk1C -= 100.0f;
    }
    if (ctx.unk24 >= 50.0f) {
        ctx.unk24 -= 100.0f;
    }
    obj->unk40->unk10 = obj->unk58;
    obj->unk40->unk14 = obj->unk5C;
    obj->unk40->unk18 = obj->unk60;
    if (ctx.unk1C > 0.0f) {
        if (ctx.unk24 > 0.0f) {
            i = 4;
        } else if (ctx.unk24 < 0.0f) {
            i = 2;
        } else {
            i = 3;
        }
    } else if (ctx.unk1C < 0.0f) {
        if (ctx.unk24 > 0.0f) {
            i = 6;
        } else if (ctx.unk24 < 0.0f) {
            i = 8;
        } else {
            i = 7;
        }
    } else {
        if (ctx.unk24 > 0.0f) {
            i = 5;
        } else if (ctx.unk24 < 0.0f) {
            i = 1;
        } else {
            i = 0;
        }
    }
    func_8028FD88(&dirA, i  ^ 0, 1);
    code = func_8026D7D8(ctx.unk10, ctx.unk14, ctx.unk18);
    yx = 0;
    yz = 0;
    res = 0;
    below = 0;
    dx = dirA.unk0;
    dz = dirA.unk8;
    func_8028FD88(&dirB, ctx.unk28, 0);
    c = code & 0xF;
    if (func_802909FC_slope(c)) {
        r = func_80290708(0, &ctx, &dirA, &dirB, code);
        if (r & 1) {
            yx = 1;
        }
        if (r & 2) {
            yz = 1;
        }
    } else if (c == 0) {
        code2 = func_8026D7D8(ctx.unk10, ctx.unk14 - 1, ctx.unk18);
        if ((code2 & 0xF) == 3 || (code2 & 0xF) == 4 || (code2 & 0xF) == 5 || (code2 & 0xF) == 6) {
            if (ctx.unk0->unk68 == 0.0f && ctx.unk0->unk6C == 0.0f) {
                r = func_80290708(2, &ctx, &dirA, &dirB, code2);
                code = code2;
                if (!(r & 1)) {
                    yx = -1;
                }
                if (!(r & 2)) {
                    yz = -1;
                }
                below = 1;
                c = code & 0xF;
            }
        }
    }
    if (yx != -1 && yz != -1) {
        codeX = func_80290498(&ctx, dirA.unk0, yx, 0, code);
        codeZ = func_80290498(&ctx, 0, yz, dirA.unk8, code);
        codeXZ = func_80290498(&ctx, dirA.unk0, yx | yz, dirA.unk8, code);
    } else {
        if (below == 0) {
            if (yx == -1) {
                dx = dirB.unk0;
            }
            if (yz == -1) {
                dz = dirB.unk8;
            }
        } else {
            dz = dirA.unk8;
            dx = dirA.unk0;
        }
        codeX = func_80290498(&ctx, dx, yx, 0, code);
        codeZ = func_80290498(&ctx, 0, yz, dz, code);
        r = func_80290708(0, &ctx, &dirA, &dirB, code) != 0 ? 1 : 0;
        if (ctx.unk14 + r >= D_800B15D8[0].unk0) {
            r = D_800B15D8[0].unk0 - ctx.unk14 - 1;
        }
        codeXZ = func_80290498(&ctx, dx, r, dz, code);
    }
    if (yx == -1) {
        if (below == 0) {
            dx = dirB.unk0;
        } else {
            dx = dirA.unk0;
        }
    } else {
        dx = dirA.unk0;
    }
    if (yz == -1) {
        if (below == 0) {
            dz = dirB.unk8;
        } else {
            dz = dirA.unk8;
        }
    } else {
        dz = dirA.unk8;
    }
    if (dx != 0) {
        if (ctx.unk30(codeX) == 0) {
            if ((c == 5 || c == 6) && dx == dirA.unk0 && dx == -dirB.unk0) {
                res = 0x81;
            } else {
                res = 1;
                ctx.unk4 -= ctx.unk1C;
            }
        } else {
            res = func_8028FFA8(code, &ctx, &dirA, codeX, 0);
        }
    }
    if (dz != 0) {
        if (ctx.unk30(codeZ) == 0) {
            if ((c == 3 || c == 4) && dz == dirA.unk8 && dz == -dirB.unk8) {
                res |= 0x82;
            } else {
                res |= 2;
                ctx.unkC -= ctx.unk24;
            }
        } else {
            res |= func_8028FFA8(code, &ctx, &dirA, codeZ, 1) * 2;
        }
    }
    if (res == 0) {
        if (ctx.unk30(code) == 0) {
            res |= 0x13;
        } else if (ctx.unk30(codeXZ) == 0) {
            r = 0;
            if (ABS(ctx.unk24) <= ABS(ctx.unk1C)) {
                r |= 1;
                ctx.unkC -= ctx.unk24;
                
                if (dirB.unk0 == 0 && dirB.unk8 == dirA.unk8) {
                    r |= 2;
                    ctx.unk4 -= dirA.unk0 * 5.0f;
                }
            } else {
                r |= 4;
                ctx.unk4 -= ctx.unk1C;
                if (dirB.unk8 == 0 && dirB.unk0 == dirA.unk0) {
                    r |= 8;
                    ctx.unkC -= dirA.unk8 * 5.0f;
                }
            }
            res |= r;
            res |= 0x20;
        } else if (*(s32 *) ctx.unk0->unk44 == 0) {
            p = ctx.unk0->unk40;
            save[0] = p->unk10;
            save[1] = p->unk14;
            save[2] = p->unk18;
            p->unk10 = ctx.unk4;
            ctx.unk0->unk40->unk14 = ctx.unk8;
            ctx.unk0->unk40->unk18 = ctx.unkC;
            h1 = func_8026E938(ctx.unk0->unk40);
            ctx.unk0->unk40->unk10 = ctx.unk0->unk58;
            ctx.unk0->unk40->unk14 = ctx.unk0->unk5C;
            ctx.unk0->unk40->unk18 = ctx.unk0->unk60;
            h2 = func_8026E938(ctx.unk0->unk40);
            code2 = func_8026D7D8((ctx.unk0->unk40->unk10 + 50.0f) * 0.01f, func_8026EE18(ctx.unk8),
                                  (ctx.unk0->unk40->unk18 + 50.0f) * 0.01f);
            ctx.unk0->unk40->unk10 = save[0];
            ctx.unk0->unk40->unk14 = save[1];
            ctx.unk0->unk40->unk18 = save[2];
            if ((code2 & 0xF) == 1 && h2 == ctx.unk0->unk5C && h2 != h1 && c != 3 && c != 4 && c != 5 &&
                c != 6 && (func_8026D7D8(ctx.unk10, ctx.unk14 - 1, ctx.unk18) & 0xF) != 3 &&
                (func_8026D7D8(ctx.unk10, ctx.unk14 - 1, ctx.unk18) & 0xF) != 4 &&
                (func_8026D7D8(ctx.unk10, ctx.unk14 - 1, ctx.unk18) & 0xF) != 5 &&
                (func_8026D7D8(ctx.unk10, ctx.unk14 - 1, ctx.unk18) & 0xF) != 6) {
                if ((func_8026D7D8(ctx.unk10 + dirA.unk0, ctx.unk14, ctx.unk18) & 0xF) == 1) {
                    res |= 0x41;
                    ctx.unk4 -= ctx.unk1C;
                }
                if ((func_8026D7D8(ctx.unk10, ctx.unk14, ctx.unk18 + dirA.unk8) & 0xF) == 1) {
                    res |= 0x42;
                    ctx.unkC -= ctx.unk24;
                }
            }
        }
    }
    if (c == 0xF) {
        if (ctx.unk30(func_8026D7D8(ctx.unk10 + dirB.unk0, ctx.unk14, ctx.unk18 + dirB.unk8))) {
            res = 0x51;
            ctx.unk4 += dirB.unk0 * 100.0f;
            ctx.unkC += dirB.unk8 * 100.0f;
        } else if (ctx.unk30(func_8026D7D8(ctx.unk10 - dirB.unk0, ctx.unk14, ctx.unk18 - dirB.unk8))) {
            res = 0x52;
            ctx.unk4 -= dirB.unk0 * 100.0f;
            ctx.unkC -= dirB.unk8 * 100.0f;
        }
    }
    if (ctx.unk0->unk68 == 0.0f && ctx.unk0->unk70 * 2.0f == ctx.unk0->unk6C) {
        a = 0.0f;
        b = 0.0f;
        func_8026E6E4(ctx.unk0->unk40, &a, &b);
        if (a != 0.0f) {
            if ((b == 90.0f && dirA.unk0 == -1 && dirB.unk0 == -1) ||
                (b == 270.0f && dirA.unk0 == 1 && dirB.unk0 == 1) ||
                (b == 0.0f && dirA.unk8 == -1 && dirB.unk8 == -1) ||
                (b == 180.0f && dirA.unk8 == 1 && dirB.unk8 == 1)) {
                ctx.unk8 = func_8026EAF8(ctx.unk0);
                ctx.unk0->unk6C = 0.0f;
            }
        }
    }
    obj->unk40->unk10 = ctx.unk4;
    obj->unk40->unk14 = ctx.unk8;
    obj->unk40->unk18 = ctx.unkC;
    return res;
}

void func_80291944(UnkStructA *obj, s32 dir, f32 speed) {
    f32 angle;
    f32 sdir;
    Vec3i d;
    f32 sp;
    s32 pad;
    f32 y0;
    f32 a;
    f32 b;
    f32 a2;
    f32 b2;
    f32 c;
    f32 e;
    f32 h;
    s32 pad2;
    UnkStruct_8026DCAC t1;
    UnkStruct_8026DCAC t2;
    s32 pad3;
    UnkStruct_8026DCAC t4;
    UnkStruct_8026DCAC t3;
    f32 g;

    y0 = obj->unk40->unk14;
    func_8028FD88(&d, dir, 0);
    if (dir & 0x20) {
        speed *= 0.707;
    }
    func_8026E6E4(obj->unk40, &angle, &sdir);
    if (obj->unk6C == 0.0f) {
        sp = func_80234408(angle) * speed;
    } else {
        sp = speed;
    }
    if (angle == 0.0f) {
        obj->unk40->unk10 += d.unk0 * sp;
        obj->unk40->unk18 += d.unk8 * sp;
    } else {
        if ((sdir == 0.0f || sdir == 180.0f) &&
            (dir == 0x40 || dir == 0x20 || dir == 0x60 || dir == 0xC0 || dir == 0xE0 || dir == 0xA0)) {
            obj->unk40->unk10 += d.unk0 * speed;
        } else {
            obj->unk40->unk10 += d.unk0 * sp;
            if (obj->unk68 == 0.0f && obj->unk6C == 0.0f) {
                a = 0.0f;
                b = 0.0f;
                func_8026E6E4(obj->unk40, &a, &b);
                if (a != 0.0f) {
                    if (sdir == 0.0f) {
                        obj->unk40->unk14 -= d.unk8 * sp * func_80234434(angle);
                    } else if (sdir == 180.0f) {
                        obj->unk40->unk14 += d.unk8 * sp * func_80234434(angle);
                    }
                } else {
                    obj->unk40->unk14 = y0;
                }
            }
            ;
        }
        if ((sdir == 90.0f || sdir == 270.0f) &&
            (dir == 0 || dir == 0x20 || dir == 0xE0 || dir == 0x80 || dir == 0x60 || dir == 0xA0)) {
            obj->unk40->unk18 += d.unk8 * speed;
        } else {
            obj->unk40->unk18 += d.unk8 * sp;
            if (obj->unk68 == 0.0f && obj->unk6C == 0.0f) {
                a2 = 0.0f;
                b2 = 0.0f;
                func_8026E6E4(obj->unk40, &a2, &b2);
                if (a2 != 0.0f) {
                    if (sdir == 90.0f) {
                        obj->unk40->unk14 -= d.unk0 * sp * func_80234434(angle);
                    } else if (sdir == 270.0f) {
                        obj->unk40->unk14 += d.unk0 * sp * func_80234434(angle);
                    }
                } else {
                    obj->unk40->unk14 = y0;
                }
            }
        }
    }
    c = 0.0f;
    e = 0.0f;
    func_8026E6E4(obj->unk40, &c, &e);
    if (obj->unk68 == 0.0f && obj->unk6C == 0.0f) {
        if (angle != 0.0f) {
            obj->unk40->unk14 = func_8026EAF8(obj);
            if (c != 0.0f) {
                h = func_8026E938(obj->unk40);
                if (h != 20000.0f && obj->unk40->unk14 <= h + 100.0f) {
                    obj->unk40->unk14 = h;
                }
            } else {
                h = func_8026E938(obj->unk40);
                if (h != 20000.0f && obj->unk40->unk14 <= obj->unk5C && obj->unk40->unk14 < h + 8.0f) {
                    obj->unk40->unk14 = h;
                }
            }
        } else if (angle == 0.0f && c != 0.0f) {
            func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, &t1, 2);
            func_8026DCAC(obj->unk58, obj->unk5C, obj->unk60, &t2, 2);
            if ((e == 0.0f && (t1.unk8 - 1 == t2.unk8 || dir == 0x80)) ||
                (e == 90.0f && (t1.unk0 - 1 == t2.unk0 || dir == 0x40)) ||
                (e == 180.0f && (t1.unk8 + 1 == t2.unk8 || dir == 0)) ||
                (e == 270.0f && (t1.unk0 + 1 == t2.unk0 || dir == 0xC0))) {
                obj->unk40->unk14 = func_8026EAF8(obj);
                h = func_8026E938(obj->unk40);
                if (h != 20000.0f && obj->unk40->unk14 <= h + 100.0f) {
                    obj->unk40->unk14 = h;
                }
            }
        }
    } else if (obj->unk6C != 0.0f && angle != 0.0f) {
        g = func_8026EAF8(obj);
        func_8026DCAC(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, &t3, 2);
        func_8026DCAC(obj->unk58, obj->unk5C, obj->unk60, &t4, 2);
        if (t4.unk0 != t3.unk0 || t4.unk8 != t3.unk8) {
            if (obj->unk40->unk14 < g) {
                obj->unk40->unk14 = g;
            }
        }
    }
}

void func_8029217C(UnkStructA *obj, s32 dir, f32 speed, s32 (*cb)(s32)) {
    func_80291944(obj, dir, speed);
    func_80230914(obj);
    func_802909FC(obj, cb);
}

static void func_802921EC(void) {
}
