#include "common.h"

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl12_02_800451B0;

void func_ovl12_02_80043840(UnkStructA *);
void func_ovl12_02_80043900(UnkStructA *);
void func_ovl12_02_80043EA0(void (*)(UnkStructA *));
void func_ovl12_02_80043EF0(void (*)(UnkStructA *));
void func_ovl12_02_80043F78(void *);
s32 func_ovl12_02_80043F98(void);
void func_ovl12_02_80043FA0(s32, void *);
void func_ovl12_02_80043FB0(s32);
void func_ovl12_02_80043FB8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl12_02_80043FC8(void);
void func_ovl12_02_80044000(s32);
void func_ovl12_02_800445F8(f32, f32, f32);
void func_ovl12_02_80044618(f32, f32, f32);
void func_ovl12_02_80044620(f32 *, f32 *, f32 *);
void func_ovl12_02_80044660(s32);
void func_ovl12_02_800447C0(UnkStructA *, s32);
void func_ovl12_02_80044838(UnkStructA *);
void func_ovl12_02_80044928(s32);
void func_ovl12_02_80044950(void);
UnkStructA *func_ovl12_02_80044990(s32);
void func_ovl12_02_800449A0(UnkStructA *, s32);
void func_ovl12_02_80044B88(s32);
void func_ovl12_02_80044EB0(s32, f32, f32, f32);

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (the store into the first call's delay slot). */
#define UNK_MACRO_ovl12_02_800430B0() \
    D_ovl12_02_8004518C = func_ovl12_02_80043F98(); func_ovl12_02_80043F78(&D_ovl12_02_80045180); func_ovl12_02_80043FA0(D_ovl12_02_8004518C, D_ovl12_02_80045170)

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl12_02_80045110;

void func_ovl12_02_80043DB8(s32);
void func_ovl12_02_80043DD0(s32);
void func_ovl12_02_80043DF8(s32, s32, s32, s32, s32, s32);
void func_ovl12_02_80043EB0(s32, s32, s32);
void func_ovl12_02_80043F68(void);
void func_ovl12_02_80043F70(s32, s32, s32);
s32 func_ovl12_02_80043F80(s32, s32, s32, s32);
void func_ovl12_02_80043FB8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl12_02_80044068(void);
void func_ovl12_02_800444C0(UnkStructA_40 *, s32);
void func_ovl12_02_800444C8(UnkStructA_40 *, s32, s32, s32);
void func_ovl12_02_800447B8(UnkStructA *, s32);
UnkStructA *func_ovl12_02_80044800(s32, s32, f32, f32, f32);
void func_ovl12_02_80044928(s32);
void func_ovl12_02_80044C30(s32, s32, s32);
void func_ovl12_02_80044C70(u32 (*)[3]);
void func_ovl12_02_80044C88(u32 (*)[3]);
void func_ovl12_02_80044E18(s32, s32, s32);

/* The five stores are one line too: IDO orders them by line otherwise. */
#define UNK_MACRO_ovl12_02_800451B0(a, b, c, d, e) \
    D_ovl12_02_800451B0.unk0 = (a); D_ovl12_02_800451B0.unk4 = (b); D_ovl12_02_800451B0.unk8 = (c); D_ovl12_02_800451B0.unkC = (d); D_ovl12_02_800451B0.unk10 = (e)

/* .bss */
u8 D_ovl12_02_80045170[0x10];
Vec3f D_ovl12_02_80045180;
s32 D_ovl12_02_8004518C;
u8 D_ovl12_02_80045190[0x4]; /* split for alignment */
s32 D_ovl12_02_80045194;
s32 D_ovl12_02_80045198;
u8 D_ovl12_02_8004519C[0x4]; /* not referenced here */
Vec3f D_ovl12_02_800451A0;
u8 D_ovl12_02_800451AC[0x4]; /* not referenced here */
UnkStruct_ovl12_02_800451B0 D_ovl12_02_800451B0;

/* .data */
/* passed to func_ovl12_02_80044C70: three 12-byte records */
u32 D_ovl12_02_800450B0[][3] = {
    { 0x970000, 0xF, 0x2004 },
    { 0xCF0000, 0xE, 4 },
    { 0xD00003, 0xF, 4 },
};
/* passed to func_ovl12_02_80044C88 */
u32 D_ovl12_02_800450D4[][3] = {
    { 0x980000, 0x84, 0 },
    { 4, 0, 4 },
};
/* three 12-byte records, each passed to func_ovl12_02_80044E18 */
u32 D_ovl12_02_800450EC[][3] = {
    { 0, 0x21, 0xFF },
    { 1, 0x1F, 0xFD },
    { 2, 0x20, 0xFE },
};
UnkStruct_ovl12_02_80045110 D_ovl12_02_80045110 = { NULL, 1100.0f, 200.0f, 2300.0f };

void func_ovl12_02_80043010(void) {
}

void func_ovl12_02_80043018(void) {
}

void func_ovl12_02_80043020(void) {
    func_ovl12_02_80044000(1);
}

void func_ovl12_02_80043040(void) {
    func_ovl12_02_80044000(1);
}

void func_ovl12_02_80043060(void) {
}

void func_ovl12_02_80043068(void) {
    D_ovl12_02_8004518C = func_ovl12_02_80043F98();
    func_ovl12_02_80043F78(&D_ovl12_02_80045180);
    func_ovl12_02_80043FA0(D_ovl12_02_8004518C, D_ovl12_02_80045170);
}

void func_ovl12_02_800430B0(void) {
    UNK_MACRO_ovl12_02_800430B0();
}

void func_ovl12_02_800430F8(void) {
}

void func_ovl12_02_80043100(void) {
}

void func_ovl12_02_80043108(void) {
    func_ovl12_02_80043DF8(9, 1, 0x16, 9, 0x17, 0x1F);
    func_ovl12_02_80043DF8(0xA, 1, 0x16, 0xB, 0x17, 0x16);
    func_ovl12_02_80043DF8(5, 2, 0x16, 5, 0x17, 0x1F);
    func_ovl12_02_80043DF8(6, 2, 0x16, 9, 0x17, 0x16);
    func_ovl12_02_80043DF8(4, 3, 0x16, 0, 0x17, 0x16);
}

void func_ovl12_02_800431D4(void) {
    if (func_ovl12_02_80043F80(0xC, 0x16, 0xD, 0x17) != 0) {
        func_ovl12_02_80043108();
        func_ovl12_02_80043FB8(0xC0, 3, 4.0f, 5, 0, 1, 1);
        func_ovl12_02_80044068();
        func_ovl12_02_80044928(0x78);
        func_ovl12_02_80043EB0(0x78, 0x12, 4);
    }
}

void func_ovl12_02_80043258(void) {
    func_ovl12_02_80043FB8(D_ovl12_02_800451B0.unk4, 3, 4.0f, D_ovl12_02_800451B0.unk10, 0, 1, 1);
}

void func_ovl12_02_800432A0(void) {
    func_ovl12_02_80043258();
}

void func_ovl12_02_800432C0(f32 arg0) {
    f32 sp1C;

    func_ovl12_02_80044620(&sp1C, NULL, NULL);
    func_ovl12_02_80044618(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl12_02_80043308(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl12_02_80043FC8();
    switch (D_ovl12_02_800451B0.unk8) {
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
        func_ovl12_02_80044618(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl12_02_800451B0.unkC;
        func_ovl12_02_80044620(&sp1C, NULL, NULL);
        func_ovl12_02_80044618(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl12_02_80043FB0(D_ovl12_02_800451B0.unk4);
}

void func_ovl12_02_80043420(void) {
    func_ovl12_02_80043308();
}

void func_ovl12_02_80043440(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    D_ovl12_02_800451B0.unk0 = arg0;
    D_ovl12_02_800451B0.unk4 = arg1;
    D_ovl12_02_800451B0.unk8 = arg2;
    D_ovl12_02_800451B0.unkC = arg3;
    D_ovl12_02_800451B0.unk10 = arg4;
}

void func_ovl12_02_80043468(void) {
    func_ovl12_02_80043F70(0xD, 1, 0x16);
    UNK_MACRO_ovl12_02_800451B0(2, 0x40, 0x40, 0.0f, 1);
}

void func_ovl12_02_800434B8(void) {
    func_ovl12_02_80043F70(0xD, 1, 0x16);
    UNK_MACRO_ovl12_02_800451B0(1, 0x40, 0x40, 0.0f, 0);
}

void func_ovl12_02_80043504(void) {
    UnkStructA *obj;

    obj = func_ovl12_02_80044800(0x31E, 0xD0, D_ovl12_02_80045110.unk4, D_ovl12_02_80045110.unk8,
                                 D_ovl12_02_80045110.unkC);
    if (obj != NULL) {
        func_ovl12_02_800447B8(obj, 0x01080000);
        D_ovl12_02_80045110.unk0 = obj;
        obj->unk40->unk20 = 180.0f;
        obj->unk40->unkC |= 0x8000;
        func_ovl12_02_800444C0(obj->unk40, 2);
        func_ovl12_02_800444C8(obj->unk40, 0x31F, 0, 0);
        func_ovl12_02_800444C8(obj->unk40, 0x31F, 1, 1);
    }
}

void func_ovl12_02_800435C0(void) {
}

void func_ovl12_02_800435C8(void) {
    func_ovl12_02_80044B88(0x400);
    func_ovl12_02_80044B88(0x401);
    func_ovl12_02_80044B88(0x402);
    func_ovl12_02_80044B88(0x403);
    func_ovl12_02_80044B88(0x404);
}

void func_ovl12_02_80043608(void) {
    UnkStructA *obj;

    func_ovl12_02_800435C8();
    func_ovl12_02_80043EA0(func_ovl12_02_80043900);
    func_ovl12_02_80043EF0(func_ovl12_02_80043840);
    obj = func_ovl12_02_80044990(0x2E5);
    func_ovl12_02_800449A0(obj, 0x20000001);
    obj->unk18 = 0.03f;
    obj->unk1C = 0.0f;
}

void func_ovl12_02_80043674(void) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    func_ovl12_02_80043608();
    func_ovl12_02_80044C70(D_ovl12_02_800450B0);
    func_ovl12_02_80044C88(D_ovl12_02_800450D4);
    func_ovl12_02_80043DB8(0x2DA);
    p = D_ovl12_02_800450EC;
    count = 3;
    for (i = 0; i < count; i++) {
        func_ovl12_02_80044E18((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
    func_ovl12_02_80043DD0(0x2E0);
    func_ovl12_02_80043F68();
    func_ovl12_02_80043504();
    func_ovl12_02_80044C30(0, 0x72, 0x37);
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl12_02_80043720(s32 arg0) {
    switch (arg0) {
        case 1:
            break;
        case 2:
            func_ovl12_02_80043674();
            break;
        case 17:
            func_ovl12_02_800434B8();
            break;
        case 18:
            func_ovl12_02_80043468();
            break;
        case 4:
            func_ovl12_02_80043308();
            break;
        case 5:
            func_ovl12_02_80043258();
            break;
        case 0x50:
            func_ovl12_02_800431D4();
            break;
        case 3:
            UNK_MACRO_ovl12_02_800430B0();
            break;
        case 12:
            func_ovl12_02_80044000(1);
            break;
        case 0x52:
            break;
        case 0x53:
            break;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/overlays/ovl_12_02/24EA00/func_ovl12_02_80043840.s")

void func_ovl12_02_80043900(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl12_02_80044660(0x10);
    }
    func_ovl12_02_800447C0(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        func_ovl12_02_80044838(arg0);
        func_ovl12_02_80044950();
    }
}

void func_ovl12_02_80043978(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01: without it arg1 is spilled */
    }
    func_ovl12_02_80044EB0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl12_02_800439AC(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl12_02_800445F8(D_ovl12_02_800451A0.x, D_ovl12_02_800451A0.y, D_ovl12_02_800451A0.z);
    func_ovl12_02_80044618(arg0, arg1, arg2);
    func_ovl12_02_80044928(180);
}

void func_ovl12_02_80043A08(void) {
    D_ovl12_02_80045194 = -1;
    D_ovl12_02_80045198 = -1;
}

void func_ovl12_02_80043A20(void) {
}

void func_ovl12_02_80043A28(void) {
}

void func_ovl12_02_80043A30(void) {
}

void func_ovl12_02_80043A38(void) {
}

void func_ovl12_02_80043A40(void) {
}

void func_ovl12_02_80043A48(void) {
}

void func_ovl12_02_80043A50(void) {
}

void func_ovl12_02_80043A58(void) {
}

void func_ovl12_02_80043A60(void) {
}

void func_ovl12_02_80043A68(void) {
}
