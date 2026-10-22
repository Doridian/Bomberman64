#include "common.h"

void func_ovl0F_06_80043598(s32);
void func_ovl0F_06_800435B0(s32);
void func_ovl0F_06_80043748(void);
void func_ovl0F_06_80043750(s32, s32, s32);
void func_ovl0F_06_800437A8(void);
void func_ovl0F_06_80043DD8(f32, f32, f32);
void func_ovl0F_06_80043DF8(f32, f32, f32);
void func_ovl0F_06_80043E00(f32 *, f32 *, f32 *);
void func_ovl0F_06_80044108(s32);
void func_ovl0F_06_800445F8(s32, s32, s32);
void func_ovl0F_06_80044690(s32, f32, f32, f32);

/* .bss, in first-seen order (docs/DECOMPILING.md, "Data") */
u8 D_ovl0F_06_80044940[0x24]; /* not referenced here */
s32 D_ovl0F_06_80044964;
s32 D_ovl0F_06_80044968;
u8 D_ovl0F_06_8004496C[4]; /* not referenced here */
Vec3f D_ovl0F_06_80044970;

/* .data: six 12-byte records, each passed to func_ovl0F_06_800445F8 */
u32 D_ovl0F_06_80044890[][3] = {
    { 0, 0x12, 0xF0 },
    { 1, 0x13, 0xF1 },
    { 2, 0x16, 0xF4 },
    { 3, 0, 0xDE },
    { 4, 2, 0xE0 },
    { 5, 0x15, 0xF3 },
};

void func_ovl0F_06_80043010(void) {
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_06_80043018(s32 arg0) {
    u32 (*p)[3];
    s32 i;
    s32 count;

    switch (arg0) {
        case 1:
            break;
        case 2:
            /* the count in a variable: with a literal 6, IDO compares the
             * pointer against the table's end instead of i with slt */
            p = D_ovl0F_06_80044890;
            count = 6;
            for (i = 0; i < count; i++) {
                func_ovl0F_06_800445F8((*p)[0], (*p)[1], (*p)[2]);
                p++;
            }
            func_ovl0F_06_80043598(0x229);
            func_ovl0F_06_800435B0(0x23C);
            func_ovl0F_06_80043748();
            break;
        case 3:
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
            break;
        case 22:
            func_ovl0F_06_80043750(0x1E, 1, 0xE);
            break;
        case 4:
            func_ovl0F_06_800437A8();
            break;
        case 0x50:
            break;
    }
}

void func_ovl0F_06_800430FC(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_09_01: without it arg1 is spilled */
    }
    func_ovl0F_06_80044690(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0F_06_80043130(f32 arg0) {
    f32 sp1C;

    func_ovl0F_06_80043E00(&sp1C, NULL, NULL);
    func_ovl0F_06_80043DF8(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0F_06_80043178(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_06_80043DD8(D_ovl0F_06_80044970.x, D_ovl0F_06_80044970.y, D_ovl0F_06_80044970.z);
    func_ovl0F_06_80043DF8(arg0, arg1, arg2);
    func_ovl0F_06_80044108(0xB4);
}

void func_ovl0F_06_800431D4(void) {
    D_ovl0F_06_80044964 = -1;
    D_ovl0F_06_80044968 = -1;
}

void func_ovl0F_06_800431EC(void) {
}

void func_ovl0F_06_800431F4(void) {
}

void func_ovl0F_06_800431FC(void) {
}

void func_ovl0F_06_80043204(void) {
}

void func_ovl0F_06_8004320C(void) {
}

void func_ovl0F_06_80043214(void) {
}

void func_ovl0F_06_8004321C(void) {
}

void func_ovl0F_06_80043224(void) {
}

void func_ovl0F_06_8004322C(void) {
}

void func_ovl0F_06_80043234(void) {
}

void func_ovl0F_06_8004323C(void) {
}
