/*
 * NON_MATCHING: ovl_0B_03's game object (a four-player set-up screen:
 * three rows of animated background pieces, the players' bombers and
 * their option boxes, driven by one big task, 8004386C), complete: every
 * function and its data (.data 0x770 with the big task's two local cursor
 * tables, .bss 0x1140, as the original's sizes). Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 4, eu 4, jp 66
 *
 * jp (`#if VERSION_JP`) has its own strings (80048AF4, 80048B60,
 * 80049144, and D_ovl0B_03_8004901C_jp for us's 80049168, with the
 * player's digit first) and the label tables' positions that go with
 * them; its text is fixed-width, so 80043234 counts the characters
 * itself (24 pixels each) where us asks ZeroJump 0x250B, and it draws
 * through 0x2501 (800486F0) where us has 0x250C (80048748). The two
 * option-label loops in 8004386C don't centre their text in jp (the
 * label's own x, no 80043234 call), and the second frees the old label
 * before its switch.
 *
 * From m2c (wk/ in scratch/0B_03/ of the main checkout has the scripts,
 * p2/ and p3/ the second and third passes', q/ the fourth's: sd.py is a
 * register/symbol-normalized diff, batch.py and spb2.py variant runners).
 * Functions written last to first. The helpers 8004386C calls
 * (80043010-80043834 but 80043060, 800431FC and 80043834) and 800464B0
 * are static, with the original's own conventions (n in $s2 and the
 * like), and come out in the original's order once 8004386C's last calls
 * are in its order; 80043060, 800431FC and 80043834 are defined above
 * 8004386C so that it pulls them out too. The two fades (80043010,
 * 800433BC) are for loops. The handler's stub at 80047190 is a static
 * freeing n models, inlined twice, and its jump table needs the empty
 * case 17. The four turning tasks wrap the expression itself and test
 * t >= 0.0f before their first pass; the zoom tasks compare t with an
 * int; the display lists are one macro per command. The ZeroJump stubs
 * are declared as other drafts declare the same codes, but 80048890 (the
 * sound) returns s32: as void, uopt kept 8004386C's temporaries in $v0
 * where the original has $v1. The .bss's unreferenced words (800492E0,
 * 8004930C, 8004A33C, 8004A3FC, 8004A418) are arrays, not yet kept in
 * place.
 *
 * 8004386C is a while (TRUE) over switch (state), each case ending
 * state = next, every case a while (TRUE) input loop with the redraw at
 * its end. Its locals are reused as the original's registers show: i in
 * $fp for every counter; state ($s3) also holds case 0's handle, k ($s3)
 * case 2's row, next ($s4) case 2's old label handle, j ($s7) case 2's
 * step; t is the angle in $f22, w the wrap's inner value in $f28 (its
 * home loaded at entry, so it is declared last, and p goes with the
 * scalars above the cursor tables: that gives the original's frame).
 * next is declared with its initializer (set before the tables are
 * copied). A state picked right after a call is set after it, or inside
 * the following if/else's arms (uopt hoists `next = c` above a call
 * before it, and as1 then moves the call's argument into the previous
 * branch's delay slot). Case 2's first label writes its digit before
 * taking the string; case 3/4 indexes its first model by the
 * D_ovl0B_03_8004A330 just stored; case 5 sets t after the second model
 * and copies the box's y before setting its x. The 0x4000 exit of case
 * 3/4 copies each model's own y (E9C[i].unk8), not a -10.0f (m2c's).
 *
 * 80046510's grid is a plain i/j loop writing D_ovl0B_03_8004A340[i][j]
 * directly, the new object stored straight into it and read back from
 * it (through a pointer, uopt doesn't know the stores leave
 * D_ovl0B_03_80049104 alone, and its loads stay below them; an obj local
 * costs a frame slot), with the rows' y as i * 64 + 24 and i * 64 + 88 in
 * the stores: uopt strength-reduces them into the two induction
 * variables it keeps in frame temporaries (84/96(sp)), and their li's
 * come after the la of the table as in the original. The update loop
 * takes the next step into a local.
 *
 * What still differs in us (words): 8004386C 4 (case 1's two spills
 * around 80043340 are at 128/132(sp), the original's at 132/136: uopt
 * leaves 12 bytes between w and them where the original leaves 8. Not
 * the ternaries, the nested calls, the switches, the loops (all tried,
 * one at a time), nor lab: without lab (D_ovl0B_03_80048C90[k]
 * throughout) the spills come out right but w 4 higher, 1 word).
 * Everything else matches.
 *
 * jp builds the same 8004386C but for its #if VERSION_JP parts: the
 * labels and strings, and the second option-label loop, which keeps the
 * old label's handle in state (`state = lab->unk18;` before freeing it)
 * where us keeps it in next until after the new label. That one variable
 * is what keeps &D_ovl0B_03_8004A324 out of a register in jp: uopt's
 * priority for the address is at the edge in this function, and with the
 * handle in next (or freed straight from lab->unk18) it still takes $s0.
 * What still differs in jp (words): 8004386C 66, all stack offsets: the
 * original's frame is 8 smaller (w at 144(sp), the cursor tables and the
 * locals above w 8 lower). w sits 4 nearer the top than in us, so jp has
 * one local fewer between the tables and w (lab, likely: the original jp
 * reaches the label through D_ovl0B_03_80048C90[k], its address in $s3),
 * and its spills are 4 nearer w, as in us; without lab in jp alone the
 * frame stays 312 until that gap is found, so lab stays.
 */

#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

typedef struct Inner Inner;

typedef struct {
    u32 w0;
    u32 w1;
} Gfx_ovl0A_01;

/* A text label: the string, its place, its scale and the handle
 * func_ovl0B_03_80048748 returns for it. */
typedef struct {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} Label_ovl0B_03;

/* A box: its centre, its size, its scale and the object drawing it. */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ UnkStructA_40 *unk14;
} Box_ovl0B_03;

/* A model: what func_ovl0B_03_80047E98 makes, where, and the result. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ UnkStructA_40 *unk10;
} Model_ovl0B_03;

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} Pair_ovl0B_03;

/* A menu's cursor positions (the big task's local tables). */
typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} MenuPos_ovl0B_03;

/* An animated piece of the background: its object, the frames left and
 * the step in D_ovl0B_03_80049104. */
typedef struct {
    /* 0x0 */ UnkStructA_40 *unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Anim_ovl0B_03;

#define WRAP_ovl0B_03(x) ((x) >= 360.0f ? (x) - 360.0f : (x) < 0.0f ? (x) + 360.0f : (x))
#define WRAPW_ovl0B_03(x) ((x) >= 360.0f ? (x) - 360.0f : (w = ((x) < 0.0f ? (x) + 360.0f : (x)), w))
#define GFX_W_ovl0B_03(pkt, a, b) { Gfx_ovl0A_01 *_g = (pkt); _g->w0 = (a); _g->w1 = (b); }

void func_ovl0B_03_800478B0(s32, s32, s32);
s32 func_ovl0B_03_800478B8(void);
s32 *func_ovl0B_03_80047908(void);
UnkStructB *func_ovl0B_03_80047938(void);
void func_ovl0B_03_80047960(s32, s32, s32);
UnkStructA_40 *func_ovl0B_03_80047E98(s32, s32);
void func_ovl0B_03_80047EA0(UnkStructA_40 *);
void func_ovl0B_03_80047EC0(UnkStructA_40 *, s32);
void func_ovl0B_03_80047EC8(UnkStructA_40 *, s32, s32, s32);
void func_ovl0B_03_80047ED8(UnkStructA_40 *, s32);
void func_ovl0B_03_80047EE0(UnkStructA_40 *, s32, s32);
Inner *func_ovl0B_03_80047F18(void (*)(s32, Gfx_ovl0A_01 **), s32);
s32 func_ovl0B_03_80047F28(UnkStructA_40 *, s32);
void func_ovl0B_03_80047FD8(s32);
void func_ovl0B_03_80047FE8(s32);
void func_ovl0B_03_80047FF8(f32, f32, f32);
void func_ovl0B_03_80048018(f32, f32, f32);
void func_ovl0B_03_80048020(f32 *, f32 *, f32 *);
void func_ovl0B_03_80048060(s32);
s32 func_ovl0B_03_80048308(void (*)(void), void *, s32, s32, s32);
void func_ovl0B_03_80048318(void);
void func_ovl0B_03_80048328(s32);
void func_ovl0B_03_80048350(void);
s32 func_ovl0B_03_800483B8();
s32 func_ovl0B_03_800483C8();
s32 func_ovl0B_03_800483D8(s32);
s32 func_ovl0B_03_800483E8(s32);
s32 func_ovl0B_03_80048448();
s32 func_ovl0B_03_80048450(s32);
f32 func_ovl0B_03_800484B8(f32);
UnkStructA_40 *func_ovl0B_03_80048690(s32 (*)(u8, u16), void *, s32, s32, s32);
void func_ovl0B_03_800486A8(void);
s32 func_ovl0B_03_800486D8();
s32 func_ovl0B_03_800486E0();
void func_ovl0B_03_800486F8(s32);
s32 func_ovl0B_03_800486F0(u8 *, u16, u16, f32, f32, s32); /* 0x2501 */
s32 func_ovl0B_03_80048740(u8 *);
s32 func_ovl0B_03_80048748(u8 *, u16, u16, f32, f32, s32);
s32 func_ovl0B_03_80048890(s32);
void func_ovl0B_03_800488A0(s32);
void func_ovl0B_03_800488A8(void);
void func_ovl0B_03_800488B0(s32, f32, f32, f32);
s32 func_ovl0B_03_800489F8(s32);

static void func_ovl0B_03_80043010(void);
void func_ovl0B_03_80043060(s32 arg0);
static void func_ovl0B_03_80043134(Box_ovl0B_03 *boxes, s32 n);
static void func_ovl0B_03_80043170(Box_ovl0B_03 *box, f32 scale);
void func_ovl0B_03_800431FC(void);
static s32 func_ovl0B_03_80043234(u8 *str, f32 scale);
static s32 func_ovl0B_03_800432A0(void);
static s32 func_ovl0B_03_800432F0(void);
static void func_ovl0B_03_80043340(Box_ovl0B_03 *boxes, s32 n, s32 model);
static void func_ovl0B_03_800433BC(void);
static void func_ovl0B_03_80043428(Label_ovl0B_03 *labels, s32 n);
static void func_ovl0B_03_80043464(Label_ovl0B_03 *labels, s32 n);
static void func_ovl0B_03_800434BC(void);
static void func_ovl0B_03_8004368C(s32 obj, s32 *vals);
static void func_ovl0B_03_800436EC(s32 n, Box_ovl0B_03 *boxes, s32 alpha);
void func_ovl0B_03_80043834(void);
void func_ovl0B_03_8004386C(void);
static void func_ovl0B_03_800464B0(Model_ovl0B_03 *models, s32 n);
void func_ovl0B_03_80046510(void);
s32 func_ovl0B_03_80046850(u8 arg0, u16 arg1);
void func_ovl0B_03_80046918(s32 arg0, Gfx_ovl0A_01 **arg1);
void func_ovl0B_03_800469B4(void);
void func_ovl0B_03_80046AE8(void);
void func_ovl0B_03_80046C20(void);
void func_ovl0B_03_80046D54(void);
void func_ovl0B_03_80046E8C(void);
void func_ovl0B_03_80046F78(void);
void func_ovl0B_03_80047064(s32 arg0, Gfx_ovl0A_01 **arg1);
void func_ovl0B_03_80047188(void);
static void func_ovl0B_03_80047190(Model_ovl0B_03 *models, s32 n);
void func_ovl0B_03_80047198(s32 arg0);
void func_ovl0B_03_8004730C(s32 arg0, void *arg1);
void func_ovl0B_03_80047340(f32 arg0);
void func_ovl0B_03_80047388(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0B_03_800473E4(void);
void func_ovl0B_03_800473FC(void);
static void func_ovl0B_03_80047404(void);
static void func_ovl0B_03_8004740C(void);
static void func_ovl0B_03_80047414(void);
static void func_ovl0B_03_8004741C(void);
static void func_ovl0B_03_80047424(void);
static void func_ovl0B_03_8004742C(void);
static void func_ovl0B_03_80047434(void);
static void func_ovl0B_03_8004743C(void);
static void func_ovl0B_03_80047444(void);
static void func_ovl0B_03_8004744C(void);
static void func_ovl0B_03_80047454(void);
static void func_ovl0B_03_8004745C(void);
static void func_ovl0B_03_80047464(void);

/* .data */
u8 D_ovl0B_03_80048AB0[0x38] = {
    0x29, 0x25, 0x1A, 0x32, 0x1E, 0x2B, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00, 0x28, 0x27, 0x00, 0x00, 0x28, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x29, 0x2D, 0x22, 0x28, 0x27, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x28, 0x26, 0x25, 0x1E, 0x2F, 0x1E, 0x25, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x1A, 0x2D, 0x2D, 0x25, 0x1E, 0x00, 0x00,
};
u8 D_ovl0B_03_80048AE8[0xC] = {
    0x13, 0x00, 0x00, 0x00, 0x2D, 0x22, 0x26, 0x1E, 0x00, 0x00, 0x00, 0x00,
};
#if VERSION_JP
u8 D_ovl0B_03_80048AF4[0x60] = {
    0x12, 0x0F, 0x26, 0x22, 0x27, 0x00, 0x00, 0x00, 0x27, 0x28, 0x0F, 0x25, 0x22, 0x26, 0x22, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x6A, 0x9A, 0x5F, 0x99, 0x6C, 0x00, 0x00, 0x00, 0x90, 0xF9, 0x6C, 0x73, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x21, 0x1A, 0x2B, 0x1A, 0x1C, 0x2D, 0x1E, 0x2B, 0x0F, 0x2D, 0x32, 0x29, 0x1E, 0x00, 0x00, 0x1C, 0x28, 0x27, 0x1F, 0x22, 0x20, 0x00, 0x00, 0x1F, 0x22, 0x25, 0x1E, 0x0F, 0x10, 0x00, 0x00, 0x2C, 0x2D, 0x1A, 0x20, 0x1E, 0x0F, 0x2C, 0x1E, 0x25, 0x1E, 0x1C, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x2D, 0x1A, 0x20, 0x1E, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#else
u8 D_ovl0B_03_80048AF4[0x6C] = {
    0x12, 0x0F, 0x26, 0x22, 0x27, 0x00, 0x00, 0x00, 0x27, 0x28, 0x0F, 0x25, 0x22, 0x26, 0x22, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x2E, 0x1D, 0x1D, 0x1E, 0x27, 0xFF, 0x0F, 0x0F, 0x0F, 0x1D, 0x1E, 0x1A, 0x2D, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21, 0x28, 0x2C, 0x2D, 0x00, 0x00, 0x00, 0x1C, 0x21, 0x1A, 0x2B, 0x1A, 0x1C, 0x2D, 0x1E, 0x2B, 0x0F, 0x2D, 0x32, 0x29, 0x1E, 0x00, 0x00, 0x1C, 0x28, 0x27, 0x1F, 0x22, 0x20, 0x00, 0x00, 0x1F, 0x22, 0x25, 0x1E, 0x0F, 0x10, 0x00, 0x00, 0x2C, 0x2D, 0x1A, 0x20, 0x1E, 0x0F, 0x2C, 0x1E, 0x25, 0x1E, 0x1C, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x2D, 0x1A, 0x20, 0x1E, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#endif
#if VERSION_JP
u8 D_ovl0B_03_80048B60[0x88] = {
    0xD0, 0xBD, 0xB1, 0xDF, 0xAF, 0x00, 0x00, 0x00, 0xB4, 0xD1, 0xE9, 0xC3, 0xB2, 0xF6, 0x00, 0x00, 0xBA, 0xB1, 0xBB, 0xAD, 0xC8, 0x9B, 0x73, 0x88, 0x00, 0x00, 0x00, 0x00, 0xB2, 0xB3, 0xCC, 0x0F, 0xBB, 0xBF, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x86, 0x7F, 0x5A, 0x9A, 0x00, 0x00, 0x00, 0xD5, 0xB7, 0xEB, 0xD7, 0x0F, 0xC9, 0xCE, 0xD9, 0x00, 0x00, 0x00, 0x00, 0xC2, 0xAF, 0xE0, 0xB7, 0x0F, 0xE2, 0xE0, 0xB7, 0x00, 0x00, 0x00, 0x00, 0xB7, 0xBA, 0xEB, 0xC8, 0xB5, 0xDF, 0xE9, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCF, 0xE3, 0xC8, 0xBD, 0xBD, 0xD6, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB5, 0xB1, 0xE5, 0xB7, 0xBD, 0xAF, 0x00, 0x00, 0x9D, 0x87, 0x91, 0xF9, 0x9A, 0x9B, 0x73, 0x88, 0x00, 0x00, 0x00, 0x00, 0x71, 0x88, 0x71, 0x88, 0x8C, 0x86, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xF9, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#else
u8 D_ovl0B_03_80048B60[0xC0] = {
    0x2E, 0x27, 0x25, 0x22, 0x26, 0x22, 0x2D, 0x1E, 0x1D, 0x00, 0x00, 0x00, 0x1C, 0x48, 0x47, 0x40, 0x4B, 0x3A, 0x4D, 0x4E, 0x45, 0x3A, 0x4D, 0x42, 0x48, 0x47, 0x4C, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x48, 0x3C, 0x44, 0x0F, 0x20, 0x3A, 0x4B, 0x3D, 0x3E, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x49, 0x0F, 0x3A, 0x47, 0x3D, 0x0F, 0x1D, 0x48, 0x50, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x52, 0x4B, 0x3A, 0x46, 0x42, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x4B, 0x3E, 0x3E, 0x3D, 0x52, 0x0F, 0x2D, 0x4B, 0x3A, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D, 0x48, 0x49, 0x0F, 0x2B, 0x4E, 0x45, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x1F, 0x42, 0x3E, 0x45, 0x3D, 0x0F, 0x48, 0x3F, 0x0F, 0x20, 0x4B, 0x3A, 0x4C, 0x4C, 0x00, 0x00, 0x22, 0x47, 0x0F, 0x4D, 0x41, 0x3E, 0x0F, 0x20, 0x4E, 0x4D, 0x4D, 0x3E, 0x4B, 0x00, 0x00, 0x00, 0x2C, 0x3E, 0x3A, 0x0F, 0x2C, 0x42, 0x3C, 0x44, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x45, 0x42, 0x53, 0x53, 0x3A, 0x4B, 0x3D, 0x0F, 0x1B, 0x3A, 0x4D, 0x4D, 0x45, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x48, 0x4C, 0x4D, 0x0F, 0x3A, 0x4D, 0x0F, 0x2C, 0x3E, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D, 0x3E, 0x3A, 0x46, 0x00, 0x00, 0x00, 0x00,
};
#endif
#if VERSION_JP
Label_ovl0B_03 D_ovl0B_03_80048C20[4] = {
    { (u8 *)D_ovl0B_03_80048AB0 + 0x30, 0, 0x4F, 0, 0x50, 0.6f, 0.6f, 5, 0 },
    { (u8 *)D_ovl0B_03_80048AE8 + 0x4, 0, 0x4F, 0, 0x6E, 0.6f, 0.6f, 5, 0 },
    { (u8 *)D_ovl0B_03_80048AF4 + 0x14, 0, 0x4F, 0, 0x8C, 0.6f, 0.6f, 5, 0 },
    { (u8 *)D_ovl0B_03_80048AF4 + 0x1C, 0, 0x4F, 0, 0xAA, 0.6f, 0.6f, 5, 0 },
};
#else
Label_ovl0B_03 D_ovl0B_03_80048C20[4] = {
    { (u8 *)D_ovl0B_03_80048AB0 + 0x30, 0, 0x4F, 0, 0x50, 0.6f, 0.6f, 5, 0 },
    { (u8 *)D_ovl0B_03_80048AE8 + 0x4, 0, 0x4F, 0, 0x6E, 0.6f, 0.6f, 5, 0 },
    { (u8 *)D_ovl0B_03_80048AF4 + 0x14, 0, 0x4F, 0, 0x84, 0.6f, 0.6f, 5, 0 },
    { (u8 *)D_ovl0B_03_80048AF4 + 0x28, 0, 0x4F, 0, 0xAA, 0.6f, 0.6f, 5, 0 },
};
#endif
#if VERSION_JP
Label_ovl0B_03 D_ovl0B_03_80048C90[4] = {
    { (u8 *)D_ovl0B_03_80048AE8, 0, 0xBA, 0, 0x50, 0.6f, 0.6f, 2, 0 },
    { (u8 *)D_ovl0B_03_80048AF4, 0, 0xBA, 0, 0x6E, 0.6f, 0.6f, 2, 0 },
    { (u8 *)D_ovl0B_03_80048AB0 + 0xC, 0, 0xBA, 0, 0x8C, 0.6f, 0.6f, 0, 0 },
    { (u8 *)D_ovl0B_03_80048AB0 + 0xC, 0, 0xBA, 0, 0xAA, 0.6f, 0.6f, 0, 0 },
};
#else
Label_ovl0B_03 D_ovl0B_03_80048C90[4] = {
    { (u8 *)D_ovl0B_03_80048AE8, 0, 0xA6, 0, 0x50, 0.6f, 0.6f, 2, 0 },
    { (u8 *)D_ovl0B_03_80048AF4, 0, 0xA6, 0, 0x6E, 0.6f, 0.6f, 2, 0 },
    { (u8 *)D_ovl0B_03_80048AB0 + 0xC, 0, 0xA6, 0, 0x8C, 0.6f, 0.6f, 0, 0 },
    { (u8 *)D_ovl0B_03_80048AB0 + 0xC, 0, 0xA6, 0, 0xAA, 0.6f, 0.6f, 0, 0 },
};
#endif
u8 *D_ovl0B_03_80048D00[2] = { D_ovl0B_03_80048AB0 + 0x10, D_ovl0B_03_80048AB0 + 0xC };
Model_ovl0B_03 D_ovl0B_03_80048D08[4] = {
    { 0x32, 0.0f, 0.0f, 0.0f, NULL },
    { 0x33, 0.0f, 85.0f, 0.0f, NULL },
    { 0x34, 115.0f, 0.0f, 0.0f, NULL },
    { 0x34, -115.0f, 0.0f, 0.0f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80048D58[3] = {
    { 160.0f, 84.0f, 160.0f, 50.0f, 0.7f, NULL },
    { 160.0f, 134.0f, 160.0f, 50.0f, 0.7f, NULL },
    { 160.0f, 184.0f, 160.0f, 50.0f, 0.7f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80048DA0[8] = {
    { 85.0f, 170.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 135.0f, 170.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 185.0f, 170.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 235.0f, 170.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 85.0f, 190.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 135.0f, 190.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 185.0f, 190.0f, 40.0f, 20.0f, 1.0f, NULL },
    { 235.0f, 190.0f, 40.0f, 20.0f, 1.0f, NULL },
};
f32 D_ovl0B_03_80048E60[3] = { 114.0f, 170.0f, 190.0f };
Box_ovl0B_03 D_ovl0B_03_80048E6C[1] = {
    { 55.0f, 114.0f, 20.0f, 20.0f, 0.7f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80048E84[1] = {
    { 115.0f, 114.0f, 20.0f, 20.0f, 0.7f, NULL },
};
Model_ovl0B_03 D_ovl0B_03_80048E9C[4] = {
    { 0x49, -75.0f, -10.0f, 0.0f, NULL },
    { 0x49, -24.0f, -10.0f, 0.0f, NULL },
    { 0x49, 24.0f, -10.0f, 0.0f, NULL },
    { 0x49, 75.0f, -10.0f, 0.0f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80048EEC[12] = {
    { 71.7f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 85.0f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 98.299995f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 121.7f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 135.0f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 148.3f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 171.7f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 185.0f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 198.3f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 221.7f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 235.0f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
    { 248.3f, 190.0f, 10.0f, 20.0f, 1.0f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_8004900C[1] = {
    { 160.0f, 136.0f, 160.0f, 20.0f, 1.0f, NULL },
};
Box_ovl0B_03 D_ovl0B_03_80049024[2] = {
    { 138.0f, 68.0f, 16.0f, 16.0f, 1.0f, NULL },
    { 138.0f, 198.0f, 16.0f, 16.0f, 1.0f, NULL },
};
#if VERSION_JP
Label_ovl0B_03 D_ovl0B_03_80049054[2] = {
    { (u8 *)D_ovl0B_03_80048B60 + 0x80, 0, 0x90, 0, 0x3C, 0.7f, 0.7f, 2, 0 },
    { (u8 *)D_ovl0B_03_80048B60 + 0x80, 0, 0x90, 0, 0xBE, 0.7f, 0.7f, 2, 0 },
};
#else
Label_ovl0B_03 D_ovl0B_03_80049054[2] = {
    { (u8 *)D_ovl0B_03_80048B60 + 0xB8, 0, 0x90, 0, 0x3C, 0.7f, 0.7f, 2, 0 },
    { (u8 *)D_ovl0B_03_80048B60 + 0xB8, 0, 0x90, 0, 0xBE, 0.7f, 0.7f, 2, 0 },
};
#endif
s32 D_ovl0B_03_8004908C[10] = { 0x201, 0x202, 0x206, 0x208, 0x20D, 0x211, 0x212, 0x216, 0x217, 0x218 };
s32 D_ovl0B_03_800490B4[10] = { -1, 0x203, -1, -1, 0x210, -1, 0x215, -1, -1, 0x352 };
f32 D_ovl0B_03_800490DC[10] = { 0.0f, -20.0f, -20.0f, 0.0f, 0.0f, -20.0f, -20.0f, -40.0f, 0.0f, 0.0f };
Pair_ovl0B_03 D_ovl0B_03_80049104[8] = { { 0, 60 }, { 2, 60 }, { 4, 10 }, { 6, 10 }, { 4, 10 }, { 6, 10 }, { 4, 20 }, { 6, 60 } };
#if VERSION_JP
u8 D_ovl0B_03_80049144[0x1C] = {
    0x69, 0x5F, 0x73, 0x8A, 0xF9, 0x86, 0xA0, 0x5A, 0x67, 0x99, 0xF9, 0x6F, 0xAE, 0xFF, 0x0F, 0x0F, 0xD5, 0xCF, 0xB9, 0xAF, 0xE9, 0xB1, 0xCE, 0xBC, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_03_8004901C_jp[0x20] = {
    0x10, 0xEB, 0xAF, 0xC8, 0x69, 0x5F, 0x73, 0x8A, 0xF9, 0x86, 0xA0, 0x5A, 0x67, 0xDC, 0xFF, 0x0F, 0x63, 0x86, 0xF9, 0xE9, 0xD5, 0xD1, 0xCE, 0xBD, 0xAF, 0xE9, 0xBB, 0xBF, 0x00, 0x00, 0x00, 0x00,
};
#else
u8 D_ovl0B_03_80049144[0x24] = {
    0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0x42, 0x47, 0x40, 0xFF, 0x0F, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00,
};
u8 D_ovl0B_03_80049168[0x2C] = {
    0x1C, 0x48, 0x4E, 0x45, 0x3D, 0x0F, 0x27, 0x48, 0x4D, 0x0F, 0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0xFF, 0x0F, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#endif
#if VERSION_JP
u8 *D_ovl0B_03_80049194[10] = { D_ovl0B_03_80048B60 + 0x10, D_ovl0B_03_80048B60 + 0x1C, D_ovl0B_03_80048B60 + 0x28, D_ovl0B_03_80048B60 + 0x30, D_ovl0B_03_80048B60 + 0x3C, D_ovl0B_03_80048B60 + 0x48, D_ovl0B_03_80048B60 + 0x54, D_ovl0B_03_80048B60 + 0x60, D_ovl0B_03_80048B60 + 0x68, D_ovl0B_03_80048B60 + 0x74 };
#else
u8 *D_ovl0B_03_80049194[10] = { D_ovl0B_03_80048B60 + 0x20, D_ovl0B_03_80048B60 + 0x30, D_ovl0B_03_80048B60 + 0x40, D_ovl0B_03_80048B60 + 0x4C, D_ovl0B_03_80048B60 + 0x5C, D_ovl0B_03_80048B60 + 0x68, D_ovl0B_03_80048B60 + 0x78, D_ovl0B_03_80048B60 + 0x88, D_ovl0B_03_80048B60 + 0x94, D_ovl0B_03_80048B60 + 0xA8 };
#endif

/* .bss */
u8 D_ovl0B_03_800492E0[0x24];
s32 D_ovl0B_03_80049304;
s32 D_ovl0B_03_80049308;
u8 D_ovl0B_03_8004930C[4];
f32 D_ovl0B_03_80049310[3];
s32 D_ovl0B_03_8004931C;
u8 D_ovl0B_03_80049320[0x1000];
s32 D_ovl0B_03_8004A320;
UnkStructB *D_ovl0B_03_8004A324;
s32 D_ovl0B_03_8004A328;
s32 D_ovl0B_03_8004A32C;
s32 D_ovl0B_03_8004A330;
UnkStructA_40 *D_ovl0B_03_8004A334;
UnkStructA_40 *D_ovl0B_03_8004A338;
u8 D_ovl0B_03_8004A33C[4];
Anim_ovl0B_03 D_ovl0B_03_8004A340[3][5];
Inner *D_ovl0B_03_8004A3F4;
UnkStructA_40 *D_ovl0B_03_8004A3F8;
u8 D_ovl0B_03_8004A3FC[4];
s32 D_ovl0B_03_8004A400[4];
s32 D_ovl0B_03_8004A410;
s32 D_ovl0B_03_8004A414;
u8 D_ovl0B_03_8004A418[8];

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047464(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004745C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047454(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004744C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047444(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004743C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047434(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004742C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047424(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004741C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047414(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_8004740C(void) {
}

/* An unused empty static (the original keeps its stub). */
static void func_ovl0B_03_80047404(void) {
}

void func_ovl0B_03_800473FC(void) {

}

void func_ovl0B_03_800473E4(void) {
    D_ovl0B_03_80049304 = -1;
    D_ovl0B_03_80049308 = -1;
}

void func_ovl0B_03_80047388(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0B_03_80047FF8(M2C_FIELD(&D_ovl0B_03_80049310, f32 *, 0), M2C_FIELD(&D_ovl0B_03_80049310, f32 *, 4), M2C_FIELD(&D_ovl0B_03_80049310, f32 *, 8));
    func_ovl0B_03_80048018(arg0, arg1, arg2);
    func_ovl0B_03_80048328(0xB4);
}

void func_ovl0B_03_80047340(f32 arg0) {
    f32 sp1C;

    func_ovl0B_03_80048020(&sp1C, NULL, NULL);
    func_ovl0B_03_80048018(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0B_03_8004730C(s32 arg0, void *arg1) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg1, void **, 0x40);
    func_ovl0B_03_800488B0(arg0, M2C_FIELD(temp_v0, f32 *, 0x10), M2C_FIELD(temp_v0, f32 *, 0x14), M2C_FIELD(temp_v0, f32 *, 0x18));
}

void func_ovl0B_03_80047198(s32 arg0) {
    s32 i;
    s32 j;

    switch (arg0) {
    case 2:
        D_ovl0B_03_8004931C = func_ovl0B_03_800478B8();
        func_ovl0B_03_800488A0(0x1D);
        return;
    case 16:
        func_ovl0B_03_80048308(func_ovl0B_03_8004386C, NULL, (s32) &D_ovl0B_03_80049320, 0x1000, 0x130);
        func_ovl0B_03_80048308(func_ovl0B_03_80046510, NULL, 0, 0, 0x130);
        return;
    case 1:
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 5; j++) {
                func_ovl0B_03_80047EA0(D_ovl0B_03_8004A340[i][j].unk0);
            }
        }
        func_ovl0B_03_80047190(D_ovl0B_03_80048D08, 4);
        func_ovl0B_03_80047190(D_ovl0B_03_80048E9C, 4);
        return;
    case 12:
        func_ovl0B_03_800488A8();
        return;
    case 17:
        return;
    }
}

static void func_ovl0B_03_80047190(Model_ovl0B_03 *models, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0B_03_80047EA0(models[i].unk10);
    }
}

void func_ovl0B_03_80047188(void) {

}

void func_ovl0B_03_80047064(s32 arg0, Gfx_ovl0A_01 **arg1) {
    Gfx_ovl0A_01 *g;

    g = *arg1;
    GFX_W_ovl0B_03(g++, 0xFA000000, 0xFF0080);
    GFX_W_ovl0B_03(g++, 0xFCFFFFFF, 0xFFFDF6FB);
    GFX_W_ovl0B_03(g++, 0xF7000000, 0x10001);
    GFX_W_ovl0B_03(g++,
                   0xF6000000 | (((D_ovl0B_03_8004A414 + 160) & 0x3FF) << 14) |
                       ((((s32) (D_ovl0B_03_8004A414 * 0.72f) + 136) & 0x3FF) << 2),
                   (((160 - D_ovl0B_03_8004A414) & 0x3FF) << 14) |
                       (((136 - (s32) (D_ovl0B_03_8004A414 * 0.72f)) & 0x3FF) << 2));
    *arg1 = g;
}

void func_ovl0B_03_80046F78(void) {
    f32 t;

    for (t = -60.0f; t < 0; t += 1.0f) {
        func_ovl0B_03_80048018(0.0f, 0.0f, t * t * -0.061f + 420.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046E8C(void) {
    f32 t;

    for (t = 0; t > -60.0f; t -= 1.0f) {
        func_ovl0B_03_80048018(0.0f, 0.0f, t * t * -0.061f + 420.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046D54(void) {
    f32 t;
    f32 a;

    a = M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C);
    for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
        M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C) = WRAP_ovl0B_03(t * t * 0.225f + a - 90.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046C20(void) {
    f32 t;
    f32 a;

    a = M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C);
    for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
        M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C) = WRAP_ovl0B_03(t * t * -0.225f + a + 90.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046AE8(void) {
    f32 t;
    f32 a;

    a = M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C);
    for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
        M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C) = WRAP_ovl0B_03(t * t * 0.45f + a - 180.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_800469B4(void) {
    f32 t;
    f32 a;

    a = M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C);
    for (t = 20.0f; t >= 0.0f; t -= 1.0f) {
        M2C_FIELD(D_ovl0B_03_80048D08[1].unk10, f32 *, 0x1C) = WRAP_ovl0B_03(t * t * -0.45f + a + 180.0f);
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048318();
}

void func_ovl0B_03_80046918(s32 arg0, Gfx_ovl0A_01 **arg1) {
    Gfx_ovl0A_01 *g;

    g = *arg1;
    GFX_W_ovl0B_03(g++, 0xFA000000, 0xFFFFFF80);
    GFX_W_ovl0B_03(g++, 0xFCFFFFFF, 0xFFFDF6FB);
    GFX_W_ovl0B_03(g++, 0xF7000000, 0x10001);
    GFX_W_ovl0B_03(g++, 0xF6000000 | (((D_ovl0B_03_8004A410 + 109) & 0x3FF) << 14) | ((207 & 0x3FF) << 2),
                   (((D_ovl0B_03_8004A410 + 60) & 0x3FF) << 14) | ((68 & 0x3FF) << 2));
    *arg1 = g;
}

s32 func_ovl0B_03_80046850(u8 arg0, u16 arg1) {
    s32 b;
    s32 p;

    b = arg1;
    p = arg0;
    if (b & 1) {
        func_ovl0B_03_80048890(1);
        D_ovl0B_03_8004A320 = -1;
        return 0;
    }
    if (b & 2) {
        func_ovl0B_03_80048890(2);
        D_ovl0B_03_8004A320 = -2;
        return 0;
    }
    if (b & 0x180) {
        if (b & 0x80) {
            D_ovl0B_03_8004A320 = p + 0x10;
            return 0;
        }
        if (b & 0x100) {
            D_ovl0B_03_8004A320 = p + 0x20;
        }
        return 0;
    }
    if (b & 0x60) {
        return 1;
    }
    return 1;
}

void func_ovl0B_03_80046510(void) {
    s32 i;
    s32 j;
    Anim_ovl0B_03 *a;
    s32 n;

    func_ovl0B_03_800464B0(D_ovl0B_03_80048D08, 4);
    D_ovl0B_03_80048D08[2].unk10->unkC |= 0x80;
    D_ovl0B_03_80048D08[3].unk10->unkC |= 0x80;
    func_ovl0B_03_800464B0(D_ovl0B_03_80048E9C, 4);
    for (i = 0; i < 4; i++) {
        D_ovl0B_03_80048E9C[i].unk10->unk30 = 0.4f;
        D_ovl0B_03_80048E9C[i].unk10->unk28 = D_ovl0B_03_80048E9C[i].unk10->unk2C = D_ovl0B_03_80048E9C[i].unk10->unk30;
        func_ovl0B_03_80047ED8(D_ovl0B_03_80048E9C[i].unk10, 2);
        func_ovl0B_03_80047EE0(D_ovl0B_03_80048E9C[i].unk10, 1, 0);
        func_ovl0B_03_80047EE0(D_ovl0B_03_80048E9C[i].unk10, 2, 1);
        D_ovl0B_03_80048E9C[i].unk10->unkC |= 0x41;
        func_ovl0B_03_80047EC0(D_ovl0B_03_80048E9C[i].unk10, 0xC);
        for (j = 0; j < 12; j++) {
            func_ovl0B_03_80047EC8(D_ovl0B_03_80048E9C[i].unk10, i + 0x4A, j, j);
        }
        D_ovl0B_03_8004A400[i] = func_ovl0B_03_80047F28(D_ovl0B_03_80048E9C[i].unk10, 0xF);
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 5; j++) {
            D_ovl0B_03_8004A340[i][j].unk0 = func_ovl0B_03_80047E98(0x30, 0);
            D_ovl0B_03_8004A340[i][j].unk8 = (i + j) & 3;
            D_ovl0B_03_8004A340[i][j].unk4 = D_ovl0B_03_80049104[(i + j) & 3].unk4;
            M2C_FIELD(D_ovl0B_03_8004A340[i][j].unk0, s32 *, 0x38) = D_ovl0B_03_80049104[(i + j) & 3].unk0;
            D_ovl0B_03_8004A340[i][j].unk0->unk10 = j * 64;
            D_ovl0B_03_8004A340[i][j].unk0->unk14 = i * 64 + 24;
            D_ovl0B_03_8004A340[i][j].unk0->unk18 = j * 64 + 64;
            D_ovl0B_03_8004A340[i][j].unk0->unk1C = i * 64 + 88;
            D_ovl0B_03_8004A340[i][j].unk0->unkC |= 0x400;
        }
    }
    while (TRUE) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 5; j++) {
                a = &D_ovl0B_03_8004A340[i][j];
                if (--a->unk4 == 0) {
                    n = a->unk8 + 1;
                    if (n >= 8) {
                        n = 0;
                    }
                    a->unk8 = n;
                    a->unk4 = D_ovl0B_03_80049104[n].unk4;
                    M2C_FIELD(a->unk0, s32 *, 0x38) = D_ovl0B_03_80049104[n].unk0;
                }
            }
        }
        func_ovl0B_03_80048350();
    }
}


/* The original passes n in $s2 (its callers' register). */
static void func_ovl0B_03_800464B0(Model_ovl0B_03 *models, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        models[i].unk10 = func_ovl0B_03_80047E98(models[i].unk0, 0);
        models[i].unk10->unk10 = models[i].unk4;
        models[i].unk10->unk14 = models[i].unk8;
        models[i].unk10->unk18 = models[i].unkC;
    }
}

void func_ovl0B_03_80043834(void) {
    func_ovl0B_03_80048308(func_ovl0B_03_80046F78, NULL, 0, 0, 0x130);
}

void func_ovl0B_03_800431FC(void) {
    func_ovl0B_03_80048308(func_ovl0B_03_80046E8C, NULL, 0, 0, 0x130);
}

void func_ovl0B_03_80043060(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        func_ovl0B_03_80048308(func_ovl0B_03_80046D54, NULL, 0, 0, 0x130);
        return;
    case 1:
        func_ovl0B_03_80048308(func_ovl0B_03_80046C20, NULL, 0, 0, 0x130);
        return;
    case 2:
        func_ovl0B_03_80048308(func_ovl0B_03_80046AE8, NULL, 0, 0, 0x130);
        return;
    case 3:
        func_ovl0B_03_80048308(func_ovl0B_03_800469B4, NULL, 0, 0, 0x130);
        return;
    }
}

void func_ovl0B_03_8004386C(void) {
    s32 state;
    s32 next = 0;
    s32 btn;
    s32 held;
    u8 *str;
    s32 j;
    s32 k;
    s32 sel;
    s32 dir;
    s32 v28;
    s32 v38;
    s32 v3C;
    s32 max;
    s32 h;
    s32 *p;
    MenuPos_ovl0B_03 spCC[6] = { { 71, 87, 0, 2, 0, 0 }, { 71, 117, 1, 3, 0, 0 }, { 71, 147, 2, 4, 0, 0 }, { 71, 177, 3, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } };
    MenuPos_ovl0B_03 spA4[5] = { { 172, 78, 0, 2, 0, 0 }, { 172, 108, 1, 3, 0, 0 }, { 172, 138, 2, 4, 0, 0 }, { 172, 168, 3, 5, 0, 0 }, { 172, 198, 4, 0, 0, 0 } };
    s32 i;
    f32 t;
    Label_ovl0B_03 *lab;
    f32 w;

    D_ovl0B_03_8004A324 = func_ovl0B_03_80047938();
    func_ovl0B_03_80048060(0x7F);
    func_ovl0B_03_80047FD8(1);
    func_ovl0B_03_80047FF8(0.0f, 10.0f, 0.0f);
    func_ovl0B_03_80047FE8(1);
    func_ovl0B_03_80043834();
    func_ovl0B_03_80048328(0xA);
    D_ovl0B_03_8004A328 = 0;
    p = func_ovl0B_03_80047908();
    max = 5;
    if ((func_ovl0B_03_800489F8(2) != 0) || (M2C_FIELD(p, s32 *, 0x44) != 0)) {
        max = 7;
    }
    if ((func_ovl0B_03_800489F8(1) != 0) || (M2C_FIELD(p, s32 *, 0x44) != 0)) {
        max = 9;
    }
    state = next;
    while (TRUE) {
        switch (state) {
        case 0:
            func_ovl0B_03_80043340(D_ovl0B_03_80048D58, 3, 0x31);
            t = 0.0f;
            func_ovl0B_03_80043170(&D_ovl0B_03_80048D58[D_ovl0B_03_8004A324->unk0], func_ovl0B_03_800484B8(WRAPW_ovl0B_03(t)) * 0.05f + 1.0f);
            for (i = 0; i != 0x108; i += 8) {
                func_ovl0B_03_800436EC(3, D_ovl0B_03_80048D58, i);
                func_ovl0B_03_80048350();
            }
            while (TRUE) {
                btn = func_ovl0B_03_800432F0();
                held = func_ovl0B_03_800432A0();
                if (btn & 0x400) {
                    if (D_ovl0B_03_8004A324->unk0 < 2) {
                        D_ovl0B_03_8004A324->unk0++;
                        func_ovl0B_03_80048890(0);
                    }
                } else if (btn & 0x800) {
                    if (D_ovl0B_03_8004A324->unk0 > 0) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_8004A324->unk0--;
                    }
                } else if (held & 0x8000) {
                    func_ovl0B_03_80048890(1);
                    if (D_ovl0B_03_8004A324->unk0 == 2) {
                        next = 2;
                    } else {
                        next = 1;
                        func_ovl0B_03_80043060(1);
                    }
                    for (i = 0xF8; i > 0; i -= 8) {
                        func_ovl0B_03_800436EC(3, D_ovl0B_03_80048D58, i);
                        func_ovl0B_03_80048350();
                    }
                    if (next == 1) {
                        j = 0;
                        func_ovl0B_03_800483B8();
                        for (i = 0; i < 4; i++) {
                            j |= func_ovl0B_03_800483C8(i);
                        }
                        if (j & 1) {
#if VERSION_JP
                            state = func_ovl0B_03_800486F0(D_ovl0B_03_80049144, 0x42, 0x6E, 0.6f, 0.6f, 2);
#else
                            state = func_ovl0B_03_80048748(D_ovl0B_03_80049144, 0x42, 0x6E, 0.6f, 0.6f, 2);
#endif
                            func_ovl0B_03_80048328(2);
                            func_ovl0B_03_80048448();
                            func_ovl0B_03_80048328(2);
                            func_ovl0B_03_800486F8(state);
                            func_ovl0B_03_80048328(4);
                        }
                        for (i = 0; i != 4; i++) {
                            if (func_ovl0B_03_800483C8(i) & 1) {
                                k = func_ovl0B_03_80048450(i);
                                if (k != 9 && k != 7) {
#if VERSION_JP
                                    D_ovl0B_03_8004901C_jp[0] = i + 0x11;
                                    func_ovl0B_03_80048890(0x18);
                                    state = func_ovl0B_03_800486F0(D_ovl0B_03_8004901C_jp, 0x42, 0x6E, 0.6f, 0.6f, 3);
#else
                                    D_ovl0B_03_80049168[0x26] = i + 0x11;
                                    func_ovl0B_03_80048890(0x18);
                                    state = func_ovl0B_03_80048748(D_ovl0B_03_80049168, 0x42, 0x6E, 0.6f, 0.6f, 3);
#endif
                                    func_ovl0B_03_80048328(0xB4);
                                    func_ovl0B_03_800486F8(state);
                                    func_ovl0B_03_80048328(4);
                                }
                            }
                        }
                    }
                    func_ovl0B_03_80043134(D_ovl0B_03_80048D58, 3);
                    func_ovl0B_03_80048350();
                    break;
                } else if (held & 0x4000) {
                    func_ovl0B_03_80048890(0x25);
                    func_ovl0B_03_800431FC();
                    for (i = 0xF8; i != 0; i -= 8) {
                        func_ovl0B_03_800436EC(3, D_ovl0B_03_80048D58, i);
                        func_ovl0B_03_80048350();
                    }
                    func_ovl0B_03_80043134(D_ovl0B_03_80048D58, 3);
                    func_ovl0B_03_800478B0(0x20, 0x11, 0);
                    while (TRUE) {
                        func_ovl0B_03_80048350();
                    }
                }
                for (i = 0; i < 3; i++) {
                    func_ovl0B_03_80043170(&D_ovl0B_03_80048D58[i], 0.7f);
                }
                func_ovl0B_03_80043170(&D_ovl0B_03_80048D58[D_ovl0B_03_8004A324->unk0], func_ovl0B_03_800484B8(WRAPW_ovl0B_03(t)) * 0.05f + 1.0f);
                t += 4.0f;
                func_ovl0B_03_80048350();
            }
            state = next;
            break;
        case 1:
            func_ovl0B_03_800433BC();
            D_ovl0B_03_8004A3F4 = func_ovl0B_03_80047F18(func_ovl0B_03_80046918, 0);
            M2C_FIELD(D_ovl0B_03_8004A3F4, s32 *, 0xC) |= 0x480;
            D_ovl0B_03_8004A410 = D_ovl0B_03_8004A328 * 50;
            D_ovl0B_03_8004A32C = 0;
            func_ovl0B_03_80043340(D_ovl0B_03_80048DA0, 8, 0x35);
            func_ovl0B_03_80043340(D_ovl0B_03_80048E6C, 2, 0x39);
            for (i = 0; i < 4; i++) {
                func_ovl0B_03_80043340(&D_ovl0B_03_80048EEC[i * 3], 3, 0x3A);
                for (j = 0; j < 3; j++) {
                    M2C_FIELD(D_ovl0B_03_80048EEC[i * 3 + j].unk14, s32 *, 0x38) = 0;
                }
            }
            for (i = 0; i < 4; i++) {
                D_ovl0B_03_80048E9C[i].unk10->unkC &= ~1;
                if (func_ovl0B_03_80048450(i) != 9) {
                    D_ovl0B_03_8004A324->unk40[i] = 0;
                }
                if (D_ovl0B_03_8004A324->unk4[i] == 1 && D_ovl0B_03_8004A324->unk40[i] == 1) {
                    func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[i], D_ovl0B_03_8004A324->unk50[i]);
                } else {
                    func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[i], NULL);
                }
            }
            D_ovl0B_03_80048E9C[D_ovl0B_03_8004A328].unk10->unkC &= ~0x40;
            t = 0.0f;
            func_ovl0B_03_800434BC();
            while (TRUE) {
                btn = func_ovl0B_03_800432F0();
                held = func_ovl0B_03_800432A0();
                if ((btn & 0x800) || (held & 8)) {
                    if (D_ovl0B_03_8004A32C > 0) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_8004A32C--;
                    }
                } else if ((btn & 0x400) || (held & 4)) {
                    if (D_ovl0B_03_8004A32C < 2) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_8004A32C++;
                    }
                    if (D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328] == 0 && D_ovl0B_03_8004A32C == 2) {
                        D_ovl0B_03_8004A32C = 1;
                    }
                } else if (held & 0x8000) {
                    for (i = 0, j = 0; i < 4; i++) {
                        if (D_ovl0B_03_8004A324->unk4[i] != 0) {
                            j++;
                        }
                    }
                    if (j >= 2) {
                        func_ovl0B_03_80048890(1);
                        if (D_ovl0B_03_8004A324->unk0 == 0) {
                            next = 5;
                        } else {
                            next = 4;
                        }
                        break;
                    }
                    func_ovl0B_03_80048890(0x18);
                } else if (held & 0x4000) {
                    func_ovl0B_03_80048890(2);
                    next = 0;
                    break;
                } else {
                    switch ((held & 3) ? 0 : D_ovl0B_03_8004A32C) {
                    case 0:
                        if ((btn & 0x200) || (held & 2)) {
                            if (D_ovl0B_03_8004A328 > 0) {
                                func_ovl0B_03_80048890(0);
                                D_ovl0B_03_80048E9C[D_ovl0B_03_8004A328].unk10->unkC |= 0x40;
                                D_ovl0B_03_8004A328--;
                                D_ovl0B_03_80048E9C[D_ovl0B_03_8004A328].unk10->unkC &= ~0x40;
                            }
                        } else if (((btn & 0x100) || (held & 1)) && (D_ovl0B_03_8004A328 < 3)) {
                            func_ovl0B_03_80048890(0);
                            D_ovl0B_03_80048E9C[D_ovl0B_03_8004A328].unk10->unkC |= 0x40;
                            D_ovl0B_03_8004A328++;
                            D_ovl0B_03_80048E9C[D_ovl0B_03_8004A328].unk10->unkC &= ~0x40;
                        }
                        break;
                    case 1:
                        i = D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328];
                        if (btn & 0x200) {
                            func_ovl0B_03_80048890(0);
                            i--;
                            if (i < 0) {
                                i = 2;
                            }
                            if ((func_ovl0B_03_800483D8(D_ovl0B_03_8004A328) & 8) && (i == 1)) {
                                i--;
                            }
                        } else if ((btn & 0x100) || (held & 0x2000)) {
                            func_ovl0B_03_80048890(0);
                            i++;
                            if (i >= 3) {
                                i = 0;
                            }
                            if ((func_ovl0B_03_800483D8(D_ovl0B_03_8004A328) & 8) && (i == 1)) {
                                i++;
                            }
                        }
                        D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328] = i;
                        if ((D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328] == 1) && (D_ovl0B_03_8004A324->unk40[D_ovl0B_03_8004A328] == 1)) {
                            func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[D_ovl0B_03_8004A328], D_ovl0B_03_8004A324->unk50[D_ovl0B_03_8004A328]);
                        } else {
                            func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[D_ovl0B_03_8004A328], NULL);
                        }
                        break;
                    case 2:
                        if (D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328] == 2) {
                            i = D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328 + 4];
                            if (btn & 0x200) {
                                func_ovl0B_03_80048890(0);
                                i--;
                                if (i < 0) {
                                    i = 2;
                                }
                            } else if ((btn & 0x100) || (held & 0x2000)) {
                                func_ovl0B_03_80048890(0);
                                i++;
                                if (i >= 3) {
                                    i = 0;
                                }
                            }
                            D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328 + 4] = i;
                        } else if (D_ovl0B_03_8004A324->unk4[D_ovl0B_03_8004A328] == 1) {
                            i = D_ovl0B_03_8004A324->unk40[D_ovl0B_03_8004A328];
                            if (((btn & 0x300) || (held & 0x2000)) && (i == 1)) {
                                func_ovl0B_03_80048890(0);
                                i = 0;
                                func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[D_ovl0B_03_8004A328], NULL);
                            } else if (((btn & 0x300) || (held & 0x2000)) && (i == 0) && (func_ovl0B_03_80048450(D_ovl0B_03_8004A328) == 9)) {
                                func_ovl0B_03_80048890(0);
                                i = 1;
                                func_ovl0B_03_8004368C(D_ovl0B_03_8004A400[D_ovl0B_03_8004A328], D_ovl0B_03_8004A324->unk50[D_ovl0B_03_8004A328]);
                            }
                            D_ovl0B_03_8004A324->unk40[D_ovl0B_03_8004A328] = i;
                        }
                        break;
                    }
                }
                D_ovl0B_03_8004A410 = D_ovl0B_03_8004A328 * 50;
                M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x1C) = D_ovl0B_03_80048E60[D_ovl0B_03_8004A32C];
                D_ovl0B_03_80048E6C->unk0 = D_ovl0B_03_8004A410 + 60.0f;
                M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x18) = D_ovl0B_03_8004A410 + 110.0f;
                D_ovl0B_03_80048E6C->unk4 = D_ovl0B_03_80048E60[D_ovl0B_03_8004A32C];
                func_ovl0B_03_80043170(D_ovl0B_03_80048E6C, func_ovl0B_03_800484B8(WRAPW_ovl0B_03(t)) * 0.05f + 0.7f);
                func_ovl0B_03_80043170(D_ovl0B_03_80048E84, func_ovl0B_03_800484B8(WRAPW_ovl0B_03(t)) * 0.05f + 0.7f);
                t += 4.0f;
                func_ovl0B_03_800434BC();
                func_ovl0B_03_80048350();
            }
            for (i = 0; i < 4; i++) {
                D_ovl0B_03_80048E9C[i].unk10->unkC |= 0x41;
            }
            func_ovl0B_03_80047EA0((UnkStructA_40 *) D_ovl0B_03_8004A3F4);
            func_ovl0B_03_80043134(D_ovl0B_03_80048DA0, 8);
            func_ovl0B_03_80043134(D_ovl0B_03_80048E6C, 2);
            for (i = 0; i < 4; i++) {
                func_ovl0B_03_80043134(&D_ovl0B_03_80048EEC[i * 3], 3);
            }
            if (next == 0) {
                func_ovl0B_03_80043060(0);
            } else if (next == 4) {
                func_ovl0B_03_80043060(1);
            } else {
                func_ovl0B_03_80043060(3);
            }
            func_ovl0B_03_80043010();
            state = next;
            break;
        case 2:
            func_ovl0B_03_800433BC();
            func_ovl0B_03_80043464(D_ovl0B_03_80048C20, 4);
            for (i = 0; i != 4; i++) {
                switch (i) {
                case 0:
                    *D_ovl0B_03_80048AE8 = D_ovl0B_03_8004A324->unk24 + 0x10;
                    str = D_ovl0B_03_80048AE8;
                    break;
                case 1:
                    if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) == 6) {
                        str = D_ovl0B_03_80048B60;
                    } else {
                        *D_ovl0B_03_80048AF4 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) + 0x10;
                        str = D_ovl0B_03_80048AF4;
                    }
                    break;
                case 2:
                    str = D_ovl0B_03_80048D00[D_ovl0B_03_8004A324->unk38];
                    if (D_ovl0B_03_8004A324->unk38 != 0) {
                        D_ovl0B_03_80048C90[i].unk14 = 0;
                    } else {
                        D_ovl0B_03_80048C90[i].unk14 = 1;
                    }
                    break;
                case 3:
                    str = D_ovl0B_03_80048D00[M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C)];
                    if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) != 0) {
                        D_ovl0B_03_80048C90[i].unk14 = 0;
                    } else {
                        D_ovl0B_03_80048C90[i].unk14 = 1;
                    }
                    break;
                }
#if VERSION_JP
                D_ovl0B_03_80048C90[i].unk18 = func_ovl0B_03_800486F0(str, D_ovl0B_03_80048C90[i].unk6, D_ovl0B_03_80048C90[i].unkA, D_ovl0B_03_80048C90[i].unkC, D_ovl0B_03_80048C90[i].unk10, D_ovl0B_03_80048C90[i].unk14);
#else
                D_ovl0B_03_80048C90[i].unk18 = func_ovl0B_03_80048748(str, func_ovl0B_03_80043234(str, 0.6f) + 42.0f, D_ovl0B_03_80048C90[i].unkA, D_ovl0B_03_80048C90[i].unkC, D_ovl0B_03_80048C90[i].unk10, D_ovl0B_03_80048C90[i].unk14);
#endif
            }
            i = D_ovl0B_03_8004A324->unk24;
            v28 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28);
            v38 = D_ovl0B_03_8004A324->unk38;
            v3C = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C);
            func_ovl0B_03_80048690(func_ovl0B_03_80046850, &spCC, 0x130, 0xC, 0xC);
            while (TRUE) {
                func_ovl0B_03_800486E0(1);
                if (D_ovl0B_03_8004A320 == -1) {
                    next = 0;
                    break;
                }
                if (D_ovl0B_03_8004A320 == -2) {
                    next = 0;
                    D_ovl0B_03_8004A324->unk24 = i;
                    M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) = v28;
                    D_ovl0B_03_8004A324->unk38 = v38;
                    M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) = v3C;
                    break;
                }
                if (D_ovl0B_03_8004A320 < 0x10) {
                    next = 0;
                    break;
                }
                j = ((D_ovl0B_03_8004A320 & 0x30) >> 4) - 1;
                k = (D_ovl0B_03_8004A320 & 0xF) - 1;
                switch (k) {
                case 0:
                    if (j == 0) {
                        if (D_ovl0B_03_8004A324->unk24 >= 2) {
                            func_ovl0B_03_80048890(0);
                            D_ovl0B_03_8004A324->unk24--;
                        }
                    } else if (j == 1) {
                        if (D_ovl0B_03_8004A324->unk24 < 5) {
                            func_ovl0B_03_80048890(0);
                            D_ovl0B_03_8004A324->unk24++;
                        }
                    }
                    break;
                case 1:
                    if (j == 0) {
                        if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) >= 2) {
                            func_ovl0B_03_80048890(0);
                            M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28)--;
                        }
                    } else if (j == 1) {
                        if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) < 6) {
                            func_ovl0B_03_80048890(0);
                            M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28)++;
                        }
                    }
                    break;
                case 2:
                    if (j == 0) {
                        if (D_ovl0B_03_8004A324->unk38 > 0) {
                            func_ovl0B_03_80048890(0);
                            D_ovl0B_03_8004A324->unk38--;
                        }
                    } else if (j == 1) {
                        if (D_ovl0B_03_8004A324->unk38 <= 0) {
                            func_ovl0B_03_80048890(0);
                            D_ovl0B_03_8004A324->unk38++;
                        }
                    }
                    break;
                case 3:
                    if (j == 0) {
                        if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) > 0) {
                            func_ovl0B_03_80048890(0);
                            M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C)--;
                        }
                    } else if (j == 1) {
                        if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) <= 0) {
                            func_ovl0B_03_80048890(0);
                            M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C)++;
                        }
                    }
                    break;
                }
                lab = &D_ovl0B_03_80048C90[k];
#if VERSION_JP
                state = lab->unk18;
                func_ovl0B_03_800486F8(state);
#else
                next = lab->unk18;
#endif
                switch (k) {
                case 0:
                    *D_ovl0B_03_80048AE8 = D_ovl0B_03_8004A324->unk24 + 0x10;
                    str = D_ovl0B_03_80048AE8;
                    break;
                case 1:
                    if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) == 6) {
                        str = D_ovl0B_03_80048B60;
                    } else {
                        *D_ovl0B_03_80048AF4 = M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x28) + 0x10;
                        str = D_ovl0B_03_80048AF4;
                    }
                    break;
                case 2:
                    str = D_ovl0B_03_80048D00[D_ovl0B_03_8004A324->unk38];
                    if (D_ovl0B_03_8004A324->unk38 != 0) {
                        lab->unk14 = 0;
                    } else {
                        lab->unk14 = 1;
                    }
                    break;
                case 3:
                    str = D_ovl0B_03_80048D00[M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C)];
                    if (M2C_FIELD(D_ovl0B_03_8004A324, s32 *, 0x3C) != 0) {
                        lab->unk14 = 0;
                    } else {
                        lab->unk14 = 1;
                    }
                    break;
                }
#if VERSION_JP
                lab->unk18 = func_ovl0B_03_800486F0(str, lab->unk6, lab->unkA, lab->unkC, lab->unk10, lab->unk14);
#else
                lab->unk18 = func_ovl0B_03_80048748(str, func_ovl0B_03_80043234(str, 0.6f) + 42.0f, lab->unkA, lab->unkC, lab->unk10, lab->unk14);
                func_ovl0B_03_800486F8(next);
#endif
                func_ovl0B_03_80048350();
            }
            func_ovl0B_03_80043428(D_ovl0B_03_80048C20, 4);
            func_ovl0B_03_80043428(D_ovl0B_03_80048C90, 4);
            func_ovl0B_03_800486A8();
            func_ovl0B_03_80048328(2);
            func_ovl0B_03_80043010();
            state = next;
            break;
        case 3:
        case 4:
            func_ovl0B_03_800433BC();
            func_ovl0B_03_80043340(D_ovl0B_03_8004900C, 1, 0x38);
            for (i = 0; i < 4; i++) {
                if (D_ovl0B_03_8004A324->unk4[i] != 0) {
                    break;
                }
            }
            D_ovl0B_03_8004A330 = i;
            D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10->unkC &= ~0x40;
            func_ovl0B_03_80043340(D_ovl0B_03_80048DA0, 4, 0x35);
            func_ovl0B_03_80043340(D_ovl0B_03_80049024, 2, 0x130);
            M2C_FIELD(D_ovl0B_03_80049024[0].unk14, s32 *, 0x38) = 0x12;
            M2C_FIELD(D_ovl0B_03_80049024[1].unk14, s32 *, 0x38) = 0x16;
            func_ovl0B_03_80043464(D_ovl0B_03_80049054, 2);
            for (i = 0; i != 4; i++) {
                if (D_ovl0B_03_8004A324->unk4[i] == 0) {
                    D_ovl0B_03_8004A324->unk90[i] = 0;
                }
                D_ovl0B_03_80048E9C[i].unk10->unkC &= ~1;
                D_ovl0B_03_80048E9C[i].unk10->unk14 = D_ovl0B_03_8004A324->unk90[i] * -70.0f;
                M2C_FIELD(D_ovl0B_03_80048DA0[i].unk14, s32 *, 0x38) = D_ovl0B_03_8004A324->unk4[i] * 2;
                D_ovl0B_03_80048DA0[i].unk4 = D_ovl0B_03_8004A324->unk90[i] * 76.0f + 116.0f;
                func_ovl0B_03_80043170(&D_ovl0B_03_80048DA0[i], 1.0f);
            }
            D_ovl0B_03_8004A3F4 = func_ovl0B_03_80047F18(func_ovl0B_03_80046918, 0);
            M2C_FIELD(D_ovl0B_03_8004A3F4, s32 *, 0xC) |= 0x480;
            D_ovl0B_03_8004A410 = D_ovl0B_03_8004A330 * 50;
            while (TRUE) {
                btn = func_ovl0B_03_800432F0();
                held = func_ovl0B_03_800432A0();
                if ((btn & 0x200) || (held & 2)) {
                    if (D_ovl0B_03_8004A330 > 0) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10->unkC |= 0x40;
                        for (i = D_ovl0B_03_8004A330 - 1; i >= 0; i--) {
                            if (D_ovl0B_03_8004A324->unk4[i] != 0) {
                                break;
                            }
                        }
                        if (i >= 0) {
                            D_ovl0B_03_8004A330 = i;
                        }
                        D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10->unkC &= ~0x40;
                    }
                } else if ((btn & 0x100) || (held & 1)) {
                    if (D_ovl0B_03_8004A330 < 3) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10->unkC |= 0x40;
                        for (i = D_ovl0B_03_8004A330 + 1; i < 4; i++) {
                            if (D_ovl0B_03_8004A324->unk4[i] != 0) {
                                break;
                            }
                        }
                        if (i < 4) {
                            D_ovl0B_03_8004A330 = i;
                        }
                        D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10->unkC &= ~0x40;
                    }
                } else if ((btn & 0x800) || (held & 8)) {
                    if (D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] > 0) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330]--;
                    }
                } else if ((btn & 0x400) || (held & 4)) {
                    if (D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] <= 0) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330]++;
                    }
                } else if (held & 0x8000) {
                    j = 0;
                    k = 0;
                    for (i = 0; i != 4; i++) {
                        if (D_ovl0B_03_8004A324->unk4[i] != 0) {
                            if (D_ovl0B_03_8004A324->unk90[i] != 0) {
                                j++;
                            } else {
                                k++;
                            }
                        }
                    }
                    if (j != 0 && k != 0) {
                        next = 5;
                        func_ovl0B_03_80048890(1);
                        break;
                    }
                    func_ovl0B_03_80048890(0x18);
                } else if (held & 0x4000) {
                    func_ovl0B_03_80048890(2);
                    next = 1;
                    break;
                }
                D_ovl0B_03_80048E9C[D_ovl0B_03_8004A330].unk10->unk14 = D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] * -70.0f;
                D_ovl0B_03_80048DA0[D_ovl0B_03_8004A330].unk4 = D_ovl0B_03_8004A324->unk90[D_ovl0B_03_8004A330] * 76.0f + 116.0f;
                func_ovl0B_03_80043170(&D_ovl0B_03_80048DA0[D_ovl0B_03_8004A330], 1.0f);
                D_ovl0B_03_8004A410 = D_ovl0B_03_8004A330 * 50;
                func_ovl0B_03_80048350();
            }
            if (next == 1) {
                func_ovl0B_03_80043060(0);
            } else {
                func_ovl0B_03_80043060(1);
            }
            for (i = 0; i < 4; i++) {
                D_ovl0B_03_80048E9C[i].unk10->unkC |= 0x41;
                D_ovl0B_03_80048E9C[i].unk10->unk14 = D_ovl0B_03_80048E9C[i].unk8;
                D_ovl0B_03_80048DA0[i].unk4 = 170.0f;
            }
            func_ovl0B_03_80043428(D_ovl0B_03_80049054, 2);
            func_ovl0B_03_80043134(D_ovl0B_03_80049024, 2);
            func_ovl0B_03_80043134(D_ovl0B_03_8004900C, 1);
            func_ovl0B_03_80043134(D_ovl0B_03_80048DA0, 4);
            func_ovl0B_03_80047EA0((UnkStructA_40 *) D_ovl0B_03_8004A3F4);
            func_ovl0B_03_80043010();
            state = next;
            break;
        case 5:
            func_ovl0B_03_800433BC();
            D_ovl0B_03_8004A334 = func_ovl0B_03_80047E98(D_ovl0B_03_8004908C[D_ovl0B_03_8004A324->unkA0], 0);
            D_ovl0B_03_8004A334->unkC |= 0x10000;
            D_ovl0B_03_8004A334->unk10 = D_ovl0B_03_800490DC[D_ovl0B_03_8004A324->unkA0] + -921.0f;
            D_ovl0B_03_8004A334->unk14 = 400.0f;
            D_ovl0B_03_8004A334->unk18 = -2000.0f;
            D_ovl0B_03_8004A334->unk1C = 50.0f;
            D_ovl0B_03_8004A334->unk30 = 0.4f;
            D_ovl0B_03_8004A334->unk28 = D_ovl0B_03_8004A334->unk2C = D_ovl0B_03_8004A334->unk30;
            if (D_ovl0B_03_800490B4[D_ovl0B_03_8004A324->unkA0] != -1) {
                D_ovl0B_03_8004A338 = func_ovl0B_03_80047E98(D_ovl0B_03_800490B4[D_ovl0B_03_8004A324->unkA0], 0);
                D_ovl0B_03_8004A338->unkC |= 0x10000;
                D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                D_ovl0B_03_8004A338->unk14 = D_ovl0B_03_8004A334->unk14;
                D_ovl0B_03_8004A338->unk18 = D_ovl0B_03_8004A334->unk18;
                D_ovl0B_03_8004A338->unk1C = D_ovl0B_03_8004A334->unk1C;
                D_ovl0B_03_8004A338->unk28 = D_ovl0B_03_8004A338->unk2C = D_ovl0B_03_8004A338->unk30 = D_ovl0B_03_8004A334->unk28;
            } else {
                D_ovl0B_03_8004A338 = NULL;
            }
            t = 0.0f;
#if VERSION_JP
            h = func_ovl0B_03_800486F0(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], func_ovl0B_03_80043234(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], 1.0f), 0xB4, 1.0f, 1.0f, 2);
#else
            h = func_ovl0B_03_80048748(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], func_ovl0B_03_80043234(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], 1.0f), 0xB4, 1.0f, 1.0f, 2);
#endif
            func_ovl0B_03_80043340(D_ovl0B_03_80048E6C, 2, 0x39);
            M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x1C) = 130.0f;
            D_ovl0B_03_80048E6C->unk4 = M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x1C);
            D_ovl0B_03_80048E6C->unk0 = 70.0f;
            M2C_FIELD(D_ovl0B_03_80048E6C, f32 *, 0x18) = 250.0f;
            while (TRUE) {
                btn = func_ovl0B_03_800432F0();
                held = func_ovl0B_03_800432A0();
                if (D_ovl0B_03_8004A324->unkA0 == 0) {
                    M2C_FIELD(D_ovl0B_03_80048E6C[0].unk14, s32 *, 0xC) |= 1;
                } else {
                    M2C_FIELD(D_ovl0B_03_80048E6C[0].unk14, s32 *, 0xC) &= ~1;
                }
                if (max == D_ovl0B_03_8004A324->unkA0) {
                    M2C_FIELD(D_ovl0B_03_80048E84[0].unk14, s32 *, 0xC) |= 1;
                } else {
                    M2C_FIELD(D_ovl0B_03_80048E84[0].unk14, s32 *, 0xC) &= ~1;
                }
                if (btn & 0x200) {
                    if (D_ovl0B_03_8004A324->unkA0 > 0) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_8004A324->unkA0--;
                        for (i = 0; i < 10; i++) {
                            D_ovl0B_03_8004A334->unk10 += 125.0f;
                            if (D_ovl0B_03_8004A338 != NULL) {
                                D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                            }
                            func_ovl0B_03_80048350();
                        }
                        func_ovl0B_03_80047EA0(D_ovl0B_03_8004A334);
                        if (D_ovl0B_03_8004A338 != NULL) {
                            func_ovl0B_03_80047EA0(D_ovl0B_03_8004A338);
                        }
                        D_ovl0B_03_8004A334 = func_ovl0B_03_80047E98(D_ovl0B_03_8004908C[D_ovl0B_03_8004A324->unkA0], 0);
                        D_ovl0B_03_8004A334->unkC |= 0x10000;
                        D_ovl0B_03_8004A334->unk10 = D_ovl0B_03_800490DC[D_ovl0B_03_8004A324->unkA0] + -2171.0f;
                        D_ovl0B_03_8004A334->unk14 = 400.0f;
                        D_ovl0B_03_8004A334->unk18 = -2000.0f;
                        D_ovl0B_03_8004A334->unk1C = 50.0f;
                        D_ovl0B_03_8004A334->unk30 = 0.4f;
                        D_ovl0B_03_8004A334->unk28 = D_ovl0B_03_8004A334->unk2C = D_ovl0B_03_8004A334->unk30;
                        if (D_ovl0B_03_800490B4[D_ovl0B_03_8004A324->unkA0] != -1) {
                            D_ovl0B_03_8004A338 = func_ovl0B_03_80047E98(D_ovl0B_03_800490B4[D_ovl0B_03_8004A324->unkA0], 0);
                            D_ovl0B_03_8004A338->unkC |= 0x10000;
                            D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                            D_ovl0B_03_8004A338->unk14 = D_ovl0B_03_8004A334->unk14;
                            D_ovl0B_03_8004A338->unk18 = D_ovl0B_03_8004A334->unk18;
                            D_ovl0B_03_8004A338->unk1C = D_ovl0B_03_8004A334->unk1C;
                            D_ovl0B_03_8004A338->unk28 = D_ovl0B_03_8004A338->unk2C = D_ovl0B_03_8004A338->unk30 = D_ovl0B_03_8004A334->unk28;
                        } else {
                            D_ovl0B_03_8004A338 = NULL;
                        }
                        i = h;
#if VERSION_JP
                        h = func_ovl0B_03_800486F0(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], func_ovl0B_03_80043234(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], 1.0f), 0xB4, 1.0f, 1.0f, 2);
#else
                        h = func_ovl0B_03_80048748(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], func_ovl0B_03_80043234(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], 1.0f), 0xB4, 1.0f, 1.0f, 2);
#endif
                        func_ovl0B_03_800486F8(i);
                        for (i = 0; i != 10; i++) {
                            D_ovl0B_03_8004A334->unk10 += 125.0f;
                            if (D_ovl0B_03_8004A338 != NULL) {
                                D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                            }
                            func_ovl0B_03_80048350();
                        }
                    }
                } else if (btn & 0x100) {
                    if (D_ovl0B_03_8004A324->unkA0 < max) {
                        func_ovl0B_03_80048890(0);
                        D_ovl0B_03_8004A324->unkA0++;
                        for (i = 0; i < 10; i++) {
                            D_ovl0B_03_8004A334->unk10 -= 125.0f;
                            if (D_ovl0B_03_8004A338 != NULL) {
                                D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                            }
                            func_ovl0B_03_80048350();
                        }
                        func_ovl0B_03_80047EA0(D_ovl0B_03_8004A334);
                        if (D_ovl0B_03_8004A338 != NULL) {
                            func_ovl0B_03_80047EA0(D_ovl0B_03_8004A338);
                        }
                        D_ovl0B_03_8004A334 = func_ovl0B_03_80047E98(D_ovl0B_03_8004908C[D_ovl0B_03_8004A324->unkA0], 0);
                        D_ovl0B_03_8004A334->unkC |= 0x10000;
                        D_ovl0B_03_8004A334->unk10 = D_ovl0B_03_800490DC[D_ovl0B_03_8004A324->unkA0] + 329.0f;
                        D_ovl0B_03_8004A334->unk14 = 400.0f;
                        D_ovl0B_03_8004A334->unk18 = -2000.0f;
                        D_ovl0B_03_8004A334->unk1C = 50.0f;
                        D_ovl0B_03_8004A334->unk30 = 0.4f;
                        D_ovl0B_03_8004A334->unk28 = D_ovl0B_03_8004A334->unk2C = D_ovl0B_03_8004A334->unk30;
                        if (D_ovl0B_03_800490B4[D_ovl0B_03_8004A324->unkA0] != -1) {
                            D_ovl0B_03_8004A338 = func_ovl0B_03_80047E98(D_ovl0B_03_800490B4[D_ovl0B_03_8004A324->unkA0], 0);
                            D_ovl0B_03_8004A338->unkC |= 0x10000;
                            D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                            D_ovl0B_03_8004A338->unk14 = D_ovl0B_03_8004A334->unk14;
                            D_ovl0B_03_8004A338->unk18 = D_ovl0B_03_8004A334->unk18;
                            D_ovl0B_03_8004A338->unk1C = D_ovl0B_03_8004A334->unk1C;
                            D_ovl0B_03_8004A338->unk28 = D_ovl0B_03_8004A338->unk2C = D_ovl0B_03_8004A338->unk30 = D_ovl0B_03_8004A334->unk28;
                        } else {
                            D_ovl0B_03_8004A338 = NULL;
                        }
                        i = h;
#if VERSION_JP
                        h = func_ovl0B_03_800486F0(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], func_ovl0B_03_80043234(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], 1.0f), 0xB4, 1.0f, 1.0f, 2);
#else
                        h = func_ovl0B_03_80048748(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], func_ovl0B_03_80043234(D_ovl0B_03_80049194[D_ovl0B_03_8004A324->unkA0], 1.0f), 0xB4, 1.0f, 1.0f, 2);
#endif
                        func_ovl0B_03_800486F8(i);
                        for (i = 0; i != 10; i++) {
                            D_ovl0B_03_8004A334->unk10 -= 125.0f;
                            if (D_ovl0B_03_8004A338 != NULL) {
                                D_ovl0B_03_8004A338->unk10 = D_ovl0B_03_8004A334->unk10;
                            }
                            func_ovl0B_03_80048350();
                        }
                    }
                } else if (held & 0x8000) {
                    func_ovl0B_03_80048890(0x25);
                    func_ovl0B_03_80047EA0(D_ovl0B_03_8004A334);
                    if (D_ovl0B_03_8004A338 != NULL) {
                        func_ovl0B_03_80047EA0(D_ovl0B_03_8004A338);
                    }
                    func_ovl0B_03_800486F8(h);
                    next = 6;
                    D_ovl0B_03_8004A324->unkA4[0] = 0;
                    D_ovl0B_03_8004A324->unkA4[1] = 0;
                    D_ovl0B_03_8004A324->unkA4[2] = 0;
                    D_ovl0B_03_8004A324->unkA4[3] = 0;
                    func_ovl0B_03_800431FC();
                    func_ovl0B_03_800478B0(D_ovl0B_03_8004A324->unkA0 + 0x90, 0x10, 0);
                    break;
                } else if (held & 0x4000) {
                    func_ovl0B_03_80048890(2);
                    func_ovl0B_03_80047EA0(D_ovl0B_03_8004A334);
                    if (D_ovl0B_03_8004A338 != NULL) {
                        func_ovl0B_03_80047EA0(D_ovl0B_03_8004A338);
                    }
                    func_ovl0B_03_800486F8(h);
                    if (D_ovl0B_03_8004A324->unk0 == 0) {
                        next = 1;
                    } else {
                        next = 4;
                    }
                    break;
                }
                func_ovl0B_03_80043170(D_ovl0B_03_80048E6C, func_ovl0B_03_800484B8(WRAPW_ovl0B_03(t)) * 0.05f + 1.0f);
                func_ovl0B_03_80043170(D_ovl0B_03_80048E84, func_ovl0B_03_800484B8(WRAPW_ovl0B_03(t)) * 0.05f + 1.0f);
                t += 4.0f;
                func_ovl0B_03_80048350();
            }
            func_ovl0B_03_80043134(D_ovl0B_03_80048E6C, 2);
            if (next == 4) {
                func_ovl0B_03_80043060(0);
            } else if (next != 6) {
                func_ovl0B_03_80043060(2);
            }
            func_ovl0B_03_80043010();
            state = next;
            break;
        }
        func_ovl0B_03_80048350();
    }
}


/* Fades n boxes' objects to alpha (0xF1 and over: opaque). */
static void func_ovl0B_03_800436EC(s32 n, Box_ovl0B_03 *boxes, s32 alpha) {
    s32 i;

    for (i = 0; i < n; i++) {
        boxes[i].unk14->unkC |= 0x80;
        if (alpha >= 0xF1) {
            boxes[i].unk14->unk36 = -1;
            boxes[i].unk14->unkC &= ~0x80;
        } else {
            boxes[i].unk14->unk36 = alpha;
        }
    }
}

/* The original passes obj in $s2 and vals in $s1. */
static void func_ovl0B_03_8004368C(s32 obj, s32 *vals) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (vals == NULL) {
            func_ovl0B_03_80047960(obj, i, 0);
        } else {
            func_ovl0B_03_80047960(obj, i, vals[i]);
        }
    }
}

static void func_ovl0B_03_800434BC(void) {
    s32 i;
    s32 j;
    s32 mode;
    u32 frame;

    for (i = 0; i < 4; i++) {
        mode = D_ovl0B_03_8004A324->unk4[i];
        if (mode != 0 && (func_ovl0B_03_800483D8(i) & 8)) {
            D_ovl0B_03_8004A324->unk4[i] = 2;
            mode = 2;
        }
        frame = mode * 2;
        if (mode == 1) {
            D_ovl0B_03_80048DA0[i + 4].unk14->unkC &= ~1;
            if (D_ovl0B_03_8004A324->unk40[i] == 1) {
                D_ovl0B_03_80048DA0[i + 4].unk14->unkC &= ~0x80;
            } else {
                D_ovl0B_03_80048DA0[i + 4].unk14->unkC |= 0x80;
                D_ovl0B_03_80048DA0[i + 4].unk14->unk36 = 0x80;
            }
        } else {
            D_ovl0B_03_80048DA0[i + 4].unk14->unkC |= 1;
        }
        M2C_FIELD(D_ovl0B_03_80048DA0[i].unk14, s32 *, 0x38) = frame;
        M2C_FIELD(D_ovl0B_03_80048DA0[i + 4].unk14, s32 *, 0x38) = 6;
        for (j = 0; j < 3; j++) {
            D_ovl0B_03_80048EEC[i * 3 + j].unk14->unkC |= 1;
        }
        if (frame == 4) {
            for (j = 0; j < 3; j++) {
                if (M2C_FIELD((u8 *)D_ovl0B_03_8004A324 + i * 4, s32 *, 0x14) >= j) {
                    D_ovl0B_03_80048EEC[i * 3 + j].unk14->unkC &= ~1;
                }
            }
        }
    }
}

/* The original passes n in $s2. */
static void func_ovl0B_03_80043464(Label_ovl0B_03 *labels, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        labels[i].unk18 = func_ovl0B_03_80048748(labels[i].unk0, labels[i].unk6, labels[i].unkA, labels[i].unkC,
                                                 labels[i].unk10, labels[i].unk14);
    }
}

/* The original passes n in $s2. */
static void func_ovl0B_03_80043428(Label_ovl0B_03 *labels, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0B_03_800486F8(labels[i].unk18);
    }
}

static void func_ovl0B_03_800433BC(void) {
    UnkStructA_40 *temp_v0;
    s32 var_s0;

    D_ovl0B_03_8004A3F8 = func_ovl0B_03_80047F18(func_ovl0B_03_80047064, -1);
    D_ovl0B_03_8004A3F8->unkC |= 0x480;
    for (var_s0 = 5; var_s0 != 0x73; var_s0 += 0xA) {
        D_ovl0B_03_8004A414 = var_s0;
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80048350();
}

/* The original takes n in $s4 and the model in $s5. */
static void func_ovl0B_03_80043340(Box_ovl0B_03 *boxes, s32 n, s32 model) {
    s32 i;

    for (i = 0; i < n; i++) {
        boxes[i].unk14 = func_ovl0B_03_80047E98(model, 0);
        M2C_FIELD(boxes[i].unk14, s32 *, 0x38) = i * 2;
        boxes[i].unk14->unkC &= ~1;
        func_ovl0B_03_80043170(&boxes[i], boxes[i].unk10);
    }
}

static s32 func_ovl0B_03_800432F0(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = 0;
    do {
        if (!(func_ovl0B_03_800483D8(var_s0) & 8)) {
            var_s1 |= func_ovl0B_03_800486D8(var_s0);
        }
        var_s0 += 1;
    } while (var_s0 != 4);
    return var_s1;
}

static s32 func_ovl0B_03_800432A0(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = 0;
    do {
        if (!(func_ovl0B_03_800483D8(var_s0) & 8)) {
            var_s1 |= func_ovl0B_03_800483E8(var_s0);
        }
        var_s0 += 1;
    } while (var_s0 != 4);
    return var_s1;
}

/* The original takes the scale in $f20 (its callers' register). */
#if VERSION_JP
/* jp's text is fixed-width: 24 pixels a character. */
static s32 func_ovl0B_03_80043234(u8 *str, f32 scale) {
    s32 n;

    for (n = 0; str[n] != 0; n++) {
    }
    return (320.0f - n * 24 * scale) / 2;
}
#else
static s32 func_ovl0B_03_80043234(u8 *str, f32 scale) {
    return (320.0f - func_ovl0B_03_80048740(str) * scale) / 2;
}
#endif

/* The original takes the scale in $f12. */
static void func_ovl0B_03_80043170(Box_ovl0B_03 *box, f32 scale) {
    box->unk10 = scale;
    box->unk14->unk10 = box->unk0 - box->unk8 * scale * 0.5f;
    box->unk14->unk14 = box->unk4 - box->unkC * box->unk10 * 0.5f;
    box->unk14->unk18 = box->unk14->unk10 + box->unk8 * box->unk10;
    box->unk14->unk1C = box->unk14->unk14 + box->unkC * box->unk10;
}

/* The original passes n in $s2 (its callers' register). */
static void func_ovl0B_03_80043134(Box_ovl0B_03 *boxes, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0B_03_80047EA0(boxes[i].unk14);
    }
}

static void func_ovl0B_03_80043010(void) {
    s32 var_s0;

    for (var_s0 = 0x6E; var_s0 != 0; var_s0 -= 0xA) {
        D_ovl0B_03_8004A414 = var_s0;
        func_ovl0B_03_80048350();
    }
    func_ovl0B_03_80047EA0(D_ovl0B_03_8004A3F8);
    func_ovl0B_03_80048350();
}
