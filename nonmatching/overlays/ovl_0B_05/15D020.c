/*
 * NON_MATCHING: ovl_0B_05's game object (a menu of four options with a
 * level number, over ovl_0A_04's scene), complete: every function and its
 * data (.data 0x140, .rodata 0xE0, .bss 0xA0, as the original). Not built
 * into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 11, eu 11, jp 11
 *
 * IDO -O3: the functions are written last to first. The scene
 * (800439B0-80043CE8, the two shadow tasks 80044094/8004431C, 800448C8 and
 * 80044C70-80044D48) is ovl_0A_04's code; the fade (8004669C and its two
 * statics) and the tail are ovl_0B_01's. The handler's callees are statics
 * (they keep the handler's $s0-$s3 and $fs0, and two take their argument in
 * $s0/$s1), so they are defined below it and come out before 800439B0;
 * the scene's globals are defined above the handler for the same reason.
 * The two fades are called once each: a dead caller apiece among the end
 * stubs keeps them from being inlined. The empty statics stand for the
 * stubs at 80043010, 80043190, 800439A8 and 800444F0; the unused ones at
 * the end come out in source order around the display-list callback.
 * tools/nonmatching.py doesn't see the statics before 800439B0 (no symbol
 * before them); a whole-object diff shows they match.
 *
 * What still differs in us (words):
 * - func_ovl0B_05_80044DD8 (static, counted with 80044D48): as in
 *   ovl_0B_01's 8004464C, the original takes &D_ovl0B_05_8004669C before
 *   storing arg0 to its home slot, and leaves the final store out of the
 *   delay slot of `jr ra`.
 */
#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} UnkStruct_ovl0B_05_Anim2;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_ovl0B_05_Anim2 *unk4;
} UnkStruct_ovl0B_05_Anim;

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
    /* 0x48 */ UnkStruct_ovl0B_05_Anim *unk48;
} UnkStruct_ovl0B_05_80045D30_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x1C];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[0x14];
    /* 0x40 */ UnkStruct_ovl0B_05_80045D30_Inner *unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
} UnkStruct_ovl0B_05_80045D30;

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
} UnkStruct_ovl0B_05_80045EE0;

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0B_05_80044E78_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl0B_05_80044E78_Inner *unk40;
} UnkStruct_ovl0B_05_80044E78;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl0B_05_800466F0;

typedef UnkStruct_ovl0B_05_80045D30 Obj04;

typedef struct {
    u32 w0;
    u32 w1;
} Gfx_ovl0B_05;

/* The fade at D_ovl0B_05_8004669C (ovl_0B_01's D_ovl0B_01_80045E34). */
typedef struct {
    /* 0x00 */ UnkStructA_40 *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ void (*unk40)(s32, Gfx_ovl0B_05 **);
} UnkStruct_ovl0B_05_8004669C;

/* The menu's items (func_ovl0B_05_80046180's table). */
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
} UnkStruct_ovl0B_05_80046674;

/* What func_ovl0B_05_800453F8 (ZeroJump 0x0F0B) returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x3C];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44[4];
    /* 0x48 */ s32 unk48;
} UnkStruct_ovl0B_05_80046820;

s32 func_ovl0B_05_80044F70(u8 *, const char *, s32); /* 0x0101 */
void func_ovl0B_05_800452A8(s32); /* 0x0C00 */
void func_ovl0B_05_800453A0(s32, s32, s32); /* 0x0F00 */
UnkStruct_ovl0B_05_80046820 *func_ovl0B_05_800453F8(void); /* 0x0F0B */
void func_ovl0B_05_80045410(s32); /* 0x0F0E */
void func_ovl0B_05_80045990(UnkStructA_40 *); /* 0x1501 */
void func_ovl0B_05_800459B0(UnkStruct_ovl0B_05_80045D30_Inner *, s32); /* 0x1505 */
void func_ovl0B_05_800459B8(UnkStruct_ovl0B_05_80045D30_Inner *, s32, s32, s32); /* 0x1506 */
UnkStructA_40 *func_ovl0B_05_80045A08(void (*)(s32, Gfx_ovl0B_05 **), s32); /* 0x1510 */
s32 func_ovl0B_05_80045A18(UnkStruct_ovl0B_05_80045D30_Inner *, s32); /* 0x1512 */
void func_ovl0B_05_80045A20(s32, s32, s32); /* 0x1513 */
void func_ovl0B_05_80045AD8(s32); /* 0x1702 */
void func_ovl0B_05_80045AE8(f32, f32, f32); /* 0x1704 */
void func_ovl0B_05_80045B08(f32, f32, f32); /* 0x1708 */
void func_ovl0B_05_80045B10(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0B_05_80045B50(s32); /* 0x1711 */
void func_ovl0B_05_80045CA8(Obj04 *, s32); /* 0x1811 */
void func_ovl0B_05_80045CB0(Obj04 *, s32); /* 0x1812 */
Obj04 *func_ovl0B_05_80045CD0(s32, s32, s32, Obj04 *); /* 0x1816 */
s32 func_ovl0B_05_80045DF8(void (*)(), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0B_05_80045E08(void); /* 0x1902 */
void func_ovl0B_05_80045E18(s32); /* 0x1904 */
Obj04 *func_ovl0B_05_80045E20(void); /* 0x1905 */
s32 func_ovl0B_05_80045E40(void); /* 0x1909 */
UnkStruct_ovl0B_05_80045EE0 *func_ovl0B_05_80045E80(s32); /* 0x1A00 */
void func_ovl0B_05_80045E90(UnkStruct_ovl0B_05_80045EE0 *, s32); /* 0x1A02 */
void func_ovl0B_05_80046140(s32); /* 0x2200 */
void func_ovl0B_05_80046148(s32, s32, s32); /* 0x2201 */
UnkStructA_40 *func_ovl0B_05_80046180(s32 (*)(u8, u16), void *, s32, s32, s32); /* 0x2400 */
void func_ovl0B_05_80046198(void); /* 0x2403 */
void func_ovl0B_05_800461A0(void); /* 0x2404 */
void func_ovl0B_05_800461A8(u8); /* 0x2405 */
void func_ovl0B_05_800461E8(s32); /* 0x2502 */
void func_ovl0B_05_800461F0(s32, u8 *, s32); /* 0x2503 */
s32 func_ovl0B_05_80046238(u8 *, u16, u16, f32, f32, s32); /* 0x250C */
void func_ovl0B_05_80046240(s32, u8 *, s32); /* 0x250D */
s32 func_ovl0B_05_80046380(s32); /* 0x2B00 */
void func_ovl0B_05_80046388(void); /* 0x2B01 */
void func_ovl0B_05_80046390(s32); /* 0x2B02 */
void func_ovl0B_05_80046398(void); /* 0x2B03 */
void func_ovl0B_05_800463A0(s32, s32, s32, s32); /* 0x2B04 */
void func_ovl0B_05_800463F0(u8); /* 0x2B0E */
s32 func_ovl0B_05_800464E8(s32); /* 0x2F0F */

/* .bss */
u8 D_ovl0B_05_800467C0[0x24]; /* not referenced here */
s32 D_ovl0B_05_800467E4;
s32 D_ovl0B_05_800467E8;
u8 D_ovl0B_05_800467EC[4]; /* not referenced here */
Vec3f_ovl0B_05_800466F0 D_ovl0B_05_800467F0;
UnkStruct_ovl0B_05_80045EE0 *D_ovl0B_05_800467FC;
s32 D_ovl0B_05_80046800;
s32 D_ovl0B_05_80046804;
Obj04 *D_ovl0B_05_80046808[6];
UnkStruct_ovl0B_05_80046820 *D_ovl0B_05_80046820;
u8 D_ovl0B_05_80046824[4]; /* not referenced here */
s32 D_ovl0B_05_80046828[8];
s32 D_ovl0B_05_80046848[4];
s32 D_ovl0B_05_80046858[2];

static void func_ovl0B_05_80044DD8(s32 arg0, Gfx_ovl0B_05 **arg1);

/* .data */
u8 D_ovl0B_05_800465A0[12] = "(IMBHGL";
u8 D_ovl0B_05_800465AC[] = ",HNG=";
u8 D_ovl0B_05_800465B4[] = ",M>K>H";
u8 D_ovl0B_05_800465BC[] = "&HGH";
u8 D_ovl0B_05_800465C4[] = "&NLB<";
u8 D_ovl0B_05_800465CC[] = "\x10\x10";
u8 D_ovl0B_05_800465D0[] = "-AKHP\xFF\x0F\x0F\x1B" "HF;L";
u8 D_ovl0B_05_800465E0[] = "\x1C" "HGMKHE\xFF\x0F\x0F\x0F\x0F\x0F,MB<D";
u8 D_ovl0B_05_800465F4[] = "\x1B\x0F\x1BNMMHG";
u8 D_ovl0B_05_80046600[] = "\xF7\xF7\xF7\xF7";
u8 D_ovl0B_05_80046608[] = "/B>P";
u8 D_ovl0B_05_80046610[12] = "\x1C" "K>=BML";
u8 D_ovl0B_05_8004661C[] = "\x1FNEE\xFF\x0F\x0F)HP>K";
u8 D_ovl0B_05_8004662C[] = "(G";
u8 D_ovl0B_05_80046630[8] = "(\x3F\x3F";
u8 D_ovl0B_05_80046638[] = ")K>LL\x0F,-\x1A+-\x0FMH\x0F,>E><M";
s32 D_ovl0B_05_80046650 = 0;
s32 D_ovl0B_05_80046654 = 0;
s32 D_ovl0B_05_80046658 = 0;
s32 D_ovl0B_05_8004665C = 0;
s32 D_ovl0B_05_80046660 = 0;
s32 D_ovl0B_05_80046664 = 0;
s32 D_ovl0B_05_80046668 = 0;
u8 *D_ovl0B_05_8004666C[2] = { D_ovl0B_05_800465B4, D_ovl0B_05_800465BC };
UnkStruct_ovl0B_05_80046674 D_ovl0B_05_80046674[5] = {
    { 0xA2, 0x4D, 0x02, 0x00, 0x00, 0x00 },
    { 0xA2, 0x67, 0x01, 0x03, 0x00, 0x00 },
    { 0xA2, 0x81, 0x02, 0x00, 0x03, 0x03 },
    { 0xA2, 0x9B, 0x03, 0x00, 0x00, 0x00 },
    { 0xA2, 0xB5, 0x04, 0x00, 0x00, 0x00 },
};
UnkStruct_ovl0B_05_8004669C D_ovl0B_05_8004669C = {
    NULL, 0x32, 0x32, 0x32, 0x8C, 0.0f, 100.0f, 1.0f, 1.0f, 0x82, 0x82, 0xA0, 0x78, 0.0f, 0x5D, 0x80,
    func_ovl0B_05_80044DD8,
};

static void func_ovl0B_05_80043018(UnkStruct_ovl0B_05_8004669C *arg0);
static void func_ovl0B_05_80043904(UnkStruct_ovl0B_05_8004669C *arg0);
void func_ovl0B_05_80044094(void);
void func_ovl0B_05_8004431C(void);
void func_ovl0B_05_800444F8(void);
s32 func_ovl0B_05_800445F4(u8 arg0, u16 arg1);
static void func_ovl0B_05_80043198(s32 arg0);
static void func_ovl0B_05_80043254(s32 arg0);
static void func_ovl0B_05_800432F4(void);
static s32 func_ovl0B_05_8004335C(void);
static void func_ovl0B_05_800433AC(s32 arg0);
void func_ovl0B_05_800439B0(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0B_05_80043A2C(void);
Obj04 *func_ovl0B_05_80043A94(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_ovl0B_05_80043B6C(void);
void func_ovl0B_05_80043CE8(void);
static void func_ovl0B_05_80043010(void);
static void func_ovl0B_05_800430A4(s32 arg0);
static void func_ovl0B_05_80043190(void);
static void func_ovl0B_05_80043438(s32 arg0);
static void func_ovl0B_05_800439A8(void);
static void func_ovl0B_05_800444F0(void);

static void func_ovl0B_05_80044DD0(void) {
}

static void func_ovl0B_05_80044DC8(void) {
}

static void func_ovl0B_05_80044DC0(void) {
}

static void func_ovl0B_05_80044DB8(void) {
}

static void func_ovl0B_05_80044DB0(void) {
}

static void func_ovl0B_05_80044DA8(void) {
}

static void func_ovl0B_05_80044DA0(void) {
}

static void func_ovl0B_05_80044D98(void) {
}

static void func_ovl0B_05_80044D90(void) {
}

static void func_ovl0B_05_80044D88(void) {
}

static void func_ovl0B_05_80044D80(void) {
}

static void func_ovl0B_05_80044D78(void) {
}

/* fakes: a second (dead) caller keeps each fade from being inlined into
 * its only real one */
static void func_ovl0B_05_80044D70(void) {
    func_ovl0B_05_80043904(&D_ovl0B_05_8004669C);
}

static void func_ovl0B_05_80044D68(void) {
    func_ovl0B_05_80043018(&D_ovl0B_05_8004669C);
}

/* unused: refers to the .bss nothing else uses, which would otherwise be
 * common */
static void func_ovl0B_05_80044D60(void) {
    D_ovl0B_05_800467C0[0] = D_ovl0B_05_800467EC[0] + D_ovl0B_05_80046824[0];
}

static void func_ovl0B_05_80044DD8(s32 arg0, Gfx_ovl0B_05 **arg1) {
    UnkStruct_ovl0B_05_8004669C *fade = &D_ovl0B_05_8004669C;
    Gfx_ovl0B_05 *gfx = *arg1;

    { Gfx_ovl0B_05 *g = gfx++; g->w0 = 0xFA000000; g->w1 = ((fade->unk4 & 0xFF) << 24) | ((fade->unk8 & 0xFF) << 16) | ((fade->unkC & 0xFF) << 8) | (fade->unk10 & 0xFF); }
    { Gfx_ovl0B_05 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFDF6FB; }
    { Gfx_ovl0B_05 *g = gfx++; g->w0 = 0xF7000000; g->w1 = 0x10001; }
    { Gfx_ovl0B_05 *g = gfx++; g->w0 = 0xF6000000 | (((fade->unk2C + (s32) fade->unk34) & 0x3FF) << 14) | (((fade->unk30 + (s32) (fade->unk34 * fade->unk20)) & 0x3FF) << 2); g->w1 = (((fade->unk2C - (s32) fade->unk34) & 0x3FF) << 14) | (((fade->unk30 - (s32) (fade->unk34 * fade->unk20)) & 0x3FF) << 2); }
    *arg1 = gfx;
}

static void func_ovl0B_05_80044F54(void) {
}

static void func_ovl0B_05_80044F4C(void) {
}


void func_ovl0B_05_80044D48(void) {
    D_ovl0B_05_800467E4 = -1;
    D_ovl0B_05_800467E8 = -1;
}

void func_ovl0B_05_80044CEC(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0B_05_80045AE8(D_ovl0B_05_800467F0.x, D_ovl0B_05_800467F0.y, D_ovl0B_05_800467F0.z);
    func_ovl0B_05_80045B08(arg0, arg1, arg2);
    func_ovl0B_05_80045E18(0xB4);
}

void func_ovl0B_05_80044CA4(f32 arg0) {
    f32 sp1C;

    func_ovl0B_05_80045B10(&sp1C, NULL, NULL);
    func_ovl0B_05_80045B08(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0B_05_80044C70(s32 arg0, UnkStruct_ovl0B_05_80044E78 *arg1) {
    UnkStruct_ovl0B_05_80044E78_Inner *p;

    p = arg1->unk40;
    func_ovl0B_05_800463A0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0B_05_800448C8(Obj04 **arg0, s32 *arg1, Obj04 **arg2, s32 *arg3, Obj04 **arg4, s32 *arg5, s32 arg6) {
    s32 i;

    *arg0 = func_ovl0B_05_80045CD0(0x27, 0x01000000, 0xD0, NULL);
    (*arg0)->unk40->unk10 = 1000.0f;
    (*arg0)->unk40->unk14 = 50.0f;
    (*arg0)->unk40->unk18 = -650.0f;
    (*arg0)->unk40->unk30 = 0.5f;
    (*arg0)->unk40->unk28 = (*arg0)->unk40->unk2C = (*arg0)->unk40->unk30;
    (*arg0)->unk40->unk20 = 345.0f;
    *arg1 = func_ovl0B_05_80045A18((*arg0)->unk40, 0x19);
    for (i = 0; i < 0x19; i++) {
        if (i == 0x10 || i == 0x11 || i == 0x12 || i == 0x13) {
            func_ovl0B_05_80045A20(*arg1, i, 0x4F);
        }
    }
    if (arg6 != 0) {
        func_ovl0B_05_80045A20(*arg1, 0xF, 0x4F);
        func_ovl0B_05_80045A20(*arg1, 0xD, 0x4F);
        func_ovl0B_05_80045A20(*arg1, 0xC, 0x4F);
        func_ovl0B_05_80045A20(*arg1, 0xB, 0x4F);
        func_ovl0B_05_80045A20(*arg1, 0xE, 0x4F);
        func_ovl0B_05_80045A20(*arg1, 5, 0x4F);
        func_ovl0B_05_80045A20(*arg1, 2, 0x4F);
        func_ovl0B_05_80045A20(*arg1, 4, 0x4F);
        func_ovl0B_05_80045A20(*arg1, 3, 0x4F);
        *arg2 = func_ovl0B_05_80045CD0(0x27, 0x01400000, 0xD0, *arg0);
        *arg3 = func_ovl0B_05_80045A18((*arg2)->unk40, 0x19);
        for (i = 0; i < 0x19; i++) {
            switch (i) {
                case 0xB:
                case 0xC:
                case 0xD:
                case 0xE:
                case 0xF:
                    break;
                default:
                    func_ovl0B_05_80045A20(*arg3, i, 0x4F);
                    break;
            }
        }
        if (arg6 >= 2) {
            *arg4 = func_ovl0B_05_80045CD0(0x27, 0x01400000, 0xD0, *arg0);
            *arg5 = func_ovl0B_05_80045A18((*arg4)->unk40, 0x19);
            for (i = 0; i < 0x19; i++) {
                switch (i) {
                    case 0x10:
                    case 0x11:
                    case 0x12:
                    case 0x13:
                        break;
                    default:
                        func_ovl0B_05_80045A20(*arg5, i, 0x4F);
                        break;
                }
            }
        }
    }
    if (arg6 != 0) {
        D_ovl0B_05_80046800 = func_ovl0B_05_80045DF8(func_ovl0B_05_8004431C, *arg2, 0, 0, 0x150);
    } else {
        D_ovl0B_05_80046800 = func_ovl0B_05_80045DF8(func_ovl0B_05_8004431C, *arg0, 0, 0, 0x150);
    }
    D_ovl0B_05_80046804 = func_ovl0B_05_80045DF8(func_ovl0B_05_80044094, *arg0, 0, 0, 0x150);
}


/* The menu's callback: arg0 the item, arg1 the buttons. */
s32 func_ovl0B_05_800445F4(u8 arg0, u16 arg1) {
    u8 ret = 1;
    s32 changed;

    if (arg1 & 6) {
        func_ovl0B_05_80046398();
        if (arg1 & 2) {
            func_ovl0B_05_80046380(2);
            D_ovl0B_05_80046650 = 0;
        } else {
            func_ovl0B_05_80046380(1);
            D_ovl0B_05_80046650 = 1;
        }
        return 0;
    }
    switch (arg0) {
        case 1:
            if (arg1 & 0x180) {
                changed = 0;
                if (D_ovl0B_05_80046668 == 0 && (arg1 & 0x100)) {
                    D_ovl0B_05_80046668 = 1;
                    changed = 1;
                } else if (D_ovl0B_05_80046668 == 1 && (arg1 & 0x80)) {
                    D_ovl0B_05_80046668 = 0;
                    changed = 1;
                }
                if (changed) {
                    func_ovl0B_05_800463F0(D_ovl0B_05_80046668);
                    func_ovl0B_05_800432F4();
                    func_ovl0B_05_80046380(0);
                }
            }
            break;
        case 2:
            if ((D_ovl0B_05_80046664 == 0 && (arg1 & 0x100)) || (D_ovl0B_05_80046664 == 1 && (arg1 & 0x80))) {
                func_ovl0B_05_80046380(0);
                func_ovl0B_05_80043254(1);
            }
            break;
        case 3:
            if (arg1 & 0x80) {
                if (D_ovl0B_05_80046654 == 0) {
                    D_ovl0B_05_80046654 = 46;
                } else {
                    D_ovl0B_05_80046654--;
                }
                func_ovl0B_05_800433AC(0);
            } else if (arg1 & 0x100) {
                if (D_ovl0B_05_80046654 == 46) {
                    D_ovl0B_05_80046654 = 0;
                } else {
                    D_ovl0B_05_80046654++;
                }
                func_ovl0B_05_800433AC(0);
            }
            if (arg1 & 1) {
                func_ovl0B_05_800433AC(1);
                if (func_ovl0B_05_8004335C()) {
                    func_ovl0B_05_80046390(D_ovl0B_05_80046654);
                }
            }
            break;
        case 4:
            if (arg1 & 1) {
                func_ovl0B_05_80046240(D_ovl0B_05_80046848[1], D_ovl0B_05_80046610, 2);
                func_ovl0B_05_800453A0(0x1C, 0x10, 0);
                func_ovl0B_05_80046388();
                func_ovl0B_05_80046380(1);
                ret = 0;
            }
            break;
        case 5:
            if ((D_ovl0B_05_80046660 == 0 && (arg1 & 0x100)) || (D_ovl0B_05_80046660 == 1 && (arg1 & 0x80))) {
                func_ovl0B_05_80046380(0);
                func_ovl0B_05_80043198(1);
            }
            break;
    }
    return ret;
}

void func_ovl0B_05_800444F8(void) {
    func_ovl0B_05_800444F0();
    if (D_ovl0B_05_80046658 == 0) {
        D_ovl0B_05_80046674[1].unk5 = 0;
    } else {
        D_ovl0B_05_80046674[1].unk5 = 3;
    }
    switch (D_ovl0B_05_8004665C) {
        case 0:
            D_ovl0B_05_80046674[2].unk5 = 0;
            break;
        case 1:
            D_ovl0B_05_80046674[2].unk5 = 4;
            D_ovl0B_05_80046674[3].unk5 = 0;
            break;
        case 2:
            D_ovl0B_05_80046674[2].unk5 = 5;
            D_ovl0B_05_80046674[4].unk4 = 3;
            break;
        case 3:
            D_ovl0B_05_80046674[2].unk5 = 4;
            D_ovl0B_05_80046674[3].unk5 = 5;
            D_ovl0B_05_80046674[4].unk4 = 4;
            break;
    }
    func_ovl0B_05_80046180(func_ovl0B_05_800445F4, D_ovl0B_05_80046674, 0x130, 0xF, 0xF);
    func_ovl0B_05_800461A8(1);
    func_ovl0B_05_800461A0();
    func_ovl0B_05_80046198();
    func_ovl0B_05_800453A0(0x20, 0x11, 0);
    func_ovl0B_05_80045E08();
}

static void func_ovl0B_05_800444F0(void) {
}

void func_ovl0B_05_8004431C(void) {
    Obj04 *self;
    Obj04 *obj;
    f32 d;
    f32 s;

    self = func_ovl0B_05_80045E20();
    obj = func_ovl0B_05_80045CD0(0x34D, 0x01080000, 0xD0, NULL);
    obj->unk40->unk36 = 0x7F;
    obj->unk40->unk10 = 1000.0f;
    obj->unk40->unk14 = -100.0f;
    obj->unk40->unk18 = -650.0f;
    obj->unk40->unk20 = self->unk40->unk20;
    func_ovl0B_05_80045E18(4);
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
            func_ovl0B_05_80045CA8(obj, 0x01000000);
        } else {
            func_ovl0B_05_80045CB0(obj, 0x01000000);
        }
        func_ovl0B_05_80045E40();
    }
}

void func_ovl0B_05_80044094(void) {
    Obj04 *self;
    Obj04 *obj;
    Obj04 *parts[4];
    s32 i;
    f32 d;
    f32 s;

    self = func_ovl0B_05_80045E20();
    obj = func_ovl0B_05_80045CD0(-1, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = 1000.0f;
    obj->unk40->unk14 = -100.0f;
    obj->unk40->unk18 = -650.0f;
    obj->unk40->unk20 = self->unk40->unk20;
    for (i = 0; i < 4; i++) {
        parts[i] = func_ovl0B_05_80045CD0(0x34D, 0x01780000, 0xD0, obj);
        parts[i]->unk40->unk36 = 0x7F;
    }
    parts[0]->unk4C = 300.0f;
    parts[1]->unk54 = 300.0f;
    parts[2]->unk4C = -300.0f;
    parts[3]->unk54 = -300.0f;
    func_ovl0B_05_80045E18(4);
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
        func_ovl0B_05_80045E40();
    }
}


void func_ovl0B_05_80043CE8(void) {
    D_ovl0B_05_800467FC = func_ovl0B_05_80045E80(0x33B);
    func_ovl0B_05_80045E90(D_ovl0B_05_800467FC, 0x20000001);
    D_ovl0B_05_800467FC->unk40 = 1.0f;
    D_ovl0B_05_800467FC->unk44 = 1.0f;
    D_ovl0B_05_800467FC->unk28 = 0.0f;
    D_ovl0B_05_800467FC->unk2C = 120.0f;
    D_ovl0B_05_800467FC->unk30 = D_ovl0B_05_800467FC->unk28 + D_ovl0B_05_800467FC->unk48 * 2.0f;
    D_ovl0B_05_800467FC->unk34 = D_ovl0B_05_800467FC->unk2C + D_ovl0B_05_800467FC->unk4C * 2.0f * 0.8f;
    func_ovl0B_05_80046140(1);
    func_ovl0B_05_80046148(0, 0, 0xFF);
    func_ovl0B_05_80045B50(0x7F);
    func_ovl0B_05_80045AE8(1000.0f, 400.0f, 200.0f);
    func_ovl0B_05_80045AD8(1);
    func_ovl0B_05_80045B08(0.0f, 20.0f, 1700.0f);
    func_ovl0B_05_80043B6C();
    func_ovl0B_05_80043A2C();
}

void func_ovl0B_05_80043B6C(void) {
    s32 i;

    i = 0;
    D_ovl0B_05_80046808[i++] = func_ovl0B_05_80043A94(1000.0f, 50.0f, -1150.0f, 13.0f, 2.0f);
    D_ovl0B_05_80046808[i++] = func_ovl0B_05_80043A94(1500.0f, 150.0f, -550.0f, 13.0f, 2.0f);
    D_ovl0B_05_80046808[i++] = func_ovl0B_05_80043A94(1000.0f, 1050.0f, -650.0f, 13.0f, 5.0f);
    D_ovl0B_05_80046808[i++] = func_ovl0B_05_80043A94(500.0f, 1050.0f, -450.0f, 13.0f, 5.0f);
    D_ovl0B_05_80046808[i++] = func_ovl0B_05_80043A94(500.0f, 1050.0f, -250.0f, 13.0f, 4.0f);
    D_ovl0B_05_80046808[i++] = func_ovl0B_05_80043A94(1500.0f, 1050.0f, -1050.0f, 13.0f, 5.0f);
}

Obj04 *func_ovl0B_05_80043A94(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    Obj04 *obj;

    obj = func_ovl0B_05_80045CD0(0x11D, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = arg0;
    obj->unk40->unk14 = arg1;
    obj->unk40->unk18 = arg2;
    obj->unk40->unkC |= 0x8000;
    func_ovl0B_05_800459B0(obj->unk40, 1);
    func_ovl0B_05_800459B8(obj->unk40, 0x11E, 0, 1);
    obj->unk40->unk28 = arg3;
    obj->unk40->unk2C = arg4;
    obj->unk40->unk36 = 0xCC;
    return obj;
}

void func_ovl0B_05_80043A2C(void) {
    func_ovl0B_05_800439B0(500.0f, 0.0f, 400.0f);
    func_ovl0B_05_800439B0(1600.0f, 0.0f, 300.0f);
    func_ovl0B_05_800439B0(500.0f, 0.0f, 700.0f);
    func_ovl0B_05_800439B0(1700.0f, 0.0f, 600.0f);
}

void func_ovl0B_05_800439B0(f32 arg0, f32 arg1, f32 arg2) {
    Obj04 *obj;

    func_ovl0B_05_800439A8();
    obj = func_ovl0B_05_80045CD0(0x97, 0x01000000, 0xD0, NULL);
    obj->unk40->unk10 = arg0;
    obj->unk40->unk14 = arg1;
    obj->unk40->unk18 = arg2;
    func_ovl0B_05_80045CD0(0x98, 0x01480000, 0xD0, obj)->unk40->unk36 = 0x80;
}


/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0B_05_80043E04(s32 arg0) {
    switch (arg0) {
        case 2:
            D_ovl0B_05_80046650 = 0;
            D_ovl0B_05_80046820 = func_ovl0B_05_800453F8();
            func_ovl0B_05_800452A8(0x33A);
            func_ovl0B_05_80043CE8();
            func_ovl0B_05_80045B08(3.2f, 6.2f, 2051.0f);
            D_ovl0B_05_80046654 = 0;
            D_ovl0B_05_8004665C = 0;
            D_ovl0B_05_80046658 = 0;
            D_ovl0B_05_80046660 = D_ovl0B_05_80046820->unk40;
            D_ovl0B_05_80046664 = D_ovl0B_05_80046820->unk48;
            D_ovl0B_05_80046668 = D_ovl0B_05_80046820->unk3C;
            if (func_ovl0B_05_800464E8(0)) {
                D_ovl0B_05_80046658 = 1;
            }
            if (func_ovl0B_05_800464E8(1)) {
                D_ovl0B_05_8004665C |= 2;
            }
            if (func_ovl0B_05_800464E8(2)) {
                D_ovl0B_05_8004665C |= 1;
                D_ovl0B_05_80046658 = 2;
            }
            func_ovl0B_05_80043904(&D_ovl0B_05_8004669C);
            D_ovl0B_05_8004666C[0] = D_ovl0B_05_800465B4;
            D_ovl0B_05_8004666C[1] = D_ovl0B_05_800465BC;
            func_ovl0B_05_80043438(0);
            func_ovl0B_05_80043438(1);
            func_ovl0B_05_80043438(2);
            if (D_ovl0B_05_80046658) {
                func_ovl0B_05_800433AC(0);
            }
            func_ovl0B_05_800432F4();
            func_ovl0B_05_80043254(0);
            func_ovl0B_05_80043198(0);
            break;
        case 5:
            func_ovl0B_05_80045DF8(func_ovl0B_05_800444F8, NULL, 0, 0, 0x130);
            break;
        case 1:
            func_ovl0B_05_800430A4(0);
            func_ovl0B_05_800430A4(1);
            func_ovl0B_05_800430A4(2);
            func_ovl0B_05_80043018(&D_ovl0B_05_8004669C);
            if (D_ovl0B_05_80046650) {
                D_ovl0B_05_80046820->unk3C = D_ovl0B_05_80046668;
                D_ovl0B_05_80046820->unk40 = D_ovl0B_05_80046660;
                D_ovl0B_05_80046820->unk48 = D_ovl0B_05_80046664;
                func_ovl0B_05_800463F0(D_ovl0B_05_80046668);
            }
            break;
        case 3:
            func_ovl0B_05_80045410(0);
            break;
        case 4:
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
    }
}

static void func_ovl0B_05_800439A8(void) {
}

static void func_ovl0B_05_80043904(UnkStruct_ovl0B_05_8004669C *arg0) {
    f32 step = (arg0->unk18 - arg0->unk14) / arg0->unk1C;

    arg0->unk0 = func_ovl0B_05_80045A08(arg0->unk40, arg0->unk38);
    arg0->unk0->unkC |= arg0->unk3C;
    for (arg0->unk34 = arg0->unk14; arg0->unk34 < arg0->unk18; arg0->unk34 += step) {
        func_ovl0B_05_80045E40();
    }
    func_ovl0B_05_80045E40();
}

/* The menu's labels: 0 the items, 1 the options under them, 2 the line at
 * the bottom. */
static void func_ovl0B_05_80043438(s32 arg0) {
    s32 i;

    switch (arg0) {
        case 0:
            i = 0;
            D_ovl0B_05_80046828[i++] = func_ovl0B_05_80046238(D_ovl0B_05_800465A0, 0x73, 0x23, 0.85f, 0.85f, 0);
            D_ovl0B_05_80046828[i++] = func_ovl0B_05_80046238(D_ovl0B_05_800465AC, 0x50, 0x46, 0.6f, 0.6f, 5);
            D_ovl0B_05_80046828[i++] = func_ovl0B_05_80046238(D_ovl0B_05_8004666C[0], 0xAF, 0x46, 0.6f, 0.6f, 1);
            D_ovl0B_05_80046828[i++] = func_ovl0B_05_80046238(D_ovl0B_05_800465D0, 0x50, 0x59, 0.6f, 0.6f, 5);
            D_ovl0B_05_80046828[i++] = func_ovl0B_05_80046238(D_ovl0B_05_800465E0, 0xAF, 0x59, 0.6f, 0.6f, 1);
            switch (D_ovl0B_05_80046658) {
                case 0:
                    D_ovl0B_05_80046828[5] = func_ovl0B_05_80046238(D_ovl0B_05_80046600, 0x50, 0x7A, 0.6f, 0.6f, 5);
                    break;
                case 1:
                case 2:
                    D_ovl0B_05_80046828[5] = func_ovl0B_05_80046238(D_ovl0B_05_800465C4, 0x50, 0x7A, 0.6f, 0.6f, 5);
                    D_ovl0B_05_80046828[6] = func_ovl0B_05_80046238(D_ovl0B_05_800465CC, 0xAF, 0x7A, 0.6f, 0.6f, 1);
                    break;
            }
            break;
        case 1:
            switch (D_ovl0B_05_8004665C) {
                case 0:
                    i = 0;
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046600, 0x50, 0x94, 0.6f, 0.6f, 5);
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046600, 0x50, 0xAE, 0.6f, 0.6f, 5);
                    break;
                case 1:
                    i = 0;
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046608, 0x50, 0x94, 0.6f, 0.6f, 5);
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046610, 0xAF, 0x94, 0.6f, 0.6f, 1);
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046600, 0x50, 0xAE, 0.6f, 0.6f, 5);
                    break;
                case 2:
                    i = 0;
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046600, 0x50, 0x94, 0.6f, 0.6f, 5);
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_8004661C, 0x50, 0xAA, 0.6f, 0.6f, 5);
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046630, 0xAF, 0xAE, 0.6f, 0.6f, 1);
                    break;
                case 3:
                    i = 0;
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046608, 0x50, 0x94, 0.6f, 0.6f, 5);
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046610, 0xAF, 0x94, 0.6f, 0.6f, 1);
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046630, 0xAF, 0xAE, 0.6f, 0.6f, 1);
                    D_ovl0B_05_80046848[i++] = func_ovl0B_05_80046238(D_ovl0B_05_8004661C, 0x50, 0xAA, 0.6f, 0.6f, 5);
                    break;
            }
            break;
        case 2:
            i = 0;
            D_ovl0B_05_80046858[i++] = func_ovl0B_05_80046238(D_ovl0B_05_80046638, 0x3F, 0xCB, 0.6f, 0.6f, 4);
            break;
    }
}

/* The level number's label: arg0 picks its colour. */
static void func_ovl0B_05_800433AC(s32 arg0) {
    u8 buf[12];
    s32 col = 1;

    if (!func_ovl0B_05_8004335C()) {
        D_ovl0B_05_800465CC[0] = 0xF9;
        D_ovl0B_05_800465CC[1] = 0xF9;
    } else {
        func_ovl0B_05_80044F70(buf, "%02d", D_ovl0B_05_80046654);
        D_ovl0B_05_800465CC[0] = buf[0] - 0x20;
        D_ovl0B_05_800465CC[1] = buf[1] - 0x20;
        if (arg0) {
            col = 2;
        }
    }
    func_ovl0B_05_800461F0(D_ovl0B_05_80046828[6], D_ovl0B_05_800465CC, (u8) col);
}

static s32 func_ovl0B_05_8004335C(void) {
    if (D_ovl0B_05_80046658 == 1) {
        if (D_ovl0B_05_80046654 == 8 || D_ovl0B_05_80046654 == 15 || D_ovl0B_05_80046654 == 16 || D_ovl0B_05_80046654 == 44) {
            return 0;
        }
    }
    return 1;
}

static void func_ovl0B_05_800432F4(void) {
    s32 id;

    id = func_ovl0B_05_80046238(D_ovl0B_05_8004666C[D_ovl0B_05_80046668], 0xAF, 0x46, 0.6f, 0.6f, 1);
    func_ovl0B_05_800461E8(D_ovl0B_05_80046828[2]);
    D_ovl0B_05_80046828[2] = id;
}

static void func_ovl0B_05_80043254(s32 arg0) {
    u8 *str;
    u16 y;
    s32 id;

    if (arg0) {
        if (D_ovl0B_05_80046664) {
            D_ovl0B_05_80046664 = 0;
        } else {
            D_ovl0B_05_80046664 = 1;
        }
    }
    if (D_ovl0B_05_80046664) {
        str = D_ovl0B_05_800465F4;
        y = 0x60;
    } else {
        str = D_ovl0B_05_800465E0;
        y = 0x59;
    }
    id = func_ovl0B_05_80046238(str, 0xAF, y, 0.6f, 0.6f, 1);
    func_ovl0B_05_800461E8(D_ovl0B_05_80046828[4]);
    D_ovl0B_05_80046828[4] = id;
}

static void func_ovl0B_05_80043198(s32 arg0) {
    s32 id;

    func_ovl0B_05_80043190();
    if (D_ovl0B_05_8004665C == 2 || D_ovl0B_05_8004665C == 3) {
        if (arg0) {
            if (D_ovl0B_05_80046660) {
                D_ovl0B_05_80046660 = 0;
            } else {
                D_ovl0B_05_80046660 = 1;
            }
        }
        id = func_ovl0B_05_80046238(D_ovl0B_05_80046660 ? D_ovl0B_05_8004662C : D_ovl0B_05_80046630, 0xAF, 0xAE, 0.6f, 0.6f, 1);
        func_ovl0B_05_800461E8(D_ovl0B_05_80046848[2]);
        D_ovl0B_05_80046848[2] = id;
    }
}

static void func_ovl0B_05_80043190(void) {
}

/* Frees the labels of group arg0 (func_ovl0B_05_80043438's). */
static void func_ovl0B_05_800430A4(s32 arg0) {
    s32 i;
    s32 n;
    s32 *ids;

    switch (arg0) {
        case 0:
            n = 7;
            if (!D_ovl0B_05_80046658) {
                n = 6;
            }
            ids = D_ovl0B_05_80046828;
            break;
        case 1:
            switch (D_ovl0B_05_8004665C) {
                case 0:
                    n = 2;
                    break;
                case 1:
                    n = 3;
                    break;
                case 2:
                    n = 3;
                    break;
                case 3:
                    n = 4;
                    break;
            }
            ids = D_ovl0B_05_80046848;
            break;
        case 2:
            n = 1;
            ids = D_ovl0B_05_80046858;
            break;
    }
    for (i = 0; i < n; i++) {
        func_ovl0B_05_800461E8(*ids++);
    }
}

static void func_ovl0B_05_80043018(UnkStruct_ovl0B_05_8004669C *arg0) {
    func_ovl0B_05_80043010();
    for (arg0->unk34 = arg0->unk24; arg0->unk34 > 0.0f; arg0->unk34 -= arg0->unk28) {
        func_ovl0B_05_80045E40();
    }
    func_ovl0B_05_80045990(arg0->unk0);
    func_ovl0B_05_80045E40();
}

static void func_ovl0B_05_80043010(void) {
}
