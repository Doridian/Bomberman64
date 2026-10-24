/*
 * NON_MATCHING: ovl_0F_05's game object, complete: every function and its data
 * (.data and .rodata as the original, .bss 0x80).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 619, eu 619, jp 619
 */
#include "common.h"

/*
 * ovl_0F_05's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). ovl_0F_08 (1FF8F0) shares
 * its callback (func_ovl0F_05_800440AC) and the small functions at the end;
 * the handler and the three tasks are its own.
 */

/* a model the stage places: twelve in D_ovl0F_05_800461E0 */
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
} UnkStruct_ovl0F_05_800461E0; /* size 0x2C */

/* what func_ovl0F_05_80045110 returns (the camera?) */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
} UnkStruct_ovl0F_05_80045110;

void func_ovl0F_05_80044E58(s32);
void func_ovl0F_05_80044E70(s32);
void func_ovl0F_05_80044EB8(f32, f32, f32, f32 *, s32);
void func_ovl0F_05_80044F38(void (*)(UnkStructA *), s32);
void func_ovl0F_05_80044F50(s32, s32, s32);
s32 func_ovl0F_05_80044F58(void);
void func_ovl0F_05_80044FC0(s32);
void func_ovl0F_05_80044FC8(s32);
void func_ovl0F_05_80045008(void);
void func_ovl0F_05_80045010(s32, s32, s32);
s32 func_ovl0F_05_80045038(void);
void func_ovl0F_05_80045048(s32);
UnkStructA *func_ovl0F_05_80045098(s32);
UnkStructA *func_ovl0F_05_800450D8(s32);
void func_ovl0F_05_800450E0(s32, s32);
UnkStruct_ovl0F_05_80045110 *func_ovl0F_05_80045110(s32);
UnkStructA_40 *func_ovl0F_05_80045538(s32, s32);
void func_ovl0F_05_80045540(UnkStructA_40 *);
void func_ovl0F_05_80045550(UnkStructA_40 *, s32);
void func_ovl0F_05_80045698(f32, f32, f32);
void func_ovl0F_05_800456A8(f32, f32, f32);
void func_ovl0F_05_800456B8(f32, f32, f32);
void func_ovl0F_05_800456C0(f32 *, f32 *, f32 *);
void func_ovl0F_05_80045700(s32);
void func_ovl0F_05_800457B8(void);
void func_ovl0F_05_800457C0(void);
s32 func_ovl0F_05_80045808(UnkStructA *, s32);
void func_ovl0F_05_80045858(UnkStructA *, s32);
void func_ovl0F_05_80045860(UnkStructA *, s32);
void func_ovl0F_05_80045870(UnkStructA *);
UnkStructA *func_ovl0F_05_800458C8(s32, s32);
s32 func_ovl0F_05_80045978(UnkStructA *, s32, UnkStructA *);
s32 func_ovl0F_05_800459A8(void (*)(void), s32, s32, s32, s32);
void func_ovl0F_05_800459B0(s32);
void func_ovl0F_05_800459B8(void);
void func_ovl0F_05_800459C8(s32);
void func_ovl0F_05_800459F0(void);
UnkStructC *func_ovl0F_05_80045A30(s32);
void func_ovl0F_05_80045A40(UnkStructC *, s32);
f32 func_ovl0F_05_80045B58(f32);
void func_ovl0F_05_80045CA8(s32, s32, s32, f32);
void func_ovl0F_05_80045D10(u32 (*)[3]);
void func_ovl0F_05_80045DF8(s32, f32, f32, f32, s32);
s32 func_ovl0F_05_80045E00(s32, f32 *, s32);
void func_ovl0F_05_80045E08(s32);
void func_ovl0F_05_80045EB8(s32, s32, s32);
void func_ovl0F_05_80045ED8(s32);
void func_ovl0F_05_80045F30(s32);
void func_ovl0F_05_80045F50(s32, f32, f32, f32);
void func_ovl0F_05_800460A8(void);
void func_ovl0F_05_800460B0(void);

void func_ovl0F_05_80043010(void);
void func_ovl0F_05_800430BC(s32);
void func_ovl0F_05_8004373C(void);
void func_ovl0F_05_80043B74(void);
void func_ovl0F_05_800440AC(UnkStructA *);
void func_ovl0F_05_8004472C(void);
void func_ovl0F_05_80044994(s32, UnkStructA *);
void func_ovl0F_05_800449C8(f32);
void func_ovl0F_05_80044A10(f32, f32, f32);
void func_ovl0F_05_80044A6C(void);
void func_ovl0F_05_80044A84(void);

static void func_ovl0F_05_80043020(UnkStruct_ovl0F_05_800461E0 *);
static void func_ovl0F_05_80043FF4(f32);
static s32 func_ovl0F_05_80043FEC(UnkStructA *);
static void func_ovl0F_05_80043FE4(s32 *, f32, f32);

/* .bss */
UnkStructA *D_ovl0F_05_800464E0[12];
u8 D_ovl0F_05_80046510[0x10];
Vec3f D_ovl0F_05_80046520;
s32 D_ovl0F_05_8004652C;
u8 D_ovl0F_05_80046530[0x4];
s32 D_ovl0F_05_80046534;
s32 D_ovl0F_05_80046538;
u8 D_ovl0F_05_8004653C[0x4];
Vec3f D_ovl0F_05_80046540;
UnkStructC *D_ovl0F_05_8004654C;
Vec3f D_ovl0F_05_80046550;
s32 D_ovl0F_05_8004655C;

/* .data */
f32 D_ovl0F_05_80046150 = 0.01f;
f32 D_ovl0F_05_80046154 = 0.1f;
s32 D_ovl0F_05_80046158 = 0;
s32 D_ovl0F_05_8004615C = 0;
UnkStructA *D_ovl0F_05_80046160 = NULL;
f32 D_ovl0F_05_80046164 = 0.0f;
f32 D_ovl0F_05_80046168 = 0.0f;
f32 D_ovl0F_05_8004616C = 0.0f;
UnkStructA *D_ovl0F_05_80046170 = NULL;
f32 D_ovl0F_05_80046174 = 0.0f;
f32 D_ovl0F_05_80046178 = 0.0f;
f32 D_ovl0F_05_8004617C = 0.0f;
s32 D_ovl0F_05_80046180 = -1;
f32 D_ovl0F_05_80046184 = 0.0f;
s32 D_ovl0F_05_80046188 = 0;
/* passed to func_ovl0F_05_80045D10: three 12-byte records */
u32 D_ovl0F_05_8004618C[][3] = {
    { 0x25D0001, 0xE, 4 },
    { 2, 0, 4 },
    { 2, 0, 4 },
};
/* four 12-byte records, each passed to func_ovl0F_05_80045EB8 */
u32 D_ovl0F_05_800461B0[][3] = {
    { 0, 0x14, 0xF2 },
    { 1, 0x16, 0xF4 },
    { 2, 0x12, 0xF0 },
    { 3, 0x15, 0xF3 },
};
UnkStruct_ovl0F_05_800461E0 D_ovl0F_05_800461E0[12] = {
    { &D_ovl0F_05_800464E0[0], 0x22B, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[1], 0x261, 0, 21.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[2], 0x268, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[3], 0x262, 0, 22.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[4], 0x22E, 0, 58.0f, 0.0f, -33.0f, 0.0f, -90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[5], 0x22F, 0, 58.0f, 0.0f, -33.0f, 0.0f, -90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[6], 0x231, 0, -12.0f, 0.0f, 14.0f, 0.0f, 90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[7], 0x232, 0, -12.0f, 0.0f, 14.0f, 0.0f, 90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[8], 0x234, 0, -5.0f, 0.0f, -58.0f, 0.0f, 0.0f, 0.0f, 0x80000, 0 },
    { &D_ovl0F_05_800464E0[9], 0x233, 0, -5.0f, 0.0f, -58.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[10], 0x235, 0, -4.0f, 0.0f, -58.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_05_800464E0[11], 0x22C, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};
s32 D_ovl0F_05_800463F0 = 0;
u8 D_ovl0F_05_800463F4[0xC] = { 0 }; /* nothing uses it */

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0F_05_80044AFC(void) {
    D_ovl0F_05_80046530[0] = D_ovl0F_05_8004653C[0];
    D_ovl0F_05_80046510[0] = D_ovl0F_05_80046520.x + D_ovl0F_05_8004652C;
}

/* A second caller keeps func_ovl0F_05_80043020 from being inlined into the
 * handler (it is a call there, with its argument in s0). */
static void func_ovl0F_05_80044AF4(void) {
    func_ovl0F_05_80043020(D_ovl0F_05_800461E0);
}

static void func_ovl0F_05_80044AEC(void) {
}

static void func_ovl0F_05_80044AE4(void) {
}

static void func_ovl0F_05_80044ADC(void) {
}

static void func_ovl0F_05_80044AD4(void) {
}

static void func_ovl0F_05_80044ACC(void) {
}

static void func_ovl0F_05_80044AC4(void) {
}

static void func_ovl0F_05_80044ABC(void) {
}

static void func_ovl0F_05_80044AB4(void) {
}

static void func_ovl0F_05_80044AAC(void) {
}

static void func_ovl0F_05_80044AA4(void) {
}

static void func_ovl0F_05_80044A9C(void) {
}

static void func_ovl0F_05_80044A94(void) {
}

static void func_ovl0F_05_80044A8C(void) {
}

void func_ovl0F_05_80044A84(void) {
}

void func_ovl0F_05_80044A6C(void) {
    D_ovl0F_05_80046534 = -1;
    D_ovl0F_05_80046538 = -1;
}

void func_ovl0F_05_80044A10(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_05_80045698(D_ovl0F_05_80046540.x, D_ovl0F_05_80046540.y, D_ovl0F_05_80046540.z);
    func_ovl0F_05_800456B8(arg0, arg1, arg2);
    func_ovl0F_05_800459C8(180);
}

void func_ovl0F_05_800449C8(f32 arg0) {
    f32 sp1C;

    func_ovl0F_05_800456C0(&sp1C, NULL, NULL);
    func_ovl0F_05_800456B8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0F_05_80044994(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0F_05_80045F50(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0F_05_8004472C(void) {
    f32 x;
    f32 z;
    s32 i;

    D_ovl0F_05_80046550.x = 35.0f;
    D_ovl0F_05_80046550.y = 38.894f;
    D_ovl0F_05_80046550.z = 4000.0f;
    x = 3929.4f;
    z = 1626.7f;
    for (i = 0; i < 500; i++) {
        z += -0.29177588f;
        x += -4.8027997f;
        D_ovl0F_05_80046550.y -= 0.03f;
        D_ovl0F_05_80046550.z += -4.0f;
        func_ovl0F_05_80045698(x, 32768.0f, z);
        func_ovl0F_05_800456B8(32768.0f, D_ovl0F_05_80046550.y, D_ovl0F_05_80046550.z);
        func_ovl0F_05_800459F0();
    }
    func_ovl0F_05_800459C8(100);
    for (i = 0; i < 600; i++) {
        D_ovl0F_05_80046550.y -= 0.081166685f;
        if (D_ovl0F_05_80046550.y < 0.0f) {
            D_ovl0F_05_80046550.y += 360.0f;
        }
        D_ovl0F_05_80046550.x -= 0.073666684f;
        if (D_ovl0F_05_80046550.x < 0.0f) {
            D_ovl0F_05_80046550.x += 360.0f;
        }
        func_ovl0F_05_800456B8(D_ovl0F_05_80046550.x, D_ovl0F_05_80046550.y, 32768.0f);
        func_ovl0F_05_800459F0();
    }
    func_ovl0F_05_800459C8(160);
    for (i = 0; i < 200; i++) {
        z += 0.4574402f;
        x += 2.8232496f;
        func_ovl0F_05_80045698(x, 32768.0f, z);
        func_ovl0F_05_800459F0();
    }
    while (1) {
        func_ovl0F_05_800459C8(100);
    }
}

static void func_ovl0F_05_8004409C(void) {
}

static void func_ovl0F_05_800440A4(s16 x, s16 z, f32 *vel) {
    vel[0] = x * 0.002f;
    vel[2] = z * 0.002f;
}

void func_ovl0F_05_800440AC(UnkStructA *arg0) {
    f32 vel[3];
    f32 dx;
    f32 dz;
    f32 pos[3];
    UnkStructA_40 *p;

    func_ovl0F_05_8004409C();
    dx = arg0->unk40->unk10 - arg0->unk58;
    dz = arg0->unk40->unk18 - arg0->unk60;
    if (arg0->unk8 & 1) {
        D_ovl0F_05_8004615C = 1;
        D_ovl0F_05_80046160 = arg0;
    } else {
        D_ovl0F_05_8004615C = 0;
        D_ovl0F_05_80046160 = NULL;
    }
    if (arg0->unk68 != 0.0f || arg0->unk6C != 0.0f) {
        arg0->unk64 = 0;
        D_ovl0F_05_80046158 = 0;
        return;
    }
    p = arg0->unk40;
    pos[0] = p->unk10;
    pos[1] = p->unk14;
    pos[2] = p->unk18;
    func_ovl0F_05_800440A4(arg0->unk64 >> 16, arg0->unk64 & 0xFFFF, vel);
    if ((s32)vel[0] != (s32)dx) {
        arg0->unk40->unk10 = arg0->unk58;
        if ((s32)dx < (s32)vel[0]) {
            vel[0] -= (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl0F_05_80046154 : D_ovl0F_05_80046150);
            if (vel[0] < dx) {
                vel[0] = dx;
            }
            func_ovl0F_05_80043FF4(dx);
        } else if ((s32)vel[0] < (s32)dx) {
            vel[0] += (dz != 0.0f ? 0.707f : 1.0f) * (dx != 0.0f ? D_ovl0F_05_80046154 : D_ovl0F_05_80046150);
            if (dx < vel[0]) {
                vel[0] = dx;
            }
            func_ovl0F_05_80043FF4(dx);
        }
        arg0->unk40->unk10 += vel[0];
    }
    if ((s32)vel[2] != (s32)dz) {
        arg0->unk40->unk18 = arg0->unk60;
        if ((s32)dz < (s32)vel[2]) {
            vel[2] -= (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl0F_05_80046154 : D_ovl0F_05_80046150);
            if (vel[2] < dz) {
                vel[2] = dz;
            }
            func_ovl0F_05_80043FF4(dz);
        } else if ((s32)vel[2] < (s32)dz) {
            vel[2] += (dx != 0.0f ? 0.707f : 1.0f) * (dz != 0.0f ? D_ovl0F_05_80046154 : D_ovl0F_05_80046150);
            if (dz < vel[2]) {
                vel[2] = dz;
            }
            func_ovl0F_05_80043FF4(dz);
        }
        arg0->unk40->unk18 += vel[2];
    }
    if (func_ovl0F_05_80043FEC(arg0)) {
        func_ovl0F_05_80043FE4(&arg0->unk64, 0.0f, 0.0f);
        arg0->unk40->unk10 = pos[0];
        arg0->unk40->unk14 = pos[1];
        arg0->unk40->unk18 = pos[2];
    } else {
        func_ovl0F_05_80043FE4(&arg0->unk64, vel[0], vel[2]);
    }
}

static void func_ovl0F_05_80043FE4(s32 *dst, f32 x, f32 z) {
    *dst = ((s16)(x * 500.0f) << 16) | ((s16)(z * 500.0f) & 0xFFFF);
}

static s32 func_ovl0F_05_80043FEC(UnkStructA *arg0) {
    s32 hit;
    s32 saved;
    UnkStructA *other;
    s32 id;

    hit = 0;
    other = NULL;
    saved = arg0->unkC;
    arg0->unkC = 0;
    if (arg0->unk8 & 1) {
        other = func_ovl0F_05_800450D8(func_ovl0F_05_80045038());
    } else if (arg0->unk8 & 2) {
        id = func_ovl0F_05_80045038();
        if (func_ovl0F_05_800450D8(id) == arg0) {
            other = func_ovl0F_05_80045098(id);
        } else {
            other = NULL;
        }
    }
    if (other != NULL) {
        if (func_ovl0F_05_80045978(arg0, 0x10, other) != 0) {
            hit = 1;
        }
    } else if (func_ovl0F_05_80045808(arg0, 0x10) != 0) {
        hit = 1;
    }
    arg0->unkC = saved;
    return hit;
}

static void func_ovl0F_05_80043FF4(f32 arg0) {
    if (D_ovl0F_05_8004615C != 0) {
        if (D_ovl0F_05_80046158 == 0) {
            if (arg0 == 0.0f) {
                func_ovl0F_05_80045F30(0x32);
            } else {
                func_ovl0F_05_80045F30(0x27);
            }
            D_ovl0F_05_80046158 = 20;
            func_ovl0F_05_80045DF8(0x19, D_ovl0F_05_80046160->unk40->unk10, D_ovl0F_05_80046160->unk40->unk14,
                                   D_ovl0F_05_80046160->unk40->unk18, 0);
        } else {
            D_ovl0F_05_80046158--;
        }
    }
}

static void func_ovl0F_05_80043B6C(void) {
}

void func_ovl0F_05_80043B74(void) {
    UnkStructA_40 *objs[4];
    s32 task;
    UnkStruct_ovl0F_05_80045110 *cam;
    s32 i;
    s32 j;
    s32 k;
    s32 flag;

    func_ovl0F_05_80043B6C();
    cam = func_ovl0F_05_80045110(0);
    D_ovl0F_05_800463F0 = 0;
    do {
        func_ovl0F_05_800459F0();
    } while (D_ovl0F_05_800463F0 == 0);
    task = func_ovl0F_05_800459A8(func_ovl0F_05_8004472C, 0, 0, 0, 0x130);
    func_ovl0F_05_80044F38(func_ovl0F_05_800440AC, 1);
    func_ovl0F_05_800450E0(0, 2);
    cam->unk8 = 30.0f;
    cam->unk4 = 0.0f;
    cam->unk0 = 32.0f;
    func_ovl0F_05_800459C8(0x23A);
    cam->unk8 = 0.0f;
    cam->unkC = 0x4000;
    cam->unkE = 0x8000;
    func_ovl0F_05_800459F0();
    cam->unkC = 0;
    func_ovl0F_05_800459C8(40);
    cam->unkE = 0;
    func_ovl0F_05_800459F0();
    cam->unk8 = 30.0f;
    cam->unk0 = 60.0f;
    for (k = 0; k < 300; k++) {
        cam->unk0 += 0.08f;
        func_ovl0F_05_800459F0();
    }
    cam->unk0 = 180.0f;
    func_ovl0F_05_800459F0();
    cam->unk8 = 0.0f;
    func_ovl0F_05_800459C8(120);
    for (i = 0; i < 4; i++) {
        objs[i] = func_ovl0F_05_80045538(0x307, 0);
        objs[i]->unkC |= 0x80;
        objs[i]->unk36 = 60;
        objs[i]->unk10 = 2450.0f;
        objs[i]->unk14 = 0.0f;
        objs[i]->unk18 = 500.0f;
        objs[i]->unk1C = 90.0f;
        objs[i]->unk28 = objs[i]->unk2C = objs[i]->unk30 = (i + 1) * 0.5f;
    }
    flag = 0;
    for (i = 0; i < 180; i++) {
        for (j = 0; j < 4; j++) {
            objs[j]->unk10 -= (j + 1) * 4.0f;
            objs[j]->unk14 -= (j + 1);
        }
        if (flag) {
            func_ovl0F_05_800459C8(1);
            D_ovl0F_05_80046550.x += 0.33333334f;
        }
        func_ovl0F_05_800459F0();
    }
    for (i = 0; i < 4; i++) {
        func_ovl0F_05_80045540(objs[i]);
    }
    func_ovl0F_05_800459C8(120);
    cam->unk8 = 36.0f;
    func_ovl0F_05_800459C8(30);
    cam->unk8 = 61.0f;
    func_ovl0F_05_800459C8(30);
    cam->unk8 = 0.0f;
    func_ovl0F_05_800459C8(80);
    cam->unkC = cam->unkE = 0x4000;
    func_ovl0F_05_800459F0();
    cam->unkE = 0;
    func_ovl0F_05_800459C8(30);
    func_ovl0F_05_800460A8();
    if (task != -1) {
        func_ovl0F_05_800459B0(task);
    }
    func_ovl0F_05_800459B8();
}

void func_ovl0F_05_8004373C(void) {
    s32 running;
    f32 pos[3];

    running = 1;
    do {
        D_ovl0F_05_80046164 += 1.0f;
        if (D_ovl0F_05_80046164 < 500.0f) {
            func_ovl0F_05_800456B8(D_ovl0F_05_80046168, D_ovl0F_05_8004616C, 6408.0f);
            D_ovl0F_05_80046168 += 0.2734f;
            D_ovl0F_05_8004616C += 0.065699995f;
            D_ovl0F_05_80046174 -= 2.5f;
        } else if (D_ovl0F_05_80046164 == 500.0f) {
            func_ovl0F_05_80045F30(0x8B);
            func_ovl0F_05_80045698(2200.0f, 100.0f, 332.0f);
            func_ovl0F_05_800456B8(135.0f, 56.8f, 2000.0f);
            D_ovl0F_05_800464E0[3]->unk40->unk28 = 1.0f;
            D_ovl0F_05_800464E0[3]->unk40->unk2C = 1.0f;
            D_ovl0F_05_800464E0[3]->unk40->unk30 = 1.0f;
            D_ovl0F_05_80046174 = 600.0f;
        } else if (D_ovl0F_05_80046164 < 650.0f) {
            D_ovl0F_05_80046174 -= 4.0f;
        } else if (D_ovl0F_05_80046164 == 650.0f) {
            D_ovl0F_05_80046184 = 0.0f;
            func_ovl0F_05_80045F30(0x90);
        } else if (D_ovl0F_05_80046164 < 830.0f) {
            D_ovl0F_05_80046174 += func_ovl0F_05_80045B58(D_ovl0F_05_80046184);
            D_ovl0F_05_80046184 += 1.0f;
        } else if (D_ovl0F_05_80046164 == 830.0f) {
            D_ovl0F_05_80046184 = 0.0f;
            func_ovl0F_05_80045F30(0x90);
        } else if (D_ovl0F_05_80046164 < 890.0f) {
            D_ovl0F_05_80046174 += func_ovl0F_05_80045B58(D_ovl0F_05_80046184);
            D_ovl0F_05_80046184 += 3.0f;
        } else if (D_ovl0F_05_80046164 == 890.0f) {
            D_ovl0F_05_80046174 = 0.0f;
            func_ovl0F_05_80045F30(0x90);
        } else if (D_ovl0F_05_80046164 < 940.0f) {
        } else if (D_ovl0F_05_80046164 == 940.0f) {
            func_ovl0F_05_80044EB8(22.0f, 0, 3.0f, pos, 0);
            pos[1] += 2.0f;
            func_ovl0F_05_80045F30(0x2C);
            D_ovl0F_05_80046180 = func_ovl0F_05_80045E00(0x25, pos, 0);
        } else if (D_ovl0F_05_80046164 < 1090.0f) {
        } else {
            running = 0;
        }
        D_ovl0F_05_800464E0[3]->unk40->unk18 = D_ovl0F_05_80046178 - D_ovl0F_05_80046174;
        D_ovl0F_05_800464E0[3]->unk40->unk14 =
            (1.0f - D_ovl0F_05_800464E0[3]->unk40->unk2C) * 600.0f + (D_ovl0F_05_8004617C + D_ovl0F_05_80046174);
        func_ovl0F_05_800459F0();
    } while (running);
    func_ovl0F_05_80044F50(0x61, 0x15, 0);
    func_ovl0F_05_800459B8();
}

static void func_ovl0F_05_800430B4(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0F_05_80045D10(D_ovl0F_05_8004618C);
    p = D_ovl0F_05_800461B0;
    count = 4;
    for (i = 0; i < count; i++) {
        func_ovl0F_05_80045EB8((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}

static void func_ovl0F_05_800430AC(void) {
    func_ovl0F_05_80044E58(0x22A);
    func_ovl0F_05_80044E70(0x23D);
    func_ovl0F_05_80045008();
}

static void func_ovl0F_05_800430A4(s32 arg1, UnkStruct_ovl0F_05_800461E0 *arg0) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *arg0->unk0 = func_ovl0F_05_800458C8(arg0->unk4, arg0->unk8);
        func_ovl0F_05_80045858(*arg0->unk0, arg0->unk24 | 0x01000000);
        func_ovl0F_05_80043020(arg0);
        (*arg0->unk0)->unk40->unk1C = arg0->unk18;
        (*arg0->unk0)->unk40->unk20 = arg0->unk1C;
        (*arg0->unk0)->unk40->unk24 = arg0->unk20;
        arg0++;
    }
}

static void func_ovl0F_05_80043018(s32 count, UnkStruct_ovl0F_05_800461E0 *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_05_80045870(*p->unk0);
        p++;
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_05_800430BC(s32 arg0) {
    s32 pad[2];

    switch (arg0) {
        case 2:
            D_ovl0F_05_8004655C = func_ovl0F_05_80044F58();
            if (D_ovl0F_05_8004655C == 0x10) {
                D_ovl0F_05_80046188 = 1;
                func_ovl0F_05_80045ED8(0);
            } else {
                D_ovl0F_05_80046188 = 0;
            }
            func_ovl0F_05_80045CA8(0xFF, 0, 0, 120.0f);
            func_ovl0F_05_800430B4();
            func_ovl0F_05_800430AC();
            func_ovl0F_05_800430A4(12, D_ovl0F_05_800461E0);
            func_ovl0F_05_80045550(D_ovl0F_05_800464E0[0]->unk40, 0x61);
            func_ovl0F_05_80045550(D_ovl0F_05_800464E0[5]->unk40, 0x61);
            func_ovl0F_05_80045550(D_ovl0F_05_800464E0[7]->unk40, 0x61);
            func_ovl0F_05_80045550(D_ovl0F_05_800464E0[8]->unk40, 0x61);
            D_ovl0F_05_800464E0[8]->unk40->unk14 -= 3200.0f;
            D_ovl0F_05_800464E0[9]->unk40->unk14 -= 3200.0f;
            D_ovl0F_05_800464E0[10]->unk40->unk14 -= 3200.0f;
            /* fake: ends the block, so the call is not scheduled into the
             * stores before it */
            if (D_ovl0F_05_8004615C && D_ovl0F_05_8004615C && D_ovl0F_05_8004615C) {}
            D_ovl0F_05_8004654C = func_ovl0F_05_80045A30(0x279);
            func_ovl0F_05_80045A40(D_ovl0F_05_8004654C, 0x20000000);
            D_ovl0F_05_8004654C->unk40 = 0.6f;
            D_ovl0F_05_8004654C->unk44 = D_ovl0F_05_8004654C->unk40 * 0.75f;
            D_ovl0F_05_8004654C->unk3C = D_ovl0F_05_8004654C->unk4C * 0.3f;
            D_ovl0F_05_800464E0[2]->unk40->unk10 = 2400.0f;
            D_ovl0F_05_800464E0[2]->unk40->unk14 = 2600.0f;
            D_ovl0F_05_800464E0[2]->unk40->unk18 = -2000.0f;
            D_ovl0F_05_800464E0[2]->unk40->unk28 = 16.0f;
            D_ovl0F_05_800464E0[2]->unk40->unk2C = 16.0f;
            D_ovl0F_05_800464E0[2]->unk40->unk30 = 16.0f;
            D_ovl0F_05_80046164 = 0.0f;
            if (D_ovl0F_05_80046188 == 0) {
                D_ovl0F_05_80046170 = func_ovl0F_05_80045098(func_ovl0F_05_80045038());
                func_ovl0F_05_80045860(D_ovl0F_05_80046170, 0x01000000);
            }
            D_ovl0F_05_80046180 = -1;
            break;
        case 16:
            func_ovl0F_05_80045010(6, 0, 11);
            break;
        case 4:
            if (D_ovl0F_05_80046188 == 1) {
                func_ovl0F_05_800456B8(35.0f, 38.894f, 4000.0f);
                func_ovl0F_05_800456A8(1259.038f, 1715.864f, 2157.064f);
                func_ovl0F_05_80045698(3929.4f, -132.448f, 1626.7f);
                func_ovl0F_05_800459A8(func_ovl0F_05_80043B74, 0, 0, 0, 0x130);
                func_ovl0F_05_80045700(0x7F);
            } else {
                func_ovl0F_05_80044FC8(1);
                func_ovl0F_05_80045048(1);
                func_ovl0F_05_800457B8();
                func_ovl0F_05_80045700(0x7F);
                D_ovl0F_05_80046168 = 24.1f;
                D_ovl0F_05_8004616C = 0.0f;
                func_ovl0F_05_80045698(2702.9f, 2073.1f, -975.7f);
                func_ovl0F_05_800456B8(D_ovl0F_05_80046168, D_ovl0F_05_8004616C, 6408.0f);
                D_ovl0F_05_80046178 = D_ovl0F_05_800464E0[3]->unk40->unk18;
                D_ovl0F_05_8004617C = D_ovl0F_05_800464E0[3]->unk40->unk14;
                D_ovl0F_05_800464E0[3]->unk40->unk28 = 0.5f;
                D_ovl0F_05_800464E0[3]->unk40->unk2C = 0.5f;
                D_ovl0F_05_800464E0[3]->unk40->unk30 = 0.5f;
                D_ovl0F_05_80046174 = 2200.0f;
                D_ovl0F_05_800464E0[3]->unk40->unk18 = D_ovl0F_05_80046178 - D_ovl0F_05_80046174;
                D_ovl0F_05_800464E0[3]->unk40->unk14 =
                    (1.0f - D_ovl0F_05_800464E0[3]->unk40->unk2C) * 600.0f + (D_ovl0F_05_8004617C + D_ovl0F_05_80046174);
                func_ovl0F_05_800459A8(func_ovl0F_05_8004373C, 0, 0, 0, 0x130);
            }
            break;
        case 1:
            func_ovl0F_05_80043018(12, D_ovl0F_05_800461E0);
            if (D_ovl0F_05_80046180 != -1) {
                func_ovl0F_05_80045E08(D_ovl0F_05_80046180);
            }
            if (D_ovl0F_05_80046188 == 1) {
                func_ovl0F_05_800460B0();
            } else {
                func_ovl0F_05_80045CA8(0, 0, 0, 0.0f);
                func_ovl0F_05_80045858(D_ovl0F_05_80046170, 0x01000000);
                func_ovl0F_05_800457C0();
                func_ovl0F_05_80044FC0(1);
                func_ovl0F_05_80045048(0);
                func_ovl0F_05_80044FC8(0);
            }
            break;
        case 3:
            D_ovl0F_05_800463F0 = 1;
            func_ovl0F_05_80044FC0(0);
            break;
    }
}

static void func_ovl0F_05_80043020(UnkStruct_ovl0F_05_800461E0 *arg0) {
    f32 pos[3];

    func_ovl0F_05_80044EB8(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

void func_ovl0F_05_80043010(void) {
}
