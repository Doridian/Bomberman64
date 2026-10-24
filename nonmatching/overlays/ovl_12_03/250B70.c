/*
 * NON_MATCHING: ovl_12_03's game object, complete: every function and its data.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 33, eu 33, jp 33
 *
 * What still differs (words; the same in all three):
 * - func_ovl12_03_80043174 (27): the inlined func_ovl12_03_8004316C is
 *   scheduled differently: the original saves s1/s2 and sets the count
 *   before computing x, stores y before x, and stores the result of
 *   func_ovl12_03_80045890 before the epilogue; ours puts that store in
 *   the epilogue. The copies inlined into 80043408 and 80043F68 match.
 * - func_ovl12_03_80043668 (4): each `func_ovl12_03_80044B98(n)` call
 *   sets `a0` again in its delay slot; the original has a nop there (`a0`
 *   is already set in the branch's delay slot).
 * - func_ovl12_03_80043108 (2): the `lui a0` of D_ovl12_03_80045EC0 is
 *   scheduled before `sw ra`; the original has it after.
 * The entry (ovl_12_03_entry, `return func_ovl12_03_8004418C;`) goes to
 * src/ with it.
 */
#include "common.h"

/*
 * ovl_12_03's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl12_03_80045EE0;

/* an object and where it is made */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl12_03_80045E24;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl12_03_80045C34;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
} UnkStruct_ovl12_03_80045C84;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} UnkStruct_ovl12_03_80045CE4;

void func_ovl12_03_800448E8(s32);
void func_ovl12_03_80044900(s32);
s32 func_ovl12_03_80044950(s32);
void func_ovl12_03_80044970(UnkStructA_40 *, f32 *, f32 *);
void func_ovl12_03_800449D0(void (*)(UnkStructA *));
void func_ovl12_03_800449E0(s32, s32, s32);
void func_ovl12_03_80044A08(void);
void func_ovl12_03_80044A20(void (*)(UnkStructA *));
void func_ovl12_03_80044A50(s32);
void func_ovl12_03_80044A58(s32);
void func_ovl12_03_80044A98(void);
void func_ovl12_03_80044AA0(s32, s32, s32);
void func_ovl12_03_80044AA8(void *);
s32 func_ovl12_03_80044AB0(s32, s32, s32, s32);
s32 func_ovl12_03_80044AC8(void);
void func_ovl12_03_80044AD0(s32, void *);
void func_ovl12_03_80044AD8(s32);
void func_ovl12_03_80044AE0(s32);
void func_ovl12_03_80044AE8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl12_03_80044AF8(void);
void func_ovl12_03_80044B30(s32);
void func_ovl12_03_80044B98(s32);
void func_ovl12_03_80044FF0(UnkStructA_40 *, s32);
void func_ovl12_03_80044FF8(UnkStructA_40 *, s32, s32, s32);
f32 func_ovl12_03_80045028(UnkStructA_40 *, s32);
void func_ovl12_03_80045128(f32, f32, f32);
void func_ovl12_03_80045148(f32, f32, f32);
void func_ovl12_03_80045150(f32 *, f32 *, f32 *);
void func_ovl12_03_80045188(s32);
void func_ovl12_03_80045190(s32);
void func_ovl12_03_80045218(void *);
void func_ovl12_03_80045248(void);
void func_ovl12_03_80045250(void);
void func_ovl12_03_800452E8(UnkStructA *, s32);
void func_ovl12_03_800452F0(UnkStructA *, s32);
void func_ovl12_03_80045300(UnkStructA *);
UnkStructA *func_ovl12_03_80045330(s32, s32, f32, f32, f32);
void func_ovl12_03_80045368(UnkStructA *);
void func_ovl12_03_80045458(s32);
void func_ovl12_03_80045480(void);
UnkStructA *func_ovl12_03_800454C0(s32);
void func_ovl12_03_800454D0(UnkStructA *, s32);
void func_ovl12_03_800456B0(s32);
void func_ovl12_03_800456B8(s32);
s32 func_ovl12_03_800456C0(s32);
void func_ovl12_03_80045760(s32, s32, s32);
void func_ovl12_03_80045778(s32, s32, s32, s32, s32);
void func_ovl12_03_800457A0(u32 (*)[3]);
s32 func_ovl12_03_80045890(s32, Vec3f *, s32);
void func_ovl12_03_80045898(s32);
void func_ovl12_03_80045948(s32, s32, s32);
void func_ovl12_03_800459C0(s32);
void func_ovl12_03_800459E0(s32, f32, f32, f32);

void func_ovl12_03_80043010(void);
void func_ovl12_03_80043020(void);
void func_ovl12_03_80043040(void);
void func_ovl12_03_80043068(void);
void func_ovl12_03_800430B0(void);
void func_ovl12_03_80043108(void);
void func_ovl12_03_80043138(s32);
void func_ovl12_03_80043174(void);
void func_ovl12_03_80043248(UnkStruct_ovl12_03_80045C34 *);
void func_ovl12_03_8004330C(s16);
void func_ovl12_03_8004337C(UnkStruct_ovl12_03_80045C84 *);
void func_ovl12_03_80043408(UnkStruct_ovl12_03_80045C84 *);
void func_ovl12_03_80043668(void);
void func_ovl12_03_800437BC(void);
void func_ovl12_03_800437FC(void);
void func_ovl12_03_80043844(void);
void func_ovl12_03_8004395C(f32);
void func_ovl12_03_800439A4(void);
void func_ovl12_03_80043ABC(void);
void func_ovl12_03_80043ADC(s32, s32, s32, f32, s32);
void func_ovl12_03_80043B04(void);
void func_ovl12_03_80043B54(void);
void func_ovl12_03_80043BA0(void);
void func_ovl12_03_80043BEC(void);
void func_ovl12_03_80043C80(void);
void func_ovl12_03_80043D98(void);
void func_ovl12_03_80043E00(void);
void func_ovl12_03_80043E68(void);
void func_ovl12_03_80043EB4(void);
void func_ovl12_03_80043EBC(void);
void func_ovl12_03_80043EFC(void);
void func_ovl12_03_80043F68(void);
void func_ovl12_03_8004418C(s32);
void func_ovl12_03_800442CC(void);
void func_ovl12_03_80044380(UnkStructA *);
void func_ovl12_03_80044440(UnkStructA *);
void func_ovl12_03_800444B8(s32, UnkStructA *);
void func_ovl12_03_800444EC(f32, f32, f32);
void func_ovl12_03_80044548(void);
void func_ovl12_03_80044560(void);

/* statics inlined everywhere: each leaves a `jr ra; nop` just before its
 * first caller */
static void func_ovl12_03_80043018(void);
static void func_ovl12_03_80043060(void);
static void func_ovl12_03_800430F8(void);
static void func_ovl12_03_80043100(void);
static void func_ovl12_03_8004316C(f32, s32, s32);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl12_03_800430B0() \
    D_ovl12_03_80045EBC = func_ovl12_03_80044AC8(); func_ovl12_03_80044AA8(&D_ovl12_03_80045EB0); func_ovl12_03_80044AD0(D_ovl12_03_80045EBC, D_ovl12_03_80045EA0)

/* .bss */
u8 D_ovl12_03_80045EA0[0x10];
Vec3f D_ovl12_03_80045EB0;
s32 D_ovl12_03_80045EBC;
s32 D_ovl12_03_80045EC0;
s32 D_ovl12_03_80045EC4;
s32 D_ovl12_03_80045EC8[2]; /* the second word unused */
/* a position (func_ovl12_03_8004316C, func_ovl12_03_800444EC); the last
 * word unused */
f32 D_ovl12_03_80045ED0[4];
UnkStruct_ovl12_03_80045EE0 D_ovl12_03_80045EE0;

/* .data */
/* passed to func_ovl12_03_800457A0: three 12-byte records */
u32 D_ovl12_03_80045BE0[][3] = {
    { 0xD00003, 0x1000F, 4 },
    { 0xCF0001, 0xE, 4 },
    { 0xD10002, 0xF, 4 },
};
/* four 12-byte records, each passed to func_ovl12_03_80045948 */
u32 D_ovl12_03_80045C04[][3] = {
    { 0, 0x1D, 0xFB },
    { 1, 0x1F, 0xFD },
    { 2, 0x1E, 0xFC },
    { 3, 0x20, 0xFE },
};
UnkStruct_ovl12_03_80045C34 D_ovl12_03_80045C34[] = {
    { NULL, 3900.0f, 400.0f, 1400.0f, 0x405 },
    { NULL, 4100.0f, 400.0f, 1400.0f, 0x406 },
    { NULL, 3900.0f, 400.0f, 1600.0f, 0x407 },
    { NULL, 4100.0f, 400.0f, 1600.0f, 0x408 },
};
UnkStruct_ovl12_03_80045C84 D_ovl12_03_80045C84[] = {
    { NULL, 1350.0f, 802.0f, 750.0f, 0x405, 0 },
    { NULL, 2950.0f, 802.0f, 750.0f, 0x406, 1 },
    { NULL, 1350.0f, 802.0f, 2250.0f, 0x407, 2 },
    { NULL, 2950.0f, 802.0f, 2250.0f, 0x408, 3 },
};
UnkStruct_ovl12_03_80045CE4 D_ovl12_03_80045CE4[] = {
    { NULL, 1600.0f, 200.0f, 1400.0f, 180.0f },
    { NULL, 1500.0f, 200.0f, 1600.0f, 0.0f },
    { NULL, 2000.0f, 200.0f, 1400.0f, 180.0f },
    { NULL, 1900.0f, 200.0f, 1600.0f, 0.0f },
    { NULL, 2600.0f, 200.0f, 1400.0f, 180.0f },
    { NULL, 2500.0f, 200.0f, 1600.0f, 0.0f },
    { NULL, 3000.0f, 200.0f, 1400.0f, 180.0f },
    { NULL, 2900.0f, 200.0f, 1600.0f, 0.0f },
};
UnkStruct_ovl12_03_80045CE4 D_ovl12_03_80045D84[] = {
    { NULL, 1550.0f, 200.0f, 1000.0f, 180.0f },
    { NULL, 1550.0f, 200.0f, 2000.0f, 0.0f },
    { NULL, 1950.0f, 200.0f, 1000.0f, 180.0f },
    { NULL, 1950.0f, 200.0f, 2000.0f, 0.0f },
    { NULL, 2350.0f, 200.0f, 1000.0f, 180.0f },
    { NULL, 2350.0f, 200.0f, 2000.0f, 0.0f },
    { NULL, 2750.0f, 200.0f, 1000.0f, 180.0f },
    { NULL, 2750.0f, 200.0f, 2000.0f, 0.0f },
};
UnkStruct_ovl12_03_80045E24 D_ovl12_03_80045E24[] = {
    { NULL, 400.0f, 200.0f, 1300.0f },
};
UnkStruct_ovl12_03_80045E24 D_ovl12_03_80045E34 = { NULL, 3850.0f, 400.0f, 1350.0f };

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl12_03_80044598(void) {
}

static void func_ovl12_03_80044590(void) {
}

static void func_ovl12_03_80044588(void) {
}

static void func_ovl12_03_80044580(void) {
}

static void func_ovl12_03_80044578(void) {
}

static void func_ovl12_03_80044570(void) {
}

static void func_ovl12_03_80044568(void) {
}

void func_ovl12_03_80044560(void) {
}

void func_ovl12_03_80044548(void) {
    D_ovl12_03_80045EC4 = -1;
    D_ovl12_03_80045EC8[0] = -1;
}

void func_ovl12_03_800444EC(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl12_03_80045128(D_ovl12_03_80045ED0[0], D_ovl12_03_80045ED0[1], D_ovl12_03_80045ED0[2]);
    func_ovl12_03_80045148(arg0, arg1, arg2);
    func_ovl12_03_80045458(180);
}

void func_ovl12_03_800444B8(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl12_03_800459E0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl12_03_80044440(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl12_03_80045190(0x10);
    }
    func_ovl12_03_800452F0(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        func_ovl12_03_80045368(arg0);
        func_ovl12_03_80045480();
    }
}

void func_ovl12_03_80044380(UnkStructA *arg0) {
    func_ovl12_03_80045458(10);
    func_ovl12_03_80044970(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl12_03_80045458(60);
}

void func_ovl12_03_80043EFC(void) {
    UnkStructA *obj;

    func_ovl12_03_80043EBC();
    func_ovl12_03_800449D0(func_ovl12_03_80044440);
    func_ovl12_03_80044A20(func_ovl12_03_80044380);
    obj = func_ovl12_03_800454C0(0x2E5);
    func_ovl12_03_800454D0(obj, 0x20000001);
    obj->unk18 = 0.03f;
    obj->unk1C = 0.0f;
}

void func_ovl12_03_800442CC(void) {
    s16 i;
    UnkStructA *obj;

    for (i = 0; i < 8; i++) {
        obj = func_ovl12_03_80045330(0x318, 0x40, D_ovl12_03_80045CE4[i].unk4, D_ovl12_03_80045CE4[i].unk8,
                                     D_ovl12_03_80045CE4[i].unkC);
        func_ovl12_03_800452E8(obj, 0x01080000);
        obj->unk40->unk20 = D_ovl12_03_80045CE4[i].unk10;
        D_ovl12_03_80045CE4[i].unk0 = obj;
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl12_03_8004418C(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl12_03_80043F68();
            break;
        case 16:
            func_ovl12_03_80043BA0();
            break;
        case 17:
            func_ovl12_03_80043B54();
            break;
        case 18:
            func_ovl12_03_80043B04();
            break;
        case 4:
            func_ovl12_03_800439A4();
            break;
        case 5:
            func_ovl12_03_80043844();
            break;
        case 0x50:
            func_ovl12_03_800437BC();
            break;
        case 0x52:
            func_ovl12_03_80043668();
            break;
        case 3:
            UNK_MACRO_ovl12_03_800430B0();
            break;
        case 12:
            func_ovl12_03_80044B30(1);
            break;
        case 0x53:
            break;
    }
}

void func_ovl12_03_80043F68(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl12_03_80043EFC();
    func_ovl12_03_800457A0(D_ovl12_03_80045BE0);
    func_ovl12_03_800448E8(0x2DB);
    p = D_ovl12_03_80045C04;
    count = 4;
    for (i = 0; i < count; i++) {
        func_ovl12_03_80045948((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl12_03_80044900(0x2E1);
    func_ovl12_03_80044A98();
    func_ovl12_03_80043E68();
    func_ovl12_03_80043E00();
    func_ovl12_03_80043D98();
    if (func_ovl12_03_800456C0(0x405) && func_ovl12_03_800456C0(0x406) && func_ovl12_03_800456C0(0x407) &&
        func_ovl12_03_800456C0(0x408)) {
        func_ovl12_03_80043174();
    }
    func_ovl12_03_80043C80();
    func_ovl12_03_80043BEC();
    func_ovl12_03_80045778(0x375, 0x3BB, 0x1E, 0x19, 0);
    func_ovl12_03_80045760(0xF, 0x7E, 0);
}

void func_ovl12_03_80043EBC(void) {
    func_ovl12_03_800456B8(0x400);
    func_ovl12_03_800456B8(0x401);
    func_ovl12_03_800456B8(0x402);
    func_ovl12_03_800456B8(0x403);
    func_ovl12_03_800456B8(0x404);
}

void func_ovl12_03_80043EB4(void) {
}

void func_ovl12_03_80043E68(void) {
    UnkStructA *obj;

    obj = func_ovl12_03_80045330(0x31B, 0xD0, 0.0f, 0.0f, 0.0f);
    func_ovl12_03_800452E8(obj, 0x01080000);
    D_ovl12_03_80045E34.unk0 = obj;
}

void func_ovl12_03_80043E00(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        func_ovl12_03_80043248(&D_ovl12_03_80045C34[i]);
    }
}

void func_ovl12_03_80043D98(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        func_ovl12_03_8004337C(&D_ovl12_03_80045C84[i]);
    }
}

void func_ovl12_03_80043C80(void) {
    s16 i;
    UnkStruct_ovl12_03_80045CE4 *p;
    UnkStructA *obj;

    for (i = 0; i < 8; i++) {
        p = &D_ovl12_03_80045D84[i];
        obj = func_ovl12_03_80045330(0x319, 0x40, p->unk4, p->unk8, p->unkC);
        func_ovl12_03_800452E8(obj, 0x01080000);
        obj->unk40->unk20 = p->unk10;
        p->unk0 = obj;
        obj->unk40->unkC |= 0x8000;
        func_ovl12_03_80044FF0(p->unk0->unk40, 2);
        func_ovl12_03_80044FF8(p->unk0->unk40, 0x31A, 0, 0);
        func_ovl12_03_80044FF8(p->unk0->unk40, 0x31A, 1, 1);
    }
}

void func_ovl12_03_80043BEC(void) {
    s16 i;
    UnkStructA *obj;

    for (i = 0; i < 1; i++) {
        obj = func_ovl12_03_80045330(0x317, 0xD0, D_ovl12_03_80045E24[i].unk4, D_ovl12_03_80045E24[i].unk8,
                                     D_ovl12_03_80045E24[i].unkC);
        func_ovl12_03_800452E8(obj, 0x01000000);
        D_ovl12_03_80045E24[i].unk0 = obj;
    }
}

void func_ovl12_03_80043BA0(void) {
    func_ovl12_03_80044AA0(8, 1, 0xF);
    func_ovl12_03_80043ADC(0, 0x40, 0xC0, 0.0f, 0);
}

void func_ovl12_03_80043B54(void) {
    func_ovl12_03_80044AA0(0xC, 4, 8);
    func_ovl12_03_80043ADC(1, 0x80, 0, 0.0f, 0);
}

void func_ovl12_03_80043B04(void) {
    func_ovl12_03_80044AA0(0x13, 1, 0x19);
    func_ovl12_03_80043ADC(2, 0, 0x80, 0.0f, 3);
}

void func_ovl12_03_80043ADC(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl12_03_80045EE0.unk0 = arg0;
    D_ovl12_03_80045EE0.unk4 = arg1;
    D_ovl12_03_80045EE0.unk8 = arg2;
    D_ovl12_03_80045EE0.unkC = arg3;
    D_ovl12_03_80045EE0.unk10 = arg4;
}

void func_ovl12_03_80043ABC(void) {
    func_ovl12_03_800439A4();
}

void func_ovl12_03_800439A4(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl12_03_80044AF8();
    switch (D_ovl12_03_80045EE0.unk8) {
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
        func_ovl12_03_80045148(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl12_03_80045EE0.unkC;
        func_ovl12_03_80045150(&sp1C, NULL, NULL);
        func_ovl12_03_80045148(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl12_03_80044AE0(D_ovl12_03_80045EE0.unk4);
}

void func_ovl12_03_8004395C(f32 arg0) {
    f32 sp1C;

    func_ovl12_03_80045150(&sp1C, NULL, NULL);
    func_ovl12_03_80045148(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl12_03_80043844(void) {
    s32 i;

    func_ovl12_03_800437FC();
    if (D_ovl12_03_80045EE0.unk0 == 0) {
        func_ovl12_03_800459C0(0xB1);
        func_ovl12_03_800452E8(D_ovl12_03_80045E24[0].unk0, 0x04000000);
        for (i = 0; i < 150; i++) {
            func_ovl12_03_80045480();
        }
        func_ovl12_03_800459C0(0xB2);
        for (;;) {
            if (D_ovl12_03_80045E24[0].unk0->unk40->unkC & 0x40) {
                break;
            }
            func_ovl12_03_80045480();
        }
    } else {
        D_ovl12_03_80045E24[0].unk0->unk40->unk48->unk4->unk4 =
            func_ovl12_03_80045028(D_ovl12_03_80045E24[0].unk0->unk40, 0) - 1.0f;
    }
}

void func_ovl12_03_800437FC(void) {
    func_ovl12_03_80044AE8(D_ovl12_03_80045EE0.unk4, 3, 4.0f, D_ovl12_03_80045EE0.unk10, 0, 1, 1);
}

void func_ovl12_03_800437BC(void) {
    if (func_ovl12_03_80044AB0(0x13, 0x19, 0x14, 0x1E) != 0) {
        func_ovl12_03_800449E0(0x7C, 0x12, 0);
    }
}

void func_ovl12_03_80043668(void) {
    if (func_ovl12_03_80044AB0(0xD, 7, 0xE, 8) != 0) {
        func_ovl12_03_80044B98(0x1D);
        func_ovl12_03_80043408(&D_ovl12_03_80045C84[0]);
    }
    if (func_ovl12_03_80044AB0(0x1D, 7, 0x1E, 8) != 0) {
        func_ovl12_03_80044B98(0xD);
        func_ovl12_03_80043408(&D_ovl12_03_80045C84[1]);
    }
    if (func_ovl12_03_80044AB0(0xD, 0x16, 0xE, 0x17) != 0) {
        func_ovl12_03_80044B98(0x1D);
        func_ovl12_03_80043408(&D_ovl12_03_80045C84[2]);
    }
    if (func_ovl12_03_80044AB0(0x1D, 0x16, 0x1E, 0x17) != 0) {
        func_ovl12_03_80044B98(0x28);
        func_ovl12_03_80043408(&D_ovl12_03_80045C84[3]);
    }
    if (func_ovl12_03_80044AB0(0x28, 0xF, 0x28, 0xF) != 0 && func_ovl12_03_800456C0(0x405) &&
        func_ovl12_03_800456C0(0x406) && func_ovl12_03_800456C0(0x407) && func_ovl12_03_800456C0(0x408)) {
        func_ovl12_03_80044AE0(0xC0);
        func_ovl12_03_80043108();
    }
}

void func_ovl12_03_80043408(UnkStruct_ovl12_03_80045C84 *arg0) {
    UnkStruct_ovl12_03_80045C34 *p;
    s32 i;

    if (func_ovl12_03_800456C0(arg0->unk10) == 0) {
        func_ovl12_03_800456B0(arg0->unk10);
        func_ovl12_03_800459C0(0x29);
        func_ovl12_03_80044A58(1);
        func_ovl12_03_80044A50(0);
        func_ovl12_03_80044AD8(1);
        p = &D_ovl12_03_80045C34[arg0->unk14];
        func_ovl12_03_80045458(10);
        func_ovl12_03_80045300(arg0->unk0);
        func_ovl12_03_8004337C(arg0);
        func_ovl12_03_80045458(10);
        func_ovl12_03_8004330C(arg0->unk14);
        func_ovl12_03_800459C0(0xB7);
        func_ovl12_03_80043248(p);
        for (i = 0; i < 255; i += 5) {
            p->unk0->unk40->unk36 = i;
            func_ovl12_03_80045480();
        }
        arg0->unk0->unk40->unk36 = 255;
        func_ovl12_03_80045458(30);
        if (func_ovl12_03_800456C0(0x405) && func_ovl12_03_800456C0(0x406) && func_ovl12_03_800456C0(0x407) &&
            func_ovl12_03_800456C0(0x408)) {
            func_ovl12_03_80045458(120);
            func_ovl12_03_800459C0(0x2C);
            func_ovl12_03_80043174();
            func_ovl12_03_80045458(30);
        }
        func_ovl12_03_80043138(0);
        func_ovl12_03_80044AD8(0);
        func_ovl12_03_80044A58(0);
        func_ovl12_03_80044A50(1);
    }
}

void func_ovl12_03_8004337C(UnkStruct_ovl12_03_80045C84 *arg0) {
    s32 id;
    UnkStructA *obj;

    if (func_ovl12_03_800456C0(arg0->unk10) == 0) {
        id = 0x1B3;
    } else {
        id = 0x1B0;
    }
    obj = func_ovl12_03_80045330(id, 0xD0, arg0->unk4, arg0->unk8, arg0->unkC);
    obj->unk40->unk28 = 2.0f;
    obj->unk40->unk30 = 2.0f;
    if (obj != NULL) {
        func_ovl12_03_800452E8(obj, 0x01000000);
        arg0->unk0 = obj;
    }
}

void func_ovl12_03_8004330C(s16 arg0) {
    UnkStruct_ovl12_03_80045C34 *p;

    func_ovl12_03_80045248();
    func_ovl12_03_80045190(0x7F);
    p = &D_ovl12_03_80045C34[arg0];
    func_ovl12_03_80045128(p->unk4, p->unk8, p->unkC);
    func_ovl12_03_80045148(-90.0f, 45.0f, 2000.0f);
}

void func_ovl12_03_80043248(UnkStruct_ovl12_03_80045C34 *arg0) {
    UnkStructA *obj;

    if (func_ovl12_03_800456C0(arg0->unk10) != 0) {
        obj = func_ovl12_03_80045330(0x2A7, 0xD0, arg0->unk4, arg0->unk8, arg0->unkC);
        func_ovl12_03_800452E8(obj, 0x01080000);
        arg0->unk0 = obj;
        obj->unk40->unkC |= 0x8000;
        func_ovl12_03_80044FF0(arg0->unk0->unk40, 2);
        func_ovl12_03_80044FF8(arg0->unk0->unk40, 0x2A8, 0, 0);
        func_ovl12_03_80044FF8(arg0->unk0->unk40, 0x2A8, 1, 1);
    }
}



void func_ovl12_03_80043174(void) {
    func_ovl12_03_8004316C(40.0f, 15, 2);
}


/* Inlined into func_ovl12_03_80043174 only; that one is inlined into its
 * callers in turn. Called from more than one function it isn't inlined.
 * The parameter order sets func_ovl12_03_80043408's frame. */
static void func_ovl12_03_8004316C(f32 x, s32 z, s32 count) {
    s32 i;

    D_ovl12_03_80045ED0[0] = x * 100.0f;
    D_ovl12_03_80045ED0[1] = 0.0f;
    for (i = 0; i < count; i++) {
        D_ovl12_03_80045ED0[1] += func_ovl12_03_80044950(i) * 100.0f;
    }
    D_ovl12_03_80045ED0[1] += 100.0f;
    D_ovl12_03_80045ED0[2] = z * 100.0f;
    D_ovl12_03_80045EC0 = func_ovl12_03_80045890(0x28, (Vec3f *) D_ovl12_03_80045ED0, 0);
}

void func_ovl12_03_80043138(s32 arg0) {
    func_ovl12_03_80045250();
    func_ovl12_03_80045218(D_ovl12_03_80045EA0);
    func_ovl12_03_80045188(0x1F);
}

void func_ovl12_03_80043108(void) {
    func_ovl12_03_80043100();
    func_ovl12_03_800430F8();
    func_ovl12_03_80045898(D_ovl12_03_80045EC0);
    func_ovl12_03_80044A08();
}

static void func_ovl12_03_80043100(void) {
}

static void func_ovl12_03_800430F8(void) {
}

void func_ovl12_03_800430B0(void) {
    UNK_MACRO_ovl12_03_800430B0();
}

void func_ovl12_03_80043068(void) {
    func_ovl12_03_80043060();
    D_ovl12_03_80045EBC = func_ovl12_03_80044AC8();
    func_ovl12_03_80044AA8(&D_ovl12_03_80045EB0);
    func_ovl12_03_80044AD0(D_ovl12_03_80045EBC, D_ovl12_03_80045EA0);
}

static void func_ovl12_03_80043060(void) {
}

void func_ovl12_03_80043040(void) {
    func_ovl12_03_80044B30(1);
}

void func_ovl12_03_80043020(void) {
    func_ovl12_03_80043018();
    func_ovl12_03_80044B30(1);
}

static void func_ovl12_03_80043018(void) {
}

void func_ovl12_03_80043010(void) {
}
