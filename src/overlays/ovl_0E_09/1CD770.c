#include "common.h"

/*
 * ovl_0E_09's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0E_09_80045FD0;

/* the two movers' records: each is passed to its task */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ UnkStructA *unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} UnkStruct_ovl0E_09_80045DCC;

/* a mover's path: ten points */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
} UnkStruct_ovl0E_09_80045E0C;

/* what func_ovl0E_09_80045D28 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
} UnkStruct_ovl0E_09_80045D28;

void func_ovl0E_09_80044A88(s32);
void func_ovl0E_09_80044AA0(s32);
f32 func_ovl0E_09_80044AB0(void);
void func_ovl0E_09_80044B10(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0E_09_80044B50(s32);
void func_ovl0E_09_80044B70(void (*)(UnkStructA *));
void func_ovl0E_09_80044B80(s32, s32, s32);
void func_ovl0E_09_80044BC0(void (*)(UnkStructA *));
void func_ovl0E_09_80044BF0(s32);
void func_ovl0E_09_80044C38(void);
void func_ovl0E_09_80044C40(s32, s32, s32);
void func_ovl0E_09_80044C48(void *);
s32 func_ovl0E_09_80044C50(s32, s32, s32, s32);
s32 func_ovl0E_09_80044C68(void);
void func_ovl0E_09_80044C70(s32, void *);
void func_ovl0E_09_80044C78(s32);
void func_ovl0E_09_80044C80(s32);
void func_ovl0E_09_80044C88(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0E_09_80044C90(const char *);
void func_ovl0E_09_80044C98(void);
void func_ovl0E_09_80044CD0(s32);
void func_ovl0E_09_80045170(s32);
void func_ovl0E_09_800451D0(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0E_09_800452C8(f32, f32, f32);
void func_ovl0E_09_800452E8(f32, f32, f32);
void func_ovl0E_09_800452F0(f32 *, f32 *, f32 *);
void func_ovl0E_09_80045330(s32);
void func_ovl0E_09_80045340(s32);
f32 func_ovl0E_09_80045430(f32 *, void *);
s32 func_ovl0E_09_80045438(UnkStructA *, s32);
void func_ovl0E_09_80045488(UnkStructA *, s32);
void func_ovl0E_09_80045490(UnkStructA *, s32);
void func_ovl0E_09_800454A0(UnkStructA *);
UnkStructA *func_ovl0E_09_800454D0(s32, s32, f32, f32, f32);
void func_ovl0E_09_80045508(UnkStructA *);
void func_ovl0E_09_80045598(UnkStructA *);
s32 func_ovl0E_09_800455D8(void (*)(void), void *, s32, s32, s32);
void func_ovl0E_09_800455E0(s32);
void func_ovl0E_09_800455E8(void);
void func_ovl0E_09_800455F8(s32);
void *func_ovl0E_09_80045600(void);
void func_ovl0E_09_80045620(void);
void func_ovl0E_09_80045858(s32);
void func_ovl0E_09_80045918(s32, s32, s32, s32, s32);
void func_ovl0E_09_80045928(s32, s32, s32);
void func_ovl0E_09_80045940(u32 (*)[3]);
void func_ovl0E_09_80045A28(s32, f32, f32, f32, s32);
void func_ovl0E_09_80045A30(s32, f32 *, s32);
void func_ovl0E_09_80045AE8(s32, s32, s32);
void func_ovl0E_09_80045B40(f32 *);
void func_ovl0E_09_80045B60(s32);
void func_ovl0E_09_80045B80(s32, f32, f32, f32);
void func_ovl0E_09_80045B88(s32, f32 *);
void func_ovl0E_09_80045D10(s32);
void func_ovl0E_09_80045D18(void);
s32 func_ovl0E_09_80045D20(void);
UnkStruct_ovl0E_09_80045D28 *func_ovl0E_09_80045D28(s32);
void func_ovl0E_09_80045D38(s32);
void func_ovl0E_09_80045D40(void);
void func_ovl0E_09_80045D48(void);

void func_ovl0E_09_80043010(void);
void func_ovl0E_09_80043018(void);
void func_ovl0E_09_80043094(void);
void func_ovl0E_09_80043124(void);
void func_ovl0E_09_80043160(void);
void func_ovl0E_09_80043180(void);
void func_ovl0E_09_800431A8(void);
void func_ovl0E_09_800431F0(void);
void func_ovl0E_09_80043250(void);
void func_ovl0E_09_80043368(void);
void func_ovl0E_09_800433E0(void);
void func_ovl0E_09_80043428(void);
void func_ovl0E_09_800434B8(void);
void func_ovl0E_09_800434E0(void);
void func_ovl0E_09_80043544(f32);
void func_ovl0E_09_8004358C(void);
void func_ovl0E_09_800436A4(void);
void func_ovl0E_09_800436E0(s32, s32, s32, f32, s32);
void func_ovl0E_09_80043708(void);
void func_ovl0E_09_80043758(void);
void func_ovl0E_09_800437AC(void);
void func_ovl0E_09_800437FC(void);
void func_ovl0E_09_8004384C(void);
void func_ovl0E_09_8004389C(void);
void func_ovl0E_09_800438E8(void);
void func_ovl0E_09_800438F0(void);
void func_ovl0E_09_80043930(void);
void func_ovl0E_09_80043968(void);
void func_ovl0E_09_80043A90(s32);
void func_ovl0E_09_80043C50(void);
void func_ovl0E_09_80043C98(void);
void func_ovl0E_09_80043D14(void);
void func_ovl0E_09_80043D50(void);
void func_ovl0E_09_80043E08(UnkStruct_ovl0E_09_80045DCC *, UnkStructA *);
void func_ovl0E_09_80043E54(UnkStruct_ovl0E_09_80045DCC *);
void func_ovl0E_09_80043F8C(void);
void func_ovl0E_09_800444F0(UnkStructA *);
void func_ovl0E_09_800445B4(UnkStructA *);
void func_ovl0E_09_8004464C(s32, UnkStructA *);
void func_ovl0E_09_80044680(f32, f32, f32);
void func_ovl0E_09_800446DC(void);
void func_ovl0E_09_800446F4(void);

/* empty statics: each leaves a `jr ra; nop` just before its caller */
static void func_ovl0E_09_800431A0(void);
static void func_ovl0E_09_80043238(void);
static void func_ovl0E_09_80043240(void);
static void func_ovl0E_09_80043248(void);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl0E_09_800431F0() \
    D_ovl0E_09_80045FAC = func_ovl0E_09_80044C68(); func_ovl0E_09_80044C48(&D_ovl0E_09_80045FA0); func_ovl0E_09_80044C70(D_ovl0E_09_80045FAC, D_ovl0E_09_80045F90)

/* .bss */
u8 D_ovl0E_09_80045F90[0x10];
Vec3f D_ovl0E_09_80045FA0;
s32 D_ovl0E_09_80045FAC;
u8 D_ovl0E_09_80045FB0[0x4]; /* unused (func_ovl0E_09_80044734) */
s32 D_ovl0E_09_80045FB4;
s32 D_ovl0E_09_80045FB8;
u8 D_ovl0E_09_80045FBC[0x4]; /* unused (func_ovl0E_09_80044734) */
Vec3f D_ovl0E_09_80045FC0;
u8 D_ovl0E_09_80045FCC[0x4]; /* unused (func_ovl0E_09_80044734) */
UnkStruct_ovl0E_09_80045FD0 D_ovl0E_09_80045FD0;

/* .data */
/* passed to func_ovl0E_09_80045940: three 12-byte records */
u32 D_ovl0E_09_80045D80[][3] = {
    { 0x9E0002, 0xE, 4 },
    { 0xA30002, 0xE, 4 },
    { 0xA40002, 0xE, 4 },
};
/* three 12-byte records, each passed to func_ovl0E_09_80045AE8 */
u32 D_ovl0E_09_80045DA4[][3] = {
    { 0, 0xE, 0xEC },
    { 1, 0xF, 0xED },
    { 2, 0xF, 0xED },
};
s32 D_ovl0E_09_80045DC8 = -1;
UnkStruct_ovl0E_09_80045DCC D_ovl0E_09_80045DCC[2] = {
    { 0, -1, NULL, 8, 0, 0, 3300.0f, 3200.0f, 2550.0f },
    { 1, -1, NULL, 2, 0, 0, 550.0f, 3200.0f, 900.0f },
};
UnkStruct_ovl0E_09_80045E0C D_ovl0E_09_80045E0C[10] = {
    { -10.0f, 0.0f, 270.0f, 1000.0f, 2150.0f, 2, 0 },
    { -7.071068f, -7.071068f, 225.0f, 550.0f, 1700.0f, 2, 2 },
    { 0.0f, -10.0f, 180.0f, 550.0f, 900.0f, 0, 2 },
    { 7.071068f, -7.071068f, 135.0f, 1100.0f, 350.0f, 1, 2 },
    { 10.0f, 0.0f, 90.0f, 3400.0f, 350.0f, 1, 0 },
    { 7.071068f, 7.071068f, 45.0f, 4150.0f, 1100.0f, 1, 1 },
    { 0.0f, 10.0f, 0.0f, 4150.0f, 2000.0f, 0, 1 },
    { -7.071068f, 7.071068f, 315.0f, 3600.0f, 2550.0f, 2, 1 },
    { -10.0f, 0.0f, 270.0f, 3200.0f, 2550.0f, 2, 0 },
    { -7.071068f, -7.071068f, 225.0f, 2800.0f, 2150.0f, 2, 2 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object; one of them
 * refers to the .bss nothing else uses, which would otherwise be common */
static void func_ovl0E_09_80044734(void) {
    D_ovl0E_09_80045FB0[0] = D_ovl0E_09_80045FBC[0] + D_ovl0E_09_80045FCC[0];
}

static void func_ovl0E_09_8004472C(void) {
}

static void func_ovl0E_09_80044724(void) {
}

static void func_ovl0E_09_8004471C(void) {
}

static void func_ovl0E_09_80044714(void) {
}

static void func_ovl0E_09_8004470C(void) {
}

static void func_ovl0E_09_80044704(void) {
}

static void func_ovl0E_09_800446FC(void) {
}

void func_ovl0E_09_800446F4(void) {
}

void func_ovl0E_09_800446DC(void) {
    D_ovl0E_09_80045FB4 = -1;
    D_ovl0E_09_80045FB8 = -1;
}

void func_ovl0E_09_80044680(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0E_09_800452C8(D_ovl0E_09_80045FC0.x, D_ovl0E_09_80045FC0.y, D_ovl0E_09_80045FC0.z);
    func_ovl0E_09_800452E8(arg0, arg1, arg2);
    func_ovl0E_09_800455F8(180);
}

void func_ovl0E_09_8004464C(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0E_09_80045B80(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0E_09_800445B4(UnkStructA *arg0) {
    f32 pos[3];

    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14 + 100.0f;
    pos[2] = arg0->unk40->unk18;
    func_ovl0E_09_80045490(arg0, 0x01000000);
    func_ovl0E_09_80045A30(7, pos, 0);
    pos[1] += 100.0f;
    func_ovl0E_09_80045A30(13, pos, 0);
    func_ovl0E_09_80045B88(180, pos);
}

void func_ovl0E_09_800444F0(UnkStructA *arg0) {
    func_ovl0E_09_80045490(arg0, 0x04000000);
    func_ovl0E_09_800455F8(10);
    func_ovl0E_09_80044B10(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    func_ovl0E_09_80045B60(30);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0E_09_800455F8(60);
}

void func_ovl0E_09_80043F8C(void) {
    s16 moving;
    s32 pad; /* unused: the original's frame has one more slot */
    UnkStruct_ovl0E_09_80045DCC *rec;
    UnkStructA *obj;
    s16 doneX;
    s16 doneZ;
    s32 flags;
    f32 pos[3];

    moving = 0;
    rec = func_ovl0E_09_80045600();
    rec->unk8 = func_ovl0E_09_800454D0(0x1BB, 0x30, rec->unk14, rec->unk18, rec->unk1C);
    obj = rec->unk8;
    func_ovl0E_09_80045488(obj, 0x0F000020);
    obj->unk30 = 1;
    obj->unk34 = 70.0f;
    obj->unk68 = 0.0f;
    obj->unk38 = 50.0f;
    obj->unk70 = 1.6333334f;
    rec->unk10 = 0;
    /* the set-up in the loop's header: on lines of their own, IDO schedules
     * the table's address after it */
    for (doneZ = 0, doneX = 0, rec->unkE = rec->unkC;;) {
        if (D_ovl0E_09_80045E0C[rec->unkE].unk14 == 0) {
            doneX = 1;
        }
        if (D_ovl0E_09_80045E0C[rec->unkE].unk14 == 1 && D_ovl0E_09_80045E0C[rec->unkE].unkC <= obj->unk40->unk10) {
            obj->unk40->unk10 = D_ovl0E_09_80045E0C[rec->unkE].unkC;
            doneX = 1;
        }
        if (D_ovl0E_09_80045E0C[rec->unkE].unk14 == 2 && obj->unk40->unk10 <= D_ovl0E_09_80045E0C[rec->unkE].unkC) {
            obj->unk40->unk10 = D_ovl0E_09_80045E0C[rec->unkE].unkC;
            doneX = 1;
        }
        if (D_ovl0E_09_80045E0C[rec->unkE].unk16 == 0) {
            doneZ = 1;
        }
        if (D_ovl0E_09_80045E0C[rec->unkE].unk16 == 1 && D_ovl0E_09_80045E0C[rec->unkE].unk10 <= obj->unk40->unk18) {
            obj->unk40->unk18 = D_ovl0E_09_80045E0C[rec->unkE].unk10;
            doneZ = 1;
        }
        if (D_ovl0E_09_80045E0C[rec->unkE].unk16 == 2 && obj->unk40->unk18 <= D_ovl0E_09_80045E0C[rec->unkE].unk10) {
            obj->unk40->unk18 = D_ovl0E_09_80045E0C[rec->unkE].unk10;
            doneZ = 1;
        }
        if (doneX == 1 && doneZ != 0) {
            rec->unkE++;
            if (rec->unkE >= 10) {
                rec->unkE = 0;
            }
        }
        obj->unk40->unk20 = D_ovl0E_09_80045E0C[rec->unkE].unk8;
        if (moving == 1) {
            obj->unk40->unk10 += D_ovl0E_09_80045E0C[rec->unkE].unk0;
            obj->unk40->unk18 += D_ovl0E_09_80045E0C[rec->unkE].unk4;
        }
        func_ovl0E_09_80045508(obj);
        if (obj->unk6C == 0.0f && obj->unk68 == 0.0f) {
            moving = 1;
        }
        if (rec->unk10 > 0) {
            rec->unk10--;
        }
        if (rec->unk10 <= 0) {
            pos[0] = obj->unk40->unk10;
            pos[1] = obj->unk40->unk14;
            pos[2] = obj->unk40->unk18;
            if (func_ovl0E_09_80045430(pos, D_ovl0E_09_80045F90) < 1200.0f) {
                func_ovl0E_09_80045B88(0x77, pos);
                rec->unk10 = 30;
            }
        }
        func_ovl0E_09_80045598(obj);
        flags = func_ovl0E_09_80045438(obj, 0xC0);
        if (flags != 0) {
            if (flags & 0x6000) {
                func_ovl0E_09_80045A28(0x14, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
                func_ovl0E_09_80045A28(0x12, obj->unk40->unk10, obj->unk40->unk14 + 100.0f, obj->unk40->unk18, 0);
                func_ovl0E_09_80045B80(0x168, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
                pos[0] = obj->unk40->unk10;
                pos[1] = obj->unk40->unk14;
                pos[2] = obj->unk40->unk18;
                func_ovl0E_09_80045B40(pos);
                func_ovl0E_09_80043E08(rec, obj);
            } else {
                func_ovl0E_09_80045B80(0x26, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
            }
        }
        if (obj->unk40->unk14 <= func_ovl0E_09_80044AB0()) {
            func_ovl0E_09_80043E54(rec);
        }
        doneZ = 0;
        doneX = 0;
        func_ovl0E_09_80045620();
    }
}

void func_ovl0E_09_80043E54(UnkStruct_ovl0E_09_80045DCC *arg0) {
    UnkStructA *obj;
    f32 floor;

    floor = func_ovl0E_09_80044AB0();
    obj = arg0->unk8;
    while (TRUE) {
        obj->unk40->unk14 -= 4.0f;
        if (obj->unk40->unk14 <= floor - 200.0f || floor == -25500.0f) {
            func_ovl0E_09_80043E08(arg0, obj);
        }
        func_ovl0E_09_80045620();
    }
}

void func_ovl0E_09_80043E08(UnkStruct_ovl0E_09_80045DCC *arg0, UnkStructA *arg1) {
    func_ovl0E_09_80045490(arg1, 0x01000000);
    func_ovl0E_09_800454A0(arg1);
    arg0->unk4 = -1;
    arg0->unk8 = NULL;
    func_ovl0E_09_800455E8();
}

void func_ovl0E_09_80043968(void) {
    UnkStructA *obj;
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl0E_09_800438F0();
    func_ovl0E_09_80044B70(func_ovl0E_09_800445B4);
    func_ovl0E_09_80044BC0(func_ovl0E_09_800444F0);
    func_ovl0E_09_80045940(D_ovl0E_09_80045D80);
    func_ovl0E_09_80044A88(0x199);
    obj = func_ovl0E_09_800454D0(0x19A, 0x50, 0.0f, 0.0f, 0.0f);
    func_ovl0E_09_80045488(obj, 0x01000000);
    p = D_ovl0E_09_80045DA4;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl0E_09_80045AE8((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl0E_09_80044AA0(0x1A5);
    func_ovl0E_09_80044C38();
    func_ovl0E_09_800433E0();
    func_ovl0E_09_80044B50(0x201F);
    func_ovl0E_09_800451D0(obj->unk40, 0, 2, 0x400, 0, 0);
    func_ovl0E_09_80045918(0x3AF, 0x3DE, 0xFF, 0x87, 0x1F);
    func_ovl0E_09_80045928(0xFF, 0xA1, 0x1D);
}

void func_ovl0E_09_80043D50(void) {
    UnkStruct_ovl0E_09_80045DCC *rec;
    s16 i;

    while (TRUE) {
        rec = D_ovl0E_09_80045DCC;
        for (i = 0; i < 2; i++, rec++) {
            if (rec->unk8 == NULL) {
                break;
            }
        }
        if (i < 2) {
            rec->unk4 = func_ovl0E_09_800455D8(func_ovl0E_09_80043F8C, rec, 0, 0, 0x110);
            func_ovl0E_09_800455F8(300);
        }
        func_ovl0E_09_80045620();
    }
}

void func_ovl0E_09_80043D14(void) {
    D_ovl0E_09_80045DC8 = func_ovl0E_09_800455D8(func_ovl0E_09_80043D50, NULL, 0, 0, 0x110);
}

void func_ovl0E_09_80043C98(void) {
    func_ovl0E_09_80044C78(1);
    func_ovl0E_09_80044BF0(0);
    func_ovl0E_09_80044C90("WM1 WG1 WAP WSH WDW WB11 ST1");
    func_ovl0E_09_80045D38(60);
    func_ovl0E_09_80045D10(1);
    while (func_ovl0E_09_80045D20() != 0) {
        func_ovl0E_09_80045620();
    }
    func_ovl0E_09_80045D40();
    func_ovl0E_09_800455E8();
}

void func_ovl0E_09_80043C50(void) {
    func_ovl0E_09_80044C40(0x1F, 4, 0x19);
    func_ovl0E_09_800436E0(1, 0, 0, 0.0f, 0);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0E_09_80043A90(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0E_09_80043968();
            break;
        case 16:
            func_ovl0E_09_8004389C();
            break;
        case 17:
            func_ovl0E_09_80043708();
            break;
        case 18:
            func_ovl0E_09_8004384C();
            break;
        case 19:
            func_ovl0E_09_800437FC();
            break;
        case 20:
            func_ovl0E_09_800437AC();
            break;
        case 21:
            func_ovl0E_09_80043758();
            break;
        case 22:
            func_ovl0E_09_80043708();
            break;
        case 4:
            func_ovl0E_09_800436A4();
            break;
        case 5:
            func_ovl0E_09_800434B8();
            break;
        case 0x50:
            func_ovl0E_09_80043250();
            break;
        case 3:
            func_ovl0E_09_800431F0();
            break;
        case 12:
            func_ovl0E_09_80043180();
            break;
        case 1:
            func_ovl0E_09_80043124();
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

void func_ovl0E_09_80043930(void) {
    func_ovl0E_09_800438F0();
    func_ovl0E_09_80044B70(func_ovl0E_09_800445B4);
    func_ovl0E_09_80044BC0(func_ovl0E_09_800444F0);
}

void func_ovl0E_09_800438F0(void) {
    func_ovl0E_09_80045858(0x400);
    func_ovl0E_09_80045858(0x401);
    func_ovl0E_09_80045858(0x402);
    func_ovl0E_09_80045858(0x403);
    func_ovl0E_09_80045858(0x404);
}

void func_ovl0E_09_800438E8(void) {
}

void func_ovl0E_09_8004389C(void) {
    func_ovl0E_09_80044C40(0x11, 5, 0x1E);
    func_ovl0E_09_800436E0(0, 0, 0x80, 0.0f, 2);
}

void func_ovl0E_09_8004384C(void) {
    func_ovl0E_09_80044C40(3, 3, 2);
    func_ovl0E_09_800436E0(2, 0x80, 1, 0.0f, 1);
}

void func_ovl0E_09_800437FC(void) {
    func_ovl0E_09_80044C40(0x12, 4, 1);
    func_ovl0E_09_800436E0(3, 0x80, 0, 0.0f, 1);
}

void func_ovl0E_09_800437AC(void) {
    func_ovl0E_09_80044C40(1, 1, 0xC);
    func_ovl0E_09_800436E0(4, 0x40, 0, 0.0f, 1);
}

void func_ovl0E_09_80043758(void) {
    func_ovl0E_09_80044C40(0x2E, 0, 0xC);
    func_ovl0E_09_800436E0(5, 0xC0, 0x40, 0.0f, 1);
}

void func_ovl0E_09_80043708(void) {
    func_ovl0E_09_80044C40(0x1B, 4, 0x16);
    func_ovl0E_09_800436E0(6, 0xC0, 0x60, 0.0f, 0);
}

void func_ovl0E_09_800436E0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl0E_09_80045FD0.unk0 = arg0;
    D_ovl0E_09_80045FD0.unk4 = arg1;
    D_ovl0E_09_80045FD0.unk8 = arg2;
    D_ovl0E_09_80045FD0.unkC = arg3;
    D_ovl0E_09_80045FD0.unk10 = arg4;
}

void func_ovl0E_09_800436A4(void) {
    func_ovl0E_09_8004358C();
    if (D_ovl0E_09_80045FD0.unk0 == 6) {
        func_ovl0E_09_800434E0();
    }
}

void func_ovl0E_09_8004358C(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0E_09_80044C98();
    switch (D_ovl0E_09_80045FD0.unk8) {
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
        func_ovl0E_09_800452E8(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0E_09_80045FD0.unkC;
        func_ovl0E_09_800452F0(&sp1C, NULL, NULL);
        func_ovl0E_09_800452E8(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0E_09_80044C80(D_ovl0E_09_80045FD0.unk4);
}

void func_ovl0E_09_80043544(f32 arg0) {
    f32 sp1C;

    func_ovl0E_09_800452F0(&sp1C, NULL, NULL);
    func_ovl0E_09_800452E8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0E_09_800434E0(void) {
    func_ovl0E_09_800452E8(225.0f, 32768.0f, 32768.0f);
    func_ovl0E_09_800455D8(func_ovl0E_09_80043C98, NULL, 0, 0, 0x130);
    func_ovl0E_09_80045330(15);
    func_ovl0E_09_80045340(1);
}

void func_ovl0E_09_800434B8(void) {
    func_ovl0E_09_80043428();
    func_ovl0E_09_80043368();
}

void func_ovl0E_09_80043428(void) {
    UnkStruct_ovl0E_09_80045DCC *rec;
    s16 i;

    func_ovl0E_09_800433E0();
    D_ovl0E_09_80045DC8 = -1;
    for (i = 0, rec = D_ovl0E_09_80045DCC; i < 2; i++, rec++) {
        if (rec->unk8 == NULL) {
            rec->unk4 = func_ovl0E_09_800455D8(func_ovl0E_09_80043F8C, rec, 0, 0, 0x110);
        }
    }
}

void func_ovl0E_09_800433E0(void) {
    s16 i;

    D_ovl0E_09_80045DC8 = -1;
    for (i = 0; i < 2; i++) {
        D_ovl0E_09_80045DCC[i].unk0 = i;
        D_ovl0E_09_80045DCC[i].unk4 = -1;
        D_ovl0E_09_80045DCC[i].unk8 = NULL;
    }
}

void func_ovl0E_09_80043368(void) {
    UNK_MACRO_ovl0E_09_800431F0();
    func_ovl0E_09_80044C88(D_ovl0E_09_80045FD0.unk4, 3, 4.0f, D_ovl0E_09_80045FD0.unk10, 0, 1, 1);
}

void func_ovl0E_09_80043250(void) {
    func_ovl0E_09_80043238();
    func_ovl0E_09_80043240();
    func_ovl0E_09_80043248();
    if (func_ovl0E_09_80044C50(2, 2, 3, 2) != 0) {
        D_ovl0E_09_80045FB4 = 0x51;
        D_ovl0E_09_80045FB8 = 0x15;
        func_ovl0E_09_80044B80(0x51, 0x15, 0);
    }
    if (func_ovl0E_09_80044C50(0x11, 1, 0x12, 1) != 0) {
        D_ovl0E_09_80045FB4 = 0x51;
        D_ovl0E_09_80045FB8 = 0x16;
        func_ovl0E_09_80044B80(0x51, 0x16, 0);
    }
    if (func_ovl0E_09_80044C50(1, 0xB, 1, 0xC) != 0) {
        D_ovl0E_09_80045FB4 = 0x53;
        D_ovl0E_09_80045FB8 = 0x13;
        func_ovl0E_09_80044B80(0x53, 0x13, 0);
    }
    if (func_ovl0E_09_80044C50(0x2E, 0xB, 0x2E, 0xC) != 0) {
        D_ovl0E_09_80045FB4 = 0x54;
        D_ovl0E_09_80045FB8 = 0x12;
        func_ovl0E_09_80044B80(0x54, 0x12, 0);
    }
}

static void func_ovl0E_09_80043248(void) {
}

static void func_ovl0E_09_80043240(void) {
}

static void func_ovl0E_09_80043238(void) {
}

void func_ovl0E_09_800431F0(void) {
    UNK_MACRO_ovl0E_09_800431F0();
}

void func_ovl0E_09_800431A8(void) {
    func_ovl0E_09_800431A0();
    UNK_MACRO_ovl0E_09_800431F0();
}

static void func_ovl0E_09_800431A0(void) {
}

void func_ovl0E_09_80043180(void) {
    func_ovl0E_09_80044CD0(1);
}

void func_ovl0E_09_80043160(void) {
    func_ovl0E_09_80044CD0(1);
}

void func_ovl0E_09_80043124(void) {
    func_ovl0E_09_80043094();
    if (D_ovl0E_09_80045FD0.unk0 == 6) {
        func_ovl0E_09_80043018();
    }
}

void func_ovl0E_09_80043094(void) {
    s16 i;

    /* one line, as in func_ovl0E_09_80043F8C's loop */
    i = 0; do {
        if (D_ovl0E_09_80045DCC[i].unk4 != -1) {
            func_ovl0E_09_800455E0(D_ovl0E_09_80045DCC[i].unk4);
        }
        i++;
    } while (i < 2);
    if (D_ovl0E_09_80045DC8 != -1) {
        func_ovl0E_09_800455E0(D_ovl0E_09_80045DC8);
    }
}

void func_ovl0E_09_80043018(void) {
    UnkStruct_ovl0E_09_80045D28 *p;

    ((UnkStructA_40 *) func_ovl0E_09_80045D28(1)->unkC)->unkC |= 1;
    func_ovl0E_09_80045928(0, 0, 0);
    func_ovl0E_09_80045D18();
    p = func_ovl0E_09_80045D28(4);
    if (p->unkC != 0) {
        func_ovl0E_09_80045170(p->unkC);
    }
    p->unkC = 0;
    func_ovl0E_09_80045D48();
}

void func_ovl0E_09_80043010(void) {
}
