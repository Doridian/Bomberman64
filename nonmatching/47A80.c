/*
 * NON_MATCHING: main_code's 47A80, complete: five functions (us
 * 0x8022D280-0x8022DB00) that build a model's display list from its joint
 * tree. Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 0, eu 0, jp 0
 *
 * fcmp counts a static with the global before it. All five functions
 * match in us, eu and jp. In func_8022D414 the call's joint
 * address is `idx * 48 + bj` (the multiply first, so ugen evaluates it
 * first and gives it t8, and the add is t0,v1), while j is
 * `&((Joint *)bj)[idx]`; with bj a variable uopt doesn't reassociate the
 * sum. func_8022D58C's case 6 is gbi.h's gDPSetHilite1Tile on a Hilite
 * (D_802A2D50, int fields), expanded exactly as the SDK does: its
 * `& 0xfff` arguments get a second `& 0xfff` from _SHIFTL, and the
 * redundant `and`s (each one ugen temp, deleted by as1) are what put
 * ugen's temps in the original's registers.
 */
#include "common.h"

/* A model's display list, built from its joint tree: one matrix per joint
 * with a translation or rotation, a segment-6 display list per mesh. */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

#define GFX2(pkt, a, b) { Gfx *_g = (Gfx *) (pkt); _g->w0 = (a); _g->w1 = (b); }

/* gbi.h's Hilite and gDPSetHilite1Tile (through gDPSetTileSize and
 * gDPLoadTileGeneric, mbi.h's _SHIFTL), on this file's Gfx */
typedef struct {
    int x1, y1, x2, y2;
} Hilite_t;

typedef union {
    Hilite_t h;
    long int force_structure_alignment[4];
} Hilite;

#define _SHIFTL(v, s, w) \
    ((unsigned int) (((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define gDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
    _g->w0 = _SHIFTL(c, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12); \
    _g->w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12); \
}
#define gDPSetTileSize(pkt, t, uls, ult, lrs, lrt) \
    gDPLoadTileGeneric(pkt, 0xF2, t, uls, ult, lrs, lrt)
#define gDPSetHilite1Tile(pkt, tile, hilite, width, height) \
    gDPSetTileSize(pkt, tile, (hilite)->h.x1 & 0xfff, (hilite)->h.y1 & 0xfff, \
        ((((width)-1)*4)+(hilite)->h.x1) & 0xfff, ((((height)-1)*4)+(hilite)->h.y1) & 0xfff)

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
extern Hilite D_802A2D50;
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
            GFX2(g++, 0x06000000, (u32) D_8029FCC8);
            gDPSetHilite1Tile(g++, 0, &D_802A2D50, 32, 32);
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
