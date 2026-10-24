/*
 * NON_MATCHING: ovl_0F_09's game object, complete: every function and its data
 * (.data and .rodata as the original, .bss 0x70).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 508, eu 508, jp 508
 *
 * Every function is the right size but func_ovl0F_09_80043200 and
 * func_ovl0F_09_80043D88 (each a word short) and func_ovl0F_09_80044528
 * (its padding, below); the stubs and the
 * data (.data 0x220, .rodata 0x90, .bss 0x70) are all where they belong.
 * What still differs in us (words):
 * - func_ovl0F_09_80043010 (34): the stubs and functions up to
 *   func_ovl0F_09_800432CC. func_ovl0F_09_80043200's loop: the original
 *   tests `slt v1,zero,s2; beqz v1` first and `slt v1,s0,s2` at the end,
 *   ours `blez s2` and `slt v0` (`while (i++ < count)` comes closest;
 *   `for` gives `bne`); one word short, so the stubs after it shift.
 * - func_ovl0F_09_8004343C (397, mostly register names and shifts): the
 *   original keeps &D_ovl0F_09_80046200 in s1 in every case (across
 *   func_ovl0F_09_80045A30's call in case 2), ours in t1 (reloaded after the
 *   call), so case 20 also gets the player in s1 rather than s2. Case 0x50's
 *   first test loads D_ovl0F_09_800460F4 through v0 rather than s1, and the
 *   second through its own base rather than 0x1C(s1): in the original the two
 *   four-word areas share a base and nothing else does (a [2][7] array or a
 *   struct shares it with everything, a struct by value goes through the
 *   stack). As in ovl_0F_08, case 2's loops put `move s2,zero` before the
 *   table's address, and `D_ovl0F_09_80046260 = -1;` leaves `lui a0` before
 *   it.
 * - func_ovl0F_09_80043D88 (64): ovl_0F_08's func_ovl0F_08_80043A28 (see
 *   there): branch operand order and float registers in the pack at the end.
 * - func_ovl0F_09_80044528 (13): only the nops after its endless loop. IDO
 *   pads the dead epilogue to a 32-byte boundary of the object, so they
 *   follow once everything before matches.
 */
#include "common.h"

/*
 * ovl_0F_09's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). ovl_0F_08 (1FF8F0) is its
 * near twin (all but the handler, func_ovl0F_09_80043200 and the task
 * func_ovl0F_09_80044528 are its code). The statics IDO inlines everywhere
 * are named for the empty stubs they leave.
 */

/* a model the stage places: seven in D_ovl0F_09_80045FC0 */
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
} UnkStruct_ovl0F_09_80045FC0; /* size 0x2C */

/* seven arguments of func_ovl0F_09_80044E58 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0F_09_8004612C; /* size 0x1C */

void func_ovl0F_09_80044C58(s32);
void func_ovl0F_09_80044C70(s32);
void func_ovl0F_09_80044C98(s32, s32, s32, s32, s32, s32);
void func_ovl0F_09_80044CB8(f32, f32, f32, f32 *, s32);
void func_ovl0F_09_80044D38(void (*)(UnkStructA *), s32);
void func_ovl0F_09_80044D40(void (*)(UnkStructA *));
void func_ovl0F_09_80044D50(s32, s32, s32);
s32 func_ovl0F_09_80044D58(void);
s32 *func_ovl0F_09_80044DA8(void);
void func_ovl0F_09_80044DC0(s32);
void func_ovl0F_09_80044DC8(s32);
void func_ovl0F_09_80044E08(void);
void func_ovl0F_09_80044E10(s32, s32, s32);
void func_ovl0F_09_80044E18(Vec3f *);
s32 func_ovl0F_09_80044E20(s32, s32, s32, s32);
s32 func_ovl0F_09_80044E38(void);
void func_ovl0F_09_80044E40(s32, void *);
void func_ovl0F_09_80044E48(s32);
void func_ovl0F_09_80044E50(s32);
void func_ovl0F_09_80044E58(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0F_09_80044E68(void);
void func_ovl0F_09_80044E70(s32);
UnkStructA *func_ovl0F_09_80044E98(s32);
void func_ovl0F_09_80044EA0(s32);
UnkStructA *func_ovl0F_09_80044ED8(s32);
void func_ovl0F_09_80045350(UnkStructA_40 *, s32);
void func_ovl0F_09_80045498(f32, f32, f32);
void func_ovl0F_09_800454B8(f32, f32, f32);
void func_ovl0F_09_800454C0(f32 *, f32 *, f32 *);
void func_ovl0F_09_800454F8(s32);
void func_ovl0F_09_80045500(s32);
void func_ovl0F_09_80045550(f32, f32);
s32 func_ovl0F_09_80045608(UnkStructA *, s32);
void func_ovl0F_09_80045630(UnkStructA *);
void func_ovl0F_09_80045638(UnkStructA *, UnkStructA *);
void func_ovl0F_09_80045658(UnkStructA *, s32);
void func_ovl0F_09_80045660(UnkStructA *, s32);
s32 func_ovl0F_09_80045670(UnkStructA *);
UnkStructA *func_ovl0F_09_800456C8(s32, s32);
void func_ovl0F_09_800456D8(UnkStructA *);
s32 func_ovl0F_09_80045778(UnkStructA *, s32, UnkStructA *);
s32 func_ovl0F_09_800457A8(void (*)(void), s32, s32, s32, s32);
void func_ovl0F_09_800457B0(s32);
void func_ovl0F_09_800457B8(void);
void func_ovl0F_09_800457C8(s32);
s32 func_ovl0F_09_800457D0(void);
void func_ovl0F_09_800457F0(void);
UnkStructC *func_ovl0F_09_80045830(s32);
void func_ovl0F_09_80045840(UnkStructC *, s32);
s32 func_ovl0F_09_80045A30(s32);
void func_ovl0F_09_80045B10(u32 (*)[3]);
void func_ovl0F_09_80045BF8(s32, f32, f32, f32, s32);
void func_ovl0F_09_80045CB8(s32, s32, s32);
void func_ovl0F_09_80045D30(s32);
void func_ovl0F_09_80045D50(s32, f32, f32, f32);

void func_ovl0F_09_80043010(void);
void func_ovl0F_09_800432CC(f32);
void func_ovl0F_09_8004343C(s32);
void func_ovl0F_09_80043D88(UnkStructA *);
void func_ovl0F_09_80044408(UnkStructA *);
void func_ovl0F_09_80044528(void);
void func_ovl0F_09_8004460C(void);
void func_ovl0F_09_80044810(s32, UnkStructA *);
void func_ovl0F_09_80044844(f32, f32, f32);
void func_ovl0F_09_800448A0(void);
void func_ovl0F_09_800448B8(void);

static void func_ovl0F_09_80043028(void);
static void func_ovl0F_09_800430C4(void);
static void func_ovl0F_09_800430BC(void);
static void func_ovl0F_09_80043150(s32);
static void func_ovl0F_09_80043200(UnkStructA *, s32, f32, f32);
static void func_ovl0F_09_800432C4(void);
static void func_ovl0F_09_80043314(s32);
static void func_ovl0F_09_80043398(UnkStruct_ovl0F_09_80045FC0 *);
static s32 func_ovl0F_09_80043CD0(UnkStructA *);
static void func_ovl0F_09_80043CD8(f32);
static void func_ovl0F_09_80043CC8(s32 *, f32, f32);

/* .bss */
UnkStructA *D_ovl0F_09_80046200[7];
u8 D_ovl0F_09_80046220[0x10];
Vec3f D_ovl0F_09_80046230;
s32 D_ovl0F_09_8004623C;
u8 D_ovl0F_09_80046240[0x4];
s32 D_ovl0F_09_80046244;
s32 D_ovl0F_09_80046248;
u8 D_ovl0F_09_8004624C[0x4];
Vec3f D_ovl0F_09_80046250;
UnkStructC *D_ovl0F_09_8004625C;
s32 D_ovl0F_09_80046260;

/* .data */
f32 D_ovl0F_09_80045F50 = 0.01f;
f32 D_ovl0F_09_80045F54 = 0.1f;
s32 D_ovl0F_09_80045F58 = 0;
s32 D_ovl0F_09_80045F5C = 0;
UnkStructA *D_ovl0F_09_80045F60 = NULL;
s32 D_ovl0F_09_80045F64 = 0;
s32 D_ovl0F_09_80045F68 = 0;
/* passed to func_ovl0F_09_80045B10: three 12-byte records */
u32 D_ovl0F_09_80045F6C[][3] = {
    { 0x25D0001, 0xE, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
/* four 12-byte records, each passed to func_ovl0F_09_80045CB8 */
u32 D_ovl0F_09_80045F90[][3] = {
    { 0, 0x14, 0xF2 },
    { 1, 0x16, 0xF4 },
    { 2, 0x12, 0xF0 },
    { 3, 0x15, 0xF3 },
};
UnkStruct_ovl0F_09_80045FC0 D_ovl0F_09_80045FC0[7] = {
    { &D_ovl0F_09_80046200[0], 0x231, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_09_80046200[1], 0x232, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0x80000, 0 },
    { &D_ovl0F_09_80046200[2], 0x268, 0, 0.0f, 0.0f, 0.0f, 0.0f, 260.0f, 0.0f, 0, 0 },
    { &D_ovl0F_09_80046200[3], 0x22B, 0, 14.0f, 0.0f, 12.0f, 0.0f, -90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_09_80046200[4], 0x234, 0, 73.0f, 0.0f, 8.0f, 0.0f, -90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_09_80046200[5], 0x235, 0, 73.0f, 0.0f, 8.0f, 0.0f, -90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_09_80046200[6], 0x26C, 0, 41.0f, 0.0f, 18.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};
/* func_ovl0F_09_8004343C's: two sets of four arguments to test, three to pass on */
s32 D_ovl0F_09_800460F4[4] = { 6, 0x12, 6, 0x12 };
s32 D_ovl0F_09_80046104 = 0x5E;
s32 D_ovl0F_09_80046108 = 0x13;
s32 D_ovl0F_09_8004610C = 0;
s32 D_ovl0F_09_80046110[4] = { 0x29, 0x12, 0x29, 0x12 };
s32 D_ovl0F_09_80046120 = 0x61;
s32 D_ovl0F_09_80046124 = 0x13;
s32 D_ovl0F_09_80046128 = 0;
UnkStruct_ovl0F_09_8004612C D_ovl0F_09_8004612C[2] = {
    { 0x40, 3, 8.5f, 2, 0, 1, 0 },
    { 0xC0, 3, 8.5f, 3, 0, 1, 0 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0F_09_80044908(void) {
    D_ovl0F_09_80046240[0] = D_ovl0F_09_8004624C[0];
}

/* Taking the task's address here (as well as in 80043028/800430C4) makes
 * the tasks and callbacks come out at their own turn, after the handler,
 * rather than pulled out ahead of their takers (as in ovl_0F_08). */
static void func_ovl0F_09_80044900(void) {
    func_ovl0F_09_800457A8(func_ovl0F_09_8004460C, 0, 0, 0, 0x130);
}

/* A second caller keeps func_ovl0F_09_80043398 from being inlined into the
 * handler (as in ovl_0F_08). */
static void func_ovl0F_09_800448F8(void) {
    func_ovl0F_09_80043398(D_ovl0F_09_80045FC0);
}

static void func_ovl0F_09_800448F0(void) {
}

static void func_ovl0F_09_800448E8(void) {
}

static void func_ovl0F_09_800448E0(void) {
}

static void func_ovl0F_09_800448D8(void) {
}

static void func_ovl0F_09_800448D0(void) {
}

static void func_ovl0F_09_800448C8(void) {
}

static void func_ovl0F_09_800448C0(void) {
}

void func_ovl0F_09_800448B8(void) {
}

void func_ovl0F_09_800448A0(void) {
    D_ovl0F_09_80046244 = -1;
    D_ovl0F_09_80046248 = -1;
}

void func_ovl0F_09_80044844(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_09_80045498(D_ovl0F_09_80046250.x, D_ovl0F_09_80046250.y, D_ovl0F_09_80046250.z);
    func_ovl0F_09_800454B8(arg0, arg1, arg2);
    func_ovl0F_09_800457C8(180);
}

void func_ovl0F_09_80044810(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0F_09_80045D50(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0F_09_8004460C(void) {
    s32 dir;
    UnkStructA *obj;
    f32 angle;
    f32 step;
    f32 i;

    dir = func_ovl0F_09_800457D0();
    obj = func_ovl0F_09_80044E98(func_ovl0F_09_80044E38());
    D_ovl0F_09_80045F68 = 1;
    angle = 0.0f;
    i = 0.0f;
    func_ovl0F_09_800454C0(NULL, &angle, NULL);
    func_ovl0F_09_80044EA0(1);
    func_ovl0F_09_80044DC8(1);
    func_ovl0F_09_80044DC0(0);
    func_ovl0F_09_80045500(0x7F);
    if (dir == 0) {
        step = -((angle > 180.0f ? 360.0f - angle : angle) / 50.0f);
    } else {
        step = (angle > 180.0f ? 360.0f - angle : angle) / 50.0f;
    }
    step *= 1.1f;
    while (i < 100.0f) {
        func_ovl0F_09_80045498(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
        func_ovl0F_09_800454B8(32768.0f, -angle, 32768.0f);
        i += 1.0f;
        angle += step;
        func_ovl0F_09_800457F0();
    }
    func_ovl0F_09_80044DC8(0);
    func_ovl0F_09_80044EA0(0);
    func_ovl0F_09_80044DC0(1);
    func_ovl0F_09_800454F8(0x1F);
    D_ovl0F_09_80045F68 = 0;
    func_ovl0F_09_800457B8();
}

/* a task: turns model 5 for 200 frames, then idles */
void func_ovl0F_09_80044528(void) {
    s32 speed;
    s32 i;

    i = 0;
    speed = func_ovl0F_09_800457D0();
    func_ovl0F_09_80045350(D_ovl0F_09_80046200[1]->unk40, 0x61);
    func_ovl0F_09_80045658(D_ovl0F_09_80046200[5], 0x80000);
    while (i < 200) {
        D_ovl0F_09_80046200[5]->unk40->unk36 += speed;
        func_ovl0F_09_800457F0();
        i++;
    }
    func_ovl0F_09_80045350(D_ovl0F_09_80046200[1]->unk40, 0x60);
    func_ovl0F_09_80045660(D_ovl0F_09_80046200[5], 0x80000);
    while (1) {
        func_ovl0F_09_800457C8(100);
    }
}

void func_ovl0F_09_80044408(UnkStructA *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl0F_09_80045500(0x10);
    }
    dx = arg0->unk40->unk28 / 30.0f;
    dy = arg0->unk40->unk2C / 30.0f;
    dz = arg0->unk40->unk30 / 30.0f;
    func_ovl0F_09_80045660(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        arg0->unk40->unk28 -= dx;
        arg0->unk40->unk2C -= dy;
        arg0->unk40->unk30 -= dz;
        func_ovl0F_09_800456D8(arg0);
        func_ovl0F_09_800457F0();
    }
    func_ovl0F_09_80045660(arg0, 0x01000000);
}

static void func_ovl0F_09_80043D80(s16 x, s16 z, f32 *vel) {
    vel[0] = x * 0.002f;
    vel[2] = z * 0.002f;
}

void func_ovl0F_09_80043D88(UnkStructA *arg0) {
    f32 vel[3];
    f32 dx;
    f32 dz;
    f32 pos[3];
    UnkStructA_40 *p;

    dx = arg0->unk40->unk10 - arg0->unk58;
    dz = arg0->unk40->unk18 - arg0->unk60;
    if (arg0->unk8 & 1) {
        D_ovl0F_09_80045F5C = 1;
        D_ovl0F_09_80045F60 = arg0;
    } else {
        D_ovl0F_09_80045F5C = 0;
        D_ovl0F_09_80045F60 = NULL;
    }
    if (arg0->unk68 != 0.0f || arg0->unk6C != 0.0f) {
        arg0->unk64 = 0;
        D_ovl0F_09_80045F58 = 0;
        return;
    }
    p = arg0->unk40;
    pos[0] = p->unk10;
    pos[1] = p->unk14;
    pos[2] = p->unk18;
    func_ovl0F_09_80043D80(arg0->unk64 >> 16, arg0->unk64 & 0xFFFF, vel);
    if ((s32)vel[0] != (s32)dx) {
        arg0->unk40->unk10 = arg0->unk58;
        if ((s32)dx < (s32)vel[0]) {
            vel[0] -= (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl0F_09_80045F54 : D_ovl0F_09_80045F50);
            if (vel[0] < dx) {
                vel[0] = dx;
            }
            func_ovl0F_09_80043CD8(dx);
        } else if ((s32)vel[0] < (s32)dx) {
            vel[0] += (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl0F_09_80045F54 : D_ovl0F_09_80045F50);
            if (dx < vel[0]) {
                vel[0] = dx;
            }
            func_ovl0F_09_80043CD8(dx);
        }
        arg0->unk40->unk10 += vel[0];
    }
    if ((s32)vel[2] != (s32)dz) {
        arg0->unk40->unk18 = arg0->unk60;
        if ((s32)dz < (s32)vel[2]) {
            vel[2] -= (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl0F_09_80045F54 : D_ovl0F_09_80045F50);
            if (vel[2] < dz) {
                vel[2] = dz;
            }
            func_ovl0F_09_80043CD8(dz);
        } else if ((s32)vel[2] < (s32)dz) {
            vel[2] += (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl0F_09_80045F54 : D_ovl0F_09_80045F50);
            if (dz < vel[2]) {
                vel[2] = dz;
            }
            func_ovl0F_09_80043CD8(dz);
        }
        arg0->unk40->unk18 += vel[2];
    }
    if (func_ovl0F_09_80043CD0(arg0)) {
        func_ovl0F_09_80043CC8(&arg0->unk64, 0.0f, 0.0f);
        arg0->unk40->unk10 = pos[0];
        arg0->unk40->unk14 = pos[1];
        arg0->unk40->unk18 = pos[2];
    } else {
        func_ovl0F_09_80043CC8(&arg0->unk64, vel[0], vel[2]);
    }
}

static void func_ovl0F_09_80043CC8(s32 *dst, f32 x, f32 z) {
    *dst = ((s16)(x * 500.0f) << 16) | ((s16)(z * 500.0f) & 0xFFFF);
}

static s32 func_ovl0F_09_80043CD0(UnkStructA *arg0) {
    s32 hit;
    s32 saved;
    UnkStructA *other;
    s32 id;

    hit = 0;
    other = NULL;
    saved = arg0->unkC;
    arg0->unkC = 0;
    if (arg0->unk8 & 1) {
        other = func_ovl0F_09_80044ED8(func_ovl0F_09_80044E38());
    } else if (arg0->unk8 & 2) {
        id = func_ovl0F_09_80044E38();
        if (func_ovl0F_09_80044ED8(id) == arg0) {
            other = func_ovl0F_09_80044E98(id);
        } else {
            other = NULL;
        }
    }
    if (other != NULL) {
        if (func_ovl0F_09_80045778(arg0, 0x10, other) != 0) {
            hit = 1;
        }
    } else if (func_ovl0F_09_80045608(arg0, 0x10) != 0) {
        hit = 1;
    }
    arg0->unkC = saved;
    return hit;
}

static void func_ovl0F_09_80043CD8(f32 arg0) {
    if (D_ovl0F_09_80045F5C != 0) {
        if (D_ovl0F_09_80045F58 == 0) {
            if (arg0 == 0.0f) {
                func_ovl0F_09_80045D30(0x32);
            } else {
                func_ovl0F_09_80045D30(0x27);
            }
            D_ovl0F_09_80045F58 = 20;
            func_ovl0F_09_80045BF8(0x19, D_ovl0F_09_80045F60->unk40->unk10, D_ovl0F_09_80045F60->unk40->unk14,
                                   D_ovl0F_09_80045F60->unk40->unk18, 0);
        } else {
            D_ovl0F_09_80045F58--;
        }
    }
}


void func_ovl0F_09_800432CC(f32 arg0) {
    f32 sp1C;

    func_ovl0F_09_800454C0(&sp1C, NULL, NULL);
    func_ovl0F_09_800454B8(sp1C + arg0, 32768.0f, 32768.0f);
}

static void func_ovl0F_09_80043434(void) {
    s32 count;
    u32 (*p)[3];
    s32 i;

    D_ovl0F_09_80046260 = -1;
    func_ovl0F_09_80045B10(D_ovl0F_09_80045F6C);
    p = D_ovl0F_09_80045F90;
    count = 4;
    for (i = 0; i < count; i++) {
        func_ovl0F_09_80045CB8((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}

static void func_ovl0F_09_8004342C(void) {
    func_ovl0F_09_80044C58(0x230);
    func_ovl0F_09_80044C70(0x23F);
    func_ovl0F_09_80044E08();
}

static void func_ovl0F_09_80043424(void) {
    s32 pad[2];

    D_ovl0F_09_80045F68 = 0;
    func_ovl0F_09_800430BC();
}

static void func_ovl0F_09_8004341C(s32 arg1, UnkStruct_ovl0F_09_80045FC0 *arg0) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *arg0->unk0 = func_ovl0F_09_800456C8(arg0->unk4, arg0->unk8);
        func_ovl0F_09_80045658(*arg0->unk0, arg0->unk24 | 0x01000000);
        func_ovl0F_09_80043398(arg0);
        (*arg0->unk0)->unk40->unk1C = arg0->unk18;
        (*arg0->unk0)->unk40->unk20 = arg0->unk1C;
        (*arg0->unk0)->unk40->unk24 = arg0->unk20;
        arg0++;
    }
}

static void func_ovl0F_09_80043390(void) {
    D_ovl0F_09_80046200[4]->unk40->unk14 -= 3200.0f;
    D_ovl0F_09_80046200[5]->unk40->unk14 -= 3200.0f;
    D_ovl0F_09_80046200[6]->unk40->unk10 += 50.0f;
}

static void func_ovl0F_09_800432AC(f32 arg0, f32 arg1) {
    D_ovl0F_09_80045F50 = arg0;
    D_ovl0F_09_80045F54 = arg1;
    D_ovl0F_09_80045F58 = 0;
}

static void func_ovl0F_09_800432B4(void) {
    if (func_ovl0F_09_80044DA8()[4] == 0) {
        func_ovl0F_09_800432AC(0.3f, 0.5f);
    } else {
        func_ovl0F_09_800432AC(0.12f, 0.15f);
    }
}

static void func_ovl0F_09_800432BC(void) {
    func_ovl0F_09_80044E68();
    func_ovl0F_09_80044D40(func_ovl0F_09_80044408);
    func_ovl0F_09_800432B4();
    func_ovl0F_09_80044D38(func_ovl0F_09_80043D88, 1);
}

/* ends the task func_ovl0F_09_80044528, if it runs */
static void func_ovl0F_09_800432C4(void) {
    if (D_ovl0F_09_80046260 != -1) {
        func_ovl0F_09_800457B0(D_ovl0F_09_80046260);
        D_ovl0F_09_80046260 = -1;
    }
}

static void func_ovl0F_09_800432A4(void) {
    switch (func_ovl0F_09_80044D58()) {
        case 17:
            func_ovl0F_09_80044E58(D_ovl0F_09_8004612C[0].unk0, D_ovl0F_09_8004612C[0].unk4,
                                   D_ovl0F_09_8004612C[0].unk8, D_ovl0F_09_8004612C[0].unkC,
                                   D_ovl0F_09_8004612C[0].unk10, D_ovl0F_09_8004612C[0].unk14,
                                   D_ovl0F_09_8004612C[0].unk18);
            break;
        case 20:
            func_ovl0F_09_80043200(D_ovl0F_09_80046200[6], 200, 0.0f, 3.0f);
            func_ovl0F_09_80045630(D_ovl0F_09_80046200[6]);
            func_ovl0F_09_80044E50(0xC0);
            func_ovl0F_09_80044E98(func_ovl0F_09_80044E38())->unk40->unk10 += 50.0f;
            func_ovl0F_09_80044E58(D_ovl0F_09_8004612C[1].unk0, D_ovl0F_09_8004612C[1].unk4,
                                   D_ovl0F_09_8004612C[1].unk8, D_ovl0F_09_8004612C[1].unkC,
                                   D_ovl0F_09_8004612C[1].unk10, D_ovl0F_09_8004612C[1].unk14,
                                   D_ovl0F_09_8004612C[1].unk18);
            func_ovl0F_09_80044DC0(1);
            func_ovl0F_09_80044E48(0);
            break;
    }
    func_ovl0F_09_800432C4();
}

static void func_ovl0F_09_800431F8(void) {
    func_ovl0F_09_80044E98(func_ovl0F_09_80044E38())->unk64 = 0;
    D_ovl0F_09_80045F58 = 0;
}

static void func_ovl0F_09_80043020(s32 count, UnkStruct_ovl0F_09_80045FC0 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_09_80045670(*p->unk0);
        p++;
    }
}

static void func_ovl0F_09_80043018(void) {
    D_ovl0F_09_8004623C = func_ovl0F_09_80044E38();
    func_ovl0F_09_80044E18(&D_ovl0F_09_80046230);
    func_ovl0F_09_80044E40(D_ovl0F_09_8004623C, D_ovl0F_09_80046220);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_09_8004343C(s32 arg0) {
    UnkStructA *obj;

    switch (arg0) {
        case 2:
            func_ovl0F_09_80043434();
            func_ovl0F_09_8004342C();
            func_ovl0F_09_80043424();
            func_ovl0F_09_8004341C(7, D_ovl0F_09_80045FC0);
            func_ovl0F_09_80043390();
            /* fake (as in ovl_0F_08): ends the block, so the call is not
             * scheduled into the stores before it */
            if (D_ovl0F_09_80045F5C && D_ovl0F_09_80045F5C && D_ovl0F_09_80045F5C) {}
            if (func_ovl0F_09_80045A30(0x405) == 0) {
                func_ovl0F_09_80043314(0x279);
            } else {
                func_ovl0F_09_80043314(0x27A);
            }
            D_ovl0F_09_80046200[2]->unk40->unk10 = 2400.0f;
            D_ovl0F_09_80046200[2]->unk40->unk14 = 2600.0f;
            D_ovl0F_09_80046200[2]->unk40->unk18 = 5200.0f;
            D_ovl0F_09_80046200[2]->unk40->unk28 = 16.0f;
            D_ovl0F_09_80046200[2]->unk40->unk2C = 16.0f;
            D_ovl0F_09_80046200[2]->unk40->unk30 = 16.0f;
            break;
        case 17:
            func_ovl0F_09_80044E50(0x40);
            func_ovl0F_09_80044E10(6, 0, 0x12);
            func_ovl0F_09_800432CC(-90.0f);
            break;
        case 19:
            func_ovl0F_09_80044E10(0x29, 0, 0x12);
            break;
        case 20:
            func_ovl0F_09_80044E50(0xC0);
            func_ovl0F_09_80044E10(0x29, 0, 0x12);
            obj = func_ovl0F_09_80044E98(func_ovl0F_09_80044E38());
            func_ovl0F_09_80044DC0(0);
            obj->unk40->unk10 += 50.0f;
            obj->unk40->unk14 -= 600.0f;
            D_ovl0F_09_80046200[6]->unk40->unk14 -= 600.0f;
            D_ovl0F_09_80046200[5]->unk40->unk36 = 50;
            D_ovl0F_09_80046260 = func_ovl0F_09_800457A8(func_ovl0F_09_80044528, 1, 0, 0, 0x110);
            func_ovl0F_09_800432CC(-90.0f);
            break;
        case 4:
            func_ovl0F_09_800432BC();
            break;
        case 5:
            func_ovl0F_09_800432A4();
            break;
        case 0x50:
            if (func_ovl0F_09_80044E20(D_ovl0F_09_800460F4[0], D_ovl0F_09_800460F4[1], D_ovl0F_09_800460F4[2],
                                       D_ovl0F_09_800460F4[3]) != 0) {
                func_ovl0F_09_80044D50(D_ovl0F_09_80046104, D_ovl0F_09_80046108, D_ovl0F_09_8004610C);
            }
            if (func_ovl0F_09_80044E20(D_ovl0F_09_80046110[0], D_ovl0F_09_80046110[1], D_ovl0F_09_80046110[2],
                                       D_ovl0F_09_80046110[3]) != 0) {
                func_ovl0F_09_80044DC0(0);
                func_ovl0F_09_80044E48(1);
                func_ovl0F_09_80044E70(1);
                D_ovl0F_09_80046200[5]->unk40->unk36 = 250;
                D_ovl0F_09_80046260 = func_ovl0F_09_800457A8(func_ovl0F_09_80044528, -1, 0, 0, 0x110);
                func_ovl0F_09_800457C8(10);
                func_ovl0F_09_80043200(NULL, 26, 2.0f, 0.0f);
                func_ovl0F_09_80044C98(D_ovl0F_09_80046110[0], 0, D_ovl0F_09_80046110[1],
                                       D_ovl0F_09_80046110[2] + 1, D_ovl0F_09_80046110[3], 0x10);
                func_ovl0F_09_80043200(D_ovl0F_09_80046200[6], 100, 0.0f, -2.5f);
                func_ovl0F_09_80044D50(D_ovl0F_09_80046120, D_ovl0F_09_80046124, D_ovl0F_09_80046128);
            }
            break;
        case 0x52:
            func_ovl0F_09_800431F8();
            func_ovl0F_09_80043150(2);
            break;
        case 0x53:
            func_ovl0F_09_80043150(1);
            break;
        case 1:
            func_ovl0F_09_80043020(7, D_ovl0F_09_80045FC0);
            if (D_ovl0F_09_80046260 != -1) {
                func_ovl0F_09_800457B0(D_ovl0F_09_80046260);
                D_ovl0F_09_80046260 = -1;
            }
            break;
        case 12:
            func_ovl0F_09_80044EA0(1);
            break;
        case 3:
            func_ovl0F_09_80043018();
            break;
    }
}

static void func_ovl0F_09_80043398(UnkStruct_ovl0F_09_80045FC0 *arg0) {
    f32 pos[3];

    func_ovl0F_09_80044CB8(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

static void func_ovl0F_09_80043314(s32 arg0) {
    D_ovl0F_09_8004625C = func_ovl0F_09_80045830(arg0);
    func_ovl0F_09_80045840(D_ovl0F_09_8004625C, 0x20000000);
    D_ovl0F_09_8004625C->unk40 = 0.6f;
    D_ovl0F_09_8004625C->unk44 = D_ovl0F_09_8004625C->unk40 * 0.75f;
    D_ovl0F_09_8004625C->unk3C = D_ovl0F_09_8004625C->unk4C * 0.3f;
}

/* moves the player (and what it rides, if anything) by (dx, dy) a frame for
 * count frames */
static void func_ovl0F_09_80043200(UnkStructA *ride, s32 count, f32 dx, f32 dy) {
    UnkStructA *obj;
    f32 saved;
    s32 i;

    obj = func_ovl0F_09_80044E98(func_ovl0F_09_80044E38());
    saved = obj->unk70;
    obj->unk70 = 0.0f;
    if (ride != NULL) {
        func_ovl0F_09_80045638(obj, ride);
        func_ovl0F_09_80045658(ride, 0x200000);
    }
    i = 0;
    while (i++ < count) {
        obj->unk40->unk10 += dx;
        obj->unk40->unk14 += dy;
        func_ovl0F_09_800457F0();
    }
    obj->unk70 = saved;
}

static void func_ovl0F_09_80043150(s32 arg0) {
    switch (arg0) {
        case 0:
            if (D_ovl0F_09_80045F64 == 0) {
                func_ovl0F_09_80043028();
            } else {
                func_ovl0F_09_800430C4();
            }
            break;
        case 1:
            if (D_ovl0F_09_80045F64 != 0) {
                func_ovl0F_09_800430C4();
            }
            break;
        case 2:
            if (D_ovl0F_09_80045F64 != 1) {
                func_ovl0F_09_80043028();
            }
            break;
    }
}

static void func_ovl0F_09_800430C4(void) {
    if (D_ovl0F_09_80045F68 == 0) {
        func_ovl0F_09_800457A8(func_ovl0F_09_8004460C, 0, 0, 0, 0x130);
        func_ovl0F_09_800430BC();
    } else {
        func_ovl0F_09_800430BC();
    }
}

static void func_ovl0F_09_800430BC(void) {
    D_ovl0F_09_80045F64 = 0;
    func_ovl0F_09_80045550(70.0f, 45.0f);
}

static void func_ovl0F_09_80043028(void) {
    if (D_ovl0F_09_80045F68 == 0) {
        func_ovl0F_09_800457A8(func_ovl0F_09_8004460C, 1, 0, 0, 0x130);
        D_ovl0F_09_80045F64 = 1;
        func_ovl0F_09_80045550(-50.0f, -60.0f);
    } else {
        D_ovl0F_09_80045F64 = 1;
        func_ovl0F_09_80045550(-50.0f, -60.0f);
    }
}

void func_ovl0F_09_80043010(void) {
}
