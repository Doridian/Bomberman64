/*
 * NON_MATCHING: ovl_0A_06's game object, complete: every function and its data
 * (.data 0x700, .rodata 0xF0, .bss 0x270 and the bss layout as the
 * original; .data differs only in callback pointers and .rodata only in
 * jump tables, both from the text's shift). The strings are us's: jp's
 * differ, and jp lacks ZeroJump 0x250B-0x250D. eu is us.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 2862, eu 2862, jp 3804
 *
 * What still differs in us (words):
 * - func_ovl0A_06_80043B5C (62; with the statics after it): 8004311C keeps
 *   an extra copy of `pressed` and doesn't share s8 for `ret = 1` (one
 *   word short); 80043250's buffer at sp+40, not 32; 800432F8's spill
 *   slot; stack offsets 4 bytes off in 800436BC; 80043E68 uses t3 where
 *   the original avoids it.
 * - func_ovl0A_06_80044BFC (49): the 9 compared against is kept in s5 in
 *   the original (ours `li at,9` each time), D_8004701C in a0.
 * - func_ovl0A_06_80044F68 (123): frame 0x50, not 0x30: the destroy loop
 *   is spilled where the original keeps s1/s2.
 * - func_ovl0A_06_80045258 and the eleven empty functions after it, with
 *   the static 800452B8 (150): 800452B8 keeps the display list pointer in
 *   v0 with a `move v1,v0` per colour command in the original; 5 words
 *   short.
 * - func_ovl0A_06_80045524 to 8004568C (1 each): the unused argument is
 *   stored to 24(sp), the original's to 0(sp) (the caller's home slot).
 */
#include "common.h"

/* what ZeroJump 0x1500 and 0x1510 return, and 0x2508 */
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
    /* 0x30 */ u8 unk30[6];
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s32 unk38;
} UnkStruct_ovl0A_06_800460E8;

/* A display list command (gbi.h's Gfx, as two words) */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_ovl0A_06_800452B8;

/* a rectangle: x, y, width, height */
typedef struct {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 unkC;
} UnkStruct_ovl0A_06_80047330;

/* a coloured rectangle: its window, its corners' colours, its place, flags
 * and the function that draws it */
typedef struct {
    /* 0x00 */ UnkStruct_ovl0A_06_800460E8 *unk0;
    /* 0x04 */ s32 *unk4;
    /* 0x08 */ s32 *unk8;
    /* 0x0C */ s32 *unkC;
    /* 0x10 */ s32 *unk10;
    /* 0x14 */ UnkStruct_ovl0A_06_80047330 unk14;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ void (*unk28)(s32, UnkStruct_ovl0A_06_800452B8 **);
} UnkStruct_ovl0A_06_80047178; /* size 0x2C */

/* what ZeroJump 0x1C05 fills in */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ u8 unk10[0xC];
} UnkStruct_ovl0A_06_80047540; /* size 0x1C */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0A_06_80045168_Inner;

typedef struct {
    /* 0x00 */ u8 unk0[0x40];
    /* 0x40 */ UnkStruct_ovl0A_06_80045168_Inner *unk40;
} UnkStruct_ovl0A_06_80045168;

typedef struct {
    f32 x, y, z;
} Vec3f_ovl0A_06;

s32 func_ovl0A_06_800456D0(u8 *, const char *, s32); /* 0x101 */
void func_ovl0A_06_80045B00(s32, s32, s32); /* 0xF00 */
s32 func_ovl0A_06_80045B18(void); /* 0xF03 */
void func_ovl0A_06_80045B70(s32); /* 0xF0E */
UnkStruct_ovl0A_06_800460E8 *func_ovl0A_06_800460E8(s32, s32); /* 0x1500 */
void func_ovl0A_06_800460F0(UnkStruct_ovl0A_06_800460E8 *); /* 0x1501 */
UnkStruct_ovl0A_06_800460E8 *func_ovl0A_06_80046168(void (*)(s32, UnkStruct_ovl0A_06_800452B8 **), s32); /* 0x1510 */
void func_ovl0A_06_80046248(f32, f32, f32); /* 0x1704 */
void func_ovl0A_06_80046268(f32, f32, f32); /* 0x1708 */
void func_ovl0A_06_80046270(f32 *, f32 *, f32 *); /* 0x1709 */
s32 func_ovl0A_06_80046558(void (*)(), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0A_06_80046568(void); /* 0x1902 */
void func_ovl0A_06_80046578(s32); /* 0x1904 */
s32 func_ovl0A_06_800465A0(void); /* 0x1909 */
s32 func_ovl0A_06_800466A0(s32); /* 0x1C02 */
s32 func_ovl0A_06_800466B0(s32); /* 0x1C04 */
s32 func_ovl0A_06_800466B8(UnkStruct_ovl0A_06_80047540 *); /* 0x1C05 */
s32 func_ovl0A_06_800466C0(void); /* 0x1C06 */
s32 func_ovl0A_06_800466C8(void); /* 0x1C07 */
s32 func_ovl0A_06_800466D0(s32); /* 0x1C08 */
void func_ovl0A_06_80046838(s32); /* 0x2000 */
void func_ovl0A_06_80046850(void); /* 0x2003 */
void func_ovl0A_06_800468A8(s32, s32, s32); /* 0x2201 */
s32 func_ovl0A_06_80046910(void); /* 0x2406 */
s32 func_ovl0A_06_80046940(u8 *, u16, u16, f32, f32, s32); /* 0x2501 */
s32 func_ovl0A_06_80046948(s32); /* 0x2502 */
void func_ovl0A_06_80046950(s32, u8 *, s32); /* 0x2503 */
void func_ovl0A_06_80046968(s32, f32, f32); /* 0x2506 */
UnkStruct_ovl0A_06_800460E8 *func_ovl0A_06_80046978(s32); /* 0x2508 */
void func_ovl0A_06_80046988(s32, s32, s32, s32); /* 0x250A */
s32 func_ovl0A_06_80046998(u8 *, u16, u16, f32, f32, s32); /* 0x250C */
void func_ovl0A_06_800469A0(s32, u8 *, s32); /* 0x250D */
void func_ovl0A_06_80046AE0(s32); /* 0x2B00 */
void func_ovl0A_06_80046B00(s32, s32, s32, s32); /* 0x2B04 */
s32 func_ovl0A_06_80046C50(s32); /* 0x2F10 */

void func_ovl0A_06_80045524(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);
void func_ovl0A_06_8004554C(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);
void func_ovl0A_06_80045574(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);
void func_ovl0A_06_8004559C(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);
void func_ovl0A_06_800455C4(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);
void func_ovl0A_06_800455EC(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);
void func_ovl0A_06_80045614(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);
void func_ovl0A_06_8004563C(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);
void func_ovl0A_06_80045664(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);
void func_ovl0A_06_8004568C(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1);

/* A sound and a wait: the wait comes out of a switch, so IDO keeps it in a
 * register rather than as an immediate (as the original does). */
#define SE(id, t)                               \
    {                                           \
        switch (t) {                            \
            case 0:                             \
                wait = 5;                      \
                break;                          \
            case 1:                             \
                wait = 15;                     \
                break;                          \
            case 2:                             \
                wait = 10;                     \
                break;                          \
            case 3:                             \
                wait = 150;                    \
                break;                          \
            case 0x18:                          \
                wait = 50;                     \
                break;                          \
            default:                            \
                wait = 0;                      \
                break;                          \
        }                                       \
        func_ovl0A_06_80043010(id, wait);      \
    }

static void func_ovl0A_06_80043010(s32 id, s32 wait);

/* .bss */
Vec3f_ovl0A_06 D_ovl0A_06_800474F0;
u8 D_ovl0A_06_800474FC[4];
Vec3f_ovl0A_06 D_ovl0A_06_80047500;
s32 D_ovl0A_06_8004750C;
u8 D_ovl0A_06_80047510[4];
s32 D_ovl0A_06_80047514;
s32 D_ovl0A_06_80047518;
u8 D_ovl0A_06_8004751C[4];
Vec3f_ovl0A_06 D_ovl0A_06_80047520;
UnkStruct_ovl0A_06_800460E8 *D_ovl0A_06_8004752C;
UnkStruct_ovl0A_06_800460E8 *D_ovl0A_06_80047530;
UnkStruct_ovl0A_06_800460E8 *D_ovl0A_06_80047534;
UnkStruct_ovl0A_06_800460E8 *D_ovl0A_06_80047538;
u8 D_ovl0A_06_8004753C[4];
UnkStruct_ovl0A_06_80047540 D_ovl0A_06_80047540[16];
u8 D_ovl0A_06_80047700[8];
s32 D_ovl0A_06_80047708[4];
UnkStruct_ovl0A_06_800460E8 *D_ovl0A_06_80047718[4];
s32 D_ovl0A_06_80047728[4];
s32 D_ovl0A_06_80047738[4];
UnkStruct_ovl0A_06_800460E8 *D_ovl0A_06_80047748[4];
s32 D_ovl0A_06_80047758;
u8 D_ovl0A_06_8004775C[4];

/* .data */
u8 D_ovl0A_06_80046D00[] = {
    0x22, 0x4C, 0x0F, 0x42, 0x4D, 0x0F, 0x28, 0x24, 0x0F, 0x4D, 0x48, 0x0F,
    0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046D14[] = {
    0x22, 0x4C, 0x0F, 0x4D, 0x41, 0x42, 0x4C, 0x0F, 0x28, 0x24, 0xF7, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046D24[] = {
    0x32, 0x3E, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046D2C[] = {
    0x27, 0x48, 0x00, 0x00,
};
u8 D_ovl0A_06_80046D30[] = {
    0x20, 0x3A, 0x46, 0x3E, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x26, 0x3E, 0x46,
    0x48, 0x4B, 0x52, 0xF7, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046D44[] = {
    0x1A, 0x45, 0x45, 0x0F, 0x1D, 0x3A, 0x4D, 0x3A, 0x0F, 0x30, 0x42, 0x45,
    0x45, 0x0F, 0x3B, 0x3E, 0x0F, 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x3D, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046D60[] = {
    0x1D, 0x3A, 0x4D, 0x3A, 0x0F, 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x3D, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046D70[] = {
    0x1D, 0x3A, 0x4D, 0x3A, 0x0F, 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x3D, 0xFF,
    0x3F, 0x3A, 0x42, 0x45, 0x4E, 0x4B, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046D88[] = {
    0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x0F, 0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046D98[] = {
    0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1C,
    0x3A, 0x47, 0x3C, 0x3E, 0x45, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046DB8[] = {
    0x27, 0x48, 0xF8, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
    0x0F, 0x20, 0x3A, 0x46, 0x3E, 0x0F, 0x1D, 0x3A, 0x4D, 0x3A, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x29, 0x3A, 0x40, 0x3E, 0x4C,
    0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046DE0[] = {
    0x4D, 0x48, 0x0F, 0x1E, 0x51, 0x42, 0x4D, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F, 0x29, 0x3A, 0x40, 0x3E, 0x4C, 0x0F, 0x1F, 0x4B, 0x3E,
    0x3E, 0x0F, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046E00[] = {
    0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45,
    0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0xFF, 0x27, 0x48, 0x4D, 0x0F, 0x1F,
    0x48, 0x4E, 0x47, 0x3D, 0xFF, 0xFF, 0x22, 0x47, 0x4C, 0x3E, 0x4B, 0x4D,
    0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45,
    0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0xFF, 0x42, 0x47, 0x4D, 0x48,
    0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F,
    0x11, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046E4C[] = {
    0x27, 0x3E, 0x50, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D,
    0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0xFF, 0x3F,
    0x48, 0x4E, 0x47, 0x3D, 0xFF, 0xFF, 0x22, 0x4D, 0x0F, 0x30, 0x42, 0x45,
    0x45, 0x0F, 0x3B, 0x3E, 0x0F, 0x2E, 0x4C, 0x3E, 0x3D, 0x0F, 0x4D, 0x48,
    0xFF, 0x2C, 0x3A, 0x4F, 0x3E, 0x0F, 0x1D, 0x3A, 0x4D, 0x3A, 0x00, 0x00,
};
u8 D_ovl0A_06_80046E88[] = {
    0x2D, 0x41, 0x3E, 0x4B, 0x3E, 0x0F, 0x42, 0x4C, 0x0F, 0x3A, 0x0F, 0x29,
    0x4B, 0x48, 0x3B, 0x45, 0x3E, 0x46, 0xFF, 0x50, 0x42, 0x4D, 0x41, 0x0F,
    0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x3A,
    0x47, 0x3D, 0xFB, 0x48, 0x4B, 0xFF, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48,
    0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44,
    0xFF, 0xFF, 0x0F, 0x0F, 0x1A, 0x0F, 0x0F, 0x2B, 0x3E, 0x42, 0x47, 0x4C,
    0x3E, 0x4B, 0x4D, 0xFF, 0x0F, 0x0F, 0x1B, 0x0F, 0x0F, 0x2B, 0x3E, 0x42,
    0x47, 0x42, 0x4D, 0x42, 0x3A, 0x45, 0x42, 0x53, 0x3E, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046EE8[] = {
    0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0x0F, 0x27, 0x48, 0x4D, 0x0F, 0x1F,
    0x48, 0x4E, 0x47, 0x3D, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046EFC[] = {
    0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x27,
    0x48, 0x4D, 0x0F, 0x29, 0x4B, 0x48, 0x49, 0x3E, 0x4B, 0x45, 0x52, 0xFF,
    0x22, 0x47, 0x4C, 0x3E, 0x4B, 0x4D, 0x3E, 0x3D, 0xFF, 0xFF, 0x29, 0x48,
    0x50, 0x3E, 0x4B, 0x0F, 0x28, 0x1F, 0x1F, 0x0F, 0x3A, 0x47, 0x3D, 0x0F,
    0x2B, 0x3E, 0x42, 0x47, 0x4C, 0x3E, 0x4B, 0x4D, 0xFF, 0x1C, 0x48, 0x47,
    0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046F44[] = {
    0x27, 0x48, 0x4D, 0x0F, 0x3A, 0x0F, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48,
    0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44,
    0xFF, 0xFF, 0x1C, 0x41, 0x3A, 0x47, 0x40, 0x3E, 0x0F, 0x4D, 0x48, 0x0F,
    0x3A, 0xFF, 0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48,
    0x45, 0x45, 0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046F80[] = {
    0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45,
    0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x1E, 0x4B, 0x4B, 0x48, 0x4B,
    0xFF, 0xFF, 0x1F, 0x3A, 0x42, 0x45, 0x3E, 0x3D, 0x0F, 0x4D, 0x48, 0x0F,
    0x1A, 0x3C, 0x3C, 0x3E, 0x4C, 0x4C, 0x0F, 0x4D, 0x41, 0x3E, 0x0F, 0x1D,
    0x3A, 0x4D, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046FB8[] = {
    0x27, 0x16, 0x14, 0x0F, 0x1C, 0x48, 0x47, 0x4D, 0x4B, 0x48, 0x45, 0x45,
    0x3E, 0x4B, 0x0F, 0x29, 0x3A, 0x44, 0x0F, 0x42, 0x4C, 0xFF, 0x27, 0x48,
    0x4D, 0x0F, 0x29, 0x4B, 0x48, 0x49, 0x3E, 0x4B, 0x45, 0x52, 0x0F, 0x22,
    0x47, 0x4C, 0x3E, 0x4B, 0x4D, 0x3E, 0x3D, 0xFF, 0xFF, 0x1E, 0x51, 0x42,
    0x4D, 0x42, 0x47, 0x40, 0x0F, 0x4D, 0x41, 0x3E, 0x0F, 0x26, 0x3E, 0x47,
    0x4E, 0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00,
};
u8 D_ovl0A_06_80046FFC[] = {
    0x2B, 0x3E, 0x3C, 0x48, 0x4B, 0x3D, 0x0F, 0x41, 0x3A, 0x4C, 0x0F, 0x3B,
    0x3E, 0x3E, 0x47, 0x0F, 0x1E, 0x4B, 0x3A, 0x4C, 0x3E, 0x3D, 0x00, 0x00,
};
s32 D_ovl0A_06_80047014 = 0;
s32 D_ovl0A_06_80047018 = 1;
s32 D_ovl0A_06_8004701C = 2;
s32 D_ovl0A_06_80047020 = 0;
s32 D_ovl0A_06_80047024 = 9;
u32 D_ovl0A_06_80047028[16] = {
    0, 0, 0, 0xFF, 0, 0, 0, 0xFF, 0, 0, 0, 0xFF, 0, 0, 0, 0xFF,
};
u8 D_ovl0A_06_80047068[4][0x20] = {
    { 0x0F, 0x10, 0x10, 0x0F, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
      0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0xF8, 0x10, 0x11, 0x12, 0x13, 0x0F, 0x0F, 0x10, 0x10, 0x10, 0x00 },
    { 0x0F, 0x10, 0x10, 0x0F, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
      0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0xF8, 0x10, 0x11, 0x12, 0x13, 0x0F, 0x0F, 0x10, 0x10, 0x10, 0x00 },
    { 0x0F, 0x10, 0x10, 0x0F, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
      0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0xF8, 0x10, 0x11, 0x12, 0x13, 0x0F, 0x0F, 0x10, 0x10, 0x10, 0x00 },
    { 0x0F, 0x10, 0x10, 0x0F, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
      0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0xF8, 0x10, 0x11, 0x12, 0x13, 0x0F, 0x0F, 0x10, 0x10, 0x10, 0x00 },
};
s32 D_ovl0A_06_800470E8[4] = { 0xDC, 0xCF, 0x43, 0xB4 };
s32 D_ovl0A_06_800470F8[4] = { 0x99, 0x5F, 0x2C, 0xB4 };
s32 D_ovl0A_06_80047108[4] = { 0x19, 0xA7, 0xC0, 0xB4 };
s32 D_ovl0A_06_80047118[4] = { 0x4F, 0x24, 0x97, 0xB4 };
s32 D_ovl0A_06_80047128[4] = { 0xE6, 0x84, 0xB9, 0xB4 };
s32 D_ovl0A_06_80047138[4] = { 0x5A, 0x13, 0x21, 0xB4 };
s32 D_ovl0A_06_80047148[4] = { 0x4D, 0x48, 0xAB, 0x8C };
s32 D_ovl0A_06_80047158[4] = { 0x1E, 0x1E, 0x1E, 0xB4 };
s32 D_ovl0A_06_80047168[4] = { 0xD6, 0xFF, 0xFA, 0xB4 };
UnkStruct_ovl0A_06_80047178 D_ovl0A_06_80047178[10] = {
    { NULL, D_ovl0A_06_800470E8, D_ovl0A_06_800470F8, D_ovl0A_06_800470E8, D_ovl0A_06_800470F8,
      { 0x3C, 0x14, 0xC8, 0x14 }, 0, func_ovl0A_06_80045524 },
    { NULL, D_ovl0A_06_80047108, D_ovl0A_06_80047118, D_ovl0A_06_80047108, D_ovl0A_06_80047118,
      { 0x1C, 0x34, 0x70, 0x12 }, 0, func_ovl0A_06_8004554C },
    { NULL, D_ovl0A_06_80047108, D_ovl0A_06_80047118, D_ovl0A_06_80047108, D_ovl0A_06_80047118,
      { 0xB4, 0x34, 0x70, 0x12 }, 0, func_ovl0A_06_80045574 },
    { NULL, D_ovl0A_06_80047108, D_ovl0A_06_80047118, D_ovl0A_06_80047108, D_ovl0A_06_80047118,
      { 0x1C, 0x4E, 0x108, 0x16 }, 0x480, func_ovl0A_06_8004559C },
    { NULL, D_ovl0A_06_80047128, D_ovl0A_06_80047138, D_ovl0A_06_80047128, D_ovl0A_06_80047138,
      { 0x1C, 0xC3, 0x70, 0x12 }, 0, func_ovl0A_06_800455C4 },
    { NULL, D_ovl0A_06_80047108, D_ovl0A_06_80047118, D_ovl0A_06_80047108, D_ovl0A_06_80047118,
      { 0x9C, 0xC4, 0x88, 0x12 }, 0, func_ovl0A_06_800455EC },
    { NULL, D_ovl0A_06_80047148, D_ovl0A_06_80047148, D_ovl0A_06_80047148, D_ovl0A_06_80047148,
      { 0x1C, 0x64, 0x108, 0x55 }, 0x480, func_ovl0A_06_80045614 },
    { NULL, D_ovl0A_06_80047168, D_ovl0A_06_80047168, D_ovl0A_06_80047168, D_ovl0A_06_80047168,
      { 0x1C, 0x34, 0x70, 0x12 }, 0x80, func_ovl0A_06_8004563C },
    { NULL, D_ovl0A_06_80047168, D_ovl0A_06_80047168, D_ovl0A_06_80047168, D_ovl0A_06_80047168,
      { 0x1C, 0xC3, 0x70, 0x12 }, 0x81, func_ovl0A_06_80045664 },
    { NULL, D_ovl0A_06_80047158, D_ovl0A_06_80047158, D_ovl0A_06_80047158, D_ovl0A_06_80047158,
      { 0, 0, 1, 1 }, 0x81, func_ovl0A_06_8004568C },
};
UnkStruct_ovl0A_06_80047330 D_ovl0A_06_80047330[6] = {
    { 0x1C, 0x34, 0x70, 0x12 },  { 0xB4, 0x34, 0x70, 0x12 },  { 0x1C, 0x64, 0x108, 0x16 },
    { 0x1C, 0x78, 0x108, 0x16 }, { 0x1C, 0x8C, 0x108, 0x16 }, { 0x1C, 0xA0, 0x108, 0x16 },
};
u8 *D_ovl0A_06_80047390[3] = {
    D_ovl0A_06_80046F80, D_ovl0A_06_80046E00, D_ovl0A_06_80046F80,
};
u8 *D_ovl0A_06_8004739C[14] = {
    D_ovl0A_06_80046E4C, D_ovl0A_06_80046EFC, D_ovl0A_06_80046F80, D_ovl0A_06_80046E88,
    D_ovl0A_06_80046F44, D_ovl0A_06_80046EE8, D_ovl0A_06_80046F80, D_ovl0A_06_80046F80,
    D_ovl0A_06_80046F80, D_ovl0A_06_80046F80, D_ovl0A_06_80046F80, D_ovl0A_06_80046F80,
    D_ovl0A_06_80046F80, D_ovl0A_06_80046F80,
};
u8 *D_ovl0A_06_800473D4 = D_ovl0A_06_80046FB8;
u8 *D_ovl0A_06_800473D8 = D_ovl0A_06_80046FFC;
s32 D_ovl0A_06_800473DC = 1;
s32 D_ovl0A_06_800473E0 = 0xFF;
s32 D_ovl0A_06_800473E4 = 0;
s32 D_ovl0A_06_800473E8 = 0;
s32 D_ovl0A_06_800473EC = 0;
s32 D_ovl0A_06_800473F0 = 0;

static void func_ovl0A_06_80043020(s32 sfx, s32 sel);
static s32 func_ovl0A_06_8004311C(void);
static void func_ovl0A_06_80043248(u8 *str, s32 value);
static void func_ovl0A_06_80043250(u8 *dest, s32 value);
static void func_ovl0A_06_800432F8(UnkStruct_ovl0A_06_80047540 *notes);
static s32 func_ovl0A_06_80043464(void);
static void func_ovl0A_06_800434CC(UnkStruct_ovl0A_06_80047178 *tbl, s32 n);
static void func_ovl0A_06_800434DC(void);
static void func_ovl0A_06_800434D4(void);
static void func_ovl0A_06_800434E4(s32 arg0);
static void func_ovl0A_06_800436BC(void);
static void func_ovl0A_06_80043B54(s32 *handles, s32 n);
void func_ovl0A_06_80043B5C(void);
static void func_ovl0A_06_80043E68(s32 msg);
static void func_ovl0A_06_8004423C(s32 state);
static s32 func_ovl0A_06_8004439C(s32 status);
static s32 func_ovl0A_06_80044400(s32 mask);
static s32 func_ovl0A_06_80044468(s32 reload);
static s32 func_ovl0A_06_80044534(s32 arg0);
static s32 func_ovl0A_06_800445BC(void);
static s32 func_ovl0A_06_800445C4(s32 mask);
static s32 func_ovl0A_06_80044620(void);
void func_ovl0A_06_80044BFC(void);
static void func_ovl0A_06_80044F50(void);
static void func_ovl0A_06_80044F58(UnkStruct_ovl0A_06_80047178 *tbl, s32 n);
static void func_ovl0A_06_80044F60(void);
void func_ovl0A_06_80044F68(s32 arg0);
void func_ovl0A_06_80045168(s32 arg0, UnkStruct_ovl0A_06_80045168 *arg1);
void func_ovl0A_06_8004519C(f32 arg0);
void func_ovl0A_06_800451E4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_06_80045240(void);
void func_ovl0A_06_80045258(void);
void func_ovl0A_06_80045260(void);
void func_ovl0A_06_80045268(void);
void func_ovl0A_06_80045270(void);
void func_ovl0A_06_80045278(void);
void func_ovl0A_06_80045280(void);
void func_ovl0A_06_80045288(void);
void func_ovl0A_06_80045290(void);
void func_ovl0A_06_80045298(void);
void func_ovl0A_06_800452A0(void);
void func_ovl0A_06_800452A8(void);
void func_ovl0A_06_800452B0(void);
static void func_ovl0A_06_800452B8(UnkStruct_ovl0A_06_80047178 *tbl, UnkStruct_ovl0A_06_800452B8 **arg1);

static void func_ovl0A_06_80043020(s32 sfx, s32 sel);
static s32 func_ovl0A_06_8004311C(void);
static void func_ovl0A_06_80043248(u8 *str, s32 value);
static void func_ovl0A_06_80043250(u8 *dest, s32 value);
static void func_ovl0A_06_800432F8(UnkStruct_ovl0A_06_80047540 *notes);
static s32 func_ovl0A_06_80043464(void);
static void func_ovl0A_06_800434CC(UnkStruct_ovl0A_06_80047178 *tbl, s32 n);
static void func_ovl0A_06_800434DC(void);
static void func_ovl0A_06_800434D4(void);
static void func_ovl0A_06_800434E4(s32 arg0);
static void func_ovl0A_06_800436BC(void);
static void func_ovl0A_06_80043B54(s32 *handles, s32 n);
void func_ovl0A_06_80043B5C(void);
static void func_ovl0A_06_80043E68(s32 msg);
static void func_ovl0A_06_8004423C(s32 state);
static s32 func_ovl0A_06_8004439C(s32 status);
static s32 func_ovl0A_06_80044400(s32 mask);
static s32 func_ovl0A_06_80044468(s32 reload);
static s32 func_ovl0A_06_80044534(s32 arg0);
static s32 func_ovl0A_06_800445BC(void);
static s32 func_ovl0A_06_800445C4(s32 mask);
static s32 func_ovl0A_06_80044620(void);
void func_ovl0A_06_80044BFC(void);
static void func_ovl0A_06_80044F50(void);
static void func_ovl0A_06_80044F58(UnkStruct_ovl0A_06_80047178 *tbl, s32 n);
static void func_ovl0A_06_80044F60(void);
void func_ovl0A_06_80044F68(s32 arg0);
void func_ovl0A_06_80045168(s32 arg0, UnkStruct_ovl0A_06_80045168 *arg1);
void func_ovl0A_06_8004519C(f32 arg0);
void func_ovl0A_06_800451E4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_06_80045240(void);
void func_ovl0A_06_80045258(void);
void func_ovl0A_06_80045260(void);
void func_ovl0A_06_80045268(void);
void func_ovl0A_06_80045270(void);
void func_ovl0A_06_80045278(void);
void func_ovl0A_06_80045280(void);
void func_ovl0A_06_80045288(void);
void func_ovl0A_06_80045290(void);
void func_ovl0A_06_80045298(void);
void func_ovl0A_06_800452A0(void);
void func_ovl0A_06_800452A8(void);
void func_ovl0A_06_800452B0(void);
static void func_ovl0A_06_800452B8(UnkStruct_ovl0A_06_80047178 *tbl, UnkStruct_ovl0A_06_800452B8 **arg1);

static void func_ovl0A_06_80043020(s32 sfx, s32 sel);
static s32 func_ovl0A_06_8004311C(void);
static void func_ovl0A_06_80043248(u8 *str, s32 value);
static void func_ovl0A_06_80043250(u8 *dest, s32 value);
static void func_ovl0A_06_800432F8(UnkStruct_ovl0A_06_80047540 *notes);
static s32 func_ovl0A_06_80043464(void);
static void func_ovl0A_06_800434CC(UnkStruct_ovl0A_06_80047178 *tbl, s32 n);
static void func_ovl0A_06_800434DC(void);
static void func_ovl0A_06_800434D4(void);
static void func_ovl0A_06_800434E4(s32 arg0);
static void func_ovl0A_06_800436BC(void);
static void func_ovl0A_06_80043B54(s32 *handles, s32 n);
void func_ovl0A_06_80043B5C(void);
static void func_ovl0A_06_80043E68(s32 msg);
static void func_ovl0A_06_8004423C(s32 state);
static s32 func_ovl0A_06_8004439C(s32 status);
static s32 func_ovl0A_06_80044400(s32 mask);
static s32 func_ovl0A_06_80044468(s32 reload);
static s32 func_ovl0A_06_80044534(s32 arg0);
static s32 func_ovl0A_06_800445BC(void);
static s32 func_ovl0A_06_800445C4(s32 mask);
static s32 func_ovl0A_06_80044620(void);
void func_ovl0A_06_80044BFC(void);
static void func_ovl0A_06_80044F50(void);
static void func_ovl0A_06_80044F58(UnkStruct_ovl0A_06_80047178 *tbl, s32 n);
static void func_ovl0A_06_80044F60(void);
void func_ovl0A_06_80044F68(s32 arg0);
void func_ovl0A_06_80045168(s32 arg0, UnkStruct_ovl0A_06_80045168 *arg1);
void func_ovl0A_06_8004519C(f32 arg0);
void func_ovl0A_06_800451E4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_06_80045240(void);
void func_ovl0A_06_80045258(void);
void func_ovl0A_06_80045260(void);
void func_ovl0A_06_80045268(void);
void func_ovl0A_06_80045270(void);
void func_ovl0A_06_80045278(void);
void func_ovl0A_06_80045280(void);
void func_ovl0A_06_80045288(void);
void func_ovl0A_06_80045290(void);
void func_ovl0A_06_80045298(void);
void func_ovl0A_06_800452A0(void);
void func_ovl0A_06_800452A8(void);
void func_ovl0A_06_800452B0(void);
static void func_ovl0A_06_800452B8(UnkStruct_ovl0A_06_80047178 *tbl, UnkStruct_ovl0A_06_800452B8 **arg1);

static void func_ovl0A_06_80043020(s32 sfx, s32 sel);
static s32 func_ovl0A_06_8004311C(void);
static void func_ovl0A_06_80043248(u8 *str, s32 value);
static void func_ovl0A_06_80043250(u8 *dest, s32 value);
static void func_ovl0A_06_800432F8(UnkStruct_ovl0A_06_80047540 *notes);
static s32 func_ovl0A_06_80043464(void);
static void func_ovl0A_06_800434CC(UnkStruct_ovl0A_06_80047178 *tbl, s32 n);
static void func_ovl0A_06_800434DC(void);
static void func_ovl0A_06_800434D4(void);
static void func_ovl0A_06_800434E4(s32 arg0);
static void func_ovl0A_06_800436BC(void);
static void func_ovl0A_06_80043B54(s32 *handles, s32 n);
void func_ovl0A_06_80043B5C(void);
static void func_ovl0A_06_80043E68(s32 msg);
static void func_ovl0A_06_8004423C(s32 state);
static s32 func_ovl0A_06_8004439C(s32 status);
static s32 func_ovl0A_06_80044400(s32 mask);
static s32 func_ovl0A_06_80044468(s32 reload);
static s32 func_ovl0A_06_80044534(s32 arg0);
static s32 func_ovl0A_06_800445BC(void);
static s32 func_ovl0A_06_800445C4(s32 mask);
static s32 func_ovl0A_06_80044620(void);
void func_ovl0A_06_80044BFC(void);
static void func_ovl0A_06_80044F50(void);
static void func_ovl0A_06_80044F58(UnkStruct_ovl0A_06_80047178 *tbl, s32 n);
static void func_ovl0A_06_80044F60(void);
void func_ovl0A_06_80044F68(s32 arg0);
void func_ovl0A_06_80045168(s32 arg0, UnkStruct_ovl0A_06_80045168 *arg1);
void func_ovl0A_06_8004519C(f32 arg0);
void func_ovl0A_06_800451E4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0A_06_80045240(void);
void func_ovl0A_06_80045258(void);
void func_ovl0A_06_80045260(void);
void func_ovl0A_06_80045268(void);
void func_ovl0A_06_80045270(void);
void func_ovl0A_06_80045278(void);
void func_ovl0A_06_80045280(void);
void func_ovl0A_06_80045288(void);
void func_ovl0A_06_80045290(void);
void func_ovl0A_06_80045298(void);
void func_ovl0A_06_800452A0(void);
void func_ovl0A_06_800452A8(void);
void func_ovl0A_06_800452B0(void);
static void func_ovl0A_06_800452B8(UnkStruct_ovl0A_06_80047178 *tbl, UnkStruct_ovl0A_06_800452B8 **arg1);

void func_ovl0A_06_8004568C(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[9], arg1);
}

void func_ovl0A_06_80045664(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[8], arg1);
}

void func_ovl0A_06_8004563C(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[7], arg1);
}

void func_ovl0A_06_80045614(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[6], arg1);
}

void func_ovl0A_06_800455EC(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[5], arg1);
}

void func_ovl0A_06_800455C4(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[4], arg1);
}

void func_ovl0A_06_8004559C(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[3], arg1);
}

void func_ovl0A_06_80045574(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[2], arg1);
}

void func_ovl0A_06_8004554C(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[1], arg1);
}

void func_ovl0A_06_80045524(s32 arg0, UnkStruct_ovl0A_06_800452B8 **arg1) {
    func_ovl0A_06_800452B8(&D_ovl0A_06_80047178[0], arg1);
}

static void func_ovl0A_06_800452B8(UnkStruct_ovl0A_06_80047178 *tbl, UnkStruct_ovl0A_06_800452B8 **arg1) {
    UnkStruct_ovl0A_06_800452B8 *gfx = *arg1;

    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0x0400103F; _g->w1 = (u32) D_ovl0A_06_80047028; }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xB2100000; _g->w1 = ((tbl->unk4[0] & 0xFF) << 24) | ((tbl->unk4[1] & 0xFF) << 16) | ((tbl->unk4[2] & 0xFF) << 8) | (tbl->unk4[3] & 0xFF); }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xB2100002; _g->w1 = ((tbl->unk8[0] & 0xFF) << 24) | ((tbl->unk8[1] & 0xFF) << 16) | ((tbl->unk8[2] & 0xFF) << 8) | (tbl->unk8[3] & 0xFF); }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xB2100004; _g->w1 = ((tbl->unkC[0] & 0xFF) << 24) | ((tbl->unkC[1] & 0xFF) << 16) | ((tbl->unkC[2] & 0xFF) << 8) | (tbl->unkC[3] & 0xFF); }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xB2100006; _g->w1 = ((tbl->unk10[0] & 0xFF) << 24) | ((tbl->unk10[1] & 0xFF) << 16) | ((tbl->unk10[2] & 0xFF) << 8) | (tbl->unk10[3] & 0xFF); }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xB2180000; _g->w1 = ((tbl->unk14.unk0 & 0x1FFF) << 18) | ((tbl->unk14.unk4 & 0x1FFF) << 2); }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xB2180002; _g->w1 = ((tbl->unk14.unk0 & 0x1FFF) << 18) | (((tbl->unk14.unk4 + tbl->unk14.unkC) & 0x1FFF) << 2); }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xB2180004; _g->w1 = (((tbl->unk14.unk0 + tbl->unk14.unk8) & 0x1FFF) << 18) | ((tbl->unk14.unk4 & 0x1FFF) << 2); }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xB2180006; _g->w1 = (((tbl->unk14.unk0 + tbl->unk14.unk8) & 0x1FFF) << 18) | (((tbl->unk14.unk4 + tbl->unk14.unkC) & 0x1FFF) << 2); }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xBF000000; _g->w1 = 0x204; }
    { UnkStruct_ovl0A_06_800452B8 *_g = (UnkStruct_ovl0A_06_800452B8 *) (gfx++); _g->w0 = 0xBF000000; _g->w1 = 0x40206; }
    *arg1 = gfx;
}

void func_ovl0A_06_800452B0(void) {
}

void func_ovl0A_06_800452A8(void) {
}

void func_ovl0A_06_800452A0(void) {
}

void func_ovl0A_06_80045298(void) {
}

void func_ovl0A_06_80045290(void) {
}

void func_ovl0A_06_80045288(void) {
}

void func_ovl0A_06_80045280(void) {
}

void func_ovl0A_06_80045278(void) {
}

void func_ovl0A_06_80045270(void) {
}

void func_ovl0A_06_80045268(void) {
}

void func_ovl0A_06_80045260(void) {
    if (0) {
        D_ovl0A_06_800474F0.x = 0;
        D_ovl0A_06_800474FC[0] = 0;
        D_ovl0A_06_80047500.x = 0;
        D_ovl0A_06_8004750C = 0;
        D_ovl0A_06_80047510[0] = 0;
        D_ovl0A_06_8004751C[0] = 0;
        D_ovl0A_06_8004753C[0] = 0;
        D_ovl0A_06_80047700[0] = 0;
        D_ovl0A_06_8004775C[0] = 0;
    }
}

void func_ovl0A_06_80045258(void) {
}

void func_ovl0A_06_80045240(void) {
    D_ovl0A_06_80047514 = -1;
    D_ovl0A_06_80047518 = -1;
}

void func_ovl0A_06_800451E4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0A_06_80046248(D_ovl0A_06_80047520.x, D_ovl0A_06_80047520.y, D_ovl0A_06_80047520.z);
    func_ovl0A_06_80046268(arg0, arg1, arg2);
    func_ovl0A_06_80046578(0xB4);
}

void func_ovl0A_06_8004519C(f32 arg0) {
    f32 sp1C;

    func_ovl0A_06_80046270(&sp1C, NULL, NULL);
    func_ovl0A_06_80046268(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0A_06_80045168(s32 arg0, UnkStruct_ovl0A_06_80045168 *arg1) {
    UnkStruct_ovl0A_06_80045168_Inner *p;

    p = arg1->unk40;
    if (1) { /* fake, as in ovl_0A_05's func_ovl0A_05_80047DF4 */
    }
    func_ovl0A_06_80046B00(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0A_06_80044F68(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl0A_06_80044F60();
            break;
        case 1:
            func_ovl0A_06_800460F0(D_ovl0A_06_8004752C);
            if (D_ovl0A_06_80047014 == 0) {
                func_ovl0A_06_800460F0(D_ovl0A_06_80047530);
                func_ovl0A_06_800460F0(D_ovl0A_06_80047534);
                func_ovl0A_06_800460F0(D_ovl0A_06_80047538);
            }
            switch (D_ovl0A_06_80047014) {
                case 0:
                    func_ovl0A_06_80044F58(D_ovl0A_06_80047178, 10);
                    break;
                case 1:
                    break;
            }
            break;
        case 3:
            func_ovl0A_06_80045B70(0);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            break;
    }
}

static void func_ovl0A_06_80044F60(void) {
    if (func_ovl0A_06_800466A0(0)) {
        func_ovl0A_06_80044F50();
        D_ovl0A_06_80047014 = 0;
        D_ovl0A_06_8004701C = 2;
        D_ovl0A_06_80047020 = 0;
        D_ovl0A_06_80047024 = 9;
        func_ovl0A_06_80046558(func_ovl0A_06_80044BFC, NULL, 0, 0, 0x130);
    } else {
        D_ovl0A_06_80047014 = 1;
        D_ovl0A_06_80047018 = 0;
        func_ovl0A_06_80046558(func_ovl0A_06_80043B5C, NULL, 0, 0, 0x130);
    }
}

static void func_ovl0A_06_80044F58(UnkStruct_ovl0A_06_80047178 *tbl, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        func_ovl0A_06_800460F0(tbl->unk0);
        tbl++;
    }
}

static void func_ovl0A_06_80044F50(void) {
    s32 i;

    D_ovl0A_06_80047540[0].unk0 = 0x7B00;
    for (i = 0; i < 16; i++) {
        D_ovl0A_06_80047540[i].unk4 = 0;
        D_ovl0A_06_80047540[i].unk8 = 0;
        D_ovl0A_06_80047540[i].unkC[0] = 0;
        D_ovl0A_06_80047540[i].unk10[0] = 0;
    }
}

void func_ovl0A_06_80044BFC(void) {
    s32 ret;
    s32 counter = 0;
    s32 status;

    func_ovl0A_06_800436BC();
    D_ovl0A_06_80047178[7].unk0->unk18 = 10.0f;
    D_ovl0A_06_80047178[8].unk0->unk18 = 10.0f;
    D_ovl0A_06_80047178[9].unk0->unk18 = -100.0f;
    D_ovl0A_06_80047178[8].unk0->unkC |= 1;
    D_ovl0A_06_80047178[9].unk0->unkC |= 1;
    D_ovl0A_06_80047178[9].unk14.unk8 = 1;
    D_ovl0A_06_80047178[9].unk14.unkC = 1;
    if (func_ovl0A_06_800466A0(0) == 1 && D_ovl0A_06_80047024 == 9) {
        func_ovl0A_06_8004423C(2);
    } else {
        if (func_ovl0A_06_800466A0(0) != 1) {
            func_ovl0A_06_8004423C(func_ovl0A_06_800466A0(0) + 10);
        } else {
            func_ovl0A_06_8004423C(D_ovl0A_06_80047024 + 10);
        }
        D_ovl0A_06_80047024 = 9;
    }
    do {
        if (D_ovl0A_06_800473DC) {
            D_ovl0A_06_800473E0 -= 10;
            if (D_ovl0A_06_800473E0 <= 0) {
                D_ovl0A_06_800473E0 = 0;
                D_ovl0A_06_800473DC = 0;
            }
        } else {
            D_ovl0A_06_800473E0 += 10;
            if (D_ovl0A_06_800473E0 >= 0xFF) {
                D_ovl0A_06_800473E0 = 0xFF;
                D_ovl0A_06_800473DC = 1;
            }
        }
        switch (D_ovl0A_06_8004701C) {
            case 0:
                D_ovl0A_06_80047168[1] = 0;
                D_ovl0A_06_80047168[2] = 0;
                D_ovl0A_06_80047168[0] = D_ovl0A_06_800473E0;
                break;
            case 1:
                D_ovl0A_06_80047168[0] = 0;
                D_ovl0A_06_80047168[2] = 0;
                D_ovl0A_06_80047168[1] = D_ovl0A_06_800473E0;
                break;
            case 2:
            case 3:
            case 4:
            case 5:
                D_ovl0A_06_80047168[2] = 0;
                D_ovl0A_06_80047168[0] = D_ovl0A_06_800473E0;
                D_ovl0A_06_80047168[1] = D_ovl0A_06_800473E0;
                break;
        }
        if (D_ovl0A_06_8004701C < 10) {
            counter++;
            if (counter >= 20) {
                status = func_ovl0A_06_800466C0();
                counter = 0;
                if (status != 1) {
                    if (D_ovl0A_06_8004701C == 0 || D_ovl0A_06_8004701C == 1) {
                        func_ovl0A_06_8004423C(2);
                    }
                    func_ovl0A_06_8004423C(status + 10);
                }
            }
        }
        ret = func_ovl0A_06_80044620();
        func_ovl0A_06_800465A0();
    } while (ret != 0);
    func_ovl0A_06_80045B00(0x20, 0x10, 2);
    func_ovl0A_06_80043B54(D_ovl0A_06_80047738, 4);
    func_ovl0A_06_80043B54(D_ovl0A_06_80047708, 4);
    func_ovl0A_06_80046568();
}

static s32 func_ovl0A_06_80044620(void) {
    static s32 D_ovl0A_06_800473F4 = 0;
    static s32 D_ovl0A_06_800473F8 = 0;
    s32 status;

    D_ovl0A_06_800473F0 = func_ovl0A_06_80046910();
    D_ovl0A_06_800473EC = func_ovl0A_06_80045B18();
    if (D_ovl0A_06_8004701C >= 2 && D_ovl0A_06_8004701C < 6 && func_ovl0A_06_80044400(0x4000)) {
        return 0;
    }
    switch (D_ovl0A_06_8004701C) {
        case 0:
            if (func_ovl0A_06_800445C4(0x100)) {
                func_ovl0A_06_8004423C(1);
            } else if (func_ovl0A_06_80044400(0x8000)) {
                status = func_ovl0A_06_800466D0(D_ovl0A_06_80047020 * 4 + D_ovl0A_06_800473F4 - 2);
                if (status == 9) {
                    status = func_ovl0A_06_80044534(1);
                    func_ovl0A_06_8004423C(D_ovl0A_06_800473F4);
                    if (status != 9 && status != 1) {
                        func_ovl0A_06_8004423C(status + 10);
                    } else {
                        func_ovl0A_06_8004423C(0x1B);
                    }
                } else {
                    func_ovl0A_06_8004423C(D_ovl0A_06_800473F4);
                    func_ovl0A_06_8004423C(status + 10);
                }
            } else if (func_ovl0A_06_80044400(0x4000)) {
                func_ovl0A_06_8004423C(D_ovl0A_06_800473F4);
            }
            break;
        case 1:
            if (func_ovl0A_06_800445C4(0x200)) {
                func_ovl0A_06_8004423C(0);
            } else if (func_ovl0A_06_80044400(0x8000)) {
                func_ovl0A_06_8004423C(D_ovl0A_06_800473F4);
            } else if (func_ovl0A_06_80044400(0x4000)) {
                func_ovl0A_06_8004423C(D_ovl0A_06_800473F4);
            }
            break;
        case 2:
            if (D_ovl0A_06_80047020 > 0 && func_ovl0A_06_800445C4(0x800)) {
                D_ovl0A_06_80047020--;
                func_ovl0A_06_80044468(0);
                func_ovl0A_06_8004423C(5);
            } else if (func_ovl0A_06_800445C4(0x400)) {
                func_ovl0A_06_8004423C(D_ovl0A_06_8004701C + 1);
            } else if (func_ovl0A_06_80044400(0x8000)) {
                D_ovl0A_06_800473F4 = D_ovl0A_06_8004701C;
                func_ovl0A_06_8004423C(1);
            } else if (func_ovl0A_06_80044400(0x4000)) {
                func_ovl0A_06_8004423C(0);
            }
            break;
        case 3:
        case 4:
            if (func_ovl0A_06_800445C4(0x400)) {
                func_ovl0A_06_8004423C(D_ovl0A_06_8004701C + 1);
            } else if (func_ovl0A_06_800445C4(0x800)) {
                func_ovl0A_06_8004423C(D_ovl0A_06_8004701C - 1);
            } else if (func_ovl0A_06_80044400(0x8000)) {
                D_ovl0A_06_800473F4 = D_ovl0A_06_8004701C;
                func_ovl0A_06_8004423C(1);
            } else if (func_ovl0A_06_80044400(0x4000)) {
                func_ovl0A_06_8004423C(0);
            }
            break;
        case 5:
            if (D_ovl0A_06_80047020 < 3 && func_ovl0A_06_800445C4(0x400)) {
                D_ovl0A_06_80047020++;
                func_ovl0A_06_80044468(0);
                func_ovl0A_06_8004423C(2);
            } else if (func_ovl0A_06_800445C4(0x800)) {
                func_ovl0A_06_8004423C(D_ovl0A_06_8004701C - 1);
            } else if (func_ovl0A_06_80044400(0x8000)) {
                D_ovl0A_06_800473F4 = D_ovl0A_06_8004701C;
                func_ovl0A_06_8004423C(1);
            } else if (func_ovl0A_06_80044400(0x4000)) {
                func_ovl0A_06_8004423C(0);
            }
            break;
        case 11:
        case 18:
        case 19:
            func_ovl0A_06_80043E68(0);
            func_ovl0A_06_8004423C(2);
            D_ovl0A_06_800473F8 = 0;
            break;
        case 10:
            if (func_ovl0A_06_80044400(0x8000) || func_ovl0A_06_80044400(0x4000)) {
                if (D_ovl0A_06_800473F8) {
                    D_ovl0A_06_800473F8 = func_ovl0A_06_800445BC() ? 1 : 0;
                } else {
                    func_ovl0A_06_8004439C(func_ovl0A_06_80044534(0));
                }
                if (D_ovl0A_06_800473F8 == 0 && func_ovl0A_06_800466C0() == 0) {
                    func_ovl0A_06_80043E68(0);
                    func_ovl0A_06_8004423C(0x1A);
                }
            }
            break;
        case 12:
        case 13:
        case 14:
        case 16:
        case 17:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
            if (func_ovl0A_06_80044400(0x8000) || func_ovl0A_06_80044400(0x4000)) {
                func_ovl0A_06_800445BC();
                D_ovl0A_06_800473F8 = 0;
            }
            break;
        case 27:
            if (func_ovl0A_06_80044400(0x8000) || func_ovl0A_06_80044400(0x4000)) {
                func_ovl0A_06_80043E68(0);
                func_ovl0A_06_8004423C(D_ovl0A_06_800473F4);
                D_ovl0A_06_800473F8 = 0;
            }
            break;
        case 26:
            func_ovl0A_06_80046578(0xB4);
            func_ovl0A_06_80043E68(0);
            return 0;
        case 15:
            if (func_ovl0A_06_80044400(0x8000)) {
                if (func_ovl0A_06_800445BC()) {
                    D_ovl0A_06_800473F8 = 1;
                } else {
                    D_ovl0A_06_800473F8 = 0;
                }
            } else if (func_ovl0A_06_80044400(0x4000)) {
                if (func_ovl0A_06_8004439C(func_ovl0A_06_800466C8())) {
                    D_ovl0A_06_800473F8 = 1;
                } else {
                    D_ovl0A_06_800473F8 = 0;
                }
            }
            break;
    }
    return 1;
}

static s32 func_ovl0A_06_800445C4(s32 mask) {
    s32 wait;
    s32 ret = 0;

    if ((D_ovl0A_06_800473F0 & mask) || (D_ovl0A_06_800473EC & mask)) {
        ret = 1;
        SE(0, 0);
    }
    return ret;
}

static s32 func_ovl0A_06_800445BC(void) {
    return func_ovl0A_06_8004439C(func_ovl0A_06_80044534(1));
}

static s32 func_ovl0A_06_80044534(s32 arg0) {
    s32 ret;

    if (arg0) {
        ret = func_ovl0A_06_800466B0(0);
    } else {
        ret = func_ovl0A_06_800466C0();
    }
    if (ret == 1 || ret == 9) {
        ret = func_ovl0A_06_80044468(1);
        func_ovl0A_06_800469A0(D_ovl0A_06_80047738[3], D_ovl0A_06_80046DE0, 0);
        D_ovl0A_06_80047748[3] = func_ovl0A_06_80046978(D_ovl0A_06_80047738[3]);
    }
    return ret;
}

static s32 func_ovl0A_06_80044468(s32 reload) {
    s32 ret = 9;
    s32 i;

    if (reload) {
        ret = func_ovl0A_06_80043464();
    } else {
        func_ovl0A_06_800432F8(D_ovl0A_06_80047540);
    }
    if (ret == 9) {
        func_ovl0A_06_80046988(8, 0xC, 0x48, 0x200);
        for (i = 0; i < 4; i++) {
            func_ovl0A_06_80046950(D_ovl0A_06_80047708[i], D_ovl0A_06_80047068[i], 0);
            D_ovl0A_06_80047718[i] = func_ovl0A_06_80046978(D_ovl0A_06_80047708[i]);
        }
        func_ovl0A_06_80046988(0x18, 0x18, 0x47, 0);
    }
    return ret;
}

static s32 func_ovl0A_06_80044400(s32 mask) {
    s32 wait;
    s32 ret = 0;

    if (D_ovl0A_06_800473EC & mask) {
        ret = 1;
        if (mask == 0x8000) {
            SE(1, 1);
        } else {
            SE(2, 2);
        }
    }
    return ret;
}

static s32 func_ovl0A_06_8004439C(s32 status) {
    s32 ret = 0;

    func_ovl0A_06_80043E68(0);
    func_ovl0A_06_80046578(2);
    if (status == 9 || status == 1) {
        func_ovl0A_06_8004423C(D_ovl0A_06_800473E8);
    } else {
        ret = 1;
        func_ovl0A_06_8004423C(status + 10);
    }
    return ret;
}

static void func_ovl0A_06_8004423C(s32 state) {
    if (state >= 10) {
        if (D_ovl0A_06_8004701C < 10) {
            D_ovl0A_06_800473E8 = D_ovl0A_06_8004701C;
        }
        D_ovl0A_06_800473E4 = 0;
        func_ovl0A_06_80043E68(state - 9);
    } else if (state >= 2) {
        D_ovl0A_06_80047178[7].unk14.unk0 = D_ovl0A_06_80047330[state].unk0;
        D_ovl0A_06_80047178[7].unk14.unk4 = D_ovl0A_06_80047330[state].unk4;
        D_ovl0A_06_80047178[7].unk14.unk8 = D_ovl0A_06_80047330[state].unk8;
        D_ovl0A_06_80047178[7].unk14.unkC = D_ovl0A_06_80047330[state].unkC;
        D_ovl0A_06_80047178[8].unk0->unkC |= 1;
    } else {
        D_ovl0A_06_80047178[8].unk14.unk0 = D_ovl0A_06_80047330[state].unk0;
        D_ovl0A_06_80047178[8].unk14.unk4 = D_ovl0A_06_80047330[state].unk4;
        D_ovl0A_06_80047178[8].unk14.unk8 = D_ovl0A_06_80047330[state].unk8;
        D_ovl0A_06_80047178[8].unk14.unkC = D_ovl0A_06_80047330[state].unkC;
        D_ovl0A_06_80047178[8].unk0->unkC &= ~1;
        if (state == 0) {
            func_ovl0A_06_800434E4(1);
        } else {
            func_ovl0A_06_800434E4(2);
        }
    }
    if (D_ovl0A_06_8004701C < 2 && state >= 2) {
        func_ovl0A_06_800434E4(0);
    }
    D_ovl0A_06_800473DC = 1;
    D_ovl0A_06_800473E0 = 0xFF;
    D_ovl0A_06_8004701C = state;
}

static void func_ovl0A_06_80043E68(s32 msg) {
    s32 wait;
    s16 alpha = 0x3C;
    UnkStruct_ovl0A_06_800460E8 **p;
    u8 **str;
    s32 i;

    if (msg != 0) {
        if (msg == 0x11) {
            alpha = 0x1E;
        }
        D_ovl0A_06_80047178[9].unk0->unkC &= ~1;
        D_ovl0A_06_80047178[9].unk0->unk18 = 20.0f;
        D_ovl0A_06_80047178[9].unk14.unk8 = 320;
        D_ovl0A_06_80047178[9].unk14.unkC = 240;
        D_ovl0A_06_8004752C->unkC |= 0x80;
        D_ovl0A_06_8004752C->unk36 = alpha;
        D_ovl0A_06_80047530->unkC |= 0x80;
        D_ovl0A_06_80047530->unk36 = alpha;
        D_ovl0A_06_80047534->unkC |= 0x80;
        D_ovl0A_06_80047534->unk36 = alpha;
        D_ovl0A_06_80047538->unkC |= 0x80;
        D_ovl0A_06_80047538->unk36 = alpha;
        for (p = D_ovl0A_06_80047748; p < &D_ovl0A_06_80047748[4]; p++) {
            (*p)->unkC |= 0x80;
            (*p)->unk36 = alpha;
        }
        for (i = 0; i < 4; i++) {
            D_ovl0A_06_80047718[i]->unkC |= 0x80;
            D_ovl0A_06_80047718[i]->unk36 = alpha;
        }
        str = &D_ovl0A_06_80047390[msg];
        D_ovl0A_06_80047758 = func_ovl0A_06_80046998(*str, 0x26, 0x46, 0.65f, 0.833f, 0);
        if (str == &D_ovl0A_06_800473D4 || str == &D_ovl0A_06_800473D8) {
            SE(1, 1);
        } else if (str != D_ovl0A_06_8004739C) {
            SE(0x18, 0x18);
        }
        func_ovl0A_06_80046578(0x1E);
    } else {
        D_ovl0A_06_80047178[9].unk0->unkC |= 1;
        D_ovl0A_06_80047178[9].unk0->unk18 = -100.0f;
        D_ovl0A_06_80047178[9].unk14.unk8 = 1;
        D_ovl0A_06_80047178[9].unk14.unkC = 1;
        D_ovl0A_06_8004752C->unkC &= ~0x80;
        D_ovl0A_06_8004752C->unk36 = 0xFF;
        D_ovl0A_06_80047530->unkC &= ~0x80;
        D_ovl0A_06_80047530->unk36 = 0xFF;
        D_ovl0A_06_80047534->unkC &= ~0x80;
        D_ovl0A_06_80047534->unk36 = 0xFF;
        D_ovl0A_06_80047538->unkC &= ~0x80;
        D_ovl0A_06_80047538->unk36 = 0xFF;
        for (p = D_ovl0A_06_80047748; p < &D_ovl0A_06_80047748[4]; p++) {
            (*p)->unkC &= ~0x80;
            (*p)->unk36 = 0xFF;
        }
        for (i = 0; i < 4; i++) {
            D_ovl0A_06_80047718[i]->unkC &= ~0x80;
            D_ovl0A_06_80047718[i]->unk36 = 0xFF;
        }
        func_ovl0A_06_80046948(D_ovl0A_06_80047758);
    }
}

void func_ovl0A_06_80043B5C(void) {
    s32 erase = 1;
    s32 a;
    s32 b;
    s32 msg;
    s32 err;
    s32 wait;

    func_ovl0A_06_800436BC();
    if (func_ovl0A_06_8004311C() == 2) {
        a = func_ovl0A_06_80046998(D_ovl0A_06_80046D44, 0x23, 0x41, 0.75f, 1.2f, 0);
        b = func_ovl0A_06_80046998(D_ovl0A_06_80046D14, 0x23, 0x69, 0.75f, 1.2f, 0);
        func_ovl0A_06_80046948(D_ovl0A_06_80047728[0]);
        func_ovl0A_06_80046948(D_ovl0A_06_80047728[1]);
        D_ovl0A_06_80047728[0] = a;
        D_ovl0A_06_80047728[1] = b;
        func_ovl0A_06_800469A0(D_ovl0A_06_80047728[2], D_ovl0A_06_80046D24, 1);
        func_ovl0A_06_80046968(D_ovl0A_06_80047728[2], 1.0f, 1.0f);
        func_ovl0A_06_80046968(D_ovl0A_06_80047728[3], 1.0f, 1.0f);
        if (func_ovl0A_06_8004311C() == 2) {
            erase = 0;
            err = func_ovl0A_06_80046C50(0x20);
            func_ovl0A_06_80043B54(D_ovl0A_06_80047728, 4);
            if (err == 0) {
                msg = func_ovl0A_06_80046998(D_ovl0A_06_80046D60, 0x46, 0x69, 1.0f, 1.0f, 0);
                SE(1, 3);
            } else {
                msg = func_ovl0A_06_80046998(D_ovl0A_06_80046D70, 0x46, 0x5A, 1.0f, 1.0f, 0);
                SE(0x18, 0x18);
                while (TRUE) {
                    if (func_ovl0A_06_80045B18() & 0xD000) {
                        SE(2, 2);
                        break;
                    }
                    func_ovl0A_06_800465A0();
                }
            }
            func_ovl0A_06_80046948(msg);
        }
    }
    func_ovl0A_06_80045B00(0x20, 0x10, 2);
    if (erase) {
        func_ovl0A_06_80043B54(D_ovl0A_06_80047728, 4);
    }
    func_ovl0A_06_80046568();
}

static void func_ovl0A_06_80043B54(s32 *handles, s32 n) {
    s32 i;
    s32 *p = handles;

    for (i = 0; i < n; i++) {
        func_ovl0A_06_80046948(*p);
        p++;
    }
}

static void func_ovl0A_06_800436BC(void) {
    s32 i;
    s32 y;

    func_ovl0A_06_80046578(0x14);
    func_ovl0A_06_80046838(1);
    switch (D_ovl0A_06_80047014) {
        case 0:
            D_ovl0A_06_8004752C = func_ovl0A_06_800460E8(0x42, 0);
            D_ovl0A_06_8004752C->unk10 = 28.0f;
            D_ovl0A_06_8004752C->unk14 = 20.0f;
            D_ovl0A_06_8004752C->unk18 = 292.0f;
            D_ovl0A_06_8004752C->unk1C = 217.0f;
            D_ovl0A_06_80047530 = func_ovl0A_06_800460E8(0x39, 0);
            D_ovl0A_06_80047534 = func_ovl0A_06_800460E8(0x39, 0);
            D_ovl0A_06_80047534->unk38 = 2;
            func_ovl0A_06_800434E4(0);
            func_ovl0A_06_800434D4();
            func_ovl0A_06_800434DC();
            if (func_ovl0A_06_80043464() != 9) {
                for (i = 0; i < 4; i++) {
                    func_ovl0A_06_80043250(D_ovl0A_06_80047068[i], i);
                    D_ovl0A_06_80047068[i][5] = 0;
                }
            }
            func_ovl0A_06_80046988(8, 0xC, 0x48, 0x200);
            for (i = 0, y = 0x67; i < 4; i++, y += 0x14) {
                D_ovl0A_06_80047708[i] = func_ovl0A_06_80046940(D_ovl0A_06_80047068[i], 0x23, y, 1.0f, 1.0f, 0);
                D_ovl0A_06_80047718[i] = func_ovl0A_06_80046978(D_ovl0A_06_80047708[i]);
            }
            func_ovl0A_06_80046988(0x18, 0x18, 0x47, 0);
            i = 0;
            D_ovl0A_06_80047738[i] = func_ovl0A_06_80046998(D_ovl0A_06_80046D88, 0x5D, 0x18, 0.666f, 0.666f, 0);
            D_ovl0A_06_80047748[i] = func_ovl0A_06_80046978(D_ovl0A_06_80047738[i]);
            i++;
            D_ovl0A_06_80047738[i] = func_ovl0A_06_80046998(D_ovl0A_06_80046D98, 0x3C, 0x39, 0.5f, 0.5f, 0);
            D_ovl0A_06_80047748[i] = func_ovl0A_06_80046978(D_ovl0A_06_80047738[i]);
            i++;
            D_ovl0A_06_80047738[i] = func_ovl0A_06_80046998(D_ovl0A_06_80046DB8, 0x23, 0x53, 0.5f, 0.5f, 0);
            D_ovl0A_06_80047748[i] = func_ovl0A_06_80046978(D_ovl0A_06_80047738[i]);
            i++;
            D_ovl0A_06_80047738[i] = func_ovl0A_06_80046998(D_ovl0A_06_80046DE0, 0x4A, 0xC8, 0.5f, 0.5f, 0);
            D_ovl0A_06_80047748[i] = func_ovl0A_06_80046978(D_ovl0A_06_80047738[i]);
            break;
        case 1:
            D_ovl0A_06_8004752C = func_ovl0A_06_800460E8(0x296, 0);
            D_ovl0A_06_8004752C->unk10 = 0.0f;
            D_ovl0A_06_8004752C->unk14 = 0.0f;
            D_ovl0A_06_8004752C->unk18 = 320.0f;
            D_ovl0A_06_8004752C->unk1C = 240.0f;
            i = 0;
            D_ovl0A_06_80047728[i++] = func_ovl0A_06_80046998(D_ovl0A_06_80046D00, 0x37, 0x41, 0.75f, 1.2f, 0);
            D_ovl0A_06_80047728[i++] = func_ovl0A_06_80046998(D_ovl0A_06_80046D30, 0x37, 0x69, 0.75f, 1.2f, 0);
            D_ovl0A_06_80047728[i++] = func_ovl0A_06_80046998(D_ovl0A_06_80046D24, 0x50, 0x96, 1.0f, 1.0f, 1);
            D_ovl0A_06_80047728[i++] = func_ovl0A_06_80046998(D_ovl0A_06_80046D2C, 0xAE, 0x96, 1.0f, 1.0f, 0);
            break;
    }
    func_ovl0A_06_800468A8(0x2D, 0x2D, 0x50);
    func_ovl0A_06_80046850();
}

static void func_ovl0A_06_800434E4(s32 arg0) {
    switch (arg0) {
        case 0:
            D_ovl0A_06_80047530->unk10 = 141.0f;
            D_ovl0A_06_80047530->unk14 = 53.0f;
            D_ovl0A_06_80047530->unk18 = 159.0f;
            D_ovl0A_06_80047530->unk1C = 71.0f;
            D_ovl0A_06_80047534->unk10 = 161.0f;
            D_ovl0A_06_80047534->unk14 = 53.0f;
            D_ovl0A_06_80047534->unk18 = 179.0f;
            D_ovl0A_06_80047534->unk1C = 71.0f;
            break;
        case 1:
            D_ovl0A_06_80047530->unk10 = 137.0f;
            D_ovl0A_06_80047530->unk14 = 49.0f;
            D_ovl0A_06_80047530->unk18 = 163.0f;
            D_ovl0A_06_80047530->unk1C = 75.0f;
            D_ovl0A_06_80047534->unk10 = 161.0f;
            D_ovl0A_06_80047534->unk14 = 53.0f;
            D_ovl0A_06_80047534->unk18 = 179.0f;
            D_ovl0A_06_80047534->unk1C = 71.0f;
            break;
        case 2:
            D_ovl0A_06_80047530->unk10 = 141.0f;
            D_ovl0A_06_80047530->unk14 = 53.0f;
            D_ovl0A_06_80047530->unk18 = 159.0f;
            D_ovl0A_06_80047530->unk1C = 71.0f;
            D_ovl0A_06_80047534->unk10 = 157.0f;
            D_ovl0A_06_80047534->unk14 = 49.0f;
            D_ovl0A_06_80047534->unk18 = 183.0f;
            D_ovl0A_06_80047534->unk1C = 75.0f;
            break;
    }
}

static void func_ovl0A_06_800434D4(void) {
    D_ovl0A_06_80047538 = func_ovl0A_06_800460E8(0x43, 0);
    D_ovl0A_06_80047538->unk38 = 0xC;
    D_ovl0A_06_80047538->unk28 = 14.0f;
    D_ovl0A_06_80047538->unk2C = 14.0f;
    D_ovl0A_06_80047538->unk10 = 51.0f;
    D_ovl0A_06_80047538->unk14 = 199.0f;
    D_ovl0A_06_80047538->unk18 = 65.0f;
    D_ovl0A_06_80047538->unk1C = 213.0f;
}

static void func_ovl0A_06_800434DC(void) {
    func_ovl0A_06_800434CC(D_ovl0A_06_80047178, 10);
}

static void func_ovl0A_06_800434CC(UnkStruct_ovl0A_06_80047178 *tbl, s32 n) {
    s32 i;

    for (i = 0; i < n; i++, tbl++) {
        tbl->unk0 = func_ovl0A_06_80046168(tbl->unk28, 0);
        tbl->unk0->unkC |= tbl->unk24;
    }
}

static s32 func_ovl0A_06_80043464(void) {
    s32 ret = func_ovl0A_06_800466B8(D_ovl0A_06_80047540);

    if (ret == 9) {
        func_ovl0A_06_80043250(&D_ovl0A_06_80046DE0[0x1A], D_ovl0A_06_80047540[0].unk0 >> 8);
        func_ovl0A_06_800432F8(D_ovl0A_06_80047540);
    }
    D_ovl0A_06_80047024 = ret;
    return ret;
}

static void func_ovl0A_06_800432F8(UnkStruct_ovl0A_06_80047540 *notes) {
    s32 i;
    s32 j;
    s32 len;
    s32 n;

    n = D_ovl0A_06_80047020 * 4;
    for (i = 0; i < 4; i++) {
        func_ovl0A_06_80043250(D_ovl0A_06_80047068[i], n + 1);
        if (notes[n].unk4 != 0) {
            D_ovl0A_06_80047068[i][0x16] = 0;
            for (j = 0; j < 16; j++) {
                D_ovl0A_06_80047068[i][j + 5] = notes[n].unk10[j];
                if (notes[n].unk10[j] == 0) {
                    break;
                }
            }
            len = j + 5;
            if (notes[n].unkC[0] != 0) {
                D_ovl0A_06_80047068[i][len] = 0x3C;
                len++;
                for (j = 0; j < 4; j++) {
                    D_ovl0A_06_80047068[i][len] = notes[n].unkC[j];
                    if (notes[n].unkC[j] == 0) {
                        break;
                    }
                    len++;
                }
            }
            for (; len < 0x1C; len++) {
                D_ovl0A_06_80047068[i][len] = 0xF;
            }
            func_ovl0A_06_80043250(&D_ovl0A_06_80047068[i][0x1C], notes[n].unk8 >> 8);
            D_ovl0A_06_80047068[i][0x1F] = 0;
        } else {
            D_ovl0A_06_80047068[i][5] = 0;
        }
        n++;
    }
}

static void func_ovl0A_06_80043250(u8 *dest, s32 value) {
    s32 i;
    u8 buf[4];

    i = 0;
    func_ovl0A_06_80043248(buf, value);
    buf[i] -= 0x20;
    i++;
    buf[i] -= 0x20;
    i++;
    buf[i] -= 0x20;
    if (buf[0] == 0x10) {
        buf[0] = 0xF;
        if (buf[1] == 0x10) {
            buf[1] = 0xF;
        }
    }
    for (i = 0; i < 3; i++) {
        dest[i] = buf[i];
    }
}

static void func_ovl0A_06_80043248(u8 *str, s32 value) {
    func_ovl0A_06_800456D0(str, "%03d", value);
}

static s32 func_ovl0A_06_8004311C(void) {
    s32 wait;
    s32 ret = 0;
    s32 held;
    s32 pressed;

    D_ovl0A_06_80047018 = 1;
    func_ovl0A_06_80043020(-1, 1);
    do {
        held = func_ovl0A_06_80046910();
        pressed = func_ovl0A_06_80045B18();
        if ((held & 0x200) && D_ovl0A_06_80047018 == 1) {
            D_ovl0A_06_80047018 = 0;
            func_ovl0A_06_80043020(0, 0);
        } else if ((held & 0x100) && D_ovl0A_06_80047018 == 0) {
            D_ovl0A_06_80047018 = 1;
            func_ovl0A_06_80043020(0, 1);
        } else if ((pressed & 0x8000) || (pressed & 0x1000)) {
            ret = 1;
            if (D_ovl0A_06_80047018 == 0) {
                ret = 2;
                SE(1, 1);
            } else {
                SE(2, 2);
            }
        } else if (pressed & 0x4000) {
            ret = 1;
            SE(2, 2);
        }
        func_ovl0A_06_800465A0();
    } while (ret == 0);
    return ret;
}

static void func_ovl0A_06_80043020(s32 sfx, s32 sel) {
    s32 wait;
    s32 noX = 0xAE;
    s32 noY = 0x96;
    s32 yesX = 0x50;
    s32 yesY = 0x96;
    f32 scale = 1.0f;
    f32 noScale = scale;
    f32 yesScale = scale;
    s32 noFlag;
    s32 yesFlag;
    s32 no;
    s32 yes;

    SE(sfx, 0);
    if (sel) {
        noX = 0xA9;
        noY = 0x91;
        noFlag = 0;
        yesFlag = 1;
        noScale = scale + 0.5f;
    } else {
        yesX = 0x4B;
        yesY = 0x91;
        yesFlag = 0;
        noFlag = 1;
        yesScale = scale + 0.5f;
    }
    no = func_ovl0A_06_80046998(D_ovl0A_06_80046D2C, noX, noY, noScale, noScale, noFlag);
    yes = func_ovl0A_06_80046998(D_ovl0A_06_80046D24, yesX, yesY, yesScale, yesScale, yesFlag);
    func_ovl0A_06_80046948(D_ovl0A_06_80047728[3]);
    func_ovl0A_06_80046948(D_ovl0A_06_80047728[2]);
    D_ovl0A_06_80047728[3] = no;
    D_ovl0A_06_80047728[2] = yes;
}

static void func_ovl0A_06_80043010(s32 id, s32 wait) {
    if (id != -1) {
        func_ovl0A_06_80046AE0(id);
        func_ovl0A_06_80046578(wait);
    }
}

