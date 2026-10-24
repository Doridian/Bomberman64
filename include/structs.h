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
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 unk34[2];
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 unk38[0x10];
    /* 0x48 */ struct UnkStructA_40_48 *unk48;
} UnkStructA_40;

/* The structure at UnkStructA_40's 0x48, and the one at its 0x4. */
typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStructA_40_48_4;

typedef struct UnkStructA_40_48 {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ UnkStructA_40_48_4 *unk4;
} UnkStructA_40_48;

/* What the overlays' tasks and callbacks get, and what the main_code
 * function behind the overlays' ZeroJump stub at 0x80044A20 (ovl_0E_06)
 * returns. */
typedef struct {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14[4];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[8];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ UnkStructA_40 *unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ u8 unk50[4];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} UnkStructA;

/* What the main_code function behind the overlays' ZeroJump stub at
 * 0x80043BE8 (ovl_17_04) returns. */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 unk4[0x28];
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ u8 unk34[4];
    /* 0x38 */ s32 unk38;
} UnkStructB;

/* What the main_code function behind the overlays' ZeroJump stub at
 * 0x80044690 (ovl_17_03) returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x1C];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ u8 unk48[4];
    /* 0x4C */ f32 unk4C;
} UnkStructC;

#endif
