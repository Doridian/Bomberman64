#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl09_01_800431C8_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl09_01_800431C8_Inner *unk40;
} UnkStruct_ovl09_01_800431C8;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl09_01_80044A10;

void func_ovl09_01_80043668(s32);
void func_ovl09_01_80043680(s32);
void func_ovl09_01_80043818(void);
void func_ovl09_01_80043820(s32, s32, s32);
void func_ovl09_01_80043860(s32);
void func_ovl09_01_80043868(s32, s32, f32, s32, s32, s32, s32);
void func_ovl09_01_80043878(void);
void func_ovl09_01_80043890(s32);
void func_ovl09_01_80043EA8(f32, f32, f32);
void func_ovl09_01_80043EC8(f32, f32, f32);
void func_ovl09_01_80043ED0(f32 *, f32 *, f32 *);
void func_ovl09_01_800441C8(void);
void func_ovl09_01_800441D8(s32);
void func_ovl09_01_80044520(u32 (*)[3]);
void func_ovl09_01_800446C8(s32, s32, s32);
void func_ovl09_01_80044760(s32, s32, s32, s32);

/* .bss: IDO lays it out in the order it first sees each variable, so the
 * definitions come before the code (docs/DECOMPILING.md, "Data"). */
u8 D_ovl09_01_800449E0[0x24]; /* not referenced here */
s32 D_ovl09_01_80044A04;
s32 D_ovl09_01_80044A08;
u8 D_ovl09_01_80044A0C[4]; /* not referenced here */
Vec3f_ovl09_01_80044A10 D_ovl09_01_80044A10;
f32 D_ovl09_01_80044A1C;
f32 D_ovl09_01_80044A20;

/* .data: passed to func_ovl09_01_80044520; three 12-byte records and a
 * zero one (or three and the section's padding: the same bytes). */
u32 D_ovl09_01_80044960[][3] = {
    { 0x008C0000, 0, 4 },
    { 0x008D0002, 0, 4 },
    { 0x008E0002, 0, 4 },
    { 0, 0, 0 },
};

/* The overlay's handler: the entry returns it to the loader.  Cases 1 and
 * 17 are empty but set the jump table's range (.rodata). */
void func_ovl09_01_80043010(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl09_01_80044520(D_ovl09_01_80044960);
            func_ovl09_01_800446C8(0, 0, 0xDE);
            func_ovl09_01_800446C8(1, 0, 0xDE);
            func_ovl09_01_800446C8(2, 0, 0xDE);
            func_ovl09_01_800446C8(3, 0, 0xDE);
            func_ovl09_01_800446C8(4, 0, 0xDE);
            func_ovl09_01_800446C8(5, 0, 0xDE);
            func_ovl09_01_80043668(0x132);
            func_ovl09_01_80043680(0x133);
            func_ovl09_01_80043820(9, 0, 0xC);
            func_ovl09_01_80043818();
            func_ovl09_01_80043878();
            D_ovl09_01_80044A1C = 45.0f;
            D_ovl09_01_80044A20 = 45.0f;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            break;
        case 16:
            func_ovl09_01_80043860(0x40);
            break;
        case 17:
            break;
        case 0x50:
            break;
        case 0x51:
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl09_01_8004316C(void) {
    func_ovl09_01_800441D8(0xA);
    func_ovl09_01_80043868(0, 3, 4.0f, 0, 1, 0, 0);
    func_ovl09_01_800441D8(0xA);
    func_ovl09_01_80043890(0x4000000);
    func_ovl09_01_800441C8();
}

void func_ovl09_01_800431C8(s32 arg0, UnkStruct_ovl09_01_800431C8 *arg1) {
    UnkStruct_ovl09_01_800431C8_Inner *p;

    p = arg1->unk40;
    if (1) { /* fake, as in 80420.c's func_80265C20: without it arg1 is spilled */
    }
    func_ovl09_01_80044760(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl09_01_800431FC(f32 arg0) {
    f32 sp1C;

    func_ovl09_01_80043ED0(&sp1C, NULL, NULL);
    func_ovl09_01_80043EC8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl09_01_80043244(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl09_01_80043EA8(D_ovl09_01_80044A10.x, D_ovl09_01_80044A10.y, D_ovl09_01_80044A10.z);
    func_ovl09_01_80043EC8(arg0, arg1, arg2);
    func_ovl09_01_800441D8(0xB4);
}

void func_ovl09_01_800432A0(void) {
    D_ovl09_01_80044A04 = -1;
    D_ovl09_01_80044A08 = -1;
}

void func_ovl09_01_800432B8(void) {
}

void func_ovl09_01_800432C0(void) {
}

void func_ovl09_01_800432C8(void) {
}

void func_ovl09_01_800432D0(void) {
}

void func_ovl09_01_800432D8(void) {
}

void func_ovl09_01_800432E0(void) {
}

void func_ovl09_01_800432E8(void) {
}

void func_ovl09_01_800432F0(void) {
}

void func_ovl09_01_800432F8(void) {
}

void func_ovl09_01_80043300(void) {
}

void func_ovl09_01_80043308(void) {
}

void func_ovl09_01_80043310(void) {
}
