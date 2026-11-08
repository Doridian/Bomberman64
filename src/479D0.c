#include "common.h"

/*
 * -O3. func_8022D1D0 alone: it builds a skeleton instance from a model's
 * chunk. The rest of the skeleton code is 45170 (nonmatching/45170.c has
 * the structures in full); only the fields used here are named.
 */

void *malloc(u32);

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

typedef struct UnkSkel UnkSkel;
typedef struct UnkNode UnkNode;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ Vec3f unk4;
    /* 0x10 */ Vec3f unk10;
    /* 0x1C */ Vec3f unk1C;
    /* 0x28 */ UnkNode *unk28;
    /* 0x2C */ void *unk2C;
    /* 0x30 */ void *unk30;
    /* 0x34 */ void *unk34;
    /* 0x38 */ s32 *unk38;
} UnkInst; /* size 0x3C */

extern s32 D_802A54D0;

void func_8022AEDC(UnkSkel *arg0, UnkInst *arg1);
UnkNode *func_8022CFC8(UnkInst *arg0, UnkNode *arg1, s32 arg2);
void func_8022D15C(Vec3f *arg0);

UnkInst *func_8022D1D0(UnkSkel *arg0, UnkModel *arg1, u32 arg2) {
    UnkInst *inst;

    if (arg2 >= arg1->unk4) {
        return NULL;
    }
    inst = malloc(sizeof(UnkInst));
    func_8022D15C(&inst->unk4);
    inst->unk38 = NULL;
    func_8022AEDC(arg0, inst);
    D_802A54D0 = 0;
    inst->unk0 = 1;
    inst->unk28 = func_8022CFC8(inst, NULL, arg1->unkC[arg2].unk4);
    return inst;
}
