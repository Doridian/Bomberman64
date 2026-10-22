#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
} UnkStruct_802AFC44;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ void *unk4;
} UnkStruct_800BCDE8; /* size 0x8 */

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_8026D2C4; /* size 0x8 */

void *func_8022A328(void *, s32, s32, s32, s32);
void func_8023903C(s32);
void func_80239094(void);
s32 func_802399AC(s32);
s32 *func_8023A840(void);
void func_8023A864(s32);
void func_80243698(s32);
void func_8026C660(s32);
void func_8026CBD4(void *);
void func_8026D2C4(s32, UnkStruct_8026D2C4 **);

extern u8 D_1000000[];
extern UnkStruct_800BCDE8 D_800BCDE8[64];
extern void *D_802A13E0;
extern u8 D_802A13E4[];
extern s32 D_802AFC40;
extern UnkStruct_802AFC44 *D_802AFC44;
extern UnkStruct_802AFC44 *D_802AFC48;

void func_8026CF30(void) {
    s32 i;

    func_80297D30(21, D_802A13E4);
    for (i = 0; i < 64; i++) {
        D_800BCDE8[i].unk4 = NULL;
        D_800BCDE8[i].unk0 = 0;
    }
}

void func_8026CF90(void) {
    if (D_802A13E0 != NULL) {
        D_802AFC40 = 1;
        func_8022A1E8(D_802AFC44);
        func_8022A1E8(D_802AFC48);
        func_8026CBD4(D_802A13E0);
        D_802A13E0 = NULL;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/87730/func_8026CFF4.s")

void func_8026D2A4(s32 arg0, s32 arg1) {
    func_8026CFF4(arg0, arg1, 0);
}

void func_8026D2C4(s32 arg0, UnkStruct_8026D2C4 **arg1) {
    UnkStruct_8026D2C4 *gfx = *arg1;

    /* one line per command, as gbi.h's macros expand: IDO allocates
     * temporaries per source line */
    { UnkStruct_8026D2C4 *g = gfx++; g->w0 = 0xFA000000; g->w1 = 0x80; }
    { UnkStruct_8026D2C4 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFDF6FB; }
    { UnkStruct_8026D2C4 *g = gfx++; g->w0 = 0xFF10013F; g->w1 = (u32) D_1000000; }
    { UnkStruct_8026D2C4 *g = gfx++; g->w0 = 0xF7000000; g->w1 = 0x10001; }
    { UnkStruct_8026D2C4 *g = gfx++; g->w0 = 0xF648C384; g->w1 = 0x702A8; }
    *arg1 = gfx;
}

void func_8026D354(void *arg0) {
    s32 i;

    func_8022A1E8(arg0);
    for (i = 0; i < 64; i++) {
        if (arg0 == D_800BCDE8[i].unk4) {
            D_800BCDE8[i].unk4 = NULL;
            break;
        }
    }
}

void func_8026D3AC(void *arg0) {
    s32 i;

    func_8022A1E8(arg0);
    for (i = 0; i < 64; i++) {
        if (arg0 == D_800BCDE8[i].unk4) {
            if (D_800BCDE8[i].unk0 != -1) {
                func_8026CCBC(D_800BCDE8[i].unk0);
            }
            D_800BCDE8[i].unk4 = NULL;
            D_800BCDE8[i].unk0 = 0;
            break;
        }
    }
}

s32 func_8026D428(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        if (D_800BCDE8[i].unk4 == NULL) {
            return i;
        }
    }
    return -1;
}

void func_8026D4B0(void *arg0, s32 arg1) {
    s32 i = func_8026D428();

    D_800BCDE8[i].unk0 = -1;
    D_800BCDE8[i].unk4 = func_8022A328(arg0, arg1 + 0x40, 1, 0, 0);
}

void func_8026D518(s32 arg0, s32 arg1) {
    s32 i;
    void *data;

    data = func_8026CE28(arg0);
    i = func_8026D428();

    D_800BCDE8[i].unk0 = arg0;
    D_800BCDE8[i].unk4 = func_8022A6C4(data, arg1 + 0x40);
}
