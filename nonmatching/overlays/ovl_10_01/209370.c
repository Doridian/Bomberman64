/*
 * NON_MATCHING: ovl_10_01's game object, complete: every function and its
 * .data/.bss/.rodata (sizes 0x1A0/0x140/0x520 and their bytes as the
 * original; .text 0x29C0 as the original). Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 29, eu 29, jp 29
 *
 * What still differs in us (words; eu and jp the same): the three
 * functions ovl_10_03's draft (210390.c) has left, with the same code and
 * the same differences there.
 * - func_ovl10_01_80044154 (14): only stack offsets. Its four Vec3f sit 12
 *   bytes higher than the original's (player at sp+0xE8, not 0xDC); the
 *   original has 0x10 free above them and 0x10 below.
 * - func_ovl10_01_800445F8 (11): case 10 stores v.y (0.0f) before loading
 *   v.x, where the original loads v.x first and stores v.y in the jal's
 *   way.
 * - func_ovl10_01_80044A10 (4): the three Vec3f are 8 bytes higher than
 *   the original's in the same 0x70 frame.
 *
 * ovl_10_01's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse, each one after the ones it
 * calls that aren't out yet, last call first; unreferenced statics go to
 * the end). From 80043E14 on it is ovl_10_03's object (80043870 and
 * 80043294 are its 800453C8 and 8004566C, emitted early here because
 * 80043AB8 and 800432DC call them); the task functions (80043484,
 * 800445DC, 800456E8-800457DC, with the strings "trap task:entry failed"
 * and "task_entry>%d:%s") are in every one of bank 0x10's overlays.
 * 80043900 is defined first, as in ovl_10_05: its initializers come first
 * in .data. 80043484 is defined above its caller 800457A4 (only so does
 * its string come first in .rodata). The empty statics 800430F0, 800431FC
 * and 8004347C are inlined into 800430F8, 80043204 and 80043484, and still
 * emitted just before them. The handler 80043C1C inlines 80043018,
 * 80043060, 8004337C and 8004345C; 800432DC inlines 80043294; 80043AB8
 * inlines 80043768. D_ovl10_01_80047100 is .data no function reads, and
 * the handler's table D_ovl10_01_80047188 ends in one word, not a record.
 */

#include "common.h"

/* What func_ovl10_01_80046830 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl10_01_80046830;

/* What func_ovl10_01_800468F0 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_01_80047540;

void func_ovl10_01_800459D8(const char *, ...);
void func_ovl10_01_80045D18(s32);
void func_ovl10_01_80045D20(s32, f32, f32, f32, s32, s32);
void func_ovl10_01_80045D30(s32);
f32 func_ovl10_01_80045DD8(UnkStructA_40 *);
void func_ovl10_01_80045DE0(s32);
void func_ovl10_01_80045E00(void (*)(UnkStructA *));
void func_ovl10_01_80045E10(s32, s32, s32);
void func_ovl10_01_80045E50(void (*)(UnkStructA *));
void func_ovl10_01_80045EC8(void);
void func_ovl10_01_80045ED0(s32, s32, s32);
s32 func_ovl10_01_80045EE0(s32, s32, s32, s32);
s32 func_ovl10_01_80045EF8(void);
void func_ovl10_01_80045F10(s32);
void func_ovl10_01_80045F18(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_01_80045F28(void);
UnkStructA *func_ovl10_01_80045F58(s32);
void func_ovl10_01_80045F60(s32);
void func_ovl10_01_80046440(UnkStructA_40 *, s32, s32);
f32 func_ovl10_01_80046458(UnkStructA_40 *, s32);
void func_ovl10_01_80046470(UnkStructA_40 *, s32, s32);
void func_ovl10_01_80046558(f32, f32, f32);
void func_ovl10_01_80046578(f32, f32, f32);
void func_ovl10_01_80046580(f32 *, f32 *, f32 *);
void func_ovl10_01_800465C0(s32);
f32 func_ovl10_01_800466C0(Vec3f *, Vec3f *);
s32 func_ovl10_01_800466C8(UnkStructA *, s32);
void func_ovl10_01_80046718(void *, s32);
void func_ovl10_01_80046720(UnkStructA *, s32);
void func_ovl10_01_80046730(UnkStructA *);
UnkStructA *func_ovl10_01_80046740(s32, s32, s32, s32);
void *func_ovl10_01_80046770(s32, s32, UnkStructA *);
void func_ovl10_01_80046798(UnkStructA *);
void func_ovl10_01_800467E8(UnkStructA *, Vec3f *);
UnkStruct_ovl10_01_80046830 *func_ovl10_01_80046830(UnkStructA *, s32);
void func_ovl10_01_80046868(void (*)(void), s32, s32, s32, s32);
void func_ovl10_01_80046888(s32);
void func_ovl10_01_800468B0(void);
UnkStruct_ovl10_01_80047540 *func_ovl10_01_800468F0(void);
void func_ovl10_01_80046900(UnkStruct_ovl10_01_80047540 *, s32);
f32 func_ovl10_01_80046A10(f32);
s32 func_ovl10_01_80046A28(s32);
s32 *func_ovl10_01_80046B00(void);
void func_ovl10_01_80046B68(s32, s32, s32, f32);
void func_ovl10_01_80046B90(s32, s32, s32);
void func_ovl10_01_80046BD0(u32 *);
void func_ovl10_01_80046CB8(s32, f32, f32, f32, s32);
void func_ovl10_01_80046CC0(s32, Vec3f *, s32);
void func_ovl10_01_80046D60(UnkStructA *, s32, f32, s32 (*)(s32));
void func_ovl10_01_80046D78(s32, s32, s32);
void func_ovl10_01_80046DF0(s32);
void func_ovl10_01_80046E10(s32, f32, f32, f32);
s32 func_ovl10_01_80045F80(void);
s32 func_ovl10_01_80045FE0(s32);
void func_ovl10_01_80046420(UnkStructA_40 *, s32);
void func_ovl10_01_80046428(UnkStructA_40 *, s32, s32, s32);
void func_ovl10_01_800466A8(Vec3f *, Vec3f *, Vec3f *);
void func_ovl10_01_800466B0(Vec3f *, Vec3f *);
void func_ovl10_01_80046750(UnkStructA *);
f32 func_ovl10_01_80046A18(f32);
void func_ovl10_01_80046E18(s32, Vec3f *);
s32 func_ovl10_01_80045E18(void);
s32 *func_ovl10_01_80045E68(void);
void func_ovl10_01_80045E80(s32);
void func_ovl10_01_80045ED8(void *);
void func_ovl10_01_80045F00(s32, void *);
void func_ovl10_01_80045F08(s32);
void func_ovl10_01_80045F20(const char *);
void func_ovl10_01_80045FB8(s32);
void func_ovl10_01_800465D0(s32);
void func_ovl10_01_80046878(void);
void func_ovl10_01_80046D98(s32);
void func_ovl10_01_80046F68(void);
void func_ovl10_01_80046F70(void);

void func_ovl10_01_80043010(void);
void func_ovl10_01_800430F8(void);
void func_ovl10_01_80043018(void);
void func_ovl10_01_80043060(void);
void func_ovl10_01_800430A8(void);
void func_ovl10_01_800433AC(void);
void func_ovl10_01_80043404(void);
void func_ovl10_01_80043154(void);
void func_ovl10_01_80043204(void);
void func_ovl10_01_80043294(f32);
void func_ovl10_01_800432DC(void);
void func_ovl10_01_8004337C(void);
void func_ovl10_01_8004345C(void);
s32 func_ovl10_01_80043484(void (*)(void));
void func_ovl10_01_800434FC(void);
void func_ovl10_01_80043590(void);
void func_ovl10_01_800435D8(void);
void func_ovl10_01_80043768(void);
void func_ovl10_01_80043794(void);
void func_ovl10_01_800437F4(void);
void func_ovl10_01_80043870();
void func_ovl10_01_80043900(void);
void func_ovl10_01_80043AB8(void);
void func_ovl10_01_80043C1C(s32);
void func_ovl10_01_80043D60(void);
void func_ovl10_01_80043DA4(void);
void func_ovl10_01_80043E14(s32);
void func_ovl10_01_80043EA8(s32, s32);
void func_ovl10_01_80043F6C(s32);
void func_ovl10_01_80044014(s32);
void func_ovl10_01_80044154(void);
void func_ovl10_01_800445DC(void);
void func_ovl10_01_800445F8(void);
void func_ovl10_01_80044A10(void);
void func_ovl10_01_80044B04(UnkStructA *);
void func_ovl10_01_80044B24(s32);
void func_ovl10_01_80044C84(void);
void func_ovl10_01_80044EDC(s32);
void func_ovl10_01_80045124(void);
void func_ovl10_01_80045260(UnkStructA *);
s32 func_ovl10_01_800455A4(s32);
void func_ovl10_01_800455C0(UnkStructA *);
void func_ovl10_01_80045640(UnkStructA *);
void func_ovl10_01_800456AC(void);
void func_ovl10_01_800456E8(void (*)(void));
void func_ovl10_01_80045704(s32);
void func_ovl10_01_80045720(s32);
s32 func_ovl10_01_80045734(void (*)(void));
void func_ovl10_01_80045778(void (*)(void));
s32 func_ovl10_01_800457A4(void (*)(void), const char *);
void func_ovl10_01_800457DC(void);
void func_ovl10_01_800458D8(s32, UnkStructA *);
void func_ovl10_01_8004590C(f32, f32, f32);
void func_ovl10_01_80045968(void);
void func_ovl10_01_80045980(void);

static void func_ovl10_01_800430F0(void);
static void func_ovl10_01_800431FC(void);
static void func_ovl10_01_8004347C(void);

/* D_ovl10_01_80047100's records */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC[6];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34[4];
} UnkStruct_ovl10_01_80047100;

/* .bss */
u8 D_ovl10_01_800472F0[0x10];
u8 D_ovl10_01_80047300[0xC];
s32 D_ovl10_01_8004730C;
u8 D_ovl10_01_80047310[0x4]; /* unused (func_ovl10_01_80045980) */
s32 D_ovl10_01_80047314;
s32 D_ovl10_01_80047318;
u8 D_ovl10_01_8004731C[0x4]; /* unused (func_ovl10_01_80045980) */
Vec3f D_ovl10_01_80047320;
s32 D_ovl10_01_8004732C;
s32 D_ovl10_01_80047330;
u8 D_ovl10_01_80047334[0x4]; /* unused (func_ovl10_01_80045980) */
/* the tasks: a countdown and a function each */
s32 D_ovl10_01_80047338[64];
s32 D_ovl10_01_80047438; /* the running task */
u8 D_ovl10_01_8004743C[0x4]; /* unused (func_ovl10_01_80045980) */
void (*D_ovl10_01_80047440[64])(void);
UnkStruct_ovl10_01_80047540 *D_ovl10_01_80047540;
u8 D_ovl10_01_80047544[0x4]; /* unused (func_ovl10_01_80045980) */
UnkStructA *D_ovl10_01_80047548[8];
UnkStructA *D_ovl10_01_80047568[8];
void *D_ovl10_01_80047588[8];
s32 D_ovl10_01_800475A8;
u8 D_ovl10_01_800475AC[0x4]; /* unused (func_ovl10_01_80045980) */
s32 D_ovl10_01_800475B0[8];
s32 D_ovl10_01_800475D0[8];
s32 D_ovl10_01_800475F0[8];
UnkStructA *D_ovl10_01_80047610[2];
UnkStructA *D_ovl10_01_80047618[2];
UnkStructA *D_ovl10_01_80047620[2];
Vec3f D_ovl10_01_80047628[2];
s32 D_ovl10_01_80047640[2];
s32 D_ovl10_01_80047648[2];
s32 D_ovl10_01_80047650[2];
s32 D_ovl10_01_80047658[2];
s32 D_ovl10_01_80047660[2];
s32 D_ovl10_01_80047668[64]; /* per task: which of the two */
f32 D_ovl10_01_80047768[2][10];
f32 D_ovl10_01_800477B8[2][10];
s32 *D_ovl10_01_80047808;

/* the first .data: its initializers */
void func_ovl10_01_80043900(void) {
    s32 i;
    f32 xs[8] = { 1150.0f, 2060.0f, 2660.0f, 3550.0f, 1160.0f, 2070.0f, 2660.0f, 3550.0f };
    f32 zs[2] = { 770.0f, 2330.0f };

    for (i = 0; i < 8; i++) {
        D_ovl10_01_80047548[i] = func_ovl10_01_80046740(0x1FE, 0x01080000, 0xD0, 0);
        D_ovl10_01_80047548[i]->unk40->unk10 = xs[i];
        D_ovl10_01_80047548[i]->unk40->unk14 = 1240.0f;
        D_ovl10_01_80047548[i]->unk40->unk18 = zs[i / 4];
        D_ovl10_01_80047548[i]->unk40->unkC |= 0x8000;
        func_ovl10_01_80046718(D_ovl10_01_80047548[i], 0x80000);
        func_ovl10_01_80046420(D_ovl10_01_80047548[i]->unk40, 1);
        func_ovl10_01_80046428(D_ovl10_01_80047548[i]->unk40, 0x1FF, 0, 0);
    }
}

/* .data */
s32 D_ovl10_01_80047038[8] = { 0, 5, 4, 1, 2, 7, 6, 3 };
s32 D_ovl10_01_80047058[8] = { 0, 20, 20, 10, 20, 20, 20, 30 };
s32 D_ovl10_01_80047078[8] = { 90, 190, 310, 350, 480, 580, 780, 940 };
extern u32 D_ovl10_01_80047188[];

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_01_800459C8(void) {
}

static void func_ovl10_01_800459C0(void) {
}

static void func_ovl10_01_800459B8(void) {
}

static void func_ovl10_01_800459B0(void) {
}

static void func_ovl10_01_800459A8(void) {
}

static void func_ovl10_01_800459A0(void) {
}

static void func_ovl10_01_80045998(void) {
}

static void func_ovl10_01_80045990(void) {
}

static void func_ovl10_01_80045988(void) {
}

void func_ovl10_01_80045980(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_01_80047310[0] = D_ovl10_01_8004731C[0] + D_ovl10_01_80047334[0] + D_ovl10_01_8004743C[0] +
                                 D_ovl10_01_80047544[0] + D_ovl10_01_800475AC[0];
    }
}

void func_ovl10_01_80045968(void) {
    D_ovl10_01_80047314 = -1;
    D_ovl10_01_80047318 = -1;
}

void func_ovl10_01_8004590C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_01_80046558(D_ovl10_01_80047320.x, D_ovl10_01_80047320.y, D_ovl10_01_80047320.z);
    func_ovl10_01_80046578(arg0, arg1, arg2);
    func_ovl10_01_80046888(180);
}

void func_ovl10_01_800458D8(s32 arg0, UnkStructA *arg1) {
    func_ovl10_01_80046E10(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_01_800457DC(void) {
    s32 i;

    D_ovl10_01_8004732C = 0;
    D_ovl10_01_80047330 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_01_80047440[i] != NULL) {
                D_ovl10_01_80047438 = i;
                if (D_ovl10_01_80047338[i] == 0) {
                    D_ovl10_01_80047440[i]();
                } else {
                    D_ovl10_01_80047338[i]--;
                }
            }
        }
        D_ovl10_01_8004732C++;
        D_ovl10_01_8004732C &= 3;
        func_ovl10_01_800468B0();
    }
}

static void func_ovl10_01_8004347C(void) {
}

/* Defined above its caller 80045514: only so does its string come first in
 * .rodata (as in ovl_10_02). */
s32 func_ovl10_01_80043484(void (*arg0)(void)) {
    s32 found;
    s32 i;

    func_ovl10_01_8004347C();
    i = 0;
    found = -1;
    do {
        if (D_ovl10_01_80047440[i] == NULL) {
            D_ovl10_01_80047440[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_01_800459D8("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_01_800457A4(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_01_80043484(arg0);
    func_ovl10_01_800459D8("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_01_80045778(void (*arg0)(void)) {
    D_ovl10_01_80047440[func_ovl10_01_80045734(arg0)] = NULL;
}

s32 func_ovl10_01_80045734(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_01_80047440[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_01_80045720(s32 arg0) {
    D_ovl10_01_80047440[arg0] = NULL;
}

void func_ovl10_01_80045704(s32 arg0) {
    D_ovl10_01_80047338[D_ovl10_01_80047438] = arg0;
}

void func_ovl10_01_800456E8(void (*arg0)(void)) {
    D_ovl10_01_80047440[D_ovl10_01_80047438] = arg0;
}

void func_ovl10_01_800456AC(void) {
    s32 *p;

    p = func_ovl10_01_80046B00();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_01_80045640(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_01_800465C0(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_01_80046798(arg0);
        func_ovl10_01_800468B0();
    }
}

void func_ovl10_01_800455C0(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_01_80046B68(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_01_80046720(arg0, 0x01000000);
        func_ovl10_01_80046888(5);
        func_ovl10_01_80046B68(0, 0, 0, 0.0f);
        func_ovl10_01_800467E8(arg0, &pos);
        func_ovl10_01_80046CC0(12, &pos, 0);
    }
}

s32 func_ovl10_01_800455A4(s32 arg0) {
    s32 ret;

    ret = 0;
    if ((arg0 & 0xF) != 0xF) {
        ret = 1;
    }
    return ret;
}

void func_ovl10_01_80045260(UnkStructA *arg0) {
    s32 i;

    func_ovl10_01_800465C0(15);
    i = 0;
    func_ovl10_01_80046440(arg0->unk40, 0x11, 0);
    func_ovl10_01_80046470(arg0->unk40, 4, 12);
    func_ovl10_01_80046470(arg0->unk40, 5, 13);
    func_ovl10_01_80046CB8(0, arg0->unk40->unk10, arg0->unk40->unk14 + 100.0f, arg0->unk40->unk18, 0);
    arg0->unk68 = 40.0f;
    arg0->unk70 = 1.6333334f;
    func_ovl10_01_80046DF0(0x1E);
    while (TRUE) {
        func_ovl10_01_80046D60(arg0, 0, 0.0f, func_ovl10_01_800455A4);
        if (arg0->unk40->unk14 > 700.0f) {
            arg0->unk40->unk14 = 700.0f;
            arg0->unk68 = 0.0f;
            arg0->unk6C = 0.0f;
        }
        arg0->unk40->unk1C += 20.0f;
        if (arg0->unk40->unk1C >= 360.0f) {
            arg0->unk40->unk1C = 0.0f;
        }
        arg0->unk40->unk10 -= func_ovl10_01_80046A10(arg0->unk40->unk1C);
        func_ovl10_01_800468B0();
        if (++i >= 200) {
            break;
        }
        if (arg0->unk40->unk14 < 700.0f && arg0->unk6C == 0.0f) {
            break;
        }
    }
    if (arg0->unk40->unk1C >= 90.0f && arg0->unk40->unk1C < 270.0f) {
        arg0->unk40->unk1C = 180.0f;
        arg0->unk40->unk14 = func_ovl10_01_80045DD8(arg0->unk40) + 70.0f;
    } else {
        arg0->unk40->unk1C = 0.0f;
        arg0->unk40->unk14 = func_ovl10_01_80045DD8(arg0->unk40);
    }
    func_ovl10_01_80046440(arg0->unk40, 0x13, 0);
    func_ovl10_01_80046720(arg0, 0x0C000000);
    arg0->unk40->unk48->unk4->unk8 |= 0x20;
    arg0->unk40->unk48->unk4->unk8 |= 0x40;
    arg0->unk40->unk48->unk4->unk4 = func_ovl10_01_80046458(arg0->unk40, 0) - 0.1f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl10_01_80046888(0x50);
}

void func_ovl10_01_80045124(void) {
    s32 i;

    if (D_ovl10_01_800475A8 == 180) {
        for (i = 0; i < 8; i++) {
            if (D_ovl10_01_80047058[i] != 0) {
                D_ovl10_01_800475B0[i] = func_ovl10_01_80046A28(D_ovl10_01_80047058[i]) + D_ovl10_01_80047078[i] + 180;
            } else {
                D_ovl10_01_800475B0[i] = D_ovl10_01_80047078[i] + 180;
            }
        }
    }
    if (D_ovl10_01_800475A8 >= 180) {
        for (i = 0; i < 8; i++) {
            if (D_ovl10_01_800475A8 == D_ovl10_01_800475B0[i]) {
                func_ovl10_01_80044EDC(D_ovl10_01_80047038[i]);
            }
        }
    }
    func_ovl10_01_80044C84();
    D_ovl10_01_800475A8++;
    if (D_ovl10_01_800475A8 == 1180) {
        D_ovl10_01_800475A8 = 180;
    }
}

void func_ovl10_01_80044EDC(s32 arg0) {
    s32 i;
    s32 sp54[2] = { 0xAB, 0xAC };
    s32 sp4C[2] = { 0xB8, 0xB9 };
    f32 sp2C[8] = { 700.0f, 1800.0f, 1300.0f, 2400.0f, 1150.0f, 2250.0f, 850.0f, 1950.0f };

    for (i = 0; i < 8; i++) {
        if (D_ovl10_01_80047568[i] == NULL) {
            D_ovl10_01_80047568[i] = func_ovl10_01_80046740(sp54[(s32)(arg0 * 0.25f)], 0x01000070, 0x30, 0);
            D_ovl10_01_80047568[i]->unk40->unk10 = -1600.0f;
            D_ovl10_01_80047568[i]->unk40->unk14 = 100.0f;
            D_ovl10_01_80047568[i]->unk40->unk18 = sp2C[arg0];
            D_ovl10_01_800475D0[i] = arg0;
            if ((s32)(arg0 * 0.25f) == 0) {
                D_ovl10_01_80047568[i]->unk30 = 1;
                D_ovl10_01_80047568[i]->unk34 = 150.0f;
                D_ovl10_01_80047568[i]->unk38 = 120.0f;
            } else {
                D_ovl10_01_80047568[i]->unk30 = 8;
                D_ovl10_01_80047568[i]->unk34 = 300.0f;
                D_ovl10_01_80047568[i]->unk38 = 1600.0f;
            }
            D_ovl10_01_80047588[i] = func_ovl10_01_80046770(sp4C[(s32)(arg0 * 0.25f)], 0x01200000, D_ovl10_01_80047568[i]);
            func_ovl10_01_80046718(D_ovl10_01_80047588[i], 0x80000);
            D_ovl10_01_800475F0[i] = 0;
            break;
        }
    }
}

void func_ovl10_01_80044C84(void) {
    s32 i;
    UnkStruct_ovl10_01_80046830 *p;
    s32 pad; /* unused: the original's frame has the slot */
    f32 x;

    for (i = 0; i < 8; i++) {
        if (D_ovl10_01_80047568[i] != NULL && D_ovl10_01_800475A8 % 2 == i % 2) {
            func_ovl10_01_80044B24(i);
            if (D_ovl10_01_800475D0[i] < 4) {
                x = D_ovl10_01_80047568[i]->unk40->unk10;
                D_ovl10_01_80047568[i]->unk40->unk10 = x + 42.5f;
            } else {
                D_ovl10_01_80047568[i]->unk40->unk10 += 34.0f;
            }
            p = func_ovl10_01_80046830(D_ovl10_01_80047568[i], 7);
            if (p != NULL) {
                if (p->unk8 & 1) {
                    p->unk10 = 0x20;
                }
                if (p->unk8 & 4) {
                    p->unk10 = 0x40;
                }
                if (p->unk8 & 2) {
                    p->unk10 = 0x20;
                }
            }
            if (D_ovl10_01_800475D0[i] < 4 && func_ovl10_01_800466C8(D_ovl10_01_80047568[i], 0x20) != 0) {
                D_ovl10_01_80047568[i]->unk40->unk10 = x;
            }
            if (D_ovl10_01_80047568[i]->unk40->unk10 > 5600.0f) {
                func_ovl10_01_80044B04(D_ovl10_01_80047568[i]);
                D_ovl10_01_80047568[i] = NULL;
            }
        }
    }
}

void func_ovl10_01_80044B24(s32 arg0) {
    Vec3f pos;
    Vec3f target;
    f32 dist;

    func_ovl10_01_800467E8(D_ovl10_01_80047568[arg0], &pos);
    if ((s32)(D_ovl10_01_800475D0[arg0] * 0.25f) == 1) {
        pos.x += 1600.0f;
    }
    func_ovl10_01_800467E8(func_ovl10_01_80045F58(func_ovl10_01_80045EF8()), &target);
    dist = func_ovl10_01_800466C0(&pos, &target);
    if (D_ovl10_01_800475F0[arg0] == 0 && dist <= 1000.0f) {
        D_ovl10_01_800475F0[arg0]++;
        if ((s32)(D_ovl10_01_800475D0[arg0] * 0.25f) == 0) {
            func_ovl10_01_80046DF0(0x92);
        } else {
            func_ovl10_01_80046DF0(0x93);
        }
    }
}

void func_ovl10_01_80044B04(UnkStructA *arg0) {
    func_ovl10_01_80046730(arg0);
}

void func_ovl10_01_80044A10(void) {
    Vec3f ang;
    Vec3f a;
    Vec3f b;
    s32 i;

    if (func_ovl10_01_80045F58(0)->unk40->unk14 == 700.0f) {
        for (i = 0; i < 2; i++) {
            if (D_ovl10_01_80047618[i] != NULL) {
                func_ovl10_01_800467E8(D_ovl10_01_80047610[i], &a);
                func_ovl10_01_800467E8(D_ovl10_01_80047618[i], &b);
                func_ovl10_01_800466A8(&a, &b, &ang);
                D_ovl10_01_80047610[i]->unk40->unk20 = ang.x;
            }
        }
    }
}

void func_ovl10_01_800445F8(void) {
    s32 n;
    Vec3f out;
    Vec3f pos;
    Vec3f v;
    UnkStruct_ovl10_01_80046830 *p;
    f32 x;
    f32 z;

    n = D_ovl10_01_80047668[D_ovl10_01_80047438];
    switch (D_ovl10_01_80047658[n]) {
        case 10:
            if (D_ovl10_01_80047640[n] & 4) {
                v.z = 70.0f;
                v.y = 0.0f;
                v.x = D_ovl10_01_80047610[n]->unk40->unk20;
                func_ovl10_01_800466B0(&v, &out);
                x = D_ovl10_01_80047610[n]->unk40->unk10 + out.x;
                z = D_ovl10_01_80047610[n]->unk40->unk18 + out.z;
                func_ovl10_01_80046CB8(0, x, D_ovl10_01_80047610[n]->unk40->unk14 + 115.0f, z, 0);
                D_ovl10_01_80047620[n] = func_ovl10_01_80046740(0x2D2, 0x11080040, 0xD0, 0);
                D_ovl10_01_80047620[n]->unk40->unk10 = D_ovl10_01_80047768[n][9];
                D_ovl10_01_80047620[n]->unk40->unk14 = D_ovl10_01_80047618[n]->unk40->unk14;
                D_ovl10_01_80047620[n]->unk40->unk18 = D_ovl10_01_800477B8[n][9];
                D_ovl10_01_80047620[n]->unk40->unk28 = 5.0f;
                D_ovl10_01_80047620[n]->unk40->unk2C = 5.0f;
                D_ovl10_01_80047620[n]->unk40->unk30 = 5.0f;
                D_ovl10_01_80047620[n]->unk30 = 1;
                D_ovl10_01_80047620[n]->unk34 = 10.0f;
                D_ovl10_01_80047620[n]->unk38 = 0.0f;
                p = func_ovl10_01_80046830(D_ovl10_01_80047620[n], 7);
                if (p != NULL) {
                    p->unk10 |= 0x40;
                    if (!(func_ovl10_01_80045F80() & 2) && func_ovl10_01_80045FE0(0) == 0) {
                        D_ovl10_01_80047330 = 1;
                    }
                }
                func_ovl10_01_800467E8(D_ovl10_01_80047620[n], &pos);
                func_ovl10_01_80046E18(0x95, &pos);
            }
            break;
        case 9:
            if (D_ovl10_01_80047620[n] != NULL) {
                D_ovl10_01_80047620[n]->unk40->unk28 = 5.0f;
                D_ovl10_01_80047620[n]->unk40->unk2C = 5.0f;
                D_ovl10_01_80047620[n]->unk40->unk30 = 5.0f;
            }
            break;
        case 8:
            if (D_ovl10_01_80047620[n] != NULL) {
                D_ovl10_01_80047620[n]->unk40->unk28 = 5.0f;
                D_ovl10_01_80047620[n]->unk40->unk2C = 5.0f;
                D_ovl10_01_80047620[n]->unk40->unk30 = 5.0f;
            }
            break;
        case 7:
            if (D_ovl10_01_80047620[n] != NULL) {
                func_ovl10_01_80046730(D_ovl10_01_80047620[n]);
                D_ovl10_01_80047620[n] = NULL;
            }
            break;
        case 0:
            D_ovl10_01_80047658[n] = 11;
            D_ovl10_01_80047650[n]--;
            break;
    }
    D_ovl10_01_80047658[n]--;
    if (D_ovl10_01_80047650[n] == 0 && (D_ovl10_01_80047640[n] & 4)) {
        D_ovl10_01_80047640[n] &= ~4;
        func_ovl10_01_80043EA8(n, 2);
    }
    if (D_ovl10_01_80047650[n] == 0) {
        func_ovl10_01_800445DC();
    }
}

void func_ovl10_01_800445DC(void) {
    D_ovl10_01_80047440[D_ovl10_01_80047438] = NULL;
}

void func_ovl10_01_80044154(void) {
    s32 pad;
    Vec3f player;
    Vec3f pos;
    Vec3f pos2;
    Vec3f ang;
    s32 i;
    s32 j;
    f32 dist;
    f32 speed;
    f32 a;

    func_ovl10_01_800467E8(func_ovl10_01_80045F58(0), &player);
    if (player.y == 700.0f || D_ovl10_01_80047330 != 0) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 9; j++) {
                D_ovl10_01_80047768[i][10 - j - 1] = D_ovl10_01_80047768[i][10 - j - 2];
                D_ovl10_01_800477B8[i][10 - j - 1] = D_ovl10_01_800477B8[i][10 - j - 2];
            }
            D_ovl10_01_80047768[i][0] = D_ovl10_01_80047618[i]->unk40->unk10;
            D_ovl10_01_800477B8[i][0] = D_ovl10_01_80047618[i]->unk40->unk18;
            func_ovl10_01_800467E8(D_ovl10_01_80047610[i], &pos);
            pos.y = 700.0f;
            if (func_ovl10_01_800466C0(&player, &pos) < 1500.0f) {
                if (!(D_ovl10_01_80047640[i] & 1)) {
                    func_ovl10_01_80044014(i);
                }
                func_ovl10_01_800467E8(D_ovl10_01_80047618[i], &pos);
                pos.y = 700.0f;
                func_ovl10_01_800466A8(&pos, &player, &ang);
                ang.y -= 90.0f;
                dist = func_ovl10_01_800466C0(&player, &pos);
                if (dist > 6.8f) {
                    speed = 6.8f;
                } else {
                    speed = dist;
                }
                if (dist < 1.0f) {
                    dist = 0.0f;
                }
                a = ang.x;
                D_ovl10_01_80047618[i]->unk40->unk10 += speed * func_ovl10_01_80046A10(a);
                D_ovl10_01_80047618[i]->unk40->unk18 += speed * func_ovl10_01_80046A18(a);
                if (D_ovl10_01_80047640[i] & 2) {
                    if (D_ovl10_01_80047648[i] > 0) {
                        D_ovl10_01_80047648[i]--;
                    }
                    if (D_ovl10_01_80047648[i] == 0 && !(D_ovl10_01_80047640[i] & 4)) {
                        func_ovl10_01_80043F6C(i);
                    }
                }
                if (dist == 0.0f && !(D_ovl10_01_80047640[i] & 2)) {
                    func_ovl10_01_80043EA8(i, 1);
                    if (!(D_ovl10_01_80047640[i] & 4)) {
                        D_ovl10_01_80047648[i] = 60;
                        D_ovl10_01_80047640[i] |= 2;
                        func_ovl10_01_800467E8(D_ovl10_01_80047610[i], &pos2);
                        func_ovl10_01_80046E18(0x94, &pos2);
                    }
                }
            } else if (D_ovl10_01_80047640[i] & 1) {
                func_ovl10_01_80043E14(i);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (D_ovl10_01_80047640[i] & 1) {
                func_ovl10_01_80043E14(i);
            }
        }
    }
}

void func_ovl10_01_80044014(s32 arg0) {
    s32 i;

    D_ovl10_01_80047618[arg0] = func_ovl10_01_80046740(0xCC, 0x11080000, 0x10, 0);
    D_ovl10_01_80047618[arg0]->unk40->unk10 = D_ovl10_01_80047628[arg0].x;
    D_ovl10_01_80047618[arg0]->unk40->unk14 = D_ovl10_01_80047628[arg0].y;
    D_ovl10_01_80047618[arg0]->unk40->unk18 = D_ovl10_01_80047628[arg0].z;
    D_ovl10_01_80047618[arg0]->unk40->unk36 = 0xC0;
    D_ovl10_01_80047640[arg0] |= 1;
    for (i = 0; i < 10; i++) {
        D_ovl10_01_80047768[arg0][i] = D_ovl10_01_80047628[arg0].x;
        D_ovl10_01_800477B8[arg0][i] = D_ovl10_01_80047628[arg0].z;
    }
}

void func_ovl10_01_80043F6C(s32 arg0) {
    D_ovl10_01_80047640[arg0] &= ~2;
    D_ovl10_01_80047650[arg0] = 4;
    D_ovl10_01_80047660[arg0] = 1;
    D_ovl10_01_80047658[arg0] = 10;
    D_ovl10_01_80047640[arg0] &= ~2;
    D_ovl10_01_80047640[arg0] |= 4;
    D_ovl10_01_80047620[arg0] = NULL;
    D_ovl10_01_80047668[func_ovl10_01_80043484(func_ovl10_01_800445F8)] = arg0;
}

void func_ovl10_01_80043EA8(s32 arg0, s32 arg1) {
    Vec3f pos;
    s32 id;

    if (arg1 == 1) {
        id = 0xCB;
    } else {
        id = 0xCC;
    }
    func_ovl10_01_800467E8(D_ovl10_01_80047618[arg0], &pos);
    func_ovl10_01_80046730(D_ovl10_01_80047618[arg0]);
    D_ovl10_01_80047618[arg0] = func_ovl10_01_80046740(id, 0x11080000, 0x10, 0);
    D_ovl10_01_80047618[arg0]->unk40->unk10 = pos.x;
    D_ovl10_01_80047618[arg0]->unk40->unk14 = pos.y;
    D_ovl10_01_80047618[arg0]->unk40->unk18 = pos.z;
    D_ovl10_01_80047618[arg0]->unk40->unk36 = 0xC0;
}

void func_ovl10_01_80043E14(s32 arg0) {
    D_ovl10_01_80047628[arg0].x = D_ovl10_01_80047618[arg0]->unk40->unk10;
    D_ovl10_01_80047628[arg0].y = D_ovl10_01_80047618[arg0]->unk40->unk14;
    D_ovl10_01_80047628[arg0].z = D_ovl10_01_80047618[arg0]->unk40->unk18;
    func_ovl10_01_80046730(D_ovl10_01_80047618[arg0]);
    D_ovl10_01_80047618[arg0] = NULL;
    D_ovl10_01_80047640[arg0] = 0;
}

void func_ovl10_01_80043DA4(void) {
    func_ovl10_01_800468B0();
    func_ovl10_01_80045F08(1);
    func_ovl10_01_80045E80(0);
    func_ovl10_01_80045FB8(1);
    func_ovl10_01_80045F20("WM1 WAP WG1 WSH WDW WB3 WDSW WB1 WDW WB3 M0 M0 ST30 M0 M0 ST20 M5 WB5");
    func_ovl10_01_80045FB8(0);
    func_ovl10_01_80045F20("WM1 WAP WG1 WSH WDW WB10");
    func_ovl10_01_80046888(10);
    func_ovl10_01_80046F68();
    func_ovl10_01_80046878();
}

void func_ovl10_01_80043D60(void) {
    func_ovl10_01_800468B0();
    func_ovl10_01_80046578(45.0f, 32768.0f, 32768.0f);
    func_ovl10_01_80046878();
}

void func_ovl10_01_80043C1C(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl10_01_80043AB8();
            break;
        case 16:
            func_ovl10_01_8004345C();
            break;
        case 17:
            func_ovl10_01_80043404();
            break;
        case 18:
            func_ovl10_01_800433AC();
            break;
        case 25:
            func_ovl10_01_8004337C();
            break;
        case 4:
            func_ovl10_01_800432DC();
            break;
        case 0x50:
            func_ovl10_01_80043154();
            break;
        case 1:
            func_ovl10_01_80043060();
            break;
        case 3:
            func_ovl10_01_80043018();
            break;
    }
}

void func_ovl10_01_80043AB8(void) {
    func_ovl10_01_80046BD0(D_ovl10_01_80047188);
    func_ovl10_01_80046D78(0, 0, 0xDE);
    func_ovl10_01_80046D78(1, 0x11, 0xEF);
    func_ovl10_01_80046D78(2, 0x1A, 0xF8);
    func_ovl10_01_80046D78(3, 0x1B, 0xF9);
    func_ovl10_01_80045D18(0x1D4);
    func_ovl10_01_80045D20(0x1D3, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_01_80045D20(0x1D5, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_01_80045D20(0x1D6, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_01_80045D20(0x1D7, 0.0f, 0.0f, 0.0f, 0x60, 0);
    func_ovl10_01_80043900();
    func_ovl10_01_80043870(0x1FD);
    func_ovl10_01_80045D30(0x1E1);
    func_ovl10_01_80045DE0(0xF);
    func_ovl10_01_80045EC8();
    func_ovl10_01_80045F10(0xC0);
    func_ovl10_01_800437F4();
    func_ovl10_01_80043794();
    func_ovl10_01_80043768();
    func_ovl10_01_80043590();
    func_ovl10_01_80045E00(func_ovl10_01_80045640);
}

void func_ovl10_01_80043870() {
    D_ovl10_01_80047540 = func_ovl10_01_800468F0();
    func_ovl10_01_80046900(D_ovl10_01_80047540, 0x20000001);
    D_ovl10_01_80047540->unk40 = 0.5f;
    D_ovl10_01_80047540->unk44 = D_ovl10_01_80047540->unk40 * 0.75f;
    D_ovl10_01_80047540->unk18 = 0.1f;
    D_ovl10_01_80047540->unk1C = -0.1f;
}

void func_ovl10_01_800437F4(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_01_80047440[i] = NULL;
        D_ovl10_01_80047338[i] = 0;
    }
    func_ovl10_01_80046868(func_ovl10_01_800457DC, 0, 0, 0, 0x110);
}
void func_ovl10_01_80043794(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_ovl10_01_80047568[i] = NULL;
    }
    D_ovl10_01_800475A8 = 0;
    func_ovl10_01_80045E50(func_ovl10_01_80045260);
    func_ovl10_01_80043484(func_ovl10_01_80045124);
}
void func_ovl10_01_80043768(void) {
    func_ovl10_01_800435D8();
    func_ovl10_01_80043484(func_ovl10_01_80044A10);
}
void func_ovl10_01_800435D8(void) {
    f32 xs[6] = { 1650.0f, 1650.0f, 1700.0f, 1700.0f, 1700.0f, 1700.0f };
    f32 zs[6] = { 400.0f, 2700.0f, 500.0f, 2600.0f, 500.0f, 2600.0f };
    s32 i;

    for (i = 0; i < 2; i++) {
        D_ovl10_01_80047610[i] = func_ovl10_01_80046740(0xB1, 0x01000010, 0x10, 0);
        D_ovl10_01_80047610[i]->unk40->unk10 = xs[i];
        D_ovl10_01_80047610[i]->unk40->unk14 = 900.0f;
        D_ovl10_01_80047610[i]->unk40->unk18 = zs[i];
        func_ovl10_01_80046750(D_ovl10_01_80047610[i]);
        if (i == 1) {
            D_ovl10_01_80047610[i]->unk40->unk20 = 180.0f;
        }
    }
}
void func_ovl10_01_800434FC(void) {
    s32 i;
    f32 dz[2] = { 500.0f, -500.0f };

    for (i = 0; i < 2; i++) {
        D_ovl10_01_80047628[i].x = D_ovl10_01_80047610[i]->unk40->unk10;
        D_ovl10_01_80047628[i].y = 710.0f;
        D_ovl10_01_80047628[i].z = D_ovl10_01_80047610[i]->unk40->unk18 + dz[i];
        D_ovl10_01_80047618[i] = NULL;
    }
}

/* .data no function reads: two 0x44-byte records */
UnkStruct_ovl10_01_80047100 D_ovl10_01_80047100[2] = {
    { 20, 1, 1, { 0 }, 4.5f, 0.0f, 0.0f, -0.24f },
    { 20, 1, 1, { 0 }, -4.5f, 0.0f, 0.0f, 0.24f },
};

/* passed to func_ovl10_01_80046BD0: three 12-byte records and an end
 * (one word, where ovl_10_02's has a whole record) */
u32 D_ovl10_01_80047188[] = {
    0xA70001, 0xE, 4,
    0xB70000, 0xE, 4,
    0xA50003, 0xF, 4,
    0,
};

void func_ovl10_01_80043590(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_ovl10_01_80047640[i] = 0;
    }
    func_ovl10_01_800434FC();
    func_ovl10_01_80043484(func_ovl10_01_80044154);
}

void func_ovl10_01_8004345C(void) {
    func_ovl10_01_80045F10(0xC0);
}

void func_ovl10_01_80043404(void) {
    func_ovl10_01_80045ED0(3, 1, 10);
    func_ovl10_01_80045F10(0x40);
    func_ovl10_01_80045F18(0x40, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_01_800433AC(void) {
    func_ovl10_01_80045ED0(3, 1, 21);
    func_ovl10_01_80045F10(0x40);
    func_ovl10_01_80045F18(0x40, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_01_8004337C(void) {
    func_ovl10_01_80045ED0(0x27, 1, 18);
    func_ovl10_01_80045F10(0xC0);
}

void func_ovl10_01_800432DC(void) {
    func_ovl10_01_80045F28();
    switch (func_ovl10_01_80045E18()) {
        case 16:
            func_ovl10_01_80046578(0.0f, 32768.0f, 32768.0f);
            break;
        case 17:
        case 18:
            func_ovl10_01_80043294(0.0f);
            break;
    }
    func_ovl10_01_80043204();
}

void func_ovl10_01_80043294(f32 arg0) {
    f32 sp1C;

    func_ovl10_01_80046580(&sp1C, NULL, NULL);
    func_ovl10_01_80046578(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_01_80043204(void) {
    func_ovl10_01_800431FC();
    D_ovl10_01_80047808 = func_ovl10_01_80045E68();
    if (*D_ovl10_01_80047808 & 2) {
        func_ovl10_01_80046868(func_ovl10_01_80043DA4, 0, 0, 0, 0x130);
        func_ovl10_01_80046868(func_ovl10_01_80043D60, 0, 0, 0, 0x130);
        func_ovl10_01_800465C0(0xF);
        func_ovl10_01_800465D0(2);
        func_ovl10_01_80046D98(0);
    }
}

static void func_ovl10_01_800431FC(void) {
}

void func_ovl10_01_80043154(void) {
    func_ovl10_01_80045F60(1);
    func_ovl10_01_800430F8();
    if (func_ovl10_01_80045EE0(1, 6, 3, 0xE) != 0) {
        D_ovl10_01_80047314 = 0x69;
        D_ovl10_01_80047318 = 0x11;
        func_ovl10_01_80045E10(0x69, 0x11, 0);
    }
    if (func_ovl10_01_80045EE0(1, 0x11, 3, 0x19) != 0) {
        D_ovl10_01_80047314 = 0x69;
        D_ovl10_01_80047318 = 0x12;
        func_ovl10_01_80045E10(0x69, 0x12, 0);
    }
}

void func_ovl10_01_800430F8(void) {
    s32 i;

    func_ovl10_01_800430F0();
    for (i = 0; i < 8; i++) {
        if (D_ovl10_01_80047548[i] != NULL) {
            func_ovl10_01_80046730(D_ovl10_01_80047548[i]);
            D_ovl10_01_80047548[i] = NULL;
        }
    }
}

static void func_ovl10_01_800430F0(void) {
}

void func_ovl10_01_800430A8(void) {
    D_ovl10_01_80047808 = func_ovl10_01_80045E68();
    if (*D_ovl10_01_80047808 & 2) {
        func_ovl10_01_80046F70();
    }
}

void func_ovl10_01_80043060(void) {
    D_ovl10_01_80047808 = func_ovl10_01_80045E68();
    if (*D_ovl10_01_80047808 & 2) {
        func_ovl10_01_80046F70();
    }
}

void func_ovl10_01_80043018(void) {
    D_ovl10_01_8004730C = func_ovl10_01_80045EF8();
    func_ovl10_01_80045ED8(D_ovl10_01_80047300);
    func_ovl10_01_80045F00(D_ovl10_01_8004730C, D_ovl10_01_800472F0);
}

void func_ovl10_01_80043010(void) {
}
