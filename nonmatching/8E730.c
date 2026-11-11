/*
 * NON_MATCHING: main_code's 8E730, complete (47 functions,
 * func_80273F30..func_80277E1C). Split from 87D80 by IDO's emission
 * order (text_objects.txt). A first draft from m2c; every function
 * global, emitted in the original's order. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 434, eu 434, jp 434
 *
 * 36 of 47 match. Biggest left: func_802741D8 461, func_8027655C 436,
 * func_80274994 320 (still m2c's control flow and untyped offsets),
 * func_80275DD8 150 (the ABS chains: the original keeps some ?: temps
 * on the stack), func_802763DC 73 (cvt'd floats stored to dead stack
 * homes), func_80276184 60 and func_80275C7C 34 (a flag test wants v0
 * but the entity pointer holds it); the rest are a few words of
 * register or stack-slot order.
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

typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ f32 x;
    /* 0x14 */ f32 y;
    /* 0x18 */ f32 z;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ f32 rot;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ f32 sx;
    /* 0x2C */ f32 sy;
    /* 0x30 */ f32 sz;
} Sub8E; /* the object's transform */

typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[0x30 - 0x14];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ Sub8E *unk40;
    /* 0x44 */ u8 pad44[0x4C - 0x44];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ u8 pad64[4];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} Obj8E;

typedef struct Ent88 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ struct Ent88 *next;
    /* 0x18 */ struct Ent88 *prev;
    /* 0x1C */ Obj8E *obj;
    /* 0x20 */ Sub8E *xf;
    /* 0x24 */ void *unk24[3];
    /* 0x30 */ Obj8E *unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ void *unk38;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 pad3E[2];
    /* 0x40 */ f32 x;
    /* 0x44 */ f32 y;
    /* 0x48 */ f32 z;
    /* 0x4C */ u8 pad4C[4];
    /* 0x50 */ f32 unk50;
    /* 0x54 */ u8 pad54[8];
    /* 0x5C */ s16 unk5C;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ s16 unk60;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ s16 unk66;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ u8 pad6A[0x74 - 0x6A];
    /* 0x74 */ s16 unk74;
    /* 0x76 */ u8 pad76[2];
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
} Ent88; /* size 0x88 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x1C - 0x12];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 pad28[8];
} Slot30; /* size 0x30 */

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 pad24[0xC8 - 0x24];
} Player8E; /* size 0xC8 */

#define ENTS ((Ent88 *) D_8008F438)
#define ENT_HEAD (*(Ent88 **) &D_8008F44C)
#define ENT_4C0 ((Ent88 *) D_8008F4C0)
#define SLOTS ((Slot30 *) D_802AFCE8)
#define PLAYERS ((Player8E *) D_800AEDF0)
#define IDS ((s16 (*)[9]) D_802AFC78)
#define OBJ_DD8 (*(Obj8E **) &D_802AFDD8)
#define VEC_E60 ((f32 *) D_802AFE60)
#define LIVE(e) ((e)->x != 1e7f)
typedef struct {
    Node87 n;
    u8 pad[0x3C - 8];
} Node3C;
#define NODES ((Node3C *) &D_802AFDE0)

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
void func_8027F820();
void func_8027F858(s32, s32);
s32 func_80286CA8(s32, f32, f32, f32);
s32 func_802870A8(void);
s32 func_80287440(void);
s32 func_802875B0(void);
s32 func_8028A4E0(s32);
s32 func_8028A81C(s32, f32, f32, f32, s32);
s32 func_802909FC(void *, s32 (*)(s32));
/*
 * func_8027655C passes func_80277378, but the original emits it after
 * func_8027723C: there the reference makes no call-graph edge, here it
 * would move func_80277378 before func_8027655C. Until the reason is
 * known, it is reached from D_802A14B4 (a data symbol, so the offset
 * folds into the relocation): the same lui/addiu, and no edge.
 */
extern s16 D_802A14B4;
#if VERSION_JP
#define FN_80277378 ((s32 (*)(s32)) ((u8 *) &D_802A14B4 - 0x29A4C))
#else
#define FN_80277378 ((s32 (*)(s32)) ((u8 *) &D_802A14B4 - 0x2A13C))
#endif
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

u16 func_8026D7D8(s32 arg0, s32 arg1, s32 arg2);
u8 func_8026DC74(s32 arg0);
void func_8026DCAC(f32 arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4);
void func_8026E338(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, s32 arg4);
f32 func_8026E8B8(void);
f32 func_8026E938(u8 *arg0);
void *func_802700EC(u8 *arg0, u8 *arg1, s16 arg2, f32 arg3);
void func_802702EC(s16 arg0);
s16 *func_802703B4(u8 *arg0);
s32 func_802704F8(f32 arg0);
void func_80270A80(void *arg0);
void func_80270BA4(u8 *arg0);
f32 func_80270F44(u8 *arg0);
f32 func_80270FC0(u8 *arg0);
void func_80271010(u8 *arg0, s16 arg1);
void func_802712C4(s16 *arg0);
s32 func_8027130C(u8 *arg0);
void func_802714C4(void);
s32 func_80271540(s16 arg0);
void *func_802716F8(s16 arg0);
void func_80271F74(s32 *arg0);
s32 func_80272024(s16 arg0);
s16 func_8027241C(s16 arg0);
void func_802727D8(s32 *arg0);
void func_802733C8(u8 *arg0);
void func_802733F8(void *arg0);
void func_80273414(void *arg0);
void func_802734BC(void *arg0);
void *func_8027361C(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4);
s32 func_80273A5C(s32 arg0, s32 arg1, s32 arg2);
s32 func_80273AD4(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80273E2C(s16 arg0);
void *func_80273F30(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4);
void func_8027404C(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
void func_802740AC(s16 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4);
void func_802741D8(s16 arg0);
s32 func_80274994(s16 arg0);
s16 func_80274F64(s16 arg0);
void func_80274F8C(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4);
void func_80274FD4(Ent88 *arg0);
void func_80275034(s16 *arg0);
s32 func_802750C0(s16 *arg0, s16 arg1);
void func_80275120(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
void func_802752BC(s16 *arg0);
void func_80275590(s16 *arg0);
void func_802756DC(s16 *arg0);
void func_802757E0(s16 *arg0);
void func_80275948(s16 *arg0);
void func_80275C08(u8 *arg0, u8 *arg1);
void func_80275C7C(s16 arg0, u8 *arg1, s16 arg2);
s32 func_80275DD8(Ent88 *a, Ent88 *b);
void func_80276184(s16 *arg0, u8 *arg1);
static void func_80271448_inl(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
static s16 func_802712A8_inl(s16 *arg0, s16 arg1);
void func_802763DC(s16 *arg0);
s32 func_8027655C(Ent88 *arg0);
void func_80276D68(Ent88 *arg0);
void func_8027723C(void);
s32 func_80277378(s32 arg0);
s32 func_802773A8(s16 arg0, s16 arg1);
void func_80277484(void);
void func_8027750C(s16 arg0);
void func_802775D8(f32 *arg0);
void func_80277774(void);
void func_802777D0(void);
void func_8027783C(void);
void func_80277984(s16 *arg0, s16 arg1);
void *func_8027799C(s16 arg0);
void func_802779C4(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
void func_80277A28(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
void func_80277AA0(s16 arg0, s16 arg1);
void func_80277AF8(s16 arg0, s16 arg1);
void func_80277B54(void);
s16 func_80277CC0(u8 *arg0);
void *func_80277CE0(void);
s32 func_80277CEC(s32 arg0);
void func_80277D20(s16 arg0, s16 arg1);
void func_80277D60(s16 arg0, s16 arg1);
void func_80277DA8(s16 arg0, s16 arg1);
void func_80277DF4(s16 arg0);
void func_80277E1C(void);
void *func_80277FC4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s16 arg8, s32 arg9);
void func_80278D54(s32 *arg0);
void func_80278DBC(void);

void func_80277E1C() {
    s32 i;

    for (i = 0; i < 5; i++) {
        PLAYERS[i].unk18 = 0x200;
        PLAYERS[i].unk1C = 2;
        PLAYERS[i].unk20 = 2;
    }
}

void func_80277DF4(s16 arg0) {
    M2C_FIELD(D_800AEDF0, s32 *, 0x18) = (s32) (M2C_FIELD(D_800AEDF0, s32 *, 0x18) & ~arg0);
}

void func_80277DA8(s16 arg0, s16 arg1) {
    u8 *temp_v0;

    temp_v0 = (arg0 * 0xC8) + D_800AEDF0;
    M2C_FIELD(temp_v0, s32 *, 0x18) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x18) & ~arg1);
}

void func_80277D60(s16 arg0, s16 arg1) {
    u8 *temp_v0;

    temp_v0 = (arg0 * 0xC8) + D_800AEDF0;
    M2C_FIELD(temp_v0, s32 *, 0x18) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x18) | arg1);
}

void func_80277D20(s16 arg0, s16 arg1) {
    *(s32 *)((u8 *)&D_800AEE08 + (arg0 * 0xC8)) = arg1 | 0x200;
}

s32 func_80277CEC(s32 arg0) {
    s32 r;

    if (SLOTS[arg0].unk10 <= 0) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

void *func_80277CE0() {
    return D_8008F438;
}

s16 func_80277CC0(u8 *arg0) {
    return M2C_FIELD(func_802703B4(arg0), s16 *, 0xE);
}

void func_80277B54() {
    s16 i;
    Ent88 *e;

    func_80297D30(0x27, D_802A14B8);
    D_802AFC70 = 0;
    D_802AFC74 = 0;
    D_802AFE58.next = NULL;
    VEC_E60[0] = 0.0f;
    VEC_E60[1] = 0.0f;
    VEC_E60[2] = 0.0f;
    for (i = 0; i < 5; i++) {
        SLOTS[i].unk10 = 0;
    }
    for (i = 0; i < 5; i++) {
        PLAYERS[i].unk1C = 2;
    }
    for (i = 0, e = ENTS; i < 22; i++, e++) {
        e->xf = NULL;
    }
    for (i = 0; i < 6; i++) {
        IDS[i][0] = -1;
    }
    ENTS[0].next = ENT_4C0;
    ENTS[0].prev = NULL;
    ENTS[0].xf = (Sub8E *) -1;
    ENT_4C0->next = NULL;
    ENT_4C0->prev = ENTS;
    ENT_4C0->xf = (Sub8E *) -1;
    D_802AFDE0.next = &D_802AFE1C;
    D_802AFDE0.unk4 = 0;
    D_802AFE1C.next = NULL;
    D_802AFE1C.unk4 = 0;
}

void func_80277AF8(s16 arg0, s16 arg1) {
    PLAYERS[arg0].unk1C += arg1;
    if (PLAYERS[arg0].unk1C >= 9) {
        PLAYERS[arg0].unk1C = 8;
    }
}

void func_80277AA0(s16 arg0, s16 arg1) {
    PLAYERS[arg0].unk1C -= arg1;
    if (PLAYERS[arg0].unk1C <= 0) {
        PLAYERS[arg0].unk1C = 1;
    }
}

void func_80277A28(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    Unk8026DCAC sp20;

    func_8026DCAC(arg0, arg1, arg2, &sp20, 0);
    *arg3 = sp20.i[0];
    *arg4 = sp20.i[1];
    *arg5 = sp20.i[2];
}

void func_802779C4(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    f32 sp24[3];

    func_8026E338(arg0, arg1, arg2, sp24, 1);
    *arg3 = sp24[0];
    *arg4 = sp24[1];
    *arg5 = sp24[2];
}

void *func_8027799C(s16 arg0) {
    return (arg0 * 0x88) + D_8008F438;
}

void func_80277984(s16 *arg0, s16 arg1) {
    *arg0 ^= arg1;
}

void func_8027783C() {
    s32 i;
    Ent88 *e;
    s32 live;
    Node87 *n;
    Node87 *h = &D_802AFDE0;

    func_802777D0();
    for (i = 0; i < 5; i++) {
        SLOTS[i].unk10 = 0;
    }
    if (D_802AFC70 == 1) {
        D_802AFC70 = 0;
        for (e = ENT_HEAD; e->next != NULL; e = e->next) {
            live = (e->x != 1e7f) ? 1 : 0;
            if (live) {
                func_80273414(e);
            }
            func_802733F8(e);
            func_80238EA8(e->unk4);
        }
        func_80278DBC();
    }
    while (D_802AFE58.next != NULL) {
        n = h->next;
        func_80270A80(h->next);
        free(n);
    }
}

void func_802777D0() {
    s16 i;

    if (D_802AFC74 != 0) {
        D_802AFC74 = 0;
        for (i = 0; i < 5; i++) {
            func_802702EC(i);
        }
        func_8022FC90(D_802AFDD8);
    }
}

void func_80277774() {
    Node87 *n;
    Node87 *h = &D_802AFDE0;

    while (D_802AFE58.next != NULL) {
        n = h->next;
        func_80270A80(h->next);
        free(n);
    }
}

void func_802775D8(f32 *arg0) {
    f32 minx;
    f32 maxx;
    f32 miny;
    f32 maxy;
    f32 minz;
    f32 maxz;
    Ent88 *e;
    s32 live;
    Sub8E *s;

    minx = arg0[0] - 200.0f;
    miny = arg0[1] - 200.0f;
    minz = arg0[2] - 200.0f;
    maxx = arg0[0] + 200.0f;
    maxy = arg0[1] + 200.0f;
    maxz = arg0[2] + 200.0f;
    live = 0;
    for (e = ENT_HEAD; e->next != NULL; e = e->next) {
        live = (e->x != 1e7f) ? 1 : 0;
        if (live) {
            s = e->obj->unk40;
            if (!(s->x < minx) && !(maxx < s->x) && !(s->y < miny) && !(maxy < s->y) && !(s->z < minz) && !(maxz < s->z)) {
                func_802734BC(e->obj);
            }
        }
    }
}

void func_8027750C(s16 arg0) {
    Ent88 *e;
    s32 live;
    s16 f;

    if (D_802AFC70 != 0) {
        live = 0;
        for (e = ENT_HEAD; e->next != NULL; e = e->next) {
            if (arg0 == e->unkE && (e->unk10 & 2) && (f = e->unk64 & 0x10) == 0) {
                live = (e->x != 1e7f) ? 1 : 0;
                if (live) {
                    e->unk64 |= 1;
                    return;
                }
            }
        }
    }
}

void func_80277484() {
    Ent88 *e;
    s32 live;

    if (D_802AFC70 != 0) {
        live = 0;
        for (e = ENT_HEAD; e->next != NULL; e = e->next) {
            live = (e->x != 1e7f) ? 1 : 0;
            if (live) {
                e->unk64 |= 1;
            }
        }
    }
}

s32 func_802773A8(s16 arg0, s16 arg1) {
    s32 r = 9;

    switch (arg0) {
    case 0:
        switch (arg1) {
        case 90:
            r = 0;
            break;
        case 270:
            r = 4;
            break;
        }
        break;
    case 90:
        switch (arg1) {
        case 0:
            r = 6;
            break;
        case 90:
            r = 7;
            break;
        case 270:
            r = 5;
            break;
        }
        break;
    case 270:
        switch (arg1) {
        case 0:
            r = 2;
            break;
        case 90:
            r = 1;
            break;
        case 270:
            r = 3;
            break;
        }
        break;
    }
    return r;
}

s32 func_80277378(s32 arg0) {
    s32 var_v1;

    if ((arg0 & 0xF) == 0xF) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    if (arg0 & 0x60) {
        var_v1 = 0;
    }
    return var_v1;
}

void func_8027723C() {
    Ent88 *e;
    s16 f;

    e = (Ent88 *) func_802391F0();
    for (;;) {
        e->x = e->xf->x;
        e->y = e->xf->y;
        e->z = e->xf->z;
        func_802313DC(e->obj, 0x1E00);
        if ((f = e->unk64 & 4) != 0) {
            func_80231408(e->obj, 0x400);
        } else if ((f = e->unk64 & 0x200) != 0 || ((f = e->unk64 & 8) != 0 && (f = e->unk64 & 0x400) != 0)) {
            func_80231408(e->obj, 0x400);
        }
        if (e->unk68 > 0 || (f = e->unk64 & 0x40) == 0 || e->unk74 != 0) {
            func_80276D68(e);
            if (func_8027655C(e) != 0) {
                return;
            }
        }
        func_80274FD4(e);
        if (e->unk3C > 0) {
            e->unk3C--;
        }
        func_80239094();
    }
}

void func_80276D68(Ent88 *arg0) {
    s16 f;

    if (D_802A14B4 == 1) {
        return;
    }
    if (arg0->unk8 != -1) {
        if (arg0->unkC > 60) {
            func_8028A4E0(arg0->unk8);
            arg0->unk8 = -1;
        } else {
            arg0->unkC++;
        }
    }
    f = arg0->unk64 & 0x20;
    if (f != 0) {
        arg0->unk78 -= arg0->unk84;
        if (arg0->unk78 < arg0->unk7C) {
            arg0->unk64 &= ~0x20;
            if (arg0->unk10 & 0x800) {
                arg0->unk84 = 0.033333335f;
            } else if (arg0->unk10 & 0x400) {
                arg0->unk84 = 0.008333334f;
            } else {
                arg0->unk84 = 0.0033333334f;
            }
            f = arg0->unk64 & 0x20;
        } else {
            arg0->unk84 += arg0->unk84 * 0.1;
            f = arg0->unk64 & 0x20;
        }
    }
    if (f == 0) {
        arg0->unk78 += arg0->unk84;
        if (arg0->unk68 < 15) {
            if (arg0->unk10 & 0x800) {
                if (arg0->unk78 >= 13.0f) {
                    arg0->unk64 |= 0x40;
                }
            } else if (arg0->unk78 >= arg0->unk80) {
                arg0->unk64 |= 0x40;
            }
        }
        if (arg0->unk80 < arg0->unk78) {
            arg0->unk64 |= 0x20;
            if (arg0->unk10 & 0x800) {
                arg0->unk84 = 0.033333335f;
            } else if (arg0->unk10 & 0x400) {
                arg0->unk84 = 0.008333334f;
            } else {
                arg0->unk84 = 0.0033333334f;
            }
        } else {
            arg0->unk84 += arg0->unk84 * 0.1;
        }
    }
    arg0->unk5C--;
    if (arg0->unk5C < 0) {
        arg0->unk5C = 0;
    }
    if (arg0->unk60 > 0) {
        arg0->unk60--;
    }
    if (arg0->unk62 > 0) {
        arg0->unk62--;
    }
    if (!(arg0->unk10 & 0x800) && (s16) ((f = arg0->unk64) & 0x80) == 0) {
        arg0->unk80 = 1.0f;
        arg0->unk7C = 0.9f;
        if (arg0->unk5C < 100) {
            arg0->unk5E = 0;
        }
        if (arg0->unk5C > 100 && arg0->unk5C <= 200) {
            if (arg0->unk5E <= 0 && arg0->unk60 <= 0) {
                func_8026C660(0x16);
                arg0->unk60 = 60;
            }
            arg0->unk5E = 1;
            arg0->unk80 = 1.3f;
            arg0->unk7C = 1.1f;
        }
        if (arg0->unk5C > 200) {
            if (arg0->unk5E < 2 && arg0->unk62 <= 0) {
                func_8026C660(0x17);
                arg0->unk62 = 60;
            }
            arg0->unk5E = 2;
            arg0->unk80 = 1.6f;
            arg0->unk7C = 1.4f;
        }
        if (arg0->unk5C > 300) {
            arg0->obj->unk34 = 70.0f;
            arg0->obj->unk38 = 70.0f;
            if (func_80232D18(arg0->obj, 0x10) == 0) {
                arg0->unk80 = 1.9f;
                arg0->unk10 |= 0x100;
                arg0->unk7C = 1.7f;
                func_80231408(arg0->obj, 0x2000);
                func_8026C660(0x1A);
                arg0->unk8 = func_8028A81C(0x15, 0.0f, 100.0f, 0.0f, (s32) arg0->obj);
                arg0->unkC = 0;
                arg0->obj->unk30 = 0x21;
                arg0->unk64 |= 0x80;
            } else {
                arg0->obj->unk34 = 40.0f;
                arg0->obj->unk38 = 40.0f;
            }
        }
    }
}

s32 func_8027655C(Ent88 *arg0) {
    s32 padT;
    f32 sp168;
    struct { f32 z, y, x; } v;
    f32 sp158;
    void *sp154;
    s32 pad[55];
    s16 fl;
    s16 f4;
    s32 padB[1];

    if (D_802A14B4 == 1) {
        return 0;
    }
    if ((s16) (arg0->unk64 & 2)) {
        arg0->unk68--;
    }
    if (arg0->unk68 < 15) {
        if (arg0->unk10 & 0x800) {
            arg0->unk80 = 13.0f;
        } else if ((s16) (arg0->unk64 & 0x80)) {
            arg0->unk80 = 2.0f;
        } else {
            arg0->unk80 = 1.3f;
        }
    }
    arg0->obj->unkC = 0xE0;
    arg0->obj->unkC |= 0x10;
    if (arg0->obj->unk10 & 0xE0) {
        func_80275948((s16 *) arg0);
    }
    sp168 = 0.0f;
    if ((s16) (arg0->unk64 & 4)) {
        sp168 = 15.0f;
    }
    func_80291944(arg0->obj, func_80272024(arg0->unk74), sp168);
    arg0->x = arg0->xf->x;
    arg0->y = arg0->xf->y;
    arg0->z = arg0->xf->z;
    func_802763DC((s16 *) arg0);
    if (!(s16) (arg0->unk64 & 0x200) && !(s16) (arg0->unk64 & 0x10)) {
        arg0->obj->unk70 = 1.6333334f;
        sp158 = arg0->obj->unk6C;
        arg0->unk64 &= ~8;
        func_80230914(arg0->obj);
        if (arg0->obj->unk6C == 0.0f && arg0->obj->unk68 == 0.0f) {
            if (!(s16) (arg0->unk64 & 0x800)) {
                arg0->unk64 |= 8;
                arg0->unk64 |= 0x800;
            }
            arg0->unk50 = 0.0f;
            if (sp158 != arg0->obj->unk6C) {
                arg0->unk30 = arg0->obj;
            }
        } else {
            arg0->unk64 |= 8;
            arg0->unk64 &= ~0x800;
        }
        arg0->x = arg0->xf->x;
        arg0->y = arg0->xf->y;
        arg0->z = arg0->xf->z;
    }
    fl = arg0->unk64 & 0x10;
    if (!fl && !(s16) (arg0->unk64 & 0x200)) {
        if (func_802909FC(arg0->obj, FN_80277378) && func_8023369C(arg0->xf->x, arg0->obj->unk58, 1.0f)
            && func_8023369C(arg0->xf->z, arg0->obj->unk60, 1.0f) && (s16) (arg0->unk64 & 4)) {
            func_802712C4((s16 *) arg0);
        }
        f4 = arg0->unk64 & 4;
    } else if (fl) {
        func_802733C8((u8 *) arg0->obj);
        f4 = arg0->unk64 & 4;
    } else {
        func_802727D8(arg0->unk38);
        f4 = arg0->unk64 & 4;
    }
    arg0->x = arg0->xf->x;
    arg0->y = arg0->xf->y;
    arg0->z = arg0->xf->z;
    if (f4 || (s16) (arg0->unk64 & 8)) {
        func_802714C4();
        OBJ_DD8->unk40->x = OBJ_DD8->unk58 = arg0->x;
        OBJ_DD8->unk40->y = OBJ_DD8->unk5C = arg0->y;
        OBJ_DD8->unk40->z = OBJ_DD8->unk60 = arg0->z;
        OBJ_DD8->unk40->sz = 1.0f;
        OBJ_DD8->unk40->sx = OBJ_DD8->unk40->sy = OBJ_DD8->unk40->sz;
        OBJ_DD8->unk30 = 1;
        OBJ_DD8->unk34 = 40.0f;
        OBJ_DD8->unk38 = 40.0f;
        if (!(s16) (arg0->unk64 & 0x400) && !func_80232D18(OBJ_DD8, 1)) {
            arg0->unk64 |= 0x400;
        }
        if ((s16) (arg0->unk64 & 0x400)) {
            sp154 = func_802308B8(arg0->obj, 0x16);
        } else {
            sp154 = (void *) func_8022F4AC((s32) arg0->obj, 0x16, (s32) func_802443F4(arg0->unkE));
        }
        if (sp154 != NULL) {
            arg0->x = arg0->xf->x = arg0->obj->unk58;
            arg0->y = arg0->xf->y = arg0->obj->unk5C;
            arg0->z = arg0->xf->z = arg0->obj->unk60;
            func_80276184((s16 *) arg0, sp154);
            func_802712C4((s16 *) arg0);
            if ((s16) (arg0->unk64 & 8)) {
                void *r = func_802700EC((u8 *) arg0->obj, sp154, func_80272024(arg0->unk74), sp168);
                arg0->unk64 |= 0x200;
                arg0->unk38 = r;
                arg0->unk64 &= ~8;
            }
            OBJ_DD8->unk40->x = OBJ_DD8->unk58 = arg0->x;
            OBJ_DD8->unk40->y = OBJ_DD8->unk5C = arg0->y;
            OBJ_DD8->unk40->z = OBJ_DD8->unk60 = arg0->z;
            if ((s16) (arg0->unk64 & 0x400) && func_80232D18(OBJ_DD8, 1)) {
                arg0->unk64 &= ~0x400;
            }
        }
    }
    if ((s16) (arg0->unk64 & 0x40)) {
        arg0->unk64 |= 1;
    }
    if ((s16) (arg0->unk64 & 1)) {
        func_80275948((s16 *) arg0);
        return 1;
    }
    func_80271448_inl(arg0->x, arg0->y, arg0->z, &v.x, &v.y, &v.z);
    if ((func_8026D7D8((s32) v.x, (s32) v.y, (s32) v.z) & 0xF) == 9) {
        func_80275948((s16 *) arg0);
    }
    func_80275034((s16 *) arg0);
    return 0;
}

static s16 func_802712A8_inl(s16 *arg0, s16 arg1) {
    return *arg0 & arg1;
}

static void func_80271448_inl(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    s32 sp20[6];

    func_8026DCAC(arg0, arg1, arg2, sp20, 2);
    *arg3 = sp20[0];
    *arg4 = sp20[1];
    *arg5 = sp20[2];
}

void func_802763DC(s16 *arg0) {
    s32 padT;
    struct { f32 z, y, x; } v;
    s32 r;
    s16 f;
    s16 t;

    if ((f = ((Ent88 *) arg0)->unk64 & 0x10) != 0) {
        return;
    }
    ((Ent88 *) arg0)->xf->x = ((Ent88 *) arg0)->x;
    ((Ent88 *) arg0)->xf->y = ((Ent88 *) arg0)->y;
    ((Ent88 *) arg0)->xf->z = ((Ent88 *) arg0)->z;
    func_80271448_inl(((Ent88 *) arg0)->xf->x, ((Ent88 *) arg0)->xf->y, ((Ent88 *) arg0)->xf->z, &v.x, &v.y, &v.z);
    t = func_8026D7D8((s32) v.x, (s32) v.y, (s32) v.z) & 0x1C00;
    if (t) {
        func_8027F858(((Ent88 *) arg0)->obj, t >> 10);
    }
    ((Ent88 *) arg0)->x = ((Ent88 *) arg0)->xf->x;
    ((Ent88 *) arg0)->y = ((Ent88 *) arg0)->xf->y;
    ((Ent88 *) arg0)->z = ((Ent88 *) arg0)->xf->z;
}

void func_80276184(s16 *arg0, u8 *arg1) {
    Ent88 *t;

    if (arg1 != NULL && (((Obj8E *) arg1)->unk8 & 0x14) && !(((Obj8E *) arg1)->unk8 & 0x8002)) {
        func_80275C08(arg1, (u8 *) ((Ent88 *) arg0)->obj);
        func_802712C4(arg0);
        func_8026C51C(0x22, ((Ent88 *) arg0)->obj->unk40->x, ((Ent88 *) arg0)->obj->unk40->y, ((Ent88 *) arg0)->obj->unk40->z);
    }
    if (arg1 != NULL && (((Obj8E *) arg1)->unk8 & 4) && func_802712A8_inl(&((Ent88 *) arg0)->unk64, 0x80) != 0) {
        ((Ent88 *) arg0)->unk74 = 9;
    }
    if (arg1 != NULL && (((Obj8E *) arg1)->unk8 & 0x8000)) {
        ((Ent88 *) arg0)->unk74 = func_8027241C(((Ent88 *) arg0)->unk74);
        func_80275C08(arg1, (u8 *) ((Ent88 *) arg0)->obj);
        if (((Obj8E *) arg1)->unk8 & 4) {
            func_8026C51C(0x22, ((Ent88 *) arg0)->obj->unk40->x, ((Ent88 *) arg0)->obj->unk40->y, ((Ent88 *) arg0)->obj->unk40->z);
        } else {
            func_8026C51C(0x23, ((Ent88 *) arg0)->obj->unk40->x, ((Ent88 *) arg0)->obj->unk40->y, ((Ent88 *) arg0)->obj->unk40->z);
        }
    }
    if (arg1 != NULL && (((Obj8E *) arg1)->unk8 & 2) && !(((Obj8E *) arg1)->unk8 & 0x8000)) {
        t = (Ent88 *) func_802703B4(arg1);
        if (func_802712A8_inl(&((Ent88 *) arg0)->unk64, 4) != 0) {
            if (func_802712A8_inl(&t->unk64, 4) == 0) {
                if (func_802712A8_inl(&t->unk64, 0x200) != 0) {
                    func_80271F74(t->unk38);
                }
                if (func_80275DD8((Ent88 *) arg0, t) != 0) {
                    func_80275C7C(((Ent88 *) arg0)->unkE, (u8 *) t->obj, ((Ent88 *) arg0)->unk74);
                }
            } else {
                func_802712C4(t);
            }
            func_8026C51C(0x23, ((Ent88 *) arg0)->obj->unk40->x, ((Ent88 *) arg0)->obj->unk40->y, ((Ent88 *) arg0)->obj->unk40->z);
            func_80275C08(arg1, (u8 *) ((Ent88 *) arg0)->obj);
        }
    }
}

s32 func_80275DD8(Ent88 *arg0, Ent88 *arg1) {
    s32 pad[14];
    f32 sp14;
    s32 p1;
    f32 spC;
    s32 p2;
    f32 sp4;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv1;
    f32 var_fa1;
    f32 var_ft4;
    f32 var_ft4_2;
    f32 var_ft4_3;
    f32 var_ft5;
    f32 var_ft5_2;
    f32 var_ft5_3;
    f32 var_ft5_4;
    f32 var_fv0;
    f32 var_fv1;
    s16 dir;
    s32 r;
    u16 temp_t2;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), void **, 0x40);
    temp_v1 = M2C_FIELD(M2C_FIELD(arg1, void **, 0x1C), void **, 0x40);
    temp_fa1 = M2C_FIELD(temp_v0, f32 *, 0x10);
    temp_ft4 = M2C_FIELD(temp_v1, f32 *, 0x10);
    temp_fv1 = M2C_FIELD(temp_v0, f32 *, 0x18);
    temp_fa0 = M2C_FIELD(temp_v1, f32 *, 0x18);
    dir = 0;
    if (temp_ft4 <= temp_fa1) {
        dir = 4;
    }
    if (temp_fv1 < temp_fa0) {
        dir += 2;
    }
    if (temp_fa1 < 0.0f) {
        var_ft5 = -temp_fa1;
    } else {
        var_ft5 = temp_fa1;
    }
    if (temp_ft4 < 0.0f) {
        sp14 = -temp_ft4;
    } else {
        sp14 = temp_ft4;
    }
    if (var_ft5 < sp14) {
        if (temp_fa1 < 0.0f) {
            var_ft5_2 = -temp_fa1;
        } else {
            var_ft5_2 = temp_fa1;
        }
        if (temp_ft4 < 0.0f) {
            spC = -temp_ft4;
        } else {
            spC = temp_ft4;
        }
        var_fa1 = -(var_ft5_2 - spC);
    } else {
        if (temp_fa1 < 0.0f) {
            var_ft5_3 = -temp_fa1;
        } else {
            var_ft5_3 = temp_fa1;
        }
        if (temp_ft4 < 0.0f) {
            sp4 = -temp_ft4;
        } else {
            sp4 = temp_ft4;
        }
        var_fa1 = var_ft5_3 - sp4;
    }
    if (temp_fv1 < 0.0f) {
        var_ft4 = -temp_fv1;
    } else {
        var_ft4 = temp_fv1;
    }
    if (temp_fa0 < 0.0f) {
        var_ft5_4 = -temp_fa0;
    } else {
        var_ft5_4 = temp_fa0;
    }
    if (var_ft4 < var_ft5_4) {
        if (temp_fv1 < 0.0f) {
            var_ft4_2 = -temp_fv1;
        } else {
            var_ft4_2 = temp_fv1;
        }
        if (temp_fa0 < 0.0f) {
            var_fv0 = -temp_fa0;
        } else {
            var_fv0 = temp_fa0;
        }
        var_fv1 = -(var_ft4_2 - var_fv0);
    } else {
        if (temp_fv1 < 0.0f) {
            var_ft4_3 = -temp_fv1;
        } else {
            var_ft4_3 = temp_fv1;
        }
        if (temp_fa0 < 0.0f) {
            var_fv0 = -temp_fa0;
        } else {
            var_fv0 = temp_fa0;
        }
        var_fv1 = var_ft4_3 - var_fv0;
    }
    if (var_fv1 <= var_fa1) {
        dir += 1;
    }
    r = 0;
    switch (*(u16 *) &arg0->unk74) {
    case 0:
        if (dir == 0 || dir == 1 || dir == 4 || dir == 5) {
            r = 1;
        }
        break;
    case 1:
        if (dir == 0 || dir == 1 || dir == 3 || dir == 4) {
            r = 1;
        }
        break;
    case 2:
        if (dir == 0 || dir == 1 || dir == 2 || dir == 3) {
            r = 1;
        }
        break;
    case 3:
        if (dir == 1 || dir == 2 || dir == 3 || dir == 6) {
            r = 1;
        }
        break;
    case 4:
        if (dir == 2 || dir == 3 || dir == 6 || dir == 7) {
            r = 1;
        }
        break;
    case 5:
        if (dir == 2 || dir == 5 || dir == 6 || dir == 7) {
            r = 1;
        }
        break;
    case 6:
        if (dir == 4 || dir == 5 || dir == 6 || dir == 7) {
            r = 1;
        }
        break;
    case 7:
        if (dir == 0 || dir == 4 || dir == 5 || dir == 7) {
            r = 1;
        }
        break;
    }
    return r;
}

void func_80275C7C(s16 arg0, u8 *arg1, s16 arg2) {
    s16 f;
    Ent88 *e;
    s16 *row;
    s16 *p;
    s32 id;
    s32 cur;
    s32 i;
    s32 fl;
    s32 neg;
    void *n;

    e = (Ent88 *) func_802703B4(arg1);
    if (e == NULL) {
        return;
    }
    if (func_802712A8_inl(&e->unk64, 0x10) != 0) {
        return;
    }
    if (func_802712A8_inl(&e->unk64, 0x200) != 0) {
        e->unk64 &= ~0x200;
        func_802313DC(e->obj, 0x20000);
        n = e->unk38;
        func_80270A80(n);
        free(n);
    }
    if (e->unk10 & 0x100) {
        return;
    }
    row = IDS[arg0];
    neg = -1;
    id = e->unk0;
    for (i = 0; i < 8; i = (s16) (i + 1)) {
        p = (s16 *) ((u8 *) row + i * 2);
        cur = *p;
        if (id == cur && arg2 == e->unk74) {
            return;
        }
        if (id == cur) {
            break;
        }
        if (neg == cur) {
            *p = id;
            break;
        }
    }
    if (i < 8) {
        row[i + 1] = neg;
        e->unkE = arg0;
        e->unk64 |= 4;
        e->unk74 = arg2;
    }
}

void func_80275C08(u8 *arg0, u8 *arg1) {
    Ent88 *e;

    e = (Ent88 *) func_802703B4(arg1);
    if (e->unk3C <= 0) {
        func_8028A81C(0, (*(Sub8E **) (arg1 + 0x40))->x, (*(Sub8E **) (arg1 + 0x40))->y + 100.0f, (*(Sub8E **) (arg1 + 0x40))->z, 0);
        e->unk3C = 25;
    }
}

void func_80275948(s16 *arg0) {
    u16 n;
    u16 i;
    f32 x;
    f32 y;
    f32 z;
    u16 snd;
    s16 f;
    void *nd;

    func_80270BA4((u8 *) ((Ent88 *) arg0)->obj);
    if ((f = ((Ent88 *) arg0)->unk64 & 0x200) != 0) {
        ((Ent88 *) arg0)->unk64 &= ~0x200;
        func_802313DC(((Ent88 *) arg0)->obj, 0x20000);
        nd = ((Ent88 *) arg0)->unk38;
        func_80270A80(nd);
        free(nd);
    }
    switch (((Ent88 *) arg0)->unk10 & ~0xC02) {
    case 0x200:
        func_802752BC(arg0);
        n = 3;
        break;
    case 0x201:
    case 0x204:
    case 0x205:
        func_802757E0(arg0);
        n = 3;
        break;
    case 0x300:
        func_802756DC(arg0);
        n = 2;
        break;
    case 0x301:
    case 0x304:
    case 0x305:
        func_80275590(arg0);
        n = 3;
        break;
    default:
        func_802752BC(arg0);
        n = 3;
        break;
    }
    x = ((Ent88 *) arg0)->x;
    y = ((Ent88 *) arg0)->y;
    z = ((Ent88 *) arg0)->z;
    func_80273414(arg0);
    snd = 11;
    ((Ent88 *) arg0)->x = ((Ent88 *) arg0)->y = ((Ent88 *) arg0)->z = 1e7f;
    if (((Ent88 *) arg0)->unk10 & 1) {
        switch (((Ent88 *) arg0)->unk66) {
        case 3:
            snd = 15;
            break;
        case 4:
            snd = 16;
            break;
        case 5:
            snd = 17;
            break;
        case 6:
            snd = 18;
            break;
        case 7:
            snd = 19;
            break;
        case 8:
            snd = 20;
            break;
        case 9:
            snd = 21;
            break;
        }
        if (((Ent88 *) arg0)->unk10 & 0x100) {
            snd = 21;
        }
    } else {
        switch (((Ent88 *) arg0)->unk66) {
        case 3:
            break;
        case 4:
            snd = 12;
            break;
        case 5:
            snd = 13;
            break;
        }
        if (((Ent88 *) arg0)->unk10 & 0x100) {
            snd = 14;
        }
    }
    func_8026C51C(snd, x, y, z);
    for (;;) {
        if (func_802750C0(arg0, n) != 0) {
            break;
        }
        for (i = 0; i < n; i++) {
            if (((Ent88 *) arg0)->unk24[i] != NULL) {
                func_80278D54(((Ent88 *) arg0)->unk24[i]);
            }
        }
        func_80239094();
    }
    func_802733F8(arg0);
    ((Ent88 *) arg0)->xf = NULL;
    func_80238EA8(((Ent88 *) arg0)->unk4);
    func_80239094();
}

void func_802757E0(s16 *arg0) {
    u16 k;
    u16 id;
    f32 x;
    f32 y;
    f32 z;

    id = ((Ent88 *) arg0)->unkE;
    k = ((Ent88 *) arg0)->unk66;
    if (((Ent88 *) arg0)->unk10 & 4) {
        k = 8;
    }
    func_80275120(((Ent88 *) arg0)->x, ((Ent88 *) arg0)->y, ((Ent88 *) arg0)->z, &x, &y, &z);
    if (((Ent88 *) arg0)->unk10 & 0x100) {
        k = 9;
    }
    ((Ent88 *) arg0)->unk24[0] = func_80277FC4(id, 0, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[0]);
    ((Ent88 *) arg0)->unk24[1] = func_80277FC4(id, 5, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[1]);
    ((Ent88 *) arg0)->unk24[2] = func_80277FC4(id, 6, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[2]);
}

void func_802756DC(s16 *arg0) {
    u16 k;
    u16 id;
    f32 x;
    f32 y;
    f32 z;

    id = ((Ent88 *) arg0)->unkE;
    k = ((Ent88 *) arg0)->unk66;
    func_80275120(((Ent88 *) arg0)->x, ((Ent88 *) arg0)->y, ((Ent88 *) arg0)->z, &x, &y, &z);
    if (((Ent88 *) arg0)->unk10 & 0x100) {
        k = 9;
    }
    ((Ent88 *) arg0)->unk24[0] = func_80277FC4(id, 3, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[0]);
    ((Ent88 *) arg0)->unk24[1] = func_80277FC4(id, 0, ((Ent88 *) arg0)->unk10, 8, 40, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[1]);
}

void func_80275590(s16 *arg0) {
    u16 k;
    u16 id;
    f32 x;
    f32 y;
    f32 z;

    id = ((Ent88 *) arg0)->unkE;
    k = ((Ent88 *) arg0)->unk66;
    func_80275120(((Ent88 *) arg0)->x, ((Ent88 *) arg0)->y, ((Ent88 *) arg0)->z, &x, &y, &z);
    if (((Ent88 *) arg0)->unk10 & 0x100) {
        k = 9;
    }
    ((Ent88 *) arg0)->unk24[0] = func_80277FC4(id, 3, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[0]);
    ((Ent88 *) arg0)->unk24[1] = func_80277FC4(id, 5, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[1]);
    ((Ent88 *) arg0)->unk24[2] = func_80277FC4(id, 0, ((Ent88 *) arg0)->unk10, 8, 40, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[2]);
}

void func_802752BC(s16 *arg0) {
    u16 k;
    u16 id;
    f32 x;
    f32 y;
    f32 z;

    id = ((Ent88 *) arg0)->unkE;
    k = ((Ent88 *) arg0)->unk66;
    func_80275120(((Ent88 *) arg0)->x, ((Ent88 *) arg0)->y, ((Ent88 *) arg0)->z, &x, &y, &z);
    if (((Ent88 *) arg0)->unk10 & 0x100) {
        k = 6;
    }
    if (k == 3) {
        ((Ent88 *) arg0)->unk24[0] = func_80277FC4(id, 0, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[0]);
        ((Ent88 *) arg0)->unk24[1] = NULL;
        ((Ent88 *) arg0)->unk24[2] = NULL;
    }
    if (k == 4) {
        ((Ent88 *) arg0)->unk24[0] = func_80277FC4(id, 1, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[0]);
        ((Ent88 *) arg0)->unk24[1] = func_80277FC4(id, 7, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[1]);
        ((Ent88 *) arg0)->unk24[2] = func_80277FC4(id, 8, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[2]);
    }
    if (k >= 5) {
        ((Ent88 *) arg0)->unk24[0] = func_80277FC4(id, 2, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[0]);
        ((Ent88 *) arg0)->unk24[1] = func_80277FC4(id, 7, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[1]);
        ((Ent88 *) arg0)->unk24[2] = func_80277FC4(id, 4, ((Ent88 *) arg0)->unk10, 0, 20, x, y, z, k, (s32) &((Ent88 *) arg0)->unk24[2]);
    }
}

void func_80275120(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    Unk8026DCAC sp28;

    func_8026DCAC(arg0, arg1, arg2, &sp28, 0);
    *arg3 = sp28.i[0];
    if (0.0f != sp28.f[0]) {
        *arg3 += sp28.f[0] / 100.0f;
    }
    if (arg1 < 0.0f) {
        *arg4 = arg1 / 100.0f;
        if (arg1 < -10000.0f) {
            *arg4 = -100.0f;
        }
    } else {
        *arg4 = sp28.i[1];
        if (0.0f != sp28.f[1]) {
            *arg4 += sp28.f[1] / (100.0f * (f32) (s32) func_8026DC74((s32) *arg4));
        }
    }
    *arg5 = sp28.i[2];
    if (0.0f != sp28.f[2]) {
        *arg5 += sp28.f[2] / 100.0f;
    }
}

s32 func_802750C0(s16 *arg0, s16 arg1) {
    s16 i;

    for (i = 0; i < arg1; i++) {
        if (((s32 *) ((u8 *) arg0 + 0x24))[i] != 0) {
            break;
        }
    }
    if (i >= arg1) {
        return 1;
    }
    return 0;
}

void func_80275034(s16 *arg0) {
    s32 v;

    v = (((Ent88 *) arg0)->y <= func_8026E8B8()) ? 1 : 0;
    if (v != 0) {
        func_8027F820(((Ent88 *) arg0)->obj);
        func_802313DC(((Ent88 *) arg0)->obj, 0x0103FFFF);
        func_80239094();
        func_802734BC(((Ent88 *) arg0)->obj);
    }
}

void func_80274FD4(Ent88 *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x10) = (f32) M2C_FIELD(arg0, f32 *, 0x40);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x14) = (f32) M2C_FIELD(arg0, f32 *, 0x44);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x18) = (f32) M2C_FIELD(arg0, f32 *, 0x48);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x28) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x2C) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x30) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
}

void func_80274F8C(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4) {
    func_80273F30(arg0, arg1, arg2, arg3, arg4);
}

s16 func_80274F64(s16 arg0) {
    return *(s16 *)(D_802AFC78 + (arg0 * 0x12));
}

s32 func_80274994(s16 arg0) {
    s32 t;
    s32 spB8;
    s32 padU[1];
    struct { f32 z, y, x; } base;
    struct { f32 z, y, x; } cur;
    s32 pad98;
    Obj8E *obj;

    func_802714C4();
    {
        Ent88 *e;
        Ent88 *n;
        s16 cnt;
        s32 live;

        e = ENT_HEAD;
        n = e->next;
        cnt = *(s16 *)(D_800AEE0E + arg0 * 0xC8);
        while (n != NULL) {
            live = (e->x != 1e7f) ? 1 : 0;
            if (live && e->xf != NULL && arg0 == e->unkE) {
                cnt--;
            }
            e = n;
            n = n->next;
        }
        if (cnt <= 0) {
            return 0;
        }
    }
    if (((arg0 >= 0 && arg0 < 5) ? 0 : 1) ? 0 : SLOTS[arg0].unkC) {
        return 0;
    }
    obj = func_802443F4(arg0);
    func_80271448_inl(obj->unk40->x, obj->unk40->y, obj->unk40->z, &base.x, &base.y, &base.z);
    cur.x = base.x;
    cur.y = base.y;
    cur.z = base.z;
    func_802740AC((s16) func_802704F8(obj->unk40->rot), 1.0f, 0.0f, &cur.x, &cur.z);
    if (func_80273A5C((s32) cur.x, (s32) cur.y, (s32) cur.z) == 0) {
        return 0;
    }
    cur.x = base.x;
    cur.y = base.y;
    cur.z = base.z;
    func_802740AC((s16) func_802704F8(obj->unk40->rot), 0.0f, 1.0f, &cur.x, &cur.z);
    if (func_80273A5C((s32) cur.x, (s32) cur.y, (s32) cur.z) == 0) {
        return 0;
    }
    func_802740AC((s16) func_802704F8(obj->unk40->rot), 1.0f, 1.0f, &base.x, &base.z);
    spB8 = func_8026D7D8((s32) base.x, (s32) base.y, (s32) base.z);
    func_8027404C(base.x, base.y, base.z, &cur.x, &cur.y, &cur.z);
    base.x = func_80234434(obj->unk40->rot) * 100.0f;
    base.y = func_80234408(obj->unk40->rot) * 100.0f;
    if (func_802336E4(base.x)) {
        base.x = 0.0f;
    }
    if (func_802336E4(base.y)) {
        base.y = 0.0f;
    }
    OBJ_DD8->unk40->x = obj->unk40->x + base.x;
    OBJ_DD8->unk40->y = obj->unk40->y + 100.0f;
    OBJ_DD8->unk40->z = obj->unk40->z + base.y;
    cur.y = func_8026E938(OBJ_DD8->unk40);
    t = spB8 & 0xF;
    if (t == 3 || t == 4 || t == 5 || t == 6) {
        cur.y = func_8026E938(OBJ_DD8->unk40);
        if (func_80270FC0(obj) + obj->unk40->y <= cur.y) {
            return 0;
        }
    }
    return 1;
}

void func_802741D8(s16 arg0) {
    s32 spD4;
    struct { f32 z, y, x; } base;
    struct { f32 z, y, x; } cur;
    Ent88 *e;
    Obj8E *obj;
    Obj8E *o;
    s32 pad[3];
    f32 spA0;
    s32 pad1[13];
    s32 sp60[3];
    s32 padA[6];
    f32 sp3C[3];
    Slot30 *slot;
    s32 padC[1];

    func_802714C4();
    if (((arg0 >= 0 && arg0 < 5) ? 0 : 1) ? 0 : SLOTS[arg0].unkC) {
        return;
    }
    obj = func_802443F4(arg0);
    { f32 z = obj->unk40->z;
    func_8026DCAC(obj->unk40->x, obj->unk40->y, z, sp60, 2); }
    base.x = sp60[0];
    base.y = sp60[1];
    base.z = sp60[2];
    cur.x = base.x;
    cur.y = base.y;
    cur.z = base.z;
    func_802740AC((s16) func_802704F8(obj->unk40->rot), 1.0f, 0.0f, &cur.x, &cur.z);
    if (func_80273A5C((s32) cur.x, (s32) cur.y, (s32) cur.z) == 0) {
        return;
    }
    cur.x = base.x;
    cur.y = base.y;
    cur.z = base.z;
    func_802740AC((s16) func_802704F8(obj->unk40->rot), 0.0f, 1.0f, &cur.x, &cur.z);
    if (func_80273A5C((s32) cur.x, (s32) cur.y, (s32) cur.z) == 0) {
        return;
    }
    func_802740AC((s16) func_802704F8(obj->unk40->rot), 1.0f, 1.0f, &base.x, &base.z);
    spD4 = func_8026D7D8((s32) base.x, (s32) base.y, (s32) base.z);
    func_8026E338(base.x, base.y, base.z, sp3C, 0);
    cur.x = sp3C[0];
    cur.y = sp3C[1];
    cur.z = sp3C[2];
    base.x = func_80234434(obj->unk40->rot) * 100.0f;
    base.y = func_80234408(obj->unk40->rot) * 100.0f;
    if (func_802336E4(base.x)) {
        base.x = 0.0f;
    }
    if (func_802336E4(base.y)) {
        base.y = 0.0f;
    }
    OBJ_DD8->unk40->x = obj->unk40->x + base.x;
    OBJ_DD8->unk40->y = obj->unk40->y + 100.0f;
    OBJ_DD8->unk40->z = obj->unk40->z + base.y;
    switch (spD4 & 0xF) {
    case 3:
    case 4:
    case 5:
    case 6:
        cur.y = func_8026E938(OBJ_DD8->unk40);
        if (func_80270FC0(obj) + obj->unk40->y <= cur.y) {
            return;
        }
        if (cur.y < obj->unk40->y) {
            cur.y = obj->unk40->y;
        }
        break;
    default:
        cur.y = obj->unk40->y;
        break;
    }
    e = func_80273F30(*(s16 *)(D_800AEE0A + arg0 * 0xC8), obj->unk40->x + base.x, cur.y, obj->unk40->z + base.y, arg0);
    if (e != NULL) {
        if (func_80232D18(e->obj, 0x10)) {
            func_802734BC(e->obj);
        } else {
            o = (Obj8E *) func_80271540(arg0);
            if (o != NULL) {
                if (func_802716F8(arg0) != NULL) {
                    if (func_8027130C(o)) {
                        slot = &SLOTS[arg0];
                        slot->unk8 = o->unk8;
                        func_80231408(o, 0x10000);
                        func_80232AC8(obj, o);
                        func_80231408(o, 0x200000);
                        if (!((arg0 >= 0 && arg0 < 5) ? 0 : 1)) {
                            slot->unkC = (s32) o;
                        }
                        func_80271010(o, arg0);
                        o->unk40->rot = obj->unk40->rot;
                        spA0 = func_80234434(obj->unk40->rot);
                        base.x = func_80270F44(obj) * spA0;
                        spA0 = func_80234408(obj->unk40->rot);
                        base.y = func_80270F44(obj) * spA0;
                        if (func_802336E4(base.x)) {
                            base.x = 0.0f;
                        }
                        if (func_802336E4(base.y)) {
                            base.y = 0.0f;
                        }
                        o->unk4C = base.x - slot->unk1C;
                        o->unk50 = o->unk40->y - obj->unk40->y;
                        o->unk6C = 1.0f;
                        o->unk54 = base.y - slot->unk24;
                        o->unk70 = 1.6333334f;
                        o->unk40->rot = obj->unk40->rot;
                    }
                }
            } else {
                func_802734BC(e->obj);
            }
        }
    }
}

void func_802740AC(s16 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4) {
    switch (arg0) {
    case 0:
        *arg4 -= arg2;
        return;
    case 4:
        *arg4 += arg2;
        return;
    case 6:
        *arg3 -= arg1;
        return;
    case 2:
        *arg3 += arg1;
        return;
    case 7:
        *arg3 -= arg1;
        *arg4 -= arg2;
        return;
    case 1:
        *arg3 += arg1;
        *arg4 -= arg2;
        return;
    case 5:
        *arg3 -= arg1;
        *arg4 += arg2;
        return;
    case 3:
        *arg3 += arg1;
        *arg4 += arg2;
        /* fallthrough */
    default:
        return;
    }
}

void func_8027404C(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    f32 sp24[3];

    func_8026E338(arg0, arg1, arg2, sp24, 0);
    *arg3 = sp24[0];
    *arg4 = sp24[1];
    *arg5 = sp24[2];
}

void *func_80273F30(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4) {
    f32 x;
    f32 y;
    f32 z;
    s32 bad;
    s32 v;
    s32 r;

    if (D_802AFC70 != 1) {
        D_802AFC70 = 1;
    }
    if (arg4 >= 0 && arg4 < 5) {
        bad = 0;
    } else {
        bad = 1;
    }
    if (bad) {
        v = 0;
    } else {
        v = *(s32 *)(D_802AFCF4 + (arg4 * 0x30));
    }
    if (v != 0) {
        func_80273E2C(arg4);
        return NULL;
    }
    r = func_80273AD4(arg4, arg1, arg2, arg3);
    if (r == 0) {
        return NULL;
    }
    if (r == 2) {
        x = M2C_FIELD(D_802AFE60, f32 *, 0);
        y = M2C_FIELD(D_802AFE60, f32 *, 4);
        z = M2C_FIELD(D_802AFE60, f32 *, 8);
    } else {
        x = arg1;
        y = arg2;
        z = arg3;
    }
    return func_8027361C(arg0, x, y, z, arg4);
}
