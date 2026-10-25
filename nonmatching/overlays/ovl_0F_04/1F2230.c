/*
 * NON_MATCHING: ovl_0F_04's game object, complete: every function and its
 * data (.data and .bss as the original's sizes).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 4362, jp 4362
 *
 * A first complete draft: the functions are right, the layout is not yet.
 * What still differs in us (words, by tools/nonmatching.py's ranges, which
 * take in the statics after each global):
 * - The order. Defined in about the reverse of the original's addresses,
 *   with the handler just below func_ovl0F_04_80044084 (so compiled before
 *   it) and func_ovl0F_04_80043324 static at the top (compiled last), the
 *   address-taken functions come out as the original's but for three
 *   places: 80043324 after 800439DC (the original: after 80043028),
 *   80044D34 before 80044BC0/80044D04, and 8004544C before 800452A0.
 *   What decides it (probes in scratch/ovl_0F_04/ord/): compiling an
 *   address-taken function that itself takes addresses (80044084) first
 *   emits every address-taken function not yet out, in the reverse of the
 *   order of their first references in the source, then itself; so in
 *   plain reverse address order 80045E14, 80044BC0, 80044D04, 800448BC,
 *   80044D34, 8004544C, 800452A0 and 80044F88 come out at 80044084's turn.
 *   No definition order gives the original's 80044084..80045E14 run from
 *   that (800460CC's references put 8004544C before 800452A0), so the
 *   original's mechanism is still open.
 * - func_ovl0F_04_80043028 (the wind): 161 words, the original 181 (it
 *   keeps &D_ovl0F_04_80048488 in s0, which the handler saves).
 * - func_ovl0F_04_80043770 (the pushed blocks): 82 words, the original 96.
 * - func_ovl0F_04_800460CC's second argument: the handler passes an `s1`
 *   it never sets (the count func_ovl0F_04_80047258 gets for
 *   func_ovl0F_04_800452A0); here both are 5.
 * - func_ovl0F_04_80043E04 takes its flag in a3 in the original: three
 *   unused parameters before it (here the script and two zeros).
 * - 80046BC8, 80046BFC, 80045E14 and 800436B0 match.
 */
#include "common.h"

/*
 * ovl_0F_04's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). ovl_0F_03 (1EE1A0) shares
 * its door, its particles and the handler's shape; ovl_17_09 (2B8D20) its
 * pushed blocks. The statics IDO inlines everywhere are named for the empty
 * stubs they leave.
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
} UnkStruct_ovl0F_04_800485C4; /* size 0x2C */

/* the door func_ovl0F_04_80044F88 runs as a task: two models and what to
 * call once it is open */
typedef struct {
    /* 0x00 */ UnkStruct_ovl0F_04_800485C4 unk0[2];
    /* 0x58 */ void (*unk58)(void);
    /* 0x5C */ void (*unk5C)(void);
} UnkStruct_ovl0F_04_80048880; /* size 0x60 */

/* seven arguments of func_ovl0F_04_80047378 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0F_04_80048918; /* size 0x1C */

/* a panel's tile and what it is set to */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_ovl0F_04_800487A8; /* size 0xC */

/* one step of a mover's route (D_ovl0F_04_800484BC) */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
} UnkStruct_ovl0F_04_800484BC; /* size 0x8 */

/* a mover (D_ovl0F_04_80048534): direction, speed, acceleration, route */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ s32 unk14;
} UnkStruct_ovl0F_04_80048534; /* size 0x18 */

/* the movers' script (D_ovl0F_04_80048C90) */
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
} UnkStruct_ovl0F_04_80048C90; /* size 0x24 */

/* one of the particles func_ovl0F_04_8004544C draws (D_ovl0F_04_80048AF0) */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0F_04_80048AF0; /* size 0x14 */

/* what func_ovl0F_04_80047848 returns: offsets into itself */
typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18[8];
    /* 0x20 */ s32 unk20;
} UnkStruct_ovl0F_04_80048470;

/* what func_ovl0F_04_800472C8 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0F_04_800472C8;

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_ovl0F_04_Gfx; /* size 0x8 */

/* gbi.h's _SHIFTL */
#define _SHIFTL(v, s, w) ((u32) (((u32) (v) & ((0x01 << (w)) - 1)) << (s)))

f32 func_ovl0F_04_80047238(UnkStructA_40 *);
f32 func_ovl0F_04_80047E70(f32);
f32 func_ovl0F_04_80047E78(f32);
f64 func_ovl0F_04_80047E80(void);
s32 func_ovl0F_04_80047278(void);
s32 func_ovl0F_04_80047340(s32, s32, s32, s32);
s32 func_ovl0F_04_80047358(void);
s32 func_ovl0F_04_80047B28(UnkStructA *, s32);
s32 func_ovl0F_04_80047C98(UnkStructA *, s32, UnkStructA *);
s32 func_ovl0F_04_80047E88(s32);
s32 func_ovl0F_04_80047F50(s32);
UnkStructA *func_ovl0F_04_800473B8(s32);
UnkStructA *func_ovl0F_04_800473F8(s32);
UnkStructA *func_ovl0F_04_800478D8(void (*)(s32, UnkStruct_ovl0F_04_Gfx **), s32);
UnkStructA *func_ovl0F_04_80047BA0(s32, s32, s32, s32);
UnkStructA *func_ovl0F_04_80047BE8(s32, s32);
void *func_ovl0F_04_80047CF0(void);
UnkStruct_ovl0F_04_800472C8 *func_ovl0F_04_800472C8(void);
UnkStruct_ovl0F_04_80048470 *func_ovl0F_04_80047848(s32);
void func_ovl0F_04_80047178(s32);
void func_ovl0F_04_80047190(s32);
void func_ovl0F_04_800471B8(s32, s32, s32, s32, s32, s32);
void func_ovl0F_04_800471D8(f32, f32, f32, f32 *, s32);
void func_ovl0F_04_80047200(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0F_04_80047258(void (*)(UnkStructA *), s32);
void func_ovl0F_04_80047260(void (*)(UnkStructA *));
void func_ovl0F_04_80047270(s32, s32, s32);
void func_ovl0F_04_80047328(void);
void func_ovl0F_04_80047330(s32, s32, s32);
void func_ovl0F_04_80047338(void *);
void func_ovl0F_04_80047360(s32, void *);
void func_ovl0F_04_80047370(s32);
void func_ovl0F_04_80047378(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0F_04_80047380(char *);
void func_ovl0F_04_80047388(void);
void func_ovl0F_04_800473C0(s32);
void func_ovl0F_04_80047418(s32);
void func_ovl0F_04_80047850(s32);
void func_ovl0F_04_80047868(UnkStructA *);
void func_ovl0F_04_800479A8(s32);
void func_ovl0F_04_800479B8(f32, f32, f32);
void func_ovl0F_04_800479D8(f32, f32, f32);
void func_ovl0F_04_800479E0(f32 *, f32 *, f32 *);
void func_ovl0F_04_80047A18(s32);
void func_ovl0F_04_80047A20(s32);
void func_ovl0F_04_80047AA8(f32 *);
void func_ovl0F_04_80047AC0(Vec3f *);
void func_ovl0F_04_80047AD0(f32 *);
void func_ovl0F_04_80047AD8(void);
void func_ovl0F_04_80047AE0(void);
void func_ovl0F_04_80047B78(UnkStructA *, s32);
UnkStructA *func_ovl0F_04_80047BB0(UnkStructA *);
void func_ovl0F_04_80047B80(UnkStructA *, s32);
void func_ovl0F_04_80047B90(UnkStructA *);
void func_ovl0F_04_80047BF8(UnkStructA *);
void func_ovl0F_04_80047C58(f32);
void func_ovl0F_04_80047C60(s32);
void func_ovl0F_04_80047CC8(void (*)(void), void *, s32, s32, s32);
void func_ovl0F_04_80047CD8(void);
void func_ovl0F_04_80047CE8(s32);
void func_ovl0F_04_80047D10(void);
void func_ovl0F_04_80047F40(s32);
void func_ovl0F_04_80048008(s32, s32, s32, s32, s32);
void func_ovl0F_04_80048018(s32, s32, s32);
void func_ovl0F_04_80048030(u32 (*)[3]);
void func_ovl0F_04_80048118(s32, f32, f32, f32, s32);
void func_ovl0F_04_80048158(void);
void func_ovl0F_04_800481C8(UnkStructA *, s32, f32);
void func_ovl0F_04_800481D8(s32, s32, s32);
void func_ovl0F_04_80048238(void);
void func_ovl0F_04_80048250(s32);
void func_ovl0F_04_80048270(s32, f32, f32, f32);
void func_ovl0F_04_80048278(s32, f32 *);
s32 func_ovl0F_04_80047B40(UnkStructA *, UnkStructA *);
void func_ovl0F_04_80048198(s16, f32, f32, f32);

static void func_ovl0F_04_80043324(s32 n, char *msg);
static void func_ovl0F_04_80046CD0(void);
static void func_ovl0F_04_80046CC8(void);
static void func_ovl0F_04_80046CC0(void);
static void func_ovl0F_04_80046CB8(void);
static void func_ovl0F_04_80046CB0(void);
static void func_ovl0F_04_80046CA8(void);
static void func_ovl0F_04_80046CA0(void);
static void func_ovl0F_04_80046C98(void);
static void func_ovl0F_04_80046C90(void);
static void func_ovl0F_04_80046C88(void);
static void func_ovl0F_04_80046C80(void);
static void func_ovl0F_04_80046C78(void);
static void func_ovl0F_04_80046C70(void);
static void func_ovl0F_04_80046CD8(void);
static void func_ovl0F_04_80046D14(void);
void func_ovl0F_04_80046C58(void);
void func_ovl0F_04_80046BFC(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0F_04_80046BC8(s32 arg0, UnkStructA *arg1);
static void func_ovl0F_04_8004623C(void);
static void func_ovl0F_04_800460CC(s32 n1, s32 n2);
static void func_ovl0F_04_80046244(void);
static void func_ovl0F_04_800460C4(void);
static void func_ovl0F_04_800460BC(void);
void func_ovl0F_04_80045E14(void);
void func_ovl0F_04_8004544C(s32 arg0, UnkStruct_ovl0F_04_Gfx **arg1);
static f32 func_ovl0F_04_80045444(f32 v);
static void func_ovl0F_04_80045308(UnkStruct_ovl0F_04_80048AF0 *p);
void func_ovl0F_04_800452A0(UnkStructA *obj);
void func_ovl0F_04_80044F88(void);
static void func_ovl0F_04_80044EB0(f32 *pos, s32 id, f32 d, f32 h);
void func_ovl0F_04_80044D34(s32 idx, s32 flag);
static s32 func_ovl0F_04_80044D2C(UnkStructA *obj);
s32 func_ovl0F_04_80044D04(s32 arg0);
void func_ovl0F_04_80044BC0(void);
void func_ovl0F_04_800448BC(UnkStructA *arg0);
void func_ovl0F_04_80044084(void);
void func_ovl0F_04_8004624C(s32 arg0);
static void func_ovl0F_04_80043E04(UnkStruct_ovl0F_04_80048C90 *s, s32 arg1, s32 arg2, s32 flag);
static void func_ovl0F_04_80043BC8(s16 i);
static s32 func_ovl0F_04_80043BC0(void);
void func_ovl0F_04_800439DC(void);
void func_ovl0F_04_8004394C(UnkStructA *obj);
void func_ovl0F_04_800438F0(UnkStructA *obj);
static void func_ovl0F_04_80043770(UnkStructA *obj, f32 speed);
static void func_ovl0F_04_80043768(UnkStructA *obj, f32 speed);
static void func_ovl0F_04_80043760(UnkStructA *obj, f32 speed);
static void func_ovl0F_04_80043758(UnkStructA *obj, f32 speed);
static void func_ovl0F_04_80043750(UnkStructA *obj, f32 speed);
void func_ovl0F_04_800436B0(void);
void func_ovl0F_04_80043590(UnkStructA *arg0);
void func_ovl0F_04_80043530(f32 arg0);
void func_ovl0F_04_80043480(UnkStruct_ovl0F_04_800485C4 *arg0, s32 arg1);
static void func_ovl0F_04_800433FC(UnkStruct_ovl0F_04_800485C4 *arg0);
void func_ovl0F_04_800433A0(s32 *arg0);
static void func_ovl0F_04_80045E88(UnkStructA **arg0);
void func_ovl0F_04_80043028(void);
static void func_ovl0F_04_80043020(s32 count, UnkStruct_ovl0F_04_800485C4 *p);
void func_ovl0F_04_80043010(void);


/* .bss */
UnkStructA *D_ovl0F_04_80048A70[6];
UnkStructA *D_ovl0F_04_80048A88[8];
f32 D_ovl0F_04_80048AA8[3];
u8 D_ovl0F_04_80048AB4[0x4];
Vec3f D_ovl0F_04_80048AB8;
s32 D_ovl0F_04_80048AC4;
u8 D_ovl0F_04_80048AC8[0x4];
s32 D_ovl0F_04_80048ACC;
s32 D_ovl0F_04_80048AD0;
u8 D_ovl0F_04_80048AD4[0x4];
Vec3f D_ovl0F_04_80048AD8;
s32 D_ovl0F_04_80048AE4;
u8 D_ovl0F_04_80048AE8[0x8];
UnkStruct_ovl0F_04_80048AF0 D_ovl0F_04_80048AF0[20];
Vec3f D_ovl0F_04_80048C80;
UnkStructA *D_ovl0F_04_80048C8C;
UnkStruct_ovl0F_04_80048C90 D_ovl0F_04_80048C90;

/* .data */
UnkStruct_ovl0F_04_80048470 *D_ovl0F_04_80048470 = NULL;
f32 D_ovl0F_04_80048474 = 0.0f;
f32 D_ovl0F_04_80048478 = 0.0f;
f32 D_ovl0F_04_8004847C = 0.0f;
f32 D_ovl0F_04_80048480 = 0.0f;
f32 D_ovl0F_04_80048484 = 0.0f;
/* the wind: a frame counter, its strength and step, the fog's two ends */
s32 D_ovl0F_04_80048488 = 0;
f32 D_ovl0F_04_8004848C = 0.0f;
f32 D_ovl0F_04_80048490 = 0.0f;
f32 D_ovl0F_04_80048494 = 0.0f;
f32 D_ovl0F_04_80048498 = 0.0f;
s32 D_ovl0F_04_8004849C = 1;
s32 D_ovl0F_04_800484A0 = 0;
/* the movers' script: frame, command (100 ends it) */
u16 D_ovl0F_04_800484A4[][2] = {
    { 0, 0x62 }, { 0x1E, 0 }, { 0x5A, 1 }, { 0x96, 2 }, { 0x97, 0x63 }, { 0x1C3, 0x64 },
};
/* three routes of five steps */
UnkStruct_ovl0F_04_800484BC D_ovl0F_04_800484BC[3][5] = {
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
UnkStruct_ovl0F_04_80048534 D_ovl0F_04_80048534[6] = {
    { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 1 }, { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 1 }, { 0x40, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
    { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 1 }, { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 1 }, { 0xC0, 1.0f, 0.0f, 0, 0, 0, 0, 1 },
};
/* the movers' models */
UnkStruct_ovl0F_04_800485C4 D_ovl0F_04_800485C4[6] = {
    { &D_ovl0F_04_80048A70[0], 0x259, 0, 0.0f, 4.0f, 6.0f, 0.0f, 90.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_04_80048A70[1], 0x259, 0, 0.0f, 4.0f, 11.0f, 0.0f, 90.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_04_80048A70[2], 0x259, 0, 0.0f, 4.0f, 17.0f, 0.0f, 90.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_04_80048A70[3], 0x259, 0, 45.0f, 4.0f, 8.0f, 0.0f, 270.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_04_80048A70[4], 0x259, 0, 45.0f, 4.0f, 12.0f, 0.0f, 270.0f, 0.0f, 0x0C000070, 0 },
    { &D_ovl0F_04_80048A70[5], 0x259, 0, 45.0f, 4.0f, 17.0f, 0.0f, 270.0f, 0.0f, 0x0C000070, 0 },
};
/* the panels */
UnkStruct_ovl0F_04_800485C4 D_ovl0F_04_800486CC[5] = {
    { &D_ovl0F_04_80048A88[0], 0x25B, 0, 22.0f, 4.0f, 11.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_04_80048A88[1], 0x25B, 0, 23.0f, 4.0f, 13.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_04_80048A88[2], 0x25B, 0, 24.0f, 4.0f, 18.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_04_80048A88[3], 0x25B, 0, 24.0f, 4.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_04_80048A88[4], 0x25B, 0, 23.0f, 4.0f, 22.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};
UnkStruct_ovl0F_04_800487A8 D_ovl0F_04_800487A8[5] = {
    { 1, 0x1410, -1 }, { 1, 0x1410, -1 }, { 1, 0x1410, -1 }, { 1, 0x1410, -1 }, { 1, 0x1410, -1 },
};
/* passed to func_ovl0F_04_80048030: three 12-byte records */
u32 D_ovl0F_04_800487E4[][3] = {
    { 0x2640002, 0xF, 4 },
    { 0x25C0002, 0xF, 4 },
    { 0x26E0000, 0xF, 0x2004 },
};
/* six 12-byte records, each passed to func_ovl0F_04_800481D8 */
u32 D_ovl0F_04_80048808[][3] = {
    { 0, 0x12, 0xF0 }, { 1, 0x13, 0xF1 }, { 2, 0x16, 0xF4 }, { 3, 0, 0xDE }, { 4, 2, 0xE0 }, { 5, 0x15, 0xF3 },
};
UnkStruct_ovl0F_04_800485C4 D_ovl0F_04_80048850 = {
    &D_ovl0F_04_80048A88[5], 0x225, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0,
};
UnkStructA *D_ovl0F_04_8004887C = NULL;
UnkStruct_ovl0F_04_80048880 D_ovl0F_04_80048880 = {
    {
        { &D_ovl0F_04_8004887C, 0x25F, 0, 33.0f, 0.0f, 13.0f, 0.0f, 270.0f, 0.0f, 0, 0x402 },
        { &D_ovl0F_04_80048A88[6], 0x260, 0, 33.0f, 1.0f, 13.0f, 0.0f, 270.0f, 0.0f, 0, 0 },
    },
    func_ovl0F_04_80046CD8,
    func_ovl0F_04_80046D14,
};
/* func_ovl0F_04_800433A0's: four arguments to test, three to pass on */
s32 D_ovl0F_04_800488E0[7] = { 0x1B, 0x10, 0x1B, 0x10, 0x58, 0x14, 0 };
s32 D_ovl0F_04_800488FC[7] = { 8, 0x1D, 9, 0x1E, 0x5A, 0x14, 0 };
UnkStruct_ovl0F_04_80048918 D_ovl0F_04_80048918[2] = {
    { 0x40, 3, 8.5f, 3, 0, 1, 0 },
    { 0xE0, 3, 8.5f, 2, 0, 1, 0 },
};
char D_ovl0F_04_80048950[] = "MA";
char D_ovl0F_04_80048954[] = "MA";
char D_ovl0F_04_80048958[] = "WM1 WG1 WSH WAP WDW WB3 ST10";
char D_ovl0F_04_80048978[] = "WM1 WG1 WSH WAP WDE WB2 ST30";

/* the switches' cut-scene: a task counts n frames while a message shows */
static void func_ovl0F_04_80043324(s32 n, char *msg) {
    func_ovl0F_04_80047418(1);
    func_ovl0F_04_80048158();
    func_ovl0F_04_80047CC8(func_ovl0F_04_80045E14, (void *) n, 0, 0, 0x130);
    func_ovl0F_04_80047380(msg);
    func_ovl0F_04_80047418(0);
    func_ovl0F_04_80047380(D_ovl0F_04_80048950);
}

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0F_04_80046CD0(void) {
}

static void func_ovl0F_04_80046CC8(void) {
}

static void func_ovl0F_04_80046CC0(void) {
}

static void func_ovl0F_04_80046CB8(void) {
}

static void func_ovl0F_04_80046CB0(void) {
}

static void func_ovl0F_04_80046CA8(void) {
}

static void func_ovl0F_04_80046CA0(void) {
}

static void func_ovl0F_04_80046C98(void) {
}

static void func_ovl0F_04_80046C90(void) {
}

static void func_ovl0F_04_80046C88(void) {
}

static void func_ovl0F_04_80046C80(void) {
}

static void func_ovl0F_04_80046C78(void) {
}

static void func_ovl0F_04_80046C70(void) {
}

/* the door's: what func_ovl0F_04_80044F88 calls once it is open (the two
 * callbacks in D_ovl0F_04_80048880) */
static void func_ovl0F_04_80046CD8(void) {
    func_ovl0F_04_800471B8(0x21, 2, 0xB, 0x21, 0xF, 0x1410);
}

static void func_ovl0F_04_80046D14(void) {
    func_ovl0F_04_800471B8(0x1F, 1, 0xB, 0x20, 0xF, 0x1410);
    func_ovl0F_04_800471B8(0x21, 1, 0xB, 0x21, 0xF, 0x1411);
    func_ovl0F_04_800471B8(0x22, 1, 0xB, 0x23, 0xF, 0x1410);
    func_ovl0F_04_800471B8(0x1F, 0, 0xB, 0x20, 0xF, 0x1815);
    func_ovl0F_04_800471B8(0x21, 0, 0xB, 0x21, 0xF, 0x1F);
    func_ovl0F_04_800471B8(0x22, 0, 0xB, 0x23, 0xF, 0x1416);
    func_ovl0F_04_800471B8(0x24, 0, 0xB, 0x27, 0xF, 0x1411);
    D_ovl0F_04_800484A0 = 0;
}

void func_ovl0F_04_80046C58(void) {
    D_ovl0F_04_80048ACC = -1;
    D_ovl0F_04_80048AD0 = -1;
}

void func_ovl0F_04_80046BFC(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_04_800479B8(D_ovl0F_04_80048AD8.x, D_ovl0F_04_80048AD8.y, D_ovl0F_04_80048AD8.z);
    func_ovl0F_04_800479D8(arg0, arg1, arg2);
    func_ovl0F_04_80047CE8(180);
}

void func_ovl0F_04_80046BC8(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0F_04_80048270(arg0, p->unk10, p->unk14, p->unk18);
}

/* case 2's: the panels and their tiles; one hides something */
static void func_ovl0F_04_8004623C(void) {
    s32 i;

    func_ovl0F_04_80043480(D_ovl0F_04_800486CC, 5);
    for (i = 0; i < 5; i++) {
        if (D_ovl0F_04_800486CC[i].unk1C == 0.0f) {
            func_ovl0F_04_800471B8((s32) D_ovl0F_04_800486CC[i].unkC - 1, (s32) D_ovl0F_04_800486CC[i].unk10,
                                   (s32) D_ovl0F_04_800486CC[i].unk14 - 1, (s32) D_ovl0F_04_800486CC[i].unkC - 1,
                                   (s32) D_ovl0F_04_800486CC[i].unk14, 0x1411);
            func_ovl0F_04_800471B8((s32) D_ovl0F_04_800486CC[i].unkC, (s32) D_ovl0F_04_800486CC[i].unk10,
                                   (s32) D_ovl0F_04_800486CC[i].unk14 - 1, (s32) D_ovl0F_04_800486CC[i].unkC,
                                   (s32) D_ovl0F_04_800486CC[i].unk14, 0x141A);
        }
        D_ovl0F_04_800487A8[i].unk0 = 1;
        D_ovl0F_04_800487A8[i].unk8 = -1;
    }
    D_ovl0F_04_800487A8[func_ovl0F_04_80047E88(5)].unk8 = 3;
    func_ovl0F_04_80047258(func_ovl0F_04_8004394C, 7);
}

/* case 2's: the wind, the blocks' callbacks and the particles */
static void func_ovl0F_04_800460CC(s32 n1, s32 n2) {
    s32 i;

    if (func_ovl0F_04_800472C8()->unk10 == 0) {
        D_ovl0F_04_80048490 = 8.5f;
    } else {
        D_ovl0F_04_80048490 = 15.3f;
    }
    D_ovl0F_04_80048488 = 0;
    D_ovl0F_04_8004848C = 0.0f;
    D_ovl0F_04_8004849C = 1;
    func_ovl0F_04_80047258(func_ovl0F_04_800438F0, n1);
    func_ovl0F_04_80047258(func_ovl0F_04_800452A0, n2);
    D_ovl0F_04_80048470 = func_ovl0F_04_80047848(0x258);
    D_ovl0F_04_80048C8C = func_ovl0F_04_800478D8(func_ovl0F_04_8004544C, -60);
    D_ovl0F_04_80048C8C->unkC |= 0x210;
    for (i = 0; i < 20; i++) {
        func_ovl0F_04_80045308(&D_ovl0F_04_80048AF0[i]);
        D_ovl0F_04_80048AF0[i].unk4 = func_ovl0F_04_80047E88(240);
    }
    func_ovl0F_04_80047AC0(&D_ovl0F_04_80048C80);
    D_ovl0F_04_8004847C = 0.0f;
    D_ovl0F_04_80048480 = 0.0f;
    D_ovl0F_04_80048484 = 1.0f;
    func_ovl0F_04_80047F40(0x407);
    func_ovl0F_04_80048018(0xE6, 0xF0, 0xFF);
    func_ovl0F_04_80048008(0x35C, 0x3C0, 0xE6, 0xF0, 0xFF);
    D_ovl0F_04_80048494 = 860.0f;
    D_ovl0F_04_80048498 = 960.0f;
}

/* case 2's: the door, closed or already open */
static void func_ovl0F_04_80046244(void) {
    if (func_ovl0F_04_80047F50(D_ovl0F_04_80048880.unk0[0].unk28) == 0) {
        func_ovl0F_04_80047CC8(func_ovl0F_04_80044F88, &D_ovl0F_04_80048880, 0, 0, 0x110);
    } else {
        D_ovl0F_04_80048880.unk58();
        D_ovl0F_04_80048880.unk5C();
        D_ovl0F_04_80048880.unk0[1].unk10 -= 1.0f;
        func_ovl0F_04_80043480(&D_ovl0F_04_80048880.unk0[1], 1);
        *D_ovl0F_04_80048880.unk0[0].unk0 = NULL;
        D_ovl0F_04_80048880.unk0[1].unk10 += 1.0f;
    }
}

/* case 2's: the stage's tables */
static void func_ovl0F_04_800460C4(void) {
    s32 count;
    u32 (*p)[3];
    s32 i;

    func_ovl0F_04_80048030(D_ovl0F_04_800487E4);
    p = D_ovl0F_04_80048808;
    count = 6;
    for (i = 0; i < count; i++) {
        func_ovl0F_04_800481D8((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}

static void func_ovl0F_04_800460BC(void) {
    func_ovl0F_04_80047178(0x227);
    func_ovl0F_04_80047190(0x23A);
    func_ovl0F_04_80047328();
}

void func_ovl0F_04_80045E14(void) {
    s32 n;
    s32 i;

    n = (s32)func_ovl0F_04_80047CF0();
    for (i = 0; i < n; i++) {
        func_ovl0F_04_80048238();
        func_ovl0F_04_80047D10();
    }
    func_ovl0F_04_80047CD8();
}

static f32 func_ovl0F_04_80045444(f32 v) {
    return v == 0.0f ? 0.0f : 1.0f;
}

void func_ovl0F_04_8004544C(s32 arg0, UnkStruct_ovl0F_04_Gfx **arg1) {
    UnkStruct_ovl0F_04_Gfx *gfx;
    UnkStruct_ovl0F_04_80048AF0 *p;
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
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x00553048; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF279; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xBB000001; g->w1 = 0x80008000; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0x8000; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xFD100000; g->w1 = D_ovl0F_04_80048470->unk20 + (u32) D_ovl0F_04_80048470; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xE8000000; g->w1 = 0; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xF5000100; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xF0000000; g->w1 = 0x0703C000; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xFD500000; g->w1 = D_ovl0F_04_80048470->unk14 + (u32) D_ovl0F_04_80048470; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xF5500000; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xF3000000; g->w1 = 0x0703F800; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xF5400200; g->w1 = 0; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xF2000000; g->w1 = 0x0003C03C; }
    oldx = D_ovl0F_04_80048C80.x;
    oldz = D_ovl0F_04_80048C80.z;
    func_ovl0F_04_80047AC0(&D_ovl0F_04_80048C80);
    func_ovl0F_04_80047AD0(view);
    s = func_ovl0F_04_80047E78(view[0]);
    c = func_ovl0F_04_80047E70(view[0]);
    D_ovl0F_04_80048474 = ((D_ovl0F_04_80048C80.x - oldx) * s - c * (D_ovl0F_04_80048C80.z - oldz)) * 0.5f;
    s = func_ovl0F_04_80047E78(view[0]);
    c = func_ovl0F_04_80047E70(view[0]);
    D_ovl0F_04_80048478 = (c * (D_ovl0F_04_80048C80.x - oldx) + (D_ovl0F_04_80048C80.z - oldz) * s) * 0.2f;
    scale = 1500.0f / view[2];
    D_ovl0F_04_80048474 *= scale;
    D_ovl0F_04_80048478 *= scale;
    i = 0;
    if (func_ovl0F_04_80047F50(0x407) == 0) {
        goto update;
    }
    do {
        p = &D_ovl0F_04_80048AF0[i];
        dsdx = 16.0f / (p->unk8 - 1.0f) * 1024.0f;
        {
            UnkStruct_ovl0F_04_Gfx *g = gfx++;
            g->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL((u32) (p->unk0 + p->unk8 - 1.0f) << 2, 12, 12) | _SHIFTL((u32) (p->unk4 + p->unk8 - 1.0f) << 2, 0, 12);
            g->w1 = _SHIFTL(0, 24, 3) | _SHIFTL((u32) p->unk0 << 2, 12, 12) | _SHIFTL((u32) p->unk4 << 2, 0, 12);
        }
        { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xB4000000; g->w1 = 0; }
        { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xB3000000; g->w1 = _SHIFTL(dsdx, 16, 16) | _SHIFTL(dsdx, 0, 16); }
    update:
        if (D_ovl0F_04_80048484 != 0.0f) {
            p = &D_ovl0F_04_80048AF0[i];
            s = func_ovl0F_04_80047E78(view[0]);
            dx = -D_ovl0F_04_80048474;
            p->unk0 += dx - (f32) func_ovl0F_04_80047E80() * (dx * 0.25f) + D_ovl0F_04_8004847C * s;
            sign = func_ovl0F_04_80045444(D_ovl0F_04_8004847C);
            if (func_ovl0F_04_80047E70(view[0]) * (sign * D_ovl0F_04_8004847C) + D_ovl0F_04_80048480 < 0.0f) {
                sign = func_ovl0F_04_80045444(D_ovl0F_04_8004847C);
                drift = (func_ovl0F_04_80047E70(view[0]) * (sign * D_ovl0F_04_8004847C) + D_ovl0F_04_80048480) * 0.5;
            } else {
                sign = func_ovl0F_04_80045444(D_ovl0F_04_8004847C);
                drift = func_ovl0F_04_80047E70(view[0]) * (sign * D_ovl0F_04_8004847C) + D_ovl0F_04_80048480;
            }
            p->unk4 += (p->unkC - D_ovl0F_04_80048478) - (f32) func_ovl0F_04_80047E80() * ((p->unkC - D_ovl0F_04_80048478) * 0.6f) + drift;
            p->unk8 -= 0.1f * (p->unk8 * 0.0625f);
            if (340.0f <= p->unk0 || 240.0f <= p->unk4 || p->unk8 <= 3.0f || p->unk10++ >= 240 || p->unk0 < -20.0f ||
                p->unk4 < -10.0f) {
                func_ovl0F_04_80045308(p);
            }
        }
        i++;
    } while (i != 20);
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0x00080000; }
    { UnkStruct_ovl0F_04_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0; }
    *arg1 = gfx;
}

static void func_ovl0F_04_80045308(UnkStruct_ovl0F_04_80048AF0 *p) {
    f32 r;
    f64 t;

    r = func_ovl0F_04_80047E80();
    p->unk0 = func_ovl0F_04_80047E80() * 370.0 - 50.0;
    t = func_ovl0F_04_80047E80();
    p->unk4 = (D_ovl0F_04_8004847C < 0.0f ? -D_ovl0F_04_8004847C : D_ovl0F_04_8004847C) * 30.0f * t;
    if (D_ovl0F_04_80048478 <= 0.0f) {
        p->unk4 += (1.0f - r) * 40.0f;
    } else {
        p->unk4 += func_ovl0F_04_80047E88(90);
    }
    p->unk10 = 0;
    p->unk8 = r * 12.0f + 4.0f;
    p->unkC = r * r * 5.0f + 0.5f;
}

void func_ovl0F_04_800452A0(UnkStructA *obj) {
    func_ovl0F_04_80043770(obj, D_ovl0F_04_8004848C * 0.42857143f);
}

void func_ovl0F_04_80044F88(void) {
    UnkStruct_ovl0F_04_80048880 *task;
    f32 pos[3];
    s32 hit;

    task = func_ovl0F_04_80047CF0();
    func_ovl0F_04_800471D8(task->unk0[0].unkC, task->unk0[0].unk10, task->unk0[0].unk14, pos, 0);
    func_ovl0F_04_80043480(task->unk0, 2);
    (*task->unk0[0].unk0)->unk34 = 250.0f;
    (*task->unk0[0].unk0)->unkC = 0;
    (*task->unk0[1].unk0)->unkC = 0;
    (*task->unk0[1].unk0)->unk70 = 2.45f;
    while (func_ovl0F_04_80047F50(task->unk0[0].unk28) == 0) {
        hit = func_ovl0F_04_80047B28(*task->unk0[0].unk0, 0x40);
        if (hit != 0) {
            if ((hit & 0x2000) || (hit & 0x4000)) {
                func_ovl0F_04_80047F40(task->unk0[0].unk28);
            } else {
                func_ovl0F_04_80048278(0x26, pos);
            }
        }
        func_ovl0F_04_80047CE8(5);
    }
    func_ovl0F_04_80048278(0x8A, pos);
    func_ovl0F_04_80044EB0(pos, 0x14, 250.0f, 120.0f);
    func_ovl0F_04_80047CE8(10);
    func_ovl0F_04_80044EB0(pos, 0x16, 250.0f, 120.0f);
    func_ovl0F_04_80043020(1, task->unk0);
    *task->unk0[0].unk0 = NULL;
    func_ovl0F_04_800471B8((s32) task->unk0[1].unkC - 2, (s32) task->unk0[1].unk10, (s32) task->unk0[1].unk14 - 2,
                           (s32) task->unk0[1].unkC + 2, (s32) task->unk0[1].unk14 + 2, 0x1410);
    task->unk58();
    func_ovl0F_04_80047BF8(*task->unk0[1].unk0);
    func_ovl0F_04_80047D10();
    do {
        func_ovl0F_04_80047BF8(*task->unk0[1].unk0);
        func_ovl0F_04_80047D10();
    } while ((*task->unk0[1].unk0)->unk6C != 0.0f);
    task->unk5C();
    func_ovl0F_04_80047CD8();
}

static void func_ovl0F_04_80044EB0(f32 *pos, s32 id, f32 d, f32 h) {
    func_ovl0F_04_80048118(id, pos[0] + d, pos[1] + h, pos[2] + d, 0);
    func_ovl0F_04_80048118(id, pos[0] + d, pos[1] + h, pos[2] - d, 0);
    func_ovl0F_04_80048118(id, pos[0] - d, pos[1] + h, pos[2] + d, 0);
    func_ovl0F_04_80048118(id, pos[0] - d, pos[1] + h, pos[2] - d, 0);
}

/* the script's command: a mover (re)starts; with flag 0 it stays stopped */
void func_ovl0F_04_80044D34(s32 idx, s32 flag) {
    UnkStruct_ovl0F_04_800485C4 *p;
    UnkStruct_ovl0F_04_80048534 *m;

    p = &D_ovl0F_04_800485C4[idx];
    func_ovl0F_04_800433FC(p);
    m = &D_ovl0F_04_80048534[idx];
    m->unkC = 0;
    m->unk12 = 0;
    m->unk14 = 1;
    m->unk11 = flag;
    if (flag == 0) {
        func_ovl0F_04_80047B80(*p->unk0, 0x01000070);
    } else {
        func_ovl0F_04_80047B78(*p->unk0, 0x01000070);
    }
    m->unk10 = 0;
    m->unk4 = 1.0f;
    m->unk8 = 0.05f;
    (*p->unk0)->unk40->unk14 = 200.0f;
    if (flag != 0) {
        (*p->unk0)->unk68 = 20.0f;
        (*p->unk0)->unk6C = 0.0f;
        func_ovl0F_04_80048118(0xC, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14, (*p->unk0)->unk40->unk18, 0);
    }
}

static s32 func_ovl0F_04_80044D2C(UnkStructA *obj) {
    s32 below;

    below = 0;
    if (obj->unk40->unk14 <= func_ovl0F_04_800471A0()) {
        below = 1;
    }
    return below;
}

/* the movers' step filter: every direction but 0xF */
s32 func_ovl0F_04_80044D04(s32 arg0) {
    if ((arg0 & 0xF) == 0xF) {
        return 0;
    }
    return 1;
}

/* a task: a hit mover's effects */
void func_ovl0F_04_80044BC0(void) {
    UnkStruct_ovl0F_04_800485C4 *p;
    s32 i;

    p = &D_ovl0F_04_800485C4[(s32) func_ovl0F_04_80047CF0()];
    for (i = 0; i < 3; i++) {
        func_ovl0F_04_80048118(7, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14 + 100.0f, (*p->unk0)->unk40->unk18, 0);
        func_ovl0F_04_80047CE8(3);
    }
    for (i = 0; i < 5; i++) {
        func_ovl0F_04_80048118(0x18, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14 + 100.0f, (*p->unk0)->unk40->unk18, 0);
        func_ovl0F_04_80047CE8(3);
    }
    func_ovl0F_04_80048118(0x16, (*p->unk0)->unk40->unk10, (*p->unk0)->unk40->unk14 + 100.0f, (*p->unk0)->unk40->unk18, 0);
    func_ovl0F_04_80047CD8();
}

/* the player's callback when a mover throws it */
void func_ovl0F_04_800448BC(UnkStructA *arg0) {
    s32 dir;
    f32 speed;
    f32 dy;
    s32 i;

    dir = 0;
    speed = 0.0f;
    func_ovl0F_04_80048250(3);
    if (D_ovl0F_04_80048C90.unk16 != -1) {
        dir = D_ovl0F_04_80048534[D_ovl0F_04_80048C90.unk16].unk0;
        speed = D_ovl0F_04_80048534[D_ovl0F_04_80048C90.unk16].unk4 * 0.8f;
    }
    func_ovl0F_04_800478A0(arg0->unk40, 0x11, 0);
    func_ovl0F_04_800478D0(arg0->unk40, 4, 0xC);
    func_ovl0F_04_800478D0(arg0->unk40, 5, 0xD);
    func_ovl0F_04_80048118(0, arg0->unk40->unk10, arg0->unk40->unk14 + 100.0f, arg0->unk40->unk18, 0);
    arg0->unk68 = 30.0f;
    arg0->unk70 = 1.6333334f;
    for (i = 1; i <= 200 && arg0->unk68 > 0.0f && !func_ovl0F_04_80044D2C(arg0); i++) {
        dy = func_ovl0F_04_80047E78(arg0->unk40->unk1C) * 30.0f;
        func_ovl0F_04_800481C0(arg0, dir, speed, func_ovl0F_04_80044D04);
        arg0->unk40->unk1C += 10.0f;
        arg0->unk40->unk10 -= func_ovl0F_04_80047E70(arg0->unk40->unk1C);
        if (dy > 0.0f) {
            dy = 0.0f;
        }
        arg0->unk40->unk14 -= dy;
        func_ovl0F_04_80047D10();
    }
    if (func_ovl0F_04_80044D2C(arg0)) {
        func_ovl0F_04_80043590(arg0);
    } else {
        arg0->unk6C = 0.0f;
        arg0->unk70 = 0.0f;
    }
    func_ovl0F_04_80047CE8(0x50);
}

/* a task: the movers, until the script ends and all have stopped */
void func_ovl0F_04_80044084(void) {
    s32 again;
    s16 i;
    UnkStruct_ovl0F_04_80048534 *m;
    UnkStruct_ovl0F_04_800485C4 *p;
    UnkStruct_ovl0F_04_800484BC *st;
    UnkStructA *pl;
    f32 dist;
    f32 angle;
    f32 pos[3];
    s32 hit;

    again = 1;
    do {
        func_ovl0F_04_80043E04(&D_ovl0F_04_80048C90, 0, 0, D_ovl0F_04_800484A0);
        if (D_ovl0F_04_80048C90.unkC != 0 && *D_ovl0F_04_80048C90.unk4 != NULL &&
            (*D_ovl0F_04_80048C90.unk4)->unk40->unk48 != NULL) {
            (*D_ovl0F_04_80048C90.unk4)->unk40->unk48->unk4->unk4 = D_ovl0F_04_80048C90.unk8;
            if (D_ovl0F_04_80048C90.unkC == 1) {
                D_ovl0F_04_80048C90.unk8 += 1.0f;
                if (func_ovl0F_04_800478B8((*D_ovl0F_04_80048C90.unk4)->unk40, 0) <= D_ovl0F_04_80048C90.unk8) {
                    D_ovl0F_04_80048C90.unk8 = 0.0f;
                    D_ovl0F_04_80048C90.unkC = 0;
                }
            } else {
                D_ovl0F_04_80048C90.unk8 -= 1.0f;
                if (D_ovl0F_04_80048C90.unk8 < 0.0f) {
                    D_ovl0F_04_80048C90.unk8 = 0.0f;
                    D_ovl0F_04_80048C90.unkC = 0;
                    if (*D_ovl0F_04_80048C90.unk4 != NULL) {
                        func_ovl0F_04_80048270(0x8C, (*D_ovl0F_04_80048C90.unk4)->unk40->unk10,
                                               (*D_ovl0F_04_80048C90.unk4)->unk40->unk14,
                                               (*D_ovl0F_04_80048C90.unk4)->unk40->unk18);
                    }
                }
            }
        }
        for (i = 0; i < 6; i++) {
            m = &D_ovl0F_04_80048534[i];
            p = &D_ovl0F_04_800485C4[i];
            if (m->unk11 == 1) {
                func_ovl0F_04_80047C88(*p->unk0);
                pl = D_ovl0F_04_80048C90.unk0;
                if (pl->unk40->unk10 <= (*p->unk0)->unk40->unk10 + 300.0f &&
                    (*p->unk0)->unk40->unk10 - 300.0f <= pl->unk40->unk10 &&
                    pl->unk40->unk18 <= (*p->unk0)->unk40->unk18 + 300.0f &&
                    (*p->unk0)->unk40->unk18 - 300.0f <= pl->unk40->unk18) {
                    if (m->unk14 != 0) {
                        func_ovl0F_04_80048250(0x87);
                        m->unk14 = 0;
                    }
                } else if (m->unk14 == 0) {
                    m->unk14 = 1;
                }
                if ((*p->unk0)->unk6C == 0.0f) {
                    st = &D_ovl0F_04_800484BC[m->unk10][m->unk12];
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
                func_ovl0F_04_80043BC8(i);
                func_ovl0F_04_800481C0(*p->unk0, m->unk0, m->unk4, func_ovl0F_04_80044D04);
                dist = 0.0f;
                angle = 0.0f;
                func_ovl0F_04_80047200((*p->unk0)->unk40, &dist, &angle);
                if (func_ovl0F_04_80047E70((*p->unk0)->unk40->unk20) >= 0.707f && angle != 0.0f) {
                    dist *= func_ovl0F_04_80047E70(angle);
                }
                (*p->unk0)->unk40->unk1C = dist * 0.6f;
                if (func_ovl0F_04_80044D2C(*p->unk0)) {
                    D_ovl0F_04_80048C90.unk20(i, 0);
                } else {
                    hit = func_ovl0F_04_80047B28(*p->unk0, 0x40);
                    if (hit != 0 && ((hit & 0x2000) || (hit & 0x4000))) {
                        pos[0] = (*p->unk0)->unk40->unk10;
                        pos[1] = (*p->unk0)->unk40->unk14;
                        pos[2] = (*p->unk0)->unk40->unk18;
                        func_ovl0F_04_80048278(0x168, pos);
                        func_ovl0F_04_80048230(pos);
                        (*p->unk0)->unk68 = 20.0f;
                        (*p->unk0)->unk70 = 0.8166667f;
                        m->unk11 = 2;
                        func_ovl0F_04_80047CC8(func_ovl0F_04_80044BC0, (void *) (s32) i, 0, 0, 0x150);
                    }
                    if (func_ovl0F_04_80047B40(D_ovl0F_04_80048C90.unk0, *p->unk0) != 0) {
                        D_ovl0F_04_80048C90.unk16 = i;
                    }
                    m->unk4 += m->unk8;
                }
            } else if (m->unk11 == 2) {
                if ((*p->unk0)->unk68 == 0.0f && (*p->unk0)->unk6C == 0.0f) {
                    D_ovl0F_04_80048C90.unk20(i, 0);
                } else {
                    if ((*p->unk0)->unk40->unk1C < 180.0f) {
                        (*p->unk0)->unk40->unk1C += 5.0f;
                    }
                    func_ovl0F_04_800481C0(*p->unk0, m->unk0, m->unk4, func_ovl0F_04_80044D04);
                    func_ovl0F_04_80047BF8(*p->unk0);
                    if (func_ovl0F_04_80044D2C(*p->unk0)) {
                        D_ovl0F_04_80048C90.unk20(i, 0);
                    }
                }
            }
        }
        if (D_ovl0F_04_800484A0 == 0) {
            again = 0;
            for (i = 0; i < 6; i++) {
                if (D_ovl0F_04_80048534[i].unk11 != 0) {
                    again = 1;
                }
            }
        }
        func_ovl0F_04_80047D10();
    } while (again);
    func_ovl0F_04_80043020(6, D_ovl0F_04_800485C4);
    func_ovl0F_04_80047CD8();
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_04_8004624C(s32 arg0) {
    s32 i;
    f32 sp1C;

    switch (arg0) {
        case 2:
            func_ovl0F_04_80047F48(0x406);
            func_ovl0F_04_800460C4();
            func_ovl0F_04_800460BC();
            func_ovl0F_04_800460CC(5, 5);
            func_ovl0F_04_80046244();
            if (func_ovl0F_04_80047F50(0x402) == 0) {
                func_ovl0F_04_80045E88(&D_ovl0F_04_8004887C);
            }
            func_ovl0F_04_8004623C();
            break;
        case 17:
            func_ovl0F_04_800479D8(45.0f, 32768.0f, 32768.0f);
            func_ovl0F_04_80047370(0x40);
            func_ovl0F_04_80047330(0x1B, 0, 0x10);
            break;
        case 19:
            func_ovl0F_04_80043530(180.0f);
            func_ovl0F_04_80047370(0xE0);
            func_ovl0F_04_80047330(8, 4, 0x1D);
            break;
        case 20:
            func_ovl0F_04_80047330(6, 4, 0x1B);
            break;
        case 4:
            func_ovl0F_04_80047388();
            func_ovl0F_04_80047260(func_ovl0F_04_80043590);
            func_ovl0F_04_80043480(&D_ovl0F_04_80048850, 1);
            func_ovl0F_04_80047C58(40.0f);
            func_ovl0F_04_80047C60(30);
            break;
        case 5:
            switch (func_ovl0F_04_80047278()) {
                case 0x11:
                    func_ovl0F_04_80047378(D_ovl0F_04_80048918[0].unk0, D_ovl0F_04_80048918[0].unk4,
                                           D_ovl0F_04_80048918[0].unk8, D_ovl0F_04_80048918[0].unkC,
                                           D_ovl0F_04_80048918[0].unk10, D_ovl0F_04_80048918[0].unk14,
                                           D_ovl0F_04_80048918[0].unk18);
                    break;
                case 0x13:
                    func_ovl0F_04_80047378(D_ovl0F_04_80048918[1].unk0, D_ovl0F_04_80048918[1].unk4,
                                           D_ovl0F_04_80048918[1].unk8, D_ovl0F_04_80048918[1].unkC,
                                           D_ovl0F_04_80048918[1].unk10, D_ovl0F_04_80048918[1].unk14,
                                           D_ovl0F_04_80048918[1].unk18);
                    func_ovl0F_04_80047CC8(func_ovl0F_04_800436B0, NULL, 0, 0, 0x130);
                    break;
            }
            break;
        case 0x50:
            func_ovl0F_04_800433A0(D_ovl0F_04_800488E0);
            func_ovl0F_04_800433A0(D_ovl0F_04_800488FC);
            break;
        case 0x52:
            if (func_ovl0F_04_80047340(0x12, 0xA, 0x12, 0xA) != 0) {
                if (func_ovl0F_04_80047F50(0x406) == 0) {
                    func_ovl0F_04_80047C58(0.0f);
                    func_ovl0F_04_80047C60(0x7F);
                    func_ovl0F_04_80047F40(0x406);
                    func_ovl0F_04_80047F48(0x407);
                    func_ovl0F_04_80047AD8();
                    func_ovl0F_04_80047A20(0xF);
                    func_ovl0F_04_80047A18(0x10);
                    func_ovl0F_04_800479A8(0);
                    func_ovl0F_04_800479C8(581.4f, 1430.1f, 1133.3f);
                    func_ovl0F_04_80043324(60, D_ovl0F_04_80048958);
                }
            } else {
                i = func_ovl0F_04_80043BC0();
                if (i != -1) {
                    D_ovl0F_04_80048AE4 = i;
                    func_ovl0F_04_80047CC8(func_ovl0F_04_800439DC, NULL, 0, 0, 0x110);
                }
            }
            break;
        case 0x53:
            if (func_ovl0F_04_80047340(0x13, 0xA, 0x13, 0xA) != 0) {
                if (func_ovl0F_04_80047F50(0x406) != 0) {
                    func_ovl0F_04_80047C58(40.0f);
                    func_ovl0F_04_80047C60(30);
                    func_ovl0F_04_80047F48(0x406);
                    func_ovl0F_04_80047F40(0x407);
                    func_ovl0F_04_80047A18(0x1F);
                    func_ovl0F_04_800479A8(1);
                    func_ovl0F_04_80047AE0();
                    func_ovl0F_04_80047AA8(D_ovl0F_04_80048AA8);
                    func_ovl0F_04_80043324(60, D_ovl0F_04_80048978);
                }
            }
            break;
        case 1:
            func_ovl0F_04_80047868(D_ovl0F_04_80048C8C);
            func_ovl0F_04_80047850(0x258);
            func_ovl0F_04_80043020(5, D_ovl0F_04_800486CC);
            func_ovl0F_04_80043020(1, &D_ovl0F_04_80048850);
            if (func_ovl0F_04_80047F50(D_ovl0F_04_80048880.unk0[0].unk28) == 0) {
                func_ovl0F_04_80043020(2, D_ovl0F_04_80048880.unk0);
            } else {
                func_ovl0F_04_80043020(1, &D_ovl0F_04_80048880.unk0[1]);
            }
            *D_ovl0F_04_80048880.unk0[0].unk0 = NULL;
            break;
        case 12:
            func_ovl0F_04_800473C0(1);
            break;
        case 3:
            D_ovl0F_04_80048AC4 = func_ovl0F_04_80047358();
            func_ovl0F_04_80047338(&D_ovl0F_04_80048AB8);
            func_ovl0F_04_80047360(D_ovl0F_04_80048AC4, D_ovl0F_04_80048AA8);
            func_ovl0F_04_80043028();
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
            break;
    }
}

/* one step of the movers' script */
static void func_ovl0F_04_80043E04(UnkStruct_ovl0F_04_80048C90 *s, s32 arg1, s32 arg2, s32 flag) {
    u16 *e;
    s32 kind;
    s32 arg;

    e = s->unk18[s->unk14];
    if (e[0] == s->unk10++) {
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
                        if (D_ovl0F_04_80048534[arg].unk11 == 0) {
                            s->unk20(arg, 1);
                        }
                        break;
                    case 10:
                        switch (arg) {
                            case 1:
                                if (*s->unk4 != NULL) {
                                    func_ovl0F_04_80048270(0x8C, (*s->unk4)->unk40->unk10, (*s->unk4)->unk40->unk14,
                                                           (*s->unk4)->unk40->unk18);
                                }
                                if (s->unkC == 0) {
                                    s->unkC = 1;
                                    s->unk8 = 0.0f;
                                }
                                break;
                            case 2:
                                if (s->unkC == 0) {
                                    s->unkC = 2;
                                    if (*s->unk4 != NULL) {
                                        s->unk8 = func_ovl0F_04_800478B8((*s->unk4)->unk40, 0) - 0.001f;
                                    }
                                }
                                break;
                        }
                        break;
                }
            }
            s->unk14++;
        } else {
            s->unk10 = 0;
            s->unk14 = 0;
        }
    }
}

/* a mover turns towards its direction, a tenth of the way (at least 1) a frame */
static void func_ovl0F_04_80043BC8(s16 i) {
    f32 target;
    f32 d;

    target = 0.0f;
    switch (D_ovl0F_04_80048534[i].unk0) {
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
    if (target < (*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20) {
        d = ((*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20 - target) * 0.1f;
        if (d > 1.0f) {
            (*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20 -= d;
        } else {
            (*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20 -= 1.0f;
        }
        if ((*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20 < target) {
            (*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20 = target;
        }
    } else if ((*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20 < target) {
        d = (target - (*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20) * 0.1f;
        if (d > 1.0f) {
            (*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20 += d;
        } else {
            (*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20 += 1.0f;
        }
        if (target < (*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20) {
            (*D_ovl0F_04_800485C4[i].unk0)->unk40->unk20 = target;
        }
    }
}

/* case 0x52's: the panel the player stands on, if it is still up */
static s32 func_ovl0F_04_80043BC0(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (D_ovl0F_04_800487A8[i].unk0 != 0 && D_ovl0F_04_800486CC[i].unk1C == 0.0f &&
            func_ovl0F_04_80047340((s32) D_ovl0F_04_800486CC[i].unkC - 1, (s32) D_ovl0F_04_800486CC[i].unk14 - 1,
                                   (s32) D_ovl0F_04_800486CC[i].unkC, (s32) D_ovl0F_04_800486CC[i].unk14) != 0) {
            return i;
        }
    }
    return -1;
}

/* a task: a panel is stepped on and its block drops */
void func_ovl0F_04_800439DC(void) {
    s32 i;
    UnkStructA *obj;
    s32 k;

    i = D_ovl0F_04_80048AE4;
    if (D_ovl0F_04_800486CC[i].unk1C == 0.0f) {
        func_ovl0F_04_800471B8((s32) D_ovl0F_04_800486CC[i].unkC - 1, (s32) D_ovl0F_04_800486CC[i].unk10,
                               (s32) D_ovl0F_04_800486CC[i].unk14 - 1, (s32) D_ovl0F_04_800486CC[i].unkC,
                               (s32) D_ovl0F_04_800486CC[i].unk14, D_ovl0F_04_800487A8[i].unk4);
    }
    D_ovl0F_04_800487A8[i].unk0 = 0;
    obj = D_ovl0F_04_80048A88[i];
    k = D_ovl0F_04_800487A8[i].unk8;
    do {
        func_ovl0F_04_80047BF8(obj);
        func_ovl0F_04_80047D10();
    } while (obj->unk6C != 0.0f);
    func_ovl0F_04_80048118(0x10, obj->unk40->unk10, obj->unk40->unk14 + 200.0f, obj->unk40->unk18, 0);
    if (k == -1) {
        k = 7;
    }
    func_ovl0F_04_80048198(k, obj->unk40->unk10, obj->unk40->unk14 + 50.0f, obj->unk40->unk18);
    func_ovl0F_04_80047B80(obj, 0x01000000);
    func_ovl0F_04_80047CD8();
}

/* the pushed blocks' callbacks */
void func_ovl0F_04_8004394C(UnkStructA *obj) {
    if (obj->unk8 & 1) {
        func_ovl0F_04_80047270(0x58, 0x16, 2);
    }
    func_ovl0F_04_80043770(obj, D_ovl0F_04_8004848C);
}

void func_ovl0F_04_800438F0(UnkStructA *obj) {
    func_ovl0F_04_80043770(obj, D_ovl0F_04_8004848C);
}

/* the wind pushes a block along x unless it is stopped */
static void func_ovl0F_04_80043770(UnkStructA *obj, f32 speed) {
    Vec3f pos;
    s32 dir;
    s32 saved;
    s32 hit;
    UnkStructA *other;
    s32 k;

    pos.x = obj->unk40->unk10;
    pos.y = obj->unk40->unk14;
    pos.z = obj->unk40->unk18;
    dir = 0x40;
    if (func_ovl0F_04_80047238(obj->unk40) == obj->unk40->unk14) {
        func_ovl0F_04_800481C8(obj, dir, speed);
    } else {
        switch (dir) {
            case 0x00:
                func_ovl0F_04_80043750(obj, speed);
                break;
            case 0x40:
                func_ovl0F_04_80043758(obj, speed);
                break;
            case 0x80:
                func_ovl0F_04_80043760(obj, speed);
                break;
            case 0xC0:
                func_ovl0F_04_80043768(obj, speed);
                break;
        }
    }
    saved = obj->unkC;
    hit = FALSE;
    other = NULL;
    obj->unkC = 0;
    if (obj->unk8 & 1) {
        other = func_ovl0F_04_800473F8(func_ovl0F_04_80047358());
    } else if (obj->unk8 & 2) {
        k = func_ovl0F_04_80047358();
        if (func_ovl0F_04_800473F8(k) == obj) {
            other = func_ovl0F_04_800473B8(k);
        }
    }
    if (other != NULL) {
        if (func_ovl0F_04_80047C98(obj, 0x10, other) != 0) {
            hit = TRUE;
        }
    } else {
        if (func_ovl0F_04_80047B28(obj, 0x10) != 0) {
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

static void func_ovl0F_04_80043768(UnkStructA *obj, f32 speed) {
    obj->unk40->unk10 -= speed;
}

static void func_ovl0F_04_80043760(UnkStructA *obj, f32 speed) {
    obj->unk40->unk18 += speed;
}

static void func_ovl0F_04_80043758(UnkStructA *obj, f32 speed) {
    obj->unk40->unk10 += speed;
}

static void func_ovl0F_04_80043750(UnkStructA *obj, f32 speed) {
    obj->unk40->unk18 -= speed;
}

/* a task: the camera waits for the player to pass x 700 */
void func_ovl0F_04_800436B0(void) {
    UnkStructA *obj;

    obj = func_ovl0F_04_800473B8(func_ovl0F_04_80047358());
    while (700.0f < obj->unk40->unk10) {
        func_ovl0F_04_80047D10();
    }
    func_ovl0F_04_80047CE8(20);
    func_ovl0F_04_80047380(D_ovl0F_04_80048954);
    func_ovl0F_04_80047CD8();
}

/* a block that fell: it sinks into the floor */
void func_ovl0F_04_80043590(UnkStructA *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl0F_04_80047A20(0x10);
    }
    dx = arg0->unk40->unk28 / 30.0f;
    dy = arg0->unk40->unk2C / 30.0f;
    dz = arg0->unk40->unk30 / 30.0f;
    func_ovl0F_04_80047B80(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        arg0->unk40->unk28 -= dx;
        arg0->unk40->unk2C -= dy;
        arg0->unk40->unk30 -= dz;
        func_ovl0F_04_80047BF8(arg0);
        func_ovl0F_04_80047D10();
    }
    func_ovl0F_04_80047B80(arg0, 0x01000000);
}

void func_ovl0F_04_80043530(f32 arg0) {
    f32 sp1C;

    func_ovl0F_04_800479E0(&sp1C, NULL, NULL);
    func_ovl0F_04_800479D8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0F_04_80043480(UnkStruct_ovl0F_04_800485C4 *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *arg0->unk0 = func_ovl0F_04_80047BE8(arg0->unk4, arg0->unk8);
        func_ovl0F_04_80047B78(*arg0->unk0, arg0->unk24 | 0x01000000);
        func_ovl0F_04_800433FC(arg0);
        (*arg0->unk0)->unk40->unk1C = arg0->unk18;
        (*arg0->unk0)->unk40->unk20 = arg0->unk1C;
        (*arg0->unk0)->unk40->unk24 = arg0->unk20;
        arg0++;
    }
}

static void func_ovl0F_04_800433FC(UnkStruct_ovl0F_04_800485C4 *arg0) {
    f32 pos[3];

    func_ovl0F_04_800471D8(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

void func_ovl0F_04_800433A0(s32 *arg0) {
    if (func_ovl0F_04_80047340(arg0[0], arg0[1], arg0[2], arg0[3]) != 0) {
        func_ovl0F_04_80047270(arg0[4], arg0[5], arg0[6]);
    }
}

/* case 2's: the movers and their script */
static void func_ovl0F_04_80045E88(UnkStructA **arg0) {
    UnkStruct_ovl0F_04_800485C4 *p;
    s32 i;

    D_ovl0F_04_80048C90.unk0 = func_ovl0F_04_800473B8(func_ovl0F_04_80047358());
    D_ovl0F_04_80048C90.unk4 = arg0;
    D_ovl0F_04_80048C90.unkC = 0;
    D_ovl0F_04_80048C90.unk10 = 0;
    D_ovl0F_04_80048C90.unk14 = 0;
    D_ovl0F_04_80048C90.unk16 = -1;
    D_ovl0F_04_80048C90.unk8 = 0.0f;
    D_ovl0F_04_800484A0 = 1;
    D_ovl0F_04_80048C90.unk18 = D_ovl0F_04_800484A4;
    D_ovl0F_04_80048C90.unk20 = func_ovl0F_04_80044D34;
    for (i = 0; i < 6; i++) {
        D_ovl0F_04_800485C4[i].unkC = 36.0f;
        D_ovl0F_04_800485C4[i].unk14 = 13.0f;
        D_ovl0F_04_800485C4[i].unk1C = 90.0f;
    }
    p = D_ovl0F_04_800485C4;
    for (i = 0; i < 6; i++) {
        *p->unk0 = func_ovl0F_04_80047BA0(p->unk4, p->unk24 | 0x01000000, 0x30, p->unk8);
        func_ovl0F_04_800433FC(p);
        (*p->unk0)->unk40->unk1C = p->unk18;
        (*p->unk0)->unk40->unk20 = p->unk1C;
        (*p->unk0)->unk40->unk24 = p->unk20;
        p++;
    }
    for (i = 0; i < 6; i++) {
        func_ovl0F_04_80047B78(func_ovl0F_04_80047BB0(*D_ovl0F_04_800485C4[i].unk0), 0x02100000);
        D_ovl0F_04_80048534[i].unk11 = 0;
        D_ovl0F_04_80048C90.unk20(i, 0);
    }
    func_ovl0F_04_800472B0(func_ovl0F_04_800448BC);
    func_ovl0F_04_80047CC8(func_ovl0F_04_80044084, NULL, 0, 0, 0x110);
}

/* the wind: it blows one way from frame 160 to 460, the other from 540 to
 * 720, and the fog moves with it */
void func_ovl0F_04_80043028(void) {
    f32 d;

    if (D_ovl0F_04_80048488 >= 160) {
        if (D_ovl0F_04_80048488 < 460) {
            D_ovl0F_04_80048494 += -30.0f / 300.0f;
            D_ovl0F_04_80048498 += -15.0f / 300.0f;
            func_ovl0F_04_80048008(D_ovl0F_04_80048494, D_ovl0F_04_80048498, 0xE6, 0xF0, 0xFF);
        } else if (D_ovl0F_04_80048488 >= 540 && D_ovl0F_04_80048488 < 720) {
            D_ovl0F_04_80048494 -= -30.0f / 180.0f;
            D_ovl0F_04_80048498 -= -15.0f / 180.0f;
            func_ovl0F_04_80048008(D_ovl0F_04_80048494, D_ovl0F_04_80048498, 0xE6, 0xF0, 0xFF);
        }
    }
    D_ovl0F_04_80048488++;
    if (D_ovl0F_04_80048488 >= 720) {
        D_ovl0F_04_80048488 = 0;
    }
    d = 0.0f;
    if (D_ovl0F_04_80048488 >= 160) {
        if (D_ovl0F_04_80048488 < 460) {
            d = D_ovl0F_04_80048490 / 300.0f;
        } else if (D_ovl0F_04_80048488 >= 540 && D_ovl0F_04_80048488 < 720) {
            d = -(D_ovl0F_04_80048490 / 180.0f);
        }
    }
    D_ovl0F_04_8004848C += d;
    if (2.0f <= D_ovl0F_04_8004848C && D_ovl0F_04_8004849C == 1) {
        D_ovl0F_04_8004849C = 0;
        func_ovl0F_04_80048250(0x89);
    } else if (D_ovl0F_04_8004848C < 2.0f) {
        D_ovl0F_04_8004849C = 1;
    }
    D_ovl0F_04_8004847C = D_ovl0F_04_8004848C * 0.5f;
    D_ovl0F_04_80048480 = 0.0f;
}

static void func_ovl0F_04_80043020(s32 count, UnkStruct_ovl0F_04_800485C4 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_04_80047B90(*p->unk0);
        p++;
    }
}

void func_ovl0F_04_80043010(void) {
}
