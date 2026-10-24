/*
 * NON_MATCHING: ovl_12_06's game object, complete: every function and its data
 * (.data and .rodata as the original, .bss 0x50).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 44, eu 44, jp 44
 *
 * IDO -O3: the functions are written last to first (IDO -O3 emits a file's
 * functions in reverse).  func_ovl12_06_80045708 and func_ovl12_06_800456E8
 * are declared s32: as void, the handler and the task take $v0 where the
 * original takes $v1.
 *
 * What still differs in us (words):
 * - func_ovl12_06_80043164 (40): the frame.  The original's is 0xA0, ours
 *   0x88: it has 11 words above obj0 (0x70, ours 0x84) and 5 fewer below
 *   angle, so every stack offset of case 11 differs.  The four inlined
 *   statics (and func_ovl12_06_80043010 inlined in case 1) take 2 words
 *   each below the locals; unused locals only go above.  Case 16/17
 *   written inline with a no-call helper for `->unk10 += 50.0f` gives
 *   their code exactly, but three stubs and a frame still 4 words off.
 *   Also case 2: the original stores D_ovl12_06_80045FBC in the delay slot
 *   of the second call (ours before it, even on one line).
 * - func_ovl12_06_800439D4 (4): the loop over a/b/c keeps its 40 in $s0
 *   and the count in $s3, ours the other way round.
 */
#include "common.h"

/* What func_ovl12_06_80045770 returns (D_ovl12_06_80045FCC). */
typedef struct {
    /* 0x00 */ u8 unk0[0x3C];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ u8 unk48[4];
    /* 0x4C */ f32 unk4C;
} UnkStruct_ovl12_06_80045FCC;

/* What func_ovl12_06_80045D30 returns (D_ovl12_06_80045FC8). */
typedef struct {
    /* 0x00 */ u8 unk0[0x90];
    /* 0x90 */ s32 unk90;
    /* 0x94 */ u8 unk94[0xE];
    /* 0xA2 */ u16 unkA2;
} UnkStruct_ovl12_06_80045FC8;

void func_ovl12_06_80044B98(s32);
void func_ovl12_06_80044BB0(s32);
s32 func_ovl12_06_80044C98(void);
void func_ovl12_06_80044D20(s32, s32);
s32 func_ovl12_06_80044D30(s32);
void func_ovl12_06_80044D38(s32);
void func_ovl12_06_80044D48(void);
void func_ovl12_06_80044D50(s32, s32, s32);
void func_ovl12_06_80044D88(s32);
void func_ovl12_06_80044D90(s32);
void func_ovl12_06_80044DA8(void);
UnkStructA *func_ovl12_06_80044DD8(s32);
void func_ovl12_06_80044E08(s32);
void func_ovl12_06_80044E28(s32, s32);
UnkStructA_40 *func_ovl12_06_80045278(s32, s32);
void func_ovl12_06_80045280(UnkStructA_40 *);
void func_ovl12_06_800452C0(UnkStructA_40 *, s32, s32);
f32 func_ovl12_06_800452D8(UnkStructA_40 *, s32);
void func_ovl12_06_80045300(s32, s32);
void func_ovl12_06_800453D8(f32, f32, f32);
void func_ovl12_06_800453F8(f32, f32, f32);
void func_ovl12_06_80045400(f32 *, f32 *, f32 *);
void func_ovl12_06_80045438(s32);
void func_ovl12_06_80045440(s32);
void func_ovl12_06_80045528(f32 *, f32 *, f32 *);
void func_ovl12_06_80045540(f32 *, f32 *);
void func_ovl12_06_800455A0(UnkStructA *, s32);
void func_ovl12_06_800455B0(UnkStructA *);
UnkStructA *func_ovl12_06_800455C0(s32, s32, s32, s32);
void func_ovl12_06_80045618(UnkStructA *);
s32 func_ovl12_06_800456E8(void (*)(void), s32, s32, s32, s32);
void func_ovl12_06_800456F8(void);
void func_ovl12_06_80045700(u16, s32);
s32 func_ovl12_06_80045708(s32);
void func_ovl12_06_80045730(void);
void func_ovl12_06_80045748(u16);
void func_ovl12_06_80045758(s32, s32, s32);
void func_ovl12_06_80045760(s32, s32);
UnkStruct_ovl12_06_80045FCC *func_ovl12_06_80045770(s32);
void func_ovl12_06_80045780(UnkStruct_ovl12_06_80045FCC *, s32);
f32 func_ovl12_06_80045890(f32);
f32 func_ovl12_06_80045898(f32);
void func_ovl12_06_80045908(void);
void func_ovl12_06_80045910(void);
void func_ovl12_06_80045B38(s32, f32, f32, f32, s32);
void func_ovl12_06_80045C70(s32);
void func_ovl12_06_80045C80(s32);
void func_ovl12_06_80045C88(void);
void func_ovl12_06_80045C90(s32, f32, f32, f32);
void func_ovl12_06_80045D18(s32, s32, s32, s32, s32);
UnkStruct_ovl12_06_80045FC8 *func_ovl12_06_80045D30(s32);
void func_ovl12_06_80045D38(s32);
void func_ovl12_06_80045DE8(void);
void func_ovl12_06_80045DF0(void);

void func_ovl12_06_80043010(void);
void func_ovl12_06_800430D0(void);
void func_ovl12_06_80043164(s32);
void func_ovl12_06_800439D4(void);
void func_ovl12_06_800446A0(void);
void func_ovl12_06_800446F8(s32, UnkStructA *);
void func_ovl12_06_8004472C(f32);
void func_ovl12_06_80044774(f32, f32, f32);
void func_ovl12_06_800447D0(void);
void func_ovl12_06_800447E8(void);
static f32 func_ovl12_06_80043068(UnkStructA_40 *from, UnkStructA_40 *to);

/* .bss */
u8 D_ovl12_06_80045F80[0x24];
s32 D_ovl12_06_80045FA4;
s32 D_ovl12_06_80045FA8;
u8 D_ovl12_06_80045FAC[0x4];
Vec3f D_ovl12_06_80045FB0;
s32 D_ovl12_06_80045FBC;
s32 D_ovl12_06_80045FC0;
s32 D_ovl12_06_80045FC4;
UnkStruct_ovl12_06_80045FC8 *D_ovl12_06_80045FC8;
UnkStruct_ovl12_06_80045FCC *D_ovl12_06_80045FCC;

/* an angle in degrees moved by d and kept in [0, 360) */
#define ANGLE_ADD(a, d) \
    (a) = ((a) + (d) >= 360.0f) ? (a) + (d) - 360.0f : ((a) + (d) < 0.0f) ? (a) + (d) + 360.0f : (a) + (d)
#define ANGLE_SUB(a, d) \
    (a) = ((a) - (d) >= 360.0f) ? (a) - (d) - 360.0f : ((a) < (d)) ? (a) - (d) + 360.0f : (a) - (d)

/* unused: the stubs IDO -O3 leaves at the end of the object; the last one
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl12_06_80044848(void) {
    D_ovl12_06_80045F80[0] = D_ovl12_06_80045FAC[0];
}

static void func_ovl12_06_80044840(void) {
}

static void func_ovl12_06_80044838(void) {
}

static void func_ovl12_06_80044830(void) {
}

static void func_ovl12_06_80044828(void) {
}

static void func_ovl12_06_80044820(void) {
}

static void func_ovl12_06_80044818(void) {
}

static void func_ovl12_06_80044810(void) {
}

static void func_ovl12_06_80044808(void) {
}

static void func_ovl12_06_80044800(void) {
}

static void func_ovl12_06_800447F8(void) {
}

void func_ovl12_06_800447E8(void) {
}

void func_ovl12_06_800447D0(void) {
    D_ovl12_06_80045FA4 = -1;
    D_ovl12_06_80045FA8 = -1;
}

void func_ovl12_06_80044774(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl12_06_800453D8(D_ovl12_06_80045FB0.x, D_ovl12_06_80045FB0.y, D_ovl12_06_80045FB0.z);
    func_ovl12_06_800453F8(arg0, arg1, arg2);
    func_ovl12_06_80045708(180);
}

void func_ovl12_06_8004472C(f32 arg0) {
    f32 sp1C;

    func_ovl12_06_80045400(&sp1C, NULL, NULL);
    func_ovl12_06_800453F8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl12_06_800446F8(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl12_06_80045C90(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl12_06_800446A0(void) {
    if (D_ovl12_06_80045FBC == 0x10) {
        func_ovl12_06_80045708(0x14F);
        func_ovl12_06_80045C80(10);
    } else {
        func_ovl12_06_80045708(45);
        func_ovl12_06_80045C80(18);
    }
    func_ovl12_06_800456F8();
}

void func_ovl12_06_800439D4(void) {
    UnkStructA *obj;
    UnkStructA *spr;
    s32 i;
    UnkStructA_40 *objs[4];
    s32 j;
    s32 k;
    f32 angle;
    f32 a[3] = { 315.0f, 45.0f, 0.0f };
    f32 b[3] = { 330.0f, 330.0f, 20.0f };
    f32 c[3] = { 315.0f, 0.0f, 45.0f };

    func_ovl12_06_80044DD8(0);
    obj = func_ovl12_06_80044DD8(1);
    func_ovl12_06_80045708(60);
    func_ovl12_06_80045C70(0x23B);
    obj->unk40->unk14 = 1000.0f;
    obj->unk40->unk10 += 10.0f;
    for (i = 0; i < 4; i++) {
        objs[i] = func_ovl12_06_80045278(0x307, 0);
        objs[i]->unkC |= 0x80;
        objs[i]->unk36 = 60;
        objs[i]->unk10 = 2650.0f;
        objs[i]->unk14 = 900.0f;
        objs[i]->unk18 = 500.0f;
        objs[i]->unk1C = 90.0f;
        objs[i]->unk28 = objs[i]->unk2C = objs[i]->unk30 = (i + 1) * 0.5f;
    }
    angle = 45.0f;
    for (i = 0; i < 180; i++) {
        func_ovl12_06_800453F8(32768.0f, angle, 32768.0f);
        ANGLE_SUB(angle, 0.33333334f);
        for (j = 0; j < 4; j++) {
            objs[j]->unk10 -= (j + 1) * 5.0f;
            objs[j]->unk14 -= (j + 1) * 5.0f;
        }
        func_ovl12_06_80045730();
    }
    for (i = 0; i != 4; i++) {
        func_ovl12_06_80045280(objs[i]);
    }
    func_ovl12_06_80045708(30);
    func_ovl12_06_800453D8(obj->unk40->unk10, obj->unk40->unk14 + 50.0f, obj->unk40->unk18);
    for (i = 0; i < 3; i++) {
        angle = 2250.0f;
        for (j = 0; j < 40; j++) {
            if (D_ovl12_06_80045FBC == 0x1B) {
                func_ovl12_06_800453F8(c[i], b[i], angle);
            } else {
                func_ovl12_06_800453F8(a[i], b[i], angle);
            }
            angle -= 42.5f;
            func_ovl12_06_80045730();
        }
    }
    func_ovl12_06_800452C0(obj->unk40, 0x21, 0);
    func_ovl12_06_800452C0(obj->unk40, -1, 1);
    obj->unk40->unk48->unk4->unk8 |= 0x20;
    obj->unk40->unk48->unk4->unk8 &= ~0x40;
    func_ovl12_06_80045708(17);
    func_ovl12_06_80045C70(0x239);
    func_ovl12_06_80045708(16);
    func_ovl12_06_80045C70(0x239);
    func_ovl12_06_80045708(16);
    func_ovl12_06_80045C70(0x239);
    while (!(obj->unk40->unk48->unk4->unk8 & 0x40)) {
        func_ovl12_06_80045730();
    }
    if (D_ovl12_06_80045FBC == 0x1A) {
        func_ovl12_06_80045708(30);
        func_ovl12_06_80045DE8();
        D_ovl12_06_80045FC0 = 0;
        func_ovl12_06_800456F8();
    } else if (D_ovl12_06_80045FBC == 0x1B) {
        func_ovl12_06_80044E28(1, 1);
        obj->unk40->unk48->unk4->unk8 |= 0x40;
        k = 0;
        obj->unk40->unk48->unk4->unk14 |= 0x40;
        obj->unk68 = 0.0f;
        obj->unk6C = 0.0f;
        obj->unk70 = 0.0f;
        for (i = 0; i < 6; i++) {
            for (angle = 0.0f; angle < func_ovl12_06_800452D8(obj->unk40, 0); angle += 4.0f) {
                obj->unk40->unk48->unk4->unk4 = angle;
                obj->unk40->unk48->unk4->unk10 = angle;
                obj->unk40->unk1C = func_ovl12_06_80045898(k) * 25.0f;
                ANGLE_ADD(k, 10);
                func_ovl12_06_80045730();
            }
        }
        func_ovl12_06_80044E28(1, 0x13);
        func_ovl12_06_80045B38(0, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, 0);
        for (i = 0; i < 20; i++) {
            obj->unk40->unk18 += 5.0f;
            ANGLE_SUB(obj->unk40->unk1C, 2.5f);
            func_ovl12_06_80045730();
        }
        func_ovl12_06_80045708(20);
        spr = func_ovl12_06_800455C0(0x2D1, 0x01000000, 0xD0, 0);
        spr->unk40->unk1C = 270.0f;
        spr->unk40->unk20 = 0.0f;
        spr->unk40->unk2C = 0.2f;
        spr->unk40->unk28 = spr->unk40->unk2C;
        spr->unk40->unk30 = 0.1f;
        spr->unk40->unk10 = 2641.0f;
        spr->unk40->unk14 = 1080.0f;
        spr->unk40->unk18 = 415.0f;
        for (i = 0; i < 40; i++) {
            spr->unk40->unk30 += 0.05f;
            spr->unk40->unk14 -= 0.5f;
            func_ovl12_06_80045730();
        }
        func_ovl12_06_80045708(60);
        func_ovl12_06_800455B0(spr);
        for (i = 0; i < 30; i++) {
            obj->unk40->unk14 -= 26.666666f;
            func_ovl12_06_80045730();
        }
        func_ovl12_06_80045708(30);
        func_ovl12_06_80045DE8();
        D_ovl12_06_80045FC0 = 0;
        func_ovl12_06_800456F8();
    }
    angle = 0.0f;
    for (i = 0; i < 120; i++) {
        func_ovl12_06_800453F8(angle, func_ovl12_06_80045890(angle) * 20.0f + 20.0f, 32768.0f);
        ANGLE_ADD(angle, 2.25f);
        func_ovl12_06_80045730();
    }
    func_ovl12_06_80045760(0x70, 0x70);
    func_ovl12_06_800452C0(obj->unk40, 0x16, 0);
    func_ovl12_06_800452C0(obj->unk40, -1, 1);
    obj->unk40->unk48->unk4->unk8 |= 0x20;
    obj->unk40->unk48->unk4->unk8 &= ~0x40;
    for (i = 0; i < 7; i++) {
        func_ovl12_06_800453F8(angle, func_ovl12_06_80045890(angle) * 20.0f + 20.0f, 32768.0f);
        ANGLE_ADD(angle, 2.25f);
        func_ovl12_06_80045730();
    }
    obj->unk68 = 20.0f;
    obj->unk70 = 1.6333334f;
    for (i = 0; i < 30; i++) {
        if (i == 5) {
            obj->unk40->unk48->unk4->unk8 |= 0x40;
        }
        obj->unk40->unk10 -= 8.333333f;
        obj->unk40->unk18 += 20; /* an int: 20.0f shares the $f22 of the camera's 20.0f */
        func_ovl12_06_800453D8(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
        func_ovl12_06_800453F8(angle, func_ovl12_06_80045890(angle) * 20.0f + 20.0f, 32768.0f);
        ANGLE_ADD(angle, 2.25f);
        func_ovl12_06_80045730();
    }
    func_ovl12_06_80045438(16);
    func_ovl12_06_80045440(15);
    func_ovl12_06_80045D38(1);
    while (obj->unk68 != 0.0f) {
        func_ovl12_06_80045730();
    }
    func_ovl12_06_80045708(60);
    func_ovl12_06_80045758(0x70, 0x70, 0);
    func_ovl12_06_80044E08(1);
    func_ovl12_06_80044D88(0);
    func_ovl12_06_80044E08(0);
    D_ovl12_06_80045FC0 = 0;
    func_ovl12_06_80045748(D_ovl12_06_80045FC8->unkA2);
    func_ovl12_06_800456F8();
}

/* The handler's cases 2, 16/26/27, 17 and 4: statics inlined into it, each
 * leaving its `jr ra; nop` stub just before it. */
static void func_ovl12_06_80043144(void) {
    D_ovl12_06_80045FBC = func_ovl12_06_80044C98();
    func_ovl12_06_80044B98(0x236);
    func_ovl12_06_80044BB0(0x241);
    func_ovl12_06_80044D48();
    D_ovl12_06_80045FCC = func_ovl12_06_80045770(0x279);
    func_ovl12_06_80045780(D_ovl12_06_80045FCC, 0x20000000);
    D_ovl12_06_80045FCC->unk40 = 0.5f;
    D_ovl12_06_80045FCC->unk44 = D_ovl12_06_80045FCC->unk40 * 0.75f;
    D_ovl12_06_80045FCC->unk3C = D_ovl12_06_80045FCC->unk4C * 0.25f;
    D_ovl12_06_80045FC0 = 1;
    D_ovl12_06_80045FC4 = 0;
    func_ovl12_06_80045908();
}

static void func_ovl12_06_8004314C(void) {
    func_ovl12_06_80044D50(0x17, 0, 0xF);
    func_ovl12_06_80044D90(0);
    func_ovl12_06_80045D18(1, 3, 0x1A, 2, 3);
    D_ovl12_06_80045FC8 = func_ovl12_06_80045D30(1);
    D_ovl12_06_80045FC8->unk90 = 60;
    func_ovl12_06_80045700(D_ovl12_06_80045FC8->unkA2, 0);
    func_ovl12_06_80045D38(0);
    func_ovl12_06_80044E08(1);
    func_ovl12_06_80044D88(1);
    func_ovl12_06_80044E08(0);
    func_ovl12_06_80044DD8(0)->unk40->unk10 += 50.0f;
    func_ovl12_06_80044DA8();
    func_ovl12_06_80045440(0x1F);
    func_ovl12_06_800453D8(2350.0f, 529.0f, 1500.0f);
    func_ovl12_06_800453F8(0.0f, 45.0f, 2000.0f);
    func_ovl12_06_80044D20(0x62, 0x11);
    func_ovl12_06_80044D88(1);
}

static void func_ovl12_06_80043154(void) {
    func_ovl12_06_80045D18(1, 3, 0x17, 0, 9);
    D_ovl12_06_80045FC8 = func_ovl12_06_80045D30(1);
    D_ovl12_06_80045FC8->unk90 = 180;
    func_ovl12_06_80044D50(0x17, 0, 0xF);
    func_ovl12_06_80044D90(0);
    func_ovl12_06_80044DD8(0)->unk40->unk10 += 50.0f;
    func_ovl12_06_80044DD8(1)->unk40->unk10 += 50.0f;
    func_ovl12_06_80044DA8();
    func_ovl12_06_80045440(0xF);
}

static void func_ovl12_06_8004315C(void) {
    if (D_ovl12_06_80045FBC != 0x1A && D_ovl12_06_80045FBC != 0x1B) {
        func_ovl12_06_800456E8(func_ovl12_06_800446A0, 0, 0, 0, 0x130);
    }
    /* `0x1A == ...`: the original's `beq v1,s0` (the other way round it's `beq s0,v1`) */
    if (D_ovl12_06_80045FBC == 0x10 || 0x1A == D_ovl12_06_80045FBC || D_ovl12_06_80045FBC == 0x1B) {
        func_ovl12_06_800456E8(func_ovl12_06_800439D4, 0, 0, 0, 0x130);
    }
}

/* inlined into func_ovl12_06_800430D0, its stub just before it */
static void func_ovl12_06_800430C8(void) {
    while (D_ovl12_06_80045FC0 != 0) {
        func_ovl12_06_80045730();
    }
}

void func_ovl12_06_800430D0(void) {
    if (D_ovl12_06_80045FBC == 0x10 || D_ovl12_06_80045FBC == 0x1A || D_ovl12_06_80045FBC == 0x1B) {
        func_ovl12_06_800430C8();
        func_ovl12_06_80044D88(0);
    }
    /* empty: without it the function is small enough to be inlined into
     * the handler (ovl_12_02's and 12_04's case 5 keep the same test) */
    if (D_ovl12_06_80045FBC == 2) {
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl12_06_80043164(s32 arg0) {
    UnkStructA *obj0;
    Vec3f pos;
    Vec3f target;
    UnkStructA *obj1;
    s32 i;
    f32 angle;

    switch (arg0) {
        case 2:
            func_ovl12_06_80043144();
            break;
        case 16:
        case 26:
        case 27:
            func_ovl12_06_8004314C();
            break;
        case 17:
            func_ovl12_06_80043154();
            break;
        case 4:
            func_ovl12_06_8004315C();
            break;
        case 5:
            func_ovl12_06_800430D0();
            break;
        case 11:
            func_ovl12_06_80044D88(1);
            func_ovl12_06_80045440(0x1F);
            func_ovl12_06_80045D38(0);
            func_ovl12_06_800453D8(2350.0f, 100.0f, 1720.0f);
            func_ovl12_06_800453F8(0.0f, 45.0f, 2000.0f);
            func_ovl12_06_80045708(2);
            obj1 = func_ovl12_06_80044DD8(1);
            obj0 = func_ovl12_06_80044DD8(0);
            func_ovl12_06_800455A0(obj1, 0x0C000000);
            func_ovl12_06_800452C0(obj1->unk40, 0, 0);
            func_ovl12_06_800452C0(obj1->unk40, -1, 1);
            obj1->unk40->unk20 = func_ovl12_06_80043068(obj1->unk40, obj0->unk40);
            if (func_ovl12_06_80044D30(1) == 3) {
                pos.x = obj0->unk40->unk10;
                pos.y = obj0->unk40->unk14;
                pos.z = obj0->unk40->unk18;
                target.x = 2350.0f;
                target.y = 0.0f;
                target.z = 1550.0f;
                func_ovl12_06_80045528(&pos.x, &target.x, &angle);
                target.x = func_ovl12_06_80045890(angle) * 800.0f + pos.x;
                target.y = pos.y;
                target.z = func_ovl12_06_80045898(angle) * 800.0f + pos.z;
                pos.x = obj1->unk40->unk10;
                pos.y = obj1->unk40->unk14;
                pos.z = obj1->unk40->unk18;
                func_ovl12_06_80045528(&pos.x, &target.x, &angle);
                func_ovl12_06_80045540(&pos.x, &target.x);
                obj1->unk68 = 51.0f;
                obj1->unk40->unk14 = 0.1f;
                obj1->unk70 = 0.8166667f;
                obj1->unk6C = 16.333334f;
                for (i = 0; i < 90; i++) {
                    obj1->unk40->unk10 += (target.x - pos.x) / 90.0f;
                    obj1->unk40->unk18 += (target.z - pos.z) / 90.0f;
                    if (obj1->unk40->unk14 < 0.0f) {
                        obj1->unk70 = 0.0f;
                        obj1->unk68 = 0.0f;
                        obj1->unk40->unk14 = 0.0f;
                    } else {
                        func_ovl12_06_80045618(obj1);
                    }
                    func_ovl12_06_80045730();
                }
                func_ovl12_06_80045C70(0x259);
            }
            obj1->unk40->unk20 = func_ovl12_06_80043068(obj1->unk40, obj0->unk40);
            obj0->unk40->unk20 = func_ovl12_06_80043068(obj0->unk40, obj1->unk40);
            func_ovl12_06_800453D8(obj0->unk40->unk10, 200.0f, obj0->unk40->unk18);
            func_ovl12_06_800453F8(obj1->unk40->unk20, 20.0f, 800.0f);
            for (i = 0; i < 30; i++) {
                obj1->unk40->unk14 += 2.0f;
                func_ovl12_06_80045730();
            }
            func_ovl12_06_80045708(30);
            func_ovl12_06_80045300(0x334, 1);
            func_ovl12_06_80044D88(1);
            func_ovl12_06_80044D38(50);
            func_ovl12_06_80045C88();
            func_ovl12_06_80045708(60);
            obj1->unk40->unkC |= 0x4000;
            func_ovl12_06_800452C0(obj1->unk40, 0x1C, 0);
            func_ovl12_06_800452C0(obj1->unk40, -1, 1);
            obj1->unk40->unk48->unk4->unk8 |= 0x20;
            while (!(obj1->unk40->unk48->unk4->unk8 & 0x40)) {
                func_ovl12_06_80045730();
            }
            func_ovl12_06_80045C70(0x20F);
            for (i = 0; i < 40; i++) {
                obj1->unk40->unk14 += 25.0f;
                func_ovl12_06_80045730();
            }
            func_ovl12_06_800455A0(obj1, 0x01000000);
            func_ovl12_06_800453D8(obj0->unk40->unk10, 50.0f, obj0->unk40->unk18);
            func_ovl12_06_800453F8(obj0->unk40->unk20, 20.0f, 800.0f);
            func_ovl12_06_80044D88(0);
            func_ovl12_06_80044D38(32);
            func_ovl12_06_80045910();
            D_ovl12_06_80045FC4 = 1;
            break;
        case 1:
            func_ovl12_06_80043010();
            break;
    }
}

/* A static: its callers pass `from` in a3 and `to` in t0.  Defined below
 * the handler, it still comes out here, ahead of func_ovl12_06_800430D0. */
static f32 func_ovl12_06_80043068(UnkStructA_40 *from, UnkStructA_40 *to) {
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
    func_ovl12_06_80045528(&a.x, &b.x, &angle);
    return angle;
}

void func_ovl12_06_80043010(void) {
    if (D_ovl12_06_80045FBC == 0x1A || D_ovl12_06_80045FBC == 0x1B) {
        func_ovl12_06_80045DF0();
    }
    if (D_ovl12_06_80045FC4 == 0) {
        func_ovl12_06_80045910();
    }
}
