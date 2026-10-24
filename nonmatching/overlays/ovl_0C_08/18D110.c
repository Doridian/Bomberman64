/*
 * NON_MATCHING: ovl_0C_08's object as one -O3 file. src/ has it at -O2 with
 * func_ovl0C_08_80043654 and one more function GLOBAL_ASM, which matches;
 * this is the closest whole -O3 version (docs/DECOMPILING.md).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 2, eu 2, jp 2
 *
 * What still differs in us (words):
 * - func_ovl0C_08_80043654 (2): with the object set-up inlined (a static
 *   taking the struct's address, calling 8004361C), the epilogue restores
 *   s2, s1, s0; the original restores s0 first.
 */
#include "common.h"

/*
 * ovl_0C_08's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_08_800455E0;

/* an object placed in the stage (as ovl_17_01's) */
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
} UnkStruct_ovl0C_08_800454FC; /* size 0x38 */

void func_ovl0C_08_800441C8(s32);
void func_ovl0C_08_800441E0(s32);
void func_ovl0C_08_80044250(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_08_800442B0(void (*)(UnkStructA *));
void func_ovl0C_08_800442C0(s32, s32, s32);
void func_ovl0C_08_80044300(void (*)(UnkStructA *));
void func_ovl0C_08_80044350(s32, s32);
void func_ovl0C_08_80044368(s32);
void func_ovl0C_08_80044378(void);
void func_ovl0C_08_80044380(s32, s32, s32);
void func_ovl0C_08_80044388(void *);
s32 func_ovl0C_08_80044390(s32, s32, s32, s32);
s32 func_ovl0C_08_800443A8(void);
void func_ovl0C_08_800443B0(s32, void *);
void func_ovl0C_08_800443B8(s32);
void func_ovl0C_08_800443C0(s32);
void func_ovl0C_08_800443C8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_08_800443D8(void);
UnkStructA *func_ovl0C_08_80044408(s32);
void func_ovl0C_08_80044410(s32);
s32 func_ovl0C_08_80044910(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0C_08_80044A08(f32, f32, f32);
void func_ovl0C_08_80044A28(f32, f32, f32);
void func_ovl0C_08_80044A30(f32 *, f32 *, f32 *);
void func_ovl0C_08_80044AC0(f32, f32);
void func_ovl0C_08_80044BC8(UnkStructA *, s32);
void func_ovl0C_08_80044BD0(UnkStructA *, s32);
void func_ovl0C_08_80044BE0(UnkStructA *);
UnkStructA *func_ovl0C_08_80044BF0(s32, s32, s32, s32);
UnkStructA *func_ovl0C_08_80044C10(s32, s32, f32, f32, f32);
void func_ovl0C_08_80044D18(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_08_80044D28(void);
void func_ovl0C_08_80044D38(s32);
UnkStructA *func_ovl0C_08_80044D40(void);
void func_ovl0C_08_80044D60(void);
f32 func_ovl0C_08_80044EC0(f32);
void func_ovl0C_08_80044F98(s32);
void func_ovl0C_08_80045080(u32 (*)[3]);
void func_ovl0C_08_80045228(s32, s32, s32);
void func_ovl0C_08_800452A0(s32);
void func_ovl0C_08_800452C0(s32, f32, f32, f32);

void func_ovl0C_08_80043010(void);
void func_ovl0C_08_80043020(void);
void func_ovl0C_08_80043040(void);
void func_ovl0C_08_80043068(void);
void func_ovl0C_08_800430B0(void);
void func_ovl0C_08_80043108(void);
void func_ovl0C_08_80043170(void);
void func_ovl0C_08_800431B8(void);
void func_ovl0C_08_80043244(void);
void func_ovl0C_08_800432A8(void);
void func_ovl0C_08_80043300(f32 arg0);
void func_ovl0C_08_80043348(void);
void func_ovl0C_08_80043478(void);
void func_ovl0C_08_800434B4(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4);
void func_ovl0C_08_800434DC(void);
void func_ovl0C_08_80043528(void);
void func_ovl0C_08_80043580(void);
void func_ovl0C_08_800435CC(void);
void func_ovl0C_08_800435DC(void);
void func_ovl0C_08_8004361C(void);
void func_ovl0C_08_80043888(s32 arg0);
void func_ovl0C_08_80043A20(void);
void func_ovl0C_08_80043AA4(UnkStructA *);
void func_ovl0C_08_80043B64(UnkStructA *);
void func_ovl0C_08_80043BA8(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_ovl0C_08_80043C80(void);
void func_ovl0C_08_80043D90(s32 arg0, UnkStructA *arg1);
void func_ovl0C_08_80043DC4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0C_08_80043E20(void);
void func_ovl0C_08_80043E38(void);

static void func_ovl0C_08_80043018(void);
static void func_ovl0C_08_80043060(void);
static void func_ovl0C_08_800430F8(void);
static void func_ovl0C_08_80043100(void);
static void func_ovl0C_08_800435D4(UnkStruct_ovl0C_08_800454FC *);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0C_08_800430B0() \
    D_ovl0C_08_800455BC = func_ovl0C_08_800443A8(); func_ovl0C_08_80044388(&D_ovl0C_08_800455B0); func_ovl0C_08_800443B0(D_ovl0C_08_800455BC, D_ovl0C_08_800455A0)

/* empty statics: each leaves a `jr ra; nop` just before its caller */

/* .bss */
u8 D_ovl0C_08_800455A0[0x10];
Vec3f D_ovl0C_08_800455B0;
s32 D_ovl0C_08_800455BC;
u8 D_ovl0C_08_800455C0[0x4]; /* unused (func_ovl0C_08_80043E78) */
s32 D_ovl0C_08_800455C4;
s32 D_ovl0C_08_800455C8;
u8 D_ovl0C_08_800455CC[0x4]; /* unused (func_ovl0C_08_80043E78) */
Vec3f D_ovl0C_08_800455D0;
UnkStructA *D_ovl0C_08_800455DC;
UnkStruct_ovl0C_08_800455E0 D_ovl0C_08_800455E0;

/* .data */
/* passed to func_ovl0C_08_80045080: three 12-byte records */
u32 D_ovl0C_08_800454C0[][3] = {
    { 0x940002, 0xE, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
/* two 12-byte records, each passed to func_ovl0C_08_80045228 */
u32 D_ovl0C_08_800454E4[][3] = {
    { 0, 0, 0xDE },
    { 1, 0x22, 0xE0 },
};
/* an object placed in the stage (func_ovl0C_08_800435D4) */
UnkStruct_ovl0C_08_800454FC D_ovl0C_08_800454FC = {
    NULL, -1, 0x2BA, -5, -0x400, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0C_08_80043E78(void) {
    D_ovl0C_08_800455C0[0] = D_ovl0C_08_800455CC[0];
}

static void func_ovl0C_08_80043E70(void) {
}

static void func_ovl0C_08_80043E68(void) {
}

static void func_ovl0C_08_80043E60(void) {
}

static void func_ovl0C_08_80043E58(void) {
}

static void func_ovl0C_08_80043E50(void) {
}

static void func_ovl0C_08_80043E48(void) {
}

static void func_ovl0C_08_80043E40(void) {
}

void func_ovl0C_08_80043E38(void) {
}

void func_ovl0C_08_80043E20(void) {
    D_ovl0C_08_800455C4 = -1;
    D_ovl0C_08_800455C8 = -1;
}

void func_ovl0C_08_80043DC4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_08_80044A08(D_ovl0C_08_800455D0.x, D_ovl0C_08_800455D0.y, D_ovl0C_08_800455D0.z);
    func_ovl0C_08_80044A28(arg0, arg1, arg2);
    func_ovl0C_08_80044D38(180);
}

void func_ovl0C_08_80043D90(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_08_800452C0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_08_80043C80(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_08_80044D40();
    func_ovl0C_08_800452C0(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_08_80044BF0(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_08_80043BA8(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_08_80044D60();
    }
    func_ovl0C_08_80044BE0(obj);
    func_ovl0C_08_80044D28();
}

void func_ovl0C_08_80043BA8(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    /* the ratio is spelled out three times: with a variable for it, IDO
     * spills it to another stack slot */
    arg0->unk40->unk28 = func_ovl0C_08_80044EC0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_08_80044EC0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_08_80043AA4(UnkStructA *arg0) {
    func_ovl0C_08_80044D38(10);
    func_ovl0C_08_80044250(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_08_80044D38(60);
}
void func_ovl0C_08_80043B64(UnkStructA *arg0) {
    func_ovl0C_08_80044BD0(arg0, 0x01000000);
    func_ovl0C_08_80044D18(func_ovl0C_08_80043C80, arg0, 0, 0, 0x150);
}

void func_ovl0C_08_80043A20(void) {
    UnkStructA *obj;
    s32 alpha;
    s32 step;

    func_ovl0C_08_800443B8(1);
    func_ovl0C_08_80044D38(10);
    obj = func_ovl0C_08_80044408(func_ovl0C_08_800443A8());
    func_ovl0C_08_800452A0(0x44);
    func_ovl0C_08_80044BC8(obj, 0x80000);
    step = 0x11;
    for (alpha = 0xFF; alpha > 0; alpha -= step) {
        obj->unk40->unk36 = alpha;
        func_ovl0C_08_80044D60();
    }
    obj->unk40->unk36 = 0;
    func_ovl0C_08_80044D28();
}

void func_ovl0C_08_800435DC(void) {
    func_ovl0C_08_80044F98(0x400);
    func_ovl0C_08_80044F98(0x401);
    func_ovl0C_08_80044F98(0x402);
    func_ovl0C_08_80044F98(0x403);
    func_ovl0C_08_80044F98(0x404);
}

void func_ovl0C_08_8004361C(void) {
    func_ovl0C_08_800435DC();
    func_ovl0C_08_800442B0(func_ovl0C_08_80043B64);
    func_ovl0C_08_80044300(func_ovl0C_08_80043AA4);
}

static void func_ovl0C_08_800435D4(UnkStruct_ovl0C_08_800454FC *e) {
    e->unk0 = func_ovl0C_08_80044C10(e->unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl0C_08_80044BC8(e->unk0, 0x01080000);
    func_ovl0C_08_80044BD0(e->unk0, 0x02000000);
    if (e->unkC != -1 && e->unkE != -1 && e->unk10 != -1 && e->unk12 != -1) {
        e->unk4 = func_ovl0C_08_80044910(e->unk0->unk40, 0, e->unkC, e->unkE, e->unk10, e->unk12);
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

void func_ovl0C_08_80043654(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0C_08_8004361C();
    func_ovl0C_08_80045080(D_ovl0C_08_800454C0);
    func_ovl0C_08_800441C8(0x249);
    p = D_ovl0C_08_800454E4;
    count = 2;
    for (i = 0; i < count; i++) {
        func_ovl0C_08_80045228((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0C_08_800441E0(0x253);
    func_ovl0C_08_80044378();
    func_ovl0C_08_800435D4(&D_ovl0C_08_800454FC);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0C_08_80043888(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl0C_08_80043654();
            break;
        case 17:
            func_ovl0C_08_80043580();
            break;
        case 18:
            func_ovl0C_08_80043528();
            break;
        case 19:
            func_ovl0C_08_800434DC();
            break;
        case 4:
            func_ovl0C_08_80043348();
            if (D_ovl0C_08_800455E0.unk0 == 2) {
                func_ovl0C_08_800432A8();
            }
            break;
        case 5:
            if (D_ovl0C_08_800455E0.unk0 == 2) {
                func_ovl0C_08_800431B8();
            }
            func_ovl0C_08_800443C8(D_ovl0C_08_800455E0.unk4, 3, 4.0f, D_ovl0C_08_800455E0.unk10, 0, 1, 1);
            break;
        case 0x50:
            func_ovl0C_08_80043108();
            break;
        case 3:
            UNK_MACRO_ovl0C_08_800430B0();
            break;
        case 12:
            func_ovl0C_08_80044410(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0C_08_800435CC(void) {
}

void func_ovl0C_08_80043580(void) {
    func_ovl0C_08_80044380(0x17, 0, 0x19);
    func_ovl0C_08_800434B4(1, 0, 0, 0.0f, 2);
}

void func_ovl0C_08_80043528(void) {
    func_ovl0C_08_80044380(0x17, 0, 0x19);
    func_ovl0C_08_800434B4(2, 0, 0, 0.0f, 2);
    func_ovl0C_08_80044350(0x2F, 0x13);
}

void func_ovl0C_08_800434DC(void) {
    func_ovl0C_08_80044380(0x17, 0, 0x19);
    func_ovl0C_08_800434B4(3, 0, 0, 0.0f, 2);
}

void func_ovl0C_08_800434B4(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0C_08_800455E0.unk0 = arg0;
    D_ovl0C_08_800455E0.unk4 = arg1;
    D_ovl0C_08_800455E0.unk8 = arg2;
    D_ovl0C_08_800455E0.unkC = arg3;
    D_ovl0C_08_800455E0.unk10 = arg4;
}

void func_ovl0C_08_80043478(void) {
    func_ovl0C_08_80043348();
    if (D_ovl0C_08_800455E0.unk0 == 2) {
        func_ovl0C_08_800432A8();
    }
}

void func_ovl0C_08_80043348(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_08_800443D8();
    switch (D_ovl0C_08_800455E0.unk8) {
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
        func_ovl0C_08_80044A28(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_08_800455E0.unkC;
        func_ovl0C_08_80044A30(&sp1C, NULL, NULL);
        func_ovl0C_08_80044A28(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_08_800443C0(D_ovl0C_08_800455E0.unk4);
    func_ovl0C_08_80044AC0(45.0f, 45.1f);
}

void func_ovl0C_08_80043300(f32 arg0) {
    f32 sp1C;

    func_ovl0C_08_80044A30(&sp1C, NULL, NULL);
    func_ovl0C_08_80044A28(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0C_08_800432A8(void) {
    D_ovl0C_08_800455DC = func_ovl0C_08_80044408(func_ovl0C_08_800443A8());
    func_ovl0C_08_80044BC8(D_ovl0C_08_800455DC, 0x80000);
    D_ovl0C_08_800455DC->unk40->unk36 = 0;
}

void func_ovl0C_08_80043244(void) {
    if (D_ovl0C_08_800455E0.unk0 == 2) {
        func_ovl0C_08_800431B8();
    }
    func_ovl0C_08_800443C8(D_ovl0C_08_800455E0.unk4, 3, 4.0f, D_ovl0C_08_800455E0.unk10, 0, 1, 1);
}

void func_ovl0C_08_800431B8(void) {
    s32 alpha;
    s32 step;

    func_ovl0C_08_800443B8(1);
    func_ovl0C_08_800452A0(0x45);
    step = 0x11;
    for (alpha = 0; alpha < 0xFF; alpha += step) {
        D_ovl0C_08_800455DC->unk40->unk36 = alpha;
        func_ovl0C_08_80044D60();
    }
    D_ovl0C_08_800455DC->unk40->unk36 = 0xFF;
    func_ovl0C_08_80044BD0(D_ovl0C_08_800455DC, 0x80000);
    func_ovl0C_08_800443B8(0);
}

void func_ovl0C_08_80043170(void) {
    func_ovl0C_08_800443C8(D_ovl0C_08_800455E0.unk4, 3, 4.0f, D_ovl0C_08_800455E0.unk10, 0, 1, 1);
}

void func_ovl0C_08_80043108(void) {
    func_ovl0C_08_800430F8();
    func_ovl0C_08_80043100();
    if (func_ovl0C_08_80044390(0x17, 0x18, 0x18, 0x19) != 0) {
        func_ovl0C_08_80044D18(func_ovl0C_08_80043A20, 0, 0, 0, 0x130);
        func_ovl0C_08_80044368(60);
        func_ovl0C_08_800442C0(0x2D, 0x13, 4);
    }
}

static void func_ovl0C_08_80043100(void) {
}

static void func_ovl0C_08_800430F8(void) {
}

void func_ovl0C_08_800430B0(void) {
    UNK_MACRO_ovl0C_08_800430B0();
}

void func_ovl0C_08_80043068(void) {
    func_ovl0C_08_80043060();
    D_ovl0C_08_800455BC = func_ovl0C_08_800443A8();
    func_ovl0C_08_80044388(&D_ovl0C_08_800455B0);
    func_ovl0C_08_800443B0(D_ovl0C_08_800455BC, D_ovl0C_08_800455A0);
}

static void func_ovl0C_08_80043060(void) {
}

void func_ovl0C_08_80043040(void) {
    func_ovl0C_08_80044410(1);
}

void func_ovl0C_08_80043020(void) {
    func_ovl0C_08_80043018();
    func_ovl0C_08_80044410(1);
}

static void func_ovl0C_08_80043018(void) {
}

void func_ovl0C_08_80043010(void) {
}

