#include "common.h"

/* A thread of the game's cooperative scheduler: setjmp/longjmp
 * (func_80297C10/func_80297C7C) switch between them. */
typedef struct UnkStruct_802AB200 {
    /* 0x000 */ u16 unk0;
    /* 0x002 */ u16 unk2;
    /* 0x004 */ s32 unk4;
    /* 0x008 */ u32 unk8;
    /* 0x00C */ s32 unkC;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ s64 unk18;
    /* 0x020 */ s32 unk20;
    /* 0x024 */ u8 *unk24;
    /* 0x028 */ u8 unk28[0x800];
    /* 0x828 */ s32 unk828[28];
    /* 0x898 */ struct UnkStruct_802AB200 *unk898;
    /* 0x89C */ struct UnkStruct_802AB200 *unk89C;
} UnkStruct_802AB200; /* size 0x8A0 */

/* func_80297C10 and func_80297C7C are setjmp and longjmp (hand-written,
 * B2410).  setjmp's result is unsigned: as s32 or int, func_802392F8's
 * switch compares with registers holding 1 and 2 instead of `at`. */
u32 func_80297C10(s32 *);
void func_80297C7C(s32 *, s32);
void func_80297D30(s32, void *);
void func_80297D38(const char *, ...);
s32 func_80297D90(s32, s32, s32);

void func_802388C0(void);
void func_802388E8(UnkStruct_802AB200 *arg0, UnkStruct_802AB200 *arg1);
UnkStruct_802AB200 *func_80238918(u16 arg0);
void func_8023897C(UnkStruct_802AB200 *arg0);
void func_80238994(UnkStruct_802AB200 *arg0);
UnkStruct_802AB200 *func_802389D4(void);
s32 func_80238A10(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, u16 arg4);
s32 func_80238B9C(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, u16 arg4);
s32 func_80238BDC(void);
UnkStruct_802AB200 *func_80238C08(u16 arg0);
s32 func_80238C68(u16 arg0);
s32 func_80238CF8(s32 arg0, s32 arg1);
s32 func_80238D98(u16 arg0, u32 arg1);
s32 func_80238DFC(s32 arg0, s32 arg1, u32 arg2);
s32 func_80238EA8(s32 arg0);
s32 func_80238F40(s32 arg0, s32 arg1);
s32 func_80238FDC(void);
s32 func_80238FF4(s32 arg0);
s32 func_8023903C(u32 arg0);
void func_80239094(void);
void func_802390B4(void);
s32 func_802390F0(s32 arg0, s32 arg1, s32 arg2);
s32 func_802391A4(void);
s32 func_802391F0(void);
s32 func_80239208(UnkStruct_802AB200 *arg0);
void func_80239430(void);

extern UnkStruct_802AB200 D_80063370[80];
/* D_802AB200 and D_802ABAA0 are the list heads (running and free); the
 * asm's D_802ABA9C and D_802AC33C are their unk89C. */
extern UnkStruct_802AB200 D_802AB200;
extern UnkStruct_802AB200 D_802ABAA0;
extern UnkStruct_802AB200 *D_802AC340;
extern UnkStruct_802AB200 *D_802AC344;
extern UnkStruct_802AB200 *D_802AC348;
extern u32 D_802AC34C;
extern u32 D_802AC350;
extern u32 D_802AC354;
extern s32 D_802AC358;
extern s32 D_802AC35C;
extern s32 D_802AC360;
extern s32 D_802AC368[];

void func_8023946C(void) {
    s32 i;
    UnkStruct_802AB200 *t;

    D_802AC358 = 0;
    D_802AC35C = 0;
    D_802AC360 = 0;
    D_802AC340 = NULL;
    D_802AC344 = NULL;
    D_802AB200.unk0 = 0x51;
    func_8023897C(&D_802AB200);
    D_802ABAA0.unk0 = 0x52;
    func_8023897C(&D_802ABAA0);
    t = D_80063370;
    for (i = 0; i < 80; i++) {
        t->unk0 = i;
        t->unk18 = i;
        func_8023897C(t);
        t++;
    }
    func_802388E8(&D_802ABAA0, D_80063370);
    t = D_80063370;
    for (i = 0; i < 79; i++) {
        func_802388E8(t, t + 1);
        t++;
    }
    func_802388C0();
}

void func_80239430(void) {
    func_80238EA8(D_802AC344->unk0);
    func_80297C7C(D_802AC368, 1);
}

void func_802392F8(void) {
    UnkStruct_802AB200 *t;
    s32 ret;

    D_802AC35C = 1;
    for (t = D_802AB200.unk89C; t != NULL; t = t->unk89C) {
        if (t->unk4 == 2) {
            if (D_802AC35C < t->unk8) {
                t->unk8 -= D_802AC35C;
            } else {
                t->unk8 = 0;
                t->unk4 = 1;
            }
        }
    }
    D_802AC344 = &D_802AB200;
    D_802AC348 = NULL;
    switch (func_80297C10(D_802AC368)) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            ret = func_80239208(D_802AC344);
            if (ret == 0) {
                ret = -1;
            }
            func_80297C7C(D_802AC344->unk828, ret);
            break;
    }
    D_802AC348 = D_802AC344;
    D_802AC344 = D_802AC344->unk89C;
    if (D_802AC344 != NULL) {
        if (D_802AC344->unk4 == 1) {
            func_80297C7C(D_802AC344->unk828, 1);
        } else {
            func_80297C7C(D_802AC368, 1);
        }
    }
}

s32 func_80239208(UnkStruct_802AB200 *arg0) {
    u32 sp;
    u32 sptop;
    u32 spbtm;
    u32 mask = 0x7FFFFFFF;

    sp = arg0->unk828[2] & mask;
    sptop = (u32)arg0->unk24 & mask;
    spbtm = arg0->unk20 + sptop;

    func_80297D38("id    : %d\n", arg0->unk0);
    func_80297D38("pri   : %d\n", arg0->unk2);
    func_80297D38("func  : %08lx\n", arg0->unkC);
    func_80297D38("sp    : %08lx\n", sp);
    func_80297D38("sptop : %08lx\n", sptop);
    func_80297D38("spbtm : %08lx\n", spbtm);
    D_802AC34C = sptop;
    D_802AC350 = spbtm;
    D_802AC354 = sp;
    if (spbtm < sp || sp < sptop) {
        return -1;
    }
    return sp - sptop;
}

s32 func_802391F0(void) {
    return D_802AC344->unk10;
}

s32 func_802391A4(void) {
    s32 ret = func_80297C10(D_802AC344->unk828);

    if (ret == 0) {
        func_80297C7C(D_802AC368, 2);
    }
    return ret;
}

s32 func_802390F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 ret;

    if (arg2 != 1) {
        return func_80297D90(arg0, arg1, 0);
    }
    ret = func_80297D90(arg0, arg1, 0);
    while (ret != 0) {
        if (func_80297C10(D_802AC344->unk828) == 0) {
            func_80297C7C(D_802AC368, 1);
        }
        ret = func_80297D90(arg0, arg1, 0);
    }
    return ret;
}

void func_802390B4(void) {
    if (func_80297C10(D_802AC344->unk828) == 0) {
        func_80297C7C(D_802AC368, 1);
    }
}

void func_80239094(void) {
    func_8023903C(1);
}

s32 func_8023903C(u32 arg0) {
    s32 ret = func_80238D98(D_802AC344->unk0, arg0);

    if (func_80297C10(D_802AC344->unk828) == 0) {
        func_80297C7C(D_802AC368, 1);
    }
    return ret;
}

s32 func_80238FF4(s32 arg0) {
    UnkStruct_802AB200 *t;

    for (t = D_802AB200.unk89C; t != NULL; t = t->unk89C) {
        if (arg0 == t->unk0) {
            return t->unk2;
        }
    }
    return -1;
}

s32 func_80238FDC(void) {
    return D_802AC344->unk2;
}

s32 func_80238F40(s32 arg0, s32 arg1) {
    UnkStruct_802AB200 *t;
    s32 n = 0;

    for (t = D_802AB200.unk89C; t != NULL; t = t->unk89C) {
        if (t->unk2 >= arg0 && t->unk2 <= arg1) {
            t = t->unk898;
            func_80238EA8(t->unk89C->unk0);
            n++;
        }
    }
    return n;
}

s32 func_80238EA8(s32 arg0) {
    UnkStruct_802AB200 *t = func_80238C08(arg0);
    UnkStruct_802AB200 *prev;

    if (t == NULL) {
        while (1) {}
    }
    prev = t->unk898;
    t->unk4 = 0;
    func_80238994(t);
    func_802388E8(&D_802ABAA0, t);
    D_802AC358--;
    if (t == D_802AC344) {
        D_802AC344 = prev;
        func_80297C7C(D_802AC368, 1);
    }
    return t->unk0;
}

s32 func_80238DFC(s32 arg0, s32 arg1, u32 arg2) {
    UnkStruct_802AB200 *t;
    s32 n = 0;

    for (t = D_802AB200.unk89C; t != NULL; t = t->unk89C) {
        if (t->unk2 >= arg0 && t->unk2 <= arg1) {
            t = t->unk898;
            func_80238D98(t->unk89C->unk0, arg2);
            t = t->unk89C;
            n++;
        }
    }
    return n;
}

s32 func_80238D98(u16 arg0, u32 arg1) {
    UnkStruct_802AB200 *t = func_80238C08(arg0);

    if (t == NULL) {
        return -1;
    }
    if (arg1 != 0) {
        t->unk4 = 2;
        t->unk8 = arg1;
    } else {
        t->unk4 = 3;
    }
    return t->unk0;
}

s32 func_80238CF8(s32 arg0, s32 arg1) {
    UnkStruct_802AB200 *t;
    s32 n = 0;

    for (t = D_802AB200.unk89C; t != NULL; t = t->unk89C) {
        if (t->unk2 >= arg0 && t->unk2 <= arg1) {
            t = t->unk898;
            func_80238C68(t->unk89C->unk0);
            t = t->unk89C;
            n++;
        }
    }
    return n;
}

s32 func_80238C68(u16 arg0) {
    UnkStruct_802AB200 *t;
    s32 ret = -1;

    t = func_80238C08(arg0);

    if (t != NULL) {
        switch (t->unk4) {
            case 2:
                t->unk8 = 0;
                t->unk4 = 1;
                break;
            case 3:
                if (t->unk8 != 0) {
                    t->unk4 = 2;
                } else {
                    t->unk4 = 1;
                }
                break;
        }
        ret = t->unk0;
    }
    return ret;
}

UnkStruct_802AB200 *func_80238C08(u16 arg0) {
    UnkStruct_802AB200 *t;

    D_802AC340 = &D_802AB200;
    for (t = D_802AB200.unk89C; t != NULL; t = t->unk89C) {
        if (t->unk0 == arg0) {
            return t;
        }
        D_802AC340 = t;
    }
    return NULL;
}

s32 func_80238BDC(void) {
    if (D_802AC344 == NULL) {
        return -1;
    }
    return D_802AC344->unk0;
}

s32 func_80238B9C(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, u16 arg4) {
    if (arg4 < 0x110 || arg4 >= 0x3D0) {
        while (1) {}
    }
    return func_80238A10(arg0, arg1, arg2, arg3, arg4);
}

s32 func_80238A10(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, u16 arg4) {
    UnkStruct_802AB200 *p;
    UnkStruct_802AB200 *t;
    s32 i;

    if (D_802AC358 >= 80) {
        return -1;
    }
    t = func_802389D4();
    if (t == NULL) {
        return -1;
    }
    if (arg2 != NULL && arg3 == 0) {
        return -1;
    }
    func_8023897C(t);
    t->unk2 = arg4;
    t->unkC = arg0;
    t->unk10 = arg1;
    t->unk4 = 1;
    if (arg2 != NULL) {
        t->unk24 = arg2;
        t->unk20 = arg3;
    } else {
        t->unk24 = t->unk28;
        t->unk20 = 0x800;
    }
    p = func_80238918(t->unk2);
    if (p == NULL) {
        p = D_802AC340;
    } else {
        p = p->unk898;
    }
    func_802388E8(p, t);
    for (i = 0; i < 28; i++) {
        t->unk828[i] = 0;
    }
    t->unk828[3] = t->unkC;
    t->unk828[2] = (s32)(t->unk24 + t->unk20);
    D_802AC358++;
    return t->unk0;
}

UnkStruct_802AB200 *func_802389D4(void) {
    UnkStruct_802AB200 *t = D_802ABAA0.unk89C;

    if (t == NULL) {
        return NULL;
    }
    func_80238994(t);
    return t;
}

void func_80238994(UnkStruct_802AB200 *arg0) {
    if (arg0->unk89C != NULL) {
        arg0->unk89C->unk898 = arg0->unk898;
        arg0->unk898->unk89C = arg0->unk89C;
    } else {
        arg0->unk898->unk89C = NULL;
    }
}

void func_8023897C(UnkStruct_802AB200 *arg0) {
    arg0->unk2 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unk898 = NULL;
    arg0->unk89C = NULL;
}

UnkStruct_802AB200 *func_80238918(u16 arg0) {
    UnkStruct_802AB200 *t;

    D_802AC340 = &D_802AB200;
    for (t = D_802AB200.unk89C; t != NULL; t = t->unk89C) {
        if (arg0 < t->unk2) {
            return t;
        }
        D_802AC340 = t;
    }
    return NULL;
}

void func_802388E8(UnkStruct_802AB200 *arg0, UnkStruct_802AB200 *arg1) {
    arg1->unk898 = arg0;
    arg1->unk89C = arg0->unk89C;
    arg0->unk89C = arg1;
    if (arg1->unk89C != NULL) {
        arg1->unk89C->unk898 = arg1;
    }
}

/* The table is a static local (the object's .data, 0x50): without it in
 * the function IDO -O3 inlines func_802388C0 into func_8023946C. */
void func_802388C0(void) {
    static void *D_802A0100[] = {
        func_80238B9C,
        func_80238EA8,
        func_80239430,
        func_80238D98,
        func_8023903C,
        func_802391F0,
        func_802391A4,
        func_802390B4,
        func_802390F0,
        func_80239094,
        func_80238FF4,
        func_80238FDC,
        func_80238C68,
        func_80238F40,
        func_80238DFC,
        func_80238CF8,
        func_80238BDC,
        NULL,
    };

    func_80297D30(0x19, D_802A0100);
}
