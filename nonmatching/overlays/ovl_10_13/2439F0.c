/*
 * NON_MATCHING: ovl_10_13's game object, complete: every function and its
 * .bss. Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING
 * drafts").
 * flags: -O3
 * differing words: us 1296, jp 1841
 *
 * What still differs in us (words, as tools/nonmatching.py counts them):
 * - 80047A0C (699), 800475F8 (126), 80048850 (117), 800470C8 (111),
 *   80047298 (90), 80048BBC (76), 800486A8 (55), 80047418 (8), 80048EA8 (8),
 *   800464B0 (4: v1 for v0, a third temporary grows the frame),
 *   80046E88 (2): m2c's C, cleaned up only where it didn't compile.
 * - Not counted: the statics 80043070 (1507), 80044E48 (394) and 8004574C
 *   (532), the cut-scenes the handler and 800474EC-800477E8 run
 *   (scratch/10_13/allf.py counts them from the object's .mdebug). They
 *   save no callee-saved registers (their callers do), so they are
 *   static; they come first in the object. They are m2c's C too.
 *
 * The handler's cases 800460E0-800468BC are globals defined above the
 * handler: it pulls them out, with the statics, in the reverse order of
 * their calls (statics first, as in the original). As statics they were
 * inlined into it; as globals below it they came out at their own turn,
 * ahead of the statics.
 *
 * ovl_10_13's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). The task functions
 * 80046ACC-80046E50 and 80049044 are ovl_10_12's and ovl_10_11's,
 * 80049138-80049210 ovl_17_09's (renamed); the rest is m2c's output
 * (scratch/10_13/ in the checkout has the scripts). .rodata (the two
 * strings, floats and jump tables) builds to the original's size and order
 * up to 0xCC, where a float of a differing function comes early. The .bss
 * has the original's order, but the unreferenced bytes (8004AB50, 0x24,
 * and the words at 8004AB7C and 8004AB94) aren't defined in place:
 * IDO leaves an unreferenced array COMMON, so the draft's .bss is 0x24
 * short at the front and 8 bytes short in the middle.
 */
#include "common.h"

/* What func_ovl10_13_80049728 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x14];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
} UnkStruct_ovl10_13_80049728;

/* What func_ovl10_13_8004A770 returns: a player. */
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
} UnkStruct_ovl10_13_8004A770;

void func_ovl10_13_80049298(const char *, ...);
void func_ovl10_13_800495D8(s32);
void func_ovl10_13_800495F0(s32);
void func_ovl10_13_800496D0(s32, s32, s32);
s32 func_ovl10_13_800496D8(void);
UnkStruct_ovl10_13_80049728 *func_ovl10_13_80049728(void);
void func_ovl10_13_80049760(s32, s32);
s32 func_ovl10_13_80049770(s32);
void func_ovl10_13_80049778(s32);
void func_ovl10_13_80049788(void);
void func_ovl10_13_80049790(s32, s32, s32);
void func_ovl10_13_800497C8(s32);
void func_ovl10_13_800497D0(s32);
void func_ovl10_13_800497E8(void);
UnkStructA *func_ovl10_13_80049818(s32);
void func_ovl10_13_80049848(s32);
void func_ovl10_13_80049868(s32, s32);
void func_ovl10_13_80049888(void);
UnkStructA_40 *func_ovl10_13_80049CB8(s32, s32);
void func_ovl10_13_80049CC0(UnkStructA_40 *);
void func_ovl10_13_80049D00(UnkStructA_40 *, s32, s32);
f32 func_ovl10_13_80049D18(UnkStructA_40 *, s32);
void func_ovl10_13_80049D30(UnkStructA_40 *, s32, s32);
void func_ovl10_13_80049D40(s32, s32);
s32 func_ovl10_13_80049D48(UnkStructA_40 *, s32);
void func_ovl10_13_80049D50(s32, s32, s32);
void func_ovl10_13_80049D60(s32, s32, s32);
void func_ovl10_13_80049DF8(s32);
void func_ovl10_13_80049E08(s32);
void func_ovl10_13_80049E18(f32, f32, f32);
void func_ovl10_13_80049E28(f32, f32, f32);
void func_ovl10_13_80049E38(f32, f32, f32);
void func_ovl10_13_80049E40(f32 *, f32 *, f32 *);
void func_ovl10_13_80049E78(s32);
void func_ovl10_13_80049E80(s32);
void func_ovl10_13_80049F68(Vec3f *, Vec3f *, f32 *);
f32 func_ovl10_13_80049F80(Vec3f *, Vec3f *);
void func_ovl10_13_80049FD8(UnkStructA *, s32);
void func_ovl10_13_80049FE0(UnkStructA *, s32);
void func_ovl10_13_80049FF0(UnkStructA *);
UnkStructA *func_ovl10_13_8004A000(s32, s32, s32, s32);
UnkStructA *func_ovl10_13_8004A010(UnkStructA *);
void func_ovl10_13_8004A058(UnkStructA *);
void func_ovl10_13_8004A0A8(UnkStructA *, Vec3f *);
s32 func_ovl10_13_8004A128(void (*)(), void *, s32, s32, s32);
void func_ovl10_13_8004A130(s32);
void func_ovl10_13_8004A138(void);
void func_ovl10_13_8004A140(u16, s32);
void func_ovl10_13_8004A148(s32);
void *func_ovl10_13_8004A150(void);
void func_ovl10_13_8004A170(void);
void func_ovl10_13_8004A188(u16);
void func_ovl10_13_8004A198(s32, s32, s32);
UnkStructC *func_ovl10_13_8004A1B0(s32);
void func_ovl10_13_8004A1C0(UnkStructC *, s32);
f32 func_ovl10_13_8004A2D0(f32);
f32 func_ovl10_13_8004A2D8(f32);
f64 func_ovl10_13_8004A2E0(void);
s32 func_ovl10_13_8004A2E8(s32);
void func_ovl10_13_8004A348(void);
void func_ovl10_13_8004A350(void);
void func_ovl10_13_8004A358(Vec3f *);
void func_ovl10_13_8004A380(s32);
s32 func_ovl10_13_8004A390(s32);
s32 *func_ovl10_13_8004A3C0(void);
void func_ovl10_13_8004A420(void);
void func_ovl10_13_8004A428(s32, s32, s32, f32);
void func_ovl10_13_8004A430(s32, s32, s32, s32);
void func_ovl10_13_8004A440(s32, s32, s32, s32);
void func_ovl10_13_8004A578(s32, f32, f32, f32, s32);
void func_ovl10_13_8004A580(s32, f32 *, s32);
void func_ovl10_13_8004A6B0(s32);
void func_ovl10_13_8004A6C0(s32);
void func_ovl10_13_8004A6C8(void);
s32 func_ovl10_13_8004A6D0(s32, f32, f32, f32);
void func_ovl10_13_8004A6F0(s32);
void func_ovl10_13_8004A700(s32, f32, f32, f32);
void func_ovl10_13_8004A710(s32);
void func_ovl10_13_8004A740(UnkStructA_40 *, s32, s32, s32, f32);
void func_ovl10_13_8004A750(UnkStructA_40 *);
void func_ovl10_13_8004A758(s32, s32, s32, s32, s32);
UnkStruct_ovl10_13_8004A770 *func_ovl10_13_8004A770(s32);
void func_ovl10_13_8004A778(s32);
void func_ovl10_13_8004A828(void);
void func_ovl10_13_8004A830(void);

static f32 func_ovl10_13_80043010(UnkStructA_40 *from, UnkStructA_40 *to);
static void func_ovl10_13_80043070(void);
static void func_ovl10_13_80044E48(void);
static void func_ovl10_13_8004574C(void);
void func_ovl10_13_800460E0(void);
void func_ovl10_13_80046168(void);
void func_ovl10_13_8004621C(void);
void func_ovl10_13_80046324(void);
void func_ovl10_13_800464B0(void);
void func_ovl10_13_800466B8(void);
void func_ovl10_13_80046750(void);
void func_ovl10_13_800468BC(void);
void func_ovl10_13_80046940(s32 arg0);
void func_ovl10_13_80046ACC(UnkStructA *arg0);
void func_ovl10_13_80046B4C(UnkStructA *arg0);
void func_ovl10_13_80046BB8(void);
void func_ovl10_13_80046BF4(void);
void func_ovl10_13_80046C70(s32 arg0);
void func_ovl10_13_80046D00(void (*arg0)());
void func_ovl10_13_80046D1C(s32 arg0);
void func_ovl10_13_80046D38(s32 arg0);
void func_ovl10_13_80046D4C(void);
s32 func_ovl10_13_80046D68(void (*arg0)());
void func_ovl10_13_80046DAC(void (*arg0)());
s32 func_ovl10_13_80046DD8(void (*arg0)());
s32 func_ovl10_13_80046E50(void (*arg0)(), const char *arg1);
void func_ovl10_13_80046E88(void);
void func_ovl10_13_800470C8(void);
void func_ovl10_13_80047298(void);
void func_ovl10_13_80047418(void);
void func_ovl10_13_800474EC(void);
void func_ovl10_13_800475F8(void);
void func_ovl10_13_800477E8(void);
void func_ovl10_13_800478D4(void);
void func_ovl10_13_80047A0C(void);
void func_ovl10_13_800486A8(void);
void func_ovl10_13_80048850(s32 arg0);
void func_ovl10_13_80048BBC(void);
void func_ovl10_13_80048CEC(void);
void func_ovl10_13_80048EA8(void);
void func_ovl10_13_80048F00(void);
void func_ovl10_13_80049044(void);
void func_ovl10_13_80049138(s32 arg0, UnkStructA *arg1);
void func_ovl10_13_8004916C(f32 arg0);
void func_ovl10_13_800491B4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl10_13_80049210(void);
void func_ovl10_13_80049228(void);
void func_ovl10_13_80049230(void);
void func_ovl10_13_80049238(void);
void func_ovl10_13_80049240(void);
void func_ovl10_13_80049248(void);
void func_ovl10_13_80049250(void);
void func_ovl10_13_80049258(void);
void func_ovl10_13_80049260(void);
void func_ovl10_13_80049268(void);
void func_ovl10_13_80049270(void);
void func_ovl10_13_80049278(void);
void func_ovl10_13_80049280(void);

u8 D_ovl10_13_8004AB50[0x24]; /* unused */
s32 D_ovl10_13_8004AB74;
s32 D_ovl10_13_8004AB78;
Vec3f D_ovl10_13_8004AB80;
s32 D_ovl10_13_8004AB8C;
s32 D_ovl10_13_8004AB90;
s32 D_ovl10_13_8004AB98[64];
s32 D_ovl10_13_8004AC98; /* the running task */
void (*D_ovl10_13_8004ACA0[64])();
UnkStructC *D_ovl10_13_8004ADA0;
UnkStructA_40 *D_ovl10_13_8004ADA4;
s32 D_ovl10_13_8004ADA8;
UnkStructA_40 *D_ovl10_13_8004ADAC;
UnkStructA_40 *D_ovl10_13_8004ADB0;
s32 D_ovl10_13_8004ADB4;
s32 D_ovl10_13_8004ADB8;
s32 D_ovl10_13_8004ADBC;
UnkStructA *D_ovl10_13_8004ADC0;
UnkStructA *D_ovl10_13_8004ADC4;
UnkStructA *D_ovl10_13_8004ADC8;
s32 D_ovl10_13_8004ADCC;
s32 D_ovl10_13_8004ADD0;
s32 D_ovl10_13_8004ADD4;
s32 D_ovl10_13_8004ADD8;
s32 D_ovl10_13_8004ADDC;
s32 D_ovl10_13_8004ADE0;
s32 D_ovl10_13_8004ADE4;

void func_ovl10_13_80049280(void) {
}

void func_ovl10_13_80049278(void) {
}

void func_ovl10_13_80049270(void) {
}

void func_ovl10_13_80049268(void) {
}

void func_ovl10_13_80049260(void) {
}

void func_ovl10_13_80049258(void) {
}

void func_ovl10_13_80049250(void) {
}

void func_ovl10_13_80049248(void) {
}

void func_ovl10_13_80049240(void) {
}

void func_ovl10_13_80049238(void) {
}

void func_ovl10_13_80049230(void) {
}

void func_ovl10_13_80049228(void) {
}

void func_ovl10_13_80049210(void) {
    D_ovl10_13_8004AB74 = -1;
    D_ovl10_13_8004AB78 = -1;
}

void func_ovl10_13_800491B4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_13_80049E18(D_ovl10_13_8004AB80.x, D_ovl10_13_8004AB80.y, D_ovl10_13_8004AB80.z);
    func_ovl10_13_80049E38(arg0, arg1, arg2);
    func_ovl10_13_8004A148(180);
}

void func_ovl10_13_8004916C(f32 arg0) {
    f32 sp1C;

    func_ovl10_13_80049E40(&sp1C, NULL, NULL);
    func_ovl10_13_80049E38(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_13_80049138(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl10_13_8004A6D0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl10_13_80049044(void) {
    s32 i;

    D_ovl10_13_8004AB8C = 0;
    D_ovl10_13_8004AB90 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_13_8004ACA0[i] != NULL) {
                D_ovl10_13_8004AC98 = i;
                if (D_ovl10_13_8004AB98[i] == 0) {
                    D_ovl10_13_8004ACA0[i]();
                } else {
                    D_ovl10_13_8004AB98[i]--;
                }
            }
        }
        D_ovl10_13_8004AB8C++;
        D_ovl10_13_8004AB8C &= 3;
        func_ovl10_13_8004A170();
    }
}

void func_ovl10_13_80048F00(void) {
    UnkStructA_40 *temp_s0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    s32 temp_s1;

    temp_s0 = ((UnkStructA *)func_ovl10_13_8004A150())->unk40;
    temp_s1 = func_ovl10_13_8004A6D0(0x240, temp_s0->unk10, temp_s0->unk14, temp_s0->unk18);
loop_1:
    temp_fs0 = func_ovl10_13_8004A2D0(temp_s0->unk20);
    temp_fs1 = func_ovl10_13_8004A2D0(temp_s0->unk1C);
    temp_fs2 = func_ovl10_13_8004A2D8(temp_s0->unk20);
    temp_s0->unk10 += func_ovl10_13_8004A2D8(temp_s0->unk1C) * temp_fs0 * 40.0f;
    temp_s0->unk14 -= temp_fs1 * 40.0f;
    temp_s0->unk18 += func_ovl10_13_8004A2D8(temp_s0->unk1C) * temp_fs2 * 40.0f;
    func_ovl10_13_8004A700(temp_s1, temp_s0->unk10, temp_s0->unk14, temp_s0->unk18);
    func_ovl10_13_8004A170();
    goto loop_1;
}

void func_ovl10_13_80048EA8(void) {
    UnkStructA *temp_s0;
    UnkStructA_40 *temp_v0;

    temp_s0 = func_ovl10_13_8004A150();
loop_1:
    temp_v0 = temp_s0->unk40;
    func_ovl10_13_80049E18(temp_v0->unk10, temp_v0->unk14, temp_v0->unk18);
    func_ovl10_13_8004A170();
    goto loop_1;
}

void func_ovl10_13_80048CEC(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v1;
    f32 temp_fv0;
    f32 var_fv1;
    s32 var_s2;

    temp_v0 = func_ovl10_13_8004A150();
    temp_v1 = temp_v0->unk40;
    func_ovl10_13_8004A6D0(0x242, temp_v1->unk10, temp_v1->unk14, temp_v1->unk18);
    temp_v0_2 = func_ovl10_13_80049CB8(0x2CF, 0);
    temp_v0_2->unkC |= 0x80;
    temp_v0_2->unk36 = 0x50;
    var_s2 = 0;
    temp_v0_2->unk2C = 50.0f;
    do {
        temp_v0_2->unk10 = temp_v0->unk40->unk10;
        temp_v0_2->unk14 = temp_v0->unk40->unk14 + 60.0f;
        temp_v0_2->unk18 = temp_v0->unk40->unk18;
        temp_fv0 = temp_v0->unk40->unk1C + 90.0f;
        if (temp_fv0 >= 360.0f) {
            temp_v0_2->unk1C = temp_fv0 - 360.0f;
        } else {
            if (temp_fv0 < 0.0f) {
                var_fv1 = temp_fv0 + 360.0f;
            } else {
                var_fv1 = temp_fv0;
            }
            temp_v0_2->unk1C = var_fv1;
        }
        temp_v0_2->unk20 = temp_v0->unk40->unk20;
        temp_v0_2->unk24 = temp_v0->unk40->unk24;
        func_ovl10_13_8004A170();
        var_s2 += 1;
    } while (var_s2 != 0x3C);
    func_ovl10_13_80049CC0(temp_v0_2);
    func_ovl10_13_8004A138();
}

void func_ovl10_13_80048BBC(void) {
    s32 var_s0;
    s32 var_s0_2;

    func_ovl10_13_8004A6B0(0x243);
    var_s0 = 0;
    do {
        func_ovl10_13_8004A740(D_ovl10_13_8004ADB0, 0x1F, 0, 4, (f32) var_s0 / 140.0f);
        func_ovl10_13_8004A170();
        var_s0 += 1;
    } while (var_s0 < 0x3C);
    D_ovl10_13_8004ADB0->unkC |= 0x1080;
    var_s0_2 = 0x3C;
    D_ovl10_13_8004ADB0->unk36 = 0xFF;
    do {
        D_ovl10_13_8004ADB0->unk36 = (s16) (s32) (((f32) var_s0_2 / 60.0f) * 255.0f);
        func_ovl10_13_8004A170();
        var_s0_2 -= 1;
    } while (var_s0_2 != 0);
    func_ovl10_13_80049CC0(D_ovl10_13_8004ADB0);
    func_ovl10_13_8004A138();
}

void func_ovl10_13_80048850(s32 arg0) {
    UnkStructA *temp_s3;
    UnkStructA_40 *temp_v0_2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs0;
    f32 var_fv0;
    s32 temp_s7;
    s32 temp_v0;
    s32 var_a0;
    s32 var_s1;

    temp_v0 = func_ovl10_13_8004A150();
    temp_s3 = func_ovl10_13_80049818(temp_v0);
    temp_v0_2 = func_ovl10_13_80049CB8(0x302, 0);
    temp_v0_2->unkC |= 0x80;
    temp_v0_2->unk36 = 0x80;
    temp_v0_2->unk30 = 0.1f;
    temp_v0_2->unk2C = 0.1f;
    temp_v0_2->unk28 = 0.1f;
    temp_v0_2->unk10 = temp_s3->unk40->unk10;
    var_a0 = 0x24F;
    temp_v0_2->unk14 = temp_s3->unk40->unk14 + 50.0f;
    temp_v0_2->unk18 = temp_s3->unk40->unk18;
    if (temp_v0 == 1) {
        var_a0 = 0x24B;
    }
    temp_s7 = func_ovl10_13_8004A6D0(var_a0, temp_v0_2->unk10, temp_v0_2->unk14, temp_v0_2->unk18);
    if (D_ovl10_13_8004ADA8 != 0x1C) {
        var_s1 = 0;
        do {
            temp_v0_2->unk30 += 0.033333335f;
            temp_fv0 = temp_v0_2->unk30;
            temp_v0_2->unk2C = temp_fv0;
            temp_v0_2->unk28 = temp_fv0;
            func_ovl10_13_8004A170();
            var_s1 += 1;
        } while (var_s1 != 0x3C);
    } else {
        temp_v0_2->unk30 = 2.0f;
        temp_v0_2->unk2C = 2.0f;
        temp_v0_2->unk28 = 2.0f;
    }
    var_fs0 = 0.0f;
loop_8:
    if (((temp_v0 != 1) || (D_ovl10_13_8004ADD4 != 0)) && ((temp_v0 != 2) || (D_ovl10_13_8004ADD8 != 0))) {
        temp_v0_2->unk10 = temp_s3->unk40->unk10;
        temp_v0_2->unk14 = temp_s3->unk40->unk14 + 50.0f;
        temp_v0_2->unk18 = temp_s3->unk40->unk18;
        temp_fv1 = (func_ovl10_13_8004A2D8(var_fs0) * 0.2f) + 2.5f;
        temp_v0_2->unk30 = temp_fv1;
        temp_v0_2->unk2C = temp_fv1;
        temp_v0_2->unk28 = temp_fv1;
        temp_v0_2->unk36 = (s16) (s32) (128.0f - (func_ovl10_13_8004A2D8(var_fs0) * 10.0f));
        temp_fv1_2 = var_fs0 + 9.0f + (f32) D_ovl10_13_8004ADDC;
        if (temp_fv1_2 >= 360.0f) {
            var_fs0 = temp_fv1_2 - 360.0f;
        } else {
            if (temp_fv1_2 < 0.0f) {
                var_fv0 = temp_fv1_2 + 360.0f;
            } else {
                var_fv0 = temp_fv1_2;
            }
            var_fs0 = var_fv0;
        }
        func_ovl10_13_8004A700(temp_s7, temp_v0_2->unk10, temp_v0_2->unk14, temp_v0_2->unk18);
        func_ovl10_13_8004A170();
        goto loop_8;
    }
    func_ovl10_13_80049CC0(temp_v0_2);
    func_ovl10_13_8004A138();
}

void func_ovl10_13_800486A8(void) {
    UnkStructA *temp_s0;
    UnkStructA_40 *temp_v0;
    f32 temp_fv0;
    s32 var_s0;
    s32 var_s1;

    temp_s0 = func_ovl10_13_8004A150();
    temp_v0 = func_ovl10_13_80049CB8(0x2C7, 0);
    temp_v0->unk36 = 0;
    temp_v0->unkC |= 0x80;
    temp_v0->unk10 = temp_s0->unk40->unk10;
    temp_v0->unk14 = temp_s0->unk40->unk14 + 50.0f;
    temp_v0->unk18 = temp_s0->unk40->unk18;
    if (D_ovl10_13_8004ADE0 != 0) {
        var_s0 = 0;
        do {
            var_s1 = 0;
loop_3:
            temp_fv0 = 15.0f - (((f32) var_s0 * 14.0f) / 30.0f);
            temp_v0->unk30 = temp_fv0;
            temp_v0->unk2C = temp_fv0;
            temp_v0->unk28 = temp_fv0;
            temp_v0->unk36 = (s16) (s32) (func_ovl10_13_8004A2D0((f32) var_s1) * 120.0f);
            func_ovl10_13_8004A170();
            var_s0 += 1;
            var_s1 += 6;
            if (var_s0 != 0x1E) {
                goto loop_3;
            }
            var_s0 = 0;
        } while (D_ovl10_13_8004ADE0 != 0);
    }
    func_ovl10_13_80049CC0(temp_v0);
    func_ovl10_13_8004A138();
}

void func_ovl10_13_80047A0C(void) {
    UnkStructA *sp5C;
    UnkStructA *sp54;
    f32 sp4C;
    s32 sp44;
    s32 sp40;
    UnkStructA *temp_s2;
    UnkStructA *temp_v0_7;
    UnkStructA_40 *temp_s1;
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_10;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    UnkStructA_40 *temp_v0_6;
    UnkStructA_40 *temp_v0_9;
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_2;
    UnkStructA_40 *temp_v1_3;
    UnkStructA_40 *temp_v1_4;
    UnkStructA_40 *temp_v1_5;
    UnkStructA_40 *temp_v1_6;
    UnkStruct_ovl10_13_8004A770 *temp_v0_8;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv0_7;
    f32 temp_fv0_8;
    f32 temp_fv1;
    f32 temp_fv1_10;
    f32 temp_fv1_11;
    f32 temp_fv1_12;
    f32 temp_fv1_13;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 temp_fv1_5;
    f32 temp_fv1_6;
    f32 temp_fv1_7;
    f32 temp_fv1_8;
    f32 temp_fv1_9;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fv0;
    f32 var_fv0_10;
    f32 var_fv0_11;
    f32 var_fv0_12;
    f32 var_fv0_13;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;
    f32 var_fv0_5;
    f32 var_fv0_6;
    f32 var_fv0_7;
    f32 var_fv0_8;
    f32 var_fv0_9;
    s32 var_s0;
    s32 var_s0_10;
    s32 var_s0_11;
    s32 var_s0_12;
    s32 var_s0_13;
    s32 var_s0_14;
    s32 var_s0_15;
    s32 var_s0_16;
    s32 var_s0_17;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_s0_7;
    s32 var_s0_8;
    s32 var_s0_9;

    sp5C = func_ovl10_13_80049818(0);
    temp_s2 = func_ovl10_13_80049818(2);
    func_ovl10_13_80049868(0, 3);
    var_s0 = 0;
    do {
        temp_v0 = sp5C->unk40;
        temp_v0->unk18 -= 8.0f;
        func_ovl10_13_8004A170();
        var_s0 += 8;
    } while (var_s0 < 0x258);
    func_ovl10_13_8004A6B0(0x263);
    func_ovl10_13_80049E38(185.0f, 10.0f, 2000.0f);
    var_s0_2 = 0;
    do {
        temp_v0_2 = sp5C->unk40;
        temp_v0_2->unk18 -= 8.0f;
        func_ovl10_13_8004A170();
        var_s0_2 += 8;
    } while (var_s0_2 < 0x258);
    func_ovl10_13_80049868(0, 0);
    func_ovl10_13_8004A6B0(0x276);
    var_s0_3 = 0;
    do {
        temp_v1 = temp_s2->unk40;
        temp_v1->unk14 -= 8.333333f;
        temp_v1_2 = temp_s2->unk40;
        temp_v1_2->unk18 -= 10.0f;
        temp_v1_3 = temp_s2->unk40;
        temp_v1_3->unk1C -= 1.5f;
        func_ovl10_13_8004A170();
        var_s0_3 += 1;
    } while (var_s0_3 < 0x3C);
    var_s0_4 = 0;
    do {
        temp_v0_3 = sp5C->unk40;
        temp_fv1 = temp_v0_3->unk20 + 18.0f;
        if (temp_fv1 >= 360.0f) {
            temp_v0_3->unk20 = temp_fv1 - 360.0f;
        } else {
            if (temp_fv1 < 0.0f) {
                var_fv0 = temp_fv1 + 360.0f;
            } else {
                var_fv0 = temp_fv1;
            }
            temp_v0_3->unk20 = var_fv0;
        }
        func_ovl10_13_8004A170();
        var_s0_4 += 1;
    } while (var_s0_4 < 0xA);
    func_ovl10_13_8004A148(0x1E);
    temp_v1_4 = temp_s2->unk40;
    func_ovl10_13_80049E18(temp_v1_4->unk10, temp_v1_4->unk14, temp_v1_4->unk18);
    func_ovl10_13_80049E38(204.0f, 25.1f, 722.0f);
    var_fa0 = 0.0f;
    var_s0_5 = 0;
    do {
        sp4C = var_fa0;
        temp_v1_5 = temp_s2->unk40;
        temp_fv1_2 = var_fa0 + 5.0f;
        temp_v1_5->unk14 += func_ovl10_13_8004A2D8(var_fa0) * 1.8f;
        if (temp_fv1_2 >= 360.0f) {
            var_fa0_2 = temp_fv1_2 - 360.0f;
        } else {
            if (temp_fv1_2 < 0.0f) {
                var_fv0_2 = temp_fv1_2 + 360.0f;
            } else {
                var_fv0_2 = temp_fv1_2;
            }
            var_fa0_2 = var_fv0_2;
        }
        sp4C = var_fa0_2;
        func_ovl10_13_8004A170();
        var_s0_5 += 1;
        var_fa0 = var_fa0_2;
    } while (var_s0_5 < 0x78);
    func_ovl10_13_80049DF8(1);
    func_ovl10_13_80049E08(0);
    sp44 = func_ovl10_13_8004A128(func_ovl10_13_80048F00, temp_s2, 0, 0, 0x130);
    sp40 = func_ovl10_13_8004A128(func_ovl10_13_80048EA8, temp_s2, 0, 0, 0x130);
    temp_s1 = temp_s2->unk40;
    var_s0_6 = 0;
    do {
        temp_fv0 = temp_s1->unk1C;
        temp_fv1_3 = temp_fv0 - 0.6666667f;
        if (temp_fv1_3 >= 360.0f) {
            temp_s1->unk1C = temp_fv1_3 - 360.0f;
        } else {
            if (temp_fv0 < 0.6666667f) {
                var_fv0_3 = temp_fv1_3 + 360.0f;
            } else {
                var_fv0_3 = temp_fv1_3;
            }
            temp_s1->unk1C = var_fv0_3;
        }
        temp_fv1_4 = temp_s1->unk20 + 3.0f;
        if (temp_fv1_4 >= 360.0f) {
            temp_s1->unk20 = temp_fv1_4 - 360.0f;
        } else {
            if (temp_fv1_4 < 0.0f) {
                var_fv0_4 = temp_fv1_4 + 360.0f;
            } else {
                var_fv0_4 = temp_fv1_4;
            }
            temp_s1->unk20 = var_fv0_4;
        }
        func_ovl10_13_8004A170();
        var_s0_6 += 1;
    } while (var_s0_6 < 0x1E);
    func_ovl10_13_80049E28(2927.0f, 2951.0f, 1300.0f);
    var_s0_7 = 0;
    do {
        temp_fv0_2 = temp_s1->unk1C;
        temp_fv1_5 = temp_fv0_2 - 2.3333333f;
        if (temp_fv1_5 >= 360.0f) {
            temp_s1->unk1C = temp_fv1_5 - 360.0f;
        } else {
            if (temp_fv0_2 < 2.3333333f) {
                var_fv0_5 = temp_fv1_5 + 360.0f;
            } else {
                var_fv0_5 = temp_fv1_5;
            }
            temp_s1->unk1C = var_fv0_5;
        }
        func_ovl10_13_8004A170();
        var_s0_7 += 1;
    } while (var_s0_7 < 0x1E);
    var_s0_8 = 0;
    do {
        temp_fv0_3 = temp_s1->unk1C;
        temp_fv1_6 = temp_fv0_3 - 3.0f;
        if (temp_fv1_6 >= 360.0f) {
            temp_s1->unk1C = temp_fv1_6 - 360.0f;
        } else {
            if (temp_fv0_3 < 3.0f) {
                var_fv0_6 = temp_fv1_6 + 360.0f;
            } else {
                var_fv0_6 = temp_fv1_6;
            }
            temp_s1->unk1C = var_fv0_6;
        }
        func_ovl10_13_8004A170();
        var_s0_8 += 1;
    } while (var_s0_8 < 0x1E);
    func_ovl10_13_8004A148(0x1E);
    var_s0_9 = 0;
    do {
        temp_fv1_7 = temp_s1->unk20 + 0.33333334f;
        if (temp_fv1_7 >= 360.0f) {
            temp_s1->unk20 = temp_fv1_7 - 360.0f;
        } else {
            if (temp_fv1_7 < 0.0f) {
                var_fv0_7 = temp_fv1_7 + 360.0f;
            } else {
                var_fv0_7 = temp_fv1_7;
            }
            temp_s1->unk20 = var_fv0_7;
        }
        func_ovl10_13_8004A170();
        var_s0_9 += 1;
    } while (var_s0_9 < 0x1E);
    var_s0_10 = 0;
    do {
        temp_fv0_4 = temp_s1->unk1C;
        temp_fv1_8 = temp_fv0_4 - 5.0f;
        if (temp_fv1_8 >= 360.0f) {
            temp_s1->unk1C = temp_fv1_8 - 360.0f;
        } else {
            if (temp_fv0_4 < 5.0f) {
                var_fv0_8 = temp_fv1_8 + 360.0f;
            } else {
                var_fv0_8 = temp_fv1_8;
            }
            temp_s1->unk1C = var_fv0_8;
        }
        func_ovl10_13_8004A170();
        var_s0_10 += 1;
    } while (var_s0_10 < 0x1E);
    func_ovl10_13_80049E28(1282.0f, 1408.0f, 2745.0f);
    func_ovl10_13_8004A170();
    func_ovl10_13_8004A128(func_ovl10_13_80048CEC, temp_s2, 0, 0, 0x130);
    var_s0_11 = 0;
    do {
        temp_fv0_5 = temp_s1->unk20;
        temp_fv1_9 = temp_fv0_5 - 0.5f;
        if (temp_fv1_9 >= 360.0f) {
            temp_s1->unk20 = temp_fv1_9 - 360.0f;
        } else {
            if (temp_fv0_5 < 0.5f) {
                var_fv0_9 = temp_fv1_9 + 360.0f;
            } else {
                var_fv0_9 = temp_fv1_9;
            }
            temp_s1->unk20 = var_fv0_9;
        }
        temp_fv0_6 = temp_s1->unk1C;
        temp_fv1_10 = temp_fv0_6 - 0.16666667f;
        if (temp_fv1_10 >= 360.0f) {
            temp_s1->unk1C = temp_fv1_10 - 360.0f;
        } else {
            if (temp_fv0_6 < 0.16666667f) {
                var_fv0_10 = temp_fv1_10 + 360.0f;
            } else {
                var_fv0_10 = temp_fv1_10;
            }
            temp_s1->unk1C = var_fv0_10;
        }
        func_ovl10_13_8004A170();
        var_s0_11 += 1;
    } while (var_s0_11 < 0x3C);
    func_ovl10_13_8004A130(sp40);
    func_ovl10_13_80049E28(3811.0f, 384.0f, 3048.0f);
    func_ovl10_13_8004A128(func_ovl10_13_80048BBC, NULL, 0, 0, 0x130);
    var_s0_12 = 0;
    do {
        temp_fv0_7 = temp_s1->unk20;
        temp_fv1_11 = temp_fv0_7 - 3.3333333f;
        if (temp_fv1_11 >= 360.0f) {
            temp_s1->unk20 = temp_fv1_11 - 360.0f;
        } else {
            if (temp_fv0_7 < 3.3333333f) {
                var_fv0_11 = temp_fv1_11 + 360.0f;
            } else {
                var_fv0_11 = temp_fv1_11;
            }
            temp_s1->unk20 = var_fv0_11;
        }
        temp_fv0_8 = temp_s1->unk1C;
        temp_fv1_12 = temp_fv0_8 - 2.6666667f;
        if (temp_fv1_12 >= 360.0f) {
            temp_s1->unk1C = temp_fv1_12 - 360.0f;
        } else {
            if (temp_fv0_8 < 2.6666667f) {
                var_fv0_12 = temp_fv1_12 + 360.0f;
            } else {
                var_fv0_12 = temp_fv1_12;
            }
            temp_s1->unk1C = var_fv0_12;
        }
        func_ovl10_13_8004A170();
        var_s0_12 += 1;
    } while (var_s0_12 < 0x1E);
    func_ovl10_13_8004A148(0xB4);
    func_ovl10_13_8004A130(sp44);
    if (D_ovl10_13_8004ADA8 == 0x1A) {
        func_ovl10_13_8004A130(func_ovl10_13_8004A770(2)->unkA0.w);
        func_ovl10_13_8004A828();
        D_ovl10_13_8004ADB4 = 0;
        func_ovl10_13_8004A138();
    }
    func_ovl10_13_80049E18(2350.0f, 0.0f, 1500.0f);
    func_ovl10_13_80049E08(1);
    func_ovl10_13_80049E38(0.0f, 30.0f, 1573.0f);
    var_s0_13 = 0;
    do {
        temp_v0_4 = sp5C->unk40;
        temp_fv1_13 = temp_v0_4->unk20 + 18.0f;
        if (temp_fv1_13 >= 360.0f) {
            temp_v0_4->unk20 = temp_fv1_13 - 360.0f;
        } else {
            if (temp_fv1_13 < 0.0f) {
                var_fv0_13 = temp_fv1_13 + 360.0f;
            } else {
                var_fv0_13 = temp_fv1_13;
            }
            temp_v0_4->unk20 = var_fv0_13;
        }
        func_ovl10_13_8004A170();
        var_s0_13 += 1;
    } while (var_s0_13 < 0xA);
    func_ovl10_13_80049868(0, 3);
    var_s0_14 = 0;
    do {
        temp_v0_5 = sp5C->unk40;
        temp_v0_5->unk18 -= 8.0f;
        func_ovl10_13_8004A170();
        var_s0_14 += 8;
    } while (var_s0_14 < 0xC8);
    func_ovl10_13_80049868(0, 0);
    temp_s2->unk40->unk10 = 2600.0f;
    temp_s2->unk40->unk14 = 400.0f;
    temp_s2->unk40->unk18 = 1200.0f;
    temp_s2->unk40->unk1C = 0.0f;
    temp_s2->unk40->unk20 = 0.0f;
    temp_s2->unk40->unk24 = 0.0f;
    func_ovl10_13_8004A6B0(0x278);
    var_s0_15 = 0;
    do {
        temp_v1_6 = temp_s2->unk40;
        temp_v1_6->unk14 -= 1.6666666f;
        func_ovl10_13_8004A170();
        var_s0_15 += 1;
    } while (var_s0_15 < 0xF0);
    func_ovl10_13_8004A148(0x3C);
    temp_v0_6 = func_ovl10_13_80049CB8(0x2D4, 0);
    temp_v0_6->unkC |= 0x80;
    temp_v0_6->unk36 = 0x5A;
    temp_v0_6->unk10 = 2100.0f;
    temp_v0_6->unk14 = 400.0f;
    temp_v0_6->unk18 = 1200.0f;
    temp_v0_6->unk2C = 200.0f;
    func_ovl10_13_8004A6D0(0x245, 2100.0f, 400.0f, 1200.0f);
    var_s0_16 = 0;
    do {
        temp_v0_6->unk14 -= 2.2222223f;
        func_ovl10_13_8004A170();
        var_s0_16 += 1;
    } while (var_s0_16 < 0xB4);
    temp_v0_6->unk14 = 0.0f;
    func_ovl10_13_8004A758(1, 4, 0x15, 0, 0xC);
    func_ovl10_13_8004A778(0);
    temp_v0_7 = func_ovl10_13_80049818(1);
    sp54 = temp_v0_7;
    temp_v0_7->unk40->unk14 = 800.0f;
    temp_v0_8 = func_ovl10_13_8004A770(1);
    temp_v0_8->unk90 = 0x3C;
    func_ovl10_13_8004A140(temp_v0_8->unkA0.h.lo, 0);
    func_ovl10_13_80049848(1);
    func_ovl10_13_800497C8(1);
    func_ovl10_13_80049848(0);
    func_ovl10_13_8004A170();
    func_ovl10_13_80049DF8(1);
    func_ovl10_13_80049E08(0);
    func_ovl10_13_80049E28(2327.0f, 632.0f, 1807.0f);
    var_s0_17 = 0;
    if (0.0f < 360.0f) {
        do {
            temp_v0_9 = sp54->unk40;
            temp_v0_9->unk14 -= 2.2222223f;
            if (var_s0_17 < 0xF0) {
                temp_v0_10 = sp54->unk40;
                func_ovl10_13_80049E18(temp_v0_10->unk10, temp_v0_10->unk14, temp_v0_10->unk18);
            }
            if (var_s0_17 == 0xF0) {
                func_ovl10_13_80049E08(1);
                func_ovl10_13_80049E78(0x10);
                func_ovl10_13_80049E80(0xF);
                func_ovl10_13_8004A778(1);
            }
            func_ovl10_13_8004A170();
            var_s0_17 += 1;
        } while ((f32) var_s0_17 < 360.0f);
        var_s0_17 = 0;
    }
    sp54->unk40->unk14 = 0.0f;
    do {
        temp_v0_6->unk36 = (s16) (s32) ((f32) temp_v0_6->unk36 - 3.0f);
        func_ovl10_13_8004A170();
        var_s0_17 += 1;
    } while (var_s0_17 != 0x1E);
    func_ovl10_13_80049CC0(temp_v0_6);
    func_ovl10_13_80049848(1);
    func_ovl10_13_800497C8(0);
    func_ovl10_13_80049848(2);
    func_ovl10_13_800497C8(0);
    func_ovl10_13_80049848(0);
    D_ovl10_13_8004ADB4 = 0;
    func_ovl10_13_8004A188(func_ovl10_13_8004A770(1)->unkA0.h.lo);
    func_ovl10_13_8004A188(func_ovl10_13_8004A770(2)->unkA0.h.lo);
    func_ovl10_13_8004A138();
    func_ovl10_13_80049E78(0x10);
}

void func_ovl10_13_800478D4(void) {
    UnkStructA *temp_s0;
    UnkStructA_40_48_4 *temp_v0;

    func_ovl10_13_8004A148(0x1E);
    temp_s0 = func_ovl10_13_80049818(1);
    func_ovl10_13_8004A6B0(0x1BE);
    func_ovl10_13_8004A148(0x46);
    func_ovl10_13_80049D00(temp_s0->unk40, 0x22, 0);
    func_ovl10_13_80049D00(temp_s0->unk40, -1, 1);
    temp_v0 = temp_s0->unk40->unk48->unk4;
    temp_v0->unk8 |= 0x20;
    if (!(temp_s0->unk40->unk48->unk4->unk8 & 0x40)) {
        do {
            func_ovl10_13_8004A170();
        } while (!(temp_s0->unk40->unk48->unk4->unk8 & 0x40));
    }
    func_ovl10_13_8004A148(0x1E);
    func_ovl10_13_8004A6C0(0xD);
    func_ovl10_13_80049E08(1);
    func_ovl10_13_80049E78(0x10);
    func_ovl10_13_80049E80(0xF);
    func_ovl10_13_8004A778(1);
    func_ovl10_13_8004A148(0x3C);
    D_ovl10_13_8004ADB4 = 0;
    temp_s0->unk70 = 1.6333334f;
    func_ovl10_13_8004A138();
}

void func_ovl10_13_800477E8(void) {
    func_ovl10_13_8004A130(func_ovl10_13_8004A770(1)->unkA0.w);
    func_ovl10_13_8004A130(func_ovl10_13_8004A770(2)->unkA0.w);
    func_ovl10_13_8004574C();
}

void func_ovl10_13_800475F8(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40_48_4 *temp_v0_3;

    func_ovl10_13_8004A130(func_ovl10_13_8004A770(1)->unkA0.w);
    temp_v0 = func_ovl10_13_80049818(1);
    temp_v0->unk70 = 0.0f;
    temp_v0->unk68 = 0.0f;
    func_ovl10_13_80049848(1);
    func_ovl10_13_800497C8(1);
    func_ovl10_13_80049848(0);
    func_ovl10_13_80049E80(0x1F);
    func_ovl10_13_8004A778(0);
    temp_v0_2 = temp_v0->unk40;
    func_ovl10_13_80049E18(temp_v0_2->unk10 + 30.0f, 100.0f, temp_v0_2->unk18);
    func_ovl10_13_80049E38(0.0f, 20.0f, 800.0f);
    func_ovl10_13_80049D00(temp_v0->unk40, 0x14, 0);
    func_ovl10_13_80049D00(temp_v0->unk40, -1, 1);
    temp_v0_3 = temp_v0->unk40->unk48->unk4;
    temp_v0_3->unk8 |= 0x20;
    if (!(temp_v0->unk40->unk48->unk4->unk8 & 0x40)) {
        do {
            func_ovl10_13_8004A170();
        } while (!(temp_v0->unk40->unk48->unk4->unk8 & 0x40));
    }
    func_ovl10_13_80044E48();
}

void func_ovl10_13_800474EC(void) {
    D_ovl10_13_8004ADC4 = func_ovl10_13_80049818(1);
    D_ovl10_13_8004ADC0 = func_ovl10_13_80049818(0);
    func_ovl10_13_8004A130(func_ovl10_13_8004A770(1)->unkA0.w);
    func_ovl10_13_80049E80(0x1F);
    func_ovl10_13_8004A778(0);
    D_ovl10_13_8004ADE4 = 0;
    func_ovl10_13_80043070();
}

void func_ovl10_13_80047418(void) {
    UnkStructA *temp_s1;
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_2;
    UnkStructA_40 *temp_v1_3;
    s32 temp_s2;
    s32 var_s0;

    temp_s1 = func_ovl10_13_8004A150();
    func_ovl10_13_8004A148(0x78);
    temp_v1 = temp_s1->unk40;
    temp_s2 = func_ovl10_13_8004A6D0(0x213, temp_v1->unk10, temp_v1->unk14, temp_v1->unk18);
    var_s0 = 0;
    do {
        temp_v1_2 = temp_s1->unk40;
        temp_v1_2->unk10 -= 50.0f;
        temp_v1_3 = temp_s1->unk40;
        func_ovl10_13_8004A700(temp_s2, temp_v1_3->unk10, temp_v1_3->unk14, temp_v1_3->unk18);
        func_ovl10_13_8004A170();
        var_s0 += 1;
    } while (var_s0 != 0x28);
    func_ovl10_13_8004A138();
}

void func_ovl10_13_80047298(void) {
    UnkStructA *temp_s1;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 var_s0;

    var_fs0 = 0.0f;
    temp_s1 = func_ovl10_13_8004A150();
loop_1:
    var_s0 = 0;
    do {
        if ((func_ovl10_13_8004A2D0(var_fs0) * 0.5f) < 0.0f) {
            var_fv1 = -(func_ovl10_13_8004A2D0(var_fs0) * 0.5f);
        } else {
            var_fv1 = func_ovl10_13_8004A2D0(var_fs0) * 0.5f;
        }
        func_ovl10_13_8004A740(temp_s1->unk40, 0x1F, 0x1F, 0x1F, var_fv1);
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
        func_ovl10_13_8004A170();
        var_s0 += 1;
    } while (var_s0 != 0x3C);
    goto loop_1;
}

void func_ovl10_13_800470C8(void) {
    UnkStructA **objs;
    UnkStructA *a;
    UnkStructA *b;
    s32 red;
    s32 green;
    s32 blue;
    f32 angle;
    f32 temp;

    objs = func_ovl10_13_8004A150();
    a = objs[0];
    b = objs[1];
    angle = 0.0f;
    while (TRUE) {
        red = func_ovl10_13_8004A2E8(31);
        green = func_ovl10_13_8004A2E8(31);
        blue = func_ovl10_13_8004A2E8(31);
        func_ovl10_13_8004A740(a->unk40, red, green, blue,
                               func_ovl10_13_8004A2D0(angle) < 0.0f ? -func_ovl10_13_8004A2D0(angle) : func_ovl10_13_8004A2D0(angle));
        func_ovl10_13_8004A740(b->unk40, red, green, blue,
                               func_ovl10_13_8004A2D0(angle) < 0.0f ? -func_ovl10_13_8004A2D0(angle) : func_ovl10_13_8004A2D0(angle));
        temp = angle + 20.0f;
        angle = temp >= 360.0f ? temp - 360.0f : temp < 0.0f ? temp + 360.0f : temp;
        func_ovl10_13_8004A148(4);
    }
}

void func_ovl10_13_80046E88(void) {
    Vec3f *pos;
    UnkStructA_40 *p;
    s32 i;

    pos = func_ovl10_13_8004A150();
    p = func_ovl10_13_80049CB8(0x302, 0);
    p->unkC |= 0x80;
    p->unk36 = 0;
    p->unk10 = pos->x + 50.0f;
    p->unk14 = func_ovl10_13_8004A2E0() * 100.0 + (pos->y - 50.0f) + 50.0;
    p->unk18 = func_ovl10_13_8004A2E0() * 100.0 + (pos->z - 50.0f);
    p->unk28 = 0.3f;
    p->unk2C = 0.3f;
    p->unk30 = 0.3f;
    for (i = 0; i < 30; i++) {
        p->unk36 += 4.266667f;
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
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049CC0(p);
    func_ovl10_13_8004A138();
}

/* Defined above its caller 80046E50, as in ovl_10_12. */
s32 func_ovl10_13_80046DD8(void (*arg0)()) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_13_8004ACA0[i] == NULL) {
            D_ovl10_13_8004ACA0[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_13_80049298("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_13_80046E50(void (*arg0)(), const char *arg1) {
    s32 i;

    i = func_ovl10_13_80046DD8(arg0);
    func_ovl10_13_80049298("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_13_80046DAC(void (*arg0)()) {
    D_ovl10_13_8004ACA0[func_ovl10_13_80046D68(arg0)] = NULL;
}

s32 func_ovl10_13_80046D68(void (*arg0)()) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_13_8004ACA0[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_13_80046D4C(void) {
    D_ovl10_13_8004ACA0[D_ovl10_13_8004AC98] = NULL;
}

void func_ovl10_13_80046D38(s32 arg0) {
    D_ovl10_13_8004ACA0[arg0] = NULL;
}

void func_ovl10_13_80046D1C(s32 arg0) {
    D_ovl10_13_8004AB98[D_ovl10_13_8004AC98] = arg0;
}

void func_ovl10_13_80046D00(void (*arg0)()) {
    D_ovl10_13_8004ACA0[D_ovl10_13_8004AC98] = arg0;
}

void func_ovl10_13_80046C70(s32 arg0) {
    D_ovl10_13_8004ADA0 = func_ovl10_13_8004A1B0(arg0);
    func_ovl10_13_8004A1C0(D_ovl10_13_8004ADA0, 0x20000001);
    D_ovl10_13_8004ADA0->unk40 = 0.5f;
    D_ovl10_13_8004ADA0->unk44 = D_ovl10_13_8004ADA0->unk40 * 0.75f;
    D_ovl10_13_8004ADA0->unk18 = 0.1f;
    D_ovl10_13_8004ADA0->unk1C = -0.1f;
}

void func_ovl10_13_80046BF4(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_13_8004ACA0[i] = NULL;
        D_ovl10_13_8004AB98[i] = 0;
    }
    func_ovl10_13_8004A128(func_ovl10_13_80049044, 0, 0, 0, 0x110);
}

void func_ovl10_13_80046BB8(void) {
    s32 *p;

    p = func_ovl10_13_8004A3C0();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_13_80046B4C(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_13_80049E80(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_13_8004A058(arg0);
        func_ovl10_13_8004A170();
    }
}

void func_ovl10_13_80046ACC(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_13_8004A428(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_13_80049FE0(arg0, 0x01000000);
        func_ovl10_13_8004A148(5);
        func_ovl10_13_8004A428(0, 0, 0, 0.0f);
        func_ovl10_13_8004A0A8(arg0, &pos);
        func_ovl10_13_8004A580(12, &pos.x, 0);
    }
}

void func_ovl10_13_800468BC(void) {
    UnkStructA_40 *temp_v0;

    D_ovl10_13_8004ADA8 = func_ovl10_13_800496D8();
    D_ovl10_13_8004ADBC = 0;
    func_ovl10_13_800495D8(0x1FA);
    D_ovl10_13_8004ADAC = func_ovl10_13_80049CB8(0x1FC, 0);
    D_ovl10_13_8004ADAC->unkC |= 0x80;
    func_ovl10_13_800495F0(0x1FB);
    func_ovl10_13_80049788();
    D_ovl10_13_8004ADB4 = 1;
    D_ovl10_13_8004ADB8 = 0;
    func_ovl10_13_8004A348();
}

void func_ovl10_13_80046750(void) {
    UnkStructA *temp_v0_2;
    UnkStructA_40 *temp_v1;
    UnkStruct_ovl10_13_8004A770 *temp_v0;

    func_ovl10_13_80049790(0x17, 0, 0x20);
    func_ovl10_13_800497D0(0);
    func_ovl10_13_8004A758(2, 5, 0x17, 0, 0x29);
    func_ovl10_13_8004A778(0);
    temp_v0 = func_ovl10_13_8004A770(2);
    temp_v0->unk90 = 0x3C;
    func_ovl10_13_8004A140(temp_v0->unkA0.h.lo, 0);
    temp_v0_2 = func_ovl10_13_80049818(2);
    temp_v0_2->unk40->unk10 = 2350.0f;
    temp_v0_2->unk40->unk14 = 600.0f;
    temp_v0_2->unk40->unk18 = 4100.0f;
    temp_v0_2->unk40->unk1C = 90.0f;
    temp_v0_2->unk40->unk20 = 180.0f;
    func_ovl10_13_80049848(2);
    func_ovl10_13_800497C8(1);
    func_ovl10_13_80049848(0);
    temp_v1 = func_ovl10_13_80049818(0)->unk40;
    temp_v1->unk10 += 50.0f;
    func_ovl10_13_800497E8();
    func_ovl10_13_80049E80(0x1F);
    func_ovl10_13_80049E18(2282.0f, -20.0f, 2811.0f);
    func_ovl10_13_80049E38(46.0f, 32.0f, 2000.0f);
    func_ovl10_13_80049760(0x74, 0x11);
    D_ovl10_13_8004ADB0 = func_ovl10_13_80049CB8(0x200, 0);
    func_ovl10_13_800497C8(1);
}

void func_ovl10_13_800466B8(void) {
    UnkStructA_40 *temp_v1;

    func_ovl10_13_8004A758(1, 4, 0x15, 0, 0xC);
    func_ovl10_13_8004A758(2, 5, 0x1A, 0, 0xC);
    func_ovl10_13_80049790(0x17, 0, 0x12);
    func_ovl10_13_800497D0(0);
    temp_v1 = func_ovl10_13_80049818(0)->unk40;
    temp_v1->unk10 += 50.0f;
    func_ovl10_13_800497E8();
    func_ovl10_13_80049E80(0xF);
}

void func_ovl10_13_800464B0(void) {
    UnkStructA *obj;
    UnkStruct_ovl10_13_8004A770 *player;
    UnkStruct_ovl10_13_80049728 *info;
    Vec3f pos;
    s32 limit;
    UnkStructA_40 *temp_v1;

    info = func_ovl10_13_80049728();
    func_ovl10_13_8004A758(1, 6, 0x17, 0, 0xC);
    func_ovl10_13_80049790(0x17, 0, 0x12);
    func_ovl10_13_800497D0(0);
    temp_v1 = func_ovl10_13_80049818(0)->unk40;
    temp_v1->unk10 += 50.0f;
    obj = func_ovl10_13_80049818(1);
    temp_v1 = obj->unk40;
    temp_v1->unk10 += 50.0f;
    temp_v1 = obj->unk40;
    temp_v1->unk14 += 800.0f;
    obj->unk68 = 0.0f;
    obj->unk70 = 0.0f;
    func_ovl10_13_80049760(0x74, 0x13);
    func_ovl10_13_800497E8();
    func_ovl10_13_80049E80(0xF);
    func_ovl10_13_8004A778(0);
    func_ovl10_13_80049E80(0x1F);
    temp_v1 = obj->unk40;
    func_ovl10_13_80049E18(temp_v1->unk10, temp_v1->unk14 + 100.0f, temp_v1->unk18);
    func_ovl10_13_80049E38(0.0f, 35.0f, 800.0f);
    player = func_ovl10_13_8004A770(1);
    if ((D_ovl10_13_8004ADA8 == 0x12) && !(player->unk124 & 8)) {
        
        if (info->unk10 == 0) {
            limit = 10000;
        } else {
            limit = 8000;
        }
        if (limit >= D_ovl10_13_8004ADD0) {
            pos.x = player->unk1C->unk40->unk10;
            pos.y = player->unk1C->unk40->unk14;
            pos.z = player->unk1C->unk40->unk18;
            func_ovl10_13_8004A358(&pos);
            player->unk124 |= 8;
            info->unk2C += 1;
        }
    }
}

void func_ovl10_13_80046324(void) {
    s32 limit;
    UnkStruct_ovl10_13_8004A770 *player;
    UnkStruct_ovl10_13_80049728 *info;
    Vec3f pos;
    UnkStructA_40 *temp_v1;

    info = func_ovl10_13_80049728();
    func_ovl10_13_8004A758(1, 6, 0x17, 0, 0xC);
    func_ovl10_13_80049790(0x17, 0, 0x12);
    func_ovl10_13_800497D0(0);
    temp_v1 = func_ovl10_13_80049818(0)->unk40;
    temp_v1->unk10 += 50.0f;
    temp_v1 = func_ovl10_13_80049818(1)->unk40;
    temp_v1->unk10 += 50.0f;
    func_ovl10_13_800497E8();
    func_ovl10_13_80049E80(0xF);
    player = func_ovl10_13_8004A770(1);
    if ((D_ovl10_13_8004ADA8 == 0x13) && !(player->unk124 & 8)) {
        if (info->unk10 == 0) {
            limit = 10000;
        } else {
            limit = 8000;
        }
        if (limit >= D_ovl10_13_8004ADD0) {
            pos.x = player->unk1C->unk40->unk10;
            pos.y = player->unk1C->unk40->unk14;
            pos.z = player->unk1C->unk40->unk18;
            func_ovl10_13_8004A358(&pos);
            player->unk124 |= 8;
            info->unk2C += 1;
        }
    }
}

void func_ovl10_13_8004621C(void) {
    switch (D_ovl10_13_8004ADA8) {
    case 16:
    case 26:
    case 27:
        func_ovl10_13_8004A128(func_ovl10_13_80047A0C, NULL, 0, 0, 0x130);
        return;
    case 18:
        func_ovl10_13_8004A128(func_ovl10_13_800478D4, NULL, 0, 0, 0x130);
        return;
    case 28:
        func_ovl10_13_8004A128(func_ovl10_13_800477E8, NULL, 0, 0, 0x130);
        return;
    case 30:
        func_ovl10_13_8004A128(func_ovl10_13_800475F8, NULL, 0, 0, 0x130);
        return;
    case 31:
        func_ovl10_13_8004A128(func_ovl10_13_800474EC, NULL, 0, 0, 0x130);
        /* fallthrough */
    default:
        return;
    }
}

void func_ovl10_13_80046168(void) {
    switch (D_ovl10_13_8004ADA8) {
    case 16:
    case 18:
    case 26:
    case 27:
    case 28:
    case 31:
        if (D_ovl10_13_8004ADB4 != 0) {
            do {
                func_ovl10_13_8004A170();
            } while (D_ovl10_13_8004ADB4 != 0);
        }
        func_ovl10_13_800497C8(0);
        break;
    }
    if ((D_ovl10_13_8004ADA8 == 0x10) || (D_ovl10_13_8004ADA8 == 0x11) || (D_ovl10_13_8004ADA8 == 0x13)) {
        func_ovl10_13_8004A6C0(0x23);
    }
}

void func_ovl10_13_800460E0(void) {
    if ((D_ovl10_13_8004ADA8 == 0x1A) || (D_ovl10_13_8004ADA8 == 0x1B) || (D_ovl10_13_8004ADA8 == 0x1C) || (D_ovl10_13_8004ADA8 == 0x1D) || (D_ovl10_13_8004ADA8 == 0x1E) || (D_ovl10_13_8004ADA8 == 0x1F)) {
        func_ovl10_13_8004A830();
    }
    func_ovl10_13_80049CC0(D_ovl10_13_8004ADAC);
    if (D_ovl10_13_8004ADB8 == 0) {
        func_ovl10_13_8004A350();
    }
}

void func_ovl10_13_80046940(s32 arg0) {
    switch (arg0) {
    case 2:
        func_ovl10_13_800468BC();
        return;
    case 16:
    case 26:
    case 27:
        func_ovl10_13_80046750();
        return;
    case 17:
    case 28:
    case 29:
        func_ovl10_13_800466B8();
        return;
    case 18:
        func_ovl10_13_800464B0();
        return;
    case 19:
    case 30:
    case 31:
        func_ovl10_13_80046324();
        return;
    case 4:
        func_ovl10_13_8004621C();
        return;
    case 5:
        func_ovl10_13_80046168();
        return;
    case 1:
        func_ovl10_13_800460E0();
        return;
    case 32:
        func_ovl10_13_8004574C();
        return;
    case 11:
        func_ovl10_13_80044E48();
        return;
    case 12:
        func_ovl10_13_80043070();
        /* fallthrough */
    default:
        return;
    }
}

static void func_ovl10_13_8004574C(void) {
    UnkStructA *temp_s1;
    UnkStructA *temp_s2;
    UnkStructA *temp_s3;
    UnkStructA *temp_v0_11;
    UnkStructA_40 *temp_v0_10;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
    UnkStructA_40 *temp_v0_6;
    UnkStructA_40 *temp_v0_7;
    UnkStructA_40 *temp_v0_8;
    UnkStructA_40 *temp_v0_9;
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_10;
    UnkStructA_40 *temp_v1_2;
    UnkStructA_40 *temp_v1_3;
    UnkStructA_40 *temp_v1_4;
    UnkStructA_40 *temp_v1_5;
    UnkStructA_40 *temp_v1_6;
    UnkStructA_40 *temp_v1_7;
    UnkStructA_40 *temp_v1_8;
    UnkStructA_40 *temp_v1_9;
    UnkStructA_40_48_4 *temp_v0_12;
    UnkStruct_ovl10_13_80049728 *temp_v0;
    UnkStruct_ovl10_13_8004A770 *temp_v0_2;
    UnkStruct_ovl10_13_8004A770 *temp_v0_3;
    f32 temp_fs1;
    f32 temp_fs1_2;
    f32 temp_fs1_3;
    f32 temp_fs2;
    f32 temp_fs2_2;
    f32 temp_fs2_3;
    f32 temp_fs4;
    f32 temp_fs4_2;
    f32 temp_fv0;
    f32 var_fs0;
    f32 var_fs3;
    f32 var_fs5;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_v0;

    temp_v0 = func_ovl10_13_80049728();
    D_ovl10_13_8004ADD0 = temp_v0->unk30;
    func_ovl10_13_8004A778(0);
    func_ovl10_13_80049E80(0x1F);
    func_ovl10_13_80049868(0, 0);
    func_ovl10_13_80049868(1, 0);
    func_ovl10_13_80049848(1);
    func_ovl10_13_80049888();
    func_ovl10_13_800497C8(1);
    func_ovl10_13_80049848(2);
    func_ovl10_13_80049888();
    func_ovl10_13_800497C8(1);
    func_ovl10_13_80049848(0);
    func_ovl10_13_80049888();
    func_ovl10_13_800497C8(1);
    func_ovl10_13_8004A198(0x70, 0x70, 0);
    temp_v0_2 = func_ovl10_13_8004A770(1);
    temp_v0_2->unk0 = 0;
    temp_v0_2->unk88 = -1;
    temp_v0_3 = func_ovl10_13_8004A770(2);
    temp_v0_3->unk0 = 0;
    temp_v0_3->unk88 = -1;
    if ((D_ovl10_13_8004ADA8 != 0x1C) && !(temp_v0_3->unk124 & 8)) {
        var_v0 = 0x1F40;
        if (temp_v0->unk10 == 0) {
            var_v0 = 0x2710;
        }
        if (var_v0 >= D_ovl10_13_8004ADD0) {
            func_ovl10_13_8004A358(&temp_v0_3->unk2C);
            temp_v0_3->unk124 |= 8;
            temp_v0->unk2C += 1;
        }
    }
    temp_s1 = func_ovl10_13_80049818(0);
    temp_s2 = func_ovl10_13_80049818(1);
    temp_s3 = func_ovl10_13_80049818(2);
    func_ovl10_13_80049FE0(temp_s1, 0x40000);
    func_ovl10_13_80049FE0(temp_s2, 0x40000);
    func_ovl10_13_80049FE0(temp_s3, 0x40000);
    if (D_ovl10_13_8004ADA8 != 0x1C) {
        func_ovl10_13_80049778(0x12C);
        func_ovl10_13_8004A6C8();
    }
    func_ovl10_13_8004A6B0(0x24C);
    temp_s2->unk70 = 0.0f;
    temp_s2->unk6C = 0.0f;
    temp_s2->unk68 = 0.0f;
    temp_s2->unk40->unk20 = 0.0f;
    temp_s3->unk68 = 0.0f;
    temp_s3->unk6C = 0.0f;
    temp_s3->unk70 = 0.0f;
    temp_s3->unk40->unk20 = 0.0f;
    func_ovl10_13_80049FE0(temp_s1, 0x40000);
    func_ovl10_13_80049FE0(temp_s2, 0x40000);
    func_ovl10_13_80049FE0(temp_s3, 0x40000);
    temp_v0_4 = temp_s2->unk40;
    func_ovl10_13_80049E18(temp_v0_4->unk10, temp_v0_4->unk14, temp_v0_4->unk18);
    func_ovl10_13_80049E38(32768.0f, 32768.0f, 1150.0f);
    func_ovl10_13_80049E08(0);
    D_ovl10_13_8004ADDC = 0;
    if (D_ovl10_13_8004ADA8 != 0x1C) {
        D_ovl10_13_8004ADD4 = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80048850, (void *)1, 0, 0, 0x130);
        func_ovl10_13_8004A148(0x3C);
        temp_s1->unk40->unk20 = func_ovl10_13_80043010(temp_s1->unk40, temp_s2->unk40);
        temp_v0_5 = temp_s2->unk40;
        var_s0 = 0;
        temp_fs4 = (1400.0f - temp_v0_5->unk18) / 300.0f;
        temp_fs2 = (2000.0f - temp_v0_5->unk10) / 300.0f;
        temp_fs1 = (800.0f - temp_v0_5->unk14) / 300.0f;
        do {
            temp_v0_6 = temp_s2->unk40;
            temp_v0_6->unk14 += temp_fs1;
            temp_v0_7 = temp_s2->unk40;
            temp_v0_7->unk10 += temp_fs2;
            temp_v0_8 = temp_s2->unk40;
            temp_v0_8->unk18 += temp_fs4;
            temp_v0_9 = temp_s2->unk40;
            func_ovl10_13_80049E18(temp_v0_9->unk10, temp_v0_9->unk14, temp_v0_9->unk18);
            func_ovl10_13_8004A170();
            var_s0 += 1;
        } while (var_s0 < 0x12C);
        temp_s1->unk40->unk20 = func_ovl10_13_80043010(temp_s1->unk40, temp_s3->unk40);
        func_ovl10_13_80049E08(1);
        temp_v1 = temp_s3->unk40;
        func_ovl10_13_80049E18(temp_v1->unk10, temp_v1->unk14, temp_v1->unk18);
        func_ovl10_13_80049E38(32768.0f, 45.0f, 1150.0f);
        func_ovl10_13_80049E08(0);
        D_ovl10_13_8004ADD8 = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80048850, (void *)2, 0, 0, 0x130);
        func_ovl10_13_8004A148(0x3C);
        temp_v1_2 = temp_s3->unk40;
        var_s0_2 = 0;
        temp_fs4_2 = (1400.0f - temp_v1_2->unk18) / 300.0f;
        temp_fs2_2 = (2700.0f - temp_v1_2->unk10) / 300.0f;
        temp_fs1_2 = (800.0f - temp_v1_2->unk14) / 300.0f;
        do {
            temp_v1_3 = temp_s3->unk40;
            temp_v1_3->unk14 += temp_fs1_2;
            temp_v1_4 = temp_s3->unk40;
            temp_v1_4->unk10 += temp_fs2_2;
            temp_v1_5 = temp_s3->unk40;
            temp_v1_5->unk18 += temp_fs4_2;
            temp_v1_6 = temp_s3->unk40;
            func_ovl10_13_80049E18(temp_v1_6->unk10, temp_v1_6->unk14, temp_v1_6->unk18);
            func_ovl10_13_8004A170();
            var_s0_2 += 1;
        } while (var_s0_2 != 0x12C);
    } else {
        D_ovl10_13_8004ADD4 = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80048850, (void *)1, 0, 0, 0x130);
        D_ovl10_13_8004ADD8 = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80048850, (void *)2, 0, 0, 0x130);
        temp_s2->unk40->unk10 = 2000.0f;
        temp_s2->unk40->unk14 = 800.0f;
        temp_s2->unk40->unk18 = 1400.0f;
        temp_s3->unk40->unk10 = 2700.0f;
        temp_s3->unk40->unk14 = 800.0f;
        temp_s3->unk40->unk18 = 1400.0f;
    }
    func_ovl10_13_80049E08(1);
    func_ovl10_13_80049E18(2350.0f, 864.0f, 1399.0f);
    func_ovl10_13_80049E38(314.0f, 32.0f, 1438.0f);
    var_s0_3 = 0;
    temp_fs1_3 = (2350.0f - temp_s3->unk40->unk10) / 300.0f;
    temp_fs2_3 = (2350.0f - temp_s2->unk40->unk10) / 300.0f;
    do {
        temp_v0_10 = temp_s2->unk40;
        temp_v0_10->unk10 += temp_fs2_3;
        temp_v1_7 = temp_s3->unk40;
        temp_v1_7->unk10 += temp_fs1_3;
        func_ovl10_13_8004A170();
        var_s0_3 += 1;
    } while (var_s0_3 < 0x12C);
    D_ovl10_13_8004ADDC = 0xA;
    func_ovl10_13_8004A6B0(0x24D);
    D_ovl10_13_8004ADE0 = func_ovl10_13_8004A128(func_ovl10_13_800486A8, temp_s2, 0, 0, 0x130);
    func_ovl10_13_8004A148(0x1E);
    func_ovl10_13_8004A440(0xFF, 0xFF, 0xFF, 0xAA);
    var_fs3 = 1438.0f;
    var_fs0 = 314.0f;
    var_s0_4 = 0;
    do {
        if (var_s0_4 == 0xAA) {
            func_ovl10_13_8004A6B0(0x250);
        }
        func_ovl10_13_80049E38(var_fs0, 32768.0f, var_fs3);
        temp_fv0 = var_fs0 + 0.15555556f;
        if (temp_fv0 >= 360.0f) {
            var_fs0 = temp_fv0 - 360.0f;
        } else {
            if (temp_fv0 < 0.0f) {
                var_fs5 = temp_fv0 + 360.0f;
            } else {
                var_fs5 = temp_fv0;
            }
            var_fs0 = var_fs5;
        }
        var_fs3 -= 6.311111f;
        func_ovl10_13_8004A170();
        var_s0_4 += 1;
    } while (var_s0_4 != 0xB4);
    D_ovl10_13_8004ADE0 = 0;
    D_ovl10_13_8004ADD8 = 0;
    D_ovl10_13_8004ADD4 = 0;
    func_ovl10_13_8004A170();
    func_ovl10_13_80049778(0x20);
    if (D_ovl10_13_8004ADA8 == 0x1C) {
        func_ovl10_13_8004A420();
        func_ovl10_13_80049FE0(temp_s2, 0x01000000);
        func_ovl10_13_80049FE0(temp_s3, 0x01000000);
        temp_s3->unk40->unk10 = 5000.0f;
        func_ovl10_13_8004A758(3, 6, 0x17, 0, 0xC);
        func_ovl10_13_8004A778(0);
        temp_v0_11 = func_ovl10_13_80049818(3);
        temp_v1_8 = temp_v0_11->unk40;
        temp_v1_8->unk10 += 50.0f;
        temp_v1_9 = temp_v0_11->unk40;
        temp_v1_9->unk14 += 800.0f;
        temp_v0_11->unk68 = 0.0f;
        temp_v0_11->unk70 = 0.0f;
        func_ovl10_13_8004A130(func_ovl10_13_8004A770(3)->unkA0.w);
        temp_v1_10 = temp_v0_11->unk40;
        func_ovl10_13_80049E18(temp_v1_10->unk10, temp_v1_10->unk14 + 100.0f, temp_v1_10->unk18);
        func_ovl10_13_80049E38(0.0f, 20.0f, 600.0f);
        func_ovl10_13_8004A430(0xFF, 0xFF, 0xFF, 0x78);
        func_ovl10_13_8004A420();
        func_ovl10_13_80049D00(temp_v0_11->unk40, 0x22, 0);
        func_ovl10_13_80049D00(temp_v0_11->unk40, -1, 1);
        temp_v0_12 = temp_v0_11->unk40->unk48->unk4;
        temp_v0_12->unk8 |= 0x20;
        if (!(temp_v0_11->unk40->unk48->unk4->unk8 & 0x40)) {
            do {
                func_ovl10_13_8004A170();
            } while (!(temp_v0_11->unk40->unk48->unk4->unk8 & 0x40));
        }
        func_ovl10_13_8004A828();
        D_ovl10_13_8004ADB4 = 0;
        func_ovl10_13_8004A138();
    }
    func_ovl10_13_800496D0(0x74, 0x12, 5);
loop_32:
    func_ovl10_13_8004A170();
    goto loop_32;
}

static void func_ovl10_13_80044E48(void) {
    Vec3f from;
    Vec3f to;
    f32 angle;
    UnkStructA *temp_v0_5;
    UnkStructA_40 *temp_v0_10;
    UnkStructA_40 *temp_v0_11;
    UnkStructA_40 *temp_v0_12;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_6;
    UnkStructA_40 *temp_v0_7;
    UnkStructA_40 *temp_v0_8;
    UnkStructA_40 *temp_v0_9;
    UnkStructA_40 *temp_v1;
    UnkStructA_40 *temp_v1_2;
    UnkStructA_40 *temp_v1_3;
    UnkStructA_40 *temp_v1_4;
    UnkStructA_40 *temp_v1_5;
    UnkStructA_40_48_4 *temp_v0;
    f32 temp_ft0;
    f32 temp_fv1;
    f32 var_fs0;
    f32 var_fv0;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;

    func_ovl10_13_800497C8(1);
    if (D_ovl10_13_8004ADA8 != 0x1E) {
        func_ovl10_13_80049E80(0x1F);
        func_ovl10_13_8004A778(0);
        func_ovl10_13_80049E18(2350.0f, 100.0f, 1720.0f);
        func_ovl10_13_80049E38(0.0f, 45.0f, 2000.0f);
    }
    func_ovl10_13_8004A148(2);
    D_ovl10_13_8004ADC4 = func_ovl10_13_80049818(1);
    D_ovl10_13_8004ADC0 = func_ovl10_13_80049818(0);
    func_ovl10_13_80049FE0(D_ovl10_13_8004ADC4, 0x0C000000);
    D_ovl10_13_8004ADC4->unk40->unk20 = func_ovl10_13_80043010(D_ovl10_13_8004ADC4->unk40, D_ovl10_13_8004ADC0->unk40);
    if ((func_ovl10_13_80049770(1) == 3) && (D_ovl10_13_8004ADA8 != 0x1E)) {
        func_ovl10_13_80049D00(D_ovl10_13_8004ADC4->unk40, 0x14, 0);
        func_ovl10_13_80049D00(D_ovl10_13_8004ADC4->unk40, -1, 1);
        temp_v0 = D_ovl10_13_8004ADC4->unk40->unk48->unk4;
        temp_v0->unk8 |= 0x40;
        D_ovl10_13_8004ADC4->unk40->unk48->unk4->unk4 = func_ovl10_13_80049D18(D_ovl10_13_8004ADC4->unk40, 0) - 0.01f;
        from.x = D_ovl10_13_8004ADC0->unk40->unk10;
        from.y = D_ovl10_13_8004ADC0->unk40->unk14;
        to.y = 0.0f;
        to.x = 2350.0f;
        to.z = 1550.0f;
        from.z = D_ovl10_13_8004ADC0->unk40->unk18;
        func_ovl10_13_80049F68(&from, &to, &angle);
        temp_ft0 = func_ovl10_13_8004A2D0(angle) * 800.0f;
        to.y = from.y;
        to.x = temp_ft0 + from.x;
        to.z = (func_ovl10_13_8004A2D8(angle) * 800.0f) + from.z;
        from.x = D_ovl10_13_8004ADC4->unk40->unk10;
        from.y = D_ovl10_13_8004ADC4->unk40->unk14;
        from.z = D_ovl10_13_8004ADC4->unk40->unk18;
        func_ovl10_13_80049F68(&from, &to, &angle);
        func_ovl10_13_80049F80(&from, &to);
        D_ovl10_13_8004ADC4->unk68 = 51.0f;
        D_ovl10_13_8004ADC4->unk40->unk14 = 0.1f;
        D_ovl10_13_8004ADC4->unk70 = 0.8166667f;
        var_s0 = 0;
        D_ovl10_13_8004ADC4->unk6C = 16.333334f;
        do {
            temp_v0_2 = D_ovl10_13_8004ADC4->unk40;
            temp_v0_2->unk10 += (to.x - from.x) / 90.0f;
            temp_v0_3 = D_ovl10_13_8004ADC4->unk40;
            temp_v0_3->unk18 += (to.z - from.z) / 90.0f;
            if (D_ovl10_13_8004ADC4->unk40->unk14 < 0.0f) {
                D_ovl10_13_8004ADC4->unk70 = 0.0f;
                D_ovl10_13_8004ADC4->unk68 = D_ovl10_13_8004ADC4->unk70;
                D_ovl10_13_8004ADC4->unk40->unk14 = 0.0f;
            } else {
                func_ovl10_13_8004A058(D_ovl10_13_8004ADC4);
            }
            func_ovl10_13_8004A170();
            var_s0 += 1;
        } while (var_s0 != 0x5A);
        func_ovl10_13_8004A6B0(0x259);
    }
    D_ovl10_13_8004ADC4->unk40->unk20 = 0.0f;
    D_ovl10_13_8004ADC0->unk40->unk20 = func_ovl10_13_80043010(D_ovl10_13_8004ADC0->unk40, D_ovl10_13_8004ADC4->unk40);
    temp_v0_4 = D_ovl10_13_8004ADC4->unk40;
    func_ovl10_13_80049E18(temp_v0_4->unk10 + 30.0f, 100.0f, temp_v0_4->unk18);
    func_ovl10_13_80049E38(0.0f, 20.0f, 800.0f);
    func_ovl10_13_80049E08(0);
    func_ovl10_13_8004A148(0x1E);
    temp_v0_5 = func_ovl10_13_8004A000(0x320, 0x01000000, 0xC0, 0);
    D_ovl10_13_8004ADC8 = temp_v0_5;
    func_ovl10_13_8004A010(temp_v0_5);
    D_ovl10_13_8004ADCC = func_ovl10_13_80049D48(D_ovl10_13_8004ADC8->unk40, 0x10);
    var_s0_2 = 0;
    do {
        func_ovl10_13_80049D50(D_ovl10_13_8004ADCC, var_s0_2, 0x322);
        func_ovl10_13_80049D60(D_ovl10_13_8004ADCC, var_s0_2, var_s0_2);
        var_s0_2 += 1;
    } while (var_s0_2 < 0x10);
    D_ovl10_13_8004ADC8->unk40->unk10 = D_ovl10_13_8004ADC4->unk40->unk10 + 50.0f;
    D_ovl10_13_8004ADC8->unk40->unk14 = D_ovl10_13_8004ADC4->unk40->unk14 + 1000.0f;
    D_ovl10_13_8004ADC8->unk40->unk18 = D_ovl10_13_8004ADC4->unk40->unk18;
    func_ovl10_13_80049D00(D_ovl10_13_8004ADC8->unk40, 0xD, 0);
    func_ovl10_13_8004A6B0(0x2E5);
    var_s0_3 = 0;
    do {
        temp_v1 = D_ovl10_13_8004ADC8->unk40;
        temp_v1->unk14 -= 16.666666f;
        func_ovl10_13_8004A170();
        var_s0_3 += 1;
    } while (var_s0_3 != 0x3C);
    func_ovl10_13_8004A6B0(0x1C);
    temp_v1_2 = D_ovl10_13_8004ADC8->unk40;
    func_ovl10_13_8004A578(0xD, temp_v1_2->unk10, temp_v1_2->unk14, temp_v1_2->unk18, 0);
    D_ovl10_13_8004ADC8->unk40->unk14 = 0.0f;
    func_ovl10_13_80049FD8(D_ovl10_13_8004ADC8, 0x04000000);
    if (!(D_ovl10_13_8004ADC8->unk40->unkC & 0x40)) {
        do {
            func_ovl10_13_8004A170();
        } while (!(D_ovl10_13_8004ADC8->unk40->unkC & 0x40));
    }
    func_ovl10_13_8004A148(0x1E);
    func_ovl10_13_80049D00(D_ovl10_13_8004ADC8->unk40, 0x16, 0);
    func_ovl10_13_80049FD8(D_ovl10_13_8004ADC8, 0x04000000);
    func_ovl10_13_8004A148(7);
    func_ovl10_13_8004A6B0(0x255);
    var_s0_4 = 0;
    do {
        if (var_s0_4 == 5) {
            func_ovl10_13_80049FE0(D_ovl10_13_8004ADC8, 0x04000000);
        }
        temp_v1_3 = D_ovl10_13_8004ADC8->unk40;
        temp_v1_3->unk14 += 4.1666665f;
        if (var_s0_4 >= 8) {
            temp_v0_6 = D_ovl10_13_8004ADC4->unk40;
            temp_v0_6->unk14 += 4.1666665f;
        }
        temp_v0_7 = D_ovl10_13_8004ADC4->unk40;
        func_ovl10_13_80049E18(temp_v0_7->unk10 + 30.0f, temp_v0_7->unk14 + 100.0f, temp_v0_7->unk18);
        func_ovl10_13_8004A170();
        var_s0_4 += 1;
    } while (var_s0_4 < 0x3C);
    if (D_ovl10_13_8004ADA8 != 0x1E) {
        func_ovl10_13_80049778(0x32);
        func_ovl10_13_8004A6C8();
    }
    var_fs0 = 0.0f;
    var_s0_5 = 0;
    do {
        temp_v0_8 = D_ovl10_13_8004ADC4->unk40;
        temp_v0_8->unk14 += func_ovl10_13_8004A2D8(var_fs0) * 1.8f;
        temp_v1_4 = D_ovl10_13_8004ADC8->unk40;
        temp_fv1 = var_fs0 + 5.0f;
        temp_v1_4->unk14 += func_ovl10_13_8004A2D8(var_fs0) * 1.8f;
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
        temp_v0_9 = D_ovl10_13_8004ADC4->unk40;
        func_ovl10_13_80049E18(temp_v0_9->unk10 + 30.0f, temp_v0_9->unk14 + 100.0f, temp_v0_9->unk18);
        func_ovl10_13_8004A170();
        var_s0_5 += 1;
    } while (var_s0_5 < 0x78);
    var_s0_6 = 0;
    do {
        temp_v0_10 = D_ovl10_13_8004ADC4->unk40;
        temp_v0_10->unk14 += 8.333333f;
        temp_v1_5 = D_ovl10_13_8004ADC8->unk40;
        temp_v1_5->unk14 += 8.333333f;
        if (var_s0_6 < 0x64) {
            temp_v0_11 = D_ovl10_13_8004ADC4->unk40;
            func_ovl10_13_80049E18(temp_v0_11->unk10 + 30.0f, temp_v0_11->unk14 + 100.0f, temp_v0_11->unk18);
        }
        func_ovl10_13_8004A170();
        var_s0_6 += 1;
    } while (var_s0_6 != 0x78);
    if (D_ovl10_13_8004ADA8 == 0x1E) {
        func_ovl10_13_8004A828();
        D_ovl10_13_8004ADB4 = 0;
        func_ovl10_13_8004A138();
    }
    func_ovl10_13_80049E08(1);
    temp_v0_12 = D_ovl10_13_8004ADC0->unk40;
    func_ovl10_13_80049E18(temp_v0_12->unk10, 50.0f, temp_v0_12->unk18);
    func_ovl10_13_80049E38(D_ovl10_13_8004ADC0->unk40->unk20, 20.0f, 800.0f);
    func_ovl10_13_800497C8(0);
    D_ovl10_13_8004ADBC = 1;
    func_ovl10_13_80049778(0x20);
    func_ovl10_13_8004A350();
    D_ovl10_13_8004ADB8 = 1;
}

static void func_ovl10_13_80043070(void) {
    UnkStructA *sp94;
    UnkStructA *sp90;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_22;
    UnkStructA *temp_v0_6;
    UnkStructA_40 *temp_a0_2;
    UnkStructA_40 *temp_a0_3;
    UnkStructA_40 *temp_v0_10;
    UnkStructA_40 *temp_v0_11;
    UnkStructA_40 *temp_v0_12;
    UnkStructA_40 *temp_v0_13;
    UnkStructA_40 *temp_v0_14;
    UnkStructA_40 *temp_v0_15;
    UnkStructA_40 *temp_v0_16;
    UnkStructA_40 *temp_v0_18;
    UnkStructA_40 *temp_v0_19;
    UnkStructA_40 *temp_v0_20;
    UnkStructA_40 *temp_v0_21;
    UnkStructA_40 *temp_v0_23;
    UnkStructA_40 *temp_v0_24;
    UnkStructA_40 *temp_v0_25;
    UnkStructA_40 *temp_v0_26;
    UnkStructA_40 *temp_v0_27;
    UnkStructA_40 *temp_v0_28;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_30;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    UnkStructA_40 *temp_v0_5;
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
    UnkStructA_40 *temp_v1_17;
    UnkStructA_40 *temp_v1_18;
    UnkStructA_40 *temp_v1_19;
    UnkStructA_40 *temp_v1_20;
    UnkStructA_40 *temp_v1_21;
    UnkStructA_40 *temp_v1_22;
    UnkStructA_40 *temp_v1_23;
    UnkStructA_40 *temp_v1_24;
    UnkStructA_40 *temp_v1_25;
    UnkStructA_40 *temp_v1_26;
    UnkStructA_40 *temp_v1_27;
    UnkStructA_40 *temp_v1_28;
    UnkStructA_40 *temp_v1_29;
    UnkStructA_40 *temp_v1_2;
    UnkStructA_40 *temp_v1_30;
    UnkStructA_40 *temp_v1_31;
    UnkStructA_40 *temp_v1_32;
    UnkStructA_40 *temp_v1_33;
    UnkStructA_40 *temp_v1_3;
    UnkStructA_40 *temp_v1_4;
    UnkStructA_40 *temp_v1_5;
    UnkStructA_40 *temp_v1_6;
    UnkStructA_40 *temp_v1_7;
    UnkStructA_40 *temp_v1_8;
    UnkStructA_40 *temp_v1_9;
    UnkStructA_40_48_4 *temp_a0;
    UnkStructA_40_48_4 *temp_a0_4;
    UnkStructA_40_48_4 *temp_a0_5;
    UnkStructA_40_48_4 *temp_a0_6;
    UnkStructA_40_48_4 *temp_a0_7;
    UnkStructA_40_48_4 *temp_a0_8;
    UnkStructA_40_48_4 *temp_v0_17;
    UnkStructA_40_48_4 *temp_v0_29;
    UnkStructA_40_48_4 *temp_v0_7;
    UnkStruct_ovl10_13_80049728 *temp_s3;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs0_3;
    f32 temp_fs0_4;
    f32 temp_fs0_5;
    f32 temp_fs0_6;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv0_7;
    f32 temp_fv0_8;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    f32 var_fv1_4;
    f32 var_fv1_5;
    f32 var_fv1_6;
    f32 var_fv1_7;
    f32 var_fv1_8;
    f32 var_fv1_9;
    s32 temp_ft2;
    s32 temp_ft2_2;
    s32 temp_ft2_3;
    s32 temp_ft2_4;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_at;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s1;
    s32 var_s1_10;
    s32 var_s1_11;
    s32 var_s1_12;
    s32 var_s1_13;
    s32 var_s1_14;
    s32 var_s1_15;
    s32 var_s1_16;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s1_8;
    s32 var_s1_9;
    s32 var_s2;
    s32 var_v0;

    if ((D_ovl10_13_8004ADBC != 0) || ((D_ovl10_13_8004ADA8 == 0x1F) && (D_ovl10_13_8004ADE4 == 0))) {
        if (D_ovl10_13_8004ADA8 == 0x1F) {
            D_ovl10_13_8004ADE4 = 1;
        }
        func_ovl10_13_8004A710(0x7F);
        func_ovl10_13_8004A6F0(0x7F);
        var_s0 = 0;
        do {
            func_ovl10_13_8004A390(var_s0 + 0x2C);
            var_s0 += 1;
        } while (var_s0 < 0x64);
        var_s0_2 = 0;
        var_s2 = 0;
        do {
            var_s0_2 += 1;
            if (func_ovl10_13_8004A390(var_s0_2 + 0x2C) != 0) {
                var_s2 += 1;
            }
        } while (var_s0_2 < 0x5F);
        var_s0_3 = 0x5F;
        var_s1 = 0;
        do {
            var_s0_3 += 1;
            if (func_ovl10_13_8004A390(var_s0_3 + 0x2C) != 0) {
                var_s1 += 1;
            }
        } while (var_s0_3 < 0x64);
        temp_s3 = func_ovl10_13_80049728();
        func_ovl10_13_8004A3C0();
        var_v0 = 0;
        if (temp_s3->unk28 >= temp_s3->unk30) {
            var_v0 = 1;
        }
        var_s0_4 = var_v0 + temp_s3->unk2C;
        if (var_s0_4 < var_s1) {
            var_s0_4 = var_s1;
        }
        if ((D_ovl10_13_8004ADA8 == 0x1F) || ((func_ovl10_13_8004A390(0xA4) == 0) && ((var_s2 + var_s0_4) >= 0x64))) {
            var_s1_2 = 0;
            temp_v0 = func_ovl10_13_8004A000(0x328, 0x01000000, 0xC0, 0);
            func_ovl10_13_8004A010(temp_v0);
            func_ovl10_13_80049D00(temp_v0->unk40, 0x16, 0);
            temp_v0->unk40->unk48->unk4->unk4 = func_ovl10_13_80049D18(temp_v0->unk40, 0) - 0.01f;
            temp_v0->unk40->unk10 = D_ovl10_13_8004ADC4->unk40->unk10 + 1000.0f;
            temp_v0->unk40->unk14 = D_ovl10_13_8004ADC4->unk40->unk14 + 467.0f;
            temp_v0->unk40->unk18 = D_ovl10_13_8004ADC4->unk40->unk18;
            temp_v0->unk40->unk20 = 270.0f;
            if (D_ovl10_13_8004ADA8 != 0x1F) {
                temp_v1 = D_ovl10_13_8004ADC4->unk40;
                func_ovl10_13_80049E18(temp_v1->unk10 + 50.0f, temp_v1->unk14, temp_v1->unk18);
                func_ovl10_13_80049E38(0.0f, 60.0f, 1300.0f);
                func_ovl10_13_8004A128(func_ovl10_13_80047418, temp_v0, 0, 0, 0x130);
                func_ovl10_13_8004A6B0(0x256);
                do {
                    temp_v0_2 = D_ovl10_13_8004ADC8->unk40;
                    temp_v0_2->unk14 += 3.3333333f;
                    temp_v1_2 = D_ovl10_13_8004ADC4->unk40;
                    temp_v1_2->unk14 += 3.3333333f;
                    temp_v1_3 = D_ovl10_13_8004ADC4->unk40;
                    func_ovl10_13_80049E18(temp_v1_3->unk10 + 50.0f, temp_v1_3->unk14, temp_v1_3->unk18);
                    func_ovl10_13_8004A170();
                    var_s1_2 += 1;
                } while (var_s1_2 < 0x8C);
                func_ovl10_13_8004A6C0(0x2C);
                func_ovl10_13_8004A6B0(0x257);
                temp_v1_4 = D_ovl10_13_8004ADC4->unk40;
                func_ovl10_13_8004A578(0, temp_v1_4->unk10 + 50.0f, temp_v1_4->unk14, temp_v1_4->unk18, 0);
                D_ovl10_13_8004ADC8->unk68 = 0.0f;
                D_ovl10_13_8004ADC4->unk68 = D_ovl10_13_8004ADC8->unk68;
                D_ovl10_13_8004ADC8->unk70 = 0.8166667f;
                var_s1_3 = 0;
                D_ovl10_13_8004ADC4->unk70 = D_ovl10_13_8004ADC8->unk70;
                D_ovl10_13_8004ADC8->unk6C = 16.333334f;
                D_ovl10_13_8004ADC4->unk6C = D_ovl10_13_8004ADC8->unk6C;
                do {
                    temp_v1_5 = D_ovl10_13_8004ADC4->unk40;
                    temp_v1_5->unk10 -= 8.333333f;
                    temp_v0_3 = D_ovl10_13_8004ADC8->unk40;
                    temp_v0_3->unk10 += 8.333333f;
                    func_ovl10_13_8004A058(D_ovl10_13_8004ADC4);
                    func_ovl10_13_8004A058(D_ovl10_13_8004ADC8);
                    func_ovl10_13_8004A170();
                    var_s1_3 += 1;
                } while (var_s1_3 != 0x3C);
                D_ovl10_13_8004ADC8->unk40->unk10 = 3500.0f;
                D_ovl10_13_8004ADC8->unk40->unk14 = 900.0f;
                D_ovl10_13_8004ADC8->unk40->unk18 = 400.0f;
                D_ovl10_13_8004ADC8->unk40->unk24 = 180.0f;
                temp_v0_4 = D_ovl10_13_8004ADC8->unk40;
                func_ovl10_13_80049E18(temp_v0_4->unk10, 0.0f, temp_v0_4->unk18);
                func_ovl10_13_80049E38(337.0f, 13.0f, 2200.0f);
                var_s1_2 = 0;
            }
            D_ovl10_13_8004ADC0->unk40->unk10 = 2100.0f;
            D_ovl10_13_8004ADC0->unk40->unk14 = 0.0f;
            D_ovl10_13_8004ADC0->unk40->unk18 = 1500.0f;
            D_ovl10_13_8004ADC0->unk40->unk20 = 135.0f;
            D_ovl10_13_8004ADC4->unk40->unk10 = 2300.0f;
            D_ovl10_13_8004ADC4->unk40->unk14 = 900.0f;
            D_ovl10_13_8004ADC4->unk40->unk18 = 1300.0f;
            D_ovl10_13_8004ADC4->unk40->unk20 = 0.0f;
            func_ovl10_13_80049D00(D_ovl10_13_8004ADC4->unk40, 0x1D, 0);
            func_ovl10_13_80049D00(D_ovl10_13_8004ADC4->unk40, -1, 1);
            temp_v1_6 = D_ovl10_13_8004ADC4->unk40;
            temp_v1_6->unkC |= 0x4000;
            temp_a0 = D_ovl10_13_8004ADC4->unk40->unk48->unk4;
            temp_a0->unk8 |= 0x60;
            if (D_ovl10_13_8004ADA8 != 0x1F) {
                func_ovl10_13_8004A148(0x14);
                do {
                    temp_v0_5 = D_ovl10_13_8004ADC8->unk40;
                    temp_v0_5->unk14 -= 53.333332f;
                    func_ovl10_13_8004A170();
                    var_s1_2 += 1;
                } while (var_s1_2 != 0x1E);
                func_ovl10_13_8004A148(0x1E);
                var_s1_2 = 0;
            }
            temp_v1_7 = D_ovl10_13_8004ADC4->unk40;
            func_ovl10_13_80049E18(temp_v1_7->unk10 - 200.0f, 50.0f, temp_v1_7->unk18 + 200.0f);
            func_ovl10_13_80049E38(0.0f, 30.0f, 1800.0f);
            func_ovl10_13_8004A148(0x1E);
            do {
                temp_v1_8 = D_ovl10_13_8004ADC4->unk40;
                temp_v1_8->unk14 -= 29.0f;
                func_ovl10_13_8004A170();
                var_s1_2 += 1;
            } while (var_s1_2 < 0x1E);
            func_ovl10_13_8004A6B0(0x259);
            func_ovl10_13_8004A6B0(0x25A);
            temp_v1_9 = D_ovl10_13_8004ADC4->unk40;
            func_ovl10_13_8004A578(0xD, temp_v1_9->unk10, temp_v1_9->unk14, temp_v1_9->unk18, 0);
            D_ovl10_13_8004ADC4->unk40->unk14 = 0.0f;
            temp_v0_6 = func_ovl10_13_8004A000(0x346, 0x01080000, 0xC0, 0);
            func_ovl10_13_8004A010(temp_v0_6);
            temp_v0_6->unk40->unk10 = D_ovl10_13_8004ADC4->unk40->unk10;
            temp_v0_6->unk40->unk14 = D_ovl10_13_8004ADC4->unk40->unk14;
            temp_v0_6->unk40->unk18 = D_ovl10_13_8004ADC4->unk40->unk18;
            temp_v0_6->unk68 = 30.0f;
            temp_v0_6->unk6C = 16.333334f;
            temp_v0_6->unk70 = 1.6333334f;
            D_ovl10_13_8004ADC0->unk68 = 30.0f;
            D_ovl10_13_8004ADC0->unk70 = 1.6333334f;
            D_ovl10_13_8004ADC0->unk6C = 16.333334f;
            D_ovl10_13_8004ADC4->unk68 = 30.0f;
            D_ovl10_13_8004ADC4->unk70 = 1.6333334f;
            D_ovl10_13_8004ADC4->unk6C = 16.333334f;
            func_ovl10_13_8004A198(0x70, 0x70, 0);
            func_ovl10_13_80049868(0, 8);
            temp_v0_7 = D_ovl10_13_8004ADC0->unk40->unk48->unk4;
            temp_v0_7->unk8 |= 0x60;
            func_ovl10_13_80049D30(D_ovl10_13_8004ADC0->unk40, 4, 4);
            func_ovl10_13_80049D30(D_ovl10_13_8004ADC0->unk40, 5, 5);
            var_s1_4 = 0;
            do {
                temp_v0_8 = temp_v0_6->unk40;
                temp_v0_8->unk10 -= 9.0f;
                temp_v0_9 = temp_v0_6->unk40;
                temp_v0_9->unk18 += 9.0f;
                temp_a0_2 = D_ovl10_13_8004ADC0->unk40;
                temp_a0_2->unk10 -= 7.5f;
                temp_a0_3 = D_ovl10_13_8004ADC0->unk40;
                temp_a0_3->unk18 += 7.5f;
                temp_v1_10 = D_ovl10_13_8004ADC4->unk40;
                temp_v1_10->unk10 -= 3.0f;
                temp_v1_11 = D_ovl10_13_8004ADC4->unk40;
                temp_v1_11->unk18 += 3.0f;
                temp_v0_10 = temp_v0_6->unk40;
                if (temp_v0_10->unk14 > 50.0f) {
                    func_ovl10_13_8004A058(temp_v0_6);
                } else {
                    temp_v0_10->unk14 = 50.0f;
                }
                temp_v1_12 = D_ovl10_13_8004ADC4->unk40;
                if (temp_v1_12->unk14 > 30.0f) {
                    func_ovl10_13_8004A058(D_ovl10_13_8004ADC4);
                } else {
                    temp_v1_12->unk14 = 30.0f;
                }
                func_ovl10_13_8004A058(D_ovl10_13_8004ADC0);
                func_ovl10_13_8004A170();
                var_s1_4 += 1;
            } while (var_s1_4 < 0x14);
            func_ovl10_13_8004A148(0x1E);
            temp_v0->unk40->unk10 = 2750.0f;
            temp_v0->unk40->unk14 = 400.0f;
            temp_v0->unk40->unk18 = 650.0f;
            temp_v0->unk40->unk20 = 315.0f;
            func_ovl10_13_8004A6B0(0x213);
            var_s1_5 = 0;
            do {
                temp_v1_13 = temp_v0->unk40;
                temp_v1_13->unk10 -= 16.666666f;
                temp_v1_14 = temp_v0->unk40;
                temp_v1_14->unk18 += 16.666666f;
                func_ovl10_13_8004A170();
                var_s1_5 += 1;
            } while (var_s1_5 < 0x1E);
            func_ovl10_13_8004A6B0(0x211);
            var_s1_6 = 0;
            temp_ft2 = (s32) func_ovl10_13_80049D18(temp_v0->unk40, 0);
            if (temp_ft2 > 0) {
                temp_fs0 = 200.0f / (f32) temp_ft2;
                do {
                    temp_v1_15 = temp_v0->unk40;
                    temp_v1_15->unk10 -= temp_fs0;
                    temp_v1_16 = temp_v0->unk40;
                    temp_v1_16->unk18 += temp_fs0;
                    temp_v1_17 = temp_v0->unk40;
                    temp_v1_17->unk14 -= 400.0f / (f32) temp_ft2;
                    temp_v1_18 = temp_v0->unk40;
                    temp_v1_18->unk20 += 90.0f / (f32) temp_ft2;
                    temp_a0_4 = temp_v0->unk40->unk48->unk4;
                    temp_a0_4->unk4 -= 1.0f;
                    temp_a0_5 = temp_v0->unk40->unk48->unk4;
                    if (temp_a0_5->unk4 < 0.0f) {
                        temp_a0_5->unk4 = 0.0f;
                    }
                    func_ovl10_13_8004A170();
                    var_s1_6 += 1;
                } while (var_s1_6 < temp_ft2);
                var_s1_6 = 0;
            }
            func_ovl10_13_80049D00(temp_v0->unk40, 7, 0);
            func_ovl10_13_80049FD8(temp_v0, 0x04000000);
            temp_ft2_2 = (s32) func_ovl10_13_80049D18(temp_v0->unk40, 0);
            if (temp_ft2_2 > 0) {
                temp_fs0_2 = 10.0f / (f32) temp_ft2_2;
                do {
                    temp_v0_11 = temp_v0_6->unk40;
                    temp_v0_11->unk14 += 100.0f / (f32) temp_ft2_2;
                    temp_v0_12 = temp_v0_6->unk40;
                    temp_v0_12->unk10 -= temp_fs0_2;
                    temp_v0_13 = temp_v0_6->unk40;
                    temp_v0_13->unk18 -= temp_fs0_2;
                    func_ovl10_13_8004A170();
                    var_s1_6 += 1;
                } while (var_s1_6 < temp_ft2_2);
                var_s1_6 = 0;
            }
            func_ovl10_13_8004A6B0(0x265);
            temp_s0 = func_ovl10_13_8004A128(func_ovl10_13_80047298, temp_v0_6, 0, 0, 0x130);
            func_ovl10_13_8004A148(0x1E);
            func_ovl10_13_8004A130(temp_s0);
            sp90 = temp_v0;
            sp94 = temp_v0_6;
            temp_s0_2 = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_800470C8, &sp90, 0, 0, 0x130);
            func_ovl10_13_8004A148(0xB4);
            temp_a0_6 = D_ovl10_13_8004ADC4->unk40->unk48->unk4;
            temp_a0_6->unk8 &= ~0x40;
            if (!(D_ovl10_13_8004ADC4->unk40->unk48->unk4->unk8 & 0x40)) {
                do {
                    func_ovl10_13_8004A170();
                } while (!(D_ovl10_13_8004ADC4->unk40->unk48->unk4->unk8 & 0x40));
            }
            func_ovl10_13_8004A130(temp_s0_2);
            func_ovl10_13_8004A750(temp_v0_6->unk40);
            func_ovl10_13_8004A750(temp_v0->unk40);
            func_ovl10_13_80049FE0(temp_v0, 0x04000000);
            temp_ft2_3 = (s32) func_ovl10_13_80049D18(temp_v0->unk40, 0);
            if (temp_ft2_3 > 0) {
                temp_fs0_3 = 10.0f / (f32) temp_ft2_3;
                do {
                    temp_v0_14 = temp_v0_6->unk40;
                    temp_v0_14->unk14 -= 100.0f / (f32) temp_ft2_3;
                    temp_v0_15 = temp_v0_6->unk40;
                    temp_v0_15->unk10 += temp_fs0_3;
                    temp_v0_16 = temp_v0_6->unk40;
                    temp_v0_16->unk18 += temp_fs0_3;
                    temp_a0_7 = temp_v0->unk40->unk48->unk4;
                    temp_a0_7->unk4 -= 1.0f;
                    temp_a0_8 = temp_v0->unk40->unk48->unk4;
                    if (temp_a0_8->unk4 < 0.0f) {
                        temp_a0_8->unk4 = 0.0f;
                    }
                    func_ovl10_13_8004A170();
                    var_s1_6 += 1;
                } while (var_s1_6 < temp_ft2_3);
                var_s1_6 = 0;
            }
            do {
                temp_v1_19 = temp_v0->unk40;
                temp_v1_19->unk20 += 3.0f;
                func_ovl10_13_8004A170();
                var_s1_6 += 1;
            } while (var_s1_6 < 0x1E);
            if (D_ovl10_13_8004ADA8 != 0x1F) {
                func_ovl10_13_80049D40(0x335, 1);
            }
            func_ovl10_13_8004A148(0x1E);
            func_ovl10_13_80049868(0, 0);
            temp_v0_17 = D_ovl10_13_8004ADC0->unk40->unk48->unk4;
            temp_v0_17->unk8 |= 0x60;
            temp_v0->unk40->unk20 = func_ovl10_13_80043010(temp_v0->unk40, D_ovl10_13_8004ADC0->unk40);
            temp_v1_20 = temp_v0->unk40;
            func_ovl10_13_80049E18(temp_v1_20->unk10, 100.0f, temp_v1_20->unk18);
            func_ovl10_13_80049E38(temp_v0->unk40->unk20, 5.0f, 800.0f);
            temp_fs2 = func_ovl10_13_8004A2D0(temp_v0->unk40->unk20);
            var_s1_7 = 0;
            temp_fs3 = func_ovl10_13_8004A2D8(temp_v0->unk40->unk20) * 12.0f;
            do {
                temp_v1_21 = temp_v0->unk40;
                temp_v1_21->unk10 += temp_fs2 * 12.0f;
                temp_v1_22 = temp_v0->unk40;
                temp_v1_22->unk18 += temp_fs3;
                temp_v1_23 = temp_v0->unk40;
                func_ovl10_13_80049E18(temp_v1_23->unk10, 100.0f, temp_v1_23->unk18);
                func_ovl10_13_8004A170();
                var_s1_7 += 1;
            } while (var_s1_7 < 0xA);
            func_ovl10_13_8004A6B0(0x25B);
            temp_v1_24 = D_ovl10_13_8004ADC4->unk40;
            func_ovl10_13_8004A578(0, temp_v1_24->unk10, temp_v1_24->unk14, temp_v1_24->unk18, 0);
            var_s1_8 = 0;
            do {
                temp_v1_25 = D_ovl10_13_8004ADC4->unk40;
                temp_v1_25->unk14 += 6.6666665f;
                func_ovl10_13_8004A170();
                var_s1_8 += 1;
            } while (var_s1_8 < 0x1E);
            func_ovl10_13_80049E18(2168.0f, 278.0f, 1174.0f);
            func_ovl10_13_80049E38(48.0f, 5.0f, 1652.0f);
            func_ovl10_13_80049D00(D_ovl10_13_8004ADC4->unk40, 0, 0);
            func_ovl10_13_80049FE0(D_ovl10_13_8004ADC4, 0x04000000);
            var_fs0 = -500.0f;
            D_ovl10_13_8004ADC4->unk40->unk1C = 270.0f;
            var_s1_9 = 0;
            var_at = 0 < 0x14;
            do {
                if (var_at == 0) {
                    temp_v1_26 = D_ovl10_13_8004ADC4->unk40;
                    func_ovl10_13_80049E18(temp_v1_26->unk10, temp_v1_26->unk14, temp_v1_26->unk18);
                    func_ovl10_13_80049E38(32768.0f, 32768.0f, 900.0f);
                }
                temp_v1_27 = D_ovl10_13_8004ADC4->unk40;
                temp_v1_27->unk10 += 10.0f;
                D_ovl10_13_8004ADC4->unk40->unk14 = (var_fs0 * var_fs0 * -0.0016f) + 400.0f;
                temp_v1_28 = D_ovl10_13_8004ADC4->unk40;
                temp_fv0 = temp_v1_28->unk20 + 20.0f;
                if (temp_fv0 >= 360.0f) {
                    temp_v1_28->unk20 = temp_fv0 - 360.0f;
                } else {
                    if (temp_fv0 < 0.0f) {
                        var_fv1 = temp_fv0 + 360.0f;
                    } else {
                        var_fv1 = temp_fv0;
                    }
                    temp_v1_28->unk20 = var_fv1;
                }
                var_fs0 += 10.0f;
                func_ovl10_13_8004A170();
                var_s1_9 += 1;
                var_at = var_s1_9 < 0x14;
            } while (var_s1_9 < 0x32);
            temp_v1_29 = temp_v0->unk40;
            func_ovl10_13_80049E18(temp_v1_29->unk10, 100.0f, temp_v1_29->unk18);
            func_ovl10_13_80049E38(32768.0f, 16.0f, 900.0f);
            func_ovl10_13_8004A6B0(0x25C);
            func_ovl10_13_80049D00(temp_v0->unk40, 0x17, 0);
            func_ovl10_13_80049FD8(temp_v0, 0x04000000);
            sp74 = temp_v0->unk40->unk10 + 10.0f;
            sp78 = temp_v0->unk40->unk14 + 50.0f;
            sp7C = temp_v0->unk40->unk18 + 50.0f;
            sp68 = temp_v0->unk40->unk10 + 10.0f;
            sp6C = temp_v0->unk40->unk14 + 50.0f;
            sp70 = temp_v0->unk40->unk18 - 50.0f;
            func_ovl10_13_8004A6B0(0x25E);
            var_s1_10 = 0;
            do {
                func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80046E88, &sp74, 0, 0, 0x130);
                func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80046E88, &sp68, 0, 0, 0x130);
                var_s1_10 += 1;
            } while (var_s1_10 < 4);
            temp_v0_18 = func_ovl10_13_80049CB8(0x2C7, 0);
            temp_v0_18->unkC |= 0x80;
            temp_v0_18->unk36 = 0x80;
            temp_v0_18->unk10 = sp74;
            temp_v0_18->unk14 = sp78;
            temp_v0_18->unk28 = 0.5f;
            temp_v0_18->unk2C = 0.5f;
            temp_v0_18->unk30 = 0.5f;
            temp_v0_18->unk18 = sp7C;
            temp_v0_19 = func_ovl10_13_80049CB8(0x2C7, 0);
            D_ovl10_13_8004ADA4 = temp_v0_19;
            temp_v0_19->unkC |= 0x80;
            var_fs1 = 0.0f;
            D_ovl10_13_8004ADA4->unk36 = 0x80;
            var_fs2 = 0.5f;
            D_ovl10_13_8004ADA4->unk10 = sp68;
            var_s1_11 = 0;
            D_ovl10_13_8004ADA4->unk14 = sp6C;
            D_ovl10_13_8004ADA4->unk18 = sp70;
            D_ovl10_13_8004ADA4->unk30 = 0.5f;
            temp_fv1 = D_ovl10_13_8004ADA4->unk30;
            D_ovl10_13_8004ADA4->unk2C = temp_fv1;
            D_ovl10_13_8004ADA4->unk28 = temp_fv1;
            do {
                temp_fs0_4 = (func_ovl10_13_8004A2D0(var_fs1) * 0.5f) + var_fs2;
                temp_v0_18->unk30 = temp_fs0_4;
                temp_v0_18->unk2C = temp_fs0_4;
                temp_v0_18->unk28 = temp_fs0_4;
                temp_fs0_5 = (func_ovl10_13_8004A2D0(var_fs1) * 0.5f) + var_fs2;
                D_ovl10_13_8004ADA4->unk30 = temp_fs0_5;
                temp_fa0 = var_fs1 + 0.5f;
                D_ovl10_13_8004ADA4->unk2C = temp_fs0_5;
                D_ovl10_13_8004ADA4->unk28 = temp_fs0_5;
                if (temp_fa0 >= 360.0f) {
                    var_fs1 = temp_fa0 - 360.0f;
                } else {
                    if (temp_fa0 < 0.0f) {
                        var_fv1_2 = temp_fa0 + 360.0f;
                    } else {
                        var_fv1_2 = temp_fa0;
                    }
                    var_fs1 = var_fv1_2;
                }
                var_fs2 += 0.0033333334f;
                func_ovl10_13_8004A170();
                var_s1_11 += 1;
            } while (var_s1_11 < 0x96);
            func_ovl10_13_8004A148(0x3C);
            func_ovl10_13_8004A6B0(0x260);
            func_ovl10_13_8004A430(0xFF, 0xFF, 0xFF, 0x14);
            func_ovl10_13_80049CC0(temp_v0_18);
            func_ovl10_13_80049CC0(D_ovl10_13_8004ADA4);
            temp_v0_20 = func_ovl10_13_80049CB8(0x2D5, 0xA);
            temp_v0_20->unkC |= 0x80;
            temp_v0_20->unk36 = 0x50;
            temp_v0_20->unk10 = sp74 + 40.0f;
            temp_v0_20->unk14 = sp78 + 40.0f;
            temp_v0_20->unk28 = 3.0f;
            temp_v0_20->unk30 = 3.0f;
            temp_v0_20->unk24 = 295.0f;
            temp_v0_20->unk2C = 70.0f;
            temp_v0_20->unk18 = sp7C;
            temp_v0_21 = func_ovl10_13_80049CB8(0x2D5, 0xA);
            D_ovl10_13_8004ADA4 = temp_v0_21;
            temp_v0_21->unkC |= 0x80;
            D_ovl10_13_8004ADA4->unk36 = 0x50;
            D_ovl10_13_8004ADA4->unk10 = sp68 + 40.0f;
            D_ovl10_13_8004ADA4->unk14 = sp6C + 40.0f;
            D_ovl10_13_8004ADA4->unk18 = sp70;
            D_ovl10_13_8004ADA4->unk24 = 295.0f;
            D_ovl10_13_8004ADA4->unk2C = 70.0f;
            temp_v0_20->unk30 = 3.0f;
            D_ovl10_13_8004ADA4->unk28 = 3.0f;
            func_ovl10_13_80049E18(2520.0f, 249.0f, 1392.0f);
            func_ovl10_13_80049E38(0.0f, 18.0f, 2353.0f);
            var_s1_12 = 0;
            do {
                temp_fv0_2 = temp_v0_20->unk20 + 15.0f;
                if (temp_fv0_2 >= 360.0f) {
                    temp_v0_20->unk20 = temp_fv0_2 - 360.0f;
                } else {
                    if (temp_fv0_2 < 0.0f) {
                        var_fv1_3 = temp_fv0_2 + 360.0f;
                    } else {
                        var_fv1_3 = temp_fv0_2;
                    }
                    temp_v0_20->unk20 = var_fv1_3;
                }
                temp_fv0_3 = D_ovl10_13_8004ADA4->unk20 + 15.0f;
                if (temp_fv0_3 >= 360.0f) {
                    D_ovl10_13_8004ADA4->unk20 = temp_fv0_3 - 360.0f;
                } else {
                    if (temp_fv0_3 < 0.0f) {
                        var_fv1_4 = temp_fv0_3 + 360.0f;
                    } else {
                        var_fv1_4 = temp_fv0_3;
                    }
                    D_ovl10_13_8004ADA4->unk20 = var_fv1_4;
                }
                func_ovl10_13_8004A170();
                var_s1_12 += 1;
            } while (var_s1_12 < 0x78);
            temp_v1_30 = D_ovl10_13_8004ADC4->unk40;
            func_ovl10_13_80049E18(temp_v1_30->unk10, temp_v1_30->unk14, temp_v1_30->unk18);
            func_ovl10_13_80049E38(0.0f, 18.0f, 900.0f);
            func_ovl10_13_80049FE0(D_ovl10_13_8004ADC4, 0x01000000);
            temp_v0_22 = func_ovl10_13_8004A000(0x326, 0x01000000, 0xD0, 0);
            temp_v0_22->unk40->unk10 = D_ovl10_13_8004ADC4->unk40->unk10;
            temp_v0_22->unk40->unk14 = D_ovl10_13_8004ADC4->unk40->unk14;
            temp_v0_22->unk40->unk18 = D_ovl10_13_8004ADC4->unk40->unk18;
            temp_v0_22->unk40->unk1C = D_ovl10_13_8004ADC4->unk40->unk1C;
            temp_v0_22->unk40->unk20 = D_ovl10_13_8004ADC4->unk40->unk20;
            temp_v0_22->unk40->unk24 = D_ovl10_13_8004ADC4->unk40->unk24;
            temp_v0_22->unk40->unk36 = 0xFF;
            temp_v1_31 = temp_v0_22->unk40;
            temp_v1_31->unkC |= 0x40000;
            func_ovl10_13_8004A6B0(0x262);
            var_s1_13 = 0;
loop_104:
            temp_fv0_4 = temp_v0_20->unk20 + 15.0f;
            if (temp_fv0_4 >= 360.0f) {
                temp_v0_20->unk20 = temp_fv0_4 - 360.0f;
            } else {
                if (temp_fv0_4 < 0.0f) {
                    var_fv1_5 = temp_fv0_4 + 360.0f;
                } else {
                    var_fv1_5 = temp_fv0_4;
                }
                temp_v0_20->unk20 = var_fv1_5;
            }
            temp_fv0_5 = D_ovl10_13_8004ADA4->unk20 + 15.0f;
            if (temp_fv0_5 >= 360.0f) {
                D_ovl10_13_8004ADA4->unk20 = temp_fv0_5 - 360.0f;
            } else {
                if (temp_fv0_5 < 0.0f) {
                    var_fv1_6 = temp_fv0_5 + 360.0f;
                } else {
                    var_fv1_6 = temp_fv0_5;
                }
                D_ovl10_13_8004ADA4->unk20 = var_fv1_6;
            }
            temp_v0_23 = temp_v0_22->unk40;
            temp_v0_23->unk36 = (s16) (s32) ((f32) temp_v0_23->unk36 - 2.125f);
            temp_v0_24 = temp_v0_22->unk40;
            if (temp_v0_24->unk36 < 0) {
                temp_v0_24->unk36 = 0;
            }
            func_ovl10_13_8004A170();
            if (D_ovl10_13_8004ADA8 == 0x1F) {
                var_s1_13 += 1;
                if (var_s1_13 == 0x32) {

                } else {
                    goto block_122;
                }
            } else {
                var_s1_13 += 1;
block_122:
                if (var_s1_13 < 0x78) {
                    goto loop_104;
                }
            }
            var_s1_14 = 0;
            if (D_ovl10_13_8004ADA8 == 0x1F) {
                func_ovl10_13_8004A828();
                func_ovl10_13_80049CC0(temp_v0_20);
                func_ovl10_13_80049CC0(D_ovl10_13_8004ADA4);
                D_ovl10_13_8004ADB4 = 0;
                func_ovl10_13_8004A138();
            }
            func_ovl10_13_80049FF0(temp_v0_22);
            do {
                temp_fv0_6 = temp_v0_20->unk20 + 15.0f;
                if (temp_fv0_6 >= 360.0f) {
                    temp_v0_20->unk20 = temp_fv0_6 - 360.0f;
                } else {
                    if (temp_fv0_6 < 0.0f) {
                        var_fv1_7 = temp_fv0_6 + 360.0f;
                    } else {
                        var_fv1_7 = temp_fv0_6;
                    }
                    temp_v0_20->unk20 = var_fv1_7;
                }
                temp_fv0_7 = D_ovl10_13_8004ADA4->unk20 + 15.0f;
                if (temp_fv0_7 >= 360.0f) {
                    D_ovl10_13_8004ADA4->unk20 = temp_fv0_7 - 360.0f;
                } else {
                    if (temp_fv0_7 < 0.0f) {
                        var_fv1_8 = temp_fv0_7 + 360.0f;
                    } else {
                        var_fv1_8 = temp_fv0_7;
                    }
                    D_ovl10_13_8004ADA4->unk20 = var_fv1_8;
                }
                temp_v0_20->unk28 -= 0.025f;
                temp_v0_20->unk30 -= 0.025f;
                D_ovl10_13_8004ADA4->unk28 -= 0.025f;
                D_ovl10_13_8004ADA4->unk30 -= 0.025f;
                func_ovl10_13_8004A170();
                var_s1_14 += 1;
            } while (var_s1_14 < 0x78);
            func_ovl10_13_80049CC0(temp_v0_20);
            func_ovl10_13_80049CC0(D_ovl10_13_8004ADA4);
            temp_v0_25 = temp_v0_6->unk40;
            func_ovl10_13_80049E18(temp_v0_25->unk10, 100.0f, temp_v0_25->unk18);
            func_ovl10_13_80049E38(42.0f, 26.0f, 1360.0f);
            temp_v0->unk40->unk10 = 2210.0f;
            var_s1_15 = 0;
            temp_v0->unk40->unk18 = 1390.0f;
            do {
                temp_v1_32 = temp_v0->unk40;
                temp_fv1_2 = temp_v1_32->unk20;
                temp_fv0_8 = temp_fv1_2 - 4.0f;
                if (temp_fv0_8 >= 360.0f) {
                    temp_v1_32->unk20 = temp_fv0_8 - 360.0f;
                } else {
                    if (temp_fv1_2 < 4.0f) {
                        var_fv1_9 = temp_fv0_8 + 360.0f;
                    } else {
                        var_fv1_9 = temp_fv0_8;
                    }
                    temp_v1_32->unk20 = var_fv1_9;
                }
                func_ovl10_13_8004A170();
                var_s1_15 += 1;
            } while (var_s1_15 < 0x1E);
            func_ovl10_13_80049D40(0x336, 3);
            func_ovl10_13_80049D00(temp_v0->unk40, 7, 0);
            func_ovl10_13_80049FD8(temp_v0, 0x04000000);
            var_s1_16 = 0;
            temp_ft2_4 = (s32) func_ovl10_13_80049D18(temp_v0->unk40, 0);
            if (temp_ft2_4 > 0) {
                temp_fs0_6 = 10.0f / (f32) temp_ft2_4;
                do {
                    temp_v0_26 = temp_v0_6->unk40;
                    temp_v0_26->unk14 += 100.0f / (f32) temp_ft2_4;
                    temp_v0_27 = temp_v0_6->unk40;
                    temp_v0_27->unk10 += temp_fs0_6;
                    temp_v0_28 = temp_v0_6->unk40;
                    temp_v0_28->unk18 -= temp_fs0_6;
                    func_ovl10_13_8004A170();
                    var_s1_16 += 1;
                } while (var_s1_16 < temp_ft2_4);
                var_s1_16 = 0;
            }
            func_ovl10_13_80049868(0, 4);
            temp_v0_29 = D_ovl10_13_8004ADC0->unk40->unk48->unk4;
            temp_v0_29->unk8 |= 0x20;
            func_ovl10_13_8004A6B0(0x20F);
            do {
                temp_v1_33 = temp_v0->unk40;
                temp_v1_33->unk14 += 33.333332f;
                temp_v0_30 = temp_v0_6->unk40;
                temp_v0_30->unk14 += 33.333332f;
                func_ovl10_13_8004A170();
                var_s1_16 += 1;
            } while (var_s1_16 != 0x1E);
            if (D_ovl10_13_8004ADA8 != 0x1F) {
                func_ovl10_13_8004A380(0xA4);
            }
        }
    }
}

/* A static: its callers pass `from` in a3 and `to` in t0 (ovl_12_06's 80043068). */
static f32 func_ovl10_13_80043010(UnkStructA_40 *from, UnkStructA_40 *to) {
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
    func_ovl10_13_80049F68(&a, &b, &angle);
    return angle;
}
