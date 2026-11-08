/*
 * NON_MATCHING: main_code's 45170, complete: the skeleton and animation
 * code. func_8022AF1C reads a model file's chunks 1, 2, 3 and 7 into a
 * skeleton; the rest builds an instance's node tree and plays animation
 * tracks (key lists and curves, interpolated per node). Every function is
 * in C, written last function first (-O3 emits a file's functions in
 * reverse). func_8022D1D0 after it is its own object (src/479D0.c,
 * text_objects.txt). Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 1949, eu 1949, jp 1949
 *
 * The code is the same in every version.
 *
 * Left:
 * - func_8022AF1C (999, ours 0xFAC vs 0xBE4): the original keeps every
 *   loop counter (D_802A54B0/B4/B8) in memory (lw, addiu, sw, lw again)
 *   while walking the chunks with a strength-reduced pointer, and keeps
 *   arg0->unk4 in a register across the counter stores. IDO promotes
 *   ours into s-registers through a base register, which then aliases
 *   arg0->unk4 and forces reloads. volatile, a local chunk pointer, and
 *   defining the counters in the file don't give the original's form.
 * - func_8022C8B8 (293, ours 0x40C vs 0x494): the animation start; its
 *   globals D_802A54D4..D_802A5504 have the same problem.
 * - func_8022C530 (124), func_8022BCC8 (96), func_8022C2A4 (85),
 *   func_8022CFC8 (80), func_8022CD98 (75), func_8022BE48 (58),
 *   func_8022BB88 (45): registers and float scheduling.
 * - func_8022CEE4 (27), func_8022C184 (20), func_8022AA50 and
 *   func_8022AB48 (18 each), func_8022C09C (11): registers only.
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

void func_8022A970(UnkChan *arg0, s32 arg1);
void func_8022AA50(UnkSkel *arg0);
void func_8022AAD4(UnkKey *arg0, s32 arg1);
void func_8022AB48(UnkSkel *arg0);
void func_8022ABCC(UnkSkel *arg0);
void func_8022AC2C(UnkSkel *arg0, UnkInst *arg1);
void func_8022AD98(UnkSkel *arg0, UnkInst *arg1);
void func_8022AED0(UnkSkel *arg0, UnkInst *arg1);
void func_8022AEDC(UnkSkel *arg0, UnkInst *arg1);
UnkSkel *func_8022AF1C(UnkModel *arg0);
void func_8022BB00(UnkTree *arg0);
void func_8022BB88(UnkAnim *arg0);
void func_8022BC64(Vec3f *arg0, Vec3f *arg1, Vec3f *arg2, f32 arg3);
void func_8022BCC8(UnkInst *arg0, s32 arg1, f32 arg2);
f32 func_8022BE48(UnkCurve *arg0, f32 arg1);
void func_8022BF44(Vec3f *arg0, Vec3f *arg1, Vec3f *arg2, f32 arg3);
f32 func_8022BF9C(f32 arg0, f32 arg1, f32 arg2);
void func_8022C008(Vec3f *arg0, Vec3f *arg1, Vec3f *arg2, f32 arg3);
void func_8022C09C(UnkTree *arg0, f32 arg1);
void func_8022C184(UnkInst *arg0, UnkTree *arg1, s32 arg2);
void func_8022C2A4(UnkTree *arg0, s32 arg1, s32 arg2, UnkInst *arg3);
void func_8022C3EC(UnkInst *arg0, UnkNode *arg1);
void func_8022C480(UnkInst *arg0, UnkNode *arg1);
void func_8022C4FC(UnkInst *arg0);
void func_8022C530(UnkAnim *arg0, f32 arg1, s32 arg2);
UnkTree *func_8022C7EC(UnkNode *arg0);
UnkAnim *func_8022C8B8(UnkInst *arg0, s32 arg1);
void func_8022CD4C(Vec3f *arg0, Vec3f *arg1, Vec3f *arg2, f32 arg3);
void func_8022CD98(UnkInst *arg0, s32 arg1, s32 arg2);
void func_8022CEE4(UnkNode *arg0);
void func_8022CF64(UnkInst *arg0);
UnkNode *func_8022CFC8(UnkInst *arg0, UnkNode *arg1, s32 arg2);
void func_8022D15C(Vec3f *arg0);

void func_8022D15C(Vec3f *arg0) {
    arg0[0] = D_8029F890;
    arg0[1] = D_8029F89C;
    arg0[2] = D_8029F8A8;
}

UnkNode *func_8022CFC8(UnkInst *arg0, UnkNode *arg1, s32 arg2) {
    UnkNode *node;
    s32 n;
    s32 i;
    s32 j;

    D_802A54D0++;
    node = malloc(sizeof(UnkNode));
    node->unk8 = arg1;
    node->unk4 = arg2;
    node->unk0 = arg0->unk2C[arg2].unk0;
    func_8022C3EC(arg0, node);
    if (arg0->unk2C[arg2].unk2C != 0) {
        n = 1;
        j = arg2 + arg0->unk2C[arg2].unk2C;
        while (arg0->unk2C[j].unk28 != 0) {
            n++;
            j += arg0->unk2C[j].unk28;
        }
        node->unk10 = n;
        node->unkC = malloc(n * 4);
        j = arg0->unk2C[arg2].unk2C + arg2;
        for (i = 0; i < n; i++) {
            node->unkC[i] = func_8022CFC8(arg0, node, j);
            j += arg0->unk2C[j].unk28;
        }
    } else {
        node->unk10 = 0;
        node->unkC = NULL;
    }
    return node;
}

void func_8022CF64(UnkInst *arg0) {
    if (arg0->unk0 == 1) {
        func_8022CEE4(arg0->unk28);
    }
    if (arg0->unk38 != NULL) {
        free(arg0->unk38);
    }
    free(arg0);
}

void func_8022CEE4(UnkNode *arg0) {
    s32 i;

    if (arg0->unk10 != 0) {
        for (i = 0; i < arg0->unk10; i++) {
            func_8022CEE4(arg0->unkC[i]);
        }
        free(arg0->unkC);
    }
    free(arg0);
}

void func_8022CD98(UnkInst *arg0, s32 arg1, s32 arg2) {
    UnkKeySet *set;
    UnkKey *key;
    UnkNode *node;
    s32 i;
    s32 j;

    if (arg0->unk0 == 1) {
        if (arg2 != 0 && arg0->unk0 == 1) {
            func_8022C480(arg0, arg0->unk28);
        }
        set = &arg0->unk30[arg0->unk38[arg1]];
        for (i = 0; i < set->unk8; i++) {
            key = &set->unk4[i];
            node = arg0->unk28;
            for (j = 1; j < key->unk4; j++) {
                node = node->unkC[key->unk0[j]];
            }
            node->unk14 = key->unk8;
            node->unk20 = key->unk14;
            node->unk2C = key->unk20;
            node->unk38 = 1;
        }
    }
}

void func_8022CD4C(Vec3f *arg0, Vec3f *arg1, Vec3f *arg2, f32 arg3) {
    arg0->x = (arg1->x - arg2->x) * arg3;
    arg0->y = (arg1->y - arg2->y) * arg3;
    arg0->z = (arg1->z - arg2->z) * arg3;
}

UnkAnim *func_8022C8B8(UnkInst *arg0, s32 arg1) {
    UnkTrack *track;
    UnkChan *chan;
    s32 *keys;

    if (arg0->unk0 != 1) {
        return NULL;
    }
    D_802A5500 = malloc(sizeof(UnkAnim));
    D_802A5500->unk0 = arg0;
    D_802A5500->unk4 = 0.0f;
    D_802A54E4 = arg0->unk34[arg1].unk8;
    D_802A5500->unk10 = D_802A54E4;
    D_802A5500->unk14 = malloc(D_802A54E4 * sizeof(UnkTrack));
    D_802A5500->unk8 = arg0->unk34[arg1].unkC;
    D_802A54FC = arg0->unk34[arg1].unk4;
    D_802A54DC = 0;
    for (D_802A54D4 = 0; D_802A54D4 < D_802A54E4; D_802A54D4++) {
        D_802A5504 = &D_802A5500->unk14[D_802A54D4];
        D_802A5504->unk4 = D_802A54FC[D_802A54D4].unk0;
        switch (D_802A54FC[D_802A54D4].unk0) {
            case 0x2F:
                D_802A54E0 = 0;
                chan = &D_802A54FC[D_802A54D4];
                D_802A54E8 = chan->unk8;
                D_802A5504->unk10 = D_802A54F8 = malloc(D_802A54E8 * 4);
                D_802A5504->unk14 = D_802A54F4 = malloc(D_802A54E8 * 4);
                D_802A5504->unk18 = D_802A54E8;
                D_802A5504->unk1C = func_8022C7EC(arg0->unk28);
                D_802A5504->unk20 = -1;
                D_802A5504->unk24 = -1;
                for (D_802A54D8 = 0; D_802A54D8 < D_802A54E8; D_802A54D8++) {
                    D_802A54F8[D_802A54D8] = chan->unkC[D_802A54D8];
                    D_802A54F4[D_802A54D8] = D_802A54E0;
                    D_802A54E0 += chan->unk10[D_802A54D8];
                }
                D_802A54EC = chan->unk4;
                break;
            case 0x30:
                chan = &D_802A54FC[D_802A54D4];
                D_802A5504->unk10 = (s32 *)chan->unkC;
                D_802A5504->unk14 = (s32 *)chan->unk8;
                D_802A5504->unk18 = (s32)&chan->unk10;
                D_802A54E0 = chan->unk8;
                D_802A54EC = chan->unk4;
                D_802A54F0 = chan->unk4 + chan->unk8;
                break;
        }
        D_802A5504->unk8 = D_802A54EC;
        D_802A5504->unkC = D_802A54EC + D_802A54E0;
        if (D_802A54DC < D_802A54E0) {
            D_802A54DC = D_802A54E0;
        }
    }
    D_802A5500->unkC = D_802A54DC;
    func_8022C530(D_802A5500, 0.0f, 0);
    return D_802A5500;
}

UnkTree *func_8022C7EC(UnkNode *arg0) {
    UnkTree *tree;
    s32 i;

    if (arg0 == NULL) {
        return NULL;
    }
    tree = malloc(sizeof(UnkTree));
    tree->unk0 = arg0;
    if (arg0->unk10 != 0) {
        tree->unk8 = malloc(arg0->unk10 * 4);
        for (i = 0; i < arg0->unk10; i++) {
            tree->unk8[i] = func_8022C7EC(arg0->unkC[i]);
        }
        tree->unkC = i;
    } else {
        tree->unkC = 0;
        tree->unk8 = NULL;
    }
    return tree;
}

void func_8022C530(UnkAnim *arg0, f32 arg1, s32 arg2) {
    UnkInst *inst;
    UnkTrack *track;
    s32 i;
    s32 j;
    s32 *s;
    s32 *k;
    f32 t;

    inst = arg0->unk0;
    arg0->unk4 = arg1;
    if (arg2 == 0 && inst->unk0 == 1) {
        func_8022C480(inst, inst->unk28);
    }
    for (i = 0; i < arg0->unk10; i++) {
        track = &arg0->unk14[i];
        if (arg1 < (f32)track->unk8 || (f32)track->unkC < arg1) {
            continue;
        }
        t = arg1 - (f32)track->unk8;
        if (track->unk4 == 0x2F) {
            for (j = 1; j < track->unk18; j++) {
                if ((s32)t < track->unk14[j]) {
                    break;
                }
            }
            s = &track->unk14[j];
            if (j == track->unk18 && t == (s32)t) {
                j--;
                s--;
            }
            k = &track->unk10[j];
            if (track->unk20 != k[-1]) {
                track->unk20 = k[-1];
                func_8022C2A4(track->unk1C, k[-1], 0, inst);
            }
            if (track->unk24 != k[0]) {
                track->unk24 = k[0];
                func_8022C2A4(track->unk1C, k[0], 1, inst);
            }
            func_8022C09C(track->unk1C, (t - s[-1]) / (s[0] - s[-1]));
        } else if (track->unk4 == 0x30) {
            func_8022BCC8(inst, (s32)track->unk10, func_8022BE48((UnkCurve *)track->unk18, t));
        }
    }
}

void func_8022C4FC(UnkInst *arg0) {
    if (arg0->unk0 == 1) {
        func_8022C480(arg0, arg0->unk28);
    }
}

void func_8022C480(UnkInst *arg0, UnkNode *arg1) {
    s32 i;

    func_8022C3EC(arg0, arg1);
    for (i = 0; i < arg1->unk10; i++) {
        func_8022C480(arg0, arg1->unkC[i]);
    }
}

void func_8022C3EC(UnkInst *arg0, UnkNode *arg1) {
    UnkJoint *joint;

    if (arg1 != NULL) {
        joint = &arg0->unk2C[arg1->unk4];
        arg1->unk14 = joint->unk4;
        arg1->unk20 = joint->unk10;
        arg1->unk2C = joint->unk1C;
    }
}

void func_8022C2A4(UnkTree *arg0, s32 arg1, s32 arg2, UnkInst *arg3) {
    UnkKeySet *set;
    UnkKey *key;
    UnkTree *tree;
    s32 i;
    s32 j;

    func_8022C184(arg3, arg0, arg2);
    set = &arg3->unk30[arg1];
    for (i = 0; i < set->unk8; i++) {
        key = &set->unk4[i];
        tree = arg0;
        for (j = 1; j < key->unk4; j++) {
            tree = tree->unk8[key->unk0[j]];
        }
        tree->unk18[arg2][0] = key->unk8;
        tree->unk18[arg2][1] = key->unk14;
        tree->unk18[arg2][2] = key->unk20;
        tree->unk10[arg2] = 1;
    }
}

void func_8022C184(UnkInst *arg0, UnkTree *arg1, s32 arg2) {
    UnkJoint *joint;
    s32 i;

    if (arg1 != NULL) {
        joint = &arg0->unk2C[arg1->unk0->unk4];
        arg1->unk18[arg2][0] = joint->unk4;
        arg1->unk18[arg2][1] = joint->unk10;
        arg1->unk18[arg2][2] = joint->unk1C;
        arg1->unk10[arg2] = 0;
        for (i = 0; i < arg1->unkC; i++) {
            func_8022C184(arg0, arg1->unk8[i], arg2);
        }
    }
}

void func_8022C09C(UnkTree *arg0, f32 arg1) {
    Vec3f *a;
    Vec3f *b;
    UnkNode *node;
    s32 i;

    if (arg0 != NULL) {
        a = arg0->unk18[0];
        b = arg0->unk18[1];
        if (arg0->unk10[1] | arg0->unk10[0]) {
            node = arg0->unk0;
            func_8022BF44(&a[0], &b[0], &node->unk14, arg1);
            func_8022C008(&a[1], &b[1], &node->unk20, arg1);
            func_8022BF44(&a[2], &b[2], &node->unk2C, arg1);
        }
        for (i = 0; i < arg0->unkC; i++) {
            func_8022C09C(arg0->unk8[i], arg1);
        }
    }
}

void func_8022C008(Vec3f *arg0, Vec3f *arg1, Vec3f *arg2, f32 arg3) {
    arg2->x = func_8022BF9C(arg0->x, arg1->x, arg3);
    arg2->y = func_8022BF9C(arg0->y, arg1->y, arg3);
    arg2->z = func_8022BF9C(arg0->z, arg1->z, arg3);
}

f32 func_8022BF9C(f32 arg0, f32 arg1, f32 arg2) {
    if (arg0 > 180.0) {
        arg0 -= 360.0;
    }
    if (arg1 > 180.0) {
        arg1 -= 360.0;
    }
    return arg0 + (arg1 - arg0) * arg2;
}

void func_8022BF44(Vec3f *arg0, Vec3f *arg1, Vec3f *arg2, f32 arg3) {
    arg2->x = arg0->x + (arg1->x - arg0->x) * arg3;
    arg2->y = arg0->y + (arg1->y - arg0->y) * arg3;
    arg2->z = arg0->z + (arg1->z - arg0->z) * arg3;
}

f32 func_8022BE48(UnkCurve *arg0, f32 arg1) {
    s32 i;
    s32 *k;
    f32 *v;
    f32 ret;

    if (arg0->unk0 == 0x31) {
        for (i = 0; i < arg0->unk4; i++) {
            if (arg0->unk8[i] >= (s32)arg1) {
                break;
            }
        }
        k = &arg0->unk8[i];
        v = &arg0->unkC[i];
        if ((s32)arg1 == k[0]) {
            ret = arg0->unkC[i];
        } else {
            ret = (arg1 - k[-1]) * ((v[0] - v[-1]) / (k[0] - k[-1])) + v[-1];
        }
    }
    return ret;
}

void func_8022BCC8(UnkInst *arg0, s32 arg1, f32 arg2) {
    UnkKeySet *set;
    UnkKey *key;
    UnkNode *node;
    s32 i;
    s32 j;

    set = &arg0->unk30[arg1];
    for (i = 0; i < set->unk8; i++) {
        key = &set->unk4[i];
        node = arg0->unk28;
        for (j = 1; j < key->unk4; j++) {
            node = node->unkC[key->unk0[j]];
        }
        func_8022BC64(&node->unk14, &key->unk8, &arg0->unk2C[node->unk4].unk4, arg2);
        func_8022BC64(&node->unk20, &key->unk14, &arg0->unk2C[node->unk4].unk10, arg2);
        func_8022BC64(&node->unk2C, &key->unk20, &arg0->unk2C[node->unk4].unk1C, arg2);
    }
}

void func_8022BC64(Vec3f *arg0, Vec3f *arg1, Vec3f *arg2, f32 arg3) {
    arg0->x += (arg1->x - arg2->x) * arg3;
    arg0->y += (arg1->y - arg2->y) * arg3;
    arg0->z += (arg1->z - arg2->z) * arg3;
}

void func_8022BB88(UnkAnim *arg0) {
    UnkTrack *track;
    s32 i;

    for (i = 0; i < arg0->unk10; i++) {
        track = &arg0->unk14[i];
        if (track->unk4 == 0x2F) {
            free(track->unk10);
            free(track->unk14);
            func_8022BB00(track->unk1C);
        } else if (track->unk4 == 0x30) {
        }
    }
    free(arg0->unk14);
    free(arg0);
}

void func_8022BB00(UnkTree *arg0) {
    s32 i;

    if (arg0->unkC != 0) {
        for (i = 0; i < arg0->unkC; i++) {
            func_8022BB00(arg0->unk8[i]);
        }
        free(arg0->unk8);
    }
    free(arg0);
}

UnkSkel *func_8022AF1C(UnkModel *arg0) {
    UnkSkel *skel;
    UnkKey *key;
    UnkChan *chan;

    D_802A54C8 = arg0->unkC;
    skel = malloc(sizeof(UnkSkel));
    skel->unk30 = NULL;
    skel->unk28 = NULL;
    skel->unk1C = arg0->unk4;
    for (D_802A54B0 = 0; D_802A54B0 < arg0->unk4; D_802A54B0++) {
        if (D_802A54C8[D_802A54B0].unk0 == 1) {
            break;
        }
    }
    if (D_802A54B0 < arg0->unk4) {
        skel->unk20 = (UnkJoint *)((u8 *)arg0 + D_802A54C8[D_802A54B0].unk8);
    }
    for (D_802A54B0 = 0; D_802A54B0 < arg0->unk4; D_802A54B0++) {
        if (D_802A54C8[D_802A54B0].unk0 == 2) {
            break;
        }
    }
    if (D_802A54B0 < arg0->unk4) {
        skel->unk2C = D_802A54C8[D_802A54B0].unk4;
        D_802A54C0 = (s32 *)((u8 *)arg0 + D_802A54C8[D_802A54B0].unk8);
        D_802A54BC = skel;
        D_802A54BC->unk28 = malloc(skel->unk2C * sizeof(UnkKeySet));
        for (D_802A54B0 = 0; (s32)D_802A54B0 < D_802A54BC->unk2C; D_802A54B0++) {
            D_802A54BC->unk28[D_802A54B0].unk0 = *D_802A54C0++;
            D_802A54BC->unk28[D_802A54B0].unk8 = *D_802A54C0++;
            D_802A54BC->unk28[D_802A54B0].unk4 = malloc(D_802A54BC->unk28[D_802A54B0].unk8 * sizeof(UnkKey));
            for (D_802A54B4 = 0; D_802A54B4 < D_802A54BC->unk28[D_802A54B0].unk8; D_802A54B4++) {
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk4 = *D_802A54C0++;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk0 = malloc(D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk4 * 4);
                for (D_802A54B8 = 0; D_802A54B8 < D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk4; D_802A54B8++) {
                    D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk0[D_802A54B8] = *D_802A54C0++;
                }
                D_802A54C4 = (f32 *)D_802A54C0;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk8.x = *D_802A54C4++;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk8.y = *D_802A54C4++;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk8.z = *D_802A54C4++;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk14.x = *D_802A54C4++;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk14.y = *D_802A54C4++;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk14.z = *D_802A54C4++;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk20.x = *D_802A54C4++;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk20.y = *D_802A54C4++;
                D_802A54BC->unk28[D_802A54B0].unk4[D_802A54B4].unk20.z = *D_802A54C4++;
                D_802A54C0 = (s32 *)D_802A54C4;
            }
        }
        D_802A54B0 = 0;
    } else {
        skel->unk2C = 0;
        D_802A54B0 = 0;
    }
    for (; D_802A54B0 < arg0->unk4; D_802A54B0++) {
        if (D_802A54C8[D_802A54B0].unk0 == 3) {
            break;
        }
    }
    if (D_802A54B0 < arg0->unk4) {
        skel->unk34 = D_802A54C8[D_802A54B0].unk4;
        D_802A54C0 = (s32 *)((u8 *)arg0 + D_802A54C8[D_802A54B0].unk8);
        D_802A54BC = skel;
        D_802A54BC->unk30 = malloc(skel->unk34 * sizeof(UnkChanSet));
        for (D_802A54B0 = 0; (s32)D_802A54B0 < D_802A54BC->unk34; D_802A54B0++) {
            D_802A54BC->unk30[D_802A54B0].unk0 = *D_802A54C0++;
            D_802A54BC->unk30[D_802A54B0].unk8 = *D_802A54C0++;
            D_802A54BC->unk30[D_802A54B0].unkC = *D_802A54C0++;
            D_802A54BC->unk30[D_802A54B0].unk4 = malloc(D_802A54BC->unk30[D_802A54B0].unk8 * sizeof(UnkChan));
            for (D_802A54B4 = 0; D_802A54B4 < D_802A54BC->unk30[D_802A54B0].unk8; D_802A54B4++) {
                if (*D_802A54C0 == 0x2F) {
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk0 = *D_802A54C0++;
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk8 = *D_802A54C0++;
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk4 = *D_802A54C0++;
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unkC = malloc(D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk8 * 4);
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk10 = malloc(D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk8 * 4);
                    for (D_802A54B8 = 0; D_802A54B8 < D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk8; D_802A54B8++) {
                        D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unkC[D_802A54B8] = *D_802A54C0++;
                        D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk10[D_802A54B8] = *D_802A54C0++;
                    }
                } else if (*D_802A54C0 == 0x30) {
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk0 = *D_802A54C0++;
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk4 = *D_802A54C0++;
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk8 = *D_802A54C0++;
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk14 = *D_802A54C0++;
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unkC = (s32 *)*D_802A54C0++;
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk10 = (s32 *)0x31;
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk18 = malloc(D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk14 * 4);
                    D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk1C = malloc(D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk14 * 4);
                    for (D_802A54B8 = 0; D_802A54B8 < D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk14; D_802A54B8++) {
                        D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk18[D_802A54B8] = *D_802A54C0++;
                        D_802A54BC->unk30[D_802A54B0].unk4[D_802A54B4].unk1C[D_802A54B8] = *(f32 *)D_802A54C0++;
                    }
                }
            }
        }
        D_802A54B0 = 0;
    } else {
        skel->unk34 = 0;
        D_802A54B0 = 0;
    }
    for (; D_802A54B0 < arg0->unk4; D_802A54B0++) {
        if (D_802A54C8[D_802A54B0].unk0 == 7) {
            break;
        }
    }
    if (D_802A54B0 < arg0->unk4 && D_802A54C8[D_802A54B0].unk4 == 4) {
        s32 *p = (s32 *)((u8 *)arg0 + D_802A54C8[D_802A54B0].unk8);
        for (D_802A54B0 = 0; D_802A54B0 != 3; D_802A54B0++) {
            skel->unk0[D_802A54B0] = p[D_802A54B0];
            skel->unkC[D_802A54B0] = p[D_802A54B0 + 3];
        }
    }
    D_802A54BC = skel;
    return skel;
}

void func_8022AEDC(UnkSkel *arg0, UnkInst *arg1) {
    func_8022AED0(arg0, arg1);
    func_8022AD98(arg0, arg1);
    func_8022AC2C(arg0, arg1);
}

void func_8022AED0(UnkSkel *arg0, UnkInst *arg1) {
    arg1->unk2C = arg0->unk20;
}

void func_8022AD98(UnkSkel *arg0, UnkInst *arg1) {
    s32 i;
    s32 j;

    arg1->unk30 = arg0->unk28;
    D_802A54A0 = arg0->unk2C;
    D_802A54A8 = 0;
    if (D_802A54A0 != 0) {
        for (i = 0; i < D_802A54A0; i++) {
            if (D_802A54A8 < arg1->unk30[i].unk0) {
                D_802A54A8 = arg1->unk30[i].unk0;
            }
        }
        D_802A54A8++;
        arg1->unk38 = malloc(D_802A54A8 * 4);
        for (i = 0; i < D_802A54A8; i++) {
            for (j = D_802A54A0 - 1; j >= 0; j--) {
                if (i == arg1->unk30[j].unk0) {
                    break;
                }
            }
            arg1->unk38[i] = j;
        }
    }
}

void func_8022AC2C(UnkSkel *arg0, UnkInst *arg1) {
    s32 i;
    s32 j;

    arg1->unk34 = arg0->unk30;
    D_802A54A4 = arg0->unk34;
    if (D_8029F880 != NULL) {
        free(D_8029F880);
    }
    D_802A54AC = 0;
    D_8029F880 = NULL;
    if (D_802A54A4 != 0) {
        for (i = 0; i < D_802A54A4; i++) {
            if (D_802A54AC < arg1->unk34[i].unk0) {
                D_802A54AC = arg1->unk34[i].unk0;
            }
        }
        D_802A54AC++;
        D_8029F880 = malloc(D_802A54AC * 4);
        for (i = 0; i < D_802A54AC; i++) {
            for (j = D_802A54A4 - 1; j >= 0; j--) {
                if (i == arg1->unk34[j].unk0) {
                    break;
                }
            }
            D_8029F880[i] = j;
        }
    }
}

void func_8022ABCC(UnkSkel *arg0) {
    if (arg0->unk28 != NULL) {
        func_8022AB48(arg0);
    }
    if (arg0->unk30 != NULL) {
        func_8022AA50(arg0);
    }
    free(arg0);
}

void func_8022AB48(UnkSkel *arg0) {
    s32 i;

    for (i = 0; i < arg0->unk2C; i++) {
        func_8022AAD4(arg0->unk28[i].unk4, arg0->unk28[i].unk8);
    }
    free(arg0->unk28);
    arg0->unk28 = NULL;
    arg0->unk2C = 0;
}

void func_8022AAD4(UnkKey *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (arg0[i].unk4 != 0) {
            free(arg0[i].unk0);
        }
    }
    free(arg0);
}

void func_8022AA50(UnkSkel *arg0) {
    s32 i;

    for (i = 0; i < arg0->unk34; i++) {
        func_8022A970(arg0->unk30[i].unk4, arg0->unk30[i].unk8);
    }
    free(arg0->unk30);
    arg0->unk30 = NULL;
    arg0->unk34 = 0;
}

void func_8022A970(UnkChan *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (arg0[i].unk0 == 0x2F) {
            if (arg0[i].unk8 != 0) {
                free(arg0[i].unkC);
                free(arg0[i].unk10);
            }
        } else if (arg0[i].unk0 == 0x30 && arg0[i].unk14 != 0) {
            free(arg0[i].unk18);
            free(arg0[i].unk1C);
        }
    }
    free(arg0);
}
