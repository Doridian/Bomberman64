/*
 * NON_MATCHING: main_code's 926A0, complete (14 functions,
 * func_80277EA0..func_80278FD8). Split from 8E730 by IDO's emission
 * order (text_objects.txt). A first draft from m2c; every function
 * global, emitted in the original's order. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 180, eu 180, jp 180
 *
 * 12 of 14 match. Pass 2 retyped the records: D_8008E658 is Rec926[48]
 * (0x48 bytes), D_800AEDF0 Player926[] (0xC8); with plain struct C most
 * functions matched outright. Left: func_80277FC4 (frame slots, 0.0f
 * colouring) and func_80277EA0 (switch return delay slot).
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

typedef struct {
    /* 0x00 */ s32 i[3];
    /* 0x0C */ f32 f[3];
} Unk8026DCAC;

typedef struct Node87 {
    /* 0x00 */ struct Node87 *next;
    /* 0x04 */ s32 unk4;
} Node87;

extern Node87 D_802AFDE0;
extern Node87 D_802AFE58;

void free(void *);
void func_8022638C(u32, void *);
void func_802297B8(s32, s32, s32, s32);
s32 func_8022984C(void *, s32);
s32 func_8022DF68(s32, s32);
s32 func_8022E884(s32, s32);
s32 func_8022F4AC(s32, s32, s32);
void func_8022FC90(void *);
void func_8022FF58(f32 *, f32 *, f32 *);
void * func_802308B8(void *, s32);
void func_80230914(void *);
s32 func_802311E8(void *);
void * func_80231274(s32, s32, s32, void *);
void func_802313DC(void *, s32);
void func_80231408(void *, s32);
void func_80231434(void *);
void func_80232A34(s32);
s32 func_80232AA8(s32);
s32 func_80232AC8(s32, s32);
s32 func_80232D18(void *, s32);
void func_80232DB4(void *);
int func_8023369C(f32, f32, f32);
int func_802336E4(f32);
s32 func_80234248(s32);
f32 func_80234408(f32);
f32 func_80234434(f32);
s32 func_80238A10(void *, s32, s32, s32, s32);
void func_80238EA8(s32);
void func_80239094(void);
s32 *func_802391F0(void);
s32 *func_8023A840(void);
void func_802438BC(s32 *);
void func_802441F4(void *, s32, s32 *, f32 *);
s32 func_802442A8(s32);
void * func_802443F4(s32);
void func_80244C30(s32, s32);
void func_80244E04(void *);
s32 func_80244F34(void *, s32);
s32 func_80244FF8(void *);
void func_802511EC(s32, s32, s32, s32);
s32 func_8026C51C(s32, f32, f32, f32);
s32 func_8026C660(s32);
void * func_8027A1A0(void *);
s32 func_8027A1F4(void *, s32);
void func_8027B440(void *);
s32 func_8027B5A8(void *);
s16 func_8027DF40(s32);
s16 func_8027DF9C(void);
s32 func_8027E8EC(s16, s16, s16, s16);
void func_8027F820(void);
void func_8027F858(s32, s32);
s32 func_80286CA8(s32, f32, f32, f32);
s32 func_802870A8(void);
s32 func_80287440(void);
s32 func_802875B0(void);
s32 func_8028A4E0(s32);
s32 func_8028A81C(s32, f32, f32, f32, s32);
s32 func_802909FC(s32);
void func_80291944(void *, s32, f32);
void func_80297D38(const char *, ...);
f32 func_8029CB40(f32);
void * malloc(s32);

extern s32 D_8008E658;
extern u8 D_8008F438[];
extern s16 *D_8008F44C;
extern u8 D_8008F4C0[];
extern u8 D_800AEDF0[];
extern s32 D_800AEE08;
extern u8 D_800AEE0A[];
extern s32 D_800AEE0C;
extern u8 D_800AEE0E[];
extern s32 D_800AEE10;
extern u8 D_802A1450[];
extern s16 D_802A14B4;
extern u8 D_802A14B8[];
extern s16 D_802A14F0;
extern void *D_802A55F4;
extern s32 D_802AC5D0;
extern s32 D_802AC89C;
extern s32 D_802AC8A0;
extern s32 D_802AFC50;
extern s32 D_802AFC54;
extern s32 D_802AFC58;
extern f32 D_802AFC5C;
extern f32 D_802AFC60;
extern f32 D_802AFC64;
extern f32 D_802AFC68;
extern void *D_802AFC6C;
extern s32 D_802AFC70;
extern s32 D_802AFC74;
extern u8 D_802AFC78[];
extern u8 D_802AFCE8[];
extern u8 D_802AFCF4[];
extern s16 D_802AFCF8;
extern void *D_802AFDD8;
extern Node87 D_802AFE1C;
extern u8 D_802AFE60[];
extern s16 D_802AFE70;


typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s16 pad34;
    /* 0x36 */ s16 unk36;
} Sub926;

typedef struct {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ Sub926 *unk40;
} Obj926;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ s32 *unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ Obj926 *unk14;
    /* 0x18 */ Sub926 *unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[2];
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
} Rec926; /* size 0x48 */

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 pad24[0xC8 - 0x24];
} Player926; /* size 0xC8 */

typedef struct {
    s32 unk0;
    s32 unk4;
} Info926;

s32 func_8026DC74(s32 arg0);
void func_8027404C(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
s32 func_80277EA0(s16 arg0);
s16 func_80277F0C(Rec926 *arg0);
s16 func_80277F74(void);
Rec926 *func_80277FC4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s16 arg8, s32 *arg9);
void func_80278740(Rec926 *arg0);
void func_80278788(Rec926 *arg0);
void func_802787E4(Rec926 *arg0);
void func_80278D54(Rec926 *arg0);
void func_80278DBC(void);
void func_80278E28(s16 arg0, s16 arg1);
void func_80278E84(s16 arg0, s16 arg1);
void func_80278F00(s16 arg0);
void func_80278F68(void);
void func_80278FD8(u32 arg0, u8 **arg1);

#define RECS ((Rec926 *) &D_8008E658)
#define PLAYERS ((Player926 *) D_800AEDF0)

void func_80278FD8(u32 arg0, u8 **arg1) {
    struct UnkStruct_80225CC0 *file;
    Info926 info;

    func_8022638C(arg0, &info);
    *arg1 = malloc(info.unk4);
    if (*arg1 != NULL) {
        file = func_80226604(arg0, 1);
        func_8022616C(*arg1, 1, info.unk4, file);
        func_80226368(file);
    }
}

void func_80278F68() {
    s16 i;
    Rec926 *p;

    D_802AFE70 = 0;
    for (i = 0; i < 5; i++) {
        PLAYERS[i].unk20 = 2;
    }
    for (i = 0, p = RECS; i < 48; i++, p++) {
        p->unk18 = NULL;
    }
}

void func_80278F00(s16 arg0) {
    switch (arg0) {
    case 1:
        D_802A14F0 = 1;
        return;
    case 0:
        D_802A14F0 = 0;
        return;
    case 2:
        D_802A14F0 ^= 1;
        return;
    }
}

void func_80278E84(s16 arg0, s16 arg1) {
    s32 max;
    Player926 *p;

    p = &PLAYERS[arg0];
    p->unk20 += arg1;
    if (p->unk18 & 5) {
        max = 7;
    } else {
        max = 4;
    }
    if (max < p->unk20) {
        p->unk20 = max;
    }
}

void func_80278E28(s16 arg0, s16 arg1) {
    Player926 *p;

    p = &PLAYERS[arg0];
    p->unk20 -= arg1;
    if (p->unk20 < 2) {
        p->unk20 = 2;
    }
}

void func_80278DBC() {
    s16 i;
    Rec926 *p;

    for (i = 0, p = RECS; i < 48; i++, p++) {
        if (p->unk18 != NULL) {
            func_80278740(p);
            p->unk36 = 0;
        }
    }
    D_802AFE70 = 0;
}

void func_80278D54(Rec926 *arg0) {
    func_80232DB4(arg0->unk14);
    switch (arg0->unkC) {
    case 1:
        func_802787E4(arg0);
        return;
    case 2:
        func_80278788(arg0);
        return;
    }
}

void func_802787E4(Rec926 *arg0) {
    f32 s;
    f32 scale;
    f32 rot;
    f32 w;
    Sub926 *sub;

    if (arg0->unk44 <= 0) {
        arg0->unk38 += arg0->unk3A;
        switch (arg0->unkE) {
        case 0:
        case 1:
            s = func_80234434(arg0->unk38);
            arg0->unk18->unk36 = func_80234408(arg0->unk38) * 191.0f + 64.0f;
            arg0->unk40 += 5.0f;
            arg0->unk18->unk20 = arg0->unk40;
            scale = arg0->unk3C * s;
            arg0->unk28 = scale;
            arg0->unk2C = scale;
            arg0->unk30 = scale;
            break;
        case 2:
        case 3:
            s = func_80234434(arg0->unk38);
            arg0->unk18->unk36 = func_80234408(arg0->unk38) * 255.0f;
            arg0->unk40 += 5.0f;
            arg0->unk18->unk20 = arg0->unk40;
            scale = arg0->unk3C * s;
            arg0->unk28 = scale;
            arg0->unk2C = scale;
            arg0->unk30 = scale;
            break;
        case 4:
            s = func_80234434(arg0->unk38);
            arg0->unk18->unk36 = func_80234408(arg0->unk38) * 255.0f;
            arg0->unk40 += 5.0f;
            arg0->unk18->unk20 = arg0->unk40;
            scale = arg0->unk3C * s * 0.7f;
            arg0->unk28 = scale;
            arg0->unk2C = scale;
            arg0->unk30 = scale;
            break;
        case 5:
            s = func_80234434(arg0->unk38);
            arg0->unk18->unk36 = func_80234408(arg0->unk38) * 255.0f;
            scale = arg0->unk3C * s;
            arg0->unk28 = scale;
            arg0->unk2C = scale;
            arg0->unk30 = scale;
            break;
        case 6:
            s = func_80234434(arg0->unk38);
            arg0->unk18->unk36 = func_80234408(arg0->unk38) * 255.0f;
            arg0->unk40 += 5.0f;
            arg0->unk18->unk20 = arg0->unk40;
            scale = arg0->unk3C * s;
            arg0->unk28 = scale;
            arg0->unk2C = scale;
            arg0->unk30 = scale;
            break;
        case 7:
            s = func_80234434(arg0->unk38);
            arg0->unk18->unk36 = func_80234408(arg0->unk38) * 255.0f;
            scale = arg0->unk3C * s * 1.5f;
            arg0->unk28 = scale;
            arg0->unk2C = scale;
            arg0->unk30 = scale;
            break;
        case 8:
            s = func_80234434(arg0->unk38);
            arg0->unk18->unk36 = func_80234408(arg0->unk38) * 255.0f;
            arg0->unk40 += 5.0f;
            arg0->unk18->unk20 = arg0->unk40;
            scale = arg0->unk3C * s * 0.65f;
            arg0->unk28 = scale;
            arg0->unk2C = scale;
            arg0->unk30 = scale;
            break;
        }
        arg0->unk18->unk28 = arg0->unk28;
        arg0->unk18->unk2C = arg0->unk2C;
        arg0->unk18->unk30 = arg0->unk30;
        sub = arg0->unk18;
        rot = sub->unk20;
        if (rot >= 360.0f) {
            sub->unk20 = rot - 360.0f;
        } else {
            if (rot < 0.0f) {
                w = rot + 360.0f;
            } else {
                w = rot;
            }
            sub->unk20 = w;
        }
        if (arg0->unk38 >= 71) {
            func_802313DC(arg0->unk14, 0x40);
        }
        if (arg0->unk38 >= 91) {
            func_80278740(arg0);
        }
    } else {
        arg0->unk44--;
    }
}

void func_80278788(Rec926 *arg0) {
    if (arg0->unk44 <= 0) {
        arg0->unk3A--;
        if (arg0->unk3A == 0) {
            arg0->unk36 = 0;
            func_80278740(arg0);
        }
    } else {
        arg0->unk44--;
    }
}

void func_80278740(Rec926 *arg0) {
    func_8022FC90(arg0->unk14);
    arg0->unk18 = NULL;
    *arg0->unk8 = 0;
    D_802AFE70--;
}

Rec926 *func_80277FC4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s16 arg8, s32 *arg9) {
    s16 idx;
    s16 alpha;
    s32 flags;
    s32 type;
    f32 f;
    Obj926 *obj;
    Rec926 *r;

    idx = func_80277F74();
    if (idx == -1) {
        return NULL;
    }
    r = &RECS[idx];
    r->unk0 = idx;
    r->unkC = 1;
    r->unkE = arg1;
    r->unk10 = arg2;
    r->unk8 = arg9;
    func_8027404C(arg5, arg6, arg7, &r->unk1C, &r->unk20, &r->unk24);
    if (arg6 < 0.0f) {
        r->unk20 = arg6 * 100.0f;
    } else {
        for (f = arg6; f >= 1.0f; f -= 1.0) {
        }
        f *= func_8026DC74(arg6) * 100.0f;
        r->unk20 += f;
    }
    r->unk38 = 0;
    r->unk36 = arg8;
    r->unk46 = arg0;
    switch (arg1) {
    case 0:
    case 1:
    case 2:
        r->unk3A = 90 / func_80277EA0(arg8);
        flags = 0x01080040;
        if (r->unk10 & 0x100) {
            flags = 0x01082040;
        }
        if (r->unk10 & 5) {
            flags |= 0x4000;
        }
        alpha = func_80277F0C(r);
        if (r->unk10 & 5) {
            type = 7;
        } else {
            switch (arg1) {
            case 0:
                type = 0x10;
                break;
            case 1:
                type = 0x11;
                break;
            case 2:
                type = 6;
                break;
            }
        }
        break;
    case 3:
    case 4:
        r->unk3A = 90 / func_80277EA0(arg8);
        flags = 0x01080000;
        alpha = 0xD0;
        if (r->unk10 & 5) {
            type = 9;
        } else {
            type = 8;
        }
        break;
    case 5:
        r->unk3A = 4;
        flags = 0x01080000;
        alpha = 0xD0;
        type = 0xB;
        break;
    case 6:
        r->unk3A = 90 / func_80277EA0(arg8);
        flags = 0x01080000;
        alpha = 0xD0;
        type = 0xD;
        break;
    case 7:
        r->unk3A = 90 / func_80277EA0(arg8);
        flags = 0x01080000;
        alpha = 0xD0;
        type = 0xE;
        break;
    case 8:
        r->unk3A = 90.0f / (func_80277EA0(arg8) * 0.5f);
        flags = 0x01080000;
        alpha = 0xD0;
        type = 0xF;
        break;
    }
    obj = func_80231274(type, flags, alpha, NULL);
    if (obj == NULL) {
        return NULL;
    }
    obj->unk30 = 1;
    obj->unk38 = 0.0f;
    obj->unk34 = 40.0f;
    r->unk14 = obj;
    r->unk18 = obj->unk40;
    r->unk44 = arg3;
    if (arg1 == 5) {
        obj->unk40->unkC |= 0x8000;
        func_8022984C(r->unk14->unk40, 1);
        func_802297B8(r->unk14->unk40, 0xC, 0, 0);
    }
    r->unk40 = 0.0f;
    r->unk18->unk20 = 0.0f;
    switch (arg1) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
        r->unk28 = 0.1f;
        r->unk18->unk28 = 0.1f;
        r->unk2C = 0.1f;
        r->unk18->unk2C = 0.1f;
        r->unk30 = 0.1f;
        r->unk18->unk30 = 0.1f;
        break;
    case 5:
        r->unk28 = 0.05f;
        r->unk18->unk28 = 0.05f;
        r->unk2C = 0.05f;
        r->unk18->unk2C = 0.05f;
        r->unk30 = 0.05f;
        r->unk18->unk30 = 0.05f;
        break;
    }
    r->unk18->unk10 = r->unk1C;
    r->unk18->unk14 = r->unk20;
    r->unk18->unk18 = r->unk24;
    if (arg1 == 5) {
        r->unk18->unk14 += 30.0;
    }
    if (r->unk10 & 5) {
        if (r->unk36 >= 10) {
            r->unk36 = 8;
        }
    } else if (r->unk36 >= 7) {
        r->unk36 = 5;
    }
    if (r->unk10 & 0x100) {
        if (r->unk10 & 5) {
            r->unk36 = 9;
        } else {
            r->unk36 = 6;
        }
    }
    switch (r->unk36) {
    case 3:
        r->unk3C = 3.0f;
        break;
    case 4:
        r->unk3C = 4.5f;
        break;
    case 5:
        r->unk3C = 6.0f;
        break;
    case 6:
        r->unk3C = 7.5f;
        break;
    case 7:
        r->unk3C = 9.0f;
        break;
    case 8:
        r->unk3C = 10.5f;
        break;
    case 9:
        r->unk3C = 12.0f;
        break;
    default:
        r->unk3C = 3.0f;
        break;
    }
    D_802AFE70++;
    return r;
}

s16 func_80277F74() {
    s16 i;
    Rec926 *p;

    for (i = 0, p = RECS; i < 48; i++, p++) {
        if (p->unk18 == NULL) {
            break;
        }
    }
    if (i < 48) {
        return i;
    }
    return -1;
}

s16 func_80277F0C(Rec926 *arg0) {
    s16 f;
    s16 r;

    f = arg0->unk10 & 0xF1FD;
    r = 0x40;
    if (f == 0x100) {
        r = 0x10;
    }
    if ((f == 1) || (f == 4) || (f == 5)) {
        r = 0x10;
    }
    if ((f == 0x101) || (f == 0x104) || (f == 0x105)) {
        r = 0;
    }
    return r;
}

s32 func_80277EA0(s16 arg0) {
    s32 r;

    r = 0x28;
    switch (arg0) {
    case 3:
        return 0x14;
    case 4:
        return 0x18;
    case 5:
        return 0x1C;
    case 6:
        return 0x20;
    case 7:
        return 0x24;
    case 9:
        r = 0x2D;
        /* fallthrough */
    default:
        return r;
    }
}
