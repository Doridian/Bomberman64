/*
 * NON_MATCHING: main_code's 47A80, complete: five functions (us
 * 0x8022D280-0x8022DB00) that build a model's display list from its joint
 * tree. Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 23, eu 23, jp 23
 *
 * fcmp counts a static with the global before it. func_8022DAB0 and
 * func_8022D280 + func_8022D414 match. In func_8022D414 the call's joint
 * address is `idx * 48 + bj` (the multiply first, so ugen evaluates it
 * first and gives it t8, and the add is t0,v1), while j is
 * `&((Joint *)bj)[idx]`; with bj a variable uopt doesn't reassociate the
 * sum. func_8022D58C + func_8022D980: 23 words,
 * all in case 6's SetTileSize. Case 6's first packet has its w1 store a
 * line below the rest (as1 orders a block partly by .loc line): that
 * puts its `addiu a0` between the two stores as in the original. The (u16) casts on the w1 terms are real:
 * ugen gives each an `and 0xFFFF` (one more temp) that as1 deletes before
 * the `and 0xFFF`, and with them ugen's temp queue leaves case 6 in the
 * original's state, so everything after it matches. Still different: the
 * original's ugen allocates g + 1 (t4) right after loading g and the
 * D_802A2D50[1] load (t5) before [0] (t6), and frees g + 1's register
 * only after the w0 store (a FIFO model of ugen's temps,
 * scratch/47A80/p2/fifo8.py, finds no other order).
 */
#include "common.h"

/* A model's display list, built from its joint tree: one matrix per joint
 * with a translation or rotation, a segment-6 display list per mesh. */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

#define GFX2(pkt, a, b) { Gfx *_g = (Gfx *) (pkt); _g->w0 = (a); _g->w1 = (b); }
#define GFX2R(pkt, a, b) { Gfx *_g = (Gfx *) (pkt); _g->w1 = (b); _g->w0 = (a); }

typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 dl;
} MeshEntry; /* size 0xC; entry n is at the base + 0xC * (n + 1) */

typedef struct {
    /* 0x00 */ s32 mesh;
    /* 0x04 */ f32 trans[3];
    /* 0x10 */ f32 rot[3];
    /* 0x1C */ u8 pad1C[0xC];
    /* 0x28 */ u32 next;
    /* 0x2C */ u32 child;
} Joint; /* size 0x30 */

typedef struct Node {
    /* 0x00 */ s32 mesh;
    /* 0x04 */ u8 pad4[8];
    /* 0x0C */ struct Node **children;
    /* 0x10 */ s32 count;
    /* 0x14 */ f32 trans[3];
    /* 0x20 */ f32 rot[3];
} Node;

typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s32 *bases;
    /* 0x0C */ s32 *meshes;
} MeshOverride; /* size 0x10 */

typedef struct {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ Node *root;
} Model;

void guMtxIdentF(f32 mf[4][4]);
void guMtxCatF(f32 mf[4][4], f32 nf[4][4], f32 res[4][4]);
void guMtxF2L(f32 mf[4][4], void *m);
void func_8029CA80(f32 m[4][4], f32, f32, f32);
void func_8029C7A8(f32 m[4][4], f32, f32, f32);
void func_8022928C(f32 m[4][4], f32 n[4][4]);

extern MeshOverride D_80098C18[];
extern f32 D_80098CF8[][4][4];
extern s32 D_800A0CF8;
extern s32 D_8029F840;
extern s32 D_8029FCC0;
extern s32 D_8029FCC4;
extern Gfx D_8029FCC8[];
extern s32 D_802A2D50[];
extern s32 D_802A5368;
extern u8 (*D_802A538C)[0x40];
extern f32 D_802A5418[4][4];
extern f32 D_802A5510[4][4];
extern Gfx *D_802A5550;
extern s32 D_802A5554;

static void func_8022D280(Gfx **gp, f32 *trans, f32 *rot, s32 *pushed);
static void func_8022D414(Gfx **gp, s32 base, s32 joints, s32 idx);
void func_8022D58C(Gfx **gp, s32 base, s32 idx);
static void func_8022D980(Node *node);
void func_8022DAB0(Model *model, Gfx **gp, s32 base);

void func_8022DAB0(Model *model, Gfx **gp, s32 base) {
    D_802A5550 = *gp;
    D_802A5554 = base;
    func_8022D980(model->root);
    *gp = D_802A5550;
}

static void func_8022D980(Node *node) {
    s32 i;
    s32 pushed;

    func_8022D280(&D_802A5550, node->trans, node->rot, &pushed);
    if (node->mesh >= 0) {
        func_8022D58C(&D_802A5550, D_802A5554, node->mesh);
    }
    if (node->count != 0) {
        for (i = 0; i < node->count; i++) {
            func_8022D980(node->children[i]);
        }
    }
    if (pushed != 0) {
        GFX2(D_802A5550++, 0xBD000000, 0);
        if (pushed == 2) {
            D_800A0CF8--;
        }
    }
}

void func_8022D58C(Gfx **gp, s32 base, s32 idx) {
    s32 load;
    Gfx *g;
    MeshEntry *m;
    s32 pushed;
    s32 type;

    load = 0;
    pushed = 0;
    if (D_8029F840 != -1) {
        if (D_80098C18[D_8029F840].bases[idx] != 0) {
            base = D_80098C18[D_8029F840].bases[idx];
            idx = D_80098C18[D_8029F840].meshes[idx];
            if (((MeshEntry *)base)[idx + 1].type == 1U) {
                D_8029F840 = -1;
            }
        }
    }
    m = &((MeshEntry *)base)[idx + 1];
    type = m->type;
    g = *gp;
    GFX2(g++, 0xBC000806, base + 0x80000000);
    if (type == 1) {
        func_8022D414(&g, base, m->dl, m->unk4);
    } else if (type != 4) {
        if (D_8029FCC0 != 0 && type != 6) {
            GFX2(g++, 0xB6000000, 0x40000);
            GFX2(g++, 0xBB000000, 0);
            D_8029FCC0 = 0;
        }
        if (D_8029FCC4 != 0 && type != 8) {
            GFX2(g++, 0xB6000000, 0x40000);
            D_8029FCC4 = 0;
        }
        switch (type) {
        case 5:
            guMtxCatF(D_80098CF8[D_800A0CF8], D_802A5418, D_802A5510);
            func_8022928C(D_802A5510, D_802A5510);
            D_800A0CF8++;
            guMtxIdentF(D_80098CF8[D_800A0CF8]);
            pushed = 1;
            load = 1;
            break;
        case 6:
            D_8029FCC0 = 1;
            { Gfx *_g = g++; _g->w0 = 0x06000000; /* GFX2 with w1 a line down (as1's order) */
            _g->w1 = (u32) D_8029FCC8; }
            {
                Gfx *_g = g;
                _g->w0 = (0xF2000000 | ((D_802A2D50[0] & 0xFFF) << 12)) | (D_802A2D50[1] & 0xFFF);
                _g->w1 = (((u16) (D_802A2D50[0] + 0x7C) & 0xFFF) << 12) | ((u16) (D_802A2D50[1] + 0x7C) & 0xFFF);
                g = _g + 1;
            }
            break;
        case 8:
            D_8029FCC4 = 1;
            GFX2(g++, 0xB7000000, 0x40000);
            break;
        }
        if (load != 0) {
            guMtxF2L(D_802A5510, D_802A538C[D_802A5368]);
            GFX2(g++, 0x01040040, (u32) D_802A538C[D_802A5368]);
            D_802A5368++;
            GFX2(g++, 0x06000000, m->dl + base);
            GFX2(g++, 0xBD000000, 0);
            if (pushed != 0) {
                D_800A0CF8--;
            }
        } else {
            GFX2(g++, 0x06000000, m->dl + base);
        }
    }
    *gp = g;
}

static void func_8022D414(Gfx **gp, s32 base, s32 joints, s32 idx) {
    s32 bj;
    Gfx *g;
    Joint *j;
    s32 pushed;

    pushed = 0;
    g = *gp;
    bj = base + joints;
    func_8022D280(&g, ((Joint *)(idx * 48 + bj))->trans, ((Joint *)(idx * 48 + bj))->rot, &pushed);
    j = &((Joint *)bj)[idx];
    if (j->mesh >= 0) {
        func_8022D58C(&g, base, j->mesh);
    }
    if (j->child != 0) {
        func_8022D414(&g, base, joints, idx + j->child);
    }
    if (pushed != 0) {
        GFX2(g++, 0xBD000000, 0);
        if (pushed == 2) {
            D_800A0CF8--;
        }
    }
    if (j->next != 0) {
        func_8022D414(&g, base, joints, idx + j->next);
    }
    *gp = g;
}

static void func_8022D280(Gfx **gp, f32 *trans, f32 *rot, s32 *pushed) {
    Gfx *g;
    s32 n;

    g = *gp;
    n = 0;
    guMtxIdentF(D_802A5510);
    if (trans[0] != 0.0f || trans[1] != 0.0f || trans[2] != 0.0f) {
        func_8029CA80(D_802A5510, trans[0], trans[1], trans[2]);
        n = 1;
    }
    if (rot[0] != 0.0f || rot[1] != 0.0f || rot[2] != 0.0f) {
        func_8029C7A8(D_802A5510, rot[0], rot[1], rot[2]);
        n = 2;
    }
    if (n == 2) {
        D_800A0CF8++;
        guMtxCatF(D_802A5510, D_80098CF8[D_800A0CF8 - 1], D_80098CF8[D_800A0CF8]);
    }
    if (n != 0) {
        guMtxF2L(D_802A5510, D_802A538C[D_802A5368]);
        GFX2(g++, 0x01040040, (u32) D_802A538C[D_802A5368]);
        D_802A5368++;
    }
    *pushed = n;
    *gp = g;
}
