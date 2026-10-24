#include "common.h"

/*
 * ovl_0E_11's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Much of it is ovl_0E_12's
 * and ovl_0E_13's code.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_11_80046500;

/* an object placed at set-up, with a collision box (unkC-unk12, -1 for none) */
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
} UnkStruct_ovl0E_11_8004625C;

/* the four movers: each record is passed to its task */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} UnkStruct_ovl0E_11_800463AC;

void func_ovl0E_11_80044F28(s32);
void func_ovl0E_11_80044F40(s32);
f32 func_ovl0E_11_80044F50(void);
void func_ovl0E_11_80044F68(s32, s32, s32, s32, s32, s32);
void func_ovl0E_11_80044FB0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_11_80045010(void (*)(UnkStructA *));
void func_ovl0E_11_80045020(s32, s32, s32);
void func_ovl0E_11_80045060(void (*)(UnkStructA *));
void func_ovl0E_11_80045090(s32);
void func_ovl0E_11_80045098(s32);
void func_ovl0E_11_800450D8(void);
void func_ovl0E_11_800450E0(s32, s32, s32);
void func_ovl0E_11_800450E8(void *);
s32 func_ovl0E_11_800450F0(s32, s32, s32, s32);
s32 func_ovl0E_11_80045108(void);
void func_ovl0E_11_80045110(s32, void *);
void func_ovl0E_11_80045118(s32);
void func_ovl0E_11_80045120(s32);
void func_ovl0E_11_80045128(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_11_80045138(void);
void func_ovl0E_11_80045170(s32);
void func_ovl0E_11_80045630(UnkStructA_40 *, s32);
void func_ovl0E_11_80045638(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl0E_11_80045670(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_11_80045678(s32);
void func_ovl0E_11_80045768(f32, f32, f32);
void func_ovl0E_11_80045788(f32, f32, f32);
void func_ovl0E_11_80045790(f32 *, f32 *, f32 *);
void func_ovl0E_11_800457C8(s32);
void func_ovl0E_11_800457D0(s32);
void func_ovl0E_11_80045858(void *);
void func_ovl0E_11_80045888(void);
void func_ovl0E_11_80045890(void);
f32 func_ovl0E_11_800458D0(f32 *, void *);
void func_ovl0E_11_80045928(UnkStructA *, s32);
void func_ovl0E_11_80045930(UnkStructA *, s32);
void func_ovl0E_11_80045940(UnkStructA *);
UnkStructA *func_ovl0E_11_80045960(UnkStructA *);
UnkStructA *func_ovl0E_11_80045970(s32, s32, f32, f32, f32);
void func_ovl0E_11_800459A8(UnkStructA *);
void func_ovl0E_11_80045A38(UnkStructA *);
s32 func_ovl0E_11_80045A78(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_11_80045A80(s32);
void func_ovl0E_11_80045A88(void);
void func_ovl0E_11_80045A98(s32);
void *func_ovl0E_11_80045AA0(void);
void func_ovl0E_11_80045AC0(void);
s32 func_ovl0E_11_80045C38(s32);
void func_ovl0E_11_80045CF0(s32);
void func_ovl0E_11_80045CF8(s32);
s32 func_ovl0E_11_80045D00(s32);
void func_ovl0E_11_80045DB8(s32, s32, s32, s32, s32);
void func_ovl0E_11_80045DC8(s32, s32, s32);
void func_ovl0E_11_80045DE0(u32 (*)[3]);
void func_ovl0E_11_80045ED0(s32, f32 *, s32);
void func_ovl0E_11_80045F40(s32, s32, s32, s32);
void func_ovl0E_11_80045F88(s32, s32, s32);
void func_ovl0E_11_80046000(s32);
void func_ovl0E_11_80046020(s32, f32, f32, f32);
void func_ovl0E_11_80046028(s32, f32 *);

void func_ovl0E_11_80043010(void);
void func_ovl0E_11_80043018(void);
void func_ovl0E_11_80043100(void);
void func_ovl0E_11_80043160(void);
void func_ovl0E_11_800431C0(void);
void func_ovl0E_11_800431F0(void);
void func_ovl0E_11_80043210(void);
void func_ovl0E_11_80043230(void);
void func_ovl0E_11_8004326C(void);
void func_ovl0E_11_80043328(void);
void func_ovl0E_11_80043370(void);
void func_ovl0E_11_800433C8(void);
void func_ovl0E_11_80043400(void);
void func_ovl0E_11_80043498(void);
void func_ovl0E_11_800434D0(void);
void func_ovl0E_11_800436D4(s16, s32);
void func_ovl0E_11_80043758(s16, s16, s32, s32, s32, s32, s32);
void func_ovl0E_11_800437DC(void);
void func_ovl0E_11_80043934(void);
void func_ovl0E_11_800439CC(void);
void func_ovl0E_11_80043A44(void);
void func_ovl0E_11_80043ABC(void);
void func_ovl0E_11_80043AE4(f32);
void func_ovl0E_11_80043B2C(void);
void func_ovl0E_11_80043C44(void);
void func_ovl0E_11_80043C64(s32, s32, s32, f32, s32);
void func_ovl0E_11_80043C8C(void);
void func_ovl0E_11_80043CDC(void);
void func_ovl0E_11_80043D2C(void);
void func_ovl0E_11_80043D78(void);
void func_ovl0E_11_80043E88(void);
void func_ovl0E_11_80043F70(void);
void func_ovl0E_11_80044034(void);
void func_ovl0E_11_8004417C(void);
void func_ovl0E_11_80044184(void);
void func_ovl0E_11_800441C4(void);
void func_ovl0E_11_800441FC(void);
void func_ovl0E_11_80044384(s32);
void func_ovl0E_11_800444F4(void);
void func_ovl0E_11_8004479C(UnkStructA *);
void func_ovl0E_11_80044860(UnkStructA *);
void func_ovl0E_11_800448F8(void);
void func_ovl0E_11_80044A5C(void);
void func_ovl0E_11_80044AF8(s32, UnkStructA *);
void func_ovl0E_11_80044B2C(f32, f32, f32);
void func_ovl0E_11_80044B88(void);
void func_ovl0E_11_80044BA0(void);

/* the two that take their record in s0 (IDO -O3's static calls) */
static void func_ovl0E_11_80043084(UnkStruct_ovl0E_11_8004625C *);
static void func_ovl0E_11_80043554(UnkStruct_ovl0E_11_8004625C *);
/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0E_11_80043320(void);
static void func_ovl0E_11_800433C0(void);
static void func_ovl0E_11_8004392C(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_11_80043328() \
    D_ovl0E_11_800464DC = func_ovl0E_11_80045108(); func_ovl0E_11_800450E8(&D_ovl0E_11_800464D0); func_ovl0E_11_80045110(D_ovl0E_11_800464DC, D_ovl0E_11_800464C0)

/* .bss */
u8 D_ovl0E_11_800464C0[0x10];
Vec3f D_ovl0E_11_800464D0;
s32 D_ovl0E_11_800464DC;
u8 D_ovl0E_11_800464E0[0x4]; /* unused (func_ovl0E_11_80044BD0) */
s32 D_ovl0E_11_800464E4;
s32 D_ovl0E_11_800464E8;
u8 D_ovl0E_11_800464EC[0x4]; /* unused (func_ovl0E_11_80044BD0) */
Vec3f D_ovl0E_11_800464F0;
UnkStructA *D_ovl0E_11_800464FC;
UnkStruct_ovl0E_11_80046500 D_ovl0E_11_80046500;

/* .data */
/* passed to func_ovl0E_11_80045DE0: three 12-byte records */
u32 D_ovl0E_11_80046220[][3] = {
    { 0xA20002, 0xE, 4 },
    { 0x9F0003, 0xE, 4 },
    { 0xA10002, 0xE, 4 },
};
/* two 12-byte records, each passed to func_ovl0E_11_80045F88 */
u32 D_ovl0E_11_80046244[][3] = {
    { 0, 0xE, 0xEC },
    { 1, 0, 0xDE },
};
UnkStruct_ovl0E_11_8004625C D_ovl0E_11_8004625C[5] = {
    { NULL, -1, 0x1B3, -1, -1, -1, -1, 350.0f, 120.2f, 50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B3, -1, -1, -1, -1, 350.0f, 0.2f, 220.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B3, -1, -1, -1, -1, 230.0f, 70.2f, 170.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B3, -1, -1, -1, -1, 210.0f, 120.2f, 190.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { NULL, -1, 0x1B4, -1, -1, -1, -1, 140.0f, 70.2f, 100.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_11_8004625C D_ovl0E_11_80046374[1] = {
    { NULL, -1, 0x1B1, -1, -1, -1, -1, 110.0f, 60.0f, 70.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_11_800463AC D_ovl0E_11_800463AC[4] = {
    { -1, NULL, 0x1B6, 0x20, 0x30, 0.0f, 15.0f, 1, 0x1E, 250.0f, 500.0f, 50.0f },
    { -1, NULL, 0x1B6, 0x20, 0x30, 0.0f, 15.0f, 1, 0x1E, 280.0f, 500.0f, 50.0f },
    { -1, NULL, 0x1B6, 0x20, 0x30, 0.0f, 15.0f, 1, 0x1E, 310.0f, 500.0f, 50.0f },
    { -1, NULL, 0x1B6, 0x20, 0x30, 0.0f, 15.0f, 1, 0x1E, 340.0f, 500.0f, 50.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0E_11_80044BD0(void) {
    D_ovl0E_11_800464E0[0] = D_ovl0E_11_800464EC[0];
}

/* Its reference to func_ovl0E_11_80044A5C keeps the tasks
 * (func_ovl0E_11_800444F4 to 80044A5C) in address order after the handler;
 * without it IDO puts the ones whose address is taken in inlined code
 * (80044A5C, 800448F8) first. Any reference to either of the two up here
 * does it; the body itself isn't emitted. */
static void func_ovl0E_11_80044BC8(void) {
    func_ovl0E_11_80045A78(func_ovl0E_11_80044A5C, NULL, 0, 0, 0);
}

static void func_ovl0E_11_80044BC0(void) {
}

static void func_ovl0E_11_80044BB8(void) {
}

static void func_ovl0E_11_80044BB0(void) {
}

static void func_ovl0E_11_80044BA8(void) {
}

void func_ovl0E_11_80044BA0(void) {
}

void func_ovl0E_11_80044B88(void) {
    D_ovl0E_11_800464E4 = -1;
    D_ovl0E_11_800464E8 = -1;
}

void func_ovl0E_11_80044B2C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_11_80045768(D_ovl0E_11_800464F0.x, D_ovl0E_11_800464F0.y, D_ovl0E_11_800464F0.z);
    func_ovl0E_11_80045788(arg0, arg1, arg2);
    func_ovl0E_11_80045A98(180);
}

void func_ovl0E_11_80044AF8(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_11_80046020(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_11_80044A5C(void) {
    s32 i;

    for (i = 30; i != 0; i--) {
        func_ovl0E_11_80045AC0();
    }
    func_ovl0E_11_80045928(D_ovl0E_11_80046374[0].unk0, 0x04000000);
    func_ovl0E_11_80046000(0x76);
    while (TRUE) {
        if (D_ovl0E_11_80046374[0].unk0->unk40->unkC & 0x40) {
            break;
        }
        func_ovl0E_11_80045AC0();
    }
    func_ovl0E_11_80045118(0);
    func_ovl0E_11_80045090(1);
    func_ovl0E_11_80045A88();
}

void func_ovl0E_11_800448F8(void) {
    s32 i;

    for (i = 60; i != 0; i--) {
        func_ovl0E_11_80045AC0();
    }
    func_ovl0E_11_80045CF0(0x40C);
    func_ovl0E_11_80045098(1);
    func_ovl0E_11_80045090(0);
    func_ovl0E_11_80045118(1);
    func_ovl0E_11_80045888();
    func_ovl0E_11_800457D0(0x7F);
    func_ovl0E_11_80045768(1200.0f, 600.0f, 1000.0f);
    func_ovl0E_11_80045788(90.0f, 45.0f, 1500.0f);
    func_ovl0E_11_80045A98(30);
    func_ovl0E_11_80046000(0x84);
    func_ovl0E_11_80043F70();
    D_ovl0E_11_800464FC->unk40->unk36 = 0;
    for (i = 60; i != 0; i--) {
        D_ovl0E_11_800464FC->unk40->unk36 += 4;
        func_ovl0E_11_80045AC0();
    }
    D_ovl0E_11_800464FC->unk40->unk36 = 0xFF;
    func_ovl0E_11_800436D4(4, 0x1B2);
    func_ovl0E_11_80045A98(30);
    func_ovl0E_11_80045890();
    func_ovl0E_11_80045858(D_ovl0E_11_800464C0);
    func_ovl0E_11_800457C8(0x1F);
    func_ovl0E_11_80045098(0);
    func_ovl0E_11_80045090(1);
    func_ovl0E_11_80045118(0);
    func_ovl0E_11_80045A88();
}

void func_ovl0E_11_80044860(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_11_80045930(arg0, 0x01000000);
    func_ovl0E_11_80045ED0(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_11_80045ED0(13, pos, 0);
    func_ovl0E_11_80046028(180, pos);
}

void func_ovl0E_11_8004479C(UnkStructA *arg0) {
    func_ovl0E_11_80045930(arg0, 0x04000000);
    func_ovl0E_11_80045A98(10);
    func_ovl0E_11_80044FB0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_11_80046000(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_11_80045A98(60);
}

void func_ovl0E_11_800444F4(void) {
    UnkStruct_ovl0E_11_800463AC *rec;
    UnkStructA *obj;
    s16 moving;
    f32 pos[3];
    s32 heard;

    rec = func_ovl0E_11_80045AA0();
    obj = rec->unk4;
    func_ovl0E_11_80045A98(func_ovl0E_11_80045C38(120));
    for (heard = 0, moving = 0;;) {
        obj->unk40->unk10 = rec->unk1C * 10.0f;
        obj->unk40->unk14 = rec->unk20 * 10.0f;
        obj->unk40->unk18 = rec->unk24 * 10.0f;
        obj->unk68 = 0.0f;
        obj->unk70 = 1.6333334f;
        func_ovl0E_11_80045928(obj, 0x01000000);
        while (TRUE) {
            func_ovl0E_11_80045A38(obj);
            if (moving == 1) {
                obj->unk40->unk10 += rec->unk10;
                obj->unk40->unk18 += rec->unk14;
            }
            func_ovl0E_11_800459A8(obj);
            if (obj->unk6C == 0.0f && obj->unk68 == 0.0f) {
                if (heard == 0) {
                    pos[0] = obj->unk40->unk10;
                    pos[1] = obj->unk40->unk14;
                    pos[2] = obj->unk40->unk18;
                    if (func_ovl0E_11_800458D0(pos, D_ovl0E_11_800464C0) < 700.0f) {
                        func_ovl0E_11_80046020(0x78, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
                        heard = 1;
                    }
                }
                moving = 1;
            }
            if (obj->unk40->unk14 <= func_ovl0E_11_80044F50()) {
                func_ovl0E_11_80045930(obj, 0x01000000);
                heard = 0;
                moving = 0;
                break;
            }
            func_ovl0E_11_80045AC0();
        }
        func_ovl0E_11_80045A98(func_ovl0E_11_80045C38(rec->unk1A - rec->unk18) + rec->unk18);
    }
}

void func_ovl0E_11_800441FC(void) {
    UnkStructA *obj;
    UnkStructA *obj2;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_11_80044184();
    func_ovl0E_11_80045010(func_ovl0E_11_80044860);
    func_ovl0E_11_80045060(func_ovl0E_11_8004479C);
    func_ovl0E_11_80045DE0(D_ovl0E_11_80046220);
    func_ovl0E_11_80044F28(0x19D);
    obj = func_ovl0E_11_80045970(0x19E, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_11_80045928(obj, 0x01000000);
    obj2 = func_ovl0E_11_80045970(0x19F, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_11_80045928(obj2, 0x01000000);
    p = D_ovl0E_11_80046244;
    count = 2;
    for (i = 0; i < count; i++) {
        func_ovl0E_11_80045F88((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_11_80044F40(0x1A7);
    func_ovl0E_11_800450D8();
    func_ovl0E_11_80044034();
    func_ovl0E_11_80043E88();
    func_ovl0E_11_80043D78();
    func_ovl0E_11_80045670(obj->unk40, 0, 2, 0x400, 0, 0);
    func_ovl0E_11_80045670(obj2->unk40, 0, 0, 0, 0xF, 0x400);
    func_ovl0E_11_80045DB8(0x393, 0x3DE, 0xFF, 0x87, 0x1F);
    func_ovl0E_11_80045DC8(0xFF, 0xA1, 0x1D);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_11_80044384(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0E_11_800441FC();
            break;
        case 17:
            func_ovl0E_11_80043D2C();
            break;
        case 18:
            func_ovl0E_11_80043CDC();
            break;
        case 19:
            func_ovl0E_11_80043C8C();
            break;
        case 4:
            func_ovl0E_11_80043C44();
            break;
        case 5:
            func_ovl0E_11_80043ABC();
            break;
        case 0x50:
            func_ovl0E_11_80043934();
            break;
        case 0x52:
            func_ovl0E_11_800437DC();
            break;
        case 3:
            func_ovl0E_11_80043370();
            break;
        case 12:
            func_ovl0E_11_80043210();
            break;
        case 1:
            func_ovl0E_11_800431C0();
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_11_800441C4(void) {
    func_ovl0E_11_80044184();
    func_ovl0E_11_80045010(func_ovl0E_11_80044860);
    func_ovl0E_11_80045060(func_ovl0E_11_8004479C);
}

void func_ovl0E_11_80044184(void) {
    func_ovl0E_11_80045CF8(0x400);
    func_ovl0E_11_80045CF8(0x401);
    func_ovl0E_11_80045CF8(0x402);
    func_ovl0E_11_80045CF8(0x403);
    func_ovl0E_11_80045CF8(0x404);
}

void func_ovl0E_11_8004417C(void) {
}

void func_ovl0E_11_80044034(void) {
    s32 i;
    s32 flag;

    for (i = 0; i < 5; i++) {
        switch (i) {
            case 0:
                flag = 0x408;
                break;
            case 1:
                flag = 0x409;
                break;
            case 2:
                flag = 0x40A;
                break;
            case 3:
                flag = 0x40B;
                break;
            case 4:
                flag = 0x40C;
                break;
        }
        if (i == 4) {
            if (func_ovl0E_11_80045D00(flag) == 0) {
                D_ovl0E_11_8004625C[i].unk8 = 0x1B4;
            } else {
                D_ovl0E_11_8004625C[i].unk8 = 0x1B2;
                func_ovl0E_11_80043F70();
            }
        } else {
            if (func_ovl0E_11_80045D00(flag) == 0) {
                D_ovl0E_11_8004625C[i].unk8 = 0x1B3;
            } else {
                D_ovl0E_11_8004625C[i].unk8 = 0x1B0;
            }
        }
        func_ovl0E_11_80043554(&D_ovl0E_11_8004625C[i]);
        func_ovl0E_11_80045928(D_ovl0E_11_8004625C[i].unk0, 0x02000000);
        func_ovl0E_11_80045930(D_ovl0E_11_8004625C[i].unk0, 0x80000);
    }
}

void func_ovl0E_11_80043F70(void) {
    if (func_ovl0E_11_80045D00(0x40C) != 0) {
        D_ovl0E_11_800464FC = func_ovl0E_11_80045970(0x2A7, 0xD0, 1400.0f, 700.0f, 1000.0f);
        func_ovl0E_11_80045928(D_ovl0E_11_800464FC, 0x01080000);
        D_ovl0E_11_800464FC->unk40->unkC |= 0x8000;
        func_ovl0E_11_80045630(D_ovl0E_11_800464FC->unk40, 2);
        func_ovl0E_11_80045638(D_ovl0E_11_800464FC->unk40, 0x2A8, 0, 0);
        func_ovl0E_11_80045638(D_ovl0E_11_800464FC->unk40, 0x2A8, 1, 1);
    }
}

void func_ovl0E_11_80043E88(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (func_ovl0E_11_80045D00(0x40D) == 0) {
            func_ovl0E_11_80043554(&D_ovl0E_11_80046374[i]);
            func_ovl0E_11_80045928(D_ovl0E_11_80046374[i].unk0, 0x02000000);
            func_ovl0E_11_80045930(D_ovl0E_11_80046374[i].unk0, 0x80000);
        } else {
            func_ovl0E_11_80043230();
        }
    }
}

void func_ovl0E_11_80043D78(void) {
    UnkStructA *obj;
    UnkStructA *p;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = func_ovl0E_11_80045970(D_ovl0E_11_800463AC[i].unk8, D_ovl0E_11_800463AC[i].unkC,
                                     D_ovl0E_11_800463AC[i].unk1C * 10.0f, D_ovl0E_11_800463AC[i].unk20 * 10.0f,
                                     D_ovl0E_11_800463AC[i].unk24 * 10.0f);
        p = func_ovl0E_11_80045960(obj);
        p->unk54 = 2.0f;
        p->unk4C = 2.0f;
        func_ovl0E_11_80045928(obj, D_ovl0E_11_800463AC[i].unkA);
        D_ovl0E_11_800463AC[i].unk4 = obj;
        obj->unk30 = 1;
        obj->unk34 = 100.0f;
        obj->unk38 = 50.0f;
    }
}

void func_ovl0E_11_80043D2C(void) {
    func_ovl0E_11_800450E0(0x1D, 4, 6);
    func_ovl0E_11_80043C64(1, 0, 0x80, 0.0f, 0);
}

void func_ovl0E_11_80043CDC(void) {
    func_ovl0E_11_800450E0(5, 2, 0x16);
    func_ovl0E_11_80043C64(2, 0, 0x80, 0.0f, 1);
}

void func_ovl0E_11_80043C8C(void) {
    func_ovl0E_11_800450E0(0x12, 2, 0x1D);
    func_ovl0E_11_80043C64(3, 0, 0x80, 0.0f, 1);
}

void func_ovl0E_11_80043C64(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_11_80046500.unk0 = arg0;
    D_ovl0E_11_80046500.unk4 = arg1;
    D_ovl0E_11_80046500.unk8 = arg2;
    D_ovl0E_11_80046500.unkC = arg3;
    D_ovl0E_11_80046500.unk10 = arg4;
}

void func_ovl0E_11_80043C44(void) {
    func_ovl0E_11_80043B2C();
}

void func_ovl0E_11_80043B2C(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_11_80045138();
    switch (D_ovl0E_11_80046500.unk8) {
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
        func_ovl0E_11_80045788(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_11_80046500.unkC;
        func_ovl0E_11_80045790(&sp1C, NULL, NULL);
        func_ovl0E_11_80045788(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_11_80045120(D_ovl0E_11_80046500.unk4);
}

void func_ovl0E_11_80043AE4(f32 arg0) {
    f32 sp1C;

    func_ovl0E_11_80045790(&sp1C, NULL, NULL);
    func_ovl0E_11_80045788(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_11_80043ABC(void) {
    func_ovl0E_11_80043A44();
    func_ovl0E_11_800439CC();
}

void func_ovl0E_11_80043A44(void) {
    UnkStruct_ovl0E_11_800463AC *rec;
    s16 i;

    for (i = 0, rec = D_ovl0E_11_800463AC; i < 4; i++, rec++) {
        rec->unk0 = func_ovl0E_11_80045A78(func_ovl0E_11_800444F4, rec, 0, 0, 0x110);
    }
}

void func_ovl0E_11_800439CC(void) {
    UNK_MACRO_ovl0E_11_80043328();
    func_ovl0E_11_80045128(D_ovl0E_11_80046500.unk4, 3, 4.0f, D_ovl0E_11_80046500.unk10, 0, 1, 1);
}

void func_ovl0E_11_80043934(void) {
    func_ovl0E_11_8004392C();
    if (func_ovl0E_11_800450F0(4, 0x16, 5, 0x16) != 0) {
        D_ovl0E_11_800464E4 = 0x51;
        D_ovl0E_11_800464E8 = 0x12;
        func_ovl0E_11_80045020(0x51, 0x12, 0);
    }
    if (func_ovl0E_11_800450F0(0x11, 0x1D, 0x12, 0x1D) != 0) {
        D_ovl0E_11_800464E4 = 0x51;
        D_ovl0E_11_800464E8 = 0x13;
        func_ovl0E_11_80045020(0x51, 0x13, 0);
    }
}

static void func_ovl0E_11_8004392C(void) {
}

void func_ovl0E_11_800437DC(void) {
    func_ovl0E_11_80043758(0x408, 0, 0x1B0, 0x23, 5, 0x23, 5);
    func_ovl0E_11_80043758(0x409, 1, 0x1B0, 0x23, 0x16, 0x23, 0x16);
    func_ovl0E_11_80043758(0x40A, 2, 0x1B0, 0x17, 0x11, 0x17, 0x11);
    func_ovl0E_11_80043758(0x40B, 3, 0x1B0, 0x15, 0x13, 0x15, 0x13);
    func_ovl0E_11_80043400();
}

void func_ovl0E_11_80043758(s16 flag, s16 idx, s32 kind, s32 x0, s32 y0, s32 x1, s32 y1) {
    if (func_ovl0E_11_80045D00(flag) == 0 && func_ovl0E_11_800450F0(x0, y0, x1, y1) != 0) {
        func_ovl0E_11_80046000(0x29);
        func_ovl0E_11_800436D4(idx, kind);
        func_ovl0E_11_80045CF0(flag);
        func_ovl0E_11_800434D0();
    }
}

void func_ovl0E_11_800436D4(s16 arg0, s32 arg1) {
    UnkStruct_ovl0E_11_8004625C *e;

    e = &D_ovl0E_11_8004625C[arg0];
    func_ovl0E_11_80043084(e);
    e->unk8 = arg1;
    func_ovl0E_11_80043554(e);
    func_ovl0E_11_80045928(e->unk0, 0x02000000);
    func_ovl0E_11_80045930(e->unk0, 0x80000);
}

static void func_ovl0E_11_80043554(UnkStruct_ovl0E_11_8004625C *e) {
    e->unk0 = func_ovl0E_11_80045970(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0E_11_80045928(e->unk0, 0x01080000);
    func_ovl0E_11_80045930(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl0E_11_80045670(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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
}

void func_ovl0E_11_800434D0(void) {
    if (func_ovl0E_11_80045D00(0x408) != 0 && func_ovl0E_11_80045D00(0x409) != 0 &&
        func_ovl0E_11_80045D00(0x40A) != 0 && func_ovl0E_11_80045D00(0x40B) != 0 &&
        func_ovl0E_11_80045D00(0x40C) == 0) {
        func_ovl0E_11_80043498();
    }
}

void func_ovl0E_11_80043498(void) {
    func_ovl0E_11_80045A78(func_ovl0E_11_800448F8, NULL, 0, 0, 0x110);
}

void func_ovl0E_11_80043400(void) {
    if (func_ovl0E_11_80045D00(0x40C) != 0) {
        if (func_ovl0E_11_80045D00(0x40D) == 0 && func_ovl0E_11_800450F0(0xE, 0xA, 0xE, 0xA) != 0 &&
            D_ovl0E_11_80046374[0].unk0 != NULL) {
            func_ovl0E_11_80045090(0);
            func_ovl0E_11_80045118(1);
            func_ovl0E_11_80046000(0x29);
            func_ovl0E_11_800433C8();
        }
    }
}

void func_ovl0E_11_800433C8(void) {
    func_ovl0E_11_800433C0();
    func_ovl0E_11_80045A78(func_ovl0E_11_80044A5C, NULL, 0, 0, 0x110);
}

static void func_ovl0E_11_800433C0(void) {
}

void func_ovl0E_11_80043370(void) {
    UNK_MACRO_ovl0E_11_80043328();
    func_ovl0E_11_8004326C();
}

void func_ovl0E_11_80043328(void) {
    func_ovl0E_11_80043320();
    UNK_MACRO_ovl0E_11_80043328();
}

static void func_ovl0E_11_80043320(void) {
}

void func_ovl0E_11_8004326C(void) {
    if (func_ovl0E_11_80045D00(0x40D) == 0) {
        if (D_ovl0E_11_80046374[0].unk0->unk40->unk48->unk4->unk4 != 0.0f &&
            (D_ovl0E_11_80046374[0].unk0->unk40->unkC & 0x40)) {
            func_ovl0E_11_80045CF0(0x40D);
            func_ovl0E_11_80043230();
            func_ovl0E_11_80045F40(0x18, 0xC, 1, 0xA);
        }
    }
}

void func_ovl0E_11_80043230(void) {
    func_ovl0E_11_80044F68(0xB, 1, 7, 0xD, 0xD, 0x11);
}

void func_ovl0E_11_80043210(void) {
    func_ovl0E_11_80045170(1);
}

void func_ovl0E_11_800431F0(void) {
    func_ovl0E_11_80045170(1);
}

void func_ovl0E_11_800431C0(void) {
    func_ovl0E_11_80043160();
    func_ovl0E_11_80043100();
    func_ovl0E_11_80043018();
}

void func_ovl0E_11_80043160(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (D_ovl0E_11_8004625C[i].unk0 != NULL) {
            func_ovl0E_11_80043084(&D_ovl0E_11_8004625C[i]);
        }
    }
}

void func_ovl0E_11_80043100(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_ovl0E_11_80046374[i].unk0 != NULL) {
            func_ovl0E_11_80043084(&D_ovl0E_11_80046374[i]);
        }
    }
}

static void func_ovl0E_11_80043084(UnkStruct_ovl0E_11_8004625C *e) {
    func_ovl0E_11_80045940(e->unk0);
    /* 0xFFFF, not -1: never equal to the s16 fields */
    if (e->unkC != 0xFFFF && e->unkE != 0xFFFF && e->unk10 != 0xFFFF && e->unk12 != 0xFFFF) {
        func_ovl0E_11_80045678(e->unk4);
    }
    e->unk0 = NULL;
    e->unk4 = -1;
}

void func_ovl0E_11_80043018(void) {
    UnkStruct_ovl0E_11_800463AC *rec;
    s16 i;

    for (i = 0, rec = D_ovl0E_11_800463AC; i < 4; i++, rec++) {
        if (rec->unk0 != -1) {
            func_ovl0E_11_80045A80(rec->unk0);
        }
    }
}

void func_ovl0E_11_80043010(void) {
}
