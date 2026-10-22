#include "common.h"

/* A controller's input, one per frame in a ring of 16 per controller. */
typedef struct {
    /* 0x00 */ u16 unk0; /* buttons held */
    /* 0x02 */ u16 unk2; /* buttons newly pressed */
    /* 0x04 */ s8 unk4;  /* stick x */
    /* 0x05 */ s8 unk5;  /* stick y */
} UnkStruct_802AC428; /* size 0x6 */

/* What the controller read gives, per controller. */
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s8 unk2;
    /* 0x03 */ s8 unk3;
    /* 0x04 */ u8 unk4;
} UnkStruct_802AC410; /* size 0x6 */

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
} UnkStruct_802AC400; /* size 0x4 */

/* One step of an input pattern (func_80239B08); a list ends at the entry
 * with bit 0 of unk0 set. */
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
} UnkStruct_80239B08; /* size 0x6 */

void func_80239094(void);
void func_8022FF58(f32 *, f32 *, f32 *);
s32 func_8023372C(f32, f32);
void func_80297D80(void *, void *, s32);
void func_80297D88(s32, void *, s32);
s32 func_80297D90(void *, void *, s32);
void func_80298030(void *, u8 *, UnkStruct_802AC400 *);
void func_80298038(void *);
void func_80298040(UnkStruct_802AC410 *);
void func_80298048(void *, UnkStruct_802AC400 *);
void func_80298050(void *);
void func_80298060(UnkStruct_802AC400 *);
void func_8027BD40(void);
void func_8027CDA4(void *);

s32 func_8023957C(s32 arg0, s32 arg1);
s8 func_802395A8(s32 arg0, s32 arg1);
s8 func_80239714(s32 arg0, s32 arg1);
u16 func_802399AC(s32 arg0);
s32 func_80239A94(s32 arg0);
s32 func_80239AB0(u8 arg0, u16 arg1, u16 arg2);
s32 func_80239B08(UnkStruct_80239B08 *arg0, UnkStruct_802AC428 *arg1, s32 *arg2);
s32 func_80239CC8(UnkStruct_80239B08 *arg0, s32 arg1);
s32 func_8023A0E4(s32 arg0);
void func_8023A104(void);
void func_8023A258(UnkStruct_802AC428 *arg0);
void func_8023A26C(void);
static void func_8023A310(void);
void func_8023A3AC(void);

extern void *D_802A015C[];
extern u8 D_802AC3E0[];
extern u8 D_802AC3F8[];
extern UnkStruct_802AC400 D_802AC400[4];
extern UnkStruct_802AC410 D_802AC410[4];
extern UnkStruct_802AC428 D_802AC428[4][16];
extern s32 D_802AC5A8[4];
extern s32 D_802AC5B8;

void func_8023A3AC(void) {
    func_80298048(D_802AC3E0, D_802AC400);
}

void func_8023A318(void) {
    u8 sp1F;

    func_8023A310();
    func_80297D30(0x1B, D_802A015C);
    func_8027BD40();
    func_8023A26C();
    D_802AC5B8 = 3;
    func_80297D80(D_802AC3E0, D_802AC3F8, 1);
    func_80297D88(5, D_802AC3E0, 0);
    func_80298030(D_802AC3E0, &sp1F, D_802AC400);
    func_8027CDA4(D_802AC3E0);
}

/* A static function IDO -O3 inlined into func_8023A318.  It still emits
 * one as a bare `jr ra` stub just before the caller, and splat counts the
 * stub as func_8023A26C's tail.  What it did is unknown (nothing is left
 * of it in func_8023A318): written as empty. */
static void func_8023A310(void) {
}

void func_8023A26C(void) {
    s32 i;
    s32 j;
    UnkStruct_802AC428 *p;

    for (i = 0; i < 4; i++) {
        D_802AC5A8[i] = 0;
        p = D_802AC428[i];
        for (j = 0; j < 16; j++) {
            func_8023A258(p++);
        }
    }
}

void func_8023A258(UnkStruct_802AC428 *arg0) {
    arg0->unk0 = 0;
    arg0->unk2 = 0;
    arg0->unk4 = 0;
    arg0->unk5 = 0;
}

void func_8023A22C(void) {
    func_80298038(D_802AC3E0);
    func_8023A104();
}

void func_8023A208(void) {
    func_80298038(D_802AC3E0);
}

void func_8023A104(void) {
    s32 i;
    UnkStruct_802AC428 *prev;
    UnkStruct_802AC428 *e;

    func_80297D90(D_802AC3E0, NULL, 1);
    for (i = 0; i < 4; i++) {
        D_802AC410[i].unk0 = 0;
        D_802AC410[i].unk2 = 0;
        D_802AC410[i].unk3 = 0;
        D_802AC410[i].unk4 = 0;
    }
    func_80298040(D_802AC410);
    for (i = 0; i < 4; i++) {
        prev = &D_802AC428[i][D_802AC5A8[i]];
        D_802AC5A8[i] = func_8023A0E4(D_802AC5A8[i]);
        e = &D_802AC428[i][D_802AC5A8[i]];
        e->unk0 = D_802AC410[i].unk0;
        e->unk4 = D_802AC410[i].unk2;
        e->unk5 = D_802AC410[i].unk3;
        e->unk2 = e->unk0 ^ prev->unk0;
        e->unk2 &= e->unk0;
    }
}

s32 func_8023A0E4(s32 arg0) {
    if (arg0 + 1 >= 16) {
        return 0;
    }
    return arg0 + 1;
}

void func_8023A0A0(void) {
    func_80298050(D_802AC3E0);
    func_80297D90(D_802AC3E0, NULL, 1);
    func_80298060(D_802AC400);
}

u16 func_8023A088(s32 arg0) {
    return D_802AC400[arg0].unk0;
}

u8 func_8023A070(s32 arg0) {
    return D_802AC400[arg0].unk2;
}

u8 func_8023A058(s32 arg0) {
    return D_802AC400[arg0].unk3;
}

u8 func_8023A038(s32 arg0) {
    return D_802AC410[arg0].unk4;
}

u16 func_80239FF8(s32 arg0) {
    return D_802AC428[arg0][D_802AC5A8[arg0]].unk0;
}

s8 func_80239F70(s32 arg0) {
    return (D_802AC5B8 < D_802AC428[arg0][D_802AC5A8[arg0]].unk4)
               ? D_802AC428[arg0][D_802AC5A8[arg0]].unk4 - D_802AC5B8
           : (D_802AC428[arg0][D_802AC5A8[arg0]].unk4 < -D_802AC5B8)
               ? D_802AC428[arg0][D_802AC5A8[arg0]].unk4 + D_802AC5B8
               : 0;
}

s8 func_80239EE8(s32 arg0) {
    return (D_802AC5B8 < D_802AC428[arg0][D_802AC5A8[arg0]].unk5)
               ? D_802AC428[arg0][D_802AC5A8[arg0]].unk5 - D_802AC5B8
           : (D_802AC428[arg0][D_802AC5A8[arg0]].unk5 < -D_802AC5B8)
               ? D_802AC428[arg0][D_802AC5A8[arg0]].unk5 + D_802AC5B8
               : 0;
}

u16 func_80239E88(s32 arg0, s32 arg1) {
    return D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk0;
}

u16 func_80239E28(s32 arg0, s32 arg1) {
    return D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk2;
}

s32 func_80239D6C(s32 arg0, u16 arg1, s32 arg2) {
    UnkStruct_80239B08 pat[2] = { { 0, 0, 0, 0 }, { 1, 0, 0, 0 } };

    pat[0].unk2 = arg1;
    pat[0].unk4 = arg2;
    pat[0].unk5 = arg2;
    if ((func_802399AC(arg0) & arg1) || func_80239CC8(pat, arg0) == 1) {
        return 1;
    }
    return -1;
}

s32 func_80239CC8(UnkStruct_80239B08 *arg0, s32 arg1) {
    UnkStruct_802AC428 *hist = D_802AC428[arg1];
    s32 idx = D_802AC5A8[arg1];

    while (!(arg0->unk0 & 1)) {
        if (!func_80239B08(arg0, hist, &idx)) {
            return 0;
        }
        arg0++;
    }
    return 1;
}

s32 func_80239B08(UnkStruct_80239B08 *arg0, UnkStruct_802AC428 *arg1, s32 *arg2) {
    s32 found = 0;
    s32 i = 0;
    s32 n;
    UnkStruct_802AC428 *e;

    while (i < arg0->unk5 && !found) {
        e = &arg1[*arg2];
        if (func_80239AB0(arg0->unk0, arg0->unk2, e->unk0)) {
            i++;
            n = 1;
            *arg2 = func_80239A94(*arg2);
            e = &arg1[*arg2];
            while (n < arg0->unk4 && i < arg0->unk5) {
                if (!func_80239AB0(arg0->unk0, arg0->unk2, e->unk0)) {
                    break;
                }
                *arg2 = func_80239A94(*arg2);
                e = &arg1[*arg2];
                n++;
                i++;
            }
            if (n >= arg0->unk4) {
                found = 1;
            }
        }
        *arg2 = func_80239A94(*arg2);
        i++;
    }
    return found;
}

s32 func_80239AB0(u8 arg0, u16 arg1, u16 arg2) {
    if (arg0 & 2) {
        if (arg1 == arg2) {
            return 1;
        }
        return 0;
    }
    if (arg1 == (arg1 & arg2)) {
        return 1;
    }
    return 0;
}

s32 func_80239A94(s32 arg0) {
    if (arg0 - 1 < 0) {
        return 15;
    }
    return arg0 - 1;
}

void func_802399EC(s32 arg0, u16 arg1) {
    if (!arg1) {
        arg1 = 0xF03F;
    }
    do {
        func_80239094();
    /* fake: the comma (from the permuter) only swaps the `and`'s operands */
    } while (!(func_802399AC(arg0) & (0, arg1)));
}

u16 func_802399AC(s32 arg0) {
    return D_802AC428[arg0][D_802AC5A8[arg0]].unk2;
}

void func_80239880(s32 arg0, s32 arg1, f32 *arg2) {
    f32 a[3];
    f32 b[3];
    f32 c[3];

    a[2] = 0.0f;
    a[1] = 0.0f;
    a[0] = 0.0f;
    b[0] = func_80239714(arg0, arg1) * -1.0f;
    b[2] = func_802395A8(arg0, arg1);
    b[1] = 0.0f;
    func_8022FF58(a, b, c);
    if (func_8023372C(c[2], 0.001f) == 0) {
        c[0] = (c[0] + 180.0f >= 360.0f) ? c[0] + 180.0f - 360.0f : (c[0] + 180.0f < 0.0f) ? c[0] + 180.0f + 360.0f : c[0] + 180.0f;
        arg2[0] = c[0];
        arg2[1] = c[1];
        arg2[2] = c[2];
    } else {
        arg2[2] = 0.0f;
    }
}

s8 func_80239714(s32 arg0, s32 arg1) {
    return (D_802AC5B8 < D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk4)
               ? D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk4 - D_802AC5B8
           : (D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk4 < -D_802AC5B8)
               ? D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk4 + D_802AC5B8
               : 0;
}

s8 func_802395A8(s32 arg0, s32 arg1) {
    return (D_802AC5B8 < D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk5)
               ? D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk5 - D_802AC5B8
           : (D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk5 < -D_802AC5B8)
               ? D_802AC428[arg0][func_8023957C(D_802AC5A8[arg0], arg1)].unk5 + D_802AC5B8
               : 0;
}

s32 func_8023957C(s32 arg0, s32 arg1) {
    s32 i;

    if (arg1 < 0 || arg1 >= 16) {
        for (;;) {}
    }
    arg1 = arg0 - arg1;
    if (arg1 < 0) {
        arg1 += 16;
    }
    return arg1;
}

void func_80239570(s32 arg0) {
    D_802AC5B8 = arg0;
}

/* .data, after func_80239D6C's pattern: the functions it hands func_80297D30 */
void *D_802A015C[] = {
    func_8023A3AC,
    func_8023A0A0,
    func_8023A088,
    func_8023A070,
    func_8023A058,
    func_8023A038,
    func_80239FF8,
    func_802399AC,
    func_80239F70,
    func_80239EE8,
    func_80239CC8,
    func_80239E88,
    func_80239E28,
    func_80239714,
    func_802395A8,
    func_80239D6C,
    func_80239880,
    func_80239570,
};
