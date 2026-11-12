/*
 * NON_MATCHING: main_code's 426E0, complete: the object pool D_800A0D00
 * (0xA0 objects linked by priority), its draw loop (matrices, render
 * modes, texture segments and scrolls, fog), the per-object animation and
 * texture slots, and object creation from a model file. Every function
 * is in C, in the original's order (callees first; the statics
 * func_802280EC, func_802284F0, func_802284F8, func_802289B8 and
 * func_8022A850 inlined, with their stubs; func_8022827C and
 * func_80228500 kept). Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 17, eu 17, jp 17
 *
 * The code is the same in every version.
 *
 * Levers that worked here:
 * - An object's index from its pointer is ((u32)p - (u32)D_800A0D00) /
 *   sizeof(UnkObj) into an s32: li at,80; divu with no break check.
 *   Pointer subtraction gives a signed div with checks, and a u32 index
 *   shares the 80 with the multiply.
 * - `for (i = 0; i != N; i++)` gives the bne end test with no guard; a
 *   pointer loop against another symbol gets a guard (do-while avoids it).
 * - `s->unk14 += s->unkC` with the same sum in the test gives the
 *   original's path-specific CSE; prev/next locals stop reloads after
 *   the link stores.
 * - func_8022A6C4: D_802A547C..D_802A548C are its function-scope
 *   statics (model, chunks, index, found index, an unused one), which
 *   uopt keeps in registers and stores back where a region ends; the
 *   kind stays a local. `kind | 0` as the call argument keeps kind out
 *   of a2 (the chunk count takes it), and `if (arg0) {}` first gives
 *   arg0's copy t0 before kind.
 * - func_8022946C: `i = D_800A0D00[idx].unk0` before `p = ...` (i first
 *   seen first takes v1). func_8022997C: `s = D_80098C68; do {` on one
 *   line orders the preheader's addiu s1 before addiu s0.
 * - func_8022A858: the pool loop is an index do-while tested against
 *   the end symbol (`&D_800A0D00[i] < D_800A3F00`: not unrolled, base
 *   re-materialised after it), and the D_80098C68 clear is written out
 *   in it (the call to func_80229BB4, inlined, schedules differently).
 * - func_8022928C (the 3x3 inverse): the nine elements are locals
 *   initialised row-major in their declarations, the three cofactors and
 *   the determinant scalars (uncoloured: stored and reloaded), `det =
 *   1.0f / det`, an early return on zero, and the stores column 0, then
 *   the other cofactors row-major, then the zeros and 1.0f.
 *
 * Left:
 * - func_802289C0 (the draw loop, 10): obj is in s2 and func_802284F0's
 *   obj is kept in memory as in the original. In its texture loop, model
 *   is `unk4[i].unk0` and the then-branch index `unk4[i].unk4` (one slot
 *   address, the i*8 strength-reduced). An animation's frames are 8-byte
 *   pairs (UnkTexFrame: picture, duration), indexed with one sll by 3,
 *   not an s32 array at cur * 2. The anim pointer is taken inside the
 *   else branch, after `g = gfx` (as1 hoists it into the bnez delay
 *   slot): taken before the if, it interferes with the unk4C reload in
 *   the loop's first block, and the reload can't share v0 with it as in
 *   the original. The else branch reads anim->unk4 into `cur` and the
 *   frame counter into `count` (the unk8 load before the threshold's,
 *   and `count + 1` stored back), and tests the threshold directly (slt
 *   at). `anim->unk4 == anim->unk0 - 1` keeps the two unk4 + 1 apart.
 *   The unkC & 2 call goes through a function-pointer local loaded after
 *   the D_802A5470 store (jalr v0, not t9). An `s32 pad[2]` in
 *   func_802284F8 gives the 0x160 frame and puts that obj's home at 0xB0.
 *   Left: gfx is in a1 where the original has t1 and leaves a1 unused
 *   through the loop (some range there that as1 deleted?); cur takes v1,
 *   so g takes t1 (v1 in the original); and the D_8029F840 store, which
 *   the original puts in func_80228500's jal delay slot (cc -S shows
 *   ugen emitting it after the argument setup there; ours emits it
 *   before). The original's join block does `addiu t1,t1,8` (gfx + 1,
 *   not g + 1), and passing gfx by value (`gfx = func_802284F0(arg0,
 *   gfx)`, returned) puts it in t1 with the original's priority; both
 *   are worse for now (29 and 17 words), because cur still takes v1
 *   and pushes model, count and g one register on. The original
 *   needs cur (or the anim->unk4 load) in a1, which is what as1
 *   leaves unused. The ry ternary's `: 0` (an int) gives the
 *   original's mtc1 pair; the matrix stack is a frame struct's
 *   `mtx[]`, as in 41FD0.c.
 * - func_8022A328 (4): the free slot and the list position are
 *   function-scope statics (D_802A5474, D_802A5478: no other function
 *   uses them), which uopt keeps in registers and stores back at each
 *   exit. `if (arg1) {}` after their initialisation ends the entry
 *   block, so the first slot test is a direct load and the pool base is
 *   loaded in the loop's preheader and again after it, as in the
 *   original. There is no pointer local: every access is
 *   `D_800A0D00[D_802A5474].f`, so the slot's address is one expression
 *   that uopt hoists above the position loop and rebuilds after the
 *   calls itself (with shifts, not a multu by the coloured 80). The
 *   chunk address is a local with a dead read (`c = &arg0->unkC[arg3];
 *   if (c) {}`, which keeps the +12 in a register) taken before the
 *   float zeros, and the else branch's stores are integer 0 and 1 (so
 *   the 0.0f of the other branch is a separate constant). The tail
 *   stores unk34, unk36, unk4C, then the D_802A5460 increment.
 *   Left (4): the arg2 == 4 block's schedule (mtc1 before the stack
 *   loads).
 * - func_80229C10 (2): `if (!chunks) {}` keeps model+12 a value of its
 *   own; `if (!arg1) {}` first and `if (!arg0) {}` after the loop keep
 *   the arguments' registers busy, so dl takes a3, first t0 and i t1 as
 *   in the original. The loop bound 2 is left in a1 (a0 in the
 *   original: arg0 dead in the loop but live where dl is set). w
 *   as arg1 again (after the loop) gives the original's a1 for it and
 *   frees a0 for the bound, but a dead read of arg0 before the loop
 *   splits the block and moves i to v0 (7 at best). func_80229448 (1): the empty loop survives only
 *   as `i * 4 != 16` (a plain `i < 4` is deleted, the multiply is what
 *   uopt strength-reduces after its dead-loop pass). A local counter
 *   takes v0 in the entry block and pushes the IV to v1; a third
 *   parameter as the counter can't use v0/v1 there (uopt forbids them
 *   to a parameter in the entry block), so the IV gets v0 and 16 v1.
 *   Left: bne's operand order. uopt swaps `==`/`!=` operands unless
 *   the left one is a variable at input, so the original compared a
 *   variable that copy propagation later turned into the IV; every
 *   such form tried (a j = i * 4 local, split blocks) colours j first.
 */
#include "common.h"

void *malloc(u32);
void free(void *);
void *realloc(void *, u32);

/* A model file: a count of chunks and the chunks (type, count, offset). */
typedef struct {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkChunk; /* size 0xC */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ UnkChunk unkC[1];
} UnkModel;

/* A joint of chunk 1 (0x30 bytes). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ Vec3f unk4;
    /* 0x10 */ Vec3f unk10;
    /* 0x1C */ Vec3f unk1C;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
} UnkJoint; /* size 0x30 */

/* Chunk 2: per animation, its keys. */
typedef struct {
    /* 0x00 */ s32 *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ Vec3f unk8;
    /* 0x14 */ Vec3f unk14;
    /* 0x20 */ Vec3f unk20;
} UnkKey; /* size 0x2C */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkKey *unk4;
    /* 0x08 */ s32 unk8;
} UnkKeySet; /* size 0xC */

/* Chunk 3: channels (0x2F: key list; 0x30: a curve, tag 0x31). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 *unk8;
    /* 0x0C */ f32 *unkC;
} UnkCurve;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 *unkC;
    /* 0x10 */ s32 *unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 *unk18;
    /* 0x1C */ f32 *unk1C;
} UnkChan; /* size 0x20 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkChan *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} UnkChanSet; /* size 0x10 */

/* What func_8022AF1C reads a model into. */
typedef struct {
    /* 0x00 */ s32 unk0[3];
    /* 0x0C */ s32 unkC[3];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u32 unk1C;
    /* 0x20 */ UnkJoint *unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ UnkKeySet *unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ UnkChanSet *unk30;
    /* 0x34 */ s32 unk34;
} UnkSkel; /* size 0x38 */

/* A node of an instance's tree. */
typedef struct UnkNode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ struct UnkNode *unk8;
    /* 0x0C */ struct UnkNode **unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ Vec3f unk14;
    /* 0x20 */ Vec3f unk20;
    /* 0x2C */ Vec3f unk2C;
    /* 0x38 */ s32 unk38;
} UnkNode; /* size 0x3C */

/* An instance (func_8022D1D0). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ Vec3f unk4;
    /* 0x10 */ Vec3f unk10;
    /* 0x1C */ Vec3f unk1C;
    /* 0x28 */ UnkNode *unk28;
    /* 0x2C */ UnkJoint *unk2C;
    /* 0x30 */ UnkKeySet *unk30;
    /* 0x34 */ UnkChanSet *unk34;
    /* 0x38 */ s32 *unk38;
} UnkInst; /* size 0x3C */

/* A copy of an instance's tree with two key states per node. */
typedef struct UnkTree {
    /* 0x00 */ UnkNode *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ struct UnkTree **unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10[2];
    /* 0x18 */ Vec3f unk18[2][3];
} UnkTree; /* size 0x60 */

/* A playing animation's track. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 *unk10;
    /* 0x14 */ s32 *unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ UnkTree *unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
} UnkTrack; /* size 0x28 */

/* A playing animation (func_8022C8B8). */
typedef struct {
    /* 0x00 */ UnkInst *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ UnkTrack *unk14;
} UnkAnim; /* size 0x18 */

/* An object's animation slots (unk48). */
typedef struct {
    /* 0x00 */ UnkAnim *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
} UnkAnimSlot; /* size 0xC */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkAnimSlot *unk4;
} UnkAnimSlots;

/* An object's texture slots (unk4C). */
typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ s32 unk4;
} UnkTexSlot; /* size 8 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} UnkTexFrame; /* size 8 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ UnkTexFrame *unkC;
} UnkTexAnim; /* size 0x10 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkTexSlot *unk4;
    /* 0x08 */ UnkTexAnim *unk8;
} UnkTexSlots;

/* An object of the pool D_800A0D00 (0xA0 of them, linked by priority). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ void *unk3C;
    /* 0x40 */ UnkSkel *unk40;
    /* 0x44 */ UnkInst *unk44;
    /* 0x48 */ UnkAnimSlots *unk48;
    /* 0x4C */ UnkTexSlots *unk4C;
} UnkObj; /* size 0x50 */

/* A display list command, two words (gbi.h's Gfx, not in include/ yet). */
typedef struct {
    u32 w0;
    u32 w1;
} UnkGfx;

typedef struct {
    s32 m[4][4];
} UnkMtx;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define gW(pkt, a, b)                \
    {                                \
        UnkGfx *_g = (UnkGfx *)(pkt); \
        _g->w0 = (a);                \
        _g->w1 = (b);                \
    }
#define gMoveWd(pkt, index, offset, data) gW(pkt, _SHIFTL(0xBC, 24, 8) | _SHIFTL((offset), 8, 16) | _SHIFTL((index), 0, 8), (u32)(data))
#define gSPSegment(pkt, seg, base) gMoveWd(pkt, 6, (seg) * 4, base)
#define gSPFogPosition(pkt, min, max)                                              \
    gMoveWd(pkt, 8, 0, _SHIFTL(128000 / ((max) - (min)), 16, 16) | _SHIFTL((500 - (min)) * 256 / ((max) - (min)), 0, 16))
#define gDPSetFogColor(pkt, r, g, b, a) \
    gW(pkt, 0xF8000000, _SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8))

/* The texture owners (D_80098C18, 5 of them). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkObj *unk4;
    /* 0x08 */ void **unk8;
    /* 0x0C */ s32 *unkC;
} UnkTexOwner; /* size 0x10 */

/* A vertex (0x10 bytes); unk8/unkA are its texture coordinates. */
typedef struct {
    /* 0x00 */ s16 unk0[3];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 unkC[4];
} UnkVtx; /* size 0x10 */

/* The texture scrolls (D_80098C68, 6 of them). */
typedef struct {
    /* 0x00 */ UnkObj *unk0;
    /* 0x04 */ UnkVtx *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
} UnkScroll; /* size 0x18 */

extern s32 *D_8029F880;
extern Vec3f D_8029F890;
extern Vec3f D_8029F89C;
extern Vec3f D_8029F8A8;
extern s32 D_802A54A0;
extern s32 D_802A54A4;
extern s32 D_802A54A8;
extern s32 D_802A54AC;
extern u32 D_802A54B0;
extern s32 D_802A54B4;
extern s32 D_802A54B8;
extern UnkSkel *D_802A54BC;
extern s32 *D_802A54C0;
extern f32 *D_802A54C4;
extern UnkChunk *D_802A54C8;
extern s32 D_802A54D0;
extern s32 D_802A54D4;
extern s32 D_802A54D8;
extern s32 D_802A54DC;
extern s32 D_802A54E0;
extern s32 D_802A54E4;
extern s32 D_802A54E8;
extern s32 D_802A54EC;
extern s32 D_802A54F0;
extern s32 *D_802A54F4;
extern s32 *D_802A54F8;
extern UnkChan *D_802A54FC;
extern UnkAnim *D_802A5500;
extern UnkTrack *D_802A5504;
void func_8026CBD4(void *);
void *func_80227678(s32);
s32 func_8022769C(s32);
void func_8022D58C(UnkGfx **, s32, s32);
void func_8022DAB0(UnkInst *, UnkGfx **, s32);
void func_80237478(f32 *, f32 *);
void func_8026437C(UnkGfx **, void *, f32, f32, f32, f32, f32, f32, f32, f32, s32);
void func_802926EC(void *);
void func_8029C7A8(f32 m[4][4], f32, f32, f32);
void func_8029C8D0(f32 m[4][4], f32, f32, f32);
void func_8029CA00(f32 m[4][4], f32, f32, f32);
void func_8029CA80(f32 m[4][4], f32, f32, f32);
void guMtxCatF(f32 mf[4][4], f32 nf[4][4], f32 res[4][4]);
void guMtxF2L(f32 mf[4][4], UnkMtx *m);
void guMtxIdentF(f32 mf[4][4]);

extern UnkTexOwner D_80098C18[5];
extern UnkScroll D_80098C68[6];
extern f32 D_80098CF8[][4][4];
extern s32 D_800A0CF8;
extern UnkObj D_800A0D00[0xA0];
extern UnkObj D_800A3F00[];
extern s32 D_8029F600;
extern s32 D_8029F7E0;
extern s32 D_8029F7E4;
extern s32 D_8029F7E8;
extern s32 D_8029F7EC;
extern s32 D_8029F7F0;
extern s32 D_8029F7F4;
extern s32 D_8029F840;
extern s32 D_8029F844;
extern s32 D_8029F848;
extern s32 D_8029F84C;
extern s32 D_8029F850;
extern s32 D_8029F854;
extern s32 D_8029F858[8];
extern s32 D_802A5368;
/* One frame's buffers (D_8014C8D0[2], as in 41FD0.c). */
typedef struct {
    /* 0x00000 */ UnkMtx mtx[0x400];
    /* 0x10000 */ u8 unk10000[4][0x5000];
    /* 0x24000 */ UnkGfx gfx[0x600];
} UnkFrame; /* size 0x27000 */

extern UnkFrame *D_802A538C;
extern s32 D_802A5460;
extern s32 D_802A5464;
extern f32 D_802A5468;
extern f32 D_802A546C;
extern s32 D_802A5470;
extern s32 D_802A5490;
extern s32 D_802AC5C8;

void func_80227EE0(s32 arg0);
void func_80227F88(void);
void func_80227FE8(s32 arg0, s32 arg1, s32 arg2);
void func_80228008(s32 arg0, s32 arg1, s32 arg2);
static s32 func_802280EC(void);
s32 func_802280F4(UnkObj *arg0, s32 arg1);
static void func_8022827C(UnkObj *arg0);
static void func_802284F0(UnkObj *arg0, UnkGfx **arg1);
static s32 func_802284F8(UnkObj *arg0, UnkGfx **arg1);
static void func_80228500(UnkGfx **arg0, UnkObj *arg1);
static s32 func_802289B8(UnkObj *arg0);
void func_802289C0(UnkObj *arg0, UnkGfx **arg1);
void func_802290CC(void);
void func_80229280(s32 arg0);
void func_8022928C(f32 arg0[4][4], f32 arg1[4][4]);
void func_80229448(s32 arg0, s32 arg1, s32 arg2);
void func_8022946C(UnkObj *arg0, s32 arg1);
void func_80229560(UnkObj *arg0);
void func_802295F4(UnkObj *arg0, s32 *arg1, s32 arg2);
void func_80229640(UnkObj *arg0, s32 arg1);
void func_8022979C(UnkObj *arg0, s32 arg1, s32 arg2);
void func_802297B8(UnkObj *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8022984C(UnkObj *arg0, s32 arg1);
void func_8022997C(void);
void func_80229BB4(void);
void func_80229BF4(s32 arg0);
u32 func_80229C10(UnkObj *arg0, s32 arg1, UnkVtx **arg2);
s32 func_80229C90(UnkObj *arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
f32 func_80229D3C(UnkObj *arg0, s32 arg1);
void func_80229D68(UnkObj *arg0);
void func_80229E38(UnkObj *arg0, s32 arg1, s32 arg2);
void func_80229F74(UnkObj *arg0, s32 arg1);
s32 func_8022A0D8(UnkObj *arg0, s32 arg1);
void func_8022A19C(UnkObj *arg0, s32 arg1);
void func_8022A1E8(void *arg0);
UnkObj *func_8022A328(UnkModel *arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4);
void *func_8022A6C4(void *arg0, s32 arg1);
static void func_8022A850(void);
void func_8022A858(void);
void func_8022ABCC(UnkSkel *arg0);
UnkSkel *func_8022AF1C(UnkModel *arg0);
void func_8022BB88(UnkAnim *arg0);
void func_8022C530(UnkAnim *arg0, f32 arg1, s32 arg2);
UnkAnim *func_8022C8B8(UnkInst *arg0, s32 arg1);
void func_8022CF64(UnkInst *arg0);
UnkInst *func_8022D1D0(UnkSkel *arg0, UnkModel *arg1, u32 arg2);

static void func_8022A850(void) {
    s32 i;

    i = 0;
    do {
        D_800A0D00[i].unk0 = 0;
        D_800A0D00[i].unk4 = 0;
        D_800A0D00[i].unk8 = 0;
        D_800A0D00[i].unk3C = NULL;
        i++;
    } while (&D_800A0D00[i] < D_800A3F00);
    D_800A0D00[0].unk3C = NULL;
    D_800A0D00[1].unk3C = NULL;
    D_800A0D00[1].unk8 = 0xA0;
    D_800A0D00[0].unk0 = 1;
    D_800A0D00[1].unk4 = 0;
    D_800A0D00[1].unk0 = -1;
    D_800A0D00[0].unk4 = -1;
}

void func_8022A858(void) {
    s32 i;

    D_802A5460 = 0;
    for (i = 0; i < 5; i++) {
        D_80098C18[i].unk0 = 0;
        D_80098C18[i].unk4 = NULL;
        D_80098C18[i].unk8 = NULL;
        D_80098C18[i].unkC = NULL;
    }
    func_8022A850();
    for (i = 0; i < 6; i++) {
        D_80098C68[i].unk0 = NULL;
    }
}

void *func_8022A6C4(void *arg0, s32 arg1) {
    static UnkModel *D_802A547C;
    static UnkChunk *D_802A5480;
    static u32 D_802A5484;
    static u32 D_802A5488;
    static s32 D_802A548C;
    s32 kind;

    if (arg0) {}
    D_802A548C = 0;
    D_802A5488 = 0;
    kind = -1;
    if (arg0 != (void *)-1) {
        D_802A547C = arg0;
        D_802A5480 = D_802A547C->unkC;
        for (D_802A5484 = 0; D_802A5484 < D_802A547C->unk4; D_802A5484++) {
            if (D_802A5480[D_802A5484].unk0 < 0x10) {
                D_802A5488 = D_802A5484;
                kind = 2;
                break;
            }
        }
        for (D_802A5484 = 0; D_802A5484 < D_802A547C->unk4; D_802A5484++) {
            if (D_802A5480[D_802A5484].unk0 == 1) {
                D_802A5488 = D_802A5484;
                kind = 2;
                break;
            }
        }
        for (D_802A5484 = 0; D_802A5484 < D_802A547C->unk4; D_802A5484++) {
            if (D_802A5480[D_802A5484].unk0 == 3) {
                kind = 3;
                break;
            }
        }
        if (kind == -1) {
            if (D_802A5480->unk0 >= 0x10) {
                kind = 4;
            }
        }
    }
    D_8029F850 = kind;
    return func_8022A328(arg0, arg1, kind | 0, D_802A5488, 0);
}

UnkObj *func_8022A328(UnkModel *arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4) {
    static s32 D_802A5474;
    static s32 D_802A5478;
    UnkSkel *skel;
    UnkChunk *c;

    D_802A5474 = 2;
    D_802A5478 = 0;
    if (arg1) {}
    while (D_800A0D00[D_802A5474].unk3C != NULL) {
        if (++D_802A5474 >= 0xA1) {
            break;
        }
    }
    if (arg1 >= 0xA0) {
        return NULL;
    }
    if (D_802A5474 >= 0xA0) {
        return NULL;
    }
    while (arg1 >= D_800A0D00[D_802A5478].unk8) {
        D_802A5478 = D_800A0D00[D_802A5478].unk0;
    }
    D_800A0D00[D_802A5474].unk8 = arg1;
    D_800A0D00[D_802A5474].unk4 = D_800A0D00[D_802A5478].unk4;
    D_800A0D00[D_802A5478].unk4 = D_802A5474;
    D_800A0D00[D_802A5474].unk0 = D_802A5478;
    D_800A0D00[D_800A0D00[D_802A5474].unk4].unk0 = D_802A5474;
    if (arg2 == 0) {
        D_800A0D00[D_802A5474].unkC = 0x800;
    } else if (arg2 == 1) {
        D_800A0D00[D_802A5474].unkC = 2;
    } else if (arg2 == 2) {
        D_800A0D00[D_802A5474].unkC = 4;
    } else if (arg2 == 3) {
        D_800A0D00[D_802A5474].unkC = 0xC;
    } else if (arg2 == 4) {
        D_800A0D00[D_802A5474].unkC = 0x10;
    }
    D_800A0D00[D_802A5474].unk40 = NULL;
    D_800A0D00[D_802A5474].unk44 = NULL;
    D_800A0D00[D_802A5474].unk48 = NULL;
    D_800A0D00[D_802A5474].unk3C = arg0;
    D_800A0D00[D_802A5474].unk38 = arg3;
    if ((D_800A0D00[D_802A5474].unkC & 4) && (D_800A0D00[D_802A5474].unkC & 8)) {
        skel = func_8022AF1C(arg0);
        D_800A0D00[D_802A5474].unk40 = skel;
        D_800A0D00[D_802A5474].unk44 = func_8022D1D0(skel, arg0, arg3);
        func_80229F74(&D_800A0D00[D_802A5474], 1);
        func_80229E38(&D_800A0D00[D_802A5474], arg4, 0);
    }
    if (arg2 == 4) {
        c = &arg0->unkC[arg3];
        if (c) {}
        D_800A0D00[D_802A5474].unk20 = 0.0f;
        D_800A0D00[D_802A5474].unk10 = 0.0f;
        D_800A0D00[D_802A5474].unk24 = 0.0f;
        D_800A0D00[D_802A5474].unk14 = 0.0f;
        D_800A0D00[D_802A5474].unk18 = D_800A0D00[D_802A5474].unk28 = (u32)((u16 *)&c->unk4)[0];
        D_800A0D00[D_802A5474].unk1C = D_800A0D00[D_802A5474].unk2C = (u32)((u16 *)&c->unk4)[1];
    } else {
        D_800A0D00[D_802A5474].unk10 = 0;
        D_800A0D00[D_802A5474].unk14 = 0;
        D_800A0D00[D_802A5474].unk18 = 0;
        D_800A0D00[D_802A5474].unk1C = 0;
        D_800A0D00[D_802A5474].unk20 = 0;
        D_800A0D00[D_802A5474].unk24 = 0;
        D_800A0D00[D_802A5474].unk28 = 1;
        D_800A0D00[D_802A5474].unk2C = 1;
        D_800A0D00[D_802A5474].unk30 = 1;
    }
    D_800A0D00[D_802A5474].unk34 = D_802AC5C8;
    D_800A0D00[D_802A5474].unk36 = -1;
    D_800A0D00[D_802A5474].unk4C = NULL;
    D_802A5460++;
    return &D_800A0D00[D_802A5474];
}

void func_8022A1E8(void *arg0) {
    s32 idx;
    UnkObj *p;
    s32 i;
    s32 prev;

    idx = ((u32)arg0 - (u32)D_800A0D00) / sizeof(UnkObj);
    p = &D_800A0D00[idx];
    if (p->unkC & 8) {
        func_80229D68(arg0);
    }
    if (p->unk4C != NULL) {
        func_80229560(arg0);
    }
    for (i = 0; i != 6; i++) {
        if (arg0 == D_80098C68[i].unk0) {
            D_80098C68[i].unk0 = NULL;
            break;
        }
    }
    func_802926EC(arg0);
    p->unk3C = NULL;
    prev = p->unk4;
    i = p->unk0;
    D_800A0D00[prev].unk0 = i;
    D_800A0D00[i].unk4 = prev;
    p->unk8 = 0;
    if (idx == D_802A5464) {
        D_802A5464 = p->unk0;
    }
    D_802A5460--;
}

void func_8022A19C(UnkObj *arg0, s32 arg1) {
    if (arg0->unkC & 8) {
        func_80229D68(arg0);
    }
    arg0->unk38 = arg1;
}

s32 func_8022A0D8(UnkObj *arg0, s32 arg1) {
    UnkAnimSlots *t;

    if (arg0->unk48 == NULL) {
        func_80229F74(arg0, 1);
        func_80229E38(arg0, arg1, 0);
    } else {
        t = arg0->unk48;
        t->unk0++;
        t->unk4 = realloc(t->unk4, arg0->unk48->unk0 * sizeof(UnkAnimSlot));
        t->unk4[t->unk0 - 1].unk0 = NULL;
        func_80229E38(arg0, arg1, arg0->unk48->unk0 - 1);
    }
    return arg0->unk48->unk0 - 1;
}

void func_80229F74(UnkObj *arg0, s32 arg1) {
    UnkAnimSlots *t;
    s32 i;

    if (arg0->unk48 != NULL) {
        func_80229D68(arg0);
    }
    t = malloc(sizeof(UnkAnimSlots));
    t->unk0 = arg1;
    t->unk4 = malloc(arg1 * sizeof(UnkAnimSlot));
    for (i = 0; i < arg1; i++) {
        t->unk4[i].unk0 = NULL;
    }
    if (arg0->unk40 == NULL) {
        arg0->unk40 = func_8022AF1C(arg0->unk3C);
    }
    if (arg0->unk44 == NULL) {
        arg0->unk44 = func_8022D1D0(arg0->unk40, arg0->unk3C, arg0->unk38);
    }
    arg0->unk48 = t;
}

void func_80229E38(UnkObj *arg0, s32 arg1, s32 arg2) {
    UnkAnimSlots *t;
    s32 i;

    t = arg0->unk48;
    if (t->unk4[arg2].unk0 != NULL) {
        func_8022BB88(t->unk4[arg2].unk0);
        t->unk4[arg2].unk0 = NULL;
    }
    if (arg1 == -1) {
        arg0->unkC &= ~8;
        for (i = 0; i < t->unk0; i++) {
            if (t->unk4[i].unk0 != NULL) {
                arg0->unkC |= 8;
                break;
            }
        }
    } else {
        t->unk4[arg2].unk0 = func_8022C8B8(arg0->unk44, arg1);
        t->unk4[arg2].unk4 = 0.0f;
        t->unk4[arg2].unk8 = 0;
        arg0->unkC |= 8;
        arg0->unkC &= ~0x20000;
    }
}

void func_80229D68(UnkObj *arg0) {
    UnkAnimSlots *t;
    s32 i;

    t = arg0->unk48;
    for (i = 0; i < t->unk0; i++) {
        if (t->unk4[i].unk0 != NULL) {
            func_8022BB88(t->unk4[i].unk0);
        }
    }
    free(t->unk4);
    free(t);
    func_8022CF64(arg0->unk44);
    func_8022ABCC(arg0->unk40);
    arg0->unk40 = NULL;
    arg0->unk44 = NULL;
    arg0->unkC &= ~8;
    arg0->unk48 = NULL;
}

f32 func_80229D3C(UnkObj *arg0, s32 arg1) {
    return arg0->unk48->unk4[arg1].unk0->unk8;
}

s32 func_80229C90(UnkObj *arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_80098C68[i].unk0 == NULL) {
            D_80098C68[i].unk0 = arg0;
            D_80098C68[i].unkC = arg2;
            D_80098C68[i].unk10 = arg3;
            D_80098C68[i].unkE = arg4;
            D_80098C68[i].unk12 = arg5;
            D_80098C68[i].unk8 = func_80229C10(arg0, arg1, &D_80098C68[i].unk4);
            D_80098C68[i].unk14 = 0;
            D_80098C68[i].unk16 = 0;
            return i;
        }
    }
    return -1;
}

u32 func_80229C10(UnkObj *arg0, s32 arg1, UnkVtx **arg2) {
    UnkModel *model;
    UnkChunk *chunks;
    UnkGfx *dl;
    u32 first;
    u32 w;
    s32 i;

    if (!arg1) {}
    model = arg0->unk3C;
    if (!arg2) {}
    chunks = model->unkC;
    if (!chunks) {}
    dl = (UnkGfx *)((u8 *)model + chunks[arg1].unk8);
    first = dl->w1;
    for (i = 0; i < 2; i++) {
        while (*(u8 *)dl != 4) {
            dl++;
        }
        dl++;
    }
    w = dl[-1].w1;
    if (!arg0) {}
    *arg2 = (UnkVtx *)((w & 0xFFFFFF) + (u32)model);
    return (first - w) >> 4;
}

void func_80229BF4(s32 arg0) {
    D_80098C68[arg0].unk0 = NULL;
}

void func_80229BB4(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        D_80098C68[i].unk0 = NULL;
    }
}

void func_8022997C(void) {
    UnkScroll *s;
    s32 j;

    s = D_80098C68; do {
        if (s->unk0 != NULL) {
            if ((s->unkC > 0 && s->unk14 + s->unkC < s->unk10) || (s->unkC < 0 && s->unk10 < s->unk14 + s->unkC)) {
                for (j = 0; j < s->unk8; j++) {
                    s->unk4[j].unk8 += s->unkC;
                }
                s->unk14 += s->unkC;
            } else {
                for (j = 0; j < s->unk8; j++) {
                    s->unk4[j].unk8 -= s->unk14;
                }
                s->unk14 = 0;
            }
            if ((s->unkE > 0 && s->unk16 + s->unkE < s->unk12) || (s->unkE < 0 && s->unk12 < s->unk16 + s->unkE)) {
                for (j = 0; j < s->unk8; j++) {
                    s->unk4[j].unkA += s->unkE;
                }
                s->unk16 += s->unkE;
            } else {
                for (j = 0; j < s->unk8; j++) {
                    s->unk4[j].unkA -= s->unk16;
                }
                s->unk16 = 0;
            }
            func_80297D60(s->unk4, s->unk8 * sizeof(UnkVtx));
        }
        s++;
    } while (s != (UnkScroll *)D_80098CF8);
}

void func_8022984C(UnkObj *arg0, s32 arg1) {
    UnkTexSlots *t;
    s32 i;

    t = malloc(sizeof(UnkTexSlots));
    t->unk0 = arg1;
    t->unk4 = malloc(arg1 * sizeof(UnkTexSlot));
    t->unk8 = NULL;
    for (i = 0; i < arg1; i++) {
        t->unk4[i].unk4 = 0;
        t->unk4[i].unk0 = NULL;
    }
    arg0->unk4C = t;
}

void func_802297B8(UnkObj *arg0, s32 arg1, s32 arg2, s32 arg3) {
    UnkTexSlots *t;

    t = arg0->unk4C;
    if (t->unk4[arg2].unk0 != NULL) {
        func_8026CBD4(t->unk4[arg2].unk0);
    }
    t->unk4[arg2].unk0 = func_8026CE28(arg1);
    t->unk4[arg2].unk4 = arg3;
}

void func_8022979C(UnkObj *arg0, s32 arg1, s32 arg2) {
    UnkTexSlots *t;

    t = arg0->unk4C;
    t->unk4[arg1].unk4 = arg2;
}

void func_80229640(UnkObj *arg0, s32 arg1) {
    UnkTexSlots *t;
    s32 i;

    t = arg0->unk4C;
    t->unk8 = malloc(arg1 * sizeof(UnkTexAnim));
    for (i = 0; i < arg1; i++) {
        t->unk8[i].unk8 = 0;
        t->unk8[i].unk4 = 0;
        t->unk8[i].unkC = NULL;
    }
}

void func_802295F4(UnkObj *arg0, s32 *arg1, s32 arg2) {
    UnkTexSlots *t;

    t = arg0->unk4C;
    t->unk8[arg2].unk0 = *arg1;
    t->unk8[arg2].unkC = (UnkTexFrame *)(arg1 + 1);
    t->unk8[arg2].unk4 = 0;
    t->unk8[arg2].unk8 = 0;
}

void func_80229560(UnkObj *arg0) {
    UnkTexSlots *t;
    s32 i;

    t = arg0->unk4C;
    for (i = 0; i < t->unk0; i++) {
        func_8026CBD4(t->unk4[i].unk0);
    }
    free(t->unk4);
    free(t);
    arg0->unk4C = NULL;
}

void func_8022946C(UnkObj *arg0, s32 arg1) {
    s32 idx;
    s32 i;
    UnkObj *p;
    s32 prev;

    idx = ((u32)arg0 - (u32)D_800A0D00) / sizeof(UnkObj);
    i = D_800A0D00[idx].unk0;
    p = &D_800A0D00[idx];
    prev = p->unk4;
    D_800A0D00[i].unk4 = prev;
    D_800A0D00[prev].unk0 = p->unk0;
    if (p->unk8 < arg1) {
        i = p->unk0;
    }
    p->unk8 = arg1;
    while (arg1 >= D_800A0D00[i].unk8) {
        i = D_800A0D00[i].unk0;
    }
    p->unk4 = D_800A0D00[i].unk4;
    D_800A0D00[i].unk4 = idx;
    p->unk0 = i;
    D_800A0D00[p->unk4].unk0 = idx;
}

void func_80229448(s32 arg0, s32 arg1, s32 arg2) {
    for (arg2 = 0; arg2 * 4 != 16; arg2++) {
    }
}

void func_8022928C(f32 arg0[4][4], f32 arg1[4][4]) {
    f32 m00 = arg1[0][0];
    f32 m01 = arg1[0][1];
    f32 m02 = arg1[0][2];
    f32 m10 = arg1[1][0];
    f32 m11 = arg1[1][1];
    f32 m12 = arg1[1][2];
    f32 m20 = arg1[2][0];
    f32 m21 = arg1[2][1];
    f32 m22 = arg1[2][2];
    f32 c00;
    f32 c10;
    f32 c20;
    f32 det;

    c00 = m11 * m22 - m12 * m21;
    c10 = m12 * m20 - m10 * m22;
    c20 = m10 * m21 - m11 * m20;
    det = m00 * c00 + m01 * c10 + m02 * c20;
    if (det == 0.0f) {
        return;
    }
    {
        det = 1.0f / det;
        arg0[0][0] = c00 * det;
        arg0[1][0] = c10 * det;
        arg0[2][0] = c20 * det;
        arg0[0][1] = (m02 * m21 - m01 * m22) * det;
        arg0[0][2] = (m01 * m12 - m02 * m11) * det;
        arg0[1][1] = (m00 * m22 - m02 * m20) * det;
        arg0[1][2] = (m02 * m10 - m00 * m12) * det;
        arg0[2][1] = (m01 * m20 - m00 * m21) * det;
        arg0[2][2] = (m00 * m11 - m01 * m10) * det;
        arg0[0][3] = 0.0f;
        arg0[1][3] = 0.0f;
        arg0[2][3] = 0.0f;
        arg0[3][0] = 0.0f;
        arg0[3][1] = 0.0f;
        arg0[3][2] = 0.0f;
        arg0[3][3] = 1.0f;
    }
}

void func_80229280(s32 arg0) {
    D_8029F84C = arg0;
}

void func_802290CC(void) {
    s32 i;
    UnkGfx *dls[4];
    UnkObj *obj;

    D_802A5470 = -1;
    D_8029F848 = 0;
    D_802A5490 = -1;
    D_800A0CF8 = 0;
    guMtxIdentF(D_80098CF8[0]);
    for (i = 0; i < 4; i++) {
        dls[i] = func_80227678(i);
    }
    func_80237478(&D_802A5468, &D_802A546C);
    for (i = 0; i < 8; i++) {
        D_8029F844 = 0;
        obj = &D_800A0D00[D_8029F844];
        D_802A5464 = obj->unk0;
        while (D_802A5464 != -1) {
            if (obj->unk3C != NULL && (obj->unkC & 0x490) == D_8029F858[i]) {
                func_802289C0(obj, &dls[obj->unk34]);
            }
            D_8029F844 = D_802A5464;
            obj = &D_800A0D00[D_8029F844];
            D_802A5464 = obj->unk0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (func_8022769C(i)) {
            gW(dls[i], 0xB8000000, 0);
        }
    }
}

static s32 func_802289B8(UnkObj *arg0) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (arg0 == D_80098C18[i].unk4) {
            return i;
        }
    }
    return -1;
}

static void func_80228500(UnkGfx **arg0, UnkObj *arg1) {
    UnkGfx *gfx;

    gfx = *arg0;
    if (D_802A5490 != arg1->unk34 || (arg1->unkC & 2)) {
        D_802A5470 = -1;
        D_8029F848 = -1;
    }
    D_802A5490 = arg1->unk34;
    if (arg1->unkC & 0x8000) {
        gW(gfx++, 0xB900031D, 0x507BD8);
        D_802A5470 = 4;
        gW(gfx++, 0xFB000000, (arg1->unk36 & 0xFF) | ~0xFF);
    } else if ((arg1->unkC & 0x80) && (arg1->unkC & 0x1000)) {
        if (D_802A5470 != 5) {
            gW(gfx++, 0xB900031D, 0x055079F8);
            gW(gfx++, 0xF8000000, arg1->unk36 & 0xFF);
            D_802A5470 = 5;
        }
    } else if ((arg1->unkC & 0x80) && arg1->unk36 != -1) {
        gW(gfx++, 0xB900031D, 0x055079D8);
        D_802A5470 = 2;
        gW(gfx++, 0xF8000000, (arg1->unk36 & 0xFF) | ~0xFF);
    } else if (arg1->unkC & 0x80) {
        if (D_802A5470 != 1) {
            gW(gfx++, 0xB900031D, 0x5049D8);
            D_802A5470 = 1;
        }
    } else if (arg1->unkC & 0x40000) {
        if (D_802A5470 != 6) {
            gW(gfx++, 0xB900031D, 0x5010F8);
            gW(gfx++, 0xFB000000, arg1->unk36 & 0xFF);
            gW(gfx++, 0xB9000002, 3);
            D_802A5470 = 6;
        }
    } else if (D_8029F7E0 != 0) {
        if (D_802A5470 != 3) {
            gW(gfx++, 0xB900031D, 0xFA005078);
            gW(gfx++, 0xB7000000, 0x10000);
            gW(gfx++, 0xB9000002, 1);
            D_802A5470 = 3;
        }
        gSPFogPosition(gfx++, D_8029F7E4, D_8029F7E8);
        gDPSetFogColor(gfx++, D_8029F7EC, D_8029F7F0, D_8029F7F4, 0x80);
    } else {
        if (D_802A5470 != 0) {
            gW(gfx++, 0xB900031D, 0x553078);
            D_802A5470 = 0;
        }
    }
    if (D_802A5470 != 3) {
        gW(gfx++, 0xB6000000, 0x10000);
    }
    if (D_802A5470 != 3 && D_802A5470 != 6) {
        gW(gfx++, 0xB9000002, 0);
    }
    if (arg1->unkC & 0x200) {
        if (D_8029F848 != 1) {
            gW(gfx++, 0xBA000C02, 0);
            D_8029F848 = 1;
        }
    } else if (D_8029F848 != 0) {
        gW(gfx++, 0xBA000C02, 0x2000);
        D_8029F848 = 0;
    }
    *arg0 = gfx;
}

static s32 func_802284F8(UnkObj *arg0, UnkGfx **arg1) {
    UnkGfx *gfx;
    f32 mf[4][4];
    s32 pushed;
    f32 rx;
    f32 ry;
    f32 rz;
    s32 pad[2];

    pushed = 0;
    gfx = *arg1;
    guMtxIdentF(mf);
    guMtxF2L(mf, &D_802A538C->mtx[D_802A5368]);
    gW(gfx++, 0x01020040, (u32)&D_802A538C->mtx[D_802A5368]);
    D_802A5368++;
    func_8029CA80(mf, arg0->unk10, arg0->unk14, arg0->unk18);
    rx = arg0->unk1C;
    ry = ((arg0->unkC & 0x2000) ? D_802A5468 : 0) + arg0->unk20;
    rz = arg0->unk24;
    if (rx != 0.0f || ry != 0.0f || rz != 0.0f) {
        if (arg0->unkC & 0x10000) {
            func_8029C7A8(mf, rx, ry, rz);
        } else {
            func_8029C8D0(mf, rx, ry, rz);
        }
        pushed = 1;
    }
    if (pushed) {
        D_800A0CF8++;
        guMtxCatF(mf, D_80098CF8[D_800A0CF8 - 1], D_80098CF8[D_800A0CF8]);
    }
    if (arg0->unk28 != 1.0f || arg0->unk2C != 1.0f || arg0->unk30 != 1.0f) {
        func_8029CA00(mf, arg0->unk28, arg0->unk2C, arg0->unk30);
    }
    guMtxF2L(mf, &D_802A538C->mtx[D_802A5368]);
    gW(gfx++, 0x01060040, (u32)&D_802A538C->mtx[D_802A5368]);
    D_802A5368++;
    *arg1 = gfx;
    return pushed;
}

static void func_802284F0(UnkObj *arg0, UnkGfx **arg1) {
    UnkGfx *gfx;
    s32 i;
    UnkGfx *g;
    UnkTexAnim *anim;
    UnkModel *model;
    s32 idx;
    s32 cur;
    s32 count;

    gfx = *arg1;
    for (i = 0; i < arg0->unk4C->unk0; i++) {
        model = arg0->unk4C->unk4[i].unk0;
        if (arg0->unk4C->unk8 == NULL) {
            idx = arg0->unk4C->unk4[i].unk4;
            gSPSegment(gfx++, i + 3, (u8 *)model + model->unkC[idx].unk8);
        } else {
            g = gfx;
            anim = &arg0->unk4C->unk8[i];
            cur = anim->unk4;
            count = anim->unk8;
            if (count >= anim->unkC[cur].unk4) {
                anim->unk8 = 0;
                if (anim->unk4 == anim->unk0 - 1) {
                    anim->unk4 = 0;
                } else {
                    anim->unk4++;
                }
            } else {
                anim->unk8 = count + 1;
            }
            gfx = g + 1;
            gSPSegment(g, i + 3, (u8 *)model + model->unkC[anim->unkC[anim->unk4].unk0].unk8);
        }
    }
    *arg1 = gfx;
}

static void func_8022827C(UnkObj *arg0) {
    s32 n;
    s32 run;
    s32 i;

    n = 0;
    run = 0;
    if (((D_8029F600 & 1) && (D_8029F854 & 1)) || !(arg0->unkC & 0x20000)) {
        run = 1;
        arg0->unkC |= 0x20000;
    } else {
        arg0->unkC &= ~0x20000;
    }
    for (i = 0; i < arg0->unk48->unk0; i++) {
        if (arg0->unk48->unk4[i].unk0 != NULL) {
            if (!(arg0->unkC & 0x4000)) {
                arg0->unk48->unk4[i].unk8 = arg0->unkC;
            }
            if (run) {
                func_8022C530(arg0->unk48->unk4[i].unk0, arg0->unk48->unk4[i].unk4, n++);
            }
            if (!(arg0->unk48->unk4[i].unk8 & 0x40)) {
                arg0->unk48->unk4[i].unk4 += 1.0f;
                if (arg0->unk48->unk4[i].unk0->unk8 <= arg0->unk48->unk4[i].unk4) {
                    if (arg0->unk48->unk4[i].unk8 & 0x20) {
                        arg0->unk48->unk4[i].unk4 = arg0->unk48->unk4[i].unk0->unk8 - 0.001f;
                        arg0->unk48->unk4[i].unk8 |= 0x40;
                        arg0->unk48->unk4[i].unk8 &= ~0x20000;
                    } else {
                        arg0->unk48->unk4[i].unk4 -= arg0->unk48->unk4[i].unk0->unk8;
                    }
                }
                if (!(arg0->unkC & 0x4000)) {
                    arg0->unkC = arg0->unk48->unk4[i].unk8;
                }
            }
        }
        if (arg0->unk48->unk0 == 1) {
            arg0->unkC = arg0->unk48->unk4[0].unk8;
        }
    }
    D_8029F854++;
}

void func_802289C0(UnkObj *arg0, UnkGfx **arg1) {
    UnkGfx *gfx;
    s32 pad;
    s32 pushed;
    void (*fn)(UnkObj *, UnkGfx **);

    if (arg0->unkC & 1) {
        return;
    }
    if (arg0->unk3C == (void *)-1) {
        return;
    }
    gfx = *arg1;
    D_8029F840 = func_802289B8(arg0);
    func_80228500(&gfx, arg0);
    if (!(arg0->unkC & 0x10)) {
        pushed = func_802284F8(arg0, &gfx);
    }
    if (arg0->unk4C != NULL) {
        func_802284F0(arg0, &gfx);
    }
    if (arg0->unkC & 2) {
        D_802A5470 = -1;
        fn = (void (*)(UnkObj *, UnkGfx **))arg0->unk3C;
        fn(arg0, &gfx);
    } else if ((arg0->unkC & 4) && (arg0->unkC & 8)) {
        if (D_8029F84C == 0 || (arg0->unkC & 0x100)) {
            func_8022827C(arg0);
        }
        func_8022DAB0(arg0->unk44, &gfx, (s32)arg0->unk3C);
    } else if (arg0->unkC & 4) {
        func_8022D58C(&gfx, (s32)arg0->unk3C, arg0->unk38);
    } else if (arg0->unkC & 0x10) {
        if (D_802A5470 != 1) {
            gW(gfx++, 0xB9000501, 0);
        }
        gW(gfx++, 0xB9000401, 0);
        gW(gfx++, 0xB9000802, 0);
        func_8026437C(&gfx, arg0->unk3C, arg0->unk10, arg0->unk14, arg0->unk18, arg0->unk1C, arg0->unk20,
                      arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk38);
        if (D_802A5470 != 1) {
            gW(gfx++, 0xB9000501, 0x20);
        }
        gW(gfx++, 0xB9000401, 0x10);
    } else if (arg0->unkC & 0x800) {
        gW(gfx++, 0x06000000, (u32)arg0->unk3C);
    }
    if (!(arg0->unkC & 0x10)) {
        gW(gfx++, 0xBD000000, 0);
        if (pushed) {
            D_800A0CF8--;
        }
    }
    *arg1 = gfx;
}

static s32 func_802280EC(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (D_80098C18[i].unk4 == NULL) {
            return i;
        }
    }
    return -1;
}

s32 func_802280F4(UnkObj *arg0, s32 arg1) {
    s32 slot;
    s32 i;

    slot = func_802280EC();
    D_80098C18[slot].unk4 = arg0;
    D_80098C18[slot].unk0 = arg1;
    D_80098C18[slot].unk8 = malloc(arg1 * 4);
    D_80098C18[slot].unkC = malloc(arg1 * 4);
    for (i = 0; i < arg1; i++) {
        D_80098C18[slot].unk8[i] = NULL;
        D_80098C18[slot].unkC[i] = 0;
    }
    return slot;
}

void func_80228008(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == -1) {
        func_8026CBD4(D_80098C18[arg0].unk8[arg1]);
        D_80098C18[arg0].unk8[arg1] = NULL;
        return;
    }
    if (D_80098C18[arg0].unk8[arg1] != NULL) {
        func_8026CBD4(D_80098C18[arg0].unk8[arg1]);
    }
    D_80098C18[arg0].unk8[arg1] = func_8026CE28(arg2);
}

void func_80227FE8(s32 arg0, s32 arg1, s32 arg2) {
    D_80098C18[arg0].unkC[arg1] = arg2;
}

void func_80227F88(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (D_80098C18[i].unk4 != NULL) {
            func_80227EE0(i);
        }
    }
}

void func_80227EE0(s32 arg0) {
    UnkTexOwner *p;
    s32 i;

    p = &D_80098C18[arg0];
    for (i = 0; i < p->unk0; i++) {
        func_8026CBD4(p->unk8[i]);
        p->unk8[i] = NULL;
    }
    free(p->unk8);
    free(p->unkC);
    p->unk4 = NULL;
    p->unk0 = 0;
}
