/*
 * NON_MATCHING: ovl_12_05's game object, complete: every function and its data.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 4009
 *
 * A first draft: most of it is m2c's C, cleaned up only where it didn't
 * compile; the functions with twins elsewhere are their C, renamed
 * (ovl_12_03, 12_04, 12_06, 10_13, 0C_10, 0E_15, 17_09, 17_10).
 * .data (0x10: the initializer of 80044534's local sound table), .rodata
 * (0x240, the original's bytes but for the jump tables' relocations) and
 * .bss (0xA0) build to the original's sizes.
 *
 * 800434C8 and 80044534 are statics: their callers 80047DA4 and 80047E90
 * save every callee-saved register for them. The handler's cases
 * (80043018-80045B00) are defined above the handler, so that IDO emits
 * them, with the statics, in the reverse order of the handler's calls, as
 * in the original. The empty statics leave the `jr ra; nop` stubs at
 * 80043010, 80044480, 80045834/3C, 80046318, 80046340 and, unused, the
 * twelve at 800492FC-80049354.
 *
 * What still differs (words; tools/nonmatching.py counts a static with the
 * function before it):
 * - 80043018 (1273, with the static 800434C8) and 80044488 (1104, with the
 *   statics 800444D4 and 80044534): the cut-scenes, m2c's C.
 * - 80047F94 (346), 800486C4 (234), 80045D3C (220, the handler), 80047238
 *   (187), 80045B00 (106), 800475C8 (102), 80048C3C (99), 800485A0 (64),
 *   80048DD4 (58), 80046D20 (57), 80048F04 (32), 800479B0 (30), 80047774
 *   (24), 80047860 (21), 800466C4 (15), 80046990 (15), 80046F44 (9),
 *   80047B64 (5), 80046348 (2), 8004712C (2), 80047544 (2), 80048EC8 (1),
 *   800492E4 (1).
 */
#include "common.h"

#define ANGLE_ADD(a, d) \
    (a) = ((a) + (d) >= 360.0f) ? (a) + (d) - 360.0f : ((a) + (d) < 0.0f) ? (a) + (d) + 360.0f : (a) + (d)

/* What func_ovl12_05_800497F8 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x14];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
} UnkStruct_ovl12_05_800497F8;

/* What func_ovl12_05_8004A840 returns: a player. */
typedef struct {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ u8 unk4[0x18];
    /* 0x01C */ UnkStructA *unk1C;
    /* 0x020 */ u8 unk20[0xC];
    /* 0x02C */ Vec3f unk2C;
    /* 0x038 */ u8 unk38[0x50];
    /* 0x088 */ s32 unk88;
    /* 0x08C */ u8 unk8C[4];
    /* 0x090 */ s32 unk90;
    /* 0x094 */ u8 unk94[0xC];
    /* 0x0A0 */ union {
        s32 w;
        struct {
            u16 hi;
            u16 lo;
        } h;
    } unkA0;
    /* 0x0A4 */ u8 unkA4[0x80];
    /* 0x124 */ s32 unk124;
} UnkStruct_ovl12_05_8004A840;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl12_05_8004AC30;

void func_ovl12_05_800496C0(s32);
void func_ovl12_05_800496D8(f32);
void func_ovl12_05_80049730(UnkStructA_40 *, f32 *, f32 *);
void func_ovl12_05_80049790(void (*)(UnkStructA *));
void func_ovl12_05_800497A0(s32, s32, s32);
s32 func_ovl12_05_800497A8(void);
void func_ovl12_05_800497E0(void (*)(UnkStructA *));
UnkStruct_ovl12_05_800497F8 *func_ovl12_05_800497F8(void);
void func_ovl12_05_80049820(s32);
void func_ovl12_05_80049830(s32, s32);
void func_ovl12_05_80049848(s32);
void func_ovl12_05_80049858(void);
void func_ovl12_05_80049860(s32, s32, s32);
void func_ovl12_05_80049868(void *);
s32 func_ovl12_05_80049888(void);
void func_ovl12_05_80049890(s32, void *);
void func_ovl12_05_80049898(s32);
void func_ovl12_05_800498A0(s32);
void func_ovl12_05_800498A8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl12_05_800498B8(void);
UnkStructA *func_ovl12_05_800498E8(s32);
void func_ovl12_05_800498F0(s32);
void func_ovl12_05_80049918(s32);
void func_ovl12_05_80049938(s32, s32);
void func_ovl12_05_80049958(void);
s32 func_ovl12_05_80049970(s32);
UnkStructA_40 *func_ovl12_05_80049D88(s32, s32);
void func_ovl12_05_80049D90(UnkStructA_40 *);
void func_ovl12_05_80049DA8(UnkStructA_40 *, s32);
void func_ovl12_05_80049DB0(UnkStructA_40 *, s32);
void func_ovl12_05_80049DB8(UnkStructA_40 *, s32, s32, s32);
void func_ovl12_05_80049DD0(UnkStructA_40 *, s32, s32);
void func_ovl12_05_80049E10(s32, s32);
s32 func_ovl12_05_80049E18(UnkStructA_40 *, s32);
void func_ovl12_05_80049E20(s32, s32, s32);
void func_ovl12_05_80049E30(s32, s32, s32);
void func_ovl12_05_80049ED8(s32);
void func_ovl12_05_80049EE8(f32, f32, f32);
void func_ovl12_05_80049EF8(f32, f32, f32);
void func_ovl12_05_80049F08(f32, f32, f32);
void func_ovl12_05_80049F10(f32 *, f32 *, f32 *);
void func_ovl12_05_80049F48(s32);
void func_ovl12_05_80049F50(s32);
void func_ovl12_05_80049FB8(void);
void func_ovl12_05_80049FC0(s32);
void func_ovl12_05_80049FD0(f32, f32, f32);
void func_ovl12_05_8004A038(Vec3f *, Vec3f *, Vec3f *);
void func_ovl12_05_8004A0A8(UnkStructA *, s32);
void func_ovl12_05_8004A0B0(UnkStructA *, s32);
void func_ovl12_05_8004A0C0(UnkStructA *);
UnkStructA *func_ovl12_05_8004A0D0(s32, s32, s32, s32);
UnkStructA *func_ovl12_05_8004A0E0(UnkStructA *);
UnkStructA *func_ovl12_05_8004A0F0(s32, s32, f32, f32, f32);
void func_ovl12_05_8004A128(UnkStructA *);
s32 func_ovl12_05_8004A1F8(void (*)(void), void *, s32, s32, s32);
void func_ovl12_05_8004A200(s32);
void func_ovl12_05_8004A208(void);
void func_ovl12_05_8004A210(u16, s32);
void func_ovl12_05_8004A218(s32);
UnkStructA *func_ovl12_05_8004A220(void);
void func_ovl12_05_8004A240(void);
void func_ovl12_05_8004A258(u16);
void func_ovl12_05_8004A268(s32, s32, s32);
UnkStructC *func_ovl12_05_8004A280(s32);
void func_ovl12_05_8004A290(UnkStructC *, s32);
f32 func_ovl12_05_8004A3A0(f32);
f32 func_ovl12_05_8004A3A8(f32);
f64 func_ovl12_05_8004A3B0(void);
s32 func_ovl12_05_8004A3B8(s32);
void func_ovl12_05_8004A418(void);
void func_ovl12_05_8004A420(void);
void func_ovl12_05_8004A428(Vec3f *);
void func_ovl12_05_8004A478(s32);
void func_ovl12_05_8004A4F0(void);
void func_ovl12_05_8004A500(s32, s32, s32, s32);
void func_ovl12_05_8004A510(s32, s32, s32, s32);
void func_ovl12_05_8004A648(s32, f32, f32, f32, s32);
void func_ovl12_05_8004A688(void);
void func_ovl12_05_8004A6E8(void);
void func_ovl12_05_8004A780(s32);
void func_ovl12_05_8004A790(s32);
void func_ovl12_05_8004A798(void);
void func_ovl12_05_8004A7A0(s32, f32, f32, f32);
void func_ovl12_05_8004A7C0(s32);
void func_ovl12_05_8004A7E0(s32);
void func_ovl12_05_8004A810(UnkStructA_40 *, s32, s32, s32, f32);
void func_ovl12_05_8004A820(UnkStructA_40 *);
void func_ovl12_05_8004A828(s32, s32, s32, s32, s32);
UnkStruct_ovl12_05_8004A840 *func_ovl12_05_8004A840(s32);
void func_ovl12_05_8004A848(s32);
void func_ovl12_05_8004A8F8(void);
void func_ovl12_05_8004A900(void);

static void func_ovl12_05_80043010(void);
void func_ovl12_05_80043018(void);
static void func_ovl12_05_800434C8(void);
static void func_ovl12_05_80044480(void);
void func_ovl12_05_80044488(void);
static f32 func_ovl12_05_800444D4(UnkStructA_40 *from, UnkStructA_40 *to);
static void func_ovl12_05_80044534(void);
void func_ovl12_05_800456A0(void);
void func_ovl12_05_80045754(void);
static void func_ovl12_05_80045834(void);
static void func_ovl12_05_8004583C(void);
void func_ovl12_05_80045844(void);
void func_ovl12_05_80045954(void);
void func_ovl12_05_80045A70(void);
void func_ovl12_05_80045B00(void);
void func_ovl12_05_80045D3C(s32 arg0);
void func_ovl12_05_80046258(UnkStructA *arg0);
static void func_ovl12_05_80046318(void);
void func_ovl12_05_80046320(void);
static void func_ovl12_05_80046340(void);
void func_ovl12_05_80046348(void);
void func_ovl12_05_80046390(f32 arg0);
void func_ovl12_05_800463D8(void);
void func_ovl12_05_800464F0(void);
void func_ovl12_05_80046538(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4);
void func_ovl12_05_80046560(void);
void func_ovl12_05_800465E4(void);
void func_ovl12_05_800466C4(void);
void func_ovl12_05_80046990(void);
void func_ovl12_05_80046D20(void);
void func_ovl12_05_80046F44(void);
void func_ovl12_05_8004712C(void);
void func_ovl12_05_80047238(void);
void func_ovl12_05_80047544(void);
void func_ovl12_05_800475C8(void);
void func_ovl12_05_80047774(void);
void func_ovl12_05_80047860(void);
void func_ovl12_05_800479B0(void);
void func_ovl12_05_80047B64(void);
void func_ovl12_05_80047DA4(void);
void func_ovl12_05_80047E90(void);
void func_ovl12_05_80047F68(void);
void func_ovl12_05_80047F94(void);
void func_ovl12_05_800485A0(void);
void func_ovl12_05_800486C4(void);
void func_ovl12_05_80048ABC(void);
void func_ovl12_05_80048C3C(void);
void func_ovl12_05_80048DD4(void);
void func_ovl12_05_80048EC8(UnkStructA *arg0);
void func_ovl12_05_80048F04(void);
void func_ovl12_05_80049130(UnkStructA *arg0);
void func_ovl12_05_800491A8(void);
void func_ovl12_05_800491E8(void);
void func_ovl12_05_80049254(s32 arg0, UnkStructA *arg1);
void func_ovl12_05_80049288(f32 arg0, f32 arg1, f32 arg2);
void func_ovl12_05_800492E4(void);
static void func_ovl12_05_800492FC(void);
static void func_ovl12_05_80049304(void);
static void func_ovl12_05_8004930C(void);
static void func_ovl12_05_80049314(void);
static void func_ovl12_05_8004931C(void);
static void func_ovl12_05_80049324(void);
static void func_ovl12_05_8004932C(void);
static void func_ovl12_05_80049334(void);
static void func_ovl12_05_8004933C(void);
static void func_ovl12_05_80049344(void);
static void func_ovl12_05_8004934C(void);
static void func_ovl12_05_80049354(void);

/* .data: the sound table 80044534 initializes its local from (0x10) */

u8 D_ovl12_05_8004ABF0[0x10];
Vec3f D_ovl12_05_8004AC00;
s32 D_ovl12_05_8004AC0C[2]; /* the second word unused */
s32 D_ovl12_05_8004AC14;
s32 D_ovl12_05_8004AC18[2]; /* the second word unused */
f32 D_ovl12_05_8004AC20[4]; /* a position; the fourth word unused */
UnkStruct_ovl12_05_8004AC30 D_ovl12_05_8004AC30;
UnkStructA *D_ovl12_05_8004AC44;
UnkStructA *D_ovl12_05_8004AC48;
s32 D_ovl12_05_8004AC4C;
s32 D_ovl12_05_8004AC50;
UnkStructA *D_ovl12_05_8004AC54;
s32 D_ovl12_05_8004AC58;
UnkStructC *D_ovl12_05_8004AC5C;
s32 D_ovl12_05_8004AC60;
s32 D_ovl12_05_8004AC64;
s32 D_ovl12_05_8004AC68;
s32 D_ovl12_05_8004AC6C;
s32 D_ovl12_05_8004AC70;
s32 D_ovl12_05_8004AC74;
f32 D_ovl12_05_8004AC78;
f32 D_ovl12_05_8004AC7C;
f32 D_ovl12_05_8004AC80;
UnkStructA *D_ovl12_05_8004AC84;

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl12_05_80049354(void) {
}

static void func_ovl12_05_8004934C(void) {
}

static void func_ovl12_05_80049344(void) {
}

static void func_ovl12_05_8004933C(void) {
}

static void func_ovl12_05_80049334(void) {
}

static void func_ovl12_05_8004932C(void) {
}

static void func_ovl12_05_80049324(void) {
}

static void func_ovl12_05_8004931C(void) {
}

static void func_ovl12_05_80049314(void) {
}

static void func_ovl12_05_8004930C(void) {
}

static void func_ovl12_05_80049304(void) {
}

static void func_ovl12_05_800492FC(void) {
}

void func_ovl12_05_800492E4(void) {
    D_ovl12_05_8004AC14 = -1;
    D_ovl12_05_8004AC18[0] = -1;
}

/* twin of 17_09:80044B14 (nonmatching/overlays/ovl_17_09/2B8D20.c) */
void func_ovl12_05_80049288(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl12_05_80049EE8(D_ovl12_05_8004AC20[0], D_ovl12_05_8004AC20[1], D_ovl12_05_8004AC20[2]);
    func_ovl12_05_80049F08(arg0, arg1, arg2);
    func_ovl12_05_8004A218(180);
}

/* twin of 17_10:80044CB8 (src/overlays/ovl_17_10/2BC0B0.c) */
void func_ovl12_05_80049254(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl12_05_8004A7A0(arg0, p->unk10, p->unk14, p->unk18);
}

/* twin of 12_03:80043EFC (nonmatching/overlays/ovl_12_03/250B70.c) */
void func_ovl12_05_800491E8(void) {
    UnkStructC *obj;

    func_ovl12_05_800491A8();
    func_ovl12_05_80049790(func_ovl12_05_80049130);
    func_ovl12_05_800497E0(func_ovl12_05_80046258);
    obj = func_ovl12_05_8004A280(0x2E5);
    func_ovl12_05_8004A290(obj, 0x20000001);
    obj->unk18 = 0.03f;
    obj->unk1C = 0.0f;
}

/* twin of 12_03:80043EBC (nonmatching/overlays/ovl_12_03/250B70.c) */
void func_ovl12_05_800491A8(void) {
    func_ovl12_05_8004A478(0x400);
    func_ovl12_05_8004A478(0x401);
    func_ovl12_05_8004A478(0x402);
    func_ovl12_05_8004A478(0x403);
    func_ovl12_05_8004A478(0x404);
}

/* twin of 12_03:80044440 (nonmatching/overlays/ovl_12_03/250B70.c) */
void func_ovl12_05_80049130(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl12_05_80049F50(0x10);
    }
    func_ovl12_05_8004A0B0(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        func_ovl12_05_8004A128(arg0);
        func_ovl12_05_8004A240();
    }
}

void func_ovl12_05_80048F04(void) {
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_fs1;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;

    var_fs1 = 0.0f;
loop_1:
    D_ovl12_05_8004AC54->unk40->unk14 = (func_ovl12_05_8004A3A0(var_fs1) * 5.0f) + D_ovl12_05_8004AC78;
    temp_v0 = D_ovl12_05_8004AC54->unk40;
    temp_fv1 = temp_v0->unk1C + D_ovl12_05_8004AC7C;
    if (temp_fv1 >= 360.0f) {
        temp_v0->unk1C = temp_fv1 - 360.0f;
    } else {
        if (temp_fv1 < 0.0f) {
            var_fv0 = temp_fv1 + 360.0f;
        } else {
            var_fv0 = temp_fv1;
        }
        temp_v0->unk1C = var_fv0;
    }
    temp_v0_2 = D_ovl12_05_8004AC54->unk40;
    temp_fv1_2 = temp_v0_2->unk20 + (2.0f * D_ovl12_05_8004AC7C);
    if (temp_fv1_2 >= 360.0f) {
        temp_v0_2->unk20 = temp_fv1_2 - 360.0f;
    } else {
        if (temp_fv1_2 < 0.0f) {
            var_fv0_2 = temp_fv1_2 + 360.0f;
        } else {
            var_fv0_2 = temp_fv1_2;
        }
        temp_v0_2->unk20 = var_fv0_2;
    }
    temp_v0_3 = D_ovl12_05_8004AC54->unk40;
    temp_fv1_3 = temp_v0_3->unk24 + (0.1f * D_ovl12_05_8004AC7C);
    if (temp_fv1_3 >= 360.0f) {
        temp_v0_3->unk24 = temp_fv1_3 - 360.0f;
    } else {
        if (temp_fv1_3 < 0.0f) {
            var_fv0_3 = temp_fv1_3 + 360.0f;
        } else {
            var_fv0_3 = temp_fv1_3;
        }
        temp_v0_3->unk24 = var_fv0_3;
    }
    temp_fv1_4 = var_fs1 + 5.0f;
    if (temp_fv1_4 >= 360.0f) {
        var_fs1 = temp_fv1_4 - 360.0f;
    } else {
        if (temp_fv1_4 < 0.0f) {
            var_fv0_4 = temp_fv1_4 + 360.0f;
        } else {
            var_fv0_4 = temp_fv1_4;
        }
        var_fs1 = var_fv0_4;
    }
    func_ovl12_05_8004A240();
    goto loop_1;
}

void func_ovl12_05_80048EC8(UnkStructA *arg0) {
    if (arg0 == func_ovl12_05_800498E8(0)) {
        func_ovl12_05_8004A0B0(arg0, 0x01000000);
    }
}

/* twin of 0C_10:800447E4 (nonmatching/overlays/ovl_0C_10/194190.c) */
/* a task: bobs the object it is given up and down */
void func_ovl12_05_80048DD4(void) {
    UnkStructA *obj;
    f32 angle;

    obj = func_ovl12_05_8004A220();
    angle = 0.0f;
    while (TRUE) {
        obj->unk40->unk14 += func_ovl12_05_8004A3A8(angle) * 2.0f;
        ANGLE_ADD(angle, 5.0f);
        func_ovl12_05_8004A240();
    }
}

/* twin of 10_13:80047298 (nonmatching/overlays/ovl_10_13/2439F0.c) */
void func_ovl12_05_80048C3C(void) {
    UnkStructA *temp_s1;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 var_s0;

    var_fs0 = 0.0f;
    temp_s1 = func_ovl12_05_8004A220();
loop_1:
    var_s0 = 0;
    do {
        if ((func_ovl12_05_8004A3A0(var_fs0) * 0.5f) < 0.0f) {
            var_fv1 = -(func_ovl12_05_8004A3A0(var_fs0) * 0.5f);
        } else {
            var_fv1 = func_ovl12_05_8004A3A0(var_fs0) * 0.5f;
        }
        func_ovl12_05_8004A810(temp_s1->unk40, 0x1F, 0x1F, 0x1F, var_fv1);
        temp_fv0 = var_fs0 + 6.0f;
        if (temp_fv0 >= 360.0f) {
            var_fs0 = temp_fv0 - 360.0f;
        } else {
            if (temp_fv0 < 0.0f) {
                var_fv1_2 = temp_fv0 + 360.0f;
            } else {
                var_fv1_2 = temp_fv0;
            }
            var_fs0 = var_fv1_2;
        }
        func_ovl12_05_8004A240();
        var_s0 += 1;
    } while (var_s0 != 0x3C);
    goto loop_1;
}

void func_ovl12_05_80048ABC(void) {
    UnkStructA_40 *temp_v0;
    f32 temp_fv0;
    s32 var_s1;
    s32 var_s3;

    temp_v0 = func_ovl12_05_80049D88(0x2C7, 0);
    temp_v0->unkC |= 0x80;
    temp_v0->unk10 = D_ovl12_05_8004AC54->unk40->unk10;
    temp_v0->unk14 = D_ovl12_05_8004AC54->unk40->unk14;
    var_s3 = 0;
    temp_v0->unk18 = D_ovl12_05_8004AC54->unk40->unk18;
    do {
        func_ovl12_05_8004A780(0x28B);
        temp_v0->unk36 = 0x96;
        temp_v0->unk30 = 0.0f;
        temp_v0->unk2C = 0.0f;
        temp_v0->unk28 = 0.0f;
        var_s1 = 0;
loop_2:
        temp_fv0 = temp_v0->unk28 + 2.0f;
        temp_v0->unk30 = temp_fv0;
        temp_v0->unk2C = temp_fv0;
        temp_v0->unk28 = temp_fv0;
        temp_v0->unk36 = (s16) (s32) ((f32) temp_v0->unk36 - 7.5f);
        func_ovl12_05_8004A240();
        var_s1 += 1;
        if (var_s1 != 0x14) {
            goto loop_2;
        }
        var_s3 += 1;
    } while (var_s3 != 0xF);
    func_ovl12_05_80049D90(temp_v0);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_800486C4(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_s0;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fs1;
    f32 var_fs4;
    s32 var_s2;
    s32 var_s2_2;

    temp_v0 = func_ovl12_05_8004A0D0(0x346, 0x01080000, 0xC0, 0);
    D_ovl12_05_8004AC84 = temp_v0;
    temp_s0 = temp_v0->unk40;
    temp_s0->unk36 = 0;
    temp_s0->unk10 = D_ovl12_05_8004AC54->unk40->unk10;
    var_s2 = 0;
    temp_s0->unk14 = D_ovl12_05_8004AC54->unk40->unk14;
    var_fs1 = 0.0f;
    temp_s0->unk28 = 0.0f;
    temp_s0->unk2C = 0.0f;
    temp_s0->unk30 = 0.0f;
    temp_s0->unk18 = D_ovl12_05_8004AC54->unk40->unk18;
    do {
        temp_fv0 = temp_s0->unk28 + 0.1125f;
        temp_s0->unk30 = temp_fv0;
        temp_s0->unk2C = temp_fv0;
        temp_s0->unk28 = temp_fv0;
        temp_s0->unk1C = D_ovl12_05_8004AC54->unk40->unk1C;
        temp_s0->unk20 = D_ovl12_05_8004AC54->unk40->unk20;
        temp_s0->unk24 = D_ovl12_05_8004AC54->unk40->unk24;
        temp_fs0 = (f32) (var_s2 / 5);
        if (((func_ovl12_05_8004A3A0(var_fs1) * 40.0f) + temp_fs0) < 0.0f) {
            temp_s0->unk36 = (s16) (s32) -((func_ovl12_05_8004A3A0(var_fs1) * 40.0f) + temp_fs0);
        } else {
            temp_s0->unk36 = (s16) (s32) ((func_ovl12_05_8004A3A0(var_fs1) * 40.0f) + temp_fs0);
        }
        temp_fv0_2 = var_fs1 + 5.4f;
        if (temp_fv0_2 >= 360.0f) {
            var_fs1 = temp_fv0_2 - 360.0f;
        } else {
            if (temp_fv0_2 < 0.0f) {
                var_fs4 = temp_fv0_2 + 360.0f;
            } else {
                var_fs4 = temp_fv0_2;
            }
            var_fs1 = var_fs4;
        }
        func_ovl12_05_8004A240();
        var_s2 += 1;
    } while (var_s2 < 0x190);
    var_s2_2 = 0;
    temp_fs0_2 = (f32) temp_s0->unk36 / 60.0f;
loop_12:
    temp_s0->unk1C = D_ovl12_05_8004AC54->unk40->unk1C;
    temp_s0->unk20 = D_ovl12_05_8004AC54->unk40->unk20;
    temp_s0->unk36 = (s16) (s32) ((f32) temp_s0->unk36 - temp_fs0_2);
    temp_s0->unk24 = D_ovl12_05_8004AC54->unk40->unk24;
    if (temp_s0->unk36 < 0xA) {
        temp_s0->unk36 = 0xA;
    } else {
        func_ovl12_05_8004A240();
        var_s2_2 += 1;
        if (var_s2_2 != 0x3C) {
            goto loop_12;
        }
    }
    temp_s0->unkC |= 0x1000;
loop_16:
    temp_s0->unk1C = D_ovl12_05_8004AC54->unk40->unk1C;
    temp_s0->unk20 = D_ovl12_05_8004AC54->unk40->unk20;
    temp_s0->unk24 = D_ovl12_05_8004AC54->unk40->unk24;
    func_ovl12_05_8004A240();
    goto loop_16;
}

void func_ovl12_05_800485A0(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_s0;

    temp_v0 = func_ovl12_05_8004A0D0(0x346, 0x01080000, 0xC0, 0);
    D_ovl12_05_8004AC84 = temp_v0;
    temp_s0 = temp_v0->unk40;
    temp_s0->unk36 = 0xA;
    temp_s0->unk10 = D_ovl12_05_8004AC54->unk40->unk10;
    temp_s0->unk14 = D_ovl12_05_8004AC54->unk40->unk14;
    temp_s0->unkC |= 0x1000;
    temp_s0->unk28 = 45.0f;
    temp_s0->unk2C = 45.0f;
    temp_s0->unk30 = 45.0f;
    temp_s0->unk18 = D_ovl12_05_8004AC54->unk40->unk18;
loop_1:
    temp_s0->unk1C = D_ovl12_05_8004AC54->unk40->unk1C;
    temp_s0->unk20 = D_ovl12_05_8004AC54->unk40->unk20;
    temp_s0->unk24 = D_ovl12_05_8004AC54->unk40->unk24;
    func_ovl12_05_8004A240();
    goto loop_1;
}

void func_ovl12_05_80047F94(void) {
    UnkStruct_ovl12_05_8004A840 *sp44;
    UnkStructA *sp40;
    UnkStructA *temp_v0_2;
    UnkStructA_40 *temp_v0_10;
    UnkStructA_40 *temp_v0_11;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    UnkStructA_40 *temp_v0_6;
    UnkStructA_40 *temp_v0_7;
    UnkStructA_40 *temp_v0_9;
    UnkStructA_40 *temp_v1;
    UnkStruct_ovl12_05_8004A840 *temp_v0;
    UnkStruct_ovl12_05_8004A840 *temp_v0_8;
    f32 temp_fv0;
    f32 var_fs0;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_s0_7;
    s32 var_s0_8;

    temp_v0 = func_ovl12_05_8004A840(1);
    sp44 = temp_v0;
    func_ovl12_05_8004A210(temp_v0->unkA0.h.lo, -1);
    sp40 = func_ovl12_05_800498E8(0);
    temp_v0_2 = func_ovl12_05_800498E8(1);
    temp_v1 = temp_v0_2->unk40;
    func_ovl12_05_8004A7A0(0x2AE, temp_v1->unk10, temp_v1->unk14, temp_v1->unk18);
    if (D_ovl12_05_8004AC4C != 0x1A) {
        func_ovl12_05_80049938(0, 3);
        func_ovl12_05_80049ED8(0);
        var_s0 = 0;
        do {
            temp_v0_3 = sp40->unk40;
            temp_v0_3->unk18 -= 8.0f;
            temp_v0_4 = sp40->unk40;
            func_ovl12_05_80049EE8(temp_v0_4->unk10, temp_v0_4->unk14, temp_v0_4->unk18);
            func_ovl12_05_8004A240();
            var_s0 += 8;
        } while (var_s0 != 0x1F8);
    }
    func_ovl12_05_80049938(0, 0);
    func_ovl12_05_80049ED8(1);
    temp_v0_5 = temp_v0_2->unk40;
    func_ovl12_05_80049EE8(temp_v0_5->unk10, temp_v0_5->unk14 + 50.0f, temp_v0_5->unk18);
    var_fs0 = 1206.0f;
    func_ovl12_05_80049F08(0.0f, 21.0f, 1206.0f);
    func_ovl12_05_8004A218(0x1E);
    var_s0_2 = 0;
    do {
        func_ovl12_05_80049F08(0.0f, 21.0f, var_fs0);
        var_fs0 -= 5.8333335f;
        func_ovl12_05_8004A240();
        var_s0_2 += 1;
    } while (var_s0_2 < 0x78);
    func_ovl12_05_8004A218(0x1E);
    var_s0_3 = 0;
    do {
        temp_v0_6 = temp_v0_2->unk40;
        temp_v0_6->unk14 += 2.0f;
        temp_v0_7 = temp_v0_2->unk40;
        func_ovl12_05_80049EE8(temp_v0_7->unk10, temp_v0_7->unk14 + 50.0f, temp_v0_7->unk18);
        func_ovl12_05_8004A240();
        var_s0_3 += 1;
    } while (var_s0_3 < 0x3C);
    D_ovl12_05_8004AC60 = func_ovl12_05_8004A1F8(func_ovl12_05_80048DD4, temp_v0_2, 0, 0, 0x130);
    func_ovl12_05_8004A780(0x289);
    func_ovl12_05_8004A218(0x1E);
    var_s0_4 = 0;
    do {
        func_ovl12_05_80049F08(0.0f, 21.0f, var_fs0);
        var_fs0 += 20.0f;
        func_ovl12_05_8004A240();
        var_s0_4 += 1;
    } while (var_s0_4 < 0x1E);
    func_ovl12_05_8004A780(0x28C);
    D_ovl12_05_8004AC80 = 0.5f;
    D_ovl12_05_8004AC64 = func_ovl12_05_8004A1F8(func_ovl12_05_80048C3C, NULL, 0, 0, 0x130);
    func_ovl12_05_8004A218(0x3C);
    func_ovl12_05_8004A1F8(func_ovl12_05_80048ABC, NULL, 0, 0, 0x130);
    var_s0_5 = 0;
    do {
        func_ovl12_05_80049F08(0.0f, 21.0f, var_fs0);
        var_fs0 += 43.333332f;
        func_ovl12_05_8004A240();
        var_s0_5 += 1;
    } while (var_s0_5 < 0x1E);
    func_ovl12_05_8004A780(0x28D);
    D_ovl12_05_8004AC68 = func_ovl12_05_8004A1F8(func_ovl12_05_800486C4, NULL, 0, 0, 0x130);
    func_ovl12_05_8004A0A8(D_ovl12_05_8004AC48, 0x80000);
    var_s0_6 = 0;
    do {
        temp_fv0 = func_ovl12_05_8004A3A0(((f32) var_s0_6 / 200.0f) * 90.0f);
        D_ovl12_05_8004AC44->unk40->unk36 = (s16) (s32) (temp_fv0 * 255.0f);
        D_ovl12_05_8004AC48->unk40->unk36 = (s16) (s32) ((1.0f - temp_fv0) * 255.0f);
        func_ovl12_05_8004A240();
        var_s0_6 += 1;
    } while (var_s0_6 < 0xC8);
    func_ovl12_05_8004A0B0(D_ovl12_05_8004AC44, 0x80000);
    func_ovl12_05_8004A0C0(D_ovl12_05_8004AC48);
    if (D_ovl12_05_8004AC4C == 0x1A) {
        temp_v0_8 = func_ovl12_05_8004A840(1);
        sp44 = temp_v0_8;
        func_ovl12_05_8004A200(temp_v0_8->unkA0.w);
        func_ovl12_05_8004A218(0x3C);
        func_ovl12_05_8004A8F8();
        D_ovl12_05_8004AC50 = 0;
        func_ovl12_05_8004A208();
    }
    var_s0_7 = 0;
    do {
        D_ovl12_05_8004AC78 += (func_ovl12_05_8004A3A0(((f32) var_s0_7 / 60.0f) * 90.0f) * 200.0f) / 60.0f;
        func_ovl12_05_8004A240();
        var_s0_7 += 1;
    } while (var_s0_7 < 0x3C);
    D_ovl12_05_8004AC7C = 0.3f;
    D_ovl12_05_8004AC80 = 0.3f;
    func_ovl12_05_8004A218(0x3C);
    func_ovl12_05_80049ED8(1);
    temp_v0_9 = temp_v0_2->unk40;
    func_ovl12_05_80049EE8(temp_v0_9->unk10, temp_v0_9->unk14 + 50.0f, temp_v0_9->unk18);
    func_ovl12_05_80049F08(0.0f, 21.0f, 800.0f);
    func_ovl12_05_8004A200(D_ovl12_05_8004AC60);
    var_s0_8 = 0;
    do {
        temp_v0_10 = temp_v0_2->unk40;
        temp_v0_10->unk14 -= 2.0f;
        temp_v0_11 = temp_v0_2->unk40;
        func_ovl12_05_80049EE8(temp_v0_11->unk10, temp_v0_11->unk14 + 50.0f, temp_v0_11->unk18);
        func_ovl12_05_8004A240();
        var_s0_8 += 1;
    } while (var_s0_8 != 0x3C);
    temp_v0_2->unk40->unk14 = 0.0f;
    func_ovl12_05_80049ED8(1);
    func_ovl12_05_80049F48(0x10);
    func_ovl12_05_80049F50(0xF);
    func_ovl12_05_8004A848(1);
    func_ovl12_05_80049918(1);
    func_ovl12_05_80049898(0);
    func_ovl12_05_80049918(0);
    func_ovl12_05_8004A258(sp44->unkA0.h.lo);
    D_ovl12_05_8004AC50 = 0;
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80047F68(void) {
    func_ovl12_05_8004A218(0x78);
    D_ovl12_05_8004AC50 = 0;
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80047E90(void) {
    func_ovl12_05_8004A200(func_ovl12_05_8004A840(1)->unkA0.w);
    func_ovl12_05_80044534();
}

/* twin of 10_13:800477E8 (nonmatching/overlays/ovl_10_13/2439F0.c) */
void func_ovl12_05_80047DA4(void) {
    func_ovl12_05_8004A200(func_ovl12_05_8004A840(1)->unkA0.w);
    func_ovl12_05_8004A200(func_ovl12_05_8004A840(2)->unkA0.w);
    func_ovl12_05_800434C8();
}

/* twin of 10_13:80046E88 (nonmatching/overlays/ovl_10_13/2439F0.c) */
void func_ovl12_05_80047B64(void) {
    Vec3f *pos;
    UnkStructA_40 *p;
    s32 i;

    pos = func_ovl12_05_8004A220();
    p = func_ovl12_05_80049D88(0x302, 0);
    p->unkC |= 0x80;
    p->unk36 = 0;
    p->unk10 = pos->x + 50.0f;
    p->unk14 = func_ovl12_05_8004A3B0() * 100.0 + (pos->y - 50.0f) + 50.0;
    p->unk18 = func_ovl12_05_8004A3B0() * 100.0 + (pos->z - 50.0f);
    p->unk28 = 0.3f;
    p->unk2C = 0.3f;
    p->unk30 = 0.3f;
    for (i = 0; i < 30; i++) {
        p->unk36 += 1.6666666f;
        p->unk10 -= 1.0f;
        if (p->unk14 < pos->y + 50.0f) {
            p->unk14 += (pos->y - p->unk14) / 30.0f;
        } else {
            p->unk14 -= (p->unk14 - pos->y) / 30.0f;
        }
        if (p->unk18 < pos->z + 50.0f) {
            p->unk18 += (pos->z - p->unk18) / 30.0f;
        } else {
            p->unk18 -= (p->unk18 - pos->z) / 30.0f;
        }
        func_ovl12_05_8004A240();
    }
    func_ovl12_05_80049D90(p);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_800479B0(void) {
    UnkStructA *temp_s0;
    UnkStructA_40 *temp_v0;
    f32 temp_fs2;
    s16 var_s2;
    s32 var_s0;

    func_ovl12_05_8004A780(0x239);
    temp_s0 = func_ovl12_05_8004A220();
    temp_v0 = func_ovl12_05_80049D88(0x32E, 0);
    temp_v0->unkC |= 0x80;
    temp_v0->unk36 = 0x96;
    temp_v0->unk10 = temp_s0->unk40->unk10;
    temp_v0->unk14 = temp_s0->unk40->unk14 + 80.0f;
    temp_v0->unk28 = 1.3f;
    temp_v0->unk2C = 1.3f;
    temp_v0->unk18 = temp_s0->unk40->unk18 + 40.0f;
    temp_v0->unk30 = 1.3f;
    func_ovl12_05_8004A648(0, temp_v0->unk10, temp_v0->unk14, temp_v0->unk18, 0);
    temp_fs2 = D_ovl12_05_8004AC54->unk40->unk18;
    var_s0 = 0;
    var_s2 = 0x80;
    do {
        D_ovl12_05_8004AC54->unk40->unk18 = (func_ovl12_05_8004A3A0((f32) var_s0 * 22.5f) * 20.0f) + temp_fs2;
        temp_v0->unk36 = var_s2;
        if (temp_v0->unk36 < 0) {
            temp_v0->unk36 = 0;
        }
        func_ovl12_05_8004A240();
        var_s0 += 1;
        var_s2 -= 0x10;
    } while (var_s0 != 8);
    D_ovl12_05_8004AC54->unk40->unk18 = temp_fs2;
    func_ovl12_05_80049D90(temp_v0);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80047860(void) {
    f32 sp38;
    UnkStructA *temp_s2;
    UnkStructA_40 *temp_s0;
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_s1;

    temp_s2 = func_ovl12_05_8004A220();
    temp_s0 = func_ovl12_05_80049D88(0x2C7, 0);
    temp_fa0 = (f32) (func_ovl12_05_8004A3B0() * 359.0);
    temp_ft4 = func_ovl12_05_8004A3A0(temp_fa0) * 150.0f;
    sp38 = temp_ft4;
    temp_fv0 = func_ovl12_05_8004A3A8(temp_fa0);
    temp_s0->unk10 = temp_s2->unk40->unk10 + temp_ft4;
    temp_fv1 = temp_fv0 * 150.0f;
    temp_s0->unk14 = temp_s2->unk40->unk14 + temp_fv1 + 70.0f;
    var_s1 = 0;
    temp_s0->unk28 = 0.2f;
    temp_s0->unk2C = 0.2f;
    temp_s0->unk30 = 0.2f;
    temp_s0->unk18 = temp_s2->unk40->unk18;
    do {
        temp_s0->unk10 -= temp_ft4 / 60.0f;
        temp_s0->unk14 -= temp_fv1 / 60.0f;
        func_ovl12_05_8004A240();
        var_s1 += 1;
    } while (var_s1 != 0x3C);
    func_ovl12_05_80049D90(temp_s0);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80047774(void) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fs0;
    f32 var_fs1;

    var_fs1 = 0.0f;
    var_fs0 = 0.0f;
loop_1:
    D_ovl12_05_8004AC5C->unk3C += var_fs0;
    temp_fv1 = D_ovl12_05_8004AC5C->unk4C;
    temp_fv0 = D_ovl12_05_8004AC5C->unk3C;
    if (temp_fv1 < temp_fv0) {
        D_ovl12_05_8004AC5C->unk3C = temp_fv0 - temp_fv1;
    }
    if (var_fs0 < 2.0f) {
        var_fs0 += var_fs1;
    }
    var_fs1 += 0.01f;
    func_ovl12_05_8004A240();
    goto loop_1;
}

/* twin of 0E_15:80043E8C (nonmatching/overlays/ovl_0E_15/1DF480.c) */
/* a task: an object put at random near the one it is given, for four frames */
void func_ovl12_05_800475C8(void) {
    UnkStructA *src;
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 i;

    src = func_ovl12_05_8004A220();
    obj = func_ovl12_05_8004A0D0(0x1CF, 0x01000000, 0x20, 0);
    p = obj->unk40;
    func_ovl12_05_80049DB0(p, 2);
    p->unk10 = src->unk40->unk10;
    p->unk14 = src->unk40->unk14;
    p->unk18 = src->unk40->unk18;
    p->unk28 = 0.5f;
    p->unk2C = 0.5f;
    p->unk30 = 0.5f;
    p->unk10 += func_ovl12_05_8004A3B0() * 200.0 - 100.0;
    p->unk14 += func_ovl12_05_8004A3B0() * 200.0 - 100.0 + 130.0;
    p->unk18 += func_ovl12_05_8004A3B0() * 200.0 - 100.0;
    for (i = 0; i < 4; i++) {
        func_ovl12_05_80049DB8(p, 0x1D0, 0, i * 2);
        func_ovl12_05_80049DB8(p, 0x1D0, 1, i * 2 + 1);
        func_ovl12_05_8004A240();
    }
    func_ovl12_05_8004A0C0(obj);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80047544(void) {
    UnkStructA *temp_s1;
    s32 var_s0;

    temp_s1 = func_ovl12_05_8004A220();
    var_s0 = 0;
    do {
        func_ovl12_05_8004A1F8(func_ovl12_05_80047860, temp_s1, 0, 0, 0x130);
        func_ovl12_05_8004A218(4);
        var_s0 += 1;
    } while (var_s0 != 0x20);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80047238(void) {
    UnkStructA *temp_s5;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;

    var_fs0 = 0.0f;
    temp_s5 = func_ovl12_05_8004A220();
    var_s1 = 0;
    var_s3 = 0;
    var_s2 = 0;
    var_s0 = 0;
    do {
        func_ovl12_05_8004A810(temp_s5->unk40, var_s2, 0, 0, 0.8f);
        var_s2 = (s32) ((f32) var_s2 + 1.5f);
        func_ovl12_05_8004A240();
        var_s0 += 1;
    } while (var_s0 < 0x14);
    var_s0_2 = 0;
    do {
        func_ovl12_05_8004A810(temp_s5->unk40, var_s2, var_s3, 0, 0.8f);
        var_s3 = (s32) ((f32) var_s3 + 1.5f);
        func_ovl12_05_8004A240();
        var_s0_2 += 1;
    } while (var_s0_2 < 0x14);
    var_s0_3 = 0;
    do {
        func_ovl12_05_8004A810(temp_s5->unk40, var_s2, var_s3, var_s1, 0.8f);
        var_s1 = (s32) ((f32) var_s1 + 1.5f);
        func_ovl12_05_8004A240();
        var_s0_3 += 1;
    } while (var_s0_3 != 0x14);
loop_7:
    var_s0_4 = 0;
    do {
        temp_s2 = func_ovl12_05_8004A3B8(0x1E);
        temp_s3 = func_ovl12_05_8004A3B8(0x1E);
        temp_s1 = func_ovl12_05_8004A3B8(0x1E);
        if ((func_ovl12_05_8004A3A0(var_fs0) * 0.8f) < 0.0f) {
            var_fv1 = -(func_ovl12_05_8004A3A0(var_fs0) * 0.8f);
        } else {
            var_fv1 = func_ovl12_05_8004A3A0(var_fs0) * 0.8f;
        }
        func_ovl12_05_8004A810(temp_s5->unk40, temp_s2, temp_s3, temp_s1, var_fv1);
        temp_fv0 = var_fs0 + 6.0f;
        if (temp_fv0 >= 360.0f) {
            var_fs0 = temp_fv0 - 360.0f;
        } else {
            if (temp_fv0 < 0.0f) {
                var_fv1_2 = temp_fv0 + 360.0f;
            } else {
                var_fv1_2 = temp_fv0;
            }
            var_fs0 = var_fv1_2;
        }
        func_ovl12_05_8004A240();
        var_s0_4 += 1;
    } while (var_s0_4 != 0x3C);
    goto loop_7;
}

void func_ovl12_05_8004712C(void) {
    UnkStructA *temp_s2;
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    s32 var_s0;

    temp_s2 = func_ovl12_05_8004A220();
    temp_v0 = func_ovl12_05_8004A0D0(0x2D5, 0x01080000, 0xD0, 0);
    temp_v0->unk40->unk10 = temp_s2->unk40->unk10;
    temp_v0->unk40->unk14 = temp_s2->unk40->unk14 + 100.0f;
    temp_v0->unk40->unk18 = temp_s2->unk40->unk18;
    temp_v0->unk40->unk1C = 270.0f;
    temp_v0->unk40->unk2C = 90.0f;
    var_s0 = 0;
    temp_v0->unk40->unk36 = 0x50;
    do {
        temp_v0_2 = temp_v0->unk40;
        temp_v0_2->unk18 += 20.0f;
        func_ovl12_05_8004A240();
        var_s0 += 1;
    } while (var_s0 != 0xC8);
    func_ovl12_05_8004A0C0(temp_v0);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80046F44(void) {
    f32 sp40;
    f32 sp3C;
    UnkStructA *temp_s0;
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fv1;
    s32 var_s0;

    func_ovl12_05_8004A218(func_ovl12_05_8004A3B8(0x10) + 1);
    temp_s0 = func_ovl12_05_8004A220();
    temp_v0 = func_ovl12_05_8004A0D0(0x307, 0x01080000, 0xD0, 0);
    temp_v0->unk40->unk10 = temp_s0->unk40->unk10;
    temp_v0->unk40->unk14 = temp_s0->unk40->unk14 + 100.0f;
    temp_v0->unk40->unk18 = temp_s0->unk40->unk18;
    temp_v0->unk40->unk36 = 0x80;
    temp_v0->unk40->unk1C = 90.0f;
    temp_fs0 = (f32) ((func_ovl12_05_8004A3B0() * 200.0) + 600.0);
    temp_fa0 = (f32) (func_ovl12_05_8004A3B0() * 360.0);
    sp40 = func_ovl12_05_8004A3A0(temp_fa0) * temp_fs0;
    sp3C = func_ovl12_05_8004A3A8(temp_fa0) * temp_fs0;
    temp_fv1 = (f32) (func_ovl12_05_8004A3B0() + 0.20000000298023224);
    temp_v0->unk40->unk30 = temp_fv1;
    temp_v0->unk40->unk2C = temp_fv1;
    var_s0 = 0;
    temp_v0->unk40->unk28 = temp_fv1;
    do {
        temp_v0_2 = temp_v0->unk40;
        temp_v0_2->unk10 += sp40 / 30.0f;
        temp_v0_3 = temp_v0->unk40;
        temp_v0_3->unk14 += sp3C / 30.0f;
        func_ovl12_05_8004A240();
        var_s0 += 1;
    } while (var_s0 != 0x1E);
    func_ovl12_05_8004A0C0(temp_v0);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80046D20(void) {
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    UnkStructA *temp_s0;
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    f32 temp_fa0;
    f32 temp_fs1;
    s32 var_s0;
    s32 var_s0_2;

    func_ovl12_05_8004A218(func_ovl12_05_8004A3B8(0x10) + 4);
    temp_s0 = func_ovl12_05_8004A220();
    temp_v0 = func_ovl12_05_8004A0D0(0x1CB, 0x01080000, 0xD0, 0);
    temp_v0->unk40->unk10 = temp_s0->unk40->unk10;
    temp_v0->unk40->unk14 = temp_s0->unk40->unk14 + 100.0f;
    temp_v0->unk40->unk18 = temp_s0->unk40->unk18;
    temp_fs1 = (f32) ((func_ovl12_05_8004A3B0() * 200.0) + 600.0);
    temp_fa0 = (f32) (func_ovl12_05_8004A3B0() * 360.0);
    sp38 = temp_fa0;
    sp40 = func_ovl12_05_8004A3A0(temp_fa0) * temp_fs1;
    sp3C = func_ovl12_05_8004A3A8(temp_fa0) * temp_fs1;
    temp_v0->unk40->unk24 = 360.0f - sp38;
    temp_v0->unk40->unk30 = 0.04f;
    temp_v0_2 = temp_v0->unk40;
    temp_v0_2->unk28 = temp_v0_2->unk30;
    var_s0 = 0;
    temp_v0->unk40->unk2C = 0.0f;
    do {
        temp_v0_3 = temp_v0->unk40;
        temp_v0_3->unk2C += (temp_fs1 / 120.0f) / 50.0f;
        func_ovl12_05_8004A240();
        var_s0 += 1;
    } while (var_s0 < 0x3C);
    var_s0_2 = 0;
    do {
        temp_v0_4 = temp_v0->unk40;
        temp_v0_4->unk10 += sp40 / 120.0f;
        temp_v0_5 = temp_v0->unk40;
        temp_v0_5->unk14 += sp3C / 120.0f;
        func_ovl12_05_8004A240();
        var_s0_2 += 1;
    } while (var_s0_2 != 0x3C);
    func_ovl12_05_8004A0C0(temp_v0);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80046990(void) {
    f32 sp70;
    f32 sp5C;
    f32 sp58;
    UnkStructA *temp_s1;
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    UnkStructA_40 *temp_v0_6;
    UnkStructA_40 *temp_v0_7;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    s32 var_s1;

    func_ovl12_05_8004A218(func_ovl12_05_8004A3B8(0x10) + 1);
    temp_s1 = func_ovl12_05_8004A220();
    temp_v0 = func_ovl12_05_8004A0D0(0x11F, 0x01080000, 0xD0, 0);
    temp_v0->unk40->unk10 = temp_s1->unk40->unk10;
    temp_v0->unk40->unk14 = temp_s1->unk40->unk14 + 100.0f;
    temp_v0->unk40->unk18 = temp_s1->unk40->unk18;
    temp_fs0 = (f32) (func_ovl12_05_8004A3B0() * 360.0);
    temp_fs1 = (f32) ((func_ovl12_05_8004A3B0() * 200.0) + 600.0);
    temp_ft5 = func_ovl12_05_8004A3A0(temp_fs0) * temp_fs1;
    sp70 = temp_ft5;
    temp_fs4 = func_ovl12_05_8004A3A8(temp_fs0) * temp_fs1;
    temp_fs5 = (f32) ((func_ovl12_05_8004A3B0() * 10.0) + 10.0);
    sp5C = (f32) ((func_ovl12_05_8004A3B0() * 10.0) + 10.0);
    sp58 = (f32) ((func_ovl12_05_8004A3B0() * 10.0) + 10.0);
    temp_v0->unk40->unk2C = (f32) (func_ovl12_05_8004A3B0() + 1.0);
    temp_v0->unk40->unk36 = 0xFA;
    var_s1 = 0;
    do {
        temp_v0_2 = temp_v0->unk40;
        temp_v0_2->unk10 += temp_ft5 / 90.0f;
        temp_v0_3 = temp_v0->unk40;
        temp_v0_3->unk14 += temp_fs4 / 90.0f;
        temp_v0_4 = temp_v0->unk40;
        temp_fv0 = temp_v0_4->unk1C + temp_fs5;
        if (temp_fv0 >= 360.0f) {
            temp_v0_4->unk1C = temp_fv0 - 360.0f;
        } else {
            if (temp_fv0 < 0.0f) {
                var_fv1 = temp_fv0 + 360.0f;
            } else {
                var_fv1 = temp_fv0;
            }
            temp_v0_4->unk1C = var_fv1;
        }
        temp_v0_5 = temp_v0->unk40;
        temp_fv0_2 = temp_v0_5->unk20 + sp5C;
        if (temp_fv0_2 >= 360.0f) {
            temp_v0_5->unk20 = temp_fv0_2 - 360.0f;
        } else {
            if (temp_fv0_2 < 0.0f) {
                var_fv1_2 = temp_fv0_2 + 360.0f;
            } else {
                var_fv1_2 = temp_fv0_2;
            }
            temp_v0_5->unk20 = var_fv1_2;
        }
        temp_v0_6 = temp_v0->unk40;
        temp_fv0_3 = temp_v0_6->unk24 + sp58;
        if (temp_fv0_3 >= 360.0f) {
            temp_v0_6->unk24 = temp_fv0_3 - 360.0f;
        } else {
            if (temp_fv0_3 < 0.0f) {
                var_fv1_3 = temp_fv0_3 + 360.0f;
            } else {
                var_fv1_3 = temp_fv0_3;
            }
            temp_v0_6->unk24 = var_fv1_3;
        }
        temp_v0_7 = temp_v0->unk40;
        temp_v0_7->unk36 = (s16) (s32) ((f32) temp_v0_7->unk36 - 2.7222223f);
        func_ovl12_05_8004A240();
        var_s1 += 1;
    } while (var_s1 != 0x5A);
    func_ovl12_05_8004A0C0(temp_v0);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_800466C4(void) {
    UnkStructA *temp_s2;
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 var_s2;

    temp_s2 = func_ovl12_05_8004A220();
    temp_v0 = func_ovl12_05_80049D88(0xA, 0);
    temp_v0->unkC |= 0x1080;
    temp_v0->unk36 = 0xFA;
    temp_v0->unk10 = temp_s2->unk40->unk10;
    temp_v0->unk14 = temp_s2->unk40->unk14 + 70.0f;
    temp_v0->unk28 = 0.1f;
    temp_v0->unk2C = 0.1f;
    temp_v0->unk30 = 0.1f;
    temp_v0->unk1C = 90.0f;
    temp_v0->unk18 = temp_s2->unk40->unk18;
    temp_v0_2 = func_ovl12_05_80049D88(0x11A, 0);
    temp_v0_2->unkC |= 0x80C0;
    temp_v0_2->unk36 = 0xB4;
    temp_v0_2->unk10 = temp_s2->unk40->unk10;
    temp_v0_2->unk14 = temp_s2->unk40->unk14 + 70.0f;
    temp_v0_2->unk18 = temp_s2->unk40->unk18;
    temp_v0->unk2C = 0.1f;
    temp_v0->unk30 = 0.1f;
    temp_v0_2->unk28 = 0.1f;
    func_ovl12_05_80049DB0(temp_v0_2, 2);
    func_ovl12_05_80049DB8(temp_v0_2, 0x11B, 0, 0);
    func_ovl12_05_80049DB8(temp_v0_2, 0x11B, 1, 1);
    var_s2 = 0;
    do {
        temp_v0->unk28 += 1.0f;
        temp_fv0 = temp_v0->unk28;
        temp_v0->unk30 = temp_fv0;
        temp_v0->unk2C = temp_fv0;
        temp_v0->unk28 = temp_fv0;
        temp_v0_2->unk28 += 0.33333334f;
        temp_fv0_2 = temp_v0_2->unk28;
        temp_v0_2->unk30 = temp_fv0_2;
        temp_v0_2->unk2C = temp_fv0_2;
        temp_v0_2->unk28 = temp_fv0_2;
        temp_v0->unk36 = (s16) (s32) ((f32) temp_v0->unk36 - 8.333333f);
        if (temp_v0->unk36 < 0) {
            temp_v0->unk36 = 0;
        }
        temp_v0_2->unk36 = (s16) (s32) ((f32) temp_v0_2->unk36 - 6.0f);
        if (temp_v0_2->unk36 < 0) {
            temp_v0_2->unk36 = 0;
        }
        func_ovl12_05_8004A240();
        var_s2 += 1;
    } while (var_s2 != 0x1E);
    func_ovl12_05_80049D90(temp_v0);
    func_ovl12_05_80049D90(temp_v0_2);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_800465E4(void) {
    s32 var_s0;

    func_ovl12_05_8004A810(D_ovl12_05_8004AC54->unk40, 0, 0, 0x1F, 0.7f);
    func_ovl12_05_8004A218(0x14);
    var_s0 = 0x3C;
    do {
        func_ovl12_05_8004A810(D_ovl12_05_8004AC54->unk40, 0, 0, 0x1F, ((f32) var_s0 / 60.0f) * 0.7f);
        func_ovl12_05_8004A240();
        var_s0 -= 1;
    } while (var_s0 != 0);
    func_ovl12_05_8004A820(D_ovl12_05_8004AC54->unk40);
    func_ovl12_05_8004A208();
}

void func_ovl12_05_80046560(void) {
    func_ovl12_05_8004A200(D_ovl12_05_8004AC64);
    D_ovl12_05_8004AC64 = func_ovl12_05_8004A1F8(func_ovl12_05_800465E4, NULL, 0, 0, 0x130);
    func_ovl12_05_8004A218(0x50);
    D_ovl12_05_8004AC64 = func_ovl12_05_8004A1F8(func_ovl12_05_80048C3C, NULL, 0, 0, 0x130);
    func_ovl12_05_8004A208();
}

/* twin of 12_04:80043358 (src/overlays/ovl_12_04/253A10.c) */
void func_ovl12_05_80046538(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl12_05_8004AC30.unk0 = arg0;
    D_ovl12_05_8004AC30.unk4 = arg1;
    D_ovl12_05_8004AC30.unk8 = arg2;
    D_ovl12_05_8004AC30.unkC = arg3;
    D_ovl12_05_8004AC30.unk10 = arg4;
}

/* twin of 12_03:800437FC (nonmatching/overlays/ovl_12_03/250B70.c) */
void func_ovl12_05_800464F0(void) {
    func_ovl12_05_800498A8(D_ovl12_05_8004AC30.unk4, 3, 4.0f, D_ovl12_05_8004AC30.unk10, 0, 1, 1);
}

/* twin of 12_03:800439A4 (nonmatching/overlays/ovl_12_03/250B70.c) */
void func_ovl12_05_800463D8(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl12_05_800498B8();
    switch (D_ovl12_05_8004AC30.unk8) {
        case 0:
            angle = 0.0f;
            break;
        case 0x80:
            angle = 180.0f;
            break;
        case 0xC0:
            angle = 90.0f;
            break;
        case 0x40:
            angle = 270.0f;
            break;
        case 1:
        default:
            angle = 360.0f;
            break;
    }
    if (angle != 360.0f) {
        func_ovl12_05_80049F08(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl12_05_8004AC30.unkC;
        func_ovl12_05_80049F10(&sp1C, NULL, NULL);
        func_ovl12_05_80049F08(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl12_05_800498A0(D_ovl12_05_8004AC30.unk4);
}

/* twin of 17_09:80044ACC (nonmatching/overlays/ovl_17_09/2B8D20.c) */
void func_ovl12_05_80046390(f32 arg0) {
    f32 sp1C;

    func_ovl12_05_80049F10(&sp1C, NULL, NULL);
    func_ovl12_05_80049F08(sp1C + arg0, 32768.0f, 32768.0f);
}

/* twin of 12_04:80043068 (src/overlays/ovl_12_04/253A10.c) */
void func_ovl12_05_80046348(void) {
    func_ovl12_05_80046340();
    D_ovl12_05_8004AC0C[0] = func_ovl12_05_80049888(); func_ovl12_05_80049868(&D_ovl12_05_8004AC00); func_ovl12_05_80049890(D_ovl12_05_8004AC0C[0], D_ovl12_05_8004ABF0);
}

static void func_ovl12_05_80046340(void) {
}

/* twin of 12_03:80043040 (nonmatching/overlays/ovl_12_03/250B70.c) */
void func_ovl12_05_80046320(void) {
    func_ovl12_05_80046318();
    func_ovl12_05_800498F0(1);
}

static void func_ovl12_05_80046318(void) {
}

/* twin of 12_03:80044380 (nonmatching/overlays/ovl_12_03/250B70.c) */
void func_ovl12_05_80046258(UnkStructA *arg0) {
    func_ovl12_05_8004A218(10);
    func_ovl12_05_80049730(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl12_05_8004A218(60);
}

void func_ovl12_05_80045B00(void) {
    UnkStructA *temp_v0_2;
    UnkStructC *temp_v0_3;
    s32 temp_v0;

    if ((D_ovl12_05_8004AC4C == 0x10) || (D_ovl12_05_8004AC4C == 0x11) || (D_ovl12_05_8004AC4C == 0x1A) || (D_ovl12_05_8004AC4C == 0x1C)) {
        func_ovl12_05_80045A70();
        func_ovl12_05_800496C0(0x2E3);
    } else {
        func_ovl12_05_800496C0(0x2E4);
    }
    func_ovl12_05_80049858();
    func_ovl12_05_80049820(0);
    temp_v0 = D_ovl12_05_8004AC4C;
    if ((temp_v0 == 0x10) || (temp_v0 == 0x12) || (temp_v0 == 0x13) || (temp_v0 == 0x1A) || (temp_v0 == 0x1E)) {
        func_ovl12_05_80044488();
    }
    if ((temp_v0 == 0x10) || (temp_v0 == 0x11) || (temp_v0 == 0x1A) || (temp_v0 == 0x1C)) {
        temp_v0_2 = func_ovl12_05_8004A0D0(0x346, 0x01080000, 0xC0, 0);
        D_ovl12_05_8004AC54 = temp_v0_2;
        temp_v0_2->unk40->unk10 = 2350.0f;
        D_ovl12_05_8004AC54->unk40->unk14 = 400.0f;
        D_ovl12_05_8004AC78 = D_ovl12_05_8004AC54->unk40->unk14;
        D_ovl12_05_8004AC7C = 1.0f;
        D_ovl12_05_8004AC54->unk40->unk18 = 1030.0f;
        func_ovl12_05_8004A0E0(D_ovl12_05_8004AC54);
        D_ovl12_05_8004AC58 = func_ovl12_05_8004A1F8(func_ovl12_05_80048F04, NULL, 0, 0, 0x130);
    }
    temp_v0_3 = func_ovl12_05_8004A280(0x357);
    D_ovl12_05_8004AC5C = temp_v0_3;
    func_ovl12_05_8004A290(temp_v0_3, 0x20000000);
    D_ovl12_05_8004AC5C->unk40 = 0.5f;
    D_ovl12_05_8004AC5C->unk44 = D_ovl12_05_8004AC5C->unk40 * 0.75f;
    D_ovl12_05_8004AC5C->unk3C = D_ovl12_05_8004AC5C->unk4C * 0.25f;
    D_ovl12_05_8004AC50 = 1;
    func_ovl12_05_80049790(func_ovl12_05_80048EC8);
    func_ovl12_05_800496D8(-1000.0f);
    D_ovl12_05_8004AC6C = 0;
    D_ovl12_05_8004AC70 = 0;
    func_ovl12_05_8004A418();
}

void func_ovl12_05_80045A70(void) {
    D_ovl12_05_8004AC44 = func_ovl12_05_8004A0F0(0x2DE, 0x50, 0.0f, 0.0f, 0.0f);
    if ((D_ovl12_05_8004AC4C == 0x10) || (D_ovl12_05_8004AC4C == 0x1A)) {
        func_ovl12_05_8004A0A8(D_ovl12_05_8004AC44, 0x01080000);
        D_ovl12_05_8004AC44->unk40->unk36 = 0;
        return;
    }
    func_ovl12_05_8004A0A8(D_ovl12_05_8004AC44, 0x01000000);
}

void func_ovl12_05_80045954(void) {
    UnkStructA *sp24;
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_2;

    func_ovl12_05_80049860(0x17, 0, 0x10);
    func_ovl12_05_800498A0(0);
    func_ovl12_05_8004A828(1, 7, 0x17, 0, 5);
    func_ovl12_05_8004A848(0);
    temp_v1 = func_ovl12_05_800498E8(1)->unk40;
    temp_v1->unk10 += 50.0f;
    func_ovl12_05_80049918(1);
    func_ovl12_05_80049898(1);
    func_ovl12_05_80049918(0);
    temp_v0 = func_ovl12_05_800498E8(0);
    sp24 = temp_v0;
    temp_v1_2 = temp_v0->unk40;
    temp_v1_2->unk10 += 50.0f;
    func_ovl12_05_800498B8();
    func_ovl12_05_80049F50(0x1F);
    func_ovl12_05_80049ED8(0);
    temp_v0_2 = sp24->unk40;
    func_ovl12_05_80049EE8(temp_v0_2->unk10, temp_v0_2->unk14, temp_v0_2->unk18);
    func_ovl12_05_80049EF8(1369.0f, 663.0f, 1308.0f);
    func_ovl12_05_80049830(0x7E, 0x11);
    func_ovl12_05_80049898(1);
}

void func_ovl12_05_80045844(void) {
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_2;

    func_ovl12_05_80045834();
    func_ovl12_05_8004583C();
    func_ovl12_05_8004A828(1, 7, 0x17, 0, 7);
    func_ovl12_05_80049860(0x17, 0, 0xE);
    func_ovl12_05_800498A0(0);
    temp_v1 = func_ovl12_05_800498E8(0)->unk40;
    temp_v1->unk10 += 50.0f;
    temp_v1_2 = func_ovl12_05_800498E8(1)->unk40;
    temp_v1_2->unk10 += 50.0f;
    func_ovl12_05_800498B8();
    func_ovl12_05_80049F50(0xF);
    D_ovl12_05_8004AC78 = 600.0f;
    D_ovl12_05_8004AC7C = 0.3f;
    D_ovl12_05_8004AC80 = 0.3f;
    D_ovl12_05_8004AC68 = func_ovl12_05_8004A1F8(func_ovl12_05_800485A0, NULL, 0, 0, 0x130);
    D_ovl12_05_8004AC64 = func_ovl12_05_8004A1F8(func_ovl12_05_80048C3C, NULL, 0, 0, 0x130);
}

static void func_ovl12_05_8004583C(void) {
}

static void func_ovl12_05_80045834(void) {
}

/* twin of 10_13:8004621C (nonmatching/overlays/ovl_10_13/2439F0.c) */
void func_ovl12_05_80045754(void) {
    switch (D_ovl12_05_8004AC4C) {
    case 16:
    case 26:
        func_ovl12_05_8004A1F8(func_ovl12_05_80047F94, NULL, 0, 0, 0x130);
        return;
    case 18:
        func_ovl12_05_8004A1F8(func_ovl12_05_80047F68, NULL, 0, 0, 0x130);
        return;
    case 28:
        func_ovl12_05_8004A1F8(func_ovl12_05_80047E90, NULL, 0, 0, 0x130);
        return;
    case 30:
        func_ovl12_05_8004A1F8(func_ovl12_05_80047DA4, NULL, 0, 0, 0x130);
        /* fallthrough */
    default:
        return;
    }
}

/* twin of 10_13:80046168 (nonmatching/overlays/ovl_10_13/2439F0.c) */
void func_ovl12_05_800456A0(void) {
    switch (D_ovl12_05_8004AC4C) {
    case 16:
    case 18:
    case 26:
    case 28:
    case 30:
        if (D_ovl12_05_8004AC50 != 0) {
            do {
                func_ovl12_05_8004A240();
            } while (D_ovl12_05_8004AC50 != 0);
        }
        func_ovl12_05_80049898(0);
        break;
    }
    if ((D_ovl12_05_8004AC4C == 0x10) || (D_ovl12_05_8004AC4C == 0x11) || (D_ovl12_05_8004AC4C == 0x13)) {
        func_ovl12_05_8004A790(0x23);
    }
}

static void func_ovl12_05_80044534(void) {
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    s32 sp38[4] = { 0x290, 0x291, 0x292, 0x293 };
    UnkStructA_40 *sp48[8];
    UnkStructA *temp_s4;
    UnkStructA *temp_s6;
    UnkStructA *temp_v0_3;
    UnkStructA_40 **temp_s0_2;
    UnkStructA_40 **var_s0_2;
    UnkStructA_40 **var_v1;
    UnkStructA_40 *temp_t0;
    UnkStructA_40 *temp_t0_2;
    UnkStructA_40 *temp_t0_3;
    UnkStructA_40 *temp_v0_10;
    UnkStructA_40 *temp_v0_5;
    UnkStructA_40 *temp_v0_6;
    UnkStructA_40 *temp_v0_7;
    UnkStructA_40 *temp_v0_8;
    UnkStructA_40 *temp_v0_9;
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_10;
    UnkStructA_40 *temp_v1_11;
    UnkStructA_40 *temp_v1_12;
    UnkStructA_40 *temp_v1_13;
    UnkStructA_40 *temp_v1_14;
    UnkStructA_40 *temp_v1_15;
    UnkStructA_40 *temp_v1_16;
    UnkStructA_40 *temp_v1_2;
    UnkStructA_40 *temp_v1_3;
    UnkStructA_40 *temp_v1_4;
    UnkStructA_40 *temp_v1_5;
    UnkStructA_40 *temp_v1_6;
    UnkStructA_40 *temp_v1_7;
    UnkStructA_40 *temp_v1_8;
    UnkStructA_40 *temp_v1_9;
    UnkStructA_40_48_4 *temp_v0_4;
    UnkStruct_ovl12_05_800497F8 *temp_v0;
    UnkStruct_ovl12_05_8004A840 *temp_s0;
    UnkStruct_ovl12_05_8004A840 *temp_v0_2;
    UnkStruct_ovl12_05_8004A840 *var_s0;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fs1;
    f32 var_fs3;
    f32 var_fv0;
    s32 temp_a0;
    s32 temp_s2;
    s32 var_s1;
    s32 var_s1_10;
    s32 var_s1_11;
    s32 var_s1_12;
    s32 var_s1_13;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s1_8;
    s32 var_s1_9;
    s32 var_t6;
    s32 var_v0;
    void *temp_v0_11;

    temp_v0 = func_ovl12_05_800497F8();
    D_ovl12_05_8004AC74 = temp_v0->unk30;
    func_ovl12_05_8004A848(0);
    func_ovl12_05_80049F50(0x1F);
    func_ovl12_05_80049938(0, 0);
    func_ovl12_05_80049938(1, 0);
    func_ovl12_05_80049918(1);
    func_ovl12_05_80049898(1);
    func_ovl12_05_80049918(0);
    func_ovl12_05_80049898(1);
    func_ovl12_05_8004A688();
    func_ovl12_05_8004A268(0x70, 0x70, 0);
    temp_s6 = func_ovl12_05_800498E8(0);
    temp_s4 = func_ovl12_05_800498E8(1);
    func_ovl12_05_80049DD0(temp_s6->unk40, 0, 0);
    func_ovl12_05_80049DD0(temp_s6->unk40, -1, 1);
    func_ovl12_05_8004A0B0(temp_s4, 0x80000);
    if (D_ovl12_05_8004AC4C == 0x1C) {
        temp_v1 = temp_s4->unk40;
        func_ovl12_05_80049EE8(temp_v1->unk10, temp_v1->unk14 + 50.0f, temp_v1->unk18);
    } else {
        temp_v0_2 = func_ovl12_05_8004A840(1);
        var_s0 = temp_v0_2;
        func_ovl12_05_8004A210(temp_v0_2->unkA0.h.lo, -1);
    }
    if ((D_ovl12_05_8004AC4C != 0x1C) && !(var_s0->unk124 & 8)) {
        temp_s0 = func_ovl12_05_8004A840(1);
        var_v0 = 0x1388;
        if (temp_v0->unk10 == 0) {
            var_v0 = 0x1F40;
        }
        if (var_v0 >= D_ovl12_05_8004AC74) {
            sp68 = temp_s0->unk1C->unk40->unk10;
            sp6C = temp_s0->unk1C->unk40->unk14;
            sp70 = temp_s0->unk1C->unk40->unk18;
            func_ovl12_05_8004A428((Vec3f *) &sp68);
            temp_s0->unk124 |= 8;
            temp_v0->unk2C += 1;
        }
    }
    if (D_ovl12_05_8004AC4C != 0x1C) {
        func_ovl12_05_80049848(0x32);
        func_ovl12_05_8004A798();
    }
    temp_v1_2 = temp_s4->unk40;
    temp_t0 = D_ovl12_05_8004AC54->unk40;
    temp_fs3 = temp_t0->unk10 - temp_v1_2->unk10;
    temp_fs2 = temp_t0->unk18 - temp_v1_2->unk18;
    func_ovl12_05_8004A780(0x1C9);
    var_s1 = 0;
    do {
        temp_s4->unk40->unk14 = func_ovl12_05_8004A3A8(90.0f - (((f32) var_s1 / 60.0f) * 90.0f)) * 670.0f;
        temp_v1_3 = temp_s4->unk40;
        if (temp_v1_3->unk14 > 670.0f) {
            temp_v1_3->unk14 = 670.0f;
        }
        temp_s4->unk40->unk10 += temp_fs3 / 60.0f;
        temp_v1_4 = temp_s4->unk40;
        temp_v1_4->unk18 += temp_fs2 / 60.0f;
        temp_s6->unk40->unk20 = func_ovl12_05_800444D4(temp_s6->unk40, temp_s4->unk40);
        temp_s4->unk40->unk20 = func_ovl12_05_800444D4(temp_s4->unk40, temp_s6->unk40);
        func_ovl12_05_8004A240();
        var_s1 += 1;
    } while (var_s1 < 0x3C);
    temp_s4->unk40->unk20 = 90.0f;
    temp_s4->unk40->unk1C = 25.0f;
    temp_s6->unk40->unk10 = 2900.0f;
    temp_s6->unk40->unk14 = 0.0f;
    temp_s6->unk40->unk18 = 1050.0f;
    temp_s6->unk40->unk20 = 270.0f;
    temp_v1_5 = temp_s4->unk40;
    func_ovl12_05_80049EE8(temp_v1_5->unk10, temp_v1_5->unk14 + 50.0f, temp_v1_5->unk18);
    func_ovl12_05_80049F08(90.0f, 20.0f, 800.0f);
    temp_v0_3 = func_ovl12_05_8004A0D0(0x320, 0x01000000, 0xC0, 0);
    temp_s2 = func_ovl12_05_80049E18(temp_v0_3->unk40, 0x10);
    var_s1_2 = 0;
    temp_a0 = temp_s2;
    do {
        func_ovl12_05_80049E20(temp_a0, var_s1_2, 0x322);
        func_ovl12_05_80049E30(temp_s2, var_s1_2, var_s1_2);
        var_s1_2 += 1;
    } while (var_s1_2 < 0x10);
    temp_v0_3->unk40->unk10 = temp_s4->unk40->unk10;
    temp_v0_3->unk40->unk14 = temp_s4->unk40->unk14;
    temp_v0_3->unk40->unk18 = temp_s4->unk40->unk18 - 800.0f;
    temp_v0_3->unk40->unk20 = 0.0f;
    func_ovl12_05_8004A0E0(temp_v0_3);
    func_ovl12_05_80049DD0(temp_v0_3->unk40, 0x19, 0);
    temp_v0_3->unk40->unk48->unk4->unk4 = 11.9f;
    func_ovl12_05_8004A218(0xA);
    func_ovl12_05_8004A218(0x3C);
    func_ovl12_05_8004A780(0x25C);
    func_ovl12_05_80049DD0(temp_s4->unk40, 0x17, 0);
    func_ovl12_05_80049DD0(temp_s4->unk40, -1, 1);
    temp_v0_4 = temp_s4->unk40->unk48->unk4;
    temp_v0_4->unk8 |= 0x20;
    sp80 = temp_s4->unk40->unk10 + 10.0f;
    sp84 = temp_s4->unk40->unk14 + 50.0f;
    sp88 = temp_s4->unk40->unk18 + 55.0f;
    sp74 = temp_s4->unk40->unk10 + 10.0f;
    sp78 = temp_s4->unk40->unk14 + 50.0f;
    sp7C = temp_s4->unk40->unk18 - 55.0f;
    func_ovl12_05_8004A780(0x25E);
    var_s1_3 = 0;
    do {
        func_ovl12_05_8004A1F8(func_ovl12_05_80047B64, &sp80, 0, 0, 0x130);
        func_ovl12_05_8004A1F8(func_ovl12_05_80047B64, &sp74, 0, 0, 0x130);
        func_ovl12_05_8004A218(4);
        var_s1_3 += 1;
    } while (var_s1_3 < 4);
    func_ovl12_05_8004A218(0x3C);
    temp_v0_5 = func_ovl12_05_80049D88(0x2C7, 0);
    temp_v0_5->unkC |= 0x80;
    temp_v0_5->unk36 = 0x80;
    temp_v0_5->unk10 = sp80;
    temp_v0_5->unk14 = sp84;
    temp_v0_5->unk28 = 0.5f;
    temp_v0_5->unk2C = 0.5f;
    temp_v0_5->unk30 = 0.5f;
    temp_v0_5->unk18 = sp88;
    temp_v0_6 = func_ovl12_05_80049D88(0x2C7, 0);
    temp_v0_6->unkC |= 0x80;
    temp_v0_6->unk36 = 0xC8;
    temp_v0_6->unk10 = sp74;
    var_fs1 = 0.0f;
    temp_v0_6->unk14 = sp78;
    temp_v0_6->unk28 = 0.5f;
    temp_v0_6->unk2C = 0.5f;
    temp_v0_6->unk30 = 0.5f;
    temp_v0_6->unk18 = sp7C;
    var_fs3 = 0.5f;
    var_s1_4 = 0;
    do {
        temp_fs0 = (func_ovl12_05_8004A3A0(var_fs1) * 0.5f) + var_fs3;
        temp_v0_5->unk30 = temp_fs0;
        temp_v0_5->unk2C = temp_fs0;
        temp_v0_5->unk28 = temp_fs0;
        temp_fv1 = var_fs1 + 0.5f;
        temp_fs0_2 = (func_ovl12_05_8004A3A0(var_fs1) * 0.5f) + var_fs3;
        temp_v0_6->unk30 = temp_fs0_2;
        temp_v0_6->unk2C = temp_fs0_2;
        temp_v0_6->unk28 = temp_fs0_2;
        if (temp_fv1 >= 360.0f) {
            var_fs1 = temp_fv1 - 360.0f;
        } else {
            if (temp_fv1 < 0.0f) {
                var_fv0 = temp_fv1 + 360.0f;
            } else {
                var_fv0 = temp_fv1;
            }
            var_fs1 = var_fv0;
        }
        var_fs3 += 0.004166667f;
        func_ovl12_05_8004A240();
        var_s1_4 += 1;
    } while (var_s1_4 < 0x78);
    temp_v1_6 = temp_s4->unk40;
    func_ovl12_05_80049EE8(temp_v1_6->unk10, temp_v1_6->unk14 + 50.0f, temp_v1_6->unk18);
    func_ovl12_05_80049ED8(0);
    temp_v0_7 = temp_s6->unk40;
    func_ovl12_05_80049EF8(temp_v0_7->unk10 + 700.0f, temp_v0_7->unk14 - 330.0f, temp_v0_7->unk18);
    func_ovl12_05_8004A218(0x1E);
    temp_v1_7 = temp_v0_3->unk40;
    func_ovl12_05_80049EE8(temp_v1_7->unk10, temp_v1_7->unk14 + 50.0f, temp_v1_7->unk18);
    func_ovl12_05_80049EF8(2977.0f, 624.0f, 1081.0f);
    func_ovl12_05_8004A780(0x280);
    var_s1_5 = 0;
    do {
        temp_v1_8 = temp_v0_3->unk40;
        temp_v1_8->unk18 += 35.0f;
        temp_v1_9 = temp_v0_3->unk40;
        func_ovl12_05_80049EE8(temp_v1_9->unk10, temp_v1_9->unk14 + 50.0f, temp_v1_9->unk18);
        func_ovl12_05_8004A240();
        var_s1_5 += 1;
    } while (var_s1_5 < 0x14);
    func_ovl12_05_80049D90(temp_v0_5);
    func_ovl12_05_80049D90(temp_v0_6);
    func_ovl12_05_8004A780(0x2E3);
    temp_v1_10 = temp_s4->unk40;
    func_ovl12_05_8004A648(0, temp_v1_10->unk10, temp_v1_10->unk14, temp_v1_10->unk18 - 50.0f, 0);
    var_s1_6 = 0;
    do {
        temp_v1_11 = temp_s4->unk40;
        temp_v1_11->unk18 += 35.0f;
        func_ovl12_05_8004A240();
        var_s1_6 += 1;
    } while (var_s1_6 < 0x14);
    temp_s4->unk40->unk10 = 2000.0f;
    temp_s4->unk40->unk14 = 0.0f;
    temp_s4->unk40->unk18 = 1340.0f;
    temp_s4->unk40->unk20 = 135.0f;
    var_s1_7 = 0;
    temp_s4->unk40->unk1C = 0.0f;
    temp_s4->unk40->unk24 = 0.0f;
    do {
        temp_v1_12 = temp_v0_3->unk40;
        temp_v1_12->unk14 -= 4.6666665f;
        func_ovl12_05_8004A240();
        var_s1_7 += 1;
    } while (var_s1_7 < 0x1E);
    temp_v1_13 = temp_v0_3->unk40;
    func_ovl12_05_80049EE8(temp_v1_13->unk10, temp_v1_13->unk14 + 80.0f, temp_v1_13->unk18 + 50.0f);
    func_ovl12_05_80049ED8(1);
    func_ovl12_05_80049F08(90.0f, 10.0f, 800.0f);
    func_ovl12_05_80049DD0(temp_v0_3->unk40, 0x1A, 0);
    func_ovl12_05_8004A0A8(temp_v0_3, 0x04000000);
    func_ovl12_05_8004A218(0xE);
    func_ovl12_05_8004A1F8(func_ovl12_05_800479B0, temp_v0_3, 0, 0, 0x130);
    func_ovl12_05_8004A218(0xF);
    func_ovl12_05_8004A1F8(func_ovl12_05_800479B0, temp_v0_3, 0, 0, 0x130);
    func_ovl12_05_8004A218(0x10);
    func_ovl12_05_8004A1F8(func_ovl12_05_800479B0, temp_v0_3, 0, 0, 0x130);
    func_ovl12_05_8004A218(0xD);
    func_ovl12_05_8004A1F8(func_ovl12_05_800479B0, temp_v0_3, 0, 0, 0x130);
    func_ovl12_05_8004A218(0x14);
    func_ovl12_05_8004A1F8(func_ovl12_05_800479B0, temp_v0_3, 0, 0, 0x130);
    if (D_ovl12_05_8004AC4C == 0x1C) {
        func_ovl12_05_8004A8F8();
        D_ovl12_05_8004AC50 = 0;
        func_ovl12_05_8004A208();
    }
    temp_v0_3->unk6C = 16.333334f;
    temp_v0_3->unk68 = 0.0f;
    temp_v0_3->unk70 = 1.6333334f;
    var_s1_8 = 0;
loop_36:
    temp_v1_14 = temp_v0_3->unk40;
    temp_v1_14->unk18 -= 13.333333f;
    func_ovl12_05_8004A128(temp_v0_3);
    if (temp_v0_3->unk6C == 0.0f) {

    } else {
        func_ovl12_05_8004A240();
        var_s1_8 += 1;
        if (var_s1_8 < 0x1E) {
            goto loop_36;
        }
    }
    var_s1_9 = 0;
    temp_v0_3->unk40->unk14 = 0.0f;
    do {
        func_ovl12_05_8004A240();
        var_s1_9 += 1;
        D_ovl12_05_8004AC7C -= 0.0050000004f;
    } while (var_s1_9 < 0x3C);
    func_ovl12_05_8004A200(D_ovl12_05_8004AC58);
    temp_t0_2 = D_ovl12_05_8004AC54->unk40;
    func_ovl12_05_80049EE8(temp_t0_2->unk10, temp_t0_2->unk14, temp_t0_2->unk18);
    func_ovl12_05_80049F08(32768.0f, 30.0f, 2280.0f);
    D_ovl12_05_8004AC80 = 0.8f;
    func_ovl12_05_8004A780(0x294);
    func_ovl12_05_8004A218(0x3C);
    var_s1_10 = 0;
    do {
        if (!(var_s1_10 & 1)) {
            func_ovl12_05_8004A780(sp38[var_s1_10 >> 1]);
        }
        temp_s0_2 = &sp48[var_s1_10];
        temp_v0_8 = func_ovl12_05_80049D88(0x1CB, 0);
        *temp_s0_2 = temp_v0_8;
        temp_v0_8->unkC |= 0x80;
        (*temp_s0_2)->unk36 = 0xC8;
        (*temp_s0_2)->unk10 = D_ovl12_05_8004AC54->unk40->unk10;
        (*temp_s0_2)->unk14 = D_ovl12_05_8004AC54->unk40->unk14;
        (*temp_s0_2)->unk18 = D_ovl12_05_8004AC54->unk40->unk18;
        (*temp_s0_2)->unk1C = (f32) (func_ovl12_05_8004A3B0() * 350.0);
        (*temp_s0_2)->unk20 = (f32) (func_ovl12_05_8004A3B0() * 350.0);
        (*temp_s0_2)->unk24 = (f32) (func_ovl12_05_8004A3B0() * 350.0);
        (*temp_s0_2)->unk30 = 0.3f;
        temp_v0_9 = *temp_s0_2;
        temp_v0_9->unk28 = temp_v0_9->unk30;
        (*temp_s0_2)->unk2C = 20.0f;
        func_ovl12_05_8004A218(func_ovl12_05_8004A3B8(0x32) + 8);
        var_s1_10 += 1;
    } while (var_s1_10 < 8);
    func_ovl12_05_8004A218(0x1E);
    func_ovl12_05_80049F08(32768.0f, 32768.0f, 650.0f);
    var_s1_11 = 0;
    do {
        func_ovl12_05_8004A240();
        var_s1_11 += 1;
        D_ovl12_05_8004AC80 -= 0.006666667f;
        if (D_ovl12_05_8004AC80 < 0.0f) {
            D_ovl12_05_8004AC80 = 0.0f;
        }
        for (var_v0 = 0; var_v0 < 8; var_v0++) {
            sp48[var_v0]->unk36 -= 1.6666666f;
            if (sp48[var_v0]->unk36 < 0) {
                sp48[var_v0]->unk36 = 0;
            }
        }
    } while (var_s1_11 < 0x78);
    func_ovl12_05_8004A820(D_ovl12_05_8004AC54->unk40);
    func_ovl12_05_8004A820(D_ovl12_05_8004AC84->unk40);
    func_ovl12_05_8004A218(0x1E);
    func_ovl12_05_8004A200(D_ovl12_05_8004AC64);
    for (var_v0 = 0; var_v0 < 8; var_v0++) {
        func_ovl12_05_80049D90(sp48[var_v0]);
    }
    func_ovl12_05_8004A780(0x295);
    func_ovl12_05_8004A780(0x297);
    func_ovl12_05_8004A510(0xFF, 0xFF, 0xFF, 8);
    func_ovl12_05_8004A4F0();
    func_ovl12_05_8004A0C0(D_ovl12_05_8004AC84);
    func_ovl12_05_8004A200(D_ovl12_05_8004AC68);
    func_ovl12_05_8004A780(0x299);
    var_s1_12 = 0;
    do {
        temp_t0_3 = D_ovl12_05_8004AC54->unk40;
        func_ovl12_05_8004A648(0x11, temp_t0_3->unk10, temp_t0_3->unk14, temp_t0_3->unk18, 0);
        var_s1_12 += 1;
    } while (var_s1_12 < 8);
    func_ovl12_05_8004A0C0(D_ovl12_05_8004AC54);
    func_ovl12_05_8004A500(0xFF, 0xFF, 0xFF, 8);
    func_ovl12_05_8004A4F0();
    func_ovl12_05_80044488();
    func_ovl12_05_8004A0A8(D_ovl12_05_8004AC48, 0x80000);
    func_ovl12_05_8004A0A8(D_ovl12_05_8004AC44, 0x80000);
    var_s1_13 = 0;
    do {
        temp_fv0 = func_ovl12_05_8004A3A0(((f32) var_s1_13 / 200.0f) * 90.0f);
        D_ovl12_05_8004AC48->unk40->unk36 = (s16) (s32) (temp_fv0 * 255.0f);
        D_ovl12_05_8004AC44->unk40->unk36 = (s16) (s32) ((1.0f - temp_fv0) * 255.0f);
        if (var_s1_13 == 0x50) {
            func_ovl12_05_80049EE8(2370.0f, 77.0f, 1040.0f);
            func_ovl12_05_80049F08(90.0f, 34.0f, 2006.0f);
        }
        func_ovl12_05_8004A240();
        var_s1_13 += 1;
    } while (var_s1_13 != 0xC8);
    func_ovl12_05_8004A0B0(D_ovl12_05_8004AC48, 0x80000);
    func_ovl12_05_8004A0C0(D_ovl12_05_8004AC44);
    func_ovl12_05_8004A218(0x1E);
    temp_v1_15 = temp_s4->unk40;
    func_ovl12_05_80049EE8(temp_v1_15->unk10, 100.0f, temp_v1_15->unk18);
    func_ovl12_05_80049F08(32768.0f, 20.0f, 800.0f);
    func_ovl12_05_8004A7C0(0x7F);
    func_ovl12_05_8004A790(0x10);
    func_ovl12_05_80049E10(0x337, 1);
    temp_v1_16 = temp_v0_3->unk40;
    func_ovl12_05_80049EE8(temp_v1_16->unk10, 100.0f, temp_v1_16->unk18);
    func_ovl12_05_80049F08(32768.0f, 20.0f, 800.0f);
    func_ovl12_05_80049E10(0x338, 1);
    func_ovl12_05_800497A0(0x7E, 0x12, 0);
loop_61:
    func_ovl12_05_8004A240();
    goto loop_61;
}

/* twin of 12_06:80043068 (nonmatching/overlays/ovl_12_06/25D670.c) */
/* A static: its callers pass `from` in a3 and `to` in t0.  Defined below
 * the handler, it still comes out here. */
static f32 func_ovl12_05_800444D4(UnkStructA_40 *from, UnkStructA_40 *to) {
    Vec3f a;
    Vec3f b;
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;

    a.x = from->unk10;
    a.y = from->unk14;
    a.z = from->unk18;
    b.x = to->unk10;
    b.y = to->unk14;
    b.z = to->unk18;
    func_ovl12_05_8004A038(&a.x, &b.x, &angle);
    return angle;
}

/* twin of 12_03:80043E68 (nonmatching/overlays/ovl_12_03/250B70.c) */
void func_ovl12_05_80044488(void) {
    UnkStructA *obj;

    func_ovl12_05_80044480();
    obj = func_ovl12_05_8004A0F0(0x2DD, 0x50, 0.0f, 0.0f, 0.0f);
    D_ovl12_05_8004AC48 = obj;
    func_ovl12_05_8004A0A8(obj, 0x01000000);
}

static void func_ovl12_05_80044480(void) {
}

static void func_ovl12_05_800434C8(void) {
    UnkStructA_40 *sp7C[6];
    s32 sp64;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    UnkStructA *temp_fp;
    UnkStructA *temp_s3;
    UnkStructA *temp_s6;
    UnkStructA *temp_v0_13;
    UnkStructA_40 **var_a1;
    UnkStructA_40 **var_s0;
    UnkStructA_40 *temp_a0;
    UnkStructA_40 *temp_a0_2;
    UnkStructA_40 *temp_a0_3;
    UnkStructA_40 *temp_a0_4;
    UnkStructA_40 *temp_a0_5;
    UnkStructA_40 *temp_a0_6;
    UnkStructA_40 *temp_v0_10;
    UnkStructA_40 *temp_v0_11;
    UnkStructA_40 *temp_v0_12;
    UnkStructA_40 *temp_v0_14;
    UnkStructA_40 *temp_v0_15;
    UnkStructA_40 *temp_v0_16;
    UnkStructA_40 *temp_v0_17;
    UnkStructA_40 *temp_v0_18;
    UnkStructA_40 *temp_v0_19;
    UnkStructA_40 *temp_v0_20;
    UnkStructA_40 *temp_v0_21;
    UnkStructA_40 *temp_v0_22;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    UnkStructA_40 *temp_v0_6;
    UnkStructA_40 *temp_v0_7;
    UnkStructA_40 *temp_v0_8;
    UnkStructA_40 *temp_v0_9;
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_2;
    UnkStructA_40 *temp_v1_3;
    UnkStructA_40 *temp_v1_4;
    UnkStructA_40 *temp_v1_5;
    UnkStructA_40 *temp_v1_6;
    UnkStruct_ovl12_05_800497F8 *temp_s0;
    UnkStruct_ovl12_05_8004A840 *temp_s1;
    UnkStruct_ovl12_05_8004A840 *temp_v0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    s16 temp_t9;
    s32 temp_s2;
    s32 var_a0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s1_8;
    s32 var_s1_9;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;

    if ((D_ovl12_05_8004AC4C == 0x12) || (D_ovl12_05_8004AC4C == 0x13) || (D_ovl12_05_8004AC4C == 0x1E)) {
        if (D_ovl12_05_8004AC4C != 0x1E) {
            func_ovl12_05_8004A688();
            func_ovl12_05_8004A6E8();
        }
        temp_fp = func_ovl12_05_800498E8(0);
        temp_s3 = func_ovl12_05_800498E8(1);
        temp_s6 = func_ovl12_05_800498E8(2);
        if (D_ovl12_05_8004AC4C == 0x1E) {
            func_ovl12_05_80049EE8(2350.0f, 100.0f, 1040.0f);
            func_ovl12_05_80049F08(0.0f, 43.0f, 2553.0f);
        }
        func_ovl12_05_80049F50(0x1F);
        func_ovl12_05_8004A848(0);
        func_ovl12_05_8004A218(0x1E);
        func_ovl12_05_8004A0B0(temp_fp, 0x0C040000);
        func_ovl12_05_8004A0B0(temp_s3, 0x0C040000);
        func_ovl12_05_8004A0B0(temp_s6, 0x0C040000);
        func_ovl12_05_80049918(2);
        func_ovl12_05_80049898(1);
        func_ovl12_05_80049958();
        func_ovl12_05_80049918(1);
        func_ovl12_05_80049898(1);
        func_ovl12_05_80049958();
        func_ovl12_05_80049918(0);
        func_ovl12_05_80049898(1);
        func_ovl12_05_80049958();
        func_ovl12_05_80049EE8(2350.0f, 100.0f, 1040.0f);
        func_ovl12_05_80049F08(0.0f, 43.0f, 2553.0f);
        temp_s0 = func_ovl12_05_800497F8();
        temp_v0 = func_ovl12_05_8004A840(2);
        temp_s1 = temp_v0;
        if ((D_ovl12_05_8004AC4C != 0x1E) && !(temp_v0->unk124 & 4) && (func_ovl12_05_80049970(2) > 0)) {
            sp54 = temp_s6->unk40->unk10;
            sp58 = temp_s6->unk40->unk14;
            sp5C = temp_s6->unk40->unk18;
            func_ovl12_05_8004A428((Vec3f *) &sp54);
            temp_s1->unk124 |= 4;
            temp_s0->unk2C += 1;
        }
        func_ovl12_05_8004A780(0x2B4);
        func_ovl12_05_80049FB8();
        func_ovl12_05_80049FD0(10.0f, 10.0f, 10.0f);
        func_ovl12_05_80049FC0(-1);
        func_ovl12_05_8004A218(0x1E);
        func_ovl12_05_8004A0A8(temp_fp, 0x80000);
        func_ovl12_05_8004A0A8(temp_s6, 0x80000);
        func_ovl12_05_8004A0A8(D_ovl12_05_8004AC48, 0x80000);
        temp_v1 = temp_fp->unk40;
        temp_v1->unkC |= 0x1000;
        temp_a0 = D_ovl12_05_8004AC48->unk40;
        temp_a0->unkC |= 0x1000;
        temp_v0_2 = temp_s6->unk40;
        temp_v0_2->unkC |= 0x1000;
        if (D_ovl12_05_8004AC4C != 0x1E) {
            func_ovl12_05_80049848(0x32);
            func_ovl12_05_8004A798();
        }
        var_s1 = 0;
        do {
            temp_v1_2 = temp_fp->unk40;
            temp_v1_2->unk36 = (s16) (s32) ((f32) temp_v1_2->unk36 - 2.125f);
            temp_v1_3 = temp_fp->unk40;
            if (temp_v1_3->unk36 < 0) {
                temp_v1_3->unk36 = 0;
            }
            temp_v0_3 = temp_s6->unk40;
            temp_v0_3->unk36 = (s16) (s32) ((f32) temp_v0_3->unk36 - 2.125f);
            temp_v0_4 = temp_s6->unk40;
            if (temp_v0_4->unk36 < 0) {
                temp_v0_4->unk36 = 0;
            }
            temp_a0_2 = D_ovl12_05_8004AC48->unk40;
            temp_a0_2->unk36 = (s16) (s32) ((f32) temp_a0_2->unk36 - 2.125f);
            temp_a0_3 = D_ovl12_05_8004AC48->unk40;
            if (temp_a0_3->unk36 < 0) {
                temp_a0_3->unk36 = 0;
            }
            func_ovl12_05_8004A240();
            var_s1 += 1;
        } while (var_s1 < 0x78);
        func_ovl12_05_8004A0B0(temp_fp, 0x01000000);
        func_ovl12_05_8004A0B0(temp_s6, 0x01000000);
        func_ovl12_05_8004A0B0(D_ovl12_05_8004AC48, 0x01000000);
        func_ovl12_05_80049FB8();
        D_ovl12_05_8004AC70 = 1;
        func_ovl12_05_8004A420();
        temp_s3->unk40->unk20 = 0.0f;
        temp_v0_5 = temp_s3->unk40;
        func_ovl12_05_80049EE8(temp_v0_5->unk10, temp_v0_5->unk14 + 100.0f, temp_v0_5->unk18);
        func_ovl12_05_80049F08(0.0f, 0.0f, 1000.0f);
        temp_v0_6 = temp_s3->unk40;
        temp_fs2 = temp_v0_6->unk10;
        temp_fs4 = temp_v0_6->unk14;
        temp_fs3 = temp_v0_6->unk18;
        temp_v0_7 = func_ovl12_05_80049D88(0x328, 0);
        sp7C[0] = temp_v0_7;
        func_ovl12_05_80049DA8(temp_v0_7, 0x37);
        sp7C[0]->unk10 = temp_fs2 + 30.0f;
        temp_fs1 = temp_fs4 + 80.0f;
        sp7C[0]->unk14 = temp_fs1;
        sp7C[0]->unk18 = temp_fs3;
        sp7C[0]->unkC |= 0x10080;
        sp7C[0]->unk36 = 0xFF;
        temp_v0_8 = func_ovl12_05_80049D88(0x328, 0);
        sp7C[1] = temp_v0_8;
        func_ovl12_05_80049DA8(temp_v0_8, 0x38);
        sp7C[1]->unk10 = temp_fs2 + 70.0f;
        sp7C[1]->unk14 = temp_fs1;
        sp7C[1]->unk18 = temp_fs3;
        sp7C[1]->unkC |= 0x10080;
        sp7C[1]->unk36 = 0xFF;
        temp_v0_9 = func_ovl12_05_80049D88(0x328, 0);
        sp7C[2] = temp_v0_9;
        func_ovl12_05_80049DA8(temp_v0_9, 0x39);
        sp7C[2]->unk10 = temp_fs2 + 60.0f;
        sp7C[2]->unk14 = temp_fs1;
        sp7C[2]->unk18 = temp_fs3;
        sp7C[2]->unkC |= 0x10080;
        sp7C[2]->unk36 = 0xFF;
        temp_v0_10 = func_ovl12_05_80049D88(0x328, 0);
        sp7C[3] = temp_v0_10;
        func_ovl12_05_80049DA8(temp_v0_10, 0x3C);
        sp7C[3]->unk10 = temp_fs2 - 30.0f;
        sp7C[3]->unk14 = temp_fs1;
        sp7C[3]->unk18 = temp_fs3;
        sp7C[3]->unkC |= 0x10080;
        sp7C[3]->unk36 = 0xFF;
        temp_v0_11 = func_ovl12_05_80049D88(0x328, 0);
        sp7C[4] = temp_v0_11;
        func_ovl12_05_80049DA8(temp_v0_11, 0x3D);
        sp7C[4]->unk10 = temp_fs2 - 70.0f;
        sp7C[4]->unk14 = temp_fs1;
        sp7C[4]->unk18 = temp_fs3;
        sp7C[4]->unkC |= 0x10080;
        sp7C[4]->unk36 = 0xFF;
        temp_v0_12 = func_ovl12_05_80049D88(0x328, 0);
        sp7C[5] = temp_v0_12;
        func_ovl12_05_80049DA8(temp_v0_12, 0x3E);
        sp7C[5]->unk10 = temp_fs2 - 60.0f;
        sp7C[5]->unk14 = temp_fs1;
        sp7C[5]->unk18 = temp_fs3;
        sp7C[5]->unkC |= 0x10080;
        sp7C[5]->unk36 = 0xFF;
        func_ovl12_05_8004A0B0(temp_s3, 0x01000000);
        temp_v0_13 = func_ovl12_05_8004A0D0(0x323, 0x01000000, 0xC0, 0);
        temp_v0_13->unk28 = 0x323;
        temp_v0_13->unk40->unk10 = temp_fs2;
        temp_v0_13->unk40->unk14 = temp_fs4;
        temp_v0_13->unk40->unk18 = temp_fs3;
        func_ovl12_05_8004A780(0x29F);
        sp64 = func_ovl12_05_8004A1F8(func_ovl12_05_80047774, NULL, 0, 0, 0x130);
        func_ovl12_05_8004A780(0x2A1);
        var_s1_2 = 0;
        do {
            func_ovl12_05_8004A1F8(func_ovl12_05_800475C8, temp_v0_13, 0, 0, 0x130);
            func_ovl12_05_8004A218(4);
            var_s1_2 += 1;
        } while (var_s1_2 < 8);
        func_ovl12_05_8004A780(0x29B);
        var_s1_3 = 0;
        do {
            for (var_a0 = 0; var_a0 < 6; var_a0++) {
                sp7C[var_a0]->unk10 += (var_a0 < 3 ? 300.0f : -300.0f) / 300.0f;
                sp7C[var_a0]->unk14 += 0.33333334f + ((f32) (3 - (var_a0 / 2)) * 10.0f) / 300.0f;
                sp7C[var_a0]->unk18 -= 0.6666667f;
                ANGLE_ADD(sp7C[var_a0]->unk1C, 5.0f);
                ANGLE_ADD(sp7C[var_a0]->unk20, (var_a0 < 3 ? 2 : -2));
                sp7C[var_a0]->unk36 -= 0.85f;
            }
            func_ovl12_05_8004A240();
            var_s1_3 += 1;
        } while (var_s1_3 < 0x12C);
        for (var_a0 = 0; var_a0 < 6; var_a0++) {
            func_ovl12_05_80049D90(sp7C[var_a0]);
        }
        func_ovl12_05_8004A780(0x29E);
        func_ovl12_05_8004A1F8(func_ovl12_05_80047544, temp_v0_13, 0, 0, 0x130);
        temp_s2 = func_ovl12_05_8004A1F8(func_ovl12_05_80047238, temp_v0_13, 0, 0, 0x130);
        func_ovl12_05_8004A1F8(func_ovl12_05_8004712C, temp_v0_13, 0, 0, 0x130);
        var_s1_4 = 0;
        do {
            func_ovl12_05_8004A1F8(func_ovl12_05_80046F44, temp_v0_13, 0, 0, 0x130);
            var_s1_4 += 1;
        } while (var_s1_4 < 0x10);
        var_s1_5 = 0;
        do {
            func_ovl12_05_8004A1F8(func_ovl12_05_80046D20, temp_v0_13, 0, 0, 0x130);
            var_s1_5 += 1;
        } while (var_s1_5 < 0x18);
        func_ovl12_05_8004A780(0x2A2);
        var_s1_6 = 0;
        do {
            if (var_s1_6 == 0x14) {
                func_ovl12_05_80049F08(32768.0f, 32768.0f, 2000.0f);
            }
            func_ovl12_05_8004A1F8(func_ovl12_05_800475C8, temp_v0_13, 0, 0, 0x130);
            func_ovl12_05_8004A218(4);
            var_s1_6 += 1;
        } while (var_s1_6 < 0x30);
        func_ovl12_05_8004A510(0xFF, 0xFF, 0xFF, 8);
        func_ovl12_05_8004A4F0();
        func_ovl12_05_8004A0B0(temp_v0_13, 0x01000000);
        func_ovl12_05_8004A200(sp64);
        func_ovl12_05_8004A200(temp_s2);
        func_ovl12_05_8004A780(0x297);
        var_s1_7 = 0;
        do {
            temp_v0_20 = temp_v0_13->unk40;
            func_ovl12_05_8004A648(0x11, temp_v0_20->unk10, temp_v0_20->unk14, temp_v0_20->unk18, 0);
            var_s1_7 += 1;
        } while (var_s1_7 < 8);
        var_s1_8 = 0;
        do {
            func_ovl12_05_8004A1F8(func_ovl12_05_80046990, temp_v0_13, 0, 0, 0x130);
            var_s1_8 += 1;
        } while (var_s1_8 < 0x18);
        func_ovl12_05_8004A1F8(func_ovl12_05_800466C4, temp_v0_13, 0, 0, 0x130);
        func_ovl12_05_8004A500(0xFF, 0xFF, 0xFF, 8);
        func_ovl12_05_8004A4F0();
        if (D_ovl12_05_8004AC4C == 0x1E) {
            func_ovl12_05_8004A218(0x55);
            func_ovl12_05_8004A8F8();
            D_ovl12_05_8004AC50 = 0;
            func_ovl12_05_8004A208();
        }
        func_ovl12_05_8004A218(0x78);
        func_ovl12_05_80049EE8(2350.0f, 100.0f, 1040.0f);
        func_ovl12_05_80049F08(0.0f, 43.0f, 2553.0f);
        func_ovl12_05_8004A0A8(temp_fp, 0x01000000);
        func_ovl12_05_8004A0A8(temp_s6, 0x01000000);
        func_ovl12_05_8004A0A8(D_ovl12_05_8004AC48, 0x01000000);
        temp_a0_4 = D_ovl12_05_8004AC48->unk40;
        temp_a0_4->unkC |= 0x1000;
        temp_fp->unk40->unk10 = 2350.0f;
        var_s1_9 = 0;
        temp_fp->unk40->unk14 = 0.0f;
        temp_fp->unk40->unk18 = 1200.0f;
        temp_fp->unk40->unk20 = 0.0f;
        temp_s6->unk40->unk10 = 2770.0f;
        temp_s6->unk40->unk14 = 0.0f;
        temp_s6->unk40->unk18 = 1465.0f;
        do {
            temp_v1_4 = temp_fp->unk40;
            temp_v1_4->unk36 = (s16) (s32) ((f32) temp_v1_4->unk36 + 2.125f);
            temp_v1_5 = temp_fp->unk40;
            if (temp_v1_5->unk36 >= 0x100) {
                temp_v1_5->unk36 = 0xFF;
            }
            temp_v0_21 = temp_s6->unk40;
            temp_v0_21->unk36 = (s16) (s32) ((f32) temp_v0_21->unk36 + 2.125f);
            temp_v0_22 = temp_s6->unk40;
            if (temp_v0_22->unk36 >= 0x100) {
                temp_v0_22->unk36 = 0xFF;
            }
            temp_a0_5 = D_ovl12_05_8004AC48->unk40;
            temp_a0_5->unk36 = (s16) (s32) ((f32) temp_a0_5->unk36 + 2.125f);
            temp_a0_6 = D_ovl12_05_8004AC48->unk40;
            if (temp_a0_6->unk36 >= 0x100) {
                temp_a0_6->unk36 = 0xFF;
            }
            func_ovl12_05_8004A240();
            var_s1_9 += 1;
        } while (var_s1_9 != 0x78);
        func_ovl12_05_8004A0B0(temp_fp, 0x80000);
        func_ovl12_05_8004A0B0(D_ovl12_05_8004AC48, 0x80000);
        temp_v1_6 = temp_fp->unk40;
        func_ovl12_05_80049EE8(temp_v1_6->unk10, temp_v1_6->unk14 + 100.0f, temp_v1_6->unk18);
        func_ovl12_05_80049F08(temp_fp->unk40->unk20, 20.0f, 800.0f);
        func_ovl12_05_80049898(0);
        func_ovl12_05_80049848(0x20);
        D_ovl12_05_8004AC6C = 1;
    }
}

void func_ovl12_05_80043018(void) {
    UnkStructA *temp_s1;
    UnkStructA *temp_s3;
    UnkStructA_40 *temp_v0_10;
    UnkStructA_40 *temp_v0_11;
    UnkStructA_40 *temp_v0_12;
    UnkStructA_40 *temp_v0_7;
    UnkStructA_40 *temp_v0_8;
    UnkStructA_40 *temp_v0_9;
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_2;
    UnkStructA_40 *temp_v1_3;
    UnkStructA_40 *temp_v1_4;
    UnkStructA_40 *temp_v1_5;
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *temp_v0_2;
    UnkStructA_40_48_4 *temp_v0_3;
    UnkStructA_40_48_4 *temp_v0_4;
    UnkStructA_40_48_4 *temp_v0_5;
    UnkStructA_40_48_4 *temp_v0_6;
    f32 temp_fv1;
    f32 var_fs0;
    f32 var_fv0;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;

    func_ovl12_05_80043010();
    if (D_ovl12_05_8004AC6C != 0) {
        func_ovl12_05_8004A7E0(0x7F);
        func_ovl12_05_8004A7C0(0x7F);
        func_ovl12_05_8004A780(0x22B);
        func_ovl12_05_80049FB8();
        func_ovl12_05_80049FD0(2.0f, 2.0f, 2.0f);
        func_ovl12_05_80049FC0(-1);
        temp_s3 = func_ovl12_05_800498E8(0);
        temp_s1 = func_ovl12_05_800498E8(2);
        func_ovl12_05_8004A0B0(temp_s3, 0x40000);
        func_ovl12_05_8004A0B0(temp_s1, 0x40000);
        func_ovl12_05_8004A268(0x70, 0x70, 0);
        temp_s1->unk40->unk10 = 2350.0f;
        temp_s1->unk40->unk14 = 400.0f;
        temp_s1->unk40->unk18 = 1100.0f;
        temp_s1->unk40->unk20 = 0.0f;
        func_ovl12_05_80049DD0(temp_s1->unk40, 0xD, 0);
        func_ovl12_05_80049DD0(temp_s1->unk40, -1, 1);
        temp_v0 = temp_s1->unk40->unk48->unk4;
        temp_v0->unk8 |= 0x20;
        temp_v0_2 = temp_s1->unk40->unk48->unk4;
        temp_v0_2->unk8 |= 0x40;
        func_ovl12_05_8004A780(0x2E6);
        var_s0 = 0;
        do {
            temp_v1 = temp_s1->unk40;
            temp_v1->unk14 -= 3.3333333f;
            if (var_s0 == 0x60) {
                temp_v0_3 = temp_s1->unk40->unk48->unk4;
                temp_v0_3->unk8 &= ~0x40;
            }
            func_ovl12_05_8004A240();
            var_s0 += 1;
        } while (var_s0 != 0x78);
        func_ovl12_05_8004A780(0x1C);
        func_ovl12_05_8004A780(0x2B2);
        func_ovl12_05_8004A780(0x1C);
        temp_v1_2 = temp_s1->unk40;
        func_ovl12_05_8004A648(0xD, temp_v1_2->unk10, temp_v1_2->unk14, temp_v1_2->unk18, 0);
        if (!(temp_s1->unk40->unk48->unk4->unk8 & 0x40)) {
            do {
                func_ovl12_05_8004A240();
            } while (!(temp_s1->unk40->unk48->unk4->unk8 & 0x40));
        }
        func_ovl12_05_8004A218(0x1E);
        func_ovl12_05_80049938(0, 0);
        func_ovl12_05_80049DD0(temp_s1->unk40, 0x16, 0);
        temp_v0_4 = temp_s1->unk40->unk48->unk4;
        var_s0_2 = 0;
        temp_v0_4->unk8 |= 0x20;
        temp_v0_5 = temp_s1->unk40->unk48->unk4;
        temp_v0_5->unk8 &= ~0x40;
        do {
            if (var_s0_2 == 5) {
                temp_v0_6 = temp_s1->unk40->unk48->unk4;
                temp_v0_6->unk8 |= 0x40;
            }
            temp_v1_3 = temp_s1->unk40;
            temp_v1_3->unk14 += 4.1666665f;
            if (var_s0_2 >= 8) {
                temp_v0_7 = temp_s3->unk40;
                temp_v0_7->unk14 += 4.1666665f;
            }
            temp_v0_8 = temp_s3->unk40;
            func_ovl12_05_80049EE8(temp_v0_8->unk10, temp_v0_8->unk14 + 100.0f, temp_v0_8->unk18);
            func_ovl12_05_8004A240();
            var_s0_2 += 1;
        } while (var_s0_2 < 0x3C);
        var_fs0 = 0.0f;
        var_s0_3 = 0;
        do {
            temp_v0_9 = temp_s3->unk40;
            temp_v0_9->unk14 += func_ovl12_05_8004A3A8(var_fs0) * 1.8f;
            temp_v1_4 = temp_s1->unk40;
            temp_fv1 = var_fs0 + 5.0f;
            temp_v1_4->unk14 += func_ovl12_05_8004A3A8(var_fs0) * 1.8f;
            if (temp_fv1 >= 360.0f) {
                var_fs0 = temp_fv1 - 360.0f;
            } else {
                if (temp_fv1 < 0.0f) {
                    var_fv0 = temp_fv1 + 360.0f;
                } else {
                    var_fv0 = temp_fv1;
                }
                var_fs0 = var_fv0;
            }
            temp_v0_10 = temp_s3->unk40;
            func_ovl12_05_80049EE8(temp_v0_10->unk10, temp_v0_10->unk14 + 100.0f, temp_v0_10->unk18);
            func_ovl12_05_8004A240();
            var_s0_3 += 1;
        } while (var_s0_3 < 0x78);
        var_s0_4 = 0;
        do {
            temp_v0_11 = temp_s3->unk40;
            temp_v0_11->unk14 += 16.666666f;
            temp_v1_5 = temp_s1->unk40;
            temp_v1_5->unk14 += 16.666666f;
            if (var_s0_4 < 0x28) {
                temp_v0_12 = temp_s3->unk40;
                func_ovl12_05_80049EE8(temp_v0_12->unk10, temp_v0_12->unk14 + 100.0f, temp_v0_12->unk18);
            }
            func_ovl12_05_8004A240();
            var_s0_4 += 1;
        } while (var_s0_4 != 0x78);
        func_ovl12_05_80049FB8();
    }
}

void func_ovl12_05_80045D3C(s32 arg0) {
    UnkStruct_ovl12_05_8004A840 *spC0;
    UnkStruct_ovl12_05_800497F8 *spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    UnkStruct_ovl12_05_8004A840 *spA0;
    UnkStruct_ovl12_05_800497F8 *sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_3;
    UnkStruct_ovl12_05_8004A840 *temp_v0;
    UnkStruct_ovl12_05_8004A840 *temp_v0_2;
    UnkStruct_ovl12_05_8004A840 *temp_v1_2;
    UnkStruct_ovl12_05_8004A840 *temp_v1_4;
    s32 var_v0;
    s32 var_v0_2;

    switch (arg0) {
    case 2:
        D_ovl12_05_8004AC4C = func_ovl12_05_800497A8();
        func_ovl12_05_80045B00();
    default:
        break;
    case 16:
    case 26:
        func_ovl12_05_80045954();
        break;
    case 17:
    case 28:
        func_ovl12_05_80045844();
        break;
    case 18:
        spBC = func_ovl12_05_800497F8();
        func_ovl12_05_8004A828(1, 8, 0x17, 0, 7);
        func_ovl12_05_8004A828(2, 9, 0x19, 0, 0xE);
        func_ovl12_05_80049860(0x16, 0, 0xE);
        func_ovl12_05_800498A0(0);
        func_ovl12_05_80049918(2);
        func_ovl12_05_800498A0(0);
        func_ovl12_05_80049918(0);
        temp_v1 = func_ovl12_05_800498E8(1)->unk40;
        temp_v1->unk10 += 50.0f;
        func_ovl12_05_80049830(0x7E, 0x13);
        func_ovl12_05_800498B8();
        func_ovl12_05_80049F50(0xF);
        temp_v0 = func_ovl12_05_8004A840(1);
        temp_v1_2 = temp_v0;
        if ((D_ovl12_05_8004AC4C == 0x12) && !(temp_v0->unk124 & 8)) {
            var_v0 = 0x1388;
            if (spBC->unk10 == 0) {
                var_v0 = 0x1F40;
            }
            if (var_v0 >= D_ovl12_05_8004AC74) {
                spB0 = temp_v1_2->unk1C->unk40->unk10;
                spB4 = temp_v1_2->unk1C->unk40->unk14;
                spC0 = temp_v1_2;
                spB8 = temp_v1_2->unk1C->unk40->unk18;
                func_ovl12_05_8004A428((Vec3f *) &spB0);
                spC0->unk124 |= 8;
                spBC->unk2C += 1;
            }
        }
        break;
    case 19:
    case 30:
        sp9C = func_ovl12_05_800497F8();
        func_ovl12_05_8004A828(1, 8, 0x17, 0, 7);
        func_ovl12_05_8004A828(2, 9, 0x19, 0, 0xE);
        func_ovl12_05_80049860(0x16, 0, 0xE);
        func_ovl12_05_800498A0(0);
        func_ovl12_05_80049918(2);
        func_ovl12_05_800498A0(0);
        func_ovl12_05_80049918(0);
        temp_v1_3 = func_ovl12_05_800498E8(1)->unk40;
        temp_v1_3->unk10 += 50.0f;
        func_ovl12_05_800498B8();
        func_ovl12_05_80049F50(0xF);
        temp_v0_2 = func_ovl12_05_8004A840(1);
        temp_v1_4 = temp_v0_2;
        if ((D_ovl12_05_8004AC4C == 0x13) && !(temp_v0_2->unk124 & 8)) {
            var_v0_2 = 0x1388;
            if (sp9C->unk10 == 0) {
                var_v0_2 = 0x1F40;
            }
            if (var_v0_2 >= D_ovl12_05_8004AC74) {
                sp90 = temp_v1_4->unk1C->unk40->unk10;
                sp94 = temp_v1_4->unk1C->unk40->unk14;
                spA0 = temp_v1_4;
                sp98 = temp_v1_4->unk1C->unk40->unk18;
                func_ovl12_05_8004A428((Vec3f *) &sp90);
                spA0->unk124 |= 8;
                sp9C->unk2C += 1;
            }
        }
        break;
    case 4:
        func_ovl12_05_80045754();
        break;
    case 5:
        func_ovl12_05_800456A0();
        break;
    case 32:
        func_ovl12_05_80044534();
        break;
    case 33:
        func_ovl12_05_8004A1F8(func_ovl12_05_80046560, NULL, 0, 0, 0x130);
        break;
    case 11:
        func_ovl12_05_800434C8();
        break;
    case 12:
        func_ovl12_05_80043018();
        break;
    case 1:
        if ((D_ovl12_05_8004AC4C == 0x1A) || (D_ovl12_05_8004AC4C == 0x1B) || (D_ovl12_05_8004AC4C == 0x1C) || (D_ovl12_05_8004AC4C == 0x1D) || (D_ovl12_05_8004AC4C == 0x1E) || (D_ovl12_05_8004AC4C == 0x1F)) {
            func_ovl12_05_8004A900();
        }
        if (D_ovl12_05_8004AC70 == 0) {
            func_ovl12_05_8004A420();
        }
        break;
    }
}

static void func_ovl12_05_80043010(void) {
}
