/*
 * NON_MATCHING: main_code's 93850, complete: the list of bonus items at
 * D_800BB4A8 (func_80279050 to func_8027A144, the list's thread). The
 * C is written last function first, as -O3 emits it. func_802797BC
 * differs in the order of two sra in the default case. Its fakes: the
 * dead `if (sound) {}` that ends cases 2 and 3 lets as1 fill the delay
 * slot after the func_80243DDC compare with li a1,32 as the original
 * does (without it, a nop and one word more), and the dead
 * `if (&D_800BA8A0[i] == 0) {}` after their D_800AEDF0 store makes the
 * D_800BA8A0 address live across that store, so the D_800AEDF0 address
 * (one live range over cases 2, 3 and 4) takes v1 as in the original;
 * it also keeps the D_800BA8A0 load after the store (without a dead read
 * there, ugen marks the two tables .noalias and as1 moves the load up).
 * func_8027036C is
 * declared s32 here, as an implicit declaration would make it (it
 * returns nothing): with void, func_80279DC8's arg0->unk14 reload took
 * v0 where the original has v1. Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING
 * drafts").
 * flags: -O3
 * differing words: us 2, eu 2, jp 2
 */
#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} UnkStruct_80279050_10;

typedef struct {
    /* 0x00 */ u8 unk0[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x24];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ UnkStruct_80279050_10 *unk40;
    /* 0x44 */ u8 unk44[0x14];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} UnkStruct_80279050_14;

/* A node of the list at D_800BB4A8; the last node is a sentinel */
typedef struct UnkStruct_800BB4A8 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ struct UnkStruct_800BB4A8 *unk8;
    /* 0x0C */ struct UnkStruct_800BB4A8 *unkC;
    /* 0x10 */ UnkStruct_80279050_10 *unk10;
    /* 0x14 */ UnkStruct_80279050_14 *unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 unk4A[6];
    /* 0x50 */ f32 unk50;
    /* 0x54 */ s32 unk54;
} UnkStruct_800BB4A8;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_802AFED0; /* size 0x1C */

typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 unk24[0xA4];
} UnkStruct_800AEDF0; /* size 0xC8 */

typedef struct {
    /* 0x00 */ u8 unk0[0x6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 unk8[0x2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 unkC[0x2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x4];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
} UnkStruct_8023A840;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStruct_80279050_14 *unk4;
    /* 0x08 */ UnkStruct_80279050_14 *unk8;
    /* 0x0C */ UnkStruct_80279050_14 *unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} UnkStruct_8027A264; /* size 0x3C */

void func_8022FC90(UnkStruct_80279050_14 *);
void func_802313DC(UnkStruct_80279050_14 *, s32);
void func_80231408(UnkStruct_80279050_14 *, s32);
UnkStruct_80279050_14 *func_802308B8(UnkStruct_80279050_14 *, s32);
s32 func_80234248(s32);
void func_80239094(void);
UnkStruct_8023A840 *func_8023A840(void);
void func_8024694C(s32, s32, s32);
void func_80246C3C(s32, s32, s32);
void func_80246D74(s32);
void func_80246F00(s32, s32);
void func_80248864(s32);
void func_802488C0(s32);
void func_802502BC(s32);
void func_8026C660(s32);
f32 func_8026E8B8(void);
void func_80270354(s32 *, s32);
s32 func_8027036C(s32 *, s32);
s32 func_802712A8(s32 *, s32);
s32 func_80272024(s16);
void func_802727D8(s32);
void func_802733C8(UnkStruct_80279050_14 *);
void func_80277D60(s32, s32);
s32 func_8027B480(s32 arg0);
void *malloc(s32);
void free(void *);
s16 func_8026FFA0(s16);
void func_80270080(UnkStruct_8027A264 *);
void func_80277DA8(s16, s32);
UnkStruct_80279050_14 *func_802443F4(s32);
UnkStruct_800BB4A8 *func_8027AA74(s16, f32, f32, f32, s32, s32, s32);
f32 func_80234434(f32);
void func_8027A950(void);
void func_8028A81C(s32, f32, f32, f32, s32);
void func_8029217C(UnkStruct_80279050_14 *, s32, f32, void (*)());

void func_802790E0(UnkStruct_800BB4A8 *arg0);
void func_802797BC(UnkStruct_80279050_14 *arg0, UnkStruct_800BB4A8 *arg1);
void func_80279CA8(void);
void func_80279D40(UnkStruct_800BB4A8 *arg0);
s32 func_80279DC8(UnkStruct_800BB4A8 *arg0, f32 arg1);
void func_80279F30(void);
UnkStruct_800BB4A8 *func_8027A1A0(UnkStruct_80279050_14 *arg0);

extern UnkStruct_800BB4A8 *D_800BB4A8;
extern UnkStruct_802AFED0 D_802AFED0[];
extern UnkStruct_800AEDF0 D_800AEDF0[];
extern UnkStruct_800BB4A8 D_800BB4A0[]; /* [0] the list's head, [1] its sentinel, [2..47] the pool */
extern s16 D_802AFF60[];

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
} UnkStruct_800BA8A0; /* size 0xE */

void func_80270B20(s32);
void func_80270BA4(UnkStruct_80279050_14 *);
void func_80238EA8(s32);
void func_8027404C(f32, f32, f32, f32 *, f32 *, f32 *);
void func_80297D30(s32, void *);
void func_8027AFB8(s16 arg0);

extern UnkStruct_800BA8A0 D_800BA8A0[];
extern u8 D_802A1500[];
extern u8 *D_802AFE80;
extern u8 *D_802AFE84;
extern s16 D_802AFE88[][3];
extern s16 D_802AFEC4;
extern s32 D_802AFEC8;
extern s32 D_802AFECC;

void func_80279628(s16 arg0, s16 arg1);
s32 func_802311E8(UnkStruct_80279050_14 *);
UnkStruct_80279050_14 *func_80231274(s32, s32, s32, void *);
s32 func_80238A10(void (*)(void), s32, void *, s32, s32);
s32 func_80243DDC(void);
s32 func_80243EF0(s32);
void func_8024512C(s32, s32);
void func_8026C51C(s32, f32, f32, f32);
void func_80277AF8(s16, s32);
void func_80278E84(s16, s16);
s32 func_8028A36C(s32);
void func_8028A3D0(s32);
void func_8027A144(void);
void func_8027A264(UnkStruct_800BB4A8 *arg0, s16 arg1);
s16 func_8027A4E8(s16 arg0);
s16 func_8027A574(s16 arg0);
void func_8027A380(s16 arg0);
void func_8027A478(UnkStruct_800BB4A8 *arg0);
UnkStruct_800BB4A8 *func_8027A4A0(void);
s16 func_8027AF70(void);
s32 func_8027911C(s16 arg0);
void func_802794FC(s16 arg0);
void func_80279560(void);
void func_80279780(s16 arg0, s32 arg1);
void func_8027404C(f32, f32, f32, f32 *, f32 *, f32 *);
void func_8027A640(void);
extern u8 D_800BD818[];
extern s32 D_802AC5D0;

#define ABSF(x) ((x) < 0.0f ? -(x) : (x))

void func_80279050(void);
s32 func_802791C4(s16 arg0);
void func_80279F10(UnkStruct_800BB4A8 *arg0);
s32 func_8027A1F4(UnkStruct_80279050_14 *arg0, s32 arg1);
UnkStruct_800BB4A8 *func_8027AA74(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_8027B094(s16 arg0);
void func_8027B0BC(s16 arg0);
void func_8027B39C(s16 arg0, s16 arg1);
void func_8027B440(UnkStruct_80279050_14 *arg0);
void func_8027B4B0(s16 arg0);
s32 func_8027B5A8(UnkStruct_80279050_14 *arg0);
void func_8027B66C(s16 arg0, s16 arg1);
void func_8027B6A4(UnkStruct_800BB4A8 *arg0, UnkStruct_800BB4A8 *arg1);
void func_8027B6D4(UnkStruct_800BB4A8 *arg0, UnkStruct_800BB4A8 *arg1);
void func_8027B70C(void);
s32 func_8027B7C4(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 func_8027B828(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
s32 func_8027B8D4(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
s32 func_8027BA80(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
s32 func_8027BAE8(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_8027BB48(void);
void func_8027BB9C(void);
void func_8027BBC4(void);
void func_8027BC74(void);
s32 func_8027BCD8(void);
void func_8027BCE8(void);

void func_8027A144(void) {
    while (TRUE) {
        func_80279F30();
        func_80279CA8();
        func_80279050();
        func_80239094();
    }
}

void func_80279F30(void) {
    UnkStruct_800BB4A8 *node = D_800BB4A8;
    s32 *flags;
    s16 i;

    while (node->unk8 != NULL) {
        flags = &node->unk54;
        if (func_802712A8(flags, 8)) {
            node->unk48--;
        }
        if (node->unk48 < 60 && !func_802712A8(flags, 0x10)) {
            func_80270354(flags, 0x10);
            func_80231408(node->unk14, 0x40000);
        }
        if (node->unk48 > 60 && func_802712A8(flags, 0x10)) {
            func_8027036C(flags, 0x10);
            func_802313DC(node->unk14, 0x40000);
        }
        if (node->unk48 == 0) {
            func_802790E0(node);
        } else {
            node->unk24 = node->unk10->unk10;
            node->unk28 = node->unk10->unk14;
            node->unk2C = node->unk10->unk18;
            if (func_802712A8(flags, 2) || func_802712A8(flags, 1)) {
                if (func_802712A8(flags, 2)) {
                    func_802733C8(node->unk14);
                } else {
                    func_802727D8(node->unk18);
                    node->unk24 = node->unk10->unk10;
                    node->unk28 = node->unk10->unk14;
                    node->unk2C = node->unk10->unk18;
                }
            } else if (!func_80279DC8(node, 1.0f)) {
                for (i = 0; i < 7; i += 2) {
                    node->unk30 = i;
                    if (func_80279DC8(node, 1.0f)) {
                        break;
                    }
                }
            }
            func_80279D40(node);
        }
        node = node->unk8;
    }
}

void func_80279F10(UnkStruct_800BB4A8 *arg0) {
    func_802790E0(arg0);
}

s32 func_80279DC8(UnkStruct_800BB4A8 *arg0, f32 arg1) {
    UnkStruct_80279050_10 *pos;
    s32 ret;

    if (arg0->unk50 != 0.0f || func_802712A8(&arg0->unk54, 2)) {
        return 0;
    }
    arg0->unk14->unk68 = arg0->unk3C;
    arg0->unk14->unk70 = 1.6333334f;
    ret = func_80272024(arg0->unk30);
    func_8029217C(arg0->unk14, ret, arg1, (void (*)())func_8027B480);
    if (arg0->unk14->unk6C == 0.0f && arg0->unk14->unk68 == 0.0f) {
        func_8027036C(&arg0->unk54, 1);
        arg0->unk3C = 0.0f;
    }
    pos = arg0->unk10;
    if (arg0->unk14->unk58 == pos->unk10 && arg0->unk14->unk60 == pos->unk18) {
        ret = 0;
    } else {
        ret = 1;
    }
    arg0->unk24 = pos->unk10;
    arg0->unk28 = pos->unk14;
    arg0->unk2C = pos->unk18;
    return ret;
}

void func_80279D40(UnkStruct_800BB4A8 *arg0) {
    s32 below;

    if (arg0->unk28 <= func_8026E8B8()) {
        below = TRUE;
    } else {
        below = FALSE;
    }
    if (below) {
        func_8028A81C(12, arg0->unk24, arg0->unk28 + 100.0f, arg0->unk2C, 0);
        func_802313DC(arg0->unk14, 0x0103FFFF);
        func_80239094();
        func_802790E0(arg0);
    }
}

void func_80279CA8(void) {
    UnkStruct_800BB4A8 *node;
    UnkStruct_80279050_14 *obj;

    if (D_800BB4A8 != NULL) {
        node = D_800BB4A8;
        while (node->unk8 != NULL) {
            node->unk1E = 1;
            node->unk1C = 0;
            if (func_802712A8(&node->unk54, 2) == 0) {
                obj = func_802308B8(node->unk14, 1);
                if (obj != NULL) {
                    func_802797BC(obj, node);
                    func_802790E0(node);
                }
            }
            node = node->unk8;
        }
    }
}

void func_802797BC(UnkStruct_80279050_14 *arg0, UnkStruct_800BB4A8 *arg1) {
    s16 i;
    s16 item;
    s16 sound;
    s32 special;
    UnkStruct_8023A840 *st;
    s16 x;
    s16 y;

    for (i = 0; i < 5; i++) {
        if (func_802443F4(i) == arg0) {
            break;
        }
    }
    if (i < 5) {
    func_80270BA4(arg1->unk14);
    if (func_802712A8(&arg1->unk54, 1)) {
        func_8027036C(&arg1->unk54, 1);
        func_802313DC(arg1->unk14, 0x20000);
        func_80270B20(arg1->unk18);
    }
    if (func_80243EF0(i) != 1) {
    switch (arg1->unk20) {
        case 0:
            func_80278E84(i, 1);
            D_800BA8A0[i].unk0++;
            sound = 4;
            break;
        case 1:
            func_80277AF8(i, 1);
            D_800BA8A0[i].unk2++;
            sound = 4;
            break;
        case 2:
            D_800AEDF0[i].unk18 |= 1;
            if (&D_800BA8A0[i] == 0) {} /* fake: see the header */
            sound = 5;
            D_800BA8A0[i].unk4++;
            if (sound) { /* fake: see the header */
            }
            break;
        case 3:
            D_800AEDF0[i].unk18 |= 2;
            if (&D_800BA8A0[i] == 0) {} /* fake: see the header */
            sound = 5;
            D_800BA8A0[i].unk6++;
            if (sound) { /* fake: see the header */
            }
            break;
        case 4:
            if ((D_802AC5D0 & 8) && i != 0) {
                D_800AEDF0[i].unk14++;
            } else {
                func_8024512C(i, 2);
            }
            D_800BA8A0[i].unk8++;
            sound = 5;
            break;
        case 5:
            func_80279780(i, 0);
            D_800BA8A0[i].unkA++;
            sound = 9;
            break;
        case 6:
            func_80279560();
            D_800BA8A0[i].unkC++;
            sound = 0x2B;
            break;
        case 7:
            func_802794FC(1);
            sound = 6;
            break;
        case 8:
            func_802794FC(5);
            sound = 7;
            break;
        default:
            item = func_802791C4(arg1->unk20);
            if (item == -1) {
                return;
            }
            func_8028A3D0(item);
            if (func_8027911C(arg1->unk20) == 9) {
                sound = 8;
            } else {
                sound = 5;
            }
            break;
    }
    if (func_80243DDC() == i && !func_802712A8(&arg1->unk54, 0x20)) {
        D_802AFECC = arg1->unk20 + 1;
    }
    st = func_8023A840();
    x = st->unk6;
    y = st->unkA;
    special = 0;
    if (x == 0 && y == 3) {
        special = 1;
    }
    if (x == 1 && y == 3) {
        special = 1;
    }
    if (x == 2 && y == 3) {
        special = 1;
    }
    if (x == 3 && y == 3) {
        special = 1;
    }
    if (x == 4 && y == 1) {
        special = 1;
    }
    if (func_802712A8(&arg1->unk54, 0x80) || special == 1) {
        func_8026C660(0xCF);
    } else {
        func_8026C660(sound);
    }
    func_8028A81C(2, arg1->unk24, arg1->unk28 + 70.0f, arg1->unk2C, 0);
    }
    }
}

void func_80279780(s16 arg0, s32 arg1) {
    func_80279628(arg0, func_80234248(6));
}

void func_80279628(s16 arg0, s16 arg1) {
    D_802AFED0[arg0].unk4 = arg0;
    D_802AFED0[arg0].unk8 = arg1;
    D_802AFED0[arg0].unkC = 1200;
    D_802AFED0[arg0].unk10 = D_800AEDF0[arg0].unk18;
    D_802AFED0[arg0].unk14 = D_800AEDF0[arg0].unk1C;
    D_802AFED0[arg0].unk18 = D_800AEDF0[arg0].unk20;
    func_80246D74(arg0);
    switch (arg1) {
        case 0:
            func_8024694C(arg0, 2, 1);
            break;
        case 1:
            func_8024694C(arg0, 1, 1);
            break;
        case 2:
            func_802488C0(arg0);
            break;
        case 3:
            func_80277D60(arg0, 0x400);
            func_80246C3C(arg0, 3, 1);
            break;
        case 4:
            func_80248864(arg0);
            break;
        case 5:
            func_802502BC(arg0);
            break;
        case 6:
            func_80277D60(arg0, 4);
            func_80246C3C(arg0, 3, 1);
            break;
        default:
            break;
    }
}

void func_80279560(void) {
    switch (func_80234248(6)) {
        case 0:
            func_80246F00(2, 1);
            break;
        case 1:
            func_80246F00(4, 1);
            break;
        case 2:
            func_80246F00(8, 1);
            break;
        case 3:
            func_80246F00(0x10, 1);
            break;
        case 4:
            func_80246F00(0x20, 1);
            break;
        case 5:
            func_80246F00(0x40, 1);
            break;
        case 6:
            func_80246F00(0x80, 1);
            break;
    }
}

void func_802794FC(s16 arg0) {
    UnkStruct_8023A840 *p = func_8023A840();

    p->unk1C += arg0;
    if (p->unk1C >= 50) {
        func_8026C660(0x24);
        p->unk18++;
        p->unk1C -= 50;
    }
}

s32 func_802791C4(s16 arg0) {
    s16 ret;
    s16 n;
    s16 q;
    s16 m;

    switch (func_8027911C(arg0)) {
        case 9:
            if (arg0 >= 45) {
                n = arg0 - 45;
                q = n / 2;
                m = n - q * 2;
                if (m == 1) {
                    m++;
                }
                ret = q * 20 + m * 5 + 3;
            } else {
                n = arg0 - 9;
                ret = arg0 - 9;
                q = n / 6;
                m = (n - q * 6) / 3;
                if (m == 1) {
                    m++;
                }
                ret = ret % 6 % 3;
                ret = q * 20 + m * 5 + ret;
            }
            ret += 0x2C;
            break;
        case 0x39:
            ret = arg0 - 0x39;
            if (ret >= 6) {
                ret = 0;
            }
            ret += 2;
            break;
        case 0x3F:
            ret = arg0 - 0x3F;
            if (ret >= 6) {
                ret = 0;
            }
            ret = (u16)ret;
            ret += 0xD;
            break;
        case 0x45:
            ret = arg0 - 0x45;
            if (ret >= 6) {
                ret = 0;
            }
            ret = (u16)ret;
            ret += 0x18;
            break;
        case 0x4B:
            ret = arg0 - 0x4B;
            if (ret >= 6) {
                ret = 0;
            }
            ret = (u16)ret;
            ret += 0x23;
            break;
        default:
            ret = -1;
    }
    return ret;
}

s32 func_8027911C(s16 arg0) {
    if (arg0 >= 9 && arg0 < 0x39) {
        return 9;
    }
    if (arg0 >= 0x39 && arg0 < 0x3F) {
        return 0x39;
    }
    if (arg0 >= 0x3F && arg0 < 0x45) {
        return 0x3F;
    }
    if (arg0 >= 0x45 && arg0 < 0x4B) {
        return 0x45;
    }
    if (arg0 >= 0x4B && arg0 < 0x51) {
        return 0x4B;
    }
    return 0;
}

void func_802790E0(UnkStruct_800BB4A8 *arg0) {
    UnkStruct_800BB4A8 *prev = arg0->unkC;
    UnkStruct_800BB4A8 *next = arg0->unk8;

    prev->unk8 = next;
    next->unkC = prev;
    arg0->unk2 = 1;
    func_8022FC90(arg0->unk14);
}

void func_80279050(void) {
    UnkStruct_800BB4A8 *node;

    if (D_800BB4A8 != NULL) {
        node = D_800BB4A8;
        while (node->unk8 != NULL) {
            if (func_802712A8(&node->unk54, 2) == 0) {
                node->unk10->unk10 = node->unk24;
                node->unk10->unk14 = node->unk28;
                node->unk10->unk18 = node->unk2C;
            }
            node = node->unk8;
        }
    }
}
