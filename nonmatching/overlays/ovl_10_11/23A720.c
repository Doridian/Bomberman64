/*
 * NON_MATCHING: ovl_10_11's game object, complete: every function and its
 * .data/.bss/.rodata (sizes 0x150/0x450/0xB0 as the original); .text one
 * word short. Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING
 * drafts").
 * flags: -O3
 * differing words: us 81, eu 81, jp 81
 *
 * What still differs in us (words; eu and jp the same):
 * - func_ovl10_11_800431AC (6): 800469F8/800469FC are loaded in the
 *   order of the stores (the original loads them as the call's
 *   arguments, a1 first) and the call's `move a2,zero` is scheduled
 *   before the jal. Its frame needs the three unused locals.
 * - func_ovl10_11_80043C2C (62): one word short. The original builds
 *   the addresses of 80046A68-80046AB0 in registers (lui/addiu/addu,
 *   a2/a3/t0/t1); ours stores three of them through `at`. A while loop
 *   strength-reduces every array; the do/if form keeps the multu as the
 *   original. A whole-file permuter run found nothing.
 * - func_ovl10_11_80044150 (2): the two stores of `y` (sp+0x74 and the
 *   call's sp+0x18) swap.
 * - func_ovl10_11_80044C24 (11): the same code; the padding IDO puts
 *   after its endless loop (to a 16-byte boundary) is a word longer
 *   because 80043C2C is a word short.
 *
 * ovl_10_11's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). The task functions
 * (8004304C, 80044134-80044C24, with the strings "trap task:entry failed"
 * and "task_entry>%d:%s") are in every one of bank 0x10's overlays.
 */

#include "common.h"

/* What func_ovl10_11_80045D80 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_11_80045D80;

void func_ovl10_11_80044E68(const char *, ...);
void func_ovl10_11_800451A8(s32);
void func_ovl10_11_800451B0(s32, f32, f32, f32, s32, s32);
void func_ovl10_11_800451C0(s32);
void func_ovl10_11_800451E0(s32, s32, s32, s32);
void func_ovl10_11_80045200(f32, f32, f32, s32 *, s32);
void func_ovl10_11_80045208(f32, f32, f32, Vec3f *, s32);
f32 func_ovl10_11_80045248(s32);
void func_ovl10_11_80045250(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_11_80045258(s32, s32, s32, s32, s32, s32);
void func_ovl10_11_80045260(s32);
void func_ovl10_11_80045290(void (*)(UnkStructA *));
void func_ovl10_11_800452A0(s32, s32, s32);
s32 *func_ovl10_11_800452F8(void);
void func_ovl10_11_80045310(s32);
void func_ovl10_11_80045358(void);
void func_ovl10_11_80045360(s32, s32, s32);
s32 func_ovl10_11_80045378(s32, s32, s32, s32, s32);
s32 func_ovl10_11_80045388(void);
void func_ovl10_11_80045398(s32);
void func_ovl10_11_800453A8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_11_800453B8(void);
void func_ovl10_11_800453C0(s32);
void func_ovl10_11_800453D0(s32);
UnkStructA *func_ovl10_11_800453E8(s32);
void func_ovl10_11_80045400(s32);
void func_ovl10_11_800459E8(f32, f32, f32);
void func_ovl10_11_80045A08(f32, f32, f32);
void func_ovl10_11_80045A10(f32 *, f32 *, f32 *);
void func_ovl10_11_80045A50(s32);
void func_ovl10_11_80045A70(f32);
void func_ovl10_11_80045A78(f32);
void func_ovl10_11_80045A90(f32);
void func_ovl10_11_80045BB0(UnkStructA *, s32);
void func_ovl10_11_80045BC0(UnkStructA *);
UnkStructA *func_ovl10_11_80045BD0(s32, s32, s32, s32);
void func_ovl10_11_80045C28(UnkStructA *);
void func_ovl10_11_80045C78(UnkStructA *, Vec3f *);
void func_ovl10_11_80045CF8(void (*)(void), s32, s32, s32, s32);
void func_ovl10_11_80045D18(s32);
void func_ovl10_11_80045D40(void);
void func_ovl10_11_80045D70(s32, s32);
UnkStruct_ovl10_11_80045D80 *func_ovl10_11_80045D80(void);
void func_ovl10_11_80045D90(UnkStruct_ovl10_11_80045D80 *, s32);
s32 *func_ovl10_11_80045F90(void);
void func_ovl10_11_80045FF8(s32, s32, s32, f32);
void func_ovl10_11_80046038(s32, s32, s32, s32, s32);
void func_ovl10_11_80046048(s32, s32, s32);
void func_ovl10_11_80046060(u32 (*)[3]);
void func_ovl10_11_80046150(s32, Vec3f *, s32);
void func_ovl10_11_80046208(s32, s32, s32);
void func_ovl10_11_80046280(s32);
void func_ovl10_11_800462A0(s32, f32, f32, f32);

void func_ovl10_11_80043010(void);
void func_ovl10_11_80043018(void);
s32 func_ovl10_11_8004304C(void (*)(void));
void func_ovl10_11_800430C4(s32, f32, f32, f32);
void func_ovl10_11_800431AC(void);
void func_ovl10_11_80043298(void);
s32 func_ovl10_11_800433D4(s32);
void func_ovl10_11_800436A4(void);
void func_ovl10_11_800436C4(void);
void func_ovl10_11_800436E4(void);
void func_ovl10_11_80043788(void);
void func_ovl10_11_800437A8(void);
void func_ovl10_11_8004390C(void);
void func_ovl10_11_800439BC(void);
void func_ovl10_11_80043A64(void);
void func_ovl10_11_80043A94(void);
void func_ovl10_11_80043B10(s32);
void func_ovl10_11_80043C2C(s32 *);
void func_ovl10_11_80043D98(void);
void func_ovl10_11_80043EBC(s32);
void func_ovl10_11_80043FD8(s32);
void func_ovl10_11_80044010(void);
void func_ovl10_11_80044134(void);
void func_ovl10_11_80044150(void);
void func_ovl10_11_800445A4(s32 *);
void func_ovl10_11_80044658(s32, s32);
void func_ovl10_11_800447B0(void);
void func_ovl10_11_80044978(UnkStructA *);
void func_ovl10_11_800449F8(UnkStructA *);
void func_ovl10_11_80044A64(void);
void func_ovl10_11_80044AA0(void);
void func_ovl10_11_80044B30(void (*)(void));
void func_ovl10_11_80044B4C(s32);
void func_ovl10_11_80044B68(s32);
s32 func_ovl10_11_80044B7C(void (*)(void));
void func_ovl10_11_80044BC0(void (*)(void));
s32 func_ovl10_11_80044BEC(void (*)(void), const char *);
void func_ovl10_11_80044C24(void);
void func_ovl10_11_80044D18(s32, UnkStructA *);
void func_ovl10_11_80044D4C(f32);
void func_ovl10_11_80044D94(f32, f32, f32);
void func_ovl10_11_80044DF0(void);
void func_ovl10_11_80044E08(void);

void func_ovl10_11_80043044(void);

/* .bss */
u8 D_ovl10_11_800466A0[0x24];
s32 D_ovl10_11_800466C4;
s32 D_ovl10_11_800466C8;
u8 D_ovl10_11_800466CC[0x4]; /* unused (func_ovl10_11_80044E08) */
Vec3f D_ovl10_11_800466D0;
s32 D_ovl10_11_800466DC;
s32 D_ovl10_11_800466E0;
s32 D_ovl10_11_800466E4;
/* the tasks: a countdown and a function each */
s32 D_ovl10_11_800466E8[64];
s32 D_ovl10_11_800467E8; /* the running task */
u8 D_ovl10_11_800467EC[0x4]; /* unused (func_ovl10_11_80044E08) */
void (*D_ovl10_11_800467F0[64])(void);
UnkStruct_ovl10_11_80045D80 *D_ovl10_11_800468F0;
u8 D_ovl10_11_800468F4[0x4]; /* unused (func_ovl10_11_80044E08) */
s32 D_ovl10_11_800468F8[4][3];
UnkStructA *D_ovl10_11_80046928[4];
s32 D_ovl10_11_80046938;
u8 D_ovl10_11_8004693C[0x4]; /* unused (func_ovl10_11_80044E08) */
s32 D_ovl10_11_80046940[4];
s32 D_ovl10_11_80046950[4];
s32 D_ovl10_11_80046960[5];
s32 D_ovl10_11_80046974;
f32 D_ovl10_11_80046978;
f32 D_ovl10_11_8004697C;
f32 D_ovl10_11_80046980;
u8 D_ovl10_11_80046984[0x4]; /* unused (func_ovl10_11_80044E08) */
s32 D_ovl10_11_80046988[6][3];
UnkStructA *D_ovl10_11_800469D0[6];
UnkStructA *D_ovl10_11_800469E8;
s32 D_ovl10_11_800469EC;
s32 D_ovl10_11_800469F0;
s32 D_ovl10_11_800469F4;
s32 D_ovl10_11_800469F8;
s32 D_ovl10_11_800469FC;
s32 D_ovl10_11_80046A00[6];
s32 D_ovl10_11_80046A18[6];
s32 D_ovl10_11_80046A30[6];
s32 D_ovl10_11_80046A48;
u8 D_ovl10_11_80046A4C[0x4]; /* unused (func_ovl10_11_80044E08) */
s32 D_ovl10_11_80046A50[6];
s32 D_ovl10_11_80046A68[6];
s32 D_ovl10_11_80046A80[6];
s32 D_ovl10_11_80046A98[6];
s32 D_ovl10_11_80046AB0[6];
f32 D_ovl10_11_80046AC8;
f32 D_ovl10_11_80046ACC;
f32 D_ovl10_11_80046AD0;
f32 D_ovl10_11_80046AD4;
f32 D_ovl10_11_80046AD8;
f32 D_ovl10_11_80046ADC;
f32 D_ovl10_11_80046AE0;

/* .data, defined below func_ovl10_11_80043B10 */
extern u32 D_ovl10_11_800464B8[][3];
extern s32 D_ovl10_11_800464DC[];

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_11_80044E58(void) {
}

static void func_ovl10_11_80044E50(void) {
}

static void func_ovl10_11_80044E48(void) {
}

static void func_ovl10_11_80044E40(void) {
}

static void func_ovl10_11_80044E38(void) {
}

static void func_ovl10_11_80044E30(void) {
}

static void func_ovl10_11_80044E28(void) {
}

static void func_ovl10_11_80044E20(void) {
}

static void func_ovl10_11_80044E18(void) {
}

static void func_ovl10_11_80044E10(void) {
}

void func_ovl10_11_80044E08(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_11_800466A0[0] = D_ovl10_11_800466CC[0] + D_ovl10_11_800467EC[0] + D_ovl10_11_800468F4[0] +
                                 D_ovl10_11_8004693C[0] + D_ovl10_11_80046984[0] + D_ovl10_11_80046A4C[0];
    }
}

void func_ovl10_11_80044DF0(void) {
    D_ovl10_11_800466C4 = -1;
    D_ovl10_11_800466C8 = -1;
}

void func_ovl10_11_80044D94(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_11_800459E8(D_ovl10_11_800466D0.x, D_ovl10_11_800466D0.y, D_ovl10_11_800466D0.z);
    func_ovl10_11_80045A08(arg0, arg1, arg2);
    func_ovl10_11_80045D18(180);
}

void func_ovl10_11_80044D4C(f32 arg0) {
    f32 sp1C;

    func_ovl10_11_80045A10(&sp1C, NULL, NULL);
    func_ovl10_11_80045A08(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_11_80044D18(s32 arg0, UnkStructA *arg1) {
    func_ovl10_11_800462A0(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_11_80044C24(void) {
    s32 i;

    D_ovl10_11_800466E0 = 0;
    D_ovl10_11_800466E4 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_11_800467F0[i] != NULL) {
                D_ovl10_11_800467E8 = i;
                if (D_ovl10_11_800466E8[i] == 0) {
                    D_ovl10_11_800467F0[i]();
                } else {
                    D_ovl10_11_800466E8[i]--;
                }
            }
        }
        D_ovl10_11_800466E0++;
        D_ovl10_11_800466E0 &= 3;
        func_ovl10_11_80045D40();
    }
}

/* Defined above its caller 80044BEC, which pulls it out among the earlier
 * functions all the same: only so does its string come first in .rodata. */
s32 func_ovl10_11_8004304C(void (*arg0)(void)) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_11_800467F0[i] == NULL) {
            D_ovl10_11_800467F0[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_11_80044E68("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_11_80044BEC(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_11_8004304C(arg0);
    func_ovl10_11_80044E68("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_11_80044BC0(void (*arg0)(void)) {
    D_ovl10_11_800467F0[func_ovl10_11_80044B7C(arg0)] = NULL;
}

s32 func_ovl10_11_80044B7C(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_11_800467F0[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_11_80044B68(s32 arg0) {
    D_ovl10_11_800467F0[arg0] = NULL;
}

void func_ovl10_11_80044B4C(s32 arg0) {
    D_ovl10_11_800466E8[D_ovl10_11_800467E8] = arg0;
}

void func_ovl10_11_80044B30(void (*arg0)(void)) {
    D_ovl10_11_800467F0[D_ovl10_11_800467E8] = arg0;
}

void func_ovl10_11_80044AA0(void) {
    D_ovl10_11_800468F0 = func_ovl10_11_80045D80();
    func_ovl10_11_80045D90(D_ovl10_11_800468F0, 0x20000001);
    D_ovl10_11_800468F0->unk40 = 0.5f;
    D_ovl10_11_800468F0->unk44 = D_ovl10_11_800468F0->unk40 * 0.75f;
    D_ovl10_11_800468F0->unk18 = 0.1f;
    D_ovl10_11_800468F0->unk1C = -0.1f;
}

void func_ovl10_11_80044A64(void) {
    s32 *p;

    p = func_ovl10_11_80045F90();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_11_800449F8(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_11_80045A50(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_11_80045C28(arg0);
        func_ovl10_11_80045D40();
    }
}

void func_ovl10_11_80044978(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_11_80045FF8(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_11_80045BB0(arg0, 0x01000000);
        func_ovl10_11_80045D18(5);
        func_ovl10_11_80045FF8(0, 0, 0, 0.0f);
        func_ovl10_11_80045C78(arg0, &pos);
        func_ovl10_11_80046150(12, &pos, 0);
    }
}

void func_ovl10_11_800447B0(void) {
    s32 found;
    s32 i;

    found = -1;
    i = 0;
    do {
        if (func_ovl10_11_80045378(D_ovl10_11_800468F8[i][0], D_ovl10_11_800468F8[i][1], D_ovl10_11_800468F8[i][2],
                                   D_ovl10_11_800468F8[i][0] + 1, D_ovl10_11_800468F8[i][2] + 1) != 0) {
            found = i;
        }
        i++;
    } while (i < D_ovl10_11_80046938 && found == -1);
    if (found != -1) {
        D_ovl10_11_80046950[found] = (D_ovl10_11_80046950[found] + 1) % 2;
        func_ovl10_11_80044658(found, D_ovl10_11_80046950[found]);
        D_ovl10_11_80046960[D_ovl10_11_80046940[found]] = (D_ovl10_11_80046960[D_ovl10_11_80046940[found]] + 1) % 2;
        if (D_ovl10_11_80046950[found] == 1 && D_ovl10_11_80046940[found] != 4) {
            for (i = 0; i < D_ovl10_11_80046938; i++) {
                if (i != found && D_ovl10_11_80046940[i] != 4 && D_ovl10_11_80046950[i] == 1) {
                    D_ovl10_11_80046950[i] = 0;
                    func_ovl10_11_80044658(i, 0);
                    D_ovl10_11_80046960[D_ovl10_11_80046940[i]] = 0;
                }
            }
        }
    }
}

void func_ovl10_11_80044658(s32 arg0, s32 arg1) {
    s32 sp38[4] = { 0xBF, 0xC0, 0xC1, 0xC4 };
    Vec3f pos;

    if (arg1 == 1) {
        D_ovl10_11_80046928[arg0] =
            func_ovl10_11_80045BD0(sp38[D_ovl10_11_80046940[arg0] - 1], 0x01000000, 0xD0, 0);
        func_ovl10_11_80045208(D_ovl10_11_800468F8[arg0][0], D_ovl10_11_800468F8[arg0][1],
                               D_ovl10_11_800468F8[arg0][2], &pos, 0);
        D_ovl10_11_80046928[arg0]->unk40->unk10 = pos.x;
        D_ovl10_11_80046928[arg0]->unk40->unk14 = pos.y;
        D_ovl10_11_80046928[arg0]->unk40->unk18 = pos.z;
    } else {
        func_ovl10_11_80045BC0(D_ovl10_11_80046928[arg0]);
        D_ovl10_11_80046928[arg0] = NULL;
    }
}

void func_ovl10_11_800445A4(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_11_800468F8[i][0] = arg0[0];
        D_ovl10_11_800468F8[i][1] = arg0[1];
        D_ovl10_11_800468F8[i][2] = arg0[2];
        D_ovl10_11_80046940[i] = arg0[3];
        D_ovl10_11_80046950[i] = 0;
        arg0 += 4;
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_11_80046938 = i;
    for (i = 1; i < 5; i++) {
        D_ovl10_11_80046960[i] = 0;
    }
}

void func_ovl10_11_80044150(void) {
    s32 y;
    s32 i;
    s32 a;
    s32 b;
    s32 out[6];
    s32 *flags;

    i = D_ovl10_11_80046974;
    D_ovl10_11_800469E8 = func_ovl10_11_800453E8(func_ovl10_11_80045388());
    D_ovl10_11_800469D0[i]->unk40->unk14 += D_ovl10_11_80046978;
    D_ovl10_11_800469E8->unk40->unk14 = D_ovl10_11_800469D0[i]->unk40->unk14;
    D_ovl10_11_80046978 += D_ovl10_11_8004697C;
    if (D_ovl10_11_80046AE0 != -1.0f &&
        ((D_ovl10_11_80046978 > 0.0f && D_ovl10_11_80046AE0 <= D_ovl10_11_800469D0[i]->unk40->unk14) ||
         (D_ovl10_11_80046978 < 0.0f && D_ovl10_11_800469D0[i]->unk40->unk14 <= D_ovl10_11_80046AE0))) {
        D_ovl10_11_8004697C = -D_ovl10_11_8004697C;
        D_ovl10_11_80046AE0 = -1.0f;
    }
    if (D_ovl10_11_80046980 != -1.0f &&
        (D_ovl10_11_80046978 == 0.0f ||
         (D_ovl10_11_80046978 > 0.0f && D_ovl10_11_80046980 < D_ovl10_11_800469D0[i]->unk40->unk14) ||
         (D_ovl10_11_80046978 < 0.0f && D_ovl10_11_800469D0[i]->unk40->unk14 < D_ovl10_11_80046980))) {
        flags = func_ovl10_11_800452F8();
        if (!(*flags & 2)) {
            func_ovl10_11_80045310(1);
        }
        func_ovl10_11_80044134();
        D_ovl10_11_800469E8->unk70 = 1.6333334f;
        if (D_ovl10_11_80046978 != 0.0f) {
            D_ovl10_11_800469D0[i]->unk40->unk14 = D_ovl10_11_80046980;
            D_ovl10_11_800469E8->unk40->unk14 = D_ovl10_11_80046980;
        }
        if (D_ovl10_11_80046A00[i] == 2) {
            func_ovl10_11_80045200(D_ovl10_11_800469D0[i]->unk40->unk10, D_ovl10_11_800469D0[i]->unk40->unk14,
                                   D_ovl10_11_800469D0[i]->unk40->unk18, out, 2);
            y = out[1];
            func_ovl10_11_80045250(D_ovl10_11_80046988[i][0], D_ovl10_11_80046988[i][1], D_ovl10_11_80046988[i][2],
                                   D_ovl10_11_80046988[i][0] + 1, D_ovl10_11_80046988[i][2] + 1,
                                   D_ovl10_11_80046988[i][0], y, D_ovl10_11_80046988[i][2]);
            func_ovl10_11_80045258(D_ovl10_11_80046988[i][0], D_ovl10_11_80046988[i][1], D_ovl10_11_80046988[i][2],
                                   D_ovl10_11_80046988[i][0] + 1, D_ovl10_11_80046988[i][2] + 1, 0);
            D_ovl10_11_80046A50[i] = D_ovl10_11_80046988[i][1];
            D_ovl10_11_80046988[i][1] = y;
            if (D_ovl10_11_80046978 > 0.0f) {
                a = D_ovl10_11_80046A68[i];
                b = D_ovl10_11_80046A80[i];
            } else {
                a = D_ovl10_11_80046A98[i];
                b = D_ovl10_11_80046AB0[i];
            }
            func_ovl10_11_800453A8(a, 3, 8.5f, b, 1, 1, 1);
            func_ovl10_11_80045A78(0.1f);
            func_ovl10_11_80045A90(40.0f);
        }
        func_ovl10_11_80045260(0);
        if (!(*flags & 2)) {
            func_ovl10_11_80045398(0);
        }
        func_ovl10_11_80045D70(0xD0, 0xD0);
    }
}

void func_ovl10_11_80044134(void) {
    D_ovl10_11_800467F0[D_ovl10_11_800467E8] = NULL;
}

void func_ovl10_11_80044010(void) {
    s32 i;

    for (i = 0; i < D_ovl10_11_80046A48; i++) {
        if (D_ovl10_11_80046A00[i] == 2 && D_ovl10_11_80046A18[i] != D_ovl10_11_80046960[D_ovl10_11_80046A30[i]]) {
            if (D_ovl10_11_800469D0[i] != NULL) {
                func_ovl10_11_80043FD8(i);
            }
            D_ovl10_11_80046A18[i] = D_ovl10_11_80046960[D_ovl10_11_80046A30[i]];
            func_ovl10_11_80043B10(i);
        }
    }
}

void func_ovl10_11_80043FD8(s32 arg0) {
    func_ovl10_11_80045BC0(D_ovl10_11_800469D0[arg0]);
    D_ovl10_11_800469D0[arg0] = NULL;
}

void func_ovl10_11_80043EBC(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl10_11_80043D98();
            break;
        case 16:
            func_ovl10_11_80043A64();
            break;
        case 17:
            func_ovl10_11_800439BC();
            break;
        case 18:
            func_ovl10_11_8004390C();
            break;
        case 4:
            func_ovl10_11_80043788();
            break;
        case 5:
            func_ovl10_11_800436E4();
            break;
        case 0x53:
            func_ovl10_11_800436C4();
            break;
        case 0x50:
            func_ovl10_11_800436A4();
            break;
        case 1:
            func_ovl10_11_80043018();
            break;
    }
}

void func_ovl10_11_80043D98(void) {
    func_ovl10_11_80046060(D_ovl10_11_800464B8);
    func_ovl10_11_80046208(0, 0, 0xDE);
    func_ovl10_11_80046208(1, 0x11, 0xEF);
    func_ovl10_11_80046208(2, 0x1A, 0xF8);
    func_ovl10_11_80046208(3, 0x1B, 0xF9);
    func_ovl10_11_80046208(4, 0x18, 0xF6);
    func_ovl10_11_800451A8(0x1F0);
    func_ovl10_11_800451C0(0x1F8);
    func_ovl10_11_80046038(0x3C6, 0x3E8, 0, 0xFF, 0xFF);
    func_ovl10_11_80046048(0, 0xFF, 0xFF);
    func_ovl10_11_800451B0(0xC7, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_11_800451B0(0xC7, 0.0f, 12000.0f, 0.0f, 0x50, 0);
    func_ovl10_11_80045358();
    func_ovl10_11_80043C2C(D_ovl10_11_800464DC);
    func_ovl10_11_80045290(func_ovl10_11_80044978);
    func_ovl10_11_80043A94();
}

/* reads records of 11 words up to a -1 */
void func_ovl10_11_80043C2C(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_11_80046988[i][0] = arg0[0];
        D_ovl10_11_80046988[i][1] = arg0[1];
        D_ovl10_11_80046988[i][2] = arg0[2];
        D_ovl10_11_80046A50[i] = arg0[3];
        D_ovl10_11_80046A00[i] = arg0[4];
        D_ovl10_11_80046A18[i] = arg0[5];
        D_ovl10_11_80046A30[i] = arg0[6];
        D_ovl10_11_80046A68[i] = arg0[7];
        D_ovl10_11_80046A80[i] = arg0[8];
        D_ovl10_11_80046A98[i] = arg0[9];
        D_ovl10_11_80046AB0[i] = arg0[10];
        arg0 += 11;
        func_ovl10_11_80043B10(i);
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_11_80046A48 = i;
}

void func_ovl10_11_80043B10(s32 arg0) {
    Vec3f pos;
    s32 sp2C[2] = { 0xCA, 0xB2 };

    D_ovl10_11_800469D0[arg0] = func_ovl10_11_80045BD0(sp2C[D_ovl10_11_80046A18[arg0]], 0x01000000, 0xD0, 0);
    func_ovl10_11_80045208(D_ovl10_11_80046988[arg0][0], D_ovl10_11_80046988[arg0][1], D_ovl10_11_80046988[arg0][2],
                           &pos, 0);
    D_ovl10_11_800469D0[arg0]->unk40->unk10 = pos.x;
    D_ovl10_11_800469D0[arg0]->unk40->unk14 = pos.y;
    D_ovl10_11_800469D0[arg0]->unk40->unk18 = pos.z;
}

/* passed to func_ovl10_11_80046060: three 12-byte records */
u32 D_ovl10_11_800464B8[][3] = {
    { 0xA60002, 0xE, 4 },
    { 0xA50002, 0xF, 4 },
    { 0xA70000, 0xE, 4 },
};

/* passed to func_ovl10_11_80043C2C: six 11-word records and a -1 */
s32 D_ovl10_11_800464DC[] = {
    1,    4, 0xF,  0xFF,       1, 1, 0, 0x73, 0x11, 0,    0,
    0x2D, 0, 0xF,  0xFFFFFF01, 1, 1, 0, 0x6F, 0x13, 0,    0,
    9,    2, 0x17, 4,          2, 1, 0, 0,    2,    0,    2,
    0x17, 4, 0xD,  0,          2, 1, 0, 0x80, 2,    0x80, 2,
    0x17, 3, 0x11, 2,          2, 1, 0, 0,    2,    0,    2,
    0x25, 0, 7,    3,          2, 1, 0, 0x80, 2,    0x80, 2,
    -1,   0, 0,
};

void func_ovl10_11_80043A94(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_11_800467F0[i] = NULL;
        D_ovl10_11_800466E8[i] = 0;
    }
    func_ovl10_11_80045CF8(func_ovl10_11_80044C24, 0, 0, 0, 0x110);
}

void func_ovl10_11_80043A64(void) {
    func_ovl10_11_80045360(0x17, 4, 0x10);
    D_ovl10_11_800466DC = 3;
}

void func_ovl10_11_800439BC(void) {
    D_ovl10_11_80046974 = 0;
    D_ovl10_11_800469EC = 4;
    D_ovl10_11_80046AC8 = 1100.0f;
    D_ovl10_11_80046ACC = 90.0f;
    D_ovl10_11_800469F0 = 1;
    D_ovl10_11_800469F4 = 0xF;
    D_ovl10_11_80046AD0 = -21.0f;
    D_ovl10_11_80046AD4 = 0.2f;
    D_ovl10_11_80046AD8 = 50.0f;
    D_ovl10_11_80046ADC = 50.0f;
    func_ovl10_11_800437A8();
    D_ovl10_11_800466DC = 1;
}

void func_ovl10_11_8004390C(void) {
    D_ovl10_11_80046974 = 1;
    D_ovl10_11_800469EC = 0;
    D_ovl10_11_80046AC8 = -1100.0f;
    D_ovl10_11_80046ACC = 270.0f;
    D_ovl10_11_800469F0 = 0x2D;
    D_ovl10_11_800469F4 = 0xF;
    D_ovl10_11_80046AD0 = 21.0f;
    D_ovl10_11_80046AD4 = -0.2f;
    D_ovl10_11_80046AD8 = 49.0f;
    D_ovl10_11_80046ADC = 50.0f;
    func_ovl10_11_800437A8();
    D_ovl10_11_800466DC = 2;
}

void func_ovl10_11_800437A8(void) {
    f32 y;

    D_ovl10_11_80046AE0 = -1.0f;
    y = func_ovl10_11_80045248(D_ovl10_11_800469EC);
    func_ovl10_11_80045360(D_ovl10_11_800469F0, D_ovl10_11_800469EC, D_ovl10_11_800469F4);
    func_ovl10_11_80045398(1);
    D_ovl10_11_800469E8 = func_ovl10_11_800453E8(func_ovl10_11_80045388());
    D_ovl10_11_800469E8->unk70 = 0.0f;
    D_ovl10_11_800469E8->unk40->unk10 += D_ovl10_11_80046AD8;
    D_ovl10_11_800469E8->unk40->unk14 += D_ovl10_11_80046AC8;
    D_ovl10_11_800469E8->unk40->unk18 += D_ovl10_11_80046ADC;
    D_ovl10_11_800469E8->unk40->unk20 = D_ovl10_11_80046ACC;
    D_ovl10_11_800469D0[D_ovl10_11_80046974]->unk40->unk14 += D_ovl10_11_80046AC8;
    func_ovl10_11_800430C4(D_ovl10_11_80046974, D_ovl10_11_80046AD0, D_ovl10_11_80046AD4, y);
    D_ovl10_11_800469E8->unk70 = 1.6333334f;
}

void func_ovl10_11_80043788(void) {
    func_ovl10_11_800453B8();
}

void func_ovl10_11_800436E4(void) {
    switch (D_ovl10_11_800466DC) {
        case 1:
            func_ovl10_11_80045D18(0x78);
            func_ovl10_11_800453A8(0x40, 3, 8.5f, 2, 0, 1, 1);
            break;
        case 2:
            func_ovl10_11_80045D18(0x78);
            func_ovl10_11_800453A8(0xC0, 3, 8.5f, 2, 0, 1, 1);
            break;
    }
}

void func_ovl10_11_800436C4(void) {
    func_ovl10_11_800433D4(2);
}

void func_ovl10_11_800436A4(void) {
    func_ovl10_11_800433D4(1);
}

s32 func_ovl10_11_800433D4(s32 arg0) {
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    if (arg0 == 2) {
        do {
            if (D_ovl10_11_80046A00[i] == 2 && D_ovl10_11_80046A18[i] == 1 &&
                func_ovl10_11_80045378(D_ovl10_11_80046988[i][0], D_ovl10_11_80046988[i][1],
                                       D_ovl10_11_80046988[i][2], D_ovl10_11_80046988[i][0] + 1,
                                       D_ovl10_11_80046988[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_11_80046A48 && found == 0);
        if (found) {
            D_ovl10_11_80046974 = i;
            if (D_ovl10_11_80046A50[i] < D_ovl10_11_80046988[i][1]) {
                D_ovl10_11_80046AD0 = 0.0f;
                D_ovl10_11_80046AD4 = -0.2f;
            } else {
                D_ovl10_11_80046AD0 = -0.0f;
                D_ovl10_11_80046AD4 = 0.2f;
            }
        }
    } else {
        do {
            if (func_ovl10_11_80045378(D_ovl10_11_80046988[i][0], D_ovl10_11_80046988[i][1],
                                       D_ovl10_11_80046988[i][2], D_ovl10_11_80046988[i][0] + 1,
                                       D_ovl10_11_80046988[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_11_80046A48 && found == 0);
    }
    if (found) {
        D_ovl10_11_80046974 = i;
        if (D_ovl10_11_80046A50[i] < D_ovl10_11_80046988[i][1]) {
            D_ovl10_11_80046AD0 = 0.0f;
            D_ovl10_11_80046AD4 = -0.2f;
        } else {
            D_ovl10_11_80046AD0 = -0.0f;
            D_ovl10_11_80046AD4 = 0.2f;
        }
        if (arg0 == 2) {
            func_ovl10_11_80043298();
        } else {
            D_ovl10_11_800469F8 = D_ovl10_11_80046A68[i];
            D_ovl10_11_800469FC = D_ovl10_11_80046A80[i];
            func_ovl10_11_800431AC();
        }
    }
    return found;
}

void func_ovl10_11_80043298(void) {
    s32 out[6];
    f32 a;
    f32 b;
    s32 i;

    i = D_ovl10_11_80046974;
    a = func_ovl10_11_80045248(D_ovl10_11_80046A50[i]);
    b = func_ovl10_11_80045248(D_ovl10_11_80046988[i][1]);
    func_ovl10_11_800453D0(0x40);
    func_ovl10_11_800453C0(1);
    D_ovl10_11_800469E8 = func_ovl10_11_800453E8(func_ovl10_11_80045388());
    D_ovl10_11_80046AE0 = (a - b) * 0.5f;
    D_ovl10_11_80046AE0 += b;
    D_ovl10_11_800469E8->unk70 = 0.0f;
    func_ovl10_11_80045200(D_ovl10_11_800469E8->unk40->unk10, D_ovl10_11_800469E8->unk40->unk14,
                           D_ovl10_11_800469E8->unk40->unk18, out, 2);
    func_ovl10_11_80045398(1);
    func_ovl10_11_80045A70(10.0f);
    func_ovl10_11_80045A78(5.0f);
    func_ovl10_11_80045A90(0.0f);
    func_ovl10_11_800430C4(i, D_ovl10_11_80046AD0, D_ovl10_11_80046AD4, a);
}

void func_ovl10_11_800431AC(void) {
    s32 out[6];
    s32 pad1;
    s32 pad2;
    s32 pad3;

    D_ovl10_11_80046AE0 = -1.0f;
    func_ovl10_11_800453D0(0x40);
    func_ovl10_11_800453C0(1);
    D_ovl10_11_800469E8 = func_ovl10_11_800453E8(func_ovl10_11_80045388());
    D_ovl10_11_800469E8->unk70 = 0.0f;
    func_ovl10_11_80045200(D_ovl10_11_800469E8->unk40->unk10, D_ovl10_11_800469E8->unk40->unk14,
                           D_ovl10_11_800469E8->unk40->unk18, out, 2);
    func_ovl10_11_800451E0(out[0], out[1], out[2], 0);
    func_ovl10_11_80045398(1);
    func_ovl10_11_800430C4(D_ovl10_11_80046974, D_ovl10_11_80046AD0, D_ovl10_11_80046AD4, -1.0f);
    func_ovl10_11_80045D18(0x78);
    D_ovl10_11_800466C4 = D_ovl10_11_800469F8;
    D_ovl10_11_800466C8 = D_ovl10_11_800469FC;
    func_ovl10_11_800452A0(D_ovl10_11_800469F8, D_ovl10_11_800469FC, 0);
}

void func_ovl10_11_800430C4(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_ovl10_11_80046974 = arg0;
    D_ovl10_11_80046978 = arg1;
    D_ovl10_11_8004697C = arg2;
    D_ovl10_11_80046980 = arg3;
    func_ovl10_11_8004304C(func_ovl10_11_80044150);
    D_ovl10_11_800469E8 = func_ovl10_11_800453E8(func_ovl10_11_80045388());
    D_ovl10_11_800469E8->unk70 = 0.0f;
    func_ovl10_11_80045260(1);
    if (arg1 == 0.0f && arg2 < 0.0f && arg3 == -1.0f) {
        func_ovl10_11_80045400(1);
    }
    func_ovl10_11_80046280(0x98);
    func_ovl10_11_80045310(0);
}

void func_ovl10_11_80043044(void) {
}

void func_ovl10_11_80043018(void) {
    func_ovl10_11_80045FF8(0, 0, 0, 0.0f);
}

void func_ovl10_11_80043010(void) {
}
