/*
 * NON_MATCHING: ovl_0E_12's game object, complete: every function and its data.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 2, eu 2, jp 2
 *
 * What still differs in us (words):
 * - func_ovl0E_12_80043164 (2): `sll t4,s3,5` (the next call's &D_FCC[i])
 *   scheduled before the stores to unk0 and unk4; the original has it
 *   after them (ours: sll, unk4, unk0). IDO's scheduling follows source
 *   lines: with the two stores on separate lines it's 3 words, with the
 *   call on their line too 4. Assembling IDO's -S output with a label
 *   between the stores (two lines) and the call gives the original's
 *   order exactly, so the original has a block boundary there; the folded
 *   fake that fixed 80043A64 leaves its branch in here (a store fills its
 *   delay slot), and do/while(0), goto, labels, inlined statics, other
 *   fake tests and the permuter didn't give one.
 */
#include "common.h"

/*
 * ovl_0E_12's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_12_800462F0;

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
} UnkStruct_ovl0E_12_80045F94;

/* what replaces it once its flag (unk0) is set */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
} UnkStruct_ovl0E_12_80045FCC;

/* the five movers: each record is passed to its task */
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
} UnkStruct_ovl0E_12_80045FEC;

/* UnkStructA with the two words at 0x0C that func_ovl0E_12_800441D8 uses */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_12_800441D8;

void func_ovl0E_12_80044C48(s32);
void func_ovl0E_12_80044C60(s32);
f32 func_ovl0E_12_80044C70(void);
void func_ovl0E_12_80044C88(s32, s32, s32, s32, s32, s32);
void func_ovl0E_12_80044CD0(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_12_80044D30(void (*)(UnkStructA *));
void func_ovl0E_12_80044D40(s32, s32, s32);
void func_ovl0E_12_80044D80(void (*)(UnkStructA *));
void func_ovl0E_12_80044DB0(s32);
void func_ovl0E_12_80044DF8(void);
void func_ovl0E_12_80044E00(s32, s32, s32);
void func_ovl0E_12_80044E08(void *);
s32 func_ovl0E_12_80044E10(s32, s32, s32, s32);
s32 func_ovl0E_12_80044E28(void);
void func_ovl0E_12_80044E30(s32, void *);
void func_ovl0E_12_80044E38(s32);
void func_ovl0E_12_80044E40(s32);
void func_ovl0E_12_80044E48(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_12_80044E50(const char *);
void func_ovl0E_12_80044E58(void);
void func_ovl0E_12_80044E70(s32);
void func_ovl0E_12_80044E90(s32);
s32 func_ovl0E_12_80045390(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_12_80045398(s32);
void func_ovl0E_12_80045488(f32, f32, f32);
void func_ovl0E_12_800454A8(f32, f32, f32);
void func_ovl0E_12_800454B0(f32 *, f32 *, f32 *);
void func_ovl0E_12_800454F0(s32);
void func_ovl0E_12_80045500(s32);
void func_ovl0E_12_80045540(f32, f32);
f32 func_ovl0E_12_800455F0(f32 *, void *);
s32 func_ovl0E_12_800455F8(UnkStructA *, s32);
void func_ovl0E_12_80045648(UnkStructA *, s32);
void func_ovl0E_12_80045650(UnkStructA *, s32);
void func_ovl0E_12_80045660(UnkStructA *);
UnkStructA *func_ovl0E_12_80045670(s32, s32, s32, s32);
UnkStructA *func_ovl0E_12_80045680(UnkStructA *);
UnkStructA *func_ovl0E_12_80045690(s32, s32, f32, f32, f32);
void func_ovl0E_12_800456C8(UnkStructA *);
void func_ovl0E_12_80045758(UnkStructA *);
s32 func_ovl0E_12_80045798(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_12_800457A0(s32);
void func_ovl0E_12_800457A8(void);
void func_ovl0E_12_800457B8(s32);
void *func_ovl0E_12_800457C0(void);
void func_ovl0E_12_800457E0(void);
s32 func_ovl0E_12_80045958(s32);
void func_ovl0E_12_80045A10(s32);
void func_ovl0E_12_80045A18(s32);
s32 func_ovl0E_12_80045A20(s32);
void func_ovl0E_12_80045AD8(s32, s32, s32, s32, s32);
void func_ovl0E_12_80045AE8(s32, s32, s32);
void func_ovl0E_12_80045B00(u32 (*)[3]);
void func_ovl0E_12_80045BE8(s32, f32, f32, f32, s32);
void func_ovl0E_12_80045BF0(s32, f32 *, s32);
void func_ovl0E_12_80045C18(s16, s32);
void func_ovl0E_12_80045C20(s16, s32);
void func_ovl0E_12_80045CA8(s32, s32, s32);
void func_ovl0E_12_80045D20(s32);
void func_ovl0E_12_80045D40(s32, f32, f32, f32);
void func_ovl0E_12_80045D48(s32, f32 *);
void func_ovl0E_12_80045E98(void);
void func_ovl0E_12_80045EA0(void);

void func_ovl0E_12_80043010(void);
void func_ovl0E_12_80043018(void);
void func_ovl0E_12_80043084(void);
void func_ovl0E_12_800430A4(void);
void func_ovl0E_12_800430DC(void);
void func_ovl0E_12_800430FC(void);
void func_ovl0E_12_8004311C(UnkStruct_ovl0E_12_80045FCC *);
void func_ovl0E_12_80043164(void);
void func_ovl0E_12_800433AC(void);
void func_ovl0E_12_800433F4(void);
void func_ovl0E_12_8004345C(void);
void func_ovl0E_12_80043534(void);
void func_ovl0E_12_800435AC(void);
void func_ovl0E_12_80043624(void);
void func_ovl0E_12_8004364C(void);
void func_ovl0E_12_800436D0(f32);
void func_ovl0E_12_80043718(void);
void func_ovl0E_12_80043830(void);
void func_ovl0E_12_8004386C(s32, s32, s32, f32, s32);
void func_ovl0E_12_80043894(void);
void func_ovl0E_12_800438E4(void);
void func_ovl0E_12_80043934(void);
void func_ovl0E_12_80043984(void);
void func_ovl0E_12_800439D4(void);
void func_ovl0E_12_80043A14(void);
void func_ovl0E_12_80043A64(void);
void func_ovl0E_12_80043CDC(void);
void func_ovl0E_12_80043DEC(void);
void func_ovl0E_12_80043DF4(void);
void func_ovl0E_12_80043E34(void);
void func_ovl0E_12_80043E6C(void);
void func_ovl0E_12_80043FE4(s32);
void func_ovl0E_12_8004418C(void);
void func_ovl0E_12_800441D8(void);
void func_ovl0E_12_80044314(void);
void func_ovl0E_12_8004441C(void);
void func_ovl0E_12_800446BC(UnkStructA *);
void func_ovl0E_12_80044780(UnkStructA *);
void func_ovl0E_12_80044818(s32, UnkStructA *);
void func_ovl0E_12_8004484C(f32, f32, f32);
void func_ovl0E_12_800448A8(void);
void func_ovl0E_12_800448C0(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0E_12_8004315C(void);
static void func_ovl0E_12_800433A4(void);
static void func_ovl0E_12_80043A0C(void);
static void func_ovl0E_12_80043444(void);
static void func_ovl0E_12_8004344C(void);
static void func_ovl0E_12_80043454(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_12_800433AC() \
    D_ovl0E_12_800462CC = func_ovl0E_12_80044E28(); func_ovl0E_12_80044E08(&D_ovl0E_12_800462C0); func_ovl0E_12_80044E30(D_ovl0E_12_800462CC, D_ovl0E_12_800462B0)

/* .bss */
u8 D_ovl0E_12_800462B0[0x10];
Vec3f D_ovl0E_12_800462C0;
s32 D_ovl0E_12_800462CC;
u8 D_ovl0E_12_800462D0[0x4]; /* unused (func_ovl0E_12_800448F0) */
s32 D_ovl0E_12_800462D4;
s32 D_ovl0E_12_800462D8;
u8 D_ovl0E_12_800462DC[0x4]; /* unused (func_ovl0E_12_800448F0) */
Vec3f D_ovl0E_12_800462E0;
u8 D_ovl0E_12_800462EC[0x4]; /* unused (func_ovl0E_12_800448F0) */
UnkStruct_ovl0E_12_800462F0 D_ovl0E_12_800462F0;
UnkStructA *D_ovl0E_12_80046304;

/* .data */
/* passed to func_ovl0E_12_80045B00: three 12-byte records */
u32 D_ovl0E_12_80045F40[][3] = {
    { 0xA10003, 0xE, 4 },
    { 0xA40002, 0xE, 4 },
    { 0x9F0002, 0xE, 4 },
};
/* four 12-byte records, each passed to func_ovl0E_12_80045CA8 */
u32 D_ovl0E_12_80045F64[][3] = {
    { 0, 0xE, 0xEC },
    { 1, 1, 0xDE },
    { 2, 0xD, 0xEB },
    { 3, 0xF, 0xED },
};
UnkStruct_ovl0E_12_80045F94 D_ovl0E_12_80045F94[1] = {
    { NULL, -1, 0xA0, -1, -1, -1, -1, 400.0f, 60.0f, 275.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
};
UnkStruct_ovl0E_12_80045FCC D_ovl0E_12_80045FCC[1] = {
    { 0x416, 395.0f, 60.0f, 285.0f, 180.0f, 0x27, 4, 0x1C, 0x28, 0x1D, 1 },
};
UnkStruct_ovl0E_12_80045FEC D_ovl0E_12_80045FEC[5] = {
    { -1, NULL, 0x1B6, 0x20, 0x30, 0.0f, -15.0f, 1, 0x78, 165.0f, 200.0f, 295.0f },
    { -1, NULL, 0x1B6, 0x20, 0x30, 0.0f, -15.0f, 1, 0x78, 185.0f, 200.0f, 295.0f },
    { -1, NULL, 0x1B6, 0x20, 0x30, 0.0f, -15.0f, 1, 0x78, 205.0f, 200.0f, 295.0f },
    { -1, NULL, 0x1B6, 0x20, 0x30, 0.0f, -15.0f, 1, 0x78, 225.0f, 200.0f, 295.0f },
    { -1, NULL, 0x1B6, 0x20, 0x30, 0.0f, -15.0f, 1, 0x78, 245.0f, 200.0f, 295.0f },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0E_12_800448F0(void) {
    D_ovl0E_12_800462D0[0] = D_ovl0E_12_800462DC[0] + D_ovl0E_12_800462EC[0];
}

static void func_ovl0E_12_800448E8(void) {
}

static void func_ovl0E_12_800448E0(void) {
}

static void func_ovl0E_12_800448D8(void) {
}

static void func_ovl0E_12_800448D0(void) {
}

static void func_ovl0E_12_800448C8(void) {
}

void func_ovl0E_12_800448C0(void) {
}

void func_ovl0E_12_800448A8(void) {
    D_ovl0E_12_800462D4 = -1;
    D_ovl0E_12_800462D8 = -1;
}

void func_ovl0E_12_8004484C(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_12_80045488(D_ovl0E_12_800462E0.x, D_ovl0E_12_800462E0.y, D_ovl0E_12_800462E0.z);
    func_ovl0E_12_800454A8(arg0, arg1, arg2);
    func_ovl0E_12_800457B8(180);
}

void func_ovl0E_12_80044818(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_12_80045D40(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_12_80044780(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_12_80045650(arg0, 0x01000000);
    func_ovl0E_12_80045BF0(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_12_80045BF0(13, pos, 0);
    func_ovl0E_12_80045D48(180, pos);
}

void func_ovl0E_12_800446BC(UnkStructA *arg0) {
    func_ovl0E_12_80045650(arg0, 0x04000000);
    func_ovl0E_12_800457B8(10);
    func_ovl0E_12_80044CD0(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_12_80045D20(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_12_800457B8(60);
}

void func_ovl0E_12_8004441C(void) {
    UnkStruct_ovl0E_12_80045FEC *rec;
    UnkStructA *obj;
    s16 moving;
    f32 pos[3];
    s32 heard;

    rec = func_ovl0E_12_800457C0();
    obj = rec->unk4;
    func_ovl0E_12_800457B8(func_ovl0E_12_80045958(120));
    for (heard = 0, moving = 0;;) {
        obj->unk40->unk10 = rec->unk1C * 10.0f;
        obj->unk40->unk14 = rec->unk20 * 10.0f;
        obj->unk40->unk18 = rec->unk24 * 10.0f;
        obj->unk68 = 0.0f;
        obj->unk70 = 1.6333334f;
        func_ovl0E_12_80045648(obj, 0x01000000);
        while (TRUE) {
            func_ovl0E_12_80045758(obj);
            if (moving == 1) {
                obj->unk40->unk10 += rec->unk10;
                obj->unk40->unk18 += rec->unk14;
            }
            func_ovl0E_12_800456C8(obj);
            if (obj->unk6C == 0.0f && obj->unk68 == 0.0f) {
                if (heard == 0) {
                    pos[0] = obj->unk40->unk10;
                    pos[1] = obj->unk40->unk14;
                    pos[2] = obj->unk40->unk18;
                    if (func_ovl0E_12_800455F0(pos, D_ovl0E_12_800462B0) < 700.0f) {
                        func_ovl0E_12_80045D40(0x78, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
                        heard = 1;
                    }
                }
                moving = 1;
            }
            if (obj->unk40->unk14 <= func_ovl0E_12_80044C70()) {
                func_ovl0E_12_80045650(obj, 0x01000000);
                heard = 0;
                moving = 0;
                break;
            }
            func_ovl0E_12_800457E0();
        }
        func_ovl0E_12_800457B8(func_ovl0E_12_80045958(rec->unk1A - rec->unk18) + rec->unk18);
    }
}

void func_ovl0E_12_80043E6C(void) {
    UnkStructA *obj;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_12_80043DF4();
    func_ovl0E_12_80044D30(func_ovl0E_12_80044780);
    func_ovl0E_12_80044D80(func_ovl0E_12_800446BC);
    func_ovl0E_12_80045B00(D_ovl0E_12_80045F40);
    func_ovl0E_12_80044C48(0x1A0);
    obj = func_ovl0E_12_80045690(0x1A1, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_12_80045648(obj, 0x01000000);
    func_ovl0E_12_80045648(func_ovl0E_12_80045690(0x365, 0x50, 0.0f, 0.0f, 0.0f), 0x01080000);
    p = D_ovl0E_12_80045F64;
    count = 4;
    for (i = 0; i < count; i++) {
        func_ovl0E_12_80045CA8((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_12_80044C60(0x1A8);
    func_ovl0E_12_80044DF8();
    func_ovl0E_12_80043CDC();
    func_ovl0E_12_80043A64();
    func_ovl0E_12_800439D4();
    func_ovl0E_12_80045390(obj->unk40, 0, 0, 0, 2, 0x400);
    func_ovl0E_12_80045AD8(0x38E, 0x3DE, 0xFF, 0x87, 0x1F);
    func_ovl0E_12_80045AE8(0xFF, 0xA1, 0x1D);
}

void func_ovl0E_12_80044314(void) {
    func_ovl0E_12_80044DB0(0);
    func_ovl0E_12_80045C18(func_ovl0E_12_80044E28(), 2);
    func_ovl0E_12_80045C20(func_ovl0E_12_80044E28(), 8);
    func_ovl0E_12_80044E50("WM1 WG1 WAP WSH WDNW WB2 ST30 M0 ST10 WB2");
    func_ovl0E_12_80044E50("WM1 WG1 WAP WSH ST30 WDSE WB0 ST30");
    func_ovl0E_12_80044E50("WM1 WG1 WAP WSH ST1");
    func_ovl0E_12_80044E70(0x800);
    func_ovl0E_12_80044E50("WM1 WG1 WAP WSH WDSE WB1 ST1 WDS WB4 ST1 WDE WB1 ST1");
    func_ovl0E_12_80044E50("WM1 WG1 WAP WSH WDN WB3 ST1 WDE WB1 ST1 M0 ST1 WDW WB2 ST1");
    func_ovl0E_12_80044E50("WM1 WG1 WAP WSH WDE WB0 ST10");
    func_ovl0E_12_80044E50("WM1 WG1 WAP WSH ST1");
    func_ovl0E_12_80044E70(0x800);
    func_ovl0E_12_80044E50("WM1 WG1 WAP M1 ST10");
    func_ovl0E_12_80044E70(0x400);
    func_ovl0E_12_80044E50("WM1 WG1 WAP WSH ST10 WDE WB1 ST10 M2 ST1");
    func_ovl0E_12_80044E70(0x800);
    func_ovl0E_12_80044E50("WM1 WG1 WAP WSH WDW WB1 ST1 WDS WB3 ST1 WDN WB0 ST10");
    func_ovl0E_12_800457B8(60);
    func_ovl0E_12_80045E98();
    func_ovl0E_12_800457A8();
}

void func_ovl0E_12_800441D8(void) {
    UnkStructA *obj;

    obj = func_ovl0E_12_80045670(0x1C1, 0x01000000, 0x80, 0);
    if (obj == NULL) {
        return;
    }
    func_ovl0E_12_80044C88(0x26, 4, 0x10, 0x27, 0x11, 0x1F);
    obj->unk40->unk10 = 3850.0f;
    obj->unk40->unk14 = 600.0f;
    obj->unk40->unk18 = 1650.0f;
    obj->unk30 = 1;
    obj->unk34 = 100.0f;
    obj->unk38 = 100.0f;
    while (TRUE) {
        ((UnkStruct_ovl0E_12_800441D8 *) obj)->unkC = 0xC0;
        if (((UnkStruct_ovl0E_12_800441D8 *) obj)->unk10 & 0xC0) {
            func_ovl0E_12_80045BE8(0xE, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
            func_ovl0E_12_80044C88(0x26, 4, 0x10, 0x27, 0x11, 0x11);
            func_ovl0E_12_80045660(obj);
            func_ovl0E_12_800457A8();
        }
        func_ovl0E_12_800457E0();
    }
}

void func_ovl0E_12_8004418C(void) {
    func_ovl0E_12_80044E00(0x12, 2, 2);
    func_ovl0E_12_8004386C(1, 0x80, 0x80, 0.0f, 0);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_12_80043FE4(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0E_12_80043E6C();
            break;
        case 17:
            func_ovl0E_12_80043894();
            break;
        case 18:
            func_ovl0E_12_80043984();
            break;
        case 19:
            func_ovl0E_12_80043934();
            break;
        case 20:
            func_ovl0E_12_800438E4();
            break;
        case 21:
            func_ovl0E_12_80043894();
            break;
        case 4:
            func_ovl0E_12_80043830();
            break;
        case 5:
            func_ovl0E_12_80043624();
            break;
        case 0x50:
            func_ovl0E_12_8004345C();
            break;
        case 3:
            func_ovl0E_12_800433F4();
            break;
        case 12:
            func_ovl0E_12_800430FC();
            break;
        case 1:
            func_ovl0E_12_800430A4();
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_12_80043E34(void) {
    func_ovl0E_12_80043DF4();
    func_ovl0E_12_80044D30(func_ovl0E_12_80044780);
    func_ovl0E_12_80044D80(func_ovl0E_12_800446BC);
}

void func_ovl0E_12_80043DF4(void) {
    func_ovl0E_12_80045A18(0x400);
    func_ovl0E_12_80045A18(0x401);
    func_ovl0E_12_80045A18(0x402);
    func_ovl0E_12_80045A18(0x403);
    func_ovl0E_12_80045A18(0x404);
}

void func_ovl0E_12_80043DEC(void) {
}

void func_ovl0E_12_80043CDC(void) {
    UnkStructA *obj;
    UnkStructA *p;
    s32 i;

    for (i = 0; i < 5; i++) {
        obj = func_ovl0E_12_80045690(D_ovl0E_12_80045FEC[i].unk8, D_ovl0E_12_80045FEC[i].unkC,
                                     D_ovl0E_12_80045FEC[i].unk1C * 10.0f, D_ovl0E_12_80045FEC[i].unk20 * 10.0f,
                                     D_ovl0E_12_80045FEC[i].unk24 * 10.0f);
        p = func_ovl0E_12_80045680(obj);
        p->unk54 = 2.0f;
        p->unk4C = 2.0f;
        func_ovl0E_12_80045648(obj, D_ovl0E_12_80045FEC[i].unkA);
        D_ovl0E_12_80045FEC[i].unk4 = obj;
        obj->unk30 = 1;
        obj->unk34 = 100.0f;
        obj->unk38 = 50.0f;
    }
}

void func_ovl0E_12_80043A64(void) {
    s32 i;

    func_ovl0E_12_80043A14();
    for (i = 0; i < 1; i++) {
        if (func_ovl0E_12_80045A20(D_ovl0E_12_80045FCC[i].unk0) == 0) {
            D_ovl0E_12_80045F94[i].unk0 = func_ovl0E_12_80045690(D_ovl0E_12_80045F94[i].unk8, 0xD0, 0.0f, 0.0f, 0.0f);
            func_ovl0E_12_80045648(D_ovl0E_12_80045F94[i].unk0, 0x01080000);
            func_ovl0E_12_80045650(D_ovl0E_12_80045F94[i].unk0, 0x02000000);
            if (D_ovl0E_12_80045F94[i].unkC != -1 && D_ovl0E_12_80045F94[i].unkE != -1 &&
                D_ovl0E_12_80045F94[i].unk10 != -1 && D_ovl0E_12_80045F94[i].unk12 != -1) {
                D_ovl0E_12_80045F94[i].unk4 = func_ovl0E_12_80045390(
                    D_ovl0E_12_80045F94[i].unk0->unk40, 0, D_ovl0E_12_80045F94[i].unkC, D_ovl0E_12_80045F94[i].unkE,
                    D_ovl0E_12_80045F94[i].unk10, D_ovl0E_12_80045F94[i].unk12);
                if (D_ovl0E_12_80045F94[i].unk4 == -1) {
                    while (TRUE) {
                    }
                }
            }
            D_ovl0E_12_80045F94[i].unk0->unk40->unk10 = D_ovl0E_12_80045F94[i].unk14 * 10.0f;
            D_ovl0E_12_80045F94[i].unk0->unk40->unk14 = D_ovl0E_12_80045F94[i].unk18 * 10.0f;
            D_ovl0E_12_80045F94[i].unk0->unk40->unk18 = D_ovl0E_12_80045F94[i].unk1C * 10.0f;
            D_ovl0E_12_80045F94[i].unk0->unk40->unk1C = D_ovl0E_12_80045F94[i].unk20;
            D_ovl0E_12_80045F94[i].unk0->unk40->unk20 = D_ovl0E_12_80045F94[i].unk24;
            D_ovl0E_12_80045F94[i].unk0->unk40->unk24 = D_ovl0E_12_80045F94[i].unk28;
            D_ovl0E_12_80045F94[i].unk0->unk40->unk28 = D_ovl0E_12_80045F94[i].unk2C;
            D_ovl0E_12_80045F94[i].unk0->unk40->unk2C = D_ovl0E_12_80045F94[i].unk30;
            D_ovl0E_12_80045F94[i].unk0->unk40->unk30 = D_ovl0E_12_80045F94[i].unk34;
            /* a fake (ends the block): without it `move a1` for the next call is
             * scheduled into a load delay slot above, not the call's delay slot */
            if (!D_ovl0E_12_80045F94[i].unkE && !D_ovl0E_12_80045F94[i].unkE && !D_ovl0E_12_80045F94[i].unkE) {
            }
            func_ovl0E_12_80045648(D_ovl0E_12_80045F94[i].unk0, 0x02000000);
            func_ovl0E_12_80045650(D_ovl0E_12_80045F94[i].unk0, 0x80000);
            D_ovl0E_12_80045F94[i].unk0->unk40->unk20 = D_ovl0E_12_80045FCC[i].unk10;
        } else {
            func_ovl0E_12_8004311C(&D_ovl0E_12_80045FCC[i]);
        }
    }
}

void func_ovl0E_12_80043A14(void) {
    func_ovl0E_12_80043A0C();
    if (func_ovl0E_12_80045A20(0x400) == 0) {
        D_ovl0E_12_80046304 = func_ovl0E_12_80045690(-1, 0x80, 0.0f, 0.0f, 0.0f);
        func_ovl0E_12_80045A10(0x400);
    }
}

static void func_ovl0E_12_80043A0C(void) {
}

void func_ovl0E_12_800439D4(void) {
    func_ovl0E_12_80045798(func_ovl0E_12_800441D8, NULL, 0, 0, 0x110);
}

void func_ovl0E_12_80043984(void) {
    func_ovl0E_12_80044E00(0x12, 2, 0);
    func_ovl0E_12_8004386C(2, 0x80, 0, 0.0f, 1);
}

void func_ovl0E_12_80043934(void) {
    func_ovl0E_12_80044E00(0x27, 0, 1);
    func_ovl0E_12_8004386C(3, 0x80, 0, 0.0f, 1);
}

void func_ovl0E_12_800438E4(void) {
    func_ovl0E_12_80044E00(0x27, 4, 0x1E);
    func_ovl0E_12_8004386C(4, 0, 0x80, 0.0f, 3);
}

void func_ovl0E_12_80043894(void) {
    func_ovl0E_12_80044E00(0x26, 4, 0x1A);
    func_ovl0E_12_8004386C(5, 0xE0, 0x60, 0.0f, 0);
}

void func_ovl0E_12_8004386C(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_12_800462F0.unk0 = arg0;
    D_ovl0E_12_800462F0.unk4 = arg1;
    D_ovl0E_12_800462F0.unk8 = arg2;
    D_ovl0E_12_800462F0.unkC = arg3;
    D_ovl0E_12_800462F0.unk10 = arg4;
}

void func_ovl0E_12_80043830(void) {
    func_ovl0E_12_80043718();
    if (D_ovl0E_12_800462F0.unk0 == 5) {
        func_ovl0E_12_8004364C();
    }
}

void func_ovl0E_12_80043718(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_12_80044E58();
    switch (D_ovl0E_12_800462F0.unk8) {
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
        func_ovl0E_12_800454A8(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_12_800462F0.unkC;
        func_ovl0E_12_800454B0(&sp1C, NULL, NULL);
        func_ovl0E_12_800454A8(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_12_80044E40(D_ovl0E_12_800462F0.unk4);
}

void func_ovl0E_12_800436D0(f32 arg0) {
    f32 sp1C;

    func_ovl0E_12_800454B0(&sp1C, NULL, NULL);
    func_ovl0E_12_800454A8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_12_8004364C(void) {
    func_ovl0E_12_800454A8(180.0f, 32768.0f, 32768.0f);
    func_ovl0E_12_800454F0(15);
    func_ovl0E_12_80045500(2);
    func_ovl0E_12_80045540(70.0f, 70.1f);
    func_ovl0E_12_80044E38(1);
    func_ovl0E_12_80045798(func_ovl0E_12_80044314, NULL, 0, 0, 0x130);
}

void func_ovl0E_12_80043624(void) {
    func_ovl0E_12_800435AC();
    func_ovl0E_12_80043534();
}

void func_ovl0E_12_800435AC(void) {
    UnkStruct_ovl0E_12_80045FEC *rec;
    s16 i;

    for (i = 0, rec = D_ovl0E_12_80045FEC; i < 5; i++, rec++) {
        rec->unk0 = func_ovl0E_12_80045798(func_ovl0E_12_8004441C, rec, 0, 0, 0x110);
    }
}

void func_ovl0E_12_80043534(void) {
    UNK_MACRO_ovl0E_12_800433AC();
    func_ovl0E_12_80044E48(D_ovl0E_12_800462F0.unk4, 3, 4.0f, D_ovl0E_12_800462F0.unk10, 0, 1, 1);
}

void func_ovl0E_12_8004345C(void) {
    func_ovl0E_12_80043444();
    func_ovl0E_12_8004344C();
    func_ovl0E_12_80043454();
    if (func_ovl0E_12_80044E10(0x11, 0, 0x12, 0) != 0) {
        D_ovl0E_12_800462D4 = 0x51;
        D_ovl0E_12_800462D8 = 0x14;
        func_ovl0E_12_80044D40(0x51, 0x14, 0);
    }
    if (func_ovl0E_12_80044E10(0x26, 1, 0x27, 1) != 0) {
        D_ovl0E_12_800462D4 = 0x50;
        D_ovl0E_12_800462D8 = 0x14;
        func_ovl0E_12_80044D40(0x50, 0x14, 0);
    }
    if (func_ovl0E_12_80044E10(0x27, 0x1E, 0x28, 0x1E) != 0) {
        D_ovl0E_12_800462D4 = 0x55;
        D_ovl0E_12_800462D8 = 0x12;
        func_ovl0E_12_80044D40(0x55, 0x12, 0);
    }
}

static void func_ovl0E_12_80043454(void) {
}

static void func_ovl0E_12_8004344C(void) {
}

static void func_ovl0E_12_80043444(void) {
}

void func_ovl0E_12_800433F4(void) {
    UNK_MACRO_ovl0E_12_800433AC();
    func_ovl0E_12_80043164();
}

void func_ovl0E_12_800433AC(void) {
    func_ovl0E_12_800433A4();
    UNK_MACRO_ovl0E_12_800433AC();
}

static void func_ovl0E_12_800433A4(void) {
}

void func_ovl0E_12_80043164(void) {
    UnkStruct_ovl0E_12_80045FCC *p;
    s16 i;
    s32 flags;

    func_ovl0E_12_8004315C();
    D_ovl0E_12_80046304->unk30 = 4;
    D_ovl0E_12_80046304->unk34 = 85.0f;
    D_ovl0E_12_80046304->unk38 = 400.0f;
    for (i = 0, p = D_ovl0E_12_80045FCC; i < 1; i++, p++) {
        if (func_ovl0E_12_80045A20(p->unk0) == 0) {
            D_ovl0E_12_80046304->unk40->unk10 = p->unk4 * 10.0f;
            D_ovl0E_12_80046304->unk40->unk14 = p->unk8 * 10.0f;
            D_ovl0E_12_80046304->unk40->unk18 = p->unkC * 10.0f;
            flags = func_ovl0E_12_800455F8(D_ovl0E_12_80046304, 0xC0);
            if (flags != 0) {
                if (flags & 0x4000) {
                    func_ovl0E_12_80045D40(0x49, D_ovl0E_12_80046304->unk40->unk10, D_ovl0E_12_80046304->unk40->unk14,
                                           D_ovl0E_12_80046304->unk40->unk18);
                    func_ovl0E_12_80045650(D_ovl0E_12_80045F94[i].unk0, 0x01000000);
                    func_ovl0E_12_80045660(D_ovl0E_12_80045F94[i].unk0);
                    /* 0xFFFF, not -1: never equal to the s16 fields */
                    if (D_ovl0E_12_80045F94[i].unkC != 0xFFFF && D_ovl0E_12_80045F94[i].unkE != 0xFFFF &&
                        D_ovl0E_12_80045F94[i].unk10 != 0xFFFF && D_ovl0E_12_80045F94[i].unk12 != 0xFFFF) {
                        func_ovl0E_12_80045398(D_ovl0E_12_80045F94[i].unk4);
                    }
                    /* one line: see the header */
                    D_ovl0E_12_80045F94[i].unk0 = NULL; D_ovl0E_12_80045F94[i].unk4 = -1;
                    func_ovl0E_12_8004311C(&D_ovl0E_12_80045FCC[i]);
                    func_ovl0E_12_80045A10(p->unk0);
                } else {
                    func_ovl0E_12_80045D40(0x26, D_ovl0E_12_80046304->unk40->unk10, D_ovl0E_12_80046304->unk40->unk14,
                                           D_ovl0E_12_80046304->unk40->unk18);
                }
            }
        }
    }
}

static void func_ovl0E_12_8004315C(void) {
}

void func_ovl0E_12_8004311C(UnkStruct_ovl0E_12_80045FCC *arg0) {
    func_ovl0E_12_80044C88(arg0->unk14, arg0->unk16, arg0->unk18, arg0->unk1A, arg0->unk1C, arg0->unk1E);
}

void func_ovl0E_12_800430FC(void) {
    func_ovl0E_12_80044E90(1);
}

void func_ovl0E_12_800430DC(void) {
    func_ovl0E_12_80044E90(1);
}

void func_ovl0E_12_800430A4(void) {
    if (D_ovl0E_12_800462F0.unk0 == 5) {
        func_ovl0E_12_80043084();
    }
    func_ovl0E_12_80043018();
}

void func_ovl0E_12_80043084(void) {
    func_ovl0E_12_80045EA0();
}

void func_ovl0E_12_80043018(void) {
    UnkStruct_ovl0E_12_80045FEC *rec;
    s16 i;

    for (i = 0, rec = D_ovl0E_12_80045FEC; i < 5; i++, rec++) {
        if (rec->unk0 != -1) {
            func_ovl0E_12_800457A0(rec->unk0);
        }
    }
}

void func_ovl0E_12_80043010(void) {
}
