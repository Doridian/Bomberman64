/*
 * NON_MATCHING: ovl_0E_15's game object, complete: every function and its
 * data (.rodata and .bss as the original).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 306, eu 306, jp 306
 *
 * What still differs in us (words):
 * - func_ovl0E_15_800444C4 (300): mostly the same code with other registers
 *   and stack slots.  Ours keeps &D_ovl0E_15_80046958 in s2 for its three
 *   `= 0` stores (the original uses `lui at` each time, and s2 for a loop
 *   bound), so the s registers of the later loops differ; dz's slot is 84
 *   where the original's is 80; the three divisions by 60 load 60.0f once
 *   (the original three times) and are scheduled differently.
 * - func_ovl0E_15_800433E0 (6): the frame, 0x98 where the original's is
 *   0xA0, and the spilled random value at 0x70 (the original 0x60).  As in
 *   ovl_12_06 and ovl_0C_10, each function inlined into the handler (here
 *   80043378, 80043340 and 80043010) takes 8 bytes below the locals: with
 *   case 2 written out, plus two unused Vec3f locals, the handler matches,
 *   but then 80043340 and 80043378 come out after it.
 * The text order: 80043340 must be defined above 800444C4 (anywhere above
 * it); defined next to 80043378, the reference to 80045024 it makes pulls
 * 80045024 out ahead of 80044E90.  The two `jr ra; nop` after 80043010 and
 * 800430E4 are statics inlined into the next function, as in ovl_12_06.
 */
#include "common.h"

/*
 * ovl_0E_15's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).  The same skeleton as
 * ovl_0C_10's 194190 and ovl_12_06's 25D670.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_15_80046940;

void func_ovl0E_15_80045508(s32);
void func_ovl0E_15_80045520(s32);
void func_ovl0E_15_80045590(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_15_800455F0(void (*)(UnkStructA *));
s32 func_ovl0E_15_80045608(void);
void func_ovl0E_15_80045640(void (*)(UnkStructA *));
void func_ovl0E_15_80045690(s32, s32);
s32 func_ovl0E_15_800456A0(s32);
void func_ovl0E_15_800456A8(s32);
void func_ovl0E_15_800456B8(void);
void func_ovl0E_15_800456C0(s32, s32, s32);
void func_ovl0E_15_800456C8(void *);
s32 func_ovl0E_15_800456E8(void);
void func_ovl0E_15_800456F0(s32, void *);
void func_ovl0E_15_800456F8(s32);
void func_ovl0E_15_80045700(s32);
void func_ovl0E_15_80045708(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_15_80045718(void);
UnkStructA *func_ovl0E_15_80045748(s32);
void func_ovl0E_15_80045750(s32);
void func_ovl0E_15_80045778(s32);
void func_ovl0E_15_80045798(s32, s32);
UnkStructA_40 *func_ovl0E_15_80045BE8(s32, s32);
void func_ovl0E_15_80045BF0(UnkStructA_40 *);
void func_ovl0E_15_80045C10(UnkStructA_40 *, s32);
void func_ovl0E_15_80045C18(UnkStructA_40 *, s32, s32, s32);
void func_ovl0E_15_80045C30(UnkStructA_40 *, s32, s32);
void func_ovl0E_15_80045D48(f32, f32, f32);
void func_ovl0E_15_80045D50(f32 *, f32 *, f32 *);
void func_ovl0E_15_80045D68(f32, f32, f32);
void func_ovl0E_15_80045D70(f32 *, f32 *, f32 *);
void func_ovl0E_15_80045DA8(s32);
void func_ovl0E_15_80045DB0(s32);
void func_ovl0E_15_80045E18(void);
void func_ovl0E_15_80045E20(s32);
void func_ovl0E_15_80045E30(f32, f32, f32);
void func_ovl0E_15_80045F10(UnkStructA *, s32);
void func_ovl0E_15_80045F20(UnkStructA *);
UnkStructA *func_ovl0E_15_80045F30(s32, s32, s32, s32);
void func_ovl0E_15_80045F40(UnkStructA *);
void func_ovl0E_15_80045F88(UnkStructA *);
void func_ovl0E_15_80046018(UnkStructA *);
s32 func_ovl0E_15_80046058(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_15_80046068(void);
s32 func_ovl0E_15_80046078(s32);
void *func_ovl0E_15_80046080(void);
s32 func_ovl0E_15_800460A0(void);
void func_ovl0E_15_800460C8(s32, s32, s32);
void func_ovl0E_15_800460D0(s32, s32);
f32 func_ovl0E_15_80046200(f32);
f32 func_ovl0E_15_80046208(f32);
f64 func_ovl0E_15_80046210(void);
s32 func_ovl0E_15_80046218(s32);
void func_ovl0E_15_80046278(void);
void func_ovl0E_15_80046280(void);
void func_ovl0E_15_800462D8(s32);
void func_ovl0E_15_800464A8(s32, f32, f32, f32, s32);
void func_ovl0E_15_800464B0(s32, f32 *, s32);
s32 func_ovl0E_15_800465E0(s32);
void func_ovl0E_15_800465F0(s32);
void func_ovl0E_15_800465F8(void);
void func_ovl0E_15_80046600(s32, f32, f32, f32);
void func_ovl0E_15_80046608(s32, f32 *);
void func_ovl0E_15_80046688(s32, s32, s32, s32, s32);
void func_ovl0E_15_800466A8(s32);
void func_ovl0E_15_80046758(void);
void func_ovl0E_15_80046760(void);

void func_ovl0E_15_80043010(void);
void func_ovl0E_15_80043070(void);
void func_ovl0E_15_800430E4(void);
void func_ovl0E_15_80043180(void);
void func_ovl0E_15_8004321C(void);
void func_ovl0E_15_80043300(void);
void func_ovl0E_15_80043340(void);
void func_ovl0E_15_80043378(void);
void func_ovl0E_15_800433E0(s32);
void func_ovl0E_15_800438DC(UnkStructA *);
void func_ovl0E_15_800439A8(void);
void func_ovl0E_15_800439D0(void);
void func_ovl0E_15_80043A18(f32);
void func_ovl0E_15_80043A60(void);
void func_ovl0E_15_80043B78(void);
void func_ovl0E_15_80043BF0(s32, s32, s32, f32, s32);
void func_ovl0E_15_80043C18(void);
void func_ovl0E_15_80043D4C(void);
void func_ovl0E_15_80043E8C(void);
void func_ovl0E_15_80044048(void);
void func_ovl0E_15_80044290(void);
void func_ovl0E_15_800444C4(void);
void func_ovl0E_15_80044E38(void);
void func_ovl0E_15_80044E90(void);
void func_ovl0E_15_80045024(UnkStructA *);
void func_ovl0E_15_800450BC(s32, UnkStructA *);
void func_ovl0E_15_800450F0(f32, f32, f32);
void func_ovl0E_15_8004514C(void);
void func_ovl0E_15_80045164(void);
static void func_ovl0E_15_80043068(void);
static void func_ovl0E_15_80043178(void);
static void func_ovl0E_15_800439A0(void);
static void func_ovl0E_15_800439C8(void);

/* an angle in degrees moved by d and kept in [0, 360) */
#define ANGLE_ADD(a, d) \
    (a) = ((a) + (d) >= 360.0f) ? (a) + (d) - 360.0f : ((a) + (d) < 0.0f) ? (a) + (d) + 360.0f : (a) + (d)
/* an angle in degrees kept in [0, 360) */
#define ANGLE_WRAP(a) (((a) >= 360.0f) ? (a) - 360.0f : ((a) < 0.0f) ? (a) + 360.0f : (a))

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_15_800439D0() \
    D_ovl0E_15_8004691C = func_ovl0E_15_800456E8(); func_ovl0E_15_800456C8(&D_ovl0E_15_80046910); func_ovl0E_15_800456F0(D_ovl0E_15_8004691C, D_ovl0E_15_80046900)

/* .bss */
u8 D_ovl0E_15_80046900[0x10];
Vec3f D_ovl0E_15_80046910;
s32 D_ovl0E_15_8004691C;
u8 D_ovl0E_15_80046920[0x4]; /* unused (func_ovl0E_15_80045164) */
s32 D_ovl0E_15_80046924;
s32 D_ovl0E_15_80046928;
u8 D_ovl0E_15_8004692C[0x4]; /* unused (func_ovl0E_15_80045164) */
Vec3f D_ovl0E_15_80046930;
UnkStructA *D_ovl0E_15_8004693C; /* unused (func_ovl0E_15_80045164) */
UnkStruct_ovl0E_15_80046940 D_ovl0E_15_80046940;
s32 D_ovl0E_15_80046954;
s32 D_ovl0E_15_80046958;
s32 D_ovl0E_15_8004695C;
s32 D_ovl0E_15_80046960;

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0E_15_800451B4(void) {
}

static void func_ovl0E_15_800451AC(void) {
}

static void func_ovl0E_15_800451A4(void) {
}

static void func_ovl0E_15_8004519C(void) {
}

static void func_ovl0E_15_80045194(void) {
}

static void func_ovl0E_15_8004518C(void) {
}

static void func_ovl0E_15_80045184(void) {
}

static void func_ovl0E_15_8004517C(void) {
}

static void func_ovl0E_15_80045174(void) {
}

static void func_ovl0E_15_8004516C(void) {
}

void func_ovl0E_15_80045164(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl0E_15_80046920[0] = D_ovl0E_15_8004692C[0];
        D_ovl0E_15_8004693C = NULL;
    }
}

void func_ovl0E_15_8004514C(void) {
    D_ovl0E_15_80046924 = -1;
    D_ovl0E_15_80046928 = -1;
}

void func_ovl0E_15_800450F0(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_15_80045D48(D_ovl0E_15_80046930.x, D_ovl0E_15_80046930.y, D_ovl0E_15_80046930.z);
    func_ovl0E_15_80045D68(arg0, arg1, arg2);
    func_ovl0E_15_80046078(180);
}

void func_ovl0E_15_800450BC(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_15_80046600(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_15_80045024(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_15_80045F10(arg0, 0x01000000);
    func_ovl0E_15_800464B0(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_15_800464B0(13, pos, 0);
    func_ovl0E_15_80046608(180, pos);
}

/* a task: one of four objects moved along x for 120 frames (its argument,
 * 0-3, picks where it starts) */
void func_ovl0E_15_80044E90(void) {
    s32 n;
    UnkStructA *obj;
    s32 odd;
    s32 i;

    n = (s32) func_ovl0E_15_80046080();
    obj = func_ovl0E_15_80045F30(0x1C2, 0x01000000, 0xC0, 0);
    func_ovl0E_15_80045F40(obj);
    odd = n & 1;
    if (n < 2) {
        obj->unk40->unk10 = 2300.0f;
    } else {
        obj->unk40->unk10 = 2400.0f;
    }
    if (odd) {
        obj->unk40->unk14 = 1050.0f;
    } else {
        obj->unk40->unk14 = 950.0f;
    }
    obj->unk40->unk18 = 1000.0f;
    if (n < 2) {
        obj->unk68 = 50.0f;
    } else {
        obj->unk68 = 30.0f;
    }
    obj->unk70 = 1.6333334f;
    obj->unk6C = 16.333334f;
    for (i = 0; i < 120; i++) {
        if (odd) {
            obj->unk40->unk10 += 5.0f;
        } else {
            obj->unk40->unk10 -= 5.0f;
        }
        func_ovl0E_15_80045F88(obj);
        func_ovl0E_15_800460A0();
    }
    func_ovl0E_15_80045F20(obj);
    func_ovl0E_15_80046068();
}

void func_ovl0E_15_80044E38(void) {
    if (D_ovl0E_15_80046954 == 0x10) {
        func_ovl0E_15_80046078(0x15E);
        func_ovl0E_15_800465F0(10);
    } else {
        func_ovl0E_15_80046078(45);
        func_ovl0E_15_800465F0(18);
    }
    func_ovl0E_15_80046068();
}

void func_ovl0E_15_80043340(void) {
    func_ovl0E_15_80043300();
    func_ovl0E_15_800455F0(func_ovl0E_15_80045024);
    func_ovl0E_15_80045640(func_ovl0E_15_800438DC);
}

/* a task, started by the handler's case 4 for D_ovl0E_15_80046954 0x10,
 * 0x1A and 0x1B.  The camera deltas are block locals and the random values
 * locals: only so do the stack slots of y, a, z and the spilled random
 * value come out where the original has them. */
void func_ovl0E_15_800444C4(void) {
    UnkStructA *obj0;
    UnkStructA *obj1;
    UnkStructA_40 *snd;
    f32 y;
    s32 i;
    f32 a;
    s32 j;
    f32 z;
    s32 id;
    UnkStructA *obj;
    UnkStructA_40 *p;
    f64 rx;
    f64 ry;
    f64 rz;

    obj0 = func_ovl0E_15_80045748(0);
    obj1 = func_ovl0E_15_80045748(1);
    snd = func_ovl0E_15_80045BE8(0x1C3, 0);
    func_ovl0E_15_800465E0(0x22B);
    func_ovl0E_15_80045E18();
    func_ovl0E_15_80045E30(10.0f, 10.0f, 10.0f);
    func_ovl0E_15_80045E20(-1);
    func_ovl0E_15_80046078(60);
    if (D_ovl0E_15_80046954 != 0x1A && D_ovl0E_15_80046954 != 0x1B) {
        for (i = 0; i < 10; i++) {
            obj0->unk40->unk20 -= 9.0f;
            func_ovl0E_15_800460A0();
        }
        func_ovl0E_15_80046078(20);
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 10; i++) {
                obj0->unk40->unk20 += 18.0f;
                func_ovl0E_15_800460A0();
            }
            func_ovl0E_15_80046078(20);
            for (i = 0; i < 10; i++) {
                obj0->unk40->unk20 -= 18.0f;
                func_ovl0E_15_800460A0();
            }
            func_ovl0E_15_80046078(20);
        }
        for (i = 0; i < 10; i++) {
            obj0->unk40->unk20 += 9.0f;
            func_ovl0E_15_800460A0();
        }
        obj0->unk40->unk20 = 180.0f;
        func_ovl0E_15_80046078(20);
    }
    func_ovl0E_15_80045D50(NULL, &y, NULL);
    func_ovl0E_15_80045D70(NULL, &a, &z);
    {
        f32 dy;
        f32 da;
        f32 dz;

        dy = (1250.0f - y) / 60.0f;
        da = (35.0f - a) / 60.0f;
        dz = (1770.0f - z) / 60.0f;
        for (j = 0; j < 60; j++) {
            func_ovl0E_15_80045D48(32768.0f, y, 32768.0f);
            func_ovl0E_15_80045D68(32768.0f, a, z);
            y += dy;
            a += da;
            z += dz;
            func_ovl0E_15_800460A0();
        }
    }
    func_ovl0E_15_800465E0(0x236);
    for (j = 0; j < 64; j++) {
        func_ovl0E_15_80046218(0x100);
        if (func_ovl0E_15_80046218(0x100) & 1) {
            id = 0xE;
        } else {
            id = 0x16;
        }
        rx = func_ovl0E_15_80046210();
        ry = func_ovl0E_15_80046210();
        rz = func_ovl0E_15_80046210();
        func_ovl0E_15_800464A8(id, rx * 500.0 + 2100.0, ry * 500.0 + 1050.0, rz * 500.0 + 950.0, 0);
        if (j == 54) {
            func_ovl0E_15_800465E0(0x22C);
            func_ovl0E_15_80045BF0(snd);
            for (i = 0; i < 4; i++) {
                func_ovl0E_15_80046058(func_ovl0E_15_80044E90, (void *) i, 0, 0, 0x130);
            }
        }
        func_ovl0E_15_80046078(2);
    }
    func_ovl0E_15_80045E18();
    if (D_ovl0E_15_80046954 == 0x1A || D_ovl0E_15_80046954 == 0x1B) {
        func_ovl0E_15_80045D48(32768.0f, 1180.0f, 32768.0f);
        func_ovl0E_15_80045D68(32768.0f, 30.0f, 340.0f);
    } else {
        func_ovl0E_15_80045D48(32768.0f, 1440.0f, 32768.0f);
        func_ovl0E_15_80045D68(32768.0f, 32768.0f, 340.0f);
    }
    func_ovl0E_15_80046078(60);
    func_ovl0E_15_80045C30(obj1->unk40, 0x20, 0);
    func_ovl0E_15_80045C30(obj1->unk40, -1, 1);
    obj1->unk40->unk48->unk4->unk8 |= 0x20;
    obj1->unk40->unk48->unk4->unk8 &= ~0x40;
    if (D_ovl0E_15_80046954 == 0x1A) {
        while (!(obj1->unk40->unk48->unk4->unk8 & 0x40)) {
            func_ovl0E_15_800460A0();
        }
        func_ovl0E_15_80046078(30);
        func_ovl0E_15_80046758();
        D_ovl0E_15_80046958 = 0;
        func_ovl0E_15_80046068();
    }
    func_ovl0E_15_80046078(90);
    func_ovl0E_15_800460D0(0x70, 0x70);
    func_ovl0E_15_80045C30(obj1->unk40, 0x16, 0);
    func_ovl0E_15_80045C30(obj1->unk40, -1, 1);
    obj1->unk40->unk48->unk4->unk8 |= 0x20;
    obj1->unk40->unk48->unk4->unk8 &= ~0x40;
    func_ovl0E_15_80046078(7);
    obj1->unk68 = 20.0f;
    obj1->unk70 = 1.6333334f;
    for (j = 0; j < 30; j++) {
        if (j == 5) {
            obj1->unk40->unk48->unk4->unk8 |= 0x40;
        }
        obj1->unk40->unk18 += 5.0f;
        func_ovl0E_15_800460A0();
    }
    if (D_ovl0E_15_80046954 == 0x1B) {
        func_ovl0E_15_80045D48(32768.0f, 148.0f, 990.0f);
        func_ovl0E_15_80045D68(32768.0f, 32768.0f, 1140.0f);
        while (obj1->unk68 != 0.0f) {
            func_ovl0E_15_800460A0();
        }
        obj = func_ovl0E_15_80045F30(0x1C2, 0x01000000, 0xC0, 0);
        func_ovl0E_15_80045F40(obj);
        obj->unk40->unk10 = obj1->unk40->unk10;
        obj->unk40->unk14 = 800.0f;
        obj->unk40->unk18 = obj1->unk40->unk18;
        obj->unk70 = 0.8166667f;
        obj->unk6C = 16.333334f;
        while (obj->unk40->unk14 > 310.0f) {
            func_ovl0E_15_80045F88(obj);
            func_ovl0E_15_800460A0();
        }
        p = obj1->unk40;
        func_ovl0E_15_800464A8(0, p->unk10, p->unk14 + 100.0f, p->unk18, 0);
        obj->unk70 = 0.8166667f;
        obj->unk6C = 16.333334f;
        obj->unk68 = 30.0f;
        p = obj1->unk40;
        func_ovl0E_15_800464A8(5, p->unk10, p->unk14 + 80.0f, p->unk18, 0);
        func_ovl0E_15_80045798(1, 8);
        for (j = 0; j < 90; j++) {
            obj->unk40->unk10 += 4.4444447f;
            if (obj->unk40->unk14 < 150.0f) {
                obj->unk6C = 16.333334f;
                obj->unk70 = 0.8166667f;
                obj->unk68 = 30.0f;
            }
            func_ovl0E_15_80045F88(obj);
            func_ovl0E_15_800460A0();
        }
        func_ovl0E_15_80046758();
        D_ovl0E_15_80046958 = 0;
        func_ovl0E_15_80046068();
    }
    func_ovl0E_15_80045DA8(0x10);
    func_ovl0E_15_80045DB0(0xF);
    func_ovl0E_15_800466A8(1);
    while (obj1->unk68 != 0.0f) {
        func_ovl0E_15_800460A0();
    }
    func_ovl0E_15_80046078(60);
    func_ovl0E_15_800460C8(0x70, 0x70, 0);
    func_ovl0E_15_80045778(1);
    func_ovl0E_15_800456F8(0);
    func_ovl0E_15_80045778(0);
    D_ovl0E_15_80046958 = 0;
    func_ovl0E_15_80046068();
}

/* a task: an object at the one it is given, scaled up and turned for 500
 * frames, its unk36 lowered after 300 */
void func_ovl0E_15_80044290(void) {
    s32 pad; /* unused: the original's frame is 8 bytes bigger (one slot, aligned) */
    UnkStructA *src;
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 i;

    src = func_ovl0E_15_80046080();
    obj = func_ovl0E_15_80045F30(0x2D5, 0x01080000, 0x20, 0);
    p = obj->unk40;
    p->unk36 = 0x50;
    p->unk10 = src->unk40->unk10;
    p->unk14 = src->unk40->unk14;
    p->unk18 = src->unk40->unk18;
    for (i = 0; i < 500; i++) {
        if (p->unk28 < 4.0f) {
            p->unk28 += 1.0f;
            p->unk30 += 1.0f;
        }
        if (p->unk2C < 20.0f) {
            p->unk2C += 2.0f;
        }
        ANGLE_ADD(p->unk20, 10.0f);
        if (i > 300) {
            if (p->unk36 != 0.0f) {
                p->unk36 -= 10.0f;
            }
        }
        func_ovl0E_15_800460A0();
    }
    func_ovl0E_15_80045F20(obj);
    func_ovl0E_15_80046068();
}

/* a task: one of four objects sent out from the one it is given, a quarter
 * turn apart */
void func_ovl0E_15_80044048(void) {
    s32 n;
    UnkStructA *src;
    UnkStructA *obj;
    f32 angle;
    f32 dx;
    f32 dz;
    s32 i;

    n = D_ovl0E_15_80046960++;
    src = func_ovl0E_15_80046080();
    obj = func_ovl0E_15_80045F30(-1, 0x01000080, 0x20, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = 0.0f;
    obj->unk40->unk18 = src->unk40->unk18;
    angle = n * 90.0f + 45.0f;
    obj->unk34 = 80.0f;
    dx = func_ovl0E_15_80046200(ANGLE_WRAP(angle)) * 2;
    dz = func_ovl0E_15_80046208(ANGLE_WRAP(angle)) * 2;
    for (i = 0; i < 240; i++) {
        obj->unk40->unk10 += 4.1666665f * dx;
        obj->unk40->unk18 += 4.1666665f * dz;
        func_ovl0E_15_80046018(obj);
        if (!(i & 3)) {
            func_ovl0E_15_800464A8(8, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
        }
        func_ovl0E_15_800460A0();
    }
    func_ovl0E_15_80046078(30);
    func_ovl0E_15_80045F20(obj);
    func_ovl0E_15_80046068();
}

/* a task: an object put at random near the one it is given, for four frames */
void func_ovl0E_15_80043E8C(void) {
    UnkStructA *src;
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 i;

    src = func_ovl0E_15_80046080();
    obj = func_ovl0E_15_80045F30(0x1CF, 0x01000000, 0x20, 0);
    p = obj->unk40;
    func_ovl0E_15_80045C10(p, 2);
    p->unk10 = src->unk40->unk10;
    p->unk14 = src->unk40->unk14;
    p->unk18 = src->unk40->unk18;
    p->unk28 = 0.5f;
    p->unk2C = 0.5f;
    p->unk30 = 0.5f;
    p->unk10 += func_ovl0E_15_80046210() * 200.0 - 100.0;
    p->unk14 += func_ovl0E_15_80046210() * 200.0 - 100.0 + 150.0;
    p->unk18 += func_ovl0E_15_80046210() * 200.0 - 100.0;
    for (i = 0; i < 4; i++) {
        func_ovl0E_15_80045C18(p, 0x1D0, 0, i * 2);
        func_ovl0E_15_80045C18(p, 0x1D0, 1, i * 2 + 1);
        func_ovl0E_15_800460A0();
    }
    func_ovl0E_15_80045F20(obj);
    func_ovl0E_15_80046068();
}

/* a task: an object under the one it is given, scaled up while its unk36
 * falls to 0 */
void func_ovl0E_15_80043D4C(void) {
    UnkStructA *src;
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 i;

    src = func_ovl0E_15_80046080();
    obj = func_ovl0E_15_80045F30(0x1CD, 0x01080000, 0x20, 0);
    p = obj->unk40;
    p->unk36 = 0x80;
    p->unk10 = src->unk40->unk10;
    p->unk14 = 2.0f;
    p->unk18 = src->unk40->unk18;
    for (i = 0; i < 60; i++) {
        p->unk28 += 0.16666667f;
        p->unk30 += 0.16666667f;
        p->unk36 -= 2.05f;
        if (p->unk36 < 0) {
            p->unk36 = 0;
            break;
        }
        func_ovl0E_15_800460A0();
    }
    func_ovl0E_15_80045F20(obj);
    func_ovl0E_15_80046068();
}

/* a task: an object at the one it is given, scaled up for 300 frames while
 * its unk36 falls.  The two stores on one line: only so does unk36's go
 * after unk18's load. */
void func_ovl0E_15_80043C18(void) {
    UnkStructA *src;
    UnkStructA *obj;
    UnkStructA_40 *p;
    s32 i;

    src = func_ovl0E_15_80046080();
    obj = func_ovl0E_15_80045F30(0x2D4, 0x01080000, 0x20, 0);
    p = obj->unk40;
    p->unk10 = src->unk40->unk10;
    p->unk14 = src->unk40->unk14;
    p->unk18 = src->unk40->unk18; p->unk36 = 200;
    for (i = 0; i < 300; i++) {
        p->unk28 += 0.06666667f;
        p->unk2C += 0.06666667f;
        p->unk30 += 0.06666667f;
        p->unk36 -= 0.65f;
        func_ovl0E_15_800460A0();
    }
    func_ovl0E_15_80045F20(obj);
    func_ovl0E_15_80046068();
}

void func_ovl0E_15_80043BF0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_15_80046940.unk0 = arg0;
    D_ovl0E_15_80046940.unk4 = arg1;
    D_ovl0E_15_80046940.unk8 = arg2;
    D_ovl0E_15_80046940.unkC = arg3;
    D_ovl0E_15_80046940.unk10 = arg4;
}

void func_ovl0E_15_80043B78(void) {
    UNK_MACRO_ovl0E_15_800439D0();
    func_ovl0E_15_80045708(D_ovl0E_15_80046940.unk4, 3, 4.0f, D_ovl0E_15_80046940.unk10, 0, 1, 1);
}

void func_ovl0E_15_80043A60(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_15_80045718();
    switch (D_ovl0E_15_80046940.unk8) {
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
        func_ovl0E_15_80045D68(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_15_80046940.unkC;
        func_ovl0E_15_80045D70(&sp1C, NULL, NULL);
        func_ovl0E_15_80045D68(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_15_80045700(D_ovl0E_15_80046940.unk4);
}

void func_ovl0E_15_80043A18(f32 arg0) {
    f32 sp1C;

    func_ovl0E_15_80045D70(&sp1C, NULL, NULL);
    func_ovl0E_15_80045D68(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_15_800439D0(void) {
    func_ovl0E_15_800439C8();
    UNK_MACRO_ovl0E_15_800439D0();
}

static void func_ovl0E_15_800439C8(void) {
}

void func_ovl0E_15_800439A8(void) {
    func_ovl0E_15_800439A0();
    func_ovl0E_15_80045750(1);
}

static void func_ovl0E_15_800439A0(void) {
}

void func_ovl0E_15_800438DC(UnkStructA *arg0) {
    func_ovl0E_15_80045F10(arg0, 0x04000000);
    func_ovl0E_15_80046078(10);
    func_ovl0E_15_80045590(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_15_800465E0(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_15_80046078(60);
}

void func_ovl0E_15_80043378(void) {
    func_ovl0E_15_80043340();
    func_ovl0E_15_80045508(0x1AA);
    func_ovl0E_15_80045520(0x1AB);
    func_ovl0E_15_800456B8();
    D_ovl0E_15_80046958 = 1;
    D_ovl0E_15_8004695C = 0;
    func_ovl0E_15_80046278();
}

void func_ovl0E_15_80043300(void) {
    func_ovl0E_15_800462D8(0x400);
    func_ovl0E_15_800462D8(0x401);
    func_ovl0E_15_800462D8(0x402);
    func_ovl0E_15_800462D8(0x403);
    func_ovl0E_15_800462D8(0x404);
}

void func_ovl0E_15_8004321C(void) {
    func_ovl0E_15_800456C0(0x17, 0, 0xF);
    func_ovl0E_15_80045700(0);
    func_ovl0E_15_80046688(1, 2, 0x17, 2, 8);
    func_ovl0E_15_800466A8(0);
    func_ovl0E_15_80045778(1);
    func_ovl0E_15_800456F8(1);
    func_ovl0E_15_80045778(0);
    func_ovl0E_15_80045748(0)->unk40->unk10 += 50.0f;
    func_ovl0E_15_80045748(1)->unk40->unk10 += 50.0f;
    func_ovl0E_15_80045718();
    func_ovl0E_15_80045DB0(0x1F);
    func_ovl0E_15_80045D68(0.0f, 45.0f, 32768.0f);
    func_ovl0E_15_80045690(0x56, 0x11);
    func_ovl0E_15_800456F8(1);
}

void func_ovl0E_15_80043180(void) {
    func_ovl0E_15_80043178();
    func_ovl0E_15_80046688(1, 2, 0x17, 0, 0xA);
    func_ovl0E_15_800456C0(0x17, 0, 0xF);
    func_ovl0E_15_80045700(0);
    func_ovl0E_15_80045748(0)->unk40->unk10 += 50.0f;
    func_ovl0E_15_80045748(1)->unk40->unk10 += 50.0f;
    func_ovl0E_15_80045718();
    func_ovl0E_15_80045DB0(0xF);
}

static void func_ovl0E_15_80043178(void) {
}

void func_ovl0E_15_800430E4(void) {
    if (D_ovl0E_15_80046954 != 0x1A && D_ovl0E_15_80046954 != 0x1B) {
        func_ovl0E_15_80046058(func_ovl0E_15_80044E38, NULL, 0, 0, 0x130);
    }
    if (D_ovl0E_15_80046954 == 0x10 || D_ovl0E_15_80046954 == 0x1A || D_ovl0E_15_80046954 == 0x1B) {
        func_ovl0E_15_80046058(func_ovl0E_15_800444C4, NULL, 0, 0, 0x130);
    }
}

/* inlined into func_ovl0E_15_80043070, its stub just before it */
static void func_ovl0E_15_80043068(void) {
    while (D_ovl0E_15_80046958 != 0) {
        func_ovl0E_15_800460A0();
    }
}

void func_ovl0E_15_80043070(void) {
    if (D_ovl0E_15_80046954 == 0x10 || D_ovl0E_15_80046954 == 0x1A || D_ovl0E_15_80046954 == 0x1B) {
        func_ovl0E_15_80043068();
        func_ovl0E_15_800456F8(0);
    }
    /* empty: without it the function is small enough to be inlined into
     * the handler (ovl_12_06's 800430D0 keeps the same test) */
    if (D_ovl0E_15_80046954 == 2) {
    }
}

void func_ovl0E_15_80043010(void) {
    if (D_ovl0E_15_80046954 == 0x1A || D_ovl0E_15_80046954 == 0x1B) {
        func_ovl0E_15_80046760();
    }
    if (D_ovl0E_15_8004695C == 0) {
        func_ovl0E_15_80046280();
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_15_800433E0(s32 arg0) {
    UnkStructA *obj0;
    UnkStructA *obj1;
    s32 i;
    s32 id;

    switch (arg0) {
        case 2:
            D_ovl0E_15_80046954 = func_ovl0E_15_80045608();
            func_ovl0E_15_80043378();
            break;
        case 16:
        case 26:
        case 27:
            func_ovl0E_15_8004321C();
            break;
        case 17:
            func_ovl0E_15_80043180();
            break;
        case 4:
            func_ovl0E_15_800430E4();
            break;
        case 5:
            func_ovl0E_15_80043070();
            break;
        case 11:
            if (func_ovl0E_15_800456A0(1) == 3) {
                break;
            }
            obj0 = func_ovl0E_15_80045748(0);
            obj1 = func_ovl0E_15_80045748(1);
            func_ovl0E_15_800456F8(0);
            func_ovl0E_15_80045D48(2350.0f, 52.0f, 1668.0f);
            func_ovl0E_15_80045D68(0.0f, 45.0f, 2157.0f);
            func_ovl0E_15_80046078(30);
            func_ovl0E_15_800465E0(0x22E);
            obj1->unk40->unkC |= 0x4000;
            func_ovl0E_15_80045C30(obj1->unk40, 7, 0);
            func_ovl0E_15_80045C30(obj1->unk40, -1, 1);
            obj1->unk40->unk48->unk4->unk8 |= 0x20;
            obj1->unk40->unk48->unk4->unk8 &= ~0x40;
            func_ovl0E_15_80046078(30);
            func_ovl0E_15_80046058(func_ovl0E_15_80044290, obj1, 0, 0, 0x130);
            func_ovl0E_15_80046078(30);
            func_ovl0E_15_80046078(60);
            D_ovl0E_15_80046960 = 0;
            for (i = 0; i < 4; i++) {
                func_ovl0E_15_80046058(func_ovl0E_15_80044048, obj1, 0, 0, 0x130);
            }
            func_ovl0E_15_800456A8(50);
            func_ovl0E_15_800465F8();
            for (i = 0; i < 32; i++) {
                func_ovl0E_15_80046218(0x100);
                func_ovl0E_15_80046058(func_ovl0E_15_80043E8C, obj1, 0, 0, 0x130);
                if (func_ovl0E_15_80046218(0x100) & 1) {
                    id = 0xC;
                } else {
                    id = 0x18;
                }
                func_ovl0E_15_800464A8(id, func_ovl0E_15_80046210() * 160.0 + (obj1->unk40->unk10 - 80.0f),
                                       func_ovl0E_15_80046210() * 50.0 + obj1->unk40->unk14 + 50.0,
                                       func_ovl0E_15_80046210() * 160.0 + (obj1->unk40->unk18 - 80.0f), 0);
                func_ovl0E_15_80046078(4);
            }
            func_ovl0E_15_800465E0(0x230);
            func_ovl0E_15_800465E0(0x1B8);
            func_ovl0E_15_80046058(func_ovl0E_15_80043D4C, obj1, 0, 0, 0x130);
            func_ovl0E_15_80046058(func_ovl0E_15_80043C18, obj1, 0, 0, 0x130);
            for (i = 0; i < 40; i++) {
                obj1->unk40->unk14 += 25.0f;
                func_ovl0E_15_800460A0();
            }
            func_ovl0E_15_80045F10(obj1, 0x01000000);
            func_ovl0E_15_80046078(60);
            obj0 = func_ovl0E_15_80045748(0);
            func_ovl0E_15_80045D48(obj0->unk40->unk10, 50.0f, obj0->unk40->unk18);
            func_ovl0E_15_80045D68(obj0->unk40->unk20, 20.0f, 800.0f);
            func_ovl0E_15_800456F8(0);
            func_ovl0E_15_800456A8(32);
            func_ovl0E_15_80046280();
            D_ovl0E_15_8004695C = 1;
            break;
        case 1:
            func_ovl0E_15_80043010();
            break;
    }
}
