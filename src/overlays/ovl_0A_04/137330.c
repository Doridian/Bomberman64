#include "common.h"

/*
 * ovl_0A_04's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).  Statics
 * inlined into every caller leave a `jr ra; nop` stub just before their first
 * caller; the unused ones at the end of the object leave one each.
 *
 * The three `if (!obj && !obj && !obj) {}` are fakes: they generate no code but
 * end a basic block, which the original's scheduling needs after the two
 * animation calls and before the wait (the same spots in ovl_0A_02-03).
 */

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} UnkStruct_ovl0A_04_Anim2;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_ovl0A_04_Anim2 *unk4;
} UnkStruct_ovl0A_04_Anim;

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
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 unk38[0x10];
    /* 0x48 */ UnkStruct_ovl0A_04_Anim *unk48;
} UnkStruct_ovl0A_04_80045D30_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x1C];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[0x14];
    /* 0x40 */ UnkStruct_ovl0A_04_80045D30_Inner *unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
} UnkStruct_ovl0A_04_80045D30;

typedef struct {
    /* 0x00 */ u8 unk0[0x28];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 unk38[8];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
} UnkStruct_ovl0A_04_80045EE0;

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0A_04_80044E78_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl0A_04_80044E78_Inner *unk40;
} UnkStruct_ovl0A_04_80044E78;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl0A_04_800466F0;

typedef UnkStruct_ovl0A_04_80045D30 Obj04;

void func_ovl0A_04_80045308(s32);
void func_ovl0A_04_80045320(s32);
void func_ovl0A_04_80045470(s32);
void func_ovl0A_04_800454B8(void);
void func_ovl0A_04_800454F8(s32);
void func_ovl0A_04_80045500(s32);
void func_ovl0A_04_80045508(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0A_04_80045530(s32);
void func_ovl0A_04_80045540(s32, s32, s32, s32);
Obj04 *func_ovl0A_04_80045548(s32);
void func_ovl0A_04_80045578(s32);
void func_ovl0A_04_80045590(s32, s32);
void func_ovl0A_04_80045A10(UnkStruct_ovl0A_04_80045D30_Inner *, s32);
void func_ovl0A_04_80045A18(UnkStruct_ovl0A_04_80045D30_Inner *, s32, s32, s32);
void func_ovl0A_04_80045A30(UnkStruct_ovl0A_04_80045D30_Inner *, s32, s32);
f32 func_ovl0A_04_80045A48(UnkStruct_ovl0A_04_80045D30_Inner *, s32);
void func_ovl0A_04_80045A60(UnkStruct_ovl0A_04_80045D30_Inner *, s32, s32);
s32 func_ovl0A_04_80045A78(UnkStruct_ovl0A_04_80045D30_Inner *, s32);
void func_ovl0A_04_80045A80(s32, s32, s32);
void func_ovl0A_04_80045B28(s32);
void func_ovl0A_04_80045B38(s32);
void func_ovl0A_04_80045B48(f32, f32, f32);
void func_ovl0A_04_80045B68(f32, f32, f32);
void func_ovl0A_04_80045B70(f32 *, f32 *, f32 *);
void func_ovl0A_04_80045BB0(s32);
void func_ovl0A_04_80045C38(f32 *);
void func_ovl0A_04_80045C40(f32 *);
void func_ovl0A_04_80045D00(s32);
void func_ovl0A_04_80045D08(Obj04 *, s32);
void func_ovl0A_04_80045D10(Obj04 *, s32);
void func_ovl0A_04_80045D20(Obj04 *);
Obj04 *func_ovl0A_04_80045D30(s32, s32, s32, Obj04 *);
void func_ovl0A_04_80045D40(Obj04 *);
void func_ovl0A_04_80045DE0(Obj04 *, Obj04 *);
s32 func_ovl0A_04_80045E58(void (*)(), void *, s32, s32, s32);
void func_ovl0A_04_80045E68(void);
void func_ovl0A_04_80045E78(s32);
Obj04 *func_ovl0A_04_80045E80(void);
s32 func_ovl0A_04_80045EA0(void);
UnkStruct_ovl0A_04_80045EE0 *func_ovl0A_04_80045EE0(s32);
void func_ovl0A_04_80045EF0(UnkStruct_ovl0A_04_80045EE0 *, s32);
f32 func_ovl0A_04_80046000(f32);
f64 func_ovl0A_04_80046010(void);
s32 func_ovl0A_04_80046018(s32);
void func_ovl0A_04_800460D0(s32);
void func_ovl0A_04_800460D8(s32);
s32 func_ovl0A_04_800460E0(s32);
void func_ovl0A_04_80046138(s32);
void func_ovl0A_04_80046150(void);
void func_ovl0A_04_80046158(s32, s32, s32, f32);
void func_ovl0A_04_800461A0(s32);
void func_ovl0A_04_800461A8(s32, s32, s32);
void func_ovl0A_04_80046400(s32, s32, s32, s32);
void func_ovl0A_04_80046560(void);
void func_ovl0A_04_80046570(void);

void func_ovl0A_04_8004452C(void);
void func_ovl0A_04_80044680(void);
void func_ovl0A_04_800448FC(void);

/* .bss: IDO lays it out in the order it first sees each variable, so the
 * definitions come before the code (docs/DECOMPILING.md, "Data"). */
u8 D_ovl0A_04_800466C0[0x24]; /* not referenced here */
s32 D_ovl0A_04_800466E4;
s32 D_ovl0A_04_800466E8;
u8 D_ovl0A_04_800466EC[4]; /* not referenced here */
Vec3f_ovl0A_04_800466F0 D_ovl0A_04_800466F0;
UnkStruct_ovl0A_04_80045EE0 *D_ovl0A_04_800466FC;
s32 D_ovl0A_04_80046700;
s32 D_ovl0A_04_80046704;
Obj04 *D_ovl0A_04_80046708[2]; /* func_ovl0A_04_80043B68 writes six */

void func_ovl0A_04_80043010(void);
void func_ovl0A_04_80043124(void);
static void func_ovl0A_04_800432F0(Obj04 *obj);
static void func_ovl0A_04_800432F8(s32 flag);
void func_ovl0A_04_80043300(void);
void func_ovl0A_04_80043714(void);
void func_ovl0A_04_80043794(void);
Obj04 *func_ovl0A_04_80043918(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl0A_04_800439AC(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_04_80043A28(void);
Obj04 *func_ovl0A_04_80043A90(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_ovl0A_04_80043B68(void);
void func_ovl0A_04_80043CE4(void);
void func_ovl0A_04_80043E00(void);
void func_ovl0A_04_800440BC(void);
static void func_ovl0A_04_800440DC(void);
void func_ovl0A_04_800440E4(void);
static void func_ovl0A_04_80044104(void);
static void func_ovl0A_04_8004410C(void);
void func_ovl0A_04_80044114(void);
void func_ovl0A_04_80044134(void);
void func_ovl0A_04_80044154(Obj04 *arg0);
void func_ovl0A_04_800442B0(Obj04 *arg0);
void func_ovl0A_04_80044364(Obj04 *arg0);
void func_ovl0A_04_800445D8(void);
void func_ovl0A_04_800445F8(s32 arg0);
void func_ovl0A_04_80044AD0(Obj04 **arg0, s32 *arg1, Obj04 **arg2, s32 *arg3, Obj04 **arg4, s32 *arg5, s32 arg6);
void func_ovl0A_04_80044E78(s32 arg0, UnkStruct_ovl0A_04_80044E78 *arg1);
void func_ovl0A_04_80044EAC(f32 arg0);
void func_ovl0A_04_80044EF4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_04_80044F50(void);
static void func_ovl0A_04_80044F68(void);
static void func_ovl0A_04_80044F70(void);
static void func_ovl0A_04_80044F78(void);
static void func_ovl0A_04_80044F80(void);
static void func_ovl0A_04_80044F88(void);
static void func_ovl0A_04_80044F90(void);
static void func_ovl0A_04_80044F98(void);
static void func_ovl0A_04_80044FA0(void);
static void func_ovl0A_04_80044FA8(void);
static void func_ovl0A_04_80044FB0(void);

void func_ovl0A_04_80043010(void);
void func_ovl0A_04_80043124(void);
static void func_ovl0A_04_800432F0(Obj04 *obj);
static void func_ovl0A_04_800432F8(s32 flag);
void func_ovl0A_04_80043300(void);
void func_ovl0A_04_80043714(void);
void func_ovl0A_04_80043794(void);
Obj04 *func_ovl0A_04_80043918(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl0A_04_800439AC(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_04_80043A28(void);
Obj04 *func_ovl0A_04_80043A90(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_ovl0A_04_80043B68(void);
void func_ovl0A_04_80043CE4(void);
void func_ovl0A_04_80043E00(void);
void func_ovl0A_04_800440BC(void);
static void func_ovl0A_04_800440DC(void);
void func_ovl0A_04_800440E4(void);
static void func_ovl0A_04_80044104(void);
static void func_ovl0A_04_8004410C(void);
void func_ovl0A_04_80044114(void);
void func_ovl0A_04_80044134(void);
void func_ovl0A_04_80044154(Obj04 *arg0);
void func_ovl0A_04_800442B0(Obj04 *arg0);
void func_ovl0A_04_80044364(Obj04 *arg0);
void func_ovl0A_04_800445D8(void);
void func_ovl0A_04_800445F8(s32 arg0);
void func_ovl0A_04_80044AD0(Obj04 **arg0, s32 *arg1, Obj04 **arg2, s32 *arg3, Obj04 **arg4, s32 *arg5, s32 arg6);
void func_ovl0A_04_80044E78(s32 arg0, UnkStruct_ovl0A_04_80044E78 *arg1);
void func_ovl0A_04_80044EAC(f32 arg0);
void func_ovl0A_04_80044EF4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_04_80044F50(void);
static void func_ovl0A_04_80044F68(void);
static void func_ovl0A_04_80044F70(void);
static void func_ovl0A_04_80044F78(void);
static void func_ovl0A_04_80044F80(void);
static void func_ovl0A_04_80044F88(void);
static void func_ovl0A_04_80044F90(void);
static void func_ovl0A_04_80044F98(void);
static void func_ovl0A_04_80044FA0(void);
static void func_ovl0A_04_80044FA8(void);
static void func_ovl0A_04_80044FB0(void);

void func_ovl0A_04_80043010(void);
void func_ovl0A_04_80043124(void);
static void func_ovl0A_04_800432F0(Obj04 *obj);
static void func_ovl0A_04_800432F8(s32 flag);
void func_ovl0A_04_80043300(void);
void func_ovl0A_04_80043714(void);
void func_ovl0A_04_80043794(void);
Obj04 *func_ovl0A_04_80043918(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl0A_04_800439AC(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_04_80043A28(void);
Obj04 *func_ovl0A_04_80043A90(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_ovl0A_04_80043B68(void);
void func_ovl0A_04_80043CE4(void);
void func_ovl0A_04_80043E00(void);
void func_ovl0A_04_800440BC(void);
static void func_ovl0A_04_800440DC(void);
void func_ovl0A_04_800440E4(void);
static void func_ovl0A_04_80044104(void);
static void func_ovl0A_04_8004410C(void);
void func_ovl0A_04_80044114(void);
void func_ovl0A_04_80044134(void);
void func_ovl0A_04_80044154(Obj04 *arg0);
void func_ovl0A_04_800442B0(Obj04 *arg0);
void func_ovl0A_04_80044364(Obj04 *arg0);
void func_ovl0A_04_800445D8(void);
void func_ovl0A_04_800445F8(s32 arg0);
void func_ovl0A_04_80044AD0(Obj04 **arg0, s32 *arg1, Obj04 **arg2, s32 *arg3, Obj04 **arg4, s32 *arg5, s32 arg6);
void func_ovl0A_04_80044E78(s32 arg0, UnkStruct_ovl0A_04_80044E78 *arg1);
void func_ovl0A_04_80044EAC(f32 arg0);
void func_ovl0A_04_80044EF4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_04_80044F50(void);
static void func_ovl0A_04_80044F68(void);
static void func_ovl0A_04_80044F70(void);
static void func_ovl0A_04_80044F78(void);
static void func_ovl0A_04_80044F80(void);
static void func_ovl0A_04_80044F88(void);
static void func_ovl0A_04_80044F90(void);
static void func_ovl0A_04_80044F98(void);
static void func_ovl0A_04_80044FA0(void);
static void func_ovl0A_04_80044FA8(void);
static void func_ovl0A_04_80044FB0(void);

void func_ovl0A_04_80043010(void);
void func_ovl0A_04_80043124(void);
static void func_ovl0A_04_800432F0(Obj04 *obj);
static void func_ovl0A_04_800432F8(s32 flag);
void func_ovl0A_04_80043300(void);
void func_ovl0A_04_80043714(void);
void func_ovl0A_04_80043794(void);
Obj04 *func_ovl0A_04_80043918(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl0A_04_800439AC(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_04_80043A28(void);
Obj04 *func_ovl0A_04_80043A90(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_ovl0A_04_80043B68(void);
void func_ovl0A_04_80043CE4(void);
void func_ovl0A_04_80043E00(void);
void func_ovl0A_04_800440BC(void);
static void func_ovl0A_04_800440DC(void);
void func_ovl0A_04_800440E4(void);
static void func_ovl0A_04_80044104(void);
static void func_ovl0A_04_8004410C(void);
void func_ovl0A_04_80044114(void);
void func_ovl0A_04_80044134(void);
void func_ovl0A_04_80044154(Obj04 *arg0);
void func_ovl0A_04_800442B0(Obj04 *arg0);
void func_ovl0A_04_80044364(Obj04 *arg0);
void func_ovl0A_04_800445D8(void);
void func_ovl0A_04_800445F8(s32 arg0);
void func_ovl0A_04_80044AD0(Obj04 **arg0, s32 *arg1, Obj04 **arg2, s32 *arg3, Obj04 **arg4, s32 *arg5, s32 arg6);
void func_ovl0A_04_80044E78(s32 arg0, UnkStruct_ovl0A_04_80044E78 *arg1);
void func_ovl0A_04_80044EAC(f32 arg0);
void func_ovl0A_04_80044EF4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_04_80044F50(void);
static void func_ovl0A_04_80044F68(void);
static void func_ovl0A_04_80044F70(void);
static void func_ovl0A_04_80044F78(void);
static void func_ovl0A_04_80044F80(void);
static void func_ovl0A_04_80044F88(void);
static void func_ovl0A_04_80044F90(void);
static void func_ovl0A_04_80044F98(void);
static void func_ovl0A_04_80044FA0(void);
static void func_ovl0A_04_80044FA8(void);
static void func_ovl0A_04_80044FB0(void);

static void func_ovl0A_04_80044FB0(void) {
}

static void func_ovl0A_04_80044FA8(void) {
}

static void func_ovl0A_04_80044FA0(void) {
}

static void func_ovl0A_04_80044F98(void) {
}

static void func_ovl0A_04_80044F90(void) {
}

static void func_ovl0A_04_80044F88(void) {
}

static void func_ovl0A_04_80044F80(void) {
}

static void func_ovl0A_04_80044F78(void) {
}

static void func_ovl0A_04_80044F70(void) {
}

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0A_04_80044F68(void) {
    D_ovl0A_04_800466C0[0] = D_ovl0A_04_800466EC[0];
}

void func_ovl0A_04_80044F50(void) {
    D_ovl0A_04_800466E4 = -1;
    D_ovl0A_04_800466E8 = -1;
}

void func_ovl0A_04_80044EF4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0A_04_80045B48(D_ovl0A_04_800466F0.x, D_ovl0A_04_800466F0.y, D_ovl0A_04_800466F0.z);
    func_ovl0A_04_80045B68(arg0, arg1, arg2);
    func_ovl0A_04_80045E78(0xB4);
}

void func_ovl0A_04_80044EAC(f32 arg0) {
    f32 sp1C;

    func_ovl0A_04_80045B70(&sp1C, NULL, NULL);
    func_ovl0A_04_80045B68(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0A_04_80044E78(s32 arg0, UnkStruct_ovl0A_04_80044E78 *arg1) {
    UnkStruct_ovl0A_04_80044E78_Inner *p;

    p = arg1->unk40;
    func_ovl0A_04_80046400(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0A_04_80044AD0(Obj04 **arg0, s32 *arg1, Obj04 **arg2, s32 *arg3, Obj04 **arg4, s32 *arg5, s32 arg6) {
    s32 i;

    *arg0 = func_ovl0A_04_80045D30(0x27, 0x01000000, 0xD0, NULL);
    (*arg0)->unk40->unk10 = 1000.0f;
    (*arg0)->unk40->unk14 = 50.0f;
    (*arg0)->unk40->unk18 = -650.0f;
    (*arg0)->unk40->unk30 = 0.5f;
    (*arg0)->unk40->unk28 = (*arg0)->unk40->unk2C = (*arg0)->unk40->unk30;
    (*arg0)->unk40->unk20 = 345.0f;
    *arg1 = func_ovl0A_04_80045A78((*arg0)->unk40, 0x19);
    for (i = 0; i < 0x19; i++) {
        if (i == 0x10 || i == 0x11 || i == 0x12 || i == 0x13) {
            func_ovl0A_04_80045A80(*arg1, i, 0x4F);
        }
    }
    if (arg6 != 0) {
        func_ovl0A_04_80045A80(*arg1, 0xF, 0x4F);
        func_ovl0A_04_80045A80(*arg1, 0xD, 0x4F);
        func_ovl0A_04_80045A80(*arg1, 0xC, 0x4F);
        func_ovl0A_04_80045A80(*arg1, 0xB, 0x4F);
        func_ovl0A_04_80045A80(*arg1, 0xE, 0x4F);
        func_ovl0A_04_80045A80(*arg1, 5, 0x4F);
        func_ovl0A_04_80045A80(*arg1, 2, 0x4F);
        func_ovl0A_04_80045A80(*arg1, 4, 0x4F);
        func_ovl0A_04_80045A80(*arg1, 3, 0x4F);
        *arg2 = func_ovl0A_04_80045D30(0x27, 0x01400000, 0xD0, *arg0);
        *arg3 = func_ovl0A_04_80045A78((*arg2)->unk40, 0x19);
        for (i = 0; i < 0x19; i++) {
            switch (i) {
                case 0xB:
                case 0xC:
                case 0xD:
                case 0xE:
                case 0xF:
                    break;
                default:
                    func_ovl0A_04_80045A80(*arg3, i, 0x4F);
                    break;
            }
        }
        if (arg6 >= 2) {
            *arg4 = func_ovl0A_04_80045D30(0x27, 0x01400000, 0xD0, *arg0);
            *arg5 = func_ovl0A_04_80045A78((*arg4)->unk40, 0x19);
            for (i = 0; i < 0x19; i++) {
                switch (i) {
                    case 0x10:
                    case 0x11:
                    case 0x12:
                    case 0x13:
                        break;
                    default:
                        func_ovl0A_04_80045A80(*arg5, i, 0x4F);
                        break;
                }
            }
        }
    }
    if (arg6 != 0) {
        D_ovl0A_04_80046700 = func_ovl0A_04_80045E58(func_ovl0A_04_800448FC, *arg2, 0, 0, 0x150);
    } else {
        D_ovl0A_04_80046700 = func_ovl0A_04_80045E58(func_ovl0A_04_800448FC, *arg0, 0, 0, 0x150);
    }
    D_ovl0A_04_80046704 = func_ovl0A_04_80045E58(func_ovl0A_04_80044680, *arg0, 0, 0, 0x150);
}

void func_ovl0A_04_800448FC(void) {
    Obj04 *self;
    Obj04 *obj;
    f32 d;
    f32 s;

    self = func_ovl0A_04_80045E80();
    obj = func_ovl0A_04_80045D30(0x34D, 0x01080000, 0xD0, NULL);
    obj->unk40->unk36 = 0x7F;
    obj->unk40->unk10 = 1000.0f;
    obj->unk40->unk14 = -100.0f;
    obj->unk40->unk18 = -650.0f;
    obj->unk40->unk20 = self->unk40->unk20;
    func_ovl0A_04_80045E78(4);
    while (1) {
        obj->unk40->unk10 = self->unk40->unk10;
        obj->unk40->unk18 = self->unk40->unk18;
        d = self->unk40->unk14 - 50.0f;
        if (d <= 500.0f) {
            s = (500.0f - d) * 0.01f;
        } else {
            s = 0.0f;
        }
        obj->unk40->unk30 = 1.0f + s;
        obj->unk40->unk28 = 1.0f + s;
        if (self->unk8 & 0x01000000) {
            func_ovl0A_04_80045D08(obj, 0x01000000);
        } else {
            func_ovl0A_04_80045D10(obj, 0x01000000);
        }
        func_ovl0A_04_80045EA0();
    }
}

void func_ovl0A_04_80044680(void) {
    Obj04 *self;
    Obj04 *obj;
    Obj04 *parts[4];
    s32 i;
    f32 d;
    f32 s;

    self = func_ovl0A_04_80045E80();
    obj = func_ovl0A_04_80045D30(-1, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = 1000.0f;
    obj->unk40->unk14 = -100.0f;
    obj->unk40->unk18 = -650.0f;
    obj->unk40->unk20 = self->unk40->unk20;
    for (i = 0; i < 4; i++) {
        parts[i] = func_ovl0A_04_80045D30(0x34D, 0x01780000, 0xD0, obj);
        parts[i]->unk40->unk36 = 0x7F;
    }
    parts[0]->unk4C = 300.0f;
    parts[1]->unk54 = 300.0f;
    parts[2]->unk4C = -300.0f;
    parts[3]->unk54 = -300.0f;
    func_ovl0A_04_80045E78(4);
    while (1) {
        obj->unk40->unk10 = self->unk40->unk10;
        obj->unk40->unk18 = self->unk40->unk18;
        d = self->unk40->unk14 - 50.0f;
        if (d <= 500.0f) {
            s = (500.0f - d) * 0.01f;
        } else {
            s = 0.0f;
        }
        for (i = 0; i < 4; i++) {
            parts[i]->unk40->unk30 = s * 0.75f;
            parts[i]->unk40->unk28 = s * 0.75f;
        }
        func_ovl0A_04_80045EA0();
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0A_04_800445F8(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0A_04_800445D8();
            break;
        case 16:
            func_ovl0A_04_80044134();
            break;
        case 17:
            func_ovl0A_04_80044114();
            break;
        case 3:
            func_ovl0A_04_800440E4();
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
            break;
        case 1:
            func_ovl0A_04_800440BC();
            break;
    }
}

void func_ovl0A_04_800445D8(void) {
    func_ovl0A_04_800460D8(0x400);
}

void func_ovl0A_04_8004452C(void) {
    Obj04 *self;

    self = func_ovl0A_04_80045E80();
    func_ovl0A_04_800432F8(0x401);
    switch (self->unk28) {
        case 0x33C:
            func_ovl0A_04_80044364(self);
            break;
        case 0x33D:
            func_ovl0A_04_800442B0(self);
            break;
        case 0x33E:
            func_ovl0A_04_80044154(self);
            break;
    }
    func_ovl0A_04_80045E68();
}

void func_ovl0A_04_80044364(Obj04 *arg0) {
    f32 unit;
    f32 speed;

    unit = 360.0f / func_ovl0A_04_80045A48(arg0->unk40, 0);
    while (1) {
        if (func_ovl0A_04_80046018(1) == 0) {
            speed = unit;
            if (func_ovl0A_04_80046018(1) != 0) {
                speed = unit * -1.0f;
            }
            speed *= func_ovl0A_04_80046018(1) + 1;
        } else {
            speed = 0.0f;
        }
        func_ovl0A_04_80045D08(arg0, 0x04000000);
        arg0->unk40->unk48->unk4->unk4 = 0.0f;
        while (!(arg0->unk40->unkC & 0x40)) {
            arg0->unk40->unk20 = (arg0->unk40->unk20 + speed) >= 360.0f ? (arg0->unk40->unk20 + speed) - 360.0f
                               : (arg0->unk40->unk20 + speed) < 0.0f ? (arg0->unk40->unk20 + speed) + 360.0f
                               : (arg0->unk40->unk20 + speed);
            func_ovl0A_04_80045EA0();
        }
        func_ovl0A_04_80045D10(arg0, 0x04000000);
        func_ovl0A_04_80045E78(func_ovl0A_04_80046018(10) + 1);
    }
}

void func_ovl0A_04_800442B0(Obj04 *arg0) {
    while (arg0->unk40->unk20 > 0.0f) {
        func_ovl0A_04_80045EA0();
        arg0->unk40->unk20 -= 6.0f;
    }
    arg0->unk40->unk20 = 0.0f;
    func_ovl0A_04_80045D08(arg0, 0x0C000000);
}

void func_ovl0A_04_80044154(Obj04 *arg0) {
    f32 base;
    f32 amp;
    f32 step;
    f32 angle;

    base = arg0->unk40->unk14;
    amp = func_ovl0A_04_80046010() * 12.5 + 50.0;
    step = func_ovl0A_04_80046010() * 10.0 + 5.0;
    angle = 0.0f;
    while (1) {
        arg0->unk40->unk14 = func_ovl0A_04_80046000(angle) * amp + base;
        angle = (angle + step) >= 360.0f ? (angle + step) - 360.0f
              : (angle + step) < 0.0f ? (angle + step) + 360.0f : (angle + step);
        func_ovl0A_04_80045EA0();
    }
}

void func_ovl0A_04_80044134(void) {
    func_ovl0A_04_80043E00();
}

void func_ovl0A_04_80044114(void) {
    func_ovl0A_04_80044104();
    func_ovl0A_04_8004410C();
    func_ovl0A_04_80043714();
}

static void func_ovl0A_04_8004410C(void) {
}

static void func_ovl0A_04_80044104(void) {
}

void func_ovl0A_04_800440E4(void) {
    func_ovl0A_04_800440DC();
    func_ovl0A_04_800460D0(0x400);
}

/* empty statics the handler's cases inline: only their stubs show */
static void func_ovl0A_04_800440DC(void) {
}

void func_ovl0A_04_800440BC(void) {
    func_ovl0A_04_80046560();
}

void func_ovl0A_04_80043E00(void) {
    s32 i;

    func_ovl0A_04_80045308(0x33A);
    func_ovl0A_04_80045320(0x339);
    for (i = 0; i < 4; i++) {
        func_ovl0A_04_80045590(i, 1);
    }
    func_ovl0A_04_80045540(0, 0xA, 0, 3);
    func_ovl0A_04_80045540(1, 8, 0, 7);
    func_ovl0A_04_80045540(2, 0xC, 0, 8);
    func_ovl0A_04_80045540(3, 0xB, 0, 7);
    func_ovl0A_04_800454B8();
    for (i = 0; i < 4; i++) {
        func_ovl0A_04_80045578(i);
        func_ovl0A_04_800454F8(1);
        func_ovl0A_04_80045500(0);
    }
    func_ovl0A_04_80043CE4();
    func_ovl0A_04_80045D00(0);
    func_ovl0A_04_800460D8(0x401);
    func_ovl0A_04_80045E58(func_ovl0A_04_8004452C, func_ovl0A_04_80043918(0x33C, 1200.0f, 0.0f, 500.0f), 0, 0, 0x150);
    func_ovl0A_04_80045E58(func_ovl0A_04_8004452C, func_ovl0A_04_80043918(0x33C, 700.0f, 0.0f, 550.0f), 0, 0, 0x150);
    func_ovl0A_04_80045E58(func_ovl0A_04_8004452C, func_ovl0A_04_80043918(0x33C, 1000.0f, 0.0f, 800.0f), 0, 0, 0x150);
    func_ovl0A_04_80045E58(func_ovl0A_04_8004452C, func_ovl0A_04_80043918(0x33D, 700.0f, 0.0f, 700.0f), 0, 0, 0x150);
    func_ovl0A_04_80045E58(func_ovl0A_04_8004452C, func_ovl0A_04_80043918(0x33D, 900.0f, 0.0f, 500.0f), 0, 0, 0x150);
    func_ovl0A_04_80045E58(func_ovl0A_04_8004452C, func_ovl0A_04_80043918(0x33D, 1300.0f, 0.0f, 700.0f), 0, 0, 0x150);
    func_ovl0A_04_80045E58(func_ovl0A_04_8004452C, func_ovl0A_04_80043918(0x33E, 700.0f, 200.0f, 500.0f), 0, 0, 0x150);
    func_ovl0A_04_80045E58(func_ovl0A_04_8004452C, func_ovl0A_04_80043918(0x33E, 1200.0f, 300.0f, 400.0f), 0, 0, 0x150);
    func_ovl0A_04_800460D8(0x401);
    func_ovl0A_04_80045E58(func_ovl0A_04_80043794, NULL, 0, 0, 0x130);
    func_ovl0A_04_80046158(0, 0, 0, 100.0f);
}

void func_ovl0A_04_80043CE4(void) {
    D_ovl0A_04_800466FC = func_ovl0A_04_80045EE0(0x33B);
    func_ovl0A_04_80045EF0(D_ovl0A_04_800466FC, 0x20000001);
    D_ovl0A_04_800466FC->unk40 = 1.0f;
    D_ovl0A_04_800466FC->unk44 = 1.0f;
    D_ovl0A_04_800466FC->unk28 = 0.0f;
    D_ovl0A_04_800466FC->unk2C = 120.0f;
    D_ovl0A_04_800466FC->unk30 = D_ovl0A_04_800466FC->unk28 + D_ovl0A_04_800466FC->unk48 * 2.0f;
    D_ovl0A_04_800466FC->unk34 = D_ovl0A_04_800466FC->unk2C + D_ovl0A_04_800466FC->unk4C * 2.0f * 0.8f;
    func_ovl0A_04_800461A0(1);
    func_ovl0A_04_800461A8(0, 0, 0xFF);
    func_ovl0A_04_80045BB0(0x7F);
    func_ovl0A_04_80045B48(1000.0f, 400.0f, 200.0f);
    func_ovl0A_04_80045B38(1);
    func_ovl0A_04_80045B68(0.0f, 20.0f, 1700.0f);
    func_ovl0A_04_80043B68();
    func_ovl0A_04_80043A28();
}

void func_ovl0A_04_80043B68(void) {
    s32 i;

    i = 0;
    D_ovl0A_04_80046708[i++] = func_ovl0A_04_80043A90(1000.0f, 50.0f, -1150.0f, 13.0f, 2.0f);
    D_ovl0A_04_80046708[i++] = func_ovl0A_04_80043A90(1500.0f, 150.0f, -550.0f, 13.0f, 2.0f);
    D_ovl0A_04_80046708[i++] = func_ovl0A_04_80043A90(1000.0f, 1050.0f, -650.0f, 13.0f, 5.0f);
    D_ovl0A_04_80046708[i++] = func_ovl0A_04_80043A90(500.0f, 1050.0f, -450.0f, 13.0f, 5.0f);
    D_ovl0A_04_80046708[i++] = func_ovl0A_04_80043A90(500.0f, 1050.0f, -250.0f, 13.0f, 4.0f);
    D_ovl0A_04_80046708[i++] = func_ovl0A_04_80043A90(1500.0f, 1050.0f, -1050.0f, 13.0f, 5.0f);
}

Obj04 *func_ovl0A_04_80043A90(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    Obj04 *obj;

    obj = func_ovl0A_04_80045D30(0x11D, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = arg0;
    obj->unk40->unk14 = arg1;
    obj->unk40->unk18 = arg2;
    obj->unk40->unkC |= 0x8000;
    func_ovl0A_04_80045A10(obj->unk40, 1);
    func_ovl0A_04_80045A18(obj->unk40, 0x11E, 0, 1);
    obj->unk40->unk28 = arg3;
    obj->unk40->unk2C = arg4;
    obj->unk40->unk36 = 0xCC;
    return obj;
}

void func_ovl0A_04_80043A28(void) {
    func_ovl0A_04_800439AC(500.0f, 0.0f, 400.0f);
    func_ovl0A_04_800439AC(1600.0f, 0.0f, 300.0f);
    func_ovl0A_04_800439AC(500.0f, 0.0f, 700.0f);
    func_ovl0A_04_800439AC(1700.0f, 0.0f, 600.0f);
}

void func_ovl0A_04_800439AC(f32 arg0, f32 arg1, f32 arg2) {
    Obj04 *obj;

    obj = func_ovl0A_04_80045D30(0x97, 0x01000000, 0xD0, NULL);
    obj->unk40->unk10 = arg0;
    obj->unk40->unk14 = arg1;
    obj->unk40->unk18 = arg2;
    func_ovl0A_04_80045D30(0x98, 0x01480000, 0xD0, obj)->unk40->unk36 = 0x80;
}

Obj04 *func_ovl0A_04_80043918(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    Obj04 *obj;

    obj = func_ovl0A_04_80045D30(arg0, 0x01000000, 0xD0, NULL);
    obj->unk40->unk10 = arg1;
    obj->unk40->unk14 = arg2;
    obj->unk40->unk18 = arg3;
    obj->unk40->unk20 = 180.0f;
    func_ovl0A_04_80045D40(obj);
    if (arg0 == 0x33E) {
        func_ovl0A_04_80045D08(obj, 0x0C000000);
    }
    return obj;
}

void func_ovl0A_04_80043794(void) {
    f32 sp4C[3];
    s32 i;
    Obj04 *obj;

    func_ovl0A_04_800432F8(0x400);
    func_ovl0A_04_80045470(0);
    func_ovl0A_04_800454F8(1);
    func_ovl0A_04_800460D0(0x401);
    func_ovl0A_04_80045C40(sp4C);
    sp4C[2] += 450.0;
    func_ovl0A_04_80045C38(sp4C);
    func_ovl0A_04_80046158(0, 0, 0, 0.0f);
    func_ovl0A_04_80046138(1);
    func_ovl0A_04_80046150();
    for (i = 0; i < 4; i++) {
        func_ovl0A_04_80045578(i);
        func_ovl0A_04_80045508(0x80, 3, 2.0f, 0, 1, 0, 0);
        func_ovl0A_04_80045E78(30);
        obj = func_ovl0A_04_80045548(i);
        func_ovl0A_04_80045A60(obj->unk40, 4, 0xE);
        func_ovl0A_04_80045A60(obj->unk40, 5, 0xF);
        func_ovl0A_04_80045530(0x04000000);
        func_ovl0A_04_80045E78(30);
    }
    func_ovl0A_04_80045E78(180);
    func_ovl0A_04_80046570();
    func_ovl0A_04_80045E68();
}

void func_ovl0A_04_80043714(void) {
    func_ovl0A_04_80045B38(1);
    func_ovl0A_04_80045B28(1);
    func_ovl0A_04_80045B68(0.0f, 0.0f, 1000.0f);
    func_ovl0A_04_80045B48(0.0f, 0.0f, 0.0f);
    func_ovl0A_04_80045E58(func_ovl0A_04_80043300, NULL, 0, 0, 0x130);
    func_ovl0A_04_80046158(0, 0, 0, 100.0f);
}

void func_ovl0A_04_80043300(void) {
    Obj04 *obj;
    f32 dx;
    f32 dy;
    f32 dz;
    Vec3f_ovl0A_04_800466F0 a;
    Vec3f_ovl0A_04_800466F0 b;
    s32 i;

    func_ovl0A_04_800432F8(0x400);
    func_ovl0A_04_80045470(0);
    func_ovl0A_04_80046158(0, 0, 0, 0.0f);
    func_ovl0A_04_80046138(1);
    obj = func_ovl0A_04_80045D30(0x328, 0x01000000, 0xD0, NULL);
    func_ovl0A_04_80045A30(obj->unk40, 0x16, 0);
    obj->unk40->unk48->unk4->unk4 = func_ovl0A_04_80045A48(obj->unk40, 0) - 0.001f;
    if (!obj && !obj && !obj) { /* fake: a block boundary */
    }
    obj->unk40->unk10 = 200.0f;
    obj->unk40->unk14 = 0.0f;
    obj->unk40->unk18 = -2000.0f;
    dx = -2.2222223f;
    dy = -0.5555556f;
    dz = 26.666666f;
    for (i = 0; i < 180; i++) {
        obj->unk40->unk10 += dx;
        obj->unk40->unk14 += dy;
        obj->unk40->unk18 += dz;
        dx += 0.012345680f;
        dy += 0.0030864200f;
        dz += -0.14814815f;
        func_ovl0A_04_80045EA0();
    }
    while (obj->unk40->unk48->unk4->unk4 != 0.0f) {
        obj->unk40->unk48->unk4->unk4 -= 1.0f;
        if (obj->unk40->unk48->unk4->unk4 < 0.0f) {
            obj->unk40->unk48->unk4->unk4 = 0.0f;
        }
        func_ovl0A_04_80045EA0();
    }
    if (!obj && !obj && !obj) { /* fake: a block boundary */
    }
    func_ovl0A_04_80045A30(obj->unk40, 0x17, 0);
    func_ovl0A_04_80045D08(obj, 0x04000000);
    func_ovl0A_04_800432F0(obj);
    a.x = 60.0f;
    a.y = 60.0f;
    a.z = 10.0f;
    b.x = a.x * -1.0f;
    b.y = a.y;
    b.z = a.z;
    a.x += obj->unk40->unk10;
    a.y += obj->unk40->unk14;
    a.z += obj->unk40->unk18;
    b.x += obj->unk40->unk10;
    b.y += obj->unk40->unk14;
    b.z += obj->unk40->unk18;
    func_ovl0A_04_80045E58(func_ovl0A_04_80043010, &a, 0, 0, 0x150);
    func_ovl0A_04_80045E58(func_ovl0A_04_80043010, &b, 0, 0, 0x150);
    func_ovl0A_04_80045E78(60);
    for (i = 0; i < 10; i++) {
        func_ovl0A_04_80046158(0xFF, 0, 0, ((f32) i / 10.0f) * 60.0f);
        func_ovl0A_04_80045EA0();
    }
    func_ovl0A_04_80046570();
    func_ovl0A_04_80045E68();
}

static void func_ovl0A_04_800432F8(s32 flag) {
    while (!func_ovl0A_04_800460E0(flag)) {
        func_ovl0A_04_80045EA0();
    }
}

static void func_ovl0A_04_800432F0(Obj04 *obj) {
    if (!obj && !obj && !obj) { /* fake: a block boundary */
    }
    while (!(obj->unk40->unkC & 0x40)) {
        func_ovl0A_04_80045EA0();
    }
}

void func_ovl0A_04_80043124(void) {
    Obj04 *self;
    Obj04 *obj;
    s32 i;
    f32 t;

    self = func_ovl0A_04_80045E80();
    obj = func_ovl0A_04_80045D30(0x2CF, 0x01080000, 0xD0, NULL);
    func_ovl0A_04_80045DE0(self, obj);
    obj->unk40->unk2C = 1.0f;
    obj->unk40->unk28 = 0.25f;
    obj->unk40->unk30 = obj->unk40->unk28;
    obj->unk40->unk1C = func_ovl0A_04_80046010() * 120.0 + 30.0;
    obj->unk40->unk20 = func_ovl0A_04_80046010() * 120.0 - 60.0;
    for (i = 0; i < 30; i++) {
        t = (f32) i / 30.0f;
        obj->unk40->unk2C = (1.0f - t) * 0.9f + 0.1f;
        obj->unk40->unk36 = t * 64.0f;
        func_ovl0A_04_80045EA0();
    }
    func_ovl0A_04_80045D20(obj);
    func_ovl0A_04_80045E68();
}

void func_ovl0A_04_80043010(void) {
    Obj04 *self;
    Obj04 *obj;
    s32 i;
    f32 scale;

    self = func_ovl0A_04_80045E80();
    obj = func_ovl0A_04_80045D30(0x2C7, 0x01080000, 0xD0, NULL);
    func_ovl0A_04_80045DE0(self, obj);
    obj->unk40->unk30 = 0.5f;
    obj->unk40->unk28 = obj->unk40->unk2C = obj->unk40->unk30;
    obj->unk40->unk36 = 0xC8;
    for (i = 0; i < 30; i++) {
        scale = ((f32) i / 30.0f) * 0.5f + 0.5f;
        obj->unk40->unk30 = scale;
        obj->unk40->unk2C = scale;
        obj->unk40->unk28 = scale;
        func_ovl0A_04_80045EA0();
    }
    func_ovl0A_04_80045E78(30);
    func_ovl0A_04_80045D20(obj);
    func_ovl0A_04_80045E68();
}

