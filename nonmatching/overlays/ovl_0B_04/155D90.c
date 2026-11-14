/*
 * NON_MATCHING: ovl_0B_04's game object (the name-entry screen: a name of
 * eight characters from four character sets, and four slots of ten choices
 * each), complete: every function and its data. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 0, eu 0, jp 5
 *
 * The pages are a table (D_ovl0B_04_800499B8: texts, handler, cursor
 * table, set-up) that func_ovl0B_04_80043ADC runs in turn; pages 1-4 are
 * the character sets, 5-8 the slots, 9 the save question. The statics
 * the original passes arguments to in $s/$t registers (80043050, 800438FC
 * (id, mode, item), 80043A24/80043A7C (n, ids, items), 8004401C/800440C8,
 * 80044394, 8004447C, 800447DC, 80045540, 800458F4/80045958 (two text
 * ids), 80046294, 80046600/80046734 (item first), 800468F0) are statics
 * with ordinary parameters. Inlined statics stand where the original has
 * their stubs: the handler 80043110's cases (H1/H4/H5, H5's four parts,
 * H1's FreeEntry, with MakeEntries and FreeEntries the ten stubs around
 * 80043050), MakeEntries/FreeEntries (index
 * loops: IDO never inlined them as pointer loops), the text-freeing
 * 80043AD4 (its own ids pointer), 80044BE0 (80044BE8's name copy,
 * unrolled), 80045530/80045538 (80045540's name check and frees),
 * 800450B8 (page 9's save, p5), 80044714 (the marks, r an int), SetText.
 * Emission order: IDO -O3 takes the globals in reverse definition order
 * and puts each one's static callees just before it, in the reverse order
 * of its calls (each after its own callees); the `if (0)` call lists at
 * the end of 800444E8, 800459C4, 80046AA0 and the others pull the
 * original's runs of statics and stubs into place. An indirect call pulls
 * every function whose address the code takes: 80043ADC's would pull
 * 80043CD0 in front of it, so 80043CD0 ends with a dead call to
 * 80043ADC and is defined just after it: 80043CD0's turn comes first and
 * puts 80043ADC (with its statics) out before it. FreeEntries is named
 * for the first stub, 80043010, so nonmatching.py compares the lead run.
 * 800447DC's D_ovl0B_04_8004A1A0 is one too (as a file-scope one its
 * address took $a0, where the original uses lui each time).
 * 800436C8's counter D_ovl0B_04_8004A1E4 is a function-scope static (as a
 * file-scope one uopt keeps its address in a register).
 *
 * jp (`#if VERSION_JP`): its 0x250C/0x250D calls go to 0x2501/0x2503 (one
 * text function, so no 80043A7C; page 0's six labels in one call), no
 * set clamp in 800441C4 (which jp inlines), 80044394 places the name at
 * 56 - 8n, no menu-cursor fade in 800444E8/800468F0 nor page 0's 0x80
 * flags, 80045214's texts at x 55/50, R goes to set 1, 80045E24's second
 * text, 80046294 sets the choices' strings in place and 80046734 lights
 * only open ones; one stub fewer at 80043F3C. jp's .bss differs: the fade
 * pointer is its last word (vermap name D_ovl0B_04_8004A4A4; us's name is
 * #defined to it) and 80043F24's two words are A3EC/A3F0 (us's A3F0/A3F4),
 * found by fcmp's relocation check. jp's .data and the rest of its .bss
 * are still us's (nonmatching.py doesn't compare them; jp's strings and
 * the rest of its .bss layout, e.g. no A40C, are to do).
 *
 * What still differs (words us/jp; the comparison counts a global with
 * the statics after it, so a static of the wrong size costs the rest of
 * its run):
 * - 80043110 0/0 (matches; p4). The frame: FreeEntries (n, e, x) with x
 *   unused and no other local (16-byte areas, as the original's homes'
 *   spacing shows); H1's final free is an inlined FreeEntry(e, i) (the 8
 *   bytes below the second FreeEntries that the end-pointer spill's place
 *   needs); case 12 calls 800487E8 directly (no H12), which keeps the stub
 *   count; H5a's i is at the original's 132 (H5a K&R, frame-tuned; p4: no
 *   pad, H1 (void), four dead calls in H4). H5b: the slots are plain
 *   names except &D_ovl0B_04_8004A17C's copy load (a volatile cast, fake: plain, uopt's
 *   PRE keeps the pointer from the copy to the second test along its skip
 *   edge, which lowers &A17C's uses until &A180 takes $s0); the first test
 *   has its own variable and x is read once before its first assignment
 *   (fake: live from the start, so the later tests' x avoids $v0 and the
 *   first test's value goes to $a3 after A178's pointer takes $v1). 0x150A
 *   (80047E28) is `s32 (Obj *, s32)` as 0B_06's 80048888, which puts H5a's
 *   object in $v1 as in the original.
 *   H5b's calls pass `(x += 1, x - 1)` for the original's `addiu a2,v1,0`
 *   copy (fake), the first with (&A16C)[1] for A170 (fake). H5a's
 *   last store (A170) is numbered below the line after it (`#line`,
 *   fake) for its place in the jal's delay slot.
 * - 800436C8 0/0 (matches): `b = a = -1` is numbered above the loop head (`#line`,
 *   fake), so as1 hoists its `li a1,-1` into the head's load delay, right
 *   after the jal, as the original has it (any C with the -1 outside the
 *   if hoists it to an s-register instead). 800438FC's cases set d before col
 *   for the original's schedule.
 * - 800444E8 0/0 (matches; p4). 80044714 returns s32 (s8 made a
 *   sll/sra pair whose temp put the ugen temps one ahead, and gave d1 $s3
 *   and n $s2). d1's first test is a plain `if (d1)`, every later one and
 *   d2/d3's `!= 0`: the int-promoted value is its own uopt expression,
 *   which takes $s2 from the first chain on while d1 stays in $t0 (the
 *   original's `move s2,t0`; cvt(d2)/cvt(d3) are its `move v1,s4`/`move
 *   v0,s5`). That also gives the frame (24) without p2's dead reads and
 *   `do {} while (0)`. The counter D_ovl0B_04_8004A1A0 (function-scope
 *   static) is incremented before its test (`A1A0++; if (n < A1A0)`):
 *   uopt keeps it in $v1 and stores it back per path, as the original. The
 *   unk1 test is written `c != X` for the beq's operand order; unk1 is
 *   stored through the neighbour, (&D_ovl0B_04_8004A480)[1][1] (fake), for
 *   the original's own lui.
 * - 80045214 0/0 (matches; p5). The save is the inlined static 800450B8
 *   returning ok (its stub; 800450C0's fade is written out, and a dead call
 *   from 80045214 (fake) pulls 800450C0 out after the stub): the test reads
 *   the inlined return value, `lw t8,ok; move v0,t8` in ugen, one load into
 *   $v0 after as1, with the original's temps after it. 80045540: its unk3
 *   store goes through a copy of item (`x = item; ... unk3 = x`): copy
 *   propagation makes uopt fold the store into a direct one with its own
 *   `lui at`, as in the original. The rub-out is the flat test
 *   `(unk0 == 7 && c == 0) || (unk0 != 7 && unk0 > 0)` on the global, a
 *   dead `if (unk1) {}` first in its arm (fake: one more use of the base,
 *   which then takes s0) and c's read on the `if (buttons & 2)` line (its
 *   .loc). The decrement is `unk0 = ((u32) unk0 - 1) & 0xFF` (p5): the
 *   unsigned arithmetic keeps unk0's own value (s1; any int arithmetic
 *   reads the promoted copy in v1), and ugen's `and 255` before the sb,
 *   which as1 drops, uses up the temporary the original's t-registers are
 *   one ahead by (p2-p4's `c = A290[..] ^ 0` did that but left c in t6).
 * - 80043ADC 0/0 (matches; w5): us's loop is `if (A168 != 0xFF) { p3 =
 *   &tbl[3]; if (!p3) {} do { ... } while (A168 != 0xFF); }` with p4 =
 *   &tbl[4] set at the top and one more dead read of p3 after the else
 *   arm's 80043A24 call. p3/p4 are copy-propagated to the constants
 *   tbl+108/tbl+144, which then stay separate uopt candidates instead of
 *   folding into the table base (a literal &tbl[3] in the test becomes
 *   base+108 once the base has a register). The second dead read gives
 *   tbl+108 two loop uses (save 20/8 = 2.5) so it is coloured before the
 *   table base (10/7) and the stride 36 (10/7, which then gets no register,
 *   so the multiply is shifts again); tbl+144 keeps one use and is reloaded
 *   with lui each time as in the original. The dead read must be in that
 *   arm: anywhere else adds a uopt block (the base's n grows and A168's
 *   address wins its register) or extends the range before the loop. The
 *   if/do shape puts p3's load at its own statement in the preheader, and
 *   writing that statement on the `if` line gives both preheader la's one
 *   .loc, so as1 orders them lui s7, lui fp, addiu fp, addiu s7 (fake).
 * - 80044BE8 0/5 (p2; was 8/16, the MakeEntries homes high): the K&R
 *   stubs 800445BC, 80044624 and 8004461C were called from 80044BE8's dead
 *   list at its end, and any inlined call after the second MakeEntries
 *   costs its 4 bytes of alignment below it (the front end's frame then
 *   ends 4 below the original's). They are called from the statics they
 *   stand before instead: 800445C4 calls 800445BC, 8004462C calls 80044624
 *   then 8004461C (first statements; the emission order is unchanged), and
 *   80044BE8 has `s32 pad[3]` (jp [1]) after its locals (frame-tuned).
 *   jp's `changed` (p4): uopt treats $v0 as a variable (R2) and the
 *   function's blocks as one loop, so any read of a call's result makes
 *   R2 live through the changed test and `changed` takes $v1. us/eu read
 *   80048668's results in case 1; jp has no such read, so the dead
 *   `i = func_ovl0B_04_800487D0(1)` (fake) stands for it. jp left (5): the
 *   inlined 800441C4's &D_ovl0B_04_8004A490 in a0 for a1 (a jp-only body
 *   rewrite, locals, a `Cursor *`, dead reads of arg0 in case 1: nothing).
 *   80043F24 0/0 (matches; 80044394: `n - 1` in its own m with a dead read, fake,
 *   gives the original's addiu v0,v1,-1; its header line numbered after
 *   the body's (`#line`, fake) lets as1 put the `sw ra` in the first
 *   branch's delay slot, and `n = 0` numbered before the [8] store puts
 *   `move v1,zero` where the original has it), 80046180 0/0 (p5: 800438FC
 *   takes (id, mode, item): IPA keeps mode in $a0, but every call now
 *   sets $a0 after the id, so jp 80046734's `li a0,1` comes after the
 *   ids index's sll as in the original; jp 80046294's mode, a ternary,
 *   goes through a local m, which the original evaluates first; jp
 *   800468F0's loop takes the paired dead reads `if (!o) {} if (!base) {}`).
 * Everything else matches.
 * 80044BE8 with a/b/i block-scoped or #if'd out, no `changed`,
 * hand-written MakeEntries loops or an unrolled 80044BE0 (the homes are
 * counted from the bottom of the frame: dropping a/b in jp shrinks the
 * frame by 8 but leaves them at 84/96/112).
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
    /* 0x1A */ u16 unk1A;
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
s32 func_ovl0B_04_80047E28(Obj *, s32); /* 0x150A */
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
s32 func_ovl0B_04_80048268(s32); /* 0x1904 */
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
#if !VERSION_JP
s32 func_ovl0B_04_80048688(u8 *, u16, u16, f32, f32, s32); /* 0x250C */
s32 func_ovl0B_04_80048690(s32, u8 *, s32); /* 0x250D */
#endif
s32 func_ovl0B_04_800487D0(s32); /* 0x2B00 */
void func_ovl0B_04_800487E0(s32); /* 0x2B02 */
void func_ovl0B_04_800487E8(void); /* 0x2B03 */
void func_ovl0B_04_800487F0(s32, f32, f32, f32); /* 0x2B04 */
s32 func_ovl0B_04_80048910(void); /* 0x2F0A */

#if VERSION_JP
/* jp's ZeroJump block ends at 0x250A: its calls of us's 0x250C and 0x250D
 * go to 0x2501 and 0x2503 */
#define func_ovl0B_04_80048688 func_ovl0B_04_80048630
#define func_ovl0B_04_80048690 func_ovl0B_04_80048640
#endif

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
#if VERSION_JP
/* jp's .bss differs (vermap.jp.txt names): the fade pointer is the last
 * word (A4A4, below), the two words 80043F24 sets are A3EC/A3F0 */
s32 D_ovl0B_04_8004A3EC;
s32 D_ovl0B_04_8004A3F0;
#define D_ovl0B_04_8004A3E4 D_ovl0B_04_8004A4A4
#else
Fade *D_ovl0B_04_8004A3E4;
s32 D_ovl0B_04_8004A3F0;
s32 D_ovl0B_04_8004A3F4;
#endif
Vec3f D_ovl0B_04_8004A3F8;
Page *D_ovl0B_04_8004A404;
s32 D_ovl0B_04_8004A40C[15];
s32 D_ovl0B_04_8004A448[8];    /* the name's characters */
s32 D_ovl0B_04_8004A468[6];
u8 D_ovl0B_04_8004A480[16];
Cursor D_ovl0B_04_8004A490;
u8 D_ovl0B_04_8004A498[8];
s32 D_ovl0B_04_8004A4A0;
#if VERSION_JP
Fade *D_ovl0B_04_8004A4A4;
#endif

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
s32 D_ovl0B_04_8004A1A4 = 0;
s32 D_ovl0B_04_8004A1A8 = 0;
s32 D_ovl0B_04_8004A1AC[14] = { 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1 };

static void func_ovl0B_04_80043050(Entry *e, Desc *d);
static void func_ovl0B_04_80043010(s32 n, Entry *e, s32 x);
static void func_ovl0B_04_800438FC(s32 id, u32 mode, Item *it);
static void func_ovl0B_04_80043A24(s32 n, s32 *ids, Item *items);
#if !VERSION_JP
static void func_ovl0B_04_80043A7C(s32 n, s32 *ids, Item *items);
#endif
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
static s8 func_ovl0B_04_8004462C(u8 set, u8 c);
static s8 func_ovl0B_04_8004471C(u8 set, u8 c);
static void func_ovl0B_04_800447DC(u16 buttons, u8 *ret);
static void func_ovl0B_04_80046294(u8 item);
static void func_ovl0B_04_80046600(u8 item, u16 buttons);
static void func_ovl0B_04_80046734(u8 item, u16 buttons);
static void func_ovl0B_04_800468F0(s32 base);
static void func_ovl0B_04_80045540(u8 item, u16 buttons, u8 *ret);
static void func_ovl0B_04_800458F4(s32 id0, s32 id1);
static void func_ovl0B_04_80045958(s32 id0, s32 id1);
static void func_ovl0B_04_80045850(void);
static void func_ovl0B_04_80043640(f32 d);
static s32 func_ovl0B_04_80044714(u8 set, u8 c);

/* A text drawn centred on an item (its string evaluated twice). */
#define DRAW_ITEM(str, it) \
    func_ovl0B_04_80048688((str), (it)->unk4 - (s32) (func_ovl0B_04_80048680(str) * 0.6f / 2) + 40, (it)->unk6, (it)->unk8, \
                           (it)->unkC, 1)
/* Pages 5-8: an item's line in the page's half. */
#define HALF_IDX(item, half) ((item) < 11 ? (item) - (half) * 5 : 6)
#define PAGE_IDX(item) HALF_IDX(item, D_ovl0B_04_8004A1A8)

static void func_ovl0B_04_800436C0(void) {
}

static void func_ovl0B_04_800438F4(void) {
}

/* A page's texts freed (inlined). */
static void func_ovl0B_04_80043AD4(s32 *ids, s32 n) {
    s32 i;

    for (i = 0; i < n; i++, ids++) {
        func_ovl0B_04_80048638(*ids);
    }
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

#if !VERSION_JP
static void func_ovl0B_04_80043F9C(void) {
}
#endif

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

static void func_ovl0B_04_800445BC() {
}

static void func_ovl0B_04_8004461C() {
}

static void func_ovl0B_04_80044624() {
}

/* Page 9's fade in, over the page (inlined). */

/* The name kept (and whether it changed), and the screen's texts freed
 * (inlined in 80045540). */
static void func_ovl0B_04_80045530(void) {
    s32 i;

    func_ovl0B_04_80043AD4(D_ovl0B_04_8004A448, 8);
    func_ovl0B_04_80043AD4(D_ovl0B_04_8004A468, 6);
    for (i = 0; i < 5; i++) {
        func_ovl0B_04_80047DE0(D_ovl0B_04_8004A060[i].unk0);
    }
    func_ovl0B_04_80043010(3, &D_ovl0B_04_8004A060[5], 0);
    func_ovl0B_04_80043010(2, &D_ovl0B_04_8004A060[8], 0);
}

static void func_ovl0B_04_80045538(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_ovl0B_04_80048A20[i] != D_ovl0B_04_8004A290[i][0]) {
            D_ovl0B_04_8004A18C = 1;
        }
        D_ovl0B_04_80048A20[i] = D_ovl0B_04_8004A290[i][0];
    }
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

static void func_ovl0B_04_80046A98(void) {
}

static void func_ovl0B_04_80046F18(void) {
}

static void func_ovl0B_04_80047164(void) {
}

/* The objects of a run of entries, and their removal (inlined). */
/* n first: its home is at the top of the inlined copy's slots, as in the
 * original's 80043110 (with (e, n, d) it sits 4 bytes higher). */
static void func_ovl0B_04_MakeEntries(s32 n, Entry *e, Desc *d) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0B_04_80043050(&e[i], d);
    }
}

/* fake: (n, e, x) with x unused (frame-tuned): 80043110's FreeEntries n
 * homes at the original's 80 and 64 (p4: no pad local; 16-byte areas). */
static void func_ovl0B_04_80043010(s32 n, Entry *e, s32 x) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0B_04_80047DE0(e[i].unk0);
    }
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
    s32 pad[3]; /* frame-tuned (with FreeEntries' (n, e, x), p4) */

    func_ovl0B_04_80046734(arg0, arg1);
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
        func_ovl0B_04_80043010(1, &D_ovl0B_04_8004A060[10], 0);
        func_ovl0B_04_80043010(1, &D_ovl0B_04_8004A060[11], 0);
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
    s32 pad[3]; /* frame-tuned (with FreeEntries' (n, e, x), p4) */

    func_ovl0B_04_80046734(arg0, arg1);
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
        func_ovl0B_04_80043010(1, &D_ovl0B_04_8004A060[10], 0);
        func_ovl0B_04_80043010(1, &D_ovl0B_04_8004A060[11], 0);
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
    s32 pad[3]; /* frame-tuned (with FreeEntries' (n, e, x), p4) */

    func_ovl0B_04_80046734(arg0, arg1);
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
        func_ovl0B_04_80043010(1, &D_ovl0B_04_8004A060[10], 0);
        func_ovl0B_04_80043010(1, &D_ovl0B_04_8004A060[11], 0);
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
    s32 pad[3]; /* frame-tuned (with FreeEntries' (n, e, x), p4) */

    func_ovl0B_04_80046734(arg0, arg1);
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
        func_ovl0B_04_80043010(1, &D_ovl0B_04_8004A060[10], 0);
        func_ovl0B_04_80043010(1, &D_ovl0B_04_8004A060[11], 0);
    }
    return ret;
}

void func_ovl0B_04_80046AA0(Obj *arg0) {
    if (0) {
        func_ovl0B_04_80046A98();
    }
    func_ovl0B_04_800468F0(0);
    if (0) {
        func_ovl0B_04_800468E8();
        func_ovl0B_04_800468E0();
        func_ovl0B_04_80046734(0, 0);
        func_ovl0B_04_80046600(0, 0);
        func_ovl0B_04_80046294(0);
        func_ovl0B_04_8004628C();
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
    for (i = 1; i < 3; i++) {
        D_ovl0B_04_8004A480[i + 10] = 1;
    }
    for (i = 1; i < 11; i++) {
        if (!o) {}
#if !VERSION_JP
        if (!o) {}
#else
        if (!o) {}
        if (!base) {}
#endif
        if (func_ovl0B_04_800484B0(base + i) == 0) {
            D_ovl0B_04_8004A480[i] = 0;
        } else {
            D_ovl0B_04_8004A480[i] = 1;
        }
    }
    func_ovl0B_04_MakeEntries(1, &D_ovl0B_04_8004A060[10], &D_ovl0B_04_80049C38[8]);
    func_ovl0B_04_MakeEntries(1, &D_ovl0B_04_8004A060[11], &D_ovl0B_04_80049C38[9]);
    D_ovl0B_04_8004A1A8 = 0;
    D_ovl0B_04_8004A1A4 = 0;
    D_ovl0B_04_8004A174 = D_ovl0B_04_8004A16C;
    func_ovl0B_04_80046294(D_ovl0B_04_8004A16C);
    func_ovl0B_04_80046600(D_ovl0B_04_8004A16C, 0);
#if !VERSION_JP
    o = func_ovl0B_04_80048608();
    o->unk36 = 0;
    o->unkC |= 0x80;
#endif
}

/* Pages 5-8's cursor. */
#if VERSION_JP
static void func_ovl0B_04_80046734(u8 item, u16 buttons) {
    if ((buttons & 0x20) || (buttons & 0x40)) {
        if (D_ovl0B_04_8004A480[D_ovl0B_04_8004A174]) {
            func_ovl0B_04_800438FC(D_ovl0B_04_8004A404->unk4[HALF_IDX(D_ovl0B_04_8004A174, D_ovl0B_04_8004A1A4)], 0,
                                   &D_ovl0B_04_8004A404->unk8[HALF_IDX(D_ovl0B_04_8004A174, D_ovl0B_04_8004A1A4)]);
        }
        if (D_ovl0B_04_8004A480[item]) {
            func_ovl0B_04_800438FC(D_ovl0B_04_8004A404->unk4[HALF_IDX(item, D_ovl0B_04_8004A1A8)], 1,
                                   &D_ovl0B_04_8004A404->unk8[HALF_IDX(item, D_ovl0B_04_8004A1A8)]);
        }
        D_ovl0B_04_8004A174 = item;
    } else if ((buttons & 0x80) || (buttons & 0x100)) {
        func_ovl0B_04_80046600(item, buttons);
        D_ovl0B_04_8004A174 = item;
    }
}
#else
static void func_ovl0B_04_80046734(u8 item, u16 buttons) {
    if ((buttons & 0x20) || (buttons & 0x40)) {
        func_ovl0B_04_800438FC(D_ovl0B_04_8004A404->unk4[HALF_IDX(D_ovl0B_04_8004A174, D_ovl0B_04_8004A1A4)], 0,
                               &D_ovl0B_04_8004A404->unk8[HALF_IDX(D_ovl0B_04_8004A174, D_ovl0B_04_8004A1A4)]);
        func_ovl0B_04_800438FC(D_ovl0B_04_8004A404->unk4[HALF_IDX(item, D_ovl0B_04_8004A1A8)], 1,
                               &D_ovl0B_04_8004A404->unk8[HALF_IDX(item, D_ovl0B_04_8004A1A8)]);
        D_ovl0B_04_8004A174 = item;
    } else if ((buttons & 0x80) || (buttons & 0x100)) {
        func_ovl0B_04_80046600(item, buttons);
        D_ovl0B_04_8004A174 = item;
    }
}
#endif

/* Pages 5-8: the other half of the choices, and its arrows. */
static void func_ovl0B_04_80046600(u8 item, u16 buttons) {
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
#if VERSION_JP
static void func_ovl0B_04_80046294(u8 item) {
    s32 i;
    s32 j;
    s32 n;
    s32 k;
    s32 m;

    D_ovl0B_04_80048B98[3] = D_ovl0B_04_8004A1A8 + 0x11;
    func_ovl0B_04_80048690(D_ovl0B_04_8004A404->unk4[8], D_ovl0B_04_80048B98, 5);
    i = D_ovl0B_04_8004A1A8 * 5;
    n = i + 5;
    for (j = 1; i < n; i++, j++) {
        k = D_ovl0B_04_8004A404->unk4[j];
        if (D_ovl0B_04_8004A480[i + 1] == 0) {
            func_ovl0B_04_80048690(k, D_ovl0B_04_80048B88, 1);
            D_ovl0B_04_8004A404->unk8[j].unk0 = D_ovl0B_04_80048B88;
        } else {
            func_ovl0B_04_80048690(k, D_ovl0B_04_800494C0[D_ovl0B_04_8004A168 - 5][i], 1);
            D_ovl0B_04_8004A404->unk8[j].unk0 = D_ovl0B_04_800494C0[D_ovl0B_04_8004A168 - 5][i];
        }
    }
    m = D_ovl0B_04_8004A480[item] ? 3 : 4;
    func_ovl0B_04_800438FC(D_ovl0B_04_8004A404->unk4[PAGE_IDX(item)], m,
                           &D_ovl0B_04_8004A404->unk8[PAGE_IDX(item)]);
}
#else
static void func_ovl0B_04_80046294(u8 item) {
    s32 i;
    s32 j;
    s32 n;
    s32 k;

    D_ovl0B_04_80048B98[5] = D_ovl0B_04_8004A1A8 + 0x11;
    func_ovl0B_04_80048690(D_ovl0B_04_8004A404->unk4[8], D_ovl0B_04_80048B98, 5);
    i = D_ovl0B_04_8004A1A8 * 5;
    n = i + 5;
    for (j = 1, k = 0; i < n; i++, j++, k++) {
        if (D_ovl0B_04_8004A480[i + 1] == 0) {
            D_ovl0B_04_8004A40C[k] = DRAW_ITEM(D_ovl0B_04_80048B88, &D_ovl0B_04_8004A404->unk8[j]);
            D_ovl0B_04_8004A404->unk8[j].unk0 = D_ovl0B_04_80048B88;
        } else {
            D_ovl0B_04_8004A40C[k] = DRAW_ITEM(D_ovl0B_04_800494C0[D_ovl0B_04_8004A168 - 5][i], &D_ovl0B_04_8004A404->unk8[j]);
            D_ovl0B_04_8004A404->unk8[j].unk0 = D_ovl0B_04_800494C0[D_ovl0B_04_8004A168 - 5][i];
        }
    }
    for (j = 1, k = 0, i = D_ovl0B_04_8004A1A8 * 5, n = i + 5; i < n; i++, j++, k++) {
        func_ovl0B_04_80048638(D_ovl0B_04_8004A404->unk4[j]);
        D_ovl0B_04_8004A404->unk4[j] = D_ovl0B_04_8004A40C[k];
    }
    func_ovl0B_04_800438FC(D_ovl0B_04_8004A404->unk4[PAGE_IDX(item)], 3,
                           &D_ovl0B_04_8004A404->unk8[PAGE_IDX(item)]);
}
#endif

/* Pages 1-4: the character sets; the R button goes to the next. */
u8 func_ovl0B_04_80046180(u8 arg0, u16 arg1) {
    u8 ret = 1;

    if (arg1 & 0x10) {
#if VERSION_JP
        D_ovl0B_04_8004A490.unk2 = 1;
        func_ovl0B_04_800487D0(0);
        func_ovl0B_04_80043FA4(&ret, 1, arg0, 0);
#else
        D_ovl0B_04_8004A490.unk2 = 3;
        func_ovl0B_04_800487D0(0);
        func_ovl0B_04_80043FA4(&ret, 3, arg0, 0);
#endif
    } else {
        func_ovl0B_04_80045540(arg0, arg1, &ret);
    }
    if (ret == 0) {
        func_ovl0B_04_800458F4(D_ovl0B_04_8004A2E8[0], D_ovl0B_04_8004A2E8[1]);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[3]);
    }
    return ret;
}

void func_ovl0B_04_80046054(Obj *arg0) {
    func_ovl0B_04_800458F4(D_ovl0B_04_8004A2E8[0], D_ovl0B_04_8004A2E8[1]);
    func_ovl0B_04_80047DF0(arg0, 0x55);
    func_ovl0B_04_8004401C(&D_ovl0B_04_80049B20[3]);
    func_ovl0B_04_80045850();
    func_ovl0B_04_80045958(D_ovl0B_04_8004A2E8[0], D_ovl0B_04_8004A2E8[1]);
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
        func_ovl0B_04_800458F4(D_ovl0B_04_8004A2E0[0], D_ovl0B_04_8004A2E0[1]);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[2]);
    }
    return ret;
}

void func_ovl0B_04_80045E24(Obj *arg0) {
    func_ovl0B_04_800458F4(D_ovl0B_04_8004A2E0[0], D_ovl0B_04_8004A2E0[1]);
    func_ovl0B_04_80047DF0(arg0, 0x55);
    func_ovl0B_04_8004401C(&D_ovl0B_04_80049B20[2]);
    func_ovl0B_04_80045850();
    func_ovl0B_04_80045958(D_ovl0B_04_8004A2E0[0], D_ovl0B_04_8004A2E0[1]);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[3], D_ovl0B_04_80048A80, 5, 0.7f);
#if VERSION_JP
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[2], D_ovl0B_04_80048A7C, 6, 0.5f);
#else
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[4], D_ovl0B_04_80048A84, 6, 0.5f);
#endif
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
        func_ovl0B_04_800458F4(D_ovl0B_04_8004A2D8[0], D_ovl0B_04_8004A2D8[1]);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[1]);
    }
    return ret;
}

void func_ovl0B_04_80045BF4(Obj *arg0) {
    func_ovl0B_04_800458F4(D_ovl0B_04_8004A2D8[0], D_ovl0B_04_8004A2D8[1]);
    func_ovl0B_04_80047DF0(arg0, 0x55);
    func_ovl0B_04_8004401C(&D_ovl0B_04_80049B20[1]);
    func_ovl0B_04_80045850();
    func_ovl0B_04_80045958(D_ovl0B_04_8004A2D8[0], D_ovl0B_04_8004A2D8[1]);
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
        func_ovl0B_04_800458F4(D_ovl0B_04_8004A2D0[0], D_ovl0B_04_8004A2D0[1]);
        func_ovl0B_04_800440C8(&D_ovl0B_04_80049B20[0]);
    }
    return ret;
}

void func_ovl0B_04_800459C4(Obj *arg0) {
    func_ovl0B_04_800458F4(D_ovl0B_04_8004A2D0[0], D_ovl0B_04_8004A2D0[1]);
    func_ovl0B_04_80047DF0(arg0, 0x55);
    func_ovl0B_04_8004401C(&D_ovl0B_04_80049B20[0]);
    func_ovl0B_04_80045850();
    func_ovl0B_04_80045958(D_ovl0B_04_8004A2D0[0], D_ovl0B_04_8004A2D0[1]);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[1], D_ovl0B_04_80048A78, 5, 0.7f);
    func_ovl0B_04_SetText(D_ovl0B_04_8004A468[4], D_ovl0B_04_80048A84, 6, 0.5f);
    if (0) {
        func_ovl0B_04_80045958(0, 0);
        func_ovl0B_04_800458F4(0, 0);
        func_ovl0B_04_80045850();
        func_ovl0B_04_80045848();
        func_ovl0B_04_80045540(0, 0, 0);
    }
}

/* A page's two texts and the menu's cursor shown, and hidden. */
static void func_ovl0B_04_80045958(s32 id0, s32 id1) {
    Obj *a = func_ovl0B_04_80048668(id0);
    Obj *b = func_ovl0B_04_80048668(id1);
    Obj *c = func_ovl0B_04_80048608();

    a->unkC &= ~1;
    b->unkC &= ~1;
    c->unkC &= ~1;
}

static void func_ovl0B_04_800458F4(s32 id0, s32 id1) {
    Obj *a = func_ovl0B_04_80048668(id0);
    Obj *b = func_ovl0B_04_80048668(id1);
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
    u8 c;
    u8 x;

    /* fake: (p2) the dead read gives the base its s0; c's read is on the
     * if's line (.loc). The decrement is unsigned arithmetic masked to a
     * byte (p5): ugen's `and 255` before the sb, which as1 drops, uses up
     * the temporary the original's t-registers are one ahead by, and it
     * keeps unk0's own (u8) value, so c stays in $a0. */
    if (buttons & 2) { c = D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0][0];
        D_ovl0B_04_8004A490.unk1 = 0;
        D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0][0] = 0;
        if ((D_ovl0B_04_8004A490.unk0 == 7 && c == 0) || (D_ovl0B_04_8004A490.unk0 != 7 && D_ovl0B_04_8004A490.unk0 > 0)) {
            if (D_ovl0B_04_8004A490.unk1) {}
            D_ovl0B_04_8004A490.unk0 = ((u32) D_ovl0B_04_8004A490.unk0 - 1) & 0xFF;
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
                func_ovl0B_04_80045538();
                func_ovl0B_04_80045530();
            } else {
                x = item;
                D_ovl0B_04_8004A490.unk1 = func_ovl0B_04_8004426C(D_ovl0B_04_8004A490.unk2, item);
                D_ovl0B_04_8004A490.unk3 = x;
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

/* Page 9's set-up: the name over a fade (written out: the stub before it,
 * 800450B8, is 80045214's save). Defined above 80045214, which pulls it
 * out right after that stub. */
void func_ovl0B_04_800450C0(Obj *arg0) {
    Obj *o = func_ovl0B_04_80048668(D_ovl0B_04_8004A3B0[4]);
    Fade *f;
    f32 step;

    func_ovl0B_04_80044394(D_ovl0B_04_8004A3B0[4], D_ovl0B_04_8004A3B0[5]);
    func_ovl0B_04_8004447C(D_ovl0B_04_8004A3B0[4], 0x50);
    func_ovl0B_04_8004447C(D_ovl0B_04_8004A3B0[5], 0x32);
    o->unkC |= 0x400;
    f = &D_ovl0B_04_80049B20[4];
    if (!D_ovl0B_04_8004A3E4) {}
    step = (f->unk18 - f->unk14) / f->unk1C;
    D_ovl0B_04_8004A3E4 = f;
    f->unk0 = func_ovl0B_04_80047E58(func_ovl0B_04_80043CD0, 0);
    f->unk0->unkC |= 0x80;
    for (f->unk34 = f->unk14; f->unk34 < f->unk18; f->unk34 += step) {
        func_ovl0B_04_80048290();
    }
    func_ovl0B_04_80048290();
}

/* Page 9's save (inlined in 80045214; its stub is 800450B8): its result
 * is the inlined return value, so the test reads it from $v0 after a load
 * through a ugen temporary (`lw t8; move v0,t8`, merged by as1). */
static s32 func_ovl0B_04_800450B8(void) {
    s32 i;
    s32 ok;
    u8 *save;
    s32 id;
    s32 id2;

    ok = 1;
    save = D_ovl0B_04_8004A188;
    func_ovl0B_04_8004447C(D_ovl0B_04_8004A3B0[4], 0);
    func_ovl0B_04_8004447C(D_ovl0B_04_8004A3B0[5], 0);
#if VERSION_JP
    id = func_ovl0B_04_80048688(D_ovl0B_04_80048A54, 55, 175, 0.8f, 0.8f, 2);
#else
    id = func_ovl0B_04_80048688(D_ovl0B_04_80048A54, 100, 175, 0.8f, 0.8f, 2);
#endif
    func_ovl0B_04_80048268(3);
    for (i = 0; i < 8; i++) {
        save[i] = D_ovl0B_04_80048A20[i];
    }
    save[8] = 0;
    if (func_ovl0B_04_80048910() != 0) {
        func_ovl0B_04_800487D0(0x18);
        func_ovl0B_04_8004447C(id, 0);
#if VERSION_JP
        id2 = func_ovl0B_04_80048688(D_ovl0B_04_80048A60, 50, 175, 0.8f, 0.8f, 0);
#else
        id2 = func_ovl0B_04_80048688(D_ovl0B_04_80048A60, 80, 175, 0.8f, 0.8f, 0);
#endif
        func_ovl0B_04_80048268(120);
        func_ovl0B_04_80048638(id2);
        ok = 0;
    }
    func_ovl0B_04_80048638(id);
    return ok;
}

/* Page 9: save the changes or not. */
u8 func_ovl0B_04_80045214(u8 arg0, u16 arg1) {
    u8 ret = 1;

    /* fake: a dead call pulls 800450C0 (defined above) out after 800450B8's
     * stub, where the original has it */
    if (0) {
        func_ovl0B_04_800450C0(0);
    }
    if ((arg1 & 0x80) || (arg1 & 0x100)) {
        func_ovl0B_04_800438FC(D_ovl0B_04_8004A3B0[D_ovl0B_04_8004A174], 0,
                               &D_ovl0B_04_80049930[D_ovl0B_04_8004A174]);
        func_ovl0B_04_800438FC(D_ovl0B_04_8004A3B0[arg0], 1, &D_ovl0B_04_80049930[arg0]);
        D_ovl0B_04_8004A174 = arg0;
    }
    if (arg1 & 1) {
        if (arg0 == 1) {
            if (func_ovl0B_04_800450B8()) {
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

/* The name copied into the one being entered (inlined). */
static void func_ovl0B_04_80044BE0(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_ovl0B_04_8004A290[i][0] = D_ovl0B_04_80048A20[i];
        D_ovl0B_04_8004A290[i][1] = 0;
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
#if VERSION_JP
    s32 pad[1]; /* frame-tuned (p2) */
#else
    s32 pad[3]; /* frame-tuned (p2) */
#endif

    if ((arg1 & 0x20) || (arg1 & 0x40)) {
        func_ovl0B_04_800438FC(D_ovl0B_04_8004A2A8[D_ovl0B_04_8004A174], 0,
                               &D_ovl0B_04_8004922C[D_ovl0B_04_8004A174]);
        func_ovl0B_04_800438FC(D_ovl0B_04_8004A2A8[arg0], 1, &D_ovl0B_04_8004922C[arg0]);
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
        /* fake: a read of the call's result (dead; in us case 1's 80048668 results
         * do it): $v0 is then the return value's in the changed test above, which
         * takes $v1 as in the original (jp; no change in us/eu) */
        i = func_ovl0B_04_800487D0(1);
        switch (arg0) {
            case 1:
                func_ovl0B_04_80044BE0();
#if VERSION_JP
                func_ovl0B_04_80043A24(8, D_ovl0B_04_8004A448, D_ovl0B_04_80049308);
                func_ovl0B_04_80043A24(6, D_ovl0B_04_8004A468, D_ovl0B_04_800493A8);
#else
                func_ovl0B_04_80043A7C(8, D_ovl0B_04_8004A448, D_ovl0B_04_80049308);
                func_ovl0B_04_80043A24(1, D_ovl0B_04_8004A468, D_ovl0B_04_800493A8);
                func_ovl0B_04_80043A7C(5, &D_ovl0B_04_8004A468[1], D_ovl0B_04_800493BC);
                a = func_ovl0B_04_80048668(D_ovl0B_04_8004A468[1]);
                b = func_ovl0B_04_80048668(D_ovl0B_04_8004A468[2]);
                a->unk36 = 0;
                a->unkC |= 0x80;
                b->unk36 = 0;
                b->unkC |= 0x80;
#endif
                func_ovl0B_04_80044154();
                func_ovl0B_04_800441C4();
                for (i = 0; i < 5; i++) {
                    func_ovl0B_04_80043050(&D_ovl0B_04_8004A060[i], &D_ovl0B_04_80049C38[2 + i]);
                }
#if !VERSION_JP
                D_ovl0B_04_8004A060[0].unk0->unkC |= 0x80;
                D_ovl0B_04_8004A060[0].unk0->unk36 = 0;
#endif
                func_ovl0B_04_MakeEntries(3, &D_ovl0B_04_8004A060[5], &D_ovl0B_04_80049C38[10]);
                func_ovl0B_04_MakeEntries(2, &D_ovl0B_04_8004A060[8], &D_ovl0B_04_80049C38[10]);
#if !VERSION_JP
                D_ovl0B_04_8004A060[5].unk0->unkC |= 0x80;
                D_ovl0B_04_8004A060[5].unk0->unk36 = 0;
                D_ovl0B_04_8004A060[6].unk0->unkC |= 0x80;
                D_ovl0B_04_8004A060[6].unk0->unk36 = 0;
#endif
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
        func_ovl0B_04_800447DC(0, 0);
        func_ovl0B_04_800445C4();
        func_ovl0B_04_8004456C();
    }
    return ret;
}

/* The character before the cursor: the marks it can take (the 0x1E00
 * buttons put them on in turn), shown in D_ovl0B_04_80048A70. */
static s32 func_ovl0B_04_80044714(u8 set, u8 c) {
    s32 r = 0;

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
    static s32 D_ovl0B_04_8004A1A0 = 0; /* function-scope: its .data place to check */
    u8 set;
    u8 idx;
    u8 c;
    s32 n;
    u8 d1;
    u8 d2;
    u8 d3;
    s32 t;

    if (D_ovl0B_04_8004A490.unk0 == 0) {
        c = 0;
    } else if (D_ovl0B_04_8004A490.unk0 == 7 && D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0][0] != 0) {
        c = D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0][0];
    } else {
        c = D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0 - 1][0];
    }
    set = D_ovl0B_04_8004905C[c];
    idx = D_ovl0B_04_80048F5C[c];
    if (set == 1 || set == 2) {
        n = 0;
        c = func_ovl0B_04_8004426C(set, idx);
        d1 = func_ovl0B_04_8004471C(set, c);
        if (d1) {
            n = 1;
        }
        d2 = func_ovl0B_04_80044714(set, c);
        if (d2 != 0) {
            n++;
        }
        d3 = func_ovl0B_04_8004462C(set, c);
        if (d3 != 0) {
            n++;
        }
        if (n != 0) {
            D_ovl0B_04_80048A70[0] = c;
            if (d1 != 0) {
                D_ovl0B_04_80048A70[2] = c + d1;
            } else if (d2 != 0) {
                D_ovl0B_04_80048A70[2] = c + d2;
            } else if (d3 != 0) {
                D_ovl0B_04_80048A70[2] = c + d3;
            }
            D_ovl0B_04_8004A060[8].unk0->unk18 = D_ovl0B_04_8004A060[8].unkC;
            D_ovl0B_04_8004A060[8].unk0->unk1C = D_ovl0B_04_8004A060[8].unk10;
            if (n >= 2) {
                D_ovl0B_04_8004A060[9].unk0->unk18 = D_ovl0B_04_8004A060[9].unkC;
                D_ovl0B_04_8004A060[9].unk0->unk1C = D_ovl0B_04_8004A060[9].unk10;
                if (d2 != 0) {
                    D_ovl0B_04_80048A70[4] = c + d2;
                } else if (d3 != 0) {
                    D_ovl0B_04_80048A70[4] = c + d3;
                } else if (d1 != 0) {
                    D_ovl0B_04_80048A70[4] = c + d1;
                }
            } else {
                D_ovl0B_04_8004A060[9].unk0->unk18 = D_ovl0B_04_8004A060[9].unk4;
                D_ovl0B_04_8004A060[9].unk0->unk1C = D_ovl0B_04_8004A060[9].unk8;
                D_ovl0B_04_80048A70[4] = 0xF;
            }
            if (buttons & 0x1E00) {
                func_ovl0B_04_800487D0(0);
                D_ovl0B_04_8004A1A0++;
                if (n < D_ovl0B_04_8004A1A0) {
                    D_ovl0B_04_8004A1A0 = 0;
                } else if (D_ovl0B_04_8004A1A0 == 1) {
                    if (d1 != 0) {
                        c += d1;
                    } else if (d2 != 0) {
                        c += d2;
                    } else if (d3 != 0) {
                        c += d3;
                    } else {
                        D_ovl0B_04_8004A1A0 = 0;
                    }
                } else if (d2 != 0) {
                    c += d2;
                } else if (d3 != 0) {
                    c += d3;
                } else if (d1 != 0) {
                    c += d1;
                } else {
                    D_ovl0B_04_8004A1A0 = 0;
                }
                if (c != D_ovl0B_04_8004A490.unk1) {
                    (&D_ovl0B_04_8004A480)[1][1] = c; /* fake: through the neighbour, for its own lui */
                    t = 0;
                    if ((D_ovl0B_04_8004A490.unk0 == 7 && D_ovl0B_04_8004A290[7][0] == 0) || D_ovl0B_04_8004A490.unk0 != 7) {
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

static s8 func_ovl0B_04_8004471C(u8 set, u8 c) {
    s8 r = 0;

    switch (set) {
        default:
            r = 0;
            break;
        case 1:
            if (c >= 0xB5 && c < 0xC4) {
                r = 0x27;
            } else if (c >= 0xC9 && c < 0xCE) {
                r = 0x22;
            }
            break;
        case 2:
            if (c >= 0x65 && c < 0x74) {
                r = 0x27;
            } else if (c >= 0x79 && c < 0x7E) {
                r = 0x22;
            }
            break;
        case 3:
        case 4:
            break;
    }
    return r;
}

static s8 func_ovl0B_04_8004462C(u8 set, u8 c) {
    s8 r = 0;
    func_ovl0B_04_80044624();
    func_ovl0B_04_8004461C();

    switch (set) {
        default:
            r = 0;
            break;
        case 1:
            if (c >= 0xB0 && c < 0xB5) {
                r = -0xB;
            } else if (c >= 0xD3 && c < 0xD6) {
                r = -0x28;
            } else if (c == 0xC1) {
                r = -0x17;
            }
            break;
        case 2:
            if (c >= 0x60 && c < 0x65) {
                r = -0xB;
            } else if (c >= 0x83 && c < 0x86) {
                r = -0x28;
            } else if (c == 0x71) {
                r = -0x17;
            }
            break;
        case 3:
        case 4:
            break;
    }
    return r;
}

/* No marks: the mark texts back at their places. */
static void func_ovl0B_04_800445C4(void) {
    func_ovl0B_04_800445BC();
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
#if !VERSION_JP
    o = func_ovl0B_04_80048608();
    o->unk36 = 0;
    o->unkC |= 0x80;
#endif
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
#if !VERSION_JP
        func_ovl0B_04_80043F9C();
#endif
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
#line 2005
static void func_ovl0B_04_80044394(s32 a, s32 b) {
#line 1982
    s32 n;
#if VERSION_JP
    u16 x;
#else
    s32 x;
#endif
    Obj *o;
    s32 m;

#line 1991
    D_ovl0B_04_80048A20[8] = 0;
#line 1990
    n = 0;
#line 1993
    while (D_ovl0B_04_80048A20[n] != 0) {
        n++;
    }
    m = n - 1;
    if (!m) {} /* fake: dead read; m = n - 1 its own variable (the original: addiu v0,v1,-1) */
    if (m != -1) {
#if VERSION_JP
        x = 56 - m * 8;
#else
        x = -func_ovl0B_04_80048680(D_ovl0B_04_80048A20) * 0.65f / 2;
#endif
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
    u8 r;

    switch (set) {
        default:
            r = 0;
            break;
        case 1:
            r = D_ovl0B_04_8004915C[idx];
            break;
        case 2:
            r = D_ovl0B_04_80049190[idx];
            break;
        case 3:
            r = D_ovl0B_04_800491C4[idx];
            break;
        case 4:
            r = D_ovl0B_04_800491F8[idx];
            break;
    }
    return r;
}

/* The character at the cursor written. */
static void func_ovl0B_04_80044210(void) {
    D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0][0] = D_ovl0B_04_8004A490.unk1;
    func_ovl0B_04_80048640(D_ovl0B_04_8004A448[D_ovl0B_04_8004A490.unk0], D_ovl0B_04_8004A290[D_ovl0B_04_8004A490.unk0], 2);
}

/* The set and item of the character at the cursor. */
static void func_ovl0B_04_800441C4(void) {
    u8 set = D_ovl0B_04_8004905C[D_ovl0B_04_8004A490.unk1];

    if (set != 0) {
        D_ovl0B_04_8004A490.unk2 = set;
    }
#if !VERSION_JP
    if (D_ovl0B_04_8004A490.unk2 < 3) {
        D_ovl0B_04_8004A490.unk2 = 3;
    }
#endif
    D_ovl0B_04_8004A490.unk3 = D_ovl0B_04_80048F5C[D_ovl0B_04_8004A490.unk1];
}

/* The cursor at the end of the name. */
static void func_ovl0B_04_80044154(void) {
    s32 n = 0;

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

    step = (f->unk18 - f->unk14) / f->unk1C;
    D_ovl0B_04_8004A3E4 = f;
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
#if VERSION_JP
    D_ovl0B_04_8004A3EC = -1;
    D_ovl0B_04_8004A3F0 = -1;
#else
    D_ovl0B_04_8004A3F0 = -1;
    D_ovl0B_04_8004A3F4 = -1;
#endif
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
#if !VERSION_JP
    Page *p3;
    Page *p4;
#endif
    Obj *menu;
    s32 i;

#if !VERSION_JP
    p4 = &D_ovl0B_04_800499B8[4];
#endif
    D_ovl0B_04_8004A16C = 1;
    D_ovl0B_04_8004A168 = 0;
#if VERSION_JP
    while (D_ovl0B_04_8004A168 != 0xFF) {
#else
    /* fake: p3's load and the table's on one line, so as1 orders them as the original */
    if (D_ovl0B_04_8004A168 != 0xFF) { p3 = &D_ovl0B_04_800499B8[3]; if (!p3) {} do {
#endif
        p = &D_ovl0B_04_800499B8[D_ovl0B_04_8004A168];
#if VERSION_JP
        func_ovl0B_04_80043A24(p->unk0, p->unk4, p->unk8);
#else
        if (p == p3 || p == p4) {
            func_ovl0B_04_80043A7C(p->unk0, p->unk4, p->unk8);
        } else {
            func_ovl0B_04_80043A24(p->unk0, p->unk4, p->unk8);
            if (!p3) {}
        }
#endif
        menu = func_ovl0B_04_800485D0(p->unkC, p->unk10, p->unk16, p->unk18, p->unk1A);
        if (p->unk1C != 2) {
            func_ovl0B_04_800438FC(p->unk4[D_ovl0B_04_8004A16C], 1, &p->unk8[D_ovl0B_04_8004A16C]);
        }
        func_ovl0B_04_800485F8(D_ovl0B_04_8004A16C);
        D_ovl0B_04_8004A174 = D_ovl0B_04_8004A16C;
        if (p->unk20 != NULL) {
            p->unk20(menu);
        }
        func_ovl0B_04_800485F0();
        func_ovl0B_04_80043AD4(p->unk4, p->unk0);
        func_ovl0B_04_800485E8();
        func_ovl0B_04_80048268(2);
#if VERSION_JP
    }
#else
    } while (D_ovl0B_04_8004A168 != 0xFF);
    }
#endif
    func_ovl0B_04_800477F0(0x1F, 0x11, 0);
    func_ovl0B_04_80048258();
    if (0) {
#if !VERSION_JP
        func_ovl0B_04_80043A7C(0, 0, 0);
#endif
        func_ovl0B_04_80043A24(0, 0, 0);
        func_ovl0B_04_800438FC(0, 0, 0);
        func_ovl0B_04_800438F4();
    }
}

/* The fade's display list (ovl_0B_05's 80044DD8). */
void func_ovl0B_04_80043CD0(s32 arg0, Gfx0B04 **arg1) {
    Gfx0B04 *gfx = *arg1;

    { Gfx0B04 *g = gfx++; g->w0 = 0xFA000000; g->w1 = ((D_ovl0B_04_8004A3E4->unk4 & 0xFF) << 24) | ((D_ovl0B_04_8004A3E4->unk8 & 0xFF) << 16) | ((D_ovl0B_04_8004A3E4->unkC & 0xFF) << 8) | (D_ovl0B_04_8004A3E4->unk10 & 0xFF); }
    { Gfx0B04 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFDF6FB; }
    { Gfx0B04 *g = gfx++; g->w0 = 0xF7000000; g->w1 = 0x10001; }
    { Gfx0B04 *g = gfx++; g->w0 = 0xF6000000 | (((D_ovl0B_04_8004A3E4->unk2C + (s32) D_ovl0B_04_8004A3E4->unk34) & 0x3FF) << 14) | (((D_ovl0B_04_8004A3E4->unk30 + (s32) (D_ovl0B_04_8004A3E4->unk34 * D_ovl0B_04_8004A3E4->unk20)) & 0x3FF) << 2); g->w1 = (((D_ovl0B_04_8004A3E4->unk2C - (s32) D_ovl0B_04_8004A3E4->unk34) & 0x3FF) << 14) | (((D_ovl0B_04_8004A3E4->unk30 - (s32) (D_ovl0B_04_8004A3E4->unk34 * D_ovl0B_04_8004A3E4->unk20)) & 0x3FF) << 2); }
    *arg1 = gfx;
    if (0) { func_ovl0B_04_80043ADC(); }
}

#if !VERSION_JP
/* A page's texts written (0x2501 for pages 3 and 4, 0x250C otherwise). */
static void func_ovl0B_04_80043A7C(s32 n, s32 *ids, Item *items) {
    s32 i;

    for (i = 0; i < n; i++, ids++, items++) {
        *ids = func_ovl0B_04_80048630(items->unk0, items->unk4, items->unk6, items->unk8, items->unkC, items->unk10);
    }
}
#endif

static void func_ovl0B_04_80043A24(s32 n, s32 *ids, Item *items) {
    s32 i;

    for (i = 0; i < n; i++, ids++, items++) {
        *ids = func_ovl0B_04_80048688(items->unk0, items->unk4, items->unk6, items->unk8, items->unkC, items->unk10);
    }
}

/* An item lit (1), unlit (0), or set without growing (2-4). */
static void func_ovl0B_04_800438FC(s32 id, u32 mode, Item *it) {
    f32 d;
    u8 col;
    s32 grow = 1;

    switch (mode) {
        case 1:
            d = 0.15f;
            col = it->unk11;
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
            grow = 0;
            d = 0.0f;
            col = it->unk10;
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
    static s32 D_ovl0B_04_8004A1E4 = 0;
    u16 buttons;
    s32 a;
    s32 b;

    while (TRUE) {
        buttons = func_ovl0B_04_80048320(0);
        if (D_ovl0B_04_8004A164->unkC & 0x40) {
            if (++D_ovl0B_04_8004A1E4 >= 14) {
                D_ovl0B_04_8004A1E4 = 0;
            }
#line 2270
            b = a = -1; /* fake: numbered above the loop head so as1 hoists li a1 into its load delay */
#line 2290
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
            func_ovl0B_04_80047E20(D_ovl0B_04_8004A164, a, 0);
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

/* The handler's cases (inlined). */
/* fake: the dead calls in H4 only add uopt basic blocks: 80043110 needs
 * enough of them (zdbug count) for the original's registers (uopt's
 * first-use cost of a saved register is blocks/4; p4: four suffice since
 * FreeEntry). More than six here, or any in 80043110/H1, stop umerge
 * inlining H5. */
static void func_ovl0B_04_H4(void) {
    if (0) { func_ovl0B_04_80048290(); }
    if (0) { func_ovl0B_04_80048290(); }
    if (0) { func_ovl0B_04_80048290(); }
    if (0) { func_ovl0B_04_80048290(); }
    func_ovl0B_04_MakeEntries(20, D_ovl0B_04_80049D40, &D_ovl0B_04_80049C38[0]);
    func_ovl0B_04_MakeEntries(20, D_ovl0B_04_80049ED0, &D_ovl0B_04_80049C38[1]);
    func_ovl0B_04_80043050(&D_ovl0B_04_8004A060[12], &D_ovl0B_04_80049C38[7]);
    D_ovl0B_04_8004A060[12].unk0->unk36 = 90;
}

/* fake: K&R (frame-tuned): i's home at the original's 132 (a (void)
 * static's area puts 8 bytes before i). */
static void func_ovl0B_04_H5a() {
    s32 i;

    D_ovl0B_04_8004A164 = func_ovl0B_04_80047DD8(0x49, 0);
    D_ovl0B_04_8004A164->unk10 = -110.0f;
    D_ovl0B_04_8004A164->unk14 = -70.0f;
    D_ovl0B_04_8004A164->unk18 = 0.0f;
    D_ovl0B_04_8004A164->unk20 = 0.0f;
    func_ovl0B_04_80047E00(D_ovl0B_04_8004A164, 12);
    for (i = 0; i < 12; i++) {
        func_ovl0B_04_80047E08(D_ovl0B_04_8004A164, 0x4A, i, i);
    }
    func_ovl0B_04_80047E28(D_ovl0B_04_8004A164, -1);
    D_ovl0B_04_8004A164->unkC |= 0x20;
    /* fake: the store numbered below the line after it, for its place in the jal's delay slot */
#line 2395
    D_ovl0B_04_8004A170 = func_ovl0B_04_80047E68(D_ovl0B_04_8004A164, 0xF);
}
#line 2377

/* The tests reread each slot through its pointer, as the original does;
 * the first test's value is its own variable (a: $a3, the later ones x:
 * $v1), and A178's pointer is loaded once for the copy and the first test
 * ($v1).
 * fake: the calls pass `(x += 1, x - 1)` for the original's `addiu a2,v1,0`
 * copy, and the first one (&D_ovl0B_04_8004A16C)[1] for A170 (the plain
 * name makes &A170 the $s0 base). */
static void func_ovl0B_04_H5b(void) {
    s32 a;
    s32 x;

    if (x) {} /* fake: x live from the start: its later tests then avoid $v0 */
    D_ovl0B_04_8004A178 = func_ovl0B_04_800484E0(8);
    D_ovl0B_04_8004A17C = func_ovl0B_04_800484E0(9);
    D_ovl0B_04_8004A180 = func_ovl0B_04_800484E0(10);
    D_ovl0B_04_8004A184 = func_ovl0B_04_800484E0(11);
    D_ovl0B_04_8004A188 = func_ovl0B_04_800484E0(12);
    D_ovl0B_04_8004A190 = *D_ovl0B_04_8004A178;
    /* fake: a volatile read of the slot pointer, so uopt's PRE doesn't carry it to
     * the second test (the original reloads it through $s0 there) */
    D_ovl0B_04_8004A194 = **(s32 * volatile *) &D_ovl0B_04_8004A17C;
    D_ovl0B_04_8004A198 = *D_ovl0B_04_8004A180;
    D_ovl0B_04_8004A19C = *D_ovl0B_04_8004A184;
    a = *D_ovl0B_04_8004A178;
    if (a != 0) {
        func_ovl0B_04_800478A0((&D_ovl0B_04_8004A16C)[1], 0, (a += 1, a - 1));
    }
    x = *D_ovl0B_04_8004A17C;
    if (x != 0) {
        func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 1, (x += 1, x - 1));
    }
    x = *D_ovl0B_04_8004A180;
    if (x != 0) {
        func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 2, (x += 1, x - 1));
    }
    x = *D_ovl0B_04_8004A184;
    if (x != 0) {
        func_ovl0B_04_800478A0(D_ovl0B_04_8004A170, 3, (x += 1, x - 1));
    }
}

static void func_ovl0B_04_H5c(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_ovl0B_04_80048A20[i] = D_ovl0B_04_8004A188[i];
        D_ovl0B_04_8004A498[i] = D_ovl0B_04_8004A188[i];
    }
    D_ovl0B_04_80048A20[8] = 0;
    D_ovl0B_04_8004A188[8] = 0;
}

static void func_ovl0B_04_H5d(void) {
    func_ovl0B_04_80048248(func_ovl0B_04_80043ADC, NULL, 0, 0, 0x130);
    D_ovl0B_04_8004A4A0 = func_ovl0B_04_80048248(func_ovl0B_04_800436C8, NULL, 0, 0, 0x130);
}

static void func_ovl0B_04_H5(void) {
    func_ovl0B_04_800487E0(0x1D);
    D_ovl0B_04_8004A18C = 0;
    func_ovl0B_04_800485A0(1);
    func_ovl0B_04_800485A8(0x46);
    func_ovl0B_04_H5a();
    func_ovl0B_04_H5b();
    func_ovl0B_04_H5c();
    func_ovl0B_04_H5d();
}

/* One entry's object freed (inlined). */
static void func_ovl0B_04_FreeEntry(Entry *e, s32 i) {
    func_ovl0B_04_80047DE0(e[i].unk0);
}

static void func_ovl0B_04_H1(void) {
    func_ovl0B_04_800485A0(0);
    func_ovl0B_04_80048250(D_ovl0B_04_8004A4A0);
    func_ovl0B_04_80047E78(D_ovl0B_04_8004A170);
    func_ovl0B_04_80047DE0(D_ovl0B_04_8004A164);
    func_ovl0B_04_80043010(20, D_ovl0B_04_80049D40, 0);
    func_ovl0B_04_80043010(20, D_ovl0B_04_80049ED0, 0);
    func_ovl0B_04_FreeEntry(D_ovl0B_04_8004A060, 12);
}

/* The handler the entry returns. */
void func_ovl0B_04_80043110(s32 arg0) {
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
            func_ovl0B_04_H4();
            break;
        case 5:
            func_ovl0B_04_H5();
            break;
        case 12:
            func_ovl0B_04_800487E8();
            break;
        case 1:
            func_ovl0B_04_H1();
            break;
        case 16:
            break;
    }
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

