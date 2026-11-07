/*
 * NON_MATCHING: ovl_14_01's game object, complete; not in the ROM.
 * flags: -O3
 * differing words: us 13, eu 13, jp 13
 *
 * The text is the same in every version (only jp's ZeroJump numbers
 * differ). 87 of 89 functions match. m2c output (with the ZeroJump
 * prototypes of the other drafts, scratch/newovl2/protos.h, and the
 * file's own in own.h) made to compile, then tuned by hand
 * (scratch/newovl2/r/).
 *
 * Order: every function and stub comes out at the original's place
 * (8004B908 and 8004B820 defined below 8004B500, 800431C4 and 80043250
 * above 800432D8, which pulls them with the static 800431F8). Statics:
 * 800431F8 (takes the object in $s0), the stubs 80043680, 8004B38C/94,
 * 8004B680/88/90 (K&R empty statics inlined in the next function) and the
 * nine unused ones 8004BB04-8004BB44. 80045008 is not a stub: it is
 * 80044FDC's own `jr ra` (a branch target). 8004697C calls 80045124,
 * which IDO inlines (non-static, same file).
 *
 * Data: .data (the two Vec3f[5] paths at 8004D190/8004D1CC; the word at
 * 8004D208 is a function-scope static of 8004739C, the only user, which
 * comes out at .data+0x78 and stops uopt keeping its address in a
 * register) and .bss defined; the four command strings are literals.
 * The bss types are partly guesses (Vec3f groups, the 3-link chains
 * D_8004D560/5A0); fillers keep the addresses. 8004D62C-8004D640 are six
 * separate f32s (the original stores each with its own lui).
 *
 * Pass 4 (scratch/newovl2/r3/): plain C from the asm for the big
 * functions. Same-file non-static functions IDO inlines: m2c's
 * D_8004D544/548 test is 80044FDC(), m2c's C9E8(8004A4E0, x, 0, 0, 0x150)
 * is 80045124(x), and 800477EC is calls to 80047730, 800476F8, 80047798,
 * 8004739C and 8004769C (all inlined but 80047730/8004739C). The Link
 * triples are written link by link through `arg1++` (unk0, then unk10
 * down to unk4 where that is the original's store order); 80046648 walks
 * arg1 and keeps a copy for the D_8004D560 test.
 *
 * Pass 5 (scratch/newovl2/r4/): 8004A914 matches with two chained
 * stores, `D_8004D4EC = D_8004D4F0 = -1` and `D_8004D6CC = D_8004D6C8 =
 * 0`: the inner global is stored first through a coloured address (v1,
 * t0), and the D_8004D6F0 index after it is the stored 0 in $zero.
 *
 * Pass 6 (scratch/newovl2/r5/): 800438D8 matches with 8004C8B0
 * declared s32 (the original keeps &D_8004D53C in v1, as if v0 held a
 * result; no other function changes). 80043CC0 has no local: the
 * quotient is written out three times, and uopt's CSE temporary is spilled
 * at the top of the frame (sp+1C) where a named `t` pushed it below its
 * own home. 80049368's wrap is two statements, `y = WRAP360(y - 90)` and
 * `y -= 5`, which gives the original's registers (y in f2, 90 in f12).
 *
 * Pass 7 (scratch/newovl2/r6/): 800488B0 calls 800476F8(home.x, home.z,
 * 30) and 8004769C(60), which IDO inlines (same file): their Vec3fs are
 * the original's sp 2C/1C, below uopt's temps; `low` is built from `home`
 * (home stored first). 80049814 stores D_8004D4DC at the end as
 * `((Vec3f **) &D_8004D4E0)[-1]` (same address; uopt then doesn't keep
 * &D_8004D4DC in a register), and `if (v) {}` sits in the else arm only.
 * That also fixes 8004A11C's alignment.
 *
 * Pass 8 (scratch/newovl2/r7/): 80049814's arms both store `v` and the
 * dead read `if (v) {}` sits after the join, so each arm's address is a
 * coloured two-use range (no t-register used up in the if arm); `l += 1`
 * then gives the original's t7 for the volatile load. 8004A760 has no `t`:
 * `x + 0.1f` is written out at each use (uopt's CSE keeps it in f0 and
 * 0.0 gets f2).
 *
 * Pass 9 (scratch/newovl2/r8/): uopt's live ranges and interference
 * are per basic block, and an empty `do {} while (0);` starts a new uopt
 * block without emitting code (TRICK). 80048ABC has one after the first
 * link (the 2 stored to unk0 no longer shares a block with the
 * D_8004D5F4 load, so both take v0); 80043010 has one after `arg0++`
 * (arg1 stays in a1, not forbidden by the call's a1, with the dead `addiu
 * a1,a1,40`), and its first two links store unk10, unkC, unk8, unk4 as
 * the third does. 800437B8 alternates `#line N "x.c"` / `#line N "y.c"`
 * before the 80043250 call, the D_8004D5DC load, the store and the 0x414
 * call (TRICK): as1 ends a scheduling block where the source switches back
 * to a file it has seen (a first switch to a new name does nothing), which
 * gives the original's two block boundaries; the rest of the file is then
 * "y.c" to the compiler (debug info only). That also fixes 80043B20's
 * alignment. 800432D8 writes `(-((f32) i / 120.0f) + 1.0f) * 100.0f`
 * (the same value as `100 * (1 - i / 120)` in IEEE arithmetic): 120.0 is
 * then the first constant seen and 1.0 gets f22 as in the original.
 *
 * Pass 10 (scratch/wrongfix/): fcmp's relocation check found
 * 8004515C's chain storing D_8004D548 and D_8004D550 the wrong way round:
 * the innermost global is stored first, so the chain is `D554 = D548 =
 * D54C = D550 = 0`. 8004654C and 800467C0 match (TRICK): the original
 * stores D_8004D6A0.y with its own lui (%lo(D_8004D6A4)) because uopt's
 * copy propagation folds an ISTR to a constant address into a direct
 * store (istrfold, uoptcopy.c) when it replaces something in the stored
 * value. So the increment is a local, `k = -2.0f; ... D.y = D.y + k`,
 * set before each loop; 800467C0's second step is `d = 45/-45; d /= 30`
 * like the first, since `d = e / 30` was propagated into the x store and
 * folded that one instead. 800488B0 matches with the inlined 80044FDC's
 * result in `r` and a dead `if (r == m) {}` (m not yet set) at the top
 * of the then-arm: m's range reaches the block where v0 holds the
 * result, so m can't take v0 (m v1, n a1, as in the original).
 * 800432D8 has `if (pad == 100.0f) {} do {} while (0);` at the top of the
 * first loop (TRICK): 100.0 is then the first constant seen and gets f20
 * (the `-(a) + 1.0f` form is no longer needed).
 *
 * What still differs (2 functions):
 * - 80049814 (8): the arms' addresses are in v1, the original's v0 (v,
 *   the loop pointer, is live there through the dead read and takes v0
 *   first). A separate variable for the arms does the same; one whose
 *   dead read is after the next call gets v1 and frees v0 for the
 *   addresses, but spills. `l` is `volatile` (semantics unchanged): the
 *   original keeps it in its frame slot, which gives the 40-byte frame.
 *   Plain `D_8004D4DC = D_8004D190` arms (no v) give 82.
 * - 800432D8 (5): `mul.s f6,f20,f4` (100.0 first) where ours has the
 *   product first, and dy0/sdy's homes are 4 bytes lower than the
 *   original's (72/68); a variable for 100.0 is propagated, and no
 *   declaration order moves the homes.
 * Several functions need an unused `pad` local for the original's frame.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define WRAP360(x) ((x) >= 360.0f ? (x) - 360.0f : ((x) < 0.0f ? (x) + 360.0f : (x)))

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Link_ovl14_01;

void func_ovl14_01_8004BE98(s32); /* 0xC00 */
void func_ovl14_01_8004BEA8(s32 *); /* 0xC02 */
void func_ovl14_01_8004BEB0(s32); /* 0xD00 */ /* also: void (s32, UnkStructA_40 **) x1 */
f32 func_ovl14_01_8004BEC0(void); /* 0xD02 */
s32 func_ovl14_01_8004BF00(s32); /* 0xD0A */
void func_ovl14_01_8004BF80(void (*)(UnkStructA *)); /* 0xE03 */ /* also: void (void (*)(Obj_0D02 *)) x1; void (void (*)(Obj_0D04 *)) x1; void (void (*)(Obj_0D06 *)) x1 */
void func_ovl14_01_8004BFB8(void); /* 0xF05 */
void func_ovl14_01_8004BFD0(void (*)(UnkStructA *)); /* 0xF08 */
s32 *func_ovl14_01_8004BFE8(void); /* 0xF0B */ /* also: s32 * (void) x3; Save_ovl0B_02 *(void) x1; UnkStruct_ovl0B_05_80046820 *(void) x1 */
void func_ovl14_01_8004C000(s32); /* 0xF0E */
void func_ovl14_01_8004C010(s32); /* 0xF10 */
void func_ovl14_01_8004C048(void); /* 0x1000 */
void func_ovl14_01_8004C058(void *); /* 0x1002 */
s32 func_ovl14_01_8004C078(void); /* 0x1006 */
void func_ovl14_01_8004C080(s32, void *); /* 0x1007 */
void func_ovl14_01_8004C088(s32); /* 0x1008 */
void func_ovl14_01_8004C0A0(const char *); /* 0x100B */
void func_ovl14_01_8004C0A8(void); /* 0x100C */
UnkStructA * func_ovl14_01_8004C0D8(s32); /* 0x1012 */ /* also: Obj02 * (s32) x1; Obj03 * (s32) x1; UnkStruct_ovl0A_05_80048CA0 *(s32) x1 */
void func_ovl14_01_8004C138(s32); /* 0x101E */
void func_ovl14_01_8004C5A0(UnkStructA_40 *, s32); /* 0x1505 */ /* also: void (Obj *, s32) x1; void (UnkStruct_ovl0A_02_80047A20_Inner *, s32) x1; void (UnkStruct_ovl0A_03_80047E20_Inner *, s32) x1 */
void func_ovl14_01_8004C5A8(UnkStructA_40 *, s32, s32, s32); /* 0x1506 */ /* also: void (Obj *, s32, s32, s32) x1; void (UnkStruct_ovl0A_02_80047A20_Inner *, s32, s32, s32) x1; void (UnkStruct_ovl0A_03_80047E20_Inner *, s32, s32, s32) x1 */
void func_ovl14_01_8004C5C0(UnkStructA_40 *, s32, s32); /* 0x1509 */ /* also: void (Obj *, s32, s32) x1; void (UnkStruct_ovl0A_02_80047A20_Inner *, s32, s32) x1; void (UnkStruct_ovl0A_03_80047E20_Inner *, s32, s32) x1 */
f32 func_ovl14_01_8004C5D8(UnkStructA_40 *, s32); /* 0x150C */ /* also: f32 (UnkStruct_ovl0A_02_80047A20_Inner *, s32) x1; f32 (UnkStruct_ovl0A_03_80047E20_Inner *, s32) x1; f32 (UnkStruct_ovl0A_05_80048CA0_Inner *, s32) x1 */
void func_ovl14_01_8004C6D8(f32, f32, f32); /* 0x1704 */
void func_ovl14_01_8004C6F8(f32, f32, f32); /* 0x1708 */
void func_ovl14_01_8004C700(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl14_01_8004C740(s32); /* 0x1711 */
void func_ovl14_01_8004C750(s32); /* 0x1713 */
void func_ovl14_01_8004C778(Vec3f *); /* 0x1718 */
void func_ovl14_01_8004C788(f32, f32, f32, f32); /* 0x171A */
void func_ovl14_01_8004C790(f32, f32); /* 0x171B */
void func_ovl14_01_8004C798(f32, f32, f32, f32); /* 0x171C */
void func_ovl14_01_8004C7F0(f32 *); /* 0x1727 */
void func_ovl14_01_8004C828(Vec3f *, Vec3f *, Vec3f *); /* 0x1803 */
void func_ovl14_01_8004C830(Vec3f *, Vec3f *); /* 0x1804 */
s32 func_ovl14_01_8004C848(UnkStructA *, s32); /* 0x1807 */ /* also: s32 (Obj_0D02 *, s32) x1; s32 (Obj_0D04 *, s32) x1; s32 (Obj_0D06 *, s32) x1 */
s32 func_ovl14_01_8004C860(s32, s32); /* 0x180A */
void func_ovl14_01_8004C868(UnkStructA *, s32); /* 0x180B */ /* also: void (Obj_0D02 *, s32) x1; void (Obj05 *, s32) x1; void (Obj_0D03 *, s32) x1 */
void func_ovl14_01_8004C880(UnkStructA *, UnkStructA *, Link_ovl14_01 *, s32); /* 0x180E */ /* also: void (UnkStructA *, UnkStructA *, Link_ovl13_01 *, s32) x1 */
void func_ovl14_01_8004C890(s32); /* 0x1810 */
void func_ovl14_01_8004C898(UnkStructA *, s32); /* 0x1811 */ /* also: void (Obj02 *, s32) x1; void (Obj03 *, s32) x1; void (UnkStruct_ovl0A_05_80048CA0 *, s32) x1 */
void func_ovl14_01_8004C8A0(UnkStructA *, s32); /* 0x1812 */ /* also: void (Obj02 *, s32) x1; void (Obj03 *, s32) x1; void (UnkStruct_ovl0A_05_80048CA0 *, s32) x1 */
s32 func_ovl14_01_8004C8B0(UnkStructA *); /* 0x1814 */ /* also: void (Obj02 *) x1; void (Obj03 *) x1; void (UnkStruct_ovl0A_05_80048CA0 *) x1 */
UnkStructA *func_ovl14_01_8004C8C0(s32, s32, s32, UnkStructA *); /* 0x1816 */ /* also: Obj02 * (s32, s32, s32, Obj02 *) x1; Obj03 * (s32, s32, s32, Obj03 *) x1; UnkStruct_ovl0A_05_80048CA0 *(s32, s32, s32, UnkStruct_ovl0A_05_80048CA0 *) x1 */
UnkStructA *func_ovl14_01_8004C8D0(UnkStructA *); /* 0x1818 */ /* also: void (Obj02 *) x1; void (Obj03 *) x1; Obj_0D02 *(Obj_0D02 *) x1 */
UnkStructA *func_ovl14_01_8004C8F0(s32, s32, UnkStructA *); /* 0x181C */
void func_ovl14_01_8004C918(UnkStructA *); /* 0x1821 */ /* also: void (Obj02 *) x1; void (Obj_0D02 *) x1; void (Obj_0D03 *) x1 */
UnkStructA *func_ovl14_01_8004C920(UnkStructA *, s32); /* 0x1822 */
void func_ovl14_01_8004C968(UnkStructA *, f32 *); /* 0x182B */ /* also: void (Obj02 *, f32 *) x1; void (Obj03 *, f32 *) x1; void (UnkStruct_ovl0A_05_80048CA0 *, f32 *) x1 */
void func_ovl14_01_8004C9A8(UnkStructA *); /* 0x1833 */
void func_ovl14_01_8004C9C8(s32 *); /* 0x1837 */
void func_ovl14_01_8004C9D0(void); /* 0x1838 */
void func_ovl14_01_8004C9D8(void); /* 0x1839 */
s32 func_ovl14_01_8004C9E8(void (*)(), void *, s32, s32, s32); /* 0x1900 */ /* also: void (void (*)(void), void *, s32, s32, s32) x6; s32 (void (*)(void), void *, s32, s32, s32) x4; s32 (void (*)(), void *, void *, s32, s32) x1 */
void func_ovl14_01_8004C9F8(void); /* 0x1902 */
void func_ovl14_01_8004CA08(s32); /* 0x1904 */ /* also: s32 (s32) x1 */
void *func_ovl14_01_8004CA10(void); /* 0x1905 */ /* also: Obj02 * (void) x1; Obj03 * (void) x1; UnkStruct_ovl0A_05_80048CA0 *(void) x1 */
s32 func_ovl14_01_8004CA30(void); /* 0x1909 */ /* also: void (void) x8 */
f32 func_ovl14_01_8004CB90(f32); /* 0x1D00 */
f32 func_ovl14_01_8004CB98(f32); /* 0x1D01 */
f64 func_ovl14_01_8004CBA0(void); /* 0x1D02 */
s32 func_ovl14_01_8004CBA8(s32); /* 0x1D03 */
void func_ovl14_01_8004CBB0(f32, f32); /* 0x1D04 */
void func_ovl14_01_8004CC00(void); /* 0x1D0E */
void func_ovl14_01_8004CC08(void); /* 0x1D0F */
void func_ovl14_01_8004CC10(void); /* 0x1D10 */
void func_ovl14_01_8004CC18(f32 *); /* 0x1D11 */
void func_ovl14_01_8004CC20(void); /* 0x1D12 */
s32 func_ovl14_01_8004CC50(s32); /* 0x1E04 */
void func_ovl14_01_8004CC60(s32); /* 0x1E06 */
void func_ovl14_01_8004CC68(s32); /* 0x1E07 */
s32 func_ovl14_01_8004CC70(s32); /* 0x1E08 */
void func_ovl14_01_8004CCE8(s32, s32, s32, f32); /* 0x2004 */
void func_ovl14_01_8004CD30(s32); /* 0x2200 */
void func_ovl14_01_8004CD40(s32); /* 0x2202 */
void func_ovl14_01_8004CD48(s32); /* 0x2203 */
void func_ovl14_01_8004CE40(s32, f32 *, s32); /* 0x2601 */ /* also: s32 (s32, f32 *, s32) x3; void (s32, f32 *, Obj_0D02 *) x1; void (s32, f32 *, Obj_0D03 *) x1 */
void func_ovl14_01_8004CE60(void *); /* 0x2701 */ /* also: void (UnkStruct_ovl0A_05_80048CA0 *) x1 */
s32 func_ovl14_01_8004CF70(s32); /* 0x2B00 */ /* also: s32 (s32) x6 */
void func_ovl14_01_8004CF80(s32); /* 0x2B02 */
void func_ovl14_01_8004CF88(void); /* 0x2B03 */
s32 func_ovl14_01_8004CF90(s32, f32, f32, f32); /* 0x2B04 */ /* also: void (s32, s32, s32, s32) x7 */
void func_ovl14_01_8004CF98(s32, f32 *); /* 0x2B05 */
void func_ovl14_01_8004CFA0(s32); /* 0x2B06 */
s32 func_ovl14_01_8004D000(void *, s32, s32, s32, f32); /* 0x2C03 */
void func_ovl14_01_8004D0E8(void); /* 0x3000 */
void func_ovl14_01_8004D0F0(void); /* 0x3001 */

/* .bss */
Vec3f D_ovl14_01_8004D4A0;
u8 D_ovl14_01_8004D4AC[4];
Vec3f D_ovl14_01_8004D4B0;
s32 D_ovl14_01_8004D4BC;
u8 D_ovl14_01_8004D4C0[4];
s32 D_ovl14_01_8004D4C4;
s32 D_ovl14_01_8004D4C8;
u8 D_ovl14_01_8004D4CC[4];
Vec3f D_ovl14_01_8004D4D0;
Vec3f *D_ovl14_01_8004D4DC;
s32 * D_ovl14_01_8004D4E0;
s32 D_ovl14_01_8004D4E4;
s32 D_ovl14_01_8004D4E8;
s32 D_ovl14_01_8004D4EC;
s32 D_ovl14_01_8004D4F0;
u8 D_ovl14_01_8004D4F4[4];
Vec3f D_ovl14_01_8004D4F8;
u8 D_ovl14_01_8004D504[4];
Vec3f D_ovl14_01_8004D508;
u8 D_ovl14_01_8004D514[4];
Vec3f D_ovl14_01_8004D518;
u8 D_ovl14_01_8004D524[4];
s32 D_ovl14_01_8004D528;
u8 D_ovl14_01_8004D52C[4];
s32 D_ovl14_01_8004D530;
f32 D_ovl14_01_8004D534;
f32 D_ovl14_01_8004D538;
s32 D_ovl14_01_8004D53C;
s32 D_ovl14_01_8004D540;
s32 D_ovl14_01_8004D544;
s32 D_ovl14_01_8004D548;
s32 D_ovl14_01_8004D54C;
s32 D_ovl14_01_8004D550;
s32 D_ovl14_01_8004D554;
s32 D_ovl14_01_8004D558;
u8 D_ovl14_01_8004D55C[4];
Link_ovl14_01 D_ovl14_01_8004D560[3];
u8 D_ovl14_01_8004D59C[4];
Link_ovl14_01 D_ovl14_01_8004D5A0[3];
UnkStructA * D_ovl14_01_8004D5DC;
UnkStructA * D_ovl14_01_8004D5E0;
UnkStructA * D_ovl14_01_8004D5E4;
UnkStructA * D_ovl14_01_8004D5E8;
UnkStructA * D_ovl14_01_8004D5EC;
UnkStructA * D_ovl14_01_8004D5F0;
UnkStructA * D_ovl14_01_8004D5F4;
UnkStructA * D_ovl14_01_8004D5F8;
u8 D_ovl14_01_8004D5FC[4];
UnkStructA *D_ovl14_01_8004D600[5];
s32 D_ovl14_01_8004D614;
UnkStructA *D_ovl14_01_8004D618[5];
f32 D_ovl14_01_8004D62C;
f32 D_ovl14_01_8004D630;
f32 D_ovl14_01_8004D634;
f32 D_ovl14_01_8004D638;
f32 D_ovl14_01_8004D63C;
f32 D_ovl14_01_8004D640;
s32 D_ovl14_01_8004D644;
s32 D_ovl14_01_8004D648;
s32 D_ovl14_01_8004D64C;
s32 D_ovl14_01_8004D650;
u8 D_ovl14_01_8004D654[4];
s32 D_ovl14_01_8004D658[5];
s32 D_ovl14_01_8004D66C;
s32 D_ovl14_01_8004D670[5];
f32 D_ovl14_01_8004D684;
f32 D_ovl14_01_8004D688;
u8 D_ovl14_01_8004D68C[4];
Vec3f D_ovl14_01_8004D690;
u8 D_ovl14_01_8004D69C[4];
Vec3f D_ovl14_01_8004D6A0;
u8 D_ovl14_01_8004D6AC[4];
Vec3f D_ovl14_01_8004D6B0;
s32 D_ovl14_01_8004D6BC;
u32 D_ovl14_01_8004D6C0;
s32 D_ovl14_01_8004D6C4;
s32 D_ovl14_01_8004D6C8;
s32 D_ovl14_01_8004D6CC;
Vec3f D_ovl14_01_8004D6D0;
s32 D_ovl14_01_8004D6DC;
Vec3f D_ovl14_01_8004D6E0;
u8 D_ovl14_01_8004D6EC[4];
Vec3f D_ovl14_01_8004D6F0[8];
s32 D_ovl14_01_8004D750[4];

void func_ovl14_01_80043010(UnkStructA **arg0, Link_ovl14_01 *arg1);
s32 func_ovl14_01_800431C4(s32 arg0, UnkStructA *arg1);
static void func_ovl14_01_800431F8(UnkStructA *obj);
void func_ovl14_01_80043250(s32 arg0);
void func_ovl14_01_800432D8(void);
void func_ovl14_01_80043624(void);
void func_ovl14_01_80043688(UnkStructA **arg0, Link_ovl14_01 *arg1);
void func_ovl14_01_800437B8(void);
void func_ovl14_01_800438D8(void);
void func_ovl14_01_800439AC(Vec3f *arg0, UnkStructA *arg1);
void func_ovl14_01_80043B20(void);
void func_ovl14_01_80043CC0(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_ovl14_01_80043D98(void);
void func_ovl14_01_80043F10(void);
void func_ovl14_01_80044104(void);
void func_ovl14_01_80044540(Vec3f *arg0);
void func_ovl14_01_800445D8(void);
void func_ovl14_01_800449C0(void);
void func_ovl14_01_80044B38(Vec3f *arg0, s32 arg1);
void func_ovl14_01_80044D50(Vec3f *arg0, f32 arg1);
s32 func_ovl14_01_80044FDC(void);
void func_ovl14_01_80045010(void);
void func_ovl14_01_80045124(void *arg0);
void func_ovl14_01_8004515C(void);
void func_ovl14_01_80045474(void);
void func_ovl14_01_800455AC(void);
void func_ovl14_01_800457F0(void);
void func_ovl14_01_80045D7C(void);
void func_ovl14_01_80045FA0(void *arg0);
void func_ovl14_01_80045FD8(void);
void func_ovl14_01_80046004(s32 arg0);
void func_ovl14_01_8004654C(void);
void func_ovl14_01_80046648(UnkStructA **arg0, Link_ovl14_01 *arg1);
void func_ovl14_01_800467C0(UnkStructA **arg0, Link_ovl14_01 *arg1);
void func_ovl14_01_8004697C(void);
s32 func_ovl14_01_80046AE8(void);
void func_ovl14_01_80046B98(s32 arg0, f32 arg1);
s32 func_ovl14_01_80046C38(void);
void func_ovl14_01_80046CE8(void);
s32 func_ovl14_01_80047344(void);
void func_ovl14_01_8004739C(s32 arg0);
void func_ovl14_01_80047594(Vec3f *arg0, s32 arg1);
void func_ovl14_01_8004769C(s32 arg0);
void func_ovl14_01_800476F8(f32 arg0, f32 arg1, s32 arg2);
void func_ovl14_01_80047730(s32 arg0);
void func_ovl14_01_80047798(s32 arg0);
void func_ovl14_01_800477EC(s32 arg0);
void func_ovl14_01_80047978(UnkStructA *arg0);
void func_ovl14_01_80047A10(void);
void func_ovl14_01_80047CDC(void);
void func_ovl14_01_80047E44(void);
void func_ovl14_01_800481B8(s32 arg0);
void func_ovl14_01_80048454(void);
void func_ovl14_01_800487A8(void);
void func_ovl14_01_8004882C(void);
void func_ovl14_01_800488B0(void);
void func_ovl14_01_80048ABC(UnkStructA **arg0, Link_ovl14_01 *arg1);
void func_ovl14_01_80048CE8(Vec3f *arg0, s32 arg1);
void *func_ovl14_01_80048D48(void *arg0);
void func_ovl14_01_80048DE8(s32 arg0);
void func_ovl14_01_80049368(s32 arg0);
void func_ovl14_01_800494C8(void);
void func_ovl14_01_80049618(void);
void func_ovl14_01_80049814(s32 arg0, UnkStructA **arg1, Link_ovl14_01 *arg2);
void func_ovl14_01_80049B70(void);
void func_ovl14_01_80049BC0(void);
void func_ovl14_01_80049BE0(u32 arg0, s32 arg1);
void func_ovl14_01_80049CF4(void);
void func_ovl14_01_80049F2C(void);
void func_ovl14_01_80049FA8(void);
s32 func_ovl14_01_8004A0CC(UnkStructA *arg0);
void func_ovl14_01_8004A11C(void);
void func_ovl14_01_8004A4E0(void);
void func_ovl14_01_8004A760(void);
void func_ovl14_01_8004A914(void);
void func_ovl14_01_8004AF68(void);
void func_ovl14_01_8004B024(UnkStructA *arg0);
void func_ovl14_01_8004B26C(void);
void func_ovl14_01_8004B2A8(void);
void func_ovl14_01_8004B39C(void);
void func_ovl14_01_8004B3EC(void);
void func_ovl14_01_8004B4B4(void);
void func_ovl14_01_8004B500(void);
void func_ovl14_01_8004B698(void);
void func_ovl14_01_8004B820(s32 arg0);
void func_ovl14_01_8004B908(void);
void func_ovl14_01_8004B9CC(void);
void func_ovl14_01_8004BA48(f32 arg0);
void func_ovl14_01_8004BA90(f32 arg0, f32 arg1, f32 arg2);
void func_ovl14_01_8004BAEC(void);

/* .data */
Vec3f D_ovl14_01_8004D190[5] = {
    { 1852.0f, 500.0f, 350.0f },
    { 1852.0f, 440.22833f, 355.22934f },
    { 1852.0f, 191.1796f, 377.01746f },
    { 1852.0f, 191.1796f, 437.01746f },
    { 1851.9995f, 190.63454f, 857.0171f }
};
Vec3f D_ovl14_01_8004D1CC[5] = {
    { 2848.0f, 500.0f, 350.0f },
    { 2848.0f, 440.22833f, 355.22934f },
    { 2847.999f, 191.1796f, 377.01746f },
    { 2847.999f, 191.1796f, 437.01746f },
    { 2847.9988f, 190.63454f, 857.0171f }
};

/* unused: the stubs IDO -O3 leaves after the tail */
static void func_ovl14_01_8004BB04(void) {
}

static void func_ovl14_01_8004BB0C(void) {
}

static void func_ovl14_01_8004BB14(void) {
}

static void func_ovl14_01_8004BB1C(void) {
}

static void func_ovl14_01_8004BB24(void) {
}

static void func_ovl14_01_8004BB2C(void) {
}

static void func_ovl14_01_8004BB34(void) {
}

static void func_ovl14_01_8004BB3C(void) {
}

static void func_ovl14_01_8004BB44(void) {
}

void func_ovl14_01_8004BAEC(void) {
    D_ovl14_01_8004D4C4 = -1;
    D_ovl14_01_8004D4C8 = -1;
}

void func_ovl14_01_8004BA90(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl14_01_8004C6D8(D_ovl14_01_8004D4D0.x, D_ovl14_01_8004D4D0.y, D_ovl14_01_8004D4D0.z);
    func_ovl14_01_8004C6F8(arg0, arg1, arg2);
    func_ovl14_01_8004CA08(0xB4);
}

void func_ovl14_01_8004BA48(f32 arg0) {
    f32 sp1C;

    func_ovl14_01_8004C700(&sp1C, NULL, NULL);
    func_ovl14_01_8004C6F8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl14_01_8004B9CC(void) {
    void *sp1C;

    sp1C = func_ovl14_01_8004CA10();
    if (func_ovl14_01_8004CC70(0x413) == 0) {
        do {
            func_ovl14_01_8004CA30();
        } while (func_ovl14_01_8004CC70(0x413) == 0);
    }
    if (!(*D_ovl14_01_8004D4E0 & 2)) {
        func_ovl14_01_8004CF80((s32) sp1C);
    }
    func_ovl14_01_8004C9F8();
}

static void func_ovl14_01_8004B690() {
}

static void func_ovl14_01_8004B688() {
}

static void func_ovl14_01_8004B680() {
}

void func_ovl14_01_8004B698(void) {
    func_ovl14_01_8004B690();
    func_ovl14_01_8004B688();
    func_ovl14_01_8004B680();
    func_ovl14_01_8004BE98(0x1D1);
    func_ovl14_01_8004BEB0(0x1D2);
    func_ovl14_01_8004C048();
    func_ovl14_01_8004C0D8(func_ovl14_01_8004C078())->unk40->unk20 = 180.0f;
    func_ovl14_01_8004BF80(func_ovl14_01_80047978);
    func_ovl14_01_8004BFD0(func_ovl14_01_8004B024);
    func_ovl14_01_8004BEA8(&D_ovl14_01_8004D528);
    D_ovl14_01_8004D518.x = ((f32) ((s32) D_ovl14_01_8004D528 / 2) * 100.0f) - 50.0f;
    func_ovl14_01_8004BF00(0);
    D_ovl14_01_8004D518.y = 0.0f;
    D_ovl14_01_8004D518.z = ((f32) ((s32) D_ovl14_01_8004D530 / 2) * 100.0f) - 50.0f;
    func_ovl14_01_8004CD30(0);
    D_ovl14_01_8004D534 = 0.0f;
    D_ovl14_01_8004D538 = -90.0f;
    func_ovl14_01_8004CBB0(D_ovl14_01_8004D534, D_ovl14_01_8004D538);
    func_ovl14_01_8004C9E8(func_ovl14_01_8004A760, NULL, 0, 0, 0x150);
    func_ovl14_01_8004AF68();
    func_ovl14_01_8004C9D0();
    func_ovl14_01_8004CC08();
    func_ovl14_01_8004A914();
}

void func_ovl14_01_8004B908(void) {
    func_ovl14_01_8004C088(1);
    if (func_ovl14_01_8004CC70(0x413) == 0) {
        do {
            func_ovl14_01_8004CA30();
        } while (func_ovl14_01_8004CC70(0x413) == 0);
    }
    func_ovl14_01_8004C088(1);
    func_ovl14_01_8004C000(0);
    if (func_ovl14_01_8004CC50(0xA4) != 0) {
        func_ovl14_01_8004C138(1);
        func_ovl14_01_8004C0A0("WM1 WAP WG1 M1 ST1 M6 ST20 WSH WDNE WB2 ST10 M2 ST8 M4 ST1");
        func_ovl14_01_8004C0A0("WM1 WAP WG1 M1 ST1 M6 ST20 WSH WDE WB4 ST10 M2 ST8 M4 ST1");
        func_ovl14_01_8004C0A0("WM1 WAP WG1 WSH WDSW WB7 ST1 WDS WB0 M1 ST1 M6 ST10 M2 ST8 M4 ST60 MB ST1");
        func_ovl14_01_8004CA08(0x5A);
    } else {
        func_ovl14_01_8004C0A0("WM1 WAP WG1 M1 ST1 M6 ST20 WSH WDNE WB2 ST20 M2 ST8 M4 ST1 WSH WDSW WB4 ST1 WSH WDNW WB3 ST1");
        func_ovl14_01_8004CA08(0x28);
    }
    func_ovl14_01_8004D0E8();
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_8004B820(s32 arg0) {
    switch (arg0) {
    case 2:
        func_ovl14_01_8004B698();
        return;
    case 4:
        func_ovl14_01_8004B500();
        return;
    case 5:
        func_ovl14_01_8004B3EC();
        return;
    case 3:
        func_ovl14_01_8004CC60(0x413);
        D_ovl14_01_8004D4BC = func_ovl14_01_8004C078(); func_ovl14_01_8004C058(&D_ovl14_01_8004D4B0);
        func_ovl14_01_8004C080(D_ovl14_01_8004D4BC, &D_ovl14_01_8004D4A0);
        return;
    case 11:
        func_ovl14_01_8004CC10();
        func_ovl14_01_8004CC60(0x401);
        return;
    case 1:
        if (func_ovl14_01_8004CC70(0x401) == 0) {
            func_ovl14_01_8004CC10();
        }
        func_ovl14_01_8004B2A8();
        /* fallthrough */
    case 17:
        break;
    default:
        return;
    }
}

void func_ovl14_01_8004B500(void) {
    func_ovl14_01_8004C890(0);
    func_ovl14_01_8004C0A8();
    func_ovl14_01_8004C010(0);
    func_ovl14_01_8004C740(0xF);
    func_ovl14_01_8004C750(2);
    func_ovl14_01_8004C788(D_ovl14_01_8004D518.x, D_ovl14_01_8004D518.z, 100.0f, 400.0f);
    func_ovl14_01_8004C798(D_ovl14_01_8004D518.x, D_ovl14_01_8004D518.z, D_ovl14_01_8004D518.x, D_ovl14_01_8004D518.z);
    func_ovl14_01_8004C790(25.0f, 25.0f);
    func_ovl14_01_8004C6F8(32768.0f, 25.0f, 2500.0f);
    func_ovl14_01_8004C6D8(2300.0f, 500.0f, 1600.0f);
    D_ovl14_01_8004D508.x = 0.0f;
    D_ovl14_01_8004D508.y = 90.0f;
    D_ovl14_01_8004D508.z = 400.0f;
    func_ovl14_01_8004C778(&D_ovl14_01_8004D508);
    D_ovl14_01_8004D4F8.x = 0.0f;
    D_ovl14_01_8004D4F8.y = 25.0f;
    D_ovl14_01_8004D4F8.z = 2500.0f;
    func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
    func_ovl14_01_8004C6F8(0.0f, D_ovl14_01_8004D4F8.y, 2500.0f);
    func_ovl14_01_800437B8();
    if (*D_ovl14_01_8004D4E0 & 2) {
        func_ovl14_01_8004C9E8(func_ovl14_01_8004B908, NULL, 0, 0, 0x130);
    }
    func_ovl14_01_8004CC20();
}

void func_ovl14_01_8004B4B4(void) {
    if (*D_ovl14_01_8004D4E0 & 2) {
        func_ovl14_01_8004C9E8(func_ovl14_01_8004B908, NULL, 0, 0, 0x130);
    }
}

void func_ovl14_01_8004B3EC(void) {
    func_ovl14_01_800432D8();
    D_ovl14_01_8004D4BC = func_ovl14_01_8004C078(); func_ovl14_01_8004C058(&D_ovl14_01_8004D4B0);
    func_ovl14_01_8004C080(D_ovl14_01_8004D4BC, &D_ovl14_01_8004D4A0);
    func_ovl14_01_8004CC00();
    func_ovl14_01_8004C9C8(&D_ovl14_01_8004D548);
    if (func_ovl14_01_8004CC70(0x400) != 0) {
        if (!(*D_ovl14_01_8004D4E0 & 2)) {
            func_ovl14_01_8004CF80(0x13);
        }
    } else {
        func_ovl14_01_8004CC60(0x400);
    }
    func_ovl14_01_8004C9E8(func_ovl14_01_8004B9CC, (void *)0x11, 0, 0, 0x150);
}

static void func_ovl14_01_8004B394() {
}

static void func_ovl14_01_8004B38C() {
}

void func_ovl14_01_8004B39C(void) {
    func_ovl14_01_8004B394();
    func_ovl14_01_8004B38C();
    func_ovl14_01_8004CC60(0x413);
    D_ovl14_01_8004D4BC = func_ovl14_01_8004C078(); func_ovl14_01_8004C058(&D_ovl14_01_8004D4B0);
    func_ovl14_01_8004C080(D_ovl14_01_8004D4BC, &D_ovl14_01_8004D4A0);
}

void func_ovl14_01_8004B2A8(void) {
    if (D_ovl14_01_8004D4E4 != -1) {
        func_ovl14_01_8004CFA0(D_ovl14_01_8004D4E4);
        D_ovl14_01_8004D4E4 = -1;
    }
    if (D_ovl14_01_8004D4E8 != -1) {
        func_ovl14_01_8004CFA0(D_ovl14_01_8004D4E8);
        D_ovl14_01_8004D4E8 = -1;
    }
    if (D_ovl14_01_8004D4EC != -1) {
        func_ovl14_01_8004CFA0(D_ovl14_01_8004D4EC);
        D_ovl14_01_8004D4EC = -1;
    }
    if (D_ovl14_01_8004D4F0 != -1) {
        func_ovl14_01_8004CFA0(D_ovl14_01_8004D4F0);
        D_ovl14_01_8004D4F0 = -1;
    }
    func_ovl14_01_8004C9D8();
    if (*D_ovl14_01_8004D4E0 & 2) {
        func_ovl14_01_8004D0F0();
    }
}

void func_ovl14_01_8004B26C(void) {
    if (*D_ovl14_01_8004D4E0 & 2) {
        func_ovl14_01_8004D0F0();
    }
}

void func_ovl14_01_8004B024(UnkStructA *arg0) {
    Vec3f vel;
    Vec3f dir;
    f32 rx;
    f32 ry;
    f32 rz;

    func_ovl14_01_800431C4(0x1E, arg0);
    func_ovl14_01_8004C828(&D_ovl14_01_8004D518, &D_ovl14_01_8004D4A0, &dir);
    dir.y = 0.0f;
    dir.z = 10.0f;
    func_ovl14_01_8004C830(&dir, &vel);
    arg0->unk68 = 50.0f;
    rx = func_ovl14_01_8004CBA0() * 20.0;
    ry = func_ovl14_01_8004CBA0() * 20.0;
    rz = func_ovl14_01_8004CBA0() * 20.0;
    if (func_ovl14_01_8004CBA8(1) != 0) {
        rx *= -1.0f;
    }
    if (func_ovl14_01_8004CBA8(1) != 0) {
        ry *= -1.0f;
    }
    if (func_ovl14_01_8004CBA8(1) != 0) {
        rz *= -1.0f;
    }
    while (((arg0->unk40->unk14 <= func_ovl14_01_8004BEC0()) ? 1 : 0) == 0) {
        arg0->unk40->unk10 += vel.x;
        arg0->unk40->unk18 += vel.z;
        arg0->unk40->unk20 += ry;
        arg0->unk40->unk1C += rx;
        arg0->unk40->unk24 += rz;
        func_ovl14_01_8004C918(arg0);
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_80047978(arg0);
}

void func_ovl14_01_8004AF68(void) {
    func_ovl14_01_8004CC68(0x43F);
    func_ovl14_01_8004CC68(0x43E);
    func_ovl14_01_8004CC68(0x41F);
    func_ovl14_01_8004CC68(0x41E);
    func_ovl14_01_8004CC68(0x41D);
    func_ovl14_01_8004CC68(0x41C);
    func_ovl14_01_8004CC68(0x41B);
    func_ovl14_01_8004CC68(0x41A);
    func_ovl14_01_8004CC68(0x419);
    func_ovl14_01_8004CC68(0x418);
    func_ovl14_01_8004CC68(0x413);
    func_ovl14_01_8004CC68(0x417);
    func_ovl14_01_8004CC60(0x415);
    func_ovl14_01_8004CC68(0x414);
    func_ovl14_01_8004CC68(0x401);
    D_ovl14_01_8004D4E0 = func_ovl14_01_8004BFE8();
    if (D_ovl14_01_8004D4E0[4] == 0) {
        func_ovl14_01_8004CC60(0x41F);
    }
}

void func_ovl14_01_8004A914(void) {
    s32 pad;
    Vec3f angle;
    s32 i;

    D_ovl14_01_8004D4E4 = -1;
    D_ovl14_01_8004D4E8 = -1;
    D_ovl14_01_8004D4EC = D_ovl14_01_8004D4F0 = -1;
    D_ovl14_01_8004D6C0 = 0;
    D_ovl14_01_8004D6C4 = 0;
    D_ovl14_01_8004D53C = 0;
    D_ovl14_01_8004D540 = 0;
    D_ovl14_01_8004D544 = 6;
    D_ovl14_01_8004D548 = 14;
    D_ovl14_01_8004D54C = 8;
    D_ovl14_01_8004D550 = 8;
    D_ovl14_01_8004D554 = 4;
    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        D_ovl14_01_8004D544 -= 4;
        D_ovl14_01_8004D548 -= 4;
        D_ovl14_01_8004D54C /= 2;
        D_ovl14_01_8004D550 /= 2;
        D_ovl14_01_8004D554 /= 2;
    }
    D_ovl14_01_8004D6A0.x = D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.z = 0.0f;
    D_ovl14_01_8004D6BC = 0;
    D_ovl14_01_8004D6B0.x = D_ovl14_01_8004D518.x;
    D_ovl14_01_8004D6B0.y = D_ovl14_01_8004D518.y + -300.0f;
    D_ovl14_01_8004D6B0.z = D_ovl14_01_8004D518.z;
    angle.x = 180.0f;
    angle.y = 0.0f;
    angle.z = 1200.0f;
    for (i = 0; i < 8; i++) {
        func_ovl14_01_8004C830(&angle, &D_ovl14_01_8004D6F0[i]);
        D_ovl14_01_8004D6F0[i].x += D_ovl14_01_8004D6B0.x;
        D_ovl14_01_8004D6F0[i].y += D_ovl14_01_8004D6B0.y;
        D_ovl14_01_8004D6F0[i].z += D_ovl14_01_8004D6B0.z;
        angle.x = WRAP360(angle.x + 45.0f);
    }
    D_ovl14_01_8004D6CC = D_ovl14_01_8004D6C8 = 0;
    D_ovl14_01_8004D690.x = D_ovl14_01_8004D6F0[D_ovl14_01_8004D6C8].x;
    D_ovl14_01_8004D690.y = D_ovl14_01_8004D6F0[D_ovl14_01_8004D6C8].y;
    D_ovl14_01_8004D690.z = D_ovl14_01_8004D6F0[D_ovl14_01_8004D6C8].z;
    D_ovl14_01_8004D62C = 31.0f;
    D_ovl14_01_8004D630 = 31.0f;
    D_ovl14_01_8004D634 = 31.0f;
    D_ovl14_01_8004D684 = 0.0f;
    D_ovl14_01_8004D638 = 0;
    D_ovl14_01_8004D63C = 0;
    D_ovl14_01_8004D640 = 0;
    D_ovl14_01_8004D688 = 0.0f;
    D_ovl14_01_8004D5E8 = func_ovl14_01_8004C8C0(0x1C4, 0x01008014, 0xC0, NULL);
    D_ovl14_01_8004D5E8->unk30 = 2;
    D_ovl14_01_8004D5E8->unk34 = 300.0f;
    D_ovl14_01_8004D5E8->unk38 = 900.0f;
    D_ovl14_01_8004D5E8->unkC = 0x2002;
    D_ovl14_01_8004D5E8->unk40->unk10 = D_ovl14_01_8004D690.x;
    D_ovl14_01_8004D5E8->unk58 = D_ovl14_01_8004D5E8->unk40->unk10;
    D_ovl14_01_8004D5E8->unk40->unk14 = D_ovl14_01_8004D690.y;
    D_ovl14_01_8004D5E8->unk5C = D_ovl14_01_8004D5E8->unk40->unk14;
    D_ovl14_01_8004D5E8->unk40->unk18 = D_ovl14_01_8004D690.z;
    D_ovl14_01_8004D5E8->unk60 = D_ovl14_01_8004D5E8->unk40->unk18;
    D_ovl14_01_8004D5DC = func_ovl14_01_8004C8F0(0x1CA, 0x01400000, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5E0 = func_ovl14_01_8004C8F0(-1, 0x400000, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5E0->unk50 = 800.0f;
    M2C_FIELD(D_ovl14_01_8004D5E0, Link_ovl14_01 **, 0x3C) = D_ovl14_01_8004D560;
    D_ovl14_01_8004D5F4 = func_ovl14_01_8004C8F0(-1, 0x400000, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5F4->unk50 = 800.0f;
    D_ovl14_01_8004D5F4->unk54 = 490.0f;
    func_ovl14_01_8004C868(D_ovl14_01_8004D5F4, 0xD0);
    D_ovl14_01_8004D5E4 = func_ovl14_01_8004C8F0(-1, 0x01600000, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5E4->unk50 = 550.0f;
    D_ovl14_01_8004D5E4->unk54 = 250.0f;
    D_ovl14_01_8004D5E4->unk40->unk30 = 3.0f;
    D_ovl14_01_8004D5E4->unk40->unk28 = D_ovl14_01_8004D5E4->unk40->unk2C = D_ovl14_01_8004D5E4->unk40->unk30;
    D_ovl14_01_8004D5EC = func_ovl14_01_8004C8F0(0x1C5, 0x01400000, D_ovl14_01_8004D5DC);
    D_ovl14_01_8004D5EC->unk50 = 900.0f;
    D_ovl14_01_8004D5F0 = func_ovl14_01_8004C8F0(0x1C6, 0x01408010, D_ovl14_01_8004D5EC);
    D_ovl14_01_8004D5F0->unk50 = 80.0f;
    D_ovl14_01_8004D5F0->unk30 = 4;
    D_ovl14_01_8004D5F0->unk34 = 100.0f;
    D_ovl14_01_8004D5F0->unk38 = 150.0f;
    D_ovl14_01_8004D5F0->unkC = 0x2002;
    func_ovl14_01_80049814(0x1C8, D_ovl14_01_8004D600, D_ovl14_01_8004D560);
    func_ovl14_01_80049814(0x1C9, D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
    func_ovl14_01_80043010(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
    func_ovl14_01_80043010(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
    func_ovl14_01_8004C9E8(func_ovl14_01_80049FA8, NULL, 0, 0, 0x110);
    func_ovl14_01_8004C9E8(func_ovl14_01_8004A11C, NULL, 0, 0, 0x110);
    func_ovl14_01_8004C9E8(func_ovl14_01_80043B20, NULL, 0, 0, 0x150);
}

void func_ovl14_01_8004A760(void) {
    f32 sb;
    f32 sa;
    f32 y;
    f32 x;
    f64 r;

    y = 0.0f;
    x = 0.0f;
    for (;;) {
        if (x + 0.1f >= 360.0f) {
            x = (x + 0.1f) - 360.0f;
        } else {
            sb = (x + 0.1f < 0.0f) ? (x + 0.1f) + 360.0f : x + 0.1f;
            x = sb;
        }
        if (y + 0.2f >= 360.0f) {
            y = (y + 0.2f) - 360.0f;
        } else {
            sb = (y + 0.2f < 0.0f) ? (y + 0.2f) + 360.0f : y + 0.2f;
            y = sb;
        }
        sa = func_ovl14_01_8004CB90(x);
        r = func_ovl14_01_8004CBA0();
        sb = func_ovl14_01_8004CB90(y);
        func_ovl14_01_8004CBB0(((f32) r * 3.0f * sa) + D_ovl14_01_8004D534, ((f32) func_ovl14_01_8004CBA0() * 3.0f * sb) + D_ovl14_01_8004D538);
        func_ovl14_01_8004CA30();
    }
}

void func_ovl14_01_8004A4E0(void) {
    UnkStructA *o;
    Vec3f pos;
    s32 i;
    s32 flag;

    o = func_ovl14_01_8004CA10();
    if (o == D_ovl14_01_8004D5E8) {
        flag = D_ovl14_01_8004D548;
    }
    if (o == D_ovl14_01_8004D5F0) {
        flag = D_ovl14_01_8004D554;
    }
    if (o == D_ovl14_01_8004D600[4]) {
        flag = D_ovl14_01_8004D54C;
    }
    if (o == D_ovl14_01_8004D618[4]) {
        flag = D_ovl14_01_8004D550;
    }
    if (flag != 0) {
        func_ovl14_01_800431C4(0x101, o);
        if (o == D_ovl14_01_8004D5E8) {
            func_ovl14_01_800431C4(0xC3, D_ovl14_01_8004D5DC);
        }
    }
    for (i = 0; i < 15; i++) {
        pos.x = func_ovl14_01_8004CB98((f32) func_ovl14_01_8004CBA0() * 360.0f) * 200.0f;
        pos.y = func_ovl14_01_8004CB98((f32) func_ovl14_01_8004CBA0() * 360.0f) * 200.0f;
        pos.z = func_ovl14_01_8004CB98((f32) func_ovl14_01_8004CBA0() * 360.0f) * 200.0f;
        if (o == D_ovl14_01_8004D5E8) {
            pos.x *= 2.0f;
            pos.z *= 2.0f;
            pos.y += 500.0f;
        }
        if (flag != 0) {
            func_ovl14_01_800439AC(&pos, o);
        } else {
            pos.x += o->unk40->unk10;
            pos.y += o->unk40->unk14;
            pos.z += o->unk40->unk18;
            if (o == D_ovl14_01_8004D5E8) {
                if (i < 14) {
                    if (func_ovl14_01_8004CBA8(1) != 0) {
                        func_ovl14_01_8004CF70(0xC9);
                    } else {
                        func_ovl14_01_8004CF70(0x102);
                    }
                } else {
                    func_ovl14_01_8004CF70(0xC7);
                }
            }
            func_ovl14_01_8004CE40(0x13, (f32 *)&pos, 0);
        }
        func_ovl14_01_8004CA08(8);
    }
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_8004A11C(void) {
    Vec3f v;
    s32 t4;
    s32 t3;
    s32 t2;
    s32 t1;
    s32 pad;
    s32 cnt;
    s32 flag;
    s32 n;

    flag = 0;
    t4 = 0;
    t3 = 0;
    t2 = 0;
    t1 = 0;
    cnt = 0;
    for (;;) {
        if (flag == 0 && D_ovl14_01_8004D548 == 0) {
            flag = 1;
            func_ovl14_01_8004CF88();
        }
        D_ovl14_01_8004D5E8->unk40->unk10 = D_ovl14_01_8004D690.x;
        D_ovl14_01_8004D5E8->unk40->unk14 = D_ovl14_01_8004D690.y;
        D_ovl14_01_8004D5E8->unk40->unk18 = D_ovl14_01_8004D690.z;
        D_ovl14_01_8004D5E8->unk40->unk1C = D_ovl14_01_8004D6A0.y;
        D_ovl14_01_8004D5E8->unk40->unk20 = D_ovl14_01_8004D6A0.x;
        D_ovl14_01_8004D5E8->unk40->unk24 = D_ovl14_01_8004D6A0.z;
        if (D_ovl14_01_8004D548 != 0) {
            if (t1 == 0) {
                n = func_ovl14_01_8004A0CC(D_ovl14_01_8004D5E8);
                D_ovl14_01_8004D548 -= n;
                if (D_ovl14_01_8004D548 < 0) {
                    D_ovl14_01_8004D548 = 0;
                }
                if (n != 0) {
                    func_ovl14_01_80045124(D_ovl14_01_8004D5E8);
                    t1 = 120;
                }
            } else {
                t1--;
            }
            if (D_ovl14_01_8004D548 < 14 && D_ovl14_01_8004D554 != 0 && func_ovl14_01_8004CC70(0x419) != 0) {
                if (cnt == 0) {
                    v.x = D_ovl14_01_8004D5F0->unk40->unk10;
                    v.y = D_ovl14_01_8004D5F0->unk40->unk14 + 210.0f;
                    v.z = D_ovl14_01_8004D5F0->unk40->unk18;
                    func_ovl14_01_8004CE40(14, (f32 *) &v, 0);
                    cnt = D_ovl14_01_8004D548 * 15;
                } else {
                    cnt--;
                }
            }
        }
        if (D_ovl14_01_8004D54C != 0) {
            if (t2 == 0) {
                n = func_ovl14_01_8004A0CC(D_ovl14_01_8004D600[4]);
                D_ovl14_01_8004D54C -= n;
                if (D_ovl14_01_8004D54C < 0) {
                    D_ovl14_01_8004D54C = 0;
                }
                if (n != 0) {
                    func_ovl14_01_80045124(D_ovl14_01_8004D600[4]);
                    t2 = 120;
                }
            } else {
                t2--;
            }
        }
        if (D_ovl14_01_8004D550 != 0) {
            if (t3 == 0) {
                n = func_ovl14_01_8004A0CC(D_ovl14_01_8004D618[4]);
                D_ovl14_01_8004D550 -= n;
                if (D_ovl14_01_8004D550 < 0) {
                    D_ovl14_01_8004D550 = 0;
                }
                if (n != 0) {
                    func_ovl14_01_80045124(D_ovl14_01_8004D618[4]);
                    t3 = 120;
                }
            } else {
                t3--;
            }
        }
        if (D_ovl14_01_8004D554 != 0) {
            if (t4 == 0) {
                n = func_ovl14_01_8004A0CC(D_ovl14_01_8004D5F0);
                D_ovl14_01_8004D554 -= n;
                if (D_ovl14_01_8004D554 < 0) {
                    D_ovl14_01_8004D554 = 0;
                }
                if (n != 0) {
                    func_ovl14_01_80045124(D_ovl14_01_8004D5F0);
                    t4 = 120;
                }
            } else {
                t4--;
            }
        }
        func_ovl14_01_800445D8();
        func_ovl14_01_80044104();
        func_ovl14_01_8004CA30();
    }
}

s32 func_ovl14_01_8004A0CC(UnkStructA *arg0) {
    s32 flags;
    s32 n;

    flags = func_ovl14_01_8004C848(arg0, 0x40);
    if (flags & 0x6000) {
        n = 1;
        if (flags & 0x2000) {
            n = 2;
        }
        if (flags & 0x4000) {
            n++;
        }
    } else {
        n = 0;
    }
    return n;
}

void func_ovl14_01_80049FA8(void) {
    while (func_ovl14_01_8004CC70(0x413) == 0) {
        func_ovl14_01_8004CA30();
    }
    D_ovl14_01_8004D6C0 = 0;
    D_ovl14_01_8004D6C4 = 0;
    func_ovl14_01_80045010();
    while (D_ovl14_01_8004D548 != 0 && D_ovl14_01_8004D544 != 0) {
        func_ovl14_01_80049CF4();
        func_ovl14_01_80049BE0(D_ovl14_01_8004D6C0, D_ovl14_01_8004D6C4);
        func_ovl14_01_8004697C();
        D_ovl14_01_8004D6C0 = 0;
        D_ovl14_01_8004D6C4 = 0;
        func_ovl14_01_80045010();
        func_ovl14_01_8004697C();
    }
    func_ovl14_01_8004C010(1);
    func_ovl14_01_8004515C();
    func_ovl14_01_8004CC68(0x415);
    func_ovl14_01_80049F2C();
    func_ovl14_01_8004BFB8();
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80049F2C(void) {
    s32 var_s0;

    var_s0 = 0;
    if (func_ovl14_01_8004CC70(0x41E) != 0) {
        var_s0 = 1;
    }
    if (func_ovl14_01_8004CC70(0x41D) != 0) {
        var_s0 += 1;
    }
    if (func_ovl14_01_8004CC70(0x41C) != 0) {
        var_s0 += 1;
    }
    if (func_ovl14_01_8004CC70(0x417) != 0) {
        var_s0 += 1;
    }
    M2C_FIELD(D_ovl14_01_8004D4E0, s32 *, 0x2C) = var_s0;
}

void func_ovl14_01_80049CF4(void) {
    u32 temp_v0;

    D_ovl14_01_8004D6C0 = 0xA;
    D_ovl14_01_8004D6C4 = 0;
    if ((D_ovl14_01_8004D54C != 0) && (D_ovl14_01_8004D550 != 0)) {
        if (func_ovl14_01_8004CBA0() < 0.4000000059604645) {
            D_ovl14_01_8004D6C0 = 1;
            D_ovl14_01_8004D6C4 = 0;
        } else {
            D_ovl14_01_8004D6C0 = 2;
            D_ovl14_01_8004D6C4 = 1;
            if (func_ovl14_01_8004CC70(0x41F) == 0) {
                D_ovl14_01_8004D6C4 += func_ovl14_01_8004CBA8(1) + 1;
            }
        }
    } else {
        temp_v0 = func_ovl14_01_8004CBA8(9);
        switch (temp_v0) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (D_ovl14_01_8004D554 != 0) {
                D_ovl14_01_8004D6C0 = 4;
                D_ovl14_01_8004D6C4 = func_ovl14_01_8004CBA8(4) + 4;
            } else {
            case 4:
            case 5:
            case 6:
            case 7:
                if ((D_ovl14_01_8004D54C != 0) || (D_ovl14_01_8004D550 != 0)) {
                    D_ovl14_01_8004D6C0 = 2;
                    D_ovl14_01_8004D6C4 = 1;
                    if (func_ovl14_01_8004CC70(0x41F) == 0) {
                        D_ovl14_01_8004D6C4 += func_ovl14_01_8004CBA8(1) + 1;
                    }
                } else {
                default:
                    D_ovl14_01_8004D6C0 = 3;
                    if (func_ovl14_01_8004CC70(0x41F) != 0) {
                        D_ovl14_01_8004D6C4 = func_ovl14_01_8004CBA8(1) + 1;
                    } else {
                        D_ovl14_01_8004D6C4 = func_ovl14_01_8004CBA8(2) + 3;
                        if ((func_ovl14_01_8004CBA8(0x1F) == 0) && (func_ovl14_01_8004CC70(0x418) != 0)) {
                            D_ovl14_01_8004D6C4 = 0xA;
                        }
                    }
                }
            }
            break;
        }
    }
    if (*D_ovl14_01_8004D4E0 & 2) {
        if (func_ovl14_01_8004CC50(0xA4) != 0) {
            D_ovl14_01_8004D6C0 = 1;
            D_ovl14_01_8004D6C4 = 0;
        } else {
            D_ovl14_01_8004D6C0 = 2;
            D_ovl14_01_8004D6C4 = 1;
        }
    }
}

void func_ovl14_01_80049BE0(u32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
        func_ovl14_01_80045010();
        return;
    case 3:
        func_ovl14_01_800477EC(arg1);
        return;
    case 4:
        func_ovl14_01_800481B8(arg1);
        return;
    case 1:
        func_ovl14_01_800488B0();
        return;
    case 2:
        func_ovl14_01_80049368(arg1);
        return;
    case 6:
        func_ovl14_01_80046B98(0, 1.0f);
        func_ovl14_01_80046004(arg1);
        return;
    case 7:
        func_ovl14_01_800467C0(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        return;
    case 8:
        func_ovl14_01_800467C0(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
        return;
    case 9:
        func_ovl14_01_8004515C();
        return;
    case 10:
        func_ovl14_01_8004CA30();
        return;
    case 5:
        func_ovl14_01_80046CE8();
        /* fallthrough */
    default:
        return;
    }
}

void func_ovl14_01_80049BC0(void) {
    func_ovl14_01_8004CA30();
}

void func_ovl14_01_80049B70(void) {
    Vec3f pos;

    pos.x = D_ovl14_01_8004D6D0.x;
    pos.y = D_ovl14_01_8004D6D0.y;
    pos.z = D_ovl14_01_8004D6D0.z;
    func_ovl14_01_80044B38(&pos, D_ovl14_01_8004D6DC);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80049814(s32 id, UnkStructA **parts, Link_ovl14_01 *links) {
    UnkStructA **base;
    Link_ovl14_01 * volatile l;
    UnkStructA *o;
    Vec3f *v;
    f32 s;
    s32 i;

    base = parts;
    *parts = func_ovl14_01_8004C8F0(-1, 0x400000, D_ovl14_01_8004D5E0);
    if (id == 0x1C8) {
        (*parts)->unk4C = -498.0f;
        D_ovl14_01_8004D4DC = v = D_ovl14_01_8004D190;
    } else {
        (*parts)->unk4C = 498.0f;
        D_ovl14_01_8004D4DC = v = D_ovl14_01_8004D1CC;
    }
    if (v) {}
    M2C_FIELD(*parts, Link_ovl14_01 **, 0x3C) = links;
    parts++;
    *parts = func_ovl14_01_8004C8F0(-1, 0x500000, parts[-1]);
    (*parts)->unk50 = 0.0f;
    (*parts)->unk54 = 60.0f;
    parts++;
    M2C_FIELD(parts[-1], Link_ovl14_01 **, 0x3C) = links;
    *parts = func_ovl14_01_8004C8F0(0x1C7, 0x01000000, parts[-1]);
    func_ovl14_01_8004C880(parts[-1], *parts, links, 0x150);
    func_ovl14_01_8004C8D0(*parts);
    l = links + 1;
    parts++;
    *parts = func_ovl14_01_8004C8F0(-1, 0, parts[-1]);
    (*parts)->unk50 = 0.0f;
    (*parts)->unk54 = 60.0f;
    func_ovl14_01_8004C880(parts[-1], *parts, l, 0x150);
    l += 1;
    parts++;
    *parts = func_ovl14_01_8004C8F0(id, 0x01008000, parts[-1]);
    (*parts)->unk54 = 420.0f;
    (*parts)->unk50 = 0.0f;
    (*parts)->unk30 = 1;
    (*parts)->unk34 = 160.0f;
    (*parts)->unk38 = 0.0f;
    func_ovl14_01_8004C880(parts[-1], *parts, l, 0x150);
    o = func_ovl14_01_8004C8D0(*parts);
    s = (*parts)->unk34 / 50.0f;
    o->unk54 = s;
    o->unk4C = s;
    func_ovl14_01_80043010(base, links);
    v = D_ovl14_01_8004D4DC;
    parts = base;
    for (i = 0; i < 5; i++) {
        (*parts)->unk40->unk10 = v->x;
        (*parts)->unk40->unk14 = v->y;
        (*parts)->unk40->unk18 = v->z;
        v++;
        parts++;
    }
    ((Vec3f **) &D_ovl14_01_8004D4E0)[-1] = v;
}

void func_ovl14_01_80049618(void) {
    Link_ovl14_01 *l;
    UnkStructA *obj;
    f32 d;
    s32 i;
    Vec3f from;
    Vec3f to;
    Vec3f ang;
    s32 done;
    s32 pad[2];

    if (func_ovl14_01_8004CA10() == (void *) 0x1C8) {
        obj = D_ovl14_01_8004D600[4];
        l = D_ovl14_01_8004D560;
    } else {
        obj = D_ovl14_01_8004D618[4];
        l = D_ovl14_01_8004D5A0;
    }
    from.x = D_ovl14_01_8004D6E0.x;
    from.y = D_ovl14_01_8004D6E0.y;
    from.z = D_ovl14_01_8004D6E0.z;
    to.x = D_ovl14_01_8004D4A0.x;
    to.y = D_ovl14_01_8004D4A0.y + 150.0f;
    to.z = D_ovl14_01_8004D4A0.z;
    func_ovl14_01_8004C828(&from, &to, &ang);
    d = (ang.z - 790.0f) / 14.0f / 3.0f;
    done = 0;
    for (i = 0; i < 14 && func_ovl14_01_80044FDC() == 0; i++) {
        l[0].unk4 += d;
        l[1].unk4 += d;
        l[2].unk4 += d;
        if (done == 0 && func_ovl14_01_8004C860((s32) obj, func_ovl14_01_8004C0D8(func_ovl14_01_8004C078())) != 0) {
            func_ovl14_01_8004C8A0(obj, 0x1E00);
            done = 1;
        }
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800494C8(void) {
    Link_ovl14_01 *l;
    f32 d;
    s32 i;

    if (func_ovl14_01_8004CA10() == (void *) 0x1C8) {
        l = D_ovl14_01_8004D560;
    } else {
        l = D_ovl14_01_8004D5A0;
    }
    d = (790.0f - (l[2].unk4 + (l[1].unk4 + l[0].unk4))) ;
    for (i = 0; i < 30 && func_ovl14_01_80044FDC() == 0; i++) {
        l[0].unk4 += d / 30.0f / 3.0f;
        l[1].unk4 += d / 30.0f / 3.0f;
        l[2].unk4 += d / 30.0f / 3.0f;
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80049368(s32 arg0) {
    Vec3f sp44;
    Vec3f sp38;
    Vec3f sp2C_v;

    sp2C_v.x = D_ovl14_01_8004D690.x;
    sp2C_v.y = D_ovl14_01_8004D690.y;
    sp2C_v.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_800431C4(0xC2, D_ovl14_01_8004D5DC);
    func_ovl14_01_8004C828(&D_ovl14_01_8004D6B0, &D_ovl14_01_8004D690, &sp38);
    sp38.y = WRAP360(sp38.y - 90.0f);
    sp38.y -= 5.0f;
    sp38.z += 200.0f;
    func_ovl14_01_8004C830(&sp38, &sp44);
    sp44.x = sp44.x + D_ovl14_01_8004D6B0.x;
    sp44.y += D_ovl14_01_8004D6B0.y;
    sp44.z += D_ovl14_01_8004D6B0.z;
    func_ovl14_01_80047594(&sp44, 0x1E);
    func_ovl14_01_8004882C();
    func_ovl14_01_80048DE8(arg0);
    func_ovl14_01_800487A8();
    func_ovl14_01_80047594(&sp2C_v, 0x1E);
    D_ovl14_01_8004D690.x = sp2C_v.x;
    D_ovl14_01_8004D690.y = sp2C_v.y;
    D_ovl14_01_8004D690.z = sp2C_v.z;
}

void func_ovl14_01_80048DE8(s32 arg0) {
    f32 ang[3];
    f32 pos[3];
    f32 from[3];
    f32 to[3];
    s32 id;
    s32 r;
    s32 i;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;

    func_ovl14_01_80044B38(&D_ovl14_01_8004D4A0, 10);
    D_ovl14_01_8004D6E0.x = D_ovl14_01_8004D5F4->unk40->unk10;
    D_ovl14_01_8004D6E0.y = D_ovl14_01_8004D5F4->unk40->unk14;
    D_ovl14_01_8004D6E0.z = D_ovl14_01_8004D5F4->unk40->unk18;
    if (func_ovl14_01_8004CBA8(1) != 0) {
        id = 0x1C8;
    } else {
        id = 0x1C9;
    }
    r = 0;
    for (i = 0; i < arg0 && r == 0 && func_ovl14_01_80044FDC() == 0; i++) {
        id = func_ovl14_01_80048D48(id);
        if (id == 0) {
            break;
        }
        func_ovl14_01_800431C4(0xF6, D_ovl14_01_8004D5DC);
        ang[2] = 0.0f;
        ang[1] = 0.0f;
        ang[0] = 0.0f;
        pos[2] = 0.0f;
        pos[1] = 0.0f;
        pos[0] = 0.0f;
        to[1] = D_ovl14_01_8004D4A0.y;
        from[1] = D_ovl14_01_8004D4A0.y;
        to[0] = D_ovl14_01_8004D4A0.x;
        to[2] = D_ovl14_01_8004D4A0.z;
        from[0] = D_ovl14_01_8004D690.x;
        from[2] = D_ovl14_01_8004D690.z;
        func_ovl14_01_8004C828((Vec3f *) from, (Vec3f *) to, (Vec3f *) ang);
        ang[1] = (ang[1] - 90.0 >= 360.0) ? ang[1] - 90.0 - 360.0 : (ang[1] < 90.0) ? ang[1] - 90.0 + 360.0 : ang[1] - 90.0;
        if (id == 0x1C8) {
            ang[0] = (ang[0] + 90.0 >= 360.0) ? ang[0] + 90.0 - 360.0 : (ang[0] + 90.0 < 0.0) ? ang[0] + 90.0 + 360.0 : ang[0] + 90.0;
        } else {
            ang[0] = (ang[0] - 90.0 >= 360.0) ? ang[0] - 90.0 - 360.0 : (ang[0] < 90.0) ? ang[0] - 90.0 + 360.0 : ang[0] - 90.0;
        }
        func_ovl14_01_8004C830((Vec3f *) ang, (Vec3f *) pos);
        pos[0] += D_ovl14_01_8004D690.x;
        pos[1] += D_ovl14_01_8004D690.y;
        pos[2] += D_ovl14_01_8004D690.z;
        func_ovl14_01_80048CE8((Vec3f *) pos, 14);
        if (id == 0x1C8) {
            func_ovl14_01_80048ABC(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        } else {
            func_ovl14_01_80048ABC(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
        }
        func_ovl14_01_8004CA08(10);
        func_ovl14_01_8004C9E8(func_ovl14_01_80049618, (void *) id, 0, 0, 0x150);
        func_ovl14_01_8004CA08(20);
        func_ovl14_01_8004C9E8(func_ovl14_01_800494C8, (void *) id, 0, 0, 0x150);
        func_ovl14_01_80044B38(&D_ovl14_01_8004D4A0, 30);
        D_ovl14_01_8004D6E0.x = D_ovl14_01_8004D5F4->unk40->unk10;
        D_ovl14_01_8004D6E0.y = D_ovl14_01_8004D5F4->unk40->unk14;
        D_ovl14_01_8004D6E0.z = D_ovl14_01_8004D5F4->unk40->unk18;
        func_ovl14_01_80043010(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        func_ovl14_01_80043010(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
        r = func_ovl14_01_80046AE8();
    }
    func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 20);
    if (r == 0 && func_ovl14_01_80044FDC() == 0) {
        func_ovl14_01_8004C9E8(func_ovl14_01_80045474, (void *) 0, 0, 0, 0x110);
        func_ovl14_01_8004C9E8(func_ovl14_01_80045474, (void *) 1, 0, 0, 0x110);
        for (i = 0; i < 240 && r == 0 && func_ovl14_01_80044FDC() == 0; i++) {
            r = func_ovl14_01_80046AE8();
            func_ovl14_01_8004CA30();
        }
    }
    func_ovl14_01_8004697C();
}

void *func_ovl14_01_80048D48(void *arg0) {
    if ((D_ovl14_01_8004D54C == 0) && (D_ovl14_01_8004D550 == 0)) {
        return NULL;
    }
    if ((D_ovl14_01_8004D54C != 0) && (D_ovl14_01_8004D550 != 0)) {
        if (arg0 == (void *)0x1C8) {
            return (void *)0x1C9;
        }
        return (void *)0x1C8;
    }
    if (!(*D_ovl14_01_8004D4E0 & 2)) {
        if (D_ovl14_01_8004D54C != 0) {
            return (void *)0x1C8;
        }
        return (void *)0x1C9;
    }
    return (void *)0x1C8;
}

void func_ovl14_01_80048CE8(Vec3f *arg0, s32 arg1) {
    D_ovl14_01_8004D6D0.x = (f32) arg0->x;
    D_ovl14_01_8004D6D0.y = (f32) arg0->y;
    D_ovl14_01_8004D6D0.z = (f32) arg0->z;
    D_ovl14_01_8004D6DC = arg1;
    func_ovl14_01_8004C9E8(func_ovl14_01_80049B70, NULL, 0, 0, 0x150);
}

void func_ovl14_01_80048ABC(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    s32 pad;
    Vec3f out;
    Vec3f from;
    Vec3f to;
    f32 f;

    arg1->unk0 = 2;
    arg1->unkC = 1.0f;
    arg1->unk10 = 0.0f;
    arg1->unk8 = 0.0f;
    arg1->unk4 = 250.0f;
    arg1++;
    arg1->unk0 = 2;
    arg1->unkC = 1.0f;
    arg1->unk10 = 0.0f;
    arg1->unk8 = 0.0f;
    arg1->unk4 = 60.0f;
    do {} while (0); /* TRICK: a uopt block boundary (no code) */
    arg1++;
    arg1->unk0 = 0x10002;
    arg1->unkC = 1.0f;
    arg1->unk10 = 0.0f;
    arg1->unk8 = 0.0f;
    arg1->unk4 = 420.0f;
    from.x = D_ovl14_01_8004D5F4->unk40->unk10;
    from.y = D_ovl14_01_8004D5F4->unk40->unk14;
    from.z = D_ovl14_01_8004D5F4->unk40->unk18;
    to.x = D_ovl14_01_8004D4A0.x;
    to.y = D_ovl14_01_8004D4A0.y + 150.0f;
    to.z = D_ovl14_01_8004D4A0.z;
    func_ovl14_01_8004C828(&from, &to, &out);
    arg0++;
    func_ovl14_01_8004C8A0(*arg0, 0x500000);
    func_ovl14_01_8004C898(*arg0, 0x300000);
    if (out.y >= 360.0f) {
        (*arg0)->unk50 = out.y - 360.0f;
    } else {
        if (out.y < 0.0f) {
            f = out.y + 360.0f;
        } else {
            f = out.y;
        }
        (*arg0)->unk50 = f;
    }
    (*arg0)->unk4C = out.x;
    arg0 += 2;
    func_ovl14_01_8004C8A0(*arg0, 0x500000);
    (*arg0)->unk50 = 0.0f;
    arg0++;
    func_ovl14_01_8004C8A0(*arg0, 0x30);
    func_ovl14_01_8004C898(*arg0, 0xC00);
    func_ovl14_01_8004C8A0(*arg0, 0x10);
    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        func_ovl14_01_8004C8A0(*arg0, 0x400);
    } else {
        func_ovl14_01_8004C8A0(*arg0, 0x800);
    }
    (*arg0)->unk40->unk28 = 1.0f;
    (*arg0)->unk40->unk2C = 1.0f;
    (*arg0)->unk40->unk30 = 1.0f;
}

void func_ovl14_01_800488B0(void) {
    Vec3f home;
    Vec3f low;
    s32 n;
    s32 m;
    s32 r;

    home.x = D_ovl14_01_8004D690.x;
    home.y = D_ovl14_01_8004D690.y;
    home.z = D_ovl14_01_8004D690.z;
    low.x = home.x;
    low.y = home.y + -300.0f;
    low.z = home.z;
    func_ovl14_01_80047594(&low, 30);
    n = 0;
    if (D_ovl14_01_8004D554 != 0) {
        n = 1;
    }
    if (D_ovl14_01_8004D54C != 0) {
        n++;
    }
    if (D_ovl14_01_8004D550 != 0) {
        n++;
    }
    func_ovl14_01_8004882C();
    func_ovl14_01_80048454();
    func_ovl14_01_800487A8();
    if ((r = func_ovl14_01_80044FDC()) == 0) {
        if (r == m) {} /* TRICK: keeps m off v0 */
        func_ovl14_01_8004CA08(60);
        m = 0;
        if (D_ovl14_01_8004D554 != 0) {
            m = 1;
        }
        if (D_ovl14_01_8004D54C != 0) {
            m++;
        }
        if (D_ovl14_01_8004D550 != 0) {
            m++;
        }
        if (n != m) {
            func_ovl14_01_80047730(30);
            func_ovl14_01_800476F8(home.x, home.z, 30);
            func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 10);
            func_ovl14_01_8004769C(60);
        } else {
            func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 10);
            func_ovl14_01_80047594(&home, 30);
        }
        D_ovl14_01_8004D690.x = home.x;
        D_ovl14_01_8004D690.y = home.y;
        D_ovl14_01_8004D690.z = home.z;
    } else {
        func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 60);
    }
}

void func_ovl14_01_8004882C(void) {
    s32 i;

    func_ovl14_01_8004CC60(0x414);
    for (i = 0; i < 10; i++) {
        D_ovl14_01_8004D684 += 0.05f;
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004CC68(0x414);
}

void func_ovl14_01_800487A8(void) {
    s32 i;

    func_ovl14_01_8004CC60(0x414);
    for (i = 0; i < 10; i++) {
        D_ovl14_01_8004D684 -= 0.05f;
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004CC68(0x414);
}

void func_ovl14_01_80048454(void) {
    f32 sx;
    f32 s;
    f32 t;
    s32 r;
    f32 w;
    Vec3f ang;
    Vec3f out;
    s32 pad;

    func_ovl14_01_80044B38(&D_ovl14_01_8004D4A0, 10);
    func_ovl14_01_80046648(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
    func_ovl14_01_80046648(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
    if (func_ovl14_01_8004CBA8(1) != 0) {
        s = 2.0f;
    } else {
        s = -2.0f;
    }
    if (func_ovl14_01_8004CBA8(1) != 0) {
        sx = 0.5f;
    } else {
        sx = -0.5f;
    }
    if (*D_ovl14_01_8004D4E0 & 2) {
        s = -2.0f;
        sx = -0.5f;
    }
    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        s *= 0.5f;
    }
    func_ovl14_01_8004C828(&D_ovl14_01_8004D518, &D_ovl14_01_8004D690, &ang);
    if (ang.y - 90.0f >= 360.0f) {
        ang.y = ang.y - 90.0f - 360.0f;
    } else {
        if (ang.y < 90.0f) {
            w = ang.y - 90.0f + 360.0f;
        } else {
            w = ang.y - 90.0f;
        }
        ang.y = w;
    }
    D_ovl14_01_8004D4E4 = func_ovl14_01_800431C4(0xF5, D_ovl14_01_8004D5DC);
    r = 0;
    for (t = 0.0f; t < 360.0f && r == 0 && func_ovl14_01_80044FDC() == 0; t += 0.5f) {
        if (D_ovl14_01_8004D6A0.x + s >= 360.0f) {
            D_ovl14_01_8004D6A0.x = D_ovl14_01_8004D6A0.x + s - 360.0f;
        } else {
            if (D_ovl14_01_8004D6A0.x + s < 0.0f) {
                w = D_ovl14_01_8004D6A0.x + s + 360.0f;
            } else {
                w = D_ovl14_01_8004D6A0.x + s;
            }
            D_ovl14_01_8004D6A0.x = w;
        }
        func_ovl14_01_8004C830(&ang, &out);
        D_ovl14_01_8004D690.x = D_ovl14_01_8004D518.x + out.x;
        D_ovl14_01_8004D690.y = D_ovl14_01_8004D518.y + out.y;
        D_ovl14_01_8004D690.z = D_ovl14_01_8004D518.z + out.z;
        ang.x += sx;
        r = func_ovl14_01_80046AE8();
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004CFA0(D_ovl14_01_8004D4E4);
    D_ovl14_01_8004D4E4 = -1;
    func_ovl14_01_8004697C();
    func_ovl14_01_80043010(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
    func_ovl14_01_80043010(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
}

void func_ovl14_01_800481B8(s32 arg0) {
    s32 n;
    s32 k;
    s32 a;
    s32 b;
    s32 lim;

    a = 0;
    b = 0;
    func_ovl14_01_8004C8A0(D_ovl14_01_8004D5F0, 0x400000);
    func_ovl14_01_8004C898(D_ovl14_01_8004D5F0, 0x200000);
    lim = 30;
    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        lim = lim * 1.5f;
    }
    n = 0;
    k = 0;
    while (k < arg0 && a == 0 && b == 0 && D_ovl14_01_8004D548 != 0) {
        D_ovl14_01_8004D5F0->unk40->unk28 = func_ovl14_01_8004CB90((f32) n / (f32) lim * 180.0f) + 1.0f;
        D_ovl14_01_8004D5F0->unk40->unk30 = D_ovl14_01_8004D5F0->unk40->unk28;
        if (lim < n) {
            func_ovl14_01_8004C9E8(func_ovl14_01_80047E44, NULL, 0, 0, 0x110);
            n = 0;
            k++;
            D_ovl14_01_8004D6BC++;
        }
        a = func_ovl14_01_80047344();
        b = func_ovl14_01_80046AE8();
        func_ovl14_01_8004CA30();
        n++;
    }
    D_ovl14_01_8004D5F0->unk40->unk30 = 1.0f;
    D_ovl14_01_8004D5F0->unk40->unk28 = D_ovl14_01_8004D5F0->unk40->unk30;
    func_ovl14_01_8004C8A0(D_ovl14_01_8004D5F0, 0x200000);
    func_ovl14_01_8004C898(D_ovl14_01_8004D5F0, 0x400000);
    while (D_ovl14_01_8004D6BC != 0 && a == 0 && b == 0) {
        a = func_ovl14_01_80047344();
        b = func_ovl14_01_80046AE8();
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004697C();
    if (a != 0 && b == 0) {
        func_ovl14_01_80046CE8();
    }
}

void func_ovl14_01_80047E44(void) {
    UnkStructA *o;
    UnkStructA *s;
    UnkStructA *t;
    Vec3f r;
    Vec3f d;

    o = func_ovl14_01_8004C8C0(0x1B6, 0x01000080, 0x40, NULL);
    o->unk34 = 100.0f;
    o->unk38 = 100.0f;
    s = func_ovl14_01_8004C8C0(0x1B7, 0x480000, 0xD0, o);
    s->unk54 = 5.0f;
    t = func_ovl14_01_8004C8D0(o);
    t->unk4C = t->unk54 = o->unk34 / 50.0f;
    o->unk40->unk10 = D_ovl14_01_8004D5F0->unk40->unk10;
    o->unk40->unk14 = D_ovl14_01_8004D5F0->unk40->unk14 + 100.0f;
    o->unk40->unk18 = D_ovl14_01_8004D5F0->unk40->unk18;
    d.x = o->unk40->unk10;
    d.y = o->unk40->unk14 + 100.0f;
    d.z = o->unk40->unk18;
    func_ovl14_01_8004CE40(14, (f32 *) &d, 0);
    r.x = func_ovl14_01_8004CBA0() * 100.0 * 360.0;
    r.y = 0.0f;
    r.z = func_ovl14_01_8004CBA0() * 100.0 * 6.0;
    func_ovl14_01_8004C830(&r, &d);
    func_ovl14_01_800431C4(0xF9, o);
    o->unk68 = 60.0f;
    for (;;) {
        if (((o->unk40->unk14 <= func_ovl14_01_8004BEC0()) ? 1 : 0) != 0 || o->unk68 == 0.0f) {
            break;
        }
        if (o->unk68 <= o->unk6C && !(s->unk8 & 0x01000000)) {
            o->unk40->unk10 = D_ovl14_01_8004D518.x + d.x;
            o->unk40->unk18 = D_ovl14_01_8004D518.z + d.z;
            func_ovl14_01_8004C898(s, 0x01000000);
        }
        func_ovl14_01_8004C918(o);
        func_ovl14_01_8004C9A8(o);
        func_ovl14_01_8004CA30();
    }
    if (((o->unk40->unk14 <= func_ovl14_01_8004BEC0()) ? 1 : 0) != 0) {
        func_ovl14_01_80047978(o);
    } else {
        func_ovl14_01_800431C4(0xFA, o);
        d.x = o->unk40->unk10;
        d.y = o->unk40->unk14 + 10.0f;
        d.z = o->unk40->unk18;
        func_ovl14_01_8004CE40(10, (f32 *) &d, 0);
    }
    D_ovl14_01_8004D6BC--;
    func_ovl14_01_8004C8B0(o);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80047CDC(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v1;
    f32 temp_fv0;
    f32 var_fv1;
    s32 *temp_s0;

    temp_s0 = func_ovl14_01_8004CA10();
    temp_v0 = func_ovl14_01_8004C8C0(0x116, 0x01200000, 0xD0, D_ovl14_01_8004D5EC);
    temp_v0->unk40->unk30 = 5.0f;
    temp_v1 = temp_v0->unk40;
    var_fv1 = temp_v1->unk30;
    temp_v1->unk2C = var_fv1;
    temp_v0->unk40->unk28 = var_fv1;
    temp_v0->unk50 = 0;
    D_ovl14_01_8004D4E8 = func_ovl14_01_8004CF70(0x107);
    if (*temp_s0 != 0) {
        do {
            temp_v0_2 = temp_v0->unk40;
            temp_fv0 = temp_v0_2->unk20 + 5.0f;
            if (temp_fv0 >= 360.0f) {
                temp_v0_2->unk20 = temp_fv0 - 360.0f;
            } else {
                if (temp_fv0 < 0.0f) {
                    var_fv1 = temp_fv0 + 360.0f;
                } else {
                    var_fv1 = temp_fv0;
                }
                temp_v0_2->unk20 = var_fv1;
            }
            func_ovl14_01_8004CA30();
        } while (*temp_s0 != 0);
    }
    func_ovl14_01_8004CFA0(D_ovl14_01_8004D4E8);
    D_ovl14_01_8004D4E8 = -1;
    func_ovl14_01_8004C8B0(temp_v0);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80047A10(void) {
    UnkStructA *o;
    UnkStructA *s;
    Vec3f d;
    s32 i;
    f32 h;

    o = func_ovl14_01_8004C8C0(0x1C6, 0x01008800, 0x60, NULL);
    o->unk30 = 4;
    o->unk34 = 100.0f;
    o->unk38 = 200.0f;
    s = func_ovl14_01_8004C8D0(o);
    s->unk4C = s->unk54 = o->unk34 / 50.0f;
    h = 50;
    d.x = o->unk40->unk10 = D_ovl14_01_8004D5F0->unk40->unk10;
    d.z = o->unk40->unk18 = D_ovl14_01_8004D5F0->unk40->unk18;
    d.x = (D_ovl14_01_8004D518.x - d.x) / 100;
    d.z = (D_ovl14_01_8004D518.z - d.z) / 100;
    for (i = 0; i < 5; i++) {
        o->unk68 = h;
        if (i >= 3) {
            func_ovl14_01_8004C898(o, 0x40000);
            func_ovl14_01_8004C8A0(o, 0x8810);
        }
        for (;;) {
            if (((o->unk40->unk14 <= func_ovl14_01_8004BEC0()) ? 1 : 0) != 0) {
                i = 5;
                break;
            }
            if (o->unk68 == 0.0f) {
                if (i < 2) {
                    func_ovl14_01_800431C4(0x111, o);
                }
                break;
            }
            o->unk40->unk10 += d.x;
            o->unk40->unk18 += d.z;
            func_ovl14_01_8004C918(o);
            func_ovl14_01_8004CA30();
        }
        d.x *= 0.7f;
        d.z *= 0.7f;
        h *= 0.7f;
    }
    if (((o->unk40->unk14 <= func_ovl14_01_8004BEC0()) ? 1 : 0) != 0) {
        func_ovl14_01_80047978(o);
    } else {
        d.x = o->unk40->unk10;
        d.y = o->unk40->unk14 + 100.0f;
        d.z = o->unk40->unk18;
        func_ovl14_01_8004CE40(15, (f32 *) &d, 0);
    }
    func_ovl14_01_8004C8B0(o);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80047978(UnkStructA *arg0) {
    Vec3f pos;

    pos.x = arg0->unk40->unk10;
    pos.y = arg0->unk40->unk14 + 100.0f;
    pos.z = arg0->unk40->unk18;
    func_ovl14_01_8004C8A0(arg0, 0x01000000);
    func_ovl14_01_8004CE40(7, (f32 *)&pos, 0);
    pos.y += 100.0f;
    func_ovl14_01_8004CE40(0xD, (f32 *)&pos, 0);
    func_ovl14_01_8004CF98(0xB4, (f32 *)&pos);
}

void func_ovl14_01_800477EC(s32 arg0) {
    func_ovl14_01_80047730(0x3C);
    D_ovl14_01_8004D6CC = func_ovl14_01_8004CBA8(7);
    func_ovl14_01_800476F8(D_ovl14_01_8004D6F0[D_ovl14_01_8004D6CC].x, D_ovl14_01_8004D6F0[D_ovl14_01_8004D6CC].z, 0x1E);
    D_ovl14_01_8004D6C8 = D_ovl14_01_8004D6CC;
    func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0x1E);
    func_ovl14_01_80047798(0x1E);
    func_ovl14_01_8004739C(D_ovl14_01_8004D6C4);
    func_ovl14_01_80047730(0x1E);
    D_ovl14_01_8004D6CC = func_ovl14_01_8004CBA8(7);
    func_ovl14_01_800476F8(D_ovl14_01_8004D6F0[D_ovl14_01_8004D6CC].x, D_ovl14_01_8004D6F0[D_ovl14_01_8004D6CC].z, 0x1E);
    D_ovl14_01_8004D6C8 = D_ovl14_01_8004D6CC;
    func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0x1E);
    func_ovl14_01_8004769C(0x3C);
}

void func_ovl14_01_80047798(s32 arg0) {
    Vec3f pos;

    pos.x = D_ovl14_01_8004D690.x;
    pos.y = D_ovl14_01_8004D6F0[0].y - 600.0f;
    pos.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_80047594(&pos, arg0);
}

void func_ovl14_01_80047730(s32 arg0) {
    Vec3f pos;

    pos.x = D_ovl14_01_8004D690.x;
    pos.y = D_ovl14_01_8004D6F0[0].y - 1000.0f;
    pos.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_800431C4(0xFC, D_ovl14_01_8004D5DC);
    func_ovl14_01_80047594(&pos, arg0);
}

void func_ovl14_01_800476F8(f32 arg0, f32 arg1, s32 arg2) {
    Vec3f pos;

    pos.x = arg0;
    pos.z = arg1;
    pos.y = D_ovl14_01_8004D690.y;
    func_ovl14_01_80047594(&pos, arg2);
}

void func_ovl14_01_8004769C(s32 arg0) {
    Vec3f pos;

    pos.x = D_ovl14_01_8004D690.x;
    pos.y = D_ovl14_01_8004D6B0.y;
    pos.z = D_ovl14_01_8004D690.z;
    func_ovl14_01_800431C4(0xFD, D_ovl14_01_8004D5DC);
    func_ovl14_01_80047594(&pos, arg0);
}

void func_ovl14_01_80047594(Vec3f *arg0, s32 arg1) {
    Vec3f sp44;
    Vec3f sp38;
    s32 i;

    func_ovl14_01_8004C828(&D_ovl14_01_8004D690, arg0, &sp38);
    sp38.y = WRAP360(sp38.y - 90.0f);
    sp38.z /= (f32) arg1;
    func_ovl14_01_8004C830(&sp38, &sp44);
    for (i = 0; i < arg1; i++) {
        D_ovl14_01_8004D690.x += sp44.x;
        D_ovl14_01_8004D690.y += sp44.y;
        D_ovl14_01_8004D690.z += sp44.z;
        func_ovl14_01_8004CA30();
    }
}

void func_ovl14_01_8004739C(s32 arg0) {
    s32 n;
    s32 k;
    s32 a;
    s32 b;
    s32 lim;
    static s32 D_ovl14_01_8004D208 = 0;

    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        lim = 100;
    } else {
        lim = 60;
    }
    b = 0;
    n = lim;
    a = 0;
    k = 0;
    while (k < arg0 && a == 0 && b == 0 && ((D_ovl14_01_8004D544 == 0 || D_ovl14_01_8004D548 == 0) ? 1 : 0) == 0) {
        n++;
        if (n > lim) {
            func_ovl14_01_8004C9E8(func_ovl14_01_80045474, (void *) D_ovl14_01_8004D208, 0, 0, 0x110);
            D_ovl14_01_8004D208 ^= 1;
            n = 0;
            k++;
        }
        a = func_ovl14_01_80047344();
        b = func_ovl14_01_80046AE8();
        func_ovl14_01_8004CA30();
    }
    for (n = 0; n < 300 && a == 0 && b == 0 && D_ovl14_01_8004D548 != 0; n++) {
        a = func_ovl14_01_80047344();
        b = func_ovl14_01_80046AE8();
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004697C();
    if (a != 0 && b == 0) {
        func_ovl14_01_80046CE8();
    }
}

s32 func_ovl14_01_80047344(void) {
    s32 flags;

    flags = 0;
    if (D_ovl14_01_8004D554 != 0) {
        flags = D_ovl14_01_8004D5F0->unk10;
    }
    flags |= D_ovl14_01_8004D5E8->unk10;
    if ((flags & 0x2002) == 0x2002) {
        flags = 1;
    } else {
        flags = 0;
    }
    return flags;
}

void func_ovl14_01_80046CE8(void) {
    s32 flag;
    s32 i;
    s32 n;
    s32 r2;
    s32 r3;
    f32 ay;
    f32 y;
    f32 x;
    f32 sy;
    f32 sx;
    f32 ax;
    f32 y0;
    f32 dy;
    f32 w;

    if (func_ovl14_01_80044FDC() == 0) {
        D_ovl14_01_8004D6C0 = 5;
        func_ovl14_01_8004CC60(0x418);
        func_ovl14_01_8004CC60(0x41B);
        flag = 1;
        r3 = 0;
        r2 = 0;
        ax = 0.0f;
        ay = 0.0f;
        sy = 3.0f;
        y = D_ovl14_01_8004D6A0.y;
        x = D_ovl14_01_8004D6A0.x;
        if (func_ovl14_01_8004CBA8(1) != 0) {
            sy *= -1.0f;
        }
        sx = 6.0f;
        if (func_ovl14_01_8004CBA8(1) != 0) {
            sx *= -1.0f;
        }
        y0 = D_ovl14_01_8004D690.y;
        dy = (D_ovl14_01_8004D6B0.y - 230.0f - y0) / 60.0f;
        func_ovl14_01_80043250(0);
        func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
        func_ovl14_01_8004C9E8(func_ovl14_01_80047CDC, &flag, 0, 0, 0x150);
        for (i = 0; i < 60 && r2 == 0 && r3 == 0 && func_ovl14_01_80044FDC() == 0; i++) {
            D_ovl14_01_8004D690.y += dy;
            D_ovl14_01_8004D6A0.y = func_ovl14_01_8004CB90(ay) * 10.0f + y;
            if (ay + sy >= 360.0f) {
                ay = ay + sy - 360.0f;
            } else {
                if (ay + sy < 0.0f) {
                    w = ay + sy + 360.0f;
                } else {
                    w = ay + sy;
                }
                ay = w;
            }
            D_ovl14_01_8004D6A0.x = func_ovl14_01_8004CB90(ax) * 10.0f + x;
            if (ax + sx >= 360.0f) {
                ax = ax + sx - 360.0f;
            } else {
                if (ax + sx < 0.0f) {
                    w = ax + sx + 360.0f;
                } else {
                    w = ax + sx;
                }
                ax = w;
            }
            r3 = func_ovl14_01_80046AE8();
            if (i > 30) {
                r2 = func_ovl14_01_80046C38();
            } else {
                r2 = 0;
            }
            func_ovl14_01_8004CA30();
        }
        n = 300;
        if (func_ovl14_01_8004CC70(0x41F) != 0) {
            n = n * 1.5;
        }
        for (i = 0; i < n && r2 == 0 && r3 == 0 && func_ovl14_01_80044FDC() == 0; i++) {
            D_ovl14_01_8004D6A0.y = func_ovl14_01_8004CB90(ay) * 10.0f + y;
            if (ay + sy >= 360.0f) {
                ay = ay + sy - 360.0f;
            } else {
                if (ay + sy < 0.0f) {
                    w = ay + sy + 360.0f;
                } else {
                    w = ay + sy;
                }
                ay = w;
            }
            D_ovl14_01_8004D6A0.x = func_ovl14_01_8004CB90(ax) * 10.0f + x;
            if (ax + sx >= 360.0f) {
                ax = ax + sx - 360.0f;
            } else {
                if (ax + sx < 0.0f) {
                    w = ax + sx + 360.0f;
                } else {
                    w = ax + sx;
                }
                ax = w;
            }
            r2 = func_ovl14_01_80046C38();
            r3 = func_ovl14_01_80046AE8();
            func_ovl14_01_8004CA30();
        }
        flag = 0;
        i = 0;
        if (D_ovl14_01_8004D548 == 0) {
            func_ovl14_01_8004CA08(60);
        }
        if (r3 != 0) {
            func_ovl14_01_80043250(1);
            func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
            func_ovl14_01_8004697C();
        } else {
            func_ovl14_01_80043250(1);
            func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
        }
        if (r2 != 0 && r3 == 0 && func_ovl14_01_80044FDC() == 0) {
            func_ovl14_01_80046004(r2);
        }
        ay = (y - D_ovl14_01_8004D6A0.y) / 16;
        ax = (x - D_ovl14_01_8004D6A0.x) / 16;
        dy = (y0 - D_ovl14_01_8004D690.y) / 16;
        do {
            D_ovl14_01_8004D6A0.y += ay;
            D_ovl14_01_8004D6A0.x += ax;
            D_ovl14_01_8004D690.y += dy;
            func_ovl14_01_8004CA30();
            i++;
        } while (i != 16);
        D_ovl14_01_8004D690.y = y0;
        D_ovl14_01_8004D6A0.y = y;
        D_ovl14_01_8004D6A0.x = x;
        func_ovl14_01_8004CC68(0x41B);
    }
}

s32 func_ovl14_01_80046C38(void) {
    UnkStructA *obj;
    s32 ret;
    s32 flags;
    Vec3f pos;

    obj = func_ovl14_01_8004C920(D_ovl14_01_8004D5E4, 2);
    if (obj == NULL) {
        return 0;
    }
    flags = obj->unk8;
    if (flags & 0x10000) {
        return 0;
    }
    ret = 1;
    if (flags & 0x2000) {
        ret = 2;
    }
    if (func_ovl14_01_8004CC70(0x417) == 0) {
        func_ovl14_01_8004C968(obj, (f32 *)&pos);
        func_ovl14_01_8004CC18((f32 *)&pos);
    }
    func_ovl14_01_8004CC60(0x417);
    func_ovl14_01_80046B98(obj->unk28, obj->unk40->unk28);
    func_ovl14_01_8004CE60(obj);
    return ret;
}

void func_ovl14_01_80046B98(s32 arg0, f32 arg1) {
    UnkStructA *o;

    D_ovl14_01_8004D5F8 = func_ovl14_01_8004C8C0(arg0, 0x01600000, 0xD0, D_ovl14_01_8004D5E8);
    D_ovl14_01_8004D5F8->unk50 = 550.0f;
    D_ovl14_01_8004D5F8->unk54 = 250.0f;
    D_ovl14_01_8004D5F8->unk40->unk28 = arg1;
    D_ovl14_01_8004D5F8->unk40->unk2C = arg1;
    D_ovl14_01_8004D5F8->unk40->unk30 = arg1;
}

s32 func_ovl14_01_80046AE8(void) {
    func_ovl14_01_8004CC60(0x41A);
    if ((D_ovl14_01_8004D554 <= 0) && (func_ovl14_01_8004CC70(0x41E) == 0)) {
        return 1;
    }
    if ((D_ovl14_01_8004D54C <= 0) && (func_ovl14_01_8004CC70(0x41D) == 0)) {
        return 1;
    }
    if ((D_ovl14_01_8004D550 <= 0) && (func_ovl14_01_8004CC70(0x41C) == 0)) {
        return 1;
    }
    func_ovl14_01_8004CC68(0x41A);
    return 0;
}

void func_ovl14_01_8004697C(void) {
    Vec3f sp34;

    if ((D_ovl14_01_8004D54C <= 0) && (func_ovl14_01_8004CC70(0x41D) == 0)) {
        func_ovl14_01_80045124(D_ovl14_01_8004D600[4]);
        func_ovl14_01_800467C0(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        func_ovl14_01_8004CC60(0x41D);
        func_ovl14_01_8004C968(D_ovl14_01_8004D600[0], (f32 *)&sp34);
        func_ovl14_01_8004CC18((f32 *)&sp34);
    }
    if ((D_ovl14_01_8004D550 <= 0) && (func_ovl14_01_8004CC70(0x41C) == 0)) {
        func_ovl14_01_80045124(D_ovl14_01_8004D618[4]);
        func_ovl14_01_800467C0(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
        func_ovl14_01_8004CC60(0x41C);
        func_ovl14_01_8004C968(D_ovl14_01_8004D618[0], (f32 *)&sp34);
        func_ovl14_01_8004CC18((f32 *)&sp34);
    }
    if (D_ovl14_01_8004D554 <= 0) {
        if (func_ovl14_01_8004CC70(0x41E) == 0) {
            func_ovl14_01_80045124(D_ovl14_01_8004D5F0);
            func_ovl14_01_8004654C();
            func_ovl14_01_8004CC60(0x41E);
            func_ovl14_01_8004C968(D_ovl14_01_8004D5F0, (f32 *)&sp34);
            func_ovl14_01_8004CC18((f32 *)&sp34);
        }
    }
}

void func_ovl14_01_800467C0(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    f32 pad;
    f32 y;
    f32 x;
    f32 d;
    s32 i;
    f32 k;

    y = D_ovl14_01_8004D6A0.y;
    x = D_ovl14_01_8004D6A0.x;
    if (arg1 == D_ovl14_01_8004D560) {
        d = -45.0f;
    } else {
        d = 45.0f;
    }
    d /= 10.0f;
    func_ovl14_01_80046648(arg0, arg1);
    if (*arg0 == D_ovl14_01_8004D600[0]) {
        func_ovl14_01_800431C4(0xFE, D_ovl14_01_8004D600[4]);
    } else {
        func_ovl14_01_800431C4(0xFE, D_ovl14_01_8004D618[4]);
    }
    k = -1.0f; /* TRICK: a propagated local makes uopt fold the store (own lui) */
    for (i = 0; i < 10; i++) {
        D_ovl14_01_8004D6A0.x += d;
        D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.y + k;
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_80043688(arg0, arg1);
    func_ovl14_01_8004CA08(0x1E);
    if (arg1 == D_ovl14_01_8004D560) {
        d = 45.0f;
    } else {
        d = -45.0f;
    }
    d /= 30.0f;
    k = 0.33333334f;
    for (i = 0; i != 30; i++) {
        D_ovl14_01_8004D6A0.x += d;
        D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.y + k;
        func_ovl14_01_8004CA30();
    }
    D_ovl14_01_8004D6A0.y = y;
    D_ovl14_01_8004D6A0.x = x;
}

void func_ovl14_01_80046648(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    Link_ovl14_01 *l = arg1;

    arg1->unk0 = 2;
    arg1->unk10 = 0.9f;
    arg1->unkC = 0.3f;
    arg1->unk8 = 0.0f;
    arg1->unk4 = 250.0f;
    arg1++;
    arg1->unk0 = 2;
    arg1->unk10 = 0.0f;
    arg1->unkC = 1.0f;
    arg1->unk8 = 0.0f;
    arg1->unk4 = 60.0f;
    arg1++;
    arg1->unk0 = 0x10002;
    arg1->unk10 = 0.9f;
    arg1->unkC = 0.3f;
    arg1->unk8 = 0.0f;
    arg1->unk4 = 420.0f;
    arg0++;
    func_ovl14_01_8004C8A0(*arg0, 0x300000);
    func_ovl14_01_8004C898(*arg0, 0x500000);
    (*arg0)->unk50 = 0.0f;
    if (l == D_ovl14_01_8004D560) {
        (*arg0)->unk4C = -90.0f;
    } else {
        (*arg0)->unk4C = 90.0f;
    }
    arg0 += 2;
    func_ovl14_01_8004C8A0(*arg0, 0x500000);
    (*arg0)->unk50 = 0.0f;
    arg0++;
    func_ovl14_01_8004C898(*arg0, 0x30);
    func_ovl14_01_8004C8A0(*arg0, 0xC00);
    (*arg0)->unk40->unk28 = 1.0f;
    (*arg0)->unk40->unk2C = 1.0f;
    (*arg0)->unk40->unk30 = 1.0f;
}

void func_ovl14_01_8004654C(void) {
    f32 pad;
    f32 sp38;
    f32 k;
    s32 var_s0;
    s32 var_s0_2;

    func_ovl14_01_800431C4(0xFE, D_ovl14_01_8004D5F0);
    func_ovl14_01_8004C8A0(D_ovl14_01_8004D5F0, 0x01000000);
    func_ovl14_01_8004C9E8(func_ovl14_01_80047A10, NULL, 0, 0, 0x150);
    var_s0 = 0;
    k = -2.0f; /* TRICK: a propagated local makes uopt fold the store (own lui) */
    sp38 = D_ovl14_01_8004D6A0.y;
    do {
        D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.y + k;
        func_ovl14_01_8004CA30();
        var_s0 += 1;
    } while (var_s0 < 0xA);
    func_ovl14_01_8004CA08(0x1E);
    var_s0 = 0;
    k = 0.6666667f;
    do {
        D_ovl14_01_8004D6A0.y = D_ovl14_01_8004D6A0.y + k;
        func_ovl14_01_8004CA30();
        var_s0 += 1;
    } while (var_s0 != 0x1E);
    D_ovl14_01_8004D6A0.y = sp38;
}

void func_ovl14_01_80046004(s32 arg0) {
    s32 i;
    Vec3f a;
    Vec3f b;
    Vec3f c;
    Vec3f r0;
    Vec3f r1;
    Vec3f r2;
    UnkStructA *o0;
    UnkStructA *o1;
    UnkStructA *o2;
    f32 t;
    f32 ang;
    f32 s;
    f32 h;
    s16 alpha;

    a.x = D_ovl14_01_8004D5DC->unk4C;
    a.y = D_ovl14_01_8004D5DC->unk50;
    a.z = D_ovl14_01_8004D5DC->unk54;
    b.x = D_ovl14_01_8004D5E0->unk4C;
    b.y = D_ovl14_01_8004D5E0->unk50;
    b.z = D_ovl14_01_8004D5E0->unk54;
    c.x = D_ovl14_01_8004D5EC->unk4C;
    c.y = D_ovl14_01_8004D5EC->unk50;
    c.z = D_ovl14_01_8004D5EC->unk54;
    r0.y = 0.0f;
    r0.x = 0.0f;
    r1.y = 0.0f;
    r1.x = 0.0f;
    r2.y = 0.0f;
    r2.x = 0.0f;
    func_ovl14_01_800431F8(D_ovl14_01_8004D5DC);
    func_ovl14_01_8004CA08(30);
    o0 = func_ovl14_01_8004C8C0(0x1CD, 0x01280000, 0xD0, D_ovl14_01_8004D5E8);
    o0->unk50 = 450.0f;
    o1 = func_ovl14_01_8004C8C0(0x1CE, 0x01280000, 0xD0, D_ovl14_01_8004D5DC);
    o1->unk40->unk20 = D_ovl14_01_8004D6A0.x;
    o2 = func_ovl14_01_8004C8C0(0x1CD, 0x01280000, 0xD0, D_ovl14_01_8004D5EC);
    func_ovl14_01_8004CC60(0x414);
    D_ovl14_01_8004D62C = 31.0f;
    D_ovl14_01_8004D630 = 31.0f;
    D_ovl14_01_8004D634 = 31.0f;
    D_ovl14_01_8004D684 = 0.0f;
    D_ovl14_01_8004D638 = 31.0f;
    D_ovl14_01_8004D63C = 31.0f;
    D_ovl14_01_8004D640 = 31.0f;
    D_ovl14_01_8004D688 = 0.0f;
    func_ovl14_01_800431C4(0xFF, D_ovl14_01_8004D5DC);
    for (i = 0; i != 30; i++) {
        D_ovl14_01_8004D5DC->unk50 = func_ovl14_01_8004CB90(r0.y) * 100.0f + a.y;
        D_ovl14_01_8004D5DC->unk54 = func_ovl14_01_8004CB90(r0.x) * -50.0f + a.z;
        D_ovl14_01_8004D5E0->unk50 = func_ovl14_01_8004CB90(r1.y) * 100.0f + b.y;
        D_ovl14_01_8004D5E0->unk54 = func_ovl14_01_8004CB90(r1.x) * -50.0f + b.z;
        D_ovl14_01_8004D5EC->unk50 = func_ovl14_01_8004CB90(r2.y) * 50.0f + c.y;
        D_ovl14_01_8004D5EC->unk54 = func_ovl14_01_8004CB90(r2.x) * -25.0f + c.z;
        t = (f32) i / 30.0f;
        ang = 180.0f * t;
        r0.y = ang;
        r0.x = ang;
        r1.y = ang;
        r1.x = ang;
        r2.y = ang;
        r2.x = ang;
        s = func_ovl14_01_8004CB90(t * 90.0f) + 1.0f;
        o0->unk40->unk28 = s;
        o0->unk40->unk30 = s;
        h = o0->unk40->unk30 * 0.5f;
        o2->unk40->unk28 = h;
        o2->unk40->unk30 = h;
        h = o0->unk40->unk30;
        o1->unk40->unk28 = h;
        o1->unk40->unk30 = h;
        alpha = (1.0f - t) * 255.0f;
        o0->unk40->unk36 = alpha;
        o2->unk40->unk36 = alpha;
        o1->unk40->unk36 = alpha;
        D_ovl14_01_8004D684 = func_ovl14_01_8004CB90(ang);
        D_ovl14_01_8004D688 = D_ovl14_01_8004D684;
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004C8B0(o0);
    func_ovl14_01_8004C8B0(o1);
    func_ovl14_01_8004C8B0(o2);
    func_ovl14_01_8004CC68(0x414);
    D_ovl14_01_8004D62C = 31.0f;
    D_ovl14_01_8004D630 = 31.0f;
    D_ovl14_01_8004D634 = 31.0f;
    D_ovl14_01_8004D684 = 0.0f;
    D_ovl14_01_8004D638 = 0;
    D_ovl14_01_8004D63C = 0;
    D_ovl14_01_8004D640 = 0;
    D_ovl14_01_8004D688 = 0.0f;
    D_ovl14_01_8004D5DC->unk4C = a.x;
    D_ovl14_01_8004D5DC->unk50 = a.y;
    D_ovl14_01_8004D5DC->unk54 = a.z;
    D_ovl14_01_8004D5E0->unk4C = b.x;
    D_ovl14_01_8004D5E0->unk50 = b.y;
    D_ovl14_01_8004D5E0->unk54 = b.z;
    D_ovl14_01_8004D5EC->unk4C = c.x;
    D_ovl14_01_8004D5EC->unk50 = c.y;
    D_ovl14_01_8004D5EC->unk54 = c.z;
    D_ovl14_01_8004D544 -= arg0;
    if (D_ovl14_01_8004D544 < 0) {
        D_ovl14_01_8004D544 = 0;
    }
    func_ovl14_01_8004C8B0(D_ovl14_01_8004D5F8);
    D_ovl14_01_8004D5F8 = NULL;
}

void func_ovl14_01_80045FD8(void) {
    func_ovl14_01_8004C8B0(D_ovl14_01_8004D5F8);
    D_ovl14_01_8004D5F8 = NULL;
}

void func_ovl14_01_80045FA0(void *arg0) {
    func_ovl14_01_8004C9E8(func_ovl14_01_80045474, arg0, 0, 0, 0x110);
}

void func_ovl14_01_80045D7C(void) {
    UnkStructA *obj;
    f32 f;
    f32 sc;
    s32 i;
    void *s;

    s = func_ovl14_01_8004CA10();
    obj = func_ovl14_01_8004C8C0(0xA, 0x480000, 0xD0, D_ovl14_01_8004D5EC);
    if (s == NULL) {
        obj->unk4C = -70.0f;
    } else {
        obj->unk4C = 70.0f;
    }
    obj->unk50 = 35.0f;
    obj->unk54 = 300.0f;
    func_ovl14_01_8004CA30();
    func_ovl14_01_8004C898(obj, 0x01000000);
    func_ovl14_01_8004C8A0(obj, 0x400000);
    obj->unk40->unk36 = 0;
    obj->unk40->unk1C = 90.0f;
    for (i = 0; i < 10; i++) {
        f = (f32) i / 10.0f;
        sc = f * 4.7f + 0.3f;
        obj->unk40->unk30 = sc;
        obj->unk40->unk28 = obj->unk40->unk30;
        obj->unk40->unk36 = f * 255.0f;
        func_ovl14_01_8004CA30();
    }
    for (i = 20; i != 0; i--) {
        sc += 0.05f;
        obj->unk40->unk30 = sc;
        obj->unk40->unk28 = obj->unk40->unk30;
        obj->unk40->unk36 = ((f32) i / 20.0f) * 255.0f;
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004C8B0(obj);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800457F0(void) {
    f32 speed;
    UnkStructA *obj;
    s32 *p;
    f32 opos[3];
    f32 pos[3];
    f32 step[3];
    f32 ang[3];
    s32 n;
    s32 i;
    f32 sp[3];
    f32 w;

    if (func_ovl14_01_8004CC70(0x41F) != 0) {
        speed = 4.0f;
    } else {
        speed = 6.8f;
    }
    n = (s32) func_ovl14_01_8004CA10();
    obj = func_ovl14_01_8004C8C0(0x1CB, 0x480080, 0x40, D_ovl14_01_8004D5EC);
    obj->unk30 = 2;
    obj->unk38 = 100.0f;
    obj->unk34 = 50.0f;
    if (n == 0) {
        p = &D_ovl14_01_8004D4F0;
        obj->unk4C = -70.0f;
    } else {
        p = &D_ovl14_01_8004D4EC;
        obj->unk4C = 70.0f;
    }
    obj->unk54 = 100.0f;
    obj->unk50 = 35.0f;
    pos[0] = D_ovl14_01_8004D4A0.x;
    pos[1] = D_ovl14_01_8004D4A0.y;
    pos[2] = D_ovl14_01_8004D4A0.z;
    func_ovl14_01_8004CA08(3);
    *p = func_ovl14_01_800431C4(0xF8, obj);
    func_ovl14_01_8004C898(obj, 0x01000000);
    func_ovl14_01_8004C8A0(obj, 0x400000);
    func_ovl14_01_8004C968(obj, (Vec3f *) opos);
    func_ovl14_01_8004C828((Vec3f *) opos, (Vec3f *) pos, (Vec3f *) ang);
    ang[1] = ((ang[1] - 180.0f >= 360.0f) ? ang[1] - 180.0f - 360.0f : (ang[1] < 180.0f) ? ang[1] - 180.0f + 360.0f : ang[1] - 180.0f) * -1.0f;
    n = 0;
    obj->unk40->unk20 = ang[0];
    obj->unk40->unk1C = ang[1];
    for (i = 0; i < 10; i++) {
        if (func_ovl14_01_8004CC70(0x41B) != 0 || func_ovl14_01_8004CC70(0x41A) != 0 || D_ovl14_01_8004D548 == 0) {
            func_ovl14_01_8004CFA0(*p);
            *p = -1;
            func_ovl14_01_8004C8B0(obj);
            func_ovl14_01_8004C9F8();
        }
        obj->unk40->unk36 = (f32) i / 10.0f * 255.0f;
        obj->unk40->unk2C += 1.0f;
        if (ang[2] * 0.01f < obj->unk40->unk2C) {
            obj->unk40->unk2C = ang[2] * 0.01f;
            if (n >= 5) {
                sp[0] = pos[0];
                sp[1] = pos[1] + 50.0f;
                sp[2] = pos[2];
                func_ovl14_01_8004CE40(7, sp, 0);
                n = 0;
            }
            n++;
        }
        func_ovl14_01_8004C9A8(obj);
        func_ovl14_01_8004CA30();
    }
    n = 0;
    for (i = 0; i != 40; i++) {
        if (func_ovl14_01_8004CC70(0x41B) != 0 || func_ovl14_01_8004CC70(0x41A) != 0 || D_ovl14_01_8004D548 == 0) {
            break;
        }
        func_ovl14_01_8004C828((Vec3f *) pos, &D_ovl14_01_8004D4A0, (Vec3f *) ang);
        if (ang[1] - 90.0f >= 360.0f) {
            ang[1] = ang[1] - 90.0f - 360.0f;
        } else {
            if (ang[1] < 90.0f) {
                w = ang[1] - 90.0f + 360.0f;
            } else {
                w = ang[1] - 90.0f;
            }
            ang[1] = w;
        }
        if (speed < ang[2]) {
            ang[2] = speed;
        }
        func_ovl14_01_8004C830((Vec3f *) ang, (Vec3f *) step);
        pos[0] += step[0];
        pos[1] += step[1];
        pos[2] += step[2];
        func_ovl14_01_8004C968(obj, (Vec3f *) opos);
        func_ovl14_01_8004C828((Vec3f *) opos, (Vec3f *) pos, (Vec3f *) ang);
        ang[1] = ((ang[1] - 180.0f >= 360.0f) ? ang[1] - 180.0f - 360.0f : (ang[1] < 180.0f) ? ang[1] - 180.0f + 360.0f : ang[1] - 180.0f) * -1.0f;
        obj->unk40->unk20 = ang[0];
        obj->unk40->unk1C = ang[1];
        obj->unk40->unk2C = ang[2] * 0.01f;
        if (n >= 5) {
            n = 0;
            sp[0] = pos[0];
            sp[1] = pos[1] + 50.0f;
            sp[2] = pos[2];
            func_ovl14_01_8004CE40(7, sp, 0);
        }
        n++;
        func_ovl14_01_8004C9A8(obj);
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004CFA0(*p);
    *p = -1;
    func_ovl14_01_8004C8B0(obj);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800455AC(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    f32 temp_fv0;
    s32 var_s0;
    void *temp_s0;

    temp_s0 = func_ovl14_01_8004CA10();
    temp_v0 = func_ovl14_01_8004C8C0(0x1CB, 0x480000, 0xD0, D_ovl14_01_8004D5EC);
    if (temp_s0 == NULL) {
        temp_v0->unk4C = -70.0f;
    } else {
        temp_v0->unk4C = 70.0f;
    }
    temp_v0->unk50 = 35.0f;
    temp_v0->unk54 = 150.0f;
    func_ovl14_01_8004CA08(1);
    temp_v0->unk40->unk28 = 0.25f;
    temp_v0->unk40->unk2C = 7.0f;
    temp_v0->unk40->unk30 = 0.25f;
    temp_v0->unk40->unk1C = (f32) ((func_ovl14_01_8004CBA0() * 120.0) + 30.0);
    temp_v0->unk40->unk20 += func_ovl14_01_8004CBA0() * 120.0 - 60.0;
    func_ovl14_01_8004C898(temp_v0, 0x01000000);
    func_ovl14_01_8004C8A0(temp_v0, 0x400000);
    var_s0 = 0;
loop_4:
    if ((func_ovl14_01_8004CC70(0x41B) == 0) && (func_ovl14_01_8004CC70(0x41A) == 0)) {
        temp_fv0 = (f32) var_s0 / 30.0f;
        temp_v0->unk40->unk2C = ((1.0f - temp_fv0) * 7.0f) + 0.1f;
        temp_v0->unk40->unk36 = (s16) (s32) (temp_fv0 * 255.0f);
        func_ovl14_01_8004CA30();
        var_s0 += 1;
        if (var_s0 != 0x1E) {
            goto loop_4;
        }
    }
    func_ovl14_01_8004C8B0(temp_v0);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80045474(void) {
    s32 j;
    s32 i;
    void *obj;

    obj = func_ovl14_01_8004CA10();
    func_ovl14_01_800431C4(0xF7, D_ovl14_01_8004D5EC);
    j = 4;
    for (i = 0; i < 90; i++) {
        if ((D_ovl14_01_8004D548 == 0) || (func_ovl14_01_8004CC70(0x41B) != 0) || (func_ovl14_01_8004CC70(0x41A) != 0)) {
            func_ovl14_01_8004C9F8();
        }
        if (++j >= 5) {
            func_ovl14_01_8004C9E8(func_ovl14_01_800455AC, obj, 0, 0, 0x150);
            j = 0;
        }
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004C9E8(func_ovl14_01_80045D7C, obj, 0, 0, 0x150);
    func_ovl14_01_8004C9E8(func_ovl14_01_800457F0, obj, 0, 0, 0x110);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_8004515C(void) {
    f32 by;
    f32 t1;
    f32 t2;
    f32 w;
    s32 n;
    f32 bx;
    s32 i;

    D_ovl14_01_8004D6C0 = 9;
    func_ovl14_01_80043250(0);
    func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
    func_ovl14_01_8004CC60(0x419);
    func_ovl14_01_8004CC60(0x414);
    by = D_ovl14_01_8004D6A0.y;
    bx = D_ovl14_01_8004D6A0.x;
    D_ovl14_01_8004D554 = D_ovl14_01_8004D548 = D_ovl14_01_8004D54C = D_ovl14_01_8004D550 = 0;
    n = 0x78;
    t1 = 0.0f;
    t2 = 0.0f;
    func_ovl14_01_800431C4(0x100, D_ovl14_01_8004D5E8);
    for (i = 0; i < 600; i++) {
        if (D_ovl14_01_8004D688 + 0.01f < 1.0f) {
            D_ovl14_01_8004D688 += 0.01f;
        } else {
            func_ovl14_01_8004CC68(0x414);
        }
        D_ovl14_01_8004D690.y += -1.6666666f;
        D_ovl14_01_8004D6A0.y = func_ovl14_01_8004CB90(t2) * 10.0f + by;
        if (t2 + 4.0f >= 360.0f) {
            t2 = t2 + 4.0f - 360.0f;
        } else {
            if (t2 + 4.0f < 0.0f) {
                w = t2 + 4.0f + 360.0f;
            } else {
                w = t2 + 4.0f;
            }
            t2 = w;
        }
        D_ovl14_01_8004D6A0.x = func_ovl14_01_8004CB90(t1) * 10.0f + bx;
        if (t1 + 10.0f >= 360.0f) {
            t1 = t1 + 10.0f - 360.0f;
        } else {
            if (t1 + 10.0f < 0.0f) {
                w = t1 + 10.0f + 360.0f;
            } else {
                w = t1 + 10.0f;
            }
            t1 = w;
        }
        n++;
        if (n > 120) {
            func_ovl14_01_80045124(D_ovl14_01_8004D5F0);
            func_ovl14_01_80045124(D_ovl14_01_8004D618[4]);
            func_ovl14_01_80045124(D_ovl14_01_8004D600[4]);
            func_ovl14_01_80045124(D_ovl14_01_8004D5E8);
            n = 0;
        }
        func_ovl14_01_8004CA30();
    }
}

void func_ovl14_01_80045124(void *arg0) {
    func_ovl14_01_8004C9E8(func_ovl14_01_8004A4E0, arg0, 0, 0, 0x150);
}

void func_ovl14_01_80045010(void) {
    s32 v;

    if (D_ovl14_01_8004D544 == 0 || D_ovl14_01_8004D548 == 0) {
        v = 1;
    } else {
        v = 0;
    }
    if (v == 0) {
        if (func_ovl14_01_8004CBA8(1) != 0) {
            D_ovl14_01_8004D6CC = D_ovl14_01_8004D6C8 + 1;
        } else {
            D_ovl14_01_8004D6CC = D_ovl14_01_8004D6C8 - 1;
        }
        if (*D_ovl14_01_8004D4E0 & 2) {
            D_ovl14_01_8004D6CC = D_ovl14_01_8004D6C8 - 1;
        }
        if (D_ovl14_01_8004D6CC < 0) {
            D_ovl14_01_8004D6CC += 8;
        }
        if (D_ovl14_01_8004D6CC >= 8) {
            D_ovl14_01_8004D6CC -= 8;
        }
        func_ovl14_01_80044D50(&D_ovl14_01_8004D6F0[D_ovl14_01_8004D6CC], 8.5f);
        D_ovl14_01_8004D6C8 = D_ovl14_01_8004D6CC;
        func_ovl14_01_80044B38(&D_ovl14_01_8004D518, 0x1E);
    }
}

s32 func_ovl14_01_80044FDC(void) {
    if ((D_ovl14_01_8004D544 == 0) || (D_ovl14_01_8004D548 == 0)) {
        return 1;
    }
    return 0;
}

void func_ovl14_01_80044D50(Vec3f *arg0, f32 arg1) {
    Vec3f a;
    Vec3f v;
    f32 t;
    f32 dist;
    f32 n;
    s32 flag;
    f32 base;
    f32 w;

    func_ovl14_01_8004C828(&D_ovl14_01_8004D690, arg0, &a);
    dist = a.z;
    func_ovl14_01_80044B38(arg0, 0x14);
    flag = 1;
    func_ovl14_01_8004C9E8(func_ovl14_01_800449C0, &flag, 0, 0, 0x150);
    t = 0.0f;
    n = 0.0f;
    base = D_ovl14_01_8004D6A0.x;
    for (n = 0.0f; n <= dist; n += arg1) {
        func_ovl14_01_8004C828(&D_ovl14_01_8004D690, arg0, &a);
        if (a.y - 90.0f >= 360.0f) {
            a.y = a.y - 90.0f - 360.0f;
        } else {
            if (a.y < 90.0f) {
                w = a.y - 90.0f + 360.0f;
            } else {
                w = a.y - 90.0f;
            }
            a.y = w;
        }
        if (a.z > arg1) {
            a.z = arg1;
        }
        func_ovl14_01_8004C830(&a, &v);
        D_ovl14_01_8004D690.x += v.x;
        D_ovl14_01_8004D690.z += v.z;
        D_ovl14_01_8004D6A0.x = func_ovl14_01_8004CB90(t) * 20.0f + base;
        if (t + 6.0f >= 360.0f) {
            t = t + 6.0f - 360.0f;
        } else {
            if (t + 6.0f < 0.0f) {
                w = t + 6.0f + 360.0f;
            } else {
                w = t + 6.0f;
            }
            t = w;
        }
        func_ovl14_01_8004CA30();
    }
    flag = 0;
    D_ovl14_01_8004D690.x = arg0->x;
    D_ovl14_01_8004D690.z = arg0->z;
    do {
        func_ovl14_01_8004CA30();
    } while (flag != -1);
}

void func_ovl14_01_80044B38(Vec3f *arg0, s32 arg1) {
    Vec3f a;
    f32 cur;
    f32 tgt;
    f32 d;
    f32 w;
    s32 i;

    if (D_ovl14_01_8004D6A0.x >= 360.0f) {
        D_ovl14_01_8004D6A0.x -= 360.0f;
    } else {
        if (D_ovl14_01_8004D6A0.x < 0.0f) {
            w = D_ovl14_01_8004D6A0.x + 360.0f;
        } else {
            w = D_ovl14_01_8004D6A0.x;
        }
        D_ovl14_01_8004D6A0.x = w;
    }
    a.x = a.y = a.z = 0.0f;
    func_ovl14_01_8004C828(&D_ovl14_01_8004D690, arg0, &a);
    if (a.x >= 0.0f && a.x <= 180.0f) {
        tgt = a.x;
    } else {
        tgt = (360.0f - a.x) * -1.0f;
    }
    if (D_ovl14_01_8004D6A0.x >= 0.0f && D_ovl14_01_8004D6A0.x <= 180.0f) {
        cur = D_ovl14_01_8004D6A0.x;
    } else {
        cur = (360.0f - D_ovl14_01_8004D6A0.x) * -1.0f;
    }
    d = tgt - cur;
    if (d >= 180.0f) {
        d -= 360.0f;
    }
    if (d < -180.0f) {
        d += 360.0f;
    }
    d /= arg1;
    for (i = 0; i < arg1; i++) {
        D_ovl14_01_8004D6A0.x += d;
        if (D_ovl14_01_8004D6A0.x >= 360.0f) {
            D_ovl14_01_8004D6A0.x -= 360.0f;
        } else {
            if (D_ovl14_01_8004D6A0.x < 0.0f) {
                w = D_ovl14_01_8004D6A0.x + 360.0f;
            } else {
                w = D_ovl14_01_8004D6A0.x;
            }
            D_ovl14_01_8004D6A0.x = w;
        }
        func_ovl14_01_8004CA30();
    }
}

void func_ovl14_01_800449C0(void) {
    s32 *s;
    f32 y;
    f32 t;

    s = func_ovl14_01_8004CA10();
    t = 0.0f;
    y = D_ovl14_01_8004D690.y;
    func_ovl14_01_800431C4(0xFB, D_ovl14_01_8004D5E8);
    for (;;) {
        D_ovl14_01_8004D690.y = func_ovl14_01_8004CB90(t) * 50.0f + y;
        t = WRAP360(t + 6.0f);
        if (t > 180.0f) {
            func_ovl14_01_800431C4(0xFB, D_ovl14_01_8004D5E8);
            D_ovl14_01_8004D690.y = y;
            t -= 180.0f;
            if (*s == 0) {
                break;
            }
        }
        func_ovl14_01_8004CA30();
    }
    *s = -1;
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800445D8(void) {
    Vec3f ang;
    f32 w;
    f32 cur;
    f32 tmp;
    f32 a;
    f32 b;
    f32 d;
    s32 neg;

    if (func_ovl14_01_8004CC70(0x413) != 0) {
        if (func_ovl14_01_8004CC70(0x415) != 0) {
            if (D_ovl14_01_8004D4F8.x >= 360.0f) {
                D_ovl14_01_8004D4F8.x = D_ovl14_01_8004D4F8.x - 360.0f;
            } else {
                if (D_ovl14_01_8004D4F8.x < 0.0f) {
                    w = D_ovl14_01_8004D4F8.x + 360.0f;
                } else {
                    w = D_ovl14_01_8004D4F8.x;
                }
                D_ovl14_01_8004D4F8.x = w;
            }
            if (D_ovl14_01_8004D4F8.y >= 360.0f) {
                D_ovl14_01_8004D4F8.y = D_ovl14_01_8004D4F8.y - 360.0f;
            } else {
                if (D_ovl14_01_8004D4F8.y < 0.0f) {
                    w = D_ovl14_01_8004D4F8.y + 360.0f;
                } else {
                    w = D_ovl14_01_8004D4F8.y;
                }
                D_ovl14_01_8004D4F8.y = w;
            }
            func_ovl14_01_8004C828(&D_ovl14_01_8004D690, &D_ovl14_01_8004D518, &ang);
            if (ang.y - 90.0f >= 360.0f) {
                ang.y = ang.y - 90.0f - 360.0f;
            } else {
                if (ang.y < 90.0f) {
                    w = ang.y - 90.0f + 360.0f;
                } else {
                    w = ang.y - 90.0f;
                }
                ang.y = w;
            }
            func_ovl14_01_8004C700(&cur, NULL, &tmp);
            a = (ang.x >= 0.0f && ang.x <= 180.0f) ? ang.x : (360.0f - ang.x) * -1.0f;
            w = (cur >= 0.0f && cur <= 180.0f) ? cur : (360.0f - cur) * -1.0f;
            d = a - w;
            neg = 0;
            if (d > 180.0f) {
                d -= 360.0f;
            }
            if (d < -180.0f) {
                d += 360.0f;
            }
            if (d < 0.0) {
                neg = 1;
                d *= -1.0f;
            }
            if (d > 5.0f) {
                d = 5.0f;
            }
            if (neg != 0) {
                d *= -1.0f;
            }
            D_ovl14_01_8004D4F8.x = cur + d;
            switch (D_ovl14_01_8004D6C0) {
                case 2:
                case 4:
                    if (D_ovl14_01_8004D4F8.y > 8.0f) {
                        D_ovl14_01_8004D4F8.y -= 1.0f;
                    }
                    break;
                case 1:
                    if (D_ovl14_01_8004D4F8.y < 50.0f) {
                        D_ovl14_01_8004D4F8.y += 1.0f;
                    }
                    break;
                default:
                case 3:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    if (D_ovl14_01_8004D4F8.y < 24.0f || D_ovl14_01_8004D4F8.y > 26.0f) {
                        if (D_ovl14_01_8004D4F8.y > 25.0f) {
                            D_ovl14_01_8004D4F8.y -= 1.0f;
                        } else {
                            D_ovl14_01_8004D4F8.y += 1.0f;
                        }
                    }
                    break;
            }
            func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
            func_ovl14_01_8004C6F8(D_ovl14_01_8004D4F8.x, 32768.0f, D_ovl14_01_8004D4F8.z);
        }
    }
}

void func_ovl14_01_80044540(Vec3f *arg0) {
    Vec3f sp1C;

    arg0->y = 0.0f;
    arg0->z *= 0.75f;
    func_ovl14_01_8004C830(arg0, &sp1C);
    func_ovl14_01_8004C788(D_ovl14_01_8004D690.x + sp1C.x, D_ovl14_01_8004D690.z + sp1C.z, 100.0f, 110.0f);
    func_ovl14_01_8004C798(D_ovl14_01_8004D690.x + sp1C.x, D_ovl14_01_8004D690.z + sp1C.z, D_ovl14_01_8004D690.x + sp1C.x, D_ovl14_01_8004D690.z + sp1C.z);
}

void func_ovl14_01_80044104(void) {
    s32 i;

    if (func_ovl14_01_8004CC70(0x414) != 0) {
        D_ovl14_01_8004D644 = func_ovl14_01_8004D000(D_ovl14_01_8004D5DC->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
        D_ovl14_01_8004D64C = func_ovl14_01_8004D000(D_ovl14_01_8004D5F0->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
        D_ovl14_01_8004D648 = func_ovl14_01_8004D000(D_ovl14_01_8004D5E8->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
        for (i = 0; i < 5; i++) {
            if (D_ovl14_01_8004D600[i]->unk28 != -1) {
                D_ovl14_01_8004D658[i] = func_ovl14_01_8004D000(D_ovl14_01_8004D600[i]->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
            }
        }
        for (i = 0; i < 5; i++) {
            if (D_ovl14_01_8004D618[i]->unk28 != -1) {
                D_ovl14_01_8004D670[i] = func_ovl14_01_8004D000(D_ovl14_01_8004D618[i]->unk40, D_ovl14_01_8004D62C, D_ovl14_01_8004D630, D_ovl14_01_8004D634, D_ovl14_01_8004D684);
            }
        }
        D_ovl14_01_8004D650 = func_ovl14_01_8004D000(D_ovl14_01_8004D5EC->unk40, D_ovl14_01_8004D638, D_ovl14_01_8004D63C, D_ovl14_01_8004D640, D_ovl14_01_8004D688);
    }
}

void func_ovl14_01_80043F10(void) {
    UnkStructA *temp_s1;
    f32 var_fs0;
    f32 var_fs1;
    Vec3f sp70;
    f32 var_fs2;
    f32 var_fs3;
    s32 var_s0;
    void *temp_s0;

    D_ovl14_01_8004D540 += 1;
    temp_s0 = func_ovl14_01_8004CA10();
    temp_s1 = func_ovl14_01_8004C8C0(0x1CC, 0x11280000, 0xD0, D_ovl14_01_8004D5E8);
    func_ovl14_01_8004C828((Vec3f *) &D_ovl14_01_8004D5E8->unk58, &D_ovl14_01_8004D690, &sp70);
    var_fs0 = 0.0f;
    var_fs1 = 500.0f;
    var_fs2 = 0.1f;
    var_fs3 = 0.2f;
    if (temp_s0 == NULL) {
        var_fs2 *= -1.0f;
        var_fs3 *= -1.0f;
    }
    var_s0 = 0;
    do {
        temp_s1->unk4C = func_ovl14_01_8004CB90(sp70.x + var_fs0) * var_fs1;
        temp_s1->unk50 = func_ovl14_01_8004BEC0() - D_ovl14_01_8004D5E8->unk40->unk14;
        temp_s1->unk54 = func_ovl14_01_8004CB98(sp70.x + var_fs0) * var_fs1;
        var_fs0 += var_fs2;
        var_fs2 += var_fs3;
        var_fs1 -= 4.0f;
        func_ovl14_01_80043CC0(temp_s1, var_s0, 0x1E, 1.0f, 1.75f);
        func_ovl14_01_8004CA30();
        var_s0 += 1;
    } while (var_s0 != 0x28);
    D_ovl14_01_8004D540 -= 1;
    func_ovl14_01_8004C8B0(temp_s1);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80043D98(void) {
    UnkStructA *o;
    f32 y;
    Vec3f vel;
    Vec3f dir;
    s32 i;

    D_ovl14_01_8004D540 += 1;
    o = func_ovl14_01_8004C8C0(0x1CC, 0x11080000, 0xD0, NULL);
    dir.x = func_ovl14_01_8004CBA8(0x23) * 10.0f;
    dir.y = 0.0f;
    dir.z = 500.0f;
    y = func_ovl14_01_8004BEC0();
    func_ovl14_01_8004C830(&dir, &vel);
    o->unk40->unk10 = D_ovl14_01_8004D5E8->unk40->unk10 + vel.x;
    o->unk40->unk14 = vel.y + y;
    o->unk40->unk18 = D_ovl14_01_8004D5E8->unk40->unk18 + vel.z;
    for (i = 0; i < 40; i++) {
        func_ovl14_01_80043CC0(o, i, 0x1E, 1.0f, 1.75f);
        func_ovl14_01_8004CA30();
    }
    D_ovl14_01_8004D540 -= 1;
    func_ovl14_01_8004C8B0(o);
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_80043CC0(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl14_01_8004CB90(((f32) arg1 / (f32) arg2) * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl14_01_8004CB90(((f32) arg1 / (f32) arg2) * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - ((f32) arg1 / (f32) arg2)) * 193.0f) + 0x40;
}

void func_ovl14_01_80043B20(void) {
    s32 n;
    void *arg;

    arg = NULL;
    n = 0x8000;
    for (;;) {
        n++;
        if (D_ovl14_01_8004D540 < 12) {
            if ((D_ovl14_01_8004D5E8->unk40->unk10 != D_ovl14_01_8004D5E8->unk58 || D_ovl14_01_8004D5E8->unk40->unk18 != D_ovl14_01_8004D5E8->unk60) && func_ovl14_01_8004BEC0() < D_ovl14_01_8004D690.y + 1100.0f) {
                if (n >= 7) {
                    func_ovl14_01_8004C9E8(func_ovl14_01_80043F10, arg, 0, 0, 0x150);
                    arg = (void *) ((s32) arg ^ 1);
                    n = 0;
                }
            } else if (D_ovl14_01_8004D5E8->unk40->unk14 != D_ovl14_01_8004D5E8->unk5C && n >= 5) {
                func_ovl14_01_8004C9E8(func_ovl14_01_80043D98, NULL, 0, 0, 0x150);
                n = 0;
            }
        }
        func_ovl14_01_8004CA30();
    }
}

void func_ovl14_01_800439AC(Vec3f *arg0, UnkStructA *arg1) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    f32 temp_fv0;

    if (D_ovl14_01_8004D53C < 0x11) {
        temp_v0 = func_ovl14_01_8004C8C0(0x1CF, 0x01000000, 0xD0, arg1);
        if (arg1 == NULL) {
            temp_v0->unk40->unk10 = arg0->x;
            temp_v0->unk40->unk14 = arg0->y;
            temp_v0->unk40->unk18 = arg0->z;
        } else {
            func_ovl14_01_8004C898(temp_v0, 0x200000);
            temp_v0->unk4C = arg0->x;
            temp_v0->unk50 = arg0->y;
            temp_v0->unk54 = arg0->z;
        }
        temp_v0->unk40->unk36 = 0xFF;
        temp_v0->unk40->unk30 = 2.0f;
        temp_v0_2 = temp_v0->unk40;
        temp_fv0 = temp_v0_2->unk30;
        temp_v0_2->unk2C = temp_fv0;
        temp_v0->unk40->unk28 = temp_fv0;
        func_ovl14_01_8004C5A0(temp_v0->unk40, 2);
        func_ovl14_01_8004C5A8(temp_v0->unk40, 0x1D0, 0, 0);
        func_ovl14_01_8004C5A8(temp_v0->unk40, 0x1D0, 1, 1);
        func_ovl14_01_8004C9E8(func_ovl14_01_800438D8, temp_v0, 0, 0, 0x150);
        D_ovl14_01_8004D53C += 1;
    }
}

void func_ovl14_01_800438D8(void) {
    UnkStructA *o;
    f32 f;
    s32 i;

    o = func_ovl14_01_8004CA10();
    f = 0.0f;
    for (i = 0; i < 16; i++) {
        func_ovl14_01_8004C5A8(o->unk40, 0x1D0, 0, (s32) f * 2);
        f += 0.25f;
        func_ovl14_01_8004CA30();
    }
    func_ovl14_01_8004C8B0(o);
    D_ovl14_01_8004D53C--;
    func_ovl14_01_8004C9F8();
}

void func_ovl14_01_800437B8(void) {
    UnkStructA *temp_s0;

    if (func_ovl14_01_8004CC70(0x400) == 0) {
        func_ovl14_01_8004CCE8(0, 0, 0, 100.0f);
        D_ovl14_01_8004D688 = 1.0f;
        func_ovl14_01_80043688(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        func_ovl14_01_80043688(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
/* TRICK: alternating #line files end as1 scheduling blocks */
#line 3150 "x.c"
        func_ovl14_01_80043250(0);
#line 3151 "y.c"
        temp_s0 = D_ovl14_01_8004D5DC;
#line 3152 "x.c"
        temp_s0->unk40->unk48->unk4->unk4 = func_ovl14_01_8004C5D8(temp_s0->unk40, 0) - 0.001f;
#line 3153 "y.c"
        func_ovl14_01_8004CC60(0x414);
        D_ovl14_01_8004D4F8.y = 8.0f;
        func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
        func_ovl14_01_8004C6F8(0.0f, D_ovl14_01_8004D4F8.y, 2500.0f);
        D_ovl14_01_8004D4F8.y = -10.0f;
        func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
        func_ovl14_01_8004C6F8(0.0f, D_ovl14_01_8004D4F8.y, 1300.0f);
    }
}

static void func_ovl14_01_80043680() {
}

void func_ovl14_01_80043688(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    func_ovl14_01_80043680();
    arg1->unk0 = 1;
    arg1->unk10 = 0.9f;
    arg1->unkC = 0.1f;
    arg1->unk8 = 0.5f;
    arg1->unk4 = 250.0f;
    arg1++;
    arg1->unk0 = 1;
    arg1->unk10 = 0.9f;
    arg1->unkC = 0.1f;
    arg1->unk8 = 0.5f;
    arg1->unk4 = 60.0f;
    arg1++;
    arg1->unk0 = 1;
    arg1->unk10 = 0.9f;
    arg1->unkC = 0.1f;
    arg1->unk8 = 0.5f;
    arg1->unk4 = 420.0f;
    arg0++;
    func_ovl14_01_8004C8A0(*arg0, 0xF00000);
    func_ovl14_01_8004C898(*arg0, 0x500000);
    (*arg0)->unk50 = -90.0f;
    (*arg0)->unk54 = 60.0f;
    arg0 += 2;
    func_ovl14_01_8004C8A0(*arg0, 0xF00000);
    func_ovl14_01_8004C898(*arg0, 0x500000);
    (*arg0)->unk50 = -90.0f;
    (*arg0)->unk4C = 0;
    arg0++;
    func_ovl14_01_8004C8A0(*arg0, 0xF00C30);
    (*arg0)->unk40->unk1C = 90.0f;
}

void func_ovl14_01_80043624(void) {
    if (!(*D_ovl14_01_8004D4E0 & 2)) {
        if (func_ovl14_01_8004CC50(0xA4) == 0) {
            func_ovl14_01_8004CA08(0x28);
        }
        func_ovl14_01_8004CF80(0x2A);
    }
    func_ovl14_01_8004C9F8();
}

s32 func_ovl14_01_800431C4(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *temp_v0;

    temp_v0 = arg1->unk40;
    return func_ovl14_01_8004CF90(arg0, temp_v0->unk10, temp_v0->unk14, temp_v0->unk18);
}

void func_ovl14_01_80043250(s32 arg0) {
    func_ovl14_01_8004C5C0(D_ovl14_01_8004D5DC->unk40, arg0, 0);
    D_ovl14_01_8004D558 = (s32) (func_ovl14_01_8004C5D8(D_ovl14_01_8004D5DC->unk40, 0) - 0.001f);
    func_ovl14_01_8004C8A0(D_ovl14_01_8004D5DC, 0x04000000);
}

void func_ovl14_01_800432D8(void) {
    s32 i;
    s32 c;
    f32 y;
    f32 sdz;
    f32 dz;
    f32 dy;
    f32 pad;
    Vec3f a;
    f32 dy0;
    f32 sdy;

    if (func_ovl14_01_8004CC70(0x400) == 0) {
        func_ovl14_01_8004C9E8(func_ovl14_01_80043624, NULL, 0, 0, 0x150);
        for (i = 0; i < 120; i++) {
            if (pad == 100.0f) {} /* TRICK: 100.0 seen first (f20) */
            do {} while (0); /* TRICK: uopt block boundary */
            func_ovl14_01_8004CA30();
            func_ovl14_01_8004CCE8(0, 0, 0, (1.0f - (f32) i / 120.0f) * 100.0f);
        }
        func_ovl14_01_8004CCE8(0, 0, 0, 0.0f);
        func_ovl14_01_800431C4(0x10D, D_ovl14_01_8004D5DC);
        func_ovl14_01_80043250(1);
        func_ovl14_01_8004C898(D_ovl14_01_8004D5DC, 0x04000000);
        func_ovl14_01_800431F8(D_ovl14_01_8004D5DC);
        func_ovl14_01_800431C4(0x10E, D_ovl14_01_8004D5F0);
        for (i = 0; i < 60; i++) {
            D_ovl14_01_8004D688 = 1.0f - (f32) i / 60.0f;
            func_ovl14_01_8004CA30();
        }
        func_ovl14_01_80043010(D_ovl14_01_8004D600, D_ovl14_01_8004D560);
        func_ovl14_01_80043010(D_ovl14_01_8004D618, D_ovl14_01_8004D5A0);
        func_ovl14_01_8004CA08(60);
        func_ovl14_01_8004C7F0((f32 *) &a);
        if (a.y >= 0.0f && a.y <= 180.0f) {
            y = a.y;
        } else {
            y = (360.0f - a.y) * -1.0f;
        }
        dy = (25.0f - y) / 30.0f;
        dz = (2500.0f - a.z) / 30.0f;
        dy0 = dy;
        sdz = dz / 60.0f * -1.0f;
        func_ovl14_01_8004CD40(1);
        c = 0xBF;
        func_ovl14_01_8004CD48(0xBF);
        sdy = dy0 / 60.0f * -1.0f;
        for (i = 0; i != 60; i++) {
            D_ovl14_01_8004D4F8.y += dy;
            func_ovl14_01_8004C790(D_ovl14_01_8004D4F8.y, D_ovl14_01_8004D4F8.y);
            a.z += dz;
            a.y += dy;
            dy += sdy;
            dz += sdz;
            func_ovl14_01_8004C6F8(32768.0f, a.y, a.z);
            func_ovl14_01_8004C790(a.y, a.y);
            D_ovl14_01_8004D4F8.y = a.y;
            func_ovl14_01_8004CA30();
        }
        do {
            func_ovl14_01_8004CD48(c);
            func_ovl14_01_8004CA30();
            c -= 8;
        } while (c >= 0);
        func_ovl14_01_8004CD40(0);
        if (func_ovl14_01_8004CC50(0xA4) != 0) {
            func_ovl14_01_8004CA08(90);
        }
        func_ovl14_01_8004CC68(0x414);
    }
}


static void func_ovl14_01_800431F8(UnkStructA *obj) {
    while (!(obj->unk40->unkC & 0x40)) {
        func_ovl14_01_8004CA30();
    }
}


void func_ovl14_01_80043010(UnkStructA **arg0, Link_ovl14_01 *arg1) {
    Link_ovl14_01 *l;

    if (arg1 == D_ovl14_01_8004D560) {
        if (D_ovl14_01_8004D54C == 0) {
            return;
        }
    } else if (D_ovl14_01_8004D550 == 0) {
        return;
    }
    arg1->unk0 = 2;
    arg1->unk10 = 0.0f;
    arg1->unkC = 0.1f;
    arg1->unk8 = 0.0f;
    arg1->unk4 = 250.0f;
    arg1++;
    arg1->unk0 = 2;
    arg1->unk10 = 0.0f;
    arg1->unkC = 0.0f;
    arg1->unk8 = 0.0f;
    arg1->unk4 = 60.0f;
    arg1++;
    arg1->unk0 = 0x10002;
    arg1->unk10 = 0.9f;
    arg1->unkC = 0.3f;
    arg1->unk8 = 0.01f;
    arg1->unk4 = 420.0f;
    arg0++;
    do {} while (0); /* TRICK: a uopt block boundary (no code) */
    func_ovl14_01_8004C8A0(*arg0, 0x300000);
    func_ovl14_01_8004C898(*arg0, 0x500000);
    (*arg0)->unk50 = -85.0f;
    (*arg0)->unk4C = 0.0f;
    arg0 += 2;
    func_ovl14_01_8004C898(*arg0, 0x500000);
    (*arg0)->unk50 = 0;
    arg0++;
    arg0[-1]->unk4C = 0;
    func_ovl14_01_8004C8A0(*arg0, 0xC30);
    (*arg0)->unk40->unk28 = 1.0f;
    (*arg0)->unk40->unk2C = 1.0f;
    (*arg0)->unk40->unk30 = 1.0f;
    (*arg0)->unk40->unk1C = 90.0f;
    func_ovl14_01_8004C898(*arg0, 0x10);
}

