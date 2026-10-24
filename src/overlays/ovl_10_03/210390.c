#include "common.h"

/*
 * ovl_10_03's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse, each one after the ones it
 * calls that aren't out yet, last call first; unreferenced statics go to
 * the end). It shares ovl_10_02's functions (20D660.c) from 80044804 on,
 * and the task functions (80043334, 800442BC, 80045458-8004554C, with the
 * strings "trap task:entry failed" and "task_entry>%d:%s") are in every
 * one of bank 0x10's overlays. 800433AC is defined above its caller
 * 80043440 so that 80043334 comes out before it; 800431B4, 80043618,
 * 800442BC and 800447E4 are inlined into their callers and still emitted.
 * .data is in definition order: 80043720 is defined first (its
 * initializers come first, as in ovl_10_05) and D_ovl10_03_80046EB0 after
 * 800433AC, whose initializers it follows. 80043E34 and 800446F0 have an
 * unused local for the original's frame.
 */

/* What func_ovl10_03_800465E0 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl10_03_800465E0;

/* What func_ovl10_03_800466A0 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_03_80047200;

void func_ovl10_03_80045788(const char *, ...);
void func_ovl10_03_80045AC8(s32);
void func_ovl10_03_80045AD0(s32, f32, f32, f32, s32, s32);
void func_ovl10_03_80045AE0(s32);
f32 func_ovl10_03_80045B88(UnkStructA_40 *);
void func_ovl10_03_80045B90(s32);
void func_ovl10_03_80045BB0(void (*)(UnkStructA *));
void func_ovl10_03_80045BC0(s32, s32, s32);
void func_ovl10_03_80045C00(void (*)(UnkStructA *));
void func_ovl10_03_80045C78(void);
void func_ovl10_03_80045C80(s32, s32, s32);
s32 func_ovl10_03_80045C90(s32, s32, s32, s32);
s32 func_ovl10_03_80045CA8(void);
void func_ovl10_03_80045CC0(s32);
void func_ovl10_03_80045CC8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_03_80045CD8(void);
UnkStructA *func_ovl10_03_80045D08(s32);
void func_ovl10_03_80045D10(s32);
void func_ovl10_03_800461F0(UnkStructA_40 *, s32, s32);
f32 func_ovl10_03_80046208(UnkStructA_40 *, s32);
void func_ovl10_03_80046220(UnkStructA_40 *, s32, s32);
void func_ovl10_03_80046308(f32, f32, f32);
void func_ovl10_03_80046328(f32, f32, f32);
void func_ovl10_03_80046330(f32 *, f32 *, f32 *);
void func_ovl10_03_80046370(s32);
f32 func_ovl10_03_80046470(Vec3f *, Vec3f *);
s32 func_ovl10_03_80046478(UnkStructA *, s32);
void func_ovl10_03_800464C8(void *, s32);
void func_ovl10_03_800464D0(UnkStructA *, s32);
void func_ovl10_03_800464E0(UnkStructA *);
UnkStructA *func_ovl10_03_800464F0(s32, s32, s32, s32);
void *func_ovl10_03_80046520(s32, s32, UnkStructA *);
void func_ovl10_03_80046548(UnkStructA *);
void func_ovl10_03_80046598(UnkStructA *, Vec3f *);
UnkStruct_ovl10_03_800465E0 *func_ovl10_03_800465E0(UnkStructA *, s32);
void func_ovl10_03_80046618(void (*)(void), s32, s32, s32, s32);
void func_ovl10_03_80046638(s32);
void func_ovl10_03_80046660(void);
UnkStruct_ovl10_03_80047200 *func_ovl10_03_800466A0(void);
void func_ovl10_03_800466B0(UnkStruct_ovl10_03_80047200 *, s32);
f32 func_ovl10_03_800467C0(f32);
s32 func_ovl10_03_800467D8(s32);
s32 *func_ovl10_03_800468B0(void);
void func_ovl10_03_80046918(s32, s32, s32, f32);
void func_ovl10_03_80046940(s32, s32, s32);
void func_ovl10_03_80046980(u32 (*)[3]);
void func_ovl10_03_80046A68(s32, f32, f32, f32, s32);
void func_ovl10_03_80046A70(s32, Vec3f *, s32);
void func_ovl10_03_80046B10(UnkStructA *, s32, f32, s32 (*)(s32));
void func_ovl10_03_80046B28(s32, s32, s32);
void func_ovl10_03_80046BA0(s32);
void func_ovl10_03_80046BC0(s32, f32, f32, f32);
s32 func_ovl10_03_80045D30(void);
s32 func_ovl10_03_80045D90(s32);
void func_ovl10_03_800461D0(UnkStructA_40 *, s32);
void func_ovl10_03_800461D8(UnkStructA_40 *, s32, s32, s32);
void func_ovl10_03_80046458(Vec3f *, Vec3f *, Vec3f *);
void func_ovl10_03_80046460(Vec3f *, Vec3f *);
void func_ovl10_03_80046500(UnkStructA *);
f32 func_ovl10_03_800467C8(f32);
void func_ovl10_03_80046BC8(s32, Vec3f *);

void func_ovl10_03_80043010(void);
void func_ovl10_03_80043028(void);
void func_ovl10_03_80043084(void);
void func_ovl10_03_800431B4(void);
void func_ovl10_03_800431D4(void);
void func_ovl10_03_8004322C(void);
void func_ovl10_03_80043284(void);
void func_ovl10_03_800432DC(void);
s32 func_ovl10_03_80043334(void (*)(void));
void func_ovl10_03_800433AC(void);
void func_ovl10_03_80043440(void);
void func_ovl10_03_80043488(void);
void func_ovl10_03_80043618(void);
void func_ovl10_03_80043644(void);
void func_ovl10_03_800436A4(void);
void func_ovl10_03_80043720(void);
void func_ovl10_03_800438D8(void);
void func_ovl10_03_80043A30(s32);
void func_ovl10_03_80043AF4(s32);
void func_ovl10_03_80043B88(s32, s32);
void func_ovl10_03_80043C4C(s32);
void func_ovl10_03_80043CF4(s32);
void func_ovl10_03_80043E34(void);
void func_ovl10_03_800442BC(void);
void func_ovl10_03_800442D8(void);
void func_ovl10_03_800446F0(void);
void func_ovl10_03_800447E4(UnkStructA *);
void func_ovl10_03_80044804(s32);
void func_ovl10_03_80044964(void);
void func_ovl10_03_80044BBC(s32);
void func_ovl10_03_80044E04(void);
void func_ovl10_03_80044F40(UnkStructA *);
s32 func_ovl10_03_80045284(s32);
void func_ovl10_03_800452A0(UnkStructA *);
void func_ovl10_03_80045320(UnkStructA *);
void func_ovl10_03_8004538C(void);
void func_ovl10_03_800453C8(void);
void func_ovl10_03_80045458(void (*)(void));
void func_ovl10_03_80045474(s32);
void func_ovl10_03_80045490(s32);
s32 func_ovl10_03_800454A4(void (*)(void));
void func_ovl10_03_800454E8(void (*)(void));
s32 func_ovl10_03_80045514(void (*)(void), const char *);
void func_ovl10_03_8004554C(void);
void func_ovl10_03_80045638(s32, UnkStructA *);
void func_ovl10_03_8004566C(f32);
void func_ovl10_03_800456B4(f32, f32, f32);
void func_ovl10_03_80045710(void);
void func_ovl10_03_80045728(void);

static void func_ovl10_03_80043018(void);
static void func_ovl10_03_80043020(void);
static void func_ovl10_03_800431AC(void);

/* .bss */
u8 D_ovl10_03_80046FB0[0x24];
s32 D_ovl10_03_80046FD4;
s32 D_ovl10_03_80046FD8;
u8 D_ovl10_03_80046FDC[0x4]; /* unused (func_ovl10_03_80045728) */
Vec3f D_ovl10_03_80046FE0;
s32 D_ovl10_03_80046FEC;
s32 D_ovl10_03_80046FF0;
u8 D_ovl10_03_80046FF4[0x4]; /* unused (func_ovl10_03_80045728) */
/* the tasks: a countdown and a function each */
s32 D_ovl10_03_80046FF8[64];
s32 D_ovl10_03_800470F8; /* the running task */
u8 D_ovl10_03_800470FC[0x4]; /* unused (func_ovl10_03_80045728) */
void (*D_ovl10_03_80047100[64])(void);
UnkStruct_ovl10_03_80047200 *D_ovl10_03_80047200;
u8 D_ovl10_03_80047204[0x4]; /* unused (func_ovl10_03_80045728) */
UnkStructA *D_ovl10_03_80047208[8];
UnkStructA *D_ovl10_03_80047228[8];
void *D_ovl10_03_80047248[8];
s32 D_ovl10_03_80047268;
u8 D_ovl10_03_8004726C[0x4]; /* unused (func_ovl10_03_80045728) */
s32 D_ovl10_03_80047270[8];
s32 D_ovl10_03_80047290[8];
s32 D_ovl10_03_800472B0[8];
UnkStructA *D_ovl10_03_800472D0[2];
UnkStructA *D_ovl10_03_800472D8[2];
UnkStructA *D_ovl10_03_800472E0[2];
Vec3f D_ovl10_03_800472E8[2];
s32 D_ovl10_03_80047300[2];
s32 D_ovl10_03_80047308[2];
s32 D_ovl10_03_80047310[2];
s32 D_ovl10_03_80047318[2];
s32 D_ovl10_03_80047320[2];
s32 D_ovl10_03_80047328[64]; /* per task: which of the two */
f32 D_ovl10_03_80047428[2][10];
f32 D_ovl10_03_80047478[2][10];

/* the first .data: its initializers */
void func_ovl10_03_80043720(void) {
    s32 i;
    f32 xs[8] = { 1150.0f, 2060.0f, 2660.0f, 3550.0f, 1160.0f, 2070.0f, 2660.0f, 3550.0f };
    f32 zs[2] = { 770.0f, 2330.0f };

    for (i = 0; i < 8; i++) {
        D_ovl10_03_80047208[i] = func_ovl10_03_800464F0(0x1FE, 0x01080000, 0xD0, 0);
        D_ovl10_03_80047208[i]->unk40->unk10 = xs[i];
        D_ovl10_03_80047208[i]->unk40->unk14 = 1240.0f;
        D_ovl10_03_80047208[i]->unk40->unk18 = zs[i / 4];
        D_ovl10_03_80047208[i]->unk40->unkC |= 0x8000;
        func_ovl10_03_800464C8(D_ovl10_03_80047208[i], 0x80000);
        func_ovl10_03_800461D0(D_ovl10_03_80047208[i]->unk40, 1);
        func_ovl10_03_800461D8(D_ovl10_03_80047208[i]->unk40, 0x1FF, 0, 0);
    }
}

/* .data */
s32 D_ovl10_03_80046DE8[8] = { 0, 5, 4, 1, 2, 7, 6, 3 };
s32 D_ovl10_03_80046E08[8] = { 0, 20, 20, 10, 20, 20, 20, 30 };
extern u32 D_ovl10_03_80046EB0[][3];
s32 D_ovl10_03_80046E28[8] = { 90, 190, 310, 350, 480, 580, 780, 940 };

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_03_80045778(void) {
}

static void func_ovl10_03_80045770(void) {
}

static void func_ovl10_03_80045768(void) {
}

static void func_ovl10_03_80045760(void) {
}

static void func_ovl10_03_80045758(void) {
}

static void func_ovl10_03_80045750(void) {
}

static void func_ovl10_03_80045748(void) {
}

static void func_ovl10_03_80045740(void) {
}

static void func_ovl10_03_80045738(void) {
}

static void func_ovl10_03_80045730(void) {
}

void func_ovl10_03_80045728(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_03_80046FB0[0] = D_ovl10_03_80046FDC[0] + D_ovl10_03_80046FF4[0] + D_ovl10_03_800470FC[0] +
                                 D_ovl10_03_80047204[0] + D_ovl10_03_8004726C[0];
    }
}

void func_ovl10_03_80045710(void) {
    D_ovl10_03_80046FD4 = -1;
    D_ovl10_03_80046FD8 = -1;
}

void func_ovl10_03_800456B4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_03_80046308(D_ovl10_03_80046FE0.x, D_ovl10_03_80046FE0.y, D_ovl10_03_80046FE0.z);
    func_ovl10_03_80046328(arg0, arg1, arg2);
    func_ovl10_03_80046638(180);
}

void func_ovl10_03_8004566C(f32 arg0) {
    f32 sp1C;

    func_ovl10_03_80046330(&sp1C, NULL, NULL);
    func_ovl10_03_80046328(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_03_80045638(s32 arg0, UnkStructA *arg1) {
    func_ovl10_03_80046BC0(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_03_8004554C(void) {
    s32 i;

    D_ovl10_03_80046FEC = 0;
    D_ovl10_03_80046FF0 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_03_80047100[i] != NULL) {
                D_ovl10_03_800470F8 = i;
                if (D_ovl10_03_80046FF8[i] == 0) {
                    D_ovl10_03_80047100[i]();
                } else {
                    D_ovl10_03_80046FF8[i]--;
                }
            }
        }
        D_ovl10_03_80046FEC++;
        D_ovl10_03_80046FEC &= 3;
        func_ovl10_03_80046660();
    }
}

/* Defined above its caller 80045514: only so does its string come first in
 * .rodata (as in ovl_10_02). */
s32 func_ovl10_03_80043334(void (*arg0)(void)) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_03_80047100[i] == NULL) {
            D_ovl10_03_80047100[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_03_80045788("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_03_80045514(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_03_80043334(arg0);
    func_ovl10_03_80045788("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_03_800454E8(void (*arg0)(void)) {
    D_ovl10_03_80047100[func_ovl10_03_800454A4(arg0)] = NULL;
}

s32 func_ovl10_03_800454A4(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_03_80047100[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_03_80045490(s32 arg0) {
    D_ovl10_03_80047100[arg0] = NULL;
}

void func_ovl10_03_80045474(s32 arg0) {
    D_ovl10_03_80046FF8[D_ovl10_03_800470F8] = arg0;
}

void func_ovl10_03_80045458(void (*arg0)(void)) {
    D_ovl10_03_80047100[D_ovl10_03_800470F8] = arg0;
}

void func_ovl10_03_800453C8(void) {
    D_ovl10_03_80047200 = func_ovl10_03_800466A0();
    func_ovl10_03_800466B0(D_ovl10_03_80047200, 0x20000001);
    D_ovl10_03_80047200->unk40 = 0.5f;
    D_ovl10_03_80047200->unk44 = D_ovl10_03_80047200->unk40 * 0.75f;
    D_ovl10_03_80047200->unk18 = 0.1f;
    D_ovl10_03_80047200->unk1C = -0.1f;
}

void func_ovl10_03_8004538C(void) {
    s32 *p;

    p = func_ovl10_03_800468B0();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_03_80045320(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_03_80046370(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_03_80046548(arg0);
        func_ovl10_03_80046660();
    }
}

void func_ovl10_03_800452A0(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_03_80046918(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_03_800464D0(arg0, 0x01000000);
        func_ovl10_03_80046638(5);
        func_ovl10_03_80046918(0, 0, 0, 0.0f);
        func_ovl10_03_80046598(arg0, &pos);
        func_ovl10_03_80046A70(12, &pos, 0);
    }
}

s32 func_ovl10_03_80045284(s32 arg0) {
    s32 ret;

    ret = 0;
    if ((arg0 & 0xF) != 0xF) {
        ret = 1;
    }
    return ret;
}

void func_ovl10_03_80044F40(UnkStructA *arg0) {
    s32 i;

    func_ovl10_03_80046370(15);
    i = 0;
    func_ovl10_03_800461F0(arg0->unk40, 0x11, 0);
    func_ovl10_03_80046220(arg0->unk40, 4, 12);
    func_ovl10_03_80046220(arg0->unk40, 5, 13);
    func_ovl10_03_80046A68(0, arg0->unk40->unk10, arg0->unk40->unk14 + 100.0f, arg0->unk40->unk18, 0);
    arg0->unk68 = 40.0f;
    arg0->unk70 = 1.6333334f;
    func_ovl10_03_80046BA0(0x1E);
    while (TRUE) {
        func_ovl10_03_80046B10(arg0, 0, 0.0f, func_ovl10_03_80045284);
        if (arg0->unk40->unk14 > 700.0f) {
            arg0->unk40->unk14 = 700.0f;
            arg0->unk68 = 0.0f;
            arg0->unk6C = 0.0f;
        }
        arg0->unk40->unk1C += 20.0f;
        if (arg0->unk40->unk1C >= 360.0f) {
            arg0->unk40->unk1C = 0.0f;
        }
        arg0->unk40->unk10 -= func_ovl10_03_800467C0(arg0->unk40->unk1C);
        func_ovl10_03_80046660();
        if (++i >= 200) {
            break;
        }
        if (arg0->unk40->unk14 < 700.0f && arg0->unk6C == 0.0f) {
            break;
        }
    }
    if (arg0->unk40->unk1C >= 90.0f && arg0->unk40->unk1C < 270.0f) {
        arg0->unk40->unk1C = 180.0f;
        arg0->unk40->unk14 = func_ovl10_03_80045B88(arg0->unk40) + 70.0f;
    } else {
        arg0->unk40->unk1C = 0.0f;
        arg0->unk40->unk14 = func_ovl10_03_80045B88(arg0->unk40);
    }
    func_ovl10_03_800461F0(arg0->unk40, 0x13, 0);
    func_ovl10_03_800464D0(arg0, 0x0C000000);
    arg0->unk40->unk48->unk4->unk8 |= 0x20;
    arg0->unk40->unk48->unk4->unk8 |= 0x40;
    arg0->unk40->unk48->unk4->unk4 = func_ovl10_03_80046208(arg0->unk40, 0) - 0.1f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl10_03_80046638(0x50);
}

void func_ovl10_03_80044E04(void) {
    s32 i;

    if (D_ovl10_03_80047268 == 180) {
        for (i = 0; i < 8; i++) {
            if (D_ovl10_03_80046E08[i] != 0) {
                D_ovl10_03_80047270[i] = func_ovl10_03_800467D8(D_ovl10_03_80046E08[i]) + D_ovl10_03_80046E28[i] + 180;
            } else {
                D_ovl10_03_80047270[i] = D_ovl10_03_80046E28[i] + 180;
            }
        }
    }
    if (D_ovl10_03_80047268 >= 180) {
        for (i = 0; i < 8; i++) {
            if (D_ovl10_03_80047268 == D_ovl10_03_80047270[i]) {
                func_ovl10_03_80044BBC(D_ovl10_03_80046DE8[i]);
            }
        }
    }
    func_ovl10_03_80044964();
    D_ovl10_03_80047268++;
    if (D_ovl10_03_80047268 == 1180) {
        D_ovl10_03_80047268 = 180;
    }
}

void func_ovl10_03_80044BBC(s32 arg0) {
    s32 i;
    s32 sp54[2] = { 0xAB, 0xAC };
    s32 sp4C[2] = { 0xB8, 0xB9 };
    f32 sp2C[8] = { 700.0f, 1800.0f, 1300.0f, 2400.0f, 1150.0f, 2250.0f, 850.0f, 1950.0f };

    for (i = 0; i < 8; i++) {
        if (D_ovl10_03_80047228[i] == NULL) {
            D_ovl10_03_80047228[i] = func_ovl10_03_800464F0(sp54[(s32)(arg0 * 0.25f)], 0x01000070, 0x30, 0);
            D_ovl10_03_80047228[i]->unk40->unk10 = -1600.0f;
            D_ovl10_03_80047228[i]->unk40->unk14 = 100.0f;
            D_ovl10_03_80047228[i]->unk40->unk18 = sp2C[arg0];
            D_ovl10_03_80047290[i] = arg0;
            if ((s32)(arg0 * 0.25f) == 0) {
                D_ovl10_03_80047228[i]->unk30 = 1;
                D_ovl10_03_80047228[i]->unk34 = 150.0f;
                D_ovl10_03_80047228[i]->unk38 = 120.0f;
            } else {
                D_ovl10_03_80047228[i]->unk30 = 8;
                D_ovl10_03_80047228[i]->unk34 = 300.0f;
                D_ovl10_03_80047228[i]->unk38 = 1600.0f;
            }
            D_ovl10_03_80047248[i] = func_ovl10_03_80046520(sp4C[(s32)(arg0 * 0.25f)], 0x01200000, D_ovl10_03_80047228[i]);
            func_ovl10_03_800464C8(D_ovl10_03_80047248[i], 0x80000);
            D_ovl10_03_800472B0[i] = 0;
            break;
        }
    }
}

void func_ovl10_03_80044964(void) {
    s32 i;
    UnkStruct_ovl10_03_800465E0 *p;
    s32 pad; /* unused: the original's frame has the slot */
    f32 x;

    for (i = 0; i < 8; i++) {
        if (D_ovl10_03_80047228[i] != NULL && D_ovl10_03_80047268 % 2 == i % 2) {
            func_ovl10_03_80044804(i);
            if (D_ovl10_03_80047290[i] < 4) {
                x = D_ovl10_03_80047228[i]->unk40->unk10;
                D_ovl10_03_80047228[i]->unk40->unk10 = x + 42.5f;
            } else {
                D_ovl10_03_80047228[i]->unk40->unk10 += 34.0f;
            }
            p = func_ovl10_03_800465E0(D_ovl10_03_80047228[i], 7);
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
            if (D_ovl10_03_80047290[i] < 4 && func_ovl10_03_80046478(D_ovl10_03_80047228[i], 0x20) != 0) {
                D_ovl10_03_80047228[i]->unk40->unk10 = x;
            }
            if (D_ovl10_03_80047228[i]->unk40->unk10 > 5600.0f) {
                func_ovl10_03_800447E4(D_ovl10_03_80047228[i]);
                D_ovl10_03_80047228[i] = NULL;
            }
        }
    }
}

void func_ovl10_03_80044804(s32 arg0) {
    Vec3f pos;
    Vec3f target;
    f32 dist;

    func_ovl10_03_80046598(D_ovl10_03_80047228[arg0], &pos);
    if ((s32)(D_ovl10_03_80047290[arg0] * 0.25f) == 1) {
        pos.x += 1600.0f;
    }
    func_ovl10_03_80046598(func_ovl10_03_80045D08(func_ovl10_03_80045CA8()), &target);
    dist = func_ovl10_03_80046470(&pos, &target);
    if (D_ovl10_03_800472B0[arg0] == 0 && dist <= 1000.0f) {
        D_ovl10_03_800472B0[arg0]++;
        if ((s32)(D_ovl10_03_80047290[arg0] * 0.25f) == 0) {
            func_ovl10_03_80046BA0(0x92);
        } else {
            func_ovl10_03_80046BA0(0x93);
        }
    }
}

void func_ovl10_03_800447E4(UnkStructA *arg0) {
    func_ovl10_03_800464E0(arg0);
}

void func_ovl10_03_800446F0(void) {
    s32 i;
    s32 pad; /* unused: the original's frame has the slot */
    Vec3f ang;
    Vec3f a;
    Vec3f b;

    if (func_ovl10_03_80045D08(0)->unk40->unk14 == 700.0f) {
        for (i = 0; i < 2; i++) {
            if (D_ovl10_03_800472D8[i] != NULL) {
                func_ovl10_03_80046598(D_ovl10_03_800472D0[i], &a);
                func_ovl10_03_80046598(D_ovl10_03_800472D8[i], &b);
                func_ovl10_03_80046458(&a, &b, &ang);
                D_ovl10_03_800472D0[i]->unk40->unk20 = ang.x;
            }
        }
    }
}

void func_ovl10_03_800442D8(void) {
    s32 n;
    Vec3f out;
    Vec3f pos;
    Vec3f v;
    UnkStruct_ovl10_03_800465E0 *p;
    f32 x;
    f32 z;

    n = D_ovl10_03_80047328[D_ovl10_03_800470F8];
    switch (D_ovl10_03_80047318[n]) {
        case 10:
            if (D_ovl10_03_80047300[n] & 4) {
                v.z = 70.0f;
                v.x = D_ovl10_03_800472D0[n]->unk40->unk20;
                v.y = 0.0f;
                func_ovl10_03_80046460(&v, &out);
                x = D_ovl10_03_800472D0[n]->unk40->unk10 + out.x;
                z = D_ovl10_03_800472D0[n]->unk40->unk18 + out.z;
                func_ovl10_03_80046A68(0, x, D_ovl10_03_800472D0[n]->unk40->unk14 + 115.0f, z, 0);
                D_ovl10_03_800472E0[n] = func_ovl10_03_800464F0(0x2D2, 0x11080040, 0xD0, 0);
                D_ovl10_03_800472E0[n]->unk40->unk10 = D_ovl10_03_80047428[n][9];
                D_ovl10_03_800472E0[n]->unk40->unk14 = D_ovl10_03_800472D8[n]->unk40->unk14;
                D_ovl10_03_800472E0[n]->unk40->unk18 = D_ovl10_03_80047478[n][9];
                D_ovl10_03_800472E0[n]->unk40->unk28 = 5.0f;
                D_ovl10_03_800472E0[n]->unk40->unk2C = 5.0f;
                D_ovl10_03_800472E0[n]->unk40->unk30 = 5.0f;
                D_ovl10_03_800472E0[n]->unk30 = 1;
                D_ovl10_03_800472E0[n]->unk34 = 10.0f;
                D_ovl10_03_800472E0[n]->unk38 = 0.0f;
                p = func_ovl10_03_800465E0(D_ovl10_03_800472E0[n], 7);
                if (p != NULL) {
                    p->unk10 |= 0x40;
                    if (!(func_ovl10_03_80045D30() & 2) && func_ovl10_03_80045D90(0) == 0) {
                        D_ovl10_03_80046FF0 = 1;
                    }
                }
                func_ovl10_03_80046598(D_ovl10_03_800472E0[n], &pos);
                func_ovl10_03_80046BC8(0x95, &pos);
            }
            break;
        case 9:
            if (D_ovl10_03_800472E0[n] != NULL) {
                D_ovl10_03_800472E0[n]->unk40->unk28 = 5.0f;
                D_ovl10_03_800472E0[n]->unk40->unk2C = 5.0f;
                D_ovl10_03_800472E0[n]->unk40->unk30 = 5.0f;
            }
            break;
        case 8:
            if (D_ovl10_03_800472E0[n] != NULL) {
                D_ovl10_03_800472E0[n]->unk40->unk28 = 5.0f;
                D_ovl10_03_800472E0[n]->unk40->unk2C = 5.0f;
                D_ovl10_03_800472E0[n]->unk40->unk30 = 5.0f;
            }
            break;
        case 7:
            if (D_ovl10_03_800472E0[n] != NULL) {
                func_ovl10_03_800464E0(D_ovl10_03_800472E0[n]);
                D_ovl10_03_800472E0[n] = NULL;
            }
            break;
        case 0:
            D_ovl10_03_80047318[n] = 11;
            D_ovl10_03_80047310[n]--;
            break;
    }
    D_ovl10_03_80047318[n]--;
    if (D_ovl10_03_80047310[n] == 0 && (D_ovl10_03_80047300[n] & 4)) {
        D_ovl10_03_80047300[n] &= ~4;
        func_ovl10_03_80043B88(n, 2);
    }
    if (D_ovl10_03_80047310[n] == 0) {
        func_ovl10_03_800442BC();
    }
}

void func_ovl10_03_800442BC(void) {
    D_ovl10_03_80047100[D_ovl10_03_800470F8] = NULL;
}

void func_ovl10_03_80043E34(void) {
    s32 i;
    s32 j;
    f32 dist;
    f32 speed;
    Vec3f player;
    Vec3f pos;
    Vec3f pos2;
    Vec3f ang;
    f32 a;
    s32 pad; /* unused: the original's frame has the slot */

    func_ovl10_03_80046598(func_ovl10_03_80045D08(0), &player);
    if (player.y == 700.0f || D_ovl10_03_80046FF0 != 0) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 9; j++) {
                D_ovl10_03_80047428[i][10 - j - 1] = D_ovl10_03_80047428[i][10 - j - 2];
                D_ovl10_03_80047478[i][10 - j - 1] = D_ovl10_03_80047478[i][10 - j - 2];
            }
            D_ovl10_03_80047428[i][0] = D_ovl10_03_800472D8[i]->unk40->unk10;
            D_ovl10_03_80047478[i][0] = D_ovl10_03_800472D8[i]->unk40->unk18;
            func_ovl10_03_80046598(D_ovl10_03_800472D0[i], &pos);
            pos.y = 700.0f;
            if (func_ovl10_03_80046470(&player, &pos) < 1500.0f) {
                if (!(D_ovl10_03_80047300[i] & 1)) {
                    func_ovl10_03_80043CF4(i);
                }
                func_ovl10_03_80046598(D_ovl10_03_800472D8[i], &pos);
                pos.y = 700.0f;
                func_ovl10_03_80046458(&pos, &player, &ang);
                ang.y -= 90.0f;
                dist = func_ovl10_03_80046470(&player, &pos);
                if (dist > 6.8f) {
                    speed = 6.8f;
                } else {
                    speed = dist;
                }
                if (dist < 1.0f) {
                    dist = 0.0f;
                }
                a = ang.x;
                D_ovl10_03_800472D8[i]->unk40->unk10 += speed * func_ovl10_03_800467C0(a);
                D_ovl10_03_800472D8[i]->unk40->unk18 += speed * func_ovl10_03_800467C8(a);
                if (D_ovl10_03_80047300[i] & 2) {
                    if (D_ovl10_03_80047308[i] > 0) {
                        D_ovl10_03_80047308[i]--;
                    }
                    if (D_ovl10_03_80047308[i] == 0 && !(D_ovl10_03_80047300[i] & 4)) {
                        func_ovl10_03_80043C4C(i);
                    }
                }
                if (dist == 0.0f && !(D_ovl10_03_80047300[i] & 2)) {
                    func_ovl10_03_80043B88(i, 1);
                    if (!(D_ovl10_03_80047300[i] & 4)) {
                        D_ovl10_03_80047308[i] = 60;
                        D_ovl10_03_80047300[i] |= 2;
                        func_ovl10_03_80046598(D_ovl10_03_800472D0[i], &pos2);
                        func_ovl10_03_80046BC8(0x94, &pos2);
                    }
                }
            } else if (D_ovl10_03_80047300[i] & 1) {
                func_ovl10_03_80043AF4(i);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (D_ovl10_03_80047300[i] & 1) {
                func_ovl10_03_80043AF4(i);
            }
        }
    }
}

void func_ovl10_03_80043CF4(s32 arg0) {
    s32 i;

    D_ovl10_03_800472D8[arg0] = func_ovl10_03_800464F0(0xCC, 0x11080000, 0x10, 0);
    D_ovl10_03_800472D8[arg0]->unk40->unk10 = D_ovl10_03_800472E8[arg0].x;
    D_ovl10_03_800472D8[arg0]->unk40->unk14 = D_ovl10_03_800472E8[arg0].y;
    D_ovl10_03_800472D8[arg0]->unk40->unk18 = D_ovl10_03_800472E8[arg0].z;
    D_ovl10_03_800472D8[arg0]->unk40->unk36 = 0xC0;
    D_ovl10_03_80047300[arg0] |= 1;
    for (i = 0; i < 10; i++) {
        D_ovl10_03_80047428[arg0][i] = D_ovl10_03_800472E8[arg0].x;
        D_ovl10_03_80047478[arg0][i] = D_ovl10_03_800472E8[arg0].z;
    }
}

void func_ovl10_03_80043C4C(s32 arg0) {
    D_ovl10_03_80047300[arg0] &= ~2;
    D_ovl10_03_80047310[arg0] = 4;
    D_ovl10_03_80047320[arg0] = 1;
    D_ovl10_03_80047318[arg0] = 10;
    D_ovl10_03_80047300[arg0] &= ~2;
    D_ovl10_03_80047300[arg0] |= 4;
    D_ovl10_03_800472E0[arg0] = NULL;
    D_ovl10_03_80047328[func_ovl10_03_80043334(func_ovl10_03_800442D8)] = arg0;
}

void func_ovl10_03_80043B88(s32 arg0, s32 arg1) {
    Vec3f pos;
    s32 id;

    if (arg1 == 1) {
        id = 0xCB;
    } else {
        id = 0xCC;
    }
    func_ovl10_03_80046598(D_ovl10_03_800472D8[arg0], &pos);
    func_ovl10_03_800464E0(D_ovl10_03_800472D8[arg0]);
    D_ovl10_03_800472D8[arg0] = func_ovl10_03_800464F0(id, 0x11080000, 0x10, 0);
    D_ovl10_03_800472D8[arg0]->unk40->unk10 = pos.x;
    D_ovl10_03_800472D8[arg0]->unk40->unk14 = pos.y;
    D_ovl10_03_800472D8[arg0]->unk40->unk18 = pos.z;
    D_ovl10_03_800472D8[arg0]->unk40->unk36 = 0xC0;
}

void func_ovl10_03_80043AF4(s32 arg0) {
    D_ovl10_03_800472E8[arg0].x = D_ovl10_03_800472D8[arg0]->unk40->unk10;
    D_ovl10_03_800472E8[arg0].y = D_ovl10_03_800472D8[arg0]->unk40->unk14;
    D_ovl10_03_800472E8[arg0].z = D_ovl10_03_800472D8[arg0]->unk40->unk18;
    func_ovl10_03_800464E0(D_ovl10_03_800472D8[arg0]);
    D_ovl10_03_800472D8[arg0] = NULL;
    D_ovl10_03_80047300[arg0] = 0;
}

void func_ovl10_03_80043A30(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl10_03_800438D8();
            break;
        case 17:
            func_ovl10_03_800432DC();
            break;
        case 18:
            func_ovl10_03_80043284();
            break;
        case 19:
            func_ovl10_03_8004322C();
            break;
        case 20:
            func_ovl10_03_800431D4();
            break;
        case 4:
            func_ovl10_03_800431B4();
            break;
        case 0x50:
            func_ovl10_03_80043084();
            break;
    }
}

void func_ovl10_03_800438D8(void) {
    func_ovl10_03_80046980(D_ovl10_03_80046EB0);
    func_ovl10_03_80046B28(0, 0, 0xDE);
    func_ovl10_03_80046B28(1, 0x11, 0xEF);
    func_ovl10_03_80046B28(2, 0x1A, 0xF8);
    func_ovl10_03_80046B28(3, 0x1B, 0xF9);
    func_ovl10_03_80045AC8(0x1DC);
    func_ovl10_03_80045AD0(0x1DD, 0.0f, 0.0f, 0.0f, 0x60, 0);
    func_ovl10_03_80045AD0(0x1D4, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_03_80045AD0(0x1D5, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_03_80045AD0(0x1D5, 7600.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_03_80043720();
    func_ovl10_03_80045AE0(0x1E3);
    func_ovl10_03_80045B90(0xF);
    func_ovl10_03_80045C78();
    func_ovl10_03_800436A4();
    func_ovl10_03_80043644();
    func_ovl10_03_80043618();
    func_ovl10_03_80043440();
    func_ovl10_03_80045BB0(func_ovl10_03_80045320);
}

void func_ovl10_03_800436A4(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_03_80047100[i] = NULL;
        D_ovl10_03_80046FF8[i] = 0;
    }
    func_ovl10_03_80046618(func_ovl10_03_8004554C, 0, 0, 0, 0x110);
}

void func_ovl10_03_80043644(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_ovl10_03_80047228[i] = NULL;
    }
    D_ovl10_03_80047268 = 0;
    func_ovl10_03_80045C00(func_ovl10_03_80044F40);
    func_ovl10_03_80043334(func_ovl10_03_80044E04);
}

void func_ovl10_03_80043618(void) {
    func_ovl10_03_80043488();
    func_ovl10_03_80043334(func_ovl10_03_800446F0);
}

void func_ovl10_03_80043488(void) {
    f32 xs[6] = { 1650.0f, 1650.0f, 1700.0f, 1700.0f, 1700.0f, 1700.0f };
    f32 zs[6] = { 400.0f, 2700.0f, 500.0f, 2600.0f, 500.0f, 2600.0f };
    s32 i;

    for (i = 0; i < 2; i++) {
        D_ovl10_03_800472D0[i] = func_ovl10_03_800464F0(0xB1, 0x01000010, 0x10, 0);
        D_ovl10_03_800472D0[i]->unk40->unk10 = xs[i];
        D_ovl10_03_800472D0[i]->unk40->unk14 = 900.0f;
        D_ovl10_03_800472D0[i]->unk40->unk18 = zs[i];
        func_ovl10_03_80046500(D_ovl10_03_800472D0[i]);
        if (i == 1) {
            D_ovl10_03_800472D0[i]->unk40->unk20 = 180.0f;
        }
    }
}

void func_ovl10_03_800433AC(void) {
    s32 i;
    f32 dz[2] = { 500.0f, -500.0f };

    for (i = 0; i < 2; i++) {
        D_ovl10_03_800472E8[i].x = D_ovl10_03_800472D0[i]->unk40->unk10;
        D_ovl10_03_800472E8[i].y = 710.0f;
        D_ovl10_03_800472E8[i].z = D_ovl10_03_800472D0[i]->unk40->unk18 + dz[i];
        D_ovl10_03_800472D8[i] = NULL;
    }
}

/* passed to func_ovl10_03_80046980: three 12-byte records and an end */
u32 D_ovl10_03_80046EB0[][3] = {
    { 0xA70001, 0xE, 4 },
    { 0xB70000, 0xE, 4 },
    { 0xA50003, 0xF, 4 },
    { 0, 0, 0 },
};

void func_ovl10_03_80043440(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_ovl10_03_80047300[i] = 0;
    }
    func_ovl10_03_800433AC();
    func_ovl10_03_80043334(func_ovl10_03_80043E34);
}

void func_ovl10_03_800432DC(void) {
    func_ovl10_03_80045C80(0x2C, 1, 10);
    func_ovl10_03_80045CC0(0xC0);
    func_ovl10_03_80045CC8(0xC0, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_03_80043284(void) {
    func_ovl10_03_80045C80(0x2C, 1, 21);
    func_ovl10_03_80045CC0(0xC0);
    func_ovl10_03_80045CC8(0xC0, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_03_8004322C(void) {
    func_ovl10_03_80045C80(3, 1, 10);
    func_ovl10_03_80045CC0(0x40);
    func_ovl10_03_80045CC8(0x40, 3, 8.5f, 4, 0, 1, 1);
}

void func_ovl10_03_800431D4(void) {
    func_ovl10_03_80045C80(3, 1, 21);
    func_ovl10_03_80045CC0(0x40);
    func_ovl10_03_80045CC8(0x40, 3, 8.5f, 4, 0, 1, 1);
}

static void func_ovl10_03_800431AC(void) {
}

void func_ovl10_03_800431B4(void) {
    func_ovl10_03_800431AC();
    func_ovl10_03_80045CD8();
}

void func_ovl10_03_80043084(void) {
    func_ovl10_03_80043028();
    func_ovl10_03_80045D10(1);
    if (func_ovl10_03_80045C90(0x2C, 6, 0x2E, 0xE) != 0) {
        D_ovl10_03_80046FD4 = 0x69;
        D_ovl10_03_80046FD8 = 0x13;
        func_ovl10_03_80045BC0(0x69, 0x13, 0);
    }
    if (func_ovl10_03_80045C90(0x2C, 0x11, 0x2E, 0x19) != 0) {
        D_ovl10_03_80046FD4 = 0x69;
        D_ovl10_03_80046FD8 = 0x14;
        func_ovl10_03_80045BC0(0x69, 0x14, 0);
    }
    if (func_ovl10_03_80045C90(1, 6, 3, 0xE) != 0) {
        D_ovl10_03_80046FD4 = 0x6B;
        D_ovl10_03_80046FD8 = 0x11;
        func_ovl10_03_80045BC0(0x6B, 0x11, 0);
    }
    if (func_ovl10_03_80045C90(1, 0x11, 3, 0x19) != 0) {
        D_ovl10_03_80046FD4 = 0x6B;
        D_ovl10_03_80046FD8 = 0x12;
        func_ovl10_03_80045BC0(0x6B, 0x12, 0);
    }
}

void func_ovl10_03_80043028(void) {
    s32 i;

    func_ovl10_03_80043018();
    func_ovl10_03_80043020();
    for (i = 0; i < 8; i++) {
        if (D_ovl10_03_80047208[i] != NULL) {
            func_ovl10_03_800464E0(D_ovl10_03_80047208[i]);
            D_ovl10_03_80047208[i] = NULL;
        }
    }
}

static void func_ovl10_03_80043020(void) {
}

static void func_ovl10_03_80043018(void) {
}

void func_ovl10_03_80043010(void) {
}
