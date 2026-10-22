#include "common.h"

/* An entry of a blob's table: type 0x1A is a palette of `unk4` u16
 * colours at offset `unk8` from the blob. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_80292418; /* size 0xC */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ UnkStruct_80292418 unkC[1];
} UnkStruct_8029279C_3C;

typedef struct {
    /* 0x00 */ UnkStruct_8029279C_3C *unk0;
    /* 0x04 */ s32 unk4;
} UnkStruct_8029279C_4C_4; /* size 0x8 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStruct_8029279C_4C_4 *unk4;
} UnkStruct_8029279C_4C;

typedef struct {
    /* 0x00 */ u8 unk0[0x3C];
    /* 0x3C */ UnkStruct_8029279C_3C *unk3C;
    /* 0x40 */ u8 unk40[0xC];
    /* 0x4C */ UnkStruct_8029279C_4C *unk4C;
} UnkStruct_8029279C;

/* A saved palette: the entry, a copy of its colours, the blob. */
typedef struct {
    /* 0x00 */ UnkStruct_80292418 *unk0;
    /* 0x04 */ u16 *unk4;
    /* 0x08 */ UnkStruct_8029279C_3C *unk8;
} UnkStruct_80090080; /* size 0xC */

typedef struct {
    /* 0x00 */ UnkStruct_8029279C *unk0;
    /* 0x04 */ s32 *unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_80090380; /* size 0xC */

void *malloc(s32);
void free(void *);

static void func_80292200(s32 arg0, s32 arg1);
void func_802922A4(s32 arg0);
void func_802922C4(s32 arg0);
s32 func_80292418(UnkStruct_8029279C_3C *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);

extern UnkStruct_80090080 D_80090080[64];
extern UnkStruct_80090380 D_80090380[16];
void func_802923CC(void);
s32 func_8029279C(UnkStruct_8029279C *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
void func_802926EC(UnkStruct_8029279C *arg0);

void *D_802A1D70[] = {
    func_80292418, func_802922A4, func_802923CC, func_8029279C, func_802922C4, func_802926EC, NULL,
};

#define ROUND(x) ((x) >= 0.0f ? (x) + 0.5f : (x) - 0.5f)

void func_80292B54(void) {
    UnkStruct_80090080 *p;
    s32 i;

    func_80297D30(0x2C, D_802A1D70);
    for (p = D_80090080; p < D_80090080 + 64; p++) {
        p->unk0 = NULL;
    }
    for (i = 0; i < 16; i++) {
        D_80090380[i].unk0 = NULL;
    }
}

/* Static and inlined into its only caller: IDO -O3 still emits an empty
 * stub (jr ra; nop) for it just before that caller, which is the empty
 * "function" splat names func_80292794 (and func_80292410 below). */
static s32 func_80292794(UnkStruct_8029279C *arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg0 == D_80090380[i].unk0) {
            return i;
        }
    }
    for (i = 0; i < 16; i++) {
        if (D_80090380[i].unk0 == NULL) {
            return i;
        }
    }
    return -1;
}

s32 func_8029279C(UnkStruct_8029279C *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    s32 n;
    s32 slot;
    s32 *out;
    s32 isNew;
    s32 nlist;
    s32 i;
    UnkStruct_80292418 *entries;
    s32 j;
    s32 k;
    UnkStruct_80292418 *e2;
    UnkStruct_8029279C_3C *list[16];

    i = 0;
    n = 0;
    entries = arg0->unk3C->unkC;
    for (; i < arg0->unk3C->unk4; i++) {
        if (entries[i].unk0 == 0x1A) {
            n++;
        }
    }
    if (arg0->unk4C != NULL) {
        nlist = 0;
        for (i = 0; i < arg0->unk4C->unk0; i++) {
            j = 0;
            isNew = 1;
            for (; j < nlist; j++) {
                if (list[j] == arg0->unk4C->unk4[i].unk0) {
                    isNew = 0;
                    break;
                }
            }
            if (isNew) {
                list[nlist++] = arg0->unk4C->unk4[i].unk0;
                e2 = arg0->unk4C->unk4[i].unk0->unkC;
                for (k = 0; k < arg0->unk4C->unk4[i].unk0->unk4; k++) {
                    if (e2[k].unk0 == 0x1A) {
                        n++;
                    }
                }
            }
        }
    }
    if (n != 0) {
        slot = func_80292794(arg0);
        if (slot != -1) {
            if (D_80090380[slot].unk0 != arg0) {
                D_80090380[slot].unk0 = arg0;
                D_80090380[slot].unk4 = malloc(n * 4);
                D_80090380[slot].unk8 = n;
            }
            n = 0;
            out = D_80090380[slot].unk4;
            for (i = 0; i < arg0->unk3C->unk4; i++) {
                if (entries[i].unk0 == 0x1A) {
                    out[n++] = func_80292418(arg0->unk3C, i, arg1, arg2, arg3, arg4);
                }
            }
            if (arg0->unk4C != NULL) {
                for (j = 0; j < nlist; j++) {
                    for (k = 0; k < list[j]->unk4; k++) {
                        e2 = list[j]->unkC;
                        if (e2[k].unk0 == 0x1A) {
                            out[n++] = func_80292418(list[j], k, arg1, arg2, arg3, arg4);
                        }
                    }
                }
            }
        }
    }
    return slot;
}

void func_802926EC(UnkStruct_8029279C *arg0) {
    s32 i;
    s32 j;

    for (i = 0; i < 16; i++) {
        if (arg0 == D_80090380[i].unk0) {
            for (j = 0; j < D_80090380[i].unk8; j++) {
                func_80292200(D_80090380[i].unk4[j], 1);
            }
            free(D_80090380[i].unk4);
            D_80090380[i].unk0 = NULL;
            return;
        }
    }
}

/* Static, inlined into func_80292418; its stub is the empty func_80292410. */
static s32 func_80292410(UnkStruct_8029279C_3C *blob, UnkStruct_80292418 *entry) {
    s32 i;
    u16 *dst;
    u16 *src;
    s32 j;

    for (i = 0; i < 64; i++) {
        if (entry == D_80090080[i].unk0) {
            return i;
        }
    }
    for (i = 0; i < 64; i++) {
        if (D_80090080[i].unk0 == NULL) {
            D_80090080[i].unk0 = entry;
            D_80090080[i].unk8 = blob;
            D_80090080[i].unk4 = malloc(entry->unk4 * 2);
            dst = D_80090080[i].unk4;
            src = (u16 *) (entry->unk8 + (u8 *) blob);
            for (j = 0; j < entry->unk4; j++) {
                *dst = *src;
                dst++;
                src++;
            }
            return i;
        }
    }
    return -1;
}

/* The colour is read through `src` each time: with a local copy, IDO keeps
 * arg0 in a register (and arg3 in $s0) where the original reloads arg0
 * from its home slot. */
s32 func_80292418(UnkStruct_8029279C_3C *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5) {
    s32 slot;
    s32 i;
    UnkStruct_80292418 *entry = &arg0->unkC[arg1];
    u16 *src;
    u16 *dst;
    s32 r;
    s32 g;
    s32 b;

    slot = func_80292410(arg0, entry);
    if (slot != -1) {
        src = D_80090080[slot].unk4;
        dst = (u16 *) (entry->unk8 + (u8 *) arg0);
        for (i = 0; i < entry->unk4; i++) {
            r = *src >> 11;
            g = (*src >> 6) & 0x1F;
            b = (*src >> 1) & 0x1F;
            r = (s32) ROUND((arg2 - r) * arg5) + r;
            g = (s32) ROUND((arg3 - g) * arg5) + g;
            b = (s32) ROUND((arg4 - b) * arg5) + b;
            *dst = (*src & 1) + (r << 11) + (g << 6) + (b << 1);
            src++;
            dst++;
        }
    }
    return slot;
}

void func_802923CC(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_80292200(i, 0);
    }
}

void func_8029236C(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (D_80090380[i].unk0 != NULL) {
            func_802922C4(i);
        }
    }
}

void func_802922C4(s32 arg0) {
    s32 i;

    if (arg0 != -1 && D_80090380[arg0].unk0 != NULL) {
        for (i = 0; i < D_80090380[arg0].unk8; i++) {
            func_80292200(D_80090380[arg0].unk4[i], 1);
        }
        free(D_80090380[arg0].unk4);
        D_80090380[arg0].unk0 = NULL;
    }
}

void func_802922A4(s32 arg0) {
    func_80292200(arg0, 1);
}

static void func_80292200(s32 arg0, s32 arg1) {
    UnkStruct_80090080 *e;
    UnkStruct_80292418 *entry;
    UnkStruct_8029279C_3C *base;
    u16 *dst;
    u16 *src;
    s32 i;

    if (arg0 != -1) {
        e = &D_80090080[arg0];
        entry = e->unk0;
        if (entry != NULL) {
            base = e->unk8;
            src = e->unk4;
            dst = (u16 *) (entry->unk8 + (u8 *) base);
            e->unk0 = NULL;
            if (arg1) {
                for (i = 0; i < entry->unk4; i++) {
                    *dst = *src;
                    src++;
                    dst++;
                }
            }
            free(e->unk4);
        }
    }
}
