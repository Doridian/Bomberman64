/*
 * NON_MATCHING: ovl_0B_06's game object (the save-slot menus: three slots
 * with their numbers and trophies, copy and erase, the controller pak's
 * notes), complete: every function and its data (.data 0x1040 and .bss 0xF0
 * as the original; .rodata is the "%03d" format, three jump tables and the
 * floats). Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING
 * drafts").
 * flags: -O3
 * differing words: us 3686, eu 4335, jp 4563
 * jp has no `#if VERSION_JP` yet: its strings, text positions and code
 * changes are not drafted (docs/DECOMPILING.md, "Versions", step 6).
 *
 * A first draft from m2c, with every function rewritten by hand: the logic
 * is the original's, the schedule mostly isn't. Most of the callees are
 * statics that take arguments in the callers' registers: 80043040 (rect
 * $s0, sprite $s1, offset $fs0), 800433B0/80043404 (label $s0), 80044BE4
 * and 80046634 (mode $t0/$t2; the label loops in them keep $a2/$a3/$t1 across
 * calls to 80044B08: FADE_LABELS/FADE_SLOTS), 80044F70 (mask $s1, wait $s3),
 * 80045100 ($s4), 80045340 (save record $s2), 80045794 (mode $s6, the others
 * in the callers' argument slots), 80045C24 ($s0-$s4 and the two flags in
 * $t0/$s6), 80045F20 ($s2, $s3, $s5), 80046558 ($s0), 80046868 ($fp),
 * 80046F14 ($a0, $a3), 80047880 ($s0). The empty stubs (48 of them, where
 * the original has two `jr ra` in a row) are statics inlined into the
 * function after each, which leaves their 8-byte bodies in place; most are
 * still empty here, their code written into the caller. One is 8004382C,
 * the first loop of 80043834 (walking its pointer parameter up to a count).
 *
 * Order: the globals 8004390C, 80043B20 and 80043220 come out in place only
 * when defined above their callers (the handler; 80043220 is inlined into
 * the handler's case 1 and keeps its body), where the statics are defined
 * below theirs.
 * jp's and eu's strings and text positions aren't drafted yet.
 *
 * What still differs in us (words):
 * - 80043220 253: with the statics after it (80043280-80043834); 80043480 is
 *   8 bytes long.
 * - 80043C48 592: the handler, 0x20 bytes short.
 * - 8004473C 1386, 8004616C 1171: each with the statics after it up to the
 *   next global (80044908-80045F20 and 800464C0-80047030), most of them
 *   the wrong size.
 * - 8004747C 248, 800478D4 18 (with 80047880); 80043010 12 (the stubs and
 *   80043040-800430F0); the callbacks 80047D08-80047DE4 1 each (80047DE4 is
 *   counted with nothing after it).
 * - 8004390C, 80043B20, 80047A48, 80047A7C and 80047AC4 match.
 */
#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
} Gfx_ovl0B_06;

/* D_ovl0B_06_80049930 */
typedef struct {
    /* 0x00 */ UnkStructA_40 *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} Unk24_ovl0B_06; /* size = 0x24 */

/* A text: string, handle, position, scale, flag, and what it shows next */
typedef struct {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x18 */ UnkStructA_40 *unk18;
} Label_ovl0B_06; /* size = 0x1C */

/* A box drawn by a display-list callback */
typedef struct {
    /* 0x00 */ UnkStructA_40 *unk0;
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
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ void (*unk40)(s32, Gfx_ovl0B_06 **);
} Box_ovl0B_06; /* size = 0x44 */

typedef struct {
    /* 0x00 */ UnkStructA_40 *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Rect_ovl0B_06; /* size = 0x14 */

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} Spr_ovl0B_06; /* size = 0x18 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} Col_ovl0B_06; /* size = 0x10 */

typedef struct {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 unkC;
} Txt_ovl0B_06; /* size = 0x10 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ f32 unk4;
} Pair_ovl0B_06; /* size = 0x8 */

typedef struct {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} Item_ovl0B_06; /* size = 0x14 */

/* D_ovl0B_06_8004A5E0 */
typedef struct {
    /* 0x00 */ s32 unk[6];
} Unk18_ovl0B_06; /* size = 0x18 */

s32 func_ovl0B_06_80047E20(u8 *, const char *, s32); /* 0x0101 */
void func_ovl0B_06_80048250(s32, s32, s32); /* 0x0F00 */
s32 func_ovl0B_06_80048258(void); /* 0x0F01 */
s32 func_ovl0B_06_80048268(void); /* 0x0F03 */
void func_ovl0B_06_800482B0(s32); /* 0x0F0C */
void func_ovl0B_06_80048300(s32, s32, s32); /* 0x0F16 */
UnkStructA_40 *func_ovl0B_06_80048838(s32, s32); /* 0x1500 */
void func_ovl0B_06_80048840(UnkStructA_40 *); /* 0x1501 */
void func_ovl0B_06_80048860(UnkStructA_40 *, s32); /* 0x1505 */
void func_ovl0B_06_80048868(UnkStructA_40 *, s32, s32, s32); /* 0x1506 */
void func_ovl0B_06_80048888(UnkStructA_40 *, s32, s32); /* 0x150A */
UnkStructA_40 *func_ovl0B_06_800488B8(void (*)(s32, Gfx_ovl0B_06 **), s32); /* 0x1510 */
s32 func_ovl0B_06_800488C8(UnkStructA_40 *, s32); /* 0x1512 */
void func_ovl0B_06_800488D8(s32); /* 0x1514 */
void func_ovl0B_06_80048978(s32); /* 0x1700 */
void func_ovl0B_06_80048988(s32); /* 0x1702 */
void func_ovl0B_06_80048998(f32, f32, f32); /* 0x1704 */
void func_ovl0B_06_800489B8(f32, f32, f32); /* 0x1708 */
void func_ovl0B_06_800489C0(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0B_06_80048A00(s32); /* 0x1711 */
s32 func_ovl0B_06_80048CA8(void (*)(), void *, void *, s32, s32); /* 0x1900 */
void func_ovl0B_06_80048CB0(s32); /* 0x1901 */
void func_ovl0B_06_80048CB8(void); /* 0x1902 */
void func_ovl0B_06_80048CC8(s32); /* 0x1904 */
void func_ovl0B_06_80048CF0(void); /* 0x1909 */
UnkStructC *func_ovl0B_06_80048D30(s32); /* 0x1A00 */
void func_ovl0B_06_80048D40(UnkStructC *, s32); /* 0x1A02 */
s32 func_ovl0B_06_80048DF0(s32); /* 0x1C02 */
s32 func_ovl0B_06_80048DF8(s32, s32); /* 0x1C03 */
s32 func_ovl0B_06_80048E00(s32); /* 0x1C04 */
s32 func_ovl0B_06_80048E18(void); /* 0x1C07 */
s32 func_ovl0B_06_80048E20(s32); /* 0x1C08 */
s32 func_ovl0B_06_80048E28(s32, s32 *); /* 0x1C09 */
u8 *func_ovl0B_06_80048E38(void); /* 0x1C0B */
void func_ovl0B_06_80048E40(s32); /* 0x1C0C */
void func_ovl0B_06_80048E48(s32); /* 0x1C0D */
f32 func_ovl0B_06_80048E50(f32); /* 0x1D00 */
void func_ovl0B_06_80048EF0(void); /* 0x1E00 */
void func_ovl0B_06_80048FF8(s32, s32, s32); /* 0x2201 */
s32 func_ovl0B_06_80049060(void); /* 0x2406 */
s32 func_ovl0B_06_80049090(u8 *, u16, u16, f32, f32, s32); /* 0x2501 */
void func_ovl0B_06_80049098(s32); /* 0x2502 */
void func_ovl0B_06_800490A8(s32, u16, u16); /* 0x2504 */
void func_ovl0B_06_800490B0(s32, u16, u16); /* 0x2505 */
void func_ovl0B_06_800490B8(s32, f32, f32); /* 0x2506 */
void func_ovl0B_06_800490C0(s32, f32, f32); /* 0x2507 */
UnkStructA_40 *func_ovl0B_06_800490C8(s32); /* 0x2508 */
s32 func_ovl0B_06_800490E0(u8 *); /* 0x250B */
s32 func_ovl0B_06_800490E8(u8 *, u16, u16, f32, f32, s32); /* 0x250C */
void func_ovl0B_06_800490F0(s32, u8 *, s32); /* 0x250D */
void func_ovl0B_06_80049230(s32); /* 0x2B00 */
void func_ovl0B_06_80049250(s32, f32, f32, f32); /* 0x2B04 */
s32 func_ovl0B_06_80049368(s32, s32); /* 0x2F09 */
s32 func_ovl0B_06_80049370(void); /* 0x2F0A */
void func_ovl0B_06_80049378(s32); /* 0x2F0B */
void func_ovl0B_06_80049380(s32); /* 0x2F0C */
s32 func_ovl0B_06_80049388(void); /* 0x2F0D */
s32 func_ovl0B_06_80049390(void); /* 0x2F0E */


/* The labels of a list fade in or out together. */
#define FADE_LABELS(mode, labels, n) { s32 i_; for (i_ = 0; i_ < (n); i_++) { func_ovl0B_06_80044B08(mode, &(labels)[i_]); } }
#define FADE_SLOTS(mode) { s32 *p_; Label_ovl0B_06 *l_; for (p_ = D_ovl0B_06_8004A5D0, l_ = D_ovl0B_06_800499F0; p_ < D_ovl0B_06_8004A5D0 + 3; p_++, l_++) { if (*p_ != 0) { func_ovl0B_06_80044B08(mode, l_); } } }
#define STUBS() { func_ovl0B_06_80043010(); func_ovl0B_06_80043018(); func_ovl0B_06_80043020(); func_ovl0B_06_80043028(); func_ovl0B_06_80043030(); func_ovl0B_06_80043038(); func_ovl0B_06_800450F8(); func_ovl0B_06_80045184(); func_ovl0B_06_800459D0(); func_ovl0B_06_80046164(); func_ovl0B_06_80047028(); func_ovl0B_06_80047D00(); func_ovl0B_06_80047B38(); func_ovl0B_06_80047B40(); func_ovl0B_06_80047B48(); func_ovl0B_06_80047B50(); func_ovl0B_06_80047B58(); func_ovl0B_06_80047B60(); func_ovl0B_06_80047B68(); func_ovl0B_06_80047B70(); func_ovl0B_06_80047B78(); func_ovl0B_06_80047B80(); func_ovl0B_06_80047B88(); func_ovl0B_06_80047B90(); }
static void func_ovl0B_06_80043010(void);
static void func_ovl0B_06_80043018(void);
static void func_ovl0B_06_80043020(void);
static void func_ovl0B_06_80043028(void);
static void func_ovl0B_06_80043030(void);
static void func_ovl0B_06_80043038(void);
static void func_ovl0B_06_80043040(Rect_ovl0B_06 *rect, Spr_ovl0B_06 *spr, f32 dy);
static void func_ovl0B_06_800430F0(s32 arg0);
static void func_ovl0B_06_80043218(void);
void func_ovl0B_06_80043220(void);
static void func_ovl0B_06_80043278(void);
static void func_ovl0B_06_80043280(void);
static void func_ovl0B_06_800433A8(void);
static void func_ovl0B_06_800433B0(Label_ovl0B_06 *label);
static void func_ovl0B_06_800433F4(void);
static void func_ovl0B_06_800433FC(void);
static void func_ovl0B_06_80043404(Label_ovl0B_06 *label);
static void func_ovl0B_06_80043450(void);
static void func_ovl0B_06_80043458(void);
static void func_ovl0B_06_80043460(void);
static void func_ovl0B_06_80043468(void);
static void func_ovl0B_06_80043470(void);
static void func_ovl0B_06_80043478(void);
static void func_ovl0B_06_80043480(s32 arg0);
static void func_ovl0B_06_8004382C(Label_ovl0B_06 *p, s32 n);
static void func_ovl0B_06_80043834(void);
static void func_ovl0B_06_800438FC(void);
static void func_ovl0B_06_80043904(void);
void func_ovl0B_06_8004390C(void);
void func_ovl0B_06_80043B20(void);
static void func_ovl0B_06_80043C40(void);
void func_ovl0B_06_80043C48(s32 arg0);
void func_ovl0B_06_8004473C(void);
static void func_ovl0B_06_80044908(s32 arg0);
static void func_ovl0B_06_80044B08(s32 arg0, Label_ovl0B_06 *label);
static void func_ovl0B_06_80044B90(void);
static void func_ovl0B_06_80044B98(void);
static void func_ovl0B_06_80044BA0(s32 arg0, Col_ovl0B_06 *col);
static void func_ovl0B_06_80044BE4(s32 arg0);
static void func_ovl0B_06_80044E40(void);
static void func_ovl0B_06_80044E48(s32 arg0, s32 arg1);
static s32 func_ovl0B_06_80044F70(s32 arg0, s32 arg1, s32 mask, s32 wait);
static s32 func_ovl0B_06_80045054(void);
static void func_ovl0B_06_800450F8(void);
static s32 func_ovl0B_06_80045100(s32 arg0);
static void func_ovl0B_06_80045184(void);
static s32 func_ovl0B_06_8004518C(void);
static void func_ovl0B_06_80045340(s32 arg0, u8 *save);
static s32 func_ovl0B_06_80045794(s32 arg0, s32 arg1, s32 arg2, s32 mode);
static void func_ovl0B_06_800459D0(void);
static void func_ovl0B_06_800459D8(s32 arg0);
static void func_ovl0B_06_80045C24(Label_ovl0B_06 *a, Label_ovl0B_06 *b, u8 *str, s16 dx, s16 dy);
static void func_ovl0B_06_80045D20(void);
static void func_ovl0B_06_80045D28(s32 arg0, s32 arg1);
static s32 func_ovl0B_06_80045F20(s32 arg0, Col_ovl0B_06 *on, Col_ovl0B_06 *off, s32 n);
static void func_ovl0B_06_80046164(void);
void func_ovl0B_06_8004616C(void);
static void func_ovl0B_06_800464C0(s32 arg0);
static void func_ovl0B_06_80046558(s32 arg0, s32 arg1);
static void func_ovl0B_06_800465E0(s16 alpha, UnkStructA_40 *obj);
static void func_ovl0B_06_80046624(void);
static void func_ovl0B_06_8004662C(void);
static void func_ovl0B_06_80046634(s32 arg0);
static void func_ovl0B_06_80046850(void);
static void func_ovl0B_06_80046858(void);
static void func_ovl0B_06_80046860(void);
static s32 func_ovl0B_06_80046868(s32 slot);
static void func_ovl0B_06_80046F14(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
static void func_ovl0B_06_80047028(void);
static s32 func_ovl0B_06_80047030(void);
void func_ovl0B_06_8004747C(void);
static void func_ovl0B_06_80047880(s32 arg0);
void func_ovl0B_06_800478D4(void);
void func_ovl0B_06_80047A48(s32 arg0, UnkStructA *arg1);
void func_ovl0B_06_80047A7C(f32 arg0);
void func_ovl0B_06_80047AC4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0B_06_80047B20(void);
static void func_ovl0B_06_80047B38(void);
static void func_ovl0B_06_80047B40(void);
static void func_ovl0B_06_80047B48(void);
static void func_ovl0B_06_80047B50(void);
static void func_ovl0B_06_80047B58(void);
static void func_ovl0B_06_80047B60(void);
static void func_ovl0B_06_80047B68(void);
static void func_ovl0B_06_80047B70(void);
static void func_ovl0B_06_80047B78(void);
static void func_ovl0B_06_80047B80(void);
static void func_ovl0B_06_80047B88(void);
static void func_ovl0B_06_80047B90(void);
static void func_ovl0B_06_80047B98(Gfx_ovl0B_06 **arg0, Box_ovl0B_06 *box);
static void func_ovl0B_06_80047D00(void);
void func_ovl0B_06_80047D08(s32 arg0, Gfx_ovl0B_06 **arg1);
void func_ovl0B_06_80047D34(s32 arg0, Gfx_ovl0B_06 **arg1);
void func_ovl0B_06_80047D60(s32 arg0, Gfx_ovl0B_06 **arg1);
void func_ovl0B_06_80047D8C(s32 arg0, Gfx_ovl0B_06 **arg1);
void func_ovl0B_06_80047DB8(s32 arg0, Gfx_ovl0B_06 **arg1);
void func_ovl0B_06_80047DE4(s32 arg0, Gfx_ovl0B_06 **arg1);

/* .bss */
u8 D_ovl0B_06_8004A590[0x24]; /* not referenced here */
s32 D_ovl0B_06_8004A5B4;
s32 D_ovl0B_06_8004A5B8;
Vec3f D_ovl0B_06_8004A5C0;
u8 D_ovl0B_06_8004A5CC[4]; /* not referenced here */
s32 D_ovl0B_06_8004A5D0[4];
Unk18_ovl0B_06 D_ovl0B_06_8004A5E0[3];
UnkStructA_40 *D_ovl0B_06_8004A628;
UnkStructA_40 *D_ovl0B_06_8004A62C;
UnkStructA_40 *D_ovl0B_06_8004A630;
UnkStructA_40 *D_ovl0B_06_8004A634;
UnkStructC *D_ovl0B_06_8004A638;
u8 D_ovl0B_06_8004A63C[4]; /* not referenced here */
u8 D_ovl0B_06_8004A640[8];
u8 D_ovl0B_06_8004A648[8];
s32 D_ovl0B_06_8004A650[4];
UnkStructA_40 *D_ovl0B_06_8004A660;
UnkStructA_40 *D_ovl0B_06_8004A664;
s32 D_ovl0B_06_8004A668[2];
s32 D_ovl0B_06_8004A670[4];

/* .data */
u8 D_ovl0B_06_80049450[] = { 0x1F, 0x42, 0x45, 0x3E, 0x0F, 0x11, 0x00, 0x00, 0x1F, 0x42, 0x45, 0x3E, 0x0F, 0x12, 0x00, 0x00, 0x1F, 0x42, 0x45, 0x3E, 0x0F, 0x13, 0x00, 0x00, 0x51, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x51, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x51, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00 };
u8 D_ovl0B_06_80049480[] = { 0x2C, 0x3E, 0x45, 0x3E, 0x3C, 0x4D, 0x0F, 0x1F, 0x42, 0x45, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x3E, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x0F, 0x1F, 0x42, 0x45, 0x3E, 0x00, 0x00 };
u8 D_ovl0B_06_800494A4[] = { 0x1D, 0x42, 0x3F, 0x3F, 0x42, 0x3C, 0x4E, 0x45, 0x4D, 0x52, 0x0F, 0x25, 0x3E, 0x4F, 0x3E, 0x45, 0x00, 0x00, 0x00, 0x00, 0x27, 0x48, 0x4B, 0x46, 0x3A, 0x45, 0x00, 0x00, 0x21, 0x3A, 0x4B, 0x3D, 0x00, 0x00, 0x00, 0x00 };
u8 D_ovl0B_06_800494C8[] = { 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x0F, 0x30, 0x41, 0x42, 0x3C, 0x41, 0x0F, 0x1F, 0x42, 0x45, 0x3E, 0xF7, 0x00, 0x00, 0x00, 0x27, 0x48, 0x0F, 0x1D, 0x3A, 0x4D, 0x3A, 0x0F, 0x1F, 0x48, 0x4E, 0x47, 0x3D, 0x00, 0x00, 0x00, 0x1A, 0x4B, 0x3E, 0x0F, 0x32, 0x48, 0x4E, 0x0F, 0x2C, 0x4E, 0x4B, 0x3E, 0xF7, 0x00, 0x00, 0x00, 0x32, 0x1E, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x28, 0x00, 0x00 };
u8 D_ovl0B_06_80049508[] = { 0x2C, 0x3E, 0x45, 0x3E, 0x3C, 0x4D, 0x0F, 0x1F, 0x42, 0x45, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C, 0x48, 0x49, 0x52, 0xFF, 0x3F, 0x4B, 0x48, 0x46, 0x0F, 0x20, 0x3A, 0x46, 0x3E, 0x0F, 0x29, 0x3A, 0x44, 0x00, 0x00, 0x00, 0x00 };
u8 D_ovl0B_06_80049534[] = { 0x1C, 0x48, 0x49, 0x52, 0x0F, 0x30, 0x41, 0x42, 0x3C, 0x41, 0x0F, 0x1D, 0x3A, 0x4D, 0x3A, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x0F, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0x00, 0x00, 0x00, 0x00 };
u8 D_ovl0B_06_80049558[] = { 0x27, 0x48, 0x0F, 0x1F, 0x42, 0x45, 0x3E, 0x0F, 0x00, 0x27, 0x48, 0x0F, 0x1F, 0x42, 0x45, 0x3E, 0x0F, 0x00, 0x27, 0x48, 0x0F, 0x1F, 0x42, 0x45, 0x3E, 0x0F, 0x00, 0x00, 0x22, 0x47, 0x4C, 0x3E, 0x4B, 0x4D, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0xFF, 0x42, 0x47, 0x4D, 0x48, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0xE9, 0xC5, 0x9F, 0x5F, 0x9B, 0xF9, 0x7E, 0x5F, 0xC8, 0x65, 0x6C, 0x6F, 0x80, 0x78, 0xF9, 0x73, 0xDC, 0xB0, 0xD7, 0xCE, 0xBC, 0x00, 0x00, 0x1C, 0x3A, 0x47, 0x47, 0x48, 0x4D, 0x0F, 0x26, 0x3A, 0x44, 0x3E, 0x0F, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0xFF, 0x27, 0x48, 0x0F, 0x1E, 0x46, 0x49, 0x4D, 0x52, 0x0F, 0x49, 0x3A, 0x40, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x27, 0x48, 0x0F, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0x0F, 0x1F, 0x48, 0x4E, 0x47, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x1E, 0x4B, 0x4B, 0x48, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x3A, 0x47, 0x47, 0x48, 0x4D, 0x0F, 0x26, 0x3A, 0x44, 0x3E, 0x0F, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0xF8, 0x0F, 0x29, 0x45, 0x3E, 0x3A, 0x4C, 0x3E, 0x0F, 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0xFF, 0x11, 0x0F, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0x0F, 0x42, 0x47, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x3A, 0x4D, 0x3A, 0x0F, 0x1C, 0x48, 0x49, 0x42, 0x3E, 0x3D, 0x0F, 0x4D, 0x48, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x00, 0x00, 0x00, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0x0F, 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x3D, 0x00, 0x00, 0x00, 0x2D, 0x41, 0x3E, 0x4B, 0x3E, 0x0F, 0x42, 0x4C, 0x0F, 0x3A, 0x0F, 0x29, 0x4B, 0x48, 0x3B, 0x45, 0x3E, 0x46, 0x0F, 0x50, 0x42, 0x4D, 0x41, 0xFF, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x3A, 0x47, 0x3D, 0xFB, 0x48, 0x4B, 0xFF, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1A, 0x0F, 0x0F, 0x2B, 0x3E, 0x42, 0x47, 0x4C, 0x3E, 0x4B, 0x4D, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1B, 0x0F, 0x0F, 0x2B, 0x3E, 0x42, 0x47, 0x42, 0x4D, 0x42, 0x3A, 0x45, 0x42, 0x53, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x3E, 0x42, 0x47, 0x42, 0x4D, 0x42, 0x3A, 0x45, 0x42, 0x53, 0x3E, 0x3D, 0x00, 0x00, 0x00, 0x2B, 0x3E, 0x42, 0x47, 0x42, 0x4D, 0x42, 0x3A, 0x45, 0x42, 0x53, 0x3E, 0x0F, 0x1F, 0x3A, 0x42, 0x45, 0x4E, 0x4B, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x27, 0x3E, 0x50, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x1F, 0x48, 0x4E, 0x47, 0x3D, 0x00, 0x00, 0x00, 0x00 };
u8 D_ovl0B_06_80049738[] = { 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x00, 0x00 };
u8 D_ovl0B_06_8004974C[] = { 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x0F, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0xF7, 0x00, 0x00, 0x00 };
u8 D_ovl0B_06_8004975C[] = { 0x1C, 0x48, 0x49, 0x52, 0x0F, 0x1D, 0x3A, 0x4D, 0x3A, 0x0F, 0x3F, 0x4B, 0x48, 0x46, 0x0F, 0x20, 0x3A, 0x46, 0x3E, 0x0F, 0x29, 0x3A, 0x44, 0xFF, 0x22, 0x4C, 0x0F, 0x2D, 0x41, 0x42, 0x4C, 0x0F, 0x28, 0x24, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 D_ovl0B_06_80049784[] = { 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0x0F, 0x1E, 0x51, 0x42, 0x4C, 0x4D, 0x4C, 0xFF, 0x28, 0x24, 0x0F, 0x4D, 0x48, 0x0F, 0x28, 0x4F, 0x3E, 0x4B, 0x50, 0x4B, 0x42, 0x4D, 0x3E, 0xF7, 0x00, 0x00 };
u8 D_ovl0B_06_800497A4[] = { 0x1A, 0x9F, 0x6F, 0x5F, 0xE9, 0xB8, 0xAA, 0xC2, 0xB1, 0x0F, 0x0F, 0x1B, 0x9F, 0x6F, 0x5F, 0xE9, 0xD2, 0xEA, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 D_ovl0B_06_800497BC[] = { 0x32, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 D_ovl0B_06_800497C4[] = { 0x27, 0x48, 0x00, 0x00, 0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0x42, 0x47, 0x40, 0x0F, 0x1D, 0x3A, 0x4D, 0x3A, 0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0x42, 0x47, 0x40, 0x0F, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x48, 0x4E, 0x45, 0x3D, 0x0F, 0x27, 0x48, 0x4D, 0x0F, 0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0x0F, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x2C, 0x3A, 0x4F, 0x3E, 0x0F, 0x1F, 0x3A, 0x42, 0x45, 0x4E, 0x4B, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0xFF, 0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0x0F, 0x1F, 0x3A, 0x42, 0x45, 0x4E, 0x4B, 0x3E, 0x00, 0x00, 0x00, 0x2C, 0x3A, 0x4F, 0x42, 0x47, 0x40, 0x0F, 0x20, 0x3A, 0x46, 0x3E, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x26, 0x3E, 0x46, 0x48, 0x4B, 0x52, 0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x20, 0x3A, 0x46, 0x3E, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x26, 0x3E, 0x46, 0x48, 0x4B, 0x52, 0x0F, 0x1F, 0x3A, 0x42, 0x45, 0x4E, 0x4B, 0x3E, 0xFF, 0x1D, 0x3A, 0x4D, 0x3A, 0x0F, 0x1C, 0x3A, 0x47, 0x47, 0x48, 0x4D, 0x0F, 0x3B, 0x3E, 0x0F, 0x2C, 0x3A, 0x4F, 0x3E, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x3A, 0x42, 0x45, 0x3E, 0x3D, 0x0F, 0x4D, 0x48, 0x0F, 0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0xFF, 0x20, 0x3A, 0x46, 0x3E, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x26, 0x3E, 0x46, 0x48, 0x4B, 0x52, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x4B, 0x3A, 0x4C, 0x42, 0x47, 0x40, 0x0F, 0x1D, 0x3A, 0x4D, 0x3A, 0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D, 0x41, 0x3E, 0x4B, 0x3E, 0x0F, 0x42, 0x4C, 0x0F, 0x3A, 0x0F, 0x20, 0x3A, 0x46, 0x3E, 0x0F, 0x29, 0x3A, 0x44, 0xFF, 0x26, 0x3E, 0x46, 0x48, 0x4B, 0x52, 0x0F, 0x29, 0x4B, 0x48, 0x3B, 0x45, 0x3E, 0x46, 0xFF, 0xFF, 0x1C, 0x48, 0x4E, 0x45, 0x3D, 0x0F, 0x27, 0x48, 0x4D, 0x0F, 0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0xFF, 0x20, 0x3A, 0x46, 0x3E, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x26, 0x3E, 0x46, 0x48, 0x4B, 0x52, 0x00, 0x00, 0x00, 0x00 };
s32 D_ovl0B_06_80049924 = -1;
s32 D_ovl0B_06_80049928 = 0;
s32 D_ovl0B_06_8004992C = 0;
Unk24_ovl0B_06 D_ovl0B_06_80049930[3] = {
    { NULL, 0x19, 0, -560.0f, 190.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { NULL, 0x19, 0, -560.0f, -15.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { NULL, 0x19, 0, -560.0f, -220.0f, 0.0f, 0.0f, 0.0f, 0.0f }
};
Label_ovl0B_06 D_ovl0B_06_8004999C[3] = {
    { D_ovl0B_06_80049450, 0, 0x28, 0x32, 0.5f, 0.5f, 0, NULL },
    { D_ovl0B_06_80049450 + 0x8, 0, 0x28, 0x5A, 0.5f, 0.5f, 0, NULL },
    { D_ovl0B_06_80049450 + 0x10, 0, 0x28, 0x82, 0.5f, 0.5f, 0, NULL }
};
Label_ovl0B_06 D_ovl0B_06_800499F0[3] = {
    { D_ovl0B_06_80049450 + 0x18, 0, 0x3C, 0x46, 0.5f, 0.5f, 0, NULL },
    { D_ovl0B_06_80049450 + 0x20, 0, 0x3C, 0x6E, 0.5f, 0.5f, 0, NULL },
    { D_ovl0B_06_80049450 + 0x28, 0, 0x3C, 0x96, 0.5f, 0.5f, 0, NULL }
};
Label_ovl0B_06 D_ovl0B_06_80049A44[6] = {
    { D_ovl0B_06_80049480, 0, 0x64, 0x14, 0.8f, 0.8f, 0, NULL },
    { D_ovl0B_06_80049480 + 0x10, 0, 0x8A, 0x3C, 0.8f, 0.8f, 5, NULL },
    { D_ovl0B_06_80049480 + 0x10, 0, 0x8A, 0x64, 0.8f, 0.8f, 5, NULL },
    { D_ovl0B_06_80049480 + 0x10, 0, 0x8A, 0x8C, 0.8f, 0.8f, 5, NULL },
    { D_ovl0B_06_80049480 + 0x18, 0, 0x28, 0xCA, 0.55f, 0.55f, 0, NULL },
    { D_ovl0B_06_80049480, 0, 0x68, 0x18, 0.8f, 0.8f, 7, NULL }
};
Label_ovl0B_06 D_ovl0B_06_80049AEC[2] = {
    { D_ovl0B_06_800494A4 + 0x14, 0, 0x5D, 0x3E, 0.55f, 0.7f, 1, NULL },
    { D_ovl0B_06_800494A4 + 0x1C, 0, 0xF5, 0x3E, 0.55f, 0.7f, 1, NULL }
};
Label_ovl0B_06 D_ovl0B_06_80049B24 = { D_ovl0B_06_800494C8 + 0x14, 0, 0x4B, 0xB4, 0.8f, 0.8f, 0, NULL };
Label_ovl0B_06 D_ovl0B_06_80049B40[3] = {
    { D_ovl0B_06_800494C8 + 0x24, 0, 0x32, 0xAA, 0.65f, 0.8f, 0, NULL },
    { D_ovl0B_06_800494C8 + 0x34, 0, 0x5A, 0xC8, 0.6f, 0.6f, 1, NULL },
    { D_ovl0B_06_800494C8 + 0x3C, 0, 0xBE, 0xC8, 0.6f, 0.6f, 0, NULL }
};
Label_ovl0B_06 D_ovl0B_06_80049B94[10] = {
    { D_ovl0B_06_80049508, 0, 0x64, 0x14, 0.8f, 0.8f, 0, NULL },
    { D_ovl0B_06_80049558, 0, 0xC6, 0x3C, 0.8f, 0.8f, 5, NULL },
    { D_ovl0B_06_80049558 + 0x9, 0, 0xC6, 0x64, 0.8f, 0.8f, 5, NULL },
    { D_ovl0B_06_80049558 + 0x12, 0, 0xC6, 0x8C, 0.8f, 0.8f, 5, NULL },
    { D_ovl0B_06_80049508 + 0x10, 0, 0x2C, 0xBE, 0.5f, 0.5f, 0, NULL },
    { D_ovl0B_06_80049534 + 0x14, 0, 0xAB, 0xCA, 0.5f, 0.5f, 0, NULL },
    { D_ovl0B_06_80049508, 0, 0x68, 0x18, 0.8f, 0.8f, 7, NULL },
    { D_ovl0B_06_80049558, 0, 0xCA, 0x40, 0.8f, 0.8f, 7, NULL },
    { D_ovl0B_06_80049558 + 0x9, 0, 0xCA, 0x68, 0.8f, 0.8f, 7, NULL },
    { D_ovl0B_06_80049558 + 0x12, 0, 0xCA, 0x90, 0.8f, 0.8f, 7, NULL }
};
Box_ovl0B_06 D_ovl0B_06_80049CAC[6] = {
    { NULL, 0, 0xB4, 0, 0x78, 0.0f, 130.0f, 1.0f, 0.15f, 0x82, 0x82, 0xA0, 0x43, 0.0f, 0, 0x480, func_ovl0B_06_80047D08 },
    { NULL, 0, 0xB4, 0, 0x78, 0.0f, 130.0f, 1.0f, 0.15f, 0x82, 0x82, 0xA0, 0x6B, 0.0f, 0, 0x480, func_ovl0B_06_80047D34 },
    { NULL, 0, 0xB4, 0, 0x78, 0.0f, 130.0f, 1.0f, 0.15f, 0x82, 0x82, 0xA0, 0x93, 0.0f, 0, 0x480, func_ovl0B_06_80047D60 },
    { NULL, 0, 0xB4, 0, 0x78, 0.0f, 50.0f, 1.0f, 0.49f, 0x32, 0x32, 0x50, 0xC0, 0.0f, 0, 0x480, func_ovl0B_06_80047D8C },
    { NULL, 0x1E, 0x1E, 0x1E, 0xB4, 0.0f, 160.0f, 1.0f, 0.75f, 0xA0, 0xA0, 0xA0, 0x78, 0.0f, 0, 0x81, func_ovl0B_06_80047DB8 },
    { NULL, 0, 0xB4, 0, 0x78, 0.0f, 50.0f, 1.0f, 0.49f, 0x32, 0x32, 0xDA, 0xC0, 0.0f, 0, 0x480, func_ovl0B_06_80047DE4 }
};
Rect_ovl0B_06 D_ovl0B_06_80049E44[11] = {
    { NULL, 34.0f, 171.0f, 66.0f, 203.0f },
    { NULL, 68.0f, 177.0f, 92.0f, 195.0f },
    { NULL, 94.0f, 171.0f, 126.0f, 203.0f },
    { NULL, 112.0f, 171.0f, 144.0f, 203.0f },
    { NULL, 150.0f, 60.0f, 170.0f, 80.0f },
    { NULL, 174.0f, 60.0f, 194.0f, 80.0f },
    { NULL, 198.0f, 60.0f, 218.0f, 80.0f },
    { NULL, 222.0f, 60.0f, 242.0f, 80.0f },
    { NULL, 172.0f, 171.0f, 204.0f, 203.0f },
    { NULL, 206.0f, 177.0f, 230.0f, 195.0f },
    { NULL, 232.0f, 171.0f, 264.0f, 203.0f }
};
Rect_ovl0B_06 D_ovl0B_06_80049F20[3][7] = {
    {
        { NULL, 250.0f, 55.0f, 274.0f, 79.0f },
        { NULL, 122.0f, 61.0f, 132.0f, 71.0f },
        { NULL, 142.0f, 61.0f, 152.0f, 71.0f },
        { NULL, 162.0f, 61.0f, 172.0f, 71.0f },
        { NULL, 182.0f, 61.0f, 192.0f, 71.0f },
        { NULL, 202.0f, 61.0f, 212.0f, 71.0f },
        { NULL, 222.0f, 61.0f, 232.0f, 71.0f }
    },
    {
        { NULL, 250.0f, 55.0f, 274.0f, 79.0f },
        { NULL, 122.0f, 61.0f, 132.0f, 71.0f },
        { NULL, 142.0f, 61.0f, 152.0f, 71.0f },
        { NULL, 162.0f, 61.0f, 172.0f, 71.0f },
        { NULL, 182.0f, 61.0f, 192.0f, 71.0f },
        { NULL, 202.0f, 61.0f, 212.0f, 71.0f },
        { NULL, 222.0f, 61.0f, 232.0f, 71.0f }
    },
    {
        { NULL, 250.0f, 55.0f, 274.0f, 79.0f },
        { NULL, 122.0f, 61.0f, 132.0f, 71.0f },
        { NULL, 142.0f, 61.0f, 152.0f, 71.0f },
        { NULL, 162.0f, 61.0f, 172.0f, 71.0f },
        { NULL, 182.0f, 61.0f, 192.0f, 71.0f },
        { NULL, 202.0f, 61.0f, 212.0f, 71.0f },
        { NULL, 222.0f, 61.0f, 232.0f, 71.0f }
    }
};
Spr_ovl0B_06 D_ovl0B_06_8004A0C4[15] = {
    { 18.0f, 24.0f, 0x43, 8, 0, 0 },
    { 32.0f, 32.0f, 0x45, 0, 0, 0x200 },
    { 32.0f, 32.0f, 0x45, 2, 0, 0x200 },
    { 32.0f, 32.0f, 0x45, 4, 0, 0x200 },
    { 24.0f, 24.0f, 0x44, 6, 0, 0 },
    { 24.0f, 24.0f, 0x44, 8, 0, 0 },
    { 24.0f, 24.0f, 0x44, 0xA, 0, 0 },
    { 24.0f, 24.0f, 0x44, 0xC, 0, 0 },
    { 24.0f, 24.0f, 0x44, 0xE, 0, 0 },
    { 24.0f, 24.0f, 0x44, 0x10, 0, 0 },
    { 24.0f, 24.0f, 0x44, 0x12, 0, 0 },
    { 24.0f, 24.0f, 0x44, 0x14, 0, 0 },
    { 20.0f, 20.0f, 0x39, 0, 0, 0 },
    { 20.0f, 20.0f, 0x39, 2, 0, 0 },
    { 32.0f, 32.0f, 0x45, 6, 0, 0x200 }
};
Spr_ovl0B_06 * D_ovl0B_06_8004A22C[3] = { &D_ovl0B_06_8004A0C4[1], &D_ovl0B_06_8004A0C4[0], &D_ovl0B_06_8004A0C4[2] };
Rect_ovl0B_06 * D_ovl0B_06_8004A238[3] = { &D_ovl0B_06_80049E44[0], &D_ovl0B_06_80049E44[1], &D_ovl0B_06_80049E44[2] };
Col_ovl0B_06 D_ovl0B_06_8004A244 = { 0, 0xB4, 0, 0x78 };
Col_ovl0B_06 D_ovl0B_06_8004A254 = { 0xFA, 0xFA, 0, 0x78 };
Col_ovl0B_06 D_ovl0B_06_8004A264 = { 0xC8, 0, 0, 0x78 };
Col_ovl0B_06 D_ovl0B_06_8004A274 = { 0xFA, 0x80, 0, 0xB4 };
Col_ovl0B_06 D_ovl0B_06_8004A284 = { 0x1E, 0x1E, 0x1E, 0xB4 };
Txt_ovl0B_06 D_ovl0B_06_8004A294[21] = {
    { D_ovl0B_06_800494C8 + 0x14, 0x4B, 0, 0.8f, 0 },
    { D_ovl0B_06_80049558 + 0x1C, 0x1B, 0, 0.7f, 3 },
    { D_ovl0B_06_80049558 + 0x4C, 0x1C, 0, 0.5f, 0 },
    { D_ovl0B_06_80049558 + 0x64, 0x1E, 0, 0.9f, 3 },
    { D_ovl0B_06_80049558 + 0x88, 0x37, 0, 0.9f, 0 },
    { D_ovl0B_06_80049558 + 0x9C, 0x28, 0, 0.65f, 0 },
    { D_ovl0B_06_80049558 + 0xB8, 0x1C, 0, 0.54f, 3 },
    { D_ovl0B_06_80049558 + 0xFC, 0x17, 0, 0.54f, 0 },
    { D_ovl0B_06_80049558 + 0x120, 0x4B, 0, 0.9f, 0 },
    { D_ovl0B_06_800497C4 + 0x4, 0x33, 0, 0.9f, 0 },
    { D_ovl0B_06_800497C4 + 0x18, 0x27, 0, 0.9f, 0 },
    { D_ovl0B_06_80049558 + 0x1C0, 0x1A, 0, 0.6f, 0 },
    { D_ovl0B_06_800497C4 + 0x4C, 0x1E, 0, 0.55f, 0 },
    { D_ovl0B_06_800497C4 + 0x70, 0x23, 0, 0.9f, 3 },
    { D_ovl0B_06_800497C4 + 0x30, 0x23, 0, 0.7f, 0 },
    { D_ovl0B_06_800497C4 + 0x94, 0x2D, 0, 0.59f, 0 },
    { D_ovl0B_06_800497C4 + 0xB0, 0x20, 0, 0.7f, 3 },
    { D_ovl0B_06_800497C4 + 0xE0, 0x37, 0, 0.8f, 2 },
    { D_ovl0B_06_800497C4 + 0xE0, 0x37, 0, 0.8f, 3 },
    { D_ovl0B_06_800497C4 + 0x104, 0x4B, 0, 0.8f, 0 },
    { D_ovl0B_06_800497C4 + 0x118, 0x28, 0, 0.8f, 2 }
};
Pair_ovl0B_06 D_ovl0B_06_8004A3E4[4] = {
    { 0xB4, 0, 0.8f },
    { 0xA8, 0, 0.8f },
    { 0x50, 0, 0.8f },
    { 0xAE, 0, 0.8f }
};
s32 D_ovl0B_06_8004A404 = 0;
s32 D_ovl0B_06_8004A408 = 0;
s32 D_ovl0B_06_8004A40C = 0;
s32 D_ovl0B_06_8004A410 = 0;
Item_ovl0B_06 D_ovl0B_06_8004A414 = { D_ovl0B_06_80049558 + 0x198, 0x5F, 0x64, 0.8f, 1.0f, 0 };
Item_ovl0B_06 D_ovl0B_06_8004A428 = { D_ovl0B_06_80049558 + 0x1A8, 0x3F, 0x64, 0.75f, 1.0f, 0 };
Item_ovl0B_06 D_ovl0B_06_8004A43C = { D_ovl0B_06_80049558 + 0x9C, 0x28, 0x64, 0.65f, 1.0f, 0 };
Item_ovl0B_06 D_ovl0B_06_8004A450 = { D_ovl0B_06_80049558 + 0x130, 0x22, 0x3C, 0.75f, 0.85f, 0 };
Item_ovl0B_06 D_ovl0B_06_8004A464 = { D_ovl0B_06_80049558 + 0x1C0, 0x24, 0x64, 0.55f, 1.0f, 0 };
UnkStructA_40 *D_ovl0B_06_8004A478 = NULL;
s32 D_ovl0B_06_8004A47C = -1;
s32 D_ovl0B_06_8004A480[4] = { 0, 0, 0, 0 };

/* @80047DE4 */
void func_ovl0B_06_80047DE4(s32 arg0, Gfx_ovl0B_06 **arg1) {
    func_ovl0B_06_80047B98(arg1, &D_ovl0B_06_80049CAC[5]);
}

/* @80047DB8 */
void func_ovl0B_06_80047DB8(s32 arg0, Gfx_ovl0B_06 **arg1) {
    func_ovl0B_06_80047B98(arg1, &D_ovl0B_06_80049CAC[4]);
}


/* @80047D8C */
void func_ovl0B_06_80047D8C(s32 arg0, Gfx_ovl0B_06 **arg1) {
    func_ovl0B_06_80047B98(arg1, &D_ovl0B_06_80049CAC[3]);
}


/* @80047D60 */
void func_ovl0B_06_80047D60(s32 arg0, Gfx_ovl0B_06 **arg1) {
    func_ovl0B_06_80047B98(arg1, &D_ovl0B_06_80049CAC[2]);
}


/* @80047D34 */
void func_ovl0B_06_80047D34(s32 arg0, Gfx_ovl0B_06 **arg1) {
    func_ovl0B_06_80047B98(arg1, &D_ovl0B_06_80049CAC[1]);
}


/* @80047D08 */
void func_ovl0B_06_80047D08(s32 arg0, Gfx_ovl0B_06 **arg1) {
    func_ovl0B_06_80047D00();
    func_ovl0B_06_80047B98(arg1, &D_ovl0B_06_80049CAC[0]);
}


/* @80047D00 */
static void func_ovl0B_06_80047D00(void) {
}


/* @80047B98 */
static void func_ovl0B_06_80047B98(Gfx_ovl0B_06 **arg0, Box_ovl0B_06 *box) {
    Gfx_ovl0B_06 *gfx = *arg0;

    func_ovl0B_06_80047B38();
    func_ovl0B_06_80047B40();
    func_ovl0B_06_80047B48();
    func_ovl0B_06_80047B50();
    func_ovl0B_06_80047B58();
    func_ovl0B_06_80047B60();
    func_ovl0B_06_80047B68();
    func_ovl0B_06_80047B70();
    func_ovl0B_06_80047B78();
    func_ovl0B_06_80047B80();
    func_ovl0B_06_80047B88();
    func_ovl0B_06_80047B90();
    { Gfx_ovl0B_06 *g = gfx++; g->w0 = 0xFA000000; g->w1 = ((box->unk4 & 0xFF) << 24) | ((box->unk8 & 0xFF) << 16) | ((box->unkC & 0xFF) << 8) | (box->unk10 & 0xFF); }
    { Gfx_ovl0B_06 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFDF6FB; }
    { Gfx_ovl0B_06 *g = gfx++; g->w0 = 0xF7000000; g->w1 = 0x10001; }
    { Gfx_ovl0B_06 *g = gfx++; g->w0 = 0xF6000000 | (((box->unk2C + (s32) box->unk34) & 0x3FF) << 14) | (((box->unk30 + (s32) (box->unk34 * box->unk20)) & 0x3FF) << 2); g->w1 = (((box->unk2C - (s32) box->unk34) & 0x3FF) << 14) | (((box->unk30 - (s32) (box->unk34 * box->unk20)) & 0x3FF) << 2); }
    *arg0 = gfx;
}


/* @80047B38 */
static void func_ovl0B_06_80047B38(void) {
}

static void func_ovl0B_06_80047B40(void) {
}

static void func_ovl0B_06_80047B48(void) {
}

static void func_ovl0B_06_80047B50(void) {
}

static void func_ovl0B_06_80047B58(void) {
}

static void func_ovl0B_06_80047B60(void) {
}

static void func_ovl0B_06_80047B68(void) {
}

static void func_ovl0B_06_80047B70(void) {
}

static void func_ovl0B_06_80047B78(void) {
}

static void func_ovl0B_06_80047B80(void) {
}

static void func_ovl0B_06_80047B88(void) {
}

static void func_ovl0B_06_80047B90(void) {
}


/* @80047B20 */
void func_ovl0B_06_80047B20(void) {
    D_ovl0B_06_8004A5B4 = -1;
    D_ovl0B_06_8004A5B8 = -1;
}


/* @80047AC4 */
void func_ovl0B_06_80047AC4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0B_06_80048998(D_ovl0B_06_8004A5C0.x, D_ovl0B_06_8004A5C0.y, D_ovl0B_06_8004A5C0.z);
    func_ovl0B_06_800489B8(arg0, arg1, arg2);
    func_ovl0B_06_80048CC8(180);
}


/* @80047A7C */
void func_ovl0B_06_80047A7C(f32 arg0) {
    f32 sp1C;

    func_ovl0B_06_800489C0(&sp1C, NULL, NULL);
    func_ovl0B_06_800489B8(sp1C + arg0, 32768.0f, 32768.0f);
}


/* @80047A48 */
void func_ovl0B_06_80047A48(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0B_06_80049250(arg0, p->unk10, p->unk14, p->unk18);
}


/* @800478D4 */
void func_ovl0B_06_800478D4(void) {
    s32 count = 0;
    s32 on = 1;

    while (TRUE) {
        D_ovl0B_06_8004A478->unk20 += 1.0f;
        if (D_ovl0B_06_8004A478->unk20 >= 360.0f) {
            D_ovl0B_06_8004A478->unk20 -= 360.0f;
        }
        if (D_ovl0B_06_8004A410 == 1) {
            count++;
            if (on && count >= 16) {
                on = 0;
                count = 0;
            } else if (!on && count >= 61) {
                on = 1;
                count = 0;
            }
            if (count == 0) {
                func_ovl0B_06_80047880(on);
            }
        } else if (D_ovl0B_06_8004A410 == 2) {
            func_ovl0B_06_80047880(1);
        }
        func_ovl0B_06_80048CF0();
    }
}


/* @80047880 */
static void func_ovl0B_06_80047880(s32 arg0) {
    UnkStructA_40 *obj = func_ovl0B_06_800490C8(D_ovl0B_06_8004A650[0]);

    if (arg0 != 0) {
        obj->unkC |= 1;
    } else {
        obj->unkC &= ~1;
    }
}


/* @8004747C */
void func_ovl0B_06_8004747C(void) {
    s32 loop;
    s32 sel;
    s32 state;
    s32 r;
    s32 slot;

    loop = 1;
    sel = 0;
    state = 10;
    D_ovl0B_06_80049924 = -1;
    do {
        r = func_ovl0B_06_80045F20(sel & 0xF, &D_ovl0B_06_8004A254, &D_ovl0B_06_8004A244, 4);
        if ((r & 0xF0) != 0x30) {
            slot = r & 0xF;
            if (slot == 3) {
                sel = (r & 0xF0) | func_ovl0B_06_80047030();
            } else {
                loop = 0;
                D_ovl0B_06_80049924 = slot;
                state = func_ovl0B_06_80049368(slot, 0);
                if (state == 10) {
                    sel = r;
                    state = func_ovl0B_06_80046868(D_ovl0B_06_80049924);
                    if (state == 10) {
                        loop = 1;
                    } else {
                        sel = 1;
                    }
                } else {
                    D_ovl0B_06_80049924 = slot;
                    sel = 2;
                }
            }
        } else {
            loop = 0;
            sel = 3;
        }
        func_ovl0B_06_80048CF0();
    } while (loop != 0);
    switch (sel) {
        case 1:
            func_ovl0B_06_80048CA8(func_ovl0B_06_8004473C, NULL, 0, 0, 0x130);
            func_ovl0B_06_80048CF0();
            func_ovl0B_06_800464C0(0);
            D_ovl0B_06_8004992C = 0x2FC8;
            func_ovl0B_06_80048CF0();
            func_ovl0B_06_80049378(D_ovl0B_06_80049924);
            func_ovl0B_06_80048EF0();
            func_ovl0B_06_80049380(state);
            if (func_ovl0B_06_80049388() != 0) {
                func_ovl0B_06_80046558(state, 0);
            }
            func_ovl0B_06_800482B0(0);
            if (func_ovl0B_06_80049370() != 0) {
                D_ovl0B_06_8004992C = 0;
                func_ovl0B_06_80048CF0();
                func_ovl0B_06_800465E0(0x3C, D_ovl0B_06_80049E44[4].unk0);
                func_ovl0B_06_800465E0(0x3C, D_ovl0B_06_80049E44[5].unk0);
                func_ovl0B_06_800465E0(0x3C, D_ovl0B_06_80049E44[6].unk0);
                func_ovl0B_06_800465E0(0x3C, D_ovl0B_06_80049E44[7].unk0);
                FADE_LABELS(0, D_ovl0B_06_80049AEC, 2);
                func_ovl0B_06_80046634(0);
                D_ovl0B_06_8004992C = 0x44C8;
                func_ovl0B_06_80049230(0x18);
                func_ovl0B_06_80048CC8(0x32);
                func_ovl0B_06_80048CC8(0xC8);
                func_ovl0B_06_80046634(1);
            }
            func_ovl0B_06_80048840(D_ovl0B_06_80049E44[4].unk0);
            func_ovl0B_06_80048840(D_ovl0B_06_80049E44[5].unk0);
            func_ovl0B_06_80048840(D_ovl0B_06_80049E44[6].unk0);
            func_ovl0B_06_80048840(D_ovl0B_06_80049E44[7].unk0);
            for (slot = 0; slot < 2; slot++) {
                func_ovl0B_06_80049098(D_ovl0B_06_80049AEC[slot].unk4);
            }
            func_ovl0B_06_80048250(0x1A, 0x10, 4);
            D_ovl0B_06_8004992C = 0x400;
            break;
        case 2:
            func_ovl0B_06_80049378(D_ovl0B_06_80049924);
            if (func_ovl0B_06_80049388() != 0) {
                func_ovl0B_06_80046558(0, 1);
            }
            func_ovl0B_06_800482B0(1);
            func_ovl0B_06_80048250(0x21, 0x10, 0);
            break;
        case 3:
            func_ovl0B_06_80048250(0x20, 0x11, 0);
            break;
    }
    func_ovl0B_06_80048CB8();
}


/* @80047030 */
static s32 func_ovl0B_06_80047030(void) {
    Label_ovl0B_06 *label;
    s32 loop;
    s32 sel;
    s32 slot;
    s32 side;
    s32 done;
    s32 keep;
    s32 n;
    s32 held;
    s32 pressed;
    s32 i;

    func_ovl0B_06_80047028();
    loop = 1;
    sel = 0;
    func_ovl0B_06_80048CA8(func_ovl0B_06_8004473C, NULL, 0, 0, 0x130);
    func_ovl0B_06_800464C0(0);
    func_ovl0B_06_80045C24(&D_ovl0B_06_80049A44[0], &D_ovl0B_06_80049A44[5], D_ovl0B_06_800494C8, -0x26, 0);
    func_ovl0B_06_800433B0(&D_ovl0B_06_80049A44[5]);
    do {
        sel = func_ovl0B_06_80045F20(sel & 0xF, &D_ovl0B_06_8004A264, &D_ovl0B_06_8004A244, 3);
        if ((sel & 0xF0) == 0x30) {
            loop = 0;
        } else {
            slot = sel & 0xF;
            if (func_ovl0B_06_80049368(slot, 0) == 10) {
                D_ovl0B_06_8004992C = 0x1064;
                func_ovl0B_06_80049230(0x18);
                func_ovl0B_06_80048CC8(0x32);
            } else {
                keep = 1;
                side = 1;
                done = 0;
                D_ovl0B_06_8004992C = 0;
                n = 3;
                loop = 0;
                for (i = 0; i < 3; i++) {
                    func_ovl0B_06_80043404(&D_ovl0B_06_80049B40[i]);
                }
                func_ovl0B_06_80044BA0(slot, &D_ovl0B_06_8004A264);
                func_ovl0B_06_80046F14(0, 0, 0, 2);
                do {
                    held = func_ovl0B_06_80049060();
                    pressed = func_ovl0B_06_80048268();
                    if ((held & 0x200) && side == 1) {
                        side = 0;
                        func_ovl0B_06_80046F14(0, 0, 0, 1);
                        func_ovl0B_06_80046F14(1, 0, 0, 2);
                        func_ovl0B_06_80049230(0);
                        func_ovl0B_06_80048CC8(5);
                    } else if ((held & 0x100) && side == 0) {
                        side = 1;
                        func_ovl0B_06_80046F14(1, 0, 0, 1);
                        func_ovl0B_06_80046F14(0, 0, 0, 2);
                        func_ovl0B_06_80049230(0);
                        func_ovl0B_06_80048CC8(5);
                    } else if ((pressed & 0x8000) || (pressed & 0x1000)) {
                        done = 1;
                        if (side == 0) {
                            for (label = D_ovl0B_06_80049B40; label != D_ovl0B_06_80049B94; label++) {
                                label->unk18->unkC |= 1;
                            }
                            keep = 0;
                            D_ovl0B_06_8004992C = 0x43C8;
                            func_ovl0B_06_80048CF0();
                            func_ovl0B_06_80049230(1);
                            func_ovl0B_06_80048CC8(0xF);
                            func_ovl0B_06_80049378(slot);
                            func_ovl0B_06_80049380(10);
                            if (func_ovl0B_06_80049390() != 0) {
                                D_ovl0B_06_8004992C = 0;
                                func_ovl0B_06_80048CF0();
                                func_ovl0B_06_80046634(0);
                                D_ovl0B_06_8004992C = 0x44C8;
                                func_ovl0B_06_80049230(0x18);
                                func_ovl0B_06_80048CC8(0x32);
                                func_ovl0B_06_80048CC8(0xC8);
                                func_ovl0B_06_80046634(1);
                            }
                            func_ovl0B_06_80043280();
                            for (i = 0; i < 6; i++) {
                                func_ovl0B_06_80049098(D_ovl0B_06_80049A44[i].unk4);
                            }
                            func_ovl0B_06_800430F0(1);
                            func_ovl0B_06_80043480(1);
                            done = 1;
                            func_ovl0B_06_80043834();
                        }
                    } else if (pressed & 0x4000) {
                        done = 1;
                        func_ovl0B_06_80049230(2);
                        func_ovl0B_06_80048CC8(0xA);
                    }
                    func_ovl0B_06_80048CF0();
                } while (done == 0);
                func_ovl0B_06_80044BA0(slot, &D_ovl0B_06_8004A244);
                for (i = 0; i < n; i++) {
                    func_ovl0B_06_80049098(D_ovl0B_06_80049B40[i].unk4);
                }
            }
        }
        func_ovl0B_06_80048CF0();
    } while (loop != 0);
    slot = sel & 0xF;
    func_ovl0B_06_80045C24(&D_ovl0B_06_80049A44[0], &D_ovl0B_06_80049A44[5], D_ovl0B_06_80049480, 0, 0);
    func_ovl0B_06_800433B0(&D_ovl0B_06_80049A44[5]);
    D_ovl0B_06_8004992C = 0x400;
    func_ovl0B_06_800464C0(1);
    return slot;
}


/* @80047028 */
static void func_ovl0B_06_80047028(void) {
}


/* @80046F14 */
static void func_ovl0B_06_80046F14(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Label_ovl0B_06 *label;
    f32 scale = 0.0f;
    s16 dx = 0;
    s16 dy = 0;
    u8 flag;

    switch (arg0 * 16 + arg3) {
        case 1:
            scale = 0.5f;
            dx = -10;
            dy = -5;
            flag = 0;
            break;
        case 17:
            scale = -0.5f;
            dx = 10;
            dy = 5;
            flag = 1;
            break;
        case 2:
            scale = 0.5f;
            dy = -5;
            flag = 0;
            dx = -10;
            break;
        case 18:
            scale = -0.5f;
            dy = 5;
            flag = 1;
            dx = 10;
            break;
    }
    label = &D_ovl0B_06_80049B40[arg3];
    func_ovl0B_06_800490C0(label->unk4, scale, scale);
    func_ovl0B_06_800490B0(label->unk4, dx, dy);
    func_ovl0B_06_800490F0(label->unk4, label->unk0, flag);
    label->unk18 = func_ovl0B_06_800490C8(label->unk4);
}


/* @80046868 */
static s32 func_ovl0B_06_80046868(s32 slot) {
    Label_ovl0B_06 *label;
    s32 ret;
    s32 loop;
    s32 result;
    s32 side;
    s32 held;
    s32 pressed;
    s32 y;
    f32 dy;
    f32 fy;
    f32 t;
    f32 s;
    s32 i;

    func_ovl0B_06_80046850();
    func_ovl0B_06_80046858();
    func_ovl0B_06_80046860();
    ret = 10;
    func_ovl0B_06_800464C0(0);
    label = &D_ovl0B_06_80049A44[slot];
    label[1].unk18->unkC |= 1;
    for (i = 0; i < 2; i++) {
        func_ovl0B_06_80043404(&D_ovl0B_06_80049AEC[i]);
    }
    func_ovl0B_06_80045C24(&D_ovl0B_06_80049A44[0], &D_ovl0B_06_80049A44[5], D_ovl0B_06_800494A4, -0x1C, 0);
    func_ovl0B_06_800433B0(&D_ovl0B_06_80049A44[5]);
    dy = slot * 40;
    loop = 0;
    do {
        t = 0.0f;
        result = 0;
        side = 0;
        func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[4], &D_ovl0B_06_8004A0C4[10], dy);
        func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[5], &D_ovl0B_06_8004A0C4[12], dy);
        func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[6], &D_ovl0B_06_8004A0C4[13], dy);
        func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[7], &D_ovl0B_06_8004A0C4[11], dy);
        func_ovl0B_06_80044BA0(slot, &D_ovl0B_06_8004A274);
        D_ovl0B_06_80049E44[5].unk0->unkC &= ~1;
        D_ovl0B_06_80049E44[6].unk0->unkC |= 1;
        y = slot * 40 + 0x3E;
        fy = slot * 40 + 0x32;
        while (TRUE) {
            held = func_ovl0B_06_80049060();
            pressed = func_ovl0B_06_80048268();
            s = func_ovl0B_06_80048E50(t);
            if (side == 0) {
                t += 3.0f;
                if (t >= 360.0f) {
                    t -= 360.0f;
                }
                func_ovl0B_06_800490B8(D_ovl0B_06_80049AEC[0].unk4, 0.55f, (s * 0.5f + 1.1f) * 0.7f);
                func_ovl0B_06_800490A8(D_ovl0B_06_80049AEC[0].unk4, 0x5D, (u32) (fy + 12.0f * (1.0f - s * 0.8f)));
                func_ovl0B_06_800490B8(D_ovl0B_06_80049AEC[1].unk4, 0.55f, 0.7f);
                func_ovl0B_06_800490A8(D_ovl0B_06_80049AEC[1].unk4, 0xF5, y);
            } else {
                t += 7.0f;
                if (t >= 360.0f) {
                    t -= 360.0f;
                }
                func_ovl0B_06_800490B8(D_ovl0B_06_80049AEC[0].unk4, 0.55f, 0.7f);
                func_ovl0B_06_800490A8(D_ovl0B_06_80049AEC[0].unk4, 0x5D, y);
                func_ovl0B_06_800490B8(D_ovl0B_06_80049AEC[1].unk4, 0.55f, (s * 0.7f + 1.1f) * 0.7f);
                func_ovl0B_06_800490A8(D_ovl0B_06_80049AEC[1].unk4, 0xF5, (u32) (fy + 12.0f * (1.0f - s)));
            }
            if ((held & 0x200) && side == 1) {
                t = 0.0f;
                side = 0;
                D_ovl0B_06_80049E44[5].unk0->unkC &= ~1;
                D_ovl0B_06_80049E44[6].unk0->unkC |= 1;
                func_ovl0B_06_80049230(0);
                func_ovl0B_06_80048CC8(5);
            } else if ((held & 0x100) && side == 0) {
                t = 0.0f;
                side = 1;
                D_ovl0B_06_80049E44[5].unk0->unkC |= 1;
                D_ovl0B_06_80049E44[6].unk0->unkC &= ~1;
                func_ovl0B_06_80049230(0);
                func_ovl0B_06_80048CC8(5);
            } else if (pressed & 0x8000) {
                result = 0x10;
                func_ovl0B_06_80049230(1);
                func_ovl0B_06_80048CC8(0xF);
            } else if (pressed & 0x1000) {
                result = 0x20;
                func_ovl0B_06_80049230(1);
                func_ovl0B_06_80048CC8(0xF);
            } else if (pressed & 0x4000) {
                result = 0x30;
                func_ovl0B_06_80049230(2);
                func_ovl0B_06_80048CC8(0xA);
            }
            func_ovl0B_06_80048CF0();
            if (result != 0) {
                break;
            }
        }
        if (result == 0x30) {
            func_ovl0B_06_80048840(D_ovl0B_06_80049E44[4].unk0);
            func_ovl0B_06_80048840(D_ovl0B_06_80049E44[5].unk0);
            func_ovl0B_06_80048840(D_ovl0B_06_80049E44[6].unk0);
            func_ovl0B_06_80048840(D_ovl0B_06_80049E44[7].unk0);
            func_ovl0B_06_80044BA0(slot, &D_ovl0B_06_8004A244);
            D_ovl0B_06_80049928 = 0;
        } else {
            D_ovl0B_06_80049928 = 1;
        }
        result |= side;
        if ((result & 0xF0) != 0x30) {
            if (!(result & 0xF)) {
                ret = 0;
            } else {
                ret = 1;
            }
        }
        func_ovl0B_06_80048CF0();
    } while (loop != 0);
    if ((result & 0xF0) == 0x30) {
        func_ovl0B_06_80045C24(&D_ovl0B_06_80049A44[0], &D_ovl0B_06_80049A44[5], D_ovl0B_06_80049480, 0, 0);
        func_ovl0B_06_800433B0(&D_ovl0B_06_80049A44[5]);
        func_ovl0B_06_800464C0(1);
        label[1].unk18->unkC &= ~1;
        for (i = 0; i < 2; i++) {
            func_ovl0B_06_80049098(D_ovl0B_06_80049AEC[i].unk4);
        }
    }
    return ret;
}


/* @80046634 */
static void func_ovl0B_06_80046860(void) {
}

static void func_ovl0B_06_80046858(void) {
}

static void func_ovl0B_06_80046850(void) {
}

static void func_ovl0B_06_80046634(s32 arg0) {
    s16 alpha;
    s32 i;
    s32 j;

    func_ovl0B_06_80046624();
    func_ovl0B_06_8004662C();
    if (arg0 & 1) {
        D_ovl0B_06_80049CAC[4].unk0->unkC |= 1;
        D_ovl0B_06_80049CAC[4].unk0->unk18 = -100.0f;
    } else {
        D_ovl0B_06_80049CAC[4].unk0->unkC &= ~1;
        D_ovl0B_06_80049CAC[4].unk0->unk18 = 20.0f;
        func_ovl0B_06_80044BA0(4, &D_ovl0B_06_8004A284);
    }
    FADE_LABELS(arg0, D_ovl0B_06_80049A44, 4);
    FADE_LABELS(arg0, D_ovl0B_06_8004999C, 3);
    FADE_SLOTS(arg0)
    alpha = arg0 == 0 ? 0x3C : 0xFF;
    for (i = 0; i < 3; i++) {
        if (D_ovl0B_06_8004A5D0[i] == 1) {
            func_ovl0B_06_800465E0(alpha, D_ovl0B_06_80049F20[i][0].unk0);
        }
    }
    alpha = arg0 == 0 ? 0x3C : 0xFF;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 6; j++) {
            if (D_ovl0B_06_8004A5E0[i].unk[j] == 1) {
                func_ovl0B_06_800465E0(alpha, D_ovl0B_06_80049F20[i][j + 1].unk0);
            }
        }
    }
}

/* @800465E0 */
static void func_ovl0B_06_8004662C(void) {
}

static void func_ovl0B_06_80046624(void) {
}

static void func_ovl0B_06_800465E0(s16 alpha, UnkStructA_40 *obj) {
    if (alpha == 0xFF) {
        obj->unk36 = 0xFF;
        obj->unkC &= ~0x80;
    } else {
        obj->unk36 = alpha;
        obj->unkC |= 0x80;
    }
}


/* @80046558 */
static void func_ovl0B_06_80046558(s32 arg0, s32 arg1) {
    func_ovl0B_06_80049380(arg0);
    if (arg1 != 0) {
        func_ovl0B_06_80048CA8(func_ovl0B_06_8004473C, NULL, 0, 0, 0x130);
        func_ovl0B_06_80048CF0();
        func_ovl0B_06_800464C0(0);
        func_ovl0B_06_80044E48(0x42C8, 0x18);
        D_ovl0B_06_8004992C = 0x400;
        func_ovl0B_06_800464C0(1);
    } else {
        func_ovl0B_06_80044E48(0x40C8, 0x18);
    }
}


/* @800464C0 */
static void func_ovl0B_06_800464C0(s32 arg0) {
    if (arg0 == 0) {
        func_ovl0B_06_800430F0(2);
        D_ovl0B_06_80049CAC[3].unk0->unkC |= 1;
        D_ovl0B_06_80049A44[4].unk18->unkC |= 1;
    } else {
        func_ovl0B_06_800430F0(3);
        D_ovl0B_06_80049CAC[3].unk0->unkC &= ~1;
        D_ovl0B_06_80049A44[4].unk18->unkC &= ~1;
    }
}


/* @8004616C */
void func_ovl0B_06_8004616C(void) {
    s32 loop;
    s32 sel;
    s32 inner;
    s32 sub;
    s32 slot;

    func_ovl0B_06_80046164();
    loop = 1;
    sel = 0;
    do {
        sel = func_ovl0B_06_80045F20(sel & 0xF, &D_ovl0B_06_8004A254, &D_ovl0B_06_8004A244, 5);
        if ((sel & 0xF0) != 0x30) {
            if ((sel & 0xF) == 3) {
                inner = 1;
                sub = 0;
                sel &= 0xF0;
                func_ovl0B_06_80048CA8(func_ovl0B_06_8004473C, NULL, 0, 0, 0x130);
                func_ovl0B_06_80044908(0);
                func_ovl0B_06_80045C24(&D_ovl0B_06_80049B94[0], &D_ovl0B_06_80049B94[5], D_ovl0B_06_80049534, -0x28, 0);
                func_ovl0B_06_800433B0(&D_ovl0B_06_80049B94[5]);
                do {
                    sub = func_ovl0B_06_80045F20(sub & 0xF, &D_ovl0B_06_8004A264, &D_ovl0B_06_8004A244, 3);
                    if ((sub & 0xF0) == 0x30) {
                        inner = 0;
                    } else {
                        slot = sub & 0xF;
                        if (func_ovl0B_06_80049368(slot, 0) == 10) {
                            D_ovl0B_06_8004992C = 0x1064;
                            func_ovl0B_06_80049230(0x18);
                            func_ovl0B_06_80048CC8(0x32);
                        } else {
                            D_ovl0B_06_8004992C = 0;
                            inner = 0;
                            func_ovl0B_06_80048CF0();
                            func_ovl0B_06_80045D28(slot, 0);
                        }
                    }
                    func_ovl0B_06_80048CF0();
                } while (inner != 0);
                func_ovl0B_06_80044908(1);
                func_ovl0B_06_80045C24(&D_ovl0B_06_80049B94[0], &D_ovl0B_06_80049B94[5], D_ovl0B_06_80049508, 0, 0);
                func_ovl0B_06_800433B0(&D_ovl0B_06_80049B94[5]);
                D_ovl0B_06_8004992C = 0x400;
                sel |= sub & 0xF;
            } else if ((sel & 0xF) == 4) {
                func_ovl0B_06_800459D8(0);
            } else {
                slot = sel & 0xF;
                if (func_ovl0B_06_80049368(slot, 0) == 10) {
                    func_ovl0B_06_80049230(0x18);
                    func_ovl0B_06_80048CC8(0x32);
                } else {
                    loop = 0;
                    func_ovl0B_06_80049378(slot);
                    if (func_ovl0B_06_80049388() != 0) {
                        func_ovl0B_06_80049380(NULL);
                        func_ovl0B_06_80048CA8(func_ovl0B_06_8004473C, NULL, 0, 0, 0x130);
                        func_ovl0B_06_80048CF0();
                        func_ovl0B_06_80044908(0);
                        func_ovl0B_06_80044BE4(0);
                        func_ovl0B_06_80044E48(0x41C8, 0x18);
                        D_ovl0B_06_8004992C = 0x400;
                        func_ovl0B_06_80044BE4(1);
                        func_ovl0B_06_80044908(1);
                    }
                    func_ovl0B_06_80048250(0x25, 0x10, 0);
                }
            }
        } else {
            loop = 0;
            func_ovl0B_06_80048250(0x20, 0x11, 0);
        }
        func_ovl0B_06_80048CF0();
    } while (loop != 0);
    func_ovl0B_06_80048CB8();
}


/* @80046164 */
static void func_ovl0B_06_80046164(void) {
}


/* @80045F20 */
static s32 func_ovl0B_06_80045F20(s32 arg0, Col_ovl0B_06 *on, Col_ovl0B_06 *off, s32 n) {
    s32 held;
    s32 pressed;
    s32 ret = 0;
    s32 sel = arg0;

    func_ovl0B_06_80044BA0(sel, on);
    do {
        held = func_ovl0B_06_80049060();
        pressed = func_ovl0B_06_80048268();
        if (sel < 3 && (held & 0x400)) {
            if (sel < n - 1) {
                func_ovl0B_06_80044BA0(sel, off);
                sel++;
                func_ovl0B_06_80044BA0(sel, on);
                func_ovl0B_06_80049230(0);
                func_ovl0B_06_80048CC8(5);
            }
        } else if (held & 0x800) {
            if (sel > 0) {
                if (sel == 4) {
                    func_ovl0B_06_80044BA0(sel + 1, off);
                    sel -= 2;
                    func_ovl0B_06_80044BA0(sel, on);
                } else {
                    func_ovl0B_06_80044BA0(sel, off);
                    sel--;
                    func_ovl0B_06_80044BA0(sel, on);
                }
                func_ovl0B_06_80049230(0);
                func_ovl0B_06_80048CC8(5);
            }
        } else if (n == 5 && sel == 3 && (held & 0x100)) {
            func_ovl0B_06_80044BA0(sel, off);
            func_ovl0B_06_80044BA0(sel + 2, on);
            sel++;
            func_ovl0B_06_80049230(0);
            func_ovl0B_06_80048CC8(5);
        } else if (n == 5 && sel == 4 && (held & 0x200)) {
            func_ovl0B_06_80044BA0(sel + 1, off);
            sel--;
            func_ovl0B_06_80044BA0(sel, on);
            func_ovl0B_06_80049230(0);
            func_ovl0B_06_80048CC8(5);
        } else if (pressed & 0x8000) {
            ret = 0x10;
            func_ovl0B_06_80049230(1);
            func_ovl0B_06_80048CC8(0xF);
        } else if (pressed & 0x1000) {
            ret = 0x20;
            func_ovl0B_06_80049230(1);
            func_ovl0B_06_80048CC8(0xF);
        } else if (pressed & 0x4000) {
            ret = 0x30;
            func_ovl0B_06_80049230(2);
            func_ovl0B_06_80048CC8(0xA);
        }
        func_ovl0B_06_80048CF0();
    } while (ret == 0);
    if (sel != 4) {
        func_ovl0B_06_80044BA0(sel, off);
    }
    return ret | sel;
}


/* @80045D28 */
static void func_ovl0B_06_80045D28(s32 arg0, s32 arg1) {
    s32 slot;
    s32 state;

    func_ovl0B_06_80045D20();
    D_ovl0B_06_8004992C = 0x29C8;
    func_ovl0B_06_80048CF0();
    state = func_ovl0B_06_80048E00(0);
    if (state != 1) {
        D_ovl0B_06_8004992C = 0;
    }
    switch (state) {
        case 0:
            func_ovl0B_06_80044E48(0x21C8, 0x18);
            break;
        case 1:
            state = func_ovl0B_06_80045100(func_ovl0B_06_80048E28(0, &slot));
            if (state == 7 || state == 8 || state == 9) {
                func_ovl0B_06_80044BE4(2);
                func_ovl0B_06_80048E48(arg0);
                if (func_ovl0B_06_80045794(arg0, 0, 0, 1) == 1) {
                    while (func_ovl0B_06_80045794(arg0, 0, 1, 2) == 1) {
                    }
                }
                func_ovl0B_06_80044BE4(3);
                D_ovl0B_06_8004992C = 0;
            } else {
                func_ovl0B_06_80044E48(0x2564, 0x18);
            }
            break;
        case 2:
            func_ovl0B_06_80045D28(arg0, 0);
            break;
        case 5:
            if (func_ovl0B_06_80045054() != 0) {
                if (arg1 == 0) {
                    func_ovl0B_06_80045D28(arg0, 1);
                } else {
                    func_ovl0B_06_80044E48(0x2578, 0x18);
                }
            }
            break;
        default:
            func_ovl0B_06_80044E48(0x2564, 0x18);
            break;
    }
}


/* @80045C24 */
static void func_ovl0B_06_80045D20(void) {
}

static void func_ovl0B_06_80045C24(Label_ovl0B_06 *a, Label_ovl0B_06 *b, u8 *str, s16 dx, s16 dy) {
    s32 ta;
    s32 tb;

    ta = func_ovl0B_06_800490E8(str, a->unk8 + dx, a->unkA + dy, a->unkC, a->unk10, a->unk14);
    tb = func_ovl0B_06_800490E8(str, b->unk8 + dx, b->unkA + dy, b->unkC, b->unk10, b->unk14);
    func_ovl0B_06_80049098(a->unk4);
    func_ovl0B_06_80049098(b->unk4);
    a->unk4 = ta;
    b->unk4 = tb;
    a->unk18 = func_ovl0B_06_800490C8(a->unk4);
    b->unk18 = func_ovl0B_06_800490C8(b->unk4);
}


/* @800459D8 */
static void func_ovl0B_06_800459D8(s32 arg0) {
    s32 slot;
    s32 state;

    func_ovl0B_06_800459D0();
    slot = -1;
    func_ovl0B_06_80044908(0);
    func_ovl0B_06_80048CA8(func_ovl0B_06_8004473C, NULL, 0, 0, 0x130);
    func_ovl0B_06_80048CF0();
    D_ovl0B_06_8004992C = 0x2AC8;
    func_ovl0B_06_80048CF0();
    state = func_ovl0B_06_80048E00(0);
    if (state != 1) {
        D_ovl0B_06_8004992C = 0;
    }
    switch (state) {
        case 1:
            if (func_ovl0B_06_80048E28(0, &slot) == 8) {
                func_ovl0B_06_80048E40(0);
                if (func_ovl0B_06_80048DF0(0) != 9) {
                    func_ovl0B_06_80044E48(0x2D78, 0x18);
                } else {
                    func_ovl0B_06_80044BE4(2);
                    func_ovl0B_06_80045794(slot, 0, 0, 0);
                    func_ovl0B_06_80044BE4(3);
                    D_ovl0B_06_8004992C = 0;
                }
            } else {
                func_ovl0B_06_80044E48(0x2478, 0x18);
            }
            break;
        case 2:
            if (arg0 == 0 || arg0 == 1) {
                D_ovl0B_06_8004992C = 0x400;
                func_ovl0B_06_800459D8(2);
            } else {
                func_ovl0B_06_80044E48(0x2578, 0x18);
            }
            break;
        case 5:
            if (func_ovl0B_06_80045054() != 0) {
                if (arg0 == 0) {
                    D_ovl0B_06_8004992C = 0x400;
                    func_ovl0B_06_800459D8(1);
                } else {
                    func_ovl0B_06_80044E48(0x2578, 0x18);
                }
            }
            break;
        case 0:
            func_ovl0B_06_80044E48(0x21C8, 0x18);
            break;
        default:
            func_ovl0B_06_80044E48(0x2EC8, 0x18);
            break;
    }
    func_ovl0B_06_80048CF0();
    D_ovl0B_06_8004992C = 0x400;
    func_ovl0B_06_80044908(1);
}


/* @800459D0 */
static void func_ovl0B_06_800459D0(void) {
}


/* @80045794 */
static s32 func_ovl0B_06_80045794(s32 arg0, s32 arg1, s32 arg2, s32 mode) {
    UnkStructA_40 *a;
    UnkStructA_40 *b;
    u8 *save;
    s32 ret;
    s32 i;

    save = func_ovl0B_06_80048E38();
    D_ovl0B_06_8004992C = 0;
    func_ovl0B_06_80045340(mode, save);
    ret = 0;
    if (D_ovl0B_06_8004A404 != 0 && (func_ovl0B_06_8004518C() & 0x8000)) {
        func_ovl0B_06_80049230(1);
        func_ovl0B_06_80048CC8(0xF);
        a = func_ovl0B_06_800490C8(D_ovl0B_06_8004A408);
        b = func_ovl0B_06_800490C8(D_ovl0B_06_8004A40C);
        a->unk36 = 0;
        a->unkC |= 0x80;
        b->unk36 = 0;
        b->unkC |= 0x80;
        if (mode == 0) {
            ret = func_ovl0B_06_80048E20(arg0);
        } else {
            ret = func_ovl0B_06_80048DF8(arg0, arg2);
        }
        switch (func_ovl0B_06_80045100(ret)) {
            case 9:
                if (mode == 0) {
                    func_ovl0B_06_80044E48(0x28C8, 2);
                } else {
                    D_ovl0B_06_8004A410 = 2;
                    func_ovl0B_06_80044E48(0x2764, 1);
                }
                break;
            case 13:
                ret = 1;
                break;
            case 2:
                ret = 3;
                break;
            case 8:
                ret = 1;
                break;
            case 7:
                func_ovl0B_06_80044E48(0x2578, 0x18);
                ret = 2;
                break;
            case 16:
                func_ovl0B_06_80044E48(0x2C78, 0x18);
                ret = 2;
                break;
            case 14:
            case 15:
                ret = 2;
                break;
        }
    } else {
        func_ovl0B_06_80049230(2);
        func_ovl0B_06_80048CC8(0xA);
    }
    func_ovl0B_06_80048CB0(D_ovl0B_06_8004A480[0]);
    func_ovl0B_06_800488D8(D_ovl0B_06_8004A47C);
    func_ovl0B_06_80048840(D_ovl0B_06_8004A478);
    for (i = 0; i < 4; i++) {
        func_ovl0B_06_80049098(D_ovl0B_06_8004A650[i]);
    }
    func_ovl0B_06_80049098(D_ovl0B_06_8004A408);
    func_ovl0B_06_80049098(D_ovl0B_06_8004A40C);
    func_ovl0B_06_80048CF0();
    func_ovl0B_06_800489B8(0.0f, 10.0f, 2200.0f);
    return ret;
}


/* @80045340 */
static void func_ovl0B_06_80045340(s32 arg0, u8 *save) {
    u8 *text;
    s16 x;
    f32 scale;
    u8 flag;
    u8 *dst;
    u8 *src;

    switch (arg0) {
        case 0:
            text = D_ovl0B_06_8004974C;
            x = 0x5F;
            flag = 0;
            D_ovl0B_06_8004A410 = 0;
            scale = 1.0f;
            break;
        case 1:
            text = D_ovl0B_06_8004975C;
            x = 0x1D;
            flag = 0;
            D_ovl0B_06_8004A410 = 0;
            scale = 0.6f;
            break;
        case 2:
            text = D_ovl0B_06_80049784;
            x = 0x50;
            flag = 2;
            D_ovl0B_06_8004A410 = 1;
            scale = 0.7f;
            break;
    }
    func_ovl0B_06_800489B8(354.5f, 10.8f, 833.0f);
    func_ovl0B_06_80048CF0();
    D_ovl0B_06_8004A478 = func_ovl0B_06_80048838(0x49, 1);
    D_ovl0B_06_8004A478->unk10 = -140.0f;
    D_ovl0B_06_8004A478->unk14 = -40.0f;
    D_ovl0B_06_8004A478->unk18 = 100.0f;
    D_ovl0B_06_8004A478->unk20 = 0.0f;
    func_ovl0B_06_80048860(D_ovl0B_06_8004A478, 0xC);
    for (x = 0; x < 0xC; x++) {
        func_ovl0B_06_80048868(D_ovl0B_06_8004A478, 0x4A, x, x);
    }
    func_ovl0B_06_80048888(D_ovl0B_06_8004A478, -1, 0);
    D_ovl0B_06_8004A478->unkC &= ~0x20;
    D_ovl0B_06_8004A478->unkC &= ~0x40;
    D_ovl0B_06_8004A47C = func_ovl0B_06_800488C8(D_ovl0B_06_8004A478, 0xF);
    func_ovl0B_06_80048300(D_ovl0B_06_8004A47C, 0, save[0x16]);
    func_ovl0B_06_80048300(D_ovl0B_06_8004A47C, 1, save[0x17]);
    func_ovl0B_06_80048300(D_ovl0B_06_8004A47C, 2, save[0x18]);
    func_ovl0B_06_80048300(D_ovl0B_06_8004A47C, 3, save[0x19]);
    for (dst = D_ovl0B_06_8004A640, src = save + 8; dst != D_ovl0B_06_8004A648; dst++, src++) {
        if ((*dst = *src) == 0) {
            break;
        }
    }
    *dst = 0;
    D_ovl0B_06_8004A650[0] = func_ovl0B_06_800490E8(text, x, 0x2E, 0.7f, scale, flag);
    D_ovl0B_06_8004A650[1] = func_ovl0B_06_800490E8(D_ovl0B_06_800497A4, 0x28, 0xD2, 0.5f, 0.5f, 4);
    D_ovl0B_06_8004A650[2] = func_ovl0B_06_800490E8(D_ovl0B_06_8004A640, (u32) (208.0f - func_ovl0B_06_800490E0(D_ovl0B_06_8004A640) * 0.8f / 2.0f), 0x78, 0.8f, 1.0f, 5);
    D_ovl0B_06_8004A650[3] = func_ovl0B_06_800490E8(D_ovl0B_06_80049738, 0x33, 0x14, 0.8f, 0.8f, 0);
    D_ovl0B_06_8004A404 = 0;
    D_ovl0B_06_8004A408 = func_ovl0B_06_800490E8(D_ovl0B_06_800497BC, 0x5F, 0xB2, 0.8f, 0.8f, 1);
    D_ovl0B_06_8004A40C = func_ovl0B_06_800490E8(D_ovl0B_06_800497C4, 0xB9, 0xA8, 1.5f, 1.5f, 0);
    func_ovl0B_06_800490C8(D_ovl0B_06_8004A650[1])->unkC |= 1;
    D_ovl0B_06_8004A480[0] = func_ovl0B_06_80048CA8(func_ovl0B_06_800478D4, NULL, 0, 0, 0x130);
}


/* @8004518C */
static s32 func_ovl0B_06_8004518C(void) {
    s32 held;
    s32 pressed;
    s32 a;
    s32 b;

    func_ovl0B_06_80045184();
    do {
        held = func_ovl0B_06_80049060();
        pressed = func_ovl0B_06_80048268() & 0xFFFF;
        if ((held & 0x200) || (held & 0x100)) {
            if (D_ovl0B_06_8004A404 == 1 && (held & 0x100)) {
                D_ovl0B_06_8004A404 = 0;
                a = func_ovl0B_06_800490E8(D_ovl0B_06_800497BC, 0x5F, 0xB2, 0.8f, 0.8f, 1);
                b = func_ovl0B_06_800490E8(D_ovl0B_06_800497C4, 0xB9, 0xA8, 1.5f, 1.5f, 0);
                func_ovl0B_06_80049098(D_ovl0B_06_8004A408);
                func_ovl0B_06_80049098(D_ovl0B_06_8004A40C);
                D_ovl0B_06_8004A408 = a;
                D_ovl0B_06_8004A40C = b;
                func_ovl0B_06_80049230(0);
                func_ovl0B_06_80048CC8(5);
            } else if (D_ovl0B_06_8004A404 == 0 && (held & 0x200)) {
                D_ovl0B_06_8004A404 = 1;
                a = func_ovl0B_06_800490E8(D_ovl0B_06_800497BC, 0x4B, 0xA8, 1.5f, 1.5f, 0);
                b = func_ovl0B_06_800490E8(D_ovl0B_06_800497C4, 0xC3, 0xB2, 0.8f, 0.8f, 1);
                func_ovl0B_06_80049098(D_ovl0B_06_8004A408);
                func_ovl0B_06_80049098(D_ovl0B_06_8004A40C);
                D_ovl0B_06_8004A408 = a;
                D_ovl0B_06_8004A40C = b;
                func_ovl0B_06_80049230(0);
                func_ovl0B_06_80048CC8(5);
            }
        }
        func_ovl0B_06_80048CF0();
    } while (!(pressed & 0x8000) && !(pressed & 0x4000));
    return pressed;
}


/* @80045184 */
static void func_ovl0B_06_80045184(void) {
}


/* @80045100 */
static s32 func_ovl0B_06_80045100(s32 arg0) {
    func_ovl0B_06_800450F8();
    switch (arg0) {
        case 0:
            func_ovl0B_06_80044E48(0x2178, 0x18);
            break;
        case 14:
            func_ovl0B_06_80044E48(0x2378, 0x18);
            break;
        case 15:
            func_ovl0B_06_80044E48(0x2678, 0x18);
            break;
        case 2:
            func_ovl0B_06_80044E48(0x2B78, 0x18);
            break;
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            break;
    }
    return arg0;
}


/* @800450F8 */
static void func_ovl0B_06_800450F8(void) {
}


/* @80045054 */
static s32 func_ovl0B_06_80045054(void) {
    s32 ret = 0;
    s32 buttons;

    func_ovl0B_06_80044BE4(0);
    buttons = func_ovl0B_06_80044F70(5, 1, 0xC000, 0x78);
    if (buttons & 0x8000) {
        func_ovl0B_06_80049230(1);
        func_ovl0B_06_80048CC8(0xF);
        func_ovl0B_06_80048CC8(5);
        ret = 1;
    } else if (buttons & 0x4000) {
        func_ovl0B_06_80049230(1);
        func_ovl0B_06_80048CC8(0xF);
        func_ovl0B_06_80044F70(func_ovl0B_06_80048E18(), 0, 0, 0xB4);
    }
    func_ovl0B_06_80044BE4(1);
    return ret;
}

/* @80044F70 */
static s32 func_ovl0B_06_80044F70(s32 arg0, s32 arg1, s32 mask, s32 wait) {
    Item_ovl0B_06 *item;
    s32 text;
    s32 buttons = 0;

    switch (arg0) {
        case 9:
            item = &D_ovl0B_06_8004A414;
            break;
        case 2:
            item = &D_ovl0B_06_8004A464;
            break;
        case 5:
            if (arg1 == 0) {
                item = &D_ovl0B_06_8004A428;
            } else {
                item = &D_ovl0B_06_8004A450;
            }
            break;
        default:
            item = &D_ovl0B_06_8004A43C;
            break;
    }
    text = func_ovl0B_06_800490E8(item->unk0, item->unk4, item->unk6, item->unk8, item->unkC, item->unk10);
    if (mask == 0) {
        func_ovl0B_06_80048CC8(wait);
    } else {
        while (TRUE) {
            buttons = func_ovl0B_06_80048268();
            if (buttons & mask) {
                break;
            }
            func_ovl0B_06_80048CF0();
        }
    }
    func_ovl0B_06_80049098(text);
    return buttons;
}


/* @80044E48 */
static void func_ovl0B_06_80044E48(s32 arg0, s32 arg1) {
    s32 n;
    s32 i;
    s32 buttons;

    func_ovl0B_06_80044E40();
    n = (arg0 & 0xFF) * 4;
    D_ovl0B_06_8004992C = arg0;
    if (arg1 != -1) {
        if (arg1 == 0) {
            func_ovl0B_06_80049230(0);
            func_ovl0B_06_80048CC8(5);
        } else if (arg1 == 1) {
            func_ovl0B_06_80049230(1);
            func_ovl0B_06_80048CC8(0xF);
        } else if (arg1 == 2) {
            func_ovl0B_06_80049230(2);
            func_ovl0B_06_80048CC8(0xA);
        } else if (arg1 == 0x18) {
            func_ovl0B_06_80049230(0x18);
            func_ovl0B_06_80048CC8(0x32);
        } else {
            func_ovl0B_06_80049230(arg1);
        }
    }
    for (i = 0; i < n; i++) {
        buttons = func_ovl0B_06_80048268();
        if ((buttons & 0x8000) || (buttons & 0x4000)) {
            func_ovl0B_06_80049230(2);
            func_ovl0B_06_80048CC8(0xA);
            D_ovl0B_06_8004992C = 0;
            func_ovl0B_06_80048CF0();
            return;
        }
        func_ovl0B_06_80048CF0();
    }
}


/* @80044BE4 */
static void func_ovl0B_06_80044E40(void) {
}

static void func_ovl0B_06_80044BE4(s32 arg0) {
    Label_ovl0B_06 *label;

    if (arg0 & 1) {
        D_ovl0B_06_80049CAC[4].unk0->unkC |= 1;
        D_ovl0B_06_80049CAC[4].unk0->unk18 = -100.0f;
        FADE_LABELS(arg0, D_ovl0B_06_80049B94, 4);
        FADE_LABELS(arg0, D_ovl0B_06_8004999C, 3);
        FADE_SLOTS(arg0)
        if (arg0 == 3) {
            D_ovl0B_06_80049B94[6].unk18->unk36 = 100;
            for (label = &D_ovl0B_06_80049B94[7]; label != (Label_ovl0B_06 *) D_ovl0B_06_80049CAC; label++) {
                label->unk18->unk36 = 0x82;
            }
            D_ovl0B_06_80049CAC[4].unk0->unkC &= ~0x400;
        }
    } else {
        if (arg0 == 2) {
            D_ovl0B_06_80049B94[6].unk18->unk36 = 0;
            D_ovl0B_06_80049B94[7].unk18->unk36 = 0;
            D_ovl0B_06_80049B94[8].unk18->unk36 = 0;
            D_ovl0B_06_80049B94[9].unk18->unk36 = 0;
            D_ovl0B_06_80049CAC[4].unk0->unkC |= 0x400;
        }
        D_ovl0B_06_80049CAC[4].unk0->unkC &= ~1;
        D_ovl0B_06_80049CAC[4].unk0->unk18 = 20.0f;
        func_ovl0B_06_80044BA0(4, &D_ovl0B_06_8004A284);
        FADE_LABELS(arg0, D_ovl0B_06_80049B94, 4);
        FADE_LABELS(arg0, D_ovl0B_06_8004999C, 3);
        FADE_SLOTS(arg0)
    }
}


/* @80044BA0 */
static void func_ovl0B_06_80044BA0(s32 arg0, Col_ovl0B_06 *col) {
    Box_ovl0B_06 *box = &D_ovl0B_06_80049CAC[arg0];

    func_ovl0B_06_80044B90();
    func_ovl0B_06_80044B98();
    box->unk4 = col->unk0;
    box->unk8 = col->unk4;
    box->unkC = col->unk8;
    box->unk10 = col->unkC;
}


/* @80044B08 */
static void func_ovl0B_06_80044B98(void) {
}

static void func_ovl0B_06_80044B90(void) {
}

static void func_ovl0B_06_80044B08(s32 arg0, Label_ovl0B_06 *label) {
    s32 alpha;

    switch (arg0) {
        case 0:
        case 2:
            alpha = 0;
            if (arg0 == 0) {
                alpha = 0x3C;
            }
            label->unk18->unkC |= 0x80;
            label->unk18->unk36 = alpha;
            break;
        case 1:
        case 3:
            label->unk18->unkC &= ~0x80;
            label->unk18->unk36 = 0xFF;
            break;
    }
}


/* @80044908 */
static void func_ovl0B_06_80044908(s32 arg0) {
    if (arg0 == 0) {
        D_ovl0B_06_80049E44[0].unk0->unkC |= 1;
        D_ovl0B_06_80049E44[1].unk0->unkC |= 1;
        D_ovl0B_06_80049E44[3].unk0->unkC |= 1;
        D_ovl0B_06_80049E44[8].unk0->unkC |= 1;
        D_ovl0B_06_80049E44[9].unk0->unkC |= 1;
        D_ovl0B_06_80049E44[10].unk0->unkC |= 1;
        D_ovl0B_06_80049CAC[3].unk0->unkC |= 1;
        D_ovl0B_06_80049CAC[5].unk0->unkC |= 1;
        D_ovl0B_06_80049B94[4].unk18->unkC |= 1;
        D_ovl0B_06_80049B94[5].unk18->unkC |= 1;
    } else {
        D_ovl0B_06_80049E44[0].unk0->unkC &= ~1;
        D_ovl0B_06_80049E44[1].unk0->unkC &= ~1;
        D_ovl0B_06_80049E44[3].unk0->unkC &= ~1;
        D_ovl0B_06_80049E44[8].unk0->unkC &= ~1;
        D_ovl0B_06_80049E44[9].unk0->unkC &= ~1;
        D_ovl0B_06_80049E44[10].unk0->unkC &= ~1;
        D_ovl0B_06_80049CAC[3].unk0->unkC &= ~1;
        D_ovl0B_06_80049CAC[5].unk0->unkC &= ~1;
        D_ovl0B_06_80049B94[4].unk18->unkC &= ~1;
        D_ovl0B_06_80049B94[5].unk18->unkC &= ~1;
    }
}


/* @8004473C */
void func_ovl0B_06_8004473C(void) {
    Txt_ovl0B_06 *txt;
    Pair_ovl0B_06 *pos;
    s32 text;
    s32 idx;

    D_ovl0B_06_8004992C = 0;
    func_ovl0B_06_80043404(&D_ovl0B_06_80049B24);
    D_ovl0B_06_80049B24.unk18->unkC |= 1;
    while (D_ovl0B_06_8004992C != 0x400) {
        if (D_ovl0B_06_8004992C & 0x6000) {
            idx = (D_ovl0B_06_8004992C & 0xF00) >> 8;
            if (D_ovl0B_06_8004992C & 0x4000) {
                idx += 0x10;
            }
            txt = &D_ovl0B_06_8004A294[idx];
            pos = &D_ovl0B_06_8004A3E4[txt->unkC];
            text = func_ovl0B_06_800490E8(txt->unk0, txt->unk4, pos->unk0, txt->unk8, pos->unk4, D_ovl0B_06_80049B24.unk14);
            func_ovl0B_06_80049098(D_ovl0B_06_80049B24.unk4);
            D_ovl0B_06_80049B24.unk4 = text;
            D_ovl0B_06_80049B24.unk18 = func_ovl0B_06_800490C8(text);
            D_ovl0B_06_8004992C &= 0x1FF;
            D_ovl0B_06_8004992C *= 4;
            D_ovl0B_06_80049B24.unk18->unkC &= ~1;
        } else if (D_ovl0B_06_8004992C & 0x1000) {
            D_ovl0B_06_8004992C &= 0x3FF;
            D_ovl0B_06_8004992C *= 4;
            D_ovl0B_06_80049B24.unk18->unkC &= ~1;
        }
        if (D_ovl0B_06_8004992C > 0) {
            D_ovl0B_06_8004992C--;
        }
        if (D_ovl0B_06_8004992C == 0) {
            D_ovl0B_06_80049B24.unk18->unkC |= 1;
        }
        func_ovl0B_06_80048CF0();
    }
    D_ovl0B_06_8004992C = 0;
    func_ovl0B_06_80049098(D_ovl0B_06_80049B24.unk4);
    func_ovl0B_06_80048CB8();
}


/* @80043C48 */
void func_ovl0B_06_80043220(void) {
    func_ovl0B_06_80043218();
    func_ovl0B_06_80048840(D_ovl0B_06_8004A628);
    func_ovl0B_06_80048840(D_ovl0B_06_8004A62C);
    func_ovl0B_06_80048840(D_ovl0B_06_8004A630);
    func_ovl0B_06_80048840(D_ovl0B_06_8004A634);
}


/* @800430F0 */
static void func_ovl0B_06_80043218(void) {
}

void func_ovl0B_06_80043B20(void) {
    D_ovl0B_06_8004A628 = func_ovl0B_06_80048838(0x353, 1);
    D_ovl0B_06_8004A628->unkC |= 1;
    D_ovl0B_06_8004A630 = func_ovl0B_06_80048838(0x355, 2);
    D_ovl0B_06_8004A630->unkC |= 1;
    D_ovl0B_06_8004A634 = func_ovl0B_06_80048838(0x356, 3);
    D_ovl0B_06_8004A634->unkC |= 1;
    D_ovl0B_06_8004A62C = func_ovl0B_06_80048838(0x354, 4);
    D_ovl0B_06_8004A62C->unkC |= 1;
    D_ovl0B_06_8004A638 = func_ovl0B_06_80048D30(0x296);
    func_ovl0B_06_80048D40(D_ovl0B_06_8004A638, 1);
    D_ovl0B_06_8004A638->unk18 = 0.0f;
    D_ovl0B_06_8004A638->unk1C = 0.0f;
    D_ovl0B_06_8004A638->unk40 = 0.5f;
    D_ovl0B_06_8004A638->unk44 = D_ovl0B_06_8004A638->unk40 * 0.75f;
    D_ovl0B_06_8004A638->unk3C = 32.0f;
}


/* @8004390C */
void func_ovl0B_06_8004390C(void) {
    func_ovl0B_06_800438FC();
    func_ovl0B_06_80043904();
    D_ovl0B_06_8004A628->unk10 = 71.0f;
    D_ovl0B_06_8004A628->unk14 = 13.0f;
    D_ovl0B_06_8004A628->unk18 = D_ovl0B_06_8004A628->unk10 + D_ovl0B_06_8004A628->unk28;
    D_ovl0B_06_8004A628->unk1C = D_ovl0B_06_8004A628->unk14 + D_ovl0B_06_8004A628->unk2C;
    D_ovl0B_06_8004A628->unkC &= ~1;
    D_ovl0B_06_8004A62C->unk10 = 29.0f;
    D_ovl0B_06_8004A62C->unk14 = 78.0f;
    D_ovl0B_06_8004A62C->unk18 = D_ovl0B_06_8004A62C->unk10 + D_ovl0B_06_8004A62C->unk28;
    D_ovl0B_06_8004A62C->unk1C = D_ovl0B_06_8004A62C->unk14 + D_ovl0B_06_8004A62C->unk2C;
    D_ovl0B_06_8004A62C->unkC &= ~1;
    D_ovl0B_06_8004A630->unk10 = 127.0f;
    D_ovl0B_06_8004A630->unk14 = 54.0f;
    D_ovl0B_06_8004A630->unk18 = D_ovl0B_06_8004A630->unk10 + D_ovl0B_06_8004A630->unk28;
    D_ovl0B_06_8004A630->unk1C = D_ovl0B_06_8004A630->unk14 + D_ovl0B_06_8004A630->unk2C;
    D_ovl0B_06_8004A630->unkC &= ~1;
    D_ovl0B_06_8004A634->unk10 = 164.0f;
    D_ovl0B_06_8004A634->unk14 = 88.0f;
    D_ovl0B_06_8004A634->unk18 = D_ovl0B_06_8004A634->unk10 + D_ovl0B_06_8004A634->unk28;
    D_ovl0B_06_8004A634->unk1C = D_ovl0B_06_8004A634->unk14 + D_ovl0B_06_8004A634->unk2C;
    D_ovl0B_06_8004A634->unkC &= ~1;
    func_ovl0B_06_80048D40(D_ovl0B_06_8004A638, 0x20000000);
    D_ovl0B_06_8004A638->unk18 = 0.0625f;
    D_ovl0B_06_8004A638->unk1C = 0.0f;
}


/* @80043834 */
static void func_ovl0B_06_80043904(void) {
}

static void func_ovl0B_06_800438FC(void) {
}

void func_ovl0B_06_80043C48(s32 arg0) {
    Box_ovl0B_06 *box;
    Label_ovl0B_06 *label;
    u8 *name;
    u8 *src;
    f32 step;
    s32 i;
    s32 j;

    func_ovl0B_06_80043C40();
    switch (arg0) {
        case 2:
            D_ovl0B_06_80049928 = 0;
            func_ovl0B_06_80048FF8(0x32, 0x32, 0x32);
            D_ovl0B_06_8004A668[0] = func_ovl0B_06_80048258();
            func_ovl0B_06_80048A00(0x7F);
            func_ovl0B_06_80048978(1);
            func_ovl0B_06_80048998(0.0f, 10.0f, 0.0f);
            func_ovl0B_06_80048988(1);
            func_ovl0B_06_800489B8(32768.0f, 10.0f, 2200.0f);
            break;
        case 4:
            func_ovl0B_06_800489B8(0.0f, 10.0f, 2200.0f);
            func_ovl0B_06_80043B20();
            func_ovl0B_06_8004390C();
            D_ovl0B_06_8004A628->unkC |= 0x480;
            D_ovl0B_06_8004A62C->unkC |= 0x480;
            D_ovl0B_06_8004A630->unkC |= 0x480;
            D_ovl0B_06_8004A634->unkC |= 0x480;
            D_ovl0B_06_8004A628->unk36 = 0x5A;
            D_ovl0B_06_8004A62C->unk36 = 0x5A;
            D_ovl0B_06_8004A630->unk36 = 0x5A;
            D_ovl0B_06_8004A634->unk36 = 0x5A;
            D_ovl0B_06_8004A660 = func_ovl0B_06_80048838(0x367, 5);
            D_ovl0B_06_8004A660->unk10 = 210.0f;
            D_ovl0B_06_8004A660->unk14 = 114.0f;
            D_ovl0B_06_8004A660->unk18 = 298.0f;
            D_ovl0B_06_8004A660->unk1C = 180.0f;
            D_ovl0B_06_8004A660->unkC |= 0x680;
            D_ovl0B_06_8004A664 = func_ovl0B_06_80048838(0x368, 5);
            D_ovl0B_06_8004A664->unk10 = 285.0f;
            D_ovl0B_06_8004A664->unk14 = 51.0f;
            D_ovl0B_06_8004A664->unk18 = 304.0f;
            D_ovl0B_06_8004A664->unk1C = 62.0f;
            D_ovl0B_06_8004A664->unkC |= 0x680;
            D_ovl0B_06_8004A660->unk36 = 0x5A;
            D_ovl0B_06_8004A664->unk36 = 0x5A;
            break;
        case 16:
            for (i = 0, box = D_ovl0B_06_80049CAC; i < 5; i++, box++) {
                step = (box->unk18 - box->unk14) / box->unk1C;
                box->unk0 = func_ovl0B_06_800488B8(box->unk40, box->unk38);
                box->unk0->unkC |= box->unk3C;
                for (box->unk34 = box->unk14; box->unk34 < box->unk18; box->unk34 += step) {
                    func_ovl0B_06_80048CF0();
                }
                func_ovl0B_06_80048CF0();
            }
            break;
        case 17:
            D_ovl0B_06_80049CAC[3].unk2C += 0x12;
            for (i = 0, box = D_ovl0B_06_80049CAC; i < 6; i++, box++) {
                step = (box->unk18 - box->unk14) / box->unk1C;
                box->unk0 = func_ovl0B_06_800488B8(box->unk40, box->unk38);
                box->unk0->unkC |= box->unk3C;
                for (box->unk34 = box->unk14; box->unk34 < box->unk18; box->unk34 += step) {
                    func_ovl0B_06_80048CF0();
                }
                func_ovl0B_06_80048CF0();
            }
            break;
        case 5:
            for (i = 0; i < 3; i++) {
                func_ovl0B_06_80043404(&D_ovl0B_06_8004999C[i]);
            }
            switch (D_ovl0B_06_8004A668[0]) {
                case 16:
                    func_ovl0B_06_80043480(1);
                    func_ovl0B_06_80048CA8(func_ovl0B_06_8004747C, NULL, D_ovl0B_06_8004A670, 0x1000, 0x130);
                    func_ovl0B_06_80043834();
                    break;
                case 17:
                    func_ovl0B_06_80043480(0);
                    func_ovl0B_06_80048CA8(func_ovl0B_06_8004616C, NULL, D_ovl0B_06_8004A670, 0x1000, 0x130);
                    for (i = 0, name = D_ovl0B_06_80049558; i < 3; i++, name += 9) {
                        src = (u8 *) func_ovl0B_06_80049368(i, 8);
                        if (src != NULL) {
                            for (j = 0; j < 8; j++) {
                                D_ovl0B_06_80049558[i * 9 + j] = src[j];
                            }
                        } else {
                            name[0] = 0x27;
                            name[1] = 0x48;
                            name[2] = 0xF;
                            name[3] = 0x1D;
                            name[4] = 0x3A;
                            name[5] = 0x4D;
                            name[6] = 0x3A;
                            name[7] = 0xF;
                        }
                        name[8] = 0;
                    }
                    for (i = 0; i < 10; i++) {
                        func_ovl0B_06_80043404(&D_ovl0B_06_80049B94[i]);
                    }
                    for (i = 0, label = D_ovl0B_06_80049B94, name = D_ovl0B_06_80049558; i != 3; i++, name += 9, label++) {
                        func_ovl0B_06_800490B0(label[1].unk4, -(s32) (func_ovl0B_06_800490E0(name) * 0.8f * 0.5f), 0);
                        if (func_ovl0B_06_80049368(i, 8) != 0) {
                            func_ovl0B_06_800433B0(&label[7]);
                            label[7].unk18->unk36 = 0x82;
                            func_ovl0B_06_800490B0(label[7].unk4, -(s32) (func_ovl0B_06_800490E0(name) * 0.8f * 0.5f), 0);
                        } else {
                            label[7].unk18->unkC |= 1;
                        }
                    }
                    func_ovl0B_06_800433B0(&D_ovl0B_06_80049B94[5]);
                    D_ovl0B_06_80049E44[0].unk8 += 18.0f;
                    D_ovl0B_06_80049E44[0].unk10 += 18.0f;
                    D_ovl0B_06_80049E44[1].unk8 += 18.0f;
                    D_ovl0B_06_80049E44[1].unk10 += 18.0f;
                    func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[0], &D_ovl0B_06_8004A0C4[1], 0.0f);
                    func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[1], &D_ovl0B_06_8004A0C4[0], 0.0f);
                    func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[3], &D_ovl0B_06_8004A0C4[3], 0.0f);
                    func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[8], &D_ovl0B_06_8004A0C4[3], 0.0f);
                    func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[9], &D_ovl0B_06_8004A0C4[0], 0.0f);
                    func_ovl0B_06_80043040(&D_ovl0B_06_80049E44[10], &D_ovl0B_06_8004A0C4[14], 0.0f);
                    break;
            }
            break;
        case 1:
            for (i = 0, box = D_ovl0B_06_80049CAC; i < 5; i++, box++) {
                for (box->unk34 = box->unk24; box->unk34 > 0.0f; box->unk34 -= box->unk28) {
                    func_ovl0B_06_80048CF0();
                }
                func_ovl0B_06_80048840(box->unk0);
                func_ovl0B_06_80048CF0();
            }
            for (i = 0; i < 3; i++) {
                func_ovl0B_06_80049098(D_ovl0B_06_8004999C[i].unk4);
            }
            func_ovl0B_06_80043280();
            func_ovl0B_06_80043220();
            func_ovl0B_06_80048840(D_ovl0B_06_8004A660);
            func_ovl0B_06_80048840(D_ovl0B_06_8004A664);
            switch (D_ovl0B_06_8004A668[0]) {
                case 16:
                    for (i = 0; i < 6; i++) {
                        func_ovl0B_06_80049098(D_ovl0B_06_80049A44[i].unk4);
                    }
                    func_ovl0B_06_800430F0(1);
                    break;
                case 17:
                    for (i = 0; i < 10; i++) {
                        func_ovl0B_06_80049098(D_ovl0B_06_80049B94[i].unk4);
                    }
                    for (i = 0, box = &D_ovl0B_06_80049CAC[5]; i < 1; i++, box++) {
                        for (box->unk34 = box->unk24; box->unk34 > 0.0f; box->unk34 -= box->unk28) {
                            func_ovl0B_06_80048CF0();
                        }
                        func_ovl0B_06_80048840(box->unk0);
                        func_ovl0B_06_80048CF0();
                    }
                    func_ovl0B_06_80048840(D_ovl0B_06_80049E44[0].unk0);
                    func_ovl0B_06_80048840(D_ovl0B_06_80049E44[1].unk0);
                    func_ovl0B_06_80048840(D_ovl0B_06_80049E44[3].unk0);
                    func_ovl0B_06_80048840(D_ovl0B_06_80049E44[8].unk0);
                    func_ovl0B_06_80048840(D_ovl0B_06_80049E44[9].unk0);
                    func_ovl0B_06_80048840(D_ovl0B_06_80049E44[10].unk0);
                    break;
            }
            break;
    }
}


/* @80043B20 */
static void func_ovl0B_06_80043C40(void) {
}

static void func_ovl0B_06_80043834(void) {
    s32 i;
    s32 j;
    UnkStructA_40 *obj;

    func_ovl0B_06_800430F0(0);
    func_ovl0B_06_8004382C(D_ovl0B_06_80049A44, 6);
    func_ovl0B_06_800433B0(&D_ovl0B_06_80049A44[5]);
    for (i = 0; i < 3; i++) {
        j = func_ovl0B_06_80049368(i, 0);
        obj = D_ovl0B_06_80049A44[i + 1].unk18;
        switch (j) {
            case 0:
                obj->unkC |= 1;
                break;
            case 1:
                obj->unkC |= 1;
                break;
            case 10:
                break;
        }
    }
}


/* @80043480 */
static void func_ovl0B_06_8004382C(Label_ovl0B_06 *p, s32 n) {
    s32 i;
    for (i = 0; i < n; i++, p++) {
        func_ovl0B_06_80043404(p);
    }
}


static void func_ovl0B_06_80043480(s32 arg0) {
    u8 buf[4];
    Unk24_ovl0B_06 *p;
    Label_ovl0B_06 *label;
    s32 state;
    s32 kind;
    f32 d;
    s32 i;
    s32 j;

    func_ovl0B_06_80043450();
    func_ovl0B_06_80043458();
    func_ovl0B_06_80043460();
    func_ovl0B_06_80043468();
    func_ovl0B_06_80043470();
    func_ovl0B_06_80043478();
    for (i = 0; i < 3; i++) {
        state = func_ovl0B_06_80049368(i, 0);
        if (state != 10) {
            p = &D_ovl0B_06_80049930[i];
            label = &D_ovl0B_06_800499F0[i];
            func_ovl0B_06_80047E20(buf, "%03d", func_ovl0B_06_80049368(i, 1));
            buf[0] -= 0x20;
            buf[1] -= 0x20;
            buf[2] -= 0x20;
            if (buf[0] == 0x10) {
                buf[0] = 0xF;
                if (buf[1] == 0x10) {
                    buf[1] = 0xF;
                }
            }
            label->unk0[1] = buf[0];
            label->unk0[2] = buf[1];
            label->unk0[3] = buf[2];
            label->unk4 = func_ovl0B_06_80049090(label->unk0, label->unk8, label->unkA, label->unkC, label->unk10, label->unk14);
            label->unk18 = func_ovl0B_06_800490C8(label->unk4);
            p->unk0 = func_ovl0B_06_80048838(p->unk4, p->unk8);
            p->unk0->unk10 = p->unkC;
            p->unk0->unk14 = p->unk10;
            p->unk0->unk18 = p->unk14;
            p->unk0->unk1C = p->unk18;
            p->unk0->unk20 = p->unk1C;
            p->unk0->unk24 = p->unk20;
            if (arg0 != 0) {
                if (state == 0) {
                    func_ovl0B_06_80043040(&D_ovl0B_06_80049F20[i][0], &D_ovl0B_06_8004A0C4[10], i * 40);
                } else {
                    func_ovl0B_06_80043040(&D_ovl0B_06_80049F20[i][0], &D_ovl0B_06_8004A0C4[11], i * 40);
                }
                for (j = 0; j < 6; j++) {
                    kind = func_ovl0B_06_80049368(i, j + 2);
                    if (kind != 0) {
                        d = 0.0f;
                        func_ovl0B_06_80043040(&D_ovl0B_06_80049F20[i][j + 1], &D_ovl0B_06_8004A0C4[j + 4], i * 40);
                        switch (kind) {
                            case 1:
                                break;
                            case 2:
                                d = 3.0f;
                                break;
                            case 3:
                                d = 6.0f;
                                break;
                            case 4:
                                d = 9.0f;
                                break;
                        }
                        D_ovl0B_06_80049F20[i][j + 1].unk0->unk10 -= d;
                        D_ovl0B_06_80049F20[i][j + 1].unk0->unk14 -= d;
                        D_ovl0B_06_80049F20[i][j + 1].unk0->unk18 += d;
                        D_ovl0B_06_80049F20[i][j + 1].unk0->unk1C += d;
                        D_ovl0B_06_8004A5E0[i].unk[j] = 1;
                    } else {
                        D_ovl0B_06_8004A5E0[i].unk[j] = 0;
                    }
                }
                D_ovl0B_06_8004A5D0[i] = 1;
            } else {
                D_ovl0B_06_8004A5D0[i] = 2;
            }
        } else {
            D_ovl0B_06_8004A5D0[i] = 0;
        }
    }
}


/* @80043404 */
static void func_ovl0B_06_80043478(void) {
}

static void func_ovl0B_06_80043470(void) {
}

static void func_ovl0B_06_80043468(void) {
}

static void func_ovl0B_06_80043460(void) {
}

static void func_ovl0B_06_80043458(void) {
}

static void func_ovl0B_06_80043450(void) {
}

static void func_ovl0B_06_80043404(Label_ovl0B_06 *label) {
    func_ovl0B_06_800433F4();
    func_ovl0B_06_800433FC();
    label->unk4 = func_ovl0B_06_800490E8(label->unk0, label->unk8, label->unkA, label->unkC, label->unk10, label->unk14);
    label->unk18 = func_ovl0B_06_800490C8(label->unk4);
}


/* @800433B0 */
static void func_ovl0B_06_800433FC(void) {
}

static void func_ovl0B_06_800433F4(void) {
}

static void func_ovl0B_06_800433B0(Label_ovl0B_06 *label) {
    func_ovl0B_06_800433A8();
    label->unk18 = func_ovl0B_06_800490C8(label->unk4);
    label->unk18->unkC |= 0x480;
    label->unk18->unk36 = 100;
}


/* @80043280 */
static void func_ovl0B_06_800433A8(void) {
}

static void func_ovl0B_06_80043280(void) {
    s32 i;
    s32 j;

    func_ovl0B_06_80043278();
    for (i = 0; i < 3; i++) {
        if (D_ovl0B_06_8004A5D0[i] != 0) {
            func_ovl0B_06_80049098(D_ovl0B_06_800499F0[i].unk4);
            func_ovl0B_06_80048840(D_ovl0B_06_80049930[i].unk0);
            if (D_ovl0B_06_8004A5D0[i] != 2) {
                func_ovl0B_06_80048840(D_ovl0B_06_80049F20[i][0].unk0);
                for (j = 0; j < 6; j++) {
                    if (D_ovl0B_06_8004A5E0[i].unk[j] != 0) {
                        func_ovl0B_06_80048840(D_ovl0B_06_80049F20[i][j + 1].unk0);
                    }
                }
            }
        }
    }
}


/* @80043220 */
static void func_ovl0B_06_80043278(void) {
}

static void func_ovl0B_06_800430F0(s32 arg0) {
    s32 i;

    switch (arg0) {
        case 0:
            for (i = 0; i < 3; i++) {
                func_ovl0B_06_80043040(D_ovl0B_06_8004A238[i], D_ovl0B_06_8004A22C[i], 0.0f);
            }
            break;
        case 1:
            for (i = 0; i < 3; i++) {
                func_ovl0B_06_80048840(D_ovl0B_06_8004A238[i]->unk0);
            }
            break;
        case 2:
            for (i = 0; i < 3; i++) {
                D_ovl0B_06_8004A238[i]->unk0->unkC |= 1;
            }
            break;
        case 3:
            for (i = 0; i < 3; i++) {
                D_ovl0B_06_8004A238[i]->unk0->unkC &= ~1;
            }
            break;
    }
}


/* @80043040 */
static void func_ovl0B_06_80043040(Rect_ovl0B_06 *rect, Spr_ovl0B_06 *spr, f32 dy) {
    func_ovl0B_06_80043010();
    func_ovl0B_06_80043018();
    func_ovl0B_06_80043020();
    func_ovl0B_06_80043028();
    func_ovl0B_06_80043030();
    func_ovl0B_06_80043038();
    rect->unk0 = func_ovl0B_06_80048838(spr->unk8, spr->unk10);
    *(s32 *) rect->unk0->unk38 = spr->unkC;
    rect->unk0->unk28 = spr->unk0;
    rect->unk0->unk2C = spr->unk4;
    rect->unk0->unk10 = rect->unk4;
    rect->unk0->unk14 = rect->unk8 + dy;
    rect->unk0->unk18 = rect->unkC;
    rect->unk0->unk1C = rect->unk10 + dy;
    rect->unk0->unkC |= spr->unk14;
}


/* @80043010 */
static void func_ovl0B_06_80043010(void) {
}

static void func_ovl0B_06_80043018(void) {
}

static void func_ovl0B_06_80043020(void) {
}

static void func_ovl0B_06_80043028(void) {
}

static void func_ovl0B_06_80043030(void) {
}

static void func_ovl0B_06_80043038(void) {
}

