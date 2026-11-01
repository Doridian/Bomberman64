/*
 * ovl_0F_02's game object, IDO -O3; it matches in us, eu and jp.
 *
 * ovl_0F_04's object (1F2230.c) ported: the same functions in the same
 * order, its statics, fakes, pads and `#line`s, with this overlay's
 * names, constants and handler. Its header has the reasons for each; what
 * follows is what is different here. Every function and stub comes out in
 * the original's place (scratch/0F_02/q1_map2.py in the main checkout).
 *
 * The order is ovl_0F_04's: the handler (func_ovl0F_02_800462F8) is
 * defined last but for func_ovl0F_02_80043010 and so compiled first, its
 * direct callees out first, then what it only takes the address of. The
 * fake is the `if (0)` address list in the empty static
 * func_ovl0F_02_80046170 (ovl_0F_04's 800460B4), every address-taken
 * function in descending address order; 80043404 takes the place of
 * ovl_0F_04's 80043530.
 *
 * Where ovl_0F_04 differs:
 * - Its 800433FC and 80043480 are here 80044C94 and 80044F74, statics not
 *   inlined, defined just before 80044C6C and just after 80045024. Here they
 *   aren't the handler's early callees and come out in definition order.
 *   80044C94's own stub is the empty 80044C8C. 80044C6C's second `jr ra` is
 *   its own, so only that one stub is left before 80044C94 (ovl_0F_04's
 *   80044D24 is gone).
 * - Its 80043530 is here 80046D54, an unreferenced global defined between
 *   80046D9C and 80046D20.
 * - 80043404 (the opening demo, case 4) is a global with three empty
 *   statics, 800433EC/F4/FC. Case 5 still calls 800433EC (as in ovl_0F_04),
 *   or the handler differs by 14 words.
 * - The door's first callback, 80046E78, is an empty static at the end
 *   (ovl_0F_04's 80046CD8 has a body).
 * - The handler's panel statics come out with the door's: 80046150 (ovl_0F_04's
 *   80043578, (n, panels, flags)), _inl4 at 80046158, the door 80046160.
 *   The empty 80046168 and 80046170 are 80046178's.
 * - The handler: case 2 calls 80046178 twice ((5, 6) or (1, 2)) and
 *   80044F74 for D_ovl0F_02_800489C4 itself; cases 18 and 20, the
 *   D_ovl0F_02_80048954 tests in cases 4 and 1 and case 3's
 *   D_ovl0F_02_80048B08 store are new. Its `switch` doesn't list the empty
 *   cases 6 to 16 (ovl_0F_04's does). With them listed the handler's loop
 *   pointers lose s5 and are spilled (595 words). Deleting about three
 *   cases' worth of code anywhere in the handler had the same effect, so the
 *   cause looks like a size limit in uopt's allocation. 80046150 has no pad
 *   (ovl_0F_04's 80043578 has pad[1]; with it the frame is 8 bytes bigger).
 *
 * There are no VERSION conditionals, as in ovl_0F_04's.
 * 800454E8 and its static 800454E0 are ovl_0F_04's 8004544C/80045444
 * renamed, nothing else changed.
 */
#include "common.h"
static void func_ovl0F_02_8004393C(void);
static void func_ovl0F_02_80043D64(void);
static void func_ovl0F_02_80043D5C(void);
static void func_ovl0F_02_80043D54(void);
static void func_ovl0F_02_80043D4C(void);
static void func_ovl0F_02_80043D44(void);
static void func_ovl0F_02_80043018(void);
static void func_ovl0F_02_80044C8C(void);
static void func_ovl0F_02_80044D18(s32 idx);
static void func_ovl0F_02_8004331C(void);
static void func_ovl0F_02_80043314(void);
static void func_ovl0F_02_8004330C(void);
static void func_ovl0F_02_80043304(void);
static void func_ovl0F_02_80045F14(void);
static void func_ovl0F_02_80045F1C(UnkStructA **arg0);

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
    /* 0x12 */ u16 unk12; /* step */
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
    /* 0x18 */ u16 (*unk18)[2];
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ void (*unk20)(s32, s32);
} UnkStruct_ovl0F_02_80048F20; /* 0x24, but the original's .bss (0x240) ends at 0x20: unk20 is past it */

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
void func_ovl0F_02_80048308(s16, f32, f32, f32);

static void func_ovl0F_02_80043324(s32 n, char *msg);
static void func_ovl0F_02_80046E10(void);
static void func_ovl0F_02_80046E18(void);
static void func_ovl0F_02_80046E20(void);
static void func_ovl0F_02_80046E28(void);
static void func_ovl0F_02_80046E30(void);
static void func_ovl0F_02_80046E38(void);
static void func_ovl0F_02_80046E40(void);
static void func_ovl0F_02_80046E48(void);
static void func_ovl0F_02_80046E50(void);
static void func_ovl0F_02_80046E58(void);
static void func_ovl0F_02_80046E60(void);
static void func_ovl0F_02_80046E68(void);
static void func_ovl0F_02_80046E70(void);
static void func_ovl0F_02_80046E78(void);
static void func_ovl0F_02_80046E80(void);
void func_ovl0F_02_80046DF8(void);
void func_ovl0F_02_80046D9C(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0F_02_80046D20(s32 arg0, UnkStructA *arg1);
static void func_ovl0F_02_80046150(s32 n, UnkStruct_ovl0F_02_80048734 *panels, UnkStruct_ovl0F_02_80048918 *flags);
static void func_ovl0F_02_80046178(s32 n1, s32 n2);
static void func_ovl0F_02_80046160(UnkStruct_ovl0F_02_800489F4 *door);
static void func_ovl0F_02_800462E8(void);
static void func_ovl0F_02_80046168(void);
static void func_ovl0F_02_80046170(void);
void func_ovl0F_02_80045EB0(void);
void func_ovl0F_02_800454E8(s32 arg0, UnkStruct_ovl0F_02_Gfx **arg1);
static void func_ovl0F_02_800454E0(UnkStruct_ovl0F_02_Gfx **gdl);
static void func_ovl0F_02_800453A4(UnkStruct_ovl0F_02_80048D80 *p);
void func_ovl0F_02_8004533C(UnkStructA *obj);
void func_ovl0F_02_80045024(void);
static void func_ovl0F_02_80044E9C(s32 id, f32 *pos, f32 d, f32 h);
void func_ovl0F_02_80044D20(s32 idx, s32 flag);
static f32 func_ovl0F_02_80043FEC_inl0(UnkStruct_ovl0F_02_80048734 *p);
static void func_ovl0F_02_80043FEC_inl1(UnkStruct_ovl0F_02_80048734 *p);
s32 func_ovl0F_02_80044C6C(s32 arg0);
void func_ovl0F_02_80044B28(void);
void func_ovl0F_02_80044824(UnkStructA *arg0);
void func_ovl0F_02_80043FEC(void);
void func_ovl0F_02_800462F8(s32 arg0);
static void func_ovl0F_02_80043D6C(s32 flag);
static void func_ovl0F_02_80043B30(s32 i);
static s32 func_ovl0F_02_80043B28(s32 n, UnkStruct_ovl0F_02_80048734 *panels, UnkStruct_ovl0F_02_80048918 *flags);
void func_ovl0F_02_80043944(void);
void func_ovl0F_02_800438B4(UnkStructA *obj);
void func_ovl0F_02_80043858(UnkStructA *obj);
static void func_ovl0F_02_800436D8(UnkStructA *obj, f32 speed);
static void func_ovl0F_02_800436B8(UnkStructA *obj, f32 speed);
static void func_ovl0F_02_800436C0(UnkStructA *obj, f32 speed);
static void func_ovl0F_02_800436C8(UnkStructA *obj, f32 speed);
static void func_ovl0F_02_800436D0(UnkStructA *obj, f32 speed);
void func_ovl0F_02_80043618(void);
void func_ovl0F_02_800434F8(UnkStructA *arg0);
void func_ovl0F_02_80046D54(f32 arg0);
void func_ovl0F_02_80043404(void);
static void func_ovl0F_02_80044F74(s32 arg1, UnkStruct_ovl0F_02_80048734 *arg0);
static void func_ovl0F_02_80044C94(UnkStruct_ovl0F_02_80048734 *arg0);
static void func_ovl0F_02_800433A0(s32 *arg0);
static void func_ovl0F_02_80045F24(UnkStructA **arg0);
static void func_ovl0F_02_80043028(void);
static void func_ovl0F_02_80043020(s32 count, UnkStruct_ovl0F_02_80048734 *p);
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
u16 D_ovl0F_02_80048614[6][2] = {
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
    { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
    { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
    { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
    { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
    { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
    { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
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
}; /* the scripts' strings, .rodata in this order */ const char D_ovl0F_02_80048B10[] = "MA"; const char D_ovl0F_02_80048B14[] = "MA"; const char D_ovl0F_02_80048B18[] = "WM1 WG1 WSH WAP WDSW WB2"; const char D_ovl0F_02_80048B34[] = "WM1 WG1 WSH WAP WDW WB11 WDNW WB1"; const char D_ovl0F_02_80048B58[] = "M1 ST1 M6 ST1"; const char D_ovl0F_02_80048B68[] = "WM1 WG1 WSH WAP WDNE WB2 WDN WB0"; const char D_ovl0F_02_80048B8C[] = "M2 ST200"; const char D_ovl0F_02_80048B98[] = "WM1 WG1 WSH WAP WDN WB3 WDW WB0"; const char D_ovl0F_02_80048BB8[] = "WM1 WG1 WSH WAP WDW WB5"; const char D_ovl0F_02_80048BD0[] = "M0 M0"; const char D_ovl0F_02_80048BD8[] = "WM1 WG1 WSH WAP WDW WB3 ST10"; const char D_ovl0F_02_80048BF8[] = "WM1 WG1 WSH WAP WDE WB2 ST30";
/* passed to func_ovl0F_02_80047B60 */
u32 D_ovl0F_02_80048AC4[17] = {
    0x14, 1, 1, 0, 0, 0, 0, 0, 0, 0x40900000, 0, 0, 0xBE75C28F, 0, 0, 0, 0,
};
s32 D_ovl0F_02_80048B08[2] = { 0, 0 };


/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0F_02_80046E10(void) {
}

static void func_ovl0F_02_80046E18(void) {
}

static void func_ovl0F_02_80046E20(void) {
}

static void func_ovl0F_02_80046E28(void) {
}

static void func_ovl0F_02_80046E30(void) {
}

static void func_ovl0F_02_80046E38(void) {
}

static void func_ovl0F_02_80046E40(void) {
}

static void func_ovl0F_02_80046E48(void) {
}

static void func_ovl0F_02_80046E50(void) {
}

static void func_ovl0F_02_80046E58(void) {
}

static void func_ovl0F_02_80046E60(void) {
}

static void func_ovl0F_02_80046E68(void) {
}

static void func_ovl0F_02_80046E70(void) {
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
#line 1 "panels.c"
}
#line 564 "1E84A0.c"

void func_ovl0F_02_80046DF8(void) {
    D_ovl0F_02_80048D5C = -1;
    D_ovl0F_02_80048D60 = -1;
}

static void func_ovl0F_02_80046170(void) {
    /* fake: first references in descending address order (the header) */
    if (0) { D_ovl0F_02_80048D44[0] = D_ovl0F_02_80048D58[0] = D_ovl0F_02_80048D64[0] = D_ovl0F_02_80048D78[0] = 0; /* the unused .bss keeps its place */
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80045EB0, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_800454E8, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_8004533C, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80045024, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80044D20, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80044C6C, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80044B28, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80044824, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80043FEC, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80043944, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_800438B4, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80043858, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80043618, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_800434F8, 0);
        func_ovl0F_02_800473C8((void (*)(UnkStructA *)) func_ovl0F_02_80043404, 0);
    }
}

void func_ovl0F_02_80046D9C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_02_80047B28(D_ovl0F_02_80048D68.x, D_ovl0F_02_80048D68.y, D_ovl0F_02_80048D68.z);
    func_ovl0F_02_80047B48(arg0, arg1, arg2);
    func_ovl0F_02_80047E58(180);
}

/* unreferenced in this overlay */
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

/* case 2's: the door, closed or already open */
static void func_ovl0F_02_80046160(UnkStruct_ovl0F_02_800489F4 *door) {
    s32 pad[2];
    if (func_ovl0F_02_800480C0(door->unk0[0].unk28) == 0) {
        func_ovl0F_02_80047E38(func_ovl0F_02_80045024, door, 0, 0, 0x110);
    } else {
        door->unk58();
        door->unk5C();
        door->unk0[1].unk10 -= 1.0f;
        func_ovl0F_02_80044F74(1, &door->unk0[1]);
        *door->unk0[0].unk0 = NULL;
        door->unk0[1].unk10 += 1.0f;
    }
}

/* case 2's: the panels and their tiles; one hides something */
#line 1 "panels.c"
static void func_ovl0F_02_80046150(s32 n, UnkStruct_ovl0F_02_80048734 *panels, UnkStruct_ovl0F_02_80048918 *flags) {
    s32 i;
    UnkStruct_ovl0F_02_80048734 *p;

    p = panels;
#line 1 "panels.c"
    func_ovl0F_02_80044F74(n, panels);
#line 8 "panels.c"
    for (i = 0; i < n; i++) {
        if (p->unk1C == 0.0f) {
            func_ovl0F_02_80047328((s32) p->unkC - 1, (s32) p->unk10,
                                   (s32) p->unk14 - 1, (s32) p->unkC - 1,
                                   (s32) p->unk14, 0x1411);
            func_ovl0F_02_80047328((s32) p->unkC, (s32) p->unk10,
                                   (s32) p->unk14 - 1, (s32) p->unkC,
                                   (s32) p->unk14, 0x141A);
        }
        flags->unk0 = 1;
        flags->unk8 = -1;
        p++;
        flags++;
    }
    D_ovl0F_02_80048918[func_ovl0F_02_80047FF8(n - 1)].unk8 = 3;
}
#line 645 "1E84A0.c"

/* case 2's: the wind, the blocks' callbacks and the particles */
static void func_ovl0F_02_80046178(s32 n1, s32 n2) {
    s32 i;
    UnkStructA *obj;

    func_ovl0F_02_80046170();
    func_ovl0F_02_80046168();
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
    obj = func_ovl0F_02_80047A48(func_ovl0F_02_800454E8, -60);
    D_ovl0F_02_80048F1C = obj;
    obj->unkC |= 0x210;
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

/* case 2's: the stage's tables */
static void func_ovl0F_02_800462E8(void) {
}

static void func_ovl0F_02_80046168(void) {
}

static void func_ovl0F_02_80045F1C(UnkStructA **arg0) {
    D_ovl0F_02_80048F20.unk0 = func_ovl0F_02_80047528(func_ovl0F_02_800474C8());
    D_ovl0F_02_80048F20.unk4 = arg0;
    D_ovl0F_02_80048F20.unkC = 0;
    D_ovl0F_02_80048F20.unk10 = 0;
    D_ovl0F_02_80048F20.unk14 = 0;
    D_ovl0F_02_80048F20.unk16 = -1;
    D_ovl0F_02_80048F20.unk8 = 0.0f;
    D_ovl0F_02_80048610 = 1;
    D_ovl0F_02_80048F20.unk18 = D_ovl0F_02_80048614;
    D_ovl0F_02_80048F20.unk20 = func_ovl0F_02_80044D20;
}

static void func_ovl0F_02_80045F14(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        D_ovl0F_02_80048734[i].unkC = 10.0f;
        D_ovl0F_02_80048734[i].unk14 = 19.0f;
        D_ovl0F_02_80048734[i].unk1C = 90.0f;
    }
}

static void func_ovl0F_02_80045F0C(UnkStruct_ovl0F_02_80048734 *p, s32 count) {
    s32 i;

#line 1 "panels.c"
    for (i = 0; i < count; i++) {
        *p->unk0 = func_ovl0F_02_80047D10(p->unk4, p->unk24 | 0x01000000, 0x30, p->unk8);
        func_ovl0F_02_80044C94(p);
        (*p->unk0)->unk40->unk1C = p->unk18;
        (*p->unk0)->unk40->unk20 = p->unk1C;
        (*p->unk0)->unk40->unk24 = p->unk20;
        p++;
    }
}
#line 700 "1E84A0.c"

/* case 2's: the movers and their script */
static void func_ovl0F_02_80045F24(UnkStructA **arg0) {
    s32 i;

    func_ovl0F_02_80045F1C(arg0);
    func_ovl0F_02_80045F14();
    func_ovl0F_02_80045F0C((UnkStruct_ovl0F_02_80048734 *)&D_ovl0F_02_800486A4[6], 6);
    for (i = 0; i < 6; i++) {
        func_ovl0F_02_80047CE8(func_ovl0F_02_80047D20(*D_ovl0F_02_80048734[i].unk0), 0x02100000);
        D_ovl0F_02_800486A4[i].unk11 = 0;
        D_ovl0F_02_80048F20.unk20(i, 0);
    }
    func_ovl0F_02_80047420(func_ovl0F_02_80044824);
    func_ovl0F_02_80047E38(func_ovl0F_02_80043FEC, NULL, 0, 0, 0x110);
}

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

static void func_ovl0F_02_800454E0(UnkStruct_ovl0F_02_Gfx **gdl) {
    UnkStruct_ovl0F_02_Gfx *g2;
    f32 oldx;
    f32 oldz;
    f32 s;
    s32 i;
    f32 view[3];

    g2 = *gdl;
    oldx = D_ovl0F_02_80048F10.x;
    oldz = D_ovl0F_02_80048F10.z;
    func_ovl0F_02_80047C30(&D_ovl0F_02_80048F10);
    func_ovl0F_02_80047C40(view);
    s = func_ovl0F_02_80047FE8(view[0]);
    D_ovl0F_02_800485E4 = ((D_ovl0F_02_80048F10.x - oldx) * s - func_ovl0F_02_80047FE0(view[0]) * (D_ovl0F_02_80048F10.z - oldz)) * 0.5f;
    s = func_ovl0F_02_80047FE8(view[0]);
    D_ovl0F_02_800485E8 = (func_ovl0F_02_80047FE0(view[0]) * (D_ovl0F_02_80048F10.x - oldx) + (D_ovl0F_02_80048F10.z - oldz) * s) * 0.2f;
    D_ovl0F_02_800485E4 *= 1500.0f / view[2];
    D_ovl0F_02_800485E8 *= 1500.0f / view[2];
    for (i = 0; i < 20; i++) {
        if (func_ovl0F_02_800480C0(0x407) != 0) {
            UnkStruct_ovl0F_02_80048D80 *p = &D_ovl0F_02_80048D80[i];

            { UnkStruct_ovl0F_02_Gfx *g = g2++; g->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL((u32) (p->unk8 + p->unk4 - 1) << 2, 0, 12) | _SHIFTL((u32) (p->unk0 + p->unk8 - 1) << 2, 12, 12); g->w1 = _SHIFTL(0, 24, 3) | _SHIFTL((u32) p->unk4 << 2, 0, 12) | _SHIFTL((u32) p->unk0 << 2, 12, 12); { UnkStruct_ovl0F_02_Gfx *g = g2++; g->w0 = 0xB4000000; g->w1 = 0; } { UnkStruct_ovl0F_02_Gfx *g = g2++; g->w0 = 0xB3000000; g->w1 = _SHIFTL((s32) (16.0f / (p->unk8 - 1) * 1024.0f), 0, 16) | _SHIFTL((s32) (16.0f / (p->unk8 - 1) * 1024.0f), 16, 16); } }
        }
        if (D_ovl0F_02_800485F4 == 0.0f) {
            continue;
        }
        {
            f32 r;
            f32 dx;
            f32 dy;
            f64 drift;

            s = func_ovl0F_02_80047FE8(view[0]);
            r = func_ovl0F_02_80047FF0();
            dx = -D_ovl0F_02_800485E4;
            D_ovl0F_02_80048D80[i].unk0 += dx - r * (dx * 0.25f) + D_ovl0F_02_800485EC * s;
            s = (D_ovl0F_02_800485EC != 0.0f ? 1.0f : 0);
            if (func_ovl0F_02_80047FE0(view[0]) * (s * D_ovl0F_02_800485EC) + D_ovl0F_02_800485F0 < 0.0f) {
                f32 sign = (D_ovl0F_02_800485EC != 0.0f ? 1.0f : 0);

                drift = (func_ovl0F_02_80047FE0(view[0]) * (sign * D_ovl0F_02_800485EC) + D_ovl0F_02_800485F0) * 0.5;
            } else {
                f32 sign = (D_ovl0F_02_800485EC != 0.0f ? 1.0f : 0);

                drift = func_ovl0F_02_80047FE0(view[0]) * (sign * D_ovl0F_02_800485EC) + D_ovl0F_02_800485F0;
            }
            r = func_ovl0F_02_80047FF0();
            dy = D_ovl0F_02_80048D80[i].unkC - D_ovl0F_02_800485E8;
            D_ovl0F_02_80048D80[i].unk4 += dy - r * (dy * 0.6f) + drift;
            D_ovl0F_02_80048D80[i].unk8 -= 0.1f * (D_ovl0F_02_80048D80[i].unk8 * 0.0625f);
            if (340.0f <= D_ovl0F_02_80048D80[i].unk0 || 240.0f <= D_ovl0F_02_80048D80[i].unk4 || D_ovl0F_02_80048D80[i].unk8 <= 3.0f ||
                D_ovl0F_02_80048D80[i].unk10++ >= 240 || D_ovl0F_02_80048D80[i].unk0 < -20.0f || D_ovl0F_02_80048D80[i].unk4 < -10.0f) {
                func_ovl0F_02_800453A4(&D_ovl0F_02_80048D80[i]);
            }
        }
    }
    *gdl = g2;
}

void func_ovl0F_02_800454E8(s32 arg0, UnkStruct_ovl0F_02_Gfx **arg1) {
    UnkStruct_ovl0F_02_Gfx *gfx;
    UnkStruct_ovl0F_02_800485E0 *t;

    gfx = *arg1;
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x00553048; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF279; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBB000001; g->w1 = 0x80008000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0x8000; }
    t = D_ovl0F_02_800485E0;
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xFD100000; g->w1 = t->unk20 + (u32) t; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE8000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF5000100; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF0000000; g->w1 = 0x0703C000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xFD500000; g->w1 = t->unk14 + (u32) t; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF5500000; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF3000000; g->w1 = 0x0703F800; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF5400200; g->w1 = 0; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xF2000000; g->w1 = 0x0003C03C; }
    func_ovl0F_02_800454E0(&gfx);
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0x00080000; }
    { UnkStruct_ovl0F_02_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0; }
    *arg1 = gfx;
}

static void func_ovl0F_02_800453A4(UnkStruct_ovl0F_02_80048D80 *p) {
    f32 r;
    f64 t;

    r = func_ovl0F_02_80047FF0();
    p->unk0 = func_ovl0F_02_80047FF0() * 370.0 - 50.0;
    t = func_ovl0F_02_80047FF0();
    p->unk4 = (D_ovl0F_02_800485EC < 0 ? -D_ovl0F_02_800485EC : D_ovl0F_02_800485EC) * 30.0f * t;
    if (D_ovl0F_02_800485E8 <= 0.0f) {
        p->unk4 += (1.0f - r) * 40.0f;
    } else {
        p->unk4 += func_ovl0F_02_80047FF8(90);
    }
    p->unk10 = 0;
    p->unk8 = r * 12.0f + 4.0f;
    p->unkC = r * r * 5.0f + 0.5f;
}

void func_ovl0F_02_8004533C(UnkStructA *obj) {
    func_ovl0F_02_800436D8(obj, D_ovl0F_02_800485FC * 0.42857143f);
}

void func_ovl0F_02_80045024(void) {
    UnkStruct_ovl0F_02_800489F4 *task;
    UnkStruct_ovl0F_02_80048734 *a;
    UnkStruct_ovl0F_02_80048734 *b;
    f32 pos[3];
    s32 hit;

    task = func_ovl0F_02_80047E60();
    a = task->unk0;
    b = &task->unk0[1];
    func_ovl0F_02_80047348(a->unkC, a->unk10, a->unk14, pos, 0);
    func_ovl0F_02_80044F74(2, a);
    (*a->unk0)->unk34 = 250.0f;
    (*a->unk0)->unkC = 0;
    (*b->unk0)->unkC = 0;
    (*b->unk0)->unk70 = 2.4500003f; /* 0x401CCCCE, one step above 2.45f */
    while (func_ovl0F_02_800480C0(a->unk28) == 0) {
        hit = func_ovl0F_02_80047C98(*a->unk0, 0x40);
        if (hit != 0) {
            if ((hit & 0x2000) || (hit & 0x4000)) {
                func_ovl0F_02_800480B0(a->unk28);
            } else {
                func_ovl0F_02_800483E8(0x26, pos);
            }
        }
        func_ovl0F_02_80047E58(5);
    }
    func_ovl0F_02_800483E8(0x8A, pos);
    func_ovl0F_02_80044E9C(0x14, pos, 250.0f, 120.0f);
    func_ovl0F_02_80047E58(10);
    func_ovl0F_02_80044E9C(0x16, pos, 250.0f, 120.0f);
    func_ovl0F_02_80043020(1, a);
    *a->unk0 = NULL;
    func_ovl0F_02_80047328((s32) b->unkC - 2, (s32) b->unk10, (s32) b->unk14 - 2,
                           (s32) b->unkC + 2, (s32) b->unk14 + 2, 0x1410);
    task->unk58();
    func_ovl0F_02_80047D68(*b->unk0);
    func_ovl0F_02_80047E80();
    do {
        func_ovl0F_02_80047D68(*b->unk0);
        func_ovl0F_02_80047E80();
    } while ((*b->unk0)->unk6C != 0.0f);
    task->unk5C();
    func_ovl0F_02_80047E48();
}

static void func_ovl0F_02_80044F74(s32 arg1, UnkStruct_ovl0F_02_80048734 *arg0) {
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

static void func_ovl0F_02_80044E9C(s32 id, f32 *pos, f32 d, f32 h) {
    func_ovl0F_02_80048288(id, pos[0] + d, pos[1] + h, pos[2] + d, 0);
    func_ovl0F_02_80048288(id, pos[0] + d, pos[1] + h, pos[2] - d, 0);
    func_ovl0F_02_80048288(id, pos[0] - d, pos[1] + h, pos[2] + d, 0);
    func_ovl0F_02_80048288(id, pos[0] - d, pos[1] + h, pos[2] - d, 0);
}

/* its 80044C94 call, inlined into 80044D20 (the stub 80044D18) */

static void func_ovl0F_02_80044D18(s32 idx) {
    func_ovl0F_02_80044C94(&D_ovl0F_02_80048734[idx]);
}

/* the script's command: a mover (re)starts; with flag 0 it stays stopped */
void func_ovl0F_02_80044D20(s32 idx, s32 flag) {
    UnkStruct_ovl0F_02_800486A4 *m;
    UnkStructA *obj;

    /* fake: an empty test of idx keeps it in a0 and spills it and flag at the call (78 to 0) */
    if (!idx) {
    }
    func_ovl0F_02_80044D18(idx);
    m = &D_ovl0F_02_800486A4[idx];
    m->unkC = 0;
    m->unk12 = 0;
    m->unk14 = 1;
    m->unk11 = flag;
    obj = *D_ovl0F_02_80048734[idx].unk0;
    if (flag == 0) {
        func_ovl0F_02_80047CF0(obj, 0x01000070);
    } else {
        func_ovl0F_02_80047CE8(obj, 0x01000070);
    }
    m->unk10 = 0;
    m->unk4 = 1.0f;
    m->unk8 = 0.05f;
    (*D_ovl0F_02_80048734[idx].unk0)->unk40->unk14 = 2200.0f;
    if (flag != 0) {
        (*D_ovl0F_02_80048734[idx].unk0)->unk68 = 20.0f;
        (*D_ovl0F_02_80048734[idx].unk0)->unk6C = 0.0f;
        func_ovl0F_02_80048288(0xC, (*D_ovl0F_02_80048734[idx].unk0)->unk40->unk10, (*D_ovl0F_02_80048734[idx].unk0)->unk40->unk14, (*D_ovl0F_02_80048734[idx].unk0)->unk40->unk18, 0);
    }
}

static f32 func_ovl0F_02_80043FEC_inl0(UnkStruct_ovl0F_02_80048734 *p) {
    f32 tilt;
    f32 slope;

    tilt = 0.0f;
    slope = 0.0f;
    func_ovl0F_02_80047370((*p->unk0)->unk40, &tilt, &slope);
    if (func_ovl0F_02_80047FE0((*p->unk0)->unk40->unk20) >= 0.707f && slope != 0.0f) {
        tilt *= func_ovl0F_02_80047FE0(slope);
    }
    return tilt * 0.6f;
}

static void func_ovl0F_02_80043FEC_inl1(UnkStruct_ovl0F_02_80048734 *p) {
    s32 padP; /* unused: pos at sp+0xA8 */
    f32 pos[3];

    pos[0] = (*p->unk0)->unk40->unk10;
    pos[1] = (*p->unk0)->unk40->unk14;
    pos[2] = (*p->unk0)->unk40->unk18;
    func_ovl0F_02_800483E8(0x168, pos);
    func_ovl0F_02_800483A0(pos);
}

/* the movers' step filter: every direction but 0xF */
static void func_ovl0F_02_80044C8C(void) {
}

static void func_ovl0F_02_80044C94(UnkStruct_ovl0F_02_80048734 *arg0) {
    f32 pos[3];

    func_ovl0F_02_80044C8C();
    func_ovl0F_02_80047348(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

s32 func_ovl0F_02_80044C6C(s32 arg0) {
    if ((arg0 & 0xF) == 0xF) {
        return 0;
    }
    return 1;
}

/* a task: a hit mover's effects */
void func_ovl0F_02_80044B28(void) {
    UnkStruct_ovl0F_02_80048734 *p;
    s32 i;

    p = &D_ovl0F_02_80048734[(s32) func_ovl0F_02_80047E60()];
    for (i = 0; i < 3; i++) {
        func_ovl0F_02_80048288(7, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14 + 100.0f, (*p->unk0)->unk40->unk18, 0);
        func_ovl0F_02_80047E58(3);
    }
    for (i = 0; i < 5; i++) {
        func_ovl0F_02_80048288(0x18, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14 + 100.0f, (*p->unk0)->unk40->unk18, 0);
        func_ovl0F_02_80047E58(3);
    }
    func_ovl0F_02_80048288(0x16, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14 + 100.0f, (*p->unk0)->unk40->unk18, 0);
    func_ovl0F_02_80047E48();
}

/* the player's callback when a mover throws it */
void func_ovl0F_02_80044824(UnkStructA *arg0) {
    s32 dir;
    f32 speed;
    f32 dy;
    s32 i;

    dir = 0;
    speed = 0.0f;
    i = 0;
    func_ovl0F_02_800483C0(0x1E);
    if (D_ovl0F_02_80048F20.unk16 != -1) {
        dir = D_ovl0F_02_800486A4[D_ovl0F_02_80048F20.unk16].unk0;
        speed = D_ovl0F_02_800486A4[D_ovl0F_02_80048F20.unk16].unk4 * 0.8f;
    }
    func_ovl0F_02_80047A10(arg0->unk40, 0x11, 0);
    func_ovl0F_02_80047A40(arg0->unk40, 4, 0xC);
    func_ovl0F_02_80047A40(arg0->unk40, 5, 0xD);
    func_ovl0F_02_80048288(0, arg0->unk40->unk10, arg0->unk40->unk14 + 100.0f, arg0->unk40->unk18, 0);
    arg0->unk68 = 30;
    arg0->unk70 = 1.6333334f;
    while (i++ <= 200 && arg0->unk68 > 0.0f && !((arg0->unk40->unk14 <= func_ovl0F_02_80047310()) ? TRUE : FALSE)) {
        dy = func_ovl0F_02_80047FE8(arg0->unk40->unk1C) * 30.0f;
        func_ovl0F_02_80048330(arg0, dir, speed, func_ovl0F_02_80044C6C);
        arg0->unk40->unk1C += 10.0f;
        arg0->unk40->unk10 -= func_ovl0F_02_80047FE0(arg0->unk40->unk1C);
        if (dy > 0.0f) {
            dy = 0.0f;
        }
        arg0->unk40->unk14 -= dy;
        func_ovl0F_02_80047E80();
    }
    if ((arg0->unk40->unk14 <= func_ovl0F_02_80047310()) ? TRUE : FALSE) {
        func_ovl0F_02_800434F8(arg0);
    } else {
        arg0->unk6C = 0.0f;
        arg0->unk70 = 0.0f;
    }
    func_ovl0F_02_80047E58(0x50);
}

/* a task: the movers, until the script ends and all have stopped */
void func_ovl0F_02_80043FEC(void) {
    s32 active;
    s32 i;
    UnkStruct_ovl0F_02_800486A4 *st; /* unused, as rec, step and player: with fewer, unk16's store addresses the symbol (2 words) */
    UnkStruct_ovl0F_02_80048734 *rec;
    UnkStruct_ovl0F_02_8004862C *step;
    UnkStructA *obj;
    UnkStructA *player;
    s32 hit;
    s32 j; /* fake: a copy of i for the loop's body (from the permuter; it puts i in s0 and
            * the record in s2), but for the store to D_ovl0F_02_80048F20.unk16 */
    f32 padA[2]; /* unused: the frame (0x100) and tilt/slope at sp+0xC4/0xC0 */
    f32 z; /* fake: the mover's x, so the x compares get f0 and f2 as in the original */

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
        for (i = 0; i != 6; i++) {
            j = i;
            if (D_ovl0F_02_800486A4[j].unk11 == 1) {
                func_ovl0F_02_80047DF8((*D_ovl0F_02_80048734[j].unk0));
                if (D_ovl0F_02_80048F20.unk0->unk40->unk10 <= (z = (*D_ovl0F_02_80048734[j].unk0)->unk40->unk10) + 300.0f &&
                    z - 300.0f <= D_ovl0F_02_80048F20.unk0->unk40->unk10 &&
                    D_ovl0F_02_80048F20.unk0->unk40->unk18 <= (*D_ovl0F_02_80048734[j].unk0)->unk40->unk18 + 300.0f &&
                    (*D_ovl0F_02_80048734[j].unk0)->unk40->unk18 - 300.0f <= D_ovl0F_02_80048F20.unk0->unk40->unk18) {
                    if (D_ovl0F_02_800486A4[j].unk14 != 0) {
                        func_ovl0F_02_800483C0(0x87);
                        D_ovl0F_02_800486A4[j].unk14 = 0;
                    }
                } else if (D_ovl0F_02_800486A4[j].unk14 == 0) {
                    D_ovl0F_02_800486A4[j].unk14 = 1;
                }
                if ((*D_ovl0F_02_80048734[j].unk0)->unk6C == 0.0f) {
                    if (D_ovl0F_02_800486A4[j].unkC >= D_ovl0F_02_8004862C[D_ovl0F_02_800486A4[j].unk10][D_ovl0F_02_800486A4[j].unk12].unk0) {
                        if (D_ovl0F_02_80048734[j].unk1C == 90.0f) {
                            D_ovl0F_02_800486A4[j].unkC = 0;
                            D_ovl0F_02_800486A4[j].unk0 = D_ovl0F_02_8004862C[D_ovl0F_02_800486A4[j].unk10][D_ovl0F_02_800486A4[j].unk12].unk2;
                            D_ovl0F_02_800486A4[j].unk8 = D_ovl0F_02_8004862C[D_ovl0F_02_800486A4[j].unk10][D_ovl0F_02_800486A4[j].unk12].unk4;
                            D_ovl0F_02_800486A4[j].unk12 = D_ovl0F_02_8004862C[D_ovl0F_02_800486A4[j].unk10][D_ovl0F_02_800486A4[j].unk12].unk3;
                        } else if (D_ovl0F_02_80048734[j].unk1C == 270.0f) {
                            D_ovl0F_02_800486A4[j].unk0 = (D_ovl0F_02_8004862C[D_ovl0F_02_800486A4[j].unk10][D_ovl0F_02_800486A4[j].unk12].unk2 + 0x80) & 0xFF;
                            D_ovl0F_02_800486A4[j].unkC = 0;
                            D_ovl0F_02_800486A4[j].unk8 = D_ovl0F_02_8004862C[D_ovl0F_02_800486A4[j].unk10][D_ovl0F_02_800486A4[j].unk12].unk4;
                            D_ovl0F_02_800486A4[j].unk12 = D_ovl0F_02_8004862C[D_ovl0F_02_800486A4[j].unk10][D_ovl0F_02_800486A4[j].unk12].unk3;
                        }
                    }
                }
                D_ovl0F_02_800486A4[j].unkC++;
                func_ovl0F_02_80043B30(j);
                func_ovl0F_02_80048330((*D_ovl0F_02_80048734[j].unk0), D_ovl0F_02_800486A4[j].unk0, D_ovl0F_02_800486A4[j].unk4, func_ovl0F_02_80044C6C);
                (*D_ovl0F_02_80048734[j].unk0)->unk40->unk1C = func_ovl0F_02_80043FEC_inl0(&D_ovl0F_02_80048734[j]);
                if (((*D_ovl0F_02_80048734[j].unk0)->unk40->unk14 <= func_ovl0F_02_80047310()) ? TRUE : FALSE) {
                    D_ovl0F_02_80048F20.unk20(j, 0);
                    continue;
                }
                hit = func_ovl0F_02_80047C98((*D_ovl0F_02_80048734[j].unk0), 0x40);
                if (hit != 0 && ((hit & 0x2000) || (hit & 0x4000))) {
                    func_ovl0F_02_80043FEC_inl1(&D_ovl0F_02_80048734[j]);
                    (*D_ovl0F_02_80048734[j].unk0)->unk68 = 20.0f;
                    (*D_ovl0F_02_80048734[j].unk0)->unk70 = 0.8166667f;
                    D_ovl0F_02_800486A4[j].unk11 = 2;
                    func_ovl0F_02_80047E38(func_ovl0F_02_80044B28, (void *) j, 0, 0, 0x150);
                }
                if (func_ovl0F_02_80047CB0(D_ovl0F_02_80048F20.unk0, (*D_ovl0F_02_80048734[j].unk0)) != 0) {
                    D_ovl0F_02_80048F20.unk16 = i;
                }
                D_ovl0F_02_800486A4[j].unk4 += D_ovl0F_02_800486A4[j].unk8;
            } else if (D_ovl0F_02_800486A4[j].unk11 == 2) {
                if ((*D_ovl0F_02_80048734[j].unk0)->unk68 == 0.0f && (*D_ovl0F_02_80048734[j].unk0)->unk6C == 0.0f) {
                    D_ovl0F_02_80048F20.unk20(j, 0);
                    continue;
                }
                if ((*D_ovl0F_02_80048734[j].unk0)->unk40->unk1C < 180.0f) {
                    (*D_ovl0F_02_80048734[j].unk0)->unk40->unk1C += 5.0f;
                }
                func_ovl0F_02_80048330((*D_ovl0F_02_80048734[j].unk0), D_ovl0F_02_800486A4[j].unk0, D_ovl0F_02_800486A4[j].unk4, func_ovl0F_02_80044C6C);
                func_ovl0F_02_80047D68((*D_ovl0F_02_80048734[j].unk0));
                if (((*D_ovl0F_02_80048734[j].unk0)->unk40->unk14 <= func_ovl0F_02_80047310()) ? TRUE : FALSE) {
                    D_ovl0F_02_80048F20.unk20(j, 0);
                }
            }
        }
        if (D_ovl0F_02_80048610 == 0) {
            active = FALSE;
            for (j = 0; j < 6; j++) {
                if (D_ovl0F_02_800486A4[j].unk11 != 0) {
                    active = TRUE;
                }
            }
        }
        func_ovl0F_02_80047E80();
    } while (active);
    func_ovl0F_02_80043020(6, D_ovl0F_02_80048734);
    func_ovl0F_02_80047E48();
}

static void func_ovl0F_02_80043D64(void) {
}

static void func_ovl0F_02_80043D5C(void) {
}

static void func_ovl0F_02_80043D54(void) {
}

static void func_ovl0F_02_80043D4C(void) {
}

static void func_ovl0F_02_80043D44(void) {
}

/* one step of the movers' script */
static void func_ovl0F_02_80043D6C(s32 flag) {
    u16 *e;
    u16 cmd;
    s32 kind;
    s32 arg;

    func_ovl0F_02_80043D64();
    func_ovl0F_02_80043D5C();
    func_ovl0F_02_80043D54();
    func_ovl0F_02_80043D4C();
    func_ovl0F_02_80043D44();
    e = D_ovl0F_02_80048F20.unk18[D_ovl0F_02_80048F20.unk14];
    if (e[0] == D_ovl0F_02_80048F20.unk10++) {
        if (e[1] != 100) {
            if (flag) {
                cmd = e[1];
                switch (cmd) {
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
                        if (D_ovl0F_02_800486A4[arg].unk11 == 0) {
                            D_ovl0F_02_80048F20.unk20(arg, 1);
                        }
                        break;
                    case 10:
                        switch (arg) {
                            case 1:
                                if (*D_ovl0F_02_80048F20.unk4 != NULL) {
                                    func_ovl0F_02_800483E0(0x8C, (*D_ovl0F_02_80048F20.unk4)->unk40->unk10, (*D_ovl0F_02_80048F20.unk4)->unk40->unk14,
                                                           (*D_ovl0F_02_80048F20.unk4)->unk40->unk18);
                                }
                                if (D_ovl0F_02_80048F20.unkC == 0) {
                                    D_ovl0F_02_80048F20.unkC = 1;
                                    D_ovl0F_02_80048F20.unk8 = 0.0f;
                                }
                                break;
                            case 2:
                                if (D_ovl0F_02_80048F20.unkC == 0) {
                                    D_ovl0F_02_80048F20.unkC = 2;
                                    if (*D_ovl0F_02_80048F20.unk4 != NULL) {
                                        D_ovl0F_02_80048F20.unk8 = func_ovl0F_02_80047A28((*D_ovl0F_02_80048F20.unk4)->unk40, 0) - 0.001f;
                                    }
                                }
                                break;
                        }
                        break;
                }
            }
            D_ovl0F_02_80048F20.unk14++;
        } else {
            D_ovl0F_02_80048F20.unk10 = 0;
            D_ovl0F_02_80048F20.unk14 = 0;
        }
    }
}

/* a mover turns towards its direction, a tenth of the way (at least 1) a frame */
static void func_ovl0F_02_80043B30(s32 i) {
    f32 target;
    f32 d;
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
        case 0x80:
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
    if (target < (*D_ovl0F_02_80048734[i].unk0)->unk40->unk20) {
        d = ((*D_ovl0F_02_80048734[i].unk0)->unk40->unk20 - target) * 0.1f;
        if (d > 1.0f) {
            (*D_ovl0F_02_80048734[i].unk0)->unk40->unk20 -= d;
        } else {
            (*D_ovl0F_02_80048734[i].unk0)->unk40->unk20 -= 1.0f;
        }
        if ((*D_ovl0F_02_80048734[i].unk0)->unk40->unk20 < target) {
            (*D_ovl0F_02_80048734[i].unk0)->unk40->unk20 = target;
        }
    } else if ((*D_ovl0F_02_80048734[i].unk0)->unk40->unk20 < target) {
        d = (target - (*D_ovl0F_02_80048734[i].unk0)->unk40->unk20) * 0.1f;
        if (d > 1.0f) {
            (*D_ovl0F_02_80048734[i].unk0)->unk40->unk20 += d;
        } else {
            (*D_ovl0F_02_80048734[i].unk0)->unk40->unk20 += 1.0f;
        }
        if (target < (*D_ovl0F_02_80048734[i].unk0)->unk40->unk20) {
            (*D_ovl0F_02_80048734[i].unk0)->unk40->unk20 = target;
        }
    }
}

/* case 0x52's: the panel the player stands on, if it is still up */
#line 1 "panels.c"
static s32 func_ovl0F_02_80043B28(s32 n, UnkStruct_ovl0F_02_80048734 *panels, UnkStruct_ovl0F_02_80048918 *flags) {
    s32 i;
    UnkStruct_ovl0F_02_80048734 *p;

    i = 0;
    for (p = panels; i < n; i++) {
        if (flags->unk0 != 0 && p->unk1C == 0.0f &&
            func_ovl0F_02_800474B0((s32) p->unkC - 1, (s32) p->unk14 - 1,
                                   (s32) p->unkC, (s32) p->unk14) != 0) {
            return i;
        }
        p++;
        flags++;
    }
    return -1;
}
#line 1362 "1E84A0.c"

static void func_ovl0F_02_8004393C(void) {
}

/* a task: a panel is stepped on and its block drops */
#line 1376 "1E84A0.c"
void func_ovl0F_02_80043944(void) {
#line 1368 "1E84A0.c"
    s32 i;
    UnkStructA *obj;
    s32 k;

    func_ovl0F_02_8004393C();
    i = D_ovl0F_02_80048D74;
    if (D_ovl0F_02_8004883C[i].unk1C == 0.0f) {
        func_ovl0F_02_80047328((s32) D_ovl0F_02_8004883C[i].unkC - 1, (s32) D_ovl0F_02_8004883C[i].unk10,
                               (s32) D_ovl0F_02_8004883C[i].unk14 - 1, (s32) D_ovl0F_02_8004883C[i].unkC,
                               (s32) D_ovl0F_02_8004883C[i].unk14, D_ovl0F_02_80048918[i].unk4);
    }
    D_ovl0F_02_80048918[i].unk0 = 0;
    k = D_ovl0F_02_80048918[(u32) i].unk8;
    obj = D_ovl0F_02_80048D18[i];
    do {
        func_ovl0F_02_80047D68(obj);
        func_ovl0F_02_80047E80();
    } while (obj->unk6C != 0.0f);
    func_ovl0F_02_80048288(0x10, obj->unk40->unk10, obj->unk40->unk14 + 200.0f, obj->unk40->unk18, 0);
    if (k == -1) {
        k = 7;
    }
    func_ovl0F_02_80048308(k, obj->unk40->unk10, obj->unk40->unk14 + 50.0f, obj->unk40->unk18);
    func_ovl0F_02_80047CF0(obj, 0x01000000);
    func_ovl0F_02_80047E48();
}

/* the pushed blocks' callbacks */
void func_ovl0F_02_800438B4(UnkStructA *obj) {
    if (obj->unk8 & 1) {
        func_ovl0F_02_800473E0(0x58, 0x15, 2);
    }
    func_ovl0F_02_800436D8(obj, D_ovl0F_02_800485FC);
}

void func_ovl0F_02_80043858(UnkStructA *obj) {
    func_ovl0F_02_800436D8(obj, D_ovl0F_02_800485FC);
}

/* the wind pushes a block along x unless it is stopped */
static void func_ovl0F_02_800436D8(UnkStructA *obj, f32 speed) {
    f32 pos[3];
    s32 dir;
    s32 saved;
    s32 hit;
    UnkStructA *other;
    s32 k;

#line 1 "panels.c"
    pos[0] = obj->unk40->unk10;
    pos[1] = obj->unk40->unk14;
    pos[2] = obj->unk40->unk18;
    dir = 0x40;
    if (func_ovl0F_02_800473A8(obj->unk40) == obj->unk40->unk14) {
        func_ovl0F_02_80048338(obj, dir, speed);
    } else {
        switch (dir) {
            case 0x00:
                func_ovl0F_02_800436D0(obj, speed);
                break;
            case 0x40:
                func_ovl0F_02_800436C8(obj, speed);
                break;
            case 0x80:
                func_ovl0F_02_800436C0(obj, speed);
                break;
            case 0xC0:
                func_ovl0F_02_800436B8(obj, speed);
                break;
        }
    }
#line 1434 "1E84A0.c"
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
        obj->unk40->unk10 = pos[0];
        obj->unk40->unk14 = pos[1];
        obj->unk40->unk18 = pos[2];
    }
}

static void func_ovl0F_02_800436B8(UnkStructA *obj, f32 speed) {
    obj->unk40->unk10 -= speed;
}

static void func_ovl0F_02_800436C0(UnkStructA *obj, f32 speed) {
    obj->unk40->unk18 += speed;
}

static void func_ovl0F_02_800436C8(UnkStructA *obj, f32 speed) {
    obj->unk40->unk10 += speed;
}

static void func_ovl0F_02_800436D0(UnkStructA *obj, f32 speed) {
    obj->unk40->unk18 -= speed;
}

/* a task: the camera waits for the player to pass x 1200 */
void func_ovl0F_02_80043618(void) {
    UnkStructA *obj;

    obj = func_ovl0F_02_80047528(func_ovl0F_02_800474C8());
    while (1200.0f < obj->unk40->unk10) {
        func_ovl0F_02_80047E80();
    }
    func_ovl0F_02_80047E58(30);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048B14);
    func_ovl0F_02_80047E48();
}


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






static void func_ovl0F_02_800433EC(void) {
}

static void func_ovl0F_02_800433FC(void) {
}

static void func_ovl0F_02_800433F4(void) {
}

void func_ovl0F_02_80043404(void) {
    func_ovl0F_02_800433EC();
    func_ovl0F_02_800433FC();
    func_ovl0F_02_800433F4();
    D_ovl0F_02_80048B08[0] = 0;
    func_ovl0F_02_800474D8(1);
    while (D_ovl0F_02_80048B08[0] == 0) {
        func_ovl0F_02_80047E80();
    }
    func_ovl0F_02_80047450(0);
    func_ovl0F_02_80047588(1);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048B18);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048B34);
    func_ovl0F_02_80047B60(D_ovl0F_02_80048AC4, 0x170, 0);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048B58);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048B68);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048B8C);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048B98);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048BB8);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048BD0);
    func_ovl0F_02_80047E58(60);
    func_ovl0F_02_80048538();
    func_ovl0F_02_80047E48();
}

static void func_ovl0F_02_800433A0(s32 *arg0) {
    if (func_ovl0F_02_800474B0(arg0[0], arg0[1], arg0[2], arg0[3]) != 0) {
        func_ovl0F_02_800473E0(arg0[4], arg0[5], arg0[6]);
    }
}

static void func_ovl0F_02_8004331C(void) {
}

static void func_ovl0F_02_80043314(void) {
}

static void func_ovl0F_02_8004330C(void) {
}

static void func_ovl0F_02_80043304(void) {
}

/* the switches' cut-scene: a task counts n frames while a message shows */
static void func_ovl0F_02_80043324(s32 n, char *msg) {
    func_ovl0F_02_8004331C();
    func_ovl0F_02_80043314();
    func_ovl0F_02_8004330C();
    func_ovl0F_02_80043304();
    func_ovl0F_02_80047588(1);
    func_ovl0F_02_800482C8();
    func_ovl0F_02_80047E38(func_ovl0F_02_80045EB0, (void *) n, 0, 0, 0x130);
    func_ovl0F_02_800474F0(msg);
    func_ovl0F_02_80047588(0);
    func_ovl0F_02_800474F0(D_ovl0F_02_80048B10);
}

static void func_ovl0F_02_80043018(void) {
}

/* the wind: it blows one way from frame 160 to 460, the other from 540 to
 * 720, and the fog moves with it */
static f32 func_ovl0F_02_80043028_inl1(s32 t) {
    f32 d;

    d = 0.0f;
    if (t >= 160) {
        if (t < 460) {
            d = D_ovl0F_02_80048600 / 300.0f;
        } else if (t >= 540 && t < 720) {
            d = -(D_ovl0F_02_80048600 / 180.0f);
        }
    }
    return d;
}

static void func_ovl0F_02_80043028(void) {
    s32 t;
    f32 d;
    f32 a;
    f32 b;

    a = 300.0f;
    b = 180.0f;

    func_ovl0F_02_80043018();
    t = D_ovl0F_02_800485F8;
    if (t >= 160) {
        if (t < 460) {
            D_ovl0F_02_80048604 += -20.0f / a;
            D_ovl0F_02_80048608 += -10.0f / a;
            func_ovl0F_02_80048178(D_ovl0F_02_80048604, D_ovl0F_02_80048608, 0xE6, 0xF0, 0xFF);
        } else if (t >= 540 && t < 720) {
            D_ovl0F_02_80048604 -= -20.0f / b;
            D_ovl0F_02_80048608 -= -10.0f / b;
            func_ovl0F_02_80048178(D_ovl0F_02_80048604, D_ovl0F_02_80048608, 0xE6, 0xF0, 0xFF);
        }
    }
    D_ovl0F_02_800485F8++;
    if (D_ovl0F_02_800485F8 >= 720) {
        D_ovl0F_02_800485F8 = 0;
        t = 0;
    } else {
        t = D_ovl0F_02_800485F8;
    }
    d = func_ovl0F_02_80043028_inl1(t);
    D_ovl0F_02_800485FC += d;
    if (2.0f <= D_ovl0F_02_800485FC && D_ovl0F_02_8004860C == 1) {
        D_ovl0F_02_8004860C = 0;
        func_ovl0F_02_800483C0(0x89);
    } else if (D_ovl0F_02_800485FC < 2.0f) {
        D_ovl0F_02_8004860C = 1;
    }
    d = D_ovl0F_02_800485FC * 0.5f;
    D_ovl0F_02_800485EC = d;
    if (D_ovl0F_02_800485FC) {
    }
    D_ovl0F_02_800485F0 = 0.0f;
}

#line 1 "panels.c"
static void func_ovl0F_02_80043020(s32 count, UnkStruct_ovl0F_02_80048734 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_02_80047D00(*p->unk0);
        p++;
    }
}
#line 1654 "1E84A0.c"

static void func_ovl0F_02_800462F8_inl1(void) {
    s32 pad[8];

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
        func_ovl0F_02_80043324(60, D_ovl0F_02_80048BD8);
    }
}

static void func_ovl0F_02_800462F8_inl2(void) {
    s32 pad[3];
    if (func_ovl0F_02_800480C0(0x406) != 0) {
        func_ovl0F_02_80047DC8(40.0f);
        func_ovl0F_02_80047DD0(30);
        func_ovl0F_02_800480B8(0x406);
        func_ovl0F_02_800480B0(0x407);
        func_ovl0F_02_80047B88(0x1F);
        func_ovl0F_02_80047B18(1);
        func_ovl0F_02_80047C50();
        func_ovl0F_02_80047C18(D_ovl0F_02_80048D38);
        func_ovl0F_02_80043324(60, D_ovl0F_02_80048BF8);
    }
}

#line 1 "panels.c"
static void func_ovl0F_02_800462F8_inl0(u32 (*p)[3], s32 count) {
    s32 i;

    func_ovl0F_02_800462E8();
    for (i = 0; i < count; i++) {
        func_ovl0F_02_80048348((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}
#line 1701 "1E84A0.c"

#line 1 "panels.c"
static void func_ovl0F_02_800462F8_inl4(void) {
    func_ovl0F_02_80046150(5, D_ovl0F_02_8004883C, D_ovl0F_02_80048918);
}
#line 1707 "1E84A0.c"



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
            func_ovl0F_02_800462F8_inl0(D_ovl0F_02_8004897C, 6);
            func_ovl0F_02_800472E8(0x224);
            func_ovl0F_02_80047300(0x238);
            func_ovl0F_02_80047498();
            if (D_ovl0F_02_80048954 == 0) {
                func_ovl0F_02_80046178(5, 6);
            } else {
                func_ovl0F_02_80046178(1, 2);
            }
            func_ovl0F_02_80044F74(1, &D_ovl0F_02_800489C4);
            func_ovl0F_02_80046160(&D_ovl0F_02_800489F4);
            func_ovl0F_02_800462F8_inl4();
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
            func_ovl0F_02_800433EC();
            switch (func_ovl0F_02_800473E8()) {
                case 0x11:
                    func_ovl0F_02_800474E8(D_ovl0F_02_80048A8C[0].unk0, D_ovl0F_02_80048A8C[0].unk4,
                                           D_ovl0F_02_80048A8C[0].unk8, D_ovl0F_02_80048A8C[0].unkC,
                                           D_ovl0F_02_80048A8C[0].unk10, D_ovl0F_02_80048A8C[0].unk14,
                                           D_ovl0F_02_80048A8C[0].unk18);
                    break;
                case 0x13:
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
                func_ovl0F_02_800462F8_inl1();
            } else {
#line 6 "panels.c"
                i = func_ovl0F_02_80043B28(5, D_ovl0F_02_8004883C, D_ovl0F_02_80048918);
                if (i != -1) {
                    D_ovl0F_02_80048D74 = i;
                    func_ovl0F_02_80047E38(func_ovl0F_02_80043944, NULL, 0, 0, 0x110);
                }
#line 1790 "1E84A0.c"
            }
            break;
        case 0x53:
            if (func_ovl0F_02_800474B0(0x13, 0xA, 0x13, 0xA) != 0) {
                func_ovl0F_02_800462F8_inl2();
            }
            break;
        case 1:
            func_ovl0F_02_800479D8(D_ovl0F_02_80048F1C);
            func_ovl0F_02_800479C0(0x258);
#line 1 "panels.c"
            func_ovl0F_02_80043020(5, D_ovl0F_02_8004883C);
            func_ovl0F_02_80043020(1, &D_ovl0F_02_800489C4);
            if (func_ovl0F_02_800480C0(D_ovl0F_02_800489F4.unk0[0].unk28) == 0) {
                func_ovl0F_02_80043020(2, D_ovl0F_02_800489F4.unk0);
            } else {
                func_ovl0F_02_80043020(1, &D_ovl0F_02_800489F4.unk0[1]);
            }
            *D_ovl0F_02_800489F4.unk0[0].unk0 = NULL;
#line 1800 "1E84A0.c"
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
    }
}

void func_ovl0F_02_80043010(void) {
}
