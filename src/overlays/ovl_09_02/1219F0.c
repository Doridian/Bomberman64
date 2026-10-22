#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl09_02_8004328C_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl09_02_8004328C_Inner *unk40;
} UnkStruct_ovl09_02_8004328C;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl09_02_80044B00;

void func_ovl09_02_800433E8(const char *);
void func_ovl09_02_80043728(s32);
void func_ovl09_02_80043740(s32);
void func_ovl09_02_80043808(void (*)(s32), s32);
void func_ovl09_02_800438D8(void);
void func_ovl09_02_800438E0(s32, s32, s32);
void func_ovl09_02_80043938(void);
void func_ovl09_02_80044020(f32, f32);
void func_ovl09_02_80044440(f32, f32);
void func_ovl09_02_80044778(s32, s32, f32);
s32 func_ovl09_02_800440D8(s32, s32);
void func_ovl09_02_80044820(s32, s32, s32, s32);
void func_ovl09_02_80043F90(f32 *, f32 *, f32 *);
void func_ovl09_02_80043F88(f32, f32, f32);
void func_ovl09_02_80043F68(f32, f32, f32);
void func_ovl09_02_80044298(s32);

/* .bss: IDO lays it out in the order it first sees each variable, so the
 * definitions come before the code (docs/DECOMPILING.md, "Data"). */
u8 D_ovl09_02_80044AD0[0x24]; /* not referenced here */
s32 D_ovl09_02_80044AF4;
s32 D_ovl09_02_80044AF8;
u8 D_ovl09_02_80044AFC[4]; /* not referenced here */
Vec3f_ovl09_02_80044B00 D_ovl09_02_80044B00;
f32 D_ovl09_02_80044B0C;
f32 D_ovl09_02_80044B10;

void func_ovl09_02_80043010(s32 arg0) {
    func_ovl09_02_80044778(arg0, 0x40, 4.0f);
    if (func_ovl09_02_800440D8(arg0, 0x10) != 0) {
        func_ovl09_02_80044778(arg0, 0xC0, 4.0f);
    }
}

void func_ovl09_02_80043058(s32 arg0) {
    func_ovl09_02_80044778(arg0, 0x40, 4.0f);
    if (func_ovl09_02_800440D8(arg0, 0x10) != 0) {
        func_ovl09_02_80044778(arg0, 0xC0, 4.0f);
    }
}

/* The overlay's handler: the entry returns it to the loader.  Cases 1 and
 * 17 are empty but set the jump table's range (.rodata). */
void func_ovl09_02_800430A0(s32 arg0) {
    f32 angle;
    f32 wrapped;
    s32 pad[5]; /* fake: unused, the original frame has 0x14 more bytes of locals */

    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl09_02_80043728(0x134);
            func_ovl09_02_80043740(0x135);
            func_ovl09_02_800438D8();
            func_ovl09_02_800438E0(9, 0, 0xC);
            func_ovl09_02_80043938();
            D_ovl09_02_80044B0C = 45.0f;
            D_ovl09_02_80044B10 = 45.0f;
            func_ovl09_02_80043808(func_ovl09_02_80043058, 1);
            func_ovl09_02_80043808(func_ovl09_02_80043058, 5);
            func_ovl09_02_80043808(func_ovl09_02_80043010, 7);
            func_ovl09_02_80044020(-45.0f, -70.0f);
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
            func_ovl09_02_800433E8("debmap0 : Mapchange happened!\n");
            break;
        case 0x51:
            func_ovl09_02_800433E8("debmap0 : Playerout happened!\n");
            break;
        case 0x52:
            break;
        case 0x53:
            func_ovl09_02_800433E8("debmap0 : Evlevel2 happened!\n");
            break;
        case 3:
            angle = D_ovl09_02_80044B0C + 1.0f;
            if (angle >= 360.0f) {
                D_ovl09_02_80044B0C = angle - 360.0f;
            } else {
                if (angle < 0.0f) {
                    wrapped = angle + 360.0f;
                } else {
                    wrapped = angle;
                }
                D_ovl09_02_80044B0C = wrapped;
            }
            func_ovl09_02_80044440(D_ovl09_02_80044B0C, D_ovl09_02_80044B10);
            break;
    }
}

void func_ovl09_02_8004328C(s32 arg0, UnkStruct_ovl09_02_8004328C *arg1) {
    UnkStruct_ovl09_02_8004328C_Inner *p;

    p = arg1->unk40;
    if (1) { /* fake, as in 80420.c's func_80265C20: without it arg1 is spilled */
    }
    func_ovl09_02_80044820(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl09_02_800432C0(f32 arg0) {
    f32 sp1C;

    func_ovl09_02_80043F90(&sp1C, NULL, NULL);
    func_ovl09_02_80043F88(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl09_02_80043308(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl09_02_80043F68(D_ovl09_02_80044B00.x, D_ovl09_02_80044B00.y, D_ovl09_02_80044B00.z);
    func_ovl09_02_80043F88(arg0, arg1, arg2);
    func_ovl09_02_80044298(0xB4);
}

void func_ovl09_02_80043364(void) {
    D_ovl09_02_80044AF4 = -1;
    D_ovl09_02_80044AF8 = -1;
}

void func_ovl09_02_8004337C(void) {
}

void func_ovl09_02_80043384(void) {
}

void func_ovl09_02_8004338C(void) {
}

void func_ovl09_02_80043394(void) {
}

void func_ovl09_02_8004339C(void) {
}

void func_ovl09_02_800433A4(void) {
}

void func_ovl09_02_800433AC(void) {
}

void func_ovl09_02_800433B4(void) {
}

void func_ovl09_02_800433BC(void) {
}

void func_ovl09_02_800433C4(void) {
}

void func_ovl09_02_800433CC(void) {
}

void func_ovl09_02_800433D4(void) {
}
