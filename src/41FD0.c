#include "common.h"

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_8022787C; /* size 0x8 */

/* gbi.h's Mtx */
typedef struct {
    /* 0x00 */ s32 m[16];
} UnkStruct_802A53D8; /* size 0x40 */

/* gbi.h's Light: col, colc and dir */
typedef struct {
    /* 0x00 */ u8 col[3];
    /* 0x03 */ s8 pad1;
    /* 0x04 */ u8 colc[3];
    /* 0x07 */ s8 pad2;
    /* 0x08 */ s8 dir[3];
    /* 0x0B */ s8 pad3;
    /* 0x0C */ u8 pad4[4];
} UnkStruct_8029F800; /* size 0x10 */

/* gbi.h's Lights2: an ambient light and two lights */
typedef struct {
    /* 0x00 */ u8 col[3];
    /* 0x03 */ s8 pad1;
    /* 0x04 */ u8 colc[3];
    /* 0x07 */ s8 pad2;
    /* 0x08 */ UnkStruct_8029F800 l[2];
} UnkStruct_8029F7F8; /* size 0x28 */

/* a viewport, its view matrix and its scissor box */
typedef struct {
    /* 0x00 */ s16 vscale[4];
    /* 0x08 */ s16 vtrans[4];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ UnkStruct_802A53D8 unk18;
    /* 0x58 */ void *unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ s32 unk6C;
} UnkStruct_800BD5B0; /* size 0x70 */

/* one frame's buffers (D_8014C8D0[2]): matrices, the 412F0 areas
 * func_80227678 hands out, the display list */
typedef struct {
    /* 0x00000 */ UnkStruct_802A53D8 mtx[0x400];
    /* 0x10000 */ u8 unk10000[4][0x5000];
    /* 0x24000 */ UnkStruct_8022787C gfx[0x600];
} UnkStruct_802A538C; /* size 0x27000 */

void *func_80227678(s32);
void guPerspective(UnkStruct_802A53D8 *, u16 *, f32, f32, f32, f32, f32);
void guLookAt(UnkStruct_802A53D8 *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_8029BB38(void *, UnkStruct_802A53D8 *);

extern UnkStruct_800BD5B0 D_800BD5B0[4];
extern s32 D_8029F7E0;
extern s32 D_8029F7E4;
extern s32 D_8029F7E8;
extern s32 D_8029F7EC;
extern s32 D_8029F7F0;
extern s32 D_8029F7F4;
extern UnkStruct_8029F7F8 D_8029F7F8;
extern u8 D_8029F820[];
extern s32 D_802A5368;
extern UnkStruct_802A538C *D_802A538C;
extern u16 D_802A53D0;
extern UnkStruct_802A53D8 D_802A53D8;
extern u8 D_802A5418[];

UnkStruct_800BD5B0 *func_80227E38(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_800BD5B0[i].unk10 == 0) {
            D_800BD5B0[i].unk10 = 1;
            return &D_800BD5B0[i];
        }
    }
    return (UnkStruct_800BD5B0 *) -1;
}

void func_80227E2C(UnkStruct_800BD5B0 *arg0) {
    arg0->unk10 = 0;
    arg0->unk58 = NULL;
}

void func_80227D50(UnkStruct_800BD5B0 *arg0, u32 x, u32 y, u32 w, u32 h) {
    arg0->vscale[0] = w * 2;
    arg0->vscale[1] = h * 2;
    arg0->vscale[2] = 0x1FF;
    arg0->vscale[3] = 0;
    arg0->vtrans[0] = (x * 2 + w) * 2;
    arg0->vtrans[1] = (y * 2 + h) * 2;
    arg0->vtrans[2] = 0x1FF;
    arg0->vtrans[3] = 0;
    arg0->unk5C = x;
    arg0->unk60 = y;
    arg0->unk64 = x + w - 1;
    arg0->unk68 = y + h - 1;
}

void func_80227CD0(UnkStruct_800BD5B0 *arg0, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp,
                   f32 yUp, f32 zUp) {
    guLookAt(&arg0->unk18, xEye, yEye, zEye, xAt, yAt, zAt, xUp, yUp, zUp);
    func_8029BB38(D_802A5418, &arg0->unk18);
}

void func_80227C9C(UnkStruct_800BD5B0 *arg0, s32 arg1) {
    arg0->unk14 = arg1;
    arg0->unk58 = func_80227678(arg1);
}

void func_80227C50(f32 fovy, f32 aspect, f32 near, f32 far, f32 scale) {
    guPerspective(&D_802A53D8, &D_802A53D0, fovy, aspect, near, far, scale);
}

void func_80227BE8(u8 r, u8 g, u8 b);
void func_80227BAC(s8 x, s8 y, s8 z);

void func_80227C18(void) {
    func_80227BE8(0x32, 0x32, 0x32);
    func_80227BAC(0, 0x72, 0x37);
}

void func_80227BE8(u8 r, u8 g, u8 b) {
    D_8029F7F8.l[0].col[0] = D_8029F7F8.l[0].colc[0] = r;
    D_8029F7F8.l[0].col[1] = D_8029F7F8.l[0].colc[1] = g;
    D_8029F7F8.l[0].col[2] = D_8029F7F8.l[0].colc[2] = b;
}

void func_80227BAC(s8 x, s8 y, s8 z) {
    D_8029F7F8.l[1].dir[0] = x;
    D_8029F7F8.l[1].dir[1] = y;
    D_8029F7F8.l[1].dir[2] = z;
    D_8029F7F8.l[0].dir[0] = D_8029F7F8.l[1].dir[0];
    D_8029F7F8.l[0].dir[1] = D_8029F7F8.l[1].dir[1];
    D_8029F7F8.l[0].dir[2] = D_8029F7F8.l[1].dir[2];
}

void func_8022787C(UnkStruct_8022787C **arg0) {
    UnkStruct_8022787C *gfx = *arg0;
    UnkStruct_800BD5B0 *p;
    s32 i;

    { UnkStruct_8022787C *g = gfx++; g->w0 = 0xBC000002; g->w1 = 0x80000060; } { UnkStruct_8022787C *g = gfx++; g->w0 = 0x03860010; g->w1 = (u32) &D_8029F7F8.l[0]; } { UnkStruct_8022787C *g = gfx++; g->w0 = 0x03880010; g->w1 = (u32) &D_8029F7F8.l[1]; } { UnkStruct_8022787C *g = gfx++; g->w0 = 0x038A0010; g->w1 = (u32) &D_8029F7F8; }
    { UnkStruct_8022787C *g = gfx++; g->w0 = 0xBC00000E; g->w1 = D_802A53D0; }
    for (i = 0; i < 4; i++) {
        p = &D_800BD5B0[i];
        if (p->unk10 != 0 && p->unk58 != NULL) {
            func_80225C44(&D_802A538C->mtx[D_802A5368], &D_802A53D8, 0x40);
            { UnkStruct_8022787C *g = gfx++; g->w0 = 0x01030040; g->w1 = (u32) &D_802A538C->mtx[D_802A5368]; }
            D_802A5368++;
            { UnkStruct_8022787C *g = gfx++; g->w0 = 0x03800010; g->w1 = (u32) p; }
            func_80225C44(&D_802A538C->mtx[D_802A5368], &p->unk18, 0x40);
            { UnkStruct_8022787C *g = gfx++; g->w0 = 0x01010040; g->w1 = (u32) &D_802A538C->mtx[D_802A5368]; }
            D_802A5368++;
            { UnkStruct_8022787C *g = gfx++; g->w0 = 0xED000000 | (((s32) (p->unk5C * 4.0f) & 0xFFF) << 12) | ((s32) (p->unk60 * 4.0f) & 0xFFF); g->w1 = (((s32) (p->unk64 * 4.0f) & 0xFFF) << 12) | ((s32) (p->unk68 * 4.0f) & 0xFFF); }
            { UnkStruct_8022787C *g = gfx++; g->w0 = 0x06000000; g->w1 = (u32) func_80227678(p->unk14); }
        }
    }
    *arg0 = gfx;
    func_80297D60(p, 0x1C0);
}

void func_80227870(void) {
    D_8029F7E0 = 0;
}

void func_80227834(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    D_8029F7E0 = 1;
    D_8029F7E4 = arg0;
    D_8029F7E8 = arg1;
    D_8029F7EC = arg2;
    D_8029F7F0 = arg3;
    D_8029F7F4 = arg4;
}

void func_802277D0(void) {
    s32 i;

    func_80297D30(0x21, D_8029F820);
    for (i = 0; i < 4; i++) {
        D_800BD5B0[i].unk10 = 0;
        D_800BD5B0[i].unk58 = NULL;
    }
}
