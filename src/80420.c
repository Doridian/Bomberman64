#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_80265C20_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_80265C20_Inner *unk40;
} UnkStruct_80265C20;

typedef struct {
    f32 x, y, z;
} Vec3f_802AD110;

void func_80299170(s32, s32, s32, s32);
void func_802988E0(f32 *, f32 *, f32 *);
void func_802988D8(f32, f32, f32);
void func_802988B8(f32, f32, f32);
void func_80298BE8(s32);

extern Vec3f_802AD110 D_802AD110;
extern s32 D_802AD104;
extern s32 D_802AD108;

void func_80265C20(s32 arg0, UnkStruct_80265C20 *arg1) {
    UnkStruct_80265C20_Inner *p;

    p = arg1->unk40;
    if (1) { /* fake (the permuter's): without it arg1 is spilled */
    }
    func_80299170(arg0, p->unk10, p->unk14, p->unk18);
}

void func_80265C54(f32 arg0) {
    f32 sp1C;

    func_802988E0(&sp1C, NULL, NULL);
    func_802988D8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_80265C9C(f32 arg0, f32 arg1, f32 arg2) {
    func_802988B8(D_802AD110.x, D_802AD110.y, D_802AD110.z);
    func_802988D8(arg0, arg1, arg2);
    func_80298BE8(0xB4);
}

void func_80265CF8(void) {
    D_802AD104 = -1;
    D_802AD108 = -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/80420/func_80265D10.s")
