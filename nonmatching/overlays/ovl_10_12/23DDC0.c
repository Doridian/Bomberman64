/*
 * NON_MATCHING: ovl_10_12's game object, complete: every function, its
 * .bss and its .data tables; .text one word long. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 111, eu 195, jp 111
 *
 * What still differs in us (words; eu and jp the same):
 * - func_ovl10_12_800432B0 (6), func_ovl10_12_80044FEC (62) and
 *   func_ovl10_12_80046908 (2): ovl_10_11's 800431AC, 80043C2C and
 *   80044150, with the same differences (its header).
 * - func_ovl10_12_80047008 (11): the same code; the padding IDO puts after its
 *   endless loop (to a 16-byte boundary) is a word longer
 *   because 80044FEC is a word short (as in ovl_10_11's 80044C24).
 * - func_ovl10_12_80044C68 (12): s4 and s5 swap (arg0 and &80048D28[i]).
 * - func_ovl10_12_80046048 (9): pos and pos2 sit a word lower in the
 *   original, in the same frame.
 * - func_ovl10_12_8004635C (9): s0 and s1 swap.
 *
 * ovl_10_12's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Most of it is ovl_10_11's
 * (its draft's spelling, renamed); 80043018-80043F14, 80044168-800446B0,
 * 80044A58-80044C68 and 80045158-80046828 are its own (as ovl_10_08,
 * ovl_10_09 and ovl_10_13 have them, none of which is C yet).
 *
 * func_ovl10_12_80043F14's loops: the original keeps arg0 in v1
 * from the ends of both arms of `if (arg1 != 0)` into the loops. An empty `if (arg0) {}` where the arms
 * meet does it (found by the permuter; 95 words to 0). `arg0 * 0` in a
 * loop's indices gets most of the way (72 words): what matters is a use of
 * arg0 that IDO removes late.
 */

#include "common.h"
/* What func_ovl10_12_80048160 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_12_80048160;

void func_ovl10_12_80047248(const char *, ...);
void func_ovl10_12_80047588(s32);
void func_ovl10_12_80047590(s32, f32, f32, f32, s32, s32);
void func_ovl10_12_800475A0(s32);
void func_ovl10_12_800475C0(s32, s32, s32, s32);
void func_ovl10_12_800475E0(f32, f32, f32, s32 *, s32);
void func_ovl10_12_800475E8(f32, f32, f32, Vec3f *, s32);
f32 func_ovl10_12_80047628(s32);
void func_ovl10_12_80047630(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_12_80047638(s32, s32, s32, s32, s32, s32);
void func_ovl10_12_80047640(s32);
void func_ovl10_12_80047670(void (*)(UnkStructA *));
void func_ovl10_12_80047680(s32, s32, s32);
s32 *func_ovl10_12_800476D8(void);
void func_ovl10_12_800476F0(s32);
void func_ovl10_12_80047738(void);
void func_ovl10_12_80047740(s32, s32, s32);
s32 func_ovl10_12_80047758(s32, s32, s32, s32, s32);
s32 func_ovl10_12_80047768(void);
void func_ovl10_12_80047778(s32);
void func_ovl10_12_80047788(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_12_80047798(void);
void func_ovl10_12_800477A0(s32);
void func_ovl10_12_800477B0(s32);
UnkStructA *func_ovl10_12_800477C8(s32);
void func_ovl10_12_800477E0(s32);
void func_ovl10_12_80047DC8(f32, f32, f32);
void func_ovl10_12_80047DE8(f32, f32, f32);
void func_ovl10_12_80047DF0(f32 *, f32 *, f32 *);
void func_ovl10_12_80047E30(s32);
void func_ovl10_12_80047E50(f32);
void func_ovl10_12_80047E58(f32);
void func_ovl10_12_80047E70(f32);
void func_ovl10_12_80047F90(UnkStructA *, s32);
void func_ovl10_12_80047FA0(UnkStructA *);
UnkStructA *func_ovl10_12_80047FB0(s32, s32, s32, s32);
void func_ovl10_12_80048008(UnkStructA *);
void func_ovl10_12_80048058(UnkStructA *, Vec3f *);
void func_ovl10_12_800480D8(void (*)(void), s32, s32, s32, s32);
void func_ovl10_12_800480F8(s32);
void func_ovl10_12_80048120(void);
void func_ovl10_12_80048150(s32, s32);
UnkStruct_ovl10_12_80048160 *func_ovl10_12_80048160(void);
void func_ovl10_12_80048170(UnkStruct_ovl10_12_80048160 *, s32);
s32 *func_ovl10_12_80048370(void);
void func_ovl10_12_800483D8(s32, s32, s32, f32);
void func_ovl10_12_80048418(s32, s32, s32, s32, s32);
void func_ovl10_12_80048428(s32, s32, s32);
void func_ovl10_12_80048440(u32 (*)[3]);
void func_ovl10_12_80048530(s32, Vec3f *, s32);
void func_ovl10_12_800485E8(s32, s32, s32);
void func_ovl10_12_80048660(s32);
void func_ovl10_12_80048680(s32, f32, f32, f32);
void func_ovl10_12_80047780(s32);
void func_ovl10_12_80047790(const char *);
void func_ovl10_12_80047828(s32);
s32 func_ovl10_12_80047850(s32);
void func_ovl10_12_80047C90(UnkStructA_40 *, s32);
void func_ovl10_12_80047C98(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl10_12_80047CD0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl10_12_80047E00(u32 *, s32, s32);
void func_ovl10_12_80047E40(s32);
f32 func_ovl10_12_80047F30(Vec3f *, Vec3f *);
void func_ovl10_12_80047F88(UnkStructA *, s32);
void func_ovl10_12_800480E8(void);
s32 func_ovl10_12_80048298(s32);
void func_ovl10_12_80048608(s32);
s32 func_ovl10_12_80048688(s32, Vec3f *);
void func_ovl10_12_80048690(s32);
void func_ovl10_12_800487D8(void);
void func_ovl10_12_800487E0(void);

void func_ovl10_12_80043010(void);
void func_ovl10_12_80043018(void);
void func_ovl10_12_80043060(void);
void func_ovl10_12_800430B0(void);
void func_ovl10_12_80043148(void);
s32 func_ovl10_12_80043150(void (*arg0)(void));
void func_ovl10_12_800431C8(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl10_12_800432B0(void);
void func_ovl10_12_8004339C(void);
s32 func_ovl10_12_800434D8(s32 arg0);
void func_ovl10_12_800437A8(void);
void func_ovl10_12_800437C8(s32 arg0);
void func_ovl10_12_800439A4(s32 arg0, s32 arg1);
void func_ovl10_12_80043AA0(void);
void func_ovl10_12_80043B44(s32 arg0);
void func_ovl10_12_80043C60(s32 arg0);
void func_ovl10_12_80043C98(void);
void func_ovl10_12_80043DBC(s32 arg0);
void func_ovl10_12_80043DD4(s32 arg0);
void func_ovl10_12_80043E6C(s32 arg0);
void func_ovl10_12_80043E9C(s32 arg0);
void func_ovl10_12_80043EE4(s32 arg0);
void func_ovl10_12_80043F14(s32 arg0, s32 arg1);
void func_ovl10_12_80044168(void);
void func_ovl10_12_80044218(s32 arg0, s32 arg1);
void func_ovl10_12_80044370(void);
void func_ovl10_12_80044538(void);
void func_ovl10_12_800445A4(void);
void func_ovl10_12_80044618(void);
void func_ovl10_12_800446B0(void);
void func_ovl10_12_80044740(void);
void func_ovl10_12_80044768(void);
void func_ovl10_12_800447A0(void);
void func_ovl10_12_80044904(void);
void func_ovl10_12_800449AC(void);
void func_ovl10_12_800449D4(void);
void func_ovl10_12_800449DC(void);
void func_ovl10_12_80044A58(s32 arg0);
void func_ovl10_12_80044B1C(s32 *arg0);
void func_ovl10_12_80044C68(s32 *arg0);
void func_ovl10_12_80044F38(s32 *arg0);
void func_ovl10_12_80044FEC(s32 *arg0);
void func_ovl10_12_80045158(void);
void func_ovl10_12_800452C0(s32 arg0);
void func_ovl10_12_80045478(void);
void func_ovl10_12_800454EC(void);
void func_ovl10_12_8004555C(void);
void func_ovl10_12_80045578(s32 arg0);
void func_ovl10_12_800455B0(void);
f32 func_ovl10_12_80045768(s32 arg0);
void func_ovl10_12_800457C0(s32 arg0, s32 arg1);
void func_ovl10_12_80045924(void);
void func_ovl10_12_800459D8(s32 arg0);
void func_ovl10_12_80045A78(void);
void func_ovl10_12_80045D94(s32 *arg0);
void func_ovl10_12_80045F00(void);
void func_ovl10_12_80045F18(void);
void func_ovl10_12_80045FE4(s32 arg0, s32 arg1);
void func_ovl10_12_80046048(s32 arg0, s32 arg1);
void func_ovl10_12_8004635C(void);
void func_ovl10_12_80046550(void);
void func_ovl10_12_80046590(s32 arg0);
void func_ovl10_12_80046608(void);
void func_ovl10_12_80046828(void);
void func_ovl10_12_80046908(void);
void func_ovl10_12_80046D5C(UnkStructA *arg0);
void func_ovl10_12_80046DDC(UnkStructA *arg0);
void func_ovl10_12_80046E48(void);
void func_ovl10_12_80046E84(void);
void func_ovl10_12_80046F14(void (*arg0)(void));
void func_ovl10_12_80046F30(s32 arg0);
void func_ovl10_12_80046F4C(s32 arg0);
s32 func_ovl10_12_80046F60(void (*arg0)(void));
void func_ovl10_12_80046FA4(void (*arg0)(void));
s32 func_ovl10_12_80046FD0(void (*arg0)(void), const char *arg1);
void func_ovl10_12_80047008(void);
void func_ovl10_12_800470F8(s32 arg0, UnkStructA *arg1);
void func_ovl10_12_8004712C(f32 arg0);
void func_ovl10_12_80047174(f32 arg0, f32 arg1, f32 arg2);
void func_ovl10_12_800471D0(void);
void func_ovl10_12_800471E8(void);


/* .bss */
u8 D_ovl10_12_80048C30[0x24]; /* unused (func_ovl10_12_800471E8) */
s32 D_ovl10_12_80048C54;
s32 D_ovl10_12_80048C58;
u8 D_ovl10_12_80048C5C[0x4]; /* unused (func_ovl10_12_800471E8) */
Vec3f D_ovl10_12_80048C60;
u8 D_ovl10_12_80048C6C[0x4]; /* unused (func_ovl10_12_800471E8) */
UnkStructA *D_ovl10_12_80048C70[12];
s32 D_ovl10_12_80048CA0[11][3];
u8 D_ovl10_12_80048D24[0x4]; /* unused (func_ovl10_12_800471E8) */
s32 D_ovl10_12_80048D28[12];
s32 D_ovl10_12_80048D58[12];
s32 D_ovl10_12_80048D88[64];
s32 D_ovl10_12_80048E88;
u8 D_ovl10_12_80048E8C[0x4]; /* unused (func_ovl10_12_800471E8) */
s32 D_ovl10_12_80048E90[12];
s32 D_ovl10_12_80048EC0[12];
s32 D_ovl10_12_80048EF0[11];
s32 D_ovl10_12_80048F1C;
s32 D_ovl10_12_80048F20[12];
UnkStructA *D_ovl10_12_80048F50[6];
s32 D_ovl10_12_80048F68[6][3];
s32 D_ovl10_12_80048FB0[6];
s32 D_ovl10_12_80048FC8[6];
s32 D_ovl10_12_80048FE0[64];
s32 D_ovl10_12_800490E0;
u8 D_ovl10_12_800490E4[0x4]; /* unused (func_ovl10_12_800471E8) */
s32 D_ovl10_12_800490E8[6];
s32 D_ovl10_12_80049100[6];
s32 D_ovl10_12_80049118;
u8 D_ovl10_12_8004911C[0x4]; /* unused (func_ovl10_12_800471E8) */
f32 D_ovl10_12_80049120[6];
f32 D_ovl10_12_80049138[6];
s32 D_ovl10_12_80049150;
s32 D_ovl10_12_80049154;
/* the tasks: a countdown and a function each */
s32 D_ovl10_12_80049158[64];
s32 D_ovl10_12_80049258; /* the running task */
u8 D_ovl10_12_8004925C[0x4]; /* unused (func_ovl10_12_800471E8) */
void (*D_ovl10_12_80049260[64])(void);
UnkStruct_ovl10_12_80048160 *D_ovl10_12_80049360;
s32 *D_ovl10_12_80049364;
s32 D_ovl10_12_80049368[4][3];
UnkStructA *D_ovl10_12_80049398[4];
s32 D_ovl10_12_800493A8;
u8 D_ovl10_12_800493AC[0x4]; /* unused (func_ovl10_12_800471E8) */
s32 D_ovl10_12_800493B0[4];
s32 D_ovl10_12_800493C0[4];
s32 D_ovl10_12_800493D0[5];
s32 D_ovl10_12_800493E4;
f32 D_ovl10_12_800493E8;
f32 D_ovl10_12_800493EC;
f32 D_ovl10_12_800493F0;
u8 D_ovl10_12_800493F4[0x4]; /* unused (func_ovl10_12_800471E8) */
s32 D_ovl10_12_800493F8[6][3];
UnkStructA *D_ovl10_12_80049440[6];
UnkStructA *D_ovl10_12_80049458;
s32 D_ovl10_12_8004945C;
s32 D_ovl10_12_80049460;
s32 D_ovl10_12_80049464;
s32 D_ovl10_12_80049468;
s32 D_ovl10_12_8004946C;
s32 D_ovl10_12_80049470[6];
s32 D_ovl10_12_80049488[6];
s32 D_ovl10_12_800494A0[6];
s32 D_ovl10_12_800494B8;
u8 D_ovl10_12_800494BC[0x4]; /* unused (func_ovl10_12_800471E8) */
s32 D_ovl10_12_800494C0[6];
s32 D_ovl10_12_800494D8[6];
s32 D_ovl10_12_800494F0[6];
s32 D_ovl10_12_80049508[6];
s32 D_ovl10_12_80049520[6];
f32 D_ovl10_12_80049538;
f32 D_ovl10_12_8004953C;
f32 D_ovl10_12_80049540;
f32 D_ovl10_12_80049544;
f32 D_ovl10_12_80049548;
f32 D_ovl10_12_8004954C;
f32 D_ovl10_12_80049550;
u8 D_ovl10_12_80049554[0x4]; /* unused (func_ovl10_12_800471E8) */
UnkStructA *D_ovl10_12_80049558[28];
UnkStructA *D_ovl10_12_800495C8[28];
s32 D_ovl10_12_80049638[27][3];
u8 D_ovl10_12_8004977C[0x4]; /* unused (func_ovl10_12_800471E8) */
s32 D_ovl10_12_80049780[28];
s32 D_ovl10_12_800497F0[28];
s32 D_ovl10_12_80049860[64];
s32 D_ovl10_12_80049960;
u8 D_ovl10_12_80049964[0x4]; /* unused (func_ovl10_12_800471E8) */
s32 D_ovl10_12_80049968[28];
s32 D_ovl10_12_800499D8[28];
s32 D_ovl10_12_80049A48[27][4];
f32 D_ovl10_12_80049BF8[28];
f32 D_ovl10_12_80049C68[28];
f32 D_ovl10_12_80049CD8[27];
s32 D_ovl10_12_80049D44;
s32 D_ovl10_12_80049D48;
s32 D_ovl10_12_80049D4C;
s32 D_ovl10_12_80049D50[64];
s32 D_ovl10_12_80049E50;
s32 D_ovl10_12_80049E54;

/* .data */
u32 D_ovl10_12_800488A0[] = { 0x14, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40900000, 0x0, 0x0, 0xBE75C28F, 0x0, 0x0, 0x0, 0x0 };
u32 D_ovl10_12_800488E4[] = { 0x14, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xC0900000, 0x0, 0x0, 0x3E75C28F, 0x0, 0x0, 0x0, 0x0 };
u32 D_ovl10_12_80048928[][3] = { { 0xA60002, 0xE, 0x4 }, { 0xA50002, 0xF, 0x4 }, { 0xA70000, 0xE, 0x4 } };
s32 D_ovl10_12_8004894C[] = { 0x14, 0x3, 0x2, 0x3A, 0x2, 0x17, 0x3, 0x2, 0x3A, 0x2, 0x1A, 0x3, 0x2, 0x3A, 0x2, 0x1D, 0x3, 0x2, 0x3A, 0x2, 0x14, 0x3, 0x1B, 0x3A, 0x2, 0x17, 0x3, 0x1B, 0x3A, 0x2, 0x1A, 0x3, 0x1B, 0x3A, 0x2, 0x1D, 0x3, 0x1B, 0x3A, 0x2, 0x21, 0x3, 0xE, 0x4A, 0x1, 0x23, 0x3, 0xE, 0x4A, 0x1, 0x25, 0x3, 0xE, 0x4A, 0x1, -1 };
s32 D_ovl10_12_80048A2C[] = { 0xB, 0x3, 0x9, 0x5, 0x2, 0x0, 0xB, 0x3, 0x13, 0x5, 0x2, 0x0, 0x10, 0x3, 0xE, 0x5, 0x1, 0x0, 0x17, 0x3, 0xE, 0x5, 0x1, 0x0, -1 };
s32 D_ovl10_12_80048A90[] = { 0x1, 0x3, 0xF, -0xFF, 0x1, 0x1, 0x0, 0x72, 0x11, 0x0, 0x0, 0xE, 0x2, 0xF, 0x0, 0x2, 0x0, 0x2, 0x40, 0x2, 0x40, 0x2, -1 };
s32 D_ovl10_12_80048AEC[] = { 0x2D, 0x3, 0xE, 0x1, 0x2D, 0x3, 0x10, 0x2, -1 };

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_12_80047238(void) {
}

static void func_ovl10_12_80047230(void) {
}

static void func_ovl10_12_80047228(void) {
}

static void func_ovl10_12_80047220(void) {
}

static void func_ovl10_12_80047218(void) {
}

static void func_ovl10_12_80047210(void) {
}

static void func_ovl10_12_80047208(void) {
}

static void func_ovl10_12_80047200(void) {
}

static void func_ovl10_12_800471F8(void) {
}

static void func_ovl10_12_800471F0(void) {
}

void func_ovl10_12_800471E8(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_12_80048C30[0] = D_ovl10_12_80048C5C[0] + D_ovl10_12_80048C6C[0] + D_ovl10_12_80048D24[0] +
                                 D_ovl10_12_80048E8C[0] + D_ovl10_12_800490E4[0] + D_ovl10_12_8004911C[0] +
                                 D_ovl10_12_8004925C[0] + D_ovl10_12_800493AC[0] + D_ovl10_12_800493F4[0] +
                                 D_ovl10_12_800494BC[0] + D_ovl10_12_80049554[0] + D_ovl10_12_8004977C[0] +
                                 D_ovl10_12_80049964[0];
    }
}

void func_ovl10_12_800471D0(void) {
    D_ovl10_12_80048C54 = -1;
    D_ovl10_12_80048C58 = -1;
}

void func_ovl10_12_80047174(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_12_80047DC8(D_ovl10_12_80048C60.x, D_ovl10_12_80048C60.y, D_ovl10_12_80048C60.z);
    func_ovl10_12_80047DE8(arg0, arg1, arg2);
    func_ovl10_12_800480F8(180);
}

void func_ovl10_12_8004712C(f32 arg0) {
    f32 sp1C;

    func_ovl10_12_80047DF0(&sp1C, NULL, NULL);
    func_ovl10_12_80047DE8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_12_800470F8(s32 arg0, UnkStructA *arg1) {
    func_ovl10_12_80048680(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_12_80047008(void) {
    s32 i;

    D_ovl10_12_80049150 = 0;
    D_ovl10_12_80049154 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_12_80049260[i] != NULL) {
                D_ovl10_12_80049258 = i;
                if (D_ovl10_12_80049158[i] == 0) {
                    D_ovl10_12_80049260[i]();
                } else {
                    D_ovl10_12_80049158[i]--;
                }
            }
        }
        D_ovl10_12_80049150++;
        D_ovl10_12_80049150 &= 3;
        func_ovl10_12_80048120();
    }
}

/* Defined above its caller 80046FD0, which pulls it out among the earlier
 * functions all the same: only so does its string come first in .rodata. */
s32 func_ovl10_12_80043150(void (*arg0)(void)) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_12_80049260[i] == NULL) {
            D_ovl10_12_80049260[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_12_80047248("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_12_80046FD0(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_12_80043150(arg0);
    func_ovl10_12_80047248("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_12_80046FA4(void (*arg0)(void)) {
    D_ovl10_12_80049260[func_ovl10_12_80046F60(arg0)] = NULL;
}

s32 func_ovl10_12_80046F60(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_12_80049260[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_12_80046F4C(s32 arg0) {
    D_ovl10_12_80049260[arg0] = NULL;
}

void func_ovl10_12_80046F30(s32 arg0) {
    D_ovl10_12_80049158[D_ovl10_12_80049258] = arg0;
}

void func_ovl10_12_80046F14(void (*arg0)(void)) {
    D_ovl10_12_80049260[D_ovl10_12_80049258] = arg0;
}

void func_ovl10_12_80046E84(void) {
    D_ovl10_12_80049360 = func_ovl10_12_80048160();
    func_ovl10_12_80048170(D_ovl10_12_80049360, 0x20000001);
    D_ovl10_12_80049360->unk40 = 0.5f;
    D_ovl10_12_80049360->unk44 = D_ovl10_12_80049360->unk40 * 0.75f;
    D_ovl10_12_80049360->unk18 = 0.1f;
    D_ovl10_12_80049360->unk1C = -0.1f;
}

void func_ovl10_12_80046E48(void) {
    s32 *p;

    p = func_ovl10_12_80048370();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_12_80046DDC(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_12_80047E30(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_12_80048008(arg0);
        func_ovl10_12_80048120();
    }
}

void func_ovl10_12_80046D5C(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_12_800483D8(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_12_80047F90(arg0, 0x01000000);
        func_ovl10_12_800480F8(5);
        func_ovl10_12_800483D8(0, 0, 0, 0.0f);
        func_ovl10_12_80048058(arg0, &pos);
        func_ovl10_12_80048530(12, &pos, 0);
    }
}

void func_ovl10_12_80046908(void) {
    s32 y;
    s32 i;
    s32 a;
    s32 b;
    s32 out[6];
    s32 *flags;

    i = D_ovl10_12_800493E4;
    D_ovl10_12_80049458 = func_ovl10_12_800477C8(func_ovl10_12_80047768());
    D_ovl10_12_80049440[i]->unk40->unk14 += D_ovl10_12_800493E8;
    D_ovl10_12_80049458->unk40->unk14 = D_ovl10_12_80049440[i]->unk40->unk14;
    D_ovl10_12_800493E8 += D_ovl10_12_800493EC;
    if (D_ovl10_12_80049550 != -1.0f &&
        ((D_ovl10_12_800493E8 > 0.0f && D_ovl10_12_80049550 <= D_ovl10_12_80049440[i]->unk40->unk14) ||
         (D_ovl10_12_800493E8 < 0.0f && D_ovl10_12_80049440[i]->unk40->unk14 <= D_ovl10_12_80049550))) {
        D_ovl10_12_800493EC = -D_ovl10_12_800493EC;
        D_ovl10_12_80049550 = -1.0f;
    }
    if (D_ovl10_12_800493F0 != -1.0f &&
        (D_ovl10_12_800493E8 == 0.0f ||
         (D_ovl10_12_800493E8 > 0.0f && D_ovl10_12_800493F0 < D_ovl10_12_80049440[i]->unk40->unk14) ||
         (D_ovl10_12_800493E8 < 0.0f && D_ovl10_12_80049440[i]->unk40->unk14 < D_ovl10_12_800493F0))) {
        flags = func_ovl10_12_800476D8();
        if (!(*flags & 2)) {
            func_ovl10_12_800476F0(1);
        }
        func_ovl10_12_8004555C();
        D_ovl10_12_80049458->unk70 = 1.6333334f;
        if (D_ovl10_12_800493E8 != 0.0f) {
            D_ovl10_12_80049440[i]->unk40->unk14 = D_ovl10_12_800493F0;
            D_ovl10_12_80049458->unk40->unk14 = D_ovl10_12_800493F0;
        }
        if (D_ovl10_12_80049470[i] == 2) {
            func_ovl10_12_800475E0(D_ovl10_12_80049440[i]->unk40->unk10, D_ovl10_12_80049440[i]->unk40->unk14,
                                   D_ovl10_12_80049440[i]->unk40->unk18, out, 2);
            y = out[1];
            func_ovl10_12_80047630(D_ovl10_12_800493F8[i][0], D_ovl10_12_800493F8[i][1], D_ovl10_12_800493F8[i][2],
                                   D_ovl10_12_800493F8[i][0] + 1, D_ovl10_12_800493F8[i][2] + 1,
                                   D_ovl10_12_800493F8[i][0], y, D_ovl10_12_800493F8[i][2]);
            func_ovl10_12_80047638(D_ovl10_12_800493F8[i][0], D_ovl10_12_800493F8[i][1], D_ovl10_12_800493F8[i][2],
                                   D_ovl10_12_800493F8[i][0] + 1, D_ovl10_12_800493F8[i][2] + 1, 0);
            D_ovl10_12_800494C0[i] = D_ovl10_12_800493F8[i][1];
            D_ovl10_12_800493F8[i][1] = y;
            if (D_ovl10_12_800493E8 > 0.0f) {
                a = D_ovl10_12_800494D8[i];
                b = D_ovl10_12_800494F0[i];
            } else {
                a = D_ovl10_12_80049508[i];
                b = D_ovl10_12_80049520[i];
            }
            func_ovl10_12_80047788(a, 3, 8.5f, b, 1, 1, 1);
            func_ovl10_12_80047E58(0.1f);
            func_ovl10_12_80047E70(40.0f);
        }
        func_ovl10_12_80047640(0);
        if (!(*flags & 2)) {
            func_ovl10_12_80047778(0);
        }
        func_ovl10_12_80048150(0xD0, 0xD0);
    }
}

void func_ovl10_12_80046828(void) {
    if (D_ovl10_12_80049D44 != 0) {
        func_ovl10_12_800483D8(0xFF, 0, 0, D_ovl10_12_80049E50);
    }
    D_ovl10_12_80049E50 += D_ovl10_12_80049E54;
    if (D_ovl10_12_80049E54 == 2 && D_ovl10_12_80049E50 >= 60) {
        D_ovl10_12_80049E54 = -2;
        D_ovl10_12_80049E50 = 60;
    }
    if (D_ovl10_12_80049E54 == -2 && D_ovl10_12_80049E50 <= 0) {
        D_ovl10_12_80049E54 = 2;
        D_ovl10_12_80049E50 = 0;
        func_ovl10_12_80048660(0x9E);
    }
    if (D_ovl10_12_80049D44 == 0) {
        func_ovl10_12_8004555C();
    }
}

void func_ovl10_12_80046608(void) {
    s32 i;

    i = D_ovl10_12_80049D50[D_ovl10_12_80049258];
    if (D_ovl10_12_80049D48 == 0) {
        D_ovl10_12_80049C68[i] += D_ovl10_12_80049BF8[i];
        D_ovl10_12_80049558[i]->unk40->unk36 = D_ovl10_12_80049C68[i];
        D_ovl10_12_800495C8[i]->unk40->unk36 = D_ovl10_12_80049C68[i] * 0.5f;
        D_ovl10_12_800495C8[i]->unk40->unk2C += D_ovl10_12_80049CD8[i];
        if (D_ovl10_12_80049BF8[i] > 0.0f && D_ovl10_12_80049558[i]->unk40->unk36 >= 256) {
            D_ovl10_12_80049558[i]->unk40->unk36 = 255;
            D_ovl10_12_800495C8[i]->unk40->unk36 = 128;
            func_ovl10_12_8004555C();
        }
        if (D_ovl10_12_80049BF8[i] < 0.0f && D_ovl10_12_80049558[i]->unk40->unk36 < 0) {
            if (D_ovl10_12_80049558[i] != NULL) {
                func_ovl10_12_80047FA0(D_ovl10_12_80049558[i]);
                func_ovl10_12_80047FA0(D_ovl10_12_800495C8[i]);
                D_ovl10_12_80049558[i] = NULL;
                func_ovl10_12_80045FE4(i, 0);
            }
            func_ovl10_12_8004555C();
        }
    } else {
        func_ovl10_12_8004555C();
    }
}

void func_ovl10_12_80046590(s32 arg0) {
    if (arg0 != D_ovl10_12_80049D44) {
        D_ovl10_12_80049D44 = arg0;
        if (arg0 == 1) {
            func_ovl10_12_80046550();
        } else {
            func_ovl10_12_800483D8(0, 0, 0, 0.0f);
        }
    }
}

void func_ovl10_12_80046550(void) {
    D_ovl10_12_80049E50 = 0;
    D_ovl10_12_80049E54 = 2;
    func_ovl10_12_80043150(func_ovl10_12_80046828);
    func_ovl10_12_80048660(0x9E);
}

void func_ovl10_12_8004635C(void) {
    s32 i;
    s32 j;
    s32 found;
    s32 k;

    i = D_ovl10_12_80049860[D_ovl10_12_80049258];
    found = -1;
    j = 0;
    do {
        if (D_ovl10_12_80049968[i] == D_ovl10_12_80049A48[i][j]) {
            D_ovl10_12_80049780[i] = 0;
            found = 0;
            D_ovl10_12_800497F0[i]++;
            func_ovl10_12_80046048(i, 1);
        }
        j++;
    } while (D_ovl10_12_80049A48[i][j] != -1 && found == -1);
    if (D_ovl10_12_800497F0[i] != 0) {
        D_ovl10_12_80049780[i]++;
        if (D_ovl10_12_80049780[i] == 80) {
            D_ovl10_12_800497F0[i] = 0;
            func_ovl10_12_80046048(i, 0);
        }
    }
    if (D_ovl10_12_80049D48 != 0) {
        for (k = 0; k < D_ovl10_12_80049960; k++) {
            if (D_ovl10_12_80049558[k] != NULL) {
                func_ovl10_12_80047FA0(D_ovl10_12_80049558[k]);
                func_ovl10_12_80047FA0(D_ovl10_12_800495C8[k]);
                D_ovl10_12_80049558[k] = NULL;
                func_ovl10_12_80045FE4(k, 0);
                D_ovl10_12_800497F0[k] = 0;
            }
        }
        func_ovl10_12_8004555C();
    }
    D_ovl10_12_80049968[i]++;
    if (D_ovl10_12_80049968[i] == D_ovl10_12_800499D8[i]) {
        D_ovl10_12_80049968[i] = 40;
    }
}

void func_ovl10_12_80046048(s32 arg0, s32 arg1) {
    Vec3f pos;
    Vec3f pos2;

    D_ovl10_12_80049D50[func_ovl10_12_80043150(func_ovl10_12_80046608)] = arg0;
    if (arg1 != 0) {
        D_ovl10_12_80049558[arg0] = func_ovl10_12_80047FB0(0xBE, 0x01080000, 0x10, 0);
        func_ovl10_12_800475E8(D_ovl10_12_80049638[arg0][0], D_ovl10_12_80049638[arg0][1],
                               D_ovl10_12_80049638[arg0][2], &pos, 0);
        D_ovl10_12_80049558[arg0]->unk40->unk10 = pos.x;
        D_ovl10_12_80049558[arg0]->unk40->unk14 = pos.y + 10.0f;
        D_ovl10_12_80049558[arg0]->unk40->unk18 = pos.z;
        D_ovl10_12_80049558[arg0]->unk40->unk36 = 0;
        D_ovl10_12_80049BF8[arg0] = 12.0f;
        D_ovl10_12_80049C68[arg0] = 0.0f;
        D_ovl10_12_800495C8[arg0] = func_ovl10_12_80047FB0(0x2A7, 0x01080000, 0x10, 0);
        func_ovl10_12_800475E8(D_ovl10_12_80049638[arg0][0], D_ovl10_12_80049638[arg0][1],
                               D_ovl10_12_80049638[arg0][2], &pos, 0);
        D_ovl10_12_800495C8[arg0]->unk40->unk10 = pos.x + 40.0f;
        D_ovl10_12_800495C8[arg0]->unk40->unk14 = pos.y;
        D_ovl10_12_800495C8[arg0]->unk40->unk18 = pos.z + 40.0f;
        D_ovl10_12_800495C8[arg0]->unk40->unk28 = 2.0f;
        D_ovl10_12_800495C8[arg0]->unk40->unk2C = 2.0f;
        D_ovl10_12_800495C8[arg0]->unk40->unk30 = 2.0f;
        D_ovl10_12_800495C8[arg0]->unk40->unkC |= 0x8000;
        func_ovl10_12_80047C90(D_ovl10_12_800495C8[arg0]->unk40, 2);
        func_ovl10_12_80047C98(D_ovl10_12_800495C8[arg0]->unk40, 0x2A8, 0, 0);
        func_ovl10_12_80047C98(D_ovl10_12_800495C8[arg0]->unk40, 0x2A8, 1, 1);
        D_ovl10_12_800495C8[arg0]->unk40->unk36 = 0;
        D_ovl10_12_80049CD8[arg0] = 0.1f;
        func_ovl10_12_80045FE4(arg0, 1);
        func_ovl10_12_80048058(D_ovl10_12_800495C8[arg0], &pos2);
        func_ovl10_12_80048688(0xAA, &pos2);
    } else {
        D_ovl10_12_80049BF8[arg0] = -6.0f;
        D_ovl10_12_80049C68[arg0] = 255.0f;
        D_ovl10_12_80049CD8[arg0] = -0.1f;
    }
}

void func_ovl10_12_80045FE4(s32 arg0, s32 arg1) {
    s32 v;

    if (arg1 != 0) {
        v = 1;
    } else {
        v = 11;
    }
    func_ovl10_12_80047638(D_ovl10_12_80049638[arg0][0], D_ovl10_12_80049638[arg0][1], D_ovl10_12_80049638[arg0][2],
                           D_ovl10_12_80049638[arg0][0] + 1, D_ovl10_12_80049638[arg0][2] + 1, v);
}

void func_ovl10_12_80045F18(void) {
    s32 i;

    if (D_ovl10_12_80049D4C == 0) {
        for (i = 0; i < D_ovl10_12_80049960; i++) {
            D_ovl10_12_80049860[func_ovl10_12_80043150(func_ovl10_12_8004635C)] = i;
            D_ovl10_12_80049968[i] = 0;
            D_ovl10_12_80049780[i] = 0;
        }
        D_ovl10_12_80049D4C = 1;
        D_ovl10_12_80049D48 = 0;
    }
}

void func_ovl10_12_80045F00(void) {
    D_ovl10_12_80049D48 = 1;
    D_ovl10_12_80049D4C = 0;
}

void func_ovl10_12_80045D94(s32 *arg0) {
    s32 i;
    s32 j;
    s32 n;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_12_80049638[i][0] = arg0[0];
            D_ovl10_12_80049638[i][1] = arg0[1];
            D_ovl10_12_80049638[i][2] = arg0[2];
            D_ovl10_12_800499D8[i] = arg0[3];
            n = arg0[4];
            arg0 += 5;
            for (j = 0; j < n; j++) {
                D_ovl10_12_80049A48[i][j] = *arg0;
                arg0++;
            }
            D_ovl10_12_80049A48[i][n] = -1;
            D_ovl10_12_800497F0[i] = 0;
            D_ovl10_12_80049558[i] = NULL;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_12_80049960 = i;
    D_ovl10_12_80049D44 = 0;
    D_ovl10_12_80049D48 = 0;
    D_ovl10_12_80049D4C = 0;
    func_ovl10_12_800483D8(0, 0, 0, 0.0f);
}

void func_ovl10_12_80045A78(void) {
    s32 i;
    s32 j;
    s32 v;

    i = D_ovl10_12_80048D88[D_ovl10_12_80049258];
    D_ovl10_12_80048E90[i]--;
    func_ovl10_12_800459D8(i);
    if (D_ovl10_12_80048E90[i] == 0) {
        D_ovl10_12_80048D58[i] = (D_ovl10_12_80048D58[i] + 2) & 3;
        if (D_ovl10_12_80048D58[i] & 2) {
            func_ovl10_12_80043EE4(i);
            D_ovl10_12_80048E90[i] = func_ovl10_12_80048298(60) + 90;
            v = 9;
        } else {
            func_ovl10_12_80043E6C(i);
            v = 1;
            D_ovl10_12_80048E90[i] = 120;
        }
        if (D_ovl10_12_80048D28[i] & 1) {
            for (j = 0; j < D_ovl10_12_80048F20[i]; j++) {
                func_ovl10_12_800475C0(D_ovl10_12_80048CA0[i][0] + j, D_ovl10_12_80048CA0[i][1], D_ovl10_12_80048CA0[i][2], v);
            }
        } else {
            for (j = 0; j < D_ovl10_12_80048F20[i]; j++) {
                func_ovl10_12_800475C0(D_ovl10_12_80048CA0[i][0], D_ovl10_12_80048CA0[i][1], D_ovl10_12_80048CA0[i][2] + j, v);
            }
        }
        if (D_ovl10_12_80049D44 != 0) {
            D_ovl10_12_80048E90[i] = 30;
        }
    }
    if (D_ovl10_12_80048EC0[i] != 0) {
        if (D_ovl10_12_80048D58[i] & 2) {
            func_ovl10_12_80043E6C(i);
            if (D_ovl10_12_80048D28[i] & 1) {
                for (j = 0; j < D_ovl10_12_80048F20[i]; j++) {
                    func_ovl10_12_800475C0(D_ovl10_12_80048CA0[i][0] + j, D_ovl10_12_80048CA0[i][1], D_ovl10_12_80048CA0[i][2], 1);
                }
            } else {
                for (j = 0; j < D_ovl10_12_80048F20[i]; j++) {
                    func_ovl10_12_800475C0(D_ovl10_12_80048CA0[i][0], D_ovl10_12_80048CA0[i][1], D_ovl10_12_80048CA0[i][2] + j, 1);
                }
            }
        }
        func_ovl10_12_8004555C();
    }
}

void func_ovl10_12_800459D8(s32 arg0) {
    f32 d;

    if (D_ovl10_12_80048D58[arg0] & 1) {
        d = func_ovl10_12_80045768(arg0);
        if (D_ovl10_12_80048F1C == -1 && (D_ovl10_12_80048D58[arg0] & 2) && d <= 300.0f) {
            func_ovl10_12_800457C0(arg0, 1);
        } else {
            func_ovl10_12_800457C0(arg0, 0);
        }
    }
}

void func_ovl10_12_80045924(void) {
    s32 i;
    f32 d;

    i = D_ovl10_12_80048D88[D_ovl10_12_80049258];
    d = func_ovl10_12_80045768(i);
    if (D_ovl10_12_80048F1C == -1 && d <= 300.0f) {
        func_ovl10_12_800457C0(i, 1);
    } else {
        func_ovl10_12_800457C0(i, 0);
    }
    if (D_ovl10_12_80048EC0[i] != 0) {
        func_ovl10_12_8004555C();
    }
}

void func_ovl10_12_800457C0(s32 arg0, s32 arg1) {
    s32 pad[2];
    Vec3f pos;
    s32 i;
    s32 n;

    n = 0;
    for (i = 0; i < D_ovl10_12_80048E88; i++) {
        if ((D_ovl10_12_80048D58[i] & 2) && func_ovl10_12_80045768(i) <= 300.0f) {
            n++;
        }
    }
    if (arg1 != 0 && n == 1 && D_ovl10_12_80048F1C == -1) {
        func_ovl10_12_80048058(D_ovl10_12_80048C70[arg0], &pos);
        D_ovl10_12_80048F1C = func_ovl10_12_80048688(0x9D, &pos);
    }
    if (arg1 == 0 && n == 0 && D_ovl10_12_80048F1C != -1) {
        func_ovl10_12_80043060();
    }
}

f32 func_ovl10_12_80045768(s32 arg0) {
    s32 pad;
    Vec3f a;
    Vec3f b;

    func_ovl10_12_80048058(D_ovl10_12_80048C70[arg0], &a);
    func_ovl10_12_80048058(func_ovl10_12_800477C8(func_ovl10_12_80047768()), &b);
    return func_ovl10_12_80047F30(&a, &b);
}

void func_ovl10_12_800455B0(void) {
    s32 i;

    i = D_ovl10_12_80048FE0[D_ovl10_12_80049258];
    D_ovl10_12_80048F50[i]->unk40->unk28 += D_ovl10_12_80049120[i];
    D_ovl10_12_80048F50[i]->unk40->unk2C += D_ovl10_12_80049120[i];
    D_ovl10_12_80048F50[i]->unk40->unk30 += D_ovl10_12_80049120[i];
    if ((D_ovl10_12_80049120[i] > 0.0f && D_ovl10_12_80049138[i] <= D_ovl10_12_80048F50[i]->unk40->unk28) ||
        (D_ovl10_12_80049120[i] < 0.0f && D_ovl10_12_80048F50[i]->unk40->unk28 <= D_ovl10_12_80049138[i])) {
        D_ovl10_12_80048F50[i]->unk40->unk28 = D_ovl10_12_80049138[i];
        D_ovl10_12_80048F50[i]->unk40->unk2C = D_ovl10_12_80049138[i];
        D_ovl10_12_80048F50[i]->unk40->unk30 = D_ovl10_12_80049138[i];
        if (D_ovl10_12_80048FC8[i] == 0) {
            func_ovl10_12_80045578(i);
        }
        func_ovl10_12_80044A58(i);
        D_ovl10_12_80049100[i] = 0;
        func_ovl10_12_8004555C();
    }
}

void func_ovl10_12_80045578(s32 arg0) {
    func_ovl10_12_80047FA0(D_ovl10_12_80048F50[arg0]);
    D_ovl10_12_80048F50[arg0] = NULL;
}

void func_ovl10_12_8004555C(void) {
    D_ovl10_12_80049260[D_ovl10_12_80049258] = NULL;
}

void func_ovl10_12_800454EC(void) {
    func_ovl10_12_80048120();
    func_ovl10_12_80047778(1);
    func_ovl10_12_800476F0(0);
    func_ovl10_12_80047828(1);
    func_ovl10_12_80047790("WM1 WAP WG1 WSH WDE WB2 ST1 WDW WB30 ST240");
    func_ovl10_12_80047828(0);
    func_ovl10_12_80047790("WM1 WAP WG1 WSH WDE WB10");
    func_ovl10_12_800480F8(10);
    func_ovl10_12_800487D8();
    func_ovl10_12_800480E8();
}

void func_ovl10_12_80045478(void) {
    func_ovl10_12_80047DE8(45.0f, 32768.0f, 32768.0f);
    func_ovl10_12_800480F8(240);
    func_ovl10_12_80047E00(D_ovl10_12_800488A0, 0x170, 0);
    func_ovl10_12_800480F8(330);
    func_ovl10_12_80047E00(D_ovl10_12_800488E4, 0x170, 0);
    func_ovl10_12_800480E8();
}

void func_ovl10_12_800452C0(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl10_12_80045158();
            break;
        case 16:
            func_ovl10_12_800449AC();
            break;
        case 17:
            func_ovl10_12_80044904();
            break;
        case 25:
            func_ovl10_12_80044768();
            break;
        case 4:
            func_ovl10_12_80044740();
            break;
        case 5:
            func_ovl10_12_80044618();
            break;
        case 0x52:
            func_ovl10_12_800445A4();
            break;
        case 0x53:
            func_ovl10_12_80044538();
            break;
        case 0x50:
            func_ovl10_12_800437A8();
            break;
        case 1:
            func_ovl10_12_800430B0();
            break;
    }
}

void func_ovl10_12_80045158(void) {
    func_ovl10_12_80048440(D_ovl10_12_80048928);
    func_ovl10_12_800485E8(0, 0, 0xDE);
    func_ovl10_12_800485E8(1, 0x11, 0xEF);
    func_ovl10_12_800485E8(2, 0x1A, 0xF8);
    func_ovl10_12_800485E8(3, 0x1B, 0xF9);
    func_ovl10_12_800485E8(4, 0x18, 0xF6);
    func_ovl10_12_80047588(0x1F1);
    func_ovl10_12_80047590(0x1F2, 0.0f, 0.0f, 0.0f, 0x60, 0);
    func_ovl10_12_80047590(0xC7, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_12_80047590(0xC7, 0.0f, 12000.0f, 0.0f, 0x50, 0);
    func_ovl10_12_800475A0(0x1F9);
    func_ovl10_12_80048418(0x3C6, 0x3E8, 0, 0xFF, 0xFF);
    func_ovl10_12_80048428(0, 0xFF, 0xFF);
    func_ovl10_12_80047738();
    D_ovl10_12_80049D44 = 0;
    func_ovl10_12_80044FEC(D_ovl10_12_80048A90);
    func_ovl10_12_80044F38(D_ovl10_12_80048AEC);
    func_ovl10_12_80044C68(D_ovl10_12_8004894C);
    func_ovl10_12_80044B1C(D_ovl10_12_80048A2C);
    func_ovl10_12_800449DC();
}

/* reads records of 11 words up to a -1 */
void func_ovl10_12_80044FEC(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_12_800493F8[i][0] = arg0[0];
        D_ovl10_12_800493F8[i][1] = arg0[1];
        D_ovl10_12_800493F8[i][2] = arg0[2];
        D_ovl10_12_800494C0[i] = arg0[3];
        D_ovl10_12_80049470[i] = arg0[4];
        D_ovl10_12_80049488[i] = arg0[5];
        D_ovl10_12_800494A0[i] = arg0[6];
        D_ovl10_12_800494D8[i] = arg0[7];
        D_ovl10_12_800494F0[i] = arg0[8];
        D_ovl10_12_80049508[i] = arg0[9];
        D_ovl10_12_80049520[i] = arg0[10];
        arg0 += 11;
        func_ovl10_12_80043B44(i);
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_12_800494B8 = i;
}

void func_ovl10_12_80044F38(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_12_80049368[i][0] = arg0[0];
        D_ovl10_12_80049368[i][1] = arg0[1];
        D_ovl10_12_80049368[i][2] = arg0[2];
        D_ovl10_12_800493B0[i] = arg0[3];
        D_ovl10_12_800493C0[i] = 0;
        arg0 += 4;
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_12_800493A8 = i;
    for (i = 1; i < 5; i++) {
        D_ovl10_12_800493D0[i] = 0;
    }
}

void func_ovl10_12_80044C68(s32 *arg0) {
    s32 i;
    s32 j;
    s32 flags;
    s32 pad;
    Vec3f pos;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_12_80048CA0[i][0] = arg0[0];
            D_ovl10_12_80048CA0[i][1] = arg0[1];
            D_ovl10_12_80048CA0[i][2] = arg0[2];
            flags = arg0[3];
            D_ovl10_12_80048D28[i] = flags & 0xF;
            D_ovl10_12_80048F20[i] = flags >> 4;
            D_ovl10_12_80048EF0[i] = arg0[4];
            arg0 += 5;
            func_ovl10_12_800475E8(D_ovl10_12_80048CA0[i][0], D_ovl10_12_80048CA0[i][1], D_ovl10_12_80048CA0[i][2],
                                   &pos, 0);
            D_ovl10_12_80048C70[i] = func_ovl10_12_80047FB0(0xBD, 0, 0xD0, 0);
            D_ovl10_12_80048C70[i]->unk40->unk10 = pos.x;
            D_ovl10_12_80048C70[i]->unk40->unk14 = pos.y;
            D_ovl10_12_80048C70[i]->unk40->unk18 = pos.z;
            if (D_ovl10_12_80048D28[i] & 2) {
                D_ovl10_12_80048C70[i]->unk40->unk10 = pos.x + 5.0f;
                D_ovl10_12_80048C70[i]->unk40->unk20 = 270.0f;
            } else {
                D_ovl10_12_80048C70[i]->unk40->unk18 = pos.z - 5.0f;
            }
            func_ovl10_12_80047CD0(D_ovl10_12_80048C70[i]->unk40, 0, 0x28, 0x190, 0, 0);
            D_ovl10_12_80048D58[i] = 0;
            if (D_ovl10_12_80048D28[i] & 1) {
                for (j = 0; j < D_ovl10_12_80048F20[i]; j++) {
                    func_ovl10_12_800475C0(D_ovl10_12_80048CA0[i][0] + j, D_ovl10_12_80048CA0[i][1], D_ovl10_12_80048CA0[i][2], 1);
                }
            } else {
                for (j = 0; j < D_ovl10_12_80048F20[i]; j++) {
                    func_ovl10_12_800475C0(D_ovl10_12_80048CA0[i][0] + j, D_ovl10_12_80048CA0[i][1], D_ovl10_12_80048CA0[i][2], 1);
                }
            }
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_12_80048E88 = i;
    D_ovl10_12_80048F1C = -1;
}

void func_ovl10_12_80044B1C(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_12_80048F68[i][0] = arg0[0];
            D_ovl10_12_80048F68[i][1] = arg0[1];
            D_ovl10_12_80048F68[i][2] = arg0[2];
            D_ovl10_12_80048FB0[i] = arg0[3];
            D_ovl10_12_800490E8[i] = arg0[4];
            D_ovl10_12_80048FC8[i] = arg0[5];
            arg0 += 6;
            D_ovl10_12_80048F50[i] = NULL;
            if (D_ovl10_12_80048FC8[i] != 0) {
                func_ovl10_12_800437C8(i);
            }
            func_ovl10_12_80044A58(i);
            D_ovl10_12_80049100[i] = 0;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_12_800490E0 = i;
}

void func_ovl10_12_80044A58(s32 arg0) {
    s32 v;
    s32 w;
    s32 t;
    s32 h;
    s32 pad;

    if (D_ovl10_12_80048FC8[arg0] != 0) {
        v = 1;
    } else {
        v = 0;
    }
    if (D_ovl10_12_80048FB0[arg0] & 4) {
        w = 6;
        h = 3;
    }
    if (D_ovl10_12_80048FB0[arg0] & 8) {
        w = 5;
        h = 1;
    }
    if (D_ovl10_12_80048FB0[arg0] & 2) {
        t = h;
        h = w;
        w = t;
    }
    func_ovl10_12_80047638(D_ovl10_12_80048F68[arg0][0], D_ovl10_12_80048F68[arg0][1], D_ovl10_12_80048F68[arg0][2],
                           D_ovl10_12_80048F68[arg0][0] + w, D_ovl10_12_80048F68[arg0][2] + h, v);
}

void func_ovl10_12_800449DC(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_12_80049260[i] = NULL;
        D_ovl10_12_80049158[i] = 0;
    }
    func_ovl10_12_800480D8(func_ovl10_12_80047008, 0, 0, 0, 0x110);
}

/* empty, as ovl_10_11's 80043044: two words before 800449DC */
void func_ovl10_12_800449D4(void) {
}

void func_ovl10_12_800449AC(void) {
    func_ovl10_12_80047740(0x18, 2, 0x10);
}

void func_ovl10_12_80044904(void) {
    D_ovl10_12_800493E4 = 0;
    D_ovl10_12_8004945C = 3;
    D_ovl10_12_80049538 = 1100.0f;
    D_ovl10_12_8004953C = 90.0f;
    D_ovl10_12_80049460 = 1;
    D_ovl10_12_80049464 = 0xF;
    D_ovl10_12_80049540 = 21.0f;
    D_ovl10_12_80049544 = 0.2f;
    D_ovl10_12_80049548 = 50.0f;
    D_ovl10_12_8004954C = 50.0f;
    func_ovl10_12_800447A0();
    D_ovl10_12_80049118 = 1;
}

void func_ovl10_12_800447A0(void) {
    f32 y;

    D_ovl10_12_80049550 = -1.0f;
    y = func_ovl10_12_80047628(D_ovl10_12_8004945C);
    func_ovl10_12_80047740(D_ovl10_12_80049460, D_ovl10_12_8004945C, D_ovl10_12_80049464);
    func_ovl10_12_80047778(1);
    D_ovl10_12_80049458 = func_ovl10_12_800477C8(func_ovl10_12_80047768());
    D_ovl10_12_80049458->unk70 = 0.0f;
    D_ovl10_12_80049458->unk40->unk10 += D_ovl10_12_80049548;
    D_ovl10_12_80049458->unk40->unk14 += D_ovl10_12_80049538;
    D_ovl10_12_80049458->unk40->unk18 += D_ovl10_12_8004954C;
    D_ovl10_12_80049458->unk40->unk20 = D_ovl10_12_8004953C;
    D_ovl10_12_80049440[D_ovl10_12_800493E4]->unk40->unk14 += D_ovl10_12_80049538;
    func_ovl10_12_800431C8(D_ovl10_12_800493E4, D_ovl10_12_80049540, D_ovl10_12_80049544, y);
    D_ovl10_12_80049458->unk70 = 1.6333334f;
}

void func_ovl10_12_80044768(void) {
    func_ovl10_12_80047740(0x2B, 3, 0x10);
    func_ovl10_12_80047780(0x40);
    D_ovl10_12_80049118 = 9;
}

void func_ovl10_12_80044740(void) {
    func_ovl10_12_80047798();
    func_ovl10_12_800446B0();
}

void func_ovl10_12_800446B0(void) {
    D_ovl10_12_80049364 = func_ovl10_12_800476D8();
    if (*D_ovl10_12_80049364 & 2) {
        func_ovl10_12_800480D8(func_ovl10_12_800454EC, 0, 0, 0, 0x130);
        func_ovl10_12_800480D8(func_ovl10_12_80045478, 0, 0, 0, 0x130);
        func_ovl10_12_80047E30(15);
        func_ovl10_12_80047E40(2);
        func_ovl10_12_80048608(0);
    }
}

void func_ovl10_12_80044618(void) {
    D_ovl10_12_800493C0[0] = 1;
    func_ovl10_12_80044218(0, 1);
    D_ovl10_12_800493D0[1] = 1;
    func_ovl10_12_80044168();
    func_ovl10_12_80043AA0();
    func_ovl10_12_80047670(func_ovl10_12_80046D5C);
    if (D_ovl10_12_80049118 == 1) {
        func_ovl10_12_800480F8(0x78);
        func_ovl10_12_80047788(0x40, 3, 8.5f, 2, 0, 1, 1);
    }
}

void func_ovl10_12_800445A4(void) {
    func_ovl10_12_800434D8(2);
    if (func_ovl10_12_80047758(D_ovl10_12_80049368[0][0], D_ovl10_12_80049368[0][1], D_ovl10_12_80049368[0][2],
                               D_ovl10_12_80049368[0][0] + 1, D_ovl10_12_80049368[0][2] + 1) != 0) {
        func_ovl10_12_80048660(0x29);
    }
    func_ovl10_12_80044370();
    func_ovl10_12_80044168();
    func_ovl10_12_80043C98();
    func_ovl10_12_80043AA0();
}

void func_ovl10_12_80044538(void) {
    if (func_ovl10_12_80047758(D_ovl10_12_80049368[1][0], D_ovl10_12_80049368[1][1], D_ovl10_12_80049368[1][2],
                               D_ovl10_12_80049368[1][0] + 1, D_ovl10_12_80049368[1][2] + 1) != 0) {
        func_ovl10_12_80048660(0x29);
    }
    func_ovl10_12_80044370();
    func_ovl10_12_80044168();
    func_ovl10_12_80043C98();
    func_ovl10_12_80043AA0();
}

void func_ovl10_12_80044370(void) {
    s32 found;
    s32 i;

    found = -1;
    i = 0;
    do {
        if (func_ovl10_12_80047758(D_ovl10_12_80049368[i][0], D_ovl10_12_80049368[i][1], D_ovl10_12_80049368[i][2],
                                   D_ovl10_12_80049368[i][0] + 1, D_ovl10_12_80049368[i][2] + 1) != 0) {
            found = i;
        }
        i++;
    } while (i < D_ovl10_12_800493A8 && found == -1);
    if (found != -1) {
        D_ovl10_12_800493C0[found] = (D_ovl10_12_800493C0[found] + 1) % 2;
        func_ovl10_12_80044218(found, D_ovl10_12_800493C0[found]);
        D_ovl10_12_800493D0[D_ovl10_12_800493B0[found]] = (D_ovl10_12_800493D0[D_ovl10_12_800493B0[found]] + 1) % 2;
        if (D_ovl10_12_800493C0[found] == 1 && D_ovl10_12_800493B0[found] != 4) {
            for (i = 0; i < D_ovl10_12_800493A8; i++) {
                if (i != found && D_ovl10_12_800493B0[i] != 4 && D_ovl10_12_800493C0[i] == 1) {
                    D_ovl10_12_800493C0[i] = 0;
                    func_ovl10_12_80044218(i, 0);
                    D_ovl10_12_800493D0[D_ovl10_12_800493B0[i]] = 0;
                }
            }
        }
    }
}

void func_ovl10_12_80044218(s32 arg0, s32 arg1) {
    s32 sp38[4] = { 0xBF, 0xC0, 0xC1, 0xC4 };
    Vec3f pos;

    if (arg1 == 1) {
        D_ovl10_12_80049398[arg0] =
            func_ovl10_12_80047FB0(sp38[D_ovl10_12_800493B0[arg0] - 1], 0x01000000, 0xD0, 0);
        func_ovl10_12_800475E8(D_ovl10_12_80049368[arg0][0], D_ovl10_12_80049368[arg0][1],
                               D_ovl10_12_80049368[arg0][2], &pos, 0);
        D_ovl10_12_80049398[arg0]->unk40->unk10 = pos.x;
        D_ovl10_12_80049398[arg0]->unk40->unk14 = pos.y;
        D_ovl10_12_80049398[arg0]->unk40->unk18 = pos.z;
    } else {
        func_ovl10_12_80047FA0(D_ovl10_12_80049398[arg0]);
        D_ovl10_12_80049398[arg0] = NULL;
    }
}

void func_ovl10_12_80044168(void) {
    s32 i;

    if (D_ovl10_12_80049D44 == 0) {
        for (i = 0; i < D_ovl10_12_80048E88; i++) {
            if (D_ovl10_12_80048D58[i] != D_ovl10_12_800493D0[D_ovl10_12_80048EF0[i]]) {
                func_ovl10_12_80043F14(i, D_ovl10_12_800493D0[D_ovl10_12_80048EF0[i]]);
            }
        }
    }
}

void func_ovl10_12_80043F14(s32 arg0, s32 arg1) {
    s32 j;
    s32 v;
    s32 pad[2];

    if (arg1 != (D_ovl10_12_80048D58[arg0] & 1)) {
        if (arg1 != 0) {
            D_ovl10_12_80048D58[arg0] |= 1;
        } else {
            D_ovl10_12_80048D58[arg0] &= ~1;
        }
        if (D_ovl10_12_80048D28[arg0] & 4) {
            func_ovl10_12_80043EE4(arg0);
            if (arg1 != 0) {
                v = 9;
                D_ovl10_12_80048D58[arg0] |= 2;
                /* func_ovl10_12_80043E9C(arg0), written out */
                D_ovl10_12_80048D88[func_ovl10_12_80043150(func_ovl10_12_80045924)] = arg0;
                D_ovl10_12_80048EC0[arg0] = 0;
            } else {
                D_ovl10_12_80048D58[arg0] &= ~2;
                func_ovl10_12_80043E6C(arg0);
                v = 1;
                func_ovl10_12_80043DBC(arg0);
            }
            /* Nothing, but it keeps arg0 in v1 for the loops. */
            if (arg0) {
            }
            if (D_ovl10_12_80048D28[arg0] & 1) {
                for (j = 0; j < D_ovl10_12_80048F20[arg0]; j++) {
                    func_ovl10_12_800475C0(D_ovl10_12_80048CA0[arg0][0] + j, D_ovl10_12_80048CA0[arg0][1], D_ovl10_12_80048CA0[arg0][2], v);
                }
            } else {
                for (j = 0; j < D_ovl10_12_80048F20[arg0]; j++) {
                    func_ovl10_12_800475C0(D_ovl10_12_80048CA0[arg0][0], D_ovl10_12_80048CA0[arg0][1], D_ovl10_12_80048CA0[arg0][2] + j, v);
                }
            }
        }
        if (D_ovl10_12_80048D28[arg0] & 8) {
            if (arg1 != 0) {
                func_ovl10_12_80043DD4(arg0);
            } else {
                func_ovl10_12_80043DBC(arg0);
            }
        }
    }
}

void func_ovl10_12_80043EE4(s32 arg0) {
    func_ovl10_12_80047F88(D_ovl10_12_80048C70[arg0], 0x01000000);
}

void func_ovl10_12_80043E9C(s32 arg0) {
    D_ovl10_12_80048D88[func_ovl10_12_80043150(func_ovl10_12_80045924)] = arg0;
    D_ovl10_12_80048EC0[arg0] = 0;
}

void func_ovl10_12_80043E6C(s32 arg0) {
    func_ovl10_12_80047F90(D_ovl10_12_80048C70[arg0], 0x01000000);
}

void func_ovl10_12_80043DD4(s32 arg0) {
    D_ovl10_12_80048D88[func_ovl10_12_80043150(func_ovl10_12_80045A78)] = arg0;
    D_ovl10_12_80048EC0[arg0] = 0;
    if (D_ovl10_12_80049D44 != 0) {
        D_ovl10_12_80048E90[arg0] = 30;
    } else {
        D_ovl10_12_80048E90[arg0] = func_ovl10_12_80048298(60) + 90;
    }
    D_ovl10_12_80048D58[arg0] = 1;
}

void func_ovl10_12_80043DBC(s32 arg0) {
    D_ovl10_12_80048EC0[arg0] = 1;
}

void func_ovl10_12_80043C98(void) {
    s32 i;

    for (i = 0; i < D_ovl10_12_800494B8; i++) {
        if (D_ovl10_12_80049470[i] == 2 && D_ovl10_12_80049488[i] != D_ovl10_12_800493D0[D_ovl10_12_800494A0[i]]) {
            if (D_ovl10_12_80049440[i] != NULL) {
                func_ovl10_12_80043C60(i);
            }
            D_ovl10_12_80049488[i] = D_ovl10_12_800493D0[D_ovl10_12_800494A0[i]];
            func_ovl10_12_80043B44(i);
        }
    }
}

void func_ovl10_12_80043C60(s32 arg0) {
    func_ovl10_12_80047FA0(D_ovl10_12_80049440[arg0]);
    D_ovl10_12_80049440[arg0] = NULL;
}

void func_ovl10_12_80043B44(s32 arg0) {
    Vec3f pos;
    s32 sp2C[2] = { 0xCA, 0xB2 };

    D_ovl10_12_80049440[arg0] = func_ovl10_12_80047FB0(sp2C[D_ovl10_12_80049488[arg0]], 0x01000000, 0xD0, 0);
    func_ovl10_12_800475E8(D_ovl10_12_800493F8[arg0][0], D_ovl10_12_800493F8[arg0][1], D_ovl10_12_800493F8[arg0][2],
                           &pos, 0);
    D_ovl10_12_80049440[arg0]->unk40->unk10 = pos.x;
    D_ovl10_12_80049440[arg0]->unk40->unk14 = pos.y;
    D_ovl10_12_80049440[arg0]->unk40->unk18 = pos.z;
}

void func_ovl10_12_80043AA0(void) {
    s32 i;

    for (i = 0; i < D_ovl10_12_800490E0; i++) {
        if (D_ovl10_12_80048FC8[i] != D_ovl10_12_800493D0[D_ovl10_12_800490E8[i]]) {
            func_ovl10_12_800439A4(i, D_ovl10_12_800493D0[D_ovl10_12_800490E8[i]]);
        }
    }
}

void func_ovl10_12_800439A4(s32 arg0, s32 arg1) {
    D_ovl10_12_80048FC8[arg0] = arg1;
    if (D_ovl10_12_80049100[arg0] == 0) {
        D_ovl10_12_80048FE0[func_ovl10_12_80043150(func_ovl10_12_800455B0)] = arg0;
    }
    if (arg1 != 0) {
        D_ovl10_12_80049120[arg0] = 0.05f;
        D_ovl10_12_80049138[arg0] = 1.0f;
        if (D_ovl10_12_80048F50[arg0] == NULL) {
            func_ovl10_12_800437C8(arg0);
        }
        func_ovl10_12_80048660(0xA2);
    } else {
        D_ovl10_12_80049120[arg0] = -0.05f;
        D_ovl10_12_80049138[arg0] = 0.0f;
    }
    D_ovl10_12_80049100[arg0] = 1;
}

void func_ovl10_12_800437C8(s32 arg0) {
    s32 sp40[2] = { 0xC5, 0xC6 };
    Vec3f pos;

    func_ovl10_12_800475E8(D_ovl10_12_80048F68[arg0][0], D_ovl10_12_80048F68[arg0][1], D_ovl10_12_80048F68[arg0][2], &pos, 0);
    D_ovl10_12_80048F50[arg0] = func_ovl10_12_80047FB0(sp40[(D_ovl10_12_80048FB0[arg0] >> 2) - 1], 0x01080000, 0xD0, 0);
    D_ovl10_12_80048F50[arg0]->unk40->unk10 = pos.x;
    D_ovl10_12_80048F50[arg0]->unk40->unk14 = pos.y;
    D_ovl10_12_80048F50[arg0]->unk40->unk18 = pos.z;
    D_ovl10_12_80048F50[arg0]->unk40->unk28 = 0.0f;
    D_ovl10_12_80048F50[arg0]->unk40->unk2C = 0.0f;
    D_ovl10_12_80048F50[arg0]->unk40->unk30 = 0.0f;
    if (D_ovl10_12_80048FB0[arg0] & 2) {
        if (D_ovl10_12_80048FB0[arg0] & 4) {
            D_ovl10_12_80048F50[arg0]->unk40->unk18 += 600.0f;
        }
        if (D_ovl10_12_80048FB0[arg0] & 8) {
            D_ovl10_12_80048F50[arg0]->unk40->unk18 += 500.0f;
        }
        D_ovl10_12_80048F50[arg0]->unk40->unk20 = 90.0f;
    }
}

void func_ovl10_12_800437A8(void) {
    func_ovl10_12_800434D8(1);
}

s32 func_ovl10_12_800434D8(s32 arg0) {
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    if (arg0 == 2) {
        do {
            if (D_ovl10_12_80049470[i] == 2 && D_ovl10_12_80049488[i] == 1 &&
                func_ovl10_12_80047758(D_ovl10_12_800493F8[i][0], D_ovl10_12_800493F8[i][1],
                                       D_ovl10_12_800493F8[i][2], D_ovl10_12_800493F8[i][0] + 1,
                                       D_ovl10_12_800493F8[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_12_800494B8 && found == 0);
        if (found) {
            D_ovl10_12_800493E4 = i;
            if (D_ovl10_12_800494C0[i] < D_ovl10_12_800493F8[i][1]) {
                D_ovl10_12_80049540 = 0.0f;
                D_ovl10_12_80049544 = -0.2f;
            } else {
                D_ovl10_12_80049540 = -0.0f;
                D_ovl10_12_80049544 = 0.2f;
            }
        }
    } else {
        do {
            if (func_ovl10_12_80047758(D_ovl10_12_800493F8[i][0], D_ovl10_12_800493F8[i][1],
                                       D_ovl10_12_800493F8[i][2], D_ovl10_12_800493F8[i][0] + 1,
                                       D_ovl10_12_800493F8[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_12_800494B8 && found == 0);
    }
    if (found) {
        D_ovl10_12_800493E4 = i;
        if (D_ovl10_12_800494C0[i] < D_ovl10_12_800493F8[i][1]) {
            D_ovl10_12_80049540 = 0.0f;
            D_ovl10_12_80049544 = -0.2f;
        } else {
            D_ovl10_12_80049540 = -0.0f;
            D_ovl10_12_80049544 = 0.2f;
        }
        if (arg0 == 2) {
            func_ovl10_12_8004339C();
        } else {
            D_ovl10_12_80049468 = D_ovl10_12_800494D8[i];
            D_ovl10_12_8004946C = D_ovl10_12_800494F0[i];
            func_ovl10_12_800432B0();
        }
    }
    return found;
}

void func_ovl10_12_8004339C(void) {
    s32 out[6];
    f32 a;
    f32 b;
    s32 i;

    i = D_ovl10_12_800493E4;
    a = func_ovl10_12_80047628(D_ovl10_12_800494C0[i]);
    b = func_ovl10_12_80047628(D_ovl10_12_800493F8[i][1]);
    func_ovl10_12_800477B0(0x40);
    func_ovl10_12_800477A0(1);
    D_ovl10_12_80049458 = func_ovl10_12_800477C8(func_ovl10_12_80047768());
    D_ovl10_12_80049550 = (a - b) * 0.5f;
    D_ovl10_12_80049550 += b;
    D_ovl10_12_80049458->unk70 = 0.0f;
    func_ovl10_12_800475E0(D_ovl10_12_80049458->unk40->unk10, D_ovl10_12_80049458->unk40->unk14,
                           D_ovl10_12_80049458->unk40->unk18, out, 2);
    func_ovl10_12_80047778(1);
    func_ovl10_12_80047E50(10.0f);
    func_ovl10_12_80047E58(5.0f);
    func_ovl10_12_80047E70(0.0f);
    func_ovl10_12_800431C8(i, D_ovl10_12_80049540, D_ovl10_12_80049544, a);
}

void func_ovl10_12_800432B0(void) {
    s32 out[6];
    s32 pad1;
    s32 pad2;
    s32 pad3;

    D_ovl10_12_80049550 = -1.0f;
    func_ovl10_12_800477B0(0x40);
    func_ovl10_12_800477A0(1);
    D_ovl10_12_80049458 = func_ovl10_12_800477C8(func_ovl10_12_80047768());
    D_ovl10_12_80049458->unk70 = 0.0f;
    func_ovl10_12_800475E0(D_ovl10_12_80049458->unk40->unk10, D_ovl10_12_80049458->unk40->unk14,
                           D_ovl10_12_80049458->unk40->unk18, out, 2);
    func_ovl10_12_800475C0(out[0], out[1], out[2], 0);
    func_ovl10_12_80047778(1);
    func_ovl10_12_800431C8(D_ovl10_12_800493E4, D_ovl10_12_80049540, D_ovl10_12_80049544, -1.0f);
    func_ovl10_12_800480F8(0x78);
    D_ovl10_12_80048C54 = D_ovl10_12_80049468;
    D_ovl10_12_80048C58 = D_ovl10_12_8004946C;
    func_ovl10_12_80047680(D_ovl10_12_80049468, D_ovl10_12_8004946C, 0);
}

void func_ovl10_12_800431C8(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_ovl10_12_800493E4 = arg0;
    D_ovl10_12_800493E8 = arg1;
    D_ovl10_12_800493EC = arg2;
    D_ovl10_12_800493F0 = arg3;
    func_ovl10_12_80043150(func_ovl10_12_80046908);
    D_ovl10_12_80049458 = func_ovl10_12_800477C8(func_ovl10_12_80047768());
    D_ovl10_12_80049458->unk70 = 0.0f;
    func_ovl10_12_80047640(1);
    if (arg1 == 0.0f && arg2 < 0.0f && arg3 == -1.0f) {
        func_ovl10_12_800477E0(1);
    }
    func_ovl10_12_80048660(0x98);
    func_ovl10_12_800476F0(0);
}

/* empty, as ovl_10_11's 80043044: two words before 80043150 */
void func_ovl10_12_80043148(void) {
}

void func_ovl10_12_800430B0(void) {
    func_ovl10_12_800483D8(0, 0, 0, 0.0f);
    func_ovl10_12_80043060();
    func_ovl10_12_80043018();
}

void func_ovl10_12_80043060(void) {
    if (D_ovl10_12_80048F1C != -1) {
        if (func_ovl10_12_80047850(0) != 0) {
            func_ovl10_12_80048690(D_ovl10_12_80048F1C);
        }
        D_ovl10_12_80048F1C = -1;
    }
}

void func_ovl10_12_80043018(void) {
    D_ovl10_12_80049364 = func_ovl10_12_800476D8();
    if (*D_ovl10_12_80049364 & 2) {
        func_ovl10_12_800487E0();
    }
}

void func_ovl10_12_80043010(void) {
}
