/*
 * main_code's 54E40 (-O3): 72 functions (us 0x8023A640-0x80243888):
 * tasks spawned through func_80238A10 and func_8022A328, and the display
 * lists of three digit counters.
 *
 * Data (us addresses): its .rodata is its own and placed in
 * data_split.txt. Its .data (0x802A01B0-0x802A0D50, between 53D70's and
 * 5E090's D_802A0D50: the strings, text items and tables) and its .bss
 * (0x802AC5D0-0x802AC880, the 16-byte boundaries after D_802AC5C0..CC,
 * which 54BE0 sets, and before 5E090's D_802AC880) are its own too, but
 * the C reaches most of them through m2c's overlapping structs and
 * arrays (D_802AC610, D_802AC660, D_802AC770), so they stay extern
 * (asm), except D_802AC7A0[10], D_802AC7C8 and D_802AC7CC: those are
 * defined here (0x802AC7A0-0x802AC7D0, no padding) and that .bss is
 * placed in data_split.txt.
 *
 * Written from m2c's functions in the reverse of the ROM's order (IDO
 * -O3 emits last to first), with the fixes the -O3 build needs. It is one
 * object: the only callee emitted after its caller is func_8024364C
 * (called by func_8023F26C), and the IPA statics (func_8023AB54,
 * B2AC, B318, B450 take arguments in s2/fs0/t0, called by func_8023FD08;
 * func_8023E8FC in s4, called by func_80242FB4) tie 0x8023AB54-0x80242FB4
 * together, so no 16-aligned cut is possible.
 *
 * The emission order is the original's. IDO -O3 emits the global
 * functions in reverse source order, each after its callees (depth
 * first, the callees last called first); statics only come out as
 * callees. With an indirect call in the file (func_8024364C's hook
 * D_802AC768), taking a function's address is no edge; the indirect
 * caller calls every function whose address code takes, in the reverse
 * order of their first reference in the source (references in .data
 * don't count). So func_8024364C is defined just below func_8023F26C (its
 * turn starts the run func_8023F26C .. func_802434F8), and
 * func_80243824, the first function in the file, holds dead references
 * that set that order; dead calls (seen by umerge, removed by uopt) pull
 * func_8023AB54 into func_8023AB90, func_8023B2AC into func_8023B318,
 * func_8023EB28 into func_8023ECEC and func_80242268 into func_80242270.
 * - func_80241590, 80241BB0, 80242270 (digit counters over 16x16
 *   pictures) are written with the GBI macros (gDPLoadTLUT_pal256/pal16,
 *   gDPLoadTextureBlock_4b, gDPLoadTextureTile_4b, gSPTextureRectangle)
 *   over TexFile (7C4D0's) D_802A0758 and D_802A075C; the digits go to
 *   D_802AC770 as entry indices (digit * 2). func_80242270's original
 *   frame is 0x128 with only 0x34 used.
 * - The IPA statics (func_8023AB54, AF5C, B2AC, B318, B450, B7C0, E8FC,
 *   EB28, ECF4, EE40, EF38) are static; func_8023AF5C takes its first
 *   argument in fs5 and its second at 0x4(sp) of the caller.
 * - jp: func_802434F8 calls func_802810A0 (us's wrapper func_802811F0
 *   doesn't exist) with the x fixed, and jp's text and x positions are
 *   #if VERSION_JP arms; every function's calls match jp's. eu differs
 *   only in its 50 Hz constants (FPS, FRAME_STEP, TIME_LIMIT).
 * - func_8023B450 takes (value, buf, n). Its IPA registers (value t0,
 *   buf a2) follow uopt's colouring, which for these unconstrained
 *   ranges is the order the expressions first appear: the digit store
 *   `buf[j++] = value / div + 0x10` names buf before the division, and
 *   `t = value / div * div` reuses it, with no d.
 * - func_8023C170 (IPA static, s0-s2 unsaved) uses one counter for both
 *   its loops; with two, its register use moved func_8023DB0C's
 *   s-registers.
 * - D_802AC7A0[10] is defined here: func_8023A640's two peeled stores
 *   share a `lui` only when as1 knows the array. (splat's D_802AC7A4 and
 *   D_802AC7A8 are its elements 1 and 2-9.)
 * - func_8023A734 tests the row index (`arg1 == 0/2/3`), not the row
 *   pointer: uopt still compares the pointer, but with fresh addresses
 *   kept apart from the loads' base (D_802A0BA8 is s32[][11]).
 * - The count is positional: a function one instruction short shifts
 *   every word after it, so its size matters more than its registers.
 *   What fixed sizes here: a separate index (`D_802AC770[k++]`, k = 0)
 *   leaves the original's dead `move v0,zero`; a global pointer read
 *   again each iteration is `tf = D_802A0758;` at the top of the loop
 *   body; a loop end against arr+N folded into one relocation is a
 *   compare with the next symbol (`r != (Rect54E40 *) D_802A079C`);
 *   calls m2c shows in both branches are both there (func_8023B8D0).
 *   func_8023AC38's dead call to func_8023AB90 keeps the order once
 *   func_8023AB54 is inlined.
 * - func_8023E1D8's three handle loops (sltu against the end, pointer
 *   spilled across the call) index `items[i]` (an index used in an
 *   address gets SR+LFTR; a `p++` form keeps a counter). The first is
 *   func_8023AB4C inlined; the other two are written out through one
 *   function-scope `TextItem *items`, so their IVs come from copy
 *   propagation, with bits after the loop-end test's, and take the second
 *   spill slot (sp+72) as in the original (`D_802A0ACC[i]` names the IV
 *   first: sp+76). The third loop counts with j: with i, the while loop's
 *   timer, uopt's LFTR builds the end as base + keys*20 at run time (an
 *   add chain and an overflow trap). func_8027EFA8 returns a u16 (the
 *   `move v1,v0` copy into keys). `cur = func_8026CE28(0x130);` on its own
 *   line saves the nested call's cfe temporary, the word j needs: the
 *   frame is h1, h2, buf, the locals, then the inlined areas (each one's
 *   parameters 8-aligned, its locals below), and an inlined
 *   func_8023AB4C as the last area could never give the original's frame.
 * - func_8023FD08 keeps its message handles in a plain array h[3] and a
 *   count nh (not a struct: `t.h[t.n]` folds the member offset into the
 *   index), with `nh = 0; h[nh++] = ...` for the first one: nh stays
 *   unaliased (the end loop's `bne`, the third store's address hoisted
 *   to the join by PRE) but isn't constant-propagated into the second
 *   store. It has no pointer local: `D_802AC7F8[i]` everywhere makes
 *   every address a uopt temp, all spilled at sp+76 as in the original;
 *   pad1/pad2 keep the frame.
 * - func_8023CD1C is static (not inlined: four callers): ugen then takes
 *   its temporaries from t6-t9 only, which gives the else arm's rotation.
 *   fcmp counts a static with the function before it, so func_8023D0F8's
 *   player loop (index form, `pl = &PLAYERS[i]`, the type read twice
 *   rather than through a local) was counted under func_8023CD1C.
 * - func_80242270's counters take the x position through a pointer
 *   (`pos = &D_802A0764[i]; ... e = tf->entries; x = *pos;`). uopt gives
 *   coloured expressions spill slots greedily in bit order, and ties in
 *   colouring priority go to the lower bit: the &D_802A0764[i] IV (never
 *   given a register) must come before tf+12 (e) to get the first slot
 *   (sp+52), and e before x to get t2 before x's t3. A plain
 *   `x = D_802A0764[i]` names x before its address, so either e comes
 *   first (slot sp+48) or x does (t2/t3 swapped); pos is copy-propagated
 *   and only orders the address.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

#define F3DEX_GBI
#define _SHIFTL(v, s, w) ((unsigned int) (((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define _SHIFTR(v, s, w) ((unsigned int)(((unsigned int)(v) >> (s)) & ((0x01 << (w)) - 1)))
#include "ultralib/PR/gbi.h"

/* gSPTextureRectangle with the y terms before the x terms in both words
 * (the order the original evaluates them in). */
#define gSPTextureRectangleYX(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
    _g->words.w0 = (_SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL(yh, 0, 12) | _SHIFTL(xh, 12, 12)); \
    _g->words.w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(yl, 0, 12) | _SHIFTL(xl, 12, 12)); \
    gImmp1(pkt, G_RDPHALF_1, (_SHIFTL(s, 16, 16) | _SHIFTL(t, 0, 16))); \
    gImmp1(pkt, G_RDPHALF_2, (_SHIFTL(dsdx, 16, 16) | _SHIFTL(dtdy, 0, 16))); \
}

typedef struct {
    /* 0x00 */ u8 *str;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scale;
    /* 0x0C */ s32 mode;
    /* 0x10 */ s32 handle;
} TextItem; /* size = 0x14 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
} UnkStruct_802AC610; /* size = 0x50 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4[4];
    /* 0x14 */ s32 unk14[4];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40[4];
    /* 0x50 */ s32 unk50[4][4];
    /* 0x90 */ s32 unk90[4];
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ s32 unkA4[4];
    /* 0xB4 */ s32 unkB4[4];
    /* 0xC4 */ u8 unkC4[0x24];
    /* 0xE8 */ s32 unkE8[4];
} UnkStruct_802AC660; /* size >= 0xF8 */

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} UnkStruct_8023FD08_48_4;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_8023FD08_48_4 *unk4;
} UnkStruct_8023FD08_48;

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C[0xC];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 unk38[0x10];
    /* 0x48 */ UnkStruct_8023FD08_48 *unk48;
} UnkStruct_8023FD08;

/* A player (D_800AEDF0[4], 0xC8 bytes). */
typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 unk28[0x94 - 0x28];
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ u8 unk9C[0xC8 - 0x9C];
} Player54E40; /* size 0xC8 */

#define PLAYERS ((Player54E40 *) D_800AEDF0)

/* One entry of a texture file's table (12 bytes, after a 12-byte header). */
typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ u16 width;
    /* 0x06 */ u16 height;
    /* 0x08 */ s32 offset;
} TexEntry; /* size 0xC */

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ TexEntry entries[1];
} TexFile;

/* A picture drawn by func_80242270: its entry and its rectangle. */
typedef struct {
    /* 0x00 */ s32 idx;
    /* 0x04 */ s32 xl;
    /* 0x08 */ s32 yl;
    /* 0x0C */ s32 xh;
    /* 0x10 */ s32 yh;
} Rect54E40; /* size 0x14 */

s32 func_802810A0(u8 *, u16, u16, f32, f32, u8);

void func_802268F4(s32);
void func_8022691C(s32);
void func_802276E0(s32, s32, s32);
void func_802276FC(s32);
void func_80227870(void);
void func_80227C18(void);
void func_80227EE0(s32);
void func_80227F88(void);
void func_80228008(s32, s32, s32);
s32 func_802280F4(s32, s32);
void func_80229280(s32);
s32 func_8022979C(s32, s32, s32);
void func_80229E38(void *, s32, s32);
void * func_8022A328(void *, s32, s32, s32, s32);
s32 func_8022F550(s32, s32);
s32 func_8022FC90(void *);
void func_8022FDE8(void);
void func_80230914(void *);
void * func_80231274(s32, s32, s32, void *);
void func_802313DC(void *, s32);
void func_80231408(void *, s32);
s32 func_80232D18(void *, s32);
void func_802346C8(f32, f32, f32);
void func_80234778(f32, f32, f32);
void func_80234858(f32 *, f32 *, f32 *);
void func_802348B4(f32 *, f32 *, f32 *);
s32 func_80234DD4(f32, f32, f32, void *);
void func_80234F6C(s32);
void func_802350F8(s32);
void func_80236218(s32);
s32 func_802362A8(void);
void func_802362B8(s32);
void func_80236B7C(void);
s32 func_80238A10(void *, u32, s32, s32, s32);
s32 func_80238CF8(s32, s32);
s32 func_80238DFC(s32, s32, u32);
void func_80238EA8(s32);
s32 func_80238F40(s32, s32);
s32 func_8023903C(s32);
s32 func_80239094(void);
s32 func_802391F0(void);
void func_80239430(void);
s32 func_802399AC(s32);
s32 func_80239FF8(s32);
u8 func_8023A038(s32);
void func_80243A30(void);
s32 func_80243DDC(void);
void func_80243E90(s32);
s32 func_80243EF0(s32);
s32 func_802441AC(void *);
void * func_802443F4(s32);
void func_802444B8(s32, s32);
s32 func_80244BA4(s32, s32);
void func_80244C30(s32, s32);
void func_80245208(s32, s32);
void func_80245280(s32);
void func_802452E8(s32);
void func_8024585C(s32);
void func_80245868(void);
void func_802459BC(s32);
void func_80246D74(s16);
void func_80247C50(s32);
void func_80250338(s32, void *);
void func_802510F0(void);
void func_802513E0(void);
void func_802514CC(void);
void func_80251534(s32);
void func_80251804(s32);
void func_8025C590(s32);
f64 func_8025E63C(void);
void func_8026BF28(s8);
void func_8026BF68(s8);
void func_8026BF90(s8);
void func_8026C394(void);
s32 func_8026C660(s32);
void func_8026C6D0(s32);
void func_8026C894(void);
void func_8026C8E8(void);
void func_8026C93C(s32);
void func_8026C964(void);
void func_8026CB2C(void);
void func_8026CF90(void);
void func_8026D5B4(s32);
s32 func_8026D7D8(s32, s32, s32);
void func_8026DCAC(f32, f32, f32, void *, s32);
void func_8026E338(f32, f32, f32, f32 *, s32);
f32 func_8026E8B8(void);
f32 func_8026E938(void *);
void func_8026F02C(void);
s32 func_80270770(s16, s16);
void func_80277484(void);
void func_8027783C(void);
void func_80277AF8(s16, s16);
void func_80277DF4(s16);
void func_80277E1C(void);
s32 func_80278E84(s32, s32);
void func_8027BBC4(void);
void func_8027EBCC(void);
u16 func_8027EFA8(void);
void func_8027F400(void);
void func_8027F428(void);
void func_8027F658(void *, void *, u16, u16, u16);
void func_8027F79C(void);
void func_8027F820(void *);
void func_8027F858(s32, s32);
void func_8027FC08(void);
s32 func_80280C08(u8 *);
s32 func_80280DB4(s32);
void func_80280EB0(s32, u16, u16);
s32 func_802811F0(u8 *, u16, u16, f32, f32, u8);
void func_802814D8(s32, u16, u16);
void func_80281A40(void);
void func_80281A88(s32, s32, s32, s32);
void func_80281AE0(s32, s32, s32, s32);
void func_802822B0(s32);
void func_80282430(void *, s32, s32);
void * func_802867E4(s32, f32, f32, f32);
void func_80286E60(void);
void func_80286EF0(void);
s32 func_80286F04(void);
s32 func_80287008(s32, s32, s32);
s32 func_802871D0(s32);
s32 func_80287680(void);
void func_8028785C(void);
s32 * func_8028A060(s32);
void func_8028A0B4(void);
s32 func_8028A36C(s32);
void func_8028A3D0(s32);
void func_8028A428(s32);
s32 func_8028A4E0(s32);
void func_8028A584(void);
s32 func_8028A81C(s32, f32, f32, f32, s32);
s32 func_8028E8E0(void);
s32 func_802909FC(void *, void (*)());
void func_80245150();
void func_80291944(void *, s32, f32);
void func_8029236C(void);
void func_802923CC(void);
s32 func_8029279C(void *, s32, s32, s32, f32);
s32 func_802947AC(void);
s32 func_80294CE8(s32);
s32 func_80295330(s32);
void func_80295384(void);

extern u8 D_1000000[];
extern u8 D_800AEBBC[];
extern u8 D_800AED4C[];
extern u8 D_800AEDF0[];
extern s32 D_800AEE04;
extern s32 D_800AEE14;
extern s32 D_800AEE58;
extern s32 D_800AEEDC;
extern s32 D_800AEF20;
extern s32 D_800AEFA4;
extern s32 D_800AEFE8;
extern s32 D_800AF06C;
extern s32 D_800AF0B0;
extern u8 D_800BD000[];
extern s32 D_800BE818;
extern s32 D_800BE824;
extern u8 D_800BE830[];
extern s32 D_802A0038;
extern s32 D_802A01B0;
extern s32 D_802A01B4;
extern s32 D_802A01B8;
extern s32 D_802A01BC;
extern s32 D_802A01C0;
extern u8 D_802A01C4[];
extern u8 D_802A01D0[];
extern u8 D_802A01D8[];
extern u8 D_802A01E0[];
extern u8 D_802A039C;
extern u8 D_802A0448[];
extern u8 D_802A04A4[];
extern u8 D_802A04B4[];
extern u8 D_802A04C8[];
extern u8 D_802A063C[];
extern s32 D_802A0654;
extern u8 D_802A0658[];
extern u8 D_802A0748[];
extern u8 D_802A0750[];
extern TexFile *D_802A0758;
extern TexFile *D_802A075C;
extern u8 *D_802A0760;
extern s32 D_802A0764[2];
extern s32 D_802A076C[2];
extern Rect54E40 D_802A0774[2];
extern s32 D_802A079C[7];
extern s32 D_802A07B8[7];
extern Rect54E40 D_802A07D4[5];
extern s32 D_802A0838[5];
extern u8 D_802A084C[];
extern u8 D_802A0888[];
extern s32 D_802A08D8[5];
extern u8 D_802A08E4[];
extern u8 D_802A08EC[];
extern u8 *D_802A08F8[][4];
extern s32 D_802A0958[][4];
extern s32 D_802A09B8[][4];
extern TextItem D_802A0A18[];
extern TextItem D_802A0A68[];
extern TextItem D_802A0A7C[];
extern TextItem D_802A0AB8[];
extern TextItem D_802A0ACC[];
extern TextItem D_802A0B1C[];
extern s32 D_802A0B40;
extern s32 D_802A0B80;
extern u8 D_802A0B84[];
extern s32 D_802A0B94;
extern u8 D_802A0B98[];
extern s32 D_802A0BA8[][11];
extern s32 D_802A0CB0[];
extern s32 D_802A0CC8[];
extern u8 D_802A0CF4[];
extern s32 D_802AC5CC;
extern s32 D_802AC5D0;
extern s32 D_802AC5D4;
extern s32 D_802AC5D8;
extern s32 D_802AC5DC;
extern s32 D_802AC5E0;
extern s32 D_802AC5E4;
extern s32 D_802AC5E8;
extern s32 D_802AC5EC;
extern s32 D_802AC5F0;
extern f32 D_802AC5F4;
extern f32 D_802AC5F8;
extern f32 D_802AC5FC;
extern f32 D_802AC600;
extern s32 D_802AC604;
extern s32 D_802AC608;
extern UnkStruct_802AC610 D_802AC610;
extern s32 D_802AC624;
extern s32 D_802AC628;
extern UnkStruct_802AC660 D_802AC660;
extern u8 D_802AC670[];
extern u8 D_802AC6A0[];
extern u8 D_802AC714[];
extern s32 D_802AC758;
extern s32 D_802AC75C;
extern s32 D_802AC760;
extern s32 (*D_802AC768)(void *);
extern s32 D_802AC770[10];
extern u8 D_802AC780[];
extern s32 D_802AC798;
s32 D_802AC7A0[10];
s32 D_802AC7C8;
s32 D_802AC7CC;
extern void *D_802AC7D0;
extern void *D_802AC7D4;
extern s32 D_802AC7D8;
extern void *D_802AC7DC;
extern void *D_802AC7E0;
extern s32 D_802AC7E4;
extern s32 D_802AC7E8;
extern s32 D_802AC7EC;
extern s32 D_802AC7F0;
extern UnkStruct_8023FD08 *D_802AC7F8[];
extern s32 D_802AC80C;
extern s32 D_802AC810;
extern s32 D_802AC814;
extern void *D_802AC818;
extern u8 D_802AC820[];
extern u8 D_802AC828[];
extern s32 D_802AC850;
extern s32 D_802AC854;
extern u32 D_802AC858;
extern u8 D_802AC868[];

void func_8023A640(void);
void func_8023A68C(void);
void func_8023A734(s32 arg0, s32 arg1, s32 arg2);
s32 *func_8023A834(void);
s32 *func_8023A840(void);
void func_8023A84C(s32 arg0);
void func_8023A858(s32 arg0);
void func_8023A864(s32 arg0);
s32 func_8023A870(s32 arg0, s32 arg1);
s32 func_8023AA60(s32 arg0);
void func_8023AA78(s32 arg0);
void func_8023AAE4(void);
static void func_8023AB54(TextItem *items, s32 n);
static void func_8023AB4C(TextItem *items, s32 n);
static s32 func_8023AB90(void);
static void func_8023AC38(void);
void func_8023ADD4(s32 arg0);
void func_8023AE6C(s32 arg0, s32 arg1, s32 arg2);
void func_8023AED0(s32 arg0);
s32 func_8023AEDC(s32 arg0);
static void func_8023AF5C(f32 arg0, f32 arg1);
static s32 func_8023B2AC(u8 *str, f32 scale);
static void func_8023B318(TextItem *items, s32 n);
static void func_8023B450(s32 value, u8 *buf, s32 n);
static void func_8023B7C0(f32 arg0);
static void func_8023B8D0();
s32 func_8023BBCC(void);
static void func_8023C170(void);
void func_8023C374(void);
static void func_8023CC4C(void);
static void func_8023CA94(void);
void func_8023CC54(s32 arg0);
static void func_8023CD1C(void);
static void func_8023D0F0(void);
static void func_8023CECC(void);
static void func_8023D840(void);
static s32 func_8023D0F8(void);
void func_8023D848(void);
static void func_8023D8A0(void);
static void func_8023D9FC(void);
void func_8023DA04(s32 arg0);
void func_8023DB0C(void);
void func_8023E1D8(void);
void func_8023E8AC(void);
static void func_8023E8FC(f32 *arg0);
static void *func_8023EB28(s32 arg0);
void func_8023ECEC(void);
static void func_8023ECF4(u8 *arg0);
static void func_8023EE40(s32 arg0);
static void func_8023EF38(u8 *arg0);
void func_8023F26C(void);
void func_8023FAA0(void);
s32 func_8023FC00(u8 arg0, u16 arg1);
void func_8023FC80(s32 arg0, u8 **arg1);
void func_8023FD08();
void func_80240F34(void);
void func_80241180(void);
void func_80241550(void);
void func_80241590(s32 arg0, Gfx **gdl);
void func_80241BB0(s32 arg0, Gfx **gdl);
void func_80242268(void);
void func_80242270(s32 arg0, Gfx **gdl);
static void func_80242994(void);
void func_80242DA8(void);
void func_80242FB4();
void func_802434F8();
void func_8024364C(u8 *arg0);
void func_8024368C(s32 (*arg0)(void *));
void func_80243698(s32 arg0);
void func_80243718(void);
void func_80243790(void);
s32 func_80243798(s32 arg0);
void func_802437C0(void);
void func_802437E0(void);
s32 func_80243800(void);
void func_80243810(s32 arg0, s32 arg1);
void func_80243824(s32 arg0);

#if VERSION_JP
#define func_802811F0 func_802810A0
#define STR_A D_8029FB00_jp
#define STR_B D_8029FB10_jp
#define X_01D8 0x70
#define X_01E0 0x83
#define X_B7C0 0xA0U
#define X_FD08_1 0xAA
#define X_FD08_2 0xDA
#define X_FD08_3 0x8C
extern u8 D_8029FB00_jp[];
extern u8 D_8029FB10_jp[];
#else
#define STR_A D_802A04A4
#define STR_B D_802A04B4
#define X_01D8 func_8023B2AC(D_802A01D8, 0.8f)
#define X_01E0 func_8023B2AC(D_802A01E0, 0.8f)
#define X_B7C0 0xB4U
#define X_FD08_1 0xBE
#define X_FD08_2 0xE2
#define X_FD08_3 0xA0
#endif

/* eu runs at 50 frames a second: its second, its per-frame step of the
 * 100-frame counter and its time limit differ. */
#if VERSION_EU
#define FPS 50
#define FRAME_STEP 2.0f
#define TIME_LIMIT 0x3841
#else
#define FPS 0x3C
#define FRAME_STEP 1.6666666f
#define TIME_LIMIT 0x2A31
#endif

void func_80243824(s32 arg0) {
    s32 idx;
    s32 n;

    idx = D_802AC608;
    for (n = 0; n < 10; n++) {
        if (D_802AC7A0[idx] == -1) {
            break;
        }
        if (++idx >= 10) {
            idx = 0;
        }
    }
    D_802AC7A0[idx] = arg0;
    if (0) {
        func_80238A10(func_802434F8, 0, 0, 0, 0);
        func_80238A10(func_80242FB4, 0, 0, 0, 0);
        func_80238A10(func_80242DA8, 0, 0, 0, 0);
        func_80238A10(func_80242270, 0, 0, 0, 0);
        func_80238A10(func_80241BB0, 0, 0, 0, 0);
        func_80238A10(func_80241590, 0, 0, 0, 0);
        func_80238A10(func_80241550, 0, 0, 0, 0);
        func_80238A10(func_80241180, 0, 0, 0, 0);
        func_80238A10(func_80240F34, 0, 0, 0, 0);
        func_80238A10(func_8023FD08, 0, 0, 0, 0);
        func_80238A10(func_8023FC80, 0, 0, 0, 0);
        func_80238A10(func_8023FC00, 0, 0, 0, 0);
        func_80238A10(func_8023FAA0, 0, 0, 0, 0);
        func_80238A10(func_8023F26C, 0, 0, 0, 0);
        func_80238A10(func_8023DB0C, 0, 0, 0, 0);
    }
}

void func_80243810(s32 arg0, s32 arg1) {
    D_802AC5DC = arg0;
    D_802AC5E0 = arg1;
}

s32 func_80243800() {
    return D_802AC5D8;
}

void func_802437E0() {
    func_80239FF8(0);
}

void func_802437C0() {
    func_802399AC(0);
}

s32 func_80243798(s32 arg0) {
    if (((arg0 & 0xF) == 0xF) || (arg0 & 0x60)) {
        return 0;
    }
    return 1;
}

void func_80243790() {

}

void func_80243718() {
    func_8028A0B4();
    if (D_802AC610.unk40 == 0) {
        func_80277DF4(0x407);
        if (PLAYERS[0].unk20 >= 5) {
            PLAYERS[0].unk20 = 4;
        }
    }
    D_802AC610.unk30 = 0;
    func_80286EF0();
    D_802AC5D0 |= 0x90;
}

void func_80243698(s32 arg0) {
    if (arg0 != 0) {
        D_802AC5D0 |= 0x40;
        func_80245280(1);
        func_80238DFC(0xB0, 0x3CF, 0U);
        return;
    }
    if (arg0 == 0) {
        D_802AC5D0 &= ~0x40;
        func_80245280(0);
        func_80238CF8(0xB0, 0x3CF);
    }
}

void func_8024368C(s32 (*arg0)(void *)) {
    D_802AC768 = arg0;
}

void func_802434F8() {
    s32 temp_s2;
    s32 var_s0;

    temp_s2 = func_802811F0(D_802A08EC, 0x140U, 0x6EU, 0.8f, 0.8f, 3U);
    func_8026C964();
    func_8026C660(0x1E9);
    for (var_s0 = 0xF0; var_s0 != 0; var_s0 -= 4) {
        if (D_802AC5D0 & 0x10) {
            break;
        }
#if VERSION_JP
        func_80280EB0(temp_s2, 0x49, var_s0);
#else
        func_80280EB0(temp_s2, func_8023B2AC(D_802A08EC, 0.8f), var_s0);
#endif
        func_80239094();
    }
    func_8026C93C(0x1C);
    func_80280DB4(temp_s2);
    func_80239430();
}

void func_80242FB4() {
    s32 id;
    s32 i;
    s32 k;
    u8 *obj;
    s32 lives;
    f32 pos[3];
    s32 st;
    u8 *p;

    lives = 5;
    i = func_802391F0();
    id = i - 1;
    func_80287008(id, 0x19, i + 0x1D);
    for (i = 0; i < lives; i++) {
        p = func_80231274(0x130, 0x01000000, 0xD0, NULL);
        ((u8 * (*)[5]) D_802AC828)[id][i] = p;
        M2C_FIELD(M2C_FIELD(p, u8 **, 0x40), f32 *, 0x10) = ((f32 *) D_802A0748)[id];
        M2C_FIELD(M2C_FIELD(p, u8 **, 0x40), f32 *, 0x14) = i * 24.0f + 40.0f;
        M2C_FIELD(M2C_FIELD(p, u8 **, 0x40), f32 *, 0x18) = ((f32 *) D_802A0748)[id] + 16.0f;
        M2C_FIELD(M2C_FIELD(p, u8 **, 0x40), f32 *, 0x1C) = M2C_FIELD(M2C_FIELD(p, u8 **, 0x40), f32 *, 0x14) + 16.0f;
        M2C_FIELD(M2C_FIELD(p, u8 **, 0x40), s32 *, 0x38) = ((s32 *) D_802A0750)[id];
    }
loop_3:
    for (i = 0; i < 4; i++) {
        if ((D_802AC660.unk4[i] != 0) && (id == D_802AC660.unk90[i])) {
            func_8023E8FC(pos);
            func_80286EF0();
            obj = func_802867E4(id, pos[0], pos[1] + 1500.0f, pos[2]);
            if (obj == NULL) {
                func_80239094();
                goto loop_3;
            }
            ((u8 **) D_802AC820)[id] = obj;
            M2C_FIELD(M2C_FIELD(M2C_FIELD(obj, u8 **, 0), u8 **, 0x40), f32 *, 0x10) = pos[0];
            M2C_FIELD(M2C_FIELD(M2C_FIELD(obj, u8 **, 0), u8 **, 0x40), f32 *, 0x18) = pos[2];
            while (func_8022F550(M2C_FIELD(obj, s32 *, 0), 0x10) != 0) {
                M2C_FIELD(M2C_FIELD(M2C_FIELD(obj, u8 **, 0), u8 **, 0x40), f32 *, 0x14) += 100.0f;
            }
            M2C_FIELD(obj, s8 *, 0x6D) = lives;
            func_80282430(obj, 0xF, 3);
            M2C_FIELD(obj, s16 *, 0x6E) = 0x3C;
            M2C_FIELD(obj, s8 *, 0x78) = 1;
            func_80231408(M2C_FIELD(obj, void **, 0), 0x0C040000);
            break;
        }
    }
    i = 0;
    while (TRUE) {
        st = func_802871D0((s32) obj) & 3;
        if (st == 3) {
            lives = M2C_FIELD(obj, u8 *, 0x6D);
            goto loop_3;
        }
        if ((st != 0) || (lives == 0)) {
            for (i = 0; i < lives - M2C_FIELD(obj, u8 *, 0x6D); i++) {
                func_8022FC90(((u8 *(*)[5]) D_802AC828)[id][lives - 1 - i]);
            }
            (&D_802AC760)[id] = 0;
            break;
        }
        if (((M2C_FIELD(obj, u8 *, 0x7A) & 0xF) == 3) && (lives != M2C_FIELD(obj, u8 *, 0x6D))) {
            for (i = 0; i < lives - M2C_FIELD(obj, u8 *, 0x6D); i++) {
                func_8022FC90(((u8 *(*)[5]) D_802AC828)[id][lives - 1 - i]);
            }
            lives = M2C_FIELD(obj, u8 *, 0x6D);
            if (M2C_FIELD(obj, u8 **, 0x68) != NULL) {
                M2C_FIELD(M2C_FIELD(obj, u8 **, 0x68), f32 *, 0x1C) = 0.0f;
            }
            p = M2C_FIELD(M2C_FIELD(obj, u8 **, 0), u8 **, 0x44);
            if (p != NULL) {
                i = func_802441AC(p);
                func_80244C30(i, 0);
                func_802444B8(i, 0);
            }
            i = 0;
            func_8023E8FC(pos);
            M2C_FIELD(M2C_FIELD(M2C_FIELD(obj, u8 **, 0), u8 **, 0x40), f32 *, 0x10) = pos[0];
            M2C_FIELD(M2C_FIELD(M2C_FIELD(obj, u8 **, 0), u8 **, 0x40), f32 *, 0x14) = pos[1] + 600.0f;
            M2C_FIELD(M2C_FIELD(M2C_FIELD(obj, u8 **, 0), u8 **, 0x40), f32 *, 0x18) = pos[2];
            while (func_8022F550(M2C_FIELD(obj, s32 *, 0), 0x10) != 0) {
                M2C_FIELD(M2C_FIELD(M2C_FIELD(obj, u8 **, 0), u8 **, 0x40), f32 *, 0x14) += 100.0f;
            }
        }
        func_80239094();
    }
    func_80239430();
}

void func_80242DA8() {
    s32 i;

    D_802AC850 = 0;
    D_802AC854 = 0;
    if (D_802AC660.unk0 == 0) {
        while (D_802AC758 >= 2) {
            func_80239094();
        }
        if (D_802AC758 > 0) {
            for (i = 0; i < 4; i++) {
                if ((func_80243EF0(i) == 0) && ((PLAYERS[i].unk24 == 1) ||
                                                (PLAYERS[i].unk24 == 2))) {
                    break;
                }
            }
            D_802AC850 = 1;
            func_8023903C(0x1E);
            if ((func_80243EF0(i) == 0) && ((PLAYERS[i].unk24 == 1) ||
                                            (PLAYERS[i].unk24 == 2))) {
                func_8024585C(i);
                func_80247C50(i);
                func_802452E8(1);
            }
        }
    } else {
        while ((&D_802AC760)[0] != 0 && (&D_802AC760)[1] != 0) {
            func_80239094();
        }
        D_802AC850 = 1;
        func_8023903C(0x3C);
        if ((&D_802AC760)[0] != 0 || (&D_802AC760)[1] != 0) {
            func_80238DFC(0xD0, 0xD0, 0);
        }
    }
    func_80242994();
    func_80239430();
}

static void func_80242994() {
    s32 i;
    s32 n;
    UnkStruct_8023FD08 *o;

    if (D_802AC854 != 0) {
        return;
    }
    D_802AC5D0 |= 0x10;
    func_80238DFC(0x70, 0x70, 0);
    func_802510F0();
    for (i = 0; i < 4; i++) {
        if ((PLAYERS[i].unk24 == 1) || (PLAYERS[i].unk24 == 2)) {
            func_8024585C(i);
            func_80247C50(i);
            func_802452E8(1);
        }
    }
    for (i = 0, n = 0; i < 4; i++) {
        if ((PLAYERS[i].unk24 != 0) && (PLAYERS[i].unk24 != 3) &&
            (func_80243EF0(i) == 0)) {
            n++;
        }
    }
    if (((D_802AC660.unk0 == 0) && (n != 1)) ||
        ((D_802AC660.unk0 == 1) && ((&D_802AC760)[0] == 0) && ((&D_802AC760)[1] == 0))) {
        func_8023903C(0x3C);
        func_8026C660(0x1E6);
        func_8023903C(0x32);
        func_8026C93C(0x21);
        func_8023903C(0x3C);
        o = func_8022A6C4(func_8026CE28(0x3E), 0);
        o->unkC |= 0x100;
        o->unk34 = D_802AC5CC;
        o->unk10 = 0.0f;
        o->unk14 = 0.0f;
        o->unk18 = 0.0f;
        o->unk28 = 0.1f;
        o->unk2C = 0.1f;
        o->unk30 = 0.1f;
        for (i = 0; i < 0x87; i++) {
            if (i == 0x28) {
                func_8026C660(0x1DD);
            }
            o->unk18 = i * 7.4074073f;
            func_80239094();
        }
        func_8022A1E8(o);
        func_8026CCBC(0x3E);
        func_8026C8E8();
        func_8026C894();
        func_8023AE6C(D_802AC5D4, D_802AC5D8, 0);
    } else if (D_802AC660.unk0 == 0) {
        func_8026C660(0x1E5);
        func_8023903C(0x3C);
        func_8026C8E8();
        func_8026C894();
        for (i = 0; i < 4; i++) {
            if ((PLAYERS[i].unk24 != 0) && (PLAYERS[i].unk24 != 3) &&
                (func_80243EF0(i) == 0)) {
                break;
            }
        }
        func_8023AE6C(0x22, i + 0x11, 0);
    } else {
        func_8023903C(0x3C);
        func_8026C660(0x1E5);
        func_8023903C(0x3C);
        func_8026C8E8();
        func_8026C894();
        for (i = 0; i < 2; i++) {
            if ((&D_802AC760)[i] == 1) {
                break;
            }
        }
        func_8023AE6C(0x22, i + 0x16, 0);
    }
}

void func_80242270(s32 arg0, Gfx **gdl) {
    Gfx *gfx;
    TexFile *tf;
    TexEntry *e;
    s32 *digit;
    s32 n;
    s32 x;
    s32 *pos;
    s32 i;
    s32 j;
    s32 v;
    s32 div;
    s32 d;
    s32 m;
    s32 t;
    s32 k;

    k = 0;
    v = D_802AC610.unk30;
    div = 10000000;
    for (m = 0; m < 8; m++) {
        d = v / div;
        D_802AC770[k++] = d * 2;
        t = d * div;
        if (v >= t) {
            v -= t;
        }
        div /= 10;
    }
    v = D_802AC610.unk1C;
    div = 10;
    m = 0;
    do {
        d = v / div;
        D_802AC770[k++] = d * 2;
        t = d * div;
        if (v >= t) {
            v -= t;
        }
        div /= 10;
        m++;
    } while (m != 2);
    if (0) {
        func_80242268();
    }
    gfx = *gdl;
    gDPSetRenderMode(gfx++, 0x553048, 0);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFCF279);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, 1);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    for (j = 0; j < 2; j++) {
        tf = D_802A0758;
        gDPLoadTLUT_pal256(gfx++, (u8 *) tf + tf->entries[D_802A0774[j].idx + 1].offset);
        gDPLoadTextureBlock_4b(gfx++, (u8 *) tf + tf->entries[D_802A0774[j].idx].offset, G_IM_FMT_CI, 16, 16, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx++, D_802A0774[j].xl, D_802A0774[j].yl, D_802A0774[j].xh, D_802A0774[j].yh, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    }
    n = 0;
    tf = D_802A075C;
    for (i = 0; i < 2; i++) {
        pos = &D_802A0764[i];
        j = 0;
        e = tf->entries;
        x = *pos;
        if (D_802A076C[i] > 0) {
            digit = &D_802AC770[n];
            do {
                n++;
                if (i == 0 && D_802AC610.unk28 < D_802AC610.unk30) {
                    gDPLoadTLUT_pal16(gfx++, 0, (u8 *) tf + e[25].offset);
                } else {
                    gDPLoadTLUT_pal16(gfx++, 0, (u8 *) tf + e[1].offset);
                }
                gDPLoadTextureTile_4b(gfx++, (u8 *) tf + e[*digit++].offset, G_IM_FMT_CI, 10, 18, 0, 0, 9, 17, 0,
                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, x << 2, 22 << 2, (x + 10) << 2, 40 << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
                j++;
                x += 10;
            } while (j < D_802A076C[i]);
        }
    }
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    *gdl = gfx;
}




void func_80242268() {

}

void func_80241BB0(s32 arg0, Gfx **gdl) {
    Gfx *gfx;
    TexFile *tf;
    TexEntry *e;
    s32 i;
    s32 j;
    s32 n;
    s32 x;

    if (D_802AC660.unk28 < 6) {
        func_8023CD1C();
    }
    for (i = 0; i < 4; i++) {
        if (PLAYERS[i].unk24 == 3 || func_80243EF0(i) != 0) {
            D_802A07D4[i + 1].idx = i * 2 + 8;
        } else {
            D_802A07D4[i + 1].idx = i * 2;
        }
    }
    gfx = *gdl;
    gDPSetRenderMode(gfx++, 0x553048, 0);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFCF279);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, 1);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    for (i = 0; i < 5; i++) {
        tf = D_802A0758;
        e = tf->entries;
        if (i == 0 || PLAYERS[i - 1].unk24 != 0) {
            gDPLoadTLUT_pal256(gfx++, (u8 *) tf + e[D_802A07D4[i].idx + 1].offset);
            gDPLoadTextureBlock_4b(gfx++, (u8 *) tf + e[D_802A07D4[i].idx].offset, G_IM_FMT_CI, 16, 16, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx++, D_802A07D4[i].xl, D_802A07D4[i].yl, D_802A07D4[i].xh, D_802A07D4[i].yh, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
        }
    }
    n = 0;
    tf = D_802A075C;
    j = 0; do {
        x = D_802A079C[j];
        i = 0;
        if (D_802A07B8[j] > 0) {
            do {
                i++;
                if (j < 3 || PLAYERS[j - 3].unk24 != 0) {
                    e = tf->entries;
                    if (j >= 3 || D_802AC660.unk2C > 0) {
                        gDPLoadTLUT_pal16(gfx++, 0, (u8 *) tf + e[1].offset);
                    } else {
                        gDPLoadTLUT_pal16(gfx++, 0, (u8 *) tf + e[25].offset);
                    }
                    gDPLoadTextureTile_4b(gfx++, (u8 *) tf + e[D_802AC770[n]].offset, G_IM_FMT_CI, 10, 18, 0, 0, 9, 17, 0,
                                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    gSPTextureRectangle(gfx++, x << 2, 22 << 2, (x + 10) << 2, 40 << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
                }
                x += 10;
                n++;
            } while (i < D_802A07B8[j]);
        }
        j++;
    } while (j != 7);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    *gdl = gfx;
}

void func_80241590(s32 arg0, Gfx **gdl) {
    Gfx *gfx;
    TexFile *tf;
    TexEntry *e;
    s32 n;
    s32 x;
    s32 i;
    s32 j;

    if (D_802AC660.unk28 < 6) {
        func_8023CD1C();
    }
    gfx = *gdl;
    gDPSetRenderMode(gfx++, 0x553048, 0);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFCF279);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, 1);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    for (j = 0; j < D_802AC7C8; j++) {
        tf = D_802A0758;
        e = tf->entries;
        gDPLoadTLUT_pal256(gfx++, (u8 *) tf + e[((Rect54E40 *) D_802A084C)[j].idx + 1].offset);
        gDPLoadTextureBlock_4b(gfx++, (u8 *) tf + e[((Rect54E40 *) D_802A084C)[j].idx].offset, G_IM_FMT_CI, 16, 16, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx++, ((Rect54E40 *) D_802A084C)[j].xl, ((Rect54E40 *) D_802A084C)[j].yl, ((Rect54E40 *) D_802A084C)[j].xh, ((Rect54E40 *) D_802A084C)[j].yh, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    }
    n = 0;
    tf = D_802A075C;
    for (i = 0; i < 5; i++) {
        x = D_802A0838[i];
        j = 0;
        if (D_802A08D8[i] > 0) {
            e = tf->entries;
            do {
                if (i >= 3 || D_802AC660.unk2C > 0) {
                    gDPLoadTLUT_pal16(gfx++, 0, (u8 *) tf + e[1].offset);
                } else {
                    gDPLoadTLUT_pal16(gfx++, 0, (u8 *) tf + e[25].offset);
                }
                gDPLoadTextureTile_4b(gfx++, (u8 *) tf + e[D_802AC770[n++]].offset, G_IM_FMT_CI, 10, 18, 0, 0, 9, 17, 0,
                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, x << 2, 22 << 2, (x + 10) << 2, 40 << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
                j++;
                x += 10;
            } while (j < D_802A08D8[i]);
        }
    }
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    *gdl = gfx;
}

void func_80241550() {
    s32 sp1C;

    sp1C = func_802391F0();
    func_8023903C(0x78);
    func_8026C93C(sp1C);
    func_80239430();
}

void func_80241180() {
    f32 yaw;
    f32 pitch;
    f32 dist;
    f32 prev;
    f32 pad;
    f32 speed;
    f32 step;
    f32 diff;
    f32 k;
    f32 d;
    s32 flag;
    u8 *obj;
    s32 n;

    obj = func_802443F4(0);
    func_802350F8(1);
    func_80234F6C(1);
    func_80234858(&yaw, &pitch, &dist);
    speed = 3.0f;
    step = 30.0f;
    diff = (yaw < M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x20)) ? -(yaw - M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x20))
                                                                      : (yaw - M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x20));
    if (diff > 180.0f) {
        diff = ((yaw + 360.0f) < M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x20))
                   ? -((yaw + 360.0f) - M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x20))
                   : ((yaw + 360.0f) - M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x20));
    }
    k = dist / 30.0f;
    diff = diff / k;
    n = 180.0f / k;
    flag = func_80234DD4(yaw, pitch, dist, M2C_FIELD(obj, u8 **, 0x40));
    while (dist > 600.0f) {
        prev = yaw;
        dist -= step;
        if (dist < 900.0f) {
            step *= 0.9f;
            if (step < 1.0f) {
                step = 1.0f;
            }
        }
        if (pitch > 25.0f) {
            pitch -= 0.08f;
        }
        speed *= 0.9f;
        d = yaw - M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x20);
        if (d < 0.0f) {
            d += 360.0f;
        } else if (d >= 360.0f) {
            d -= 360.0f;
        }
        if (flag != 0) {
            yaw += n;
        } else if ((d >= 15.0f) && (d <= 180.0f)) {
            yaw -= diff;
        } else if ((d > 180.0f) && (d <= 345.0f)) {
            yaw += diff;
        }
        if (yaw < 0.0f) {
            yaw += 360.0f;
        } else if (yaw >= 360.0f) {
            yaw -= 360.0f;
        }
        if (func_80234DD4(yaw, pitch, dist, M2C_FIELD(obj, u8 **, 0x40)) != 0) {
            if (flag == 0) {
                yaw = prev;
            }
        } else {
            flag = 0;
        }
        func_80234778(yaw, pitch, dist);
        func_80239094();
    }
    D_802AC7EC = 0;
    func_80239430();
}

void func_80240F34() {
    f32 t[3];
    f32 x;
    f32 y;
    f32 z;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 speed;

    func_802350F8(1);
    func_80234F6C(1);
    func_802348B4(&x, &y, &z);
    speed = 8.0f;
    while (TRUE) {
        func_80250338(func_80243DDC(), t);
        if (t[1] < -1000.0f) {
            break;
        }
        dx = (x < t[0]) ? -(x - t[0]) : (x - t[0]);
        dy = (y < t[1]) ? -(y - t[1]) : (y - t[1]);
        dz = (z < t[2]) ? -(z - t[2]) : (z - t[2]);
        if (!(dx > 100.0f) && !(dy > 100.0f) && !(dz > 100.0f)) {
            speed *= 0.9f;
            if (speed < 1.0f) {
                speed = 1.0f;
            }
        }
        if (dx > 1.0f) {
            if (x < t[0]) {
                x += speed;
            } else {
                x -= speed;
            }
        }
        if (dy > 1.0f) {
            if (y < t[1]) {
                y += speed;
            } else {
                y -= speed;
            }
        }
        if (dz > 1.0f) {
            if (z < t[2]) {
                z += speed;
            } else {
                z -= speed;
            }
        }
        func_802346C8(x, y + 50.0f, z);
        func_80239094();
    }
    D_802AC7F0 = 0;
    func_80239430();
}

void func_8023FD08() {
    s32 h[3];
    s32 nh;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 (*v)[4];
    u8 *obj;
    s32 msg;
    void *model;
    s32 pad1;
    u8 buf[12];
    UnkStruct_8023FD08 *o;
    f32 y4;
    f32 y3;
    f32 y2;
    f32 y1;
    f32 dx;
    s32 pad2;

    D_802AC5D0 |= 0x90;
    func_80270770(0, 1);
    func_802268F4(0xB);
    func_8026C8E8();
    while (func_8023AB90() == 0) {
        func_80239094();
    }
    if (D_802AC5D0 & 2) {
        func_80239430();
    }
    D_802AC5E8 = D_802AC610.unk4;
    D_802AC5EC = D_802AC610.unk8;
    D_802AC5F0 = 0;
    func_8027F79C();
    func_80246D74(0);
    func_80245280(1);
    func_80247C50(0);
    func_802313DC(func_802443F4(0), 0x40000);
    for (i = 0, n = 0; i < 3; i++) {
        if (func_8028A36C((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + i + 0x2C) != 0) {
            n++;
        }
    }
    if (D_802AC5D0 & 0x28) {
        D_802AC80C = D_802AC610.unk2C;
        for (i = 0; i < ((D_802AC610.unk28 >= D_802AC610.unk30) ? 1 : 0) + D_802AC80C; i++) {
            func_8028A3D0((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + i + 0x2C);
        }
    } else {
        D_802AC80C = n - D_802AC610.unk20;
        if (D_802AC610.unk28 >= D_802AC610.unk30) {
            func_8028A3D0((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + 0x30);
        }
    }
    *func_8028A060(1) = D_802AC610.unk38;
    *func_8028A060(5) = D_802AC610.unk18;
    *func_8028A060(5) = D_802AC610.unk18;
    v = (s32 (*)[4]) func_8028A060(0x15);
    if ((D_802AC75C == 0) || (D_802AC610.unk30 < ((s32 *) v)[D_802AC5E8 * 4 + D_802AC5EC])) {
        ((s32 *) v)[D_802AC5E8 * 4 + D_802AC5EC] = D_802AC610.unk30;
    }
    D_802AC610.unk0 |= 8;
    func_80277484();
    func_8023903C(0x28);
    if (D_802AC5D0 & 0x28) {
        func_8026C93C(0x2D);
    } else {
        func_8026C93C(0x15);
    }
    func_80238DFC(0xD0, 0xF0, 0U);
    obj = func_802443F4(0);
    func_802362B8(0x7F);
    D_802A0038 = 0;
    if (D_802A01BC != 0) {
        D_802AC7EC = func_80238A10(func_80241180, 0, 0, 0, 0x401);
        D_802AC7F0 = func_80238A10(func_80240F34, 0, 0, 0, 0x401);
    } else {
        D_802AC7F0 = 0;
        D_802AC7EC = D_802AC7F0;
    }
    func_8023903C(0x1E);
    D_802AC610.unk0 &= ~8;
    func_802313DC(obj, 0x08000000);
    func_80231408(obj, 0x04000000);
    M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), s32 *, 0xC) &= ~0x4000;
    func_80229E38(M2C_FIELD(obj, void **, 0x40), 0x16, 0);
    func_80229E38(M2C_FIELD(obj, void **, 0x40), -1, 1);
    func_8022979C((s32) M2C_FIELD(obj, void **, 0x40), 4, 0xE);
    func_8022979C((s32) M2C_FIELD(obj, void **, 0x40), 5, 0xF);
    while (!(M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), s32 *, 0xC) & 0x40)) {
        func_80239094();
    }
    func_8023B318(D_802A0A68, 1);
    func_8023903C(0x5A);
    for (i = 0; i < 16; i++) {
        if (((s32 *) v)[i] == 0) {
            break;
        }
    }
    if ((i == 16) && (func_80295330(0) == 0)) {
        func_80294CE8(0);
        func_80295384();
    }
    i = 0;
    if ((D_802AC5E8 == 5) && (D_802AC5EC == 3) && (func_80295330(2) == 0)) {
        func_80294CE8(2);
        func_80295384();
    }
    for (j = 0; j < 0x78; j++) {
        if (func_8028A36C(j + 0x2C) != 0) {
            i++;
        }
    }
    if (i == 0x78) {
        if (func_80295330(1) == 0) {
            func_80294CE8(1);
            func_80295384();
        }
        func_8028A3D0(8);
        func_8028A3D0(0x13);
        func_8028A3D0(0x1E);
        func_8028A3D0(0x29);
        if ((D_802AC610.unk10 == 1) && (D_802AC610.unk38 < TIME_LIMIT)) {
            func_8028A3D0(0xA);
            func_8028A3D0(0x15);
            func_8028A3D0(0x20);
            func_8028A3D0(0x2B);
        }
    }
    if ((D_802AC5E8 == 5) && (D_802AC5EC == 3) && (D_802AC610.unk38 < TIME_LIMIT)) {
        func_8028A3D0(9);
        func_8028A3D0(0x14);
        func_8028A3D0(0x1F);
        func_8028A3D0(0x2A);
    }
    func_8023903C(0x1E);
    func_8023AB54(D_802A0A68, 1);
    func_8023903C(2);
    if (D_802AC5D0 & 0x28) {
        func_8023B318(D_802A0A7C, 3);
        y4 = 3.4f;
        y3 = -1.5f;
        dx = 3.82f;
        y2 = 110.0f;
        y1 = 140.0f;
    } else {
        func_8023B318(D_802A0A18, 4);
        y4 = 6.6f;
        y3 = -3.3f;
        dx = 5.725f;
        y2 = 120.0f;
        y1 = 180.0f;
    }
    func_8023B450(D_802AC610.unk28, buf, 8);
    nh = 0;
    h[nh++] = func_802811F0(buf, X_FD08_1, (u32) y1, 0.6f, 0.8f, 3);
    func_8023903C(0x1E);
    model = func_8026CE28(0x19);
    for (i = 0; i < D_802AC80C; i++) {
        func_8026C660(0x1E8);
        o = func_8022A6C4(model, 0x40);
        D_802AC7F8[i] = o;
        o->unkC |= 0x100;
        o->unk34 = D_802AC5CC;
        o->unk10 = i * dx + 6.55f;
        o->unk14 = y4;
        o->unk18 = 930.0f;
        o->unk28 = 0.03f;
        o->unk2C = 0.03f;
        o->unk30 = 0.03f;
        if (i != 0) {
            o->unk48->unk4->unk4 = D_802AC7F8[i - 1]->unk48->unk4->unk4;
        }
        func_8023903C(0x1E);
    }
    if (!(D_802AC5D0 & 0x28)) {
        func_8023B450(func_80287680(), buf, 2);
        h[nh++] = func_802811F0(buf, X_FD08_2, 0x5A, 0.8f, 0.8f, 2);
        if ((D_800BE824 == 0) && (func_8028A36C((D_802AC5E8 * 0x14) + (D_802AC5EC * 5) + 0x2F) != 0)) {
            func_8026C660(0x1E8);
            o = func_8022A6C4(model, 0x40);
            D_802AC7F8[i] = o;
            o->unkC |= 0x100;
            o->unk34 = D_802AC5CC;
            o->unk10 = 18.0f;
            o->unk14 = 1.6f;
            o->unk18 = 930.0f;
            o->unk30 = 0.03f;
            o->unk2C = 0.03f;
            o->unk28 = 0.03f;
            if (i != 0) {
                o->unk48->unk4->unk4 = D_802AC7F8[i - 1]->unk48->unk4->unk4;
            }
            i++;
            D_802AC80C++;
        }
    }
    func_8023903C(0x1E);
    func_8023B450(D_802AC610.unk30, buf, 8);
    h[nh++] = func_802811F0(buf, X_FD08_3, (u32) y2, 0.6f, 0.8f, 2);
    if (D_802AC610.unk28 >= D_802AC610.unk30) {
        func_8026C660(0x1E8);
        o = func_8022A6C4(model, 0x40);
        D_802AC7F8[i] = o;
        o->unkC |= 0x100;
        o->unk34 = D_802AC5CC;
        o->unk10 = 18.0f;
        o->unk14 = y3;
        o->unk18 = 930.0f;
        o->unk30 = 0.03f;
        o->unk2C = 0.03f;
        o->unk28 = 0.03f;
        if (D_802AC7F8 != &D_802AC7F8[i]) {
            o->unk48->unk4->unk4 = D_802AC7F8[i - 1]->unk48->unk4->unk4;
        }
        D_802AC80C++;
    }
    func_8023903C(0x3C);
    msg = func_802811F0(STR_A, func_8023B2AC(STR_A, 0.6f), 0xD2, 0.6f, 0.6f, 2);
    func_8023903C(2);
    if (func_802947AC() != 0) {
        func_80280DB4(msg);
        func_8023903C(4);
        func_8026C660(0x18);
        msg = func_802811F0(STR_B, func_8023B2AC(STR_B, 0.6f), 0xD2, 0.6f, 0.6f, 0);
        func_8023903C(0xB4);
    }
    func_8023903C(0x3C);
    if ((D_802AC5E8 == 4) && (D_802AC5EC == 3) && (func_8028A36C(0xA4) == 0)) {
        func_8026CB2C();
    }
    func_80280DB4(msg);
    func_8023903C(0x3C);
    if (D_802AC5D0 & 0x28) {
        func_8023AB54(D_802A0A7C, 3);
    } else {
        func_8023AB54(D_802A0A18, 4);
    }
    for (i = 0; i < D_802AC80C; i++) {
        func_8022A1E8(D_802AC7F8[i]);
    }
    func_8026CCBC(0x19);
    for (i = 0; i < nh; i++) {
        func_80280DB4(h[i]);
    }
    func_8023903C(2);
    for (i = 0; i < 16; i++) {
        if (((s32 *) v)[i] == 0) {
            break;
        }
    }
    for (k = 0, j = 0; k < 0x78; k++) {
        if (func_8028A36C(k + 0x2C) != 0) {
            j++;
        }
    }
    if (D_802AC75C == 0) {
        if (++D_802AC5EC >= 4) {
            D_802AC5EC = 0;
            if ((++D_802AC5E8 == 4) && (i != 16)) {
                D_802AC5E8 = 0;
            }
        }
    }
    D_802AC610.unk4 = D_802AC5E8;
    D_802AC610.unk8 = D_802AC5EC;
    func_8026C894();
    if (D_802AC7EC != 0) {
        func_80238EA8(D_802AC7EC);
    }
    if (D_802AC7F0 != 0) {
        func_80238EA8(D_802AC7F0);
    }
    if (D_802AC75C == 0) {
        if (D_802AC5E8 == 6) {
            func_8023AE6C(0x1C, 0x10, 0);
        } else if ((D_802AC5E8 == 5) && (D_802AC5EC == 0) && (j < 100)) {
            func_8023AE6C(0x1C, 0x11, 0);
        } else if ((D_802AC5E8 == 5) && (D_802AC5EC == 0) && (j == 100) && (func_8028A36C(0xA4) == 0)) {
            func_8023AE6C(0x21, 0x14, 0);
        } else if (D_802AC5EC == 0) {
            func_8023AE6C(0x21, 0x12, 0);
        } else {
            func_8023AE6C(0x21, 0x11, 0);
        }
    } else if ((D_802AC5E8 == 5) && (D_802AC5EC == 3)) {
        func_8023AE6C(0x1C, 0x10, 0);
    } else if ((D_802AC5E8 == 4) && (D_802AC5EC == 3) && (j < 100)) {
        func_8023AE6C(0x1C, 0x11, 0);
    } else if ((D_802AC5E8 == 4) && (D_802AC5EC == 3) && (j == 100) && (func_8028A36C(0xA4) == 0)) {
        D_802AC5E8 = 5;
        D_802AC610.unk4 = 5;
        D_802AC5EC = 0;
        D_802AC610.unk8 = 0;
        func_8023AE6C(0x21, 0x14, 0);
    } else {
        func_8023AE6C(0x21, 0x11, 0);
    }
    func_80239430();
}

void func_8023FC80(s32 arg0, u8 **arg1) {
    Gfx *gfx;

    gfx = *(Gfx **) arg1;
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0x80);
    gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFDF6FB);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_1000000);
    gDPSetFillColor(gfx++, 0x10001);
    gDPFillRectangle(gfx++, 0, 0, 319, 239);
    *(Gfx **) arg1 = gfx;
}

s32 func_8023FC00(u8 arg0, u16 arg1) {
    s32 temp_v0;

    temp_v0 = arg1;
    if (temp_v0 & 1) {
        func_8026C660(1);
        D_802AC810 = (s32) arg0;
        return 0;
    }
    if (temp_v0 & 6) {
        func_8026C660(2);
        D_802AC810 = -1;
        return 0;
    }
    if (temp_v0 & 0x78) {
        return 1;
    }
    return 1;
}

void func_8023FAA0() {
    s32 temp_v1_2;
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;
    s32 sp44[3];
    u8 *temp_v1_3;

    temp_v0 = (u8 *)(func_802391F0());
    M2C_FIELD(temp_v0, f32 *, 0x70) = 1.6333334f;
    M2C_FIELD(temp_v0, f32 *, 0x6C) = 16.333334f;
loop_1:
    var_v0 = (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) <= func_8026E8B8()) ? 1 : 0;
    if (var_v0 != 0) {
        func_8027F820(temp_v0);
loop_5:
        func_80239094();
        goto loop_5;
    }
    func_80291944(temp_v0, 1, 0.0f);
    temp_v1 = M2C_FIELD(temp_v0, void **, 0x40);
    func_8026DCAC(M2C_FIELD(temp_v1, f32 *, 0x10), M2C_FIELD(temp_v1, f32 *, 0x14), M2C_FIELD(temp_v1, f32 *, 0x18), sp44, 2);
    temp_v1_2 = func_8026D7D8(sp44[0], sp44[1], sp44[2]) & 0x1C00;
    if (temp_v1_2 != 0) {
        func_8027F858((s32) temp_v0, temp_v1_2 >> 0xA);
    }
    func_80230914(temp_v0);
    func_802909FC(temp_v0, func_80245150);
    temp_v1 = M2C_FIELD(temp_v0, void **, 0x40);
    M2C_FIELD(temp_v0, f32 *, 0x58) = (f32) M2C_FIELD(temp_v1, f32 *, 0x10);
    M2C_FIELD(temp_v0, f32 *, 0x5C) = (f32) M2C_FIELD(temp_v1, f32 *, 0x14);
    M2C_FIELD(temp_v0, f32 *, 0x60) = (f32) M2C_FIELD(temp_v1, f32 *, 0x18);
    func_80239094();
    goto loop_1;
}

void func_8023F26C() {
    s32 h;
    s32 k;
    s32 id;
    s32 pad1;
    u32 mode;
    s32 pad2;
    void *model;
    s32 pad3[3];
    s32 i;
    s32 task;
    u8 *obj;
    u8 *pl;
    s32 x;
    s32 y;

    D_802A0B94 = 1;
    id = *(s32 *) func_802391F0();
    func_80247C50(id);
    if ((D_802AC5D0 & 4) || ((D_802AC5D0 & 8) && (id != 0))) {
        mode = (&D_802AC858)[id];
        obj = func_802443F4(id);
        if ((D_802AC5D0 & 4) && (D_802AC660.unk0 == 0) && (func_80243EF0(id) == 0)) {
            D_802AC758--;
        }
        if ((D_802AC5D0 & 8) && (D_802AC758 == 1)) {
            func_80245208(0, 1);
        }
    } else {
        mode = D_802AC858;
        obj = func_802443F4(0);
        id = 0;
    }
    func_802313DC(obj, 0x7FFFF);
    ((s32 *) D_802AC868)[id] = mode;
    switch (mode) {
    case 3:
        if (!(D_802AC5D0 & 8) || (id == 0)) {
            func_8026C660(0x1E);
        }
        func_8027F820(obj);
        func_8023903C(0x5A);
        break;
    case 2:
        func_8024364C(obj);
        func_8023903C(0x5A);
        break;
    case 1:
        if ((D_802AC5D0 & 8) && (id != 0)) {
            func_8023EE40((s32) obj);
        } else {
            func_8023EF38(obj);
        }
        break;
    case 0:
        if ((D_802AC5D0 & 8) && (id != 0)) {
            func_8023EE40((s32) obj);
        } else {
            func_8023ECF4(obj);
        }
        break;
    case 5:
        task = func_80238A10(func_8023FAA0, (s32) obj, 0, 0, 0x130);
        func_802362B8(0x7F);
        D_802A0038 = 0;
        if (D_802A01BC != 0) {
            D_802AC7EC = func_80238A10(func_80241180, 0, 0, 0, 0x130);
            D_802AC7F0 = func_80238A10(func_80240F34, 0, 0, 0, 0x130);
        } else {
            D_802AC7F0 = 0;
            D_802AC7EC = D_802AC7F0;
        }
        func_8022979C(M2C_FIELD(obj, s32 *, 0x40), 4, 0xC);
        func_8022979C(M2C_FIELD(obj, s32 *, 0x40), 5, 0xD);
        for (i = 0; i < 20; i++) {
            f32 t = (f32) i / 20.0f;

            M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x30) = 1.0f - t;
            M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x28) = 1.0f - t;
            M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x2C) = t + 1.0f;
            func_80239094();
        }
        if (D_802AC7EC != 0) {
            func_80238EA8(D_802AC7EC);
        }
        func_80238EA8(task);
        break;
    }
    if (D_802AC5D0 & 4) {
        func_802313DC(obj, 0x0507FFFF);
        if (D_802AC660.unk0 == 0) {
            func_802313DC(obj, 0x01000000);
            func_8023903C(2);
            if ((D_802AC660.unk4[id] == 1) && (D_802AC660.unk40[id] == 1)) {
                func_80227EE0(D_802AC660.unkE8[id]);
            }
            func_8025C590(id);
            if ((D_802AC660.unk3C != 0) && (D_802AC660.unk2C > 0) && !(D_802AC5D0 & 0x10)) {
                func_80243E90(id);
                obj = func_8023EB28(id);
                model = func_80231274(-1, 0x01000000, 0xD0, NULL);
                h = func_8028A81C(0x15, 0.0f, 20.0f, 0.0f, (s32) model);
                func_80245208(id, 1);
                pl = D_800AEDF0 + id * 0xC8;
                for (k = 0; k < 60; k++) {
                    if (M2C_FIELD(pl, s32 *, 0x24) == 3) {
                        break;
                    }
                    M2C_FIELD(M2C_FIELD(model, u8 **, 0x40), f32 *, 0x10) = M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x10);
                    M2C_FIELD(M2C_FIELD(model, u8 **, 0x40), f32 *, 0x14) = M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x14);
                    M2C_FIELD(M2C_FIELD(model, u8 **, 0x40), f32 *, 0x18) = M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x18);
                    func_80239094();
                }
                if (M2C_FIELD(pl, s32 *, 0x24) != 3) {
                    func_80245208(id, 0);
                }
                func_8028A4E0(h);
                func_8022FC90(model);
            }
        } else {
            func_802313DC(obj, 0x01000000);
            func_8023903C(2);
            if ((D_802AC660.unk4[id] == 1) && (D_802AC660.unk40[id] == 1)) {
                func_80227EE0(D_802AC660.unkE8[id]);
            }
            func_8025C590(id);
            if (((D_802AC660.unk2C != 0) || (D_802AC660.unk30 != 0)) && !(D_802AC5D0 & 0x10)) {
                func_8023EB28(id);
            }
        }
    } else if (id != 0) {
        D_802AC758--;
        func_8024585C(id);
        func_80245280(1);
        func_8024585C(0);
        if ((D_802AC758 == 0) && (D_800AEE14 != 3)) {
            func_80251534(0);
            func_802313DC(func_802443F4(0), 0x40000);
            func_80247C50(0);
            func_8023E8AC();
        }
    } else if (D_802AC610.unk14 == 0) {
        func_8023E1D8();
    } else {
        if (D_802AC610.unk40 == 0) {
            func_80277DF4(2);
        }
        D_802AC5F0 = 0;
        D_802AC7CC = 0x32;
        func_8026C8E8();
        func_8026C894();
        func_802510F0();
        x = D_802AC5DC;
        y = D_802AC5E0;
        if (!(D_802AC5D0 & 1) && (D_802A01B4 == 0)) {
            D_802AC5D4 = x; D_802AC5D8 = y;
            D_802AC5DC = D_802AC5D4;
            D_802AC5E0 = D_802AC5D8;
            D_802AC5D0 |= 1;
            D_802AC5E4 = 0;
        }
    }
    D_802A0B94 = 0;
    func_80239430();
}

void func_8024364C(u8 *arg0) {
    func_802362B8(0x7F);
    if (D_802AC768 != NULL) {
        D_802AC768(arg0);
    }
}

static void func_8023EF38(u8 *arg0) {
    f64 r;
    s32 task;
    s32 i;
    u8 *temp_v0;

    func_802313DC(arg0, 0x0C000000);
    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) & ~0x4000);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), 0x14, 0);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), -1, 1);
    task = func_80238A10(func_8023FAA0, (s32) arg0, 0, 0, 0x130);
    func_802362B8(0x7F);
    D_802A0038 = 0;
    if (D_802A01BC != 0) {
        D_802AC7EC = func_80238A10(func_80241180, 0, 0, 0, 0x130);
        D_802AC7F0 = func_80238A10(func_80240F34, 0, 0, 0, 0x130);
    } else {
        D_802AC7F0 = 0;
        D_802AC7EC = D_802AC7F0;
    }
    func_8026C660(0x1E);
    func_8022979C((s32) M2C_FIELD(arg0, void **, 0x40), 4, 0xC);
    func_8022979C((s32) M2C_FIELD(arg0, void **, 0x40), 5, 0xD);
    func_8029279C(M2C_FIELD(arg0, void **, 0x40), 0, 0, 0, 0.7f);
    func_80239094();
    func_80231408(arg0, 0x04000000);
    M2C_FIELD(arg0, f32 *, 0x68) = 13.0f;
    i = 0;
    M2C_FIELD(arg0, f32 *, 0x70) = 0.40833336f;
    do {
        r = func_8025E63C();
        func_8028A81C(7, ((f32) r * 100.0f) - 50.0f, 100.0f, ((f32) func_8025E63C() * 100.0f) - 50.0f, (s32) arg0);
        func_8023903C(8);
        i++;
    } while (i < 8);
    for (i = 0; i < 8; i++) {
        r = func_8025E63C();
        func_8028A81C(0xD, ((f32) r * 50.0f) - 25.0f, 70.0f, ((f32) func_8025E63C() * 50.0f) - 25.0f, (s32) arg0);
        func_8023903C(8);
    }
    func_8023903C(0x3C);
    while (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41) && ((M2C_FIELD(arg0, f32 *, 0x68) != 0.0f) || (M2C_FIELD(arg0, f32 *, 0x6C) != 0.0f))) {
        func_80239094();
    }
    func_80238EA8(task);
    func_8023903C(0x3C);
    if (D_802AC7EC != 0) {
        func_80238EA8(D_802AC7EC);
    }
}

static void func_8023EE40(s32 arg0) {
    s32 temp_s1;
    u8 *temp_v0;

    temp_s1 = func_80238A10(func_8023FAA0, arg0, 0, 0, 0x130);
    func_802313DC((void *) arg0, 0x0C000000);
    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) & ~0x4000);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), 0x14, 0);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), -1, 1);
    if (D_802AC758 < 2) {
        func_802362B8(0x7F);
    }
    func_80231408((void *) arg0, 0x04000000);
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41)) {
        do {
            func_80239094();
        } while (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41));
    }
    func_80238EA8(temp_s1);
    func_8023903C(0x3C);
}

static void func_8023ECF4(u8 *arg0) {
    s32 temp_s1;
    u8 *temp_v0;

    func_802362B8(0x7F);
    D_802A0038 = 0;
    if (D_802A01BC != 0) {
        func_80238A10(func_80241180, 0, 0, 0, 0x130);
        func_80238A10(func_80240F34, 0, 0, 0, 0x130);
    }
    func_802313DC(arg0, 0x08000000);
    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) & ~0x4000);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), 0x13, 0);
    func_80229E38(M2C_FIELD(arg0, void **, 0x40), -1, 1);
    func_8022979C((s32) M2C_FIELD(arg0, void **, 0x40), 4, 0xC);
    func_8022979C((s32) M2C_FIELD(arg0, void **, 0x40), 5, 0xD);
    func_8026C660(0x1E);
    temp_s1 = func_80238A10(func_8023FAA0, (s32) arg0, 0, 0, 0x130);
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41)) {
        do {
            func_80239094();
        } while (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0xC) & 0x41));
    }
    func_80238EA8(temp_s1);
    func_8023903C(0x3C);
}

void func_8023ECEC() {
    if (0) {
        func_8023EB28(0);
    }

}

static void *func_8023EB28(s32 arg0) {
    u8 *obj;
    f32 pos[3];
    u8 *pl;
    s32 i;

    pl = D_800AEDF0 + arg0 * 0xC8;
    M2C_FIELD(pl, s32 *, 0x24) = (D_802AC660.unk4[arg0] == 1) ? 1 : 2;
    func_802459BC(arg0);
    M2C_FIELD(pl, s32 *, 0x18) = 0x200;
    M2C_FIELD(pl, s32 *, 0x1C) = 2;
    M2C_FIELD(pl, s32 *, 0x20) = 3;
    M2C_FIELD(pl, s32 *, 0x14) = 1;
    obj = func_802443F4(arg0);
    if (D_802AC660.unk4[arg0] == 2) {
        *(u8 **) (D_800BD000 + arg0 * 0x128) = obj;
    }
    if ((D_802AC660.unk4[arg0] == 1) && (D_802AC660.unk40[arg0] == 1)) {
        D_802AC660.unkE8[arg0] = func_802280F4(M2C_FIELD(obj, s32 *, 0x40), 0xF);
        for (i = 0; i < 4; i++) {
            func_8023A734(D_802AC660.unkE8[arg0], i, D_802AC660.unk50[arg0][i]);
        }
    }
    if (D_802AC660.unk0 == 1) {
        func_8023E8FC(pos);
        M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x10) = pos[0];
        M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x14) = pos[1] + 600.0f;
        M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x18) = pos[2];
    }
    while (func_80232D18(obj, 0x10) != 0) {
        M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), f32 *, 0x14) += 100.0f;
    }
    return obj;
}

static void func_8023E8FC(f32 *pos) {
    s32 padA[9];
    f32 x;
    f32 y;
    f32 z;
    s32 ix;
    s32 iz;
    s32 a;
    s32 b;
    struct {
        s32 unk0[4];
        f32 unk10[3];
    } s;
    s32 padB[2];

    while (TRUE) {
        x = (s32) ((f32) func_8025E63C() * (((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0 + 10][0] - ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][0])) + ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][0];
        y = ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][1];
        z = (s32) ((f32) func_8025E63C() * (((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0 + 10][2] - ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][2])) + ((f32 (*)[3]) D_802A0658)[D_802AC660.unkA0][2];
        ix = x;
        iz = z;
        a = func_8026D7D8(ix, (s32) y, iz);
        if ((D_802AC660.unkA0 == 0) || (D_802AC660.unkA0 == 6) || (D_802AC660.unkA0 == 7) ||
            (D_802AC660.unkA0 == 9)) {
            b = func_8026D7D8(ix, 0, iz);
        } else {
            b = 0;
        }
        func_8026E338(x, y, z, pos, 0);
        s.unk10[0] = pos[0];
        s.unk10[1] = pos[1];
        s.unk10[2] = pos[2];
        if (a & 0x60) {
            continue;
        }
        if (func_8026E938(&s) == 20000.0f) {
            continue;
        }
        if (((a & 0xF) != 0) && ((a & 0xF) != 1)) {
            continue;
        }
        if (b & 0x60) {
            continue;
        }
        if (((b & 0xF) != 0) && ((b & 0xF) != 1)) {
            continue;
        }
        break;
    }
}

void func_8023E8AC() {
    if (func_8023AB90() != 0) {
        func_80245280(1);
    }
    func_80238A10(func_8023FD08, 0, 0, 0, 0x130);
}

void func_8023E1D8() {
    s32 h1;
    s32 h2;
    u8 buf[28];
    s32 i;
    s32 j;
    s32 k;
    s32 sel;
    s32 keys;
    u8 *cur;
    TextItem *items;

    for (i = 0; i < 5; i++) {
        if ((&D_800BE818)[i] != 0) {
            func_8028A3D0(D_802AC5E8 * 20 + D_802AC5EC * 5 + i + 0x2C);
        } else {
            func_8028A428(D_802AC5E8 * 20 + D_802AC5EC * 5 + i + 0x2C);
        }
    }
    for (i = 0; i != 0x2C; i++) {
        if (((s32 *) D_800BE830)[i / 8] & (1 << (i % 8))) {
            func_8028A3D0(i);
        } else {
            func_8028A428(i);
        }
    }
    func_8026C8E8();
    D_802AC5F0 = 0;
    func_8023B318(D_802A0AB8, 1);
    if (D_802AC628 == 0) {
        func_8023903C(0xB4);
        func_8023AB4C(D_802A0AB8, 1);
        func_8023AE6C(0x20, 0x11, 0);
    } else {
        func_8023903C(0xB4);
        items = D_802A0AB8;
        sel = 1;
        for (i = 0; i < sel; i++) {
            func_80280DB4(items[i].handle);
        }
        func_8023903C(2);
        func_8023B450(D_802AC610.unk18, buf, 2);
        func_8023B318(D_802A0ACC, 4);
        h1 = func_802811F0(buf, 0xBEU, 0xA0U, 0.6f, 0.6f, 2U);
        func_8023B450(9, buf, 1);
        h2 = func_802811F0(buf, 0xD6U, 0x50U, 0.8f, 0.8f, 2U);
        cur = func_8026CE28(0x130);
        cur = func_8022A6C4(cur, 0x40);
        M2C_FIELD(cur, f32 *, 0x10) = 123.0f;
        M2C_FIELD(cur, f32 *, 0x14) = 108.0f;
        M2C_FIELD(cur, f32 *, 0x18) = 137.0f;
        M2C_FIELD(cur, f32 *, 0x1C) = 122.0f;
        func_8026C93C(0x26);
        i = 0;
        k = 9;
        sel = 0;
        while (TRUE) {
            keys = func_8027EFA8();
            if ((keys & 0x800) && (sel == 1)) {
                sel = 0;
                M2C_FIELD(cur, f32 *, 0x14) = 108.0f;
                M2C_FIELD(cur, f32 *, 0x1C) = 122.0f;
            } else if ((keys & 0x400) && (sel == 0)) {
                sel = 1;
                M2C_FIELD(cur, f32 *, 0x14) = 126.0f;
                M2C_FIELD(cur, f32 *, 0x1C) = 140.0f;
            } else if (func_802399AC(0) & 0x8000) {
                do {} while (0);
                func_8026C660(1);
                if (sel == 0) {
                    D_802AC810 = 1;
                } else {
                    D_802AC810 = -1;
                }
                break;
            } else if (func_802399AC(0) & 0x4000) {
                do {} while (0);
                D_802AC810 = -1;
                break;
            }
            i++;
            if (i >= FPS) {
                k--;
                i = 0;
                if (k < 0) {
                    D_802AC810 = -1;
                    break;
                }
                func_80280DB4(h2);
                func_8023B450(k, buf, 1);
                h2 = func_802811F0(buf, 0xD6U, 0x50U, 0.8f, 0.8f, 2U);
                func_8026C660(0x37);
            }
            func_80239094();
        }
        func_8022A1E8(cur);
        func_8026CCBC(0x130);
        if (D_802AC810 == 1) {
            func_80280DB4(h1);
            func_8023903C(2);
            func_8023B450(--D_802AC610.unk18, buf, 2);
            h1 = func_802811F0(buf, 0xBEU, 0xA0U, 0.6f, 0.6f, 2U);
            func_8023903C(0x3C);
            D_800AEE04 = 1;
            D_802AC624 = 2;
            D_802AC5D0 &= ~2;
            func_8023AE6C(0x21, 0x11, 0);
        } else {
            func_8023903C(0x3C);
            func_8023AE6C(0x20, 0x11, 0);
        }
        items = D_802A0ACC;
        keys = 4;
        for (j = 0; j < keys; j++) {
            func_80280DB4(items[j].handle);
        }
        func_80280DB4(h1);
        func_80280DB4(h2);
    }
    D_802AC7CC = 0x3C;
    func_8026C8E8();
    func_8026C894();
    func_8023903C(2);
}

void func_8023DB0C() {
    s32 i;
    s32 j;
    s32 a;
    s32 t;

    D_802AC5E8 = 0;
    D_802AC5EC = 0;
    D_802AC5F0 = 0;
    D_802AC610.unk0 = 0;
    D_802AC610.unk4 = 0;
    D_802AC610.unk8 = 0;
    D_802AC610.unkC = 0;
    D_802AC610.unk38 = *func_8028A060(1);
    switch (*func_8028A060(3)) {
        case 0:
            D_802AC610.unk10 = 0;
            break;
        case 1:
            D_802AC610.unk10 = 1;
            break;
    }
    D_802AC610.unk14 = 2;
    D_802AC610.unk18 = 3;
    D_802AC610.unk1C = 0;
    D_802AC610.unk2C = 0;
    func_8028A0B4();
    if (D_802AC610.unk40 != 0) {
        PLAYERS[0].unk18 |= 0x200;
        PLAYERS[0].unk18 |= 3;
        func_80278E84(0, 8);
        func_80277AF8(0, 8);
    } else {
#line 2196
        func_80277E1C();
#line 2189
    }
    D_802AC610.unk0 |= 1;
    D_802AC660.unk0 = 0;
#line 2195
    PLAYERS[0].unk14 = 1;
#line 2193
    do {} while (0);
    for (i = 0; i < 4; i++) {
        D_802AC660.unk4[i] = 1;
        D_802AC660.unk40[i] = 0;
        D_802AC660.unk90[i] = 0;
        D_802AC660.unkA4[i] = 0;
        D_802AC660.unk14[i] = 1;
        for (j = 0; j < 4; j++) {
            D_802AC660.unk50[i][j] = 0;
        }
    }
    D_802AC660.unk24 = 3;
    D_802AC660.unk28 = 2;
    D_802AC660.unk2C = 2;
    D_802AC660.unk30 = 0;
    D_802AC660.unk34 = FPS;
    D_802AC660.unk38 = 1;
    D_802AC660.unk3C = 1;
    D_802AC660.unkA0 = 0;
#line 2203
    D_802AC5D4 = 0x14;
#line 2213
    D_802AC5D8 = 0x10;
    func_802268F4(2);
    func_802268F4(0x10);
    func_802268F4(4);
    func_802268F4(5);
    D_802A01B8 = 0;
    while (TRUE) {
        if (D_802AC5D0 & 1) {
            D_802A01B8 = 0;
            func_802268F4(0xC);
            if (!(D_802AC5E4 & 1)) {
                if (D_802AC5E4 & 4) {
                    a = 0xFF;
                } else {
                    a = 0;
                }
                func_80281A88(a, a, a, D_802AC7CC);
                func_80281A40();
            }
            if (D_802A01C0 != 0) {
                func_802350F8(1);
                func_80234F6C(1);
                func_80234778(D_802AC5F8, D_802AC5FC, D_802AC600);
                D_802A01C0 = 0;
            }
            func_8026BF68(0);
            func_8029236C();
            func_802923CC();
            func_802268F4(1);
            func_8027F79C();
            func_8023D8A0();
            func_80239094();
            func_8026BF28(0x7F);
            func_8026BF90(0x7F);
            func_8023D0F8();
            func_8022691C(D_802AC5D4);
            func_802268F4(2);
            func_802268F4(D_802AC5D8);
            func_802268F4(4);
            func_8023ADD4(1);
            func_80229280(0);
            func_8023CA94();
            if (!(D_802AC5E4 & 2)) {
                if (D_802AC5E4 & 4) {
                    j = 0xFF;
                } else {
                    j = 0;
                }
                func_80281AE0(j, j, j, D_802AC7CC);
                func_80281A40();
            }
            D_802AC7CC = 0x20;
            func_802268F4(5);
            D_802AC5D0 &= ~1;
            func_8023C374();
            func_8023ADD4(0);
            if ((D_802AC5D4 >= 0x28) && !(D_802AC610.unk0 & 6)) {
                D_802A01B8 = 1;
            }
            func_8023A640();
        } else if (!(D_802AC5D0 & 0x10) && !(D_802AC5D0 & 2)) {
            if (!(D_802AC5D0 & 0x40) && !(D_802AC5D0 & 0x80)) {
                if ((D_802AC5D0 & 4) && (D_802AC660.unk28 < 6)) {
                    if (--D_802AC660.unk34 <= 0) {
                        D_802AC660.unk34 = FPS;
                        if (--D_802AC660.unk30 < 0) {
                            D_802AC660.unk30 = 0x3B;
                            if (--D_802AC660.unk2C == 0) {
                                func_80238A10(func_802434F8, 0, 0, 0, 0x130);
                            }
                        } else if ((D_802AC660.unk30 == 0) && (D_802AC660.unk2C == 0)) {
                            func_8023C170();
                        }
                    }
                } else {
                    D_802AC610.unk34 += FRAME_STEP;
                    if (D_802AC610.unk34 >= 1.0f) {
                        t = D_802AC610.unk34;
                        D_802AC610.unk30 += t;
                        D_802AC610.unk34 -= t;
                    }
                    D_802AC5F4 += FRAME_STEP;
                    if (D_802AC5F4 >= 100.0f) {
                        D_802AC610.unk38++;
                        D_802AC5F4 -= (s32) D_802AC5F4;
                    }
                    if (D_802AC610.unk30 >= 100000000) {
                        D_802AC610.unk30 = 99999999;
                    }
                    if (D_802AC610.unk38 >= 0x57E40) {
                        D_802AC610.unk38 = 0x57E3F;
                    }
                }
            }
            for (i = 0; i < 10; i++) {
                if (D_802AC7A0[D_802AC608] != -1) {
                    func_802268F4(D_802AC7A0[D_802AC608]);
                    D_802AC7A0[D_802AC608] = -1;
                }
                if (++D_802AC608 >= 10) {
                    D_802AC608 = 0;
                }
            }
            func_802268F4(3);
            func_8023BBCC();
        }
        func_8023903C(1);
    }
}

void func_8023DA04(s32 arg0) {
    s32 temp_v1;

    if (0) {
        func_8023D9FC();
        func_8023D8A0();
    }
    D_802AC5E8 = 0;
    D_802AC5EC = 0;
    D_802AC5F0 = 0;
    D_802AC610.unk0 = 0;
    D_802AC610.unk4 = 0;
    D_802AC610.unk8 = 0;
    D_802AC610.unkC = 0;
    D_802AC610.unk38 = (s32) *func_8028A060(1);
    temp_v1 = *func_8028A060(3);
    switch (temp_v1) {
    case 0:
        D_802AC610.unk10 = 0;
        break;
    case 1:
        D_802AC610.unk10 = 1;
        break;
    }
    D_802AC610.unk14 = 2;
    D_802AC610.unk18 = 3;
    D_802AC610.unk1C = 0;
    D_802AC610.unk2C = 0;
    func_8028A0B4();
    if (D_802AC610.unk40 != 0) {
        PLAYERS[0].unk18 |= 0x200;
        PLAYERS[0].unk18 |= 3;
        func_80278E84(0, 8);
        func_80277AF8(0, 8);
    } else {
        func_80277E1C();
    }
    PLAYERS[0].unk14 = 1;
}

static void func_8023D9FC(void) {
}

static void func_8023D8A0() {
    s32 var_s0;

    func_8026C394();
    func_8026CF90();
    func_80243A30();
    func_8028A584();
    func_8027BBC4();
    func_8027783C();
    func_8028E8E0();
    func_80286E60();
    func_80286F04();
    func_802822B0(3);
    func_8027EBCC();
    func_80227F88();
    var_s0 = 0;
    do {
        func_80247C50(var_s0);
        var_s0 += 1;
    } while (var_s0 != 4);
    func_80245868();
    func_8026F02C();
    func_8027FC08();
    func_8028785C();
    func_80238F40(0x110, 0x3CF);
    func_8022FDE8();
    func_8023D848();
    func_802514CC();
    func_8026D5B4(0);
    func_80236B7C();
    if (D_802A0758 != NULL) {
        func_8026CCBC(0x130);
        D_802A0758 = NULL;
    }
    if (D_802A075C != NULL) {
        func_8026CCBC(0x131);
        D_802A075C = NULL;
    }
    if (D_802A0760 != NULL) {
        func_8022A1E8(D_802A0760);
        D_802A0760 = NULL;
    }
    func_8026CB2C();
}

void func_8023D848() {
    func_80227C18();
    func_80227870();
    func_802276FC(1);
    func_802276E0(0, 0, 0);
    D_802AC768 = NULL;
    D_802AC798 = 0;
    D_802A01BC = 1;
    if (0) {
        func_8023D840();
        func_8023D0F8();
    }
}

static void func_8023D840(void) {
}

static s32 func_8023D0F8() {
    f32 a;
    s32 i;
    f32 yaw;
    s32 k;
    s32 skip;
    Player54E40 *pl;
    s32 pad;

    if (0) {
        func_8023D0F0();
    }
    if ((D_802AC5D0 & 2) && (D_802AC610.unk14 != 0)) {
        D_802AC610.unk14--;
        PLAYERS[0].unk14 = 1;
        skip = 1;
        D_802AC7CC = 0x20;
    } else {
        skip = 0;
    }
    D_802AC5D0 &= ~0x6E;
    do {} while (0);
    D_800AEE14 = 0;
    D_800AEE58 = 0;
    D_800AEEDC = 0;
    D_800AEF20 = 0;
    D_800AEFA4 = 0;
    D_800AEFE8 = 0;
    D_800AF06C = 0;
    D_800AF0B0 = 0;
    PLAYERS[0].unk24 = 1;
    M2C_FIELD(D_800AEDF0, s32 *, 0x344) = 0;
    func_80234858(&yaw, NULL, NULL);
    a = (s32) (yaw / 45.0f) * 45;
    func_80234778((a >= 360.0f) ? a - 360.0f : ((a < 0.0f) ? a + 360.0f : a), 32768.0f, 32768.0f);
    if (D_802AC5F0 == 0) {
        func_80236218(1);
        D_802A0038 = 0;
    }
    D_802AC758 = 0;
    for (k = 0; k < 6; k++) {
        D_802AC5E8 = k;
        if (D_802AC5D4 == ((s32 (*)[4]) D_802A04C8)[k][1]) {
            D_802AC5EC = 1;
        } else if (D_802AC5D4 == ((s32 (*)[4]) D_802A04C8)[k][3]) {
            D_802AC5EC = 3;
        } else if ((D_802AC5D4 >= ((s32 (*)[4]) D_802A04C8)[k][0]) && (D_802AC5D4 < ((s32 (*)[4]) D_802A04C8)[k][2])) {
            D_802AC5EC = 0;
        } else if ((D_802AC5D4 >= ((s32 (*)[4]) D_802A04C8)[k][2]) && (D_802AC5D4 < ((s32 (*)[4]) D_802A04C8)[k][1]) && (D_802AC5D4 < ((s32 (*)[4]) D_802A04C8)[k][3])) {
            D_802AC5EC = 2;
        } else {
            continue;
        }
        if ((D_802AC5EC == 0) || (D_802AC5EC == 2)) {
            D_802AC610.unkC = D_802AC5D4 - ((s32 (*)[4]) D_802A04C8)[D_802AC5E8][D_802AC5EC];
        } else {
            D_802AC610.unkC = 0;
        }
        if ((D_802AC610.unk4 == 1) && (D_802AC610.unk8 == 2) && (D_802AC5D4 == 0x3B)) {
            D_802AC5EC = 2;
            D_802AC610.unkC = 2;
        }
        D_802AC610.unk4 = D_802AC5E8;
        D_802AC610.unk8 = D_802AC5EC;
        if ((D_802AC5F0 == 0) && (skip == 0)) {
            for (i = 0, D_802AC610.unk20 = 0; i < 5; i++) {
                if (((&D_800BE818)[i] = func_8028A36C(D_802AC5E8 * 20 + D_802AC5EC * 5 + i + 0x2C)) != 0) {
                    if (i < 3) {
                        D_802AC610.unk20++;
                    }
                } else {
                    (&D_800BE818)[i] = 0;
                }
            }
            for (i = 0; i < 0x2C; i++) {
                if (func_8028A36C(i) != 0) {
                    ((s32 *) D_800BE830)[i / 8] |= 1 << (i % 8);
                } else {
                    ((s32 *) D_800BE830)[i / 8] &= ~(1 << (i % 8));
                }
            }
            D_802AC5F4 = 0.0f;
            D_802AC610.unk34 = 0.0f;
            D_802AC610.unk38 = *func_8028A060(1);
        }
        if ((D_802AC5E8 == 4) || (D_802AC5E8 == 5)) {
            if (D_802AC5EC == 3) {
                D_802AC5D0 |= 8;
            } else if (D_802AC5EC == 1) {
                D_802AC5D0 |= 0x20;
            }
        } else if (D_802AC5EC == 1) {
            D_802AC5D0 |= 8;
        } else if (D_802AC5EC == 3) {
            D_802AC5D0 |= 0x20;
        }
        if (D_802AC5D0 & 0x28) {
            D_802AC610.unk30 = 0;
            D_802AC610.unk2C = 0;
        }
        if (!(D_802AC610.unk0 & 6)) {
            D_802A0758 = func_8026CE28(0x130);
            D_802A075C = func_8026CE28(0x131);
            D_802A0760 = func_8022A328(func_80242270, 0x3F, 1, 0, 0);
            M2C_FIELD(D_802A0760, s32 *, 0xC) |= 0x210;
        }
        if (D_802AC5D0 & 0x20) {
            func_8026C6D0(1);
            func_8026BF68(M2C_FIELD(&((s32 *) D_802A0654)[D_802AC5E8], s8 *, 3));
        } else {
            func_8026C6D0(0);
            func_8026BF68(((s8 (**)[4]) D_802A063C)[D_802AC5E8][D_802AC5D4 - ((s32 (*)[4]) D_802A04C8)[D_802AC5E8][0]][3]);
        }
        return 0;
    }
    if ((D_802AC5D4 >= 0x90) && (D_802AC5D4 < 0x9A)) {
        func_8028A0B4();
        D_802AC610.unk10 = 0;
        func_8023CECC();
        D_802AC610.unk4 = 9;
        D_802AC610.unk8 = 0;
        D_802AC610.unkC = D_802AC5D4 - 0x90;
        D_802AC5D0 |= 4;
        for (i = 0; i < 4; i++) {
            pl = &PLAYERS[i];
            if (D_802AC660.unk4[i] == 0) {
                pl->unk24 = 0;
            } else {
                D_802AC758++;
                if (D_802AC660.unk4[i] == 1) {
                    pl->unk24 = 1;
                } else {
                    pl->unk24 = 2;
                }
            }
        }
        func_8026C6D0(0);
        func_8026BF68(4);
        return 1;
    }
    func_8026BF68(0);
    return -1;
}

static void func_8023D0F0(void) {
}

static void func_8023CECC() {
    Rect54E40 *r;
    s32 n;
    s32 i;
    s32 x;

    D_802A0758 = func_8026CE28(0x130);
    D_802A075C = func_8026CE28(0x131);
    if (D_802AC660.unk0 == 0) {
        D_802A0760 = func_8022A328(func_80241BB0, 0x3F, 1, 0, 0);
        func_8023CD1C();
        func_8023CC54(4);
    } else {
        func_8023CD1C();
        func_8023CC54(2);
        for (n = 0, i = 0; i < 4; i++) {
            if ((D_802AC660.unk4[i] != 0) && (D_802AC660.unk90[i] == 0)) {
                n++;
            }
        }
        r = (Rect54E40 *) D_802A0888; i = 3; x = 0x84; do {
            r->xl = x << 2;
            r->xh = (x + 0x10) << 2;
            x += 0x12;
            if ((n + 2) == i) {
                D_802A0838[3] = x + 4;
                x += 0x3A;
            }
            i++;
            r++;
        } while (i < 7);
        ((Rect54E40 *) D_802A084C)[2].xl = (n * 0x12 + 0xAC) << 2;
        ((Rect54E40 *) D_802A084C)[2].xh = (n * 0x12 + 0xBC) << 2;
        x = n + 3;
        n = 3;
        for (i = 0; i < 4; i++) {
            if (D_802AC660.unk4[i] != 0) {
                if (D_802AC660.unk90[i] == 0) {
                    ((Rect54E40 *) D_802A084C)[n++].idx = i * 2;
                } else {
                    ((Rect54E40 *) D_802A084C)[x++].idx = i * 2;
                }
            }
        }
        D_802A0838[4] = x * 0x12 + 0x8C;
        D_802AC7C8 = x;
        D_802A0760 = func_8022A328(func_80241590, 0x3F, 1, 0, 0);
    }
    M2C_FIELD(D_802A0760, s32 *, 0xC) |= 0x210;
}

static void func_8023CD1C() {
    s32 n;
    s32 i;
    s32 v;
    s32 d;
    s32 t;

    n = 0;
    if (D_802AC660.unk28 < 6) {
        v = D_802AC660.unk2C;
        d = 1;
        for (i = 0; i < 1; i++) {
            D_802AC770[n++] = v / d * 2;
            t = v / d * d;
            if (v >= t) {
                v -= t;
            }
            d /= 10;
        }
        D_802AC770[n++] = 0x14;
        v = D_802AC660.unk30;
        d = 10;
        for (i = 0; i < 2; i++) {
            D_802AC770[n++] = v / d * 2;
            t = v / d * d;
            if (v >= t) {
                v -= t;
            }
            d /= 10;
        }
    } else {
        D_802AC770[n++] = 0x16; D_802AC770[n++] = 0x14;
        D_802AC770[n++] = 0x16;
        D_802AC770[n++] = 0x16;
    }
}

void func_8023CC54(s32 arg0) {
    s32 i;
    s32 j;
    s32 v;
    s32 div;
    s32 k;
    s32 t;

    if (0) {
        func_8023CC4C();
        func_8023CA94();
    }
    k = 0;
    for (i = 0; i < arg0; i++) {
        v = D_802AC660.unkA4[i];
        div = 1;
        for (j = 0; j < 1; j++) {
            ((s32 *) D_802AC780)[k++] = v / div * 2;
            t = v / div * div;
            if (v >= t) {
                v -= t;
            }
            div /= 10;
        }
    }
}

static void func_8023CC4C(void) {
}

static void func_8023CA94() {
    s32 i;
    s32 j;
    s32 v;
    s32 *q;

    if (D_802AC5D0 & 4) {
        D_802AC660.unk2C = D_802AC660.unk28;
        D_802AC660.unk30 = 0;
        D_802AC660.unk34 = FPS;
        func_80277E1C();
        for (i = 0; i < 4; i++) {
            PLAYERS[i].unk20 = 3;
            PLAYERS[i].unk14 = 1;
            PLAYERS[i].unk98 = 3;
            PLAYERS[i].unk94 = PLAYERS[i].unk18;
            D_802AC660.unkB4[i] &= ~2;
            if (D_802AC660.unk4[i] == 2) {
                func_80251804(i);
                D_802AC660.unkB4[i] |= 8;
            } else if ((D_802AC660.unk4[i] == 1) && (D_802AC660.unk40[i] == 1)) {
                D_802AC660.unkE8[i] = func_802280F4(M2C_FIELD(func_802443F4(i), s32 *, 0x40), 0xF);
                q = D_802AC660.unk50[i];
                for (j = 0; j < 4; j++) {
                    func_8023A734(D_802AC660.unkE8[i], j, q[j]);
                }
            }
        }
        if (D_802AC660.unk0 == 1) {
            D_802AC610.unk10 = 0;
            (&D_802AC760)[0] = (&D_802AC760)[1] = 1;
            ((s32 *) D_802AC820)[0] = ((s32 *) D_802AC820)[1] = 0;
            func_80238A10(func_80242FB4, 1, 0, 0, 0x130);
            func_80238A10(func_80242FB4, 2, 0, 0, 0x130);
        }
        func_80238A10(func_80242DA8, 0, 0, 0, 0x130);
    }
}

void func_8023C374() {
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 pad;
    u8 *temp_a0;

    if (0) {
        func_8023C170();
    }
    if ((D_802AC5F0 != 0) || (D_802AC5D4 < 0x28) || (D_802AC610.unk0 & 6)) {
        D_802AC5D0 &= ~0x10;
        return;
    }
    if (D_802AC5D0 & 4) {
        func_8026C93C(0x1B);
        func_8026C660(0x1E4);
        sp68 = func_802811F0(D_802A01D8, X_01D8, 0x6EU, 0.8f, 0.8f, 0U);
        func_8023903C(0x2B);
        sp64 = func_802811F0(D_802A01E0, X_01E0, 0x6EU, 0.8f, 0.8f, 4U);
        func_80280DB4(sp68);
        func_8023903C(0x23);
        func_80280DB4(sp64);
        func_8023903C(3);
        D_802AC5D0 &= ~0x90;
        return;
    }
    if (!(D_802AC5D0 & 0x28)) {
        func_8026C93C(0x18);
    }
    func_8023903C(0x1E);
    D_802AC5F0 = 1;
    D_802A01C4[6] = (s8) (D_802AC5EC + 0x11);
    sp6C = func_802811F0(D_802A01C4, func_8023B2AC(D_802A01C4, 0.8f), 0x3CU, 0.8f, 0.8f, 0U);
    sp68 = func_802811F0(D_802A01D0, func_8023B2AC(D_802A01D0, 0.8f), 0x5AU, 0.8f, 0.8f, 0U);
    temp_a0 = ((u8 **) D_802A08F8)[D_802AC5E8 * 4 + D_802AC5EC];
    sp60 = func_802811F0(temp_a0, func_8023B2AC(temp_a0, 0.6f), 0x78U, 0.6f, 0.8f, 0U);
    func_8023AF5C(163.0f, 150.0f);
    if (D_802AC610.unk10 == 0) {
        D_802AC610.unk28 = D_802A0958[D_802AC5E8][D_802AC5EC];
    } else {
        D_802AC610.unk28 = D_802A09B8[D_802AC5E8][D_802AC5EC];
    }
    func_8023B7C0(180.0f);
    func_8023903C(0xB4);
    func_80280DB4(sp6C);
    func_80280DB4(sp68);
    func_80280DB4(sp60);
    func_80280DB4(D_802AC7E4);
    func_80280DB4(D_802AC7E8);
    func_8023AAE4();
    D_802AC75C = func_8028A060(0x15)[D_802AC5E8 * 4 + D_802AC5EC];
    func_8023903C(2);
    if (D_802AC5D0 & 8) {
        if (D_802AC5E8 == 0) {
            func_8026C93C(0xE);
        } else if (D_802AC5E8 == 4) {
            if ((D_802AC5D8 == 0x10) || (D_802AC5D8 == 0x11)) {
                func_8026C93C(0xC);
            } else if ((D_802AC5D8 == 0x12) || (D_802AC5D8 == 0x13)) {
                func_8026C93C(0xD);
            }
        } else if (D_802AC5E8 == 5) {
            if ((D_802AC5D8 == 0x10) || (D_802AC5D8 == 0x11)) {
                func_8026C93C(0xF);
            } else if ((D_802AC5D8 == 0x12) || (D_802AC5D8 == 0x13)) {
                func_8026C93C(0x10);
            }
        } else {
            func_8026C93C(0xB);
        }
    } else if (!(D_802AC5D0 & 0x20)) {
        if ((D_802AC5E8 == 0) && (D_802AC5EC == 0) && (D_802AC75C == 0) && (D_802AC610.unk30 == 0) && (D_802AC610.unk10 == 0)) {
            func_80238A10(func_80241550, D_802AC5E8 + 3, 0, 0, 9);
        } else {
            func_8026C93C(D_802AC5E8 + 3);
        }
    }
    D_802AC5D0 &= ~0x90;
}

static void func_8023C170() {
    s32 i;
    UnkStruct_8023FD08 *o;

    if (D_802AC660.unk0 == 0) {
        if (D_802AC758 < 2) {
            return;
        }
    } else if (((&D_802AC760)[0] != 1) || ((&D_802AC760)[1] != 1)) {
        return;
    }
    D_802AC854 = 1;
    func_802510F0();
    func_8026C660(0x1E7);
    func_8026C93C(0x2E);
    for (i = 0; i < 4; i++) {
        if ((PLAYERS[i].unk24 != 3) && (PLAYERS[i].unk24 != 0)) {
            func_8024585C(i);
            func_80247C50(i);
            func_802452E8(1);
        }
    }
    func_80238DFC(0xD0, 0xD0, 0U);
    func_8024585C(0);
    func_8023903C(0x3C);
    func_8026C660(0x1E1);
    o = func_8022A6C4(func_8026CE28(0x3F), 0);
    o->unkC |= 0x100;
    o->unk34 = D_802AC5CC;
    o->unk10 = 0.0f;
    o->unk14 = 0.0f;
    o->unk18 = 0.0f;
    o->unk28 = 0.1f;
    o->unk2C = 0.1f;
    o->unk30 = 0.1f;
    i = 0;
    do {
        o->unk18 = i * 11.111111f;
        func_80239094();
        i++;
    } while (i != 0x5A);
    func_8022A1E8(o);
    func_8026CCBC(0x3F);
    func_8026C8E8();
    func_8026C894();
    func_8023AE6C(D_802AC5D4, D_802AC5D8, 0);
}

s32 func_8023BBCC() {
    s32 pad[6];
    s32 i;
    s32 var_v0;

    if ((D_802A0B80 != 0) || (D_802A01B8 == 0)) {
        return 1;
    }
    if (D_802AC5D0 & 4) {
        var_v0 = func_8023AEDC(1);
    } else {
        var_v0 = func_8023AEDC(0);
    }
    if (!(var_v0 & 0x1000)) {
        return 1;
    }
    func_8026C660(0x2F);
    D_802A0B80 = 1;
    func_8023AA78(1);
    func_80239094();
    if (func_802362A8() & 0xF) {
        func_80238CF8(0x401, 0x401);
        func_80238CF8(0x90, 0x90);
        func_80238CF8(0x170, 0x170);
    }
    D_802AC818 = func_8022A328(func_8023FC80, 0x9D, 1, 0, 0);
    M2C_FIELD(D_802AC818, s32 *, 0xC) |= 0x80;
    func_8023B8D0();
    func_8026BF90(0x40);
    if (D_802AC5D0 & 0x2C) {
        while (!(func_8023AEDC((D_802AC5D0 & 4) ? 1 : 0) & 0x1000)) {
            func_80239094();
        }
        func_8026C660(2);
        func_8026BF90(0x7F);
        func_8023AC38();
        func_8022A1E8(D_802AC818);
        func_8023903C(2);
        func_8023AA78(0);
    } else {
        func_802443F4(func_80243DDC());
        if ((D_802AC75C == 0) || (func_8023AB90() == 0)) {
            while (!(func_8023AEDC(0) & 0x1000)) {
                func_80239094();
            }
            func_8026C660(2);
            func_8026BF90(0x7F);
            func_8023AC38();
            func_8022A1E8(D_802AC818);
            func_8023903C(2);
            func_8023AA78(0);
        } else {
            func_8027F658(func_8023FC00, D_802A0B84, 0x130U, 0xEU, 0xEU);
            func_8027F400();
            func_8027F428();
            if (D_802AC810 == 2) {
                func_8023903C(0x3C);
                func_8023AA78(0);
                D_802A01B8 = 0;
                D_802AC7CC = 0x3C;
                func_8026C8E8();
                func_8026C894();
                for (i = 0; i < 5; i++) {
                    if ((&D_800BE818)[i] != 0) {
                        func_8028A3D0(D_802AC5E8 * 20 + D_802AC5EC * 5 + i + 0x2C);
                    } else {
                        func_8028A428(D_802AC5E8 * 20 + D_802AC5EC * 5 + i + 0x2C);
                    }
                }
                for (i = 0; i < 0x2C; i++) {
                    if (((s32 *) D_800BE830)[i / 8] & (1 << (i % 8))) {
                        func_8028A3D0(i);
                    } else {
                        func_8028A428(i);
                    }
                }
                *func_8028A060(1) = D_802AC610.unk38;
                func_8023AE6C(0x21, 0x11, 0);
                func_8023ADD4(1);
                func_80229280(1);
                D_802AC5F0 = 0;
                func_8023AC38();
                func_8022A1E8(D_802AC818);
                D_802AC5D0 |= 0x80;
            } else {
                func_8026BF90(0x7F);
                func_8023AC38();
                func_8022A1E8(D_802AC818);
                func_8023903C(2);
                func_8023AA78(0);
            }
        }
    }
    D_802A0B80 = 0;
    return 0;
}

static void func_8023B8D0() {
    s32 i;
    s32 model;
    UnkStruct_8023FD08 *o;
    u8 buf[4];

    if (!(D_802AC5D0 & 4)) {
        D_802A0B1C[0].str = (*D_802A08F8)[D_802AC5E8 * 4 + D_802AC5EC];
    } else {
        D_802A0B1C[0].str = D_802A0448;
    }
    if (D_802AC5D0 & 0x2C) {
        func_8023B318(D_802A0B1C, 1);
        if (!(D_802AC5D0 & 4)) {
            func_8023B7C0(154.0f);
        }
    } else {
        func_8023B450(func_80287680(), buf, 2);
        D_802AC814 = func_802811F0(buf, 0xDC, 0x50, 0.6f, 0.6f, 2);
        model = (s32)(func_8026CE28(0x19));
        for (i = 0; i < 5; i++) {
            o = D_802AC7F8[i] = func_8022A6C4((void *) model, 0x40);
            if ((func_8028A36C(D_802AC5E8 * 20 + D_802AC5EC * 5 + i + 0x2C) != 0) || ((i == 3) && ((&D_800BE818)[i] != 0))) {
                o->unkC |= 0x100;
            } else {
                o->unkC |= 0x1180;
                o->unk36 = 0x64;
            }
            o->unk34 = D_802AC5CC;
            o->unk10 = i * 5.8f + 0.65f;
            o->unk14 = 9.95f;
            o->unk18 = 900.3f;
            o->unk28 = 0.05f;
            o->unk2C = 0.05f;
            o->unk30 = 0.05f;
        }
        func_8023B7C0(154.0f);
        if ((D_802AC75C == 0) || (func_8023AB90() == 0)) {
            func_8023B318(D_802A0B1C, 3);
            func_802814D8(D_802A0B40, 0xFFE8, 0);
        } else {
            func_8023B318(D_802A0B1C, 5);
            func_802814D8(D_802A0B40, 0xFFE8, 0);
        }
    }
    if (!(D_802AC5D0 & 4)) {
        func_8023AF5C(160.0f, 125.0f);
    }
}

static void func_8023B7C0(f32 arg0) {
    u8 buf[12];

    func_8023B450(D_802AC610.unk28, buf, 8);
    D_802AC7E4 = func_802811F0(&D_802A039C, 0x2D, (u32) arg0, 0.6f, 0.8f, 2);
    D_802AC7E8 = func_802811F0(buf, X_B7C0, (u32) arg0, 0.6f, 0.8f, 3);
}

static void func_8023B450(s32 value, u8 *buf, s32 n) {
    s32 i;
    s32 div;
    s32 j;
    s32 t;

    for (i = 0, div = 1; i < n - 1; i++) {
        div *= 10;
    }
    j = 0;
    for (i = 0; i < n; i++) {
        buf[j++] = value / div + 0x10;
        t = value / div * div;
        if (value >= t) {
            value -= t;
        }
        div /= 10;
    }
    buf[j] = 0;
}

static void func_8023B318(TextItem *items, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        items[i].handle = func_802811F0(items[i].str, func_8023B2AC(items[i].str, items[i].scale), (u32) items[i].y, items[i].scale, items[i].scale, items[i].mode);
    }
}

static s32 func_8023B2AC(u8 *str, f32 scale) {
#if VERSION_JP
    s32 n;

    for (n = 0; str[n] != 0; n++) {
    }
    return (320.0f - (f32) (n * 24) * scale) / 2;
#else
    return (320.0f - (f32) func_80280C08(str) * scale) / 2;
#endif
}

static void func_8023AF5C(f32 x, f32 y) {
    u8 buf[4];
    s32 v;
    s32 d;
    s32 i;
    s32 q;
    s32 t;
    s32 j;
    f32 w;

    v = D_802AC610.unk14;
    d = 10;
    for (i = 0, j = 0; i < 2; i++) {
        q = v / d;
        buf[j] = q + 0x10;
        j++;
        t = q * d;
        if (v >= t) {
            v -= t;
        }
        d /= 10;
    }
    buf[j] = 0;
    if (D_800AEE04 >= 2) {
        w = 16.0f;
        D_802AC7E0 = func_8026CE28(0x34E);
        D_802AC7DC = func_8022A6C4(D_802AC7E0, 0x3F);
        M2C_FIELD(D_802AC7DC, f32 *, 0x10) = (x - 28.0f) - 28.0f + 16.0f;
        M2C_FIELD(D_802AC7DC, f32 *, 0x14) = y + 1.0f;
        M2C_FIELD(D_802AC7DC, f32 *, 0x18) = (x - 28.0f) - 28.0f + w + 16.0f;
        M2C_FIELD(D_802AC7DC, f32 *, 0x1C) = y + 1.0f + 16.0f;
    } else {
        w = 0.0f;
        D_802AC7E0 = NULL;
    }
    D_802AC7D0 = func_8026CE28(0x130);
    D_802AC7D4 = func_8022A6C4(D_802AC7D0, 0x3F);
    M2C_FIELD(D_802AC7D4, s32 *, 0xC) |= 0x10;
    M2C_FIELD(D_802AC7D4, f32 *, 0x10) = (x - 28.0f) + w;
    M2C_FIELD(D_802AC7D4, f32 *, 0x14) = y + 1.0f;
    M2C_FIELD(D_802AC7D4, f32 *, 0x18) = (x - 28.0f) + 16.0f + w;
    M2C_FIELD(D_802AC7D4, f32 *, 0x1C) = y + 1.0f + 16.0f;
    D_802AC7D8 = func_802811F0(buf, (x - 36.0f) + 24.0f + 8.0f + w, y, 0.6f, 0.8f, 2);
}

s32 func_8023AEDC(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    if (arg0 != 0) {
        var_s0 = 0;
        do {
            if (!(func_8023A038(var_s0) & 8)) {
                var_s1 |= func_802399AC(var_s0);
            }
            var_s0 += 1;
        } while (var_s0 != 4);
    } else {
        var_s1 = func_802399AC(0);
    }
    return var_s1;
}

void func_8023AED0(s32 arg0) {
    D_802AC7CC = arg0;
}

void func_8023AE6C(s32 arg0, s32 arg1, s32 arg2) {
    if (!(D_802AC5D0 & 1) && (D_802A01B4 == 0)) {
        D_802AC5D4 = arg0;
        D_802AC5DC = D_802AC5D4;
        D_802AC5D8 = arg1;
        D_802AC5E0 = D_802AC5D8;
        D_802AC5D0 |= 1;
        D_802AC5E4 = arg2;
    }
}

void func_8023ADD4(s32 arg0) {
    if (0) {
        func_8023AC38();
    }
    if ((arg0 != 0) && (D_802A01B4 == 0)) {
        D_802A01B4 = 1;
        func_80238DFC(0x70, 0x70, 0U);
        func_80238DFC(0xD0, 0xF0, 0U);
        return;
    }
    if ((arg0 == 0) && (D_802A01B4 != 0)) {
        D_802A01B4 = 0;
        func_80238CF8(0x70, 0x70);
        func_80238CF8(0xD0, 0xF0);
        func_80238CF8(0x90, 0x90);
    }
}

static void func_8023AC38(void) {
    s32 i;

    if (D_802AC5D0 & 0x2C) {
        func_8023AB54(D_802A0B1C, 1);
        if (!(D_802AC5D0 & 4)) {
            func_80280DB4(D_802AC7E4);
            func_80280DB4(D_802AC7E8);
        }
    } else {
        if ((D_802AC75C == 0) || (func_8023AB90() == 0)) {
            func_8023AB54(D_802A0B1C, 3);
        } else {
            func_8023AB54(D_802A0B1C, 5);
        }
        for (i = 0; i < 5; i++) {
            func_8022A1E8(D_802AC7F8[i]);
        }
        func_8026CCBC(0x19);
        func_80280DB4(D_802AC814);
        func_80280DB4(D_802AC7E4);
        func_80280DB4(D_802AC7E8);
    }
    if (0) {
        func_8023AB90();
    }
    if (!(D_802AC5D0 & 4)) {
        func_8023AAE4();
    }
}

static void func_8023AB4C(TextItem *items, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_80280DB4(items[i].handle);
    }
}

static s32 func_8023AB90(void) {
    s32 id;
    u8 *obj;

    if (0) {
        func_8023AB54(0, 0);
        func_8023AB4C(0, 0);
    }
    id = func_80243DDC();
    obj = func_802443F4(id);
    if ((PLAYERS[id].unk24 == 3) || (M2C_FIELD(obj, f32 *, 0x68) != 0.0f) ||
        (M2C_FIELD(obj, f32 *, 0x6C) != 0.0f) || (func_80244BA4(id, 0x20) != 0)) {
        return 0;
    }
    return 1;
}

static void func_8023AB54(TextItem *items, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_80280DB4(items[i].handle);
    }
}

void func_8023AAE4() {
    func_8022A1E8(D_802AC7D4);
    func_8026CCBC(0x130);
    if (D_802AC7E0 != NULL) {
        func_8022A1E8(D_802AC7DC);
        func_8026CCBC(0x34E);
    }
    func_80280DB4(D_802AC7D8);
}

void func_8023AA78(s32 arg0) {
    if (arg0 != 0) {
        func_80238DFC(0x30, 0x3CF, 0U);
        func_80238DFC(0x401, 0x403, 0U);
        func_80229280(1);
        return;
    }
    func_80238CF8(0x30, 0x3CF);
    func_80238CF8(0x401, 0x403);
    func_80229280(0);
}

s32 func_8023AA60(s32 arg0) {
    return ((s32 *) D_802AC868)[arg0];
}

s32 func_8023A870(s32 arg0, s32 arg1) {
    u8 *obj;
    s32 pad[2];

    if (!(D_802A01B0 & 2)) {
        if (!(D_802AC5D0 & 1)) {
    func_80245208(arg0, 1);
    obj = func_802443F4(arg0);
    *func_8028A060(1) = D_802AC610.unk38;
    if ((D_802AC5D0 & 4) || ((D_802AC5D0 & 8) && (arg0 != 0))) {
        ((s32 *) D_802AC714)[arg0] = 2;
        func_802313DC(obj, 0x7FFFF);
        D_802A01BC = 0;
    } else {
        if (D_802A01BC != 0) {
            func_802350F8(1);
            func_80234F6C(1);
            func_80234858(&D_802AC5F8, &D_802AC5FC, &D_802AC600);
            D_802A01C0 = 1;
            if (D_802AC5D0 & 8) {
                func_80251534(0);
            }
        }
        D_802A01B8 = 0;
        D_802AC5D0 |= 0x92;
    }
    M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), s32 *, 0xC) &= ~0x4000;
    M2C_FIELD(M2C_FIELD(obj, u8 **, 0x40), s32 *, 0xC) |= 0x40;
    if (arg1 == 4) {
        arg1 = D_802AC798;
    }
    (&D_802AC858)[arg0] = arg1;
    func_80238A10(func_8023F26C, (s32) (D_802A0B98 + arg0 * 4), 0, 0, 0x130);
    return 1;
        }
    }
    return 0;
}

void func_8023A864(s32 arg0) {
    D_802A01B8 = arg0;
}

void func_8023A858(s32 arg0) {
    D_802A01BC = arg0;
}

void func_8023A84C(s32 arg0) {
    D_802AC798 = arg0;
}

s32 *func_8023A840() {
    return (s32 *) &D_802AC610;
}

s32 *func_8023A834() {
    return ((s32 *) &D_802AC660);
}

void func_8023A734(s32 arg0, s32 arg1, s32 arg2) {
    func_80228008(arg0, D_802A0CB0[arg1], D_802A0BA8[arg1][arg2]);
    if (arg1 == 0) {
        if (D_802A0CC8[arg2] != 0) {
            func_80228008(arg0, 8, -1);
        } else {
            func_80228008(arg0, 8, 0x4F);
        }
    } else if (arg1 == 2) {
        func_80228008(arg0, 5, D_802A0BA8[4][arg2]);
    } else if (arg1 == 3) {
        func_80228008(arg0, 0xC, D_802A0BA8[5][arg2]);
    }
}

void func_8023A68C() {
    func_80297D30(0xF, D_802A0CF4);
    D_802AC604 = func_80238A10(func_8023DB0C, 0, 0, 0, 9);
    D_802AC5D0 = 0x90;
    D_802A01B4 = 0;
    D_802A01B8 = 0;
    D_802A01BC = 1;
    D_802AC7CC = 0x20;
    D_802AC610.unk3C = 0;
    D_802AC610.unk40 = 0;
    D_802AC610.unk44 = 0;
    D_802AC610.unk48 = 0;
    func_8023A640();
    func_802513E0();
}

void func_8023A640() {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_802AC7A0[i] = -1;
    }
    D_802AC608 = 0;
}
