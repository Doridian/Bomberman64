/*
 * NON_MATCHING: ovl_0D_05's stage object, complete: every function and its data.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 120, eu 120, jp 120
 *
 * What still differs in us (words):
 * - func_ovl0D_05_80043018 (6): a fake `if (!D_ovl0D_05_8004614C) {}`
 *   after the store to D_8004617C keeps the loads of D_80046170[0]/[2]
 *   after it, as in the original, but the call's argument is reloaded
 *   (`lw a0,0(v1)`) where the original moves it from v0.
 * - func_ovl0D_05_80043790 (109): the camera (ZeroJump 0x171A): the
 *   original puts 1600.0f in $f16 and copies it to $f14 and a3; ours loads
 *   it into $f14. One word long, so the rest is shifted.
 * - func_ovl0D_05_80044290 (5): a local 4 bytes higher (sp+172, not 168).
 */
#include "common.h"

/*
 * ovl_0D_05's stage object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse; docs/DECOMPILING.md).
 */

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10[0x20];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ UnkStructA_40 *unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ u8 unk50[4];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 unk58[0x10];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
} Obj05;

/* a model placed on the stage: the object, its collision handle, its model
 * id, its collision box, and its position (in tiles), angles and scale */
typedef struct {
    /* 0x00 */ Obj05 *obj;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
} Ent05;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Trio05;

typedef struct {
    f32 x, y, z, w;
} Vec4f05;

void func_ovl0D_05_80044BF8(s32); /* 0xC00 */
void func_ovl0D_05_80044C08(s32 *); /* 0xC02 */
void func_ovl0D_05_80044C38(s32, s32, s32, s32, s32, s32); /* 0xD05 */
void func_ovl0D_05_80044C50(f32, f32, f32, s32 *, s32); /* 0xD08 */
void func_ovl0D_05_80044C70(s32); /* 0xD0C */
void func_ovl0D_05_80044C78(void); /* 0xD0D */
void func_ovl0D_05_80044CC0(s32); /* 0xD16 */
s32 func_ovl0D_05_80044CC8(s32); /* 0xE00 */
void func_ovl0D_05_80044CD0(s32, s32, s32, s32, s32, s32, s32, s32); /* 0xE01 */
void func_ovl0D_05_80044CE0(void (*)(Obj05 *)); /* 0xE03 */
void func_ovl0D_05_80044CF0(s32, s32, s32); /* 0xF00 */
s32 func_ovl0D_05_80044CF8(void); /* 0xF01 */
void func_ovl0D_05_80044D40(s32); /* 0xF0A */
s32 *func_ovl0D_05_80044D48(void); /* 0xF0B */
void func_ovl0D_05_80044DA8(void); /* 0x1000 */
void func_ovl0D_05_80044DB0(s32, s32, s32); /* 0x1001 */
void func_ovl0D_05_80044DB8(void *); /* 0x1002 */
s32 func_ovl0D_05_80044DC0(s32, s32, s32, s32); /* 0x1003 */
s32 func_ovl0D_05_80044DD8(void); /* 0x1006 */
void func_ovl0D_05_80044DE0(s32, void *); /* 0x1007 */
void func_ovl0D_05_80044DE8(s32); /* 0x1008 */
void func_ovl0D_05_80044DF0(s32); /* 0x1009 */
void func_ovl0D_05_80044DF8(s32, s32, f32, s32, s32, s32, s32); /* 0x100A */
void func_ovl0D_05_80044E08(void); /* 0x100C */
s32 func_ovl0D_05_80045340(UnkStructA_40 *, s32, s32, s32, s32, s32); /* 0x150D */
void func_ovl0D_05_80045348(s32); /* 0x150E */
void func_ovl0D_05_80045438(f32, f32, f32); /* 0x1704 */
void func_ovl0D_05_80045458(f32, f32, f32); /* 0x1708 */
void func_ovl0D_05_80045460(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0D_05_800454E8(f32, f32, f32, f32); /* 0x171A */
void func_ovl0D_05_800454F8(f32, f32, f32, f32); /* 0x171C */
void func_ovl0D_05_80045510(s32); /* 0x171F */
void func_ovl0D_05_80045520(f32, f32, f32); /* 0x1721 */
void func_ovl0D_05_80045588(f32 *, f32 *, f32 *); /* 0x1803 */
void func_ovl0D_05_80045590(f32 *, f32 *); /* 0x1804 */
s32 func_ovl0D_05_800455A8(Obj05 *, s32); /* 0x1807 */
void func_ovl0D_05_800455C8(Obj05 *, s32); /* 0x180B */
void func_ovl0D_05_800455F8(Obj05 *, s32); /* 0x1811 */
void func_ovl0D_05_80045600(Obj05 *, s32); /* 0x1812 */
void func_ovl0D_05_80045610(Obj05 *); /* 0x1814 */
Obj05 *func_ovl0D_05_80045618(s32, s32, s32, s32, s32); /* 0x1815 */
Obj05 *func_ovl0D_05_80045620(s32, s32, s32, s32); /* 0x1816 */
Obj05 *func_ovl0D_05_80045630(Obj05 *); /* 0x1818 */
Obj05 *func_ovl0D_05_80045640(s32, s32, f32, f32, f32); /* 0x181A */
s32 func_ovl0D_05_80045670(Obj05 *, f32 *, f32 *, f32 *); /* 0x1820 */
void func_ovl0D_05_800456C8(Obj05 *, f32 *); /* 0x182B */
void func_ovl0D_05_80045748(void (*)(void), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0D_05_80045758(void); /* 0x1902 */
void func_ovl0D_05_80045768(s32); /* 0x1904 */
void *func_ovl0D_05_80045770(void); /* 0x1905 */
void func_ovl0D_05_80045790(void); /* 0x1909 */
f32 func_ovl0D_05_800458F0(f32); /* 0x1D00 */
f64 func_ovl0D_05_80045900(void); /* 0x1D02 */
s32 func_ovl0D_05_80045908(s32); /* 0x1D03 */
void func_ovl0D_05_800459C0(s32); /* 0x1E06 */
s32 func_ovl0D_05_800459D0(s32); /* 0x1E08 */
void func_ovl0D_05_80045A70(s32, s32, s32); /* 0x2101 */
void func_ovl0D_05_80045A90(s32); /* 0x2200 */
void func_ovl0D_05_80045AB0(u32 (*)[3]); /* 0x2300 */
void func_ovl0D_05_80045AC8(u32 (*)[3]); /* 0x2303 */
void func_ovl0D_05_80045BA0(s32, f32 *, s32); /* 0x2601 */
void func_ovl0D_05_80045C58(s32, s32, s32); /* 0x2A00 */
void func_ovl0D_05_80045CF0(s32, f32, f32, f32); /* 0x2B04 */
void func_ovl0D_05_80045CF8(s32, f32 *); /* 0x2B05 */

void func_ovl0D_05_80043010(void);
void func_ovl0D_05_80043018(void);
void func_ovl0D_05_800430CC(void);
void func_ovl0D_05_80043124(void);
void func_ovl0D_05_80043210(void);
void func_ovl0D_05_800432F4(void);
void func_ovl0D_05_80043324(void);
void func_ovl0D_05_8004338C(f32);
void func_ovl0D_05_800433D4(void);
void func_ovl0D_05_80043484(void);
void func_ovl0D_05_800434FC(void);
void func_ovl0D_05_80043768(void);
void func_ovl0D_05_80043790(void);
void func_ovl0D_05_80043A94(s32);
void func_ovl0D_05_80043C78(Obj05 *);
void func_ovl0D_05_80043CBC(Obj05 *, s32, s32, f32, f32);
void func_ovl0D_05_80043D94(s32, Obj05 *);
void func_ovl0D_05_80043DC8(void);
void func_ovl0D_05_80043EC4(void);
void func_ovl0D_05_80044290(void);
void func_ovl0D_05_80044814(f32, f32, f32);

static void func_ovl0D_05_8004311C(void);
static void func_ovl0D_05_800448A8(void);
static void func_ovl0D_05_800448A0(void);
static void func_ovl0D_05_80044898(void);
static void func_ovl0D_05_80044890(void);
static void func_ovl0D_05_80044888(void);
static void func_ovl0D_05_80044880(void);
static void func_ovl0D_05_80044878(void);
static void func_ovl0D_05_80044870(void);
static void func_ovl0D_05_80044288(Ent05 *, s32 *);
static void func_ovl0D_05_80044280(Ent05 *, s32);
static void func_ovl0D_05_80043788(void);
static void func_ovl0D_05_80043780(Trio05 *, s32);
static void func_ovl0D_05_80043760(void);
static void func_ovl0D_05_80043758(void);
static void func_ovl0D_05_80043750(void);
static void func_ovl0D_05_80043524(void);
static void func_ovl0D_05_800432EC(void);
static void func_ovl0D_05_80043208(void);
static void func_ovl0D_05_80043200(void);
static void func_ovl0D_05_800431F8(void);
static void func_ovl0D_05_800430C4(void);
static void func_ovl0D_05_800430BC(void);
static void func_ovl0D_05_8004317C(Ent05 *);
static void func_ovl0D_05_8004352C(Ent05 *);
static void func_ovl0D_05_800435D0(Ent05 *);

#define UNK_MACRO_ovl0D_05_800430CC() \
    D_ovl0D_05_8004614C = func_ovl0D_05_80044DD8(); func_ovl0D_05_80044DB8(&D_ovl0D_05_80046140); func_ovl0D_05_80044DE0(D_ovl0D_05_8004614C, &D_ovl0D_05_80046130)

/* .bss */
Vec4f05 D_ovl0D_05_80046130;
Vec3f D_ovl0D_05_80046140;
s32 D_ovl0D_05_8004614C;
u8 D_ovl0D_05_80046150[0x4]; /* unused (func_ovl0D_05_800448A8) */
s32 D_ovl0D_05_80046154;
s32 D_ovl0D_05_80046158;
u8 D_ovl0D_05_8004615C[0x4]; /* unused (func_ovl0D_05_800448A8) */
Vec3f D_ovl0D_05_80046160;
Obj05 *D_ovl0D_05_8004616C;
s32 D_ovl0D_05_80046170[3];
s32 D_ovl0D_05_8004617C;
s32 *D_ovl0D_05_80046180;

/* .data */
/* passed to func_ovl0D_05_80045AB0: three 12-byte records */
u32 D_ovl0D_05_80045EF0[][3] = {
    { 0x9A0002, 0x6000E, 4 },
    { 0x990002, 0xE, 4 },
    { 0x970001, 0xF, 0x2004 },
};
/* passed to func_ovl0D_05_80045AC8 */
u32 D_ovl0D_05_80045F14[][3] = {
    { 0, 4, 0 },
    { 4, 0x980000, 0x84 },
};
Ent05 D_ovl0D_05_80045F2C[1] = {
    { NULL, -1, 0x153, 0, 0x400, 0x20, 0x400, -300.0f, 60.0f, 60.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent05 D_ovl0D_05_80045F64[2] = {
    { NULL, -1, 0x14B, 0, 0x400, 0x20, 0x400, 10.0f, 20.0f, 290.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x14B, -1, -1, -1, -1, 0.0f, 60.0f, 140.0f, 0.0f, 90.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
Ent05 D_ovl0D_05_80045FD4[3] = {
    { NULL, -1, 0x161, -1, -1, -1, -1, 400.0f, 40.0f, 240.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x161, -1, -1, -1, -1, 230.0f, 80.0f, 190.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x161, -1, -1, -1, -1, 130.0f, 60.0f, 270.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
/* the flags set once each of D_ovl0D_05_80045FD4 is done */
s32 D_ovl0D_05_8004607C[3] = { 0x40F, 0x410, 0x411 };
Trio05 D_ovl0D_05_80046088[5] = {
    { 0, 7, 0xE5 },
    { 1, 9, 0xE7 },
    { 2, 9, 0xE7 },
    { 3, 0, 0xDE },
    { 4, 2, 0xE0 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0D_05_800448A8(void) {
    D_ovl0D_05_80046150[0] = D_ovl0D_05_8004615C[0];
}

static void func_ovl0D_05_800448A0(void) {
}

static void func_ovl0D_05_80044898(void) {
}

static void func_ovl0D_05_80044890(void) {
}

static void func_ovl0D_05_80044888(void) {
}

static void func_ovl0D_05_80044880(void) {
}

static void func_ovl0D_05_80044878(void) {
}

static void func_ovl0D_05_80044870(void) {
}

void func_ovl0D_05_80044814(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0D_05_80045438(D_ovl0D_05_80046160.x, D_ovl0D_05_80046160.y, D_ovl0D_05_80046160.z);
    func_ovl0D_05_80045458(arg0, arg1, arg2);
    func_ovl0D_05_80045768(180);
}

/* the task of each of D_ovl0D_05_80045FD4 (its index is the argument) */
void func_ovl0D_05_80044290(void) {
    s32 idx;
    Ent05 *e;
    s32 flag;
    Vec3f pos;
    s32 grid[6];
    s32 cnt;
    s32 r;
    f32 ang;
    Vec3f tgt;
    s32 pad;
    s32 timer;

    idx = (s32) func_ovl0D_05_80045770();
    e = &D_ovl0D_05_80045FD4[idx];
    flag = D_ovl0D_05_8004607C[idx];
    pos.x = e->unk14 * 10.0f + 150.0f;
    pos.y = e->unk18 * 10.0f;
    pos.z = e->unk1C * 10.0f + 150.0f;
    cnt = 0;
    timer = 240 / (idx + 1);
    func_ovl0D_05_80044C50(pos.x, pos.y, pos.z, grid, 0);
    while (func_ovl0D_05_800459D0(flag) == 0) {
        if (e->obj == NULL) {
            break;
        }
        e->obj->unk40->unk10 = pos.x;
        e->obj->unk40->unk18 = pos.z;
        tgt.x = D_ovl0D_05_80046130.x;
        tgt.y = pos.y;
        tgt.z = D_ovl0D_05_80046130.z;
        func_ovl0D_05_80045588(&pos.x, &tgt.x, &ang);
        e->obj->unk40->unk20 = ang;
        if (func_ovl0D_05_800459D0(0x424) != 0) {
            func_ovl0D_05_80044288(e, &timer);
        }
        if (idx == (cnt >> 2)) {
            cnt = 0;
            r = func_ovl0D_05_800455A8(e->obj, 0x40);
            if (r & 0x40) {
                if ((r & 0x2000) || (r & 0x4000)) {
                    func_ovl0D_05_80044280(e, flag);
                } else {
                    func_ovl0D_05_80043D94(0x26, e->obj);
                }
            }
        }
        cnt++;
        func_ovl0D_05_80045790();
    }
    func_ovl0D_05_80045758();
}

/* a model's hit: it fades out, scattering debris, and its tiles become solid */
static void func_ovl0D_05_80044280(Ent05 *e, s32 flag) {
    s32 i;
    s32 k;
    Vec3f v;
    Obj05 *o;

    o = e->obj;
    k = 5;
    func_ovl0D_05_800455F8(o, 0x80000);
    func_ovl0D_05_80043D94(0x73, o);
    for (i = 0; i < 30; i++) {
        o->unk40->unk36 = (u8) ((1.0f - i / 30.0f) * 255.0f);
        if (++k >= 6) {
            k = 0;
            func_ovl0D_05_800456C8(o, &v.x);
            if (func_ovl0D_05_80045908(1) != 0) {
                v.x += 300.0 * func_ovl0D_05_80045900();
            } else {
                v.x -= 300.0 * func_ovl0D_05_80045900();
            }
            v.y += 100.0 + 300.0 * func_ovl0D_05_80045900();
            if (func_ovl0D_05_80045908(1) != 0) {
                v.z += 300.0 * func_ovl0D_05_80045900();
            } else {
                v.z -= 300.0 * func_ovl0D_05_80045900();
            }
            func_ovl0D_05_80045BA0(20, &v.x, 0);
        }
        func_ovl0D_05_80045790();
    }
    func_ovl0D_05_80045600(o, 0x01080000);
    func_ovl0D_05_8004352C(e);
    func_ovl0D_05_800459C0(flag);
}

/* every few seconds, when the player is near, the model throws a bomb */
static void func_ovl0D_05_80044288(Ent05 *e, s32 *timer) {
    UnkStructA_40 *p;
    s32 grid[6];

    if (*timer == 0) {
        p = e->obj->unk40;
        func_ovl0D_05_80044C50(p->unk10, p->unk14, p->unk18, grid, 0);
        if (func_ovl0D_05_80044DC0(grid[0] - 12, grid[2] - 12, grid[0] + 12, grid[2] + 12) != 0 &&
            func_ovl0D_05_80044DC0(grid[0] - 2, grid[2] - 2, grid[0] + 2, grid[2] + 2) == 0) {
            func_ovl0D_05_80045748(func_ovl0D_05_80043EC4, e, 0, 0, 0x110);
            func_ovl0D_05_80045520(10.0f, 10.0f, 10.0f);
            func_ovl0D_05_80045510(60);
        }
        *timer = (D_ovl0D_05_80046180[4] != 0) ? 240 : 360;
    } else {
        (*timer)--;
    }
}

/* the task a model's hit starts: a bomb flies from it to the player */
void func_ovl0D_05_80043EC4(void) {
    Vec3f tmp;
    Vec3f dir;
    Vec3f pos;
    Ent05 *e;
    Obj05 *o;
    Obj05 *o2;
    s32 n;
    f32 dx;
    f32 dz;

    e = func_ovl0D_05_80045770();
    o = func_ovl0D_05_80045618(0, 0, 0x01000210, 0x60, 0);
    o2 = func_ovl0D_05_80045630(o);
    o2->unk4C = 1.5f;
    o2->unk54 = 1.5f;
    o->unk40->unk30 = 1.5f;
    o->unk40->unk2C = 1.5f;
    o->unk40->unk28 = 1.5f;
    dir.x = e->obj->unk40->unk20;
    dir.y = 60.0f;
    dir.z = 500.0f;
    func_ovl0D_05_80045590(&dir.x, &pos.x);
    pos.x += e->obj->unk40->unk10;
    pos.y += e->obj->unk40->unk14;
    pos.z += e->obj->unk40->unk18;
    o->unk40->unk10 = pos.x;
    o->unk40->unk14 = pos.y;
    o->unk40->unk18 = pos.z;
    func_ovl0D_05_80045BA0(7, &pos.x, 0);
    func_ovl0D_05_80045BA0(14, &pos.x, 0);
    func_ovl0D_05_80045790();
    func_ovl0D_05_80045CF8(0x61, &pos.x);
    o->unk68 = 100.0f;
    o->unk70 = 1.2250001f;
    o->unk6C = 0.0f;
    o->unk74 = 1000.0f;
    n = 0;
    while ((D_ovl0D_05_80046130.y < o->unk40->unk14 || o->unk6C < o->unk68) && o->unk68 != 0.0f) {
        func_ovl0D_05_80045670(o, &o->unk68, &o->unk6C, &o->unk70);
        n++;
    }
    o->unk40->unk14 = pos.y;
    o->unk6C = 0.0f;
    o->unk68 = 100.0f;
    dx = (D_ovl0D_05_80046130.x - pos.x) / n;
    dz = (D_ovl0D_05_80046130.z - pos.z) / n;
    while (o->unk68 != 0.0f) {
        o->unk40->unk10 += dx;
        o->unk40->unk18 += dz;
        func_ovl0D_05_80045670(o, &o->unk68, &o->unk6C, &o->unk70);
        func_ovl0D_05_80045790();
    }
    func_ovl0D_05_80045600(o, 0x01000000);
    pos.x = o->unk40->unk10;
    pos.y = o->unk40->unk14 + 5.0f;
    pos.z = o->unk40->unk18;
    func_ovl0D_05_80045BA0(10, &pos.x, 0);
    func_ovl0D_05_80045CF8(0x62, &pos.x);
    func_ovl0D_05_80045610(o);
    func_ovl0D_05_80045758();
}

void func_ovl0D_05_80043DC8(void) {
    Obj05 *self;
    Obj05 *o;
    s32 i;
    s32 n;

    self = func_ovl0D_05_80045770();
    o = func_ovl0D_05_80045620(0x183, 0x11080000, 0xD0, 0);
    o->unk40->unk10 = self->unk40->unk10;
    o->unk40->unk14 = self->unk40->unk14;
    o->unk40->unk18 = self->unk40->unk18;
    n = 20;
    func_ovl0D_05_80043D94(0xB3, o);
    for (i = 0; i < n; i++) {
        func_ovl0D_05_80043CBC(o, i, 20, 2.0f, 4.0f);
        func_ovl0D_05_80045790();
    }
    func_ovl0D_05_80045610(o);
    func_ovl0D_05_80045758();
}

void func_ovl0D_05_80043D94(s32 arg0, Obj05 *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0D_05_80045CF0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0D_05_80043CBC(Obj05 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0D_05_800458F0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0D_05_800458F0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

/* the callback func_ovl0D_05_80043790 registers */
void func_ovl0D_05_80043C78(Obj05 *arg0) {
    func_ovl0D_05_80045600(arg0, 0x01000000);
    func_ovl0D_05_80045748(func_ovl0D_05_80043DC8, arg0, 0, 0, 0x150);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0D_05_80043A94(s32 arg0) {
    Ent05 *p;
    s32 i;

    switch (arg0) {
        case 2:
            func_ovl0D_05_80043790();
            break;
        case 17:
            func_ovl0D_05_80044DB0(4, 2, 0x17);
            break;
        case 18:
            func_ovl0D_05_80043484();
            break;
        case 4:
            func_ovl0D_05_800433D4();
            break;
        case 5:
            func_ovl0D_05_80043324();
            break;
        case 0x50:
            func_ovl0D_05_80043124();
            break;
        case 3:
            UNK_MACRO_ovl0D_05_800430CC();
            func_ovl0D_05_800459C0(0x424);
            break;
        case 12:
            if (D_ovl0D_05_80046154 == 0x3D) {
                func_ovl0D_05_80044DE8(1);
            }
            break;
        case 1:
            func_ovl0D_05_80043210();
            break;
    }
}

void func_ovl0D_05_80043768(void) {
    D_ovl0D_05_80046154 = -1;
    D_ovl0D_05_80046158 = -1;
}

void func_ovl0D_05_80043790(void) {
    s32 i;

    func_ovl0D_05_80045AB0(D_ovl0D_05_80045EF0);
    func_ovl0D_05_80045AC8(D_ovl0D_05_80045F14);
    func_ovl0D_05_80044BF8(0x13E);
    func_ovl0D_05_80043788();
    if (func_ovl0D_05_800459D0(0x409) != 0) {
        D_ovl0D_05_80046088[1].unk4 = 0x24;
        D_ovl0D_05_80046088[1].unk8 = 0xE8;
        D_ovl0D_05_80046088[2].unk4 = 0xB;
        D_ovl0D_05_80046088[2].unk8 = 0xE9;
    }
    func_ovl0D_05_80043780(D_ovl0D_05_80046088, 5);
    func_ovl0D_05_80044C70(0x144);
    func_ovl0D_05_80044DA8();
    func_ovl0D_05_80044C08(D_ovl0D_05_80046170);
    D_ovl0D_05_8004616C = func_ovl0D_05_80045640(-1, 0x80, 0.0f, 0.0f, 0.0f);
    D_ovl0D_05_8004616C->unkC = 0x3FFFF;
    func_ovl0D_05_80044D40(0);
    func_ovl0D_05_80045A90(1);
    func_ovl0D_05_80044CC0(0x201F);
    func_ovl0D_05_80044CE0(func_ovl0D_05_80043C78);
    func_ovl0D_05_80043768();
    D_ovl0D_05_80046180 = func_ovl0D_05_80044D48();
    func_ovl0D_05_800459C0(0x407);
    func_ovl0D_05_800454E8(2400.0f, 1600, 800.0f, 1600.0f);
    func_ovl0D_05_800454F8(1600.0f, 1600.0f, 3200.0f, 1600.0f);
    func_ovl0D_05_80043760();
    UNK_MACRO_ovl0D_05_800430CC();
    func_ovl0D_05_80043758();
    func_ovl0D_05_80043750();
    for (i = 0; i < 3; i++) {
        if (func_ovl0D_05_800459D0(D_ovl0D_05_8004607C[i]) == 0) {
            func_ovl0D_05_800435D0(&D_ovl0D_05_80045FD4[i]);
            func_ovl0D_05_800455F8(D_ovl0D_05_80045FD4[i].obj, 0x02000000);
            func_ovl0D_05_80045600(D_ovl0D_05_80045FD4[i].obj, 0x80000);
            func_ovl0D_05_800455C8(D_ovl0D_05_80045FD4[i].obj, 0xC0);
            D_ovl0D_05_80045FD4[i].obj->unk30 = 4;
            D_ovl0D_05_80045FD4[i].obj->unk34 = 200.0f;
            D_ovl0D_05_80045FD4[i].obj->unk38 = 300.0f;
            func_ovl0D_05_80045748(func_ovl0D_05_80044290, (void *) i, 0, 0, 0x110);
        } else {
            func_ovl0D_05_8004352C(&D_ovl0D_05_80045FD4[i]);
        }
    }
    func_ovl0D_05_80043524();
}

static void func_ovl0D_05_80043788(void) {
}

static void func_ovl0D_05_80043780(Trio05 *t, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0D_05_80045C58(t->unk0, t->unk4, t->unk8);
        t++;
    }
}

static void func_ovl0D_05_80043760(void) {
}

static void func_ovl0D_05_80043758(void) {
    Ent05 *p;

    for (p = D_ovl0D_05_80045F2C; p < D_ovl0D_05_80045F2C + 1; p++) {
        func_ovl0D_05_800435D0(p);
        p->obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_05_80043750(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_ovl0D_05_800435D0(&D_ovl0D_05_80045F64[i]);
        D_ovl0D_05_80045F64[i].obj->unk40->unk36 = 0x80;
    }
}

static void func_ovl0D_05_800435D0(Ent05 *arg0) {
    arg0->obj = func_ovl0D_05_80045640(arg0->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0D_05_800455F8(arg0->obj, 0x01080000);
    func_ovl0D_05_80045600(arg0->obj, 0x02000000);
    if (arg0->unkC != -1 && arg0->unkE != -1 && arg0->unk10 != -1 && arg0->unk12 != -1) {
        arg0->unk4 = func_ovl0D_05_80045340(arg0->obj->unk40, 0, arg0->unkC, arg0->unkE, arg0->unk10, arg0->unk12);
        if (arg0->unk4 == -1) {
            while (1) {
            }
        }
    }
    arg0->obj->unk40->unk10 = arg0->unk14 * 10.0f;
    arg0->obj->unk40->unk14 = arg0->unk18 * 10.0f;
    arg0->obj->unk40->unk18 = arg0->unk1C * 10.0f;
    arg0->obj->unk40->unk1C = arg0->unk20;
    arg0->obj->unk40->unk20 = arg0->unk24;
    arg0->obj->unk40->unk24 = arg0->unk28;
    arg0->obj->unk40->unk28 = arg0->unk2C;
    arg0->obj->unk40->unk2C = arg0->unk30;
    arg0->obj->unk40->unk30 = arg0->unk34;
}

static void func_ovl0D_05_8004352C(Ent05 *arg0) {
    s32 pos[6];

    func_ovl0D_05_80044C50(arg0->unk14 * 10.0f, arg0->unk18 * 10.0f, arg0->unk1C * 10.0f, pos, 0);
    func_ovl0D_05_80044C38(pos[0], pos[1], pos[2], pos[0] + 3, pos[2] + 3, 0x11);
    func_ovl0D_05_80044C38(pos[0], pos[1] + 1, pos[2], pos[0] + 3, pos[2] + 3, 0x10);
}

static void func_ovl0D_05_80043524(void) {
    func_ovl0D_05_80043018();
    func_ovl0D_05_80044C78();
}

void func_ovl0D_05_800434FC(void) {
    func_ovl0D_05_80044DB0(4, 2, 0x17);
}

void func_ovl0D_05_80043484(void) {
    if (func_ovl0D_05_800459D0(0x420) != 0) {
        if (func_ovl0D_05_800459D0(0x426) == 0) {
            func_ovl0D_05_800459C0(0x426);
            func_ovl0D_05_80044DB0(1, 2, 0xC);
        } else {
            func_ovl0D_05_80044DB0(1, 0, 0xC);
        }
    } else {
        func_ovl0D_05_80044DB0(1, 2, 0x17);
    }
}

void func_ovl0D_05_800433D4(void) {
    func_ovl0D_05_80044E08();
    func_ovl0D_05_80045A70(0x2D, 0x6E, 0x2C);
    switch (func_ovl0D_05_80044CF8()) {
        case 16:
            func_ovl0D_05_80044DF0(0xC0);
            func_ovl0D_05_80045458(0.0f, 32768.0f, 32768.0f);
            break;
        case 18:
            func_ovl0D_05_80044DF0(0x40);
            func_ovl0D_05_8004338C(0.0f);
            break;
    }
}

void func_ovl0D_05_8004338C(f32 arg0) {
    f32 sp1C;

    func_ovl0D_05_80045460(&sp1C, NULL, NULL);
    func_ovl0D_05_80045458(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0D_05_80043324(void) {
    if (func_ovl0D_05_80044CF8() == 18) {
        if (func_ovl0D_05_800459D0(0x420) == 0) {
            func_ovl0D_05_80044DF8(0x40, 3, 8.5f, 5, 0, 1, 1);
        }
        func_ovl0D_05_80044DE8(0);
    }
}

void func_ovl0D_05_800432F4(void) {
    func_ovl0D_05_800432EC();
    if (D_ovl0D_05_80046154 == 0x3D) {
        func_ovl0D_05_80044DE8(1);
    }
}

static void func_ovl0D_05_800432EC(void) {
}

void func_ovl0D_05_80043210(void) {
    if (!D_ovl0D_05_80046154 && !D_ovl0D_05_80046154 && !D_ovl0D_05_80046154) {
    }
    func_ovl0D_05_800431F8();
    func_ovl0D_05_80043200();
    func_ovl0D_05_80043208();
}

static void func_ovl0D_05_80043208(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_ovl0D_05_80045FD4[i].obj != NULL) {
            func_ovl0D_05_8004317C(&D_ovl0D_05_80045FD4[i]);
        }
    }
}

static void func_ovl0D_05_80043200(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_ovl0D_05_80045F64[i].obj != NULL) {
            func_ovl0D_05_8004317C(&D_ovl0D_05_80045F64[i]);
        }
    }
}

static void func_ovl0D_05_800431F8(void) {
    Ent05 *p;

    func_ovl0D_05_80045610(D_ovl0D_05_8004616C);
    for (p = D_ovl0D_05_80045F2C; p < D_ovl0D_05_80045F2C + 1; p++) {
        if (p->obj != NULL) {
            func_ovl0D_05_8004317C(p);
        }
    }
}

static void func_ovl0D_05_8004317C(Ent05 *arg0) {
    func_ovl0D_05_80045610(arg0->obj);
    if (arg0->unkC != 0xFFFF && arg0->unkE != 0xFFFF && arg0->unk10 != 0xFFFF && arg0->unk12 != 0xFFFF) {
        func_ovl0D_05_80045348(arg0->unk4);
    }
    arg0->obj = NULL;
    arg0->unk4 = -1;
}

void func_ovl0D_05_80043124(void) {
    func_ovl0D_05_8004311C();
    if (func_ovl0D_05_80044DC0(0, 0x16, 0, 0x17) != 0) {
        D_ovl0D_05_80046154 = 0x3D;
        D_ovl0D_05_80046158 = 0x11;
        func_ovl0D_05_80044CF0(0x3D, 0x11, 0);
    }
}

static void func_ovl0D_05_8004311C(void) {
}

void func_ovl0D_05_800430CC(void) {
    func_ovl0D_05_800430BC();
    func_ovl0D_05_800430C4();
    UNK_MACRO_ovl0D_05_800430CC();
    func_ovl0D_05_800459C0(0x424);
}

static void func_ovl0D_05_800430C4(void) {
}

static void func_ovl0D_05_800430BC(void) {
}

void func_ovl0D_05_80043018(void) {
    if (func_ovl0D_05_800459D0(0x409) != 0) {
        D_ovl0D_05_8004617C = func_ovl0D_05_80044CC8(0x15A);
        if (!D_ovl0D_05_8004614C) {
        }
        func_ovl0D_05_80044CD0(D_ovl0D_05_8004617C, 0, 0, D_ovl0D_05_80046170[0] - 1, D_ovl0D_05_80046170[2] - 1, 0, 0, 0);
        func_ovl0D_05_80045600(D_ovl0D_05_80045F2C[0].obj, 0x01000000);
        func_ovl0D_05_80045600(D_ovl0D_05_80045F64[0].obj, 0x01000000);
        func_ovl0D_05_80045600(D_ovl0D_05_80045F64[1].obj, 0x01000000);
    }
}

void func_ovl0D_05_80043010(void) {
}
