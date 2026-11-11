/*
 * NON_MATCHING: main_code's 87D80, complete (97 functions,
 * func_8026D580..func_80273F0C): the stage map D_800B15D8 (layers of
 * 0x82-byte cells of 64 attribute halfwords), the attribute queries
 * (func_8026D7D8, func_8026DCAC, func_8026E3AC) and the objects on it.
 * A first draft from m2c; every function global, emitted in the
 * original's order. Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 4014, eu 4014, jp 4014
 *
 * 33 of 97 match. func_8026D5F8 and func_8026D5C0 (cell and slot of a
 * point) are inlined by func_8026D620/func_8026D7D8, which is what the
 * original's register copies show. The map reads as D_800B15D8->unkN,
 * not D_800B15D8[0].unkN (the latter swaps the multiply's registers).
 * func_8026F5E8 and func_8026E3AC keep their x/y/z in an f32[3] (the
 * original's dead stores to it), not in three variables.
 * Biggest left: func_802727D8 475, func_8026F068 354, func_802716F8 270,
 * func_8027361C 264, func_80271BB8 232: m2c's control flow and untyped
 * object pointers (D_802AFDD8, the 0xC8-stride D_800AEDF0, the
 * 0x30-stride D_802AFCE8).
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

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u16 unk2[64];
} UnkCell_800B15D8; /* size 0x82 */

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ UnkCell_800B15D8 unk12[23];
    /* 0xBC0 */ u8 unkBC0[0x74];
} UnkStruct_800B15D8; /* size 0xC34 */

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

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x1C - 0x12];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
} Slot30; /* size 0x30 */

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ Obj8E *obj;
    /* 0x08 */ Obj8E *unk8;
    /* 0x0C */ Obj8E *unkC;
    /* 0x10 */ s32 flags;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} Ctl87;

#define SLOTS ((Slot30 *) D_802AFCE8)

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
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 pad2C[0xC8 - 0x2C];
} Player87; /* size 0xC8 */

#define ENT_HEAD (*(Ent88 **) &D_8008F44C)
#define PLAYERS ((Player87 *) D_800AEDF0)
#define OBJ_DD8 (*(Obj8E **) &D_802AFDD8)
#define VEC_E60 ((f32 *) D_802AFE60)

extern Node87 D_802AFDE0;
extern Node87 D_802AFE58;

void free(void *);
void func_8022638C(u32, void *);
void func_802297B8(s32, s32, s32, s32);
s32 func_8022984C(void *, s32);
f32 func_8022DF68(f32 *, f32 *);
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
s32 func_802870A8();
s32 func_80287440(void);
s32 func_802875B0();
s32 func_8028A4E0(s32);
s32 func_8028A81C(s32, f32, f32, f32, s32);
s32 func_802909FC(void *, void *);
void func_80277378();
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
extern UnkStruct_800B15D8 D_800B15D8[];
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

void func_8026D580(void);
void func_8026D5B4(s32 arg0);
s32 func_8026D5C0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8026D5F8(s32 arg0, s32 arg1, s32 arg2);
void func_8026D620(s32 arg0, s32 arg1, s32 arg2, u16 arg3);
void func_8026D6C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
u16 func_8026D7D8(s32 arg0, s32 arg1, s32 arg2);
void func_8026D92C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_8026DA1C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8026DA2C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_8026DB88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
u8 func_8026DC74(s32 arg0);
void func_8026DCAC(f32 arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4);
void func_8026DF74(f32 arg0, f32 arg1, f32 arg2);
void func_8026DFB8(f32 arg0, f32 arg1, f32 arg2, f32 *arg3);
s32 func_8026E278(s32 arg0);
f32 func_8026E2B0(s32 arg0);
void func_8026E338(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, s32 arg4);
f32 func_8026E3AC(f32 arg0, f32 arg1, f32 arg2);
s32 func_8026E5CC(s32 arg0);
s32 func_8026E608(s32 arg0, s32 arg1);
void func_8026E6E4(u8 *arg0, f32 *arg1, f32 *arg2);
f32 func_8026E8B8(void);
s32 func_8026E8C8(void);
s32 func_8026E8E0(s32 arg0);
f32 func_8026E938(u8 *arg0);
f32 func_8026EAF8(u8 *arg0);
void func_8026ECC0(void);
void func_8026ECE8(f32 arg0);
void func_8026ECF4(void);
void func_8026EE08(s32 arg0);
void func_8026EE10(s32 arg0);
u8 func_8026EE18(f32 arg0);
void func_8026EEF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
u16 func_8026EF50(f32 arg0, f32 arg1, f32 arg2);
u16 func_8026EFD0(s32 arg0, s32 arg1, s32 arg2);
void func_8026F02C(void);
s32 func_8026F068(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8026F5E8(s32 arg0, s32 arg1, s32 arg2);
void func_8026F8B0(void);
void func_8026FC08(s32 arg0);
void func_8026FF64(s32 arg0);
void func_8026FF94(s32 arg0);
s32 func_8026FFA0(s16 arg0);
void func_80270080(s32 *arg0);
void *func_802700EC(u8 *arg0, u8 *arg1, s16 arg2, f32 arg3);
s32 func_802702BC(s16 arg0);
void func_802702EC(s16 arg0);
void func_80270354(s16 *arg0, s32 arg1);
void func_8027036C(s16 *arg0, s32 arg1);
s32 func_80270384(u8 *arg0);
s16 *func_802703B4(u8 *arg0);
s32 func_80270438(u8 *arg0, s32 *arg1);
s16 func_802704F8(f32 arg0);
s32 func_80270714(s16 arg0);
void func_80270770(s16 arg0, s16 arg1);
void func_80270A80(s32 *arg0);
void func_80270B20(u8 *arg0);
s16 func_80270B4C(s32 arg0);
void func_80270BA4(u8 *arg0);
void func_80270C24(u8 *arg0, s16 arg1, s32 arg2);
void func_80270EF0(u8 *arg0);
f32 func_80270F44(u8 *arg0);
f32 func_80270FC0(u8 *arg0);
void func_80271010(u8 *arg0, s16 arg1);
void func_80271178(s16 arg0, s32 arg1);
void func_802711C8(s16 *arg0);
s16 func_802712A8(s16 *arg0, s32 arg1);
void func_802712C4(s16 *arg0);
s32 func_8027130C(u8 *arg0);
void func_80271448(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
void func_802714C4(void);
s32 func_80271540(s16 arg0);
void *func_802716F8(s16 arg0);
void func_80271BB8(s16 arg0);
void func_80271F74(s32 *arg0);
s32 func_80272024(s16 arg0);
void func_802720C8(u8 *arg0);
s32 func_802721D4(u8 *arg0, s32 arg1, s32 *arg2);
s16 func_8027241C(s16 arg0);
void func_80272494(u8 *arg0, u8 *arg1, s32 *arg2);
void func_802727D8(Ctl87 *arg0);
void func_80272FC0(Obj8E *arg0, s16 arg1);
void func_802731A4(Obj8E *arg0, s16 arg1);
void *func_80273370(s32 arg0);
void func_802733C8(u8 *arg0);
void func_802733F8(s16 *arg0);
void func_80273414(s16 *arg0);
void func_802734BC(u8 *arg0);
void func_80273544(u8 *arg0);
s32 func_8027356C(s16 arg0);
s16 func_802735CC(void);
void *func_8027361C(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4);
s32 func_80273A5C(s32 arg0, s32 arg1, s32 arg2);
s32 func_80273AD4(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80273E2C(s16 arg0);
void func_80273F0C(void);
void func_8027723C(void);

void func_80273F0C() {
    if (D_802AFC70 != 1) {
        D_802AFC70 = 1;
    }
}

void func_80273E2C(s16 arg0) {
    s16 *p;

    if (arg0 >= 0 && arg0 < 5 && func_80270714(arg0) != 0) {
        p = func_802703B4((u8 *) func_80270714(arg0));
        p[0x2E] += 0x1E;
    }
}

s32 func_80273AD4(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    Player87 *pl;
    Ent88 *e;
    f32 v[3];
    s32 pb[7];
    Unk8026DCAC info;
    Ent88 *n;
    s16 cnt;
    s32 live;

    func_802714C4();
    func_8026DCAC(arg1, arg2, arg3, &info, 2);
    v[2] = info.i[0];
    v[1] = info.i[1];
    v[0] = info.i[2];
    if (func_80273A5C(v[2], v[1], v[0]) == 0) {
        return 0;
    }
    e = ENT_HEAD;
    n = e->next;
    pl = &PLAYERS[arg0];
    cnt = pl->unk1E;
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
    OBJ_DD8->unk58 = arg1;
    OBJ_DD8->unk40->x = OBJ_DD8->unk58;
    OBJ_DD8->unk5C = arg2;
    OBJ_DD8->unk40->y = OBJ_DD8->unk5C;
    OBJ_DD8->unk60 = arg3;
    OBJ_DD8->unk40->z = OBJ_DD8->unk60;
    OBJ_DD8->unk40->sz = 1.0f;
    OBJ_DD8->unk40->sx = OBJ_DD8->unk40->sy = OBJ_DD8->unk40->sz;
    OBJ_DD8->unk30 = 1;
    OBJ_DD8->unk34 = 40.0f;
    OBJ_DD8->unk38 = 40.0f;
    if (func_8022F4AC((s32) OBJ_DD8, 0x10, pl->unk28) != 0) {
        return 0;
    }
    if (func_802909FC(OBJ_DD8, func_80277378) != 0) {
        if (func_8022F4AC((s32) OBJ_DD8, 0x10, pl->unk28) != 0) {
            return 0;
        }
        VEC_E60[0] = OBJ_DD8->unk40->x;
        VEC_E60[1] = OBJ_DD8->unk40->y;
        VEC_E60[2] = OBJ_DD8->unk40->z;
        return 2;
    }
    return 1;
}

s32 func_80273A5C(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_t8;
    u16 temp_v0;

    temp_v0 = func_8026D7D8(arg0, arg1, arg2);
    if (temp_v0 & 0x4000) {
        return 0;
    }
    temp_t8 = temp_v0 & 0xF;
    if (temp_v0 & 0x60) {
        return 0;
    }
    switch (temp_t8) {
    case 7:
    case 8:
    case 12:
    case 13:
    case 15:
        return 0;
    default:
        return 1;
    }
}

void *func_8027361C(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4) {
    s16 spA6;
    s32 spA0;
    s32 sp9C;
    u8 *sp94;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    s16 temp_v0;
    s16 var_t0;
    s32 temp_t6;
    s32 temp_v0_3;
    s32 var_a1;
    s32 var_a2;
    u8 *temp_a0;
    u8 *temp_v0_2;

    temp_v0 = func_802735CC();
    if (temp_v0 == -1) {
        return NULL;
    }
    if (arg0 & 0x100) {
        var_a2 = 0x90;
    } else {
        var_a2 = 0xA0;
    }
    var_a1 = 0x01000012;
    if (arg0 & 5) {
        var_a1 = 0x01004012;
    }
    if (arg0 & 2) {
        var_a1 |= 0x0C000000;
    }
    if (arg0 & 0x800) {
        var_a1 |= 0x8000;
    }
    sp9C = var_a1;
    spA0 = var_a2;
    spA6 = temp_v0;
    temp_v0_2 = func_80231274(func_8027356C(arg0), var_a1, var_a2, NULL);
    if (temp_v0_2 == NULL) {
        return NULL;
    }
    spA6 = temp_v0;
    sp94 = temp_v0_2;
    if (func_802311E8(temp_v0_2) == 0) {
        return NULL;
    }
    M2C_FIELD(temp_v0_2, s32 *, 0x30) = 0x21;
    M2C_FIELD(temp_v0_2, f32 *, 0x34) = 40.0f;
    M2C_FIELD(temp_v0_2, f32 *, 0x38) = 40.0f;
    temp_a0 = (temp_v0 * 0x88) + D_8008F438;
    sp94 = temp_v0_2;
    spA6 = temp_v0;
    func_80273544(temp_a0);
    temp_v0_3 = func_80238A10(func_8027723C, (s32) temp_a0, 0, 0, 0xB0);
    M2C_FIELD(temp_a0, s32 *, 4) = temp_v0_3;
    if (temp_v0_3 == -1) {
        return NULL;
    }
    M2C_FIELD(temp_a0, s16 *, 0) = temp_v0;
    M2C_FIELD(temp_a0, s32 *, 8) = -1;
    M2C_FIELD(temp_a0, s16 *, 0xC) = 0;
    M2C_FIELD(temp_a0, void **, 0x1C) = temp_v0_2;
    M2C_FIELD(temp_a0, void **, 0x30) = temp_v0_2;
    M2C_FIELD(temp_a0, void **, 0x34) = temp_v0_2;
    M2C_FIELD(temp_a0, s16 *, 0x3C) = 0;
    M2C_FIELD(temp_a0, s16 *, 0xE) = arg4;
    M2C_FIELD(temp_a0, s32 *, 0x20) = (s32) M2C_FIELD(temp_v0_2, s32 *, 0x40);
    M2C_FIELD(temp_a0, s16 *, 0x10) = arg0;
    var_t0 = 0;
    if (M2C_FIELD(temp_a0, s16 *, 0x10) & 0x400) {
        M2C_FIELD(temp_a0, s16 *, 0x68) = 0x3C;
    } else {
        M2C_FIELD(temp_a0, s16 *, 0x68) = 0x96;
    }
    M2C_FIELD(temp_a0, s16 *, 0x62) = 0;
    M2C_FIELD(temp_a0, s16 *, 0x5C) = 0;
    M2C_FIELD(temp_a0, s16 *, 0x5E) = 0;
    M2C_FIELD(temp_a0, s16 *, 0x60) = (s16) M2C_FIELD(temp_a0, s16 *, 0x62);
    if (M2C_FIELD(temp_a0, s16 *, 0x10) & 2) {
        M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFFFD);
    } else {
        M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) | 2);
    }
    do {
        temp_t6 = var_t0 * 4;
        var_t0 += 1;
        M2C_FIELD((temp_a0 + temp_t6), s32 *, 0x24) = 0;
    } while (var_t0 < 3);
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x10) = arg1;
    temp_fv0 = M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x10);
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x1C), f32 *, 0x58) = temp_fv0;
    M2C_FIELD(temp_a0, f32 *, 0x40) = temp_fv0;
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x14) = arg2;
    temp_fv0_2 = M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x14);
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x1C), f32 *, 0x5C) = temp_fv0_2;
    M2C_FIELD(temp_a0, f32 *, 0x44) = temp_fv0_2;
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x18) = arg3;
    temp_fv0_3 = M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x18);
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x1C), f32 *, 0x60) = temp_fv0_3;
    M2C_FIELD(temp_a0, f32 *, 0x48) = temp_fv0_3;
    M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x1C), f32 *, 0x6C) = 1.0f;
    M2C_FIELD(temp_a0, f32 *, 0x4C) = 0.0f;
    M2C_FIELD(temp_a0, f32 *, 0x50) = 0.0f;
    M2C_FIELD(temp_a0, f32 *, 0x54) = 0.0f;
    M2C_FIELD(temp_a0, s16 *, 0x66) = (s16) (*(s32 *)((u8 *)&D_800AEE10 + (arg4 * 0xC8)) + 1);
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFFFB);
    M2C_FIELD(temp_a0, s16 *, 0x74) = 9;
    if (M2C_FIELD(temp_a0, s16 *, 0x10) & 0x800) {
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x28) = 10.0f;
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x2C) = 10.0f;
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x30) = 10.0f;
        M2C_FIELD(temp_a0, f32 *, 0x78) = 10.0f;
        M2C_FIELD(temp_a0, f32 *, 0x80) = 10.0f;
        M2C_FIELD(temp_a0, f32 *, 0x7C) = 9.0f;
        M2C_FIELD(temp_a0, f32 *, 0x84) = 0.033333335f;
    } else {
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x28) = 1.0f;
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x2C) = 1.0f;
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), f32 *, 0x30) = 1.0f;
        M2C_FIELD(temp_a0, f32 *, 0x78) = 1.0f;
        M2C_FIELD(temp_a0, f32 *, 0x80) = 1.0f;
        M2C_FIELD(temp_a0, f32 *, 0x7C) = 0.9f;
        if (M2C_FIELD(temp_a0, s16 *, 0x10) & 0x400) {
            M2C_FIELD(temp_a0, f32 *, 0x84) = 0.008333334f;
        } else {
            M2C_FIELD(temp_a0, f32 *, 0x84) = 0.0033333334f;
        }
    }
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFFFE);
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFFDF);
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFDFF);
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFFF7);
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFFEF);
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFF7F);
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFFBF);
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xFBFF);
    M2C_FIELD(temp_a0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_a0, s16 *, 0x64) & 0xF7FF);
}

s16 func_802735CC() {
    u8 *var_v0;
    s16 var_v1;
    s32 var_at;

    var_v0 = D_8008F438;
    var_v1 = 0;
loop_1:
    var_at = var_v1 < 0x16;
    if (M2C_FIELD(var_v0, s32 *, 0x20) != 0) {
        var_v1 += 1;
        var_v0 += 0x88;
        if (var_v1 >= 0x16) {
            var_at = var_v1 < 0x16;
        } else {
            goto loop_1;
        }
    }
    if (var_at != 0) {
        return var_v1;
    }
    return -1;
}

s32 func_8027356C(s16 arg0) {
    u32 temp_t8;

    temp_t8 = arg0 & 0xF;
    switch (temp_t8) {
    case 0:
        return 0;
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 5;
    case 4:
    case 5:
    case 6:
    case 7:
        return 0;
    default:
        return 0;
    }
}

void func_80273544(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(D_8008F438, void **, 0xA0);
    M2C_FIELD(D_8008F438, void **, 0xA0) = arg0;
    M2C_FIELD(temp_v0, void **, 0x14) = arg0;
    M2C_FIELD(arg0, M2C_UNK **, 0x14) = D_8008F4C0;
    M2C_FIELD(arg0, void **, 0x18) = temp_v0;
}

void func_802734BC(u8 *arg0) {
    s16 *temp_v0;
    s32 var_v0;

    temp_v0 = func_802703B4(arg0);
    if (temp_v0 != NULL) {
        var_v0 = 0;
        if (M2C_FIELD(temp_v0, f32 *, 0x40) != 1e7f) {
            var_v0 = 1;
        }
        if (var_v0 != 0) {
            func_80273414(temp_v0);
        }
        func_802733F8(temp_v0);
        func_80238EA8(M2C_FIELD(temp_v0, s32 *, 4));
        func_80239094();
    }
}

void func_80273414(s16 *arg0) {
    s16 temp_v1;
    s32 *temp_a0;
    s32 temp_a0_2;

    func_80270BA4(M2C_FIELD(arg0, void **, 0x1C));
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x64);
    if ((s16) (temp_v1 & 0x200) != 0) {
        M2C_FIELD(arg0, s16 *, 0x64) = (s16) (temp_v1 & 0xFDFF);
        func_802313DC(M2C_FIELD(arg0, void **, 0x1C), 0x20000);
        temp_a0 = M2C_FIELD(arg0, s32 **, 0x38);
        func_80270A80(temp_a0);
        free(temp_a0);
    }
    temp_a0_2 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_a0_2 != -1) {
        func_8028A4E0(temp_a0_2);
        M2C_FIELD(arg0, s32 *, 8) = -1;
    }
    M2C_FIELD(arg0, s16 *, 0x74) = 9;
    func_802711C8(arg0);
    func_8022FC90(M2C_FIELD(arg0, void **, 0x1C));
}

void func_802733F8(s16 *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = M2C_FIELD(arg0, void **, 0x18);
    temp_v1 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_v0, void **, 0x14) = temp_v1;
    M2C_FIELD(temp_v1, void **, 0x18) = temp_v0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}

void func_802733C8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = func_80273370((s32) arg0);
    func_802731A4(M2C_FIELD(temp_v0, void **, 0xC), M2C_FIELD(temp_v0, s16 *, 0));
}

void *func_80273370(s32 arg0) {
    s16 var_v0;
    u8 *temp_v1;

    var_v0 = 0;
loop_1:
    temp_v1 = D_802AFCE8 + (var_v0 * 0x30);
    if (arg0 == M2C_FIELD(temp_v1, s32 *, 0xC)) {
        return temp_v1;
    }
    var_v0 += 1;
    if (var_v0 >= 5) {
        return NULL;
    }
    goto loop_1;
}

void func_802731A4(Obj8E *arg0, s16 arg1) {
    s32 done;
    s32 pad;
    f32 y;
    Sub8E *t;
    Obj8E *cur;

    if (func_802702BC(arg1) != 0) {
        return;
    }
    cur = (Obj8E *) func_80270714(arg1);
    if (cur == NULL) {
        return;
    }
    if (cur != arg0) {
        return;
    }
    if (SLOTS[arg1].unk10 <= 0) {
        return;
    }
    y = func_8026E938(arg0->unk40);
    func_80272FC0(arg0, arg1);
    done = 0;
    func_80231434(arg0);
    if (y != 20000.0f) {
        t = arg0->unk40;
        if (t->y < y) {
            arg0->unk50 += y - t->y;
            t->y = y;
        }
    }
    if (arg0->unk8 & 0x10) {
        if (func_80232D18(arg0, 0x10) != 0) {
            arg0->unk40->x = arg0->unk58;
            arg0->unk40->y = arg0->unk5C;
            arg0->unk40->z = arg0->unk60;
            done = 1;
        }
        if (done == 1) {
            func_80244C30(arg1, 0);
        }
    }
}

void func_80272FC0(Obj8E *arg0, s16 arg1) {
    f32 dx;
    f32 dz;
    Slot30 *sl;
    f32 h;
    Obj8E *o;
    f32 s;
    s32 pad[1];

    o = func_802443F4(arg1);
    s = func_80234434(o->unk40->rot);
    dx = func_80270F44(arg0) * s;
    s = func_80234408(o->unk40->rot);
    dz = func_80270F44(arg0) * s;
    if (func_802336E4(dx) != 0) {
        dx = 0.0f;
    }
    if (func_802336E4(dz) != 0) {
        dz = 0.0f;
    }
    sl = &SLOTS[arg1];
    arg0->unk4C = dx - sl->unk1C;
    sl->unk1C -= sl->unk1C / sl->unk10;
    arg0->unk54 = dz - sl->unk24;
    sl->unk24 -= sl->unk24 / sl->unk10;
    h = func_80234434(sl->unk20) * sl->unk2C;
    arg0->unk50 += h - sl->unk28;
    sl->unk10--;
    sl->unk28 = h;
    sl->unk20 += 4.5f;
    if (sl->unk10 <= 0) {
        func_802313DC(arg0, 0x200000);
        func_80231408(arg0, 0x600000);
        arg0->unk4C = 0.0f;
        arg0->unk50 = func_80270FC0(o);
        arg0->unk54 = func_80270F44(arg0);
    }
}

void func_802727D8(Ctl87 *arg0) {
    s32 pad[2];
    Obj8E *p;
    Obj8E *obj;
    Obj8E *hit;
    s32 v;
    s16 i;
    s32 done;

    obj = arg0->obj;
    if (arg0->unk16 > 0) {
        arg0->unk16--;
    }
    func_80291944(obj, func_80272024(arg0->unk14), arg0->unk1C);
    if (obj->unk8 & 1) {
        func_80291944(obj, arg0->unk20, arg0->unk24);
        arg0->unk20 = 1;
        arg0->unk24 = 0.0f;
    }
    func_802720C8(obj);
    obj->unk70 = 1.6333334f;
    func_80230914(obj);
    if (func_802909FC(obj, func_80277378) != 0) {
        if (obj->unk40->x == obj->unk58 && obj->unk40->z == obj->unk60 && !(obj->unk8 & 1)) {
            arg0->unk1C = 0.0f;
        }
    }
    if (arg0->unk2C != 10000.0f) {
        arg0->unk1C = arg0->unk2C;
        arg0->unk2C = 10000.0f;
    }
    if (!(arg0->flags & 8)) {
        if (obj->unk8 & 1) {
            for (i = 0; i < 4; i++) {
                if (func_802443F4(i) == obj) {
                    break;
                }
            }
            if (i >= 4) {
                i = 0;
            }
            hit = (Obj8E *) func_8022F4AC((s32) obj, 0x8016, func_802442A8(i));
        } else {
            hit = func_802308B8(obj, 0x8016);
        }
        if (hit != NULL) {
            obj->unk40->x = obj->unk58;
            obj->unk40->y = obj->unk5C;
            obj->unk40->z = obj->unk60;
            if (hit != NULL && (hit->unk8 & 0x8000) && hit != arg0->unk8) {
                arg0->unk8 = hit;
                arg0->unk14 = func_8027241C(arg0->unk14);
                if (arg0->unk16 == 0) {
                    arg0->unk16 = 25;
                    func_8028A81C(0, obj->unk40->x, obj->unk40->y + 100.0f, obj->unk40->z, 0);
                }
                if (hit->unk8 & 4) {
                    func_8026C51C(0x22, obj->unk40->x, obj->unk40->y, obj->unk40->z);
                } else if (obj->unk8 & 1) {
                    func_8026C51C(0x2D, obj->unk40->x, obj->unk40->y, obj->unk40->z);
                } else {
                    func_8026C51C(0x23, obj->unk40->x, obj->unk40->y, obj->unk40->z);
                }
            }
            if (hit != NULL && obj->unk6C != 1.0f && (hit->unk8 & 0x16)) {
                if (hit == arg0->unkC) {
                    arg0->unk14 = func_8027241C(arg0->unk14);
                    func_80272494((u8 *) obj, (u8 *) hit, (s32 *) arg0);
                }
                if (hit->unk40->y <= obj->unk40->y) {
                    arg0->unkC = hit;
                    obj->unk6C = 2.0f;
                    obj->unk68 = 22.5f;
                    if (obj->unk8 & 1) {
                        if (!func_8023369C(arg0->unk34, obj->unk40->x, 0.9f) || !func_8023369C(arg0->unk38, obj->unk40->z, 0.9f)) {
                            arg0->unk30 = 0;
                            arg0->unk34 = obj->unk40->x;
                            arg0->unk38 = obj->unk40->z;
                        } else if (++arg0->unk30 >= 6) {
                            arg0->unk1C = 0.0f;
                        }
                        arg0->unk20 = func_80272024(arg0->unk14);
                        arg0->unk24 = 0.0f;
                        func_802441F4(obj, func_80272024(arg0->unk14), &arg0->unk20, &arg0->unk24);
                    }
                    if (arg0->unk16 == 0) {
                        arg0->unk16 = 25;
                        func_8028A81C(0, obj->unk40->x, obj->unk40->y + 100.0f, obj->unk40->z, 0);
                    }
                    if (hit->unk8 & 4) {
                        func_8026C51C(0x22, obj->unk40->x, obj->unk40->y, obj->unk40->z);
                    } else if (obj->unk8 & 1) {
                        func_8026C51C(0x2D, obj->unk40->x, obj->unk40->y, obj->unk40->z);
                    } else {
                        func_8026C51C(0x23, obj->unk40->x, obj->unk40->y, obj->unk40->z);
                    }
                } else if (hit != arg0->unkC) {
                    obj->unk68 = 0.0f;
                    obj->unk6C = 2.0f;
                    arg0->unk14 = 9;
                    arg0->unkC = hit;
                }
            }
        } else {
            arg0->unkC = arg0->obj;
            if (arg0->flags & 1) {
                for (i = 0; i < 5; i++) {
                    if (func_802443F4(i) == arg0->obj) {
                        arg0->obj = func_802443F4(i);
                        break;
                    }
                }
                if (i < 5 && func_80270714(i) != 0) {
                    p = (Obj8E *) func_80270714(i);
                    func_80231434(p);
                    if (func_802308B8(p, 0x8016) != NULL) {
                        obj->unk40->x = obj->unk58;
                        obj->unk40->y = obj->unk5C;
                        obj->unk40->z = obj->unk60;
                        p->unk40->x = p->unk58;
                        p->unk40->y = p->unk5C;
                        p->unk40->z = p->unk60;
                        func_80244C30(i, 0);
                    }
                }
            }
        }
    }
    done = 0;
    if (obj->unk6C == 0.0f && obj->unk68 == 0.0f) {
        if (arg0->flags & 8) {
            u8 *b = func_8027A1A0(arg0->obj);

            if (b != NULL && (s16) (*(s16 *) (b + 0x54) & 0x40) == 0 && arg0->unk28 < 2) {
                v = 0;
                if (obj->unk40->y <= func_8026E8B8()) {
                    v = 1;
                }
                if (v == 0) {
                    arg0->unk28++;
                    done = 1;
                    obj->unk6C = 2.0f;
                    obj->unk68 = 22.5f;
                }
            }
        }
        if (done == 0) {
            func_80271F74((s32 *) arg0);
        }
    }
}

void func_80272494(u8 *arg0, u8 *arg1, s32 *arg2) {
    f32 sp88[3];
    f32 sp7C[3];
    f32 sp70;
    f32 temp_fs2;
    f32 var_fs0;
    f32 var_fs0_2;
    f32 var_fs0_3;
    f32 var_fs0_4;
    f32 var_fs2;
    f32 var_fv1;
    f32 var_fv1_2;
    s16 var_s3;
    s32 temp_v0;
    s32 var_s4;

    sp88[1] = 0.0f;
    sp88[0] = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x10);
    sp88[2] = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x18);
    sp7C[1] = 0.0f;
    sp7C[0] = M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), f32 *, 0x10);
    sp7C[2] = M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), f32 *, 0x18);
    if (M2C_FIELD(arg1, s32 *, 8) & 0x8000) {
        M2C_FIELD(arg2, s16 *, 0x14) = func_8027241C(M2C_FIELD(arg2, s16 *, 0x14));
    }
    if (M2C_FIELD(arg2, s16 *, 0x14) == 9) {
        func_8022FF58(sp7C, sp88, &sp70);
        M2C_FIELD(arg2, s16 *, 0x14) = func_802704F8(sp70);
    }
    var_s3 = M2C_FIELD(arg2, s16 *, 0x14);
    M2C_FIELD(arg2, f32 *, 0x2C) = (f32) M2C_FIELD(arg2, f32 *, 0x1C);
    if (func_80270F44(arg0) < 0.0f) {
        var_fs0 = -func_80270F44(arg0);
    } else {
        var_fs0 = func_80270F44(arg0);
    }
    if (func_80270F44(arg1) < 0.0f) {
        var_fv1 = -func_80270F44(arg1);
    } else {
        var_fv1 = func_80270F44(arg1);
    }
    if ((var_fv1 + var_fs0) < 0.0f) {
        if (func_80270F44(arg0) < 0.0f) {
            var_fs0_2 = -func_80270F44(arg0);
        } else {
            var_fs0_2 = func_80270F44(arg0);
        }
        if (func_80270F44(arg1) < 0.0f) {
            var_fs2 = -(-func_80270F44(arg1) + var_fs0_2);
        } else {
            var_fs2 = -(func_80270F44(arg1) + var_fs0_2);
        }
    } else {
        if (func_80270F44(arg0) < 0.0f) {
            var_fs0_3 = -func_80270F44(arg0);
        } else {
            var_fs0_3 = func_80270F44(arg0);
        }
        if (func_80270F44(arg1) < 0.0f) {
            var_fv1_2 = -func_80270F44(arg1);
        } else {
            var_fv1_2 = func_80270F44(arg1);
        }
        var_fs2 = var_fv1_2 + var_fs0_3;
    }
    var_s4 = 0;
    temp_fs2 = var_fs2 + 1.0f;
loop_25:
    var_fs0_4 = 10.0f;
    if (temp_fs2 > 10.0f) {
loop_26:
        M2C_FIELD(arg2, f32 *, 0x1C) = var_fs0_4;
        M2C_FIELD(arg2, s16 *, 0x14) = var_s3;
        temp_v0 = func_802721D4(arg0, (s32) arg1, arg2);
        if (temp_v0 != 2) {
            if (temp_v0 != 1) {
                var_fs0_4 += 10.0f;
                if (!(var_fs0_4 < temp_fs2)) {
                    goto block_29;
                }
                goto loop_26;
            }
        } else {
            goto block_29;
        }
    } else {
block_29:
        if (temp_fs2 <= var_fs0_4) {
            M2C_FIELD(arg2, f32 *, 0x1C) = temp_fs2;
            M2C_FIELD(arg2, s16 *, 0x14) = var_s3;
            if (func_802721D4(arg0, (s32) arg1, arg2) != 1) {
                goto block_33;
            }
        } else {
block_33:
            var_s4 += 1;
            var_s3 = (var_s3 + 1) & 7;
            if (var_s4 == 8) {

            } else {
                goto loop_25;
            }
        }
    }
}

s16 func_8027241C(s16 arg0) {
    s16 var_a0;

    var_a0 = arg0;
    switch (arg0) {
    case 0:
        return 4;
    case 1:
        return 5;
    case 2:
        return 6;
    case 3:
        return 7;
    case 4:
        return 0;
    case 5:
        return 1;
    case 6:
        return 2;
    case 7:
        var_a0 = 3;
        /* fallthrough */
    default:
        return var_a0;
    }
}

s32 func_802721D4(u8 *arg0, s32 arg1, s32 *arg2) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    s32 var_v0;
    u8 *temp_a0;

    func_802714C4();
    temp_fv0 = M2C_FIELD(arg0, f32 *, 0x58);
    M2C_FIELD(D_802AFDD8, f32 *, 0x58) = temp_fv0;
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x10) = temp_fv0;
    temp_fv0_2 = M2C_FIELD(arg0, f32 *, 0x5C);
    M2C_FIELD(D_802AFDD8, f32 *, 0x5C) = temp_fv0_2;
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x14) = temp_fv0_2;
    temp_fv0_3 = M2C_FIELD(arg0, f32 *, 0x60);
    M2C_FIELD(D_802AFDD8, f32 *, 0x60) = temp_fv0_3;
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x18) = temp_fv0_3;
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x28) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x28);
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x2C) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x2C);
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x30) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x30);
    M2C_FIELD(D_802AFDD8, s32 *, 0x30) = 1;
    M2C_FIELD(D_802AFDD8, f32 *, 0x34) = (f32) M2C_FIELD(arg0, f32 *, 0x34);
    M2C_FIELD(D_802AFDD8, f32 *, 0x38) = (f32) M2C_FIELD(arg0, f32 *, 0x38);
    func_80291944(D_802AFDD8, func_80272024(M2C_FIELD(arg2, s16 *, 0x14)), M2C_FIELD(arg2, f32 *, 0x1C));
    temp_a0 = D_802AFDD8;
    if (M2C_FIELD(temp_a0, s32 *, 8) & 1) {
        M2C_FIELD(arg2, s32 *, 0x20) = func_80272024(M2C_FIELD(arg2, s16 *, 0x14));
        M2C_FIELD(arg2, f32 *, 0x24) = 0.0f;
        func_802441F4(arg0, func_80272024(M2C_FIELD(arg2, s16 *, 0x14)), (u8 *)arg2 + 0x20, (f32 *) ((u8 *)arg2 + 0x24));
        func_80291944(D_802AFDD8, M2C_FIELD(arg2, s32 *, 0x20), M2C_FIELD(arg2, f32 *, 0x24));
        M2C_FIELD(arg2, s32 *, 0x20) = 1;
        M2C_FIELD(arg2, f32 *, 0x24) = 0.0f;
    }
    func_802720C8(temp_a0);
    M2C_FIELD(D_802AFDD8, f32 *, 0x70) = 1.6333334f;
    M2C_FIELD(D_802AFDD8, f32 *, 0x6C) = 2.0f;
    M2C_FIELD(D_802AFDD8, f32 *, 0x68) = 22.5f;
    func_80230914(D_802AFDD8);
    if (func_802909FC(D_802AFDD8, func_80277378) != 0) {
        return 2;
    }
    var_v0 = 1;
    if (func_8022E884((s32) D_802AFDD8, arg1) != 0) {
        var_v0 = 0;
    }
    return var_v0;
}

void func_802720C8(u8 *arg0) {
    s32 sp20[3];
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_t5;

    func_8026DCAC(M2C_FIELD(arg0, f32 *, 0x58), M2C_FIELD(arg0, f32 *, 0x5C), M2C_FIELD(arg0, f32 *, 0x60), sp20, 2);
    temp_fv0 = (f32) sp20[0];
    temp_fv1 = (f32) sp20[1];
    temp_fa0 = (f32) sp20[2];
    temp_t5 = func_8026D7D8((s32) temp_fv0, (s32) temp_fv1, (s32) temp_fa0) & 0x1C00;
    if (temp_t5 != 0) {
        func_8027F858((s32) arg0, temp_t5 >> 0xA);
    }
}

s32 func_80272024(s16 arg0) {
    s32 sp4;

    switch (arg0) {
    case 9:
        sp4 = 1;
        break;
    case 0:
        sp4 = 0;
        break;
    case 1:
        sp4 = 0x20;
        break;
    case 2:
        sp4 = 0x40;
        break;
    case 3:
        sp4 = 0x60;
        break;
    case 4:
        sp4 = 0x80;
        break;
    case 5:
        sp4 = 0xA0;
        break;
    case 6:
        sp4 = 0xC0;
        break;
    case 7:
        sp4 = 0xE0;
        break;
    }
    return sp4;
}

void func_80271F74(s32 *arg0) {
    s32 temp_v0;

    func_802313DC(M2C_FIELD(arg0, void **, 4), 0x20000);
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_v0 & 2) {
        func_80270EF0(M2C_FIELD(arg0, void **, 4));
    } else if (temp_v0 & 8) {
        func_8027B440(M2C_FIELD(arg0, void **, 4));
    } else if (temp_v0 & 4) {
        func_80287440();
    } else if (temp_v0 & 1) {
        func_80244E04(M2C_FIELD(arg0, void **, 4));
    }
    func_80270A80(arg0);
    free(arg0);
}

void func_80271BB8(s16 arg0) {
    s32 flags;
    s32 hit;
    f32 dx;
    f32 dz;
    Obj8E *pl;
    s32 pad[1];
    f32 ppos[3];
    f32 opos[3];
    f32 s;
    Obj8E *obj;
    Slot30 *sl;
    Sub8E *t;

    if (func_80270714(arg0) != 0) {
        return;
    }
    pl = func_802443F4(arg0);
    obj = (Obj8E *) func_80271540(arg0);
    if (obj == NULL) {
        return;
    }
    t = pl->unk40;
    ppos[0] = t->x;
    ppos[1] = t->y;
    ppos[2] = t->z;
    t = obj->unk40;
    opos[0] = t->x;
    opos[1] = t->y;
    opos[2] = t->z;
    if (func_802716F8(arg0) == NULL) {
        return;
    }
    flags = obj->unk8;
    hit = 0;
    if (flags & 2) {
        if (func_8027130C((u8 *) obj) == 0) {
            hit = 1;
        }
    } else if (flags & 8) {
        if (func_8027B5A8(obj) == 0) {
            hit = 1;
        }
    } else if (flags & 4) {
        if (func_802875B0(obj) == 0) {
            hit = 1;
        }
    } else if (flags & 1) {
        if (func_80244FF8(obj) == 0) {
            hit = 1;
        }
    } else {
        hit = 1;
    }
    if (hit == 1) {
        pl->unk40->x = ppos[0];
        pl->unk40->y = ppos[1];
        pl->unk40->z = ppos[2];
        obj->unk40->x = opos[0];
        obj->unk40->y = opos[1];
        obj->unk40->z = opos[2];
    } else {
        sl = &SLOTS[arg0];
        sl->unk8 = flags;
        func_80231408(obj, 0x10000);
        func_80232AC8((s32) pl, (s32) obj);
        func_80231408(obj, 0x200000);
        func_80271178(arg0, (s32) obj);
        func_80271010((u8 *) obj, arg0);
        obj->unk40->rot = pl->unk40->rot;
        s = func_80234434(pl->unk40->rot);
        dx = func_80270F44((u8 *) pl) * s;
        s = func_80234408(pl->unk40->rot);
        dz = func_80270F44((u8 *) pl) * s;
        if (func_802336E4(dx) != 0) {
            dx = 0.0f;
        }
        if (func_802336E4(dz) != 0) {
            dz = 0.0f;
        }
        obj->unk4C = dx - sl->unk1C;
        obj->unk50 = obj->unk40->y - pl->unk40->y;
        obj->unk6C = 1.0f;
        obj->unk54 = dz - sl->unk24;
        obj->unk70 = 1.6333334f;
    }
}

void *func_802716F8(s16 arg0) {
    f32 dx;
    f32 dz;
    f32 r;
    f32 dist;
    s32 pad[2];
    f32 a[3];
    f32 b[3];
    s32 pad2[2];
    f32 ang;
    s32 pad3;
    f32 pr;
    s32 pad4[6];
    Unk8026DCAC info;
    Obj8E *pl;
    Obj8E *obj;
    s32 t;

    func_802714C4();
    pl = func_802443F4(arg0);
    obj = (Obj8E *) func_80271540(arg0);
    if (obj != NULL) {
    func_8026DCAC(obj->unk40->x, obj->unk40->y, obj->unk40->z, &info, 2);
    a[0] = info.i[0];
    a[1] = info.i[1];
    a[2] = info.i[2];
    t = func_8026D7D8(a[0], a[1], a[2]) & 0xF;
    if (t == 3 || t == 4 || t == 5 || t == 6) {
        return obj;
    }
    a[1] = 0.0f;
    a[0] = pl->unk40->x;
    a[2] = pl->unk40->z;
    b[1] = 0.0f;
    b[0] = obj->unk40->x;
    b[2] = obj->unk40->z;
    dist = func_8022DF68(a, b);
    pr = func_80270F44((u8 *) pl);
    r = (func_80270F44((u8 *) obj) + pr) * 1.2f;
    if (dist < r) {
        func_8022FF58(a, b, &ang);
        dx = func_80234434(ang) * r;
        dz = func_80234408(ang) * r;
        OBJ_DD8->unk40->x = pl->unk40->x + dx;
        OBJ_DD8->unk40->y = obj->unk40->y;
        OBJ_DD8->unk40->z = pl->unk40->z + dz;
        OBJ_DD8->unk40->sx = obj->unk40->sx;
        OBJ_DD8->unk40->sy = obj->unk40->sy;
        OBJ_DD8->unk40->sz = obj->unk40->sz;
        OBJ_DD8->unk30 = obj->unk30;
        OBJ_DD8->unk34 = obj->unk34;
        OBJ_DD8->unk38 = obj->unk38;
        if (func_8022F4AC((s32) OBJ_DD8, 0x10, (s32) obj) == 0 && func_802909FC(OBJ_DD8, func_80277378) == 0) {
            obj->unk40->x = pl->unk40->x + dx;
            obj->unk40->z = pl->unk40->z + dz;
        } else {
            OBJ_DD8->unk40->x = pl->unk40->x - ((pl->unk40->x + dx) - obj->unk40->x);
            OBJ_DD8->unk40->y = pl->unk40->y;
            OBJ_DD8->unk40->z = pl->unk40->z - ((pl->unk40->z + dz) - obj->unk40->z);
            OBJ_DD8->unk40->sx = pl->unk40->sx;
            OBJ_DD8->unk40->sy = pl->unk40->sy;
            OBJ_DD8->unk40->sz = pl->unk40->sz;
            OBJ_DD8->unk30 = pl->unk30;
            OBJ_DD8->unk34 = pl->unk34;
            OBJ_DD8->unk38 = pl->unk38;
            if (func_8022F4AC((s32) OBJ_DD8, 0x10, (s32) pl) == 0 && func_802909FC(OBJ_DD8, func_80277378) == 0) {
                pl->unk40->x = OBJ_DD8->unk40->x;
                pl->unk40->z = OBJ_DD8->unk40->z;
            } else {
                obj = NULL;
            }
        }
    }
    }
    return obj;
}

s32 func_80271540(s16 arg0) {
    f32 sp28;
    f32 sp24;
    f32 temp_fv0;
    u8 *temp_v0;
    u8 *temp_v1;

    func_802714C4();
    temp_v0 = func_802443F4((s32) arg0);
    sp28 = func_80234434(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20)) * 100.0f * 0.8f;
    sp24 = func_80234408(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20)) * 100.0f * 0.8f;
    if (func_802336E4(sp28) != 0) {
        sp28 = 0.0f;
    }
    if (func_802336E4(sp24) != 0) {
        sp24 = 0.0f;
    }
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x10) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) + sp28);
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x14) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) + 60.0f);
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x18) = (f32) (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) + sp24);
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x30) = 0.8f;
    temp_v1 = M2C_FIELD(D_802AFDD8, void **, 0x40);
    temp_fv0 = M2C_FIELD(temp_v1, f32 *, 0x30);
    M2C_FIELD(temp_v1, f32 *, 0x2C) = temp_fv0;
    M2C_FIELD(M2C_FIELD(D_802AFDD8, void **, 0x40), f32 *, 0x28) = temp_fv0;
    M2C_FIELD(D_802AFDD8, s32 *, 0x30) = 1;
    M2C_FIELD(D_802AFDD8, f32 *, 0x34) = 50.0f;
    M2C_FIELD(D_802AFDD8, f32 *, 0x38) = 50.0f;
    return func_802308B8(D_802AFDD8, 0xF);
}

void func_802714C4() {
    s16 var_s0;
    s32 var_a0;

    if (D_802AFC74 != 1) {
        D_802AFC74 = 1;
        var_s0 = 0;
        var_a0 = 0 << 0x10;
        do {
            func_802702EC((s16) (var_a0 >> 0x10));
            var_s0 += 1;
            var_a0 = var_s0 << 0x10;
        } while (var_s0 < 5);
        D_802AFDD8 = func_80231274(-1, 0, 0xD0, NULL);
    }
}

void func_80271448(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    s32 sp20[3];

    func_8026DCAC(arg0, arg1, arg2, sp20, 2);
    *arg3 = (f32) sp20[0];
    *arg4 = (f32) sp20[1];
    *arg5 = (f32) sp20[2];
}

s32 func_8027130C(u8 *arg0) {
    s16 *temp_v0;
    s16 temp_v1;
    s16 var_v0;
    s32 *temp_a0;

    temp_v0 = func_802703B4(arg0);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_v1 = M2C_FIELD(temp_v0, s16 *, 0x64);
    if ((s16) (temp_v1 & 0x80) != 0) {
        return 0;
    }
    var_v0 = temp_v1 & 0x200;
    if ((s16) (temp_v1 & 0x10) != 0) {
        func_80270BA4(arg0);
        var_v0 = M2C_FIELD(temp_v0, s16 *, 0x64) & 0x200;
    }
    if (var_v0 != 0) {
        M2C_FIELD(temp_v0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_v0, s16 *, 0x64) & 0xFDFF);
        func_802313DC(M2C_FIELD(temp_v0, void **, 0x1C), 0x20000);
        temp_a0 = M2C_FIELD(temp_v0, s32 **, 0x38);
        func_80270A80(temp_a0);
        free(temp_a0);
    }
    func_802712C4(temp_v0);
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x1C), f32 *, 0x6C) = 1.0f;
    M2C_FIELD(temp_v0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_v0, s16 *, 0x64) | 0x10);
    M2C_FIELD(temp_v0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_v0, s16 *, 0x64) & 0xF7FF);
    M2C_FIELD(temp_v0, f32 *, 0x50) = 0.0f;
    M2C_FIELD(temp_v0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_v0, s16 *, 0x64) & 0xFFFD);
    if (M2C_FIELD(temp_v0, s16 *, 0x10) & 0x400) {
        M2C_FIELD(temp_v0, s16 *, 0x68) = 0x3C;
    } else {
        M2C_FIELD(temp_v0, s16 *, 0x68) = 0x96;
    }
    M2C_FIELD(temp_v0, f32 *, 0x80) = 1.0f;
    func_802313DC(arg0, 0x20000);
    return 1;
}

void func_802712C4(s16 *arg0) {
    s16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x64);
    if ((s16) (temp_v1 & 4) != 0) {
        M2C_FIELD(arg0, s16 *, 0x74) = 9;
        M2C_FIELD(arg0, s16 *, 0x64) = (s16) (temp_v1 & 0xFFFB);
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
        func_802711C8(arg0);
    }
}

s16 func_802712A8(s16 *arg0, s32 arg1) {
    return (s16) (*arg0 & arg1);
}

void func_802711C8(s16 *arg0) {
    s16 *temp_v0;
    s16 temp_t9;
    s16 var_a0;
    s16 var_a1;
    s32 var_at;
    s32 var_t6;
    s32 var_t8;
    s32 var_v0;

    var_v0 = 0;
    var_a1 = 0;
    var_t6 = 0 * 8;
loop_1:
    var_a0 = 0;
    var_t8 = 0 * 2;
loop_2:
    if (*arg0 == *(((var_t6 + var_a1) * 2) + D_802AFC78 + var_t8)) {
        var_v0 = 1;
    } else {
        var_a0 += 1;
        var_t8 = var_a0 * 2;
        if (var_a0 < 8) {
            goto loop_2;
        }
    }
    var_at = var_a1 < 6;
    if (var_v0 != 1) {
        var_a1 += 1;
        var_t6 = var_a1 * 8;
        if (var_a1 >= 6) {
            var_at = var_a1 < 6;
        } else {
            goto loop_1;
        }
    }
    if ((var_at != 0) && (var_a0 < 8)) {
        do {
            temp_v0 = (var_a1 * 0x12) + D_802AFC78 + (var_a0 * 2);
            temp_t9 = M2C_FIELD(temp_v0, s16 *, 2);
            var_a0 += 1;
            M2C_FIELD(temp_v0, s16 *, 0) = temp_t9;
        } while (var_a0 < 8);
    }
}

void func_80271178(s16 arg0, s32 arg1) {
    s32 var_v0;

    if (arg0 >= 0) {
        var_v0 = 1;
        if (arg0 < 5) {
            var_v0 = 0;
        }
    } else {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        *(s32 *)(D_802AFCF4 + (arg0 * 0x30)) = arg1;
    }
}

void func_80271010(u8 *arg0, s16 arg1) {
    f32 sp34;
    f32 sp30;
    f32 sp24;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = func_802443F4((s32) arg1);
    sp24 = func_80234434(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20));
    sp34 = func_80270F44(arg0) * sp24;
    sp24 = func_80234408(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20));
    sp30 = func_80270F44(arg0) * sp24;
    if (func_802336E4(sp34) != 0) {
        sp34 = 0.0f;
    }
    if (func_802336E4(sp30) != 0) {
        sp30 = 0.0f;
    }
    temp_v0_2 = (arg1 * 0x30) + D_802AFCE8;
    M2C_FIELD(temp_v0_2, s16 *, 0x10) = 0x14;
    M2C_FIELD(temp_v0_2, s16 *, 0) = arg1;
    M2C_FIELD(temp_v0_2, f32 *, 0x1C) = (f32) ((M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) + sp34) - M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x10));
    M2C_FIELD(temp_v0_2, f32 *, 0x20) = 0.0f;
    M2C_FIELD(temp_v0_2, f32 *, 0x28) = 0.0f;
    M2C_FIELD(temp_v0_2, f32 *, 0x24) = (f32) ((M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) + sp30) - M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x18));
    M2C_FIELD(temp_v0_2, f32 *, 0x2C) = (f32) ((func_80270FC0(temp_v0) + M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14)) - M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14));
}

f32 func_80270FC0(u8 *arg0) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fv1;
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    var_fv1 = M2C_FIELD(temp_v0, f32 *, 0x28);
    temp_fv0 = M2C_FIELD(temp_v0, f32 *, 0x2C);
    if (var_fv1 < temp_fv0) {
        var_fv1 = temp_fv0;
    }
    temp_fv0_2 = M2C_FIELD(temp_v0, f32 *, 0x30);
    if (var_fv1 < temp_fv0_2) {
        var_fv1 = temp_fv0_2;
    }
    return 100.0f * var_fv1;
}

f32 func_80270F44(u8 *arg0) {
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fv0;
    u8 *temp_v0;

    if (M2C_FIELD(arg0, s32 *, 0x30) & 0x20) {
        return M2C_FIELD(arg0, f32 *, 0x34);
    }
    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    var_fv0 = M2C_FIELD(temp_v0, f32 *, 0x28);
    temp_fv1 = M2C_FIELD(temp_v0, f32 *, 0x2C);
    if (var_fv0 < temp_fv1) {
        var_fv0 = temp_fv1;
    }
    temp_fv1_2 = M2C_FIELD(temp_v0, f32 *, 0x30);
    if (var_fv0 < temp_fv1_2) {
        var_fv0 = temp_fv1_2;
    }
    return M2C_FIELD(arg0, f32 *, 0x34) * var_fv0;
}

void func_80270EF0(u8 *arg0) {
    s16 *temp_v0;

    temp_v0 = func_802703B4(arg0);
    M2C_FIELD(temp_v0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_v0, s16 *, 0x64) & 0xFDFF);
    func_802313DC(arg0, 0x20000);
    M2C_FIELD(temp_v0, s16 *, 0x3C) = 0;
    M2C_FIELD(temp_v0, f32 *, 0x50) = 0.0f;
    M2C_FIELD(temp_v0, s32 *, 0x30) = (s32) M2C_FIELD(temp_v0, s32 *, 0x1C);
}

void func_80270C24(u8 *arg0, s16 arg1, s32 arg2) {
    s32 sp34;
    f32 sp28;
    f32 sp24;
    Node87 *var_s0;
    Node87 *var_v0_3;
    f32 var_fv0;
    s32 *temp_v0;
    s32 temp_t6;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v1;

    var_a3 = 0;
    var_v1 = 0 << 0x10;
    do {
        temp_t6 = var_v1 >> 0x10;
        if (temp_t6 >= 0) {
            var_v0 = 1;
            if (temp_t6 < 5) {
                var_v0 = 0;
            }
        } else {
            var_v0 = 1;
        }
        if (var_v0 != 0) {
            var_v0_2 = 0;
        } else {
            var_v0_2 = *(s32 *)(D_802AFCF4 + (temp_t6 * 0x30));
        }
        if ((s32) var_v0_2 == (s32) arg0) {
            sp34 = var_a3;
            func_80270BA4(arg0);
        }
        var_a3 += 1;
        var_v1 = var_a3 << 0x10;
    } while (var_a3 != 5);
    var_s0 = D_802AFDE0.next;
    var_v0_3 = var_s0->next;
    if (var_v0_3 != NULL) {
loop_12:
        if ((s32) arg0 != var_s0->unk4) {
            var_s0 = var_v0_3;
            var_v0_3 = var_v0_3->next;
            if (var_v0_3 != NULL) {
                goto loop_12;
            }
        }
    }
    if (var_v0_3 != NULL) {
        func_80270A80((s32 *) var_s0);
        free(var_s0);
    }
    switch (arg2) {                                 /* irregular */
    case 0:
        var_fv0 = 0.0f;
        sp24 = 0.0f;
        break;
    case 1:
        var_fv0 = 25.0f;
        sp24 = 8.25f;
        break;
    case 2:
        var_fv0 = 25.0f;
        sp24 = 11.0f;
        break;
    case 3:
        var_fv0 = 25.0f;
        sp24 = 14.0f;
        break;
    default:
        var_fv0 = 10.0f;
        break;
    }
    sp28 = var_fv0;
    temp_v0 = malloc(0x3C);
    M2C_FIELD(temp_v0, void **, 4) = arg0;
    sp28 = var_fv0;
    M2C_FIELD(temp_v0, s16 *, 0x14) = func_8026FFA0(arg1);
    M2C_FIELD(temp_v0, f32 *, 0x18) = var_fv0;
    M2C_FIELD(temp_v0, s32 *, 0x20) = 1;
    M2C_FIELD(temp_v0, s32 *, 0x28) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x16) = 0;
    M2C_FIELD(temp_v0, f32 *, 0x1C) = sp24;
    M2C_FIELD(temp_v0, f32 *, 0x24) = 0.0f;
    M2C_FIELD(temp_v0, s32 *, 0x30) = 0;
    M2C_FIELD(temp_v0, f32 *, 0x2C) = 10000.0f;
    var_a0 = 0;
    M2C_FIELD(temp_v0, f32 *, 0x34) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x10);
    M2C_FIELD(temp_v0, f32 *, 0x38) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x18);
    temp_v1 = M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(temp_v0, s32 *, 0x10) = temp_v1;
    if (temp_v1 & 2) {
        var_v0_4 = func_80270438(arg0, temp_v0);
        goto block_35;
    }
    if (temp_v1 & 8) {
        var_v0_4 = func_8027A1F4(arg0, (s32) temp_v0);
        goto block_35;
    }
    if (temp_v1 & 4) {
        var_v0_4 = func_802870A8();
        goto block_35;
    }
    if (temp_v1 & 1) {
        var_v0_4 = func_80244F34(arg0, (s32) temp_v0);
block_35:
        var_a0 = var_v0_4;
    }
    if (var_a0 != 0) {
        func_80270080(temp_v0);
        func_80231408(arg0, 0x20000);
        M2C_FIELD(arg0, f32 *, 0x68) = (f32) M2C_FIELD(temp_v0, f32 *, 0x18);
        M2C_FIELD(arg0, f32 *, 0x6C) = 1.0f;
        M2C_FIELD(temp_v0, void **, 8) = arg0;
        M2C_FIELD(temp_v0, void **, 0xC) = arg0;
        return;
    }
    free(temp_v0);
}

void func_80270BA4(u8 *arg0) {
    s16 temp_v0;

    temp_v0 = func_80270B4C((s32) arg0);
    if (temp_v0 != -1) {
        *(s16 *)((u8 *)&D_802AFCF8 + (temp_v0 * 0x30)) = 0;
        func_802702EC(temp_v0);
        func_802313DC(arg0, 0x10000);
        func_80232AA8((s32) arg0);
        func_802313DC(arg0, 0x200000);
        func_802313DC(arg0, 0x600000);
    }
}

s16 func_80270B4C(s32 arg0) {
    s16 var_v1;

    var_v1 = 0;
loop_1:
    if (arg0 == M2C_FIELD((D_802AFCE8 + (var_v1 * 0x30)), s32 *, 0xC)) {
        return var_v1;
    }
    var_v1 += 1;
    if (var_v1 >= 5) {
        return -1;
    }
    goto loop_1;
}

void func_80270B20(u8 *arg0) {
    func_80270A80((s32 *) arg0);
    free(arg0);
}

void func_80270A80(s32 *arg0) {
    Node87 *var_a1;
    Node87 *var_v1;
    s32 var_v0;

    if ((D_802AFE58.next != NULL) && ((s32) arg0 != (s32) NULL)) {
        var_v1 = &D_802AFDE0;
        var_v0 = 0;
        if (D_802AFDE0.next->next != NULL) {
            var_a1 = D_802AFDE0.next;
loop_4:
            if ((s32) arg0 == (s32) var_a1) {
                var_v0 = 1;
            } else {
                var_v1 = var_a1;
                var_a1 = var_a1->next;
                if (var_a1->next != NULL) {
                    goto loop_4;
                }
            }
        }
        if (var_v0 == 1) {
            var_v1->next = (Node87 *) *arg0;
            D_802AFE58.next -= 1;
        }
    }
}

void func_80270770(s16 arg0, s16 arg1) {
    s32 pad[2];
    f32 speed;
    f32 h;
    Obj8E *o;
    Ctl87 *c;
    Obj8E *obj;
    s32 ok;

    if (func_80270714(arg0) == 0) {
        return;
    }
    obj = (Obj8E *) func_80270714(arg0);
    switch (arg1) {
        case 0:
            speed = 0.0f;
            h = 0.0f;
            break;
        case 1:
            speed = 25.0f;
            h = 8.25f;
            break;
        case 2:
            speed = 25.0f;
            h = 11.0f;
            break;
        case 3:
            speed = 25.0f;
            h = 14.0f;
            break;
        default:
            speed = 10.0f;
            break;
    }
    c = malloc(sizeof(Ctl87));
    o = func_802443F4(arg0);
    c->obj = obj;
    c->unk14 = func_802704F8(o->unk40->rot);
    c->unk18 = speed;
    c->unk20 = 1;
    c->unk28 = 0;
    c->unk16 = 0;
    c->unk1C = h;
    c->unk24 = 0.0f;
    c->unk30 = 0;
    c->unk2C = 10000.0f;
    ok = 0;
    c->unk34 = obj->unk40->x;
    c->unk38 = obj->unk40->z;
    c->flags = SLOTS[arg0].unk8;
    if (c->flags & 2) {
        ok = func_80270438((u8 *) obj, (s32 *) c);
    } else if (c->flags & 8) {
        ok = func_8027A1F4(obj, (s32) c);
    } else if (c->flags & 4) {
        ok = func_802870A8(obj, c);
    } else if (c->flags & 1) {
        ok = func_80244F34(obj, (s32) c);
    }
    if (ok != 0) {
        func_80270080((s32 *) c);
        func_80231408(obj, 0x20000);
        obj->unk68 = c->unk18;
        obj->unk6C = 1.0f;
        c->unk8 = obj;
        c->unkC = obj;
        func_802702EC(arg0);
        func_802313DC(obj, 0x10000);
        SLOTS[arg0].unk10 = 0;
        func_80232AA8((s32) obj);
        func_802313DC(obj, 0x200000);
        func_802313DC(obj, 0x600000);
        return;
    }
    free(c);
}

s32 func_80270714(s16 arg0) {
    if (func_802702BC(arg0) != 0) {
        return 0;
    }
    return SLOTS[arg0].unkC;
}

s16 func_802704F8(f32 arg0) {
    arg0 = (arg0 >= 360.0f) ? arg0 - 360.0f : ((arg0 < 0.0f) ? arg0 + 360.0f : arg0);
    if (arg0 > 337.0f || arg0 <= 22.0f) {
        return 4;
    }
    if (arg0 > 22.0f && arg0 <= 67.0f) {
        return 3;
    }
    if (arg0 > 67.0f && arg0 <= 112.0f) {
        return 2;
    }
    if (arg0 > 112.0f && arg0 <= 157.0f) {
        return 1;
    }
    if (arg0 > 157.0f && arg0 <= 202.0f) {
        return 0;
    }
    if (arg0 > 202.0f && arg0 <= 247.0f) {
        return 7;
    }
    if (arg0 > 247.0f && arg0 <= 292.0f) {
        return 6;
    }
    if (arg0 > 292.0f && arg0 <= 337.0f) {
        return 5;
    }
    return 4;
}

s32 func_80270438(u8 *arg0, s32 *arg1) {
    s16 *sp1C;
    s16 *temp_v0;
    s16 *var_v1;

    temp_v0 = func_802703B4(arg0);
    var_v1 = temp_v0;
    if (M2C_FIELD(temp_v0, s16 *, 0x10) & 0x100) {
        sp1C = temp_v0;
        func_80232A34(M2C_FIELD(temp_v0, s32 *, 0x1C));
        var_v1 = sp1C;
    }
    M2C_FIELD(var_v1, s16 *, 0x64) = (s16) (M2C_FIELD(var_v1, s16 *, 0x64) & 0xFFEF);
    M2C_FIELD(var_v1, s32 *, 0x30) = (s32) M2C_FIELD(var_v1, s32 *, 0x1C);
    M2C_FIELD(var_v1, s16 *, 0x64) = (s16) (M2C_FIELD(var_v1, s16 *, 0x64) | 0x200);
    sp1C = var_v1;
    func_80231408(arg0, 0x20000);
    M2C_FIELD(var_v1, s32 **, 0x38) = arg1;
    if (!(M2C_FIELD(var_v1, s16 *, 0x10) & 2)) {
        M2C_FIELD(var_v1, s16 *, 0x64) = (s16) (M2C_FIELD(var_v1, s16 *, 0x64) | 2);
    }
    if (M2C_FIELD(var_v1, s16 *, 0x10) & 0x400) {
        M2C_FIELD(var_v1, s16 *, 0x68) = 0x3C;
    } else {
        M2C_FIELD(var_v1, s16 *, 0x68) = 0x96;
    }
    return 1;
}

s16 *func_802703B4(u8 *arg0) {
    s16 *var_a1;
    s16 *var_v1;
    s32 var_v0;

    var_v1 = D_8008F44C;
    var_a1 = M2C_FIELD(var_v1, s16 **, 0x14);
    if (var_a1 != NULL) {
loop_2:
        var_v0 = 0;
        if (M2C_FIELD(var_v1, f32 *, 0x40) != 1e7f) {
            var_v0 = 1;
        }
        if ((var_v0 != 0) && ((s32) arg0 == M2C_FIELD(var_v1, s32 *, 0x1C))) {
            return var_v1;
        }
        var_v1 = var_a1;
        var_a1 = M2C_FIELD(var_a1, s16 **, 0x14);
        if (var_a1 == NULL) {
            /* Duplicate return node #9. Try simplifying control flow for better match */
            return NULL;
        }
        goto loop_2;
    }
    return NULL;
}

s32 func_80270384(u8 *arg0) {
    if (M2C_FIELD(arg0, f32 *, 0x40) != 1e7f) {
        return 1;
    }
    return 0;
}

void func_8027036C(s16 *arg0, s32 arg1) {
    *arg0 &= ~arg1;
}

void func_80270354(s16 *arg0, s32 arg1) {
    *arg0 |= arg1;
}

void func_802702EC(s16 arg0) {
    s32 var_v0;
    u8 *temp_v0;

    if (arg0 >= 0) {
        var_v0 = 1;
        if (arg0 < 5) {
            var_v0 = 0;
        }
    } else {
        var_v0 = 1;
    }
    if (var_v0 == 0) {
        temp_v0 = (arg0 * 0x30) + D_802AFCE8;
        M2C_FIELD(temp_v0, s32 *, 0xC) = 0;
        M2C_FIELD(temp_v0, f32 *, 0x24) = 0.0f;
        M2C_FIELD(temp_v0, f32 *, 0x20) = 0.0f;
        M2C_FIELD(temp_v0, f32 *, 0x1C) = 0.0f;
        M2C_FIELD(temp_v0, f32 *, 0x28) = 0.0f;
    }
}

s32 func_802702BC(s16 arg0) {
    if (arg0 >= 0 && arg0 < 5) {
        return 0;
    }
    return 1;
}

void *func_802700EC(u8 *arg0, u8 *arg1, s16 arg2, f32 arg3) {
    s32 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;

    if (M2C_FIELD(arg0, s32 *, 8) & 0x20000) {
loop_1:
        func_80239094();
        goto loop_1;
    }
    temp_v0 = malloc(0x3C);
    func_80270080(temp_v0);
    M2C_FIELD(temp_v0, void **, 4) = arg0;
    M2C_FIELD(temp_v0, void **, 8) = arg0;
    M2C_FIELD(temp_v0, void **, 0xC) = arg0;
    M2C_FIELD(temp_v0, s32 *, 0x10) = (s32) M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(temp_v0, s16 *, 0x14) = func_8026FFA0(arg2);
    M2C_FIELD(temp_v0, f32 *, 0x18) = 22.5f;
    M2C_FIELD(temp_v0, s32 *, 0x20) = 1;
    M2C_FIELD(temp_v0, s16 *, 0x16) = 0;
    M2C_FIELD(temp_v0, f32 *, 0x1C) = arg3;
    M2C_FIELD(temp_v0, f32 *, 0x24) = 0.0f;
    M2C_FIELD(temp_v0, s32 *, 0x30) = 0;
    M2C_FIELD(temp_v0, f32 *, 0x2C) = 10000.0f;
    M2C_FIELD(temp_v0, f32 *, 0x34) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x10);
    M2C_FIELD(temp_v0, f32 *, 0x38) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x18);
    if (M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), f32 *, 0x14) <= M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14)) {
        func_80231408(arg0, 0x20000);
        temp_v0_2 = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(arg0, f32 *, 0x68) = 22.5f;
        M2C_FIELD(arg0, f32 *, 0x6C) = 2.0f;
        func_8028A81C(0, M2C_FIELD(temp_v0_2, f32 *, 0x10), M2C_FIELD(temp_v0_2, f32 *, 0x14) + 100.0f, M2C_FIELD(temp_v0_2, f32 *, 0x18), 0);
        if (M2C_FIELD(arg0, s32 *, 8) & 2) {
            temp_v0_3 = M2C_FIELD(arg0, void **, 0x40);
            func_8026C51C(0x23, M2C_FIELD(temp_v0_3, f32 *, 0x10), M2C_FIELD(temp_v0_3, f32 *, 0x14), M2C_FIELD(temp_v0_3, f32 *, 0x18));
        } else {
            temp_v0_4 = M2C_FIELD(arg0, void **, 0x40);
            func_8026C51C(0x22, M2C_FIELD(temp_v0_4, f32 *, 0x10), M2C_FIELD(temp_v0_4, f32 *, 0x14), M2C_FIELD(temp_v0_4, f32 *, 0x18));
        }
    } else {
        M2C_FIELD(arg0, f32 *, 0x68) = 0.0f;
        M2C_FIELD(arg0, f32 *, 0x6C) = 2.0f;
    }
    return temp_v0;
}

void func_80270080(s32 *arg0) {
    Node87 *var_v0;
    Node87 *var_v1;

    var_v0 = &D_802AFDE0;
    if (D_802AFDE0.next->next != NULL) {
        var_v1 = D_802AFDE0.next;
        do {
            var_v0 = var_v1;
            var_v1 = var_v1->next;
        } while (var_v1->next != NULL);
    }
    *arg0 = (s32) var_v0->next;
    var_v0->next = (Node87 *) arg0;
    D_802AFE58.next += 1;
}

s32 func_8026FFA0(s16 arg0) {
    s32 sp4;

    switch (arg0) {                                 /* irregular */
    case 0x1:
        sp4 = 9;
        break;
    case 0x0:
        sp4 = 0;
        break;
    case 0x20:
        sp4 = 1;
        break;
    case 0x40:
        sp4 = 2;
        break;
    case 0x60:
        sp4 = 3;
        break;
    case 0x80:
        sp4 = 4;
        break;
    case 0xA0:
        sp4 = 5;
        break;
    case 0xC0:
        sp4 = 6;
        break;
    case 0xE0:
        sp4 = 7;
        break;
    }
    return sp4;
}

void func_8026FF94(s32 arg0) {
    D_802AFC58 = arg0;
}

void func_8026FF64(s32 arg0) {
    func_8026FC08(arg0);
    func_8026F8B0();
    D_802AFC58 = 0x2010;
}

void func_8026FC08(s32 arg0) {
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_t0;
    s32 temp_t6_3;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s4;
    s32 var_s5;
    s32 var_v0;
    s32 var_v1;
    u8 *var_fp;
    u8 *var_fp_2;
    u8 *var_s3_2;
    u8 temp_t2;
    u8 temp_t2_2;
    u8 temp_t2_3;
    u8 temp_t3;
    u8 temp_t5;
    u8 temp_t6;
    u8 temp_t6_2;
    u8 *temp_s3;
    u8 *temp_s3_2;
    u8 *temp_v0;
    u8 *var_s1;
    u8 *var_s3;

    D_802AFC50 = arg0;
    D_800B15D8->unk4 = 0;
    D_800B15D8->unk8 = 0;
    temp_v0 = func_8026CE28(arg0);
    D_802AFC6C = temp_v0;
    D_802AFC60 = 0.0f;
    D_802AFC64 = 1.6333334f;
    D_802AFC68 = 0.0f;
    temp_t6 = M2C_FIELD(temp_v0, u8 *, 0);
    temp_t7 = temp_t6 & 0xFF;
    D_800B15D8->unk0 = temp_t6;
    D_800B15D8->unk1 = (u8) M2C_FIELD(temp_v0, u8 *, 1);
    D_800B15D8->unk2 = (u8) M2C_FIELD(temp_v0, u8 *, 2);
    D_800B15D8->unk3 = (u8) M2C_FIELD(temp_v0, u8 *, 3);
    temp_t2 = M2C_FIELD(temp_v0, u8 *, 4);
    D_800B15D8->unkC = temp_t2;
    var_s3 = temp_v0 + 5;
    var_fp = D_800B15D8;
    var_s5 = 0;
    D_802AFC5C = (f32) -(temp_t2 & 0x7F) * 100.0f;
    if (temp_t7 > 0) {
        do {
            temp_t6_2 = M2C_FIELD(var_s3, u8 *, 0);
            temp_s3 = var_s3 + 2;
            M2C_FIELD(var_fp, u8 *, 0xE) = temp_t6_2;
            M2C_FIELD(var_fp, u8 *, 0xF) = (u8) M2C_FIELD(temp_s3, u8 *, -1);
            temp_v0_2 = (temp_t6_2 & 0xFF) + ((s32) (D_800B15D8->unk1 + 7) >> 3);
            if (D_800B15D8->unk4 < temp_v0_2) {
                D_800B15D8->unk4 = temp_v0_2;
            }
            temp_v1 = M2C_FIELD(var_fp, u8 *, 0xF) + ((s32) (D_800B15D8->unk3 + 7) >> 3);
            if (D_800B15D8->unk8 < temp_v1) {
                D_800B15D8->unk8 = temp_v1;
            }
            temp_lo = M2C_FIELD(var_fp, u8 *, 0xF) * M2C_FIELD(var_fp, u8 *, 0xE);
            var_s5 += 1;
            var_fp += 0xC34;
            M2C_FIELD(var_fp, u8 *, -0xC24) = (u8) M2C_FIELD(var_s3, u8 *, 2);
            var_s3 = temp_s3 + 1 + (temp_lo * 0x82);
        } while (var_s5 != temp_t7);
        var_s5 = 0;
    }
    var_s3_2 = temp_v0 + 5;
    if (temp_t7 > 0) {
        var_fp_2 = D_800B15D8;
        do {
            temp_t2_2 = *var_s3_2;
            temp_s3_2 = var_s3_2 + 2;
            M2C_FIELD(var_fp_2, u8 *, 0xE) = temp_t2_2;
            temp_t3 = M2C_FIELD(temp_s3_2, u8 *, -1);
            temp_lo_2 = (temp_t3 & 0xFF) * (temp_t2_2 & 0xFF);
            M2C_FIELD(var_fp_2, u8 *, 0xF) = temp_t3;
            var_s4 = 0;
            temp_t6_3 = D_800B15D8->unk8 * 8;
            var_v1 = temp_t6_3;
            if (temp_t6_3 > 0) {
                var_v0 = D_800B15D8->unk4 * 8;
                do {
                    var_s0 = 0;
                    if (var_v0 > 0) {
                        do {
                            func_8026D620(var_s0, D_800B15D8->unk2 + var_s5, var_s4, 0x2010U);
                            var_s0 += 1;
                            temp_t0 = D_800B15D8->unk4 * 8;
                            var_v0 = temp_t0;
                        } while (var_s0 < temp_t0);
                        var_v1 = D_800B15D8->unk8 * 8;
                    }
                    var_s4 += 1;
                } while (var_s4 < var_v1);
                var_s4 = 0;
            }
            var_s3_2 = temp_s3_2 + 1;
            if (temp_lo_2 > 0) {
                var_s1 = &D_800B15D8[var_s5];
                do {
                    temp_t2_3 = *var_s3_2;
                    var_s3_2 += 2;
                    M2C_FIELD(var_s1, u8 *, 0x12) = temp_t2_3;
                    var_s0_2 = 0;
                    M2C_FIELD(var_s1, u8 *, 0x13) = (u8) M2C_FIELD(var_s3_2, u8 *, -1);
loop_20:
                    temp_t5 = M2C_FIELD(var_s3_2, u8 *, 1);
                    temp_t7_2 = M2C_FIELD(var_s3_2, u8 *, 0) << 8;
                    var_s3_2 += 2;
                    func_8026D620((M2C_FIELD(var_s1, u8 *, 0x12) * 8) + D_800B15D8->unk1 + (var_s0_2 % 8), D_800B15D8->unk2 + var_s5, (M2C_FIELD(var_s1, u8 *, 0x13) * 8) + D_800B15D8->unk3 + (var_s0_2 >> 3), temp_t5 + temp_t7_2);
                    var_s0_2 += 1;
                    if (var_s0_2 != 0x40) {
                        goto loop_20;
                    }
                    var_s4 += 1;
                    var_s1 += 0x82;
                } while (var_s4 != temp_lo_2);
            }
            var_s5 += 1;
            var_fp_2 += 0xC34;
        } while (var_s5 != temp_t7);
    }
}

void func_8026F8B0() {
    s32 sp5C;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s16 temp_v0_3;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s2_2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_fp;
    s32 var_s0_2;
    s32 var_s7;
    s32 var_v0;
    s32 var_v1;
    u16 temp_v0_2;
    u8 temp_s2;
    u8 var_s0;
    u8 var_s1;
    u8 *temp_s0;

    temp_s2 = D_800B15D8->unk0;
    var_fp = 0;
    if ((s32) temp_s2 > 0) {
        var_v1 = D_800B15D8->unk8 * 8;
        do {
            var_s1 = D_800B15D8->unk3;
            if ((s32) var_s1 < var_v1) {
                var_v0 = D_800B15D8->unk4 * 8;
                do {
                    var_s0 = D_800B15D8->unk1;
                    if ((s32) var_s0 < var_v0) {
                        do {
                            func_8026F5E8((s32) var_s0, var_fp, (s32) var_s1);
                            var_s0 += 1;
                            temp_t8 = D_800B15D8->unk4 * 8;
                            var_v0 = temp_t8;
                        } while ((s32) var_s0 < temp_t8);
                        var_v1 = D_800B15D8->unk8 * 8;
                    }
                    var_s1 += 1;
                } while ((s32) var_s1 < var_v1);
            }
            var_fp += 1;
        } while (var_fp != temp_s2);
        var_fp = 0;
    }
    temp_v0 = func_8027DF9C();
    if (temp_v0 > 0) {
        do {
loop_11:
            sp5C = 0;
            temp_s3 = func_80234248(D_800B15D8->unk0 - 1) + D_800B15D8->unk2;
            temp_s0 = &D_800B15D8[temp_s3];
            temp_s4 = func_80234248((M2C_FIELD(temp_s0, u8 *, 0xE) * 8) - 1) + D_800B15D8->unk1;
            temp_s5 = func_80234248((M2C_FIELD(temp_s0, u8 *, 0xF) * 8) - 1) + D_800B15D8->unk3;
            temp_v0_2 = func_8026D7D8(temp_s4, temp_s3, temp_s5);
            if (!(temp_v0_2 & 0x70) && !(temp_v0_2 & 0x60)) {
                var_s0_2 = 0;
                sp40 = 0;
                sp44 = 0;
                sp48 = 0;
                sp4C = 0;
                sp50 = 0;
                var_s7 = 0;
                temp_v0_3 = func_8027DF40(0x20);
                if (temp_v0_3 != 1) {
                    if (temp_v0_3 != 2) {
                        temp_s1 = temp_s4 + 1;
                        if (temp_v0_3 != 3) {

                        } else {
                            temp_s2_2 = temp_s5 + 1;
                            var_s7 = func_8026D7D8(temp_s1, temp_s3, temp_s5) & 0x70;
                            sp50 = func_8026D7D8(temp_s4, temp_s3, temp_s2_2) & 0x70;
                            temp_s0_2 = temp_s3 + 1;
                            sp4C = func_8026D7D8(temp_s1, temp_s3, temp_s2_2) & 0x70;
                            sp48 = func_8026D7D8(temp_s4, temp_s0_2, temp_s5) & 0x70;
                            sp44 = func_8026D7D8(temp_s1, temp_s0_2, temp_s5) & 0x70;
                            sp40 = func_8026D7D8(temp_s4, temp_s0_2, temp_s2_2) & 0x70;
                            var_s0_2 = func_8026D7D8(temp_s1, temp_s0_2, temp_s2_2) & 0x70;
                        }
                    } else {
                        var_s7 = func_8026D7D8(temp_s4 + 1, temp_s3, temp_s5) & 0x70;
                        sp50 = func_8026D7D8(temp_s4, temp_s3, temp_s5 + 1) & 0x70;
                    }
                } else {
                    var_s7 = func_8026D7D8(temp_s4, temp_s3 + 1, temp_s5) & 0x70;
                }
                if ((var_s7 | sp50 | sp4C | sp48 | sp44 | sp40 | var_s0_2) == 0) {
                    sp5C = func_8026F068(temp_s4, temp_s3, temp_s5, 0x20);
                }
            }
            if (sp5C == 0) {
                goto loop_11;
            }
            var_fp += 1;
        } while (var_fp < temp_v0);
    }
}

void func_8026F5E8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 sp28;
    s32 sp24;
    f32 pos[3];

    sp28 = D_802AC5D0 & 4;
    sp24 = *func_8023A840() & 6;
    temp_v0 = func_8026D7D8(arg0, arg1, arg2);
    if (temp_v0 & 0x380) {
        pos[0] = arg0 * 100.0f;
        pos[1] = func_8026E2B0((f32) arg1);
        pos[2] = arg2 * 100.0f;
        switch (temp_v0 & 0x380) {
        case 0x80:
            func_802511EC(0, arg0, arg1, arg2);
            break;
        case 0x100:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(0, pos[0], pos[1], pos[2]);
            } else {
                func_802511EC(1, arg0, arg1, arg2);
            }
            break;
        case 0x180:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(1, pos[0], pos[1], pos[2]);
            } else {
                func_802511EC(2, arg0, arg1, arg2);
            }
            break;
        case 0x200:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(2, pos[0], pos[1], pos[2]);
            } else {
                func_802511EC(3, arg0, arg1, arg2);
            }
            break;
        case 0x280:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(3, pos[0], pos[1], pos[2]);
            }
            break;
        case 0x300:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(4, pos[0], pos[1], pos[2]);
            }
            break;
        case 0x380:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(5, pos[0], pos[1], pos[2]);
            }
            break;
        }
    }
    if (temp_v0 & 0x60) {
        func_8026F068(arg0, arg1, arg2, temp_v0 & 0x60);
    }
}

s32 func_8026F068(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 ok;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 g;
    s32 h;
    s32 type;
    s32 ret;

    ret = 0;
    ok = 1;
    type = func_8027DF40(arg3);
    if (type == 2 || type == 3) {
        a = func_8026D7D8(arg0 - 1, arg1, arg2) & 0x60;
        b = func_8026D7D8(arg0 - 1, arg1, arg2 + 1) & 0x60;
        c = func_8026D7D8(arg0, arg1, arg2 + 1) & 0x60;
        d = func_8026D7D8(arg0, arg1, arg2 - 1) & 0x60;
        e = func_8026D7D8(arg0 + 1, arg1, arg2 - 1) & 0x60;
        f = func_8026D7D8(arg0 + 1, arg1, arg2) & 0x60;
        g = func_8026D7D8(arg0 - 1, arg1, arg2) & 0x60;
        h = func_8026D7D8(arg0 - 1, arg1, arg2 - 1) & 0x60;
        if ((a == arg3 && b == arg3 && c == arg3) || (d == arg3 && e == arg3 && f == arg3) ||
            (g == arg3 && h == arg3 && (func_8026D7D8(arg0, arg1, arg2 - 1) & 0x60) == arg3)) {
            ok = 0;
        }
    }
    if (type == 1 && arg3 == (func_8026D7D8(arg0, arg1 - 1, arg2) & 0x60)) {
        ok = 0;
    }
    if (ok != 0 && type == 3 && arg1 != 0 && arg3 == (func_8026D7D8(arg0, arg1 - 1, arg2) & 0x60)) {
        ok = 0;
    }
    if (ok == 1) {
        if (func_8027E8EC(arg3, arg0, arg1, arg2) != 0) {
            ret = 1;
            switch (type) {
                case 0:
                    func_8026EEF0(arg0, arg1, arg2, arg3, 1);
                    break;
                case 1:
                    func_8026EEF0(arg0, arg1, arg2, arg3, 1);
                    func_8026EEF0(arg0, arg1 + 1, arg2, arg3, 1);
                    break;
                case 2:
                    func_8026EEF0(arg0, arg1, arg2, arg3, 1);
                    func_8026EEF0(arg0 + 1, arg1, arg2, arg3, 1);
                    func_8026EEF0(arg0, arg1, arg2 + 1, arg3, 1);
                    func_8026EEF0(arg0 + 1, arg1, arg2 + 1, arg3, 1);
                    break;
                case 3:
                    func_8026EEF0(arg0, arg1, arg2, arg3, 1);
                    func_8026EEF0(arg0 + 1, arg1, arg2, arg3, 1);
                    func_8026EEF0(arg0, arg1, arg2 + 1, arg3, 1);
                    func_8026EEF0(arg0 + 1, arg1, arg2 + 1, arg3, 1);
                    func_8026EEF0(arg0, arg1 + 1, arg2, arg3, 1);
                    func_8026EEF0(arg0 + 1, arg1 + 1, arg2, arg3, 1);
                    func_8026EEF0(arg0, arg1 + 1, arg2 + 1, arg3, 1);
                    func_8026EEF0(arg0 + 1, arg1 + 1, arg2 + 1, arg3, 1);
                    break;
            }
        } else {
            func_8026EEF0(arg0, arg1, arg2, 0x60, 0);
        }
    }
    return ret;
}

void func_8026F02C() {
    if (D_802AFC6C != NULL) {
        func_8026CCBC(D_802AFC50);
        D_802AFC6C = NULL;
    }
}

u16 func_8026EFD0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp1C;
    s32 var_v1;
    u16 temp_a0;

    var_v1 = 0;
    if (D_802AC89C == 1) {
        D_802AC89C = 0;
        var_v1 = 1;
    }
    sp1C = var_v1;
    temp_a0 = func_8026D7D8(arg0, arg1, arg2);
    if (var_v1 == 1) {
        D_802AC89C = 1;
    }
    return temp_a0;
}

u16 func_8026EF50(f32 arg0, f32 arg1, f32 arg2) {
    s32 sp54;
    s32 sp24[3];
    s32 var_v1;
    u16 temp_a0;

    var_v1 = 0;
    if (D_802AC89C == 1) {
        D_802AC89C = 0;
        var_v1 = 1;
    }
    sp54 = var_v1;
    func_8026DCAC(arg0, arg1, arg2, sp24, 2);
    temp_a0 = func_8026D7D8(sp24[0], sp24[1], sp24[2]);
    if (sp54 == 1) {
        D_802AC89C = 1;
    }
    return temp_a0;
}

void func_8026EEF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u16 temp_v0;
    u16 var_a3;

    temp_v0 = func_8026D7D8(arg0, arg1, arg2);
    if (arg4 == 1) {
        var_a3 = temp_v0 | arg3;
    } else {
        var_a3 = temp_v0 & (arg3 ^ 0xFFFF);
    }
    func_8026D620(arg0, arg1, arg2, var_a3);
}

u8 func_8026EE18(f32 arg0) {
    s32 sp4;
    s32 temp_a3;
    s32 temp_ft2;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    s32 var_v1_2;
    u8 *var_t0;
    u8 temp_v0;

    temp_a3 = D_800B15D8->unk0 + 1;
    var_a0 = 0;
    var_a1 = 0;
    if (temp_a3 > 0) {
        var_t0 = D_800B15D8;
        temp_ft2 = (s32) (arg0 * 0.01f);
loop_2:
        if (temp_ft2 < var_a0) {
            var_v1_2 = var_a1;
            if (var_a1 > 0) {
                var_v1_2 = var_a1 - 1;
            }
            sp4 = var_v1_2;
        } else if (var_a0 == temp_ft2) {
            sp4 = var_a1;
        } else {
            temp_v0 = M2C_FIELD(var_t0, u8 *, 0x10);
            var_a1 += 1;
            var_t0 += 0xC34;
            var_a0 += temp_v0;
            if (var_a1 < temp_a3) {
                goto loop_2;
            }
        }
    }
    var_v1 = sp4;
    if (D_800B15D8->unk0 < var_a1) {
        var_v1 = D_800B15D8->unk0;
    }
    if (arg0 < 0.0f) {
        var_v1 = -1;
    }
    return (u8) var_v1;
}

void func_8026EE10(s32 arg0) {

}

void func_8026EE08(s32 arg0) {

}

void func_8026ECF4() {
    s32 var_s1;
    u8 *var_s0;
    u8 *var_s0_2;

    func_80297D38("*** MAP INFORMATION ***\n");
    func_80297D38("Offset:%d,%d,%d\n", D_800B15D8->unk1, D_800B15D8->unk2, D_800B15D8->unk3);
    func_80297D38("Layer :%d\n", D_800B15D8->unk0);
    func_80297D38("Size  :%d x %d\n", D_800B15D8->unk4, D_800B15D8->unk8);
    var_s1 = 0;
    if (D_800B15D8->unk0 > 0) {
        var_s0 = D_800B15D8;
        do {
            func_80297D38("   (%d):%d x %d\n", var_s1, M2C_FIELD(var_s0, u8 *, 0xE), M2C_FIELD(var_s0, u8 *, 0xF));
            var_s1 += 1;
            var_s0 += 0xC34;
        } while (var_s1 < D_800B15D8->unk0);
        var_s1 = 0;
    }
    func_80297D38("Layer Unit\n");
    var_s0_2 = D_800B15D8;
    if (D_800B15D8->unk0 > 0) {
        do {
            func_80297D38("   [%d]:%d\n", var_s1, M2C_FIELD(var_s0_2, u8 *, 0x10));
            var_s1 += 1;
            var_s0_2 += 0xC34;
        } while (var_s1 < D_800B15D8->unk0);
    }
}

void func_8026ECE8(f32 arg0) {
    D_802AFC5C = arg0;
}

void func_8026ECC0() {
    D_802AFC60 = 0.0f;
    D_802AFC64 = 1.6333334f;
    D_802AFC68 = 0.0f;
}

f32 func_8026EAF8(u8 *arg0) {
    s32 sp68[3];
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp3C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fv1;
    s32 temp_a1;
    s32 temp_t9;
    s32 var_s0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 var_a0;
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    temp_fa0 = M2C_FIELD(temp_v0, f32 *, 0x10);
    temp_fv0 = M2C_FIELD(temp_v0, f32 *, 0x18);
    sp58 = temp_fa0 + 50.0f;
    temp_fa1 = M2C_FIELD(temp_v0, f32 *, 0x14);
    sp54 = temp_fa1 + 50.0f;
    sp50 = temp_fv0 + 50.0f;
    func_8026DCAC(temp_fa0, temp_fa1, temp_fv0, sp68, 2);
    temp_a1 = sp68[1];
    temp_v0_2 = func_8026D7D8(sp68[0], temp_a1, sp68[2]);
    if (temp_v0_2 & 0x60) {
        var_a0 = 0xF;
    } else {
        var_a0 = temp_v0_2 & 0xF;
    }
    if (var_a0 == 0xF) {
        do {
            temp_a1 = temp_a1 + 1;
            var_s0 = 0;
            temp_v0_3 = func_8026D7D8(sp68[0], temp_a1, sp68[2]);
            temp_t9 = temp_v0_3 & 0x60;
            if ((temp_a1 < D_800B15D8->unk0) && ((temp_t9 != 0) || ((temp_v0_3 & 0xF) == 0xF))) {
                var_s0 = 1;
            }
        } while (var_s0 != 0);
        if (temp_a1 >= D_800B15D8->unk0) {
            var_fv1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14);
        } else {
            sp3C = func_8026E2B0(temp_a1);
            if (func_8026E278((u16) temp_v0_3) != 0) {
                var_fv1 = func_8026E3AC(temp_fa0 + 50.0f, sp3C + 50.0f, temp_fv0 + 50.0f);
            } else {
                var_fv1 = sp3C;
            }
        }
    } else if (func_8026E278(var_a0) != 0) {
        var_fv1 = func_8026E3AC(sp58, sp54, sp50);
    } else {
        var_fv1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14);
    }
    return var_fv1;
}

f32 func_8026E938(u8 *arg0) {
    f32 sp80;
    s32 sp68[3];
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fv1;
    s32 temp_s0;
    s32 temp_v1;
    s32 var_s1;
    u16 temp_s2;
    u16 temp_v0;

    if ((D_802AFC54 != 0) && (func_8026E8E0((s32) arg0) != 0)) {
        var_fv1 = M2C_FIELD(arg0, f32 *, 0x14);
    } else {
        temp_fv0 = M2C_FIELD(arg0, f32 *, 0x18);
        temp_fa0 = M2C_FIELD(arg0, f32 *, 0x10);
        temp_fa1 = M2C_FIELD(arg0, f32 *, 0x14);
        func_8026DCAC(temp_fa0, temp_fa1, temp_fv0, sp68, 2);
        var_s1 = sp68[1];
loop_4:
        temp_s0 = var_s1 - 1;
        temp_s2 = func_8026D7D8(sp68[0], var_s1, sp68[2]);
        temp_v0 = func_8026D7D8(sp68[0], temp_s0, sp68[2]);
        temp_v1 = temp_s2 & 0xF;
        if ((temp_v1 == 0) && !(temp_v0 & 0x60)) {
            var_s1 = temp_s0;
        }
        if ((temp_v1 == 0) && !(temp_v0 & 0x60) && (var_s1 >= 0)) {
            goto loop_4;
        }
        if (var_s1 >= 0) {
            if (func_8026E278(temp_s2) != 0) {
                var_fv1 = func_8026E3AC(temp_fa0 + 50.0f, temp_fa1, temp_fv0 + 50.0f);
            } else {
                sp80 = (f32) sp68[0] * 100.0f;
                var_fv1 = func_8026E2B0((s32) (f32) var_s1);
            }
        } else if (D_800B15D8->unkC < 0) {
            var_fv1 = 20000.0f;
        } else {
            var_fv1 = D_802AFC5C;
        }
    }
    return var_fv1;
}

s32 func_8026E8E0(s32 arg0) {
    u8 *var_v0;

    var_v0 = D_802A55F4;
    if (var_v0 != NULL) {
loop_1:
        if (arg0 == M2C_FIELD(var_v0, s32 *, 0x40)) {
            if (M2C_FIELD(var_v0, s32 *, 8) & 1) {
                return 1;
            }
            /* Duplicate return node #5. Try simplifying control flow for better match */
            return 0;
        }
        var_v0 = M2C_FIELD(var_v0, void **, 0x7C);
        if (var_v0 == NULL) {
            /* Duplicate return node #5. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_1;
    }
    return 0;
}

s32 func_8026E8C8() {
    return D_800B15D8->unkC >> 7;
}

f32 func_8026E8B8() {
    return D_802AFC5C;
}

void func_8026E6E4(u8 *arg0, f32 *arg1, f32 *arg2) {
    s32 sp78[3];
    M2C_UNK sp6C[3];
    f32 temp_fs3;
    f32 temp_fs4;
    f32 var_fs0;
    s32 temp_v1;
    u16 temp_v0;

    temp_fs3 = M2C_FIELD(arg0, f32 *, 0x10);
    var_fs0 = M2C_FIELD(arg0, f32 *, 0x14);
    temp_fs4 = M2C_FIELD(arg0, f32 *, 0x18);
loop_1:
    func_8026DCAC(temp_fs3, var_fs0, temp_fs4, sp78, 2);
    temp_v0 = func_8026D7D8(sp78[0], sp78[1], sp78[2]);
    temp_v1 = temp_v0 & 0xF;
    if ((temp_v1 == 0) && (var_fs0 >= 0.0f)) {
        var_fs0 -= 100.0f;
    }
    if (temp_v1 == 0) {
        if (!(var_fs0 >= 0.0f)) {

        } else {
            goto loop_1;
        }
    }
    *arg1 = 0.0f;
    switch (temp_v1) {                              /* irregular */
    case 3:
        *arg2 = 180.0f;
        break;
    case 4:
        *arg2 = 0.0f;
        break;
    case 5:
        *arg2 = 270.0f;
        break;
    case 6:
        *arg2 = 90.0f;
        break;
    default:
        *arg2 = 0.0f;
        break;
    }
    if (func_8026E278(temp_v0) != 0) {
        func_8026DFB8(temp_fs3 + 50.0f, var_fs0, temp_fs4 + 50.0f, sp6C);
        *arg1 = (f32) ((f64) func_8029CB40(sp6C[2]) * 57.29577951308232);
    }
}

s32 func_8026E608(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_t9;
    s32 var_v1;

    var_v1 = 0;
    if (arg1 & 1) {
        if (((arg0 & 0xF) == 0xF) || (var_t9 = arg1 & 2, ((arg0 & 0x60) != 0))) {
            var_v1 = 1;
            goto block_4;
        }
    } else {
block_4:
        var_t9 = arg1 & 2;
    }
    if ((var_t9 != 0) && ((temp_v0 = arg0 & 0xF, (temp_v0 == 6)) || (temp_v0 == 5))) {
        var_v1 = 1;
    }
    if ((arg1 & 4) && ((temp_v0_2 = arg0 & 0xF, (temp_v0_2 == 3)) || (temp_v0_2 == 4))) {
        var_v1 = 1;
    }
    if ((arg1 & 8) && (arg0 & 0x2000)) {
        var_v1 = 1;
    }
    if ((arg1 & 0x10) && (arg0 & 0x8000)) {
        var_v1 = 1;
    }
    temp_v0_3 = arg0 & 0xF;
    if ((arg1 & 0x20) && ((temp_v0_3 == 7) || (temp_v0_3 == 8) || (temp_v0_3 == 0xC) || (temp_v0_3 == 0xD))) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 func_8026E5CC(s32 arg0) {
    s32 temp_t6;
    s32 var_v1;

    temp_t6 = arg0 & 0xF;
    var_v1 = 0;
    switch (temp_t6) {
    case 1:
    case 2:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        var_v1 = arg0;
        break;
    }
    return var_v1;
}

f32 func_8026E3AC(f32 arg0, f32 arg1, f32 arg2) {
    s32 attr;
    Unk8026DCAC sp90;
    f32 pos[3];
    f32 sp78[3];
    f32 s;
    f32 fx;
    f32 fy;
    f32 fz;

    do {
        func_8026DCAC(arg0, arg1, arg2, &sp90, 0);
        fx = sp90.i[0];
        fz = sp90.i[2];
        fy = sp90.i[1];
        pos[0] = fx * 100.0f;
        pos[1] = func_8026E2B0(fy);
        pos[2] = fz * 100.0f;
        attr = func_8026D7D8(sp90.i[0], sp90.i[1], sp90.i[2]);
        if ((attr & 0xF) == 0 && arg1 >= 0.0f) {
            arg1 -= 100.0f;
        }
    } while ((attr & 0xF) == 0 && arg1 >= 0.0f);
    if (func_8026E278(attr) != 0) {
        func_8026DFB8(arg0, arg1, arg2, sp78);
        switch (attr & 0xF) {
        case 3:
            s = sp78[0];
            break;
        case 5:
            s = sp78[0];
            break;
        case 4:
            s = sp78[1];
            break;
        case 6:
            s = sp78[1];
            break;
        default:
            return 0.0f;
        }
        return sp78[2] * s + pos[1];
    }
    return pos[1] - 1.0f;
}

void func_8026E338(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, s32 arg4) {
    M2C_FIELD(arg3, f32 *, 0) = arg0 * 100.0f;
    M2C_FIELD(arg3, f32 *, 4) = func_8026E2B0((s32) arg1);
    M2C_FIELD(arg3, f32 *, 8) = (f32) (arg2 * 100.0f);
}

f32 func_8026E2B0(s32 arg0) {
    s32 var_v1;
    u8 *var_a0;
    u8 temp_v0;

    if (arg0 >= 0) {
        var_v1 = 0;
        if (arg0 > 0) {
            var_a0 = D_800B15D8;
            do {
                temp_v0 = M2C_FIELD(var_a0, u8 *, 0x10);
                var_a0 += 0xC34;
                var_v1 += temp_v0;
            } while ((u32) var_a0 < (u32) ((arg0 * 0xC34) + &D_800B15D8));
        }
        return (f32) var_v1 * 100.0f;
    }
    return -32700.0f;
}

s32 func_8026E278(s32 arg0) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = arg0 & 0xF;
    var_v1 = 0;
    if ((temp_v0 == 3) || (temp_v0 == 4) || (temp_v0 == 5) || (temp_v0 == 6)) {
        var_v1 = 1;
    }
    return var_v1;
}

void func_8026DFB8(f32 arg0, f32 arg1, f32 arg2, f32 *arg3) {
    Unk8026DCAC spA8;
    s32 count;
    f32 base;
    f32 scale;
    f32 lo;
    f32 hi;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0_2;
    s32 temp_a0;
    s32 temp_v0;
    s32 kind;
    s32 dz;
    s32 dx;
    s32 iz;
    s32 ix;
    s32 nz;
    s32 nx;
    s32 pz;
    s32 px;

    scale = 0.0f;
    count = 0;
    func_8026DCAC(arg0, arg1, arg2, &spA8, 0);
    kind = func_8026D7D8(spA8.i[0], spA8.i[1], spA8.i[2]) & 0xF;
    nz = 0;
    pz = 0;
    nx = 0;
    px = 0;
    if ((kind == 3) || (kind == 4)) {
        scale = 100.0f;
        dx = 0;
        dz = 1;
        ix = 0;
        iz = 1;
        base = spA8.f[2];
    } else if ((kind == 5) || (kind == 6)) {
        scale = 100.0f;
        dx = 1;
        dz = 0;
        ix = 1;
        iz = 0;
        base = spA8.f[0];
    } else {
        hi = 0.0f;
        kind = 0;
        lo = 0.0f;
    }
    if (kind != 0) {
        do {
            temp_a0 = func_8026D7D8(spA8.i[0] + px + dx, spA8.i[1], spA8.i[2] + pz + dz) & 0xF;
            if (kind == temp_a0) {
                px += ix;
                pz += iz;
            }
        } while (temp_a0 == kind);
        do {
            temp_a0 = func_8026D7D8((spA8.i[0] - nx) - dx, spA8.i[1], (spA8.i[2] - nz) - dz) & 0xF;
            if (kind == temp_a0) {
                nx += ix;
                nz += iz;
            }
        } while (temp_a0 == kind);
        temp_v0 = px + pz;
        count = temp_v0 + nx + nz + 1;
        lo = ((f32) (nx + nz) * scale) + base;
        hi = ((f32) temp_v0 * scale) + (scale - base);
    }
    arg3[0] = lo;
    arg3[1] = hi;
    if (count == 0) {
        var_fa0_2 = 0.0f;
    } else {
        temp_fv0 = (f32) D_800B15D8[spA8.i[1]].unk10 * 100.0f;
        temp_fv1 = (f32) count;
        temp_fa1 = temp_fv0 / (temp_fv1 * scale);
        var_fa0_2 = temp_fa1;
        if (temp_fv0 != (temp_fv1 * temp_fa1 * scale)) {
            var_fa0_2 = temp_fa1 + 0.001f;
        }
    }
    arg3[2] = var_fa0_2;
}

void func_8026DF74(f32 arg0, f32 arg1, f32 arg2) {
    s32 sp24[3];

    func_8026DCAC(arg0, arg1, arg2, sp24, 2);
    func_8026D7D8(sp24[0], sp24[1], sp24[2]);
}

void func_8026DCAC(f32 arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4) {
    s32 temp_a3;
    s32 temp_ft1;
    s32 temp_ft2;
    s32 temp_v0_2;
    s32 var_a2;
    s32 var_t1;
    s32 var_v1;
    u8 *var_a1;
    u8 temp_v0;

    temp_ft1 = (s32) (arg0 * 0.01f);
    var_t1 = 0;
    M2C_FIELD(arg3, s32 *, 0) = temp_ft1;
    M2C_FIELD(arg3, s32 *, 8) = (s32) (arg2 * 0.01f);
    if (arg0 < 0.0f) {
        M2C_FIELD(arg3, s32 *, 0) = (s32) (temp_ft1 - 1);
    }
    if (arg2 < 0.0f) {
        M2C_FIELD(arg3, s32 *, 8) = (s32) (M2C_FIELD(arg3, s32 *, 8) - 1);
    }
    var_v1 = 0;
    temp_a3 = D_800B15D8->unk0 + 1;
    var_a2 = 0;
    if (temp_a3 > 0) {
        var_a1 = D_800B15D8;
        temp_ft2 = (s32) (arg1 * 0.01f);
loop_6:
        if (temp_ft2 < var_v1) {
            if (var_a2 > 0) {
                M2C_FIELD(arg3, s32 *, 4) = (s32) (var_a2 - 1);
            } else {
                M2C_FIELD(arg3, s32 *, 4) = var_a2;
            }
        } else {
            var_t1 = var_v1;
            if (var_v1 == temp_ft2) {
                M2C_FIELD(arg3, s32 *, 4) = var_a2;
                var_t1 = var_v1;
            } else {
                temp_v0 = M2C_FIELD(var_a1, u8 *, 0x10);
                var_a2 += 1;
                var_a1 += 0xC34;
                var_v1 += temp_v0;
                if (var_a2 < temp_a3) {
                    goto loop_6;
                }
            }
        }
    }
    if (D_800B15D8->unk0 < var_a2) {
        M2C_FIELD(arg3, s32 *, 4) = D_800B15D8->unk0;
    }
    if (arg1 < 0.0f) {
        M2C_FIELD(arg3, s32 *, 4) = -1;
    }
    temp_v0_2 = M2C_FIELD(arg3, s32 *, 0);
    M2C_FIELD(arg3, f32 *, 0xC) = (f32) (arg0 - ((f32) temp_v0_2 * 100.0f));
    M2C_FIELD(arg3, f32 *, 0x10) = (f32) (arg1 - ((f32) var_t1 * 100.0f));
    M2C_FIELD(arg3, f32 *, 0x14) = (f32) (arg2 - ((f32) M2C_FIELD(arg3, s32 *, 8) * 100.0f));
    if (arg4 & 2) {
        if (M2C_FIELD(arg3, f32 *, 0xC) >= 50.0f) {
            M2C_FIELD(arg3, s32 *, 0) = (s32) (temp_v0_2 + 1);
        }
        if (M2C_FIELD(arg3, f32 *, 0x14) >= 50.0f) {
            M2C_FIELD(arg3, s32 *, 8) = (s32) (M2C_FIELD(arg3, s32 *, 8) + 1);
        }
        M2C_FIELD(arg3, f32 *, 0xC) = (f32) ((f64) M2C_FIELD(arg3, f32 *, 0xC) - 50.0);
        M2C_FIELD(arg3, f32 *, 0x14) = (f32) ((f64) M2C_FIELD(arg3, f32 *, 0x14) - 50.0);
    }
    if ((D_802AC8A0 == 1) && ((M2C_FIELD(arg3, f32 *, 0xC) == 100.0f) || (M2C_FIELD(arg3, f32 *, 0x10) == 100.0f) || (M2C_FIELD(arg3, f32 *, 0x14) == 100.0f))) {
        func_80297D38("atrpos>remain=100\n");
    }
}

u8 func_8026DC74(s32 arg0) {
    return D_800B15D8[arg0].unk10;
}

void func_8026DB88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_s0;
    s32 var_a1;
    s32 var_at;
    s32 var_at_2;
    s32 var_s0;
    s32 var_t0;

    var_a1 = arg1;
    var_t0 = arg4;
    if (var_t0 < var_a1) {
        temp_s0 = var_a1;
        var_a1 = var_t0;
        var_t0 = temp_s0;
    }
    if (var_a1 < 0) {
        var_a1 = 0;
    }
    if (var_t0 < 0) {
        var_t0 = 0;
    }
    var_at = D_800B15D8->unk0 < var_t0;
    if (D_800B15D8->unk0 < var_a1) {
        var_a1 = D_800B15D8->unk0;
        var_at = D_800B15D8->unk0 < var_t0;
    }
    var_at_2 = var_t0 < var_a1;
    if (var_at != 0) {
        var_t0 = D_800B15D8->unk0;
        var_at_2 = var_t0 < var_a1;
    }
    var_s0 = var_a1;
    if (var_at_2 == 0) {
        do {
            func_8026DA2C(arg0, var_s0, arg2, arg3, arg5, arg6);
            var_s0 += 1;
        } while ((var_t0 + 1) != var_s0);
    }
}

void func_8026DA2C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp44[3];
    s32 temp_s2;
    s32 temp_s2_2;
    s32 var_a0;
    s32 var_at;
    s32 var_at_2;
    s32 var_at_3;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_s6;
    s32 var_s7;
    s32 var_v0;

    var_s7 = arg0;
    var_s0 = arg2;
    var_s6 = arg3;
    func_802438BC(sp44);
    temp_s2 = var_s7;
    if (var_s6 < var_s7) {
        var_s7 = var_s6;
        var_s6 = temp_s2;
    }
    if (var_s7 < 0) {
        var_s7 = 0;
    }
    if (var_s6 < 0) {
        var_s6 = 0;
    }
    temp_s2_2 = var_s0;
    if (sp44[0] < var_s7) {
        var_s7 = sp44[0];
    }
    if (sp44[0] < var_s6) {
        var_s6 = sp44[0];
    }
    var_v0 = arg4;
    if (var_v0 < var_s0) {
        var_s0 = var_v0;
        var_v0 = temp_s2_2;
    }
    if (var_s0 < 0) {
        var_s0 = 0;
    }
    if (var_v0 < 0) {
        var_v0 = 0;
    }
    var_at = sp44[2] < var_v0;
    if (sp44[2] < var_s0) {
        var_s0 = sp44[2];
        var_at = sp44[2] < var_v0;
    }
    var_at_2 = var_v0 < var_s0;
    if (var_at != 0) {
        var_v0 = sp44[2];
        var_at_2 = var_v0 < var_s0;
    }
    var_s2 = var_s0;
    if (var_at_2 == 0) {
        var_at_3 = var_s6 < var_s7;
        do {
            var_s0_2 = var_s7;
            if (var_at_3 == 0) {
                var_a0 = var_s0_2;
                do {
                    func_8026D620(var_a0, arg1, var_s2, (u16) arg5);
                    var_s0_2 += 1;
                    var_a0 = var_s0_2;
                } while ((var_s6 + 1) != var_s0_2);
            }
            var_s2 += 1;
            var_at_3 = var_s6 < var_s7;
        } while ((var_v0 + 1) != var_s2);
    }
}

void func_8026DA1C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = arg3;
}

void func_8026D92C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_s5;
    s32 temp_t8;
    s32 var_fp;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    temp_t8 = arg4 - arg2;
    var_fp = 0;
    if (temp_t8 >= 0) {
        temp_s5 = arg3 - arg0;
        do {
            var_s0 = 0;
            if (temp_s5 >= 0) {
                var_s1 = arg0;
                var_s2 = arg5;
                do {
                    func_8026D620(var_s2, arg6, arg7 + var_fp, func_8026D7D8(var_s1, arg1, arg2 + var_fp));
                    var_s0 += 1;
                    var_s1 += 1;
                    var_s2 += 1;
                } while (temp_s5 >= var_s0);
            }
            var_fp += 1;
        } while (temp_t8 >= var_fp);
    }
}

u16 func_8026D7D8(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;
    u16 var_a0;

    var_v1 = 0;
    if (arg1 < 0) {
        arg1 = 0;
        var_v1 = 1;
    }
    if (((D_800B15D8->unk1 + (D_800B15D8->unk4 * 8)) - 1) < arg0 || ((D_800B15D8->unk3 + (D_800B15D8->unk8 * 8)) - 1) < arg2 || arg0 < 0 || arg2 < 0 || arg1 >= D_800B15D8->unk0) {
        var_a0 = D_802AFC58;
    } else {
        var_a0 = D_800B15D8[arg1].unk12[func_8026D5F8(arg0, arg1, arg2)].unk2[func_8026D5C0(arg0, arg1, arg2)];
    }
    if (var_v1 == 1 && (var_a0 & 0xF)) {
        var_a0 = 0xF;
    }
    if (D_802AC89C == 1) {
        var_a0 = 1;
    }
    return var_a0;
}

void func_8026D6C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i;
    s32 j;

    for (i = 0; i <= arg4 - arg2; i++) {
        for (j = 0; j <= arg3 - arg0; j++) {
            func_8026D620(arg0 + j, arg1, arg2 + i, arg5);
        }
    }
}

void func_8026D620(s32 arg0, s32 arg1, s32 arg2, u16 arg3) {
    D_800B15D8[arg1].unk12[func_8026D5F8(arg0, arg1, arg2)].unk2[func_8026D5C0(arg0, arg1, arg2)] = arg3;
}

s32 func_8026D5F8(s32 arg0, s32 arg1, s32 arg2) {
    return ((arg2 >> 3) * D_800B15D8->unk4) + (arg0 >> 3);
}

s32 func_8026D5C0(s32 arg0, s32 arg1, s32 arg2) {
    return ((arg2 % 8) * 8) + (arg0 % 8);
}

void func_8026D5B4(s32 arg0) {
    D_802AFC54 = arg0;
}

void func_8026D580() {
    func_80297D30(0xD, D_802A1450);
    D_802AFC6C = NULL;
    D_802AFC54 = 0;
}
