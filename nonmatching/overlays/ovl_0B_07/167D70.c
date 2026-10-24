/*
 * NON_MATCHING: ovl_0B_07's game object (the battle results: confetti, the
 * players' figures and their trophies, "Congratulations" and the winner's
 * name), complete: every function and its data (.data 0x1E0, .rodata 0xC0
 * as the original; jp's .data is 0x1A0). Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 1290, eu 1290, jp 1281
 *
 * IDO -O3: the functions are written last to first. The tail (80045438,
 * 800453F0, 800453BC, 80045494 and the twelve empty stubs) is ovl_17_10's;
 * the .bss nothing here uses (D_ovl0B_07_80046DF0, ..E1C, ..F38) comes out
 * common, so .bss is 0x120 where the original's is 0x150. The statics
 * 80043544 (the buttons of every controller; it uses its callers' $s0-$s2)
 * and 8004359C (arg0 in $s2, arg1 in $s1) are defined below the handler.
 * jp centres its two texts itself (func_ovl0B_07_80043594_jp, 24 pixels a
 * character, where us has the empty stub 80043594) and creates them with
 * ZeroJump 0x2707, its own strings (`#if VERSION_JP`).
 *
 * What still differs in us (words; eu the same, jp close):
 * - func_ovl0B_07_80043010 (2): case 2's 0.0f/350.0f arguments are loaded
 *   in the other order.
 * - func_ovl0B_07_800435FC (507): the original's frame is 0x98 (ours 0x58):
 *   it spills the winner's text height and func_ovl0B_07_80045FC8's result
 *   to the stack where ours takes $f22, and keeps an `i = 0` ($s8) before
 *   the confetti loop; everything after shifts registers.
 * - func_ovl0B_07_8004400C (781): the else branch's loop over the four
 *   players is unrolled here (the original keeps it a loop, walking a
 *   pointer and a counter), so it comes out 0x5C longer and everything
 *   after it differs. Fix that first.
 * - jp: 8004345C's 37 are the static 80043594_jp counted with it.
 *   80044D54's last nops follow once the object's size matches (IDO pads
 *   the dead epilogue after its endless loop to 32 bytes of the object).
 */
#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
} Gfx_ovl0B_07;

/* D_ovl0B_07_80046CF0: the four vertices of 800450D0's square */
typedef union {
    struct {
        /* 0x00 */ s16 ob[3];
        /* 0x06 */ u16 flag;
        /* 0x08 */ s16 tc[2];
        /* 0x0C */ u8 cn[4];
    } v;
    long long force_structure_alignment; /* as gbi.h's Vtx: 8-aligned */
} Vtx_ovl0B_07;

void func_ovl0B_07_80045950(s32, s32, s32); /* 0x0F00 */
s32 func_ovl0B_07_80045958(void); /* 0x0F01 */
UnkStructB *func_ovl0B_07_800459D8(void); /* 0x0F11 */
void func_ovl0B_07_80045A00(s32, s32, s32); /* 0x0F16 */
UnkStructA_40 *func_ovl0B_07_80045F38(s32, s32); /* 0x1500 */
void func_ovl0B_07_80045F40(UnkStructA_40 *); /* 0x1501 */
void func_ovl0B_07_80045F60(UnkStructA_40 *, s32); /* 0x1505 */
void func_ovl0B_07_80045F68(UnkStructA_40 *, s32, s32, s32); /* 0x1506 */
void func_ovl0B_07_80045F80(UnkStructA_40 *, s32, s32); /* 0x1509 */
UnkStructA_40 *func_ovl0B_07_80045FB8(void (*)(s32, Gfx_ovl0B_07 **), s32); /* 0x1510 */
s32 func_ovl0B_07_80045FC8(UnkStructA_40 *, s32); /* 0x1512 */
void func_ovl0B_07_80046078(s32); /* 0x1700 */
void func_ovl0B_07_80046088(s32); /* 0x1702 */
void func_ovl0B_07_80046098(f32, f32, f32); /* 0x1704 */
void func_ovl0B_07_800460B8(f32, f32, f32); /* 0x1708 */
void func_ovl0B_07_800460C0(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0B_07_80046100(s32); /* 0x1711 */
s32 func_ovl0B_07_800463A8(void (*)(), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0B_07_800463B8(void); /* 0x1902 */
void func_ovl0B_07_800463C8(s32); /* 0x1904 */
void *func_ovl0B_07_800463D0(void); /* 0x1905 */
s32 func_ovl0B_07_800463F0(void); /* 0x1909 */
UnkStructC *func_ovl0B_07_80046430(s32); /* 0x1A00 */
void func_ovl0B_07_80046440(UnkStructC *, s32); /* 0x1A02 */
s32 func_ovl0B_07_80046478(s32); /* 0x1B05 */
s32 func_ovl0B_07_80046488(s32); /* 0x1B07 */
f64 func_ovl0B_07_80046560(void); /* 0x1D02 */
void func_ovl0B_07_800466A0(void); /* 0x2003 */
void func_ovl0B_07_80046798(s32); /* 0x2502 */
void func_ovl0B_07_800467A8(s32, u16, u16); /* 0x2504 */
void func_ovl0B_07_800467B8(s32, f32, f32); /* 0x2506 */
s32 func_ovl0B_07_800467E0(u8 *); /* 0x250B */
s32 func_ovl0B_07_800467E8(u8 *, u16, u16, f32, f32, s32); /* 0x250C */
#if VERSION_JP
s32 func_ovl0B_07_80046790(u8 *, u16, u16, f32, f32, s32); /* 0x2707 */
#endif
void func_ovl0B_07_800467F8(s32, f32, f32, f32, s32); /* 0x2600 */
s32 func_ovl0B_07_80046930(s32); /* 0x2B00 */
void func_ovl0B_07_80046940(s32); /* 0x2B02 */
void func_ovl0B_07_80046948(void); /* 0x2B03 */
void func_ovl0B_07_80046950(s32, f32, f32, f32); /* 0x2B04 */
void func_ovl0B_07_80046998(void); /* 0x2B0D */

void func_ovl0B_07_8004345C(void);
void func_ovl0B_07_800435FC(void);
void func_ovl0B_07_8004400C(void);
void func_ovl0B_07_80044C9C(void);
void func_ovl0B_07_80044D54(void);
void func_ovl0B_07_80044EF4(void);
void func_ovl0B_07_800450D0(s32 arg0, Gfx_ovl0B_07 **arg1);
static s32 func_ovl0B_07_80043544(void);
#if VERSION_JP
static s32 func_ovl0B_07_80043594_jp(u8 *str, f32 scale);
/* jp centres its text itself (24 pixels a character) */
#define TEXT_X(str, scale) func_ovl0B_07_80043594_jp(str, scale)
#define TEXT_NEW func_ovl0B_07_80046790
#define TEXT_CONGRATS D_ovl0B_07_80046B3C_jp
#else
static void func_ovl0B_07_80043594(void);
#define TEXT_X(str, scale) (s32) ((320.0f - func_ovl0B_07_800467E0(str) * (scale)) / 2.0f)
#define TEXT_NEW func_ovl0B_07_800467E8
#define TEXT_CONGRATS D_ovl0B_07_80046C0C
#endif
static void func_ovl0B_07_8004359C(s32 arg0, s32 *arg1);

/* .bss */
u8 D_ovl0B_07_80046DF0[0x24]; /* not referenced here */
s32 D_ovl0B_07_80046E14;
s32 D_ovl0B_07_80046E18;
u8 D_ovl0B_07_80046E1C[4]; /* not referenced here */
Vec3f D_ovl0B_07_80046E20;
s32 D_ovl0B_07_80046E2C;
UnkStructA_40 *D_ovl0B_07_80046E30[4][5];
UnkStructA_40 *D_ovl0B_07_80046E80[6];
UnkStructA_40 *D_ovl0B_07_80046E98[32];
UnkStructB *D_ovl0B_07_80046F18;
s32 D_ovl0B_07_80046F1C;
s32 D_ovl0B_07_80046F20[4];
s32 D_ovl0B_07_80046F30;
s32 D_ovl0B_07_80046F34;
u8 D_ovl0B_07_80046F38[8]; /* not referenced here */

/* .data: the game's text encoding ('A' is 0x1A, 'a' 0x3A, '0' 0x10, ' ' 0x0F) */
#if VERSION_JP
u8 D_ovl0B_07_80046A90_jp[0xC] = ")%\x1A" "2\x1E+\x0F\x10";
u8 D_ovl0B_07_80046A9C_jp[0x4] = "('";
u8 D_ovl0B_07_80046AA0_jp[0x8] = "(\x1F\x1F";
u8 D_ovl0B_07_80046AA8_jp[0xC] = "()-\x22(',";
u8 D_ovl0B_07_80046AB4_jp[0xC] = "\x1C(&%\x1E/\x1E%";
u8 D_ovl0B_07_80046AC0_jp[0x8] = "\x1B\x1A--%\x1E";
u8 D_ovl0B_07_80046AC8_jp[0x4] = "\x13";
u8 D_ovl0B_07_80046ACC_jp[0x8] = "-\x22&\x1E";
u8 D_ovl0B_07_80046AD4_jp[0x8] = "\x12\x0F&\x22'";
u8 D_ovl0B_07_80046ADC_jp[0xC] = "'(\x0F%\x22&\x22-";
u8 D_ovl0B_07_80046AE8_jp[0x8] = "j\x9A_\x99l";
u8 D_ovl0B_07_80046AF0_jp[0x8] = "\x90\xF9ls";
u8 D_ovl0B_07_80046AF8_jp[0x10] = "\x1C!\x1A+\x1A\x1C-\x1E+\x0F-2)\x1E";
u8 D_ovl0B_07_80046B08_jp[0x8] = "\x1C('\x1F\x22 ";
u8 D_ovl0B_07_80046B10_jp[0x8] = "\x1F\x22%\x1E\x0F\x10";
u8 D_ovl0B_07_80046B18_jp[0x10] = ",-\x1A \x1E\x0F,\x1E%\x1E\x1C-";
u8 D_ovl0B_07_80046B28_jp[0xC] = ",-\x1A \x1E\x0F\x10";
u8 D_ovl0B_07_80046B34_jp[0x8] = "\xD0\xBD\xB1\xDF\xAF";
u8 D_ovl0B_07_80046B3C_jp[0x8] = "\xB4\xD1\xE9\xC3\xB2\xF6";
u8 D_ovl0B_07_80046B44_jp[0xC] = "\xBA\xB1\xBB\xAD\xC8\x9Bs\x88";
u8 D_ovl0B_07_80046B50_jp[0xC] = "\xB2\xB3\xCC\x0F\xBB\xBF\xCC";
u8 D_ovl0B_07_80046B5C_jp[0x8] = "\xA1\x86\x7FZ\x9A";
u8 D_ovl0B_07_80046B64_jp[0xC] = "\xD5\xB7\xEB\xD7\x0F\xC9\xCE\xD9";
u8 D_ovl0B_07_80046B70_jp[0xC] = "\xC2\xAF\xE0\xB7\x0F\xE2\xE0\xB7";
u8 D_ovl0B_07_80046B7C_jp[0xC] = "\xB7\xBA\xEB\xC8\xB5\xDF\xE9";
u8 D_ovl0B_07_80046B88_jp[0xC] = "\xCF\xE3\xC8\xBD\xBD\xD6\xDD";
u8 D_ovl0B_07_80046B94_jp[0x8] = "\xB5\xB1\xE5\xB7\xBD\xAF";
u8 D_ovl0B_07_80046B9C_jp[0xC] = "\x9D\x87\x91\xF9\x9A\x9Bs\x88";
u8 D_ovl0B_07_80046BA8_jp[0xC] = "q\x88q\x88\x8C\x86l";
u8 D_ovl0B_07_80046BB4_jp[0x8] = "p\xF9\x80";
#else
u8 D_ovl0B_07_80046B50[0xC] = ")%\x1A" "2\x1E+\x0F\x10";
u8 D_ovl0B_07_80046B5C[0x4] = "('";
u8 D_ovl0B_07_80046B60[0x8] = "(\x1F\x1F";
u8 D_ovl0B_07_80046B68[0xC] = "()-\x22(',";
u8 D_ovl0B_07_80046B74[0xC] = "\x1C(&%\x1E/\x1E%";
u8 D_ovl0B_07_80046B80[0x8] = "\x1B\x1A--%\x1E";
u8 D_ovl0B_07_80046B88[0x4] = "\x13";
u8 D_ovl0B_07_80046B8C[0x8] = "-\x22&\x1E";
u8 D_ovl0B_07_80046B94[0x8] = "\x12\x0F&\x22'";
u8 D_ovl0B_07_80046B9C[0xC] = "'(\x0F%\x22&\x22-";
u8 D_ovl0B_07_80046BA8[0x14] = ",.\x1D\x1D\x1E'\xFF\x0F\x0F\x0F\x1D\x1E\x1A-!";
u8 D_ovl0B_07_80046BBC[0x8] = " !(,-";
u8 D_ovl0B_07_80046BC4[0x10] = "\x1C!\x1A+\x1A\x1C-\x1E+\x0F-2)\x1E";
u8 D_ovl0B_07_80046BD4[0x8] = "\x1C('\x1F\x22 ";
u8 D_ovl0B_07_80046BDC[0x8] = "\x1F\x22%\x1E\x0F\x10";
u8 D_ovl0B_07_80046BE4[0x10] = ",-\x1A \x1E\x0F,\x1E%\x1E\x1C-";
u8 D_ovl0B_07_80046BF4[0xC] = ",-\x1A \x1E\x0F\x10";
u8 D_ovl0B_07_80046C00[0xC] = ".'%\x22&\x22-\x1E\x1D";
u8 D_ovl0B_07_80046C0C[0x14] = "\x1CHG@K:MNE:MBHGL\xF6";
u8 D_ovl0B_07_80046C20[0x10] = "+H<D\x0F :K=>G";
u8 D_ovl0B_07_80046C30[0x10] = ".I\x0F:G=\x0F\x1DHPG";
u8 D_ovl0B_07_80046C40[0xC] = ")RK:FB=";
u8 D_ovl0B_07_80046C4C[0x10] = " K>>=R\x0F-K:I";
u8 D_ovl0B_07_80046C5C[0xC] = "-HI\x0F+NE>L";
u8 D_ovl0B_07_80046C68[0x10] = "\x1F" "B>E=\x0FH\x3F\x0F K:LL";
u8 D_ovl0B_07_80046C78[0x10] = "\x22G\x0FMA>\x0F NMM>K";
u8 D_ovl0B_07_80046C88[0xC] = ",>:\x0F,B<D";
u8 D_ovl0B_07_80046C94[0x14] = "\x1B" "EBSS:K=\x0F\x1B:MME>";
u8 D_ovl0B_07_80046CA8[0x10] = "%HLM\x0F:M\x0F,>:";
u8 D_ovl0B_07_80046CB8[0x8] = "->:F";
#endif
s32 D_ovl0B_07_80046CC0[11] = {
    0x1A4, 0x1A5, 0x1A9, 0x1AA, 0x1A8, 0x1A6, 0x1A7, 0x1A7, 0x1A9, 0x1B1, 0x1A5,
};
Vtx_ovl0B_07 D_ovl0B_07_80046CF0[4] = {
    { { { 2, 8, 0 }, 0, { 0, 0 }, { 0x00, 0xFF, 0x00, 0xFF } } },
    { { { 8, 2, 0 }, 0, { 0, 0 }, { 0x00, 0x00, 0x00, 0xFF } } },
    { { { -2, -8, 0 }, 0, { 0, 0 }, { 0x00, 0x00, 0xFF, 0xFF } } },
    { { { -8, -2, 0 }, 0, { 0, 0 }, { 0xFF, 0x00, 0x00, 0xFF } } },
};

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0B_07_80045504(void) {
}

static void func_ovl0B_07_800454FC(void) {
}

static void func_ovl0B_07_800454F4(void) {
}

static void func_ovl0B_07_800454EC(void) {
}

static void func_ovl0B_07_800454E4(void) {
}

static void func_ovl0B_07_800454DC(void) {
}

static void func_ovl0B_07_800454D4(void) {
}

static void func_ovl0B_07_800454CC(void) {
}

static void func_ovl0B_07_800454C4(void) {
}

static void func_ovl0B_07_800454BC(void) {
}

static void func_ovl0B_07_800454B4(void) {
}

static void func_ovl0B_07_800454AC(void) {
}

void func_ovl0B_07_80045494(void) {
    D_ovl0B_07_80046E14 = -1;
    D_ovl0B_07_80046E18 = -1;
}

void func_ovl0B_07_80045438(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0B_07_80046098(D_ovl0B_07_80046E20.x, D_ovl0B_07_80046E20.y, D_ovl0B_07_80046E20.z);
    func_ovl0B_07_800460B8(arg0, arg1, arg2);
    func_ovl0B_07_800463C8(180);
}

void func_ovl0B_07_800453F0(f32 arg0) {
    f32 sp1C;

    func_ovl0B_07_800460C0(&sp1C, NULL, NULL);
    func_ovl0B_07_800460B8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0B_07_800453BC(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0B_07_80046950(arg0, p->unk10, p->unk14, p->unk18);
}

/* The confetti's display list: a square in a random colour. */
void func_ovl0B_07_800450D0(s32 arg0, Gfx_ovl0B_07 **arg1) {
    Gfx_ovl0B_07 *gfx = *arg1;

    { Gfx_ovl0B_07 *g = gfx++; g->w0 = 0xB6000000; g->w1 = 0x2000; }
    { Gfx_ovl0B_07 *g = gfx++; g->w0 = 0xFA000000; g->w1 = ((u8) (func_ovl0B_07_80046560() * 250.0) << 24) | ((u8) (func_ovl0B_07_80046560() * 250.0) << 16) | ((u8) (func_ovl0B_07_80046560() * 250.0) << 8) | 0xFF; }
    { Gfx_ovl0B_07 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFDF6FB; }
    { Gfx_ovl0B_07 *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x552078; }
    { Gfx_ovl0B_07 *g = gfx++; g->w0 = 0xBB000000; g->w1 = 0x80008000; }
    { Gfx_ovl0B_07 *g = gfx++; g->w0 = 0x0400103F; g->w1 = (u32) D_ovl0B_07_80046CF0; }
    { Gfx_ovl0B_07 *g = gfx++; g->w0 = 0xBF000000; g->w1 = 0x204; }
    { Gfx_ovl0B_07 *g = gfx++; g->w0 = 0xBF000000; g->w1 = 0x406; }
    { Gfx_ovl0B_07 *g = gfx++; g->w0 = 0xB7000000; g->w1 = 0x2000; }
    *arg1 = gfx;
}

/* A piece of confetti falling and spinning (arg: its object). */
void func_ovl0B_07_80044EF4(void) {
    UnkStructA_40 *obj;
    f32 speed;

    obj = func_ovl0B_07_800463D0();
    while (TRUE) {
        obj->unk10 = func_ovl0B_07_80046560() * 610.0 + 2.0;
        obj->unk14 = 0.0f;
        obj->unk18 = func_ovl0B_07_80046560() * 200.0 + 560.0;
        obj->unk1C = func_ovl0B_07_80046560() * 349.0 + 10.0;
        speed = func_ovl0B_07_80046560() * 1 + 0.1f;
        while (TRUE) {
            obj->unk14 -= speed;
            obj->unk1C = obj->unk1C + 10.0f >= 360.0f ? obj->unk1C + 10.0f - 360.0f
                       : obj->unk1C + 10.0f < 0.0f    ? obj->unk1C + 10.0f + 360.0f
                                                       : obj->unk1C + 10.0f;
            if (obj->unk14 < -500.0f) {
                break;
            }
            func_ovl0B_07_800463F0();
        }
    }
}

void func_ovl0B_07_80044D54(void) {
    s32 i;

    while (TRUE) {
        for (i = 0; i < 2; i++) {
            func_ovl0B_07_800467F8(0xE, func_ovl0B_07_80046560() * 280.0 - 216.0,
                                   func_ovl0B_07_80046560() * 299.0 - 140.0, -400.0f, 0);
            func_ovl0B_07_800463C8(20);
            func_ovl0B_07_800467F8(0xE, func_ovl0B_07_80046560() * 280.0 + 513.0,
                                   func_ovl0B_07_80046560() * 299.0 - 140.0, -400.0f, 0);
            func_ovl0B_07_800463C8(20);
        }
        func_ovl0B_07_800463C8(40);
    }
    func_ovl0B_07_800463B8();
}

void func_ovl0B_07_80044C9C(void) {
    s32 i;
    s32 j;

    func_ovl0B_07_800463C8(60);
    for (i = 0; i < 240; i++) {
        for (j = 0; j < D_ovl0B_07_80046F1C; j++) {
            D_ovl0B_07_80046E80[j + 2]->unk14 += 0.6666667f;
        }
        func_ovl0B_07_800463F0();
    }
    func_ovl0B_07_800463B8();
}

void func_ovl0B_07_8004400C(void) {
    s32 i;
    s32 j;
    s32 n;
    s32 m;
    s32 team;
    s32 cnt;
    s32 v;
    s32 *p;
    s32 *q;
    f32 off;
    f32 step;
    f32 y;
    UnkStructA_40 *obj;

    func_ovl0B_07_80046940(0x20);
    func_ovl0B_07_80046930(0x1F0);
    off = 0.0f;
    if (D_ovl0B_07_80046F18->unk0 == 0) {
        D_ovl0B_07_80046F1C = 0;
        j = 0;
        if (D_ovl0B_07_80046F18->unk4[0] != 0) {
            D_ovl0B_07_80046F1C++;
            D_ovl0B_07_80046F20[j] = 0;
            j++;
        }
        if (D_ovl0B_07_80046F18->unk4[1] != 0) {
            D_ovl0B_07_80046F20[j] = 1;
            D_ovl0B_07_80046F1C++;
            j++;
        }
        if (D_ovl0B_07_80046F18->unk4[2] != 0) {
            D_ovl0B_07_80046F20[j] = 2;
            D_ovl0B_07_80046F1C++;
            j++;
        }
        if (D_ovl0B_07_80046F18->unk4[3] != 0) {
            D_ovl0B_07_80046F20[j] = 3;
            D_ovl0B_07_80046F1C++;
            j++;
        }
    } else {
        D_ovl0B_07_80046F1C = 0;
        j = 0;
        /* walks the players' words: q[1] is unk4[i], q[0x24] unk90[i] */
        for (i = 0, q = (s32 *) D_ovl0B_07_80046F18; i < 4; i++, q++) {
            if (q[1] != 0 && q[0x24] == 0) {
                D_ovl0B_07_80046F1C++;
                D_ovl0B_07_80046F20[j] = i;
                j++;
            }
        }
        n = j;
        if (D_ovl0B_07_80046F18->unk4[0] != 0 && D_ovl0B_07_80046F18->unk90[0] == 1) {
            D_ovl0B_07_80046F1C++;
            D_ovl0B_07_80046F20[j] = 0;
            j++;
        }
        if (D_ovl0B_07_80046F18->unk4[1] != 0 && D_ovl0B_07_80046F18->unk90[1] == 1) {
            D_ovl0B_07_80046F20[j] = 1;
            D_ovl0B_07_80046F1C++;
            j++;
        }
        if (D_ovl0B_07_80046F18->unk4[2] != 0 && D_ovl0B_07_80046F18->unk90[2] == 1) {
            D_ovl0B_07_80046F20[j] = 2;
            D_ovl0B_07_80046F1C++;
            j++;
        }
        if (D_ovl0B_07_80046F18->unk4[3] != 0 && D_ovl0B_07_80046F18->unk90[3] == 1) {
            D_ovl0B_07_80046F20[j] = 3;
            D_ovl0B_07_80046F1C++;
            j++;
        }
    }
    if (D_ovl0B_07_80046F18->unk0 == 0) {
        step = 720.0f / D_ovl0B_07_80046F1C;
    } else {
        step = 640.0f / D_ovl0B_07_80046F1C;
    }
    for (i = 0; i < D_ovl0B_07_80046F1C; i++) {
        if (D_ovl0B_07_80046F18->unk0 == 1 && i == n) {
            off += 180.0f * D_ovl0B_07_80046F1C - 160.0f * D_ovl0B_07_80046F1C;
        }
        D_ovl0B_07_80046E80[i] = func_ovl0B_07_80045F38(0x49, 0);
        m = func_ovl0B_07_80045FC8(D_ovl0B_07_80046E80[i], 0xF);
        D_ovl0B_07_80046E80[i]->unk10 = 0.0f;
        D_ovl0B_07_80046E80[i]->unk14 = 90.0f - 720.0f / D_ovl0B_07_80046F1C / 2.0f - off;
        D_ovl0B_07_80046E80[i]->unk18 = 0.0f;
        off += step;
        func_ovl0B_07_80045F60(D_ovl0B_07_80046E80[i], 12);
        for (j = 0; j < 12; j++) {
            func_ovl0B_07_80045F68(D_ovl0B_07_80046E80[i], D_ovl0B_07_80046F20[i] + 0x4A, j, j);
        }
        if (D_ovl0B_07_80046F18->unk4[D_ovl0B_07_80046F20[i]] == 1 &&
            D_ovl0B_07_80046F18->unk40[D_ovl0B_07_80046F20[i]] == 1) {
            func_ovl0B_07_8004359C(m, D_ovl0B_07_80046F18->unk50[D_ovl0B_07_80046F20[i]]);
        }
    }
    if (D_ovl0B_07_80046F18->unk0 == 0) {
        y = 0.0f;
        for (i = 0; i < D_ovl0B_07_80046F1C; i++) {
            for (j = 0; j < D_ovl0B_07_80046F18->unkA4[D_ovl0B_07_80046F20[i]]; j++) {
                D_ovl0B_07_80046E30[i][j] = obj = func_ovl0B_07_80045F38(0x40, 0);
                obj->unk10 = j * 120.0f + 120.0f;
                obj->unk18 = 0.0f;
                obj->unk14 = 170.0f - 720.0f / D_ovl0B_07_80046F1C / 2.0f - y;
            }
            y += step;
        }
    } else {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < D_ovl0B_07_80046F18->unkA4[i]; j++) {
                D_ovl0B_07_80046E30[i][j] = obj = func_ovl0B_07_80045F38(0x40, 0);
                obj->unk10 = j * 120.0f + 120.0f;
                if (i == 0) {
                    obj->unk14 = 170.0f - 720.0f / D_ovl0B_07_80046F1C / 2.0f - step * (n - 1) / 2.0f;
                } else {
                    obj->unk14 = 170.0f - 720.0f / D_ovl0B_07_80046F1C / 2.0f -
                                 step * (D_ovl0B_07_80046F1C - n - 1) / 2.0f - step * n -
                                 (180.0f * D_ovl0B_07_80046F1C - 160.0f * D_ovl0B_07_80046F1C);
                }
                obj->unk18 = 0.0f;
            }
        }
    }
    if (D_ovl0B_07_80046F18->unk0 == 0) {
        team = D_ovl0B_07_80046E2C - 0x11;
        for (j = 0; j < D_ovl0B_07_80046F1C; j++) {
            if (team == D_ovl0B_07_80046F20[j]) {
                break;
            }
        }
        obj = func_ovl0B_07_80045F38(0x40, 0);
        D_ovl0B_07_80046E30[j][D_ovl0B_07_80046F18->unkA4[team]] = obj;
    } else {
        team = D_ovl0B_07_80046E2C - 0x16;
        obj = func_ovl0B_07_80045F38(0x40, 0);
        D_ovl0B_07_80046E30[team][D_ovl0B_07_80046F18->unkA4[team]] = obj;
    }
    obj->unk10 = 310.0f;
    obj->unk14 = -200.0f;
    obj->unk18 = 1200.0f;
    cnt = D_ovl0B_07_80046F18->unkA4[team];
    if (D_ovl0B_07_80046F18->unk0 == 0) {
        y = 170.0f - 720.0f / D_ovl0B_07_80046F1C / 2.0f - step * j;
    } else if (team == 0) {
        y = 170.0f - 720.0f / D_ovl0B_07_80046F1C / 2.0f - step * (n - 1) / 2.0f;
    } else {
        y = 170.0f - 720.0f / D_ovl0B_07_80046F1C / 2.0f - step * (D_ovl0B_07_80046F1C - n - 1) / 2.0f -
            step * n - (180.0f * D_ovl0B_07_80046F1C - 160.0f * D_ovl0B_07_80046F1C);
    }
    D_ovl0B_07_80046F18->unkA4[team] = cnt + 1;
    for (i = 0; i < 120; i++) {
        if (func_ovl0B_07_80043544() & 0xC000) {
            break;
        }
        func_ovl0B_07_800463F0();
    }
    for (i = 0; i < 60; i++) {
        obj->unk10 += (cnt * 120.0f + 120.0f - 310.0f) / 60.0f;
        obj->unk14 += (y - -200.0f) / 60.0f;
        obj->unk18 += -20.0f;
        func_ovl0B_07_800463F0();
    }
    func_ovl0B_07_80046930(0x1E8);
    if (D_ovl0B_07_80046F18->unk0 == 0) {
        D_ovl0B_07_80046E80[j]->unkC |= 0x20;
        func_ovl0B_07_80045F80(D_ovl0B_07_80046E80[j], 0x16, 0);
        if (D_ovl0B_07_80046F18->unk4[D_ovl0B_07_80046F20[j]] == 1 &&
            D_ovl0B_07_80046F18->unk40[D_ovl0B_07_80046F20[j]] == 1) {
            p = D_ovl0B_07_80046F18->unk50[D_ovl0B_07_80046F20[j]];
            v = p[0];
            for (j = 1; j < 4; j++) {
                if (p[j] != v) {
                    break;
                }
            }
            if (j == 4) {
                if (v != 0) {
                    func_ovl0B_07_80046930(D_ovl0B_07_80046CC0[v]);
                }
            } else {
                func_ovl0B_07_80046930(D_ovl0B_07_80046CC0[0]);
            }
        }
    } else if (team == 0) {
        for (j = 0; j < n; j++) {
            D_ovl0B_07_80046E80[j]->unkC |= 0x20;
            func_ovl0B_07_80045F80(D_ovl0B_07_80046E80[j], 0x16, 0);
        }
    } else {
        for (j = n; j < D_ovl0B_07_80046F1C; j++) {
            D_ovl0B_07_80046E80[j]->unkC |= 0x20;
            func_ovl0B_07_80045F80(D_ovl0B_07_80046E80[j], 0x16, 0);
        }
    }
    while (!(func_ovl0B_07_80043544() & 0xD000)) {
        func_ovl0B_07_800463F0();
    }
    func_ovl0B_07_80046948();
    func_ovl0B_07_80046998();
    if (D_ovl0B_07_80046F18->unk24 == D_ovl0B_07_80046F18->unkA4[team]) {
        func_ovl0B_07_80045950(0x22, 0x15, 0);
    } else {
        func_ovl0B_07_80045950(D_ovl0B_07_80046F18->unkA0 + 0x90, 0x10, 0);
    }
    func_ovl0B_07_800463B8();
}

void func_ovl0B_07_800435FC(void) {
    s32 i;
    s32 j;
    s32 n;
    s32 x;
    f32 scale;

    func_ovl0B_07_80046940(0x1F);
    for (i = 0; i < 32; i++) {
        D_ovl0B_07_80046E98[i] = func_ovl0B_07_80045FB8(func_ovl0B_07_800450D0, 0);
        D_ovl0B_07_80046E98[i]->unk28 = 0.7f;
        D_ovl0B_07_80046E98[i]->unk28 = D_ovl0B_07_80046E98[i]->unk28 = D_ovl0B_07_80046E98[i]->unk28;
        func_ovl0B_07_800463A8(func_ovl0B_07_80044EF4, D_ovl0B_07_80046E98[i], 0, 0, 0x130);
    }
    func_ovl0B_07_800463A8(func_ovl0B_07_80044D54, NULL, 0, 0, 0x130);
    D_ovl0B_07_80046E80[0] = func_ovl0B_07_80045F38(0x3B, 0);
    D_ovl0B_07_80046E80[0]->unk10 = 310.0f;
    D_ovl0B_07_80046E80[0]->unk14 = -540.0f;
    D_ovl0B_07_80046E80[0]->unk18 = 160.0f;
    D_ovl0B_07_80046E80[1] = func_ovl0B_07_80045F38(0x3C, 0);
    D_ovl0B_07_80046E80[1]->unk10 = 310.0f;
    D_ovl0B_07_80046E80[1]->unk14 = -260.0f;
    D_ovl0B_07_80046E80[1]->unk18 = -36.0f;
    D_ovl0B_07_80046E80[1]->unkC |= 0x8080;
    func_ovl0B_07_80045F60(D_ovl0B_07_80046E80[1], 2);
    for (j = 0; j < 2; j++) {
        func_ovl0B_07_80045F68(D_ovl0B_07_80046E80[1], 0x3D, j, j);
    }
    if (D_ovl0B_07_80046F18->unk0 == 0) {
        D_ovl0B_07_80046F1C = 1;
        for (i = 0; i < 4; i++) {
            if (D_ovl0B_07_80046F18->unk24 == D_ovl0B_07_80046F18->unkA4[i]) {
                break;
            }
        }
        D_ovl0B_07_80046F20[0] = i;
    } else {
        D_ovl0B_07_80046F1C = 0;
        for (i = 0; i < 2; i++) {
            if (D_ovl0B_07_80046F18->unk24 == D_ovl0B_07_80046F18->unkA4[i]) {
                break;
            }
        }
        n = 0;
        if (D_ovl0B_07_80046F18->unk4[0] != 0 && i == D_ovl0B_07_80046F18->unk90[0]) {
            D_ovl0B_07_80046F20[n] = 0;
            n++;
            D_ovl0B_07_80046F1C++;
        }
        if (D_ovl0B_07_80046F18->unk4[1] != 0 && i == D_ovl0B_07_80046F18->unk90[1]) {
            D_ovl0B_07_80046F20[n] = 1;
            n++;
            D_ovl0B_07_80046F1C++;
        }
        if (D_ovl0B_07_80046F18->unk4[2] != 0 && i == D_ovl0B_07_80046F18->unk90[2]) {
            D_ovl0B_07_80046F20[n] = 2;
            n++;
            D_ovl0B_07_80046F1C++;
        }
        if (D_ovl0B_07_80046F18->unk4[3] != 0 && i == D_ovl0B_07_80046F18->unk90[3]) {
            D_ovl0B_07_80046F20[n] = 3;
            n++;
            D_ovl0B_07_80046F1C++;
        }
    }
    x = 390 - D_ovl0B_07_80046F1C * 80;
    for (i = 0; i < D_ovl0B_07_80046F1C; i++) {
        D_ovl0B_07_80046E80[i + 2] = func_ovl0B_07_80045F38(0x49, 0);
        n = func_ovl0B_07_80045FC8(D_ovl0B_07_80046E80[i + 2], 0xF);
        D_ovl0B_07_80046E80[i + 2]->unk10 = x;
        D_ovl0B_07_80046E80[i + 2]->unk14 = -440.0f;
        D_ovl0B_07_80046E80[i + 2]->unk18 = 160.0f;
        x += 160;
        D_ovl0B_07_80046E80[i + 2]->unk30 = 1.5f;
        D_ovl0B_07_80046E80[i + 2]->unk28 = D_ovl0B_07_80046E80[i + 2]->unk2C = D_ovl0B_07_80046E80[i + 2]->unk30;
        func_ovl0B_07_80045F60(D_ovl0B_07_80046E80[i + 2], 12);
        for (j = 0; j < 12; j++) {
            func_ovl0B_07_80045F68(D_ovl0B_07_80046E80[i + 2], D_ovl0B_07_80046F20[i] + 0x4A, j, j);
        }
        if (D_ovl0B_07_80046F18->unk4[D_ovl0B_07_80046F20[i]] == 1 &&
            D_ovl0B_07_80046F18->unk40[D_ovl0B_07_80046F20[i]] == 1) {
            func_ovl0B_07_8004359C(n, D_ovl0B_07_80046F18->unk50[D_ovl0B_07_80046F20[i]]);
        }
    }
    func_ovl0B_07_800463A8(func_ovl0B_07_80044C9C, NULL, 0, 0, 0x130);
    for (i = 0; i < 255; i++) {
        if (func_ovl0B_07_80043544() & 0xD000) {
            goto end;
        }
        func_ovl0B_07_800463F0();
    }
    for (i = 0; i < D_ovl0B_07_80046F1C; i++) {
        func_ovl0B_07_80045F80(D_ovl0B_07_80046E80[i + 2], 0x17, 0);
    }
    for (i = 0; i < 221; i++) {
        if (func_ovl0B_07_80043544() & 0xD000) {
            goto end;
        }
        func_ovl0B_07_800463F0();
    }
    for (i = 0; i < D_ovl0B_07_80046F1C; i++) {
        func_ovl0B_07_80045F80(D_ovl0B_07_80046E80[i + 2], 0x1A, 0);
    }
    func_ovl0B_07_800466A0();
    if (D_ovl0B_07_80046F18->unk0 == 0 && D_ovl0B_07_80046F18->unk40[D_ovl0B_07_80046F20[0]] == 1) {
        D_ovl0B_07_80046F30 = TEXT_NEW(TEXT_CONGRATS, TEXT_X(TEXT_CONGRATS, 1.0f), 30, 1.0f, 1.0f, 3);
        D_ovl0B_07_80046F34 = TEXT_NEW(D_ovl0B_07_80046F18->unkC4[D_ovl0B_07_80046F20[0]],
                                       TEXT_X(D_ovl0B_07_80046F18->unkC4[D_ovl0B_07_80046F20[0]], 1.0f), 190,
                                       1.0f, 1.0f, 5);
        scale = 0.0f;
        for (i = 0; i < 40; i++) {
            scale += 0.025f;
            func_ovl0B_07_800467B8(D_ovl0B_07_80046F30, scale, scale);
            func_ovl0B_07_800467B8(D_ovl0B_07_80046F34, scale, scale);
            func_ovl0B_07_800467A8(D_ovl0B_07_80046F30, TEXT_X(TEXT_CONGRATS, scale), 42.0f - 24.0f * scale * 0.5f);
            func_ovl0B_07_800467A8(D_ovl0B_07_80046F34,
                                   TEXT_X(D_ovl0B_07_80046F18->unkC4[D_ovl0B_07_80046F20[0]], scale),
                                   202.0f - 24.0f * scale * 0.5f);
            if (func_ovl0B_07_80043544() & 0xD000) {
                goto end;
            }
            func_ovl0B_07_800463F0();
        }
        func_ovl0B_07_800467B8(D_ovl0B_07_80046F30, 1.0f, 1.0f);
        func_ovl0B_07_800467B8(D_ovl0B_07_80046F34, 1.0f, 1.0f);
    }
    while (!(func_ovl0B_07_80043544() & 0xD000)) {
        func_ovl0B_07_800463F0();
    }
end:
    func_ovl0B_07_800466A0();
    func_ovl0B_07_80046948();
    func_ovl0B_07_80045950(0x23, 0x10, 0);
    func_ovl0B_07_800463B8();
}

/* The camera's climb. */
void func_ovl0B_07_8004345C(void) {
    s32 i;

    for (i = 0; i < 300; i++) {
        func_ovl0B_07_800460B8(0.0f, i * 0.02f + 350.0f, i * 1.65f + 1494.0f);
        func_ovl0B_07_800463F0();
    }
    func_ovl0B_07_800463B8();
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0B_07_80043010(s32 arg0) {
    s32 i;
    s32 j;
    UnkStructC *c;

    switch (arg0) {
        case 2:
            D_ovl0B_07_80046E2C = func_ovl0B_07_80045958();
            D_ovl0B_07_80046F18 = func_ovl0B_07_800459D8();
            func_ovl0B_07_80046100(0x7F);
            func_ovl0B_07_80046078(1);
            func_ovl0B_07_80046098(310.0f, -200.0f, -500.0f);
            func_ovl0B_07_80046088(1);
            if (D_ovl0B_07_80046E2C == 0x15 || D_ovl0B_07_80046E2C == 0x18) {
                func_ovl0B_07_800460B8(0.0f, 350.0f, 1494.0f);
            } else {
                func_ovl0B_07_800460B8(0.0f, 0.0f, 2000.0f);
                c = func_ovl0B_07_80046430(0x296);
                func_ovl0B_07_80046440(c, 0x20000000);
                c->unk40 = 0.5f;
                c->unk44 = c->unk40 * 0.75f;
                c->unk3C = c->unk4C * 0.25f;
            }
            D_ovl0B_07_80046F30 = D_ovl0B_07_80046F34 = -1;
            break;
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
            func_ovl0B_07_800463A8(func_ovl0B_07_8004400C, NULL, 0, 0, 0x130);
            break;
        case 0x15:
        case 0x18:
            func_ovl0B_07_800463A8(func_ovl0B_07_800435FC, NULL, 0, 0, 0x130);
            func_ovl0B_07_800463A8(func_ovl0B_07_8004345C, NULL, 0, 0, 0x130);
            break;
        case 0x16:
        case 0x17:
            func_ovl0B_07_800463A8(func_ovl0B_07_8004400C, NULL, 0, 0, 0x130);
            break;
        case 1:
            if (D_ovl0B_07_80046F30 != -1) {
                func_ovl0B_07_80046798(D_ovl0B_07_80046F30);
            }
            if (D_ovl0B_07_80046F34 != -1) {
                func_ovl0B_07_80046798(D_ovl0B_07_80046F34);
            }
            if ((D_ovl0B_07_80046E2C >= 0x11 && D_ovl0B_07_80046E2C < 0x15) ||
                (D_ovl0B_07_80046E2C >= 0x16 && D_ovl0B_07_80046E2C < 0x18)) {
                for (i = 0; i < D_ovl0B_07_80046F1C; i++) {
                    func_ovl0B_07_80045F40(D_ovl0B_07_80046E80[i]);
                    if (D_ovl0B_07_80046F18->unk0 == 0) {
                        for (j = 0; j < D_ovl0B_07_80046F18->unkA4[D_ovl0B_07_80046F20[i]]; j++) {
                            func_ovl0B_07_80045F40(D_ovl0B_07_80046E30[i][j]);
                        }
                    }
                }
                if (D_ovl0B_07_80046F18->unk0 == 1) {
                    for (i = 0; i < 2; i++) {
                        for (j = 0; j < D_ovl0B_07_80046F18->unkA4[i]; j++) {
                            func_ovl0B_07_80045F40(D_ovl0B_07_80046E30[i][j]);
                        }
                    }
                }
            } else if (D_ovl0B_07_80046E2C == 0x15 || D_ovl0B_07_80046E2C == 0x18) {
                for (i = 0; i < D_ovl0B_07_80046F1C + 2; i++) {
                    func_ovl0B_07_80045F40(D_ovl0B_07_80046E80[i]);
                }
                for (i = 0; i < 32; i++) {
                    func_ovl0B_07_80045F40(D_ovl0B_07_80046E98[i]);
                }
            }
            break;
    }
}

/* The buttons pressed on any controller (skipping those with bit 3). */
static s32 func_ovl0B_07_80043544(void) {
    s32 i;
    s32 buttons;

    buttons = 0;
    for (i = 0; i < 4; i++) {
        if (!(func_ovl0B_07_80046478(i) & 8)) {
            buttons |= func_ovl0B_07_80046488(i);
        }
    }
    return buttons;
}

#if VERSION_JP
static s32 func_ovl0B_07_80043594_jp(u8 *str, f32 scale) {
    s32 len;

    len = 0;
    while (str[len] != 0) {
        len++;
    }
    return (320.0f - len * 24 * scale) / 2.0f;
}
#else
static void func_ovl0B_07_80043594(void) {
}
#endif

static void func_ovl0B_07_8004359C(s32 arg0, s32 *arg1) {
    s32 i;

#if !VERSION_JP
    func_ovl0B_07_80043594();
#endif
    for (i = 0; i < 4; i++) {
        if (arg1 == NULL) {
            func_ovl0B_07_80045A00(arg0, i, 0);
        } else {
            func_ovl0B_07_80045A00(arg0, i, arg1[i]);
        }
    }
}
