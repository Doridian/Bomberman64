/*
 * NON_MATCHING: ovl_0F_07's game object, complete: every function and its data
 * (.data and .rodata as the original, .bss 0x60).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 163, eu 163, jp 163
 *
 * What still differs in us (words):
 * - func_ovl0F_07_800433A4 (2): case 2's D_E30[2] stores: the original
 *   has `lui at,0x4516; lw t6,8(v1); mtc1`, ours `lw t6,8(v1); lui at`.
 * - func_ovl0F_07_80043A58 (64): `if ((s32)vel[0] != (s32)dx)` gives
 *   `beq dx,vel`, the original `beq vel,dx` (z too); at the end the
 *   original keeps 500.0f in $f0 and the vel[0] preload in $f6 (ours
 *   $f12/$f0), and has a nop after the hit path's mul.s. One word short.
 * - func_ovl0F_07_80044208 (97): the original has `move s1,v0` before
 *   `mtc1 zero,$f12; jal 800452F8; nop`; ours moves it into the delay
 *   slot. One word short, so the rest is shifted.
 */
#include "common.h"

/*
 * ovl_0F_07's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

/* a model the stage places: seven in D_ovl0F_07_80045B88, two in
 * D_ovl0F_07_80045CBC */
typedef struct {
    /* 0x00 */ UnkStructA **unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
} UnkStruct_ovl0F_07_80045B88; /* s(s32)dze 0x2C */

/* seven arguments of func_ovl0F_07_80044A18 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0F_07_80045D90; /* s(s32)dze 0x1C */

/* the task func_ovl0F_07_80044208 runs as: its argument at 0x2C */
typedef struct {
    /* 0x00 */ u8 unk0[0x2C];
    /* 0x2C */ UnkStructA **unk2C;
} UnkStruct_ovl0F_07_80045390;

void func_ovl0F_07_80044818(s32);
void func_ovl0F_07_80044830(s32);
void func_ovl0F_07_80044858(s32, s32, s32, s32, s32, s32);
void func_ovl0F_07_80044878(f32, f32, f32, f32 *, s32);
void func_ovl0F_07_800448F8(void (*)(UnkStructA *), s32);
void func_ovl0F_07_80044900(void (*)(UnkStructA *));
void func_ovl0F_07_80044910(s32, s32, s32);
s32 func_ovl0F_07_80044918(void);
void func_ovl0F_07_80044938(void);
s32 *func_ovl0F_07_80044968(void);
void func_ovl0F_07_80044990(s32);
void func_ovl0F_07_800449C8(void);
void func_ovl0F_07_800449D0(s32, s32, s32);
void func_ovl0F_07_800449D8(void *);
s32 func_ovl0F_07_800449E0(s32, s32, s32, s32);
s32 func_ovl0F_07_800449F8(void);
void func_ovl0F_07_80044A00(s32, void *);
void func_ovl0F_07_80044A10(s32);
void func_ovl0F_07_80044A18(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0F_07_80044A28(void);
void func_ovl0F_07_80044A30(s32);
UnkStructA *func_ovl0F_07_80044A58(s32);
void func_ovl0F_07_80044A60(s32);
UnkStructA *func_ovl0F_07_80044A98(s32);
void func_ovl0F_07_80044F10(UnkStructA_40 *, s32);
void func_ovl0F_07_80045058(f32, f32, f32);
void func_ovl0F_07_80045078(f32, f32, f32);
void func_ovl0F_07_80045080(f32 *, f32 *, f32 *);
void func_ovl0F_07_800450C0(s32);
void func_ovl0F_07_800450E0(f32);
void func_ovl0F_07_800450E8(f32);
void func_ovl0F_07_80045100(f32);
s32 func_ovl0F_07_800451C8(UnkStructA *, s32);
void func_ovl0F_07_80045218(UnkStructA *, s32);
void func_ovl0F_07_80045220(UnkStructA *, s32);
s32 func_ovl0F_07_80045230(UnkStructA *);
UnkStructA *func_ovl0F_07_80045288(s32, s32);
void func_ovl0F_07_80045298(UnkStructA *);
void func_ovl0F_07_800452F8(f32);
void func_ovl0F_07_80045300(s32);
s32 func_ovl0F_07_80045338(UnkStructA *, s32, UnkStructA *);
void func_ovl0F_07_80045368(void (*)(void), void *, s32, s32, s32);
void func_ovl0F_07_80045378(void);
void func_ovl0F_07_80045388(s32);
UnkStruct_ovl0F_07_80045390 *func_ovl0F_07_80045390(void);
void func_ovl0F_07_800453B0(void);
UnkStructC *func_ovl0F_07_800453F0(s32);
void func_ovl0F_07_80045400(UnkStructC *, s32);
s32 func_ovl0F_07_800455F0(s32);
s32 *func_ovl0F_07_80045600(s32);
void func_ovl0F_07_800456D0(u32 (*)[3]);
void func_ovl0F_07_800457B8(s32, f32, f32, f32, s32);
s32 func_ovl0F_07_800457C0(s32, f32 *, s32);
void func_ovl0F_07_800457C8(s32);
void func_ovl0F_07_80045878(s32, s32, s32);
void func_ovl0F_07_800458F0(s32);
void func_ovl0F_07_80045910(s32, f32, f32, f32);

void func_ovl0F_07_80043010(void);
void func_ovl0F_07_800430AC(f32);
void func_ovl0F_07_800433A4(s32);
void func_ovl0F_07_80043A58(UnkStructA *);
void func_ovl0F_07_800440D8(UnkStructA *);
void func_ovl0F_07_80044208(void);
void func_ovl0F_07_800443B8(s32, UnkStructA *);
void func_ovl0F_07_800443EC(f32, f32, f32);
void func_ovl0F_07_80044448(void);
void func_ovl0F_07_80044460(void);

static void func_ovl0F_07_80043040(s32 *);
static void func_ovl0F_07_800430F4(UnkStruct_ovl0F_07_80045B88 *);
static void func_ovl0F_07_80043178(UnkStruct_ovl0F_07_80045B88 *, s32);
static void func_ovl0F_07_80043228(UnkStruct_ovl0F_07_80045B88 *, s32);
static void func_ovl0F_07_80043310(s32);
static void func_ovl0F_07_800439A8(f32);
static s32 func_ovl0F_07_800439A0(UnkStructA *);
static void func_ovl0F_07_80043998(s32 *, f32, f32);
static void func_ovl0F_07_800441F8(UnkStruct_ovl0F_07_80045390 *, UnkStructA *);
static void func_ovl0F_07_80044200(void);

/* .bss */
UnkStructA *D_ovl0F_07_80045E30[8];
u8 D_ovl0F_07_80045E50[0x10];
Vec3f D_ovl0F_07_80045E60;
s32 D_ovl0F_07_80045E6C;
u8 D_ovl0F_07_80045E70[0x4];
s32 D_ovl0F_07_80045E74;
s32 D_ovl0F_07_80045E78;
u8 D_ovl0F_07_80045E7C[0x4];
Vec3f D_ovl0F_07_80045E80;
UnkStructC *D_ovl0F_07_80045E8C;

/* .data */
f32 D_ovl0F_07_80045B10 = 0.01f;
f32 D_ovl0F_07_80045B14 = 0.1f;
s32 D_ovl0F_07_80045B18 = 0;
s32 D_ovl0F_07_80045B1C = 0;
UnkStructA *D_ovl0F_07_80045B20 = NULL;
s32 D_ovl0F_07_80045B24 = 0;
s32 D_ovl0F_07_80045B28 = -1;
u8 D_ovl0F_07_80045B2C[4] = { 0 };
extern UnkStruct_ovl0F_07_80045B88 D_ovl0F_07_80045B88[7];
extern UnkStruct_ovl0F_07_80045D90 D_ovl0F_07_80045D90;

/* the PACK of the two speeds into unk64 */
#define PACK_ovl0F_07(a, b) (((s32)((a) * 500.0f) << 16) | ((s32)((b) * 500.0f) & 0xFFFF))

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0F_07_80043948() \
    D_ovl0F_07_80045E6C = func_ovl0F_07_800449F8(); func_ovl0F_07_800449D8(&D_ovl0F_07_80045E60); func_ovl0F_07_80044A00(D_ovl0F_07_80045E6C, D_ovl0F_07_80045E50)

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0F_07_800444C0(void) {
    D_ovl0F_07_80045E70[0] = D_ovl0F_07_80045E7C[0];
}

static void func_ovl0F_07_800444B8(void) {
    func_ovl0F_07_800430F4(D_ovl0F_07_80045B88);
    func_ovl0F_07_80043228(D_ovl0F_07_80045B88, 0);
}

static void func_ovl0F_07_800444B0(void) {
}

static void func_ovl0F_07_800444A8(void) {
}

static void func_ovl0F_07_800444A0(void) {
}

static void func_ovl0F_07_80044498(void) {
}

static void func_ovl0F_07_80044490(void) {
}

static void func_ovl0F_07_80044488(void) {
}

static void func_ovl0F_07_80044480(void) {
}

static void func_ovl0F_07_80044478(void) {
}

static void func_ovl0F_07_80044470(void) {
}

static void func_ovl0F_07_80044468(void) {
}

void func_ovl0F_07_80044460(void) {
}

void func_ovl0F_07_80044448(void) {
    D_ovl0F_07_80045E74 = -1;
    D_ovl0F_07_80045E78 = -1;
}

void func_ovl0F_07_800443EC(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_07_80045058(D_ovl0F_07_80045E80.x, D_ovl0F_07_80045E80.y, D_ovl0F_07_80045E80.z);
    func_ovl0F_07_80045078(arg0, arg1, arg2);
    func_ovl0F_07_80045388(180);
}

void func_ovl0F_07_800443B8(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0F_07_80045910(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0F_07_80044208(void) {
    UnkStruct_ovl0F_07_80045390 *task;
    UnkStructA *obj;

    task = func_ovl0F_07_80045390();
    obj = func_ovl0F_07_80044A58(func_ovl0F_07_800449F8());
    func_ovl0F_07_80044200();
    func_ovl0F_07_800441F8(task, obj);
    func_ovl0F_07_80045378();
}

static void func_ovl0F_07_800441F8(UnkStruct_ovl0F_07_80045390 *task, UnkStructA *obj) {
    static s32 D_ovl0F_07_80045B30 = 0;

    while (D_ovl0F_07_80045B30 < 400) {
        (*task->unk2C)->unk40->unk14 += 3.75f;
        (*task->unk2C)->unk40->unk18 -= 3.75f;
        obj->unk40->unk14 += 3.75f;
        D_ovl0F_07_80045B30++;
        func_ovl0F_07_800453B0();
    }
}

static void func_ovl0F_07_80044200(void) {
    func_ovl0F_07_800452F8(0.0f);
    func_ovl0F_07_80045300(0x7F);
    if (D_ovl0F_07_80045B28 != -1) {
        func_ovl0F_07_800457C8(D_ovl0F_07_80045B28);
    }
    func_ovl0F_07_80045388(250);
    func_ovl0F_07_80044A30(1);
    func_ovl0F_07_80044A60(1);
    func_ovl0F_07_800450E0(30.0f);
    func_ovl0F_07_800450E8(1.0f);
    func_ovl0F_07_80045100(10.0f);
    func_ovl0F_07_80044A18(D_ovl0F_07_80045D90.unk0, D_ovl0F_07_80045D90.unk4, D_ovl0F_07_80045D90.unk8,
                           D_ovl0F_07_80045D90.unkC, D_ovl0F_07_80045D90.unk10, D_ovl0F_07_80045D90.unk14,
                           D_ovl0F_07_80045D90.unk18);
    func_ovl0F_07_800458F0(0x8E);
}

/* .data after func_ovl0F_07_800441F8's static */
/* passed to func_ovl0F_07_800456D0: three 12-byte records */
u32 D_ovl0F_07_80045B34[][3] = {
    { 0x25D0001, 0xE, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
/* four 12-byte records, each passed to func_ovl0F_07_80045878 */
u32 D_ovl0F_07_80045B58[][3] = {
    { 0, 0x14, 0xF2 },
    { 1, 0x16, 0xF4 },
    { 2, 0x12, 0xF0 },
    { 3, 0x15, 0xF3 },
};
UnkStruct_ovl0F_07_80045B88 D_ovl0F_07_80045B88[7] = {
    { &D_ovl0F_07_80045E30[0], 0x22B, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_07_80045E30[1], 0x261, 0, 21.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_07_80045E30[2], 0x268, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_07_80045E30[3], 0x22F, 0, 58.0f, 0.0f, -33.0f, 0.0f, -90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_07_80045E30[4], 0x232, 0, -12.0f, 0.0f, 14.0f, 0.0f, 90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_07_80045E30[5], 0x22C, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_07_80045E30[6], 0x231, 0, -12.0f, 0.0f, 14.0f, 0.0f, 90.0f, 0.0f, 0, 0 },
};
UnkStruct_ovl0F_07_80045B88 D_ovl0F_07_80045CBC[2] = {
    { &D_ovl0F_07_80045E30[7], 0x262, 0, 22.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0, 0x405 },
    { &D_ovl0F_07_80045E30[7], 0x262, 0, 22.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};
/* func_ovl0F_07_80043040's: four arguments to test, three to pass on */
s32 D_ovl0F_07_80045D14[7] = { 0x28, 9, 0x28, 9, 0x5F, 0x11, 0 };
s32 D_ovl0F_07_80045D30[7] = { 6, 9, 6, 9, 0x60, 0x11, 0 };
UnkStruct_ovl0F_07_80045D90 D_ovl0F_07_80045D4C[2] = {
    { 0x80, 3, 8.5f, 2, 0, 1, 1 },
    { 0x80, 3, 8.5f, 2, 0, 1, 1 },
};
u8 D_ovl0F_07_80045D84[0xC] = { 0 };
UnkStruct_ovl0F_07_80045D90 D_ovl0F_07_80045D90 = { 0, 3, 3.75f, 15, 0, 0, 0 };
f32 D_ovl0F_07_80045DAC = 0.6f;

void func_ovl0F_07_800440D8(UnkStructA *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl0F_07_800450C0(0x10);
    }
    dx = arg0->unk40->unk28 / 30.0f;
    dy = arg0->unk40->unk2C / 30.0f;
    dz = arg0->unk40->unk30 / 30.0f;
    func_ovl0F_07_80045220(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        arg0->unk40->unk28 -= dx;
        arg0->unk40->unk2C -= dy;
        arg0->unk40->unk30 -= dz;
        func_ovl0F_07_80045298(arg0);
        func_ovl0F_07_800453B0();
    }
    func_ovl0F_07_80045220(arg0, 0x01000000);
}

static void func_ovl0F_07_80043A50(s16 x, s16 z, f32 *vel) {
    vel[0] = x * 0.002f;
    vel[2] = z * 0.002f;
}

void func_ovl0F_07_80043A58(UnkStructA *arg0) {
    f32 vel[3];
    f32 dx;
    f32 dz;
    f32 pos[3];
    UnkStructA_40 *p;

    dx = arg0->unk40->unk10 - arg0->unk58;
    dz = arg0->unk40->unk18 - arg0->unk60;
    if (arg0->unk8 & 1) {
        D_ovl0F_07_80045B1C = 1;
        D_ovl0F_07_80045B20 = arg0;
    } else {
        D_ovl0F_07_80045B1C = 0;
        D_ovl0F_07_80045B20 = NULL;
    }
    if (arg0->unk68 != 0.0f || arg0->unk6C != 0.0f) {
        arg0->unk64 = 0;
        D_ovl0F_07_80045B18 = 0;
        return;
    }
    p = arg0->unk40;
    pos[0] = p->unk10;
    pos[1] = p->unk14;
    pos[2] = p->unk18;
    func_ovl0F_07_80043A50(arg0->unk64 >> 16, arg0->unk64 & 0xFFFF, vel);
    if ((s32)vel[0] != (s32)dx) {
        arg0->unk40->unk10 = arg0->unk58;
        if ((s32)dx < (s32)vel[0]) {
            vel[0] -= (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl0F_07_80045B14 : D_ovl0F_07_80045B10);
            if (vel[0] < dx) {
                vel[0] = dx;
            }
            func_ovl0F_07_800439A8(dx);
        } else if ((s32)vel[0] < (s32)dx) {
            vel[0] += (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl0F_07_80045B14 : D_ovl0F_07_80045B10);
            if (dx < vel[0]) {
                vel[0] = dx;
            }
            func_ovl0F_07_800439A8(dx);
        }
        arg0->unk40->unk10 += vel[0];
    }
    if ((s32)vel[2] != (s32)dz) {
        arg0->unk40->unk18 = arg0->unk60;
        if ((s32)dz < (s32)vel[2]) {
            vel[2] -= (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl0F_07_80045B14 : D_ovl0F_07_80045B10);
            if (vel[2] < dz) {
                vel[2] = dz;
            }
            func_ovl0F_07_800439A8(dz);
        } else if ((s32)vel[2] < (s32)dz) {
            vel[2] += (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl0F_07_80045B14 : D_ovl0F_07_80045B10);
            if (dz < vel[2]) {
                vel[2] = dz;
            }
            func_ovl0F_07_800439A8(dz);
        }
        arg0->unk40->unk18 += vel[2];
    }
    if (func_ovl0F_07_800439A0(arg0)) {
        func_ovl0F_07_80043998(&arg0->unk64, 0.0f, 0.0f);
        arg0->unk40->unk10 = pos[0];
        arg0->unk40->unk14 = pos[1];
        arg0->unk40->unk18 = pos[2];
    } else {
        func_ovl0F_07_80043998(&arg0->unk64, vel[0], vel[2]);
    }
}

static void func_ovl0F_07_800439A8(f32 arg0) {
    if (D_ovl0F_07_80045B1C != 0) {
        if (D_ovl0F_07_80045B18 == 0) {
            if (arg0 == 0.0f) {
                func_ovl0F_07_800458F0(0x32);
            } else {
                func_ovl0F_07_800458F0(0x27);
            }
            D_ovl0F_07_80045B18 = 20;
            func_ovl0F_07_800457B8(0x19, D_ovl0F_07_80045B20->unk40->unk10, D_ovl0F_07_80045B20->unk40->unk14,
                                   D_ovl0F_07_80045B20->unk40->unk18, 0);
        } else {
            D_ovl0F_07_80045B18--;
        }
    }
}


static s32 func_ovl0F_07_800439A0(UnkStructA *arg0) {
    s32 hit;
    s32 saved;
    UnkStructA *other;
    s32 id;

    hit = 0;
    other = NULL;
    saved = arg0->unkC;
    arg0->unkC = 0;
    if (arg0->unk8 & 1) {
        other = func_ovl0F_07_80044A98(func_ovl0F_07_800449F8());
    } else if (arg0->unk8 & 2) {
        id = func_ovl0F_07_800449F8();
        if (func_ovl0F_07_80044A98(id) == arg0) {
            other = func_ovl0F_07_80044A58(id);
        } else {
            other = NULL;
        }
    }
    if (other != NULL) {
        if (func_ovl0F_07_80045338(arg0, 0x10, other) != 0) {
            hit = 1;
        }
    } else if (func_ovl0F_07_800451C8(arg0, 0x10) != 0) {
        hit = 1;
    }
    arg0->unkC = saved;
    return hit;
}

static void func_ovl0F_07_80043998(s32 *dst, f32 x, f32 z) {
    *dst = ((s16)(x * 500.0f) << 16) | ((s16)(z * 500.0f) & 0xFFFF);
}

void func_ovl0F_07_800430AC(f32 arg0) {
    f32 sp1C;

    func_ovl0F_07_80045080(&sp1C, NULL, NULL);
    func_ovl0F_07_80045078(sp1C + arg0, 32768.0f, 32768.0f);
}

static void func_ovl0F_07_8004339C(void) {
    s32 count;
    u32 (*p)[3];
    s32 i;

    func_ovl0F_07_800456D0(D_ovl0F_07_80045B34);
    p = D_ovl0F_07_80045B58;
    count = 4;
    for (i = 0; i < count; i++) {
        func_ovl0F_07_80045878((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}

static void func_ovl0F_07_80043394(void) {
    func_ovl0F_07_80044818(0x22A);
    func_ovl0F_07_80044830(0x23D);
    func_ovl0F_07_800449C8();
}

static void func_ovl0F_07_8004338C(void) {
    s32 pad[2];

    func_ovl0F_07_80044F10(D_ovl0F_07_80045E30[0]->unk40, 0x61);
    func_ovl0F_07_80044F10(D_ovl0F_07_80045E30[3]->unk40, 0x61);
    func_ovl0F_07_80044F10(D_ovl0F_07_80045E30[4]->unk40, 0x61);
}

static void func_ovl0F_07_80043020(s32 count, UnkStruct_ovl0F_07_80045B88 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_07_80045230(*p->unk0);
        p++;
    }
}

static void func_ovl0F_07_80043018(void) {
    D_ovl0F_07_80045E6C = func_ovl0F_07_800449F8();
    func_ovl0F_07_800449D8(&D_ovl0F_07_80045E60);
    func_ovl0F_07_80044A00(D_ovl0F_07_80045E6C, D_ovl0F_07_80045E50);
}

static void func_ovl0F_07_8004309C(f32 arg0, f32 arg1) {
    D_ovl0F_07_80045B10 = arg0;
    D_ovl0F_07_80045B14 = arg1;
    D_ovl0F_07_80045B18 = 0;
}

static void func_ovl0F_07_800430A4(void) {
    if (func_ovl0F_07_80044968()[4] == 0) {
        func_ovl0F_07_8004309C(0.3f, 0.5f);
    } else {
        func_ovl0F_07_8004309C(0.12f, 0.15f);
    }
}

static void func_ovl0F_07_80043094(void) {
    s32 pad2[2];

    switch (func_ovl0F_07_80044918()) {
        case 0x12:
            func_ovl0F_07_80044A18(D_ovl0F_07_80045D4C[0].unk0, D_ovl0F_07_80045D4C[0].unk4,
                                   D_ovl0F_07_80045D4C[0].unk8, D_ovl0F_07_80045D4C[0].unkC,
                                   D_ovl0F_07_80045D4C[0].unk10, D_ovl0F_07_80045D4C[0].unk14,
                                   D_ovl0F_07_80045D4C[0].unk18);
            break;
        case 0x13:
            func_ovl0F_07_80044A18(D_ovl0F_07_80045D4C[1].unk0, D_ovl0F_07_80045D4C[1].unk4,
                                   D_ovl0F_07_80045D4C[1].unk8, D_ovl0F_07_80045D4C[1].unkC,
                                   D_ovl0F_07_80045D4C[1].unk10, D_ovl0F_07_80045D4C[1].unk14,
                                   D_ovl0F_07_80045D4C[1].unk18);
            break;
    }
}

static void func_ovl0F_07_8004308C(void) {
    func_ovl0F_07_80045078(32768.0f, -45.0f, 32768.0f);
}

static void func_ovl0F_07_80043030(s32 *p) {
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

static void func_ovl0F_07_80043038(void) {
    if (func_ovl0F_07_800455F0(0x405) != 0 && func_ovl0F_07_800449E0(0x16, 3, 0x16, 3) != 0) {
        func_ovl0F_07_80044A30(1);
        func_ovl0F_07_80044990(0);
        func_ovl0F_07_80045368(func_ovl0F_07_80044208, D_ovl0F_07_80045CBC, 0, 0, 0x130);
        func_ovl0F_07_80043030(func_ovl0F_07_80045600(0x23));
        func_ovl0F_07_80044938();
    }
}

static void func_ovl0F_07_80043028(void) {
    func_ovl0F_07_80044A58(func_ovl0F_07_800449F8())->unk64 = 0;
    D_ovl0F_07_80045B18 = 0;
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_07_800433A4(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0F_07_8004339C();
            func_ovl0F_07_80043394();
            func_ovl0F_07_80043178(D_ovl0F_07_80045B88, 7);
            func_ovl0F_07_8004338C();
            if (func_ovl0F_07_800455F0(0x405) == 0) {
                func_ovl0F_07_80043310(0x279);
            } else {
                func_ovl0F_07_80043310(0x27A);
            }
            D_ovl0F_07_80045E30[2]->unk40->unk10 = 2400.0f;
            D_ovl0F_07_80045E30[2]->unk40->unk14 = 2600.0f;
            D_ovl0F_07_80045E30[2]->unk40->unk18 = -2000.0f;
            D_ovl0F_07_80045E30[2]->unk40->unk28 = 16.0f;
            D_ovl0F_07_80045E30[2]->unk40->unk2C = 16.0f;
            D_ovl0F_07_80045E30[2]->unk40->unk30 = 16.0f;
            func_ovl0F_07_80043228(D_ovl0F_07_80045CBC, 1);
            break;
        case 16:
            func_ovl0F_07_800449D0(0x17, 0, 0x1B);
            break;
        case 17:
            func_ovl0F_07_800449D0(0x17, 0, 0x1B);
            break;
        case 18:
            func_ovl0F_07_80044A10(0x80);
            func_ovl0F_07_800449D0(0x28, 0, 9);
            func_ovl0F_07_800430AC(-90.0f);
            break;
        case 19:
            func_ovl0F_07_80044A10(0x80);
            func_ovl0F_07_800449D0(6, 0, 9);
            func_ovl0F_07_800430AC(90.0f);
            break;
        case 4:
            func_ovl0F_07_80044A28();
            func_ovl0F_07_80044900(func_ovl0F_07_800440D8);
            func_ovl0F_07_800430A4();
            func_ovl0F_07_800448F8(func_ovl0F_07_80043A58, 1);
            break;
        case 5:
            func_ovl0F_07_80043094();
            func_ovl0F_07_8004308C();
            break;
        case 0x50:
            func_ovl0F_07_80043040(D_ovl0F_07_80045D14);
            func_ovl0F_07_80043040(D_ovl0F_07_80045D30);
            func_ovl0F_07_80043038();
            break;
        case 0x52:
            func_ovl0F_07_80043028();
            break;
        case 1:
            func_ovl0F_07_80043020(7, D_ovl0F_07_80045B88);
            if (D_ovl0F_07_80045B24 != 0) {
                func_ovl0F_07_80043020(D_ovl0F_07_80045B24, D_ovl0F_07_80045CBC);
            }
            break;
        case 12:
            func_ovl0F_07_80044A60(1);
            break;
        case 3:
            func_ovl0F_07_80043018();
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
        case 15:
            break;
        case 0x53:
            break;
    }
}

static void func_ovl0F_07_80043310(s32 arg0) {
    D_ovl0F_07_80045E8C = func_ovl0F_07_800453F0(arg0);
    func_ovl0F_07_80045400(D_ovl0F_07_80045E8C, 0x20000000);
    D_ovl0F_07_80045E8C->unk40 = D_ovl0F_07_80045DAC;
    D_ovl0F_07_80045E8C->unk44 = D_ovl0F_07_80045E8C->unk40 * 0.75f;
    D_ovl0F_07_80045E8C->unk3C = D_ovl0F_07_80045E8C->unk4C * 0.3f;
}

static void func_ovl0F_07_80043228(UnkStruct_ovl0F_07_80045B88 *arg0, s32 arg1) {
    f32 pos[3];

    if (func_ovl0F_07_800455F0(arg0->unk28) != 0) {
        func_ovl0F_07_80044878(22.0f, 0.0f, 3.0f, pos, 0);
        pos[1] += 2.0f;
        D_ovl0F_07_80045B28 = func_ovl0F_07_800457C0(0x25, pos, 0);
        func_ovl0F_07_80044858(0x16, 0, 3, 0x16, 3, 0x2012);
        func_ovl0F_07_80044858(0x16, 0, 4, 0x16, 4, 0x2011);
        D_ovl0F_07_80045B24 = 1;
    } else {
        D_ovl0F_07_80045B24 = 0;
    }
    func_ovl0F_07_80043178(arg0, D_ovl0F_07_80045B24);
}

static void func_ovl0F_07_80043178(UnkStruct_ovl0F_07_80045B88 *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *arg0->unk0 = func_ovl0F_07_80045288(arg0->unk4, arg0->unk8);
        func_ovl0F_07_80045218(*arg0->unk0, arg0->unk24 | 0x01000000);
        func_ovl0F_07_800430F4(arg0);
        (*arg0->unk0)->unk40->unk1C = arg0->unk18;
        (*arg0->unk0)->unk40->unk20 = arg0->unk1C;
        (*arg0->unk0)->unk40->unk24 = arg0->unk20;
        arg0++;
    }
}

static void func_ovl0F_07_800430F4(UnkStruct_ovl0F_07_80045B88 *arg0) {
    f32 pos[3];

    func_ovl0F_07_80044878(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

static void func_ovl0F_07_80043040(s32 *arg0) {
    if (func_ovl0F_07_800449E0(arg0[0], arg0[1], arg0[2], arg0[3]) != 0) {
        func_ovl0F_07_80044910(arg0[4], arg0[5], arg0[6]);
    }
}

void func_ovl0F_07_80043010(void) {
}
