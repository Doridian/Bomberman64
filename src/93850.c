#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} UnkStruct_80279050_10;

typedef struct {
    /* 0x00 */ u8 unk0[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[0x34];
    /* 0x40 */ UnkStruct_80279050_10 *unk40;
    /* 0x44 */ u8 unk44[0x14];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} UnkStruct_80279050_14;

/* A node of the list at D_800BB4A8; the last node is a sentinel */
typedef struct UnkStruct_800BB4A8 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ struct UnkStruct_800BB4A8 *unk8;
    /* 0x0C */ struct UnkStruct_800BB4A8 *unkC;
    /* 0x10 */ UnkStruct_80279050_10 *unk10;
    /* 0x14 */ UnkStruct_80279050_14 *unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 unk4A[6];
    /* 0x50 */ f32 unk50;
    /* 0x54 */ s32 unk54;
} UnkStruct_800BB4A8;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_802AFED0; /* size 0x1C */

typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 unk24[0xA4];
} UnkStruct_800AEDF0; /* size 0xC8 */

typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
} UnkStruct_8023A840;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStruct_80279050_14 *unk4;
    /* 0x08 */ UnkStruct_80279050_14 *unk8;
    /* 0x0C */ UnkStruct_80279050_14 *unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} UnkStruct_8027A264; /* size 0x3C */

void func_8022FC90(UnkStruct_80279050_14 *);
void func_802313DC(UnkStruct_80279050_14 *, s32);
void func_80231408(UnkStruct_80279050_14 *, s32);
UnkStruct_80279050_14 *func_802308B8(UnkStruct_80279050_14 *, s32);
s32 func_80234248(s32);
void func_80239094(void);
UnkStruct_8023A840 *func_8023A840(void);
void func_8024694C(s32, s32, s32);
void func_80246C3C(s32, s32, s32);
void func_80246D74(s32);
void func_80246F00(s32, s32);
void func_80248864(s32);
void func_802488C0(s32);
void func_802502BC(s32);
void func_8026C660(s32);
f32 func_8026E8B8(void);
void func_80270354(s32 *, s32);
void func_8027036C(s32 *, s32);
s32 func_802712A8(s32 *, s32);
s32 func_80272024(s16);
void func_802727D8(s32);
void func_802733C8(UnkStruct_80279050_14 *);
void func_80277D60(s32, s32);
s32 func_8027B480(s32 arg0);
void *malloc(s32);
void free(void *);
s16 func_8026FFA0(s16);
void func_80270080(UnkStruct_8027A264 *);
void func_80277DA8(s16, s32);
UnkStruct_80279050_14 *func_802443F4(s32);
UnkStruct_800BB4A8 *func_8027AA74(s16, f32, f32, f32, s32, s32, s32);
f32 func_80234434(f32);
void func_8027A950(void);
void func_8028A81C(s32, f32, f32, f32, s32);
void func_8029217C(UnkStruct_80279050_14 *, s32, f32, void (*)());

void func_802790E0(UnkStruct_800BB4A8 *arg0);
void func_802797BC(UnkStruct_80279050_14 *arg0, UnkStruct_800BB4A8 *arg1);
void func_80279CA8(void);
void func_80279D40(UnkStruct_800BB4A8 *arg0);
s32 func_80279DC8(UnkStruct_800BB4A8 *arg0, f32 arg1);
void func_80279F30(void);
UnkStruct_800BB4A8 *func_8027A1A0(UnkStruct_80279050_14 *arg0);

extern UnkStruct_800BB4A8 *D_800BB4A8;
extern UnkStruct_802AFED0 D_802AFED0[];
extern UnkStruct_800AEDF0 D_800AEDF0[];
extern UnkStruct_800BB4A8 D_800BB4A0[]; /* [0] the list's head, [1] its sentinel, [2..47] the pool */
extern s16 D_802AFF60[];

void func_80279628(s16 arg0, s16 arg1);
void func_80279050(void) {
    UnkStruct_800BB4A8 *node;

    if (D_800BB4A8 != NULL) {
        node = D_800BB4A8;
        while (node->unk8 != NULL) {
            if (func_802712A8(&node->unk54, 2) == 0) {
                node->unk10->unk10 = node->unk24;
                node->unk10->unk14 = node->unk28;
                node->unk10->unk18 = node->unk2C;
            }
            node = node->unk8;
        }
    }
}

void func_802790E0(UnkStruct_800BB4A8 *arg0) {
    UnkStruct_800BB4A8 *prev = arg0->unkC;
    UnkStruct_800BB4A8 *next = arg0->unk8;

    prev->unk8 = next;
    next->unkC = prev;
    arg0->unk2 = 1;
    func_8022FC90(arg0->unk14);
}

s32 func_8027911C(s16 arg0) {
    if (arg0 >= 9 && arg0 < 0x39) {
        return 9;
    }
    if (arg0 >= 0x39 && arg0 < 0x3F) {
        return 0x39;
    }
    if (arg0 >= 0x3F && arg0 < 0x45) {
        return 0x3F;
    }
    if (arg0 >= 0x45 && arg0 < 0x4B) {
        return 0x45;
    }
    if (arg0 >= 0x4B && arg0 < 0x51) {
        return 0x4B;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_802791C4.s")

void func_802794FC(s16 arg0) {
    UnkStruct_8023A840 *p = func_8023A840();

    p->unk1C += arg0;
    if (p->unk1C >= 50) {
        func_8026C660(0x24);
        p->unk18++;
        p->unk1C -= 50;
    }
}

void func_80279560(void) {
    switch (func_80234248(6)) {
        case 0:
            func_80246F00(2, 1);
            break;
        case 1:
            func_80246F00(4, 1);
            break;
        case 2:
            func_80246F00(8, 1);
            break;
        case 3:
            func_80246F00(0x10, 1);
            break;
        case 4:
            func_80246F00(0x20, 1);
            break;
        case 5:
            func_80246F00(0x40, 1);
            break;
        case 6:
            func_80246F00(0x80, 1);
            break;
    }
}

void func_80279628(s16 arg0, s16 arg1) {
    D_802AFED0[arg0].unk4 = arg0;
    D_802AFED0[arg0].unk8 = arg1;
    D_802AFED0[arg0].unkC = 1200;
    D_802AFED0[arg0].unk10 = D_800AEDF0[arg0].unk18;
    D_802AFED0[arg0].unk14 = D_800AEDF0[arg0].unk1C;
    D_802AFED0[arg0].unk18 = D_800AEDF0[arg0].unk20;
    func_80246D74(arg0);
    switch (arg1) {
        case 0:
            func_8024694C(arg0, 2, 1);
            break;
        case 1:
            func_8024694C(arg0, 1, 1);
            break;
        case 2:
            func_802488C0(arg0);
            break;
        case 3:
            func_80277D60(arg0, 0x400);
            func_80246C3C(arg0, 3, 1);
            break;
        case 4:
            func_80248864(arg0);
            break;
        case 5:
            func_802502BC(arg0);
            break;
        case 6:
            func_80277D60(arg0, 4);
            func_80246C3C(arg0, 3, 1);
            break;
        default:
            break;
    }
}

void func_80279780(s16 arg0, s32 arg1) {
    func_80279628(arg0, func_80234248(6));
}

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_802797BC.s")

void func_80279CA8(void) {
    UnkStruct_800BB4A8 *node;
    UnkStruct_80279050_14 *obj;

    if (D_800BB4A8 != NULL) {
        node = D_800BB4A8;
        while (node->unk8 != NULL) {
            node->unk1E = 1;
            node->unk1C = 0;
            if (func_802712A8(&node->unk54, 2) == 0) {
                obj = func_802308B8(node->unk14, 1);
                if (obj != NULL) {
                    func_802797BC(obj, node);
                    func_802790E0(node);
                }
            }
            node = node->unk8;
        }
    }
}

void func_80279D40(UnkStruct_800BB4A8 *arg0) {
    s32 below;

    if (arg0->unk28 <= func_8026E8B8()) {
        below = TRUE;
    } else {
        below = FALSE;
    }
    if (below) {
        func_8028A81C(12, arg0->unk24, arg0->unk28 + 100.0f, arg0->unk2C, 0);
        func_802313DC(arg0->unk14, 0x0103FFFF);
        func_80239094();
        func_802790E0(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_80279DC8.s")

void func_80279F10(UnkStruct_800BB4A8 *arg0) {
    func_802790E0(arg0);
}

void func_80279F30(void) {
    UnkStruct_800BB4A8 *node = D_800BB4A8;
    s32 *flags;
    s16 i;

    while (node->unk8 != NULL) {
        flags = &node->unk54;
        if (func_802712A8(flags, 8)) {
            node->unk48--;
        }
        if (node->unk48 < 60 && !func_802712A8(flags, 0x10)) {
            func_80270354(flags, 0x10);
            func_80231408(node->unk14, 0x40000);
        }
        if (node->unk48 > 60 && func_802712A8(flags, 0x10)) {
            func_8027036C(flags, 0x10);
            func_802313DC(node->unk14, 0x40000);
        }
        if (node->unk48 == 0) {
            func_802790E0(node);
        } else {
            node->unk24 = node->unk10->unk10;
            node->unk28 = node->unk10->unk14;
            node->unk2C = node->unk10->unk18;
            if (func_802712A8(flags, 2) || func_802712A8(flags, 1)) {
                if (func_802712A8(flags, 2)) {
                    func_802733C8(node->unk14);
                } else {
                    func_802727D8(node->unk18);
                    node->unk24 = node->unk10->unk10;
                    node->unk28 = node->unk10->unk14;
                    node->unk2C = node->unk10->unk18;
                }
            } else if (!func_80279DC8(node, 1.0f)) {
                for (i = 0; i < 7; i += 2) {
                    node->unk30 = i;
                    if (func_80279DC8(node, 1.0f)) {
                        break;
                    }
                }
            }
            func_80279D40(node);
        }
        node = node->unk8;
    }
}

void func_8027A144(void) {
    while (TRUE) {
        func_80279F30();
        func_80279CA8();
        func_80279050();
        func_80239094();
    }
}

UnkStruct_800BB4A8 *func_8027A1A0(UnkStruct_80279050_14 *arg0) {
    UnkStruct_800BB4A8 *node = D_800BB4A8;

    while (node->unk8 != NULL) {
        if (arg0 == node->unk14) {
            return node;
        }
        node = node->unk8;
    }
    return NULL;
}

s32 func_8027A1F4(UnkStruct_80279050_14 *arg0, s32 arg1) {
    UnkStruct_800BB4A8 *node = func_8027A1A0(arg0);

    func_80231408(arg0, 0x20000);
    func_8027036C(&node->unk54, 2);
    func_80270354(&node->unk54, 8);
    node->unk18 = arg1;
    func_80270354(&node->unk54, 1);
    return 1;
}

void func_8027A264(UnkStruct_800BB4A8 *arg0, s16 arg1) {
    UnkStruct_80279050_14 *obj = arg0->unk14;
    UnkStruct_8027A264 *ptr;

    if (!(obj->unk8 & 0x20000)) {
        ptr = malloc(sizeof(UnkStruct_8027A264));
        ptr->unk4 = obj;
        ptr->unk14 = func_8026FFA0(arg1);
        ptr->unk18 = 25.0f;
        ptr->unk1C = 7.7f;
        ptr->unk20 = 1;
        ptr->unk24 = 0.0f;
        ptr->unk28 = 0;
        ptr->unk2C = 10000.0f;
        ptr->unk30 = 0;
        ptr->unk34 = obj->unk40->unk10;
        ptr->unk38 = obj->unk40->unk18;
        obj->unk68 = 25.0f;
        obj->unk6C = 1.0f;
        ptr->unk10 = obj->unk8;
        if (func_8027A1F4(obj, (s32)ptr)) {
            func_80270080(ptr);
            func_80270354(&arg0->unk54, 0x20);
            func_80231408(obj, 0x20000);
            ptr->unk8 = obj;
            ptr->unkC = obj;
        } else {
            free(ptr);
        }
    }
}

void func_8027A380(s16 arg0) {
    switch (arg0) {
        case 0:
            D_802AFF60[0]++;
            break;
        case 1:
            D_802AFF60[1]++;
            break;
        case 2:
            D_802AFF60[2]++;
            break;
        case 3:
            D_802AFF60[3]++;
            break;
        case 4:
            D_802AFF60[4]++;
            break;
        case 5:
            D_802AFF60[5]++;
            break;
        case 6:
            D_802AFF60[6]++;
            break;
        default:
            break;
    }
}

void func_8027A478(UnkStruct_800BB4A8 *arg0) {
    UnkStruct_800BB4A8 *last = D_800BB4A0[1].unkC;

    D_800BB4A0[1].unkC = arg0;
    last->unk8 = arg0;
    arg0->unk8 = &D_800BB4A0[1];
    arg0->unkC = last;
}

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027A4A0.s")

s16 func_8027A4E8(s16 arg0) {
    s32 temp = func_8027911C(arg0);
    s16 ret = temp;

    switch (temp) {
        case 9:
            ret = 0x19;
            break;
        case 0x39:
            ret = 0x1A;
            break;
        case 0x3F:
            ret = 0x1B;
            break;
        case 0x45:
            ret = 0x1C;
            break;
        case 0x4B:
            ret = 0x1D;
            break;
        default:
            break;
    }
    return ret;
}

s16 func_8027A574(s16 arg0) {
    s16 ret;

    switch (arg0) {
        case 0:
            ret = 8 - D_802AFF60[0];
            break;
        case 1:
            ret = 12 - D_802AFF60[1];
            break;
        case 2:
            ret = 4 - D_802AFF60[2];
            break;
        case 4:
            ret = 3 - D_802AFF60[4];
            break;
        case 5:
            ret = 7 - D_802AFF60[5];
            break;
        case 6:
            ret = 1 - D_802AFF60[6];
            break;
        default:
            break;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027A640.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027A950.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027AA74.s")

s16 func_8027AF70(void) {
    UnkStruct_800BB4A8 *node;
    s16 count;

    func_8027A950();
    count = 0;
    node = D_800BB4A8;
    while (node->unk8 != NULL) {
        node = node->unk8;
        count++;
    }
    return count;
}

void func_8027AFB8(s16 arg0) {
    s16 state = ((s16 *)&D_802AFED0[arg0].unk8)[1]; /* read as the s16 at 0xA */

    switch (state) {
        case 3:
            func_80246C3C(arg0, 0, 0);
            func_80277DA8(arg0, 0x400);
            func_80246D74(arg0);
            break;
        case 6:
            func_80246C3C(arg0, 0, 0);
            func_80277DA8(arg0, 4);
            func_80246D74(arg0);
            break;
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
            break;
        default:
            return;
    }
    D_802AFED0[arg0].unk8 = -1;
}

s32 func_8027B094(s16 arg0) {
    return D_802AFED0[arg0].unk8;
}

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027B0BC.s")

void func_8027B39C(s16 arg0, s16 arg1) {
    UnkStruct_80279050_14 *obj;
    UnkStruct_80279050_10 *pos;
    UnkStruct_800BB4A8 *node;

    obj = func_802443F4(arg1);
    pos = obj->unk40;
    node = func_8027AA74(arg0, pos->unk10, pos->unk14 + 200.0f, pos->unk18, 1, 0, 0);
    if (node != NULL) {
        func_80270354(&node->unk54, 2);
        func_8027A264(node, func_80272024(func_80234248(7)));
    }
}

void func_8027B440(UnkStruct_80279050_14 *arg0) {
    UnkStruct_800BB4A8 *node = func_8027A1A0(arg0);

    if (node) {} /* fake (permuter): without it the registers come out swapped */
    func_8027036C(&node->unk54, 1);
    node->unk3C = 0.0f;
}

s32 func_8027B480(s32 arg0) {
    s32 ret;

    if ((arg0 & 0xF) == 0xF) {
        ret = 0;
    } else {
        ret = 1;
    }
    if (arg0 & 0x60) {
        ret = 0;
    }
    return ret;
}

void func_8027B4B0(s16 arg0) {
    UnkStruct_800BB4A8 *node = &D_800BB4A0[arg0];
    f32 f;

    node->unk24 += node->unk38;
    node->unk2C -= node->unk40;
    f = func_80234434(node->unk3C) * 150.0;
    node->unk28 += f - node->unk44;
    node->unk44 = f;
    node->unk3C += 4.5;
    node->unk50 -= 1.0f;
    if (node->unk50 == 0.0f) {
        func_80270354(&node->unk54, 2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027B5A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027B66C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027B6A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027B6D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027B70C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027B7C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027B828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027B8D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027BA80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027BAE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027BB48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027BB9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027BBC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027BC74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027BCD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/93850/func_8027BCE8.s")
