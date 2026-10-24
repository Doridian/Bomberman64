/*
 * NON_MATCHING: ovl_10_10's game object, complete: every function and its
 * .data/.bss/.rodata (sizes 0x80/0xB0/0x490 and contents as the
 * original); .text one word short. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 81, eu 81, jp 81
 *
 * What still differs in us (words; eu and jp the same), all of it as in
 * ovl_10_11's draft of the same code:
 * - func_ovl10_10_800431AC (6): 800473F8/800473FC are loaded in the
 *   order of the stores (the original loads them as the call's
 *   arguments, a1 first) and the call's `move a2,zero` is scheduled
 *   before the jal.
 * - func_ovl10_10_80043D88 (62): one word short. The original builds
 *   the addresses of 80047468-800474B0 in registers (lui/addiu/addu,
 *   a2/a3/t0/t1); ours stores them through `at`. While and for loops
 *   are worse (93 words).
 * - func_ovl10_10_80044CA0 (2): the two stores of `y` (sp+0x74 and the
 *   call's sp+0x18) swap.
 * - func_ovl10_10_80045700 (11): the same code; the padding after its
 *   endless loop is a word longer because 80043D88 is a word short.
 *
 * ovl_10_10's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Most of it is ovl_10_11's
 * 23A720 with the overlay's addresses: the task functions (8004304C,
 * 8004417C, 80044280, 8004429C, 80045644-80045700, with the strings "trap
 * task:entry failed" and "task_entry>%d:%s"), the switches and their
 * records (800433D4, 80043C6C-80043D88, 80044B44-80045300).
 *
 * Where a function comes out: IDO takes the functions from the bottom of
 * the file up, and before each one it puts out the functions it calls
 * that aren't out yet, the last call first (a static only that way). So
 * 80043D88, 80043C6C, 80043BF0, 80043AAC and the static 80043A0C are
 * defined above 8004486C, where nothing below 80043EF4 reaches them:
 * 80043EF4 pulls them out in front of it in the original's order, and
 * 80043C6C's initializer comes after 800451A8's and before the tables
 * and 80044664's, as in .data. 80043A0C takes its arguments in s2-s4
 * (the callers save them); its parameter order sets 80043EF4's scheduling.
 */

#include "common.h"

/* What func_ovl10_10_80046850 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_10_80046850;

void func_ovl10_10_80045938(const char *, ...);
void func_ovl10_10_80045C78(s32);
void func_ovl10_10_80045C80(s32, f32, f32, f32, s32, s32);
void func_ovl10_10_80045C90(s32);
void func_ovl10_10_80045CB0(s32, s32, s32, s32);
void func_ovl10_10_80045CD0(f32, f32, f32, s32 *, s32);
void func_ovl10_10_80045CD8(f32, f32, f32, Vec3f *, s32);
s32 func_ovl10_10_80045CE0(s32);
f32 func_ovl10_10_80045D18(s32);
void func_ovl10_10_80045D20(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_10_80045D28(s32, s32, s32, s32, s32, s32);
void func_ovl10_10_80045D30(s32);
void func_ovl10_10_80045D60(void (*)(UnkStructA *));
void func_ovl10_10_80045D70(s32, s32, s32);
void func_ovl10_10_80045D98(void);
s32 *func_ovl10_10_80045DC8(void);
void func_ovl10_10_80045DE0(s32);
void func_ovl10_10_80045DE8(s32);
void func_ovl10_10_80045E28(void);
void func_ovl10_10_80045E30(s32, s32, s32);
s32 func_ovl10_10_80045E40(s32, s32, s32, s32);
s32 func_ovl10_10_80045E48(s32, s32, s32, s32, s32);
s32 func_ovl10_10_80045E58(void);
void func_ovl10_10_80045E68(s32);
void func_ovl10_10_80045E78(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_10_80045E88(void);
void func_ovl10_10_80045E90(s32);
void func_ovl10_10_80045EA0(s32);
UnkStructA *func_ovl10_10_80045EB8(s32);
void func_ovl10_10_80045ED0(s32);
void func_ovl10_10_800464B8(f32, f32, f32);
void func_ovl10_10_800464D8(f32, f32, f32);
void func_ovl10_10_800464E0(f32 *, f32 *, f32 *);
void func_ovl10_10_80046518(s32);
void func_ovl10_10_80046520(s32);
void func_ovl10_10_80046540(f32);
void func_ovl10_10_80046548(f32);
void func_ovl10_10_80046560(f32);
void func_ovl10_10_800465D8(void);
void func_ovl10_10_800465E0(void);
s32 func_ovl10_10_80046628(UnkStructA *, s32);
void func_ovl10_10_80046680(UnkStructA *, s32);
void func_ovl10_10_80046690(UnkStructA *);
UnkStructA *func_ovl10_10_800466A0(s32, s32, s32, s32);
void func_ovl10_10_800466F8(UnkStructA *);
void func_ovl10_10_80046748(UnkStructA *, Vec3f *);
void func_ovl10_10_800467C8(void (*)(void), s32, s32, s32, s32);
void func_ovl10_10_800467E8(s32);
void func_ovl10_10_80046810(void);
void func_ovl10_10_80046840(s32, s32);
UnkStruct_ovl10_10_80046850 *func_ovl10_10_80046850(void);
void func_ovl10_10_80046860(UnkStruct_ovl10_10_80046850 *, s32);
f64 func_ovl10_10_80046980(void);
s32 func_ovl10_10_80046988(s32);
void func_ovl10_10_80046A40(s32);
s32 func_ovl10_10_80046A50(s32);
s32 *func_ovl10_10_80046A60(s32);
void func_ovl10_10_80046AC8(s32, s32, s32, f32);
void func_ovl10_10_80046B08(s32, s32, s32, s32, s32);
void func_ovl10_10_80046B18(s32, s32, s32);
void func_ovl10_10_80046B30(u32 (*)[3]);
s32 func_ovl10_10_80046C20(s32, Vec3f *, s32);
void func_ovl10_10_80046C28(s32);
void func_ovl10_10_80046C58(void);
void func_ovl10_10_80046CD8(s32, s32, s32);
void func_ovl10_10_80046D50(s32);
void func_ovl10_10_80046D70(s32, f32, f32, f32);
void func_ovl10_10_80046D78(s32, Vec3f *);

void func_ovl10_10_80043010(void);
void func_ovl10_10_80043018(void);
s32 func_ovl10_10_8004304C(void (*)(void));
void func_ovl10_10_800430C4(s32, f32, f32, f32);
void func_ovl10_10_800431AC(void);
void func_ovl10_10_80043298(void);
s32 func_ovl10_10_800433D4(s32);
void func_ovl10_10_800436A4(s32);
void func_ovl10_10_800436E8(void);
void func_ovl10_10_80043764(void);
void func_ovl10_10_800437BC(void);
void func_ovl10_10_800437DC(void);
void func_ovl10_10_80043940(void);
void func_ovl10_10_800439E4(void);
void func_ovl10_10_80043AAC(void);
void func_ovl10_10_80043BF0(void);
void func_ovl10_10_80043C6C(s32);
void func_ovl10_10_80043D88(s32 *);
void func_ovl10_10_80043EF4(void);
void func_ovl10_10_800440A4(s32);
void func_ovl10_10_8004417C(void);
void func_ovl10_10_80044198(void);
void func_ovl10_10_80044220(void);
void func_ovl10_10_80044280(void (*)(void));
void func_ovl10_10_8004429C(s32);
void func_ovl10_10_800442B8(void);
void func_ovl10_10_80044350(void);
void func_ovl10_10_800443E4(f32);
void func_ovl10_10_80044508(void);
void func_ovl10_10_8004455C(void);
void func_ovl10_10_800445E4(void);
void func_ovl10_10_80044664(void);
void func_ovl10_10_8004486C(void);
void func_ovl10_10_80044B44(s32);
void func_ovl10_10_80044B7C(void);
void func_ovl10_10_80044CA0(void);
void func_ovl10_10_800450F4(s32 *);
void func_ovl10_10_800451A8(s32, s32);
void func_ovl10_10_80045300(void);
void func_ovl10_10_800454C8(UnkStructA *);
void func_ovl10_10_80045548(UnkStructA *);
void func_ovl10_10_800455B4(void);
void func_ovl10_10_80045644(s32);
s32 func_ovl10_10_80045658(void (*)(void));
void func_ovl10_10_8004569C(void (*)(void));
s32 func_ovl10_10_800456C8(void (*)(void), const char *);
void func_ovl10_10_80045700(void);
void func_ovl10_10_800457F8(s32, UnkStructA *);
void func_ovl10_10_8004582C(f32);
void func_ovl10_10_80045874(f32, f32, f32);
void func_ovl10_10_800458D0(void);
void func_ovl10_10_800458E8(void);

void func_ovl10_10_80043044(void);
static void func_ovl10_10_800436E0(void);
static void func_ovl10_10_80043A0C(s32, s32, s32, s32);

/* .bss */
u8 D_ovl10_10_800470A0[0x20];
s32 D_ovl10_10_800470C0;
s32 D_ovl10_10_800470C4;
s32 D_ovl10_10_800470C8;
u8 D_ovl10_10_800470CC[0x4]; /* unused (func_ovl10_10_800458E8) */
Vec3f D_ovl10_10_800470D0;
s32 D_ovl10_10_800470DC;
s32 D_ovl10_10_800470E0;
s32 D_ovl10_10_800470E4;
/* the tasks: a countdown and a function each */
s32 D_ovl10_10_800470E8[64];
s32 D_ovl10_10_800471E8; /* the running task */
u8 D_ovl10_10_800471EC[0x4]; /* unused (func_ovl10_10_800458E8) */
void (*D_ovl10_10_800471F0[64])(void);
UnkStruct_ovl10_10_80046850 *D_ovl10_10_800472F0;
u8 D_ovl10_10_800472F4[0x4]; /* unused (func_ovl10_10_800458E8) */
s32 D_ovl10_10_800472F8[4][3];
UnkStructA *D_ovl10_10_80047328[4];
s32 D_ovl10_10_80047338;
u8 D_ovl10_10_8004733C[0x4]; /* unused (func_ovl10_10_800458E8) */
s32 D_ovl10_10_80047340[4];
s32 D_ovl10_10_80047350[4];
s32 D_ovl10_10_80047360[5];
s32 D_ovl10_10_80047374;
f32 D_ovl10_10_80047378;
f32 D_ovl10_10_8004737C;
f32 D_ovl10_10_80047380;
u8 D_ovl10_10_80047384[0x4]; /* unused (func_ovl10_10_800458E8) */
s32 D_ovl10_10_80047388[6][3];
UnkStructA *D_ovl10_10_800473D0[6];
UnkStructA *D_ovl10_10_800473E8;
s32 D_ovl10_10_800473EC;
s32 D_ovl10_10_800473F0;
s32 D_ovl10_10_800473F4;
s32 D_ovl10_10_800473F8;
s32 D_ovl10_10_800473FC;
s32 D_ovl10_10_80047400[6];
s32 D_ovl10_10_80047418[6];
s32 D_ovl10_10_80047430[6];
s32 D_ovl10_10_80047448;
u8 D_ovl10_10_8004744C[0x4]; /* unused (func_ovl10_10_800458E8) */
s32 D_ovl10_10_80047450[6];
s32 D_ovl10_10_80047468[6];
s32 D_ovl10_10_80047480[6];
s32 D_ovl10_10_80047498[6];
s32 D_ovl10_10_800474B0[6];
f32 D_ovl10_10_800474C8;
f32 D_ovl10_10_800474CC;
f32 D_ovl10_10_800474D0;
f32 D_ovl10_10_800474D4;
f32 D_ovl10_10_800474D8;
f32 D_ovl10_10_800474DC;
f32 D_ovl10_10_800474E0;
/* the two objects 80043AAC makes */
UnkStructA *D_ovl10_10_800474E4;
UnkStructA *D_ovl10_10_800474E8;
s32 D_ovl10_10_800474EC;
s32 D_ovl10_10_800474F0;
/* the camera's moves (800443E4, 8004486C) */
f32 D_ovl10_10_800474F4;
f32 D_ovl10_10_800474F8;
f32 D_ovl10_10_800474FC;
f32 D_ovl10_10_80047500;
f32 D_ovl10_10_80047504;
f32 D_ovl10_10_80047508;
f32 D_ovl10_10_8004750C;
f32 D_ovl10_10_80047510;
f32 D_ovl10_10_80047514;
f32 D_ovl10_10_80047518;
f32 D_ovl10_10_8004751C;
f32 D_ovl10_10_80047520;

/* .data, defined below func_ovl10_10_80043C6C */
extern u32 D_ovl10_10_80046F88[][3];
extern s32 D_ovl10_10_80046FAC[];

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_10_80045928(void) {
}

static void func_ovl10_10_80045920(void) {
}

static void func_ovl10_10_80045918(void) {
}

static void func_ovl10_10_80045910(void) {
}

static void func_ovl10_10_80045908(void) {
}

static void func_ovl10_10_80045900(void) {
}

static void func_ovl10_10_800458F8(void) {
}

static void func_ovl10_10_800458F0(void) {
}

void func_ovl10_10_800458E8(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_10_800470A0[0] = D_ovl10_10_800470CC[0] + D_ovl10_10_800471EC[0] + D_ovl10_10_800472F4[0] +
                                 D_ovl10_10_8004733C[0] + D_ovl10_10_80047384[0] + D_ovl10_10_8004744C[0];
    }
}

void func_ovl10_10_800458D0(void) {
    D_ovl10_10_800470C4 = -1;
    D_ovl10_10_800470C8 = -1;
}

void func_ovl10_10_80045874(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_10_800464B8(D_ovl10_10_800470D0.x, D_ovl10_10_800470D0.y, D_ovl10_10_800470D0.z);
    func_ovl10_10_800464D8(arg0, arg1, arg2);
    func_ovl10_10_800467E8(180);
}

void func_ovl10_10_8004582C(f32 arg0) {
    f32 sp1C;

    func_ovl10_10_800464E0(&sp1C, NULL, NULL);
    func_ovl10_10_800464D8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_10_800457F8(s32 arg0, UnkStructA *arg1) {
    func_ovl10_10_80046D70(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_10_80045700(void) {
    s32 i;

    D_ovl10_10_800470E0 = 0;
    D_ovl10_10_800470E4 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_10_800471F0[i] != NULL) {
                D_ovl10_10_800471E8 = i;
                if (D_ovl10_10_800470E8[i] == 0) {
                    D_ovl10_10_800471F0[i]();
                } else {
                    D_ovl10_10_800470E8[i]--;
                }
            }
        }
        D_ovl10_10_800470E0++;
        D_ovl10_10_800470E0 &= 3;
        func_ovl10_10_80046810();
    }
}

/* Defined above its caller 800456C8 (only so does its string come first in
 * .rodata); 800430C4, the first caller IDO reaches, pulls it out. */
s32 func_ovl10_10_8004304C(void (*arg0)(void)) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_10_800471F0[i] == NULL) {
            D_ovl10_10_800471F0[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_10_80045938("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_10_800456C8(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_10_8004304C(arg0);
    func_ovl10_10_80045938("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_10_8004569C(void (*arg0)(void)) {
    D_ovl10_10_800471F0[func_ovl10_10_80045658(arg0)] = NULL;
}

s32 func_ovl10_10_80045658(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_10_800471F0[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_10_80045644(s32 arg0) {
    D_ovl10_10_800471F0[arg0] = NULL;
}

void func_ovl10_10_800455B4(void) {
    D_ovl10_10_800472F0 = func_ovl10_10_80046850();
    func_ovl10_10_80046860(D_ovl10_10_800472F0, 0x20000001);
    D_ovl10_10_800472F0->unk40 = 0.5f;
    D_ovl10_10_800472F0->unk44 = D_ovl10_10_800472F0->unk40 * 0.75f;
    D_ovl10_10_800472F0->unk18 = 0.1f;
    D_ovl10_10_800472F0->unk1C = -0.1f;
}

void func_ovl10_10_80045548(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_10_80046520(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_10_800466F8(arg0);
        func_ovl10_10_80046810();
    }
}

void func_ovl10_10_800454C8(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_10_80046AC8(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_10_80046680(arg0, 0x01000000);
        func_ovl10_10_800467E8(5);
        func_ovl10_10_80046AC8(0, 0, 0, 0.0f);
        func_ovl10_10_80046748(arg0, &pos);
        func_ovl10_10_80046C20(12, &pos, 0);
    }
}

void func_ovl10_10_80045300(void) {
    s32 found;
    s32 i;

    found = -1;
    i = 0;
    do {
        if (func_ovl10_10_80045E48(D_ovl10_10_800472F8[i][0], D_ovl10_10_800472F8[i][1], D_ovl10_10_800472F8[i][2],
                                   D_ovl10_10_800472F8[i][0] + 1, D_ovl10_10_800472F8[i][2] + 1) != 0) {
            found = i;
        }
        i++;
    } while (i < D_ovl10_10_80047338 && found == -1);
    if (found != -1) {
        D_ovl10_10_80047350[found] = (D_ovl10_10_80047350[found] + 1) % 2;
        func_ovl10_10_800451A8(found, D_ovl10_10_80047350[found]);
        D_ovl10_10_80047360[D_ovl10_10_80047340[found]] = (D_ovl10_10_80047360[D_ovl10_10_80047340[found]] + 1) % 2;
        if (D_ovl10_10_80047350[found] == 1 && D_ovl10_10_80047340[found] != 4) {
            for (i = 0; i < D_ovl10_10_80047338; i++) {
                if (i != found && D_ovl10_10_80047340[i] != 4 && D_ovl10_10_80047350[i] == 1) {
                    D_ovl10_10_80047350[i] = 0;
                    func_ovl10_10_800451A8(i, 0);
                    D_ovl10_10_80047360[D_ovl10_10_80047340[i]] = 0;
                }
            }
        }
    }
}

void func_ovl10_10_800451A8(s32 arg0, s32 arg1) {
    s32 sp38[4] = { 0xBF, 0xC0, 0xC1, 0xC4 };
    Vec3f pos;

    if (arg1 == 1) {
        D_ovl10_10_80047328[arg0] =
            func_ovl10_10_800466A0(sp38[D_ovl10_10_80047340[arg0] - 1], 0x01000000, 0xD0, 0);
        func_ovl10_10_80045CD8(D_ovl10_10_800472F8[arg0][0], D_ovl10_10_800472F8[arg0][1],
                               D_ovl10_10_800472F8[arg0][2], &pos, 0);
        D_ovl10_10_80047328[arg0]->unk40->unk10 = pos.x;
        D_ovl10_10_80047328[arg0]->unk40->unk14 = pos.y;
        D_ovl10_10_80047328[arg0]->unk40->unk18 = pos.z;
    } else {
        func_ovl10_10_80046690(D_ovl10_10_80047328[arg0]);
        D_ovl10_10_80047328[arg0] = NULL;
    }
}

void func_ovl10_10_800450F4(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_10_800472F8[i][0] = arg0[0];
        D_ovl10_10_800472F8[i][1] = arg0[1];
        D_ovl10_10_800472F8[i][2] = arg0[2];
        D_ovl10_10_80047340[i] = arg0[3];
        D_ovl10_10_80047350[i] = 0;
        arg0 += 4;
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_10_80047338 = i;
    for (i = 1; i < 5; i++) {
        D_ovl10_10_80047360[i] = 0;
    }
}

void func_ovl10_10_80044CA0(void) {
    s32 y;
    s32 i;
    s32 a;
    s32 b;
    s32 out[6];
    s32 *flags;

    i = D_ovl10_10_80047374;
    D_ovl10_10_800473E8 = func_ovl10_10_80045EB8(func_ovl10_10_80045E58());
    D_ovl10_10_800473D0[i]->unk40->unk14 += D_ovl10_10_80047378;
    D_ovl10_10_800473E8->unk40->unk14 = D_ovl10_10_800473D0[i]->unk40->unk14;
    D_ovl10_10_80047378 += D_ovl10_10_8004737C;
    if (D_ovl10_10_800474E0 != -1.0f &&
        ((D_ovl10_10_80047378 > 0.0f && D_ovl10_10_800474E0 <= D_ovl10_10_800473D0[i]->unk40->unk14) ||
         (D_ovl10_10_80047378 < 0.0f && D_ovl10_10_800473D0[i]->unk40->unk14 <= D_ovl10_10_800474E0))) {
        D_ovl10_10_8004737C = -D_ovl10_10_8004737C;
        D_ovl10_10_800474E0 = -1.0f;
    }
    if (D_ovl10_10_80047380 != -1.0f &&
        (D_ovl10_10_80047378 == 0.0f ||
         (D_ovl10_10_80047378 > 0.0f && D_ovl10_10_80047380 < D_ovl10_10_800473D0[i]->unk40->unk14) ||
         (D_ovl10_10_80047378 < 0.0f && D_ovl10_10_800473D0[i]->unk40->unk14 < D_ovl10_10_80047380))) {
        flags = func_ovl10_10_80045DC8();
        if (!(*flags & 2)) {
            func_ovl10_10_80045DE0(1);
        }
        func_ovl10_10_8004417C();
        D_ovl10_10_800473E8->unk70 = 1.6333334f;
        if (D_ovl10_10_80047378 != 0.0f) {
            D_ovl10_10_800473D0[i]->unk40->unk14 = D_ovl10_10_80047380;
            D_ovl10_10_800473E8->unk40->unk14 = D_ovl10_10_80047380;
        }
        if (D_ovl10_10_80047400[i] == 2) {
            func_ovl10_10_80045CD0(D_ovl10_10_800473D0[i]->unk40->unk10, D_ovl10_10_800473D0[i]->unk40->unk14,
                                   D_ovl10_10_800473D0[i]->unk40->unk18, out, 2);
            y = out[1];
            func_ovl10_10_80045D20(D_ovl10_10_80047388[i][0], D_ovl10_10_80047388[i][1], D_ovl10_10_80047388[i][2],
                                   D_ovl10_10_80047388[i][0] + 1, D_ovl10_10_80047388[i][2] + 1,
                                   D_ovl10_10_80047388[i][0], y, D_ovl10_10_80047388[i][2]);
            func_ovl10_10_80045D28(D_ovl10_10_80047388[i][0], D_ovl10_10_80047388[i][1], D_ovl10_10_80047388[i][2],
                                   D_ovl10_10_80047388[i][0] + 1, D_ovl10_10_80047388[i][2] + 1, 0);
            D_ovl10_10_80047450[i] = D_ovl10_10_80047388[i][1];
            D_ovl10_10_80047388[i][1] = y;
            if (D_ovl10_10_80047378 > 0.0f) {
                a = D_ovl10_10_80047468[i];
                b = D_ovl10_10_80047480[i];
            } else {
                a = D_ovl10_10_80047498[i];
                b = D_ovl10_10_800474B0[i];
            }
            func_ovl10_10_80045E78(a, 3, 8.5f, b, 1, 1, 1);
            func_ovl10_10_80046548(0.1f);
            func_ovl10_10_80046560(40.0f);
        }
        func_ovl10_10_80045D30(0);
        if (!(*flags & 2)) {
            func_ovl10_10_80045E68(0);
        }
        func_ovl10_10_80046840(0xD0, 0xD0);
    }
}

void func_ovl10_10_80044B7C(void) {
    s32 i;

    for (i = 0; i < D_ovl10_10_80047448; i++) {
        if (D_ovl10_10_80047400[i] == 2 && D_ovl10_10_80047418[i] != D_ovl10_10_80047360[D_ovl10_10_80047430[i]]) {
            if (D_ovl10_10_800473D0[i] != NULL) {
                func_ovl10_10_80044B44(i);
            }
            D_ovl10_10_80047418[i] = D_ovl10_10_80047360[D_ovl10_10_80047430[i]];
            func_ovl10_10_80043C6C(i);
        }
    }
}

void func_ovl10_10_80044B44(s32 arg0) {
    func_ovl10_10_80046690(D_ovl10_10_800473D0[arg0]);
    D_ovl10_10_800473D0[arg0] = NULL;
}

/* reads records of 11 words up to a -1 (defined up here: see the top) */
void func_ovl10_10_80043D88(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_10_80047388[i][0] = arg0[0];
        D_ovl10_10_80047388[i][1] = arg0[1];
        D_ovl10_10_80047388[i][2] = arg0[2];
        D_ovl10_10_80047450[i] = arg0[3];
        D_ovl10_10_80047400[i] = arg0[4];
        D_ovl10_10_80047418[i] = arg0[5];
        D_ovl10_10_80047430[i] = arg0[6];
        D_ovl10_10_80047468[i] = arg0[7];
        D_ovl10_10_80047480[i] = arg0[8];
        D_ovl10_10_80047498[i] = arg0[9];
        D_ovl10_10_800474B0[i] = arg0[10];
        arg0 += 11;
        func_ovl10_10_80043C6C(i);
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_10_80047448 = i;
}

void func_ovl10_10_80043C6C(s32 arg0) {
    Vec3f pos;
    s32 sp2C[2] = { 0xCA, 0xB2 };

    D_ovl10_10_800473D0[arg0] = func_ovl10_10_800466A0(sp2C[D_ovl10_10_80047418[arg0]], 0x01000000, 0xD0, 0);
    func_ovl10_10_80045CD8(D_ovl10_10_80047388[arg0][0], D_ovl10_10_80047388[arg0][1], D_ovl10_10_80047388[arg0][2],
                           &pos, 0);
    D_ovl10_10_800473D0[arg0]->unk40->unk10 = pos.x;
    D_ovl10_10_800473D0[arg0]->unk40->unk14 = pos.y;
    D_ovl10_10_800473D0[arg0]->unk40->unk18 = pos.z;
}

/* passed to func_ovl10_10_80046B30: three 12-byte records */
u32 D_ovl10_10_80046F88[][3] = {
    { 0xA60002, 0xE, 4 },
    { 0xA50003, 0xF, 4 },
    { 0xA70001, 0xE, 4 },
};

/* passed to func_ovl10_10_80043D88: one 11-word record and a -1 */
s32 D_ovl10_10_80046FAC[] = {
    1, 0, 0xF, 0xFFFFFF01, 1, 1, 0, 0x70, 0x12, 0, 0,
    -1,
};

void func_ovl10_10_80043BF0(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_10_800471F0[i] = NULL;
        D_ovl10_10_800470E8[i] = 0;
    }
    func_ovl10_10_800467C8(func_ovl10_10_80045700, 0, 0, 0, 0x110);
}

void func_ovl10_10_80043AAC(void) {
    Vec3f pos;

    func_ovl10_10_80045CD8(14.0f, 1.0f, 15.0f, &pos, 0);
    D_ovl10_10_800474E4 = func_ovl10_10_800466A0(0xC8, 0x01000000, 0x10, 0);
    D_ovl10_10_800474E4->unk40->unk10 = pos.x + 50.0f;
    D_ovl10_10_800474E4->unk40->unk14 = pos.y;
    D_ovl10_10_800474E4->unk40->unk18 = pos.z + 50.0f;
    D_ovl10_10_800474E4->unk30 = 1;
    D_ovl10_10_800474E4->unk34 = 200.0f;
    D_ovl10_10_800474E4->unk38 = 200.0f;
    D_ovl10_10_800474E8 = func_ovl10_10_800466A0(0xC9, 0x01080000, 0x10, 0);
    D_ovl10_10_800474E8->unk40->unk10 = pos.x + 50.0f;
    D_ovl10_10_800474E8->unk40->unk14 = pos.y;
    D_ovl10_10_800474E8->unk40->unk18 = pos.z + 50.0f;
    D_ovl10_10_800474E8->unk30 = 1;
    D_ovl10_10_800474E8->unk34 = 200.0f;
    D_ovl10_10_800474E8->unk38 = 200.0f;
    func_ovl10_10_8004304C(func_ovl10_10_80044198);
}

static void func_ovl10_10_80043A0C(s32 model, s32 x, s32 n, s32 z) {
    s32 i;

    D_ovl10_10_800470D0.x = x * 100.0f;
    D_ovl10_10_800470D0.y = 0.0f;
    for (i = 0; i < n; i++) {
        D_ovl10_10_800470D0.y += func_ovl10_10_80045CE0(i) * 100.0f;
    }
    D_ovl10_10_800470D0.y += 100.0f;
    D_ovl10_10_800470D0.z = z * 100.0f;
    D_ovl10_10_800470C0 = func_ovl10_10_80046C20(model, &D_ovl10_10_800470D0, 0);
}

void func_ovl10_10_8004486C(void) {
    func_ovl10_10_800464B8(D_ovl10_10_8004750C, 32768.0f, D_ovl10_10_80047510);
    func_ovl10_10_800464D8(270.0f, D_ovl10_10_800474F4, D_ovl10_10_80047504);
    D_ovl10_10_800474F4 += D_ovl10_10_800474FC;
    D_ovl10_10_80047504 += D_ovl10_10_80047500;
    D_ovl10_10_8004750C += D_ovl10_10_80047518;
    D_ovl10_10_80047510 += D_ovl10_10_80047520;
    if ((D_ovl10_10_800474FC > 0.0f && D_ovl10_10_800474F8 <= D_ovl10_10_800474F4) ||
        (D_ovl10_10_800474FC < 0.0f && D_ovl10_10_800474F4 <= D_ovl10_10_800474F8)) {
        D_ovl10_10_800474FC = 0.0f;
        D_ovl10_10_800474F4 = D_ovl10_10_800474F8;
    }
    if ((D_ovl10_10_80047500 > 0.0f && D_ovl10_10_80047508 <= D_ovl10_10_80047504) ||
        (D_ovl10_10_80047500 < 0.0f && D_ovl10_10_80047504 <= D_ovl10_10_80047508)) {
        D_ovl10_10_80047504 = D_ovl10_10_80047508;
        D_ovl10_10_80047500 = 0.0f;
    }
    if ((D_ovl10_10_80047518 > 0.0f && D_ovl10_10_80047514 <= D_ovl10_10_8004750C) ||
        (D_ovl10_10_80047518 < 0.0f && D_ovl10_10_8004750C <= D_ovl10_10_80047514)) {
        D_ovl10_10_8004750C = D_ovl10_10_80047514;
        D_ovl10_10_80047518 = 0.0f;
    }
    if ((D_ovl10_10_80047520 > 0.0f && D_ovl10_10_8004751C <= D_ovl10_10_80047510) ||
        (D_ovl10_10_80047520 < 0.0f && D_ovl10_10_80047510 <= D_ovl10_10_8004751C)) {
        D_ovl10_10_80047510 = D_ovl10_10_8004751C;
        D_ovl10_10_80047520 = 0.0f;
    }
    if (D_ovl10_10_800474FC == 0.0f && D_ovl10_10_80047500 == 0.0f && D_ovl10_10_80047518 == 0.0f &&
        D_ovl10_10_80047520 == 0.0f) {
        func_ovl10_10_8004417C();
    }
}

void func_ovl10_10_80044664(void) {
    s32 r;
    s32 big;
    s32 pad; /* unused: the original's frame has the slot */
    s32 ids[2] = { 0xC, 0x13 };
    Vec3f pos;

    D_ovl10_10_800474EC--;
    if (!(D_ovl10_10_800474EC & 7)) {
        big = D_ovl10_10_800474EC >> 3;
        r = func_ovl10_10_80046988(1);
        func_ovl10_10_80046748(D_ovl10_10_800474E4, &pos);
        pos.x += (f32)func_ovl10_10_80046980() * 20.0f - 110.0f;
        pos.y += (f32)func_ovl10_10_80046980() * 300.0f;
        pos.z += (f32)func_ovl10_10_80046980() * 400.0f - 200.0f;
        func_ovl10_10_80046C20(ids[r], &pos, 0);
        if (big != 0) {
            if (func_ovl10_10_80046988(1) != 0) {
                func_ovl10_10_80046D78(0xC9, &pos);
            } else {
                func_ovl10_10_80046D78(0xCB, &pos);
            }
        }
    }
    if (D_ovl10_10_800474EC == 0) {
        func_ovl10_10_80046748(D_ovl10_10_800474E4, &pos);
        func_ovl10_10_80046D78(0xAB, &pos);
        func_ovl10_10_80046690(D_ovl10_10_800474E4);
        func_ovl10_10_80046690(D_ovl10_10_800474E8);
        D_ovl10_10_800474E4 = NULL;
        D_ovl10_10_800474E8 = NULL;
        func_ovl10_10_80045D28(0xE, 1, 0xE, 0xF, 0x11, 1);
        func_ovl10_10_80045D28(0xE, 2, 0xE, 0xF, 0x11, 1);
        func_ovl10_10_8004417C();
    }
}

void func_ovl10_10_800445E4(void) {
    func_ovl10_10_80045DE0(0);
    func_ovl10_10_80045E68(1);
    func_ovl10_10_80045DE8(1);
    func_ovl10_10_80046840(0xB0, 0xB0);
    func_ovl10_10_8004304C(func_ovl10_10_80044664);
    D_ovl10_10_800474EC = 180;
    func_ovl10_10_8004429C(90);
    func_ovl10_10_80044280(func_ovl10_10_8004455C);
}

void func_ovl10_10_8004455C(void) {
    func_ovl10_10_800465D8();
    func_ovl10_10_80046520(0x1F);
    func_ovl10_10_800464B8(1400.0f, 200.0f, 1550.0f);
    func_ovl10_10_800464D8(270.0f, 45.0f, 4000.0f);
    func_ovl10_10_8004429C(150);
    func_ovl10_10_80044280(func_ovl10_10_80044508);
}

void func_ovl10_10_80044508(void) {
    func_ovl10_10_800443E4(60.0f);
    func_ovl10_10_8004429C(60);
    func_ovl10_10_80044280(func_ovl10_10_80044350);
}

void func_ovl10_10_800443E4(f32 arg0) {
    D_ovl10_10_800474F4 = 45.0f;
    D_ovl10_10_800474F8 = 45.0f;
    D_ovl10_10_80047504 = 4000.0f;
    D_ovl10_10_80047508 = 2200.0f;
    D_ovl10_10_8004750C = 1400.0f;
    D_ovl10_10_80047514 = 4600.0f;
    D_ovl10_10_80047510 = 1550.0f;
    D_ovl10_10_8004751C = 1600.0f;
    D_ovl10_10_800474FC = (D_ovl10_10_800474F8 - D_ovl10_10_800474F4) / arg0;
    D_ovl10_10_80047500 = (D_ovl10_10_80047508 - D_ovl10_10_80047504) / arg0;
    D_ovl10_10_80047518 = (D_ovl10_10_80047514 - D_ovl10_10_8004750C) / arg0;
    D_ovl10_10_80047520 = (D_ovl10_10_8004751C - D_ovl10_10_80047510) / arg0;
    func_ovl10_10_8004304C(func_ovl10_10_8004486C);
}

void func_ovl10_10_80044350(void) {
    Vec3f pos;

    func_ovl10_10_80045CD8(46.0f, 2.0f, 16.0f, &pos, 0);
    func_ovl10_10_800464B8(pos.x, pos.y, pos.z);
    func_ovl10_10_800464D8(270.0f, 45.0f, 2200.0f);
    func_ovl10_10_8004429C(90);
    func_ovl10_10_80044280(func_ovl10_10_800442B8);
}

void func_ovl10_10_800442B8(void) {
    func_ovl10_10_80043A0C(0x28, 0x2E, 2, 0x10);
    func_ovl10_10_80046D50(0x2C);
    func_ovl10_10_8004429C(120);
    func_ovl10_10_80044280(func_ovl10_10_80044220);
}

void func_ovl10_10_8004429C(s32 arg0) {
    D_ovl10_10_800470E8[D_ovl10_10_800471E8] = arg0;
}

void func_ovl10_10_80044280(void (*arg0)(void)) {
    D_ovl10_10_800471F0[D_ovl10_10_800471E8] = arg0;
}

void func_ovl10_10_80044220(void) {
    func_ovl10_10_80046518(0x1F);
    func_ovl10_10_800465E0();
    func_ovl10_10_80045E68(0);
    func_ovl10_10_8004417C();
    func_ovl10_10_80046A40(0x402);
    func_ovl10_10_80045DE8(0);
    func_ovl10_10_80045DE0(1);
}

void func_ovl10_10_80044198(void) {
    s32 hit;
    Vec3f pos;

    hit = func_ovl10_10_80046628(D_ovl10_10_800474E4, 0x40);
    if (hit != 0 && D_ovl10_10_800474F0 == 0) {
        if (hit & 0x6000) {
            func_ovl10_10_8004304C(func_ovl10_10_800445E4);
            func_ovl10_10_8004417C();
        } else {
            func_ovl10_10_80046748(D_ovl10_10_800474E4, &pos);
            func_ovl10_10_80046D78(0x26, &pos);
        }
    }
}

void func_ovl10_10_8004417C(void) {
    D_ovl10_10_800471F0[D_ovl10_10_800471E8] = NULL;
}

void func_ovl10_10_800440A4(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl10_10_80043EF4();
            break;
        case 16:
            func_ovl10_10_800439E4();
            break;
        case 17:
            func_ovl10_10_80043940();
            break;
        case 4:
            func_ovl10_10_800437BC();
            break;
        case 5:
            func_ovl10_10_80043764();
            break;
        case 0x50:
            func_ovl10_10_800436E8();
            break;
        case 1:
            func_ovl10_10_80043018();
            break;
    }
}

void func_ovl10_10_80043EF4(void) {
    func_ovl10_10_80046B30(D_ovl10_10_80046F88);
    func_ovl10_10_80046CD8(0, 0, 0xDE);
    func_ovl10_10_80046CD8(1, 0x11, 0xEF);
    func_ovl10_10_80046CD8(2, 0x1A, 0xF8);
    func_ovl10_10_80046CD8(3, 0x1B, 0xF9);
    func_ovl10_10_80046CD8(4, 0x18, 0xF6);
    func_ovl10_10_80045C78(0x1EF);
    func_ovl10_10_80045C80(0xC7, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_10_80045C90(0x1F7);
    func_ovl10_10_80046B08(0x3C6, 0x3E8, 0, 0xFF, 0xFF);
    func_ovl10_10_80046B18(0, 0xFF, 0xFF);
    func_ovl10_10_80045E28();
    func_ovl10_10_80043D88(D_ovl10_10_80046FAC);
    func_ovl10_10_80045D60(func_ovl10_10_800454C8);
    func_ovl10_10_80043BF0();
    if (func_ovl10_10_80046A50(0x402) == 0) {
        func_ovl10_10_80043AAC();
    } else {
        func_ovl10_10_80045D28(0xE, 1, 0xE, 0xF, 0x11, 1);
        func_ovl10_10_80045D28(0xE, 2, 0xE, 0xF, 0x11, 1);
        func_ovl10_10_80043A0C(0x28, 0x2E, 2, 0x10);
    }
    D_ovl10_10_800474F0 = 0;
}

void func_ovl10_10_800439E4(void) {
    func_ovl10_10_80045E30(0x18, 2, 0x10);
}

void func_ovl10_10_80043940(void) {
    D_ovl10_10_80047374 = 0;
    D_ovl10_10_800473EC = 0;
    D_ovl10_10_800474C8 = -1100.0f;
    D_ovl10_10_800474CC = 90.0f;
    D_ovl10_10_800473F0 = 1;
    D_ovl10_10_800473F4 = 0xF;
    D_ovl10_10_800474D0 = 21.0f;
    D_ovl10_10_800474D4 = -0.2f;
    D_ovl10_10_800474D8 = 50.0f;
    D_ovl10_10_800474DC = 50.0f;
    func_ovl10_10_800437DC();
    D_ovl10_10_800470DC = 1;
}

void func_ovl10_10_800437DC(void) {
    f32 y;

    D_ovl10_10_800474E0 = -1.0f;
    y = func_ovl10_10_80045D18(D_ovl10_10_800473EC);
    func_ovl10_10_80045E30(D_ovl10_10_800473F0, D_ovl10_10_800473EC, D_ovl10_10_800473F4);
    func_ovl10_10_80045E68(1);
    D_ovl10_10_800473E8 = func_ovl10_10_80045EB8(func_ovl10_10_80045E58());
    D_ovl10_10_800473E8->unk70 = 0.0f;
    D_ovl10_10_800473E8->unk40->unk10 += D_ovl10_10_800474D8;
    D_ovl10_10_800473E8->unk40->unk14 += D_ovl10_10_800474C8;
    D_ovl10_10_800473E8->unk40->unk18 += D_ovl10_10_800474DC;
    D_ovl10_10_800473E8->unk40->unk20 = D_ovl10_10_800474CC;
    D_ovl10_10_800473D0[D_ovl10_10_80047374]->unk40->unk14 += D_ovl10_10_800474C8;
    func_ovl10_10_800430C4(D_ovl10_10_80047374, D_ovl10_10_800474D0, D_ovl10_10_800474D4, y);
    D_ovl10_10_800473E8->unk70 = 1.6333334f;
}

void func_ovl10_10_800437BC(void) {
    func_ovl10_10_80045E88();
}

void func_ovl10_10_80043764(void) {
    if (D_ovl10_10_800470DC == 1) {
        func_ovl10_10_800467E8(0x78);
        func_ovl10_10_80045E78(0x40, 3, 8.5f, 2, 0, 1, 1);
    }
}

void func_ovl10_10_800436E8(void) {
    func_ovl10_10_800436E0();
    if (func_ovl10_10_80045E40(0x2E, 0xE, 0x2F, 0x11) != 0) {
        func_ovl10_10_80046C28(D_ovl10_10_800470C0);
        func_ovl10_10_800436A4(0x27);
        func_ovl10_10_80046C58();
        func_ovl10_10_80045E90(1);
        func_ovl10_10_80045D98();
    } else {
        D_ovl10_10_800474F0 = 1;
    }
    func_ovl10_10_800433D4(1);
}

static void func_ovl10_10_800436E0(void) {
}

void func_ovl10_10_800436A4(s32 arg0) {
    s32 *p;

    p = func_ovl10_10_80046A60(arg0);
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

s32 func_ovl10_10_800433D4(s32 arg0) {
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    if (arg0 == 2) {
        do {
            if (D_ovl10_10_80047400[i] == 2 && D_ovl10_10_80047418[i] == 1 &&
                func_ovl10_10_80045E48(D_ovl10_10_80047388[i][0], D_ovl10_10_80047388[i][1],
                                       D_ovl10_10_80047388[i][2], D_ovl10_10_80047388[i][0] + 1,
                                       D_ovl10_10_80047388[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_10_80047448 && found == 0);
        if (found) {
            D_ovl10_10_80047374 = i;
            if (D_ovl10_10_80047450[i] < D_ovl10_10_80047388[i][1]) {
                D_ovl10_10_800474D0 = 0.0f;
                D_ovl10_10_800474D4 = -0.2f;
            } else {
                D_ovl10_10_800474D0 = -0.0f;
                D_ovl10_10_800474D4 = 0.2f;
            }
        }
    } else {
        do {
            if (func_ovl10_10_80045E48(D_ovl10_10_80047388[i][0], D_ovl10_10_80047388[i][1],
                                       D_ovl10_10_80047388[i][2], D_ovl10_10_80047388[i][0] + 1,
                                       D_ovl10_10_80047388[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_10_80047448 && found == 0);
    }
    if (found) {
        D_ovl10_10_80047374 = i;
        if (D_ovl10_10_80047450[i] < D_ovl10_10_80047388[i][1]) {
            D_ovl10_10_800474D0 = 0.0f;
            D_ovl10_10_800474D4 = -0.2f;
        } else {
            D_ovl10_10_800474D0 = -0.0f;
            D_ovl10_10_800474D4 = 0.2f;
        }
        if (arg0 == 2) {
            func_ovl10_10_80043298();
        } else {
            D_ovl10_10_800473F8 = D_ovl10_10_80047468[i];
            D_ovl10_10_800473FC = D_ovl10_10_80047480[i];
            func_ovl10_10_800431AC();
        }
    }
    return found;
}

void func_ovl10_10_80043298(void) {
    s32 out[6];
    f32 a;
    f32 b;
    s32 i;

    i = D_ovl10_10_80047374;
    a = func_ovl10_10_80045D18(D_ovl10_10_80047450[i]);
    b = func_ovl10_10_80045D18(D_ovl10_10_80047388[i][1]);
    func_ovl10_10_80045EA0(0x40);
    func_ovl10_10_80045E90(1);
    D_ovl10_10_800473E8 = func_ovl10_10_80045EB8(func_ovl10_10_80045E58());
    D_ovl10_10_800474E0 = (a - b) * 0.5f;
    D_ovl10_10_800474E0 += b;
    D_ovl10_10_800473E8->unk70 = 0.0f;
    func_ovl10_10_80045CD0(D_ovl10_10_800473E8->unk40->unk10, D_ovl10_10_800473E8->unk40->unk14,
                           D_ovl10_10_800473E8->unk40->unk18, out, 2);
    func_ovl10_10_80045E68(1);
    func_ovl10_10_80046540(10.0f);
    func_ovl10_10_80046548(5.0f);
    func_ovl10_10_80046560(0.0f);
    func_ovl10_10_800430C4(i, D_ovl10_10_800474D0, D_ovl10_10_800474D4, a);
}

void func_ovl10_10_800431AC(void) {
    s32 out[6];
    s32 pad1;
    s32 pad2;
    s32 pad3;

    D_ovl10_10_800474E0 = -1.0f;
    func_ovl10_10_80045EA0(0x40);
    func_ovl10_10_80045E90(1);
    D_ovl10_10_800473E8 = func_ovl10_10_80045EB8(func_ovl10_10_80045E58());
    D_ovl10_10_800473E8->unk70 = 0.0f;
    func_ovl10_10_80045CD0(D_ovl10_10_800473E8->unk40->unk10, D_ovl10_10_800473E8->unk40->unk14,
                           D_ovl10_10_800473E8->unk40->unk18, out, 2);
    func_ovl10_10_80045CB0(out[0], out[1], out[2], 0);
    func_ovl10_10_80045E68(1);
    func_ovl10_10_800430C4(D_ovl10_10_80047374, D_ovl10_10_800474D0, D_ovl10_10_800474D4, -1.0f);
    func_ovl10_10_800467E8(0x78);
    D_ovl10_10_800470C4 = D_ovl10_10_800473F8;
    D_ovl10_10_800470C8 = D_ovl10_10_800473FC;
    func_ovl10_10_80045D70(D_ovl10_10_800473F8, D_ovl10_10_800473FC, 0);
}

void func_ovl10_10_800430C4(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_ovl10_10_80047374 = arg0;
    D_ovl10_10_80047378 = arg1;
    D_ovl10_10_8004737C = arg2;
    D_ovl10_10_80047380 = arg3;
    func_ovl10_10_8004304C(func_ovl10_10_80044CA0);
    D_ovl10_10_800473E8 = func_ovl10_10_80045EB8(func_ovl10_10_80045E58());
    D_ovl10_10_800473E8->unk70 = 0.0f;
    func_ovl10_10_80045D30(1);
    if (arg1 == 0.0f && arg2 < 0.0f && arg3 == -1.0f) {
        func_ovl10_10_80045ED0(1);
    }
    func_ovl10_10_80046D50(0x98);
    func_ovl10_10_80045DE0(0);
}

void func_ovl10_10_80043044(void) {
}

void func_ovl10_10_80043018(void) {
    func_ovl10_10_80046AC8(0, 0, 0, 0.0f);
}

void func_ovl10_10_80043010(void) {
}
