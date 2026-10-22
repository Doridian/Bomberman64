#ifndef STRUCTS_H
#define STRUCTS_H

/*
 * Structures the game's C shares between files.  Nothing about them is
 * understood yet: fields are unk<offset>, and a structure is named only by
 * a letter until the code says more (CLAUDE.md, "Don't guess names").  A
 * field is added where some code is seen to use it; the gaps are padding
 * arrays.
 */

typedef struct {
    f32 x, y, z;
} Vec3f;

/* The structure at UnkStructA's 0x40. */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 unk34[2];
    /* 0x36 */ s16 unk36;
} UnkStructA_40;

/* What the overlays' tasks and callbacks get, and what the main_code
 * function behind the overlays' ZeroJump stub at 0x80044A20 (ovl_0E_06)
 * returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x30];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ UnkStructA_40 *unk40;
    /* 0x44 */ u8 unk44[0x28];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} UnkStructA;

#endif
