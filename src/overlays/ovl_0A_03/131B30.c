#include "common.h"

/*
 * ovl_0A_03's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).  Statics
 * inlined into every caller leave a `jr ra; nop` stub just before their first
 * caller; the unused ones at the end of the object leave one each.
 *
 * The `if (!obj && !obj && !obj) {}` in the animation wait is a fake: it ends
 * a basic block, which the original's scheduling needs (as in ovl_0A_04).  In
 * func_ovl0A_03_800442AC the 700s are double literals: written 700.0f, IDO
 * keeps 1200.0f in a saved register and rebuilds 700 at each call, where the
 * original keeps 700 and 850 and rebuilds 1200.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStruct_ovl0A_03_Anim2;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_ovl0A_03_Anim2 *unk4;
} UnkStruct_ovl0A_03_Anim;

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
    /* 0x48 */ UnkStruct_ovl0A_03_Anim *unk48;
} UnkStruct_ovl0A_03_80047E20_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x1C];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[0x14];
    /* 0x40 */ UnkStruct_ovl0A_03_80047E20_Inner *unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 unk48[4];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58[3];
    /* 0x64 */ u8 unk64[4];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} UnkStruct_ovl0A_03_80047E20;

typedef UnkStruct_ovl0A_03_80047E20 Obj03;

typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[8];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 unk38[4];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
} UnkStruct_ovl0A_03_80047FD0;

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0A_03_B04_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl0A_03_B04_Inner *unk40;
} UnkStruct_ovl0A_03_B04;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl0A_03;

void func_ovl0A_03_800470B0(const char *); /* 0x100 */
void func_ovl0A_03_800473F8(s32); /* 0xC00 */
void func_ovl0A_03_80047410(s32); /* 0xD00 */
s32 func_ovl0A_03_800474F8(void); /* 0xF01 */
s32 * func_ovl0A_03_80047548(void); /* 0xF0B */
void func_ovl0A_03_80047560(s32); /* 0xF0E */
void func_ovl0A_03_80047568(s32); /* 0xF0F */
void func_ovl0A_03_800475A8(void); /* 0x1000 */
void func_ovl0A_03_800475B0(s32, s32, s32); /* 0x1001 */
s32 func_ovl0A_03_800475D8(void); /* 0x1006 */
void func_ovl0A_03_800475E8(s32); /* 0x1008 */
void func_ovl0A_03_800475F8(s32, s32, f32, s32, s32, s32, s32); /* 0x100A */
void func_ovl0A_03_80047610(s32); /* 0x100D */
void func_ovl0A_03_80047620(s32); /* 0x100F */
void func_ovl0A_03_80047630(s32, s32, s32, s32); /* 0x1011 */
Obj03 * func_ovl0A_03_80047638(s32); /* 0x1012 */
void func_ovl0A_03_80047668(s32); /* 0x1018 */
void func_ovl0A_03_80047680(s32, s32); /* 0x101B */
void func_ovl0A_03_80047688(s32, s32); /* 0x101C */
void func_ovl0A_03_80047B00(UnkStruct_ovl0A_03_80047E20_Inner *, s32); /* 0x1505 */
void func_ovl0A_03_80047B08(UnkStruct_ovl0A_03_80047E20_Inner *, s32, s32, s32); /* 0x1506 */
void func_ovl0A_03_80047B20(UnkStruct_ovl0A_03_80047E20_Inner *, s32, s32); /* 0x1509 */
f32 func_ovl0A_03_80047B38(UnkStruct_ovl0A_03_80047E20_Inner *, s32); /* 0x150C */
void func_ovl0A_03_80047B50(UnkStruct_ovl0A_03_80047E20_Inner *, s32, s32); /* 0x150F */
s32 func_ovl0A_03_80047B68(UnkStruct_ovl0A_03_80047E20_Inner *, s32); /* 0x1512 */
void func_ovl0A_03_80047B70(s32, s32, s32); /* 0x1513 */
void func_ovl0A_03_80047B88(s32, s32, s32); /* 0x1516 */
void func_ovl0A_03_80047C28(s32); /* 0x1702 */
void func_ovl0A_03_80047C38(f32, f32, f32); /* 0x1704 */
void func_ovl0A_03_80047C48(f32, f32, f32); /* 0x1706 */
void func_ovl0A_03_80047C58(f32, f32, f32); /* 0x1708 */
void func_ovl0A_03_80047C60(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0A_03_80047CA0(s32); /* 0x1711 */
void func_ovl0A_03_80047D10(s32); /* 0x171F */
void func_ovl0A_03_80047D20(f32, f32, f32); /* 0x1721 */
void func_ovl0A_03_80047D28(f32 *); /* 0x1722 */
void func_ovl0A_03_80047D30(f32 *); /* 0x1723 */
void func_ovl0A_03_80047D40(f32 *); /* 0x1725 */
void func_ovl0A_03_80047D88(f32 *, f32 *, f32 *); /* 0x1803 */
void func_ovl0A_03_80047D90(f32 *, f32 *); /* 0x1804 */
void func_ovl0A_03_80047DD0(Obj03 *); /* 0x180C */
void func_ovl0A_03_80047DD8(Obj03 *, Obj03 *); /* 0x180D */
void func_ovl0A_03_80047DF0(s32); /* 0x1810 */
void func_ovl0A_03_80047DF8(Obj03 *, s32); /* 0x1811 */
void func_ovl0A_03_80047E00(Obj03 *, s32); /* 0x1812 */
void func_ovl0A_03_80047E10(Obj03 *); /* 0x1814 */
Obj03 * func_ovl0A_03_80047E20(s32, s32, s32, Obj03 *); /* 0x1816 */
void func_ovl0A_03_80047E30(Obj03 *); /* 0x1818 */
void func_ovl0A_03_80047EC8(Obj03 *, f32 *); /* 0x182B */
void func_ovl0A_03_80047ED0(Obj03 *, Obj03 *); /* 0x182C */
s32 func_ovl0A_03_80047F48(void (*)(), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0A_03_80047F58(void); /* 0x1902 */
void func_ovl0A_03_80047F68(s32); /* 0x1904 */
Obj03 * func_ovl0A_03_80047F70(void); /* 0x1905 */
s32 func_ovl0A_03_80047F90(void); /* 0x1909 */
void func_ovl0A_03_80047FA8(u16); /* 0x190C */
UnkStruct_ovl0A_03_80047FD0 * func_ovl0A_03_80047FD0(s32); /* 0x1A00 */
void func_ovl0A_03_80047FE0(UnkStruct_ovl0A_03_80047FD0 *, s32); /* 0x1A02 */
void func_ovl0A_03_80047FE8(UnkStruct_ovl0A_03_80047FD0 *, s32); /* 0x1A03 */
f32 func_ovl0A_03_800480F0(f32); /* 0x1D00 */
f64 func_ovl0A_03_80048100(void); /* 0x1D02 */
s32 func_ovl0A_03_80048108(s32); /* 0x1D03 */
void func_ovl0A_03_800481C0(s32); /* 0x1E06 */
void func_ovl0A_03_800481C8(s32); /* 0x1E07 */
s32 func_ovl0A_03_800481D0(s32); /* 0x1E08 */
void func_ovl0A_03_80048228(s32); /* 0x2000 */
void func_ovl0A_03_80048238(s32); /* 0x2002 */
void func_ovl0A_03_80048240(void); /* 0x2003 */
void func_ovl0A_03_80048248(s32, s32, s32, f32); /* 0x2004 */
void func_ovl0A_03_80048290(s32); /* 0x2200 */
void func_ovl0A_03_80048298(s32, s32, s32); /* 0x2201 */
void func_ovl0A_03_800483A0(s32, f32 *, s32); /* 0x2601 */
s32 func_ovl0A_03_800484D0(s32); /* 0x2B00 */
void func_ovl0A_03_800484E0(s32); /* 0x2B02 */
void func_ovl0A_03_800484F0(s32, s32, s32, s32); /* 0x2B04 */
void func_ovl0A_03_80048500(s32); /* 0x2B06 */
void func_ovl0A_03_80048648(void); /* 0x3000 */
void func_ovl0A_03_80048650(void); /* 0x3001 */
void func_ovl0A_03_80048658(s32); /* 0x3002 */

/* .bss */
u8 D_ovl0A_03_80048800[0x24];
s32 D_ovl0A_03_80048824;
s32 D_ovl0A_03_80048828;
u8 D_ovl0A_03_8004882C[4];
Vec3f_ovl0A_03 D_ovl0A_03_80048830;
UnkStruct_ovl0A_03_80047FD0 *D_ovl0A_03_8004883C;
s32 D_ovl0A_03_80048840;
s32 D_ovl0A_03_80048844;
Obj03 *D_ovl0A_03_80048848[6];
Obj03 *D_ovl0A_03_80048860;
s32 D_ovl0A_03_80048864;
Obj03 *D_ovl0A_03_80048868;
s32 D_ovl0A_03_8004886C;
Obj03 *D_ovl0A_03_80048870;
s32 D_ovl0A_03_80048874;
s32 D_ovl0A_03_80048878;
Obj03 *D_ovl0A_03_8004887C;
Obj03 *D_ovl0A_03_80048880;

/* .data */
s32 D_ovl0A_03_800486F0 = 1;

void func_ovl0A_03_8004305C(void);
void func_ovl0A_03_8004374C(void);
void func_ovl0A_03_80043BBC(void);
void func_ovl0A_03_80043CA0(void);
void func_ovl0A_03_8004416C(void);
void func_ovl0A_03_800442AC(void);
void func_ovl0A_03_80044BD4(void);
void func_ovl0A_03_80045020(void);
void func_ovl0A_03_800455B8(void);
void func_ovl0A_03_800455E8(void);
void func_ovl0A_03_80045940(void);
void func_ovl0A_03_80045E98(void);
void func_ovl0A_03_80046B20(void);
void func_ovl0A_03_80046D9C(void);
void func_ovl0A_03_80047060(void);

static void func_ovl0A_03_80043010(Obj03 *obj);
static void func_ovl0A_03_80043018(Obj03 *obj);
void func_ovl0A_03_80043D8C(Obj03 *arg0);
void func_ovl0A_03_80043EF0(Obj03 *arg0);
void func_ovl0A_03_80043FA4(Obj03 *arg0);
Obj03 *func_ovl0A_03_80044218(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl0A_03_80044B94(void);
Obj03 *func_ovl0A_03_80044D60(Obj03 *parent);
void func_ovl0A_03_80044E80(Obj03 *obj, s32 *count);
void func_ovl0A_03_8004543C(Obj03 *obj, s32 *count);
void func_ovl0A_03_80045EE0(void);
void func_ovl0A_03_80045F48(void);
static void func_ovl0A_03_80045F78(void);
void func_ovl0A_03_80045F80(void);
void func_ovl0A_03_80045FA0(void);
void func_ovl0A_03_80046004(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_03_80046080(void);
Obj03 *func_ovl0A_03_800460E8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_ovl0A_03_800461C0(void);
void func_ovl0A_03_8004633C(void);
void func_ovl0A_03_80046458(void);
void func_ovl0A_03_800464B4(Obj03 **arg0, s32 *arg1, Obj03 **arg2, s32 *arg3, Obj03 **arg4, s32 *arg5, s32 arg6);
void func_ovl0A_03_8004685C(void);
void func_ovl0A_03_800468D0(void);
void func_ovl0A_03_800469C0(void);
void func_ovl0A_03_80046A24(s32 arg0);
void func_ovl0A_03_80046F70(s32 arg0, UnkStruct_ovl0A_03_B04 *arg1);
void func_ovl0A_03_80046FA4(f32 arg0);
void func_ovl0A_03_80046FEC(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_03_80047048(void);
static void func_ovl0A_03_80047068(void);
static void func_ovl0A_03_80047070(void);
static void func_ovl0A_03_80047078(void);
static void func_ovl0A_03_80047080(void);
static void func_ovl0A_03_80047088(void);
static void func_ovl0A_03_80047090(void);
static void func_ovl0A_03_80047098(void);
static void func_ovl0A_03_800470A0(void);
static void func_ovl0A_03_800470A8(void);

static void func_ovl0A_03_800470A8(void) {
}

static void func_ovl0A_03_800470A0(void) {
}

static void func_ovl0A_03_80047098(void) {
}

static void func_ovl0A_03_80047090(void) {
}

static void func_ovl0A_03_80047088(void) {
}

static void func_ovl0A_03_80047080(void) {
}

static void func_ovl0A_03_80047078(void) {
}

static void func_ovl0A_03_80047070(void) {
}

/* Unused: IDO -O3 drops their bodies and leaves a `jr ra` each.  What
 * they did is unknown; they have to reference the .bss the code doesn't
 * (or it becomes common) and take a function's address (or the task
 * functions defined before their spawner move). */
static void func_ovl0A_03_80047068(void) {
    D_ovl0A_03_80048800[0] = 0;
    D_ovl0A_03_8004882C[0] = 0;
    func_ovl0A_03_80047F48(func_ovl0A_03_80047060, NULL, 0, 0, 0);
}

void func_ovl0A_03_80047060(void) {
}

void func_ovl0A_03_80047048(void) {
    D_ovl0A_03_80048824 = -1;
    D_ovl0A_03_80048828 = -1;
}

void func_ovl0A_03_80046FEC(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0A_03_80047C38(D_ovl0A_03_80048830.x, D_ovl0A_03_80048830.y, D_ovl0A_03_80048830.z);
    func_ovl0A_03_80047C58(arg0, arg1, arg2);
    func_ovl0A_03_80047F68(0xB4);
}

void func_ovl0A_03_80046FA4(f32 arg0) {
    f32 sp1C;

    func_ovl0A_03_80047C60(&sp1C, NULL, NULL);
    func_ovl0A_03_80047C58(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0A_03_80046F70(s32 arg0, UnkStruct_ovl0A_03_B04 *arg1) {
    UnkStruct_ovl0A_03_B04_Inner *p;

    p = arg1->unk40;
    func_ovl0A_03_800484F0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0A_03_80046D9C(void) {
    Obj03 *self;
    Obj03 *obj;
    f32 d;
    f32 s;

    self = func_ovl0A_03_80047F70();
    obj = func_ovl0A_03_80047E20(0x34D, 0x01080000, 0xD0, NULL);
    obj->unk40->unk36 = 0x7F;
    obj->unk40->unk10 = 1000.0f;
    obj->unk40->unk14 = -100.0f;
    obj->unk40->unk18 = -650.0f;
    obj->unk40->unk20 = self->unk40->unk20;
    func_ovl0A_03_80047F68(4);
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
            func_ovl0A_03_80047DF8(obj, 0x01000000);
        } else {
            func_ovl0A_03_80047E00(obj, 0x01000000);
        }
        func_ovl0A_03_80047F90();
    }
}

void func_ovl0A_03_80046B20(void) {
    Obj03 *self;
    Obj03 *obj;
    Obj03 *parts[4];
    s32 i;
    f32 d;
    f32 s;

    self = func_ovl0A_03_80047F70();
    obj = func_ovl0A_03_80047E20(-1, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = 1000.0f;
    obj->unk40->unk14 = -100.0f;
    obj->unk40->unk18 = -650.0f;
    obj->unk40->unk20 = self->unk40->unk20;
    for (i = 0; i < 4; i++) {
        parts[i] = func_ovl0A_03_80047E20(0x34D, 0x01780000, 0xD0, obj);
        parts[i]->unk40->unk36 = 0x7F;
    }
    parts[0]->unk4C = 300.0f;
    parts[1]->unk54 = 300.0f;
    parts[2]->unk4C = -300.0f;
    parts[3]->unk54 = -300.0f;
    func_ovl0A_03_80047F68(4);
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
        func_ovl0A_03_80047F90();
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0A_03_80046A24(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0A_03_800469C0();
            break;
        case 16:
            func_ovl0A_03_800468D0();
            break;
        case 17:
            func_ovl0A_03_8004685C();
            break;
        case 4:
            func_ovl0A_03_80046458();
            break;
        case 5:
            func_ovl0A_03_80045FA0();
            break;
        case 3:
            func_ovl0A_03_80045F80();
            break;
        case 1:
            func_ovl0A_03_80045F48();
            break;
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
    }
}

void func_ovl0A_03_800469C0(void) {
    if (*func_ovl0A_03_80047548() & 2) {
        func_ovl0A_03_800481C0(0x402);
    } else {
        func_ovl0A_03_800481C8(0x402);
    }
    func_ovl0A_03_800473F8(0x33A);
    func_ovl0A_03_80047410(0x339);
    func_ovl0A_03_800481C8(0x403);
}

void func_ovl0A_03_800468D0(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_ovl0A_03_80047680(i, 1);
    }
    func_ovl0A_03_80047630(0, 0xA, 0, 3);
    func_ovl0A_03_80047630(1, 8, 0, 7);
    func_ovl0A_03_80047630(2, 0xC, 0, 8);
    func_ovl0A_03_80047630(3, 0xB, 0, 7);
    func_ovl0A_03_800475A8();
    func_ovl0A_03_800481C8(0x404);
    func_ovl0A_03_800481C8(0x405);
    func_ovl0A_03_800464B4(&D_ovl0A_03_80048860, &D_ovl0A_03_80048864, &D_ovl0A_03_80048868,
                           &D_ovl0A_03_8004886C, &D_ovl0A_03_80048870, &D_ovl0A_03_80048874, 2);
}

void func_ovl0A_03_8004685C(void) {
    func_ovl0A_03_800475A8();
    func_ovl0A_03_800475B0(0xA, 0, 3);
    func_ovl0A_03_800464B4(&D_ovl0A_03_80048860, &D_ovl0A_03_80048864, &D_ovl0A_03_80048868,
                           &D_ovl0A_03_8004886C, &D_ovl0A_03_80048870, &D_ovl0A_03_80048874, 1);
}

void func_ovl0A_03_800464B4(Obj03 **arg0, s32 *arg1, Obj03 **arg2, s32 *arg3, Obj03 **arg4, s32 *arg5, s32 arg6) {
    s32 i;

    *arg0 = func_ovl0A_03_80047E20(0x27, 0x01000000, 0xD0, NULL);
    (*arg0)->unk40->unk10 = 1000.0f;
    (*arg0)->unk40->unk14 = 50.0f;
    (*arg0)->unk40->unk18 = -650.0f;
    (*arg0)->unk40->unk30 = 0.5f;
    (*arg0)->unk40->unk28 = (*arg0)->unk40->unk2C = (*arg0)->unk40->unk30;
    (*arg0)->unk40->unk20 = 345.0f;
    *arg1 = func_ovl0A_03_80047B68((*arg0)->unk40, 0x19);
    for (i = 0; i < 0x19; i++) {
        if (i == 0x10 || i == 0x11 || i == 0x12 || i == 0x13) {
            func_ovl0A_03_80047B70(*arg1, i, 0x4F);
        }
    }
    if (arg6 != 0) {
        func_ovl0A_03_80047B70(*arg1, 0xF, 0x4F);
        func_ovl0A_03_80047B70(*arg1, 0xD, 0x4F);
        func_ovl0A_03_80047B70(*arg1, 0xC, 0x4F);
        func_ovl0A_03_80047B70(*arg1, 0xB, 0x4F);
        func_ovl0A_03_80047B70(*arg1, 0xE, 0x4F);
        func_ovl0A_03_80047B70(*arg1, 5, 0x4F);
        func_ovl0A_03_80047B70(*arg1, 2, 0x4F);
        func_ovl0A_03_80047B70(*arg1, 4, 0x4F);
        func_ovl0A_03_80047B70(*arg1, 3, 0x4F);
        *arg2 = func_ovl0A_03_80047E20(0x27, 0x01400000, 0xD0, *arg0);
        *arg3 = func_ovl0A_03_80047B68((*arg2)->unk40, 0x19);
        for (i = 0; i < 0x19; i++) {
            switch (i) {
                case 0xB:
                case 0xC:
                case 0xD:
                case 0xE:
                case 0xF:
                    break;
                default:
                    func_ovl0A_03_80047B70(*arg3, i, 0x4F);
                    break;
            }
        }
        if (arg6 >= 2) {
            *arg4 = func_ovl0A_03_80047E20(0x27, 0x01400000, 0xD0, *arg0);
            *arg5 = func_ovl0A_03_80047B68((*arg4)->unk40, 0x19);
            for (i = 0; i < 0x19; i++) {
                switch (i) {
                    case 0x10:
                    case 0x11:
                    case 0x12:
                    case 0x13:
                        break;
                    default:
                        func_ovl0A_03_80047B70(*arg5, i, 0x4F);
                        break;
                }
            }
        }
    }
    if (arg6 != 0) {
        D_ovl0A_03_80048840 = func_ovl0A_03_80047F48(func_ovl0A_03_80046D9C, *arg2, 0, 0, 0x150);
    } else {
        D_ovl0A_03_80048840 = func_ovl0A_03_80047F48(func_ovl0A_03_80046D9C, *arg0, 0, 0, 0x150);
    }
    D_ovl0A_03_80048844 = func_ovl0A_03_80047F48(func_ovl0A_03_80046B20, *arg0, 0, 0, 0x150);
}

void func_ovl0A_03_80046458(void) {
    func_ovl0A_03_8004633C();
    func_ovl0A_03_80047DF0(0);
    func_ovl0A_03_800481C8(0x400);
    func_ovl0A_03_800481C8(0x401);
    func_ovl0A_03_800481C8(0x406);
    func_ovl0A_03_800481C8(0x407);
    func_ovl0A_03_80048248(0, 0, 0, 100.0f);
}

void func_ovl0A_03_8004633C(void) {
    D_ovl0A_03_8004883C = func_ovl0A_03_80047FD0(0x33B);
    func_ovl0A_03_80047FE0(D_ovl0A_03_8004883C, 0x20000001);
    D_ovl0A_03_8004883C->unk40 = 1.0f;
    D_ovl0A_03_8004883C->unk44 = 1.0f;
    D_ovl0A_03_8004883C->unk28 = 0.0f;
    D_ovl0A_03_8004883C->unk2C = 120.0f;
    D_ovl0A_03_8004883C->unk30 = D_ovl0A_03_8004883C->unk28 + D_ovl0A_03_8004883C->unk48 * 2.0f;
    D_ovl0A_03_8004883C->unk34 = D_ovl0A_03_8004883C->unk2C + D_ovl0A_03_8004883C->unk4C * 2.0f * 0.8f;
    func_ovl0A_03_80048290(1);
    func_ovl0A_03_80048298(0, 0, 0xFF);
    func_ovl0A_03_80047CA0(0x7F);
    func_ovl0A_03_80047C38(1000.0f, 400.0f, 200.0f);
    func_ovl0A_03_80047C28(1);
    func_ovl0A_03_80047C58(0.0f, 20.0f, 1700.0f);
    func_ovl0A_03_800461C0();
    func_ovl0A_03_80046080();
}

void func_ovl0A_03_800461C0(void) {
    s32 i;

    i = 0;
    D_ovl0A_03_80048848[i++] = func_ovl0A_03_800460E8(1000.0f, 50.0f, -1150.0f, 13.0f, 2.0f);
    D_ovl0A_03_80048848[i++] = func_ovl0A_03_800460E8(1500.0f, 150.0f, -550.0f, 13.0f, 2.0f);
    D_ovl0A_03_80048848[i++] = func_ovl0A_03_800460E8(1000.0f, 1050.0f, -650.0f, 13.0f, 5.0f);
    D_ovl0A_03_80048848[i++] = func_ovl0A_03_800460E8(500.0f, 1050.0f, -450.0f, 13.0f, 5.0f);
    D_ovl0A_03_80048848[i++] = func_ovl0A_03_800460E8(500.0f, 1050.0f, -250.0f, 13.0f, 4.0f);
    D_ovl0A_03_80048848[i++] = func_ovl0A_03_800460E8(1500.0f, 1050.0f, -1050.0f, 13.0f, 5.0f);
}

Obj03 *func_ovl0A_03_800460E8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    Obj03 *obj;

    obj = func_ovl0A_03_80047E20(0x11D, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = arg0;
    obj->unk40->unk14 = arg1;
    obj->unk40->unk18 = arg2;
    obj->unk40->unkC |= 0x8000;
    func_ovl0A_03_80047B00(obj->unk40, 1);
    func_ovl0A_03_80047B08(obj->unk40, 0x11E, 0, 1);
    obj->unk40->unk28 = arg3;
    obj->unk40->unk2C = arg4;
    obj->unk40->unk36 = 0xCC;
    return obj;
}

void func_ovl0A_03_80046080(void) {
    func_ovl0A_03_80046004(500.0f, 0.0f, 400.0f);
    func_ovl0A_03_80046004(1600.0f, 0.0f, 300.0f);
    func_ovl0A_03_80046004(500.0f, 0.0f, 700.0f);
    func_ovl0A_03_80046004(1700.0f, 0.0f, 600.0f);
}

void func_ovl0A_03_80046004(f32 arg0, f32 arg1, f32 arg2) {
    Obj03 *obj;

    obj = func_ovl0A_03_80047E20(0x97, 0x01000000, 0xD0, NULL);
    obj->unk40->unk10 = arg0;
    obj->unk40->unk14 = arg1;
    obj->unk40->unk18 = arg2;
    func_ovl0A_03_80047E20(0x98, 0x01480000, 0xD0, obj)->unk40->unk36 = 0x80;
}

void func_ovl0A_03_80045FA0(void) {
    if (func_ovl0A_03_800474F8() == 0x10) {
        func_ovl0A_03_80045EE0();
    } else {
        func_ovl0A_03_80044B94();
    }
}

void func_ovl0A_03_80045F80(void) {
    func_ovl0A_03_80045F78();
    func_ovl0A_03_800481C0(0x403);
}

static void func_ovl0A_03_80045F78(void) {
}

void func_ovl0A_03_80045F48(void) {
    if (func_ovl0A_03_800481D0(0x402)) {
        func_ovl0A_03_80048650();
    }
}

void func_ovl0A_03_80045EE0(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_ovl0A_03_80047668(i);
        func_ovl0A_03_800475E8(1);
    }
    func_ovl0A_03_80047F48(func_ovl0A_03_80045940, NULL, 0, 0, 0x130);
}

void func_ovl0A_03_80045E98(void) {
    func_ovl0A_03_80047F68((s32) func_ovl0A_03_80047F70());
    func_ovl0A_03_80048500(D_ovl0A_03_80048878);
    func_ovl0A_03_800484E0(0x16);
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_80045940(void) {
    s32 i;
    s32 j;
    f32 cam[3];
    Obj03 *obj;

    func_ovl0A_03_800475E8(1);
    while (!func_ovl0A_03_800481D0(0x403)) {
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047568(1);
    func_ovl0A_03_80047560(0);
    func_ovl0A_03_800475E8(1);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33C, 1200.0f, 0.0f, 500.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33C, 700.0f, 0.0f, 550.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33C, 1000.0f, 0.0f, 800.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33D, 700.0f, 0.0f, 700.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33D, 900.0f, 0.0f, 500.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33D, 1300.0f, 0.0f, 700.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33E, 700.0f, 200.0f, 500.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33E, 1200.0f, 300.0f, 400.0f), 0, 0, 0x150);
    for (i = 1; i < 4; i++) {
        func_ovl0A_03_80047668(i);
        func_ovl0A_03_800475F8(0, 3, 2.0f, 0, 1, 0, 0);
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047FA8(D_ovl0A_03_80048840);
    func_ovl0A_03_80047FA8(D_ovl0A_03_80048844);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004374C, NULL, 0, 0, 0x150);
    func_ovl0A_03_80048248(0, 0, 0, 0.0f);
    func_ovl0A_03_80048228(1);
    func_ovl0A_03_80048240();
    func_ovl0A_03_80047F48(func_ovl0A_03_800455E8, NULL, 0, 0, 0x150);
    while (!func_ovl0A_03_800481D0(0x401)) {
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_800481C0(0x404);
    while (!func_ovl0A_03_800481D0(0x405)) {
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047D30(cam);
    func_ovl0A_03_80047F48(func_ovl0A_03_80045E98, (void *) 90, 0, 0, 0x150);
    for (i = 0; i < 180; i++) {
        cam[2] += 2.5f;
        D_ovl0A_03_80048860->unk40->unk18 += 2.0f;
        for (j = 0; j < 6; j++) {
            D_ovl0A_03_80048848[j]->unk40->unk18 += 2.0f;
        }
        func_ovl0A_03_80047D28(cam);
        func_ovl0A_03_80047F90();
    }
    for (i = 0; i < 4; i++) {
        func_ovl0A_03_80047668(i);
        func_ovl0A_03_800475F8(0x80, 3, 2.0f, 0, 1, 0, 0);
        func_ovl0A_03_80047F68(30);
        obj = func_ovl0A_03_80047638(i);
        func_ovl0A_03_80047B50(obj->unk40, 4, 0xE);
        func_ovl0A_03_80047B50(obj->unk40, 5, 0xF);
        if (i == 0) {
            func_ovl0A_03_800484D0(0x1AD);
        }
        func_ovl0A_03_80047620(0x04000000);
        func_ovl0A_03_80047F68(30);
        if (i == 0) {
            func_ovl0A_03_800481C0(0x400);
        }
    }
    for (i = 0; i < 240; i++) {
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80048658(1);
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_800455E8(void) {
    Obj03 *obj;
    Obj03 *spark;
    s32 done;
    s32 count;
    s32 i;

    obj = func_ovl0A_03_80047E20(-1, 0x600000, 0xD0, D_ovl0A_03_80048870);
    obj->unk50 = 1400.0f;
    obj->unk54 = 200.0f;
    func_ovl0A_03_80047DD0(D_ovl0A_03_80048870);
    D_ovl0A_03_80048870->unk40->unk14 = -500.0f;
    func_ovl0A_03_80047F48(func_ovl0A_03_800455B8, NULL, 0, 0, 0x150);
    count = 12;
    done = 0;
    for (i = 0; i < 180; i++) {
        D_ovl0A_03_80048870->unk40->unk14 += -1.6666666f;
        func_ovl0A_03_8004543C(obj, &count);
        if (done == 0 && i == 170) {
            spark = func_ovl0A_03_80047E20(0x2D3, 0x01000000, 0xD0, NULL);
            done = 1;
            spark->unk40->unk30 = 1.0f;
            spark->unk40->unk28 = spark->unk40->unk2C = spark->unk40->unk30;
            spark->unk40->unk10 = obj->unk40->unk10 + 50.0f;
            spark->unk40->unk14 = obj->unk40->unk14 + 10.0f;
            spark->unk40->unk18 = obj->unk40->unk18;
            func_ovl0A_03_80047F48(func_ovl0A_03_80043CA0, spark, 0, 0, 0x150);
        }
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047F48(func_ovl0A_03_80045020, NULL, 0, 0, 0x150);
    func_ovl0A_03_800484D0(0x2BE);
    func_ovl0A_03_80047D20(10.0f, 10.0f, 10.0f);
    func_ovl0A_03_80047D10(30);
    func_ovl0A_03_80047F68(30);
    func_ovl0A_03_800484D0(0x2BC);
    func_ovl0A_03_80047D20(2.0f, 2.0f, 2.0f);
    func_ovl0A_03_80047D10(-1);
    func_ovl0A_03_80047DF8(D_ovl0A_03_80048870, 0x80000);
    for (i = 0; i < 120; i++) {
        D_ovl0A_03_80048870->unk40->unk36 = (1.0f - ((f32) i / 120.0f)) * 255.0f;
        D_ovl0A_03_80048870->unk40->unk14 += -0.41666666f;
        func_ovl0A_03_8004543C(obj, &count);
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047E00(D_ovl0A_03_80048870, 0x01000000);
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_800455B8(void) {
    func_ovl0A_03_80047F68(60);
    func_ovl0A_03_800484D0(0x2C3);
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_8004543C(Obj03 *obj, s32 *count) {
    static Vec3f_ovl0A_03 D_ovl0A_03_80048888;

    if (++*count >= 13) {
        D_ovl0A_03_80048888.x = func_ovl0A_03_80048100() * 50.0;
        D_ovl0A_03_80048888.y = func_ovl0A_03_80048100() * 50.0;
        D_ovl0A_03_80048888.z = func_ovl0A_03_80048100() * 50.0;
        if (func_ovl0A_03_80048108(1) == 0) {
            D_ovl0A_03_80048888.x *= -1.0f;
        }
        if (func_ovl0A_03_80048108(1) == 0) {
            D_ovl0A_03_80048888.y *= -1.0f;
        }
        if (func_ovl0A_03_80048108(1) == 0) {
            D_ovl0A_03_80048888.z *= -1.0f;
        }
        D_ovl0A_03_80048888.x += obj->unk40->unk10;
        D_ovl0A_03_80048888.y += obj->unk40->unk14;
        D_ovl0A_03_80048888.z += obj->unk40->unk18;
        func_ovl0A_03_800483A0(13, &D_ovl0A_03_80048888.x, 0);
        *count = 0;
    }
}

void func_ovl0A_03_80045020(void) {
    Obj03 *obj;
    Obj03 *pieces[16];
    s32 count;
    s32 i;
    s32 j;
    s32 wait;
    s32 k;
    f32 f;

    obj = func_ovl0A_03_80047E20(-1, 0x600000, 0xD0, D_ovl0A_03_80048868);
    obj->unk50 = 350.0f;
    obj->unk54 = 100.0f;
    func_ovl0A_03_80047DD0(D_ovl0A_03_80048868);
    count = 12;
    for (i = 0; i < 240; i++) {
        func_ovl0A_03_80044E80(obj, &count);
        if (func_ovl0A_03_800481D0(0x402) && i >= 121) {
            func_ovl0A_03_80048648();
            func_ovl0A_03_80047F58();
        }
        func_ovl0A_03_80047F90();
    }
    j = 0;
    wait = 1;
    k = 0;
    while (k < 16) {
        func_ovl0A_03_80044E80(obj, &count);
        if (wait < ++j) {
            switch (k) {
                case 0:
                    func_ovl0A_03_800484D0(0x2B5);
                    break;
                case 5:
                    func_ovl0A_03_800484D0(0x2B6);
                    break;
                case 10:
                    func_ovl0A_03_800484D0(0x2B7);
                    break;
            }
            pieces[k] = func_ovl0A_03_80044D60(obj);
            k++;
            j = 0;
            wait = func_ovl0A_03_80048108(30);
        }
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047F48(func_ovl0A_03_80044BD4, obj, 0, 0, 0x150);
    for (i = 0; i < 10; i++) {
        func_ovl0A_03_80044E80(obj, &count);
        func_ovl0A_03_80047F90();
    }
    D_ovl0A_03_800486F0 = 0;
    func_ovl0A_03_800484D0(0x2B8);
    for (i = 0; i < 10; i++) {
        f = (f32) i / 10.0f;
        func_ovl0A_03_80048248(0xFF, 0xFF, 0xFF, 99.999f * f);
        func_ovl0A_03_80044E80(obj, &count);
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047DF8(D_ovl0A_03_80048868, 0x80000);
    for (i = 0; i < 60; i++) {
        f = 1.0f - ((f32) i / 60.0f);
        D_ovl0A_03_80048868->unk40->unk36 = 255.0f * f;
        for (k = 0; k < 16; k++) {
            pieces[k]->unk40->unk36 = (s32) (191.0f * f);
        }
        func_ovl0A_03_80044E80(obj, &count);
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047E00(D_ovl0A_03_80048868, 0x01000000);
    func_ovl0A_03_80047E10(obj);
    func_ovl0A_03_80047D10(0);
    for (i = 0; i < 240; i++) {
        f = 1.0f - ((f32) i / 240.0f);
        func_ovl0A_03_80048248(0xFF, 0xFF, 0xFF, 100.0f * f);
        if (i == 180) {
            D_ovl0A_03_80048878 = func_ovl0A_03_800484D0(0x2CA);
        }
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_800481C0(0x401);
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_80044E80(Obj03 *obj, s32 *count) {
    static Vec3f_ovl0A_03 D_ovl0A_03_80048898;

    if (++*count >= 9) {
        if (D_ovl0A_03_800486F0) {
            func_ovl0A_03_800484D0(func_ovl0A_03_80048108(1) + 0x2BF);
        }
        D_ovl0A_03_80048898.x = func_ovl0A_03_80048100() * 100.0;
        D_ovl0A_03_80048898.y = func_ovl0A_03_80048100() * 100.0;
        D_ovl0A_03_80048898.z = func_ovl0A_03_80048100() * 100.0;
        if (func_ovl0A_03_80048108(1) == 0) {
            D_ovl0A_03_80048898.x *= -1.0f;
        }
        if (func_ovl0A_03_80048108(1) == 0) {
            D_ovl0A_03_80048898.y *= -1.0f;
        }
        if (func_ovl0A_03_80048108(1) == 0) {
            D_ovl0A_03_80048898.z *= -1.0f;
        }
        D_ovl0A_03_80048898.x += obj->unk40->unk10;
        D_ovl0A_03_80048898.y += obj->unk40->unk14;
        D_ovl0A_03_80048898.z += obj->unk40->unk18;
        func_ovl0A_03_800483A0(20, &D_ovl0A_03_80048898.x, 0);
        *count = 0;
    }
}

Obj03 *func_ovl0A_03_80044D60(Obj03 *parent) {
    Obj03 *obj;

    obj = func_ovl0A_03_80047E20(0x1CB, 0x01280000, 0xD0, parent);
    obj->unk40->unk28 = 0.3f;
    obj->unk40->unk2C = 50.0f;
    obj->unk40->unk30 = 0.3f;
    obj->unk40->unk36 = 0xBF;
    obj->unk40->unk1C = func_ovl0A_03_80048100() * 60.0;
    if (func_ovl0A_03_80048108(1) == 0) {
        obj->unk40->unk1C += 120.0f;
    }
    obj->unk40->unk20 = func_ovl0A_03_80048100() * 90.0;
    if (func_ovl0A_03_80048108(1) != 0) {
        obj->unk40->unk20 += 45.0f;
    } else {
        obj->unk40->unk20 += 225.0f;
    }
    return obj;
}

void func_ovl0A_03_80044BD4(void) {
    Obj03 *obj;
    s32 i;
    f32 t;
    f32 s;

    obj = func_ovl0A_03_80047E20(0xA, 0x01280000, 0xD0, func_ovl0A_03_80047F70());
    func_ovl0A_03_800484D0(0x2C2);
    for (i = 0; i < 20; i++) {
        t = (f32) i / 20.0f;
        s = (s32) (func_ovl0A_03_800480F0(t * 90.0f) * 30.0f);
        obj->unk40->unk30 = s;
        obj->unk40->unk28 = s;
        obj->unk40->unk36 = (1.0f - t) * 255.0f;
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047E10(obj);
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_80044B94(void) {
    func_ovl0A_03_800475E8(1);
    func_ovl0A_03_80047F48(func_ovl0A_03_800442AC, NULL, 0, 0, 0x130);
}

void func_ovl0A_03_800442AC(void) {
    s32 i;
    f32 v;
    f32 s;
    f32 a; /* 0.0f when added: the add stays */
    f32 pos[3];
    f32 target[3];
    f32 d[3];
    f32 sph[3];
    Obj03 *obj;

    func_ovl0A_03_800475E8(1);
    while (!func_ovl0A_03_800481D0(0x403)) {
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047568(1);
    func_ovl0A_03_80047560(0);
    func_ovl0A_03_800475E8(1);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33C, 1200.0f, 0.0f, 500.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33C, 900.0f, 0.0f, 750.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33C, 800.0f, 0.0f, 850.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33D, 700.0, 0.0f, 700.0), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33D, 1100.0f, 0.0f, 850.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33D, 1300.0f, 0.0f, 700.0), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33E, 700.0, 200.0f, 500.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004416C, func_ovl0A_03_80044218(0x33E, 1200.0f, 300.0f, 400.0f), 0, 0, 0x150);
    func_ovl0A_03_80047F48(func_ovl0A_03_8004305C, NULL, 0, 0, 0x150);
    func_ovl0A_03_80047FA8(D_ovl0A_03_80048840);
    func_ovl0A_03_80047FA8(D_ovl0A_03_80048844);
    func_ovl0A_03_80048248(0, 0, 0, 0.0f);
    func_ovl0A_03_80048228(1);
    if (!func_ovl0A_03_800481D0(0x402)) {
        func_ovl0A_03_800484E0(0x16);
    }
    func_ovl0A_03_80048240();
    func_ovl0A_03_80047F68(10);
    func_ovl0A_03_80047E00(D_ovl0A_03_80048868, 0xF00000);
    func_ovl0A_03_80047DD0(D_ovl0A_03_80048868);
    obj = func_ovl0A_03_80047E20(0x2D3, 0x01000000, 0xD0, NULL);
    obj->unk40->unk30 = 1.0f;
    obj->unk40->unk28 = obj->unk40->unk2C = obj->unk40->unk30;
    obj->unk40->unk10 = D_ovl0A_03_80048868->unk40->unk10;
    obj->unk40->unk14 = D_ovl0A_03_80048868->unk40->unk14 + 400.0f;
    obj->unk40->unk18 = D_ovl0A_03_80048868->unk40->unk18;
    func_ovl0A_03_80047F48(func_ovl0A_03_80043CA0, obj, 0, 0, 0x150);
    func_ovl0A_03_80047F68(60);
    v = 0.0f;
    func_ovl0A_03_800484D0(0x2B9);
    while (TRUE) {
        if (D_ovl0A_03_80048868->unk40->unk14 >= 500.0f) {
            break;
        }
        D_ovl0A_03_80048868->unk40->unk14 += v;
        v += 0.025f;
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80048238(1);
    func_ovl0A_03_80048240();
    func_ovl0A_03_80047FE8(D_ovl0A_03_8004883C, 0x20000000);
    func_ovl0A_03_80047C38(D_ovl0A_03_80048868->unk40->unk10, 1000.0f, D_ovl0A_03_80048868->unk40->unk18);
    func_ovl0A_03_80047C28(0);
    func_ovl0A_03_80047C48(838.0f, -195.0f, 829.0f);
    D_ovl0A_03_80048860->unk40->unk18 += 314.0f;
    for (i = 0; i < 6; i++) {
        D_ovl0A_03_80048848[i]->unk40->unk18 += 314.0f;
    }
    s = 0.5f;
    a = 0.0f;
    func_ovl0A_03_80048228(1);
    while (1) {
        if (D_ovl0A_03_80048868->unk40->unk14 >= 1000.0f) {
            if (func_ovl0A_03_800481D0(0x402)) {
                func_ovl0A_03_80048648();
                func_ovl0A_03_80047F58();
            }
            D_ovl0A_03_80048868->unk40->unk30 = s;
            D_ovl0A_03_80048868->unk40->unk28 = D_ovl0A_03_80048868->unk40->unk2C = D_ovl0A_03_80048868->unk40->unk30;
            s -= 0.0045f;
        }
        if (D_ovl0A_03_80048868->unk40->unk14 >= 1500.0f) {
            break;
        }
        D_ovl0A_03_80048868->unk40->unk14 += v;
        v += a;
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047EC8(D_ovl0A_03_80048868, pos);
    func_ovl0A_03_80047D40(target);
    func_ovl0A_03_80047D88(target, pos, sph);
    sph[1] = (sph[1] - 90.0f) >= 360.0f ? (sph[1] - 90.0f) - 360.0f
           : (sph[1] - 90.0f) < 0.0f ? (sph[1] - 90.0f) + 360.0f : (sph[1] - 90.0f);
    sph[2] = 3000.0f;
    func_ovl0A_03_80047D90(sph, d);
    pos[0] = target[0] + d[0];
    pos[1] = target[1] + d[1];
    pos[2] = target[2] + d[2];
    func_ovl0A_03_800484D0(0x2BA);
    func_ovl0A_03_800483A0(1, pos, 0);
    func_ovl0A_03_80047E00(D_ovl0A_03_80048868, 0x01000000);
    func_ovl0A_03_80047F68(120);
    func_ovl0A_03_80048238(1);
    func_ovl0A_03_80048240();
    D_ovl0A_03_80048860->unk40->unk18 += 50.0f;
    for (i = 0; i < 6; i++) {
        D_ovl0A_03_80048848[i]->unk40->unk18 += 50.0f;
    }
    func_ovl0A_03_80047C38(1000.0f, 400.0f, 700.0f);
    func_ovl0A_03_80047C28(1);
    func_ovl0A_03_80047C58(0.0f, 20.0f, 1700.0f);
    func_ovl0A_03_80047FE0(D_ovl0A_03_8004883C, 0x20000000);
    func_ovl0A_03_80048228(1);
    func_ovl0A_03_80048240();
    D_ovl0A_03_80048878 = func_ovl0A_03_800484D0(0x2CA);
    func_ovl0A_03_800481C0(0x406);
    while (!func_ovl0A_03_800481D0(0x407)) {
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047F68(180);
    func_ovl0A_03_800475F8(0x80, 3, 2.0f, 0, 0, 0, 0);
    func_ovl0A_03_80047F68(40);
    func_ovl0A_03_800481C0(0x400);
    func_ovl0A_03_800484D0(0x1AC);
    func_ovl0A_03_80047688(func_ovl0A_03_800475D8(), 0xB);
    func_ovl0A_03_80047F68(240);
    func_ovl0A_03_80048500(D_ovl0A_03_80048878);
    func_ovl0A_03_80048658(0);
    func_ovl0A_03_80047F58();
}

Obj03 *func_ovl0A_03_80044218(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    Obj03 *obj;

    obj = func_ovl0A_03_80047E20(arg0, 0x01000000, 0xD0, NULL);
    obj->unk40->unk10 = arg1;
    obj->unk40->unk14 = arg2;
    obj->unk40->unk18 = arg3;
    obj->unk40->unk20 = 180.0f;
    func_ovl0A_03_80047E30(obj);
    if (arg0 == 0x33E) {
        func_ovl0A_03_80047DF8(obj, 0x0C000000);
    }
    return obj;
}

void func_ovl0A_03_8004416C(void) {
    Obj03 *self;

    self = func_ovl0A_03_80047F70();
    while (!func_ovl0A_03_800481D0(0x400)) {
        func_ovl0A_03_80047F90();
    }
    switch (self->unk28) {
        case 0x33C:
            func_ovl0A_03_80043FA4(self);
            break;
        case 0x33D:
            func_ovl0A_03_80043EF0(self);
            break;
        case 0x33E:
            func_ovl0A_03_80043D8C(self);
            break;
    }
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_80043FA4(Obj03 *arg0) {
    f32 unit;
    f32 speed;

    unit = 360.0f / func_ovl0A_03_80047B38(arg0->unk40, 0);
    while (1) {
        if (func_ovl0A_03_80048108(1) == 0) {
            speed = unit;
            if (func_ovl0A_03_80048108(1) != 0) {
                speed = unit * -1.0f;
            }
            speed *= func_ovl0A_03_80048108(1) + 1;
        } else {
            speed = 0.0f;
        }
        func_ovl0A_03_80047DF8(arg0, 0x04000000);
        arg0->unk40->unk48->unk4->unk4 = 0.0f;
        while (!(arg0->unk40->unkC & 0x40)) {
            arg0->unk40->unk20 = (arg0->unk40->unk20 + speed) >= 360.0f ? (arg0->unk40->unk20 + speed) - 360.0f
                               : (arg0->unk40->unk20 + speed) < 0.0f ? (arg0->unk40->unk20 + speed) + 360.0f
                               : (arg0->unk40->unk20 + speed);
            func_ovl0A_03_80047F90();
        }
        func_ovl0A_03_80047E00(arg0, 0x04000000);
        func_ovl0A_03_80047F68(func_ovl0A_03_80048108(10) + 1);
    }
}

void func_ovl0A_03_80043EF0(Obj03 *arg0) {
    while (arg0->unk40->unk20 > 0.0f) {
        func_ovl0A_03_80047F90();
        arg0->unk40->unk20 -= 6.0f;
    }
    arg0->unk40->unk20 = 0.0f;
    func_ovl0A_03_80047DF8(arg0, 0x0C000000);
}

void func_ovl0A_03_80043D8C(Obj03 *arg0) {
    f32 base;
    f32 amp;
    f32 step;
    f32 angle;

    base = arg0->unk40->unk14;
    amp = func_ovl0A_03_80048100() * 12.5 + 50.0;
    step = func_ovl0A_03_80048100() * 10.0 + 5.0;
    angle = 0.0f;
    while (1) {
        arg0->unk40->unk14 = func_ovl0A_03_800480F0(angle) * amp + base;
        angle = (angle + step) >= 360.0f ? (angle + step) - 360.0f
              : (angle + step) < 0.0f ? (angle + step) + 360.0f : (angle + step);
        func_ovl0A_03_80047F90();
    }
}

void func_ovl0A_03_80043CA0(void) {
    Obj03 *obj;
    f32 v;
    s32 n;
    s32 i;

    obj = func_ovl0A_03_80047F70();
    v = 5.0f;
    n = 1;
    for (i = 0; i < 180; i++) {
        obj->unk40->unk10 += v;
        v += 0.1f;
        if (++n >= 2) {
            n = 0;
            func_ovl0A_03_80047F48(func_ovl0A_03_80043BBC, obj, 0, 0, 0x150);
        }
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047E10(obj);
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_80043BBC(void) {
    Obj03 *obj;
    Obj03 *src;
    s32 alpha;

    src = func_ovl0A_03_80047F70();
    obj = func_ovl0A_03_80047E20(src->unk28, 0x01080000, 0xD0, NULL);
    alpha = 0xFF;
    obj->unk40->unk28 = obj->unk40->unk2C = obj->unk40->unk30 = src->unk40->unk28;
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    while (1) {
        alpha -= 10;
        obj->unk40->unk36 = alpha;
        if (alpha < 0x41) {
            break;
        }
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047E10(obj);
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_8004374C(void) {
    Obj03 *obj;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;

    D_ovl0A_03_8004887C = func_ovl0A_03_80047E20(0x322, 0x01000000, 0xD0, NULL);
    func_ovl0A_03_80047E30(D_ovl0A_03_8004887C);
    D_ovl0A_03_8004887C->unk40->unk20 = -45.0f;
    func_ovl0A_03_80047B20(D_ovl0A_03_8004887C->unk40, 1, 0);
    func_ovl0A_03_80043018(D_ovl0A_03_8004887C);
    func_ovl0A_03_80047668(0);
    func_ovl0A_03_80047688(0, 0xB);
    D_ovl0A_03_8004887C->unk40->unk10 = 1800.0f;
    D_ovl0A_03_8004887C->unk40->unk14 = 800.0f;
    D_ovl0A_03_8004887C->unk40->unk18 = 150.0f;
    dx = -10.75f;
    dy = -6.6666665f;
    dz = 0.083333336f;
    obj = func_ovl0A_03_80047638(0);
    func_ovl0A_03_80047DF8(obj, 0x400000);
    func_ovl0A_03_80047DD8(D_ovl0A_03_8004887C, obj);
    obj->unk68 = 0.0f;
    obj->unk6C = 0.0f;
    obj->unk70 = 0.0f;
    obj->unk4C = 0.0f;
    obj->unk50 = 100.0f;
    obj->unk54 = 37.5f;
    while (!func_ovl0A_03_800481D0(0x404)) {
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_800484D0(0x2C8);
    for (i = 0; i < 121; i++) {
        D_ovl0A_03_8004887C->unk40->unk10 += dx;
        D_ovl0A_03_8004887C->unk40->unk14 += dy;
        D_ovl0A_03_8004887C->unk40->unk18 += dz;
        dx += 0.08958333f;
        dy += 0.055555556f;
        dz += -0.00069444446f;
        func_ovl0A_03_80047F90();
    }
    D_ovl0A_03_8004887C->unk40->unk10 = 1155.0f;
    D_ovl0A_03_8004887C->unk40->unk14 = 400.0f;
    D_ovl0A_03_8004887C->unk40->unk18 = 155.0f;
    func_ovl0A_03_80047E00(obj, 0x400000);
    func_ovl0A_03_80047DD0(obj);
    obj->unk6C = 0.0f;
    obj->unk68 = 10.0f;
    obj->unk70 = 1.6333334f;
    func_ovl0A_03_80047B20(D_ovl0A_03_8004887C->unk40, 2, 0);
    D_ovl0A_03_8004887C->unk40->unk48->unk4->unk4 = 0.0f;
    func_ovl0A_03_80047DF8(D_ovl0A_03_8004887C, 0x04000000);
    while (obj->unk68 != 0.0f) {
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047F68(30);
    func_ovl0A_03_80047668(0);
    func_ovl0A_03_80047610(0);
    func_ovl0A_03_80047F68(10);
    func_ovl0A_03_800475F8(0xA0, 3, 8.5f, 1, 0, 1, 0);
    func_ovl0A_03_80047F68(40);
    func_ovl0A_03_800475F8(0x20, 3, 2.0f, 0, 0, 0, 0);
    func_ovl0A_03_80047F68(40);
    func_ovl0A_03_80047B88(0x360, 3, 300);
    func_ovl0A_03_80047560(0);
    func_ovl0A_03_800475E8(1);
    func_ovl0A_03_80047B20(D_ovl0A_03_8004887C->unk40, 3, 0);
    func_ovl0A_03_80047DF8(D_ovl0A_03_8004887C, 0x04000000);
    dy = 0.0f;
    D_ovl0A_03_8004887C->unk40->unk48->unk4->unk4 = 0.0f;
    func_ovl0A_03_800484D0(0x2C9);
    for (i = 0; i < 120; i++) {
        D_ovl0A_03_8004887C->unk40->unk14 += dy;
        dy += 0.22222222f;
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_800481C0(0x405);
    func_ovl0A_03_80047E10(D_ovl0A_03_8004887C);
    func_ovl0A_03_80047F58();
}

void func_ovl0A_03_8004305C(void) {
    f32 pos[3];
    f32 target[3];
    f32 d[3];
    f32 sph[3];
    f32 ang[3];
    Obj03 *obj;
    f32 r;
    f32 step;
    f32 t;
    f32 n;
    f32 da;

    D_ovl0A_03_80048880 = func_ovl0A_03_80047E20(0x328, 0x01000004, 0xD0, NULL);
    func_ovl0A_03_80047E30(D_ovl0A_03_80048880);
    func_ovl0A_03_80047B20(D_ovl0A_03_80048880->unk40, 0x16, 0);
    func_ovl0A_03_80043018(D_ovl0A_03_80048880);
    obj = func_ovl0A_03_80047638(func_ovl0A_03_800475D8());
    func_ovl0A_03_80047DF8(obj, 0x400000);
    func_ovl0A_03_80047DD8(D_ovl0A_03_80048880, obj);
    obj->unk68 = 0.0f;
    obj->unk6C = 0.0f;
    obj->unk70 = 0.0f;
    obj->unk50 = 60.0f;
    func_ovl0A_03_80047688(func_ovl0A_03_800475D8(), 0xB);
    D_ovl0A_03_80048880->unk40->unk10 = 1700.0f;
    D_ovl0A_03_80048880->unk40->unk14 = 400.0f;
    D_ovl0A_03_80048880->unk40->unk18 = 350.0f;
    pos[0] = 1700.0f;
    pos[1] = 400.0f;
    pos[2] = 350.0f;
    target[0] = 1000.0f;
    target[1] = 400.0f;
    target[2] = 300.0f;
    func_ovl0A_03_80047D88(pos, target, sph);
    sph[1] = (sph[1] - 90.0f) >= 360.0f ? (sph[1] - 90.0f) - 360.0f
           : (sph[1] - 90.0f) < 0.0f ? (sph[1] - 90.0f) + 360.0f : (sph[1] - 90.0f);
    while (!func_ovl0A_03_800481D0(0x406)) {
        func_ovl0A_03_80047F90();
    }
    n = 30.0f;
    r = sph[2] / (n * 0.5f);
    step = (r / n) * -1.0f;
    func_ovl0A_03_800484D0(0x2C5);
    while (r > 20.0f) {
        sph[2] = r;
        r += step;
        func_ovl0A_03_80047D90(sph, d);
        pos[0] += d[0];
        pos[1] += d[1];
        pos[2] += d[2];
        func_ovl0A_03_80047ED0(pos, D_ovl0A_03_80048880);
        func_ovl0A_03_80047D88(D_ovl0A_03_80048880->unk58, pos, ang);
        D_ovl0A_03_80048880->unk40->unk20 = ang[0];
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047E00(obj, 0x400000);
    func_ovl0A_03_80047DD0(obj);
    obj->unk6C = 0.0f;
    obj->unk68 = 10.0f;
    obj->unk70 = 1.6333334f;
    da = (-30.0f - sph[0]) / 30.0f;
    for (t = 0.0f; t < n; t += 1.0f) {
        sph[2] = r;
        sph[0] += da;
        func_ovl0A_03_80047D90(sph, d);
        pos[0] += d[0];
        pos[1] += d[1];
        pos[2] += d[2];
        func_ovl0A_03_80047ED0(pos, D_ovl0A_03_80048880);
        func_ovl0A_03_80047D88(D_ovl0A_03_80048880->unk58, pos, ang);
        D_ovl0A_03_80048880->unk40->unk20 = ang[0];
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_800484D0(0x2C6);
    while (D_ovl0A_03_80048880->unk40->unk48->unk4->unk4 > 0.0f) {
        func_ovl0A_03_80047F90();
        D_ovl0A_03_80048880->unk40->unk48->unk4->unk4 -= 1.0f;
    }
    D_ovl0A_03_80048880->unk40->unk48->unk4->unk4 = 0.0f;
    while (obj->unk68 != 0.0f) {
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_800475F8(0x20, 3, 2.0f, 0, 0, 0, 0);
    func_ovl0A_03_80047F68(40);
    func_ovl0A_03_80047B88(0x35F, 2, 300);
    func_ovl0A_03_80047560(0);
    func_ovl0A_03_800475E8(1);
    func_ovl0A_03_800481C0(0x407);
    func_ovl0A_03_800484D0(0x2C6);
    func_ovl0A_03_80047DF8(D_ovl0A_03_80048880, 0x04000000);
    func_ovl0A_03_80043010(D_ovl0A_03_80048880);
    r = 0.0f;
    sph[0] = D_ovl0A_03_80048880->unk40->unk20;
    n = 120.0f;
    func_ovl0A_03_800484D0(0x2C7);
    for (t = 0.0f; t < n; t += 1.0f) {
        if (t == 30.0f) {
            func_ovl0A_03_800475F8(0xA0, 3, 2.0f, 0, 0, 0, 0);
        }
        r += 2.0f;
        sph[2] = r;
        func_ovl0A_03_80047D90(sph, d);
        pos[0] += d[0];
        pos[1] += d[1];
        pos[2] += d[2];
        func_ovl0A_03_80047ED0(pos, D_ovl0A_03_80048880);
        func_ovl0A_03_80047D88(D_ovl0A_03_80048880->unk58, pos, ang);
        D_ovl0A_03_80048880->unk40->unk20 = ang[0];
        func_ovl0A_03_80047F90();
    }
    func_ovl0A_03_80047E10(D_ovl0A_03_80048880);
    func_ovl0A_03_80047F58();
}

static void func_ovl0A_03_80043018(Obj03 *obj) {
    obj->unk40->unk48->unk4->unk4 = func_ovl0A_03_80047B38(obj->unk40, 0) - 0.001f;
}

/* Waits for the object's animation to end; IDO passes obj in s0. */
static void func_ovl0A_03_80043010(Obj03 *obj) {
    if (!obj && !obj && !obj) { /* fake: a block boundary */
    }
    while (!(obj->unk40->unkC & 0x40)) {
        func_ovl0A_03_80047F90();
    }
}

