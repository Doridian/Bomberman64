#include "common.h"

void func_80226E40(s32);
void func_8022946C(void *, s32, void *);
void func_8023AA78(s32);
void func_8023AE6C(s32, s32, s32);
void func_8023AED0(s32);
s32 func_80238A10(void *, s32, s32, s32, s32);
void func_80239094(void);
void func_8026D3AC(void *);
void *func_8026D4B0(void *, s32);
void func_80282144(s32, s32, s32, f32);
void func_8028A0B4(void);
void func_80297114(void);
void func_8029738C(void);
void *func_8022A328(void *, s32, s32, s32, s32);
void free(void *);
void *malloc(s32);
void func_80227D50(s32, s32, s32, s32, s32);
void func_802276D4(s32);
void func_80238EA8(s32);
void func_80239430(void);
s32 func_80239FF8(s32);
s32 *func_8023A840(void);
void func_80243DEC(s32);
void func_8026BEB0(void);
void func_8026C8E8(void);
void func_80277E1C(void);
void func_80297A34(void);

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ void *unkC;
    /* 0x10 */ u8 unk10[1];
} UnkStruct_80296B3C;

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_80297564; /* size 0x8 */

void func_80297564(void *, UnkStruct_80297564 **);

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
} UnkStruct_80297858;

void func_80297858(UnkStruct_80297858 *, UnkStruct_80297564 **);

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
} UnkStruct_80297804;

typedef struct {
    /* 0x000 */ void *unk0;
    /* 0x004 */ s32 unk4;
    /* 0x008 */ s32 unk8;
    /* 0x00C */ void *unkC;
    /* 0x010 */ u8 unk10[0xA00];
} UnkStruct_802B03C0; /* size 0xA10 */

extern s32 D_802A2C70;
extern s32 D_802A2C74[];
extern s32 D_802A2C88[];
extern s32 D_802A2C9C[];
extern u8 D_802A2CB0[];
extern s32 D_802B03A0;
extern s32 D_802B03A4;
extern s32 D_802B03A8;
extern UnkStruct_80296B3C *D_802B03B0[4];
extern UnkStruct_802B03C0 D_802B03C0[5];
extern s32 D_802AC5C0;
extern s32 D_802AC5D0;
extern s32 D_802B3614;
extern s32 D_802B3610;

void func_802969F0(void) {
    func_80297D30(49, D_802A2CB0);
}

void func_80296A18(s32 arg0) {
    D_802A2C70 = arg0;
}

s32 func_80296A24(void) {
    return D_802A2C70;
}

void func_80296A34(void) {
    if (D_802A2C70 == 0) {
        func_8023AE6C(0x1B, 0x10, 0);
    } else {
        func_8023AE6C(0x1A, 0x10, 4);
    }
}

void func_80296A80(void) {
    func_8023AE6C(D_802A2C74[D_802B03A4], D_802A2C88[D_802B03A4], D_802A2C9C[D_802B03A4]);
    func_8028A0B4();
}

void func_80296AD8(s32 arg0) {
    s32 i;

    for (i = 0; i < arg0; i++) {
        if (D_802B03A0 == 0) {
            func_80239094();
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/B11F0/func_80296B3C.s")

UnkStruct_802B03C0 *func_80296BEC(s32 arg0) {
    return &D_802B03C0[arg0];
}

#pragma GLOBAL_ASM("asm/nonmatchings/B11F0/func_80296C10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/B11F0/func_80296D4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/B11F0/func_80297114.s")

void func_80297240(UnkStruct_80296B3C *arg0) {
    s32 i;

    if (arg0->unkC != NULL) {
        for (i = 0; arg0 != D_802B03B0[i]; i++) {
        }
        if (i < 4) {
            D_802B03B0[i] = NULL;
            func_8026D3AC(arg0->unkC);
            arg0->unkC = NULL;
            D_802B03A8--;
        }
    }
}

void func_802972D0(void) {
    UnkStruct_80296B3C **p;
    s32 i;

    for (p = D_802B03B0; p < D_802B03B0 + 4; p++) {
        if (*p != NULL) {
            func_80297240(*p);
        }
    }
    for (i = 0; i < 4; i++) {
        free(D_802B03C0[i].unk0);
        D_802B03C0[i].unk0 = NULL;
    }
    if (D_802B03C0[i].unkC != NULL) {
        func_8026D3AC(D_802B03C0[i].unkC);
        D_802B03C0[i].unkC = NULL;
    }
    if (D_802B03C0[i].unk0 != NULL) {
        free(D_802B03C0[i].unk0);
        D_802B03C0[i].unk0 = NULL;
    }
}

void func_8029738C(void) {
    s32 *flags = func_8023A840();

    func_80243DEC(0);
    if (D_802B03A0 != 0) {
        func_8026C8E8();
        func_8026BEB0();
        *flags &= ~0xC;
        func_8028A0B4();
        if (D_802A2C70 == 0) {
            func_802972D0();
        }
        if (D_802B3614 != -1) {
            func_80238EA8(D_802B3614);
        }
        func_8023AA78(0);
        func_80227D50(D_802AC5C0, 8, 6, 0x130, 0xE4);
        func_802276D4(0);
        func_80282144(0, 0, 0, 0.0f);
        if (D_802A2C70 == 0) {
            D_802A2C70 = 1;
        } else {
            D_802A2C70 = 0;
        }
    }
}

void func_80297498(void) {
    D_802B03A0 = 1;
    func_8029738C();
}

s32 func_802974C0(void) {
    return D_802B03A0;
}

s32 func_802974D0(void) {
    return D_802B3610;
}

void func_802974E0(void) {
    func_80282144(0, 0, 0, 0.0f);
}

void func_8029750C(s32 arg0) {
    D_802B3610 = 1;
    func_8023AA78(1);
    func_8023AED0(10);
    func_80238A10(func_80297114, 0, 0, 0, 0x150);
}

#pragma GLOBAL_ASM("asm/nonmatchings/B11F0/func_80297564.s")

void func_802977E4(void *arg0) {
    func_8022A1E8(arg0);
}

UnkStruct_80297804 *func_80297804(void) {
    UnkStruct_80297804 *obj = func_8022A328(func_80297858, 0x3F, 1, 0, 0);

    if (obj != NULL) {
        obj->unkC |= 0x410;
        return obj;
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/B11F0/func_80297858.s")

void func_80297A34(void) {
    while (1) {
        if ((func_80239FF8(0) & 0x1000) && !(D_802AC5D0 & 1)) {
            break;
        }
        func_80239094();
    }
    func_8023AA78(1);
    func_80226E40(1);
    D_802B03A0 = 1;
    func_8023AED0(0x20);
    func_8026C8E8();
    func_8023AE6C(0x20, 0x11, 4);
    D_802B3614 = -1;
    func_80239430();
}

void func_80297ADC(void) {
    s32 *flags = func_8023A840();
    s32 i;

    *flags |= 4;
    func_8028A0B4();
    func_80277E1C();
    func_80243DEC(0);
    D_802B03A0 = 0;
    D_802B3614 = func_80238A10(func_80297A34, 0, 0, 0, 9);
    D_802B03A4 = 0;
    if (D_802A2C70 != 0) {
        *flags &= ~8;
    } else {
        *flags |= 8;
        D_802B03A8 = 0;
        for (i = 0; i < 4; i++) {
            D_802B03B0[i] = NULL;
            D_802B03C0[i].unk4 = 0x94;
            D_802B03C0[i].unk8 = 0x6F;
            D_802B03C0[i].unk0 = malloc(0x8058);
            D_802B03C0[i].unkC = NULL;
        }
        D_802B03C0[i].unk0 = malloc(0x25818);
        D_802B03C0[i].unkC = NULL;
    }
}
