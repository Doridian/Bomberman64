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
 * differing words: us 795, eu 795, jp 795
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
 * - func_8022A6C4: the first two chunk searches use a local index and a
 *   `chunks` local (the original walks model+12 with a pointer); the
 *   third stores D_802A547C and D_802A5484 on both exits.
 * - func_8022946C: `i = D_800A0D00[idx].unk0` before `p = ...` (i first
 *   seen first takes v1). func_8022997C: `s = D_80098C68; do {` on one
 *   line orders the preheader's addiu s1 before addiu s0.
 * - func_8022A858: the pool loop is an index do-while tested against
 *   the end symbol (`&D_800A0D00[i] < D_800A3F00`: not unrolled, base
 *   re-materialised after it), and the D_80098C68 clear is written out
 *   in it (the call to func_80229BB4, inlined, schedules differently).
 *
 * Left:
 * - func_802289C0 (the draw loop, 431): the original keeps obj in s2
 *   with a 0x160 frame (ours 0x140, obj in t4 and spilled); its texture
 *   loop spills obj to 0xB0(sp), keeps 0xBC000000 in t5 with its own
 *   ori 6, and strength-reduces the slot offset.
 * - func_8022A328 (166): mostly registers. The original keeps j in t0
 *   for the two failure exits (ours stores zero and merges them) and
 *   re-materialises the pool base after the free-slot search.
 * - func_8022928C (92, the 3x3 inverse): nine element locals and
 *   `f32 c[4]` give the original's loads; its frame is 120 (ours 104).
 * - func_8022A6C4 (80): the original's third search keeps D_802A547C
 *   and D_802A5484 in registers (stores on each exit, a duplicate pair
 *   IDO merges in ours); a global loop counter, static or not, isn't
 *   promoted here.
 * - func_80229C10 (18): a rotation of a0/a1/a3/t0/t1 (the original's
 *   dl a3, first t0, i t1, 2 in a0); `if (!chunks) {}` keeps model+12 a
 *   value of its own. func_80229448 (8: the original keeps an empty
 *   4-step loop after storing its arguments; IDO deletes ours).
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
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 *unkC;
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
extern UnkMtx *D_802A538C;
extern s32 D_802A5460;
extern s32 D_802A5464;
extern f32 D_802A5468;
extern f32 D_802A546C;
extern s32 D_802A5470;
extern s32 D_802A5474;
extern s32 D_802A5478;
extern UnkModel *D_802A547C;
extern UnkChunk *D_802A5480;
extern u32 D_802A5484;
extern u32 D_802A5488;
extern s32 D_802A548C;
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
void func_80229448(s32 arg0, s32 arg1);
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
    UnkModel *model;
    UnkChunk *chunks;
    s32 kind;
    u32 idx;
    u32 i;

    D_802A548C = 0;
    idx = 0;
    kind = -1;
    if (arg0 != (void *)-1) {
        model = arg0;
        chunks = model->unkC;
        for (i = 0; i < model->unk4; i++) {
            if (chunks[i].unk0 < 0x10) {
                idx = i;
                kind = 2;
                break;
            }
        }
        for (i = 0; i < model->unk4; i++) {
            if (chunks[i].unk0 == 1) {
                idx = i;
                kind = 2;
                break;
            }
        }
        i = 0;
        D_802A5484 = i;
        D_802A547C = model;
        for (; i < model->unk4; i++) {
            if (chunks[i].unk0 == 3) {
                D_802A547C = model;
                D_802A5484 = i;
                kind = 3;
                goto found;
            }
        }
        D_802A547C = model;
        D_802A5484 = i;
    found:
        D_802A5480 = chunks;
        if (kind == -1) {
            D_802A5480 = chunks;
            if (chunks->unk0 >= 0x10) {
                kind = 4;
            }
        }
    }
    D_8029F850 = kind;
    D_802A5488 = idx;
    return func_8022A328(arg0, arg1, kind, idx, 0);
}

UnkObj *func_8022A328(UnkModel *arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4) {
    s32 i;
    s32 j;
    UnkObj *p;
    UnkSkel *skel;
    f32 f;

    j = 0;
    i = 2;
    while (D_800A0D00[i].unk3C != NULL) {
        if (++i >= 0xA1) {
            break;
        }
    }
    if (arg1 >= 0xA0) {
        D_802A5478 = j;
        D_802A5474 = i;
        return NULL;
    }
    if (i < 0xA0) {
    } else {
        D_802A5478 = j;
        D_802A5474 = i;
        return NULL;
    }
    p = &D_800A0D00[i];
    while (arg1 >= D_800A0D00[j].unk8) {
        j = D_800A0D00[j].unk0;
    }
    p->unk8 = arg1;
    p->unk4 = D_800A0D00[j].unk4;
    D_800A0D00[j].unk4 = i;
    p->unk0 = j;
    D_800A0D00[p->unk4].unk0 = i;
    D_802A5474 = i;
    D_802A5478 = j;
    if (arg2 == 0) {
        p->unkC = 0x800;
    } else if (arg2 == 1) {
        p->unkC = 2;
    } else if (arg2 == 2) {
        p->unkC = 4;
    } else if (arg2 == 3) {
        p->unkC = 0xC;
    } else if (arg2 == 4) {
        p->unkC = 0x10;
    }
    p->unk40 = NULL;
    p->unk44 = NULL;
    p->unk48 = NULL;
    p->unk3C = arg0;
    p->unk38 = arg3;
    if ((p->unkC & 4) && (p->unkC & 8)) {
        skel = func_8022AF1C(arg0);
        D_800A0D00[D_802A5474].unk40 = skel;
        D_800A0D00[D_802A5474].unk44 = func_8022D1D0(skel, arg0, arg3);
        func_80229F74(&D_800A0D00[D_802A5474], 1);
        func_80229E38(&D_800A0D00[D_802A5474], arg4, 0);
        p = &D_800A0D00[(u32)D_802A5474];
    }
    if (arg2 == 4) {
        p->unk20 = 0.0f;
        p->unk10 = 0.0f;
        p->unk24 = 0.0f;
        p->unk14 = 0.0f;
        p->unk18 = p->unk28 = (u32)((u16 *)&arg0->unkC[arg3].unk4)[0];
        p->unk1C = p->unk2C = (u32)((u16 *)&arg0->unkC[arg3].unk4)[1];
    } else {
        p->unk10 = 0.0f;
        p->unk14 = 0.0f;
        p->unk18 = 0.0f;
        p->unk1C = 0.0f;
        p->unk20 = 0.0f;
        p->unk24 = 0.0f;
        p->unk28 = 1.0f;
        p->unk2C = 1.0f;
        p->unk30 = 1.0f;
    }
    p->unk36 = -1;
    p->unk4C = NULL;
    D_802A5460++;
    p->unk34 = D_802AC5C8;
    return p;
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
    *arg2 = (UnkVtx *)((u8 *)model + (w & 0xFFFFFF));
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
    t->unk8[arg2].unkC = arg1 + 1;
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

void func_80229448(s32 arg0, s32 arg1) {
    s32 i;
    s32 *p;

    p = &arg0;
    for (i = 0; i < 4; i++) {
        p[i] = p[i];
    }
}

void func_8022928C(f32 arg0[4][4], f32 arg1[4][4]) {
    f32 m00;
    f32 m01;
    f32 m02;
    f32 m10;
    f32 m11;
    f32 m12;
    f32 m20;
    f32 m21;
    f32 m22;
    f32 c[4];
    f32 inv;

    m11 = arg1[1][1];
    m22 = arg1[2][2];
    m12 = arg1[1][2];
    m21 = arg1[2][1];
    m20 = arg1[2][0];
    m10 = arg1[1][0];
    m00 = arg1[0][0];
    m01 = arg1[0][1];
    m02 = arg1[0][2];
    c[3] = m11 * m22 - m12 * m21;
    c[2] = m12 * m20 - m10 * m22;
    c[1] = m10 * m21 - m11 * m20;
    c[0] = m00 * c[3] + m01 * c[2] + m02 * c[1];
    if (c[0] != 0.0f) {
        inv = 1.0f / c[0];
        arg0[0][0] = c[3] * inv;
        arg0[1][0] = c[2] * inv;
        arg0[0][3] = 0.0f;
        arg0[1][3] = 0.0f;
        arg0[2][3] = 0.0f;
        arg0[3][0] = 0.0f;
        arg0[2][0] = c[1] * inv;
        arg0[3][1] = 0.0f;
        arg0[3][2] = 0.0f;
        arg0[0][1] = (m02 * m21 - m01 * m22) * inv;
        arg0[0][2] = (m01 * m12 - m02 * m11) * inv;
        arg0[1][1] = (m00 * m22 - m02 * m20) * inv;
        arg0[1][2] = (m02 * m10 - m00 * m12) * inv;
        arg0[2][1] = (m01 * m20 - m00 * m21) * inv;
        arg0[3][3] = 1.0f;
        arg0[2][2] = (m00 * m11 - m01 * m10) * inv;
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

    pushed = 0;
    gfx = *arg1;
    guMtxIdentF(mf);
    guMtxF2L(mf, &D_802A538C[D_802A5368]);
    gW(gfx++, 0x01020040, (u32)&D_802A538C[D_802A5368]);
    D_802A5368++;
    func_8029CA80(mf, arg0->unk10, arg0->unk14, arg0->unk18);
    rx = arg0->unk1C;
    ry = ((arg0->unkC & 0x2000) ? D_802A5468 : 0.0f) + arg0->unk20;
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
    guMtxF2L(mf, &D_802A538C[D_802A5368]);
    gW(gfx++, 0x01060040, (u32)&D_802A538C[D_802A5368]);
    D_802A5368++;
    *arg1 = gfx;
    return pushed;
}

static void func_802284F0(UnkObj *arg0, UnkGfx **arg1) {
    UnkGfx *gfx;
    s32 i;
    UnkTexSlot *slot;
    UnkTexAnim *anim;
    UnkModel *model;

    gfx = *arg1;
    for (i = 0; i < arg0->unk4C->unk0; i++) {
        slot = &arg0->unk4C->unk4[i];
        anim = &arg0->unk4C->unk8[i];
        model = slot->unk0;
        if (arg0->unk4C->unk8 == NULL) {
            gSPSegment(gfx++, i + 3, (u8 *)model + model->unkC[slot->unk4].unk8);
        } else {
            if (anim->unk8 >= anim->unkC[anim->unk4 * 2 + 1]) {
                anim->unk8 = 0;
                if (anim->unk0 == anim->unk4 + 1) {
                    anim->unk4 = 0;
                } else {
                    anim->unk4 = anim->unk4 + 1;
                }
            } else {
                anim->unk8 = anim->unk8 + 1;
            }
            gSPSegment(gfx++, i + 3, (u8 *)model + model->unkC[anim->unkC[anim->unk4 * 2]].unk8);
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
        ((void (*)(UnkObj *, UnkGfx **))arg0->unk3C)(arg0, &gfx);
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
