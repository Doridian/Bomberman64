#include "common.h"

/* gbi.h's _SHIFTL: func_80226E84's texture rectangles match only with its
 * u32 casts (the shifted value, not the masked one, is shared between the
 * unrolled copies) */
#define _SHIFTL(v, s, w) ((u32) (((u32) (v) & ((0x01 << (w)) - 1)) << (s)))

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_80226E84; /* size 0x8 */

/* gbi.h's Mtx */
typedef struct {
    /* 0x00 */ s32 m[16];
} UnkStruct_802A53D8; /* size 0x40 */

/* one frame's buffers (D_8014C8D0[2]): matrices, the areas func_80227678
 * hands out, the display list */
typedef struct {
    /* 0x00000 */ UnkStruct_802A53D8 mtx[0x400];
    /* 0x10000 */ u8 unk10000[4][0x5000];
    /* 0x24000 */ UnkStruct_80226E84 gfx[0x600];
} UnkStruct_802A538C; /* size 0x27000 */

/* a message queue (os.h's OSMesgQueue) */
typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ void *unk14;
} UnkStruct_802A5330; /* size 0x18 */

/* a scheduler task (sched.h's OSScTask) */
typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ void *unkC;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ void *unk18;
    /* 0x1C */ u32 unk1C;
    /* 0x20 */ void *unk20;
    /* 0x24 */ u32 unk24;
    /* 0x28 */ void *unk28;
    /* 0x2C */ u32 unk2C;
    /* 0x30 */ void *unk30;
    /* 0x34 */ u32 unk34;
    /* 0x38 */ void *unk38;
    /* 0x3C */ void *unk3C;
    /* 0x40 */ void *unk40;
    /* 0x44 */ u32 unk44;
    /* 0x48 */ void *unk48;
    /* 0x4C */ u32 unk4C;
    /* 0x50 */ UnkStruct_802A5330 *unk50;
    /* 0x54 */ void *unk54;
    /* 0x58 */ u8 unk58[0x10];
} UnkStruct_8029F608; /* size 0x68 */

void func_8022997C(void);
void func_80237A70(UnkStruct_802A5330 *, void *);
void func_80237A90(UnkStruct_8029F608 *);
void func_80237AE4(void *, UnkStruct_802A5330 *);
void func_80237D4C(s32);
void func_80237E18(s32, s32);
void func_80237F44(UnkStruct_802A5330 *);
s32 func_80238564(void (*)(void *), s32, s32, s32);
void func_802383A4(s32);
void func_80297D80(UnkStruct_802A5330 *, void *, s32);
void func_80297D90(UnkStruct_802A5330 *, void *, s32);
void func_80297D98(UnkStruct_802A5330 *, s32, s32);

extern u8 D_1000000[];
extern u8 D_200000[];
extern u16 D_80100000[][320 * 240];
extern UnkStruct_802A538C D_8014C8D0[2];
extern u8 D_8019A8D0[];
extern u64 D_801E56C0[0x2000];
extern u8 D_8029D250[];
extern u8 D_8029D320[];
extern s32 D_8029F5E0;
extern s32 D_8029F5E4;
extern s32 D_8029F5E8;
extern s32 D_8029F5EC;
extern s32 D_8029F5F0;
extern s32 D_8029F5F4;
extern s32 D_8029F5F8;
extern s32 D_8029F5FC;
extern s32 D_8029F600;
extern UnkStruct_8029F608 D_8029F608[2];
extern u8 D_8029F6D8[];
extern u8 D_8029F718[];
extern u8 D_8029F7A0[];
extern u8 D_8029F7C8[];
extern u8 D_802A4840[];
extern s32 D_802A5800;

/* This object's .bss (0x802A5330-0x802A53D0). Defined here because the
 * code depends on it: as1 shares one `lui $at` between stores to two
 * variables of the file's own .bss (func_80226D80), not between externs. */
UnkStruct_802A5330 D_802A5330;
UnkStruct_802A5330 D_802A5348;
void *D_802A5360;
void *D_802A5364;
s32 D_802A5368;
u8 D_802A536C[4];
s32 D_802A5370[4];
UnkStruct_80226E84 *D_802A5380[2];
s32 D_802A5388;
UnkStruct_802A538C *D_802A538C;
UnkStruct_80226E84 *D_802A5390;
s32 D_802A5394;
s32 D_802A5398;
u8 D_802A539C[4];
UnkStruct_802A5330 D_802A53A0;
void *D_802A53B8;
s32 D_802A53BC;
s32 D_802A53C0;
s32 D_802A53C4;
s32 D_802A53C8;
s32 D_802A53CC;

s32 func_8022773C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_802A5370[i] == 0) {
            D_802A5370[i] = 1;
            return i;
        }
    }
    return 0;
}

void func_80227708(s32 x, s32 y, s32 w, s32 h) {
    D_802A53BC = x;
    D_802A53C0 = y;
    D_802A53C4 = x + w - 1;
    D_802A53C8 = y + h - 1;
}

void func_802276FC(s32 arg0) {
    D_8029F5E4 = arg0;
}

void func_802276E0(s32 r, s32 g, s32 b) {
    D_8029F5EC = r;
    D_8029F5F0 = g;
    D_8029F5F4 = b;
}

void func_802276D4(s32 arg0) {
    D_8029F5F8 = arg0;
}

void func_802276C8(s32 arg0) {
    D_8029F5FC = arg0;
}

void func_802276B4(s32 i) {
    D_802A5370[i] = 0;
}

s32 func_8022769C(s32 i) {
    return D_802A5370[i];
}

void *func_80227678(s32 n) {
    return D_802A538C->unk10000[n];
}

void func_802272B0(UnkStruct_80226E84 **arg0);

UnkStruct_80226E84 *func_80227464(void) {
    D_802A5388 = D_8029F5E0;
    D_802A538C = &D_8014C8D0[D_802A5388];
    D_802A5390 = D_802A538C->gfx;
    D_802A5368 = 0;
    { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0xBC000006; g->w1 = 0; }
    { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0xBC000406; g->w1 = (u32) ((char *) D_80100000[D_802A5388] - 0x80000000); }
    { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0x06000000; g->w1 = (u32) D_8029F718; }
    if (D_8029F5F8 != 0) {
        { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0xBA000602; g->w1 = 0xC0; }
    } else {
        { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0xBA000602; g->w1 = 0; }
    }
    { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0x06000000; g->w1 = (u32) D_8029F6D8; }
    { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0xFE000000; g->w1 = (u32) D_200000; }
    { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0xED000000; g->w1 = 0x5003C0; }
    func_802272B0(&D_802A5390);
    { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0xB7000000; g->w1 = 0x22001; }
    { UnkStruct_80226E84 *g = D_802A5390++; g->w0 = 0xB900031D; g->w1 = 0x553078; }
    return D_802A5390;
}

void func_802272B0(UnkStruct_80226E84 **arg0) {
    UnkStruct_80226E84 *gfx = *arg0;

    { UnkStruct_80226E84 *g = gfx++; g->w0 = 0x06000000; g->w1 = (u32) D_8029F7A0; }
    { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xF6000000 | (((D_802A53C4 - 1) & 0x3FF) << 14) | (((D_802A53C8 - 1) & 0x3FF) << 2); g->w1 = ((D_802A53BC & 0x3FF) << 14) | ((D_802A53C0 & 0x3FF) << 2); }
    { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xFF10013F; g->w1 = (u32) D_1000000; }
    if (D_8029F5E4 != 0) {
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xF7000000; g->w1 = ((((D_8029F5EC << 8) & 0xF800) | ((D_8029F5F0 << 3) & 0x7C0) | ((D_8029F5F4 >> 2) & 0x3E) | 1) << 16) | (((D_8029F5EC << 8) & 0xF800) | ((D_8029F5F0 << 3) & 0x7C0) | ((D_8029F5F4 >> 2) & 0x3E) | 1); }
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xF6000000 | (((D_802A53C4 - 1) & 0x3FF) << 14) | (((D_802A53C8 - 1) & 0x3FF) << 2); g->w1 = ((D_802A53BC & 0x3FF) << 14) | ((D_802A53C0 & 0x3FF) << 2); }
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; }
    }
    { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xBA001402; g->w1 = 0; }
    *arg0 = gfx;
}

void func_80226E84(UnkStruct_80226E84 *gfx) {
    s32 i;

    if (D_8029F5F8 != 0) {
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xBB000001; g->w1 = 0x80008000; }
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xB900031D; g->w1 = 0x504340; }
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xFA000000; g->w1 = D_8029F5FC & 0xFF; }
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF67B; }
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xBA001301; g->w1 = 0; }
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xBA000E02; g->w1 = 0; }
        { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xB9000002; g->w1 = 0; }
        for (i = 0; i < 240; i += 2) {
            { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xFD100000; g->w1 = (u32) ((char *) D_80100000[D_802A5388 ^ 1] - 0x80000000) + i * 640; } { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xF5100000; g->w1 = 0x07000000; } { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xE6000000; g->w1 = 0; } { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xF3000000; g->w1 = 0x0727F01A; } { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xE7000000; g->w1 = 0; } { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xF510A000; g->w1 = 0; } { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xF2000000; g->w1 = 0x4FC004; }
            { UnkStruct_80226E84 *g = gfx++; g->w0 = _SHIFTL(0xE4, 24, 8) | _SHIFTL(320 << 2, 12, 12) | _SHIFTL((i + 2) << 2, 0, 12); g->w1 = _SHIFTL(0, 24, 3) | _SHIFTL(0, 12, 12) | _SHIFTL(i << 2, 0, 12); } { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xB4000000; g->w1 = 0; } { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xB3000000; g->w1 = 0x04000400; }
        }
    }
    { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xE9000000; g->w1 = 0; }
    { UnkStruct_80226E84 *g = gfx++; g->w0 = 0xB8000000; g->w1 = 0; }
    D_802A5380[D_802A5388] = gfx;
    if (D_8029F5E8 != 0) {
        func_80297D98(&D_802A5330, D_8029F600, 0);
    }
    func_80237F44(&D_802A5348);
    D_8029F600++;
}

u16 *func_80226E4C(s32 arg0) {
    return D_80100000[D_802A5388 ^ arg0];
}

void func_80226E40(s32 arg0) {
    D_8029F5E8 = arg0;
}

void func_80226B18(void *arg0);

void func_80226D80(void) {
    s32 i;

    func_80297D30(0x22, D_8029F7C8);
    for (i = 0; i < 4; i++) {
        D_802A5370[i] = 0;
    }
    D_802A5800 = 0;
    func_80297D80(&D_802A5330, &D_802A5360, 1);
    func_80297D80(&D_802A5348, &D_802A5364, 1);
    func_80297D80(&D_802A53A0, &D_802A53B8, 1);
    D_802A53CC = func_80238564(func_80226B18, 0, 0, 0);
    func_80237E18(D_802A53CC, 0x7C);
}

void func_80226B18(void *arg0) {
    u8 client[8];
    UnkStruct_802A5330 mq;
    void *msgbuf;
    UnkStruct_8029F608 *task;
    void *msg5C;
    UnkStruct_802A538C *frame;
    void *msg54;
    s32 i;

    func_80237D4C(0);
    func_80297D80(&mq, &msgbuf, 1);
    func_80237AE4(client, &mq);
    D_8029F5E0 = 0;
    while (1) {
        if (D_802A5330.unk8 >= D_802A5330.unk10) {
            func_80297D90(&D_802A5330, &msg54, 1);
        }
        func_80297D90(&D_802A5330, &D_802A5398, 1);
        i = D_8029F5E0;
        task = &D_8029F608[i];
        D_802A5800 = 0;
        D_8029F5E0 ^= 1;
        task->unkC = D_80100000[i];
        frame = &D_8014C8D0[i];
        task->unk18 = D_8029D250;
        task->unk1C = (u32) D_8029D320 - (u32) D_8029D250;
        task->unk20 = D_8029D320;
        task->unk28 = D_802A4840;
        task->unk30 = D_8019A8D0;
        task->unk38 = D_801E56C0;
        /* a 64-bit sum: with a 32-bit one (or a folded symbol+offset) the
         * temporaries come out in other registers */
        task->unk3C = (u64 *) ((u64) D_801E56C0 + 0x10000);
        task->unk40 = frame->gfx;
        task->unk44 = (D_802A5380[i] - frame->gfx) * sizeof(UnkStruct_80226E84);
        task->unk50 = &D_802A53A0;
        task->unk54 = &D_802A53B8;
        func_80297D60(D_802A538C, 0x10000);
        func_80237A90(task);
        func_80237A70(&D_802A53A0, &msg5C);
        func_8022997C();
        D_802A5394 = D_802A5398;
    }
}

void func_80226AF0(void) {
    func_802383A4(D_802A53CC);
}
