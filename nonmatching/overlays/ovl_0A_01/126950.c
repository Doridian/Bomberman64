/*
 * NON_MATCHING: ovl_0A_01's game object (the opening's stage), complete: every
 * function and its .data/.bss; .text 0x40C0 as the original.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 286, eu 286, jp 286
 *
 * What still differs in us (words):
 * - func_ovl0A_01_80043028 (6): `beq a0,s0` where the original has
 *   `beq s0,a0` (three compares), and a table address scheduled later.
 * - func_ovl0A_01_80043338 (2): `move s4,s2` and the `bnez` after it swap.
 * - func_ovl0A_01_8004364C (3): a table address built in v1, not a0.
 * - func_ovl0A_01_80043AA4 (17): the float constants' loads and an add.s
 *   scheduled differently ($f2 for $f0).
 * - func_ovl0A_01_800442B4 (144): frame 0x58, not 0x60: the original keeps
 *   a counter on the stack (sp+92), ours in s1, which renumbers the
 *   s registers after it; 5 words short.
 * - func_ovl0A_01_80044584 (25), in its static 80044A2C: the call to
 *   80047DC8 (inlined from 80044A24) gets its stores scheduled before its
 *   arguments, and `&fall` in s2 where the original has s1.
 * - func_ovl0A_01_80044F3C (41): constant loads scheduled differently,
 *   and the epilogue after its closing `while (1)` comes after 7 nops where
 *   the original has 2 (the code before is the same length; the padding
 *   keeps our epilogue at the object's offset 0x2200 whatever comes before).
 * - func_ovl0A_01_8004609C (48): $f24 where the original uses $f22, and
 *   the frame 8 bytes too big: 8004607C's count parameter gives the
 *   original's `slt` (with a constant 1 it was `bne`) but takes a slot the
 *   original doesn't have.
 */
#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStruct_ovl0A_01_Anim2;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_ovl0A_01_Anim2 *unk4;
} UnkStruct_ovl0A_01_Anim;

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
    /* 0x48 */ UnkStruct_ovl0A_01_Anim *unk48;
} Inner;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x1C];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[0x14];
    /* 0x40 */ Inner *unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58[3];
    /* 0x64 */ u8 unk64[4];
    /* 0x68 */ f32 unk68;
} Obj;

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
} Sprite;

typedef struct {
    u32 w0;
    u32 w1;
} Gfx_ovl0A_01;

/* A placed object: what a table entry spawns and where. */
typedef struct {
    /* 0x00 */ Obj *obj;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ f32 unk20;
} UnkStruct_ovl0A_01_Entry;

typedef struct {
    /* 0x00 */ Inner *unk0;
    /* 0x04 */ s32 *unk4[4];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ void (*unk18)(s32, Gfx_ovl0A_01 **);
} UnkStruct_ovl0A_01_Entry2;

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0A_01_B04_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl0A_01_B04_Inner *unk40;
} UnkStruct_ovl0A_01_B04;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl0A_01;

typedef UnkStruct_ovl0A_01_Entry Entry;
typedef UnkStruct_ovl0A_01_Entry2 Entry2;

void func_ovl0A_01_800470F0(const char *); /* 0x100 */
void func_ovl0A_01_80047450(s32); /* 0xD00 */
void func_ovl0A_01_80047530(s32, s32, s32); /* 0xF00 */
s32 func_ovl0A_01_80047538(void); /* 0xF01 */
s32 * func_ovl0A_01_80047588(void); /* 0xF0B */
void func_ovl0A_01_800475A0(s32); /* 0xF0E */
void func_ovl0A_01_80047B20(Inner *); /* 0x1501 */
void func_ovl0A_01_80047B30(Inner *, s32); /* 0x1503 */
void func_ovl0A_01_80047B40(Inner *, s32); /* 0x1505 */
void func_ovl0A_01_80047B48(Inner *, s32, s32, s32); /* 0x1506 */
void func_ovl0A_01_80047B58(Inner *, s32); /* 0x1508 */
void func_ovl0A_01_80047B60(Inner *, s32, s32); /* 0x1509 */
f32 func_ovl0A_01_80047B78(Inner *, s32); /* 0x150C */
Inner *func_ovl0A_01_80047B98(void (*)(s32, Gfx_ovl0A_01 **), s32); /* 0x1510 */
s32 func_ovl0A_01_80047BA8(Inner *, s32); /* 0x1512 */
void func_ovl0A_01_80047BB0(s32, s32, s32); /* 0x1513 */
void func_ovl0A_01_80047BC0(s32, s32, s32); /* 0x1515 */
void func_ovl0A_01_80047BC8(s32, s32, s32); /* 0x1516 */
void func_ovl0A_01_80047C78(f32, f32, f32); /* 0x1704 */
void func_ovl0A_01_80047C88(f32, f32, f32); /* 0x1706 */
void func_ovl0A_01_80047C98(f32, f32, f32); /* 0x1708 */
void func_ovl0A_01_80047CA0(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0A_01_80047D50(s32); /* 0x171F */
void func_ovl0A_01_80047D60(f32, f32, f32); /* 0x1721 */
void func_ovl0A_01_80047DC8(f32 *, f32 *, f32 *); /* 0x1803 */
void func_ovl0A_01_80047E38(Obj *, s32); /* 0x1811 */
void func_ovl0A_01_80047E40(Obj *, s32); /* 0x1812 */
void func_ovl0A_01_80047E50(Obj *); /* 0x1814 */
Obj * func_ovl0A_01_80047E60(s32, s32, s32, Obj *); /* 0x1816 */
void func_ovl0A_01_80047E70(Obj *); /* 0x1818 */
void func_ovl0A_01_80047F10(Obj *, Obj *); /* 0x182C */
s32 func_ovl0A_01_80047F88(void (*)(), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0A_01_80047F90(s32); /* 0x1901 */
void func_ovl0A_01_80047F98(void); /* 0x1902 */
void func_ovl0A_01_80047FA8(s32); /* 0x1904 */
Obj * func_ovl0A_01_80047FB0(void); /* 0x1905 */
s32 func_ovl0A_01_80047FD0(void); /* 0x1909 */
Sprite * func_ovl0A_01_80048010(s32); /* 0x1A00 */
void func_ovl0A_01_80048020(Sprite *, s32); /* 0x1A02 */
f32 func_ovl0A_01_80048130(f32); /* 0x1D00 */
f64 func_ovl0A_01_80048140(void); /* 0x1D02 */
s32 func_ovl0A_01_80048148(s32); /* 0x1D03 */
void func_ovl0A_01_80048288(s32, s32, s32, f32); /* 0x2004 */
void func_ovl0A_01_800483D8(s32, f32, f32, f32, s32); /* 0x2600 */
void func_ovl0A_01_800483E0(s32, f32 *, s32); /* 0x2601 */
void func_ovl0A_01_80048510(s32); /* 0x2B00 */
void func_ovl0A_01_80048530(s32, s32, s32, s32); /* 0x2B04 */
void func_ovl0A_01_800485A0(Inner *, s32, s32, s32, f32); /* 0x2C03 */
void func_ovl0A_01_80048688(void); /* 0x3000 */
void func_ovl0A_01_80048690(void); /* 0x3001 */
void func_ovl0A_01_800486F8(void); /* 0x310A */

/* .bss */
u8 D_ovl0A_01_80048CE0[0x24];
s32 D_ovl0A_01_80048D04;
s32 D_ovl0A_01_80048D08;
u8 D_ovl0A_01_80048D0C[4];
Vec3f_ovl0A_01 D_ovl0A_01_80048D10;
s32 D_ovl0A_01_80048D1C;
s32 *D_ovl0A_01_80048D20;
Sprite *D_ovl0A_01_80048D24;
u8 D_ovl0A_01_80048D28[8];

static void func_ovl0A_01_80046F10(s32 arg0, Gfx_ovl0A_01 **arg1);

/* .data */
u32 D_ovl0A_01_80048730[4][4] = {
    { 0xFF5600FA, 0, 0, 0xFF },
    { 0xFFCE0000, 0, 0, 0xFF },
    { 0x00AA00FA, 0, 0, 0xFF },
    { 0x00320000, 0, 0, 0xFF },
};
Entry D_ovl0A_01_80048770[8] = {
    { NULL, 1, 0x324, 2300.0f, 0.0f, 1100.0f, 0, -1, 0.0f },
    { NULL, 1, 0x321, 2100.0f, 0.0f, 1500.0f, 0, -1, 135.0f },
    { NULL, 1, 0x322, 2500.0f, 0.0f, 1500.0f, 0, -1, 225.0f },
    { NULL, 0, 0x327, 2550.0f, 0.0f, 1200.0f, -1, -1, 0.0f },
    { NULL, 0, 0x346, 2300.0f, 100.0f, 1400.0f, -1, -1, 0.0f },
    { NULL, 0, 0x342, 2300.0f, 0.0f, 800.0f, -1, -1, 0.0f },
    { NULL, 0, 0x1FA, 0.0f, 0.0f, 0.0f, -1, -1, 0.0f },
    { NULL, 0, 0x1FC, 0.0f, 0.0f, 0.0f, -1, -1, 0.0f },
};
Entry D_ovl0A_01_80048890[2] = {
    { NULL, 0, 0x320, 2300.0f, 0.0f, 2000.0f, 1, 2, 180.0f },
    { NULL, 0, 0x340, 2300.0f, 400.0f, 800.0f, -1, -1, 0.0f },
};
Entry D_ovl0A_01_800488D8[9] = {
    { NULL, 0, 0x345, 1235.0f, 895.0f, 512.0f, -1, -1, 57.0f },
    { NULL, 0, 0x343, 0.0f, 0.0f, 0.0f, -1, -1, 0.0f },
    { NULL, 0, 0x49, 620.0f, 0.0f, 1300.0f, 5, 6, 90.0f },
    { NULL, 0, 0x49, 500.0f, 0.0f, 1300.0f, 5, 6, 90.0f },
    { NULL, 0, 0x49, 620.0f, 0.0f, 1300.0f, 5, 6, 90.0f },
    { NULL, 0, 0x49, 500.0f, 0.0f, 1300.0f, 5, 6, 90.0f },
    { NULL, 0, 0x97, 1000.0f, 0.0f, -200.0f, -1, -1, 0.0f },
    { NULL, 0, 0x97, 300.0f, 0.0f, 400.0f, -1, -1, 0.0f },
    { NULL, 0, 0x97, 300.0f, 0.0f, 1100.0f, -1, -1, 0.0f },
};
f32 D_ovl0A_01_80048A1C = 0.0f;
f32 D_ovl0A_01_80048A20 = 0.0f;
f32 D_ovl0A_01_80048A24 = 0.0f;
s32 D_ovl0A_01_80048A28[4] = { 0x9B, 0xFF, 0x5C, 0 };
s32 D_ovl0A_01_80048A38[4] = { 0x9B, 0xFF, 0x5C, 0xFF };
Entry2 D_ovl0A_01_80048A48[1] = {
    { NULL, { D_ovl0A_01_80048A28, D_ovl0A_01_80048A38, D_ovl0A_01_80048A28, D_ovl0A_01_80048A38 }, 0x80, func_ovl0A_01_80046F10 },
};
#define LIGHTS D_ovl0A_01_80048A48
s32 D_ovl0A_01_80048A64 = -1;
s32 D_ovl0A_01_80048A68 = -1;
s32 D_ovl0A_01_80048A6C = -1;
s32 D_ovl0A_01_80048A70 = 0;
f32 D_ovl0A_01_80048A74 = 0.0f;
extern Entry D_ovl0A_01_80048A84[3];
extern s32 D_ovl0A_01_80048AF0;
extern s32 D_ovl0A_01_80048AF4;

void func_ovl0A_01_80043DE8(void);
void func_ovl0A_01_800442B4(void);
void func_ovl0A_01_80044584(void);
void func_ovl0A_01_80044F3C(void);
void func_ovl0A_01_80045288(void);
void func_ovl0A_01_800456C4(void);
void func_ovl0A_01_80045908(void);
void func_ovl0A_01_80045C70(void);
void func_ovl0A_01_80045EA0(void);
void func_ovl0A_01_8004609C(void);
void func_ovl0A_01_8004694C(void);
void func_ovl0A_01_80046A50(void);

static void func_ovl0A_01_80043018(s32 n, Entry *tbl);
static void func_ovl0A_01_80043020(s32 n, Entry2 *tbl);
static void func_ovl0A_01_80043010(s32 task);
void func_ovl0A_01_80043028(void);
static void func_ovl0A_01_80043274(void);
static void func_ovl0A_01_8004327C(void);
static void func_ovl0A_01_80043284(void);
void func_ovl0A_01_8004328C(void);
void func_ovl0A_01_800432C8(void);
void func_ovl0A_01_80043300(void);
void func_ovl0A_01_80043338(void);
static void func_ovl0A_01_80043378(Entry *e);
static void func_ovl0A_01_80043370(Entry *e);
static void func_ovl0A_01_80043380(Entry *tbl, s32 n);
static void func_ovl0A_01_80043500(s32 id);
static void func_ovl0A_01_800435E4(void);
void func_ovl0A_01_8004364C(void);
void func_ovl0A_01_80043AA4(void);
static void func_ovl0A_01_80043DE0(void);
static void func_ovl0A_01_80043FF8(s32 frame);
static void func_ovl0A_01_800440F4(void);
static void func_ovl0A_01_800441F8(void);
static void func_ovl0A_01_800442AC(void);
static void func_ovl0A_01_800442A4(void);
static void func_ovl0A_01_8004429C(void);
static void func_ovl0A_01_80044294(void);
static void func_ovl0A_01_8004428C(void);
static void func_ovl0A_01_8004457C(void);
static void func_ovl0A_01_80044790(void);
static void func_ovl0A_01_80044798(f32 speed, f32 *fall);
static void func_ovl0A_01_80044968(s32 frame, f32 dx, f32 dy);
static void func_ovl0A_01_80044A24(Obj *obj, f32 *pos, f32 *tgt);
static void func_ovl0A_01_80044A2C(void);
static void func_ovl0A_01_80045280(void);
static void func_ovl0A_01_80045278(void);
static void func_ovl0A_01_80045270(void);
static void func_ovl0A_01_80046094(void);
static void func_ovl0A_01_8004608C(void);
static void func_ovl0A_01_8004607C(s32 n, Entry2 *tbl);
static void func_ovl0A_01_80046084(void);
void func_ovl0A_01_80046C88(s32 arg0);
void func_ovl0A_01_80046DB8(s32 arg0, UnkStruct_ovl0A_01_B04 *arg1);
void func_ovl0A_01_80046DEC(f32 arg0);
void func_ovl0A_01_80046E34(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_01_80046E90(void);
void func_ovl0A_01_80046EA8(void);
static void func_ovl0A_01_80046EB0(void);
static void func_ovl0A_01_80046EB8(void);
static void func_ovl0A_01_80046EC0(void);
static void func_ovl0A_01_80046EC8(void);
static void func_ovl0A_01_80046ED0(void);
static void func_ovl0A_01_80046ED8(void);
static void func_ovl0A_01_80046EE0(void);
static void func_ovl0A_01_80046EE8(void);
static void func_ovl0A_01_80046EF0(void);
static void func_ovl0A_01_80046EF8(void);
static void func_ovl0A_01_80046F00(void);
static void func_ovl0A_01_80046F08(void);

static void func_ovl0A_01_80043018(s32 n, Entry *tbl);
static void func_ovl0A_01_80043020(s32 n, Entry2 *tbl);
static void func_ovl0A_01_80043010(s32 task);
void func_ovl0A_01_80043028(void);
static void func_ovl0A_01_80043274(void);
static void func_ovl0A_01_8004327C(void);
static void func_ovl0A_01_80043284(void);
void func_ovl0A_01_8004328C(void);
void func_ovl0A_01_800432C8(void);
void func_ovl0A_01_80043300(void);
void func_ovl0A_01_80043338(void);
static void func_ovl0A_01_80043378(Entry *e);
static void func_ovl0A_01_80043370(Entry *e);
static void func_ovl0A_01_80043380(Entry *tbl, s32 n);
static void func_ovl0A_01_80043500(s32 id);
static void func_ovl0A_01_800435E4(void);
void func_ovl0A_01_8004364C(void);
void func_ovl0A_01_80043AA4(void);
static void func_ovl0A_01_80043DE0(void);
static void func_ovl0A_01_80043FF8(s32 frame);
static void func_ovl0A_01_800440F4(void);
static void func_ovl0A_01_800441F8(void);
static void func_ovl0A_01_800442AC(void);
static void func_ovl0A_01_800442A4(void);
static void func_ovl0A_01_8004429C(void);
static void func_ovl0A_01_80044294(void);
static void func_ovl0A_01_8004428C(void);
static void func_ovl0A_01_8004457C(void);
static void func_ovl0A_01_80044790(void);
static void func_ovl0A_01_80044798(f32 speed, f32 *fall);
static void func_ovl0A_01_80044968(s32 frame, f32 dx, f32 dy);
static void func_ovl0A_01_80044A24(Obj *obj, f32 *pos, f32 *tgt);
static void func_ovl0A_01_80044A2C(void);
static void func_ovl0A_01_80045280(void);
static void func_ovl0A_01_80045278(void);
static void func_ovl0A_01_80045270(void);
static void func_ovl0A_01_80046094(void);
static void func_ovl0A_01_8004608C(void);
static void func_ovl0A_01_8004607C(s32 n, Entry2 *tbl);
static void func_ovl0A_01_80046084(void);
void func_ovl0A_01_80046C88(s32 arg0);
void func_ovl0A_01_80046DB8(s32 arg0, UnkStruct_ovl0A_01_B04 *arg1);
void func_ovl0A_01_80046DEC(f32 arg0);
void func_ovl0A_01_80046E34(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_01_80046E90(void);
void func_ovl0A_01_80046EA8(void);
static void func_ovl0A_01_80046EB0(void);
static void func_ovl0A_01_80046EB8(void);
static void func_ovl0A_01_80046EC0(void);
static void func_ovl0A_01_80046EC8(void);
static void func_ovl0A_01_80046ED0(void);
static void func_ovl0A_01_80046ED8(void);
static void func_ovl0A_01_80046EE0(void);
static void func_ovl0A_01_80046EE8(void);
static void func_ovl0A_01_80046EF0(void);
static void func_ovl0A_01_80046EF8(void);
static void func_ovl0A_01_80046F00(void);
static void func_ovl0A_01_80046F08(void);

static void func_ovl0A_01_80043018(s32 n, Entry *tbl);
static void func_ovl0A_01_80043020(s32 n, Entry2 *tbl);
static void func_ovl0A_01_80043010(s32 task);
void func_ovl0A_01_80043028(void);
static void func_ovl0A_01_80043274(void);
static void func_ovl0A_01_8004327C(void);
static void func_ovl0A_01_80043284(void);
void func_ovl0A_01_8004328C(void);
void func_ovl0A_01_800432C8(void);
void func_ovl0A_01_80043300(void);
void func_ovl0A_01_80043338(void);
static void func_ovl0A_01_80043378(Entry *e);
static void func_ovl0A_01_80043370(Entry *e);
static void func_ovl0A_01_80043380(Entry *tbl, s32 n);
static void func_ovl0A_01_80043500(s32 id);
static void func_ovl0A_01_800435E4(void);
void func_ovl0A_01_8004364C(void);
void func_ovl0A_01_80043AA4(void);
static void func_ovl0A_01_80043DE0(void);
static void func_ovl0A_01_80043FF8(s32 frame);
static void func_ovl0A_01_800440F4(void);
static void func_ovl0A_01_800441F8(void);
static void func_ovl0A_01_800442AC(void);
static void func_ovl0A_01_800442A4(void);
static void func_ovl0A_01_8004429C(void);
static void func_ovl0A_01_80044294(void);
static void func_ovl0A_01_8004428C(void);
static void func_ovl0A_01_8004457C(void);
static void func_ovl0A_01_80044790(void);
static void func_ovl0A_01_80044798(f32 speed, f32 *fall);
static void func_ovl0A_01_80044968(s32 frame, f32 dx, f32 dy);
static void func_ovl0A_01_80044A24(Obj *obj, f32 *pos, f32 *tgt);
static void func_ovl0A_01_80044A2C(void);
static void func_ovl0A_01_80045280(void);
static void func_ovl0A_01_80045278(void);
static void func_ovl0A_01_80045270(void);
static void func_ovl0A_01_80046094(void);
static void func_ovl0A_01_8004608C(void);
static void func_ovl0A_01_8004607C(s32 n, Entry2 *tbl);
static void func_ovl0A_01_80046084(void);
void func_ovl0A_01_80046C88(s32 arg0);
void func_ovl0A_01_80046DB8(s32 arg0, UnkStruct_ovl0A_01_B04 *arg1);
void func_ovl0A_01_80046DEC(f32 arg0);
void func_ovl0A_01_80046E34(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_01_80046E90(void);
void func_ovl0A_01_80046EA8(void);
static void func_ovl0A_01_80046EB0(void);
static void func_ovl0A_01_80046EB8(void);
static void func_ovl0A_01_80046EC0(void);
static void func_ovl0A_01_80046EC8(void);
static void func_ovl0A_01_80046ED0(void);
static void func_ovl0A_01_80046ED8(void);
static void func_ovl0A_01_80046EE0(void);
static void func_ovl0A_01_80046EE8(void);
static void func_ovl0A_01_80046EF0(void);
static void func_ovl0A_01_80046EF8(void);
static void func_ovl0A_01_80046F00(void);
static void func_ovl0A_01_80046F08(void);

static void func_ovl0A_01_80043018(s32 n, Entry *tbl);
static void func_ovl0A_01_80043020(s32 n, Entry2 *tbl);
static void func_ovl0A_01_80043010(s32 task);
void func_ovl0A_01_80043028(void);
static void func_ovl0A_01_80043274(void);
static void func_ovl0A_01_8004327C(void);
static void func_ovl0A_01_80043284(void);
void func_ovl0A_01_8004328C(void);
void func_ovl0A_01_800432C8(void);
void func_ovl0A_01_80043300(void);
void func_ovl0A_01_80043338(void);
static void func_ovl0A_01_80043378(Entry *e);
static void func_ovl0A_01_80043370(Entry *e);
static void func_ovl0A_01_80043380(Entry *tbl, s32 n);
static void func_ovl0A_01_80043500(s32 id);
static void func_ovl0A_01_800435E4(void);
void func_ovl0A_01_8004364C(void);
void func_ovl0A_01_80043AA4(void);
static void func_ovl0A_01_80043DE0(void);
static void func_ovl0A_01_80043FF8(s32 frame);
static void func_ovl0A_01_800440F4(void);
static void func_ovl0A_01_800441F8(void);
static void func_ovl0A_01_800442AC(void);
static void func_ovl0A_01_800442A4(void);
static void func_ovl0A_01_8004429C(void);
static void func_ovl0A_01_80044294(void);
static void func_ovl0A_01_8004428C(void);
static void func_ovl0A_01_8004457C(void);
static void func_ovl0A_01_80044790(void);
static void func_ovl0A_01_80044798(f32 speed, f32 *fall);
static void func_ovl0A_01_80044968(s32 frame, f32 dx, f32 dy);
static void func_ovl0A_01_80044A24(Obj *obj, f32 *pos, f32 *tgt);
static void func_ovl0A_01_80044A2C(void);
static void func_ovl0A_01_80045280(void);
static void func_ovl0A_01_80045278(void);
static void func_ovl0A_01_80045270(void);
static void func_ovl0A_01_80046094(void);
static void func_ovl0A_01_8004608C(void);
static void func_ovl0A_01_8004607C(s32 n, Entry2 *tbl);
static void func_ovl0A_01_80046084(void);
void func_ovl0A_01_80046C88(s32 arg0);
void func_ovl0A_01_80046DB8(s32 arg0, UnkStruct_ovl0A_01_B04 *arg1);
void func_ovl0A_01_80046DEC(f32 arg0);
void func_ovl0A_01_80046E34(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_01_80046E90(void);
void func_ovl0A_01_80046EA8(void);
static void func_ovl0A_01_80046EB0(void);
static void func_ovl0A_01_80046EB8(void);
static void func_ovl0A_01_80046EC0(void);
static void func_ovl0A_01_80046EC8(void);
static void func_ovl0A_01_80046ED0(void);
static void func_ovl0A_01_80046ED8(void);
static void func_ovl0A_01_80046EE0(void);
static void func_ovl0A_01_80046EE8(void);
static void func_ovl0A_01_80046EF0(void);
static void func_ovl0A_01_80046EF8(void);
static void func_ovl0A_01_80046F00(void);
static void func_ovl0A_01_80046F08(void);

static void func_ovl0A_01_80046F08(void) {
}

static void func_ovl0A_01_80046F00(void) {
}

static void func_ovl0A_01_80046EF8(void) {
}

static void func_ovl0A_01_80046EF0(void) {
}

static void func_ovl0A_01_80046EE8(void) {
}

static void func_ovl0A_01_80046EE0(void) {
}

static void func_ovl0A_01_80046ED8(void) {
}

static void func_ovl0A_01_80046ED0(void) {
}

static void func_ovl0A_01_80046EC8(void) {
}

static void func_ovl0A_01_80046EC0(void) {
}

static void func_ovl0A_01_80046EB8(void) {
}

/* Unused: IDO -O3 drops their bodies and leaves a `jr ra` each. */
static void func_ovl0A_01_80046EB0(void) {
    D_ovl0A_01_80048CE0[0] = 0;
    D_ovl0A_01_80048D0C[0] = 0;
    D_ovl0A_01_80048D28[0] = 0;
    func_ovl0A_01_80047F88(func_ovl0A_01_80046EA8, NULL, 0, 0, 0);
}

/* Draws the light's quad: D_ovl0A_01_80048A48[0]'s draw callback. */
/* Draws the light's quad: D_ovl0A_01_80048A48[0]'s draw callback. */
#define RGBA(c) ((((c)[0] & 0xFF) << 24) | (((c)[1] & 0xFF) << 16) | (((c)[2] & 0xFF) << 8) | ((c)[3] & 0xFF))
/* Draws the light's quad: D_ovl0A_01_80048A48's draw callback. */
static void func_ovl0A_01_80046F10(s32 arg0, Gfx_ovl0A_01 **arg1) {
    Gfx_ovl0A_01 *gfx;
    s32 i;

    gfx = *arg1;
    { Gfx_ovl0A_01 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFE793C; }
    { Gfx_ovl0A_01 *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x00504240; }
    { Gfx_ovl0A_01 *g = gfx++; g->w0 = 0x0400103F; g->w1 = (u32) D_ovl0A_01_80048730; }
    for (i = 0; i < 4; i++) {
        { Gfx_ovl0A_01 *g = gfx++; g->w0 = 0xB2100000 + i * 2; g->w1 = RGBA(D_ovl0A_01_80048A48[0].unk4[i]); }
    }
    { Gfx_ovl0A_01 *g = gfx++; g->w0 = 0xBF000000; g->w1 = 0x204; }
    { Gfx_ovl0A_01 *g = gfx++; g->w0 = 0xBF000000; g->w1 = 0x40206; }
    *arg1 = gfx;
}

void func_ovl0A_01_80046EA8(void) {
}

void func_ovl0A_01_80046E90(void) {
    D_ovl0A_01_80048D04 = -1;
    D_ovl0A_01_80048D08 = -1;
}

void func_ovl0A_01_80046E34(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0A_01_80047C78(D_ovl0A_01_80048D10.x, D_ovl0A_01_80048D10.y, D_ovl0A_01_80048D10.z);
    func_ovl0A_01_80047C98(arg0, arg1, arg2);
    func_ovl0A_01_80047FA8(0xB4);
}

void func_ovl0A_01_80046DEC(f32 arg0) {
    f32 sp1C;

    func_ovl0A_01_80047CA0(&sp1C, NULL, NULL);
    func_ovl0A_01_80047C98(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0A_01_80046DB8(s32 arg0, UnkStruct_ovl0A_01_B04 *arg1) {
    UnkStruct_ovl0A_01_B04_Inner *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01's func_ovl09_01_800431C8 */
    }
    func_ovl0A_01_80048530(arg0, p->unk10, p->unk14, p->unk18);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0A_01_80046C88(s32 arg0) {
    switch (arg0) {
        case 2:
            D_ovl0A_01_80048D1C = func_ovl0A_01_80047538();
            func_ovl0A_01_8004364C();
            break;
        case 16:
            func_ovl0A_01_80043338();
            break;
        case 17:
            func_ovl0A_01_80043300();
            break;
        case 18:
            func_ovl0A_01_800432C8();
            break;
        case 19:
            func_ovl0A_01_800432C8();
            break;
        case 4:
            func_ovl0A_01_8004328C();
            break;
        case 1:
            func_ovl0A_01_80043028();
            break;
        case 3:
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
    }
}

void func_ovl0A_01_80046A50(void) {
    f32 *pos;
    f32 x;
    f32 z;
    f32 y;
    Obj *obj;
    s32 i;
    f32 a;
    f32 dx;
    f32 dy;
    f32 dz;

    pos = func_ovl0A_01_80047FB0();
    x = pos[0];
    y = pos[1];
    z = pos[2];
    obj = func_ovl0A_01_80047E60(0x2D3, 0x01080000, 0xD0, NULL);
    obj->unk40->unk30 = 5.0f;
    obj->unk40->unk28 = obj->unk40->unk2C = obj->unk40->unk30;
    a = 200.0f;
    obj->unk40->unk10 = x;
    obj->unk40->unk14 = y;
    obj->unk40->unk18 = z;
    dx = (x - 2300.0f) / 180.0f;
    dy = (y - 100.0f) / 180.0f;
    dz = (z - 1400.0f) / 180.0f;
    for (i = 0; i < 180; i++) {
        a -= 0.6666667f;
        obj->unk40->unk10 -= dx;
        obj->unk40->unk14 -= dy;
        obj->unk40->unk18 -= dz;
        obj->unk40->unk28 *= 0.992f;
        obj->unk40->unk2C *= 0.992f;
        obj->unk40->unk30 *= 0.992f;
        obj->unk40->unk36 = a;
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80047E50(obj);
    func_ovl0A_01_80047F98();
}

void func_ovl0A_01_8004694C(void) {
    s32 i;

    func_ovl0A_01_80047E38(D_ovl0A_01_80048890[0].obj, 0x01000000);
    for (i = 0; i < 100; i++) {
        D_ovl0A_01_80048890[0].obj->unk40->unk18 -= 3.0f;
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80047FA8(5);
    func_ovl0A_01_80047B60(D_ovl0A_01_80048890[0].obj->unk40, 0, 0);
    func_ovl0A_01_80047B60(D_ovl0A_01_80048890[0].obj->unk40, 0, 1);
    func_ovl0A_01_80047BC8(0x34B, 2, 0x12C);
    func_ovl0A_01_800475A0(0);
    while (1) {
        func_ovl0A_01_80047FD0();
    }
}

void func_ovl0A_01_8004609C(void) {
    func_ovl0A_01_80046094();
    func_ovl0A_01_8004608C();
    func_ovl0A_01_80046084();
}

static void func_ovl0A_01_80046084(void) {
    s32 i;
    f32 a;
    f32 b;
    f32 cz;
    f32 fadeStep;
    f32 lz;

    a = 0.0f;
    D_ovl0A_01_80048A38[3] = 0;
    b = 0.0f;
    func_ovl0A_01_8004607C(1, LIGHTS);
    LIGHTS[0].unk0->unk10 = 2300.0f;
    LIGHTS[0].unk0->unk14 = 60.0f;
    LIGHTS[0].unk0->unk18 = 800.0f;
    LIGHTS[0].unk0->unk2C = 0.0f;
    LIGHTS[0].unk0->unk36 = 0xFF;
    func_ovl0A_01_80047B30(LIGHTS[0].unk0, 0x61);
    D_ovl0A_01_80048890[1].obj->unk40->unk14 = 0.0f;
    D_ovl0A_01_80048890[1].obj->unk40->unk28 = 0.0f;
    D_ovl0A_01_80048890[1].obj->unk40->unk2C = 0.0f;
    D_ovl0A_01_80048890[1].obj->unk40->unk36 = 0;
    D_ovl0A_01_80048890[1].obj->unk40->unkC |= 0x40000;
    func_ovl0A_01_80047E38(D_ovl0A_01_80048890[1].obj, 0x01000000);
    D_ovl0A_01_80048890[1].obj->unk40->unk20 = 14.0f;
    LIGHTS[0].unk0->unk20 = 14.0f;
    func_ovl0A_01_80048510(0x2CC);
    for (i = 0; i < 120; i++) {
        D_ovl0A_01_80048890[1].obj->unk40->unk14 += 2.9166667f;
        D_ovl0A_01_80048890[1].obj->unk40->unk28 += 0.008333334f;
        D_ovl0A_01_80048890[1].obj->unk40->unk2C += 0.008333334f;
        LIGHTS[0].unk0->unk2C += 0.016666668f;
        b += 1.25f;
        a += 2.125f;
        D_ovl0A_01_80048890[1].obj->unk40->unk36 = b;
        D_ovl0A_01_80048A38[3] = (u32) a;
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80047FA8(60);
    a = 255.0f;
    lz = 1805.0f;
    b = D_ovl0A_01_80048890[1].obj->unk40->unk36;
    cz = 255.0f;
    {
        fadeStep = (a - b) / 90.0f;
        func_ovl0A_01_80047B30(D_ovl0A_01_80048770[4].obj->unk40, 0x61);
        func_ovl0A_01_80047E38(D_ovl0A_01_80048770[6].obj, 0x80000);
        D_ovl0A_01_80048770[6].obj->unk40->unkC |= 0x1080;
        D_ovl0A_01_80048770[6].obj->unk40->unk36 = 0xFF;
        func_ovl0A_01_80047E38(D_ovl0A_01_80048770[7].obj, 0x80000);
        D_ovl0A_01_80048770[7].obj->unk40->unkC |= 0x80;
        D_ovl0A_01_80048770[7].obj->unk40->unk36 = 100;
        for (i = 0; i < 120; i++) {
            if (i >= 31) {
                a -= 2.8333333f;
                D_ovl0A_01_80048A38[3] = (u32) a;
                b += fadeStep;
                cz -= 2.8333333f;
                D_ovl0A_01_80048890[1].obj->unk40->unk36 = b;
                D_ovl0A_01_80048770[5].obj->unk40->unk36 = D_ovl0A_01_80048770[7].obj->unk40->unk36 =
                    D_ovl0A_01_80048770[6].obj->unk40->unk36 = (s32) cz;
                D_ovl0A_01_80048770[0].obj->unk40->unk18 += 2.0f;
                D_ovl0A_01_80048770[3].obj->unk40->unk18 += 2.0f;
            }
            lz += -3.7916667f;
            func_ovl0A_01_80047C98(32768.0f, 32768.0f, lz);
            func_ovl0A_01_80047FD0();
        }
    }
    D_ovl0A_01_80048890[1].obj->unk40->unkC &= ~0x40000;
    D_ovl0A_01_80048890[1].obj->unk40->unkC |= 0x80;
    D_ovl0A_01_80048890[1].obj->unk40->unk36 = 0xFF;
    func_ovl0A_01_80047FA8(120);
    a = 0.0f;
    func_ovl0A_01_80048510(0x2CD);
    for (i = 0; i < 120; i++) {
        func_ovl0A_01_80048288(0xFF, 0xFF, 0xFF, ((f32) i / 120.0f) * 100.0f);
        a += 0.15f;
        lz -= a;
        func_ovl0A_01_80047C98(32768.0f, 32768.0f, lz);
        func_ovl0A_01_80047FD0();
    }
}

static void func_ovl0A_01_8004607C(s32 n, Entry2 *tbl) {
    s32 i;

    for (i = 0; i < n; i++, tbl++) {
        tbl->unk0 = func_ovl0A_01_80047B98(tbl->unk18, 0);
        tbl->unk0->unkC |= tbl->unk14;
    }
}

static void func_ovl0A_01_8004608C(void) {
    s32 i;
    f32 cz;
    f32 cy;
    f32 cx;
    f32 ly;
    f32 lz;
    f32 lx;
    f32 t;

    cz = 611.229f;
    cy = -502.879f;
    cx = 2314.773f;
    ly = 33.2f;
    lx = 0;
    t = 0.0f;
    lz = 2425.0f;
    D_ovl0A_01_80048770[5].obj->unk40->unk36 = 0xFF;
    func_ovl0A_01_80047E38(D_ovl0A_01_80048770[5].obj, 0x01080000);
    func_ovl0A_01_80047B30(D_ovl0A_01_80048770[5].obj->unk40, 0x61);
    for (i = 0; i < 30; i++) {
        cz -= 2.8f;
        func_ovl0A_01_80047C78(2314.773f, -502.879f, cz);
        func_ovl0A_01_80047FD0();
        t += 8.5f;
    }
    func_ovl0A_01_80047FD0();
    {
        f32 z;

        z = cz;
        for (i = 0; i < 120; i++) {
            D_ovl0A_01_80048770[0].obj->unk40->unk20 += 1.5f;
            cx += -0.5417745f;
            cy += 6.8256583f;
            cz += (530.88f - z) / 120.0f;
            ly += -0.25750002f;
            lz += -5.1666665f;
            lx += 0.09666667f;
            func_ovl0A_01_80047C78(cx, cy, cz);
            func_ovl0A_01_80047C98(lx, ly, lz);
            func_ovl0A_01_80047FD0();
        }
    }
}

static void func_ovl0A_01_80046094(void) {
    while (D_ovl0A_01_80048770[2].obj->unk40->unk20 > 180.0f) {
        D_ovl0A_01_80048770[2].obj->unk40->unk20 -= 2.0f;
        D_ovl0A_01_80048770[2].obj->unk40->unk18 -= 2.0f;
        func_ovl0A_01_80047FD0();
    }
    D_ovl0A_01_80048770[2].obj->unk40->unk20 = 180.0f;
}

void func_ovl0A_01_80045EA0(void) {
    s32 wait;
    f32 pos[3];
    f32 s;

    wait = 2;
    while (1) {
        s = (func_ovl0A_01_80048148(1) == 1) ? 1.0f : -1.0f;
        pos[0] = (f32) (func_ovl0A_01_80048140() * 500.0) * s + 2300.0f;
        s = (func_ovl0A_01_80048148(1) == 1) ? 1.0f : -1.0f;
        pos[1] = (f32) (func_ovl0A_01_80048140() * 150.0) * s + 300.0f;
        s = (func_ovl0A_01_80048148(1) == 1) ? 1.0f : -1.0f;
        pos[2] = (f32) (func_ovl0A_01_80048140() * 800.0) * s + 1300.0f;
        func_ovl0A_01_80047F88(func_ovl0A_01_80046A50, pos, 0, 0, 0x130);
        func_ovl0A_01_80047FA8(wait);
        wait += 2;
    }
}

void func_ovl0A_01_80045C70(void) {
    f32 *pos;
    Obj *obj;
    s32 i;
    s32 j;
    f32 a;
    f32 s;

    pos = func_ovl0A_01_80047FB0();
    obj = func_ovl0A_01_80047E60(0x32B, 0x01080000, 0xD0, NULL);
    obj->unk40->unk10 = (pos[0] - 25.0f) + func_ovl0A_01_80048140() * 50.0;
    obj->unk40->unk14 = pos[1];
    obj->unk40->unk18 = (pos[2] - 25.0f) + func_ovl0A_01_80048140() * 50.0;
    func_ovl0A_01_80047B40(obj->unk40, 2);
    a = 180.0f;
    for (i = 0, j = 0; i < 35; i++) {
        s = 2.0f * (f32) (i / 35) + 2.5f;
        obj->unk40->unk30 = s;
        obj->unk40->unk2C = s;
        obj->unk40->unk28 = s;
        a -= 5.0f;
        obj->unk40->unk36 = a;
        obj->unk40->unk14 += 6.0f;
        if (j < 10) {
            if (!(j & 1)) {
                func_ovl0A_01_80047B48(obj->unk40, 0x32C, 0, j);
                func_ovl0A_01_80047B48(obj->unk40, 0x32C, 1, j + 1);
            }
            j += 2;
        }
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80047E50(obj);
    func_ovl0A_01_80047F98();
}

void func_ovl0A_01_80045908(void) {
    Obj *ring;
    Obj *flash;
    f32 *pos;
    s32 i;
    f32 a;

    ring = func_ovl0A_01_80047E60(0x1CC, 0x01080000, 0xD0, NULL);
    flash = func_ovl0A_01_80047E60(0x2D5, 0x01080000, 0xD0, NULL);
    pos = func_ovl0A_01_80047FB0();
    a = 180.0f;
    ring->unk40->unk10 = flash->unk40->unk10 = pos[0];
    ring->unk40->unk14 = flash->unk40->unk14 = pos[1];
    ring->unk40->unk18 = flash->unk40->unk18 = pos[2];
    ring->unk40->unk2C = 0.5f;
    flash->unk40->unk30 = 5.0f;
    flash->unk40->unk28 = flash->unk40->unk30;
    flash->unk40->unk2C = 0.1f;
    for (i = 0; i < 80; i++) {
        ring->unk40->unk2C += 0.04375f + 0.01f * func_ovl0A_01_80048130(i * 10.0f);
        flash->unk40->unk2C += 0.37375f;
        a += -1.0f;
        flash->unk40->unk36 = a;
        func_ovl0A_01_80047FD0();
    }
    for (i = 0; i < 80; i++) {
        ring->unk40->unk2C += 0.07f * func_ovl0A_01_80048130(i * 10.0f);
        flash->unk40->unk28 += 0.175f;
        flash->unk40->unk30 += 0.175f;
        func_ovl0A_01_80047FD0();
    }
    for (i = 0; i < 120; i++) {
        ring->unk40->unk2C += -0.029166667f + 0.05f * func_ovl0A_01_80048130(i * 10.0f);
        a += -0.7916667f;
        flash->unk40->unk36 = a;
        flash->unk40->unk28 += 0.175f;
        flash->unk40->unk30 += 0.175f;
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80047E50(ring);
    func_ovl0A_01_80047E50(flash);
    func_ovl0A_01_80047F98();
}

void func_ovl0A_01_800456C4(void) {
    Obj *obj;
    f32 *pos;
    s32 i;
    f32 v;
    f32 s;

    obj = func_ovl0A_01_80047E60(0x1C2, 0x01080000, 0xD0, NULL);
    pos = func_ovl0A_01_80047FB0();
    v = 0.0f;
    func_ovl0A_01_80047E70(obj);
    obj->unk40->unk10 = pos[0] + func_ovl0A_01_80048140() * 200.0;
    obj->unk40->unk14 = pos[1];
    obj->unk40->unk18 = pos[2] + (func_ovl0A_01_80048140() - 0.1) * 1000.0;
    s = (func_ovl0A_01_80048140() + 0.3) * 0.7;
    obj->unk40->unk30 = s;
    obj->unk40->unk28 = s;
    obj->unk40->unk2C = 0.7f;
    obj->unk40->unk1C = func_ovl0A_01_80048140() * 360.0;
    obj->unk40->unk20 = func_ovl0A_01_80048140() * 360.0;
    obj->unk40->unk24 = func_ovl0A_01_80048140() * 360.0;
    for (i = 0; i < 240; i++) {
        v += 0.1f;
        obj->unk40->unk14 += v;
        obj->unk40->unk1C += 3.0 * func_ovl0A_01_80048140();
        obj->unk40->unk24 += 3.0 * func_ovl0A_01_80048140();
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80047E50(obj);
    func_ovl0A_01_80047F98();
}

void func_ovl0A_01_80045288(void) {
    static f32 D_ovl0A_01_80048A78 = 0.01f;
    static f32 D_ovl0A_01_80048A7C = 0.0f;
    static f32 D_ovl0A_01_80048A80 = 0.0f;
    s32 i;

    func_ovl0A_01_80045280();
    func_ovl0A_01_80045278();
    func_ovl0A_01_80045270();
    for (i = 0;; i++) {
        if (i < 180) {
            D_ovl0A_01_800488D8[2].obj->unk40->unk10 += 7.111111f;
            D_ovl0A_01_800488D8[2].obj->unk40->unk18 += -1.1111112f;
        } else if (i == 180) {
            D_ovl0A_01_80048A78 = 0.01f;
            D_ovl0A_01_80048A80 = 15.0f;
            D_ovl0A_01_80048A7C = 0.0f;
        } else if (D_ovl0A_01_80048A78 > 0.0f) {
            D_ovl0A_01_80048A78 += 12.0f - D_ovl0A_01_80048A7C;
            D_ovl0A_01_80048A7C += 0.7f;
            D_ovl0A_01_80048A80 += 0.8f;
            if (D_ovl0A_01_80048A78 < 0.0f) {
                D_ovl0A_01_80048A80 = 180.0f;
                D_ovl0A_01_80048A78 = 0.0f;
                func_ovl0A_01_80047B60(D_ovl0A_01_800488D8[2].obj->unk40, 0x13, 0);
                D_ovl0A_01_800488D8[2].obj->unk40->unk48->unk4->unk4 =
                    func_ovl0A_01_80047B78(D_ovl0A_01_800488D8[2].obj->unk40, 0) - 0.1f;
                func_ovl0A_01_80047B60(D_ovl0A_01_800488D8[2].obj->unk40, 0, 1);
                D_ovl0A_01_800488D8[2].obj->unk40->unk48->unk4->unk8 |= 0x60;
                D_ovl0A_01_800488D8[2].obj->unk40->unk48->unk4->unk14 |= 0x20;
            }
            D_ovl0A_01_800488D8[2].obj->unk40->unk10 += 8.533334f;
            D_ovl0A_01_800488D8[2].obj->unk40->unk18 += -1.3333335f;
            D_ovl0A_01_800488D8[2].obj->unk40->unk1C = D_ovl0A_01_80048A80;
            if (D_ovl0A_01_80048A78 == 0.0f) {
                D_ovl0A_01_800488D8[2].obj->unk40->unk14 += 35.0f;
            } else {
                D_ovl0A_01_800488D8[2].obj->unk40->unk14 = D_ovl0A_01_80048A78;
            }
        }
        if (i < 220) {
            D_ovl0A_01_800488D8[3].obj->unk40->unk10 += 11.363636f;
            D_ovl0A_01_800488D8[3].obj->unk40->unk18 += -2.7272727f;
        }
        if (i == 220) {
            func_ovl0A_01_80047E40(D_ovl0A_01_800488D8[3].obj, 0x01000000);
        }
        if (i >= 81 && i < 330) {
            D_ovl0A_01_800488D8[4].obj->unk40->unk10 += 13.52f;
            D_ovl0A_01_800488D8[4].obj->unk40->unk18 += 2.8f;
        } else if (i == 330) {
            func_ovl0A_01_80047E40(D_ovl0A_01_800488D8[4].obj, 0x01000000);
        }
        func_ovl0A_01_80044968(i, 1.0f, 0.0f);
        func_ovl0A_01_80047FD0();
    }
}

static void func_ovl0A_01_80045270(void) {
}

static void func_ovl0A_01_80045278(void) {
}

static void func_ovl0A_01_80045280(void) {
}

Entry D_ovl0A_01_80048A84[3] = {
    { NULL, 0, 0x1CB, -1000.0f, 1500.0f, 2000.0f, -1, -1, 0.0f },
    { NULL, 0, 0xA, -200.0f, 20.0f, 900.0f, -1, -1, 0.0f },
    { NULL, 0, 0xA, -200.0f, 450.0f, 900.0f, -1, -1, 0.0f },
};
s32 D_ovl0A_01_80048AF0 = -1;
s32 D_ovl0A_01_80048AF4 = -1;
void func_ovl0A_01_80044F3C(void) {
    s32 i;
    s32 k;
    s32 played;
    f32 v;
    s32 u;
    f32 pos[3];

    func_ovl0A_01_80044A2C();
    v = 0;
    pos[0] = 200.0f;
    pos[2] = 900.0f;
    pos[1] = v;
    played = 0;
    D_ovl0A_01_800488D8[2].obj->unk40->unk1C = 90.0f;
    func_ovl0A_01_80047B60(D_ovl0A_01_800488D8[2].obj->unk40, 7, 0);
    func_ovl0A_01_80047B60(D_ovl0A_01_800488D8[2].obj->unk40, 0, 1);
    D_ovl0A_01_800488D8[2].obj->unk40->unk48->unk4->unk4 = 0.0f;
    func_ovl0A_01_80047E38(D_ovl0A_01_800488D8[2].obj, 0x04000000);
    D_ovl0A_01_800488D8[2].obj->unk40->unk48->unk4->unk8 |= 0x20;
    D_ovl0A_01_800488D8[2].obj->unk40->unk48->unk4->unk14 |= 0x20;
    for (i = 0, k = 0; i != 120; i++, k++) {
        if (k >= 15) {
            if (!played) {
                played = 1;
                func_ovl0A_01_80048510(0x2D4);
            }
            func_ovl0A_01_80047F88(func_ovl0A_01_80045908, pos, 0, 0, 0x130);
            func_ovl0A_01_80047F88(func_ovl0A_01_800456C4, pos, 0, 0, 0x130);
            k = 0;
        }
        pos[0] += 31.666666f;
        pos[2] += 3.3333333f;
        if (i == 20) {
            func_ovl0A_01_80047B60(D_ovl0A_01_800488D8[2].obj->unk40, 7, 0);
            func_ovl0A_01_80047B60(D_ovl0A_01_800488D8[2].obj->unk40, 6, 1);
            D_ovl0A_01_800488D8[2].obj->unk40->unk48->unk4->unk4 = 0.0f;
            func_ovl0A_01_80047E38(D_ovl0A_01_800488D8[2].obj, 0x0C000000);
        } else if (i >= 21) {
            v += 0.17f;
            D_ovl0A_01_800488D8[2].obj->unk40->unk14 += v;
            if (D_ovl0A_01_80048D1C == 0x13 && i == 100) {
                i = 0;
                k = 0;
                played = 1;
                func_ovl0A_01_80048688();
                break;
            }
        }
        func_ovl0A_01_80047FD0();
    }
    while (1) {
        func_ovl0A_01_80047FA8(200);
    }
}

static void func_ovl0A_01_80044A2C(void) {
    s32 i;
    s32 k;
    s32 played;
    f32 a1;
    f32 a0;
    f32 speed;
    f32 push;
    f32 fall;
    f32 tgt[3];

    a0 = 255.0f;
    speed = 1.5f;
    played = 0;
    a1 = 255.0f;
    push = 0.0f;
    fall = 0.0f;
    func_ovl0A_01_80043380(D_ovl0A_01_80048A84, 3);
    func_ovl0A_01_80047E38(D_ovl0A_01_80048A84[0].obj, 0x80000);
    func_ovl0A_01_80047E38(D_ovl0A_01_80048A84[1].obj, 0x80000);
    func_ovl0A_01_80047E38(D_ovl0A_01_80048A84[2].obj, 0x80000);
    D_ovl0A_01_80048A84[2].obj->unk40->unk1C = 180.0f;
    tgt[1] = 0.0f;
    tgt[0] = -200.0f;
    tgt[2] = 900.0f;
    func_ovl0A_01_80048288(0xFF, 0xFF, 0xFF, 100.0f);
    for (i = 0, k = 0; i < 120; i++, k++) {
        if (i == 8) {
            func_ovl0A_01_80048510(0x2D5);
        }
        if (i < 70) {
            tgt[0] += 62.142857f;
            tgt[2] += 5.714286f;
            func_ovl0A_01_80044A24(D_ovl0A_01_80048A84[0].obj, &D_ovl0A_01_80048A84[0].unkC, tgt);
            if (k >= 5) {
                k = 0;
                func_ovl0A_01_80047F88(func_ovl0A_01_80045C70, tgt, 0, 0, 0x130);
            }
        }
        if (!played) {
            played = 1;
            func_ovl0A_01_80048510(0x2D6);
        }
        if (i < 10) {
            func_ovl0A_01_80048288(0xFF, 0xFF, 0xFF, (f32) (10 / (10 - i)) * 100.0f);
        } else if (i == 10) {
            func_ovl0A_01_80048288(0, 0, 0, 0.0f);
        }
        if (i < 50) {
            a1 += -5.0f;
            D_ovl0A_01_80048A84[1].obj->unk40->unk36 = a1;
            D_ovl0A_01_80048A84[2].obj->unk40->unk36 = a1;
            D_ovl0A_01_80048A84[1].obj->unk40->unk28 += 2.0f;
            D_ovl0A_01_80048A84[1].obj->unk40->unk30 += 2.0f;
            D_ovl0A_01_80048A84[2].obj->unk40->unk28 += 3.0f;
            D_ovl0A_01_80048A84[2].obj->unk40->unk30 += 3.0f;
            func_ovl0A_01_80044968(0xC9, speed, 4.0f);
            push = 3.8f;
            D_ovl0A_01_800488D8[5].obj->unk40->unk1C -= 1.3f;
            fall = 3;
            if (i & 1) {
                D_ovl0A_01_800488D8[5].obj->unk40->unk48->unk4->unk4 *= 0.9f;
                D_ovl0A_01_800488D8[5].obj->unk40->unk48->unk4->unk10 *= 0.9f;
            }
            func_ovl0A_01_80044798(speed, &fall);
            speed += 0.1f;
        }
        if (push != 0.0f) {
            D_ovl0A_01_800488D8[2].obj->unk40->unk10 += push;
            push -= 0.5f;
            if (push < 0.0f) {
                push = 0.0f;
            }
            func_ovl0A_01_80044798(speed, &fall);
            speed += 0.1f;
        }
        a0 += -2.0f;
        D_ovl0A_01_80048A84[0].obj->unk40->unk36 = a0;
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80043018(3, D_ovl0A_01_80048A84);
}

static void func_ovl0A_01_80044A24(Obj *obj, f32 *pos, f32 *tgt) {
    f32 ang[3];
    s32 u1;
    s32 u2;

    func_ovl0A_01_80047DC8(pos, tgt, ang);
    obj->unk40->unk20 = ang[0];
    obj->unk40->unk1C = ((ang[1] - 180.0f) >= 360.0f ? (ang[1] - 180.0f) - 360.0f
                         : (ang[1] - 180.0f) < 0.0f ? (ang[1] - 180.0f) + 360.0f : (ang[1] - 180.0f)) * -1.0f;
    obj->unk40->unk2C = ang[2] / 100.0f;
}

static void func_ovl0A_01_80044968(s32 frame, f32 dx, f32 dy) {
    if (frame >= 0xC9 && frame < 0x190) {
        D_ovl0A_01_800488D8[5].obj->unk40->unk10 += 12.0f * dx;
        D_ovl0A_01_800488D8[5].obj->unk40->unk14 += dy;
        D_ovl0A_01_800488D8[5].obj->unk40->unk18 += 0.55f * dx;
    } else if (frame == 0x190) {
        func_ovl0A_01_80047E40(D_ovl0A_01_800488D8[5].obj, 0x01000000);
    }
}

static void func_ovl0A_01_80044798(f32 speed, f32 *fall) {
    Inner *m;

    func_ovl0A_01_80044790();
    m = D_ovl0A_01_800488D8[0].obj->unk40;
    if (m->unk20 > 72.0f) {
        m->unk10 += 12.0f * speed * 0.4f;
        m = D_ovl0A_01_800488D8[0].obj->unk40;
        m->unk18 += 0.55f * speed * 0.4f;
        m = D_ovl0A_01_800488D8[0].obj->unk40;
        m->unk20 += 1.0f;
        *fall += 5.0f;
    } else {
        switch ((s32) m->unk20) {
            case 0x39:
            case 0x3E:
            case 0x43:
            case 0x48:
                func_ovl0A_01_800483D8(0x16, m->unk10, m->unk14, m->unk18, 0);
                m = D_ovl0A_01_800488D8[0].obj->unk40;
                break;
        }
        m->unk24 += 2.0f;
        *fall += 4.0f;
    }
    m = D_ovl0A_01_800488D8[0].obj->unk40;
    m->unk14 -= *fall;
    m = D_ovl0A_01_800488D8[0].obj->unk40;
    m->unk20 += 1.0f;
    m = D_ovl0A_01_800488D8[0].obj->unk40;
    if (m->unk14 < 0.0f) {
        m->unk14 = 0.0f;
    }
}

static void func_ovl0A_01_80044790(void) {
}

void func_ovl0A_01_80044584(void) {
    s32 i;
    s32 started;
    s32 now;

    func_ovl0A_01_8004457C();
    i = 0;
    started = 0;
    func_ovl0A_01_80047E38(D_ovl0A_01_80048770[4].obj, 0x80000);
    for (; i < 300; i++) {
        now = 0;
        func_ovl0A_01_800441F8();
        func_ovl0A_01_800440F4();
        if (i == 130) {
            func_ovl0A_01_80047B60(D_ovl0A_01_80048770[0].obj->unk40, 0x1B, 0);
            now = 1;
            D_ovl0A_01_80048770[0].obj->unk40->unk48->unk4->unk8 |= 0x20;
            D_ovl0A_01_80048770[0].obj->unk40->unk48->unk4->unk4 = 0.0f;
        }
        if (now) {
            started = 1;
        }
        if (started) {
            if (i < 250) {
                func_ovl0A_01_800485A0(D_ovl0A_01_80048770[4].obj->unk40, 0x1F, 0x1F, 0x1F, (f32) (i - 130) / 120.0f);
            }
            func_ovl0A_01_80048288(0xFF, 0xFF, 0xFF, ((f32) (i - 130) / 170.0f) * 100.0f);
        }
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80047530(0x1A, 0x11, 3);
    func_ovl0A_01_80047F98();
}

static void func_ovl0A_01_8004457C(void) {
    D_ovl0A_01_80048A1C = 0;
    D_ovl0A_01_80048A20 = 0;
    D_ovl0A_01_80048A24 = 0;
}

void func_ovl0A_01_800442B4(void) {
    s32 i;

    func_ovl0A_01_800442AC();
    i = 0;
    func_ovl0A_01_800442A4();
    func_ovl0A_01_8004429C();
    func_ovl0A_01_80044294();
    func_ovl0A_01_8004428C();
    for (; i < 670; i++) {
        func_ovl0A_01_800441F8();
        func_ovl0A_01_800440F4();
        func_ovl0A_01_80043FF8(i);
        if (D_ovl0A_01_80048A70 != 0) {
            switch (D_ovl0A_01_80048A70) {
                case 1:
                    D_ovl0A_01_80048A74 += 0.05f;
                    if (D_ovl0A_01_80048A74 >= 1.0f) {
                        D_ovl0A_01_80048A74 = 1.0f;
                        D_ovl0A_01_80048A70 = 2;
                    }
                    break;
                case 2:
                    D_ovl0A_01_80048A74 -= 0.05f;
                    if (D_ovl0A_01_80048A74 <= 0.0f) {
                        D_ovl0A_01_80048A74 = 0.0f;
                        D_ovl0A_01_80048A70 = 1;
                    }
                    break;
                case 3:
                    D_ovl0A_01_80048A74 = 1.0f;
                    break;
            }
            func_ovl0A_01_800485A0(D_ovl0A_01_80048770[4].obj->unk40, 0x1F, 0x1F, 0x1F, D_ovl0A_01_80048A74);
        }
        if (i < 120) {
            func_ovl0A_01_80048288(0, 0, 0xFF, ((f32) (120 - i) / 120.0f) * 70.0f);
        }
        func_ovl0A_01_80047FD0();
    }
    for (; i < 1370; i++) {
        func_ovl0A_01_800441F8();
        func_ovl0A_01_800440F4();
        func_ovl0A_01_80043FF8(i);
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80047530(0x1A, 0x12, 4);
    func_ovl0A_01_80047F98();
}

static void func_ovl0A_01_8004428C(void) {
    D_ovl0A_01_80048A70 = 0;
    D_ovl0A_01_80048A64 = func_ovl0A_01_80047F88(func_ovl0A_01_80045EA0, NULL, 0, 0, 0x130);
}

static void func_ovl0A_01_80044294(void) {
    func_ovl0A_01_80047E40(D_ovl0A_01_80048890[1].obj, 0x01000000);
}

static void func_ovl0A_01_8004429C(void) {
    func_ovl0A_01_80047E40(D_ovl0A_01_80048890[0].obj, 0x01000000);
}

static void func_ovl0A_01_800442A4(void) {
    func_ovl0A_01_80047E38(D_ovl0A_01_80048770[4].obj, 0x80000);
}

static void func_ovl0A_01_800442AC(void) {
    D_ovl0A_01_80048A1C = 0.0f;
    D_ovl0A_01_80048A20 = 0.0f;
    D_ovl0A_01_80048A24 = 0.0f;
}

static void func_ovl0A_01_800441F8(void) {
    D_ovl0A_01_80048A1C += 2.0f;
    if (D_ovl0A_01_80048A1C >= 360.0f) {
        D_ovl0A_01_80048A1C -= 360.0f;
    }
    D_ovl0A_01_80048770[3].obj->unk40->unk14 = func_ovl0A_01_80048130(D_ovl0A_01_80048A1C) * 10.0f + 70.0f;
}

static void func_ovl0A_01_800440F4(void) {
    f32 s;
    D_ovl0A_01_80048A20 += 5.0f;
    if (D_ovl0A_01_80048A20 >= 360.0f) {
        D_ovl0A_01_80048A20 -= 360.0f;
        D_ovl0A_01_80048A24 *= 1.5f;
    }
    s = func_ovl0A_01_80048130(D_ovl0A_01_80048A20);
    D_ovl0A_01_80048770[4].obj->unk40->unk14 = 5.0f * s + 105.0f;
    D_ovl0A_01_80048770[4].obj->unk40->unk1C += 1.0f;
    D_ovl0A_01_80048770[4].obj->unk40->unk20 += 2.0f;
    D_ovl0A_01_80048770[4].obj->unk40->unk24 += 0.1f;
}

static void func_ovl0A_01_80043FF8(s32 frame) {
    switch (frame) {
        case 160:
            func_ovl0A_01_80043010(D_ovl0A_01_80048A64);
            break;
        case 425:
            D_ovl0A_01_80048A68 = func_ovl0A_01_80047F88(func_ovl0A_01_8004694C, NULL, 0, 0, 0x130);
            break;
        case 540:
            D_ovl0A_01_80048A70 = 1;
            D_ovl0A_01_80048A74 = 0.0f;
            break;
        case 670:
            D_ovl0A_01_80048A70 = 3;
            func_ovl0A_01_80043010(D_ovl0A_01_80048A68);
            D_ovl0A_01_80048A6C = func_ovl0A_01_80047F88(func_ovl0A_01_8004609C, NULL, 0, 0, 0x130);
            break;
    }
}

void func_ovl0A_01_80043DE8(void) {
    s32 i;
    f32 fade;

    func_ovl0A_01_80043DE0();
    i = 0;
    fade = 0.0f;
    for (; i < 900; i++) {
        switch (i) {
            case 120:
                func_ovl0A_01_80048510(0x2D3);
                func_ovl0A_01_80047D60(6.0f, 6.0f, 6.0f);
                func_ovl0A_01_80047D50(300);
                break;
            case 198:
                func_ovl0A_01_80048510(0x2DA);
                break;
            case 130:
                D_ovl0A_01_80048AF0 = func_ovl0A_01_80047F88(func_ovl0A_01_80045288, NULL, 0, 0, 0x130);
                break;
            case 450:
                func_ovl0A_01_80047D60(6.0f, 6.0f, 6.0f);
                func_ovl0A_01_80047D50(300);
                D_ovl0A_01_80048AF4 = func_ovl0A_01_80047F88(func_ovl0A_01_80044F3C, NULL, 0, 0, 0x130);
                break;
            case 620:
                func_ovl0A_01_80047D60(6.0f, 6.0f, 6.0f);
                func_ovl0A_01_80047D50(300);
                fade = 0;
                break;
        }
        if (D_ovl0A_01_80048D1C != 0x13 && i >= 620) {
            func_ovl0A_01_80048288(0xFF, 0, 0, fade);
            fade += 0.32142857f;
        }
        func_ovl0A_01_80047FD0();
    }
    func_ovl0A_01_80047530(0x1A, 0x13, 0);
    func_ovl0A_01_80047F98();
}

static void func_ovl0A_01_80043DE0(void) {
}

void func_ovl0A_01_80043AA4(void) {
    Obj *obj;
    f32 pos[3];
    f32 base[3];
    f32 tgt[3];
    f32 ang[3];
    s16 a;

    obj = func_ovl0A_01_80047E60(0x1CB, 0x01080000, 0xD0, NULL);
    obj->unk40->unk36 = 0;
    obj->unk40->unk36 = 0xB2;
    obj->unk40->unk30 = 0.5f;
    obj->unk40->unk28 = obj->unk40->unk30;
    pos[1] = 1000.0f;
    pos[0] = 600.0f;
    pos[2] = 2400.0f;
    func_ovl0A_01_80047F10(pos, obj);
    tgt[0] = base[0] = pos[0] + 250.0f;
    tgt[1] = pos[1] - 1000.0f;
    tgt[2] = base[2] = pos[2] - 1500.0f;
    while (1) {
        tgt[0] = func_ovl0A_01_80048140() * 260.0;
        if (func_ovl0A_01_80048148(1)) {
            tgt[0] *= -1.0f;
        }
        tgt[0] += base[0];
        tgt[2] = func_ovl0A_01_80048140() * 260.0;
        if (func_ovl0A_01_80048148(1)) {
            tgt[2] *= -1.0f;
        }
        tgt[2] += base[2];
        func_ovl0A_01_80047DC8(pos, tgt, ang);
        obj->unk40->unk20 = ang[0];
        obj->unk40->unk1C = ((ang[1] - 180.0f) >= 360.0f ? (ang[1] - 180.0f) - 360.0f
                             : (ang[1] - 180.0f) < 0.0f ? (ang[1] - 180.0f) + 360.0f : (ang[1] - 180.0f)) * -1.0f;
        obj->unk40->unk2C = ang[2] / 100.0f;
        obj->unk40->unk36 = 0xB2;
        func_ovl0A_01_800483E0(9, tgt, 0);
        func_ovl0A_01_80047D60(1.0f, 1.0f, 1.0f);
        func_ovl0A_01_80047D50(0x28);
        while (obj->unk40->unk36 > 0) {
            obj->unk40->unk36 -= 4;
            if (obj->unk40->unk36 < 0) {
                obj->unk40->unk36 = 0;
            }
            func_ovl0A_01_80047FD0();
        }
        func_ovl0A_01_80047FA8(func_ovl0A_01_80048148(8) + 2);
        func_ovl0A_01_80047FD0();
    }
}

void func_ovl0A_01_8004364C(void) {
    s32 i;
    s32 k;

    D_ovl0A_01_80048D20 = func_ovl0A_01_80047588();
    switch (D_ovl0A_01_80048D1C = func_ovl0A_01_80047538()) {
        case 16:
            func_ovl0A_01_80043380(&D_ovl0A_01_80048770[0], 8);
            func_ovl0A_01_800435E4();
            break;
        case 17:
            func_ovl0A_01_80043500(0x357);
            func_ovl0A_01_80043380(&D_ovl0A_01_80048770[0], 8);
            func_ovl0A_01_80043380(&D_ovl0A_01_80048890[0], 2);
            func_ovl0A_01_800435E4();
            break;
        case 18:
        case 19:
            func_ovl0A_01_80043500(0x296);
            {
            Entry *tbl;
            s32 n;
            s32 i;
            s32 j;
            s32 m;
            Entry *e;

            n = 9;
            tbl = &D_ovl0A_01_800488D8[0];
            for (i = 0; i < n; i++) {
                e = tbl;
                tbl->obj = func_ovl0A_01_80047E60(tbl->unk4 == 0 ? tbl->unk8 : 0x320, 0x0D000000, 0xD0, NULL);
                if (tbl->unk4 != 0) {
                    m = func_ovl0A_01_80047BA8(tbl->obj->unk40, 0x10);
                    for (j = 0; j < 0x10; j++) {
                        func_ovl0A_01_80047BB0(m, j, tbl->unk8);
                        func_ovl0A_01_80047BC0(m, j, j);
                    }
                }
                func_ovl0A_01_80047E70(tbl->obj);
                if (tbl->unk18 != -1 || tbl->unk1C != -1) {
                    func_ovl0A_01_80047B58(tbl->obj->unk40, 2);
                    func_ovl0A_01_80047B60(tbl->obj->unk40, tbl->unk18, 0);
                    func_ovl0A_01_80047B60(tbl->obj->unk40, tbl->unk1C, 1);
                    tbl->obj->unk40->unkC |= 0x4000;
                }
                tbl++;
                e->obj->unk40->unk10 = e->unkC;
                e->obj->unk40->unk14 = e->unk10;
                e->obj->unk40->unk18 = e->unk14;
                e->obj->unk40->unk20 = e->unk20;
            }
                if (0) {
                    func_ovl0A_01_80043380(tbl, n);
                }
            }

            func_ovl0A_01_80047450(0x35E);
            func_ovl0A_01_80047B40(D_ovl0A_01_800488D8[2].obj->unk40, 0xC);
            func_ovl0A_01_80047B40(D_ovl0A_01_800488D8[3].obj->unk40, 0xC);
            func_ovl0A_01_80047B40(D_ovl0A_01_800488D8[4].obj->unk40, 0xC);
            func_ovl0A_01_80047B40(D_ovl0A_01_800488D8[5].obj->unk40, 0xC);
            for (i = 0; i < 12; i++) {
                func_ovl0A_01_80047B48(D_ovl0A_01_800488D8[2].obj->unk40, 0x4C, i, i);
                func_ovl0A_01_80047B48(D_ovl0A_01_800488D8[3].obj->unk40, 0x4D, i, i);
                func_ovl0A_01_80047B48(D_ovl0A_01_800488D8[4].obj->unk40, 0x4C, i, i);
                func_ovl0A_01_80047B48(D_ovl0A_01_800488D8[5].obj->unk40, 0x4D, i, i);
            }
            D_ovl0A_01_800488D8[6].obj->unk40->unkC |= 0x2004;
            D_ovl0A_01_800488D8[6].obj->unk40->unk2C *= 1.8f;
            D_ovl0A_01_800488D8[7].obj->unk40->unkC |= 0x2004;
            D_ovl0A_01_800488D8[7].obj->unk40->unk2C *= 1.5f;
            D_ovl0A_01_800488D8[8].obj->unk40->unkC |= 0x2004;
            D_ovl0A_01_800488D8[8].obj->unk40->unk2C *= 1.5f;
            func_ovl0A_01_80047E38(D_ovl0A_01_800488D8[0].obj, 0x0C000000);
            func_ovl0A_01_80047C78(-1660.471f, 418.866f, -1088.718f);
            func_ovl0A_01_80047C98(58.4f, 358.3f, 6384.0f);
            break;
    }
}

static void func_ovl0A_01_800435E4(void) {
    func_ovl0A_01_80047C78(2314.773f, -502.879f, 611.229f);
    func_ovl0A_01_80047C88(2382.179f, 1443.399f, 3193.9951f);
    func_ovl0A_01_80047C98(0.0f, 33.2f, 2425.0f);
}

static void func_ovl0A_01_80043500(s32 id) {
    D_ovl0A_01_80048D24 = func_ovl0A_01_80048010(id);
    func_ovl0A_01_80048020(D_ovl0A_01_80048D24, 0x20000001);
    D_ovl0A_01_80048D24->unk40 = 1.0f;
    D_ovl0A_01_80048D24->unk44 = D_ovl0A_01_80048D24->unk40 * 0.75f;
    if (D_ovl0A_01_80048D1C == 0x12 || D_ovl0A_01_80048D1C == 0x13) {
        D_ovl0A_01_80048D24->unk3C = D_ovl0A_01_80048D24->unk4C * 0.3f;
        D_ovl0A_01_80048D24->unk18 = -0.01f;
        D_ovl0A_01_80048D24->unk1C = 0.0f;
    } else {
        D_ovl0A_01_80048D24->unk18 = 0.01f;
        D_ovl0A_01_80048D24->unk1C = -0.01f;
    }
}

static void func_ovl0A_01_80043380(Entry *tbl, s32 n) {
    s32 i;
    Entry *e;

    for (i = 0; i < n; i++) {
        e = tbl;
        tbl->obj = func_ovl0A_01_80047E60(tbl->unk4 == 0 ? tbl->unk8 : 0x320, 0x0D000000, 0xD0, NULL);
        if (tbl->unk4 != 0) {
            func_ovl0A_01_80043378(tbl);
        }
        func_ovl0A_01_80047E70(tbl->obj);
        if (tbl->unk18 != -1 || tbl->unk1C != -1) {
            func_ovl0A_01_80047B58(tbl->obj->unk40, 2);
            func_ovl0A_01_80047B60(tbl->obj->unk40, tbl->unk18, 0);
            func_ovl0A_01_80047B60(tbl->obj->unk40, tbl->unk1C, 1);
            tbl->obj->unk40->unkC |= 0x4000;
        }
        tbl++;
        func_ovl0A_01_80043370(e);
    }
}

static void func_ovl0A_01_80043370(Entry *e) {
    e->obj->unk40->unk10 = e->unkC;
    e->obj->unk40->unk14 = e->unk10;
    e->obj->unk40->unk18 = e->unk14;
    e->obj->unk40->unk20 = e->unk20;
}

static void func_ovl0A_01_80043378(Entry *e) {
    s32 j;
    s32 m;

    m = func_ovl0A_01_80047BA8(e->obj->unk40, 0x10);
    for (j = 0; j < 0x10; j++) {
        func_ovl0A_01_80047BB0(m, j, e->unk8);
        func_ovl0A_01_80047BC0(m, j, j);
    }
}

void func_ovl0A_01_80043338(void) {
    func_ovl0A_01_80047F88(func_ovl0A_01_80044584, NULL, 0, 0, 0x130);
}

void func_ovl0A_01_80043300(void) {
    func_ovl0A_01_80047F88(func_ovl0A_01_800442B4, NULL, 0, 0, 0x130);
}

void func_ovl0A_01_800432C8(void) {
    func_ovl0A_01_80047F88(func_ovl0A_01_80043DE8, NULL, 0, 0, 0x130);
}

void func_ovl0A_01_8004328C(void) {
    func_ovl0A_01_80043284();
    func_ovl0A_01_8004327C();
    func_ovl0A_01_80043274();
}

static void func_ovl0A_01_80043284(void) {
}

static void func_ovl0A_01_8004327C(void) {
    if (D_ovl0A_01_80048D1C == 0x11) {
        func_ovl0A_01_80048288(0, 0, 0xFF, 100.0f);
    }
}

static void func_ovl0A_01_80043274(void) {
}

void func_ovl0A_01_80043028(void) {
    switch (D_ovl0A_01_80048D1C) {
        case 16:
            func_ovl0A_01_80043018(8, &D_ovl0A_01_80048770[0]);
            break;
        case 17:
            func_ovl0A_01_80043018(8, &D_ovl0A_01_80048770[0]);
            func_ovl0A_01_80043018(2, &D_ovl0A_01_80048890[0]);
            func_ovl0A_01_80043020(1, LIGHTS);
            func_ovl0A_01_80048288(0, 0, 0, 0.0f);
            func_ovl0A_01_80043010(D_ovl0A_01_80048A6C);
            break;
        case 18:
        case 19:
            func_ovl0A_01_80043018(9, &D_ovl0A_01_800488D8[0]);
            func_ovl0A_01_80043010(D_ovl0A_01_80048AF0);
            func_ovl0A_01_80043010(D_ovl0A_01_80048AF4);
            if (D_ovl0A_01_80048D1C == 19) {
                func_ovl0A_01_80048690();
            } else {
                func_ovl0A_01_80048288(0, 0, 0, 0.0f);
            }
            break;
    }
    if (*D_ovl0A_01_80048D20 & 4) {
        func_ovl0A_01_800486F8();
    }
}

static void func_ovl0A_01_80043010(s32 task) {
    if (task != -1) {
        func_ovl0A_01_80047F90(task);
    }
}

static void func_ovl0A_01_80043020(s32 n, Entry2 *tbl) {
    s32 i;

    for (i = 0; i < n; i++) {
        if (tbl->unk0 != NULL) {
            func_ovl0A_01_80047B20(tbl->unk0);
        }
        tbl++;
    }
}

static void func_ovl0A_01_80043018(s32 n, Entry *tbl) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0A_01_80047E50(tbl->obj);
        tbl++;
    }
}

