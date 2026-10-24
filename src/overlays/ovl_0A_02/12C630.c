#include "common.h"

/*
 * ovl_0A_02's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).  Statics
 * inlined into every caller leave a `jr ra; nop` stub just before their first
 * caller; the unused ones at the end of the object leave one each.
 *
 * Two fakes end basic blocks where the original's scheduling and register
 * choice need it: in func_ovl0A_02_80043070 after the animation-end static
 * (the address of its table is formed before the store), and in
 * func_ovl0A_02_800447CC after rot is computed (rot, not the loop bound, is
 * the value spilled).
 */

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} UnkStruct_ovl0A_02_Anim2;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_ovl0A_02_Anim2 *unk4;
} UnkStruct_ovl0A_02_Anim;

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
    /* 0x48 */ UnkStruct_ovl0A_02_Anim *unk48;
} UnkStruct_ovl0A_02_80047A20_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x1C];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[0x14];
    /* 0x40 */ UnkStruct_ovl0A_02_80047A20_Inner *unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58[3];
    /* 0x64 */ u8 unk64[4];
    /* 0x68 */ f32 unk68;
} UnkStruct_ovl0A_02_80047A20;

typedef UnkStruct_ovl0A_02_80047A20 Obj02;

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
} UnkStruct_ovl0A_02_80047BD0;

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0A_02_B04_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl0A_02_B04_Inner *unk40;
} UnkStruct_ovl0A_02_B04;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl0A_02;

void func_ovl0A_02_80046CB0(const char *); /* 0x100 */
void func_ovl0A_02_80046FF8(s32); /* 0xC00 */
void func_ovl0A_02_80047010(s32); /* 0xD00 */
void func_ovl0A_02_800470F0(s32, s32, s32); /* 0xF00 */
s32 func_ovl0A_02_800470F8(void); /* 0xF01 */
s32 *func_ovl0A_02_80047148(void); /* 0xF0B */
void func_ovl0A_02_80047160(s32); /* 0xF0E */
void func_ovl0A_02_80047168(s32); /* 0xF0F */
void func_ovl0A_02_80047198(s32); /* 0xF15 */
void func_ovl0A_02_800471A8(void); /* 0x1000 */
void func_ovl0A_02_800471B0(s32, s32, s32); /* 0x1001 */
s32 func_ovl0A_02_800471D8(void); /* 0x1006 */
void func_ovl0A_02_800471E8(s32); /* 0x1008 */
void func_ovl0A_02_800471F8(s32, s32, f32, s32, s32, s32, s32); /* 0x100A */
void func_ovl0A_02_80047220(s32); /* 0x100F */
Obj02 * func_ovl0A_02_80047238(s32); /* 0x1012 */
void func_ovl0A_02_80047288(s32, s32); /* 0x101C */
void func_ovl0A_02_80047700(UnkStruct_ovl0A_02_80047A20_Inner *, s32); /* 0x1505 */
void func_ovl0A_02_80047708(UnkStruct_ovl0A_02_80047A20_Inner *, s32, s32, s32); /* 0x1506 */
void func_ovl0A_02_80047720(UnkStruct_ovl0A_02_80047A20_Inner *, s32, s32); /* 0x1509 */
f32 func_ovl0A_02_80047738(UnkStruct_ovl0A_02_80047A20_Inner *, s32); /* 0x150C */
s32 func_ovl0A_02_80047768(UnkStruct_ovl0A_02_80047A20_Inner *, s32); /* 0x1512 */
void func_ovl0A_02_80047770(s32, s32, s32); /* 0x1513 */
void func_ovl0A_02_80047788(s32, s32, s32); /* 0x1516 */
void func_ovl0A_02_80047828(s32); /* 0x1702 */
void func_ovl0A_02_80047838(f32, f32, f32); /* 0x1704 */
void func_ovl0A_02_80047848(f32, f32, f32); /* 0x1706 */
void func_ovl0A_02_80047858(f32, f32, f32); /* 0x1708 */
void func_ovl0A_02_80047860(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0A_02_800478A0(s32); /* 0x1711 */
void func_ovl0A_02_80047930(f32 *); /* 0x1723 */
void func_ovl0A_02_80047988(f32 *, f32 *, f32 *); /* 0x1803 */
void func_ovl0A_02_80047990(f32 *, f32 *); /* 0x1804 */
f32 func_ovl0A_02_800479A0(f32 *, f32 *); /* 0x1806 */
void func_ovl0A_02_800479F0(s32); /* 0x1810 */
void func_ovl0A_02_800479F8(Obj02 *, s32); /* 0x1811 */
void func_ovl0A_02_80047A00(Obj02 *, s32); /* 0x1812 */
void func_ovl0A_02_80047A10(Obj02 *); /* 0x1814 */
Obj02 * func_ovl0A_02_80047A20(s32, s32, s32, Obj02 *); /* 0x1816 */
void func_ovl0A_02_80047A30(Obj02 *); /* 0x1818 */
void func_ovl0A_02_80047A78(Obj02 *); /* 0x1821 */
void func_ovl0A_02_80047AC8(Obj02 *, f32 *); /* 0x182B */
void func_ovl0A_02_80047AD0(Obj02 *, Obj02 *); /* 0x182C */
s32 func_ovl0A_02_80047B48(void (*)(), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0A_02_80047B50(s32); /* 0x1901 */
void func_ovl0A_02_80047B58(void); /* 0x1902 */
void func_ovl0A_02_80047B68(s32); /* 0x1904 */
Obj02 * func_ovl0A_02_80047B70(void); /* 0x1905 */
s32 func_ovl0A_02_80047B90(void); /* 0x1909 */
void func_ovl0A_02_80047BA8(u16); /* 0x190C */
void func_ovl0A_02_80047BC0(s32, s32); /* 0x190F */
UnkStruct_ovl0A_02_80047BD0 * func_ovl0A_02_80047BD0(s32); /* 0x1A00 */
void func_ovl0A_02_80047BE0(UnkStruct_ovl0A_02_80047BD0 *, s32); /* 0x1A02 */
void func_ovl0A_02_80047BE8(UnkStruct_ovl0A_02_80047BD0 *, s32); /* 0x1A03 */
f32 func_ovl0A_02_80047CF0(f32); /* 0x1D00 */
f64 func_ovl0A_02_80047D00(void); /* 0x1D02 */
s32 func_ovl0A_02_80047D08(s32); /* 0x1D03 */
void func_ovl0A_02_80047DC0(s32); /* 0x1E06 */
void func_ovl0A_02_80047DC8(s32); /* 0x1E07 */
s32 func_ovl0A_02_80047DD0(s32); /* 0x1E08 */
void func_ovl0A_02_80047E28(s32); /* 0x2000 */
void func_ovl0A_02_80047E38(s32); /* 0x2002 */
void func_ovl0A_02_80047E40(void); /* 0x2003 */
void func_ovl0A_02_80047E48(s32, s32, s32, f32); /* 0x2004 */
void func_ovl0A_02_80047E90(s32); /* 0x2200 */
void func_ovl0A_02_80047E98(s32, s32, s32); /* 0x2201 */
void func_ovl0A_02_80047EB0(u32 (*)[3]); /* 0x2300 */
void func_ovl0A_02_80047EC8(u32 (*)[3]); /* 0x2303 */
void func_ovl0A_02_80047FA0(s32, f32 *, s32); /* 0x2601 */
void func_ovl0A_02_80048058(s32, s32, s32); /* 0x2A00 */
void func_ovl0A_02_800480D0(s32); /* 0x2B00 */
void func_ovl0A_02_800480E0(s32); /* 0x2B02 */
void func_ovl0A_02_800480F0(s32, s32, s32, s32); /* 0x2B04 */
void func_ovl0A_02_80048248(void); /* 0x3000 */
void func_ovl0A_02_80048250(void); /* 0x3001 */
void func_ovl0A_02_800482B8(void); /* 0x310A */
void func_ovl0A_02_800482C0(void); /* 0x310B */

/* .bss */
u8 D_ovl0A_02_80048500[0x24];
s32 D_ovl0A_02_80048524;
s32 D_ovl0A_02_80048528;
u8 D_ovl0A_02_8004852C[4];
Vec3f_ovl0A_02 D_ovl0A_02_80048530;
UnkStruct_ovl0A_02_80047BD0 *D_ovl0A_02_8004853C;
s32 D_ovl0A_02_80048540;
s32 D_ovl0A_02_80048544;
Obj02 *D_ovl0A_02_80048548[6];
Obj02 *D_ovl0A_02_80048560;
s32 D_ovl0A_02_80048564;
Obj02 *D_ovl0A_02_80048568;
s32 D_ovl0A_02_8004856C;
Obj02 *D_ovl0A_02_80048570;
s32 D_ovl0A_02_80048574;
s32 D_ovl0A_02_80048578;
s32 *D_ovl0A_02_8004857C;
s32 D_ovl0A_02_80048580;
f32 D_ovl0A_02_80048584;
f32 D_ovl0A_02_80048588;
f32 D_ovl0A_02_8004858C;
s32 D_ovl0A_02_80048590;
s32 D_ovl0A_02_80048594;
s32 D_ovl0A_02_80048598;

/* .data */
s32 D_ovl0A_02_800482F0[4][3] = {
    { 0, 7, 0xE5 },
    { 1, 2, 0xE0 },
    { 2, 8, 0xE6 },
    { 3, 0, 0xDE },
};
u32 D_ovl0A_02_80048320[3][3] = {
    { 0x009C0002, 0x0005000E, 4 },
    { 0x009B0002, 0x0000000E, 4 },
    { 0x00970001, 0x0000000F, 0x2084 },
};
u32 D_ovl0A_02_80048344[2][3] = {
    { 0, 4, 0 },
    { 4, 0x00980000, 0x84 },
};
f32 D_ovl0A_02_8004835C[3] = { 1000.0f, 1500.0f, 2000.0f };
f32 D_ovl0A_02_80048368[3] = { 2450.0f, 800.0f, 1400.0f };
f32 D_ovl0A_02_80048374[6][3] = {
    { 2550.0f, 800.0f, 1500.0f },
    { 2350.0f, 800.0f, 1500.0f },
    { 2550.0f, 800.0f, 1300.0f },
    { 2350.0f, 800.0f, 1300.0f },
    { 2450.0f, 800.0f, 1600.0f },
    { 2450.0f, 800.0f, 1200.0f },
};
Vec3f_ovl0A_02 D_ovl0A_02_800483BC = { 0.0f, 0.0f, 0.0f };
f32 D_ovl0A_02_800483C8[2][3] = {
    { 2550.0f, 600.0f, 1500.0f },
    { 2950.0f, 600.0f, 1300.0f },
};

void func_ovl0A_02_80043070(void);
void func_ovl0A_02_80045214(f32 *pos, f32 *sph, f32 *r, f32 *step);
void func_ovl0A_02_80043C38(void);
void func_ovl0A_02_80043E68(void);
void func_ovl0A_02_80044364(void);
void func_ovl0A_02_800446EC(void);
void func_ovl0A_02_800447CC(void);
void func_ovl0A_02_80044998(void);
void func_ovl0A_02_80044B14(void);
void func_ovl0A_02_80044ED0(void);
void func_ovl0A_02_80045054(void);
void func_ovl0A_02_80045294(void);
void func_ovl0A_02_80045468(void);
void func_ovl0A_02_80046724(void);
void func_ovl0A_02_8004699C(void);

static void func_ovl0A_02_80043010(Obj02 *obj);
static void func_ovl0A_02_80043068(Obj02 *obj);
void func_ovl0A_02_800438FC(void);
void func_ovl0A_02_80043938(void);
void func_ovl0A_02_80043CA0(Obj02 *obj, f32 *from, f32 *to);
void func_ovl0A_02_80043D60(f32 *center, f32 *out);
void func_ovl0A_02_80043E3C(void);
void func_ovl0A_02_8004426C(void);
void func_ovl0A_02_8004438C(void);
void func_ovl0A_02_80044744(void);
void func_ovl0A_02_80044780(void);
void func_ovl0A_02_80044CA4(void);
void func_ovl0A_02_800456D0(void);
static void func_ovl0A_02_80045958(s32 (*tbl)[3], s32 n);
void func_ovl0A_02_80045960(void);
void func_ovl0A_02_80045A50(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_02_80045ACC(void);
Obj02 *func_ovl0A_02_80045B34(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_ovl0A_02_80045C0C(void);
void func_ovl0A_02_80045D88(void);
void func_ovl0A_02_80045EA4(Obj02 **arg0, s32 *arg1, Obj02 **arg2, s32 *arg3, Obj02 **arg4, s32 *arg5, s32 arg6);
void func_ovl0A_02_8004624C(s32 arg0, s32 arg1, s32 arg2);
void func_ovl0A_02_800462EC(void);
void func_ovl0A_02_800463B4(void);
void func_ovl0A_02_800463D4(void);
void func_ovl0A_02_800464F8(void);
void func_ovl0A_02_80046560(void);
void func_ovl0A_02_80046588(void);
void func_ovl0A_02_800465B0(void);
void func_ovl0A_02_800465D0(void);
void func_ovl0A_02_800465F0(void);
void func_ovl0A_02_8004664C(s32 arg0);
void func_ovl0A_02_80046B70(s32 arg0, UnkStruct_ovl0A_02_B04 *arg1);
void func_ovl0A_02_80046BA4(f32 arg0);
void func_ovl0A_02_80046BEC(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_02_80046C48(void);
static void func_ovl0A_02_80046C60(void);
static void func_ovl0A_02_80046C68(void);
static void func_ovl0A_02_80046C70(void);
static void func_ovl0A_02_80046C78(void);
static void func_ovl0A_02_80046C80(void);
static void func_ovl0A_02_80046C88(void);
static void func_ovl0A_02_80046C90(void);
static void func_ovl0A_02_80046C98(void);
static void func_ovl0A_02_80046CA0(void);

static void func_ovl0A_02_80046CA0(void) {
}

static void func_ovl0A_02_80046C98(void) {
}

static void func_ovl0A_02_80046C90(void) {
}

static void func_ovl0A_02_80046C88(void) {
}

static void func_ovl0A_02_80046C80(void) {
}

static void func_ovl0A_02_80046C78(void) {
}

static void func_ovl0A_02_80046C70(void) {
}

static void func_ovl0A_02_80046C68(void) {
}

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common,
 * and takes the tasks' addresses, which keeps them after the handler */
static void func_ovl0A_02_80046C60(void) {
    D_ovl0A_02_80048500[0] = D_ovl0A_02_8004852C[0];
    func_ovl0A_02_80047B48(func_ovl0A_02_80046724, NULL, 0, 0, 0);
    func_ovl0A_02_80047B48(func_ovl0A_02_8004699C, NULL, 0, 0, 0);
}

void func_ovl0A_02_80046C48(void) {
    D_ovl0A_02_80048524 = -1;
    D_ovl0A_02_80048528 = -1;
}

void func_ovl0A_02_80046BEC(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0A_02_80047838(D_ovl0A_02_80048530.x, D_ovl0A_02_80048530.y, D_ovl0A_02_80048530.z);
    func_ovl0A_02_80047858(arg0, arg1, arg2);
    func_ovl0A_02_80047B68(0xB4);
}

void func_ovl0A_02_80046BA4(f32 arg0) {
    f32 sp1C;

    func_ovl0A_02_80047860(&sp1C, NULL, NULL);
    func_ovl0A_02_80047858(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0A_02_80046B70(s32 arg0, UnkStruct_ovl0A_02_B04 *arg1) {
    UnkStruct_ovl0A_02_B04_Inner *p;

    p = arg1->unk40;
    func_ovl0A_02_800480F0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0A_02_8004699C(void) {
    Obj02 *self;
    Obj02 *obj;
    f32 d;
    f32 s;

    self = func_ovl0A_02_80047B70();
    obj = func_ovl0A_02_80047A20(0x34D, 0x01080000, 0xD0, NULL);
    obj->unk40->unk36 = 0x7F;
    obj->unk40->unk10 = 1000.0f;
    obj->unk40->unk14 = -100.0f;
    obj->unk40->unk18 = -650.0f;
    obj->unk40->unk20 = self->unk40->unk20;
    func_ovl0A_02_80047B68(4);
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
            func_ovl0A_02_800479F8(obj, 0x01000000);
        } else {
            func_ovl0A_02_80047A00(obj, 0x01000000);
        }
        func_ovl0A_02_80047B90();
    }
}

void func_ovl0A_02_80046724(void) {
    Obj02 *self;
    Obj02 *obj;
    Obj02 *parts[4];
    s32 i;
    f32 d;
    f32 s;

    self = func_ovl0A_02_80047B70();
    obj = func_ovl0A_02_80047A20(-1, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = 1000.0f;
    obj->unk40->unk14 = -100.0f;
    obj->unk40->unk18 = -650.0f;
    obj->unk40->unk20 = self->unk40->unk20;
    for (i = 0; i < 4; i++) {
        parts[i] = func_ovl0A_02_80047A20(0x34D, 0x01780000, 0xD0, obj);
        parts[i]->unk40->unk36 = 0x7F;
    }
    parts[0]->unk4C = 300.0f;
    parts[1]->unk54 = 300.0f;
    parts[2]->unk4C = -300.0f;
    parts[3]->unk54 = -300.0f;
    func_ovl0A_02_80047B68(4);
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
        func_ovl0A_02_80047B90();
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0A_02_8004664C(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0A_02_800465F0();
            break;
        case 16:
            func_ovl0A_02_800465B0();
            break;
        case 17:
            func_ovl0A_02_800465D0();
            break;
        case 18:
            func_ovl0A_02_80046588();
            break;
        case 19:
            func_ovl0A_02_80046560();
            break;
        case 4:
            func_ovl0A_02_800464F8();
            break;
        case 5:
            func_ovl0A_02_800463D4();
            break;
        case 3:
            func_ovl0A_02_800463B4();
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
        case 1:
            func_ovl0A_02_800462EC();
            break;
    }
}

void func_ovl0A_02_800465F0(void) {
    D_ovl0A_02_8004857C = func_ovl0A_02_80047148();
    D_ovl0A_02_80048580 = func_ovl0A_02_800470F8();
    D_ovl0A_02_80048578 = 0;
    func_ovl0A_02_80047DC8(0x400);
    func_ovl0A_02_80047DC8(0x401);
    func_ovl0A_02_80047DC8(0x402);
    func_ovl0A_02_80047DC8(0x403);
}

void func_ovl0A_02_800465D0(void) {
    func_ovl0A_02_80045960();
}

void func_ovl0A_02_800465B0(void) {
    func_ovl0A_02_80045960();
}

void func_ovl0A_02_80046588(void) {
    func_ovl0A_02_8004624C(5, 0, 8);
}

void func_ovl0A_02_80046560(void) {
    func_ovl0A_02_8004624C(0xA, 0, 3);
}

void func_ovl0A_02_800464F8(void) {
    if (D_ovl0A_02_80048580 == 0x10 || D_ovl0A_02_80048580 == 0x11 || D_ovl0A_02_80048580 == 0x12) {
        func_ovl0A_02_80047E48(0xFF, 0xFF, 0xFF, 100.0f);
    } else {
        func_ovl0A_02_80047E48(0, 0, 0, 100.0f);
    }
}

void func_ovl0A_02_800463D4(void) {
    func_ovl0A_02_80047168(1);
    func_ovl0A_02_80047160(0);
    switch (D_ovl0A_02_80048580) {
        case 16:
            func_ovl0A_02_80047B48(func_ovl0A_02_800456D0, NULL, 0, 0, 0x150);
            break;
        case 17:
            func_ovl0A_02_80047B48(func_ovl0A_02_80044CA4, NULL, 0, 0, 0x150);
            break;
        case 18:
            func_ovl0A_02_80044780();
            func_ovl0A_02_80047B48(func_ovl0A_02_8004438C, NULL, 0, 0, 0x150);
            break;
        case 19:
            func_ovl0A_02_80047B48(func_ovl0A_02_80043938, NULL, 0, 0, 0x150);
            break;
    }
}

void func_ovl0A_02_800463B4(void) {
    func_ovl0A_02_80047DC0(0x400);
}

void func_ovl0A_02_800462EC(void) {
    if (D_ovl0A_02_80048580 != 0x11) {
        func_ovl0A_02_80047E48(0, 0, 0, 0.0f);
    } else {
        func_ovl0A_02_80047E48(0, 0, 0xFF, 100.0f);
    }
    func_ovl0A_02_80044744();
    if (*D_ovl0A_02_8004857C & 4) {
        if (D_ovl0A_02_80048580 == 0x13) {
            func_ovl0A_02_800482C0();
        } else {
            func_ovl0A_02_800482B8();
        }
    }
}

void func_ovl0A_02_8004624C(s32 arg0, s32 arg1, s32 arg2) {
    func_ovl0A_02_80046FF8(0x33A);
    func_ovl0A_02_80047010(0x339);
    func_ovl0A_02_800471A8();
    func_ovl0A_02_800471B0(arg0, arg1, arg2);
    func_ovl0A_02_80045EA4(&D_ovl0A_02_80048560, &D_ovl0A_02_80048564, &D_ovl0A_02_80048568,
                           &D_ovl0A_02_8004856C, &D_ovl0A_02_80048570, &D_ovl0A_02_80048574, 0);
    func_ovl0A_02_80045D88();
    func_ovl0A_02_800479F0(0);
}

void func_ovl0A_02_80045EA4(Obj02 **arg0, s32 *arg1, Obj02 **arg2, s32 *arg3, Obj02 **arg4, s32 *arg5, s32 arg6) {
    s32 i;

    *arg0 = func_ovl0A_02_80047A20(0x27, 0x01000000, 0xD0, NULL);
    (*arg0)->unk40->unk10 = 1000.0f;
    (*arg0)->unk40->unk14 = 50.0f;
    (*arg0)->unk40->unk18 = -650.0f;
    (*arg0)->unk40->unk30 = 0.5f;
    (*arg0)->unk40->unk28 = (*arg0)->unk40->unk2C = (*arg0)->unk40->unk30;
    (*arg0)->unk40->unk20 = 345.0f;
    *arg1 = func_ovl0A_02_80047768((*arg0)->unk40, 0x19);
    for (i = 0; i < 0x19; i++) {
        if (i == 0x10 || i == 0x11 || i == 0x12 || i == 0x13) {
            func_ovl0A_02_80047770(*arg1, i, 0x4F);
        }
    }
    if (arg6 != 0) {
        func_ovl0A_02_80047770(*arg1, 0xF, 0x4F);
        func_ovl0A_02_80047770(*arg1, 0xD, 0x4F);
        func_ovl0A_02_80047770(*arg1, 0xC, 0x4F);
        func_ovl0A_02_80047770(*arg1, 0xB, 0x4F);
        func_ovl0A_02_80047770(*arg1, 0xE, 0x4F);
        func_ovl0A_02_80047770(*arg1, 5, 0x4F);
        func_ovl0A_02_80047770(*arg1, 2, 0x4F);
        func_ovl0A_02_80047770(*arg1, 4, 0x4F);
        func_ovl0A_02_80047770(*arg1, 3, 0x4F);
        *arg2 = func_ovl0A_02_80047A20(0x27, 0x01400000, 0xD0, *arg0);
        *arg3 = func_ovl0A_02_80047768((*arg2)->unk40, 0x19);
        for (i = 0; i < 0x19; i++) {
            switch (i) {
                case 0xB:
                case 0xC:
                case 0xD:
                case 0xE:
                case 0xF:
                    break;
                default:
                    func_ovl0A_02_80047770(*arg3, i, 0x4F);
                    break;
            }
        }
        if (arg6 >= 2) {
            *arg4 = func_ovl0A_02_80047A20(0x27, 0x01400000, 0xD0, *arg0);
            *arg5 = func_ovl0A_02_80047768((*arg4)->unk40, 0x19);
            for (i = 0; i < 0x19; i++) {
                switch (i) {
                    case 0x10:
                    case 0x11:
                    case 0x12:
                    case 0x13:
                        break;
                    default:
                        func_ovl0A_02_80047770(*arg5, i, 0x4F);
                        break;
                }
            }
        }
    }
    if (arg6 != 0) {
        D_ovl0A_02_80048540 = func_ovl0A_02_80047B48(func_ovl0A_02_8004699C, *arg2, 0, 0, 0x150);
    } else {
        D_ovl0A_02_80048540 = func_ovl0A_02_80047B48(func_ovl0A_02_8004699C, *arg0, 0, 0, 0x150);
    }
    D_ovl0A_02_80048544 = func_ovl0A_02_80047B48(func_ovl0A_02_80046724, *arg0, 0, 0, 0x150);
}

void func_ovl0A_02_80045D88(void) {
    D_ovl0A_02_8004853C = func_ovl0A_02_80047BD0(0x33B);
    func_ovl0A_02_80047BE0(D_ovl0A_02_8004853C, 0x20000001);
    D_ovl0A_02_8004853C->unk40 = 1.0f;
    D_ovl0A_02_8004853C->unk44 = 1.0f;
    D_ovl0A_02_8004853C->unk28 = 0.0f;
    D_ovl0A_02_8004853C->unk2C = 120.0f;
    D_ovl0A_02_8004853C->unk30 = D_ovl0A_02_8004853C->unk28 + D_ovl0A_02_8004853C->unk48 * 2.0f;
    D_ovl0A_02_8004853C->unk34 = D_ovl0A_02_8004853C->unk2C + D_ovl0A_02_8004853C->unk4C * 2.0f * 0.8f;
    func_ovl0A_02_80047E90(1);
    func_ovl0A_02_80047E98(0, 0, 0xFF);
    func_ovl0A_02_800478A0(0x7F);
    func_ovl0A_02_80047838(1000.0f, 400.0f, 200.0f);
    func_ovl0A_02_80047828(1);
    func_ovl0A_02_80047858(0.0f, 20.0f, 1700.0f);
    func_ovl0A_02_80045C0C();
    func_ovl0A_02_80045ACC();
}

void func_ovl0A_02_80045C0C(void) {
    s32 i;

    i = 0;
    D_ovl0A_02_80048548[i++] = func_ovl0A_02_80045B34(1000.0f, 50.0f, -1150.0f, 13.0f, 2.0f);
    D_ovl0A_02_80048548[i++] = func_ovl0A_02_80045B34(1500.0f, 150.0f, -550.0f, 13.0f, 2.0f);
    D_ovl0A_02_80048548[i++] = func_ovl0A_02_80045B34(1000.0f, 1050.0f, -650.0f, 13.0f, 5.0f);
    D_ovl0A_02_80048548[i++] = func_ovl0A_02_80045B34(500.0f, 1050.0f, -450.0f, 13.0f, 5.0f);
    D_ovl0A_02_80048548[i++] = func_ovl0A_02_80045B34(500.0f, 1050.0f, -250.0f, 13.0f, 4.0f);
    D_ovl0A_02_80048548[i++] = func_ovl0A_02_80045B34(1500.0f, 1050.0f, -1050.0f, 13.0f, 5.0f);
}

Obj02 *func_ovl0A_02_80045B34(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    Obj02 *obj;

    obj = func_ovl0A_02_80047A20(0x11D, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = arg0;
    obj->unk40->unk14 = arg1;
    obj->unk40->unk18 = arg2;
    obj->unk40->unkC |= 0x8000;
    func_ovl0A_02_80047700(obj->unk40, 1);
    func_ovl0A_02_80047708(obj->unk40, 0x11E, 0, 1);
    obj->unk40->unk28 = arg3;
    obj->unk40->unk2C = arg4;
    obj->unk40->unk36 = 0xCC;
    return obj;
}

void func_ovl0A_02_80045ACC(void) {
    func_ovl0A_02_80045A50(500.0f, 0.0f, 400.0f);
    func_ovl0A_02_80045A50(1600.0f, 0.0f, 300.0f);
    func_ovl0A_02_80045A50(500.0f, 0.0f, 700.0f);
    func_ovl0A_02_80045A50(1700.0f, 0.0f, 600.0f);
}

void func_ovl0A_02_80045A50(f32 arg0, f32 arg1, f32 arg2) {
    Obj02 *obj;

    obj = func_ovl0A_02_80047A20(0x97, 0x01000000, 0xD0, NULL);
    obj->unk40->unk10 = arg0;
    obj->unk40->unk14 = arg1;
    obj->unk40->unk18 = arg2;
    func_ovl0A_02_80047A20(0x98, 0x01480000, 0xD0, obj)->unk40->unk36 = 0x80;
}

void func_ovl0A_02_80045960(void) {
    func_ovl0A_02_80047EB0(D_ovl0A_02_80048320);
    func_ovl0A_02_80047EC8(D_ovl0A_02_80048344);
    func_ovl0A_02_80045958(D_ovl0A_02_800482F0, 4);
    func_ovl0A_02_80046FF8(0x13B);
    func_ovl0A_02_80047010(0x141);
    func_ovl0A_02_800471A8();
    func_ovl0A_02_800471B0(0x16, 1, 0x10);
    func_ovl0A_02_800471B0(0x2E, 1, 0x1D);
    func_ovl0A_02_800478A0(0x7F);
    func_ovl0A_02_80047838(2250.0f, 600.0f, 1500.0f);
    func_ovl0A_02_80047858(100.0f, 34.0f, 2600.0f);
}

static void func_ovl0A_02_80045958(s32 (*tbl)[3], s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0A_02_80048058((*tbl)[0], (*tbl)[1], (*tbl)[2]);
        tbl++;
    }
}

void func_ovl0A_02_800456D0(void) {
    s32 i;
    Vec3f_ovl0A_02 pos;

    pos = D_ovl0A_02_800483BC;
    func_ovl0A_02_800480E0(1);
    while (!func_ovl0A_02_80047DD0(0x400)) {
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_8004426C();
    for (i = 0; i < 8; i++) {
        pos.x = D_ovl0A_02_8004835C[0] + func_ovl0A_02_80047D00() * 300.0;
        pos.y = D_ovl0A_02_8004835C[1] + func_ovl0A_02_80047D00() * 100.0;
        pos.z = D_ovl0A_02_8004835C[2] + func_ovl0A_02_80047D00() * 300.0;
        func_ovl0A_02_80047B48(func_ovl0A_02_80045468, &pos, 0, 0, 0x150);
        func_ovl0A_02_80047B68(10);
    }
    func_ovl0A_02_80047B68(140);
    for (i = 0; i < 20; i++) {
        func_ovl0A_02_80047E48(0, 0, 0, ((f32) i / 20.0f) * 35.0f);
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047B68(90);
    for (i = 0; i < 6; i++) {
        func_ovl0A_02_80047B48(func_ovl0A_02_80045054, (void *) i, 0, 0, 0x150);
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047B68(90);
    func_ovl0A_02_80047B48(func_ovl0A_02_80045294, &pos, 0, 0, 0x150);
    while (!func_ovl0A_02_80047DD0(0x401)) {
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047B68(30);
    func_ovl0A_02_80047E38(4);
    func_ovl0A_02_80047E40();
    func_ovl0A_02_800470F0(0x19, 0x10, 1);
    func_ovl0A_02_80047B58();
}

void func_ovl0A_02_80045468(void) {
    f32 *start;
    Obj02 *obj;
    f32 pos[3];
    f32 target[3];
    f32 sph[3];
    f32 ang[3];
    f32 r;
    f32 step;

    start = func_ovl0A_02_80047B70();
    obj = func_ovl0A_02_80047A20(0x33E, 0x0D000004, 0xD0, NULL);
    func_ovl0A_02_80047A30(obj);
    func_ovl0A_02_80047AD0(start, obj);
    func_ovl0A_02_80047AC8(obj, pos);
    func_ovl0A_02_80047AC8(obj, obj->unk58);
    func_ovl0A_02_80047930(target);
    target[1] += 300.0f;
    sph[0] = 110.0f;
    sph[1] = 0.1f;
    sph[2] = 0.0f;
    r = 5.0f;
    step = 0.25f;
    while (TRUE) {
        if (func_ovl0A_02_800479A0(pos, target) > 4000.0f) {
            break;
        }
        func_ovl0A_02_80045214(pos, sph, &r, &step);
        func_ovl0A_02_80047AD0(pos, obj);
        func_ovl0A_02_80047988(obj->unk58, pos, ang);
        ang[1] = ((ang[1] - 90.0f) >= 360.0f ? (ang[1] - 90.0f) - 360.0f
                  : (ang[1] - 90.0f) < 0.0f ? (ang[1] - 90.0f) + 360.0f : (ang[1] - 90.0f)) * -1.0f;
        obj->unk40->unk20 = ang[0];
        obj->unk40->unk1C = ang[1];
        sph[0] -= 0.01f;
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047A10(obj);
    func_ovl0A_02_80047B58();
}

void func_ovl0A_02_80045294(void) {
    Obj02 *obj;
    f32 pos[3];
    f32 sph[3];
    f32 r;
    f32 step;
    f32 t;
    f32 n;

    obj = func_ovl0A_02_80047A20(0x320, 0x0D000004, 0xD0, NULL);
    func_ovl0A_02_80047A30(obj);
    obj->unk40->unk20 = 90.0f;
    func_ovl0A_02_80047AD0(D_ovl0A_02_80048368, obj);
    obj->unk40->unk14 = 2000.0f;
    n = 120.0f;
    sph[1] = -90.0f;
    r = (2000.0f - D_ovl0A_02_80048368[1]) / (n * 0.5f);
    sph[0] = 0.0f;
    sph[2] = 0.0f;
    step = (r / n) * -1.0f;
    func_ovl0A_02_80047AC8(obj, pos);
    for (t = 0.0f; t < n; t += 1.0f) {
        func_ovl0A_02_80045214(pos, sph, &r, &step);
        func_ovl0A_02_80047AD0(pos, obj);
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047720(obj->unk40, 0x1F, 0);
    func_ovl0A_02_80047A00(obj, 0x08000000);
    func_ovl0A_02_800479F8(obj, 0x04000000);
    func_ovl0A_02_80043010(obj);
    func_ovl0A_02_80047B68(10);
    func_ovl0A_02_80047DC0(0x401);
    while (1) {
        func_ovl0A_02_80047B90();
    }
}

void func_ovl0A_02_80045214(f32 *pos, f32 *sph, f32 *r, f32 *step) {
    f32 d[3];

    sph[2] = *r;
    *r += *step;
    func_ovl0A_02_80047990(sph, d);
    pos[0] += d[0];
    pos[1] += d[1];
    pos[2] += d[2];
}

void func_ovl0A_02_80045054(void) {
    s32 idx;
    Obj02 *obj;
    s32 i;

    idx = (s32) func_ovl0A_02_80047B70();
    obj = func_ovl0A_02_80047A20(0xDE, 0x0D000004, 0xD0, NULL);
    func_ovl0A_02_80047A30(obj);
    obj->unk40->unk20 = 90.0f;
    func_ovl0A_02_80047AD0(D_ovl0A_02_80048374[idx], obj);
    obj->unk40->unk14 = 2000.0f;
    obj->unk68 = 0.001f;
    while (obj->unk68 != 0.0f) {
        func_ovl0A_02_80047A78(obj);
        func_ovl0A_02_80047B90();
    }
    while (!func_ovl0A_02_80047DD0(0x401)) {
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_800479F8(obj, 0x04000000);
    for (i = 0; i < 2; i++) {
        obj->unk68 = 25.0f;
        while (obj->unk68 != 0.0f) {
            func_ovl0A_02_80047A78(obj);
            func_ovl0A_02_80047B90();
        }
    }
    while (1) {
        obj->unk40->unk10 += 4.0f;
        func_ovl0A_02_80047B90();
    }
}

void func_ovl0A_02_80044ED0(void) {
    f32 angle;
    f32 v;

    angle = 0.0f;
    while (1) {
        v = func_ovl0A_02_80047CF0(angle) * D_ovl0A_02_80048588 + D_ovl0A_02_80048584;
        if (v > 100.0f) {
            v = 100.0f;
        }
        if (v < 0.0f) {
            v = 0.0f;
        }
        func_ovl0A_02_80047E48(D_ovl0A_02_80048590, D_ovl0A_02_80048594, D_ovl0A_02_80048598, v);
        angle = (angle + D_ovl0A_02_8004858C) >= 360.0f ? (angle + D_ovl0A_02_8004858C) - 360.0f
              : (angle + D_ovl0A_02_8004858C) < 0.0f ? (angle + D_ovl0A_02_8004858C) + 360.0f
              : (angle + D_ovl0A_02_8004858C);
        func_ovl0A_02_80047B90();
    }
}

void func_ovl0A_02_80044CA4(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_ovl0A_02_80047B48(func_ovl0A_02_800447CC, (void *) i, 0, 0, 0x150);
    }
    while (!func_ovl0A_02_80047DD0(0x400)) {
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047B68(15);
    func_ovl0A_02_8004426C();
    func_ovl0A_02_80047B68(120);
    D_ovl0A_02_80048584 = 0.0f;
    D_ovl0A_02_80048588 = 5.0f;
    D_ovl0A_02_8004858C = 6.0f;
    D_ovl0A_02_80048590 = 0;
    D_ovl0A_02_80048594 = 0;
    D_ovl0A_02_80048598 = 0xFF;
    func_ovl0A_02_80047B48(func_ovl0A_02_80044ED0, NULL, 0, 0, 0x150);
    for (i = 0; i < 120; i++) {
        D_ovl0A_02_80048584 = ((f32) i * 30.0f) / 120.0f;
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047B48(func_ovl0A_02_80044B14, NULL, 0, 0, 0x150);
    func_ovl0A_02_80047B68(180);
    for (i = 0; i < 360; i++) {
        D_ovl0A_02_80048584 = (((f32) i * 70.0f) / 360.0f) + 30.0f;
        func_ovl0A_02_80047B90();
    }
    D_ovl0A_02_80048584 = 100.0f;
    D_ovl0A_02_80048588 = 0.0f;
    D_ovl0A_02_8004858C = 0.0f;
    func_ovl0A_02_800470F0(0x19, 0x11, 3);
    func_ovl0A_02_80047B58();
}

void func_ovl0A_02_80044B14(void) {
    f32 pos[3];

    while (1) {
        pos[0] = 2250.0f;
        pos[1] = 600.0f;
        pos[2] = 1500.0f;
        if (func_ovl0A_02_80047D08(1)) {
            pos[0] += func_ovl0A_02_80047D00() * 1000.0;
        } else {
            pos[0] -= func_ovl0A_02_80047D00() * 1000.0;
        }
        if (func_ovl0A_02_80047D08(1)) {
            pos[2] += func_ovl0A_02_80047D00() * 1000.0;
        } else {
            pos[2] -= func_ovl0A_02_80047D00() * 1000.0;
        }
        func_ovl0A_02_80047B48(func_ovl0A_02_80044998, pos, 0, 0, 0x150);
        func_ovl0A_02_80047B68(10);
    }
}

void func_ovl0A_02_80044998(void) {
    f32 *pos;
    Obj02 *obj;
    f32 v;
    s32 i;
    f32 s;

    pos = func_ovl0A_02_80047B70();
    obj = func_ovl0A_02_80047A20(0x2D3, 0x01080000, 0xD0, NULL);
    obj->unk40->unk30 = 5.0f;
    obj->unk40->unk28 = obj->unk40->unk2C = obj->unk40->unk30;
    obj->unk40->unk36 = 0x7F;
    func_ovl0A_02_80047AD0(pos, obj);
    s = 13.333333f;
    for (v = s; v > 0.0f;) {
        obj->unk40->unk14 += v;
        v += s / 60.0f - 1.0f;
        func_ovl0A_02_80047B90();
    }
    v = 2.0f;
    for (i = 0; i < 180; i++) {
        obj->unk40->unk14 += v;
        v += 0.1f;
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047A10(obj);
    func_ovl0A_02_80047B58();
}

void func_ovl0A_02_800447CC(void) {
    s32 idx;
    Obj02 *obj;
    s32 i;
    f32 t;
    f32 n;
    f32 rot;

    idx = (s32) func_ovl0A_02_80047B70();
    obj = func_ovl0A_02_80047A20(0xDE, 0x0D000004, 0xD0, NULL);
    func_ovl0A_02_80047AD0(D_ovl0A_02_800483C8[idx], obj);
    for (i = 0; i < 10; i++) {
        func_ovl0A_02_80047D00();
    }
    rot = func_ovl0A_02_80047D00() * 360.0;
    if (!obj) { /* fake: ends the block, so rot is the value spilled */
    }
    obj->unk40->unk20 = rot;
    func_ovl0A_02_80047A30(obj);
    func_ovl0A_02_80047D08(1);
    while (1) {
        n = 120.0f;
        for (t = 0.0f; t < n; t += 1.0f) {
            obj->unk40->unk20 = func_ovl0A_02_80047CF0((t / 120.0f) * 360.0f) * 20.0f + rot;
            func_ovl0A_02_80047B90();
        }
        func_ovl0A_02_80047B68(func_ovl0A_02_80047D08(20) + 10);
    }
}

void func_ovl0A_02_80044780(void) {
    if (*D_ovl0A_02_8004857C & 2) {
        func_ovl0A_02_80047B48(func_ovl0A_02_800446EC, NULL, 0, 0, 0x130);
    }
}

void func_ovl0A_02_80044744(void) {
    if (*D_ovl0A_02_8004857C & 2) {
        func_ovl0A_02_80048250();
    }
}

void func_ovl0A_02_800446EC(void) {
    while (!func_ovl0A_02_80047DD0(0x400)) {
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047B68(0x564);
    func_ovl0A_02_80048248();
    func_ovl0A_02_80047B58();
}

void func_ovl0A_02_8004438C(void) {
    s32 i;
    f32 y;

    func_ovl0A_02_80047BE8(D_ovl0A_02_8004853C, 0x20000000);
    func_ovl0A_02_80047838(D_ovl0A_02_80048560->unk40->unk10, 1000.0f, D_ovl0A_02_80048560->unk40->unk18);
    func_ovl0A_02_80047828(0);
    func_ovl0A_02_80047848(830.0f, -310.0f, 870.0f);
    y = D_ovl0A_02_80048560->unk40->unk14;
    D_ovl0A_02_80048560->unk40->unk14 = 1000.0f;
    func_ovl0A_02_80047BA8(D_ovl0A_02_80048540);
    func_ovl0A_02_80047BA8(D_ovl0A_02_80048544);
    func_ovl0A_02_800471E8(1);
    while (!func_ovl0A_02_80047DD0(0x400)) {
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047B48(func_ovl0A_02_80044364, NULL, 0, 0, 0x150);
    func_ovl0A_02_800480D0(0x2CE);
    for (i = 0; i < 240; i++) {
        D_ovl0A_02_80048560->unk40->unk14 -= 1.0f;
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047E38(3);
    for (i = 0; i < 120; i++) {
        D_ovl0A_02_80048560->unk40->unk14 -= 1.0f;
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047838(1000.0f, 400.0f, 200.0f);
    func_ovl0A_02_80047828(1);
    func_ovl0A_02_80047858(0.0f, 20.0f, 1700.0f);
    func_ovl0A_02_80047BE0(D_ovl0A_02_8004853C, 0x20000000);
    func_ovl0A_02_80047E48(0, 0, 0, 0.0f);
    func_ovl0A_02_80047E28(3);
    func_ovl0A_02_800480D0(0x2CF);
    while (y < D_ovl0A_02_80048560->unk40->unk14) {
        D_ovl0A_02_80048560->unk40->unk14 -= 1.0f;
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_800471F8(0x20, 3, 8.5f, 5, 1, 1, 0);
    func_ovl0A_02_80047B68(2);
    func_ovl0A_02_800471F8(0, 3, 4.0f, 0, 1, 1, 0);
    func_ovl0A_02_80047B68(30);
    func_ovl0A_02_80047B48(func_ovl0A_02_80043C38, NULL, 0, 0, 0x150);
    func_ovl0A_02_80047220(0x20000);
    func_ovl0A_02_80047B68(110);
    func_ovl0A_02_80047288(func_ovl0A_02_800471D8(), 0xB);
    func_ovl0A_02_80047B68(180);
    if (!(*D_ovl0A_02_8004857C & 2)) {
        func_ovl0A_02_800470F0(0x19, 0x12, 0);
    }
    func_ovl0A_02_80047B58();
}

void func_ovl0A_02_80044364(void) {
    func_ovl0A_02_8004426C();
    func_ovl0A_02_80047B58();
}

void func_ovl0A_02_8004426C(void) {
    f32 t;

    for (t = 0.0f; t < 40.0f; t += 1.0f) {
        func_ovl0A_02_80047E48(0xFF, 0xFF, 0xFF, (1.0f - (t / 39.0f)) * 100.0f);
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047E48(0, 0, 0, 0.0f);
}

void func_ovl0A_02_80043E68(void) {
    static s32 D_ovl0A_02_800483E0 = 0;
    f32 center[3];
    f32 a[3];
    f32 b[3];
    f32 start[3];
    f32 x[3];
    f32 y[3];
    f32 pos[3];
    Obj02 *obj;
    f32 dx;
    f32 dz;
    f32 t;
    s32 i;
    s32 pad[2];

    obj = func_ovl0A_02_80047A20(0x1CB, 0x01480000, 0xD0, NULL);
    obj->unk40->unk30 = 0.5f;
    obj->unk40->unk28 = obj->unk40->unk30;
    func_ovl0A_02_80047AC8(D_ovl0A_02_80048560, pos);
    pos[1] += 250.0f;
    pos[2] += 50.0f;
    func_ovl0A_02_80047AD0(pos, obj);
    center[0] = pos[0] + 500.0f;
    center[1] = pos[1] - 1300.0f;
    center[2] = pos[2] - 1500.0f;
    func_ovl0A_02_80043D60(center, a);
    func_ovl0A_02_80043D60(center, b);
    start[0] = a[0];
    start[1] = a[1];
    start[2] = a[2];
    dx = (b[0] - a[0]) / 40.0f;
    dz = (b[2] - a[2]) / 40.0f;
    if (!(*D_ovl0A_02_8004857C & 2)) {
        for (t = 0.0f; t < 20.0f; t += 1.0f) {
            func_ovl0A_02_80047E48(0xFF, 0xFF, 0xFF, (1.0f - (t / 20.0f)) * 100.0f);
            func_ovl0A_02_80047B90();
            if (t == 5.0f && D_ovl0A_02_80048580 == 0x12 && D_ovl0A_02_800483E0 == 0) {
                D_ovl0A_02_800483E0 = 1;
                func_ovl0A_02_800480D0(0x2D0);
            }
        }
        func_ovl0A_02_80047E48(0, 0, 0, 0.0f);
    }
    for (i = 0; i < 40; i++) {
        if (i == 5 && D_ovl0A_02_80048580 == 0x12) {
            func_ovl0A_02_800480D0(0x2D1);
        }
        obj->unk40->unk36 = (1.0f - ((f32) i / 40.0f)) * 191.25f;
        func_ovl0A_02_80043CA0(obj, pos, a);
        a[0] += dx;
        a[2] += dz;
        func_ovl0A_02_80047B90();
    }
    a[0] = start[0];
    a[1] = start[1];
    a[2] = start[2];
    for (i = 0; i < 40; i += 10) {
        func_ovl0A_02_80047FA0(9, a, 0);
        a[0] += dx * 10.0f;
        a[2] += dz * 10.0f;
        func_ovl0A_02_80047B68(5);
        if (i == 0 && D_ovl0A_02_80048580 == 0x12) {
            func_ovl0A_02_800480D0(0x2D2);
        }
        func_ovl0A_02_80047B68(5);
    }
    func_ovl0A_02_80047A10(obj);
    func_ovl0A_02_80047B58();
}

void func_ovl0A_02_80043E3C(void) {
    func_ovl0A_02_80047A20(0x1CB, 0x01480000, 0xD0, NULL);
}

void func_ovl0A_02_80043D60(f32 *center, f32 *out) {
    out[0] = func_ovl0A_02_80047D00() * 240.0;
    if (func_ovl0A_02_80047D08(1)) {
        out[0] *= -1.0f;
    }
    out[0] += center[0];
    out[1] = center[1];
    out[2] = func_ovl0A_02_80047D00() * 120.0;
    if (func_ovl0A_02_80047D08(1)) {
        out[2] *= -1.0f;
    }
    out[2] += center[2];
}

void func_ovl0A_02_80043CA0(Obj02 *obj, f32 *from, f32 *to) {
    f32 ang[3];

    func_ovl0A_02_80047988(from, to, ang);
    obj->unk40->unk20 = ang[0];
    obj->unk40->unk1C = ((ang[1] - 180.0f) >= 360.0f ? (ang[1] - 180.0f) - 360.0f
                         : (ang[1] - 180.0f) < 0.0f ? (ang[1] - 180.0f) + 360.0f : (ang[1] - 180.0f)) * -1.0f;
    obj->unk40->unk2C = ang[2] / 100.0f;
}

void func_ovl0A_02_80043C38(void) {
    func_ovl0A_02_80047B68(60);
    while (1) {
        func_ovl0A_02_80047B48(func_ovl0A_02_80043E68, NULL, 0, 0, 0x150);
        func_ovl0A_02_80047B68(func_ovl0A_02_80047D08(40) + 60);
    }
}

void func_ovl0A_02_80043938(void) {
    s32 task;

    func_ovl0A_02_80047B48(func_ovl0A_02_80043070, NULL, 0, 0, 0x150);
    task = func_ovl0A_02_80047B48(func_ovl0A_02_80043C38, NULL, 0, 0, 0x150);
    func_ovl0A_02_80047238(func_ovl0A_02_800471D8())->unk40->unk20 = 180.0f;
    func_ovl0A_02_800471E8(1);
    func_ovl0A_02_80047288(func_ovl0A_02_800471D8(), 0xB);
    func_ovl0A_02_80047BA8(D_ovl0A_02_80048540);
    func_ovl0A_02_80047BA8(D_ovl0A_02_80048544);
    while (!func_ovl0A_02_80047DD0(0x400)) {
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047B68(30);
    func_ovl0A_02_800438FC();
    func_ovl0A_02_80047B68(30);
    func_ovl0A_02_80047220(0x10000);
    func_ovl0A_02_80047B68(60);
    func_ovl0A_02_80047288(func_ovl0A_02_800471D8(), 0);
    func_ovl0A_02_80047B68(60);
    func_ovl0A_02_80047DC0(0x402);
    func_ovl0A_02_800471F8(0x20, 3, 8.5f, 1, 1, 1, 0);
    func_ovl0A_02_80047288(func_ovl0A_02_800471D8(), 0xB);
    func_ovl0A_02_80047B68(120);
    func_ovl0A_02_80047220(0x10000);
    func_ovl0A_02_80047B68(60);
    func_ovl0A_02_80047288(func_ovl0A_02_800471D8(), 0);
    func_ovl0A_02_800471F8(0xE0, 3, 8.5f, 0, 1, 1, 0);
    func_ovl0A_02_80047B50(task);
    func_ovl0A_02_80047B68(50);
    func_ovl0A_02_80047788(0x34C, 4, 0x12C);
    func_ovl0A_02_80047168(1);
    func_ovl0A_02_80047160(0);
    func_ovl0A_02_80047BC0(0x110, 0x150);
    func_ovl0A_02_80047B48(func_ovl0A_02_80043C38, NULL, 0, 0, 0x150);
    func_ovl0A_02_80047DC0(0x403);
    func_ovl0A_02_80047B68(150);
    func_ovl0A_02_800471F8(0x40, 3, 8.5f, 0, 1, 1, 0);
    func_ovl0A_02_80047B68(20);
    func_ovl0A_02_80047220(0x200000);
    func_ovl0A_02_80047B68(40);
    func_ovl0A_02_800471F8(0x40, 3, 8.5f, 7, 1, 1, 0);
    func_ovl0A_02_80047B68(120);
    func_ovl0A_02_80047198(0x40);
    if (!(*D_ovl0A_02_8004857C & 4)) {
        func_ovl0A_02_800470F0(0x21, 0x13, 4);
    } else {
        func_ovl0A_02_800470F0(0x20, 0x11, 4);
    }
    func_ovl0A_02_80047B58();
}

void func_ovl0A_02_800438FC(void) {
    func_ovl0A_02_80047E48(0, 0, 0, 0.0f);
    func_ovl0A_02_80047E28(1);
    func_ovl0A_02_80047E40();
}

void func_ovl0A_02_80043070(void) {
    static f32 D_ovl0A_02_800483E4[3] = { 1600.0f, -200.0f, -50.0f };
    static f32 D_ovl0A_02_800483F0[3] = { 780.0f, 250.0f, -50.0f };
    Obj02 *obj;
    f32 r;
    f32 t;
    f32 step;
    f32 n;
    f32 x; /* unused: its slot sets the frame */
    f32 da;
    f32 db;
    f32 d[3];
    f32 pos[3];
    f32 sph[3];
    f32 ang[3];

    func_ovl0A_02_80047238(func_ovl0A_02_800471D8());
    obj = func_ovl0A_02_80047A20(0x328, 0x01000004, 0xD0, NULL);
    func_ovl0A_02_80047A30(obj);
    func_ovl0A_02_80047720(obj->unk40, 0x16, 0);
    func_ovl0A_02_80043068(obj);
    if (!D_ovl0A_02_800483E4 && !D_ovl0A_02_800483E4 && !D_ovl0A_02_800483E4) { /* fake */
    }
    func_ovl0A_02_80047AD0(D_ovl0A_02_800483E4, obj);
    func_ovl0A_02_80047AC8(obj, pos);
    func_ovl0A_02_80047AC8(obj, obj->unk58);
    while (!func_ovl0A_02_80047DD0(0x402)) {
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047988(D_ovl0A_02_800483E4, D_ovl0A_02_800483F0, sph);
    sph[1] = (((sph[1] - 90.0f) >= 360.0f) ? (sph[1] - 90.0f) - 360.0f : ((sph[1] - 90.0f) < 0.0f) ? (sph[1] - 90.0f) + 360.0f : (sph[1] - 90.0f));
    n = 30.0f;
    r = sph[2] / (n * 0.5f);
    step = (r / n) * -1.0f;
    func_ovl0A_02_800480D0(0x2D7);
    for (t = 0.0f; t < n; t += 1.0f) {
        if (r < 10.0f) {
            step = 0.0f;
            break;
        }
        sph[2] = r;
        r += step;
        func_ovl0A_02_80047990(sph, d);
        pos[0] += d[0];
        pos[1] += d[1];
        pos[2] += d[2];
        func_ovl0A_02_80047AD0(pos, obj);
        func_ovl0A_02_80047988(obj->unk58, pos, ang);
        ang[1] = (((ang[1] - 90.0f) >= 360.0f) ? (ang[1] - 90.0f) - 360.0f : ((ang[1] - 90.0f) < 0.0f) ? (ang[1] - 90.0f) + 360.0f : (ang[1] - 90.0f)) * -1.0f;
        obj->unk40->unk20 = ang[0];
        obj->unk40->unk1C = ang[1];
        func_ovl0A_02_80047B90();
    }
    da = (45.0f - sph[0]) / n;
    db = (0.0f - sph[1]) / n;
    for (t = 0.0f; t < n; t += 1.0f) {
        sph[0] += da;
        sph[1] += db;
        sph[2] = r;
        r += step;
        func_ovl0A_02_80047990(sph, d);
        pos[0] += d[0];
        pos[1] += d[1];
        pos[2] += d[2];
        func_ovl0A_02_80047AD0(pos, obj);
        func_ovl0A_02_80047988(obj->unk58, pos, ang);
        ang[1] = (((ang[1] - 90.0f) >= 360.0f) ? (ang[1] - 90.0f) - 360.0f : ((ang[1] - 90.0f) < 0.0f) ? (ang[1] - 90.0f) + 360.0f : (ang[1] - 90.0f)) * -1.0f;
        obj->unk40->unk20 = ang[0];
        obj->unk40->unk1C = ang[1];
        func_ovl0A_02_80047B90();
    }
    r = 0.0f;
    obj->unk40->unk20 = 45.0f;
    sph[0] = obj->unk40->unk20;
    obj->unk40->unk1C = 0.0f;
    sph[1] = obj->unk40->unk1C;
    func_ovl0A_02_800480D0(0x2D8);
    while (obj->unk40->unk48->unk4->unk4 > 0.0f) {
        func_ovl0A_02_80047B90();
        obj->unk40->unk48->unk4->unk4 -= 1.0f;
    }
    obj->unk40->unk48->unk4->unk4 = 0.0f;
    while (!func_ovl0A_02_80047DD0(0x403)) {
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_800480D0(0x2D8);
    func_ovl0A_02_800479F8(obj, 0x04000000);
    func_ovl0A_02_80043010(obj);
    da = (90.0f - sph[0]) / n;
    db = (8.0f - sph[1]) / n;
    func_ovl0A_02_800480D0(0x2D9);
    step = 2.0f;
    for (t = 0.0f; t < n; t += 1.0f) {
        sph[0] += da;
        sph[1] += db;
        sph[2] = r;
        r += step;
        func_ovl0A_02_80047990(sph, d);
        pos[0] += d[0];
        pos[1] += d[1];
        pos[2] += d[2];
        func_ovl0A_02_80047AD0(pos, obj);
        func_ovl0A_02_80047988(obj->unk58, pos, ang);
        if (ang[2] > 2.0f) {
            ang[1] = (((ang[1] - 90.0f) >= 360.0f) ? (ang[1] - 90.0f) - 360.0f : ((ang[1] - 90.0f) < 0.0f) ? (ang[1] - 90.0f) + 360.0f : (ang[1] - 90.0f)) * -1.0f;
            obj->unk40->unk20 = ang[0];
            obj->unk40->unk1C = ang[1];
        }
        func_ovl0A_02_80047B90();
    }
    step = 0.0f;
    n = 120.0f;
    for (t = 0.0f; t < n; t += 1.0f) {
        sph[2] = r;
        r += step;
        func_ovl0A_02_80047990(sph, d);
        pos[0] += d[0];
        pos[1] += d[1];
        pos[2] += d[2];
        func_ovl0A_02_80047AD0(pos, obj);
        func_ovl0A_02_80047988(obj->unk58, pos, ang);
        ang[1] = (((ang[1] - 90.0f) >= 360.0f) ? (ang[1] - 90.0f) - 360.0f : ((ang[1] - 90.0f) < 0.0f) ? (ang[1] - 90.0f) + 360.0f : (ang[1] - 90.0f)) * -1.0f;
        obj->unk40->unk20 = ang[0];
        obj->unk40->unk1C = ang[1];
        func_ovl0A_02_80047B90();
    }
    func_ovl0A_02_80047A10(obj);
    func_ovl0A_02_80047B58();
}

static void func_ovl0A_02_80043068(Obj02 *obj) {
    obj->unk40->unk48->unk4->unk4 = func_ovl0A_02_80047738(obj->unk40, 0) - 0.001f;
}

/* Waits for the object's animation to end; IDO passes obj in s0. */
static void func_ovl0A_02_80043010(Obj02 *obj) {
    while (!(obj->unk40->unkC & 0x40)) {
        func_ovl0A_02_80047B90();
    }
}

