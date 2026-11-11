/*
 * NON_MATCHING: main_code's 45170, complete: func_8022AF1C reads a model
 * file's chunks 1, 2, 3 and 7 into a skeleton, func_8022AEDC attaches
 * one to an instance (with index tables of its key sets and channels),
 * and the rest free one. Every function is in C, written last function
 * first (-O3 emits a file's functions in reverse). Its text matches in
 * every version; the data is not checked yet (below). 46300 after it
 * is the node tree and the animation tracks (nonmatching/46300.c,
 * text_objects.txt). Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 0, eu 0, jp 0
 *
 * The code is the same in every version.
 *
 * func_8022AF1C keeps its globals (D_802A54B0..C8) as function-scope
 * statics: only then does a store to one not kill pointer loads, and
 * each access gets its own lui. Moving this file to src/ has to check
 * where IDO puts those in .bss (D_802A54A0..C8, padded to 0x802A54D0;
 * .data D_8029F880, padded to 0x8029F890).
 * D_802A54B0 is s32 against arg0->unk4's u32 on purpose: the unsigned
 * compare is what keeps the counter's store-then-reload.
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

extern s32 *D_8029F880;
extern s32 D_802A54A0;
extern s32 D_802A54A4;
extern s32 D_802A54A8;
extern s32 D_802A54AC;

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

UnkSkel *func_8022AF1C(UnkModel *arg0) {
    static s32 D_802A54B0;
    static s32 D_802A54B4;
    static s32 D_802A54B8;
    static UnkSkel *D_802A54BC;
    static s32 *D_802A54C0;
    static f32 *D_802A54C4;
    static UnkChunk *D_802A54C8;
    UnkKey *key;
    UnkChan *chan;

    D_802A54C8 = arg0->unkC;
    D_802A54BC = malloc(sizeof(UnkSkel));
    D_802A54BC->unk1C = arg0->unk4;
    D_802A54BC->unk30 = NULL;
    D_802A54BC->unk28 = NULL;
    for (D_802A54B0 = 0; D_802A54B0 < arg0->unk4; D_802A54B0++) {
        if (D_802A54C8[D_802A54B0].unk0 == 1) {
            break;
        }
    }
    if (D_802A54B0 < arg0->unk4) {
        D_802A54BC->unk20 = (UnkJoint *)((u8 *)arg0 + D_802A54C8[D_802A54B0].unk8);
    }
    for (D_802A54B0 = 0; D_802A54B0 < arg0->unk4; D_802A54B0++) {
        if (D_802A54C8[D_802A54B0].unk0 == 2) {
            break;
        }
    }
    if (D_802A54B0 < arg0->unk4) {
        D_802A54C0 = (s32 *)((u8 *)arg0 + D_802A54C8[D_802A54B0].unk8);
        D_802A54BC->unk2C = D_802A54C8[D_802A54B0].unk4;
        D_802A54BC->unk28 = malloc(D_802A54BC->unk2C * sizeof(UnkKeySet));
        for (D_802A54B0 = 0; D_802A54B0 < D_802A54BC->unk2C; D_802A54B0++) {
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
    } else {
        D_802A54BC->unk2C = 0;
    }
    for (D_802A54B0 = 0; D_802A54B0 < arg0->unk4; D_802A54B0++) {
        if (D_802A54C8[D_802A54B0].unk0 == 3) {
            break;
        }
    }
    if (D_802A54B0 < arg0->unk4) {
        D_802A54C0 = (s32 *)((u8 *)arg0 + D_802A54C8[D_802A54B0].unk8);
        D_802A54BC->unk34 = D_802A54C8[D_802A54B0].unk4;
        D_802A54BC->unk30 = malloc(D_802A54BC->unk34 * sizeof(UnkChanSet));
        for (D_802A54B0 = 0; D_802A54B0 < D_802A54BC->unk34; D_802A54B0++) {
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
    } else {
        D_802A54BC->unk34 = 0;
    }
    for (D_802A54B0 = 0; D_802A54B0 < arg0->unk4; D_802A54B0++) {
        if (D_802A54C8[D_802A54B0].unk0 == 7) {
            break;
        }
    }
    if (D_802A54B0 < arg0->unk4 && D_802A54C8[D_802A54B0].unk4 == 4) {
        s32 *p = (s32 *)((u8 *)arg0 + D_802A54C8[D_802A54B0].unk8);
        s32 *q = p + 3;
        for (D_802A54B0 = 0; D_802A54B0 != 3; D_802A54B0++) {
            D_802A54BC->unk0[D_802A54B0] = p[D_802A54B0];
            D_802A54BC->unkC[D_802A54B0] = q[D_802A54B0];
        }
    }
    return D_802A54BC;
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
    UnkKeySet *p;

    for (i = 0, p = arg0->unk28; i < arg0->unk2C; i++) {
        func_8022AAD4(p[i].unk4, p[i].unk8);
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
    UnkChanSet *p;

    for (i = 0, p = arg0->unk30; i < arg0->unk34; i++) {
        func_8022A970(p[i].unk4, p[i].unk8);
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
