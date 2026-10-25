/*
 * NON_MATCHING: ovl_0B_04's game object (the name-entry screen: a name of
 * eight characters from four character sets, and four slots of ten choices
 * each), complete: every function and its data. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 3565, jp 4192
 *
 * Order (scratch/ord/search.py, hill-climb over definition order, scored by
 * the emitted sequence's edit distance from the original's address order):
 * distance 31 of 56 functions out of place, from 4362 words; the search
 * stopped at its kick limit, so it is a local best. No static/global changes.
 * A first draft from m2c: the logic is the original's, the layout isn't.
 * The pages are a table (D_ovl0B_04_800499B8: texts, handler, cursor
 * table, set-up) that func_ovl0B_04_80043ADC runs in turn; pages 1-4 are
 * the character sets, 5-8 the slots, 9 the save question. The statics
 * the original passes arguments in $s/$t registers (80043050, 800438FC,
 * 80043A24/80043A7C, 8004401C/800440C8, 80044394, 8004447C, 800447DC,
 * 80045540, 800458F4/80045958, 800468F0) are statics here with ordinary
 * parameters; MakeEntries/FreeEntries, PageItem, SetText and Mark27 are
 * statics the original inlines (their parameter slots show in the frames).
 * Emission order: IDO -O3 takes the globals in reverse definition order
 * and puts each one's static callees just before it, in the reverse order
 * of its calls (each after its own callees); an indirect call also pulls
 * every function whose address the code takes (why 80043CD0 comes out
 * first: 80043110's or 80043ADC's call through the page table pulls it).
 * The original's statics come out before callers that don't call them
 * (80043FA4-8004447C before 800444E8, 80045540 before 800459C4, 80046294-
 * 80046734 before 80046AA0), so its callers probably inlined statics whose
 * dead branches called them. Here a dead `if (0) { ... }` at the end of
 * the global lists the run in reverse (scratch/0B_04/p4/pull.py and
 * spec2.txt in the main checkout); the empty stubs it calls are named for
 * the original's stub addresses. The `if (0)` calls to 8004471C keep it out
 * of line, as in the original. 80046734 writes PageItem out twice (no
 * stubs before it in the original); PageItem itself is 80046294's.
 * Data: .data 800489F0-8004A1F0 typed from data_c.py's words
 * (scratch/0B_04/gendata.py in the main checkout); the .bss in address
 * order without the unreferenced gaps.
 *
 * What still differs in us (words), mostly because the statics don't come
 * out between the same globals as in the original yet (the comparison
 * counts a global with the statics after it):
 * - 80043110 350, 800436C8 368, 80043CD0 211, 80043ADC 207,
 *   80043F24 362, 800444E8 579, 80044BE8 205, 800450C0 105,
 *   80045214 431, 800459C4 233, 80046180 544 (the statics after them);
 * - 80045AF0/80045D20 25 each, 80045F50 24 (it passes D[0]'s value to
 *   800458F4 by a cast, as the original does; its D[1] in $s1 isn't in C), 80045BF4/80045E24/80046054 73
 *   each, 80046B28 109, 80046FA8 79, 80046D74 73, 800471F4 77,
 *   80046AA0 42, 80046CEC/80046F20/8004716C 3 each;
 *   80046D74, 80046FA8 and 800471F4 have their 0x30-byte pad (the frame
 *   is 144 as in the original) and their FreeEntries loops written out
 *   (80046D74 and 80046FA8 are 8 bytes short: the empty stub after each
 *   isn't written yet);
 * - 80043E4C, 80043E80, 80043EC8 match.
 */
#include "common.h"

/* The game objects the ZeroJump calls make and return. */
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
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 unk3C[0xC];
    /* 0x48 */ UnkStructA_40_48 *unk48;
} Obj;

typedef struct {
    u32 w0;
    u32 w1;
} Gfx0B04;

/* A line of text: string, position, scale and its two colours. */
typedef struct {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
} Item; /* size = 0x14 */

/* A menu's cursor table (the 0x2400 call's second argument). */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 unk4[4];
} Nav; /* size = 0x8 */

/* The screen's pages (func_ovl0B_04_80043ADC runs them). */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 *unk4;
    /* 0x08 */ Item *unk8;
    /* 0x0C */ u8 (*unkC)(u8, u16);
    /* 0x10 */ void *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ void (*unk20)(Obj *);
} Page; /* size = 0x24 */

/* A fade (ovl_0B_05's D_ovl0B_05_8004669C). */
typedef struct {
    /* 0x00 */ Obj *unk0;
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
} Fade; /* size = 0x38 */

/* How func_ovl0B_04_80043050 makes an Entry's object. */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} Desc; /* size = 0x18 */

typedef struct {
    /* 0x00 */ Obj *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Entry; /* size = 0x14 */

typedef struct {
    /* 0x00 */ u8 unk0; /* cursor in the name */
    /* 0x01 */ u8 unk1; /* character */
    /* 0x02 */ u8 unk2; /* character set (page) */
    /* 0x03 */ u8 unk3; /* menu item */
} Cursor;

/* ZeroJump (the main code's functions; the code in the comments). */
void func_ovl0B_04_800477F0(s32, s32, s32); /* 0x0F00 */
void func_ovl0B_04_800478A0(s32, s32, s32); /* 0x0F16 */
Obj *func_ovl0B_04_80047DD8(s32, s32); /* 0x1500 */
void func_ovl0B_04_80047DE0(Obj *); /* 0x1501 */
void func_ovl0B_04_80047DF0(Obj *, s32); /* 0x1503 */
void func_ovl0B_04_80047E00(Obj *, s32); /* 0x1505 */
void func_ovl0B_04_80047E08(Obj *, s32, s32, s32); /* 0x1506 */
void func_ovl0B_04_80047E20(Obj *, s32, s32); /* 0x1509 */
void func_ovl0B_04_80047E28(Obj *, s32, s32); /* 0x150A */
Obj *func_ovl0B_04_80047E58(void (*)(s32, Gfx0B04 **), s32); /* 0x1510 */
s32 func_ovl0B_04_80047E68(Obj *, s32); /* 0x1512 */
void func_ovl0B_04_80047E70(s32, s32, s32); /* 0x1513 */
void func_ovl0B_04_80047E78(s32); /* 0x1514 */
void func_ovl0B_04_80047F18(s32); /* 0x1700 */
void func_ovl0B_04_80047F28(s32); /* 0x1702 */
void func_ovl0B_04_80047F38(f32, f32, f32); /* 0x1704 */
void func_ovl0B_04_80047F58(f32, f32, f32); /* 0x1708 */
void func_ovl0B_04_80047F60(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0B_04_80047FA0(s32); /* 0x1711 */
s32 func_ovl0B_04_80048248(void (*)(void), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0B_04_80048250(s32); /* 0x1901 */
void func_ovl0B_04_80048258(void); /* 0x1902 */
void func_ovl0B_04_80048268(s32); /* 0x1904 */
s32 func_ovl0B_04_80048290(void); /* 0x1909 */
s32 func_ovl0B_04_80048320(s32); /* 0x1B06 */
s32 func_ovl0B_04_800484B0(s32); /* 0x1E04 */
void *func_ovl0B_04_800484E0(s32); /* 0x1E0A */
void func_ovl0B_04_800485A0(s32); /* 0x2202 */
void func_ovl0B_04_800485A8(s32); /* 0x2203 */
Obj *func_ovl0B_04_800485D0(u8 (*)(u8, u16), void *, s32, s32, s32); /* 0x2400 */
void func_ovl0B_04_800485E8(void); /* 0x2403 */
void func_ovl0B_04_800485F0(void); /* 0x2404 */
void func_ovl0B_04_800485F8(u8); /* 0x2405 */
Obj *func_ovl0B_04_80048608(void); /* 0x2407 */
s32 func_ovl0B_04_80048630(u8 *, u16, u16, f32, f32, s32); /* 0x2501 */
void func_ovl0B_04_80048638(s32); /* 0x2502 */
void func_ovl0B_04_80048640(s32, u8 *, s32); /* 0x2503 */
void func_ovl0B_04_80048650(s32, u16, u16); /* 0x2505 */
void func_ovl0B_04_80048658(s32, f32, f32); /* 0x2506 */
void func_ovl0B_04_80048660(s32, f32, f32); /* 0x2507 */
Obj *func_ovl0B_04_80048668(s32); /* 0x2508 */
s32 func_ovl0B_04_80048680(u8 *); /* 0x250B */
s32 func_ovl0B_04_80048688(u8 *, u16, u16, f32, f32, s32); /* 0x250C */
void func_ovl0B_04_80048690(s32, u8 *, s32); /* 0x250D */
s32 func_ovl0B_04_800487D0(s32); /* 0x2B00 */
void func_ovl0B_04_800487E0(s32); /* 0x2B02 */
void func_ovl0B_04_800487E8(void); /* 0x2B03 */
void func_ovl0B_04_800487F0(s32, f32, f32, f32); /* 0x2B04 */
s32 func_ovl0B_04_80048910(u8 *); /* 0x2F0A */

/* The pages' handlers and set-ups (the page table refers to them). */
u8 func_ovl0B_04_80044BE8(u8 arg0, u16 arg1);
void func_ovl0B_04_800444E8(Obj *arg0);
u8 func_ovl0B_04_80045AF0(u8 arg0, u16 arg1);
void func_ovl0B_04_800459C4(Obj *arg0);
u8 func_ovl0B_04_80045D20(u8 arg0, u16 arg1);
void func_ovl0B_04_80045BF4(Obj *arg0);
u8 func_ovl0B_04_80045F50(u8 arg0, u16 arg1);
void func_ovl0B_04_80045E24(Obj *arg0);
u8 func_ovl0B_04_80046180(u8 arg0, u16 arg1);
void func_ovl0B_04_80046054(Obj *arg0);
u8 func_ovl0B_04_80046B28(u8 arg0, u16 arg1);
void func_ovl0B_04_80046AA0(Obj *arg0);
u8 func_ovl0B_04_80046D74(u8 arg0, u16 arg1);
void func_ovl0B_04_80046CEC(Obj *arg0);
u8 func_ovl0B_04_80046FA8(u8 arg0, u16 arg1);
void func_ovl0B_04_80046F20(Obj *arg0);
u8 func_ovl0B_04_800471F4(u8 arg0, u16 arg1);
void func_ovl0B_04_8004716C(Obj *arg0);
u8 func_ovl0B_04_80045214(u8 arg0, u16 arg1);
void func_ovl0B_04_800450C0(Obj *arg0);

/* .bss */
u8 D_ovl0B_04_8004A290[12][2]; /* the name being entered, one character a string */
s32 D_ovl0B_04_8004A2A8[10];   /* page 0's texts */
s32 D_ovl0B_04_8004A2D0[2];    /* pages 1-4's */
s32 D_ovl0B_04_8004A2D8[2];
s32 D_ovl0B_04_8004A2E0[2];
s32 D_ovl0B_04_8004A2E8[50];   /* page 4's, then pages 5-8's (11 each) */
s32 D_ovl0B_04_8004A3B0[6];    /* page 9's */
Fade *D_ovl0B_04_8004A3E4;
s32 D_ovl0B_04_8004A3F0;
s32 D_ovl0B_04_8004A3F4;
Vec3f D_ovl0B_04_8004A3F8;
Page *D_ovl0B_04_8004A404;
s32 D_ovl0B_04_8004A40C[15];
s32 D_ovl0B_04_8004A448[8];    /* the name's characters */
s32 D_ovl0B_04_8004A468[6];
u8 D_ovl0B_04_8004A480[16];
Cursor D_ovl0B_04_8004A490;
u8 D_ovl0B_04_8004A498[8];
s32 D_ovl0B_04_8004A4A0;

/* .data */
u8 D_ovl0B_04_800489F0[0x30] = {
    0x1C, 0x4E, 0x4C, 0x4D, 0x48, 0x46, 0x00, 0x00, 0x27, 0x3A, 0x46, 0x3E, 0x00, 0x00, 0x00, 0x00,
    0x21, 0x3E, 0x3A, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x48, 0x3D, 0x52, 0x00, 0x00, 0x00, 0x00,
    0x1A, 0x4B, 0x46, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x25, 0x3E, 0x40, 0x4C, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80048A20[0xC] = {
    0x1B, 0x28, 0x26, 0x1B, 0x1E, 0x2B, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80048A2C[0x28] = {
    0x1D, 0x3A, 0x4D, 0x3A, 0x0F, 0x2E, 0x49, 0x3D, 0x3A, 0x4D, 0x3E, 0x3D, 0x00, 0x00, 0x00, 0x00,
    0x2C, 0x3A, 0x4F, 0x3E, 0x0F, 0x1D, 0x3A, 0x4D, 0x3A, 0xF7, 0x00, 0x00, 0x32, 0x3E, 0x4C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x27, 0x48, 0x00, 0x00,
};
u8 D_ovl0B_04_80048A54[0xC] = {
    0x2C, 0x3A, 0x4F, 0x42, 0x47, 0x40, 0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80048A60[0x10] = {
    0x2C, 0x3A, 0x4F, 0x3E, 0x0F, 0x1F, 0x3A, 0x42, 0x45, 0x4E, 0x4B, 0x3E, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80048A70[0x8] = {
    0x79, 0x0F, 0x9B, 0x0F, 0xA0, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80048A78[0x4] = {
    0xB0, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80048A7C[0x4] = {
    0x60, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80048A80[0x4] = {
    0x1A, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80048A84[0x104] = {
    0x3A, 0x00, 0x00, 0x00, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xFF, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xFF,
    0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xFF, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xFF, 0xC4, 0xC5, 0xC6, 0xC7,
    0xC8, 0x00, 0x00, 0x00, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xFF, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xFF,
    0xD3, 0x0F, 0xD4, 0x0F, 0xD5, 0xFF, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xFF, 0xDB, 0xAE, 0xAF, 0x0F,
    0x0F, 0x00, 0x00, 0x00, 0x60, 0x61, 0x62, 0x63, 0x64, 0xFF, 0x65, 0x66, 0x67, 0x68, 0x69, 0xFF,
    0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0xFF, 0x6F, 0x70, 0x71, 0x72, 0x73, 0xFF, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x00, 0x00, 0x00, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0xFF, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0xFF,
    0x83, 0x0F, 0x84, 0x0F, 0x85, 0xFF, 0x86, 0x87, 0x88, 0x89, 0x8A, 0xFF, 0x8B, 0x5E, 0x5F, 0x0F,
    0x0F, 0x00, 0x00, 0x00, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0xFF, 0x24, 0x25, 0x26, 0x27, 0x28, 0xFF,
    0x2E, 0x2F, 0x30, 0x31, 0x32, 0xFF, 0x10, 0x11, 0x12, 0x13, 0x14, 0xFF, 0xF6, 0xF7, 0xF8, 0xF9,
    0xFA, 0x00, 0x00, 0x00, 0x1F, 0x20, 0x21, 0x22, 0x23, 0xFF, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0xFF,
    0x33, 0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0x15, 0x16, 0x17, 0x18, 0x19, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F,
    0x0F, 0x00, 0x00, 0x00, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0xFF, 0x44, 0x45, 0x46, 0x47, 0x48, 0xFF,
    0x4E, 0x4F, 0x50, 0x51, 0x52, 0xFF, 0x10, 0x11, 0x12, 0x13, 0x14, 0xFF, 0xF6, 0xF7, 0xF8, 0xF9,
    0xFA, 0x00, 0x00, 0x00, 0x3F, 0x40, 0x41, 0x42, 0x43, 0xFF, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0xFF,
    0x53, 0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0x15, 0x16, 0x17, 0x18, 0x19, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F,
    0x0F, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80048B88[0x10] = {
    0xF7, 0xF7, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x3E, 0x46, 0x48, 0x4F, 0x3E, 0x00, 0x00,
};
u8 D_ovl0B_04_80048B98[0x234] = {
    0x29, 0x3A, 0x40, 0x3E, 0x0F, 0x11, 0x00, 0x00, 0x20, 0x48, 0x45, 0x3D, 0x0F, 0x2F, 0x42, 0x4C,
    0x48, 0x4B, 0x00, 0x00, 0x2C, 0x4E, 0x47, 0x40, 0x45, 0x3A, 0x4C, 0x4C, 0x3E, 0x4C, 0x00, 0x00,
    0x1C, 0x3A, 0x4D, 0x0F, 0x21, 0x48, 0x48, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x4B, 0x3A, 0x40,
    0x48, 0x47, 0x0F, 0x21, 0x3E, 0x3A, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x48, 0x47, 0x52,
    0x4D, 0x3A, 0x42, 0x45, 0x4C, 0x00, 0x00, 0x00, 0x22, 0x4B, 0x48, 0x47, 0x0F, 0x20, 0x48, 0x40,
    0x40, 0x45, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x24, 0x47, 0x42, 0x40, 0x41, 0x4D, 0x0F, 0x21,
    0x3E, 0x45, 0x46, 0x3E, 0x4D, 0x00, 0x00, 0x00, 0x1C, 0x45, 0x48, 0x50, 0x47, 0x0F, 0x2C, 0x46,
    0x42, 0x45, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x41, 0x42, 0x3C, 0x44, 0x3E, 0x47, 0x0F,
    0x21, 0x3E, 0x3A, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x3A, 0x46, 0x4E, 0x4B, 0x3A, 0x42, 0x0F,
    0x21, 0x3E, 0x3A, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x20, 0x48, 0x45, 0x3D, 0x0F, 0x1A, 0x4B, 0x46,
    0x48, 0x4B, 0x00, 0x00, 0x1D, 0x4E, 0x3C, 0x44, 0x0F, 0x1F, 0x45, 0x48, 0x3A, 0x4D, 0x00, 0x00,
    0x1C, 0x3A, 0x4D, 0x0F, 0x2C, 0x4E, 0x42, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x4B, 0x3A, 0x40,
    0x48, 0x47, 0x0F, 0x26, 0x3A, 0x42, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x4B, 0x3E, 0x4C,
    0x4C, 0x00, 0x00, 0x00, 0x22, 0x4B, 0x48, 0x47, 0x0F, 0x1A, 0x4B, 0x46, 0x48, 0x4B, 0x00, 0x00,
    0x24, 0x47, 0x42, 0x40, 0x41, 0x4D, 0x0F, 0x1A, 0x4B, 0x46, 0x48, 0x4B, 0x00, 0x00, 0x00, 0x00,
    0x24, 0x3A, 0x4B, 0x3A, 0x4D, 0x3E, 0x0F, 0x30, 0x3A, 0x4B, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x2B, 0x48, 0x3C, 0x44, 0x42, 0x47, 0x40, 0x0F, 0x21, 0x48, 0x4B, 0x4C, 0x3E, 0x00, 0x00, 0x00,
    0x2C, 0x41, 0x48, 0x40, 0x4E, 0x47, 0x0F, 0x24, 0x42, 0x46, 0x48, 0x47, 0x48, 0x00, 0x00, 0x00,
    0x20, 0x48, 0x45, 0x3D, 0x0F, 0x20, 0x45, 0x48, 0x4F, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1D, 0x4B, 0x42, 0x45, 0x45, 0x0F, 0x1A, 0x4B, 0x46, 0x4C, 0x00, 0x00, 0x1C, 0x3A, 0x4D, 0x0F,
    0x29, 0x3A, 0x50, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x4B, 0x3A, 0x40, 0x48, 0x47, 0x0F, 0x20,
    0x45, 0x48, 0x4F, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x2C, 0x45, 0x3A, 0x4C, 0x41, 0x0F, 0x1C, 0x45,
    0x3A, 0x50, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x4B, 0x48, 0x47, 0x0F, 0x27, 0x4E, 0x3C,
    0x44, 0x45, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x24, 0x47, 0x42, 0x40, 0x41, 0x4D, 0x0F, 0x2C,
    0x50, 0x48, 0x4B, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x48, 0x51, 0x42, 0x47, 0x40, 0x0F, 0x20,
    0x45, 0x48, 0x4F, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x1C, 0x41, 0x42, 0x3C, 0x44, 0x3E, 0x47, 0x0F,
    0x30, 0x42, 0x47, 0x40, 0x4C, 0x00, 0x00, 0x00, 0x1F, 0x3A, 0x47, 0x4C, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x48, 0x45, 0x3D, 0x0F, 0x1B, 0x48, 0x48, 0x4D, 0x4C, 0x00, 0x00, 0x1D, 0x4E, 0x3C, 0x44,
    0x0F, 0x1F, 0x3E, 0x3E, 0x4D, 0x00, 0x00, 0x00, 0x1C, 0x3A, 0x4D, 0x0F, 0x29, 0x3A, 0x50, 0x4C,
    0x00, 0x00, 0x00, 0x00, 0x1D, 0x4B, 0x3A, 0x40, 0x48, 0x47, 0x0F, 0x2C, 0x49, 0x42, 0x44, 0x3E,
    0x4C, 0x00, 0x00, 0x00, 0x21, 0x42, 0x40, 0x41, 0x0F, 0x2D, 0x48, 0x49, 0x4C, 0x00, 0x00, 0x00,
    0x22, 0x4B, 0x48, 0x47, 0x0F, 0x2C, 0x47, 0x3E, 0x3A, 0x44, 0x3E, 0x4B, 0x4C, 0x00, 0x00, 0x00,
    0x24, 0x47, 0x42, 0x40, 0x41, 0x4D, 0x0F, 0x2C, 0x41, 0x48, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x00,
    0x1C, 0x45, 0x48, 0x40, 0x4C, 0x00, 0x00, 0x00, 0x1B, 0x4E, 0x3B, 0x3B, 0x52, 0x0F, 0x2C, 0x48,
    0x3C, 0x44, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x42, 0x40, 0x41, 0x0F, 0x21, 0x3E, 0x3E,
    0x45, 0x4C, 0x00, 0x00,
};
Nav D_ovl0B_04_80048DCC[2] = {
    { 69, 93, 21, 6, 30, 2 },
    { 89, 93, 22, 7, 1, 3 },
};
u8 D_ovl0B_04_80048DDC[0x180] = {
    0x00, 0x6D, 0x00, 0x5D, 0x17, 0x08, 0x02, 0x04, 0x00, 0x81, 0x00, 0x5D, 0x18, 0x09, 0x03, 0x05,
    0x00, 0x95, 0x00, 0x5D, 0x19, 0x0A, 0x04, 0x1A, 0x00, 0x45, 0x00, 0x71, 0x01, 0x0B, 0x23, 0x07,
    0x00, 0x59, 0x00, 0x71, 0x02, 0x0C, 0x06, 0x08, 0x00, 0x6D, 0x00, 0x71, 0x03, 0x0D, 0x07, 0x09,
    0x00, 0x81, 0x00, 0x71, 0x04, 0x0E, 0x08, 0x0A, 0x00, 0x95, 0x00, 0x71, 0x05, 0x0F, 0x09, 0x1F,
    0x00, 0x45, 0x00, 0x85, 0x06, 0x10, 0x28, 0x0C, 0x00, 0x59, 0x00, 0x85, 0x07, 0x11, 0x0B, 0x0D,
    0x00, 0x6D, 0x00, 0x85, 0x08, 0x12, 0x0C, 0x0E, 0x00, 0x81, 0x00, 0x85, 0x09, 0x13, 0x0D, 0x0F,
    0x00, 0x95, 0x00, 0x85, 0x0A, 0x14, 0x0E, 0x24, 0x00, 0x45, 0x00, 0x99, 0x0B, 0x15, 0x2D, 0x11,
    0x00, 0x59, 0x00, 0x99, 0x0C, 0x16, 0x10, 0x12, 0x00, 0x6D, 0x00, 0x99, 0x0D, 0x17, 0x11, 0x13,
    0x00, 0x81, 0x00, 0x99, 0x0E, 0x18, 0x12, 0x14, 0x00, 0x95, 0x00, 0x99, 0x0F, 0x19, 0x13, 0x29,
    0x00, 0x45, 0x00, 0xAD, 0x10, 0x01, 0x32, 0x16, 0x00, 0x59, 0x00, 0xAD, 0x11, 0x02, 0x15, 0x17,
    0x00, 0x6D, 0x00, 0xAD, 0x12, 0x03, 0x16, 0x18, 0x00, 0x81, 0x00, 0xAD, 0x13, 0x04, 0x17, 0x19,
    0x00, 0x95, 0x00, 0xAD, 0x14, 0x05, 0x18, 0x2E, 0x00, 0xAB, 0x00, 0x5D, 0x2E, 0x1F, 0x05, 0x1B,
    0x00, 0xBF, 0x00, 0x5D, 0x2F, 0x20, 0x1A, 0x1C, 0x00, 0xD3, 0x00, 0x5D, 0x30, 0x21, 0x1B, 0x1D,
    0x00, 0xE7, 0x00, 0x5D, 0x31, 0x22, 0x1C, 0x1E, 0x00, 0xFB, 0x00, 0x5D, 0x32, 0x23, 0x1D, 0x01,
    0x00, 0xAB, 0x00, 0x71, 0x1A, 0x24, 0x0A, 0x20, 0x00, 0xBF, 0x00, 0x71, 0x1B, 0x25, 0x1F, 0x21,
    0x00, 0xD3, 0x00, 0x71, 0x1C, 0x26, 0x20, 0x22, 0x00, 0xE7, 0x00, 0x71, 0x1D, 0x27, 0x21, 0x23,
    0x00, 0xFB, 0x00, 0x71, 0x1E, 0x28, 0x22, 0x06, 0x00, 0xAB, 0x00, 0x85, 0x1F, 0x29, 0x0F, 0x25,
    0x00, 0xBF, 0x00, 0x85, 0x20, 0x2A, 0x24, 0x26, 0x00, 0xD3, 0x00, 0x85, 0x21, 0x2B, 0x25, 0x27,
    0x00, 0xE7, 0x00, 0x85, 0x22, 0x2C, 0x26, 0x28, 0x00, 0xFB, 0x00, 0x85, 0x23, 0x2D, 0x27, 0x0B,
    0x00, 0xAB, 0x00, 0x99, 0x24, 0x2E, 0x14, 0x2A, 0x00, 0xBF, 0x00, 0x99, 0x25, 0x2F, 0x29, 0x2B,
    0x00, 0xD3, 0x00, 0x99, 0x26, 0x30, 0x2A, 0x2C, 0x00, 0xE7, 0x00, 0x99, 0x27, 0x31, 0x2B, 0x2D,
    0x00, 0xFB, 0x00, 0x99, 0x28, 0x32, 0x2C, 0x10, 0x00, 0xAB, 0x00, 0xAD, 0x29, 0x1A, 0x19, 0x2F,
    0x00, 0xBF, 0x00, 0xAD, 0x2A, 0x1B, 0x2E, 0x30, 0x00, 0xD3, 0x00, 0xAD, 0x2B, 0x1C, 0x2F, 0x31,
    0x00, 0xF1, 0x00, 0xAD, 0x2C, 0x1D, 0x30, 0x15, 0x00, 0xF1, 0x00, 0xAD, 0x2D, 0x1E, 0x30, 0x15,
};
u8 D_ovl0B_04_80048F5C[0x100] = {
    0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x31,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x01, 0x02, 0x03, 0x04, 0x05, 0x1A,
    0x1B, 0x1C, 0x1D, 0x1E, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x0B, 0x0C,
    0x0D, 0x0E, 0x0F, 0x24, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x01, 0x02, 0x03, 0x04, 0x05, 0x1A,
    0x1B, 0x1C, 0x1D, 0x1E, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x0B, 0x0C,
    0x0D, 0x0E, 0x0F, 0x24, 0x32, 0x01, 0x02, 0x03, 0x04, 0x05, 0x12, 0x24, 0x26, 0x28, 0x2F, 0x30,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x21, 0x22, 0x23, 0x24, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x06, 0x07, 0x08, 0x09,
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
    0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x01, 0x02, 0x03, 0x04, 0x05, 0x12, 0x24, 0x26, 0x28, 0x2F, 0x30,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x21, 0x22, 0x23, 0x24, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x06, 0x07, 0x08, 0x09,
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
    0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x31, 0x15, 0x16, 0x17, 0x18, 0x19, 0x31, 0x31, 0x31, 0x32, 0x32,
};
u8 D_ovl0B_04_8004905C[0x100] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_8004915C[0x34] = {
    0x50, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE,
    0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE,
    0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0x0F, 0xD4, 0x0F, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xAE,
    0xAF, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_80049190[0x34] = {
    0x50, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E,
    0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E,
    0x7F, 0x80, 0x81, 0x82, 0x83, 0x0F, 0x84, 0x0F, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x5E,
    0x5F, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_800491C4[0x34] = {
    0x50, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x24, 0x25, 0x26, 0x27, 0x28, 0x2E, 0x2F, 0x30, 0x31, 0x32,
    0x10, 0x11, 0x12, 0x13, 0x14, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x29,
    0x2A, 0x2B, 0x2C, 0x2D, 0x33, 0x0F, 0x0F, 0x0F, 0x0F, 0x15, 0x16, 0x17, 0x18, 0x19, 0x0F, 0x0F,
    0x0F, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_04_800491F8[0x34] = {
    0x50, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x44, 0x45, 0x46, 0x47, 0x48, 0x4E, 0x4F, 0x50, 0x51, 0x52,
    0x10, 0x11, 0x12, 0x13, 0x14, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x49,
    0x4A, 0x4B, 0x4C, 0x4D, 0x53, 0x0F, 0x0F, 0x0F, 0x0F, 0x15, 0x16, 0x17, 0x18, 0x19, 0x0F, 0x0F,
    0x0F, 0x00, 0x00, 0x00,
};
Item D_ovl0B_04_8004922C[9] = {
    { D_ovl0B_04_800489F0, 110, 35, 0.9f, 0.9f, 0, 0 },
    { D_ovl0B_04_800489F0 + 0x8, 187, 77, 0.6f, 0.6f, 4, 3 },
    { D_ovl0B_04_800489F0 + 0x10, 187, 99, 0.6f, 0.6f, 4, 3 },
    { D_ovl0B_04_800489F0 + 0x18, 187, 121, 0.6f, 0.6f, 4, 3 },
    { D_ovl0B_04_800489F0 + 0x20, 187, 143, 0.6f, 0.6f, 4, 3 },
    { D_ovl0B_04_800489F0 + 0x28, 187, 165, 0.6f, 0.6f, 4, 3 },
    { D_ovl0B_04_80048A20, 93, 180, 0.65f, 0.65f, 2, 3 },
    { D_ovl0B_04_80048A20, 97, 184, 0.65f, 0.65f, 7, 0 },
    { D_ovl0B_04_800489F0, 114, 39, 0.9f, 0.9f, 7, 0 },
};
Nav D_ovl0B_04_800492E0[5] = {
    { 159, 78, 5, 2, 0, 0 },
    { 159, 100, 1, 3, 0, 0 },
    { 159, 122, 2, 4, 0, 0 },
    { 159, 144, 3, 5, 0, 0 },
    { 159, 166, 4, 1, 0, 0 },
};
Item D_ovl0B_04_80049308[8] = {
    { D_ovl0B_04_8004A290[0], 120, 50, 0.8f, 0.8f, 2, 0 },
    { D_ovl0B_04_8004A290[1], 140, 50, 0.8f, 0.8f, 2, 0 },
    { D_ovl0B_04_8004A290[2], 160, 50, 0.8f, 0.8f, 2, 0 },
    { D_ovl0B_04_8004A290[3], 180, 50, 0.8f, 0.8f, 2, 0 },
    { D_ovl0B_04_8004A290[4], 200, 50, 0.8f, 0.8f, 2, 0 },
    { D_ovl0B_04_8004A290[5], 220, 50, 0.8f, 0.8f, 2, 0 },
    { D_ovl0B_04_8004A290[6], 240, 50, 0.8f, 0.8f, 2, 0 },
    { D_ovl0B_04_8004A290[7], 260, 50, 0.8f, 0.8f, 2, 0 },
};
Item D_ovl0B_04_800493A8[1] = {
    { D_ovl0B_04_800489F0 + 0x8, 50, 50, 0.8f, 0.8f, 0, 0 },
};
Item D_ovl0B_04_800493BC[13] = {
    { D_ovl0B_04_80048A78, 163, 25, 0.5f, 0.5f, 6, 5 },
    { D_ovl0B_04_80048A7C, 193, 25, 0.5f, 0.5f, 6, 5 },
    { D_ovl0B_04_80048A80, 223, 25, 0.5f, 0.5f, 6, 5 },
    { D_ovl0B_04_80048A84, 253, 25, 0.5f, 0.5f, 6, 5 },
    { D_ovl0B_04_80048A70, 78, 194, 0.78f, 0.78f, 5, 5 },
    { D_ovl0B_04_80048A84 + 0x4, 58, 82, 0.85f, 0.85f, 3, 3 },
    { D_ovl0B_04_80048A84 + 0x24, 160, 82, 0.85f, 0.85f, 3, 3 },
    { D_ovl0B_04_80048A84 + 0x44, 58, 82, 0.85f, 0.85f, 3, 3 },
    { D_ovl0B_04_80048A84 + 0x64, 160, 82, 0.85f, 0.85f, 3, 3 },
    { D_ovl0B_04_80048A84 + 0x84, 58, 82, 0.85f, 0.85f, 3, 3 },
    { D_ovl0B_04_80048A84 + 0xA4, 160, 82, 0.85f, 0.85f, 3, 3 },
    { D_ovl0B_04_80048A84 + 0xC4, 58, 82, 0.85f, 0.85f, 3, 3 },
    { D_ovl0B_04_80048A84 + 0xE4, 160, 82, 0.85f, 0.85f, 3, 3 },
};
u8 *D_ovl0B_04_800494C0[4][10] = {
    D_ovl0B_04_80048B98 + 0x58,
    D_ovl0B_04_80048B98 + 0x2C,
    D_ovl0B_04_80048B98 + 0x48,
    D_ovl0B_04_80048B98 + 0x20,
    D_ovl0B_04_80048B98 + 0x3C,
    D_ovl0B_04_80048B98 + 0x14,
    D_ovl0B_04_80048B98 + 0x78,
    D_ovl0B_04_80048B98 + 0x88,
    D_ovl0B_04_80048B98 + 0x68,
    D_ovl0B_04_80048B98 + 0x8,
    D_ovl0B_04_80048B98 + 0xE0,
    D_ovl0B_04_80048B98 + 0xBC,
    D_ovl0B_04_80048B98 + 0xD4,
    D_ovl0B_04_80048B98 + 0xB0,
    D_ovl0B_04_80048B98 + 0xCC,
    D_ovl0B_04_80048B98 + 0xA4,
    D_ovl0B_04_80048B98 + 0x100,
    D_ovl0B_04_80048B98 + 0x110,
    D_ovl0B_04_80048B98 + 0xF0,
    D_ovl0B_04_80048B98 + 0x98,
    D_ovl0B_04_80048B98 + 0x178,
    D_ovl0B_04_80048B98 + 0x148,
    D_ovl0B_04_80048B98 + 0x168,
    D_ovl0B_04_80048B98 + 0x13C,
    D_ovl0B_04_80048B98 + 0x158,
    D_ovl0B_04_80048B98 + 0x130,
    D_ovl0B_04_80048B98 + 0x198,
    D_ovl0B_04_80048B98 + 0x1A8,
    D_ovl0B_04_80048B98 + 0x188,
    D_ovl0B_04_80048B98 + 0x120,
    D_ovl0B_04_80048B98 + 0x200,
    D_ovl0B_04_80048B98 + 0x1D4,
    D_ovl0B_04_80048B98 + 0x1F0,
    D_ovl0B_04_80048B98 + 0x1C8,
    D_ovl0B_04_80048B98 + 0x1E4,
    D_ovl0B_04_80048B98 + 0x1BC,
    D_ovl0B_04_80048B98 + 0x218,
    D_ovl0B_04_80048B98 + 0x228,
    D_ovl0B_04_80048B98 + 0x210,
    D_ovl0B_04_80048B98 + 0x1B0,
};
Item D_ovl0B_04_80049560[11] = {
    { D_ovl0B_04_800489F0 + 0x10, 120, 35, 0.9f, 0.9f, 0, 0 },
    { D_ovl0B_04_80048B98 + 0x8, 172, 82, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x14, 172, 102, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x20, 172, 122, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x2C, 172, 142, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x3C, 172, 162, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B88 + 0x8, 180, 197, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048A20, 93, 180, 0.65f, 0.65f, 2, 3 },
    { D_ovl0B_04_80048B98, 192, 62, 0.6f, 0.6f, 5, 5 },
    { D_ovl0B_04_80048A20, 97, 184, 0.65f, 0.65f, 7, 0 },
    { D_ovl0B_04_800489F0 + 0x10, 124, 39, 0.9f, 0.9f, 7, 0 },
};
Nav D_ovl0B_04_8004963C[12] = {
    { 159, 90, 11, 2, 0, 6 },
    { 159, 110, 1, 3, 0, 7 },
    { 159, 130, 2, 4, 0, 8 },
    { 159, 150, 3, 5, 0, 9 },
    { 159, 170, 4, 11, 0, 10 },
    { 159, 90, 12, 7, 1, 0 },
    { 159, 110, 6, 8, 2, 0 },
    { 159, 130, 7, 9, 3, 0 },
    { 159, 150, 8, 10, 4, 0 },
    { 159, 170, 9, 12, 5, 0 },
    { 159, 205, 5, 1, 0, 12 },
    { 159, 205, 10, 6, 11, 0 },
};
Item D_ovl0B_04_8004969C[11] = {
    { D_ovl0B_04_800489F0 + 0x18, 120, 35, 0.9f, 0.9f, 0, 0 },
    { D_ovl0B_04_80048B98 + 0x98, 172, 82, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0xA4, 172, 102, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0xB0, 172, 122, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0xBC, 172, 142, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0xCC, 172, 162, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B88 + 0x8, 180, 197, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048A20, 93, 180, 0.65f, 0.65f, 2, 3 },
    { D_ovl0B_04_80048B98, 192, 62, 0.6f, 0.6f, 5, 5 },
    { D_ovl0B_04_80048A20, 97, 184, 0.65f, 0.65f, 7, 0 },
    { D_ovl0B_04_800489F0 + 0x18, 124, 39, 0.9f, 0.9f, 7, 0 },
};
Item D_ovl0B_04_80049778[11] = {
    { D_ovl0B_04_800489F0 + 0x20, 123, 35, 0.9f, 0.9f, 0, 0 },
    { D_ovl0B_04_80048B98 + 0x120, 172, 82, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x130, 172, 102, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x13C, 172, 122, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x148, 172, 142, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x158, 172, 162, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B88 + 0x8, 180, 197, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048A20, 93, 180, 0.65f, 0.65f, 2, 3 },
    { D_ovl0B_04_80048B98, 192, 62, 0.6f, 0.6f, 5, 5 },
    { D_ovl0B_04_80048A20, 97, 184, 0.65f, 0.65f, 7, 0 },
    { D_ovl0B_04_800489F0 + 0x20, 127, 39, 0.9f, 0.9f, 7, 0 },
};
Item D_ovl0B_04_80049854[11] = {
    { D_ovl0B_04_800489F0 + 0x28, 125, 35, 0.9f, 0.9f, 0, 0 },
    { D_ovl0B_04_80048B98 + 0x1B0, 172, 82, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x1BC, 172, 102, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x1C8, 172, 122, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x1D4, 172, 142, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B98 + 0x1E4, 172, 162, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048B88 + 0x8, 180, 197, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048A20, 93, 180, 0.65f, 0.65f, 2, 3 },
    { D_ovl0B_04_80048B98, 192, 62, 0.6f, 0.6f, 5, 5 },
    { D_ovl0B_04_80048A20, 97, 184, 0.65f, 0.65f, 7, 0 },
    { D_ovl0B_04_800489F0 + 0x28, 129, 39, 0.9f, 0.9f, 7, 0 },
};
Item D_ovl0B_04_80049930[6] = {
    { D_ovl0B_04_80048A2C, 80, 60, 0.9f, 0.9f, 0, 0 },
    { D_ovl0B_04_80048A2C + 0x1C, 100, 140, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048A2C + 0x24, 170, 140, 0.6f, 0.6f, 1, 3 },
    { D_ovl0B_04_80048A2C + 0x10, 100, 120, 0.6f, 0.6f, 2, 2 },
    { D_ovl0B_04_80048A20, 93, 180, 0.65f, 0.65f, 2, 3 },
    { D_ovl0B_04_80048A20, 97, 184, 0.65f, 0.65f, 7, 0 },
};
Nav D_ovl0B_04_800499A8[2] = {
    { 87, 148, 0, 0, 0, 2 },
    { 157, 148, 0, 0, 1, 0 },
};
Page D_ovl0B_04_800499B8[10] = {
    { 9, D_ovl0B_04_8004A2A8, &D_ovl0B_04_8004922C[0], func_ovl0B_04_80044BE8, &D_ovl0B_04_800492E0[0], 0, 304, 16, 16, 1, func_ovl0B_04_800444E8 },
    { 2, D_ovl0B_04_8004A2D0, &D_ovl0B_04_800493BC[5], func_ovl0B_04_80045AF0, &D_ovl0B_04_80048DCC[0], 0, 65, 22, 22, 2, func_ovl0B_04_800459C4 },
    { 2, D_ovl0B_04_8004A2D8, &D_ovl0B_04_800493BC[7], func_ovl0B_04_80045D20, &D_ovl0B_04_80048DCC[0], 0, 65, 22, 22, 2, func_ovl0B_04_80045BF4 },
    { 2, D_ovl0B_04_8004A2E0, &D_ovl0B_04_800493BC[9], func_ovl0B_04_80045F50, &D_ovl0B_04_80048DCC[0], 0, 65, 22, 22, 2, func_ovl0B_04_80045E24 },
    { 2, D_ovl0B_04_8004A2E8, &D_ovl0B_04_800493BC[11], func_ovl0B_04_80046180, &D_ovl0B_04_80048DCC[0], 0, 65, 22, 22, 2, func_ovl0B_04_80046054 },
    { 11, &D_ovl0B_04_8004A2E8[2], &D_ovl0B_04_80049560[0], func_ovl0B_04_80046B28, &D_ovl0B_04_8004963C[0], 0, 304, 16, 16, 2, func_ovl0B_04_80046AA0 },
    { 11, &D_ovl0B_04_8004A2E8[14], &D_ovl0B_04_8004969C[0], func_ovl0B_04_80046D74, &D_ovl0B_04_8004963C[0], 0, 304, 16, 16, 2, func_ovl0B_04_80046CEC },
    { 11, &D_ovl0B_04_8004A2E8[26], &D_ovl0B_04_80049778[0], func_ovl0B_04_80046FA8, &D_ovl0B_04_8004963C[0], 0, 304, 16, 16, 2, func_ovl0B_04_80046F20 },
    { 11, &D_ovl0B_04_8004A2E8[38], &D_ovl0B_04_80049854[0], func_ovl0B_04_800471F4, &D_ovl0B_04_8004963C[0], 0, 304, 16, 16, 2, func_ovl0B_04_8004716C },
    { 6, D_ovl0B_04_8004A3B0, &D_ovl0B_04_80049930[0], func_ovl0B_04_80045214, &D_ovl0B_04_800499A8[0], 0, 304, 16, 16, 1, func_ovl0B_04_800450C0 },
};
Fade D_ovl0B_04_80049B20[5] = {
    { NULL, 30, 150, 0, 100, 5.0f, 135.0f, 10.0f, 0.44f, 110, 10, 161, 133, 0.0f },
    { NULL, 160, 190, 0, 100, 5.0f, 135.0f, 10.0f, 0.44f, 110, 10, 161, 133, 0.0f },
    { NULL, 30, 0, 200, 100, 5.0f, 135.0f, 10.0f, 0.44f, 110, 10, 161, 133, 0.0f },
    { NULL, 140, 20, 200, 100, 5.0f, 135.0f, 10.0f, 0.44f, 110, 10, 161, 133, 0.0f },
    { NULL, 50, 50, 50, 120, 5.0f, 160.0f, 5.0f, 0.75f, 110, 10, 160, 120, 0.0f },
};
Desc D_ovl0B_04_80049C38[11] = {
    { 32.0f, 32.0f, 67, 2, 0, 1024 },
    { 64.0f, 11.0f, 67, 0, 1, 1024 },
    { 24.0f, 24.0f, 67, 4, 0, 0 },
    { 24.0f, 24.0f, 67, 6, 0, 0 },
    { 48.0f, 24.0f, 67, 16, 0, 0 },
    { 48.0f, 24.0f, 67, 14, 0, 0 },
    { 24.0f, 2.0f, 67, 18, 2, 0 },
    { 276.0f, 200.0f, 67, 20, 2, 1152 },
    { 20.0f, 20.0f, 57, 0, 0, 0 },
    { 20.0f, 20.0f, 57, 2, 0, 0 },
    { 18.0f, 24.0f, 67, 8, 0, 0 },
};
Entry D_ovl0B_04_80049D40[20] = {
    { NULL, 0.0f, 0.0f, 64.0f, 60.0f },
    { NULL, 64.0f, 0.0f, 128.0f, 60.0f },
    { NULL, 128.0f, 0.0f, 192.0f, 60.0f },
    { NULL, 192.0f, 0.0f, 256.0f, 60.0f },
    { NULL, 256.0f, 0.0f, 320.0f, 60.0f },
    { NULL, 0.0f, 60.0f, 64.0f, 120.0f },
    { NULL, 64.0f, 60.0f, 128.0f, 120.0f },
    { NULL, 128.0f, 60.0f, 192.0f, 120.0f },
    { NULL, 192.0f, 60.0f, 256.0f, 120.0f },
    { NULL, 256.0f, 60.0f, 320.0f, 120.0f },
    { NULL, 0.0f, 120.0f, 64.0f, 180.0f },
    { NULL, 64.0f, 120.0f, 128.0f, 180.0f },
    { NULL, 128.0f, 120.0f, 192.0f, 180.0f },
    { NULL, 192.0f, 120.0f, 256.0f, 180.0f },
    { NULL, 256.0f, 120.0f, 320.0f, 180.0f },
    { NULL, 0.0f, 180.0f, 64.0f, 240.0f },
    { NULL, 64.0f, 180.0f, 128.0f, 240.0f },
    { NULL, 128.0f, 180.0f, 192.0f, 240.0f },
    { NULL, 192.0f, 180.0f, 256.0f, 240.0f },
    { NULL, 256.0f, 180.0f, 320.0f, 240.0f },
};
Entry D_ovl0B_04_80049ED0[20] = {
    { NULL, 0.0f, 10.0f, 64.0f, 21.0f },
    { NULL, 64.0f, 42.0f, 128.0f, 53.0f },
    { NULL, 128.0f, 10.0f, 192.0f, 21.0f },
    { NULL, 192.0f, 42.0f, 256.0f, 53.0f },
    { NULL, 256.0f, 10.0f, 320.0f, 21.0f },
    { NULL, 0.0f, 74.0f, 64.0f, 85.0f },
    { NULL, 64.0f, 106.0f, 128.0f, 117.0f },
    { NULL, 128.0f, 74.0f, 192.0f, 85.0f },
    { NULL, 192.0f, 106.0f, 256.0f, 117.0f },
    { NULL, 256.0f, 74.0f, 320.0f, 85.0f },
    { NULL, 0.0f, 138.0f, 64.0f, 149.0f },
    { NULL, 64.0f, 170.0f, 128.0f, 181.0f },
    { NULL, 128.0f, 138.0f, 192.0f, 149.0f },
    { NULL, 192.0f, 170.0f, 256.0f, 181.0f },
    { NULL, 256.0f, 138.0f, 320.0f, 149.0f },
    { NULL, 0.0f, 202.0f, 64.0f, 213.0f },
    { NULL, 64.0f, 234.0f, 128.0f, 245.0f },
    { NULL, 128.0f, 202.0f, 192.0f, 213.0f },
    { NULL, 192.0f, 234.0f, 256.0f, 245.0f },
    { NULL, 256.0f, 202.0f, 320.0f, 213.0f },
};
Entry D_ovl0B_04_8004A060[13] = {
    { NULL, 50.0f, 192.0f, 74.0f, 216.0f },
    { NULL, 205.0f, 25.0f, 219.0f, 39.0f },
    { NULL, 220.0f, 162.0f, 264.0f, 186.0f },
    { NULL, 220.0f, 162.0f, 264.0f, 186.0f },
    { NULL, 120.0f, 70.0f, 140.0f, 73.0f },
    { NULL, 180.0f, 25.0f, 190.0f, 37.0f },
    { NULL, 210.0f, 25.0f, 220.0f, 37.0f },
    { NULL, 240.0f, 25.0f, 250.0f, 37.0f },
    { NULL, 97.0f, 194.0f, 112.0f, 211.0f },
    { NULL, 134.0f, 194.0f, 149.0f, 211.0f },
    { NULL, 170.0f, 62.0f, 184.0f, 76.0f },
    { NULL, 255.0f, 62.0f, 269.0f, 76.0f },
    { NULL, 24.0f, 20.0f, 300.0f, 220.0f },
};

Obj *D_ovl0B_04_8004A164 = NULL;
s32 D_ovl0B_04_8004A168 = 0; /* the page; 0xFF ends the screen */
s32 D_ovl0B_04_8004A16C = 0; /* the page's first item */
s32 D_ovl0B_04_8004A170 = -1;
u8 D_ovl0B_04_8004A174 = 0;  /* the item under the cursor */
s32 *D_ovl0B_04_8004A178 = NULL;
s32 *D_ovl0B_04_8004A17C = NULL;
s32 *D_ovl0B_04_8004A180 = NULL;
s32 *D_ovl0B_04_8004A184 = NULL;
u8 *D_ovl0B_04_8004A188 = NULL;
s32 D_ovl0B_04_8004A18C = 0;
s32 D_ovl0B_04_8004A190 = 0;
s32 D_ovl0B_04_8004A194 = 0;
s32 D_ovl0B_04_8004A198 = 0;
s32 D_ovl0B_04_8004A19C = 0;
s32 D_ovl0B_04_8004A1A0 = 0;
s32 D_ovl0B_04_8004A1A4 = 0;
s32 D_ovl0B_04_8004A1A8 = 0;
s32 D_ovl0B_04_8004A1AC[14] = { 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1 };
s32 D_ovl0B_04_8004A1E4 = 0;

static void func_ovl0B_04_80043050(Entry *e, Desc *d);
static void func_ovl0B_04_800438FC(u32 mode, Item *it, s32 id);
static void func_ovl0B_04_80043A24(Item *items, s32 *ids, s32 n);
static void func_ovl0B_04_80043A7C(Item *items, s32 *ids, s32 n);
void func_ovl0B_04_80043CD0(s32 arg0, Gfx0B04 **arg1);
static void func_ovl0B_04_80043FA4(u8 *ret, s32 page, s32 item, s32 mode);
static void func_ovl0B_04_8004401C(Fade *f);
static void func_ovl0B_04_800440C8(Fade *f);
static void func_ovl0B_04_80044154(void);
static void func_ovl0B_04_800441C4(void);
static void func_ovl0B_04_80044210(void);
static u8 func_ovl0B_04_8004426C(u8 set, u8 idx);
static void func_ovl0B_04_8004430C(u8 item);
static void func_ovl0B_04_80044394(s32 a, s32 b);
static void func_ovl0B_04_8004447C(s32 id, s32 alpha);
static void func_ovl0B_04_8004456C(void);
static void func_ovl0B_04_800445C4(void);
static u8 func_ovl0B_04_8004462C(u8 set, u8 c);
static u8 func_ovl0B_04_8004471C(u8 set, u8 c);
static void func_ovl0B_04_800447DC(u16 buttons, u8 *ret);
static void func_ovl0B_04_80046294(u8 item);
static void func_ovl0B_04_80046600(u16 buttons, u8 item);
static void func_ovl0B_04_80046734(u16 buttons, u8 item);
static void func_ovl0B_04_800468F0(s32 base);
static void func_ovl0B_04_80045540(u8 item, u16 buttons, u8 *ret);
static void func_ovl0B_04_800458F4(s32 *ids);
static void func_ovl0B_04_80045958(s32 *ids);
static void func_ovl0B_04_80045850(void);
static void func_ovl0B_04_80043640(f32 d);
static u8 func_ovl0B_04_Mark27(u8 set, u8 c);

static void func_ovl0B_04_800436C0(void) {
}

static void func_ovl0B_04_800438F4(void) {
}

static void func_ovl0B_04_80043AD4(void) {
}

static void func_ovl0B_04_80043F3C(void) {
}

static void func_ovl0B_04_80043F44(void) {
}

static void func_ovl0B_04_80043F4C(void) {
}

static void func_ovl0B_04_80043F54(void) {
}

static void func_ovl0B_04_80043F5C(void) {
}

static void func_ovl0B_04_80043F64(void) {
}

static void func_ovl0B_04_80043F6C(void) {
}

static void func_ovl0B_04_80043F74(void) {
}

static void func_ovl0B_04_80043F7C(void) {
}

static void func_ovl0B_04_80043F84(void) {
}

static void func_ovl0B_04_80043F8C(void) {
}

static void func_ovl0B_04_80043F94(void) {
}

static void func_ovl0B_04_80043F9C(void) {
}

static void func_ovl0B_04_800441BC(void) {
}

static void func_ovl0B_04_80044264(void) {
}

static void func_ovl0B_04_800442FC(void) {
}

static void func_ovl0B_04_80044304(void) {
}

static void func_ovl0B_04_80044384(void) {
}

static void func_ovl0B_04_8004438C(void) {
}

static void func_ovl0B_04_800444D0(void) {
}

static void func_ovl0B_04_800444D8(void) {
}

static void func_ovl0B_04_800444E0(void) {
}

static void func_ovl0B_04_800445BC(void) {
}

static void func_ovl0B_04_8004461C(void) {
}

static void func_ovl0B_04_80044624(void) {
}

static void func_ovl0B_04_80044714(void) {
}

static void func_ovl0B_04_800450B8(void) {
}

static void func_ovl0B_04_80045530(void) {
}

static void func_ovl0B_04_80045538(void) {
}

static void func_ovl0B_04_80045848(void) {
}

static void func_ovl0B_04_80046284(void) {
}

static void func_ovl0B_04_8004628C(void) {
}

static void func_ovl0B_04_800468E0(void) {
}

static void func_ovl0B_04_800468E8(void) {
}

static void func_ovl0B_04_80046CE4(void) {
}

static void func_ovl0B_04_80046F18(void) {
}

static void func_ovl0B_04_80047164(void) {
}

/* The objects of a run of entries, and their removal (inlined). */
static void func_ovl0B_04_MakeEntries(Entry *e, s32 n, Desc *d) {
    Entry *p;

    for (p = e; p < e + n; p++) {
        func_ovl0B_04_80043050(p, d);
    }
}

static void func_ovl0B_04_FreeEntries(Entry *e, s32 n) {
    Entry *p;

    for (p = e; p < e + n; p++) {
        func_ovl0B_04_80047DE0(p->unk0);
    }
}

/* An item of the current page lit (mode 1) or not (0); 6 past the list. */
static void func_ovl0B_04_PageItem(u32 mode, u8 item, s32 half) {
    s32 i;

    if (item < 11) {
        i = item - half * 5;
    } else {
        i = 6;
    }
    func_ovl0B_04_800438FC(mode, &D_ovl0B_04_8004A404->unk8[i], D_ovl0B_04_8004A404->unk4[i]);
}

/* A text set to a string, colour and scale (inlined in the set-ups). */
static void func_ovl0B_04_SetText(s32 id, u8 *str, s32 col, f32 scale) {
    func_ovl0B_04_80048640(id, str, col);
    func_ovl0B_04_80048658(id, scale, scale);
}

/* Pages 5-8: one of a slot's ten choices (ZeroJump 0x1E04 says which are
 * open), in two halves of five. */
u8 func_ovl0B_04_800471F4(u8 arg0, u16 arg1) {
    u8 ret = 1;
    u8 pad[0x30];
    Entry *p;

    func_ovl0B_04_80046734(arg1, arg0);
    if (arg1 & 1) {
        if (arg0 >= 11) {
            func_ovl0B_04_80047E70(D_ovl0B_04_8004A170, 10, -1);
            func_ovl0B_04_80047E70(D_ovl0B_04_8004A170, 12, -1);
            *D_ovl0B_04_8004A184 = 0;
            func_ovl0B_04_800487D0(2);
        } else if (D_ovl0B_04_8004A480[arg0] != 0) {
            func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 3, arg0);
            func_ovl0B_04_800487D0(0x2E);
            *D_ovl0B_04_8004A184 = arg0;
        }
    } else if (arg1 & 2) {
        func_ovl0B_04_800487D0(2);
        func_ovl0B_04_80043FA4(&ret, 0, 5, 0);
        for (p = &D_ovl0B_04_8004A060[10]; p < &D_ovl0B_04_8004A060[10] + 1; p++) {
            func_ovl0B_04_80047DE0(p->unk0);
        }
        for (p = &D_ovl0B_04_8004A060[11]; p < &D_ovl0B_04_8004A060[11] + 1; p++) {
            func_ovl0B_04_80047DE0(p->unk0);
        }
    }
    return ret;
}

void func_ovl0B_04_8004716C(Obj *arg0) {
    func_ovl0B_04_800468F0(33);
    if (0) {
        func_ovl0B_04_80047164();
    }
}

u8 func_ovl0B_04_80046FA8(u8 arg0, u16 arg1) {
    u8 ret = 1;
    u8 pad[0x30];
    Entry *p;

    func_ovl0B_04_80046734(arg1, arg0);
    if (arg1 & 1) {
        if (arg0 >= 11) {
            func_ovl0B_04_80047E70(D_ovl0B_04_8004A170, 3, -1);
            func_ovl0B_04_80047E70(D_ovl0B_04_8004A170, 5, -1);
            *D_ovl0B_04_8004A180 = 0;
            func_ovl0B_04_800487D0(2);
        } else if (D_ovl0B_04_8004A480[arg0] != 0) {
            func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 2, arg0);
            func_ovl0B_04_800487D0(0x2E);
            *D_ovl0B_04_8004A180 = arg0;
        }
    } else if (arg1 & 2) {
        func_ovl0B_04_800487D0(2);
        func_ovl0B_04_80043FA4(&ret, 0, 4, 0);
        for (p = &D_ovl0B_04_8004A060[10]; p < &D_ovl0B_04_8004A060[10] + 1; p++) {
            func_ovl0B_04_80047DE0(p->unk0);
        }
        for (p = &D_ovl0B_04_8004A060[11]; p < &D_ovl0B_04_8004A060[11] + 1; p++) {
            func_ovl0B_04_80047DE0(p->unk0);
        }
    }
    return ret;
}

void func_ovl0B_04_80046F20(Obj *arg0) {
    func_ovl0B_04_800468F0(22);
    if (0) {
        func_ovl0B_04_80046F18();
    }
}

u8 func_ovl0B_04_80046D74(u8 arg0, u16 arg1) {
    u8 ret = 1;
    u8 pad[0x30];
    Entry *p;

    func_ovl0B_04_80046734(arg1, arg0);
    if (arg1 & 1) {
        if (arg0 >= 11) {
            func_ovl0B_04_80047E70(D_ovl0B_04_8004A170, 1, -1);
            *D_ovl0B_04_8004A17C = 0;
            func_ovl0B_04_800487D0(2);
        } else if (D_ovl0B_04_8004A480[arg0] != 0) {
            func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 1, arg0);
            func_ovl0B_04_800487D0(0x2E);
            *D_ovl0B_04_8004A17C = arg0;
        }
    } else if (arg1 & 2) {
        func_ovl0B_04_800487D0(2);
        func_ovl0B_04_80043FA4(&ret, 0, 3, 0);
        for (p = &D_ovl0B_04_8004A060[10]; p < &D_ovl0B_04_8004A060[10] + 1; p++) {
            func_ovl0B_04_80047DE0(p->unk0);
        }
        for (p = &D_ovl0B_04_8004A060[11]; p < &D_ovl0B_04_8004A060[11] + 1; p++) {
            func_ovl0B_04_80047DE0(p->unk0);
        }
    }
    return ret;
}

void func_ovl0B_04_80046CEC(Obj *arg0) {
    func_ovl0B_04_800468F0(11);
    if (0) {
        func_ovl0B_04_80046CE4();
    }
}

u8 func_ovl0B_04_80046B28(u8 arg0, u16 arg1) {
    u8 ret = 1;

    func_ovl0B_04_80046734(arg1, arg0);
    if (arg1 & 1) {
        if (arg0 >= 11) {
            func_ovl0B_04_80047E70(D_ovl0B_04_8004A170, 6, -1);
            func_ovl0B_04_80047E70(D_ovl0B_04_8004A170, 8, -1);
            *D_ovl0B_04_8004A178 = 0;
            func_ovl0B_04_800487D0(2);
        } else if (D_ovl0B_04_8004A480[arg0] != 0) {
            func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 0, arg0);
            func_ovl0B_04_800487D0(0x2E);
            *D_ovl0B_04_8004A178 = arg0;
        }
    } else if (arg1 & 2) {
        func_ovl0B_04_800487D0(2);
        func_ovl0B_04_80043FA4(&ret, 0, 2, 0);
        func_ovl0B_04_FreeEntries(&D_ovl0B_04_8004A060[10], 1);
        func_ovl0B_04_FreeEntries(&D_ovl0B_04_8004A060[11], 1);
    }
    return ret;
}

void func_ovl0B_04_80046AA0(Obj *arg0) {
    func_ovl0B_04_800468F0(0);
    if (0) {
        func_ovl0B_04_800468E8();
        func_ovl0B_04_800468F0(0);
        func_ovl0B_04_800468E0();
        func_ovl0B_04_8004628C();
        func_ovl0B_04_80046734(0, 0);
        func_ovl0B_04_80046600(0, 0);
        func_ovl0B_04_80046294(0);
        func_ovl0B_04_80046284();
    }
}

/* Pages 5-8's set-up: which of the ten choices from base + 1 are open. */
static void func_ovl0B_04_800468F0(s32 base) {
    Obj *o;
    s32 i;

    D_ovl0B_04_8004A404 = &D_ovl0B_04_800499B8[D_ovl0B_04_8004A168];
    func_ovl0B_04_80044394(D_ovl0B_04_8004A404->unk4[7], D_ovl0B_04_8004A404->unk4[9]);
    o = func_ovl0B_04_80048668(D_ovl0B_04_8004A404->unk4[10]);
    o->unkC |= 0x480;
    o->unk36 = 100;
    D_ovl0B_04_8004A480[0] = 0;
    for (i = 11; i < 13; i++) {
        D_ovl0B_04_8004A480[i] = 1;
    }
    for (i = 1; i < 11; i++) {
        if (func_ovl0B_04_800484B0(base + i) == 0) {
            D_ovl0B_04_8004A480[i] = 0;
        } else {
            D_ovl0B_04_8004A480[i] = 1;
        }
    }
    func_ovl0B_04_MakeEntries(&D_ovl0B_04_8004A060[10], 1, &D_ovl0B_04_80049C38[8]);
    func_ovl0B_04_MakeEntries(&D_ovl0B_04_8004A060[11], 1, &D_ovl0B_04_80049C38[9]);
    D_ovl0B_04_8004A1A8 = 0;
    D_ovl0B_04_8004A1A4 = 0;
    D_ovl0B_04_8004A174 = D_ovl0B_04_8004A16C;
    func_ovl0B_04_80046294(D_ovl0B_04_8004A16C);
    func_ovl0B_04_80046600(0, D_ovl0B_04_8004A16C);
    o = func_ovl0B_04_80048608();
    o->unk36 = 0;
    o->unkC |= 0x80;
}

/* Pages 5-8's cursor. */
static void func_ovl0B_04_80046734(u16 buttons, u8 item) {
    s32 i;

    if ((buttons & 0x20) || (buttons & 0x40)) {
        if (D_ovl0B_04_8004A174 < 11) {
            i = D_ovl0B_04_8004A174 - D_ovl0B_04_8004A1A4 * 5;
        } else {
            i = 6;
        }
        func_ovl0B_04_800438FC(0, &D_ovl0B_04_8004A404->unk8[i], D_ovl0B_04_8004A404->unk4[i]);
        if (item < 11) {
            i = item - D_ovl0B_04_8004A1A8 * 5;
        } else {
            i = 6;
        }
        func_ovl0B_04_800438FC(1, &D_ovl0B_04_8004A404->unk8[i], D_ovl0B_04_8004A404->unk4[i]);
    }
    if ((buttons & 0x80) || (buttons & 0x100)) {
        func_ovl0B_04_80046600(buttons, item);
    }
    D_ovl0B_04_8004A174 = item;
}

/* Pages 5-8: the other half of the choices, and its arrows. */
static void func_ovl0B_04_80046600(u16 buttons, u8 item) {
    if (D_ovl0B_04_8004A1A8 == 0 && (buttons & 0x100)) {
        D_ovl0B_04_8004A1A4 = D_ovl0B_04_8004A1A8;
        D_ovl0B_04_8004A1A8++;
        func_ovl0B_04_80046294(item);
        D_ovl0B_04_8004A1A4 = D_ovl0B_04_8004A1A8;
    } else if (D_ovl0B_04_8004A1A8 == 1 && (buttons & 0x80)) {
        D_ovl0B_04_8004A1A4 = D_ovl0B_04_8004A1A8;
        D_ovl0B_04_8004A1A8--;
        func_ovl0B_04_80046294(item);
        D_ovl0B_04_8004A1A4 = D_ovl0B_04_8004A1A8;
    }
    switch (D_ovl0B_04_8004A1A8) {
        case 0:
            D_ovl0B_04_8004A060[10].unk0->unkC |= 1;
            D_ovl0B_04_8004A060[11].unk0->unkC &= ~1;
            break;
        case 1:
            D_ovl0B_04_8004A060[10].unk0->unkC &= ~1;
            D_ovl0B_04_8004A060[11].unk0->unkC |= 1;
            break;
    }
}

/* Pages 5-8: the half's five choices written ("---" for a closed one). */
static void func_ovl0B_04_80046294(u8 item) {
    s32 i;
    s32 j;
    u8 *str;
    Item *it;

    D_ovl0B_04_80048B98[5] = D_ovl0B_04_8004A1A8 + 0x11;
    func_ovl0B_04_80048690(D_ovl0B_04_8004A404->unk4[8], D_ovl0B_04_80048B98, 5);
    for (j = 0, i = D_ovl0B_04_8004A1A8 * 5; i < D_ovl0B_04_8004A1A8 * 5 + 5; i++, j++) {
        it = &D_ovl0B_04_8004A404->unk8[j + 1];
        if (D_ovl0B_04_8004A480[i + 1] == 0) {
            str = D_ovl0B_04_80048B88;
        } else {
            str = D_ovl0B_04_800494C0[D_ovl0B_04_8004A168 - 5][i];
        }
        D_ovl0B_04_8004A40C[j] = func_ovl0B_04_80048688(
            str, it->unk4 - (s32) (func_ovl0B_04_80048680(str) * 0.6f / 2.0f) + 40, it->unk6, it->unk8, it->unkC, 1);
        it->unk0 = str;
    }
    for (j = 0, i = D_ovl0B_04_8004A1A8 * 5; i < D_ovl0B_04_8004A1A8 * 5 + 5; i++, j++) {
        func_ovl0B_04_80048638(D_ovl0B_04_8004A404->unk4[j + 1]);
        D_ovl0B_04_8004A404->unk4[j + 1] = D_ovl0B_04_8004A40C[j];
    }
    func_ovl0B_04_PageItem(3, item, D_ovl0B_04_8004A1A8);
}

/* Pages 1-4: the character sets; the R button goes to the next. */
u8 func_ovl0B_04_80046180(u8 arg0, u16 arg1) {
    u8 ret = 1;

    if (arg1 & 0x10) {
        D_ovl0B_04_8004A490.unk2 = 3;
        func_ovl0B_04_800487D0(0);
        func_ovl0B_04_80043FA4(&ret, 3, arg0, 0);
    } else {
        func_ovl0B_04_80045540(arg0, arg1, &ret);
    }
    if (ret == 0) {
        func_ovl0B_04_800458F4(D_ovl0B_04_8004A2E8);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[3]);
    }
    return ret;
}

void func_ovl0B_04_80046054(Obj *arg0) {
    func_ovl0B_04_800458F4(D_ovl0B_04_8004A2E8);
    func_ovl0B_04_80047DF0(arg0, 0x55);
    func_ovl0B_04_8004401C(&D_ovl0B_04_80049B20[3]);
    func_ovl0B_04_80045850();
    func_ovl0B_04_80045958(D_ovl0B_04_8004A2E8);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[4], D_ovl0B_04_80048A84, 5, 0.7f);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[3], D_ovl0B_04_80048A80, 6, 0.5f);
}

u8 func_ovl0B_04_80045F50(u8 arg0, u16 arg1) {
    u8 ret = 1;

    if (arg1 & 0x10) {
        D_ovl0B_04_8004A490.unk2 = 4;
        func_ovl0B_04_800487D0(0);
        func_ovl0B_04_80043FA4(&ret, 4, arg0, 0);
    } else {
        func_ovl0B_04_80045540(arg0, arg1, &ret);
    }
    if (ret == 0) {
        func_ovl0B_04_800458F4((s32 *) D_ovl0B_04_8004A2E0[0]);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[2]);
    }
    return ret;
}

void func_ovl0B_04_80045E24(Obj *arg0) {
    func_ovl0B_04_800458F4(D_ovl0B_04_8004A2E0);
    func_ovl0B_04_80047DF0(arg0, 0x55);
    func_ovl0B_04_8004401C(&D_ovl0B_04_80049B20[2]);
    func_ovl0B_04_80045850();
    func_ovl0B_04_80045958(D_ovl0B_04_8004A2E0);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[3], D_ovl0B_04_80048A80, 5, 0.7f);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[4], D_ovl0B_04_80048A84, 6, 0.5f);
}

u8 func_ovl0B_04_80045D20(u8 arg0, u16 arg1) {
    u8 ret = 1;

    if (arg1 & 0x10) {
        D_ovl0B_04_8004A490.unk2 = 3;
        func_ovl0B_04_800487D0(0);
        func_ovl0B_04_80043FA4(&ret, 3, arg0, 0);
    } else {
        func_ovl0B_04_80045540(arg0, arg1, &ret);
    }
    if (ret == 0) {
        func_ovl0B_04_800458F4(D_ovl0B_04_8004A2D8);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[1]);
    }
    return ret;
}

void func_ovl0B_04_80045BF4(Obj *arg0) {
    func_ovl0B_04_800458F4(D_ovl0B_04_8004A2D8);
    func_ovl0B_04_80047DF0(arg0, 0x55);
    func_ovl0B_04_8004401C(&D_ovl0B_04_80049B20[1]);
    func_ovl0B_04_80045850();
    func_ovl0B_04_80045958(D_ovl0B_04_8004A2D8);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[2], D_ovl0B_04_80048A7C, 5, 0.7f);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[1], D_ovl0B_04_80048A78, 6, 0.5f);
}

u8 func_ovl0B_04_80045AF0(u8 arg0, u16 arg1) {
    u8 ret = 1;

    if (arg1 & 0x10) {
        D_ovl0B_04_8004A490.unk2 = 2;
        func_ovl0B_04_800487D0(0);
        func_ovl0B_04_80043FA4(&ret, 2, arg0, 0);
    } else {
        func_ovl0B_04_80045540(arg0, arg1, &ret);
    }
    if (ret == 0) {
        func_ovl0B_04_800458F4(D_ovl0B_04_8004A2D0);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[0]);
    }
    return ret;
}

void func_ovl0B_04_800459C4(Obj *arg0) {
    func_ovl0B_04_800458F4(D_ovl0B_04_8004A2D0);
    func_ovl0B_04_80047DF0(arg0, 0x55);
    func_ovl0B_04_8004401C(&D_ovl0B_04_80049B20[0]);
    func_ovl0B_04_80045850();
    func_ovl0B_04_80045958(D_ovl0B_04_8004A2D0);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[1], D_ovl0B_04_80048A78, 5, 0.7f);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[4], D_ovl0B_04_80048A84, 6, 0.5f);
    if (0) {
        func_ovl0B_04_80045958(0);
        func_ovl0B_04_800458F4(0);
        func_ovl0B_04_80045850();
        func_ovl0B_04_80045848();
        func_ovl0B_04_80045540(0, 0, 0);
        func_ovl0B_04_80045538();
        func_ovl0B_04_80045530();
    }
}

/* A page's two texts and the menu's cursor shown, and hidden. */
static void func_ovl0B_04_80045958(s32 *ids) {
    Obj *a = func_ovl0B_04_80048668(ids[0]);
    Obj *b = func_ovl0B_04_80048668(ids[1]);
    Obj *c = func_ovl0B_04_80048608();

    a->unkC &= ~1;
    b->unkC &= ~1;
    c->unkC &= ~1;
}

static void func_ovl0B_04_800458F4(s32 *ids) {
    Obj *a = func_ovl0B_04_80048668(ids[0]);
    Obj *b = func_ovl0B_04_80048668(ids[1]);
    Obj *c = func_ovl0B_04_80048608();

    a->unkC |= 1;
    b->unkC |= 1;
    c->unkC |= 1;
}

static void func_ovl0B_04_80045850(void) {
    s32 i;
    u8 ret;

    for (i = 2; i < 7; i++) {
        D_ovl0B_04_80049C38[i].unk14 &= ~1;
    }
    func_ovl0B_04_8004430C(D_ovl0B_04_8004A490.unk3);
    func_ovl0B_04_800447DC(0, &ret);
    func_ovl0B_04_8004456C();
}

/* Pages 1-4: B rubs a character out, A writes the one under the cursor or
 * (items 0x31 and 0x32) ends the name. */
static void func_ovl0B_04_80045540(u8 item, u16 buttons, u8 *ret) {
    s32 i;
    u8 *p;
    u8 c;

    if (buttons & 2) {
        p = D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0];
        c = p[0];
        D_ovl0B_04_8004A490.unk1 = 0;
        p[0] = 0;
        if ((D_ovl0B_04_8004A490.unk0 == 7 && c == 0) || (D_ovl0B_04_8004A490.unk0 != 7 && D_ovl0B_04_8004A490.unk0 > 0)) {
            D_ovl0B_04_8004A490.unk0--;
        }
        func_ovl0B_04_80044210();
        func_ovl0B_04_80044154();
        func_ovl0B_04_800487D0(2);
    } else {
        func_ovl0B_04_8004430C(item);
        if (buttons & 1) {
            if (item == 0x31 || item == 0x32) {
                func_ovl0B_04_800487D0(1);
                func_ovl0B_04_80043FA4(ret, 0, 1, 1);
                D_ovl0B_04_8004A164->unk20 = 0.0f;
                for (i = 0; i < 8; i++) {
                    if (D_ovl0B_04_80048A20[i] != D_ovl0B_04_8004A290[i][0]) {
                        D_ovl0B_04_8004A18C = 1;
                    }
                    D_ovl0B_04_80048A20[i] = D_ovl0B_04_8004A290[i][0];
                }
                for (i = 0; i < 8; i++) {
                    func_ovl0B_04_80048638(D_ovl0B_04_8004A448[i]);
                }
                for (i = 0; i < 6; i++) {
                    func_ovl0B_04_80048638(D_ovl0B_04_8004A468[i]);
                }
                for (i = 0; i < 5; i++) {
                    func_ovl0B_04_80047DE0(D_ovl0B_04_8004A060[i].unk0);
                }
                func_ovl0B_04_FreeEntries(&D_ovl0B_04_8004A060[5], 3);
                func_ovl0B_04_FreeEntries(&D_ovl0B_04_8004A060[8], 2);
            } else {
                D_ovl0B_04_8004A490.unk1 = func_ovl0B_04_8004426C(D_ovl0B_04_8004A490.unk2, item);
                D_ovl0B_04_8004A490.unk3 = item;
                func_ovl0B_04_80044210();
                D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0][0] = D_ovl0B_04_8004A490.unk1;
                D_ovl0B_04_8004A490.unk0++;
                D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0][0] = 0;
                func_ovl0B_04_800487D0(1);
                if (D_ovl0B_04_8004A490.unk0 == 8) {
                    D_ovl0B_04_8004A490.unk0--;
                    D_ovl0B_04_8004A490.unk1 = 0;
                    func_ovl0B_04_800441C4();
                    func_ovl0B_04_800485F8(D_ovl0B_04_8004A490.unk3);
                    func_ovl0B_04_8004430C(D_ovl0B_04_8004A490.unk3);
                }
            }
        }
    }
    func_ovl0B_04_800447DC(buttons, ret);
    func_ovl0B_04_8004456C();
}

/* Page 9: save the changes or not. */
u8 func_ovl0B_04_80045214(u8 arg0, u16 arg1) {
    u8 ret = 1;
    s32 ok;
    u8 *save;
    s32 id;
    s32 id2;
    s32 i;

    if ((arg1 & 0x80) || (arg1 & 0x100)) {
        func_ovl0B_04_800438FC(0, &D_ovl0B_04_80049930[D_ovl0B_04_8004A174], D_ovl0B_04_8004A3B0[D_ovl0B_04_8004A174]);
        func_ovl0B_04_800438FC(1, &D_ovl0B_04_80049930[arg0], D_ovl0B_04_8004A3B0[arg0]);
        D_ovl0B_04_8004A174 = arg0;
    }
    if (arg1 & 1) {
        if (arg0 == 1) {
            ok = 1;
            save = D_ovl0B_04_8004A188;
            func_ovl0B_04_8004447C(D_ovl0B_04_8004A3B0[4], 0);
            func_ovl0B_04_8004447C(D_ovl0B_04_8004A3B0[5], 0);
            id = func_ovl0B_04_80048688(D_ovl0B_04_80048A54, 100, 175, 0.8f, 0.8f, 2);
            func_ovl0B_04_80048268(3);
            for (i = 0; i < 8; i++) {
                save[i] = D_ovl0B_04_80048A20[i];
            }
            save[8] = 0;
            if (func_ovl0B_04_80048910(save) != 0) {
                func_ovl0B_04_800487D0(0x18);
                func_ovl0B_04_8004447C(id, 0);
                id2 = func_ovl0B_04_80048688(D_ovl0B_04_80048A60, 80, 175, 0.8f, 0.8f, 0);
                func_ovl0B_04_80048268(120);
                func_ovl0B_04_80048638(id2);
                ok = 0;
            }
            func_ovl0B_04_80048638(id);
            if (ok) {
                func_ovl0B_04_800487D0(0x25);
            } else {
                func_ovl0B_04_800487D0(2);
            }
        } else {
            *D_ovl0B_04_8004A178 = D_ovl0B_04_8004A190;
            *D_ovl0B_04_8004A17C = D_ovl0B_04_8004A194;
            *D_ovl0B_04_8004A180 = D_ovl0B_04_8004A198;
            *D_ovl0B_04_8004A184 = D_ovl0B_04_8004A19C;
            func_ovl0B_04_800487D0(1);
        }
        func_ovl0B_04_80043FA4(&ret, 0xFF, 0, 2);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[4]);
    } else if (arg1 & 2) {
        func_ovl0B_04_800487D0(2);
        func_ovl0B_04_80043FA4(&ret, 0, 1, 1);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[4]);
        func_ovl0B_04_8004447C(D_ovl0B_04_8004A3B0[4], 0xFF);
    }
    return ret;
}

/* Page 9's set-up: the name over a fade. */
void func_ovl0B_04_800450C0(Obj *arg0) {
    Obj *o = func_ovl0B_04_80048668(D_ovl0B_04_8004A3B0[4]);
    Fade *f;

    func_ovl0B_04_80044394(D_ovl0B_04_8004A3B0[4], D_ovl0B_04_8004A3B0[5]);
    func_ovl0B_04_8004447C(D_ovl0B_04_8004A3B0[4], 0x50);
    func_ovl0B_04_8004447C(D_ovl0B_04_8004A3B0[5], 0x50);
    o->unkC |= 0x400;
    f = &D_ovl0B_04_80049B20[4];
    D_ovl0B_04_8004A3E4 = f;
    f->unk0 = func_ovl0B_04_80047E58(func_ovl0B_04_80043CD0, 0);
    f->unk0->unkC |= 0x80;
    for (f->unk34 = f->unk14; f->unk34 < f->unk18; f->unk34 += (f->unk18 - f->unk14) / f->unk1C) {
        func_ovl0B_04_80048290();
    }
    func_ovl0B_04_80048290();
    if (0) {
        func_ovl0B_04_800450B8();
    }
}

/* Page 0: the name, the four slots (pages 5-8), and B to leave (through
 * page 9 if anything changed). */
u8 func_ovl0B_04_80044BE8(u8 arg0, u16 arg1) {
    u8 ret = 1;
    s32 changed;
    Obj *a;
    Obj *b;
    s32 i;

    if ((arg1 & 0x20) || (arg1 & 0x40)) {
        func_ovl0B_04_800438FC(0, &D_ovl0B_04_8004922C[D_ovl0B_04_8004A174], D_ovl0B_04_8004A2A8[D_ovl0B_04_8004A174]);
        func_ovl0B_04_800438FC(1, &D_ovl0B_04_8004922C[arg0], D_ovl0B_04_8004A2A8[arg0]);
        D_ovl0B_04_8004A174 = arg0;
    }
    if (arg1 & 2) {
        func_ovl0B_04_800487D0(1);
        changed = 0;
        if (D_ovl0B_04_8004A18C == 1 || D_ovl0B_04_8004A190 != *D_ovl0B_04_8004A178 ||
            D_ovl0B_04_8004A194 != *D_ovl0B_04_8004A17C || D_ovl0B_04_8004A198 != *D_ovl0B_04_8004A180 ||
            D_ovl0B_04_8004A19C != *D_ovl0B_04_8004A184) {
            changed = 1;
        }
        if (changed) {
            func_ovl0B_04_80043FA4(&ret, 9, 1, 1);
        } else {
            func_ovl0B_04_80043FA4(&ret, 0xFF, 0, 2);
        }
    } else if (arg1 & 1) {
        func_ovl0B_04_800487D0(1);
        switch (arg0) {
            case 1:
                for (i = 0; i < 8; i++) {
                    D_ovl0B_04_8004A290[i][0] = D_ovl0B_04_80048A20[i];
                    D_ovl0B_04_8004A290[i][1] = 0;
                }
                func_ovl0B_04_80043A7C(D_ovl0B_04_80049308, D_ovl0B_04_8004A448, 8);
                func_ovl0B_04_80043A24(D_ovl0B_04_800493A8, D_ovl0B_04_8004A468, 1);
                func_ovl0B_04_80043A7C(D_ovl0B_04_800493BC, &D_ovl0B_04_8004A468[1], 5);
                a = func_ovl0B_04_80048668(D_ovl0B_04_8004A468[1]);
                b = func_ovl0B_04_80048668(D_ovl0B_04_8004A468[2]);
                a->unk36 = 0;
                a->unkC |= 0x80;
                b->unk36 = 0;
                b->unkC |= 0x80;
                func_ovl0B_04_80044154();
                func_ovl0B_04_800441C4();
                for (i = 0; i < 5; i++) {
                    func_ovl0B_04_80043050(&D_ovl0B_04_8004A060[i], &D_ovl0B_04_80049C38[2 + i]);
                }
                D_ovl0B_04_8004A060[0].unk0->unkC |= 0x80;
                D_ovl0B_04_8004A060[0].unk0->unk36 = 0;
                func_ovl0B_04_MakeEntries(&D_ovl0B_04_8004A060[5], 3, &D_ovl0B_04_80049C38[10]);
                func_ovl0B_04_MakeEntries(&D_ovl0B_04_8004A060[8], 2, &D_ovl0B_04_80049C38[10]);
                D_ovl0B_04_8004A060[5].unk0->unkC |= 0x80;
                D_ovl0B_04_8004A060[5].unk0->unk36 = 0;
                D_ovl0B_04_8004A060[6].unk0->unkC |= 0x80;
                D_ovl0B_04_8004A060[6].unk0->unk36 = 0;
                func_ovl0B_04_800447DC(0, &ret);
                func_ovl0B_04_8004430C(D_ovl0B_04_8004A490.unk3);
                func_ovl0B_04_8004456C();
                func_ovl0B_04_80043FA4(&ret, D_ovl0B_04_8004A490.unk2, D_ovl0B_04_8004A490.unk3, 2);
                break;
            case 2:
                func_ovl0B_04_80043FA4(&ret, 5, 1, 0);
                break;
            case 3:
                func_ovl0B_04_80043FA4(&ret, 6, 1, 0);
                break;
            case 4:
                func_ovl0B_04_80043FA4(&ret, 7, 1, 0);
                break;
            case 5:
                func_ovl0B_04_80043FA4(&ret, 8, 1, 0);
                break;
        }
    }
    if (0) {
        func_ovl0B_04_8004471C(0, 0);
        func_ovl0B_04_80044714();
        func_ovl0B_04_800447DC(0, 0);
        func_ovl0B_04_80044624();
        func_ovl0B_04_8004461C();
        func_ovl0B_04_800445C4();
        func_ovl0B_04_800445BC();
        func_ovl0B_04_8004456C();
    }
    return ret;
}

/* The character before the cursor: the marks it can take (the 0x1E00
 * buttons put them on in turn), shown in D_ovl0B_04_80048A70. */
static u8 func_ovl0B_04_Mark27(u8 set, u8 c) {
    u8 r = 0;

    switch (set) {
        case 1:
            if (c >= 0xC9 && c < 0xCE) {
                r = 0x27;
            }
            break;
        case 2:
            if (c >= 0x79 && c < 0x7E) {
                r = 0x27;
            }
            break;
        case 3:
        case 4:
            break;
    }
    return r;
}

static void func_ovl0B_04_800447DC(u16 buttons, u8 *ret) {
    u8 ch;
    u8 set;
    u8 idx;
    u8 c;
    s32 n;
    u8 d1;
    u8 d2;
    u8 d3;
    s32 t;

    if (D_ovl0B_04_8004A490.unk0 == 0) {
        ch = 0;
    } else if (D_ovl0B_04_8004A490.unk0 == 7 && D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0][0] != 0) {
        ch = D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0][0];
    } else {
        ch = D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0 - 1][0];
    }
    set = D_ovl0B_04_8004905C[ch];
    idx = D_ovl0B_04_80048F5C[ch];
    if (set == 1 || set == 2) {
        n = 0;
        c = func_ovl0B_04_8004426C(set, idx);
        d1 = func_ovl0B_04_8004471C(set, c);
        if (d1) {
            n = 1;
        }
        d2 = func_ovl0B_04_Mark27(set, c);
        if (d2) {
            n++;
        }
        d3 = func_ovl0B_04_8004462C(set, c);
        if (d3) {
            n++;
        }
        if (n != 0) {
            D_ovl0B_04_80048A70[0] = c;
            if (d1) {
                D_ovl0B_04_80048A70[2] = c + d1;
            } else if (d2) {
                D_ovl0B_04_80048A70[2] = c + d2;
            } else if (d3) {
                D_ovl0B_04_80048A70[2] = c + d3;
            }
            D_ovl0B_04_8004A060[8].unk0->unk18 = D_ovl0B_04_8004A060[8].unkC;
            D_ovl0B_04_8004A060[8].unk0->unk1C = D_ovl0B_04_8004A060[8].unk10;
            if (n >= 2) {
                D_ovl0B_04_8004A060[9].unk0->unk18 = D_ovl0B_04_8004A060[9].unkC;
                D_ovl0B_04_8004A060[9].unk0->unk1C = D_ovl0B_04_8004A060[9].unk10;
                if (d2) {
                    D_ovl0B_04_80048A70[4] = c + d2;
                } else if (d3) {
                    D_ovl0B_04_80048A70[4] = c + d3;
                } else if (d1) {
                    D_ovl0B_04_80048A70[4] = c + d1;
                }
            } else {
                D_ovl0B_04_8004A060[9].unk0->unk18 = D_ovl0B_04_8004A060[9].unk4;
                D_ovl0B_04_8004A060[9].unk0->unk1C = D_ovl0B_04_8004A060[9].unk8;
                D_ovl0B_04_80048A70[4] = 0xF;
            }
            if (buttons & 0x1E00) {
                func_ovl0B_04_800487D0(0);
                if (n < D_ovl0B_04_8004A1A0 + 1) {
                    D_ovl0B_04_8004A1A0 = 0;
                } else {
                    D_ovl0B_04_8004A1A0++;
                    if (D_ovl0B_04_8004A1A0 == 1) {
                        if (d1) {
                            c += d1;
                        } else if (d2) {
                            c += d2;
                        } else if (d3) {
                            c += d3;
                        } else {
                            D_ovl0B_04_8004A1A0 = 0;
                        }
                    } else if (d2) {
                        c += d2;
                    } else if (d3) {
                        c += d3;
                    } else if (d1) {
                        c += d1;
                    } else {
                        D_ovl0B_04_8004A1A0 = 0;
                    }
                }
                if (D_ovl0B_04_8004A490.unk1 != c) {
                    D_ovl0B_04_8004A490.unk1 = c;
                    t = 0;
                    if (D_ovl0B_04_8004A490.unk0 != 7 || D_ovl0B_04_8004A290[7][0] == 0) {
                        D_ovl0B_04_8004A490.unk0--;
                        t = 1;
                    }
                    func_ovl0B_04_80044210();
                    if (t) {
                        D_ovl0B_04_8004A490.unk0++;
                    }
                }
                *ret = 2;
            } else {
                D_ovl0B_04_8004A1A0 = 0;
            }
        } else {
            func_ovl0B_04_800445C4();
            D_ovl0B_04_8004A1A0 = 0;
        }
    } else {
        func_ovl0B_04_800445C4();
        D_ovl0B_04_8004A1A0 = 0;
    }
    func_ovl0B_04_80048640(D_ovl0B_04_8004A468[5], D_ovl0B_04_80048A70, 5);
}

static u8 func_ovl0B_04_8004471C(u8 set, u8 c) {
    u8 r = 0;

    switch (set) {
        case 1:
            if (c >= 0xB5 && c < 0xC4) {
                return 0x27;
            }
            if (c >= 0xC9 && c < 0xCE) {
                return 0x22;
            }
            /* fallthrough */
        case 3:
        case 4:
            return r;
        case 2:
            if (c >= 0x65 && c < 0x74) {
                return 0x27;
            }
            if (c >= 0x79 && c < 0x7E) {
                r = 0x22;
            }
            return r;
        default:
            return 0;
    }
}

static u8 func_ovl0B_04_8004462C(u8 set, u8 c) {
    u8 r = 0;

    switch (set) {
        case 1:
            if (c >= 0xB0 && c < 0xB5) {
                return -0xB;
            }
            if (c >= 0xD3 && c < 0xD6) {
                return -0x28;
            }
            if (c == 0xC1) {
                return -0x17;
            }
            /* fallthrough */
        case 3:
        case 4:
            return r;
        case 2:
            if (c >= 0x60 && c < 0x65) {
                return -0xB;
            }
            if (c >= 0x83 && c < 0x86) {
                return -0x28;
            }
            if (c == 0x71) {
                r = -0x17;
            }
            return r;
        default:
            return 0;
    }
}

/* No marks: the mark texts back at their places. */
static void func_ovl0B_04_800445C4(void) {
    D_ovl0B_04_8004A060[8].unk0->unk18 = D_ovl0B_04_8004A060[8].unk4;
    D_ovl0B_04_8004A060[8].unk0->unk1C = D_ovl0B_04_8004A060[8].unk8;
    D_ovl0B_04_8004A060[9].unk0->unk18 = D_ovl0B_04_8004A060[9].unk4;
    D_ovl0B_04_8004A060[9].unk0->unk1C = D_ovl0B_04_8004A060[9].unk8;
    D_ovl0B_04_80048A70[0] = 0xF;
    D_ovl0B_04_80048A70[2] = 0xF;
    D_ovl0B_04_80048A70[4] = 0xF;
}

/* The cursor under the name. */
static void func_ovl0B_04_8004456C(void) {
    D_ovl0B_04_8004A060[4].unk0->unk10 = D_ovl0B_04_8004A490.unk0 * 20 + 120;
    D_ovl0B_04_8004A060[4].unk0->unk18 = D_ovl0B_04_8004A060[4].unk0->unk10 + 20.0f;
}

/* Page 0's set-up. */
void func_ovl0B_04_800444E8(Obj *arg0) {
    Obj *o;

    func_ovl0B_04_80044394(D_ovl0B_04_8004A2A8[6], D_ovl0B_04_8004A2A8[7]);
    o = func_ovl0B_04_80048668(D_ovl0B_04_8004A2A8[8]);
    o->unkC |= 0x480;
    o->unk36 = 100;
    o = func_ovl0B_04_80048608();
    o->unk36 = 0;
    o->unkC |= 0x80;
    if (0) {
        func_ovl0B_04_800444E0();
        func_ovl0B_04_800444D8();
        func_ovl0B_04_800444D0();
        func_ovl0B_04_8004447C(0, 0);
        func_ovl0B_04_80044394(0, 0);
        func_ovl0B_04_8004438C();
        func_ovl0B_04_80044384();
        func_ovl0B_04_8004430C(0);
        func_ovl0B_04_80044304();
        func_ovl0B_04_800442FC();
        func_ovl0B_04_8004426C(0, 0);
        func_ovl0B_04_80044264();
        func_ovl0B_04_80044210();
        func_ovl0B_04_800441C4();
        func_ovl0B_04_800441BC();
        func_ovl0B_04_80044154();
        func_ovl0B_04_800440C8(0);
        func_ovl0B_04_8004401C(0);
        func_ovl0B_04_80043FA4(0, 0, 0, 0);
        func_ovl0B_04_80043F9C();
        func_ovl0B_04_80043F94();
        func_ovl0B_04_80043F8C();
        func_ovl0B_04_80043F84();
        func_ovl0B_04_80043F7C();
        func_ovl0B_04_80043F74();
        func_ovl0B_04_80043F6C();
        func_ovl0B_04_80043F64();
        func_ovl0B_04_80043F5C();
        func_ovl0B_04_80043F54();
        func_ovl0B_04_80043F4C();
        func_ovl0B_04_80043F44();
        func_ovl0B_04_80043F3C();
    }
}

static void func_ovl0B_04_8004447C(s32 id, s32 alpha) {
    Obj *o = func_ovl0B_04_80048668(id);

    if (alpha != 0xFF) {
        o->unkC |= 0x80;
    } else {
        o->unkC &= ~0x80;
    }
    o->unk36 = alpha;
}

/* The name's two texts centred. */
static void func_ovl0B_04_80044394(s32 a, s32 b) {
    s32 n;
    s32 x;
    Obj *o;

    n = 0;
    D_ovl0B_04_80048A20[8] = 0;
    while (D_ovl0B_04_80048A20[n] != 0) {
        n++;
    }
    if (n - 1 != -1) {
        x = -func_ovl0B_04_80048680(D_ovl0B_04_80048A20) * 0.65f / 2.0f;
        func_ovl0B_04_80048650(a, x, 0);
        if (b != -1) {
            func_ovl0B_04_80048650(b, x, 0);
            o = func_ovl0B_04_80048668(b);
            o->unkC |= 0x480;
            o->unk36 = 100;
        }
    }
}

/* The END item (0x31, 0x32) lit or the character set's tab. */
static void func_ovl0B_04_8004430C(u8 item) {
    if (item == 0x31 || item == 0x32) {
        func_ovl0B_04_80047DF0(D_ovl0B_04_8004A060[3].unk0, 1);
        func_ovl0B_04_80047DF0(D_ovl0B_04_8004A060[2].unk0, 2);
    } else {
        func_ovl0B_04_80047DF0(D_ovl0B_04_8004A060[3].unk0, 2);
        func_ovl0B_04_80047DF0(D_ovl0B_04_8004A060[2].unk0, 1);
    }
}

/* A character set's character. */
static u8 func_ovl0B_04_8004426C(u8 set, u8 idx) {
    switch (set) {
        case 1:
            return D_ovl0B_04_8004915C[idx];
        case 2:
            return D_ovl0B_04_80049190[idx];
        case 3:
            return D_ovl0B_04_800491C4[idx];
        case 4:
            return D_ovl0B_04_800491F8[idx];
        default:
            return 0;
    }
}

/* The character at the cursor written. */
static void func_ovl0B_04_80044210(void) {
    u8 *p = D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0];

    p[0] = D_ovl0B_04_8004A490.unk1;
    func_ovl0B_04_80048640(D_ovl0B_04_8004A448[D_ovl0B_04_8004A490.unk0], p, 2);
}

/* The set and item of the character at the cursor. */
static void func_ovl0B_04_800441C4(void) {
    u8 set = D_ovl0B_04_8004905C[D_ovl0B_04_8004A490.unk1];

    if (set != 0) {
        D_ovl0B_04_8004A490.unk2 = set;
    }
    if (D_ovl0B_04_8004A490.unk2 < 3) {
        D_ovl0B_04_8004A490.unk2 = 3;
    }
    D_ovl0B_04_8004A490.unk3 = D_ovl0B_04_80048F5C[D_ovl0B_04_8004A490.unk1];
}

/* The cursor at the end of the name. */
static void func_ovl0B_04_80044154(void) {
    u8 n = 0;

    D_ovl0B_04_8004A290[8][0] = 0;
    while (D_ovl0B_04_8004A290[n][0] != 0) {
        n++;
    }
    if (n == 8) {
        n--;
    }
    D_ovl0B_04_8004A490.unk0 = n;
    D_ovl0B_04_8004A490.unk1 = D_ovl0B_04_8004A290[n][0];
}

/* The fade out and in (ovl_0B_05's 80043018 and 80043904). */
static void func_ovl0B_04_800440C8(Fade *f) {
    for (f->unk34 = f->unk24; f->unk34 > 0.0f; f->unk34 -= f->unk28) {
        func_ovl0B_04_80048290();
    }
    func_ovl0B_04_80047DE0(f->unk0);
    func_ovl0B_04_80048290();
}

static void func_ovl0B_04_8004401C(Fade *f) {
    f32 step;

    D_ovl0B_04_8004A3E4 = f;
    step = (f->unk18 - f->unk14) / f->unk1C;
    f->unk0 = func_ovl0B_04_80047E58(func_ovl0B_04_80043CD0, 2);
    f->unk0->unkC |= 0x480;
    for (f->unk34 = f->unk14; f->unk34 < f->unk18; f->unk34 += step) {
        func_ovl0B_04_80048290();
    }
    func_ovl0B_04_80048290();
}

/* Leave the page for another (0xFF ends the screen). */
static void func_ovl0B_04_80043FA4(u8 *ret, s32 page, s32 item, s32 mode) {
    *ret = 0;
    D_ovl0B_04_8004A168 = page;
    D_ovl0B_04_8004A16C = item;
    D_ovl0B_04_8004A490.unk3 = item;
    switch (mode) {
        case 1:
            D_ovl0B_04_8004A164->unkC &= ~1;
            break;
        case 2:
            D_ovl0B_04_8004A164->unkC |= 1;
            break;
    }
}

/* The other overlays' shared code (ovl_17_09's 80044A98-80044B70); nothing
 * here calls it. */
void func_ovl0B_04_80043F24(void) {
    D_ovl0B_04_8004A3F0 = -1;
    D_ovl0B_04_8004A3F4 = -1;
}

void func_ovl0B_04_80043EC8(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0B_04_80047F38(D_ovl0B_04_8004A3F8.x, D_ovl0B_04_8004A3F8.y, D_ovl0B_04_8004A3F8.z);
    func_ovl0B_04_80047F58(arg0, arg1, arg2);
    func_ovl0B_04_80048268(180);
}

void func_ovl0B_04_80043E80(f32 arg0) {
    f32 sp1C;

    func_ovl0B_04_80047F60(&sp1C, NULL, NULL);
    func_ovl0B_04_80047F58(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0B_04_80043E4C(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0B_04_800487F0(arg0, p->unk10, p->unk14, p->unk18);
}

/* The menu task: each page in turn until one leaves with 0xFF. */
void func_ovl0B_04_80043ADC(void) {
    Page *p;
    Obj *menu;
    s32 i;

    D_ovl0B_04_8004A16C = 1;
    D_ovl0B_04_8004A168 = 0;
    while (D_ovl0B_04_8004A168 != 0xFF) {
        p = &D_ovl0B_04_800499B8[D_ovl0B_04_8004A168];
        if (p == &D_ovl0B_04_800499B8[3] || p == &D_ovl0B_04_800499B8[4]) {
            func_ovl0B_04_80043A7C(p->unk8, p->unk4, p->unk0);
        } else {
            func_ovl0B_04_80043A24(p->unk8, p->unk4, p->unk0);
        }
        menu = func_ovl0B_04_800485D0(p->unkC, p->unk10, p->unk16, p->unk18, p->unk1A);
        if (p->unk1C != 2) {
            func_ovl0B_04_800438FC(1, &p->unk8[D_ovl0B_04_8004A16C], p->unk4[D_ovl0B_04_8004A16C]);
        }
        func_ovl0B_04_800485F8(D_ovl0B_04_8004A16C);
        D_ovl0B_04_8004A174 = D_ovl0B_04_8004A16C;
        if (p->unk20 != NULL) {
            p->unk20(menu);
        }
        func_ovl0B_04_800485F0();
        for (i = 0; i < p->unk0; i++) {
            func_ovl0B_04_80048638(p->unk4[i]);
        }
        func_ovl0B_04_800485E8();
        func_ovl0B_04_80048268(2);
    }
    func_ovl0B_04_800477F0(0x1F, 0x11, 0);
    func_ovl0B_04_80048258();
    if (0) {
        func_ovl0B_04_80043AD4();
        func_ovl0B_04_80043A7C(0, 0, 0);
        func_ovl0B_04_80043A24(0, 0, 0);
        func_ovl0B_04_800438FC(0, 0, 0);
        func_ovl0B_04_800438F4();
    }
}

/* A page's texts written (0x2501 for pages 3 and 4, 0x250C otherwise). */
static void func_ovl0B_04_80043A7C(Item *items, s32 *ids, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        ids[i] = func_ovl0B_04_80048630(items[i].unk0, items[i].unk4, items[i].unk6, items[i].unk8, items[i].unkC, items[i].unk10);
    }
}

static void func_ovl0B_04_80043A24(Item *items, s32 *ids, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        ids[i] = func_ovl0B_04_80048688(items[i].unk0, items[i].unk4, items[i].unk6, items[i].unk8, items[i].unkC, items[i].unk10);
    }
}

/* An item lit (1), unlit (0), or set without growing (2-4). */
static void func_ovl0B_04_800438FC(u32 mode, Item *it, s32 id) {
    s32 grow = 1;
    f32 d;
    u8 col;

    switch (mode) {
        case 1:
            col = it->unk11;
            d = 0.15f;
            break;
        case 0:
            d = -0.15f;
            col = it->unk10;
            break;
        case 2:
            grow = 0;
            d = 0.0f;
            col = it->unk10;
            break;
        case 3:
            grow = 0;
            d = 0.15f;
            col = it->unk11;
            break;
        case 4:
            col = it->unk10;
            grow = 0;
            d = 0.0f;
            break;
    }
    func_ovl0B_04_80048690(id, it->unk0, col);
    if (grow) {
        func_ovl0B_04_80048660(id, d * 0.4f, d);
    } else {
        func_ovl0B_04_80048658(id, it->unk8 + d * 0.4f, it->unkC + d);
    }
}

/* The bomber's task: turned with the C buttons, its animation picked from
 * D_ovl0B_04_8004A1AC each time one ends. */
void func_ovl0B_04_800436C8(void) {
    Obj *o;
    u16 buttons;
    s32 a;
    s32 b;

    while (TRUE) {
        o = D_ovl0B_04_8004A164;
        buttons = func_ovl0B_04_80048320(0);
        if (o->unkC & 0x40) {
            a = -1;
            b = -1;
            if (++D_ovl0B_04_8004A1E4 >= 14) {
                D_ovl0B_04_8004A1E4 = 0;
            }
            switch (D_ovl0B_04_8004A1AC[D_ovl0B_04_8004A1E4]) {
                case 0:
                    a = 0;
                    break;
                case 1:
                    a = 1;
                    b = 2;
                    break;
                case 2:
                    a = 3;
                    b = 4;
                    break;
                case 3:
                    a = 5;
                    b = 6;
                    break;
            }
            func_ovl0B_04_80047E20(o, a, 0);
            func_ovl0B_04_80047E20(D_ovl0B_04_8004A164, b, 1);
            D_ovl0B_04_8004A164->unkC |= 0x20;
            D_ovl0B_04_8004A164->unkC &= ~0x40;
            D_ovl0B_04_8004A164->unk48->unk4->unk4 = 0.0f;
            D_ovl0B_04_8004A164->unk48->unk4->unk10 = 0.0f;
        }
        if (buttons & 0x10) {
            func_ovl0B_04_80043640(2.0f);
        } else if (buttons & 0x2000) {
            func_ovl0B_04_80043640(-2.0f);
        }
        func_ovl0B_04_80048290();
    }
    if (0) {
        func_ovl0B_04_800436C0();
        func_ovl0B_04_80043640(0);
    }
}

static void func_ovl0B_04_80043640(f32 d) {
    D_ovl0B_04_8004A164->unk20 += d;
    if (D_ovl0B_04_8004A164->unk20 >= 360.0f) {
        D_ovl0B_04_8004A164->unk20 -= 360.0f;
    }
    if (D_ovl0B_04_8004A164->unk20 < 0.0f) {
        D_ovl0B_04_8004A164->unk20 += 360.0f;
    }
}

/* The handler the entry returns. */
void func_ovl0B_04_80043110(s32 arg0) {
    s32 i;

    switch (arg0) {
        case 2:
            func_ovl0B_04_80047FA0(0x7F);
            func_ovl0B_04_80047F18(1);
            func_ovl0B_04_80047F38(0.0f, 10.0f, 0.0f);
            func_ovl0B_04_80047F28(1);
            func_ovl0B_04_80047F58(32768.0f, 10.0f, 700.0f);
            D_ovl0B_04_8004A1A8 = 0;
            D_ovl0B_04_8004A1A4 = 0;
            D_ovl0B_04_8004A490.unk0 = 0;
            D_ovl0B_04_8004A490.unk1 = 0;
            D_ovl0B_04_8004A490.unk2 = 1;
            D_ovl0B_04_8004A490.unk3 = 0x32;
            break;
        case 4:
            func_ovl0B_04_MakeEntries(D_ovl0B_04_80049D40, 20, &D_ovl0B_04_80049C38[0]);
            func_ovl0B_04_MakeEntries(D_ovl0B_04_80049ED0, 20, &D_ovl0B_04_80049C38[1]);
            func_ovl0B_04_80043050(&D_ovl0B_04_8004A060[12], &D_ovl0B_04_80049C38[7]);
            D_ovl0B_04_8004A060[12].unk0->unk36 = 90;
            break;
        case 5:
            func_ovl0B_04_800487E0(0x1D);
            D_ovl0B_04_8004A18C = 0;
            func_ovl0B_04_800485A0(1);
            func_ovl0B_04_800485A8(0x46);
            D_ovl0B_04_8004A164 = func_ovl0B_04_80047DD8(0x49, 0);
            D_ovl0B_04_8004A164->unk10 = -110.0f;
            D_ovl0B_04_8004A164->unk14 = -70.0f;
            D_ovl0B_04_8004A164->unk18 = 0.0f;
            D_ovl0B_04_8004A164->unk20 = 0.0f;
            func_ovl0B_04_80047E00(D_ovl0B_04_8004A164, 12);
            for (i = 0; i < 12; i++) {
                func_ovl0B_04_80047E08(D_ovl0B_04_8004A164, 0x4A, i, i);
            }
            func_ovl0B_04_80047E28(D_ovl0B_04_8004A164, -1, i);
            D_ovl0B_04_8004A164->unkC |= 0x20;
            D_ovl0B_04_8004A170 = func_ovl0B_04_80047E68(D_ovl0B_04_8004A164, 0xF);
            D_ovl0B_04_8004A178 = func_ovl0B_04_800484E0(8);
            D_ovl0B_04_8004A17C = func_ovl0B_04_800484E0(9);
            D_ovl0B_04_8004A180 = func_ovl0B_04_800484E0(10);
            D_ovl0B_04_8004A184 = func_ovl0B_04_800484E0(11);
            D_ovl0B_04_8004A188 = func_ovl0B_04_800484E0(12);
            D_ovl0B_04_8004A190 = *D_ovl0B_04_8004A178;
            D_ovl0B_04_8004A194 = *D_ovl0B_04_8004A17C;
            D_ovl0B_04_8004A198 = *D_ovl0B_04_8004A180;
            D_ovl0B_04_8004A19C = *D_ovl0B_04_8004A184;
            if (*D_ovl0B_04_8004A178 != 0) {
                func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 0, *D_ovl0B_04_8004A178);
            }
            if (*D_ovl0B_04_8004A17C != 0) {
                func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 1, *D_ovl0B_04_8004A17C);
            }
            if (*D_ovl0B_04_8004A180 != 0) {
                func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 2, *D_ovl0B_04_8004A180);
            }
            if (*D_ovl0B_04_8004A184 != 0) {
                func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 3, *D_ovl0B_04_8004A184);
            }
            for (i = 0; i < 8; i++) {
                D_ovl0B_04_80048A20[i] = D_ovl0B_04_8004A188[i];
                D_ovl0B_04_8004A498[i] = D_ovl0B_04_8004A188[i];
            }
            D_ovl0B_04_80048A20[8] = 0;
            D_ovl0B_04_8004A188[8] = 0;
            func_ovl0B_04_80048248(func_ovl0B_04_80043ADC, NULL, 0, 0, 0x130);
            D_ovl0B_04_8004A4A0 = func_ovl0B_04_80048248(func_ovl0B_04_800436C8, NULL, 0, 0, 0x130);
            break;
        case 12:
            func_ovl0B_04_800487E8();
            break;
        case 1:
            func_ovl0B_04_800485A0(0);
            func_ovl0B_04_80048250(D_ovl0B_04_8004A4A0);
            func_ovl0B_04_80047E78(D_ovl0B_04_8004A170);
            func_ovl0B_04_80047DE0(D_ovl0B_04_8004A164);
            func_ovl0B_04_FreeEntries(D_ovl0B_04_80049D40, 20);
            func_ovl0B_04_FreeEntries(D_ovl0B_04_80049ED0, 20);
            func_ovl0B_04_80047DE0(D_ovl0B_04_8004A060[12].unk0);
            break;
    }
}

/* The fade's display list (ovl_0B_05's 80044DD8). */
void func_ovl0B_04_80043CD0(s32 arg0, Gfx0B04 **arg1) {
    Fade *fade = D_ovl0B_04_8004A3E4;
    Gfx0B04 *gfx = *arg1;

    { Gfx0B04 *g = gfx++; g->w0 = 0xFA000000; g->w1 = ((fade->unk4 & 0xFF) << 24) | ((fade->unk8 & 0xFF) << 16) | ((fade->unkC & 0xFF) << 8) | (fade->unk10 & 0xFF); }
    { Gfx0B04 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFDF6FB; }
    { Gfx0B04 *g = gfx++; g->w0 = 0xF7000000; g->w1 = 0x10001; }
    { Gfx0B04 *g = gfx++; g->w0 = 0xF6000000 | (((fade->unk2C + (s32) fade->unk34) & 0x3FF) << 14) | (((fade->unk30 + (s32) (fade->unk34 * fade->unk20)) & 0x3FF) << 2); g->w1 = (((fade->unk2C - (s32) fade->unk34) & 0x3FF) << 14) | (((fade->unk30 - (s32) (fade->unk34 * fade->unk20)) & 0x3FF) << 2); }
    *arg1 = gfx;
}

/* An entry's object made as its Desc says. */
static void func_ovl0B_04_80043050(Entry *e, Desc *d) {
    e->unk0 = func_ovl0B_04_80047DD8(d->unk8, d->unk10);
    e->unk0->unk38 = d->unkC;
    e->unk0->unk28 = d->unk0;
    e->unk0->unk2C = d->unk4;
    e->unk0->unk10 = e->unk4;
    e->unk0->unk14 = e->unk8;
    e->unk0->unk18 = e->unkC;
    e->unk0->unk1C = e->unk10;
    e->unk0->unkC |= d->unk14;
}

