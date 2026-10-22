#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1[0xD];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10[0xC24];
} UnkStruct_800B15D8; /* size 0xC34 */

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C[0x1A];
    /* 0x36 */ s16 unk36;
} UnkStruct_800AED78_0;

typedef struct {
    /* 0x00 */ UnkStruct_800AED78_0 *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_800AED78; /* size 0xC */


extern UnkStruct_800AED78 D_800AED78[];
extern UnkStruct_800B15D8 D_800B15D8[];
extern u8 D_802A0D50[];
extern s32 D_802AC880;
extern s32 D_802AC884;

void func_80243890(void) {
    func_80297D30(12, D_802A0D50);
    D_802AC880 = 0;
}

void func_802438BC(s32 *arg0) {
    s32 maxY;
    s32 maxX;
    s32 i;
    s32 x;
    s32 y;

    arg0[1] = D_800B15D8[0].unk0;
    maxY = 0;
    maxX = 0;
    for (i = 0; i < D_800B15D8[0].unk0; i++) {
        x = D_800B15D8[i].unkE * 8;
        y = D_800B15D8[i].unkF * 8;
        if (maxX < x) {
            maxX = x;
        }
        if (maxY < y) {
            maxY = y;
        }
    }
    arg0[0] = maxX;
    arg0[2] = maxY;
}

s32 func_80243954(s32 arg0) {
    if (D_800AED78[arg0].unk0 != NULL) {
        func_8022A1E8(D_800AED78[arg0].unk0);
        func_8026CCBC(D_800AED78[arg0].unk8);
        D_800AED78[arg0].unk0 = NULL;
        return 0;
    }
    return -1;
}

void func_802439C0(void) {
    s32 i;

    for (i = 0; i < D_802AC884; i++) {
        if (D_800AED78[i].unk0 != NULL) {
            func_80243954(i);
        }
    }
}

void func_80243A30(void) {
    func_802439C0();
}

void func_80243A50(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s16 arg5) {
    void *temp = func_8026CE28(arg0);

    D_800AED78[D_802AC884].unk4 = temp;
    D_800AED78[D_802AC884].unk0 = func_8022A6C4(temp, arg4);
    D_800AED78[D_802AC884].unk0->unk10 = arg1;
    D_800AED78[D_802AC884].unk0->unk14 = arg2;
    D_800AED78[D_802AC884].unk0->unk18 = arg3;
    if (arg4 == 0x60) {
        D_800AED78[D_802AC884].unk0->unkC |= 0x80;
        if (arg5 != 0) {
            D_800AED78[D_802AC884].unk0->unk36 = arg5;
        }
    }
    D_800AED78[D_802AC884].unk8 = arg0;
    D_802AC884++;
}

void func_80243BA8(s32 arg0) {
    D_802AC884 = 0;
    func_80243A50(arg0, 0.0f, 0.0f, 0.0f, 0x50, 0);
}
