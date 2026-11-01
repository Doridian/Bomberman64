/*
 * NON_MATCHING: ovl_0F_01's game object, complete: every function and its
 * data (.data and .bss as the original's sizes).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 0, jp 0
 *
 * ovl_0F_04's draft (1F2230.c) ported where the code is the same: the
 * movers (8004464C with its _inl0/_inl1, 80044E54, 80045158, 8004529C,
 * the script step 80044408 with its five empty statics, the turn
 * 800441CC), the particles (8004540C and its loop static 80045404, the
 * reset 80043100), the panel loop 80043588 (body in "panels.c") and
 * 80043504, the cut-scene 80043030, 80043094, 80045DD4, 80045E40 and its
 * setup static 80045E38, 80046988/80046A04/80046A60, with ovl_0F_04's
 * fakes and `#line`s. Its header has the reasons; what follows is what is
 * different here. Every function and stub comes out in the original's
 * place (scratch/0F_01/s1_map2.py in the main checkout), and the whole
 * .text, .data and .rodata match (jp).
 *
 * The order is ovl_0F_04's: the functions are defined last to first, the
 * handler last but for 80043010; its direct callees come out first
 * (80043018's stub, 80043030, 80043094, 80043100, 8004324C), then what it
 * only takes the address of, then case 2's static 80045E40 and the
 * handler. The fake is the `if (0)` address list in the empty static
 * func_ovl0F_01_80045FA8 (ovl_0F_04's 800460B4), called first in case 2:
 * every address-taken function in descending address order.
 *
 * Statics: 80043030, 80043094, 80043100, 80043468, 80043504, 80043588,
 * 800438C0, 800441CC, 80044408, 80045404, 80045E40 (the ones the
 * original passes arguments to in s registers are statics). 80043588,
 * 80043468, 800438C0 and 80045E40 are real calls; the others leave the
 * empty stubs. The stubs are named for where they come out; which statics
 * the original had there is open. A static's stubs come out just before
 * it (in the reverse of its calls), the handler's with its direct callees
 * in the reverse of its cases:
 * - the handler: 80043018 (case 1's loop, also 8004464C's last),
 *   80043020 (case 1's last, only an unused pad[2]), 80043028 (case 15), 800430E0-F8
 *   (case 5's four calls, each a static taking its D_ovl0F_01_80048508
 *   record), 8004323C (case 4's particle loop, defined after the handler
 *   so that its lines come after case 4's: 2 words), 80045FB0 (case 2's
 *   table loop, in "panels.c"; 80045FA0 is the empty stub in it) and
 *   80045FA8;
 * - 80043B0C: 80043B04 (its first 80043588 call), 80043AFC and 80043AF4
 *   (the platform's position put back and kept, (obj, sv)); 80043ACC-AEC
 *   are empty statics only in 80045FA8's list (in one call to
 *   80047CC8, so that 80045FA8 stays small enough to inline), which keeps
 *   their frame out of 80043B0C's; 80043ACC's dead `if (0)` call to
 *   800438C0 puts 800438C0 (and its stub 800438B8) ahead of them;
 * - 800452CC: 800452BC (empty) and 800452C4 (its 80043504 call, idx a
 *   parameter: ovl_0F_04's 80044D2C);
 * - the rest are empty statics called first in the function they
 *   precede (two in 8004324C, one in 80043298, one each in 80043504 and
 *   at the end of 80043588, one in 800438C0, one in 80045FB0); the
 *   trailing fourteen are unreferenced empty statics, defined first.
 *
 * Frames (as measured here): every local takes a frame word, whether it
 * lives in a register or not, from the top down in declaration order
 * (block-scoped ones too); below them each inlined static's own area, in
 * source order (at least 8 bytes, its parameters and locals rounded up to
 * 8); then the temporaries. An empty static only called from the `if (0)` list costs
 * nothing.
 *
 * Fakes and choices:
 * - 80043628: the switch is read into its own local (sw) for the setup
 *   (obj only in the loop), so it is in s0 for 80043468 (146 to 0).
 * - 800438C0: the last branch is `else if (unk14 > 0) { state = 1; ... }
 *   else { state = 2; }` (25 to 0).
 * - 80043B0C (363 to 0): the platforms' first loop has its own j (with
 *   i, p shared the last loop's s0); the frame (0x110: a at 0xEC, b 0xE0,
 *   x 0xC8, sv 0xA4) takes the unused pad0[6], pad1[5] and pad2 and only
 *   three inlined statics (above); the statics' bodies are in the file
 *   before `#line 1149 "1E2D80.c"` (a file change between them and the
 *   function: the copy `move v0, v1` and the reloads), but 80043B04 is
 *   after it (the prologue's `li s3, 3`); the D_ovl0F_01_80048420 = 2 store
 *   is renumbered one line past its loop's `for` (`#line 1230` /
 *   `#line 1229`, 7 words).
 * - 800452CC: obj and the last stores read `*D_ovl0F_01_80048264[idx].unk0`
 *   (not through p), and ovl_0F_04's empty `if (!idx) {}`, here after the
 *   800452C4 call (61 to 0).
 * - 80045E38: unk8 is set from the integer 0 (`= 0`), so its 0.0f isn't
 *   the one 80045E30's records share (69 to 0).
 * - 8004464C, 80044408: ovl_0F_04's, without its 0x8C sound calls. The
 *   route step's unk0 is u16 (lhu). 8004464C's 0.8166667f (its rodata
 *   word; 0.81666666f rounds one bit low, as in ovl_0F_02 and 0F_04).
 * - The handler (243 to 0): func_ovl0F_01_80047850 returns s32 (so v0
 *   isn't free in case 1's loops: i a1, count a2, p v1); case 4's object
 *   is read into a local before it is stored to D_ovl0F_01_8004878C;
 *   case 2's last store and case 3's first are followed by a file change
 *   (`#line 1 "panels.c"`), which keeps them out of the delay slots; the
 *   frame (0x100: q 0xF8, case 2's loop 0xE4, case 1's 0x6C and 0x5C, case
 *   4's 0x4C) has q and obj as its locals (obj first), y and i in the
 *   case 15 and case 4 statics, the unused pad[12] in 800430F8 and pad[2]
 *   in 80043020.
 * There are no VERSION conditionals (none in the earlier draft either);
 * only jp is measured.
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
    /* 0x00 */ u16 unk0;
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
s32 func_ovl0F_01_80047850(UnkStructA *);
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
void func_ovl0F_01_80043010(void);
void func_ovl0F_01_80045FB8(s32 arg0);
static void func_ovl0F_01_80045FB0(u32 (*p)[3], s32 count);
static void func_ovl0F_01_80043018(s32 count, UnkStruct_ovl0F_01_80048264 *p);
static void func_ovl0F_01_80043030(s32 n, char *msg);
static void func_ovl0F_01_80043020(void);
static void func_ovl0F_01_80043028(void);
static void func_ovl0F_01_80043094(s32 *arg0);
static void func_ovl0F_01_80043100(UnkStruct_ovl0F_01_80048798 *p);
static void func_ovl0F_01_800430E0(UnkStruct_ovl0F_01_80048508 *p);
static void func_ovl0F_01_800430E8(UnkStruct_ovl0F_01_80048508 *p);
static void func_ovl0F_01_800430F0(UnkStruct_ovl0F_01_80048508 *p);
static void func_ovl0F_01_800430F8(UnkStruct_ovl0F_01_80048508 *p);
void func_ovl0F_01_8004324C(void);
static void func_ovl0F_01_8004323C(void);
static void func_ovl0F_01_80043244(void);
void func_ovl0F_01_80043298(void);
static void func_ovl0F_01_80043290(void);
void func_ovl0F_01_80043348(UnkStructA *arg0);
static void func_ovl0F_01_80043468(UnkStructA *obj);
static void func_ovl0F_01_80043504(UnkStruct_ovl0F_01_80048264 *arg0);
static void func_ovl0F_01_800434F4(void);
static void func_ovl0F_01_800434FC(void);
static void func_ovl0F_01_80043588(UnkStruct_ovl0F_01_80048264 *p, s32 count);
void func_ovl0F_01_80043628(void);
static s32 func_ovl0F_01_800438C0(f32 *x);
static void func_ovl0F_01_800438B8(void);
void func_ovl0F_01_80043B0C(void);
static void func_ovl0F_01_80043AF4(UnkStructA *obj, f32 *sv);
static void func_ovl0F_01_80043AFC(UnkStructA *obj, f32 *sv);
static void func_ovl0F_01_80043B04(void);
static void func_ovl0F_01_80043ACC(void);
static void func_ovl0F_01_80043AD4(void);
static void func_ovl0F_01_80043ADC(void);
static void func_ovl0F_01_80043AE4(void);
static void func_ovl0F_01_80043AEC(void);
void func_ovl0F_01_8004413C(UnkStructA *obj);
static void func_ovl0F_01_800441CC(s32 i);
static void func_ovl0F_01_80044408(s32 flag);
static void func_ovl0F_01_800443E0(void);
static void func_ovl0F_01_800443E8(void);
static void func_ovl0F_01_800443F0(void);
static void func_ovl0F_01_800443F8(void);
static void func_ovl0F_01_80044400(void);
void func_ovl0F_01_8004464C(void);
static void func_ovl0F_01_8004464C_inl1(UnkStruct_ovl0F_01_80048264 *p);
static f32 func_ovl0F_01_8004464C_inl0(UnkStruct_ovl0F_01_80048264 *p);
void func_ovl0F_01_80044E54(UnkStructA *arg0);
void func_ovl0F_01_80045158(void);
s32 func_ovl0F_01_8004529C(s32 arg0);
void func_ovl0F_01_800452CC(s32 idx, s32 flag);
static void func_ovl0F_01_800452BC(void);
static void func_ovl0F_01_800452C4(s32 idx);
void func_ovl0F_01_8004540C(s32 arg0, UnkStruct_ovl0F_01_Gfx **arg1);
static void func_ovl0F_01_80045404(UnkStruct_ovl0F_01_Gfx **gdl);
void func_ovl0F_01_80045DD4(void);
static void func_ovl0F_01_80045E40(UnkStructA **arg0);
static void func_ovl0F_01_80045E30(void);
static void func_ovl0F_01_80045E38(UnkStructA **arg0);
static void func_ovl0F_01_80045FA0(void);
void func_ovl0F_01_80046988(s32 arg0, UnkStructA *arg1);
void func_ovl0F_01_800469BC(f32 arg0);
void func_ovl0F_01_80046A04(f32 arg0, f32 arg1, f32 arg2);
static void func_ovl0F_01_80045FA8(void);
void func_ovl0F_01_80046A60(void);
static void func_ovl0F_01_80046AE0(void);
static void func_ovl0F_01_80046AD8(void);
static void func_ovl0F_01_80046AD0(void);
static void func_ovl0F_01_80046AC8(void);
static void func_ovl0F_01_80046AC0(void);
static void func_ovl0F_01_80046AB8(void);
static void func_ovl0F_01_80046AB0(void);
static void func_ovl0F_01_80046AA8(void);
static void func_ovl0F_01_80046AA0(void);
static void func_ovl0F_01_80046A98(void);
static void func_ovl0F_01_80046A90(void);
static void func_ovl0F_01_80046A88(void);
static void func_ovl0F_01_80046A80(void);
static void func_ovl0F_01_80046A78(void);

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

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0F_01_80046A78(void) {
}

static void func_ovl0F_01_80046A80(void) {
}

static void func_ovl0F_01_80046A88(void) {
}

static void func_ovl0F_01_80046A90(void) {
}

static void func_ovl0F_01_80046A98(void) {
}

static void func_ovl0F_01_80046AA0(void) {
}

static void func_ovl0F_01_80046AA8(void) {
}

static void func_ovl0F_01_80046AB0(void) {
}

static void func_ovl0F_01_80046AB8(void) {
}

static void func_ovl0F_01_80046AC0(void) {
}

static void func_ovl0F_01_80046AC8(void) {
}

static void func_ovl0F_01_80046AD0(void) {
}

static void func_ovl0F_01_80046AD8(void) {
}

static void func_ovl0F_01_80046AE0(void) {
}

void func_ovl0F_01_80046A60(void) {
    D_ovl0F_01_80048774 = -1;
    D_ovl0F_01_80048778 = -1;
}

static void func_ovl0F_01_80045FA8(void) {
    /* fake: first references in descending address order (ovl_0F_04's 800460B4) */
    if (0) {
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_80045DD4, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_8004540C, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_800452CC, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_8004529C, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_80045158, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_80044E54, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_8004464C, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_8004413C, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_80043B0C, 0);
        func_ovl0F_01_80047CC8((s32) func_ovl0F_01_80043AEC, (s32) func_ovl0F_01_80043AE4, (s32) func_ovl0F_01_80043ADC, (s32) func_ovl0F_01_80043AD4, (s32) func_ovl0F_01_80043ACC);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_80043628, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_80043348, 0);
        func_ovl0F_01_80046F18((void (*)(UnkStructA *)) func_ovl0F_01_80043298, 0);
    }
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

static void func_ovl0F_01_80045FA0(void) {
}

static void func_ovl0F_01_80045E38(UnkStructA **arg0) {
    D_ovl0F_01_80048938.unk0 = func_ovl0F_01_80047078(func_ovl0F_01_80047018());
    D_ovl0F_01_80048938.unk4 = arg0;
    D_ovl0F_01_80048938.unkC = 0;
    D_ovl0F_01_80048938.unk10 = 0;
    D_ovl0F_01_80048938.unk14 = 0;
    D_ovl0F_01_80048938.unk16 = -1;
    D_ovl0F_01_80048938.unk8 = 0;
    D_ovl0F_01_80048148 = 1;
    D_ovl0F_01_80048938.unk18 = D_ovl0F_01_8004814C;
    D_ovl0F_01_80048938.unk20 = func_ovl0F_01_800452CC;
}

static void func_ovl0F_01_80045E30(void) {
    D_ovl0F_01_80048264[0].unkC = 0.0f;
    D_ovl0F_01_80048264[0].unk14 = 6.0f;
    D_ovl0F_01_80048264[0].unk1C = 90.0f;
    D_ovl0F_01_80048264[1].unkC = 0.0f;
    D_ovl0F_01_80048264[1].unk14 = 11.0f;
    D_ovl0F_01_80048264[1].unk1C = 90.0f;
    D_ovl0F_01_80048264[2].unkC = 0.0f;
    D_ovl0F_01_80048264[2].unk14 = 17.0f;
    D_ovl0F_01_80048264[2].unk1C = 90.0f;
}

/* case 2's: the movers and their script */
static void func_ovl0F_01_80045E40(UnkStructA **arg0) {
    s32 i;

    func_ovl0F_01_80045E38(arg0);
    func_ovl0F_01_80045E30();
    func_ovl0F_01_80043588(D_ovl0F_01_80048264, 6);
    for (i = 0; i < 6; i++) {
        func_ovl0F_01_80047838(func_ovl0F_01_80047870(*D_ovl0F_01_80048264[i].unk0), 0x02100000);
        D_ovl0F_01_800481D4[i].unk11 = 0;
        D_ovl0F_01_80048938.unk20(i, 0);
    }
    func_ovl0F_01_80046F70(func_ovl0F_01_80044E54);
    func_ovl0F_01_80047988(func_ovl0F_01_8004464C, NULL, 0, 0, 0x110);
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

static void func_ovl0F_01_80045404(UnkStruct_ovl0F_01_Gfx **gdl) {
    UnkStruct_ovl0F_01_Gfx *g2;
    f32 oldx;
    f32 oldz;
    f32 s;
    s32 i;
    f32 view[3];

    g2 = *gdl;
    oldx = D_ovl0F_01_80048928.x;
    oldz = D_ovl0F_01_80048928.z;
    func_ovl0F_01_80047780(&D_ovl0F_01_80048928);
    func_ovl0F_01_80047790(view);
    s = func_ovl0F_01_80047B38(view[0]);
    D_ovl0F_01_80048134 = ((D_ovl0F_01_80048928.x - oldx) * s - func_ovl0F_01_80047B30(view[0]) * (D_ovl0F_01_80048928.z - oldz)) * 0.5f;
    s = func_ovl0F_01_80047B38(view[0]);
    D_ovl0F_01_80048138 = (func_ovl0F_01_80047B30(view[0]) * (D_ovl0F_01_80048928.x - oldx) + (D_ovl0F_01_80048928.z - oldz) * s) * 0.2f;
    D_ovl0F_01_80048134 *= 1500.0f / view[2];
    D_ovl0F_01_80048138 *= 1500.0f / view[2];
    for (i = 0; i < 20; i++) {
        if (func_ovl0F_01_80047C10(0x407) != 0) {
            UnkStruct_ovl0F_01_80048798 *p = &D_ovl0F_01_80048798[i];

            { UnkStruct_ovl0F_01_Gfx *g = g2++; g->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL((u32) (p->unk8 + p->unk4 - 1) << 2, 0, 12) | _SHIFTL((u32) (p->unk0 + p->unk8 - 1) << 2, 12, 12); g->w1 = _SHIFTL(0, 24, 3) | _SHIFTL((u32) p->unk4 << 2, 0, 12) | _SHIFTL((u32) p->unk0 << 2, 12, 12); { UnkStruct_ovl0F_01_Gfx *g = g2++; g->w0 = 0xB4000000; g->w1 = 0; } { UnkStruct_ovl0F_01_Gfx *g = g2++; g->w0 = 0xB3000000; g->w1 = _SHIFTL((s32) (16.0f / (p->unk8 - 1) * 1024.0f), 0, 16) | _SHIFTL((s32) (16.0f / (p->unk8 - 1) * 1024.0f), 16, 16); } }
        }
        if (D_ovl0F_01_80048144 == 0.0f) {
            continue;
        }
        {
            f32 r;
            f32 dx;
            f32 dy;
            f64 drift;

            s = func_ovl0F_01_80047B38(view[0]);
            r = func_ovl0F_01_80047B40();
            dx = -D_ovl0F_01_80048134;
            D_ovl0F_01_80048798[i].unk0 += dx - r * (dx * 0.25f) + D_ovl0F_01_8004813C * s;
            s = (D_ovl0F_01_8004813C != 0.0f ? 1.0f : 0);
            if (func_ovl0F_01_80047B30(view[0]) * (s * D_ovl0F_01_8004813C) + D_ovl0F_01_80048140 < 0.0f) {
                f32 sign = (D_ovl0F_01_8004813C != 0.0f ? 1.0f : 0);

                drift = (func_ovl0F_01_80047B30(view[0]) * (sign * D_ovl0F_01_8004813C) + D_ovl0F_01_80048140) * 0.5;
            } else {
                f32 sign = (D_ovl0F_01_8004813C != 0.0f ? 1.0f : 0);

                drift = func_ovl0F_01_80047B30(view[0]) * (sign * D_ovl0F_01_8004813C) + D_ovl0F_01_80048140;
            }
            r = func_ovl0F_01_80047B40();
            dy = D_ovl0F_01_80048798[i].unkC - D_ovl0F_01_80048138;
            D_ovl0F_01_80048798[i].unk4 += dy - r * (dy * 0.6f) + drift;
            D_ovl0F_01_80048798[i].unk8 -= 0.1f * (D_ovl0F_01_80048798[i].unk8 * 0.0625f);
            if (340.0f <= D_ovl0F_01_80048798[i].unk0 || 240.0f <= D_ovl0F_01_80048798[i].unk4 || D_ovl0F_01_80048798[i].unk8 <= 3.0f ||
                D_ovl0F_01_80048798[i].unk10++ >= 240 || D_ovl0F_01_80048798[i].unk0 < -20.0f || D_ovl0F_01_80048798[i].unk4 < -10.0f) {
                func_ovl0F_01_80043100(&D_ovl0F_01_80048798[i]);
            }
        }
    }
    *gdl = g2;
}

void func_ovl0F_01_8004540C(s32 arg0, UnkStruct_ovl0F_01_Gfx **arg1) {
    UnkStruct_ovl0F_01_Gfx *gfx;
    UnkStruct_ovl0F_01_80048130 *t;

    gfx = *arg1;
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x00553048; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF279; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBB000001; g->w1 = 0x80008000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0x8000; }
    t = D_ovl0F_01_80048130;
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xFD100000; g->w1 = t->unk20 + (u32) t; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE8000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF5000100; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF0000000; g->w1 = 0x0703C000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xFD500000; g->w1 = t->unk14 + (u32) t; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF5500000; g->w1 = 0x07000000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF3000000; g->w1 = 0x0703F800; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF5400200; g->w1 = 0; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xF2000000; g->w1 = 0x0003C03C; }
    func_ovl0F_01_80045404(&gfx);
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0x00080000; }
    { UnkStruct_ovl0F_01_Gfx *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0; }
    *arg1 = gfx;
}

/* 800452CC's 80043504 call */
static void func_ovl0F_01_800452C4(s32 idx) {
    func_ovl0F_01_80043504(&D_ovl0F_01_80048264[idx]);
}

static void func_ovl0F_01_800452BC(void) {
}

/* the script's command: a mover (re)starts at a random speed on a random
 * route, high above; with flag 0 it stays stopped */
void func_ovl0F_01_800452CC(s32 idx, s32 flag) {
    UnkStruct_ovl0F_01_800481D4 *m;
    UnkStructA *obj;

    func_ovl0F_01_800452BC();
    func_ovl0F_01_800452C4(idx);
    if (!idx) {
    }
    m = &D_ovl0F_01_800481D4[idx];
    m->unkC = 0;
    m->unk12 = 0;
    m->unk14 = 1;
    m->unk11 = flag;
    obj = *D_ovl0F_01_80048264[idx].unk0;
    if (flag == 0) {
        func_ovl0F_01_80047840(obj, 0x01000070);
    } else {
        func_ovl0F_01_80047838(obj, 0x01000070);
    }
    m->unk4 = (f32) (func_ovl0F_01_80047B40() * 3.0) + 1.0f;
    m->unk10 = func_ovl0F_01_80047B48(2);
    m->unk8 = 0.05f;
    (*D_ovl0F_01_80048264[idx].unk0)->unk40->unk14 = 4300.0f;
    (*D_ovl0F_01_80048264[idx].unk0)->unk40->unk1C = 30.0f;
}

s32 func_ovl0F_01_8004529C(s32 arg0) {
    if ((arg0 & 0xF) == 0xF) {
        return 0;
    }
    return 1;
}

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

void func_ovl0F_01_80044E54(UnkStructA *arg0) {
    s32 dir;
    f32 speed;
    f32 dy;
    s32 i;

    dir = 0;
    speed = 0.0f;
    i = 0;
    func_ovl0F_01_80047F10(0x1E);
    if (D_ovl0F_01_80048938.unk16 != -1) {
        dir = D_ovl0F_01_800481D4[D_ovl0F_01_80048938.unk16].unk0;
        speed = D_ovl0F_01_800481D4[D_ovl0F_01_80048938.unk16].unk4 * 0.8f;
    }
    func_ovl0F_01_80047560(arg0->unk40, 0x11, 0);
    func_ovl0F_01_80047590(arg0->unk40, 4, 0xC);
    func_ovl0F_01_80047590(arg0->unk40, 5, 0xD);
    func_ovl0F_01_80047DD8(0, arg0->unk40->unk10, arg0->unk40->unk14 + 100.0f, arg0->unk40->unk18, 0);
    arg0->unk68 = 30;
    arg0->unk70 = 1.6333334f;
    while (i++ <= 200 && arg0->unk68 > 0.0f && !((arg0->unk40->unk14 <= func_ovl0F_01_80046E60()) ? TRUE : FALSE)) {
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
    if ((arg0->unk40->unk14 <= func_ovl0F_01_80046E60()) ? TRUE : FALSE) {
        func_ovl0F_01_80043348(arg0);
    } else {
        arg0->unk6C = 0.0f;
        arg0->unk70 = 0.0f;
    }
    func_ovl0F_01_800479A8(0x50);
}

static f32 func_ovl0F_01_8004464C_inl0(UnkStruct_ovl0F_01_80048264 *p) {
    f32 tilt;
    f32 slope;

    tilt = 0.0f;
    slope = 0.0f;
    func_ovl0F_01_80046EC0((*p->unk0)->unk40, &tilt, &slope);
    if (func_ovl0F_01_80047B30((*p->unk0)->unk40->unk20) >= 0.707f && slope != 0.0f) {
        tilt *= func_ovl0F_01_80047B30(slope);
    }
    return tilt * 0.6f;
}

static void func_ovl0F_01_8004464C_inl1(UnkStruct_ovl0F_01_80048264 *p) {
    s32 padP; /* unused: pos at sp+0xA8 */
    f32 pos[3];

    pos[0] = (*p->unk0)->unk40->unk10;
    pos[1] = (*p->unk0)->unk40->unk14;
    pos[2] = (*p->unk0)->unk40->unk18;
    func_ovl0F_01_80047F38(0x168, pos);
    func_ovl0F_01_80047EF0(pos);
}

void func_ovl0F_01_8004464C(void) {
    s32 active;
    s32 i;
    UnkStruct_ovl0F_01_800481D4 *st; /* unused, as rec, step and player: with fewer, unk16's store addresses the symbol (2 words) */
    UnkStruct_ovl0F_01_80048264 *rec;
    UnkStruct_ovl0F_01_8004815C *step;
    UnkStructA *obj;
    UnkStructA *player;
    s32 hit;
    s32 j; /* fake: a copy of i for the loop's body (from the permuter; it puts i in s0 and
            * the record in s2), but for the store to D_ovl0F_01_80048938.unk16 */
    f32 padA[2]; /* unused: the frame (0x100) and tilt/slope at sp+0xC4/0xC0 */
    f32 z; /* fake: the mover's x, so the x compares get f0 and f2 as in the original */

    active = TRUE;
    do {
        func_ovl0F_01_80044408(D_ovl0F_01_80048148);
        if (D_ovl0F_01_80048938.unkC != 0) {
            obj = *D_ovl0F_01_80048938.unk4;
            if (obj != NULL && obj->unk40->unk48 != NULL) {
                obj->unk40->unk48->unk4->unk4 = D_ovl0F_01_80048938.unk8;
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
        }
        for (i = 0; i != 6; i++) {
            j = i;
            if (D_ovl0F_01_800481D4[j].unk11 == 1) {
                func_ovl0F_01_80047948((*D_ovl0F_01_80048264[j].unk0));
                if (D_ovl0F_01_80048938.unk0->unk40->unk10 <= (z = (*D_ovl0F_01_80048264[j].unk0)->unk40->unk10) + 300.0f &&
                    z - 300.0f <= D_ovl0F_01_80048938.unk0->unk40->unk10 &&
                    D_ovl0F_01_80048938.unk0->unk40->unk18 <= (*D_ovl0F_01_80048264[j].unk0)->unk40->unk18 + 300.0f &&
                    (*D_ovl0F_01_80048264[j].unk0)->unk40->unk18 - 300.0f <= D_ovl0F_01_80048938.unk0->unk40->unk18) {
                    if (D_ovl0F_01_800481D4[j].unk14 != 0) {
                        func_ovl0F_01_80047F10(0x87);
                        D_ovl0F_01_800481D4[j].unk14 = 0;
                    }
                } else if (D_ovl0F_01_800481D4[j].unk14 == 0) {
                    D_ovl0F_01_800481D4[j].unk14 = 1;
                }
                if ((*D_ovl0F_01_80048264[j].unk0)->unk6C == 0.0f) {
                    if (D_ovl0F_01_800481D4[j].unkC >= D_ovl0F_01_8004815C[D_ovl0F_01_800481D4[j].unk10][D_ovl0F_01_800481D4[j].unk12].unk0) {
                        if (D_ovl0F_01_80048264[j].unk1C == 90.0f) {
                            D_ovl0F_01_800481D4[j].unkC = 0;
                            D_ovl0F_01_800481D4[j].unk0 = D_ovl0F_01_8004815C[D_ovl0F_01_800481D4[j].unk10][D_ovl0F_01_800481D4[j].unk12].unk2;
                            D_ovl0F_01_800481D4[j].unk8 = D_ovl0F_01_8004815C[D_ovl0F_01_800481D4[j].unk10][D_ovl0F_01_800481D4[j].unk12].unk4;
                            D_ovl0F_01_800481D4[j].unk12 = D_ovl0F_01_8004815C[D_ovl0F_01_800481D4[j].unk10][D_ovl0F_01_800481D4[j].unk12].unk3;
                        } else if (D_ovl0F_01_80048264[j].unk1C == 270.0f) {
                            D_ovl0F_01_800481D4[j].unk0 = (D_ovl0F_01_8004815C[D_ovl0F_01_800481D4[j].unk10][D_ovl0F_01_800481D4[j].unk12].unk2 + 0x80) & 0xFF;
                            D_ovl0F_01_800481D4[j].unkC = 0;
                            D_ovl0F_01_800481D4[j].unk8 = D_ovl0F_01_8004815C[D_ovl0F_01_800481D4[j].unk10][D_ovl0F_01_800481D4[j].unk12].unk4;
                            D_ovl0F_01_800481D4[j].unk12 = D_ovl0F_01_8004815C[D_ovl0F_01_800481D4[j].unk10][D_ovl0F_01_800481D4[j].unk12].unk3;
                        }
                    }
                }
                D_ovl0F_01_800481D4[j].unkC++;
                func_ovl0F_01_800441CC(j);
                func_ovl0F_01_80047E80((*D_ovl0F_01_80048264[j].unk0), D_ovl0F_01_800481D4[j].unk0, D_ovl0F_01_800481D4[j].unk4, func_ovl0F_01_8004529C);
                (*D_ovl0F_01_80048264[j].unk0)->unk40->unk1C = func_ovl0F_01_8004464C_inl0(&D_ovl0F_01_80048264[j]);
                if (((*D_ovl0F_01_80048264[j].unk0)->unk40->unk14 <= func_ovl0F_01_80046E60()) ? TRUE : FALSE) {
                    D_ovl0F_01_80048938.unk20(j, 0);
                    continue;
                }
                hit = func_ovl0F_01_800477E8((*D_ovl0F_01_80048264[j].unk0), 0x40);
                if (hit != 0 && ((hit & 0x2000) || (hit & 0x4000))) {
                    func_ovl0F_01_8004464C_inl1(&D_ovl0F_01_80048264[j]);
                    (*D_ovl0F_01_80048264[j].unk0)->unk68 = 20.0f;
                    (*D_ovl0F_01_80048264[j].unk0)->unk70 = 0.8166667f;
                    D_ovl0F_01_800481D4[j].unk11 = 2;
                    func_ovl0F_01_80047988(func_ovl0F_01_80045158, (void *) j, 0, 0, 0x150);
                }
                if (func_ovl0F_01_80047800(D_ovl0F_01_80048938.unk0, (*D_ovl0F_01_80048264[j].unk0)) != 0) {
                    D_ovl0F_01_80048938.unk16 = i;
                }
                D_ovl0F_01_800481D4[j].unk4 += D_ovl0F_01_800481D4[j].unk8;
            } else if (D_ovl0F_01_800481D4[j].unk11 == 2) {
                if ((*D_ovl0F_01_80048264[j].unk0)->unk68 == 0.0f && (*D_ovl0F_01_80048264[j].unk0)->unk6C == 0.0f) {
                    D_ovl0F_01_80048938.unk20(j, 0);
                    continue;
                }
                if ((*D_ovl0F_01_80048264[j].unk0)->unk40->unk1C < 180.0f) {
                    (*D_ovl0F_01_80048264[j].unk0)->unk40->unk1C += 5.0f;
                }
                func_ovl0F_01_80047E80((*D_ovl0F_01_80048264[j].unk0), D_ovl0F_01_800481D4[j].unk0, D_ovl0F_01_800481D4[j].unk4, func_ovl0F_01_8004529C);
                func_ovl0F_01_800478B8((*D_ovl0F_01_80048264[j].unk0));
                if (((*D_ovl0F_01_80048264[j].unk0)->unk40->unk14 <= func_ovl0F_01_80046E60()) ? TRUE : FALSE) {
                    D_ovl0F_01_80048938.unk20(j, 0);
                }
            }
        }
        if (D_ovl0F_01_80048148 == 0) {
            active = FALSE;
            for (j = 0; j < 6; j++) {
                if (D_ovl0F_01_800481D4[j].unk11 != 0) {
                    active = TRUE;
                }
            }
        }
        func_ovl0F_01_800479D0();
    } while (active);
    func_ovl0F_01_80043018(6, D_ovl0F_01_80048264);
    func_ovl0F_01_80047998();
}

static void func_ovl0F_01_80044400(void) {
}

static void func_ovl0F_01_800443F8(void) {
}

static void func_ovl0F_01_800443F0(void) {
}

static void func_ovl0F_01_800443E8(void) {
}

static void func_ovl0F_01_800443E0(void) {
}

/* one step of the movers' script */
static void func_ovl0F_01_80044408(s32 flag) {
    u16 *e;
    u16 cmd;
    s32 kind;
    s32 arg;

    func_ovl0F_01_80044400();
    func_ovl0F_01_800443F8();
    func_ovl0F_01_800443F0();
    func_ovl0F_01_800443E8();
    func_ovl0F_01_800443E0();
    e = D_ovl0F_01_80048938.unk18[D_ovl0F_01_80048938.unk14];
    if (e[0] == D_ovl0F_01_80048938.unk10++) {
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
static void func_ovl0F_01_800441CC(s32 i) {
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

void func_ovl0F_01_8004413C(UnkStructA *obj) {
    if ((obj->unk8 & 1) || ((obj->unk8 & 2) && obj->unk40->unk10 < 300.0f) || (obj->unk8 & 4)) {
        if (obj->unk40->unk10 < obj->unk58) {
            obj->unk40->unk10 = obj->unk58;
            obj->unk40->unk14 = obj->unk5C;
        }
    }
}

static void func_ovl0F_01_80043AEC(void) {
}

static void func_ovl0F_01_80043AE4(void) {
}

static void func_ovl0F_01_80043ADC(void) {
}

static void func_ovl0F_01_80043AD4(void) {
}

/* only in 80045FA8's address list (a fake): its dead call puts 800438C0 ahead of it */
static void func_ovl0F_01_80043ACC(void) {
    if (0) {
        func_ovl0F_01_800438C0(NULL);
    }
}

/* 80043B0C's: the platform's position put back */
static void func_ovl0F_01_80043AFC(UnkStructA *obj, f32 *sv) {
    obj->unk40->unk10 = sv[0];
    obj->unk40->unk14 = sv[1];
    obj->unk40->unk18 = sv[2];
}

/* 80043B0C's: the platform's position kept */
static void func_ovl0F_01_80043AF4(UnkStructA *obj, f32 *sv) {
    sv[0] = obj->unk40->unk10;
    sv[1] = obj->unk40->unk14;
    sv[2] = obj->unk40->unk18;
}
#line 1149 "1E2D80.c"
static void func_ovl0F_01_80043B04(void) {
    func_ovl0F_01_80043588(D_ovl0F_01_8004836C, 3);
}


/* a task: the platforms, once the player reaches them */
void func_ovl0F_01_80043B0C(void) {
    s32 pad0[6];
    Vec3f a;
    Vec3f b;
    s32 pad1[5];
    f32 x;
    UnkStructA *pl;
    UnkStructA *obj;
    s32 state;
    s32 i;
    s32 j;
    s32 pad2;
    f32 sv[3];

    D_ovl0F_01_80048420 = 0;
    func_ovl0F_01_80043B04();
    func_ovl0F_01_80043588(&D_ovl0F_01_800483F0, 1);
    func_ovl0F_01_80047840(D_ovl0F_01_80048744, 0x01000000);
    for (j = 0; j < 3; j++) {
        obj = D_ovl0F_01_80048738[j];
        obj->unk40->unk28 = 3.0f;
        obj->unk40->unk2C = 3.0f;
        obj->unk40->unk30 = 1.0f;
        obj->unk40->unk14 += 110.0f;
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
        if (!((D_ovl0F_01_80048744->unk40->unk14 <= func_ovl0F_01_80046E60()) ? TRUE : FALSE)) {
            func_ovl0F_01_800478B8(D_ovl0F_01_80048744);
        }
        if ((f32) func_ovl0F_01_80047B40() > 0.8f) {
            func_ovl0F_01_80047DD8(0x10, x + 50.0f, D_ovl0F_01_80048744->unk40->unk14 + 1000.0f,
                                   func_ovl0F_01_80047B40() * 1100.0 + 500.0, 0);
            func_ovl0F_01_80047750(10);
        }
        if (state == 0 && pl->unk40->unk18 >= 360.0f && pl->unk40->unk18 <= 1850.0f && pl->unk40->unk10 <= x) {
            func_ovl0F_01_80043AF4(D_ovl0F_01_80048738[0], sv);
            D_ovl0F_01_80048738[0]->unk40->unk10 = pl->unk40->unk10;
            D_ovl0F_01_80048738[0]->unk40->unk14 = pl->unk40->unk14;
            D_ovl0F_01_80048738[0]->unk40->unk18 = pl->unk40->unk18;
            func_ovl0F_01_80047838(D_ovl0F_01_80048738[0], 0x20);
            func_ovl0F_01_80047948(D_ovl0F_01_80048738[0]);
            func_ovl0F_01_80047840(D_ovl0F_01_80048738[0], 0x20);
            func_ovl0F_01_80043AFC(D_ovl0F_01_80048738[0], sv);
        }
        func_ovl0F_01_800479D0();
    }
    func_ovl0F_01_80047760(50.0f, 50.0f, 50.0f);
    func_ovl0F_01_80047750(20);
#line 1230
    D_ovl0F_01_80048420 = 2;
#line 1229
    for (i = 0; i < 3; i++) {
        D_ovl0F_01_80048738[i]->unkC = 0;
        func_ovl0F_01_80047840(D_ovl0F_01_80048738[i], 0x01000030);
    }
    func_ovl0F_01_80046E78(2, 3, 4, 4, 0x12, 0x16);
    D_ovl0F_01_8004841C = -1;
    func_ovl0F_01_80047998();
}

static void func_ovl0F_01_800438B8(void) {
}

/* the platforms rise, wobble and settle; 1 while one still sinks, 2 once all
 * are down */
static s32 func_ovl0F_01_800438C0(f32 *x) {
    s32 state;
    f32 d;
    s32 i;
    UnkStructA *obj;

    func_ovl0F_01_800438B8();
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
        } else if (obj->unk40->unk14 > 0.0f) {
            state = 1;
            obj->unk40->unk14 -= 10.0f;
        } else {
            state = 2;
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
    UnkStructA *sw;

    func_ovl0F_01_80043588(&D_ovl0F_01_8004845C, 1);
    sw = D_ovl0F_01_80048748;
    sw->unkC = 0x40;
    func_ovl0F_01_80047540(sw->unk40, 2);
    func_ovl0F_01_80043468(sw);
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
static void func_ovl0F_01_80043588(UnkStruct_ovl0F_01_80048264 *p, s32 count) {
    s32 i;

#line 1 "panels.c"
    for (i = 0; i < count; i++) {
        *p->unk0 = func_ovl0F_01_80047860(p->unk4, p->unk24 | 0x01000000, 0x30, p->unk8);
        func_ovl0F_01_80043504(p);
        (*p->unk0)->unk40->unk1C = p->unk18;
        (*p->unk0)->unk40->unk20 = p->unk1C;
        (*p->unk0)->unk40->unk24 = p->unk20;
        p++;
    }
    func_ovl0F_01_800434F4();
}
#line 1301 "1E2D80.c"

static void func_ovl0F_01_800434FC(void) {
}

static void func_ovl0F_01_800434F4(void) {
}

static void func_ovl0F_01_80043504(UnkStruct_ovl0F_01_80048264 *arg0) {
    f32 pos[3];

    func_ovl0F_01_800434FC();
    func_ovl0F_01_80046E98(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

/* the switch's two looks, by its state */
static void func_ovl0F_01_80043468(UnkStructA *obj) {
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

static void func_ovl0F_01_80043290(void) {
}

/* a task: the stage's opening message, once the stage has started */
void func_ovl0F_01_80043298(void) {
    func_ovl0F_01_80043290();
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

static void func_ovl0F_01_80043244(void) {
}


/* cases 0x15 and 0x16's: the player starts high above the floor */
void func_ovl0F_01_8004324C(void) {
    func_ovl0F_01_80043244();
    func_ovl0F_01_80047078(func_ovl0F_01_80047018())->unk40->unk14 += 2000.0f;
}

static void func_ovl0F_01_800430F8(UnkStruct_ovl0F_01_80048508 *p) {
    s32 pad[12];

    func_ovl0F_01_80047038(p->unk0, p->unk4, p->unk8, p->unkC, p->unk10, p->unk14, p->unk18);
}

static void func_ovl0F_01_800430F0(UnkStruct_ovl0F_01_80048508 *p) {
    func_ovl0F_01_80047038(p->unk0, p->unk4, p->unk8, p->unkC, p->unk10, p->unk14, p->unk18);
}

static void func_ovl0F_01_800430E8(UnkStruct_ovl0F_01_80048508 *p) {
    func_ovl0F_01_80047038(p->unk0, p->unk4, p->unk8, p->unkC, p->unk10, p->unk14, p->unk18);
}

static void func_ovl0F_01_800430E0(UnkStruct_ovl0F_01_80048508 *p) {
    func_ovl0F_01_80047038(p->unk0, p->unk4, p->unk8, p->unkC, p->unk10, p->unk14, p->unk18);
}

static void func_ovl0F_01_80043100(UnkStruct_ovl0F_01_80048798 *p) {
    f32 r;
    f64 t;

    r = func_ovl0F_01_80047B40();
    p->unk0 = func_ovl0F_01_80047B40() * 370.0 - 50.0;
    t = func_ovl0F_01_80047B40();
    p->unk4 = (D_ovl0F_01_8004813C < 0 ? -D_ovl0F_01_8004813C : D_ovl0F_01_8004813C) * 30.0f * t;
    if (D_ovl0F_01_80048138 <= 0.0f) {
        p->unk4 += (1.0f - r) * 40.0f;
    } else {
        p->unk4 += func_ovl0F_01_80047B48(90);
    }
    p->unk10 = 0;
    p->unk8 = r * 12.0f + 4.0f;
    p->unkC = r * r * 5.0f + 0.5f;
}

static void func_ovl0F_01_80043094(s32 *arg0) {
    if (func_ovl0F_01_80047000(arg0[0], arg0[1], arg0[2], arg0[3]) != 0) {
        func_ovl0F_01_80046F30(arg0[4], arg0[5], arg0[6]);
    }
}

static void func_ovl0F_01_80043028(void) {
    f32 y;

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
}

static void func_ovl0F_01_80043020(void) {
    s32 pad[2];
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

/* case 1's: the models' tasks end */
#line 1 "panels.c"
static void func_ovl0F_01_80043018(s32 count, UnkStruct_ovl0F_01_80048264 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_01_80047850(*p->unk0);
        p++;
    }
}
#line 1457 "1E2D80.c"

/* case 2's: the stage's tables */
#line 1 "panels.c"
static void func_ovl0F_01_80045FB0(u32 (*p)[3], s32 count) {
    s32 i;

    func_ovl0F_01_80045FA0();
    for (i = 0; i < count; i++) {
        func_ovl0F_01_80047E98((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}
#line 1470 "1E2D80.c"

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_01_80045FB8(s32 arg0) {
    UnkStructA *obj;
    UnkStruct_ovl0F_01_800480D8 *q;

    switch (arg0) {
        case 2:
            func_ovl0F_01_80045FA8();
            D_ovl0F_01_80048434 = 0;
            D_ovl0F_01_80048790 = func_ovl0F_01_80046F88();
            func_ovl0F_01_80047CF0(D_ovl0F_01_80048438);
            func_ovl0F_01_80045FB0(D_ovl0F_01_80048488, 6);
            func_ovl0F_01_80046E38(0x223);
            func_ovl0F_01_80046E50(0x237);
            D_ovl0F_01_8004842C = 0;
            D_ovl0F_01_80048430 = func_ovl0F_01_80047988(func_ovl0F_01_80043628, NULL, 0, 0, 0x110);
            func_ovl0F_01_80046FE8();
            func_ovl0F_01_80045E40(&D_ovl0F_01_80048428);
            func_ovl0F_01_80046F18(func_ovl0F_01_8004413C, 5);
            D_ovl0F_01_8004841C = func_ovl0F_01_80047988(func_ovl0F_01_80043B0C, NULL, 0, 0, 0x110);
#line 1 "panels.c"
            break;
#line 1493 "1E2D80.c"
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
            obj = func_ovl0F_01_80047598(func_ovl0F_01_8004540C, -60);
            D_ovl0F_01_8004878C = obj;
            obj->unkC |= 0x210;
            func_ovl0F_01_8004323C();
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
                    func_ovl0F_01_800430F8(&D_ovl0F_01_80048508[0]);
                    break;
                case 20:
                    func_ovl0F_01_800430F0(&D_ovl0F_01_80048508[1]);
                    break;
                case 21:
                    func_ovl0F_01_800430E8(&D_ovl0F_01_80048508[2]);
                    break;
                case 22:
                    func_ovl0F_01_800430E0(&D_ovl0F_01_80048508[3]);
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
            func_ovl0F_01_80043028();
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
            func_ovl0F_01_80043020();
            break;
        case 12:
            func_ovl0F_01_80047080(1);
            break;
        case 3:
#line 1 "panels.c"
            D_ovl0F_01_80048434 = 1;
#line 1654 "1E2D80.c"
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

static void func_ovl0F_01_8004323C(void) {
    s32 i;

    for (i = 0; i < 20; i++) {
        func_ovl0F_01_80043100(&D_ovl0F_01_80048798[i]);
        D_ovl0F_01_80048798[i].unk4 = func_ovl0F_01_80047B48(240);
    }
}

void func_ovl0F_01_80043010(void) {
}

