#include "common.h"

/*
 * ovl_0C_03's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_03_800456B0;

void func_ovl0C_03_800442C8(s32);
void func_ovl0C_03_800442E0(s32);
void func_ovl0C_03_80044350(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_03_800443B0(void (*)(UnkStructA *));
void func_ovl0C_03_800443C0(s32, s32, s32);
void func_ovl0C_03_80044400(void (*)(UnkStructA *));
void func_ovl0C_03_80044450(s32, s32);
void func_ovl0C_03_80044468(s32);
void func_ovl0C_03_80044478(void);
void func_ovl0C_03_80044480(s32, s32, s32);
void func_ovl0C_03_80044488(void *);
s32 func_ovl0C_03_80044490(s32, s32, s32, s32);
s32 func_ovl0C_03_800444A8(void);
void func_ovl0C_03_800444B0(s32, void *);
void func_ovl0C_03_800444B8(s32);
void func_ovl0C_03_800444C0(s32);
void func_ovl0C_03_800444C8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_03_800444D8(void);
UnkStructA *func_ovl0C_03_80044508(s32);
void func_ovl0C_03_80044510(s32);
void func_ovl0C_03_80044B08(f32, f32, f32);
void func_ovl0C_03_80044B28(f32, f32, f32);
void func_ovl0C_03_80044B30(f32 *, f32 *, f32 *);
void func_ovl0C_03_80044BC0(f32, f32);
void func_ovl0C_03_80044CC8(UnkStructA *, s32);
void func_ovl0C_03_80044CD0(UnkStructA *, s32);
void func_ovl0C_03_80044CE0(UnkStructA *);
UnkStructA *func_ovl0C_03_80044CF0(s32, s32, s32, s32);
void func_ovl0C_03_80044E18(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_03_80044E28(void);
void func_ovl0C_03_80044E38(s32);
UnkStructA *func_ovl0C_03_80044E40(void);
void func_ovl0C_03_80044E60(void);
f32 func_ovl0C_03_80044FC0(f32);
void func_ovl0C_03_80045098(s32);
void func_ovl0C_03_80045180(u32 (*)[3]);
void func_ovl0C_03_80045328(s32, s32, s32);
void func_ovl0C_03_800453A0(s32);
void func_ovl0C_03_800453C0(s32, f32, f32, f32);

void func_ovl0C_03_80043010(void);
void func_ovl0C_03_80043020(void);
void func_ovl0C_03_80043040(void);
void func_ovl0C_03_80043068(void);
void func_ovl0C_03_800430B0(void);
void func_ovl0C_03_80043108(void);
void func_ovl0C_03_80043210(void);
void func_ovl0C_03_80043258(void);
void func_ovl0C_03_800432E4(void);
void func_ovl0C_03_8004335C(void);
void func_ovl0C_03_800433B4(f32);
void func_ovl0C_03_800433FC(void);
void func_ovl0C_03_8004352C(void);
void func_ovl0C_03_80043578(s32, s32, s32, f32, s32);
void func_ovl0C_03_800435A0(void);
void func_ovl0C_03_800435F0(void);
void func_ovl0C_03_80043640(void);
void func_ovl0C_03_80043690(void);
void func_ovl0C_03_800436F0(void);
void func_ovl0C_03_80043750(void);
void func_ovl0C_03_800437AC(void);
void func_ovl0C_03_800437FC(void);
void func_ovl0C_03_80043804(void);
void func_ovl0C_03_80043844(void);
void func_ovl0C_03_8004387C(void);
void func_ovl0C_03_8004391C(s32);
void func_ovl0C_03_80043B14(void);
void func_ovl0C_03_80043B98(UnkStructA *);
void func_ovl0C_03_80043C58(UnkStructA *);
void func_ovl0C_03_80043C9C(UnkStructA *, s32, s32, f32, f32);
void func_ovl0C_03_80043D74(void);
void func_ovl0C_03_80043E84(s32, UnkStructA *);
void func_ovl0C_03_80043EB8(f32, f32, f32);
void func_ovl0C_03_80043F14(void);
void func_ovl0C_03_80043F2C(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0C_03_80043018(void);
static void func_ovl0C_03_80043060(void);
static void func_ovl0C_03_800430F8(void);
static void func_ovl0C_03_80043100(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0C_03_800430B0() \
    D_ovl0C_03_8004568C = func_ovl0C_03_800444A8(); func_ovl0C_03_80044488(&D_ovl0C_03_80045680); func_ovl0C_03_800444B0(D_ovl0C_03_8004568C, D_ovl0C_03_80045670)

/* .bss */
u8 D_ovl0C_03_80045670[0x10];
Vec3f D_ovl0C_03_80045680;
s32 D_ovl0C_03_8004568C;
u8 D_ovl0C_03_80045690[0x4]; /* unused (func_ovl0C_03_80043F74) */
s32 D_ovl0C_03_80045694;
s32 D_ovl0C_03_80045698;
u8 D_ovl0C_03_8004569C[0x4]; /* unused (func_ovl0C_03_80043F74) */
Vec3f D_ovl0C_03_800456A0;
UnkStructA *D_ovl0C_03_800456AC;
UnkStruct_ovl0C_03_800456B0 D_ovl0C_03_800456B0;

/* .data */
/* passed to func_ovl0C_03_80045180: three 12-byte records */
u32 D_ovl0C_03_800455C0[][3] = {
    { 0x910002, 0xE, 4 },
    { 0x910002, 0xE, 4 },
    { 0x940002, 0xE, 4 },
};
/* two 12-byte records, each passed to func_ovl0C_03_80045328 */
u32 D_ovl0C_03_800455E4[][3] = {
    { 0, 4, 0xE2 },
    { 1, 0x17, 0xF5 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0C_03_80043F74(void) {
    D_ovl0C_03_80045690[0] = D_ovl0C_03_8004569C[0];
}

static void func_ovl0C_03_80043F6C(void) {
}

static void func_ovl0C_03_80043F64(void) {
}

static void func_ovl0C_03_80043F5C(void) {
}

static void func_ovl0C_03_80043F54(void) {
}

static void func_ovl0C_03_80043F4C(void) {
}

static void func_ovl0C_03_80043F44(void) {
}

static void func_ovl0C_03_80043F3C(void) {
}

static void func_ovl0C_03_80043F34(void) {
}

void func_ovl0C_03_80043F2C(void) {
}

void func_ovl0C_03_80043F14(void) {
    D_ovl0C_03_80045694 = -1;
    D_ovl0C_03_80045698 = -1;
}

void func_ovl0C_03_80043EB8(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_03_80044B08(D_ovl0C_03_800456A0.x, D_ovl0C_03_800456A0.y, D_ovl0C_03_800456A0.z);
    func_ovl0C_03_80044B28(arg0, arg1, arg2);
    func_ovl0C_03_80044E38(180);
}

void func_ovl0C_03_80043E84(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_03_800453C0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_03_80043D74(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_03_80044E40();
    func_ovl0C_03_800453C0(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_03_80044CF0(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_03_80043C9C(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_03_80044E60();
    }
    func_ovl0C_03_80044CE0(obj);
    func_ovl0C_03_80044E28();
}

void func_ovl0C_03_80043C9C(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    /* the ratio is spelled out three times: with a variable for it, IDO
     * spills it to another stack slot */
    arg0->unk40->unk28 = func_ovl0C_03_80044FC0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_03_80044FC0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_03_80043C58(UnkStructA *arg0) {
    func_ovl0C_03_80044CD0(arg0, 0x01000000);
    func_ovl0C_03_80044E18(func_ovl0C_03_80043D74, arg0, 0, 0, 0x150);
}

void func_ovl0C_03_80043B98(UnkStructA *arg0) {
    func_ovl0C_03_80044E38(10);
    func_ovl0C_03_80044350(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_03_80044E38(60);
}

void func_ovl0C_03_80043B14(void) {
    UnkStructA *obj;
    s32 alpha;
    s32 step;

    func_ovl0C_03_800444B8(1);
    func_ovl0C_03_80044E38(10);
    obj = func_ovl0C_03_80044508(func_ovl0C_03_800444A8());
    func_ovl0C_03_800453A0(0x44);
    func_ovl0C_03_80044CC8(obj, 0x80000);
    step = 0x11;
    for (alpha = 0xFF; alpha > 0; alpha -= step) {
        obj->unk40->unk36 = alpha;
        func_ovl0C_03_80044E60();
    }
    obj->unk40->unk36 = 0;
    func_ovl0C_03_80044E28();
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0C_03_8004391C(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0C_03_8004387C();
            break;
        case 17:
            func_ovl0C_03_800437AC();
            break;
        case 18:
            func_ovl0C_03_80043750();
            break;
        case 19:
            func_ovl0C_03_800436F0();
            break;
        case 20:
            func_ovl0C_03_80043690();
            break;
        case 21:
            func_ovl0C_03_80043640();
            break;
        case 22:
            func_ovl0C_03_800435F0();
            break;
        case 23:
            func_ovl0C_03_800435A0();
            break;
        case 4:
            func_ovl0C_03_800433FC();
            if (D_ovl0C_03_800456B0.unk0 == 2 || D_ovl0C_03_800456B0.unk0 == 3 || D_ovl0C_03_800456B0.unk0 == 4) {
                func_ovl0C_03_8004335C();
            }
            break;
        case 5:
            if (D_ovl0C_03_800456B0.unk0 == 2 || D_ovl0C_03_800456B0.unk0 == 3 || D_ovl0C_03_800456B0.unk0 == 4) {
                func_ovl0C_03_80043258();
            }
            func_ovl0C_03_800444C8(D_ovl0C_03_800456B0.unk4, 3, 4.0f, D_ovl0C_03_800456B0.unk10, 0, 1, 1);
            break;
        case 0x50:
            func_ovl0C_03_80043108();
            break;
        case 3:
            UNK_MACRO_ovl0C_03_800430B0();
            break;
        case 12:
            func_ovl0C_03_80044510(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0C_03_8004387C(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0C_03_80043804();
    func_ovl0C_03_800443B0(func_ovl0C_03_80043C58);
    func_ovl0C_03_80044400(func_ovl0C_03_80043B98);
    func_ovl0C_03_80045180(D_ovl0C_03_800455C0);
    func_ovl0C_03_800442C8(0x244);
    p = D_ovl0C_03_800455E4;
    count = 2;
    for (i = 0; i < count; i++) {
        func_ovl0C_03_80045328((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0C_03_800442E0(0x24E);
    func_ovl0C_03_80044478();
}

void func_ovl0C_03_80043844(void) {
    func_ovl0C_03_80043804();
    func_ovl0C_03_800443B0(func_ovl0C_03_80043C58);
    func_ovl0C_03_80044400(func_ovl0C_03_80043B98);
}

void func_ovl0C_03_80043804(void) {
    func_ovl0C_03_80045098(0x400);
    func_ovl0C_03_80045098(0x401);
    func_ovl0C_03_80045098(0x402);
    func_ovl0C_03_80045098(0x403);
    func_ovl0C_03_80045098(0x404);
}

void func_ovl0C_03_800437FC(void) {
}

void func_ovl0C_03_800437AC(void) {
    func_ovl0C_03_80044480(0x17, 5, 5);
    func_ovl0C_03_80043578(1, 0x80, 0, 0.0f, 2);
}

void func_ovl0C_03_80043750(void) {
    func_ovl0C_03_80044480(0x17, 5, 5);
    func_ovl0C_03_80043578(2, 0x80, 0, 0.0f, 2);
    func_ovl0C_03_80044450(0x2A, 0x15);
}

void func_ovl0C_03_800436F0(void) {
    func_ovl0C_03_80044480(0x17, 0, 7);
    func_ovl0C_03_80043578(3, 0x80, 0, 0.0f, 2);
    func_ovl0C_03_80044450(0x2A, 0x16);
}

void func_ovl0C_03_80043690(void) {
    func_ovl0C_03_80044480(0x17, 3, 0x1C);
    func_ovl0C_03_80043578(4, 0, 0x80, 0.0f, 2);
    func_ovl0C_03_80044450(0x2A, 0x17);
}

void func_ovl0C_03_80043640(void) {
    func_ovl0C_03_80044480(0x17, 5, 5);
    func_ovl0C_03_80043578(5, 0x80, 0, 0.0f, 2);
}

void func_ovl0C_03_800435F0(void) {
    func_ovl0C_03_80044480(0x17, 0, 7);
    func_ovl0C_03_80043578(6, 0x80, 0, 0.0f, 2);
}

void func_ovl0C_03_800435A0(void) {
    func_ovl0C_03_80044480(0x17, 3, 0x1C);
    func_ovl0C_03_80043578(7, 0, 0x80, 0.0f, 2);
}

void func_ovl0C_03_80043578(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0C_03_800456B0.unk0 = arg0;
    D_ovl0C_03_800456B0.unk4 = arg1;
    D_ovl0C_03_800456B0.unk8 = arg2;
    D_ovl0C_03_800456B0.unkC = arg3;
    D_ovl0C_03_800456B0.unk10 = arg4;
}

void func_ovl0C_03_8004352C(void) {
    func_ovl0C_03_800433FC();
    if (D_ovl0C_03_800456B0.unk0 == 2 || D_ovl0C_03_800456B0.unk0 == 3 || D_ovl0C_03_800456B0.unk0 == 4) {
        func_ovl0C_03_8004335C();
    }
}

void func_ovl0C_03_800433FC(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_03_800444D8();
    switch (D_ovl0C_03_800456B0.unk8) {
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
        func_ovl0C_03_80044B28(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_03_800456B0.unkC;
        func_ovl0C_03_80044B30(&sp1C, NULL, NULL);
        func_ovl0C_03_80044B28(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_03_800444C0(D_ovl0C_03_800456B0.unk4);
    func_ovl0C_03_80044BC0(45.0f, 45.1f);
}

void func_ovl0C_03_800433B4(f32 arg0) {
    f32 sp1C;

    func_ovl0C_03_80044B30(&sp1C, NULL, NULL);
    func_ovl0C_03_80044B28(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0C_03_8004335C(void) {
    D_ovl0C_03_800456AC = func_ovl0C_03_80044508(func_ovl0C_03_800444A8());
    func_ovl0C_03_80044CC8(D_ovl0C_03_800456AC, 0x80000);
    D_ovl0C_03_800456AC->unk40->unk36 = 0;
}

void func_ovl0C_03_800432E4(void) {
    if (D_ovl0C_03_800456B0.unk0 == 2 || D_ovl0C_03_800456B0.unk0 == 3 || D_ovl0C_03_800456B0.unk0 == 4) {
        func_ovl0C_03_80043258();
    }
    func_ovl0C_03_800444C8(D_ovl0C_03_800456B0.unk4, 3, 4.0f, D_ovl0C_03_800456B0.unk10, 0, 1, 1);
}

void func_ovl0C_03_80043258(void) {
    s32 alpha;
    s32 step;

    func_ovl0C_03_800444B8(1);
    func_ovl0C_03_800453A0(0x45);
    step = 0x11;
    for (alpha = 0; alpha < 0xFF; alpha += step) {
        D_ovl0C_03_800456AC->unk40->unk36 = alpha;
        func_ovl0C_03_80044E60();
    }
    D_ovl0C_03_800456AC->unk40->unk36 = 0xFF;
    func_ovl0C_03_80044CD0(D_ovl0C_03_800456AC, 0x80000);
    func_ovl0C_03_800444B8(0);
}

void func_ovl0C_03_80043210(void) {
    func_ovl0C_03_800444C8(D_ovl0C_03_800456B0.unk4, 3, 4.0f, D_ovl0C_03_800456B0.unk10, 0, 1, 1);
}

void func_ovl0C_03_80043108(void) {
    func_ovl0C_03_800430F8();
    func_ovl0C_03_80043100();
    if (func_ovl0C_03_80044490(0x17, 4, 0x18, 5) != 0) {
        func_ovl0C_03_80044E18(func_ovl0C_03_80043B14, 0, 0, 0, 0x130);
        func_ovl0C_03_80044468(60);
        func_ovl0C_03_800443C0(0x2A, 0x13, 4);
    }
    if (func_ovl0C_03_80044490(0x17, 6, 0x18, 7) != 0) {
        func_ovl0C_03_80044E18(func_ovl0C_03_80043B14, 0, 0, 0, 0x130);
        func_ovl0C_03_80044468(60);
        func_ovl0C_03_800443C0(0x2A, 0x12, 4);
    }
    if (func_ovl0C_03_80044490(0x17, 0x1C, 0x18, 0x1D) != 0) {
        func_ovl0C_03_80044E18(func_ovl0C_03_80043B14, 0, 0, 0, 0x130);
        func_ovl0C_03_80044468(60);
        func_ovl0C_03_800443C0(0x28, 0x12, 4);
    }
}

static void func_ovl0C_03_80043100(void) {
}

static void func_ovl0C_03_800430F8(void) {
}

void func_ovl0C_03_800430B0(void) {
    UNK_MACRO_ovl0C_03_800430B0();
}

void func_ovl0C_03_80043068(void) {
    func_ovl0C_03_80043060();
    D_ovl0C_03_8004568C = func_ovl0C_03_800444A8();
    func_ovl0C_03_80044488(&D_ovl0C_03_80045680);
    func_ovl0C_03_800444B0(D_ovl0C_03_8004568C, D_ovl0C_03_80045670);
}

static void func_ovl0C_03_80043060(void) {
}

void func_ovl0C_03_80043040(void) {
    func_ovl0C_03_80044510(1);
}

void func_ovl0C_03_80043020(void) {
    func_ovl0C_03_80043018();
    func_ovl0C_03_80044510(1);
}

static void func_ovl0C_03_80043018(void) {
}

void func_ovl0C_03_80043010(void) {
}

