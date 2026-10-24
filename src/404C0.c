#include "common.h"

/* An open file: 8 of them at D_8014B808. */
typedef struct UnkStruct_80225CC0 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_80225CC0; /* size 0x14 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} UnkStruct_8014B008; /* size 0x8 */

void func_80297ED0(s32, s32, void *);
void func_80225E2C(s32);
void func_802260A8(UnkStruct_80225CC0 *, u32);

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u32 unk4;
} UnkStruct_8014B000;

extern UnkStruct_8014B000 D_8014B000;
extern UnkStruct_8014B008 D_8014B008[256];
extern UnkStruct_80225CC0 D_8014B808[8];
extern u8 D_8014B8A8[0x400];
extern s32 D_8029F5B0;
extern s32 D_8029F5B4;
extern s32 D_8029F5B8;
extern s32 D_8029F5BC;
extern s32 D_8029F5C0;
extern s32 D_802A5300;
extern UnkStruct_80225CC0 *D_802A5304;
extern s32 D_802A5308;
extern s32 D_802A530C;
extern s32 D_802A5310;

u32 func_80225CC0(UnkStruct_80225CC0 *arg0) {
    return arg0->unk8;
}

s32 func_80225CCC(UnkStruct_80225CC0 *arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
        case 0:
            if (arg1 < 0) {
                return -1;
            }
            arg0->unk8 = arg1;
            break;
        case 1:
            if (arg1 < 0 && arg0->unk8 < (u32) -arg1) {
                return -1;
            }
            arg0->unk8 += arg1;
            break;
        case 2:
            if (arg1 < 0 && arg0->unkC < (u32) -arg1) {
                return -1;
            }
            arg0->unk8 = arg0->unkC + arg1;
            break;
    }
    if (arg0->unkC < arg0->unk8) {
        return -1;
    }
    return 0;
}

void func_80225D9C(void) {
    func_80297ED0(D_802A5310 * 8 + D_802A5300, 0x800, D_8014B008);
}

void func_80225DDC(void) {
    if (D_802A530C != 0) {
        func_80297ED0(D_802A5310 * 8 + D_802A5300, 0x800, D_8014B008);
    }
    D_802A530C = 0;
}

void func_80225E2C(s32 arg0) {
    if (arg0 != D_802A5310) {
        if (D_802A530C != 0) {
            func_80297ED0(D_802A5310 * 8 + D_802A5300, 0x800, D_8014B008);
        }
        D_802A530C = 0;
        D_802A5310 = arg0;
        func_80297EC0(D_8014B008, 0x800, (arg0 << 11) + D_802A5300);
    }
}

/* This object may be -O3 after all: func_80225FB8 keeps its arguments in
 * t registers (-O2 homes them), and it matches only at -O3; the whole file,
 * written last function first at -O3, matches but for func_80225EBC's
 * `lui a3` (scratch/main_code/404C0_O3.c in the main checkout). */
#pragma GLOBAL_ASM("asm/nonmatchings/404C0/func_80225EBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/404C0/func_80225FB8.s")

void func_80226074(void *arg0, void *arg1, s32 arg2) {
    func_80225C44(arg0, arg1, arg2);
    func_80297D60(arg0, arg2);
}

void func_802260A8(UnkStruct_80225CC0 *arg0, u32 arg1) {
    s32 size;

    if (arg0 != D_802A5304) {
        D_802A5304 = arg0;
        D_802A5308 = (s32) arg1 / 1024;
    } else if (D_802A5308 != (s32) arg1 / 1024) {
        D_802A5308 = (s32) arg1 / 1024;
    } else {
        return;
    }
    if (arg0->unkC <= 0x400 || arg0->unkC >= arg1 + 0x400) {
        size = 0x400;
    } else {
        size = arg0->unkC - arg1;
        size += size & 1;
    }
    func_80297EC0(D_8014B8A8, size, arg0->unk4 + (D_802A5308 << 10));
}

s32 func_8022616C(u8 *arg0, s32 arg1, s32 arg2, UnkStruct_80225CC0 *arg3) {
    s32 size;
    u32 i;
    u32 pos;
    s32 left;
    s32 n;
    u32 count;

    while (D_8029F5C0 != 0) {
        func_80297DC0();
    }
    D_8029F5C0 = 1;
    i = 0;
    if (!(arg3->unk10 & 1)) {
        return 0;
    }
    /* fake (the permuter's): count holding the product first, and the
     * if (1) below; without them the frame comes out 8 bytes bigger */
    count = arg1 * arg2;
    size = count;
    if (arg3->unkC < arg3->unk8 + size) {
        size -= (arg3->unk8 + size) - arg3->unkC;
        if (1) {
        }
    }
    pos = arg3->unk8;
    count = ((arg3->unk8 + size - 1) >> 10) - (arg3->unk8 >> 10) + 1;
    left = size;
    for (; i < count; i++) {
        func_802260A8(arg3, pos);
        if ((pos & 0x3FF) + left < 0x400) {
            n = left;
        } else {
            n = 0x400 - (pos & 0x3FF);
        }
        func_80225C44(arg0, D_8014B8A8 + (pos & 0x3FF), n);
        func_80297D60(arg0, n);
        pos += n;
        arg0 += n;
        left -= n;
    }
    arg3->unk8 += size;
    D_8029F5C0 = 0;
    return size;
}

s32 func_80226304(UnkStruct_80225CC0 *arg0) {
    u32 pos;
    s32 ret;

    if (arg0->unk8 >= arg0->unkC) {
        ret = -1;
    } else {
        pos = arg0->unk8;
        func_802260A8(arg0, pos);
        ret = D_8014B8A8[arg0->unk8++ & 0x3FF];
    }
    return ret;
}

void func_80226368(UnkStruct_80225CC0 *arg0) {
    if (arg0 == D_802A5304) {
        D_802A5304 = NULL;
    }
    arg0->unk10 = 0;
}

void func_8022638C(u32 arg0, UnkStruct_8014B008 *arg1) {
    s32 sp24 = -1;
    UnkStruct_8014B008 *entry;

    while (D_8029F5B0 != 0) {
        func_80297DC0();
    }
    D_8029F5B0 = 1;
    if (D_802A5310 != (arg0 >> 8)) {
        sp24 = D_802A5310;
        func_80225E2C(arg0 >> 8);
    }
    entry = &D_8014B008[arg0 & 0xFF];
    arg1->unk0 = entry->unk0 + D_8014B000.unk0;
    arg1->unk4 = entry->unk4;
    if (sp24 != -1) {
        func_80225E2C(sp24);
    }
    D_8029F5B0 = 0;
}

u32 func_80226460(void) {
    u32 i;
    UnkStruct_8014B008 *entry;
    UnkStruct_8014B008 prev;

    while (D_8029F5BC != 0) {
        func_80297DC0();
    }
    D_8029F5BC = 1;
    for (i = 0; i < D_8014B000.unk4; i++) {
        func_80225E2C(i >> 8);
        entry = &D_8014B008[i & 0xFF];
        if (entry->unk0 == -1) {
            if (i == 0) {
                entry->unk0 = D_8014B000.unk4 * 8 + 8;
            } else {
                func_8022638C(i - 1, &prev);
                entry->unk0 = prev.unk0 + prev.unk4;
            }
            return i;
        }
    }
    D_8029F5BC = 0;
    return 0;
}

UnkStruct_80225CC0 *func_8022657C(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_8014B808[i].unk10 == 0) {
            return &D_8014B808[i];
        }
    }
    return NULL;
}

UnkStruct_80225CC0 *func_80226604(u32 arg0, s32 arg1) {
    UnkStruct_80225CC0 *f;
    UnkStruct_8014B008 *entry;

    while (D_8029F5B8 != 0) {
        func_80297DC0();
    }
    D_8029F5B8 = 1;
    func_80225E2C(arg0 >> 8);
    arg0 &= 0xFF;
    f = func_8022657C();
    if (f != NULL) {
        entry = &D_8014B008[arg0];
        if (entry->unk0 == -1) {
            return NULL;
        }
        f->unk0 = arg0;
        f->unk4 = entry->unk0 + D_8014B000.unk0;
        f->unkC = entry->unk4;
        f->unk8 = 0;
        f->unk10 = arg1;
    }
    D_8029F5B8 = 0;
    return f;
}

u32 func_802266DC(UnkStruct_80225CC0 *arg0) {
    return arg0->unkC;
}

void func_802266E8(s32 arg0) {
    s32 i;

    D_802A530C = 0;
    for (i = 0; i < 8; i++) {
        D_8014B808[i].unk10 = 0;
    }
    func_80297EC0(&D_8014B000, 8, arg0);
    D_802A5300 = arg0 + 8;
    D_8014B000.unk0 += arg0;
    D_8029F5B0 = 0;
    D_8029F5B4 = 0;
    D_8029F5B8 = 0;
    D_8029F5BC = 0;
    D_8029F5C0 = 0;
    D_802A5310 = -1;
    D_802A5304 = NULL;
}
