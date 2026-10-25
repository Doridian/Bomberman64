/*
 * NON_MATCHING: ovl_0F_02's game object, complete: every function and its
 * data (.data as the original). A first draft: the layout is only partly
 * IDO's, and most of the count is functions compared against the wrong
 * code. Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 3348, jp 5736
 *
 * Every function and static comes out in the original's order. The order
 * is ovl_0F_03's: the handler, defined last but for func_ovl0F_02_80043010,
 * is compiled first, its direct callees (3028 3324 33A0) out before
 * everything it only takes the address of; those come out in the reverse
 * of the order of their first references, the statics' (in definition
 * order) before the handler's own. Hudson's natural order of references
 * would give 3944 3618 3404 34F8 38B4 5024 5EB0 3FEC 4824 4D20 54E8 533C
 * 3858; the `if (0)` at the top of func_ovl0F_02_80046178 is a fake that
 * makes every first reference in descending address order, so they come
 * out ascending as in the original (5736 words to 3348;
 * scratch/0F_02/p3/ord.py and hf.sh in the main checkout). What the
 * original's source had instead is open.
 *
 * What still differs in us (words):
 * - func_ovl0F_02_800454E8 (620): ovl_0F_03's 80044258, the same register
 *   and frame misses as there.
 * - func_ovl0F_02_800462F8 (606), func_ovl0F_02_80044824 (184): frames
 *   and registers.
 * - func_ovl0F_02_80043028 (186): global here; the original is a static
 *   using s0 and fs0-fs2 unsaved (the handler saves them). 80043324 (26)
 *   and 800433A0 (21) likewise: statics taking their arguments in s0/s1.
 *   They are global only to come out first, as the original has them.
 * - the rest (under 110 each): the stubs and statics after them.
 */
#include "common.h"

/*
 * ovl_0F_02's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). ovl_0F_03 (1EE1A0) shares
 * the door, the particles and the handler's shape, ovl_0F_10 and ovl_17_09
 * the wind's helpers, and ovl_0F_04 (and ovl_0F_01) the movers. The statics
 * IDO inlines everywhere are named for the empty stubs they leave.
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
} UnkStruct_ovl0F_02_80048734; /* size 0x2C */

/* the door func_ovl0F_02_80045024 runs as a task: two models and what to
 * call once it is open */
typedef struct {
    /* 0x00 */ UnkStruct_ovl0F_02_80048734 unk0[2];
    /* 0x58 */ void (*unk58)(void);
    /* 0x5C */ void (*unk5C)(void);
} UnkStruct_ovl0F_02_800489F4; /* size 0x60 */

/* a mover's state */
typedef struct {
    /* 0x00 */ s32 unk0; /* heading, 0x00-0xE0 */
    /* 0x04 */ f32 unk4; /* speed */
    /* 0x08 */ f32 unk8; /* acceleration */
    /* 0x0C */ s32 unkC; /* frames on this step */
    /* 0x10 */ u8 unk10; /* path */
    /* 0x11 */ u8 unk11; /* 0 gone, 1 moving, 2 hit */
    /* 0x12 */ u8 unk12; /* step */
    /* 0x13 */ u8 unk13;
    /* 0x14 */ s32 unk14;
} UnkStruct_ovl0F_02_800486A4; /* size 0x18 */

/* a step of a mover's path */
typedef struct {
    /* 0x00 */ u16 unk0; /* frames */
    /* 0x02 */ u8 unk2;  /* heading */
    /* 0x03 */ u8 unk3;  /* next step */
    /* 0x04 */ f32 unk4; /* acceleration */
} UnkStruct_ovl0F_02_8004862C; /* size 0x8 */

/* a command of the movers' script */
typedef struct {
    /* 0x00 */ u16 unk0; /* frame */
    /* 0x02 */ u16 unk2; /* command */
} UnkStruct_ovl0F_02_80048614; /* size 0x4 */

/* the movers' controller */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ UnkStructA **unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ UnkStruct_ovl0F_02_80048614 *unk18;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ void (*unk20)(s32, s32);
} UnkStruct_ovl0F_02_80048F20;

/* a switch's state */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_ovl0F_02_80048918; /* size 0xC */

/* seven arguments of func_ovl0F_02_800474E8 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0F_02_80048A8C; /* size 0x1C */

/* one of the particles func_ovl0F_02_800454E8 draws (D_ovl0F_02_80048D80) */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0F_02_80048D80; /* size 0x14 */

/* what func_ovl0F_02_800479B8 returns: offsets into itself */
typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18[8];
    /* 0x20 */ s32 unk20;
} UnkStruct_ovl0F_02_800485E0;

/* what func_ovl0F_02_80047438 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0F_02_80047438;

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_ovl0F_02_Gfx; /* size 0x8 */

/* gbi.h's _SHIFTL */
#define _SHIFTL(v, s, w) ((u32) (((u32) (v) & ((0x01 << (w)) - 1)) << (s)))

void func_ovl0F_02_800472E8(s32);
void func_ovl0F_02_80047300(s32);
f32 func_ovl0F_02_80047310(void);
void func_ovl0F_02_80047328(s32, s32, s32, s32, s32, s32);
void func_ovl0F_02_80047348(f32, f32, f32, f32 *, s32);
void func_ovl0F_02_80047370(UnkStructA_40 *, f32 *, f32 *);
f32 func_ovl0F_02_800473A8(UnkStructA_40 *);
void func_ovl0F_02_800473C8(void (*)(UnkStructA *), s32);
void func_ovl0F_02_800473D0(void (*)(UnkStructA *));
void func_ovl0F_02_800473E0(s32, s32, s32);
s32 func_ovl0F_02_800473E8(void);
void func_ovl0F_02_80047420(void (*)(UnkStructA *));
UnkStruct_ovl0F_02_80047438 *func_ovl0F_02_80047438(void);
void func_ovl0F_02_80047450(s32);
void func_ovl0F_02_80047498(void);
void func_ovl0F_02_800474A0(s32, s32, s32);
void func_ovl0F_02_800474A8(Vec3f *);
s32 func_ovl0F_02_800474B0(s32, s32, s32, s32);
s32 func_ovl0F_02_800474C8(void);
void func_ovl0F_02_800474D0(s32, f32 *);
void func_ovl0F_02_800474D8(s32);
void func_ovl0F_02_800474E0(s32);
void func_ovl0F_02_800474E8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0F_02_800474F0(char *);
void func_ovl0F_02_800474F8(void);
UnkStructA *func_ovl0F_02_80047528(s32);
void func_ovl0F_02_80047530(s32);
UnkStructA *func_ovl0F_02_80047568(s32);
void func_ovl0F_02_80047588(s32);
UnkStruct_ovl0F_02_800485E0 *func_ovl0F_02_800479B8(s32);
void func_ovl0F_02_800479C0(s32);
void func_ovl0F_02_800479D8(UnkStructA *);
void func_ovl0F_02_80047A10(UnkStructA_40 *, s32, s32);
f32 func_ovl0F_02_80047A28(UnkStructA_40 *, s32);
void func_ovl0F_02_80047A40(UnkStructA_40 *, s32, s32);
UnkStructA *func_ovl0F_02_80047A48(void (*)(s32, UnkStruct_ovl0F_02_Gfx **), s32);
void func_ovl0F_02_80047B18(s32);
void func_ovl0F_02_80047B28(f32, f32, f32);
void func_ovl0F_02_80047B38(f32, f32, f32);
void func_ovl0F_02_80047B48(f32, f32, f32);
void func_ovl0F_02_80047B50(f32 *, f32 *, f32 *);
void func_ovl0F_02_80047B60(u32 *, s32, s32);
void func_ovl0F_02_80047B88(s32);
void func_ovl0F_02_80047B90(s32);
void func_ovl0F_02_80047BA0(s32);
void func_ovl0F_02_80047C18(f32 *);
void func_ovl0F_02_80047C30(Vec3f *);
void func_ovl0F_02_80047C40(f32 *);
void func_ovl0F_02_80047C48(void);
void func_ovl0F_02_80047C50(void);
s32 func_ovl0F_02_80047C98(UnkStructA *, s32);
s32 func_ovl0F_02_80047CB0(UnkStructA *, UnkStructA *);
void func_ovl0F_02_80047CE8(UnkStructA *, s32);
void func_ovl0F_02_80047CF0(UnkStructA *, s32);
s32 func_ovl0F_02_80047D00(UnkStructA *);
UnkStructA *func_ovl0F_02_80047D10(s32, s32, s32, s32);
UnkStructA *func_ovl0F_02_80047D20(UnkStructA *);
UnkStructA *func_ovl0F_02_80047D58(s32, s32);
void func_ovl0F_02_80047D68(UnkStructA *);
void func_ovl0F_02_80047DC8(f32);
void func_ovl0F_02_80047DD0(s32);
void func_ovl0F_02_80047DF8(UnkStructA *);
s32 func_ovl0F_02_80047E08(UnkStructA *, s32, UnkStructA *);
s32 func_ovl0F_02_80047E38(void (*)(void), void *, s32, s32, s32);
void func_ovl0F_02_80047E48(void);
void func_ovl0F_02_80047E58(s32);
void *func_ovl0F_02_80047E60(void);
void func_ovl0F_02_80047E80(void);
f32 func_ovl0F_02_80047FE0(f32);
f32 func_ovl0F_02_80047FE8(f32);
f64 func_ovl0F_02_80047FF0(void);
s32 func_ovl0F_02_80047FF8(s32);
void func_ovl0F_02_800480B0(s32);
void func_ovl0F_02_800480B8(s32);
s32 func_ovl0F_02_800480C0(s32);
void func_ovl0F_02_80048178(s32, s32, s32, s32, s32);
void func_ovl0F_02_80048188(s32, s32, s32);
void func_ovl0F_02_800481A0(u32 (*)[3]);
void func_ovl0F_02_80048288(s32, f32, f32, f32, s32);
void func_ovl0F_02_800482C8(void);
void func_ovl0F_02_80048308(s16, f32, f32, f32);
void func_ovl0F_02_80048330(UnkStructA *, s32, f32, s32 (*)(s32));
void func_ovl0F_02_80048338(UnkStructA *, s32, f32);
void func_ovl0F_02_80048348(s32, s32, s32);
void func_ovl0F_02_80048368(s32);
void func_ovl0F_02_800483A0(f32 *);
void func_ovl0F_02_800483A8(void);
void func_ovl0F_02_800483C0(s32);
void func_ovl0F_02_800483E0(s32, f32, f32, f32);
void func_ovl0F_02_800483E8(s32, f32 *);
void func_ovl0F_02_80048538(void);
void func_ovl0F_02_80048540(void);

static void func_ovl0F_02_80046E70(void);
static void func_ovl0F_02_80046E68(void);
static void func_ovl0F_02_80046E60(void);
static void func_ovl0F_02_80046E58(void);
static void func_ovl0F_02_80046E50(void);
static void func_ovl0F_02_80046E48(void);
static void func_ovl0F_02_80046E40(void);
static void func_ovl0F_02_80046E38(void);
static void func_ovl0F_02_80046E30(void);
static void func_ovl0F_02_80046E28(void);
static void func_ovl0F_02_80046E20(void);
static void func_ovl0F_02_80046E18(void);
static void func_ovl0F_02_80046E10(void);
static void func_ovl0F_02_80046E78(void);
static void func_ovl0F_02_80046E80(void);
void func_ovl0F_02_80046DF8(void);
void func_ovl0F_02_80046D9C(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0F_02_80046D54(f32 arg0);
void func_ovl0F_02_80046D20(s32 arg0, UnkStructA *arg1);
void func_ovl0F_02_800462F8(s32 arg0);
static void func_ovl0F_02_80046178(s32 n1, s32 n2);
static void func_ovl0F_02_80045F24(UnkStructA **door);
void func_ovl0F_02_80045EB0(void);
static f32 func_ovl0F_02_800454E0(f32 v);
static void func_ovl0F_02_800453A4(UnkStruct_ovl0F_02_80048D80 *p);
void func_ovl0F_02_80043FEC(void);
void func_ovl0F_02_80045024(void);
void func_ovl0F_02_800454E8(s32 arg0, UnkStruct_ovl0F_02_Gfx **arg1);
void func_ovl0F_02_8004533C(UnkStructA *obj);
static void func_ovl0F_02_80044F74(UnkStruct_ovl0F_02_80048734 *arg0, s32 arg1);
static void func_ovl0F_02_80044E9C(f32 *pos, s32 id, f32 d, f32 h);
void func_ovl0F_02_80044D20(s32 i, s32 flag);
static void func_ovl0F_02_80044C94(UnkStruct_ovl0F_02_80048734 *arg0);
s32 func_ovl0F_02_80044C6C(s32 arg0);
void func_ovl0F_02_80044B28(void);
void func_ovl0F_02_80044824(UnkStructA *obj);
static void func_ovl0F_02_80043D6C(s32 active);
static void func_ovl0F_02_80043B30(s32 i);
static s32 func_ovl0F_02_80043B28(UnkStructA *obj);
void func_ovl0F_02_80043944(void);
void func_ovl0F_02_800438B4(UnkStructA *obj);
void func_ovl0F_02_80043858(UnkStructA *obj);
static void func_ovl0F_02_800436D8(UnkStructA *obj, f32 speed);
static void func_ovl0F_02_800436B8(UnkStructA *obj, f32 speed);
void func_ovl0F_02_80043618(void);
void func_ovl0F_02_800434F8(UnkStructA *arg0);
void func_ovl0F_02_80043404(void);
void func_ovl0F_02_800433A0(s32 *arg0);
void func_ovl0F_02_80043324(s32 n, char *script);
void func_ovl0F_02_80043028(void);
static void func_ovl0F_02_80043020(s32 count, UnkStruct_ovl0F_02_80048734 *p);
static s32 func_ovl0F_02_80043018(void);
void func_ovl0F_02_80043010(void);


/* .bss */
UnkStructA *D_ovl0F_02_80048D00[6];
UnkStructA *D_ovl0F_02_80048D18[8];
f32 D_ovl0F_02_80048D38[3];
u8 D_ovl0F_02_80048D44[0x4];
Vec3f D_ovl0F_02_80048D48;
s32 D_ovl0F_02_80048D54;
u8 D_ovl0F_02_80048D58[0x4];
s32 D_ovl0F_02_80048D5C;
s32 D_ovl0F_02_80048D60;
u8 D_ovl0F_02_80048D64[0x4];
Vec3f D_ovl0F_02_80048D68;
s32 D_ovl0F_02_80048D74;
u8 D_ovl0F_02_80048D78[0x4];
s32 D_ovl0F_02_80048D7C;
UnkStruct_ovl0F_02_80048D80 D_ovl0F_02_80048D80[20];
Vec3f D_ovl0F_02_80048F10;
UnkStructA *D_ovl0F_02_80048F1C;
UnkStruct_ovl0F_02_80048F20 D_ovl0F_02_80048F20;

/* .data */
UnkStruct_ovl0F_02_800485E0 *D_ovl0F_02_800485E0 = NULL;
f32 D_ovl0F_02_800485E4 = 0.0f;
f32 D_ovl0F_02_800485E8 = 0.0f;
f32 D_ovl0F_02_800485EC = 0.0f;
f32 D_ovl0F_02_800485F0 = 0.0f;
f32 D_ovl0F_02_800485F4 = 0.0f;
s32 D_ovl0F_02_800485F8 = 0;
f32 D_ovl0F_02_800485FC = 0.0f;
f32 D_ovl0F_02_80048600 = 0.0f;
f32 D_ovl0F_02_80048604 = 0.0f;
f32 D_ovl0F_02_80048608 = 0.0f;
s32 D_ovl0F_02_8004860C = 1;
s32 D_ovl0F_02_80048610 = 0;
/* the movers' script: on frame unk0, command unk2 */
UnkStruct_ovl0F_02_80048614 D_ovl0F_02_80048614[6] = {
    { 0, 0x62 }, { 0x1E, 0 }, { 0x78, 1 }, { 0xD2, 2 }, { 0xD3, 0x63 }, { 0x1FF, 0x64 },
};
/* the movers' paths: three of five steps */
UnkStruct_ovl0F_02_8004862C D_ovl0F_02_8004862C[3][5] = {
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
/* the movers' state */
UnkStruct_ovl0F_02_800486A4 D_ovl0F_02_800486A4[6] = {
    { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 0, 1 },
    { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 0, 1 },
    { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 0, 1 },
    { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 0, 1 },
    { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 0, 1 },
    { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 0, 1 },
};
/* the movers' models */
UnkStruct_ovl0F_02_80048734 D_ovl0F_02_80048734[6] = {
    { &D_ovl0F_02_80048D00[0], 0x259, 0, 0.0f, 4.0f, 6.0f, 0.0f, 90.0f, 0.0f, 0xC000070, 0 },
    { &D_ovl0F_02_80048D00[1], 0x259, 0, 0.0f, 4.0f, 11.0f, 0.0f, 90.0f, 0.0f, 0xC000070, 0 },
    { &D_ovl0F_02_80048D00[2], 0x259, 0, 0.0f, 4.0f, 17.0f, 0.0f, 90.0f, 0.0f, 0xC000070, 0 },
    { &D_ovl0F_02_80048D00[3], 0x259, 0, 45.0f, 4.0f, 8.0f, 0.0f, 270.0f, 0.0f, 0xC000070, 0 },
    { &D_ovl0F_02_80048D00[4], 0x259, 0, 45.0f, 4.0f, 12.0f, 0.0f, 270.0f, 0.0f, 0xC000070, 0 },
    { &D_ovl0F_02_80048D00[5], 0x259, 0, 45.0f, 4.0f, 17.0f, 0.0f, 270.0f, 0.0f, 0xC000070, 0 },
};
/* the switches' models */
UnkStruct_ovl0F_02_80048734 D_ovl0F_02_8004883C[5] = {
    { &D_ovl0F_02_80048D18[0], 0x25B, 0, 23.0f, 4.0f, 14.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_02_80048D18[1], 0x25B, 0, 24.0f, 4.0f, 16.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_02_80048D18[2], 0x25B, 0, 24.0f, 4.0f, 18.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_02_80048D18[3], 0x25B, 0, 24.0f, 4.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_02_80048D18[4], 0x25B, 0, 23.0f, 4.0f, 22.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};
/* the switches' state: armed, the flag they set, what they give */
UnkStruct_ovl0F_02_80048918 D_ovl0F_02_80048918[5] = {
    { 1, 0x1410, -1 }, { 1, 0x1410, -1 }, { 1, 0x1410, -1 }, { 1, 0x1410, -1 }, { 1, 0x1410, -1 },
};
s32 D_ovl0F_02_80048954 = 0;
/* passed to func_ovl0F_02_800481A0: three 12-byte records */
u32 D_ovl0F_02_80048958[][3] = {
    { 0x2640002, 0xF, 4 },
    { 0x25C0002, 0xF, 4 },
    { 0x26D0000, 0xF, 0x2004 },
};
/* six 12-byte records, each passed to func_ovl0F_02_80048348 */
u32 D_ovl0F_02_8004897C[][3] = {
    { 0, 0x12, 0xF0 },
    { 1, 0x13, 0xF1 },
    { 2, 0x16, 0xF4 },
    { 3, 0, 0xDE },
    { 4, 2, 0xE0 },
    { 5, 0x15, 0xF3 },
};
UnkStruct_ovl0F_02_80048734 D_ovl0F_02_800489C4 = {
    &D_ovl0F_02_80048D18[5], 0x225, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0,
};
UnkStructA *D_ovl0F_02_800489F0 = NULL;
UnkStruct_ovl0F_02_800489F4 D_ovl0F_02_800489F4 = {
    {
        { &D_ovl0F_02_800489F0, 0x25F, 0, 7.0f, 4.0f, 19.0f, 0.0f, 270.0f, 0.0f, 0, 0x400 },
        { &D_ovl0F_02_80048D18[6], 0x260, 0, 7.0f, 5.0f, 19.0f, 0.0f, 270.0f, 0.0f, 0, 0 },
    },
    func_ovl0F_02_80046E78,
    func_ovl0F_02_80046E80,
};
/* func_ovl0F_02_800433A0's: four arguments to test, three to pass on */
s32 D_ovl0F_02_80048A54[7] = { 0x1C, 0x10, 0x1C, 0x10, 0x58, 0x12, 0 };
s32 D_ovl0F_02_80048A70[7] = { 0xD, 1, 0xE, 2, 0x5A, 0x12, 0 };
UnkStruct_ovl0F_02_80048A8C D_ovl0F_02_80048A8C[2] = {
    { 0x40, 3, 8.5f, 3, 0, 1, 0 },
    { 0xA0, 3, 8.5f, 3, 0, 1, 1 },
};
/* passed to func_ovl0F_02_80047B60 */
u32 D_ovl0F_02_80048AC4[17] = {
    0x14, 1, 1, 0, 0, 0, 0, 0, 0, 0x40900000, 0, 0, 0xBE75C28F, 0, 0, 0, 0,
};
s32 D_ovl0F_02_80048B08[2] = { 0, 0 };

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0F_02_80046E70(void) {
}

static void func_ovl0F_02_80046E68(void) {
}

static void func_ovl0F_02_80046E60(void) {
}

static void func_ovl0F_02_80046E58(void) {
}

static void func_ovl0F_02_80046E50(void) {
}

static void func_ovl0F_02_80046E48(void) {
}

static void func_ovl0F_02_80046E40(void) {
}

static void func_ovl0F_02_80046E38(void) {
}

static void func_ovl0F_02_80046E30(void) {
}

static void func_ovl0F_02_80046E28(void) {
}

static void func_ovl0F_02_80046E20(void) {
}

static void func_ovl0F_02_80046E18(void) {
}

static void func_ovl0F_02_80046E10(void) {
}

/* the door's: what func_ovl0F_02_80045024 calls once it is open (the two
 * callbacks in D_ovl0F_02_800489F4) */
static void func_ovl0F_02_80046E78(void) {
}

static void func_ovl0F_02_80046E80(void) {
    func_ovl0F_02_80047328(5, 5, 0x11, 6, 0x15, 0x1410);
    func_ovl0F_02_80047328(7, 5, 0x11, 7, 0x15, 0x1411);
    func_ovl0F_02_80047328(8, 5, 0x11, 9, 0x15, 0x1410);
    func_ovl0F_02_80047328(5, 4, 0x11, 6, 0x15, 0x1815);
    func_ovl0F_02_80047328(7, 4, 0x11, 7, 0x15, 0x1F);
    func_ovl0F_02_80047328(8, 4, 0x11, 9, 0x15, 0x1416);
    func_ovl0F_02_80047328(0xA, 4, 0x11, 0xD, 0x15, 0x1411);
    D_ovl0F_02_80048610 = 0;
}

void func_ovl0F_02_80046DF8(void) {
    D_ovl0F_02_80048D5C = -1;
    D_ovl0F_02_80048D60 = -1;
}

void func_ovl0F_02_80046D9C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_02_80047B28(D_ovl0F_02_80048D68.x, D_ovl0F_02_80048D68.y, D_ovl0F_02_80048D68.z);
    func_ovl0F_02_80047B48(arg0, arg1, arg2);
    func_ovl0F_02_80047E58(180);
}

void func_ovl0F_02_80046D54(f32 arg0) {
    f32 sp1C;

    func_ovl0F_02_80047B50(&sp1C, NULL, NULL);
    func_ovl0F_02_80047B48(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0F_02_80046D20(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0F_02_800483E0(arg0, p->unk10, p->unk14, p->unk18);
}

/* case 2's: the wind, the particles and the fog */
static void func_ovl0F_02_80046178(s32 n1, s32 n2) {
    s32 i;

    if (0) {
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80045EB0, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_800454E8, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_8004533C, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80045024, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80044D20, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80044C6C, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80044B28, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80044824, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80043FEC, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80043944, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_800438B4, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80043858, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80043618, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_800434F8, NULL, 0, 0, 0);
        func_ovl0F_02_80047E38((void (*)(void)) func_ovl0F_02_80043404, NULL, 0, 0, 0);
    }
    if (func_ovl0F_02_80047438()->unk10 == 0) {
        D_ovl0F_02_80048600 = 8.5f;
    } else {
        D_ovl0F_02_80048600 = 15.299999f;
    }
    D_ovl0F_02_800485F8 = 0;
    D_ovl0F_02_800485FC = 0.0f;
    D_ovl0F_02_8004860C = 1;
    func_ovl0F_02_800473C8(func_ovl0F_02_80043858, n1);
    func_ovl0F_02_800473C8(func_ovl0F_02_8004533C, n2);
    D_ovl0F_02_800485E0 = func_ovl0F_02_800479B8(0x258);
    D_ovl0F_02_80048F1C = func_ovl0F_02_80047A48(func_ovl0F_02_800454E8, -60);
    D_ovl0F_02_80048F1C->unkC |= 0x210;
    for (i = 0; i < 20; i++) {
        func_ovl0F_02_800453A4(&D_ovl0F_02_80048D80[i]);
        D_ovl0F_02_80048D80[i].unk4 = func_ovl0F_02_80047FF8(240);
    }
    func_ovl0F_02_80047C30(&D_ovl0F_02_80048F10);
    D_ovl0F_02_800485EC = 0.0f;
    D_ovl0F_02_800485F0 = 0.0f;
    D_ovl0F_02_800485F4 = 1.0f;
    func_ovl0F_02_800480B0(0x407);
    func_ovl0F_02_80048188(0xE6, 0xF0, 0xFF);
    func_ovl0F_02_80048178(0x3A2, 0x3B6, 0xE6, 0xF0, 0xFF);
    D_ovl0F_02_80048604 = 930.0f;
    D_ovl0F_02_80048608 = 950.0f;
}

/* case 2's: the movers, their script and their callbacks */
static void func_ovl0F_02_80045F24(UnkStructA **door) {
    UnkStruct_ovl0F_02_80048734 *rec;
    s32 i;

    D_ovl0F_02_80048F20.unk0 = func_ovl0F_02_80047528(func_ovl0F_02_800474C8());
    D_ovl0F_02_80048F20.unk4 = door;
    D_ovl0F_02_80048F20.unkC = 0;
    D_ovl0F_02_80048F20.unk10 = 0;
    D_ovl0F_02_80048F20.unk14 = 0;
    D_ovl0F_02_80048F20.unk16 = -1;
    D_ovl0F_02_80048F20.unk8 = 0.0f;
    D_ovl0F_02_80048610 = 1;
    D_ovl0F_02_80048F20.unk18 = D_ovl0F_02_80048614;
    D_ovl0F_02_80048F20.unk20 = func_ovl0F_02_80044D20;
    for (i = 0; i < 6; i++) {
        D_ovl0F_02_80048734[i].unkC = 10.0f;
        D_ovl0F_02_80048734[i].unk14 = 19.0f;
        D_ovl0F_02_80048734[i].unk1C = 90.0f;
    }
    rec = D_ovl0F_02_80048734;
    for (i = 0; i < 6; i++) {
        *rec->unk0 = func_ovl0F_02_80047D10(rec->unk4, rec->unk24 | 0x01000000, 0x30, rec->unk8);
        func_ovl0F_02_80044C94(rec);
        (*rec->unk0)->unk40->unk1C = rec->unk18;
        (*rec->unk0)->unk40->unk20 = rec->unk1C;
        (*rec->unk0)->unk40->unk24 = rec->unk20;
        rec++;
    }
    for (i = 0; i < 6; i++) {
        func_ovl0F_02_80047CE8(func_ovl0F_02_80047D20(*D_ovl0F_02_80048734[i].unk0), 0x02100000);
        D_ovl0F_02_800486A4[i].unk11 = 0;
        D_ovl0F_02_80048F20.unk20(i, 0);
    }
    func_ovl0F_02_80047420(func_ovl0F_02_80044824);
    func_ovl0F_02_80047E38(func_ovl0F_02_80043FEC, NULL, 0, 0, 0x110);
}

/* a task: the door's switch, pressed a number of times */
void func_ovl0F_02_80045EB0(void) {
    s32 n;
    s32 i;

    n = (s32)func_ovl0F_02_80047E60();
    for (i = 0; i < n; i++) {
        func_ovl0F_02_800483A8();
        func_ovl0F_02_80047E80();
    }
    func_ovl0F_02_80047E48();
}

/* the particles: a display list of textured rectangles */
void func_ovl0F_02_800454E8(s32 arg0, UnkStruct_ovl0F_02_Gfx **arg1) {
    UnkStruct_ovl0F_02_Gfx *gfx;
    UnkStruct_ovl0F_02_80048D80 *p;
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
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x00553048; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF279; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBB000001; g->w1 = 0x80008000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0x8000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xFD100000; g->w1 = D_ovl0F_02_800485E0->unk20 + (u32) D_ovl0F_02_800485E0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE8000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF5000100; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF0000000; g->w1 = 0x0703C000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xFD500000; g->w1 = D_ovl0F_02_800485E0->unk14 + (u32) D_ovl0F_02_800485E0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF5500000; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF3000000; g->w1 = 0x0703F800; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF5400200; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF2000000; g->w1 = 0x0003C03C; }
    oldx = D_ovl0F_02_80048F10.x;
    oldz = D_ovl0F_02_80048F10.z;
    func_ovl0F_02_80047C30(&D_ovl0F_02_80048F10);
    func_ovl0F_02_80047C40(view);
    s = func_ovl0F_02_80047FE8(view[0]);
    c = func_ovl0F_02_80047FE0(view[0]);
    D_ovl0F_02_800485E4 = ((D_ovl0F_02_80048F10.x - oldx) * s - c * (D_ovl0F_02_80048F10.z - oldz)) * 0.5f;
    s = func_ovl0F_02_80047FE8(view[0]);
    c = func_ovl0F_02_80047FE0(view[0]);
    D_ovl0F_02_800485E8 = (c * (D_ovl0F_02_80048F10.x - oldx) + (D_ovl0F_02_80048F10.z - oldz) * s) * 0.2f;
    scale = 1500.0f / view[2];
    D_ovl0F_02_800485E4 *= scale;
    D_ovl0F_02_800485E8 *= scale;
    i = 0;
    if (func_ovl0F_02_800480C0(0x407) == 0) {
        goto update;
    }
    do {
        p = &D_ovl0F_02_80048D80[i];
        dsdx = 16.0f / (p->unk8 - 1.0f) * 1024.0f;
        {
            UnkStruct_ovl0F_02_Gfx *g = gfx++;
            g->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL((u32) (p->unk0 + p->unk8 - 1.0f) << 2, 12, 12) | _SHIFTL((u32) (p->unk4 + p->unk8 - 1.0f) << 2, 0, 12);
            g->w1 = _SHIFTL(0, 24, 3) | _SHIFTL((u32) p->unk0 << 2, 12, 12) | _SHIFTL((u32) p->unk4 << 2, 0, 12);
        }
        { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xB4000000; g->w1 = 0; }
        { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xB3000000; g->w1 = _SHIFTL(dsdx, 16, 16) | _SHIFTL(dsdx, 0, 16); }
    update:
        if (D_ovl0F_02_800485F4 != 0.0f) {
            p = &D_ovl0F_02_80048D80[i];
            s = func_ovl0F_02_80047FE8(view[0]);
            dx = -D_ovl0F_02_800485E4;
            p->unk0 += dx - (f32) func_ovl0F_02_80047FF0() * (dx * 0.25f) + D_ovl0F_02_800485EC * s;
            sign = func_ovl0F_02_800454E0(D_ovl0F_02_800485EC);
            if (func_ovl0F_02_80047FE0(view[0]) * (sign * D_ovl0F_02_800485EC) + D_ovl0F_02_800485F0 < 0.0f) {
                sign = func_ovl0F_02_800454E0(D_ovl0F_02_800485EC);
                drift = (func_ovl0F_02_80047FE0(view[0]) * (sign * D_ovl0F_02_800485EC) + D_ovl0F_02_800485F0) * 0.5;
            } else {
                sign = func_ovl0F_02_800454E0(D_ovl0F_02_800485EC);
                drift = func_ovl0F_02_80047FE0(view[0]) * (sign * D_ovl0F_02_800485EC) + D_ovl0F_02_800485F0;
            }
            p->unk4 += (p->unkC - D_ovl0F_02_800485E8) - (f32) func_ovl0F_02_80047FF0() * ((p->unkC - D_ovl0F_02_800485E8) * 0.6f) + drift;
            p->unk8 -= 0.1f * (p->unk8 * 0.0625f);
            if (340.0f <= p->unk0 || 240.0f <= p->unk4 || p->unk8 <= 3.0f || p->unk10++ >= 240 || p->unk0 < -20.0f ||
                p->unk4 < -10.0f) {
                func_ovl0F_02_800453A4(p);
            }
        }
        i++;
    } while (i != 20);
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0x00080000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0; }
    *arg1 = gfx;
}

static f32 func_ovl0F_02_800454E0(f32 v) {
    return v == 0.0f ? 0.0f : 1.0f;
}

static void func_ovl0F_02_800453A4(UnkStruct_ovl0F_02_80048D80 *p) {
    f32 r;
    f64 t;

    r = func_ovl0F_02_80047FF0();
    p->unk0 = func_ovl0F_02_80047FF0() * 370.0 - 50.0;
    t = func_ovl0F_02_80047FF0();
    p->unk4 = (D_ovl0F_02_800485EC < 0.0f ? -D_ovl0F_02_800485EC : D_ovl0F_02_800485EC) * 30.0f * t;
    if (D_ovl0F_02_800485E8 <= 0.0f) {
        p->unk4 += (1.0f - r) * 40.0f;
    } else {
        p->unk4 += func_ovl0F_02_80047FF8(90);
    }
    p->unk10 = 0;
    p->unk8 = r * 12.0f + 4.0f;
    p->unkC = r * r * 5.0f + 0.5f;
}

/* a callback (case 2): the wind pushes an object, more weakly */
void func_ovl0F_02_8004533C(UnkStructA *obj) {
    func_ovl0F_02_800436D8(obj, D_ovl0F_02_800485FC * 0.42857143f);
}

/* a task: the door opens once its switch is hit */
void func_ovl0F_02_80045024(void) {
    UnkStruct_ovl0F_02_800489F4 *task;
    f32 pos[3];
    s32 hit;

    task = func_ovl0F_02_80047E60();
    func_ovl0F_02_80047348(task->unk0[0].unkC, task->unk0[0].unk10, task->unk0[0].unk14, pos, 0);
    func_ovl0F_02_80044F74(task->unk0, 2);
    (*task->unk0[0].unk0)->unk34 = 250.0f;
    (*task->unk0[0].unk0)->unkC = 0;
    (*task->unk0[1].unk0)->unkC = 0;
    (*task->unk0[1].unk0)->unk70 = 2.45f;
    while (func_ovl0F_02_800480C0(task->unk0[0].unk28) == 0) {
        hit = func_ovl0F_02_80047C98(*task->unk0[0].unk0, 0x40);
        if (hit != 0) {
            if ((hit & 0x2000) || (hit & 0x4000)) {
                func_ovl0F_02_800480B0(task->unk0[0].unk28);
            } else {
                func_ovl0F_02_800483E8(0x26, pos);
            }
        }
        func_ovl0F_02_80047E58(5);
    }
    func_ovl0F_02_800483E8(0x8A, pos);
    func_ovl0F_02_80044E9C(pos, 0x14, 250.0f, 120.0f);
    func_ovl0F_02_80047E58(10);
    func_ovl0F_02_80044E9C(pos, 0x16, 250.0f, 120.0f);
    func_ovl0F_02_80043020(1, task->unk0);
    *task->unk0[0].unk0 = NULL;
    func_ovl0F_02_80047328((s32) task->unk0[1].unkC - 2, (s32) task->unk0[1].unk10, (s32) task->unk0[1].unk14 - 2,
                           (s32) task->unk0[1].unkC + 2, (s32) task->unk0[1].unk14 + 2, 0x1410);
    task->unk58();
    func_ovl0F_02_80047D68(*task->unk0[1].unk0);
    func_ovl0F_02_80047E80();
    do {
        func_ovl0F_02_80047D68(*task->unk0[1].unk0);
        func_ovl0F_02_80047E80();
    } while ((*task->unk0[1].unk0)->unk6C != 0.0f);
    task->unk5C();
    func_ovl0F_02_80047E48();
}

static void func_ovl0F_02_80044F74(UnkStruct_ovl0F_02_80048734 *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *arg0->unk0 = func_ovl0F_02_80047D58(arg0->unk4, arg0->unk8);
        func_ovl0F_02_80047CE8(*arg0->unk0, arg0->unk24 | 0x01000000);
        func_ovl0F_02_80044C94(arg0);
        (*arg0->unk0)->unk40->unk1C = arg0->unk18;
        (*arg0->unk0)->unk40->unk20 = arg0->unk1C;
        (*arg0->unk0)->unk40->unk24 = arg0->unk20;
        arg0++;
    }
}

/* four effects at the corners of a square around pos */
static void func_ovl0F_02_80044E9C(f32 *pos, s32 id, f32 d, f32 h) {
    func_ovl0F_02_80048288(id, pos[0] + d, pos[1] + h, pos[2] + d, 0);
    func_ovl0F_02_80048288(id, pos[0] + d, pos[1] + h, pos[2] - d, 0);
    func_ovl0F_02_80048288(id, pos[0] - d, pos[1] + h, pos[2] + d, 0);
    func_ovl0F_02_80048288(id, pos[0] - d, pos[1] + h, pos[2] - d, 0);
}

/* the movers' callback (D_ovl0F_02_80048F20.unk20): mover i back to its
 * start, shown (flag set) or hidden */
void func_ovl0F_02_80044D20(s32 i, s32 flag) {
    UnkStruct_ovl0F_02_80048734 *rec;
    UnkStruct_ovl0F_02_800486A4 *st;

    rec = &D_ovl0F_02_80048734[i];
    func_ovl0F_02_80044C94(rec);
    st = &D_ovl0F_02_800486A4[i];
    st->unkC = 0;
    st->unk12 = 0;
    st->unk14 = 1;
    st->unk11 = flag;
    if (flag == 0) {
        func_ovl0F_02_80047CF0(*rec->unk0, 0x01000070);
    } else {
        func_ovl0F_02_80047CE8(*rec->unk0, 0x01000070);
    }
    st->unk10 = 0;
    st->unk4 = 1.0f;
    st->unk8 = 0.05f;
    (*rec->unk0)->unk40->unk14 = 2200.0f;
    if (flag != 0) {
        (*rec->unk0)->unk68 = 20.0f;
        (*rec->unk0)->unk6C = 0.0f;
        func_ovl0F_02_80048288(0xC, (*rec->unk0)->unk40->unk10, (*rec->unk0)->unk40->unk14,
                               (*rec->unk0)->unk40->unk18, 0);
    }
}

static void func_ovl0F_02_80044C94(UnkStruct_ovl0F_02_80048734 *arg0) {
    f32 pos[3];

    func_ovl0F_02_80047348(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

/* passed to func_ovl0F_02_80048330 */
s32 func_ovl0F_02_80044C6C(s32 arg0) {
    if ((arg0 & 0xF) == 0xF) {
        return 0;
    }
    return 1;
}

/* a task: the sparks over a mover that was hit */
void func_ovl0F_02_80044B28(void) {
    UnkStruct_ovl0F_02_80048734 *rec;
    s32 i;

    rec = &D_ovl0F_02_80048734[(s32) func_ovl0F_02_80047E60()];
    for (i = 0; i < 3; i++) {
        func_ovl0F_02_80048288(7, (*rec->unk0)->unk40->unk10, (*rec->unk0)->unk40->unk14 + 100.0f,
                               (*rec->unk0)->unk40->unk18, 0);
        func_ovl0F_02_80047E58(3);
    }
    for (i = 0; i < 5; i++) {
        func_ovl0F_02_80048288(0x18, (*rec->unk0)->unk40->unk10, (*rec->unk0)->unk40->unk14 + 100.0f,
                               (*rec->unk0)->unk40->unk18, 0);
        func_ovl0F_02_80047E58(3);
    }
    func_ovl0F_02_80048288(0x16, (*rec->unk0)->unk40->unk10, (*rec->unk0)->unk40->unk14 + 100.0f,
                           (*rec->unk0)->unk40->unk18, 0);
    func_ovl0F_02_80047E48();
}

/* the callback func_ovl0F_02_80045F24 registers: an object a mover hit
 * flies off */
void func_ovl0F_02_80044824(UnkStructA *obj) {
    s32 dir;
    f32 speed;
    s32 i;
    f32 dy;

    dir = 0;
    speed = 0.0f;
    func_ovl0F_02_800483C0(0x1E);
    if (D_ovl0F_02_80048F20.unk16 != -1) {
        dir = D_ovl0F_02_800486A4[D_ovl0F_02_80048F20.unk16].unk0;
        speed = D_ovl0F_02_800486A4[D_ovl0F_02_80048F20.unk16].unk4 * 0.8f;
    }
    func_ovl0F_02_80047A10(obj->unk40, 0x11, 0);
    func_ovl0F_02_80047A40(obj->unk40, 4, 0xC);
    func_ovl0F_02_80047A40(obj->unk40, 5, 0xD);
    func_ovl0F_02_80048288(0, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
    obj->unk68 = 30.0f;
    obj->unk70 = 1.6333334f;
    for (i = 1; i < 201 && obj->unk68 > 0.0f && !func_ovl0F_02_80043B28(obj); i++) {
        dy = func_ovl0F_02_80047FE8(obj->unk40->unk1C) * 30.0f;
        func_ovl0F_02_80048330(obj, dir, speed, func_ovl0F_02_80044C6C);
        obj->unk40->unk1C += 10.0f;
        obj->unk40->unk10 -= func_ovl0F_02_80047FE0(obj->unk40->unk1C);
        if (dy > 0.0f) {
            dy = 0.0f;
        }
        obj->unk40->unk14 -= dy;
        func_ovl0F_02_80047E80();
    }
    if (func_ovl0F_02_80043B28(obj)) {
        func_ovl0F_02_800434F8(obj);
    } else {
        obj->unk6C = 0.0f;
        obj->unk70 = 0.0f;
    }
    func_ovl0F_02_80047E58(0x50);
}

/* a task: the movers, every frame, until they are all gone */
void func_ovl0F_02_80043FEC(void) {
    s32 active;
    s32 i;
    UnkStruct_ovl0F_02_800486A4 *st;
    UnkStruct_ovl0F_02_80048734 *rec;
    UnkStruct_ovl0F_02_8004862C *step;
    UnkStructA *obj;
    UnkStructA *player;
    s32 hit;
    f32 pos[3];
    f32 tilt;
    f32 slope;

    active = TRUE;
    do {
        func_ovl0F_02_80043D6C(D_ovl0F_02_80048610);
        if (D_ovl0F_02_80048F20.unkC != 0) {
            obj = *D_ovl0F_02_80048F20.unk4;
            if (obj != NULL && obj->unk40->unk48 != NULL) {
                obj->unk40->unk48->unk4->unk4 = D_ovl0F_02_80048F20.unk8;
                if (D_ovl0F_02_80048F20.unkC == 1) {
                    D_ovl0F_02_80048F20.unk8 += 1.0f;
                    if (func_ovl0F_02_80047A28((*D_ovl0F_02_80048F20.unk4)->unk40, 0) <= D_ovl0F_02_80048F20.unk8) {
                        D_ovl0F_02_80048F20.unk8 = 0.0f;
                        D_ovl0F_02_80048F20.unkC = 0;
                    }
                } else {
                    D_ovl0F_02_80048F20.unk8 -= 1.0f;
                    if (D_ovl0F_02_80048F20.unk8 < 0.0f) {
                        D_ovl0F_02_80048F20.unk8 = 0.0f;
                        D_ovl0F_02_80048F20.unkC = 0;
                        obj = *D_ovl0F_02_80048F20.unk4;
                        if (obj != NULL) {
                            func_ovl0F_02_800483E0(0x8C, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
                        }
                    }
                }
            }
        }
        for (i = 0; i < 6; i++) {
            st = &D_ovl0F_02_800486A4[i];
            rec = &D_ovl0F_02_80048734[i];
            if (st->unk11 == 1) {
                func_ovl0F_02_80047DF8(*rec->unk0);
                player = D_ovl0F_02_80048F20.unk0;
                if (player->unk40->unk10 <= (*rec->unk0)->unk40->unk10 + 300.0f &&
                    (*rec->unk0)->unk40->unk10 - 300.0f <= player->unk40->unk10 &&
                    player->unk40->unk18 <= (*rec->unk0)->unk40->unk18 + 300.0f &&
                    (*rec->unk0)->unk40->unk18 - 300.0f <= player->unk40->unk18) {
                    if (st->unk14 != 0) {
                        func_ovl0F_02_800483C0(0x87);
                        st->unk14 = 0;
                    }
                } else if (st->unk14 == 0) {
                    st->unk14 = 1;
                }
                if ((*rec->unk0)->unk6C == 0.0f) {
                    step = &D_ovl0F_02_8004862C[st->unk10][st->unk12];
                    if (st->unkC >= step->unk0) {
                        if (rec->unk1C == 90.0f) {
                            st->unkC = 0;
                            st->unk0 = step->unk2;
                            st->unk8 = step->unk4;
                            st->unk12 = step->unk3;
                        }
                        if (rec->unk1C == 270.0f) {
                            st->unk0 = (step->unk2 + 0x80) & 0xFF;
                            st->unkC = 0;
                            st->unk8 = step->unk4;
                            st->unk12 = step->unk3;
                        }
                    }
                }
                st->unkC++;
                func_ovl0F_02_80043B30(i);
                func_ovl0F_02_80048330(*rec->unk0, st->unk0, st->unk4, func_ovl0F_02_80044C6C);
                tilt = 0.0f;
                slope = 0.0f;
                func_ovl0F_02_80047370((*rec->unk0)->unk40, &tilt, &slope);
                if (func_ovl0F_02_80047FE0((*rec->unk0)->unk40->unk20) >= 0.707f && slope != 0.0f) {
                    tilt *= func_ovl0F_02_80047FE0(slope);
                }
                (*rec->unk0)->unk40->unk1C = tilt * 0.6f;
                if (func_ovl0F_02_80043B28(*rec->unk0)) {
                    D_ovl0F_02_80048F20.unk20(i, 0);
                } else {
                    hit = func_ovl0F_02_80047C98(*rec->unk0, 0x40);
                    if (hit != 0 && ((hit & 0x2000) || (hit & 0x4000))) {
                        pos[0] = (*rec->unk0)->unk40->unk10;
                        pos[1] = (*rec->unk0)->unk40->unk14;
                        pos[2] = (*rec->unk0)->unk40->unk18;
                        func_ovl0F_02_800483E8(0x168, pos);
                        func_ovl0F_02_800483A0(pos);
                        (*rec->unk0)->unk68 = 20.0f;
                        (*rec->unk0)->unk70 = 0.81666666f;
                        st->unk11 = 2;
                        func_ovl0F_02_80047E38(func_ovl0F_02_80044B28, (void *) i, 0, 0, 0x150);
                    }
                    if (func_ovl0F_02_80047CB0(D_ovl0F_02_80048F20.unk0, *rec->unk0) != 0) {
                        D_ovl0F_02_80048F20.unk16 = i;
                    }
                    st->unk4 += st->unk8;
                }
            } else if (st->unk11 == 2) {
                if ((*rec->unk0)->unk68 == 0.0f && (*rec->unk0)->unk6C == 0.0f) {
                    D_ovl0F_02_80048F20.unk20(i, 0);
                } else {
                    if ((*rec->unk0)->unk40->unk1C < 180.0f) {
                        (*rec->unk0)->unk40->unk1C += 5.0f;
                    }
                    func_ovl0F_02_80048330(*rec->unk0, st->unk0, st->unk4, func_ovl0F_02_80044C6C);
                    func_ovl0F_02_80047D68(*rec->unk0);
                    if (func_ovl0F_02_80043B28(*rec->unk0)) {
                        D_ovl0F_02_80048F20.unk20(i, 0);
                    }
                }
            }
        }
        if (D_ovl0F_02_80048610 == 0) {
            active = FALSE;
            for (i = 0; i < 6; i++) {
                if (D_ovl0F_02_800486A4[i].unk11 != 0) {
                    active = TRUE;
                }
            }
        }
        func_ovl0F_02_80047E80();
    } while (active);
    for (i = 0; i < 6; i++) {
        func_ovl0F_02_80047D00(*D_ovl0F_02_80048734[i].unk0);
    }
    func_ovl0F_02_80047E48();
}

/* the movers' script (D_ovl0F_02_80048614), one frame */
static void func_ovl0F_02_80043D6C(s32 active) {
    UnkStruct_ovl0F_02_80048614 *cmd;
    s32 kind;
    s32 n;
    UnkStructA *obj;

    cmd = &D_ovl0F_02_80048F20.unk18[D_ovl0F_02_80048F20.unk14];
    if (cmd->unk0 == D_ovl0F_02_80048F20.unk10++) {
        if (cmd->unk2 == 0x64) {
            D_ovl0F_02_80048F20.unk10 = 0;
            D_ovl0F_02_80048F20.unk14 = 0;
            return;
        }
        if (active) {
            switch (cmd->unk2) {
                case 0:
                    kind = 1;
                    n = 0;
                    break;
                case 1:
                    kind = 1;
                    n = 1;
                    break;
                case 2:
                    kind = 1;
                    n = 2;
                    break;
                case 7:
                    kind = 1;
                    n = 3;
                    break;
                case 8:
                    kind = 1;
                    n = 4;
                    break;
                case 9:
                    kind = 1;
                    n = 5;
                    break;
                case 0x62:
                    kind = 10;
                    n = 1;
                    break;
                case 0x63:
                    kind = 10;
                    n = 2;
                    break;
            }
            switch (kind) {
                case 1:
                    if (D_ovl0F_02_800486A4[n].unk11 == 0) {
                        D_ovl0F_02_80048F20.unk20(n, 1);
                    }
                    break;
                case 10:
                    switch (n) {
                        case 1:
                            obj = *D_ovl0F_02_80048F20.unk4;
                            if (obj != NULL) {
                                func_ovl0F_02_800483E0(0x8C, obj->unk40->unk10, obj->unk40->unk14,
                                                       obj->unk40->unk18);
                            }
                            if (D_ovl0F_02_80048F20.unkC == 0) {
                                D_ovl0F_02_80048F20.unkC = 1;
                                D_ovl0F_02_80048F20.unk8 = 0.0f;
                            }
                            break;
                        case 2:
                            if (D_ovl0F_02_80048F20.unkC == 0) {
                                D_ovl0F_02_80048F20.unkC = 2;
                                obj = *D_ovl0F_02_80048F20.unk4;
                                if (obj != NULL) {
                                    D_ovl0F_02_80048F20.unk8 = func_ovl0F_02_80047A28(obj->unk40, 0) - 0.001f;
                                }
                            }
                            break;
                    }
                    break;
            }
        }
        D_ovl0F_02_80048F20.unk14++;
    }
}

/* mover i turns towards its heading */
static void func_ovl0F_02_80043B30(s32 i) {
    f32 target;
    f32 step;
    UnkStruct_ovl0F_02_80048734 *rec;

    target = 0.0f;
    switch (D_ovl0F_02_800486A4[i].unk0) {
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
    rec = &D_ovl0F_02_80048734[i];
    if (target < (*rec->unk0)->unk40->unk20) {
        step = ((*rec->unk0)->unk40->unk20 - target) * 0.1f;
        if (step > 1.0f) {
            (*rec->unk0)->unk40->unk20 -= step;
        } else {
            (*rec->unk0)->unk40->unk20 -= 1.0f;
        }
        if ((*rec->unk0)->unk40->unk20 < target) {
            (*rec->unk0)->unk40->unk20 = target;
        }
    } else if ((*rec->unk0)->unk40->unk20 < target) {
        step = (target - (*rec->unk0)->unk40->unk20) * 0.1f;
        if (step > 1.0f) {
            (*rec->unk0)->unk40->unk20 += step;
        } else {
            (*rec->unk0)->unk40->unk20 += 1.0f;
        }
        if (target < (*rec->unk0)->unk40->unk20) {
            (*rec->unk0)->unk40->unk20 = target;
        }
    }
}

/* whether an object is down at the floor's height */
static s32 func_ovl0F_02_80043B28(UnkStructA *obj) {
    s32 below;

    below = FALSE;
    if (obj->unk40->unk14 <= func_ovl0F_02_80047310()) {
        below = TRUE;
    }
    return below;
}

/* a task (case 0x52): switch D_ovl0F_02_80048D74 goes down */
void func_ovl0F_02_80043944(void) {
    s32 i;
    UnkStruct_ovl0F_02_80048734 *rec;
    UnkStructA *obj;
    s32 x;
    s32 z;
    s32 give;

    i = D_ovl0F_02_80048D74;
    rec = &D_ovl0F_02_8004883C[i];
    if (rec->unk1C == 0.0f) {
        x = rec->unkC;
        z = rec->unk14;
        func_ovl0F_02_80047328(x - 1, rec->unk10, z - 1, x, z, D_ovl0F_02_80048918[i].unk4);
    }
    D_ovl0F_02_80048918[i].unk0 = 0;
    obj = D_ovl0F_02_80048D18[i];
    give = D_ovl0F_02_80048918[i].unk8;
    do {
        func_ovl0F_02_80047D68(obj);
        func_ovl0F_02_80047E80();
    } while (obj->unk6C != 0.0f);
    func_ovl0F_02_80048288(0x10, obj->unk40->unk10, obj->unk40->unk14 + 200.0f, obj->unk40->unk18, 0);
    if (give == -1) {
        give = 7;
    }
    func_ovl0F_02_80048308(give, obj->unk40->unk10, obj->unk40->unk14 + 50.0f, obj->unk40->unk18);
    func_ovl0F_02_80047CF0(obj, 0x01000000);
    func_ovl0F_02_80047E48();
}

/* a callback (case 2): the wind, and a sound */
void func_ovl0F_02_800438B4(UnkStructA *obj) {
    if (obj->unk8 & 1) {
        func_ovl0F_02_800473E0(0x58, 0x15, 2);
    }
    func_ovl0F_02_800436D8(obj, D_ovl0F_02_800485FC);
}

/* a callback (case 2): the wind pushes an object */
void func_ovl0F_02_80043858(UnkStructA *obj) {
    func_ovl0F_02_800436D8(obj, D_ovl0F_02_800485FC);
}

/* the wind moves an object along x unless something is in its way */
static void func_ovl0F_02_800436D8(UnkStructA *obj, f32 speed) {
    Vec3f pos;
    s32 saved;
    s32 hit;
    UnkStructA *other;
    s32 k;

    pos.x = obj->unk40->unk10;
    pos.y = obj->unk40->unk14;
    pos.z = obj->unk40->unk18;
    if (func_ovl0F_02_800473A8(obj->unk40) == obj->unk40->unk14) {
        func_ovl0F_02_80048338(obj, 0x40, speed);
    } else {
        func_ovl0F_02_800436B8(obj, speed);
    }
    saved = obj->unkC;
    hit = FALSE;
    other = NULL;
    obj->unkC = 0;
    if (obj->unk8 & 1) {
        other = func_ovl0F_02_80047568(func_ovl0F_02_800474C8());
    } else if (obj->unk8 & 2) {
        k = func_ovl0F_02_800474C8();
        if (func_ovl0F_02_80047568(k) == obj) {
            other = func_ovl0F_02_80047528(k);
        }
    }
    if (other != NULL) {
        if (func_ovl0F_02_80047E08(obj, 0x10, other) != 0) {
            hit = TRUE;
        }
    } else {
        if (func_ovl0F_02_80047C98(obj, 0x10) != 0) {
            hit = TRUE;
        }
    }
    obj->unkC = saved;
    if (hit) {
        obj->unk40->unk10 = pos.x;
        obj->unk40->unk14 = pos.y;
        obj->unk40->unk18 = pos.z;
    }
}

static void func_ovl0F_02_800436B8(UnkStructA *obj, f32 speed) {
    obj->unk40->unk10 += speed;
}

/* a task: the camera waits for the player to pass x 1200 */
void func_ovl0F_02_80043618(void) {
    UnkStructA *obj;

    obj = func_ovl0F_02_80047528(func_ovl0F_02_800474C8());
    while (1200.0f < obj->unk40->unk10) {
        func_ovl0F_02_80047E80();
    }
    func_ovl0F_02_80047E58(30);
    func_ovl0F_02_800474F0("MA");
    func_ovl0F_02_80047E48();
}

/* the callback case 4 registers: an object sinks back over 30 frames */
void func_ovl0F_02_800434F8(UnkStructA *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl0F_02_80047B90(0x10);
    }
    dx = arg0->unk40->unk28 / 30.0f;
    dy = arg0->unk40->unk2C / 30.0f;
    dz = arg0->unk40->unk30 / 30.0f;
    func_ovl0F_02_80047CF0(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        arg0->unk40->unk28 -= dx;
        arg0->unk40->unk2C -= dy;
        arg0->unk40->unk30 -= dz;
        func_ovl0F_02_80047D68(arg0);
        func_ovl0F_02_80047E80();
    }
    func_ovl0F_02_80047CF0(arg0, 0x01000000);
}

/* a task (case 4): the stage's opening demo */
void func_ovl0F_02_80043404(void) {
    D_ovl0F_02_80048B08[0] = 0;
    func_ovl0F_02_800474D8(1);
    while (D_ovl0F_02_80048B08[0] == 0) {
        func_ovl0F_02_80047E80();
    }
    func_ovl0F_02_80047450(0);
    func_ovl0F_02_80047588(1);
    func_ovl0F_02_800474F0("WM1 WG1 WSH WAP WDSW WB2");
    func_ovl0F_02_800474F0("WM1 WG1 WSH WAP WDW WB11 WDNW WB1");
    func_ovl0F_02_80047B60(D_ovl0F_02_80048AC4, 0x170, 0);
    func_ovl0F_02_800474F0("M1 ST1 M6 ST1");
    func_ovl0F_02_800474F0("WM1 WG1 WSH WAP WDNE WB2 WDN WB0");
    func_ovl0F_02_800474F0("M2 ST200");
    func_ovl0F_02_800474F0("WM1 WG1 WSH WAP WDN WB3 WDW WB0");
    func_ovl0F_02_800474F0("WM1 WG1 WSH WAP WDW WB5");
    func_ovl0F_02_800474F0("M0 M0");
    func_ovl0F_02_80047E58(60);
    func_ovl0F_02_80048538();
    func_ovl0F_02_80047E48();
}

void func_ovl0F_02_800433A0(s32 *arg0) {
    if (func_ovl0F_02_800474B0(arg0[0], arg0[1], arg0[2], arg0[3]) != 0) {
        func_ovl0F_02_800473E0(arg0[4], arg0[5], arg0[6]);
    }
}

/* the cut to the camera at a switch: a task, then a camera script */
void func_ovl0F_02_80043324(s32 n, char *script) {
    func_ovl0F_02_80047588(1);
    func_ovl0F_02_800482C8();
    func_ovl0F_02_80047E38(func_ovl0F_02_80045EB0, (void *) n, 0, 0, 0x130);
    func_ovl0F_02_800474F0(script);
    func_ovl0F_02_80047588(0);
    func_ovl0F_02_800474F0("MA");
}

/* case 3's: the wind rises and falls over 720 frames, the fog with it */
void func_ovl0F_02_80043028(void) {
    f32 d;

    if (D_ovl0F_02_800485F8 >= 160) {
        if (D_ovl0F_02_800485F8 < 460) {
            D_ovl0F_02_80048604 += -20.0f / 300.0f;
            D_ovl0F_02_80048608 += -10.0f / 300.0f;
            func_ovl0F_02_80048178(D_ovl0F_02_80048604, D_ovl0F_02_80048608, 0xE6, 0xF0, 0xFF);
        } else if (D_ovl0F_02_800485F8 >= 540 && D_ovl0F_02_800485F8 < 720) {
            D_ovl0F_02_80048604 -= -20.0f / 180.0f;
            D_ovl0F_02_80048608 -= -10.0f / 180.0f;
            func_ovl0F_02_80048178(D_ovl0F_02_80048604, D_ovl0F_02_80048608, 0xE6, 0xF0, 0xFF);
        }
    }
    D_ovl0F_02_800485F8++;
    if (D_ovl0F_02_800485F8 >= 720) {
        D_ovl0F_02_800485F8 = 0;
    }
    d = 0.0f;
    if (D_ovl0F_02_800485F8 >= 160) {
        if (D_ovl0F_02_800485F8 < 460) {
            d = D_ovl0F_02_80048600 / 300.0f;
        } else if (D_ovl0F_02_800485F8 >= 540 && D_ovl0F_02_800485F8 < 720) {
            d = -(D_ovl0F_02_80048600 / 180.0f);
        }
    }
    D_ovl0F_02_800485FC += d;
    if (2.0f <= D_ovl0F_02_800485FC && D_ovl0F_02_8004860C == 1) {
        D_ovl0F_02_8004860C = 0;
        func_ovl0F_02_800483C0(0x89);
    } else if (D_ovl0F_02_800485FC < 2.0f) {
        D_ovl0F_02_8004860C = 1;
    }
    D_ovl0F_02_800485EC = D_ovl0F_02_800485FC * 0.5f;
    D_ovl0F_02_800485F0 = 0.0f;
}

static void func_ovl0F_02_80043020(s32 count, UnkStruct_ovl0F_02_80048734 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_02_80047D00(*p->unk0);
        p++;
    }
}

/* case 0x52's: the switch the player stands on, or -1 */
static s32 func_ovl0F_02_80043018(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (D_ovl0F_02_80048918[i].unk0 != 0 && D_ovl0F_02_8004883C[i].unk1C == 0.0f &&
            func_ovl0F_02_800474B0((s32) D_ovl0F_02_8004883C[i].unkC - 1, (s32) D_ovl0F_02_8004883C[i].unk14 - 1,
                                   (s32) D_ovl0F_02_8004883C[i].unkC, (s32) D_ovl0F_02_8004883C[i].unk14) != 0) {
            return i;
        }
    }
    return -1;
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_02_800462F8(s32 arg0) {
    s32 i;

    switch (arg0) {
        case 2:
            D_ovl0F_02_80048D7C = func_ovl0F_02_800473E8();
            if (D_ovl0F_02_80048D7C == 0x14) {
                D_ovl0F_02_80048954 = 1;
                func_ovl0F_02_80048368(0);
            } else {
                D_ovl0F_02_80048954 = 0;
            }
            func_ovl0F_02_800481A0(D_ovl0F_02_80048958);
            for (i = 0; i < 6; i++) {
                func_ovl0F_02_80048348(D_ovl0F_02_8004897C[i][0], D_ovl0F_02_8004897C[i][1], D_ovl0F_02_8004897C[i][2]);
            }
            func_ovl0F_02_800472E8(0x224);
            func_ovl0F_02_80047300(0x238);
            func_ovl0F_02_80047498();
            if (D_ovl0F_02_80048954 == 0) {
                func_ovl0F_02_80046178(5, 6);
            } else {
                func_ovl0F_02_80046178(1, 2);
            }
            func_ovl0F_02_80044F74(&D_ovl0F_02_800489C4, 1);
            if (func_ovl0F_02_800480C0(D_ovl0F_02_800489F4.unk0[0].unk28) == 0) {
                func_ovl0F_02_80047E38(func_ovl0F_02_80045024, &D_ovl0F_02_800489F4, 0, 0, 0x110);
            } else {
                D_ovl0F_02_800489F4.unk58();
                D_ovl0F_02_800489F4.unk5C();
                D_ovl0F_02_800489F4.unk0[1].unk10 -= 1.0f;
                func_ovl0F_02_80044F74(&D_ovl0F_02_800489F4.unk0[1], 1);
                *D_ovl0F_02_800489F4.unk0[0].unk0 = NULL;
                D_ovl0F_02_800489F4.unk0[1].unk10 += 1.0f;
            }
            func_ovl0F_02_80044F74(D_ovl0F_02_8004883C, 5);
            for (i = 0; i < 5; i++) {
                if (D_ovl0F_02_8004883C[i].unk1C == 0.0f) {
                    func_ovl0F_02_80047328((s32) D_ovl0F_02_8004883C[i].unkC - 1, D_ovl0F_02_8004883C[i].unk10,
                                           (s32) D_ovl0F_02_8004883C[i].unk14 - 1, (s32) D_ovl0F_02_8004883C[i].unkC - 1,
                                           D_ovl0F_02_8004883C[i].unk14, 0x1411);
                    func_ovl0F_02_80047328(D_ovl0F_02_8004883C[i].unkC, D_ovl0F_02_8004883C[i].unk10,
                                           (s32) D_ovl0F_02_8004883C[i].unk14 - 1, D_ovl0F_02_8004883C[i].unkC,
                                           D_ovl0F_02_8004883C[i].unk14, 0x141A);
                }
                D_ovl0F_02_80048918[i].unk0 = 1;
                D_ovl0F_02_80048918[i].unk8 = -1;
            }
            D_ovl0F_02_80048918[func_ovl0F_02_80047FF8(4)].unk8 = 3;
            if (func_ovl0F_02_800480C0(0x400) == 0) {
                func_ovl0F_02_80045F24(&D_ovl0F_02_800489F0);
            }
            func_ovl0F_02_800473C8(func_ovl0F_02_800438B4, 7);
            break;
        case 17:
            func_ovl0F_02_800474E0(0x40);
            func_ovl0F_02_800474A0(0x1C, 0, 0x10);
            break;
        case 18:
            func_ovl0F_02_800474A0(0xB, 4, 0x12);
            break;
        case 19:
            func_ovl0F_02_800474E0(0xA0);
            func_ovl0F_02_800474A0(0xD, 4, 2);
            break;
        case 20:
            D_ovl0F_02_80048954 = 1;
            func_ovl0F_02_800474A0(0x16, 2, 0x17);
            break;
        case 4:
            func_ovl0F_02_800474F8();
            func_ovl0F_02_800473D0(func_ovl0F_02_800434F8);
            func_ovl0F_02_80047DC8(40.0f);
            func_ovl0F_02_80047DD0(30);
            if (D_ovl0F_02_80048954 == 1) {
                func_ovl0F_02_80047B48(0.0f, 32768.0f, 32768.0f);
                func_ovl0F_02_80047E38(func_ovl0F_02_80043404, NULL, 0, 0, 0x130);
                func_ovl0F_02_80047B90(0xF);
                func_ovl0F_02_80047BA0(1);
            }
            break;
        case 5:
            switch (func_ovl0F_02_800473E8()) {
                case 17:
                    func_ovl0F_02_800474E8(D_ovl0F_02_80048A8C[0].unk0, D_ovl0F_02_80048A8C[0].unk4,
                                           D_ovl0F_02_80048A8C[0].unk8, D_ovl0F_02_80048A8C[0].unkC,
                                           D_ovl0F_02_80048A8C[0].unk10, D_ovl0F_02_80048A8C[0].unk14,
                                           D_ovl0F_02_80048A8C[0].unk18);
                    break;
                case 19:
                    func_ovl0F_02_800474E8(D_ovl0F_02_80048A8C[1].unk0, D_ovl0F_02_80048A8C[1].unk4,
                                           D_ovl0F_02_80048A8C[1].unk8, D_ovl0F_02_80048A8C[1].unkC,
                                           D_ovl0F_02_80048A8C[1].unk10, D_ovl0F_02_80048A8C[1].unk14,
                                           D_ovl0F_02_80048A8C[1].unk18);
                    func_ovl0F_02_80047E38(func_ovl0F_02_80043618, NULL, 0, 0, 0x130);
                    break;
            }
            break;
        case 0x50:
            func_ovl0F_02_800433A0(D_ovl0F_02_80048A54);
            func_ovl0F_02_800433A0(D_ovl0F_02_80048A70);
            break;
        case 0x52:
            if (func_ovl0F_02_800474B0(0x12, 0xA, 0x12, 0xA) != 0) {
                if (func_ovl0F_02_800480C0(0x406) == 0) {
                    func_ovl0F_02_80047DC8(0.0f);
                    func_ovl0F_02_80047DD0(0x7F);
                    func_ovl0F_02_800480B0(0x406);
                    func_ovl0F_02_800480B8(0x407);
                    func_ovl0F_02_80047C48();
                    func_ovl0F_02_80047B90(0xF);
                    func_ovl0F_02_80047B88(0x10);
                    func_ovl0F_02_80047B18(0);
                    func_ovl0F_02_80047B38(581.4f, 1430.1f, 1133.3f);
                    func_ovl0F_02_80043324(60, "WM1 WG1 WSH WAP WDW WB3 ST10");
                }
            } else {
                i = func_ovl0F_02_80043018();
                if (i != -1) {
                    D_ovl0F_02_80048D74 = i;
                    func_ovl0F_02_80047E38(func_ovl0F_02_80043944, NULL, 0, 0, 0x110);
                }
            }
            break;
        case 0x53:
            if (func_ovl0F_02_800474B0(0x13, 0xA, 0x13, 0xA) != 0 && func_ovl0F_02_800480C0(0x406) != 0) {
                func_ovl0F_02_80047DC8(40.0f);
                func_ovl0F_02_80047DD0(30);
                func_ovl0F_02_800480B8(0x406);
                func_ovl0F_02_800480B0(0x407);
                func_ovl0F_02_80047B88(0x1F);
                func_ovl0F_02_80047B18(1);
                func_ovl0F_02_80047C50();
                func_ovl0F_02_80047C18(D_ovl0F_02_80048D38);
                func_ovl0F_02_80043324(60, "WM1 WG1 WSH WAP WDE WB2 ST30");
            }
            break;
        case 1:
            func_ovl0F_02_800479D8(D_ovl0F_02_80048F1C);
            func_ovl0F_02_800479C0(0x258);
            func_ovl0F_02_80043020(5, D_ovl0F_02_8004883C);
            func_ovl0F_02_80043020(1, &D_ovl0F_02_800489C4);
            if (func_ovl0F_02_800480C0(D_ovl0F_02_800489F4.unk0[0].unk28) == 0) {
                func_ovl0F_02_80043020(2, D_ovl0F_02_800489F4.unk0);
            } else {
                func_ovl0F_02_80043020(1, &D_ovl0F_02_800489F4.unk0[1]);
            }
            *D_ovl0F_02_800489F4.unk0[0].unk0 = NULL;
            if (D_ovl0F_02_80048954 == 1) {
                func_ovl0F_02_80048540();
            }
            break;
        case 12:
            func_ovl0F_02_80047530(1);
            break;
        case 3:
            D_ovl0F_02_80048D54 = func_ovl0F_02_800474C8();
            func_ovl0F_02_800474A8(&D_ovl0F_02_80048D48);
            func_ovl0F_02_800474D0(D_ovl0F_02_80048D54, D_ovl0F_02_80048D38);
            D_ovl0F_02_80048B08[0] = 1;
            func_ovl0F_02_80043028();
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
        case 15:
        case 16:
            break;
    }
}

void func_ovl0F_02_80043010(void) {
}
