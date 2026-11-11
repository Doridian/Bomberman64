/*
 * NON_MATCHING: main_code's 8E730, complete (47 functions,
 * func_80273F30..func_80277E1C). Split from 87D80 by IDO's emission
 * order (text_objects.txt). A first draft from m2c; every function
 * global, emitted in the original's order. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 1739, eu 1739, jp 1739
 *
 * 13 of 47 match. Biggest left: func_802741D8 461, func_8027655C 436,
 * func_80274994 320, func_80276D68 171: m2c's control flow and untyped
 * structs.
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

u16 func_8026D7D8(s32 arg0, s32 arg1, s32 arg2);
u8 func_8026DC74(s32 arg0);
void func_8026DCAC(f32 arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4);
void func_8026E338(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, s32 arg4);
f32 func_8026E8B8(void);
f32 func_8026E938(u8 *arg0);
void *func_802700EC(u8 *arg0, u8 *arg1, s16 arg2, f32 arg3);
void func_802702EC(s16 arg0);
s16 *func_802703B4(u8 *arg0);
f32 func_802704F8(f32 arg0);
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
s32 func_80275DD8(s16 *arg0, s16 *arg1);
void func_80276184(s16 *arg0, u8 *arg1);
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
    f32 sp168;
    f32 sp158;
    u8 *sp154;
    s32 sp38[3];
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv0_10;
    f32 temp_fv0_11;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv0_7;
    f32 temp_fv0_8;
    f32 temp_fv0_9;
    f32 temp_fv1;
    f32 var_fv0;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_a1_3;
    s16 temp_v1_3;
    s16 var_a0;
    s32 *temp_v0;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_4;
    u8 *temp_v1_5;
    u8 *var_v0;

    if (D_802A14B4 == 1) {
        goto block_56;
    }
    if ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 2) != 0) {
        M2C_FIELD(arg0, s16 *, 0x68) = (s16) (M2C_FIELD(arg0, s16 *, 0x68) - 1);
    }
    if (M2C_FIELD(arg0, s16 *, 0x68) < 0xF) {
        if (M2C_FIELD(arg0, s16 *, 0x10) & 0x800) {
            M2C_FIELD(arg0, f32 *, 0x80) = 13.0f;
        } else if ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0x80) != 0) {
            M2C_FIELD(arg0, f32 *, 0x80) = 2.0f;
        } else {
            M2C_FIELD(arg0, f32 *, 0x80) = 1.3f;
        }
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), s32 *, 0xC) = 0xE0;
    temp_a0 = M2C_FIELD(arg0, void **, 0x1C);
    M2C_FIELD(temp_a0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xC) | 0x10);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), s32 *, 0x10) & 0xE0) {
        func_80275948(arg0);
    }
    var_fv0 = 0.0f;
    if ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 4) != 0) {
        var_fv0 = 15.0f;
    }
    sp168 = var_fv0;
    func_80291944(M2C_FIELD(arg0, void **, 0x1C), func_80272024(M2C_FIELD(arg0, s16 *, 0x74)), sp168);
    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(arg0, f32 *, 0x40) = (f32) M2C_FIELD(temp_v1, f32 *, 0x10);
    M2C_FIELD(arg0, f32 *, 0x44) = (f32) M2C_FIELD(temp_v1, f32 *, 0x14);
    M2C_FIELD(arg0, f32 *, 0x48) = (f32) M2C_FIELD(temp_v1, f32 *, 0x18);
    func_802763DC(arg0);
    temp_a1 = M2C_FIELD(arg0, s16 *, 0x64);
    if (((s16) (temp_a1 & 0x200) == 0) && ((s16) (temp_a1 & 0x10) == 0)) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), f32 *, 0x70) = 1.6333334f;
        temp_a0_2 = M2C_FIELD(arg0, void **, 0x1C);
        sp158 = M2C_FIELD(temp_a0_2, f32 *, 0x6C);
        M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0xFFF7);
        func_80230914(temp_a0_2);
        temp_a0_3 = M2C_FIELD(arg0, void **, 0x1C);
        if ((M2C_FIELD(temp_a0_3, f32 *, 0x6C) == 0.0f) && (M2C_FIELD(temp_a0_3, f32 *, 0x68) == 0.0f)) {
            temp_a1_2 = M2C_FIELD(arg0, s16 *, 0x64);
            if ((s16) (temp_a1_2 & 0x800) == 0) {
                M2C_FIELD(arg0, s16 *, 0x64) = (s16) (temp_a1_2 | 8);
                M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(arg0, s16 *, 0x64) | 0x800);
            }
            M2C_FIELD(arg0, f32 *, 0x50) = 0.0f;
            if (sp158 != M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), f32 *, 0x6C)) {
                M2C_FIELD(arg0, void **, 0x30) = M2C_FIELD(arg0, void **, 0x1C);
            }
        } else {
            M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(arg0, s16 *, 0x64) | 8);
            M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0xF7FF);
        }
        temp_v1_2 = M2C_FIELD(arg0, void **, 0x20);
        M2C_FIELD(arg0, f32 *, 0x40) = (f32) M2C_FIELD(temp_v1_2, f32 *, 0x10);
        M2C_FIELD(arg0, f32 *, 0x44) = (f32) M2C_FIELD(temp_v1_2, f32 *, 0x14);
        M2C_FIELD(arg0, f32 *, 0x48) = (f32) M2C_FIELD(temp_v1_2, f32 *, 0x18);
    }
    temp_v1_3 = M2C_FIELD(arg0, s16 *, 0x64) & 0x10;
    if ((temp_v1_3 == 0) && ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0x200) == 0)) {
        if ((func_802909FC((s32) M2C_FIELD(arg0, void **, 0x1C)) != 0) && (func_8023369C(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x10), M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), f32 *, 0x58), 1.0f) != 0) && (func_8023369C(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x18), M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), f32 *, 0x60), 1.0f) != 0) && ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 4) != 0)) {
            func_802712C4(arg0);
        }
        var_a0 = M2C_FIELD(arg0, s16 *, 0x64) & 4;
    } else if (temp_v1_3 != 0) {
        func_802733C8(M2C_FIELD(arg0, void **, 0x1C));
        var_a0 = M2C_FIELD(arg0, s16 *, 0x64) & 4;
    } else {
        func_802727D8(M2C_FIELD(arg0, s32 **, 0x38));
        var_a0 = M2C_FIELD(arg0, s16 *, 0x64) & 4;
    }
    temp_v1_4 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(arg0, f32 *, 0x40) = (f32) M2C_FIELD(temp_v1_4, f32 *, 0x10);
    M2C_FIELD(arg0, f32 *, 0x44) = (f32) M2C_FIELD(temp_v1_4, f32 *, 0x14);
    M2C_FIELD(arg0, f32 *, 0x48) = (f32) M2C_FIELD(temp_v1_4, f32 *, 0x18);
    if ((var_a0 != 0) || ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 8) != 0)) {
        func_802714C4();
        temp_fv0 = M2C_FIELD(arg0, f32 *, 0x40);
        M2C_FIELD(D_802AFDD8, f32 *, 0x58) = temp_fv0;
        M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x10) = temp_fv0;
        temp_fv0_2 = M2C_FIELD(arg0, f32 *, 0x44);
        M2C_FIELD(D_802AFDD8, f32 *, 0x5C) = temp_fv0_2;
        M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x14) = temp_fv0_2;
        temp_fv0_3 = M2C_FIELD(arg0, f32 *, 0x48);
        M2C_FIELD(D_802AFDD8, f32 *, 0x60) = temp_fv0_3;
        M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x18) = temp_fv0_3;
        M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x30) = 1.0f;
        temp_v1_5 = M2C_FIELD(D_802AFDD8, void **, 0x40);
        temp_fv0_4 = M2C_FIELD(temp_v1_5, f32 *, 0x30);
        M2C_FIELD(temp_v1_5, f32 *, 0x2C) = temp_fv0_4;
        M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x28) = temp_fv0_4;
        M2C_FIELD(D_802AFDD8, s32 *, 0x30) = 1;
        M2C_FIELD(D_802AFDD8, f32 *, 0x34) = 40.0f;
        M2C_FIELD(D_802AFDD8, f32 *, 0x38) = 40.0f;
        if (((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0x400) == 0) && (func_80232D18(D_802AFDD8, 1) == 0)) {
            M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(arg0, s16 *, 0x64) | 0x400);
        }
        if ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0x400) != 0) {
            var_v0 = func_802308B8(M2C_FIELD(arg0, void **, 0x1C), 0x16);
        } else {
            var_v0 = func_8022F4AC((s32) M2C_FIELD(arg0, void **, 0x1C), 0x16, func_802443F4((s32) M2C_FIELD(arg0, s16 *, 0xE)));
        }
        sp154 = var_v0;
        if (var_v0 != NULL) {
            temp_fv0_5 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), f32 *, 0x58);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x10) = temp_fv0_5;
            M2C_FIELD(arg0, f32 *, 0x40) = temp_fv0_5;
            temp_fv0_6 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), f32 *, 0x5C);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x14) = temp_fv0_6;
            M2C_FIELD(arg0, f32 *, 0x44) = temp_fv0_6;
            temp_fv0_7 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), f32 *, 0x60);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x18) = temp_fv0_7;
            M2C_FIELD(arg0, f32 *, 0x48) = temp_fv0_7;
            func_80276184(arg0, sp154);
            func_802712C4(arg0);
            if ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 8) != 0) {
                temp_v0 = func_802700EC(M2C_FIELD(arg0, void **, 0x1C), sp154, func_80272024(M2C_FIELD(arg0, s16 *, 0x74)), sp168);
                M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(arg0, s16 *, 0x64) | 0x200);
                M2C_FIELD(arg0, s32 **, 0x38) = temp_v0;
                M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0xFFF7);
            }
            temp_fv0_8 = M2C_FIELD(arg0, f32 *, 0x40);
            M2C_FIELD(D_802AFDD8, f32 *, 0x58) = temp_fv0_8;
            M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x10) = temp_fv0_8;
            temp_fv0_9 = M2C_FIELD(arg0, f32 *, 0x44);
            M2C_FIELD(D_802AFDD8, f32 *, 0x5C) = temp_fv0_9;
            M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x14) = temp_fv0_9;
            temp_fv0_10 = M2C_FIELD(arg0, f32 *, 0x48);
            M2C_FIELD(D_802AFDD8, f32 *, 0x60) = temp_fv0_10;
            M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x18) = temp_fv0_10;
            if (((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0x400) != 0) && (func_80232D18(D_802AFDD8, 1) != 0)) {
                M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0xFBFF);
            }
        }
    }
    temp_a1_3 = M2C_FIELD(arg0, s16 *, 0x64);
    if ((s16) (temp_a1_3 & 0x40) != 0) {
        M2C_FIELD(arg0, s16 *, 0x64) = (s16) (temp_a1_3 | 1);
    }
    if ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 1) != 0) {
        func_80275948(arg0);
        return 1;
    }
    func_8026DCAC(M2C_FIELD(arg0, f32 *, 0x40), M2C_FIELD(arg0, f32 *, 0x44), M2C_FIELD(arg0, f32 *, 0x48), sp38, 2);
    temp_fv0_11 = (f32) sp38[0];
    temp_fv1 = (f32) sp38[1];
    temp_fa0 = (f32) sp38[2];
    if ((func_8026D7D8((s32) temp_fv0_11, (s32) temp_fv1, (s32) temp_fa0) & 0xF) == 9) {
        func_80275948(arg0);
    }
    func_80275034(arg0);
block_56:
    return 0;
}

void func_802763DC(s16 *arg0) {
    s32 sp30[3];
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_t0;
    u8 *temp_v0;
    u8 *temp_v0_2;

    if ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0x10) == 0) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x10) = (f32) M2C_FIELD(arg0, f32 *, 0x40);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x14) = (f32) M2C_FIELD(arg0, f32 *, 0x44);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), f32 *, 0x18) = (f32) M2C_FIELD(arg0, f32 *, 0x48);
        temp_v0 = M2C_FIELD(arg0, void **, 0x20);
        func_8026DCAC(M2C_FIELD(temp_v0, f32 *, 0x10), M2C_FIELD(temp_v0, f32 *, 0x14), M2C_FIELD(temp_v0, f32 *, 0x18), sp30, 2);
        temp_fv0 = (f32) sp30[0];
        temp_fv1 = (f32) sp30[1];
        temp_fa0 = (f32) sp30[2];
        temp_t0 = func_8026D7D8((s32) temp_fv0, (s32) temp_fv1, (s32) temp_fa0) & 0x1C00;
        if (temp_t0 != 0) {
            func_8027F858(M2C_FIELD(arg0, s32 *, 0x1C), temp_t0 >> 0xA);
        }
        temp_v0_2 = M2C_FIELD(arg0, void **, 0x20);
        M2C_FIELD(arg0, f32 *, 0x40) = (f32) M2C_FIELD(temp_v0_2, f32 *, 0x10);
        M2C_FIELD(arg0, f32 *, 0x44) = (f32) M2C_FIELD(temp_v0_2, f32 *, 0x14);
        M2C_FIELD(arg0, f32 *, 0x48) = (f32) M2C_FIELD(temp_v0_2, f32 *, 0x18);
    }
}

void func_80276184(s16 *arg0, u8 *arg1) {
    s16 *sp24;
    s16 *temp_a3;
    s16 temp_v1;
    s32 temp_v0;
    s32 temp_v0_5;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_6;

    if ((s32) arg1 != (s32) NULL) {
        temp_v0 = M2C_FIELD(arg1, s32 *, 8);
        if ((temp_v0 & 0x14) && !(temp_v0 & 0x8002)) {
            func_80275C08(arg1, M2C_FIELD(arg0, void **, 0x1C));
            func_802712C4(arg0);
            temp_v0_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), void **, 0x40);
            func_8026C51C(0x22, M2C_FIELD(temp_v0_2, f32 *, 0x10), M2C_FIELD(temp_v0_2, f32 *, 0x14), M2C_FIELD(temp_v0_2, f32 *, 0x18));
        }
    }
    if (((s32) arg1 != (s32) NULL) && (M2C_FIELD(arg1, s32 *, 8) & 4) && ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 0x80) != 0)) {
        M2C_FIELD(arg0, s16 *, 0x74) = 9;
    }
    if (((s32) arg1 != (s32) NULL) && (M2C_FIELD(arg1, s32 *, 8) & 0x8000)) {
        M2C_FIELD(arg0, s16 *, 0x74) = func_8027241C(M2C_FIELD(arg0, s16 *, 0x74));
        func_80275C08(arg1, M2C_FIELD(arg0, void **, 0x1C));
        if (M2C_FIELD(arg1, s32 *, 8) & 4) {
            temp_v0_3 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), void **, 0x40);
            func_8026C51C(0x22, M2C_FIELD(temp_v0_3, f32 *, 0x10), M2C_FIELD(temp_v0_3, f32 *, 0x14), M2C_FIELD(temp_v0_3, f32 *, 0x18));
        } else {
            temp_v0_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), void **, 0x40);
            func_8026C51C(0x23, M2C_FIELD(temp_v0_4, f32 *, 0x10), M2C_FIELD(temp_v0_4, f32 *, 0x14), M2C_FIELD(temp_v0_4, f32 *, 0x18));
        }
    }
    if ((s32) arg1 != (s32) NULL) {
        temp_v0_5 = M2C_FIELD(arg1, s32 *, 8);
        if (temp_v0_5 & 2) {
            if (!(temp_v0_5 & 0x8000)) {
                temp_a3 = func_802703B4(arg1);
                if ((s16) (M2C_FIELD(arg0, s16 *, 0x64) & 4) != 0) {
                    temp_v1 = M2C_FIELD(temp_a3, s16 *, 0x64);
                    if ((s16) (temp_v1 & 4) == 0) {
                        if ((s16) (temp_v1 & 0x200) != 0) {
                            sp24 = temp_a3;
                            func_80271F74(M2C_FIELD(temp_a3, s32 **, 0x38));
                        }
                        sp24 = temp_a3;
                        if (func_80275DD8(arg0, temp_a3) != 0) {
                            func_80275C7C(M2C_FIELD(arg0, s16 *, 0xE), M2C_FIELD(temp_a3, void **, 0x1C), M2C_FIELD(arg0, s16 *, 0x74));
                        }
                    } else {
                        func_802712C4(temp_a3);
                    }
                    temp_v0_6 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), void **, 0x40);
                    func_8026C51C(0x23, M2C_FIELD(temp_v0_6, f32 *, 0x10), M2C_FIELD(temp_v0_6, f32 *, 0x14), M2C_FIELD(temp_v0_6, f32 *, 0x18));
                    func_80275C08(arg1, M2C_FIELD(arg0, void **, 0x1C));
                }
            }
        }
    }
}

s32 func_80275DD8(s16 *arg0, s16 *arg1) {
    f32 sp14;
    f32 spC;
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
    s16 var_a2;
    s32 var_v0;
    s32 var_v1;
    u16 temp_t2;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), void **, 0x40);
    temp_v1 = M2C_FIELD(M2C_FIELD(arg1, void **, 0x1C), void **, 0x40);
    temp_fa1 = M2C_FIELD(temp_v0, f32 *, 0x10);
    temp_ft4 = M2C_FIELD(temp_v1, f32 *, 0x10);
    temp_fv1 = M2C_FIELD(temp_v0, f32 *, 0x18);
    temp_fa0 = M2C_FIELD(temp_v1, f32 *, 0x18);
    var_a2 = 0;
    if (temp_ft4 <= temp_fa1) {
        var_a2 = 4;
    }
    if (temp_fv1 < temp_fa0) {
        var_a2 += 2;
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
            var_fv1 = -(var_ft4_2 - -temp_fa0);
        } else {
            var_fv1 = -(var_ft4_2 - temp_fa0);
        }
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
        var_a2 += 1;
    }
    temp_t2 = M2C_FIELD(arg0, u16 *, 0x74);
    var_v1 = 0;
    switch (temp_t2) {
    case 0:
        if ((var_a2 == 0) || (var_a2 == 1) || (var_a2 == 4) || (var_v0 = 0, (var_a2 == 5))) {
block_88:
            var_v1 = 1;
        default:
            var_v0 = var_v1;
        }
        break;
    case 1:
        if ((var_a2 == 0) || (var_a2 == 1) || (var_a2 == 3) || (var_v0 = 0, (var_a2 == 4))) {
            goto block_88;
        }
        break;
    case 2:
        if ((var_a2 == 0) || (var_a2 == 1) || (var_a2 == 2) || (var_v0 = 0, (var_a2 == 3))) {
            goto block_88;
        }
        break;
    case 3:
        if ((var_a2 == 1) || (var_a2 == 2) || (var_a2 == 3) || (var_v0 = 0, (var_a2 == 6))) {
            goto block_88;
        }
        break;
    case 4:
        if ((var_a2 == 2) || (var_a2 == 3) || (var_a2 == 6) || (var_v0 = 0, (var_a2 == 7))) {
            goto block_88;
        }
        break;
    case 5:
        if ((var_a2 == 2) || (var_a2 == 5) || (var_a2 == 6) || (var_v0 = 0, (var_a2 == 7))) {
            goto block_88;
        }
        break;
    case 6:
        if ((var_a2 == 4) || (var_a2 == 5) || (var_a2 == 6) || (var_v0 = 0, (var_a2 == 7))) {
            goto block_88;
        }
        break;
    case 7:
        if ((var_a2 == 0) || (var_a2 == 4) || (var_a2 == 5) || (var_v0 = 0, (var_a2 == 7))) {
            goto block_88;
        }
        break;
    }
    return var_v0;
}

void func_80275C7C(s16 arg0, u8 *arg1, s16 arg2) {
    s16 *temp_a0_2;
    s16 *temp_v0;
    s16 temp_a1;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_v1;
    s32 *temp_a0;
    s32 var_at;
    s32 var_t9;
    u8 *temp_a3;

    temp_v0 = func_802703B4(arg1);
    if ((temp_v0 != NULL) && (temp_v1 = M2C_FIELD(temp_v0, s16 *, 0x64), ((s16) (temp_v1 & 0x10) == 0))) {
        if ((s16) (temp_v1 & 0x200) != 0) {
            M2C_FIELD(temp_v0, s16 *, 0x64) = (s16) (temp_v1 & 0xFDFF);
            func_802313DC(M2C_FIELD(temp_v0, void **, 0x1C), 0x20000);
            temp_a0 = M2C_FIELD(temp_v0, s32 **, 0x38);
            func_80270A80(temp_a0);
            free(temp_a0);
        }
        var_v1 = 0;
        if (!(M2C_FIELD(temp_v0, s16 *, 0x10) & 0x100)) {
            temp_a1 = M2C_FIELD(temp_v0, s16 *, 0);
            temp_a3 = (arg0 * 0x12) + D_802AFC78;
            var_t9 = 0 * 2;
loop_6:
            temp_a0_2 = temp_a3 + var_t9;
            temp_v0_2 = *temp_a0_2;
            if ((temp_a1 != temp_v0_2) || (arg2 != M2C_FIELD(temp_v0, s16 *, 0x74))) {
                var_at = var_v1 < 8;
                if (temp_a1 != temp_v0_2) {
                    if (temp_v0_2 == -1) {
                        *temp_a0_2 = temp_a1;
                        goto block_12;
                    }
                    var_v1 += 1;
                    var_t9 = var_v1 * 2;
                    if (var_v1 >= 8) {
block_12:
                        var_at = var_v1 < 8;
                        goto block_13;
                    }
                    goto loop_6;
                }
block_13:
                if (var_at != 0) {
                    M2C_FIELD((temp_a3 + (var_v1 * 2)), s16 *, 2) = -1;
                    M2C_FIELD(temp_v0, s16 *, 0xE) = arg0;
                    M2C_FIELD(temp_v0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_v0, s16 *, 0x64) | 4);
                    M2C_FIELD(temp_v0, s16 *, 0x74) = arg2;
                }
            }
        }
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
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    s32 sp28;
    s16 temp_a0;
    s16 temp_t1;
    s16 temp_v0;
    s16 temp_v1;
    s16 var_s0;
    s32 *temp_a0_2;
    s32 *temp_s0;
    s32 temp_t8;
    s32 temp_t9;
    s32 var_s0_2;
    s32 var_v1;

    func_80270BA4(M2C_FIELD(arg0, void **, 0x1C));
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x64);
    if ((s16) (temp_v1 & 0x200) != 0) {
        M2C_FIELD(arg0, s16 *, 0x64) = (s16) (temp_v1 & 0xFDFF);
        func_802313DC(M2C_FIELD(arg0, void **, 0x1C), 0x20000);
        temp_s0 = M2C_FIELD(arg0, s32 **, 0x38);
        func_80270A80(temp_s0);
        free(temp_s0);
    }
    temp_t9 = M2C_FIELD(arg0, s16 *, 0x10) & ~0xC02;
    switch (temp_t9) {                              /* switch 1; irregular */
    case 0x200:                                     /* switch 1 */
        func_802752BC(arg0);
block_16:
        var_s0 = 3;
        break;
    case 0x201:                                     /* switch 1 */
    case 0x204:                                     /* switch 1 */
    case 0x205:                                     /* switch 1 */
        func_802757E0(arg0);
        goto block_16;
    case 0x300:                                     /* switch 1 */
        func_802756DC(arg0);
        var_s0 = 2;
        break;
    case 0x301:                                     /* switch 1 */
    case 0x304:                                     /* switch 1 */
    case 0x305:                                     /* switch 1 */
        func_80275590(arg0);
        goto block_16;
    default:                                        /* switch 1 */
        func_802752BC(arg0);
        goto block_16;
    }
    sp5C = M2C_FIELD(arg0, f32 *, 0x40);
    sp58 = M2C_FIELD(arg0, f32 *, 0x44);
    sp54 = M2C_FIELD(arg0, f32 *, 0x48);
    func_80273414(arg0);
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x10);
    var_v1 = 0xB;
    M2C_FIELD(arg0, f32 *, 0x48) = 1e7f;
    M2C_FIELD(arg0, f32 *, 0x44) = 1e7f;
    M2C_FIELD(arg0, f32 *, 0x40) = 1e7f;
    if (temp_a0 & 1) {
        temp_t1 = M2C_FIELD(arg0, s16 *, 0x66);
        switch (temp_t1) {                          /* switch 2 */
        case 3:                                     /* switch 2 */
            var_v1 = 0xF;
            break;
        case 4:                                     /* switch 2 */
            var_v1 = 0x10;
            break;
        case 5:                                     /* switch 2 */
            var_v1 = 0x11;
            break;
        case 6:                                     /* switch 2 */
            var_v1 = 0x12;
            break;
        case 7:                                     /* switch 2 */
            var_v1 = 0x13;
            break;
        case 8:                                     /* switch 2 */
            var_v1 = 0x14;
            break;
        case 9:                                     /* switch 2 */
            var_v1 = 0x15;
            break;
        }
        if (temp_a0 & 0x100) {
            var_v1 = 0x15;
        }
    } else {
        temp_v0 = M2C_FIELD(arg0, s16 *, 0x66);
        switch (temp_v0) {                          /* switch 3; irregular */
        case 3:                                     /* switch 3 */
            break;
        case 4:                                     /* switch 3 */
            var_v1 = 0xC;
            break;
        case 5:                                     /* switch 3 */
            var_v1 = 0xD;
            break;
        }
        if (temp_a0 & 0x100) {
            var_v1 = 0xE;
        }
    }
    func_8026C51C(var_v1, sp5C, sp58, sp54);
    sp28 = (s32) var_s0;
loop_39:
    if (func_802750C0(arg0, (s16) sp28) == 0) {
        var_s0_2 = 0;
        if (var_s0 > 0) {
            do {
                temp_a0_2 = M2C_FIELD(((u8 *)arg0 + (var_s0_2 * 4)), s32 **, 0x24);
                if (temp_a0_2 != NULL) {
                    func_80278D54(temp_a0_2);
                }
                temp_t8 = (var_s0_2 + 1) & 0xFFFF;
                var_s0_2 = temp_t8;
            } while (temp_t8 < var_s0);
        }
        func_80239094();
        goto loop_39;
    }
    func_802733F8(arg0);
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    func_80238EA8(M2C_FIELD(arg0, s32 *, 4));
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
    s32 spB8;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    s32 sp48[3];
    f32 sp24[3];
    f32 temp_ft0;
    f32 temp_ft2;
    f32 temp_ft4;
    s16 *var_a0;
    s16 *var_v1;
    s16 var_a1;
    s32 temp_t2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    u8 *temp_v0;
    u8 *temp_v1;

    func_802714C4();
    var_v1 = D_8008F44C;
    var_a0 = M2C_FIELD(var_v1, s16 **, 0x14);
    var_a1 = *(s16 *)(D_800AEE0E + (arg0 * 0xC8));
    if (var_a0 != NULL) {
        do {
            var_v0_2 = 0;
            if (M2C_FIELD(var_v1, f32 *, 0x40) != 1e7f) {
                var_v0_2 = 1;
            }
            if ((var_v0_2 != 0) && (M2C_FIELD(var_v1, s32 *, 0x20) != 0)) {
                var_v1 = var_a0;
                if (arg0 == M2C_FIELD(var_v1, s16 *, 0xE)) {
                    var_a1 -= 1;
                    goto block_8;
                }
            } else {
block_8:
                var_v1 = var_a0;
            }
            var_a0 = M2C_FIELD(var_a0, s16 **, 0x14);
        } while (var_a0 != NULL);
    }
    if (var_a1 <= 0) {
        return 0;
    }
    if (arg0 >= 0) {
        var_v0_3 = 1;
        if (arg0 < 5) {
            var_v0_3 = 0;
        }
    } else {
        var_v0_3 = 1;
    }
    if (var_v0_3 != 0) {
        var_v0_4 = 0;
    } else {
        var_v0_4 = *(s32 *)(D_802AFCF4 + (arg0 * 0x30));
    }
    if (var_v0_4 != 0) {
        return 0;
    }
    temp_v0 = func_802443F4((s32) arg0);
    temp_v1 = M2C_FIELD(temp_v0, void **, 0x40);
    func_8026DCAC(M2C_FIELD(temp_v1, f32 *, 0x10), M2C_FIELD(temp_v1, f32 *, 0x14), M2C_FIELD(temp_v1, f32 *, 0x18), sp48, 2);
    temp_ft2 = (f32) sp48[0];
    temp_ft4 = (f32) sp48[1];
    spB0 = temp_ft2;
    spA4 = temp_ft2;
    temp_ft0 = (f32) sp48[2];
    spAC = temp_ft4;
    spA0 = temp_ft4;
    spA8 = temp_ft0;
    sp9C = temp_ft0;
    func_802740AC(M2C_BITWISE(s16, func_802704F8(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20))), 1.0f, 0.0f, &spA4, &sp9C);
    if (func_80273A5C((s32) spA4, (s32) spA0, (s32) sp9C) == 0) {
        return 0;
    }
    spA4 = spB0;
    spA0 = spAC;
    sp9C = spA8;
    func_802740AC(M2C_BITWISE(s16, func_802704F8(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20))), 0.0f, 1.0f, &spA4, &sp9C);
    if (func_80273A5C((s32) spA4, (s32) spA0, (s32) sp9C) == 0) {
        return 0;
    }
    func_802740AC(M2C_BITWISE(s16, func_802704F8(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20))), 1.0f, 1.0f, &spB0, &spA8);
    spB8 = func_8026D7D8((s32) spB0, (s32) spAC, (s32) spA8);
    func_8026E338(spB0, spAC, spA8, sp24, 0);
    spA4 = sp24[0];
    spA0 = sp24[1];
    sp9C = sp24[2];
    spB0 = func_80234434(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20)) * 100.0f;
    spAC = func_80234408(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20)) * 100.0f;
    if (func_802336E4(spB0) != 0) {
        spB0 = 0.0f;
    }
    if (func_802336E4(spAC) != 0) {
        spAC = 0.0f;
    }
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x10) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) + spB0);
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x14) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) + 100.0f);
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x18) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) + spAC);
    temp_t2 = spB8 & 0xF;
    spA0 = func_8026E938(M2C_FIELD(D_802AFDD8, void **, 0x40));
    if ((temp_t2 == 3) || (temp_t2 == 4) || (temp_t2 == 5) || (var_v0 = 1, (temp_t2 == 6))) {
        spA0 = func_8026E938(M2C_FIELD(D_802AFDD8, void **, 0x40));
        var_v0 = 1;
        if ((func_80270FC0(temp_v0) + M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14)) <= spA0) {
            var_v0 = 0;
        }
    }
    return var_v0;
}

void func_802741D8(s16 arg0) {
    s32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spA0;
    s32 sp60[3];
    f32 sp3C[3];
    f32 temp_ft1;
    f32 temp_ft3;
    f32 temp_ft5;
    f32 temp_fv1;
    s32 temp_t9;
    s32 temp_v0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_4;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v1;
    u8 *var_v0_3;

    func_802714C4();
    var_v0 = 1;
    if ((arg0 >= 0) && (arg0 < 5)) {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        var_v0_2 = 0;
    } else {
        var_v0_2 = *(s32 *)(D_802AFCF4 + (arg0 * 0x30));
    }
    if (var_v0_2 == 0) {
        temp_v0 = func_802443F4((s32) arg0);
        temp_v1 = M2C_FIELD(temp_v0, void **, 0x40);
        func_8026DCAC(M2C_FIELD(temp_v1, f32 *, 0x10), M2C_FIELD(temp_v1, f32 *, 0x14), M2C_FIELD(temp_v1, f32 *, 0x18), sp60, 2);
        temp_ft1 = (f32) sp60[0];
        temp_ft3 = (f32) sp60[1];
        spD0 = temp_ft1;
        spC4 = temp_ft1;
        temp_ft5 = (f32) sp60[2];
        spCC = temp_ft3;
        spC0 = temp_ft3;
        spC8 = temp_ft5;
        spBC = temp_ft5;
        func_802740AC(M2C_BITWISE(s16, func_802704F8(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20))), 1.0f, 0.0f, &spC4, &spBC);
        if (func_80273A5C((s32) spC4, (s32) spC0, (s32) spBC) != 0) {
            spC4 = spD0;
            spC0 = spCC;
            spBC = spC8;
            func_802740AC(M2C_BITWISE(s16, func_802704F8(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20))), 0.0f, 1.0f, &spC4, &spBC);
            if (func_80273A5C((s32) spC4, (s32) spC0, (s32) spBC) != 0) {
                func_802740AC(M2C_BITWISE(s16, func_802704F8(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20))), 1.0f, 1.0f, &spD0, &spC8);
                spD4 = func_8026D7D8((s32) spD0, (s32) spCC, (s32) spC8);
                func_8026E338(spD0, spCC, spC8, sp3C, 0);
                spC4 = sp3C[0];
                spC0 = sp3C[1];
                spBC = sp3C[2];
                spD0 = func_80234434(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20)) * 100.0f;
                spCC = func_80234408(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20)) * 100.0f;
                if (func_802336E4(spD0) != 0) {
                    spD0 = 0.0f;
                }
                if (func_802336E4(spCC) != 0) {
                    spCC = 0.0f;
                }
                M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x10) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) + spD0);
                M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x14) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) + 100.0f);
                M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x18) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) + spCC);
                temp_t9 = spD4 & 0xF;
                if ((temp_t9 != 3) && (temp_t9 != 4) && (temp_t9 != 5) && (temp_t9 != 6)) {
                    spC0 = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14);
                    var_v0_3 = M2C_FIELD(temp_v0, void **, 0x40);
                    goto block_21;
                }
                spC0 = func_8026E938(M2C_FIELD(D_802AFDD8, void **, 0x40));
                var_v0_3 = M2C_FIELD(temp_v0, void **, 0x40);
                temp_fv1 = M2C_FIELD(var_v0_3, f32 *, 0x14);
                if (!((func_80270FC0(temp_v0) + temp_fv1) <= spC0)) {
                    if (spC0 < temp_fv1) {
                        spC0 = temp_fv1;
                        var_v0_3 = M2C_FIELD(temp_v0, void **, 0x40);
                    }
block_21:
                    temp_v0_2 = func_80273F30(*(s16 *)(D_800AEE0A + (arg0 * 0xC8)), M2C_FIELD(var_v0_3, f32 *, 0x10) + spD0, spC0, M2C_FIELD(var_v0_3, f32 *, 0x18) + spCC, (s16) (s32) arg0);
                    if (temp_v0_2 != NULL) {
                        if (func_80232D18(M2C_FIELD(temp_v0_2, void **, 0x1C), 0x10) != 0) {
                            func_802734BC(M2C_FIELD(temp_v0_2, void **, 0x1C));
                        } else {
                            temp_v0_3 = func_80271540(arg0);
                            if (temp_v0_3 != 0) {
                                if (func_802716F8(arg0) != NULL) {
                                    if (func_8027130C((void *) temp_v0_3) != 0) {
                                        temp_v0_4 = (arg0 * 0x30) + D_802AFCE8;
                                        M2C_FIELD(temp_v0_4, s32 *, 8) = (s32) M2C_FIELD(temp_v0_3, s32 *, 8);
                                        func_80231408((void *) temp_v0_3, 0x10000);
                                        func_80232AC8((s32) temp_v0, temp_v0_3);
                                        func_80231408((void *) temp_v0_3, 0x200000);
                                        if (arg0 >= 0) {
                                            var_v0_4 = 1;
                                            if (arg0 < 5) {
                                                var_v0_4 = 0;
                                            }
                                        } else {
                                            var_v0_4 = 1;
                                        }
                                        if (var_v0_4 == 0) {
                                        }
                                        func_80271010((void *) temp_v0_3, arg0);
                                        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20);
                                        spA0 = func_80234434(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20));
                                        spD0 = func_80270F44(temp_v0) * spA0;
                                        spA0 = func_80234408(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20));
                                        spCC = func_80270F44(temp_v0) * spA0;
                                        if (func_802336E4(spD0) != 0) {
                                            spD0 = 0.0f;
                                        }
                                        if (func_802336E4(spCC) != 0) {
                                            spCC = 0.0f;
                                        }
                                        temp_v0_5 = M2C_FIELD(temp_v0_3, void **, 0x40);
                                        M2C_FIELD(temp_v0_3, f32 *, 0x4C) = (f32) (spD0 - M2C_FIELD(temp_v0_4, f32 *, 0x1C));
                                        M2C_FIELD(temp_v0_3, f32 *, 0x50) = (f32) (M2C_FIELD(temp_v0_5, f32 *, 0x14) - M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14));
                                        M2C_FIELD(temp_v0_3, f32 *, 0x6C) = 1.0f;
                                        M2C_FIELD(temp_v0_3, f32 *, 0x54) = (f32) (spCC - M2C_FIELD(temp_v0_4, f32 *, 0x24));
                                        M2C_FIELD(temp_v0_3, f32 *, 0x70) = 1.6333334f;
                                        M2C_FIELD(temp_v0_5, f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20);
                                    }
                                }
                            } else {
                                func_802734BC(M2C_FIELD(temp_v0_2, void **, 0x1C));
                            }
                        }
                    }
                }
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
