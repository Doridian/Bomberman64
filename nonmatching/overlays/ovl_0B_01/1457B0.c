/*
 * NON_MATCHING: ovl_0B_01's game object (the title screen: PUSH START, the
 * copyright line, the four-item menu and its cheat-code task), complete:
 * every function and its data (.data 0x110, .rodata 0x70, .bss 0x70, as
 * the original). Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 326, eu 327, jp 416
 *
 * IDO -O3: the functions are written last to first (IDO -O3 emits a file's
 * functions in reverse). The strings, the copyright line and the menu
 * positions are .data objects (their order among the globals says so), so
 * 80043448 and 80043998 copy them as structures. ZeroJump 0x1909 and
 * 0x2B00 are declared s32: as void, 80043148 keeps its temporaries in $v0
 * where the original has $v1. Empty statics stand for the stubs before
 * 800430A4, 80043D64 and 80043DD4.
 *
 * What still differs in us (words):
 * - func_ovl0B_01_8004376C (static, counted with 80043660) and
 *   func_ovl0B_01_80043998: register allocation. The static takes its mode
 *   in $s5 and works in $s0-$s6 unsaved, so the caller keeps sel and
 *   &D_ovl0B_01_80045ED8 in $s7/$fp; ours spreads the static over $s0-$fp
 *   (its second loop keeps &rect[i]/&spr[i] in $s1/$s0, the original in
 *   $a0/$v1), so 80043998's registers all move. Both originals also have
 *   12/16 bytes free above their arrays (ours below); unused locals don't
 *   reproduce it here. 80043998's x offset computes (scale - 1.5f) before
 *   converting xs[sel], ours after.
 * jp has no copyright line (80043448 shows its own picture at once) and no
 * third sprite in the handler (`#if VERSION_JP`); its count also takes
 * func_ovl0B_01_8004464C whole, since the tool finds it in jp but folds
 * it into the stubs before it in us and eu.
 * - func_ovl0B_01_8004464C (counted with 800445BC): the original takes
 *   &D_ovl0B_01_80045E34 before storing arg0 to its home slot, and leaves
 *   the final store out of the delay slot of `jr ra`.
 */
#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
} Gfx_ovl0B_01;

/* The fade at D_ovl0B_01_80045E34: its object, colour, and the rectangle
 * its display list fills. */
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
    /* 0x40 */ void (*unk40)(s32, Gfx_ovl0B_01 **);
} UnkStruct_ovl0B_01_80045E34;

/* The copyright line 80043448 copies to its stack. */
typedef struct {
    u8 s[0x5D];
} UnkStruct_ovl0B_01_80045E78;

/* The menu items' positions 80043998 copies to its stack. */
typedef struct {
    u16 v[4];
} UnkStruct_ovl0B_01_80045EDC;

typedef struct {
    /* 0x00 */ u8 unk0[0x44];
    /* 0x44 */ s32 unk44;
} UnkStruct_ovl0B_01_80044C58;

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0B_01_B04_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl0B_01_B04_Inner *unk40;
} UnkStruct_ovl0B_01_B04;

void func_ovl0B_01_80044C00(s32, s32, s32); /* 0xF00 */
s32 func_ovl0B_01_80044C08(void); /* 0xF01 */
s32 func_ovl0B_01_80044C18(void); /* 0xF03 */
UnkStruct_ovl0B_01_80044C58 *func_ovl0B_01_80044C58(void); /* 0xF0B */
UnkStructA_40 *func_ovl0B_01_800451E8(s32, s32); /* 0x1500 */
void func_ovl0B_01_800451F0(UnkStructA_40 *); /* 0x1501 */
UnkStructA_40 *func_ovl0B_01_80045268(void (*)(s32, Gfx_ovl0B_01 **), s32); /* 0x1510 */
void func_ovl0B_01_80045328(s32); /* 0x1700 */
void func_ovl0B_01_80045338(s32); /* 0x1702 */
void func_ovl0B_01_80045348(f32, f32, f32); /* 0x1704 */
void func_ovl0B_01_80045368(f32, f32, f32); /* 0x1708 */
void func_ovl0B_01_80045370(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0B_01_800453B0(s32); /* 0x1711 */
s32 func_ovl0B_01_80045658(void (*)(void), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0B_01_80045660(s32); /* 0x1901 */
void func_ovl0B_01_80045668(void); /* 0x1902 */
void func_ovl0B_01_80045678(s32); /* 0x1904 */
s32 func_ovl0B_01_800456A0(void); /* 0x1909 */
UnkStructC *func_ovl0B_01_800456E0(s32); /* 0x1A00 */
void func_ovl0B_01_800456F0(UnkStructC *, s32); /* 0x1A02 */
s32 func_ovl0B_01_80045720(s32); /* 0x1B04 */
s32 func_ovl0B_01_80045738(s32); /* 0x1B07 */
void func_ovl0B_01_80045938(s32); /* 0x2000 */
void func_ovl0B_01_80045950(void); /* 0x2003 */
void func_ovl0B_01_800459A8(s32, s32, s32); /* 0x2201 */
UnkStructA_40 *func_ovl0B_01_800459E0(s32 (*)(u8, u16), void *, s32, s32, s32); /* 0x2400 */
void func_ovl0B_01_800459F8(void); /* 0x2403 */
void func_ovl0B_01_80045A00(void); /* 0x2404 */
void func_ovl0B_01_80045A08(u8); /* 0x2405 */
void func_ovl0B_01_80045A48(s32); /* 0x2502 */
void func_ovl0B_01_80045A58(s32, u16, u16); /* 0x2504 */
void func_ovl0B_01_80045A68(s32, f32, f32); /* 0x2506 */
UnkStructA_40 *func_ovl0B_01_80045A78(s32); /* 0x2508 */
s32 func_ovl0B_01_80045A98(u8 *, u16, u16, f32, f32, s32); /* 0x250C */
s32 func_ovl0B_01_80045BE0(s32); /* 0x2B00 */
void func_ovl0B_01_80045C00(s32, s32, s32, s32); /* 0x2B04 */
void func_ovl0B_01_80045D88(void); /* 0x3102 */
void func_ovl0B_01_80045DE0(void); /* 0x310D */
void func_ovl0B_01_80045DF0(s32); /* 0x310F */

/* .bss */
u8 D_ovl0B_01_80045F80[0x24];
s32 D_ovl0B_01_80045FA4;
s32 D_ovl0B_01_80045FA8;
u8 D_ovl0B_01_80045FAC[4];
Vec3f D_ovl0B_01_80045FB0;
UnkStructA_40 *D_ovl0B_01_80045FBC;
UnkStructA_40 *D_ovl0B_01_80045FC0;
UnkStructA_40 *D_ovl0B_01_80045FC4;
UnkStructA_40 *D_ovl0B_01_80045FC8;
UnkStructC *D_ovl0B_01_80045FCC;
s32 D_ovl0B_01_80045FD0;
s32 D_ovl0B_01_80045FD4;
UnkStructA_40 *D_ovl0B_01_80045FD8;
UnkStructA_40 *D_ovl0B_01_80045FDC;
UnkStructA_40 *D_ovl0B_01_80045FE0;
#if !VERSION_JP
UnkStructA_40 *D_ovl0B_01_80045FE4;
#endif

static void func_ovl0B_01_8004464C(s32 arg0, Gfx_ovl0B_01 **arg1);
static void func_ovl0B_01_800430A4(UnkStruct_ovl0B_01_80045E34 *arg0);

/* .data */
u8 D_ovl0B_01_80045E00[] = "\x1A=O>GMNK>";
u8 D_ovl0B_01_80045E0C[] = "\x0F\x0F\x0F\x1B:MME>";
u8 D_ovl0B_01_80045E18[] = "\x0F\x0F\x1CNLMHF";
u8 D_ovl0B_01_80045E24[] = "\x0F\x0F(IMBHGL";
s32 D_ovl0B_01_80045E30 = 0;
UnkStruct_ovl0B_01_80045E34 D_ovl0B_01_80045E34 = {
    NULL, 0x1E, 0x1E, 0x1E, 0xB4, 0.0f, 160.0f, 1.0f, 0.75f, 160, 160, 160, 120, 0.0f, 0, 0x80,
    func_ovl0B_01_8004464C,
};
#if !VERSION_JP
UnkStruct_ovl0B_01_80045E78 D_ovl0B_01_80045E78 = { "'H\x0F\x1CHGMKHEE>K\x0F" "BG\x0F\xFF\x1CHGMKHEE>K\x0F,H<D>M\x0F\x11\xF8\xFF)E>:L>\x0FMNKG\x0FMA>\x0F\xFFIHP>K\x0FH\x3F\x3F\x0F:G=\x0F" "BGL>KM\x0F\xFF:\x0F\x1CHGMKHEE>K\xF8" };
#endif
s32 D_ovl0B_01_80045ED8 = 1;
UnkStruct_ovl0B_01_80045EDC D_ovl0B_01_80045EDC = { { 0x37, 0x27, 0x2A, 0x2B } };
UnkStruct_ovl0B_01_80045EDC D_ovl0B_01_80045EE4 = { { 0x28, 0x51, 0x7A, 0xA3 } };
u16 D_ovl0B_01_80045EEC[18] = {
    0x6E, 0xAB, 0x0402, 0,
    0x6E, 0xB7, 0x0103, 0,
    0x6E, 0xC3, 0x0204, 0,
    0x6E, 0xCF, 0x0301, 0,
    0, 0,
};

s32 func_ovl0B_01_800435C8(u8 arg0, u16 arg1);
void func_ovl0B_01_80043148(void);
void func_ovl0B_01_80043448(void);
void func_ovl0B_01_80043660(void);
void func_ovl0B_01_80043998(void);

static void func_ovl0B_01_80044644(void) {
}

static void func_ovl0B_01_8004463C(void) {
}

static void func_ovl0B_01_80044634(void) {
}

static void func_ovl0B_01_8004462C(void) {
}

static void func_ovl0B_01_80044624(void) {
}

static void func_ovl0B_01_8004461C(void) {
}

static void func_ovl0B_01_80044614(void) {
}

static void func_ovl0B_01_8004460C(void) {
}

static void func_ovl0B_01_80044604(void) {
}

static void func_ovl0B_01_800445FC(void) {
}

static void func_ovl0B_01_800445F4(void) {
}

static void func_ovl0B_01_800445EC(void) {
}

static void func_ovl0B_01_800445E4(void) {
}

/* a fake: a second (dead) caller keeps func_ovl0B_01_800430A4 from being
 * inlined into its only real one */
static void func_ovl0B_01_800445DC(void) {
    func_ovl0B_01_800430A4(&D_ovl0B_01_80045E34);
}

/* unused: the stubs IDO -O3 leaves at the end of the object; this one
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0B_01_800445D4(void) {
    D_ovl0B_01_80045F80[0] = D_ovl0B_01_80045FAC[0];
}

static void func_ovl0B_01_8004464C(s32 arg0, Gfx_ovl0B_01 **arg1) {
    UnkStruct_ovl0B_01_80045E34 *fade = &D_ovl0B_01_80045E34;
    Gfx_ovl0B_01 *gfx = *arg1;

    { Gfx_ovl0B_01 *g = gfx++; g->w0 = 0xFA000000; g->w1 = ((fade->unk4 & 0xFF) << 24) | ((fade->unk8 & 0xFF) << 16) | ((fade->unkC & 0xFF) << 8) | (fade->unk10 & 0xFF); }
    { Gfx_ovl0B_01 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFDF6FB; }
    { Gfx_ovl0B_01 *g = gfx++; g->w0 = 0xF7000000; g->w1 = 0x10001; }
    { Gfx_ovl0B_01 *g = gfx++; g->w0 = 0xF6000000 | (((fade->unk2C + (s32) fade->unk34) & 0x3FF) << 14) | (((fade->unk30 + (s32) (fade->unk34 * fade->unk20)) & 0x3FF) << 2); g->w1 = (((fade->unk2C - (s32) fade->unk34) & 0x3FF) << 14) | (((fade->unk30 - (s32) (fade->unk34 * fade->unk20)) & 0x3FF) << 2); }
    *arg1 = gfx;
}

void func_ovl0B_01_800445BC(void) {
    D_ovl0B_01_80045FA4 = -1;
    D_ovl0B_01_80045FA8 = -1;
}

void func_ovl0B_01_80044560(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0B_01_80045348(D_ovl0B_01_80045FB0.x, D_ovl0B_01_80045FB0.y, D_ovl0B_01_80045FB0.z);
    func_ovl0B_01_80045368(arg0, arg1, arg2);
    func_ovl0B_01_80045678(0xB4);
}

void func_ovl0B_01_80044518(f32 arg0) {
    f32 sp1C;

    func_ovl0B_01_80045370(&sp1C, NULL, NULL);
    func_ovl0B_01_80045368(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0B_01_800444E4(s32 arg0, UnkStruct_ovl0B_01_B04 *arg1) {
    func_ovl0B_01_80045C00(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

static void func_ovl0B_01_80043010(UnkStruct_ovl0B_01_80045E34 *arg0);
void func_ovl0B_01_80043D64(void);
void func_ovl0B_01_80043DD4(void);
void func_ovl0B_01_80043FE8(void);

void func_ovl0B_01_80044108(s32 arg0) {
    switch (arg0) {
        case 2:
            D_ovl0B_01_80045E34.unk0 = NULL;
            D_ovl0B_01_80045FD4 = func_ovl0B_01_80044C08();
            break;
        default:
            break;
        case 4:
            if (D_ovl0B_01_80045FD4 == 0x11) {
                func_ovl0B_01_80043FE8();
                func_ovl0B_01_80043DD4();
                D_ovl0B_01_80045FBC->unkC |= 0x400;
                D_ovl0B_01_80045FC0->unkC |= 0x400;
                D_ovl0B_01_80045FC4->unkC |= 0x400;
                D_ovl0B_01_80045FC8->unkC |= 0x400;
            }
            break;
        case 16:
            func_ovl0B_01_80045658(func_ovl0B_01_80043448, NULL, 0, 0, 0x130);
            break;
        case 17:
#if VERSION_JP
            D_ovl0B_01_80045FDC = func_ovl0B_01_800451E8(0x25, 5);
            D_ovl0B_01_80045FDC->unk10 = 91.5f;
            D_ovl0B_01_80045FDC->unk14 = 180.0f;
            D_ovl0B_01_80045FDC->unk18 = 228.5f;
            D_ovl0B_01_80045FDC->unk1C = 199.0f;
            D_ovl0B_01_80045FDC->unkC |= 0x200;
            D_ovl0B_01_80045FE0 = func_ovl0B_01_800451E8(0x26, 5);
            D_ovl0B_01_80045FE0->unk10 = 73.0f;
            D_ovl0B_01_80045FE0->unk14 = 205.0f;
            D_ovl0B_01_80045FE0->unk18 = 247.0f;
            D_ovl0B_01_80045FE0->unk1C = 218.0f;
            D_ovl0B_01_80045FE0->unkC |= 0x600;
#else
            D_ovl0B_01_80045FDC = func_ovl0B_01_800451E8(0x25, 5);
            D_ovl0B_01_80045FDC->unk10 = 84.5f;
            D_ovl0B_01_80045FDC->unk14 = 180.0f;
            D_ovl0B_01_80045FDC->unk18 = 235.5f;
            D_ovl0B_01_80045FDC->unk1C = 199.0f;
            D_ovl0B_01_80045FDC->unkC |= 0x200;
            D_ovl0B_01_80045FE0 = func_ovl0B_01_800451E8(0x367, 5);
            D_ovl0B_01_80045FE0->unk10 = 210.0f;
            D_ovl0B_01_80045FE0->unk14 = 114.0f;
            D_ovl0B_01_80045FE0->unk18 = 298.0f;
            D_ovl0B_01_80045FE0->unk1C = 180.0f;
            D_ovl0B_01_80045FE0->unkC |= 0x600;
            D_ovl0B_01_80045FE4 = func_ovl0B_01_800451E8(0x368, 5);
            D_ovl0B_01_80045FE4->unk10 = 285.0f;
            D_ovl0B_01_80045FE4->unk14 = 51.0f;
            D_ovl0B_01_80045FE4->unk18 = 304.0f;
            D_ovl0B_01_80045FE4->unk1C = 62.0f;
            D_ovl0B_01_80045FE4->unkC |= 0x600;
#endif
            func_ovl0B_01_800453B0(0x7F);
            func_ovl0B_01_80045328(1);
            func_ovl0B_01_80045348(0.0f, 70.0f, 0.0f);
            func_ovl0B_01_80045338(1);
            func_ovl0B_01_80045368(0.0f, 40.0f, 500.0f);
            break;
        case 5:
            if (D_ovl0B_01_80045FD4 == 0x11) {
                func_ovl0B_01_80045658(func_ovl0B_01_80043148, NULL, 0, 0, 0x130);
            }
            break;
        case 1:
            switch (D_ovl0B_01_80045FD4) {
                case 0x10:
                    func_ovl0B_01_800451F0(D_ovl0B_01_80045FD8);
                    func_ovl0B_01_80045D88();
                    break;
                case 0x11:
                    func_ovl0B_01_80043D64();
                    func_ovl0B_01_800451F0(D_ovl0B_01_80045FDC);
                    func_ovl0B_01_800451F0(D_ovl0B_01_80045FE0);
#if !VERSION_JP
                    func_ovl0B_01_800451F0(D_ovl0B_01_80045FE4);
#endif
                    if (D_ovl0B_01_80045E34.unk0 != NULL) {
                        func_ovl0B_01_80043010(&D_ovl0B_01_80045E34);
                    }
                    if (D_ovl0B_01_80045E30 != 0) {
                        func_ovl0B_01_80045D88();
                    }
                    break;
            }
            break;
    }
}

void func_ovl0B_01_80043FE8(void) {
    D_ovl0B_01_80045FBC = func_ovl0B_01_800451E8(0x353, 1);
    D_ovl0B_01_80045FBC->unkC |= 1;
    D_ovl0B_01_80045FC4 = func_ovl0B_01_800451E8(0x355, 2);
    D_ovl0B_01_80045FC4->unkC |= 1;
    D_ovl0B_01_80045FC8 = func_ovl0B_01_800451E8(0x356, 3);
    D_ovl0B_01_80045FC8->unkC |= 1;
    D_ovl0B_01_80045FC0 = func_ovl0B_01_800451E8(0x354, 4);
    D_ovl0B_01_80045FC0->unkC |= 1;
    D_ovl0B_01_80045FCC = func_ovl0B_01_800456E0(0x296);
    func_ovl0B_01_800456F0(D_ovl0B_01_80045FCC, 1);
    D_ovl0B_01_80045FCC->unk18 = 0.0f;
    D_ovl0B_01_80045FCC->unk1C = 0.0f;
    D_ovl0B_01_80045FCC->unk40 = 0.5f;
    D_ovl0B_01_80045FCC->unk44 = D_ovl0B_01_80045FCC->unk40 * 0.75f;
    D_ovl0B_01_80045FCC->unk3C = 32.0f;
}

static void func_ovl0B_01_80043DCC(void) {
}

static void func_ovl0B_01_80043DC4(void) {
}

static void func_ovl0B_01_80043DBC(void) {
}

void func_ovl0B_01_80043DD4(void) {
    func_ovl0B_01_80043DBC();
    func_ovl0B_01_80043DC4();
    func_ovl0B_01_80043DCC();
    D_ovl0B_01_80045FBC->unk10 = 71.0f;
    D_ovl0B_01_80045FBC->unk14 = 13.0f;
    D_ovl0B_01_80045FBC->unk18 = D_ovl0B_01_80045FBC->unk10 + D_ovl0B_01_80045FBC->unk28;
    D_ovl0B_01_80045FBC->unk1C = D_ovl0B_01_80045FBC->unk14 + D_ovl0B_01_80045FBC->unk2C;
    D_ovl0B_01_80045FBC->unkC &= ~1;
    D_ovl0B_01_80045FC0->unk10 = 29.0f;
    D_ovl0B_01_80045FC0->unk14 = 78.0f;
    D_ovl0B_01_80045FC0->unk18 = D_ovl0B_01_80045FC0->unk10 + D_ovl0B_01_80045FC0->unk28;
    D_ovl0B_01_80045FC0->unk1C = D_ovl0B_01_80045FC0->unk14 + D_ovl0B_01_80045FC0->unk2C;
    D_ovl0B_01_80045FC0->unkC &= ~1;
    D_ovl0B_01_80045FC4->unk10 = 127.0f;
    D_ovl0B_01_80045FC4->unk14 = 54.0f;
    D_ovl0B_01_80045FC4->unk18 = D_ovl0B_01_80045FC4->unk10 + D_ovl0B_01_80045FC4->unk28;
    D_ovl0B_01_80045FC4->unk1C = D_ovl0B_01_80045FC4->unk14 + D_ovl0B_01_80045FC4->unk2C;
    D_ovl0B_01_80045FC4->unkC &= ~1;
    D_ovl0B_01_80045FC8->unk10 = 164.0f;
    D_ovl0B_01_80045FC8->unk14 = 88.0f;
    D_ovl0B_01_80045FC8->unk18 = D_ovl0B_01_80045FC8->unk10 + D_ovl0B_01_80045FC8->unk28;
    D_ovl0B_01_80045FC8->unk1C = D_ovl0B_01_80045FC8->unk14 + D_ovl0B_01_80045FC8->unk2C;
    D_ovl0B_01_80045FC8->unkC &= ~1;
    func_ovl0B_01_800456F0(D_ovl0B_01_80045FCC, 0x20000000);
    D_ovl0B_01_80045FCC->unk18 = 0.0625f;
    D_ovl0B_01_80045FCC->unk1C = 0.0f;
}

static void func_ovl0B_01_80043D5C(void) {
}

void func_ovl0B_01_80043D64(void) {
    func_ovl0B_01_80043D5C();
    func_ovl0B_01_800451F0(D_ovl0B_01_80045FBC);
    func_ovl0B_01_800451F0(D_ovl0B_01_80045FC0);
    func_ovl0B_01_800451F0(D_ovl0B_01_80045FC4);
    func_ovl0B_01_800451F0(D_ovl0B_01_80045FC8);
}

static void func_ovl0B_01_8004376C(s32 *ids, s32 mode);

void func_ovl0B_01_80043998(void) {
    s32 ids[4];
    UnkStruct_ovl0B_01_80045EDC xs = D_ovl0B_01_80045EDC;
    UnkStruct_ovl0B_01_80045EDC ys = D_ovl0B_01_80045EE4;
    f32 step;
    f32 scale;
    s32 sel;
    s32 i;

    step = 0.025f;
    scale = 1.5f;
    sel = D_ovl0B_01_80045ED8 - 1;
    ids[0] = func_ovl0B_01_80045A98(D_ovl0B_01_80045E00, 0x37, 0x28, 1.5f, 1.63f, 0);
    ids[1] = func_ovl0B_01_80045A98(D_ovl0B_01_80045E0C, 0x27, 0x51, 1.5f, 1.63f, 0);
    ids[2] = func_ovl0B_01_80045A98(D_ovl0B_01_80045E18, 0x2A, 0x7A, 1.5f, 1.63f, 0);
    ids[3] = func_ovl0B_01_80045A98(D_ovl0B_01_80045E24, 0x2B, 0xA3, 1.5f, 1.63f, 0);
    func_ovl0B_01_8004376C(ids, 0);
    while (D_ovl0B_01_80045FD0 != 0) {
        for (i = 0; i < 10; i++) {
            if (D_ovl0B_01_80045FD0 == 0) {
                break;
            }
            if (D_ovl0B_01_80045ED8 > 0 && sel + 1 != D_ovl0B_01_80045ED8) {
                step = 0.025f;
                scale = 1.5f;
                i = 0;
                func_ovl0B_01_80045A58(ids[sel], xs.v[sel], ys.v[sel]);
                func_ovl0B_01_80045A68(ids[sel], 1.5f, 1.63f);
                sel = D_ovl0B_01_80045ED8 - 1;
            }
            func_ovl0B_01_80045A58(ids[sel], xs.v[sel] - (scale - 1.5f) * 80.0f, ys.v[sel]);
            func_ovl0B_01_80045A68(ids[sel], scale, scale * 1.0866667f);
            scale += step;
            func_ovl0B_01_800456A0();
        }
        step = -step;
    }
    func_ovl0B_01_8004376C(ids, 1);
    func_ovl0B_01_80045A48(ids[0]);
    func_ovl0B_01_80045A48(ids[1]);
    func_ovl0B_01_80045A48(ids[2]);
    func_ovl0B_01_80045A48(ids[3]);
    func_ovl0B_01_80045668();
}

static void func_ovl0B_01_8004376C(s32 *ids, s32 mode) {
    UnkStructA_40 *spr[4];
    f32 rect[4][4];
    s32 n;
    s32 i;
    s32 j;

    if (mode == 0) {
        n = 30;
    } else {
        n = 15;
    }
    for (i = 0; i < 4; i++) {
        spr[i] = func_ovl0B_01_80045A78(ids[i]);
        rect[i][0] = spr[i]->unk10;
        rect[i][1] = spr[i]->unk14;
        rect[i][2] = spr[i]->unk18;
        rect[i][3] = spr[i]->unk1C;
        if (mode == 0) {
            spr[i]->unk10 = 160.0f;
            spr[i]->unk18 = 160.0f;
            spr[i]->unk14 = 120.0f;
            spr[i]->unk1C = 120.0f;
        }
    }
    for (j = 0; j < n; j++) {
        for (i = 0; i < 4; i++) {
            if (mode == 0) {
                if (D_ovl0B_01_80045FD0 == 0) {
                    j = n;
                    break;
                }
                spr[i]->unk10 += (rect[i][0] - 160.0f) / n;
                spr[i]->unk14 += (rect[i][1] - 120.0f) / n;
                spr[i]->unk18 += (rect[i][2] - 160.0f) / n;
                spr[i]->unk1C += (rect[i][3] - 120.0f) / n;
            } else {
                spr[i]->unk10 += (160.0f - rect[i][0]) / n;
                spr[i]->unk14 += (120.0f - rect[i][1]) / n;
                spr[i]->unk18 += (160.0f - rect[i][2]) / n;
                spr[i]->unk1C += (120.0f - rect[i][3]) / n;
            }
        }
        func_ovl0B_01_800456A0();
    }
}

void func_ovl0B_01_80043660(void) {
    s32 pad[3]; /* unused: the original's frame has the slots */
    UnkStruct_ovl0B_01_80044C58 *state;
    s32 presses;
    s32 idle;
    s32 t;

    state = func_ovl0B_01_80044C58();
    if (state->unk44 != 0) {
        func_ovl0B_01_800456A0();
    }
    presses = 0;
    idle = 0;
    t = 0;
    for (;;) {
        if (func_ovl0B_01_80045738(0) & 0x1000) {
            presses++;
            idle = 0;
        } else {
            idle++;
        }
        if (idle >= 7) {
            t = 0;
            presses = 0;
        }
        if (t == 59) {
            if (presses >= 10 && presses < 15) {
                presses = 0;
                idle = 0;
                t = 0;
                func_ovl0B_01_80045BE0(0x2C);
                state->unk44 = 1;
                for (;;) {
                    func_ovl0B_01_800456A0();
                }
            }
            t = 0;
            presses = 0;
        } else {
            t++;
        }
        func_ovl0B_01_800456A0();
    }
}

s32 func_ovl0B_01_800435C8(u8 arg0, u16 arg1) {
    D_ovl0B_01_80045ED8 = arg0;
    if (arg1 & 1) {
        func_ovl0B_01_80045BE0(1);
        D_ovl0B_01_80045FD0 = 0;
        return 0;
    }
    if (arg1 & 2) {
        func_ovl0B_01_80045BE0(2);
        D_ovl0B_01_80045ED8 = -1;
        D_ovl0B_01_80045FD0 = 0;
        return 0;
    }
    if (arg1 & 0x78) {
        func_ovl0B_01_80045BE0(0);
        return 1;
    }
    return 1;
}

#if VERSION_JP
void func_ovl0B_01_80043448(void) {
    s32 i;

    func_ovl0B_01_80045678(0x14);
    func_ovl0B_01_80045938(1);
    D_ovl0B_01_80045FD8 = func_ovl0B_01_800451E8(0x24, 0);
    D_ovl0B_01_80045FD8->unk10 = 31.0f;
    D_ovl0B_01_80045FD8->unk14 = 97.0f;
    D_ovl0B_01_80045FD8->unk18 = 289.0f;
    D_ovl0B_01_80045FD8->unk1C = 143.0f;
#else
void func_ovl0B_01_80043448(void) {
    s32 i;
    UnkStruct_ovl0B_01_80045E78 str = D_ovl0B_01_80045E78;

    func_ovl0B_01_80045678(0x14);
    func_ovl0B_01_80045938(1);
    if (func_ovl0B_01_80045720(0) == 8) {
        func_ovl0B_01_80045A98(str.s, 0x28, 0x50, 0.8f, 0.8f, 2);
        for (;;) {
            func_ovl0B_01_800456A0();
        }
    }
    D_ovl0B_01_80045FD8 = func_ovl0B_01_800451E8(0x366, 0);
    D_ovl0B_01_80045FD8->unk10 = 0.0f;
    D_ovl0B_01_80045FD8->unk14 = 0.0f;
    D_ovl0B_01_80045FD8->unk18 = 319.0f;
    D_ovl0B_01_80045FD8->unk1C = 239.0f;
#endif
    func_ovl0B_01_800459A8(0xFF, 0xFF, 0xFF);
    func_ovl0B_01_80045950();
#if !VERSION_JP
    func_ovl0B_01_80045678(300);
#endif
    for (i = 0; i < 120; i++) {
        if (func_ovl0B_01_80044C18() & 0x1000) {
            break;
        }
        func_ovl0B_01_800456A0();
    }
    func_ovl0B_01_80045DF0(0);
    func_ovl0B_01_80045DE0();
    func_ovl0B_01_80045668();
}

static void func_ovl0B_01_800430A4(UnkStruct_ovl0B_01_80045E34 *arg0);

void func_ovl0B_01_80043148(void) {
    s32 blink;
    s32 idle;
    s32 task;

    blink = 0;
    idle = 0;
    for (D_ovl0B_01_80045E30 = 0; D_ovl0B_01_80045E30 == 0;) {
        if (func_ovl0B_01_80044C18() & 0x1000) {
            idle = 0;
            func_ovl0B_01_80045BE0(1);
            blink = 0;
            D_ovl0B_01_80045FDC->unkC |= 1;
            func_ovl0B_01_800430A4(&D_ovl0B_01_80045E34);
            D_ovl0B_01_80045ED8 = 1;
            D_ovl0B_01_80045FD0 = 1;
            func_ovl0B_01_80045658(func_ovl0B_01_80043998, NULL, 0, 0, 0x130);
            task = func_ovl0B_01_80045658(func_ovl0B_01_80043660, NULL, 0, 0, 0x130);
            func_ovl0B_01_800459E0(func_ovl0B_01_800435C8, D_ovl0B_01_80045EEC, 0x130, 0xE, 0xE)->unkC |= 1;
            func_ovl0B_01_800456A0();
            func_ovl0B_01_80045A08(D_ovl0B_01_80045ED8);
            func_ovl0B_01_80045A00();
            func_ovl0B_01_800459F8();
            func_ovl0B_01_80045660(task);
            func_ovl0B_01_800456A0();
            if (D_ovl0B_01_80045ED8 == -1) {
                func_ovl0B_01_80045678(0x14);
            } else if (D_ovl0B_01_80045ED8 == 1) {
                func_ovl0B_01_80044C00(0x1F, 0x10, 0);
                for (;;) {
                    func_ovl0B_01_800456A0();
                }
            } else if (D_ovl0B_01_80045ED8 == 2) {
                func_ovl0B_01_80044C00(0x23, 0x10, 0);
                for (;;) {
                    func_ovl0B_01_800456A0();
                }
            } else if (D_ovl0B_01_80045ED8 == 3) {
                func_ovl0B_01_80044C00(0x1F, 0x11, 0);
                for (;;) {
                    func_ovl0B_01_800456A0();
                }
            } else if (D_ovl0B_01_80045ED8 == 4) {
                func_ovl0B_01_80044C00(0x26, 0x10, 0);
                for (;;) {
                    func_ovl0B_01_800456A0();
                }
            }
            func_ovl0B_01_80043010(&D_ovl0B_01_80045E34);
            D_ovl0B_01_80045E34.unk0 = NULL;
        } else {
            idle++;
            if (idle >= 0x709) {
                func_ovl0B_01_80045DE0();
                D_ovl0B_01_80045E30 = 1;
            }
            blink++;
            if (blink & 0x10) {
                D_ovl0B_01_80045FDC->unkC |= 1;
            } else {
                D_ovl0B_01_80045FDC->unkC &= ~1;
            }
        }
        func_ovl0B_01_800456A0();
    }
    for (;;) {
        func_ovl0B_01_800456A0();
    }
}

static void func_ovl0B_01_8004309C(void) {
}

static void func_ovl0B_01_800430A4(UnkStruct_ovl0B_01_80045E34 *arg0) {
    f32 step = (arg0->unk18 - arg0->unk14) / arg0->unk1C;

    func_ovl0B_01_8004309C();
    arg0->unk0 = func_ovl0B_01_80045268(arg0->unk40, arg0->unk38);
    arg0->unk0->unkC |= arg0->unk3C;
    for (arg0->unk34 = arg0->unk14; arg0->unk34 < arg0->unk18; arg0->unk34 += step) {
        func_ovl0B_01_800456A0();
    }
    func_ovl0B_01_800456A0();
}

static void func_ovl0B_01_80043010(UnkStruct_ovl0B_01_80045E34 *arg0) {
    for (arg0->unk34 = arg0->unk24; arg0->unk34 > 0.0f; arg0->unk34 -= arg0->unk28) {
        func_ovl0B_01_800456A0();
    }
    func_ovl0B_01_800451F0(arg0->unk0);
    func_ovl0B_01_800456A0();
}
