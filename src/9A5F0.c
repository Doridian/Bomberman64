#include "common.h"

/* The object func_8022A6C4 makes for a text slot. */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x14];
    /* 0x34 */ s16 unk34;
} UnkStruct_80280A74;

/* The image header func_80280814 writes at the start of a slot's buffer. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStruct_80280814_C;

typedef struct {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ UnkStruct_80280814_C unkC;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ u8 unk28[0x20];
} UnkStruct_80280814;

/* A text slot, 27 of them. */
typedef struct {
    /* 0x00 */ UnkStruct_80280A74 *unk0;
    /* 0x04 */ UnkStruct_80280814 *unk4;
    /* 0x08 */ u8 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
} UnkStruct_800BCAF0; /* size 0x1C */

/* A glyph's extent in the proportional font. */
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
} UnkStruct_802A1630;

void *malloc(u32);
void free(void *);
void func_80225CCC(struct UnkStruct_80225CC0 *file, s32 offset, s32 whence);

void func_8027FDF0(s32 arg0);
void func_80280028(u8 *src, u8 *dst, u16 col, u16 row, u16 width, u16 height, s32 draw);
static void func_8028014C(u8 *src, u8 *dst, s32 x, u16 row, u16 width, s32 off, s32 draw);
static void func_80280020(u8 *dst, s32 x, u16 row, u16 width);
s32 func_80280274();
void func_80280358(u8 *arg0, u8 *arg1, u16 arg2, u16 arg3);
void func_802800B4_jp(u8 *arg0, u8 *arg1, u16 arg2, u16 arg3);
void func_802807A8(u8 *arg0, u8 arg1);
void func_80280814(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5);
void func_80280918(u8 *arg0, s32 *arg1, s32 *arg2);
void func_802809A0(s32 arg0);
void func_802809F0(s32 arg0);
s32 func_80280A40(s32 arg0);
s32 func_80280A74(s32 arg0, u8 *arg1, u8 arg2);
void func_80280BD0(s32 arg0, u8 *arg1, u8 arg2);
s32 func_80280C08(u8 *arg0);
s32 func_80280DB4(s32 arg0);
void func_80280E4C(s32 arg0, f32 arg1, f32 arg2);
void func_80280EB0(s32 arg0, u16 arg1, u16 arg2);
s32 func_80280F24(s32 *arg0);
s32 func_802810A0(u8 *arg0, u16 arg1, u16 arg2, f32 arg3, f32 arg4, u8 arg5);
void func_802811F0(u8 *arg0, u16 arg1, u16 arg2, f32 arg3, f32 arg4, u8 arg5);
void func_8028124C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
static void func_80281270(u8 *, u8 *);
s32 func_80281278(u8 *arg0, u16 arg1, u16 arg2, f32 arg3, f32 arg4, u8 arg5);
UnkStruct_80280A74 *func_80281444(s32 arg0);
void func_80281464(s32 arg0, f32 arg1, f32 arg2);
void func_802814D8(s32 arg0, u16 arg1, u16 arg2);
void func_8028155C(void);

extern UnkStruct_800BCAF0 D_800BCAF0[27];
extern s32 D_802AC5CC;

#if !VERSION_JP
s32 D_802B0220;

/* The proportional font's glyph extents (func_80280358, func_80280C08). */
UnkStruct_802A1630 D_802A1630[256] = {
    { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 },
    { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 },
    { 2, 22 }, { 4, 20 }, { 2, 22 }, { 2, 22 }, { 2, 24 }, { 0, 22 }, { 0, 24 }, { 0, 22 },
    { 2, 22 }, { 0, 24 }, { 2, 22 }, { 2, 22 }, { 2, 22 }, { 2, 22 }, { 2, 20 }, { 4, 20 },
    { 2, 24 }, { 2, 24 }, { 6, 18 }, { 4, 20 }, { 2, 22 }, { 4, 20 }, { 0, 22 }, { 2, 22 },
    { 2, 22 }, { 2, 20 }, { 0, 24 }, { 2, 22 }, { 2, 20 }, { 2, 22 }, { 2, 22 }, { 2, 22 },
    { 0, 24 }, { 2, 22 }, { 2, 20 }, { 2, 22 }, { 0, 12 }, { 0, 12 }, { 0, 12 }, { 0, 12 },
    { 0, 12 }, { 0, 12 }, { 4, 20 }, { 4, 20 }, { 4, 20 }, { 4, 20 }, { 4, 20 }, { 6, 18 },
    { 4, 20 }, { 4, 20 }, { 8, 16 }, { 6, 16 }, { 4, 20 }, { 6, 16 }, { 0, 24 }, { 2, 20 },
    { 4, 20 }, { 2, 20 }, { 2, 22 }, { 6, 18 }, { 4, 20 }, { 6, 18 }, { 4, 20 }, { 2, 20 },
    { 0, 24 }, { 2, 20 }, { 2, 20 }, { 4, 20 }, { 0, 12 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 },
    { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 24 }, { 0, 12 }, { 4, 18 }, { 2, 22 },
    { 4, 12 }, { 0, 22 }, { 0, 24 }, { 4, 22 }, { 2, 10 }, { 0, 12 }, { 0, 12 }, { 0, 12 },
};
#endif
s32 D_802A1A30 = 0;
s32 D_802A1A34 = 0x47;
s32 D_802A1A38 = 24;
s32 D_802A1A3C = 24;
s32 D_802A1A40 = 0;
#if !VERSION_JP
s32 D_802A1A44 = 0;
#endif

void *D_802A1A48[] = {
    func_8028155C, func_802810A0, func_80280DB4, func_80280A74, func_80280EB0, func_802814D8, func_80280E4C,
    func_80281464, func_80281444, func_80281278, func_8028124C,
#if !VERSION_JP
    func_80280C08, func_802811F0, func_80280BD0,
#endif
};

void func_802815EC(void) {
    s32 i;

    func_80297D30(0x25, D_802A1A48);
    for (i = 0; i < 27; i++) {
        D_800BCAF0[i].unk8 = 0;
        D_800BCAF0[i].unk0 = NULL;
        D_800BCAF0[i].unk4 = NULL;
        D_800BCAF0[i].unkA = 0;
        D_800BCAF0[i].unkC = 0;
        D_800BCAF0[i].unk10 = 1.0f;
        D_800BCAF0[i].unk14 = 1.0f;
        D_800BCAF0[i].unk18 = 0;
        D_800BCAF0[i].unk19 = 0;
    }
    D_802A1A30 = 0;
    D_802A1A38 = 24;
    D_802A1A3C = 24;
    D_802A1A34 = 0x47;
    D_802A1A40 = 0;
}

void func_8028155C(void) {
    s32 i;

    if (D_802A1A30 != 0) {
        for (i = 0; i < 27; i++) {
            if (func_80280A40(i)) {
                func_80280DB4(i);
            }
        }
    }
    D_802A1A30 = 0;
}

void func_802814D8(s32 arg0, u16 arg1, u16 arg2) {
    if (func_80280A40(arg0)) {
        D_800BCAF0[arg0].unkA += arg1;
        D_800BCAF0[arg0].unkC += arg2;
        func_8027FDF0(arg0);
    }
}

void func_80281464(s32 arg0, f32 arg1, f32 arg2) {
    if (func_80280A40(arg0)) {
        D_800BCAF0[arg0].unk10 += arg1;
        D_800BCAF0[arg0].unk14 += arg2;
        func_8027FDF0(arg0);
    }
}

UnkStruct_80280A74 *func_80281444(s32 arg0) {
    return D_800BCAF0[arg0].unk0;
}

/* Inlined into func_80281278; its stub is at 0x80281270.  Defined above
 * its caller: below it, the loop's constants come out after the pointers'
 * set-up instead of before. */
static void func_80281270(u8 *dst, u8 *src) {
    s32 i;

    for (i = 0; i < 80; i++) {
        if (*src == 0x54 || (*src >= 0x3F && *src < 0x3A) || (*src >= 0xA5 && *src < 0xF6) ||
            (*src >= 0xFA && *src < 0xFF)) {
            *dst = 0x38;
        } else if (*src >= 0x3A && *src < 0x54) {
            *dst = *src + 0x66;
        } else if (*src >= 0x55 && *src < 0xA5) {
            *dst = *src - 0x10;
        } else if (*src == 0xF6) {
            *dst = 0x34;
        } else if (*src == 0xF7) {
            *dst = 0x40;
        } else if (*src == 0xF8) {
            *dst = 0x3C;
        } else if (*src == 0xF9) {
            *dst = 0x3B;
        } else {
            *dst = *src;
        }
        if (*src == 0) {
            break;
        }
        src++;
        dst++;
    }
}

s32 func_80281278(u8 *arg0, u16 arg1, u16 arg2, f32 arg3, f32 arg4, u8 arg5) {
    u8 buf[80];
    s32 id;

    func_8028124C(8, 12, 0x48, 0x200);
    func_80281270(buf, arg0);
    id = func_802810A0(buf, arg1, arg2, arg3, arg4, arg5);
    func_8028124C(24, 24, 0x47, 0);
    return id;
}

#if !VERSION_JP
void func_8028124C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_802A1A38 = arg0;
    D_802A1A3C = arg1;
    D_802A1A34 = arg2;
    D_802A1A40 = arg3;
}
#endif

#if !VERSION_JP
void func_802811F0(u8 *arg0, u16 arg1, u16 arg2, f32 arg3, f32 arg4, u8 arg5) {
    D_802A1A44 = 1;
    func_802810A0(arg0, arg1, arg2, arg3, arg4, arg5);
    D_802A1A44 = 0;
}
#endif

s32 func_802810A0(u8 *arg0, u16 arg1, u16 arg2, f32 arg3, f32 arg4, u8 arg5) {
    s32 id;

    if (!func_80280F24(&id)) {
        return -1;
    }
    func_80280EB0(id, arg1, arg2);
    func_80280E4C(id, arg3, arg4);
    if (func_80280A74(id, arg0, arg5) == 1) {
        return id;
    }
    func_80280DB4(id);
    return -1;
}

s32 func_80280F24(s32 *arg0) {
    s32 i;

    for (i = 0; i < 27; i++) {
        if (D_800BCAF0[i].unk8 == 0) {
            D_800BCAF0[i].unk8 = 1;
            D_800BCAF0[i].unk0 = NULL;
            D_800BCAF0[i].unk4 = NULL;
            *arg0 = i;
            return 1;
        }
    }
    return 0;
}

void func_80280EB0(s32 arg0, u16 arg1, u16 arg2) {
    if (func_80280A40(arg0)) {
        D_800BCAF0[arg0].unkA = arg1;
        D_800BCAF0[arg0].unkC = arg2;
        func_8027FDF0(arg0);
    }
}

void func_80280E4C(s32 arg0, f32 arg1, f32 arg2) {
    if (func_80280A40(arg0)) {
        D_800BCAF0[arg0].unk10 = arg1;
        D_800BCAF0[arg0].unk14 = arg2;
        func_8027FDF0(arg0);
    }
}

#if !VERSION_JP
s32 func_80280DB4(s32 arg0) {
    if (!func_80280A40(arg0)) {
        return 0;
    }
    D_800BCAF0[arg0].unk8 = 0;
    func_802809F0(arg0);
    func_802809A0(arg0);
    D_802A1A30--;
    D_800BCAF0[arg0].unk0 = NULL;
    D_800BCAF0[arg0].unk4 = NULL;
    return 1;
}
#endif

#if !VERSION_JP
s32 func_80280C08(u8 *arg0) {
    s32 max;
    s32 cols;
    s32 rows;
    s32 row;
    s32 col;
    s32 i;
    s32 w;

    cols = 0;
    rows = 0;
    i = 0;
    max = 0;
    func_80280918(arg0, &cols, &rows);

    for (row = 0; row < rows; row++) {
        w = 0;
        for (col = 0; col < cols; col++) {
            if (arg0[i] == 0xFF) {
                if (col >= cols - 1) {
                    i++;
                }
            } else if (arg0[i] != 0) {
                w += D_802A1630[arg0[i]].unk2 - D_802A1630[arg0[i]].unk0;
                i++;
            }
        }
        if (max < w) {
            max = w;
        }
    }
    return max;
}
#endif

#if !VERSION_JP
void func_80280BD0(s32 arg0, u8 *arg1, u8 arg2) {
    D_802A1A44 = 1;
    func_80280A74(arg0, arg1, arg2);
    D_802A1A44 = 0;
}
#endif

s32 func_80280A74(s32 arg0, u8 *arg1, u8 arg2) {
    s32 cols = 0;
    s32 rows = 0;
    s32 size;

    if (!func_80280A40(arg0)) {
        return 0;
    }
    func_802809F0(arg0);
    func_802809A0(arg0);
    func_80280918(arg1, &cols, &rows);
    size = cols * rows * ((D_802A1A38 * D_802A1A3C) >> 1) + 0x48;
    D_800BCAF0[arg0].unk4 = malloc(size);
    func_80280814(arg0, arg1, cols, rows, size, arg2);
    D_800BCAF0[arg0].unk0 = func_8022A6C4(D_800BCAF0[arg0].unk4, 0x9E);
    D_800BCAF0[arg0].unk0->unkC |= D_802A1A40;
    D_800BCAF0[arg0].unk0->unk34 = D_802AC5CC;
    D_800BCAF0[arg0].unk18 = cols;
    D_800BCAF0[arg0].unk19 = rows;
    func_8027FDF0(arg0);
    return 1;
}

s32 func_80280A40(s32 arg0) {
    if (D_800BCAF0[arg0].unk8 == 1) {
        return 1;
    }
    return 0;
}

void func_802809F0(s32 arg0) {
    if (D_800BCAF0[arg0].unk0 != NULL) {
        func_8022A1E8(D_800BCAF0[arg0].unk0);
        D_800BCAF0[arg0].unk0 = NULL;
    }
}

void func_802809A0(s32 arg0) {
    if (D_800BCAF0[arg0].unk4 != NULL) {
        free(D_800BCAF0[arg0].unk4);
        D_800BCAF0[arg0].unk4 = NULL;
    }
}

void func_80280918(u8 *arg0, s32 *arg1, s32 *arg2) {
    s32 n;
    u8 c;

    *arg1 = 0;
    n = 0;
    *arg2 = 1;
    while (1) {
        c = *arg0++;
        if (c == 0) {
            if (*arg1 < n) {
                *arg1 = n;
            }
            return;
        }
        if (c == 0xFF) {
            n++;
            if (*arg1 < n) {
                *arg1 = n;
                n = 0;
            }
            (*arg2)++;
        } else {
            n++;
        }
    }
}

void func_80280814(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
    UnkStruct_80280814 *hdr;
    UnkStruct_80280814_C *img;

    hdr = D_800BCAF0[arg0].unk4;
    img = &D_800BCAF0[arg0].unk4->unkC;
    hdr->unk4 = 2;
    hdr->unk0 = 0x36340037;
    hdr->unk8 = 4;
    hdr->unk9 = 4;
    hdr->unkA = 4;
    hdr->unkB = 4;
    img->unk0 = 0x12;
    img->unk4 = arg2 * D_802A1A38;
    img->unk6 = arg3 * D_802A1A3C;
    img->unk8 = 0x48;
    img->unkC = 0x1A;
    img->unk14 = 0x28;
    func_802807A8(hdr->unk28, arg5);
#if VERSION_JP
    func_802800B4_jp(arg1, img->unk8 + (u8 *) hdr, arg2, arg3);
#else
    func_80280358(arg1, img->unk8 + (u8 *) hdr, arg2, arg3);
#endif
    func_80297D60(img->unk8 + (u8 *) hdr, arg4);
}

void func_802807A8(u8 *arg0, u8 arg1) {
    s32 offset;
    struct UnkStruct_80225CC0 *file;

    offset = 8;
    file = func_80226604(D_802A1A34, 1);
    offset += arg1 * 32;
    func_80225CCC(file, offset, 0);
    func_8022616C(arg0, 1, 0x20, file);
    func_80226368(file);
}

#if VERSION_JP
s32 func_80280274(arg0, arg1, arg2, arg3)
    struct UnkStruct_80225CC0 *arg0;
    u8 arg1;
    u8 *arg2;
    int arg3;
{
    func_80225CCC(arg0, arg3 + arg1 * ((D_802A1A38 * D_802A1A3C) >> 1), 0);
    return func_8022616C(arg2, 1, (D_802A1A38 * D_802A1A3C) >> 1, arg0);
}
#else
s32 func_80280274(arg0, arg1, arg2, arg3)
    struct UnkStruct_80225CC0 *arg0;
    u8 arg1;
    u8 *arg2;
    int arg3;
{
    if (D_802A1A34 == 0x47) {
        if (arg1 >= 0x55 && arg1 < 0xF5) {
            arg1 = 0xF9;
        }
    } else {
        if (arg1 >= 0x42 && arg1 < 0x95) {
            arg1 = 0x3B;
        }
    }
    func_80225CCC(arg0, arg3 + arg1 * ((D_802A1A38 * D_802A1A3C) >> 1), 0);
    return func_8022616C(arg2, 1, (D_802A1A38 * D_802A1A3C) >> 1, arg0);
}
#endif

void func_80280028(u8 *src, u8 *dst, u16 col, u16 row, u16 width, u16 height, s32 draw) {
    s32 y;
    s32 i;
    u8 *p;
    s32 xoff;
    s32 base;

    xoff = (col * D_802A1A38) >> 1;
    base = row * width * ((D_802A1A38 * D_802A1A3C) >> 1);
    dst = dst + xoff + base;
    for (y = 0; y < D_802A1A3C; y++) {
        p = dst + width * y * (D_802A1A38 >> 1);
        for (i = 0; i < (D_802A1A38 >> 1); i++) {
            if (draw) {
                p[i] = *(src + (D_802A1A3C - y - 1) * (D_802A1A38 >> 1) + i);
            } else {
                p[i] = 0;
            }
        }
    }
}

#if VERSION_JP
void func_802800B4_jp(u8 *arg0, u8 *arg1, u16 arg2, u16 arg3) {
    u8 glyph[0x120];
    s32 base = 0;
    s32 col;
    s32 row;
    s32 i;
    struct UnkStruct_80225CC0 *file;

    file = func_80226604(D_802A1A34, 1);
    func_80225CCC(file, 4, 0);
    func_8022616C((u8 *) &base, 1, 4, file);
    for (row = 0, i = 0; row < arg3; row++) {
        for (col = 0; col < arg2; col++) {
            if (arg0[i] == 0) {
                func_80280028(glyph, arg1, col, row, arg2, arg3, 0);
            } else if (arg0[i] == 0xFF) {
                func_80280028(glyph, arg1, col, row, arg2, arg3, 0);
                if (col >= arg2 - 1) {
                    i++;
                }
            } else {
                func_80280274(file, arg0[i], glyph, base);
                func_80280028(glyph, arg1, col, row, arg2, arg3, 1);
                i++;
            }
        }
    }
    func_80226368(file);
}
#else
void func_80280358(u8 *arg0, u8 *arg1, u16 arg2, u16 arg3) {
    u8 glyph[0x120];
    s32 base = 0;
    s32 col;
    s32 row;
    s32 i;
    struct UnkStruct_80225CC0 *file;
    s32 x;

    file = func_80226604(D_802A1A34, 1);
    D_802B0220 = D_802A1A38;
    func_80225CCC(file, 4, 0);
    func_8022616C((u8 *) &base, 1, 4, file);
    for (row = 0, i = 0; row < arg3; row++) {
        x = 0;
        for (col = 0; col < arg2; col++) {
            if (arg0[i] == 0) {
                if (D_802A1A44) {
                    D_802A1A38 = D_802B0220;
                    func_8028014C(glyph, arg1, x, row, arg2, 0, 0);
                } else {
                    func_80280028(glyph, arg1, col, row, arg2, arg3, 0);
                }
            } else if (arg0[i] == 0xFF) {
                if (D_802A1A44) {
                    D_802A1A38 = D_802B0220;
                    func_8028014C(glyph, arg1, x, row, arg2, 0, 0);
                } else {
                    func_80280028(glyph, arg1, col, row, arg2, arg3, 0);
                }
                if (col >= arg2 - 1) {
                    i++;
                }
            } else {
                D_802A1A38 = D_802B0220;
                func_80280274(file, arg0[i], glyph, base);
                if (D_802A1A44) {
                    D_802A1A38 = D_802A1630[arg0[i]].unk2;
                    func_8028014C(glyph, arg1, x, row, arg2, D_802A1630[arg0[i]].unk0 >> 1, 1);
                    x = x + D_802A1A38 - D_802A1630[arg0[i]].unk0;
                } else {
                    func_80280028(glyph, arg1, col, row, arg2, arg3, 1);
                }
                i++;
            }
        }
        if (D_802A1A44) {
            func_80280020(arg1, x, row, arg2);
        }
    }
    func_80226368(file);
    D_802A1A38 = D_802B0220;
}
#endif

#if !VERSION_JP
static void func_8028014C(u8 *src, u8 *dst, s32 x, u16 row, u16 width, s32 off, s32 draw) {
    s32 y;
    s32 i;
    u8 *p;
    s32 xoff;
    s32 base;

    xoff = x >> 1;
    base = row * width * ((D_802B0220 * D_802A1A3C) >> 1);
    dst = dst + xoff + base;
    for (y = 0; y < D_802A1A3C; y++) {
        p = dst + width * y * (D_802B0220 >> 1);
        for (i = 0; i < (D_802A1A38 >> 1); i++) {
            if (draw) {
                p[i] = *(src + (D_802A1A3C - y - 1) * (D_802B0220 >> 1) + i + off);
            } else {
                p[i] = 0;
            }
        }
    }
}
#endif

#if !VERSION_JP
/* Inlined into its one caller (func_80280358); IDO -O3 still emits a static
 * function inlined everywhere, as a bare `jr ra` stub, which splat counts
 * as the tail of func_8027FDF0. */
static void func_80280020(u8 *dst, s32 x, u16 row, u16 width) {
    s32 y;
    s32 i;
    u8 *p;
    s32 xoff;
    s32 base;
    s32 w;

    w = (width * D_802B0220) >> 1;
    xoff = x >> 1;
    base = row * width * ((D_802B0220 * D_802A1A3C) >> 1);
    dst = dst + xoff + base;
    for (y = 0; y < D_802A1A3C; y++) {
        p = dst + width * y * (D_802B0220 >> 1);
        for (i = 0; i < w - xoff; i++) {
            p[i] = 0;
        }
    }
}
#endif

void func_8027FDF0(s32 arg0) {
    UnkStruct_800BCAF0 *e = &D_800BCAF0[arg0];
    f32 w = e->unk10 * D_802A1A38 * e->unk18;
    f32 h = e->unk14 * D_802A1A3C * e->unk19;

    if (e->unk0 != NULL) {
        if (w >= 0.0f) {
            e->unk0->unk10 = e->unkA;
            e->unk0->unk18 = e->unkA + w;
        } else {
            e->unk0->unk10 = e->unkA - w;
            e->unk0->unk18 = e->unkA;
        }
        if (h >= 0.0f) {
            e->unk0->unk14 = e->unkC;
            e->unk0->unk1C = e->unkC + h;
        } else {
            e->unk0->unk14 = e->unkC - h;
            e->unk0->unk1C = e->unkC;
        }
    }
}

#if VERSION_JP
s32 func_80280DB4(s32 arg0) {
    if (!func_80280A40(arg0)) {
        return 0;
    }
    D_800BCAF0[arg0].unk8 = 0;
    func_802809F0(arg0);
    func_802809A0(arg0);
    D_802A1A30--;
    D_800BCAF0[arg0].unk0 = NULL;
    D_800BCAF0[arg0].unk4 = NULL;
    return 1;
}

void func_8028124C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_802A1A38 = arg0;
    D_802A1A3C = arg1;
    D_802A1A34 = arg2;
    D_802A1A40 = arg3;
}
#endif
