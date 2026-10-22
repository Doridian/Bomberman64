#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} UnkStruct_8027EFD8;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
} UnkStruct_8027F0C4; /* size 0x8 */

typedef struct {
    /* 0x00 */ UnkStruct_8027EFD8 *unk0;
    /* 0x04 */ UnkStruct_8027F0C4 *unk4;
    /* 0x08 */ void *unk8;
    /* 0x0C */ s32 (*unkC)(u8, u16);
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 unk16;
} UnkStruct_802A15C0;

void func_80239094(void);
s32 func_802399AC(s32);
s32 func_80239EE8(s32);
s32 func_80239F70(void);
s32 func_8023A038(s32);
void func_8026C660(s32);
s32 func_8027EDC8(s32 arg0);
static void func_8027EFD8(f32 arg0, f32 arg1);
s32 func_8027F0C4(s32 arg0);
static u16 func_8027F0B4(u16 dir, u16 buttons);
static void func_8027F0BC(UnkStruct_8027F0C4 *entry, u16 dir);
static void *func_8027F4B0(u16 arg0);
static void func_8027F420(void);

extern UnkStruct_802A15C0 D_802A15C0;
extern s32 D_802A15D8;
extern u8 D_802A15DC[];
extern s16 D_802A1608[];

void func_8027F6B4(void) {
    func_80297D30(0x24, D_802A15DC);
    func_8027F420();
    D_802A15C0.unk16 = 1;
    D_802A15C0.unk0 = NULL;
    D_802A15C0.unk4 = NULL;
    D_802A15C0.unk8 = NULL;
    D_802A15C0.unkC = NULL;
}

void func_8027F658(s32 (*arg0)(u8, u16), UnkStruct_8027F0C4 *arg1, u16 arg2, u16 arg3, u16 arg4) {
    D_802A15C0.unk4 = arg1;
    D_802A15C0.unk10 = arg2;
    D_802A15C0.unk12 = arg3;
    D_802A15C0.unkC = arg0;
    D_802A15C0.unk14 = arg4;
    D_802A15D8 = 0;
    func_8027F4B0(arg2);
}

void func_8027F64C(s32 arg0) {
    D_802A15D8 = arg0;
}

void func_8027F63C(u8 arg0) {
    D_802A15C0.unk16 = arg0;
}

void func_8027F5A8(u16 arg0, u16 arg1, u16 arg2) {
    u8 sp2F = D_802A15C0.unk16;

    func_8027F420();
    D_802A15C0.unk12 = arg1;
    D_802A15C0.unk14 = arg2;
    func_8027F4B0(arg0);
    D_802A15C0.unk16 = sp2F;
}

static void *func_8027F4B0(u16 arg0) {
    D_802A15C0.unk8 = func_8026CE28(arg0);
    D_802A15C0.unk0 = func_8022A6C4(D_802A15C0.unk8, 0x40);
    D_802A15C0.unk16 = 1;
    D_802A15C0.unk10 = arg0;
    D_802A15C0.unk0->unk18 = D_802A15C0.unk12;
    D_802A15C0.unk0->unk1C = D_802A15C0.unk14;
    func_8027EFD8(D_802A15C0.unk4->unk0, D_802A15C0.unk4->unk2);
    return D_802A15C0.unk0;
}

void func_8027F498(UnkStruct_8027F0C4 *arg0) {
    D_802A15C0.unk4 = arg0;
    D_802A15C0.unk16 = 1;
}

void func_8027F428(void) {
    func_8027F420();
    D_802A15C0.unk0 = NULL;
    D_802A15C0.unk4 = NULL;
    D_802A15C0.unk8 = NULL;
    D_802A15C0.unkC = NULL;
    D_802A15C0.unk16 = 1;
}

static void func_8027F420(void) {
    if (D_802A15C0.unk0 != NULL) {
        func_8022A1E8(D_802A15C0.unk0);
    }
    if (D_802A15C0.unk8 != NULL) {
        func_8026CCBC(D_802A15C0.unk10);
    }
}

void func_8027F400(void) {
    func_8027F0C4(0);
}

/* unnamed in the asm: two static functions inlined into func_8027F0C4,
 * which IDO -O3 still emits, empty, after func_8027EFD8 */
static void func_8027F0BC(UnkStruct_8027F0C4 *entry, u16 dir) {
    u8 next;

    if ((next = entry->unk4) != 0 && dir == 0x800) {
        func_8026C660(D_802A15D8);
        D_802A15C0.unk16 = next;
    }
    if ((next = entry->unk5) != 0 && dir == 0x400) {
        func_8026C660(D_802A15D8);
        D_802A15C0.unk16 = next;
    }
    if ((next = entry->unk6) != 0 && dir == 0x200) {
        func_8026C660(D_802A15D8);
        D_802A15C0.unk16 = next;
    }
    if ((next = entry->unk7) != 0 && dir == 0x100) {
        func_8026C660(D_802A15D8);
        D_802A15C0.unk16 = next;
    }
}

static u16 func_8027F0B4(u16 dir, u16 buttons) {
    u16 mask = 0;

    if (dir == 0x800) {
        mask = 0x20;
    }
    if (dir == 0x400) {
        mask |= 0x40;
    }
    if (dir == 0x200) {
        mask |= 0x80;
    }
    if (dir == 0x100) {
        mask |= 0x100;
    }
    if (buttons & 0x8000) {
        mask |= 1;
    }
    if (buttons & 0x4000) {
        mask |= 2;
    }
    if (buttons & 0x1000) {
        mask |= 4;
    }
    if (buttons & 0x20) {
        mask |= 8;
    }
    if (buttons & 0x10) {
        mask |= 0x10;
    }
    if (buttons & 8) {
        mask |= 0x200;
    }
    if (buttons & 4) {
        mask |= 0x400;
    }
    if (buttons & 2) {
        mask |= 0x800;
    }
    if (buttons & 1) {
        mask |= 0x1000;
    }
    return mask;
}

s32 func_8027F0C4(s32 arg0) {
    s32 ret = 1;
    UnkStruct_8027F0C4 *entry;
    u16 dir;
    u16 buttons;
    u16 mask;
    s32 i;

    if (D_802A15C0.unk0 == NULL || D_802A15C0.unk4 == NULL || D_802A15C0.unk8 == NULL || D_802A15C0.unkC == NULL) {
        return 0;
    }
    do {
        entry = &D_802A15C0.unk4[D_802A15C0.unk16 - 1];
        if (arg0) {
            dir = 0;
            buttons = 0;
            for (i = 0; i < 4; i++) {
                if (!(func_8023A038(i) & 8)) {
                    dir |= func_8027EDC8(i);
                    buttons |= func_802399AC(i);
                }
            }
        } else {
            dir = func_8027EDC8(0);
            buttons = func_802399AC(0);
        }
        mask = func_8027F0B4(dir, buttons);
        func_8027F0BC(entry, dir);
        if (mask) {
            ret = D_802A15C0.unkC(D_802A15C0.unk16, mask);
        }
        func_8027EFD8(entry->unk0, entry->unk2);
        func_80239094();
    } while (ret);
    return 1;
}

static void func_8027EFD8(f32 arg0, f32 arg1) {
    D_802A15C0.unk0->unk10 = arg0;
    D_802A15C0.unk0->unk14 = arg1;
    if (D_802A15C0.unk0->unkC == 0x10) {
        D_802A15C0.unk0->unk10 -= D_802A15C0.unk12 >> 1;
        D_802A15C0.unk0->unk14 -= D_802A15C0.unk14 >> 1;
        D_802A15C0.unk0->unk18 = D_802A15C0.unk0->unk10 + D_802A15C0.unk12;
        D_802A15C0.unk0->unk1C = D_802A15C0.unk0->unk14 + D_802A15C0.unk14;
    }
}

UnkStruct_8027EFD8 *func_8027EFC8(void) {
    return D_802A15C0.unk0;
}

void func_8027EFA8(void) {
    func_8027EDC8(0);
}

s32 func_8027EDC8(s32 arg0) {
    s32 dir;
    s32 amount;
    s32 rawx;
    s32 rawy;
    s8 x;
    s8 y;

    rawx = func_80239F70();
    x = rawx * 0.7;
    rawy = func_80239EE8(arg0);
    y = rawy * 0.7;
    if (x >= -11 && x <= 11 && y >= -11 && y <= 11) {
        dir = 0;
        amount = 0;
    } else if (y * y < x * x) {
        if (x < 0) {
            dir = 0x200;
            amount = -x & 0xFF;
        } else {
            dir = 0x100;
            amount = x & 0xFF;
        }
    } else {
        if (y < 0) {
            dir = 0x400;
            amount = -y & 0xFF;
        } else {
            dir = 0x800;
            amount = y & 0xFF;
        }
    }
    if (dir != 0) {
        D_802A1608[arg0] -= amount;
        if (D_802A1608[arg0] > 0) {
            dir = 0;
        } else {
            D_802A1608[arg0] = 700;
        }
    } else {
        D_802A1608[arg0] = 0;
    }
    return dir;
}

void func_8027EDC0(void) {
}
