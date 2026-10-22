#include "common.h"

/* -O3 (the Makefile's O3_C_FILES), so written last function first.  Eight
 * threads, each with its queue and stack (D_802A5A60), and a thread
 * (func_80237F84) serving the scheduler's messages.  func_80297Dxx are
 * ZeroJump stubs into libultra.  func_802382C0 is the static that
 * func_802382C8, func_802383A4 and func_80238414 inline (func_80237BA4's
 * body again); its empty stub is left at 0x802382C0.  The loops walk a
 * pointer beside the index, which is how the original keeps both. */

/* a message queue (os.h's OSMesgQueue) */
typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ void *unk14;
} UnkStruct_802A8938; /* size 0x18 */

/* one of eight threads, with its queue and stack */
typedef struct {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ u16 unk4;
    /* 0x008 */ UnkStruct_802A8938 unk8;
    /* 0x020 */ void *unk20;
    /* 0x024 */ u8 unk24[4];
    /* 0x028 */ u8 unk28[0x1B0];
    /* 0x1D8 */ u8 unk1D8[0x400];
} UnkStruct_802A5A60; /* size 0x5D8 */

void func_80297D80(UnkStruct_802A8938 *, void *, s32);
s32 func_80297D90(UnkStruct_802A8938 *, void *, s32);
s32 func_80297D98(UnkStruct_802A8938 *, void *, s32);
void func_80297DA8(void *, s32, void (*)(void *), void *, void *, s32);
void func_80297DB0(void *);
void func_80297DB8(void *);
void func_80297DC0(void);
void func_80297DC8(void *);
s32 func_80297DD0(void *);
void func_80297DD8(void *, s32);
s32 func_80297DE0(void *);
void func_80297DE8(void *, void *, s32, u8, s32);
void func_80297DF0(void *, void *, UnkStruct_802A8938 *);
void func_80297DF8(void *, void *);
UnkStruct_802A8938 *func_80297E00(void *);
s32 func_802983B0(void);

extern UnkStruct_802A5A60 D_802A5A60[8];
extern void *D_802A8920;
extern s32 D_802A8924;
extern s32 D_802A8928;
extern s32 D_802A892C;
extern s32 D_802A8930;
extern s32 D_802A8934;
extern UnkStruct_802A8938 D_802A8938;
extern void *D_802A8950;
extern s32 D_802A8954;
extern UnkStruct_802A8938 D_802A8958;
extern void *D_802A8970[16];
/* func_8023876C passes its end (D_802AAC38's address) as the second
 * argument: written as &D_802AAC38, IDO keeps that address in a register
 * for the store that follows. */
extern u8 D_802A89B0[0x2288];
extern UnkStruct_802A8938 *D_802AAC38;
extern u8 D_802AAC40[];
extern u8 D_802AAC48[];
extern u8 D_802AB1F0[];

void func_80237F84(void *arg0);
s32 func_80237B14(u16 arg0);
UnkStruct_802A5A60 *func_80237BA4(u16 arg0);

static UnkStruct_802A5A60 *func_802382C0(u16 arg0) {
    s32 i = func_80237B14(arg0);

    if (i == -1) {
        return NULL;
    }
    return &D_802A5A60[i];
}

void func_8023876C(void *arg0, s32 arg1, s32 arg2) {
    s32 i;
    UnkStruct_802A5A60 *p;
    s32 mode;

#if VERSION_JP
    mode = 2;
#else
    switch (func_802983B0()) {
        case 0:
            mode = 0x10;
            break;
        case 2:
            mode = 0x1E;
            break;
        default:
            mode = 2;
            break;
    }
#endif
    func_80297DE8(D_802A89B0, D_802A89B0 + 0x2288, 0x7F, mode, 1);
    D_802AAC38 = func_80297E00(D_802A89B0);
    func_80297DA8(D_802AAC48, arg1 + 9, func_80237F84, NULL, D_802AB1F0, 0x7D);
    func_80297DB0(D_802AAC48);
    D_802A8920 = arg0;
    D_802A8924 = arg1;
    D_802A8928 = arg2;
    D_802A892C = 0;
    D_802A8930 = 0;
    D_802A8934 = 0;
    p = D_802A5A60;
    for (i = 0; i < 8; i++, p++) {
        p->unk0 = arg1 + i;
        p->unk4 = 0;
        func_80297D80(&p->unk8, &p->unk20, 1);
    }
}

s32 func_802386CC(u16 arg0) {
    UnkStruct_802A5A60 *p = D_802A5A60;
    s32 i;

    for (i = 0; i < 8; i++, p++) {
        if ((p->unk4 & arg0) == arg0) {
            return i;
        }
    }
    return -1;
}

s32 func_802384D4(u16 arg0) {
    UnkStruct_802A5A60 *p = D_802A5A60;
    s32 i;

    for (i = 0; i < 8; i++, p++) {
        if (p->unk4 == arg0) {
            return i;
        }
    }
    return -1;
}

s32 func_80238564(void (*arg0)(void *), void *arg1, s32 arg2, void *arg3) {
    s32 i;
    UnkStruct_802A5A60 *p;

    if (D_802A892C + D_802A8930 + 1 > 8) {
        return -1;
    }
    i = func_802384D4(0);
    if (i == -1) {
        return -1;
    }
    D_802A8930++;
    p = &D_802A5A60[i];
    p->unk4 |= 1;
    if (arg3 == NULL) {
        func_80297DA8(p->unk28, p->unk0, arg0, arg1, p->unk1D8 + sizeof(p->unk1D8), D_802A8928 + arg2);
    } else {
        func_80297DA8(p->unk28, p->unk0, arg0, arg1, arg3, D_802A8928 + arg2);
    }
    if (p->unk8.unk8 >= p->unk8.unk10) {
        func_80297D90(&p->unk8, NULL, 0);
    }
    return p->unk0;
}

void func_80238414(s32 arg0) {
    UnkStruct_802A5A60 *slot = func_802382C0(func_80297DE0(NULL));
    s32 i;

    if (slot == NULL) {
        for (;;) {}
    }
    for (i = 0; i < arg0; i++) {
        slot->unk4 |= 4;
        func_80297DB8(slot->unk28);
    }
}

s32 func_802382C8(s32 arg0);

s32 func_802383A4(s32 arg0) {
    func_802382C8(arg0);
    func_80297DC8(func_802382C0(arg0)->unk28);
    return arg0;
}

void func_80238368(void) {
    if (func_802382C8(func_80297DE0(NULL)) != -1) {
        func_80297DC8(NULL);
    }
}

s32 func_802382C8(s32 arg0) {
    UnkStruct_802A5A60 *slot;

    if (D_802A892C == 0) {
        for (;;) {}
    }
    slot = func_802382C0(arg0);
    if (slot == NULL) {
        for (;;) {}
    }
    slot->unk4 = 0;
    D_802A892C--;
    return slot->unk0;
}

void func_802381F8(void) {
    s32 i;
    s32 pri;
    UnkStruct_802A5A60 *p;
    s32 a;
    s32 b;

    pri = func_80297DD0(NULL);
    func_80297DD8(D_802A8920, 1);
    for (;;) {
        a = 0;
        b = 0;
        p = D_802A5A60;
        for (i = 0; i < 8; i++, p++) {
            if ((p->unk4 & 0x100) && (p->unk4 & 2)) {
                a++;
                if (p->unk4 & 4) {
                    b++;
                }
            }
        }
        if (a == b) {
            break;
        }
        func_80297DC0();
    }
    func_80297DD8(D_802A8920, pri);
}

void func_80238100(void) {
    s32 i;
    s32 pri;
    UnkStruct_802A5A60 *p;

    pri = func_80297DD0(NULL);
    func_80297DD8(D_802A8920, 100);
    D_802A892C += D_802A8930;
    D_802A8930 = 0;
    D_802A8934 = 0;
    p = D_802A5A60;
    for (i = 0; i < 8; i++, p++) {
        if (p->unk4 & 1) {
            if (!(p->unk4 & 2)) {
                p->unk4 |= 0x102;
                func_80297DB0(p->unk28);
            } else if (p->unk4 & 4) {
                p->unk4 &= ~4;
                func_80297DB0(p->unk28);
            }
        }
    }
    func_80297DD8(D_802A8920, pri);
}

void func_80237F84(void *arg0) {
    s32 run;
    s32 pad; /* the frame has a slot here */
    UnkStruct_802A8938 *mq;
    s16 *msg = NULL;

    func_80297D80(&D_802A8938, &D_802A8950, 1);
    func_80297D80(&D_802A8958, D_802A8970, 16);
    func_80297DF0(D_802A89B0, D_802AAC40, &D_802A8938);
    D_802A8954 = 0;
    run = 1;
    while (run) {
        if (D_802A8938.unk8 >= D_802A8938.unk10) {
            func_80297D90(&D_802A8938, &msg, 1);
        }
        func_80297D90(&D_802A8938, &msg, 1);
        switch (*msg) {
            case 1:
                D_802A8954++;
                while (func_80297D90(&D_802A8958, &mq, 0) != -1) {
                    func_80297D98(mq, NULL, 0);
                }
                break;
            case 4:
                break;
        }
    }
}

void func_80237F44(UnkStruct_802A8938 *arg0) {
    func_80297D98(&D_802A8958, arg0, 0);
    func_80297D90(arg0, NULL, 1);
}

s32 func_80237F34(void) {
    return D_802A8954;
}

s32 func_80237E18(s32 arg0, s32 arg1);

s32 func_80237F0C(s32 arg0, s32 arg1) {
    return func_80237E18(arg0, D_802A8928 + arg1);
}

s32 func_80237ED0(s32 arg0) {
    s32 id;
    s32 pri = D_802A8928 + arg0;

    id = func_80297DE0(NULL);
    return func_80237E18(id, pri);
}

s32 func_80237EA0(s32 arg0) {
    return func_80237E18(func_80297DE0(NULL), arg0);
}

s32 func_80237E18(s32 arg0, s32 arg1) {
    UnkStruct_802A5A60 *slot = func_80237BA4(arg0);

    if (slot == NULL) {
        return -1;
    }
    func_80297DD8(slot->unk28, arg1);
    return arg0;
}

s32 func_80237D7C(s32 arg0);

s32 func_80237DF0(void) {
    return func_80237D7C(func_80297DE0(NULL));
}

s32 func_80237D7C(s32 arg0) {
    UnkStruct_802A5A60 *slot = func_80237BA4(arg0);

    if (slot == NULL) {
        return -1;
    }
    return func_80297DD0(slot->unk28);
}

s32 func_80237CAC(s32 arg0, u16 arg1);

s32 func_80237D4C(u16 arg0) {
    return func_80237CAC(func_80297DE0(NULL), arg0);
}

s32 func_80237CAC(s32 arg0, u16 arg1) {
    UnkStruct_802A5A60 *slot;

    arg1 &= 0xFF00;
    slot = func_80237BA4(arg0);
    if (slot == NULL) {
        return -1;
    }
    slot->unk4 &= 0xFF;
    slot->unk4 |= arg1;
    return arg0;
}

s32 func_80237C08(s32 arg0);

s32 func_80237C84(void) {
    return func_80237C08(func_80297DE0(NULL));
}

s32 func_80237C08(s32 arg0) {
    UnkStruct_802A5A60 *slot = func_80237BA4(arg0);

    if (slot == NULL) {
        return -1;
    }
    return slot->unk4 & 0xFF00;
}

UnkStruct_802A5A60 *func_80237BA4(u16 arg0) {
    s32 i = func_80237B14(arg0);

    if (i == -1) {
        return NULL;
    }
    return &D_802A5A60[i];
}

s32 func_80237B14(u16 arg0) {
    UnkStruct_802A5A60 *p = D_802A5A60;
    s32 i;

    for (i = 0; i < 8; i++, p++) {
        if (p->unk0 == arg0) {
            return i;
        }
    }
    return -1;
}

void func_80237AE4(void *arg0, UnkStruct_802A8938 *arg1) {
    func_80297DF0(D_802A89B0, arg0, arg1);
}

void func_80237ABC(void *arg0) {
    func_80297DF8(D_802A89B0, arg0);
}

void func_80237A90(void *arg0) {
    func_80297D98(D_802AAC38, arg0, 1);
}

void func_80237A70(UnkStruct_802A8938 *arg0, void *arg1) {
    func_80297D90(arg0, arg1, 1);
}
