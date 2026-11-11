/*
 * NON_MATCHING: main_code's 46300, complete: an instance's node tree and
 * its animation tracks (key lists and curves, interpolated per node).
 * Every function is in C, written last function first (-O3 emits a
 * file's functions in reverse). 45170 before it reads the model
 * (nonmatching/45170.c), func_8022D1D0 after it is its own object
 * (src/479D0.c, text_objects.txt). Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 108, eu 108, jp 108
 *
 * The code is the same in every version.
 *
 * func_8022C8B8 keeps its globals (D_802A54D4..D_802A5504) as
 * function-scope statics: only then does a store to one not kill
 * pointer loads, and each access gets its own lui. Its .bss starts with
 * the global D_802A54D0, then those statics; its .data at 0x8029F890.
 * Moving this file to src/ has to check where IDO puts them.
 *
 * Left:
 * - func_8022C8B8 (84): same size and shape; temporaries numbered
 *   from one lower (the channel's address is in v1 in the original).
 * - func_8022BE48 (14): n, i and (s32)arg1 coloured a2/a3/v0 in the
 *   original, v0/a2/a3 here; the add's operands swapped.
 * - func_8022BB88 (10): the count and count * 40 in v1/a0, here a1/v1.
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

/* A key list channel's part from unk4 on. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 *unk8;
    /* 0x0C */ s32 *unkC;
} UnkChanKeys;

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

extern Vec3f D_8029F890;
extern Vec3f D_8029F89C;
extern Vec3f D_8029F8A8;
extern s32 D_802A54D0;

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
    node->unk0 = arg0->unk2C[arg2].unk0;
    node->unk4 = arg2;
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
    UnkNode **c;

    if (arg0->unk10 != 0) {
        c = arg0->unkC;
        for (i = 0; i < arg0->unk10; i++) {
            func_8022CEE4(c[i]);
        }
        free(c);
    }
    free(arg0);
}

void func_8022CD98(UnkInst *arg0, s32 arg1, s32 arg2) {
    UnkKey *keys;
    s32 n;
    UnkNode *node;
    s32 i;
    s32 j;

    if (arg0->unk0 == 1) {
        if (arg2 != 0 && arg0->unk0 == 1) {
            func_8022C480(arg0, arg0->unk28);
        }
        n = arg0->unk30[arg0->unk38[arg1]].unk8;
        keys = arg0->unk30[arg0->unk38[arg1]].unk4;
        for (i = 0; i < n; i++) {
            node = arg0->unk28;
            for (j = 1; j < keys[i].unk4; j++) {
                node = node->unkC[keys[i].unk0[j]];
            }
            node->unk14 = keys[i].unk8;
            node->unk20 = keys[i].unk14;
            node->unk2C = keys[i].unk20;
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
    static s32 D_802A54D4;
    static s32 D_802A54D8;
    static s32 D_802A54DC;
    static s32 D_802A54E0;
    static s32 D_802A54E4;
    static s32 D_802A54E8;
    static s32 D_802A54EC;
    static s32 D_802A54F0;
    static s32 *D_802A54F4;
    static s32 *D_802A54F8;
    static UnkChan *D_802A54FC;
    static UnkAnim *D_802A5500;
    static UnkTrack *D_802A5504;
    UnkTrack *track;
    UnkChan *chan;
    UnkChanKeys *k;
    s32 t;

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
        D_802A54E0 = 0;
        D_802A5504->unk4 = t = D_802A54FC[D_802A54D4].unk0;
        switch (t) {
            case 0x2F:
                k = (UnkChanKeys *)&D_802A54FC[D_802A54D4].unk4;
                D_802A54E8 = k->unk4;
                D_802A5504->unk10 = D_802A54F8 = malloc(D_802A54E8 * 4);
                D_802A5504->unk14 = D_802A54F4 = malloc(D_802A54E8 * 4);
                D_802A5504->unk18 = D_802A54E8;
                D_802A5504->unk1C = func_8022C7EC(arg0->unk28);
                D_802A5504->unk20 = -1;
                D_802A5504->unk24 = -1;
                for (D_802A54D8 = 0; D_802A54D8 < D_802A54E8; D_802A54D8++) {
                    D_802A54F8[D_802A54D8] = k->unk8[D_802A54D8];
                    D_802A54F4[D_802A54D8] = D_802A54E0;
                    D_802A54E0 += k->unkC[D_802A54D8];
                }
                D_802A54EC = k->unk0;
                break;
            case 0x30:
                chan = &D_802A54FC[D_802A54D4];
                D_802A5504->unk10 = (s32 *)chan->unkC;
                D_802A54E0 = chan->unk8;
                D_802A5504->unk14 = (s32 *)D_802A54E0;
                D_802A5504->unk18 = (s32)&chan->unk10;
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
    f32 t;
    f32 u;
    s32 n;
    s32 *times;
    s32 *keys;

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
            n = track->unk18;
            times = track->unk14;
            keys = track->unk10;
            for (j = 1; j < n; j++) {
                if ((s32)t < times[j]) {
                    break;
                }
            }
            if (j == n && t == (s32)t) {
                j--;
            }
            if (track->unk20 != keys[j - 1]) {
                track->unk20 = keys[j - 1];
                func_8022C2A4(track->unk1C, keys[j - 1], 0, inst);
            }
            if (track->unk24 != keys[j]) {
                track->unk24 = keys[j];
                func_8022C2A4(track->unk1C, keys[j], 1, inst);
            }
            u = (t - times[j - 1]) / (times[j] - times[j - 1]);
            func_8022C09C(track->unk1C, u);
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
    UnkKey *keys;
    s32 n;
    UnkTree *tree;
    s32 i;
    s32 j;

    func_8022C184(arg3, arg0, arg2);
    set = &arg3->unk30[arg1];
    n = set->unk8;
    keys = set->unk4;
    for (i = 0; i < n; i++) {
        tree = arg0;
        for (j = 1; j < keys[i].unk4; j++) {
            tree = tree->unk8[keys[i].unk0[j]];
        }
        tree->unk18[arg2][0] = keys[i].unk8;
        tree->unk18[arg2][1] = keys[i].unk14;
        tree->unk18[arg2][2] = keys[i].unk20;
        tree->unk10[arg2] = 1;
    }
}

void func_8022C184(UnkInst *arg0, UnkTree *arg1, s32 arg2) {
    UnkJoint *joint;
    Vec3f *d;
    s32 i;

    if (arg1 != NULL) {
        d = arg1->unk18[arg2];
        joint = &arg0->unk2C[arg1->unk0->unk4];
        d[0] = joint->unk4;
        d[1] = joint->unk10;
        d[2] = joint->unk1C;
        arg1->unk10[arg2] = 0;
        for (i = 0; i < arg1->unkC; i++) {
            func_8022C184(arg0, arg1->unk8[i], arg2);
        }
    }
}

void func_8022C09C(UnkTree *arg0, f32 arg1) {
    s32 i;
    Vec3f *a;
    Vec3f *b;
    Vec3f *c;

    if (arg0 != NULL) {
        a = arg0->unk18[0];
        b = arg0->unk18[1];
        if (arg0->unk10[0] | arg0->unk10[1]) {
            c = &arg0->unk0->unk14;
            func_8022BF44(&a[0], &b[0], &c[0], arg1);
            func_8022C008(&a[1], &b[1], &c[1], arg1);
            func_8022BF44(&a[2], &b[2], &c[2], arg1);
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
    f32 r;
    f32 ret;
    s32 n;
    s32 *keys;
    f32 *vals;

    if (arg0->unk0 == 0x31) {
        n = arg0->unk4;
        keys = arg0->unk8;
        vals = arg0->unkC;
        for (i = 0; i < n; i++) {
            if (keys[i] >= (s32)arg1) {
                break;
            }
        }
        if ((s32)arg1 == keys[i]) {
            ret = vals[i];
        } else {
            ret = vals[i - 1];
            ret += (arg1 - keys[i - 1]) * ((vals[i] - vals[i - 1]) / (keys[i] - keys[i - 1]));
        }
    }
    return ret;
}

void func_8022BCC8(UnkInst *arg0, s32 arg1, f32 arg2) {
    UnkKeySet *set;
    UnkKey *keys;
    s32 n;
    UnkNode *node;
    s32 i;
    s32 j;

    set = &arg0->unk30[arg1];
    n = set->unk8;
    keys = set->unk4;
    for (i = 0; i < n; i++) {
        node = arg0->unk28;
        for (j = 1; j < keys[i].unk4; j++) {
            node = node->unkC[keys[i].unk0[j]];
        }
        func_8022BC64(&node->unk14, &keys[i].unk8, &arg0->unk2C[node->unk4].unk4, arg2);
        func_8022BC64(&node->unk20, &keys[i].unk14, &arg0->unk2C[node->unk4].unk10, arg2);
        func_8022BC64(&node->unk2C, &keys[i].unk20, &arg0->unk2C[node->unk4].unk1C, arg2);
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
        switch (track->unk4) {
            case 0x2F:
                free(track->unk10);
                free(track->unk14);
                func_8022BB00(track->unk1C);
                break;
            case 0x30:
                break;
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

