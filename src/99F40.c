#include "common.h"

/* An 8x8 block of a map's cells */
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u16 unk2[64];
} UnkStruct_800B5F30; /* size 0x82 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ UnkStruct_800B5F30 unk10[24];
} UnkStruct_800B5F20; /* size 0xC40 */

void func_8026D620(s32, s32, s32, s32);
s32 func_8026D7D8(s32, s32, s32);

extern UnkStruct_800B5F20 D_800B5F20[6];
extern u8 D_802A1610[];
s32 D_802B01F0;
void (*D_802B01F8[7])(s32);
void (*D_802B0214)(void);

void func_8027F740(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        D_800B5F20[i].unk0 = -1;
    }
    D_802B01F0 = 0;
}

void func_8027F79C(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        D_802B01F8[i] = NULL;
    }
    D_802B0214 = NULL;
}

void func_8027F7E0(void) {
    func_80297D30(14, D_802A1610);
    func_8027F79C();
    func_8027F740();
}

void func_8027F818(s32 arg0) {
}

void func_8027F820(void) {
    if (D_802B0214 != NULL) {
        D_802B0214();
    }
}

void func_8027F84C(void (*arg0)(void)) {
    D_802B0214 = arg0;
}

void func_8027F858(s32 arg0, s32 arg1) {
    if (D_802B01F8[arg1 - 1] != NULL) {
        D_802B01F8[arg1 - 1](arg0);
    }
}

void func_8027F88C(void (*arg0)(s32), s32 arg1) {
    D_802B01F8[arg1 - 1] = arg0;
}

void func_8027F8A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 block = D_800B5F20[arg0].unk8 * (arg2 / 8) + arg1 / 8;
    s32 cell = (arg2 % 8) * 8 + arg1 % 8;

    D_800B5F20[arg0].unk10[block].unk2[cell] = arg3;
}

u16 func_8027F940(s32 arg0, s32 arg1, s32 arg2) {
    s32 block = D_800B5F20[arg0].unk8 * (arg2 / 8) + arg1 / 8;
    s32 cell = (arg2 % 8) * 8 + arg1 % 8;
    u16 ret;

    ret = D_800B5F20[arg0].unk10[block].unk2[cell];
    return ret;
}

void func_8027F9E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 i;
    s32 j;
    s32 a;
    s32 b;

    for (i = 0; i <= arg4 - arg2; i++) {
        for (j = 0; j <= arg3 - arg1; j++) {
            a = func_8027F940(arg0, arg1 + j, arg2 + i);
            b = func_8026D7D8(arg5 + j, arg6, arg7 + i);
            func_8026D620(arg5 + j, arg6, arg7 + i, a);
            func_8027F8A0(arg0, arg1 + j, arg2 + i, b);
        }
    }
}

void func_8027FB18(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 i;
    s32 j;

    for (i = 0; i <= arg4 - arg2; i++) {
        for (j = 0; j <= arg3 - arg1; j++) {
            func_8026D620(arg5 + j, arg6, arg7 + i, func_8027F940(arg0, arg1 + j, arg2 + i));
        }
    }
}

void func_8027FC08(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_800B5F20[i].unk0 != -1) {
            func_8026CCBC(D_800B5F20[i].unk0);
            D_800B5F20[i].unk0 = -1;
        }
    }
    D_802B01F0 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/99F40/func_8027FC78.s")
