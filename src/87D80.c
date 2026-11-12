/*
 * main_code's 87D80, IDO -O3; it matches in us, eu and jp (43 functions,
 * func_8026D580..func_8026FF94): the stage map D_800B15D8 (layers of
 * 0x82-byte cells of 64 attribute halfwords) and its attribute queries
 * (func_8026D7D8, func_8026DCAC, func_8026E3AC). The objects on it are
 * the next object, 8A7A0 (src/8A7A0.c, text_objects.txt).
 * Every function is global, in the original's order.
 *
 * func_8026D5F8 and func_8026D5C0 (cell and slot of a point) are
 * inlined by func_8026D620/func_8026D7D8, which is what the original's
 * register copies show; func_8026D5F8 keeps its result in a local
 * (`r = ...; return r;`), which gives the inlined copies their extra
 * register. The map reads as D_800B15D8->unkN, not
 * D_800B15D8[0].unkN (the latter swaps the multiply's registers).
 * func_8026F5E8 and func_8026E3AC keep their x/y/z in an f32[3] (the
 * original's dead stores to it), not in three variables.
 * func_8026E938's tail calls the getters func_8026E8C8 (the map's sign
 * bit, inlined as `lui v0; lb`) and func_8026E8B8.
 * func_8026DCAC and func_8026EE18 add the layer heights through the
 * getter func_8026DC74 (its inlined result is the original's v0); a
 * dead `&D_800B15D8[layer] == NULL` test in the loop head puts the
 * address in every pass, so uopt strength-reduces it as the original
 * does (a single use at the loop's end keeps a multu).
 * In func_8026DCAC uopt hoists iy out of the loop; a dead
 * `if (iy && iy) {}` adds two loop uses, so iy outranks the layer
 * pointer (tie, lower bit) and takes a0 as in the original.
 * In func_8026FC08 the `src = p = D_802AFC6C = ...`
 * chain puts &D_802AFC6C in v1, as the original does. Its inner loop
 * computes the three coordinates into x, y and z before `p += 2` and
 * passes `(p[-2] << 8) + p[-1]` (uopt reverses the sum, so the source
 * has the shift first): ugen then emits the cell's two loads last, and
 * as1 schedules them, j % 8 and the increment as the original does.
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
void func_8026D620(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8026D6C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_8026D7D8(s32 arg0, s32 arg1, s32 arg2);
void func_8026D92C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_8026DA1C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8026DA2C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_8026DB88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
u8 func_8026DC74(s32 arg0);
void func_8026DCAC(f32 arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4);
s32 func_8026DF74(f32 arg0, f32 arg1, f32 arg2);
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
s32 func_8026EF50(f32 arg0, f32 arg1, f32 arg2);
s32 func_8026EFD0(s32 arg0, s32 arg1, s32 arg2);
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
s32 func_802735CC(void);
void *func_8027361C(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4);
s32 func_80273A5C(s32 arg0, s32 arg1, s32 arg2);
s32 func_80273AD4(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80273E2C(s16 arg0);
void func_80273F0C(void);
void func_8027723C(void);

static const char D_802A3B60[] = "atrpos>remain=100\n";

void func_8026FF94(s32 arg0) {
    D_802AFC58 = arg0;
}

void func_8026FF64(s32 arg0) {
    func_8026FC08(arg0);
    func_8026F8B0();
    D_802AFC58 = 0x2010;
}

void func_8026FC08(s32 arg0) {
    u8 *src;
    u8 *p;
    s32 n;
    s32 layers;
    s32 i;
    s32 j;
    s32 cnt;
    s32 v;
    f32 f;
    s32 x;
    s32 y;
    s32 z;

    D_802AFC50 = arg0;
    D_800B15D8->unk4 = 0;
    D_800B15D8->unk8 = 0;
    src = p = D_802AFC6C = func_8026CE28(arg0);
    D_802AFC60 = 0.0f;
    D_802AFC64 = 1.6333334f;
    D_802AFC68 = 0.0f;
    D_800B15D8->unk0 = *p++;
    layers = D_800B15D8->unk0;
    D_800B15D8->unk1 = *p++;
    D_800B15D8->unk2 = *p++;
    D_800B15D8->unk3 = *p++;
    D_800B15D8->unkC = *p++;
    f = -((u8) D_800B15D8->unkC & 0x7F) * 100.0f;
    D_802AFC5C = f;
    for (n = 0; n < layers; n++) {
        D_800B15D8[n].unkE = *p++;
        D_800B15D8[n].unkF = *p++;
        v = D_800B15D8[n].unkE + ((D_800B15D8->unk1 + 7) >> 3);
        if (D_800B15D8->unk4 < v) {
            D_800B15D8->unk4 = v;
        }
        if (D_800B15D8->unk8 < D_800B15D8[n].unkF + ((D_800B15D8->unk3 + 7) >> 3)) {
            D_800B15D8->unk8 = D_800B15D8[n].unkF + ((D_800B15D8->unk3 + 7) >> 3);
        }
        D_800B15D8[n].unk10 = *p;
        cnt = D_800B15D8[n].unkE * D_800B15D8[n].unkF;
        p++;
        p += cnt * sizeof(UnkCell_800B15D8);
    }
    p = src + 5;
    for (n = 0; n < layers; n++) {
        D_800B15D8[n].unkE = *p++;
        D_800B15D8[n].unkF = *p++;
        cnt = D_800B15D8[n].unkE * D_800B15D8[n].unkF;
        for (i = 0; i < D_800B15D8->unk8 * 8; i++) {
            for (j = 0; j < D_800B15D8->unk4 * 8; j++) {
                func_8026D620(j, D_800B15D8->unk2 + n, i, 0x2010);
            }
        }
        p++;
        for (i = 0; i < cnt; i++) {
            D_800B15D8[n].unk12[i].unk0 = *p++;
            D_800B15D8[n].unk12[i].unk1 = *p++;
            for (j = 0; j < 64; j++) {
                x = D_800B15D8[n].unk12[i].unk0 * 8 + D_800B15D8->unk1 + j % 8;
                y = D_800B15D8->unk2 + n;
                z = D_800B15D8[n].unk12[i].unk1 * 8 + D_800B15D8->unk3 + (j >> 3);
                p += 2;
                func_8026D620(x, y, z, (p[-2] << 8) + p[-1]);
            }
        }
    }
}

void func_8026F8B0(void) {
    s32 x;
    s32 j;
    s32 k;
    s32 y;
    s32 z;
    s32 i;
    s32 x1;
    s32 y1;
    s32 count;
    s32 n;
    s32 ok;
    s32 a1;
    s32 a0;
    s32 a6;
    s32 a5;
    s32 a4;
    s32 a3;
    s32 a2;

    n = D_800B15D8->unk0;
    for (i = 0; i < n; i++) {
        for (k = D_800B15D8->unk3; k < D_800B15D8->unk8 * 8; k++) {
            for (j = D_800B15D8->unk1; j < D_800B15D8->unk4 * 8; j++) {
                func_8026F5E8(j, i, k);
            }
        }
    }
    count = func_8027DF9C();
    for (i = 0; i < count; i++) {
        do {
            ok = 0;
            y = func_80234248(D_800B15D8->unk0 - 1) + D_800B15D8->unk2;
            x = func_80234248(D_800B15D8[y].unkE * 8 - 1) + D_800B15D8->unk1;
            z = func_80234248(D_800B15D8[y].unkF * 8 - 1) + D_800B15D8->unk3;
            x1 = func_8026D7D8(x, y, z);
            if (!(x1 & 0x70) && !(x1 & 0x60)) {
                n = func_8027DF40(0x20);
                a0 = 0;
                a2 = 0;
                a3 = 0;
                a4 = 0;
                a5 = 0;
                a6 = 0;
                a1 = 0;
                switch (n) {
                    case 1:
                        a1 = func_8026D7D8(x, y + 1, z) & 0x70;
                        break;
                    case 2:
                        a1 = func_8026D7D8(x + 1, y, z) & 0x70;
                        a6 = func_8026D7D8(x, y, z + 1) & 0x70;
                        break;
                    case 3:
                        x1 = x + 1;
                        n = z + 1;
                        a1 = func_8026D7D8(x1, y, z) & 0x70;
                        a6 = func_8026D7D8(x, y, n) & 0x70;
                        y1 = y + 1;
                        a5 = func_8026D7D8(x1, y, n) & 0x70;
                        a4 = func_8026D7D8(x, y1, z) & 0x70;
                        a3 = func_8026D7D8(x1, y1, z) & 0x70;
                        a2 = func_8026D7D8(x, y1, n) & 0x70;
                        a0 = func_8026D7D8(x1, y1, n) & 0x70;
                        break;
                }
                if ((a1 | a6 | a5 | a4 | a3 | a2 | a0) == 0) {
                    ok = func_8026F068(x, y, z, 0x20);
                }
            }
        } while (ok == 0);
    }
}

void func_8026F5E8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 sp28;
    s32 sp24;
    f32 pos[3];
    f32 x;
    f32 y;
    f32 z;

    sp28 = D_802AC5D0 & 4;
    sp24 = *func_8023A840() & 6;
    temp_v0 = func_8026D7D8(arg0, arg1, arg2);
    if (temp_v0 & 0x380) {
        /* fake: x and y appear first, so uopt colours them f2 and f12;
         * the dead read of pos[1] gives z f16 */
        x = 0.0f;
        y = 0.0f;
        if (x) {
        }
        if (pos[1]) {
        }
        if (y) {
        }
        pos[0] = arg0 * 100.0f;
        pos[1] = func_8026E2B0((f32) arg1);
        pos[2] = arg2 * 100.0f;
        x = pos[0];
        z = pos[2];
        y = pos[1];
        switch (temp_v0 & 0x380) {
        case 0x80:
            func_802511EC(0, arg0, arg1, arg2);
            break;
        case 0x100:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(0, x, y, z);
            } else {
                func_802511EC(1, arg0, arg1, arg2);
            }
            break;
        case 0x180:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(1, x, y, z);
            } else {
                func_802511EC(2, arg0, arg1, arg2);
            }
            break;
        case 0x200:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(2, x, y, z);
            } else {
                func_802511EC(3, arg0, arg1, arg2);
            }
            break;
        case 0x280:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(3, x, y, z);
            }
            break;
        case 0x300:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(4, x, y, z);
            }
            break;
        case 0x380:
            if (sp28 == 0 && sp24 == 0) {
                func_80286CA8(5, x, y, z);
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
    s32 i;
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
        i = func_8026D7D8(arg0, arg1, arg2 - 1) & 0x60;
        if ((a == arg3 && b == arg3 && c == arg3) || (d == arg3 && e == arg3 && f == arg3) ||
            (g == arg3 && h == arg3 && i == arg3)) {
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

s32 func_8026EFD0(s32 arg0, s32 arg1, s32 arg2) {
    s32 restore;
    s32 v;

    restore = 0;
    if (D_802AC89C == 1) {
        D_802AC89C = 0;
        restore = 1;
    }
    v = func_8026D7D8(arg0, arg1, arg2);
    if (restore == 1) {
        D_802AC89C = 1;
    }
    return v;
}

s32 func_8026EF50(f32 arg0, f32 arg1, f32 arg2) {
    s32 restore;
    s32 sp24[12]; /* only [0..2] are read; the size comes from the frame */
    s32 v;

    restore = 0;
    if (D_802AC89C == 1) {
        D_802AC89C = 0;
        restore = 1;
    }
    func_8026DCAC(arg0, arg1, arg2, sp24, 2);
    v = func_8026D7D8(sp24[0], sp24[1], sp24[2]);
    if (restore == 1) {
        D_802AC89C = 1;
    }
    return v;
}

void func_8026EEF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 v;

    v = func_8026D7D8(arg0, arg1, arg2);
    if (arg4 == 1) {
        v |= arg3;
    } else {
        v &= arg3 ^ 0xFFFF;
    }
    func_8026D620(arg0, arg1, arg2, v);
}

s32 func_8026EE18(f32 arg0) {
    s32 r;
    s32 layer;
    s32 h;
    s32 iy;

    iy = (s32) (arg0 * 0.01f);
    h = 0;
    for (layer = 0; layer < D_800B15D8->unk0 + 1; layer++) {
        if (&D_800B15D8[layer] == NULL) { /* fake: puts &D_800B15D8[layer] in the
                                            * loop head, so it is strength-reduced */
        }
        if (iy < h) {
            if (layer > 0) {
                r = layer - 1;
            } else {
                r = layer;
            }
            break;
        }
        if (h == iy) {
            r = layer;
            break;
        }
        h += func_8026DC74(layer);
    }
    if (D_800B15D8->unk0 < layer) {
        r = D_800B15D8->unk0;
    }
    if (arg0 < 0.0f) {
        r = -1;
    }
    return r;
}

void func_8026EE10(s32 arg0) {

}

void func_8026EE08(s32 arg0) {

}

void func_8026ECF4() {
    s32 i;

    func_80297D38("*** MAP INFORMATION ***\n");
    func_80297D38("Offset:%d,%d,%d\n", D_800B15D8->unk1, D_800B15D8->unk2, D_800B15D8->unk3);
    func_80297D38("Layer :%d\n", D_800B15D8->unk0);
    func_80297D38("Size  :%d x %d\n", D_800B15D8->unk4, D_800B15D8->unk8);
    for (i = 0; i < D_800B15D8->unk0; i++) {
        func_80297D38("   (%d):%d x %d\n", i, D_800B15D8[i].unkE, D_800B15D8[i].unkF);
    }
    func_80297D38("Layer Unit\n");
    for (i = 0; i < D_800B15D8->unk0; i++) {
        func_80297D38("   [%d]:%d\n", i, D_800B15D8[i].unk10);
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
    Unk8026DCAC pos;
    f32 fx;
    f32 fy;
    f32 fz;
    f32 ax;
    f32 ay;
    f32 az;
    s32 attr;
    s32 a;
    s32 more;
    f32 r;
    f32 h;

    fx = ((Obj8E *) arg0)->unk40->x;
    fz = ((Obj8E *) arg0)->unk40->z;
    ax = ((Obj8E *) arg0)->unk40->x + 50.0f;
    fy = ((Obj8E *) arg0)->unk40->y;
    ay = ((Obj8E *) arg0)->unk40->y + 50.0f;
    az = ((Obj8E *) arg0)->unk40->z + 50.0f;
    func_8026DCAC(fx, fy, fz, pos.i, 2);
    attr = func_8026D7D8(pos.i[0], pos.i[1], pos.i[2]);
    if (attr & 0x60) {
        a = 0xF;
    } else {
        a = attr & 0xF;
    }
    if (a == 0xF) {
        do {
            pos.i[1]++;
            more = 0;
            attr = func_8026D7D8(pos.i[0], pos.i[1], pos.i[2]);
            if (pos.i[1] < D_800B15D8->unk0 && ((attr & 0x60) || (attr & 0xF) == 0xF)) {
                more = 1;
            }
        } while (more);
        if (D_800B15D8) { /* fake: lifts the map address above the 0xF constant (s1) */
        }
        if (pos.i[1] >= D_800B15D8->unk0) {
            r = ((Obj8E *) arg0)->unk40->y;
        } else {
            h = func_8026E2B0(pos.i[1]);
            if (func_8026E278(attr) != 0) {
                r = func_8026E3AC(fx + 50.0f, h + 50.0f, fz + 50.0f);
            } else {
                r = h;
            }
        }
    } else if (func_8026E278(a) != 0) {
        r = func_8026E3AC(ax, ay, az);
    } else {
        r = ((Obj8E *) arg0)->unk40->y;
    }
    return r;
}

f32 func_8026E938(u8 *arg0) {
    s32 padA[1];
    f32 fx;
    f32 fy;
    f32 fz;
    s32 padB[2];
    s32 padC[3];
    f32 v[3];
    Unk8026DCAC pos;
    s32 padD[3];
    f32 r;
    s32 x;
    s32 y;
    s32 z;
    s32 a;
    s32 b;

    if ((D_802AFC54 != 0) && (func_8026E8E0((s32) arg0) != 0)) {
        r = M2C_FIELD(arg0, f32 *, 0x14);
    } else {
        fz = M2C_FIELD(arg0, f32 *, 0x18);
        fx = M2C_FIELD(arg0, f32 *, 0x10);
        fy = M2C_FIELD(arg0, f32 *, 0x14);
        func_8026DCAC(fx, fy, fz, &pos, 2);
        x = pos.i[0];
        y = pos.i[1];
        z = pos.i[2];
        do {
            a = func_8026D7D8(x, y, z);
            b = func_8026D7D8(x, y - 1, z);
            if (((a & 0xF) == 0) && !(b & 0x60)) {
                y--;
            }
        } while (((a & 0xF) == 0) && !(b & 0x60) && (y >= 0));
        if (y >= 0) {
            if (func_8026E278(a) != 0) {
                r = func_8026E3AC(fx + 50.0f, fy, fz + 50.0f);
            } else {
                v[0] = x * 100.0f;
                r = func_8026E2B0((s32) (f32) y);
            }
        } else if (func_8026E8C8()) {
            r = 20000.0f;
        } else {
            r = func_8026E8B8();
        }
        if (z) { /* fake: keeps z live (permuter find) */
        }
    }
    return r;
}

s32 func_8026E8E0(s32 arg0) {
    u8 *p;
    s32 r;

    r = 0;
    for (p = D_802A55F4; p != NULL; p = M2C_FIELD(p, u8 **, 0x7C)) {
        if (arg0 == M2C_FIELD(p, s32 *, 0x40)) {
            if (M2C_FIELD(p, s32 *, 8) & 1) {
                r = 1;
            }
            break;
        }
    }
    return r;
}

s32 func_8026E8C8() {
    return (u8) D_800B15D8->unkC >> 7;
}

f32 func_8026E8B8() {
    return D_802AFC5C;
}

void func_8026E6E4(u8 *arg0, f32 *arg1, f32 *arg2) {
    s32 pad[3];
    s32 sp78[3];
    f32 sp6C[3];
    f32 temp_fs3;
    f32 temp_fs4;
    f32 var_fs0;
    s32 temp_v1;
    s32 temp_v0;

    temp_fs3 = M2C_FIELD(arg0, f32 *, 0x10);
    var_fs0 = M2C_FIELD(arg0, f32 *, 0x14);
    temp_fs4 = M2C_FIELD(arg0, f32 *, 0x18);
    do {
        func_8026DCAC(temp_fs3, var_fs0, temp_fs4, sp78, 2);
        temp_v0 = func_8026D7D8(sp78[0], sp78[1], sp78[2]);
        temp_v1 = temp_v0 & 0xF;
        if ((temp_v1 == 0) && (var_fs0 >= 0.0f)) {
            var_fs0 -= 100.0f;
        }
    } while ((temp_v1 == 0) && (var_fs0 >= 0.0f));
    *arg1 = 0.0f;
    switch (temp_v1) {
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
    s32 pad[3];
    Unk8026DCAC sp90;
    f32 pos[3];
    f32 sp78[3];
    f32 s;
    f32 pad2;
    f32 y;
    f32 fz;
    f32 r;

    do {
        func_8026DCAC(arg0, arg1, arg2, &sp90, 0);
        fz = sp90.i[2];
        pos[0] = (f32) sp90.i[0] * 100.0f;
        y = func_8026E2B0((f32) sp90.i[1]);
        pos[2] = fz * 100.0f;
        pos[1] = y;
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
            return 0.0;
        }
        r = pos[1] + sp78[2] * s;
    } else {
        r = pos[1] - 1.0f;
    }
    return r;
}

void func_8026E338(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, s32 arg4) {
    M2C_FIELD(arg3, f32 *, 0) = arg0 * 100.0f;
    M2C_FIELD(arg3, f32 *, 4) = func_8026E2B0((s32) arg1);
    M2C_FIELD(arg3, f32 *, 8) = (f32) (arg2 * 100.0f);
}

f32 func_8026E2B0(s32 arg0) {
    s32 i;
    s32 n;
    s32 sum;
    f32 r;

    if (arg0 >= 0) {
        sum = 0;
        n = arg0;
        for (i = 0; i < n; i++) {
            sum += func_8026DC74(i);
        }
        r = sum * 100.0f;
    } else {
        r = -32700.0f;
    }
    return r;
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
    f32 scale;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0_2;
    s32 temp_a0;
    s32 ix;
    s32 iz;
    s32 dx;
    s32 dz;
    s32 temp_v0;
    s32 kind;
    s32 nz;
    f32 base;
    f32 lo;
    f32 hi;
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
    switch (kind) {
        case 3:
        case 4:
            scale = 100.0f;
            dx = 0;
            dz = 1;
            ix = 0;
            iz = 1;
            base = spA8.f[2];
            break;
        case 5:
        case 6:
            scale = 100.0f;
            dx = 1;
            dz = 0;
            ix = 1;
            iz = 0;
            base = spA8.f[0];
            break;
        default:
            hi = lo = 0;
            kind = 0;
            break;
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
    temp_v0 = D_800B15D8[spA8.i[1]].unk10;
    if (count == 0) {
        var_fa0_2 = 0.0f;
    } else {
        temp_fv0 = (f32) temp_v0 * 100.0f;
        temp_fv1 = (f32) count;
        temp_fa1 = temp_fv0 / (temp_fv1 * scale);
        var_fa0_2 = temp_fa1;
        if (temp_fv0 != (temp_fv1 * temp_fa1 * scale)) {
            var_fa0_2 = temp_fa1 + 0.001f;
        }
    }
    arg3[2] = var_fa0_2;
}

s32 func_8026DF74(f32 arg0, f32 arg1, f32 arg2) {
    s32 sp24[7]; /* only [0..2] are read; the size comes from the frame */

    func_8026DCAC(arg0, arg1, arg2, sp24, 2);
    return func_8026D7D8(sp24[0], sp24[1], sp24[2]);
}

void func_8026DCAC(f32 arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4) {
    s32 ix;
    s32 iy;
    s32 h;
    s32 layer;
    s32 ry;

    ry = 0;
    ((Unk8026DCAC *) arg3)->i[0] = (s32) (arg0 * 0.01f);
    ((Unk8026DCAC *) arg3)->i[2] = (s32) (arg2 * 0.01f);
    if (arg0 < 0.0f) {
        ((Unk8026DCAC *) arg3)->i[0]--;
    }
    if (arg2 < 0.0f) {
        ((Unk8026DCAC *) arg3)->i[2]--;
    }
    h = 0;
    for (layer = 0; layer < D_800B15D8->unk0 + 1; layer++) {
        iy = (s32) (arg1 * 0.01f);
        if (iy && iy) { /* fake: two loop uses of iy (hoisted out of the
                         * loop) raise it over the layer pointer */
        }
        if (&D_800B15D8[layer] == NULL) {
        }
        if (iy < h) {
            if (layer > 0) {
                /* fake: h is dead after the break; this keeps the
                 * ugen temporaries below in step with the original */
                h = layer - 1;
                ((Unk8026DCAC *) arg3)->i[1] = h;
            } else {
                ((Unk8026DCAC *) arg3)->i[1] = layer;
            }
            break;
        }
        if (h == iy) {
            ((Unk8026DCAC *) arg3)->i[1] = layer;
            ry = h;
            break;
        }
        ry = h;
        h += func_8026DC74(layer);
    }
    if (D_800B15D8->unk0 < layer) {
        ((Unk8026DCAC *) arg3)->i[1] = D_800B15D8->unk0;
    }
    if (arg1 < 0.0f) {
        ((Unk8026DCAC *) arg3)->i[1] = -1;
        if (layer) { /* fake: keeps layer in a2 */
        }
    }
    ix = ((Unk8026DCAC *) arg3)->i[0];
    ((Unk8026DCAC *) arg3)->f[0] = arg0 - (f32) ix * 100.0f;
    ((Unk8026DCAC *) arg3)->f[1] = arg1 - (f32) ry * 100.0f;
    ((Unk8026DCAC *) arg3)->f[2] = arg2 - (f32) ((Unk8026DCAC *) arg3)->i[2] * 100.0f;
    if (arg4 & 2) {
        if (((Unk8026DCAC *) arg3)->f[0] >= 50.0f) {
            ((Unk8026DCAC *) arg3)->i[0] = ix + 1;
        }
        if (((Unk8026DCAC *) arg3)->f[2] >= 50.0f) {
            ((Unk8026DCAC *) arg3)->i[2]++;
        }
        ((Unk8026DCAC *) arg3)->f[0] = ((Unk8026DCAC *) arg3)->f[0] - 50.0;
        ((Unk8026DCAC *) arg3)->f[2] = ((Unk8026DCAC *) arg3)->f[2] - 50.0;
    }
    if (D_802AC8A0 == 1 && (((Unk8026DCAC *) arg3)->f[0] == 100.0f || ((Unk8026DCAC *) arg3)->f[1] == 100.0f || ((Unk8026DCAC *) arg3)->f[2] == 100.0f)) {
        func_80297D38(D_802A3B60);
    }
}

u8 func_8026DC74(s32 arg0) {
    return D_800B15D8[arg0].unk10;
}

void func_8026DB88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 i;
    s32 n;

    n = D_800B15D8->unk0;
    if (arg4 < arg1) {
        i = arg1;
        arg1 = arg4;
        arg4 = i;
    }
    if (arg1 < 0) {
        arg1 = 0;
    }
    if (arg4 < 0) {
        arg4 = 0;
    }
    if (n < arg1) {
        arg1 = n;
    }
    if (n < arg4) {
        arg4 = n;
    }
    for (i = arg1; i <= arg4; i++) {
        func_8026DA2C(arg0, i, arg2, arg3, arg5, arg6);
    }
}

void func_8026DA2C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i;
    s32 j;
    s32 size[3];

    func_802438BC(size);
    if (arg3 < arg0) {
        i = arg0;
        arg0 = arg3;
        arg3 = i;
    }
    if (arg0 < 0) {
        arg0 = 0;
    }
    if (arg3 < 0) {
        arg3 = 0;
    }
    if (size[0] < arg0) {
        arg0 = size[0];
    }
    if (size[0] < arg3) {
        arg3 = size[0];
    }
    if (arg4 < arg2) {
        i = arg2;
        arg2 = arg4;
        arg4 = i;
    }
    if (arg2 < 0) {
        arg2 = 0;
    }
    if (arg4 < 0) {
        arg4 = 0;
    }
    if (size[2] < arg2) {
        arg2 = size[2];
    }
    if (size[2] < arg4) {
        arg4 = size[2];
    }
    for (i = arg2; i <= arg4; i++) {
        for (j = arg0; j <= arg3; j++) {
            func_8026D620(j, arg1, i, arg5);
        }
    }
}

void func_8026DA1C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = arg3;
}

void func_8026D92C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 i;
    s32 j;

    for (i = 0; i <= arg4 - arg2; i++) {
        for (j = 0; j <= arg3 - arg0; j++) {
            func_8026D620(arg5 + j, arg6, arg7 + i, func_8026D7D8(arg0 + j, arg1, arg2 + i));
        }
    }
}

s32 func_8026D7D8(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;
    s32 xmax;
    s32 zmax;
    s32 var_a0;
    s32 cell;
    s32 slot;

    var_v1 = 0;
    if (arg1 < 0) {
        arg1 = 0;
        var_v1 = 1;
    }
    xmax = D_800B15D8->unk1 + D_800B15D8->unk4 * 8 - 1;
    zmax = D_800B15D8->unk3 + D_800B15D8->unk8 * 8 - 1;
    if (xmax < arg0 || zmax < arg2 || arg0 < 0 || arg2 < 0 || arg1 >= D_800B15D8->unk0) {
        var_a0 = D_802AFC58;
    } else {
        cell = func_8026D5F8(arg0, arg1, arg2);
        slot = func_8026D5C0(arg0, arg1, arg2);
        var_a0 = D_800B15D8[arg1].unk12[cell].unk2[slot];
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

void func_8026D620(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 cell;
    s32 slot;

    cell = func_8026D5F8(arg0, arg1, arg2);
    slot = func_8026D5C0(arg0, arg1, arg2);
    D_800B15D8[arg1].unk12[cell].unk2[slot] = arg3;
}

s32 func_8026D5F8(s32 arg0, s32 arg1, s32 arg2) {
    s32 r;
    r = ((arg2 >> 3) * D_800B15D8->unk4) + (arg0 >> 3);
    return r;
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
