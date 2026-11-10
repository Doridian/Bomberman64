/*
 * main_code's A1EA0, IDO -O3; it matches in us, eu and jp: the two
 * D_802B0260 entries and the task that updates them. Its .data
 * (D_802A1B50, the D_802A1B54 table) and .bss (D_802B0260, D_802B0300,
 * D_802B0308) are its own, placed in data_split.txt.
 */
#include "common.h"

/* The object the tables' functions are handed (A2840's name); it is
 * D_800BA900[i].unk14. */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 unk3D;
    /* 0x3E */ u16 unk3E;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ union {
        f32 f;
        u8 b[4];
    } unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ union {
        f32 f;
        u8 b[4];
    } unk58;
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 unk5D;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 unk6D;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ u8 unk78;
    /* 0x79 */ s8 unk79;
    /* 0x7A */ u8 unk7A;
    /* 0x7C */ u16 unk7C;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s16 unk88;
    /* 0x8C */ s32 unk8C;
} UnkStruct_80288040; /* size 0x90 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ Vec3f unk8;
    /* 0x14 */ UnkStruct_80288040 unk14;
} UnkStruct_800BA900; /* size 0xA4 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ UnkStruct_800BA900 *unk10;
} UnkStruct_800BB340; /* size 0x14 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
} UnkStruct_800BA8E8;

extern UnkStruct_800BA8E8 D_800BA8E8[6];
extern UnkStruct_800BA900 D_800BA900[16];
extern UnkStruct_800BB340 D_800BB340[16];
extern s32 D_800BB480;
extern UnkStruct_80288040 *D_800BB484;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_8023A840;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
} UnkStruct_802B0260; /* size 0x50 */

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
} UnkStruct_802B0300;

typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 unk30[6];
    /* 0x36 */ s16 unk36;
} UnkStruct_802B0308;

void func_80225CCC(void *, s32, s32);
void func_802276FC(s32);
f32 func_80229D3C(void *, s32);
void func_80229E38(void *, s32, s32);
s32 func_8022F4AC(UnkStructA *, s32, UnkStructA *);
UnkStructA *func_8022F550(UnkStructA *, s32);
void func_8022FC90(void *);
void func_80230914(void *);
UnkStructA *func_80230CB4(s32, s32, s32, s32, void *);
s32 func_802311E8(void *);
void func_802313DC(void *, s32);
void func_80231408(void *, s32);
s32 func_80232D18(void *, s32);
void func_80232DB4(void *);
int func_802336E4(f32);
s32 func_80234248(s32);
f32 func_80234434(f32);
s32 func_80234768(void);
void func_80234858(f32 *, f32 *, f32 *);
void func_802348B4(f32 *, f32 *, f32 *);
s32 func_80238A10(void *, void *, s32, s32, s32);
void func_80238EA8(s32);
void func_80239094(void);
UnkStruct_800BB340 *func_802391F0(void);
void func_80239430(void);
UnkStruct_8023A840 *func_8023A840(void);
s32 func_80243DDC(void);
UnkStructA *func_802443F4(s32);
void func_80250338(s32, Vec3f *);
f64 func_8025E63C(void);
f32 func_80263DC8(f32, f32);
s32 func_8026C51C(s32, f32, f32, f32);
s32 func_8026D7D8(s32, s32, s32);
void func_8026DCAC(f32, f32, f32, void *, s32);
s32 func_8026EE18(f32);
s32 func_802700EC(UnkStructA *, UnkStructA *, s32, f32);
void func_80270BA4(void *);
void func_80270C24(UnkStructA *, s32, s32);
void func_802727D8(s32);
void func_802733C8(void *);
void func_8027B7C4(s32, f32, f32, f32);
void func_8027F820(void);
void func_8027F858(UnkStructA *, s32);
void func_8028805C(void *);
void func_802881A0(void *);
void func_802883B0(void);
s32 func_8028A4E0(s32);
s32 func_8028A81C(s32, f32, f32, f32, UnkStructA *);
s32 func_802909FC(UnkStructA *, void *);
void func_80291944(void *, s32, f32);
f32 sinf(f32);

extern u8 D_800BA90C[];
extern u8 D_800BB488[20];
extern s32 D_800BC520;
extern u8 D_802A1AB4[];
extern s32 D_802A1AF0[][4];
extern UnkStruct_802B0260 D_802B0260[2];
extern UnkStruct_802B0300 *D_802B0300[2];
extern UnkStruct_802B0308 *D_802B0308[2];

void func_802822B0(s32 arg0);
void func_802822BC(UnkStruct_800BB340 *arg0);
void func_802822D8();
void func_802822E0(UnkStruct_800BB340 *arg0);
void func_80282340(UnkStruct_800BA900 *arg0);
void func_80282428();
void func_80282430(UnkStruct_80288040 *arg0, s32 arg1, s32 arg2);
void func_80282454(UnkStruct_80288040 *arg0);
s32 func_802824B4(UnkStruct_80288040 *arg0);
s32 func_80282524(UnkStruct_80288040 *arg1);
void func_80282588();
void func_80282598(UnkStruct_800BB340 *arg0, s32 arg1);
void func_80282714(UnkStruct_80288040 *arg0);
void func_8028275C(f32 arg0, f32 arg1, f32 arg2);
void func_80282934(void);
void func_80282978(Vec3f *arg0);
s32 func_802829AC(s32 arg0, Vec3f *arg1);
void func_80282AD0();
s32 func_80282AF0(UnkStruct_800BB340 *arg0, s32 arg1);
void func_80282F44(UnkStruct_800BB340 *arg0, s32 arg1);
void func_8028301C(UnkStruct_80288040 *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_8028304C(UnkStruct_80288040 *arg0, s32 arg1);
void func_802831A8(UnkStruct_80288040 *arg0);
f32 func_8028322C(UnkStruct_80288040 *arg0);
u8 func_80283314(s32 arg0, s32 arg1, UnkStruct_80288040 *arg2);
void func_802836F0(UnkStruct_80288040 *arg0, s32 arg1);
s32 func_80283794(UnkStruct_80288040 *arg0, u8 arg1);
void func_80283B04(UnkStruct_80288040 *arg0, Vec3f *arg1);
void func_80283CF0(UnkStruct_80288040 *arg0);
s32 func_80283D9C(UnkStruct_80288040 *arg0);
void func_80283DF0(s32 arg0, UnkStruct_80288040 *arg1);
void func_80283F38(UnkStruct_80288040 *arg0);
void func_80283FCC(UnkStruct_80288040 *arg0);
void func_8028425C(UnkStruct_80288040 *arg0);
s32 func_8028456C(UnkStruct_80288040 *arg0);
void func_802847E4(UnkStruct_80288040 *arg0, s32 arg1);
void func_802848E8(UnkStruct_80288040 *arg0);
void func_80284B30(UnkStruct_80288040 *arg0);
s32 func_80284CAC(UnkStruct_80288040 *arg0);
s32 func_80284FD4(UnkStruct_80288040 *arg0);
s32 func_8028556C(s32 arg0);
s32 func_80285658(UnkStruct_800BA900 *arg0, UnkStruct_800BB340 *arg1);
void func_80285A9C(UnkStruct_800BB340 *arg0);
void func_80285F8C(void);
void func_802863B0(Vec3f *arg0);
void func_802863E0();
void func_80286400(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
UnkStruct_80288040 *func_802867E4(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 func_80286CA8(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80286E60(void);
void func_80286EF0(void);
void func_80286EFC();
void func_80286F04(void);
void func_80286F70(void);
void func_80286F98(void);
void func_80287008(s32 arg0, s16 arg1, s16 arg2);
UnkStruct_80288040 *func_80287024(UnkStructA *arg0);
s32 func_802870A8(UnkStructA *arg0, s32 arg1);
s32 func_80287150(void);
UnkStruct_800BB340 *func_802871C8(UnkStruct_80288040 *arg0);
s32 func_802871D0(UnkStruct_80288040 *arg0);
s32 func_802872E0(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80287440(UnkStructA *arg0);
s32 func_802875B0(UnkStructA *arg0);
s32 func_80287680(void);
void func_802876A0(void);
void func_802876C8(UnkStruct_802B0260 *arg0);
void func_8028773C(UnkStruct_802B0260 *arg0);
void func_8028785C(void);
void func_802878BC(UnkStruct_802B0260 *arg0, s32 arg1);
void func_802878E0(UnkStruct_802B0260 *arg0, s32 arg1);
static void func_80287904(void);
UnkStruct_802B0260 *func_80287DC0(s32 arg0);
void func_80287FD4(void);
void func_80282338();
void func_80282590();
void func_802829A4();
void func_80282AD8();
void func_80282AE0();
void func_80282AE8();
void func_80283014();
void func_80283304();
void func_8028330C();
void func_80283784();
void func_8028378C();
void func_80283AFC();
void func_80283DE8();
s32 func_80283F28(UnkStruct_80288040 *arg0);
void func_80283F30(UnkStruct_80288040 *arg0);
void func_80283FAC();
void func_80283FB4();
void func_80283FBC();
void func_80283FC4();
void func_8028422C();
void func_80284234();
void func_8028423C();
void func_80284244();
void func_8028424C();
void func_80284254();
void func_802847DC();
void func_802848D8();
void func_802848E0();
void func_80284B20();
void func_80284B28();
void func_80284C9C();
void func_80284CA4();
s32 func_80284FCC(UnkStruct_80288040 *arg0);
void func_80285554();
void func_8028555C();
void func_80285564();
void func_80285650();
s32 func_80285A6C(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
UnkStruct_800BA900 *func_80285A74(Vec3f *arg0);
void func_80285A7C();
void func_80285A84();
void func_80285A8C();
void func_80285A94();
s32 func_80285F84(UnkStruct_80288040 *arg0);
void func_802863E8();
void func_802863F0();
void func_802863F8();
void func_802867CC();
void func_802867D4();
void func_802867DC(UnkStruct_800BA900 *arg0);
UnkStruct_800BB340 *func_802872D8(UnkStruct_800BA900 *arg0);
void func_80287690();
void func_80287698();

#define LOAD_80285A7C(a_, i_) \
    { \
        void *f; \
        f = func_80226604(0xDD, 1); \
        func_80225CCC((void *) f, D_800BA8E8[(i_)].unk0 * 20, 0); \
        func_8022616C(D_800BB488, 1, 20, f); \
        func_80226368(f); \
        (a_)->unk1F = D_800BB488[0]; \
        (a_)->unk3E = D_800BB488[1]; \
        (a_)->unk3C = D_800BB488[2]; \
        (a_)->unk3D = D_800BB488[3]; \
        (a_)->unk50.b[0] = D_800BB488[4]; \
        (a_)->unk1E = D_800BB488[5]; \
        (a_)->unk24 = (D_800BB488[6] << 24) + (D_800BB488[7] << 16) + (D_800BB488[8] << 8) + D_800BB488[9]; \
        (a_)->unk2C = 2.0f * (s16) ((D_800BB488[10] << 8) + D_800BB488[11]) * 0.01f; \
        (a_)->unk1D = D_800BB488[12]; \
        (a_)->unk44 = D_800BB488[13]; \
        (a_)->unk6C = D_800BB488[14]; \
        (a_)->unk6D = D_800BB488[15]; \
        (a_)->unk70 = (u32) D_800BB488[16]; \
        (a_)->unk74 = (u32) D_800BB488[17]; \
        (a_)->unk7C = D_800BB488[18]; \
        (a_)->unk7E = D_800BB488[19]; \
    }

#define HARD_80285A84(a_) \
    if (func_8023A840()->unk10 == 0) { \
        (a_)->unk2C *= 0.5f; \
        if ((a_)->unk6D >= 2) { \
            (a_)->unk6D--; \
        } \
        (a_)->unk3E *= 2; \
    }

#define FREESLOT_802867CC(r_) \
    { \
        UnkStruct_800BA900 *s_; \
        s32 i_; \
        (r_) = -1; \
        s_ = D_800BA900; \
        for (i_ = 0; i_ < 16; i_++, s_++) { \
            if (s_->unk0 == 0) { \
                (r_) = i_; \
                break; \
            } \
        } \
    }

#define FREETASK_802867D4(r_) \
    { \
        UnkStruct_800BB340 *t_; \
        s32 i_; \
        s32 n_; \
        n_ = 0; \
        (r_) = -1; \
        t_ = D_800BB340; \
        for (i_ = 1; i_ < 16; i_++, t_++) { \
            if (t_->unk4 != 0) { \
                n_++; \
            } \
        } \
        if (n_ < D_800BB480) { \
            t_ = D_800BB340; \
            for (i_ = 0; i_ < 16; i_++, t_++) { \
                if (t_->unk4 == 0) { \
                    (r_) = i_; \
                    break; \
                } \
            } \
        } \
    }

#define DEC_80284CA4(a_) ((--(a_)->unk6D == 0) ? 1 : 0)

s32 D_802A1B50 = -1;
void *D_802A1B54[] = { func_80287DC0, func_8028773C, func_802878E0, func_802878BC };
UnkStruct_802B0260 D_802B0260[2];
UnkStruct_802B0300 *D_802B0300[2];
UnkStruct_802B0308 *D_802B0308[2];

void func_80287FD4(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_802B0260[i].unk0 = i;
        func_802876C8(&D_802B0260[i]);
    }
    func_802876A0();
    D_802A1B50 = -1;
}

UnkStruct_802B0260 *func_80287DC0(s32 arg0) {
    UnkStruct_802B0260 *e;
    s32 i;

    e = D_802B0260;
    for (i = 0; i < 2; i++, e++) {
        if (e->unk4 == 0) {
            e->unk0 = i;
            e->unk8 = arg0;
            e->unk4 |= 0x80000000;
            e->unkC = 0x400;
            e->unk10 = 0x40;
            D_802B0300[e->unk0] = func_8026CE28(arg0);
            D_802B0308[e->unk0] = func_8022A6C4(D_802B0300[e->unk0], e->unk10);
            e->unkC |= D_802B0308[e->unk0]->unkC;
            e->unk48 = D_802B0300[e->unk0]->unk10;
            e->unk4C = D_802B0300[e->unk0]->unk12;
            D_802B0308[e->unk0]->unk10 = e->unk28;
            D_802B0308[e->unk0]->unk14 = e->unk2C;
            D_802B0308[e->unk0]->unk18 = e->unk30;
            D_802B0308[e->unk0]->unk1C = e->unk34;
            D_802B0308[e->unk0]->unk20 = 0.0f;
            D_802B0308[e->unk0]->unk24 = 0.0f;
            if (D_802A1B50 == -1) {
                D_802A1B50 = func_80238A10(func_80287904, 0, 0, 0, 0x403);
                func_802276FC(0);
            }
            return e;
        }
    }
    return NULL;
}

static void func_80287904(void) {
    s32 j;
    f32 u[2];
    f32 v[2];
    f32 w;
    s32 pad[3];
    f32 rot[3];
    f32 cam[3];
    f32 h;
    f32 du;
    f32 dv;
    UnkStruct_802B0260 *e;
    s32 i;

    func_802348B4(&cam[0], &cam[1], &cam[2]);
    for (j = 0; j < 2; j++) {
        u[j] = 0.0f;
        v[j] = 0.0f;
    }
    for (;;) {
        e = D_802B0260;
        for (i = 0; i < 2; i++, e++) {
            if (!(e->unk4 & 0x80000000)) {
                continue;
            }
            if (e->unk4 & 0x20000000) {
                e->unkC &= ~1;
            } else {
                e->unkC |= 1;
            }
            D_802B0308[i]->unkC = e->unkC;
            D_802B0308[i]->unk8 = e->unk10;
            D_802B0308[i]->unk36 = e->unk14;
            D_802B0308[i]->unk10 = e->unk28;
            D_802B0308[i]->unk14 = e->unk2C;
            D_802B0308[i]->unk18 = e->unk30;
            D_802B0308[i]->unk1C = e->unk34;
            if (!(e->unk4 & 0x20000000)) {
                continue;
            }
            D_802B0308[i]->unk28 = e->unk48 * e->unk40;
            D_802B0308[i]->unk2C = e->unk4C * e->unk44;
            w = e->unk48;
            h = e->unk4C;
            switch (e->unk4 & 0xF) {
            case 0:
                func_80234858(&rot[0], &rot[1], &rot[2]);
                if (func_802336E4(rot[0]) != 0) {
                    du = 0.0f;
                } else if (func_80234768() == 1) {
                    du = w - (w / (360.0f / rot[0]));
                } else {
                    du = w / (360.0f / rot[0]);
                }
                dv = func_80234434((rot[1] >= 360.0f) ? rot[1] - 360.0f : ((rot[1] < 0.0f) ? rot[1] + 360.0f : rot[1])) * (h * e->unk44 * 0.5f);
                break;
            case 1:
                e->unk20 += e->unk18;
                e->unk24 += e->unk1C;
                if (e->unk20 < 0.0f) {
                    e->unk20 += e->unk48;
                }
                if (e->unk48 < e->unk20) {
                    e->unk20 -= e->unk48;
                }
                if (e->unk24 < 0.0f) {
                    e->unk24 += e->unk4C;
                }
                if (e->unk4C < e->unk24) {
                    e->unk24 -= e->unk4C;
                }
                du = e->unk20;
                dv = e->unk24;
                break;
            default:
                for (;;) {
                }
            }
            u[i] = e->unk38 + du;
            u[i] = func_80263DC8(u[i], w);
            v[i] = e->unk3C + dv;
            v[i] = func_80263DC8(v[i], h);
            D_802B0308[e->unk0]->unk20 = u[i];
            D_802B0308[e->unk0]->unk24 = v[i];
        }
        func_80239094();
    }
}

void func_802878E0(UnkStruct_802B0260 *arg0, s32 arg1) {
    if (!(arg0->unk4 & 0x80000000)) {
        for (;;) {
        }
    }
    arg0->unk4 |= arg1;
}

void func_802878BC(UnkStruct_802B0260 *arg0, s32 arg1) {
    if (!(arg0->unk4 & 0x80000000)) {
        for (;;) {
        }
    }
    arg0->unk4 &= ~arg1;
}

void func_8028785C(void) {
    UnkStruct_802B0260 *e;
    s32 i;

    e = D_802B0260;
    for (i = 0; i < 2; i++, e++) {
        if (e->unk4 != 0) {
            func_8028773C(e);
        }
    }
}

void func_8028773C(UnkStruct_802B0260 *arg0) {
    UnkStruct_802B0260 *e;
    s32 last;
    s32 i;
    s32 n;

    if (!(arg0->unk4 & 0x80000000)) {
        for (;;) {
        }
    }
    func_8022A1E8(D_802B0308[arg0->unk0]);
    last = 1;
    e = D_802B0260;
    for (i = 0; i < 2; i++, e++) {
        if ((arg0->unk0 != e->unk0) && (arg0->unk8 == e->unk8)) {
            last = 0;
        }
    }
    if (last != 0) {
        func_8026CCBC(arg0->unk8);
    }
    func_802876C8(arg0);
    n = 0;
    arg0 = D_802B0260;
    for (i = 0; i < 2; i++, arg0++) {
        if (arg0->unk4 != 0) {
            n++;
        }
    }
    if (n == 0) {
        if (D_802A1B50 != -1) {
            func_80238EA8(D_802A1B50);
            D_802A1B50 = -1;
            func_802276FC(1);
        }
    }
}

void func_802876C8(UnkStruct_802B0260 *arg0) {
    arg0->unk4 = 0;
    arg0->unk8 = -1;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unk14 = 0xFF;
    arg0->unk18 = 0.0f;
    arg0->unk1C = 0.0f;
    arg0->unk20 = 0.0f;
    arg0->unk24 = 0.0f;
    arg0->unk28 = 0.0f;
    arg0->unk2C = 0.0f;
    arg0->unk38 = 0.0f;
    arg0->unk3C = 0.0f;
    arg0->unk48 = 0.0f;
    arg0->unk4C = 0.0f;
    arg0->unk40 = 1.0f;
    arg0->unk44 = 1.0f;
    arg0->unk30 = 320.0f;
    arg0->unk34 = 240.0f;
}

void func_802876A0(void) {
    func_80297D30(0x1A, D_802A1B54);
    if (0) {
        func_80297D30(0, 0);
        func_80297D30(0, 0);
    }
}

