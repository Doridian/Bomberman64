#include "common.h"

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} Vec3f_8008E648; /* size 0xC */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ Vec3f_8008E648 unk8;
    /* 0x14 */ Vec3f_8008E648 unk14;
    /* 0x20 */ Vec3f_8008E648 unk20;
    /* 0x2C */ s32 unk2C;
} UnkStruct_80090050;

typedef struct UnkStruct_802363BC {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ struct UnkStruct_802363BC *unk3C;
    /* 0x40 */ struct UnkStruct_802363BC *unk40;
} UnkStruct_802363BC; /* size 0x44 */

s32 func_80238A10(void *, s32, s32, s32, s32);
void func_80234F6C(s32);
void func_80235114(Vec3f_8008E648 *);
void func_80235178(Vec3f_8008E648 *);
void func_80236218(s32);
void func_80236658(void);
void func_80237164(Vec3f_8008E648 *);
s32 func_80234768(void);
s32 func_802348A4(void);
void func_802351DC(Vec3f_8008E648 *);
void func_80235208(Vec3f_8008E648 *);
u16 func_80235924(void);
s32 func_80236208(void);
void func_80237264(Vec3f_8008E648 *);

extern Vec3f_8008E648 D_8008E648;
extern Vec3f_8008E648 D_8008F3E8;
extern Vec3f_8008E648 D_8008F3F8;
extern s32 D_8008F404;
extern s32 D_8008F408;
extern s32 D_8008F40C;
extern s32 D_8008F410;
extern Vec3f_8008E648 D_8008F418;
extern u16 D_8008F424;
extern u16 D_8008F426;
extern s32 D_8008F428;
extern s32 D_8008F42C;
extern f32 D_8008FFE8;
extern f32 D_8008FFEC;
extern f32 D_8008FFF0;
extern Vec3f_8008E648 D_8008FFF8;
extern f32 D_80090004;
extern f32 D_80090018;
extern f32 D_8009001C;
extern f32 D_80090034;
extern f32 D_80090038;
extern f32 D_8009003C;
extern f32 D_80090040;
extern f32 D_80090044;
extern f32 D_80090048;
extern UnkStruct_80090050 D_80090050;

#define WRAP360(a) ((a) >= 360.0f ? (a) - 360.0f : ((a) < 0.0f ? (a) + 360.0f : (a)))

void func_8022FEAC(Vec3f_8008E648 *, Vec3f_8008E648 *);
void func_8022FF58(Vec3f_8008E648 *, Vec3f_8008E648 *, Vec3f_8008E648 *);
s32 func_80233650(f32, f32);
s32 func_802336E4(f32);
s32 func_80233768(f32);
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ f32 unk20;
} UnkStruct_80234DD4;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_80234DD4 *unk40;
} UnkStruct_802443F4;

UnkStruct_802443F4 *func_802443F4(s32);
void func_80234778(f32, f32, f32);
void func_80234858(f32 *, f32 *, f32 *);
f32 func_80234D24(f32, f32, f32);
s32 func_80234DD4(f32, f32, f32, UnkStruct_80234DD4 *);
void func_802350F8(s32);
f32 D_802A5A50;
f32 D_802A5A54;
f32 D_802A5A58;

UnkStruct_802363BC D_8029FEA0 = { 20, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 4.5f, 0.0f, 0.0f, -0.24f, 0.0f, 0.0f, NULL, NULL };
UnkStruct_802363BC D_8029FEE4 = { 20, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -4.5f, 0.0f, 0.0f, 0.24f, 0.0f, 0.0f, NULL, NULL };
UnkStruct_802363BC D_8029FF28 = { 20, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -5e+01f, 0.0f, 0.0f, 2.635f, NULL, NULL };
UnkStruct_802363BC D_8029FF6C = { 20, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5e+01f, 0.0f, 0.0f, -2.635f, NULL, NULL };
UnkStruct_802363BC D_8029FFB0 = { 20, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 4e+01f, 0.0f, 0.0f, -2.135f, NULL, NULL };
UnkStruct_802363BC D_8029FFF4 = { 20, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -4e+01f, 0.0f, 0.0f, 2.135f, NULL, NULL };
s32 D_802A0038 = 0;
extern f32 D_8008F430;
#define ABS(x) ((x) < 0.0f ? -(x) : (x))

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ u8 unkC[0xC];
} UnkStruct_8026DCAC; /* size 0x18 */

void func_8026DCAC(f32, f32, f32, UnkStruct_8026DCAC *, s32);
s32 func_8026EE18(f32);
s32 func_8026D7D8(s32, s32, s32);
void func_802358D0(void *, s32, s16);
s32 func_802399AC(s32);
extern UnkStruct_802443F4 *D_8009004C;
s32 func_80243DDC(void);
void func_80234578(Vec3f_8008E648 *, Vec3f_8008E648 *, Vec3f_8008E648 *);
void func_8023494C(f32 *);
void func_80235234(Vec3f_8008E648 *);
void func_80235934(Vec3f_8008E648 *, u16 *);
extern Vec3f_8008E648 D_80090020;
extern f32 D_8009002C;
extern f32 D_80090030;
void func_802346C8(f32, f32, f32);
void func_80234718(f32, f32, f32);
UnkStruct_802363BC *func_802391F0(void);
void func_80239430(void);
void func_802348B4(f32 *, f32 *, f32 *);
void func_80234900(f32 *, f32 *, f32 *);
void func_802362F0(UnkStruct_802363BC *, UnkStruct_802363BC *);
void func_802363BC(UnkStruct_802363BC *);
void func_8023646C(UnkStruct_802363BC *);
void func_80236AEC(u16);
void func_80236ACC(u16);
s32 func_80234248(s32);
void func_80227CD0(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern s32 D_802AC5C0;
extern Vec3f_8008E648 D_8008F3D8;
void func_80235D7C(void);
void func_80236D30(void);
s32 func_80236BA8(Vec3f_8008E648 *);
typedef struct {
    /* 0x0 */ Vec3f_8008E648 pos;
    /* 0xC */ s32 unkC;
} UnkStruct_80250338;
void func_80250338(s32, UnkStruct_80250338 *);
void func_80234550(void);
void func_802362B8(s32);
void func_80236048(f32, f32);
void func_802361FC(f32);
void func_802361F0(f32);
void func_802361E4(f32);
void func_80236174(f32);
void func_80236180(Vec3f_8008E648 *);
void func_80235FE4(f32, f32, f32, f32);
void func_80235FD8(UnkStruct_802443F4 *);
void func_802360D4(f32, f32, f32, f32);
void func_80236B7C(void);
void func_80237890(void) {
    func_80234550();
    func_802346C8(0.0f, 0.0f, 0.0f);
    func_80234718(0.0f, 3000.0f, 3000.0f);
    func_80234778(0.0f, 0.0f, 0.000001f);
    func_802350F8(1);
    func_80234F6C(1);
    func_802362B8(0x7F);
    func_80236218(1);
    func_802360D4(2400.0f, 1600.0f, 1600.0f, 2400.0f);
    func_80236048(70.0f, 45.0f);
    func_80235FE4(2400.0f, 1600.0f, 2400.0f, 1600.0f);
    func_80235FD8(NULL);
    func_80236B7C();
}

void func_80237664(void) {
    Vec3f_8008E648 sp9C;
    UnkStruct_80250338 sp8C;

    func_802350F8(1);
    func_80234F6C(1);
    func_80250338(func_80243DDC(), &sp8C);
    func_802346C8(sp8C.pos.x, sp8C.pos.y, sp8C.pos.z);
    func_80234778(32768.0f, 45.0f, 32768.0f);
    func_802362B8(0x7F);
    func_802360D4(2400.0f, 1600.0f, 800.0f, 1600.0f);
    func_80236048(70.0f, 45.0f);
    func_802361FC(10.0f);
    func_802361F0(0.1f);
    sp9C.x = 0.0f;
    sp9C.y = 0.0f;
    sp9C.z = 80.0f;
    func_80236180(&sp9C);
    D_8008FFF0 = sp9C.z * 2;
    func_80236174(1.0f);
    func_80235FE4(1600.0f, 1600.0f, 3200.0f, 1600.0f);
    func_80235FD8(NULL);
    func_80236B7C();
    func_802358D0(NULL, 0, 0);
}

f32 func_802375A4(f32 arg0) {
    Vec3f_8008E648 sp2C;

    switch (D_8008F404) {
        case 0:
            func_8022FF58(&D_8008F3E8, &D_8008E648, &sp2C);
            break;
        case 1:
            func_8022FF58(&D_8008E648, &D_8008F3E8, &sp2C);
            break;
    }
    return WRAP360(sp2C.x + arg0);
}

void func_80237478(f32 *arg0, f32 *arg1) {
    Vec3f_8008E648 sp24;

    switch (D_8008F404) {
        case 0:
            func_8022FF58(&D_8008F3E8, &D_8008E648, &sp24);
            break;
        case 1:
            func_8022FF58(&D_8008E648, &D_8008F3E8, &sp24);
            break;
    }
    *arg0 = WRAP360(sp24.x);
    *arg1 = WRAP360((sp24.y - 90.0f) * -1.0f);
}

void func_8023733C(UnkStruct_80234DD4 *arg0, f32 *arg1, f32 *arg2) {
    Vec3f_8008E648 sp34;
    Vec3f_8008E648 sp28;

    sp28.x = arg0->unk10;
    sp28.y = arg0->unk14;
    sp28.z = arg0->unk18;
    switch (D_8008F404) {
        case 0:
            func_8022FF58(&sp28, &D_8008E648, &sp34);
            break;
        case 1:
            func_8022FF58(&sp28, &D_8008F3E8, &sp34);
            break;
    }
    *arg1 = WRAP360(sp34.x);
    *arg2 = WRAP360((sp34.y - 90.0f) * -1.0f);
}

void func_80237290(void) {
    D_80090050.unk0 = func_80234768();
    D_80090050.unk4 = func_802348A4();
    func_802351DC(&D_80090050.unk8);
    switch (D_80090050.unk4) {
        case 0:
            func_80235208(&D_80090050.unk14);
            break;
        case 1:
            func_80237264(&D_80090050.unk20);
            break;
    }
    D_80090050.unk2C = func_80236208();
}

void func_80237264(Vec3f_8008E648 *arg0) {
    arg0->x = D_8008F3F8.x;
    arg0->y = D_8008F3F8.y;
    arg0->z = D_8008F3F8.z;
}

void func_802371C8(void) {
    if (D_80090050.unk0 == 0 || D_80090050.unk0 == 1) {
        D_8008F404 = D_80090050.unk0;
    }
    func_80234F6C(D_80090050.unk4);
    func_80235114(&D_80090050.unk8);
    switch (D_80090050.unk4) {
        case 0:
            func_80235178(&D_80090050.unk14);
            break;
        case 1:
            func_80237164(&D_80090050.unk20);
            break;
    }
    func_80236218(D_80090050.unk2C);
}

void func_80237164(Vec3f_8008E648 *arg0) {
    if (arg0->x != 32768.0f) {
        D_8008F3F8.x = arg0->x;
    }
    if (arg0->y != 32768.0f) {
        D_8008F3F8.y = arg0->y;
    }
    if (arg0->z != 32768.0f) {
        D_8008F3F8.z = arg0->z;
    }
}

void func_80236F54(void) {
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;
    f32 atX;
    f32 atY;
    f32 atZ;
    f32 upX;
    f32 upY;
    f32 upZ;
    Vec3f_8008E648 sp88;

    eyeX = eyeY = eyeZ = atX = atY = atZ = 0.0f;
    func_802358D0(NULL, 0, 0);
    sp88.x = sp88.y = sp88.z = 0.0f;
    func_80238A10(func_80235D7C, 0, 0, 0, 0x90);
    while (1) {
        func_80236D30();
        switch (D_8008F404) {
            case 0:
                eyeX = D_8008E648.x;
                eyeY = D_8008E648.y;
                eyeZ = D_8008E648.z;
                atX = D_8008F3D8.x;
                atY = D_8008F3D8.y;
                atZ = D_8008F3D8.z;
                break;
            case 1:
                eyeX = D_8008F3D8.x;
                eyeY = D_8008F3D8.y;
                eyeZ = D_8008F3D8.z;
                atX = D_8008E648.x;
                atY = D_8008E648.y;
                atZ = D_8008E648.z;
                break;
        }
        if (func_80236BA8(&sp88) != 0) {
            eyeX += sp88.x;
            eyeY += sp88.y;
            eyeZ += sp88.z;
            atX += sp88.x;
            atY += sp88.y;
            atZ += sp88.z;
        }
        upX = 0.0f;
        upY = 1.0f;
        upZ = 0.0f;
        func_80227CD0(D_802AC5C0, eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ);
        func_80239094();
    }
}

void func_80236D30(void) {
    Vec3f_8008E648 sp2C;

    switch (D_8008F408) {
        case 0:
            func_80235208(&D_8008F3D8);
            func_8022FF58(&D_8008E648, &D_8008F3E8, &D_8008F3F8);
            D_8008F3F8.y = WRAP360(D_8008F3F8.y - 90.0f);
            break;
        case 1:
            D_8008F3F8.x = WRAP360(D_8008F3F8.x);
            D_8008F3F8.y = WRAP360(D_8008F3F8.y);
            sp2C.x = D_8008F3F8.x;
            sp2C.y = WRAP360(D_8008F3F8.y);
            sp2C.z = D_8008F3F8.z;
            func_8022FEAC(&sp2C, &D_8008F3D8);
            D_8008F3D8.x += D_8008E648.x;
            D_8008F3D8.y += D_8008E648.y;
            D_8008F3D8.z += D_8008E648.z;
            D_8008F3E8.x = D_8008F3D8.x;
            D_8008F3E8.y = D_8008F3D8.y;
            D_8008F3E8.z = D_8008F3D8.z;
            break;
    }
}

s32 func_80236BA8(Vec3f_8008E648 *arg0) {
    f32 t;

    if (D_8008F40C != 0) {
        if (D_8008F40C != -1) {
            t = (f32) D_8008F40C / (f32) D_8008F410;
        } else {
            t = 1.0f;
        }
        t = t * t;
        arg0->x = (func_80234248(1) ? 1.0f : -1.0f) * D_8008F418.x * t;
        arg0->y = (func_80234248(1) ? 1.0f : -1.0f) * D_8008F418.y * t;
        arg0->z = (func_80234248(1) ? 1.0f : -1.0f) * D_8008F418.z * t;
        if (D_8008F40C != -1) {
            D_8008F40C--;
        }
    } else {
        arg0->x = 0.0f;
        arg0->y = 0.0f;
        arg0->z = 0.0f;
    }
    return D_8008F40C;
}

void func_80236B7C(void) {
    D_8008F40C = 0;
    D_8008F410 = 0;
    D_8008F418.x = 0.0f;
    D_8008F418.y = 0.0f;
    D_8008F418.z = 0.0f;
}

void func_80236B68(s32 arg0) {
    D_8008F40C = arg0;
    D_8008F410 = arg0;
}

s32 func_80236B58(void) {
    return D_8008F40C;
}

void func_80236B08(f32 arg0, f32 arg1, f32 arg2) {
    if (arg0 != 32768.0f) {
        D_8008F418.x = arg0;
    }
    if (arg1 != 32768.0f) {
        D_8008F418.y = arg1;
    }
    if (arg2 != 32768.0f) {
        D_8008F418.z = arg2;
    }
}

void func_80236AEC(u16 arg0) {
    D_8008F424 |= arg0;
}

void func_80236ACC(u16 arg0) {
    D_8008F424 &= ~arg0;
}

void func_802358D0(void *arg0, s32 arg1, s16 arg2) {
    // Source order: this function and func_80235924 sit just above
    // func_80236658, not in address order.  In address order IDO -O3 pulls
    // func_80236658 (whose address this takes) and its callees in before this
    // function; here func_80235934 pulls both in instead, in their place.
    D_8008F424 = arg2;
    D_8008F426 = 0;
    if (arg0 != 0) {
        func_80238A10(func_80236658, arg0, 0, 0, arg1);
    }
}

u16 func_80235924(void) {
    return D_8008F426;
}

void func_80236658(void) {
    // func_80239094 is not declared in this file: called as an implicit
    // `int` function, it lets flags & 2 have $v0 (as void, $a0).
    UnkStruct_802363BC sp114;
    UnkStruct_802363BC spD0;
    UnkStruct_802363BC *entry;
    s32 flags;
    s32 active;
    Vec3f_8008E648 spB8;
    Vec3f_8008E648 spAC;

    func_802363BC(&sp114);
    entry = &spD0;
    func_802363BC(&spD0);
    spD0.unk40 = func_802391F0();
    func_802362F0(&spD0, &sp114);
    while (entry != NULL) {
        flags = D_8008F424;
        if (flags & 0x8000) {
            entry = NULL;
        } else {
            if (sp114.unk0 == 0) {
                entry = entry->unk40;
                if (entry == NULL) {
                    D_8008F424 = flags | 0x8000;
                    active = 0;
                } else {
                    func_802362F0(entry, &sp114);
                    switch (entry->unk4) {
                        case 0:
                        case 1:
                            func_802350F8(entry->unk4);
                            active = 1;
                            func_80234F6C(entry->unk8);
                            break;
                        case 2:
                            active = 0;
                            func_8023646C(entry);
                            break;
                        default:
                            while (1) {
                            }
                    }
                    if (1) { // fake (permuter): moves &D_8008F426 to $s8
                    }
                }
            }
            if (active) {
                do {
                    D_8008F426 = 1;
                    func_802348B4(&spB8.x, &spB8.y, &spB8.z);
                    spB8.x += sp114.unkC;
                    spB8.y += sp114.unk10;
                    spB8.z += sp114.unk14;
                    func_802346C8(spB8.x, spB8.y, spB8.z);
                    switch (entry->unk8) {
                        case 0:
                            func_80234900(&spAC.x, &spAC.y, &spAC.z);
                            spAC.x += sp114.unk24;
                            spAC.y += sp114.unk28;
                            spAC.z += sp114.unk2C;
                            func_80234718(spAC.x, spAC.y, spAC.z);
                            break;
                        case 1:
                            func_80234858(&spAC.x, &spAC.y, &spAC.z);
                            spAC.x += sp114.unk24;
                            spAC.y += sp114.unk28;
                            spAC.z += sp114.unk2C;
                            func_80234778(spAC.x, spAC.y, spAC.z);
                            break;
                        default:
                            while (1) {
                            }
                    }
                    sp114.unkC += sp114.unk18;
                    sp114.unk10 += sp114.unk1C;
                    sp114.unk14 += sp114.unk20;
                    sp114.unk24 += sp114.unk30;
                    sp114.unk28 += sp114.unk34;
                    sp114.unk2C += sp114.unk38;
                    sp114.unk0--;
                    flags = D_8008F424;
                    if (flags & 2) {
                        D_8008F426 = 2;
                        while (flags & 2) {
                            func_80239094();
                            flags = D_8008F424;
                        }
                    } else {
                        func_80239094();
                        flags = D_8008F424;
                    }
                    if (sp114.unk0 == 0) {
                        active = 0;
                    }
                    if (flags & 0x8000) {
                        active = 0;
                    }
                } while (active);
            }
        }
    }
    D_8008F426 = 0x8000;
    func_80239430();
}

void func_8023646C(UnkStruct_802363BC *arg0) {
    if (arg0->unkC != 32768.0f && arg0->unk10 != 32768.0f && arg0->unk14 != 32768.0f) {
        func_802346C8(arg0->unkC, arg0->unk10, arg0->unk14);
    }
    func_80234F6C(arg0->unk8);
    switch (arg0->unk8) {
        case 0:
            if (arg0->unk24 != 32768.0f && arg0->unk28 != 32768.0f && arg0->unk2C != 32768.0f) {
                func_80234718(arg0->unk24, arg0->unk28, arg0->unk2C);
            }
            break;
        case 1:
            if (arg0->unk24 != 32768.0f && arg0->unk28 != 32768.0f && arg0->unk2C != 32768.0f) {
                func_80234778(arg0->unk24, arg0->unk28, arg0->unk2C);
            }
            break;
        default:
            while (1) {
            }
    }
}

s32 func_8023640C(void) {
    s32 frames = 0;

    while (func_80235924() != 0x8000) {
        func_80239094();
        frames++;
    }
    return frames;
}

void func_802363BC(UnkStruct_802363BC *arg0) {
    arg0->unk0 = 0;
    arg0->unk4 = 1;
    arg0->unk8 = 1;
    arg0->unk3C = NULL;
    arg0->unk40 = NULL;
    arg0->unkC = 0.0f;
    arg0->unk10 = 0.0f;
    arg0->unk14 = 0.0f;
    arg0->unk18 = 0.0f;
    arg0->unk1C = 0.0f;
    arg0->unk20 = 0.0f;
    arg0->unk24 = 0.0f;
    arg0->unk28 = 0.0f;
    arg0->unk2C = 0.0f;
    arg0->unk30 = 0.0f;
    arg0->unk34 = 0.0f;
    arg0->unk38 = 0.0f;
}

void func_802362F0(UnkStruct_802363BC *arg0, UnkStruct_802363BC *arg1) {
    arg1->unk0 = arg0->unk0;
    arg1->unk4 = arg0->unk4;
    arg1->unk8 = arg0->unk8;
    arg1->unkC = arg0->unkC;
    arg1->unk10 = arg0->unk10;
    arg1->unk14 = arg0->unk14;
    arg1->unk18 = arg0->unk18;
    arg1->unk1C = arg0->unk1C;
    arg1->unk20 = arg0->unk20;
    arg1->unk24 = arg0->unk24;
    arg1->unk28 = arg0->unk28;
    arg1->unk2C = arg0->unk2C;
    arg1->unk30 = arg0->unk30;
    arg1->unk34 = arg0->unk34;
    arg1->unk38 = arg0->unk38;
    arg1->unk3C = arg0->unk3C;
    arg1->unk40 = arg0->unk3C;
}

void func_802362D4(s32 arg0) {
    D_8008F428 |= arg0;
}

void func_802362B8(s32 arg0) {
    D_8008F428 &= ~arg0;
}

s32 func_802362A8(void) {
    return D_8008F428;
}

void func_80236218(s32 arg0) {
    D_8008F42C = arg0;
    switch (D_8008F42C) {
        case 0:
            func_80234778(32768.0f, 32768.0f, 1500.0f);
            break;
        case 1:
            func_80234778(32768.0f, 32768.0f, 2000.0f);
            break;
        case 2:
            func_80234778(32768.0f, 32768.0f, 2400.0f);
            break;
    }
}

s32 func_80236208(void) {
    return D_8008F42C;
}

void func_802361FC(f32 arg0) {
    D_8008FFE8 = arg0;
}

void func_802361F0(f32 arg0) {
    D_8008FFEC = arg0;
}

void func_802361E4(f32 arg0) {
    D_8008FFF0 = arg0;
}

void func_80236180(Vec3f_8008E648 *arg0) {
    if (arg0->x != 32768.0f) {
        D_8008FFF8.x = arg0->x;
    }
    if (arg0->y != 32768.0f) {
        D_8008FFF8.y = arg0->y;
    }
    if (arg0->z != 32768.0f) {
        D_8008FFF8.z = arg0->z;
    }
}

void func_80236174(f32 arg0) {
    D_80090004 = arg0;
}

void func_802360D4(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != 32768.0f) {
        D_80090020.x = arg0;
    }
    if (arg1 != 32768.0f) {
        D_80090020.z = arg1;
    }
    D_80090020.y = 0.0f;
    if (arg2 != 32768.0f) {
        D_80090030 = arg2;
    }
    if (arg3 != 32768.0f) {
        D_8009002C = arg3;
    }
    if (!(D_8008F428 & 0x40)) {
        D_80090038 = D_80090030;
        D_80090034 = D_8009002C;
    }
}

void func_80236084(f32 arg0, f32 arg1) {
    if (D_8008F428 & 0x40) {
        if (arg0 != 32768.0f) {
            D_80090038 = arg0;
        }
        if (arg1 != 32768.0f) {
            D_80090034 = arg1;
        }
    }
}

void func_80236048(f32 arg0, f32 arg1) {
    if (arg0 != 32768.0f) {
        D_80090018 = arg0;
    }
    if (arg1 != 32768.0f) {
        D_8009001C = arg1;
    }
}

void func_80235FE4(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != 32768.0f) {
        D_8009003C = arg0;
    }
    if (arg1 != 32768.0f) {
        D_80090040 = arg1;
    }
    if (arg2 != 32768.0f) {
        D_80090044 = arg2;
    }
    if (arg3 != 32768.0f) {
        D_80090048 = arg3;
    }
}

void func_80235FD8(UnkStruct_802443F4 *arg0) {
    D_8009004C = arg0;
}

void func_80235D7C(void) {
    UnkStruct_802443F4 *p;
    u16 sp8A;
    Vec3f_8008E648 sp7C;
    Vec3f_8008E648 sp70;
    Vec3f_8008E648 sp64;
    f32 sp60;

    sp60 = 0.0f;
    while (1) {
        if (D_8008F428 & 0x10) {
            if (!(D_8008F428 & 0x20)) {
                p = func_802443F4(func_80243DDC());
                sp60 = func_80233650(D_8008FFF8.x, p->unk40->unk20) ? 0.0f : sp60 + 1.0f;
                if (D_80090004 < sp60) {
                    D_8008FFF8.x = p->unk40->unk20;
                }
                sp64.x = D_8008FFF8.x;
                sp64.y = D_8008FFF8.y;
                sp64.z = D_8008FFF8.z;
                func_8022FEAC(&sp64, &sp70);
                sp70.x += p->unk40->unk10;
                sp70.y += p->unk40->unk14 + 100.0f;
                sp70.z += p->unk40->unk18;
            } else {
                sp70.x = D_8009004C->unk40->unk10;
                sp70.y = D_8009004C->unk40->unk14;
                sp70.z = D_8009004C->unk40->unk18;
            }
            func_80235234(&sp70);
            func_8023494C(&sp60);
        } else {
            sp60 = 0.0f;
            D_8008F430 = D_8008FFE8;
        }
        if (D_8008F428 & 0xF) {
            func_80235934(&sp7C, &sp8A);
        }
        func_80239094();
    }
}

void func_80235934(Vec3f_8008E648 *arg0, u16 *arg1) {
    switch (func_80235924()) {
        case 0:
            *arg1 = func_802399AC(0) & 0xF;
            func_80234858(&arg0->x, &arg0->y, &arg0->z);
            switch (*arg1) {
                case 8:
                    if (D_8008F428 & 1) {
                        switch (D_8008F42C) {
                            case 1:
                                func_802358D0(&D_8029FF28, 0x170, 0);
                                D_8008F42C--;
                                break;
                            case 2:
                                func_802358D0(&D_8029FFF4, 0x170, 0);
                                D_8008F42C--;
                                break;
                        }
                    }
                    break;
                case 4:
                    if (D_8008F428 & 4) {
                        switch (D_8008F42C) {
                            case 0:
                                func_802358D0(&D_8029FF6C, 0x170, 0);
                                D_8008F42C++;
                                break;
                            case 1:
                                func_802358D0(&D_8029FFB0, 0x170, 0);
                                D_8008F42C++;
                                break;
                        }
                    }
                    break;
                case 1:
                    if (D_8008F428 & 2) {
                        func_802358D0(&D_8029FEA0, 0x170, 0);
                    }
                    break;
                case 2:
                    if (D_8008F428 & 8) {
                        func_802358D0(&D_8029FEE4, 0x170, 0);
                    }
                    break;
            }
            break;
        case 1:
        case 2:
            break;
        case 0x8000:
            switch (*arg1) {
                case 8:
                case 4:
                    switch (D_8008F42C) {
                        case 0:
                            func_80234778(32768.0f, 32768.0f, 1500.0f);
                            break;
                        case 1:
                            func_80234778(32768.0f, 32768.0f, 2000.0f);
                            break;
                        case 2:
                            func_80234778(32768.0f, 32768.0f, 2400.0f);
                            break;
                    }
                    func_802358D0(NULL, 0, 0);
                    break;
                case 1:
                    if (D_802A0038 == 0) {
                        func_80234778(arg0->x + 45.0f, 32768.0f, 32768.0f);
                    }
                    func_802358D0(NULL, 0, 0);
                    break;
                case 2:
                    if (D_802A0038 == 0) {
                        func_80234778(arg0->x - 45.0f, 32768.0f, 32768.0f);
                    }
                    func_802358D0(NULL, 0, 0);
                    break;
            }
            break;
        default:
            while (1) {
            }
    }
}



void func_80235234(Vec3f_8008E648 *arg0) {
    static f32 D_802A003C = 0.5f;
    static f32 D_802A0040 = 1.0f;
    static f32 D_802A0044 = 0.0f;
    static s32 D_802A0048 = 0;
    static s32 D_802A004C = 1;
    Vec3f_8008E648 sp94;
    Vec3f_8008E648 sp88;
    Vec3f_8008E648 sp7C;
    s32 ret;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    UnkStruct_802443F4 *p;
    f32 diff;
    s32 sp5C;

    switch (func_80234768()) {
        case 0:
            func_80235208(&sp94);
            break;
        case 1:
            func_802351DC(&sp94);
            break;
    }
    func_8022FF58(arg0, &sp94, &sp7C);
    sp7C.z = func_80234D24(sp7C.z, 0.0f, D_8008F430);
    if (func_802336E4(sp7C.z) != 0) {
        D_8008F430 = D_8008FFE8;
    } else if (sp7C.z < 80.0f) {
        if (D_802A003C >= 0.0f) {
            D_8008F430 = 2.5f;
        }
        D_802A003C = -0.05f;
        D_8008F430 += D_802A003C;
        if (D_8008F430 < 0.6f) {
            D_8008F430 = 0.6f;
        }
    } else {
        if (D_802A003C < 0.0f) {
            D_8008F430 = 8.0f;
        }
        D_802A003C = 0.5f;
        D_8008F430 += D_802A003C;
        if (8.0f < D_8008F430) {
            D_8008F430 = 8.0f;
        }
    }
    sp7C.y = WRAP360(sp7C.y - 90.0f);
    if (func_80233768(sp7C.z - D_8008FFF0) == 1) {
        D_8008F430 += D_8008FFEC * 2.0f;
        if (D_8008FFF0 * 3.0f < sp7C.z) {
            sp7C.z = D_8008FFF0 * 3.0f;
        }
    }
    func_8022FEAC(&sp7C, &sp88);
    sp94.x = arg0->x + sp88.x;
    sp94.y = arg0->y + sp88.y;
    sp94.z = arg0->z + sp88.z;
    switch (func_80234768()) {
        case 0:
            func_80235178(&sp94);
            break;
        case 1:
            func_80235114(&sp94);
            break;
    }
    if (D_802A0038 != 0) {
        if (D_802A5A54 == arg0->x && D_802A5A58 == arg0->y) {
            sp5C = 0;
            D_802A5A50 = D_802A0040 * 0.4;
        } else {
            D_802A5A50 = D_802A0040 * 0.2;
            sp5C = 1;
        }
        func_802350F8(1);
        func_80234F6C(1);
        func_80234858(&sp74, &sp70, &sp6C);
        sp68 = sp74;
        p = func_802443F4(0);
        diff = sp74 - p->unk40->unk20;
        if (diff < 0.0f) {
            diff += 360.0f;
        } else if (diff >= 360.0f) {
            diff -= 360.0f;
        }
        if (diff >= 0.0f && diff <= 179.0f) {
            sp74 += D_802A5A50;
            if (D_802A0048 == 0) {
                D_802A004C = 1;
            }
        } else if (diff > 180.0f && diff <= 359.0f) {
            sp74 -= D_802A5A50;
            if (D_802A0048 == 0) {
                D_802A004C = -1;
            }
        }
        if (sp74 < 0.0f) {
            sp74 += 360.0f;
        } else if (sp74 >= 360.0f) {
            sp74 -= 360.0f;
        }
        if (ABS(diff - 180.0f) < 40.0f) {
            D_802A0040 -= D_802A0044;
            if (D_802A0040 < 0.1f) {
                D_802A0040 = 0.1f;
            }
            D_802A0044 += 0.001f;
        } else {
            D_802A0044 = 0.0f;
            D_802A0040 = 1.0f;
        }
        ret = func_80234DD4(sp74, sp70, sp6C, p->unk40);
        if (ret != 0) {
            if (D_802A0048 == 0) {
                sp74 = sp68;
                if (sp5C != 0 && ret != 0x2010) {
                    D_802A0048 = 1;
                }
            } else {
                D_802A0048 = 1;
                if (D_802A004C > 0) {
                    sp74 += D_802A0040;
                } else {
                    sp74 -= D_802A0040;
                }
            }
        } else {
            D_802A0048 = 0;
        }
        func_80234778(sp74, sp70, sp6C);
        D_802A5A54 = arg0->x;
        D_802A5A58 = arg0->y;
    }
}

void func_80235208(Vec3f_8008E648 *arg0) {
    arg0->x = D_8008F3E8.x;
    arg0->y = D_8008F3E8.y;
    arg0->z = D_8008F3E8.z;
}

void func_802351DC(Vec3f_8008E648 *arg0) {
    arg0->x = D_8008E648.x;
    arg0->y = D_8008E648.y;
    arg0->z = D_8008E648.z;
}

void func_80235178(Vec3f_8008E648 *arg0) {
    if (arg0->x != 32768.0f) {
        D_8008F3E8.x = arg0->x;
    }
    if (arg0->y != 32768.0f) {
        D_8008F3E8.y = arg0->y;
    }
    if (arg0->z != 32768.0f) {
        D_8008F3E8.z = arg0->z;
    }
}

void func_80235114(Vec3f_8008E648 *arg0) {
    if (arg0->x != 32768.0f) {
        D_8008E648.x = arg0->x;
    }
    if (arg0->y != 32768.0f) {
        D_8008E648.y = arg0->y;
    }
    if (arg0->z != 32768.0f) {
        D_8008E648.z = arg0->z;
    }
}

void func_802350F8(s32 arg0) {
    if (arg0 == 0 || arg0 == 1) {
        D_8008F404 = arg0;
    }
}

void func_80234F6C(s32 arg0) {
    Vec3f_8008E648 sp2C;

    switch (arg0) {
        case 0:
            if (D_8008F408 == 0) {
                break;
            }
            D_8008F408 = arg0;
            sp2C.x = D_8008F3F8.x;
            sp2C.y = WRAP360(D_8008F3F8.y);
            sp2C.z = D_8008F3F8.z;
            func_8022FEAC(&sp2C, &D_8008F3E8);
            D_8008F3E8.x += D_8008E648.x;
            D_8008F3E8.y += D_8008E648.y;
            D_8008F3E8.z += D_8008E648.z;
            break;
        case 1:
            if (D_8008F408 == 1) {
                break;
            }
            D_8008F408 = arg0;
            func_8022FF58(&D_8008E648, &D_8008F3E8, &D_8008F3F8);
            D_8008F3F8.y = WRAP360(D_8008F3F8.y - 90.0f);
            break;
    }
}

s32 func_80234DD4(f32 arg0, f32 arg1, f32 arg2, UnkStruct_80234DD4 *arg3) {
    Vec3f_8008E648 sp8C;
    Vec3f_8008E648 sp80;
    UnkStruct_8026DCAC sp68;
    s32 ret;

    sp80.x = arg0;
    sp80.y = arg1;
    ret = 0;
    sp80.z = 50.0f;
    while (sp80.z < arg2) {
        func_8022FEAC(&sp80, &sp8C);
        sp8C.x += arg3->unk10 + 50.0f;
        sp8C.y += arg3->unk14;
        sp8C.z += arg3->unk18 + 50.0f;
        func_8026DCAC(sp8C.x, sp8C.y, sp8C.z, &sp68, 0);
        if (sp68.unk4) { // fake (permuter): an empty test that changes IDO's
        }                // float register priorities (arg2 in $f22)
        sp68.unk4 = func_8026EE18(sp8C.y);
        if (sp68.unk4 >= func_8026EE18(5000.0f)) {
            break;
        }
        ret = func_8026D7D8(sp68.unk0, sp68.unk4, sp68.unk8);
        if ((ret & 0xF) == 0xF || ret == 0x2010) {
            break;
        }
        ret = 0;
        sp80.z += 100.0f;
    }
    return ret;
}

f32 func_80234D24(f32 arg0, f32 arg1, f32 arg2) {
    if (func_80233650(arg0, arg1) == 0) {
        if (func_80233768(arg0 - arg1) == -1) {
            arg0 += arg2;
            if (func_80233768(arg0 - arg1) > 0) {
                arg0 = arg1;
            }
        } else {
            arg0 -= arg2;
            if (func_80233768(arg0 - arg1) < 0) {
                arg0 = arg1;
            }
        }
    } else {
        arg0 = arg1;
    }
    return arg0;
}

void func_8023494C(f32 *arg0) {
    Vec3f_8008E648 spCC;
    Vec3f_8008E648 spC0;
    Vec3f_8008E648 spB4;
    Vec3f_8008E648 spA8;
    f32 spA4;
    Vec3f_8008E648 sp98;
    f32 far;
    f32 near;

    switch (func_80234768()) {
        case 0:
            func_80234900(&spCC.x, &spCC.y, &spCC.z);
            break;
        case 1:
            func_802348B4(&spCC.x, &spCC.y, &spCC.z);
            break;
    }
    spA4 = spCC.y;
    spCC.y = 0.0f;
    func_80234578(&sp98, &D_80090020, &spCC);
    func_8022FF58(&sp98, &spCC, &spB4);
    if (!(D_8008F428 & 0x40)) {
        far = D_8009002C;
        near = D_80090030;
    } else {
        far = D_80090034;
        near = D_80090038;
    }
    if (func_802348A4() == 1) {
        func_80234858(&spA8.x, &spA8.y, &spA8.z);
        if (!(spA8.y >= 0.0f && spA8.y <= 180.0f)) {
            spA8.y = (360 - spA8.y) * -1;
        }
        if (near < spB4.z) {
            if (D_80090018 > 0.0f) {
                spA8.y = (D_80090018 - D_8009001C) * ((spB4.z - near) / (far - near)) + D_8009001C;
            } else {
                spA8.y = D_80090018 - (D_80090018 - D_8009001C) * ((spB4.z - near) / (far - near));
            }
        }
        if (spA8.y < D_8009001C) {
            spA8.y = D_8009001C;
        }
        if (D_80090018 < spA8.y) {
            spA8.y = D_80090018;
        }
        func_80234778(spA8.x, spA8.y, spA8.z);
    }
    if (D_8009002C < spB4.z) {
        D_8008F430 = D_8008FFE8;
        *arg0 = 0.0f;
        spB4.z = D_8009002C;
        spB4.y = WRAP360(spB4.y - 90.0f);
        func_8022FEAC(&spB4, &spC0);
        spCC.x = sp98.x + spC0.x;
        spCC.z = sp98.z + spC0.z;
        switch (func_80234768()) {
            case 0:
                func_80234718(spCC.x, spA4, spCC.z);
                break;
            case 1:
                func_802346C8(spCC.x, spA4, spCC.z);
                break;
        }
    }
}

void func_80234900(f32 *arg0, f32 *arg1, f32 *arg2) {
    if (arg0 != NULL) {
        *arg0 = D_8008F3E8.x;
    }
    if (arg1 != NULL) {
        *arg1 = D_8008F3E8.y;
    }
    if (arg2 != NULL) {
        *arg2 = D_8008F3E8.z;
    }
}

void func_802348B4(f32 *arg0, f32 *arg1, f32 *arg2) {
    if (arg0 != NULL) {
        *arg0 = D_8008E648.x;
    }
    if (arg1 != NULL) {
        *arg1 = D_8008E648.y;
    }
    if (arg2 != NULL) {
        *arg2 = D_8008E648.z;
    }
}

s32 func_802348A4(void) {
    return D_8008F408;
}

void func_80234858(f32 *arg0, f32 *arg1, f32 *arg2) {
    if (arg0 != NULL) {
        *arg0 = D_8008F3F8.x;
    }
    if (arg1 != NULL) {
        *arg1 = D_8008F3F8.y;
    }
    if (arg2 != NULL) {
        *arg2 = D_8008F3F8.z;
    }
}

void func_80234778(f32 arg0, f32 arg1, f32 arg2) {
    if (arg0 != 32768.0f) {
        arg0 = WRAP360(arg0);
        D_8008F3F8.x = arg0;
    }
    if (arg1 != 32768.0f) {
        arg1 = WRAP360(arg1);
        D_8008F3F8.y = arg1;
    }
    if (arg2 != 32768.0f) {
        D_8008F3F8.z = arg2;
    }
}

s32 func_80234768(void) {
    return D_8008F404;
}

void func_80234718(f32 arg0, f32 arg1, f32 arg2) {
    if (arg0 != 32768.0f) {
        D_8008F3E8.x = arg0;
    }
    if (arg1 != 32768.0f) {
        D_8008F3E8.y = arg1;
    }
    if (arg2 != 32768.0f) {
        D_8008F3E8.z = arg2;
    }
}

void func_802346C8(f32 arg0, f32 arg1, f32 arg2) {
    if (arg0 != 32768.0f) {
        D_8008E648.x = arg0;
    }
    if (arg1 != 32768.0f) {
        D_8008E648.y = arg1;
    }
    if (arg2 != 32768.0f) {
        D_8008E648.z = arg2;
    }
}

void func_80234578(Vec3f_8008E648 *arg0, Vec3f_8008E648 *arg1, Vec3f_8008E648 *arg2) {
    Vec3f_8008E648 sp24;

    func_8022FF58(arg1, arg2, &sp24);
    sp24.y = WRAP360(sp24.y - 90.0f);
    func_8022FEAC(&sp24, arg0);
    arg0->x += arg1->x;
    arg0->y = 0.0f;
    arg0->z += arg1->z;
    if (arg0->x < D_8009003C) {
        arg0->x = D_8009003C;
    }
    if (D_80090044 < arg0->x) {
        arg0->x = D_80090044;
    }
    if (arg0->z < D_80090040) {
        arg0->z = D_80090040;
    }
    if (D_80090048 < arg0->z) {
        arg0->z = D_80090048;
    }
}

void func_80234550(void) {
    static void *D_802A0050[] = {
        func_802350F8, func_80234768, func_80234F6C, func_802348A4,
        func_802346C8, func_802348B4, func_80234718, func_80234900,
        func_80234778, func_80234858, func_802375A4, func_802358D0,
        func_80236AEC, func_80236ACC, func_80235924, func_8023640C,
        func_802362D4, func_802362B8, func_802362A8, func_80236218,
        func_80236208, func_802361FC, func_802361F0, func_802361E4,
        func_80236180, func_80236174, func_802360D4, func_80236048,
        func_80235FE4, func_80235FD8, func_80236B7C, func_80236B68,
        func_80236B58, func_80236B08, func_80235114, func_802351DC,
        func_80235178, func_80235208, func_80237164, func_80237264,
        func_80237290, func_802371C8, func_80236084, NULL,
    };

    func_80297D30(23, D_802A0050);
}
