/*
 * NON_MATCHING: ovl_0F_08's game object, complete: every function and its data
 * (.data and .rodata as the original, .bss 0x60).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 72, eu 72, jp 72
 *
 * What still differs in us (words):
 * - func_ovl0F_08_800433DC (8): scheduling only. The loops of case 2 (the
 *   models) and case 1 put `move s2,zero` (i = 0) after the table's
 *   `lui`/`addiu` and the count in the original, before them in ours; after
 *   the if/else on func_ovl0F_08_80045600, the original loads
 *   D_ovl0F_08_80045DA0[2] after `lui at,0x4516`, ours before.
 * - func_ovl0F_08_80043A28 (64): ovl_0F_07's func_ovl0F_07_80043A58 again.
 *   `if ((s32)vel[0] != (s32)dx)` gives `beq dx,vel`, the original
 *   `beq vel,dx` (z too; written the other way round it's the same); in
 *   the pack at the end the original keeps 500.0f in $f0 and the vel[0]
 *   preload in $f6 (ours $f12/$f0), and has a nop after the hit path's
 *   mul.s. One word short, so the rest is shifted.
 */
#include "common.h"

/*
 * ovl_0F_08's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). ovl_0F_07 (1FCAC0) is its
 * near twin. The statics IDO inlines everywhere are named for the empty stubs
 * they leave (their order inferred from the rules in docs/DECOMPILING.md).
 */

/* a model the stage places: six in D_ovl0F_08_80045B90 */
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
} UnkStruct_ovl0F_08_80045B90; /* size 0x2C */

/* seven arguments of func_ovl0F_08_80044A28 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0F_08_80045CD0; /* size 0x1C */

void func_ovl0F_08_80044828(s32);
void func_ovl0F_08_80044840(s32);
void func_ovl0F_08_80044888(f32, f32, f32, f32 *, s32);
void func_ovl0F_08_80044908(void (*)(UnkStructA *), s32);
void func_ovl0F_08_80044910(void (*)(UnkStructA *));
void func_ovl0F_08_80044920(s32, s32, s32);
s32 func_ovl0F_08_80044928(void);
s32 *func_ovl0F_08_80044978(void);
void func_ovl0F_08_80044990(s32);
void func_ovl0F_08_80044998(s32);
void func_ovl0F_08_800449D8(void);
void func_ovl0F_08_800449E0(s32, s32, s32);
void func_ovl0F_08_800449E8(Vec3f *);
s32 func_ovl0F_08_800449F0(s32, s32, s32, s32);
s32 func_ovl0F_08_80044A08(void);
void func_ovl0F_08_80044A10(s32, void *);
void func_ovl0F_08_80044A20(s32);
void func_ovl0F_08_80044A28(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0F_08_80044A38(void);
UnkStructA *func_ovl0F_08_80044A68(s32);
void func_ovl0F_08_80044A70(s32);
UnkStructA *func_ovl0F_08_80044AA8(s32);
void func_ovl0F_08_80044F20(UnkStructA_40 *, s32);
void func_ovl0F_08_80045068(f32, f32, f32);
void func_ovl0F_08_80045088(f32, f32, f32);
void func_ovl0F_08_80045090(f32 *, f32 *, f32 *);
void func_ovl0F_08_800450C8(s32);
void func_ovl0F_08_800450D0(s32);
void func_ovl0F_08_80045120(f32, f32);
s32 func_ovl0F_08_800451D8(UnkStructA *, s32);
void func_ovl0F_08_80045228(UnkStructA *, s32);
void func_ovl0F_08_80045230(UnkStructA *, s32);
s32 func_ovl0F_08_80045240(UnkStructA *);
UnkStructA *func_ovl0F_08_80045298(s32, s32);
void func_ovl0F_08_800452A8(UnkStructA *);
s32 func_ovl0F_08_80045348(UnkStructA *, s32, UnkStructA *);
void func_ovl0F_08_80045378(void (*)(void), s32, s32, s32, s32);
void func_ovl0F_08_80045388(void);
void func_ovl0F_08_80045398(s32);
s32 func_ovl0F_08_800453A0(void);
void func_ovl0F_08_800453C0(void);
UnkStructC *func_ovl0F_08_80045400(s32);
void func_ovl0F_08_80045410(UnkStructC *, s32);
s32 func_ovl0F_08_80045600(s32);
void func_ovl0F_08_800456E0(u32 (*)[3]);
void func_ovl0F_08_800457C8(s32, f32, f32, f32, s32);
void func_ovl0F_08_80045888(s32, s32, s32);
void func_ovl0F_08_80045900(s32);
void func_ovl0F_08_80045920(s32, f32, f32, f32);

void func_ovl0F_08_80043010(void);
void func_ovl0F_08_8004326C(f32);
void func_ovl0F_08_800433DC(s32);
void func_ovl0F_08_80043A28(UnkStructA *);
void func_ovl0F_08_800440A8(UnkStructA *);
void func_ovl0F_08_800441C8(void);
void func_ovl0F_08_800443CC(s32, UnkStructA *);
void func_ovl0F_08_80044400(f32, f32, f32);
void func_ovl0F_08_8004445C(void);
void func_ovl0F_08_80044474(void);

static void func_ovl0F_08_80043028(void);
static void func_ovl0F_08_800430C4(void);
static void func_ovl0F_08_800430BC(void);
static void func_ovl0F_08_80043150(s32);
static void func_ovl0F_08_80043200(s32 *);
static void func_ovl0F_08_800432B4(s32);
static void func_ovl0F_08_80043338(UnkStruct_ovl0F_08_80045B90 *);
static s32 func_ovl0F_08_80043970(UnkStructA *);
static void func_ovl0F_08_80043978(f32);
static void func_ovl0F_08_80043968(s32 *, f32, f32);

/* .bss */
UnkStructA *D_ovl0F_08_80045DA0[6];
u8 D_ovl0F_08_80045DB8[0x10];
Vec3f D_ovl0F_08_80045DC8;
s32 D_ovl0F_08_80045DD4;
u8 D_ovl0F_08_80045DD8[0x4];
s32 D_ovl0F_08_80045DDC;
s32 D_ovl0F_08_80045DE0;
u8 D_ovl0F_08_80045DE4[0x4];
Vec3f D_ovl0F_08_80045DE8;
UnkStructC *D_ovl0F_08_80045DF4;

/* .data */
f32 D_ovl0F_08_80045B20 = 0.01f;
f32 D_ovl0F_08_80045B24 = 0.1f;
s32 D_ovl0F_08_80045B28 = 0;
s32 D_ovl0F_08_80045B2C = 0;
UnkStructA *D_ovl0F_08_80045B30 = NULL;
s32 D_ovl0F_08_80045B34 = 0;
s32 D_ovl0F_08_80045B38 = 0;
/* passed to func_ovl0F_08_800456E0: three 12-byte records */
u32 D_ovl0F_08_80045B3C[][3] = {
    { 0x25D0001, 0xE, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
/* four 12-byte records, each passed to func_ovl0F_08_80045888 */
u32 D_ovl0F_08_80045B60[][3] = {
    { 0, 0x14, 0xF2 },
    { 1, 0x16, 0xF4 },
    { 2, 0x12, 0xF0 },
    { 3, 0x15, 0xF3 },
};
UnkStruct_ovl0F_08_80045B90 D_ovl0F_08_80045B90[6] = {
    { &D_ovl0F_08_80045DA0[0], 0x22E, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_08_80045DA0[1], 0x22F, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0x80000, 0 },
    { &D_ovl0F_08_80045DA0[2], 0x268, 0, 0.0f, 0.0f, 0.0f, 0.0f, 110.0f, 0.0f, 0, 0 },
    { &D_ovl0F_08_80045DA0[3], 0x22B, 0, 33.0f, 0.0f, 58.0f, 0.0f, 90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_08_80045DA0[4], 0x234, 0, -25.0f, 0.0f, 63.0f, 0.0f, 90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_08_80045DA0[5], 0x22C, 0, 33.0f, 0.0f, 58.0f, 0.0f, 90.0f, 0.0f, 0, 0 },
};
/* func_ovl0F_08_80043200's: four arguments to test, three to pass on */
s32 D_ovl0F_08_80045C98[7] = { 0x29, 0x12, 0x29, 0x12, 0x5E, 0x12, 0 };
s32 D_ovl0F_08_80045CB4[7] = { 6, 0x12, 6, 0x12, 0x61, 0x12, 0 };
UnkStruct_ovl0F_08_80045CD0 D_ovl0F_08_80045CD0[2] = {
    { 0xC0, 3, 8.5f, 4, 0, 1, 1 },
    { 0x40, 3, 8.5f, 4, 0, 1, 1 },
};
u8 D_ovl0F_08_80045D08[0x8] = { 0 }; /* nothing uses it */

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0F_08_800444CC(void) {
    D_ovl0F_08_80045DD8[0] = D_ovl0F_08_80045DE4[0];
}

/* Taking the task's address here (as well as in 80043028/800430C4) makes
 * the tasks and callbacks come out at their own turn, after the handler,
 * rather than pulled out ahead of their takers. A guess at the cause. */
static void func_ovl0F_08_800444C4(void) {
    func_ovl0F_08_80045378(func_ovl0F_08_800441C8, 0, 0, 0, 0x130);
}

/* A second caller keeps func_ovl0F_08_80043338 from being inlined into the
 * handler (it is a call there, with its argument in s0). */
static void func_ovl0F_08_800444BC(void) {
    func_ovl0F_08_80043338(D_ovl0F_08_80045B90);
}

static void func_ovl0F_08_800444B4(void) {
}

static void func_ovl0F_08_800444AC(void) {
}

static void func_ovl0F_08_800444A4(void) {
}

static void func_ovl0F_08_8004449C(void) {
}

static void func_ovl0F_08_80044494(void) {
}

static void func_ovl0F_08_8004448C(void) {
}

static void func_ovl0F_08_80044484(void) {
}

static void func_ovl0F_08_8004447C(void) {
}

void func_ovl0F_08_80044474(void) {
}

void func_ovl0F_08_8004445C(void) {
    D_ovl0F_08_80045DDC = -1;
    D_ovl0F_08_80045DE0 = -1;
}

void func_ovl0F_08_80044400(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_08_80045068(D_ovl0F_08_80045DE8.x, D_ovl0F_08_80045DE8.y, D_ovl0F_08_80045DE8.z);
    func_ovl0F_08_80045088(arg0, arg1, arg2);
    func_ovl0F_08_80045398(180);
}

void func_ovl0F_08_800443CC(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0F_08_80045920(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0F_08_800441C8(void) {
    s32 dir;
    UnkStructA *obj;
    f32 angle;
    f32 step;
    f32 i;

    dir = func_ovl0F_08_800453A0();
    obj = func_ovl0F_08_80044A68(func_ovl0F_08_80044A08());
    D_ovl0F_08_80045B38 = 1;
    angle = 0.0f;
    i = 0.0f;
    func_ovl0F_08_80045090(NULL, &angle, NULL);
    func_ovl0F_08_80044A70(1);
    func_ovl0F_08_80044998(1);
    func_ovl0F_08_80044990(0);
    func_ovl0F_08_800450D0(0x7F);
    if (dir == 0) {
        step = -((angle > 180.0f ? 360.0f - angle : angle) / 50.0f);
    } else {
        step = (angle > 180.0f ? 360.0f - angle : angle) / 50.0f;
    }
    step *= 1.1f;
    while (i < 100.0f) {
        func_ovl0F_08_80045068(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
        func_ovl0F_08_80045088(32768.0f, -angle, 32768.0f);
        i += 1.0f;
        angle += step;
        func_ovl0F_08_800453C0();
    }
    func_ovl0F_08_80044998(0);
    func_ovl0F_08_80044A70(0);
    func_ovl0F_08_80044990(1);
    func_ovl0F_08_800450C8(0x1F);
    D_ovl0F_08_80045B38 = 0;
    func_ovl0F_08_80045388();
}

void func_ovl0F_08_800440A8(UnkStructA *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl0F_08_800450D0(0x10);
    }
    dx = arg0->unk40->unk28 / 30.0f;
    dy = arg0->unk40->unk2C / 30.0f;
    dz = arg0->unk40->unk30 / 30.0f;
    func_ovl0F_08_80045230(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        arg0->unk40->unk28 -= dx;
        arg0->unk40->unk2C -= dy;
        arg0->unk40->unk30 -= dz;
        func_ovl0F_08_800452A8(arg0);
        func_ovl0F_08_800453C0();
    }
    func_ovl0F_08_80045230(arg0, 0x01000000);
}

static void func_ovl0F_08_80043A20(s16 x, s16 z, f32 *vel) {
    vel[0] = x * 0.002f;
    vel[2] = z * 0.002f;
}

void func_ovl0F_08_80043A28(UnkStructA *arg0) {
    f32 vel[3];
    f32 dx;
    f32 dz;
    f32 pos[3];
    UnkStructA_40 *p;

    dx = arg0->unk40->unk10 - arg0->unk58;
    dz = arg0->unk40->unk18 - arg0->unk60;
    if (arg0->unk8 & 1) {
        D_ovl0F_08_80045B2C = 1;
        D_ovl0F_08_80045B30 = arg0;
    } else {
        D_ovl0F_08_80045B2C = 0;
        D_ovl0F_08_80045B30 = NULL;
    }
    if (arg0->unk68 != 0.0f || arg0->unk6C != 0.0f) {
        arg0->unk64 = 0;
        D_ovl0F_08_80045B28 = 0;
        return;
    }
    p = arg0->unk40;
    pos[0] = p->unk10;
    pos[1] = p->unk14;
    pos[2] = p->unk18;
    func_ovl0F_08_80043A20(arg0->unk64 >> 16, arg0->unk64 & 0xFFFF, vel);
    if ((s32)vel[0] != (s32)dx) {
        arg0->unk40->unk10 = arg0->unk58;
        if ((s32)dx < (s32)vel[0]) {
            vel[0] -= (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl0F_08_80045B24 : D_ovl0F_08_80045B20);
            if (vel[0] < dx) {
                vel[0] = dx;
            }
            func_ovl0F_08_80043978(dx);
        } else if ((s32)vel[0] < (s32)dx) {
            vel[0] += (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl0F_08_80045B24 : D_ovl0F_08_80045B20);
            if (dx < vel[0]) {
                vel[0] = dx;
            }
            func_ovl0F_08_80043978(dx);
        }
        arg0->unk40->unk10 += vel[0];
    }
    if ((s32)vel[2] != (s32)dz) {
        arg0->unk40->unk18 = arg0->unk60;
        if ((s32)dz < (s32)vel[2]) {
            vel[2] -= (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl0F_08_80045B24 : D_ovl0F_08_80045B20);
            if (vel[2] < dz) {
                vel[2] = dz;
            }
            func_ovl0F_08_80043978(dz);
        } else if ((s32)vel[2] < (s32)dz) {
            vel[2] += (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl0F_08_80045B24 : D_ovl0F_08_80045B20);
            if (dz < vel[2]) {
                vel[2] = dz;
            }
            func_ovl0F_08_80043978(dz);
        }
        arg0->unk40->unk18 += vel[2];
    }
    if (func_ovl0F_08_80043970(arg0)) {
        func_ovl0F_08_80043968(&arg0->unk64, 0.0f, 0.0f);
        arg0->unk40->unk10 = pos[0];
        arg0->unk40->unk14 = pos[1];
        arg0->unk40->unk18 = pos[2];
    } else {
        func_ovl0F_08_80043968(&arg0->unk64, vel[0], vel[2]);
    }
}

static void func_ovl0F_08_80043968(s32 *dst, f32 x, f32 z) {
    *dst = ((s16)(x * 500.0f) << 16) | ((s16)(z * 500.0f) & 0xFFFF);
}

static s32 func_ovl0F_08_80043970(UnkStructA *arg0) {
    s32 hit;
    s32 saved;
    UnkStructA *other;
    s32 id;

    hit = 0;
    other = NULL;
    saved = arg0->unkC;
    arg0->unkC = 0;
    if (arg0->unk8 & 1) {
        other = func_ovl0F_08_80044AA8(func_ovl0F_08_80044A08());
    } else if (arg0->unk8 & 2) {
        id = func_ovl0F_08_80044A08();
        if (func_ovl0F_08_80044AA8(id) == arg0) {
            other = func_ovl0F_08_80044A68(id);
        } else {
            other = NULL;
        }
    }
    if (other != NULL) {
        if (func_ovl0F_08_80045348(arg0, 0x10, other) != 0) {
            hit = 1;
        }
    } else if (func_ovl0F_08_800451D8(arg0, 0x10) != 0) {
        hit = 1;
    }
    arg0->unkC = saved;
    return hit;
}

static void func_ovl0F_08_80043978(f32 arg0) {
    if (D_ovl0F_08_80045B2C != 0) {
        if (D_ovl0F_08_80045B28 == 0) {
            if (arg0 == 0.0f) {
                func_ovl0F_08_80045900(0x32);
            } else {
                func_ovl0F_08_80045900(0x27);
            }
            D_ovl0F_08_80045B28 = 20;
            func_ovl0F_08_800457C8(0x19, D_ovl0F_08_80045B30->unk40->unk10, D_ovl0F_08_80045B30->unk40->unk14,
                                   D_ovl0F_08_80045B30->unk40->unk18, 0);
        } else {
            D_ovl0F_08_80045B28--;
        }
    }
}


void func_ovl0F_08_8004326C(f32 arg0) {
    f32 sp1C;

    func_ovl0F_08_80045090(&sp1C, NULL, NULL);
    func_ovl0F_08_80045088(sp1C + arg0, 32768.0f, 32768.0f);
}

static void func_ovl0F_08_800433D4(void) {
    s32 count;
    u32 (*p)[3];
    s32 i;

    func_ovl0F_08_800456E0(D_ovl0F_08_80045B3C);
    p = D_ovl0F_08_80045B60;
    count = 4;
    for (i = 0; i < count; i++) {
        func_ovl0F_08_80045888((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}

static void func_ovl0F_08_800433CC(void) {
    func_ovl0F_08_80044828(0x22D);
    func_ovl0F_08_80044840(0x23E);
    func_ovl0F_08_800449D8();
}

static void func_ovl0F_08_800433C4(void) {
    s32 pad[2];

    D_ovl0F_08_80045B38 = 0;
    func_ovl0F_08_800430BC();
}

static void func_ovl0F_08_800433BC(s32 arg1, UnkStruct_ovl0F_08_80045B90 *arg0) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *arg0->unk0 = func_ovl0F_08_80045298(arg0->unk4, arg0->unk8);
        func_ovl0F_08_80045228(*arg0->unk0, arg0->unk24 | 0x01000000);
        func_ovl0F_08_80043338(arg0);
        (*arg0->unk0)->unk40->unk1C = arg0->unk18;
        (*arg0->unk0)->unk40->unk20 = arg0->unk1C;
        (*arg0->unk0)->unk40->unk24 = arg0->unk20;
        arg0++;
    }
}

static void func_ovl0F_08_80043330(void) {
    func_ovl0F_08_80044F20(D_ovl0F_08_80045DA0[3]->unk40, 0x61);
    func_ovl0F_08_80044F20(D_ovl0F_08_80045DA0[4]->unk40, 0x61);
    D_ovl0F_08_80045DA0[4]->unk40->unk14 -= 3200.0f;
}

static void func_ovl0F_08_80043254(f32 arg0, f32 arg1) {
    D_ovl0F_08_80045B20 = arg0;
    D_ovl0F_08_80045B24 = arg1;
    D_ovl0F_08_80045B28 = 0;
}

static void func_ovl0F_08_8004325C(void) {
    if (func_ovl0F_08_80044978()[4] == 0) {
        func_ovl0F_08_80043254(0.3f, 0.5f);
    } else {
        func_ovl0F_08_80043254(0.12f, 0.15f);
    }
}

static void func_ovl0F_08_80043264(void) {
    func_ovl0F_08_80044A38();
    func_ovl0F_08_80044910(func_ovl0F_08_800440A8);
    func_ovl0F_08_8004325C();
    func_ovl0F_08_80044908(func_ovl0F_08_80043A28, 1);
}

static void func_ovl0F_08_8004324C(void) {
    switch (func_ovl0F_08_80044928()) {
        case 17:
            func_ovl0F_08_80044A28(D_ovl0F_08_80045CD0[0].unk0, D_ovl0F_08_80045CD0[0].unk4,
                                   D_ovl0F_08_80045CD0[0].unk8, D_ovl0F_08_80045CD0[0].unkC,
                                   D_ovl0F_08_80045CD0[0].unk10, D_ovl0F_08_80045CD0[0].unk14,
                                   D_ovl0F_08_80045CD0[0].unk18);
            break;
        case 20:
            func_ovl0F_08_80044A28(D_ovl0F_08_80045CD0[1].unk0, D_ovl0F_08_80045CD0[1].unk4,
                                   D_ovl0F_08_80045CD0[1].unk8, D_ovl0F_08_80045CD0[1].unkC,
                                   D_ovl0F_08_80045CD0[1].unk10, D_ovl0F_08_80045CD0[1].unk14,
                                   D_ovl0F_08_80045CD0[1].unk18);
            break;
    }
}

static void func_ovl0F_08_800431F8(void) {
    func_ovl0F_08_80044A68(func_ovl0F_08_80044A08())->unk64 = 0;
    D_ovl0F_08_80045B28 = 0;
}

static void func_ovl0F_08_80043020(s32 count, UnkStruct_ovl0F_08_80045B90 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_08_80045240(*p->unk0);
        p++;
    }
}

static void func_ovl0F_08_80043018(void) {
    D_ovl0F_08_80045DD4 = func_ovl0F_08_80044A08();
    func_ovl0F_08_800449E8(&D_ovl0F_08_80045DC8);
    func_ovl0F_08_80044A10(D_ovl0F_08_80045DD4, D_ovl0F_08_80045DB8);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_08_800433DC(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0F_08_800433D4();
            func_ovl0F_08_800433CC();
            func_ovl0F_08_800433C4();
            func_ovl0F_08_800433BC(6, D_ovl0F_08_80045B90);
            func_ovl0F_08_80043330();
            /* fake: ends the block, so the call is not scheduled into the
             * store before it */
            if (D_ovl0F_08_80045B2C && D_ovl0F_08_80045B2C && D_ovl0F_08_80045B2C) {}
            if (func_ovl0F_08_80045600(0x405) == 0) {
                func_ovl0F_08_800432B4(0x279);
            } else {
                func_ovl0F_08_800432B4(0x27A);
            }
            D_ovl0F_08_80045DA0[2]->unk40->unk10 = 2400.0f;
            D_ovl0F_08_80045DA0[2]->unk40->unk14 = 2600.0f;
            D_ovl0F_08_80045DA0[2]->unk40->unk18 = 5200.0f;
            D_ovl0F_08_80045DA0[2]->unk40->unk28 = 16.0f;
            D_ovl0F_08_80045DA0[2]->unk40->unk2C = 16.0f;
            D_ovl0F_08_80045DA0[2]->unk40->unk30 = 16.0f;
            break;
        case 17:
            func_ovl0F_08_80044A20(0xC0);
            func_ovl0F_08_800449E0(0x29, 0, 0x12);
            func_ovl0F_08_8004326C(90.0f);
            break;
        case 18:
            func_ovl0F_08_800449E0(0x29, 0, 0x12);
            break;
        case 20:
            func_ovl0F_08_80044A20(0x40);
            func_ovl0F_08_800449E0(6, 0, 0x12);
            func_ovl0F_08_8004326C(90.0f);
            break;
        case 4:
            func_ovl0F_08_80043264();
            break;
        case 5:
            func_ovl0F_08_8004324C();
            break;
        case 0x50:
            func_ovl0F_08_80043200(D_ovl0F_08_80045C98);
            func_ovl0F_08_80043200(D_ovl0F_08_80045CB4);
            break;
        case 0x52:
            func_ovl0F_08_800431F8();
            func_ovl0F_08_80043150(2);
            break;
        case 0x53:
            func_ovl0F_08_80043150(1);
            break;
        case 1:
            func_ovl0F_08_80043020(6, D_ovl0F_08_80045B90);
            break;
        case 12:
            func_ovl0F_08_80044A70(1);
            break;
        case 3:
            func_ovl0F_08_80043018();
            break;
    }
}

static void func_ovl0F_08_80043338(UnkStruct_ovl0F_08_80045B90 *arg0) {
    f32 pos[3];

    func_ovl0F_08_80044888(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

static void func_ovl0F_08_800432B4(s32 arg0) {
    D_ovl0F_08_80045DF4 = func_ovl0F_08_80045400(arg0);
    func_ovl0F_08_80045410(D_ovl0F_08_80045DF4, 0x20000000);
    D_ovl0F_08_80045DF4->unk40 = 0.6f;
    D_ovl0F_08_80045DF4->unk44 = D_ovl0F_08_80045DF4->unk40 * 0.75f;
    D_ovl0F_08_80045DF4->unk3C = D_ovl0F_08_80045DF4->unk4C * 0.3f;
}

static void func_ovl0F_08_80043200(s32 *arg0) {
    if (func_ovl0F_08_800449F0(arg0[0], arg0[1], arg0[2], arg0[3]) != 0) {
        func_ovl0F_08_80044920(arg0[4], arg0[5], arg0[6]);
    }
}

static void func_ovl0F_08_80043150(s32 arg0) {
    switch (arg0) {
        case 0:
            if (D_ovl0F_08_80045B34 == 0) {
                func_ovl0F_08_80043028();
            } else {
                func_ovl0F_08_800430C4();
            }
            break;
        case 1:
            if (D_ovl0F_08_80045B34 != 0) {
                func_ovl0F_08_800430C4();
            }
            break;
        case 2:
            if (D_ovl0F_08_80045B34 != 1) {
                func_ovl0F_08_80043028();
            }
            break;
    }
}

static void func_ovl0F_08_800430C4(void) {
    if (D_ovl0F_08_80045B38 == 0) {
        func_ovl0F_08_80045378(func_ovl0F_08_800441C8, 0, 0, 0, 0x130);
        func_ovl0F_08_800430BC();
    } else {
        func_ovl0F_08_800430BC();
    }
}

static void func_ovl0F_08_800430BC(void) {
    D_ovl0F_08_80045B34 = 0;
    func_ovl0F_08_80045120(70.0f, 45.0f);
}

static void func_ovl0F_08_80043028(void) {
    if (D_ovl0F_08_80045B38 == 0) {
        func_ovl0F_08_80045378(func_ovl0F_08_800441C8, 1, 0, 0, 0x130);
        D_ovl0F_08_80045B34 = 1;
        func_ovl0F_08_80045120(-50.0f, -60.0f);
    } else {
        D_ovl0F_08_80045B34 = 1;
        func_ovl0F_08_80045120(-50.0f, -60.0f);
    }
}

void func_ovl0F_08_80043010(void) {
}
