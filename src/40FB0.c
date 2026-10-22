#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
} UnkStruct_8019B0D0; /* size 0x2 */

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ struct {
        /* 0x00 */ u8 unk0;
        /* 0x01 */ u8 unk1;
        /* 0x02 */ u8 unk2;
    } unk1[1];
} UnkStruct_8019C0D0;

void func_802267B0(u32 arg0);
void func_80226818(void);
void func_80297D50(void *, s32);
void func_80297D58(void *, s32);

extern UnkStruct_8019B0D0 D_8019B0D0[];
extern UnkStruct_8019C0D0 D_8019C0D0;
extern u8 D_8029F5D0[];
extern s32 D_802A5320;
extern u32 D_802A5324;
extern s32 D_802A5328;
extern s32 D_802A532C;

void func_8022691C(s32 arg0) {
    struct UnkStruct_80225CC0 *file;
    s32 size;
    s32 id;
    s32 pad[2]; /* fake: unused, the original's frame has 8 more bytes of locals */

    if (D_802A5328 != arg0) {
        D_802A5328 = arg0;
        func_802267B0((D_8019B0D0[arg0].unk0 << 17) + (D_8019B0D0[arg0].unk1 << 11));
        file = func_80226604(0, 1);
        size = func_802266DC(file);
        func_8022616C((u8 *) &D_8019C0D0, 1, size, file);
        for (size = 0; size < D_8019C0D0.unk0; size++) {
            id = (D_8019C0D0.unk1[size].unk0 << 8) + D_8019C0D0.unk1[size].unk1;
            if (id == arg0) {
                id = D_8019C0D0.unk1[size].unk2;
                break;
            }
        }
        func_80226368(file);
        file = func_80226604(id, 1);
        func_8022616C((u8 *) &size, 4, 1, file);
        func_80297D58((void *) 0x80043000, 0x20000);
        func_80297D50((void *) 0x80043000, 0x20000);
        func_80292BD0(file, (void *) 0x80043000, size);
        func_80297D60((void *) 0x80043000, 0x20000);
        func_80226368(file);
        func_802267E0(0x18);
        D_802A532C = ((s32 (*)(void)) 0x80043000)();
    }
}

void func_802268F4(void) {
    ((void (*)(void)) D_802A532C)();
}

void func_80226860(void) {
    func_80297D30(11, D_8029F5D0);
    D_802A5320 = -1;
    D_802A5324 = -1;
    D_802A5328 = -1;
    func_80226818();
    func_802267E0(0x18);
}

void func_80226818(void) {
    if (D_802A5320 == -1) {
        func_80297EC0(D_8019B0D0, 0x1000, 0x30800);
        D_802A5320 = 0;
    }
}

void func_802267E0(s32 arg0) {
    func_802267B0(arg0 << 17);
}

void func_802267B0(u32 arg0) {
    if (D_802A5324 != arg0) {
        D_802A5324 = arg0;
        func_802266E8(arg0);
    }
}
