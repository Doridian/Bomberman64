#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ s32 unk18[45];
} UnkStruct_8008E570; /* size 0xCC */

extern UnkStruct_8008E570 D_8008E570;
extern u8 D_8008E640[8];
extern u8 D_802A1C00[];

s32 *func_8028A060(s32 arg0) {
    if (arg0 < 0 || arg0 >= 45) {
        while (1) {
        }
    }
    return &D_8008E570.unk18[arg0];
}

void func_8028A08C(void) {
    func_80297D30(30, D_802A1C00);
}

void func_8028A0B4(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_8008E640[i] = 0;
    }
}

void func_8028A0E4(void) {
    s32 i;

    for (i = 0; i < 21; i++) {
        D_8008E570.unk0[i] = 0;
    }
    for (i = 0; i < 45; i++) {
        D_8008E570.unk18[i] = 0;
    }
    for (i = 21; i < 45; i++) {
        D_8008E570.unk18[i] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/A4860/func_8028A154.s")

s32 func_8028A1DC(s32 arg0) {
    if (arg0 < 0x400 || arg0 >= 0x440) {
        while (1) {
        }
    }
    arg0 -= 0x400;
    if (D_8008E640[arg0 / 8] & (1 << (arg0 % 8))) {
        return 1;
    }
    return 0;
}

void func_8028A24C(s32 arg0) {
    if (arg0 < 0x400 || arg0 >= 0x440) {
        while (1) {
        }
    }
    arg0 -= 0x400;
    D_8008E640[arg0 / 8] |= 1 << (arg0 % 8);
}

void func_8028A2B0(s32 arg0) {
    if (arg0 < 0x400 || arg0 >= 0x440) {
        while (1) {
        }
    }
    arg0 -= 0x400;
    D_8008E640[arg0 / 8] &= ~(1 << (arg0 % 8));
}

s32 func_8028A318(s32 arg0) {
    if (func_8028A1DC(arg0)) {
        func_8028A2B0(arg0);
    } else {
        func_8028A24C(arg0);
    }
    return func_8028A1DC(arg0);
}

s32 func_8028A36C(s32 arg0) {
    if (arg0 >= 0xAC) {
        while (1) {
        }
    }
    if (D_8008E570.unk0[arg0 / 8] & (1 << (arg0 % 8))) {
        return 1;
    }
    return 0;
}

void func_8028A3D0(s32 arg0) {
    if (arg0 >= 0xAC) {
        while (1) {
        }
    }
    D_8008E570.unk0[arg0 / 8] |= 1 << (arg0 % 8);
}

void func_8028A428(s32 arg0) {
    if (arg0 >= 0xAC) {
        while (1) {
        }
    }
    D_8008E570.unk0[arg0 / 8] &= ~(1 << (arg0 % 8));
}

s32 func_8028A484(s32 arg0) {
    if (func_8028A36C(arg0)) {
        func_8028A428(arg0);
    } else {
        func_8028A3D0(arg0);
    }
    return func_8028A36C(arg0);
}
