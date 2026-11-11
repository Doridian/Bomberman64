/*
 * NON_MATCHING: main_code's 9CAB0, complete: the objects in D_800BA900's
 * sixteen slots, each driven by a task in D_800BB340. Every function is
 * emitted in the original's order, with the original's stubs. Not built
 * into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 231, eu 231, jp 231
 */
#include "common.h"

/* The object the tables' functions are handed (A2840's name); it is
 * D_800BA900[i].unk14. */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 unk3D;
    /* 0x3E */ u16 unk3E;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ union {
        f32 f;
        u8 b[4];
    } unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ union {
        f32 f;
        u8 b[4];
    } unk58;
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 unk5D;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 unk6D;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ u8 unk78;
    /* 0x79 */ s8 unk79;
    /* 0x7A */ u8 unk7A;
    /* 0x7C */ u16 unk7C;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s16 unk88;
    /* 0x8C */ s32 unk8C;
} UnkStruct_80288040; /* size 0x90 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ Vec3f unk8;
    /* 0x14 */ UnkStruct_80288040 unk14;
} UnkStruct_800BA900; /* size 0xA4 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ UnkStruct_800BA900 *unk10;
} UnkStruct_800BB340; /* size 0x14 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
} UnkStruct_800BA8E8;

extern UnkStruct_800BA8E8 D_800BA8E8[6];
extern UnkStruct_800BA900 D_800BA900[16];
extern UnkStruct_800BB340 D_800BB340[16];
extern s32 D_800BB480;
extern UnkStruct_80288040 *D_800BB484;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_8023A840;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
} UnkStruct_802B0260; /* size 0x50 */

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
} UnkStruct_802B0300;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 unk30[6];
    /* 0x36 */ s16 unk36;
} UnkStruct_802B0308;

void func_80225CCC(void *, s32, s32);
void func_802276FC(s32);
f32 func_80229D3C(void *, s32);
void func_80229E38(void *, s32, s32);
s32 func_8022F4AC(UnkStructA *, s32, UnkStructA *);
UnkStructA *func_8022F550(UnkStructA *, s32);
void func_8022FC90(void *);
void func_80230914(void *);
UnkStructA *func_80230CB4(s32, s32, s32, s32, void *);
s32 func_802311E8(void *);
void func_802313DC(void *, s32);
void func_80231408(void *, s32);
s32 func_80232D18(void *, s32);
void func_80232DB4(void *);
int func_802336E4(f32);
s32 func_80234248(s32);
f32 func_80234434(f32);
s32 func_80234768(void);
void func_80234858(f32 *, f32 *, f32 *);
void func_802348B4(f32 *, f32 *, f32 *);
s32 func_80238A10(void *, void *, s32, s32, s32);
void func_80238EA8(s32);
void func_80239094(void);
UnkStruct_800BB340 *func_802391F0(void);
void func_80239430(void);
UnkStruct_8023A840 *func_8023A840(void);
s32 func_80243DDC(void);
UnkStructA *func_802443F4(s32);
void func_80250338(s32, Vec3f *);
f64 func_8025E63C(void);
f32 func_80263DC8(f32, f32);
s32 func_8026C51C(s32, f32, f32, f32);
s32 func_8026D7D8(s32, s32, s32);
void func_8026DCAC(f32, f32, f32, void *, s32);
s32 func_8026EE18(f32);
s32 func_802700EC(UnkStructA *, UnkStructA *, s32, f32);
void func_80270BA4(void *);
void func_80270C24(UnkStructA *, s32, s32);
void func_802727D8(s32);
void func_802733C8(void *);
void func_8027B7C4(s16, f32, f32, f32);
void func_8027F820(UnkStructA *);
void func_8027F858(UnkStructA *, s32);
void func_8028805C(void *);
void func_802881A0(void *);
void func_802883B0(void);
s32 func_8028A4E0(s32);
s32 func_8028A81C(s32, f32, f32, f32, UnkStructA *);
s32 func_802909FC(UnkStructA *, void *);
void func_80291944(void *, s32, f32);
f32 sinf(f32);

extern u8 D_800BA90C[];
extern u8 D_800BB488[20];
extern s32 D_800BC520;
extern u8 D_802A1AB4[];
extern s32 D_802A1AF0[][4];
extern s32 D_802A1B50;
extern u8 D_802A1B54[];
extern UnkStruct_802B0260 D_802B0260[2];
extern UnkStruct_802B0300 *D_802B0300[2];
extern UnkStruct_802B0308 *D_802B0308[2];

void func_802822B0(s32 arg0);
void func_802822BC(UnkStruct_800BB340 *arg0);
static void func_802822D8();
static void func_802822E0(UnkStruct_800BB340 *arg0);
static void func_80282340(UnkStruct_800BA900 *arg0);
static void func_80282428();
void func_80282430();
static void func_80282454(UnkStruct_80288040 *arg0);
static s32 func_802824B4(UnkStruct_80288040 *arg0);
s32 func_80282524(UnkStruct_80288040 *arg1);
static void func_80282588();
void func_80282598(UnkStruct_800BB340 *arg0, s32 arg1);
static void func_80282714(UnkStruct_80288040 *arg0);
void func_8028275C(f32 arg0, f32 arg1, f32 arg2);
void func_80282934(void);
void func_80282978(Vec3f *arg0);
static s32 func_802829AC(Vec3f *arg1, s32 arg0);
static void func_80282AD0();
s32 func_80282AF0(UnkStruct_800BB340 *arg0, s32 arg1);
static void func_80282F44(UnkStruct_800BB340 *arg0, s32 arg1);
void func_8028301C(UnkStruct_80288040 *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
static void func_8028304C(UnkStruct_80288040 *arg0, s32 arg1);
static void func_802831A8(UnkStruct_80288040 *arg0);
f32 func_8028322C(UnkStruct_80288040 *arg0);
static u8 func_80283314(UnkStruct_80288040 *arg2, s32 arg0, s32 arg1);
static void func_802836F0(UnkStruct_80288040 *arg0, s32 arg1);
static s32 func_80283794(UnkStruct_80288040 *arg0, u8 arg1);
void func_80283B04(UnkStruct_80288040 *arg0, Vec3f *arg1);
static void func_80283CF0(UnkStruct_80288040 *arg0);
static s32 func_80283D9C(UnkStruct_80288040 *arg0);
void func_80283DF0(UnkStruct_80288040 *arg1, s32 arg0);
static void func_80283F38(UnkStruct_80288040 *arg0);
static void func_80283FCC(UnkStruct_80288040 *arg0);
static void func_8028425C(UnkStruct_80288040 *arg0);
static s32 func_8028456C(UnkStruct_80288040 *arg0);
void func_802847E4(UnkStruct_80288040 *arg0, s32 arg1);
static void func_802848E8(UnkStruct_80288040 *arg0);
static void func_80284B30(UnkStruct_80288040 *arg0);
static s32 func_80284CAC(UnkStruct_80288040 *arg0);
static s32 func_80284FD4(UnkStruct_80288040 *arg0);
s32 func_8028556C(s32 arg0);
s32 func_80285658(UnkStruct_800BA900 *arg0, UnkStruct_800BB340 *arg1);
static void func_80285A9C(UnkStruct_800BB340 *arg0);
static void func_80285F8C(void);
void func_802863B0(Vec3f *arg0);
static void func_802863E0();
void func_80286400(s32 arg4, s32 arg0, s32 arg5, f32 arg1, f32 arg2, f32 arg3);
UnkStruct_80288040 *func_802867E4(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 func_80286CA8(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80286E60(void);
void func_80286EF0(void);
static void func_80286EFC();
void func_80286F04(void);
void func_80286F70(void);
void func_80286F98(void);
void func_80287008(s32 arg0, s32 arg1, s32 arg2);
static UnkStruct_80288040 *func_80287024(UnkStructA *arg0);
s32 func_802870A8(UnkStructA *arg0, s32 arg1);
s32 func_80287150(void);
static UnkStruct_800BB340 *func_802871C8(UnkStruct_80288040 *arg0);
s32 func_802871D0(UnkStruct_80288040 *arg0);
s32 func_802872E0(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80287440(UnkStructA *arg0);
s32 func_802875B0(UnkStructA *arg0);
s32 func_80287680(void);
void func_802876A0(void);
void func_802876C8(UnkStruct_802B0260 *arg0);
void func_8028773C(UnkStruct_802B0260 *arg0);
void func_8028785C(void);
void func_802878BC(UnkStruct_802B0260 *arg0, s32 arg1);
void func_802878E0(UnkStruct_802B0260 *arg0, s32 arg1);
void func_80287904(void);
UnkStruct_802B0260 *func_80287DC0(s32 arg0);
void func_80287FD4(void);
void func_80282338();
static void func_80282590();
void func_802829A4();
static s32 func_80282AD8(UnkStruct_80288040 *act);
static s32 func_80282AE0(UnkStruct_80288040 *act);
static s32 func_80282AE8(UnkStruct_80288040 *act);
static void func_80283014();
static void func_80283304();
void func_8028330C();
static void func_80283784();
void func_8028378C();
static s32 func_80283AFC(UnkStructA_40 *p, Vec3f *arg1);
static s32 func_80283F28(UnkStruct_80288040 *arg0);
static void func_80283F30(UnkStruct_80288040 *arg0);
static void func_80283FAC();
void func_80283FB4();
static void func_80283FBC();
void func_80283FC4();
static void func_8028422C();
void func_80284234();
static void func_8028423C();
void func_80284244();
static void func_8028424C();
static s32 func_80284254(UnkStruct_80288040 *arg0);
static void func_802847DC();
static void func_802848D8();
void func_802848E0();
static void func_80284B20();
void func_80284B28();
static void func_80284C9C();
void func_80284CA4();
static s32 func_80284FCC(UnkStruct_80288040 *arg0);
static void func_80285554();
void func_8028555C();
static void func_80285564();
static void func_80285650();
static void func_80285A6C();
static UnkStruct_800BA900 *func_80285A74();
static void func_80285A7C(UnkStruct_80288040 *a_, UnkStruct_800BA8E8 *e_);
static void func_80285A84(UnkStruct_80288040 *a_);
static void func_80285A8C(UnkStruct_80288040 *a_, UnkStruct_800BA8E8 *e_);
static void func_80285A94(UnkStruct_80288040 *a_);
static void func_80285F84(void);
static s32 func_802863E8(s32 arg0);
static s32 func_802863F0(void);
static s32 func_802863F8(void);
static s32 func_802867CC(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
static s32 func_802867D4(void);
static void func_802867DC(UnkStruct_800BA900 *arg0);
static UnkStruct_800BB340 *func_802872D8(UnkStruct_800BA900 *arg0);
static void func_80287690();
void func_80287698();

#define DEC_80284CA4(a_) ((--(a_)->unk6D == 0) ? 1 : 0)

static void func_80287690() {
}

static void func_80287698() {
}

s32 func_80287680(void) {
    return D_800BC520;
}

s32 func_802875B0(UnkStructA *arg0) {
    UnkStruct_80288040 *a;

    a = func_80287024(arg0);
    if (a == NULL) {
        return 0;
    }
    if (((u8) (a->unk7A & 0xF) != 1) && (D_800BA8E8[a->unk84].unk0 != 0x19)) {
        return 0;
    }
    switch ((u8) (a->unk7A & 0xF0)) {
    case 0x20:
    case 0x30:
        func_802313DC(a->unk0, 0x400);
        break;
    case 0x10:
        func_80282714(a);
        break;
    }
    func_80231408(a->unk0, 0x10000);
    func_80282430(a, 0xF0, 0x10);
    return 1;
}

void func_80287440(UnkStructA *arg0) {
    UnkStruct_80288040 *a;
    s32 f;

    a = func_80287024(arg0);
    f = 4;
    if (a != NULL) {
        if ((u8) (a->unk7A & 0xF0) == 0x20) {
            a->unk6E = 120;
            a->unk4 = (a->unk0->unk40->unk10 + 50.0f) * 0.01;
            a->unk8 = func_8026EE18(a->unk0->unk40->unk14);
            a->unkC = (a->unk0->unk40->unk18 + 50.0f) * 0.01;
        }
        func_802847E4(a, 1);
        a->unk7A &= 0xF;
        a->unk68 = 0;
        func_802313DC(a->unk0, 0x20400);
        if ((u8) (a->unk7A & 0xF) != 1) {
            f = func_802824B4(a) | 4;
        }
        func_80231408(a->unk0, f);
    }
}

static UnkStruct_800BB340 *func_802872D8(UnkStruct_800BA900 *arg0) {
    s32 i;
    UnkStruct_800BB340 *t;

    t = D_800BB340;
    for (i = 0; i < 16; i++, t++) {
        if ((t->unk10 != NULL) && (arg0 == t->unk10)) {
            return t;
        }
    }
    return NULL;
}

s32 func_802872E0(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStruct_800BA900 *s;
    UnkStruct_800BB340 *t;
    s32 i;

    s = D_800BA900;
    for (i = 0; i < 16; i++, s++) {
        if ((s->unk0 != 0) && (arg0 == s->unk14.unk84) && (arg1 == s->unk8.x) && (arg2 == s->unk8.y) &&
            (arg3 == s->unk8.z)) {
            t = func_802872D8(s);
            if (t != NULL) {
                func_80282598(t, 0);
                func_802867DC(s);
                return 0;
            }
        }
    }
    return -1;
}

s32 func_802871D0(UnkStruct_80288040 *arg0) {
    UnkStruct_800BB340 *t;
    s32 st;
    s32 an;

    st = 0;
    an = 0;
    t = func_802871C8(arg0);
    if (t == NULL) {
        return 0xFFFF;
    }
    switch (t->unkC) {
    case 0:
        return 0xFFFF;
    case 2:
        st = 1;
        break;
    case 3:
        st = 3;
        break;
    case 4:
        st = 2;
        break;
    case 5:
        st = 4;
        break;
    }
    if (st == 0) {
        switch ((u8) (arg0->unk7A & 0xF)) {
        case 2:
            an = 0x18;
            break;
        case 1:
            an = 8;
            break;
        case 3:
            an = 0x20;
            break;
        }
        if (((u8) (arg0->unk7A & 0xF0)) == 0x10) {
            an = 0x10;
        }
    }
    return an | st;
}

static UnkStruct_800BB340 *func_802871C8(UnkStruct_80288040 *arg0) {
    s32 i;
    UnkStruct_800BB340 *t;

    t = D_800BB340;
    for (i = 0; i < 16; i++, t++) {
        if ((t->unk10 != NULL) && (arg0 == &t->unk10->unk14)) {
            return t;
        }
    }
    return NULL;
}

s32 func_80287150(void) {
    s32 i;
    s32 n;
    UnkStruct_800BB340 *t;

    t = D_800BB340;
    n = 0;
    for (i = 0; i < 16; i++, t++) {
        if (t->unkC == 1) {
            n++;
        }
    }
    return n;
}

s32 func_802870A8(UnkStructA *arg0, s32 arg1) {
    UnkStruct_80288040 *a;

    a = func_80287024(arg0);
    if (a == NULL) {
        return 0;
    }
    if ((D_800BA8E8[a->unk84].unk0 != 0x19) && (((u8) (a->unk7A & 0xF0)) != 0x10)) {
        return 0;
    }
    func_802313DC(a->unk0, 0x10000);
    a->unk68 = arg1;
    func_80282430(a, 0xF0, 0x20);
    func_80231408(a->unk0, 0x20400);
    return 1;
}

static UnkStruct_80288040 *func_80287024(UnkStructA *arg0) {
    s32 i;
    UnkStruct_800BA900 *s;

    s = D_800BA900;
    for (i = 0; i < 16; i++, s++) {
        if (arg0 == s->unk14.unk0) {
            return &s->unk14;
        }
    }
    return NULL;
}

void func_80287008(s32 arg0, s32 arg1, s32 arg2) {
    D_800BA8E8[arg0].unk0 = arg1;
    D_800BA8E8[arg0].unk2 = arg2;
}

void func_80286F98(void) {
    s32 i;

    func_80286F70();
    func_80286F04();
    for (i = 0; i < 16; i++) {
        func_80282340(&D_800BA900[i]);
        func_802822BC(&D_800BB340[i]);
    }
    func_802822B0(3);
    func_802883B0();
    func_80286EF0();
}

void func_80286F70(void) {
    s32 i;

    func_80297D30(0x2A, D_802A1AB4);
    if (0) {
        for (i = 0; i < 6; i++) {
            D_800BA8E8[i].unk0 = -1;
            D_800BA8E8[i].unk2 = -1;
        }
    }
}

void func_80286F04(void) {
    s32 i;

    func_80286EFC();
    for (i = 0; i < 6; i++) {
        D_800BA8E8[i].unk0 = -1;
        D_800BA8E8[i].unk2 = -1;
    }
}

static void func_80286EFC() {
}

void func_80286EF0(void) {
    D_800BC520 = 0;
}

void func_80286E60(void) {
    s32 i;
    UnkStruct_800BA900 *s;
    UnkStruct_800BB340 *t;

    s = D_800BA900;
    t = D_800BB340;
    for (i = 0; i < 16; i++, s++, t++) {
        func_802867DC(s);
        func_802822E0(t);
    }
}

s32 func_80286CA8(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 t;
    UnkStruct_800BB340 *task;

    t = func_802867D4();
    if (t != -1) {
        task = &D_800BB340[t];
        task->unk0 = t;
        task->unkC = 0;
        task->unk4 = 1;
        task->unk8 = func_80238A10(func_80285F8C, task, 0, 0, 0xD0);
        task->unk10 = NULL;
    }
    return func_802867CC(arg0, arg1, arg2, arg3);
}

static s32 func_802863F8(void) {
    UnkStruct_800BA900 *s;
    s32 i;

    s = D_800BA900;
    for (i = 0; i < 16; i++, s++) {
        if (s->unk0 == 0) {
            return i;
        }
    }
    return -1;
}

static s32 func_802867CC(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 pad[2];
    s32 slot;

    slot = func_802863F8();
    if (slot != -1) {
        func_80286400(slot, arg0, 2, arg1, arg2, arg3);
    }
    return slot;
}

static s32 func_802863F0(void) {
    UnkStruct_800BB340 *t;
    s32 i;
    s32 n;

    n = 0;
    t = D_800BB340;
    for (i = 0; i++ < 16; t++) {
        if (t->unk4 != 0) {
            n++;
        }
    }
    if (n < D_800BB480) {
        for (i = 0; i < 16; i++) {
            if (D_800BB340[i].unk4 == 0) {
                return i;
            }
        }
    }
    return -1;
}

static s32 func_802867D4(void) {
    return func_802863F0();
}
static s32 func_802863E8(s32 arg0) {
    s32 t;
    UnkStruct_800BB340 *task;
    s32 pad[2];

    t = func_802867D4();
    if (t != -1) {
        task = &D_800BB340[t];
        task->unk0 = t;
        task->unkC = 0;
        task->unk4 = arg0;
        task->unk8 = func_80238A10(func_80285F8C, task, 0, 0, 0xD0); task->unk10 = NULL;
    }
    return t;
}

static void func_802867DC(UnkStruct_800BA900 *arg0) {
    if (arg0->unk0 != 0) {
        func_8022FC90(arg0->unk14.unk0);
        func_80282340(arg0);
    }
}

UnkStruct_80288040 *func_802867E4(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStruct_80288040 *ret;
    s32 slot;
    s32 special;
    s32 t;
    UnkStruct_800BB340 *task;

    func_802863E0();
    special = 0;
    ret = NULL;
    slot = -1;
    if (0) { D_800BC520 = (s32) &slot; }
    if ((arg0 == 0) && (D_800BA8E8[arg0].unk0 == 0x19) && (D_800BA8E8[arg0].unk2 == 0x1E)) {
        slot = 13;
        special = 1;
    } else if ((arg0 == 1) && (D_800BA8E8[arg0].unk0 == 0x19) && (D_800BA8E8[arg0].unk2 == 0x1F)) {
        slot = 14;
        special = 1;
    } else if ((arg0 == 3) && (D_800BA8E8[arg0].unk0 == 0x1C) && (D_800BA8E8[arg0].unk2 == 0xD2)) {
        slot = 15;
        special = 1;
    }
    if (special && (D_800BA900[slot].unk0 != 0)) {
        slot = -1;
    }
    if (special) {
        if (slot != -1) {
            func_80286400(slot, arg0, 2, arg1, arg2, arg3);
        }
    } else {
        slot = func_802867CC(arg0, arg1, arg2, arg3);
    }
    if (slot != -1) {
        if (D_800BB480 + 1 < 16) {
            D_800BB480++;
            t = func_802863E8(2);
            if (t != -1) {
                if (func_80285658(&D_800BA900[slot], &D_800BB340[t]) == 0) {
                    func_802867DC(&D_800BA900[slot]);
                    func_802822E0(&D_800BB340[t]);
                } else {
                    ret = &D_800BA900[slot].unk14;
                }
            } else {
                if (ret) {}
                D_800BB480--;
                func_802867DC(&D_800BA900[slot]);
            }
        } else {
            func_802867DC(&D_800BA900[slot]);
        }
    }
    return ret;
}

static void func_80286400(s32 arg4, s32 arg0, s32 arg5, f32 arg1, f32 arg2, f32 arg3) {
    UnkStruct_800BA900 *s;
    UnkStruct_80288040 *a;
    UnkStructA *m;
    s32 size;
    Vec3f *p;
    struct {
        s32 g[3];
        Vec3f o;
    } grid;

    s = &D_800BA900[arg4];
    func_80282340(s);
    s->unk0 = arg5;
    s->unk4 = 0;
    s->unk8.x = arg1;
    s->unk8.y = arg2;
    s->unk8.z = arg3;
    s->unk14.unk80 = arg4;
    s->unk14.unk84 = arg0;
    func_80285A7C(&s->unk14, &D_800BA8E8[arg0]);
    a = &s->unk14;
    s->unk0 = 2;
    p = &s->unk8;
    func_8026DCAC(p->x, p->y, p->z, &grid, 0);
    a->unk4 = grid.g[0];
    a->unk8 = grid.g[1];
    a->unkC = grid.g[2];
    a->unk10 = grid.g[0];
    a->unk14 = grid.g[1];
    a->unk18 = grid.g[2];
    switch (a->unk44) {
    case 0:
    case 1:
    case 2:
    case 3:
        size = 0x60;
        break;
    case 4:
        size = 0x50;
        break;
    case 5:
        size = 0x40;
        break;
    case 6:
        size = 0x30;
        break;
    case 7:
        size = 0x20;
        break;
    case 8:
        size = 0xC0;
        break;
    default:
        size = 0xC0;
        break;
    }
    if (p) {}
    m = func_80230CB4(D_800BA8E8[a->unk84].unk2, -1, 0, size, NULL);
    m->unk40->unk10 = p->x - grid.o.x;
    m->unk40->unk14 = p->y - grid.o.y;
    m->unk40->unk18 = p->z - grid.o.z;
    m->unk58 = m->unk40->unk10;
    m->unk5C = m->unk40->unk14;
    m->unk60 = m->unk40->unk18;
    m->unk34 = a->unk70 * 10.0f;
    m->unk38 = a->unk74 * 10.0f;
    a->unk0 = m;
    func_802847E4(a, 0);
    func_80231408(func_802311E8(m), 0x2100000);
    func_80283DF0(a, 1);
    func_80285A84(a);
}

static void func_802863E0() {
}

void func_802863B0(Vec3f *arg0) {
    func_802829AC(arg0, 2);
}

static void func_80285F84(void) {
}

static void func_80285F8C(void) {
    UnkStruct_800BB340 *task;
    s32 padA[2];
    Vec3f pos2;
    s32 padB[2];
    UnkStruct_80288040 *a;
    s32 pad[3];
    Vec3f pos;
    UnkStruct_80288040 *a2;
    s32 far;

    func_80285F84();
    task = func_802391F0();
    for (;;) {
        switch (task->unkC) {
        case 0:
            func_80285A9C(task);
            break;
        case 1:
            a = &task->unk10->unk14;
            if ((D_800BA8E8[a->unk84].unk0 == 0x19) || (D_800BA8E8[a->unk84].unk0 == 0x1C)) {
                far = 0;
            } else {
                func_80250338(func_80243DDC(), &pos);
                if (((pos.x < a->unk0->unk40->unk10) && ((pos.x + 1300.0f) < a->unk0->unk40->unk10)) ||
                    ((a->unk0->unk40->unk10 < pos.x) && (a->unk0->unk40->unk10 < (pos.x - 1300.0f))) ||
                    ((pos.z < a->unk0->unk40->unk18) && ((pos.z + 1300.0f) < a->unk0->unk40->unk18)) ||
                    ((a->unk0->unk40->unk18 < pos.z) && (a->unk0->unk40->unk18 < (pos.z - 1300.0f)))) {
                    far = 1;
                } else {
                    far = 0;
                }
            }
            if (far) {
                func_80282598(task, 0);
            } else {
                task->unkC = func_80284FD4(a);
                if (task->unkC != 1) {
                    func_802313DC(a->unk0, 0x3FFFF);
                    if (((u8) (a->unk7A & 0xF)) == 1) {
                        if (a->unk79 != -1) {
                            func_8028A4E0(a->unk79);
                            a->unk79 = -1;
                        }
                    }
                    func_80282714(a);
                    a->unk20 = 0;
                    if (D_800BA8E8[a->unk84].unk0 == 0x19) {
                        func_8026C51C(0x1F1, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
                    } else if ((a->unk3D != 5) || (a->unk3C != 2)) {
                        if (task->unkC == 4) {
                            func_8026C51C(0x166, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
                        } else {
                            func_8026C51C(0x168, a->unk0->unk40->unk10, a->unk0->unk40->unk14, a->unk0->unk40->unk18);
                        }
                    }
                }
            }
            break;
        case 2:
            func_80282F44(task, 0);
            break;
        case 5:
            func_80282F44(task, 1);
            break;
        case 4:
            func_80282F44(task, 2);
            break;
        case 3:
            a2 = &task->unk10->unk14;
            pos2.x = a2->unk0->unk40->unk10;
            pos2.y = a2->unk0->unk40->unk14;
            pos2.z = a2->unk0->unk40->unk18;
            func_802829AC(&pos2, 3);
            func_80282598(task, 1);
            break;
        }
        func_80239094();
    }
}

static void func_80285A6C() {
}

static UnkStruct_800BA900 *func_80285A74() {
    s32 pada[1];
    Vec3f pos;
    s32 padb[17];
    UnkStruct_800BA900 *s;
    UnkStructA_40 *p;
    s32 i;
    f32 c;

    s = D_800BA900;
    func_80250338(func_80243DDC(), &pos);
    for (i = 0; i < 16; i++, s++) {
        if (s->unk0 == 2) {
            if (s->unk4 == 0) {
                p = s->unk14.unk0->unk40;
                if (pos.x < p->unk10) {
                    c = pos.x + 1100.0f;
                    if (((c - 50.0f) < p->unk10) && (p->unk10 < (c + 50.0f)) && ((pos.z - 1100.0f) < p->unk18) && (p->unk18 < (pos.z + 1100.0f))) {
                        return s;
                    }
                } else {
                    c = pos.x - 1100.0f;
                    if (((c - 50.0f) < p->unk10) && (p->unk10 < (c + 50.0f)) && ((pos.z - 1100.0f) < p->unk18) && (p->unk18 < (pos.z + 1100.0f))) {
                        return s;
                    }
                }
                if (pos.z < p->unk18) {
                    c = pos.z + 1100.0f;
                    if (((c - 50.0f) < p->unk18) && (p->unk18 < (c + 50.0f)) && ((pos.x - 1100.0f) < p->unk10) && (p->unk10 < (pos.x + 1100.0f))) {
                        return s;
                    }
                } else {
                    c = pos.z - 1100.0f;
                    if (((c - 50.0f) < p->unk18) && (p->unk18 < (c + 50.0f)) && ((pos.x - 1100.0f) < p->unk10) && (p->unk10 < (pos.x + 1100.0f))) {
                        return s;
                    }
                }
            } else {
                p = s->unk14.unk0->unk40;
                if ((pos.x < (p->unk10 - 1100.0f)) || ((p->unk10 + 1100.0f) < pos.x) ||
                    (pos.z < (p->unk18 - 1100.0f)) || ((p->unk18 + 1100.0f) < pos.z)) {
                    s->unk4--;
                    if (s->unk4 <= 0) {
                        s->unk4 = 0;
                    }
                }
            }
        }
    }
    return NULL;
}

static void func_80285A8C(UnkStruct_80288040 *a_, UnkStruct_800BA8E8 *e_) {
    void *f;
    s32 v;

    f = func_80226604(0xDD, 1);
    func_80225CCC((void *) f, e_->unk0 * 20, 0);
    func_8022616C(D_800BB488, 1, 20, f);
    func_80226368(f);
    (a_)->unk1F = D_800BB488[0];
    (a_)->unk3E = D_800BB488[1];
    (a_)->unk3C = D_800BB488[2];
    (a_)->unk3D = D_800BB488[3];
    (a_)->unk50.b[0] = D_800BB488[4];
    (a_)->unk1E = D_800BB488[5];
    (a_)->unk24 = (D_800BB488[6] << 24) + (D_800BB488[7] << 16) + (D_800BB488[8] << 8) + D_800BB488[9];
    v = (D_800BB488[10] << 8);
    v = (s16) (v + D_800BB488[11]);
    (a_)->unk2C = 2.0f * v * 0.01f;
    (a_)->unk1D = D_800BB488[12];
    (a_)->unk44 = D_800BB488[13];
    (a_)->unk6C = D_800BB488[14];
    (a_)->unk6D = D_800BB488[15];
    (a_)->unk70 = (u32) D_800BB488[16];
    (a_)->unk74 = (u32) D_800BB488[17];
    (a_)->unk7C = D_800BB488[18];
    (a_)->unk7E = D_800BB488[19];
}

static void func_80285A94(UnkStruct_80288040 *a_) {
    if (func_8023A840()->unk10 == 0) {
        (a_)->unk2C *= 0.5f;
        if ((a_)->unk6D >= 2) {
            (a_)->unk6D--;
        }
        (a_)->unk3E += (a_)->unk3E;
    }
}

static void func_80285A7C(UnkStruct_80288040 *a_, UnkStruct_800BA8E8 *e_) {
    func_80285A8C(a_, e_);
}

static void func_80285A84(UnkStruct_80288040 *a_) {
    func_80285A94(a_);
}

static void func_80285A9C(UnkStruct_800BB340 *arg0) {
    UnkStruct_800BA900 *r;
    UnkStruct_80288040 *a;

    func_80285A6C();
    r = func_80285A74();
    if (r != NULL) {
        a = &r->unk14;
        func_80285A7C(a, &D_800BA8E8[a->unk84]);
        goto L;
    L:
        if (D_800BA8E8[0].unk0) {}
        a->unk0->unk40->unk28 = 1.0f;
        a->unk0->unk40->unk2C = 1.0f;
        a->unk0->unk40->unk30 = 1.0f;
        func_80285A84(a);
        func_80285658(r, arg0);
    }
}

static void func_80285650() {
}

static s32 func_80285658(UnkStruct_800BA900 *arg0, UnkStruct_800BB340 *arg1) {
    UnkStruct_80288040 *a;
    f32 x;
    f32 z;
    s32 ok;
    s32 i;

    func_80285650();
    a = &arg0->unk14;
    x = a->unk0->unk40->unk10;
    z = a->unk0->unk40->unk18;
    D_800BB484 = a;
    ok = 1;
    i = 40;
    while ((func_80232D18(a->unk0, 0x10) != 0) ||
           (func_8028556C(func_8026D7D8((s32) ((a->unk0->unk40->unk10 + 50.0f) * 0.01),
                                        func_8026EE18(a->unk0->unk40->unk14),
                                        (s32) ((a->unk0->unk40->unk18 + 50.0f) * 0.01))) == 0)) {
        i--;
        if (i >= 31) {
            a->unk0->unk40->unk10 += 25.0f;
        } else if (i >= 21) {
            a->unk0->unk40->unk10 -= 25.0f;
        } else if (i >= 11) {
            a->unk0->unk40->unk18 += 25.0f;
        } else {
            a->unk0->unk40->unk18 -= 25.0f;
        }
        if ((i == 30) || (i == 20)) {
            a->unk0->unk40->unk10 = x;
        } else if (i == 10) {
            a->unk0->unk40->unk18 = z;
        } else if (i == 0) {
            ok = 0;
            a->unk0->unk40->unk18 = z;
            break;
        }
    }
    if (ok) {
        D_800BA900[a->unk80].unk8.x = a->unk0->unk40->unk10;
        D_800BA900[a->unk80].unk8.z = a->unk0->unk40->unk18;
    }
    if (!ok) {
        if (ok) {}
        func_802313DC(a->unk0, func_80282524(a));
        return 0;
    }
    if (a->unk48 != 0) {
        func_8028805C(a);
    }
    a->unk40 = 0;
    func_80231408(a->unk0, func_80282524(a));
    arg0->unk0 = 1;
    arg0->unk14.unk8C = (s32) arg1;
    a->unk0->unkC = 0x26E57;
    if (D_800BA8E8[a->unk84].unk0 == 0x1C) {
        a->unk0->unkC |= 8;
    }
    func_802847E4(a, 0);
    arg1->unkC = 1;
    arg1->unk10 = arg0;
    return 1;
}

static void func_80285554() {
}

static void func_8028555C() {
}

static void func_80285564() {
}

static s32 func_8028556C(s32 arg0) {
    UnkStruct_80288040 *p;

    func_80285564();
    func_8028555C();
    func_80285554();
    p = D_800BB484;
    if ((arg0 & 0x2000) ||
        (!(p->unk24 & 0x20) && ((arg0 & 0xF) == 0xF)) ||
        (!(p->unk24 & 0x10) && (arg0 & 0x60)) ||
        (!(p->unk24 & 1) && !(arg0 & 0xF)) ||
        (!(p->unk24 & 8) && (((arg0 & 0xF) == 3) || ((arg0 & 0xF) == 4) || ((arg0 & 0xF) == 5) || ((arg0 & 0xF) == 6))) ||
        (!(p->unk24 & 4) && (((arg0 & 0xF) == 9) || ((arg0 & 0xF) == 2) || ((arg0 & 0xF) == 10) || ((arg0 & 0xF) == 11))) ||
        (!(p->unk24 & 0x40) && ((arg0 & 0xF) == 0x1C00)) ||
        (!(p->unk24 & 2) && ((arg0 & 0xF) == 1))) {
        return 0;
    }
    return 1;
}

static s32 func_80284FCC(UnkStruct_80288040 *arg0) {
    if (arg0->unk0->unk10 & 0x40000000) {
        func_8027F820(arg0->unk0);
        return 1;
    }
    return 0;
}

static s32 func_80284FD4(UnkStruct_80288040 *arg0) {
    s32 ret;
    s32 r;
    s32 st;
    f32 target;
    f32 step;
    f32 diff;

    if (func_80284FCC(arg0)) {
        return 3;
    }
    r = func_80284CAC(arg0);
    if (r != 1) {
        return r;
    }
    func_80284B30(arg0);
    ret = 1;
    switch ((u8) (arg0->unk7A & 0xF0)) {
    case 0x00:
        switch ((u8) (arg0->unk7A & 0xF)) {
        case 0:
            if (arg0->unk1E != 0) {
                func_802848E8(arg0);
            }
            break;
        case 2:
            if ((arg0->unk1E != 0) && (arg0->unk3C == 1)) {
                arg0->unk0->unk68 = 0.0f;
            }
            break;
        case 1:
            arg0->unk6E--;
            if (arg0->unk6E <= 0) {
                arg0->unk6E = 0;
                arg0->unk78 = 0;
                if (arg0->unk79 != -1) {
                    func_8028A4E0(arg0->unk79);
                    arg0->unk79 = -1;
                }
                func_80282454(arg0);
                func_802847E4(arg0, 1);
                func_802313DC(arg0->unk0, 0x400);
                func_80231408(arg0->unk0, func_802824B4(arg0) | 4);
            }
            break;
        case 3:
            func_802831A8(arg0);
            break;
        case 5:
            arg0->unk6E--;
            if (arg0->unk6E <= 0) {
                arg0->unk6E = 0;
                func_80282454(arg0);
                func_80283F30(arg0);
                func_80283DF0(arg0, 2);
            } else if (arg0->unk6E >= 52) {
                arg0->unk0->unk40->unk20 -= 2.0f * arg0->unk2C;
            } else if (arg0->unk6E >= 45) {
                arg0->unk0->unk40->unk20 -= arg0->unk2C;
            } else if (arg0->unk6E >= 37) {
                arg0->unk0->unk40->unk20 += arg0->unk2C;
            } else if (arg0->unk6E >= 30) {
                arg0->unk0->unk40->unk20 += 2.0f * arg0->unk2C;
            } else if (arg0->unk6E >= 22) {
                arg0->unk0->unk40->unk20 += 2.0f * arg0->unk2C;
            } else if (arg0->unk6E >= 15) {
                arg0->unk0->unk40->unk20 += arg0->unk2C;
            } else if (arg0->unk6E >= 7) {
                arg0->unk0->unk40->unk20 -= arg0->unk2C;
            } else {
                arg0->unk0->unk40->unk20 -= 2.0f * arg0->unk2C;
            }
            break;
        }
        ret = func_8028456C(arg0);
        func_80283FCC(arg0);
        target = func_8028322C(arg0);
        st = (u8) (arg0->unk7A & 0xF);
        step = 2.0f * arg0->unk2C;
        if ((st == 0) || (st == 2)) {
            while (arg0->unk0->unk40->unk20 >= 360.0f) {
                arg0->unk0->unk40->unk20 -= 360.0f;
            }
            while (arg0->unk0->unk40->unk20 < 0.0f) {
                arg0->unk0->unk40->unk20 += 360.0f;
            }
            if (target < arg0->unk0->unk40->unk20) {
                diff = arg0->unk0->unk40->unk20 - target;
                if (diff < step) {
                    step = diff;
                }
                if (diff <= ((target + 360.0f) - arg0->unk0->unk40->unk20)) {
                    arg0->unk0->unk40->unk20 -= step;
                } else {
                    arg0->unk0->unk40->unk20 += step;
                }
            } else {
                diff = target - arg0->unk0->unk40->unk20;
                if (diff < step) {
                    step = diff;
                }
                if (diff < ((arg0->unk0->unk40->unk20 + 360.0f) - target)) {
                    arg0->unk0->unk40->unk20 += step;
                } else {
                    arg0->unk0->unk40->unk20 -= step;
                }
            }
        }
        break;
    case 0x20:
        if (((u8) (arg0->unk7A & 0xF)) == 3) {
            func_802831A8(arg0);
        }
        func_802727D8(arg0->unk68);
        break;
    case 0x10:
        func_802733C8(arg0->unk0);
        if ((arg0->unk7A & 0xF) == 3) {
            func_802831A8(arg0);
        }
        break;
    case 0x30:
        func_802727D8(arg0->unk68);
        break;
    }
    if (ret != 1) {
        r = ret;
    } else {
        r = 1;
    }
    return r;
}

static void func_80284C9C() {
}

static void func_80284CA4() {
}

static s32 func_80284CAC(UnkStruct_80288040 *arg0) {
    s32 hit;

    func_80284CA4();
    func_80284C9C();
    if (arg0->unk78 == 0) {
        if (arg0->unk0->unk10 & 0x40) {
            if (DEC_80284CA4(arg0)) {
                return 2;
            }
            if ((arg0->unk0->unk10 & 0x2000) && DEC_80284CA4(arg0)) {
                return 2;
            }
            if ((arg0->unk0->unk10 & 0x4000) && DEC_80284CA4(arg0)) {
                return 2;
            }
            if (D_800BA8E8[arg0->unk84].unk0 == 0x19) {
                func_8026C51C(0x1EB, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
                func_8028A81C(0x16, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14 + 140.0f, arg0->unk0->unk40->unk18, 0);
                func_8028A81C(0x11, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14 + 140.0f, arg0->unk0->unk40->unk18, 0);
            } else {
                func_8026C51C(0x167, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
            }
            if (arg0->unk48 != 0) {
                func_8028805C(arg0);
            }
            arg0->unk40 = 0;
            if (((u8) (arg0->unk7A & 0xF)) == 1) {
                if (arg0->unk79 != -1) {
                    func_8028A4E0(arg0->unk79);
                    arg0->unk79 = -1;
                }
            }
            func_80282430(arg0, 0xF, 3);
            arg0->unk78 = 1;
            arg0->unk6E = 60;
            func_80231408(arg0->unk0, 0x40000);
            return 1;
        }
        hit = 0;
        if ((arg0->unk0->unk10 & 0x2000) && (arg0->unk0->unk10 & 0x400)) {
            switch (arg0->unk6C & 0xF) {
            case 0:
                hit = 1;
                break;
            case 1:
                func_8028304C(arg0, 0);
                break;
            }
        } else if ((arg0->unk0->unk10 & 2) && (arg0->unk0->unk10 & 0x400)) {
            func_8028304C(arg0, 1);
        } else if ((arg0->unk0->unk10 & 0x20000) || !(arg0->unk0->unk10 & 4)) {
            if (arg0->unk0->unk10 & 0x200) {
                func_8028304C(arg0, 0);
            } else if (arg0->unk0->unk10 & 0x400) {
                func_8028304C(arg0, 1);
            } else if (arg0->unk0->unk10 & 0x800) {
                func_8028304C(arg0, 2);
            }
        }
        if (hit != 0) {
            return 4;
        }
    }
    return 1;
}

static void func_80284B20() {
}

static void func_80284B28() {
}

static void func_80284B30(UnkStruct_80288040 *arg0) {
    f32 step;
    UnkStructA_40_48_4 *p;

    func_80284B28();
    func_80284B20();
    step = 0.0f;
    switch ((u8) (arg0->unk7A & 0xF)) {
    case 3:
    case 4:
    case 5:
        break;
    case 0:
        step = arg0->unk2C * 0.6;
        break;
    case 2:
        if (arg0->unk2C == 0.0f) {
            step = 1.0f;
        } else {
            step = arg0->unk2C * 0.6;
        }
        break;
    case 1:
        step = 1.0f;
        break;
    }
    if (arg0->unk0->unk40->unk48 != NULL) {
        p = arg0->unk0->unk40->unk48->unk4;
        p->unk4 += step;
        if (func_80229D3C(arg0->unk0->unk40, 0) <= (p = arg0->unk0->unk40->unk48->unk4)->unk4) {
            if ((arg0->unk7A == 2) && (arg0->unk3C == 1)) {
                p->unk4 -= step;
            } else {
                p->unk4 = 0.0f;
            }
        }
    }
}

static void func_802848D8() {
}

static void func_802848E0() {
}

static void func_802848E8(UnkStruct_80288040 *arg0) {
    f32 amp;
    UnkStructA_40 *p;

    func_802848E0();
    func_802848D8();
    switch (arg0->unk30) {
    case 0:
        amp = 0.0f;
        switch (arg0->unk1E) {
        case 1:
            amp = 20.0f;
            break;
        case 2:
            amp = 0.1f;
            break;
        case 3:
            amp = 5.0f;
            break;
        }
        arg0->unk0->unk68 = (sinf(arg0->unk34) * amp) - arg0->unk0->unk68;
        arg0->unk34 += 0.1f;
        if (arg0->unk34 >= 360.0f) {
            arg0->unk34 -= 360.0f;
        }
        p = arg0->unk0->unk40;
        if ((arg0->unk38 + 100.0f) < p->unk14) {
            p->unk14 -= p->unk14 - (arg0->unk38 + 100.0f);
        } else if (p->unk14 < (arg0->unk38 - 100.0f)) {
            p->unk14 += (arg0->unk38 - 100.0f) - p->unk14;
        }
        break;
    case 1:
        break;
    case 2:
        if ((arg0->unk0->unk68 == 0.0f) && (arg0->unk0->unk6C == 0.0f)) {
            if (p) {}
            arg0->unk30 = 3;
            arg0->unk0->unk68 = 2.0f;
            arg0->unk0->unk6C = 0.0f;
            arg0->unk0->unk70 = 0.0f;
        }
        break;
    case 3:
        if (arg0->unk38 <= arg0->unk0->unk40->unk14) {
            arg0->unk0->unk40->unk14 = arg0->unk38;
            arg0->unk30 = 0;
            arg0->unk0->unk68 = 0.0f;
            arg0->unk0->unk6C = 0.0f;
            arg0->unk0->unk70 = 0.0f;
            arg0->unk34 = 0.0f;
        } else if (arg0->unk0->unk68 < 2.0f) {
            arg0->unk0->unk68 = 2.0f;
        }
        break;
    }
}

static void func_802847DC() {
}

static void func_802847E4(UnkStruct_80288040 *arg0, s32 arg1) {
    f32 h;

    func_802847DC();
    arg0->unk38 = arg0->unk0->unk40->unk14;
    if (arg0->unk1E == 0) {
        arg0->unk30 = 0;
        arg0->unk0->unk68 = 0.0f;
        arg0->unk0->unk6C = 0.0f;
        arg0->unk0->unk70 = 1.6333334f;
        return;
    }
    h = 300.0f;
    if (D_800BA8E8[arg0->unk84].unk0 == 9) {
        h = 200.0f;
    }
    if (arg1 == 0) {
        arg0->unk38 = D_800BA900[arg0->unk80].unk8.y + h;
    } else {
        arg0->unk38 = arg0->unk0->unk40->unk14 + h;
    }
    arg0->unk30 = 2;
    arg0->unk0->unk68 = 0.0f;
    arg0->unk0->unk6C = 0.0f;
    arg0->unk0->unk70 = 0.8166667f;
}

static s32 func_8028456C(UnkStruct_80288040 *arg0) {
    f32 speed;
    s32 st;
    u16 tile;

    func_8028425C(arg0);
    st = arg0->unk7A & 0xF;
    if (arg0->unk30 != 3) {
        arg0->unk40++;
        arg0->unk40 &= 0x7FFF;
        if ((arg0->unk3D != 0) && ((u8) st != 1) && ((u8) st != 3) &&
            ((arg0->unk48 != 0) || ((u32) arg0->unk40 >= arg0->unk3E))) {
            func_802881A0(arg0);
            if (arg0->unk48 != 0) {
                arg0->unk40 = 0;
            }
        }
        st = arg0->unk7A & 0xF;
    }
    speed = arg0->unk2C;
    switch ((u8) st) {
    case 2:
    case 4:
        break;
    case 0:
        if (arg0->unk1F == 40) {
            speed = 0.0f;
        }
        break;
    case 1:
        speed = 0.0f;
        break;
    case 5:
        speed = 0.0f;
        break;
    case 3:
        speed = 0.0f;
        break;
    }
    func_80291944(arg0->unk0, arg0->unk1C & 0xF0, speed);
    tile = func_8026D7D8((s32) ((arg0->unk0->unk40->unk10 + 50.0f) * 0.01), func_8026EE18(arg0->unk0->unk40->unk14),
                         (s32) ((arg0->unk0->unk40->unk18 + 50.0f) * 0.01));
    if (arg0->unk6C & 0x20) {
        if (tile & 0x1C00) {
            func_8027F858(arg0->unk0, tile >> 10);
        } else if ((tile & 0xF) == 9) {
            if ((arg0->unk0->unk68 == 0.0f) && (arg0->unk0->unk6C == 0.0f)) {
                return 5;
            }
        }
    }
    return 1;
}

static void func_8028422C() {
}

static void func_80284234() {
}

static void func_8028423C() {
}

static void func_80284244() {
}

static void func_8028424C() {
}

static s32 func_80284254(UnkStruct_80288040 *arg0) {
    switch (func_80283D9C(arg0)) {
    case 1:
        switch (arg0->unk1F) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 4;
        case 4:
            return 2;
        case 5:
            return 4;
        }
        break;
    case 2:
        switch (arg0->unk1F) {
        case 20:
            return 1;
        case 21:
            return 2;
        case 22:
            return 3;
        case 23:
            return 4;
        case 24:
            return 4;
        case 25:
            return 6;
        }
        break;
    case 3:
        switch (arg0->unk1F) {
        case 40:
            return 0;
        case 41:
            return 2;
        case 42:
            return 6;
        case 43:
            return 3;
        case 44:
            return 4;
        case 45:
            return 2;
        }
        break;
    }
    return 0;
}

static void func_8028425C(UnkStruct_80288040 *arg0) {
    s32 n;
    s32 r;
    s32 x;

    func_8028424C();
    func_80284244();
    func_8028423C();
    func_80284234();
    func_8028422C();
    x = (u8) (s32) ((arg0->unk0->unk40->unk10 + 50.0f) * 0.01);
    if ((x != arg0->unk10) ||
        (arg0->unk18 != (u8) (s32) ((arg0->unk0->unk40->unk18 + 50.0f) * 0.01))) {
        arg0->unk10 = x;
        arg0->unk18 = (u8) (s32) ((arg0->unk0->unk40->unk18 + 50.0f) * 0.01);
        n = func_80284254(arg0);
        if (x) {}
        arg0->unk20++;
        if (n == 0) {
            arg0->unk1C |= 1;
        } else if (arg0->unk20 >= n) {
            arg0->unk20 = 0;
            func_80283DF0(arg0, 1);
            func_80283F30(arg0);
        }
        if (func_80283D9C(arg0) == 3) {
            r = func_80283794(arg0, arg0->unk1C);
            if (r != 0) {
                func_80283F38(arg0);
                arg0->unk1C = r & 0xF0;
            }
        }
    }
}
static void func_80283FAC() {
}

static void func_80283FB4() {
}

static void func_80283FBC() {
}

static void func_80283FC4() {
}

static void func_80283FCC(UnkStruct_80288040 *arg0) {
    UnkStructA *p;
    s32 flags;

    func_80283FC4();
    func_80283FBC();
    func_80283FB4();
    func_80283FAC();
    func_80230914(arg0->unk0);
    D_800BB484 = arg0;
    if (func_802909FC(arg0->unk0, func_8028556C) != 0) {
        func_80283F38(arg0);
        func_80283DF0(arg0, 0);
    }
    if (D_800BA8E8[arg0->unk84].unk0 == 0x1C) {
        p = func_8022F550(arg0->unk0, 0xF);
        if (p == NULL) {
            if (*(UnkStructA **) arg0->unk0->unk20 != NULL) {
                p = *(UnkStructA **) arg0->unk0->unk20;
            }
        }
        if ((p != NULL) && (func_8022F4AC(p, 0x10, arg0->unk0) == 0)) {
            func_80270C24(p, func_80234248(7) << 5, 3);
        }
    }
    p = func_8022F550(arg0->unk0, 0x11);
    if ((p != NULL) && (p->unk68 <= p->unk6C)) {
        arg0->unk0->unk40->unk10 = arg0->unk0->unk58;
        arg0->unk0->unk40->unk14 = arg0->unk0->unk5C;
        arg0->unk0->unk40->unk18 = arg0->unk0->unk60;
        if (!(arg0->unk7A & 0xF0) && ((arg0->unk0->unk68 != 0.0f) || (arg0->unk0->unk6C != 0.0f))) {
            flags = (u8) (arg0->unk7A & 0xF);
            if (flags == 2) {
                if (arg0->unk48 != 0) {
                    func_8028805C(arg0);
                }
                arg0->unk40 = 0;
            } else if (!(p->unk8 & 4) || (flags == 1) || (p->unk8 & 0x20000) || (arg0->unk30 == 2) || (arg0->unk30 == 3)) {
                arg0->unk68 = func_802700EC(arg0->unk0, p, arg0->unk1C & 0xF0, arg0->unk2C);
                func_80282430(arg0, 0xF0, 0x30);
                func_80231408(arg0->unk0, 0x20400);
            }
        }
        func_80283F38(arg0);
        func_80283DF0(arg0, 2);
    }
    func_80232DB4(arg0->unk0);
}

static s32 func_80283F28(UnkStruct_80288040 *arg0) {
    if ((arg0->unk1D == 0) || (arg0->unk1D == 1) || (arg0->unk1D == 2)) {
        return 0;
    }
    return 1;
}

static void func_80283F30(UnkStruct_80288040 *arg0) {
    if (func_80283F28(arg0) == 0) {
        arg0->unk28 = 0xAA;
    } else {
        arg0->unk28 = 0;
    }
}

static void func_80283F38(UnkStruct_80288040 *arg0) {
    if (arg0->unk28 != 0xFF) {
        arg0->unk28 |= 1 << (arg0->unk1C >> 5);
        return;
    }
    func_80283F30(arg0);
}

static void func_80283DF0(UnkStruct_80288040 *arg1, s32 arg0) {
    if (arg0 == 0) {
        func_802836F0(arg1, 0);
    } else if (arg0 == 2) {
        func_802836F0(arg1, 1);
    } else if (arg0 == 1) {
        if (!((u8) (arg1->unk7A & 0xF))) {
            switch (arg1->unk1F) {
            case 4:
            case 5:
            case 24:
            case 25:
            case 42:
                func_80282430(arg1, 0xF, 5);
                arg1->unk6E = 60;
                if (arg1->unk1E != 0) {
                    arg1->unk0->unk68 = 0.0f;
                }
                break;
            }
        }
        switch (func_80283D9C(arg1)) {
        case 1:
            func_80283CF0(arg1);
            break;
        case 2:
            func_802836F0(arg1, 0);
            break;
        case 3:
            if (arg1->unk1F == 45) {
                func_80283CF0(arg1);
            } else {
                func_802836F0(arg1, 0);
            }
            break;
        }
    }
}

static s32 func_80283D9C(UnkStruct_80288040 *arg0) {
    if (arg0->unk1F < 20) {
        return 1;
    }
    if ((arg0->unk1F >= 20) && (arg0->unk1F < 40)) {
        return 2;
    }
    if (arg0->unk1F >= 40) {
        return 3;
    }
    return -1;
}

static void func_80283CF0(UnkStruct_80288040 *arg0) {
    Vec3f pos;
    s32 player;
    s32 y;

    player = func_80243DDC();
    if (player == -1) {
        func_802836F0(arg0, 0);
        return;
    }
    func_80250338(player, &pos);
    y = func_8026EE18(pos.y);
    if ((func_8026EE18(arg0->unk0->unk40->unk14) == y) || (arg0->unk24 & 1) || (arg0->unk24 & 8)) {
        func_80283B04(arg0, &pos);
    } else {
        func_802836F0(arg0, 0);
    }
}

static s32 func_80283AFC(UnkStructA_40 *p, Vec3f *arg1) {
    if ((p->unk10 + 50.0f) < arg1->x) {
        if ((p->unk18 + 50.0f) < arg1->z) {
            return 3;
        } else if (arg1->z < (p->unk18 - 50.0f)) {
            return 1;
        } else {
            return 2;
        }
    } else if (arg1->x < (p->unk10 - 50.0f)) {
        if ((p->unk18 + 50.0f) < arg1->z) {
            return 5;
        } else if (arg1->z < (p->unk18 - 50.0f)) {
            return 7;
        } else {
            return 6;
        }
    }
    if (p->unk18 < arg1->z) {
        return 4;
    }
    return 0;
}

void func_80283B04(UnkStruct_80288040 *arg0, Vec3f *arg1) {
    s32 failed;
    s32 i;
    s32 dir;
    s32 d;

    failed = 1;
    dir = func_80283AFC(arg0->unk0->unk40, arg1) & 0xFF;
    if (dir) {}
    for (i = 0; i < 4; i++) {
        d = dir + i;
        if (d >= 8) {
            d -= 8;
        }
        if (!(arg0->unk28 & (1 << d))) {
            arg0->unk1C = d << 5;
            failed = 0;
            break;
        }
        d = dir - i;
        if (d < 0) {
            d += 8;
        }
        if (!(arg0->unk28 & (1 << d))) {
            arg0->unk1C = d << 5;
            failed = 0;
            break;
        }
    }
    if ((failed != 0) || (func_80283794(arg0, arg0->unk1C) != 0)) {
        arg0->unk1C = func_80283314(arg0, 1, 1) << 5;
    }
    if (0) {
        func_802836F0(NULL, 0);
    }
}
static void func_80283784() {
}

static void func_8028378C() {
}

static s32 func_80283794(UnkStruct_80288040 *arg0, u8 arg1) {
    s32 pos[3];
    s32 pad[7];
    s8 range[2];
    s8 gx;
    s8 gz;
    s32 flags;

    func_8028378C();
    if (arg1) {}
    func_80283784();
    pos[0] = (arg0->unk0->unk40->unk10 + 50.0f) * 0.01;
    pos[2] = (arg0->unk0->unk40->unk18 + 50.0f) * 0.01;
    pos[1] = func_8026EE18(arg0->unk0->unk40->unk14);
    switch (arg1) {
    case 0x00:
        pos[2]--;
        break;
    case 0x20:
        pos[0]++; pos[2]--;
        break;
    case 0x40:
        pos[0]++;
        break;
    case 0x60:
        pos[0]++; pos[2]++;
        break;
    case 0x80:
        pos[2]++;
        break;
    case 0xA0:
        pos[0]--; pos[2]++;
        break;
    case 0xC0:
        pos[0]--;
        break;
    case 0xE0:
        pos[0]--; pos[2]--;
        break;
    }
    gx = arg0->unk4;
    gz = arg0->unkC;
    flags = 0;
    switch (arg0->unk1F) {
    case 40:
        return 0;
    case 41:
        range[1] = 3;
        break;
    case 42:
        range[1] = 3;
        break;
    case 43:
        range[1] = 5;
        break;
    case 44:
        range[1] = 8;
        break;
    case 45:
        range[1] = 8;
        break;
    }
    if (gx >= pos[0]) {
        if (pos[0] < gx) {
            flags = 1;
        }
        gx = gx - pos[0];
    } else {
        flags = 2;
        gx = pos[0] - gx;
    }
    if (gz >= pos[2]) {
        if (pos[2] < gz) {
            flags |= 0x10;
        }
        gz = gz - pos[2];
    } else {
        flags |= 0x20;
        gz = pos[2] - gz;
    }
    if ((range[1] >= gx) && (range[1] >= gz)) {
        return 0;
    }
    switch (flags) {
    case 1:
        flags = 0x40;
        break;
    case 2:
        flags = 0xC0;
        break;
    case 16:
        flags = 0x80;
        break;
    case 17:
        flags = 0x60;
        break;
    case 18:
        flags = 0xA0;
        break;
    case 32:
        flags = 0;
        break;
    case 33:
        flags = 0x20;
        break;
    case 34:
        flags = 0xE0;
        break;
    }
    return flags | 1;
}

static void func_802836F0(UnkStruct_80288040 *arg0, s32 arg1) {
    s32 mode;

    switch (arg0->unk1D) {
    case 0:
        mode = 0;
        break;
    case 1:
        mode = 1;
        break;
    case 2:
        mode = 2;
        break;
    case 3:
        mode = 0;
        break;
    case 4:
        mode = 1;
        break;
    case 5:
        mode = 2;
        break;
    }
    arg0->unk1C = func_80283314(arg0, mode, arg1) << 5;
}

static void func_80283304() {
}

static void func_8028330C() {
}

static u8 func_80283314(UnkStruct_80288040 *arg2, s32 arg0, s32 arg1) {
    s32 n;
    s32 i;
    s32 dir;
    s32 d;

    func_8028330C();
    func_80283304();
    switch (arg0) {
    case 0:
        n = func_8025E63C() * 5.0;
        break;
    case 1:
        if ((s32) (func_8025E63C() * 10.0) >= 3) {
            n = 0;
        } else if ((s32) (func_8025E63C() * 2) == 1) {
            n = 1;
        } else if ((s32) (func_8025E63C() * 2) == 1) {
            n = 2;
        } else if ((s32) (func_8025E63C() * 2) == 1) {
            n = 3;
        } else {
            n = 4;
        }
        break;
    case 2:
        if ((s32) (func_8025E63C() * 10.0) >= 3) {
            n = 4;
        } else if ((s32) (func_8025E63C() * 2) == 1) {
            n = 3;
        } else if ((s32) (func_8025E63C() * 2) == 1) {
            n = 2;
        } else if ((s32) (func_8025E63C() * 2) == 1) {
            n = 1;
        } else {
            n = 0;
        }
        break;
    }
    if (n < arg1) {
        n = arg1;
    }
    dir = arg2->unk1C >> 5;
    for (i = n; i >= 0; i--) {
        d = dir + i;
        if (d >= 8) {
            d -= 8;
        }
        if (!(arg2->unk28 & (1 << d))) {
            return d;
        }
        d = dir - i;
        if (d < 0) {
            d += 8;
        }
        if (!(arg2->unk28 & (1 << d))) {
            return d;
        }
    }
    i = n;
    if (i < 5) {
    loop:
        d = dir + i;
        if (d >= 8) {
            d -= 8;
        }
        if (!(arg2->unk28 & (1 << d))) {
            return d;
        }
        d = dir - i;
        if (d < 0) {
            d += 8;
        }
        if (!(arg2->unk28 & (1 << d))) {
            return d;
        }
        i++;
        if (i < 5) goto loop;
    }
    return dir | 1;
}

f32 func_8028322C(UnkStruct_80288040 *arg0) {
    if (0) {
        func_802831A8(NULL);
    }
    switch (arg0->unk1C) {
    case 0x00:
        return 180.0f;
    case 0x20:
        return 135.0f;
    case 0x40:
        return 90.0f;
    case 0x60:
        return 45.0f;
    case 0x80:
        return 0.0f;
    case 0xA0:
        return 315.0f;
    case 0xC0:
        return 270.0f;
    case 0xE0:
        return 225.0f;
    }
    return 0.0f;
}

static void func_802831A8(UnkStruct_80288040 *arg0) {
    arg0->unk6E -= 1;
    if (arg0->unk6E <= 0) {
        arg0->unk6E = 0;
        func_802313DC(arg0->unk0, 0x40000);
        arg0->unk78 = 0;
        if (((u8) (arg0->unk7A & 0xF0)) == 0x10) {
            func_8028304C(arg0, 1);
        } else {
            func_80231408(arg0->unk0, func_802824B4(arg0) | 4);
            func_80282454(arg0);
        }
    }
}

static void func_8028304C(UnkStruct_80288040 *arg0, s32 arg1) {
    if ((arg0->unk6C & 0x10) && (((u8) (arg0->unk7A & 0xF)) != 1)) {
        if (arg0->unk48 != 0) {
            func_8028805C(arg0);
        }
        arg0->unk40 = 0;
        func_80229E38(arg0->unk0->unk40, 1, 0);
        if (((u8) (arg0->unk7A & 0xF)) != 1) {
            if (arg0->unk79 != -1) {
                func_8028A4E0(arg0->unk79);
                arg0->unk79 = -1;
            }
            arg0->unk79 = func_8028A81C(5, 0.0f, 130.0f, 0.0f, arg0->unk0);
        }
        func_80282430(arg0, 0xF, 1U);
        func_802313DC(arg0->unk0, func_802824B4(arg0));
        if (arg0->unk1E != 0) {
            func_8028301C(arg0, 2, 0, 0, 0.8166667f);
        }
        switch (arg1) {
        case 0:
            arg0->unk6E = 600;
            break;
        case 1:
            arg0->unk6E = 300;
            break;
        case 2:
            arg0->unk6E = 120;
            break;
        }
    }
}

static void func_80283014() {
}

void func_8028301C(UnkStruct_80288040 *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    func_80283014();
    arg0->unk30 = arg1;
    arg0->unk0->unk68 = arg2;
    arg0->unk0->unk6C = arg3;
    arg0->unk0->unk70 = arg4;
    if (0) {
        func_80282F44(NULL, 0);
    }
}

static void func_80282F44(UnkStruct_800BB340 *arg0, s32 arg1) {
    UnkStructA_40 *p;
    UnkStruct_80288040 *act;
    s32 v;

    act = &arg0->unk10->unk14;
    v = 0;
    if (act->unk3D == 5) {
        v = 2;
    }
    if (act->unk3C == 2) {
        v |= 1;
    }
    if (v < 2) {
        if (func_80282AF0(arg0, arg1) != 0) {
            func_80282598(arg0, 1);
        }
    } else {
        if (v == 3) {
            arg1 = 2;
        }
        if (func_80282AF0(arg0, arg1) != 0) {
            act->unk48 = 2;
            p = act->unk0->unk40;
            func_8026C51C(0x16B, p->unk10, p->unk14, p->unk18);
            func_802881A0(act);
            func_80282598(arg0, 1);
        }
    }
}

static s32 func_80282AE8(UnkStruct_80288040 *act) {
    UnkStructA_40 *p;

    if (act->unk20++ < 50) {
        act->unk0->unk40->unk20 += 14.0f;
        act->unk0->unk40->unk28 -= 0.01f;
        act->unk0->unk40->unk2C -= 0.01f;
        act->unk0->unk40->unk30 -= 0.01f;
    } else {
        return 1;
    }
    if (act->unk20 == 1) {
        act->unk0->unk68 = 15.0f;
        act->unk0->unk6C = 0.8f;
        act->unk0->unk70 = 0.8f;
        p = act->unk0->unk40;
        func_8028A81C(7, p->unk10, p->unk14 + 100.0f, p->unk18, 0);
    } else if (act->unk20 == 10) {
        p = act->unk0->unk40;
        func_8028A81C(7, p->unk10 + 30.0f, p->unk14 + 50.0f, p->unk18 - 30.0f, 0);
    } else if (act->unk20 == 18) {
        p = act->unk0->unk40;
        func_8028A81C(13, p->unk10, p->unk14 + 100.0f, p->unk18, 0);
    }
    func_80230914(act->unk0);
    return 0;
}

static s32 func_80282AE0(UnkStruct_80288040 *act) {
    if (act->unk20++ < 3) {
        act->unk0->unk40->unk2C -= 0.12;
    } else if (act->unk20 < 8) {
        act->unk0->unk40->unk2C -= 0.08;
    } else if (act->unk20 < 15) {
        act->unk0->unk40->unk2C -= 0.04;
    } else {
        func_8028A81C(1, act->unk0->unk40->unk10, act->unk0->unk40->unk14 + 100.0f, act->unk0->unk40->unk18, 0);
        return 1;
    }
    return 0;
}

static s32 func_80282AD8(UnkStruct_80288040 *act) {
    if (act->unk20++ < 30) {
        if (act->unk20 == 1) {
            func_80231408(act->unk0, 0x40000);
        }
    } else {
        return 1;
    }
    return 0;
}

static s32 func_80282AF0(UnkStruct_800BB340 *arg0, s32 arg1) {
    UnkStruct_80288040 *act;
    UnkStructA_40 *p;
    s32 ret;
    Vec3f pos;

    func_80282AD0();
    act = &arg0->unk10->unk14;
    ret = 0;
    switch (arg1) {
    case 0:
        ret = func_80282AE8(act);
        break;
    case 2:
        ret = func_80282AE0(act);
        break;
    case 1:
        ret = func_80282AD8(act);
        break;
    }
    func_80291944(act->unk0, act->unk1C & 0xF0, 0.0f);
    if (ret == 1) {
        pos.x = act->unk0->unk40->unk10;
        pos.y = act->unk0->unk40->unk14;
        pos.z = act->unk0->unk40->unk18;
        if (func_802829AC(&pos, arg0->unkC) == 0) {
            if ((arg1 != 3) && (act->unk7C >= (s32) (func_8025E63C() * 100.0))) {
                p = act->unk0->unk40;
                func_8027B7C4(act->unk7E, p->unk10, p->unk14 + 150.0f, p->unk18);
            }
        }
    }
    return ret;
}

static void func_80282AD0() {
}

static void func_802829A4() {
}

static s32 func_802829AC(Vec3f *arg1, s32 arg0) {
    s32 ret = 0;
    UnkStruct_8023A840 *p;
    s32 kind;

    func_802829A4();
    if ((arg0 == 2) || (arg0 == 3) || (arg0 == 5) || (arg0 == 4)) {
        if (D_800BC520 < 99) {
            D_800BC520++;
            if (arg0 != 3) {
                switch (D_800BC520) {
                case 30:
                case 60:
                case 90:
                    p = func_8023A840();
                    kind = D_802A1AF0[p->unk4][p->unk8];
                    if (kind != -1) {
                        ret = 1;
                        func_8027B7C4(kind, arg1->x, arg1->y, arg1->z);
                    }
                    break;
                case 99:
                    func_8027B7C4(4, arg1->x, arg1->y, arg1->z);
                    func_8027B7C4(8, arg1->x, arg1->y, arg1->z);
                    func_8027B7C4(8, arg1->x, arg1->y, arg1->z);
                    break;
                }
            }
        }
    }
    return ret;
}

void func_80282978(Vec3f *arg0) {
    func_8028275C(arg0->x, arg0->y, arg0->z);
}

void func_80282934(void) {
    UnkStructA_40 *pos;

    pos = func_802443F4(func_80243DDC())->unk40;
    func_8028275C(pos->unk10, pos->unk14, pos->unk18);
}

void func_8028275C(f32 arg0, f32 arg1, f32 arg2) {
    UnkStructA_40 *pos;
    UnkStruct_800BA900 *obj;
    UnkStruct_800BB340 *slot;
    UnkStruct_80288040 *act;
    s32 i;

    slot = D_800BB340;
    for (i = 0; i < 16; i++, slot++) {
        if (slot->unk4 != 0) {
            obj = slot->unk10;
            if (obj != NULL) {
                act = &obj->unk14;
                if (obj->unk0 != 0) {
                    pos = act->unk0->unk40;
                    if (((arg0 - 200.0f) <= pos->unk10) && (pos->unk10 <= (arg0 + 200.0f)) &&
                        ((arg1 - 200.0f) <= pos->unk14) && (pos->unk14 <= (arg1 + 200.0f)) &&
                        ((arg2 - 200.0f) <= pos->unk18) && (pos->unk18 <= (arg2 + 200.0f))) {
                        func_8028A81C(1, pos->unk10, pos->unk14 + 100.0f, pos->unk18, 0);
                        func_80282714(act);
                        func_80282598(slot, 2);
                    }
                }
            }
        }
    }
}

static void func_80282714(UnkStruct_80288040 *arg0) {
    if (((u8) (arg0->unk7A & 0xF0)) == 0x10) {
        func_80270BA4(arg0->unk0);
        func_80282430(arg0, 0xF0, 0);
    }
}

static void func_80282590() {
}

static void func_80282598(UnkStruct_800BB340 *arg0, s32 arg1) {
    UnkStruct_800BA900 *obj;
    UnkStruct_80288040 *act;

    func_80282590();
    func_80282588();
    obj = arg0->unk10;
    obj->unk0 = 2;
    obj->unk14.unk8C = 0;
    act = &obj->unk14;
    if (((u8) (obj->unk14.unk7A & 0xF)) == 1) {
        if (act->unk79 != -1) {
            func_8028A4E0(act->unk79);
            act->unk79 = -1;
        }
    }
    act->unk0->unkC = 0;
    act->unk78 = 0;
    if (act->unk48 != 0) {
        func_8028805C(act);
    }
    act->unk40 = 0;
    func_802313DC(act->unk0, func_80282524(act) | 0x40000);
    func_80282454(act);
    arg0->unkC = 0;
    arg0->unk10 = NULL;
    if (arg0->unk4 == 2) {
        if (obj->unk0 != 0) {
            func_8022FC90(obj->unk14.unk0);
            func_80282340(obj);
        }
        if (arg1 == 2) {
            func_802822E0(arg0);
        } else {
            func_802822BC(arg0);
            D_800BB480 -= 1;
            func_80239430();
        }
    } else {
        switch (arg1) {
        case 0:
        case 2:
            obj->unk4 = 0;
            break;
        case 1:
            obj->unk4 = 0x4B0;
            act->unk0->unk40->unk10 = obj->unk8.x;
            act->unk0->unk40->unk14 = obj->unk8.y;
            act->unk0->unk40->unk18 = obj->unk8.z;
            break;
        }
    }
}

static void func_80282588() {
}

static s32 func_80282524(UnkStruct_80288040 *arg1) {
    s32 flags;
    s16 kind;

    flags = func_802824B4(arg1) | 0x03000014;
    kind = D_800BA8E8[arg1->unk84].unk2;
    if ((kind == 0xE9) || (kind == 0xEE) || (kind == 0xD2)) {
        flags |= 0x80000;
    }
    return flags;
}

static s32 func_802824B4(UnkStruct_80288040 *arg0) {
    s32 ret = 0;

    switch (arg0->unk44) {
    case 0:
        ret = 0x200;
        break;
    case 1:
        ret = 0x400;
        break;
    case 2:
        ret = 0x800;
        break;
    case 3:
        ret = 0x1000;
        break;
    case 4:
        ret = 0x100;
        break;
    case 5:
        ret = 0x80;
        break;
    case 6:
        ret = 0x20;
        break;
    case 7:
        ret = 0x40;
        break;
    case 8:
        break;
    }
    return ret;
}

static void func_80282454(UnkStruct_80288040 *arg0) {
    func_80229E38(arg0->unk0->unk40, 0, 0);
    arg0->unk0->unk40->unk48->unk4->unk4 = 0.0f;
    func_80282430(arg0, 0xF, 0);
    if (0) {
        D_800BC520 = (s32) func_80282454;
    }
}

void func_80282430(arg0, arg1, arg2)
    UnkStruct_80288040 *arg0;
    u8 arg1;
    u8 arg2;
{
    func_80282428();
    arg0->unk7A &= ~arg1;
    arg0->unk7A |= arg2;
    if (0) {
        func_80282340(NULL);
        func_802822E0(NULL);
        func_802822BC(NULL);
    }
}

static void func_80282428() {
}

static void func_80282338() {
}

static void func_80282340(UnkStruct_800BA900 *arg0) {
    func_80282338();
    arg0->unk14.unk1D = 3;
    arg0->unk14.unk1E = 0xA;
    arg0->unk14.unk0 = NULL;
    arg0->unk14.unk4 = 0;
    arg0->unk14.unk8 = 0;
    arg0->unk14.unkC = 0;
    arg0->unk14.unk10 = 0;
    arg0->unk14.unk14 = 0;
    arg0->unk14.unk18 = 0;
    arg0->unk14.unk1C = 0;
    arg0->unk14.unk1F = 0x14;
    arg0->unk14.unk20 = 0;
    arg0->unk14.unk24 = 2;
    arg0->unk14.unk28 = 0;
    arg0->unk14.unk30 = 0;
    arg0->unk14.unk3C = 0;
    arg0->unk14.unk3D = 0;
    arg0->unk14.unk3E = 0;
    arg0->unk14.unk40 = 0;
    arg0->unk14.unk44 = 4;
    arg0->unk14.unk48 = 0;
    arg0->unk14.unk4C = 0;
    arg0->unk14.unk50.b[0] = 0;
    arg0->unk14.unk68 = 0;
    arg0->unk14.unk6C = 0;
    arg0->unk14.unk6D = 1;
    arg0->unk14.unk6E = 0;
    arg0->unk14.unk78 = 0;
    arg0->unk14.unk7A = 0;
    arg0->unk14.unk79 = -1;
    arg0->unk14.unk7C = 0;
    arg0->unk14.unk7E = 0;
    arg0->unk14.unk80 = -1;
    arg0->unk14.unk84 = -1;
    arg0->unk14.unk88 = 0;
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk14.unk8C = 0;
    arg0->unk14.unk34 = 0.0f;
    arg0->unk14.unk38 = 0.0f;
    arg0->unk8.x = 0.0f;
    arg0->unk8.y = 0.0f;
    arg0->unk8.z = 0.0f;
    arg0->unk14.unk70 = 5.0f;
    arg0->unk14.unk74 = 5.0f;
    arg0->unk14.unk2C = 0;
}

static void func_802822E0(UnkStruct_800BB340 *arg0) {
    s32 temp_v0;

    func_802822D8();
    temp_v0 = arg0->unk4;
    if (temp_v0 != 0) {
        if (temp_v0 == 2) {
            D_800BB480 -= 1;
        }
        func_80238EA8(arg0->unk8);
        func_802822BC(arg0);
    }
}

static void func_802822D8() {
}

static void func_802822BC(UnkStruct_800BB340 *arg0) {
    arg0->unk0 = -1;
    arg0->unk4 = 0;
    arg0->unk8 = -1;
    arg0->unkC = 0;
    arg0->unk10 = NULL;
}

void func_802822B0(s32 arg0) {
    D_800BB480 = arg0;
}

