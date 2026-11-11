/*
 * NON_MATCHING: main_code's 48300, complete: 92 functions (us
 * 0x8022DB00-0x80233644) around three lists of 0x80-byte objects
 * (UnkStructA80: D_802A5578, D_802A55F8 and D_802A5678 head them, the 128
 * in D_800A3F00) and their collision shapes (spheres, cylinders and
 * boxes, func_8022E884). Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 2577, eu 2577, jp 2577
 *
 * A first draft: functions in the reverse of the ROM's order, which IDO
 * now emits exactly as the original does (stubs included); a handful by
 * hand, the rest m2c's with the fixes the -O3 build needs. 35 of 72
 * global blocks match. What is understood:
 *   - the function-local statics (D_802A5708-D_802A5770 and
 *     D_802A59D0-D_802A5A0C in func_8022E884, D_802A593C-48 in
 *     func_8022F844, D_802A5960-C8 in func_8022E4DC, D_802A5A14-20 in
 *     func_802304C0, D_802A5734/58/8C in func_8023017C) are reached with
 *     lui/%lo at every access, as the original does;
 *   - func_80232FF8 and func_80232FA8 are global: as statics IPA moved
 *     func_80232FF8's register saves into func_802334CC.
 * Biggest left: func_8022E884 (the frame is 0xC0 in the original, with
 * stubs at 0x8022E874/7C, 0x8022E170 and 0x8022E328: its cases are
 * probably inlined static helpers), func_80231D88 and func_80231434
 * (still m2c's), func_80232FF8 (m2c's locals: a 0xE0 frame against
 * 0x98), func_8022E4DC (the original copies vectors through three stack
 * slots, 0x18-0x20), func_8022FF58.
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

/* A collision shape's placement. */
typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 pos[3];
    /* 0x1C */ f32 rot[3];
    /* 0x28 */ f32 scale[3];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
} Shape;

/* Probably the whole of structs.h's UnkStructA, but this file stores
 * 0x7FFFFFFF in 0x18 and 0x1C, which UnkStructA has as floats. */
typedef struct UnkStructA80 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ void *unk3C;
    /* 0x40 */ Shape *unk40;
    /* 0x44 */ struct UnkStructA80 *unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ f32 unk4C[3];
    /* 0x58 */ f32 unk58[3];
    /* 0x64 */ s32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ struct UnkStructA80 *unk78;
    /* 0x7C */ struct UnkStructA80 *unk7C;
} UnkStructA80; /* size 0x80 */

/* A screen rectangle (0x40 bytes from func_8022A6C4). */
typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ f32 x0;
    /* 0x14 */ f32 y0;
    /* 0x18 */ f32 x1;
    /* 0x1C */ f32 y1;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} Rect40;




void func_8022946C(void *, s32);
void * func_8022A328(void *, s32, s32, s32, s32);
int func_8023369C(f32, f32, f32);
int func_802336E4(f32);
s32 func_8023372C(f32, f32);
s32 func_80233768(f32);
s32 func_802337EC(f32);
f32 func_80234408(f32);
f32 func_80234434(f32);
s32 func_80234768(void);
void func_802348B4(f32 *, f32 *, f32 *);
void func_80234900(f32 *, f32 *, f32 *);
s32 func_80238A10(void *, s32, s32, s32, s32);
s32 func_80238FDC(void);
void func_8023903C(s32);
void func_80239094(void);
s32 func_802391F0(void);
void func_80239430(void);
s32 * func_8023A840(void);
void func_8026C454(s32, f32, f32, f32);
s32 func_8026C51C(s32, f32, f32, f32);
s32 func_8026D7D8(s32, s32, s32);
u8 func_8026DC74(s32);
void func_8026DCAC(f32, f32, f32, void *, s32);
void func_8026E6E4(void *, f32 *, f32 *);
f32 func_8026E8B8(void);
f32 func_8026E938(void *);
void func_8029C8D0(f32 m[4][4], f32, f32, f32);
void func_8029CA80(f32 m[4][4], f32, f32, f32);
f32 func_8029CB40(f32);
void guMtxIdentF(f32 mf[4][4]);
f32 sqrtf(f32);

extern UnkStructA80 D_800A3F00[];
extern f32 D_800A7F00;
extern s32 D_800A7F04;
extern Rect40 *D_800A7F08[8];
extern void *D_800A7F28;
extern u8 D_8029FD40[];
extern f32 *D_802A5560;
extern f32 D_802A5568;
extern f32 D_802A556C;
extern f32 D_802A5570;
extern UnkStructA80 D_802A5578;
extern void *D_802A55F4;
extern UnkStructA80 D_802A55F8;
extern s32 *D_802A5674;
extern UnkStructA80 D_802A5678;
extern s32 *D_802A56F4;
extern s32 *D_802A56F8;
extern s32 D_802A56FC;
extern s32 D_802A5700;
extern f32 D_802A5780[3];
extern f32 D_802A5790[3];
extern f32 D_802A57A0;
extern f32 D_802A57A8;
extern f32 D_802A57B0[3];
extern f32 D_802A57BC;
extern f32 D_802A57C0[4];
extern s32 D_802A5800;
extern s32 D_802A5804;
extern f32 D_802A5808[3];
extern f32 D_802A5814;
extern s32 D_802A5818[];
extern s32 D_802A5938;

void func_8022DB00(void);
static void func_8022DB28(void);
void func_8022DBBC(s32 arg0);
static void func_8022DBF4(Rect40 **arg0, f32 arg1, f32 arg2, s32 *arg3, s32 arg4);
static void func_8022DD6C(void);
void func_8022DDB4(s32 arg0);
void func_8022DE00(void);
void func_8022DE6C(void);
f32 func_8022DF68(f32 *arg0, f32 *arg1);
static s32 func_8022DFBC(f32 *arg0, f32 *arg1);
static void func_8022E0A4();
static void func_8022E0AC(UnkStructA80 *arg0, f32 *arg1);
void func_8022E170(void);
static s32 func_8022E178(f32 *arg0, f32 *arg1);
static void func_8022E264();
static void func_8022E26C(UnkStructA80 *arg0, f32 *arg1);
void func_8022E328(void);
f32 func_8022E330(f32 *arg0, f32 *arg1);
void func_8022E364(f32 *arg0, f32 *arg1, f32 *arg2);
void func_8022E3D4(f32 m[4][4], f32 *v);
static s32 func_8022E4DC(f32 *arg0, f32 *arg1);
s32 func_8022E884(UnkStructA80 *arg0, UnkStructA80 *arg1);
static s32 func_8022F3F8(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3);
f32 *func_8022F4AC(f32 *arg0, s32 arg1, f32 *arg2);
f32 *func_8022F550(f32 *arg0, s32 arg1);
static s32 func_8022F5E4(f32 *arg0, u8 *arg1, u8 *arg2);
s32 func_8022F698(s32 arg0, f32 *arg1, f32 *arg2, f32 **arg3, s32 arg4);
s32 func_8022F77C(s32 arg0, s32 arg1, s32 arg2);
void func_8022F808(f32 *arg0, f32 *arg1);
static f32 *func_8022F844(s32 arg0, f32 *arg1, s32 arg2, f32 *arg3);
void func_8022F998(f32 *arg0, s32 arg1, f32 *arg2);
void func_8022FA10(f32 *arg0, s32 arg1, f32 *arg2);
void func_8022FA88(f32 *arg0, s32 arg1, f32 *arg2);
f32 func_8022FB00(u8 *arg0);
void func_8022FC0C(s32 arg0);
void func_8022FC18(void);
static void func_8022FC20(u8 *arg0, s32 *arg1);
static void func_8022FC50(u8 *arg0);
s32 func_8022FC90(u8 *arg0);
void func_8022FDE8(void);
void func_8022FE94(s32 arg0);
void func_8022FEA0(f32 arg0);
void func_8022FEAC(f32 *arg0, f32 *arg1);
void func_8022FF58(f32 *arg0, f32 *arg1, f32 *arg2);
static void func_8023017C(s32 arg0, u8 *arg1, f32 *arg2, s32 arg3);
void func_80230340(f32 *arg0, s32 arg1, u8 *arg2);
void func_802303C0(f32 *arg0, s32 arg1, u8 *arg2);
void func_80230440(f32 *arg0, s32 arg1, u8 *arg2);
static f32 *func_802304C0(s32 arg0, f32 *arg1, s32 arg2);
static void func_80230604(f32 *arg0, s32 arg1, f32 *arg2, s32 arg3);
void func_802306B0(f32 *arg0, s32 arg1, f32 *arg2);
void func_80230720(f32 *arg0, s32 arg1, f32 *arg2);
void func_80230790(f32 *arg0, s32 arg1, f32 *arg2);
void func_80230800(f32 *arg0, s32 arg1);
void func_8023085C(f32 *arg0, s32 arg1);
void func_802308B8(f32 *arg0, s32 arg1);
void func_80230914(u8 *arg0);
void func_80230AA0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
static s32 *func_80230B98(s32 arg0);
static void func_80230C08(s32 *arg0);
void *func_80230CB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4);
void func_80230E6C(s32 arg0, s32 arg1);
void *func_80230E9C(u8 *arg0);
void func_8023101C(s32 arg0, s32 arg1, s32 arg2, u8 *arg3);
void *func_80231048(s32 arg0, u8 *arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5);
void func_802310BC(s32 arg0, s32 arg1, u8 *arg2);
void *func_802310F4(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void *func_8023116C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void *func_802311E8(u8 *arg0);
void func_80231244(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80231274(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
static void func_802312AC(u8 *arg0);
void func_802313B0(u8 *arg0, s32 arg1);
void func_802313DC(u8 *arg0, s32 arg1);
void func_80231408(u8 *arg0, s32 arg1);
void func_80231434(UnkStructA80 *arg0);
void func_80231D60(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80231D88(u8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3);
static void func_802320A8(void);
void func_80232A34(u8 *arg0, s32 arg1);
void func_80232AA8(u8 *arg0);
void func_80232AC8(u8 *arg0, u8 *arg1);
void func_80232B04(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
void func_80232BA0(u8 *arg0, u8 *arg1);
s32 func_80232BD0(f32 *arg0, s32 arg1);
s32 func_80232C74(f32 *arg0, s32 arg1);
s32 func_80232D18(f32 *arg0, s32 arg1);
void func_80232DB4(f32 *arg0);
void func_80232E60(void);
void func_80232FA8(u8 *arg0);
void func_80232FF8(u8 *arg0, s32 *arg1);
void func_802334CC(void);
void func_8023357C(u8 *arg0);
s32 func_802335A0(s32 arg0);

static void func_8023363C(void) {
}

static void func_80233634(void) {
}

static void func_8023362C(void) {
}

static void func_80233624(void) {
}

s32 func_802335A0(s32 arg0) {
    s32 *p;
    s32 i;
    s32 found;

    if (arg0 == -1) {
        return 0;
    }
    p = D_802A5818;
    found = 0;
    for (i = 0; i < D_802A5938 && found == 0; i++, p++) {
        if (arg0 == *p) {
            found = 1;
        }
    }
    if (found != 0) {
        return 0;
    }
    D_802A5818[D_802A5938] = arg0;
    D_802A5938++;
    return 1;
}

void func_8023357C(u8 *arg0) {
    u8 *var_a0;

    var_a0 = arg0;
    if (var_a0 != NULL) {
        do {
            M2C_FIELD(var_a0, s32 *, 0x10) = 0;
            var_a0 = M2C_FIELD(var_a0, void **, 0x7C);
        } while (var_a0 != NULL);
    }
}

void func_802334CC(void) {
    s32 sp2C;

    while (1) {
        sp2C = D_802A5800;
        func_80232FF8(((UnkStructA80 *) &D_802A5578)->unk7C, &sp2C);
        func_80232FF8(((UnkStructA80 *) &D_802A5678)->unk7C, &sp2C);
        func_80232FA8(((UnkStructA80 *) &D_802A5578)->unk7C);
        func_80232FA8(((UnkStructA80 *) &D_802A5678)->unk7C);
        D_802A5800++;
        func_80239094();
    }
}

void func_80232FF8(u8 *arg0, s32 *arg1) {
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp6C;
    f32 sp60[3];
    f32 sp54[3];
    f32 temp_fv0;
    s32 temp_t3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_t4;
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v0_10;
    u8 *temp_v0_11;
    u8 *temp_v0_12;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_7;
    u8 *temp_v0_8;
    u8 *temp_v0_9;
    u8 *var_s0;

    var_s0 = arg0;
    if ((s32) arg0 != (s32) NULL) {
        do {
            if (M2C_FIELD(var_s0, s32 *, 8) & 0x01000000) {
                temp_v0 = M2C_FIELD(var_s0, void **, 0x40);
                M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xC) & ~1);
                temp_v1 = M2C_FIELD(var_s0, s32 *, 8);
                if (temp_v1 & 0x40000) {
                    temp_t3 = temp_v1 ^ 0x40000000;
                    var_t4 = temp_v1 & 0x40000000;
                    if (*arg1 == 0) {
                        M2C_FIELD(var_s0, s32 *, 8) = temp_t3;
                        var_t4 = temp_t3 & 0x40000000;
                    }
                    if (var_t4 != 0) {
                        temp_v0_2 = M2C_FIELD(var_s0, void **, 0x40);
                        M2C_FIELD(temp_v0_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 0xC) & ~1);
                    } else {
                        temp_v0_3 = M2C_FIELD(var_s0, void **, 0x40);
                        M2C_FIELD(temp_v0_3, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_3, s32 *, 0xC) | 1);
                    }
                }
                if ((D_802A5804 != 0) && (M2C_FIELD(var_s0, s32 *, 8) & 0x01000000) && (M2C_FIELD(var_s0, s32 *, 8) & 0x02000000)) {
                    switch (D_802A5804) {           /* switch 1; irregular */
                    case 1:                         /* switch 1 */
                        temp_v0_4 = func_80234768();
                        switch (temp_v0_4) {        /* switch 2; irregular */
                        case 0:                     /* switch 2 */
                            func_802348B4(&sp78, &sp7C, &sp80);
                            func_80234900(&sp84, &sp88, &sp8C);
                            break;
                        case 1:                     /* switch 2 */
                            func_80234900(&sp78, &sp7C, &sp80);
                            func_802348B4(&sp84, &sp88, &sp8C);
                            break;
                        }
                        func_8022FF58(&sp78, &sp84, &sp6C);
                        sp54[0] = M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x10);
                        sp54[1] = M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x14);
                        sp54[2] = M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x18);
                        func_8022FF58(&sp84, sp54, sp60);
                        temp_fv0 = (f32) ((f64) sp74 * 0.7);
                        sp74 = temp_fv0;
                        if (temp_fv0 <= sp60[2]) {
                            temp_v0_5 = M2C_FIELD(var_s0, void **, 0x40);
                            M2C_FIELD(temp_v0_5, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_5, s32 *, 0xC) | 1);
                            M2C_FIELD(var_s0, s32 *, 8) = (s32) (M2C_FIELD(var_s0, s32 *, 8) & 0xDFFFFFFF);
                        } else {
                            M2C_FIELD(var_s0, s32 *, 8) = (s32) (M2C_FIELD(var_s0, s32 *, 8) | 0x20000000);
                        }
                        break;
                    case 2:                         /* switch 1 */
                        sp84 = D_802A5808[0];
                        sp88 = D_802A5808[1];
                        sp8C = D_802A5808[2];
                        sp74 = D_802A5814;
                        sp54[0] = M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x10);
                        sp54[1] = M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x14);
                        sp54[2] = M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x18);
                        func_8022FF58(&sp84, sp54, sp60);
                        if (sp74 <= sp60[2]) {
                            temp_v0_6 = M2C_FIELD(var_s0, void **, 0x40);
                            M2C_FIELD(temp_v0_6, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_6, s32 *, 0xC) | 1);
                            M2C_FIELD(var_s0, s32 *, 8) = (s32) (M2C_FIELD(var_s0, s32 *, 8) & 0xDFFFFFFF);
                        } else {
                            M2C_FIELD(var_s0, s32 *, 8) = (s32) (M2C_FIELD(var_s0, s32 *, 8) | 0x20000000);
                        }
                        break;
                    }
                } else if (M2C_FIELD(var_s0, s32 *, 8) & 0x02000000) {
                    M2C_FIELD(var_s0, s32 *, 8) = (s32) (M2C_FIELD(var_s0, s32 *, 8) | 0x20000000);
                }
            } else {
                temp_v0_7 = M2C_FIELD(var_s0, void **, 0x40);
                M2C_FIELD(temp_v0_7, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_7, s32 *, 0xC) | 1);
            }
            if (M2C_FIELD(var_s0, s32 *, 0x44) != 0) {
                func_80231434((UnkStructA80 *) var_s0);
            }
            if (M2C_FIELD(var_s0, s32 *, 8) & 0x10000000) {
                temp_v0_8 = M2C_FIELD(var_s0, void **, 0x40);
                M2C_FIELD(temp_v0_8, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_8, s32 *, 0xC) | 0x2000);
            } else {
                temp_v0_9 = M2C_FIELD(var_s0, void **, 0x40);
                M2C_FIELD(temp_v0_9, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_9, s32 *, 0xC) & ~0x2000);
            }
            if (M2C_FIELD(var_s0, s32 *, 8) & 0x80000) {
                temp_v0_10 = M2C_FIELD(var_s0, void **, 0x40);
                M2C_FIELD(temp_v0_10, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_10, s32 *, 0xC) | 0x80);
            } else {
                temp_v0_11 = M2C_FIELD(var_s0, void **, 0x40);
                M2C_FIELD(temp_v0_11, s32 *, 0xC) = (s32) (M2C_FIELD(temp_v0_11, s32 *, 0xC) & ~0x80);
            }
            if (M2C_FIELD(var_s0, s32 *, 8) & 0xF) {
                temp_v0_12 = M2C_FIELD(var_s0, void **, 0x40);
                M2C_FIELD(var_s0, f32 *, 0x58) = (f32) M2C_FIELD(temp_v0_12, f32 *, 0x10);
                M2C_FIELD(var_s0, f32 *, 0x5C) = (f32) M2C_FIELD(temp_v0_12, f32 *, 0x14);
                M2C_FIELD(var_s0, f32 *, 0x60) = (f32) M2C_FIELD(temp_v0_12, f32 *, 0x18);
                var_v0 = 0;
                if (M2C_FIELD(M2C_FIELD(var_s0, void **, 0x40), f32 *, 0x14) <= func_8026E8B8()) {
                    var_v0 = 1;
                }
                if (var_v0 != 0) {
                    M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x40000000);
                } else {
                    M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) & 0xBFFFFFFF);
                }
            }
            var_s0 = M2C_FIELD(var_s0, void **, 0x7C);
        } while (var_s0 != NULL);
    }
}

void func_80232FA8(u8 *arg0) {
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t8;
    u8 *var_a0;

    var_a0 = arg0;
    if (var_a0 != NULL) {
        do {
            temp_t6 = M2C_FIELD(var_a0, s32 *, 0x14);
            temp_t7 = M2C_FIELD(var_a0, s32 *, 0x1C);
            temp_t8 = M2C_FIELD(var_a0, s32 *, 0x24);
            M2C_FIELD(var_a0, s32 *, 0x14) = 0;
            M2C_FIELD(var_a0, s32 *, 0x1C) = 0x7FFFFFFF;
            M2C_FIELD(var_a0, s32 *, 0x24) = 0;
            M2C_FIELD(var_a0, s32 *, 0x10) = temp_t6;
            M2C_FIELD(var_a0, s32 *, 0x18) = temp_t7;
            M2C_FIELD(var_a0, s32 *, 0x20) = temp_t8;
            var_a0 = M2C_FIELD(var_a0, void **, 0x7C);
        } while (var_a0 != NULL);
    }
}

void func_80232E60(void) {
    UnkStructA80 *o;
    s32 i;

    D_802A5808[0] = 0.0f;
    D_802A5808[1] = 0.0f;
    D_802A5808[2] = 0.0f;
    D_802A5814 = 0.0f;
    D_802A5804 = 1;
    D_800A7F00 = 0.0f;
    D_800A7F04 = 0x7F;
    D_802A5700 = 0x10;
    D_802A56FC = 0;
    func_80230C08((s32 *) &D_802A5578);
    D_802A5578.unk0 = 0x81;
    func_80230C08((s32 *) &D_802A55F8);
    D_802A55F8.unk0 = 0x82;
    func_80230C08((s32 *) &D_802A5678);
    D_802A5678.unk0 = 0x83;
    for (i = 0, o = D_800A3F00; i < 0x80; i++, o++) {
        o->unk0 = i;
        func_80230C08((s32 *) o);
    }
    func_8022FC20((u8 *) D_800A3F00, (s32 *) &D_802A55F8);
    for (i = 0, o = D_800A3F00; i < 0x7E; i++, o++) {
        func_8022FC20((u8 *) (o + 1), (s32 *) o);
    }
    for (i = 0; i < 0x48; i++) {
        D_802A5818[i] = -1;
    }
    D_802A5938 = 0;
    func_8022DB00();
}

void func_80232DB4(f32 *arg0) {
    UnkStructA80 *a = (UnkStructA80 *) arg0;
    UnkStructA80 *o;
    s32 m;

    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        m = o->unkC ^ o->unk14;
        if (m != 0 && (a->unk8 & m) && a->unk4 < o->unk1C && a != o) {
            func_8022E884(arg0, (f32 *) o);
        }
    }
}

s32 func_80232D18(f32 *arg0, s32 arg1) {
    UnkStructA80 *o;

    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if (func_8022F3F8(arg0, (f32 *) o, 0, arg1) != 0 && func_8022E884(arg0, (f32 *) o) != 0) {
            return o->unk8 | ((UnkStructA80 *) arg0)->unk14;
        }
    }
    return 0;
}

s32 func_80232C74(f32 *arg0, s32 arg1) {
    UnkStructA80 *o;

    arg1 &= 0x3FFFF;
    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if (func_8022F3F8(arg0, (f32 *) o, 1, arg1) != 0 && func_8022E884(arg0, (f32 *) o) != 0) {
            return o->unk8 | ((UnkStructA80 *) arg0)->unk14;
        }
    }
    return 0;
}

s32 func_80232BD0(f32 *arg0, s32 arg1) {
    UnkStructA80 *o;

    arg1 &= 0x3FFFF;
    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if (func_8022F3F8(arg0, (f32 *) o, 2, arg1) != 0 && func_8022E884(arg0, (f32 *) o) != 0) {
            return o->unk8 | ((UnkStructA80 *) arg0)->unk14;
        }
    }
    return 0;
}

void func_80232BA0(u8 *arg0, u8 *arg1) {
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), f32 *, 0x10) = (f32) M2C_FIELD(arg0, f32 *, 0);
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), f32 *, 0x14) = (f32) M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), f32 *, 0x18) = (f32) M2C_FIELD(arg0, f32 *, 8);
}

void func_80232B04(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0;

    func_80238FDC();
    temp_v0 = M2C_FIELD(arg1, void **, 0x44);
    M2C_FIELD(arg1, s32 *, 0x3C) = arg2;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x48) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x48) - 1);
        M2C_FIELD(arg1, void **, 0x44) = NULL;
    }
    M2C_FIELD(arg1, void **, 0x44) = arg0;
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + 1);
    func_80232A34(arg1, M2C_FIELD(arg0, s32 *, 4) + 1);
    func_80238A10(func_802320A8, (s32) arg1, 0, 0, arg3);
}

void func_80232AC8(u8 *arg0, u8 *arg1) {
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg1, void **, 0x44);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x48) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x48) - 1);
        M2C_FIELD(arg1, void **, 0x44) = NULL;
    }
    M2C_FIELD(arg1, void **, 0x44) = arg0;
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + 1);
}

void func_80232AA8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x44);
    M2C_FIELD(temp_v0, s32 *, 0x48) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x48) - 1);
    M2C_FIELD(arg0, void **, 0x44) = NULL;
}

void func_80232A34(u8 *arg0, s32 arg1) {
    s32 sv_a3;
    void *sv_a2;
    void *sv_a0;
    s32 *temp_v0;
    s32 *var_a1;

    sv_a0 = arg0;
    sv_a2 = arg0;
    sv_a3 = arg1;
    func_8022FC50(arg0);
    if (sv_a3 < 0xD0) {
        sv_a0 = (void *) sv_a3;
        temp_v0 = func_80230B98(sv_a3);
        if (temp_v0 != NULL) {
            var_a1 = M2C_FIELD(temp_v0, s32 **, 0x78);
        } else {
            var_a1 = D_802A56F8;
        }
        func_8022FC20(sv_a2, var_a1);
    } else {
        func_8022FC20(sv_a2, &D_802A5678);
    }
    M2C_FIELD(sv_a2, s32 *, 4) = sv_a3;
}

static void func_802320A8() {
    f32 *sv_a1;
    s32 sv_a2;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp128[3];
    f32 sp11C;
    f32 sp110[3];
    f32 sp104[3];
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spC8[3];
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB4;
    f32 spB0;
    f32 spA4;
    f32 spA0;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp74;
    f32 *sp68;
    f32 *temp_a1;
    f32 *temp_s5;
    f32 *temp_v0;
    f32 *temp_v1;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv0_7;
    f32 temp_fv0_8;
    f32 temp_fv0_9;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_t0;
    s32 temp_t3;
    s32 var_t7;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v1_2;

    temp_v0 = func_802391F0();
    temp_v1 = M2C_FIELD(temp_v0, f32 **, 0x44);
    temp_s5 = M2C_FIELD(temp_v1, f32 **, 0x44);
    temp_a1 = (u8 *)temp_v0 + 0x58;
    sv_a1 = temp_a1;
    func_8022F808(temp_v0, temp_a1);
    sv_a1 = &spBC;
    func_8022F808(temp_v0, &spBC);
    spDC = 0.0f;
    spD8 = 0.0f;
    spD4 = 0.0f;
    temp_a0 = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), s32 *, 0);
    if (temp_a0 != 0) {
        var_fs3 = sp7C;
        sp68 = (u8 *)temp_v0 + 0x58;
        var_t7 = temp_a0 & 0x80000000;
loop_2:
        if (var_t7 != 0) {
            do {
                func_80239094();
            } while (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), s32 *, 0) & 0x80000000);
        }
        temp_fs5 = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 8) * 16.333334f;
        sv_a1 = sp110;
        func_8022F808(temp_v1, sp110);
        if ((temp_s5 != NULL) && (M2C_FIELD(temp_s5, s32 *, 0x3C) != 0)) {
            func_8022F808(temp_s5, &sp11C);
            func_8022FF58(&sp11C, sp110, &spE4);
            temp_fv0 = spE8 - 90.0f;
            sp104[0] = spE4;
            if (temp_fv0 >= 360.0f) {
                sp104[1] = temp_fv0 - 360.0f;
            } else {
                if (spE8 < 90.0f) {
                    var_fs3 = temp_fv0 + 360.0f;
                } else {
                    var_fs3 = temp_fv0;
                }
                sp104[1] = var_fs3;
            }
            sp104[2] = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 4);
            func_8022FEAC(sp104, &spBC);
            spBC += sp110[0];
            spC0 += sp110[1];
            spC4 += sp110[2];
        } else {
            spE4 = 0.0f;
            spE8 = 0.0f;
            spEC = 0.0f;
            spBC = sp110[0];
            spC4 = sp110[2];
            spC0 = sp110[1] - M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 4);
        }
        func_8022FF58(sp110, &spBC, &spB0);
        spB4 = spD8 - spB4;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 0x3C);
        temp_t3 = M2C_FIELD(temp_v1_2, s32 *, 0) & 0xFFFF;
        switch (temp_t3) {                          /* switch 1; irregular */
        case 1:                                     /* switch 1 */
            temp_fs2 = func_80234434(spB4) * (spBC - M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10)) * M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 0xC);
            temp_fs1 = func_80234434(spB4) * (spC0 - M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14)) * M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 0xC);
            temp_fs0 = func_80234434(spB4) * (spC4 - M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18)) * M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 0xC);
            spA0 = func_80234408(spB4) * ((M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) - M2C_FIELD(temp_v0, f32 *, 0x58)) * M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 0x10));
            spA4 = func_80234408(spB4) * ((M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) - M2C_FIELD(temp_v0, f32 *, 0x5C)) * M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 0x10));
            temp_fv0_2 = func_80234408(spB4);
            temp_v0_2 = M2C_FIELD(temp_v0, void **, 0x40);
            sp128[0] = M2C_FIELD(temp_v0_2, f32 *, 0x10) + spA0 + temp_fs2;
            sp128[1] = (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) + spA4 + temp_fs1) - temp_fs5;
            sp128[2] = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) + (temp_fv0_2 * ((M2C_FIELD(temp_v0_2, f32 *, 0x18) - M2C_FIELD(temp_v0, f32 *, 0x60)) * M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 0x10))) + temp_fs0;
block_20:
            sv_a2 = 0 /* FIXME unset $a2 */;
            func_8022F808(temp_v0, sp68);
            func_8022FF58(sp110, sp128, &spD4);
            temp_fv0_3 = spD8 - 90.0f;
            spF8 = spD4;
            if (temp_fv0_3 >= 360.0f) {
                spFC = temp_fv0_3 - 360.0f;
            } else {
                if (spD8 < 90.0f) {
                    var_fs3 = temp_fv0_3 + 360.0f;
                } else {
                    var_fs3 = temp_fv0_3;
                }
                spFC = var_fs3;
            }
            sp100 = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), f32 *, 4);
            func_8022FEAC(&spF8, spC8);
            if (!(M2C_BITWISE(s32, temp_v0[2]) & 0xF00000)) {
                M2C_FIELD(temp_v0, f32 *, 0x4C) = spF8;
                temp_fv0_4 = spFC + 90.0f;
                if (temp_fv0_4 >= 360.0f) {
                    M2C_FIELD(temp_v0, f32 *, 0x50) = (f32) (temp_fv0_4 - 360.0f);
                } else {
                    if (temp_fv0_4 < 0.0f) {
                        var_fs3 = temp_fv0_4 + 360.0f;
                    } else {
                        var_fs3 = temp_fv0_4;
                    }
                    M2C_FIELD(temp_v0, f32 *, 0x50) = var_fs3;
                }
                M2C_FIELD(temp_v0, f32 *, 0x54) = sp100;
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) = (f32) (sp110[0] + spC8[0]);
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = (f32) (sp110[1] + spC8[1]);
                if (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), s32 *, 0) & 0x100000) {
                    temp_fv0_5 = func_8026E938(M2C_FIELD(temp_v0, void **, 0x40));
                    if ((temp_fv0_5 != 20000.0f) && ((sp110[1] + spC8[1]) <= temp_fv0_5)) {
                        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = temp_fv0_5;
                    }
                }
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) = (f32) (sp110[2] + spC8[2]);
            }
            temp_t0 = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), s32 *, 0) & 0xF0000;
            switch (temp_t0) {                      /* switch 2; irregular */
            default:                                /* switch 2 */
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v0, f32 **, 0x44), void **, 0x40), f32 *, 0x20);
                break;
            case 0x10000:                           /* switch 2 */
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = spD4;
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x1C) = (f32) ((spD8 * -1.0f) + 90.0f);
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x24) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v0, f32 **, 0x44), void **, 0x40), f32 *, 0x24);
                break;
            case 0x20000:                           /* switch 2 */
                sp80 = spD4;
                sp84 = spD8;
                sp88 = spDC;
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v0, f32 **, 0x44), void **, 0x40), f32 *, 0x20);
                temp_fv0_6 = M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v0, f32 **, 0x44), void **, 0x40), f32 *, 0x20);
                if (temp_fv0_6 >= 0.0f) {
                    if (temp_fv0_6 <= 180.0f) {
                        sp74 = temp_fv0_6;
                    } else {
                        goto block_47;
                    }
                } else {
block_47:
                    sp74 = (360.0f - temp_fv0_6) * -1.0f;
                }
                if (sp80 >= 0.0f) {
                    if (sp80 <= 180.0f) {
                        var_fs3 = sp80;
                    } else {
                        goto block_52;
                    }
                } else {
block_52:
                    var_fs3 = (360.0f - sp80) * -1.0f;
                }
                temp_fv1 = sp74 - var_fs3;
                if (temp_fv1 >= 360.0f) {
                    sp80 = temp_fv1 - 360.0f;
                } else {
                    if (temp_fv1 < 0.0f) {
                        var_fs3 = temp_fv1 + 360.0f;
                    } else {
                        var_fs3 = temp_fv1;
                    }
                    sp80 = var_fs3;
                }
                temp_fv0_7 = sp84 - 90.0f;
                if (temp_fv0_7 >= 360.0f) {
                    sp84 = temp_fv0_7 - 360.0f;
                } else {
                    if (sp84 < 90.0f) {
                        var_fs3 = temp_fv0_7 + 360.0f;
                    } else {
                        var_fs3 = temp_fv0_7;
                    }
                    sp84 = var_fs3;
                }
                func_8022FEAC(&sp80, &sp134);
                sp134 = sp110[0];
                sp138 += sp110[1];
                sp13C += sp110[2];
                func_8022FF58(sp110, &sp134, &sp80);
                if (func_8023369C(sp80, 0.0f, 90.0f) != 0) {
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x1C) = (f32) (sp84 * -1.0f);
                } else {
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x1C) = sp84;
                }
                break;
            case 0x30000:                           /* switch 2 */
                sv_a2 = 0 /* FIXME unset $a2 */;
                func_8022F808(temp_v0, &sp134);
                func_8022FF58(&sp134, sp110, &sp80);
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = sp80;
                temp_fv0_8 = sp84 - 180.0f;
                if (temp_fv0_8 >= 360.0f) {
                    var_fs3 = temp_fv0_8 - 360.0f;
                } else {
                    if (sp84 < 180.0f) {
                        sp74 = temp_fv0_8 + 360.0f;
                    } else {
                        sp74 = temp_fv0_8;
                    }
                    var_fs3 = sp74;
                }
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x1C) = (f32) (var_fs3 * -1.0f);
                break;
            }
            func_80239094();
            temp_a0_2 = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x3C), s32 *, 0);
            var_t7 = temp_a0_2 & 0x80000000;
            if (temp_a0_2 == 0) {
                sp7C = var_fs3;
                /* Duplicate return node #77. Try simplifying control flow for better match */
                func_80239430();
                return;
            }
            goto loop_2;
        case 2:                                     /* switch 1 */
            temp_v0_3 = M2C_FIELD(temp_v0, void **, 0x40);
            temp_fv0_9 = M2C_FIELD(temp_v1_2, f32 *, 0xC);
            temp_fv1_2 = M2C_FIELD(temp_v0_3, f32 *, 0x10);
            sp128[0] = temp_fv1_2 + ((spBC - temp_fv1_2) * temp_fv0_9);
            sp128[1] = (M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) + ((spC0 - M2C_FIELD(temp_v0_3, f32 *, 0x14)) * temp_fv0_9)) - temp_fs5;
            sp128[2] = M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) + ((spC4 - M2C_FIELD(temp_v0_3, f32 *, 0x18)) * temp_fv0_9);
            goto block_20;
        }
    } else {
        func_80239430();
    }
}

void func_80231D88(u8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3) {
    f32 sp24;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 var_ft0;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_fa1 = M2C_FIELD(arg1, f32 *, 0) - M2C_FIELD(arg0, f32 *, 0);
    temp_fa0 = (M2C_FIELD(arg1, f32 *, 4) - M2C_FIELD(arg0, f32 *, 4)) * -1.0f;
    sp24 = M2C_FIELD(arg1, f32 *, 8) - M2C_FIELD(arg0, f32 *, 8);
    if (func_802336E4(temp_fa0) != 0) {
        temp_v0 = func_802337EC(temp_fa1);
        switch (temp_v0) {                          /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            *arg2 = 0.0f;
            break;
        case 1:                                     /* switch 1 */
            *arg2 = 90.0f;
            break;
        case -1:                                    /* switch 1 */
            *arg2 = 270.0f;
            break;
        }
        temp_v0_2 = func_802337EC(sp24);
        switch (temp_v0_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            *arg3 = 0.0f;
            break;
        case 1:                                     /* switch 2 */
            var_ft0 = 90.0f;
            goto block_20;
        case -1:                                    /* switch 2 */
            *arg3 = 270.0f;
            break;
        }
    } else {
        *arg2 = (f32) ((f64) func_8029CB40(temp_fa1 / temp_fa0) * 57.29577951308232);
        var_ft0 = (f32) ((f64) func_8029CB40(sp24 / temp_fa0) * 57.29577951308232);
block_20:
        *arg3 = var_ft0;
    }
    arg2 = arg2;
    arg3 = arg3;
    if (func_802337EC(temp_fa0) == -1) {
        temp_fv0 = *arg2 + 180.0f;
        if (temp_fv0 >= 360.0f) {
            *arg2 = temp_fv0 - 360.0f;
        } else {
            if (temp_fv0 < 0.0f) {
                var_fv1 = temp_fv0 + 360.0f;
            } else {
                var_fv1 = temp_fv0;
            }
            *arg2 = var_fv1;
        }
        temp_fv0_2 = *arg3 + 180.0f;
        if (temp_fv0_2 >= 360.0f) {
            *arg3 = temp_fv0_2 - 360.0f;
            return;
        }
        if (temp_fv0_2 < 0.0f) {
            var_fv1_2 = temp_fv0_2 + 360.0f;
        } else {
            var_fv1_2 = temp_fv0_2;
        }
        goto block_45;
    }
    temp_fv0_3 = *arg2;
    if (temp_fv0_3 >= 360.0f) {
        *arg2 = temp_fv0_3 - 360.0f;
    } else {
        if (temp_fv0_3 < 0.0f) {
            var_fv1_3 = temp_fv0_3 + 360.0f;
        } else {
            var_fv1_3 = temp_fv0_3;
        }
        *arg2 = var_fv1_3;
    }
    temp_fv0_4 = *arg3;
    if (temp_fv0_4 >= 360.0f) {
        *arg3 = temp_fv0_4 - 360.0f;
        return;
    }
    if (temp_fv0_4 < 0.0f) {
        var_fv1_2 = temp_fv0_4 + 360.0f;
    } else {
        var_fv1_2 = temp_fv0_4;
    }
block_45:
    *arg3 = var_fv1_2;
}

void func_80231D60(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_802A5808[0] = arg0;
    D_802A5808[1] = arg1;
    D_802A5808[2] = arg2;
    D_802A5814 = arg3;
}

void func_80231434(UnkStructA80 *arg0) {
    f32 v[3];
    f32 rot[3];
    f32 ang[3];
    f32 m[4][4];
    f32 sp3C[2];
    f32 sp38;
    f32 x;
    f32 w;

    switch (arg0->unk8 & 0xF00000) {
    case 0x200000:
        arg0->unk40->pos[0] = arg0->unk4C[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = arg0->unk4C[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = arg0->unk4C[2] + arg0->unk44->unk40->pos[2];
        break;
    case 0x300000:
        x = arg0->unk4C[0];
        if (x >= 360.0f) {
            arg0->unk4C[0] = x - 360.0f;
        } else {
            if (x < 0.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            arg0->unk4C[0] = w;
        }
        x = arg0->unk4C[1] - 90.0f;
        if (x >= 360.0f) {
            arg0->unk4C[1] = x - 360.0f;
        } else {
            if (arg0->unk4C[1] < 90.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            arg0->unk4C[1] = w;
        }
        func_8022FEAC(arg0->unk4C, v);
        arg0->unk40->pos[0] = v[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = v[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = v[2] + arg0->unk44->unk40->pos[2];
        x = arg0->unk4C[1] + 90.0f;
        if (x >= 360.0f) {
            arg0->unk4C[1] = x - 360.0f;
        } else {
            if (x < 0.0f) {
                w = x + 360.0f;
            } else {
                w = x;
            }
            arg0->unk4C[1] = w;
        }
        break;
    case 0x400000:
        arg0->unk40->scale[0] = arg0->unk44->unk40->scale[0];
        arg0->unk40->scale[1] = arg0->unk44->unk40->scale[1];
        arg0->unk40->scale[2] = arg0->unk44->unk40->scale[2];
    case 0x600000:
        arg0->unk40->rot[1] = arg0->unk44->unk40->rot[1];
        arg0->unk40->rot[0] = arg0->unk44->unk40->rot[0];
        arg0->unk40->rot[2] = arg0->unk44->unk40->rot[2];
    case 0x700000:
        guMtxIdentF(m);
        v[2] = 0.0f; v[1] = 0.0f; v[0] = 0.0f;
        func_8029C8D0(m, arg0->unk44->unk40->rot[0], arg0->unk44->unk40->rot[1], arg0->unk44->unk40->rot[2]);
        func_8029CA80(m, arg0->unk4C[0], arg0->unk4C[1], arg0->unk4C[2]);
        func_8022E3D4(m, v);
        arg0->unk40->pos[0] = v[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = v[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = v[2] + arg0->unk44->unk40->pos[2];
        break;
    case 0x500000:
        arg0->unk40->scale[0] = arg0->unk44->unk40->scale[0];
        arg0->unk40->scale[1] = arg0->unk44->unk40->scale[1];
        arg0->unk40->scale[2] = arg0->unk44->unk40->scale[2];
        arg0->unk40->rot[0] = arg0->unk44->unk40->rot[0];
        arg0->unk40->rot[1] = arg0->unk44->unk40->rot[1];
        arg0->unk40->rot[2] = arg0->unk44->unk40->rot[2];
        func_8022FEAC(arg0->unk4C, rot);
        guMtxIdentF(m);
        v[2] = 0.0f; v[1] = 0.0f; v[0] = 0.0f;
        func_8029C8D0(m, arg0->unk44->unk40->rot[0], arg0->unk44->unk40->rot[1], arg0->unk44->unk40->rot[2]);
        func_8029CA80(m, rot[0], rot[1], rot[2]);
        func_8022E3D4(m, v);
        arg0->unk40->pos[0] = v[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = v[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = v[2] + arg0->unk44->unk40->pos[2];
        break;
    case 0x800000:
    case 0x900000:
        arg0->unk40->scale[0] = arg0->unk44->unk40->scale[0];
        arg0->unk40->scale[1] = arg0->unk44->unk40->scale[1];
        arg0->unk40->scale[2] = arg0->unk44->unk40->scale[2];
        func_8022FEAC(arg0->unk4C, rot);
        guMtxIdentF(m);
        v[2] = 0.0f; v[1] = 0.0f; v[0] = 0.0f;
        func_8029C8D0(m, arg0->unk44->unk40->rot[0], arg0->unk44->unk40->rot[1], arg0->unk44->unk40->rot[2]);
        func_8029CA80(m, rot[0], rot[1], rot[2]);
        func_8022E3D4(m, v);
        arg0->unk40->pos[0] = v[0] + arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[1] = v[1] + arg0->unk44->unk40->pos[1];
        arg0->unk40->pos[2] = v[2] + arg0->unk44->unk40->pos[2];
        D_802A5780[0] = arg0->unk44->unk40->pos[0];
        D_802A5780[1] = arg0->unk44->unk40->pos[1];
        D_802A5780[2] = arg0->unk44->unk40->pos[2];
        D_802A5790[0] = arg0->unk40->pos[0];
        D_802A5790[1] = arg0->unk40->pos[1];
        D_802A5790[2] = arg0->unk40->pos[2];
        if ((arg0->unk8 & 0xF00000) != 0x900000) {
            func_8022FF58(D_802A5780, D_802A5790, ang);
        } else {
            func_8022FF58(D_802A5790, D_802A5780, ang);
        }
        arg0->unk40->rot[0] = ang[1] * -1.0f + 90.0f;
        arg0->unk40->rot[1] = ang[0];
        break;
    case 0x100000:
        if (!(arg0->unk44->unk8 & 0x01000000) || ((arg0->unk44->unk8 & 0x02000000) && !(arg0->unk44->unk8 & 0x20000000))) {
            arg0->unk40->unkC |= 1;
            break;
        }
        arg0->unk40->pos[0] = arg0->unk44->unk40->pos[0];
        arg0->unk40->pos[2] = arg0->unk44->unk40->pos[2];
        arg0->unk40->pos[1] = func_8026E938(arg0->unk44->unk40);
        func_8026E6E4(arg0->unk44->unk40, sp3C, &sp38);
        arg0->unk40->rot[0] = sp3C[0];
        arg0->unk40->rot[1] = sp38;
        if (arg0->unk40->pos[1] <= arg0->unk44->unk40->pos[1]) {
            x = arg0->unk44->unk40->pos[1] - arg0->unk40->pos[1];
            x -= 2000.0f;
            x *= -1.0f;
            x /= 2000.0f;
            if (x <= 0.3f) {
                x = 0.3f;
            }
            arg0->unk40->scale[0] = x;
            arg0->unk40->scale[2] = x;
            arg0->unk40->scale[0] *= arg0->unk4C[0];
            arg0->unk40->scale[1] *= arg0->unk4C[1];
            arg0->unk40->scale[2] *= arg0->unk4C[2];
            arg0->unk40->pos[1] += D_800A7F00;
            arg0->unk40->unk36 = D_800A7F04;
        } else {
            arg0->unk40->scale[0] = 1.0f;
            arg0->unk40->scale[2] = 1.0f;
            arg0->unk40->pos[1] = 20000.0f;
        }
        break;
    }
}

void func_80231408(u8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) | arg1);
    func_802312AC(arg0);
}

void func_802313DC(u8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & ~arg1);
    func_802312AC(arg0);
}

void func_802313B0(u8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) ^ arg1);
    func_802312AC(arg0);
}

static void func_802312AC(u8 *arg0) {
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;

    if (M2C_FIELD(arg0, s32 *, 8) & 0x04000000) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(temp_a0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xC) & ~0x40);
    } else {
        temp_a0_2 = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(temp_a0_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 0xC) | 0x40);
    }
    if (M2C_FIELD(arg0, s32 *, 8) & 0x08000000) {
        temp_a0_3 = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(temp_a0_3, s32 *, 0xC) = (s32) (M2C_FIELD(temp_a0_3, s32 *, 0xC) & ~0x20);
    } else {
        temp_a0_4 = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(temp_a0_4, s32 *, 0xC) = (s32) (M2C_FIELD(temp_a0_4, s32 *, 0xC) | 0x20);
    }
    if (M2C_FIELD(arg0, s32 *, 8) & 0x80000) {
        temp_a0_5 = M2C_FIELD(arg0, void **, 0x40);
        if (M2C_FIELD(temp_a0_5, s32 *, 8) != 0x60) {
            func_8022946C(temp_a0_5, 0x60);
        }
    } else {
        temp_a0_6 = M2C_FIELD(arg0, void **, 0x40);
        if (M2C_FIELD(temp_a0_6, s32 *, 8) != 0x40) {
            func_8022946C(temp_a0_6, 0x40);
        }
    }
}

void func_80231274(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80230CB4(arg0, -1, arg1, arg2, (void *) arg3);
}

void func_80231244(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80230CB4(arg0, arg1, 0, arg2, (void *) arg3);
}

void *func_802311E8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(0x22, -1, 0x01180000, 0xD0, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), s16 *, 0x36) = 0x7F;
        M2C_FIELD(temp_v0, f32 *, 0x4C) = 1.0f;
        M2C_FIELD(temp_v0, f32 *, 0x50) = 1.0f;
        M2C_FIELD(temp_v0, f32 *, 0x54) = 1.0f;
    }
    return temp_v0;
}

void *func_8023116C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(arg0, -1, arg1, D_802A5700, NULL);
    if (temp_v0 != NULL) {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) = arg2;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = arg3;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) = arg4;
        M2C_FIELD(temp_v0, f32 *, 0x58) = arg2;
        M2C_FIELD(temp_v0, f32 *, 0x5C) = arg3;
        M2C_FIELD(temp_v0, f32 *, 0x60) = arg4;
    }
    return temp_v0;
}

void *func_802310F4(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(arg0, -1, 0, arg1, NULL);
    if (temp_v0 != NULL) {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) = arg2;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = arg3;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) = arg4;
        M2C_FIELD(temp_v0, f32 *, 0x58) = arg2;
        M2C_FIELD(temp_v0, f32 *, 0x5C) = arg3;
        M2C_FIELD(temp_v0, f32 *, 0x60) = arg4;
    }
    return temp_v0;
}

void func_802310BC(s32 arg0, s32 arg1, u8 *arg2) {
    func_80230CB4(arg0, -1, arg1, M2C_FIELD(arg2, s32 *, 4) + 1, arg2);
}

void *func_80231048(s32 arg0, u8 *arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(arg0, -1, arg2, M2C_FIELD(arg1, s32 *, 4) + 1, arg1);
    if (temp_v0 != NULL) {
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) = arg3;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = arg4;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) = arg5;
        M2C_FIELD(temp_v0, f32 *, 0x58) = arg3;
        M2C_FIELD(temp_v0, f32 *, 0x5C) = arg4;
        M2C_FIELD(temp_v0, f32 *, 0x60) = arg5;
    }
    return temp_v0;
}

void func_8023101C(s32 arg0, s32 arg1, s32 arg2, u8 *arg3) {
    func_80230CB4(arg0, arg1, arg2, M2C_FIELD(arg3, s32 *, 4) + 1, arg3);
}

void *func_80230E9C(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = func_80230CB4(M2C_FIELD(arg0, s32 *, 0x28), -1, M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 4) + 1, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x30) = (s32) M2C_FIELD(arg0, s32 *, 0x30);
        M2C_FIELD(temp_v0, f32 *, 0x34) = (f32) M2C_FIELD(arg0, f32 *, 0x34);
        M2C_FIELD(temp_v0, f32 *, 0x38) = (f32) M2C_FIELD(arg0, f32 *, 0x38);
        M2C_FIELD(temp_v0, s32 *, 0x3C) = (s32) M2C_FIELD(arg0, s32 *, 0x3C);
        M2C_FIELD(temp_v0, s32 *, 0x2C) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
        M2C_FIELD(temp_v0, f32 *, 0x4C) = (f32) M2C_FIELD(arg0, f32 *, 0x4C);
        M2C_FIELD(temp_v0, f32 *, 0x50) = (f32) M2C_FIELD(arg0, f32 *, 0x50);
        M2C_FIELD(temp_v0, f32 *, 0x54) = (f32) M2C_FIELD(arg0, f32 *, 0x54);
        M2C_FIELD(temp_v0, f32 *, 0x58) = (f32) M2C_FIELD(arg0, f32 *, 0x58);
        M2C_FIELD(temp_v0, f32 *, 0x5C) = (f32) M2C_FIELD(arg0, f32 *, 0x5C);
        M2C_FIELD(temp_v0, f32 *, 0x60) = (f32) M2C_FIELD(arg0, f32 *, 0x60);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x10) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x14) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x18) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x18);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x1C) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x1C);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x20) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x20);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x24) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x24);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x28) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x28);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x2C) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x2C);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x40), f32 *, 0x30) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x30);
    }
    return temp_v0;
}

void func_80230E6C(s32 arg0, s32 arg1) {
    func_80230CB4(arg0, -1, 0, 0xD0, (void *) arg1);
}

void *func_80230CB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    void *sv_a3;
    s32 *sv_a2;
    s32 *sv_a0;
    s32 *temp_v0_2;
    s32 *var_a1_2;
    s32 var_a1;
    u8 *temp_v0;
    u8 *var_v0;

    if (D_802A56FC >= 0x80) {
        return NULL;
    }
    temp_v0 = func_8026CE28(arg0);
    if (temp_v0 == NULL) {
loop_3:
        goto loop_3;
    }
    if (arg2 & 0x100000) {
        var_a1 = 0x51;
    } else {
        var_a1 = 0x40;
        if (arg2 & 0x80000) {
            var_a1 = 0x60;
        }
    }
    if (arg1 == -1) {
        var_v0 = func_8022A6C4(temp_v0, var_a1);
    } else {
        var_v0 = func_8022A328(temp_v0, var_a1, 2, arg1, 0);
    }
    if (var_v0 == NULL) {
loop_12:
        goto loop_12;
    }
    if (D_802A5674 == NULL) {
loop_14:
        goto loop_14;
    }
    sv_a0 = D_802A5674;
    sv_a2 = D_802A5674;
    sv_a3 = var_v0;
    func_8022FC50(D_802A5674);
    sv_a0 = sv_a2;
    func_80230C08(sv_a2);
    if (arg3 < 0xD0) {
        sv_a0 = (s32 *) arg3;
        temp_v0_2 = func_80230B98(arg3);
        if (temp_v0_2 != NULL) {
            var_a1_2 = M2C_FIELD(temp_v0_2, s32 **, 0x78);
        } else {
            var_a1_2 = D_802A56F8;
        }
        func_8022FC20(sv_a2, var_a1_2);
    } else {
        func_8022FC20(sv_a2, &D_802A5678);
    }
    M2C_FIELD(sv_a2, s32 *, 8) = (s32) (M2C_FIELD(sv_a2, s32 *, 8) | 0x80000000 | arg2);
    M2C_FIELD(sv_a2, s32 *, 4) = arg3;
    M2C_FIELD(sv_a2, void **, 0x40) = sv_a3;
    M2C_FIELD(sv_a2, s32 *, 0x28) = arg0;
    M2C_FIELD(sv_a3, s32 *, 0xC) = (s32) (M2C_FIELD(sv_a3, s32 *, 0xC) | 0x61);
    M2C_FIELD(M2C_FIELD(sv_a2, void **, 0x40), s16 *, 0x36) = 0xFF;
    M2C_FIELD(sv_a2, void **, 0x44) = arg4;
    if ((s32) arg4 != (s32) NULL) {
        M2C_FIELD(arg4, s32 *, 0x48) = (s32) (M2C_FIELD(arg4, s32 *, 0x48) + 1);
    }
    D_802A56FC += 1;
    return sv_a2;
}

static void func_80230C08(s32 *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0x7FFFFFFF;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0x7FFFFFFF;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = -1;
    M2C_FIELD(arg0, s32 *, 0x2C) = -1;
    M2C_FIELD(arg0, s32 *, 0x30) = 1;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = 0;
    M2C_FIELD(arg0, f32 *, 0x4C) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x50) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x54) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x58) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x5C) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x60) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x68) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x6C) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x34) = 50.0f;
    M2C_FIELD(arg0, f32 *, 0x38) = 50.0f;
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
    M2C_FIELD(arg0, f32 *, 0x70) = 1.6333334f;
    M2C_FIELD(arg0, f32 *, 0x74) = 100.0f;
}

static s32 *func_80230B98(s32 arg0) {
    s32 *var_v1;

    if (arg0 < 0xD0) {
        var_v1 = M2C_FIELD(&D_802A5578, s32 **, 0x7C);
        D_802A56F8 = &D_802A5578;
        if (var_v1 != NULL) {
loop_2:
            if (arg0 < M2C_FIELD(var_v1, s32 *, 4)) {
                return var_v1;
            }
            D_802A56F8 = var_v1;
            var_v1 = M2C_FIELD(var_v1, s32 **, 0x7C);
            if (var_v1 == NULL) {
                /* Duplicate return node #5. Try simplifying control flow for better match */
                return NULL;
            }
            goto loop_2;
        }
        return NULL;
    }
    return D_802A56F4;
}

void func_80230AA0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;

    temp_fv0 = func_8026E938(M2C_FIELD(arg0, void **, 0x40));
    if (temp_fv0 != 20000.0f) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x40);
        if (((M2C_FIELD(temp_v0, f32 *, 0x14) - M2C_FIELD(arg0, f32 *, 0x6C)) + M2C_FIELD(arg0, f32 *, 0x68)) <= temp_fv0) {
            M2C_FIELD(arg0, f32 *, 0x6C) = 0.0f;
            M2C_FIELD(arg0, f32 *, 0x68) = 0.0f;
            M2C_FIELD(temp_v0, f32 *, 0x14) = temp_fv0;
            return;
        }
    }
    temp_v0_2 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(temp_v0_2, f32 *, 0x14) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 0x14) + M2C_FIELD(arg0, f32 *, 0x68));
    temp_v0_3 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(temp_v0_3, f32 *, 0x14) = (f32) (M2C_FIELD(temp_v0_3, f32 *, 0x14) - M2C_FIELD(arg0, f32 *, 0x6C));
    temp_fv0_2 = M2C_FIELD(arg0, f32 *, 0x6C);
    temp_fv1 = M2C_FIELD(arg0, f32 *, 0x74);
    if (temp_fv0_2 <= temp_fv1) {
        M2C_FIELD(arg0, f32 *, 0x6C) = (f32) (temp_fv0_2 + M2C_FIELD(arg0, f32 *, 0x70));
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x6C) = temp_fv1;
}

void func_80230914(u8 *arg0) {
    f32 sp18;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;

    temp_fv0 = func_8026E938(M2C_FIELD(arg0, void **, 0x40));
    if ((temp_fv0 != 20000.0f) && (temp_v0 = M2C_FIELD(arg0, void **, 0x40), (((M2C_FIELD(temp_v0, f32 *, 0x14) - M2C_FIELD(arg0, f32 *, 0x6C)) + M2C_FIELD(arg0, f32 *, 0x68)) <= temp_fv0))) {
        M2C_FIELD(arg0, f32 *, 0x6C) = 0.0f;
        M2C_FIELD(arg0, f32 *, 0x68) = 0.0f;
        M2C_FIELD(temp_v0, f32 *, 0x14) = temp_fv0;
    } else {
        temp_v0_2 = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(temp_v0_2, f32 *, 0x14) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 0x14) + M2C_FIELD(arg0, f32 *, 0x68));
        temp_v0_3 = M2C_FIELD(arg0, void **, 0x40);
        M2C_FIELD(temp_v0_3, f32 *, 0x14) = (f32) (M2C_FIELD(temp_v0_3, f32 *, 0x14) - M2C_FIELD(arg0, f32 *, 0x6C));
        temp_fv0_2 = M2C_FIELD(arg0, f32 *, 0x6C);
        temp_fv1 = M2C_FIELD(arg0, f32 *, 0x74);
        if (temp_fv0_2 <= temp_fv1) {
            M2C_FIELD(arg0, f32 *, 0x6C) = (f32) (temp_fv0_2 + M2C_FIELD(arg0, f32 *, 0x70));
        } else {
            M2C_FIELD(arg0, f32 *, 0x6C) = temp_fv1;
        }
    }
    if ((M2C_FIELD(arg0, s32 *, 0x30) & ~0x20) == 1) {
        var_fa0 = M2C_FIELD(arg0, f32 *, 0x34) + M2C_FIELD(arg0, f32 *, 0x38);
    } else {
        var_fa0 = M2C_FIELD(arg0, f32 *, 0x38);
    }
    sp18 = var_fa0;
    temp_fv0_3 = func_8022FB00(arg0);
    temp_fv1_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14);
    if ((temp_fv0_3 < temp_fv1_2) || (temp_fv0_3 < (temp_fv1_2 + var_fa0))) {
        if (M2C_FIELD(arg0, f32 *, 0x68) != 0.0f) {
            M2C_FIELD(arg0, f32 *, 0x6C) = 0.0f;
        }
        M2C_FIELD(arg0, f32 *, 0x68) = 0.0f;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14) = (f32) (temp_fv0_3 - var_fa0);
    }
}

void func_802308B8(f32 *arg0, s32 arg1) {
    func_802304C0(arg1, arg0, 0);
}

void func_8023085C(f32 *arg0, s32 arg1) {
    func_802304C0(arg1, arg0, 1);
}

void func_80230800(f32 *arg0, s32 arg1) {
    func_802304C0(arg1, arg0, 2);
}

void func_80230790(f32 *arg0, s32 arg1, f32 *arg2) {
    func_80230604(arg0, arg1, arg2, 0);
}

void func_80230720(f32 *arg0, s32 arg1, f32 *arg2) {
    func_80230604(arg0, arg1, arg2, 1);
}

void func_802306B0(f32 *arg0, s32 arg1, f32 *arg2) {
    func_80230604(arg0, arg1, arg2, 2);
}

static void func_80230604(f32 *arg0, s32 arg1, f32 *arg2, s32 arg3) {
    f32 *sv_a1;
    f32 *sv_a0;
    f32 *temp_v0;

    temp_v0 = func_802304C0(arg1, arg0, arg3);
    D_802A5560 = temp_v0;
    if (temp_v0 != NULL) {
        sv_a0 = D_802A5560;
        func_8022F808(D_802A5560, D_802A5780);
        sv_a1 = D_802A5790;
        func_8022F808(arg0, D_802A5790);
        func_8022FF58(D_802A5780, D_802A5790, &D_802A5568);
        D_802A556C = 0.0f;
        D_802A5570 = (M2C_FIELD(D_802A5560, f32 *, 0x34) + M2C_FIELD(arg0, f32 *, 0x34)) - D_802A5570;
        func_8022FEAC(&D_802A5568, arg2);
    }
}

static f32 *func_802304C0(s32 arg0, f32 *arg1, s32 arg2) {
    static UnkStructA80 *D_802A5A14;
    static UnkStructA80 *D_802A5A18;
    static f32 D_802A5A1C;
    static s32 D_802A5A20;

    D_802A5A14 = D_802A55F4;
    arg0 &= 0x3FFFF;
    D_802A57BC = 32767.0f;
    D_802A5A18 = NULL;
    func_8022F808(arg1, D_802A5780);
    for (; D_802A5A14 != NULL; D_802A5A14 = D_802A5A14->unk7C) {
        if (D_802A5A14->unk4 >= 0xD0) {
            break;
        }
        D_802A5A20 = func_8022F3F8(arg1, (f32 *) D_802A5A14, arg2, arg0);
        if (D_802A5A20 != 0 && func_8022E884(arg1, (f32 *) D_802A5A14) != 0) {
            func_8022F808((f32 *) D_802A5A14, D_802A5790);
            D_802A5A1C = func_8022DF68(D_802A5780, D_802A5790);
            if (D_802A5A1C < D_802A57BC) {
                D_802A5A18 = D_802A5A14;
                D_802A57BC = D_802A5A1C;
            }
        }
    }
    return (f32 *) D_802A5A18;
}

void func_80230440(f32 *arg0, s32 arg1, u8 *arg2) {
    func_8023017C(arg1, arg2, arg0, 0);
}

void func_802303C0(f32 *arg0, s32 arg1, u8 *arg2) {
    func_8023017C(arg1, arg2, arg0, 1);
}

void func_80230340(f32 *arg0, s32 arg1, u8 *arg2) {
    func_8023017C(arg1, arg2, arg0, 2);
}

static void func_8023017C(s32 arg0, u8 *arg1, f32 *arg2, s32 arg3) {
    static UnkStructA80 *D_802A5734;
    static s32 D_802A5758;
    static s32 D_802A578C;
    f32 *out = (f32 *) arg1;
    f32 n;

    D_802A5734 = D_802A55F4;
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    arg0 &= 0x3FFFF;
    D_802A5758 = 0;
    func_8022F808(arg2, D_802A5790);
    for (; D_802A5734 != NULL; D_802A5734 = D_802A5734->unk7C) {
        if (D_802A5734->unk4 >= 0xD0) {
            break;
        }
        D_802A578C = func_8022F3F8(arg2, (f32 *) D_802A5734, arg3, arg0);
        if (D_802A578C != 0 && func_8022E884((UnkStructA80 *) arg2, D_802A5734) != 0) {
            func_8022F808((f32 *) D_802A5734, D_802A5780);
            func_8022FF58(D_802A5780, D_802A5790, D_802A57B0);
            D_802A57B0[1] = 0.0f;
            D_802A57B0[2] = (D_802A5734->unk34 + ((UnkStructA80 *) arg2)->unk34) - D_802A57B0[2];
            func_8022FEAC(D_802A57B0, &D_802A57A0);
            out[0] += D_802A57A0;
            out[2] += D_802A57A8;
            D_802A5758++;
        }
    }
    if (D_802A5758 != 0) {
        n = D_802A5758;
        out[0] /= n;
        out[2] /= n;
    }
}

void func_8022FF58(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 dz;
    f32 dy;
    f32 dx;
    f32 v;
    f32 w;

    dx = arg1[0] - arg0[0];
    dy = arg1[1] - arg0[1];
    dz = arg1[2] - arg0[2];
    arg2[2] = sqrtf(dx * dx + dz * dz);
    if (func_8023372C(arg2[2], 0.002f)) {
        arg2[2] = 0.0f;
        arg2[0] = 0.0f;
        if (func_80233768(dy) == -1) {
            arg2[1] = 0.0f;
        } else {
            arg2[1] = 180.0f;
        }
    } else {
        arg2[0] = func_8029CB40(dx / dz) * 57.29577951308232;
        if (dz < 0.0f) {
            arg2[0] -= 180.0f;
        }
        arg2[1] = func_8029CB40(dy / arg2[2]) * 57.29577951308232;
        v = arg2[0];
        if (v >= 360.0f) {
            arg2[0] = v - 360.0f;
        } else {
            if (v < 0.0f) {
                w = v + 360.0f;
            } else {
                w = v;
            }
            arg2[0] = w;
        }
        v = arg2[1] + 90.0f;
        if (v >= 360.0f) {
            arg2[1] = v - 360.0f;
        } else {
            if (v < 0.0f) {
                w = v + 360.0f;
            } else {
                w = v;
            }
            arg2[1] = w;
        }
    }
    if (func_8023372C(arg2[1], 0.002f)) {
        arg2[1] = 0.0f;
    }
    arg2[2] = sqrtf(dy * dy + arg2[2] * arg2[2]);
}

void func_8022FEAC(f32 *arg0, f32 *arg1) {
    f32 sp24;

    sp24 = func_80234434(M2C_FIELD(arg0, f32 *, 0));
    M2C_FIELD(arg1, f32 *, 0) = func_80234408(M2C_FIELD(arg0, f32 *, 4)) * (M2C_FIELD(arg0, f32 *, 8) * sp24);
    arg1[1] = func_80234434(M2C_FIELD(arg0, f32 *, 4)) * M2C_FIELD(arg0, f32 *, 8);
    sp24 = func_80234408(M2C_FIELD(arg0, f32 *, 0));
    arg1[2] = func_80234408(M2C_FIELD(arg0, f32 *, 4)) * (M2C_FIELD(arg0, f32 *, 8) * sp24);
}

void func_8022FEA0(f32 arg0) {
    D_800A7F00 = arg0;
}

void func_8022FE94(s32 arg0) {
    D_800A7F04 = arg0;
}

void func_8022FDE8() {
    u8 *temp_s0;
    u8 *temp_s0_2;

    temp_s0 = M2C_FIELD(&D_802A5578, void **, 0x7C);
    if (temp_s0 != NULL) {
        do {
            func_8022FC90(temp_s0);
        } while ((s32) M2C_FIELD(&D_802A5578, void **, 0x7C) != NULL);
    }
    temp_s0_2 = M2C_FIELD(&D_802A5678, void **, 0x7C);
    if (temp_s0_2 != NULL) {
        do {
            func_8022FC90(temp_s0_2);
        } while ((s32) M2C_FIELD(&D_802A5678, void **, 0x7C) != NULL);
    }
    D_802A5938 = 0;
    D_800A7F00 = 0.0f;
    D_800A7F04 = 0x7F;
    D_802A5804 = 1;
}

s32 func_8022FC90(u8 *arg0) {
    s32 *sv_a1;
    void *sv_a0;
    u8 *temp_v0;
    u8 *var_v0;
    u8 *var_v1;
    u8 *var_v1_2;

    if (D_802A56FC <= 0) {
        return -1;
    }
    M2C_FIELD(arg0, s32 *, 8) = 0;
    sv_a0 = arg0;
    func_8022FC50(arg0);
    sv_a1 = &D_802A55F8;
    func_8022FC20(arg0, &D_802A55F8);
    func_8022A1E8(M2C_FIELD(arg0, void **, 0x40));
    func_8026CCBC(M2C_FIELD(arg0, s32 *, 0x28));
    temp_v0 = M2C_FIELD(arg0, void **, 0x44);
    M2C_FIELD(arg0, s32 *, 0x28) = -1;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x48) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x48) - 1);
    }
    if (M2C_FIELD(arg0, s32 *, 0x48) != 0) {
        do {
            var_v1 = M2C_FIELD(&D_802A5578, void **, 0x7C);
            var_v0 = NULL;
            if (var_v1 != NULL) {
loop_7:
                if ((s32) arg0 == M2C_FIELD(var_v1, s32 *, 0x44)) {
                    var_v0 = var_v1;
                } else {
                    var_v1 = M2C_FIELD(var_v1, void **, 0x7C);
                    if (var_v1 == NULL) {
                        goto block_10;
                    }
                    goto loop_7;
                }
            } else {
block_10:
                var_v1_2 = M2C_FIELD(&D_802A5678, void **, 0x7C);
                if (var_v1_2 != NULL) {
loop_11:
                    if ((s32) arg0 == M2C_FIELD(var_v1_2, s32 *, 0x44)) {
                        var_v0 = var_v1_2;
                    } else {
                        var_v1_2 = M2C_FIELD(var_v1_2, void **, 0x7C);
                        if (var_v1_2 != NULL) {
                            goto loop_11;
                        }
                    }
                }
            }
            func_8022FC90(var_v0);
        } while (M2C_FIELD(arg0, s32 *, 0x48) != 0);
    }
    D_802A56FC -= 1;
    return M2C_FIELD(arg0, s32 *, 0);
}

static void func_8022FC50(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x7C);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0x78) = (void *) M2C_FIELD(arg0, void **, 0x78);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x78), void **, 0x7C) = (void *) M2C_FIELD(arg0, void **, 0x7C);
        return;
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x78), void **, 0x7C) = NULL;
}

static void func_8022FC20(u8 *arg0, s32 *arg1) {
    u8 *temp_v0;

    M2C_FIELD(arg0, s32 **, 0x78) = arg1;
    M2C_FIELD(arg0, void **, 0x7C) = (void *) M2C_FIELD(arg1, void **, 0x7C);
    M2C_FIELD(arg1, void **, 0x7C) = arg0;
    temp_v0 = M2C_FIELD(arg0, void **, 0x7C);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0x78) = arg0;
    }
}

void func_8022FC18() {

}

void func_8022FC0C(s32 arg0) {
    D_802A5804 = arg0;
}

f32 func_8022FB00(u8 *arg0) {
    s32 sp50[3];
    f32 temp_ft1;
    f32 var_fs0;
    s32 temp_v0_2;
    s32 var_s0;
    u8 temp_ft3;
    u8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x40);
    func_8026DCAC(M2C_FIELD(temp_v0, f32 *, 0x10), M2C_FIELD(temp_v0, f32 *, 0x14), M2C_FIELD(temp_v0, f32 *, 0x18), sp50, 2);
    var_fs0 = 0.0f;
    var_s0 = 0;
    if (sp50[1] >= 0) {
        do {
            temp_ft1 = (f32) func_8026DC74(var_s0);
            var_s0 += 1;
            var_fs0 += temp_ft1 * 100.0f;
        } while (sp50[1] >= var_s0);
    }
    if (var_s0 < 6) {
loop_4:
        temp_v0_2 = func_8026D7D8(sp50[0], var_s0, sp50[2]);
        if (temp_v0_2 != 0x2010) {
            if (!(temp_v0_2 & 0xF)) {
                if (!(temp_v0_2 & 0x60)) {
                    goto block_7;
                }
            }
        } else {
block_7:
            temp_ft3 = func_8026DC74(var_s0);
            var_s0 += 1;
            var_fs0 += (f32) temp_ft3 * 100.0f;
            if (var_s0 >= 6) {

            } else {
                goto loop_4;
            }
        }
    }
    return var_fs0;
}

void func_8022FA88(f32 *arg0, s32 arg1, f32 *arg2) {
    func_8022F844(arg1, arg0, 0, arg2);
}

void func_8022FA10(f32 *arg0, s32 arg1, f32 *arg2) {
    func_8022F844(arg1, arg0, 1, arg2);
}

void func_8022F998(f32 *arg0, s32 arg1, f32 *arg2) {
    func_8022F844(arg1, arg0, 2, arg2);
}

static f32 *func_8022F844(s32 arg0, f32 *arg1, s32 arg2, f32 *arg3) {
    static UnkStructA80 *D_802A593C;
    static UnkStructA80 *D_802A5940;
    static f32 D_802A5944;
    static s32 D_802A5948;

    D_802A593C = D_802A55F4;
    arg0 &= 0x3FFFF;
    D_802A57BC = 32767.0f;
    D_802A5940 = NULL;
    func_8022F808(arg1, D_802A5780);
    for (; D_802A593C != NULL; D_802A593C = D_802A593C->unk7C) {
        if (D_802A593C->unk4 >= 0xD0) {
            break;
        }
        D_802A5948 = func_8022F3F8(arg1, (f32 *) D_802A593C, arg2, arg0);
        if (D_802A5948 != 0) {
            func_8022F808((f32 *) D_802A593C, D_802A5790);
            D_802A5944 = func_8022DF68(D_802A5780, D_802A5790);
            if (D_802A5944 < D_802A57BC) {
                D_802A5940 = D_802A593C;
                D_802A57BC = D_802A5944;
            }
        }
    }
    *arg3 = D_802A57BC;
    if (*arg3 == 32767.0f) {
        D_802A5940 = NULL;
    }
    return (f32 *) D_802A5940;
}

void func_8022F808(f32 *arg0, f32 *arg1) {
    M2C_FIELD(arg1, f32 *, 0) = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x10);
    arg1[1] = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x14);
    arg1[2] = M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 0x18);
}

s32 func_8022F77C(s32 arg0, s32 arg1, s32 arg2) {
    UnkStructA80 *o;

    arg0 &= 0x3FFFF;
    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if ((o->unk8 & arg0) && func_8022F5E4((f32 *) o, (u8 *) arg1, (u8 *) arg2) != 0) {
            return (s32) o;
        }
    }
    return 0;
}

s32 func_8022F698(s32 arg0, f32 *arg1, f32 *arg2, f32 **arg3, s32 arg4) {
    f32 *var_t0;
    s32 var_t1;
    s32 var_v0;

    var_t0 = D_802A55F4;
    arg0 &= 0x3FFFF;
    var_t1 = 0;
    if (var_t0 != NULL && arg4 > 0) {
        do {
            if ((M2C_FIELD(var_t0, s32 *, 8) & arg0) && func_8022F5E4(var_t0, arg1, arg2) != 0) {
                *arg3++ = var_t0;
                var_t1++;
            }
            var_t0 = M2C_FIELD(var_t0, f32 **, 0x7C);
        } while (var_t0 != NULL && var_t1 < arg4);
    }
    for (var_v0 = var_t1; var_v0 < arg4; var_v0++) {
        *arg3++ = NULL;
    }
    return var_t1;
}

static s32 func_8022F5E4(f32 *arg0, u8 *arg1, u8 *arg2) {
    f32 *n = (f32 *) ((UnkStructA80 *) arg0)->unk40;
    f32 *c = (f32 *) arg1;
    f32 *r = (f32 *) arg2;

    if (c[0] - r[0] <= n[4] && n[4] <= c[0] + r[0] && c[1] - r[1] <= n[5] && n[5] <= c[1] + r[1] &&
        c[2] - r[2] <= n[6] && n[6] <= c[2] + r[2]) {
        return 1;
    }
    return 0;
}

f32 *func_8022F550(f32 *arg0, s32 arg1) {
    UnkStructA80 *o;

    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if (func_8022F3F8(arg0, (f32 *) o, 0, arg1) != 0 && func_8022E884((UnkStructA80 *) arg0, o) != 0) {
            return (f32 *) o;
        }
    }
    return NULL;
}

f32 *func_8022F4AC(f32 *arg0, s32 arg1, f32 *arg2) {
    UnkStructA80 *o;

    for (o = D_802A55F4; o != NULL; o = o->unk7C) {
        if (o->unk4 >= 0xD0) {
            break;
        }
        if (o != (UnkStructA80 *) arg2 && func_8022F3F8(arg0, (f32 *) o, 0, arg1) != 0 &&
            func_8022E884((UnkStructA80 *) arg0, o) != 0) {
            return (f32 *) o;
        }
    }
    return NULL;
}

static s32 func_8022F3F8(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3) {
    s32 r;

    if (arg0 == arg1) {
        return 0;
    }
    switch (arg2) {
    case 0:
        if (((UnkStructA80 *) arg1)->unk8 & arg3) {
            r = 1;
        } else {
            r = 0;
        }
        break;
    case 1:
        if (arg3 == (((UnkStructA80 *) arg1)->unk8 & arg3)) {
            r = 1;
        } else {
            r = 0;
        }
        break;
    case 2:
        if (arg3 == (((UnkStructA80 *) arg1)->unk8 & 0x3FFFF)) {
            r = 1;
        } else {
            r = 0;
        }
        break;
    default:
        for (;;) {
        }
    }
    return r;
}

static s32 func_8022E4DC(f32 *a, f32 *b) {
    static Vec3f p;
    static Vec3f q;
    static Vec3f ap;
    static Vec3f qp;
    static Vec3f aq;
    static Vec3f pq;
    static Vec3f n;
    f32 d;

    if (b[4] + a[3] + b[3] < func_8022DF68(a, b)) {
        return 0;
    }
    guMtxIdentF((f32 (*)[4]) D_802A57C0);
    func_8029C8D0((f32 (*)[4]) D_802A57C0, b[5], b[6], b[7]);
    func_8029CA80((f32 (*)[4]) D_802A57C0, 0.0f, b[4] + a[3], 0.0f);
    p.x = 0.0f;
    p.y = 0.0f;
    p.z = 0.0f;
    func_8022E3D4((f32 (*)[4]) D_802A57C0, &p.x);
    p.x += b[0];
    p.y += b[1];
    p.z += b[2];
    guMtxIdentF((f32 (*)[4]) D_802A57C0);
    func_8029C8D0((f32 (*)[4]) D_802A57C0, b[5], b[6], b[7]);
    func_8029CA80((f32 (*)[4]) D_802A57C0, 0.0f, a[3] * -1.0f, 0.0f);
    q.x = 0.0f;
    q.y = 0.0f;
    q.z = 0.0f;
    func_8022E3D4((f32 (*)[4]) D_802A57C0, &q.x);
    q.x += b[0];
    q.y += b[1];
    q.z += b[2];
    ap.x = a[0] - p.x;
    ap.y = a[1] - p.y;
    ap.z = a[2] - p.z;
    qp.x = q.x - p.x;
    qp.y = q.y - p.y;
    qp.z = q.z - p.z;
    pq.x = p.x - q.x;
    pq.y = p.y - q.y;
    pq.z = p.z - q.z;
    aq.x = a[0] - q.x;
    aq.y = a[1] - q.y;
    aq.z = a[2] - q.z;
    func_8022E364(&ap.x, &qp.x, &n.x);
    d = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
    if (b[3] + a[3] <= d / sqrtf(qp.x * qp.x + qp.y * qp.y + qp.z * qp.z)) {
        return 0;
    }
    if (func_8022E330(&pq.x, &ap.x) > 0.0f || func_8022E330(&qp.x, &aq.x) > 0.0f) {
        return 0;
    }
    return 1;
}

void func_8022E3D4(f32 m[4][4], f32 *v) {
    static f32 D_802A594C;
    static f32 D_802A5950;
    static f32 D_802A5954;
    static f32 D_802A5958;
    f32 tx, ty, tz;
    f32 x, y, z;

    x = v[0];
    y = v[1];
    z = v[2];
    tx = m[3][0] + (x * m[0][0] + y * m[1][0] + m[2][0] * z);
    ty = m[3][1] + (x * m[0][1] + y * m[1][1] + m[2][1] * z);
    tz = m[3][2] + (x * m[0][2] + y * m[1][2] + m[2][2] * z);
    D_802A5958 = m[3][3] + (x * m[0][3] + y * m[1][3] + m[2][3] * z);
    v[0] = tx * D_802A5958;
    v[1] = ty * D_802A5958;
    v[2] = tz * D_802A5958;
    D_802A594C = tx;
    D_802A5950 = ty;
    D_802A5954 = tz;
}

void func_8022E364(f32 *a, f32 *b, f32 *c) {
    c[0] = a[1] * b[2] - b[1] * a[2];
    c[1] = a[2] * b[0] - b[2] * a[0];
    c[2] = a[0] * b[1] - b[0] * a[1];
}

f32 func_8022E330(f32 *a, f32 *b) {
    return a[0] * b[0] + a[1] * b[1] + b[2] * a[2];
}

void func_8022E328() {

}

static void func_8022E264() {
}

static void func_8022E26C(UnkStructA80 *arg0, f32 *arg1) {
    f32 h;
    f32 r;

    func_8022E264();
    if (arg0->unk30 & 0x20) {
        h = r = 1.0f;
    } else {
        r = arg0->unk40->scale[0];
        if (r < arg0->unk40->scale[1]) {
            r = arg0->unk40->scale[1];
        }
        if (r < arg0->unk40->scale[2]) {
            r = arg0->unk40->scale[2];
        }
        h = arg0->unk40->scale[1];
    }
    arg1[0] = arg0->unk40->pos[0];
    arg1[1] = arg0->unk40->pos[1] + arg0->unk38 * h;
    arg1[2] = arg0->unk40->pos[2];
    arg1[3] = arg0->unk34 * r;
}

static s32 func_8022E178(f32 *a, f32 *b) {
    if (a[0] <= b[0]) {
        if (a[0] + a[3] <= b[0]) {
            return 0;
        }
    } else if (b[0] + b[4] <= a[0] - a[3]) {
        return 0;
    }
    D_802A5780[0] = 0.0f;
    D_802A5780[1] = a[1];
    D_802A5780[2] = a[2];
    D_802A5790[0] = 0.0f;
    D_802A5790[1] = b[1];
    D_802A5790[2] = b[2];
    if (a[3] + b[3] <= func_8022DF68(D_802A5780, D_802A5790)) {
        return 0;
    }
    return 1;
}

void func_8022E170() {

}

static void func_8022E0A4() {
}

static void func_8022E0AC(UnkStructA80 *arg0, f32 *arg1) {
    f32 r;

    func_8022E0A4();
    r = arg0->unk40->scale[0];
    if (r < arg0->unk40->scale[2]) {
        r = arg0->unk40->scale[2];
    }
    arg1[0] = arg0->unk40->pos[0];
    arg1[1] = arg0->unk40->pos[1];
    arg1[2] = arg0->unk40->pos[2];
    arg1[5] = arg0->unk40->rot[0];
    arg1[6] = arg0->unk40->rot[1];
    arg1[7] = arg0->unk40->rot[2];
    arg1[3] = arg0->unk34 * r;
    arg1[4] = arg0->unk38 * arg0->unk40->scale[1];
}

static s32 func_8022DFBC(f32 *a, f32 *b) {
    s32 r;
    f32 d;

    if (a[2] <= b[2]) {
        if (a[2] + a[3] <= b[2]) {
            return 0;
        }
    } else if (b[2] + b[4] <= a[2] - a[3]) {
        return 0;
    }
    D_802A5780[0] = a[0];
    D_802A5780[1] = a[1];
    D_802A5780[2] = 0.0f;
    D_802A5790[0] = b[0];
    D_802A5790[1] = b[1];
    D_802A5790[2] = 0.0f;
    if (a[3] + b[3] <= func_8022DF68(D_802A5780, D_802A5790)) {
        return 0;
    }
    return 1;
}

f32 func_8022DF68(f32 *arg0, f32 *arg1) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = M2C_FIELD(arg1, f32 *, 0) - M2C_FIELD(arg0, f32 *, 0);
    temp_fv1 = arg1[1] - arg0[1];
    temp_fa1 = arg1[2] - arg0[2];
    return ((sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1))));
}

s32 func_8022E884(UnkStructA80 *arg0, UnkStructA80 *arg1) {
    static f32 D_802A5708[4];
    static f32 D_802A5720[4];
    static f32 D_802A5738[8];
    static f32 D_802A5760[8];
    static f32 D_802A59D0[4];
    static f32 D_802A59E8[4];
    static f32 D_802A5A00[4];
    s32 sa;
    s32 hit;
    s32 ret;
    s32 r;
    s32 dx;
    s32 dy;
    s32 dz;
    f32 n;
    f32 y;
    f32 step;
    f32 t;

    sa = arg0->unk30 & ~0x20;
    switch (sa | (arg1->unk30 & ~0x20)) {
    case 1:
        func_8022E26C(arg0, D_802A5708);
        func_8022E26C(arg1, D_802A5720);
        r = D_802A5708[3] + D_802A5720[3];
        dx = D_802A5708[0] - D_802A5720[0];
        dy = D_802A5708[1] - D_802A5720[1];
        dz = D_802A5708[2] - D_802A5720[2];
        if (dx * dx + dz * dz + dy * dy < r * r) {
            hit = 1;
        } else {
            hit = 0;
        }
        break;
    case 2:
        func_8022E0AC(arg0, D_802A5738);
        func_8022E0AC(arg1, D_802A5760);
        hit = 0;
        if (D_802A5738[4] + D_802A5738[3] + D_802A5760[4] + D_802A5760[3] < func_8022DF68(D_802A5738, D_802A5760)) {
            break;
        }
        n = D_802A5738[4] / (D_802A5738[3] * 2.0f);
        y = D_802A5738[3];
        D_802A59D0[3] = D_802A5738[3];
        hit = 0;
        while (n > 0.0f) {
            guMtxIdentF((f32 (*)[4]) D_802A57C0);
            func_8029C8D0((f32 (*)[4]) D_802A57C0, D_802A5738[5], D_802A5738[6], D_802A5738[7]);
            func_8029CA80((f32 (*)[4]) D_802A57C0, 0.0f, y, 0.0f);
            D_802A59D0[0] = D_802A59D0[1] = D_802A59D0[2] = 0.0f;
            func_8022E3D4((f32 (*)[4]) D_802A57C0, D_802A59D0);
            D_802A59D0[0] += D_802A5738[0];
            D_802A59D0[1] += D_802A5738[1];
            D_802A59D0[2] += D_802A5738[2];
            if (func_8022E4DC(D_802A59D0, D_802A5760) == 1) {
                hit = 1;
                break;
            }
            n -= 1.0f;
            if (n >= 1.0f) {
                y += D_802A59D0[3] + D_802A59D0[3];
            } else {
                y += (D_802A59D0[3] + D_802A59D0[3]) * n;
            }
        }
        break;
    case 3:
        switch (sa) {
        case 1:
            func_8022E26C(arg0, D_802A5708);
            func_8022E0AC(arg1, D_802A5738);
            break;
        case 2:
            func_8022E0AC(arg0, D_802A5738);
            func_8022E26C(arg1, D_802A5708);
            break;
        default:
            for (;;) {
            }
        }
        hit = func_8022E4DC(D_802A5708, D_802A5738);
        func_8022E328();
        break;
    case 9:
        switch (sa) {
        case 1:
            func_8022E26C(arg0, D_802A5708);
            func_8022E0AC(arg1, D_802A5738);
            break;
        case 8:
            func_8022E0AC(arg0, D_802A5738);
            func_8022E26C(arg1, D_802A5708);
            break;
        default:
            for (;;) {
            }
        }
        hit = func_8022E178(D_802A5708, D_802A5738);
        break;
    case 5:
        switch (sa) {
        case 1:
            func_8022E26C(arg0, D_802A5708);
            func_8022E0AC(arg1, D_802A5738);
            break;
        case 4:
            func_8022E0AC(arg0, D_802A5738);
            func_8022E26C(arg1, D_802A5708);
            break;
        default:
            for (;;) {
            }
        }
        if (D_802A5708[1] <= D_802A5738[1]) {
            if (D_802A5708[1] + D_802A5708[3] <= D_802A5738[1]) {
                hit = 0;
                break;
            }
        } else if (D_802A5738[1] + D_802A5738[4] <= D_802A5708[1] - D_802A5708[3]) {
            hit = 0;
            break;
        }
        D_802A5780[0] = D_802A5708[0];
        D_802A5780[1] = 0.0f;
        D_802A5780[2] = D_802A5708[2];
        D_802A5790[0] = D_802A5738[0];
        D_802A5790[1] = 0.0f;
        D_802A5790[2] = D_802A5738[2];
        if (D_802A5708[3] + D_802A5738[3] <= func_8022DF68(D_802A5780, D_802A5790)) {
            hit = 0;
        } else {
            hit = 1;
        }
        break;
    case 17:
        switch (sa) {
        case 1:
            func_8022E26C(arg0, D_802A5708);
            func_8022E0AC(arg1, D_802A5738);
            break;
        case 16:
            func_8022E0AC(arg0, D_802A5738);
            func_8022E26C(arg1, D_802A5708);
            break;
        default:
            for (;;) {
            }
        }
        hit = func_8022DFBC(D_802A5708, D_802A5738);
        break;
    case 12:
        func_8022E0AC(arg0, D_802A5738);
        func_8022E0AC(arg1, D_802A5760);
        D_802A59E8[0] = D_802A5738[0];
        D_802A59E8[1] = D_802A5738[1] + D_802A5738[3];
        D_802A59E8[3] = D_802A5738[3];
        D_802A59E8[2] = D_802A5738[2];
        step = D_802A5738[3] * 2.0f;
        hit = 0;
        for (t = 0.0f; t < D_802A5738[4];) {
            if (func_8022E178(D_802A59E8, D_802A5760) != 0) {
                hit = 1;
                break;
            }
            t += step;
            if (t + step <= D_802A5738[4]) {
                D_802A59E8[1] += step;
            } else {
                D_802A59E8[1] += D_802A5738[4] - t;
            }
        }
        break;
    case 4:
        func_8022E170();
        func_8022E0AC(arg0, D_802A5738);
        func_8022E0AC(arg1, D_802A5760);
        if (D_802A5738[1] <= D_802A5760[1]) {
            if (D_802A5738[1] + D_802A5738[4] <= D_802A5760[1]) {
                hit = 0;
                break;
            }
        } else if (D_802A5760[1] + D_802A5760[4] <= D_802A5738[1]) {
            hit = 0;
            break;
        }
        D_802A5780[0] = D_802A5738[0];
        D_802A5780[1] = 0.0f;
        D_802A5780[2] = D_802A5738[2];
        D_802A5790[0] = D_802A5760[0];
        D_802A5790[1] = 0.0f;
        D_802A5790[2] = D_802A5760[2];
        if (D_802A5738[3] + D_802A5760[3] <= func_8022DF68(D_802A5780, D_802A5790)) {
            hit = 0;
        } else {
            hit = 1;
        }
        break;
    case 20:
        func_8022E0AC(arg0, D_802A5738);
        func_8022E0AC(arg1, D_802A5760);
        D_802A5A00[0] = D_802A5738[0];
        D_802A5A00[1] = D_802A5738[1] + D_802A5738[3];
        D_802A5A00[3] = D_802A5738[3];
        D_802A5A00[2] = D_802A5738[2];
        step = D_802A5738[3] * 2.0f;
        hit = 0;
        for (t = 0.0f; t < D_802A5738[4];) {
            if (func_8022DFBC(D_802A5A00, D_802A5760) != 0) {
                hit = 1;
                break;
            }
            t += step;
            if (t + step <= D_802A5738[4]) {
                D_802A5A00[1] += step;
            } else {
                D_802A5A00[1] += D_802A5738[4] - t;
            }
        }
        break;
    default:
        for (;;) {
        }
    }
    ret = hit;
    if (hit) {
        sa = arg0->unkC & arg1->unk8;
        if (sa != 0) {
            arg0->unk14 |= sa;
            if (arg0->unk1C >= arg1->unk4) {
                arg0->unk1C = arg1->unk4;
                arg0->unk24 = (s32) arg1;
            }
        }
        sa = arg1->unkC & arg0->unk8;
        if (sa != 0) {
            arg1->unk14 |= sa;
            if (arg1->unk1C >= arg0->unk4) {
                arg1->unk1C = arg0->unk4;
                arg1->unk24 = (s32) arg0;
            }
        }
        ret = arg1->unk8 & 0x3FFFF;
    }
    return ret;
}

void func_8022DE6C() {
    s32 i;

    if (!(*func_8023A840() & 2)) {
        D_800A7F28 = func_8026CE28(0x34E);
        for (i = 0; i < 8; i++) {
            D_800A7F08[i] = func_8022A6C4(D_800A7F28, 0x40);
            D_800A7F08[i]->x0 = 291.0f;
            D_800A7F08[i]->y0 = 56.0f;
            D_800A7F08[i]->x1 = 291.0f;
            D_800A7F08[i]->y1 = 56.0f;
            D_800A7F08[i]->unk20 = 0.0f;
            D_800A7F08[i]->unk24 = 0.0f;
        }
    }
}

void func_8022DE00() {
    s32 i;

    if (!(*func_8023A840() & 2)) {
        for (i = 0; i < 8; i++) {
            func_8022A1E8(D_800A7F08[i]);
        }
        func_8026CCBC(0x34E);
        D_800A7F28 = NULL;
    }
}

void func_8022DDB4(s32 arg0) {
    if (!(*func_8023A840() & 2)) {
        func_80238A10(func_8022DD6C, arg0, 0, 0, 0x150);
    }
}

static void func_8022DD6C() {
    func_8022DBF4(D_800A7F08, 291.0f, 56.0f, func_802391F0(), 0);
    func_80239430();
}

static void func_8022DBF4(Rect40 **arg0, f32 arg1, f32 arg2, s32 *arg3, s32 arg4) {
    Rect40 *r;
    s32 cur;
    s32 tgt;
    s32 n;
    f32 f;

    r = *arg0;
    cur = 0;
    while (TRUE) {
        n = *arg3 - arg4;
        if (n < 0) {
            n = 0;
        }
        if (n < 3) {
            tgt = n * 4;
        } else {
            tgt = 8;
        }
        if (cur == tgt && n == 0) {
            break;
        }
        if (cur == tgt && n >= 3) {
            func_8022DBF4(arg0 + 1, arg1, arg2 + 16.0f + 4.0f, arg3, arg4 + 2);
        }
        if (cur < tgt) {
            cur++;
        } else if (tgt < cur) {
            cur--;
        }
        f = cur;
        r->x0 = arg1 - f;
        r->y0 = arg2 - f;
        r->x1 = f + arg1;
        r->y1 = f + arg2;
        func_8023903C(2);
    }
}

void func_8022DBBC(s32 arg0) {
    func_80238A10(func_8022DB28, arg0, 0, 0, 0x150);
}

static void func_8022DB28() {
    s32 *args;
    Rect40 *r;
    s32 id;
    s32 n;
    s32 i;

    args = (s32 *) func_802391F0();
    r = (Rect40 *) args[0]; id = args[1]; n = args[2];
    id = func_8026C51C(id, r->x0, r->y0, r->x1);
    for (i = 0; i < n; i++) {
        func_8026C454(id, r->x0, r->y0, r->x1);
        func_80239094();
    }
    func_80239430();
}

void func_8022DB00(void) {
    func_80297D30(0x18, D_8029FD40);
}
