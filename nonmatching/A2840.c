/*
 * NON_MATCHING: main_code's A2840, complete (every function and its
 * .data); not in the ROM.
 * flags: -O3
 * differing words: us 0, eu 0, jp 0
 *
 * All 37 functions match, the same in every version (the code is the
 * same in all three). Function order is reversed, as -O3 emits it. The
 * statics: 80288C00, 80288634 and 80289750 are empty K&R
 * `static void f() {}` called first thing in 80288C08, 80288644 and
 * 80289758 (their stubs land before them; 80289758 does the wrap
 * inline after the call); 80288C08 (`++unk4C >= limit`) is kept out of
 * line; 802884D4/8028854C/802885E4/8028863C (abs), 80288644 (the switch
 * of 80288654, taking (o, px, pz)), 80288190/80288198 and 80289758 are
 * inlined and leave stubs.
 *
 * func_80288654's diagonal cases keep a dead
 * `if (0) { func_8028863C(...); }` (keeps the inline frame area), test
 * z then x with the loads in the condition, and reload x and z from
 * the object inside the distance arguments
 * (`(px < (x = ...->unk10)) ? ...`, `func_8028863C(pz, z = ...->unk18)`):
 * an indirect load in a block keeps uopt from giving player.x/player.z
 * (address-taken by func_80250338) a live range there, so they are
 * read from the stack in each block as in the original.
 */
#include "common.h"

/* The object these functions are handed (the tables' argument). */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10[0xC];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 unk20[4];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ u8 unk34[8];
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 unk3D;
    /* 0x3E */ u8 unk3E[0xA];
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ union {
        f32 f;
        u8 b[4];
    } unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ union {
        f32 f;
        u8 b[4];
    } unk58;
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 unk5D;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ u8 unk68[6];
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ u8 unk70[8];
    /* 0x78 */ u8 unk78;
    /* 0x79 */ u8 unk79[0xB];
    /* 0x84 */ s32 unk84;
} UnkStruct_80288040;

/* A record of the table read from file 0x10B (func_802883B0). */
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x04 */ Vec3f pos;
} UnkStruct_800BC9F0;

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_8023A840;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 unk2[2];
} UnkStruct_800BA8EA;

extern UnkStruct_800BA8EA D_800BA8EA[];
extern UnkStruct_800BC9F0 D_800BC9F0[];

void func_80229E38(UnkStructA_40 *, s32, s32);
void func_8022FF58(Vec3f *, Vec3f *, f32 *);
void func_80230914(UnkStructA *);
void func_802313DC(UnkStructA *, s32);
void func_80231408(UnkStructA *, s32);
s32 func_80232D18(UnkStructA *, s32);
void func_80232DB4(UnkStructA *);
void func_8023903C(s32);
UnkStruct_8023A840 *func_8023A840(void);
s32 func_80243DDC(void);
void func_80250338(s32, Vec3f *);
void func_8026C51C(s32, f32, f32, f32);
f32 func_8026E938(UnkStructA_40 *);
s32 func_8026EE18(f32);
void func_80282430(UnkStruct_80288040 *, s32, s32);
void func_80282454(UnkStruct_80288040 *);
void func_8028301C(UnkStruct_80288040 *, s32, f32, f32, f32);
f32 func_8028322C(UnkStruct_80288040 *);
void func_80283B04(UnkStruct_80288040 *, Vec3f *);
UnkStruct_80288040 *func_802867E4(s32, f32, f32, f32);
void func_8028E8A4(s32, f32, f32, f32, s32);
void func_80291944(UnkStructA *, s32, f32);

s32 func_802884BC(UnkStruct_80288040 *);
s32 func_802884C8(UnkStruct_80288040 *);
s32 func_80288654(UnkStruct_80288040 *);
s32 func_80288B10(UnkStruct_80288040 *);
s32 func_80288B7C(UnkStruct_80288040 *);
s32 func_80288BE8(UnkStruct_80288040 *);
s32 func_80288BF4(UnkStruct_80288040 *);
s32 func_80288C40(UnkStruct_80288040 *);
s32 func_802890CC(UnkStruct_80288040 *);
s32 func_8028924C(UnkStruct_80288040 *);
s32 func_80289294(UnkStruct_80288040 *);
s32 func_80289320(UnkStruct_80288040 *);
s32 func_80289464(UnkStruct_80288040 *);
s32 func_80289760(UnkStruct_80288040 *);
s32 func_80289C00(UnkStruct_80288040 *);
void func_80289C48(UnkStruct_80288040 *);
void func_80289C50(UnkStruct_80288040 *);
void func_80289C5C(UnkStruct_80288040 *);
void func_80289C64(UnkStruct_80288040 *);
void func_80289C6C(UnkStruct_80288040 *);
void func_80289C80(UnkStruct_80288040 *);
void func_80289CCC(UnkStruct_80288040 *);
void func_80289D00(UnkStruct_80288040 *);
void func_80289D7C(UnkStruct_80288040 *);
void func_80289DB0(UnkStruct_80288040 *);
void func_80289DB8(UnkStruct_80288040 *);
void func_80289E24(UnkStruct_80288040 *);
void func_80289E64(UnkStruct_80288040 *);
void func_80289E6C(UnkStruct_80288040 *);
void func_80289EA0(UnkStruct_80288040 *);
void func_80289EB8(UnkStruct_80288040 *);
void func_80289F04(UnkStruct_80288040 *);
void func_8028A00C(UnkStruct_80288040 *);

/* How many records func_802883B0 read into D_800BC9F0. */
s32 D_802A1B70 = 0;

/* Per kind (unk3D): the test before the object starts (state 0). */
s32 (*D_802A1B74[])(UnkStruct_80288040 *) = {
    func_802884BC, func_802884C8, func_80288654,
    func_80288B10, func_80288B7C, func_80288BE8,
};

/* Per kind (unk3C): each frame while it runs (state 2); 0 ends it. */
s32 (*D_802A1B8C[])(UnkStruct_80288040 *) = {
    func_80288BF4, func_80288C40, func_802890CC,
    func_8028924C, func_80289294, func_80289320,
    func_80289464, func_80289760, func_80289C00,
};

/* Per kind (unk3C): when it starts (state 1). */
void (*D_802A1BB0[])(UnkStruct_80288040 *) = {
    func_80289DB0, func_80289DB8, func_80289E24,
    func_80289E64, func_80289E6C, func_80289EA0,
    func_80289EB8, func_80289F04, func_8028A00C,
};

/* Per kind (unk3C): when it ends. */
void (*D_802A1BD4[])(UnkStruct_80288040 *) = {
    func_80289C48, func_80289C50, func_80289C5C,
    func_80289C64, func_80289C6C, func_80289C80,
    func_80289CCC, func_80289D00, func_80289D7C,
};

/* IDO -O3 emits a file's functions last to first: they are written in
 * the reverse of their order in the ROM. */

void func_8028A00C(UnkStruct_80288040 *arg0) {
    arg0->unk50.f = arg0->unk2C;
    arg0->unk58.b[0] = arg0->unk1F;
    arg0->unk54 = 300.0f;
    arg0->unk2C = 10.200001f;
    arg0->unk1F = 0;
    func_80231408(arg0->unk0, 0x100);
}

void func_80289F04(UnkStruct_80288040 *arg0) {
    Vec3f player;
    Vec3f pos;
    f32 angles[3];

    func_80250338(func_80243DDC(), &player);
    pos.x = arg0->unk0->unk40->unk10;
    pos.y = arg0->unk0->unk40->unk14;
    pos.z = arg0->unk0->unk40->unk18;
    func_8022FF58(&pos, &player, angles);
    arg0->unk64 = angles[0];
    arg0->unk60 = angles[1];
    arg0->unk50.f = player.y + 50.0f;
    arg0->unk54 = arg0->unk0->unk40->unk14;
    arg0->unk58.f = arg0->unk2C;
    arg0->unk5C = arg0->unk1E;
    arg0->unk5D = 1;
    arg0->unk5E = 0;
    arg0->unk1E = 10;
    func_802313DC(arg0->unk0, 0x10);
    func_8026C51C(0x174, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
}

void func_80289EB8(UnkStruct_80288040 *arg0) {
    f32 v;

    v = arg0->unk2C;
    arg0->unk50.f = v;
    arg0->unk58.b[0] = arg0->unk1F;
    arg0->unk54 = 300.0f;
    arg0->unk1F = 0;
    arg0->unk2C = 2.0f * v;
    func_80231408(arg0->unk0, 0x100);
}

void func_80289EA0(UnkStruct_80288040 *arg0) {
    arg0->unk0->unk30 = 0x21;
    arg0->unk50.f = 0.0f;
}

void func_80289E6C(UnkStruct_80288040 *arg0) {
    f32 v = arg0->unk2C;

    arg0->unk58.b[0] = arg0->unk1F;
    arg0->unk1F = 0;
    arg0->unk54 = 300.0f;
    arg0->unk50.f = v;
    arg0->unk2C = v * 3.0f;
}

void func_80289E64(UnkStruct_80288040 *arg0) {
}

void func_80289E24(UnkStruct_80288040 *arg0) {
    func_8026C51C(0x16B, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
}

void func_80289DB8(UnkStruct_80288040 *arg0) {
    Vec3f player;

    func_80250338(func_80243DDC(), &player);
    func_80283B04(arg0, &player);
    arg0->unk0->unk40->unk20 = func_8028322C(arg0);
    arg0->unk50.b[1] = arg0->unk1C;
    arg0->unk54 = arg0->unk2C;
    arg0->unk2C = 0.0f;
}

void func_80289DB0(UnkStruct_80288040 *arg0) {
}

void func_80289D7C(UnkStruct_80288040 *arg0) {
    arg0->unk2C = arg0->unk50.f;
    arg0->unk1F = arg0->unk58.b[0];
    func_802313DC(arg0->unk0, 0x100);
}

void func_80289D00(UnkStruct_80288040 *arg0) {
    arg0->unk1E = arg0->unk5C;
    arg0->unk0->unk40->unk1C = 0.0f;
    arg0->unk0->unk40->unk24 = 0.0f;
    func_80231408(arg0->unk0, 0x10);
    if (arg0->unk1E != 0) {
        func_8028301C(arg0, 3, 2.0f, 0.0f, 0.0f);
    }
}

void func_80289CCC(UnkStruct_80288040 *arg0) {
    arg0->unk2C = arg0->unk50.f;
    arg0->unk1F = arg0->unk58.b[0];
    func_802313DC(arg0->unk0, 0x100);
}

void func_80289C80(UnkStruct_80288040 *arg0) {
    arg0->unk0->unk30 = 1;
    arg0->unk0->unk40->unk28 = 1.0f;
    arg0->unk0->unk40->unk2C = 1.0f;
    arg0->unk0->unk40->unk30 = 1.0f;
}

void func_80289C6C(UnkStruct_80288040 *arg0) {
    arg0->unk2C = arg0->unk50.f;
    arg0->unk1F = arg0->unk58.b[0];
}

void func_80289C64(UnkStruct_80288040 *arg0) {
}

void func_80289C5C(UnkStruct_80288040 *arg0) {
}

void func_80289C50(UnkStruct_80288040 *arg0) {
    arg0->unk2C = arg0->unk54;
}

void func_80289C48(UnkStruct_80288040 *arg0) {
}

/* Counts unk4C up: 1 once it reaches `limit`. */
static void func_80288C00() {
}

static s32 func_80288C08(UnkStruct_80288040 *arg0, f32 limit) {
    func_80288C00();
    if (++arg0->unk4C >= limit) {
        return 1;
    }
    return 0;
}

s32 func_80289C00(UnkStruct_80288040 *arg0) {
    return !func_80288C08(arg0, arg0->unk54);
}

/* Moves the object's height towards `y` at `speed`: 1 once there. */
static s32 func_802895D4(UnkStruct_80288040 *arg0, f32 y, f32 speed) {
    s32 done = 0;
    f32 s68 = arg0->unk0->unk68;
    f32 s6C = arg0->unk0->unk6C;
    f32 s70 = arg0->unk0->unk70;
    f32 floor = func_8026E938(arg0->unk0->unk40);

    arg0->unk0->unk70 = 0.0f;
    if (floor != 20000.0f && y < floor) {
        y = floor;
    }
    if (arg0->unk0->unk40->unk14 < y) {
        arg0->unk0->unk68 = speed;
        arg0->unk0->unk6C = 0.0f;
        func_80230914(arg0->unk0);
        if (y < arg0->unk0->unk40->unk14) {
            arg0->unk0->unk40->unk14 = y;
            done = 1;
        }
    } else if (y < arg0->unk0->unk40->unk14) {
        arg0->unk0->unk68 = 0.0f;
        arg0->unk0->unk6C = speed;
        func_80230914(arg0->unk0);
        if (arg0->unk0->unk40->unk14 < y) {
            arg0->unk0->unk40->unk14 = y;
            done = 1;
        }
    } else {
        arg0->unk0->unk40->unk14 = y;
        done = 1;
    }
    arg0->unk0->unk68 = s68;
    arg0->unk0->unk6C = s6C;
    arg0->unk0->unk70 = s70;
    return done;
}

static void func_80289750() {
}

static void func_80289758(UnkStruct_80288040 *arg0, f32 angle, f32 speed) {
    s32 dir;

    func_80289750();
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    if (angle >= 0.0f && angle < 22.5f) {
        dir = 0x80;
        goto done;
    }
    if (angle >= 22.5f && angle < 67.5f) {
        dir = 0x60;
        goto done;
    }
    if (angle >= 67.5f && angle < 112.5f) {
        dir = 0x40;
        goto done;
    }
    if (angle >= 112.5f && angle < 157.5f) {
        dir = 0x20;
        goto done;
    }
    if (angle >= 157.5f && angle < 202.5f) {
        dir = 0;
        goto done;
    }
    if (angle >= 202.5f && angle < 247.5f) {
        dir = 0xE0;
        goto done;
    }
    if (angle >= 247.5f && angle < 292.5f) {
        dir = 0xC0;
        goto done;
    }
    if (angle >= 292.5f && angle < 337.5f) {
        dir = 0xA0;
        goto done;
    }
    dir = 0x80;
done:
    func_80291944(arg0->unk0, dir, speed);
}

s32 func_80289760(UnkStruct_80288040 *arg0) {
    Vec3f pos;

    if (arg0->unk50.f + 600.0f < arg0->unk54 || arg0->unk54 + 600.0f < arg0->unk50.f || arg0->unk5E++ > 150) {
        return 0;
    }
    pos.x = arg0->unk0->unk40->unk10;
    pos.y = arg0->unk0->unk40->unk14;
    pos.z = arg0->unk0->unk40->unk18;
    func_80232DB4(arg0->unk0);
    arg0->unk0->unk40->unk20 = arg0->unk64;
    func_80289758(arg0, arg0->unk64, arg0->unk58.f);
    switch (arg0->unk5D) {
        case 1:
            if (func_802895D4(arg0, arg0->unk50.f, arg0->unk58.f)) {
                arg0->unk5D = 2;
                arg0->unk58.f = arg0->unk2C;
            } else {
                arg0->unk58.f += 0.3f;
            }
            arg0->unk0->unk40->unk1C = 90.0f - arg0->unk60;
            break;
        case 2:
            if (func_802895D4(arg0, arg0->unk54, arg0->unk58.f)) {
                arg0->unk5D = 3;
            } else {
                arg0->unk58.f += 0.15f;
            }
            arg0->unk0->unk40->unk1C = arg0->unk60 + -90.0f;
            break;
    }
    if (func_80232D18(arg0->unk0, 0x10)) {
        arg0->unk0->unk40->unk10 = pos.x;
        arg0->unk0->unk40->unk14 = pos.y;
        arg0->unk0->unk40->unk18 = pos.z;
        return 0;
    }
    return arg0->unk5D != 3;
}

s32 func_80289464(UnkStruct_80288040 *arg0) {
    UnkStruct_8023A840 *g = func_8023A840();
    s32 n = arg0->unk4C;

    switch (D_800BA8EA[arg0->unk84].unk0) {
        case 0xEC:
            if (g->unk10 == 0) {
                if (n % 25 == 0) {
                    func_8026C51C(0x176, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
                }
            } else if (n % 13 == 0) {
                func_8026C51C(0x176, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
            }
            break;
        case 0xE0:
        case 0xFE:
            if (g->unk10 == 0) {
                if (n % 16 == 0) {
                    func_8026C51C(0x173, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
                }
            } else if (n % 8 == 0) {
                func_8026C51C(0x173, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
            }
            break;
    }
    return !func_80288C08(arg0, arg0->unk54);
}

s32 func_80289320(UnkStruct_80288040 *arg0) {
    if (arg0->unk50.f < 12.0f) {
        arg0->unk0->unk40->unk28 -= (1.0 - 0.7) / 12;
    } else if (arg0->unk50.f < 22.0f) {
        arg0->unk0->unk40->unk28 += (1.0 - 0.7) / 10;
    } else if (arg0->unk50.f < 34.0f) {
        arg0->unk0->unk40->unk30 -= (1.0 - 0.7) / 12;
    } else if (arg0->unk50.f < 45.0f) {
        arg0->unk0->unk40->unk30 += (1.0 - 0.7) / 11;
    } else {
        arg0->unk50.f = 0.0f;
        return 0;
    }
    arg0->unk50.f += 0.8f;
    return 1;
}

s32 func_80289294(UnkStruct_80288040 *arg0) {
    s32 n;

    if (D_800BA8EA[arg0->unk84].unk0 == 0xE8 && (n = arg0->unk4C) % 25 == 0) {
        func_8026C51C(0x169, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
    }
    return !func_80288C08(arg0, arg0->unk54);
}

s32 func_8028924C(UnkStruct_80288040 *arg0) {
    return !func_80288C08(arg0, 180.0f);
}

s32 func_802890CC(UnkStruct_80288040 *arg0) {
    s32 i;
    UnkStruct_80288040 *obj;

    for (i = 0; i < 2; i++) {
        obj = func_802867E4(arg0->unk84, arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14, arg0->unk0->unk40->unk18);
        if (obj != NULL) {
            obj->unk0->unk40->unk28 = 0.65f;
            obj->unk0->unk40->unk2C = 0.65f;
            obj->unk0->unk40->unk30 = 0.65f;
            obj->unk3C = 0;
            obj->unk3D = 0;
            obj->unk2C *= 1.5f;
            func_80282430(obj, 15, 3);
            obj->unk6E = 60;
            obj->unk78 = 1;
            obj->unk30 = 1;
            obj->unk0->unk68 = 20.0f;
            obj->unk0->unk6C = 0.8f;
            obj->unk0->unk70 = 0.8f;
            func_8023903C(5);
        }
    }
    return 0;
}

s32 func_80288C40(UnkStruct_80288040 *arg0) {
    s32 k;
    Vec3f v;
    f32 x;
    f32 z;
    s32 i;
    UnkStruct_800BC9F0 *e;

    for (i = 0; i < D_802A1B70; i++) {
        e = &D_800BC9F0[i];
        k = D_800BA8EA[arg0->unk84].unk0;
        if (k == e->unk0 + 0xDE) {
            if (e->unk1 == arg0->unk4C) {
                v.x = e->pos.x;
                v.y = e->pos.y;
                v.z = e->pos.z;
                x = v.x;
                z = v.z;
                switch (arg0->unk50.b[1]) {
                    case 0x80:
                        v.x = arg0->unk0->unk40->unk10 + x;
                        v.z = arg0->unk0->unk40->unk18 + z;
                        break;
                    case 0x60:
                        v.x = arg0->unk0->unk40->unk10 + x * 0.707106781 + z * 0.707106781;
                        v.z = arg0->unk0->unk40->unk18 + z * 0.707106781 - x * 0.707106781;
                        break;
                    case 0x40:
                        v.x = arg0->unk0->unk40->unk10 + z;
                        v.z = arg0->unk0->unk40->unk18 - x;
                        break;
                    case 0x20:
                        v.x = arg0->unk0->unk40->unk10 - x * 0.707106781 + z * 0.707106781;
                        v.z = arg0->unk0->unk40->unk18 - z * 0.707106781 - x * 0.707106781;
                        break;
                    case 0x00:
                        v.x = arg0->unk0->unk40->unk10 - x;
                        v.z = arg0->unk0->unk40->unk18 - z;
                        break;
                    case 0xE0:
                        v.x = arg0->unk0->unk40->unk10 - x * 0.707106781 - z * 0.707106781;
                        v.z = arg0->unk0->unk40->unk18 - z * 0.707106781 + x * 0.707106781;
                        break;
                    case 0xC0:
                        v.x = arg0->unk0->unk40->unk10 - z;
                        v.z = arg0->unk0->unk40->unk18 + x;
                        break;
                    case 0xA0:
                        v.x = arg0->unk0->unk40->unk10 + x * 0.707106781 - z * 0.707106781;
                        v.z = arg0->unk0->unk40->unk18 + z * 0.707106781 + x * 0.707106781;
                        break;
                }
                v.y += arg0->unk0->unk40->unk14;
                func_8028E8A4(arg0->unk50.b[0], v.x, v.y, v.z, (arg0->unk50.b[1] >> 5) + 1);
            } else if (arg0->unk4C >= e->unk2) {
                return 0;
            }
            arg0->unk4C++;
            return 1;
        }
    }
    if (arg0->unk4C == 0) {
        func_8028E8A4(arg0->unk50.b[0], arg0->unk0->unk40->unk10, arg0->unk0->unk40->unk14,
                      arg0->unk0->unk40->unk18, (arg0->unk50.b[1] >> 5) + 1);
    }
    if (0) { D_802A1B70 = (s32) &v; }
    if (func_80288C08(arg0, 180.0f)) {
        return 0;
    }
    return 1;
}

s32 func_80288BF4(UnkStruct_80288040 *arg0) {
    return 0;
}

s32 func_80288BE8(UnkStruct_80288040 *arg0) {
    return 0;
}

/* 2 if (pos, pos2) is within reach*100 of (center, center2) on both axes
 * (reach2 for the second), 1 if only on the first, else 0. */
static s32 func_802884D4(f32 reach, f32 center, f32 pos, f32 reach2, f32 center2, f32 pos2) {
    s32 ret = 0;

    if (pos <= center + reach * 100.0f && center - reach * 100.0f <= pos) {
        ret = 1;
        if (pos2 <= center2 + reach2 * 100.0f && center2 - reach2 * 100.0f <= pos2) {
            ret = 2;
        }
    } else {
        ret = 0;
    }
    return ret;
}

static s32 func_8028854C(UnkStruct_80288040 *arg0, f32 reach) {
    Vec3f player;

    func_80250338(func_80243DDC(), &player);
    if (func_802884D4(reach, arg0->unk0->unk40->unk10, player.x, 0.75f, arg0->unk0->unk40->unk18, player.z)
        && func_802884D4(reach, arg0->unk0->unk40->unk18, player.z, 0.75f, arg0->unk0->unk40->unk10, player.x)) {
        return 1;
    }
    return 0;
}

static f32 func_8028863C(f32 a, f32 b) {
    if (a < b) {
        a = b - a;
    } else {
        a = a - b;
    }
    return a;
}

static s32 func_802885E4(UnkStruct_80288040 *arg0, f32 reach, f32 dx, f32 dz) {
    s32 ret = 0;

    if (func_8028854C(arg0, reach)) {
        if (((dz < dx) ? dx - dz : dz - dx) < 50.0f) {
            ret = 1;
        }
    }
    return ret;
}

s32 func_80288B7C(UnkStruct_80288040 *arg0) {
    return func_8028854C(arg0, 1.5f);
}

s32 func_80288B10(UnkStruct_80288040 *arg0) {
    return func_8028854C(arg0, 3.0f);
}

static void func_80288634() {
}

static s32 func_80288644(UnkStruct_80288040 *arg0, f32 px, f32 pz) {
    s32 ret;
    f32 x;
    f32 z;

    func_80288634();
    ret = 0;
    switch (arg0->unk1C) {
        case 0x00:
            z = arg0->unk0->unk40->unk18;
            if (pz < z
                && func_802884D4(8.0f, z, pz, 0.75f, arg0->unk0->unk40->unk10, px) == 2) {
                ret = 1;
            }
            break;
        case 0x20:
            if (0) { func_8028863C(px, x); }
            if (pz < (z = arg0->unk0->unk40->unk18) && (x = arg0->unk0->unk40->unk10) < px
                && func_802885E4(arg0, 8.0f, (px < (x = arg0->unk0->unk40->unk10)) ? x - px : px - x, func_8028863C(pz, z = arg0->unk0->unk40->unk18))) {
                ret = 1;
            }
            break;
        case 0x40:
            x = arg0->unk0->unk40->unk10;
            if (x < px
                && func_802884D4(8.0f, x, px, 0.75f, arg0->unk0->unk40->unk18, pz) == 2) {
                ret = 1;
            }
            break;
        case 0x60:
            if (0) { func_8028863C(px, x); }
            if ((z = arg0->unk0->unk40->unk18) < pz && (x = arg0->unk0->unk40->unk10) < px
                && func_802885E4(arg0, 8.0f, (px < (x = arg0->unk0->unk40->unk10)) ? x - px : px - x, func_8028863C(pz, z = arg0->unk0->unk40->unk18))) {
                ret = 1;
            }
            break;
        case 0x80:
            z = arg0->unk0->unk40->unk18;
            if (z < pz
                && func_802884D4(8.0f, z, pz, 0.75f, arg0->unk0->unk40->unk10, px) == 2) {
                ret = 1;
            }
            break;
        case 0xA0:
            if (0) { func_8028863C(px, x); }
            if ((z = arg0->unk0->unk40->unk18) < pz && px < (x = arg0->unk0->unk40->unk10)
                && func_802885E4(arg0, 8.0f, (px < (x = arg0->unk0->unk40->unk10)) ? x - px : px - x, func_8028863C(pz, z = arg0->unk0->unk40->unk18))) {
                ret = 1;
            }
            break;
        case 0xC0:
            x = arg0->unk0->unk40->unk10;
            if (px < x
                && func_802884D4(8.0f, x, px, 0.75f, arg0->unk0->unk40->unk18, pz) == 2) {
                ret = 1;
            }
            break;
        case 0xE0:
            if (0) { func_8028863C(px, x); }
            if (pz < (z = arg0->unk0->unk40->unk18) && px < (x = arg0->unk0->unk40->unk10)
                && func_802885E4(arg0, 8.0f, (px < (x = arg0->unk0->unk40->unk10)) ? x - px : px - x, func_8028863C(pz, z = arg0->unk0->unk40->unk18))) {
                ret = 1;
            }
            break;
    }
    return ret;
}

s32 func_80288654(UnkStruct_80288040 *arg0) {
    Vec3f player;

    func_80250338(func_80243DDC(), &player);
    return func_80288644(arg0, player.x, player.z);
}

s32 func_802884C8(UnkStruct_80288040 *arg0) {
    return 1;
}

s32 func_802884BC(UnkStruct_80288040 *arg0) {
    return 0;
}

void func_802883B0(void) {
    struct UnkStruct_80225CC0 *file;
    u8 buf[200];
    s32 i;
    s32 j;
    s16 t;

    file = func_80226604(0x10B, 1);
    func_8022616C(buf, 1, func_802266DC(file), file);
    func_80226368(file);
    D_802A1B70 = buf[0];
    j = 1;
    for (i = 0; i < D_802A1B70; i++) {
        D_800BC9F0[i].unk0 = buf[j++];
        D_800BC9F0[i].unk1 = buf[j++];
        t = buf[j++] << 8;
        t |= buf[j++];
        D_800BC9F0[i].pos.x = (s16) t;
        t = buf[j++] << 8;
        t |= buf[j++];
        D_800BC9F0[i].pos.y = (s16) t;
        t = buf[j++] << 8;
        t |= buf[j++];
        D_800BC9F0[i].pos.z = (s16) t;
        D_800BC9F0[i].unk2 = buf[j++];
    }
}

static s32 func_80288190(UnkStruct_80288040 *arg0);
static s32 func_80288198(UnkStruct_80288040 *arg0);

static s32 func_80288198(UnkStruct_80288040 *arg0) {
    if (++arg0->unk4C >= 30) {
        return 1;
    }
    return 0;
}

void func_8028805C(UnkStruct_80288040 *arg0);

void func_802881A0(UnkStruct_80288040 *arg0) {
    Vec3f player;

    switch (arg0->unk48) {
        case 0:
            func_80250338(func_80243DDC(), &player);
            if (func_8026EE18(player.y) == func_8026EE18(arg0->unk0->unk40->unk14) || (arg0->unk24 & 1) || (arg0->unk24 & 8)) {
                if (D_802A1B74[arg0->unk3D](arg0)) {
                    arg0->unk48 = 1;
                }
            }
            break;
        case 1:
            if (func_80288190(arg0)) {
                arg0->unk48 = 2;
                arg0->unk4C = 0;
                arg0->unk0->unk40->unk20 = func_8028322C(arg0);
                arg0->unk1C &= 0xFFFE;
                if (arg0->unk3C != 5) {
                    func_80282430(arg0, 15, 2);
                    func_80229E38(arg0->unk0->unk40, 2, 0);
                    arg0->unk0->unk40->unk48->unk4->unk4 = 0.0f;
                }
                D_802A1BB0[arg0->unk3C](arg0);
            }
            break;
        case 2:
            if (!D_802A1B8C[arg0->unk3C](arg0)) {
                func_8028805C(arg0);
            }
            break;
        case 3:
            if (func_80288198(arg0)) {
                arg0->unk48 = 0;
                func_8028805C(arg0);
            }
            break;
    }
}

static s32 func_80288190(UnkStruct_80288040 *arg0) {
    if (arg0->unk6E != 0) {
        return 0;
    }
    return 1;
}

void func_8028805C(UnkStruct_80288040 *arg0) {
    if (arg0->unk48 == 2) {
        if (arg0->unk3C != 5) {
            func_80282454(arg0);
        }
        D_802A1BD4[arg0->unk3C](arg0);
    }
    arg0->unk48 = 0;
    arg0->unk4C = 0;
    if (arg0->unk1F >= 40) {
        arg0->unk4 = (arg0->unk0->unk40->unk10 + 50.0f) * 0.01;
        arg0->unk8 = func_8026EE18(arg0->unk0->unk40->unk14);
        arg0->unkC = (arg0->unk0->unk40->unk18 + 50.0f) * 0.01;
    }
}

void func_80288040(UnkStruct_80288040 *arg0) {
    if (arg0->unk48 == 0) {
        arg0->unk48 = 1;
    }
}
