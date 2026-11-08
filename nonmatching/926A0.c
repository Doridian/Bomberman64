/*
 * NON_MATCHING: main_code's 926A0, complete (14 functions,
 * func_80277EA0..func_80278FD8). Split from 8E730 by IDO's emission
 * order (text_objects.txt). A first draft from m2c; every function
 * global, emitted in the original's order. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 805, eu 805, jp 805
 *
 * 7 of 14 match. Biggest left: func_80277FC4 430 and func_802787E4 341,
 * which index D_8008E658 (0x48-byte records) untyped.
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

u8 func_8026DC74(s32 arg0);
void func_8027404C(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
s32 func_80277EA0(s16 arg0);
s16 func_80277F0C(u8 *arg0);
s16 func_80277F74(void);
void *func_80277FC4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s16 arg8, s32 arg9);
void func_80278740(s32 *arg0);
void func_80278788(s32 *arg0);
void func_802787E4(s32 *arg0);
void func_80278D54(s32 *arg0);
void func_80278DBC(void);
void func_80278E28(s16 arg0, s16 arg1);
void func_80278E84(s16 arg0, s16 arg1);
void func_80278F00(s16 arg0);
void func_80278F68(void);
void func_80278FD8(u32 arg0, u8 **arg1);

void func_80278FD8(u32 arg0, u8 **arg1) {
    s32 sp1C[2];
    u8 *temp_v0;
    struct UnkStruct_80225CC0 *temp_v0_2;

    func_8022638C(arg0, sp1C);
    temp_v0 = malloc(sp1C[1]);
    *arg1 = temp_v0;
    if (temp_v0 != NULL) {
        temp_v0_2 = func_80226604(arg0, 1);
        func_8022616C(*arg1, 1, sp1C[1], temp_v0_2);
        func_80226368(temp_v0_2);
    }
}

void func_80278F68() {
    s16 var_v0;
    s16 var_v0_2;
    s32 *var_v1;
    s32 temp_lo;

    D_802AFE70 = 0;
    var_v0 = 0;
    do {
        temp_lo = var_v0 * 0xC8;
        var_v0 += 1;
        M2C_FIELD((D_800AEDF0 + temp_lo), s32 *, 0x20) = 2;
    } while (var_v0 < 5);
    var_v1 = &D_8008E658;
    var_v0_2 = 0;
    do {
        var_v0_2 += 1;
        var_v1 = (void *) ((u8 *)var_v1 + 0x48);
        M2C_FIELD(var_v1, s32 *, -0x30) = 0;
    } while (var_v0_2 < 0x30);
}

void func_80278F00(s16 arg0) {
    switch (arg0) {                                 /* irregular */
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
    s32 var_v1;
    u8 *temp_v0;

    temp_v0 = (arg0 * 0xC8) + D_800AEDF0;
    M2C_FIELD(temp_v0, s32 *, 0x20) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x20) + arg1);
    if (M2C_FIELD(temp_v0, s32 *, 0x18) & 5) {
        var_v1 = 7;
    } else {
        var_v1 = 4;
    }
    if (var_v1 < M2C_FIELD(temp_v0, s32 *, 0x20)) {
        M2C_FIELD(temp_v0, s32 *, 0x20) = var_v1;
    }
}

void func_80278E28(s16 arg0, s16 arg1) {
    s32 temp_t3;
    u8 *temp_v0;

    temp_v0 = (arg0 * 0xC8) + D_800AEDF0;
    temp_t3 = M2C_FIELD(temp_v0, s32 *, 0x20) - arg1;
    M2C_FIELD(temp_v0, s32 *, 0x20) = temp_t3;
    if (temp_t3 < 2) {
        M2C_FIELD(temp_v0, s32 *, 0x20) = 2;
    }
}

void func_80278DBC() {
    s16 var_s1;
    s32 *var_s0;

    var_s0 = &D_8008E658;
    var_s1 = 0;
    do {
        if (M2C_FIELD(var_s0, s32 *, 0x18) != 0) {
            func_80278740(var_s0);
            M2C_FIELD(var_s0, s16 *, 0x36) = 0;
        }
        var_s1 += 1;
        var_s0 = (void *) ((u8 *)var_s0 + 0x48);
    } while (var_s1 < 0x30);
    D_802AFE70 = 0;
}

void func_80278D54(s32 *arg0) {
    s16 temp_v0;

    func_80232DB4(M2C_FIELD(arg0, void **, 0x14));
    temp_v0 = M2C_FIELD(arg0, s16 *, 0xC);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_802787E4(arg0);
        return;
    case 2:
        func_80278788(arg0);
        return;
    }
}

void func_802787E4(s32 *arg0) {
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs0_3;
    f32 temp_fs0_4;
    f32 temp_fs0_5;
    f32 temp_fs0_6;
    f32 temp_fs0_7;
    f32 temp_fv0;
    f32 var_fv1;
    f32 var_fv1_2;
    s16 temp_v0;
    s16 temp_v0_3;
    s32 var_at;
    u16 temp_t9;
    u8 *temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x44);
    if (temp_v0 <= 0) {
        temp_t9 = M2C_FIELD(arg0, u16 *, 0xE);
        M2C_FIELD(arg0, s16 *, 0x38) = (s16) (M2C_FIELD(arg0, s16 *, 0x38) + M2C_FIELD(arg0, s16 *, 0x3A));
        switch (temp_t9) {
        case 0:
        case 1:
            temp_fs0 = func_80234434((f32) M2C_FIELD(arg0, s16 *, 0x38));
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s16 *, 0x36) = (s16) (s32) ((func_80234408((f32) M2C_FIELD(arg0, s16 *, 0x38)) * 191.0f) + 64.0f);
            M2C_FIELD(arg0, f32 *, 0x40) = (f32) (M2C_FIELD(arg0, f32 *, 0x40) + 5.0f);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x20) = (f32) M2C_FIELD(arg0, f32 *, 0x40);
            var_fv1 = M2C_FIELD(arg0, f32 *, 0x3C) * temp_fs0;
            M2C_FIELD(arg0, f32 *, 0x28) = var_fv1;
            M2C_FIELD(arg0, f32 *, 0x2C) = var_fv1;
block_10:
            M2C_FIELD(arg0, f32 *, 0x30) = var_fv1;
            break;
        case 2:
        case 3:
            temp_fs0_2 = func_80234434((f32) M2C_FIELD(arg0, s16 *, 0x38));
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s16 *, 0x36) = (s16) (s32) (func_80234408((f32) M2C_FIELD(arg0, s16 *, 0x38)) * 255.0f);
            M2C_FIELD(arg0, f32 *, 0x40) = (f32) (M2C_FIELD(arg0, f32 *, 0x40) + 5.0f);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x20) = (f32) M2C_FIELD(arg0, f32 *, 0x40);
            var_fv1 = M2C_FIELD(arg0, f32 *, 0x3C) * temp_fs0_2;
            M2C_FIELD(arg0, f32 *, 0x28) = var_fv1;
            M2C_FIELD(arg0, f32 *, 0x2C) = var_fv1;
            goto block_10;
        case 4:
            temp_fs0_3 = func_80234434((f32) M2C_FIELD(arg0, s16 *, 0x38));
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s16 *, 0x36) = (s16) (s32) (func_80234408((f32) M2C_FIELD(arg0, s16 *, 0x38)) * 255.0f);
            M2C_FIELD(arg0, f32 *, 0x40) = (f32) (M2C_FIELD(arg0, f32 *, 0x40) + 5.0f);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x20) = (f32) M2C_FIELD(arg0, f32 *, 0x40);
            var_fv1 = M2C_FIELD(arg0, f32 *, 0x3C) * temp_fs0_3 * 0.7f;
            M2C_FIELD(arg0, f32 *, 0x28) = var_fv1;
            M2C_FIELD(arg0, f32 *, 0x2C) = var_fv1;
            goto block_10;
        case 5:
            temp_fs0_4 = func_80234434((f32) M2C_FIELD(arg0, s16 *, 0x38));
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s16 *, 0x36) = (s16) (s32) (func_80234408((f32) M2C_FIELD(arg0, s16 *, 0x38)) * 255.0f);
            var_fv1 = M2C_FIELD(arg0, f32 *, 0x3C) * temp_fs0_4;
            M2C_FIELD(arg0, f32 *, 0x28) = var_fv1;
            M2C_FIELD(arg0, f32 *, 0x2C) = var_fv1;
            goto block_10;
        case 6:
            temp_fs0_5 = func_80234434((f32) M2C_FIELD(arg0, s16 *, 0x38));
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s16 *, 0x36) = (s16) (s32) (func_80234408((f32) M2C_FIELD(arg0, s16 *, 0x38)) * 255.0f);
            M2C_FIELD(arg0, f32 *, 0x40) = (f32) (M2C_FIELD(arg0, f32 *, 0x40) + 5.0f);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x20) = (f32) M2C_FIELD(arg0, f32 *, 0x40);
            var_fv1 = M2C_FIELD(arg0, f32 *, 0x3C) * temp_fs0_5;
            M2C_FIELD(arg0, f32 *, 0x28) = var_fv1;
            M2C_FIELD(arg0, f32 *, 0x2C) = var_fv1;
            goto block_10;
        case 7:
            temp_fs0_6 = func_80234434((f32) M2C_FIELD(arg0, s16 *, 0x38));
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s16 *, 0x36) = (s16) (s32) (func_80234408((f32) M2C_FIELD(arg0, s16 *, 0x38)) * 255.0f);
            var_fv1 = M2C_FIELD(arg0, f32 *, 0x3C) * temp_fs0_6 * 1.5f;
            M2C_FIELD(arg0, f32 *, 0x28) = var_fv1;
            M2C_FIELD(arg0, f32 *, 0x2C) = var_fv1;
            goto block_10;
        case 8:
            temp_fs0_7 = func_80234434((f32) M2C_FIELD(arg0, s16 *, 0x38));
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s16 *, 0x36) = (s16) (s32) (func_80234408((f32) M2C_FIELD(arg0, s16 *, 0x38)) * 255.0f);
            M2C_FIELD(arg0, f32 *, 0x40) = (f32) (M2C_FIELD(arg0, f32 *, 0x40) + 5.0f);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x20) = (f32) M2C_FIELD(arg0, f32 *, 0x40);
            var_fv1 = M2C_FIELD(arg0, f32 *, 0x3C) * temp_fs0_7 * 0.65f;
            M2C_FIELD(arg0, f32 *, 0x28) = var_fv1;
            M2C_FIELD(arg0, f32 *, 0x2C) = var_fv1;
            goto block_10;
        }
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x28) = (f32) M2C_FIELD(arg0, f32 *, 0x28);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x2C) = (f32) M2C_FIELD(arg0, f32 *, 0x2C);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), f32 *, 0x30) = (f32) M2C_FIELD(arg0, f32 *, 0x30);
        temp_v0_2 = M2C_FIELD(arg0, void **, 0x18);
        temp_fv0 = M2C_FIELD(temp_v0_2, f32 *, 0x20);
        if (temp_fv0 >= 360.0f) {
            M2C_FIELD(temp_v0_2, f32 *, 0x20) = (f32) (temp_fv0 - 360.0f);
        } else {
            if (temp_fv0 < 0.0f) {
                var_fv1_2 = temp_fv0 + 360.0f;
            } else {
                var_fv1_2 = temp_fv0;
            }
            M2C_FIELD(temp_v0_2, f32 *, 0x20) = var_fv1_2;
        }
        temp_v0_3 = M2C_FIELD(arg0, s16 *, 0x38);
        var_at = temp_v0_3 < 0x5B;
        if (temp_v0_3 >= 0x47) {
            func_802313DC(M2C_FIELD(arg0, void **, 0x14), 0x40);
            var_at = M2C_FIELD(arg0, s16 *, 0x38) < 0x5B;
        }
        if (var_at == 0) {
            func_80278740(arg0);
        }
    } else {
        M2C_FIELD(arg0, s16 *, 0x44) = (s16) (temp_v0 - 1);
    }
}

void func_80278788(s32 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x44);
    if (temp_v0 <= 0) {
        M2C_FIELD(arg0, s16 *, 0x3A) = (s16) (M2C_FIELD(arg0, s16 *, 0x3A) - 1);
        if (M2C_FIELD(arg0, s16 *, 0x3A) == 0) {
            M2C_FIELD(arg0, s16 *, 0x36) = 0;
            func_80278740(arg0);
        }
    } else {
        M2C_FIELD(arg0, s16 *, 0x44) = (s16) (temp_v0 - 1);
    }
}

void func_80278740(s32 *arg0) {
    func_8022FC90(M2C_FIELD(arg0, void **, 0x14));
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    *M2C_FIELD(arg0, s32 **, 8) = 0;
    D_802AFE70 -= 1;
}

void *func_80277FC4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s16 arg8, s32 arg9) {
    s16 sp44;
    s32 sp40;
    s32 sp3C;
    f32 sp38;
    u8 *sp28;
    u32 sp24;
    f32 temp_ft5;
    f32 var_ft5;
    f32 var_fv1;
    s16 temp_t2;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v1_2;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 var_a1;
    s32 var_t7;
    u8 *temp_t0;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *var_t0;

    temp_v0 = func_80277F74();
    if (temp_v0 == -1) {
        return NULL;
    }
    temp_t0 = (temp_v0 * 0x48) + &D_8008E658;
    M2C_FIELD(temp_t0, s16 *, 0) = temp_v0;
    M2C_FIELD(temp_t0, s16 *, 0xC) = 1;
    sp28 = temp_t0;
    M2C_FIELD(temp_t0, s16 *, 0xE) = arg1;
    M2C_FIELD(temp_t0, s16 *, 0x10) = arg2;
    M2C_FIELD(temp_t0, s32 *, 8) = arg9;
    func_8027404C(arg5, arg6, arg7, temp_t0 + 0x1C, temp_t0 + 0x20, temp_t0 + 0x24);
    var_t0 = temp_t0;
    if (arg6 < 0.0f) {
        M2C_FIELD(var_t0, f32 *, 0x20) = (f32) (arg6 * 100.0f);
    } else {
        var_fv1 = arg6;
        if (arg6 >= 1.0f) {
            do {
                var_fv1 = (f32) ((f64) var_fv1 - 1.0);
            } while (var_fv1 >= 1.0f);
        }
        sp28 = var_t0;
        sp38 = var_fv1;
        M2C_FIELD(var_t0, f32 *, 0x20) = (f32) (M2C_FIELD(var_t0, f32 *, 0x20) + (var_fv1 * ((f32) func_8026DC74((s32) arg6) * 100.0f)));
    }
    M2C_FIELD(var_t0, s16 *, 0x38) = 0;
    sp24 = (u32) arg1;
    M2C_FIELD(var_t0, s16 *, 0x36) = arg8;
    M2C_FIELD(var_t0, s16 *, 0x46) = arg0;
    switch (arg1) {                                 /* switch 1 */
    case 0:                                         /* switch 1 */
    case 1:                                         /* switch 1 */
    case 2:                                         /* switch 1 */
        sp28 = var_t0;
        temp_v1 = M2C_FIELD(var_t0, s16 *, 0x10);
        var_a1 = 0x01080040;
        M2C_FIELD(var_t0, s16 *, 0x3A) = (s16) (0x5A / func_80277EA0(arg8));
        if (temp_v1 & 0x100) {
            var_a1 = 0x01082040;
        }
        if (temp_v1 & 5) {
            var_a1 |= 0x4000;
        }
        sp40 = var_a1;
        sp28 = var_t0;
        temp_v0_2 = func_80277F0C(var_t0);
        sp44 = temp_v0_2;
        if (M2C_FIELD(var_t0, s16 *, 0x10) & 5) {
            sp3C = 7;
        } else {
            switch (arg1) {                         /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                sp3C = 0x10;
                break;
            case 1:                                 /* switch 2 */
                sp3C = 0x11;
                break;
            case 2:                                 /* switch 2 */
                sp3C = 6;
                break;
            }
        }
        sp40 = var_a1;
        break;
    case 3:                                         /* switch 1 */
    case 4:                                         /* switch 1 */
        sp28 = var_t0;
        temp_lo = 0x5A / func_80277EA0(arg8);
        sp44 = 0xD0;
        M2C_FIELD(var_t0, s16 *, 0x3A) = (s16) temp_lo;
        if (M2C_FIELD(var_t0, s16 *, 0x10) & 5) {
            sp3C = 9;
        } else {
            sp3C = 8;
        }
        sp40 = 0x01080000;
        break;
    case 5:                                         /* switch 1 */
        M2C_FIELD(var_t0, s16 *, 0x3A) = 4;
        sp44 = 0xD0;
        sp3C = 0xB;
        sp40 = 0x01080000;
        break;
    case 6:                                         /* switch 1 */
        sp28 = var_t0;
        temp_lo_2 = 0x5A / func_80277EA0(arg8);
        sp44 = 0xD0;
        sp3C = 0xD;
        sp40 = 0x01080000;
        M2C_FIELD(var_t0, s16 *, 0x3A) = (s16) temp_lo_2;
        break;
    case 7:                                         /* switch 1 */
        sp28 = var_t0;
        temp_lo_3 = 0x5A / func_80277EA0(arg8);
        sp44 = 0xD0;
        sp3C = 0xE;
        sp40 = 0x01080000;
        M2C_FIELD(var_t0, s16 *, 0x3A) = (s16) temp_lo_3;
        break;
    case 8:                                         /* switch 1 */
        sp28 = var_t0;
        temp_ft5 = 90.0f / ((f32) func_80277EA0(arg8) * 0.5f);
        sp44 = 0xD0;
        sp3C = 0xF;
        sp40 = 0x01080000;
        M2C_FIELD(var_t0, s16 *, 0x3A) = (s16) (s32) temp_ft5;
        break;
    }
    sp28 = var_t0;
    temp_v0_3 = func_80231274(sp3C, sp40, (s32) sp44, NULL);
    if (temp_v0_3 == NULL) {
        return NULL;
    }
    M2C_FIELD(temp_v0_3, s32 *, 0x30) = 1;
    M2C_FIELD(temp_v0_3, f32 *, 0x38) = 0.0f;
    M2C_FIELD(temp_v0_3, f32 *, 0x34) = 40.0f;
    M2C_FIELD(var_t0, void **, 0x14) = temp_v0_3;
    M2C_FIELD(var_t0, void **, 0x18) = (void *) M2C_FIELD(temp_v0_3, void **, 0x40);
    M2C_FIELD(var_t0, s16 *, 0x44) = arg3;
    if (sp24 == 5) {
        temp_v0_4 = M2C_FIELD(temp_v0_3, void **, 0x40);
        M2C_FIELD(temp_v0_4, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_4, s32 *, 0xC) | 0x8000);
        sp28 = var_t0;
        func_8022984C(M2C_FIELD(M2C_FIELD(var_t0, void **, 0x14), void **, 0x40), 1);
        func_802297B8(M2C_FIELD(M2C_FIELD(var_t0, void **, 0x14), s32 *, 0x40), 0xC, 0, 0);
    }
    M2C_FIELD(var_t0, f32 *, 0x40) = 0.0f;
    M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x20) = 0.0f;
    switch (sp24) {                                 /* switch 3 */
    case 0:                                         /* switch 3 */
    case 1:                                         /* switch 3 */
    case 2:                                         /* switch 3 */
    case 3:                                         /* switch 3 */
    case 4:                                         /* switch 3 */
    case 6:                                         /* switch 3 */
    case 7:                                         /* switch 3 */
    case 8:                                         /* switch 3 */
        M2C_FIELD(var_t0, f32 *, 0x28) = 0.1f;
        M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x28) = 0.1f;
        M2C_FIELD(var_t0, f32 *, 0x2C) = 0.1f;
        M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x2C) = 0.1f;
        M2C_FIELD(var_t0, f32 *, 0x30) = 0.1f;
        M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x30) = 0.1f;
        break;
    case 5:                                         /* switch 3 */
        M2C_FIELD(var_t0, f32 *, 0x28) = 0.05f;
        M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x28) = 0.05f;
        M2C_FIELD(var_t0, f32 *, 0x2C) = 0.05f;
        M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x2C) = 0.05f;
        M2C_FIELD(var_t0, f32 *, 0x30) = 0.05f;
        M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x30) = 0.05f;
        break;
    }
    M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x10) = (f32) M2C_FIELD(var_t0, f32 *, 0x1C);
    M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x14) = (f32) M2C_FIELD(var_t0, f32 *, 0x20);
    M2C_FIELD(M2C_FIELD(var_t0, void **, 0x18), f32 *, 0x18) = (f32) M2C_FIELD(var_t0, f32 *, 0x24);
    if (sp24 == 5) {
        temp_v0_5 = M2C_FIELD(var_t0, void **, 0x18);
        M2C_FIELD(temp_v0_5, f32 *, 0x14) = (f32) ((f64) M2C_FIELD(temp_v0_5, f32 *, 0x14) + 30.0);
    }
    temp_v1_2 = M2C_FIELD(var_t0, s16 *, 0x10);
    if (temp_v1_2 & 5) {
        var_t7 = temp_v1_2 & 0x100;
        if (M2C_FIELD(var_t0, s16 *, 0x36) >= 0xA) {
            M2C_FIELD(var_t0, s16 *, 0x36) = 8;
            goto block_47;
        }
    } else {
        var_t7 = temp_v1_2 & 0x100;
        if (M2C_FIELD(var_t0, s16 *, 0x36) >= 7) {
            M2C_FIELD(var_t0, s16 *, 0x36) = 5;
block_47:
            var_t7 = M2C_FIELD(var_t0, s16 *, 0x10) & 0x100;
        }
    }
    if (var_t7 != 0) {
        if (M2C_FIELD(var_t0, s16 *, 0x10) & 5) {
            M2C_FIELD(var_t0, s16 *, 0x36) = 9;
        } else {
            M2C_FIELD(var_t0, s16 *, 0x36) = 6;
        }
    }
    temp_t2 = M2C_FIELD(var_t0, s16 *, 0x36);
    switch (temp_t2) {                              /* switch 4 */
    case 3:                                         /* switch 4 */
        M2C_FIELD(var_t0, f32 *, 0x3C) = 3.0f;
        break;
    case 4:                                         /* switch 4 */
        var_ft5 = 4.5f;
block_62:
        M2C_FIELD(var_t0, f32 *, 0x3C) = var_ft5;
        break;
    case 5:                                         /* switch 4 */
        M2C_FIELD(var_t0, f32 *, 0x3C) = 6.0f;
        break;
    case 6:                                         /* switch 4 */
        M2C_FIELD(var_t0, f32 *, 0x3C) = 7.5f;
        break;
    case 7:                                         /* switch 4 */
        M2C_FIELD(var_t0, f32 *, 0x3C) = 9.0f;
        break;
    case 8:                                         /* switch 4 */
        M2C_FIELD(var_t0, f32 *, 0x3C) = 10.5f;
        break;
    case 9:                                         /* switch 4 */
        M2C_FIELD(var_t0, f32 *, 0x3C) = 12.0f;
        break;
    default:                                        /* switch 4 */
        var_ft5 = 3.0f;
        goto block_62;
    }
    D_802AFE70 += 1;
    return var_t0;
}

s16 func_80277F74() {
    s16 var_v1;
    s32 *var_v0;
    s32 var_at;

    var_v0 = &D_8008E658;
    var_v1 = 0;
loop_1:
    var_at = var_v1 < 0x30;
    if (M2C_FIELD(var_v0, s32 *, 0x18) != 0) {
        var_v1 += 1;
        var_v0 = (void *) ((u8 *)var_v0 + 0x48);
        if (var_v1 >= 0x30) {
            var_at = var_v1 < 0x30;
        } else {
            goto loop_1;
        }
    }
    if (var_at != 0) {
        return var_v1;
    }
    return -1;
}

s16 func_80277F0C(u8 *arg0) {
    s16 temp_t6;
    s16 var_v1;

    temp_t6 = M2C_FIELD(arg0, s16 *, 0x10) & 0xF1FD;
    var_v1 = 0x40;
    if (temp_t6 == 0x100) {
        var_v1 = 0x10;
    }
    if ((temp_t6 == 1) || (temp_t6 == 4) || (temp_t6 == 5)) {
        var_v1 = 0x10;
    }
    if ((temp_t6 == 0x101) || (temp_t6 == 0x104) || (temp_t6 == 0x105)) {
        var_v1 = 0;
    }
    return var_v1;
}

s32 func_80277EA0(s16 arg0) {
    s32 var_v1;

    var_v1 = 0x28;
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
        var_v1 = 0x2D;
        /* fallthrough */
    default:
        return var_v1;
    }
}
