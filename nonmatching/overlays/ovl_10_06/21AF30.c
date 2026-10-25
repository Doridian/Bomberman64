/*
 * NON_MATCHING: ovl_10_06's game object, complete: every function, its
 * .data, .rodata and .bss (sizes 0x170/0x160/0x1080 as the original; .data
 * byte for byte, .rodata's strings and first floats in place, the later
 * floats in another order). .text is 0x120 bytes long. Not built into the
 * ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 2563, jp 2563
 *
 * What still differs in us (words, as tools/nonmatching.py counts them; a
 * static's words go to the named function before it):
 * - first pass, m2c's C cleaned up only where it didn't compile, or
 *   rewritten where m2c's was wrong (80044EFC, 80044F8C, 80045888,
 *   800460C8, 800466C4, 8004683C, 80046B58, 80046D74, 80047810,
 *   800479B8, 80048110): 8004322C (5), 80043278 (18), 800434E0 (40),
 *   800435FC (40), 8004368C (8), 80043820 (25), 80043A68 (16), 80043B94
 *   (48), 80043CB0 (56), 80043F50 (19), 80043FF8 (57), 8004411C (55),
 *   800442D4 (2), 800443DC (7), 800445DC (58), 80044804 (6), 80044A54 (6),
 *   80044AE4 (3), 80044BCC (15), 80044D00 (119), 80044F8C (4), 800453A0
 *   (20), 80045458 (20), 80045518 (44), 800455EC (3), 8004584C (9),
 *   80045888 (214), 80045CE4 (152), 80045F9C (34), 800460C8 (2), 800463C0
 *   (24), 80046478 (91), 800465F4 (39), 800466C4 (18), 8004683C (30),
 *   80046A04 (60), 80046BF0 (19), 80046C64 (21), 80046D74 (223), 80047110
 *   (22), 80047308 (53), 800473FC (14), 80047450 (89), 80047634 (108),
 *   80047810 (15), 80047A50 (44), 80047B0C (3), 80047BE0 (18), 80047C98
 *   (16), 80047D14 (165: something is inlined into it, 0x2CC bytes against
 *   0xFC), 80047E10 (184), 80048110 (57), 80048498 (38), 80048944 (10),
 *   800489FC (84), 80049020 (13).
 * - 800434E0 and 800435FC are ovl_10_13's code and match; their words
 *   are the static 8004355C (ovl_10_10's 80043A0C, arguments in s2-s4),
 *   which comes out after 800435FC, not after 800434E0.
 * - Not drafted: the two empty stubs after 8004322C (0x80043268 and
 *   0x80043270, statics inlined somewhere).
 *
 * ovl_10_06's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). The task functions
 * (800430A8, 80043A30, 80045838-80045C64, 80048EFC-80049020), 80043018,
 * 80043060, 80043338, 800433C8, 80044CAC and 80045598 are ovl_10_10's,
 * ovl_10_12's and ovl_10_13's, 80049118-800491F0 ovl_17_09's (renamed by
 * their asm); the rest is m2c's output (scratch/10_06/ in the checkout has
 * the scripts). 800430A8 is defined above 80048FE8, as in ovl_10_10, so
 * the strings come out in the original's order. The tables 8004A998-
 * 8004A9C8 and 8004A9D4 are 800460C8's and 80045888's local initializers.
 * 80049208's fake keeps the .bss's unread words in place.
 */
#include "common.h"

/* What func_ovl10_06_8004A0E0 takes. */
typedef struct {
    /* 0x00 */ UnkStructA_40 *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_ovl10_06_8004A0E0;

/* What func_ovl10_06_8004A0B0 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ s32 unk14;
} UnkStruct_ovl10_06_8004A0B0;

/* What func_ovl10_06_8004A460 returns: a list. */
typedef struct UnkStruct_ovl10_06_8004A460 {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ struct UnkStruct_ovl10_06_8004A460 *unk4;
    /* 0x08 */ u8 unk8[0x14];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} UnkStruct_ovl10_06_8004A460;

void func_ovl10_06_80049258(const char *, ...);
void func_ovl10_06_80049598(s32);
void func_ovl10_06_800495B0(s32);
void func_ovl10_06_800495D0(s32, s32, s32, s32);
void func_ovl10_06_800495F8(f32, f32, f32, f32 *, s32);
s32 func_ovl10_06_80049600(s32);
s32 func_ovl10_06_80049608(s32, s32, s32);
s32 func_ovl10_06_80049628(f32, f32, f32);
void func_ovl10_06_80049640(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_06_80049648(s32, s32, s32, s32, s32, s32);
void func_ovl10_06_80049650(s32);
void func_ovl10_06_80049660(s32);
s32 func_ovl10_06_80049668(s32);
void func_ovl10_06_80049680(void (*)(UnkStructA *));
s32 func_ovl10_06_80049688();
void func_ovl10_06_80049690(s32, s32, s32);
void func_ovl10_06_800496B8(void);
void func_ovl10_06_800496D0(void (*)(UnkStructA *));
s32 func_ovl10_06_800496D8();
s32 *func_ovl10_06_800496E8(void);
void func_ovl10_06_80049700(s32);
void func_ovl10_06_80049708(s32);
void func_ovl10_06_80049748(void);
void func_ovl10_06_80049750(s32, s32, s32);
s32 func_ovl10_06_80049760(s32, s32, s32, s32);
s32 func_ovl10_06_80049768(s32, s32, s32, s32, s32);
s32 func_ovl10_06_80049778(void);
void func_ovl10_06_80049780(s32, void *);
void func_ovl10_06_80049788(s32);
void func_ovl10_06_80049790(s32);
void func_ovl10_06_80049798(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_06_800497A0(const char *);
void func_ovl10_06_800497A8(void);
void func_ovl10_06_800497B0(s32);
void func_ovl10_06_800497C0(s32);
UnkStructA *func_ovl10_06_800497D8(s32);
void func_ovl10_06_800497E0(s32);
s32 func_ovl10_06_80049800(void);
void func_ovl10_06_80049838(s32);
void func_ovl10_06_80049848(void);
void func_ovl10_06_80049CB8(UnkStructA_40 *, s32);
void func_ovl10_06_80049CC0(UnkStructA_40 *, s32, s32);
void func_ovl10_06_80049D00(s32, s32);
void func_ovl10_06_80049DD8(f32, f32, f32);
void func_ovl10_06_80049DF8(f32, f32, f32);
void func_ovl10_06_80049E00(f32 *, f32 *, f32 *);
s32 func_ovl10_06_80049E28(void);
void func_ovl10_06_80049E30(void);
void func_ovl10_06_80049E38(s32);
void func_ovl10_06_80049E40(s32);
void func_ovl10_06_80049E50(s32);
void func_ovl10_06_80049EB0(s32);
void func_ovl10_06_80049EC0(f32, f32, f32);
void func_ovl10_06_80049EC8(void *);
s32 func_ovl10_06_80049EE8();
void func_ovl10_06_80049EF0(f32 *);
void func_ovl10_06_80049EF8(void);
void func_ovl10_06_80049F00(void);
void func_ovl10_06_80049F28(f32 *, f32 *, f32 *);
void func_ovl10_06_80049F30(f32 *, f32 *);
f32 func_ovl10_06_80049F40(Vec3f *, Vec3f *);
s32 func_ovl10_06_80049F48(UnkStructA *, s32);
void func_ovl10_06_80049F70(UnkStructA *);
void func_ovl10_06_80049F78(UnkStructA *, UnkStructA *);
void func_ovl10_06_80049F98(UnkStructA *, s32);
void func_ovl10_06_80049FA0(UnkStructA *, s32);
void func_ovl10_06_80049FB0(UnkStructA *);
UnkStructA *func_ovl10_06_80049FC0(s32, s32, s32, s32);
UnkStructA *func_ovl10_06_80049FD0(UnkStructA *);
void *func_ovl10_06_80049FF0(s32, s32, UnkStructA *);
void func_ovl10_06_8004A018(UnkStructA *);
void func_ovl10_06_8004A068(UnkStructA *, Vec3f *);
UnkStruct_ovl10_06_8004A0B0 *func_ovl10_06_8004A0B0(UnkStructA *, s32);
s32 func_ovl10_06_8004A0C0();
void func_ovl10_06_8004A0E0(void *);
s32 func_ovl10_06_8004A0E8(void (*)(void), void *, s32, s32, s32);
void func_ovl10_06_8004A0F8(void);
void func_ovl10_06_8004A108(s32);
void func_ovl10_06_8004A130(void);
void func_ovl10_06_8004A158(s32, s32, s32);
void func_ovl10_06_8004A160(s32, s32);
UnkStructC *func_ovl10_06_8004A170(s32);
void func_ovl10_06_8004A180(UnkStructC *, s32);
f32 func_ovl10_06_8004A290(f32);
f32 func_ovl10_06_8004A298(f32);
f64 func_ovl10_06_8004A2A0(void);
s32 func_ovl10_06_8004A2A8(s32);
s32 func_ovl10_06_8004A350(s32);
void func_ovl10_06_8004A360(s32);
s32 func_ovl10_06_8004A370(s32);
s32 *func_ovl10_06_8004A380(s32);
void func_ovl10_06_8004A3E8(s32, s32, s32, f32);
void func_ovl10_06_8004A450(u32 (*)[3]);
UnkStruct_ovl10_06_8004A460 *func_ovl10_06_8004A460(void);
void func_ovl10_06_8004A538(s32, f32, f32, f32, s32);
s32 func_ovl10_06_8004A540(s32, f32 *, s32);
void func_ovl10_06_8004A548(s32);
void func_ovl10_06_8004A578(void);
void func_ovl10_06_8004A5F8(s32, s32, s32);
void func_ovl10_06_8004A608(s32, f32, f32, f32);
void func_ovl10_06_8004A618(s32);
s32 func_ovl10_06_8004A640(void);
void func_ovl10_06_8004A668(f32 *);
void func_ovl10_06_8004A670(s32);
void func_ovl10_06_8004A690(s32, f32, f32, f32);
void func_ovl10_06_8004A698(s32, f32 *);
void func_ovl10_06_8004A7E8(void);
void func_ovl10_06_8004A7F0(void);

void func_ovl10_06_80043010(void);
void func_ovl10_06_80043018(void);
void func_ovl10_06_80043060(void);
s32 func_ovl10_06_800430A8(void (*arg0)());
void func_ovl10_06_80043120(void);
void func_ovl10_06_800431C0(void);
void func_ovl10_06_8004322C(s32 arg0);
void func_ovl10_06_80043278(void);
void func_ovl10_06_80043338(void);
void func_ovl10_06_800433C8(void);
void func_ovl10_06_800433F0(void);
void func_ovl10_06_80043424(void);
void func_ovl10_06_8004347C(void);
void func_ovl10_06_800434D8(void);
void func_ovl10_06_800434E0(void);
void func_ovl10_06_800435FC(s32 arg0);
void func_ovl10_06_8004368C(void);
void func_ovl10_06_80043820(s32 arg0);
void func_ovl10_06_8004396C(UnkStructA *arg0);
void func_ovl10_06_800439C0(void);
void func_ovl10_06_800439DC(void);
void func_ovl10_06_80043A30(void (*arg0)());
void func_ovl10_06_80043A4C(s32 arg0);
void func_ovl10_06_80043A68(void);
void func_ovl10_06_80043AEC(void);
void func_ovl10_06_80043B38(s32 arg0);
void func_ovl10_06_80043B94(void);
void func_ovl10_06_80043C64(void);
void func_ovl10_06_80043CB0(void);
void func_ovl10_06_80043EA8(void);
void func_ovl10_06_80043F50(void);
void func_ovl10_06_80043FAC(void);
void func_ovl10_06_80043FF8(void);
void func_ovl10_06_8004411C(void);
void func_ovl10_06_800442D4(void);
void func_ovl10_06_800443DC(void);
void func_ovl10_06_800444F0(void);
void func_ovl10_06_800445DC(void);
void func_ovl10_06_800446D0(void);
void func_ovl10_06_8004476C(void);
void func_ovl10_06_80044804(void);
void func_ovl10_06_800448EC(void);
void func_ovl10_06_80044920(void);
void func_ovl10_06_800449BC(void);
void func_ovl10_06_80044A54(void);
void func_ovl10_06_80044AE4(void);
void func_ovl10_06_80044BCC(f32 arg0);
void func_ovl10_06_80044CAC(void);
void func_ovl10_06_80044D00(void);
void func_ovl10_06_80044EFC(void);
void func_ovl10_06_80044F8C(s32 arg0);
void func_ovl10_06_8004526C(void);
void func_ovl10_06_800452EC(void);
void func_ovl10_06_800453A0(void);
void func_ovl10_06_80045458(s32 arg0);
void func_ovl10_06_80045518(void);
void func_ovl10_06_80045598(void);
void func_ovl10_06_800455EC(void);
void func_ovl10_06_800456D4(void);
void func_ovl10_06_80045754(void);
void func_ovl10_06_800457C0(void);
void func_ovl10_06_80045838(s32 arg0);
void func_ovl10_06_8004584C(void);
void func_ovl10_06_80045888(void);
s32 func_ovl10_06_80045C20(void (*arg0)());
void func_ovl10_06_80045C64(void (*arg0)());
void func_ovl10_06_80045C90(void);
void func_ovl10_06_80045CE4(void);
void func_ovl10_06_80045F9C(void);
void func_ovl10_06_800460C8(void);
void func_ovl10_06_800463C0(void);
void func_ovl10_06_80046478(void);
void func_ovl10_06_800465F4(void);
void func_ovl10_06_800466C4(void);
void func_ovl10_06_8004683C(void);
void func_ovl10_06_80046A04(void);
s32 func_ovl10_06_80046B58(s32 arg0);
void func_ovl10_06_80046BC4(void);
void func_ovl10_06_80046BF0(void);
void func_ovl10_06_80046C34(void);
void func_ovl10_06_80046C64(void);
void func_ovl10_06_80046D74(void);
void func_ovl10_06_80047110(s32 arg0);
void func_ovl10_06_80047308(void);
void func_ovl10_06_800473FC(void);
void func_ovl10_06_80047450(void);
void func_ovl10_06_80047634(void);
void func_ovl10_06_80047810(void);
void func_ovl10_06_800479B8(void);
void func_ovl10_06_80047A50(void);
void func_ovl10_06_80047B0C(void);
void func_ovl10_06_80047B78(void);
void func_ovl10_06_80047BE0(s32 arg0);
void func_ovl10_06_80047C98(void);
void func_ovl10_06_80047D14(void);
void func_ovl10_06_80047E10(void);
void func_ovl10_06_80048110(void);
void func_ovl10_06_80048498(void);
void func_ovl10_06_8004870C(void);
void func_ovl10_06_80048944(void);
void func_ovl10_06_800489FC(void);
void func_ovl10_06_80048E64(void);
void func_ovl10_06_80048EA0(void);
void func_ovl10_06_80048EFC(UnkStructA *arg0);
void func_ovl10_06_80048F7C(UnkStructA *arg0);
s32 func_ovl10_06_80048FE8(void (*arg0)(), const char *arg1);
void func_ovl10_06_80049020(void);
void func_ovl10_06_80049118(s32 arg0, UnkStructA *arg1);
void func_ovl10_06_8004914C(f32 arg0);
void func_ovl10_06_80049194(f32 arg0, f32 arg1, f32 arg2);
void func_ovl10_06_800491F0(void);
void func_ovl10_06_80049208(void);

static void func_ovl10_06_8004355C(s32 model, s32 x, s32 n, s32 z);

/* .data */
/* two records of 0x44 bytes nothing in the object reads (4.5f, -0.24f; the second negated) */
s32 D_ovl10_06_8004A890[34] = {
    0x14, 1, 1, 0, 0, 0, 0, 0, 0, 0x40900000, 0, 0, 0xBE75C28F, 0, 0, 0, 0,
    0x14, 1, 1, 0, 0, 0, 0, 0, 0, 0xC0900000, 0, 0, 0x3E75C28F, 0, 0, 0, 0,
};
u32 D_ovl10_06_8004A918[][3] = { { 0xA60002, 0xE, 0x4 }, { 0xA70001, 0xE, 0x4 }, { 0xB70000, 0xE, 0x4 } };
f32 D_ovl10_06_8004A93C[3] = { 3800.0f, 3600.0f, 3600.0f };
f32 D_ovl10_06_8004A948[3] = { 0.0f, 0.0f, 0.0f };
/* unread: three 1s, then zeros */
s32 D_ovl10_06_8004A954[17] = { 1, 1, 1 };
/* 800460C8 and 80045888 own the rest (their local tables) */

/* .bss */
u8 D_ovl10_06_8004AB60[0x20]; /* unused */
s32 D_ovl10_06_8004AB80;
s32 D_ovl10_06_8004AB84;
s32 D_ovl10_06_8004AB88;
u8 D_ovl10_06_8004AB8C[0x4]; /* unused */
Vec3f D_ovl10_06_8004AB90;
s32 D_ovl10_06_8004AB9C;
s32 D_ovl10_06_8004ABA0;
u8 D_ovl10_06_8004ABA4[0x4]; /* unused */
s32 D_ovl10_06_8004ABA8[64]; /* M2C_UNK */
s32 D_ovl10_06_8004ACA8;
u8 D_ovl10_06_8004ACAC[0x4]; /* unused */
void (*D_ovl10_06_8004ACB0[64])(void);
UnkStructC * D_ovl10_06_8004ADB0;
s32 * D_ovl10_06_8004ADB4;
UnkStructA * D_ovl10_06_8004ADB8;
UnkStructA * D_ovl10_06_8004ADBC;
UnkStructA *D_ovl10_06_8004ADC0[4];
UnkStructA *D_ovl10_06_8004ADD0[4];
UnkStructA * D_ovl10_06_8004ADE0[2];
UnkStructA *D_ovl10_06_8004ADE8[4];
UnkStructA * D_ovl10_06_8004ADF8[72];
UnkStructA * D_ovl10_06_8004AF18;
u8 D_ovl10_06_8004AF1C[0x4]; /* unused */
UnkStruct_ovl10_06_8004A0E0 D_ovl10_06_8004AF20;
f32 D_ovl10_06_8004AF2C;
f32 D_ovl10_06_8004AF30;
f32 D_ovl10_06_8004AF34;
f32 D_ovl10_06_8004AF38;
f32 D_ovl10_06_8004AF3C;
f32 D_ovl10_06_8004AF40;
f32 D_ovl10_06_8004AF44;
f32 D_ovl10_06_8004AF48;
f32 D_ovl10_06_8004AF4C;
f32 D_ovl10_06_8004AF50;
f32 D_ovl10_06_8004AF54;
f32 D_ovl10_06_8004AF58[4];
f32 D_ovl10_06_8004AF68[4];
f32 D_ovl10_06_8004AF78[4];
f32 D_ovl10_06_8004AF88[4];
f32 D_ovl10_06_8004AF98[3];
f32 D_ovl10_06_8004AFA4;
f32 D_ovl10_06_8004AFA8[10];
f32 D_ovl10_06_8004AFD0[10];
f32 D_ovl10_06_8004AFF8[3];
f32 D_ovl10_06_8004B004;
f32 D_ovl10_06_8004B008;
f32 D_ovl10_06_8004B00C;
f32 D_ovl10_06_8004B010[64];
f32 D_ovl10_06_8004B110[64];
s32 D_ovl10_06_8004B210[3]; /* M2C_UNK */
s32 D_ovl10_06_8004B21C;
s32 D_ovl10_06_8004B220[4]; /* M2C_UNK */
s32 D_ovl10_06_8004B230[4]; /* M2C_UNK */
s32 D_ovl10_06_8004B240[3]; /* M2C_UNK */
s32 D_ovl10_06_8004B24C[1]; /* M2C_UNK */
s32 D_ovl10_06_8004B250[4]; /* M2C_UNK */
s32 D_ovl10_06_8004B260[4]; /* M2C_UNK */
s32 D_ovl10_06_8004B270[3]; /* M2C_UNK */
s32 D_ovl10_06_8004B27C;
s32 D_ovl10_06_8004B280;
s32 D_ovl10_06_8004B284;
s32 D_ovl10_06_8004B288;
u8 D_ovl10_06_8004B28C[0x4]; /* unused */
s32 D_ovl10_06_8004B290[64]; /* M2C_UNK */
s32 D_ovl10_06_8004B390[4]; /* M2C_UNK */
s32 D_ovl10_06_8004B3A0[3]; /* M2C_UNK */
s32 D_ovl10_06_8004B3AC;
s32 D_ovl10_06_8004B3B0;
s32 D_ovl10_06_8004B3B4;
u32 D_ovl10_06_8004B3B8;
s32 D_ovl10_06_8004B3BC;
s32 D_ovl10_06_8004B3C0[4];
s32 D_ovl10_06_8004B3D0[64]; /* M2C_UNK */
s32 D_ovl10_06_8004B4D0[64]; /* M2C_UNK */
s32 D_ovl10_06_8004B5D0[64]; /* M2C_UNK */
s32 D_ovl10_06_8004B6D0[64]; /* M2C_UNK */
s32 D_ovl10_06_8004B7D0;
u8 D_ovl10_06_8004B7D4[0x4]; /* unused */
s32 D_ovl10_06_8004B7D8[3]; /* M2C_UNK */
s32 D_ovl10_06_8004B7E4;
s32 D_ovl10_06_8004B7E8;
s32 D_ovl10_06_8004B7EC;
s32 D_ovl10_06_8004B7F0;
s32 D_ovl10_06_8004B7F4;
s32 D_ovl10_06_8004B7F8[64]; /* M2C_UNK */
s32 D_ovl10_06_8004B8F8;
s32 D_ovl10_06_8004B8FC;
f32 D_ovl10_06_8004B900[4];
f32 D_ovl10_06_8004B910[4];
f32 D_ovl10_06_8004B920[4];
f32 D_ovl10_06_8004B930[4];
f32 D_ovl10_06_8004B940[4];
f32 D_ovl10_06_8004B950[4];
f32 D_ovl10_06_8004B960[4];
f32 D_ovl10_06_8004B970[4];
f32 D_ovl10_06_8004B980[4];
UnkStruct_ovl10_06_8004A460 *D_ovl10_06_8004B990[2];
s32 D_ovl10_06_8004B998[3]; /* M2C_UNK */
UnkStructA * D_ovl10_06_8004B9A4;
UnkStructA * D_ovl10_06_8004B9A8;
u8 D_ovl10_06_8004B9AC[0x4]; /* unused */
UnkStructA *D_ovl10_06_8004B9B0[64];
UnkStructA * D_ovl10_06_8004BAB0[72];
UnkStructA *D_ovl10_06_8004BBD0[4];

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_06_80049248(void) {
}

static void func_ovl10_06_80049240(void) {
}

static void func_ovl10_06_80049238(void) {
}

static void func_ovl10_06_80049230(void) {
}

static void func_ovl10_06_80049228(void) {
}

static void func_ovl10_06_80049220(void) {
}

static void func_ovl10_06_80049218(void) {
}

static void func_ovl10_06_80049210(void) {
}

void func_ovl10_06_80049208(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_06_8004AB60[0] = D_ovl10_06_8004AB8C[0] + D_ovl10_06_8004ABA4[0] + D_ovl10_06_8004ACAC[0] +
                                 D_ovl10_06_8004AF1C[0] + D_ovl10_06_8004B28C[0] + D_ovl10_06_8004B7D4[0] +
                                 D_ovl10_06_8004B9AC[0];
    }
}

/* ovl_17_09's 80044B70 */
void func_ovl10_06_800491F0(void) {
    D_ovl10_06_8004AB84 = -1;
    D_ovl10_06_8004AB88 = -1;
}

/* ovl_17_09's 80044B14 */
void func_ovl10_06_80049194(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_06_80049DD8(D_ovl10_06_8004AB90.x, D_ovl10_06_8004AB90.y, D_ovl10_06_8004AB90.z);
    func_ovl10_06_80049DF8(arg0, arg1, arg2);
    func_ovl10_06_8004A108(180);
}

/* ovl_17_09's 80044ACC */
void func_ovl10_06_8004914C(f32 arg0) {
    f32 sp1C;

    func_ovl10_06_80049E00(&sp1C, NULL, NULL);
    func_ovl10_06_80049DF8(sp1C + arg0, 32768.0f, 32768.0f);
}

/* ovl_17_09's 80044A98 */
void func_ovl10_06_80049118(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl10_06_8004A690(arg0, p->unk10, p->unk14, p->unk18);
}

/* ovl_10_10's 80045700 */
/* runs the tasks, one frame each time round */
void func_ovl10_06_80049020(void) {
    s32 i;

    D_ovl10_06_8004AB9C = 0;
    D_ovl10_06_8004ABA0 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_06_8004ACB0[i] != NULL) {
                D_ovl10_06_8004ACA8 = i;
                if (D_ovl10_06_8004ABA8[i] == 0) {
                    D_ovl10_06_8004ACB0[i]();
                } else {
                    D_ovl10_06_8004ABA8[i]--;
                }
            }
        }
        D_ovl10_06_8004AB9C++;
        D_ovl10_06_8004AB9C &= 3;
        func_ovl10_06_8004A130();
    }
}

/* ovl_10_13's 80046DD8 */
/* Defined above its caller 80046E50, as in ovl_10_12. */
s32 func_ovl10_06_800430A8(void (*arg0)()) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_06_8004ACB0[i] == NULL) {
            D_ovl10_06_8004ACB0[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_06_80049258("trap task:entry failed\n");
    }
    return found;
}

/* ovl_10_13's 80046E50 */
s32 func_ovl10_06_80048FE8(void (*arg0)(), const char *arg1) {
    s32 i;

    i = func_ovl10_06_800430A8(arg0);
    func_ovl10_06_80049258("task_entry>%d:%s\n", i, arg1);
    return i;
}

/* ovl_10_13's 80046B4C */
void func_ovl10_06_80048F7C(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_06_80049E40(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_06_8004A018(arg0);
        func_ovl10_06_8004A130();
    }
}

/* ovl_10_13's 80046ACC */
void func_ovl10_06_80048EFC(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_06_8004A3E8(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_06_80049FA0(arg0, 0x01000000);
        func_ovl10_06_8004A108(5);
        func_ovl10_06_8004A3E8(0, 0, 0, 0.0f);
        func_ovl10_06_8004A068(arg0, &pos);
        func_ovl10_06_8004A540(12, &pos.x, 0);
    }
}

void func_ovl10_06_80048EA0(void) {
    func_ovl10_06_8004A130();
    func_ovl10_06_80049788(1);
    func_ovl10_06_80049700(0);
    func_ovl10_06_80049838(1);
    func_ovl10_06_800497A0("WM1 WAP WG1 WSH WDE WB2 ST300 WB11 ST780");
    func_ovl10_06_8004A108(0xA);
    func_ovl10_06_8004A7E8();
    func_ovl10_06_8004A0F8();
}

void func_ovl10_06_80048E64(void) {
    func_ovl10_06_80049DF8(315.0f, 32768.0f, 32768.0f);
    func_ovl10_06_8004A0F8();
}

void func_ovl10_06_800489FC(void) {
    UnkStructA **var_v1;
    UnkStructA *temp_a0;
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    s32 temp_a3;
    s32 temp_ft0;
    s32 temp_ft2;
    s32 temp_ft4;
    s32 temp_s4;
    s32 var_at;
    s32 var_s0;
    s32 var_s1;
    s32 var_s6;
    s32 var_s6_2;
    void **var_s5;
    void *temp_v0_3;
    void *temp_v0_4;

    temp_v0 = D_ovl10_06_8004ADB8->unk40;
    temp_v0->unk14 += D_ovl10_06_8004AF2C;
    var_s6 = 0;
    if (D_ovl10_06_8004B7F4 > 0) {
        var_v1 = D_ovl10_06_8004ADE0;
        do {
            temp_a0 = *var_v1;
            var_s6 += 1;
            var_at = var_s6 < D_ovl10_06_8004B7F4;
            if (temp_a0 != NULL) {
                temp_v0_2 = temp_a0->unk40;
                temp_v0_2->unk14 += D_ovl10_06_8004AF2C;
                var_at = var_s6 < D_ovl10_06_8004B7F4;
            }
            var_v1 += 1;
        } while (var_at != 0);
    }
    if ((D_ovl10_06_8004B27C != 0xA) || !(D_ovl10_06_8004ADB8->unk40->unk14 <= D_ovl10_06_8004AF30)) {
        if (D_ovl10_06_8004B27C == 8) {
            if (D_ovl10_06_8004AF30 <= D_ovl10_06_8004ADB8->unk40->unk14) {
                goto block_9;
            }
        }
    } else {
block_9:
        var_s6_2 = 0;
        if (D_ovl10_06_8004B27C == 0xA) {
            func_ovl10_06_80049688(D_ovl10_06_8004B284, 0, 0, 0x2F, 0x1F, 0, 0, 0);
            func_ovl10_06_80049640(0x14, 1, 8, 0x29, 0x16, 0x14, 0, 8);
            func_ovl10_06_80049688(D_ovl10_06_8004B288, 0x14, 8, 0x29, 0x16, 0x14, 1, 8);
            var_s1 = 0xF;
            var_s0 = 0xF;
        } else {
            func_ovl10_06_80049640(0x14, 0, 8, 0x29, 0x16, 0x14, 1, 8);
            func_ovl10_06_80049688(D_ovl10_06_8004B284, 0, 0, 0x2F, 0x1F, 0, 0, 0);
            var_s1 = 1;
            var_s0 = 0;
        }
        func_ovl10_06_800495D0(0x29, 0, 0xE, var_s0);
        func_ovl10_06_800495D0(0x29, 0, 0xF, var_s0);
        func_ovl10_06_800495D0(0x29, 0, 0x10, var_s0);
        func_ovl10_06_800495D0(0x29, 1, 0xE, var_s1);
        func_ovl10_06_800495D0(0x29, 1, 0xF, var_s1);
        func_ovl10_06_800495D0(0x29, 1, 0x10, var_s1);
        D_ovl10_06_8004ADB8->unk40->unk14 = D_ovl10_06_8004AF30;
        D_ovl10_06_8004ACB0[func_ovl10_06_80045C20(func_ovl10_06_800489FC)] = NULL;
        func_ovl10_06_80049650(0);
        var_s5 = D_ovl10_06_8004B990;
        if (D_ovl10_06_8004B7F4 > 0) {
            do {
                temp_v0_3 = *var_s5;
                if (temp_v0_3 != NULL) {
                    if (D_ovl10_06_8004B27C == 0xA) {
                        (*(f32 *)((u8 *)(temp_v0_3) + 32)) = 0.0f;
                    } else {
                        (*(f32 *)((u8 *)(temp_v0_3) + 32)) = 1.0f;
                    }
                    temp_v0_4 = *var_s5;
                    temp_ft2 = (s32) (*(f32 *)((u8 *)(temp_v0_4) + 28));
                    temp_ft4 = (s32) (*(f32 *)((u8 *)(temp_v0_4) + 32));
                    temp_ft0 = (s32) (*(f32 *)((u8 *)(temp_v0_4) + 36));
                    temp_a3 = func_ovl10_06_80049608(temp_ft2, temp_ft4, temp_ft0) | 0x40;
                    func_ovl10_06_800495D0(temp_ft2, temp_ft4, temp_ft0, temp_a3);
                    func_ovl10_06_800495D0(temp_ft2 + 1, temp_ft4, temp_ft0, temp_a3);
                    temp_s4 = temp_ft0 + 1;
                    func_ovl10_06_800495D0(temp_ft2, temp_ft4, temp_s4, temp_a3);
                    func_ovl10_06_800495D0(temp_ft2, temp_ft4, temp_s4, temp_a3);
                }
                var_s6_2 += 1;
                var_s5 += 1;
            } while (var_s6_2 < D_ovl10_06_8004B7F4);
        }
        func_ovl10_06_80048944();
        func_ovl10_06_8004A160(0xB0, 0xB0);
        func_ovl10_06_8004A160(0x50, 0x50);
        func_ovl10_06_8004A670(0xA4);
    }
}

void func_ovl10_06_80048944(void) {
    UnkStructA **var_s0;
    UnkStructA *temp_v0;
    s32 var_s1;

    var_s1 = 0;
    if (D_ovl10_06_8004B7D0 > 0) {
        var_s0 = D_ovl10_06_8004ADF8;
        do {
            temp_v0 = *var_s0;
            temp_v0->unk40->unk14 = D_ovl10_06_8004ADB8->unk40->unk14 + temp_v0->unk50;
            func_ovl10_06_80049FA0(*var_s0, 0x200000);
            func_ovl10_06_80049F70(*var_s0);
            var_s1 += 1;
            var_s0 += 1;
            (*(s32 *)((u8 *)(var_s0) + -4)) = 0;
        } while (var_s1 < D_ovl10_06_8004B7D0);
    }
}

void func_ovl10_06_8004870C(void) {
    func_ovl10_06_80049DD8(D_ovl10_06_8004AF4C, 32768.0f, 32768.0f);
    func_ovl10_06_80049DF8(270.0f, D_ovl10_06_8004AF34, D_ovl10_06_8004AF44);
    D_ovl10_06_8004AF34 += D_ovl10_06_8004AF3C;
    D_ovl10_06_8004AF44 = (f32) (D_ovl10_06_8004AF44 + D_ovl10_06_8004AF40);
    D_ovl10_06_8004AF4C += D_ovl10_06_8004AF54;
    if (((D_ovl10_06_8004AF3C > 0.0f) && (D_ovl10_06_8004AF38 <= D_ovl10_06_8004AF34)) || ((D_ovl10_06_8004AF3C < 0.0f) && (D_ovl10_06_8004AF34 <= D_ovl10_06_8004AF38))) {
        D_ovl10_06_8004AF3C = 0.0f;
        D_ovl10_06_8004AF34 = D_ovl10_06_8004AF38;
    }
    if (((D_ovl10_06_8004AF40 > 0.0f) && (D_ovl10_06_8004AF48 <= D_ovl10_06_8004AF44)) || ((D_ovl10_06_8004AF40 < 0.0f) && (D_ovl10_06_8004AF44 <= D_ovl10_06_8004AF48))) {
        D_ovl10_06_8004AF44 = D_ovl10_06_8004AF48;
        D_ovl10_06_8004AF40 = 0.0f;
    }
    if (((D_ovl10_06_8004AF54 > 0.0f) && (D_ovl10_06_8004AF50 <= D_ovl10_06_8004AF4C)) || ((D_ovl10_06_8004AF54 < 0.0f) && (D_ovl10_06_8004AF4C <= D_ovl10_06_8004AF50))) {
        D_ovl10_06_8004AF4C = D_ovl10_06_8004AF50;
        D_ovl10_06_8004AF54 = 0.0f;
    }
    if ((D_ovl10_06_8004AF3C == 0.0f) && (D_ovl10_06_8004AF40 == 0.0f) && (D_ovl10_06_8004AF54 == 0.0f)) {
        D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    }
}

void func_ovl10_06_80048498(void) {
    func_ovl10_06_80049EC8(D_ovl10_06_8004B900);
    func_ovl10_06_80049EE8(D_ovl10_06_8004B940);
    D_ovl10_06_8004B900[0] = (f32) (D_ovl10_06_8004B900[0] + D_ovl10_06_8004B920[0]);
    if (((D_ovl10_06_8004B920[0] < 0.0f) && (D_ovl10_06_8004B900[0] <= D_ovl10_06_8004B910[0])) || ((D_ovl10_06_8004B920[0] > 0.0f) && (D_ovl10_06_8004B910[0] <= D_ovl10_06_8004B900[0]))) {
        D_ovl10_06_8004B920[0] = 0.0f;
        D_ovl10_06_8004B900[0] = D_ovl10_06_8004B910[0];
    }
    D_ovl10_06_8004B900[1] = (f32) (D_ovl10_06_8004B900[1] + D_ovl10_06_8004B920[1]);
    if (((D_ovl10_06_8004B920[1] < 0.0f) && (D_ovl10_06_8004B900[1] <= D_ovl10_06_8004B910[1])) || ((D_ovl10_06_8004B920[1] > 0.0f) && (D_ovl10_06_8004B910[1] <= D_ovl10_06_8004B900[1]))) {
        D_ovl10_06_8004B900[1] = D_ovl10_06_8004B910[1];
        D_ovl10_06_8004B920[1] = 0.0f;
    }
    D_ovl10_06_8004B940[1] = (f32) (D_ovl10_06_8004B940[1] + D_ovl10_06_8004B960[1]);
    if (((D_ovl10_06_8004B960[1] < 0.0f) && (D_ovl10_06_8004B940[1] <= D_ovl10_06_8004B950[1])) || ((D_ovl10_06_8004B960[1] > 0.0f) && (D_ovl10_06_8004B950[1] <= D_ovl10_06_8004B940[1]))) {
        D_ovl10_06_8004B940[1] = D_ovl10_06_8004B950[1];
        D_ovl10_06_8004B960[1] = 0.0f;
    }
    D_ovl10_06_8004B940[2] = (f32) (D_ovl10_06_8004B940[2] + D_ovl10_06_8004B960[2]);
    if (((D_ovl10_06_8004B960[2] < 0.0f) && (D_ovl10_06_8004B940[2] <= D_ovl10_06_8004B950[2])) || ((D_ovl10_06_8004B960[2] > 0.0f) && (D_ovl10_06_8004B950[2] <= D_ovl10_06_8004B940[2]))) {
        D_ovl10_06_8004B940[2] = D_ovl10_06_8004B950[2];
        D_ovl10_06_8004B960[2] = 0.0f;
    }
    if ((D_ovl10_06_8004B920[0] == 0.0f) && (D_ovl10_06_8004B920[1] == 0.0f) && (D_ovl10_06_8004B960[1] == 0.0f) && (D_ovl10_06_8004B960[2] == 0.0f)) {
        D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    }
}

void func_ovl10_06_80048110(void) {
    Vec3f d;
    Vec3f pos;
    Vec3f ang;
    UnkStruct_ovl10_06_8004A0B0 *p;

    switch (D_ovl10_06_8004B3B8) {
    case 10:
        if (D_ovl10_06_8004B3AC & 4) {
            ang.z = 70.0f;
            ang.y = 0.0f;
            ang.x = D_ovl10_06_8004ADD0[0]->unk40->unk20;
            func_ovl10_06_80049F30(&ang.x, &d.x);
            func_ovl10_06_8004A538(0, D_ovl10_06_8004ADD0[0]->unk40->unk10 + d.x, D_ovl10_06_8004ADD0[0]->unk40->unk14 + 115.0f,
                                   D_ovl10_06_8004ADD0[0]->unk40->unk18 + d.z, 0);
            D_ovl10_06_8004B9A8 = func_ovl10_06_80049FC0(0x2D2, 0x11080050, 0xD0, 0);
            D_ovl10_06_8004B9A8->unk40->unk10 = D_ovl10_06_8004AFA8[9];
            D_ovl10_06_8004B9A8->unk40->unk14 = D_ovl10_06_8004B9A4->unk40->unk14;
            D_ovl10_06_8004B9A8->unk40->unk18 = D_ovl10_06_8004AFD0[9];
            D_ovl10_06_8004B9A8->unk40->unk28 = 5.0f;
            D_ovl10_06_8004B9A8->unk40->unk2C = 5.0f;
            D_ovl10_06_8004B9A8->unk40->unk30 = 5.0f;
            D_ovl10_06_8004B9A8->unk30 = 1;
            D_ovl10_06_8004B9A8->unk34 = 10.0f;
            D_ovl10_06_8004B9A8->unk38 = 0.0f;
            p = func_ovl10_06_8004A0B0(D_ovl10_06_8004B9A8, 7);
            if (p != NULL) {
                p->unk14 |= 0x40;
                if (!(func_ovl10_06_80049800() & 2)) {
                    D_ovl10_06_8004ABA0 = 1;
                }
            }
            func_ovl10_06_8004A068(D_ovl10_06_8004ADD0[0], &pos);
            func_ovl10_06_8004A698(0x95, &pos.x);
        }
        break;
    case 9:
        if (D_ovl10_06_8004B9A8 != NULL) {
            D_ovl10_06_8004B9A8->unk40->unk28 = 5.0f;
            D_ovl10_06_8004B9A8->unk40->unk2C = 5.0f;
            D_ovl10_06_8004B9A8->unk40->unk30 = 5.0f;
        }
        break;
    case 8:
        if (D_ovl10_06_8004B9A8 != NULL) {
            D_ovl10_06_8004B9A8->unk40->unk28 = 5.0f;
            D_ovl10_06_8004B9A8->unk40->unk2C = 5.0f;
            D_ovl10_06_8004B9A8->unk40->unk30 = 5.0f;
        }
        break;
    case 7:
        if (D_ovl10_06_8004B9A8 != NULL) {
            func_ovl10_06_80049FB0(D_ovl10_06_8004B9A8);
            D_ovl10_06_8004B9A8 = NULL;
        }
        break;
    case 0:
        D_ovl10_06_8004B3B8 = 11;
        D_ovl10_06_8004B3B4--;
        break;
    }
    D_ovl10_06_8004B3B8--;
    if (D_ovl10_06_8004B3B4 == 0) {
        D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
        if (D_ovl10_06_8004B3AC & 4) {
            D_ovl10_06_8004B3AC &= ~4;
            func_ovl10_06_80047BE0(2);
        }
    }
}

void func_ovl10_06_80047E10(void) {
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    s32 i;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_ft3;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 var_fa1;
    f32 var_fv1;

    func_ovl10_06_8004A068(D_ovl10_06_8004ADBC, &sp54);
    for (i = 9; i > 0; i--) {
        D_ovl10_06_8004AFA8[i] = D_ovl10_06_8004AFA8[i - 1];
        D_ovl10_06_8004AFD0[i] = D_ovl10_06_8004AFD0[i - 1];
    }
    D_ovl10_06_8004AFA8[0] = D_ovl10_06_8004B9A4->unk40->unk10;
    D_ovl10_06_8004AFD0[0] = D_ovl10_06_8004B9A4->unk40->unk18;
    func_ovl10_06_8004A068(D_ovl10_06_8004ADD0, &sp48);
    sp48.y = sp54.y;
    if (func_ovl10_06_80049F40(&sp54, &sp48) < 1500.0f) {
        if (!(D_ovl10_06_8004B3AC & 1)) {
            func_ovl10_06_80047D14();
        }
        func_ovl10_06_8004A068(D_ovl10_06_8004B9A4, &sp48);
        sp48.y = sp54.y;
        func_ovl10_06_80049F28(&sp48.x, &sp54.x, &sp30);
        sp34 -= 90.0f;
        temp_fv0 = func_ovl10_06_80049F40(&sp54, &sp48);
        var_fa1 = temp_fv0;
        if (temp_fv0 > 6.8f) {
            var_fv1 = 6.8f;
        } else {
            var_fv1 = temp_fv0;
        }
        if (temp_fv0 < 1.0f) {
            var_fa1 = 0.0f;
        }
        sp24 = sp30;
        sp28 = var_fv1;
        sp2C = var_fa1;
        temp_v0 = D_ovl10_06_8004B9A4->unk40;
        temp_v0->unk10 += var_fv1 * func_ovl10_06_8004A290(sp30);
        temp_v0_2 = D_ovl10_06_8004B9A4->unk40;
        temp_v0_2->unk18 += var_fv1 * func_ovl10_06_8004A298(sp30);
        if (D_ovl10_06_8004B3AC & 2) {
            if (D_ovl10_06_8004B3B0 > 0) {
                D_ovl10_06_8004B3B0 -= 1;
            }
            if ((D_ovl10_06_8004B3B0 == 0) && !(D_ovl10_06_8004B3AC & 4)) {
                func_ovl10_06_80047C98();
            }
        }
        if ((sp2C == 0.0f) && !(D_ovl10_06_8004B3AC & 2)) {
            func_ovl10_06_80047BE0(1);
            if (!(D_ovl10_06_8004B3AC & 4)) {
                D_ovl10_06_8004B3B0 = 0x3C;
                D_ovl10_06_8004B3AC |= 2;
                func_ovl10_06_8004A068(D_ovl10_06_8004B9A4, &sp3C);
                func_ovl10_06_8004A698(0x94, &sp3C.x);
            }
        }
    } else if (D_ovl10_06_8004B3AC & 1) {
        func_ovl10_06_80047B78();
    }
}

void func_ovl10_06_80047D14(void) {
    s32 i;

    D_ovl10_06_8004B9A4 = func_ovl10_06_80049FC0(0xCC, 0x11080000, 0xD0, 0);
    D_ovl10_06_8004B9A4->unk40->unk10 = D_ovl10_06_8004B930[0];
    D_ovl10_06_8004B9A4->unk40->unk14 = D_ovl10_06_8004B930[1];
    D_ovl10_06_8004B9A4->unk40->unk18 = D_ovl10_06_8004B930[2];
    D_ovl10_06_8004B9A4->unk40->unk36 = 0xC0;
    D_ovl10_06_8004B3AC |= 1;
    for (i = 0; i < 10; i++) {
        D_ovl10_06_8004AFA8[i] = D_ovl10_06_8004B930[0];
        D_ovl10_06_8004AFD0[i] = D_ovl10_06_8004B930[2];
    }
}

void func_ovl10_06_80047C98(void) {
    s32 temp_t2;

    D_ovl10_06_8004B3AC &= ~2;
    D_ovl10_06_8004B3B4 = 4;
    D_ovl10_06_8004B3BC = 1;
    D_ovl10_06_8004B3B8 = 0xA;
    temp_t2 = D_ovl10_06_8004B3AC & ~2;
    D_ovl10_06_8004B3AC = temp_t2;
    D_ovl10_06_8004B3AC = temp_t2 | 4;
    D_ovl10_06_8004B9A8 = NULL;
    func_ovl10_06_800430A8(func_ovl10_06_80048110);
}

void func_ovl10_06_80047BE0(s32 arg0) {
    Vec3f sp24;
    s32 sp20;
    UnkStructA *temp_v0;
    s32 var_t0;

    if (arg0 == 1) {
        var_t0 = 0xCB;
    } else {
        var_t0 = 0xCC;
    }
    sp20 = var_t0;
    func_ovl10_06_8004A068(D_ovl10_06_8004B9A4, &sp24);
    func_ovl10_06_80049FB0(D_ovl10_06_8004B9A4);
    D_ovl10_06_8004B9A4 = func_ovl10_06_80049FC0(sp20, 0x11080000, 0xD0, 0);
    D_ovl10_06_8004B9A4->unk40->unk10 = sp24.x;
    D_ovl10_06_8004B9A4->unk40->unk14 = sp24.y;
    D_ovl10_06_8004B9A4->unk40->unk18 = sp24.z;
    D_ovl10_06_8004B9A4->unk40->unk36 = 0xC0;
}

void func_ovl10_06_80047B78(void) {
    D_ovl10_06_8004B930[0] = (f32) D_ovl10_06_8004B9A4->unk40->unk10;
    D_ovl10_06_8004B930[1] = (f32) D_ovl10_06_8004B9A4->unk40->unk14;
    D_ovl10_06_8004B930[2] = (f32) D_ovl10_06_8004B9A4->unk40->unk18;
    func_ovl10_06_80049FB0(D_ovl10_06_8004B9A4);
    D_ovl10_06_8004B9A4 = NULL;
    D_ovl10_06_8004B3AC = 0;
}

void func_ovl10_06_80047B0C(void) {
    f32 sp34;
    Vec3f sp28;
    Vec3f sp1C;

    if (D_ovl10_06_8004B9A4 != NULL) {
        func_ovl10_06_8004A068(D_ovl10_06_8004ADD0, &sp28);
        func_ovl10_06_8004A068(D_ovl10_06_8004B9A4, &sp1C);
        func_ovl10_06_80049F28(&sp28.x, &sp1C.x, &sp34);
        D_ovl10_06_8004ADD0[0]->unk40->unk20 = sp34;
    }
}

void func_ovl10_06_80047A50(void) {
    Vec3f sp2C;
    UnkStructA **var_s1;
    s32 var_s0;

loop_1:
    if (func_ovl10_06_8004A640() != 0) {
        var_s0 = 0;
        if (D_ovl10_06_8004B7F0 > 0) {
            var_s1 = D_ovl10_06_8004BAB0;
            do {
                func_ovl10_06_8004A068(*var_s1, &sp2C);
                func_ovl10_06_8004A668(&sp2C.x);
                var_s0 += 1;
                var_s1 += 1;
            } while (var_s0 < D_ovl10_06_8004B7F0);
        }
    } else {
        func_ovl10_06_8004A0F8();
    }
    func_ovl10_06_8004A130();
    goto loop_1;
}

void func_ovl10_06_800479B8(void) {
    Vec3f pos;
    s32 z;

    if (--D_ovl10_06_8004B7EC == 0) {
        D_ovl10_06_8004B7EC = 120;
        if (func_ovl10_06_8004A640() < 3) {
            z = 16;
            if (func_ovl10_06_8004A2A8(2) != 0) {
                z = 14;
            }
            func_ovl10_06_800495F8(34.0f, 0.0f, z, &pos.x, 0);
            func_ovl10_06_8004A608(5, pos.x, pos.y, pos.z);
        }
    }
}

void func_ovl10_06_80047810(void) {
    Vec3f pos2;
    Vec3f from;
    Vec3f to;
    f32 angles[2];
    s32 i;

    i = D_ovl10_06_8004B7F8[D_ovl10_06_8004ACA8];
    D_ovl10_06_8004B8F8++;
    func_ovl10_06_8004A068(D_ovl10_06_8004BBD0[i], &from);
    D_ovl10_06_8004BBD0[i]->unk40->unk10 += D_ovl10_06_8004B010[i];
    D_ovl10_06_8004BBD0[i]->unk40->unk18 += D_ovl10_06_8004B110[i];
    func_ovl10_06_8004A018(D_ovl10_06_8004BBD0[i]);
    func_ovl10_06_8004A068(D_ovl10_06_8004BBD0[i], &to);
    func_ovl10_06_80049F28(&from.x, &to.x, angles);
    D_ovl10_06_8004BBD0[i]->unk40->unk1C = 90.0f - angles[1];
    D_ovl10_06_8004BBD0[i]->unk40->unk20 = angles[0];
    if (D_ovl10_06_8004BBD0[i]->unk6C == 0.0f || func_ovl10_06_80049F48(D_ovl10_06_8004BBD0[i], 0x10) == 0) {
        func_ovl10_06_8004A068(D_ovl10_06_8004BBD0[i], &pos2);
        pos2.y += 50.0f;
        func_ovl10_06_8004A540(0xA, &pos2.x, 0);
        func_ovl10_06_8004A698(0x175, &pos2.x);
        func_ovl10_06_80049FB0(D_ovl10_06_8004BBD0[i]);
        D_ovl10_06_8004BBD0[i] = NULL;
        D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    }
}

void func_ovl10_06_80047634(void) {
    Vec3f sp2C;
    Vec3f sp20;
    s32 *temp_v1;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 var_t7;
    s32 var_t9;
    s32 var_v0;
    s32 var_v1;

    func_ovl10_06_8004A068(D_ovl10_06_8004B9B0[D_ovl10_06_8004ACA8], &sp2C);
    func_ovl10_06_8004A068(D_ovl10_06_8004ADBC, &sp20);
    temp_t8 = D_ovl10_06_8004ACA8 * 4;
    var_v0 = temp_t8;
    sp20.y = sp2C.y;
    if (*(s32 *)((u8 *)D_ovl10_06_8004B4D0 + temp_t8) == 0xB4) {
        if (func_ovl10_06_80049F40(&sp2C, &sp20) <= 700.0f) {
            temp_t0 = D_ovl10_06_8004ACA8 * 4;
            temp_v1 = (s32 *)((u8 *)D_ovl10_06_8004B5D0 + temp_t0);
            var_v0 = temp_t0;
            *temp_v1 |= 1;
        } else {
            temp_t4 = D_ovl10_06_8004ACA8 * 4;
            *(s32 *)((u8 *)D_ovl10_06_8004B4D0 + temp_t4) = 0;
            var_v0 = temp_t4;
        }
    }
    var_v1 = *(s32 *)((u8 *)D_ovl10_06_8004B5D0 + var_v0);
    var_t7 = var_v1 & 2;
    if (var_v1 & 1) {
        func_ovl10_06_80047450();
        temp_t6 = D_ovl10_06_8004ACA8 * 4;
        var_v1 = *(s32 *)((u8 *)D_ovl10_06_8004B5D0 + temp_t6);
        var_v0 = temp_t6;
        var_t7 = var_v1 & 2;
    }
    var_t9 = var_v1 & 4;
    if (var_t7 != 0) {
        func_ovl10_06_800473FC();
        temp_t8_2 = D_ovl10_06_8004ACA8 * 4;
        var_v0 = temp_t8_2;
        var_t9 = *(s32 *)((u8 *)D_ovl10_06_8004B5D0 + temp_t8_2) & 4;
    }
    if (var_t9 != 0) {
        if (func_ovl10_06_80049F40(&sp2C, &sp20) <= 700.0f) {
            func_ovl10_06_80047308();
            var_v0 = D_ovl10_06_8004ACA8 * 4;
        } else {
            temp_t1 = D_ovl10_06_8004ACA8 * 4;
            temp_v1_2 = (s32 *)((u8 *)D_ovl10_06_8004B5D0 + temp_t1);
            var_v0 = temp_t1;
            *temp_v1_2 &= ~4;
            *(s32 *)((u8 *)D_ovl10_06_8004B4D0 + temp_t1) = 0;
        }
    }
    temp_v1_3 = (s32 *)((u8 *)D_ovl10_06_8004B4D0 + var_v0);
    *temp_v1_3 += 1;
}

void func_ovl10_06_80047450(void) {
    Vec3f sp44;
    Vec3f sp38;
    f32 sp2C;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv0;
    f32 var_fv1;
    s32 *temp_v0_2;
    s32 temp_t2;
    s32 temp_t9;
    void *temp_v0;
    void *var_v0;

    func_ovl10_06_8004A068(D_ovl10_06_8004B9B0[D_ovl10_06_8004ACA8], &sp44);
    func_ovl10_06_8004A068(D_ovl10_06_8004ADBC, &sp38);
    func_ovl10_06_80049F28(&sp44.x, &sp38.x, &sp2C);
    temp_v0 = (*(void **)((u8 *)(D_ovl10_06_8004B9B0[D_ovl10_06_8004ACA8]) + 64));
    temp_fv1 = (*(f32 *)((u8 *)(temp_v0) + 32));
    var_fv0 = sp2C - temp_fv1;
    if (var_fv0 >= 180.0f) {
        var_fv0 -= 360.0f;
    }
    if (var_fv0 <= -180.0f) {
        var_fv0 += 360.0f;
    }
    var_fa0 = 0.7f;
    var_fa1 = var_fv0;
    if (var_fv0 < 0.0f) {
        var_fa0 = -1.5f;
        var_fa1 = -var_fv0;
    }
    if ((f64) var_fa1 < 1.5) {
        var_fa0 = var_fv0;
    }
    (*(f32 *)((u8 *)(temp_v0) + 32)) = (f32) (temp_fv1 + var_fa0);
    var_v0 = (*(void **)((u8 *)(D_ovl10_06_8004B9B0[D_ovl10_06_8004ACA8]) + 64));
    var_fv1 = (*(f32 *)((u8 *)(var_v0) + 32));
    if (var_fv1 >= 360.0f) {
        (*(f32 *)((u8 *)(var_v0) + 32)) = (f32) (var_fv1 - 360.0f);
        var_v0 = (*(void **)((u8 *)(D_ovl10_06_8004B9B0[D_ovl10_06_8004ACA8]) + 64));
        var_fv1 = (*(f32 *)((u8 *)(var_v0) + 32));
    }
    if (var_fv1 < 0.0f) {
        (*(f32 *)((u8 *)(var_v0) + 32)) = (f32) (var_fv1 + 360.0f);
    }
    if (var_fv0 == 0.0f) {
        temp_t9 = D_ovl10_06_8004ACA8 * 4;
        temp_v0_2 = (s32 *)((u8 *)D_ovl10_06_8004B5D0 + temp_t9);
        temp_t2 = *temp_v0_2 & ~1;
        *temp_v0_2 = temp_t2;
        *temp_v0_2 = temp_t2 | 2;
        *(s32 *)((u8 *)D_ovl10_06_8004B6D0 + temp_t9) = 0x4D;
    }
}

void func_ovl10_06_800473FC(void) {
    s32 *temp_v1;
    s32 *temp_v1_2;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_t9;

    temp_t6 = D_ovl10_06_8004ACA8 * 4;
    temp_v1 = (s32 *)((u8 *)D_ovl10_06_8004B6D0 + temp_t6);
    temp_t9 = *temp_v1 - 1;
    *temp_v1 = temp_t9;
    if (temp_t9 == 0) {
        temp_v1_2 = (s32 *)((u8 *)D_ovl10_06_8004B5D0 + temp_t6);
        temp_t3 = *temp_v1_2 | 4;
        *temp_v1_2 = temp_t3;
        *temp_v1_2 = temp_t3 & ~2;
    }
}

void func_ovl10_06_80047308(void) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    s32 *temp_v1;
    s32 temp_t8;
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(D_ovl10_06_8004B9B0[D_ovl10_06_8004ACA8]) + 64));
    if ((f64) (*(f32 *)((u8 *)(temp_v0) + 32)) >= 0.0) {

    }
    sp24 = (*(f32 *)((u8 *)(temp_v0) + 16)) - 20.0f;
    sp20 = (*(f32 *)((u8 *)(temp_v0) + 20)) + 100.0f;
    sp1C = (*(f32 *)((u8 *)(temp_v0) + 24)) + 40.0f;
    func_ovl10_06_80047110(D_ovl10_06_8004ACA8);
    temp_t8 = D_ovl10_06_8004ACA8 * 4;
    *(s32 *)((u8 *)D_ovl10_06_8004B4D0 + temp_t8) = 0;
    temp_v1 = (s32 *)((u8 *)D_ovl10_06_8004B5D0 + temp_t8);
    *temp_v1 &= ~4;
    func_ovl10_06_8004A690(0x94, sp24, sp20, sp1C);
}

void func_ovl10_06_80047110(s32 arg0) {
    Vec3f sp48;
    Vec3f sp3C;
    f32 sp30;
    s32 sp2C;
    UnkStructA **temp_s0;
    UnkStructA *temp_v0;
    s32 temp_t6;
    void **temp_v1;

    D_ovl10_06_8004B8F8 = 0;
    temp_v0 = func_ovl10_06_80049FC0(0x106, 0x01000040, 0xD0, 0);
    temp_t6 = arg0 * 4;
    temp_v1 = (UnkStructA * *)((u8 *)D_ovl10_06_8004B9B0 + temp_t6);
    temp_s0 = (UnkStructA * *)((u8 *)D_ovl10_06_8004BBD0 + temp_t6);
    *temp_s0 = temp_v0;
    temp_v0->unk40->unk10 = (*(f32 *)((u8 *)((*(void **)((u8 *)(*temp_v1) + 64))) + 16));
    (*temp_s0)->unk40->unk14 = (*(f32 *)((u8 *)((*(void **)((u8 *)(*temp_v1) + 64))) + 20));
    (*temp_s0)->unk40->unk18 = (*(f32 *)((u8 *)((*(void **)((u8 *)(*temp_v1) + 64))) + 24));
    (*temp_s0)->unk40->unk20 = 270.0f;
    (*temp_s0)->unk30 = 1;
    (*temp_s0)->unk34 = 50.0f;
    (*temp_s0)->unk38 = 50.0f;
    sp2C = temp_t6;
    func_ovl10_06_8004A068(D_ovl10_06_8004ADBC, &sp48);
    func_ovl10_06_8004A068(*temp_s0, &sp3C);
    func_ovl10_06_80049F28(&sp3C.x, &sp48.x, &sp30);
    (*temp_s0)->unk38 = 50.0f;
    (*temp_s0)->unk40->unk20 = sp30;
    *(f32 *)((u8 *)D_ovl10_06_8004B010 + sp2C) = (sp48.x - sp3C.x) / 56.0f;
    *(f32 *)((u8 *)D_ovl10_06_8004B110 + sp2C) = (sp48.z - sp3C.z) / 56.0f;
    (*temp_s0)->unk68 = 40.0f;
    func_ovl10_06_80049FD0(*temp_s0);
    D_ovl10_06_8004B7F8[func_ovl10_06_800430A8(func_ovl10_06_80047810)] = arg0;
    func_ovl10_06_8004A068(*temp_s0, &sp48);
    sp48.y += 50.0f;
    func_ovl10_06_8004A540(0xE, &sp48.x, 0);
    func_ovl10_06_8004A698(0x16F, &sp48.x);
}

void func_ovl10_06_80046D74(void) {
    s32 i;
    s32 state;

    i = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8];
    state = D_ovl10_06_8004B210[i];
    switch (state) {
    case 0:
        D_ovl10_06_8004ADC0[i]->unk40->unk10 += D_ovl10_06_8004AF58[i];
        if ((D_ovl10_06_8004AF58[i] < 0.0f && D_ovl10_06_8004ADC0[i]->unk40->unk10 <= D_ovl10_06_8004A93C[i]) ||
            (D_ovl10_06_8004AF58[i] > 0.0f && D_ovl10_06_8004A93C[i] <= D_ovl10_06_8004ADC0[i]->unk40->unk10)) {
            D_ovl10_06_8004AF58[i] = 0.0f;
            D_ovl10_06_8004B210[i]++;
        }
        if (D_ovl10_06_8004B21C == 0 && D_ovl10_06_8004ADC0[i]->unk40->unk10 < 4000.0f) {
            D_ovl10_06_8004B21C = 1;
            func_ovl10_06_80046C64();
        }
        break;
    case 1:
        D_ovl10_06_8004ADC0[i]->unk40->unk14 += D_ovl10_06_8004AF68[i];
        if (D_ovl10_06_8004AF68[i] == 0.0f ||
            (D_ovl10_06_8004AF68[i] < 0.0f && D_ovl10_06_8004ADC0[i]->unk40->unk14 <= D_ovl10_06_8004A948[i]) ||
            (D_ovl10_06_8004AF68[i] > 0.0f && D_ovl10_06_8004A948[i] <= D_ovl10_06_8004ADC0[i]->unk40->unk14)) {
            D_ovl10_06_8004AF68[i] = 0.0f;
            D_ovl10_06_8004B210[i]++;
            func_ovl10_06_80049FA0(D_ovl10_06_8004ADC0[i], 0x20);
        }
        if (&D_ovl10_06_8004AF68[i] == D_ovl10_06_8004AF68 && D_ovl10_06_8004B240[i] == 3) {
            D_ovl10_06_8004B7D8[i] = 150;
        } else {
            D_ovl10_06_8004B7D8[i] = 1;
        }
        break;
    case 2:
        if (--D_ovl10_06_8004B7D8[i] == 0) {
            D_ovl10_06_8004B210[i] = state + 1;
        }
        break;
    case 3:
        D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
        D_ovl10_06_8004B3A0[i] &= ~0x30;
        D_ovl10_06_8004B3A0[i] |= 0x40;
        D_ovl10_06_8004B390[i] = 0;
        if (i == 0) {
            if (D_ovl10_06_8004B280 == 0) {
                D_ovl10_06_8004B3AC = 0;
                func_ovl10_06_80046BF0();
                func_ovl10_06_800430A8(func_ovl10_06_80047E10);
                func_ovl10_06_800430A8(func_ovl10_06_80047B0C);
                D_ovl10_06_8004B3C0[0] = func_ovl10_06_800430A8(func_ovl10_06_800479B8);
                D_ovl10_06_8004B7EC = 120;
            }
        } else {
            D_ovl10_06_8004B3C0[i] = func_ovl10_06_80046B58(i);
        }
        D_ovl10_06_8004ADE8[i] = 0;
        break;
    }
}

void func_ovl10_06_80046C64(void) {
    D_ovl10_06_8004B900[0] = 4000.0f;
    D_ovl10_06_8004B900[1] = 400.0f;
    D_ovl10_06_8004B910[0] = 3200.0f;
    D_ovl10_06_8004B910[1] = 0.0f;
    D_ovl10_06_8004B900[2] = 1500.0f;
    D_ovl10_06_8004B920[0] = (f32) ((D_ovl10_06_8004B910[0] - D_ovl10_06_8004B900[0]) / 150.0f);
    D_ovl10_06_8004B920[1] = (f32) ((D_ovl10_06_8004B910[1] - D_ovl10_06_8004B900[1]) / 150.0f);
    func_ovl10_06_80049EF0(D_ovl10_06_8004B940);
    D_ovl10_06_8004B950[1] = 45.0f;
    D_ovl10_06_8004B950[2] = 2400.0f;
    D_ovl10_06_8004B960[1] = (f32) ((D_ovl10_06_8004B950[1] - D_ovl10_06_8004B940[1]) / 150.0f);
    D_ovl10_06_8004B960[2] = (f32) ((D_ovl10_06_8004B950[2] - D_ovl10_06_8004B940[2]) / 150.0f);
    func_ovl10_06_800430A8(func_ovl10_06_80048498);
}

void func_ovl10_06_80046C34(void) {
    D_ovl10_06_8004B3AC = 0;
    func_ovl10_06_80046BF0();
    func_ovl10_06_800430A8(func_ovl10_06_80047E10);
}

void func_ovl10_06_80046BF0(void) {
    D_ovl10_06_8004B930[1] = 10.0f;
    D_ovl10_06_8004B930[0] = (f32) D_ovl10_06_8004ADD0[0]->unk40->unk10;
    D_ovl10_06_8004B930[2] = (f32) D_ovl10_06_8004ADD0[0]->unk40->unk18;
    D_ovl10_06_8004B9A4 = NULL;
}

void func_ovl10_06_80046BC4(void) {
    func_ovl10_06_800430A8(func_ovl10_06_800479B8);
    D_ovl10_06_8004B7EC = 0x78;
}

s32 func_ovl10_06_80046B58(s32 arg0) {
    s32 slot;

    slot = func_ovl10_06_800430A8(func_ovl10_06_80047634);
    D_ovl10_06_8004B3D0[slot] = arg0;
    D_ovl10_06_8004B4D0[slot] = 0;
    D_ovl10_06_8004B5D0[slot] = 0;
    D_ovl10_06_8004B9B0[slot] = D_ovl10_06_8004ADD0[arg0];
    return slot;
}

void func_ovl10_06_80046A04(void) {
    s32 sp30;
    s32 *sp24;
    s32 *temp_s0;
    s32 *temp_v1;
    s32 temp_t8;
    s32 var_t3;
    s32 var_t4;
    s32 var_t5;
    s32 var_t8;
    s32 var_v0;

    temp_t8 = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8] * 4;
    temp_s0 = (s32 *)((u8 *)D_ovl10_06_8004B3A0 + temp_t8);
    var_v0 = *temp_s0;
    sp30 = temp_t8;
    if (var_v0 & 1) {
        func_ovl10_06_8004683C();
        var_v0 = *temp_s0;
    }
    var_t3 = var_v0 & 8;
    if (var_v0 & 2) {
        func_ovl10_06_800465F4();
        var_v0 = *temp_s0;
        var_t3 = var_v0 & 8;
    }
    var_t4 = var_v0 & 0x20;
    if (var_t3 != 0) {
        func_ovl10_06_80046478();
        var_v0 = *temp_s0;
        var_t4 = var_v0 & 0x20;
    }
    var_t5 = var_v0 & 0x10;
    if (var_t4 != 0) {
        func_ovl10_06_800463C0();
        var_v0 = *temp_s0;
        var_t5 = var_v0 & 0x10;
    }
    var_t8 = var_v0 & 0x40;
    if (var_t5 != 0) {
        func_ovl10_06_800460C8();
        var_v0 = *temp_s0 & ~0x10;
        *temp_s0 = var_v0;
        var_t8 = var_v0 & 0x40;
    }
    if (var_t8 != 0) {
        temp_v1 = (s32 *)((u8 *)D_ovl10_06_8004B390 + sp30);
        if ((*temp_v1 == 0xF0) && (temp_v1 != D_ovl10_06_8004B390)) {
            *temp_s0 = var_v0 | 1;
            sp24 = temp_v1;
            func_ovl10_06_80045F9C();
        }
        sp24 = temp_v1;
        func_ovl10_06_80045CE4();
        var_v0 = *temp_s0;
        *temp_v1 += 1;
    }
    if (var_v0 & 0x80) {
        func_ovl10_06_80045888();
    }
}

void func_ovl10_06_8004683C(void) {
    Vec3f pos;
    Vec3f target;
    f32 ang[2];
    f32 diff;
    f32 step;
    f32 a;
    s32 i;

    i = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8];
    func_ovl10_06_8004A068(D_ovl10_06_8004ADC0[i], &pos);
    func_ovl10_06_8004A068(D_ovl10_06_8004ADBC, &target);
    func_ovl10_06_80049F28(&pos.x, &target.x, ang);
    diff = ang[0] - D_ovl10_06_8004ADC0[i]->unk40->unk20;
    if (diff >= 180.0f) {
        diff -= 360.0f;
    }
    if (diff <= -180.0f) {
        diff += 360.0f;
    }
    a = diff;
    step = 0.7f;
    if (diff < 0.0f) {
        step = -0.7f;
        a = -diff;
    }
    if (a < 0.7f) {
        step = diff;
    }
    D_ovl10_06_8004ADC0[i]->unk40->unk20 += step;
    if (D_ovl10_06_8004ADC0[i]->unk40->unk20 >= 360.0f) {
        D_ovl10_06_8004ADC0[i]->unk40->unk20 -= 360.0f;
    }
    if (D_ovl10_06_8004ADC0[i]->unk40->unk20 < 0.0f) {
        D_ovl10_06_8004ADC0[i]->unk40->unk20 += 360.0f;
    }
    if (D_ovl10_06_8004B3A0[i] & 4) {
        if (--D_ovl10_06_8004B260[i] == 0 || diff == 0.0f) {
            D_ovl10_06_8004B3A0[i] &= ~4;
            func_ovl10_06_800466C4();
        }
    }
}

void func_ovl10_06_800466C4(void) {
    Vec3f pos;
    Vec3f from;
    Vec3f to;
    Vec3f pos2;
    f32 ang[2];
    f32 ang2[2];
    s32 i;

    i = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8];
    D_ovl10_06_8004B3A0[i] &= ~1;
    D_ovl10_06_8004B3A0[i] |= 8;
    func_ovl10_06_80049F70(D_ovl10_06_8004ADE8[i]);
    func_ovl10_06_8004A068(D_ovl10_06_8004ADE8[i], &pos);
    func_ovl10_06_8004A068(D_ovl10_06_8004ADC0[i], &from);
    func_ovl10_06_80049F28(&from.x, &pos.x, ang);
    func_ovl10_06_8004A068(D_ovl10_06_8004ADBC, &to);
    to.y = pos.y;
    func_ovl10_06_80049F28(&pos.x, &to.x, ang2);
    D_ovl10_06_8004AF78[i] = func_ovl10_06_8004A290(ang[0]);
    D_ovl10_06_8004AF88[i] = (from.y - pos.y) / ang2[1];
    D_ovl10_06_8004AF98[i] = func_ovl10_06_8004A298(ang[0]);
    func_ovl10_06_80049F98(D_ovl10_06_8004ADE8[i], 0x40);
    func_ovl10_06_80049FA0(D_ovl10_06_8004ADE8[i], 0x40000);
    D_ovl10_06_8004ADE8[i]->unk30 = 1;
    D_ovl10_06_8004ADE8[i]->unk34 = 65.0f;
    D_ovl10_06_8004ADE8[i]->unk38 = 0.0f;
    func_ovl10_06_8004A068(D_ovl10_06_8004ADE8[i], &pos2);
    func_ovl10_06_8004A698(0x99, &pos2.x);
}

void func_ovl10_06_800465F4(void) {
    s32 *temp_a2;
    s32 *temp_v0;
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_v1;
    void **temp_a0;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;

    temp_v1 = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8] * 4;
    temp_a0 = (UnkStructA * *)((u8 *)D_ovl10_06_8004ADE8 + temp_v1);
    temp_a1 = (*(void **)((u8 *)(*temp_a0) + 64));
    (*(f32 *)((u8 *)(temp_a1) + 40)) = (f32) ((*(f32 *)((u8 *)(temp_a1) + 40)) + 0.0083f);
    temp_a2 = (s32 *)((u8 *)D_ovl10_06_8004B220 + temp_v1);
    temp_a1_2 = (*(void **)((u8 *)(*temp_a0) + 64));
    temp_v0 = (s32 *)((u8 *)D_ovl10_06_8004B3A0 + temp_v1);
    (*(f32 *)((u8 *)(temp_a1_2) + 44)) = (f32) ((*(f32 *)((u8 *)(temp_a1_2) + 44)) + 0.0083f);
    temp_a1_3 = (*(void **)((u8 *)(*temp_a0) + 64));
    (*(f32 *)((u8 *)(temp_a1_3) + 48)) = (f32) ((*(f32 *)((u8 *)(temp_a1_3) + 48)) + 0.0083f);
    temp_t4 = *temp_a2 - 1;
    *temp_a2 = temp_t4;
    if (temp_t4 == 0) {
        temp_t8 = *temp_v0 & ~2;
        *temp_v0 = temp_t8;
        *temp_v0 = temp_t8 | 4;
        *(s32 *)((u8 *)D_ovl10_06_8004B260 + temp_v1) = 0x78;
    }
}

void func_ovl10_06_80046478(void) {
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;
    UnkStructA **temp_s0;
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    f32 temp_fv0;
    f32 var_fv1;
    s32 *temp_v0_4;
    s32 temp_s1;

    temp_s1 = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8] * 4;
    temp_s0 = (UnkStructA * *)((u8 *)D_ovl10_06_8004ADE8 + temp_s1);
    func_ovl10_06_8004A068(*temp_s0, &sp4C);
    func_ovl10_06_8004A068(D_ovl10_06_8004ADBC, &sp40);
    temp_fv0 = func_ovl10_06_80049F40(&sp4C, &sp40);
    var_fv1 = 17.0f;
    if (temp_fv0 < 17.0f) {
        var_fv1 = temp_fv0;
    }
    temp_v0 = (*temp_s0)->unk40;
    temp_v0->unk10 += var_fv1 * *(f32 *)((u8 *)D_ovl10_06_8004AF78 + temp_s1);
    temp_v0_2 = (*temp_s0)->unk40;
    temp_v0_2->unk14 += var_fv1 * *(f32 *)((u8 *)D_ovl10_06_8004AF88 + temp_s1);
    temp_v0_3 = (*temp_s0)->unk40;
    temp_v0_3->unk18 += var_fv1 * *(f32 *)((u8 *)D_ovl10_06_8004AF98 + temp_s1);
    if ((func_ovl10_06_80049F48(*temp_s0, 0x10) != 0) || ((*temp_s0)->unk40->unk14 <= 0.0f)) {
        func_ovl10_06_8004A068(*temp_s0, &sp34);
        temp_v0_4 = (s32 *)((u8 *)D_ovl10_06_8004B3A0 + temp_s1);
        *temp_v0_4 &= ~8;
        func_ovl10_06_80049FB0(*temp_s0);
        *temp_s0 = NULL;
        *(s32 *)((u8 *)D_ovl10_06_8004B390 + temp_s1) = 0;
    }
}

void func_ovl10_06_800463C0(void) {
    s32 sp18;
    UnkStructA *temp_a0_2;
    s32 *temp_a0;
    s32 *temp_v0;
    s32 temp_a2;
    s32 temp_t2;
    s32 temp_t9;
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8];
    temp_a2 = temp_v1 * 4;
    temp_a0 = (s32 *)((u8 *)D_ovl10_06_8004B270 + temp_a2);
    var_v0 = *temp_a0;
    if (var_v0 > 0) {
        temp_t9 = var_v0 - 1;
        *temp_a0 = temp_t9;
        var_v0 = temp_t9;
    }
    if (var_v0 == 0) {
        temp_a0_2 = *(UnkStructA * *)((u8 *)D_ovl10_06_8004ADC0 + temp_a2);
        if (temp_a0_2 != NULL) {
            sp18 = temp_a2;
            func_ovl10_06_80049FA0(temp_a0_2, 0x40000);
            func_ovl10_06_80049FA0(D_ovl10_06_8004ADD0[temp_v1], 0x40000);
            temp_v0 = (s32 *)((u8 *)D_ovl10_06_8004B3A0 + temp_a2);
            temp_t2 = *temp_v0 & ~0x20;
            *temp_v0 = temp_t2;
            *temp_v0 = temp_t2 | 0x40;
        }
    }
}

void func_ovl10_06_800460C8(void) {
    f32 x[3] = { 5800.0f, 5600.0f, 5600.0f };
    f32 y[3] = { 400.0f, 400.0f, 400.0f };
    f32 z[3] = { 1500.0f, 1000.0f, 2000.0f };
    f32 model[3] = { 175.0f, 173.0f, 173.0f };
    f32 model2[3] = { 177.0f, 181.0f, 181.0f };
    s32 slot;
    Vec3f pos;
    s32 i;

    i = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8];
    D_ovl10_06_8004ADC0[i] = func_ovl10_06_80049FC0(model[i], 0x01002070, 0x20, 0);
    D_ovl10_06_8004ADC0[i]->unk40->unk10 = x[i];
    D_ovl10_06_8004ADC0[i]->unk40->unk14 = y[i];
    D_ovl10_06_8004ADC0[i]->unk40->unk18 = z[i];
    D_ovl10_06_8004ADC0[i]->unk40->unk20 = 270.0f;
    D_ovl10_06_8004ADC0[i]->unk30 = 1;
    D_ovl10_06_8004ADC0[i]->unk34 = 250.0f;
    D_ovl10_06_8004ADC0[i]->unk38 = 0.0f;
    D_ovl10_06_8004AF58[i] = (D_ovl10_06_8004A93C[i] - x[i]) / 180.0f;
    D_ovl10_06_8004AF68[i] = (D_ovl10_06_8004A948[i] - y[i]) / 150.0f;
    D_ovl10_06_8004B210[i] = 0;
    slot = func_ovl10_06_800430A8(func_ovl10_06_80046D74);
    D_ovl10_06_8004ADD0[i] = func_ovl10_06_80049FF0(model2[i], 0x01200000, D_ovl10_06_8004ADC0[i]);
    D_ovl10_06_8004ADD0[i]->unk4C = 0.0f;
    D_ovl10_06_8004ADD0[i]->unk50 = 250.0f;
    D_ovl10_06_8004ADD0[i]->unk54 = 0.0f;
    D_ovl10_06_8004ADD0[i]->unk40->unk20 = 270.0f;
    D_ovl10_06_8004B290[slot] = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8];
    D_ovl10_06_8004B230[i] = 4;
    func_ovl10_06_8004A068(D_ovl10_06_8004ADC0[i], &pos);
    func_ovl10_06_8004A698(0x9B, &pos.x);
}

void func_ovl10_06_80045F9C(void) {
    s32 sp1C;
    UnkStructA **temp_v1;
    UnkStructA *temp_v0_2;
    UnkStructA *temp_v0_3;
    s32 *temp_v0;
    s32 temp_t0;

    temp_t0 = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8] * 4;
    temp_v0 = (s32 *)((u8 *)D_ovl10_06_8004B3A0 + temp_t0);
    *temp_v0 |= 2;
    sp1C = temp_t0;
    temp_v0_2 = func_ovl10_06_80049FC0(0xAE, 0x016C0000, 0x20, *(UnkStructA * *)((u8 *)D_ovl10_06_8004ADC0 + temp_t0));
    temp_v1 = (UnkStructA * *)((u8 *)D_ovl10_06_8004ADE8 + temp_t0);
    *temp_v1 = temp_v0_2;
    temp_v0_2->unk4C = 40.0f;
    (*temp_v1)->unk50 = 230.0f;
    (*temp_v1)->unk54 = 400.0f;
    (*temp_v1)->unk40->unk28 = 0.3f;
    (*temp_v1)->unk40->unk2C = 0.3f;
    (*temp_v1)->unk40->unk30 = 0.3f;
    temp_v0_3 = func_ovl10_06_80049FD0(*temp_v1);
    temp_v0_3->unk4C = 2.0f;
    temp_v0_3->unk54 = 2.0f;
    *(s32 *)((u8 *)D_ovl10_06_8004B220 + temp_t0) = 0x78;
    func_ovl10_06_8004A670(0xA6);
}

void func_ovl10_06_80045CE4(void) {
    s32 sp4C;
    UnkStructA **sp2C;
    s32 *sp28;
    UnkStructA **sp20;
    UnkStructA **temp_a1;
    UnkStructA **temp_a1_2;
    UnkStructA **temp_v1;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *temp_v1_4;
    s32 *var_v1;
    s32 temp_s0;
    s32 temp_t1;
    s32 temp_t5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a2;
    s32 var_a2_2;

    temp_v0 = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8];
    temp_s0 = temp_v0 * 4;
    temp_v1 = (UnkStructA * *)((u8 *)D_ovl10_06_8004ADC0 + temp_s0);
    sp2C = temp_v1;
    sp4C = 0;
    temp_v0_2 = func_ovl10_06_80049F48(*temp_v1, 0x40);
    var_a2 = sp4C;
    if (temp_v0_2 != 0) {
        if (temp_v0_2 & 0x4000) {
            temp_v1_2 = (s32 *)((u8 *)D_ovl10_06_8004B230 + temp_s0);
            var_a2 = 1;
            *temp_v1_2 -= 1;
        }
        temp_v1_3 = (s32 *)((u8 *)D_ovl10_06_8004B230 + temp_s0);
        if (temp_v0_2 & 0x2000) {
            var_a2 = 1;
            *temp_v1_3 -= 1;
        }
        if (*temp_v1_3 <= 0) {
            var_v1 = (s32 *)((u8 *)D_ovl10_06_8004B3A0 + temp_s0);
            var_a2_2 = *var_v1;
            if (var_a2_2 & 2) {
                temp_a1 = (UnkStructA * *)((u8 *)D_ovl10_06_8004ADE8 + temp_s0);
                *var_v1 = var_a2_2 & ~2;
                sp20 = temp_a1;
                sp28 = var_v1;
                func_ovl10_06_80049FB0(*temp_a1);
                var_a2_2 = *var_v1;
                *temp_a1 = NULL;
            }
            if (var_a2_2 & 4) {
                temp_a1_2 = (UnkStructA * *)((u8 *)D_ovl10_06_8004ADE8 + temp_s0);
                *var_v1 = var_a2_2 & ~4;
                sp20 = temp_a1_2;
                sp28 = var_v1;
                func_ovl10_06_80049FB0(*temp_a1_2);
                var_a2_2 = *var_v1;
                *temp_a1_2 = NULL;
            }
            temp_t5 = var_a2_2 & ~0x41;
            *var_v1 = temp_t5;
            *var_v1 = temp_t5 | 0x80;
            if (var_v1 == D_ovl10_06_8004B3A0) {
                if (D_ovl10_06_8004B3AC & 4) {
                    D_ovl10_06_8004B3AC &= ~4;
                }
                if (D_ovl10_06_8004B9A4 != NULL) {
                    func_ovl10_06_80049FB0(D_ovl10_06_8004B9A4);
                    D_ovl10_06_8004B9A4 = NULL;
                }
                D_ovl10_06_8004B3AC = 0;
                D_ovl10_06_8004ACB0[func_ovl10_06_80045C20(func_ovl10_06_80047E10)] = NULL;
                D_ovl10_06_8004ACB0[func_ovl10_06_80045C20(func_ovl10_06_80047B0C)] = NULL;
            }
            D_ovl10_06_8004AFA4 = 2.1333334f;
            *(s32 *)((u8 *)D_ovl10_06_8004B7D8 + temp_s0) = 0x3C;
            func_ovl10_06_80049F98(*sp2C, 0x80000);
            func_ovl10_06_80049F98(D_ovl10_06_8004ADD0[temp_v0], 0x80000);
            (*sp2C)->unk40->unk36 = 0x80;
            *(f32 *)((u8 *)D_ovl10_06_8004AFF8 + temp_s0) = 128.0f;
            return;
        }
        if (var_a2 == 1) {
            temp_v1_4 = (s32 *)((u8 *)D_ovl10_06_8004B3A0 + temp_s0);
            temp_t1 = *temp_v1_4 | 0x20;
            *temp_v1_4 = temp_t1;
            *temp_v1_4 = temp_t1 & ~0x40;
            func_ovl10_06_80049F98(*sp2C, 0x40000);
            func_ovl10_06_80049F98(D_ovl10_06_8004ADD0[temp_v0], 0x40000);
            *(s32 *)((u8 *)D_ovl10_06_8004B270 + temp_s0) = 0x78;
        }
    }
}

void func_ovl10_06_80045C90(void) {
    if (D_ovl10_06_8004B9A4 != NULL) {
        func_ovl10_06_80049FB0(D_ovl10_06_8004B9A4);
        D_ovl10_06_8004B9A4 = NULL;
    }
    D_ovl10_06_8004B3AC = 0;
    D_ovl10_06_8004ACB0[func_ovl10_06_80045C20(func_ovl10_06_80047E10)] = NULL;
}

/* ovl_10_13's 80046DAC */
void func_ovl10_06_80045C64(void (*arg0)()) {
    D_ovl10_06_8004ACB0[func_ovl10_06_80045C20(arg0)] = NULL;
}

/* ovl_10_13's 80046D68 */
s32 func_ovl10_06_80045C20(void (*arg0)()) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_06_8004ACB0[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_06_80045888(void) {
    s32 i;
    s32 r;
    s32 pad;
    s32 effects[10] = { 12, 13, 14, 15, 16, 19, 20, 22, 23, 24 };
    Vec3f ang;
    Vec3f pos;
    s32 pad2[7];

    i = D_ovl10_06_8004B290[D_ovl10_06_8004ACA8];
    D_ovl10_06_8004B7D8[i]--;
    D_ovl10_06_8004AFF8[i] -= D_ovl10_06_8004AFA4;
    D_ovl10_06_8004ADC0[i]->unk40->unk36 = D_ovl10_06_8004AFF8[i];
    D_ovl10_06_8004ADD0[i]->unk40->unk36 = D_ovl10_06_8004AFF8[i];
    ang.z = (f32)func_ovl10_06_8004A2A0() * 250.0f;
    ang.x = (f32)func_ovl10_06_8004A2A0() * 360.0f;
    ang.y = (f32)func_ovl10_06_8004A2A0() * 360.0f;
    r = func_ovl10_06_8004A2A8(9);
    func_ovl10_06_80049F30(&ang.x, &pos.x);
    pos.x += D_ovl10_06_8004ADC0[i]->unk40->unk10;
    pos.y += D_ovl10_06_8004ADC0[i]->unk40->unk14 + 200.0f;
    pos.z += D_ovl10_06_8004ADC0[i]->unk40->unk18;
    if (D_ovl10_06_8004B7D8[i] % 10 == 0) {
        func_ovl10_06_8004A540(effects[r], &pos.x, 0);
        func_ovl10_06_8004A068(D_ovl10_06_8004ADC0[i], &pos);
        if (func_ovl10_06_8004A2A8(1) != 0) {
            func_ovl10_06_8004A698(0xC9, &pos.x);
        } else {
            func_ovl10_06_8004A698(0xC7, &pos.x);
        }
    }
    if (D_ovl10_06_8004B7D8[i] == 0) {
        D_ovl10_06_8004B3A0[i] &= ~0x80;
        func_ovl10_06_80049FB0(D_ovl10_06_8004ADC0[i]);
        D_ovl10_06_8004ADD0[i] = NULL;
        D_ovl10_06_8004ADC0[i] = NULL;
        D_ovl10_06_8004ACB0[D_ovl10_06_8004B3C0[D_ovl10_06_8004B290[D_ovl10_06_8004ACA8]]] = NULL;
        if (--D_ovl10_06_8004B240[i] != 0) {
            D_ovl10_06_8004B3A0[i] |= 0x30;
            D_ovl10_06_8004B270[i] = -1;
            return;
        }
        if (D_ovl10_06_8004B240[0] == 0 && D_ovl10_06_8004B240[1] == 0 && D_ovl10_06_8004B240[2] == 0) {
            func_ovl10_06_80049700(0);
            func_ovl10_06_800430A8(func_ovl10_06_800452EC);
            func_ovl10_06_8004A360(0x401);
        }
        D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    }
}

void func_ovl10_06_8004584C(void) {
    D_ovl10_06_8004ACB0[D_ovl10_06_8004B3C0[D_ovl10_06_8004B290[D_ovl10_06_8004ACA8]]] = NULL;
}

/* ovl_10_13's 80046D38 */
void func_ovl10_06_80045838(s32 arg0) {
    D_ovl10_06_8004ACB0[arg0] = NULL;
}

void func_ovl10_06_800457C0(void) {
    func_ovl10_06_80049E40(0x1F);
    if (func_ovl10_06_80049E28() & 1) {
        func_ovl10_06_80049E30();
    }
    func_ovl10_06_80049700(0);
    func_ovl10_06_80049708(1);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x1E;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80045754;
}

void func_ovl10_06_80045754(void) {
    func_ovl10_06_80044F8C(0xA);
    func_ovl10_06_80049EC0(10.0f, 10.0f, 10.0f);
    func_ovl10_06_80049EB0(0x3C);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x5A;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_800456D4;
}

void func_ovl10_06_800456D4(void) {
    func_ovl10_06_80049E50(2);
    func_ovl10_06_80049DD8(2700.0f, 400.0f, 1500.0f);
    func_ovl10_06_80049DF8(270.0f, 45.0f, 4000.0f);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0xB4;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_800455EC;
}

void func_ovl10_06_800455EC(void) {
    s32 var_s1;
    s32 var_s2;
    void **var_s0;

    var_s2 = 0;
    if (D_ovl10_06_8004B7F4 > 0) {
        var_s0 = D_ovl10_06_8004B990;
        var_s1 = 0;
        do {
            if (*var_s0 != NULL) {
                func_ovl10_06_80049FB0(*(UnkStructA * *)((u8 *)D_ovl10_06_8004ADE0 + var_s1));
                *var_s0 = NULL;
            }
            var_s2 += 1;
            var_s1 += 4;
            var_s0 += 1;
        } while (var_s2 < D_ovl10_06_8004B7F4);
    }
    func_ovl10_06_80049EC0(10.0f, 10.0f, 10.0f);
    func_ovl10_06_80049EB0(0x3C);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x3C;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80045598;
}

/* ovl_10_10's 80044508 */
void func_ovl10_06_80045598(void) {
    func_ovl10_06_80044BCC(60.0f);
    func_ovl10_06_80043A4C(60);
    func_ovl10_06_80043A30(func_ovl10_06_80045518);
}

void func_ovl10_06_80045518(void) {
    s32 i;

    D_ovl10_06_8004B21C = 0;
    for (i = 0; i < 3; i++) {
        D_ovl10_06_8004B240[i] = 0;
    }
    func_ovl10_06_80045458(0);
    func_ovl10_06_80045458(1);
    func_ovl10_06_80045458(2);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x14A;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_800453A0;
}

void func_ovl10_06_80045458(s32 arg0) {
    s32 sp1C;
    s32 *sp18;
    s32 *temp_a0;
    s32 *temp_v0;
    s32 temp_v1;

    D_ovl10_06_8004B290[func_ovl10_06_800430A8(func_ovl10_06_80046A04)] = arg0;
    temp_v1 = arg0 * 4;
    *(s32 *)((u8 *)D_ovl10_06_8004B390 + temp_v1) = 0;
    *(s32 *)((u8 *)D_ovl10_06_8004B3A0 + temp_v1) = 0x30;
    *(s32 *)((u8 *)D_ovl10_06_8004B270 + temp_v1) = -1;
    temp_a0 = (s32 *)((u8 *)D_ovl10_06_8004B240 + temp_v1);
    *temp_a0 = 1;
    sp18 = temp_a0;
    sp1C = temp_v1;
    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
        if (D_ovl10_06_8004ADB4[4] != 0) {
        *temp_a0 += 2;
    }
    *(s32 *)((u8 *)D_ovl10_06_8004B250 + temp_v1) = 0;
}

void func_ovl10_06_800453A0(void) {
    s32 *temp_v0;

    func_ovl10_06_8004A670(0xA3);
    func_ovl10_06_80049E38(0x1F);
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    func_ovl10_06_800495D0(0x2A, 1, 0xE, 1);
    func_ovl10_06_800495D0(0x2A, 1, 0x10, 1);
    func_ovl10_06_80049708(0);
    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
        if (!(*D_ovl10_06_8004ADB4 & 2)) {
        func_ovl10_06_80049788(0);
        func_ovl10_06_80049700(1);
        return;
    }
    func_ovl10_06_800497E0(1);
}

void func_ovl10_06_800452EC(void) {
    func_ovl10_06_80049E40(0x1F);
    if (func_ovl10_06_80049E28() & 1) {
        func_ovl10_06_80049E30();
    }
    func_ovl10_06_80049708(1);
    func_ovl10_06_80049700(0);
    func_ovl10_06_8004A160(0x150, 0x150);
    func_ovl10_06_800497E0(1);
    func_ovl10_06_80049EF8();
    func_ovl10_06_80049EC0(10.0f, 10.0f, 10.0f);
    func_ovl10_06_80049EB0(0x5A);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x5A;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_8004526C;
}

void func_ovl10_06_8004526C(void) {
    func_ovl10_06_80049DD8(2700.0f, 400.0f, 1500.0f);
    func_ovl10_06_80049DF8(270.0f, 45.0f, 4000.0f);
    func_ovl10_06_80044F8C(8);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0xD2;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80044CAC;
}

void func_ovl10_06_80044F8C(s32 arg0) {
    Vec3f pos;
    s32 i;

    func_ovl10_06_80049648(0x1D, 1, 8, 0x26, 0x16, 1);
    func_ovl10_06_800495D0(0x27, 1, 0xD, 1);
    func_ovl10_06_800495D0(0x27, 1, 0xE, 1);
    func_ovl10_06_800495D0(0x27, 1, 0xF, 1);
    func_ovl10_06_800495D0(0x27, 1, 0x10, 1);
    func_ovl10_06_800495D0(0x27, 1, 0x11, 1);
    func_ovl10_06_800495D0(0x28, 1, 0xE, 1);
    func_ovl10_06_800495D0(0x28, 1, 0xF, 1);
    func_ovl10_06_800495D0(0x28, 1, 0x10, 1);
    D_ovl10_06_8004ADBC = func_ovl10_06_800497D8(func_ovl10_06_80049778());
    D_ovl10_06_8004B27C = arg0;
    if (arg0 == 10) {
        D_ovl10_06_8004AF30 = D_ovl10_06_8004ADB8->unk40->unk14 - 200.0f;
    } else {
        D_ovl10_06_8004AF30 = D_ovl10_06_8004ADB8->unk40->unk14 + 200.0f;
    }
    D_ovl10_06_8004AF2C = (D_ovl10_06_8004AF30 - D_ovl10_06_8004ADB8->unk40->unk14) / 270.0f;
    func_ovl10_06_800430A8(func_ovl10_06_800489FC);
    func_ovl10_06_80049650(1);
    func_ovl10_06_80044EFC();
    func_ovl10_06_80044D00();
    for (i = 0; i < D_ovl10_06_8004B7F4; i++) {
        if (D_ovl10_06_8004B990[i] != NULL) {
            D_ovl10_06_8004ADE0[i] = func_ovl10_06_80049FC0(0xA6, 0x01000000, 0xD0, 0);
            func_ovl10_06_800495F8(D_ovl10_06_8004B990[i]->unk1C, D_ovl10_06_8004B990[i]->unk20, D_ovl10_06_8004B990[i]->unk24,
                                   &pos.x, 0);
            D_ovl10_06_8004ADE0[i]->unk40->unk10 = pos.x;
            D_ovl10_06_8004ADE0[i]->unk40->unk14 = pos.y;
            D_ovl10_06_8004ADE0[i]->unk40->unk18 = pos.z;
            D_ovl10_06_8004B990[i]->unk20 = -1.0f;
        } else {
            D_ovl10_06_8004ADE0[i] = NULL;
        }
    }
    func_ovl10_06_8004A158(0xB0, 0xB0, 0);
    func_ovl10_06_8004A158(0x50, 0x50, 0);
    func_ovl10_06_8004A670(0x9C);
}

void func_ovl10_06_80044EFC(void) {
    UnkStruct_ovl10_06_8004A460 *p;
    s32 n;

    for (n = 0; n < 2; n++) {
        D_ovl10_06_8004B990[n] = NULL;
    }
    n = 0;
    for (p = func_ovl10_06_8004A460(); p != NULL; p = p->unk4) {
        if (p->unk1C == 24.0f) {
            D_ovl10_06_8004B990[n] = p;
            n++;
        }
    }
    D_ovl10_06_8004B7F4 = n;
}

void func_ovl10_06_80044D00(void) {
    UnkStructA *e;
    UnkStructA *list[72];
    s32 n;
    s32 i;
    Vec3f a;
    Vec3f b;
    f32 x;
    f32 y;
    f32 z;

    a.x = 2000.0f;
    a.y = 0.0f;
    a.z = 800.0f;
    b.x = 3900.0f;
    b.y = D_ovl10_06_8004ADB8->unk40->unk14 + 600.0f;
    b.z = 2200.0f;
    n = func_ovl10_06_8004A0C0(0xF, &a, &b, list, 0x48);
    D_ovl10_06_8004B7D0 = 0;
    for (i = 0; i < n; i++) {
        e = list[i];
        x = e->unk40->unk10;
        y = e->unk40->unk14;
        z = e->unk40->unk18;
        if (e != NULL && *(s32 *)e->unk44 == 0 && (func_ovl10_06_80049628(x, y, z) & 0xF) == 1) {
            D_ovl10_06_8004ADF8[D_ovl10_06_8004B7D0] = e;
            func_ovl10_06_80049F78(D_ovl10_06_8004ADB8, e);
            func_ovl10_06_80049F98(e, 0x200000);
            e->unk4C = e->unk40->unk10 - D_ovl10_06_8004ADB8->unk40->unk10;
            e->unk50 = e->unk40->unk14 - D_ovl10_06_8004ADB8->unk40->unk14;
            e->unk54 = e->unk40->unk18 - D_ovl10_06_8004ADB8->unk40->unk18;
            D_ovl10_06_8004B7D0++;
        }
    }
}

void func_ovl10_06_80044CAC(void) {
    func_ovl10_06_80044BCC(60.0f);
    func_ovl10_06_80043A4C(60);
    func_ovl10_06_80043A30(func_ovl10_06_80044AE4);
}

void func_ovl10_06_80044BCC(f32 arg0) {
    D_ovl10_06_8004AF34 = 45.0f;
    D_ovl10_06_8004AF38 = 25.0f;
    D_ovl10_06_8004AF44 = 4000.0f;
    D_ovl10_06_8004AF48 = 3200.0f;
    D_ovl10_06_8004AF50 = 4000.0f;
    D_ovl10_06_8004AF4C = 2700.0f;
    D_ovl10_06_8004AF3C = (D_ovl10_06_8004AF38 - D_ovl10_06_8004AF34) / arg0;
    D_ovl10_06_8004AF40 = (D_ovl10_06_8004AF48 - D_ovl10_06_8004AF44) / arg0;
    D_ovl10_06_8004AF54 = (D_ovl10_06_8004AF50 - D_ovl10_06_8004AF4C) / arg0;
    func_ovl10_06_800430A8(func_ovl10_06_8004870C);
}

void func_ovl10_06_80044AE4(void) {
    s32 var_s1;
    s32 var_s2;
    void **var_s0;

    var_s2 = 0;
    if (D_ovl10_06_8004B7F4 > 0) {
        var_s0 = D_ovl10_06_8004B990;
        var_s1 = 0;
        do {
            if (*var_s0 != NULL) {
                func_ovl10_06_80049FB0(*(UnkStructA * *)((u8 *)D_ovl10_06_8004ADE0 + var_s1));
                *var_s0 = NULL;
            }
            var_s2 += 1;
            var_s1 += 4;
            var_s0 += 1;
        } while (var_s2 < D_ovl10_06_8004B7F4);
    }
    func_ovl10_06_80049EC0(10.0f, 10.0f, 10.0f);
    func_ovl10_06_80049EB0(0x3C);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x3C;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80044A54;
}

void func_ovl10_06_80044A54(void) {
    Vec3f sp2C;

    func_ovl10_06_800495F8(44.0f, 1.0f, 15.0f, &sp2C.x, 0);
    func_ovl10_06_80049DD8(sp2C.x, sp2C.y, sp2C.z);
    func_ovl10_06_80049DF8(270.0f, 45.0f, 2000.0f);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x5A;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_800449BC;
}

void func_ovl10_06_800449BC(void) {
    func_ovl10_06_8004355C(0x28, 0x2C, 1, 0xF);
    func_ovl10_06_8004A670(0x2C);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x78;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80044920;
}

void func_ovl10_06_80044920(void) {
    func_ovl10_06_80049E38(0x1F);
    func_ovl10_06_80049F00();
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
    func_ovl10_06_80049708(0);
    if (!(*D_ovl10_06_8004ADB4 & 2)) {
        func_ovl10_06_80049788(0);
        func_ovl10_06_80049700(1);
    } else {
        func_ovl10_06_800497E0(1);
    }
    func_ovl10_06_800445DC();
}

void func_ovl10_06_800448EC(void) {
    func_ovl10_06_80049700(0);
    func_ovl10_06_800430A8(func_ovl10_06_800452EC);
    func_ovl10_06_8004A360(0x401);
}

void func_ovl10_06_80044804(void) {
    Vec3f sp2C;

    func_ovl10_06_80049E40(0x1F);
    if (func_ovl10_06_80049E28() & 1) {
        func_ovl10_06_80049E30();
    }
    func_ovl10_06_8004A360(0x401);
    func_ovl10_06_80049708(1);
    func_ovl10_06_80049700(0);
    func_ovl10_06_8004A160(0x150, 0x150);
    func_ovl10_06_80049788(1);
    func_ovl10_06_80049EF8();
    func_ovl10_06_800495F8(44.0f, 1.0f, 15.0f, &sp2C.x, 0);
    func_ovl10_06_80049DD8(sp2C.x, sp2C.y, sp2C.z);
    func_ovl10_06_80049DF8(270.0f, 45.0f, 2000.0f);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x5A;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_800449BC;
}

void func_ovl10_06_8004476C(void) {
    func_ovl10_06_8004355C(0x28, 0x2C, 1, 0xF);
    func_ovl10_06_8004A670(0x2C);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x78;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80044920;
}

void func_ovl10_06_800446D0(void) {
    func_ovl10_06_80049E38(0x1F);
    func_ovl10_06_80049F00();
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
    func_ovl10_06_80049708(0);
    if (!(*D_ovl10_06_8004ADB4 & 2)) {
        func_ovl10_06_80049788(0);
        func_ovl10_06_80049700(1);
    } else {
        func_ovl10_06_80049788(1);
    }
    func_ovl10_06_800445DC();
}

void func_ovl10_06_800445DC(void) {
    Vec3f a;
    Vec3f b;
    s32 i;

    a.x = 2000.0f;
    a.y = 0.0f;
    a.z = 800.0f;
    b.x = 3900.0f;
    b.y = D_ovl10_06_8004ADB8->unk40->unk14 + 200.0f;
    b.z = 2200.0f;
    D_ovl10_06_8004B7F0 = func_ovl10_06_8004A0C0(4, &a, &b, D_ovl10_06_8004BAB0, 0x48);
    for (i = 0; i < D_ovl10_06_8004B7F0; i++) {
        func_ovl10_06_8004A068(D_ovl10_06_8004BAB0[i], &a);
        func_ovl10_06_8004A668(&a);
    }
}

void func_ovl10_06_800444F0(void) {
    D_ovl10_06_8004B008 += D_ovl10_06_8004B004;
    if (D_ovl10_06_8004B008 > 360.0f) {
        D_ovl10_06_8004B008 -= 360.0f;
    }
    if (D_ovl10_06_8004B008 < 0.0f) {
        D_ovl10_06_8004B008 += 360.0f;
    }
    if (D_ovl10_06_8004B008 >= 315.0f) {
        if (D_ovl10_06_8004B008 < 316.9f) {
            D_ovl10_06_8004B008 = 315.0f;
            D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
        }
    }
    func_ovl10_06_80049DF8(D_ovl10_06_8004B008, 32768.0f, 32768.0f);
}

void func_ovl10_06_800443DC(void) {
    f32 sp1C;
    f32 var_fv1;

    func_ovl10_06_80049E00(&D_ovl10_06_8004B008, NULL, NULL);
    if ((D_ovl10_06_8004B008 >= 0.0f) && (D_ovl10_06_8004B008 < 135.0f)) {
        sp1C = -45.0f - D_ovl10_06_8004B008;
    }
    var_fv1 = sp1C;
    if (D_ovl10_06_8004B008 >= 135.0f) {
        if (D_ovl10_06_8004B008 < 315.0f) {
            var_fv1 = 315.0f - D_ovl10_06_8004B008;
        }
    }
    D_ovl10_06_8004B004 = var_fv1 / 60.0f;
    if (D_ovl10_06_8004B004 > 2.0f) {
        D_ovl10_06_8004B004 = 2.0f;
    }
    if (D_ovl10_06_8004B004 < -2.0f) {
        D_ovl10_06_8004B004 = -2.0f;
    }
    func_ovl10_06_800430A8(func_ovl10_06_800444F0);
}

void func_ovl10_06_800442D4(void) {
    UnkStructA_40_48_4 *temp_v0;
    f32 temp_fv0;

    temp_v0 = D_ovl10_06_8004AF18->unk40->unk48->unk4;
    temp_v0->unk4 += (f32) D_ovl10_06_8004B7E8;
    temp_fv0 = (f32) D_ovl10_06_8004B7E8;
    if (((temp_fv0 == 1.0f) && (D_ovl10_06_8004AF18->unk40->unk48->unk4->unk4 >= 41.0f)) || ((temp_fv0 == -1.0f) && (D_ovl10_06_8004AF18->unk40->unk48->unk4->unk4 <= 0.0f))) {
        D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    }
}

void func_ovl10_06_8004411C(void) {
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;
    UnkStructA_40 *temp_a0;
    f32 temp_fv1;

    D_ovl10_06_8004B970[2] = (f32) (D_ovl10_06_8004B970[2] + D_ovl10_06_8004B980[2]);
    D_ovl10_06_8004B970[0] = (f32) (D_ovl10_06_8004B970[0] + D_ovl10_06_8004B980[0]);
    D_ovl10_06_8004B970[1] = (f32) (D_ovl10_06_8004B970[1] + D_ovl10_06_8004B980[1]);
    D_ovl10_06_8004B980[2] = (f32) (D_ovl10_06_8004B980[2] + 0.1f);
    D_ovl10_06_8004AF18->unk40->unk20 = D_ovl10_06_8004B970[0] + 18.0f;
    temp_a0 = D_ovl10_06_8004AF18->unk40;
    temp_fv1 = temp_a0->unk20;
    if (temp_fv1 >= 360.0f) {
        temp_a0->unk20 = temp_fv1 - 360.0f;
    }
    if (D_ovl10_06_8004B970[0] < 0.0f) {
        D_ovl10_06_8004B970[0] = (f32) (D_ovl10_06_8004B970[0] + 360.0f);
    }
    if (D_ovl10_06_8004B970[2] <= 0.0f) {
        D_ovl10_06_8004B970[2] = 0.0f;
        D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    }
    sp4C.z = D_ovl10_06_8004B970[2];
    sp4C.x = D_ovl10_06_8004B970[0];
    sp4C.y = D_ovl10_06_8004B970[1];
    func_ovl10_06_80049F30(&sp4C.x, &sp40.x);
    func_ovl10_06_80049780(func_ovl10_06_80049778(), &sp34.x);
    D_ovl10_06_8004AF18->unk40->unk10 = sp40.x + sp34.x + 200.0f;
    D_ovl10_06_8004AF18->unk40->unk14 = sp40.y + sp34.y + 30.0f;
    D_ovl10_06_8004AF18->unk40->unk18 = sp40.z + sp34.z;
}

void func_ovl10_06_80043FF8(void) {
    UnkStructA_40 *temp_v0;
    s32 *temp_v0_2;
    s32 temp_t8;

    func_ovl10_06_8004A018(D_ovl10_06_8004AF18);
    temp_v0 = D_ovl10_06_8004AF18->unk40;
    temp_v0->unk10 += D_ovl10_06_8004B00C;
    temp_t8 = D_ovl10_06_8004B7E4 - 1;
    D_ovl10_06_8004B00C += -1.0f;
    D_ovl10_06_8004B7E4 = temp_t8;
    if (temp_t8 == 0) {
        func_ovl10_06_80049FB0(D_ovl10_06_8004AF18);
        D_ovl10_06_8004AF18 = NULL;
        D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
                if (!(*D_ovl10_06_8004ADB4 & 2)) {
            func_ovl10_06_80049788(0);
            func_ovl10_06_80049700(1);
        }
        if (func_ovl10_06_8004A370(0x401) != 0) {
            func_ovl10_06_80049788(1);
            D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x3C;
            D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80043FAC;
            return;
        }
        D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
    }
}

void func_ovl10_06_80043FAC(void) {
    func_ovl10_06_800497C0(0x20000);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x3C;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80043F50;
}

void func_ovl10_06_80043F50(void) {
    s32 *temp_v0;

    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
        if (!(*D_ovl10_06_8004ADB4 & 2)) {
        func_ovl10_06_80049788(0);
    }
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
}

void func_ovl10_06_80043EA8(void) {
    func_ovl10_06_80049E40(0x1F);
    if (func_ovl10_06_80049E28() & 1) {
        func_ovl10_06_80049E30();
    }
    func_ovl10_06_80049EF8();
    func_ovl10_06_80049DF8(300.0f, 359.0f, 800.0f);
    func_ovl10_06_80049700(0);
    func_ovl10_06_80049708(1);
    func_ovl10_06_80049788(1);
    func_ovl10_06_80043CB0();
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x3C;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80043C64;
}

void func_ovl10_06_80043CB0(void) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3f sp24;
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;

    D_ovl10_06_8004B970[2] = 1000.0f;
    D_ovl10_06_8004B970[0] = 315.0f;
    D_ovl10_06_8004B970[1] = 180.0f;
    D_ovl10_06_8004B980[0] = -1.0f;
    D_ovl10_06_8004B980[1] = -1.0f;
    sp3C.z = D_ovl10_06_8004B970[2];
    sp3C.x = D_ovl10_06_8004B970[0];
    sp3C.y = D_ovl10_06_8004B970[1];
    D_ovl10_06_8004B980[2] = -19.0f;
    func_ovl10_06_80049F30(&sp3C.x, &sp30.x);
    func_ovl10_06_80049780(func_ovl10_06_80049778(), &sp24.x);
    func_ovl10_06_800430A8(func_ovl10_06_8004411C);
    D_ovl10_06_8004AF18 = func_ovl10_06_80049FC0(0x328, 0x01000000, 0xC0, 0);
    D_ovl10_06_8004AF18->unk40->unk10 = sp30.x + sp24.x + 200.0f;
    D_ovl10_06_8004AF18->unk40->unk14 = sp30.y + sp24.y + 500.0f;
    D_ovl10_06_8004AF18->unk40->unk18 = sp30.z + sp24.z;
    D_ovl10_06_8004AF18->unk40->unk20 = 0.0f;
    func_ovl10_06_80049FD0(D_ovl10_06_8004AF18);
    func_ovl10_06_80049CB8(D_ovl10_06_8004AF18->unk40, 1);
    func_ovl10_06_80049CC0(D_ovl10_06_8004AF18->unk40, 0x16, 0);
    temp_v0_2 = D_ovl10_06_8004AF18->unk40;
    temp_v0_2->unkC &= ~0x20;
    temp_v0_3 = D_ovl10_06_8004AF18->unk40;
    temp_v0_3->unkC |= 0x40;
    D_ovl10_06_8004AF18->unk40->unk48->unk4->unk4 = 41.0f;
    (*(s32 *)((u8 *)&D_ovl10_06_8004AF20 + 4)) = 0x213;
    (*(s32 *)((u8 *)&D_ovl10_06_8004AF20 + 8)) = 0x3F;
    (*(UnkStructA_40 **)((u8 *)&D_ovl10_06_8004AF20 + 0)) = (UnkStructA_40 *) D_ovl10_06_8004AF18->unk40;
    func_ovl10_06_8004A0E0(&D_ovl10_06_8004AF20);
}

void func_ovl10_06_80043C64(void) {
    func_ovl10_06_80043B38(1);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x50;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80043B94;
}

void func_ovl10_06_80043B94(void) {
    s32 *temp_v0;

    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
        if (!(*D_ovl10_06_8004ADB4 & 2)) {
        if (func_ovl10_06_8004A350(0xA4) != 0) {
            func_ovl10_06_80049D00(0x291, 1);
        } else {
            func_ovl10_06_80049D00(0xCD, 2);
        }
    } else {
        func_ovl10_06_8004A108(0x3C);
    }
    func_ovl10_06_80049E40(0x1F);
    func_ovl10_06_80049708(1);
    func_ovl10_06_80049700(0);
    func_ovl10_06_80049788(1);
    func_ovl10_06_80043B38(0);
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0xA;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_80043AEC;
}

void func_ovl10_06_80043B38(s32 arg0) {
    Vec3f sp1C;

    D_ovl10_06_8004B7E8 = 1;
    if (arg0 != 0) {
        D_ovl10_06_8004B7E8 = -1;
    }
    func_ovl10_06_800430A8(func_ovl10_06_800442D4);
    func_ovl10_06_8004A068(D_ovl10_06_8004AF18, &sp1C);
    func_ovl10_06_8004A698(0x211, &sp1C.x);
}

void func_ovl10_06_80043AEC(void) {
    func_ovl10_06_80043A68();
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = 0x78;
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = func_ovl10_06_800439DC;
}

void func_ovl10_06_80043A68(void) {
    D_ovl10_06_8004AF18->unk68 = 50.0f;
    func_ovl10_06_800430A8(func_ovl10_06_80043FF8);
    D_ovl10_06_8004B7E4 = 0x78;
    D_ovl10_06_8004B00C = -10.0f;
    (*(s32 *)((u8 *)&D_ovl10_06_8004AF20 + 4)) = 0x20F;
    (*(UnkStructA_40 **)((u8 *)&D_ovl10_06_8004AF20 + 0)) = (UnkStructA_40 *) D_ovl10_06_8004AF18->unk40;
    (*(s32 *)((u8 *)&D_ovl10_06_8004AF20 + 8)) = (s32) D_ovl10_06_8004B7E4;
    func_ovl10_06_8004A0E0(&D_ovl10_06_8004AF20);
}

void func_ovl10_06_80043A4C(s32 arg0) {
    D_ovl10_06_8004ABA8[D_ovl10_06_8004ACA8] = arg0;
}

/* ovl_10_13's 80046D00 */
void func_ovl10_06_80043A30(void (*arg0)()) {
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = arg0;
}

void func_ovl10_06_800439DC(void) {
    func_ovl10_06_80049F00();
    func_ovl10_06_80049E38(0x1F);
    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
    func_ovl10_06_80049708(0);
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
}

void func_ovl10_06_800439C0(void) {
    D_ovl10_06_8004ACB0[D_ovl10_06_8004ACA8] = NULL;
}

void func_ovl10_06_8004396C(UnkStructA *arg0) {
    func_ovl10_06_800496D8(func_ovl10_06_80049778(), 0);
loop_1:
    func_ovl10_06_8004A130();
    goto loop_1;
}

void func_ovl10_06_80043820(s32 arg0) {
    s32 *temp_v0;

    switch (arg0) {                                 /* irregular */
    case 0x2:
        func_ovl10_06_8004368C();
        break;
    case 0x11:
        func_ovl10_06_8004347C();
        break;
    case 0x12:
        func_ovl10_06_80043424();
        break;
    case 0x19:
        func_ovl10_06_80049750(0x11, 1, 0xF);
        func_ovl10_06_80049790(0x40);
        D_ovl10_06_8004B280 = 0;
        break;
    case 0x4:
        func_ovl10_06_800497A8();
        func_ovl10_06_80043338();
        break;
    case 0x50:
        func_ovl10_06_80043278();
        break;
    case 0x52:
        func_ovl10_06_800431C0();
        break;
    case 0x53:
        func_ovl10_06_80043120();
        break;
    case 0x1:
        D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
                if (*D_ovl10_06_8004ADB4 & 2) {
            func_ovl10_06_8004A7F0();
        }
        break;
    }
}

/* ovl_10_13's 80046C70 */
void func_ovl10_06_800435FC(s32 arg0) {
    D_ovl10_06_8004ADB0 = func_ovl10_06_8004A170(arg0);
    func_ovl10_06_8004A180(D_ovl10_06_8004ADB0, 0x20000001);
    D_ovl10_06_8004ADB0->unk40 = 0.5f;
    D_ovl10_06_8004ADB0->unk44 = D_ovl10_06_8004ADB0->unk40 * 0.75f;
    D_ovl10_06_8004ADB0->unk18 = 0.1f;
    D_ovl10_06_8004ADB0->unk1C = -0.1f;
}

/* ovl_10_10's 80043A0C */
static void func_ovl10_06_8004355C(s32 model, s32 x, s32 n, s32 z) {
    s32 i;

    D_ovl10_06_8004AB90.x = x * 100.0f;
    D_ovl10_06_8004AB90.y = 0.0f;
    for (i = 0; i < n; i++) {
        D_ovl10_06_8004AB90.y += func_ovl10_06_80049600(i) * 100.0f;
    }
    D_ovl10_06_8004AB90.y += 100.0f;
    D_ovl10_06_8004AB90.z = z * 100.0f;
    D_ovl10_06_8004AB80 = func_ovl10_06_8004A540(model, &D_ovl10_06_8004AB90.x, 0);
}

/* ovl_10_13's 80046BF4 */
void func_ovl10_06_800434E0(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_06_8004ACB0[i] = NULL;
        D_ovl10_06_8004ABA8[i] = 0;
    }
    func_ovl10_06_8004A0E8(func_ovl10_06_80049020, 0, 0, 0, 0x110);
}

void func_ovl10_06_8004368C(void) {
    UnkStructA *temp_v0;

    func_ovl10_06_8004A450((u32 (*)[3]) D_ovl10_06_8004A918);
    func_ovl10_06_8004A5F8(0, 0, 0xDE);
    func_ovl10_06_8004A5F8(1, 0x11, 0xEF);
    func_ovl10_06_8004A5F8(2, 0x1A, 0xF8);
    func_ovl10_06_8004A5F8(3, 0x1B, 0xF9);
    func_ovl10_06_8004A5F8(4, 0xC, 0xEA);
    func_ovl10_06_8004A5F8(5, 0xC, 0xE0);
    func_ovl10_06_80049598(0x1E0);
    D_ovl10_06_8004ADB8 = func_ovl10_06_80049FC0(0xBC, 0x01000000, 0xD0, 0);
    D_ovl10_06_8004ADB8->unk40->unk10 = 0.0f;
    D_ovl10_06_8004ADB8->unk40->unk14 = 0.0f;
    D_ovl10_06_8004ADB8->unk40->unk18 = 0.0f;
    func_ovl10_06_800435FC(0x1FD);
    func_ovl10_06_800495B0(0x1E6);
    func_ovl10_06_80049660(0xF);
    D_ovl10_06_8004B284 = func_ovl10_06_80049668(0x1E7);
    D_ovl10_06_8004B288 = func_ovl10_06_80049668(0x1E8);
    func_ovl10_06_80049748();
    func_ovl10_06_800496D0(func_ovl10_06_8004396C);
    if (func_ovl10_06_8004A370(0x401) != 0) {
        func_ovl10_06_8004355C(0x28, 0x2C, 1, 0xF);
    }
    func_ovl10_06_80049680(func_ovl10_06_80048F7C);
    func_ovl10_06_800434E0();
    D_ovl10_06_8004B8FC = 0;
}

void func_ovl10_06_800434D8(void) {

}

void func_ovl10_06_8004347C(void) {
    func_ovl10_06_80049750(5, 0, 0xF);
    func_ovl10_06_80049790(0x40);
    func_ovl10_06_80049798(0x40, 3, 8.5f, 5, 0, 1, 1);
    D_ovl10_06_8004B280 = 0;
}

void func_ovl10_06_80043424(void) {
    func_ovl10_06_80049750(5, 0, 0xF);
    func_ovl10_06_80049798(0x40, 3, 8.5f, 5, 0, 1, 1);
    D_ovl10_06_8004B280 = 1;
}

void func_ovl10_06_800433F0(void) {
    func_ovl10_06_80049750(0x11, 1, 0xF);
    func_ovl10_06_80049790(0x40);
    D_ovl10_06_8004B280 = 0;
}

/* ovl_10_12's 80044740 */
void func_ovl10_06_800433C8(void) {
    func_ovl10_06_800497A8();
    func_ovl10_06_80043338();
}

/* ovl_10_12's 800446B0 */
static void func_ovl10_06_80043330(void) {
}

void func_ovl10_06_80043338(void) {
    func_ovl10_06_80043330();
    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
    if (*D_ovl10_06_8004ADB4 & 2) {
        func_ovl10_06_8004A0E8(func_ovl10_06_80048EA0, 0, 0, 0, 0x130);
        func_ovl10_06_8004A0E8(func_ovl10_06_80048E64, 0, 0, 0, 0x130);
        func_ovl10_06_80049E40(15);
        func_ovl10_06_80049E50(2);
        func_ovl10_06_8004A618(0);
    }
}

static void func_ovl10_06_80043270(void) {
}

static void func_ovl10_06_80043268(void) {
}

void func_ovl10_06_80043278(void) {
    func_ovl10_06_80043268();
    func_ovl10_06_80043270();
    func_ovl10_06_800497E0(1);
    if (func_ovl10_06_80049760(3, 0xE, 5, 0x10) != 0) {
        D_ovl10_06_8004AB84 = 0x6C;
        D_ovl10_06_8004AB88 = 0x13;
        func_ovl10_06_80049690(0x6C, 0x13, 0);
    }
    if (func_ovl10_06_80049760(0x2B, 0xE, 0x2F, 0x10) != 0) {
        if (func_ovl10_06_8004A370(0x401) != 0) {
            func_ovl10_06_8004A548(D_ovl10_06_8004AB80);
        }
        func_ovl10_06_8004322C(0x25);
        func_ovl10_06_8004A578();
        func_ovl10_06_800497B0(1);
        func_ovl10_06_800496B8();
    }
}

void func_ovl10_06_8004322C(s32 arg0) {
    s32 *p;

    p = func_ovl10_06_8004A380(arg0);
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_06_800431C0(void) {
    if (func_ovl10_06_8004A370(0x400) == 0) {
        func_ovl10_06_80049798(0x40, 3, 4.0f, 0, 1, 1, 1);
        func_ovl10_06_8004A360(0x400);
        func_ovl10_06_80049788(1);
        func_ovl10_06_800430A8(func_ovl10_06_80043EA8);
    }
}

void func_ovl10_06_80043120(void) {
    if (func_ovl10_06_8004A370(0x401) == 0) {
        if (D_ovl10_06_8004B8FC == 0) {
            func_ovl10_06_80049848();
            if (func_ovl10_06_80049768(0x27, 1, 0xE, 0x29, 0x10) != 0) {
                func_ovl10_06_80049788(1);
                func_ovl10_06_800430A8(func_ovl10_06_80044804);
            } else {
                func_ovl10_06_80049788(1);
                func_ovl10_06_800430A8(func_ovl10_06_800457C0);
                D_ovl10_06_8004B8FC = 1;
            }
        }
    }
}

/* ovl_10_12's 80043018 */
void func_ovl10_06_80043060(void) {
    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
    if (*D_ovl10_06_8004ADB4 & 2) {
        func_ovl10_06_8004A7F0();
    }
}

/* ovl_10_12's 80043018 */
void func_ovl10_06_80043018(void) {
    D_ovl10_06_8004ADB4 = func_ovl10_06_800496E8();
    if (*D_ovl10_06_8004ADB4 & 2) {
        func_ovl10_06_8004A7F0();
    }
}

void func_ovl10_06_80043010(void) {

}
