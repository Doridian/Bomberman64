/*
 * NON_MATCHING: ovl_0C_06's game object, complete: every function and its
 * data (.data 0x410, .rodata 0xB0 and .bss 0x60 laid out as the original).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 334, jp 627
 *
 * A first draft: ovl_0C_07's for what the two share (sibling functions
 * translated, constants and data rechecked), the crumbling blocks and their
 * switches from m2c (ovl_0C_01 and ovl_0C_02 have them too, still asm).
 * Matched since: 80043544 (the loop walks the list parameter itself and a
 * copy taken first goes to the call), 800430A8 (`dz * 50`, an int, so its
 * 50.0f isn't shared with the stored one; `!= arg1` returns 0 first),
 * 80046CF0 and 8004696C (an s16 alpha).
 *
 * What still differs in us (words):
 * - func_ovl0C_06_80044340 (84), 80043248 (67), 80044494 (57): the
 *   original passes `arg ? 0x01000000 : 0x01000000` without folding it:
 *   a branch over a second copy of the constant (in the loops, two saved
 *   registers, one hoisted as the initial value).  Every ternary, if/else,
 *   cast or type mix tried folds to one `lui`; an inlined static
 *   `if (a) return K; return K;` keeps a branch but not this one.  The
 *   rest of each diff is the register allocation that follows.
 * - func_ovl0C_06_80046288 (38): ovl_0C_07's mover, word for word, but the
 *   original keeps obj->unk40 in v1 where this gives v0.
 * - func_ovl0C_06_800455DC (26): the original's frame is 0x10 bigger (lim
 *   at 0x54); 80045BA0 (2) has a frame 8 bigger;
 *   80046200's macro with its flag doesn't give either.
 * - func_ovl0C_06_800458D8 (2): `li s1, 0x7F` is scheduled after the loop
 *   test in the original; no placement of `vol = 0x7F` gives it.
 * - func_ovl0C_06_80044F44 (16), 800446FC (15), 8004510C (9),
 *   80045FC8 (8), and five of 2 words each.
 */
#include "common.h"

/*
 * ovl_0C_06's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).  ovl_0C_07's skeleton for
 * the gate, the movers, the lift and the stage object; the crumbling blocks
 * and their switches are ovl_0C_06's own (as in ovl_0C_01 and ovl_0C_02).
 */

/* the handler's state, set by func_ovl0C_07_80043CF0 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_06_800493B0;

/* a gate: its object, its position, the trigger object's position and the
 * arguments of its map changes (the task func_ovl0C_07_80044B48 takes one) */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
} UnkStruct_ovl0C_06_80048F10;

/* an object, its position and the limits the movers check it against */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} UnkStruct_ovl0C_06_80048FD0;

/* a mover: the tasks func_ovl0C_07_80044CE0 and func_ovl0C_07_80044DC8
 * take one (unk0 indexes D_ovl0C_06_80048FD0) */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
} UnkStruct_ovl0C_06_80049030;

/* three lifts, each the task func_ovl0C_07_80045694's */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ UnkStructA *unk8;
    /* 0x0C */ UnkStructA *unkC;
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
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ s32 unk44;
} UnkStruct_ovl0C_06_80048F88;

/* the stage object func_ovl0C_07_80044178 sets up (ovl_0C_04's
 * D_ovl0C_04_80045D34) */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
} UnkStruct_ovl0C_06_80049274;

/* a crumbling block (func_ovl0C_06_8004696C's task); the list ends at the
 * first unk2 of 0 */
typedef struct UnkStruct_ovl0C_06_800490FC UnkStruct_ovl0C_06_800490FC;
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ UnkStruct_ovl0C_06_800490FC *unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
} UnkStruct_ovl0C_06_8004914C;

/* a switch: its flag (unk24) and the timer of its sparks */
struct UnkStruct_ovl0C_06_800490FC {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s32 unk24;
};

/* an object and its position */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl0C_06_80049264;

void func_ovl0C_06_80047BB8(s32);
void func_ovl0C_06_80047BD0(s32);
void func_ovl0C_06_80047BF0(s32, s32, s32, s32);
void func_ovl0C_06_80047BF8(s32, s32, s32, s32, s32, s32);
void func_ovl0C_06_80047C00(s32, s32, s32, s32, s32, s32, s32);
void func_ovl0C_06_80047C40(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_06_80047CA0(void (*)(UnkStructA *));
void func_ovl0C_06_80047CB0(s32, s32, s32);
void func_ovl0C_06_80047CF0(void (*)(UnkStructA *));
s32 *func_ovl0C_06_80047D08(void);
void func_ovl0C_06_80047D20(s32);
void func_ovl0C_06_80047D28(s32);
void func_ovl0C_06_80047D40(s32, s32);
void func_ovl0C_06_80047D58(s32);
void func_ovl0C_06_80047D68(void);
void func_ovl0C_06_80047D70(s32, s32, s32);
void func_ovl0C_06_80047D78(void *);
s32 func_ovl0C_06_80047D80(s32, s32, s32, s32);
s32 func_ovl0C_06_80047D88(s32, s32, s32, s32, s32);
s32 func_ovl0C_06_80047D98(void);
void func_ovl0C_06_80047DA0(s32, void *);
void func_ovl0C_06_80047DA8(s32);
void func_ovl0C_06_80047DB0(s32);
void func_ovl0C_06_80047DB8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_06_80047DC8(void);
void func_ovl0C_06_80047DE0(s32);
UnkStructA *func_ovl0C_06_80047DF8(s32);
void func_ovl0C_06_80047E00(s32);
void func_ovl0C_06_80047E68(void);
void func_ovl0C_06_800482C0(UnkStructA_40 *, s32);
void func_ovl0C_06_800482C8(UnkStructA_40 *, s32, s32, s32);
f32 func_ovl0C_06_800482F8(UnkStructA_40 *, s32);
s32 func_ovl0C_06_80048300(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0C_06_80048320(s32, s32);
void func_ovl0C_06_800483F8(f32, f32, f32);
void func_ovl0C_06_80048418(f32, f32, f32);
void func_ovl0C_06_80048420(f32 *, f32 *, f32 *);
void func_ovl0C_06_80048458(s32);
void func_ovl0C_06_80048460(s32);
void func_ovl0C_06_800484B0(f32, f32);
void func_ovl0C_06_800484E8(void *);
void func_ovl0C_06_80048518(void);
void func_ovl0C_06_80048520(void);
s32 func_ovl0C_06_80048568(UnkStructA *, s32);
void func_ovl0C_06_80048590(UnkStructA *);
void func_ovl0C_06_80048598(UnkStructA *, UnkStructA *);
void func_ovl0C_06_800485B8(UnkStructA *, s32);
void func_ovl0C_06_800485C0(UnkStructA *, s32);
void func_ovl0C_06_800485D0(UnkStructA *);
UnkStructA *func_ovl0C_06_800485E0(s32, s32, s32, s32);
UnkStructA *func_ovl0C_06_800485F0(UnkStructA *);
UnkStructA *func_ovl0C_06_80048600(s32, s32, f32, f32, f32);
void func_ovl0C_06_80048638(UnkStructA *);
UnkStructA *func_ovl0C_06_80048648(UnkStructA *, s32);
void func_ovl0C_06_800486C8(UnkStructA *);
s32 func_ovl0C_06_80048708(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_06_80048710(s32);
void func_ovl0C_06_80048718(void);
void func_ovl0C_06_80048728(s32);
void *func_ovl0C_06_80048730(void);
void func_ovl0C_06_80048750(void);
void func_ovl0C_06_80048768(u16);
void func_ovl0C_06_80048780(s32, s32);
f32 func_ovl0C_06_800488B0(f32);
f32 func_ovl0C_06_800488B8(f32);
s32 func_ovl0C_06_800488C8(s32);
s32 func_ovl0C_06_80048970(s32);
void func_ovl0C_06_80048980(s32);
void func_ovl0C_06_80048988(s32);
s32 func_ovl0C_06_80048990(s32);
void func_ovl0C_06_80048A70(u32 (*)[3]);
void func_ovl0C_06_80048A88(u32 (*)[3]);
void func_ovl0C_06_80048B58(s32, f32, f32, f32, s32);
void func_ovl0C_06_80048BA8(f32 *);
void func_ovl0C_06_80048C18(s32, s32, s32);
void func_ovl0C_06_80048C78(void);
s32 func_ovl0C_06_80048C90(s32);
void func_ovl0C_06_80048CB0(s32, f32, f32, f32);
void func_ovl0C_06_80048CC0(s32);
void func_ovl0C_06_80048CC8(s32, s8);
void func_ovl0C_06_80048E08(void);

void func_ovl0C_06_80043010(void);
void func_ovl0C_06_80043018(void);
void func_ovl0C_06_80043020(void);
void func_ovl0C_06_80043040(void);
void func_ovl0C_06_80043060(void);
s32 func_ovl0C_06_800430A8(UnkStructA *arg0, UnkStructA *arg1);
void func_ovl0C_06_800431B8(void);
void func_ovl0C_06_80043248(UnkStruct_ovl0C_06_8004914C *arg0, s32 arg1);
void func_ovl0C_06_80043354(UnkStruct_ovl0C_06_80049264 *arg0, UnkStruct_ovl0C_06_8004914C *arg1, UnkStruct_ovl0C_06_800490FC *arg2, s32 arg3);
s32 func_ovl0C_06_80043544(UnkStruct_ovl0C_06_80049264 *arg0, UnkStruct_ovl0C_06_8004914C *arg1, UnkStruct_ovl0C_06_800490FC *list, s32 arg3);
void func_ovl0C_06_80043710(UnkStruct_ovl0C_06_80048F10 *arg0);
void func_ovl0C_06_8004379C(UnkStruct_ovl0C_06_80048F10 *arg0);
void func_ovl0C_06_80043820(void);
void func_ovl0C_06_80043868(void);
void func_ovl0C_06_80043914(void);
void func_ovl0C_06_8004394C(UnkStructA *arg0, UnkStructA *arg1, f32 arg2);
void func_ovl0C_06_8004399C(UnkStruct_ovl0C_06_80049030 *arg0);
void func_ovl0C_06_80043A5C(void);
void func_ovl0C_06_80043AB4(void);
void func_ovl0C_06_80043AEC(void);
void func_ovl0C_06_80043B3C(void);
void func_ovl0C_06_80043D54(UnkStruct_ovl0C_06_80048F10 *arg0);
void func_ovl0C_06_80043DC0(void);
void func_ovl0C_06_80043EC8(void);
void func_ovl0C_06_80043F34(void);
void func_ovl0C_06_80043F6C(void);
void func_ovl0C_06_80043FE0(void);
void func_ovl0C_06_80044028(void);
void func_ovl0C_06_800440B4(void);
void func_ovl0C_06_80044164(UnkStruct_ovl0C_06_80048F10 *arg0);
void func_ovl0C_06_80044228(UnkStruct_ovl0C_06_80048F10 *arg0);
void func_ovl0C_06_80044264(void);
void func_ovl0C_06_800442BC(UnkStruct_ovl0C_06_80048FD0 *arg0);
void func_ovl0C_06_800442BC(UnkStruct_ovl0C_06_80048FD0 *arg0);
void func_ovl0C_06_80044340(UnkStruct_ovl0C_06_800490FC *arg0, s32 arg1);
void func_ovl0C_06_80044340(UnkStruct_ovl0C_06_800490FC *arg0, s32 arg1);
void func_ovl0C_06_80044494(UnkStruct_ovl0C_06_80049264 *arg0, UnkStruct_ovl0C_06_8004914C *arg1, s32 arg2);
void func_ovl0C_06_80044584(f32 arg0);
void func_ovl0C_06_800445CC(void);
void func_ovl0C_06_800446FC(void);
void func_ovl0C_06_80044808(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4);
void func_ovl0C_06_80044830(void);
void func_ovl0C_06_80044884(void);
void func_ovl0C_06_800448D4(void);
void func_ovl0C_06_8004491C(void);
void func_ovl0C_06_80044950(void);
void func_ovl0C_06_800449C8(void);
void func_ovl0C_06_800449F0(void);
void func_ovl0C_06_80044A4C(void);
void func_ovl0C_06_80044AB0(void);
void func_ovl0C_06_80044B10(void);
void func_ovl0C_06_80044B60(void);
void func_ovl0C_06_80044BC8(void);
void func_ovl0C_06_80044C0C(void);
void func_ovl0C_06_80044C88(UnkStruct_ovl0C_06_80048F10 *arg0);
void func_ovl0C_06_80044CE4(s32 arg0);
void func_ovl0C_06_80044DA0(void);
void func_ovl0C_06_80044F44(void);
static void func_ovl0C_06_8004508C(void);
void func_ovl0C_06_80045094(void);
void func_ovl0C_06_800450D4(void);
void func_ovl0C_06_8004510C(void);
void func_ovl0C_06_80045364(s32 arg0);
void func_ovl0C_06_80045524(void);
void func_ovl0C_06_800455DC(void);
void func_ovl0C_06_80045874(UnkStructA *arg0);
void func_ovl0C_06_800458A0(void *arg0);
void func_ovl0C_06_800458D8(void);
void func_ovl0C_06_80045BA0(void);
void func_ovl0C_06_80045F44(void);
void func_ovl0C_06_80045FC8(void);
void func_ovl0C_06_80046160(void *arg0);
void func_ovl0C_06_80046198(void);
void func_ovl0C_06_80046200(s32 arg0, UnkStructA *arg1, UnkStructA *arg2, f32 arg3);
void func_ovl0C_06_80046288(void);
void func_ovl0C_06_8004696C(void);
void func_ovl0C_06_80046BD8(void);
void func_ovl0C_06_80046CF0(void);
void func_ovl0C_06_80046E14(UnkStruct_ovl0C_06_80048F88 *arg0, UnkStructA *arg1, UnkStructA *arg2);
void func_ovl0C_06_80046EB0(UnkStruct_ovl0C_06_80048F88 *arg0, UnkStructA *arg1);
void func_ovl0C_06_80046FFC(void);
void func_ovl0C_06_80047490(UnkStructA *arg0);
void func_ovl0C_06_80047550(UnkStructA *arg0);
void func_ovl0C_06_80047594(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_ovl0C_06_8004766C(void);
void func_ovl0C_06_8004777C(s32 arg0, UnkStructA *arg1);
void func_ovl0C_06_800477B0(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0C_06_8004780C(void);
void func_ovl0C_06_80047824(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (as in ovl_0C_04, ovl_0C_07 and ovl_0C_09). */
#define UNK_MACRO_ovl0C_06_80043820() \
    D_ovl0C_06_8004938C = func_ovl0C_06_80047D98(); func_ovl0C_06_80047D78(&D_ovl0C_06_80049380); func_ovl0C_06_80047DA0(D_ovl0C_06_8004938C, D_ovl0C_06_80049370)

/* func_ovl0C_06_80046200's body, written out where the mover drops its
 * object: the mover's frame has no room for its parameters (as in
 * ovl_0C_09) */
#define UNK_MACRO_ovl0C_06_80046200(flag, a, b, f)                             \
    fl = (flag);                                                               \
    if (fl & 1) {                                                              \
        func_ovl0C_06_80048C90(0x4C);                                          \
        func_ovl0C_06_80048598(a, b);                                          \
        func_ovl0C_06_800485B8(b, 0x200000);                                   \
        (b)->unk4C = 0.0f;                                                     \
        (b)->unk50 = f;                                                        \
        (b)->unk54 = 0.0f;                                                     \
    } else {                                                                   \
        func_ovl0C_06_80048C90(0x4C);                                          \
        func_ovl0C_06_80048590(b);                                             \
        func_ovl0C_06_800485C0(b, 0x200000);                                   \
    }

/* .bss */
u8 D_ovl0C_06_80049370[0x10];
Vec3f D_ovl0C_06_80049380;
s32 D_ovl0C_06_8004938C;
u8 D_ovl0C_06_80049390[0x4];
s32 D_ovl0C_06_80049394;
s32 D_ovl0C_06_80049398;
u8 D_ovl0C_06_8004939C[0x4];
Vec3f D_ovl0C_06_800493A0;
UnkStructA *D_ovl0C_06_800493AC;
UnkStruct_ovl0C_06_800493B0 D_ovl0C_06_800493B0;
UnkStructA *D_ovl0C_06_800493C4;
UnkStructA *D_ovl0C_06_800493C8[2];

/* .data */
/* passed to func_ovl0C_06_80048A70: three 12-byte records */
u32 D_ovl0C_06_80048EB0[][3] = {
    { 0x910002, 0x2000E, 4 },
    { 0x940002, 0xE, 4 },
    { 0x950000, 0xE, 4 },
};
/* passed to func_ovl0C_06_80048A88 */
u32 D_ovl0C_06_80048ED4[][3] = {
    { 0, 4, 0 },
    { 4, 0x960000, 0x84 },
};
/* three 12-byte records, each passed to func_ovl0C_06_80048C18 */
u32 D_ovl0C_06_80048EEC[][3] = {
    { 0, 0, 0xDE },
    { 1, 0x22, 0xE0 },
    { 2, 5, 0x34F },
};
UnkStruct_ovl0C_06_80048F10 D_ovl0C_06_80048F10[] = {
    { 0, NULL, 1550.0f, 0.0f, 200.0f, 0x80, 1550.0f, 0.0f, 250.0f, 0xF, 0, 1, 0x10, 1, 4, 0xF, 0, 1, 0x10, 1,
      0xE, 0, 3, 0x1C, 0x11, 0x11, 0, 3, 0x17, 0x11 },
};
UnkStruct_ovl0C_06_80048F88 D_ovl0C_06_80048F88[] = {
    { 0, 0, 0, NULL, NULL, 3150.0f, 100.0f, 850.0f, 100.0f, 700.0f, 3150.0f, 0.0f, 850.0f, 43.5f,
      0x1F, 1, 8, 0x20, 4, 9, 0x40, 0, 0 },
};
UnkStruct_ovl0C_06_80048FD0 D_ovl0C_06_80048FD0[] = {
    { NULL, 1550.0f, 0.0f, 1550.0f, 0.0f, -400.0f, 1550.0f, 1550.0f },
    { NULL, 4350.0f, 1000.0f, 250.0f, 1000.0f, -400.0f, 4350.0f, 250.0f },
    { NULL, 4350.0f, 1000.0f, 250.0f, 1000.0f, -400.0f, 4350.0f, 250.0f },
};
UnkStruct_ovl0C_06_80049030 D_ovl0C_06_80049030[] = {
    { 0, NULL, 0x2E, 0x13, 12.0f, 0.0f, 35.0f, 1.0f, 1, 0x43A,
      550.0f, 1000.0f, 1550.0f, 1050.0f, 1550.0f, 2550.0f, 1550.0f },
    { 1, NULL, 0x2E, 0x14, 0.0f, -12.0f, 35.0f, 1.0f, 2, 0x437,
      2650.0f, 1500.0f, 1950.0f, 4350.0f, 550.0f, 435.0f, -300.0f },
    { 2, NULL, 0x30, 0x13, 0.0f, -12.0f, 35.0f, 1.0f, 1, 0x436,
      4350.0f, 1800.0f, 250.0f, 4350.0f, 650.0f, 435.0f, -300.0f },
};
UnkStruct_ovl0C_06_800490FC D_ovl0C_06_800490FC[] = {
    { 0, 1, NULL, 4350.0f, 200.0f, 1450.0f, 450.0f, 0x2B, 3, 0xE, 1, 0, 0, 0x43C },
    { 1, 0, NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0 },
};
UnkStruct_ovl0C_06_8004914C D_ovl0C_06_8004914C[] = {
    { 0, 1, NULL, 4350.0f, 700.0f, 1050.0f, 700.0f, 0x2A, 4, 8, 3, NULL, 1, 0 },
    { 1, 2, NULL, 4350.0f, 700.0f, 1350.0f, 700.0f, 0x2A, 4, 0xB, 3, NULL, 1, 0 },
    { 2, 3, NULL, 4350.0f, 700.0f, 1650.0f, 700.0f, 0x2A, 4, 0xE, 3, D_ovl0C_06_800490FC, 1, 0 },
    { 3, 4, NULL, 4350.0f, 700.0f, 1950.0f, 700.0f, 0x2A, 4, 0x11, 3, NULL, 1, 0 },
    { 4, 5, NULL, 4350.0f, 700.0f, 2250.0f, 700.0f, 0x2A, 4, 0x14, 3, NULL, 1, 0 },
    { 5, 6, NULL, 4350.0f, 700.0f, 2549.9f, 700.0f, 0x2A, 4, 0x17, 3, NULL, 1, 0 },
    { 6, 0, NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, NULL, 1, 0 },
};
UnkStruct_ovl0C_06_80049264 D_ovl0C_06_80049264 = { NULL, 4350.0f, 700.0f, 1050.0f };
UnkStruct_ovl0C_06_80049274 D_ovl0C_06_80049274 = {
    NULL, -1, 0x2B8, -5, -0x400, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
};
UnkStruct_ovl0C_06_80049264 D_ovl0C_06_800492AC = { NULL, 300.0f, 200.0f, 1600.0f };

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0C_06_80047864(void) {
}
static void func_ovl0C_06_8004785C(void) {
}
static void func_ovl0C_06_80047854(void) {
}
static void func_ovl0C_06_8004784C(void) {
}
static void func_ovl0C_06_80047844(void) {
}
static void func_ovl0C_06_8004783C(void) {
}
static void func_ovl0C_06_80047834(void) {
}
static void func_ovl0C_06_8004782C(void) {
}

void func_ovl0C_06_80047824(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl0C_06_80049390[0] = D_ovl0C_06_8004939C[0];
    }
}

void func_ovl0C_06_8004780C(void) {
    D_ovl0C_06_80049394 = -1;
    D_ovl0C_06_80049398 = -1;
}

void func_ovl0C_06_800477B0(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_06_800483F8(D_ovl0C_06_800493A0.x, D_ovl0C_06_800493A0.y, D_ovl0C_06_800493A0.z);
    func_ovl0C_06_80048418(arg0, arg1, arg2);
    func_ovl0C_06_80048728(180);
}

void func_ovl0C_06_8004777C(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_06_80048CB0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_06_8004766C(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_06_80048730();
    func_ovl0C_06_80048CB0(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_06_800485E0(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_06_80047594(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_06_80048750();
    }
    func_ovl0C_06_800485D0(obj);
    func_ovl0C_06_80048718();
}

void func_ovl0C_06_80047594(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0C_06_800488B0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_06_800488B0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_06_80047550(UnkStructA *arg0) {
    func_ovl0C_06_800485C0(arg0, 0x01000000);
    func_ovl0C_06_80048708(func_ovl0C_06_8004766C, arg0, 0, 0, 0x150);
}

void func_ovl0C_06_80047490(UnkStructA *arg0) {
    func_ovl0C_06_80048728(10);
    func_ovl0C_06_80047C40(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_06_80048728(60);
}

/* a lift: rises while something stands on it, falls back otherwise */
void func_ovl0C_06_80046FFC(void) {
    UnkStruct_ovl0C_06_80048F88 *rec;
    UnkStructA *obj;
    UnkStructA *player;
    s16 wait;

    rec = func_ovl0C_06_80048730();
    obj = rec->unk8;
    player = func_ovl0C_06_80047DF8(0);
    obj->unk68 = 0.0f;
    wait = 2;
    obj->unk70 = 1.6333334f;
    while (TRUE) {
        D_ovl0C_06_800493C4->unk30 = 4;
        D_ovl0C_06_800493C4->unk34 = 100.0f;
        D_ovl0C_06_800493C4->unk38 = 100.0f;
        D_ovl0C_06_800493C4->unk40->unk10 = rec->unk24;
        D_ovl0C_06_800493C4->unk40->unk14 = rec->unk28;
        D_ovl0C_06_800493C4->unk40->unk18 = rec->unk2C;
        func_ovl0C_06_800486C8(rec->unkC);
        if (func_ovl0C_06_80048568(D_ovl0C_06_800493C4, 2) != 0) {
            wait = 2;
            rec->unk44 |= 1;
        } else if (wait == 0) {
            rec->unk44 &= ~1;
        } else {
            wait--;
        }
        if (func_ovl0C_06_80048568(D_ovl0C_06_800493C4, 0x40) != 0 && (rec->unk44 & 1)) {
            func_ovl0C_06_80047BF8(rec->unk34, rec->unk36, rec->unk38, rec->unk3A, rec->unk3E, 0x10);
            func_ovl0C_06_800485C0(rec->unkC, 0x100);
            obj->unk68 = rec->unk30;
        }
        if (obj->unk40->unk14 - obj->unk6C + obj->unk68 <= rec->unk1C) {
            obj->unk6C = 0.0f;
            obj->unk68 = 0.0f;
            obj->unk40->unk14 = rec->unk1C;
            func_ovl0C_06_800485B8(rec->unkC, 0x100);
        } else {
            obj->unk40->unk14 += obj->unk68;
            obj->unk40->unk14 -= obj->unk6C;
            if (obj->unk6C <= 99.0f) {
                obj->unk6C += obj->unk70;
            } else {
                obj->unk6C = 99.0f;
            }
        }
        if (obj->unk40->unk14 - obj->unk6C + obj->unk68 <= rec->unk1C + 100.0f &&
            obj->unk40->unk14 < player->unk40->unk14 && obj->unk68 == 0) {
            func_ovl0C_06_80047BF8(rec->unk34, rec->unk36, rec->unk38, rec->unk3A, rec->unk3E, 0x11);
        }
        if (rec->unk44 & 2) {
            player->unk6C = 0;
        }
        func_ovl0C_06_80046EB0(rec, obj);
        if (obj->unk6C == 0 && obj->unk68 == 0) {
            func_ovl0C_06_80047BF8(rec->unk34, rec->unk36, rec->unk38, rec->unk3A, rec->unk3E, 0x11);
            if (rec->unk44 & 2) {
                func_ovl0C_06_80048750();
                rec->unk44 &= ~2;
                func_ovl0C_06_80045874(player);
                func_ovl0C_06_80047DA8(0);
            }
        }
        if (rec->unk20 < obj->unk40->unk14) {
            func_ovl0C_06_80047BF8(rec->unk34, rec->unk3C, rec->unk38, rec->unk3A, rec->unk3E, 0x11);
            func_ovl0C_06_80048750();
            if (rec->unk44 & 2) {
                func_ovl0C_06_80046E14(rec, obj, player);
            }
            func_ovl0C_06_80048728(60);
            obj->unk40->unk14 = rec->unk20;
            obj->unk6C = 0.0f;
            obj->unk68 = 0.0f;
            player->unk6C = 0.0f;
            player->unk68 = 0.0f;
            func_ovl0C_06_80047BF8(rec->unk34, rec->unk3C, rec->unk38, rec->unk3A, rec->unk3E, 0x10);
        }
        func_ovl0C_06_80048750();
    }
}

void func_ovl0C_06_80046EB0(UnkStruct_ovl0C_06_80048F88 *arg0, UnkStructA *arg1) {
    UnkStructA *player;

    if (arg1->unk68 != 0.0f && func_ovl0C_06_80048568(arg1, 1) != 0) {
        player = func_ovl0C_06_80047DF8(0);
        if (arg0->unk14 + 100.0f <= player->unk40->unk14 &&
            player->unk40->unk10 < arg0->unk10 + 100.0f && arg0->unk10 - 100.0f < player->unk40->unk10 &&
            player->unk40->unk18 < arg0->unk18 + 100.0f && arg0->unk18 - 100.0f < player->unk40->unk18) {
            func_ovl0C_06_80047DA8(1);
            func_ovl0C_06_80048598(arg1, player);
            func_ovl0C_06_800485B8(player, 0x200000);
            player->unk4C = player->unk40->unk10 - arg0->unk10;
            player->unk50 = 100.0f;
            player->unk54 = player->unk40->unk18 - arg0->unk18;
            arg0->unk44 |= 2;
        }
    }
}

void func_ovl0C_06_80046E14(UnkStruct_ovl0C_06_80048F88 *arg0, UnkStructA *arg1, UnkStructA *arg2) {
    f32 pos[3];

    arg0->unk44 &= ~2;
    pos[0] = arg2->unk40->unk10;
    pos[1] = arg2->unk40->unk14;
    pos[2] = arg2->unk40->unk18;
    func_ovl0C_06_80048BA8(pos);
    func_ovl0C_06_80048C78();
    func_ovl0C_06_80045874(arg2);
    func_ovl0C_06_80048750();
    func_ovl0C_06_80047DA8(0);
}

/* a switch fading out with its block: its tiles open */
void func_ovl0C_06_80046CF0(void) {
    UnkStruct_ovl0C_06_800490FC *rec;
    s16 alpha;

    rec = func_ovl0C_06_80048730();
    alpha = 0xFF;
    while (TRUE) {
        alpha -= 0xA;
        func_ovl0C_06_800485B8(rec->unk4, 0x80000);
        if (alpha < 0) {
            alpha = 0;
            func_ovl0C_06_800485C0(rec->unk4, 0x01000000);
            func_ovl0C_06_80047C00(rec->unk18, rec->unk1A, rec->unk1C, rec->unk18 + 1, rec->unk1E + 1, rec->unk1C + 1, 0x10);
            func_ovl0C_06_80047BF8(rec->unk18, rec->unk1E, rec->unk1C, rec->unk18 + 1, rec->unk1C + 1, 0x11);
            rec->unk22 = 0;
            func_ovl0C_06_800485D0(rec->unk4);
            func_ovl0C_06_80048718();
        }
        rec->unk4->unk40->unk36 = alpha;
        func_ovl0C_06_80048750();
    }
}

/* the switches' sparks, each on its own random timer */
void func_ovl0C_06_80046BD8(void) {
    UnkStruct_ovl0C_06_800490FC *list;
    UnkStruct_ovl0C_06_800490FC *p;

    list = func_ovl0C_06_80048730();
    for (p = list; p->unk2 != 0; p++) {
        p->unk20 = func_ovl0C_06_800488C8(5) + 0x14;
        p->unk22 = 1;
    }
    while (TRUE) {
        for (p = list; p->unk2 != 0; p++) {
            if (p->unk20-- <= 0 && p->unk22 == 1) {
                func_ovl0C_06_80048B58(0xF, p->unk8 - 100.0f, p->unk14, p->unk10, 0);
                func_ovl0C_06_80048C90(0x4A);
                p->unk20 = func_ovl0C_06_800488C8(5) + 0x14;
            }
        }
        func_ovl0C_06_80048750();
    }
}

/* a block crumbling: it sinks, fades, and its smoke rises */
void func_ovl0C_06_8004696C(void) {
    UnkStruct_ovl0C_06_8004914C *rec;
    UnkStructA *obj;
    s16 alpha;

    rec = func_ovl0C_06_80048730();
    obj = rec->unk4;
    if (rec->unk20 != NULL) {
        func_ovl0C_06_80048708(func_ovl0C_06_80046CF0, rec->unk20, 0, 0, 0x110);
    }
    func_ovl0C_06_80047BF8(rec->unk18, rec->unk1A, rec->unk1C, rec->unk18 + 3, rec->unk1C + 2, 0x10);
    func_ovl0C_06_80047BF8(rec->unk18, rec->unk1E, rec->unk1C, rec->unk18 + 3, rec->unk1C + 2, 0x10);
    if (rec->unk24 == 1) {
        func_ovl0C_06_80047BF8(0x2B, 3, 0xB, 0x2D, 0x12, 0x11);
        func_ovl0C_06_80047BF8(0x2C, 3, 0xC, 0x2D, 0x11, 0x10);
        func_ovl0C_06_80047BF8(0x2B, 3, 0xE, 0x2B, 0xF, 0x10);
    }
    while (TRUE) {
        obj->unk40->unk1C -= 5.0f;
        if (obj->unk40->unk1C < -50.0f) {
            break;
        }
        func_ovl0C_06_80048750();
    }
    func_ovl0C_06_800485B8(obj, 0x80000);
    alpha = 0xFF;
    while (TRUE) {
        alpha -= 0xA;
        if (alpha < 0) {
            alpha = 0;
        }
        obj->unk40->unk36 = alpha;
        func_ovl0C_06_80048638(obj);
        if (obj->unk6C == 0.0f && obj->unk68 == 0.0f) {
            func_ovl0C_06_80048B58(0x10, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
            func_ovl0C_06_800485C0(obj, 0x01000000);
            func_ovl0C_06_80048718();
        }
        func_ovl0C_06_80048750();
    }
}

/* a mover on x and z: carries D_ovl0C_06_80048FD0[rec->unk0]'s object
 * across, then drops it */
void func_ovl0C_06_80046288(void) {
    UnkStruct_ovl0C_06_80049030 *rec;
    UnkStructA *obj;
    UnkStructA *other;
    UnkStruct_ovl0C_06_80048FD0 *lim;
    s16 done;
    f32 dist;
    s32 fl;

    rec = func_ovl0C_06_80048730();
    obj = rec->unk4;
    obj->unk68 = rec->unk18;
    obj->unk70 = rec->unk1C;
    lim = &D_ovl0C_06_80048FD0[rec->unk0];
    other = lim->unk0;
    done = FALSE;
    func_ovl0C_06_80047E00(1);
    func_ovl0C_06_80048CB0(0x48, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
    while (TRUE) {
        obj->unk40->unk10 += rec->unk10;
        obj->unk40->unk18 += rec->unk14;
        if (rec->unk10 != 0) {
            if (rec->unk10 > 0) {
                if (rec->unk34 <= obj->unk40->unk10) {
                    break;
                }
            } else if (obj->unk40->unk10 <= rec->unk34) {
                break;
            }
        }
        if (rec->unk14 != 0) {
            if (rec->unk14 > 0) {
                if (rec->unk38 <= obj->unk40->unk18) {
                    break;
                }
            } else if (obj->unk40->unk18 <= rec->unk38) {
                break;
            }
        }
        func_ovl0C_06_80048750();
    }
    while (TRUE) {
        if (rec->unk2C <= obj->unk40->unk14 + obj->unk6C - obj->unk68) {
            break;
        }
        obj->unk40->unk14 -= obj->unk68;
        obj->unk40->unk14 += obj->unk6C;
        if (obj->unk6C <= 99.0f) {
            obj->unk6C += obj->unk70;
        } else {
            obj->unk6C = 99.0f;
        }
        obj->unk40->unk10 += rec->unk10;
        obj->unk40->unk18 += rec->unk14;
        if (done == FALSE) {
            dist = lim->unk14;
            if (rec->unk10 != 0) {
                if (rec->unk10 > 0) {
                    if (lim->unk18 < obj->unk40->unk10) {
                        done = TRUE;
                        UNK_MACRO_ovl0C_06_80046200(rec->unk20, obj, other, dist);
                    }
                } else if (obj->unk40->unk10 < lim->unk18) {
                    done = TRUE;
                    UNK_MACRO_ovl0C_06_80046200(rec->unk20, obj, other, dist);
                }
            }
            if (rec->unk14 != 0) {
                if (rec->unk14 > 0) {
                    if (lim->unk1C < obj->unk40->unk18) {
                        done = TRUE;
                        UNK_MACRO_ovl0C_06_80046200(rec->unk20, obj, other, dist);
                    }
                } else if (obj->unk40->unk18 < lim->unk1C) {
                    done = TRUE;
                    UNK_MACRO_ovl0C_06_80046200(rec->unk20, obj, other, dist);
                }
            }
        }
        func_ovl0C_06_80048750();
    }
    done = FALSE;
    while (TRUE) {
        if (rec->unk10 != 0) {
            if (rec->unk10 > 0) {
                if (rec->unk3C <= obj->unk40->unk10) {
                    done = TRUE;
                }
            } else if (obj->unk40->unk10 <= rec->unk3C) {
                done = TRUE;
            }
        }
        if (rec->unk14 != 0) {
            if (rec->unk14 > 0) {
                if (rec->unk40 <= obj->unk40->unk18) {
                    done = TRUE;
                }
            } else if (obj->unk40->unk18 <= rec->unk40) {
                done = TRUE;
            }
        }
        if (done == TRUE) {
            func_ovl0C_06_80047DA8(0);
            func_ovl0C_06_80048980(rec->unk24);
            if (func_ovl0C_06_80048990(0x431) == 0) {
                func_ovl0C_06_80047CB0(rec->unk8, rec->unkC, 0);
            } else {
                func_ovl0C_06_80048E08();
            }
            func_ovl0C_06_80048718();
        }
        obj->unk40->unk10 += rec->unk10;
        obj->unk40->unk18 += rec->unk14;
        func_ovl0C_06_80048750();
    }
}

void func_ovl0C_06_80046200(s32 arg0, UnkStructA *arg1, UnkStructA *arg2, f32 arg3) {
    if (arg0 & 1) {
        func_ovl0C_06_80048C90(0x4C);
        func_ovl0C_06_8004394C(arg1, arg2, arg3);
    } else {
        func_ovl0C_06_80048C90(0x4C);
        func_ovl0C_06_80045874(arg2);
    }
}

void func_ovl0C_06_80046198(void) {
    UnkStructA *obj;

    obj = *(UnkStructA **) func_ovl0C_06_80048730();
    obj->unk68 = 0.0f;
    obj->unk70 = 1.6333334f;
    while (TRUE) {
        func_ovl0C_06_80048638(obj);
        func_ovl0C_06_80048750();
    }
}

void func_ovl0C_06_80046160(void *arg0) {
    func_ovl0C_06_80048708(func_ovl0C_06_80046288, arg0, 0, 0, 0x110);
}

void func_ovl0C_06_80045FC8(void) {
    UnkStruct_ovl0C_06_80048F10 *rec;
    UnkStructA_40 *p;

    rec = func_ovl0C_06_80048730();
    p = rec->unk4->unk40;
    D_ovl0C_06_800493C8[rec->unk0]->unkC = 0x40;
    while (TRUE) {
        if (D_ovl0C_06_800493C8[rec->unk0]->unk10 & 0x40) {
            func_ovl0C_06_80048980(0x429);
            func_ovl0C_06_80048C90(0x53);
            p->unk48->unk4->unk4 = func_ovl0C_06_800482F8(p, 0) - 0.01f;
            while (p->unk48->unk4->unk4 > 1.0f) {
                func_ovl0C_06_80048750();
                p->unk48->unk4->unk4 -= 1.0f;
            }
            p->unk48->unk4->unk4 = 0.0f;
            func_ovl0C_06_80044164(rec);
            func_ovl0C_06_80048718();
        }
        func_ovl0C_06_80048750();
    }
}

void func_ovl0C_06_80045F44(void) {
    UnkStructA *obj;
    s32 alpha;
    s32 step;

    func_ovl0C_06_80047DA8(1);
    func_ovl0C_06_80048728(10);
    obj = func_ovl0C_06_80047DF8(func_ovl0C_06_80047D98());
    func_ovl0C_06_80048C90(0x44);
    func_ovl0C_06_800485B8(obj, 0x80000);
    step = 0x11;
    for (alpha = 0xFF; alpha > 0; alpha -= step) {
        obj->unk40->unk36 = alpha;
        func_ovl0C_06_80048750();
    }
    obj->unk40->unk36 = 0;
    func_ovl0C_06_80048718();
}

/* mover 0: swings its object round on a circle, drops limit 0's object
 * on the way */
void func_ovl0C_06_80045BA0(void) {
    UnkStructA *obj;
    UnkStructA *other;
    f32 lim;
    f32 cx;
    f32 cz;
    f32 a;
    s32 snd;
    s32 dropped;
    s32 vol;

    func_ovl0C_06_800458A0(&D_ovl0C_06_80048FD0[0]);
    obj = D_ovl0C_06_80049030[0].unk4;
    snd = func_ovl0C_06_80048C90(0x4E);
    obj->unk68 = D_ovl0C_06_80049030[0].unk18 * 0.75f;
    obj->unk70 = D_ovl0C_06_80049030[0].unk1C * 0.5f;
    dropped = 0;
    cx = obj->unk40->unk10 - 30.0f;
    a = 0.0f;
    cz = obj->unk40->unk18 - 600.0f;
    while (TRUE) {
        if (D_ovl0C_06_80049030[0].unk2C <= obj->unk40->unk14 + obj->unk6C - obj->unk68) {
            break;
        }
        obj->unk40->unk14 -= obj->unk68;
        obj->unk40->unk14 += obj->unk6C;
        if (obj->unk6C <= 99.0f) {
            obj->unk6C += obj->unk70;
        } else {
            obj->unk6C = 99.0f;
        }
        if (dropped == 0 && D_ovl0C_06_80048FD0[0].unk18 < obj->unk40->unk10) {
            lim = D_ovl0C_06_80048FD0[0].unk14;
            dropped = 1;
            func_ovl0C_06_80048C90(0x4C);
            other = D_ovl0C_06_80048FD0[0].unk0;
            func_ovl0C_06_80048598(obj, other);
            func_ovl0C_06_800485B8(other, 0x200000);
            other->unk4C = 0.0f;
            other->unk50 = lim;
            other->unk54 = 0.0f;
        }
        obj->unk40->unk10 = func_ovl0C_06_800488B0(a) * 1200.0f + cx;
        obj->unk40->unk18 = func_ovl0C_06_800488B8(a) * 1200.0f + cz;
        obj->unk40->unk20 = a + 90.0f;
        func_ovl0C_06_80048750();
        a += 0.85f;
    }
    vol = 0x7F;
    while (obj->unk40->unk10 > 1500.0f) {
        obj->unk40->unk10 = func_ovl0C_06_800488B0(a) * 1200.0f + cx;
        obj->unk40->unk18 = func_ovl0C_06_800488B8(a) * 1200.0f + cz;
        obj->unk40->unk20 = a + 90.0f;
        if (vol > 0) {
            vol -= 5;
            func_ovl0C_06_80048CC8(snd, vol);
        } else {
            func_ovl0C_06_80048CC8(snd, 0);
        }
        func_ovl0C_06_80048750();
        a += 0.85f;
    }
    func_ovl0C_06_80048CC0(snd);
    func_ovl0C_06_80048980(D_ovl0C_06_80049030[0].unk24);
    func_ovl0C_06_80047CB0(D_ovl0C_06_80049030[0].unk8, D_ovl0C_06_80049030[0].unkC, 0);
    while (TRUE) {
        func_ovl0C_06_80048750();
    }
}

/* mover 1: carries limit 1's object along x and z, then drops it */
void func_ovl0C_06_800458D8(void) {
    UnkStructA *obj;
    s32 snd;
    s32 vol;

    func_ovl0C_06_80047D28(1);
    func_ovl0C_06_80047D20(0);
    func_ovl0C_06_80047DA8(1);
    func_ovl0C_06_80048460(0x7F);
    func_ovl0C_06_800483F8(2650.0f, 1500.0f, 1950.0f);
    func_ovl0C_06_80048418(0.0f, 45.0f, 2000.0f);
    func_ovl0C_06_800458A0(&D_ovl0C_06_80048FD0[1]);
    obj = D_ovl0C_06_80049030[1].unk4;
    snd = func_ovl0C_06_80048C90(0x4E);
    obj->unk40->unk20 = 135.0f;
    while (obj->unk40->unk10 < 4350.0f) {
        obj->unk40->unk10 += 7.0f;
        obj->unk40->unk18 -= 7.0f;
        func_ovl0C_06_800483F8(obj->unk40->unk10, 1500.0f, obj->unk40->unk18);
        func_ovl0C_06_80048750();
    }
    obj->unk40->unk10 = 4350.0f;
    D_ovl0C_06_80048FD0[1].unk0->unk6C = 0.0f;
    func_ovl0C_06_80048C90(0x4C);
    func_ovl0C_06_80045874(D_ovl0C_06_80048FD0[1].unk0);
    vol = 0x7F;
    while (obj->unk40->unk10 < 5000.0f) {
        obj->unk40->unk10 += 7.0f;
        obj->unk40->unk14 += 10.0f;
        obj->unk40->unk18 -= 7.0f;
        if (vol > 0) {
            vol -= 2;
            func_ovl0C_06_80048CC8(snd, vol);
        } else {
            func_ovl0C_06_80048CC8(snd, 0);
        }
        func_ovl0C_06_80048750();
    }
    func_ovl0C_06_80048CC0(snd);
    func_ovl0C_06_80048980(D_ovl0C_06_80049030[1].unk24);
    func_ovl0C_06_80047CB0(D_ovl0C_06_80049030[1].unk8, D_ovl0C_06_80049030[1].unkC, 0);
    while (TRUE) {
        func_ovl0C_06_80048750();
    }
}

void func_ovl0C_06_800458A0(void *arg0) {
    func_ovl0C_06_80048708(func_ovl0C_06_80046198, arg0, 0, 0, 0x110);
}

void func_ovl0C_06_80045874(UnkStructA *arg0) {
    func_ovl0C_06_80048590(arg0);
    func_ovl0C_06_800485C0(arg0, 0x200000);
}

/* mover 2: lifts its object up, then the camera follows it */
void func_ovl0C_06_800455DC(void) {
    UnkStructA *obj;
    UnkStructA *lim;
    f32 dy;
    f32 pitch;

    obj = D_ovl0C_06_80049030[2].unk4;
    func_ovl0C_06_80048CB0(0x48, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
    obj->unk40->unk20 = -45.0f;
    while (obj->unk40->unk14 > 1400.0f) {
        obj->unk40->unk14 -= 5.0f;
        func_ovl0C_06_80048750();
    }
    obj->unk40->unk14 = 1400.0f;
    func_ovl0C_06_80048C90(0x4C);
    lim = D_ovl0C_06_80048FD0[2].unk0;
    func_ovl0C_06_80048598(obj, lim);
    func_ovl0C_06_800485B8(lim, 0x200000);
    dy = 0.0f;
    lim->unk4C = 0.0f;
    lim->unk54 = 0.0f;
    lim->unk50 = -400.0f;
    pitch = 45.0f;
    while (obj->unk40->unk14 < 2000.0f) {
        obj->unk40->unk14 += 10.0f;
        dy -= 10.0f;
        func_ovl0C_06_800483F8(4300.0f, 1000.0f - dy, 200.0f);
        func_ovl0C_06_80048418(-45.0f, pitch, 2000.0f);
        func_ovl0C_06_80048750();
        pitch -= 1.0f;
    }
    while (obj->unk40->unk14 < 2700.0f) {
        obj->unk40->unk14 += 10.0f;
        func_ovl0C_06_80048750();
    }
    func_ovl0C_06_80048980(D_ovl0C_06_80049030[2].unk24);
    func_ovl0C_06_80047CB0(D_ovl0C_06_80049030[2].unk8, D_ovl0C_06_80049030[2].unkC, 0);
    while (TRUE) {
        func_ovl0C_06_80048750();
    }
}

/* the camera of the blocks' cut scene */
void func_ovl0C_06_80045524(void) {
    s32 i;

    func_ovl0C_06_80047D20(0);
    func_ovl0C_06_80048518();
    func_ovl0C_06_80048460(0x7F);
    func_ovl0C_06_800483F8(4500.0f, 200.0f, 1750.0f);
    func_ovl0C_06_80048418(225.0f, 45.0f, 2400.0f);
    for (i = 0; i < 360; i++) {
        func_ovl0C_06_80048750();
    }
    func_ovl0C_06_8004491C();
    func_ovl0C_06_80047D20(1);
    func_ovl0C_06_80048718();
}

/* the stage's event handler (the overlay's entry returns it) */
void func_ovl0C_06_80045364(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0C_06_8004510C();
            break;
        case 0x10:
            func_ovl0C_06_80044BC8();
            break;
        case 0x11:
            func_ovl0C_06_80044B60();
            break;
        case 0x12:
            func_ovl0C_06_80044B10();
            break;
        case 0x13:
            func_ovl0C_06_80044AB0();
            break;
        case 0x14:
            func_ovl0C_06_80044A4C();
            break;
        case 0x15:
            func_ovl0C_06_800449F0();
            break;
        case 0x16:
            func_ovl0C_06_800449C8();
            break;
        case 0x17:
            func_ovl0C_06_80044950();
            break;
        case 0x18:
            func_ovl0C_06_800448D4();
            break;
        case 0x19:
            func_ovl0C_06_80044884();
            break;
        case 0x1A:
            func_ovl0C_06_80044830();
            break;
        case 4:
            func_ovl0C_06_800446FC();
            break;
        case 5:
            func_ovl0C_06_800440B4();
            break;
        case 0x50:
            func_ovl0C_06_80043DC0();
            break;
        case 0x52:
            func_ovl0C_06_80043B3C();
            break;
        case 0x53:
            break;
        case 3:
            func_ovl0C_06_80043868();
            break;
        case 0xF:
            func_ovl0C_06_800431B8();
            break;
        case 0xC:
            func_ovl0C_06_80043020();
            break;
        case 1:
            func_ovl0C_06_80043010();
            break;
    }
}

/* the stage's setup (ovl_0C_07's, with the sign) */
void func_ovl0C_06_8004510C(void) {
    UnkStruct_ovl0C_06_80049274 *rec;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0C_06_800450D4();
    func_ovl0C_06_80048A70(D_ovl0C_06_80048EB0);
    func_ovl0C_06_80048A88(D_ovl0C_06_80048ED4);
    func_ovl0C_06_80047BB8(0x247);
    p = D_ovl0C_06_80048EEC;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl0C_06_80048C18((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0C_06_80047BD0(0x251);
    func_ovl0C_06_80047D68();
    func_ovl0C_06_8004508C();
    func_ovl0C_06_80044F44();
    func_ovl0C_06_80044DA0();
    rec = &D_ovl0C_06_80049274;
    rec->unk0 = func_ovl0C_06_80048600(rec->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0C_06_800485B8(rec->unk0, 0x01080000);
    func_ovl0C_06_800485C0(rec->unk0, 0x02000000);
    if (rec->unkC != -1 && rec->unkE != -1 && rec->unk10 != -1 && rec->unk12 != -1) {
        rec->unk4 = func_ovl0C_06_80048300(rec->unk0->unk40, 0, rec->unkC, rec->unkE, rec->unk10, rec->unk12);
        if (rec->unk4 == -1) {
            for (;;) {
            }
        }
    }
    rec->unk0->unk40->unk10 = rec->unk14 * 10.0f;
    rec->unk0->unk40->unk14 = rec->unk18 * 10.0f;
    rec->unk0->unk40->unk18 = rec->unk1C * 10.0f;
    rec->unk0->unk40->unk1C = rec->unk20;
    rec->unk0->unk40->unk20 = rec->unk24;
    rec->unk0->unk40->unk24 = rec->unk28;
    rec->unk0->unk40->unk28 = rec->unk2C;
    rec->unk0->unk40->unk2C = rec->unk30;
    rec->unk0->unk40->unk30 = rec->unk34;
    func_ovl0C_06_80044C0C();
}

void func_ovl0C_06_800450D4(void) {
    func_ovl0C_06_80045094();
    func_ovl0C_06_80047CA0(func_ovl0C_06_80047550);
    func_ovl0C_06_80047CF0(func_ovl0C_06_80047490);
}

void func_ovl0C_06_80045094(void) {
    func_ovl0C_06_80048988(0x400);
    func_ovl0C_06_80048988(0x401);
    func_ovl0C_06_80048988(0x402);
    func_ovl0C_06_80048988(0x403);
    func_ovl0C_06_80048988(0x404);
}

static void func_ovl0C_06_8004508C(void) {
}

void func_ovl0C_06_80044F44(void) {
    UnkStruct_ovl0C_06_80048F88 *p;
    UnkStructA *obj;
    s16 i;

    func_ovl0C_06_80043060();
    for (i = 0; i < 3; i++) {
        p = &D_ovl0C_06_80048F88[i];
        obj = func_ovl0C_06_80048600(0x2AC, 0xD0, p->unk10, p->unk1C, p->unk18);
        func_ovl0C_06_800485B8(obj, 0x01000000);
        p->unk8 = obj;
        p->unk44 = 0;
        obj->unk30 = 4;
        obj->unk34 = 100.0f;
        obj->unk38 = 100.0f;
        func_ovl0C_06_80047BF8(p->unk34, p->unk36, p->unk38, p->unk3A, p->unk3E, 0x11);
        D_ovl0C_06_80048F88[i].unkC = func_ovl0C_06_800485E0(-1, 0, 0x50, 0);
        D_ovl0C_06_80048F88[i].unkC->unk40->unk10 = D_ovl0C_06_80048F88[i].unk10;
        D_ovl0C_06_80048F88[i].unkC->unk40->unk14 = D_ovl0C_06_80048F88[i].unk1C - 100.0f;
        D_ovl0C_06_80048F88[i].unkC->unk40->unk18 = D_ovl0C_06_80048F88[i].unk18;
    }
}

void func_ovl0C_06_80044DA0(void) {
    UnkStruct_ovl0C_06_80048F10 *p;
    f32 angle;
    UnkStructA *obj;
    s16 i;

    for (i = 0; i < 1; i++) {
        func_ovl0C_06_80044CE4(i);
        p = &D_ovl0C_06_80048F10[i];
        obj = func_ovl0C_06_80048600(0x2A9, 0xD0, p->unk8, p->unkC, p->unk10);
        func_ovl0C_06_800485B8(obj, 0x01000000);
        switch (p->unk14) {
            case 0:
                angle = 270.0f;
                break;
            case 0x40:
                angle = 180.0f;
                break;
            case 0x80:
                angle = 90.0f;
                break;
            case 0xC0:
                angle = 0.0f;
                break;
        }
        obj->unk40->unk20 = angle;
        p->unk4 = obj;
        func_ovl0C_06_80044C88(p);
    }
}

void func_ovl0C_06_80044CE4(s32 arg0) {
    D_ovl0C_06_800493C8[arg0] = func_ovl0C_06_800485E0(-1, 0, 0x20, 0);
    D_ovl0C_06_800493C8[arg0]->unk40->unk10 = D_ovl0C_06_80048F10[arg0].unk18;
    D_ovl0C_06_800493C8[arg0]->unk40->unk14 = D_ovl0C_06_80048F10[arg0].unk1C;
    D_ovl0C_06_800493C8[arg0]->unk40->unk18 = D_ovl0C_06_80048F10[arg0].unk20;
    D_ovl0C_06_800493C8[arg0]->unk30 = 1;
    D_ovl0C_06_800493C8[arg0]->unk34 = 200.0f;
    D_ovl0C_06_800493C8[arg0]->unk38 = 100.0f;
}

void func_ovl0C_06_80044C88(UnkStruct_ovl0C_06_80048F10 *arg0) {
    arg0->unk4->unk40->unk48->unk4->unk4 = func_ovl0C_06_800482F8(arg0->unk4->unk40, 0) - 0.0001f;
    func_ovl0C_06_80043710(arg0);
}

/* the sign by the start */
void func_ovl0C_06_80044C0C(void) {
    UnkStructA *obj;

    obj = func_ovl0C_06_80048600(0x323, 0xC0, D_ovl0C_06_800492AC.unk4, D_ovl0C_06_800492AC.unk8, D_ovl0C_06_800492AC.unkC);
    D_ovl0C_06_800492AC.unk0 = obj;
    obj->unk40->unk20 = 90.0f;
    func_ovl0C_06_800485F0(obj);
    func_ovl0C_06_800485B8(obj, 0x03000010);
}

void func_ovl0C_06_80044BC8(void) {
    func_ovl0C_06_80047D70(0xF, 0, 0x1B);
    func_ovl0C_06_80044808(0, 0, 0, 0.0f, 0);
}

void func_ovl0C_06_80044B60(void) {
    func_ovl0C_06_80048980(0x43A);
    func_ovl0C_06_80048980(0x439);
    func_ovl0C_06_80048980(0x438);
    func_ovl0C_06_80048980(0x437);
    func_ovl0C_06_80047D70(0x24, 4, 4);
    func_ovl0C_06_80044808(1, 0, 0, 0.0f, 0);
}

void func_ovl0C_06_80044B10(void) {
    func_ovl0C_06_80047D70(0xF, 0, 1);
    func_ovl0C_06_80044808(2, 0x80, 0, 0.0f, 4);
}

void func_ovl0C_06_80044AB0(void) {
    func_ovl0C_06_80047D70(0x1B, 4, 0x15);
    func_ovl0C_06_80044808(3, 0, 0xC0, 0.0f, 2);
    func_ovl0C_06_80047D40(0x2D, 0x19);
}

void func_ovl0C_06_80044A4C(void) {
    func_ovl0C_06_80047D70(0x2D, 1, 0xE);
    func_ovl0C_06_80044808(4, 0xC0, 0x40, 0.0f, 1);
    func_ovl0C_06_80047D40(0x2D, 0x1A);
}

void func_ovl0C_06_800449F0(void) {
    func_ovl0C_06_80047D70(0xF, 0, 0x10);
    func_ovl0C_06_80044808(5, 0, 0, 0.0f, 0);
    func_ovl0C_06_80048520();
    func_ovl0C_06_80047D40(0x2D, 0x18);
}

void func_ovl0C_06_800449C8(void) {
    func_ovl0C_06_80044808(6, 0, 0, 0.0f, 0);
}

void func_ovl0C_06_80044950(void) {
    func_ovl0C_06_80047D70(0x2B, 5, 3);
    func_ovl0C_06_80044808(7, 0x40, 0x40, 0.0f, 0);
    func_ovl0C_06_80047D40(0x2D, 0x18);
    func_ovl0C_06_8004491C();
}

void func_ovl0C_06_8004491C(void) {
    func_ovl0C_06_80048520();
    func_ovl0C_06_800484E8(D_ovl0C_06_80049370);
    func_ovl0C_06_80048458(0x1F);
}

void func_ovl0C_06_800448D4(void) {
    func_ovl0C_06_80047D70(0xF, 0, 0x1B);
    func_ovl0C_06_80044808(8, 0, 0, 0.0f, 0);
}

void func_ovl0C_06_80044884(void) {
    func_ovl0C_06_80047D70(0x1B, 4, 0x15);
    func_ovl0C_06_80044808(9, 0, 0xC0, 0.0f, 2);
}

void func_ovl0C_06_80044830(void) {
    func_ovl0C_06_80047D70(0x2D, 1, 0xE);
    func_ovl0C_06_80044808(0xA, 0xC0, 0x40, 0.0f, 1);
}

void func_ovl0C_06_80044808(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0C_06_800493B0.unk0 = arg0;
    D_ovl0C_06_800493B0.unk4 = arg1;
    D_ovl0C_06_800493B0.unk8 = arg2;
    D_ovl0C_06_800493B0.unkC = arg3;
    D_ovl0C_06_800493B0.unk10 = arg4;
}

void func_ovl0C_06_800446FC(void) {
    s32 state;

    func_ovl0C_06_800445CC();
    if (!func_ovl0C_06_80048990(0x43B)) {
        func_ovl0C_06_80044494(&D_ovl0C_06_80049264, D_ovl0C_06_8004914C, 1);
        func_ovl0C_06_80044340(D_ovl0C_06_800490FC, 1);
    }
    if (!func_ovl0C_06_80048990(0x43A)) {
        func_ovl0C_06_800442BC(&D_ovl0C_06_80048FD0[0]);
    }
    if (func_ovl0C_06_80048990(0x438) && !func_ovl0C_06_80048990(0x437)) {
        func_ovl0C_06_800442BC(&D_ovl0C_06_80048FD0[1]);
        func_ovl0C_06_8004399C(&D_ovl0C_06_80049030[1]);
    }
    if (func_ovl0C_06_80048990(0x437) && !func_ovl0C_06_80048990(0x436)) {
        func_ovl0C_06_800442BC(&D_ovl0C_06_80048FD0[2]);
    }
    state = D_ovl0C_06_800493B0.unk0;
    if (state == 3 || state == 4) {
        func_ovl0C_06_80044264();
    }
    if (state == 2) {
        func_ovl0C_06_80044228(D_ovl0C_06_80048F10);
    }
}

void func_ovl0C_06_800445CC(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_06_80047DC8();
    switch (D_ovl0C_06_800493B0.unk8) {
        case 0:
            angle = 0.0f;
            break;
        case 0x80:
            angle = 180.0f;
            break;
        case 0xC0:
            angle = 90.0f;
            break;
        case 0x40:
            angle = 270.0f;
            break;
        case 1:
        default:
            angle = 360.0f;
            break;
    }
    if (angle != 360.0f) {
        func_ovl0C_06_80048418(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_06_800493B0.unkC;
        func_ovl0C_06_80048420(&sp1C, NULL, NULL);
        func_ovl0C_06_80048418(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_06_80047DB0(D_ovl0C_06_800493B0.unk4);
    func_ovl0C_06_800484B0(45.0f, 45.1f);
}

void func_ovl0C_06_80044584(f32 arg0) {
    f32 sp1C;

    func_ovl0C_06_80048420(&sp1C, NULL, NULL);
    func_ovl0C_06_80048418(sp1C + arg0, 32768.0f, 32768.0f);
}

/* the wall the blocks stand in front of, and the blocks' tiles */
void func_ovl0C_06_80044494(UnkStruct_ovl0C_06_80049264 *arg0, UnkStruct_ovl0C_06_8004914C *arg1, s32 arg2) {
    UnkStruct_ovl0C_06_8004914C *p;
    UnkStructA *obj;

    p = arg1;
    obj = func_ovl0C_06_80048600(0x2BB, 0xD0, arg0->unk4, arg0->unk8, arg0->unkC);
    func_ovl0C_06_800485B8(obj, arg2 ? 0x01000000 : 0x01000000);
    arg0->unk0 = obj;
    for (; p->unk2 != 0; p++) {
        func_ovl0C_06_80047BF8(p->unk18, p->unk1A, p->unk1C, p->unk18 + 3, p->unk1C + 2, 0x11);
        func_ovl0C_06_80047BF8(p->unk18, p->unk1E, p->unk1C, p->unk18 + 3, p->unk1C + 2, 0x1F);
    }
}

/* the switches' objects, turned if already hit, and their tiles */
void func_ovl0C_06_80044340(UnkStruct_ovl0C_06_800490FC *arg0, s32 arg1) {
    UnkStruct_ovl0C_06_800490FC *p;
    UnkStructA *obj;

    p = arg0;
    func_ovl0C_06_80043060();
    for (; p->unk2 != 0; p++) {
        obj = func_ovl0C_06_80048600(0x2AE, 0xD0, p->unk8, p->unkC, p->unk10);
        func_ovl0C_06_800485B8(obj, arg1 ? 0x01000000 : 0x01000000);
        p->unk4 = obj;
        p->unk22 = 0;
        func_ovl0C_06_800482C0(obj->unk40, 2);
        if (!func_ovl0C_06_80048990(p->unk24)) {
            func_ovl0C_06_800482C8(p->unk4->unk40, 0x2AF, 0, 0);
            func_ovl0C_06_800482C8(p->unk4->unk40, 0x2AF, 1, 1);
        } else {
            func_ovl0C_06_800482C8(p->unk4->unk40, 0x2AF, 0, 2);
            func_ovl0C_06_800482C8(p->unk4->unk40, 0x2AF, 1, 3);
        }
        func_ovl0C_06_80047C00(p->unk18, p->unk1A, p->unk1C, p->unk18 + 1, p->unk1E, p->unk1C + 1, 0x1F);
    }
}

void func_ovl0C_06_800442BC(UnkStruct_ovl0C_06_80048FD0 *arg0) {
    UnkStructA *obj;
    UnkStructA *shadow;

    obj = func_ovl0C_06_80048600(0x2A6, 0xD0, arg0->unk4, arg0->unk10, arg0->unkC);
    shadow = func_ovl0C_06_800485F0(obj);
    shadow->unk54 = 2.0f;
    shadow->unk4C = 2.0f;
    shadow->unk40->unk36 = 0x19;
    func_ovl0C_06_800485B8(obj, 0x0D080000);
    arg0->unk0 = obj;
    arg0->unk8 = arg0->unk10;
}

void func_ovl0C_06_80044264(void) {
    D_ovl0C_06_800493AC = func_ovl0C_06_80047DF8(func_ovl0C_06_80047D98());
    func_ovl0C_06_800485B8(D_ovl0C_06_800493AC, 0x80000);
    D_ovl0C_06_800493AC->unk40->unk36 = 0;
}

void func_ovl0C_06_80044228(UnkStruct_ovl0C_06_80048F10 *arg0) {
    arg0->unk4->unk40->unk48->unk4->unk4 = 0.0f;
    func_ovl0C_06_80044164(arg0);
}

void func_ovl0C_06_80044164(UnkStruct_ovl0C_06_80048F10 *arg0) {
    func_ovl0C_06_80047C00(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk34, arg0->unk38, 0x10);
    func_ovl0C_06_80047BF8(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk38, 0x11);
    func_ovl0C_06_80047BF8(arg0->unk3C, arg0->unk40, arg0->unk44, arg0->unk48, arg0->unk4C, 0x12);
    func_ovl0C_06_80047BF0(arg0->unk50, arg0->unk54, arg0->unk58, arg0->unk60);
    func_ovl0C_06_80047BF0(arg0->unk64, arg0->unk68, arg0->unk6C, arg0->unk74);
}

void func_ovl0C_06_800440B4(void) {
    if (D_ovl0C_06_800493B0.unk0 == 3 || D_ovl0C_06_800493B0.unk0 == 4) {
        func_ovl0C_06_80044028();
    }
    func_ovl0C_06_80043FE0();
    func_ovl0C_06_80043F6C();
    if (D_ovl0C_06_800493B0.unk0 == 6) {
        func_ovl0C_06_80043F34();
    }
    func_ovl0C_06_80043EC8();
}

void func_ovl0C_06_80044028(void) {
    s32 alpha;
    s32 step;

    func_ovl0C_06_80047DA8(1);
    func_ovl0C_06_80048C90(0x45);
    step = 0x11;
    for (alpha = 0; alpha < 0xFF; alpha += step) {
        D_ovl0C_06_800493AC->unk40->unk36 = alpha;
        func_ovl0C_06_80048750();
    }
    D_ovl0C_06_800493AC->unk40->unk36 = 0xFF;
    func_ovl0C_06_800485C0(D_ovl0C_06_800493AC, 0x80000);
    func_ovl0C_06_80047DA8(0);
}

void func_ovl0C_06_80043FE0(void) {
    func_ovl0C_06_80047DB8(D_ovl0C_06_800493B0.unk4, 3, 4.0f, D_ovl0C_06_800493B0.unk10, 0, 1, 1);
}

void func_ovl0C_06_80043F6C(void) {
    UnkStruct_ovl0C_06_80048F88 *p;
    s16 i;

    for (i = 0, p = D_ovl0C_06_80048F88; i < 1; i++, p++) {
        p->unk4 = func_ovl0C_06_80048708(func_ovl0C_06_80046FFC, p, 0, 0, 0x110);
    }
}

void func_ovl0C_06_80043F34(void) {
    func_ovl0C_06_80048708(func_ovl0C_06_800458D8, NULL, 0, 0, 0x110);
}

void func_ovl0C_06_80043EC8(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0C_06_80048708(func_ovl0C_06_80045FC8, &D_ovl0C_06_80048F10[i], 0, 0, 0x110);
    }
}

void func_ovl0C_06_80043DC0(void) {
    if (func_ovl0C_06_80047D80(0xF, 1, 0x10, 1)) {
        func_ovl0C_06_80043D54(D_ovl0C_06_80048F10);
        func_ovl0C_06_80047CB0(0x2E, 0x12, 0);
    }
    if (func_ovl0C_06_80047D80(0x18, 0x1D, 0x19, 0x1E)) {
        func_ovl0C_06_80047E00(1);
        func_ovl0C_06_80048708(func_ovl0C_06_80045F44, NULL, 0, 0, 0x130);
        func_ovl0C_06_80047D58(0x3C);
        func_ovl0C_06_80047CB0(0x2F, 0x12, 4);
    }
    if (func_ovl0C_06_80047D80(0x2D, 0xE, 0x2E, 0xF)) {
        func_ovl0C_06_80047E00(1);
        func_ovl0C_06_80048708(func_ovl0C_06_80045F44, NULL, 0, 0, 0x130);
        func_ovl0C_06_80047D58(0x3C);
        func_ovl0C_06_80047CB0(0x30, 0x12, 4);
    }
}

void func_ovl0C_06_80043D54(UnkStruct_ovl0C_06_80048F10 *arg0) {
    func_ovl0C_06_80047DA8(1);
    func_ovl0C_06_80048C90(0x4B);
    func_ovl0C_06_800485B8(arg0->unk4, 0x04000000);
    func_ovl0C_06_80048728(60);
    func_ovl0C_06_80048C90(0x46);
    func_ovl0C_06_80043710(arg0);
    func_ovl0C_06_80048988(0x429);
    func_ovl0C_06_80048728(10);
}

/* the movers' switches: a cut scene each */
void func_ovl0C_06_80043B3C(void) {
    if (func_ovl0C_06_80047D80(0xF, 0xF, 0x10, 0x10) && !func_ovl0C_06_80048990(0x43A)) {
        func_ovl0C_06_80043AEC();
        func_ovl0C_06_80047E00(1);
        func_ovl0C_06_80047D28(1);
        func_ovl0C_06_80047D20(0);
        func_ovl0C_06_80047DB8(0x80, 3, 4.0f, 0, 1, 1, 1);
        func_ovl0C_06_80048728(0x1E);
        func_ovl0C_06_80047DE0(0x04000000);
        func_ovl0C_06_8004399C(&D_ovl0C_06_80049030[0]);
        func_ovl0C_06_80048750();
        func_ovl0C_06_80043AB4();
        func_ovl0C_06_80048728(0x5A);
        func_ovl0C_06_80047DA8(1);
        func_ovl0C_06_80047DB8(0, 3, 4.0f, 0, 1, 1, 1);
    }
    if (func_ovl0C_06_80047D80(0x2B, 2, 0x2C, 3) && func_ovl0C_06_80048990(0x437) && !func_ovl0C_06_80048990(0x436)) {
        func_ovl0C_06_80043A5C();
        func_ovl0C_06_80047D28(1);
        func_ovl0C_06_80047D20(0);
        func_ovl0C_06_80047E00(1);
        func_ovl0C_06_80047DB8(0x80, 3, 4.0f, 0, 1, 1, 1);
        func_ovl0C_06_80048728(0x1E);
        func_ovl0C_06_80047DE0(0x04000000);
        func_ovl0C_06_8004399C(&D_ovl0C_06_80049030[2]);
        func_ovl0C_06_80048750();
        func_ovl0C_06_80043914();
        func_ovl0C_06_80048728(0x5A);
        func_ovl0C_06_80047DA8(1);
        func_ovl0C_06_80047DB8(0x20, 3, 4.0f, 0, 1, 1, 1);
    }
}

void func_ovl0C_06_80043AEC(void) {
    func_ovl0C_06_80048518();
    func_ovl0C_06_80048460(0x7F);
    func_ovl0C_06_800483F8(1500.0f, 0.0f, 1600.0f);
    func_ovl0C_06_80048418(0.0f, 45.0f, 2800.0f);
}

void func_ovl0C_06_80043AB4(void) {
    func_ovl0C_06_80048708(func_ovl0C_06_80045BA0, NULL, 0, 0, 0x110);
}

void func_ovl0C_06_80043A5C(void) {
    func_ovl0C_06_80048518();
    func_ovl0C_06_80048460(0x7F);
    func_ovl0C_06_800483F8(4300.0f, 1000.0f, 200.0f);
    func_ovl0C_06_80048418(-45.0f, 45.0f, 2000.0f);
}

void func_ovl0C_06_8004399C(UnkStruct_ovl0C_06_80049030 *arg0) {
    UnkStructA *obj;
    UnkStructA *other;
    UnkStruct_ovl0C_06_80048FD0 *lim;

    obj = func_ovl0C_06_80048600(0x2B2, 0xD0, arg0->unk28, arg0->unk2C, arg0->unk30);
    func_ovl0C_06_800485F0(obj);
    func_ovl0C_06_800485B8(obj, 0x0D000000);
    lim = &D_ovl0C_06_80048FD0[arg0->unk0];
    arg0->unk4 = obj;
    other = lim->unk0;
    if (arg0->unk20 & 2) {
        func_ovl0C_06_8004394C(obj, other, lim->unk14);
    }
}

void func_ovl0C_06_8004394C(UnkStructA *arg0, UnkStructA *arg1, f32 arg2) {
    func_ovl0C_06_80048598(arg0, arg1);
    func_ovl0C_06_800485B8(arg1, 0x200000);
    arg1->unk4C = 0.0f;
    arg1->unk50 = arg2;
    arg1->unk54 = 0.0f;
}

void func_ovl0C_06_80043914(void) {
    func_ovl0C_06_80048708(func_ovl0C_06_800455DC, NULL, 0, 0, 0x110);
}

void func_ovl0C_06_80043868(void) {
    UNK_MACRO_ovl0C_06_80043820();
    if (!func_ovl0C_06_80048990(0x404) && D_ovl0C_06_800493B0.unk0 == 2) {
        func_ovl0C_06_8004379C(D_ovl0C_06_80048F10);
    }
    if (!func_ovl0C_06_80048990(0x43B)) {
        func_ovl0C_06_80043544(&D_ovl0C_06_80049264, D_ovl0C_06_8004914C, D_ovl0C_06_800490FC, 0x43B);
    }
    func_ovl0C_06_80048980(0x404);
}

void func_ovl0C_06_80043820(void) {
    UNK_MACRO_ovl0C_06_80043820();
}

void func_ovl0C_06_8004379C(UnkStruct_ovl0C_06_80048F10 *arg0) {
    func_ovl0C_06_80047DA8(1);
    func_ovl0C_06_80048728(90);
    func_ovl0C_06_80048C90(0x4B);
    func_ovl0C_06_800485B8(arg0->unk4, 0x04000000);
    func_ovl0C_06_80048728(60);
    func_ovl0C_06_80048C90(0x46);
    func_ovl0C_06_80048728(10);
    func_ovl0C_06_80043710(arg0);
    func_ovl0C_06_80048988(0x429);
    func_ovl0C_06_80047DA8(0);
}

void func_ovl0C_06_80043710(UnkStruct_ovl0C_06_80048F10 *arg0) {
    func_ovl0C_06_80047C00(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk34, arg0->unk38, 0x1F);
    func_ovl0C_06_80047BF0(arg0->unk50, arg0->unk54, arg0->unk58, arg0->unk5C);
    func_ovl0C_06_80047BF0(arg0->unk64, arg0->unk68, arg0->unk6C, arg0->unk70);
}

/* bombs on the switches: a switch hit turns, and once none is left the
 * blocks crumble */
s32 func_ovl0C_06_80043544(UnkStruct_ovl0C_06_80049264 *arg0, UnkStruct_ovl0C_06_8004914C *arg1, UnkStruct_ovl0C_06_800490FC *list, s32 arg3) {
    UnkStructA_40 *pos;
    s32 hit;
    s32 left;
    s32 ret;
    UnkStruct_ovl0C_06_800490FC *saved;

    saved = list;
    D_ovl0C_06_800493C4->unk30 = 4;
    D_ovl0C_06_800493C4->unk34 = 90.0f;
    D_ovl0C_06_800493C4->unk38 = 400.0f;
    left = 0;
    for (; list->unk2 != 0; list++) {
        if (!func_ovl0C_06_80048990(list->unk24)) {
            D_ovl0C_06_800493C4->unk40->unk10 = list->unk8;
            D_ovl0C_06_800493C4->unk40->unk14 = list->unkC;
            D_ovl0C_06_800493C4->unk40->unk18 = list->unk10;
            hit = func_ovl0C_06_80048568(D_ovl0C_06_800493C4, 0xC0);
            if (hit) {
                if (hit & 0x6000) {
                    func_ovl0C_06_80048CB0(0x49, list->unk8, list->unkC, list->unk10);
                    func_ovl0C_06_800482C8(list->unk4->unk40, 0x2AF, 0, 2);
                    func_ovl0C_06_800482C8(list->unk4->unk40, 0x2AF, 1, 3);
                    func_ovl0C_06_80048980(list->unk24);
                } else {
                    pos = D_ovl0C_06_800493C4->unk40;
                    func_ovl0C_06_80048CB0(0x26, pos->unk10, pos->unk14, pos->unk18);
                    left = 1;
                }
            } else {
                left = 1;
            }
        }
    }
    ret = 0;
    if (!left && !func_ovl0C_06_80048990(arg3)) {
        ret = 1;
        func_ovl0C_06_80048980(arg3);
        func_ovl0C_06_80043354(arg0, arg1, saved, arg3);
    }
    return ret;
}

/* the blocks crumble (a cut scene) */
void func_ovl0C_06_80043354(UnkStruct_ovl0C_06_80049264 *arg0, UnkStruct_ovl0C_06_8004914C *arg1, UnkStruct_ovl0C_06_800490FC *arg2, s32 arg3) {
    s32 sparks;
    s32 task;
    UnkStruct_ovl0C_06_8004914C *p;

    func_ovl0C_06_80047E68();
    func_ovl0C_06_80047DA8(1);
    task = func_ovl0C_06_80048708(func_ovl0C_06_80045524, arg1, 0, 0, 0x110);
    func_ovl0C_06_800485D0(arg0->unk0);
    func_ovl0C_06_80043248(arg1, 0x40C);
    sparks = func_ovl0C_06_80048708(func_ovl0C_06_80046BD8, arg2, 0, 0, 0x110);
    func_ovl0C_06_80047D28(1);
    func_ovl0C_06_80048768(task);
    func_ovl0C_06_80048768(sparks);
    func_ovl0C_06_80048780(0xB0, 0xB0);
    for (p = arg1; p->unk2 != 0; p++) {
        func_ovl0C_06_80048B58(0x10, p->unk8 - 300.0f, p->unkC + 200.0f, p->unk10, 0);
        func_ovl0C_06_80048728(0x1E);
    }
    func_ovl0C_06_80048CB0(0x42, arg1->unk8, arg1->unkC, arg1->unk10);
    for (p = arg1; p->unk2 != 0; p++) {
        func_ovl0C_06_80048708(func_ovl0C_06_8004696C, p, 0, 0, 0x110);
        func_ovl0C_06_80048728(0xF);
    }
    func_ovl0C_06_80048728(0x3C);
    func_ovl0C_06_80048710(sparks);
    func_ovl0C_06_80048728(0x3C);
    func_ovl0C_06_80047D28(0);
    if (*func_ovl0C_06_80047D08() & 2) {
        func_ovl0C_06_80047DA8(1);
    }
}

/* the blocks' objects, and their tiles made solid */
void func_ovl0C_06_80043248(UnkStruct_ovl0C_06_8004914C *arg0, s32 arg1) {
    UnkStruct_ovl0C_06_8004914C *p;
    UnkStructA *obj;

    for (p = arg0; p->unk2 != 0; p++) {
        obj = func_ovl0C_06_80048600(0x2B0, 0xD0, p->unk8, p->unk14, p->unk10);
        func_ovl0C_06_800485B8(obj, arg1 ? 0x01000000 : 0x01000000);
        p->unk4 = obj;
        p->unkC = p->unk14;
        func_ovl0C_06_80047BF8(p->unk18, p->unk1A, p->unk1C, p->unk18 + 3, p->unk1C + 2, 0x11);
        func_ovl0C_06_80047BF8(p->unk18, p->unk1E, p->unk1C, p->unk18 + 3, p->unk1C + 2, 0x1F);
    }
}

void func_ovl0C_06_800431B8(void) {
    if (func_ovl0C_06_80047D88(3, 1, 0xF, 4, 0x11) && func_ovl0C_06_800430A8(func_ovl0C_06_80047DF8(func_ovl0C_06_80047D98()), D_ovl0C_06_800492AC.unk0)) {
        if (func_ovl0C_06_80048970(0xA4)) {
            func_ovl0C_06_80048320(0x291, 1);
        } else {
            func_ovl0C_06_80048320(0x361, 4);
        }
    }
}

/* whether the player (arg0) faces arg1: probes 50 units ahead with the
 * shared probe object */
s32 func_ovl0C_06_800430A8(UnkStructA *arg0, UnkStructA *arg1) {
    f32 dz;
    f32 dx;

    func_ovl0C_06_80043060();
    dx = func_ovl0C_06_800488B0(arg0->unk40->unk20) * 50.0f;
    dz = func_ovl0C_06_800488B8(arg0->unk40->unk20);
    D_ovl0C_06_800493C4->unk30 = 1;
    D_ovl0C_06_800493C4->unk34 = 30.0f;
    D_ovl0C_06_800493C4->unk38 = 50.0f;
    D_ovl0C_06_800493C4->unk40->unk10 = arg0->unk40->unk10 + dx;
    D_ovl0C_06_800493C4->unk40->unk14 = arg0->unk40->unk14;
    D_ovl0C_06_800493C4->unk40->unk18 = arg0->unk40->unk18 + dz * 50;
    if (func_ovl0C_06_80048648(D_ovl0C_06_800493C4, 0x10) != arg1) {
        return 0;
    }
    return 1;
}

void func_ovl0C_06_80043060(void) {
    if (func_ovl0C_06_80048990(0x400) == 0) {
        D_ovl0C_06_800493C4 = func_ovl0C_06_800485E0(-1, 0, 0x20, 0);
        func_ovl0C_06_80048980(0x400);
    }
}

void func_ovl0C_06_80043040(void) {
    func_ovl0C_06_80047E00(1);
}

void func_ovl0C_06_80043020(void) {
    func_ovl0C_06_80047E00(1);
}

void func_ovl0C_06_80043018(void) {
}

void func_ovl0C_06_80043010(void) {
}

