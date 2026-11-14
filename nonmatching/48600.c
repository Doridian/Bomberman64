/*
 * NON_MATCHING: main_code's 48600, complete: 86 functions (us
 * 0x8022DE00-0x80233644) around three lists of 0x80-byte objects
 * (UnkStructA80: D_802A5578, D_802A55F8 and D_802A5678 head them, the 128
 * in D_800A3F00) and their collision shapes (spheres, cylinders and
 * boxes, func_8022E884). Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts"). src/48300.c, before it, is another object:
 * func_80232E60 calls its func_8022DB00 with a jal (text_objects.txt).
 * flags: -O3
 * differing words: us 11, eu 11, jp 11
 *
 * Functions in the reverse of the ROM's order, which IDO emits exactly
 * as the original does. An 8-byte stub (jr ra; nop) is an inlined
 * static, at its place in the source: the stubs at 0x8022E0A4-0x8022E87C
 * are func_8022E884's cases, func_8022FC18 is func_8022FC90's child
 * search and func_80232FF0 is func_80232FF8's D_802A5804 switch.
 * 67 of 68 global blocks match. What is understood:
 *   - the function-local statics (D_802A5708-D_802A5770 and
 *     D_802A59D0-D_802A5A0C in func_8022E884, D_802A593C-48 in
 *     func_8022F844, D_802A5960-C8 in func_8022E4DC, D_802A5A14-20 in
 *     func_802304C0, D_802A5560-70 in func_80230604, D_802A57A0-A8 and
 *     D_802A5734/58/8C in func_8023017C) are reached with lui/%lo at
 *     every access, as the original does; func_8022E884's are its own
 *     statics, passed to its inlined cases as parameters (so the cases'
 *     loads fold to lui/%lo too);
 *   - func_80232FF8, func_80232FA8, func_802312AC and func_802320A8
 *     are global: as statics IPA moved func_80232FF8's register saves
 *     into func_802334CC, and the others would get only t6-t9;
 *   - float sums are written (a*b + c*d + e*f) + g, and int and float
 *     constants (90, 0 in compares, x * 2) are kept apart as the
 *     original's are;
 *   - a variable keeps one register over all its live ranges, so
 *     func_8022FF58's two angle wraps have a variable each.
 *   - IDO -O3 gives a static function's parameters registers in the
 *     order its body first uses them, and its callers set them in the
 *     source's order: func_8022F3F8's mask is its first parameter (the
 *     callers set a3 first), though it is used last and so gets a3.
 *   - each inlined call adds its own frame area (rounded to 8), its
 *     parameters then its locals in declaration order; func_8022E884's
 *     frame is the original's 0xC0.
 *   - func_8022E884's inlined statics sit where its stubs say: E0A4 is
 *     case 20's loop, E170 case 4's y test, E264 case 12's loop, E328
 *     case 5's y test, E874 case 2's and E87C case 1's helper (the stubs
 *     come out in a post-order walk from E884, callees in reverse call
 *     order). Case 4's y test uses a[4] (the height) on both sides.
 *   - case 12/20's ball (D_802A59E8, D_802A5A00) is a function-scope
 *     static struct of its helper (Ball): uopt sees its fields as plain
 *     variables (isvar S), so the stores and the loop's y updates are
 *     direct lui/%lo sharing one lui at, they kill none of p's loads
 *     (p[3] is a CSE in f2 for the add, the store and the doubling into
 *     step, f22), and &ball for the test is rebuilt in s0 every pass.
 *     A file-scope struct or array, or a pointer parameter, puts the
 *     ball's address in a register or kills the p[3] load. y is
 *     p[3] + p[1]: uopt keeps that order, which loads p[1] first.
 *     func_8022E0A4 is defined above func_8022E170 so that its static's
 *     cfe symbol number comes before func_8022E3D4's statics (.bss
 *     order, below); moving the static helper moves no code.
 *   - func_802320A8's t is a volatile scalar: the original stores it in
 *     both arms and reloads it after the join (then b = t; x = b - n).
 * .bss: IDO lays it out in ugen's .lcomm order (a 256-bucket hash on
 * cfe's symbol number; within a bucket function-local statics come
 * first), and fcmp resolves a static by its name, so only sym+k
 * accesses depend on our layout. D_802A59D0 is an f32[5] static defined
 * after func_8022E4DC (moved up above the stubs, which moves no code),
 * so it and the two balls follow its Vec3fs as in the original;
 * D_802A5708-D_802A5760 are extern (see there).
 * Left: func_802320A8 (11, the size right): what's left is obj+0x58's slot
 * (0x64, not 0x68), the default's delay slot, which holds the store to
 * t (the original has a nop), and colouring in the 0x20000 case. ugen
 * hands out f4..f18 least recently freed first (frees at a value's last
 * read, in operand order; the queue carries on through labels and calls,
 * and as1 -O3 deletes register computations that are dead). The no-gp
 * branch's and the join's allocations leave the queue at case 1 as
 * [16 18 4 6 8 10]; the original's registers from case 1 on need
 * [4 6 8 10 18 16]: two temporaries taken after the join's statement and
 * freed the other way round, with no code left. The draft gets that with
 * a dead c = spD4[2] - spB0[1] * h (spB0[1] * h into f16, spD4[2] into
 * f18, then sub.s c, f18, f16) kept alive to the colouring by the
 * switch's + (s32) c * 0, which uopt folds only afterwards; as1 then
 * deletes the computation. The original's source for this is not known
 * (scratch/48600/p9/NOTES.txt). What is understood:
 *   - the default case is an endless loop storing n to the volatile t:
 *     a read of n there keeps it live through the outer loop (the
 *     original loads it into fs3 before the loop and stores it after),
 *     and the volatile store stays in the loop, in the branch's delay
 *     slot. A plain store is hoisted out of the loop (one word more);
 *     with no read of n it is dead and the function is 6 words shorter.
 *   - case 2 computes a, b and c before the three stores, and case 1's
 *     d, e and f put the call on the right: func_80234408(x) * (...)
 *     makes cfe spill the call's result to a stack temporary, which grows
 *     the frame.
 *   - the wraps are written out (spE4[1] - 90.0f each time) with no
 *     shared x: one variable keeps one register over all its live
 *     ranges, so x in all three forced mov.s copies.
 *   - spE4[1] is promoted (loaded once into f2 for both compares of the
 *     first wrap) because the no-gp branch's zero stores share a block
 *     with obj->unk3C->unk4's load: uopt leaves blocks with an indirect
 *     access out of a memory variable's live range, so the store isn't
 *     in it. Pass 7's goto dl; dl: split them apart and lost it.
 *   - in the 0x20000 case, t's reload goes through b (b = t; then
 *     x = b - n), which the original keeps in f16 against our f22, and
 *     x = sp80[1]; x = x - 90.0f is two statements: both move the
 *     colouring. Pass 7's b = sp80[0] (n = b) was right only for the
 *     wrong temporary queue; with the queue right, n = sp80[0]. The
 *     0x30000 case's angle is c, not x (x there took f2 for sp80[1]'s f0).
 * uopt puts a commutative op's operands in its own order, not the
 * source's, but the form of an operand counts: func_8022E0AC's mul.s
 * takes the original's order with (*arg0).unk38 (not arg0->unk38) on the
 * right, and func_80230914's add.s with a store of y back to o->unk6C
 * before o->unk6C += o->unk70 (both permuter finds). In func_802320A8,
 * the 0x20000 case has a dead read of obj->unk3C->unkC (a permuter find:
 * it moves the colouring), and pos = sp110 + spC8 is written
 * spC8 + sp110.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

/* A test cylinder in func_8022E884's cases 12 and 20 (centre, radius,
 * height). */
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 r;
    f32 h;
} Ball;

/* A collision shape's placement. */
typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 pos[3];
    /* 0x1C */ f32 rot[3];
    /* 0x28 */ f32 scale[3];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
} Shape;

/* Probably the whole of structs.h's UnkStructA, but this file stores
 * 0x7FFFFFFF in 0x18 and 0x1C, which UnkStructA has as floats. */
/* A path step: flags (0x80000000 wait, 0xF0000 facing, 0xFFFF mode). */
typedef struct {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Step3C;

typedef struct UnkStructA80 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ Step3C *unk3C;
    /* 0x40 */ Shape *unk40;
    /* 0x44 */ struct UnkStructA80 *unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ f32 unk4C[3];
    /* 0x58 */ f32 unk58[3];
    /* 0x64 */ s32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ struct UnkStructA80 *unk78;
    /* 0x7C */ struct UnkStructA80 *unk7C;
} UnkStructA80; /* size 0x80 */

/* A screen rectangle (0x40 bytes from func_8022A6C4). */
typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ f32 x0;
    /* 0x14 */ f32 y0;
    /* 0x18 */ f32 x1;
    /* 0x1C */ f32 y1;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} Rect40;




void func_8022946C(void *, s32);
void * func_8022A328(void *, s32, s32, s32, s32);
int func_8023369C(f32, f32, f32);
int func_802336E4(f32);
s32 func_8023372C(f32, f32);
s32 func_80233768(f32);
s32 func_802337EC(f32);
f32 func_80234408(f32);
f32 func_80234434(f32);
s32 func_80234768(void);
void func_802348B4(f32 *, f32 *, f32 *);
void func_80234900(f32 *, f32 *, f32 *);
s32 func_80238A10(void *, s32, s32, s32, s32);
s32 func_80238FDC(void);
s32 func_80239094(void);
s32 func_802391F0(void);
void func_80239430(void);
s32 * func_8023A840(void);
s32 func_8026D7D8(s32, s32, s32);
u8 func_8026DC74(s32);
void func_8026DCAC(f32, f32, f32, void *, s32);
void func_8026E6E4(void *, f32 *, f32 *);
f32 func_8026E8B8(void);
f32 func_8026E938(void *);
void func_8029C8D0(f32 m[4][4], f32, f32, f32);
void func_8029CA80(f32 m[4][4], f32, f32, f32);
f32 func_8029CB40(f32);
void guMtxIdentF(f32 mf[4][4]);
f32 sqrtf(f32);

extern UnkStructA80 D_800A3F00[];
extern f32 D_800A7F00;
extern s32 D_800A7F04;
extern Rect40 *D_800A7F08[8];
extern void *D_800A7F28;
// D_802A5560: func_80230604
extern UnkStructA80 D_802A5578;
extern void *D_802A55F4;
extern UnkStructA80 D_802A55F8;
extern s32 *D_802A5674;
extern UnkStructA80 D_802A5678;
extern s32 *D_802A56F4;
extern s32 *D_802A56F8;
extern s32 D_802A56FC;
extern s32 D_802A5700;
extern f32 D_802A5780[3];
extern f32 D_802A5790[3];
extern f32 D_802A57B0[3];
extern f32 D_802A57BC;
extern f32 D_802A57C0[4];
extern s32 D_802A5800;
extern s32 D_802A5804;
extern f32 D_802A5808[3];
extern f32 D_802A5814;
extern s32 D_802A5818[];
extern s32 D_802A5938;

void func_8022DB00(void);
void func_8022DE00(void);
void func_8022DE6C(void);
f32 func_8022DF68(f32 *arg0, f32 *arg1);
static s32 func_8022DFBC(f32 *arg0, f32 *arg1);
static s32 func_8022E0A4(f32 *arg0);
static void func_8022E0AC(UnkStructA80 *arg0, f32 *arg1);
static s32 func_8022E178(f32 *arg0, f32 *arg1);
static void func_8022E26C(UnkStructA80 *arg0, f32 *arg1);
f32 func_8022E330(f32 *arg0, f32 *arg1);
void func_8022E364(f32 *arg0, f32 *arg1, f32 *arg2);
void func_8022E3D4(f32 m[4][4], f32 *v);
static s32 func_8022E4DC(f32 *arg0, f32 *arg1);
s32 func_8022E884(UnkStructA80 *arg0, UnkStructA80 *arg1);
static s32 func_8022F3F8(s32 arg0, f32 *arg1, f32 *arg2, s32 arg3);
f32 *func_8022F4AC(f32 *arg0, s32 arg1, f32 *arg2);
f32 *func_8022F550(f32 *arg0, s32 arg1);
static s32 func_8022F5E4(f32 *arg0, u8 *arg1, u8 *arg2);
s32 func_8022F698(s32 arg0, f32 *arg1, f32 *arg2, f32 **arg3, s32 arg4);
s32 func_8022F77C(s32 arg0, s32 arg1, s32 arg2);
void func_8022F808(f32 *arg0, f32 *arg1);
static f32 *func_8022F844(s32 arg0, f32 *arg1, s32 arg2, f32 *arg3);
void func_8022F998(f32 *arg0, s32 arg1, f32 *arg2);
void func_8022FA10(f32 *arg0, s32 arg1, f32 *arg2);
void func_8022FA88(f32 *arg0, s32 arg1, f32 *arg2);
f32 func_8022FB00(u8 *arg0);
void func_8022FC0C(s32 arg0);
static UnkStructA80 *func_8022FC18(UnkStructA80 *arg0);
static void func_8022FC20(s32 *arg0, u8 *arg1);
static void func_8022FC50(u8 *arg0);
s32 func_8022FC90(UnkStructA80 *arg0);
void func_8022FDE8(void);
void func_8022FE94(s32 arg0);
void func_8022FEA0(f32 arg0);
void func_8022FEAC(f32 *arg0, f32 *arg1);
void func_8022FF58(f32 *arg0, f32 *arg1, f32 *arg2);
static void func_8023017C(s32 arg0, u8 *arg1, f32 *arg2, s32 arg3);
void func_80230340(f32 *arg0, s32 arg1, u8 *arg2);
void func_802303C0(f32 *arg0, s32 arg1, u8 *arg2);
void func_80230440(f32 *arg0, s32 arg1, u8 *arg2);
static f32 *func_802304C0(s32 arg0, f32 *arg1, s32 arg2);
static void func_80230604(f32 *arg0, s32 arg1, f32 *arg2, s32 arg3);
void func_802306B0(f32 *arg0, s32 arg1, f32 *arg2);
void func_80230720(f32 *arg0, s32 arg1, f32 *arg2);
void func_80230790(f32 *arg0, s32 arg1, f32 *arg2);
void func_80230800(f32 *arg0, s32 arg1);
void func_8023085C(f32 *arg0, s32 arg1);
void func_802308B8(f32 *arg0, s32 arg1);
void func_80230914(u8 *arg0);
void func_80230AA0(UnkStructA80 *arg0, s32 arg1, s32 arg2, s32 arg3);
static s32 *func_80230B98(s32 arg0);
static void func_80230C08(s32 *arg0);
void *func_80230CB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4);
void func_80230E6C(s32 arg0, s32 arg1);
void *func_80230E9C(u8 *arg0);
void func_8023101C(s32 arg0, s32 arg1, s32 arg2, u8 *arg3);
void *func_80231048(s32 arg0, u8 *arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5);
void func_802310BC(s32 arg0, s32 arg1, u8 *arg2);
void *func_802310F4(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void *func_8023116C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void *func_802311E8(u8 *arg0);
void func_80231244(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80231274(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_802312AC(u8 *arg0);
void func_802313B0(u8 *arg0, s32 arg1);
void func_802313DC(u8 *arg0, s32 arg1);
void func_80231408(u8 *arg0, s32 arg1);
void func_80231434(UnkStructA80 *arg0);
void func_80231D60(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80231D88(u8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3);
void func_802320A8(void);
void func_80232A34(u8 *arg0, s32 arg1);
void func_80232AA8(u8 *arg0);
void func_80232AC8(u8 *arg0, u8 *arg1);
void func_80232B04(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
void func_80232BA0(u8 *arg0, u8 *arg1);
s32 func_80232BD0(f32 *arg0, s32 arg1);
s32 func_80232C74(f32 *arg0, s32 arg1);
s32 func_80232D18(f32 *arg0, s32 arg1);
void func_80232DB4(f32 *arg0);
void func_80232E60(void);
void func_80232FA8(UnkStructA80 *arg0);
static void func_80232FF0(UnkStructA80 *arg0);
void func_80232FF8(UnkStructA80 *arg0, s32 *arg1);
void func_802334CC(void);
void func_8023357C(UnkStructA80 *arg0);
s32 func_802335A0(s32 arg0);

static void func_8023363C(void) {
}

static void func_80233634(void) {
}

static void func_8023362C(void) {
}

static void func_80233624(void) {
}

s32 func_802335A0(s32 arg0) {
    s32 *p;
    s32 i;
    s32 found;

    if (arg0 == -1) {
        return 0;
    }
    p = D_802A5818;
    found = 0;
    for (i = 0; i < D_802A5938 && found == 0; i++, p++) {
        if (arg0 == *p) {
            found = 1;
        }
    }
    if (found != 0) {
        return 0;
    }
    D_802A5818[D_802A5938] = arg0;
    D_802A5938++;
    return 1;
}

void func_8023357C(UnkStructA80 *arg0) {
    for (; arg0 != NULL; arg0 = arg0->unk7C) {
        arg0->unk10 = 0;
    }
}

void func_802334CC(void) {
    s32 sp2C;

    while (1) {
        sp2C = D_802A5800;
        func_80232FF8(((UnkStructA80 *) &D_802A5578)->unk7C, &sp2C);
        func_80232FF8(((UnkStructA80 *) &D_802A5678)->unk7C, &sp2C);
        func_80232FA8(((UnkStructA80 *) &D_802A5578)->unk7C);
        func_80232FA8(((UnkStructA80 *) &D_802A5678)->unk7C);
        D_802A5800++;
        func_80239094();
    }
}

static void func_80232FF0(UnkStructA80 *arg0) {
    f32 b[3];
    f32 a[3];
    f32 c[3];
    f32 d[3];
    f32 e[3];

    switch (D_802A5804) {
    case 1:
        switch (func_80234768()) {
        case 0:
            func_802348B4(&a[0], &a[1], &a[2]);
            func_80234900(&b[0], &b[1], &b[2]);
            break;
        case 1:
            func_80234900(&a[0], &a[1], &a[2]);
            func_802348B4(&b[0], &b[1], &b[2]);
            break;
        }
        func_8022FF58(a, b, c);
        e[0] = arg0->unk40->pos[0];
        e[1] = arg0->unk40->pos[1];
        e[2] = arg0->unk40->pos[2];
        func_8022FF58(b, e, d);
        c[2] *= 0.7;
        if (c[2] <= d[2]) {
            arg0->unk40->unkC |= 1;
            arg0->unk8 &= ~0x20000000;
        } else {
            arg0->unk8 |= 0x20000000;
        }
        break;
    case 2:
        b[0] = D_802A5808[0];
        b[1] = D_802A5808[1];
        b[2] = D_802A5808[2];
        c[2] = D_802A5814;
        e[0] = arg0->unk40->pos[0];
        e[1] = arg0->unk40->pos[1];
        e[2] = arg0->unk40->pos[2];
        func_8022FF58(b, e, d);
        if (c[2] <= d[2]) {
            arg0->unk40->unkC |= 1;
            arg0->unk8 &= ~0x20000000;
        } else {
            arg0->unk8 |= 0x20000000;
        }
        break;
    }
}

void func_80232FF8(UnkStructA80 *arg0, s32 *arg1) {
    s32 f;

    for (; arg0 != NULL; arg0 = arg0->unk7C) {
        if (arg0->unk8 & 0x01000000) {
            arg0->unk40->unkC &= ~1;
            if (arg0->unk8 & 0x40000) {
                if (*arg1 == 0) {
                    arg0->unk8 ^= 0x40000000;
                }
                if (arg0->unk8 & 0x40000000) {
                    arg0->unk40->unkC &= ~1;
                } else {
                    arg0->unk40->unkC |= 1;
                }
            }
            if (D_802A5804 != 0 && (arg0->unk8 & 0x01000000) && (arg0->unk8 & 0x02000000)) {
                func_80232FF0(arg0);
            } else if (arg0->unk8 & 0x02000000) {
                arg0->unk8 |= 0x20000000;
            }
        } else {
            arg0->unk40->unkC |= 1;
        }
        if (arg0->unk44 != NULL) {
            func_80231434(arg0);
        }
        if (arg0->unk8 & 0x10000000) {
            arg0->unk40->unkC |= 0x2000;
        } else {
            arg0->unk40->unkC &= ~0x2000;
        }
        if (arg0->unk8 & 0x80000) {
            arg0->unk40->unkC |= 0x80;
        } else {
            arg0->unk40->unkC &= ~0x80;
        }
        if (arg0->unk8 & 0xF) {
            arg0->unk58[0] = arg0->unk40->pos[0];
            arg0->unk58[1] = arg0->unk40->pos[1];
            arg0->unk58[2] = arg0->unk40->pos[2];
            f = (arg0->unk40->pos[1] <= func_8026E8B8()) ? 1 : 0;
            if (f) {
                arg0->unk14 |= 0x40000000;
            } else {
                arg0->unk14 &= ~0x40000000;
            }
        }
    }
}

void func_80232FA8(UnkStructA80 *arg0) {
    for (; arg0 != NULL; arg0 = arg0->unk7C) {
        arg0->unk10 = arg0->unk14;
        arg0->unk14 = 0;
        arg0->unk18 = arg0->unk1C;
        arg0->unk1C = 0x7FFFFFFF;
        arg0->unk20 = arg0->unk24;
        arg0->unk24 = 0;
    }
}

void func_80232E60(void) {
    UnkStructA80 *o;
    s32 i;

    D_802A5808[0] = 0.0f;
    D_802A5808[1] = 0.0f;
    D_802A5808[2] = 0.0f;
    D_802A5814 = 0.0f;
    D_802A5804 = 1;
    D_800A7F00 = 0.0f;
    D_800A7F04 = 0x7F;
    D_802A5700 = 0x10;
    D_802A56FC = 0;
    func_80230C08((s32 *) &D_802A5578);
    D_802A5578.unk0 = 0x81;
    func_80230C08((s32 *) &D_802A55F8);
    D_802A55F8.unk0 = 0x82;
    func_80230C08((s32 *) &D_802A5678);
    D_802A5678.unk0 = 0x83;
    for (i = 0, o = D_800A3F00; i < 0x80; i++, o++) {
        o->unk0 = i;
        func_80230C08((s32 *) o);
    }
    o = D_800A3F00;
    func_8022FC20((s32 *) &D_802A55F8, (u8 *) o);
    for (i = 0; i < 0x7E; i++, o++) {
        func_8022FC20((s32 *) o, (u8 *) (o + 1));
    }
    for (i = 0; i < 0x48; i++) {
        D_802A5818[i] = -1;
    }
    D_802A5938 = 0;
    func_8022DB00();
}

void func_80232DB4(f32 *arg0) {
    UnkStructA80 *a = (UnkStructA80 *) arg0;
    UnkStructA80 *o;

    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if ((o->unkC ^ o->unk14) != 0 && ((o->unkC ^ o->unk14) & a->unk8) && a->unk4 < o->unk1C && a != o) {
            func_8022E884(arg0, (f32 *) o);
        }
    }
}

s32 func_80232D18(f32 *arg0, s32 arg1) {
    UnkStructA80 *o;

    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if (func_8022F3F8(arg1, arg0, (f32 *) o, 0) != 0 && func_8022E884(arg0, (f32 *) o) != 0) {
            return o->unk8 | ((UnkStructA80 *) arg0)->unk14;
        }
    }
    return 0;
}

s32 func_80232C74(f32 *arg0, s32 arg1) {
    UnkStructA80 *o;

    arg1 &= 0x3FFFF;
    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if (func_8022F3F8(arg1, arg0, (f32 *) o, 1) != 0 && func_8022E884(arg0, (f32 *) o) != 0) {
            return o->unk8 | ((UnkStructA80 *) arg0)->unk14;
        }
    }
    return 0;
}

s32 func_80232BD0(f32 *arg0, s32 arg1) {
    UnkStructA80 *o;

    arg1 &= 0x3FFFF;
    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if (func_8022F3F8(arg1, arg0, (f32 *) o, 2) != 0 && func_8022E884(arg0, (f32 *) o) != 0) {
            return o->unk8 | ((UnkStructA80 *) arg0)->unk14;
        }
    }
    return 0;
}

void func_80232BA0(u8 *arg0, u8 *arg1) {
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), f32 *, 0x10) = (f32) M2C_FIELD(arg0, f32 *, 0);
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), f32 *, 0x14) = (f32) M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), f32 *, 0x18) = (f32) M2C_FIELD(arg0, f32 *, 8);
}

void func_80232B04(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0;

    func_80238FDC();
    temp_v0 = M2C_FIELD(arg1, void **, 0x44);
    M2C_FIELD(arg1, s32 *, 0x3C) = arg2;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x48) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x48) - 1);
        M2C_FIELD(arg1, void **, 0x44) = NULL;
    }
    M2C_FIELD(arg1, void **, 0x44) = arg0;
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + 1);
    func_80232A34(arg1, M2C_FIELD(arg0, s32 *, 4) + 1);
    func_80238A10(func_802320A8, (s32) arg1, 0, 0, arg3);
}

void func_80232AC8(u8 *arg0, u8 *arg1) {
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg1, void **, 0x44);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x48) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x48) - 1);
        M2C_FIELD(arg1, void **, 0x44) = NULL;
    }
    M2C_FIELD(arg1, void **, 0x44) = arg0;
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + 1);
}

void func_80232AA8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x44);
    M2C_FIELD(temp_v0, s32 *, 0x48) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x48) - 1);
    M2C_FIELD(arg0, void **, 0x44) = NULL;
}

void func_80232A34(u8 *arg0, s32 arg1) {
    s32 sv_a3;
    void *sv_a2;
    void *sv_a0;
    s32 *temp_v0;
    s32 *var_a1;

    sv_a0 = arg0;
    sv_a2 = arg0;
    sv_a3 = arg1;
    func_8022FC50(arg0);
    if (sv_a3 < 0xD0) {
        sv_a0 = (void *) sv_a3;
        temp_v0 = func_80230B98(sv_a3);
        if (temp_v0 != NULL) {
            var_a1 = M2C_FIELD(temp_v0, s32 **, 0x78);
        } else {
            var_a1 = D_802A56F8;
        }
        func_8022FC20(var_a1, sv_a2);
    } else {
        func_8022FC20(&D_802A5678, sv_a2);
    }
    M2C_FIELD(sv_a2, s32 *, 4) = sv_a3;
}

void func_802320A8() {
    f32 sp134[3];
    f32 sp128[3];
    f32 sp11C[3];
    f32 sp110[3];
    f32 sp104[3];
    f32 spF8[3];
    UnkStructA80 *parent;
    UnkStructA80 *gp;
    f32 spE4[3];
    UnkStructA80 *obj;
    f32 spD4[3];
    f32 spC8[3];
    f32 spBC[3];
    f32 spB0[3];
    f32 a;
    f32 b;
    f32 e;
    f32 d;
    f32 c;
    f32 f;
    f32 h;
    f32 x;
    f32 y;
    f32 sp80[3];
    f32 n;
    f32 v;
    volatile f32 t;

    obj = (UnkStructA80 *) func_802391F0();
    parent = obj->unk44;
    gp = obj->unk44->unk44;
    func_8022F808((f32 *) obj, obj->unk58);
    func_8022F808((f32 *) obj, spBC);
    spD4[2] = 0.0f;
    spD4[1] = 0.0f;
    spD4[0] = 0.0f;
    while (obj->unk3C->flags != 0) {
        while (obj->unk3C->flags & 0x80000000) {
            func_80239094();
        }
        h = obj->unk3C->unk8 * 16.333334f;
        func_8022F808((f32 *) parent, sp110);
        if (gp != NULL && gp->unk3C != NULL) {
            func_8022F808((f32 *) gp, sp11C);
            func_8022FF58(sp11C, sp110, spE4);
            sp104[0] = spE4[0];
            if ((spE4[1] - 90.0f) >= 360.0f) {
                sp104[1] = (spE4[1] - 90.0f) - 360.0f;
            } else {
                if (spE4[1] < 90.0f) {
                    n = (spE4[1] - 90.0f) + 360.0f;
                } else {
                    n = (spE4[1] - 90.0f);
                }
                sp104[1] = n;
            }
            sp104[2] = obj->unk3C->unk4;
            func_8022FEAC(sp104, spBC);
            spBC[0] += sp110[0];
            spBC[1] += sp110[1];
            spBC[2] += sp110[2];
        } else {
            spE4[0] = 0.0f;
            spE4[1] = 0.0f;
            spE4[2] = 0.0f;
            spBC[0] = sp110[0];
            spBC[1] = sp110[1] - obj->unk3C->unk4;
            spBC[2] = sp110[2];
        }
        func_8022FF58(sp110, spBC, spB0);
        spB0[1] = spD4[1] - spB0[1]; c = spD4[2] - spB0[1] * h;
        switch ((obj->unk3C->flags & 0xFFFF) + (s32) c * 0) {
        case 1:
            a = (spBC[0] - obj->unk40->pos[0]) * func_80234434(spB0[1]) * obj->unk3C->unkC;
            b = (spBC[1] - obj->unk40->pos[1]) * func_80234434(spB0[1]) * obj->unk3C->unkC;
            c = (spBC[2] - obj->unk40->pos[2]) * func_80234434(spB0[1]) * obj->unk3C->unkC;
            d = ((obj->unk40->pos[0] - obj->unk58[0]) * obj->unk3C->unk10) * func_80234408(spB0[1]);
            e = ((obj->unk40->pos[1] - obj->unk58[1]) * obj->unk3C->unk10) * func_80234408(spB0[1]);
            f = ((obj->unk40->pos[2] - obj->unk58[2]) * obj->unk3C->unk10) * func_80234408(spB0[1]);
            sp128[0] = obj->unk40->pos[0] + d + a;
            sp128[1] = obj->unk40->pos[1] + e + b - h;
            sp128[2] = obj->unk40->pos[2] + f + c;
            break;
        case 2:
            y = obj->unk3C->unkC;
            a = (spBC[0] - obj->unk40->pos[0]) * y;
            b = (spBC[1] - obj->unk40->pos[1]) * y;
            c = (spBC[2] - obj->unk40->pos[2]) * y;
            sp128[0] = obj->unk40->pos[0] + a;
            sp128[1] = obj->unk40->pos[1] + b - h;
            sp128[2] = obj->unk40->pos[2] + c;
            break;
        default:
            for (;;) { t = n; }
        }
        func_8022F808((f32 *) obj, obj->unk58);
        func_8022FF58(sp110, sp128, spD4);
        spF8[0] = spD4[0];
        if ((spD4[1] - 90.0f) >= 360.0f) {
            spF8[1] = (spD4[1] - 90.0f) - 360.0f;
        } else {
            if (spD4[1] < 90.0f) {
                n = (spD4[1] - 90.0f) + 360.0f;
            } else {
                n = (spD4[1] - 90.0f);
            }
            spF8[1] = n;
        }
        spF8[2] = obj->unk3C->unk4;
        func_8022FEAC(spF8, spC8);
        if (!(obj->unk8 & 0xF00000)) {
            obj->unk4C[0] = spF8[0];
            if ((spF8[1] + 90.0f) >= 360.0f) {
                obj->unk4C[1] = (spF8[1] + 90.0f) - 360.0f;
            } else {
                if ((spF8[1] + 90.0f) < 0.0f) {
                    n = (spF8[1] + 90.0f) + 360.0f;
                } else {
                    n = (spF8[1] + 90.0f);
                }
                obj->unk4C[1] = n;
            }
            obj->unk4C[2] = spF8[2];
            obj->unk40->pos[0] = spC8[0] + sp110[0];
            obj->unk40->pos[1] = spC8[1] + sp110[1];
            if (obj->unk3C->flags & 0x100000) {
                y = func_8026E938(obj->unk40);
                if (y != 20000.0f && spC8[1] + sp110[1] <= y) {
                    obj->unk40->pos[1] = y;
                }
            }
            obj->unk40->pos[2] = spC8[2] + sp110[2];
        }
        switch (obj->unk3C->flags & 0xF0000) {
        default:
            obj->unk40->rot[1] = obj->unk44->unk40->rot[1];
            break;
        case 0x10000:
            obj->unk40->rot[1] = spD4[0];
            obj->unk40->rot[0] = spD4[1] * -1.0f + 90;
            obj->unk40->rot[2] = obj->unk44->unk40->rot[2];
            break;
        case 0x20000:
            sp80[0] = spD4[0];
            sp80[1] = spD4[1];
            sp80[2] = spD4[2];
            obj->unk40->rot[1] = obj->unk44->unk40->rot[1];
            v = obj->unk44->unk40->rot[1];
            if (v >= 0.0f && v <= 180.0f) {
                t = v;
            } else {
                t = (360.0f - v) * -1.0f;
            }
            b = t;
            if (sp80[0] >= 0.0f && sp80[0] <= 180.0f) {
                n = sp80[0];
            } else {
                n = (360.0f - sp80[0]) * -1.0f;
            }
            x = b - n;
            if (x >= 360.0f) {
                sp80[0] = x - 360.0f;
            } else {
                if (x < 0.0f) {
                    n = x + 360.0f;
                } else {
                    n = x;
                }
                sp80[0] = n;
            }
            x = sp80[1];
            x = x - 90.0f;
            if (x >= 360.0f) {
                y = obj->unk3C->unkC;
                sp80[1] = x - 360.0f;
            } else {
                if (sp80[1] < 90.0f) {
                    n = x + 360.0f;
                } else {
                    n = x;
                }
                sp80[1] = n;
            }
            func_8022FEAC(sp80, sp134);
            sp134[0] = sp110[0];
            sp134[1] += sp110[1];
            sp134[2] += sp110[2];
            func_8022FF58(sp110, sp134, sp80);
            if (func_8023369C(sp80[0], 0.0f, 90.0f)) {
                obj->unk40->rot[0] = sp80[1] * -1.0f;
            } else {
                obj->unk40->rot[0] = sp80[1];
            }
            break;
        case 0x30000:
            func_8022F808((f32 *) obj, sp134);
            func_8022FF58(sp134, sp110, sp80);
            obj->unk40->rot[1] = sp80[0];
            c = sp80[1] - 180.0f;
            if (c >= 360.0f) {
                n = c - 360.0f;
            } else {
                if (sp80[1] < 180.0f) {
                    t = c + 360.0f;
                } else {
                    t = c;
                }
                n = t;
            }
            obj->unk40->rot[0] = n * -1.0f;
            break;
        }
        func_80239094();
    }
    func_80239430();
}

void func_80231D88(u8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3) {
    f32 dz;
    f32 dy;
    f32 dx;
    f32 x;
    f32 w;

    dx = ((f32 *) arg1)[0] - ((f32 *) arg0)[0];
    dy = ((f32 *) arg1)[1] - ((f32 *) arg0)[1];
    dz = ((f32 *) arg1)[2] - ((f32 *) arg0)[2];
    dy *= -1.0f;
    if (func_802336E4(dy)) {
        switch (func_802337EC(dx)) {
        case 0:
            *arg2 = 0.0f;
            break;
        case 1:
            *arg2 = 90.0f;
            break;
        case -1:
            *arg2 = 270.0f;
            break;
        }
        switch (func_802337EC(dz)) {
        case 0:
            *arg3 = 0.0f;
            break;
        case 1:
            *arg3 = 90.0f;
            break;
        case -1:
            *arg3 = 270.0f;
            break;
        }
    } else {
        *arg2 = func_8029CB40(dx / dy) * 57.29577951308232;
        *arg3 = func_8029CB40(dz / dy) * 57.29577951308232;
    }
    if (func_802337EC(dy) == -1) {
        x = *arg2 + 180.0f;
        if (x >= 360.0f) {
            *arg2 = x - 360.0f;
        } else {
            if (x < 0.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            *arg2 = w;
        }
        x = *arg3 + 180.0f;
        if (x >= 360.0f) {
            *arg3 = x - 360.0f;
        } else {
            if (x < 0.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            *arg3 = w;
        }
    } else {
        x = *arg2;
        if (x >= 360.0f) {
            *arg2 = x - 360.0f;
        } else {
            if (x < 0.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            *arg2 = w;
        }
        x = *arg3;
        if (x >= 360.0f) {
            *arg3 = x - 360.0f;
        } else {
            if (x < 0.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            *arg3 = w;
        }
    }
}

void func_80231D60(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_802A5808[0] = arg0;
    D_802A5808[1] = arg1;
    D_802A5808[2] = arg2;
    D_802A5814 = arg3;
}

void func_80231434(UnkStructA80 *arg0) {
    f32 v[3];
    f32 rot[3];
    f32 ang[3];
    f32 m[4][4];
    f32 sp3C[2];
    f32 sp38;
    f32 x;
    f32 w;

    switch (arg0->unk8 & 0xF00000) {
    case 0x200000:
        arg0->unk40->pos[0] = arg0->unk4C[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = arg0->unk4C[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = arg0->unk4C[2] + arg0->unk44->unk40->pos[2];
        break;
    case 0x300000:
        x = arg0->unk4C[0];
        if (x >= 360.0f) {
            arg0->unk4C[0] = x - 360.0f;
        } else {
            if (x < 0.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            arg0->unk4C[0] = w;
        }
        x = arg0->unk4C[1] - 90.0f;
        if (x >= 360.0f) {
            arg0->unk4C[1] = x - 360.0f;
        } else {
            if (arg0->unk4C[1] < 90.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            arg0->unk4C[1] = w;
        }
        func_8022FEAC(arg0->unk4C, v);
        arg0->unk40->pos[0] = v[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = v[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = v[2] + arg0->unk44->unk40->pos[2];
        x = arg0->unk4C[1] + 90.0f;
        if (x >= 360.0f) {
            arg0->unk4C[1] = x - 360.0f;
        } else {
            if (x < 0.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            arg0->unk4C[1] = w;
        }
        break;
    case 0x400000:
        arg0->unk40->scale[0] = arg0->unk44->unk40->scale[0];
        arg0->unk40->scale[1] = arg0->unk44->unk40->scale[1];
        arg0->unk40->scale[2] = arg0->unk44->unk40->scale[2];
    case 0x600000:
        arg0->unk40->rot[1] = arg0->unk44->unk40->rot[1];
        arg0->unk40->rot[0] = arg0->unk44->unk40->rot[0];
        arg0->unk40->rot[2] = arg0->unk44->unk40->rot[2];
    case 0x700000:
        guMtxIdentF(m);
        v[2] = 0.0f; v[1] = 0.0f; v[0] = 0.0f;
        func_8029C8D0(m, arg0->unk44->unk40->rot[0], arg0->unk44->unk40->rot[1], arg0->unk44->unk40->rot[2]);
        func_8029CA80(m, arg0->unk4C[0], arg0->unk4C[1], arg0->unk4C[2]);
        func_8022E3D4(m, v);
        arg0->unk40->pos[0] = v[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = v[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = v[2] + arg0->unk44->unk40->pos[2];
        break;
    case 0x500000:
        arg0->unk40->scale[0] = arg0->unk44->unk40->scale[0];
        arg0->unk40->scale[1] = arg0->unk44->unk40->scale[1];
        arg0->unk40->scale[2] = arg0->unk44->unk40->scale[2];
        arg0->unk40->rot[0] = arg0->unk44->unk40->rot[0];
        arg0->unk40->rot[1] = arg0->unk44->unk40->rot[1];
        arg0->unk40->rot[2] = arg0->unk44->unk40->rot[2];
        func_8022FEAC(arg0->unk4C, rot);
        guMtxIdentF(m);
        v[2] = 0.0f; v[1] = 0.0f; v[0] = 0.0f;
        func_8029C8D0(m, arg0->unk44->unk40->rot[0], arg0->unk44->unk40->rot[1], arg0->unk44->unk40->rot[2]);
        func_8029CA80(m, rot[0], rot[1], rot[2]);
        func_8022E3D4(m, v);
        arg0->unk40->pos[0] = v[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = v[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = v[2] + arg0->unk44->unk40->pos[2];
        break;
    case 0x800000:
    case 0x900000:
        arg0->unk40->scale[0] = arg0->unk44->unk40->scale[0];
        arg0->unk40->scale[1] = arg0->unk44->unk40->scale[1];
        arg0->unk40->scale[2] = arg0->unk44->unk40->scale[2];
        func_8022FEAC(arg0->unk4C, rot);
        guMtxIdentF(m);
        v[2] = 0.0f; v[1] = 0.0f; v[0] = 0.0f;
        func_8029C8D0(m, arg0->unk44->unk40->rot[0], arg0->unk44->unk40->rot[1], arg0->unk44->unk40->rot[2]);
        func_8029CA80(m, rot[0], rot[1], rot[2]);
        func_8022E3D4(m, v);
        arg0->unk40->pos[0] = v[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = v[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = v[2] + arg0->unk44->unk40->pos[2];
        D_802A5780[0] = arg0->unk44->unk40->pos[0];
        D_802A5780[1] = arg0->unk44->unk40->pos[1];
        D_802A5780[2] = arg0->unk44->unk40->pos[2];
        D_802A5790[0] = arg0->unk40->pos[0];
        D_802A5790[1] = arg0->unk40->pos[1];
        D_802A5790[2] = arg0->unk40->pos[2];
        if ((arg0->unk8 & 0xF00000) != 0x900000) {
            func_8022FF58(D_802A5780, D_802A5790, ang);
        } else {
            func_8022FF58(D_802A5790, D_802A5780, ang);
        }
        arg0->unk40->rot[0] = ang[1] * -1.0f + 90.0f;
        arg0->unk40->rot[1] = ang[0];
        break;
    case 0x100000:
        if (!(arg0->unk44->unk8 & 0x01000000) || ((arg0->unk44->unk8 & 0x02000000) && !(arg0->unk44->unk8 & 0x20000000))) {
            arg0->unk40->unkC |= 1;
            break;
        }
        arg0->unk40->pos[0] = arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[2] = arg0->unk44->unk40->pos[2];
        arg0->unk40->pos[1] = func_8026E938(arg0->unk44->unk40);
        func_8026E6E4(arg0->unk44->unk40, sp3C, &sp38);
        arg0->unk40->rot[0] = sp3C[0];
        arg0->unk40->rot[1] = sp38;
        if (arg0->unk40->pos[1] <= arg0->unk44->unk40->pos[1]) {
            x = arg0->unk44->unk40->pos[1] - arg0->unk40->pos[1];
            x -= 2000.0f;
            x *= -1.0f;
            x /= 2000.0f;
            if (x <= 0.3f) {
                x = 0.3f;
            }
            arg0->unk40->scale[0] = x;
            arg0->unk40->scale[2] = x;
            arg0->unk40->scale[0] *= arg0->unk4C[0];
            arg0->unk40->scale[1] *= arg0->unk4C[1];
            arg0->unk40->scale[2] *= arg0->unk4C[2];
            arg0->unk40->pos[1] += D_800A7F00;
            arg0->unk40->unk36 = D_800A7F04;
        } else {
            arg0->unk40->scale[0] = 1.0f;
            arg0->unk40->scale[2] = 1.0f;
            arg0->unk40->pos[1] = 20000.0f;
        }
        break;
    }
}

void func_80231408(u8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) | arg1);
    func_802312AC(arg0);
}

void func_802313DC(u8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & ~arg1);
    func_802312AC(arg0);
}

void func_802313B0(u8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) ^ arg1);
    func_802312AC(arg0);
}

void func_802312AC(u8 *arg0) {
    u8 *p;

    if (M2C_FIELD(arg0, s32 *, 8) & 0x04000000) {
        p = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(p, s32 *, 0xC) &= ~0x40;
    } else {
        p = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(p, s32 *, 0xC) |= 0x40;
    }
    if (M2C_FIELD(arg0, s32 *, 8) & 0x08000000) {
        p = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(p, s32 *, 0xC) &= ~0x20;
    } else {
        p = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(p, s32 *, 0xC) |= 0x20;
    }
    if (M2C_FIELD(arg0, s32 *, 8) & 0x80000) {
        p = M2C_FIELD(arg0, void **, 0x40);
        if (M2C_FIELD(p, s32 *, 8) != 0x60) {
            func_8022946C(p, 0x60);
        }
    } else {
        p = M2C_FIELD(arg0, void **, 0x40);
        if (M2C_FIELD(p, s32 *, 8) != 0x40) {
            func_8022946C(p, 0x40);
        }
    }
}

void func_80231274(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80230CB4(arg0, -1, arg1, arg2, (void *) arg3);
}

void func_80231244(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80230CB4(arg0, arg1, 0, arg2, (void *) arg3);
}

void *func_802311E8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(0x22, -1, 0x01180000, 0xD0, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), s16 *, 0x36) = 0x7F;
        M2C_FIELD(temp_v0, f32 *, 0x4C) = 1.0f;
        M2C_FIELD(temp_v0, f32 *, 0x50) = 1.0f;
        M2C_FIELD(temp_v0, f32 *, 0x54) = 1.0f;
    }
    return temp_v0;
}

void *func_8023116C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(arg0, -1, arg1, D_802A5700, NULL);
    if (temp_v0 != NULL) {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) = arg2;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = arg3;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) = arg4;
        M2C_FIELD(temp_v0, f32 *, 0x58) = arg2;
        M2C_FIELD(temp_v0, f32 *, 0x5C) = arg3;
        M2C_FIELD(temp_v0, f32 *, 0x60) = arg4;
    }
    return temp_v0;
}

void *func_802310F4(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(arg0, -1, 0, arg1, NULL);
    if (temp_v0 != NULL) {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) = arg2;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = arg3;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) = arg4;
        M2C_FIELD(temp_v0, f32 *, 0x58) = arg2;
        M2C_FIELD(temp_v0, f32 *, 0x5C) = arg3;
        M2C_FIELD(temp_v0, f32 *, 0x60) = arg4;
    }
    return temp_v0;
}

void func_802310BC(s32 arg0, s32 arg1, u8 *arg2) {
    func_80230CB4(arg0, -1, arg1, M2C_FIELD(arg2, s32 *, 4) + 1, arg2);
}

void *func_80231048(s32 arg0, u8 *arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(arg0, -1, arg2, M2C_FIELD(arg1, s32 *, 4) + 1, arg1);
    if (temp_v0 != NULL) {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) = arg3;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = arg4;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) = arg5;
        M2C_FIELD(temp_v0, f32 *, 0x58) = arg3;
        M2C_FIELD(temp_v0, f32 *, 0x5C) = arg4;
        M2C_FIELD(temp_v0, f32 *, 0x60) = arg5;
    }
    return temp_v0;
}

void func_8023101C(s32 arg0, s32 arg1, s32 arg2, u8 *arg3) {
    func_80230CB4(arg0, arg1, arg2, M2C_FIELD(arg3, s32 *, 4) + 1, arg3);
}

void *func_80230E9C(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(M2C_FIELD(arg0, s32 *, 0x28), -1, M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 4) + 1, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x30) = (s32) M2C_FIELD(arg0, s32 *, 0x30);
        M2C_FIELD(temp_v0, f32 *, 0x34) = (f32) M2C_FIELD(arg0, f32 *, 0x34);
        M2C_FIELD(temp_v0, f32 *, 0x38) = (f32) M2C_FIELD(arg0, f32 *, 0x38);
        M2C_FIELD(temp_v0, s32 *, 0x3C) = (s32) M2C_FIELD(arg0, s32 *, 0x3C);
        M2C_FIELD(temp_v0, s32 *, 0x2C) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
        M2C_FIELD(temp_v0, f32 *, 0x4C) = (f32) M2C_FIELD(arg0, f32 *, 0x4C);
        M2C_FIELD(temp_v0, f32 *, 0x50) = (f32) M2C_FIELD(arg0, f32 *, 0x50);
        M2C_FIELD(temp_v0, f32 *, 0x54) = (f32) M2C_FIELD(arg0, f32 *, 0x54);
        M2C_FIELD(temp_v0, f32 *, 0x58) = (f32) M2C_FIELD(arg0, f32 *, 0x58);
        M2C_FIELD(temp_v0, f32 *, 0x5C) = (f32) M2C_FIELD(arg0, f32 *, 0x5C);
        M2C_FIELD(temp_v0, f32 *, 0x60) = (f32) M2C_FIELD(arg0, f32 *, 0x60);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x18);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x1C) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x1C);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x20);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x24) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x24);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x28) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x28);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x2C) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x2C);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x30) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x30);
    }
    return temp_v0;
}

void func_80230E6C(s32 arg0, s32 arg1) {
    func_80230CB4(arg0, -1, 0, 0xD0, (void *) arg1);
}

void *func_80230CB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    UnkStructA80 *obj;
    Shape *shape;
    UnkStructA80 *p;
    s32 *list;
    u8 *res;
    s32 kind;

    if (D_802A56FC >= 0x80) {
        return NULL;
    }
    res = func_8026CE28(arg0);
    if (res == NULL) {
        for (;;) {}
    }
    if (arg2 & 0x100000) {
        kind = 0x51;
    } else if (arg2 & 0x80000) {
        kind = 0x60;
    } else {
        kind = 0x40;
    }
    if (arg1 == -1) {
        shape = func_8022A6C4(res, kind);
    } else {
        shape = func_8022A328(res, kind, 2, arg1, 0);
    }
    if (shape == NULL) {
        for (;;) {}
    }
    if (D_802A5674 == NULL) {
        for (;;) {}
    }
    obj = (UnkStructA80 *) D_802A5674;
    func_8022FC50((u8 *) obj);
    func_80230C08((s32 *) obj);
    if (arg3 < 0xD0) {
        p = (UnkStructA80 *) func_80230B98(arg3);
        if (p != NULL) {
            list = (s32 *) p->unk78;
        } else {
            list = D_802A56F8;
        }
        func_8022FC20(list, (u8 *) obj);
    } else {
        func_8022FC20((s32 *) &D_802A5678, (u8 *) obj);
    }
    obj->unk8 |= 0x80000000 | arg2;
    obj->unk4 = arg3;
    obj->unk28 = arg0;
    obj->unk40 = shape;
    shape->unkC |= 0x61;
    obj->unk40->unk36 = 0xFF;
    obj->unk44 = (UnkStructA80 *) arg4;
    if (arg4 != NULL) {
        ((UnkStructA80 *) arg4)->unk48++;
    }
    D_802A56FC++;
    return obj;
}

static void func_80230C08(s32 *arg0) {
    UnkStructA80 *o = (UnkStructA80 *) arg0;

    o->unk4 = 0;
    o->unk8 = 0;
    o->unkC = 0;
    o->unk10 = 0;
    o->unk14 = 0;
    o->unk18 = 0x7FFFFFFF;
    o->unk1C = 0x7FFFFFFF;
    o->unk20 = 0;
    o->unk24 = 0;
    o->unk28 = -1;
    o->unk2C = -1;
    o->unk30 = 1;
    o->unk3C = NULL;
    o->unk40 = NULL;
    o->unk44 = NULL;
    o->unk48 = 0;
    o->unk64 = 0;
    o->unk34 = 50.0f;
    o->unk38 = 50.0f;
    o->unk4C[0] = 0.0f;
    o->unk4C[1] = 0.0f;
    o->unk4C[2] = 0.0f;
    o->unk58[0] = 0.0f;
    o->unk58[1] = 0.0f;
    o->unk58[2] = 0.0f;
    o->unk68 = 0.0f;
    o->unk6C = 0.0f;
    o->unk70 = 1.6333334f;
    o->unk74 = 100.0f;
    o->unk78 = NULL;
    o->unk7C = NULL;
}

static s32 *func_80230B98(s32 arg0) {
    UnkStructA80 *p;

    if (arg0 < 0xD0) {
        p = D_802A5578.unk7C;
        D_802A56F8 = (s32 *) &D_802A5578;
        for (; p != NULL; p = p->unk7C) {
            if (arg0 < p->unk4) {
                return (s32 *) p;
            }
            D_802A56F8 = (s32 *) p;
        }
        return NULL;
    }
    return D_802A56F4;
}

void func_80230AA0(UnkStructA80 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 y;

    y = func_8026E938(arg0->unk40);
    if (y != 20000.0f && arg0->unk40->pos[1] - arg0->unk6C + arg0->unk68 <= y) {
        arg0->unk6C = 0.0f;
        arg0->unk68 = 0.0f;
        arg0->unk40->pos[1] = y;
        return;
    }
    arg0->unk40->pos[1] += arg0->unk68;
    arg0->unk40->pos[1] -= arg0->unk6C;
    if (arg0->unk6C <= arg0->unk74) {
        arg0->unk6C += arg0->unk70;
    } else {
        arg0->unk6C = arg0->unk74;
    }
}

void func_80230914(u8 *arg0) {
    UnkStructA80 *o = (UnkStructA80 *) arg0;
    f32 h;
    f32 y;

    y = func_8026E938(o->unk40);
    if (y != 20000.0f && o->unk40->pos[1] - o->unk6C + o->unk68 <= y) {
        o->unk6C = 0.0f;
        o->unk68 = 0.0f;
        o->unk40->pos[1] = y;
    } else {
        o->unk40->pos[1] += o->unk68;
        o->unk40->pos[1] -= o->unk6C;
        y = o->unk6C;
        if (y <= o->unk74) {
            o->unk6C = y;
            o->unk6C += o->unk70;
        } else {
            o->unk6C = o->unk74;
        }
    }
    if ((o->unk30 & ~0x20) == 1) {
        h = o->unk34 + o->unk38;
    } else {
        h = o->unk38;
    }
    y = func_8022FB00((u8 *) o);
    if (y < o->unk40->pos[1] || y < o->unk40->pos[1] + h) {
        if (o->unk68 != 0.0f) {
            o->unk6C = 0.0f;
        }
        o->unk68 = 0.0f;
        o->unk40->pos[1] = y - h;
    }
}

void func_802308B8(f32 *arg0, s32 arg1) {
    func_802304C0(arg1, arg0, 0);
}

void func_8023085C(f32 *arg0, s32 arg1) {
    func_802304C0(arg1, arg0, 1);
}

void func_80230800(f32 *arg0, s32 arg1) {
    func_802304C0(arg1, arg0, 2);
}

void func_80230790(f32 *arg0, s32 arg1, f32 *arg2) {
    func_80230604(arg0, arg1, arg2, 0);
}

void func_80230720(f32 *arg0, s32 arg1, f32 *arg2) {
    func_80230604(arg0, arg1, arg2, 1);
}

void func_802306B0(f32 *arg0, s32 arg1, f32 *arg2) {
    func_80230604(arg0, arg1, arg2, 2);
}

static void func_80230604(f32 *arg0, s32 arg1, f32 *arg2, s32 arg3) {
    static f32 *D_802A5560;
    static f32 D_802A5568;
    static f32 D_802A556C;
    static f32 D_802A5570;

    D_802A5560 = func_802304C0(arg1, arg0, arg3);
    if (D_802A5560 != NULL) {
        func_8022F808(D_802A5560, D_802A5780);
        func_8022F808(arg0, D_802A5790);
        func_8022FF58(D_802A5780, D_802A5790, &D_802A5568);
        D_802A556C = 0.0f;
        D_802A5570 = (M2C_FIELD(arg0, f32 *, 0x34) + M2C_FIELD(D_802A5560, f32 *, 0x34)) - D_802A5570;
        func_8022FEAC(&D_802A5568, arg2);
    }
}

static f32 *func_802304C0(s32 arg0, f32 *arg1, s32 arg2) {
    static UnkStructA80 *D_802A5A14;
    static UnkStructA80 *D_802A5A18;
    static f32 D_802A5A1C;
    static s32 D_802A5A20;

    D_802A5A14 = D_802A55F4;
    arg0 &= 0x3FFFF;
    D_802A57BC = 32767.0f;
    D_802A5A18 = NULL;
    func_8022F808(arg1, D_802A5780);
    for (; D_802A5A14 != NULL; D_802A5A14 = D_802A5A14->unk7C) {
        if (D_802A5A14->unk4 >= 0xD0) {
            break;
        }
        D_802A5A20 = func_8022F3F8(arg0, arg1, (f32 *) D_802A5A14, arg2);
        if (D_802A5A20 != 0 && func_8022E884(arg1, (f32 *) D_802A5A14) != 0) {
            func_8022F808((f32 *) D_802A5A14, D_802A5790);
            D_802A5A1C = func_8022DF68(D_802A5780, D_802A5790);
            if (D_802A5A1C < D_802A57BC) {
                D_802A5A18 = D_802A5A14;
                D_802A57BC = D_802A5A1C;
            }
        }
    }
    return (f32 *) D_802A5A18;
}

void func_80230440(f32 *arg0, s32 arg1, u8 *arg2) {
    func_8023017C(arg1, arg2, arg0, 0);
}

void func_802303C0(f32 *arg0, s32 arg1, u8 *arg2) {
    func_8023017C(arg1, arg2, arg0, 1);
}

void func_80230340(f32 *arg0, s32 arg1, u8 *arg2) {
    func_8023017C(arg1, arg2, arg0, 2);
}

static void func_8023017C(s32 arg0, u8 *arg1, f32 *arg2, s32 arg3) {
    static UnkStructA80 *D_802A5734;
    static s32 D_802A5758;
    static s32 D_802A578C;
    static f32 D_802A57A0;
    static f32 D_802A57A4;
    static f32 D_802A57A8;
    f32 *out = (f32 *) arg1;
    f32 n;

    arg0 &= 0x3FFFF;
    D_802A5734 = D_802A55F4;
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    D_802A5758 = 0;
    func_8022F808(arg2, D_802A5790);
    for (; D_802A5734 != NULL; D_802A5734 = D_802A5734->unk7C) {
        if (D_802A5734->unk4 >= 0xD0) {
            break;
        }
        D_802A578C = func_8022F3F8(arg0, arg2, (f32 *) D_802A5734, arg3);
        if (D_802A578C != 0 && func_8022E884((UnkStructA80 *) arg2, D_802A5734) != 0) {
            func_8022F808((f32 *) D_802A5734, D_802A5780);
            func_8022FF58(D_802A5780, D_802A5790, D_802A57B0);
            D_802A57B0[1] = 0.0f;
            D_802A57B0[2] = (D_802A5734->unk34 + ((UnkStructA80 *) arg2)->unk34) - D_802A57B0[2];
            func_8022FEAC(D_802A57B0, &D_802A57A0);
            out[0] += D_802A57A0;
            out[2] += D_802A57A8;
            D_802A5758++;
        }
    }
    if (D_802A5758 != 0) {
        n = D_802A5758;
        out[0] /= n;
        out[2] /= n;
    }
}

void func_8022FF58(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 dz;
    f32 dy;
    f32 dx;
    f32 v;
    f32 u;
    f32 w;

    dx = arg1[0] - arg0[0];
    dy = arg1[1] - arg0[1];
    dz = arg1[2] - arg0[2];
    arg2[2] = sqrtf(dx * dx + dz * dz);
    if (func_8023372C(arg2[2], 0.002f)) {
        arg2[2] = 0.0f;
        arg2[0] = 0.0f;
        if (func_80233768(dy) == -1) {
            arg2[1] = 0.0f;
        } else {
            arg2[1] = 180.0f;
        }
    } else {
        arg2[0] = func_8029CB40(dx / dz) * 57.29577951308232;
        if (dz < 0.0f) {
            arg2[0] -= 180.0f;
        }
        arg2[1] = func_8029CB40(dy / arg2[2]) * 57.29577951308232;
        v = arg2[0];
        if (v >= 360.0f) {
            arg2[0] = v - 360.0f;
        } else {
            if (v < 0.0f) {
                w = v + 360.0f;
            } else {
                w = v;
            }
            arg2[0] = w;
        }
        u = arg2[1] + 90.0f;
        if (u >= 360.0f) {
            arg2[1] = u - 360.0f;
        } else {
            if (u < 0.0f) {
                w = u + 360.0f;
            } else {
                w = u;
            }
            arg2[1] = w;
        }
    }
    if (func_8023372C(arg2[1], 0.002f)) {
        arg2[1] = 0.0f;
    }
    arg2[2] = sqrtf(arg2[2] * arg2[2] + (v = dy) * v);
}

void func_8022FEAC(f32 *arg0, f32 *arg1) {
    f32 sp24;

    sp24 = func_80234434(arg0[0]);
    arg1[0] = (arg0[2] * sp24) * func_80234408(arg0[1]);
    arg1[1] = arg0[2] * func_80234434(arg0[1]);
    sp24 = func_80234408(arg0[0]);
    arg1[2] = (arg0[2] * sp24) * func_80234408(arg0[1]);
}

void func_8022FEA0(f32 arg0) {
    D_800A7F00 = arg0;
}

void func_8022FE94(s32 arg0) {
    D_800A7F04 = arg0;
}

void func_8022FDE8() {
    UnkStructA80 *o;

    while ((o = D_802A5578.unk7C) != NULL) {
        func_8022FC90(o);
    }
    while ((o = D_802A5678.unk7C) != NULL) {
        func_8022FC90(o);
    }
    D_802A5938 = 0;
    D_800A7F00 = 0.0f;
    D_800A7F04 = 0x7F;
    D_802A5804 = 1;
}

s32 func_8022FC90(UnkStructA80 *arg0) {

    if (D_802A56FC <= 0) {
        return -1;
    }
    arg0->unk8 = 0;
    func_8022FC50((u8 *) arg0);
    func_8022FC20((s32 *) &D_802A55F8, (u8 *) arg0);
    func_8022A1E8(arg0->unk40);
    func_8026CCBC(arg0->unk28);
    arg0->unk28 = -1;
    if (arg0->unk44 != NULL) {
        arg0->unk44->unk48--;
    }
    while (arg0->unk48 != 0) {
        func_8022FC90(func_8022FC18(arg0));
    }
    D_802A56FC--;
    return arg0->unk0;
}

static void func_8022FC50(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x7C);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0x78) = (void *) M2C_FIELD(arg0, void **, 0x78);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x78), void **, 0x7C) = (void *) M2C_FIELD(arg0, void **, 0x7C);
        return;
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x78), void **, 0x7C) = NULL;
}

static void func_8022FC20(s32 *arg0, u8 *arg1) {
    u8 *temp_v0;

    M2C_FIELD(arg1, s32 **, 0x78) = arg0;
    M2C_FIELD(arg1, void **, 0x7C) = (void *) M2C_FIELD(arg0, void **, 0x7C);
    M2C_FIELD(arg0, void **, 0x7C) = arg1;
    temp_v0 = M2C_FIELD(arg1, void **, 0x7C);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0x78) = arg1;
    }
}

static UnkStructA80 *func_8022FC18(UnkStructA80 *arg0) {
    UnkStructA80 *p;

    for (p = D_802A5578.unk7C; p != NULL; p = p->unk7C) {
        if (p->unk44 == arg0) {
            return p;
        }
    }
    for (p = D_802A5678.unk7C; p != NULL; p = p->unk7C) {
        if (p->unk44 == arg0) {
            return p;
        }
    }
    return NULL;
}

void func_8022FC0C(s32 arg0) {
    D_802A5804 = arg0;
}

f32 func_8022FB00(u8 *arg0) {
    s32 f;
    s32 g;
    s32 h;
    s32 sp50[3];
    f32 sum;
    s32 i;
    s32 t;
    Shape *obj;

    obj = ((UnkStructA80 *) arg0)->unk40;
    func_8026DCAC(obj->pos[0], obj->pos[1], obj->pos[2], sp50, 2);
    sum = 0.0f;
    for (i = 0; i <= sp50[1]; i++) {
        sum += (s32) func_8026DC74(i) * 100.0f;
    }
    for (; i < 6; i++) {
        t = func_8026D7D8(sp50[0], i, sp50[2]);
        if (t != 0x2010 && ((t & 0xF) || (t & 0x60))) {
            break;
        }
        sum += (s32) func_8026DC74(i) * 100.0f;
    }
    return sum;
}

void func_8022FA88(f32 *arg0, s32 arg1, f32 *arg2) {
    func_8022F844(arg1, arg0, 0, arg2);
}

void func_8022FA10(f32 *arg0, s32 arg1, f32 *arg2) {
    func_8022F844(arg1, arg0, 1, arg2);
}

void func_8022F998(f32 *arg0, s32 arg1, f32 *arg2) {
    func_8022F844(arg1, arg0, 2, arg2);
}

static f32 *func_8022F844(s32 arg0, f32 *arg1, s32 arg2, f32 *arg3) {
    static UnkStructA80 *D_802A593C;
    static UnkStructA80 *D_802A5940;
    static f32 D_802A5944;
    static s32 D_802A5948;

    arg0 &= 0x3FFFF;
    D_802A593C = D_802A55F4;
    D_802A57BC = 32767.0f;
    D_802A5940 = NULL;
    func_8022F808(arg1, D_802A5780);
    for (; D_802A593C != NULL; D_802A593C = D_802A593C->unk7C) {
        if (D_802A593C->unk4 >= 0xD0) {
            break;
        }
        D_802A5948 = func_8022F3F8(arg0, arg1, (f32 *) D_802A593C, arg2);
        if (D_802A5948 != 0) {
            func_8022F808((f32 *) D_802A593C, D_802A5790);
            D_802A5944 = func_8022DF68(D_802A5780, D_802A5790);
            if (D_802A5944 < D_802A57BC) {
                D_802A5940 = D_802A593C;
                D_802A57BC = D_802A5944;
            }
        }
    }
    *arg3 = D_802A57BC;
    if (*arg3 == 32767.0f) {
        D_802A5940 = NULL;
    }
    return (f32 *) D_802A5940;
}

void func_8022F808(f32 *arg0, f32 *arg1) {
    M2C_FIELD(arg1, f32 *, 0) = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x10);
    arg1[1] = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14);
    arg1[2] = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x18);
}

s32 func_8022F77C(s32 arg0, s32 arg1, s32 arg2) {
    UnkStructA80 *o;

    arg0 &= 0x3FFFF;
    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if ((o->unk8 & arg0) && func_8022F5E4((f32 *) o, (u8 *) arg1, (u8 *) arg2) != 0) {
            return (s32) o;
        }
    }
    return 0;
}

s32 func_8022F698(s32 arg0, f32 *arg1, f32 *arg2, f32 **arg3, s32 arg4) {
    f32 *var_t0;
    s32 var_t1;
    s32 var_v0;

    var_t0 = D_802A55F4;
    arg0 &= 0x3FFFF;
    var_t1 = 0;
    if (var_t0 != NULL && arg4 > 0) {
        do {
            if ((M2C_FIELD(var_t0, s32 *, 8) & arg0) && func_8022F5E4(var_t0, arg1, arg2) != 0) {
                *arg3++ = var_t0;
                var_t1++;
            }
            var_t0 = M2C_FIELD(var_t0, f32 **, 0x7C);
        } while (var_t0 != NULL && var_t1 < arg4);
    }
    for (var_v0 = var_t1; var_v0 < arg4; var_v0++) {
        *arg3++ = NULL;
    }
    return var_t1;
}

static s32 func_8022F5E4(f32 *arg0, u8 *arg1, u8 *arg2) {
    f32 *n = (f32 *) ((UnkStructA80 *) arg0)->unk40;
    f32 *c = (f32 *) arg1;
    f32 *r = (f32 *) arg2;

    if (c[0] - r[0] <= n[4] && n[4] <= r[0] + c[0] && c[1] - r[1] <= n[5] && n[5] <= r[1] + c[1] &&
        c[2] - r[2] <= n[6] && n[6] <= r[2] + c[2]) {
        return 1;
    }
    return 0;
}

f32 *func_8022F550(f32 *arg0, s32 arg1) {
    UnkStructA80 *o;

    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if (func_8022F3F8(arg1, arg0, (f32 *) o, 0) != 0 && func_8022E884((UnkStructA80 *) arg0, o) != 0) {
            return (f32 *) o;
        }
    }
    return NULL;
}

f32 *func_8022F4AC(f32 *arg0, s32 arg1, f32 *arg2) {
    UnkStructA80 *o;

    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if ((f32 *) o != arg2 && func_8022F3F8(arg1, arg0, (f32 *) o, 0) != 0 &&
            func_8022E884((UnkStructA80 *) arg0, o) != 0) {
            return (f32 *) o;
        }
    }
    return NULL;
}

static s32 func_8022F3F8(s32 arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    s32 r;

    if (arg1 == arg2) {
        return 0;
    }
    switch (arg3) {
    case 0:
        if (((UnkStructA80 *) arg2)->unk8 & arg0) {
            r = 1;
        } else {
            r = 0;
        }
        break;
    case 1:
        if (arg0 == (((UnkStructA80 *) arg2)->unk8 & arg0)) {
            r = 1;
        } else {
            r = 0;
        }
        break;
    case 2:
        if (arg0 == (((UnkStructA80 *) arg2)->unk8 & 0x3FFFF)) {
            r = 1;
        } else {
            r = 0;
        }
        break;
    default:
        for (;;) {
        }
    }
    return r;
}

/*
 * Module bss (f32[5], f32[5], f32[8], f32[8]); extern, not static, until the
 * whole 0x802A5560-0x802A5A24 can be defined in the original's order: as
 * statics they can't sit 0x258 before func_8022E4DC's Vec3fs, so every
 * sym+k access would land wrong. Static or extern gives the same code.
 */
extern f32 D_802A5708[];
extern f32 D_802A5720[];
extern f32 D_802A5738[];
extern f32 D_802A5760[];

static s32 func_8022E4DC(f32 *a, f32 *b) {
    static Vec3f p;
    static Vec3f q;
    static Vec3f ap;
    static Vec3f qp;
    static Vec3f aq;
    static Vec3f pq;
    static Vec3f n;
    f32 d;

    if (b[4] + a[3] + b[3] < func_8022DF68(a, b)) {
        return 0;
    }
    guMtxIdentF((f32 (*)[4]) D_802A57C0);
    func_8029C8D0((f32 (*)[4]) D_802A57C0, b[5], b[6], b[7]);
    func_8029CA80((f32 (*)[4]) D_802A57C0, 0.0f, a[3] + b[4], 0.0f);
    p.x = 0.0f;
    p.y = 0.0f;
    p.z = 0.0f;
    func_8022E3D4((f32 (*)[4]) D_802A57C0, &p.x);
    p.x += b[0];
    p.y += b[1];
    p.z += b[2];
    guMtxIdentF((f32 (*)[4]) D_802A57C0);
    func_8029C8D0((f32 (*)[4]) D_802A57C0, b[5], b[6], b[7]);
    func_8029CA80((f32 (*)[4]) D_802A57C0, 0.0f, a[3] * -1.0f, 0.0f);
    q.x = 0.0f;
    q.y = 0.0f;
    q.z = 0.0f;
    func_8022E3D4((f32 (*)[4]) D_802A57C0, &q.x);
    q.x += b[0];
    q.y += b[1];
    q.z += b[2];
    ap.x = a[0] - p.x;
    ap.y = a[1] - p.y;
    ap.z = a[2] - p.z;
    qp.x = q.x - p.x;
    qp.y = q.y - p.y;
    qp.z = q.z - p.z;
    pq.x = p.x - q.x;
    pq.y = p.y - q.y;
    pq.z = p.z - q.z;
    aq.x = a[0] - q.x;
    aq.y = a[1] - q.y;
    aq.z = a[2] - q.z;
    func_8022E364(&ap.x, &qp.x, &n.x);
    d = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
    if (b[3] + a[3] <= d / sqrtf(qp.x * qp.x + qp.y * qp.y + qp.z * qp.z)) {
        return 0;
    }
    if (func_8022E330(&pq.x, &ap.x) > 0 || func_8022E330(&qp.x, &aq.x) > 0) {
        return 0;
    }
    return 1;
}

static f32 D_802A59D0[5];

static s32 func_8022E87C(void) {
    s32 r;
    s32 dx;
    s32 dy;
    s32 dz;

    r = D_802A5720[3] + D_802A5708[3];
    r *= r;
    dx = D_802A5708[0] - D_802A5720[0];
    dx *= dx;
    dy = D_802A5708[1] - D_802A5720[1];
    dy *= dy;
    dz = D_802A5708[2] - D_802A5720[2];
    dz *= dz;
    if (dx + dz + dy >= r) {
        return 0;
    }
    return 1;
}

static s32 func_8022E874(f32 *p, f32 *r) {
    f32 n;
    f32 y;

    if (p[4] + p[3] + D_802A5760[4] + D_802A5760[3] < func_8022DF68(p, D_802A5760)) {
        return 0;
    }
    n = p[4] / (p[3] * 2);
    y = p[3];
    r[3] = p[3];
    while (n > 0.0f) {
        guMtxIdentF((f32 (*)[4]) D_802A57C0);
        func_8029C8D0((f32 (*)[4]) D_802A57C0, p[5], p[6], p[7]);
        func_8029CA80((f32 (*)[4]) D_802A57C0, 0.0f, y, 0.0f);
        r[0] = r[1] = r[2] = 0.0f;
        func_8022E3D4((f32 (*)[4]) D_802A57C0, r);
        r[0] += p[0];
        r[1] += p[1];
        r[2] += p[2];
        if (func_8022E4DC(r, D_802A5760) == 1) {
            return 1;
        }
        if (n - 1.0f >= 1.0f) {
            n -= 1.0f;
            y += r[3] + r[3];
        } else {
            n -= 1.0f;
            y += (r[3] + r[3]) * n;
        }
    }
    return 0;
}

static s32 func_8022E328(f32 *a, f32 *b) {
    if (a[1] <= b[1]) {
        if (a[1] + a[3] <= b[1]) {
            return 0;
        }
    } else if (b[1] + b[4] <= a[1] - a[3]) {
        return 0;
    }
    D_802A5780[0] = a[0];
    D_802A5780[1] = 0.0f;
    D_802A5780[2] = a[2];
    D_802A5790[0] = b[0];
    D_802A5790[1] = 0.0f;
    D_802A5790[2] = b[2];
    if (a[3] + b[3] <= func_8022DF68(D_802A5780, D_802A5790)) {
        return 0;
    }
    return 1;
}

static s32 func_8022E264(f32 *p) {
    static Ball D_802A59E8;
    f32 t;
    f32 step;

    D_802A59E8.x = p[0];
    D_802A59E8.y = p[3] + p[1];
    D_802A59E8.z = p[2];
    D_802A59E8.r = p[3];
    step = p[3] * 2;
    for (t = 0.0f; t < p[4];) {
        if (func_8022E178((f32 *) &D_802A59E8, D_802A5760) != 0) {
            return 1;
        }
        t += step;
        if (t + step <= p[4]) {
            D_802A59E8.y += step;
        } else {
            D_802A59E8.y += p[4] - t;
        }
    }
    return 0;
}

static s32 func_8022E0A4(f32 *p) {
    static Ball D_802A5A00;
    f32 t;
    f32 step;

    D_802A5A00.x = p[0];
    D_802A5A00.y = p[3] + p[1];
    D_802A5A00.z = p[2];
    D_802A5A00.r = p[3];
    step = p[3] * 2;
    for (t = 0.0f; t < p[4];) {
        if (func_8022DFBC((f32 *) &D_802A5A00, D_802A5760) != 0) {
            return 1;
        }
        t += step;
        if (t + step <= p[4]) {
            D_802A5A00.y += step;
        } else {
            D_802A5A00.y += p[4] - t;
        }
    }
    return 0;
}

static s32 func_8022E170(f32 *a, f32 *b) {
    if (a[1] <= b[1]) {
        if (a[1] + a[4] <= b[1]) {
            return 0;
        }
    } else if (b[1] + b[4] <= a[1]) {
        return 0;
    }
    D_802A5780[0] = a[0];
    D_802A5780[1] = 0.0f;
    D_802A5780[2] = a[2];
    D_802A5790[0] = b[0];
    D_802A5790[1] = 0.0f;
    D_802A5790[2] = b[2];
    if (a[3] + b[3] <= func_8022DF68(D_802A5780, D_802A5790)) {
        return 0;
    }
    return 1;
}


void func_8022E3D4(f32 m[4][4], f32 *v) {
    static f32 D_802A594C;
    static f32 D_802A5950;
    static f32 D_802A5954;
    static f32 D_802A5958;
    f32 tx, ty, tz;

    tx = (v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0]) + m[3][0];
    ty = (v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1]) + m[3][1];
    tz = (v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2]) + m[3][2];
    D_802A5958 = (v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3]) + m[3][3];
    v[0] = tx * D_802A5958;
    v[1] = ty * D_802A5958;
    v[2] = tz * D_802A5958;
    D_802A594C = tx;
    D_802A5950 = ty;
    D_802A5954 = tz;
}

void func_8022E364(f32 *a, f32 *b, f32 *c) {
    c[0] = a[1] * b[2] - b[1] * a[2];
    c[1] = a[2] * b[0] - b[2] * a[0];
    c[2] = a[0] * b[1] - b[0] * a[1];
}

f32 func_8022E330(f32 *a, f32 *b) {
    return a[2] * b[2] + (a[1] * b[1] + b[0] * a[0]);
}

static void func_8022E26C(UnkStructA80 *arg0, f32 *arg1) {
    f32 h;
    f32 r;

    if (arg0->unk30 & 0x20) {
        h = r = 1.0f;
    } else {
        r = arg0->unk40->scale[0];
        if (r < arg0->unk40->scale[1]) {
            r = arg0->unk40->scale[1];
        }
        if (r < arg0->unk40->scale[2]) {
            r = arg0->unk40->scale[2];
        }
        h = arg0->unk40->scale[1];
    }
    arg1[0] = arg0->unk40->pos[0];
    arg1[1] = arg0->unk40->pos[1] + arg0->unk38 * h;
    arg1[2] = arg0->unk40->pos[2];
    arg1[3] = arg0->unk34 * r;
}

static s32 func_8022E178(f32 *a, f32 *b) {
    if (a[0] <= b[0]) {
        if (a[0] + a[3] <= b[0]) {
            return 0;
        }
    } else if (b[0] + b[4] <= a[0] - a[3]) {
        return 0;
    }
    D_802A5780[0] = 0.0f;
    D_802A5780[1] = a[1];
    D_802A5780[2] = a[2];
    D_802A5790[0] = 0.0f;
    D_802A5790[1] = b[1];
    D_802A5790[2] = b[2];
    if (a[3] + b[3] <= func_8022DF68(D_802A5780, D_802A5790)) {
        return 0;
    }
    return 1;
}


static void func_8022E0AC(UnkStructA80 *arg0, f32 *arg1) {
    f32 r;

    r = arg0->unk40->scale[0];
    if (r < arg0->unk40->scale[2]) {
        r = arg0->unk40->scale[2];
    }
    arg1[0] = arg0->unk40->pos[0];
    arg1[1] = arg0->unk40->pos[1];
    arg1[2] = arg0->unk40->pos[2];
    arg1[5] = arg0->unk40->rot[0];
    arg1[6] = arg0->unk40->rot[1];
    arg1[7] = arg0->unk40->rot[2];
    arg1[3] = arg0->unk34 * r;
    arg1[4] = arg0->unk40->scale[1] * (*arg0).unk38;
}

static s32 func_8022DFBC(f32 *a, f32 *b) {
    s32 r;
    f32 d;

    if (a[2] <= b[2]) {
        if (a[2] + a[3] <= b[2]) {
            return 0;
        }
    } else if (b[2] + b[4] <= a[2] - a[3]) {
        return 0;
    }
    D_802A5780[0] = a[0];
    D_802A5780[1] = a[1];
    D_802A5780[2] = 0.0f;
    D_802A5790[0] = b[0];
    D_802A5790[1] = b[1];
    D_802A5790[2] = 0.0f;
    if (a[3] + b[3] <= func_8022DF68(D_802A5780, D_802A5790)) {
        return 0;
    }
    return 1;
}

f32 func_8022DF68(f32 *arg0, f32 *arg1) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = M2C_FIELD(arg1, f32 *, 0) - M2C_FIELD(arg0, f32 *, 0);
    temp_fv1 = arg1[1] - arg0[1];
    temp_fa1 = arg1[2] - arg0[2];
    return ((sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1))));
}

s32 func_8022E884(UnkStructA80 *arg0, UnkStructA80 *arg1) {
    s32 sa;
    s32 sb;
    s32 hit;

    sa = arg0->unk30 & ~0x20;
    sb = arg1->unk30 & ~0x20;
    switch (sa | sb) {
    case 1:
        func_8022E26C(arg0, D_802A5708);
        func_8022E26C(arg1, D_802A5720);
        hit = func_8022E87C();
        break;
    case 2:
        func_8022E0AC(arg0, D_802A5738);
        func_8022E0AC(arg1, D_802A5760);
        hit = func_8022E874(D_802A5738, D_802A59D0);
        break;
    case 3:
            switch (sa) {
            case 1:
                func_8022E26C(arg0, D_802A5708);
                func_8022E0AC(arg1, D_802A5738);
                break;
            case 2:
                func_8022E0AC(arg0, D_802A5738);
                func_8022E26C(arg1, D_802A5708);
                break;
            default:
                for (;;) {
                }
            }
        hit = func_8022E4DC(D_802A5708, D_802A5738);
        break;
    case 9:
            switch (sa) {
            case 1:
                func_8022E26C(arg0, D_802A5708);
                func_8022E0AC(arg1, D_802A5738);
                break;
            case 8:
                func_8022E0AC(arg0, D_802A5738);
                func_8022E26C(arg1, D_802A5708);
                break;
            default:
                for (;;) {
                }
            }
        hit = func_8022E178(D_802A5708, D_802A5738);
        break;
    case 5:
            switch (sa) {
            case 1:
                func_8022E26C(arg0, D_802A5708);
                func_8022E0AC(arg1, D_802A5738);
                break;
            case 4:
                func_8022E0AC(arg0, D_802A5738);
                func_8022E26C(arg1, D_802A5708);
                break;
            default:
                for (;;) {
                }
            }
        hit = func_8022E328(D_802A5708, D_802A5738);
        break;
    case 17:
            switch (sa) {
            case 1:
                func_8022E26C(arg0, D_802A5708);
                func_8022E0AC(arg1, D_802A5738);
                break;
            case 16:
                func_8022E0AC(arg0, D_802A5738);
                func_8022E26C(arg1, D_802A5708);
                break;
            default:
                for (;;) {
                }
            }
        hit = func_8022DFBC(D_802A5708, D_802A5738);
        break;
    case 12:
        func_8022E0AC(arg0, D_802A5738);
        func_8022E0AC(arg1, D_802A5760);
        hit = func_8022E264(D_802A5738);
        break;
    case 4:
        func_8022E0AC(arg0, D_802A5738);
        func_8022E0AC(arg1, D_802A5760);
        hit = func_8022E170(D_802A5738, D_802A5760);
        break;
    case 20:
        func_8022E0AC(arg0, D_802A5738);
        func_8022E0AC(arg1, D_802A5760);
        hit = func_8022E0A4(D_802A5738);
        break;
    default:
        for (;;) {
        }
    }
    if (hit) {
        sa = arg0->unkC & arg1->unk8;
        if (sa != 0) {
            arg0->unk14 |= sa;
            if (arg0->unk1C >= arg1->unk4) {
                arg0->unk1C = arg1->unk4;
                arg0->unk24 = (s32) arg1;
            }
        }
        sa = arg1->unkC & arg0->unk8;
        if (sa != 0) {
            arg1->unk14 |= sa;
            if (arg1->unk1C >= arg0->unk4) {
                arg1->unk1C = arg0->unk4;
                arg1->unk24 = (s32) arg0;
            }
        }
        hit = arg1->unk8 & 0x3FFFF;
    }
    return hit;
}

void func_8022DE6C() {
    s32 i;

    if (!(*func_8023A840() & 2)) {
        D_800A7F28 = func_8026CE28(0x34E);
        for (i = 0; i < 8; i++) {
            D_800A7F08[i] = func_8022A6C4(D_800A7F28, 0x40);
            D_800A7F08[i]->x0 = 291.0f;
            D_800A7F08[i]->y0 = 56.0f;
            D_800A7F08[i]->x1 = 291.0f;
            D_800A7F08[i]->y1 = 56.0f;
            D_800A7F08[i]->unk20 = 0.0f;
            D_800A7F08[i]->unk24 = 0.0f;
        }
    }
}

void func_8022DE00() {
    s32 i;

    if (!(*func_8023A840() & 2)) {
        for (i = 0; i < 8; i++) {
            func_8022A1E8(D_800A7F08[i]);
        }
        func_8026CCBC(0x34E);
        D_800A7F28 = NULL;
    }
}

