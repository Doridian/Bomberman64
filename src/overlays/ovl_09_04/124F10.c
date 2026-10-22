#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl09_04_800431CC_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl09_04_800431CC_Inner *unk40;
} UnkStruct_ovl09_04_800431CC;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl09_04_80044A70;

void func_ovl09_04_80043328(const char *);
void func_ovl09_04_80043668(s32);
void func_ovl09_04_80043680(s32);
void func_ovl09_04_80043818(void);
void func_ovl09_04_80043878(void);
void func_ovl09_04_80043F08(s32);
void func_ovl09_04_80043FD8(f32, f32);
void func_ovl09_04_80044380(f32, f32);
void func_ovl09_04_80044520(u32 (*)[3]);
void func_ovl09_04_80044760(s32, s32, s32, s32);
void func_ovl09_04_80043ED0(f32 *, f32 *, f32 *);
void func_ovl09_04_80043EC8(f32, f32, f32);
void func_ovl09_04_80043EA8(f32, f32, f32);
void func_ovl09_04_800441D8(s32);

/* .bss: IDO lays it out in the order it first sees each variable, so the
 * definitions come before the code (docs/DECOMPILING.md, "Data"). */
u8 D_ovl09_04_80044A40[0x24]; /* not referenced here */
s32 D_ovl09_04_80044A64;
s32 D_ovl09_04_80044A68;
u8 D_ovl09_04_80044A6C[4]; /* not referenced here */
Vec3f_ovl09_04_80044A70 D_ovl09_04_80044A70;
f32 D_ovl09_04_80044A7C;
f32 D_ovl09_04_80044A80;

/* .data: passed to func_ovl09_04_80044520, as in ovl_09_01; three 12-byte
 * records and a zero one (or three and the section's padding). */
u32 D_ovl09_04_80044960[][3] = {
    { 0x008C0000, 0, 4 },
    { 0x008D0002, 0, 4 },
    { 0x008E0002, 0, 4 },
    { 0, 0, 0 },
};

/* The overlay's handler: the entry returns it to the loader.  Cases 1 and
 * 17 are empty but set the jump table's range (.rodata). */
void func_ovl09_04_80043010(s32 arg0) {
    f32 angle;
    f32 wrapped;

    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl09_04_80044520(D_ovl09_04_80044960);
            func_ovl09_04_80043668(0x138);
            func_ovl09_04_80043680(0x139);
            func_ovl09_04_80043818();
            func_ovl09_04_80043878();
            func_ovl09_04_80043F08(0x40);
            func_ovl09_04_80043FD8(400.0f, 800.0f);
            D_ovl09_04_80044A7C = 45.0f;
            D_ovl09_04_80044A80 = 45.0f;
            break;
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
        case 16:
            break;
        case 17:
            break;
        case 0x50:
            func_ovl09_04_80043328("debmap0 : Mapchange happened!\n");
            break;
        case 0x51:
            func_ovl09_04_80043328("debmap0 : Playerout happened!\n");
            break;
        case 0x52:
            break;
        case 0x53:
            func_ovl09_04_80043328("debmap0 : Evlevel2 happened!\n");
            break;
        case 3:
            angle = D_ovl09_04_80044A7C + 1.0f;
            if (angle >= 360.0f) {
                D_ovl09_04_80044A7C = angle - 360.0f;
            } else {
                if (angle < 0.0f) {
                    wrapped = angle + 360.0f;
                } else {
                    wrapped = angle;
                }
                D_ovl09_04_80044A7C = wrapped;
            }
            func_ovl09_04_80044380(D_ovl09_04_80044A7C, D_ovl09_04_80044A80);
            break;
    }
}

void func_ovl09_04_800431CC(s32 arg0, UnkStruct_ovl09_04_800431CC *arg1) {
    UnkStruct_ovl09_04_800431CC_Inner *p;

    p = arg1->unk40;
    if (1) { /* fake, as in 80420.c's func_80265C20: without it arg1 is spilled */
    }
    func_ovl09_04_80044760(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl09_04_80043200(f32 arg0) {
    f32 sp1C;

    func_ovl09_04_80043ED0(&sp1C, NULL, NULL);
    func_ovl09_04_80043EC8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl09_04_80043248(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl09_04_80043EA8(D_ovl09_04_80044A70.x, D_ovl09_04_80044A70.y, D_ovl09_04_80044A70.z);
    func_ovl09_04_80043EC8(arg0, arg1, arg2);
    func_ovl09_04_800441D8(0xB4);
}

void func_ovl09_04_800432A4(void) {
    D_ovl09_04_80044A64 = -1;
    D_ovl09_04_80044A68 = -1;
}

void func_ovl09_04_800432BC(void) {
}

void func_ovl09_04_800432C4(void) {
}

void func_ovl09_04_800432CC(void) {
}

void func_ovl09_04_800432D4(void) {
}

void func_ovl09_04_800432DC(void) {
}

void func_ovl09_04_800432E4(void) {
}

void func_ovl09_04_800432EC(void) {
}

void func_ovl09_04_800432F4(void) {
}

void func_ovl09_04_800432FC(void) {
}

void func_ovl09_04_80043304(void) {
}

void func_ovl09_04_8004330C(void) {
}

void func_ovl09_04_80043314(void) {
}
