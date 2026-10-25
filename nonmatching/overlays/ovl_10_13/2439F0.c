/*
 * NON_MATCHING: ovl_10_13's game object, complete: every function and its
 * .bss. Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING
 * drafts").
 * flags: -O3
 * differing words: us 1335, jp 1335
 *
 * What still differs in us (words, as tools/nonmatching.py counts them):
 * - 800464B0 (4): v1 for v0; a third temporary grows the frame.
 * - The statics, compared with 80043010 as one run (1331). Each on its
 *   own (scratch/10_13/allf.py): 80043070 936 and 8004574C 395;
 *   80044E48 matches (its two unused pads give the original's frame,
 *   with i and a between the vectors and angle). They are the
 *   cut-scenes the handler and 800474EC-800477E8 run. They save no callee-saved registers (their
 *   callers do), so they are static; they come first in the object.
 * - 80043070 is Hudson's loops with the original's frame (0xA0: two
 *   locals above `pair`, four between it and the vectors, ten below;
 *   k, m and y are unused and only place the rest). Its counters are the
 *   original's three: i (the first loops, the total and the animation
 *   lengths), j (the last five's count and every later loop) and n. Its
 *   code is the original's length, but 3.0f isn't kept in $f28 from the
 *   20-frame loop to the turn (270.0f takes $f28 for $f30), so the
 *   floats' registers differ from 0x800438xx to 0x800446xx.
 * - 8004574C has the original's frame (0x50) with dx shared with the
 *   turn's angle and dz with its distance. What differs is the same as
 *   in 80043070, the other way: it keeps 1150.0f in a saved float
 *   register (passed with mfc1) where the original loads it as an
 *   immediate (lui/ori into a2), and the stores and divisions around
 *   dx/dy/dz are scheduled differently; it is 0x20 short (the alignment
 *   nops before the epilogue), so what follows shifts.
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

/* an angle in degrees moved by d and kept in [0, 360) */
#define ANGLE_ADD(a, d) \
    (a) = ((a) + (d) >= 360.0f) ? (a) + (d) - 360.0f : ((a) + (d) < 0.0f) ? (a) + (d) + 360.0f : (a) + (d)
#define ANGLE_SUB(a, d) \
    (a) = ((a) - (d) >= 360.0f) ? (a) - (d) - 360.0f : ((a) < (d)) ? (a) - (d) + 360.0f : (a) - (d)

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
s32 func_ovl10_13_8004A148(s32);
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
s32 *func_ovl10_13_8004A3C0();
void func_ovl10_13_8004A420(void);
void func_ovl10_13_8004A428(s32, s32, s32, f32);
void func_ovl10_13_8004A430(s32, s32, s32, s32);
void func_ovl10_13_8004A440(s32, s32, s32, s32);
void func_ovl10_13_8004A578(s32, f32, f32, f32, s32);
void func_ovl10_13_8004A580(s32, f32 *, s32);
s32 func_ovl10_13_8004A6B0(s32);
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
void func_ovl10_13_80048850(void);
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
    s32 i;

    func_ovl10_13_8004A6B0(0x243);

    for (i = 0; i < 60; i++) {
        func_ovl10_13_8004A740(D_ovl10_13_8004ADB0, 0x1F, 0, 4, (f32) i / 140.0f);
        func_ovl10_13_8004A170();
    }
    D_ovl10_13_8004ADB0->unkC |= 0x1080;
    D_ovl10_13_8004ADB0->unk36 = 0xFF;
    for (i = 60; i != 0; i--) {
        D_ovl10_13_8004ADB0->unk36 = (f32) i / 60.0f * 255.0f;
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049CC0(D_ovl10_13_8004ADB0);
    func_ovl10_13_8004A138();
}

void func_ovl10_13_80048850(void) {
    UnkStructA *obj;
    UnkStructA_40 *p;
    f32 scale;
    f32 angle;
    s32 sound;
    s32 who;
    s32 i;

    who = func_ovl10_13_8004A150();
    obj = func_ovl10_13_80049818(who);
    p = func_ovl10_13_80049CB8(0x302, 0);
    p->unkC |= 0x80;
    p->unk36 = 0x80;
    p->unk30 = 0.1f;
    p->unk2C = 0.1f;
    p->unk28 = 0.1f;
    p->unk10 = obj->unk40->unk10;
    p->unk14 = obj->unk40->unk14 + 50.0f;
    p->unk18 = obj->unk40->unk18;
    sound = func_ovl10_13_8004A6D0(who == 1 ? 0x24B : 0x24F, p->unk10, p->unk14, p->unk18);
    if (D_ovl10_13_8004ADA8 != 0x1C) {
        for (i = 0; i != 60; i++) {
            p->unk30 += 0.033333335f;
            p->unk2C = p->unk30;
            p->unk28 = p->unk30;
            func_ovl10_13_8004A170();
        }
    } else {
        p->unk30 = 2.0f;
        p->unk2C = 2.0f;
        p->unk28 = 2.0f;
    }
    angle = 0.0f;
    while (TRUE) {
        if (who == 1 && D_ovl10_13_8004ADD4 == 0) {
            break;
        }
        if (who == 2 && D_ovl10_13_8004ADD8 == 0) {
            break;
        }
        p->unk10 = obj->unk40->unk10;
        p->unk14 = obj->unk40->unk14 + 50.0f;
        p->unk18 = obj->unk40->unk18;
        scale = func_ovl10_13_8004A2D8(angle) * 0.2f + 2.5f;
        p->unk30 = scale;
        p->unk2C = scale;
        p->unk28 = scale;
        p->unk36 = 128.0f - func_ovl10_13_8004A2D8(angle) * 10;
        angle = angle + 9.0f + D_ovl10_13_8004ADDC >= 360.0f ? angle + 9.0f + D_ovl10_13_8004ADDC - 360.0f
              : angle + 9.0f + D_ovl10_13_8004ADDC < 0.0f ? angle + 9.0f + D_ovl10_13_8004ADDC + 360.0f
              : angle + 9.0f + D_ovl10_13_8004ADDC;
        func_ovl10_13_8004A700(sound, p->unk10, p->unk14, p->unk18);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049CC0(p);
    func_ovl10_13_8004A138();
}

void func_ovl10_13_800486A8(void) {
    UnkStructA *obj;
    UnkStructA_40 *p;
    f32 scale;
    s32 i;
    s32 angle;

    obj = func_ovl10_13_8004A150();
    p = func_ovl10_13_80049CB8(0x2C7, 0);
    p->unk36 = 0;
    p->unkC |= 0x80;
    p->unk10 = obj->unk40->unk10;
    p->unk14 = obj->unk40->unk14 + 50.0f;
    p->unk18 = obj->unk40->unk18;
    while (D_ovl10_13_8004ADE0 != 0) {
        for (i = 0, angle = 0; i != 30; i++, angle += 6) {
            scale = 15.0f - (f32) i * 14.0f / 30.0f;
            p->unk30 = scale;
            p->unk2C = scale;
            p->unk28 = scale;
            p->unk36 = func_ovl10_13_8004A2D0(angle) * 120.0f;
            func_ovl10_13_8004A170();
        }
    }
    func_ovl10_13_80049CC0(p);
    func_ovl10_13_8004A138();
}

void func_ovl10_13_80047A0C(void) {
    UnkStructA *obj0;
    UnkStructA *obj2;
    UnkStructA *obj1;
    UnkStructA_40 *p;
    f32 angle;
    s32 i;
    s32 task1;
    s32 task2;
    UnkStruct_ovl10_13_8004A770 *player;

    obj0 = func_ovl10_13_80049818(0);
    obj2 = func_ovl10_13_80049818(2);
    func_ovl10_13_80049868(0, 3);
    for (i = 0; i < 600; i += 8) {
        obj0->unk40->unk18 -= 8.0f;
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_8004A6B0(0x263);
    func_ovl10_13_80049E38(185.0f, 10.0f, 2000.0f);
    for (i = 0; i < 600; i += 8) {
        obj0->unk40->unk18 -= 8.0f;
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049868(0, 0);
    func_ovl10_13_8004A6B0(0x276);
    for (i = 0; i < 60; i++) {
        obj2->unk40->unk14 -= 8.333333f;
        obj2->unk40->unk18 -= 10.0f;
        obj2->unk40->unk1C -= 1.5f;
        func_ovl10_13_8004A170();
    }
    for (i = 0; i < 10; i++) {
        ANGLE_ADD(obj0->unk40->unk20, 18.0f);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_8004A148(0x1E);
    func_ovl10_13_80049E18(obj2->unk40->unk10, obj2->unk40->unk14, obj2->unk40->unk18);
    func_ovl10_13_80049E38(204.0f, 25.1f, 722.0f);
    angle = 0.0f;
    for (i = 0; i < 120; i++) {
        obj2->unk40->unk14 += func_ovl10_13_8004A2D8(angle) * 1.8f;
        ANGLE_ADD(angle, 5.0f);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049DF8(1);
    func_ovl10_13_80049E08(0);
    task1 = func_ovl10_13_8004A128(func_ovl10_13_80048F00, obj2, 0, 0, 0x130);
    task2 = func_ovl10_13_8004A128(func_ovl10_13_80048EA8, obj2, 0, 0, 0x130);
    p = obj2->unk40;
    for (i = 0; i < 30; i++) {
        ANGLE_SUB(p->unk1C, 0.6666667f);
        ANGLE_ADD(p->unk20, 3.0f);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049E28(2927.0f, 2951.0f, 1300.0f);
    for (i = 0; i < 30; i++) {
        ANGLE_SUB(p->unk1C, 2.3333333f);
        func_ovl10_13_8004A170();
    }
    for (i = 0; i < 30; i++) {
        ANGLE_SUB(p->unk1C, 3.0f);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_8004A148(0x1E);
    for (i = 0; i < 30; i++) {
        ANGLE_ADD(p->unk20, 0.33333334f);
        func_ovl10_13_8004A170();
    }
    for (i = 0; i < 30; i++) {
        ANGLE_SUB(p->unk1C, 5);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049E28(1282.0f, 1408.0f, 2745.0f);
    func_ovl10_13_8004A170();
    func_ovl10_13_8004A128(func_ovl10_13_80048CEC, obj2, 0, 0, 0x130);
    for (i = 0; i < 60; i++) {
        ANGLE_SUB(p->unk20, 0.5f);
        ANGLE_SUB(p->unk1C, 0.16666667f);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_8004A130(task2);
    func_ovl10_13_80049E28(3811.0f, 384.0f, 3048.0f);
    func_ovl10_13_8004A128(func_ovl10_13_80048BBC, NULL, 0, 0, 0x130);
    for (i = 0; i < 30; i++) {
        ANGLE_SUB(p->unk20, 3.3333333f);
        ANGLE_SUB(p->unk1C, 2.6666667f);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_8004A148(0xB4);
    func_ovl10_13_8004A130(task1);
    if (D_ovl10_13_8004ADA8 == 0x1A) {
        func_ovl10_13_8004A130(func_ovl10_13_8004A770(2)->unkA0.w);
        func_ovl10_13_8004A828();
        D_ovl10_13_8004ADB4 = 0;
        func_ovl10_13_8004A138();
    }
    func_ovl10_13_80049E18(2350.0f, 0.0f, 1500.0f);
    func_ovl10_13_80049E08(1);
    func_ovl10_13_80049E38(0.0f, 30.0f, 1573.0f);
    for (i = 0; i < 10; i++) {
        ANGLE_ADD(obj0->unk40->unk20, 18.0f);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049868(0, 3);
    for (i = 0; i < 200; i += 8) {
        obj0->unk40->unk18 -= 8.0f;
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049868(0, 0);
    obj2->unk40->unk10 = 2600.0f;
    obj2->unk40->unk14 = 400.0f;
    obj2->unk40->unk18 = 1200.0f;
    obj2->unk40->unk1C = 0.0f;
    obj2->unk40->unk20 = 0.0f;
    obj2->unk40->unk24 = 0.0f;
    func_ovl10_13_8004A6B0(0x278);
    for (i = 0; i < 240; i++) {
        obj2->unk40->unk14 -= 1.6666666f;
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_8004A148(0x3C);
    p = func_ovl10_13_80049CB8(0x2D4, 0);
    p->unkC |= 0x80;
    p->unk36 = 0x5A;
    p->unk10 = 2100.0f;
    p->unk14 = 400.0f;
    p->unk18 = 1200.0f;
    p->unk2C = 200.0f;
    func_ovl10_13_8004A6D0(0x245, 2100.0f, 400.0f, 1200.0f);
    for (i = 0; i < 180; i++) {
        p->unk14 -= 2.2222223f;
        func_ovl10_13_8004A170();
    }
    p->unk14 = 0.0f;
    func_ovl10_13_8004A758(1, 4, 0x15, 0, 0xC);
    func_ovl10_13_8004A778(0);
    obj1 = func_ovl10_13_80049818(1);
    obj1->unk40->unk14 = 800.0f;
    player = func_ovl10_13_8004A770(1);
    player->unk90 = 0x3C;
    func_ovl10_13_8004A140(player->unkA0.h.lo, 0);
    func_ovl10_13_80049848(1);
    func_ovl10_13_800497C8(1);
    func_ovl10_13_80049848(0);
    func_ovl10_13_8004A170();
    func_ovl10_13_80049DF8(1);
    func_ovl10_13_80049E08(0);
    func_ovl10_13_80049E28(2327.0f, 632.0f, 1807.0f);
    for (i = 0; i < 360.0f; i++) {
        obj1->unk40->unk14 -= 2.2222223f;
        if (i < 240) {
            func_ovl10_13_80049E18(obj1->unk40->unk10, obj1->unk40->unk14, obj1->unk40->unk18);
        }
        if (i == 240) {
            func_ovl10_13_80049E08(1);
            func_ovl10_13_80049E78(0x10);
            func_ovl10_13_80049E80(0xF);
            func_ovl10_13_8004A778(1);
        }
        func_ovl10_13_8004A170();
    }
    obj1->unk40->unk14 = 0.0f;
    for (i = 0; i < 30; i++) {
        p->unk36 -= 3.0f;
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_80049CC0(p);
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
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 sound;
    s32 i;

    obj = func_ovl10_13_8004A150();
    func_ovl10_13_8004A148(0x78);
    p = obj->unk40;
    sound = func_ovl10_13_8004A6D0(0x213, p->unk10, p->unk14, p->unk18);
    for (i = 0; i != 40; i++) {
        p = obj->unk40;
        p->unk10 -= 50.0f;
        p = obj->unk40;
        func_ovl10_13_8004A700(sound, p->unk10, p->unk14, p->unk18);
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_8004A138();
}

void func_ovl10_13_80047298(void) {
    UnkStructA *obj;
    f32 angle;
    s32 i;

    angle = 0.0f;
    obj = func_ovl10_13_8004A150();
    while (TRUE) {
        for (i = 0; i != 60; i++) {
            func_ovl10_13_8004A740(obj->unk40, 0x1F, 0x1F, 0x1F,
                func_ovl10_13_8004A2D0(angle) * 0.5f < 0 ? -(func_ovl10_13_8004A2D0(angle) * 0.5f) : func_ovl10_13_8004A2D0(angle) * 0.5f);
            angle = angle + 6.0f >= 360.0f ? angle + 6.0f - 360.0f : angle + 6.0f < 0.0f ? angle + 6.0f + 360.0f : angle + 6.0f;
            func_ovl10_13_8004A170();
        }
    }
}

void func_ovl10_13_800470C8(void) {
    UnkStructA **objs;
    UnkStructA *a;
    UnkStructA *b;
    s32 red;
    s32 green;
    s32 blue;
    f32 angle;

    objs = func_ovl10_13_8004A150();
    a = objs[0];
    b = objs[1];
    angle = 0.0f;
    while (TRUE) {
        red = func_ovl10_13_8004A2E8(31);
        green = func_ovl10_13_8004A2E8(31);
        blue = func_ovl10_13_8004A2E8(31);
        func_ovl10_13_8004A740(a->unk40, red, green, blue,
                               func_ovl10_13_8004A2D0(angle) < 0 ? -func_ovl10_13_8004A2D0(angle) : func_ovl10_13_8004A2D0(angle));
        func_ovl10_13_8004A740(b->unk40, red, green, blue,
                               func_ovl10_13_8004A2D0(angle) < 0 ? -func_ovl10_13_8004A2D0(angle) : func_ovl10_13_8004A2D0(angle));
        angle = angle + 20.0f >= 360.0f ? angle + 20.0f - 360.0f : angle + 20.0f < 0.0f ? angle + 20.0f + 360.0f : angle + 20.0f;
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
    p->unk30 = 0.3f;
    p->unk2C = 0.3f;
    p->unk28 = 0.3f;
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
    UnkStruct_ovl10_13_80049728 *info;
    UnkStruct_ovl10_13_8004A770 *player;
    UnkStructA *obj0;
    UnkStructA *obj1;
    UnkStructA *obj2;
    f32 dy;
    f32 dx;
    f32 dz;
    s32 limit;
    s32 i;

    info = func_ovl10_13_80049728();
    D_ovl10_13_8004ADD0 = info->unk30;
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
    player = func_ovl10_13_8004A770(1);
    player->unk0 = 0;
    player->unk88 = -1;
    player = func_ovl10_13_8004A770(2);
    player->unk0 = 0;
    player->unk88 = -1;
    if ((D_ovl10_13_8004ADA8 != 0x1C) && !(player->unk124 & 8)) {
        if (info->unk10 == 0) {
            limit = 10000;
        } else {
            limit = 8000;
        }
        if (limit >= D_ovl10_13_8004ADD0) {
            func_ovl10_13_8004A358(&player->unk2C);
            player->unk124 |= 8;
            info->unk2C += 1;
        }
    }
    obj0 = func_ovl10_13_80049818(0);
    obj1 = func_ovl10_13_80049818(1);
    obj2 = func_ovl10_13_80049818(2);
    func_ovl10_13_80049FE0(obj0, 0x40000);
    func_ovl10_13_80049FE0(obj1, 0x40000);
    func_ovl10_13_80049FE0(obj2, 0x40000);
    if (D_ovl10_13_8004ADA8 != 0x1C) {
        func_ovl10_13_80049778(0x12C);
        func_ovl10_13_8004A6C8();
    }
    func_ovl10_13_8004A6B0(0x24C);
    obj1->unk70 = 0.0f;
    obj1->unk6C = 0.0f;
    obj1->unk68 = 0.0f;
    obj1->unk40->unk20 = 0.0f;
    obj2->unk68 = 0.0f;
    obj2->unk6C = 0.0f;
    obj2->unk70 = 0.0f;
    obj2->unk40->unk20 = 0.0f;
    func_ovl10_13_80049FE0(obj0, 0x40000);
    func_ovl10_13_80049FE0(obj1, 0x40000);
    func_ovl10_13_80049FE0(obj2, 0x40000);
    func_ovl10_13_80049E18(obj1->unk40->unk10, obj1->unk40->unk14, obj1->unk40->unk18);
    func_ovl10_13_80049E38(32768.0f, 32768.0f, 1150.0f);
    func_ovl10_13_80049E08(0);
    D_ovl10_13_8004ADDC = 0;
    if (D_ovl10_13_8004ADA8 != 0x1C) {
        D_ovl10_13_8004ADD4 = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80048850, (void *)1, 0, 0, 0x130);
        func_ovl10_13_8004A148(0x3C);
        obj0->unk40->unk20 = func_ovl10_13_80043010(obj0->unk40, obj1->unk40);
        dz = (1400.0f - obj1->unk40->unk18) / 300.0f;
        dx = (2000.0f - obj1->unk40->unk10) / 300.0f;
        dy = (800.0f - obj1->unk40->unk14) / 300.0f;
        for (i = 0; i < 0x12C; i++) {
            obj1->unk40->unk14 += dy;
            obj1->unk40->unk10 += dx;
            obj1->unk40->unk18 += dz;
            func_ovl10_13_80049E18(obj1->unk40->unk10, obj1->unk40->unk14, obj1->unk40->unk18);
            func_ovl10_13_8004A170();
        }
        obj0->unk40->unk20 = func_ovl10_13_80043010(obj0->unk40, obj2->unk40);
        func_ovl10_13_80049E08(1);
        func_ovl10_13_80049E18(obj2->unk40->unk10, obj2->unk40->unk14, obj2->unk40->unk18);
        func_ovl10_13_80049E38(32768.0f, 45.0f, 1150.0f);
        func_ovl10_13_80049E08(0);
        D_ovl10_13_8004ADD8 = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80048850, (void *)2, 0, 0, 0x130);
        func_ovl10_13_8004A148(0x3C);
        i = 0;
        dz = (1400.0f - obj2->unk40->unk18) / 300.0f;
        dx = (2700.0f - obj2->unk40->unk10) / 300.0f;
        dy = (800.0f - obj2->unk40->unk14) / 300.0f;
        for (i = 0; i < 0x12C; i++) {
            obj2->unk40->unk14 += dy;
            obj2->unk40->unk10 += dx;
            obj2->unk40->unk18 += dz;
            func_ovl10_13_80049E18(obj2->unk40->unk10, obj2->unk40->unk14, obj2->unk40->unk18);
            func_ovl10_13_8004A170();
        }
    } else {
        D_ovl10_13_8004ADD4 = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80048850, (void *)1, 0, 0, 0x130);
        D_ovl10_13_8004ADD8 = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80048850, (void *)2, 0, 0, 0x130);
        obj1->unk40->unk10 = 2000.0f;
        obj1->unk40->unk14 = 800.0f;
        obj1->unk40->unk18 = 1400.0f;
        obj2->unk40->unk10 = 2700.0f;
        obj2->unk40->unk14 = 800.0f;
        obj2->unk40->unk18 = 1400.0f;
    }
    func_ovl10_13_80049E08(1);
    func_ovl10_13_80049E18(2350.0f, 864.0f, 1399.0f);
    func_ovl10_13_80049E38(314.0f, 32.0f, 1438.0f);
    dy = (2350.0f - obj2->unk40->unk10) / 300.0f;
    dx = (2350.0f - obj1->unk40->unk10) / 300.0f;
    for (i = 0; i < 0x12C; i++) {
        obj1->unk40->unk10 += dx;
        obj2->unk40->unk10 += dy;
        func_ovl10_13_8004A170();
    }
    D_ovl10_13_8004ADDC = 0xA;
    func_ovl10_13_8004A6B0(0x24D);
    D_ovl10_13_8004ADE0 = func_ovl10_13_8004A128(func_ovl10_13_800486A8, obj1, 0, 0, 0x130);
    func_ovl10_13_8004A148(0x1E);
    func_ovl10_13_8004A440(0xFF, 0xFF, 0xFF, 0xAA);
    dz = 1438.0f;
    dx = 314.0f;
    for (i = 0; i < 0xB4; i++) {
        if (i == 0xAA) {
            func_ovl10_13_8004A6B0(0x250);
        }
        func_ovl10_13_80049E38(dx, 32768.0f, dz);
        ANGLE_ADD(dx, 0.15555556f);
        dz -= 6.311111f;
        func_ovl10_13_8004A170();
    }
    D_ovl10_13_8004ADE0 = 0;
    D_ovl10_13_8004ADD8 = 0;
    D_ovl10_13_8004ADD4 = 0;
    func_ovl10_13_8004A170();
    func_ovl10_13_80049778(0x20);
    if (D_ovl10_13_8004ADA8 == 0x1C) {
        func_ovl10_13_8004A420();
        func_ovl10_13_80049FE0(obj1, 0x01000000);
        func_ovl10_13_80049FE0(obj2, 0x01000000);
        obj2->unk40->unk10 = 5000.0f;
        func_ovl10_13_8004A758(3, 6, 0x17, 0, 0xC);
        func_ovl10_13_8004A778(0);
        obj0 = func_ovl10_13_80049818(3);
        obj0->unk40->unk10 += 50.0f;
        obj0->unk40->unk14 += 800.0f;
        obj0->unk68 = 0.0f;
        obj0->unk70 = 0.0f;
        func_ovl10_13_8004A130(func_ovl10_13_8004A770(3)->unkA0.w);
        func_ovl10_13_80049E18(obj0->unk40->unk10, obj0->unk40->unk14 + 100.0f, obj0->unk40->unk18);
        func_ovl10_13_80049E38(0.0f, 20.0f, 600.0f);
        func_ovl10_13_8004A430(0xFF, 0xFF, 0xFF, 0x78);
        func_ovl10_13_8004A420();
        func_ovl10_13_80049D00(obj0->unk40, 0x22, 0);
        func_ovl10_13_80049D00(obj0->unk40, -1, 1);
        obj0->unk40->unk48->unk4->unk8 |= 0x20;
        while (!(obj0->unk40->unk48->unk4->unk8 & 0x40)) {
            func_ovl10_13_8004A170();
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
    s32 i;
    f32 a;
    f32 angle;
    s32 pad1;
    s32 pad2;

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
        D_ovl10_13_8004ADC4->unk40->unk48->unk4->unk8 |= 0x40;
        D_ovl10_13_8004ADC4->unk40->unk48->unk4->unk4 = func_ovl10_13_80049D18(D_ovl10_13_8004ADC4->unk40, 0) - 0.01f;
        from.x = D_ovl10_13_8004ADC0->unk40->unk10;
        from.y = D_ovl10_13_8004ADC0->unk40->unk14;
        from.z = D_ovl10_13_8004ADC0->unk40->unk18;
        to.x = 2350.0f;
        to.y = 0.0f;
        to.z = 1550.0f;
        func_ovl10_13_80049F68(&from, &to, &angle);
        to.x = func_ovl10_13_8004A2D0(angle) * 800.0f + from.x;
        to.y = from.y;
        to.z = (func_ovl10_13_8004A2D8(angle) * 800.0f) + from.z;
        from.x = D_ovl10_13_8004ADC4->unk40->unk10;
        from.y = D_ovl10_13_8004ADC4->unk40->unk14;
        from.z = D_ovl10_13_8004ADC4->unk40->unk18;
        func_ovl10_13_80049F68(&from, &to, &angle);
        func_ovl10_13_80049F80(&from, &to);
        D_ovl10_13_8004ADC4->unk68 = 51.0f;
        D_ovl10_13_8004ADC4->unk40->unk14 = 0.1f;
        D_ovl10_13_8004ADC4->unk70 = 0.8166667f;
        i = 0;
        D_ovl10_13_8004ADC4->unk6C = 16.333334f;
        do {
            D_ovl10_13_8004ADC4->unk40->unk10 += (to.x - from.x) / 90.0f;
            D_ovl10_13_8004ADC4->unk40->unk18 += (to.z - from.z) / 90.0f;
            if (D_ovl10_13_8004ADC4->unk40->unk14 < 0.0f) {
                D_ovl10_13_8004ADC4->unk70 = 0.0f;
                D_ovl10_13_8004ADC4->unk68 = D_ovl10_13_8004ADC4->unk70;
                D_ovl10_13_8004ADC4->unk40->unk14 = 0.0f;
            } else {
                func_ovl10_13_8004A058(D_ovl10_13_8004ADC4);
            }
            func_ovl10_13_8004A170();
            i += 1;
        } while (i != 0x5A);
        func_ovl10_13_8004A6B0(0x259);
    }
    D_ovl10_13_8004ADC4->unk40->unk20 = 0.0f;
    D_ovl10_13_8004ADC0->unk40->unk20 = func_ovl10_13_80043010(D_ovl10_13_8004ADC0->unk40, D_ovl10_13_8004ADC4->unk40);
    func_ovl10_13_80049E18(D_ovl10_13_8004ADC4->unk40->unk10 + 30.0f, 100.0f, D_ovl10_13_8004ADC4->unk40->unk18);
    func_ovl10_13_80049E38(0.0f, 20.0f, 800.0f);
    func_ovl10_13_80049E08(0);
    func_ovl10_13_8004A148(0x1E);
    D_ovl10_13_8004ADC8 = func_ovl10_13_8004A000(0x320, 0x01000000, 0xC0, 0);
    func_ovl10_13_8004A010(D_ovl10_13_8004ADC8);
    D_ovl10_13_8004ADCC = func_ovl10_13_80049D48(D_ovl10_13_8004ADC8->unk40, 0x10);
    for (i = 0; i < 0x10; i++) {
        func_ovl10_13_80049D50(D_ovl10_13_8004ADCC, i, 0x322);
        func_ovl10_13_80049D60(D_ovl10_13_8004ADCC, i, i);
    }
    D_ovl10_13_8004ADC8->unk40->unk10 = D_ovl10_13_8004ADC4->unk40->unk10 + 50.0f;
    D_ovl10_13_8004ADC8->unk40->unk14 = D_ovl10_13_8004ADC4->unk40->unk14 + 1000.0f;
    D_ovl10_13_8004ADC8->unk40->unk18 = D_ovl10_13_8004ADC4->unk40->unk18;
    func_ovl10_13_80049D00(D_ovl10_13_8004ADC8->unk40, 0xD, 0);
    func_ovl10_13_8004A6B0(0x2E5);
    for (i = 0; i < 0x3C; i++) {
        D_ovl10_13_8004ADC8->unk40->unk14 -= 16.666666f;
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_8004A6B0(0x1C);
    func_ovl10_13_8004A578(0xD, D_ovl10_13_8004ADC8->unk40->unk10, D_ovl10_13_8004ADC8->unk40->unk14, D_ovl10_13_8004ADC8->unk40->unk18, 0);
    D_ovl10_13_8004ADC8->unk40->unk14 = 0.0f;
    func_ovl10_13_80049FD8(D_ovl10_13_8004ADC8, 0x04000000);
    while (!(D_ovl10_13_8004ADC8->unk40->unkC & 0x40)) {
        func_ovl10_13_8004A170();
    }
    func_ovl10_13_8004A148(0x1E);
    func_ovl10_13_80049D00(D_ovl10_13_8004ADC8->unk40, 0x16, 0);
    func_ovl10_13_80049FD8(D_ovl10_13_8004ADC8, 0x04000000);
    func_ovl10_13_8004A148(7);
    func_ovl10_13_8004A6B0(0x255);
    for (i = 0; i < 0x3C; i++) {
        if (i == 5) {
            func_ovl10_13_80049FE0(D_ovl10_13_8004ADC8, 0x04000000);
        }
        D_ovl10_13_8004ADC8->unk40->unk14 += 4.1666665f;
        if (i >= 8) {
            D_ovl10_13_8004ADC4->unk40->unk14 += 4.1666665f;
        }
        func_ovl10_13_80049E18(D_ovl10_13_8004ADC4->unk40->unk10 + 30.0f, D_ovl10_13_8004ADC4->unk40->unk14 + 100.0f, D_ovl10_13_8004ADC4->unk40->unk18);
        func_ovl10_13_8004A170();
    }
    if (D_ovl10_13_8004ADA8 != 0x1E) {
        func_ovl10_13_80049778(0x32);
        func_ovl10_13_8004A6C8();
    }
    a = 0.0f;
    for (i = 0; i < 0x78; i++) {
        D_ovl10_13_8004ADC4->unk40->unk14 += func_ovl10_13_8004A2D8(a) * 1.8f;
        D_ovl10_13_8004ADC8->unk40->unk14 += func_ovl10_13_8004A2D8(a) * 1.8f;
        ANGLE_ADD(a, 5.0f);
        func_ovl10_13_80049E18(D_ovl10_13_8004ADC4->unk40->unk10 + 30.0f, D_ovl10_13_8004ADC4->unk40->unk14 + 100.0f, D_ovl10_13_8004ADC4->unk40->unk18);
        func_ovl10_13_8004A170();
    }
    for (i = 0; i < 0x78; i++) {
        D_ovl10_13_8004ADC4->unk40->unk14 += 8.333333f;
        D_ovl10_13_8004ADC8->unk40->unk14 += 8.333333f;
        if (i < 0x64) {
            func_ovl10_13_80049E18(D_ovl10_13_8004ADC4->unk40->unk10 + 30.0f, D_ovl10_13_8004ADC4->unk40->unk14 + 100.0f, D_ovl10_13_8004ADC4->unk40->unk18);
        }
        func_ovl10_13_8004A170();
    }
    if (D_ovl10_13_8004ADA8 == 0x1E) {
        func_ovl10_13_8004A828();
        D_ovl10_13_8004ADB4 = 0;
        func_ovl10_13_8004A138();
    }
    func_ovl10_13_80049E08(1);
    func_ovl10_13_80049E18(D_ovl10_13_8004ADC0->unk40->unk10, 50.0f, D_ovl10_13_8004ADC0->unk40->unk18);
    func_ovl10_13_80049E38(D_ovl10_13_8004ADC0->unk40->unk20, 20.0f, 800.0f);
    func_ovl10_13_800497C8(0);
    D_ovl10_13_8004ADBC = 1;
    func_ovl10_13_80049778(0x20);
    func_ovl10_13_8004A350();
    D_ovl10_13_8004ADB8 = 1;
}

static void func_ovl10_13_80043070(void) {
    UnkStruct_ovl10_13_80049728 *s;
    UnkStructA *obj;
    UnkStructA *pair[2];
    UnkStructA *obj2;
    UnkStructA *ring;
    UnkStructA_40 *fx;
    s32 task;
    Vec3f a;
    Vec3f b;
    f32 x;
    f32 step;
    f32 angle;
    f32 scale;
    s32 i;
    s32 j;
    s32 n;
    s32 m;
    s32 k;
    f32 y;

    if ((D_ovl10_13_8004ADBC != 0) || ((D_ovl10_13_8004ADA8 == 0x1F) && (D_ovl10_13_8004ADE4 == 0))) {
        if (D_ovl10_13_8004ADA8 == 0x1F) {
            D_ovl10_13_8004ADE4 = 1;
        }
        func_ovl10_13_8004A710(0x7F);
        func_ovl10_13_8004A6F0(0x7F);
        for (i = 0; i < 100; i++) {
            func_ovl10_13_8004A390(i + 0x2C);
        }
        for (i = 0, n = 0; i < 95; i++) {
            if (func_ovl10_13_8004A390(i + 0x2C) != 0) {
                n++;
            }
        }
        for (i = 95, j = 0; i < 100; i++) {
            if (func_ovl10_13_8004A390(i + 0x2C) != 0) {
                j++;
            }
        }
        s = func_ovl10_13_80049728();
        func_ovl10_13_8004A3C0(21);
        i = ((s->unk28 >= s->unk30) ? 1 : 0) + s->unk2C;
        if (i < j) {
            i = j;
        }
        if ((D_ovl10_13_8004ADA8 == 0x1F) || ((func_ovl10_13_8004A390(0xA4) == 0) && ((n + i) >= 100))) {
            obj = func_ovl10_13_8004A000(0x328, 0x01000000, 0xC0, 0);
            func_ovl10_13_8004A010(obj);
            func_ovl10_13_80049D00(obj->unk40, 0x16, 0);
            obj->unk40->unk48->unk4->unk4 = func_ovl10_13_80049D18(obj->unk40, 0) - 0.01f;
            obj->unk40->unk10 = D_ovl10_13_8004ADC4->unk40->unk10 + 1000.0f;
            obj->unk40->unk14 = D_ovl10_13_8004ADC4->unk40->unk14 + 467.0f;
            obj->unk40->unk18 = D_ovl10_13_8004ADC4->unk40->unk18;
            obj->unk40->unk20 = 270.0f;
            if (D_ovl10_13_8004ADA8 != 0x1F) {
                func_ovl10_13_80049E18(D_ovl10_13_8004ADC4->unk40->unk10 + 50.0f, D_ovl10_13_8004ADC4->unk40->unk14, D_ovl10_13_8004ADC4->unk40->unk18);
                func_ovl10_13_80049E38(0.0f, 60.0f, 1300.0f);
                func_ovl10_13_8004A128(func_ovl10_13_80047418, obj, 0, 0, 0x130);
                func_ovl10_13_8004A6B0(0x256);
                for (j = 0; j < 140; j++) {
                    D_ovl10_13_8004ADC8->unk40->unk14 += 3.3333333f;
                    D_ovl10_13_8004ADC4->unk40->unk14 += 3.3333333f;
                    func_ovl10_13_80049E18(D_ovl10_13_8004ADC4->unk40->unk10 + 50.0f, D_ovl10_13_8004ADC4->unk40->unk14, D_ovl10_13_8004ADC4->unk40->unk18);
                    func_ovl10_13_8004A170();
                }
                func_ovl10_13_8004A6C0(0x2C);
                func_ovl10_13_8004A6B0(0x257);
                func_ovl10_13_8004A578(0, D_ovl10_13_8004ADC4->unk40->unk10 + 50.0f, D_ovl10_13_8004ADC4->unk40->unk14, D_ovl10_13_8004ADC4->unk40->unk18, 0);
                D_ovl10_13_8004ADC4->unk68 = D_ovl10_13_8004ADC8->unk68 = 0.0f;
                D_ovl10_13_8004ADC4->unk70 = D_ovl10_13_8004ADC8->unk70 = 0.8166667f;
                D_ovl10_13_8004ADC4->unk6C = D_ovl10_13_8004ADC8->unk6C = 16.333334f;
                for (j = 0; j < 60; j++) {
                    D_ovl10_13_8004ADC4->unk40->unk10 -= 8.333333f;
                    D_ovl10_13_8004ADC8->unk40->unk10 += 8.333333f;
                    func_ovl10_13_8004A058(D_ovl10_13_8004ADC4);
                    func_ovl10_13_8004A058(D_ovl10_13_8004ADC8);
                    func_ovl10_13_8004A170();
                }
                D_ovl10_13_8004ADC8->unk40->unk10 = 3500.0f;
                D_ovl10_13_8004ADC8->unk40->unk14 = 900.0f;
                D_ovl10_13_8004ADC8->unk40->unk18 = 400.0f;
                D_ovl10_13_8004ADC8->unk40->unk24 = 180.0f;
                func_ovl10_13_80049E18(D_ovl10_13_8004ADC8->unk40->unk10, 0.0f, D_ovl10_13_8004ADC8->unk40->unk18);
                func_ovl10_13_80049E38(337.0f, 13.0f, 2200.0f);
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
            D_ovl10_13_8004ADC4->unk40->unkC |= 0x4000;
            D_ovl10_13_8004ADC4->unk40->unk48->unk4->unk8 |= 0x60;
            if (D_ovl10_13_8004ADA8 != 0x1F) {
                func_ovl10_13_8004A148(0x14);
                for (j = 0; j < 30; j++) {
                    D_ovl10_13_8004ADC8->unk40->unk14 -= 53.333332f;
                    func_ovl10_13_8004A170();
                }
                func_ovl10_13_8004A148(0x1E);
            }
            func_ovl10_13_80049E18(D_ovl10_13_8004ADC4->unk40->unk10 - 200.0f, 50.0f, D_ovl10_13_8004ADC4->unk40->unk18 + 200.0f);
            func_ovl10_13_80049E38(0.0f, 30.0f, 1800.0f);
            func_ovl10_13_8004A148(0x1E);
            for (j = 0; j < 30; j++) {
                D_ovl10_13_8004ADC4->unk40->unk14 -= 29.0f;
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_8004A6B0(0x259);
            func_ovl10_13_8004A6B0(0x25A);
            func_ovl10_13_8004A578(0xD, D_ovl10_13_8004ADC4->unk40->unk10, D_ovl10_13_8004ADC4->unk40->unk14, D_ovl10_13_8004ADC4->unk40->unk18, 0);
            D_ovl10_13_8004ADC4->unk40->unk14 = 0.0f;
            obj2 = func_ovl10_13_8004A000(0x346, 0x01080000, 0xC0, 0);
            func_ovl10_13_8004A010(obj2);
            obj2->unk40->unk10 = D_ovl10_13_8004ADC4->unk40->unk10;
            obj2->unk40->unk14 = D_ovl10_13_8004ADC4->unk40->unk14;
            obj2->unk40->unk18 = D_ovl10_13_8004ADC4->unk40->unk18;
            obj2->unk68 = 30.0f;
            obj2->unk6C = 16.333334f;
            obj2->unk70 = 1.6333334f;
            D_ovl10_13_8004ADC0->unk68 = 30.0f;
            D_ovl10_13_8004ADC0->unk70 = 1.6333334f;
            D_ovl10_13_8004ADC0->unk6C = 16.333334f;
            D_ovl10_13_8004ADC4->unk68 = 30.0f;
            D_ovl10_13_8004ADC4->unk70 = 1.6333334f;
            D_ovl10_13_8004ADC4->unk6C = 16.333334f;
            func_ovl10_13_8004A198(0x70, 0x70, 0);
            func_ovl10_13_80049868(0, 8);
            D_ovl10_13_8004ADC0->unk40->unk48->unk4->unk8 |= 0x60;
            func_ovl10_13_80049D30(D_ovl10_13_8004ADC0->unk40, 4, 4);
            func_ovl10_13_80049D30(D_ovl10_13_8004ADC0->unk40, 5, 5);
            for (j = 0; j < 20; j++) {
                obj2->unk40->unk10 -= 9.0f;
                obj2->unk40->unk18 += 9.0f;
                D_ovl10_13_8004ADC0->unk40->unk10 -= 7.5f;
                D_ovl10_13_8004ADC0->unk40->unk18 += 7.5f;
                D_ovl10_13_8004ADC4->unk40->unk10 -= 3.0f;
                D_ovl10_13_8004ADC4->unk40->unk18 += 3.0f;
                if (obj2->unk40->unk14 > 50.0f) {
                    func_ovl10_13_8004A058(obj2);
                } else {
                    obj2->unk40->unk14 = 50.0f;
                }
                if (D_ovl10_13_8004ADC4->unk40->unk14 > 30.0f) {
                    func_ovl10_13_8004A058(D_ovl10_13_8004ADC4);
                } else {
                    D_ovl10_13_8004ADC4->unk40->unk14 = 30.0f;
                }
                func_ovl10_13_8004A058(D_ovl10_13_8004ADC0);
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_8004A148(0x1E);
            obj->unk40->unk10 = 2750.0f;
            obj->unk40->unk14 = 400.0f;
            obj->unk40->unk18 = 650.0f;
            obj->unk40->unk20 = 315.0f;
            func_ovl10_13_8004A6B0(0x213);
            for (j = 0; j < 30; j++) {
                obj->unk40->unk10 -= 16.666666f;
                obj->unk40->unk18 += 16.666666f;
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_8004A6B0(0x211);
            i = func_ovl10_13_80049D18(obj->unk40, 0);
            for (j = 0; j < i; j++) {
                obj->unk40->unk10 -= 200.0f / i;
                obj->unk40->unk18 += 200.0f / i;
                obj->unk40->unk14 -= 400.0f / i;
                obj->unk40->unk20 += 90.0f / i;
                obj->unk40->unk48->unk4->unk4 -= 1.0f;
                if (obj->unk40->unk48->unk4->unk4 < 0.0f) {
                    obj->unk40->unk48->unk4->unk4 = 0.0f;
                }
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_80049D00(obj->unk40, 7, 0);
            func_ovl10_13_80049FD8(obj, 0x04000000);
            i = func_ovl10_13_80049D18(obj->unk40, 0);
            for (j = 0; j < i; j++) {
                obj2->unk40->unk14 += 100.0f / i;
                obj2->unk40->unk10 -= 10.0f / i;
                obj2->unk40->unk18 -= 10.0f / i;
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_8004A6B0(0x265);
            task = func_ovl10_13_8004A128(func_ovl10_13_80047298, obj2, 0, 0, 0x130);
            func_ovl10_13_8004A148(0x1E);
            func_ovl10_13_8004A130(task);
            pair[0] = obj;
            pair[1] = obj2;
            task = func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_800470C8, pair, 0, 0, 0x130);
            func_ovl10_13_8004A148(0xB4);
            D_ovl10_13_8004ADC4->unk40->unk48->unk4->unk8 &= ~0x40;
            while (!(D_ovl10_13_8004ADC4->unk40->unk48->unk4->unk8 & 0x40)) {
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_8004A130(task);
            func_ovl10_13_8004A750(obj2->unk40);
            func_ovl10_13_8004A750(obj->unk40);
            func_ovl10_13_80049FE0(obj, 0x04000000);
            i = func_ovl10_13_80049D18(obj->unk40, 0);
            for (j = 0; j < i; j++) {
                obj2->unk40->unk14 -= 100.0f / i;
                obj2->unk40->unk10 += 10.0f / i;
                obj2->unk40->unk18 += 10.0f / i;
                obj->unk40->unk48->unk4->unk4 -= 1.0f;
                if (obj->unk40->unk48->unk4->unk4 < 0.0f) {
                    obj->unk40->unk48->unk4->unk4 = 0.0f;
                }
                func_ovl10_13_8004A170();
            }
            for (j = 0; j < 30; j++) {
                obj->unk40->unk20 += 3.0f;
                func_ovl10_13_8004A170();
            }
            if (D_ovl10_13_8004ADA8 != 0x1F) {
                func_ovl10_13_80049D40(0x335, 1);
            }
            func_ovl10_13_8004A148(0x1E);
            func_ovl10_13_80049868(0, 0);
            D_ovl10_13_8004ADC0->unk40->unk48->unk4->unk8 |= 0x60;
            obj->unk40->unk20 = func_ovl10_13_80043010(obj->unk40, D_ovl10_13_8004ADC0->unk40);
            func_ovl10_13_80049E18(obj->unk40->unk10, 100.0f, obj->unk40->unk18);
            func_ovl10_13_80049E38(obj->unk40->unk20, 5.0f, 800.0f);
            x = func_ovl10_13_8004A2D0(obj->unk40->unk20);
            step = func_ovl10_13_8004A2D8(obj->unk40->unk20);
            for (j = 0; j < 10; j++) {
                obj->unk40->unk10 += x * 12.0f;
                obj->unk40->unk18 += step * 12.0f;
                func_ovl10_13_80049E18(obj->unk40->unk10, 100.0f, obj->unk40->unk18);
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_8004A6B0(0x25B);
            func_ovl10_13_8004A578(0, D_ovl10_13_8004ADC4->unk40->unk10, D_ovl10_13_8004ADC4->unk40->unk14, D_ovl10_13_8004ADC4->unk40->unk18, 0);
            for (j = 0; j < 30; j++) {
                D_ovl10_13_8004ADC4->unk40->unk14 += 6.6666665f;
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_80049E18(2168.0f, 278.0f, 1174.0f);
            func_ovl10_13_80049E38(48.0f, 5.0f, 1652.0f);
            func_ovl10_13_80049D00(D_ovl10_13_8004ADC4->unk40, 0, 0);
            func_ovl10_13_80049FE0(D_ovl10_13_8004ADC4, 0x04000000);
            x = -500.0f;
            D_ovl10_13_8004ADC4->unk40->unk1C = 270.0f;
            for (j = 0; j < 50; j++) {
                if (j >= 20) {
                    func_ovl10_13_80049E18(D_ovl10_13_8004ADC4->unk40->unk10, D_ovl10_13_8004ADC4->unk40->unk14, D_ovl10_13_8004ADC4->unk40->unk18);
                    func_ovl10_13_80049E38(32768.0f, 32768.0f, 900.0f);
                }
                D_ovl10_13_8004ADC4->unk40->unk10 += 10.0f;
                D_ovl10_13_8004ADC4->unk40->unk14 = (x * x * -0.0016f) + 400.0f;
                ANGLE_ADD(D_ovl10_13_8004ADC4->unk40->unk20, 20.0f);
                x += 10.0f;
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_80049E18(obj->unk40->unk10, 100.0f, obj->unk40->unk18);
            func_ovl10_13_80049E38(32768.0f, 16.0f, 900.0f);
            func_ovl10_13_8004A6B0(0x25C);
            func_ovl10_13_80049D00(obj->unk40, 0x17, 0);
            func_ovl10_13_80049FD8(obj, 0x04000000);
            a.x = obj->unk40->unk10 + 10.0f;
            a.y = obj->unk40->unk14 + 50.0f;
            a.z = obj->unk40->unk18 + 50.0f;
            b.x = obj->unk40->unk10 + 10.0f;
            b.y = obj->unk40->unk14 + 50.0f;
            b.z = obj->unk40->unk18 - 50.0f;
            func_ovl10_13_8004A6B0(0x25E);
            for (j = 0; j < 4; j++) {
                func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80046E88, &a, 0, 0, 0x130);
                func_ovl10_13_8004A128((void (*)(UnkStructA *)) func_ovl10_13_80046E88, &b, 0, 0, 0x130);
            }
            fx = func_ovl10_13_80049CB8(0x2C7, 0);
            fx->unkC |= 0x80;
            fx->unk36 = 0x80;
            fx->unk10 = a.x;
            fx->unk14 = a.y;
            fx->unk18 = a.z;
            fx->unk28 = fx->unk2C = fx->unk30 = 0.5f;
            D_ovl10_13_8004ADA4 = func_ovl10_13_80049CB8(0x2C7, 0);
            D_ovl10_13_8004ADA4->unkC |= 0x80;
            D_ovl10_13_8004ADA4->unk36 = 0x80;
            D_ovl10_13_8004ADA4->unk10 = b.x;
            D_ovl10_13_8004ADA4->unk14 = b.y;
            D_ovl10_13_8004ADA4->unk18 = b.z;
            D_ovl10_13_8004ADA4->unk28 = D_ovl10_13_8004ADA4->unk2C = D_ovl10_13_8004ADA4->unk30 = 0.5f;
            angle = 0.0f;
            scale = 0.5f;
            for (j = 0; j < 150; j++) {
                fx->unk28 = fx->unk2C = fx->unk30 = (func_ovl10_13_8004A2D0(angle) * 0.5f) + scale;
                D_ovl10_13_8004ADA4->unk28 = D_ovl10_13_8004ADA4->unk2C = D_ovl10_13_8004ADA4->unk30 = (func_ovl10_13_8004A2D0(angle) * 0.5f) + scale;
                ANGLE_ADD(angle, 0.5f);
                scale += 0.0033333334f;
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_8004A148(0x3C);
            func_ovl10_13_8004A6B0(0x260);
            func_ovl10_13_8004A430(0xFF, 0xFF, 0xFF, 0x14);
            func_ovl10_13_80049CC0(fx);
            func_ovl10_13_80049CC0(D_ovl10_13_8004ADA4);
            fx = func_ovl10_13_80049CB8(0x2D5, 0xA);
            fx->unkC |= 0x80;
            fx->unk36 = 0x50;
            fx->unk10 = a.x + 40.0f;
            fx->unk14 = a.y + 40.0f;
            fx->unk18 = a.z;
            fx->unk24 = 295.0f;
            fx->unk2C = 70.0f;
            fx->unk28 = fx->unk30 = 3.0f;
            D_ovl10_13_8004ADA4 = func_ovl10_13_80049CB8(0x2D5, 0xA);
            D_ovl10_13_8004ADA4->unkC |= 0x80;
            D_ovl10_13_8004ADA4->unk36 = 0x50;
            D_ovl10_13_8004ADA4->unk10 = b.x + 40.0f;
            D_ovl10_13_8004ADA4->unk14 = b.y + 40.0f;
            D_ovl10_13_8004ADA4->unk18 = b.z;
            D_ovl10_13_8004ADA4->unk24 = 295.0f;
            D_ovl10_13_8004ADA4->unk2C = 70.0f;
            fx->unk30 = 3.0f;
            D_ovl10_13_8004ADA4->unk28 = 3.0f;
            func_ovl10_13_80049E18(2520.0f, 249.0f, 1392.0f);
            func_ovl10_13_80049E38(0.0f, 18.0f, 2353.0f);
            for (j = 0; j < 120; j++) {
                ANGLE_ADD(fx->unk20, 15.0f);
                ANGLE_ADD(D_ovl10_13_8004ADA4->unk20, 15.0f);
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_80049E18(D_ovl10_13_8004ADC4->unk40->unk10, D_ovl10_13_8004ADC4->unk40->unk14, D_ovl10_13_8004ADC4->unk40->unk18);
            func_ovl10_13_80049E38(0.0f, 18.0f, 900.0f);
            func_ovl10_13_80049FE0(D_ovl10_13_8004ADC4, 0x01000000);
            ring = func_ovl10_13_8004A000(0x326, 0x01000000, 0xD0, 0);
            ring->unk40->unk10 = D_ovl10_13_8004ADC4->unk40->unk10;
            ring->unk40->unk14 = D_ovl10_13_8004ADC4->unk40->unk14;
            ring->unk40->unk18 = D_ovl10_13_8004ADC4->unk40->unk18;
            ring->unk40->unk1C = D_ovl10_13_8004ADC4->unk40->unk1C;
            ring->unk40->unk20 = D_ovl10_13_8004ADC4->unk40->unk20;
            ring->unk40->unk24 = D_ovl10_13_8004ADC4->unk40->unk24;
            ring->unk40->unk36 = 0xFF;
            ring->unk40->unkC |= 0x40000;
            func_ovl10_13_8004A6B0(0x262);
            for (j = 0; j < 120; j++) {
                ANGLE_ADD(fx->unk20, 15.0f);
                ANGLE_ADD(D_ovl10_13_8004ADA4->unk20, 15.0f);
                ring->unk40->unk36 = ring->unk40->unk36 - 2.125f;
                if (ring->unk40->unk36 < 0) {
                    ring->unk40->unk36 = 0;
                }
                func_ovl10_13_8004A170();
                if ((D_ovl10_13_8004ADA8 == 0x1F) && (j == 49)) {
                    break;
                }
            }
            if (D_ovl10_13_8004ADA8 == 0x1F) {
                func_ovl10_13_8004A828();
                func_ovl10_13_80049CC0(fx);
                func_ovl10_13_80049CC0(D_ovl10_13_8004ADA4);
                D_ovl10_13_8004ADB4 = 0;
                func_ovl10_13_8004A138();
            }
            func_ovl10_13_80049FF0(ring);
            for (j = 0; j < 120; j++) {
                ANGLE_ADD(fx->unk20, 15.0f);
                ANGLE_ADD(D_ovl10_13_8004ADA4->unk20, 15.0f);
                fx->unk28 -= 0.025f;
                fx->unk30 -= 0.025f;
                D_ovl10_13_8004ADA4->unk28 -= 0.025f;
                D_ovl10_13_8004ADA4->unk30 -= 0.025f;
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_80049CC0(fx);
            func_ovl10_13_80049CC0(D_ovl10_13_8004ADA4);
            func_ovl10_13_80049E18(obj2->unk40->unk10, 100.0f, obj2->unk40->unk18);
            func_ovl10_13_80049E38(42.0f, 26.0f, 1360.0f);
            obj->unk40->unk10 = 2210.0f;
            obj->unk40->unk18 = 1390.0f;
            for (j = 0; j < 30; j++) {
                ANGLE_SUB(obj->unk40->unk20, 4.0f);
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_80049D40(0x336, 3);
            func_ovl10_13_80049D00(obj->unk40, 7, 0);
            func_ovl10_13_80049FD8(obj, 0x04000000);
            i = func_ovl10_13_80049D18(obj->unk40, 0);
            for (j = 0; j < i; j++) {
                obj2->unk40->unk14 += 100.0f / i;
                obj2->unk40->unk10 += 10.0f / i;
                obj2->unk40->unk18 -= 10.0f / i;
                func_ovl10_13_8004A170();
            }
            func_ovl10_13_80049868(0, 4);
            D_ovl10_13_8004ADC0->unk40->unk48->unk4->unk8 |= 0x20;
            func_ovl10_13_8004A6B0(0x20F);
            for (j = 0; j < 30; j++) {
                obj->unk40->unk14 += 33.333332f;
                obj2->unk40->unk14 += 33.333332f;
                func_ovl10_13_8004A170();
            }
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
