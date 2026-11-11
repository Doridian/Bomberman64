/*
 * NON_MATCHING: main_code's 8A7A0, complete (54 functions,
 * func_8026FFA0..func_80273F0C): the objects on the stage map (the
 * 0x30-byte slots D_802AFCE8, the object D_802AFDD8, the lists
 * D_802AFDE0/D_802AFE58), split from 87D80 (text_objects.txt). A first
 * draft from m2c; every function global, emitted in the original's
 * order. Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING
 * drafts").
 * flags: -O3
 * differing words: us 119, eu 119, jp 119
 *
 * func_802727D8 calls func_8026E8B8 (87D80) with a jal, which IDO
 * would inline within one file (475 words in the one-file draft, 39
 * here). The prelude (types, externs, prototypes) is 87D80.c's.
 * The entity flag helpers func_80270354/func_8027036C/func_802712A8 and
 * the tests func_80270384/func_802702BC are inlined by umerge where the
 * original calls them; the callers call them rather than spell them out.
 * 49 of 54 match. Left: func_80270C24 55, func_80270770 35 (flags
 * and ok in v1/a0 where the original has a0/a1), func_80271BB8 25 (the
 * s temp's slot at 68, the second unk40 pointer in v1, the tail's
 * schedule), func_8027241C 3, func_80271010 1 (one add.s with its
 * operands swapped).
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

typedef struct Ctl87 {
    /* 0x00 */ struct Ctl87 *next;
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
#define ABSF(x) ((x) < 0.0f ? -(x) : (x))

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
    /* 0x34 */ Obj8E *unk34;
    /* 0x38 */ void *unk38;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 pad3E[2];
    /* 0x40 */ f32 x;
    /* 0x44 */ f32 y;
    /* 0x48 */ f32 z;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 pad58[4];
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
#define ENTS ((Ent88 *) D_8008F438)
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
void func_80232A34(u8 *arg0, s32 arg1);
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
s32 func_80287440(Obj8E *arg0);
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
s32 func_8026EE18(f32 arg0);
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
void func_80270354(s16 *arg0, s16 arg1);
void func_8027036C(s16 *arg0, s16 arg1);
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
s16 func_802712A8(s16 *arg0, s16 arg1);
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
s32 func_802721D4(Obj8E *arg0, s32 arg1, Ctl87 *arg2);
s16 func_8027241C(s16 arg0);
void func_80272494(Obj8E *arg0, Obj8E *arg1, Ctl87 *arg2);
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
    Ent88 *n;
    s16 cnt;
    Unk8026DCAC info;
    s32 live;

    func_802714C4();
    func_8026DCAC(arg1, arg2, arg3, &info, 2);
    v[2] = info.i[0];
    v[1] = info.i[1];
    v[0] = info.i[2];
    if (func_80273A5C(v[2], v[1], v[0]) == 0) {
        return 0;
    }
    pl = &PLAYERS[arg0];
    cnt = pl->unk1E;
    e = ENT_HEAD;
    n = e->next;
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
    u32 t;

    t = func_8026D7D8(arg0, arg1, arg2);
    if (t & 0x4000) {
        return 0;
    }
    if (t & 0x60) {
        return 0;
    }
    switch (t & 0xF) {
    case 7:
    case 8:
    case 12:
    case 13:
    case 15:
        return 0;
    }
    return 1;
}

void *func_8027361C(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4) {
    s16 idx;
    s32 size;
    s32 flags;
    Ent88 *e;
    Obj8E *obj;
    s32 pad[25]; /* the frame is 0xA8 */

    idx = func_802735CC();
    if (idx == -1) {
        return NULL;
    }
    if (arg0 & 0x100) {
        size = 0x90;
    } else {
        size = 0xA0;
    }
    flags = 0x01000012;
    if (arg0 & 5) {
        flags = 0x01004012;
    }
    if (arg0 & 2) {
        flags |= 0x0C000000;
    }
    if (arg0 & 0x800) {
        flags |= 0x8000;
    }
    obj = func_80231274(func_8027356C(arg0), flags, size, NULL);
    if (obj == NULL) {
        return NULL;
    }
    if (func_802311E8(obj) == 0) {
        return NULL;
    }
    obj->unk30 = 0x21;
    obj->unk34 = 40.0f;
    obj->unk38 = 40.0f;
    e = &ENTS[idx];
    func_80273544((u8 *) e);
    e->unk4 = func_80238A10(func_8027723C, (s32) e, 0, 0, 0xB0);
    if (e->unk4 == -1) {
        return NULL;
    }
    e->unk0 = idx;
    e->unk8 = -1;
    e->unkC = 0;
    e->obj = obj;
    e->xf = obj->unk40;
    e->unk30 = obj;
    e->unk34 = obj;
    e->unk3C = 0;
    e->unkE = arg4;
    e->unk10 = arg0;
    if (e->unk10 & 0x400) {
        e->unk68 = 0x3C;
    } else {
        e->unk68 = 0x96;
    }
    e->unk5C = 0;
    e->unk5E = 0;
    e->unk60 = e->unk62 = 0;
    if (e->unk10 & 2) {
        e->unk64 &= ~2;
    } else {
        e->unk64 |= 2;
    }
    for (idx = 0; idx < 3; idx++) {
        e->unk24[idx] = NULL;
    }
    e->xf->x = arg1;
    e->x = e->obj->unk58 = e->xf->x;
    e->xf->y = arg2;
    e->y = e->obj->unk5C = e->xf->y;
    e->xf->z = arg3;
    e->z = e->obj->unk60 = e->xf->z;
    e->obj->unk6C = 1.0; /* a double: 1.0f would share the else branch's 1.0f */
    e->unk4C = 0.0f;
    e->unk50 = 0.0f;
    e->unk54 = 0.0f;
    e->unk66 = PLAYERS[arg4].unk20 + 1;
    e->unk64 &= ~4;
    e->unk74 = 9;
    if (e->unk10 & 0x800) {
        e->xf->sx = 10.0f;
        e->xf->sy = 10.0f;
        e->xf->sz = 10.0f;
        e->unk78 = 10.0f;
        e->unk80 = 10.0f;
        e->unk7C = 9.0f;
        e->unk84 = 0.033333335f;
    } else {
        e->xf->sx = 1.0f;
        e->xf->sy = 1.0f;
        e->xf->sz = 1.0f;
        e->unk78 = 1.0f;
        e->unk7C = 0.9f;
        e->unk80 = 1.0f;
        if (e->unk10 & 0x400) {
            e->unk84 = 0.008333334f;
        } else {
            e->unk84 = 0.0033333334f;
        }
    }
    e->unk64 &= ~1;
    e->unk64 &= ~0x20;
    e->unk64 &= ~0x200;
    e->unk64 &= ~8;
    e->unk64 &= ~0x10;
    e->unk64 &= ~0x80;
    e->unk64 &= ~0x40;
    e->unk64 &= ~0x400;
    e->unk64 &= ~0x800;
    return e;
}

s16 func_802735CC(void) {
    Ent88 *e;
    s16 i;

    e = ENTS;
    for (i = 0; i < 22; i++, e++) {
        if (e->xf == NULL) {
            break;
        }
    }
    if (i < 22) {
        return i;
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
    s16 *e;

    e = func_802703B4(arg0);
    if (e != NULL) {
        if (func_80270384((u8 *) e)) {
            func_80273414(e);
        }
        func_802733F8(e);
        func_80238EA8(((Ent88 *) e)->unk4);
        func_80239094();
    }
}

void func_80273414(s16 *arg0) {
    Ent88 *e = (Ent88 *) arg0;
    s32 pad[4];
    void *p;

    func_80270BA4(e->obj);
    if (func_802712A8(&e->unk64, 0x200)) {
        func_8027036C(&e->unk64, 0x200);
        func_802313DC(e->obj, 0x20000);
        p = e->unk38;
        func_80270A80(p);
        free(p);
    }
    if (e->unk8 != -1) {
        func_8028A4E0(e->unk8);
        e->unk8 = -1;
    }
    e->unk74 = 9;
    func_802711C8(arg0);
    func_8022FC90(e->obj);
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
    s16 i;
    Slot30 *p;

    for (i = 0; i < 5; i++) {
        p = &SLOTS[i];
        if (arg0 == p->unkC) {
            return p;
        }
    }
    return NULL;
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
    if (sl) { /* fake: moves the slot pointer's spill to the original's place */
    }
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
    s32 w;
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
                    func_80272494(obj, hit, arg0);
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
            v = (s32) func_8027A1A0(arg0->obj);
            if (v != 0 && func_802712A8((s16 *) (v + 0x54), 0x40) == 0 && arg0->unk28 < 2) {
                w = (obj->unk40->y <= func_8026E8B8()) ? 1 : 0;
                if (w == 0) {
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

void func_80272494(Obj8E *arg0, Obj8E *arg1, Ctl87 *arg2) {
    f32 d;
    f32 r;
    s32 dir;
    s32 i;
    s32 res;
    f32 a[3];
    f32 b[3];
    s32 pad2[2]; /* places ang at the original's offset */
    f32 ang;

    a[0] = arg0->unk40->x;
    a[1] = 0.0; /* doubles: a 0.0f would share ABSF's register */
    a[2] = arg0->unk40->z;
    b[0] = arg1->unk40->x;
    b[1] = 0.0;
    b[2] = arg1->unk40->z;
    if (arg1->unk8 & 0x8000) {
        arg2->unk14 = func_8027241C(arg2->unk14);
    }
    if (arg2->unk14 == 9) {
        func_8022FF58(b, a, &ang);
        arg2->unk14 = func_802704F8(ang);
    }
    dir = arg2->unk14;
    arg2->unk2C = arg2->unk1C;
    d = ABSF(ABSF(func_80270F44((u8 *) arg0)) + ABSF(func_80270F44((u8 *) arg1)));
    d += 1.0f;
    for (i = 0; i < 8; i++) {
        for (r = 10.0f; r < d; r += 10.0f) {
            arg2->unk1C = r;
            arg2->unk14 = dir;
            res = func_802721D4(arg0, (s32) arg1, arg2);
            if (res == 2) {
                break;
            }
            if (res == 1) {
                return;
            }
        }
        if (d <= r) {
            arg2->unk1C = d;
            arg2->unk14 = dir;
            if (func_802721D4(arg0, (s32) arg1, arg2) == 1) {
                return;
            }
        }
        dir = (dir + 1) & 7;
    }
}

s16 func_8027241C(s16 arg0) {
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
        arg0 = 3;
        break;
    }
    return arg0;
}

s32 func_802721D4(Obj8E *arg0, s32 arg1, Ctl87 *arg2) {
    func_802714C4();
    OBJ_DD8->unk40->x = OBJ_DD8->unk58 = arg0->unk58;
    OBJ_DD8->unk40->y = OBJ_DD8->unk5C = arg0->unk5C;
    OBJ_DD8->unk40->z = OBJ_DD8->unk60 = arg0->unk60;
    OBJ_DD8->unk40->sx = arg0->unk40->sx;
    OBJ_DD8->unk40->sy = arg0->unk40->sy;
    OBJ_DD8->unk40->sz = arg0->unk40->sz;
    OBJ_DD8->unk30 = 1;
    OBJ_DD8->unk34 = arg0->unk34;
    OBJ_DD8->unk38 = arg0->unk38;
    func_80291944(OBJ_DD8, func_80272024(arg2->unk14), arg2->unk1C);
    if (OBJ_DD8->unk8 & 1) {
        arg2->unk20 = func_80272024(arg2->unk14);
        arg2->unk24 = 0.0f;
        func_802441F4(arg0, func_80272024(arg2->unk14), &arg2->unk20, &arg2->unk24);
        func_80291944(OBJ_DD8, arg2->unk20, arg2->unk24);
        arg2->unk20 = 1;
        arg2->unk24 = 0.0f;
    }
    func_802720C8((u8 *) OBJ_DD8);
    OBJ_DD8->unk70 = 1.6333334f;
    OBJ_DD8->unk6C = 2.0f;
    OBJ_DD8->unk68 = 22.5f;
    func_80230914(OBJ_DD8);
    if (func_802909FC(OBJ_DD8, func_80277378) != 0) {
        return 2;
    }
    if (func_8022E884((s32) OBJ_DD8, arg1) != 0) {
        return 0;
    }
    return 1;
}

void func_802720C8(u8 *arg0) {
    f32 z;
    f32 p[3];
    s32 pad[5]; /* places info at the original's offset */
    s16 t;
    Unk8026DCAC info;

    z = ((Obj8E *) arg0)->unk60;
    func_8026DCAC(((Obj8E *) arg0)->unk58, ((Obj8E *) arg0)->unk5C, z, &info, 2);
    p[2] = info.i[0];
    p[1] = info.i[1];
    p[0] = info.i[2];
    t = func_8026D7D8(p[2], p[1], p[0]);
    t &= 0x1C00;
    if (t != 0) {
        func_8027F858((s32) arg0, t >> 10);
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
    Ctl87 *c = (Ctl87 *) arg0;

    func_802313DC(c->obj, 0x20000);
    if (c->flags & 2) {
        func_80270EF0((u8 *) c->obj);
    } else if (c->flags & 8) {
        func_8027B440(c->obj);
    } else if (c->flags & 4) {
        func_80287440(c->obj);
    } else if (c->flags & 1) {
        func_80244E04(c->obj);
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
    Sub8E *t;
    f32 ppos[3];
    f32 opos[3];
    Obj8E *obj;

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
    if (obj->unk8 & 2) {
        if (func_8027130C((u8 *) obj) == 0) {
            hit = 1;
        }
    } else if (obj->unk8 & 8) {
        if (func_8027B5A8(obj) == 0) {
            hit = 1;
        }
    } else if (obj->unk8 & 4) {
        if (func_802875B0(obj) == 0) {
            hit = 1;
        }
    } else if (obj->unk8 & 1) {
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
        SLOTS[arg0].unk8 = flags;
        func_80231408(obj, 0x10000);
        func_80232AC8((s32) pl, (s32) obj);
        func_80231408(obj, 0x200000);
        func_80271178(arg0, (s32) obj);
        func_80271010((u8 *) obj, arg0);
        obj->unk40->rot = pl->unk40->rot;
        dx = func_80234434(pl->unk40->rot);
        dx = func_80270F44((u8 *) pl) * dx;
        dz = func_80234408(pl->unk40->rot);
        dz = func_80270F44((u8 *) pl) * dz;
        if (func_802336E4(dx) != 0) {
            dx = 0.0f;
        }
        if (func_802336E4(dz) != 0) {
            dz = 0.0f;
        }
        obj->unk4C = dx - SLOTS[arg0].unk1C;
        obj->unk50 = obj->unk40->y - pl->unk40->y;
        obj->unk6C = 1.0f;
        obj->unk54 = dz - SLOTS[arg0].unk24;
        obj->unk70 = 1.6333334f;
    }
}

void *func_802716F8(s16 arg0) {
    f32 z;
    f32 dx;
    f32 dz;
    f32 r;
    f32 dist;
    s32 pad[2]; /* the pads place the locals at the original's offsets */
    f32 a[3];
    f32 b[3];
    s32 pad2[2];
    f32 ang;
    s32 pad3;
    f32 pr;
    s32 pad4[4];
    Obj8E *pl;
    Obj8E *obj;
    Unk8026DCAC info;
    s32 t;

    func_802714C4();
    if (1) {} /* fake: without it arg0 takes a third saved register */
    pl = func_802443F4(arg0);
    obj = (Obj8E *) func_80271540(arg0);
    if (obj != NULL) {
        z = obj->unk40->z;
        func_8026DCAC(obj->unk40->x, obj->unk40->y, z, &info, 2);
        a[0] = info.i[0];
        a[1] = info.i[1];
        a[2] = info.i[2];
        t = func_8026D7D8(a[0], a[1], a[2]) & 0xF;
        if (t == 3 || t == 4 || t == 5 || t == 6) {
            return obj;
        }
        a[0] = pl->unk40->x;
        a[1] = 0.0f;
        a[2] = pl->unk40->z;
        b[0] = obj->unk40->x;
        b[1] = 0.0f;
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
    s32 pad[1];
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
    s16 i;

    if (D_802AFC74 != 1) {
        D_802AFC74 = 1;
        for (i = 0; i < 5; i++) {
            func_802702EC(i);
        }
        D_802AFDD8 = func_80231274(-1, 0, 0xD0, NULL);
    }
}

void func_80271448(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    s32 pad[3];
    s32 a[3];

    func_8026DCAC(arg0, arg1, arg2, a, 2);
    *arg3 = a[0];
    *arg4 = a[1];
    *arg5 = a[2];
}

s32 func_8027130C(u8 *arg0) {
    s32 pad[10]; /* the frame is 0x50 */
    Ent88 *e;
    void *p;

    e = (Ent88 *) func_802703B4(arg0);
    if (e == NULL) {
        return 0;
    }
    if (func_802712A8(&e->unk64, 0x80)) {
        return 0;
    }
    if (func_802712A8(&e->unk64, 0x10)) {
        func_80270BA4(arg0);
    }
    if (func_802712A8(&e->unk64, 0x200)) {
        func_8027036C(&e->unk64, 0x200);
        func_802313DC(e->obj, 0x20000);
        p = e->unk38;
        func_80270A80(p);
        free(p);
    }
    func_802712C4((s16 *) e);
    e->obj->unk6C = 1.0f;
    func_80270354(&e->unk64, 0x10);
    func_8027036C(&e->unk64, 0x800);
    e->unk50 = 0.0f;
    func_8027036C(&e->unk64, 2);
    if (e->unk10 & 0x400) {
        e->unk68 = 0x3C;
    } else {
        e->unk68 = 0x96;
    }
    e->unk80 = 1.0; /* a double, so the 1.0f above isn't reused */
    func_802313DC(arg0, 0x20000);
    return 1;
}

void func_802712C4(s16 *arg0) {
    Ent88 *e = (Ent88 *) arg0;

    if (func_802712A8(&e->unk64, 4)) {
        e->unk74 = 9;
        func_8027036C(&e->unk64, 4);
        e->unk30 = e->obj;
        func_802711C8(arg0);
    }
}

s16 func_802712A8(s16 *arg0, s16 arg1) {
    return *arg0 & arg1;
}

void func_802711C8(s16 *arg0) {
    s16 v;
    s16 found;
    s16 i;
    s16 j;

    found = 0;
    v = *arg0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 8; j++) {
            if (v == ((s16 (*)[9]) D_802AFC78)[i][j]) {
                found = 1;
                break;
            }
        }
        if (found == 1) {
            break;
        }
    }
    if (i < 6) {
        for (; j < 8; j++) {
            ((s16 (*)[9]) D_802AFC78)[i][j] = ((s16 (*)[9]) D_802AFC78)[i][j + 1];
        }
    }
}

void func_80271178(s16 arg0, s32 arg1) {
    if (func_802702BC(arg0) == 0) {
        SLOTS[arg0].unkC = arg1;
    }
}

void func_80271010(u8 *arg0, s16 arg1) {
    f32 dx;
    f32 dz;
    Slot30 *sl;
    Obj8E *pl;
    f32 s;

    pl = func_802443F4(arg1);
    s = func_80234434(pl->unk40->rot);
    dx = func_80270F44(arg0) * s;
    s = func_80234408(pl->unk40->rot);
    dz = func_80270F44(arg0) * s;
    if (func_802336E4(dx) != 0) {
        dx = 0.0f;
    }
    if (func_802336E4(dz) != 0) {
        dz = 0.0f;
    }
    sl = &SLOTS[arg1];
    if (sl) { /* fake, as in func_80272FC0 */
    }
    sl->unk10 = 0x14;
    sl->unk0 = arg1;
    sl->unk1C = (pl->unk40->x + dx) - ((Obj8E *) arg0)->unk40->x;
    sl->unk24 = (dz + pl->unk40->z) - ((Obj8E *) arg0)->unk40->z;
    sl->unk20 = 0.0; /* doubles: the 0.0f of dz isn't reused */
    sl->unk28 = 0.0;
    dx = func_80270FC0((u8 *) pl); /* reusing dx (a permuter find) */
    sl->unk2C = (dx + pl->unk40->y) - ((Obj8E *) arg0)->unk40->y;
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
    Obj8E *o = (Obj8E *) arg0;
    f32 m;
    f32 r;

    if (o->unk30 & 0x20) {
        r = o->unk34;
    } else {
        m = o->unk40->sx;
        if (m < o->unk40->sy) {
            m = o->unk40->sy;
        }
        if (m < o->unk40->sz) {
            m = o->unk40->sz;
        }
        r = o->unk34 * m;
    }
    return r;
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
    s32 i;
    Ctl87 *c;
    s32 ok;
    f32 r;
    f32 h;

    for (i = 0; i < 5; i++) {
        if (func_80270714(i) == (s32) arg0) {
            func_80270BA4(arg0);
        }
    }
    for (c = (Ctl87 *) D_802AFDE0.next; c->next != NULL; c = c->next) {
        if (arg0 == (u8 *) c->obj) {
            break;
        }
    }
    if (c->next != NULL) {
        func_80270A80((s32 *) c);
        free(c);
    }
    switch (arg2) {
        case 0:
            r = 0.0f;
            h = 0.0f;
            break;
        case 1:
            r = 25.0f;
            h = 8.25f;
            break;
        case 2:
            r = 25.0f;
            h = 11.0f;
            break;
        case 3:
            r = 25.0f;
            h = 14.0f;
            break;
        default:
            r = 10.0f;
    }
    c = malloc(sizeof(Ctl87));
    c->obj = (Obj8E *) arg0;
    c->unk14 = func_8026FFA0(arg1);
    c->unk18 = r;
    c->unk20 = 1;
    c->unk28 = 0;
    c->unk16 = 0;
    c->unk1C = h;
    c->unk24 = 0.0f;
    c->unk30 = 0;
    c->unk2C = 10000.0f;
    ok = 0;
    c->unk34 = ((Obj8E *) arg0)->unk40->x;
    c->unk38 = ((Obj8E *) arg0)->unk40->z;
    c->flags = ((Obj8E *) arg0)->unk8;
    if (c->flags & 2) {
        ok = func_80270438(arg0, (s32 *) c);
    } else if (c->flags & 8) {
        ok = func_8027A1F4(arg0, (s32) c);
    } else {
        if (h) { /* fake: keeps h live into the chain (permuter find) */
        }
        if (c->flags & 4) {
            ok = func_802870A8(arg0, c);
        } else if (c->flags & 1) {
            ok = func_80244F34(arg0, (s32) c);
        }
    }
    if (ok != 0) {
        func_80270080((s32 *) c);
        func_80231408(arg0, 0x20000);
        ((Obj8E *) arg0)->unk68 = c->unk18;
        ((Obj8E *) arg0)->unk6C = 1.0f;
        c->unk8 = (Obj8E *) arg0;
        c->unkC = (Obj8E *) arg0;
        return;
    }
    free(c);
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
    s16 i;

    for (i = 0; i < 5; i++) {
        if (arg0 == SLOTS[i].unkC) {
            return i;
        }
    }
    return -1;
}

void func_80270B20(u8 *arg0) {
    func_80270A80((s32 *) arg0);
    free(arg0);
}

void func_80270A80(s32 *arg0) {
    Node87 *p;
    s32 found;

    if (*(s32 *) &D_802AFE58 != 0 && arg0 != NULL) {
        found = 0;
        for (p = &D_802AFDE0; p->next->next != NULL; p = p->next) {
            if ((Node87 *) arg0 == p->next) {
                found = 1;
                break;
            }
        }
        if (found == 1) {
            p->next = (Node87 *) *arg0;
            (*(s32 *) &D_802AFE58)--;
        }
    }
}

void func_80270770(s16 arg0, s16 arg1) {
    Obj8E *o;
    Ctl87 *c;
    f32 speed;
    f32 h;
    Obj8E *obj;
    s32 ok;
    s32 flags;

    if (func_80270714(arg0) == 0) {
        return;
    }
    obj = (Obj8E *) func_80270714(arg0);
    switch (arg1) {
        case 0:
            speed = 0.0f;
            if (D_802AFC5C == 0.0f) { /* fake: lets speed's 0.0f serve h's store too */
            }
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
    }
    c = malloc(sizeof(Ctl87));
    goto next; /* fake: a block boundary, so speed is reloaded and saved again around func_802443F4 */
next:
    o = func_802443F4(arg0);
    c->obj = obj;
    c->unk14 = func_802704F8(o->unk40->rot);
    c->unk18 = speed;
    c->unk1C = h;
    c->unk20 = 1;
    c->unk28 = 0;
    c->unk16 = 0;
    c->unk24 = 0.0f;
    c->unk30 = 0;
    c->unk2C = 10000.0f;
    ok = 0;
    c->unk34 = obj->unk40->x;
    c->unk38 = obj->unk40->z;
    flags = SLOTS[arg0].unk8;
    c->flags = flags;
    if (flags & 2) {
        ok = func_80270438((u8 *) obj, (s32 *) c);
    } else if (flags & 8) {
        ok = func_8027A1F4(obj, (s32) c);
    } else if (flags & 4) {
        ok = func_802870A8(obj, c);
    } else if (flags & 1) {
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
        *(s16 *) (D_802AFCE8 + arg0 * 0x30 + 0x10) = 0;
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
    Ent88 *e;

    e = (Ent88 *) func_802703B4(arg0);
    if (e->unk10 & 0x100) {
        func_80232A34((u8 *) e->obj, 0x90);
    }
    func_8027036C(&e->unk64, 0x10);
    func_80270354(&e->unk64, 0x200);
    e->unk30 = e->obj;
    func_80231408(arg0, 0x20000);
    e->unk38 = arg1;
    if (!(e->unk10 & 2)) {
        func_80270354(&e->unk64, 2);
    }
    if (e->unk10 & 0x400) {
        e->unk68 = 0x3C;
    } else {
        e->unk68 = 0x96;
    }
    return 1;
}

s16 *func_802703B4(u8 *arg0) {
    Ent88 *e;

    for (e = ENT_HEAD; e->next != NULL; e = e->next) {
        if (func_80270384((u8 *) e) && (Obj8E *) arg0 == e->obj) {
            return (s16 *) e;
        }
    }
    return NULL;
}

s32 func_80270384(u8 *arg0) {
    if (M2C_FIELD(arg0, f32 *, 0x40) != 1e7f) {
        return 1;
    }
    return 0;
}

void func_8027036C(s16 *arg0, s16 arg1) {
    *arg0 &= ~arg1;
}

void func_80270354(s16 *arg0, s16 arg1) {
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
    Ctl87 *c;
    Sub8E *t;

    if (((Obj8E *) arg0)->unk8 & 0x20000) {
        for (;;) {
            func_80239094();
        }
    }
    c = malloc(sizeof(Ctl87));
    func_80270080((s32 *) c);
    c->obj = (Obj8E *) arg0;
    c->unk8 = (Obj8E *) arg0;
    c->unkC = (Obj8E *) arg0;
    c->flags = ((Obj8E *) arg0)->unk8;
    c->unk14 = func_8026FFA0(arg2);
    c->unk18 = 22.5f;
    c->unk1C = arg3;
    c->unk20 = 1;
    c->unk16 = 0;
    c->unk24 = 0.0f;
    c->unk2C = 10000.0f;
    c->unk30 = 0;
    c->unk34 = ((Obj8E *) arg0)->unk40->x;
    c->unk38 = ((Obj8E *) arg0)->unk40->z;
    if (((Obj8E *) arg1)->unk40->y <= ((Obj8E *) arg0)->unk40->y) {
        func_80231408(arg0, 0x20000);
        t = ((Obj8E *) arg0)->unk40;
        ((Obj8E *) arg0)->unk68 = 22.5f;
        ((Obj8E *) arg0)->unk6C = 2.0f;
        func_8028A81C(0, t->x, t->y + 100.0f, t->z, 0);
        if (((Obj8E *) arg0)->unk8 & 2) {
            t = ((Obj8E *) arg0)->unk40;
            func_8026C51C(0x23, t->x, t->y, t->z);
        } else {
            t = ((Obj8E *) arg0)->unk40;
            func_8026C51C(0x22, t->x, t->y, t->z);
        }
    } else {
        ((Obj8E *) arg0)->unk68 = 0.0f;
        ((Obj8E *) arg0)->unk6C = 2.0f;
    }
    return c;
}

void func_80270080(s32 *arg0) {
    Node87 *p;

    for (p = &D_802AFDE0; p->next->next != NULL; p = p->next) {
    }
    *arg0 = (s32) p->next;
    p->next = (Node87 *) arg0;
    (*(s32 *) &D_802AFE58)++;
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
