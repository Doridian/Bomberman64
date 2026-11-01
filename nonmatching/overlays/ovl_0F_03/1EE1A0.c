/*
 * NON_MATCHING: ovl_0F_03's game object, complete: every function and its
 * data (.data and .rodata as the original; .bss 0x1F0, the original 0x200).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 3, eu 3, jp 3
 *
 * The functions ovl_0F_02's draft (1E84A0.c) shares with this overlay are
 * ported from it: the particles (func_ovl0F_03_80044258 with its loop in
 * the static 80044250, ovl_0F_02's 800454E8/800454E0), their reset
 * 800432F0 (800453A4), the door task 80043F38 (80045024) and its
 * effects 80043E60 (80044E9C, (id, pos, d, h)), and the handler's door
 * static 80044C7C (80046160, a door pointer and pad[2]). 800430B4 takes
 * (n, models) as ovl_0F_02's 80044F74; with (models, n) the door's call
 * schedules differently. Every function and stub comes out in the
 * original's place.
 *
 * Fakes and guesses:
 * - `#line 1 "panels.c"` around the statics 800434A4, 80044C8C and
 *   800432E8 (ovl_0F_02's trick: a file change ends an as1 block, and as1
 *   orders a block partly by .loc line). 800434A4's makes 800434AC's pos
 *   copy schedule as the original (8 words to 3); 80044C8C's and
 *   800432E8's the handler's table loop and case 4's 800468C0 call.
 * - The handler's frame: `s32 pad[10]` in 8004327C (case 0x50), and case
 *   15's code written in the handler with the empty static 80043028
 *   called first (as a static of its own its 5-argument call takes 8
 *   bytes of the frame below case 0x52's slots). The door's pad[2] sits
 *   between case 20's slot and the tables'.
 * - 80044C8C takes (table, count) and the handler calls 800469B0 itself,
 *   as ovl_0F_02's 800462F8_inl0.
 * - 80046E10 and 80046E14 are function statics of 80043AF0 and 80043944
 *   (as ovl_0F_10's 80044B7C): as globals each loop keeps the variable's
 *   address in a register. The .data after them is defined after
 *   80043944, with extern declarations at the top, so .data keeps the
 *   original's order.
 * - 80043944's set-up is the static 8004393C (its stub) and the loop is
 *   inline, as ovl_0F_10's 80044B84; the set-up inline with 8004393C
 *   empty compiles the same.
 * - func_ovl0F_03_80046668 and func_ovl0F_03_80046690 are declared to
 *   return s32 (void in every matched overlay). With both void,
 *   80043AF0's pointer temporaries take v0 where the original has v1 and
 *   its counter v1 for a0 (52 words); 80046BD0 in place of 80046690 does
 *   the same.
 * - The door's 2.45 is 2.4500003f: the original's float is 0x401CCCCE,
 *   one ulp above 2.45f (ovl_0F_02's and ovl_0F_04's drafts have 2.45f
 *   against the same 0x401CCCCE).
 * - The `if (0)` in 80043434 only puts 80044C20 (which nothing uses)
 *   where the original has it, and the unused static 80045678's call
 *   keeps 80043030 from being inlined.
 *
 * What still differs (jp):
 * - func_ovl0F_03_800434AC (3): the hit flag (80043494's) is loaded into
 *   v0, the original's v1, and the branch over the restore takes `lw ra`
 *   into its delay slot where the original has a nop. Tried: the flag by
 *   pointer, returned through 8004348C, an inline test with 80043494
 *   empty, early returns and nested ifs, the callees' return types, and
 *   the permuter (15 minutes).
 *
 * jp only measured; us and eu keep the previous draft's 1649 (there are
 * no VERSION conditionals).
 *
 * The order is IDO's: the handler, last in the file but for
 * func_ovl0F_03_80043010, is compiled first, its callees (and the statics
 * they inline) before it, the functions it only takes the address of after
 * those, in the reverse of the order their references appear, the inlined
 * statics' (in the statics' definition order) before its own.
 */
#include "common.h"

/*
 * ovl_0F_03's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). ovl_0F_07 (1FCAC0),
 * ovl_0F_10 (205890) and ovl_17_09 (2B8D20) share most of its code. The
 * statics IDO inlines everywhere are named for the empty stubs they leave.
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
} UnkStruct_ovl0F_03_80046E88; /* size 0x2C */

/* the door func_ovl0F_03_80043F38 runs as a task: two models and what to
 * call once it is open */
typedef struct {
    /* 0x00 */ UnkStruct_ovl0F_03_80046E88 unk0[2];
    /* 0x58 */ void (*unk58)(void);
    /* 0x5C */ void (*unk5C)(void);
} UnkStruct_ovl0F_03_80046F0C; /* size 0x60 */

/* seven arguments of func_ovl0F_03_80045CF8 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0F_03_80046FE4; /* size 0x1C */

/* one of the particles func_ovl0F_03_80044258 draws (D_ovl0F_03_800470E8) */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0F_03_800470E8; /* size 0x14 */

/* what func_ovl0F_03_800461C8 returns: offsets into itself */
typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18[8];
    /* 0x20 */ s32 unk20;
} UnkStruct_ovl0F_03_80046DF0;

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_ovl0F_03_Gfx; /* size 0x8 */

/* gbi.h's _SHIFTL */
#define _SHIFTL(v, s, w) ((u32) (((u32) (v) & ((0x01 << (w)) - 1)) << (s)))

void func_ovl0F_03_80045AF8(s32);
void func_ovl0F_03_80045B10(s32);
void func_ovl0F_03_80045B38(s32, s32, s32, s32, s32, s32);
void func_ovl0F_03_80045B58(f32, f32, f32, f32 *, s32);
void func_ovl0F_03_80045B80(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0F_03_80045BD8(void (*)(UnkStructA *), s32);
void func_ovl0F_03_80045BE0(void (*)(UnkStructA *));
void func_ovl0F_03_80045BF0(s32, s32, s32);
s32 func_ovl0F_03_80045BF8(void);
void func_ovl0F_03_80045C18(void);
void func_ovl0F_03_80045C48(void);
void func_ovl0F_03_80045C60(s32);
void func_ovl0F_03_80045C68(s32);
void func_ovl0F_03_80045C70(s32);
void func_ovl0F_03_80045CA8(void);
void func_ovl0F_03_80045CB0(s32, s32, s32);
void func_ovl0F_03_80045CB8(Vec3f *);
s32 func_ovl0F_03_80045CC0(s32, s32, s32, s32);
s32 func_ovl0F_03_80045CC8(s32, s32, s32, s32, s32);
s32 func_ovl0F_03_80045CD8(void);
void func_ovl0F_03_80045CE0(s32, f32 *);
void func_ovl0F_03_80045CE8(s32);
void func_ovl0F_03_80045CF0(s32);
void func_ovl0F_03_80045CF8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0F_03_80045D00(char *);
void func_ovl0F_03_80045D08(void);
void func_ovl0F_03_80045D10(s32);
void func_ovl0F_03_80045D20(s32);
UnkStructA *func_ovl0F_03_80045D38(s32);
void func_ovl0F_03_80045D40(s32);
UnkStructA *func_ovl0F_03_80045D78(s32);
UnkStruct_ovl0F_03_80046DF0 *func_ovl0F_03_800461C8(s32);
void func_ovl0F_03_800461D0(s32);
void func_ovl0F_03_800461E8(UnkStructA *);
UnkStructA *func_ovl0F_03_80046258(void (*)(s32, UnkStruct_ovl0F_03_Gfx **), s32);
void func_ovl0F_03_80046260(s32, s32);
void func_ovl0F_03_80046338(f32, f32, f32);
void func_ovl0F_03_80046358(f32, f32, f32);
void func_ovl0F_03_80046360(f32 *, f32 *, f32 *);
void func_ovl0F_03_80046398(s32);
void func_ovl0F_03_800463A0(s32);
void func_ovl0F_03_800463C0(f32);
void func_ovl0F_03_800463C8(f32);
void func_ovl0F_03_800463E0(f32);
void func_ovl0F_03_80046428(f32 *);
void func_ovl0F_03_80046440(Vec3f *);
void func_ovl0F_03_80046450(f32 *);
void func_ovl0F_03_80046458(void);
void func_ovl0F_03_80046460(void);
s32 func_ovl0F_03_800464A8(UnkStructA *, s32);
void func_ovl0F_03_800464F8(UnkStructA *, s32);
void func_ovl0F_03_80046500(UnkStructA *, s32);
s32 func_ovl0F_03_80046510(UnkStructA *);
UnkStructA *func_ovl0F_03_80046520(s32, s32, s32, s32);
UnkStructA *func_ovl0F_03_80046568(s32, s32);
void func_ovl0F_03_80046578(UnkStructA *);
void func_ovl0F_03_800465D8(f32);
void func_ovl0F_03_800465E0(s32);
s32 func_ovl0F_03_80046618(UnkStructA *, s32, UnkStructA *);
s32 func_ovl0F_03_80046648(void (*)(void), void *, s32, s32, s32);
void func_ovl0F_03_80046658(void);
s32 func_ovl0F_03_80046668(s32);
void *func_ovl0F_03_80046670(void);
s32 func_ovl0F_03_80046690(void);
f32 func_ovl0F_03_800467F0(f32);
f32 func_ovl0F_03_800467F8(f32);
f64 func_ovl0F_03_80046800(void);
s32 func_ovl0F_03_80046808(s32);
s32 func_ovl0F_03_800468B0(s32);
void func_ovl0F_03_800468C0(s32);
s32 func_ovl0F_03_800468D0(s32);
s32 *func_ovl0F_03_800468E0(s32);
void func_ovl0F_03_80046988(s32, s32, s32, s32, s32);
void func_ovl0F_03_80046998(s32, s32, s32);
void func_ovl0F_03_800469B0(u32 (*)[3]);
void func_ovl0F_03_80046A98(s32, f32, f32, f32, s32);
s32 func_ovl0F_03_80046AA0(s32, f32 *, s32);
void func_ovl0F_03_80046AA8(s32);
void func_ovl0F_03_80046AD8(void);
void func_ovl0F_03_80046B48(UnkStructA *, s32, f32);
void func_ovl0F_03_80046B58(s32, s32, s32);
void func_ovl0F_03_80046BB8(void);
void func_ovl0F_03_80046BD0(s32);
void func_ovl0F_03_80046BF0(s32, f32, f32, f32);
void func_ovl0F_03_80046BF8(s32, f32 *);

void func_ovl0F_03_80043010(void);
void func_ovl0F_03_80043444(f32);
void func_ovl0F_03_800434AC(UnkStructA *);
void func_ovl0F_03_8004377C(UnkStructA *);
void func_ovl0F_03_8004389C(void);
void func_ovl0F_03_80043944(void);
void func_ovl0F_03_80043AF0(void);
void func_ovl0F_03_80043F38(void);
void func_ovl0F_03_80044258(s32, UnkStruct_ovl0F_03_Gfx **);
void func_ovl0F_03_80044C20(void);
void func_ovl0F_03_80044C94(s32);
void func_ovl0F_03_80045568(s32, UnkStructA *);
void func_ovl0F_03_8004559C(f32, f32, f32);
void func_ovl0F_03_800455F8(void);

static void func_ovl0F_03_80043030(UnkStruct_ovl0F_03_80046E88 *);
static void func_ovl0F_03_800430B4(s32, UnkStruct_ovl0F_03_80046E88 *);
static void func_ovl0F_03_80043164(UnkStruct_ovl0F_03_80046E88 *, s32);
static void func_ovl0F_03_80043284(s32 *);
static void func_ovl0F_03_800432F0(UnkStruct_ovl0F_03_800470E8 *);
static void func_ovl0F_03_80043E60(s32, f32 *, f32, f32);
static void func_ovl0F_03_80045680(void);
static void func_ovl0F_03_800456BC(void);
static void func_ovl0F_03_80043028(void);
static void func_ovl0F_03_8004326C(void);
static void func_ovl0F_03_80043020(s32, UnkStruct_ovl0F_03_80046E88 *);
static void func_ovl0F_03_8004327C(void);
static void func_ovl0F_03_80043274(s32 *);
static void func_ovl0F_03_800432D0(void);
static void func_ovl0F_03_800432D0(void);
static void func_ovl0F_03_800432D8(void);
static void func_ovl0F_03_80044C84(void);
static void func_ovl0F_03_80044C8C(u32 (*)[3], s32);
static void func_ovl0F_03_80044250(UnkStruct_ovl0F_03_Gfx **);
static void func_ovl0F_03_80043018(void);
static void func_ovl0F_03_8004393C(void);

static void func_ovl0F_03_80043434(void);
static void func_ovl0F_03_80044C7C(UnkStruct_ovl0F_03_80046F0C *);
static void func_ovl0F_03_80043020(s32 count, UnkStruct_ovl0F_03_80046E88 *p);
static void func_ovl0F_03_80043274(s32 *p);
static void func_ovl0F_03_8004343C(void);
static void func_ovl0F_03_8004342C(void);
static void func_ovl0F_03_800432E8(void);
static void func_ovl0F_03_800432E0(void);
static void func_ovl0F_03_800432D8(void);

/* .bss */
UnkStructA *D_ovl0F_03_80047090[6];
f32 D_ovl0F_03_800470A8[3];
u8 D_ovl0F_03_800470B4[0x4];
Vec3f D_ovl0F_03_800470B8;
s32 D_ovl0F_03_800470C4;
u8 D_ovl0F_03_800470C8[0x4];
s32 D_ovl0F_03_800470CC;
s32 D_ovl0F_03_800470D0;
u8 D_ovl0F_03_800470D4[0x4];
Vec3f D_ovl0F_03_800470D8;
u8 D_ovl0F_03_800470E4[0x4];
UnkStruct_ovl0F_03_800470E8 D_ovl0F_03_800470E8[20];
Vec3f D_ovl0F_03_80047278;
UnkStructA *D_ovl0F_03_80047284;

/* .data */
UnkStruct_ovl0F_03_80046DF0 *D_ovl0F_03_80046DF0 = NULL;
f32 D_ovl0F_03_80046DF4 = 0.0f;
f32 D_ovl0F_03_80046DF8 = 0.0f;
f32 D_ovl0F_03_80046DFC = 0.0f;
f32 D_ovl0F_03_80046E00 = 0.0f;
f32 D_ovl0F_03_80046E04 = 0.0f;
s32 D_ovl0F_03_80046E08 = 0;
s32 D_ovl0F_03_80046E0C = -1;
extern f32 D_ovl0F_03_80046E18;
extern u32 D_ovl0F_03_80046E1C[][3];
extern u32 D_ovl0F_03_80046E40[][3];
extern UnkStruct_ovl0F_03_80046E88 D_ovl0F_03_80046E88;
extern UnkStruct_ovl0F_03_80046E88 D_ovl0F_03_80046EB4[2];
extern UnkStruct_ovl0F_03_80046F0C D_ovl0F_03_80046F0C;
extern s32 D_ovl0F_03_80046F6C[7];
extern s32 D_ovl0F_03_80046F88[7];
extern UnkStruct_ovl0F_03_80046FE4 D_ovl0F_03_80046FA4[2];
extern UnkStructA * D_ovl0F_03_80046FDC;
extern char D_ovl0F_03_80046FE0[];
extern UnkStruct_ovl0F_03_80046FE4 D_ovl0F_03_80046FE4;

/* unused: the stubs IDO -O3 leaves at the end of the object */
/* A second caller keeps func_ovl0F_03_80043030 from being inlined. */
static void func_ovl0F_03_80045678(void) {
    func_ovl0F_03_80043030(D_ovl0F_03_80046EB4);
}

static void func_ovl0F_03_80045670(void) {
}

static void func_ovl0F_03_80045668(void) {
}

static void func_ovl0F_03_80045660(void) {
}

static void func_ovl0F_03_80045658(void) {
}

static void func_ovl0F_03_80045650(void) {
}

static void func_ovl0F_03_80045648(void) {
}

static void func_ovl0F_03_80045640(void) {
}

static void func_ovl0F_03_80045638(void) {
}

static void func_ovl0F_03_80045630(void) {
}

static void func_ovl0F_03_80045628(void) {
}

static void func_ovl0F_03_80045620(void) {
}

static void func_ovl0F_03_80045618(void) {
}

static void func_ovl0F_03_80045610(void) {
}

/* the door's: what func_ovl0F_03_80043F38 calls once it is open (the two
 * callbacks in D_ovl0F_03_80046F0C) */
static void func_ovl0F_03_80045680(void) {
    func_ovl0F_03_80045B38(0x14, 4, 0x1C, 0x18, 0x1C, 0x10);
}

static void func_ovl0F_03_800456BC(void) {
    func_ovl0F_03_80045B38(0x14, 3, 0x1A, 0x18, 0x1B, 0x10);
    func_ovl0F_03_80045B38(0x14, 3, 0x1C, 0x18, 0x1C, 0x11);
    func_ovl0F_03_80045B38(0x14, 3, 0x1D, 0x18, 0x1E, 0x10);
    func_ovl0F_03_80045B38(0x14, 2, 0x1A, 0x18, 0x1B, 0x13);
    func_ovl0F_03_80045B38(0x14, 2, 0x1C, 0x18, 0x1C, 0x1F);
    func_ovl0F_03_80045B38(0x14, 2, 0x1D, 0x18, 0x1E, 0x14);
}

void func_ovl0F_03_800455F8(void) {
    D_ovl0F_03_800470CC = -1;
    D_ovl0F_03_800470D0 = -1;
}

void func_ovl0F_03_8004559C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_03_80046338(D_ovl0F_03_800470D8.x, D_ovl0F_03_800470D8.y, D_ovl0F_03_800470D8.z);
    func_ovl0F_03_80046358(arg0, arg1, arg2);
    func_ovl0F_03_80046668(180);
}

void func_ovl0F_03_80045568(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0F_03_80046BF0(arg0, p->unk10, p->unk14, p->unk18);
}

/* a task: the door's switch, pressed a number of times */
void func_ovl0F_03_80044C20(void) {
    s32 n;
    s32 i;

    n = (s32)func_ovl0F_03_80046670();
    for (i = 0; i < n; i++) {
        func_ovl0F_03_80046BB8();
        func_ovl0F_03_80046690();
    }
    func_ovl0F_03_80046658();
}

static void func_ovl0F_03_80044250(UnkStruct_ovl0F_03_Gfx **gdl) {
    UnkStruct_ovl0F_03_Gfx *g2;
    f32 oldx;
    f32 oldz;
    f32 s;
    s32 i;
    f32 view[3];

    g2 = *gdl;
    oldx = D_ovl0F_03_80047278.x;
    oldz = D_ovl0F_03_80047278.z;
    func_ovl0F_03_80046440(&D_ovl0F_03_80047278);
    func_ovl0F_03_80046450(view);
    s = func_ovl0F_03_800467F8(view[0]);
    D_ovl0F_03_80046DF4 = ((D_ovl0F_03_80047278.x - oldx) * s - func_ovl0F_03_800467F0(view[0]) * (D_ovl0F_03_80047278.z - oldz)) * 0.5f;
    s = func_ovl0F_03_800467F8(view[0]);
    D_ovl0F_03_80046DF8 = (func_ovl0F_03_800467F0(view[0]) * (D_ovl0F_03_80047278.x - oldx) + (D_ovl0F_03_80047278.z - oldz) * s) * 0.2f;
    D_ovl0F_03_80046DF4 *= 1500.0f / view[2];
    D_ovl0F_03_80046DF8 *= 1500.0f / view[2];
    for (i = 0; i < 20; i++) {
        if (func_ovl0F_03_800468D0(0x407) != 0) {
            UnkStruct_ovl0F_03_800470E8 *p = &D_ovl0F_03_800470E8[i];

            { UnkStruct_ovl0F_03_Gfx *g = g2++; g->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL((u32) (p->unk8 + p->unk4 - 1) << 2, 0, 12) | _SHIFTL((u32) (p->unk0 + p->unk8 - 1) << 2, 12, 12); g->w1 = _SHIFTL(0, 24, 3) | _SHIFTL((u32) p->unk4 << 2, 0, 12) | _SHIFTL((u32) p->unk0 << 2, 12, 12); { UnkStruct_ovl0F_03_Gfx *g = g2++; g->w0 = 0xB4000000; g->w1 = 0; } { UnkStruct_ovl0F_03_Gfx *g = g2++; g->w0 = 0xB3000000; g->w1 = _SHIFTL((s32) (16.0f / (p->unk8 - 1) * 1024.0f), 0, 16) | _SHIFTL((s32) (16.0f / (p->unk8 - 1) * 1024.0f), 16, 16); } }
        }
        if (D_ovl0F_03_80046E04 == 0.0f) {
            continue;
        }
        {
            f32 r;
            f32 dx;
            f32 dy;
            f64 drift;

            s = func_ovl0F_03_800467F8(view[0]);
            r = func_ovl0F_03_80046800();
            dx = -D_ovl0F_03_80046DF4;
            D_ovl0F_03_800470E8[i].unk0 += dx - r * (dx * 0.25f) + D_ovl0F_03_80046DFC * s;
            s = (D_ovl0F_03_80046DFC != 0.0f ? 1.0f : 0);
            if (func_ovl0F_03_800467F0(view[0]) * (s * D_ovl0F_03_80046DFC) + D_ovl0F_03_80046E00 < 0.0f) {
                f32 sign = (D_ovl0F_03_80046DFC != 0.0f ? 1.0f : 0);

                drift = (func_ovl0F_03_800467F0(view[0]) * (sign * D_ovl0F_03_80046DFC) + D_ovl0F_03_80046E00) * 0.5;
            } else {
                f32 sign = (D_ovl0F_03_80046DFC != 0.0f ? 1.0f : 0);

                drift = func_ovl0F_03_800467F0(view[0]) * (sign * D_ovl0F_03_80046DFC) + D_ovl0F_03_80046E00;
            }
            r = func_ovl0F_03_80046800();
            dy = D_ovl0F_03_800470E8[i].unkC - D_ovl0F_03_80046DF8;
            D_ovl0F_03_800470E8[i].unk4 += dy - r * (dy * 0.6f) + drift;
            D_ovl0F_03_800470E8[i].unk8 -= 0.1f * (D_ovl0F_03_800470E8[i].unk8 * 0.0625f);
            if (340.0f <= D_ovl0F_03_800470E8[i].unk0 || 240.0f <= D_ovl0F_03_800470E8[i].unk4 || D_ovl0F_03_800470E8[i].unk8 <= 3.0f ||
                D_ovl0F_03_800470E8[i].unk10++ >= 240 || D_ovl0F_03_800470E8[i].unk0 < -20.0f || D_ovl0F_03_800470E8[i].unk4 < -10.0f) {
                func_ovl0F_03_800432F0(&D_ovl0F_03_800470E8[i]);
            }
        }
    }
    *gdl = g2;
}

void func_ovl0F_03_80044258(s32 arg0, UnkStruct_ovl0F_03_Gfx **arg1) {
    UnkStruct_ovl0F_03_Gfx *gfx;
    UnkStruct_ovl0F_03_80046DF0 *t;

    gfx = *arg1;
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x00553048; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF279; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xBB000001; g->w1 = 0x80008000; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0x8000; }
    t = D_ovl0F_03_80046DF0;
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xFD100000; g->w1 = t->unk20 + (u32) t; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xE8000000; g->w1 = 0; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xF5000100; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xF0000000; g->w1 = 0x0703C000; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xFD500000; g->w1 = t->unk14 + (u32) t; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xF5500000; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xF3000000; g->w1 = 0x0703F800; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xF5400200; g->w1 = 0; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xF2000000; g->w1 = 0x0003C03C; }
    func_ovl0F_03_80044250(&gfx);
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0x00080000; }
    { UnkStruct_ovl0F_03_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0; }
    *arg1 = gfx;
}

void func_ovl0F_03_80043F38(void) {
    UnkStruct_ovl0F_03_80046F0C *task;
    UnkStruct_ovl0F_03_80046E88 *a;
    UnkStruct_ovl0F_03_80046E88 *b;
    f32 pos[3];
    s32 hit;

    task = func_ovl0F_03_80046670();
    a = task->unk0;
    b = &task->unk0[1];
    func_ovl0F_03_80045B58(a->unkC, a->unk10, a->unk14, pos, 0);
    func_ovl0F_03_800430B4(2, a);
    (*a->unk0)->unk34 = 250.0f;
    (*a->unk0)->unkC = 0;
    (*b->unk0)->unkC = 0;
    (*b->unk0)->unk70 = 2.4500003f;
    while (func_ovl0F_03_800468D0(a->unk28) == 0) {
        hit = func_ovl0F_03_800464A8(*a->unk0, 0x40);
        if (hit != 0) {
            if ((hit & 0x2000) || (hit & 0x4000)) {
                func_ovl0F_03_800468C0(a->unk28);
            } else {
                func_ovl0F_03_80046BF8(0x26, pos);
            }
        }
        func_ovl0F_03_80046668(5);
    }
    func_ovl0F_03_80046BF8(0x8A, pos);
    func_ovl0F_03_80043E60(0x14, pos, 250.0f, 120.0f);
    func_ovl0F_03_80046668(10);
    func_ovl0F_03_80043E60(0x16, pos, 250.0f, 120.0f);
    func_ovl0F_03_80043020(1, a);
    *a->unk0 = NULL;
    func_ovl0F_03_80045B38((s32) b->unkC - 2, (s32) b->unk10, (s32) b->unk14 - 2,
                           (s32) b->unkC + 2, (s32) b->unk14 + 2, 0x1410);
    task->unk58();
    func_ovl0F_03_80046578(*b->unk0);
    func_ovl0F_03_80046690();
    do {
        func_ovl0F_03_80046578(*b->unk0);
        func_ovl0F_03_80046690();
    } while ((*b->unk0)->unk6C != 0.0f);
    task->unk5C();
    func_ovl0F_03_80046658();
}
static void func_ovl0F_03_80043E60(s32 id, f32 *pos, f32 d, f32 h) {
    func_ovl0F_03_80046A98(id, pos[0] + d, pos[1] + h, pos[2] + d, 0);
    func_ovl0F_03_80046A98(id, pos[0] + d, pos[1] + h, pos[2] - d, 0);
    func_ovl0F_03_80046A98(id, pos[0] - d, pos[1] + h, pos[2] + d, 0);
    func_ovl0F_03_80046A98(id, pos[0] - d, pos[1] + h, pos[2] - d, 0);
}

/* its 80044C94 call, inlined into 80044D20 (the stub 80044D18) */
/* a task: the gate rises and the camera follows */
void func_ovl0F_03_80043AF0(void) {
    static s32 D_ovl0F_03_80046E10 = 0;
    UnkStruct_ovl0F_03_80046E88 *task;
    f32 pos[3];

    task = func_ovl0F_03_80046670();
    func_ovl0F_03_80045C68(1);
    func_ovl0F_03_80045C60(0);
    func_ovl0F_03_80045CE8(1);
    func_ovl0F_03_80046668(30);
    func_ovl0F_03_80045CE8(1);
    func_ovl0F_03_80046458();
    func_ovl0F_03_800463A0(0x7F);
    func_ovl0F_03_80046338(2165.0f, 3100.0f, 914.0f);
    func_ovl0F_03_80046358(135.0f, 45.0f, 2400.0f);
    func_ovl0F_03_80046668(30);
    (*task[1].unk0)->unk40->unk14 += 500.0f;
    (*task[1].unk0)->unk40->unk18 -= 500.0f;
    func_ovl0F_03_800464F8(*task[1].unk0, 0x01000000);
    func_ovl0F_03_80046BD0(0x8B);
    while (D_ovl0F_03_80046E10 < 200) {
        (*task[1].unk0)->unk40->unk14 -= 2.5f;
        (*task[1].unk0)->unk40->unk18 += 2.5f;
        D_ovl0F_03_80046E10++;
        func_ovl0F_03_80046690();
    }
    func_ovl0F_03_80046BD0(0x90);
    for (D_ovl0F_03_80046E10 = 0; D_ovl0F_03_80046E10 < 180;) {
        f32 t = func_ovl0F_03_800467F8(D_ovl0F_03_80046E10);

        (*task[1].unk0)->unk40->unk14 += t;
        (*task[1].unk0)->unk40->unk18 -= t;
        D_ovl0F_03_80046E10++;
        func_ovl0F_03_80046690();
    }
    func_ovl0F_03_80046BD0(0x90);
    for (D_ovl0F_03_80046E10 = 0; D_ovl0F_03_80046E10 < 180;) {
        f32 t = func_ovl0F_03_800467F8(D_ovl0F_03_80046E10);

        (*task[1].unk0)->unk40->unk14 += t;
        (*task[1].unk0)->unk40->unk18 -= t;
        D_ovl0F_03_80046E10 += 3;
        func_ovl0F_03_80046690();
    }
    func_ovl0F_03_80046BD0(0x90);
    func_ovl0F_03_80046668(50);
    func_ovl0F_03_80045B58(22.0f, 5.0f, 7.0f, pos, 0);
    pos[1] += 42.0f;
    D_ovl0F_03_80046E0C = func_ovl0F_03_80046AA0(0x25, pos, 0);
    func_ovl0F_03_80046BD0(0x2C);
    func_ovl0F_03_80046668(130);
    func_ovl0F_03_80046460();
    func_ovl0F_03_80046428(D_ovl0F_03_800470A8);
    func_ovl0F_03_80046398(0x1F);
    func_ovl0F_03_80045C68(0);
    func_ovl0F_03_80045C60(1);
    func_ovl0F_03_80045CE8(0);
    func_ovl0F_03_80046658();
}

/* a task: the gate sinks back */
void func_ovl0F_03_80043944(void) {
    static s32 D_ovl0F_03_80046E14 = 0;
    UnkStruct_ovl0F_03_80046E88 *task;
    UnkStructA *obj;

    task = func_ovl0F_03_80046670();
    obj = func_ovl0F_03_80045D38(func_ovl0F_03_80045CD8());
    func_ovl0F_03_8004393C();
    while (D_ovl0F_03_80046E14 < 400) {
        (*task[1].unk0)->unk40->unk14 += 3.75f;
        (*task[1].unk0)->unk40->unk18 -= 3.75f;
        obj->unk40->unk14 += 3.75f;
        D_ovl0F_03_80046E14++;
        func_ovl0F_03_80046690();
    }
    func_ovl0F_03_80046658();
}

/* .data after func_ovl0F_03_80043944's static */
f32 D_ovl0F_03_80046E18 = 3.0f;
/* passed to func_ovl0F_03_800469B0: three 12-byte records */
u32 D_ovl0F_03_80046E1C[][3] = {
    { 0x2640002, 0xF, 4 },
    { 0x25C0002, 0xF, 4 },
    { 0x25A0002, 0xF, 4 },
};
/* six 12-byte records, each passed to func_ovl0F_03_80046B58 */
u32 D_ovl0F_03_80046E40[][3] = {
    { 0, 0x12, 0xF0 },
    { 1, 0x13, 0xF1 },
    { 2, 0x16, 0xF4 },
    { 3, 0, 0xDE },
    { 4, 2, 0xE0 },
    { 5, 0x15, 0xF3 },
};
UnkStruct_ovl0F_03_80046E88 D_ovl0F_03_80046E88 = {
    &D_ovl0F_03_80047090[0], 0x261, 0, 21.0f, 5.0f, 9.0f, 0.0f, 0.0f, 0.0f, 0, 0,
};
UnkStruct_ovl0F_03_80046E88 D_ovl0F_03_80046EB4[2] = {
    { &D_ovl0F_03_80047090[1], 0x1B3, 0, 22.0f, 2.0f, 31.0f, 0.0f, 0.0f, 0.0f, 0, 0x404 },
    { &D_ovl0F_03_80047090[2], 0x262, 0, 22.0f, 5.0f, 7.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};
UnkStruct_ovl0F_03_80046F0C D_ovl0F_03_80046F0C = {
    {
        { &D_ovl0F_03_80047090[3], 0x25F, 0, 22.0f, 2.0f, 28.0f, 0.0f, 0.0f, 0.0f, 0, 0x401 },
        { &D_ovl0F_03_80047090[4], 0x260, 0, 22.0f, 3.0f, 28.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    },
    func_ovl0F_03_80045680,
    func_ovl0F_03_800456BC,
};
/* func_ovl0F_03_80043284's: four arguments to test, three to pass on */
s32 D_ovl0F_03_80046F6C[7] = { 1, 0x1A, 2, 0x1B, 0x59, 0x13, 0 };
s32 D_ovl0F_03_80046F88[7] = { 0x2D, 0x1B, 0x2E, 0x1C, 0x5B, 0x13, 0 };
UnkStruct_ovl0F_03_80046FE4 D_ovl0F_03_80046FA4[2] = {
    { 0x20, 3, 8.5f, 3, 0, 1, 1 },
    { 0xE0, 3, 8.5f, 2, 0, 1, 0 },
};
UnkStructA *D_ovl0F_03_80046FDC = NULL;
char D_ovl0F_03_80046FE0[] = "MA";
UnkStruct_ovl0F_03_80046FE4 D_ovl0F_03_80046FE4 = { 0, 3, 3.75f, 15, 0, 0, 0 };

static void func_ovl0F_03_8004393C(void) {
    func_ovl0F_03_800465D8(0.0f);
    func_ovl0F_03_800465E0(0x7F);
    if (D_ovl0F_03_80046E0C != -1) {
        func_ovl0F_03_80046AA8(D_ovl0F_03_80046E0C);
    }
    func_ovl0F_03_80046668(250);
    func_ovl0F_03_80045D10(1);
    func_ovl0F_03_80045D40(1);
    func_ovl0F_03_800463C0(30.0f);
    func_ovl0F_03_800463C8(1.0f);
    func_ovl0F_03_800463E0(10.0f);
    func_ovl0F_03_80045CF8(D_ovl0F_03_80046FE4.unk0, D_ovl0F_03_80046FE4.unk4, D_ovl0F_03_80046FE4.unk8,
                           D_ovl0F_03_80046FE4.unkC, D_ovl0F_03_80046FE4.unk10, D_ovl0F_03_80046FE4.unk14,
                           D_ovl0F_03_80046FE4.unk18);
    func_ovl0F_03_80046BD0(0x8E);
}

/* a task: the camera waits for the player to pass x 4400 */
void func_ovl0F_03_8004389C(void) {
    UnkStructA *obj;

    obj = func_ovl0F_03_80045D38(func_ovl0F_03_80045CD8());
    while (4400.0f < obj->unk40->unk10) {
        func_ovl0F_03_80046690();
    }
    func_ovl0F_03_80046668(30);
    func_ovl0F_03_80045D00("MA");
    func_ovl0F_03_80046658();
}

void func_ovl0F_03_8004377C(UnkStructA *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl0F_03_800463A0(0x10);
    }
    dx = arg0->unk40->unk28 / 30.0f;
    dy = arg0->unk40->unk2C / 30.0f;
    dz = arg0->unk40->unk30 / 30.0f;
    func_ovl0F_03_80046500(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        arg0->unk40->unk28 -= dx;
        arg0->unk40->unk2C -= dy;
        arg0->unk40->unk30 -= dz;
        func_ovl0F_03_80046578(arg0);
        func_ovl0F_03_80046690();
    }
    func_ovl0F_03_80046500(arg0, 0x01000000);
}

static void func_ovl0F_03_800434A4(UnkStructA *arg0, f32 *pos);
static s32 func_ovl0F_03_80043494(UnkStructA *arg0);
static void func_ovl0F_03_8004348C(UnkStructA *arg0, f32 *pos);
static void func_ovl0F_03_8004349C(UnkStructA *arg0, f32 angle);

/* the pushed blocks' callback */
void func_ovl0F_03_800434AC(UnkStructA *arg0) {
    f32 dist;
    f32 angle;
    f32 pos[3];

    dist = 0.0f;
    angle = 0.0f;
    if (arg0->unk68 != 0.0f || arg0->unk6C != 0.0f) {
        return;
    }
    func_ovl0F_03_800434A4(arg0, pos);
    func_ovl0F_03_80045B80(arg0->unk40, &dist, &angle);
    if (dist == 0.0f) {
        return;
    }
    func_ovl0F_03_8004349C(arg0, angle);
    if (func_ovl0F_03_80043494(arg0)) {
        func_ovl0F_03_8004348C(arg0, pos);
    }
}

#line 1 "panels.c"
static void func_ovl0F_03_800434A4(UnkStructA *arg0, f32 *pos) {
    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14;
    pos[2] = arg0->unk40->unk18;
}
#line 719 "1EE1A0.c"

static s32 func_ovl0F_03_80043494(UnkStructA *arg0) {
    s32 hit;
    s32 saved;
    UnkStructA *other;
    s32 id;

    hit = 0;
    other = NULL;
    saved = arg0->unkC;
    arg0->unkC = 0;
    if (arg0->unk8 & 1) {
        other = func_ovl0F_03_80045D78(func_ovl0F_03_80045CD8());
    } else if (arg0->unk8 & 2) {
        id = func_ovl0F_03_80045CD8();
        if (func_ovl0F_03_80045D78(id) == arg0) {
            other = func_ovl0F_03_80045D38(id);
        } else {
            other = NULL;
        }
    }
    if (other != NULL) {
        if (func_ovl0F_03_80046618(arg0, 0x10, other) != 0) {
            hit = 1;
        }
    } else if (func_ovl0F_03_800464A8(arg0, 0x10) != 0) {
        hit = 1;
    }
    arg0->unkC = saved;
    return hit;
}

static void func_ovl0F_03_8004348C(UnkStructA *arg0, f32 *pos) {
    arg0->unk40->unk10 = pos[0];
    arg0->unk40->unk14 = pos[1];
    arg0->unk40->unk18 = pos[2];
}

static void func_ovl0F_03_8004349C(UnkStructA *arg0, f32 angle) {
    f32 mult;
    s32 dir;

    mult = 1.0f;
    dir = 0xFFFF;
    switch ((s32) angle) {
        case 0:
            dir = 0x80;
            if (arg0->unk60 < arg0->unk40->unk18) {
                mult = 2.5f;
            }
            break;
        case 90:
            dir = 0x40;
            if (arg0->unk58 < arg0->unk40->unk10) {
                mult = 2.5f;
            }
            break;
        case 270:
            dir = 0xC0;
            if (arg0->unk40->unk10 < arg0->unk58) {
                mult = 2.5f;
            }
            break;
        case 180:
            dir = 0;
            if (arg0->unk40->unk18 < arg0->unk60) {
                mult = 2.5f;
            }
            break;
    }
    if (dir != 0xFFFF) {
        func_ovl0F_03_80046B48(arg0, dir, D_ovl0F_03_80046E18 * mult);
    }
}

void func_ovl0F_03_80043444(f32 arg0) {
    f32 sp1C;

    func_ovl0F_03_80046360(&sp1C, NULL, NULL);
    func_ovl0F_03_80046358(sp1C + arg0, 32768.0f, 32768.0f);
}

static void func_ovl0F_03_800432F0(UnkStruct_ovl0F_03_800470E8 *p) {
    f32 r;
    f64 t;

    r = func_ovl0F_03_80046800();
    p->unk0 = func_ovl0F_03_80046800() * 370.0 - 50.0;
    t = func_ovl0F_03_80046800();
    p->unk4 = (D_ovl0F_03_80046DFC < 0 ? -D_ovl0F_03_80046DFC : D_ovl0F_03_80046DFC) * 30.0f * t;
    if (D_ovl0F_03_80046DF8 <= 0.0f) {
        p->unk4 += (1.0f - r) * 40.0f;
    } else {
        p->unk4 += func_ovl0F_03_80046808(90);
    }
    p->unk10 = 0;
    p->unk8 = r * 12.0f + 4.0f;
    p->unkC = r * r * 5.0f + 0.5f;
}

static void func_ovl0F_03_80043284(s32 *arg0) {
    if (func_ovl0F_03_80045CC0(arg0[0], arg0[1], arg0[2], arg0[3]) != 0) {
        func_ovl0F_03_80045BF0(arg0[4], arg0[5], arg0[6]);
    }
}

static void func_ovl0F_03_80043164(UnkStruct_ovl0F_03_80046E88 *arg0, s32 arg1) {
    f32 pos[3];

    if (func_ovl0F_03_800468D0(arg0->unk28) != 0) {
        if (arg1 != 0) {
            func_ovl0F_03_80045B58(22.0f, 5.0f, 7.0f, pos, 0);
            pos[1] += 42.0f;
            D_ovl0F_03_80046E0C = func_ovl0F_03_80046AA0(0x25, pos, 0);
        }
        arg0->unk4 = 0x1B0;
        func_ovl0F_03_80045B38(0x16, 5, 7, 0x16, 7, 0x2012);
        D_ovl0F_03_80046E08 = 2;
    } else {
        arg0->unk4 = 0x1B3;
        D_ovl0F_03_80046E08 = 1;
    }
    func_ovl0F_03_800430B4(D_ovl0F_03_80046E08, arg0);
    (*arg0->unk0)->unk40->unk14 += 42.0f;
}

static void func_ovl0F_03_800430B4(s32 arg1, UnkStruct_ovl0F_03_80046E88 *arg0) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *arg0->unk0 = func_ovl0F_03_80046568(arg0->unk4, arg0->unk8);
        func_ovl0F_03_800464F8(*arg0->unk0, arg0->unk24 | 0x01000000);
        func_ovl0F_03_80043030(arg0);
        (*arg0->unk0)->unk40->unk1C = arg0->unk18;
        (*arg0->unk0)->unk40->unk20 = arg0->unk1C;
        (*arg0->unk0)->unk40->unk24 = arg0->unk20;
        arg0++;
    }
}

static void func_ovl0F_03_80043030(UnkStruct_ovl0F_03_80046E88 *arg0) {
    f32 pos[3];

    func_ovl0F_03_80045B58(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

/* case 4's: the particles' texture and display list */
static void func_ovl0F_03_80043434(void) {
    UnkStructA *obj;

    if (0) {
        func_ovl0F_03_80046648(func_ovl0F_03_80044C20, NULL, 0, 0, 0);
    }
    D_ovl0F_03_80046DF0 = func_ovl0F_03_800461C8(0x258);
    obj = func_ovl0F_03_80046258(func_ovl0F_03_80044258, -60);
    D_ovl0F_03_80047284 = obj;
    obj->unkC |= 0x210;
}

/* case 2's: the door, closed or already open */
static void func_ovl0F_03_80044C7C(UnkStruct_ovl0F_03_80046F0C *door) {
    s32 pad[2];
    if (func_ovl0F_03_800468D0(door->unk0[0].unk28) == 0) {
        func_ovl0F_03_80046648(func_ovl0F_03_80043F38, door, 0, 0, 0x110);
    } else {
        door->unk58();
        door->unk5C();
        door->unk0[1].unk10 -= 1.0f;
        func_ovl0F_03_800430B4(1, &door->unk0[1]);
        *door->unk0[0].unk0 = NULL;
        door->unk0[1].unk10 += 1.0f;
    }
}

static void func_ovl0F_03_80043020(s32 count, UnkStruct_ovl0F_03_80046E88 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_03_80046510(*p->unk0);
        p++;
    }
}

static void func_ovl0F_03_8004326C(void) {
    if (func_ovl0F_03_800468D0(0x404) == 0 && func_ovl0F_03_80045CC0(0x16, 0x1F, 0x16, 0x1F) != 0) {
        func_ovl0F_03_80045D20(0x40);
        func_ovl0F_03_80045CE8(1);
        func_ovl0F_03_80046BB8();
        func_ovl0F_03_80046AD8();
        func_ovl0F_03_80045D10(1);
        func_ovl0F_03_80046BD0(0x29);
        func_ovl0F_03_800468C0(D_ovl0F_03_80046EB4[0].unk28);
        func_ovl0F_03_80043020(1, D_ovl0F_03_80046EB4);
        func_ovl0F_03_80043164(D_ovl0F_03_80046EB4, 0);
        func_ovl0F_03_80046500(*D_ovl0F_03_80046EB4[1].unk0, 0x01000000);
        func_ovl0F_03_80046648(func_ovl0F_03_80043AF0, D_ovl0F_03_80046EB4, 0, 0, 0x130);
    }
}

static void func_ovl0F_03_80043274(s32 *p) {
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

static void func_ovl0F_03_8004327C(void) {
    s32 pad[10];
    if (func_ovl0F_03_800468D0(0x404) != 0 && func_ovl0F_03_80045CC0(0x16, 7, 0x16, 7) != 0) {
        func_ovl0F_03_80045D10(1);
        func_ovl0F_03_80045C70(0);
        func_ovl0F_03_80046648(func_ovl0F_03_80043944, D_ovl0F_03_80046EB4, 0, 0, 0x130);
        func_ovl0F_03_80043274(func_ovl0F_03_800468E0(0x21));
        func_ovl0F_03_80045C18();
    }
}

static void func_ovl0F_03_800432D0(void) {
    switch (func_ovl0F_03_80045BF8()) {
        case 0x12:
            func_ovl0F_03_80045CF8(D_ovl0F_03_80046FA4[0].unk0, D_ovl0F_03_80046FA4[0].unk4,
                                   D_ovl0F_03_80046FA4[0].unk8, D_ovl0F_03_80046FA4[0].unkC,
                                   D_ovl0F_03_80046FA4[0].unk10, D_ovl0F_03_80046FA4[0].unk14,
                                   D_ovl0F_03_80046FA4[0].unk18);
            break;
        case 0x14:
            func_ovl0F_03_80045CF8(D_ovl0F_03_80046FA4[1].unk0, D_ovl0F_03_80046FA4[1].unk4,
                                   D_ovl0F_03_80046FA4[1].unk8, D_ovl0F_03_80046FA4[1].unkC,
                                   D_ovl0F_03_80046FA4[1].unk10, D_ovl0F_03_80046FA4[1].unk14,
                                   D_ovl0F_03_80046FA4[1].unk18);
            func_ovl0F_03_80046648(func_ovl0F_03_8004389C, NULL, 0, 0, 0x130);
            break;
    }
}

/* case 4's: the callbacks */
static void func_ovl0F_03_8004343C(void) {
    func_ovl0F_03_80045D08();
    func_ovl0F_03_80045BE0(func_ovl0F_03_8004377C);
    func_ovl0F_03_80046998(0xE6, 0xF0, 0xFF);
    func_ovl0F_03_80046988(0x3B1, 0x3CA, 0xE6, 0xF0, 0xFF);
    func_ovl0F_03_80045C48();
    func_ovl0F_03_80045BD8(func_ovl0F_03_800434AC, 1);
}

/* case 4's: the particles */
static void func_ovl0F_03_8004342C(void) {
    s32 i;

    for (i = 0; i < 20; i++) {
        func_ovl0F_03_800432F0(&D_ovl0F_03_800470E8[i]);
        D_ovl0F_03_800470E8[i].unk4 = func_ovl0F_03_80046808(240);
    }
}

#line 1 "panels.c"
static void func_ovl0F_03_800432E8(void) {
    func_ovl0F_03_80046440(&D_ovl0F_03_80047278);
}
#line 965 "1EE1A0.c"

static void func_ovl0F_03_800432E0(void) {
    D_ovl0F_03_80046DFC = 0.0f;
    D_ovl0F_03_80046E00 = 0.0f;
    D_ovl0F_03_80046E04 = 1.0f;
}

static void func_ovl0F_03_800432D8(void) {
    func_ovl0F_03_800468C0(0x407);
    func_ovl0F_03_800465D8(40.0f);
    func_ovl0F_03_800465E0(30);
}

/* case 2's: the stage's tables */
#line 1 "panels.c"
static void func_ovl0F_03_80044C8C(u32 (*p)[3], s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_03_80046B58((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}
#line 987 "1EE1A0.c"

static void func_ovl0F_03_80044C84(void) {
    func_ovl0F_03_80045AF8(0x226);
    func_ovl0F_03_80045B10(0x239);
    func_ovl0F_03_80045CA8();
}

static void func_ovl0F_03_80043028(void) {
}

static void func_ovl0F_03_80043018(void) {
    D_ovl0F_03_800470C4 = func_ovl0F_03_80045CD8();
    func_ovl0F_03_80045CB8(&D_ovl0F_03_800470B8);
    func_ovl0F_03_80045CE0(D_ovl0F_03_800470C4, D_ovl0F_03_800470A8);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_03_80044C94(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0F_03_800469B0(D_ovl0F_03_80046E1C);
            func_ovl0F_03_80044C8C(D_ovl0F_03_80046E40, 6);
            func_ovl0F_03_80044C84();
            func_ovl0F_03_800430B4(1, &D_ovl0F_03_80046E88);
            func_ovl0F_03_80044C7C(&D_ovl0F_03_80046F0C);
            func_ovl0F_03_80043164(D_ovl0F_03_80046EB4, 1);
            D_ovl0F_03_80046FDC = func_ovl0F_03_80046520(0x323, 0x1000010, 0xC0, 0);
            D_ovl0F_03_80046FDC->unk40->unk10 = 3600.0f;
            D_ovl0F_03_80046FDC->unk40->unk14 = 0.0f;
            D_ovl0F_03_80046FDC->unk40->unk18 = 1900.0f;
            D_ovl0F_03_80046FDC->unk40->unk20 = 0.0f;
            break;
        case 18:
            func_ovl0F_03_80045CF0(0x20);
            func_ovl0F_03_80045CB0(2, 0, 0x1A);
            break;
        case 19:
            func_ovl0F_03_80045CB0(0x16, 5, 0x16);
            break;
        case 20:
            func_ovl0F_03_80043444(180.0f);
            func_ovl0F_03_80045CF0(0xE0);
            func_ovl0F_03_80045CB0(0x2D, 0, 0x1B);
            break;
        case 4:
            func_ovl0F_03_8004343C();
            func_ovl0F_03_80043434();
            func_ovl0F_03_8004342C();
            func_ovl0F_03_800432E8();
            func_ovl0F_03_800432E0();
            func_ovl0F_03_800432D8();
            break;
        case 5:
            func_ovl0F_03_800432D0();
            break;
        case 0x50:
            func_ovl0F_03_80043284(D_ovl0F_03_80046F6C);
            func_ovl0F_03_80043284(D_ovl0F_03_80046F88);
            func_ovl0F_03_8004327C();
            break;
        case 0x52:
            func_ovl0F_03_8004326C();
            break;
        case 15:
            /* the empty static 80043028 called, its body here (the header) */
            func_ovl0F_03_80043028();
            {
                f32 y;

                if (func_ovl0F_03_80045CC8(0x24, 0, 0x14, 0x24, 0x14) != 0) {
                    y = func_ovl0F_03_80045D38(func_ovl0F_03_80045CD8())->unk40->unk20;
                    if (135.0f <= y && y <= 225.0f) {
                        if (func_ovl0F_03_800468B0(0xA4) != 0) {
                            func_ovl0F_03_80046260(0x291, 1);
                        } else {
                            func_ovl0F_03_80046260(0x277, 4);
                        }
                    }
                }
            }
            break;
        case 1:
            func_ovl0F_03_80043020(1, &D_ovl0F_03_80046E88);
            if (func_ovl0F_03_800468D0(D_ovl0F_03_80046F0C.unk0[0].unk28) == 0) {
                func_ovl0F_03_80043020(2, D_ovl0F_03_80046F0C.unk0);
            } else {
                func_ovl0F_03_80043020(1, &D_ovl0F_03_80046F0C.unk0[1]);
            }
            *D_ovl0F_03_80046F0C.unk0[0].unk0 = NULL;
            func_ovl0F_03_800461E8(D_ovl0F_03_80047284);
            if (D_ovl0F_03_80046E08 != 0) {
                func_ovl0F_03_80043020(D_ovl0F_03_80046E08, D_ovl0F_03_80046EB4);
            }
            func_ovl0F_03_800461D0(0x258);
            break;
        case 12:
            func_ovl0F_03_80045D40(1);
            break;
        case 3:
            func_ovl0F_03_80043018();
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
        case 16:
        case 17:
            break;
    }
}

void func_ovl0F_03_80043010(void) {
}
