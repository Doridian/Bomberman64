#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} UnkStruct_8027CE10_C;

/* A node of the list at D_80090440: [0] its head, [1] its sentinel, [2..49] the pool */
typedef struct UnkStruct_80090440 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ struct UnkStruct_80090440 *unk4;
    /* 0x08 */ struct UnkStruct_80090440 *unk8;
    /* 0x0C */ UnkStruct_8027CE10_C *unkC;
    /* 0x10 */ UnkStruct_8027CE10_C *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} UnkStruct_80090440; /* size 0x28 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
} UnkStruct_802B0190; /* size 0xC */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} UnkStruct_802B01B8; /* size 0x8 */

typedef struct {
    /* 0x00 */ u8 unk0[0x30];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ UnkStruct_8027CE10_C *unk40;
} UnkStruct_802B01D0;

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ u8 unk4[0xA];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10[0xC24];
} UnkStruct_800B15D8; /* size 0xC34 */

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_8023A840;

typedef struct {
    /* 0x00 */ u8 unk0[0x28];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
} UnkStruct_8023A834;

void func_8022946C(UnkStruct_8027CE10_C *, s32);
void func_8022FC90(UnkStruct_802B01D0 *);
void func_8022FF58(f32 *, f32 *, f32 *);
UnkStruct_802B01D0 *func_80231274(s32, s32, s32, s32);
void func_802313DC(UnkStruct_802B01D0 *, s32);
void func_80231408(UnkStruct_802B01D0 *, s32);
s32 func_80232D18(UnkStruct_802B01D0 *, s32);
s32 func_80234248(s32);
s32 func_80234768(void);
void func_802348B4(f32 *, f32 *, f32 *);
void func_80234900(f32 *, f32 *, f32 *);
s32 func_80238A10(void (*)(void), s32, s32, s32, s32);
void func_80238EA8(s32);
void func_8023903C(s32);
void func_80239094(void);
UnkStruct_8023A834 *func_8023A834(void);
UnkStruct_8023A840 *func_8023A840(void);
void func_8026C660(s32);
s32 func_8026D7D8(s32, s32, s32);
s32 func_8026DC74(s32);
void func_8026EEF0(s32, s32, s32, s32, s32);
s32 func_8026F068(s32, s32, s32, s32);
void func_8027404C(f32, f32, f32, f32 *, f32 *, f32 *);
void func_8027A640(void);
s32 func_8027B828(s16, s16, s16, s16);
s32 func_8027B8D4(s16, s16, s16, s16);
void func_8028A7CC(s32, f32 *, s32);

extern UnkStruct_80090440 D_80090440[50];
extern UnkStruct_80090440 D_80090468;
extern UnkStruct_800B15D8 D_800B15D8[];
extern s32 D_802AC5D0;
extern u8 *D_802AFE80;
extern s32 D_802AFE84;
extern s32 D_802B0180;
extern s32 D_802B0184;
extern s16 D_802B0188;
extern s16 D_802B018A;
extern s32 D_802B018C;
extern UnkStruct_802B0190 D_802B0190[3];
extern u8 D_802B01B4[4];
extern UnkStruct_802B01B8 D_802B01B8[3];
extern UnkStruct_802B01D0 *D_802B01D0;
extern s32 D_802B01D4;
extern void *D_802B01D8;
extern void *D_802B01DC;
extern void *D_802B01E0;
extern void *D_802B01E4;
extern void *D_802B01E8;
extern void *D_802B01EC;
extern UnkStruct_802B0190 D_802A1570[3];
extern UnkStruct_802B01B8 D_802A1594[3];
extern void *D_802A15AC[];

void func_8027CE10(UnkStruct_80090440 *arg0) {
    f32 b[3];
    f32 a[3];
    f32 c[3];
    f32 d[3];
    f32 pos[3];

    switch (func_80234768()) {
        case 0:
            func_802348B4(&a[0], &a[1], &a[2]);
            func_80234900(&b[0], &b[1], &b[2]);
            break;
        case 1:
            func_80234900(&a[0], &a[1], &a[2]);
            func_802348B4(&b[0], &b[1], &b[2]);
            break;
    }
    func_8022FF58(a, b, c);
    func_8027404C(arg0->unk1C, arg0->unk20, arg0->unk24, &pos[0], &pos[1], &pos[2]);
    func_8022FF58(b, pos, d);
    if (c[2] <= d[2]) {
        arg0->unkC->unkC |= 1;
        if (arg0->unk10 != NULL) {
            arg0->unk10->unkC |= 1;
        }
    } else {
        arg0->unkC->unkC &= ~1;
        if (arg0->unk10 != NULL) {
            arg0->unk10->unkC &= ~1;
        }
    }
}

s16 func_8027CF64(s32 arg0) {
    s16 ret;
    s32 kind = arg0 & 0x60;

    switch (kind) {
        case 0x20:
            ret = D_802B0190[0].unkA;
            break;
        case 0x40:
            ret = D_802B0190[1].unkA;
            break;
        case 0x60:
            ret = D_802B0190[2].unkA;
            break;
        default:
            ret = 0;
            if (kind) {}
            break;
    }
    return ret;
}

void func_8027CFC0(void) {
    UnkStruct_80090440 *node;

    if (D_80090440[0].unk4 != NULL) {
        node = D_80090440[0].unk4;
        while (node->unk4 != NULL) {
            node->unkC->unkC = func_8027CF64(node->unk1A);
            if (node->unkC->unkC & 0x80) {
                if (node->unkC->unk8 != 0x60) {
                    func_8022946C(node->unkC, 0x60);
                }
            } else if (node->unkC->unk8 != 0x40) {
                func_8022946C(node->unkC, 0x40);
            }
            func_8027CE10(node);
            func_8027404C(node->unk1C, node->unk20, node->unk24, &node->unkC->unk10, &node->unkC->unk14,
                          &node->unkC->unk18);
            if (node->unk10 != NULL) {
                node->unk10->unk10 = node->unkC->unk10;
                node->unk10->unk14 = node->unkC->unk14;
                node->unk10->unk18 = node->unkC->unk18;
            }
            node = node->unk4;
        }
    }
}

s32 func_8027D10C(void) {
    UnkStruct_80090440 *node;
    s32 n = 0;

    for (node = D_80090440[0].unk4; node->unk4 != NULL; node = node->unk4) {
        n++;
    }
    return n;
}

void func_8027D140(UnkStruct_80090440 *arg0) {
    s16 x;
    s16 y;
    s16 z;
    s16 nx;
    s16 ny;
    s16 nz;

    switch (arg0->unk14) {
        case 0:
            nz = 1;
            ny = 1;
            nx = 1;
            break;
        case 1:
            nz = 1;
            nx = 1;
            ny = 2;
            break;
        case 2:
            nz = 2;
            nx = 2;
            ny = 1;
            break;
        case 3:
            nz = 2;
            ny = 2;
            nx = 2;
            break;
    }
    for (y = 0; y < ny; y++) {
        for (z = 0; z < nz; z++) {
            for (x = 0; x < nx; x++) {
                func_8026EEF0(arg0->unk1C + x, arg0->unk20 + y, arg0->unk24 + z, 0x60, 0);
            }
        }
    }
}

void func_8027D328(UnkStruct_80090440 *arg0) {
    UnkStruct_80090440 *prev = arg0->unk8;
    UnkStruct_80090440 *next = arg0->unk4;

    prev->unk4 = next;
    next->unk8 = prev;
    arg0->unk2 = 1;
    func_8022A1E8(arg0->unkC);
    if (arg0->unk10 != NULL) {
        func_8022A1E8(arg0->unk10);
    }
    func_8027D140(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/97610/func_8027D398.s")

void func_8027D774(UnkStruct_80090440 *arg0, UnkStruct_80090440 *arg1) {
    UnkStruct_80090440 *prev = arg0->unk8;
    UnkStruct_80090440 *next = arg1->unk4;

    next->unk8 = arg1->unk8;
    arg1->unk8->unk4 = next;
    prev->unk4 = arg1;
    arg0->unk8 = arg1;
    arg1->unk4 = arg0;
    arg1->unk8 = prev;
}

void func_8027D7A4(UnkStruct_80090440 *arg0, UnkStruct_80090440 *arg1) {
    UnkStruct_80090440 *next = arg1->unk4;

    func_8027D774(arg0, arg1);
    func_8027D774(next, arg0);
}

void func_8027D7DC(void) {
    UnkStruct_80090440 *a;
    UnkStruct_80090440 *b;
    UnkStruct_80090440 *next;
    UnkStruct_80090440 *tmp;

    for (a = D_80090440[0].unk4; a->unk4 != NULL; a = a->unk4) {
        b = a->unk4;
        if (b->unk4 == NULL) {
            break;
        }
        do {
            if (a->unk16 < b->unk16) {
                next = b->unk4;
                func_8027D774(a, b);
                func_8027D774(next, a);
                tmp = a;
                a = b;
                b = tmp;
            }
            b = b->unk4;
        } while (b->unk4 != NULL);
    }
}

void func_8027D894(void) {
    UnkStruct_80090440 *node;
    s32 i;
    s16 n;
    s16 kind;
    s32 pad;
    f32 pos[3];

    if (D_80090440[0].unk4 != NULL) {
        func_8027D7DC();
        for (node = D_80090440[0].unk4; node->unk4 != NULL; node = node->unk4) {
            if (node->unk18 == 0) {
                node->unk16++;
            }
            node->unk18 = 0;
        }
        for (node = D_80090440[0].unk4, i = 0; node->unk4 != NULL; node = node->unk4, i++) {
            if (i >= 10) {
                break;
            }
            node->unk18 = 1;
            node->unk16 = 0;
            D_802B01D0->unk40->unk10 = node->unkC->unk10;
            D_802B01D0->unk40->unk14 = node->unkC->unk14;
            D_802B01D0->unk40->unk18 = node->unkC->unk18;
            func_80231408(D_802B01D0, 0x01000000);
            n = func_8026DC74(node->unk20);
            D_802B01D0->unk30 = 4;
            switch (node->unk14) {
                case 0:
                    D_802B01D0->unk34 = 50.0f;
                    D_802B01D0->unk38 = n * 100 - 10;
                    break;
                case 1:
                    D_802B01D0->unk34 = 50.0f;
                    D_802B01D0->unk38 = n * 200 - 10;
                    break;
                case 2:
                    D_802B01D0->unk34 = 100.0f;
                    D_802B01D0->unk38 = n * 100 - 10;
                    D_802B01D0->unk40->unk10 += 50.0f;
                    D_802B01D0->unk40->unk18 += 50.0f;
                    break;
                case 3:
                    D_802B01D0->unk34 = 100.0f;
                    D_802B01D0->unk38 = n * 200 - 10;
                    D_802B01D0->unk40->unk10 += 50.0f;
                    D_802B01D0->unk40->unk18 += 50.0f;
                    break;
            }
            switch (node->unk1A & 0x60) {
                case 0x20:
                    kind = 0;
                    break;
                case 0x40:
                    kind = 1;
                    break;
                case 0x60:
                    kind = 2;
                    break;
                default:
                    kind = 0;
                    break;
            }
            if (func_80232D18(D_802B01D0, 0xC0) != 0) {
                func_8027D398(node);
                func_8027D328(node);
                func_8027404C(node->unk1C, node->unk20, node->unk24, &pos[0], &pos[1], &pos[2]);
                pos[1] += 50;
                func_8028A7CC(D_802B0190[kind].unk6, pos, 0);
            }
            func_802313DC(D_802B01D0, 0x01000000);
        }
    }
}

void func_8027DCB8(void);
void func_8027DFAC(void);

void func_8027DCB8(void) {
    while (TRUE) {
        func_8027D894();
        if ((D_802AC5D0 & 4) && D_802B018A == 0 && func_8027D10C() == 0) {
            D_802B018A = 1;
            D_802B0184 = func_80238A10(func_8027DFAC, 0, 0, 0, 0x110);
            if (D_802B0184 == 0) {}
            if (D_802B0188) {}
        }
        func_8027CFC0();
        func_80239094();
    }
}

void func_8027DD94(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s16 arg5) {
    s16 x;
    s16 y;
    s16 z;
    s16 nx;
    s16 ny;
    s16 nz;

    switch (arg0) {
        case 0:
            nx = ny = nz = 1;
            break;
        case 1:
            nz = 1;
            nx = 1;
            ny = 2;
            break;
        case 2:
            nz = 2;
            nx = 2;
            ny = 1;
            break;
        case 3:
            nx = ny = nz = 2;
            break;
    }
    for (y = 0; y < ny; y++) {
        for (z = 0; z < nz; z++) {
            for (x = 0; x < nx; x++) {
                func_8026EEF0(arg1 + x, arg2 + y, arg3 + z, arg4, arg5);
            }
        }
    }
}

s16 func_8027DF40(s32 arg0) {
    s16 ret;
    s32 kind = arg0 & 0x60;

    switch (kind) {
        case 0x20:
            ret = D_802B0190[0].unk2;
            break;
        case 0x40:
            ret = D_802B0190[1].unk2;
            break;
        case 0x60:
            ret = D_802B0190[2].unk2;
            break;
        default:
            ret = 0;
            if (kind) {}
            break;
    }
    return ret;
}

s16 func_8027DF9C(void) {
    return D_802B0190[0].unk4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/97610/func_8027DFAC.s")

s16 func_8027E5F8(s32 arg0) {
    s16 ret;
    s32 kind = arg0 & 0x60;

    switch (kind) {
        case 0x20:
            ret = D_802B01B8[0].unk6;
            break;
        case 0x40:
            ret = D_802B01B8[1].unk6;
            break;
        case 0x60:
            ret = D_802B01B8[2].unk6;
            break;
        default:
            ret = 0;
            if (kind) {}
            break;
    }
    return ret;
}

void func_8027E654(UnkStruct_80090440 *arg0) {
    UnkStruct_80090440 *last = D_80090440[1].unk8;

    D_80090440[1].unk8 = arg0;
    last->unk4 = arg0;
    arg0->unk4 = &D_80090440[1];
    arg0->unk8 = last;
}

UnkStruct_80090440 *func_8027E67C(void) {
    UnkStruct_80090440 *node;
    UnkStruct_80090440 *end = &D_80090440[50];

    for (node = &D_80090440[2]; node < end; node++) {
        if (node->unk2 == 1) {
            return node;
        }
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/97610/func_8027E6C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/97610/func_8027E8EC.s")

void func_8027EB1C(UnkStruct_802B01B8 *arg0) {
    UnkStruct_802B01B8 *p = D_802B01B8;
    s16 i;

    for (i = 0; i < 3; i++) {
        p->unk0 = arg0->unk0;
        *(s32 *)&p->unk4 = *(s32 *)&arg0->unk4;
        arg0++;
        p++;
    }
}

void func_8027EB5C(UnkStruct_802B0190 *arg0) {
    UnkStruct_802B0190 *p = D_802B0190;
    s16 i;

    for (i = 0; i < 3; i++) {
        p->unk0 = arg0->unk0;
        p->unk2 = arg0->unk2;
        p->unk4 = arg0->unk4;
        p->unk6 = arg0->unk6;
        *(s32 *)&p->unk8 = *(s32 *)&arg0->unk8;
        arg0++;
        p++;
    }
    func_8027A640();
}

void func_8027EBCC(void) {
    UnkStruct_80090440 *node;

    if (D_802B0188 != 0) {
        D_802B0188 = 0;
        D_802B018A = 0;
        D_802B01D4 = 0;
        for (node = D_80090440[0].unk4; node->unk4 != NULL; node = node->unk4) {
            func_8027D328(node);
        }
        if (D_802B0190[0].unk0 != 0) {
            func_8026CCBC(D_802B0190[0].unk0);
        }
        if (D_802B0190[1].unk0 != 0) {
            func_8026CCBC(D_802B0190[1].unk0);
        }
        if (D_802B0190[2].unk0 != 0) {
            func_8026CCBC(D_802B0190[2].unk0);
        }
        if (D_802B01B8[0].unk0 != 0) {
            func_8026CCBC(D_802B01B8[0].unk0);
        }
        if (D_802B01B8[1].unk0 != 0) {
            func_8026CCBC(D_802B01B8[1].unk0);
        }
        if (D_802B01B8[2].unk0 != 0) {
            func_8026CCBC(D_802B01B8[2].unk0);
        }
        func_8022FC90(D_802B01D0);
        func_80238EA8(D_802B0180);
        func_8027EB5C(D_802A1570);
        func_8027EB1C(D_802A1594);
    }
}

void func_8027ED1C(void) {
    func_80297D30(0x23, D_802A15AC);
    D_802B0188 = 0;
    D_802B018A = 0;
    D_802B018C = 300;
    D_802B01D4 = 0;
    func_8027EB5C(D_802A1570);
    func_8027EB1C(D_802A1594);
}

UnkStruct_80090440 *func_8027ED80(void) {
    return D_80090440[0].unk4;
}

void func_8027ED90(s16 arg0, s16 arg1, s16 arg2) {
    D_802B0190[0].unk2 = arg0;
    D_802B0190[1].unk2 = arg1;
    D_802B0190[2].unk2 = arg2;
}
