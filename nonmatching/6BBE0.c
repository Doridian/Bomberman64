/*
 * NON_MATCHING: main_code's 6BBE0, complete: 80 functions (us
 * 0x802513E0-0x8025E1D4), one object. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 647, eu 647, jp 5700
 *
 * A first draft: every function not called from outside is static, in
 * the reverse of the ROM's order, with a dead call list fixing IPA's
 * emission order; m2c's bodies with the -O3 fixes (byte arithmetic on
 * typed pointers, flag words as s32, address-taken vectors as arrays,
 * the register-passed float arguments of the statics restored), some
 * by hand. 70 of 80 match apart from relocations in every version.
 *
 * Pass 4 fixed draft errors in func_802553D4: the D_800AEDF0 player
 * records read as s32 fields (m2c read them as u8 at D_800AEExx +
 * X * 0xC8), func_802268F4's lost argument, func_8028A81C's result kept
 * for func_8028A4E0, the flags double stores, the switch's shared tail
 * as one func_802530A8 call after it, and spE4 as a struct copy of
 * D_802A0FA0 indexed by a separate idx (m2c reused a register-family
 * variable, which uopt then rematerialised before every no-exit loop).
 *
 * Almost all of what differs is func_802553D4 (about 7300 words). m2c
 * gave each register family (loop counters, float temps) many names,
 * and uopt hoisted all their constant initialisations together, so they
 * took every callee-saved register before the object pointer; merging
 * the families gives the pointer fp. Its size is -14 words in us, and
 * the drift moves along it (from -24 to +3 words): the original
 * keeps 360.0f in f30 for the whole function and puts the W360 inner
 * ?: results in stack temporaries (spA0, spAC, spC4: m2c's names are
 * those slots), where ours gives the ?: results f30. Its count is
 * positional, so a local fix there can move it by hundreds of words
 * either way. The three "turn" blocks share their `F7C = 60.0f` tail
 * in the original; the second one has the goto now, and giving the
 * other two theirs raises us (by 1000 for the first). Before the
 * func_8026E8B8 call, the object should be loaded after the call (jp
 * -19, us +1014). These need the f30 question solved first.
 *
 * Pass 6 gave func_802553D4 the original's frame (352, the front end's
 * part 208 bytes, the uopt spill words at 0x88/0x8C). The front end
 * puts the declared locals top-down in declaration order, then its own
 * temporaries: one per kind live at once (int and pointer share, float,
 * double), reused from statement to statement. A call inside another
 * call's arguments needs one, a ?: value needs one, and W360 inside an
 * argument needs two floats; the original has a double and two words.
 * So the register-only locals were merged (same code, sp offsets aside)
 * down to 48 words, and the declarations are ordered so sp150, sp148,
 * sp134, sp12C, sp118, sp10C, sp108 and spE4 land on their slots. In
 * jp the original keeps var_s5 in memory at 0x140.
 *
 * func_802530A8 (about 1500) has its exact size (0x1BE8) and frame
 * (136): its 24 declared words in the original's slot order, the
 * func_8022FA88 wrappers taking the distance pointer (&sp6C) as a
 * second argument, and an else/goto shape that keeps umerge from
 * inlining the small static wrappers (a `break` shape is small enough
 * that it inlines them; check the jal list). Of its own words 26 still
 * differ: dir and the arguments of two calls ($5 set before $4 in the
 * original), one float temp in f22 for f0 and a store scheduled
 * differently.
 *
 * The other procedures that differ: func_80251EE0 (ret should live in
 * $2; the forms that do it change the size), func_80252174 (n in $3
 * across an IPA call), func_802515D8 (the new history pointer is kept
 * in $5 and not folded into the stores), and the argument order of
 * func_80251C48 calls (func_80255224, func_8025D544, func_80252174,
 * func_8025C840, func_802529A4): the original sets $5 first and $4 in
 * the delay slot, and nothing in the source moved it yet.
 *
 * What moved the count: exact sizes first (one block per original
 * global, so a short static misaligns everything after it; for
 * func_80251EE0, `if (ret == 1)` was the size). In func_802530A8, the
 * (flags & 3) switch with its bodies in source order (case 3, case 0,
 * default); `flags &= ~3; flags |= K;` for a double store (K may be
 * 0); and m2c's shared-tail gotos written as inline stores in each
 * branch. Also chained global stores (`A = B = 0`), f32 `k = 2.0f` to
 * keep a mul.s, `x = c ? 1 : 0` for `b; li v0,1`, K&R prototypes for
 * callees given arguments, and m2c's goto loops as for(;;) with an
 * else-if chain and break to the return block.
 *
 * Pass 5: commutative operands in the original's order (`x + d[0]`),
 * pointer assignments in the order that gives the original's
 * registers, a single `ret` for a float return with if/else, declaration
 * order and real or pad locals for the frame slots, nested ifs for
 * comma conditions, `f8 = f4; f4 = K;` for the state swaps (m2c's
 * temp_tN made a variable), loads into locals before the stores when
 * the original loads both first, `x = off; x += pos[4];` for the
 * operand order of an add, u16 fields for 0x8000 stores (ori, not
 * addiu), index loops for m2c's pointer walks to an end address (IDO
 * strength-reduces them, and unrolls a constant count by 4), lw for an
 * s32 table m2c read as u8, and one access path for repeated loads
 * through arg0->0x98.
 *
 * jp lacks one height test in func_802553D4 (VERSION_JP); eu is us.
 */
#include "common.h"

typedef struct { s32 n; f32 f4; s32 unk8; f32 fC; } SeqA; /* 0x10 */
typedef struct { s32 n; u16 v; } SeqB; /* 0x8 */
typedef struct { s32 len[3]; s32 idx[3]; s32 cnt[3]; SeqA *a; SeqB *b; SeqB *c; } Seq;
typedef struct { f32 f0; f32 f4; f32 f8; u16 vC; u16 vE; } SeqOut;

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define FDIFF(a, b) ((a) < (b) ? -((a) - (b)) : ((a) - (b)))
#define W360(a) ((a) >= 360.0f ? (a) - 360.0f : ((a) < 0.0f ? (a) + 360.0f : (a)))
#define W360M90(a) ((a) - 90.0f >= 360.0f ? (a) - 90.0f - 360.0f : ((a) < 90.0f ? (a) - 90.0f + 360.0f : (a) - 90.0f))
#define M2C_BITWISE(type, expr) ((type)(expr))
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} UnkModel;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkModel *unk40;
    /* 0x44 */ u8 unk44[0x4C - 0x44];
    /* 0x4C */ f32 unk4C[3];
    /* 0x58 */ u8 unk58[0x6C - 0x58];
    /* 0x6C */ f32 unk6C;
} UnkObj;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ UnkObj *unk28;
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
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s32 unkB0;
    /* 0xB4 */ s32 unkB4;
    /* 0xB8 */ s32 unkB8;
    /* 0xBC */ s32 unkBC;
    /* 0xC0 */ s32 unkC0;
    /* 0xC4 */ s32 unkC4;
} UnkStruct_800AEDF0; /* size 0xC8 */

extern UnkStruct_800AEDF0 D_800AEDF0[5];
extern u8 D_802ACF08[][0x10];

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 unk4;
} Unk6BBE0_8; /* size 8 */

typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0C */ u8 pad0C[0xC];
} Unk6BBE0_18; /* size 0x18 */

void free(void *);
void func_802268F4(s32);
void func_80227FE8(s32, s32, s32);
void func_80228008(s32, s32, s32);
s32 func_802280F4(s32, s32);
s32 func_8022979C(s32, s32, s32);
void func_802297B8(s32, s32, s32, s32);
s32 func_8022984C(void *, s32);
s32 func_80229C90(s32, s32, s32, s32, s32, s32);
f32 func_80229D3C(void *, s32);
void func_80229E38(void *, s32, s32);
s32 func_80229F74(void *, s32);
void func_8022A1E8(void *);
void * func_8022A6C4(void *, s32);
s32 func_8022F4AC(s32, s32, s32);
s32 func_8022F550(s32, s32);
s32 func_8022F698(void *, s32, f32 *, void *, s32);
s32 func_8022F77C(s32, s32, s32);
void func_8022F808(void *, f32 *);
void *func_8022FA88();
void func_8022FC90(void *);
void func_8022FF58(f32 *, f32 *, f32 *);
void func_80230914(void *);
s32 func_802311E8(void *);
void * func_80231274(s32, s32, s32, void *);
void func_802313DC(void *, s32);
void func_80231408(void *, s32);
void func_80232BA0(f32 *, void *);
s32 func_80232D18(void *, s32);
void func_80232DB4(void *);
int func_8023369C(f32, f32, f32);
void func_80233C80(f32 *);
s32 func_80234248(s32);
f32 func_80234408(f32);
f32 func_80234434(f32);
void func_802346C8(f32, f32, f32);
void func_80234778(f32, f32, f32);
void func_80234F6C(s32);
void func_802350F8(s32);
void func_802362B8(s32);
void func_802362D4(s32);
void func_802371C8(void);
void func_80237290(void);
s32 func_80238A10(void *, void *, s32, s32, s32);
void func_8023903C(s32);
void func_80239094(void);
s32 *func_802391F0(void);
void func_80239430(void);
void * func_8023A834(void);
void * func_8023A840(void);
s32 func_8023AA60(s32);
void func_8023E8AC(void);
void func_8024368C(s32);
s32 func_80243D2C(s32);
s32 func_80243EB4(s32, s32);
s32 func_80243EF0(s32);
void * func_802443F4(s32);
s32 func_80244BA4(s32, s32);
void func_80245280(s32);
void func_802452E8(s32);
s32 func_80245408(s32);
void func_8024585C(s32);
void func_802459BC(s32);
void func_80247C50(s32);
void func_80250338(s32, void *);
void func_802512C0(s32, s32, s32);
f64 func_8025E63C(void);
void func_8026BE80(s32);
void func_8026C454(s32, f32, f32, f32);
s32 func_8026C51C(s32, f32, f32, f32);
s32 func_8026C660(s32);
void func_8026C8E8(void);
void func_8026CBD4(void *);
void func_8026CCBC(s32);
void * func_8026CE28(s32);
s32 func_8026D7D8(s32, s32, s32);
void func_8026DCAC(f32, f32, f32, void *, s32);
void func_8026E338(f32, f32, f32, f32 *, s32);
f32 func_8026E8B8(void);
f32 func_8026E938(void *);
s32 func_802703B4(s32);
s32 func_80270770(s16, s16);
s32 func_80271F74(s32);
f32 func_80277484(void);
void * func_8027A1A0(void *);
void func_8027F820();
void func_8027F858(s32, s32);
s32 func_8028A4E0(s32);
s32 func_8028A81C(s32, f32, f32, f32, s32);
s32 func_802909FC(void *, void *);
void func_80291944(void *, s32, f32);
void func_802923CC(void);
s32 func_8029279C(void *, s32, s32, s32, f32);
void func_80297D30(s32, void *);
void func_80297D80(void *, void *, s32);
void func_80297D88(s32, void *, s32);
s32 func_80297D90(void *, void *, s32);
void func_80297DA8(void *, s32, void *, void *, void *, s32);
void func_80297DB0(void *);
void func_80297FA0(s32);
void * malloc(s32);
f32 sqrtf(f32);

extern u8 D_1000000[];
extern u8 D_8008E658[];
extern u8 D_8008F3D8[];
extern u8 D_800AEE04[];
extern u8 D_800AEE14[];
extern u8 D_800AEE1C[];
extern u8 D_800AEE3C[];
extern u8 D_800AEE58[];
extern u8 D_800AEE94[];
extern s32 D_800AEF94;
extern u8 D_800BCFE8[];
extern s32 D_800BD080;
extern s32 D_800BD1A8;
extern u8 D_800BD238[];
extern s32 D_800BD2D0;
extern s32 D_800BD3F8;
extern u8 D_800BD488[];
extern u8 D_800BE848[];
extern u8 D_800BE860[];
extern u8 D_800BE868[];
extern u8 D_800BEA58[];
extern u8 D_802A0EF0[];
extern u8 D_802A0F3C[];
extern s32 D_802A0F7C[];
extern s32 D_802A0F9C;
typedef struct { f32 x, z; } Pt2;
typedef struct { Pt2 p[4]; } Pt2x4;
extern Pt2x4 D_802A0FA0;
extern f32 D_802A0FC0;
extern u8 D_802A1008[];
extern s32 D_802A1038[];
extern u8 D_802A1044[];
extern u8 D_802A10C4[];
extern u8 D_802A10E4[];
extern u8 D_802A1104[];
extern u8 D_802A1144[];
extern u8 D_802A1184[];
extern u8 D_802A11A0[];
extern s32 D_802AC5D0;
extern s32 D_802AC758;
extern u8 D_802AC760[];
extern u8 D_802AC820[];
extern f32 D_802ACFB0;
extern f32 D_802ACFB4;
extern f32 D_802ACFB8;
extern s32 D_802ACFBC;
extern f32 D_802ACFC0;
extern s32 D_802ACFC4;
extern s32 D_802ACFC8;
extern s32 D_802ACFD0;
extern s32 D_802ACFD4;

void func_802513E0(void);
static void func_80251424(f32 *arg0);
void func_802514CC(void);
void func_80251534(s32 arg0);
static s32 func_8025156C(f32 *arg0);
static void func_802515D8(f32 *arg0);
static s32 func_80251708(s32 arg0);
void func_80251804(s32 arg0);
static void *func_80251974(f32 *arg0, f32 *arg1);
static f32 func_80251994(f32 *arg0, f32 *arg1);
static s32 func_802519B4(f32 arg0);
static s32 func_80251A24(s32 arg0, f32 *arg1, f32 arg2);
static s32 func_80251AC8(s32 arg0);
static void *func_80251B08(s32 arg2, s32 *arg0, s32 arg1);
static s32 func_80251BDC(f32 *arg1, f32 *arg0);
static f32 func_80251C48(f32 *arg1, f32 *arg0);
static void *func_80251C88(s32 arg0);
static void *func_80251D10(f32 *arg0, f32 *arg1);
s32 func_80251D30(f32 *arg0, s32 arg1, s32 arg2, s32 arg3);
static void func_80251E5C(f32 *arg0);
static s32 func_80251EE0(f32 *arg0);
static void func_80252048(f32 *arg0);
void func_8025216C(void);
void func_80254FA0(void);
static void func_80252174(f32 *arg0);
static s32 func_80252330(s32 *arg0, f32 arg1);
static f32 func_80252380(u8 *arg0, f32 arg1);
static f32 func_802523E0(f32 *arg0);
static f32 func_80252490(f32 *arg0);
static f32 func_80252598(f32 *arg0, f32 *arg1);
static s32 func_80252658(f32 *arg1, f32 *arg0);
static f32 func_802526A0(f32 *arg1, f32 *arg0);
static s32 func_80252724(u8 *arg0);
static s32 func_80252918(s32 *arg1, s32 arg0, s32 arg2);
static s32 func_802529A4(u8 *arg0, s32 arg1, s32 arg2, f32 arg3);
static s32 func_80252AF8(s32 arg0, s32 *arg1, s32 arg2);
static s32 func_80252BF8(s32 arg0, s32 *arg1);
static void *func_80252CB4(f32 *arg0, f32 *arg1);
static f32 func_80252CD4(u8 *arg0, f32 arg1);
static void func_80252D14(f32 *arg0);
static s32 func_80252EA4(f32 *arg0);
static void func_802530A8(f32 *arg0);
static void func_80254C90(f32 *arg0);
static s32 func_80254DC8(s32 arg0, void *arg1, f32 arg2);
static void *func_80254E00(f32 *arg0, f32 *arg1);
static s32 func_80254E20(f32 *arg0, s32 arg2, s32 arg1);
static void func_80254EC4(f32 *arg0);
static void func_80254F20(f32 *arg0);
static void func_80254FA8(f32 *arg0);
static s32 func_8025500C(s32 arg0, u8 *arg1);
static void func_80255040(u8 *arg0, u8 *arg1);
static void func_80255064(u8 *arg0, u8 *arg1, f32 arg2, f32 arg3, f32 arg4);
static s32 func_80255098(f32 *arg0);
static void func_80255110(f32 *arg0);
static void func_80255174(f32 *arg0);
static void func_802551B4(f32 *arg0);
s32 func_80255224(f32 *arg0, f32 *arg1, s32 arg2);
static s32 func_802552B8(f32 *arg0);
static void func_80255350(f32 *arg0);
static void func_802553D4(void);
void func_8025C590(s32 arg0);
void func_8025C628(void);
void func_8025C840();
void func_8025CB60(void);
void func_8025CC5C(void);
void func_8025CDAC(void);
void func_8025CEA0(void);
void func_8025D008(u8 *arg0);
void func_8025D1AC(u8 *arg0);
void func_8025D35C(void);
s32 func_8025D504(s32 arg0);
void func_8025D544(void);
void func_8025D858(void);
void func_8025DAB0(void);
void func_8025DC18(void);
void func_8025DC60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8025E0C4(s32 arg0, s32 arg1, s32 arg2);
void func_8025E0D4(s32 arg0);
void *func_8025E0DC(s32 arg0);
void func_8025E100(s32 arg0);
void func_8025E16C(void);
void func_8025E1D4(u8 **arg0);

void func_8025E1D4(u8 **arg0) {
    s32 *g;
    s32 i;

    if (D_802ACFD0 != 0) {
        if (D_802ACFD4 >= 9) {
            D_802ACFD4 = 0;
            D_802ACFD0++;
        }
        if (D_802ACFD0 >= 3) {
            func_80297FA0(1);
            D_802ACFD0 = 0;
            for (;;) {}
        }
        g = (s32 *) *arg0;
        { s32 *_g = g; g += 2; _g[0] = 0xB900031D; _g[1] = 0x5041C8; }
        { s32 *_g = g; g += 2; _g[0] = 0xFCFFFFFF; _g[1] = 0xFFFDF6FB; }
        { s32 *_g = g; g += 2; _g[0] = 0xFF10013F; _g[1] = (s32) D_1000000; }
        { s32 *_g = g; g += 2; _g[0] = 0xF7000000; _g[1] = 0x10001; }
        { s32 *_g = g; g += 2; _g[0] = 0xFA000000; _g[1] = ((s32 *) D_802A11A0)[D_802ACFD0] & 0xFF; }
        for (i = 0; i < 0xF0; i += 8) {
            { s32 *_g = g; g += 2; _g[0] = (((i + D_802ACFD4) & 0x3FF) << 2) | 0xF64FC000; _g[1] = (i & 0x3FF) << 2; }
        }
        { s32 *_g = g; g += 2; _g[0] = 0xFA000000; _g[1] = ((s32 *) D_802A11A0)[D_802ACFD0 - 1] & 0xFF; }
        for (i = 0; i < 0xF0; i += 8) {
            { s32 *_g = g; g += 2; _g[0] = (((i + 8) & 0x3FF) << 2) | 0xF64FC000; _g[1] = ((i + D_802ACFD4) & 0x3FF) << 2; }
        }
        D_802ACFD4++;
        *arg0 = (u8 *) g;
    }
}

void func_8025E16C() {
    D_802ACFD0 = D_802ACFD4 = 0;
    func_80297DA8(D_800BE868, 2, func_8025E100, NULL, D_800BEA58, 0x7F);
    func_80297DB0(D_800BE868);
}

void func_8025E100(s32 arg0) {
    func_80297D80(D_800BE848, D_800BE860, 1);
    func_80297D88(0xE, D_800BE848, 0);
    func_80297D90(D_800BE848, NULL, 1);
    func_8026C8E8();
    D_802ACFD0 = 1;
}

void *func_8025E0DC(s32 arg0) {
    return (arg0 * 0x128) + D_800BCFE8;
}

void func_8025E0D4(s32 arg0) {

}

void func_8025E0C4(s32 arg0, s32 arg1, s32 arg2) {

}

void func_8025DC60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    UnkStruct_800AEDF0 *ent;
    u8 *def;
    u8 *obj;
    u8 *p;
    s32 i;
    s32 k;

    ent = &D_800AEDF0[arg0];
    D_802AC758++;
    def = D_802A1044 + (arg1 << 5);
    ent->unk24 = 2;
    ent->unk18 = 0x200;
    ent->unk14 = M2C_FIELD(def, s32 *, 0);
    ent->unk1C = M2C_FIELD(def, s32 *, 4);
    ent->unk20 = M2C_FIELD(def, s32 *, 8);
    func_8024585C(arg0);
    func_802459BC(arg0);
    obj = func_802443F4(arg0);
    if (arg1 == 7) {
        M2C_FIELD(obj, s32 *, 0xC) = 0;
    } else {
        M2C_FIELD(obj, s32 *, 0xC) &= ~0xA0;
    }
    if (arg1 != 5) {
        func_8026CBD4(M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), void **, 0x3C));
        func_8022A1E8(M2C_FIELD(obj, void **, 0x40));
        if (arg1 == 7 || arg1 == 8) {
            M2C_FIELD(obj, s32 *, 0x28) = M2C_FIELD(def, s32 *, 0x1C);
        } else {
            M2C_FIELD(obj, s32 *, 0x28) = 0x320;
        }
        M2C_FIELD(obj, void **, 0x40) = func_8022A6C4(func_8026CE28(M2C_FIELD(obj, s32 *, 0x28)), 0x40);
        func_80229F74(M2C_FIELD(obj, void **, 0x40), 2);
        func_80229E38(M2C_FIELD(obj, void **, 0x40), 0, 0);
        func_80229E38(M2C_FIELD(obj, void **, 0x40), -1, 1);
        M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), s32 *, 0xC) |= 0x4000;
        func_8022984C(M2C_FIELD(obj, void **, 0x40), 12);
        for (i = 0; i < 12; i++) {
            func_802297B8(M2C_FIELD(obj, s32 *, 0x40), 0x4B, i, i);
        }
        if (arg1 != 7 && arg1 != 8) {
            k = func_802280F4(M2C_FIELD(obj, s32 *, 0x40), 0x10);
            for (i = 0; i < 16; i++) {
                func_80228008(k, i, M2C_FIELD(def, s32 *, 0x1C));
                if (arg1 == 0) {
                    func_80227FE8(k, i, i + 0x22);
                } else {
                    func_80227FE8(k, i, i);
                }
            }
        }
    }
    func_802512C0(arg2, arg3, arg4);
    func_8024585C(0);
    p = D_800BCFE8 + arg0 * 0x128;
    M2C_FIELD(p, u8 **, 0x9C) = D_802ACF08[arg0];
    M2C_FIELD(p, s32 *, 0) = 1;
    M2C_FIELD(p, s32 *, 0x98) = 0;
    M2C_FIELD(p, s32 *, 0xC) = arg0;
    if (arg1 == 9) {
        M2C_FIELD(p, s32 *, 0x10) = 1;
    } else {
        M2C_FIELD(p, s32 *, 0x10) = 0;
    }
    M2C_FIELD(p, void **, 0x18) = func_802443F4(arg0);
    M2C_FIELD(p, void **, 0x1C) = func_802443F4(M2C_FIELD(p, s32 *, 0x10));
    M2C_FIELD(p, s32 *, 4) = 3;
    func_802515D8((f32 *) p);
    M2C_FIELD(p, s32 *, 0x84) = 0;
    M2C_FIELD(p, s32 *, 0x88) = 0;
    M2C_FIELD(p, s32 *, 0x8C) = 0;
    M2C_FIELD(p, s32 *, 0x90) = 0;
    M2C_FIELD(p, s32 *, 0x11C) = 0;
    M2C_FIELD(p, s32 *, 0x120) = 0;
    M2C_FIELD(p, s32 *, 0x14) = arg1;
    M2C_FIELD(p, s32 *, 0x94) = -1;
    M2C_FIELD(p, s32 *, 0x124) = 0;
    M2C_FIELD(p, f32 *, 0x7C) = 0.0f;
    M2C_FIELD(p, f32 *, 0x78) = 0.0f;
    obj = func_8023A840();
    M2C_FIELD(obj, s32 *, 0x2C) = 0;
    D_802ACFC4 = M2C_FIELD(def, s32 *, 0xC);
    if (M2C_FIELD(obj, s32 *, 0x10) == 1) {
        if (ent->unk14 != -1) {
            ent->unk14++;
        }
    }
    func_80255110((f32 *) p);
    if ((s32) def == (s32) D_802A10E4) {
        func_80238A10(func_8025CB60, (s32) p, 0, 0, 0x130);
    }
    D_802ACFB0 = M2C_FIELD(def, f32 *, 0x18);
    D_802ACFB4 = M2C_FIELD(def, f32 *, 0x10);
    D_802ACFB8 = M2C_FIELD(def, f32 *, 0x14);
    D_802ACFBC = 0;
    M2C_FIELD(p, s32 *, 0xA0) = func_80238A10(func_802553D4, (s32) p, 0, 0, 0x130);
    func_80238A10(func_8025C840, (s32) p, 0, 0, 0x130);
    if ((def >= D_802A1044 && def < D_802A10C4) || (s32) def == (s32) D_802A1104 || (s32) def == (s32) D_802A1144) {
        func_80238A10(func_8025C628, (s32) p, 0, 0, 0x130);
    }
}

void func_8025DC58(void) {
}

void func_8025DC50(void) {
}

void func_8025DC48(void) {
}

void func_8025DC40(void) {
}

void func_8025DC38(void) {
}

void func_8025DC30(void) {
}

void func_8025DC28(void) {
}

void func_8025DC20(void) {
}

void func_8025DC18() {

}

void func_8025DAB0() {
    s32 *player;
    u8 *obj;
    f32 *src;
    f32 *dst;
    s32 i;
    f32 f;
    f32 s;

    player = func_802391F0();
    obj = func_80231274(0xA, 0x03080000, 0xD0, NULL);
    dst = M2C_FIELD(obj, f32 **, 0x40);
    src = M2C_FIELD(player, f32 **, 0x40);
    dst[4] = src[4];
    dst[5] = src[5] + 50.0f;
    dst[6] = src[6];
    M2C_FIELD(M2C_FIELD(obj, void **, 0x40), s16 *, 0x36) = 0xFF;
    for (i = 0; i < 20; i++) {
        f = i;
        s = ((2.0f * f) / 20.0f) + 1.0f;
        M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x30) = s;
        M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x2C) = s;
        M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x28) = s;
        M2C_FIELD(M2C_FIELD(obj, void **, 0x40), s16 *, 0x36) = 255.0f - ((f * 255.0f) / 20.0f);
        func_80239094();
    }
    func_8022FC90(obj);
    func_80239430();
}

void func_8025D858() {
    f32 f;
    f64 r1;
    f64 r2;
    u8 *p;
    u8 *obj;
    u8 *o;
    u8 *s;
    s32 i;
    s32 j;

    p = func_802391F0();
    obj = func_80231274(0x32B, 0x03080080, 0x40, NULL);
    r1 = func_8025E63C();
    r2 = func_8025E63C();
    o = M2C_FIELD(obj, void **, 0x40);
    s = M2C_FIELD(p, void **, 0x40);
    M2C_FIELD(o, f32 *, 0x10) = M2C_FIELD(s, f32 *, 0x10) + (f32) (r1 * 50.0 + -25.0);
    M2C_FIELD(o, f32 *, 0x14) = M2C_FIELD(s, f32 *, 0x14);
    M2C_FIELD(o, f32 *, 0x18) = M2C_FIELD(s, f32 *, 0x18) + (f32) (r2 * 50.0 + -25.0);
    M2C_FIELD(M2C_FIELD(obj, void **, 0x40), s16 *, 0x36) = 0xFF;
    func_8022984C(M2C_FIELD(obj, void **, 0x40), 2);
    for (i = 0, j = 0; i < 20; i++) {
        f = ((f32) i * 0.5f) / 20.0f + 1.0f;
        M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x30) = f;
        M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x2C) = f;
        M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x28) = f;
        M2C_FIELD(M2C_FIELD(obj, void **, 0x40), s16 *, 0x36) = 255.0f - ((f32) i * 255.0f) / 20.0f;
        M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x14) += 6.0f;
        if (j < 10) {
            if (!(j & 1)) {
                func_802297B8((s32) M2C_FIELD(obj, void **, 0x40), 0x32C, 0, j);
                func_802297B8((s32) M2C_FIELD(obj, void **, 0x40), 0x32C, 1, j + 1);
            }
            j += 2;
        }
        func_80232DB4(obj);
        func_80239094();
    }
    func_8022FC90(obj);
    func_80239430();
}

void func_8025D544() {
    u8 *src;
    s32 dir;
    u8 *obj;
    u8 *o;
    u8 *s;
    f32 *t;
    s32 dist;
    f32 y;
    f32 dy;
    f32 ady;
    f32 x;
    f32 z;
    s32 i;

    src = *func_802391F0();
    dir = M2C_FIELD(func_802391F0(), s32 *, 4);
    obj = func_80231274(0x32A, 0x03000000, 0xD0, NULL);
    o = M2C_FIELD(obj, void **, 0x40);
    s = M2C_FIELD(M2C_FIELD(src, void **, 0x18), void **, 0x40);
    M2C_FIELD(o, f32 *, 0x10) = M2C_FIELD(s, f32 *, 0x10);
    M2C_FIELD(o, f32 *, 0x14) = M2C_FIELD(s, f32 *, 0x14);
    M2C_FIELD(o, f32 *, 0x18) = M2C_FIELD(s, f32 *, 0x18);
    M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x20) = (dir * 45.0f >= 360.0f) ? dir * 45.0f - 360.0f : ((dir * 45.0f < 0.0f) ? dir * 45.0f + 360.0f : dir * 45.0f);
    M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x1C) = 45.0f;
    M2C_FIELD(M2C_FIELD(obj, void **, 0x40), s32 *, 0xC) |= 0x10000;
    M2C_FIELD(obj, f32 *, 0x6C) = 0.0f;
    M2C_FIELD(obj, f32 *, 0x70) = 0.0f;
    M2C_FIELD(obj, f32 *, 0x68) = 0.0f;
    func_802311E8(obj);
    dist = func_80251C48(src + 0x20, src + 0x2C);
    i = dist;
    dy = M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x14) / dist;
    ady = (dy < 0) ? -dy : dy;
    if (dist > 0) {
        t = ((f32 (*)[2]) D_802A0F3C)[dir];
        do {
            M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x10) += t[0] * 20.0f;
            M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x14) -= ady * 20.0f;
            if (M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x14) < 0.0f) {
                M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x14) = 0.0f;
            }
            M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x18) += t[1] * 20.0f;
            func_80239094();
            i -= 20;
        } while (i > 0);
    }
    x = M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x10);
    y = M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x14);
    z = M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x18);
    func_80231408(obj, 0x01000000);
    func_8026C51C(0x219, x, y, z);
    func_80238A10(func_8025DAB0, (s32) obj, 0, 0, 0x130);
    for (i = 0; i < 8; i++) {
        func_80238A10(func_8025D858, (s32) obj, 0, 0, 0x130);
        func_8023903C(4);
    }
    func_80239094();
    func_8022FC90(obj);
    func_80239430();
}

s32 func_8025D504(s32 arg0) {
    if (((arg0 & 0xF) == 0xF) || (arg0 & 0x60) || (arg0 == 0x2010) || (arg0 == 0x10) || (arg0 & 0x8000)) {
        return 0;
    }
    return 1;
}

void func_8025D35C() {
    u8 *obj;
    void *res;
    s32 dir;
    s32 i;
    u8 *p;
    f32 *t;
    u8 *o;
    f32 x;
    f32 z;

    func_8026C660(0x239);
    obj = func_802391F0();
    res = func_8026CE28(0x32E);
    dir = func_802519B4(M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x20));
    p = func_8022A6C4(res, 0);
    M2C_FIELD(p, s32 *, 0xC) |= 0x80;
    M2C_FIELD(p, s16 *, 0x36) = 0xFA;
    o = M2C_FIELD(obj, void **, 0x40);
    t = ((f32 (*)[2]) D_802A0F3C)[dir];
    x = M2C_FIELD(o, f32 *, 0x10) + t[0] * 50.0f;
    z = M2C_FIELD(o, f32 *, 0x18) + t[1] * 50.0f;
    M2C_FIELD(p, f32 *, 0x10) = x;
    M2C_FIELD(p, f32 *, 0x18) = z;
    M2C_FIELD(p, f32 *, 0x14) = 80.0f;
    M2C_FIELD(p, f32 *, 0x20) = M2C_FIELD(M2C_FIELD(obj, void **, 0x40), f32 *, 0x20);
    M2C_FIELD(p, f32 *, 0x24) = func_8025E63C() * 60.0 + -30.0;
    for (i = 0; i < 8; i++) {
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(p, s16 *, 0x36) - 31.25f;
        if (M2C_FIELD(p, s16 *, 0x36) < 0) {
            M2C_FIELD(p, s16 *, 0x36) = 0;
        }
        func_80239094();
    }
    func_8022A1E8(p);
    func_8026CCBC(0x32E);
    func_80239430();
}

void func_8025D1AC(u8 *arg0) {
    s32 hit;
    f32 k = 2.0f;

    func_8026C660(0x1E);
    func_8022979C(M2C_FIELD(arg0, s32 *, 0x40), 4, 0xC);
    func_8022979C(M2C_FIELD(arg0, s32 *, 0x40), 5, 0xD);
    func_802313DC(arg0, 0x08000000);
    M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x40), s32 *, 0xC) &= ~0x4000;
    func_80229E38((void *) M2C_FIELD(arg0, s32 *, 0x40), 0x14, 0);
    func_80229E38((void *) M2C_FIELD(arg0, s32 *, 0x40), -1, 1);
    M2C_FIELD(arg0, f32 *, 0x68) = 13.0f;
    M2C_FIELD(arg0, f32 *, 0x6C) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x70) = 0.40833336f;
    while (M2C_FIELD(arg0, f32 *, 0x68) != 0.0f) {
        M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x40), f32 *, 0x10) += ((f32 (*)[2]) D_802A0F3C)[D_802ACFC8][0] * k;
        M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x40), f32 *, 0x18) += ((f32 (*)[2]) D_802A0F3C)[D_802ACFC8][1] * k;
        func_80230914(arg0);
        hit = M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x40), f32 *, 0x14) <= func_8026E8B8() ? 1 : 0;
        if (hit) {
            func_8027F820(arg0);
            return;
        }
        func_80239094();
    }
}

void func_8025D008(u8 *arg0) {
    s32 i;

    func_8022979C(M2C_FIELD(arg0, s32 *, 0x40), 4, 0xC);
    func_8022979C(M2C_FIELD(arg0, s32 *, 0x40), 5, 0xD);
    func_80229E38((void *) M2C_FIELD(arg0, s32 *, 0x40), 1, 0);
    func_80229E38((void *) M2C_FIELD(arg0, s32 *, 0x40), 2, 1);
    func_802313DC(arg0, 0x0C000000);
    M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x40), s32 *, 0xC) &= ~0x4000;
    for (i = 0; i < 0x3C; i++) {
        if (i == 0x1E) {
            func_8026C660(0x1E);
        }
        func_8029279C((void *) M2C_FIELD(arg0, s32 *, 0x40), 0x1F, 0, 4, (f32) i / 140.0f);
        func_80239094();
    }
    func_80231408(arg0, 0x80000);
    M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x40), s32 *, 0xC) |= 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x40), s16 *, 0x36) = 0xFF;
    for (i = 0x3C; i != 0; i--) {
        M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x40), s16 *, 0x36) = (s16) (((f32) i / 60.0f) * 255.0f);
        func_80239094();
    }
    func_802313DC(arg0, 0x01000000);
}

void func_8025CEA0() {
    s32 *player;
    u8 *obj;
    f32 sign;
    f32 off;
    f32 *pos;
    f32 *dst;
    f32 x;
    f32 z;

    player = func_802391F0();
    if (M2C_FIELD(player, f32 *, 0x74) == 90.0f) {
        sign = -1.0f;
    } else {
        sign = 1.0f;
    }
    if (sign < 0.0f) {
        off = 400.0f;
    } else {
        off = -400.0f;
    }
    pos = M2C_FIELD(M2C_FIELD(player, void **, 0x18), f32 **, 0x40);
    func_8028A81C(8, pos[4] + off, 150.0f, pos[6], 0);
    obj = func_80231274(-1, 0x03000040, 0x20, NULL);
    if (sign < 0.0f) {
        off = 400.0f;
    } else {
        off = -400.0f;
    }
    dst = M2C_FIELD(obj, f32 **, 0x40);
    pos = M2C_FIELD(M2C_FIELD(player, void **, 0x18), f32 **, 0x40);
    x = off;
    x += pos[4];
    z = pos[6];
    dst[6] = z;
    dst[4] = x;
    dst[5] = 100.0f;
    M2C_FIELD(obj, f32 *, 0x6C) = 0.0f;
    M2C_FIELD(obj, f32 *, 0x70) = 0.0f;
    M2C_FIELD(obj, f32 *, 0x68) = 0.0f;
    M2C_FIELD(obj, s32 *, 0x30) = 1;
    M2C_FIELD(obj, f32 *, 0x34) = 100.0f;
    func_80232DB4(obj);
    func_8023903C(0x1E);
    func_8022FC90(obj);
    func_80239430();
}

void func_8025CDAC() {
    s32 *temp_s1;
    s32 var_s0;

    D_802A0F9C = 1;
    temp_s1 = func_802391F0();
    func_8026C660(0x2B0);
    func_8029279C(M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x18), void **, 0x40), 0, 0, 0x1F, 0.7f);
    func_8023903C(0x14);
    var_s0 = 0x3C;
    do {
        func_8029279C(M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x18), void **, 0x40), 0, 0, 0x1F, ((f32) var_s0 / 60.0f) * 0.7f);
        func_80239094();
        var_s0 -= 1;
    } while (var_s0 != 0);
    func_802923CC();
    func_8023903C(2);
    D_802A0F9C = 0;
    func_80239430();
}

void func_8025CC5C() {
    s32 *sp2C;
    s32 var_s0;
    u8 *temp_a0;
    u8 *temp_v0;
    u8 *temp_v1;

    sp2C = func_802391F0();
    temp_v0 = func_80231274(0x329, 0x03080000, 0xD0, NULL);
    temp_v1 = M2C_FIELD(temp_v0, void **, 0x40);
    temp_a0 = M2C_FIELD(M2C_FIELD(sp2C, void **, 0x18), void **, 0x40);
    M2C_FIELD(temp_v1, f32 *, 0x10) = (f32) M2C_FIELD(temp_a0, f32 *, 0x10);
    M2C_FIELD(temp_v1, f32 *, 0x14) = (f32) M2C_FIELD(temp_a0, f32 *, 0x14);
    var_s0 = 0x14;
    M2C_FIELD(temp_v1, f32 *, 0x18) = (f32) M2C_FIELD(temp_a0, f32 *, 0x18);
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x1C) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(sp2C, void **, 0x18), void **, 0x40), f32 *, 0x1C);
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(sp2C, void **, 0x18), void **, 0x40), f32 *, 0x20);
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x24) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(sp2C, void **, 0x18), void **, 0x40), f32 *, 0x24);
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), s16 *, 0x36) = 0xFF;
    M2C_FIELD(temp_v0, f32 *, 0x6C) = 0.0f;
    M2C_FIELD(temp_v0, f32 *, 0x70) = 0.0f;
    M2C_FIELD(temp_v0, f32 *, 0x68) = 0.0f;
    do {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), s16 *, 0x36) = (s16) (s32) ((f32) var_s0 * 12.75f);
        func_80239094();
        var_s0 -= 1;
    } while (var_s0 != 0);
    func_8022FC90(temp_v0);
    func_80239430();
}

void func_8025CB60() {
    u8 *temp_s0;
    u8 *temp_s2;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_s2 = M2C_FIELD(func_802391F0(), void **, 0x18);
    temp_s0 = M2C_FIELD(temp_s2, void **, 0x40);
    temp_v0 = func_80231274(0x327, 0x03000000, 0xD0, NULL);
    M2C_FIELD(temp_v0, f32 *, 0x6C) = 0.0f;
    M2C_FIELD(temp_v0, f32 *, 0x70) = 0.0f;
    M2C_FIELD(temp_v0, f32 *, 0x68) = 0.0f;
loop_1:
    temp_v0_2 = M2C_FIELD(temp_v0, void **, 0x40);
    M2C_FIELD(temp_v0_2, f32 *, 0x10) = (f32) M2C_FIELD(temp_s0, f32 *, 0x10);
    M2C_FIELD(temp_v0_2, f32 *, 0x14) = (f32) M2C_FIELD(temp_s0, f32 *, 0x14);
    M2C_FIELD(temp_v0_2, f32 *, 0x18) = (f32) M2C_FIELD(temp_s0, f32 *, 0x18);
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x1C) = (f32) M2C_FIELD(temp_s0, f32 *, 0x1C);
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(temp_s0, f32 *, 0x20);
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x24) = (f32) M2C_FIELD(temp_s0, f32 *, 0x24);
    func_802313DC(temp_s2, 0x01000000);
    M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_s0, s32 *, 0xC) | 1);
    func_80239094();
    goto loop_1;
}

void func_8025C840() {

    s32 pad[1];
    f32 spA0[3];
    f32 sp94[3];
    f32 *temp_s0;
    f32 *var_s1;
    s32 i;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv0;
    f32 var_fv0;

    func_802362B8(0xF);
    func_802350F8(1);
    func_80234F6C(1);
    for (;;) {
    if (D_802ACFBC == 0) {
        D_802ACFC0 = 0.0f;
        for (i = 0; i < 2; i++) {
            var_s1 = (f32 *) (D_800BCFE8 + i * 0x128);
            temp_s0 = (u8 *)var_s1 + 0x128;
            if (D_800AEDF0[M2C_FIELD(var_s1, s32 *, 0x134)].unk24 == 2) {
                temp_fs0 = func_8026E938(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x18), void **, 0x40));
                temp_fs1 = func_8026E938(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x1C), void **, 0x40));
                if (((func_80244BA4(M2C_FIELD(temp_s0, s32 *, 0xC), 0x02000000) == 0) && ((func_8026E8B8() == temp_fs0) || (temp_fs0 == 20000.0f))) || (func_8026E8B8() == temp_fs1) || (temp_fs1 == 20000.0f)) {
                    func_802362B8(0x10);
                }
                spA0[0] = M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x18), void **, 0x40), f32 *, 0x10);
                spA0[1] = M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x18), void **, 0x40), f32 *, 0x14);
                spA0[2] = M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x18), void **, 0x40), f32 *, 0x18);
                sp94[0] = M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x1C), void **, 0x40), f32 *, 0x10);
                sp94[1] = M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x1C), void **, 0x40), f32 *, 0x14);
                sp94[2] = M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x1C), void **, 0x40), f32 *, 0x18);
                temp_fv0 = func_80251C48(spA0, sp94);
                if (D_802ACFC0 < temp_fv0) {
                    D_802ACFC0 = temp_fv0;
                }
            }
        }
        var_fv0 = (D_802ACFC0 * 1.2f) + 1500.0f;
        if (var_fv0 > 2500.0f) {
            var_fv0 = 2500.0f;
        }
        func_80234778(0.0f, 45.0f, var_fv0);
    }
    func_80239094();
    }
}

void func_8025C628() {
    s32 *temp_s0;
    s32 temp_v1;
    s32 temp_v1_2;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_s0 = func_802391F0();
    temp_s1 = func_8023A840();
loop_1:
    if (!(M2C_FIELD(temp_s0, s32 *, 0x124) & 2) && (func_80244BA4(M2C_FIELD(temp_s0, s32 *, 0xC), 0x1000) != 0)) {
        temp_v0 = M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x18), void **, 0x20);
        if (temp_v0 != NULL) {
            temp_v1 = M2C_FIELD(temp_v0, s32 *, 8);
            if ((temp_v1 & 0x2000) && (temp_v1 & 0x20000)) {
                func_80233C80((f32 *) ((u8 *)temp_s0 + 0x20));
                M2C_FIELD(temp_s1, s32 *, 0x2C) = (s32) (M2C_FIELD(temp_s1, s32 *, 0x2C) + 1);
                M2C_FIELD(temp_s0, s32 *, 0x124) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x124) | 2);
            }
        }
    }
    if (!(M2C_FIELD(temp_s0, s32 *, 0x124) & 4) && ((func_80244BA4(M2C_FIELD(temp_s0, s32 *, 0xC), 0x20000) != 0) || (func_80243D2C(M2C_FIELD(temp_s0, s32 *, 0xC)) <= 0))) {
        temp_v0_2 = M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x18), void **, 0x20);
        if (temp_v0_2 != NULL) {
            temp_v1_2 = M2C_FIELD(temp_v0_2, s32 *, 8);
            if ((temp_v1_2 & 0x2000) && (temp_v1_2 & 0x40)) {
                func_80233C80((f32 *) ((u8 *)temp_s0 + 0x20));
                M2C_FIELD(temp_s1, s32 *, 0x2C) = (s32) (M2C_FIELD(temp_s1, s32 *, 0x2C) + 1);
                M2C_FIELD(temp_s0, s32 *, 0x124) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x124) | 4);
            }
        }
    }
    if ((M2C_FIELD(temp_s1, s32 *, 4) != 5) && !(M2C_FIELD(temp_s0, s32 *, 0x124) & 1) && (func_80243D2C(M2C_FIELD(temp_s0, s32 *, 0xC)) <= 0)) {
        func_80239094();
        if (func_8023AA60(M2C_FIELD(temp_s0, s32 *, 0xC)) == 1) {
            func_80233C80((f32 *) ((u8 *)temp_s0 + 0x20));
            M2C_FIELD(temp_s1, s32 *, 0x2C) = (s32) (M2C_FIELD(temp_s1, s32 *, 0x2C) + 1);
            M2C_FIELD(temp_s0, s32 *, 0x124) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x124) | 1);
        }
    }
    func_80239094();
    goto loop_1;
}

void func_8025C590(s32 arg0) {
    UnkStruct_800AEDF0 *sp18;
    UnkObj *var_a0;
    UnkStruct_800AEDF0 *temp_v0;

    temp_v0 = &D_800AEDF0[arg0];
    if (temp_v0->unk24 != 0) {
        var_a0 = temp_v0->unk28;
        if (var_a0 != NULL) {
            if (M2C_FIELD(var_a0, s32 *, 8) & 0x20000) {
                sp18 = temp_v0;
                func_80271F74(temp_v0->unk40);
                var_a0 = temp_v0->unk28;
            }
            sp18 = temp_v0;
            func_8022FC90(var_a0);
            temp_v0->unk28 = NULL;
            temp_v0->unkC = 0.0f;
        }
    }
}

s32 func_80255224(f32 *arg0, f32 *arg1, s32 arg2) {
    s32 pad;
    s32 best;
    f32 *p;
    f32 d;
    f32 min;
    s32 i;

    min = 10000.0f;
    i = 0;
    if (arg2 > 0) {
        p = arg1;
        do {
            d = func_80251C48(arg0, p);
            if (d <= min) {
                min = d;
                best = i;
            }
            i++;
            p += 3;
        } while (i != arg2);
    }
    return best;
}

void func_8025216C(void) {
}

void func_80254FA0(void) {
}

s32 func_80251D30(f32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *p;

    if (M2C_FIELD(arg0, void **, 0x98) != NULL) {
        return 1;
    }
    p = malloc(0x30);
    if (arg1 != 0) {
        M2C_FIELD(p, void **, 0x24) = malloc(arg1 * 0x10);
    } else {
        M2C_FIELD(p, void **, 0x24) = NULL;
    }
    M2C_FIELD(p, s32 *, 0) = arg1;
    M2C_FIELD(p, s32 *, 0xC) = 0;
    M2C_FIELD(p, s32 *, 0x18) = 0;
    if (arg2 != 0) {
        M2C_FIELD(p, void **, 0x28) = malloc(arg2 * 8);
    } else {
        M2C_FIELD(p, void **, 0x28) = NULL;
    }
    M2C_FIELD(p, s32 *, 4) = arg2;
    M2C_FIELD(p, s32 *, 0x10) = 0;
    M2C_FIELD(p, s32 *, 0x1C) = 0;
    if (arg3 != 0) {
        M2C_FIELD(p, void **, 0x2C) = malloc(arg3 * 8);
    } else {
        M2C_FIELD(p, void **, 0x2C) = NULL;
    }
    M2C_FIELD(p, s32 *, 8) = arg3;
    M2C_FIELD(p, s32 *, 0x14) = 0;
    M2C_FIELD(p, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0) &= ~3;
    M2C_FIELD(arg0, void **, 0x98) = p;
    M2C_FIELD(arg0, s32 *, 0) |= 3;
    return 0;
}

static void func_802553D4() {
    s32 idx;
    f32 spC4;
    u8 *var_s0;
    s32 sp150;
    s32 *var_fp;
    s32 *sp148;
    UnkStruct_800AEDF0 *temp_v0_41;
    s32 var_s5;
    f32 temp_fs1_3;
    struct { f32 *obj; s32 dir; } sp134;
    f32 temp_fs2;
    f32 sp12C;
    s32 var_s2;
    f32 temp_fs3;
    s32 var_s3;
    f32 temp_fv0;
    s32 sp118;
    f32 sp10C[3];
    u8 *sp108;
    s32 var_s4;
    Pt2x4 spE4;
    s32 temp_s2;
    s32 temp_v0_2;
    s32 temp_v1;
    u8 *temp_a0_3;
    u8 *temp_s1;
    u8 *temp_v0_6;

    sp108 = func_8023A840();
    sp148 = func_8023A834();
    var_fp = func_802391F0();
    sp118 = M2C_FIELD(var_fp, s32 *, 0xC);
    func_802515D8((f32 *) var_fp);
    func_80255174((f32 *) var_fp);
    M2C_FIELD(var_fp, f32 *, 0x74) = func_80252598((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
    for (;;) {
    if ((D_802AC5D0 & 4) && (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0)) {
        M2C_FIELD(var_fp, s32 *, 0) = 0;
        M2C_FIELD(var_fp, s32 *, 4) = 0xF3;
        M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
        M2C_FIELD(M2C_FIELD(var_fp, void **, 0x9C), f32 *, 8) = 0.0f;
        M2C_FIELD(var_fp, s32 *, 0x88) = 0x3C;
        M2C_FIELD(var_fp, s32 *, 0x90) = 0;
        M2C_FIELD(var_fp, s32 *, 0x11C) = 0;
        M2C_FIELD(var_fp, s32 *, 0x120) = 0;
        M2C_FIELD(var_fp, u32 *, 0x94) = 0U;
        if (M2C_FIELD(var_fp, s32 *, 0x98) != 0) {
            func_80251424((f32 *) var_fp);
        }
    } else if ((func_80243D2C(M2C_FIELD(var_fp, s32 *, 0x10)) <= 0) || (M2C_FIELD(var_fp, s32 *, 0x10) == -1)) {
        if (D_802AC5D0 & 4) {
            M2C_FIELD(var_fp, s32 *, 0x10) = func_80251708(sp118);
            if (M2C_FIELD(var_fp, s32 *, 0x10) != -1) {
                M2C_FIELD(var_fp, void **, 0x1C) = func_802443F4(M2C_FIELD(var_fp, s32 *, 0x10));
            }
            func_802515D8((f32 *) var_fp);
            M2C_FIELD(var_fp, s32 *, 4) = 4;
            M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
            func_802530A8((f32 *) var_fp);
        } else {
            break;
        }
    } else if (!(D_802AC5D0 & 0x10) && !(M2C_FIELD(var_fp, s32 *, 0) & 4)) {
        func_802515D8((f32 *) var_fp);
        func_80255174((f32 *) var_fp);
        switch (M2C_FIELD(var_fp, u32 *, 0x14)) {                          /* switch 1 */
        case 0:                                     /* switch 1 */
            if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) {
                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                M2C_FIELD(var_fp, s32 *, 0) |= 0;
                M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                break;
            }
            if (!(M2C_FIELD(var_fp, s32 *, 0x124) & 8) && (M2C_FIELD(sp108, s32 *, 0x30) < 0x7D1)) {
                if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk24 != 3) {
                    temp_v0_2 = func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC));
                    if (temp_v0_2 < (M2C_FIELD(sp108, s32 *, 0x10) == 0 ? 3 : 4)) {
                        func_80233C80((f32 *) ((u8 *)var_fp + 0x20));
                        M2C_FIELD(var_fp, s32 *, 0x124) = (s32) (M2C_FIELD(var_fp, s32 *, 0x124) | 8);
                        M2C_FIELD(sp108, s32 *, 0x2C) = (s32) (M2C_FIELD(sp108, s32 *, 0x2C) + 1);
                    }
                }
            }
            func_80254F20((f32 *) var_fp);
            if (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0) {
loop_25:
                func_80239094();
                goto loop_25;
            }
            if ((M2C_FIELD(var_fp, s32 *, 0) & 3) == 1) {
                if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x8000) != 0) {
                    if (func_80234248(0x64) >= 0x33) {
                        func_80254C90((f32 *) var_fp);
                    } else {
                        func_80252174((f32 *) var_fp);
                    }
                } else if ((func_80254E20((f32 *) var_fp, 2, 1) == 0) && (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x20) == 0) && (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x1000) == 0)) {
                    if (func_80251BDC((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) != -1) {
                        temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                        sp12C = temp_fv0;
                        temp_s2 = func_802519B4(temp_fv0);
                        if (func_80251B08(1, (u8 *)var_fp + 0x38, temp_s2) != NULL) {
                            M2C_FIELD(var_fp, f32 *, 0x74) = sp12C;
                            func_80252048((f32 *) var_fp);
                        } else {
                            goto block_38;
                        }
                    } else {
block_38:
                        sp12C = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                        temp_v0_2 = func_80252330((s32 *) ((u8 *)var_fp + 0x38), sp12C);
                        temp_v0_2 = func_80251AC8(temp_v0_2);
                        if (sp12C < (D_802ACFB0 - 300.0f)) {
#if VERSION_JP
                            if (temp_v0_2 == 0) {
#else
                            if ((M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x14) < 50.0f) && (temp_v0_2 == 0)) {
#endif
                                func_80252048((f32 *) var_fp);
                            } else {
                                goto block_46;
                            }
                        } else if ((sp12C < (D_802ACFB0 - 150.0f)) && (temp_v0_2 == 0)) {
                            func_80255350((f32 *) var_fp);
                        } else {
block_46:
                            M2C_FIELD(var_fp, s32 *, 4) = 8;
                        }
                    }
                }
            }
            break;
        case 1:                                     /* switch 1 */
            if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) {
                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                M2C_FIELD(var_fp, s32 *, 0) |= 0;
                M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
            } else {
                func_80254F20((f32 *) var_fp);
                if (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) > 0) {
                    if (!(M2C_FIELD(var_fp, u32 *, 0) & 3)) {
                        if ((func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0) || (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) != 0)) {
                            M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                            M2C_FIELD(var_fp, s32 *, 0) |= 1;
                            M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                        } else {
                            func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x08000000);
                            func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0x16, 0);
                            func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                            M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) = (s32) (M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) | 0x20);
                            func_8023903C(7);
                            if ((func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0) || (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) != 0)) {
                                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                M2C_FIELD(var_fp, s32 *, 0) |= 1;
                                M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                            } else {
                                M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x68) = 8.0f;
                                M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x70) = 0.0f;
                                for (var_s3 = 0; var_s3 < 0x14; var_s3++) {
                                    if (func_802552B8((f32 *) var_fp) != 0) {
                                        func_802551B4((f32 *) var_fp);
                                        break;
                                    }
                                    func_80239094();
                                }
                                temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18);
                                M2C_FIELD(temp_a0_3, f32 *, 0x68) = (f32) M2C_FIELD(temp_a0_3, f32 *, 0x6C);
                                sp134.obj = (f32 *) var_fp;
                                sp134.dir = (func_802519B4(M2C_FIELD(var_fp, f32 *, 0x74)) - 1) & 7;
                                func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0x17, 0);
                                func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                                if (func_80234248(0x12C) < 0x65) {
                                    if (func_80234248(0xC8) < 0x65) {
                                        func_8026C660(0x1B2);
                                    } else {
                                        func_8026C660(0x1B3);
                                    }
                                }
                                for (var_s3 = 0; var_s3 < 8; var_s3++) {
                                    if (func_802552B8((f32 *) var_fp) != 0) {
                                        func_802551B4((f32 *) var_fp);
                                        break;
                                    }
                                    func_80239094();
                                }
                                for (var_s3 = 0; var_s3 < 3; var_s3++) {
                                    if ((func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0) || (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) != 0)) {
                                        func_802551B4((f32 *) var_fp);
                                        break;
                                    }
                                    func_8025500C(0x218, M2C_FIELD(var_fp, u8 **, 0x18));
                                    func_80238A10(func_8025D544, &sp134, 0, 0, 0x130);
                                    for (var_s2 = 0; var_s2 < 10; var_s2++) {
                                        if (func_802552B8((f32 *) var_fp) != 0) {
                                            func_802551B4((f32 *) var_fp);
                                            break;
                                        }
                                        func_80239094();
                                    }
                                    sp134.dir = (sp134.dir + 1) & 7;
                                }
                                for (var_s3 = 0; var_s3 < 10; var_s3++) {
                                    if (func_802552B8((f32 *) var_fp) != 0) {
                                        func_802551B4((f32 *) var_fp);
                                        break;
                                    }
                                    func_80239094();
                                }
                                if (func_802552B8((f32 *) var_fp) != 0) {
                                    func_802551B4((f32 *) var_fp);
                                } else {
                                    func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 0);
                                    for (var_s3 = 0; var_s3 < 50; var_s3++) {
                                        if (func_802552B8((f32 *) var_fp) != 0) {
                                            func_802551B4((f32 *) var_fp);
                                            break;
                                        }
                                        func_80239094();
                                    }
                                    M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x70) = 1.6333334f;
                                    M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x6C) = 16.333334f;
                                    M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x68) = 0.0f;
                                    M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                                    M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                    M2C_FIELD(var_fp, s32 *, 0) |= 1;
                                }
                            }
                        }
                    } else {
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        if ((FDIFF(M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x10)) <= 100.0f) && (FDIFF(M2C_FIELD(var_s0, f32 *, 0x18), M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x18)) <= 100.0f) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0)) {
                                temp_fv0 = (f32) ((s32) func_80251994((f32 *) ((u8 *)var_fp + 0x2C), (f32 *) ((u8 *)var_fp + 0x20)) / 45) * 45.0f;
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                temp_v1 = M2C_FIELD(var_fp, s32 *, 0);
                                M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                if (temp_v1 & 0x100) {
                                    M2C_FIELD(var_fp, s32 *, 4) = (s32) M2C_FIELD(var_fp, s32 *, 8);
                                    M2C_FIELD(var_fp, s32 *, 0) = temp_v1 & ~0x100;
                                }
                        } else {
block_101:
                            if (!(M2C_FIELD(var_fp, s32 *, 0) & 0x100)) {
                                M2C_FIELD(var_fp, s32 *, 0x90) = (s32) (M2C_FIELD(var_fp, s32 *, 0x90) + 1);
                            }
                            spE4 = D_802A0FA0;
                            temp_v1 = M2C_FIELD(var_fp, s32 *, 0);
                            if (!(temp_v1 & 0x100)) {
                                if (((s32) M2C_FIELD(var_fp, s32 *, 0x90) % 300) == 0) {
                                    var_s3 = (M2C_FIELD((M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40)), f32 *, 0x10) > 2350.0f) ? 0 : 1;
                                    if (M2C_FIELD((M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40)), f32 *, 0x18) < 1550.0f) {
                                        var_s3 |= 2;
                                    }
                                    M2C_FIELD(var_fp, s32 *, 0) = temp_v1 | 0x100;
                                    M2C_FIELD(var_fp, f32 *, 0x68) = spE4.p[var_s3].x;
                                    M2C_FIELD(var_fp, f32 *, 0x70) = spE4.p[var_s3].z;
                                    M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                    M2C_FIELD(var_fp, s32 *, 4) = 0;
                                } else {
                                    goto block_119;
                                }
                            } else {
                                var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                                if ((FDIFF(M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD(var_fp, f32 *, 0x68)) < 100.0f) && (FDIFF(M2C_FIELD(var_s0, f32 *, 0x18), M2C_FIELD(var_fp, f32 *, 0x70)) < 100.0f)) {
                                        M2C_FIELD(var_fp, s32 *, 4) = (s32) M2C_FIELD(var_fp, s32 *, 8);
                                        M2C_FIELD(var_fp, s32 *, 0) = temp_v1 & ~0x100;
                                }
block_119:
                                if ((M2C_FIELD(var_fp, s32 *, 4) == 1) || (func_80254E20((f32 *) var_fp, 1, 1) == 0)) {
                                    if ((func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) < 150.0f) && (M2C_FIELD(var_fp, s32 *, 4) != 5) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) && (M2C_FIELD(var_fp, u32 *, 0x94) == 0)) {
                                        func_80251E5C((f32 *) var_fp);
                                        M2C_FIELD(var_fp, u32 *, 0x94) = 0x1EU;
                                        temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x2C), (f32 *) ((u8 *)var_fp + 0x20));
                                        M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                        M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                        M2C_FIELD(var_fp, s32 *, 4) = 5;
                                        M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                                    } else {
                                        temp_v0_2 = M2C_FIELD(var_fp, u32 *, 0x94);
                                        if (temp_v0_2 != 0) {
                                            M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (temp_v0_2 - 1);
                                        }
                                        if ((func_80234248(0x64) >= 0x60) && (temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18), (M2C_FIELD(temp_a0_3, f32 *, 0x68) == 0)) && (M2C_FIELD(temp_a0_3, f32 *, 0x6C) == 0) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) && (func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) > 500.0f)) {
                                            temp_fv0 = (f32) (s32) (func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) / 45.0f) * 45.0f;
                                            M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                            M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                            M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                                            M2C_FIELD(var_fp, s32 *, 0) |= 0;
                                            M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                                        } else {
                                            M2C_FIELD(var_fp, s32 *, 4) = 0x24;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 2:                                     /* switch 1 */
            if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) {
                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                M2C_FIELD(var_fp, s32 *, 0) |= 0;
                M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
            } else {
                func_80254F20((f32 *) var_fp);
                if (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0) {
                    func_802452E8(0);
                    func_80251534(0);
                } else if (!(M2C_FIELD(var_fp, s32 *, 0) & 3)) {
                    if (func_802552B8((f32 *) var_fp) == 0) {
                        M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x68) = 20.0f;
                        M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x70) = 1.6333334f;
                        M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x6C) = 16.333334f;
                        func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x08000000);
                        var_s4 = 0;
                        var_s3 = 0;
                        func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0x18, 0);
                        func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                        M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) = (s32) (M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) | 0x20);
loop_143:
                        if (func_802552B8((f32 *) var_fp) == 0) {
                            func_80239094();
                            var_s3 += 1;
                            if (var_s3 != 0x14) {
                                goto loop_143;
                            }
                        }
loop_145:
                        if ((func_802552B8((f32 *) var_fp) == 0) && (M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x68) != 0.0f)) {
                            func_80239094();
                            goto loop_145;
                        }
loop_148:
                        if (func_802552B8((f32 *) var_fp) == 0) {
                            func_80239094();
                            var_s4 += 1;
                            if (var_s4 != 8) {
                                goto loop_148;
                            }
                        }
                        if (func_802552B8((f32 *) var_fp) == 0) {
                            var_s3 = 0;
                            func_8024585C(1);
                            func_80245280(1);
                            func_8024585C(0);
                            func_8026C660(0x1B6);
                            func_8025500C(0x229, M2C_FIELD(var_fp, u8 **, 0x18));
                            temp_s1 = func_80231274(0x32D, 0x03080200, 0x60, NULL);
                            temp_a0_3 = M2C_FIELD(temp_s1, void **, 0x40);
                            func_80255040(temp_a0_3, M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40));
                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), s16 *, 0x36) = 0x80;
                            M2C_FIELD(temp_s1, f32 *, 0x6C) = 0.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x70) = 0.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x68) = 0.0f;
                            M2C_FIELD(temp_s1, s32 *, 0x30) = 1;
                            M2C_FIELD(temp_s1, f32 *, 0x38) = 0.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x34) = 40.0f;
                            func_80229C90((s32) M2C_FIELD(temp_s1, void **, 0x40), 0, 0, 0, -0x60, -0x400);
                            do {
                                if (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0) {
                                    M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                    M2C_FIELD(var_fp, s32 *, 0) |= 1;
                                    M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                                    break;
                                }
                                M2C_FIELD((M2C_FIELD(temp_s1, void **, 0x40)), f32 *, 0x28) = (f32) ((f64) M2C_FIELD((M2C_FIELD(temp_s1, void **, 0x40)), f32 *, 0x28) + 0.3000000117579475);
                                M2C_FIELD((M2C_FIELD(temp_s1, void **, 0x40)), f32 *, 0x2C) = (f32) ((f64) M2C_FIELD((M2C_FIELD(temp_s1, void **, 0x40)), f32 *, 0x2C) + 0.3000000117579475);
                                M2C_FIELD((M2C_FIELD(temp_s1, void **, 0x40)), f32 *, 0x30) = (f32) ((f64) M2C_FIELD((M2C_FIELD(temp_s1, void **, 0x40)), f32 *, 0x30) + 0.3000000117579475);
                                func_80232DB4(temp_s1);
                                if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0x10), 0x1000) != 0) {
                                    M2C_FIELD(temp_s1, s32 *, 8) = (s32) (M2C_FIELD(temp_s1, s32 *, 8) & ~0x200);
                                }
                                if (!(M2C_FIELD(var_fp, s32 *, 0x124) & 8) && (func_8022F550((s32) temp_s1, 1) == (s32) M2C_FIELD(var_fp, void **, 0x1C))) {
                                    func_80233C80((f32 *) ((u8 *)var_fp + 0x2C));
                                    M2C_FIELD(var_fp, s32 *, 0x124) = (s32) (M2C_FIELD(var_fp, s32 *, 0x124) | 8);
                                    M2C_FIELD(sp108, s32 *, 0x2C) = (s32) (M2C_FIELD(sp108, s32 *, 0x2C) + 1);
                                }
                                func_80239094();
                                var_s3 += 1;
                            } while (var_s3 < 0x1E);
                            var_s3 = 0;
                            do {
                                if (!(M2C_FIELD(var_fp, s32 *, 0x124) & 8) && (func_8022F550((s32) temp_s1, 1) == (s32) M2C_FIELD(var_fp, void **, 0x1C))) {
                                    func_80233C80((f32 *) ((u8 *)var_fp + 0x2C));
                                    M2C_FIELD(var_fp, s32 *, 0x124) = (s32) (M2C_FIELD(var_fp, s32 *, 0x124) | 8);
                                    M2C_FIELD(sp108, s32 *, 0x2C) = (s32) (M2C_FIELD(sp108, s32 *, 0x2C) + 1);
                                }
                                func_80239094();
                                var_s3 += 1;
                            } while (var_s3 != 0xA);
                            func_8022FC90(temp_s1);
                            func_80239094();
                            func_8024585C(1);
                            func_802452E8(0);
                            func_8024585C(0);
                            M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x70) = 1.6333334f;
                            M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                            M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                            M2C_FIELD(var_fp, s32 *, 0) |= 1;
                            M2C_FIELD(var_fp, u32 *, 0x94) = 0U;
                            M2C_FIELD(var_fp, s32 *, 0x90) = 0x14;
                        }
                    }
                } else {
                    switch (M2C_FIELD(var_fp, u32 *, 0x94)) {               /* switch 2 */
                    case 0:                         /* switch 2 */
                        if (--M2C_FIELD(var_fp, s32 *, 0x90) == 0) {
                            M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                        }
                        break;
                    case 1:                         /* switch 2 */
                        if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0x10), 0x1000) != 0) {
                            M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                            if (func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) <= 300.0f) {
                                M2C_FIELD(var_fp, s32 *, 0) |= 0x100;
                                M2C_FIELD(var_fp, f32 *, 0x68) = (f32) M2C_FIELD(var_fp, f32 *, 0x2C);
                                M2C_FIELD(var_fp, f32 *, 0x70) = (f32) M2C_FIELD(var_fp, f32 *, 0x34);
                                M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                M2C_FIELD(var_fp, s32 *, 4) = 0;
                                M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                            }
                        } else {
                            M2C_FIELD(var_fp, u32 *, 0x94) = -1U;
                            M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                        }
                        break;
                    case 2:                         /* switch 2 */
                        if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0x10), 0x1000) != 0) {
                            if (func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) <= 100.0f) {
                                M2C_FIELD(var_fp, f32 *, 0x80) = (f32) M2C_FIELD(var_fp, f32 *, 0x74);
                                temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                                M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                func_80254EC4((f32 *) var_fp);
                                M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                                M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                                M2C_FIELD(var_fp, s32 *, 0x90) = 0x28;
                                M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(var_fp, f32 *, 0x80);
                            }
                            M2C_FIELD(var_fp, f32 *, 0x68) = (f32) M2C_FIELD(var_fp, f32 *, 0x2C);
                            M2C_FIELD(var_fp, f32 *, 0x70) = (f32) M2C_FIELD(var_fp, f32 *, 0x34);
                            break;
                        } else {
                            M2C_FIELD(var_fp, u32 *, 0x94) = -1U;
                            M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                        }
                        break;
                    case 3:                         /* switch 2 */
                        if (--M2C_FIELD(var_fp, s32 *, 0x90) == 0) {
                            M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                        }
                        break;
                    case 4:                         /* switch 2 */
                        if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x8000) != 0) {
                            M2C_FIELD(var_fp, s32 *, 0) |= 0x100;
                            temp_v0_6 = (func_80255224((f32 *) ((u8 *)var_fp + 0x20), &D_802A0FC0, 6) * 0xC) + (u8 *) &D_802A0FC0;
                            M2C_FIELD(var_fp, f32 *, 0x68) = (f32) M2C_FIELD(temp_v0_6, f32 *, 0);
                            M2C_FIELD(var_fp, f32 *, 0x70) = (f32) M2C_FIELD(temp_v0_6, f32 *, 8);
                            M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                            M2C_FIELD(var_fp, f32 *, 0x78) = (f32) M2C_FIELD(var_fp, f32 *, 0x74);
                        } else {
                            M2C_FIELD(var_fp, u32 *, 0x94) = -1U;
                        }
                        break;
                    case 5:                         /* switch 2 */
                        if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x8000) != 0) {
                            temp_v0_2 = func_80252330((s32 *) ((u8 *) (u8 *)var_fp + 0x38), M2C_FIELD(var_fp, f32 *, 0x74));
                            if ((temp_v0_2 & 0x10) && !(temp_v0_2 & 0xF)) {
                                func_80254EC4((f32 *) var_fp);
                                M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                                M2C_FIELD(var_fp, u32 *, 0x94) = -1U;
                            }
                        } else {
                            M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                            M2C_FIELD(var_fp, u32 *, 0x94) = -1U;
                        }
                        break;
                    }
                    if (M2C_FIELD(var_fp, u32 *, 0x94) == -1U) {
                        temp_v1 = M2C_FIELD(var_fp, s32 *, 0x90);
                        if (temp_v1 != 0) {
                            M2C_FIELD(var_fp, s32 *, 0x90) = (s32) (temp_v1 - 1);
                        }
                        if (!(M2C_FIELD(var_fp, s32 *, 0) & 0x100) && (func_80254E20((f32 *) var_fp, 1, 0x21) == 0)) {
                            temp_fv0 = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                            sp12C = temp_fv0;
                            if ((temp_fv0 > 250.0f) && (temp_fv0 <= 350.0f) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) && (func_80234248(0x64) >= 0x47) && (temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18), (M2C_FIELD(temp_a0_3, f32 *, 0x68) == 0)) && (M2C_FIELD(temp_a0_3, f32 *, 0x6C) == 0)) {
                                temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                                M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                                M2C_FIELD(var_fp, s32 *, 0) |= 0;
                                M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                            } else if (func_80252724(var_fp) != 0) {
                                M2C_FIELD(var_fp, s32 *, 4) = 4;
                            } else {
                                M2C_FIELD(var_fp, s32 *, 4) = 0x28;
                            }
                        }
                    }
                }
            }
            break;
        case 3:                                     /* switch 1 */
            if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) {
                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                M2C_FIELD(var_fp, s32 *, 0) |= 0;
                M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
            } else {
                func_80254F20((f32 *) var_fp);
                if (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0) {
                    func_80251534(0);
                } else if (func_80255098((f32 *) var_fp) == 0) {
                    temp_v1 = M2C_FIELD(var_fp, s32 *, 0x90);
                    if (temp_v1 != 0) {
                        M2C_FIELD(var_fp, s32 *, 0x90) = (s32) (temp_v1 - 1);
                    }
                    if (!(M2C_FIELD(var_fp, s32 *, 0) & 3)) {
                        var_s5 = 0;
                        var_s4 = 0;
                        func_8025500C(0x237, M2C_FIELD(var_fp, u8 **, 0x18));
                        spC4 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                        var_s3 = func_802519B4(spC4);
                        D_802ACFC8 = var_s3;
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        temp_s2 = func_8028A81C(0x15, M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD(var_s0, f32 *, 0x14) + 50.0f, M2C_FIELD(var_s0, f32 *, 0x18), 0);
                        for (var_s4 = 0; var_s4 < 18; var_s4++) {
                            if (func_80255098((f32 *) var_fp) != 0) {
                                func_802551B4((f32 *) var_fp);
                                break;
                            }
                            func_80239094();
                        }
                        func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0x19, 0);
                        func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                        M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) |= 0x20;
                        for (var_s4 = 0; var_s4 < 12; var_s4++) {
                            if (func_80255098((f32 *) var_fp) != 0) {
                                func_802551B4((f32 *) var_fp);
                                break;
                            }
                            func_80239094();
                        }
                        func_8028A4E0(temp_s2);
                        func_80254FA8((f32 *) var_fp);
                        for (sp12C = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) * 2; sp12C > 50.0f; sp12C -= 25.0f) {
                            func_802515D8((f32 *) var_fp);
                            if (func_80255098((f32 *) var_fp) != 0) {
                                func_802551B4((f32 *) var_fp);
                                break;
                            }
                            func_80291944(M2C_FIELD(var_fp, f32 **, 0x18), D_802A0F7C[var_s3], 20.0f);
                            func_80230914(M2C_FIELD(var_fp, f32 **, 0x18));
                            func_802909FC(M2C_FIELD(var_fp, f32 **, 0x18), func_8025D504);
                            if ((func_8026E8B8() >= M2C_FIELD(M2C_FIELD(temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14)) ? 1 : 0) {
                                func_8024585C(1);
                                func_802452E8(0);
                                func_8024585C(0);
                                break;
                            }
                            var_s5 = func_8022F4AC((s32) temp_a0_3, 0x10, D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk4C);
                            if (var_s5 != 0) {
                                func_80232BA0((u8 *)M2C_FIELD(var_fp, f32 **, 0x18) + 0x58, M2C_FIELD(var_fp, f32 **, 0x18));
                                break;
                            }
                            func_80239094();
                        }
                        if ((var_s5 != (s32) M2C_FIELD(var_fp, void **, 0x1C)) && (func_80255098((f32 *) var_fp) != 0)) {
                            func_802551B4((f32 *) var_fp);
                        } else {
                            if (var_s5 == (s32) M2C_FIELD(var_fp, void **, 0x1C)) {
                                func_8024585C(1);
                                func_802452E8(1);
                                func_8024585C(0);
                                func_80247C50(0);
                                func_802452E8(1);
                            }
                            for (var_s3 = 0xB; var_s3 > 0; var_s3--) {
                                if ((var_s5 != (s32) M2C_FIELD(var_fp, void **, 0x1C)) && (func_80255098((f32 *) var_fp) != 0)) {
                                    func_802551B4((f32 *) var_fp);
                                    break;
                                }
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = (f32) var_s3;
                                func_80239094();
                            }
                            if ((var_s5 != (s32) M2C_FIELD(var_fp, void **, 0x1C)) && (func_80255098((f32 *) var_fp) != 0)) {
                                func_802551B4((f32 *) var_fp);
                            } else {
                                if (var_s5 == (s32) M2C_FIELD(var_fp, void **, 0x1C)) {
                                    func_802452E8(1);
                                    func_8024585C(1);
                                    func_802452E8(1);
                                    func_8024585C(0);
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) = W360(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) + 180.0f);
                                    D_802ACFBC = 1;
                                    func_80237290();
                                    func_802346C8(M2C_FIELD((M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40)), f32 *, 0x10), M2C_FIELD((M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40)), f32 *, 0x14) + 50.0f, M2C_FIELD((M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40)), f32 *, 0x18));
                                    func_80234778(32768.0f, 20.0f, 800.0f);
                                    var_s3 = 0;
                                    sp12C = 0;
                                    do {
                                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                                        M2C_FIELD(var_s0, f32 *, 0x10) -= ((f32 (*)[2]) D_802A0F3C)[D_802ACFC8][0];
                                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                                        M2C_FIELD(var_s0, f32 *, 0x18) -= M2C_FIELD((D_802A0F3C + (D_802ACFC8 * 8)), f32 *, 4);
                                        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14) = (f32) (func_80234434(sp12C) * 20.0f);
                                        sp12C += 6.0f;
                                        func_80239094();
                                        var_s3 += 1;
                                    } while (var_s3 != 0x1E);
                                    func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0x1A, 0);
                                    func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                                    func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 0, 0);
                                    func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), -1, 1);
                                    M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) = (s32) (M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) | 0x20);
                                    func_8022979C((s32) M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 4, 0xC);
                                    func_8022979C((s32) M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 5, 0xD);
                                    func_8023903C(0xE);
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = (f32) (func_8025E63C() * (f64) (func_80229D3C(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 0) - 0.01f));
                                    func_80238A10(func_8025D35C, (s32) M2C_FIELD(var_fp, f32 **, 0x18), 0, 0, 0x130);
                                    func_8023903C(0xF);
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = (f32) (func_8025E63C() * (f64) (func_80229D3C(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 0) - 0.01f));
                                    func_80238A10(func_8025D35C, (s32) M2C_FIELD(var_fp, f32 **, 0x18), 0, 0, 0x130);
                                    func_8023903C(0x10);
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = (f32) (func_8025E63C() * (f64) (func_80229D3C(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 0) - 0.01f));
                                    func_80238A10(func_8025D35C, (s32) M2C_FIELD(var_fp, f32 **, 0x18), 0, 0, 0x130);
                                    func_8023903C(0xD);
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = (f32) (func_8025E63C() * (f64) (func_80229D3C(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 0) - 0.01f));
                                    func_80238A10(func_8025D35C, (s32) M2C_FIELD(var_fp, f32 **, 0x18), 0, 0, 0x130);
                                    func_8023903C(0x14);
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = (f32) (func_8025E63C() * (f64) (func_80229D3C(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 0) - 0.01f));
                                    func_80238A10(func_8025D35C, (s32) M2C_FIELD(var_fp, f32 **, 0x18), 0, 0, 0x130);
                                    func_8022979C((s32) M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 4, 4);
                                    func_8022979C((s32) M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), 5, 5);
                                    D_802ACFBC = 0;
                                    func_802371C8();
                                    func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0, 0);
                                    func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                                    func_8024368C((s32) func_8025D1AC);
                                    temp_s1 = func_80231274(-1, 0x03000020, 0x30, NULL);
                                    func_80255040(M2C_FIELD(temp_s1, void **, 0x40), M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40));
                                    M2C_FIELD(temp_s1, f32 *, 0x6C) = 0.0f;
                                    M2C_FIELD(temp_s1, f32 *, 0x70) = 0.0f;
                                    M2C_FIELD(temp_s1, f32 *, 0x68) = 0.0f;
                                    M2C_FIELD(temp_s1, s32 *, 0x30) = 1;
                                    M2C_FIELD(temp_s1, f32 *, 0x34) = 50.0f;
                                    func_80232DB4(temp_s1);
                                    func_80245280(0);
                                    func_80239094();
                                    func_8022FC90(temp_s1);
                                    func_80239094();
                                    func_8024585C(1);
                                    func_802452E8(0);
                                    func_8024585C(0);
                                }
                                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                M2C_FIELD(var_fp, s32 *, 0) |= 1;
                                M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                            }
                        }
                    } else if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x20) == 0) {
                        if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x1000) == 0) {
                            if (func_80254E20((f32 *) var_fp, 2, 0x21) == 0) {
                                if (func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) >= 400.0f) {
                                    if (func_80251BDC((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) == -1) {
                                        temp_v0_2 = func_80252658((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                                        temp_v1 = temp_v0_2 & 1;
                                        temp_fs3 = FDIFF(M2C_FIELD(var_fp, f32 *, 0x20), M2C_FIELD(var_fp, f32 *, 0x2C));
                                        temp_fs2 = FDIFF(M2C_FIELD(var_fp, f32 *, 0x28), M2C_FIELD(var_fp, f32 *, 0x34));
                                        if (temp_fs2 < temp_fs3) {
                                            temp_v1 = temp_v0_2 & 2;
                                            if (((temp_v1 != 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 180.0f)) || ((temp_v1 == 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 0.0f))) {
                                                if ((temp_v0_2 & 1) != 0) {
                                                    M2C_FIELD(var_fp, f32 *, 0x74) = 0.0f;
                                                } else {
                                                    M2C_FIELD(var_fp, f32 *, 0x74) = 180.0f;
                                                }
                                                func_80252048((f32 *) var_fp);
                                            } else {
                                                M2C_FIELD(var_fp, f32 *, 0x74) = (temp_v1 != 0) ? 0.0f : 180.0f;
                                                goto block_t0;
                                            }
                                        } else if (((temp_v1 != 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 270.0f)) || ((temp_v1 == 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 90.0f))) {
                                            if ((temp_v0_2 & 2) != 0) {
                                                M2C_FIELD(var_fp, f32 *, 0x74) = 90.0f;
                                            } else {
                                                M2C_FIELD(var_fp, f32 *, 0x74) = 270.0f;
                                            }
                                            func_80252048((f32 *) var_fp);
                                        } else {
                                                M2C_FIELD(var_fp, f32 *, 0x74) = (temp_v1 != 0) ? 90.0f : 270.0f;
block_t0:
                                                M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                                        }
                                    } else {
                                        goto block_305;
                                    }
                                } else if ((func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) < 150.0f) && (M2C_FIELD(var_fp, s32 *, 4) != 5)) {
                                    func_80251E5C((f32 *) var_fp);
                                    M2C_FIELD(var_fp, f32 *, 0x74) = W360(M2C_FIELD(var_fp, f32 *, 0x74) + 180.0f);
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(var_fp, f32 *, 0x74);
                                    M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                    M2C_FIELD(var_fp, s32 *, 4) = 5;
                                    M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                                } else {
block_305:
                                    if ((func_80251BDC((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) != -1) && (temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18), (M2C_FIELD(temp_a0_3, f32 *, 0x68) == 0.0f)) && (M2C_FIELD(temp_a0_3, f32 *, 0x6C) == 0.0f) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) && (M2C_FIELD(var_fp, s32 *, 0x90) == 0)) {
                                        if ((func_80234248(0x64) >= 0xB) && (temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)), M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0, (func_80251B08(2, (u8 *)var_fp + 0x38, func_802519B4(temp_fv0)) == NULL))) {
                                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(var_fp, f32 *, 0x74);
                                            M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                            M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                                            M2C_FIELD(var_fp, s32 *, 0) |= 0;
                                            M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                                            M2C_FIELD(var_fp, s32 *, 0x90) = 0xB4;
                                        } else {
                                            goto block_316;
                                        }
                                    } else if (func_80234248(0x32) == 2) {
                                        func_80252048((f32 *) var_fp);
                                    } else {
block_316:
                                        M2C_FIELD(var_fp, s32 *, 4) = 0x28;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 4:                                     /* switch 1 */
            if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) {
                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                M2C_FIELD(var_fp, s32 *, 0) |= 0;
                M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                break;
            }
            if ((D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk14 == 1) || (D_802AC758 == 1)) {
                D_802AC5D0 |= 0x10;
                func_80247C50(0);
                func_80270770(0, 1);
                func_802313DC(func_802443F4(0), 0x40000);
                func_802268F4(0x20);
loop_322:
                func_80239094();
                goto loop_322;
            }
            func_80254F20((f32 *) var_fp);
            if (func_80251974(M2C_FIELD(var_fp, f32 **, 0x18), &sp12C) != NULL) {
                if (((M2C_FIELD(var_fp, s32 *, 4)) & 0xF) != 6) {
                    if (sp12C <= 490.0f) {
                        M2C_FIELD(var_fp, s32 *, 8) = (M2C_FIELD(var_fp, s32 *, 4));
                        M2C_FIELD(var_fp, s32 *, 4) = 6;
                        M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                    } else {
                        goto block_329;
                    }
                } else if (sp12C <= 490.0f) {
                    M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                } else {
                    goto block_329;
                }
            } else {
block_329:
                if (func_80254E20((f32 *) var_fp, 1, 0x21) == 0) {
                    M2C_FIELD(var_fp, s32 *, 4) = 0x28;
                }
            }
            break;
        case 5:                                     /* switch 1 */
            if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) {
                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                M2C_FIELD(var_fp, s32 *, 0) |= 0;
                M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                break;
            }
            if ((D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk14 == 1) || (D_802AC758 == 1)) {
                D_802AC5D0 |= 0x10;
                func_80247C50(0);
                func_80270770(0, 1);
                func_802313DC(func_802443F4(0), 0x40000);
                func_802268F4(0x20);
loop_336:
                func_80239094();
                goto loop_336;
            }
            if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x100) != 0) {
                M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = 11.0f;
                M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) = (s32) (M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) | 0x40);
            }
            func_80254F20((f32 *) var_fp);
            if (func_80255098((f32 *) var_fp) == 0) {
                if (!(M2C_FIELD(var_fp, s32 *, 0) & 3)) {
                    func_8025500C(0x247, M2C_FIELD(var_fp, u8 **, 0x18));
                    var_s3 = 0;
                    var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                    temp_s2 = func_8028A81C(0x15, M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD(var_s0, f32 *, 0x14) + 50.0f, M2C_FIELD(var_s0, f32 *, 0x18), 0);
loop_342:
                    if (func_80255098((f32 *) var_fp) == 0) {
                        func_80239094();
                        var_s3 += 1;
                        if (var_s3 < 0x1E) {
                            goto loop_342;
                        }
                    }
                    func_8028A4E0(temp_s2);
                    if (!(M2C_FIELD(var_fp, s32 *, 0) & 1)) {
                        var_s3 = 0;
                        func_8024368C((s32) func_8025D008);
                        temp_s1 = func_80231274(0x2CF, 0x03080020, 0x30, NULL);
                        temp_a0_3 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        func_80255064(M2C_FIELD(temp_s1, u8 **, 0x40), temp_a0_3, 0.0f, 80.0f, 0.0f);
                        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), f32 *, 0x2C) = 0.0f;
                        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), f32 *, 0x1C) = 90.0f;
                        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), s16 *, 0x36) = 0x80;
                        M2C_FIELD(temp_s1, f32 *, 0x6C) = 0.0f;
                        M2C_FIELD(temp_s1, f32 *, 0x70) = 0.0f;
                        M2C_FIELD(temp_s1, f32 *, 0x68) = 0.0f;
                        M2C_FIELD(temp_s1, s32 *, 0x30) = 2;
                        M2C_FIELD(temp_s1, f32 *, 0x34) = 30.0f;
                        M2C_FIELD(temp_s1, f32 *, 0x38) = 100.0f;
                        temp_s2 = func_8025500C(0x249, M2C_FIELD(var_fp, u8 **, 0x18));
loop_346:
                        if (func_80255098((f32 *) var_fp) == 0) {
                            M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x2C) = (f32) (M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x2C) + 0.2857143f);
                            func_80232DB4(temp_s1);
                            func_80239094();
                            var_s3 += 1;
                            if (var_s3 != 0xAF) {
                                goto loop_346;
                            }
                        }
                        if (var_s3 < 0xAA) {
                            func_8026BE80(temp_s2);
                        }
                        func_8022FC90(temp_s1);
                        M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                        M2C_FIELD(var_fp, s32 *, 0) |= 1;
                        M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                    }
                } else if (func_80254E20((f32 *) var_fp, 1, 0x21) == 0) {
                    var_s3 = func_80234248(0x64);
                    temp_fv0 = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                    sp12C = temp_fv0;
                    if (var_s3 >= 0x51) {
                        if ((temp_fv0 > 400.0f) && (temp_fv0 < 500.0f) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0)) {
                            temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                            M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                            M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                            M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                            M2C_FIELD(var_fp, s32 *, 0) |= 0;
                            M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                        } else {
                            goto block_358;
                        }
                    } else {
block_358:
                        M2C_FIELD(var_fp, s32 *, 4) = 0x24;
                    }
                }
            }
            break;
        case 6:                                     /* switch 1 */
            if ((D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) || (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0)) {
                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                M2C_FIELD(var_fp, s32 *, 0) |= 0;
                M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
            } else {
                func_80254F20((f32 *) var_fp);
                if (func_8026E938(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40)) == 20000.0f) {
                    func_802362B8(0x1F);
                    func_80251534(0);
                    if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk24 != 3) {
                        do {
                            func_80239094();
                        } while (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk24 != 3);
                    }
                    func_802346C8(2350.0f, 100.0f, 1720.0f);
                    func_80234778(0.0f, 45.0f, 2000.0f);
                } else if ((func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) <= 0) || (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk24 == 3)) {
                    func_80251534(0);
                } else {
                    if ((M2C_FIELD(var_fp, s32 *, 0) & 3) != 3) {
                        M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                    }
                    if ((M2C_FIELD(var_fp, s32 *, 4) == 0x21) && (func_80252724(var_fp) != 0)) {
                        M2C_FIELD(var_fp, s32 *, 4) = 0x24;
                    } else if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x8000) != 0) {
                        temp_v0_2 = func_80252330((s32 *) ((u8 *) (u8 *)var_fp + 0x38), M2C_FIELD(var_fp, f32 *, 0x74));
                        if (((temp_v0_2 & 0x10) && !(temp_v0_2 & 0xF)) || (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x18) >= 2050.0f)) {
                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = 0.0f;
                            func_80254EC4((f32 *) var_fp);
                            M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                        }
                    } else {
                        temp_v0_2 = M2C_FIELD(var_fp, u32 *, 0x94);
                        if (temp_v0_2 == 0) {
                            M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                        } else {
                            M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (temp_v0_2 - 1);
                        }
                        if (!(M2C_FIELD(var_fp, s32 *, 0) & 3)) {
                            func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0x1E, 0);
                            func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                            M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) = (s32) (M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) | 0x20);
                            func_8023903C(0x14);
                            temp_s1 = func_80231274(0x32F, 0x03080400, 0x60, NULL);
                            temp_v0_2 = func_802519B4(func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)));
                            spC4 = M2C_FIELD(((temp_v0_2 * 8) + D_802A0F3C), f32 *, 0) * 80.0f;
                            temp_a0_3 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                            var_s3 = temp_v0_2;
                            func_80255064(M2C_FIELD(temp_s1, u8 **, 0x40), temp_a0_3, spC4, 80.0f, M2C_FIELD(((temp_v0_2 * 8) + D_802A0F3C), f32 *, 4) * 80.0f);
                            M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), s16 *, 0x36) = 0x80;
                            M2C_FIELD(temp_s1, f32 *, 0x34) = 50.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x38) = 200.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x6C) = 0.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x70) = 0.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x68) = 0.0f;
                            M2C_FIELD(temp_s1, s32 *, 0x30) = 2;
                            M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), f32 *, 0x20) = (f32) ((f32) var_s3 * 45.0f);
                            func_8025500C(0x253, M2C_FIELD(var_fp, u8 **, 0x18));
                            temp_fv0 = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) * 2;
                            sp12C = temp_fv0;
                            if (temp_fv0 > 50.0f) {
                                var_s0 = (var_s3 * 8) + D_802A0F3C;
                                do {
                                    M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x10) += M2C_FIELD(var_s0, f32 *, 0) * 30.0f;
                                    M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x18) += M2C_FIELD(var_s0, f32 *, 4) * 30.0f;
                                    func_80232DB4(temp_s1);
                                    func_80239094();
                                    sp12C -= 25.0f;
                                } while (sp12C > 50.0f);
                            }
                            func_8022FC90(temp_s1);
                            func_8023903C(2);
                            if ((func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x1000) == 0) && (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0x10), 0x1000) != 0) && (func_8025E63C() < 0.25) && (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) > 0)) {
                                func_8025500C(0x275, M2C_FIELD(var_fp, u8 **, 0x18));
                                func_80231408(M2C_FIELD(var_fp, f32 **, 0x18), 0x80000);
                                func_80254FA8((f32 *) var_fp);
                                func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x11);
                                var_s3 = 0x1E;
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = 0xFF;
                                var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                                M2C_FIELD(var_s0, s32 *, 0xC) = (s32) (M2C_FIELD(var_s0, s32 *, 0xC) | 0x1000);
                                do {
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = (s16) (s32) (((f32) var_s3 / 30.0f) * 255.0f);
                                    func_80239094();
                                    var_s3 -= 1;
                                } while (var_s3 != 0);
                                func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x01040000);
                                do {
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x10) = (f32) (((f64) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x10) + (func_8025E63C() * 160.0)) - 80.0);
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x18) = (f32) (((f64) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x18) + (func_8025E63C() * 160.0)) - 80.0);
                                    func_802515D8((f32 *) var_fp);
                                } while ((func_8022F550((s32) M2C_FIELD(var_fp, f32 **, 0x18), 0x10) != 0) || (func_80251AC8(func_8026D7D8(M2C_FIELD(var_fp, s32 *, 0x38), M2C_FIELD(var_fp, s32 *, 0x3C), M2C_FIELD(var_fp, s32 *, 0x40))) != 0));
                                func_8025500C(0x275, M2C_FIELD(var_fp, u8 **, 0x18));
                                func_80231408(M2C_FIELD(var_fp, f32 **, 0x18), 0x01000000);
                                func_80231408(M2C_FIELD(var_fp, f32 **, 0x18), 0x11);
                                func_80255110((f32 *) var_fp);
                                var_s3 = 0;
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = 0;
                                do {
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = (s16) (s32) (((f32) var_s3 / 30.0f) * 255.0f);
                                    func_80239094();
                                    var_s3 += 1;
                                } while (var_s3 != 0x1E);
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = -1;
                                var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                                M2C_FIELD(var_s0, s32 *, 0xC) = (s32) (M2C_FIELD(var_s0, s32 *, 0xC) & ~0x1000);
                                func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x80000);
                                func_8024585C(1);
                                func_802452E8(0);
                                func_8024585C(0);
                                func_80255174((f32 *) var_fp);
                                if (func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) <= 100.0f) {
                                    if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0x10), 0x1000) != 0) {
                                        M2C_FIELD(var_fp, f32 *, 0x80) = (f32) M2C_FIELD(var_fp, f32 *, 0x74);
                                        temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                                        M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                        func_80254EC4((f32 *) var_fp);
                                        M2C_FIELD(var_fp, s32 *, 0) |= 0x100;
                                        M2C_FIELD(var_fp, f32 *, 0x68) = 2350.0f;
                                        M2C_FIELD(var_fp, f32 *, 0x70) = 2100.0f;
                                        M2C_FIELD(var_fp, f32 *, 0x78) = (f32) M2C_FIELD(var_fp, f32 *, 0x74);
                                        M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                        M2C_FIELD(var_fp, s32 *, 4) = 0;
                                        M2C_FIELD(var_fp, u32 *, 0x94) = 0x28U;
                                    } else {
                                        M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                                        goto block_401;
                                    }
                                } else {
                                    goto block_401;
                                }
                            } else {
block_401:
                                func_8024585C(1);
                                func_802452E8(0);
                                func_8024585C(0);
                                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                M2C_FIELD(var_fp, s32 *, 0) |= 1;
                                M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                            }
                        } else {
                            temp_s1 = func_80252CB4(M2C_FIELD(var_fp, f32 **, 0x18), &sp12C);
                            if (temp_s1 != NULL) {
                                if ((func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) && (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) > 0)) {
                                    var_s0 = (u8 *) func_802703B4((s32) temp_s1);
                                    if (var_s0 == 0) {
                                        var_s3 = 3;
                                    } else {
                                        var_s3 = ((s16) M2C_FIELD(var_s0, s16 *, 0x66) >> 1) + 2;
                                    }
                                    if (sp12C <= ((f32) var_s3 * 100.0f)) {
                                        if ((M2C_FIELD(var_s0, s16 *, 0x10) & 0x100) || (func_80254DC8(2, ((u8 *)var_fp + 0x20), 300.0f) >= 3) || (var_s0 == 0)) {
                                            func_8024585C(1);
                                            func_802452E8(1);
                                            func_8024585C(0);
                                            func_8025500C(0x275, M2C_FIELD(var_fp, u8 **, 0x18));
                                            func_80231408(M2C_FIELD(var_fp, f32 **, 0x18), 0x80000);
                                            func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x11);
                                            func_80254FA8((f32 *) var_fp);
                                            var_s3 = 0x1E;
                                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = 0xFF;
                                            var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                                            M2C_FIELD(var_s0, s32 *, 0xC) = (s32) (M2C_FIELD(var_s0, s32 *, 0xC) | 0x1000);
                                            do {
                                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = (s16) (s32) (((f32) var_s3 / 30.0f) * 255.0f);
                                                func_80239094();
                                                var_s3 -= 1;
                                            } while (var_s3 != 0);
                                            func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x01040000);
                                            func_8023903C(0x78);
                                            do {
                                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x10) = (f32) ((func_8025E63C() * 1100.0) + 1800.0);
                                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x18) = (f32) ((func_8025E63C() * 1100.0) + 800.0);
                                            } while (func_8022F550((s32) M2C_FIELD(var_fp, f32 **, 0x18), 0x10) != 0);
                                            func_8025500C(0x275, M2C_FIELD(var_fp, u8 **, 0x18));
                                            func_80231408(M2C_FIELD(var_fp, f32 **, 0x18), 0x01000000);
                                            func_80231408(M2C_FIELD(var_fp, f32 **, 0x18), 0x11);
                                            func_80255110((f32 *) var_fp);
                                            var_s3 = 0;
                                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = 0;
                                            do {
                                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = (s16) (s32) (((f32) var_s3 / 30.0f) * 255.0f);
                                                func_80239094();
                                                var_s3 += 1;
                                            } while (var_s3 != 0x1E);
                                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), s16 *, 0x36) = -1;
                                            var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                                            M2C_FIELD(var_s0, s32 *, 0xC) = (s32) (M2C_FIELD(var_s0, s32 *, 0xC) & ~0x1000);
                                            func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x80000);
                                            func_8024585C(1);
                                            func_802452E8(0);
                                            func_8024585C(0);
                                        } else {
                                            M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                            M2C_FIELD(var_fp, s32 *, 4) = 0x21;
                                        }
                                    } else {
                                        goto block_421;
                                    }
                                } else {
                                    goto block_421;
                                }
                            } else {
block_421:
                                if (func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) >= 400.0f) {
                                    if (func_80251BDC((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) == -1) {
                                        temp_v0_2 = func_80252658((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                                        temp_v1 = temp_v0_2 & 1;
                                        temp_fs3 = FDIFF(M2C_FIELD(var_fp, f32 *, 0x20), M2C_FIELD(var_fp, f32 *, 0x2C));
                                        temp_fs2 = FDIFF(M2C_FIELD(var_fp, f32 *, 0x28), M2C_FIELD(var_fp, f32 *, 0x34));
                                        if (temp_fs2 < temp_fs3) {
                                            temp_v1 = temp_v0_2 & 2;
                                            if (((temp_v1 != 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 180.0f)) || ((temp_v1 == 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 0.0f))) {
                                                if ((temp_v0_2 & 1) != 0) {
                                                    M2C_FIELD(var_fp, f32 *, 0x74) = 0.0f;
                                                } else {
                                                    M2C_FIELD(var_fp, f32 *, 0x74) = 180.0f;
                                                }
                                                func_80252048((f32 *) var_fp);
                                            } else {
                                                M2C_FIELD(var_fp, f32 *, 0x74) = (temp_v1 != 0) ? 0.0f : 180.0f;
                                                goto block_7c1;
                                            }
                                        } else if (((temp_v1 != 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 270.0f)) || ((temp_v1 == 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 90.0f))) {
                                            if ((temp_v0_2 & 2) != 0) {
                                                M2C_FIELD(var_fp, f32 *, 0x74) = 90.0f;
                                            } else {
                                                M2C_FIELD(var_fp, f32 *, 0x74) = 270.0f;
                                            }
                                            func_80252048((f32 *) var_fp);
                                        } else {
                                            M2C_FIELD(var_fp, f32 *, 0x74) = (temp_v1 != 0) ? 90.0f : 270.0f;
block_7c1:
                                            M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                                        }
                                    } else {
                                        goto block_458;
                                    }
                                } else if ((func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) < 150.0f) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) && (M2C_FIELD(var_fp, s32 *, 4) != 5)) {
                                    func_80251E5C((f32 *) var_fp);
                                    M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                    M2C_FIELD(var_fp, s32 *, 4) = 5;
                                    M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                                } else {
block_458:
                                    var_s3 = func_80234248(0x64);
                                    temp_fv0 = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                                    sp12C = temp_fv0;
                                    if ((var_s3 >= 0x51) && (temp_fv0 > 400.0f) && (temp_fv0 < 500.0f) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) && (M2C_FIELD(var_fp, s32 *, 0x90) == 0) && (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0xC)) > 0)) {
                                        temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                                        M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                        M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                        M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                                        M2C_FIELD(var_fp, s32 *, 0) |= 0;
                                        M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                                        if (func_8025E63C() < 0.5) {
                                            M2C_FIELD(var_fp, s32 *, 0x90) = 0xB4;
                                        } else {
                                            M2C_FIELD(var_fp, s32 *, 0x90) = 0;
                                        }
                                    } else {
                                        temp_v1 = M2C_FIELD(var_fp, s32 *, 0x90);
                                        if (temp_v1 != 0) {
                                            M2C_FIELD(var_fp, s32 *, 0x90) = (s32) (temp_v1 - 1);
                                        }
                                        if (func_80254DC8(2, ((u8 *)var_fp + 0x2C), 200.0f) > 0) {
                                            M2C_FIELD(var_fp, s32 *, 4) = 4;
                                        } else {
                                            var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                                            if ((FDIFF(M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD((M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40)), f32 *, 0x10)) <= 50.0f) || (FDIFF(M2C_FIELD(var_s0, f32 *, 0x18), M2C_FIELD((M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40)), f32 *, 0x18)) <= 50.0f)) {
                                                if (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) {
                                                    temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                                    M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                                }
                                            }
                                            M2C_FIELD(var_fp, s32 *, 4) = 0x28;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 7:                                     /* switch 1 */
            if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) {
                func_8024585C(1);
                func_802452E8(1);
                func_8024585C(0);
loop_484:
                func_80239094();
                goto loop_484;
            }
            func_80254F20((f32 *) var_fp);
            if (!(M2C_FIELD(var_fp, s32 *, 0) & 3) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14) >= 0.0f)) {
                if ((func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) != 0) || (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk24 == 3)) {
                    M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                    M2C_FIELD(var_fp, s32 *, 0) |= 1;
                    M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                } else {
                    var_s3 = 0;
                    func_8024585C(1);
                    func_802452E8(1);
                    func_8024585C(0);
                    M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x68) = 0.0f;
                    M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x70) = 0.0f;
                    do {
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        M2C_FIELD(var_s0, f32 *, 0x14) = (f32) (M2C_FIELD(var_s0, f32 *, 0x14) + 10.0f);
                        func_80239094();
                        var_s3 += 1;
                    } while (var_s3 != 0x1E);
                    temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18);
                    M2C_FIELD(temp_a0_3, f32 *, 0x68) = (f32) M2C_FIELD(temp_a0_3, f32 *, 0x6C);
                    func_8025500C(0x2E7, M2C_FIELD(var_fp, u8 **, 0x18));
                    func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x08000000);
                    func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0x16, 0);
                    func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                    M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) = (s32) (M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) | 0x20);
                    if (!(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40)) {
                        do {
                            func_80239094();
                        } while (!(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40));
                    }
                    temp_fs3 = func_80234434(M2C_FIELD(var_fp, f32 *, 0x74));
                    temp_fs2 = func_80234408(M2C_FIELD(var_fp, f32 *, 0x74));
                    temp_s2 = func_8025500C(0x2E9, M2C_FIELD(var_fp, u8 **, 0x18));
                    var_s3 = 0;
                    do {
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        M2C_FIELD(var_s0, f32 *, 0x10) = (f32) (M2C_FIELD(var_s0, f32 *, 0x10) + (temp_fs3 * 22.5f));
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        M2C_FIELD(var_s0, f32 *, 0x18) = (f32) (M2C_FIELD(var_s0, f32 *, 0x18) + (temp_fs2 * 22.5f));
                        if (var_s3 < 0x64) {
                            var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                            func_8026C454(temp_s2, M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD(var_s0, f32 *, 0x14), M2C_FIELD(var_s0, f32 *, 0x18));
                        }
                        func_80239094();
                        var_s3 += 1;
                    } while (var_s3 < 0x78);
                    if (temp_fs3 < 0.0f) {
                        sp10C[0] = 0.0f;
                    } else {
                        sp10C[0] = 4700.0f;
                    }
                    sp10C[1] = M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14);
                    sp10C[2] = (f32) ((func_8025E63C() * 1100.0) + 500.0);
                    func_8022F808(M2C_FIELD(var_fp, f32 **, 0x18), (f32 *) ((u8 *)var_fp + 0x20));
                    temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), sp10C);
                    sp12C = temp_fv0;
                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                    M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                    temp_fs3 = func_80234434(sp12C);
                    temp_fs2 = func_80234408(sp12C);
                    sp12C = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), sp10C);
                    var_s3 = 0;
                    do {
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        M2C_FIELD(var_s0, f32 *, 0x10) = (f32) (M2C_FIELD(var_s0, f32 *, 0x10) + (temp_fs3 * (sp12C / 120.0f)));
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        M2C_FIELD(var_s0, f32 *, 0x18) = (f32) (M2C_FIELD(var_s0, f32 *, 0x18) + (temp_fs2 * (sp12C / 120.0f)));
                        func_80239094();
                        var_s3 += 1;
                    } while (var_s3 < 0x78);
                    var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                    if (M2C_FIELD(var_s0, f32 *, 0x10) > 2350.0f) {
                        M2C_FIELD(var_s0, f32 *, 0x20) = 270.0f;
                        M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                    } else {
                        M2C_FIELD(var_s0, f32 *, 0x20) = 90.0f;
                        M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                    }
                    temp_s1 = func_80231274(0x2CF, 0x03080000, 0xD0, NULL);
                    M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), s32 *, 0xC) = (s32) (M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), s32 *, 0xC) | 0x1000);
                    temp_a0_3 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                    func_80255040(M2C_FIELD(temp_s1, void **, 0x40), temp_a0_3);
                    M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x1C) = 120.0f;
                    M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(var_fp, f32 *, 0x74);
                    M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x2C) = 20.0f;
                    M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), s16 *, 0x36) = 0x80;
                    M2C_FIELD(temp_s1, f32 *, 0x6C) = 0.0f;
                    M2C_FIELD(temp_s1, f32 *, 0x70) = 0.0f;
                    M2C_FIELD(temp_s1, f32 *, 0x68) = 0.0f;
                    var_s2 = func_8025500C(0x28E, M2C_FIELD(var_fp, u8 **, 0x18));
                    var_s4 = (s32) func_8025500C(0x28F, M2C_FIELD(var_fp, u8 **, 0x18));
                    var_s3 = 0;
                    do {
                        if (M2C_FIELD(var_fp, f32 *, 0x74) == 90.0f) {
                            var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                            M2C_FIELD(var_s0, f32 *, 0x10) = (f32) (M2C_FIELD(var_s0, f32 *, 0x10) + 39.166668f);
                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x10) += 39.166668f;
                        } else {
                            var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                            M2C_FIELD(var_s0, f32 *, 0x10) = (f32) (M2C_FIELD(var_s0, f32 *, 0x10) - 39.166668f);
                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x10) -= 39.166668f;
                        }
                        if (!(var_s3 % 4)) {
                            func_80238A10(func_8025CEA0, (s32) var_fp, 0, 0, 0x130);
                        }
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        func_8026C454(var_s2, M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD(var_s0, f32 *, 0x14), M2C_FIELD(var_s0, f32 *, 0x18));
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        func_8026C454(var_s4, M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD(var_s0, f32 *, 0x14), M2C_FIELD(var_s0, f32 *, 0x18));
                        func_80239094();
                        var_s3 += 1;
                    } while (var_s3 < 0x78);
                    func_8022FC90(temp_s1);
                    sp10C[0] = (f32) ((func_8025E63C() * 1100.0) + 1800.0);
                    sp10C[1] = M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14);
                    sp10C[2] = -200.0f;
                    func_8022F808(M2C_FIELD(var_fp, f32 **, 0x18), (f32 *) ((u8 *)var_fp + 0x20));
                    temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), sp10C);
                    sp12C = temp_fv0;
                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                    M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                    temp_fs3 = func_80234434(sp12C);
                    temp_fs2 = func_80234408(sp12C);
                    sp12C = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), sp10C);
                    var_s3 = 0;
                    do {
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        M2C_FIELD(var_s0, f32 *, 0x10) = (f32) (M2C_FIELD(var_s0, f32 *, 0x10) + (temp_fs3 * (sp12C / 120.0f)));
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        M2C_FIELD(var_s0, f32 *, 0x18) = (f32) (M2C_FIELD(var_s0, f32 *, 0x18) + (temp_fs2 * (sp12C / 120.0f)));
                        func_80239094();
                        var_s3 += 1;
                    } while (var_s3 < 0x78);
                    var_s3 = 0;
                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = 0.0f;
                    M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                    do {
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        M2C_FIELD(var_s0, f32 *, 0x18) = (f32) (M2C_FIELD(var_s0, f32 *, 0x18) + 10.416667f);
                        if (var_s3 == 0x50) {
                            var_s2 = func_8025500C(0x2EA, M2C_FIELD(var_fp, u8 **, 0x18));
                        }
                        if (var_s3 >= 0x51) {
                            var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                            func_8026C454(var_s2, M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD(var_s0, f32 *, 0x14), M2C_FIELD(var_s0, f32 *, 0x18));
                        }
                        func_80239094();
                        var_s3 += 1;
                    } while (var_s3 != 0x78);
                    func_8025500C(0x2E7, M2C_FIELD(var_fp, u8 **, 0x18));
                    temp_fv0 = func_80229D3C(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0) - 0.1f;
                    sp12C = temp_fv0;
                    if (temp_fv0 >= 1.0f) {
                        do {
                            M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = sp12C;
                            func_80239094();
                            temp_fv0 = sp12C - 1.0f;
                            sp12C = temp_fv0;
                        } while (temp_fv0 >= 1.0f);
                    }
                    M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x70) = 1.6333334f;
                    M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                    M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                    M2C_FIELD(var_fp, s32 *, 0) |= 1;
                    func_8024585C(1);
                    func_802452E8(0);
                    func_8024585C(0);
                }
            } else if (func_80243D2C(M2C_FIELD(var_fp, s32 *, 0x10)) > 0) {
                if (((func_80232D18(M2C_FIELD(var_fp, f32 **, 0x18), 0x40) != 0) && (D_802A0F9C == 0)) || (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk24 == 3) || (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14) < 0.0f)) {
                    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14) < 0.0f) {
                        func_8024585C(1);
                        func_802452E8(1);
                        func_8024585C(0);
                        D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk24 = 3;
                        M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x70) = 0.0f;
                        M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x6C) = 0.0f;
                    }
                    if (D_802A0F9C == 0) {
                        func_80238A10(func_8025CDAC, (s32) var_fp, 0, 0, 0x130);
                        func_802268F4(0x21);
                    }
                    temp_v0_41 = &D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)];
                    if ((temp_v0_41->unk14 == -1) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14) >= 0.0f)) {
                        func_80247C50(M2C_FIELD(var_fp, s32 *, 0xC));
                        func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x40000);
                        D_802ACFBC = 1;
                        func_80237290();
                        func_802362B8(0x10);
                        var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                        func_802346C8(M2C_FIELD(var_s0, f32 *, 0x10), M2C_FIELD(var_s0, f32 *, 0x14) + 50.0f, M2C_FIELD(var_s0, f32 *, 0x18));
                        func_80245280(1);
                        func_8024585C(1);
                        func_802452E8(1);
                        func_8024585C(0);
                        func_80277484();
                        func_8023903C(0x1E);
                        func_8026C660(0x1C6);
                        func_8023903C(0x5A);
                        func_8026C660(0x1C8);
                        func_8023903C(0x1E);
                        func_802362D4(0x10);
                        func_802371C8();
                        D_802ACFBC = 0;
                        func_80245280(0);
                        func_8024585C(1);
                        func_802452E8(0);
                        func_8024585C(0);
                    } else if ((temp_v0_41->unk24 == 3) || (((M2C_FIELD(sp108, s32 *, 0x10) == 0) ? 0 : -2) == (temp_v0_41->unk14 + 7)) || (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14) < 0.0f)) {
                        D_802AC5D0 |= 0x10;
                        func_80247C50(0);
                        func_80270770(0, 1);
                        func_802313DC(func_802443F4(0), 0x40000);
                        func_80247C50(M2C_FIELD(var_fp, s32 *, 0xC));
                        func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x40000);
                        if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) {
                            break;
                        }
                        func_802268F4(0x20);
                    } else {
                        if (((M2C_FIELD(sp108, s32 *, 0x10) == 0) ? 0 : -2) == (temp_v0_41->unk14 + 6)) {
                            func_8026C660(0x1C8);
                        }
                        func_8023903C(0x3C);
                    }
                    temp_v0_41 = &D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)];
                    temp_v0_41->unk14 -= 1;
                }
                    if (func_80254E20((f32 *) var_fp, 1, 0x21) == 0) {
                        var_s3 = func_80234248(0x64);
                        temp_fv0 = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                        sp12C = temp_fv0;
                        if ((var_s3 >= 0x5B) && (temp_fv0 > 400.0f) && (temp_fv0 < 500.0f) && (temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18), (M2C_FIELD(temp_a0_3, f32 *, 0x68) == 0.0f)) && (M2C_FIELD(temp_a0_3, f32 *, 0x6C) == 0.0f) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0)) {
                                temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                                M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                                M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                                M2C_FIELD(var_fp, s32 *, 0) |= 0;
                                M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                        } else {
                            M2C_FIELD(var_fp, s32 *, 4) = 0x28;
                        }
                    }
            }
            break;
        case 8:                                     /* switch 1 */
            if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0x10)].unk24 == 3) {
                func_8024585C(1);
                func_802452E8(1);
                func_8024585C(0);
loop_561:
                func_80239094();
                goto loop_561;
            }
            if ((D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk24 == 3) && (D_800AEF94 > 0)) {
                func_8024585C(2);
                func_802452E8(1);
                func_8024585C(0);
                func_802452E8(1);
                func_8023E8AC();
loop_565:
                func_80239094();
                goto loop_565;
            }
            func_80254F20((f32 *) var_fp);
            if (func_80255098((f32 *) var_fp) == 0) {
                if (!(M2C_FIELD(var_fp, s32 *, 0) & 3)) {
                    if (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) {
                        var_s3 = 0;
                        func_8024585C(1);
                        func_802452E8(1);
                        func_8024585C(0);
                        spC4 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                        sp12C = (f32) func_802519B4(spC4) * 45.0f;
                        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = sp12C;
                        M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                        func_8025500C(0x2AA, M2C_FIELD(var_fp, u8 **, 0x18));
                        func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0x17, 0);
                        func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                        M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) = (s32) (M2C_FIELD((M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4)), s32 *, 8) | 0x20);
                        if (!(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40)) {
                            do {
                                func_80239094();
                            } while (!(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40));
                        }
                        temp_s1 = func_80231274(0x2C7, 0x010C0000, 0xD0, NULL);
                        var_s0 = func_80231274(0x2C7, 0x010C0000, 0xD0, NULL);
                        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = sp12C;
                        M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                        func_80255064(M2C_FIELD(temp_s1, u8 **, 0x40), M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), (func_80234434(W360(sp12C + 90)) * 55.0f) + (func_80234434(W360(sp12C)) * 10.0f), 50.0f, (func_80234408(W360(sp12C + 90.0f)) * 55.0f) + (func_80234408(W360(sp12C)) * 10.0f));
                        M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x30) = 1.0f;
                        temp_fv0 = M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x30);
                        M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x2C) = temp_fv0;
                        M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x28) = temp_fv0;
                        func_80255064(M2C_FIELD(var_s0, u8 **, 0x40), M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), (func_80234434(W360M90(sp12C)) * 55.0f) + (func_80234434(W360(sp12C)) * 10.0f), 50.0f, (func_80234408(W360M90(sp12C)) * 55.0f) + (func_80234408(W360(sp12C)) * 10.0f));
                        M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x30) = 1.0f;
                        temp_a0_3 = M2C_FIELD(var_s0, void **, 0x40);
                        temp_fv0 = M2C_FIELD(temp_a0_3, f32 *, 0x30);
                        M2C_FIELD(temp_a0_3, f32 *, 0x2C) = temp_fv0;
                        M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x28) = temp_fv0;
                        M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), s16 *, 0x36) = 0xC8;
                        M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), s16 *, 0x36) = 0xC8;
                        func_8025500C(0x2AC, M2C_FIELD(var_fp, u8 **, 0x18));
                        do {
                            spC4 = M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x28) + 0.016666668f;
                            M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x30) = spC4;
                            M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x2C) = spC4;
                            M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x28) = spC4;
                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x30) = spC4;
                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x2C) = spC4;
                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x28) = spC4;
                            func_80239094();
                            var_s3 += 1;
                        } while (var_s3 < 0x3C);
                        func_8022FC90(temp_s1);
                        func_8022FC90(var_s0);
                        func_8025500C(0x2A8, M2C_FIELD(var_fp, u8 **, 0x18));
                        var_s5 = (s32) func_80231274(0x2D5, 0x01080000, 0xD0, NULL);
                        M2C_FIELD(M2C_FIELD(((u8 *) var_s5), void **, 0x40), s16 *, 0x36) = 0x80;
                        temp_v0_41 = M2C_FIELD(((u8 *) var_s5), void **, 0x40);
                        M2C_FIELD(temp_v0_41, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_41, s32 *, 0xC) | 0x10000);
                        func_80255064(M2C_FIELD(((u8 *) var_s5), u8 **, 0x40), M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), func_80234434(sp12C) * 40.0f, 40.0f, func_80234408(sp12C) * 40.0f);
                        M2C_FIELD(M2C_FIELD(((u8 *) var_s5), void **, 0x40), f32 *, 0x1C) = W360(sp12C + 90.0f);
                        M2C_FIELD(M2C_FIELD(((u8 *) var_s5), void **, 0x40), f32 *, 0x24) = 90.0f;
                        M2C_FIELD(M2C_FIELD(((u8 *) var_s5), void **, 0x40), f32 *, 0x2C) = 70.0f;
                        M2C_FIELD(M2C_FIELD(((u8 *) var_s5), void **, 0x40), f32 *, 0x30) = 3.0f;
                        temp_v0_41 = M2C_FIELD(((u8 *) var_s5), void **, 0x40);
                        M2C_FIELD(temp_v0_41, f32 *, 0x28) = (f32) M2C_FIELD(temp_v0_41, f32 *, 0x30);
                        temp_s1 = func_80231274(-1, 0x01000040, 0x20, NULL);
                        func_80255040(M2C_FIELD(temp_s1, void **, 0x40), M2C_FIELD(((u8 *) var_s5), void **, 0x40));
                        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), f32 *, 0x20) = sp12C;
                        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), f32 *, 0x1C) = 90.0f;
                        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), f32 *, 0x2C) = 70.0f;
                        M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x40), f32 *, 0x30) = 3.0f;
                        M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x28) = (f32) M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x30);
                        M2C_FIELD(temp_s1, s32 *, 0x30) = 2;
                        var_s3 = 0;
                        M2C_FIELD(temp_s1, f32 *, 0x34) = 60.0f;
                        M2C_FIELD(temp_s1, f32 *, 0x38) = 200.0f;
                        do {
                            temp_v0_41 = M2C_FIELD(((u8 *) var_s5), void **, 0x40);
                            M2C_FIELD(temp_v0_41, f32 *, 0x20) = W360(M2C_FIELD(temp_v0_41, f32 *, 0x20) + 10.0f);
                            func_80232DB4(temp_s1);
                            func_80239094();
                            var_s3 += 1;
                        } while (var_s3 < 0x78);
                        var_s3 = 0;
                        do {
                            temp_v0_41 = M2C_FIELD(((u8 *) var_s5), void **, 0x40);
                            M2C_FIELD(temp_v0_41, f32 *, 0x20) = W360(M2C_FIELD(temp_v0_41, f32 *, 0x20) + 10.0f);
                            temp_v0_41 = M2C_FIELD(((u8 *) var_s5), void **, 0x40);
                            M2C_FIELD(temp_v0_41, f32 *, 0x28) = (f32) (M2C_FIELD(temp_v0_41, f32 *, 0x28) - 0.025f);
                            temp_v0_41 = M2C_FIELD(((u8 *) var_s5), void **, 0x40);
                            M2C_FIELD(temp_v0_41, f32 *, 0x30) = (f32) (M2C_FIELD(temp_v0_41, f32 *, 0x30) - 0.025f);
                            M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x28) = (f32) (M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x28) - 0.025f);
                            M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x30) = (f32) (M2C_FIELD((M2C_FIELD(temp_s1, s32 *, 0x40)), f32 *, 0x30) - 0.025f);
                            func_80232DB4(temp_s1);
                            func_80239094();
                            var_s3 += 1;
                        } while (var_s3 != 0x78);
                        func_8022FC90(((u8 *) var_s5));
                        func_8022FC90(temp_s1);
                        func_8025500C(0x2AA, M2C_FIELD(var_fp, u8 **, 0x18));
                        temp_fv0 = func_80229D3C(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0) - 0.1f;
                        sp12C = temp_fv0;
                        if (temp_fv0 >= 1.0f) {
                            do {
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = sp12C;
                                func_80239094();
                                sp12C -= 1.0f;
                            } while (sp12C >= 1.0f);
                        }
                        func_8023903C(2);
                        func_8024585C(1);
                        func_802452E8(0);
                        func_8024585C(0);
                        M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                        M2C_FIELD(var_fp, s32 *, 0) |= 1;
                        M2C_FIELD(var_fp, s32 *, 0x88) = 0;
                    } else {
                        goto block_650;
                    }
                } else {
block_650:
                    if (func_80254E20((f32 *) var_fp, 1, 0x21) == 0) {
                        temp_fv0 = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                        sp12C = temp_fv0;
                        if ((temp_fv0 > 600.0f) && (func_80251BDC((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) != -1) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0)) {
                            var_s2 = 0;
                            var_s3 = func_802519B4(func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)));
                            temp_fv0 = (f32) var_s3 * 45.0f;
                            M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                            func_8024585C(1);
                            func_802452E8(1);
                            func_8024585C(0);
                            func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x08000000);
                            func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0x16, 0);
                            func_80229E38(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), -1, 1);
                            temp_s1 = M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4);
                            M2C_FIELD(temp_s1, s32 *, 8) = (s32) (M2C_FIELD(temp_s1, s32 *, 8) | 0x20);
                            if (!(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40)) {
                                do {
                                    func_80239094();
                                } while (!(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), s32 *, 8) & 0x40));
                            }
                            func_802313DC(M2C_FIELD(var_fp, f32 **, 0x18), 0x10);
                            var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                            temp_fs3 = M2C_FIELD(var_s0, f32 *, 0x10);
                            temp_fs2 = M2C_FIELD(var_s0, f32 *, 0x18);
                            func_8025500C(0x280, M2C_FIELD(var_fp, u8 **, 0x18));
                            func_80254FA8((f32 *) var_fp);
loop_658:
                            func_802515D8((f32 *) var_fp);
                            if (func_80251AC8(func_80252330((s32 *) ((u8 *) (u8 *)var_fp + 0x38), M2C_FIELD(var_fp, f32 *, 0x74))) == 0) {
                                func_80291944(M2C_FIELD(var_fp, f32 **, 0x18), D_802A0F7C[var_s3], 50.0f);
                                func_80230914(M2C_FIELD(var_fp, f32 **, 0x18));
                                func_802909FC(M2C_FIELD(var_fp, f32 **, 0x18), func_8025D504);
                                if (func_8022F550((s32) M2C_FIELD(var_fp, f32 **, 0x18), 0x10) != 0) {
                                    func_80232BA0((u8 *)M2C_FIELD(var_fp, f32 **, 0x18) + 0x58, M2C_FIELD(var_fp, f32 **, 0x18));
                                } else {
                                    if (!(var_s2 & 3)) {
                                        func_80238A10(func_8025CC5C, (s32) var_fp, 0, 0, 0x130);
                                    }
                                    var_s2 += 1;
                                    func_80239094();
                                    goto loop_658;
                                }
                            }
                            func_80231408(M2C_FIELD(var_fp, f32 **, 0x18), 0x10);
                            temp_fv0 = func_80229D3C(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), 0) - 0.1f;
                            sp12C = temp_fv0;
                            if (temp_fv0 >= 1.0f) {
                                do {
                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), void **, 0x48), void **, 4), f32 *, 4) = sp12C;
                                    func_80239094();
                                    sp12C -= 1.0f;
                                } while (sp12C >= 1.0f);
                            }
                            if (M2C_FIELD(var_fp, f32 *, 0x74) + 180.0f >= 360.0f) {
                                spC4 = M2C_FIELD(var_fp, f32 *, 0x74) + 180.0f - 360.0f;
                            } else {
                                if (M2C_FIELD(var_fp, f32 *, 0x74) + 180.0f < 0.0f) {
                                    sp10C[0] = M2C_FIELD(var_fp, f32 *, 0x74) + 180.0f + 360.0f;
                                } else {
                                    sp10C[0] = M2C_FIELD(var_fp, f32 *, 0x74) + 180.0f;
                                }
                                spC4 = sp10C[0];
                            }
                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = spC4;
                            M2C_FIELD(var_fp, f32 *, 0x74) = spC4;
                            func_80239094();
                            func_8024368C((s32) func_8025D008);
                            temp_s1 = func_80231274(-1, 0x40, 0x20, NULL);
                            temp_fv0 = M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x14) + 80.0f;
                            temp_v0_6 = M2C_FIELD(temp_s1, void **, 0x40);
                            M2C_FIELD(temp_v0_6, f32 *, 0x14) = temp_fv0;
                            M2C_FIELD(temp_v0_6, f32 *, 0x10) = temp_fs3;
                            M2C_FIELD(temp_v0_6, f32 *, 0x18) = temp_fs2;
                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x2C) = (f32) (((f32) var_s2 * 50.0f) / 160.0f);
                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x1C) = 90.0f;
                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x20) = W360(M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) + 180.0f);
                            M2C_FIELD(temp_s1, f32 *, 0x6C) = 0.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x70) = 0.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x68) = 0.0f;
                            M2C_FIELD(temp_s1, s32 *, 0x30) = 2;
                            M2C_FIELD(temp_s1, f32 *, 0x34) = 30.0f;
                            M2C_FIELD(temp_s1, f32 *, 0x38) = 160.0f;
                            temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18);
                            M2C_FIELD(temp_a0_3, s32 *, 0xC) = (s32) (M2C_FIELD(temp_a0_3, s32 *, 0xC) & ~0x40);
                            func_80232DB4(temp_s1);
                            func_80239094();
                            func_8022FC90(temp_s1);
                            temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18);
                            M2C_FIELD(temp_a0_3, s32 *, 0xC) = (s32) (M2C_FIELD(temp_a0_3, s32 *, 0xC) | 0x40);
                            func_8024585C(1);
                            func_802452E8(0);
                            func_8024585C(0);
                            M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                            M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                            M2C_FIELD(var_fp, s32 *, 0) |= 0;
                            M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                        } else if ((func_80234248(0x64) >= 0x5B) && (sp12C > 400.0f) && (sp12C < 500.0f) && (temp_a0_3 = M2C_FIELD(var_fp, f32 **, 0x18), (M2C_FIELD(temp_a0_3, f32 *, 0x68) == 0.0f)) && (M2C_FIELD(temp_a0_3, f32 *, 0x6C) == 0.0f) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) && (M2C_FIELD(var_fp, s32 *, 0x90) == 0)) {
                            spC4 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                            temp_fv0 = (f32) func_802519B4(spC4) * 45.0f;
                            M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                            M2C_FIELD(var_fp, s32 *, 0) &= ~3;
                            M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                            M2C_FIELD(var_fp, s32 *, 0) |= 0;
                            M2C_FIELD(var_fp, s32 *, 0x88) = -1;
                            M2C_FIELD(var_fp, s32 *, 0x90) = 0xB4;
                        } else {
                            temp_v1 = M2C_FIELD(var_fp, s32 *, 0x90);
                            if (temp_v1 != 0) {
                                M2C_FIELD(var_fp, s32 *, 0x90) = (s32) (temp_v1 - 1);
                            }
                            M2C_FIELD(var_fp, s32 *, 4) = 0x28;
                        }
                    }
                }
            }
            break;
        case 9:                                     /* switch 1 */
            func_80254F20((f32 *) var_fp);
            if (func_80251974(M2C_FIELD(var_fp, f32 **, 0x18), &sp12C) != NULL) {
                if (((M2C_FIELD(var_fp, s32 *, 4)) & 0xF) != 6) {
                    if (sp12C <= 490.0f) {
                        M2C_FIELD(var_fp, s32 *, 8) = (M2C_FIELD(var_fp, s32 *, 4));
                        M2C_FIELD(var_fp, s32 *, 4) = 6;
                        M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                    } else {
                        goto block_697;
                    }
                } else if (sp12C <= 490.0f) {
                    M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                } else {
                    goto block_697;
                }
            } else {
block_697:
                if (M2C_FIELD(var_fp, u32 *, 4) == 0x21) {
                    if (func_80252724(var_fp) != 0) {
                        M2C_FIELD(var_fp, s32 *, 4) = 0x24;
                    }
                }
                if (func_80254E20((f32 *) var_fp, 2, 0x21) == 0) {
                    if (func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) >= 300.0f) {
                        if (func_80251BDC((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) == -1) {
                            temp_v0_2 = func_80252658((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                            temp_v1 = temp_v0_2 & 1;
                            temp_fs3 = FDIFF(M2C_FIELD(var_fp, f32 *, 0x20), M2C_FIELD(var_fp, f32 *, 0x2C));
                            temp_fs2 = FDIFF(M2C_FIELD(var_fp, f32 *, 0x28), M2C_FIELD(var_fp, f32 *, 0x34));
                            if (temp_fs2 < temp_fs3) {
                                temp_v1 = temp_v0_2 & 2;
                                if (((temp_v1 != 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 180.0f)) || ((temp_v1 == 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 0.0f))) {
                                    if ((temp_v0_2 & 1) != 0) {
                                        M2C_FIELD(var_fp, f32 *, 0x74) = 0.0f;
                                    } else {
                                        M2C_FIELD(var_fp, f32 *, 0x74) = 180.0f;
                                    }
                                    func_80252048((f32 *) var_fp);
                                } else {
                                    M2C_FIELD(var_fp, f32 *, 0x74) = (temp_v1 != 0) ? 0.0f : 180.0f;
                                    goto block_tb;
                                }
                            } else if (((temp_v1 != 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 270.0f)) || ((temp_v1 == 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, void **, 0x1C), void **, 0x40), f32 *, 0x20) == 90.0f))) {
                                if ((temp_v0_2 & 2) != 0) {
                                    M2C_FIELD(var_fp, f32 *, 0x74) = 90.0f;
                                } else {
                                    M2C_FIELD(var_fp, f32 *, 0x74) = 270.0f;
                                }
                                func_80252048((f32 *) var_fp);
                            } else {
                                    M2C_FIELD(var_fp, f32 *, 0x74) = (temp_v1 != 0) ? 90.0f : 270.0f;
block_tb:
                                    M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                            }
                        } else {
                            goto block_740;
                        }
                    } else if ((func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) < 150.0f) && (func_80245408(M2C_FIELD(var_fp, s32 *, 0xC)) == 0) && (M2C_FIELD(var_fp, s32 *, 4) != 5)) {
                        func_80251E5C((f32 *) var_fp);
                        M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                        M2C_FIELD(var_fp, s32 *, 4) = 5;
                        M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
                    } else {
block_740:
                        M2C_FIELD(var_fp, s32 *, 4) = 0x28;
                    }
                }
            }
            break;
        default:                                    /* switch 1 */
            if (M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), f32 *, 0x6C) == 0.0f) {
                temp_fs3 = func_80251C48((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                temp_fs1_3 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C));
                if (func_80243EB4(M2C_FIELD(var_fp, s32 *, 0xC), 0x2000) != 0) {
                    func_80252D14((f32 *) var_fp);
                } else {
                    temp_v1 = M2C_FIELD(var_fp, u32 *, 0x94);
                    if ((temp_v1 == 0) && (temp_v1 = M2C_FIELD(var_fp, s32 *, 0x90), temp_v0_2 = temp_v1 - 1, (temp_v1 != 0))) {
                        M2C_FIELD(var_fp, s32 *, 0x90) = temp_v0_2;
                        if (temp_v0_2 == 0) {
                            M2C_FIELD(var_fp, s32 *, 4) = 0xF3;
                        }
                    } else if ((temp_v1 == 0) && (M2C_FIELD(var_fp, s32 *, 0x90) == 0) && (func_80252724(var_fp) != 0)) {
                        M2C_FIELD(var_fp, s32 *, 4) = 4;
                        M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                        M2C_FIELD(var_fp, s32 *, 0x90) = 0x32;
                        M2C_FIELD(var_fp, s32 *, 0x120) = 0;
                        for (var_s3 = 0; var_s3 < 5; var_s3++) {
                            M2C_FIELD((u8 *)var_fp + var_s3 * 0x18, s32 *, 0xA4) = (f32) var_s3;
                        }
                    } else {
                        if (D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk68 & 0xAC) {
                            M2C_FIELD(var_fp, s32 *, 8) = (s32) M2C_FIELD(var_fp, s32 *, 4);
                            M2C_FIELD(var_fp, s32 *, 4) = 3;
                            temp_fv0 = (f32) ((s32) temp_fs1_3 / 45) * 45.0f;
                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                            M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                            M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                        } else if (func_80243EF0(M2C_FIELD(var_fp, s32 *, 0xC)) != 0) {
                            if (M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), s32 *, 0x44) != 0) {
                                if (func_80244BA4(D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unkA4, 0x1000) != 0) {
                                    func_80252D14((f32 *) var_fp);
                                } else if ((M2C_FIELD(&sp148[M2C_FIELD(var_fp, s32 *, 0xC)], s32 *, 0x14) == 2) || (M2C_FIELD(sp148, s32 *, 0x30) < 0x1E)) {
                                    temp_s1 = func_80254E00(M2C_FIELD(var_fp, f32 **, 0x18), &sp12C);
                                    if ((temp_s1 != NULL) && (M2C_FIELD(temp_s1, s32 *, 0x44) == 0)) {
                                        func_8022F808(temp_s1, sp10C);
                                        temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), sp10C);
                                        M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                        M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x20) = temp_fv0;
                                        M2C_FIELD(var_fp, s32 *, 4) = (s32) M2C_FIELD(var_fp, s32 *, 8);
                                        M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                                    } else {
                                        goto block_768;
                                    }
                                } else {
                                    M2C_FIELD(var_fp, s32 *, 4) = 4;
                                    break;
                                }
                            } else if ((func_80251BDC((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C)) != -1) && (temp_fs3 < 150.0f)) {
                                temp_fv0 = (f32) ((s32) (temp_fs1_3 / 45.0f) * 0x2D);
                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                            } else {
                                M2C_FIELD(var_fp, s32 *, 4) = 3;
                                goto block_768;
                            }
                        } else {
block_768:
                            temp_s1 = func_80251D10(M2C_FIELD(var_fp, f32 **, 0x18), &sp12C);
                            if ((temp_s1 != NULL) && (temp_v0_6 = func_80251C88((s32) temp_s1), (temp_v0_6 != NULL)) && (sp12C < 400.0f)) {
                                sp10C[0] = M2C_FIELD(temp_v0_6, f32 *, 0x1C);
                                sp10C[1] = M2C_FIELD(temp_v0_6, f32 *, 0x20);
                                sp10C[2] = M2C_FIELD(temp_v0_6, f32 *, 0x24);
                                M2C_FIELD(var_fp, f32 *, 0x74) = func_80251994(sp10C, (f32 *) ((u8 *)var_fp + 0x20));
                                M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                                if (func_80252724(var_fp) != 0) {
                                    M2C_FIELD(var_fp, f32 *, 0x74) = (f32) ((f32) func_80252BF8((s32) (M2C_FIELD(var_fp, f32 *, 0x74) / 45.0f) ^ 4, (u8 *)var_fp + 0x38) * 45.0f);
                                }
                            } else {
                                var_s4 = 0;
                                if ((M2C_FIELD(sp148, s32 *, 0) == 1) && (func_80234248(0x3E8) < 0x1F4) && (temp_v0_6 = func_8022FA88(M2C_FIELD(var_fp, f32 **, 0x18), 4, &sp12C), (temp_v0_6 != NULL)) && (temp_v1 = (1 - M2C_FIELD(&sp148[M2C_FIELD(var_fp, s32 *, 0xC)], s32 *, 0x90)) * 4, (*(s32 *)(D_802AC760 + temp_v1) != 0)) && (temp_v0_6 == (u8 *) **(void ***)(D_802AC820 + temp_v1)) && (sp12C < 800.0f)) {
                                    if ((sp12C < 500.0f) && (M2C_FIELD(var_fp, s32 *, 4) != 5) && (M2C_FIELD(var_fp, u32 *, 0x94) == 0)) {
                                        func_8022F808(temp_v0_6, (f32 *) ((u8 *)var_fp + 0x2C));
                                        temp_fv0 = (f32) func_802519B4(func_80251994((f32 *) ((u8 *)var_fp + 0x20), (f32 *) ((u8 *)var_fp + 0x2C))) * 45.0f;
                                        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                        M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                        if (func_80234248(0x64) < 0x32) {
                                            func_80251E5C((f32 *) var_fp);
                                        } else {
                                            func_80252174((f32 *) var_fp);
                                        }
                                        M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                        M2C_FIELD(var_fp, s32 *, 4) = 5;
                                        M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                                    } else {
                                        func_8022F808(temp_v0_6, (f32 *) ((u8 *)var_fp + 0x2C));
                                        var_s4 = 1;
                                        goto block_788;
                                    }
                                } else {
block_788:
                                    if ((M2C_FIELD(var_fp, s32 *, 0) & 3) != 3) {
                                        M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                                    }
                                    if ((func_8022FA88(M2C_FIELD(var_fp, f32 **, 0x18), 1, &sp12C) != NULL) && (sp12C <= 70.0f) && (sp12C <= 70.0f) && (func_80252724(var_fp) != 0)) {
                                        M2C_FIELD(var_fp, f32 *, 0x74) = W360(M2C_FIELD(var_fp, f32 *, 0x74) + 180.0f);
                                        M2C_FIELD(var_fp, s32 *, 4) = 4;
                                        break;
                                    }
                                    switch (M2C_FIELD(var_fp, u32 *, 0x94)) { /* switch 3 */
                                    case 1:         /* switch 3 */
                                        temp_v1 = M2C_FIELD(var_fp, s32 *, 0x90) - 1;
                                        M2C_FIELD(var_fp, s32 *, 0x90) = temp_v1;
                                        if (temp_v1 == 0) {
                                            M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                                        }
                                        break;
                                    case 2:         /* switch 3 */
                                        temp_v1 = M2C_FIELD(sp148, s32 *, 0);
                                        if (temp_v1 == 0) {
                                            if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0x10), 0x1000) == 0) {
                                                temp_v1 = M2C_FIELD(sp148, s32 *, 0);
                                                goto block_809;
                                            }
                                            goto block_811;
                                        }
block_809:
                                        if ((temp_v1 == 1) && (var_s4 != 0)) {
block_811:
                                            if (temp_fs3 <= 300.0f) {
                                                M2C_FIELD(var_fp, s32 *, 0) |= 0x100;
                                                M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                                                M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                                                M2C_FIELD(var_fp, f32 *, 0x70) = (f32) M2C_FIELD(var_fp, f32 *, 0x34);
                                                M2C_FIELD(var_fp, f32 *, 0x68) = (f32) M2C_FIELD(var_fp, f32 *, 0x2C);
                                                M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                                M2C_FIELD(var_fp, s32 *, 4) = 0;
                                            } else {
                                                goto block_813;
                                            }
                                        } else {
block_813:
                                            M2C_FIELD(var_fp, u32 *, 0x94) = 0U;
                                            M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                                        }
                                        break;
                                    case 3:         /* switch 3 */
                                        temp_v1 = M2C_FIELD(sp148, s32 *, 0);
                                        if (temp_v1 == 0) {
                                            if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0x10), 0x1000) == 0) {
                                                temp_v1 = M2C_FIELD(sp148, s32 *, 0);
                                                goto block_818;
                                            }
                                            goto block_820;
                                        }
block_818:
                                        if ((temp_v1 == 1) && (var_s4 != 0)) {
block_820:
                                            if (temp_fs3 <= 400.0f) {
                                                if (temp_fs3 <= 100.0f) {
                                                    temp_fv0 = M2C_FIELD(var_fp, f32 *, 0x74);
                                                    M2C_FIELD(var_fp, f32 *, 0x74) = temp_fs1_3;
                                                    M2C_FIELD(var_fp, f32 *, 0x80) = temp_fv0;
                                                    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fs1_3;
                                                    func_80254EC4((f32 *) var_fp);
                                                    M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                                                    M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                                                    M2C_FIELD(var_fp, s32 *, 0x90) = 0x28;
                                                    M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(var_fp, f32 *, 0x80);
                                                }
                                                M2C_FIELD(var_fp, f32 *, 0x68) = (f32) M2C_FIELD(var_fp, f32 *, 0x2C);
                                                M2C_FIELD(var_fp, f32 *, 0x70) = (f32) M2C_FIELD(var_fp, f32 *, 0x34);
                                                break;
                                            } else {
                                                goto block_824;
                                            }
                                        } else {
block_824:
                                            M2C_FIELD(var_fp, u32 *, 0x94) = 0U;
                                            M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                                        }
                                        break;
                                    case 4:         /* switch 3 */
                                        temp_v1 = M2C_FIELD(var_fp, s32 *, 0x90) - 1;
                                        M2C_FIELD(var_fp, s32 *, 0x90) = temp_v1;
                                        if (temp_v1 == 0) {
                                            M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                                        }
                                        break;
                                    case 5:         /* switch 3 */
                                        temp_s1 = func_80252CB4(M2C_FIELD(var_fp, f32 **, 0x18), &sp12C);
                                        if ((func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x8000) != 0) && (temp_s1 != NULL) && (sp12C < 800.0f)) {
                                            M2C_FIELD(var_fp, s32 *, 0) |= 0x100;
                                            M2C_FIELD(var_fp, f32 *, 0x68) = (f32) M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x10);
                                            M2C_FIELD(var_fp, f32 *, 0x70) = (f32) M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x18);
                                            M2C_FIELD(var_fp, u32 *, 0x94) = (u32) (M2C_FIELD(var_fp, u32 *, 0x94) + 1);
                                            M2C_FIELD(var_fp, f32 *, 0x78) = (f32) M2C_FIELD(var_fp, f32 *, 0x74);
                                        } else {
                                            M2C_FIELD(var_fp, u32 *, 0x94) = 0U;
                                        }
                                        break;
                                    case 6:         /* switch 3 */
                                        if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x8000) != 0) {
                                            temp_s1 = func_80252CB4(M2C_FIELD(var_fp, f32 **, 0x18), &sp12C);
                                            if ((temp_s1 != NULL) && (sp12C < 400.0f)) {
                                                func_8022F808(temp_s1, sp10C);
                                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = func_80251994((f32 *) ((u8 *)var_fp + 0x20), sp10C);
                                                func_80254EC4((f32 *) var_fp);
                                                M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                                                M2C_FIELD(var_fp, u32 *, 0x94) = 0U;
                                            }
                                        } else {
                                            M2C_FIELD(var_fp, u32 *, 0x94) = 0U;
                                            M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                                        }
                                        break;
                                    }
                                    if (M2C_FIELD(var_fp, u32 *, 0x94) != 0) {
                                        if (M2C_FIELD(var_fp, s32 *, 0) & 0x100) {
                                            if (func_80252724(var_fp) != 0) {
                                                temp_fv0 = M2C_FIELD(var_fp, f32 *, 0x74);
                                                M2C_FIELD(var_fp, f32 *, 0x74) = temp_fs1_3;
                                                M2C_FIELD(var_fp, f32 *, 0x80) = temp_fv0;
                                                M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fs1_3;
                                                func_80254EC4((f32 *) var_fp);
                                                M2C_FIELD(var_fp, s32 *, 0) &= ~0x100;
                                                M2C_FIELD(var_fp, u32 *, 0x94) = 5U;
                                                M2C_FIELD(var_fp, s32 *, 0x90) = 0x28;
                                                M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(var_fp, f32 *, 0x80);
                                            }
                                        }
                                    } else {
                                        if ((M2C_FIELD(&sp148[M2C_FIELD(var_fp, s32 *, 0xC)], s32 *, 0x14) > 0) && (func_80234248(0x64) >= 0x33)) {
                                            temp_v1 = M2C_FIELD(sp148, s32 *, 0);
                                            if (temp_v1 == 0) {
                                                if (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0x10), 0x1000) == 0) {
                                                    temp_v1 = M2C_FIELD(sp148, s32 *, 0);
                                                    goto block_849;
                                                }
                                                goto block_851;
                                            }
block_849:
                                            if ((temp_v1 == 1) && (var_s4 != 0)) {
block_851:
                                                if (temp_fs3 <= 300.0f) {
                                                    M2C_FIELD(var_fp, u32 *, 0x94) = 1U;
                                                    M2C_FIELD(var_fp, s32 *, 0x90) = 0x14;
                                                } else {
                                                    goto block_853;
                                                }
                                            } else {
block_853:
                                                M2C_FIELD(var_fp, u32 *, 0x94) = 0U;
                                            }
                                        }
                                        if ((temp_fs3 < 120.0f) && (M2C_FIELD(var_fp, s32 *, 4) != 5)) {
                                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fs1_3;
                                            M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                                            func_80251E5C((f32 *) var_fp);
                                            M2C_FIELD(var_fp, s32 *, 8) = M2C_FIELD(var_fp, s32 *, 4);
                                            M2C_FIELD(var_fp, s32 *, 4) = 5;
                                        } else {
                                            if ((M2C_FIELD(var_fp, s32 *, 4) == 5) && (func_80252724(var_fp) != 0)) {
                                                M2C_FIELD(var_fp, s32 *, 4) = 4;
                                                break;
                                            }
                                            if ((M2C_FIELD(var_fp, s32 *, 4) == 0xF3) && (func_80252724(var_fp) != 0)) {
                                                M2C_FIELD(var_fp, s32 *, 0x10) = func_80251708(sp118);
                                                if (M2C_FIELD(var_fp, s32 *, 0x10) != -1) {
                                                    M2C_FIELD(var_fp, void **, 0x1C) = func_802443F4(M2C_FIELD(var_fp, s32 *, 0x10));
                                                }
                                            }
                                            if (M2C_FIELD(var_fp, s32 *, 8) == M2C_FIELD(var_fp, s32 *, 4)) {
                                                M2C_FIELD(var_fp, s32 *, 4) = 0xF3;
                                            }
                                            temp_s1 = func_80254E00(M2C_FIELD(var_fp, f32 **, 0x18), &sp12C);
                                            if (M2C_FIELD(var_fp, s32 *, 4) == 1) {
                                                if (func_80252724(var_fp) != 0) {
                                                    if (temp_s1 != NULL) {
                                                        if (sp12C < 110.0f) {
                                                            func_8022F808(temp_s1, sp10C);
                                                            temp_fv0 = func_80251994((f32 *) ((u8 *)var_fp + 0x20), sp10C);
                                                            M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                                            M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x20) = temp_fv0;
                                                            M2C_FIELD(var_fp, s32 *, 4) = (s32) M2C_FIELD(var_fp, s32 *, 8);
                                                            M2C_FIELD(var_fp, f32 *, 0x7C) = 60.0f;
                                                        } else {
                                                            goto block_873;
                                                        }
                                                    } else {
                                                        goto block_872;
                                                    }
                                                } else {
                                                    goto block_873;
                                                }
                                            } else {
block_872:
block_873:
                                                if (func_80254E20((f32 *) var_fp, 3, 1) == 0) {
                                                    if ((M2C_FIELD(var_fp, s32 *, 4) == 1) && (func_80254DC8(2, ((u8 *)var_fp + 0x20), 300.0f) >= 3)) {
                                                        var_s3 = 0xA;
                                                        var_s2 = 0;
                                                        var_s0 = D_802A1008;
                                                        do {
                                                            sp10C[1] = 0.0f;
                                                            sp10C[0] = M2C_FIELD(var_s0, f32 *, 0);
                                                            sp10C[2] = M2C_FIELD(var_s0, f32 *, 8);
                                                            temp_v0_2 = func_80254DC8(2, sp10C, 300.0f);
                                                            if (temp_v0_2 < var_s3) {
                                                                var_s3 = temp_v0_2;
                                                                sp150 = var_s2;
                                                            }
                                                            var_s2 += 1;
                                                            var_s0 += 0xC;
                                                        } while (var_s2 != 4);
                                                        M2C_FIELD(var_fp, f32 *, 0x74) = func_80251994((f32 *) ((u8 *)var_fp + 0x20), (sp150 * 0xC) + D_802A1008);
                                                    }
                                                    if ((M2C_FIELD(sp148, s32 *, 0) == 0) && (M2C_FIELD(sp148, s32 *, 0xA0) == 8)) {
                                                        temp_s1 = func_80231274(-1, 0, 0xD0, NULL);
                                                        M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x10) = 2400.0f;
                                                        M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x14) = 0.0f;
                                                        M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x40), f32 *, 0x18) = 1600.0f;
                                                        func_8027F858((s32) temp_s1, 5);
                                                        temp_a0_3 = M2C_FIELD(temp_s1, void **, 0x40);
                                                        if ((FDIFF(M2C_FIELD(temp_a0_3, f32 *, 0x10), 2400.0f) >= 6.0f) || (FDIFF(M2C_FIELD(temp_a0_3, f32 *, 0x18), 1600.0f) >= 6.0f)) {
                                                            if (M2C_FIELD(temp_a0_3, f32 *, 0x10) != 2400.0f) {
                                                                if (M2C_FIELD(temp_a0_3, f32 *, 0x10) > 2400.0f) {
                                                                    var_s3 = 6;
                                                                } else {
                                                                    var_s3 = 2;
                                                                }
                                                            } else {
                                                                var_s3 = 0;
                                                            }
                                                            if (M2C_FIELD(temp_a0_3, f32 *, 0x18) != 1600.0f) {
                                                                if (M2C_FIELD(temp_a0_3, f32 *, 0x18) > 1600.0f) {
                                                                    if (var_s3 == 0) {
                                                                        var_s3 = 4;
                                                                    } else {
                                                                        if (var_s3 == 2) {
                                                                            var_s3 += 1;
                                                                        } else {
                                                                            var_s3 -= 1;
                                                                        }
                                                                    }
                                                                } else if (var_s3 == 0) {
                                                                    var_s3 = 0;
                                                                } else if (var_s3 == 2) {
                                                                    var_s3 -= 1;
                                                                } else {
                                                                    var_s3 += 1;
                                                                }
                                                                }
                                                            temp_fv0 = var_s3 * 45;
                                                            M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20) = temp_fv0;
                                                            M2C_FIELD(var_fp, f32 *, 0x74) = temp_fv0;
                                                        }
                                                        func_8022FC90(temp_s1);
                                                        if ((M2C_FIELD(sp148, s32 *, 0x38) != 0) && (M2C_FIELD(sp148, s32 *, 0x2C) <= 0)) {
                                                            var_s0 = M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40);
                                                            temp_fv0 = M2C_FIELD(var_s0, f32 *, 0x10);
                                                            if (temp_fv0 > 2700.0f) {
                                                                M2C_FIELD(var_s0, f32 *, 0x20) = 270.0f;
                                                                M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                                                            } else if (temp_fv0 < 1900.0f) {
                                                                M2C_FIELD(var_s0, f32 *, 0x20) = 90.0f;
                                                                M2C_FIELD(var_fp, f32 *, 0x74) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(var_fp, f32 **, 0x18), void **, 0x40), f32 *, 0x20);
                                                            }
                                                        }
                                                    }
                                                    if ((M2C_FIELD(&sp148[M2C_FIELD(var_fp, s32 *, 0xC)], s32 *, 0x14) > 0) && (func_8025E63C() > 0.949999988079071) && (func_80244BA4(M2C_FIELD(var_fp, s32 *, 0xC), 0x8000) != 0) && (func_802703B4(D_800AEDF0[M2C_FIELD(var_fp, s32 *, 0xC)].unk2C) != 0)) {
                                                        func_80254C90((f32 *) var_fp);
                                                    }
                                                    if (M2C_FIELD(var_fp, s32 *, 4) == 0) {
                                                        M2C_FIELD(var_fp, s32 *, 4) = 4;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        func_802530A8((f32 *) var_fp);
    }
    func_80239094();
    }
    func_8024585C(M2C_FIELD(var_fp, s32 *, 0xC));
    func_802452E8(1);
    func_8024585C(0);
    M2C_FIELD(var_fp, s32 *, 0) &= ~3;
    M2C_FIELD(var_fp, f32 *, 0x7C) = 0.0f;
    M2C_FIELD(var_fp, s32 *, 0) |= 0;
    M2C_FIELD(var_fp, s32 *, 0x88) = -1;
    M2C_FIELD(M2C_FIELD(var_fp, void **, 0x9C), f32 *, 8) = 0.0f;
    M2C_FIELD(M2C_FIELD(var_fp, void **, 0x9C), f32 *, 0) = (f32) M2C_FIELD(var_fp, f32 *, 0x74);
    func_80239430();
    if (0) {  /* fake: emission order */
        func_80255350(0);
        func_802552B8(0);
        func_80255224(0, 0, 0);
        func_802551B4(0);
        func_80255174(0);
        func_80255110(0);
        func_80255098(0);
        func_80255064(0, 0, 0, 0, 0);
        func_80255040(0, 0);
        func_8025500C(0, 0);
        func_80254FA8(0);
        func_80254FA0();
        func_80254F20(0);
        func_80254EC4(0);
        func_80254E20(0, 0, 0);
        func_80254E00(0, 0);
        func_80254DC8(0, 0, 0);
        func_80254C90(0);
        func_802530A8(0);
        func_80252EA4(0);
        func_80252D14(0);
        func_80252CD4(0, 0);
        func_80252CB4(0, 0);
        func_80252BF8(0, 0);
        func_80252AF8(0, 0, 0);
        func_802529A4(0, 0, 0, 0);
        func_80252918(0, 0, 0);
        func_80252724(0);
        func_802526A0(0, 0);
        func_80252658(0, 0);
        func_80252598(0, 0);
        func_80252490(0);
        func_802523E0(0);
        func_80252380(0, 0);
        func_80252330(0, 0);
        func_80252174(0);
        func_8025216C();
        func_80252048(0);
        func_80251EE0(0);
        func_80251E5C(0);
        func_80251D30(0, 0, 0, 0);
        func_80251D10(0, 0);
        func_80251C88(0);
        func_80251C48(0, 0);
        func_80251BDC(0, 0);
        func_80251B08(0, 0, 0);
        func_80251AC8(0);
        func_80251A24(0, 0, 0);
        func_802519B4(0);
        func_80251994(0, 0);
        func_80251974(0, 0);
    }
}

static void func_80255350(f32 *arg0) {
    if (func_80251D30(arg0, 0, 1, 1) == 0) {
        *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x28) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x28), s16 *, 4) = 0x4000;
        *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), u16 *, 4) = 0x8000;
    }
}

static s32 func_802552B8(f32 *arg0) {
    if ((func_80243D2C(M2C_FIELD(arg0, s32 *, 0xC)) <= 0) || ((func_80245408(M2C_FIELD(arg0, s32 *, 0xC)) & ~0x200) != 0)) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x70) = 1.6333334f;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x6C) = 16.333334f;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x68) = 0.0f;
        M2C_FIELD(arg0, s32 *, 0x88) = 0;
        M2C_FIELD(arg0, s32 *, 0) &= ~3;
        M2C_FIELD(arg0, s32 *, 0) |= 1;
        return 1;
    }
    return 0;
}

static void func_802551B4(f32 *arg0) {
    u8 *temp_s1;

    temp_s1 = func_8023A840();
    if (!(M2C_FIELD(arg0, s32 *, 0x124) & 8) && (func_80244BA4(M2C_FIELD(arg0, s32 *, 0xC), 0x1000) != 0)) {
        func_80233C80((u8 *)arg0 + 0x20);
        M2C_FIELD(arg0, s32 *, 0x124) = (s32) (M2C_FIELD(arg0, s32 *, 0x124) | 8);
        M2C_FIELD(temp_s1, s32 *, 0x2C) = (s32) (M2C_FIELD(temp_s1, s32 *, 0x2C) + 1);
    }
}

static void func_80255174(f32 *arg0) {
    func_80250338(M2C_FIELD(arg0, s32 *, 0x10), (u8 *)arg0 + 0x2C);
    func_8026DCAC(M2C_FIELD(arg0, f32 *, 0x2C), M2C_FIELD(arg0, f32 *, 0x30), M2C_FIELD(arg0, f32 *, 0x34), (u8 *)arg0 + 0x50, 2);
}

static void func_80255110(f32 *arg0) {
    u8 *temp_v0;
    u8 *temp_v0_2;

    if (M2C_FIELD(func_8023A840(), s32 *, 0x10) == 0) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x18);
        M2C_FIELD(temp_v0, s32 *, 8) = (s32) (M2C_FIELD(temp_v0, s32 *, 8) | 0x1000);
        return;
    }
    temp_v0_2 = M2C_FIELD(arg0, void **, 0x18);
    M2C_FIELD(temp_v0_2, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 8) | 0x800);
}

static s32 func_80255098(f32 *arg0) {
    if ((func_80243D2C(M2C_FIELD(arg0, s32 *, 0xC)) <= 0) || ((func_80245408(M2C_FIELD(arg0, s32 *, 0xC)) & ~0x200) != 0)) {
        if ((M2C_FIELD(arg0, s32 *, 0) & 3) != 3) {
            M2C_FIELD(arg0, s32 *, 0) &= ~3;
            M2C_FIELD(arg0, s32 *, 0) |= 1;
            M2C_FIELD(arg0, s32 *, 0x88) = 0;
        }
        return 1;
    }
    return 0;
}

static void func_80255064(u8 *arg0, u8 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    M2C_FIELD(arg0, f32 *, 0x10) = M2C_FIELD(arg1, f32 *, 0x10) + arg2;
    M2C_FIELD(arg0, f32 *, 0x14) = M2C_FIELD(arg1, f32 *, 0x14) + arg3;
    M2C_FIELD(arg0, f32 *, 0x18) = M2C_FIELD(arg1, f32 *, 0x18) + arg4;
}

static void func_80255040(u8 *arg0, u8 *arg1) {
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) M2C_FIELD(arg1, f32 *, 0x10);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) M2C_FIELD(arg1, f32 *, 0x14);
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) M2C_FIELD(arg1, f32 *, 0x18);
}

static s32 func_8025500C(s32 arg0, u8 *arg1) {
    u8 *m = M2C_FIELD(arg1, u8 **, 0x40);

    return func_8026C51C(arg0, M2C_FIELD(m, f32 *, 0x10), M2C_FIELD(m, f32 *, 0x14), M2C_FIELD(m, f32 *, 0x18));
}

static void func_80254FA8(f32 *arg0) {
    u8 *temp_v0;
    u8 *temp_v0_2;

    if (M2C_FIELD(func_8023A840(), s32 *, 0x10) == 0) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x18);
        M2C_FIELD(temp_v0, s32 *, 8) = (s32) (M2C_FIELD(temp_v0, s32 *, 8) & ~0x1000);
        return;
    }
    temp_v0_2 = M2C_FIELD(arg0, void **, 0x18);
    M2C_FIELD(temp_v0_2, s32 *, 8) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 8) & ~0x800);
}

static void func_80254F20(f32 *arg0) {
    s32 var_s0;
    u8 *temp_v0;

    var_s0 = (M2C_FIELD(func_8023A840(), s32 *, 0x10) == 0) ? 0x1000 : 0x800;
    if (func_80244BA4(M2C_FIELD(arg0, s32 *, 0xC), 0x1000) != 0) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x18);
        M2C_FIELD(temp_v0, s32 *, 8) = (s32) (M2C_FIELD(temp_v0, s32 *, 8) & ~var_s0);
    } else {
        temp_v0 = M2C_FIELD(arg0, void **, 0x18);
        M2C_FIELD(temp_v0, s32 *, 8) = (s32) (M2C_FIELD(temp_v0, s32 *, 8) | var_s0);
    }
}

static void func_80254EC4(f32 *arg0) {
    if (func_80251D30(arg0, 0, 0, 1) == 0) {
        *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s16 *, 4) = 0x4000;
    }
}

static s32 func_80254E20(f32 *arg0, s32 arg2, s32 arg1) {
    s32 pad[2];
    f32 sp24;
    s32 n;
    u8 *temp_v0;

    if (arg1 != M2C_FIELD(arg0, s32 *, 4)) {
        if (func_80244BA4(M2C_FIELD(arg0, s32 *, 0xC), 0x8000) == 0) {
            temp_v0 = func_8022FA88(M2C_FIELD(arg0, void **, 0x18), 2, &sp24);
            if (temp_v0 != NULL) {
                n = ((s16) M2C_FIELD(func_802703B4((s32) temp_v0), s16 *, 0x66) >> 1) + arg2;
                if (sp24 <= n * 100.0f) {
                    M2C_FIELD(arg0, s32 *, 8) = M2C_FIELD(arg0, s32 *, 4);
                    M2C_FIELD(arg0, s32 *, 4) = arg1;
                    return 1;
                }
            }
        }
    }
    return 0;
}

static void *func_80254E00(f32 *arg0, f32 *arg1) {
    return func_8022FA88(arg0, 2, arg1);
}

static s32 func_80254DC8(s32 arg0, void *arg1, f32 arg2) {
    f32 size[3];
    u8 buf[0x28];

    size[2] = arg2;
    size[1] = arg2;
    size[0] = arg2;
    return func_8022F698((void *) arg0, (s32) arg1, size, buf, 10);
}

static void func_80254C90(f32 *arg0) {
    s32 i;

    if (func_80251D30(arg0, 0, 0, 0x11) == 0) {
        for (i = 0; i < 16; i++) {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), Unk6BBE0_8 **, 0x2C)[i].unk0 = 1;
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), Unk6BBE0_8 **, 0x2C)[i].unk4 = 0x8000;
        }
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), Unk6BBE0_8 **, 0x2C)[i].unk0 = 1;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), Unk6BBE0_8 **, 0x2C)[i].unk4 = 0x4000;
    }
}

static void func_802530A8(f32 *arg0) {
    s32 i;
    s32 dir;
    s32 v;
    s32 range;
    s32 tile;
    s32 side;
    f32 dist;
    f32 angle;
    f32 limit;
    f32 dx;
    f32 pos[3];
    f32 dz;
    void *target;
    void *entry;
    s32 grid[3];
    s32 dirX;
    s32 dirZ;
    s32 tile2;
    f32 wrap;

    switch (M2C_FIELD(arg0, s32 *, 0) & 3) {
    case 3:
        if (func_80252EA4(arg0) != 0) {
            func_80251424(arg0);
            M2C_FIELD(arg0, s32 *, 0) = ((M2C_FIELD(arg0, s32 *, 0) | 1));
        }
        return;
    case 0:
        if (M2C_FIELD(arg0, s32 *, 0x88) != -1) {
            if (--M2C_FIELD(arg0, s32 *, 0x88) == 0) {
                M2C_FIELD(arg0, s32 *, 0) &= ~3;
                M2C_FIELD(arg0, s32 *, 0) |= 1;
            }
        }
        break;
    default:
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x9C), s16 *, 0xC) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x9C), s16 *, 0xE) = 0;
        if (func_80244BA4(M2C_FIELD(arg0, s32 *, 0xC), 0x1000) != 0) {
            if (M2C_FIELD(arg0, s32 *, 0x98) != 0) {
                func_80251424(arg0);
            }
            func_80252D14(arg0);
            break;
        }
        tile = func_80252330((s32 *) ((u8 *)arg0 + 0x38), M2C_FIELD(arg0, f32 *, 0x74));
        tile2 = func_80252330((s32 *) ((u8 *)arg0 + 0x38), M2C_FIELD(arg0, f32 *, 0x80));
        if (M2C_FIELD(arg0, s32 *, 0) & 0x100) {
            dist = M2C_FIELD(arg0, f32 *, 0x74);
            i = func_80252658((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x68));
            if (M2C_FIELD(arg0, f32 *, 0x20) < M2C_FIELD(arg0, f32 *, 0x68)) {
                wrap = -(M2C_FIELD(arg0, f32 *, 0x20) - M2C_FIELD(arg0, f32 *, 0x68));
            } else {
                wrap = M2C_FIELD(arg0, f32 *, 0x20) - M2C_FIELD(arg0, f32 *, 0x68);
            }
            if (wrap > 50.0f) {
                if ((i & 1) && func_80252CD4((u8 *) arg0, 90.0f)) {
                    M2C_FIELD(arg0, f32 *, 0x74) = 90.0f;
                } else if (!(i & 1) && func_80252CD4((u8 *) arg0, 270.0f)) {
                    M2C_FIELD(arg0, f32 *, 0x74) = 270.0f;
                } else if (i & 2) {
                    if (func_80252CD4((u8 *) arg0, 0.0f)) {
                        M2C_FIELD(arg0, f32 *, 0x74) = 0.0f;
                    } else {
                        M2C_FIELD(arg0, f32 *, 0x74) = 180.0f;
                    }
                } else {
                    if (func_80252CD4((u8 *) arg0, 180.0f)) {
                        M2C_FIELD(arg0, f32 *, 0x74) = 180.0f;
                    } else {
                        M2C_FIELD(arg0, f32 *, 0x74) = 0.0f;
                    }
                }
            } else if ((i & 2) && func_80252CD4((u8 *) arg0, 0.0f)) {
                M2C_FIELD(arg0, f32 *, 0x74) = 0.0f;
            } else if (!(i & 2) && func_80252CD4((u8 *) arg0, 180.0f)) {
                M2C_FIELD(arg0, f32 *, 0x74) = 180.0f;
            } else if (i & 1) {
                if (func_80252CD4((u8 *) arg0, 90.0f)) {
                    M2C_FIELD(arg0, f32 *, 0x74) = 90.0f;
                } else {
                    M2C_FIELD(arg0, f32 *, 0x74) = 270.0f;
                }
            } else {
                if (func_80252CD4((u8 *) arg0, 270.0f)) {
                    M2C_FIELD(arg0, f32 *, 0x74) = 270.0f;
                } else {
                    M2C_FIELD(arg0, f32 *, 0x74) = 90.0f;
                }
            }
        }
        switch (M2C_FIELD(arg0, s32 *, 4) & 0xF) {
        case 3:
            if (func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) {
                if (D_802ACFB0 < func_80251C48((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C))) {
                    if (M2C_FIELD(arg0, s32 *, 0) & 0x40) {
                        if (func_80251AC8(tile2) == 0) {
                            M2C_FIELD(arg0, s32 *, 0) = ((M2C_FIELD(arg0, s32 *, 0) & ~0x40));
                            M2C_FIELD(arg0, f32 *, 0x74) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
                        } else if (func_8025156C(M2C_FIELD(arg0, f32 **, 0x18)) == 0) {
                            angle = M2C_FIELD(arg0, f32 *, 0x80) + 90.0f;
                            if (angle >= 360.0f) {
                                M2C_FIELD(arg0, f32 *, 0x80) = (f32) (angle - 360.0f);
                            } else {
                                if (angle < 0.0f) {
                                    wrap = angle + 360.0f;
                                } else {
                                    wrap = angle;
                                }
                                M2C_FIELD(arg0, f32 *, 0x80) = wrap;
                            }
                            angle = M2C_FIELD(arg0, f32 *, 0x74) + 90.0f;
                            if (angle >= 360.0f) {
                                M2C_FIELD(arg0, f32 *, 0x74) = (f32) (angle - 360.0f);
                            } else {
                                if (angle < 0.0f) {
                                    wrap = angle + 360.0f;
                                } else {
                                    wrap = angle;
                                }
                                M2C_FIELD(arg0, f32 *, 0x74) = wrap;
                            }
                        }
                    } else {
                        if (func_8025156C(M2C_FIELD(arg0, f32 **, 0x18)) == 0) {
                            M2C_FIELD(arg0, s32 *, 0) = ((M2C_FIELD(arg0, s32 *, 0) | 0x40));
                            M2C_FIELD(arg0, f32 *, 0x80) = (f32) M2C_FIELD(arg0, f32 *, 0x74);
                            angle = func_802526A0(arg0, (f32 *) ((u8 *)arg0 + 0x2C));
                        } else {
                            angle = func_80252598((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C));
                        }
                        M2C_FIELD(arg0, f32 *, 0x74) = angle;
                    }
                    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) D_802ACFB4;
                } else {
                    M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                }
            } else if (func_8025156C(M2C_FIELD(arg0, f32 **, 0x18)) == 0) {
                if (func_80251A24(0x3FFFF, (f32 *) ((u8 *)arg0 + 0x20), M2C_FIELD(arg0, f32 *, 0x74)) != 0) {
                    angle = M2C_FIELD(arg0, f32 *, 0x74) + 180.0f;
                    if (angle >= 360.0f) {
                        M2C_FIELD(arg0, f32 *, 0x74) = angle - 360.0f;
                    } else {
                        if (angle < 0.0f) {
                            wrap = angle + 360.0f;
                        } else {
                            wrap = angle;
                        }
                        M2C_FIELD(arg0, f32 *, 0x74) = wrap;
                    }
                } else {
                    angle = M2C_FIELD(arg0, f32 *, 0x74) + 90.0f;
                    if (angle >= 360.0f) {
                        M2C_FIELD(arg0, f32 *, 0x74) = angle - 360.0f;
                    } else {
                        if (angle < 0.0f) {
                            wrap = angle + 360.0f;
                        } else {
                            wrap = angle;
                        }
                        M2C_FIELD(arg0, f32 *, 0x74) = wrap;
                    }
                }
                M2C_FIELD(arg0, f32 *, 0x7C) = (f32) D_802ACFB4;
            }
            break;
        case 5:
            if (func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) {
                M2C_FIELD(arg0, f32 *, 0x7C) = (f32) D_802ACFB8;
                target = func_80252CB4(M2C_FIELD(arg0, f32 **, 0x18), &dist);
                if (target != NULL) {
                entry = func_802703B4((s32) target);
                if (entry == NULL) {
                    range = 3;
                } else {
                    range = ((s16) M2C_FIELD(entry, s16 *, 0x66) >> 1) + 1;
                }
                limit = (f32) range * 110.0f;
                if (dist <= limit) {
                    wrap = dist * 0.01f;
                    if (wrap >= 0) {
                        wrap = wrap + 0.5f;
                    } else {
                        wrap = wrap - 0.5f;
                    }
                    range = (range - (s32) wrap) + 1;
                    dir = func_802519B4(M2C_FIELD(arg0, f32 *, 0x74));
                    if (func_80252AF8(dir, (s32 *) ((u8 *)arg0 + 0x38), range) != 0) {
                        dir = func_80252BF8(dir ^ 4, (s32 *) ((u8 *)arg0 + 0x38));
                        entry = func_80251B08(2, (s32 *) ((u8 *)arg0 + 0x38), dir);
                        if (entry != NULL) {
                            if (M2C_FIELD(entry, s32 *, 8) & 2) {
                                dir = func_802519B4(M2C_FIELD(arg0, f32 *, 0x74)) ^ 4;
                            }
                        } else if (func_80252AF8(dir, (s32 *) ((u8 *)arg0 + 0x38), range) != 0) {
                            dir = func_802519B4(M2C_FIELD(arg0, f32 *, 0x74)) ^ 4;
                        }
                    } else {
                        for (i = 0; i < 4; i++) {
                            if (func_80252918((s32 *) ((u8 *)arg0 + 0x38), dir, 1) != 0 && func_80252AF8(dir, (s32 *) ((u8 *)arg0 + 0x38), range >> 1) == 0) {
                                break;
                            }
                            dir += 2;
                            dir &= 7;
                        }
                        if (i >= 4) {
                            M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                            break;
                        }
                        if (func_80251B08(0x3FFFF, (s32 *) ((u8 *)arg0 + 0x38), dir) != NULL) {
                            dir ^= 4;
                        }
                    }
                    M2C_FIELD(arg0, f32 *, 0x74) = dir * 45;
                } else {
                    if ((dist - limit) >= 200.0f) {
                        M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                        M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 8);
                    } else {
                        M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                    }
                    break;
                }
                } else {
                    M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 8);
                }
            } else {
                dir = func_802519B4(M2C_FIELD(arg0, f32 *, 0x74));
                entry = func_80251B08(2, (s32 *) ((u8 *)arg0 + 0x38), dir);
                if ((entry != NULL) && (M2C_FIELD(entry, s32 *, 8) & 2)) {
                    M2C_FIELD(arg0, f32 *, 0x74) = (func_802519B4(M2C_FIELD(arg0, f32 *, 0x74)) ^ 4) * 45;
                }
            }
            break;
        case 1:
            if (func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) {
                M2C_FIELD(arg0, f32 *, 0x7C) = (f32) D_802ACFB8;
                target = func_80252CB4(M2C_FIELD(arg0, f32 **, 0x18), &dist);
                if (target != NULL) {
                entry = func_802703B4((s32) target);
                if (entry == NULL) {
                    range = 3;
                } else {
                    range = ((s16) M2C_FIELD(entry, s16 *, 0x66) >> 1) + 1;
                }
                if (dist <= (f32) range * 110.0f) {
                    limit = (f32) range * 110.0f;
                    wrap = dist * 0.01f;
                    if (wrap >= 0) {
                        wrap = wrap + 0.5f;
                    } else {
                        wrap = wrap - 0.5f;
                    }
                    range = (range - (s32) wrap) + 1;
                    dir = func_802519B4(M2C_FIELD(arg0, f32 *, 0x74));
                    if (func_80252AF8(dir, (s32 *) ((u8 *)arg0 + 0x38), range) != 0) {
                        dir = func_80252BF8(dir ^ 4, (s32 *) ((u8 *)arg0 + 0x38));
                        if (func_80251B08(0x3FFFF, (s32 *) ((u8 *)arg0 + 0x38), dir) != NULL) {
                            if (func_802529A4(M2C_FIELD(arg0, u8 **, 0x18), 0x42, dir, limit) != 0) {
                                dir = func_802519B4(M2C_FIELD(arg0, f32 *, 0x74)) ^ 4;
                            }
                        } else if (func_80252AF8(dir, (s32 *) ((u8 *)arg0 + 0x38), range) != 0) {
                            dir = func_802519B4(M2C_FIELD(arg0, f32 *, 0x74)) ^ 4;
                        }
                    } else {
                        for (i = 0; i < 4; i++) {
                            if (func_80252918((s32 *) ((u8 *)arg0 + 0x38), dir, 1) != 0 && func_80252AF8(dir, (s32 *) ((u8 *)arg0 + 0x38), range >> 1) == 0) {
                                break;
                            }
                            dir += 1;
                            dir &= 7;
                        }
                        if (i >= 4) {
                            M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                            break;
                        }
                        if ((func_80251B08(0x3FFFF, (s32 *) ((u8 *)arg0 + 0x38), dir) != NULL) || (func_802529A4(M2C_FIELD(arg0, u8 **, 0x18), 0x42, dir, limit) != 0)) {
                            dir = (dir + 1) & 7;
                        }
                    }
                    M2C_FIELD(arg0, f32 *, 0x74) = dir * 45;
                } else {
                    if ((dist - (f32) range * 110.0f) >= 200.0f) {
                        M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 8);
                    } else {
                        M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 8);
                    }
                    break;
                }
                } else {
                    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 8);
                }
            } else if (func_8025156C(M2C_FIELD(arg0, f32 **, 0x18)) == 0) {
                angle = M2C_FIELD(arg0, f32 *, 0x74) + 45.0f;
                if (angle >= 360.0f) {
                    M2C_FIELD(arg0, f32 *, 0x74) = angle - 360.0f;
                } else {
                    if (angle < 0.0f) {
                        wrap = angle + 360.0f;
                    } else {
                        wrap = angle;
                    }
                    M2C_FIELD(arg0, f32 *, 0x74) = wrap;
                }
            } else {
                dir = func_802519B4(M2C_FIELD(arg0, f32 *, 0x74));
                if (func_80251B08(0x3FFFF, (s32 *) ((u8 *)arg0 + 0x38), dir) != NULL) {
                    if (func_802529A4(M2C_FIELD(arg0, u8 **, 0x18), 0x42, dir, 110.0f) != 0) {
                        M2C_FIELD(arg0, f32 *, 0x74) = func_802519B4(M2C_FIELD(arg0, f32 *, 0x74) + 45.0f) * 45;
                    }
                }
            }
            break;
        case 4:
            if ((func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) || ((func_80252724(arg0) != 0))) {
                if (func_80234248(0xC8) < 0x32) {
                    i = func_80234248(8) & 6;
                    if ((func_80252918((s32 *) ((u8 *)arg0 + 0x38), i, 1) != 0) && ((func_80251B08(0x3FFFF, (s32 *) ((u8 *)arg0 + 0x38), i) == NULL))) {
                        M2C_FIELD(arg0, f32 *, 0x74) = (f32) ((f32) i * 45.0f);
                        M2C_FIELD(arg0, f32 *, 0x7C) = (f32) D_802ACFB4;
                    } else {
                        M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                    }
                }
                for (dir = 0; dir < 4; dir++) {
                    if (func_80251AC8(func_80252330((s32 *) ((u8 *)arg0 + 0x38), M2C_FIELD(arg0, f32 *, 0x74))) == 0) {
                        break;
                    }
                    angle = M2C_FIELD(arg0, f32 *, 0x74) + 90.0f;
                    if (angle >= 360.0f) {
                        M2C_FIELD(arg0, f32 *, 0x74) = (f32) (angle - 360.0f);
                    } else {
                        if (angle < 0.0f) {
                            wrap = angle + 360.0f;
                        } else {
                            wrap = angle;
                        }
                        M2C_FIELD(arg0, f32 *, 0x74) = wrap;
                    }
                }
            }
            if (func_8025156C(M2C_FIELD(arg0, f32 **, 0x18)) == 0) {
                M2C_FIELD(arg0, f32 *, 0x7C) = (f32) D_802ACFB4;
                M2C_FIELD(arg0, f32 *, 0x74) = func_802523E0(arg0);
            }
            break;
        case 6:
            if (func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) {
                target = func_80251974(M2C_FIELD(arg0, f32 **, 0x18), &dist);
                if ((target != NULL) && (M2C_FIELD(M2C_FIELD(target, void **, 0x40), f32 *, 0x14) <= M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, f32 **, 0x18), void **, 0x40), f32 *, 0x14))) {
                entry = func_8027A1A0(target);
                if ((dist <= 500.0f) && (M2C_FIELD(entry, s16 *, 0x20) != 5)) {
                    pos[0] = M2C_FIELD(M2C_FIELD(target, void **, 0x40), f32 *, 0x10);
                    pos[1] = M2C_FIELD(M2C_FIELD(target, void **, 0x40), f32 *, 0x14);
                    pos[2] = M2C_FIELD(M2C_FIELD(target, void **, 0x40), f32 *, 0x18);
                    side = func_80252658((f32 *) ((u8 *)arg0 + 0x20), pos);
                    angle = M2C_FIELD(arg0, f32 *, 0x20);
                    if (pos[0] < angle) {
                        dx = -(pos[0] - angle);
                    } else {
                        dx = pos[0] - angle;
                    }
                    angle = M2C_FIELD(arg0, f32 *, 0x28);
                    if (pos[2] < angle) {
                        dz = -(pos[2] - angle);
                    } else {
                        dz = pos[2] - angle;
                    }
                    grid[0] = M2C_FIELD(arg0, s32 *, 0x38);
                    grid[1] = M2C_FIELD(arg0, s32 *, 0x3C);
                    grid[2] = M2C_FIELD(arg0, s32 *, 0x40);
                    dir = (side & 1) ? 2 : 6;
                    dirZ = (side & 2) ? 0 : 4;
                    if (dx < dz) {
                        if (func_80252918(grid, dirZ, (s32) (dz * 0.01f)) != 0) {
                            grid[2] += ((s32 (*)[2]) D_802A0EF0)[dirZ][1];
                            if (func_80252918(grid, dir, (s32) (dx * 0.01f)) != 0) {
                                if (dz != 0) {
                                    M2C_FIELD(arg0, f32 *, 0x74) = dirZ * 45;
                                } else {
                                    M2C_FIELD(arg0, f32 *, 0x74) = dir * 45;
                                }
                                break;
                            }
                            grid[2] -= ((s32 (*)[2]) D_802A0EF0)[dirZ][1];
                        }
                        if (func_80252918(grid, dir, (s32) (dx * 0.01f)) != 0) {
                            grid[0] += ((s32 (*)[2]) D_802A0EF0)[dir][0];
                            if (func_80252918(grid, dirZ, (s32) (dz * 0.01f)) != 0) {
                                if (dx != 0) {
                                    M2C_FIELD(arg0, f32 *, 0x74) = dir * 45;
                                } else {
                                    M2C_FIELD(arg0, f32 *, 0x74) = dirZ * 45;
                                }
                                break;
                            }
                            grid[0] -= ((s32 (*)[2]) D_802A0EF0)[dir][0];
                        }
                    } else {
                        if (func_80252918(grid, dir, (s32) (dx * 0.01f)) != 0) {
                            grid[0] += ((s32 (*)[2]) D_802A0EF0)[dir][0];
                            if (func_80252918(grid, dirZ, (s32) (dz * 0.01f)) != 0) {
                                if (dx != 0) {
                                    M2C_FIELD(arg0, f32 *, 0x74) = dir * 45;
                                } else {
                                    M2C_FIELD(arg0, f32 *, 0x74) = dirZ * 45;
                                }
                                break;
                            }
                            grid[0] -= ((s32 (*)[2]) D_802A0EF0)[dir][0];
                        }
                        if (func_80252918(grid, dirZ, (s32) (dz * 0.01f)) != 0) {
                            grid[2] += ((s32 (*)[2]) D_802A0EF0)[dirZ][1];
                            if (func_80252918(grid, dir, (s32) (dx * 0.01f)) != 0) {
                                if (dz != 0) {
                                    M2C_FIELD(arg0, f32 *, 0x74) = dirZ * 45;
                                } else {
                                    M2C_FIELD(arg0, f32 *, 0x74) = dir * 45;
                                }
                                break;
                            }
                            grid[2] -= ((s32 (*)[2]) D_802A0EF0)[dirZ][1];
                        }
                    }
                }
                }
                M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 8);
            } else if (func_80252724(arg0) != 0) {
                angle = func_80252490(arg0);
                M2C_FIELD(arg0, s32 *, 0) &= ~3;
                M2C_FIELD(arg0, f32 *, 0x74) = angle;
                M2C_FIELD(arg0, s32 *, 0x88) = 0x14;
                M2C_FIELD(arg0, s32 *, 0) |= 0;
                M2C_FIELD(arg0, f32 *, 0x7C) = 60.0f;
            }
            break;
        case 8:
            if (func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) {
                dist = func_80251C48((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C));
                if (D_802ACFB0 < dist) {
                    if (M2C_FIELD(arg0, s32 *, 0) & 0x40) {
                        if (func_80251AC8(tile2) == 0) {
                            M2C_FIELD(arg0, s32 *, 0) = ((M2C_FIELD(arg0, s32 *, 0) & ~0x40));
                            M2C_FIELD(arg0, f32 *, 0x74) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
                            M2C_FIELD(arg0, f32 *, 0x74) = func_802523E0(arg0);
                        } else if (func_8025156C(M2C_FIELD(arg0, f32 **, 0x18)) == 0) {
                            angle = M2C_FIELD(arg0, f32 *, 0x80) + 90.0f;
                            if (angle >= 360.0f) {
                                M2C_FIELD(arg0, f32 *, 0x80) = (f32) (angle - 360.0f);
                            } else {
                                if (angle < 0.0f) {
                                    wrap = angle + 360.0f;
                                } else {
                                    wrap = angle;
                                }
                                M2C_FIELD(arg0, f32 *, 0x80) = wrap;
                            }
                            angle = M2C_FIELD(arg0, f32 *, 0x74) + 90.0f;
                            if (angle >= 360.0f) {
                                M2C_FIELD(arg0, f32 *, 0x74) = (f32) (angle - 360.0f);
                            } else {
                                if (angle < 0.0f) {
                                    wrap = angle + 360.0f;
                                } else {
                                    wrap = angle;
                                }
                                M2C_FIELD(arg0, f32 *, 0x74) = wrap;
                            }
                            M2C_FIELD(arg0, f32 *, 0x74) = func_802523E0(arg0);
                        }
                    } else {
                        if (func_8025156C(M2C_FIELD(arg0, f32 **, 0x18)) == 0) {
                            M2C_FIELD(arg0, s32 *, 0) = ((M2C_FIELD(arg0, s32 *, 0) | 0x40));
                            M2C_FIELD(arg0, f32 *, 0x80) = (f32) M2C_FIELD(arg0, f32 *, 0x74);
                            M2C_FIELD(arg0, f32 *, 0x74) = func_802526A0(arg0, (f32 *) ((u8 *)arg0 + 0x2C));
                            M2C_FIELD(arg0, f32 *, 0x74) = func_802523E0(arg0);
                        } else {
                            M2C_FIELD(arg0, f32 *, 0x74) = func_80252598((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C));
                            M2C_FIELD(arg0, f32 *, 0x74) = func_802523E0(arg0);
                        }
                    }
                    M2C_FIELD(arg0, f32 *, 0x7C) = D_802ACFB4;
                } else if (dist <= (D_802ACFB0 - 100.0f)) {
                    M2C_FIELD(arg0, f32 *, 0x74) = func_80252598((f32 *) ((u8 *)arg0 + 0x2C), (f32 *) ((u8 *)arg0 + 0x20));
                    M2C_FIELD(arg0, f32 *, 0x74) = func_802523E0(arg0);
                    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) D_802ACFB4;
                } else {
                    M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                }
            } else if (func_8025156C(M2C_FIELD(arg0, f32 **, 0x18)) == 0) {
                dist = func_80251994((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C));
                M2C_FIELD(arg0, f32 *, 0x74) = func_80252490(arg0);
                M2C_FIELD(arg0, f32 *, 0x74) = func_802523E0(arg0);
                M2C_FIELD(arg0, f32 *, 0x7C) = D_802ACFB4;
            }
            break;
        }
        switch (M2C_FIELD(arg0, s32 *, 4) & 0xF0) {
        case 0x20:
            if (func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) {
                if (func_80251C48((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C)) <= 300.0f) {
                    func_80251E5C(arg0);
                }
            }
            break;
        case 0x40:
            if (func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) {
                func_80252174(arg0);
                M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 8);
            }
            break;
        case 0x80:
            if (func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) {
                func_80252048(arg0);
                M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 8);
            }
            break;
        case 0xF0:
            if (func_80251EE0((f32 *) ((u8 *)arg0 + 0x20)) != 0) {
                if ((M2C_FIELD(arg0, u32 *, 4) & 0xF) != 5) {
                    v = func_80251A24(1, (f32 *) ((u8 *)arg0 + 0x20), M2C_FIELD(arg0, f32 *, 0x74));
                    if ((tile & 0x60) || (v != 0)) {
                        func_80251E5C(arg0);
                        M2C_FIELD(arg0, s32 *, 8) = M2C_FIELD(arg0, s32 *, 4);
                        M2C_FIELD(arg0, s32 *, 4) = 5;
                        M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                    } else {
                        target = func_80251D10(M2C_FIELD(arg0, f32 **, 0x18), &dist);
                        if ((target != NULL) && (entry = func_80251C88((s32) target), angle = (entry != NULL) ? (f32) M2C_FIELD(entry, s16 *, 0x36) : 2.0f, (dist < (angle * 100.0f)))) {
                            M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
                        } else {
                            dist = func_80251C48((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C));
                            if ((dist >= 400.0f) && (dist <= 500.0f)) {
                                M2C_FIELD(arg0, s32 *, 8) = M2C_FIELD(arg0, s32 *, 4);
                                M2C_FIELD(arg0, s32 *, 4) = 0x40;
                                break;
                            }
                            if ((func_80251BDC((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C)) != -1) && (M2C_FIELD(arg0, f32 *, 0x30) <= M2C_FIELD(arg0, f32 *, 0x24)) && (limit = func_80251994((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C)), dir = func_802519B4(limit), func_80251B08(1, (s32 *) ((u8 *)arg0 + 0x38), dir) != NULL)) {
                                M2C_FIELD(arg0, f32 *, 0x74) = func_80251994((f32 *) ((u8 *)arg0 + 0x20), (f32 *) ((u8 *)arg0 + 0x2C));
                                M2C_FIELD(arg0, s32 *, 8) = M2C_FIELD(arg0, s32 *, 4);
                                M2C_FIELD(arg0, s32 *, 4) = 0x80;
                            } else {
                                goto block_296;
                            }
                        }
                    }
                } else {
block_296:
                    if ((M2C_FIELD(arg0, s32 *, 4) & 0xF) != 6) {
                        target = func_80251974(M2C_FIELD(arg0, f32 **, 0x18), &dist);
                        if ((target != NULL) && (M2C_FIELD(M2C_FIELD(target, void **, 0x40), f32 *, 0x14) <= M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, f32 **, 0x18), void **, 0x40), f32 *, 0x14)) && (dist <= 500.0f)) {
                            M2C_FIELD(arg0, s32 *, 8) = M2C_FIELD(arg0, s32 *, 4);
                            M2C_FIELD(arg0, s32 *, 4) = 6;
                        }
                    }
                }
            }
            break;
        }
        break;
    }
    if ((D_802AC5D0 & 4) && (func_80243EB4(M2C_FIELD(arg0, s32 *, 0xC), 0x20) != 0)) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x9C), f32 *, 8) = (f32) (60.0f - M2C_FIELD(arg0, f32 *, 0x7C));
    } else {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x9C), f32 *, 8) = (f32) M2C_FIELD(arg0, f32 *, 0x7C);
    }
    *M2C_FIELD(arg0, f32 **, 0x9C) = M2C_FIELD(arg0, f32 *, 0x74);
}

static s32 func_80252EA4(f32 *arg0) {
    Seq *p = M2C_FIELD(arg0, Seq **, 0x98);
    f32 f;
    s32 c = 1;
    s32 b = 1;
    s32 a = 1;

    if (p->len[0] != 0) {
        a = 0;
        if (p->cnt[0] != 0) {
            p->cnt[0]--;
        } else if (p->len[0] != p->idx[0]) {
            f = p->a[p->idx[0]].fC;
            M2C_FIELD(arg0, f32 *, 0x7C) = f;
            M2C_FIELD(arg0, SeqOut **, 0x9C)->f8 = f;
            f = p->a[p->idx[0]].f4;
            M2C_FIELD(arg0, f32 *, 0x74) = f;
            M2C_FIELD(arg0, SeqOut **, 0x9C)->f0 = f;
            p->cnt[0] = p->a[p->idx[0]].n;
            p->idx[0]++;
            p->cnt[0]--;
        } else {
            M2C_FIELD(arg0, f32 *, 0x7C) = 0.0f;
            a = 1;
            M2C_FIELD(arg0, SeqOut **, 0x9C)->f8 = 0.0f;
        }
    }
    if (p->len[1] != 0) {
        b = 0;
        if (p->cnt[1] != 0) {
            p->cnt[1]--;
        } else if (p->len[1] != p->idx[1]) {
            M2C_FIELD(arg0, SeqOut **, 0x9C)->vC = p->b[p->idx[1]].v;
            p->cnt[1] = p->b[p->idx[1]].n;
            p->idx[1]++;
            p->cnt[1]--;
        } else {
            b = 1;
            M2C_FIELD(arg0, SeqOut **, 0x9C)->vC = 0;
        }
    }
    if (p->len[2] != 0) {
        c = 0;
        if (p->cnt[2] != 0) {
            p->cnt[2]--;
        } else if (p->len[2] != p->idx[2]) {
            M2C_FIELD(arg0, SeqOut **, 0x9C)->vE = p->c[p->idx[2]].v;
            p->cnt[2] = p->c[p->idx[2]].n;
            p->idx[2]++;
            p->cnt[2]--;
        } else {
            c = 1;
            M2C_FIELD(arg0, SeqOut **, 0x9C)->vE = 0;
        }
    }
    if (a == 1 && b == 1 && c == 1) {
        return 1;
    }
    return 0;
}

static void func_80252D14(f32 *arg0) {
    s32 i;

    if (func_80251D30(arg0, 8, 0, 0) == 0) {
        for (i = 0; i < 8; i++) {
            *(s32 *)(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), u8 **, 0x24) + i * 0x10) = D_802ACFC4;
            M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), u8 **, 0x24) + i * 0x10, f32 *, 0xC) = 70.0f;
            M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), u8 **, 0x24) + i * 0x10, f32 *, 4) =
                (i * 45.0f >= 360.0f) ? i * 45.0f - 360.0f : ((i * 45.0f < 0) ? i * 45.0f + 360.0f : i * 45.0f);
        }
    }
}

static f32 func_80252CD4(u8 *arg0, f32 arg1) {
    if (func_80251AC8(func_80252330((s32 *) (arg0 + 0x38), arg1)) != 0) {
        return 0.0f;
    }
    return 1.0f;
}

static void *func_80252CB4(f32 *arg0, f32 *arg1) {
    return func_8022FA88(arg0, 0x62, arg1);
}

static s32 func_80252BF8(s32 arg0, s32 *arg1) {
    s32 var_s0;
    s32 var_s3;
    s32 var_s4;
    s32 var_s6;
    s32 *temp_s1;

    var_s4 = 1;
    var_s6 = 0;
    var_s3 = 0;
    do {
        if (var_s3 != arg0) {
            var_s0 = 1;
            temp_s1 = (s32 *) ((var_s3 * 8) + D_802A0EF0);
loop_3:
            if (func_80251AC8(func_8026D7D8(arg1[0] + temp_s1[0] * var_s0, arg1[1], arg1[2] + temp_s1[1] * var_s0)) == 0) {
                var_s0 += 1;
                goto loop_3;
            }
            if (var_s4 < var_s0) {
                var_s6 = var_s3;
                var_s4 = var_s0;
            }
        }
        var_s3 += 2;
    } while (var_s3 != 8);
    if (var_s4 == 1) {
        return arg0;
    }
    return var_s6;
}

static s32 func_80252AF8(s32 arg0, s32 *arg1, s32 arg2) {
    s32 *d;
    s32 *side;
    s32 x;
    s32 z;
    s32 i;
    s32 a;
    s32 b;
    s32 c;

    d = ((s32 (*)[2]) D_802A0EF0)[arg0];
    x = arg1[0] + d[0];
    z = arg1[2] + d[1];
    for (i = 0; i < arg2; i++) {
        side = ((s32 (*)[2]) D_802A0EF0)[(arg0 + 2) & 7];
        a = func_8026D7D8(side[0] + x, arg1[1], side[1] + z);
        b = func_8026D7D8(x, arg1[1], z);
        c = func_8026D7D8(x - side[0], arg1[1], z - side[1]);
        if (func_80251AC8(b) == 0) {
            if (func_80251AC8(a) == 0 || func_80251AC8(c) == 0) {
                return 0;
            }
        } else {
            return 1;
        }
        x += d[0];
        z += d[1];
    }
    return 0;
}

static s32 func_802529A4(u8 *arg0, s32 arg1, s32 arg2, f32 arg3) {
    f32 sp3C;
    u8 *temp_v0;
    s32 side;
    f32 sp28[3];
    f32 sp1C[3];

    temp_v0 = func_8022FA88(arg0, arg1, &sp3C);
    if ((temp_v0 != NULL) && (sp3C <= arg3)) {
        sp28[0] = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x10);
        sp28[1] = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14);
        sp28[2] = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x18);
        sp1C[0] = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10);
        sp1C[1] = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14);
        sp1C[2] = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18);
        side = func_80252658(sp28, sp1C);
        switch (side) {
        case 0:
            if (arg2 >= 4 && arg2 < 7) {
                return 1;
            }
            break;
        case 1:
            if (arg2 >= 2 && arg2 < 5) {
                return 1;
            }
            break;
        case 2:
            if (arg2 >= 6 && arg2 < 8) {
                return 1;
            }
            break;
        case 3:
            if (arg2 >= 0 && arg2 < 3) {
                return 1;
            }
            break;
        }
    }
    return 0;
}

static s32 func_80252918(s32 *arg1, s32 arg0, s32 arg2) {
    s32 *d;
    s32 i;
    s32 x;
    s32 z;

    d = ((s32 (*)[2]) D_802A0EF0)[arg0];
    x = arg1[0] + d[0];
    z = arg1[2] + d[1];
    for (i = 0; i < arg2; i++) {
        if (func_80251AC8(func_8026D7D8(x, arg1[1], z)) != 0) {
            return 0;
        }
        x += d[0];
        z += d[1];
    }
    return 1;
}

static s32 func_80252724(u8 *arg0) {
    s32 n = 0;
    s32 max = 0;
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        for (j = i + 1; j < 5; j++) {
            if (M2C_FIELD(&((Unk6BBE0_18 *) arg0)[i], s32 *, 0xA4) == M2C_FIELD(&((Unk6BBE0_18 *) arg0)[j], s32 *, 0xA4) &&
                M2C_FIELD(&((Unk6BBE0_18 *) arg0)[i], s32 *, 0xA8) == M2C_FIELD(&((Unk6BBE0_18 *) arg0)[j], s32 *, 0xA8) &&
                M2C_FIELD(&((Unk6BBE0_18 *) arg0)[i], s32 *, 0xAC) == M2C_FIELD(&((Unk6BBE0_18 *) arg0)[j], s32 *, 0xAC)) {
                n++;
            }
        }
        if (max < n) {
            max = n;
        }
    }
    if (max >= 3 || M2C_FIELD(arg0, s32 *, 0x120) >= 0x1F) {
        return 1;
    }
    return 0;
}

static f32 func_802526A0(f32 *arg1, f32 *arg0) {
    f32 var_fv1;
    s32 temp_v0;

    temp_v0 = func_80252658((u8 *)arg1 + 0x20, arg0);
    if ((M2C_FIELD(arg1, f32 *, 0x74) == 90.0f) || (M2C_FIELD(arg1, f32 *, 0x74) == 270.0f)) {
        if (temp_v0 & 2) {
            var_fv1 = 0.0f;
        } else {
            var_fv1 = 180.0f;
        }
    } else if (temp_v0 & 1) {
        var_fv1 = 90.0f;
    } else {
        var_fv1 = 270.0f;
    }
    return var_fv1;
}

static s32 func_80252658(f32 *arg1, f32 *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(arg1, f32 *, 0) <= M2C_FIELD(arg0, f32 *, 0)) {
        var_v1 = 1;
    }
    if (M2C_FIELD(arg1, f32 *, 8) <= M2C_FIELD(arg0, f32 *, 8)) {
        var_v1 |= 2;
    }
    return var_v1;
}

static f32 func_80252598(f32 *arg0, f32 *arg1) {
    f32 dx;
    f32 dz;
    f32 ret;

    dx = FDIFF(arg0[0], arg1[0]);
    dz = FDIFF(arg0[2], arg1[2]);
    if (dz < dx) {
        if (arg0[0] < arg1[0]) {
            ret = 90.0f;
        } else {
            ret = 270.0f;
        }
    } else if (arg0[2] < arg1[2]) {
        ret = 0.0f;
    } else {
        ret = 180.0f;
    }
    return ret;
}

static f32 func_80252490(f32 *arg0) {
    s32 x;
    s32 z;
    f32 ret;

    x = (s32) M2C_FIELD(arg0, f32 *, 0x20) % 100;
    z = (s32) M2C_FIELD(arg0, f32 *, 0x28) % 100;
    if (z < x) {
        if (x >= 50) {
            ret = 270.0f;
        } else {
            ret = 90.0f;
        }
    } else if (z >= 50) {
        ret = 0.0f;
    } else {
        ret = 180.0f;
    }
    return ret;
}

static f32 func_802523E0(f32 *arg0) {
    f32 a;
    s32 i;

    a = M2C_FIELD(arg0, f32 *, 0x74);
    for (i = 0; i < 4; i++) {
        if (func_80252380((u8 *) arg0, a) != 0.0f) {
            return a;
        }
        a = (a + 90.0f >= 360.0f) ? a + 90.0f - 360.0f : ((a + 90.0f < 0) ? a + 90.0f + 360.0f : a + 90.0f);
    }
    return M2C_FIELD(arg0, f32 *, 0x74);
}

static f32 func_80252380(u8 *arg0, f32 arg1) {
    if (func_80251AC8(func_80252330((s32 *) (arg0 + 0x38), arg1)) != 0 || func_80251A24(0x3FFFF, (f32 *) (arg0 + 0x20), arg1) != 0) {
        return 0.0f;
    }
    return 1.0f;
}

static s32 func_80252330(s32 *arg0, f32 arg1) {
    s32 *d = (s32 *) (D_802A0EF0 + func_802519B4(arg1) * 8);

    return func_8026D7D8(arg0[0] + d[0], arg0[1], arg0[2] + d[1]);
}

static void func_80252174(f32 *arg0) {
    s32 pad[8];
    f32 sp34;
    f32 *temp_s1;
    f32 *temp_s2;
    f32 temp_fv0;
    f32 a;
    s32 n;

    temp_s1 = (u8 *)arg0 + 0x20;
    temp_s2 = (u8 *)arg0 + 0x2C;
    func_8022FF58(temp_s1, temp_s2, &sp34);
    a = sp34;
    temp_fv0 = func_80251C48(temp_s1, temp_s2);
    if (temp_fv0 <= 500.0f) {
        n = (s32) (temp_fv0 / 100.0f) - 3;
        if (n < 0) {
            n = 0;
        }
    } else {
        n = 5;
    }
    if (func_80251D30(arg0, 1, 1, 4) == 0) {
        *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x24) = 3;
        if (!n && !n) {}
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x24), f32 *, 0xC) = 60.0f;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x24), f32 *, 4) = a;
        *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x28) = 8;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x28), s16 *, 4) = 0x4000;
        *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C) = 6;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s16 *, 4) = 0;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s32 *, 8) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), u16 *, 0xC) = 0x8000;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s32 *, 0x10) = 0x1E;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s16 *, 0x14) = 0;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s32 *, 0x18) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s16 *, 0x1C) = 0x4000;
    }
}

static void func_80252048(f32 *arg0) {
    s32 pad[6];
    f32 sp1C;
    f32 a;

    func_8022FF58((u8 *)arg0 + 0x20, (u8 *)arg0 + 0x2C, &sp1C);
    a = sp1C;
    if (func_80251D30(arg0, 1, 0, 4) == 0) {
        *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x24) = 5;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x24), f32 *, 0xC) = 60.0f;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x24), f32 *, 4) = a;
        *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C) = 5;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s16 *, 4) = 0;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s32 *, 8) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), u16 *, 0xC) = 0x8000;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s32 *, 0x10) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s16 *, 0x14) = 0;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s32 *, 0x18) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), u16 *, 0x1C) = 0x8000;
    }
}

static s32 func_80251EE0(f32 *arg0) {
    f32 x;
    f32 r;
    s32 ret;

    x = M2C_FIELD(arg0, f32 *, 0);
    if (x >= 0.0f) {
        r = x + 0.5f;
    } else {
        r = x - 0.5f;
    }
    ret = func_8023369C((f32) (((s32) r / 100) * 100), x, 31.0f) != 0;
    if (ret == 1) {
        x = M2C_FIELD(arg0, f32 *, 8);
        if (x >= 0.0f) {
            r = x + 0.5f;
        } else {
            r = x - 0.5f;
        }
        ret = func_8023369C((f32) (((s32) r / 100) * 100), x, 31.0f) != 0;
    }
    return ret;
}

static void func_80251E5C(f32 *arg0) {
    if (func_80251D30(arg0, 0, 0, 2) == 0) {
        *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), u16 *, 4) = 0x8000;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s32 *, 8) = 2;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 **, 0x2C), s16 *, 0xC) = 0;
    }
}

static void *func_80251D10(f32 *arg0, f32 *arg1) {
    return func_8022FA88(arg0, 0x40, arg1);
}

static void *func_80251C88(s32 arg0) {
    s32 i;

    for (i = 0; i < 48; i++) {
        if (arg0 == M2C_FIELD(D_8008E658 + i * 0x48, s32 *, 0x14)) {
            return D_8008E658 + i * 0x48;
        }
    }
    return NULL;
}

static f32 func_80251C48(f32 *arg1, f32 *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = M2C_FIELD(arg0, f32 *, 0) - M2C_FIELD(arg1, f32 *, 0);
    temp_fv1 = M2C_FIELD(arg0, f32 *, 8) - M2C_FIELD(arg1, f32 *, 8);
    return ((sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1))));
}

static s32 func_80251BDC(f32 *arg1, f32 *arg0) {
    if (func_8023369C(M2C_FIELD(arg1, f32 *, 8), M2C_FIELD(arg0, f32 *, 8), 50.0f) != 0) {
        return 0;
    }
    if (func_8023369C(M2C_FIELD(arg1, f32 *, 0), M2C_FIELD(arg0, f32 *, 0), 50.0f) != 0) {
        return 1;
    }
    return -1;
}

static void *func_80251B08(s32 arg2, s32 *arg0, s32 arg1) {
    f32 v[3];
    s32 x;
    s32 z;
    s32 r;
    s32 *d;

    x = arg0[0];
    z = arg0[2];
    for (;;) {
        if (func_80251AC8(func_8026D7D8(x, arg0[1], z)) != 0) {
            return NULL;
        }
        func_8026E338((f32) x, (f32) arg0[1], (f32) z, v, 0);
        r = func_80251A24(arg2, v, (f32) (arg1 * 45));
        if (r != 0) {
            return (void *) r;
        }
        d = (s32 *) (D_802A0EF0 + arg1 * 8);
        x += d[0];
        z += d[1];
    }
}

static s32 func_80251AC8(s32 arg0) {
    if (((arg0 & 0xF) == 0xF) || (arg0 & 0x60) || (arg0 == 0x2010) || (arg0 == 0x10) || (arg0 & 0x8000)) {
        return 1;
    }
    return 0;
}

static s32 func_80251A24(s32 arg0, f32 *arg1, f32 arg2) {
    s32 dir;
    f32 size[3];
    f32 pos[3];

    size[2] = 40.0f;
    size[1] = 40.0f;
    size[0] = 40.0f;
    dir = func_802519B4(arg2);
    pos[0] = arg1[0] + (f32) (((s32 (*)[2]) D_802A0EF0)[dir][0] * 100);
    pos[1] = arg1[1];
    pos[2] = arg1[2] + (f32) (((s32 (*)[2]) D_802A0EF0)[dir][1] * 100);
    return func_8022F77C(arg0, (s32) pos, (s32) size);
}

static s32 func_802519B4(f32 arg0) {
    f32 temp_fv0;
    f32 var_fv1;

    temp_fv0 = arg0 / 45.0f;
    if (temp_fv0 >= 0.0f) {
        var_fv1 = temp_fv0 + 0.5f;
    } else {
        var_fv1 = temp_fv0 - 0.5f;
    }
    return (s32) var_fv1 & 7;
}

static f32 func_80251994(f32 *arg0, f32 *arg1) {
    f32 sp1C;

    func_8022FF58(arg0, arg1, &sp1C);
    return sp1C;
}

static void *func_80251974(f32 *arg0, f32 *arg1) {
    return func_8022FA88(arg0, 8, arg1);
}

void func_80251804(s32 arg0) {
    f32 *temp_s4;
    u8 *sp40;
    s32 temp_v0;

    sp40 = func_8023A834();
    temp_s4 = (arg0 * 0x128) + D_800BCFE8;
    M2C_FIELD(temp_s4, s32 *, 0xC) = arg0;
    M2C_FIELD(temp_s4, u8 **, 0x9C) = D_802ACF08[arg0];
    M2C_FIELD(temp_s4, s32 *, 0) = 1;
    do {
        temp_v0 = func_80251708(arg0);
        M2C_FIELD(temp_s4, s32 *, 0x10) = temp_v0;
    } while (temp_v0 == -1);
    M2C_FIELD(temp_s4, void **, 0x18) = func_802443F4(arg0);
    M2C_FIELD(temp_s4, void **, 0x1C) = func_802443F4(M2C_FIELD(temp_s4, s32 *, 0x10));
    M2C_FIELD(temp_s4, s32 *, 4) = 0xF3;
    func_802515D8(temp_s4);
    M2C_FIELD(temp_s4, s32 *, 0x84) = 0;
    M2C_FIELD(temp_s4, s32 *, 0x88) = 0;
    M2C_FIELD(temp_s4, s32 *, 0x8C) = 0;
    M2C_FIELD(temp_s4, s32 *, 0x90) = 0;
    M2C_FIELD(temp_s4, s32 *, 0x11C) = 0;
    M2C_FIELD(temp_s4, s32 *, 0x120) = 0;
    M2C_FIELD(temp_s4, s32 *, 0x94) = 0;
    M2C_FIELD(temp_s4, s32 *, 0x14) = -1;
    M2C_FIELD(temp_s4, s32 *, 0x98) = 0;
    M2C_FIELD(temp_s4, f32 *, 0x7C) = 0.0f;
    D_802ACFB0 = 80.0f;
    D_802ACFB4 = 60.0f;
    D_802ACFB8 = 60.0f;
    D_802ACFC4 = D_802A1038[((s32 *) (sp40 + 0x14))[arg0]];
    func_80238A10(func_802553D4, (s32) temp_s4, 0, 0, 0x130);
}

static s32 func_80251708(s32 arg0) {
    u8 *g;
    s32 p;

    g = func_8023A834();
    p = func_80234248(3);
    if ((D_800AEDF0[p].unk24 == 1 || D_800AEDF0[p].unk24 == 2) && func_80243EF0(p) == 0) {
        if (M2C_FIELD(g, s32 *, 0) == 1 && ((s32 *) (g + 0x90))[p] == ((s32 *) (g + 0x90))[arg0]) {
            return -1;
        }
        if (M2C_FIELD(g, s32 *, 0) == 0 && (M2C_FIELD(g, s32 *, 0x24) - ((s32 *) (g + 0xA4))[p]) != 1 && func_80234248(100) < 51) {
            return -1;
        }
        if (p != arg0) {
            return p;
        }
    }
    return -1;
}

static void func_802515D8(f32 *arg0) {
    s32 *cur;
    s32 *hist;
    s32 idx;

    func_80250338(M2C_FIELD(arg0, s32 *, 0xC), (u8 *)arg0 + 0x20);
    cur = (s32 *) ((u8 *)arg0 + 0x38);
    func_8026DCAC(M2C_FIELD(arg0, f32 *, 0x20), M2C_FIELD(arg0, f32 *, 0x24), M2C_FIELD(arg0, f32 *, 0x28), cur, 2);
    hist = ((s32 (*)[6]) ((u8 *)arg0 + 0xA4))[M2C_FIELD(arg0, s32 *, 0x11C)];
    if (func_8025156C(M2C_FIELD(arg0, f32 **, 0x18)) != 0) {
        if (cur[0] != hist[0] || cur[1] != hist[1] || cur[2] != hist[2]) {
            M2C_FIELD(arg0, s32 *, 0x120) = 0;
            idx = ++M2C_FIELD(arg0, s32 *, 0x11C);
            if (idx >= 5) {
                M2C_FIELD(arg0, s32 *, 0x11C) = 0;
                idx = 0;
            }
            hist = ((s32 (*)[6]) ((u8 *)arg0 + 0xA4))[idx];
            hist[0] = cur[0];
            hist[1] = cur[1];
            hist[2] = cur[2];
        } else if (cur[0] == hist[0] && cur[1] == hist[1] && cur[2] == hist[2]) {
            M2C_FIELD(arg0, s32 *, 0x120)++;
        }
    } else {
        M2C_FIELD(arg0, s32 *, 0x120)++;
    }
}

static s32 func_8025156C(f32 *arg0) {
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    if ((M2C_FIELD(arg0, f32 *, 0x58) == M2C_FIELD(temp_v0, f32 *, 0x10)) && (M2C_FIELD(arg0, f32 *, 0x5C) == M2C_FIELD(temp_v0, f32 *, 0x14)) && (M2C_FIELD(arg0, f32 *, 0x60) == M2C_FIELD(temp_v0, f32 *, 0x18))) {
        return 0;
    }
    return 1;
}

void func_80251534(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        D_802ACFBC = 1;
        return;
    case 1:
        D_802ACFBC = 0;
        return;
    }
}

void func_802514CC() {
    s32 i;
    f32 *p;

    for (i = 0; i < 4; i++) {
        p = (f32 *) (D_800BCFE8 + i * 0x128);
        if (M2C_FIELD(p, s32 *, 0x98) != 0) {
            func_80251424(p);
        }
    }
}

static void func_80251424(f32 *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, s32 **, 0x98), s32 *, 0) != 0) {
        free(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), void **, 0x24));
    }
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 *, 4) != 0) {
        free(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), void **, 0x28));
    }
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), s32 *, 8) != 0) {
        free(M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), void **, 0x2C));
    }
    free(M2C_FIELD(arg0, void **, 0x98));
    M2C_FIELD(arg0, void **, 0x98) = NULL;
    M2C_FIELD(arg0, s32 *, 0) &= ~3;
}

void func_802513E0() {
    func_80297D30(0x2D, D_802A1184);
    D_800BD080 = 0;
    D_800BD1A8 = 0;
    D_800BD2D0 = 0;
    D_800BD3F8 = 0;
}
