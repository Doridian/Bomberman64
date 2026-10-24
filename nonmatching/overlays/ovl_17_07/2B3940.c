/*
 * NON_MATCHING: ovl_17_07's game object, complete: every function and its data.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 202, eu 202, jp 202
 *
 * What still differs in us (words):
 * - func_ovl17_07_8004376C (189): frame 0x58, not 0x60: the original saves
 *   $f26/$f27 too and numbers the s registers one higher (s6 for ours s7);
 *   9 words short, so the rest is shifted.
 * - func_ovl17_07_80043A70 (13): one nop too many (a word long).
 */
#include "common.h"

/*
 * ovl_17_07's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

/* the model D_ovl17_07_8004376C turns, and where it stands */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
} UnkStruct_ovl17_07_80045680; /* size 0xC */

/* a model placed in the stage (ovl_17_01's kind) */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
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
} UnkStruct_ovl17_07_800456B0; /* size 0x38 */

/* the argument of func_ovl17_07_80043C98's tasks: a model moving along x */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} UnkStruct_ovl17_07_800456E8; /* size 0x24 */

void func_ovl17_07_80044388(s32);
void func_ovl17_07_800443A0(s32);
void func_ovl17_07_800443D0(s32, s32, s32, s32, s32, s32, s32);
void func_ovl17_07_80044468(void (*)(UnkStructA *), s32);
void func_ovl17_07_80044500(s32);
UnkStructB *func_ovl17_07_80044508(void);
void func_ovl17_07_80044538(void);
UnkStructA *func_ovl17_07_800445C8(s32);
UnkStructA *func_ovl17_07_80044608(s32);
s32 func_ovl17_07_80044AD0(UnkStructA_40 *, s32, s16, s16, s32, s32);
void func_ovl17_07_80044AD8(s32);
void func_ovl17_07_80044BA8(s32);
void func_ovl17_07_80044BB8(s32);
void func_ovl17_07_80044BC8(f32, f32, f32);
void func_ovl17_07_80044BE8(f32, f32, f32);
void func_ovl17_07_80044BF0(f32 *, f32 *, f32 *);
void func_ovl17_07_80044C30(s32);
s32 func_ovl17_07_80044D38(UnkStructA *, s32, UnkStructA *);
void func_ovl17_07_80044D88(UnkStructA *, s32);
void func_ovl17_07_80044D90(UnkStructA *, s32);
UnkStructA *func_ovl17_07_80044DC0(UnkStructA *);
UnkStructA *func_ovl17_07_80044DD0(s32, s32, f32, f32, f32);
s32 func_ovl17_07_80044EA8(UnkStructA *, s32, UnkStructA *);
void func_ovl17_07_80044ED8(void (*)(void), void *, s32, s32, s32);
void func_ovl17_07_80044EE8(void);
void func_ovl17_07_80044EF8(s32);
void *func_ovl17_07_80044F00(void);
void func_ovl17_07_80044F20(void);
s32 func_ovl17_07_80044F60(s32);
void func_ovl17_07_80044F70(s32, s32);
s32 func_ovl17_07_80045098(s32);
void func_ovl17_07_80045150(s32);
void func_ovl17_07_80045158(s32);
s32 func_ovl17_07_80045160(s32);
void func_ovl17_07_800451D8(s32, s32, s32, f32);
void func_ovl17_07_80045240(u32 (*)[3]);
void func_ovl17_07_80045328(s32, f32, f32, f32, s32);
s32 func_ovl17_07_80045388(UnkStructA *);
s32 func_ovl17_07_80045390(s16);
void func_ovl17_07_80045398(s16, s32);
void func_ovl17_07_800453D8(UnkStructA *, s32, f32);
void func_ovl17_07_80045460(s32);
void func_ovl17_07_80045480(s32, f32, f32, f32);

void func_ovl17_07_80043010(void);
void func_ovl17_07_80043098(void);
void func_ovl17_07_800430D0(void);
void func_ovl17_07_80043150(void);
void func_ovl17_07_800431CC(s32);
void func_ovl17_07_8004354C(UnkStructA *);
void func_ovl17_07_8004376C(s32, f32);
void func_ovl17_07_80043A70(void);
void func_ovl17_07_80043BA0(UnkStructA *);
void func_ovl17_07_80043C98(void);

/* .bss */
u8 D_ovl17_07_80045780[0x24];
s32 D_ovl17_07_800457A4;
s32 D_ovl17_07_800457A8;
u8 D_ovl17_07_800457AC[0x4];
Vec3f D_ovl17_07_800457B0;
s32 D_ovl17_07_800457BC;
s32 D_ovl17_07_800457C0;

/* .data */
UnkStruct_ovl17_07_80045680 D_ovl17_07_80045680 = { NULL, 2300, 400, 1500 };
/* passed to func_ovl17_07_80045240: three 12-byte records */
u32 D_ovl17_07_8004568C[][3] = {
    { 0xD80000, 0xE000C, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
UnkStruct_ovl17_07_800456B0 D_ovl17_07_800456B0 = {
    NULL, -1, 0x215, 0, 0x400, 0, 0x400, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
};
UnkStruct_ovl17_07_800456E8 D_ovl17_07_800456E8[2] = {
    { NULL, 0x214, 0.0f, 0.0f, 0.0f, 700.0f, 0x10, 8, 0x16 },
    { NULL, 0x213, 0.0f, 0.0f, 0.0f, -700.0f, 0x1E, 8, 0x16 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl17_07_80044030(void) {
    D_ovl17_07_80045780[0] = D_ovl17_07_800457AC[0];
}

static void func_ovl17_07_80044028(void) {
    func_ovl17_07_80044ED8(func_ovl17_07_80043098, NULL, 0, 0, 0);
}

static void func_ovl17_07_80044020(void) {
}

static void func_ovl17_07_80044018(void) {
}

static void func_ovl17_07_80044010(void) {
}

static void func_ovl17_07_80044008(void) {
}

static void func_ovl17_07_80044000(void) {
}

static void func_ovl17_07_80043FF8(void) {
}

static void func_ovl17_07_80043FF0(void) {
}

static void func_ovl17_07_80043FE8(void) {
}

static void func_ovl17_07_80043FE0(void) {
}

void func_ovl17_07_80043FC8(void) {
    D_ovl17_07_800457A4 = -1;
    D_ovl17_07_800457A8 = -1;
}

void func_ovl17_07_80043F6C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl17_07_80044BC8(D_ovl17_07_800457B0.x, D_ovl17_07_800457B0.y, D_ovl17_07_800457B0.z);
    func_ovl17_07_80044BE8(arg0, arg1, arg2);
    func_ovl17_07_80044EF8(180);
}

void func_ovl17_07_80043F24(f32 arg0) {
    f32 sp1C;

    func_ovl17_07_80044BF0(&sp1C, NULL, NULL);
    func_ovl17_07_80044BE8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl17_07_80043EF0(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl17_07_80045480(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl17_07_80043C98(void) {
    UnkStruct_ovl17_07_800456E8 *rec;
    UnkStructB *b;
    f32 acc;
    f32 step;
    s32 n;
    s32 flag;

    rec = func_ovl17_07_80044F00();
    b = func_ovl17_07_80044508();
    while (TRUE) {
        if (b->unk2C <= 0) {
            break;
        }
        func_ovl17_07_80044F20();
    }
    acc = 0;
    n = rec->unk18;
    flag = FALSE;
    step = (rec->unk14 - rec->unk8) / 3600.0f;
    while (TRUE) {
        if (ABS(acc) > 80.0f && !flag) {
            flag = TRUE;
            func_ovl17_07_800443D0(n, 0, rec->unk1C, n, 5, rec->unk20, 0x141F);
        }
        if (ABS(acc) >= 100.0f) {
            if (acc > 0.0f) {
                acc -= 100.0f;
                n++;
                flag = FALSE;
            } else {
                acc += 100.0f;
                n--;
                flag = FALSE;
            }
        }
        if (ABS(rec->unk0->unk40->unk10 - rec->unk8) > ABS(rec->unk14 - rec->unk8)) {
            func_ovl17_07_80044EE8();
        }
        acc += step;
        rec->unk0->unk40->unk10 += step;
        func_ovl17_07_80044F20();
    }
}

void func_ovl17_07_80043BA0(UnkStructA *arg0) {
    s32 i;
    s32 r;
    s16 k;

    func_ovl17_07_80045328(0xF, arg0->unk40->unk10, arg0->unk40->unk14, arg0->unk40->unk18, 0);
    if (arg0->unk8 & 1) {
        for (i = 0; i < 4; i++) {
            if (func_ovl17_07_800445C8(i) == arg0) {
                break;
            }
        }
        if (i < 4) {
            k = i;
            if (func_ovl17_07_80045390(k) != 0) {
                func_ovl17_07_80045398(k, 0);
            }
        }
    } else {
        r = func_ovl17_07_80045388(arg0);
        if (r != -1) {
            func_ovl17_07_80045398(r, 0);
        }
    }
    arg0->unk5C = -600.0f;
    arg0->unk40->unk14 = -600.0f;
}

void func_ovl17_07_80043A70(void) {
    s32 dir;
    f32 angle;

    D_ovl17_07_800457C0 = 0;
    func_ovl17_07_80044EF8(300);
    while (TRUE) {
        if (func_ovl17_07_80045098(1) == 0) {
            angle = 90.0f;
            dir = 0xC0;
            func_ovl17_07_80045158(0x401);
        } else {
            angle = 270.0f;
            dir = 0x40;
            func_ovl17_07_80045150(0x401);
        }
        func_ovl17_07_80045460(0x1EF);
        func_ovl17_07_80045150(0x400);
        func_ovl17_07_8004376C(dir, angle);
        func_ovl17_07_80044EF8(func_ovl17_07_80045098(120) + 180);
        if (angle == 90.0f) {
            dir = 0x40;
        } else {
            dir = 0xC0;
        }
        func_ovl17_07_80045158(0x400);
        func_ovl17_07_8004376C(dir, 0.0f);
        func_ovl17_07_80044EF8(func_ovl17_07_80045098(120) + 60);
        func_ovl17_07_80044F20();
    }
}

void func_ovl17_07_8004376C(s32 arg0, f32 arg1) {
    UnkStructA *obj;
    f32 cur;
    f32 diff;
    f32 t;
    s32 i;
    s32 x;
    s32 y;

    obj = D_ovl17_07_80045680.unk0;
    cur = obj->unk40->unk20;
    if (arg0 != 0xC0) {
        diff = cur - arg1;
        if (cur < arg1) {
            diff += 360.0f;
        }
    } else {
        diff = arg1 - cur;
        if (arg1 < cur) {
            diff += 360.0f;
        }
    }
    if (diff >= 360.0f) {
        t = 0.0f;
    } else {
        t = 0.0f;
    }
    if (arg0 != 0xC0) {
        diff = -diff;
    }
    diff /= 60.0f;
    for (i = 0; i < 60; i++) {
        obj->unk40->unk20 += diff;
        y = -0x400;
        if (func_ovl17_07_80045160(0x401) != 0) {
            y = 0x400;
            if (func_ovl17_07_80045160(0x400) != 0) {
                x = (s32) t;
            } else {
                x = 10 - (s32) t;
            }
            D_ovl17_07_800457C0 = x / 2;
        } else {
            if (func_ovl17_07_80045160(0x400) != 0) {
                x = -(s32) t;
            } else {
                x = -(10 - (s32) t);
            }
            D_ovl17_07_800457C0 = (x < 0 ? -x : x) / 2;
        }
        func_ovl17_07_80044AD8(D_ovl17_07_800456B0.unk4);
        D_ovl17_07_800456B0.unk4 = func_ovl17_07_80044AD0(D_ovl17_07_800456B0.unk0->unk40, 0, x, y,
                                                          D_ovl17_07_800456B0.unk10, D_ovl17_07_800456B0.unk12);
        func_ovl17_07_80044F20();
        t += 0.16666667f;
    }
    D_ovl17_07_800457C0 = 5;
    obj->unk40->unk20 = arg1;
}

void func_ovl17_07_8004354C(UnkStructA *arg0) {
    s32 pad;
    s32 moved;
    UnkStructA *other;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 saved;

    if (func_ovl17_07_80045160(0x400) != 0 && arg0->unk6C == 0.0f && arg0->unk68 == 0.0f) {
        x = arg0->unk40->unk10;
        y = arg0->unk40->unk14;
        z = arg0->unk40->unk18;
        if (func_ovl17_07_80045160(0x401) != 0) {
            func_ovl17_07_800453D8(arg0, 0xC0, D_ovl17_07_800457C0);
        } else {
            func_ovl17_07_800453D8(arg0, 0x40, D_ovl17_07_800457C0);
        }
        moved = FALSE;
        if (arg0->unk8 & 3) {
            if (arg0->unk8 & 2) {
                for (i = 0; i < 5; i++) {
                    if (func_ovl17_07_80044608(i) == arg0) {
                        break;
                    }
                }
                if (i < 5) {
                    other = func_ovl17_07_800445C8(i);
                } else {
                    other = NULL;
                }
            } else {
                for (i = 0; i < 5; i++) {
                    if (func_ovl17_07_800445C8(i) == arg0) {
                        break;
                    }
                }
                if (i < 5) {
                    other = func_ovl17_07_80044608(i);
                } else {
                    other = NULL;
                }
            }
        } else {
            other = NULL;
        }
        saved = arg0->unkC;
        arg0->unkC = 0;
        if (other != NULL) {
            if (func_ovl17_07_80044EA8(arg0, 0x10, other) != 0) {
                moved = TRUE;
            }
        } else {
            if (func_ovl17_07_80044D38(arg0, 0x10, other) != 0) {
                moved = TRUE;
            }
        }
        arg0->unkC = saved;
        if (moved) {
            arg0->unk40->unk10 = x;
            arg0->unk40->unk14 = y;
            arg0->unk40->unk18 = z;
        }
    }
}

static void func_ovl17_07_80043204(UnkStruct_ovl17_07_800456B0 *e) {
    e->unk0 = func_ovl17_07_80044DD0(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl17_07_80044D88(e->unk0, 0x01080000);
    func_ovl17_07_80044D90(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 &&
        e->unk12 != -1) {
        e->unk4 =
            func_ovl17_07_80044AD0(e->unk0->unk40, 0, e->unkC,
                                   e->unkE, e->unk10, e->unk12);
        if (e->unk4 == -1) {
            while (TRUE) {
            }
        }
    }
    e->unk0->unk40->unk10 = e->unk14 * 10.0f;
    e->unk0->unk40->unk14 = e->unk18 * 10.0f;
    e->unk0->unk40->unk18 = e->unk1C * 10.0f;
    e->unk0->unk40->unk1C = e->unk20;
    e->unk0->unk40->unk20 = e->unk24;
    e->unk0->unk40->unk24 = e->unk28;
    e->unk0->unk40->unk28 = e->unk2C;
    e->unk0->unk40->unk2C = e->unk30;
    e->unk0->unk40->unk30 = e->unk34;
    if (e && e && e) { /* fake: without it the handler's next call is scheduled into these stores */
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl17_07_8004320C(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl17_07_80045240(D_ovl17_07_8004568C);
            func_ovl17_07_80044388(0x212);
            func_ovl17_07_80043204(&D_ovl17_07_800456B0);
            func_ovl17_07_800443A0(0x21F);
            func_ovl17_07_80044538();
            func_ovl17_07_800431CC(0x296);
            func_ovl17_07_80044500(0);
            func_ovl17_07_80044C30(0x7F);
            func_ovl17_07_80044BA8(1);
            func_ovl17_07_80044BB8(1);
            func_ovl17_07_80044BC8(2300.0f, 330.0f, 1640.0f);
            func_ovl17_07_80044BE8(0.0f, 55.0f, 2480.0f);
            func_ovl17_07_80044468(func_ovl17_07_8004354C, 1);
            func_ovl17_07_80043150();
            func_ovl17_07_80044468(func_ovl17_07_80043BA0, 5);
            func_ovl17_07_800430D0();
            break;
        case 3:
        case 4:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            break;
        case 5:
            func_ovl17_07_80043098();
            func_ovl17_07_80043010();
            break;
        case 1:
            func_ovl17_07_800451D8(0, 0, 0, 0.0f);
            break;
        case 0x50:
            break;
        case 0x51:
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl17_07_800431CC(s32 arg0) {
    D_ovl17_07_800457BC = func_ovl17_07_80044F60(arg0);
    func_ovl17_07_80044F70(D_ovl17_07_800457BC, 0x20000000);
}

void func_ovl17_07_80043150(void) {
    UnkStruct_ovl17_07_80045680 *p;
    UnkStructA *obj;

    p = &D_ovl17_07_80045680;
    obj = func_ovl17_07_80044DD0(0x2B2, 0xD0, p->unk4, p->unk6, p->unk8);
    func_ovl17_07_80044DC0(obj);
    func_ovl17_07_80044D88(obj, 0x0D000000);
    p->unk0 = obj;
}

void func_ovl17_07_800430D0(void) {
    s32 i;
    UnkStructA *obj;

    for (i = 0; i < 2; i++) {
        obj = func_ovl17_07_80044DD0(D_ovl17_07_800456E8[i].unk4, 0xD0, D_ovl17_07_800456E8[i].unk8,
                                     D_ovl17_07_800456E8[i].unkC, D_ovl17_07_800456E8[i].unk10);
        func_ovl17_07_80044D88(obj, 0x01000000);
        D_ovl17_07_800456E8[i].unk0 = obj;
    }
}

void func_ovl17_07_80043098(void) {
    func_ovl17_07_80044ED8(func_ovl17_07_80043A70, NULL, 0, 0, 0x110);
}

void func_ovl17_07_80043010(void) {
    UnkStructB *b;
    s32 i;

    b = func_ovl17_07_80044508();
    if (b->unk38 == 1 && b->unk0 == 0) {
        for (i = 0; i < 2; i++) {
            func_ovl17_07_80044ED8(func_ovl17_07_80043C98, &D_ovl17_07_800456E8[i], 0, 0, 0x110);
        }
    }
}
