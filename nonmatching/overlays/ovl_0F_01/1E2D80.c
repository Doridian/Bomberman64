/*
 * NON_MATCHING: ovl_0F_01's game object, complete: every function and its
 * data (.data and .bss as the original's sizes).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 3482, jp 3482
 *
 * The definition order is a hill-climb's (scratch/ovl_0F_01/search.py, from
 * the committed order, scored by distance from the original's emitted order,
 * words as the tie-break): 8713 -> 3482 words, emitted distance 14. The
 * address-taken functions (8004529C, 80045158, 80045DD4, 800452CC, 80044E54,
 * 8004464C, 80043628, 8004413C, 80043B0C, 80043348, 8004540C, 80043298, ...)
 * stay below 80043010 in emission, which stays first; no static was made
 * static for the count. Five statics are global here (80043094, 80043468,
 * 80043588, 800438C0, 80045E40); those are the search's flips, and the
 * original's linkage for them is not known from the asm.
 *
 * Emitted here: 3010 3094 324C 3298 3348 3468 +3504 3588 3628 38C0 +324C
 * 3B0C 413C +41CC +435C +4408 464C 4E54 52CC 5158 529C +3100 540C 5DD4
 * 5E40 +3030 5FB8 6988 69BC 6A04 6A60; the original: 3010 +3030 +3094 +3100
 * 324C 3298 3348 +3468 +3504 +3588 3628 +38C0 3B0C 413C +41CC +435C +4408
 * 464C 4E54 5158 529C 52CC 540C 5DD4 +5E40 5FB8. What still differs:
 * - func_ovl0F_01_80043B0C (355), 80044E54 (277), 8004413C (289),
 *   8004464C (477), 80043094 (106), 80045E40 (123): frames and registers.
 * - func_ovl0F_01_8004540C (620), 80045FB8 (610), 80043628 (152),
 *   800438C0 (178), 80043588 (49), 80043468 (70): the same, and the
 *   handler's inlined statics.
 * - func_ovl0F_01_80043010 (31 words; its size here is 0x8 against 0x84):
 *   the entry is empty in this draft, and its original is larger.
 * - 80045DD4 (4), 8004324C (2), 800452CC (56), 8004529C (83) are close.
 * - 80043298, 80043348, 80045158, 80046988, 800469BC, 80046A04 and 80046A60
 *   match.
 */
#include "common.h"

/*
 * ovl_0F_01's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). ovl_0F_04 (1F2230) and
 * ovl_0F_02 (1E84A0) share its movers and their script, ovl_0F_03 (1EE1A0)
 * its particles and the handler's shape, ovl_17_09 (2B8D20) its small
 * globals. The statics IDO inlines everywhere are named for the empty stubs
 * they leave.
 */

/* a model the stage places */
typedef struct {
    /* 0x00 */ UnkStructA **unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
} UnkStruct_ovl0F_01_80048264; /* size 0x2C */

/* seven arguments of func_ovl0F_01_80047038 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0F_01_80048508; /* size 0x1C */

/* one step of a mover's route (D_ovl0F_01_8004815C) */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
} UnkStruct_ovl0F_01_8004815C; /* size 0x8 */

/* a mover (D_ovl0F_01_800481D4): direction, speed, acceleration, route */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ s32 unk14;
} UnkStruct_ovl0F_01_800481D4; /* size 0x18 */

/* the movers' script (D_ovl0F_01_80048938) */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ UnkStructA **unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u16 (*unk18)[2];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ void (*unk20)(s32, s32);
} UnkStruct_ovl0F_01_80048938; /* size 0x24 */

/* one of the particles func_ovl0F_01_8004540C draws (D_ovl0F_01_80048798) */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0F_01_80048798; /* size 0x14 */

/* what func_ovl0F_01_80047508 returns: offsets into itself */
typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18[8];
    /* 0x20 */ s32 unk20;
} UnkStruct_ovl0F_01_80048130;

/* what func_ovl0F_01_800480D8 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ UnkStructA *unkC;
} UnkStruct_ovl0F_01_800480D8;

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_ovl0F_01_Gfx; /* size 0x8 */

/* gbi.h's _SHIFTL */
#define _SHIFTL(v, s, w) ((u32) (((u32) (v) & ((0x01 << (w)) - 1)) << (s)))

/* the ZeroJump stubs (0x80046AF0 on) */
void func_ovl0F_01_80046E38(s32);
void func_ovl0F_01_80046E50(s32);
f32 func_ovl0F_01_80046E60(void);
void func_ovl0F_01_80046E78(s32, s32, s32, s32, s32, s32);
void func_ovl0F_01_80046E98(f32, f32, f32, f32 *, s32);
void func_ovl0F_01_80046EC0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0F_01_80046F18(void (*)(UnkStructA *), s32);
void func_ovl0F_01_80046F20(void (*)(UnkStructA *));
s32 func_ovl0F_01_80046F38(void);
void func_ovl0F_01_80046F70(void (*)(UnkStructA *));
s32 *func_ovl0F_01_80046F88(void);
void func_ovl0F_01_80046FA0(s32);
void func_ovl0F_01_80046FC0(s32, s32);
void func_ovl0F_01_80046F30(s32, s32, s32);
void func_ovl0F_01_80046FE8(void);
void func_ovl0F_01_80046FF0(s32, s32, s32);
void func_ovl0F_01_80046FF8(void *);
s32 func_ovl0F_01_80047000(s32, s32, s32, s32);
s32 func_ovl0F_01_80047008(s32, s32, s32, s32, s32);
s32 func_ovl0F_01_80047018(void);
void func_ovl0F_01_80047020(s32, void *);
void func_ovl0F_01_80047028(s32);
void func_ovl0F_01_80047030(s32);
void func_ovl0F_01_80047038(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0F_01_80047040(char *);
void func_ovl0F_01_80047048(void);
UnkStructA *func_ovl0F_01_80047078(s32);
void func_ovl0F_01_80047080(s32);
void func_ovl0F_01_800470D8(s32);
UnkStruct_ovl0F_01_80048130 *func_ovl0F_01_80047508(s32);
void func_ovl0F_01_80047510(s32);
void func_ovl0F_01_80047520(UnkStructA *);
void func_ovl0F_01_80047528(UnkStructA *);
void func_ovl0F_01_80047540(UnkStructA_40 *, s32);
void func_ovl0F_01_80047548(UnkStructA_40 *, s32, s32, s32);
f32 func_ovl0F_01_80047578(UnkStructA_40 *, s32);
s32 func_ovl0F_01_80047580(UnkStructA_40 *, s32, s32, s32, s32, s32);
UnkStructA *func_ovl0F_01_80047598(void (*)(s32, UnkStruct_ovl0F_01_Gfx **), s32);
void func_ovl0F_01_800475A0(s32, s32);
void func_ovl0F_01_80047560(UnkStructA_40 *, s32, s32);
void func_ovl0F_01_80047590(UnkStructA_40 *, s32, s32);
void func_ovl0F_01_80047668(s32);
void func_ovl0F_01_80047678(f32, f32, f32);
void func_ovl0F_01_80047688(f32, f32, f32);
void func_ovl0F_01_80047698(f32, f32, f32);
void func_ovl0F_01_800476A0(f32 *, f32 *, f32 *);
s32 func_ovl0F_01_800476C8(void);
void func_ovl0F_01_800476D0(void);
void func_ovl0F_01_800476D8(s32);
void func_ovl0F_01_800476E0(s32);
void func_ovl0F_01_800476F0(s32);
void func_ovl0F_01_80047728(f32, f32, f32, f32);
void func_ovl0F_01_80047730(f32, f32);
void func_ovl0F_01_80047738(f32, f32, f32, f32);
void func_ovl0F_01_80047750(s32);
void func_ovl0F_01_80047760(f32, f32, f32);
void func_ovl0F_01_80047768(f32 *);
void func_ovl0F_01_80047780(Vec3f *);
void func_ovl0F_01_80047790(f32 *);
void func_ovl0F_01_80047798(void);
void func_ovl0F_01_800477A0(void);
void func_ovl0F_01_800477A8(f32, f32);
s32 func_ovl0F_01_800477E8(UnkStructA *, s32);
s32 func_ovl0F_01_80047800(UnkStructA *, UnkStructA *);
void func_ovl0F_01_80047838(UnkStructA *, s32);
void func_ovl0F_01_80047840(UnkStructA *, s32);
void func_ovl0F_01_80047850(UnkStructA *);
UnkStructA *func_ovl0F_01_80047860(s32, s32, s32, s32);
UnkStructA *func_ovl0F_01_80047870(UnkStructA *);
void func_ovl0F_01_800478B8(UnkStructA *);
void func_ovl0F_01_80047918(f32);
void func_ovl0F_01_80047920(s32);
s32 func_ovl0F_01_80047940(s32, Vec3f *, Vec3f *);
void func_ovl0F_01_80047948(UnkStructA *);
s32 func_ovl0F_01_80047988(void (*)(void), void *, s32, s32, s32);
void func_ovl0F_01_80047990(s32);
void func_ovl0F_01_80047998(void);
void func_ovl0F_01_800479A8(s32);
void *func_ovl0F_01_800479B0(void);
void func_ovl0F_01_800479D0(void);
f32 func_ovl0F_01_80047B30(f32);
f32 func_ovl0F_01_80047B38(f32);
f64 func_ovl0F_01_80047B40(void);
s32 func_ovl0F_01_80047B48(s32);
void func_ovl0F_01_80047C00(s32);
void func_ovl0F_01_80047C08(s32);
s32 func_ovl0F_01_80047C10(s32);
void func_ovl0F_01_80047C68(s32);
void func_ovl0F_01_80047CC8(s32, s32, s32, s32, s32);
void func_ovl0F_01_80047CD8(s32, s32, s32);
void func_ovl0F_01_80047CF0(u32 (*)[3]);
void func_ovl0F_01_80047DD8(s32, f32, f32, f32, s32);
void func_ovl0F_01_80047E18(void);
void func_ovl0F_01_80047E80(UnkStructA *, s32, f32, s32 (*)(s32));
void func_ovl0F_01_80047E98(s32, s32, s32);
void func_ovl0F_01_80047EF0(f32 *);
void func_ovl0F_01_80047EF8(void);
void func_ovl0F_01_80047F10(s32);
void func_ovl0F_01_80047F30(s32, f32, f32, f32);
void func_ovl0F_01_80047F38(s32, f32 *);
void func_ovl0F_01_800480C0(s32);
void func_ovl0F_01_800480C8(void);
s32 func_ovl0F_01_800480D0(void);
UnkStruct_ovl0F_01_800480D8 *func_ovl0F_01_800480D8(s32);
void func_ovl0F_01_800480E8(s32);
void func_ovl0F_01_800480F0(void);
void func_ovl0F_01_800480F8(void);

/* this file's */
static void func_ovl0F_01_8004435C(void);
static void func_ovl0F_01_80043030(s32 n, char *msg);
void func_ovl0F_01_80046A60(void);
void func_ovl0F_01_80046A04(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0F_01_800469BC(f32 arg0);
void func_ovl0F_01_80046988(s32 arg0, UnkStructA *arg1);
void func_ovl0F_01_80045FB8(s32 arg0);
void func_ovl0F_01_80045DD4(void);
void func_ovl0F_01_8004540C(s32 arg0, UnkStruct_ovl0F_01_Gfx **arg1);
static f32 func_ovl0F_01_80045404(f32 v);
void func_ovl0F_01_800452CC(s32 idx, s32 flag);
static s32 func_ovl0F_01_800452B4(UnkStructA *obj);
s32 func_ovl0F_01_8004529C(s32 arg0);
void func_ovl0F_01_80045158(void);
void func_ovl0F_01_80044E54(UnkStructA *arg0);
void func_ovl0F_01_8004464C(void);
void func_ovl0F_01_80045E40(UnkStructA **arg0);
static void func_ovl0F_01_80044408(s32 arg0, s32 arg1, s32 arg2, s32 flag);
static void func_ovl0F_01_800441CC(s16 i);
void func_ovl0F_01_8004413C(UnkStructA *obj);
void func_ovl0F_01_80043B0C(void);
static void func_ovl0F_01_80043018(s32 count, UnkStruct_ovl0F_01_80048264 *p);
s32 func_ovl0F_01_800438C0(f32 *x);
void func_ovl0F_01_80043628(void);
void func_ovl0F_01_80043588(UnkStruct_ovl0F_01_80048264 *p, s32 count);
void func_ovl0F_01_80043468(UnkStructA *obj);
void func_ovl0F_01_80043348(UnkStructA *arg0);
void func_ovl0F_01_80043298(void);
void func_ovl0F_01_8004324C(void);
static void func_ovl0F_01_80043100(UnkStruct_ovl0F_01_80048798 *p);
static void func_ovl0F_01_80043504(UnkStruct_ovl0F_01_80048264 *arg0);
void func_ovl0F_01_80043094(s32 *arg0);
void func_ovl0F_01_80043010(void);

/* .bss */
UnkStructA *D_ovl0F_01_80048720[6];
UnkStructA *D_ovl0F_01_80048738[3];
UnkStructA *D_ovl0F_01_80048744;
UnkStructA *D_ovl0F_01_80048748;
u8 D_ovl0F_01_8004874C[0x4];
f32 D_ovl0F_01_80048750[3];
u8 D_ovl0F_01_8004875C[0x4];
Vec3f D_ovl0F_01_80048760;
s32 D_ovl0F_01_8004876C;
u8 D_ovl0F_01_80048770[0x4];
s32 D_ovl0F_01_80048774;
s32 D_ovl0F_01_80048778;
u8 D_ovl0F_01_8004877C[0x4];
Vec3f D_ovl0F_01_80048780;
UnkStructA *D_ovl0F_01_8004878C;
s32 *D_ovl0F_01_80048790;
u8 D_ovl0F_01_80048794[0x4];
UnkStruct_ovl0F_01_80048798 D_ovl0F_01_80048798[20];
Vec3f D_ovl0F_01_80048928;
u8 D_ovl0F_01_80048934[0x4];
UnkStruct_ovl0F_01_80048938 D_ovl0F_01_80048938;

/* .data */
UnkStruct_ovl0F_01_80048130 *D_ovl0F_01_80048130 = NULL;
f32 D_ovl0F_01_80048134 = 0.0f;
f32 D_ovl0F_01_80048138 = 0.0f;
f32 D_ovl0F_01_8004813C = 0.0f;
f32 D_ovl0F_01_80048140 = 0.0f;
f32 D_ovl0F_01_80048144 = 0.0f;
/* the movers' script runs */
s32 D_ovl0F_01_80048148 = 0;
/* the movers' script: frame, command (100 ends it) */
u16 D_ovl0F_01_8004814C[][2] = {
    { 0, 7 }, { 0x1E, 8 }, { 0x3C, 9 }, { 0x64, 0x64 },
};
/* three routes of five steps */
UnkStruct_ovl0F_01_8004815C D_ovl0F_01_8004815C[3][5] = {
    {
        { 0x32, 0x60, 1, 0.01f },
        { 0x32, 0x40, 2, 0.1f },
        { 0x32, 0x20, 3, 0.02f },
        { 0x1E, 0x40, 4, 0.03f },
        { 0x14, 0x20, 0, 0.05f },
    },
    {
        { 0x32, 0x40, 1, 0.001f },
        { 0x32, 0x60, 2, 0.001f },
        { 0x32, 0x40, 3, 0.01f },
        { 0x32, 0x20, 4, 0.001f },
        { 0x32, 0x40, 0, 0.01f },
    },
    {
        { 0x14, 0x40, 1, 0.1f },
        { 0x14, 0x60, 2, 0.05f },
        { 0x14, 0x40, 3, 0.15f },
        { 0x14, 0x20, 0, 0.05f },
        { 0x14, 0x40, 0, 0.2f },
    },
};
UnkStruct_ovl0F_01_800481D4 D_ovl0F_01_800481D4[6] = {
    { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 1 }, { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 1 }, { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
    { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 1 }, { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 1 }, { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
};
/* the movers' models */
UnkStruct_ovl0F_01_80048264 D_ovl0F_01_80048264[6] = {
    { &D_ovl0F_01_80048720[0], 0x259, 0, 0.0f, 4.0f, 6.0f, 0.0f, 90.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_01_80048720[1], 0x259, 0, 0.0f, 4.0f, 11.0f, 0.0f, 90.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_01_80048720[2], 0x259, 0, 0.0f, 4.0f, 17.0f, 0.0f, 90.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_01_80048720[3], 0x259, 0, 45.0f, 4.0f, 8.0f, 0.0f, 270.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_01_80048720[4], 0x259, 0, 45.0f, 4.0f, 12.0f, 0.0f, 270.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_01_80048720[5], 0x259, 0, 45.0f, 4.0f, 17.0f, 0.0f, 270.0f, 0.0f, 0x0C000070, 0 },
};
/* the three floating platforms */
UnkStruct_ovl0F_01_80048264 D_ovl0F_01_8004836C[3] = {
    { &D_ovl0F_01_80048738[0], 0x269, 0, 1.0f, 4.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_01_80048738[1], 0x269, 0, 1.0f, 4.0f, 11.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_01_80048738[2], 0x269, 0, 1.0f, 4.0f, 16.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};
UnkStruct_ovl0F_01_80048264 D_ovl0F_01_800483F0 = {
    &D_ovl0F_01_80048744, 0xEB, 0, 4.0f, 3.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0, 0,
};
/* the platforms' task, and what it is at */
s32 D_ovl0F_01_8004841C = -1;
s32 D_ovl0F_01_80048420 = 0;
f32 D_ovl0F_01_80048424 = 0.01f;
UnkStructA *D_ovl0F_01_80048428 = NULL;
/* the switch: its state and task */
s32 D_ovl0F_01_8004842C = 0;
s32 D_ovl0F_01_80048430 = -1;
s32 D_ovl0F_01_80048434 = 0;
/* passed to func_ovl0F_01_80047CF0: three 12-byte records */
u32 D_ovl0F_01_80048438[][3] = {
    { 0x2640002, 0xF, 4 },
    { 0x25C0002, 0xF, 4 },
    { 0xDA0000, 0xF, 4 },
};
UnkStruct_ovl0F_01_80048264 D_ovl0F_01_8004845C = {
    &D_ovl0F_01_80048748, 0x26A, 0, 13.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0, 0,
};
/* six 12-byte records, each passed to func_ovl0F_01_80047E98 */
u32 D_ovl0F_01_80048488[][3] = {
    { 0, 0x12, 0xF0 }, { 1, 0x13, 0xF1 }, { 2, 0x16, 0xF4 }, { 3, 0, 0xDE }, { 4, 2, 0xE0 }, { 5, 0x15, 0xF3 },
};
/* func_ovl0F_01_80043094's: four arguments to test, three to pass on */
s32 D_ovl0F_01_800484D0[7] = { 6, 0x1A, 6, 0x1A, 0x59, 0x11, 0 };
s32 D_ovl0F_01_800484EC[7] = { 0x2D, 0x18, 0x2D, 0x18, 0x5B, 0x11, 0 };
UnkStruct_ovl0F_01_80048508 D_ovl0F_01_80048508[4] = {
    { 0x40, 3, 8.5f, 2, 0, 1, 0 },
    { 0xC0, 3, 8.5f, 3, 0, 1, 0 },
    { 0x40, 3, 17.0f, 0xD, 0, 1, 1 },
    { 0xC0, 3, 17.0f, 0xD, 0, 1, 1 },
};
s32 D_ovl0F_01_80048578[2] = { 0, 0 };
char D_ovl0F_01_80048580[] = "MA";
char D_ovl0F_01_80048584[] = "WAP WM1 WG1 WSH WDN WB1 ST1 WDNW WB9 ST1";
char D_ovl0F_01_800485B0[] = "WM1 WG1 WSH WAP WDS WB2 ST30";
char D_ovl0F_01_800485D0[] = "WM1 WG1 WSH WAP WDE WB1 ST30";

/* case 2's: the stage's tables */
static void func_ovl0F_01_8004435C(void) {
    s32 count;
    u32 (*p)[3];
    s32 i;

    func_ovl0F_01_80047CF0(D_ovl0F_01_80048438);
    p = D_ovl0F_01_80048488;
    count = 6;
    for (i = 0; i < count; i++) {
        func_ovl0F_01_80047E98((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}

/* the cut-scene: a task counts n frames while a message shows */
static void func_ovl0F_01_80043030(s32 n, char *msg) {
    func_ovl0F_01_800470D8(1);
    func_ovl0F_01_80047E18();
    func_ovl0F_01_80047988(func_ovl0F_01_80045DD4, (void *) n, 0, 0, 0x130);
    func_ovl0F_01_80047040(msg);
    func_ovl0F_01_800470D8(0);
    func_ovl0F_01_80047040(D_ovl0F_01_80048580);
}

void func_ovl0F_01_80046A60(void) {
    D_ovl0F_01_80048774 = -1;
    D_ovl0F_01_80048778 = -1;
}

void func_ovl0F_01_80046A04(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_01_80047678(D_ovl0F_01_80048780.x, D_ovl0F_01_80048780.y, D_ovl0F_01_80048780.z);
    func_ovl0F_01_80047698(arg0, arg1, arg2);
    func_ovl0F_01_800479A8(180);
}

void func_ovl0F_01_800469BC(f32 arg0) {
    f32 sp1C;

    func_ovl0F_01_800476A0(&sp1C, NULL, NULL);
    func_ovl0F_01_80047698(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0F_01_80046988(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0F_01_80047F30(arg0, p->unk10, p->unk14, p->unk18);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_01_80045FB8(s32 arg0) {
    UnkStruct_ovl0F_01_800480D8 *q;
    f32 y;
    s32 i;

    switch (arg0) {
        case 2:
            D_ovl0F_01_80048434 = 0;
            D_ovl0F_01_80048790 = func_ovl0F_01_80046F88();
            func_ovl0F_01_8004435C();
            func_ovl0F_01_80046E38(0x223);
            func_ovl0F_01_80046E50(0x237);
            D_ovl0F_01_8004842C = 0;
            D_ovl0F_01_80048430 = func_ovl0F_01_80047988(func_ovl0F_01_80043628, NULL, 0, 0, 0x110);
            func_ovl0F_01_80046FE8();
            func_ovl0F_01_80045E40(&D_ovl0F_01_80048428);
            func_ovl0F_01_80046F18(func_ovl0F_01_8004413C, 5);
            D_ovl0F_01_8004841C = func_ovl0F_01_80047988(func_ovl0F_01_80043B0C, NULL, 0, 0, 0x110);
            break;
        case 16:
            func_ovl0F_01_80046FF0(0x18, 3, 0x10);
            break;
        case 17:
            func_ovl0F_01_80046FF0(0xD, 0, 8);
            break;
        case 18:
            func_ovl0F_01_80047030(0x40);
            func_ovl0F_01_80046FF0(6, 1, 0x1A);
            break;
        case 20:
            func_ovl0F_01_80047698(315.0f, 32768.0f, 32768.0f);
            func_ovl0F_01_80047030(0xC0);
            func_ovl0F_01_80046FF0(0x2D, 1, 0x18);
            break;
        case 21:
            func_ovl0F_01_80047C68(1);
            func_ovl0F_01_80047030(0x40);
            func_ovl0F_01_80046FF0(1, 4, 0xC);
            func_ovl0F_01_8004324C();
            func_ovl0F_01_80046FC0(0x58, 0x17);
            break;
        case 22:
            func_ovl0F_01_80047C68(1);
            func_ovl0F_01_80047030(0xC0);
            func_ovl0F_01_80046FF0(0x2E, 4, 0xB);
            func_ovl0F_01_8004324C();
            func_ovl0F_01_80046FC0(0x58, 0x18);
            break;
        case 23:
            func_ovl0F_01_80046FF0(0xE, 0, 0xC);
            break;
        case 24:
            func_ovl0F_01_80046FF0(0x21, 0, 0xB);
            break;
        case 25:
            func_ovl0F_01_80047030(0);
            func_ovl0F_01_80046FF0(0x1B, 0, 0xE);
            break;
        case 4:
            func_ovl0F_01_80047048();
            func_ovl0F_01_80046F20(func_ovl0F_01_80043348);
            func_ovl0F_01_800476D8(0x5F);
            func_ovl0F_01_80047728(2200.0f, 1600.0f, 800.0f, 2000.0f);
            func_ovl0F_01_800477A8(800.0f, 1200.0f);
            func_ovl0F_01_80047738(2400.0f, 1600.0f, 2400.0f, 1600.0f);
            func_ovl0F_01_80047730(70.0f, 55.0f);
            func_ovl0F_01_80047CD8(0xE6, 0xF0, 0xFF);
            func_ovl0F_01_80047CC8(0x3B1, 0x3CA, 0xE6, 0xF0, 0xFF);
            D_ovl0F_01_80048130 = func_ovl0F_01_80047508(0x258);
            D_ovl0F_01_8004878C = func_ovl0F_01_80047598(func_ovl0F_01_8004540C, -60);
            D_ovl0F_01_8004878C->unkC |= 0x210;
            for (i = 0; i < 20; i++) {
                func_ovl0F_01_80043100(&D_ovl0F_01_80048798[i]);
                D_ovl0F_01_80048798[i].unk4 = func_ovl0F_01_80047B48(240);
            }
            func_ovl0F_01_80047780(&D_ovl0F_01_80048928);
            D_ovl0F_01_8004813C = 0.0f;
            D_ovl0F_01_80048140 = 0.0f;
            D_ovl0F_01_80048144 = 1.0f;
            func_ovl0F_01_80047C00(0x407);
            func_ovl0F_01_80047918(40.0f);
            func_ovl0F_01_80047920(30);
            if (*D_ovl0F_01_80048790 & 4) {
                func_ovl0F_01_80047698(135.0f, 32768.0f, 32768.0f);
                func_ovl0F_01_80047988(func_ovl0F_01_80043298, NULL, 0, 0, 0x130);
                func_ovl0F_01_800476E0(0xF);
                func_ovl0F_01_800476F0(1);
            }
            break;
        case 5:
            switch (func_ovl0F_01_80046F38()) {
                case 18:
                    func_ovl0F_01_80047038(D_ovl0F_01_80048508[0].unk0, D_ovl0F_01_80048508[0].unk4,
                                           D_ovl0F_01_80048508[0].unk8, D_ovl0F_01_80048508[0].unkC,
                                           D_ovl0F_01_80048508[0].unk10, D_ovl0F_01_80048508[0].unk14,
                                           D_ovl0F_01_80048508[0].unk18);
                    break;
                case 20:
                    func_ovl0F_01_80047038(D_ovl0F_01_80048508[1].unk0, D_ovl0F_01_80048508[1].unk4,
                                           D_ovl0F_01_80048508[1].unk8, D_ovl0F_01_80048508[1].unkC,
                                           D_ovl0F_01_80048508[1].unk10, D_ovl0F_01_80048508[1].unk14,
                                           D_ovl0F_01_80048508[1].unk18);
                    break;
                case 21:
                    func_ovl0F_01_80047038(D_ovl0F_01_80048508[2].unk0, D_ovl0F_01_80048508[2].unk4,
                                           D_ovl0F_01_80048508[2].unk8, D_ovl0F_01_80048508[2].unkC,
                                           D_ovl0F_01_80048508[2].unk10, D_ovl0F_01_80048508[2].unk14,
                                           D_ovl0F_01_80048508[2].unk18);
                    break;
                case 22:
                    func_ovl0F_01_80047038(D_ovl0F_01_80048508[3].unk0, D_ovl0F_01_80048508[3].unk4,
                                           D_ovl0F_01_80048508[3].unk8, D_ovl0F_01_80048508[3].unkC,
                                           D_ovl0F_01_80048508[3].unk10, D_ovl0F_01_80048508[3].unk14,
                                           D_ovl0F_01_80048508[3].unk18);
                    break;
            }
            break;
        case 0x50:
            func_ovl0F_01_80043094(D_ovl0F_01_800484D0);
            func_ovl0F_01_80043094(D_ovl0F_01_800484EC);
            break;
        case 0x52:
            if (func_ovl0F_01_80047000(1, 0x15, 1, 0x15) != 0 && func_ovl0F_01_80047C10(0x406) == 0) {
                func_ovl0F_01_80047C00(0x406);
                if (func_ovl0F_01_800476C8() == 1) {
                    func_ovl0F_01_800476D0();
                }
                func_ovl0F_01_80047798();
                func_ovl0F_01_800476E0(0x1F);
                func_ovl0F_01_80047698(271.0f, 50.4f, 1728.0f);
                func_ovl0F_01_80047688(-627.4f, 2685.0f, 3200.3f);
                func_ovl0F_01_80047678(447.4f, 1425.9f, 2032.76f);
                func_ovl0F_01_80043030(30, D_ovl0F_01_800485B0);
            }
            break;
        case 0x53:
            if (func_ovl0F_01_80047000(2, 0x15, 2, 0x15) != 0 && func_ovl0F_01_80047C10(0x406) != 0) {
                func_ovl0F_01_80047C08(0x406);
                func_ovl0F_01_800476D8(0x1F);
                func_ovl0F_01_80047668(1);
                func_ovl0F_01_800477A0();
                func_ovl0F_01_80047768(D_ovl0F_01_80048750);
                func_ovl0F_01_80043030(30, D_ovl0F_01_800485D0);
            }
            break;
        case 15:
            if (func_ovl0F_01_80047008(0xD, 0, 3, 0xD, 3) != 0) {
                y = func_ovl0F_01_80047078(func_ovl0F_01_80047018())->unk40->unk20;
                if (135.0f <= y && y <= 225.0f) {
                    switch (D_ovl0F_01_8004842C) {
                        case 0:
                            func_ovl0F_01_800475A0(0x275, 1);
                            break;
                        case 1:
                            func_ovl0F_01_800475A0(0x276, 1);
                            break;
                    }
                }
            }
            break;
        case 1:
            func_ovl0F_01_80043018(3, D_ovl0F_01_8004836C);
            if (D_ovl0F_01_8004841C != -1) {
                func_ovl0F_01_80047990(D_ovl0F_01_8004841C);
            }
            func_ovl0F_01_80047528(D_ovl0F_01_8004878C);
            func_ovl0F_01_80043018(1, &D_ovl0F_01_8004845C);
            func_ovl0F_01_80047510(0x258);
            if (D_ovl0F_01_80048430 != -1) {
                func_ovl0F_01_80047990(D_ovl0F_01_80048430);
                D_ovl0F_01_80048430 = -1;
            }
            if (*D_ovl0F_01_80048790 & 4) {
                func_ovl0F_01_800480D8(2)->unkC->unkC |= 1;
                func_ovl0F_01_80047CD8(0, 0, 0);
                func_ovl0F_01_800480C8();
                q = func_ovl0F_01_800480D8(4);
                if (q->unkC != NULL) {
                    func_ovl0F_01_80047520(q->unkC);
                }
                q->unkC = NULL;
                func_ovl0F_01_800480F8();
            }
            break;
        case 12:
            func_ovl0F_01_80047080(1);
            break;
        case 3:
            D_ovl0F_01_80048434 = 1;
            D_ovl0F_01_8004876C = func_ovl0F_01_80047018();
            func_ovl0F_01_80046FF8(&D_ovl0F_01_80048760);
            func_ovl0F_01_80047020(D_ovl0F_01_8004876C, D_ovl0F_01_80048750);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
        case 19:
            break;
    }
}

void func_ovl0F_01_80045DD4(void) {
    s32 n;
    s32 i;

    n = (s32)func_ovl0F_01_800479B0();
    for (i = 0; i < n; i++) {
        func_ovl0F_01_80047EF8();
        func_ovl0F_01_800479D0();
    }
    func_ovl0F_01_80047998();
}

void func_ovl0F_01_8004540C(s32 arg0, UnkStruct_ovl0F_01_Gfx **arg1) {
    UnkStruct_ovl0F_01_Gfx *gfx;
    UnkStruct_ovl0F_01_80048798 *p;
    f32 oldx;
    f32 oldz;
    f32 s;
    f32 c;
    f32 scale;
    f32 sign;
    f32 dx;
    f64 drift;
    s32 dsdx;
    s32 i;
    f32 view[8];

    gfx = *arg1;
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x00553048; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF279; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBB000001; g->w1 = 0x80008000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0x8000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xFD100000; g->w1 = D_ovl0F_01_80048130->unk20 + (u32) D_ovl0F_01_80048130; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE8000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF5000100; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF0000000; g->w1 = 0x0703C000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xFD500000; g->w1 = D_ovl0F_01_80048130->unk14 + (u32) D_ovl0F_01_80048130; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF5500000; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF3000000; g->w1 = 0x0703F800; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF5400200; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF2000000; g->w1 = 0x0003C03C; }
    oldx = D_ovl0F_01_80048928.x;
    oldz = D_ovl0F_01_80048928.z;
    func_ovl0F_01_80047780(&D_ovl0F_01_80048928);
    func_ovl0F_01_80047790(view);
    s = func_ovl0F_01_80047B38(view[0]);
    c = func_ovl0F_01_80047B30(view[0]);
    D_ovl0F_01_80048134 = ((D_ovl0F_01_80048928.x - oldx) * s - c * (D_ovl0F_01_80048928.z - oldz)) * 0.5f;
    s = func_ovl0F_01_80047B38(view[0]);
    c = func_ovl0F_01_80047B30(view[0]);
    D_ovl0F_01_80048138 = (c * (D_ovl0F_01_80048928.x - oldx) + (D_ovl0F_01_80048928.z - oldz) * s) * 0.2f;
    scale = 1500.0f / view[2];
    D_ovl0F_01_80048134 *= scale;
    D_ovl0F_01_80048138 *= scale;
    i = 0;
    if (func_ovl0F_01_80047C10(0x407) == 0) {
        goto update;
    }
    do {
        p = &D_ovl0F_01_80048798[i];
        dsdx = 16.0f / (p->unk8 - 1.0f) * 1024.0f;
        {
            UnkStruct_ovl0F_01_Gfx *g = gfx++;
            g->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL((u32) (p->unk0 + p->unk8 - 1.0f) << 2, 12, 12) | _SHIFTL((u32) (p->unk4 + p->unk8 - 1.0f) << 2, 0, 12);
            g->w1 = _SHIFTL(0, 24, 3) | _SHIFTL((u32) p->unk0 << 2, 12, 12) | _SHIFTL((u32) p->unk4 << 2, 0, 12);
        }
        { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xB4000000; g->w1 = 0; }
        { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xB3000000; g->w1 = _SHIFTL(dsdx, 16, 16) | _SHIFTL(dsdx, 0, 16); }
    update:
        if (D_ovl0F_01_80048144 != 0.0f) {
            p = &D_ovl0F_01_80048798[i];
            s = func_ovl0F_01_80047B38(view[0]);
            dx = -D_ovl0F_01_80048134;
            p->unk0 += dx - (f32) func_ovl0F_01_80047B40() * (dx * 0.25f) + D_ovl0F_01_8004813C * s;
            sign = func_ovl0F_01_80045404(D_ovl0F_01_8004813C);
            if (func_ovl0F_01_80047B30(view[0]) * (sign * D_ovl0F_01_8004813C) + D_ovl0F_01_80048140 < 0.0f) {
                sign = func_ovl0F_01_80045404(D_ovl0F_01_8004813C);
                drift = (func_ovl0F_01_80047B30(view[0]) * (sign * D_ovl0F_01_8004813C) + D_ovl0F_01_80048140) * 0.5;
            } else {
                sign = func_ovl0F_01_80045404(D_ovl0F_01_8004813C);
                drift = func_ovl0F_01_80047B30(view[0]) * (sign * D_ovl0F_01_8004813C) + D_ovl0F_01_80048140;
            }
            p->unk4 += (p->unkC - D_ovl0F_01_80048138) - (f32) func_ovl0F_01_80047B40() * ((p->unkC - D_ovl0F_01_80048138) * 0.6f) + drift;
            p->unk8 -= 0.1f * (p->unk8 * 0.0625f);
            if (340.0f <= p->unk0 || 240.0f <= p->unk4 || p->unk8 <= 3.0f || p->unk10++ >= 240 || p->unk0 < -20.0f ||
                p->unk4 < -10.0f) {
                func_ovl0F_01_80043100(p);
            }
        }
        i++;
    } while (i != 20);
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0x00080000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0; }
    *arg1 = gfx;
}

static f32 func_ovl0F_01_80045404(f32 v) {
    return v == 0.0f ? 0.0f : 1.0f;
}

/* the script's command: a mover (re)starts at a random speed on a random
 * route, high above; with flag 0 it stays stopped */
void func_ovl0F_01_800452CC(s32 idx, s32 flag) {
    UnkStruct_ovl0F_01_80048264 *p;
    UnkStruct_ovl0F_01_800481D4 *m;

    p = &D_ovl0F_01_80048264[idx];
    func_ovl0F_01_80043504(p);
    m = &D_ovl0F_01_800481D4[idx];
    m->unkC = 0;
    m->unk12 = 0;
    m->unk14 = 1;
    m->unk11 = flag;
    if (flag == 0) {
        func_ovl0F_01_80047840(*p->unk0, 0x01000070);
    } else {
        func_ovl0F_01_80047838(*p->unk0, 0x01000070);
    }
    m->unk4 = (f32) (func_ovl0F_01_80047B40() * 3.0) + 1.0f;
    m->unk10 = func_ovl0F_01_80047B48(2);
    m->unk8 = 0.05f;
    (*p->unk0)->unk40->unk14 = 4300.0f;
    (*p->unk0)->unk40->unk1C = 30.0f;
}

static s32 func_ovl0F_01_800452B4(UnkStructA *obj) {
    s32 below;

    below = 0;
    if (obj->unk40->unk14 <= func_ovl0F_01_80046E60()) {
        below = 1;
    }
    return below;
}

/* the movers' step filter: every direction but 0xF */
s32 func_ovl0F_01_8004529C(s32 arg0) {
    if ((arg0 & 0xF) == 0xF) {
        return 0;
    }
    return 1;
}

/* a task: a hit mover's effects */
void func_ovl0F_01_80045158(void) {
    UnkStruct_ovl0F_01_80048264 *p;
    s32 i;

    p = &D_ovl0F_01_80048264[(s32) func_ovl0F_01_800479B0()];
    for (i = 0; i < 3; i++) {
        func_ovl0F_01_80047DD8(7, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14 + 100.0f, (*p->unk0)->unk40->unk18, 0);
        func_ovl0F_01_800479A8(3);
    }
    for (i = 0; i < 5; i++) {
        func_ovl0F_01_80047DD8(0x18, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14 + 100.0f, (*p->unk0)->unk40->unk18, 0);
        func_ovl0F_01_800479A8(3);
    }
    func_ovl0F_01_80047DD8(0x16, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14 + 100.0f, (*p->unk0)->unk40->unk18, 0);
    func_ovl0F_01_80047998();
}

/* the player's callback when a mover throws it */
void func_ovl0F_01_80044E54(UnkStructA *arg0) {
    s32 dir;
    f32 speed;
    f32 dy;
    s32 i;

    dir = 0;
    speed = 0.0f;
    func_ovl0F_01_80047F10(3);
    if (D_ovl0F_01_80048938.unk16 != -1) {
        dir = D_ovl0F_01_800481D4[D_ovl0F_01_80048938.unk16].unk0;
        speed = D_ovl0F_01_800481D4[D_ovl0F_01_80048938.unk16].unk4 * 0.8f;
    }
    func_ovl0F_01_80047560(arg0->unk40, 0x11, 0);
    func_ovl0F_01_80047590(arg0->unk40, 4, 0xC);
    func_ovl0F_01_80047590(arg0->unk40, 5, 0xD);
    func_ovl0F_01_80047DD8(0, arg0->unk40->unk10, arg0->unk40->unk14 + 100.0f, arg0->unk40->unk18, 0);
    arg0->unk68 = 30.0f;
    arg0->unk70 = 1.6333334f;
    for (i = 1; i <= 200 && arg0->unk68 > 0.0f && !func_ovl0F_01_800452B4(arg0); i++) {
        dy = func_ovl0F_01_80047B38(arg0->unk40->unk1C) * 30.0f;
        func_ovl0F_01_80047E80(arg0, dir, speed, func_ovl0F_01_8004529C);
        arg0->unk40->unk1C += 10.0f;
        arg0->unk40->unk10 -= func_ovl0F_01_80047B30(arg0->unk40->unk1C);
        if (dy > 0.0f) {
            dy = 0.0f;
        }
        arg0->unk40->unk14 -= dy;
        func_ovl0F_01_800479D0();
    }
    if (func_ovl0F_01_800452B4(arg0)) {
        func_ovl0F_01_80043348(arg0);
    } else {
        arg0->unk6C = 0.0f;
        arg0->unk70 = 0.0f;
    }
    func_ovl0F_01_800479A8(0x50);
}

/* a task: the movers, until the script ends and all have stopped */
void func_ovl0F_01_8004464C(void) {
    s32 again;
    s16 i;
    UnkStruct_ovl0F_01_800481D4 *m;
    UnkStruct_ovl0F_01_80048264 *p;
    UnkStruct_ovl0F_01_8004815C *st;
    UnkStructA *pl;
    f32 dist;
    f32 angle;
    f32 pos[3];
    s32 hit;

    again = 1;
    do {
        func_ovl0F_01_80044408(0, 0, 0, D_ovl0F_01_80048148);
        if (D_ovl0F_01_80048938.unkC != 0 && *D_ovl0F_01_80048938.unk4 != NULL &&
            (*D_ovl0F_01_80048938.unk4)->unk40->unk48 != NULL) {
            (*D_ovl0F_01_80048938.unk4)->unk40->unk48->unk4->unk4 = D_ovl0F_01_80048938.unk8;
            if (D_ovl0F_01_80048938.unkC == 1) {
                D_ovl0F_01_80048938.unk8 += 1.0f;
                if (func_ovl0F_01_80047578((*D_ovl0F_01_80048938.unk4)->unk40, 0) <= D_ovl0F_01_80048938.unk8) {
                    D_ovl0F_01_80048938.unk8 = 0.0f;
                    D_ovl0F_01_80048938.unkC = 0;
                }
            } else {
                D_ovl0F_01_80048938.unk8 -= 1.0f;
                if (D_ovl0F_01_80048938.unk8 < 0.0f) {
                    D_ovl0F_01_80048938.unk8 = 0.0f;
                    D_ovl0F_01_80048938.unkC = 0;
                }
            }
        }
        for (i = 0; i < 6; i++) {
            m = &D_ovl0F_01_800481D4[i];
            p = &D_ovl0F_01_80048264[i];
            if (m->unk11 == 1) {
                func_ovl0F_01_80047948(*p->unk0);
                pl = D_ovl0F_01_80048938.unk0;
                if (pl->unk40->unk10 <= (*p->unk0)->unk40->unk10 + 300.0f &&
                    (*p->unk0)->unk40->unk10 - 300.0f <= pl->unk40->unk10 &&
                    pl->unk40->unk18 <= (*p->unk0)->unk40->unk18 + 300.0f &&
                    (*p->unk0)->unk40->unk18 - 300.0f <= pl->unk40->unk18) {
                    if (m->unk14 != 0) {
                        func_ovl0F_01_80047F10(0x87);
                        m->unk14 = 0;
                    }
                } else if (m->unk14 == 0) {
                    m->unk14 = 1;
                }
                if ((*p->unk0)->unk6C == 0.0f) {
                    st = &D_ovl0F_01_8004815C[m->unk10][m->unk12];
                    if (m->unkC >= st->unk0) {
                        if (p->unk1C == 90.0f) {
                            m->unkC = 0;
                            m->unk0 = st->unk2;
                            m->unk8 = st->unk4;
                            m->unk12 = st->unk3;
                        } else if (p->unk1C == 270.0f) {
                            m->unk0 = (st->unk2 + 0x80) & 0xFF;
                            m->unkC = 0;
                            m->unk8 = st->unk4;
                            m->unk12 = st->unk3;
                        }
                    }
                }
                m->unkC++;
                func_ovl0F_01_800441CC(i);
                func_ovl0F_01_80047E80(*p->unk0, m->unk0, m->unk4, func_ovl0F_01_8004529C);
                dist = 0.0f;
                angle = 0.0f;
                func_ovl0F_01_80046EC0((*p->unk0)->unk40, &dist, &angle);
                if (func_ovl0F_01_80047B30((*p->unk0)->unk40->unk20) >= 0.707f && angle != 0.0f) {
                    dist *= func_ovl0F_01_80047B30(angle);
                }
                (*p->unk0)->unk40->unk1C = dist * 0.6f;
                if (func_ovl0F_01_800452B4(*p->unk0)) {
                    D_ovl0F_01_80048938.unk20(i, 0);
                } else {
                    hit = func_ovl0F_01_800477E8(*p->unk0, 0x40);
                    if (hit != 0 && ((hit & 0x2000) || (hit & 0x4000))) {
                        pos[0] = (*p->unk0)->unk40->unk10;
                        pos[1] = (*p->unk0)->unk40->unk14;
                        pos[2] = (*p->unk0)->unk40->unk18;
                        func_ovl0F_01_80047F38(0x168, pos);
                        func_ovl0F_01_80047EF0(pos);
                        (*p->unk0)->unk68 = 20.0f;
                        (*p->unk0)->unk70 = 0.8166667f;
                        m->unk11 = 2;
                        func_ovl0F_01_80047988(func_ovl0F_01_80045158, (void *) (s32) i, 0, 0, 0x150);
                    }
                    if (func_ovl0F_01_80047800(D_ovl0F_01_80048938.unk0, *p->unk0) != 0) {
                        D_ovl0F_01_80048938.unk16 = i;
                    }
                    m->unk4 += m->unk8;
                }
            } else if (m->unk11 == 2) {
                if ((*p->unk0)->unk68 == 0.0f && (*p->unk0)->unk6C == 0.0f) {
                    D_ovl0F_01_80048938.unk20(i, 0);
                } else {
                    if ((*p->unk0)->unk40->unk1C < 180.0f) {
                        (*p->unk0)->unk40->unk1C += 5.0f;
                    }
                    func_ovl0F_01_80047E80(*p->unk0, m->unk0, m->unk4, func_ovl0F_01_8004529C);
                    func_ovl0F_01_800478B8(*p->unk0);
                    if (func_ovl0F_01_800452B4(*p->unk0)) {
                        D_ovl0F_01_80048938.unk20(i, 0);
                    }
                }
            }
        }
        if (D_ovl0F_01_80048148 == 0) {
            again = 0;
            for (i = 0; i < 6; i++) {
                if (D_ovl0F_01_800481D4[i].unk11 != 0) {
                    again = 1;
                }
            }
        }
        func_ovl0F_01_800479D0();
    } while (again);
    func_ovl0F_01_80043018(6, D_ovl0F_01_80048264);
    func_ovl0F_01_80047998();
}

/* case 2's: the movers and their script */
void func_ovl0F_01_80045E40(UnkStructA **arg0) {
    s32 i;

    D_ovl0F_01_80048938.unk0 = func_ovl0F_01_80047078(func_ovl0F_01_80047018());
    D_ovl0F_01_80048938.unk4 = arg0;
    D_ovl0F_01_80048938.unkC = 0;
    D_ovl0F_01_80048938.unk10 = 0;
    D_ovl0F_01_80048938.unk14 = 0;
    D_ovl0F_01_80048938.unk16 = -1;
    D_ovl0F_01_80048938.unk8 = 0.0f;
    D_ovl0F_01_80048148 = 1;
    D_ovl0F_01_80048938.unk18 = D_ovl0F_01_8004814C;
    D_ovl0F_01_80048938.unk20 = func_ovl0F_01_800452CC;
    D_ovl0F_01_80048264[0].unkC = 0.0f;
    D_ovl0F_01_80048264[0].unk14 = 6.0f;
    D_ovl0F_01_80048264[0].unk1C = 90.0f;
    D_ovl0F_01_80048264[1].unkC = 0.0f;
    D_ovl0F_01_80048264[1].unk14 = 11.0f;
    D_ovl0F_01_80048264[1].unk1C = 90.0f;
    D_ovl0F_01_80048264[2].unkC = 0.0f;
    D_ovl0F_01_80048264[2].unk14 = 17.0f;
    D_ovl0F_01_80048264[2].unk1C = 90.0f;
    func_ovl0F_01_80043588(D_ovl0F_01_80048264, 6);
    for (i = 0; i < 6; i++) {
        func_ovl0F_01_80047838(func_ovl0F_01_80047870(*D_ovl0F_01_80048264[i].unk0), 0x02100000);
        D_ovl0F_01_800481D4[i].unk11 = 0;
        D_ovl0F_01_80048938.unk20(i, 0);
    }
    func_ovl0F_01_80046F70(func_ovl0F_01_80044E54);
    func_ovl0F_01_80047988(func_ovl0F_01_8004464C, NULL, 0, 0, 0x110);
}

/* one step of the movers' script */
static void func_ovl0F_01_80044408(s32 arg0, s32 arg1, s32 arg2, s32 flag) {
    u16 *e;
    s32 kind;
    s32 arg;

    e = D_ovl0F_01_80048938.unk18[D_ovl0F_01_80048938.unk14];
    if (e[0] == D_ovl0F_01_80048938.unk10++) {
        if (e[1] != 100) {
            if (flag) {
                switch (e[1]) {
                    case 0:
                        kind = 1;
                        arg = 0;
                        break;
                    case 1:
                        kind = 1;
                        arg = 1;
                        break;
                    case 2:
                        kind = 1;
                        arg = 2;
                        break;
                    case 7:
                        kind = 1;
                        arg = 3;
                        break;
                    case 8:
                        kind = 1;
                        arg = 4;
                        break;
                    case 9:
                        kind = 1;
                        arg = 5;
                        break;
                    case 98:
                        kind = 10;
                        arg = 1;
                        break;
                    case 99:
                        kind = 10;
                        arg = 2;
                        break;
                }
                switch (kind) {
                    case 1:
                        if (D_ovl0F_01_800481D4[arg].unk11 == 0) {
                            D_ovl0F_01_80048938.unk20(arg, 1);
                        }
                        break;
                    case 10:
                        switch (arg) {
                            case 1:
                                if (D_ovl0F_01_80048938.unkC == 0) {
                                    D_ovl0F_01_80048938.unkC = 1;
                                    D_ovl0F_01_80048938.unk8 = 0.0f;
                                }
                                break;
                            case 2:
                                if (D_ovl0F_01_80048938.unkC == 0) {
                                    D_ovl0F_01_80048938.unkC = 2;
                                    if (*D_ovl0F_01_80048938.unk4 != NULL) {
                                        D_ovl0F_01_80048938.unk8 = func_ovl0F_01_80047578((*D_ovl0F_01_80048938.unk4)->unk40, 0) - 0.001f;
                                    }
                                }
                                break;
                        }
                        break;
                }
            }
            D_ovl0F_01_80048938.unk14++;
        } else {
            D_ovl0F_01_80048938.unk10 = 0;
            D_ovl0F_01_80048938.unk14 = 0;
        }
    }
}

/* a mover turns towards its direction, a tenth of the way (at least 1) a frame */
static void func_ovl0F_01_800441CC(s16 i) {
    f32 target;
    f32 d;

    target = 0.0f;
    switch (D_ovl0F_01_800481D4[i].unk0) {
        case 0x00:
            target = 180.0f;
            break;
        case 0x20:
            target = 135.0f;
            break;
        case 0x40:
            target = 90.0f;
            break;
        case 0x60:
            target = 45.0f;
            break;
        case 0xA0:
            target = 315.0f;
            break;
        case 0xC0:
            target = 270.0f;
            break;
        case 0xE0:
            target = 225.0f;
            break;
    }
    if (target < (*D_ovl0F_01_80048264[i].unk0)->unk40->unk20) {
        d = ((*D_ovl0F_01_80048264[i].unk0)->unk40->unk20 - target) * 0.1f;
        if (d > 1.0f) {
            (*D_ovl0F_01_80048264[i].unk0)->unk40->unk20 -= d;
        } else {
            (*D_ovl0F_01_80048264[i].unk0)->unk40->unk20 -= 1.0f;
        }
        if ((*D_ovl0F_01_80048264[i].unk0)->unk40->unk20 < target) {
            (*D_ovl0F_01_80048264[i].unk0)->unk40->unk20 = target;
        }
    } else if ((*D_ovl0F_01_80048264[i].unk0)->unk40->unk20 < target) {
        d = (target - (*D_ovl0F_01_80048264[i].unk0)->unk40->unk20) * 0.1f;
        if (d > 1.0f) {
            (*D_ovl0F_01_80048264[i].unk0)->unk40->unk20 += d;
        } else {
            (*D_ovl0F_01_80048264[i].unk0)->unk40->unk20 += 1.0f;
        }
        if (target < (*D_ovl0F_01_80048264[i].unk0)->unk40->unk20) {
            (*D_ovl0F_01_80048264[i].unk0)->unk40->unk20 = target;
        }
    }
}

/* the platforms' callback: what stands on them is held at their edge */
void func_ovl0F_01_8004413C(UnkStructA *obj) {
    if ((obj->unk8 & 1) || ((obj->unk8 & 2) && obj->unk40->unk10 < 300.0f) || (obj->unk8 & 4)) {
        if (obj->unk40->unk10 < obj->unk58) {
            obj->unk40->unk10 = obj->unk58;
            obj->unk40->unk14 = obj->unk5C;
        }
    }
}

/* a task: the platforms, once the player reaches them */
void func_ovl0F_01_80043B0C(void) {
    Vec3f a;
    Vec3f b;
    f32 x;
    UnkStructA *pl;
    s32 state;
    s32 i;
    f32 sx;
    f32 sy;
    f32 sz;

    D_ovl0F_01_80048420 = 0;
    func_ovl0F_01_80043588(D_ovl0F_01_8004836C, 3);
    func_ovl0F_01_80043588(&D_ovl0F_01_800483F0, 1);
    func_ovl0F_01_80047840(D_ovl0F_01_80048744, 0x01000000);
    for (i = 0; i < 3; i++) {
        D_ovl0F_01_80048738[i]->unk40->unk28 = 3.0f;
        D_ovl0F_01_80048738[i]->unk40->unk2C = 3.0f;
        D_ovl0F_01_80048738[i]->unk40->unk30 = 1.0f;
        D_ovl0F_01_80048738[i]->unk40->unk14 += 110.0f;
    }
    a.x = 300.0f;
    a.y = 1700.0f;
    a.z = 1100.0f;
    b.x = 150.0f;
    b.y = 300.0f;
    b.z = 750.0f;
    while (func_ovl0F_01_80047940(0x40, &a, &b) == 0) {
        func_ovl0F_01_800479D0();
    }
    D_ovl0F_01_80048420 = 1;
    func_ovl0F_01_80047760(20.0f, 20.0f, 20.0f);
    func_ovl0F_01_80047750(60);
    func_ovl0F_01_80047DD8(0x10, 400.0f, 2000.0f, 700.0f, 0);
    func_ovl0F_01_80047DD8(0x10, 450.0f, 2000.0f, 1000.0f, 0);
    func_ovl0F_01_80047DD8(0x10, 320.0f, 2000.0f, 1300.0f, 0);
    func_ovl0F_01_80047DD8(0x10, 400.0f, 2000.0f, 1600.0f, 0);
    func_ovl0F_01_80047760(10.0f, 10.0f, 10.0f);
    func_ovl0F_01_80047750(300);
    func_ovl0F_01_80047F30(0x88, 626.0f, 1066.0f, 1071.7f);
    D_ovl0F_01_80048424 = 0.01f;
    pl = func_ovl0F_01_80047078(func_ovl0F_01_80047018());
    x = 430.0f;
    func_ovl0F_01_80047580(D_ovl0F_01_80048738[0]->unk40, 0, 0, 0x400, 0x20, 0x400);
    func_ovl0F_01_80047760(10.0f, 10.0f, 10.0f);
    while ((state = func_ovl0F_01_800438C0(&x)) != 2) {
        D_ovl0F_01_80048744->unk40->unk10 = x;
        if (!func_ovl0F_01_800452B4(D_ovl0F_01_80048744)) {
            func_ovl0F_01_800478B8(D_ovl0F_01_80048744);
        }
        if ((f32) func_ovl0F_01_80047B40() > 0.8f) {
            func_ovl0F_01_80047DD8(0x10, x + 50.0f, D_ovl0F_01_80048744->unk40->unk14 + 1000.0f,
                                   func_ovl0F_01_80047B40() * 1100.0 + 500.0, 0);
            func_ovl0F_01_80047750(10);
        }
        if (state == 0 && pl->unk40->unk18 >= 360.0f && pl->unk40->unk18 <= 1850.0f && pl->unk40->unk10 <= x) {
            sx = D_ovl0F_01_80048738[0]->unk40->unk10;
            sy = D_ovl0F_01_80048738[0]->unk40->unk14;
            sz = D_ovl0F_01_80048738[0]->unk40->unk18;
            D_ovl0F_01_80048738[0]->unk40->unk10 = pl->unk40->unk10;
            D_ovl0F_01_80048738[0]->unk40->unk14 = pl->unk40->unk14;
            D_ovl0F_01_80048738[0]->unk40->unk18 = pl->unk40->unk18;
            func_ovl0F_01_80047838(D_ovl0F_01_80048738[0], 0x20);
            func_ovl0F_01_80047948(D_ovl0F_01_80048738[0]);
            func_ovl0F_01_80047840(D_ovl0F_01_80048738[0], 0x20);
            D_ovl0F_01_80048738[0]->unk40->unk10 = sx;
            D_ovl0F_01_80048738[0]->unk40->unk14 = sy;
            D_ovl0F_01_80048738[0]->unk40->unk18 = sz;
        }
        func_ovl0F_01_800479D0();
    }
    func_ovl0F_01_80047760(50.0f, 50.0f, 50.0f);
    func_ovl0F_01_80047750(20);
    D_ovl0F_01_80048420 = 2;
    for (i = 0; i < 3; i++) {
        D_ovl0F_01_80048738[i]->unkC = 0;
        func_ovl0F_01_80047840(D_ovl0F_01_80048738[i], 0x01000030);
    }
    func_ovl0F_01_80046E78(2, 3, 4, 4, 0x12, 0x16);
    D_ovl0F_01_8004841C = -1;
    func_ovl0F_01_80047998();
}

static void func_ovl0F_01_80043018(s32 count, UnkStruct_ovl0F_01_80048264 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_01_80047850(*p->unk0);
        p++;
    }
}

/* the platforms rise, wobble and settle; 1 while one still sinks, 2 once all
 * are down */
s32 func_ovl0F_01_800438C0(f32 *x) {
    s32 state;
    f32 d;
    s32 i;
    UnkStructA *obj;

    state = 0;
    d = 0.0f;
    for (i = 0; i < 3; i++) {
        obj = D_ovl0F_01_80048738[i];
        if (obj->unk40->unk28 < 16.0f) {
            D_ovl0F_01_80048424 += 0.0001f;
            d = ((f32) func_ovl0F_01_80047B40() - 0.5f) * 0.065f + D_ovl0F_01_80048424;
            *x += d * 31.0f;
        } else if (obj->unk40->unk28 == 19.0f) {
            func_ovl0F_01_80047838(obj, 0x80000);
        } else if (obj->unk40->unk28 < 19.0f) {
            obj->unk40->unk2C -= 0.01f;
            d = 0.01f;
            obj->unk40->unk36 = (19.0f - obj->unk40->unk28) * 16.666666f + 200.0f;
        } else {
            state = 2;
            if (obj->unk40->unk14 > 0.0f) {
                state = 1;
                obj->unk40->unk14 -= 10.0f;
            }
        }
        obj->unk40->unk28 += d;
        obj->unk40->unk2C += d;
        obj->unk40->unk30 = obj->unk40->unk30;
    }
    return state;
}

/* a task: the switch; the first hit turns it, the second only sparks */
void func_ovl0F_01_80043628(void) {
    UnkStructA *obj;

    func_ovl0F_01_80043588(&D_ovl0F_01_8004845C, 1);
    D_ovl0F_01_80048748->unkC = 0x40;
    func_ovl0F_01_80047540(D_ovl0F_01_80048748->unk40, 2);
    func_ovl0F_01_80043468(D_ovl0F_01_80048748);
    while (1) {
        func_ovl0F_01_80047948(D_ovl0F_01_80048748);
        obj = D_ovl0F_01_80048748;
        if (func_ovl0F_01_800477E8(obj, 0x40) != 0) {
            switch (D_ovl0F_01_8004842C) {
                case 0:
                    D_ovl0F_01_8004842C = 1;
                    func_ovl0F_01_80043468(obj);
                    func_ovl0F_01_80047F30(0x91, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
                    func_ovl0F_01_80047DD8(0x10, obj->unk40->unk10, obj->unk40->unk14 + 200.0f, obj->unk40->unk18, 0);
                    func_ovl0F_01_80047DD8(0x11, obj->unk40->unk10, obj->unk40->unk14 + 50.0f, obj->unk40->unk18, 0);
                    func_ovl0F_01_800479A8(60);
                    break;
                case 1:
                    func_ovl0F_01_80047F30(0x7B, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
                    func_ovl0F_01_80047DD8(8, obj->unk40->unk10, obj->unk40->unk14 + 400.0f, obj->unk40->unk18 + 100.0f, 0);
                    func_ovl0F_01_800479A8(10);
                    func_ovl0F_01_80047DD8(8, obj->unk40->unk10 + 50.0f, obj->unk40->unk14 + 400.0f,
                                           obj->unk40->unk18 + 100.0f, 0);
                    func_ovl0F_01_800479A8(10);
                    func_ovl0F_01_80047DD8(8, obj->unk40->unk10 - 50.0f, obj->unk40->unk14 + 400.0f,
                                           obj->unk40->unk18 + 120.0f, 0);
                    break;
            }
        }
        func_ovl0F_01_800479D0();
    }
}

/* places count models, each made with its flags */
void func_ovl0F_01_80043588(UnkStruct_ovl0F_01_80048264 *p, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        *p->unk0 = func_ovl0F_01_80047860(p->unk4, p->unk24 | 0x01000000, 0x30, p->unk8);
        func_ovl0F_01_80043504(p);
        (*p->unk0)->unk40->unk1C = p->unk18;
        (*p->unk0)->unk40->unk20 = p->unk1C;
        (*p->unk0)->unk40->unk24 = p->unk20;
        p++;
    }
}

/* the switch's two looks, by its state */
void func_ovl0F_01_80043468(UnkStructA *obj) {
    switch (D_ovl0F_01_8004842C) {
        case 0:
            func_ovl0F_01_80047548(obj->unk40, 0x26B, 0, 0);
            func_ovl0F_01_80047548(obj->unk40, 0x26B, 1, 1);
            break;
        case 1:
            func_ovl0F_01_80047548(obj->unk40, 0x26B, 0, 2);
            func_ovl0F_01_80047548(obj->unk40, 0x26B, 1, 3);
            break;
    }
}

/* a block that fell: it sinks into the floor */
void func_ovl0F_01_80043348(UnkStructA *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl0F_01_800476E0(0x10);
    }
    dx = arg0->unk40->unk28 / 30.0f;
    dy = arg0->unk40->unk2C / 30.0f;
    dz = arg0->unk40->unk30 / 30.0f;
    func_ovl0F_01_80047840(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        arg0->unk40->unk28 -= dx;
        arg0->unk40->unk2C -= dy;
        arg0->unk40->unk30 -= dz;
        func_ovl0F_01_800478B8(arg0);
        func_ovl0F_01_800479D0();
    }
    func_ovl0F_01_80047840(arg0, 0x01000000);
}

/* a task: the stage's opening message, once the stage has started */
void func_ovl0F_01_80043298(void) {
    func_ovl0F_01_80047028(1);
    func_ovl0F_01_80046FA0(0);
    while (D_ovl0F_01_80048434 == 0) {
        func_ovl0F_01_800479D0();
    }
    func_ovl0F_01_80047040(D_ovl0F_01_80048584);
    func_ovl0F_01_800480E8(60);
    func_ovl0F_01_800480C0(1);
    while (func_ovl0F_01_800480D0() != 0) {
        func_ovl0F_01_800479D0();
    }
    func_ovl0F_01_800480F0();
    func_ovl0F_01_80047998();
}

/* cases 0x15 and 0x16's: the player starts high above the floor */
void func_ovl0F_01_8004324C(void) {
    func_ovl0F_01_80047078(func_ovl0F_01_80047018())->unk40->unk14 += 2000.0f;
}

static void func_ovl0F_01_80043100(UnkStruct_ovl0F_01_80048798 *p) {
    f32 r;
    f64 t;

    r = func_ovl0F_01_80047B40();
    p->unk0 = func_ovl0F_01_80047B40() * 370.0 - 50.0;
    t = func_ovl0F_01_80047B40();
    p->unk4 = (D_ovl0F_01_8004813C < 0.0f ? -D_ovl0F_01_8004813C : D_ovl0F_01_8004813C) * 30.0f * t;
    if (D_ovl0F_01_80048138 <= 0.0f) {
        p->unk4 += (1.0f - r) * 40.0f;
    } else {
        p->unk4 += func_ovl0F_01_80047B48(90);
    }
    p->unk10 = 0;
    p->unk8 = r * 12.0f + 4.0f;
    p->unkC = r * r * 5.0f + 0.5f;
}

static void func_ovl0F_01_80043504(UnkStruct_ovl0F_01_80048264 *arg0) {
    f32 pos[3];

    func_ovl0F_01_80046E98(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

void func_ovl0F_01_80043094(s32 *arg0) {
    if (func_ovl0F_01_80047000(arg0[0], arg0[1], arg0[2], arg0[3]) != 0) {
        func_ovl0F_01_80046F30(arg0[4], arg0[5], arg0[6]);
    }
}

void func_ovl0F_01_80043010(void) {
}
