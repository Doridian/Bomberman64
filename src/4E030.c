#include "common.h"

/* -O3 (the Makefile's O3_C_FILES), so written last function first: IDO
 * 5.3 -O3 emits a file's functions in reverse, a callee from the file
 * (func_80233C30) just before its first caller.  Its wrappers of 4DE50's
 * compares call them with a `jal`: 4DE50 is another file. */

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
} UnkStruct_80233E3C_4;

typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStruct_80233E3C_4 *unk4;
} UnkStruct_80233E3C_48;

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 unk38[0x10];
    /* 0x48 */ UnkStruct_80233E3C_48 *unk48;
} UnkStruct_80233C30;

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[0x2C];
    /* 0x40 */ UnkStruct_80233C30 *unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
} UnkStruct_80231274;

s32 func_8025E5EC(void);
s32 func_8025E63C();
void func_80227BAC(s32, s32, s32);
f32 func_80229D3C(UnkStruct_80233C30 *, s32);
void func_80229E38(UnkStruct_80233C30 *, s32, s32);
void func_8022F808(UnkStruct_80231274 *, f32 *);
void func_8022FC90(UnkStruct_80231274 *);
void func_8022FEAC(f32 *, f32 *);
void func_8022FF58(f32 *, f32 *, f32 *);
void func_802311E8(UnkStruct_80231274 *);
UnkStruct_80231274 *func_80231274(s32, s32, s32, UnkStruct_80231274 *);
void func_80232BA0(f32 *, UnkStruct_80231274 *);
void func_80238A10(void (*)(), s32, s32, s32, s32);
void func_8023903C(s32);
void func_80239094(void);
s32 func_802391F0(void);
void func_80239430(void);
s32 *func_8023A840(void);
s32 func_80243DDC(void);
void func_80250338(s32, f32 *);
void func_8026C630(s32, f32 *);
void func_8026C660(s32);
void func_8027B7C4(s32, f32, f32, f32);
void func_8027BA80(s32, f32, f32, f32, s32, s32);
s32 func_8028A36C(s32);
void func_8028A7CC(s32, f32 *, s32);
void func_8028A81C(s32, f32, f32, f32, s32);
void func_80297D00(s32);
void func_80297D20(void);
f32 fcos(f32);
f32 sinf(f32);

s32 func_80233650(f32, f32);
s32 func_8023369C(f32, f32, f32);
s32 func_802336E4(f32);
s32 func_8023372C(f32, f32);
s32 func_80233768(f32);
s32 func_802337B0(f32, f32);
s32 func_802337EC(f32);

void func_80233830(void);
void func_802339A0(void);
void func_80233A04(void);
void func_80233A74(void);
UnkStruct_80233C30 *func_80233C30(void);
void func_80233C80(f32 *arg0);
void func_80233D7C(void);
void func_80233DEC(void);
void func_80233E3C(void);
void func_802341F0(s32 arg0);
void func_80234210(void);
s32 func_80234248(s32 arg0);
void func_802342D4(f32 arg0, f32 arg1);
f32 func_80234408(f32 arg0);
f32 func_80234434(f32 arg0);
s32 func_80234460(f32 arg0);
s32 func_80234480(f32 arg0, f32 arg1);
s32 func_802344A0(f32 arg0);
s32 func_802344C0(f32 arg0, f32 arg1);
s32 func_802344E0(f32 arg0);
s32 func_80234500(f32 arg0, f32 arg1, f32 arg2);
s32 func_80234528(f32 arg0, f32 arg1);

/* The object's .bss: IDO puts the array 8-aligned, past a 4-byte gap */
s32 D_802A5A30;
UnkStruct_80233C30 *D_802A5A38[4];
void *D_802A5A48;
extern s32 D_802AC5CC;

/* The object's .data: the table it passes func_80297D30, then a flag */
void *D_8029FE40[] = {
    func_80234434, func_80234408, func_8025E63C, func_80234248, func_802342D4,
    func_80234460, func_80234480, func_802344A0, func_802344C0, func_802344E0,
    func_80234500, func_80234528, func_80234210, func_802341F0, func_80233E3C,
    func_80233DEC, func_80233D7C, func_80233C80, func_802339A0, func_80233A04,
};

s32 D_8029FE90 = 0;

s32 func_80234528(f32 arg0, f32 arg1) {
    return func_80233650(arg0, arg1);
}

s32 func_80234500(f32 arg0, f32 arg1, f32 arg2) {
    return func_8023369C(arg0, arg1, arg2);
}

s32 func_802344E0(f32 arg0) {
    return func_802336E4(arg0);
}

s32 func_802344C0(f32 arg0, f32 arg1) {
    return func_8023372C(arg0, arg1);
}

s32 func_802344A0(f32 arg0) {
    return func_80233768(arg0);
}

s32 func_80234480(f32 arg0, f32 arg1) {
    return func_802337B0(arg0, arg1);
}

s32 func_80234460(f32 arg0) {
    return func_802337EC(arg0);
}

f32 func_80234434(f32 arg0) {
    return sinf(0.017453292f * arg0);
}

f32 func_80234408(f32 arg0) {
    return fcos(0.017453292f * arg0);
}

void func_802342D4(f32 arg0, f32 arg1) {
    f32 rot[3];
    f32 out[3];

    rot[0] = arg0 >= 360.0f ? arg0 - 360.0f : arg0 < 0.0f ? arg0 + 360.0f : arg0;
    rot[1] = arg1 >= 360.0f ? arg1 - 360.0f : arg1 < 0.0f ? arg1 + 360.0f : arg1;
    rot[2] = 127.0f;
    func_8022FEAC(rot, out);
    func_80227BAC((s32) out[0] & 0xFF, (s32) out[1] & 0xFF, (s32) out[2] & 0xFF);
}

/* Three static functions -O3 inlined into func_80234248: IDO still emits
 * each as a bare `jr ra` stub just before it, which splat counts as
 * func_80234210's tail.  What they did is unknown (nothing of them is left
 * to see): written as empty. */
static void func_80234230(void) {
}

static void func_80234238(void) {
}

static void func_80234240(void) {
}

s32 func_80234248(s32 arg0) {
    s32 r;
    s32 ret;

    func_80234230();
    func_80234238();
    func_80234240();
    r = func_8025E5EC();
    if (arg0 != 1) {
        ret = r & 0xFFFF;
        if (arg0 < ret) {
            ret = ret - ret / (arg0 + 1) * (arg0 + 1);
        }
    } else {
        ret = r & 1;
    }
    return ret;
}

void func_80234210(void) {
    func_80297D20();
}

void func_802341F0(s32 arg0) {
    func_80297D00(arg0);
}

void func_802341C8(void) {
    func_80297D30(29, D_8029FE40);
}

/* flags is declared first: its stack slot is above the arrays' */
void func_80233E3C(void) {
    s32 *flags;
    f32 pos[3];
    f32 pos2[3];
    f32 step[3];
    f32 rot[3];
    UnkStruct_80231274 *obj;
    s32 i;
    f32 speed;
    f32 accel;

    flags = func_8023A840();
    if (func_8028A36C(0xA4) == 0 || (*flags & 2)) {
        func_80250338(func_80243DDC(), pos);
        obj = func_80231274(0x328, 0x01000000, 0xD0, NULL);
        func_80229E38(obj->unk40, 0x16, 0);
        obj->unk40->unk48->unk4->unk4 = func_80229D3C(obj->unk40, 0) - 0.001f;
        func_802311E8(obj);
        obj->unk40->unk10 = pos[0] + 1000.0f;
        obj->unk40->unk14 = pos[1] + 300.0f;
        obj->unk40->unk18 = pos[2];
        func_8022F808(obj, pos2);
        func_8026C660(0x215);
        pos[1] = obj->unk40->unk14;
        func_8022FF58(pos2, pos, rot);
        obj->unk40->unk20 = rot[0];
        rot[1] = rot[1] - 90.0f >= 360.0f ? rot[1] - 90.0f - 360.0f : rot[1] < 90.0f ? rot[1] - 90.0f + 360.0f : rot[1] - 90.0f;
        speed = rot[2] / 30.0f;
        accel = (speed / 60.0f) * -1.0f;
        for (i = 0; i < 60; i++) {
            rot[2] = speed;
            speed += accel;
            func_8022FEAC(rot, step);
            pos2[0] += step[0];
            pos2[1] += step[1];
            pos2[2] += step[2];
            func_80232BA0(pos2, obj);
            func_80239094();
        }
        func_8027B7C4(3, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
        speed = 2.0f;
        for (i = 0; i < 60; i++) {
            if (rot[1] < 90.0f) {
                rot[1] += 2.0f;
                if (rot[1] > 90.0f) {
                    rot[1] = 90.0f;
                }
            }
            obj->unk40->unk20 = rot[0];
            obj->unk40->unk1C = rot[1] * -1.0f;
            rot[2] = speed;
            speed += 1.0f;
            func_8022FEAC(rot, step);
            pos2[0] += step[0];
            pos2[1] += step[1];
            pos2[2] += step[2];
            func_80232BA0(pos2, obj);
            func_80239094();
        }
        func_8022FC90(obj);
    }
}

void func_80233DEC(void) {
    s32 i;

    D_8029FE90 = 1;
    D_802A5A30 = 0;
    D_802A5A48 = func_8026CE28(0x19);
    for (i = 0; i < 4; i++) {
        D_802A5A38[i] = NULL;
    }
}

void func_80233D7C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_802A5A38[i] != NULL) {
            func_8022A1E8(D_802A5A38[i]);
        }
    }
    D_8029FE90 = 0;
    D_802A5A30 = 0;
    func_8026CCBC(0x19);
}

void func_80233C80(f32 *arg0) {
    s32 *flags = func_8023A840();

    if (D_802A5A30 < 4 && D_8029FE90 != 0 && !(*flags & 2)) {
        D_802A5A38[D_802A5A30] = func_80233C30();
        D_802A5A38[D_802A5A30]->unk10 = arg0[0];
        D_802A5A38[D_802A5A30]->unk14 = arg0[1];
        D_802A5A38[D_802A5A30]->unk18 = arg0[2];
        func_80238A10(func_80233A74, D_802A5A30, 0, 0, 0x150);
        D_802A5A30++;
    }
}

UnkStruct_80233C30 *func_80233C30(void) {
    UnkStruct_80233C30 *obj = func_8022A6C4(D_802A5A48, 0x40);

    obj->unkC |= 0x80;
    obj->unk36 = 0xFF;
    obj->unk28 = obj->unk2C = obj->unk30 = 1.0f;
    return obj;
}

/* obj before id: id's slot is the second */
void func_80233A74(void) {
    UnkStruct_80233C30 *obj;
    s32 id;
    s32 i;
    f32 speed;
    f32 accel;

    id = func_802391F0();
    if (D_802A5A38[id] == NULL) {
        func_80239430();
    }
    obj = D_802A5A38[id];
    speed = 8.333333f;
    func_8026C660(0x38);
    func_8028A81C(3, obj->unk10, obj->unk14, obj->unk18, 0);
    accel = (speed / 60.0f) * -1.0f;
    for (i = 0; i < 60; i++) {
        if (D_802A5A38[id] == NULL) {
            func_80239430();
        }
        obj->unk14 += speed;
        speed += accel;
        func_80239094();
    }
    func_8023903C(30);
    if (D_802A5A38[id] == NULL) {
        func_80239430();
    }
    func_8028A81C(2, obj->unk10, obj->unk14, obj->unk18, 0);
    obj->unk34 = D_802AC5CC;
    obj->unk28 = obj->unk2C = obj->unk30 = 0.01f;
    obj->unk10 = -5.5f;
    obj->unk14 = id * -1.4f + 2.0f;
    obj->unk18 = 980.0f;
    func_80239430();
}

void func_80233A04(void) {
    if (D_802A5A30 > 0) {
        func_8026C660(0x39);
        func_8022A1E8(D_802A5A38[D_802A5A30 - 1]);
        D_802A5A38[D_802A5A30 - 1] = NULL;
        D_802A5A30--;
    }
}

void func_802339A0(void) {
    s32 *flags = func_8023A840();

    if (func_8028A36C(0xA4) != 0) {
        if (!(*flags & 2)) {
            func_80238A10(func_80233830, 0, 0, 0, 0x150);
        }
    }
}

void func_80233830(void) {
    UnkStruct_80231274 *a;
    UnkStruct_80231274 *b;
    f32 pos[3];

    a = func_80231274(0x15, 0x01080010, 0xC0, NULL);
    a->unk40->unk36 = 0x7F;
    a->unkC = 0x40;
    b = func_80231274(0x2B1, 0x01780000, 0xD0, a);
    b->unk4C = -587.5f;
    b->unk50 = -250.0f;
    b->unk54 = -362.5f;
    b->unk40->unk30 = 0.25f;
    b->unk40->unk28 = b->unk40->unk2C = b->unk40->unk30;
    b->unk40->unk36 = a->unk40->unk36;
    func_80250338(func_80243DDC(), pos);
    pos[0] += 105.0f;
    func_80232BA0(pos, a);
    while (!(a->unk10 & 0x40)) {
        func_8023903C(4);
    }
    func_8028A7CC(0x12, pos, 0);
    func_8026C630(0xCE, pos);
    func_8027BA80(3, pos[0], pos[1], pos[2], 0, 1);
    func_8022FC90(a);
    func_80239430();
}
