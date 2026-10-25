/*
 * NON_MATCHING: ovl_0C_02's game object, complete: every function and its
 * data (.data 0x640 and .bss 0x60 laid out as the original; .rodata is
 * 0xF0 where the original's is 0xD0).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 2382
 *
 * A first complete draft: the functions shared with bank 0x0C's and
 * 0x12/0x17's drafts are theirs (scratch/0C_02/sib.py), the rest m2c's
 * output with its types fixed, so most of the rest still differs.  62 of
 * the 96 functions match.  ovl_0C_01 and ovl_0C_06 have most of the same
 * functions (80043338, 80043544-80043840, 80044914, 80044A68, 80045538,
 * 800475BC-80047E90 at ratio 1.00) and no C yet.
 *
 * What still differs in us (words):
 * - func_ovl0C_02_80046DD0 (351), 800460B0 (171, the object set-up),
 *   8004639C (153, the handler), 80046B68 (152), 80043338 (129),
 *   80046924 (112), 80045B50 (110), 80044CD0 (101), 80043E0C (98),
 *   80043840 (96), 80045898 (91), 80044914 (84), 80043650 (78),
 *   80045538 (76), 800475BC, 800477B0 and 80047E90 (72 each), 80047410
 *   (69), 80043544 (66), 80044A68 (55), 800430D0 (50), 8004797C (24),
 *   800431D4 and 80045A7C (17 each), 80045448 (15), 8004460C (14),
 *   800467D8 (12), 800454B4 (11), 80043B64 (4), 80043A98, 80043C54,
 *   80043FD8, 80045668 and 80045780 (2 each): m2c's register use and
 *   loop shapes (its `goto` loops in the tasks), not yet worked on.
 * - The record loops (UnkStruct_ovl0C_02_80049B84 lists, ending at unk2
 *   == 0) keep m2c's do-while; 80043544, 80044914 and 80044A68 keep two
 *   values in saved registers that the C doesn't explain yet (an
 *   `if (arg1 == 0) {}` m2c left where the original chooses between two
 *   equal flags).
 */
#include "common.h"

/* the handler's state (ovl_0C_07's D_ovl0C_07_80047990) */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_02_8004A110;

/* a gate (ovl_0C_07's UnkStruct_ovl0C_07_80047590) */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
} UnkStruct_ovl0C_02_80049A38;

/* an object at a position, with three arguments */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0C_02_80049AB0;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStruct_ovl0C_02_80049B20;

/* an object and its position */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl0C_02_80049B50;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} UnkStruct_ovl0C_02_80049B60;

/* a list of these ends at the one whose unk2 is 0; unk20 and unk22 count */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s32 unk24;
} UnkStruct_ovl0C_02_80049B84;


/* a list of these ends at the one whose unk2 is 0; unk20 points into
 * another list */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ UnkStruct_ovl0C_02_80049B84 *unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
} UnkStruct_ovl0C_02_80049C24;

/* the stage object (ovl_0C_07's UnkStruct_ovl0C_07_800477A8) */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
} UnkStruct_ovl0C_02_80049EEC;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
} UnkStruct_ovl0C_02_80049F24;

/* what the ZeroJump stub 0x3106 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
} UnkStruct_ovl0C_02_80049968_C;

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ UnkStruct_ovl0C_02_80049968_C *unkC;
} UnkStruct_ovl0C_02_80049968;

void func_ovl0C_02_800486C8(s32); /* 0xC00 */
void func_ovl0C_02_800486E0(s32); /* 0xD00 */
void func_ovl0C_02_80048700(s32, s32, s32, s32); /* 0xD04 */
void func_ovl0C_02_80048708(s32, s32, s32, s32, s32, s32); /* 0xD05 */
void func_ovl0C_02_80048710(s32, s32, s32, s32, s32, s32, s32); /* 0xD06 */
s32 func_ovl0C_02_80048730(s32); /* 0xD0A */
void func_ovl0C_02_80048750(UnkStructA_40 *, f32 *, f32 *); /* 0xD0E */
void func_ovl0C_02_800487A8(void (*)(UnkStructA *), s32); /* 0xE02 */
void func_ovl0C_02_800487B0(void (*)(UnkStructA *)); /* 0xE03 */
void func_ovl0C_02_800487C0(s32, s32, s32); /* 0xF00 */
void func_ovl0C_02_800487E8(void); /* 0xF05 */
void func_ovl0C_02_80048800(void (*)(UnkStructA *)); /* 0xF08 */
s32 * func_ovl0C_02_80048818(void); /* 0xF0B */
void func_ovl0C_02_80048830(s32); /* 0xF0E */
void func_ovl0C_02_80048838(s32); /* 0xF0F */
void func_ovl0C_02_80048850(s32, s32); /* 0xF12 */
void func_ovl0C_02_80048868(s32); /* 0xF15 */
void func_ovl0C_02_80048878(void); /* 0x1000 */
void func_ovl0C_02_80048880(s32, s32, s32); /* 0x1001 */
void func_ovl0C_02_80048888(void *); /* 0x1002 */
s32 func_ovl0C_02_80048890(s32, s32, s32, s32); /* 0x1003 */
s32 func_ovl0C_02_80048898(s32, s32, s32, s32, s32); /* 0x1004 */
s32 func_ovl0C_02_800488A8(void); /* 0x1006 */
void func_ovl0C_02_800488B0(s32, void *); /* 0x1007 */
void func_ovl0C_02_800488B8(s32); /* 0x1008 */
void func_ovl0C_02_800488C0(s32); /* 0x1009 */
void func_ovl0C_02_800488C8(s32, s32, f32, s32, s32, s32, s32); /* 0x100A */
void func_ovl0C_02_800488D0(const char *); /* 0x100B */
void func_ovl0C_02_800488D8(void); /* 0x100C */
void func_ovl0C_02_800488E0(s32); /* 0x100D */
UnkStructA * func_ovl0C_02_80048908(s32); /* 0x1012 */
void func_ovl0C_02_80048910(s32); /* 0x1013 */
UnkStructA * func_ovl0C_02_80048948(s32); /* 0x101A */
void func_ovl0C_02_80048978(void); /* 0x1020 */
void func_ovl0C_02_80048DD0(UnkStructA_40 *, s32); /* 0x1505 */
void func_ovl0C_02_80048DD8(UnkStructA_40 *, s32, s32, s32); /* 0x1506 */
f32 func_ovl0C_02_80048E08(UnkStructA_40 *, s32); /* 0x150C */
s32 func_ovl0C_02_80048E10(UnkStructA_40 *, s32, s32, s32, s32, s32); /* 0x150D */
void func_ovl0C_02_80048E18(s32); /* 0x150E */
void func_ovl0C_02_80048E30(s32, s32); /* 0x1511 */
void func_ovl0C_02_80048F08(f32, f32, f32); /* 0x1704 */
void func_ovl0C_02_80048F28(f32, f32, f32); /* 0x1708 */
void func_ovl0C_02_80048F30(f32 *, f32 *, f32 *); /* 0x1709 */
void func_ovl0C_02_80048F68(s32); /* 0x1710 */
void func_ovl0C_02_80048F70(s32); /* 0x1711 */
void func_ovl0C_02_80048F80(s32); /* 0x1713 */
void func_ovl0C_02_80048FC0(f32, f32); /* 0x171B */
void func_ovl0C_02_80048FF8(void *); /* 0x1722 */
void func_ovl0C_02_80049028(void); /* 0x1728 */
void func_ovl0C_02_80049030(void); /* 0x1729 */
s32 func_ovl0C_02_80049078(UnkStructA *, s32); /* 0x1807 */
void func_ovl0C_02_800490C8(UnkStructA *, s32); /* 0x1811 */
void func_ovl0C_02_800490D0(UnkStructA *, s32); /* 0x1812 */
void func_ovl0C_02_800490E0(UnkStructA *); /* 0x1814 */
UnkStructA * func_ovl0C_02_800490F0(s32, s32, s32, s32); /* 0x1816 */
UnkStructA * func_ovl0C_02_80049100(UnkStructA *); /* 0x1818 */
UnkStructA * func_ovl0C_02_80049110(s32, s32, f32, f32, f32); /* 0x181A */
void func_ovl0C_02_80049148(UnkStructA *); /* 0x1821 */
UnkStructA * func_ovl0C_02_80049158(UnkStructA *, s32); /* 0x1823 */
s32 func_ovl0C_02_800491E8(UnkStructA *, s32, UnkStructA *); /* 0x1835 */
s32 func_ovl0C_02_80049218(void (*)(void), void *, s32, s32, s32); /* 0x1900 */
void func_ovl0C_02_80049220(s32); /* 0x1901 */
void func_ovl0C_02_80049228(void); /* 0x1902 */
void func_ovl0C_02_80049238(s32); /* 0x1904 */
void * func_ovl0C_02_80049240(void); /* 0x1905 */
void func_ovl0C_02_80049260(void); /* 0x1909 */
void func_ovl0C_02_80049278(u16); /* 0x190C */
void func_ovl0C_02_80049290(s32, s32); /* 0x190F */
f32 func_ovl0C_02_800493C0(f32); /* 0x1D00 */
f32 func_ovl0C_02_800493C8(f32); /* 0x1D01 */
s32 func_ovl0C_02_800493D8(s32); /* 0x1D03 */
s32 func_ovl0C_02_80049480(s32); /* 0x1E04 */
void func_ovl0C_02_80049490(s32); /* 0x1E06 */
void func_ovl0C_02_80049498(s32); /* 0x1E07 */
s32 func_ovl0C_02_800494A0(s32); /* 0x1E08 */
void func_ovl0C_02_80049518(s32, s32, s32, f32); /* 0x2004 */
void func_ovl0C_02_80049568(s32, s32, s32); /* 0x2201 */
void func_ovl0C_02_80049580(u32 (*)[3]); /* 0x2300 */
void func_ovl0C_02_80049598(u32 (*)[3]); /* 0x2303 */
void func_ovl0C_02_80049668(s32, f32, f32, f32, s32); /* 0x2600 */
s32 func_ovl0C_02_80049670(s32, f32 *, s32); /* 0x2601 */
void func_ovl0C_02_80049678(s32); /* 0x2602 */
void func_ovl0C_02_800496A8(void); /* 0x2704 */
void func_ovl0C_02_800496B8(f32 *); /* 0x2706 */
void func_ovl0C_02_800496E8(s32, f32, f32, f32); /* 0x2801 */
void func_ovl0C_02_80049718(UnkStructA *, s32, f32); /* 0x2901 */
void func_ovl0C_02_80049728(s32, s32, s32); /* 0x2A00 */
void func_ovl0C_02_80049748(s32); /* 0x2A04 */
void func_ovl0C_02_80049788(void); /* 0x2A0C */
void func_ovl0C_02_800497A0(s32); /* 0x2B00 */
void func_ovl0C_02_800497C0(s32, f32, f32, f32); /* 0x2B04 */
void func_ovl0C_02_800497C8(s32, f32 *); /* 0x2B05 */
void func_ovl0C_02_80049950(s32); /* 0x3103 */
s32 func_ovl0C_02_80049960(void); /* 0x3105 */
UnkStruct_ovl0C_02_80049968 *func_ovl0C_02_80049968(s32); /* 0x3106 */
void func_ovl0C_02_80049978(s32); /* 0x3108 */
void func_ovl0C_02_80049980(void); /* 0x3109 */
void func_ovl0C_02_80049988(void); /* 0x310A */

void func_ovl0C_02_80043010(void);
void func_ovl0C_02_80043018(void);
void func_ovl0C_02_80043060(void);
void func_ovl0C_02_80043090(void);
void func_ovl0C_02_800430B0(void);
s32 func_ovl0C_02_800430D0(UnkStructA *arg0, UnkStructA *arg1);
s32 func_ovl0C_02_800431D4(void);
void func_ovl0C_02_80043250(void);
void func_ovl0C_02_80043338(void);
void func_ovl0C_02_80043544(UnkStruct_ovl0C_02_80049C24 *arg0, s32 arg1);
void func_ovl0C_02_80043650(UnkStructA **arg0, UnkStruct_ovl0C_02_80049C24 *arg1, UnkStruct_ovl0C_02_80049B84 *arg2, s32 arg3);
s32 func_ovl0C_02_80043840(UnkStructA **arg0, UnkStruct_ovl0C_02_80049C24 *arg1, UnkStruct_ovl0C_02_80049B84 *arg2, s32 arg3);
void func_ovl0C_02_80043A0C(UnkStruct_ovl0C_02_80049A38 *arg0);
void func_ovl0C_02_80043A98(UnkStruct_ovl0C_02_80049A38 *arg0);
void func_ovl0C_02_80043B1C(void);
void func_ovl0C_02_80043B64(void);
void func_ovl0C_02_80043C54(void);
void func_ovl0C_02_80043E0C(UnkStruct_ovl0C_02_80049B20 *arg0);
void func_ovl0C_02_80043FD8(void);
void func_ovl0C_02_80044094(void);
void func_ovl0C_02_800440E4(UnkStruct_ovl0C_02_80049A38 *arg0);
void func_ovl0C_02_80044150(void);
void func_ovl0C_02_800442E0(void);
void func_ovl0C_02_8004434C(void *arg0);
void func_ovl0C_02_80044384(void);
void func_ovl0C_02_800444D4(UnkStruct_ovl0C_02_80049AB0 *arg0);
void func_ovl0C_02_80044538(void);
void func_ovl0C_02_80044580(void);
void func_ovl0C_02_8004460C(void);
void func_ovl0C_02_80044710(UnkStruct_ovl0C_02_80049A38 *arg0);
void func_ovl0C_02_800447D4(UnkStruct_ovl0C_02_80049A38 *arg0);
void func_ovl0C_02_80044810(void);
void func_ovl0C_02_80044868(void);
void func_ovl0C_02_800448CC(void);
void func_ovl0C_02_80044914(UnkStruct_ovl0C_02_80049B84 *arg0, s32 arg1);
void func_ovl0C_02_80044A68(UnkStruct_ovl0C_02_80049B50 *arg0, UnkStruct_ovl0C_02_80049C24 *arg1, s32 arg2);
void func_ovl0C_02_80044B58(f32 arg0);
void func_ovl0C_02_80044BA0(void);
void func_ovl0C_02_80044CD0(void);
void func_ovl0C_02_80044E74(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4);
void func_ovl0C_02_80044E9C(void);
void func_ovl0C_02_80044F00(void);
void func_ovl0C_02_80044F68(void);
void func_ovl0C_02_80044FCC(void);
void func_ovl0C_02_80045030(void);
void func_ovl0C_02_80045098(void);
void func_ovl0C_02_800450C8(void);
void func_ovl0C_02_800450F8(void);
void func_ovl0C_02_80045128(void);
void func_ovl0C_02_80045158(void);
void func_ovl0C_02_800451CC(void);
void func_ovl0C_02_8004523C(void);
void func_ovl0C_02_800452B0(void);
void func_ovl0C_02_80045318(void);
void func_ovl0C_02_80045378(UnkStructA *arg0);
void func_ovl0C_02_800453CC(Vec3f *arg0);
s32 func_ovl0C_02_80045448(void);
void func_ovl0C_02_800454B4(void);
void func_ovl0C_02_80045538(void);
void func_ovl0C_02_80045668(void);
void func_ovl0C_02_80045780(void);
void func_ovl0C_02_80045898(void);
static void func_ovl0C_02_80045A74(f32 x, s32 z, s32 count);
void func_ovl0C_02_80045A7C(void);
void func_ovl0C_02_80045B50(void);
void func_ovl0C_02_80045D74(UnkStruct_ovl0C_02_80049A38 *arg0);
void func_ovl0C_02_80045DD0(s32 arg0);
void func_ovl0C_02_80045E8C(void);
void func_ovl0C_02_80046030(void);
void func_ovl0C_02_80046038(void);
void func_ovl0C_02_80046078(void);
void func_ovl0C_02_800460B0(void);
void func_ovl0C_02_8004639C(s32 arg0);
void func_ovl0C_02_8004661C(void);
void func_ovl0C_02_80046720(void);
void func_ovl0C_02_8004679C(void);
void func_ovl0C_02_800467D8(void);
void func_ovl0C_02_800468EC(void);
void func_ovl0C_02_80046924(void);
void func_ovl0C_02_80046B30(void);
UnkStructA *func_ovl0C_02_80046B68(UnkStruct_ovl0C_02_80049AB0 *arg0);
void func_ovl0C_02_80046DD0(void);
void func_ovl0C_02_80047410(void);
void func_ovl0C_02_80047538(void);
void func_ovl0C_02_800475BC(UnkStructA *arg0);
void func_ovl0C_02_800477B0(UnkStructA *arg0);
void func_ovl0C_02_8004797C(void);
void func_ovl0C_02_80047B20(void);
void func_ovl0C_02_80047D78(void);
void func_ovl0C_02_80047E90(void);
void func_ovl0C_02_80047FB4(UnkStructA *arg0);
void func_ovl0C_02_80048074(UnkStructA *arg0);
void func_ovl0C_02_800480B8(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_ovl0C_02_80048190(void);
void func_ovl0C_02_800482A0(s32 arg0, UnkStructA *arg1);
void func_ovl0C_02_800482D4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0C_02_80048330(void);
static void func_ovl0C_02_80048348(void);

/* the handler's state set in one line (ovl_0C_07's func_ovl0C_07_80043CF0, here
 * never a function of its own) */
#define UNK_MACRO_ovl0C_02_80045098(a, b, c, d, e) \
    D_ovl0C_02_8004A110.unk0 = (a); D_ovl0C_02_8004A110.unk4 = (b); D_ovl0C_02_8004A110.unk8 = (c); D_ovl0C_02_8004A110.unkC = (d); D_ovl0C_02_8004A110.unk10 = (e)

/* .bss */
u8 D_ovl0C_02_8004A0D0[0x10];
Vec3f D_ovl0C_02_8004A0E0;
s32 D_ovl0C_02_8004A0EC;
s32 D_ovl0C_02_8004A0F0;
s32 D_ovl0C_02_8004A0F4;
s32 D_ovl0C_02_8004A0F8;
u8 D_ovl0C_02_8004A0FC[0x4];
f32 D_ovl0C_02_8004A100[3];
UnkStructA *D_ovl0C_02_8004A10C;
UnkStruct_ovl0C_02_8004A110 D_ovl0C_02_8004A110;
UnkStructA *D_ovl0C_02_8004A124;
UnkStructA *D_ovl0C_02_8004A128[2];

/* .data */
u32 D_ovl0C_02_800499C0[][3] = {
    { 0x8F0002, 0x2000E, 4 },
    { 0x950000, 0xE, 4 },
    { 0x930000, 0xE, 0x2004 },
};
u32 D_ovl0C_02_800499E4[][3] = {
    { 0, 4, 0x960000 },
    { 0x84, 0, 4 },
};
u32 D_ovl0C_02_800499FC[][3] = {
    { 0, 6, 0xE4 },
    { 1, 4, 0xE2 },
    { 2, 0, 0xDE },
    { 3, 5, 0x34F },
    { 4, 0x17, 0xF5 },
};
UnkStruct_ovl0C_02_80049A38 D_ovl0C_02_80049A38[] = {
    { 0, NULL, 200.0f, 300.0f, 1450.0f, 0x40, 250.0f, 300.0f, 1450.0f, 1, 1, 0xE, 4, 2, 0xF, 1, 1, 0xE, 1, 0xF, 3, 1, 0x10, 0x17, 0x11, 3, 1, 0xD, 0x18, 0x11 },
};
UnkStruct_ovl0C_02_80049AB0 D_ovl0C_02_80049AB0[] = {
    { NULL, 2100.0f, 1200.0f, 1200.0f, 0x416, 0x28, 0x15 },
};
UnkStruct_ovl0C_02_80049AB0 D_ovl0C_02_80049ACC[] = {
    { NULL, 2100.0f, 1200.0f, 1700.0f, 0x417, 0x28, 0x16 },
};
UnkStruct_ovl0C_02_80049AB0 D_ovl0C_02_80049AE8[] = {
    { NULL, 2600.0f, 1200.0f, 1200.0f, 0x418, 0x29, 0x1B },
};
UnkStruct_ovl0C_02_80049AB0 D_ovl0C_02_80049B04[] = {
    { NULL, 2600.0f, 1200.0f, 1700.0f, 0x419, 0x29, 0x1C },
};
UnkStruct_ovl0C_02_80049B20 D_ovl0C_02_80049B20[] = {
    { NULL, 3000.0f, 600.0f, 2500.0f, 0x19, 0x418 },
};
UnkStruct_ovl0C_02_80049B20 D_ovl0C_02_80049B38[] = {
    { NULL, 4100.0f, 400.0f, 900.0f, 0x1A, 0x419 },
};
UnkStruct_ovl0C_02_80049B50 D_ovl0C_02_80049B50[] = {
    { NULL, 2350.0f, 1000.0f, 1450.0f },
};
UnkStruct_ovl0C_02_80049B60 D_ovl0C_02_80049B60[] = {
    { NULL, 0.0f, 0.0f, 0.0f, 0x15, 5, 0xC, 0x1A, 0x11 },
};
UnkStruct_ovl0C_02_80049B84 D_ovl0C_02_80049B84[] = {
    { 0, 1, NULL, 4450.0f, 400.0f, 1450.0f, 650.0f, 0x2C, 3, 0xE, 2, 0, 0, 0x407 },
    { 1, 2, NULL, 4450.0f, 400.0f, 1950.0f, 650.0f, 0x2C, 3, 0x13, 2, 0, 0, 0x408 },
    { 2, 3, NULL, 4450.0f, 400.0f, 2450.0f, 650.0f, 0x2C, 3, 0x18, 2, 0, 0, 0x409 },
    { 3, 0, NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0 },
};
UnkStruct_ovl0C_02_80049C24 D_ovl0C_02_80049C24[] = {
    { 0, 1, NULL, 4450.0f, 900.0f, 1350.0f, 900.0f, 0x2B, 5, 0xB, 4, NULL, 0, 0 },
    { 1, 2, NULL, 4450.0f, 900.0f, 1650.0f, 900.0f, 0x2B, 5, 0xE, 4, &D_ovl0C_02_80049B84[0], 0, 0 },
    { 2, 3, NULL, 4450.0f, 900.0f, 1950.0f, 900.0f, 0x2B, 5, 0x11, 4, &D_ovl0C_02_80049B84[1], 0, 0 },
    { 3, 4, NULL, 4450.0f, 900.0f, 2250.0f, 900.0f, 0x2B, 5, 0x14, 4, NULL, 0, 0 },
    { 4, 5, NULL, 4450.0f, 900.0f, 2550.0f, 900.0f, 0x2B, 5, 0x17, 4, &D_ovl0C_02_80049B84[2], 0, 0 },
    { 5, 6, NULL, 4450.0f, 900.0f, 2850.0f, 900.0f, 0x2B, 5, 0x1A, 4, NULL, 0, 0 },
    { 6, 0, NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, NULL, 0, 0 },
};
UnkStruct_ovl0C_02_80049B84 D_ovl0C_02_80049D3C[] = {
    { 0, 1, NULL, 3750.0f, 400.0f, 1150.0f, 650.0f, 0x25, 3, 0xB, 2, 0, 0, 0x40A },
    { 1, 2, NULL, 3750.0f, 400.0f, 1650.0f, 650.0f, 0x25, 3, 0x10, 2, 0, 0, 0x40B },
    { 2, 0, NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0 },
};
UnkStruct_ovl0C_02_80049C24 D_ovl0C_02_80049DB4[] = {
    { 0, 1, NULL, 3750.0f, 900.0f, 550.0f, 900.0f, 0x24, 5, 3, 4, NULL, 0, 0 },
    { 1, 2, NULL, 3750.0f, 900.0f, 850.0f, 900.0f, 0x24, 5, 6, 4, NULL, 0, 0 },
    { 2, 3, NULL, 3750.0f, 900.0f, 1150.0f, 900.0f, 0x24, 5, 9, 4, &D_ovl0C_02_80049D3C[0], 0, 0 },
    { 3, 4, NULL, 3750.0f, 900.0f, 1450.0f, 900.0f, 0x24, 5, 0xC, 4, NULL, 0, 0 },
    { 4, 5, NULL, 3750.0f, 900.0f, 1750.0f, 900.0f, 0x24, 5, 0xF, 4, &D_ovl0C_02_80049D3C[1], 0, 0 },
    { 5, 6, NULL, 3750.0f, 900.0f, 2050.0f, 900.0f, 0x24, 5, 0x12, 4, NULL, 0, 0 },
    { 6, 0, NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, NULL, 0, 0 },
};
UnkStruct_ovl0C_02_80049B50 D_ovl0C_02_80049ECC[] = {
    { NULL, 4450.0f, 900.0f, 1350.0f },
};
UnkStruct_ovl0C_02_80049B50 D_ovl0C_02_80049EDC[] = {
    { NULL, 3750.0f, 900.0f, 550.0f },
};
UnkStruct_ovl0C_02_80049EEC D_ovl0C_02_80049EEC = { NULL, -1, 0x2B4, 0x40, 0x400, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
UnkStruct_ovl0C_02_80049F24 D_ovl0C_02_80049F24[] = {
    { NULL, 0x2AD, 2150.0f, 600.0f, 250.0f, 0x15, 3, 2, 5, 5, 0x425, 0, 8 },
    { NULL, 0x2AD, 2550.0f, 600.0f, 250.0f, 0x19, 3, 2, 5, 5, 0x426, 0, 8 },
    { NULL, 0x2AD, 3650.0f, 1000.0f, 150.0f, 0x24, 5, 1, 5, 5, 0x427, 0, 8 },
    { NULL, 0x2AD, 3850.0f, 1000.0f, 150.0f, 0x26, 5, 1, 5, 5, 0x428, 0, 8 },
};
UnkStruct_ovl0C_02_80049AB0 D_ovl0C_02_80049FE4[] = {
    { NULL, 400.0f, 300.0f, 1500.0f, 0, 0, 0 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0C_02_80048378(void) {
}
static void func_ovl0C_02_80048370(void) {
}
static void func_ovl0C_02_80048368(void) {
}
static void func_ovl0C_02_80048360(void) {
}
static void func_ovl0C_02_80048358(void) {
}
static void func_ovl0C_02_80048350(void) {
}
static void func_ovl0C_02_80048348(void) {
}

void func_ovl0C_02_80048330(void) {
    D_ovl0C_02_8004A0F4 = -1;
    D_ovl0C_02_8004A0F8 = -1;
}

void func_ovl0C_02_800482D4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_02_80048F08(D_ovl0C_02_8004A100[0], D_ovl0C_02_8004A100[1], D_ovl0C_02_8004A100[2]);
    func_ovl0C_02_80048F28(arg0, arg1, arg2);
    func_ovl0C_02_80049238(180);
}

void func_ovl0C_02_800482A0(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_02_800497C0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_02_80048190(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_02_80049240();
    func_ovl0C_02_800497C0(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_02_800490F0(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_02_800480B8(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_02_80049260();
    }
    func_ovl0C_02_800490E0(obj);
    func_ovl0C_02_80049228();
}

void func_ovl0C_02_800480B8(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0C_02_800493C0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_02_800493C0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_02_80048074(UnkStructA *arg0) {
    func_ovl0C_02_800490D0(arg0, 0x01000000);
    func_ovl0C_02_80049218(func_ovl0C_02_80048190, arg0, 0, 0, 0x150);
}

void func_ovl0C_02_80047FB4(UnkStructA *arg0) {
    func_ovl0C_02_80049238(10);
    func_ovl0C_02_80048750(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_02_80049238(60);
}

void func_ovl0C_02_80047E90(void) {
    s16 temp_s1;
    s16 temp_s1_2;
    s16 temp_s2;
    s16 temp_s2_2;
    s16 var_s3;
    UnkStruct_ovl0C_02_80049B84 *temp_s0;

    temp_s0 = func_ovl0C_02_80049240();
    var_s3 = 0xFF;
loop_1:
    var_s3 -= 0xA;
    func_ovl0C_02_800490C8(temp_s0->unk4, 0x80000);
    if (var_s3 < 0) {
        var_s3 = 0;
        func_ovl0C_02_800490D0(temp_s0->unk4, 0x01000000);
        temp_s1 = temp_s0->unk18;
        temp_s2 = temp_s0->unk1C;
        func_ovl0C_02_80048710((s32) temp_s1, (s32) temp_s0->unk1A, (s32) temp_s2, temp_s1 + 1, temp_s0->unk1E + 1, temp_s2 + 1, 0x10);
        temp_s1_2 = temp_s0->unk18;
        temp_s2_2 = temp_s0->unk1C;
        func_ovl0C_02_80048708((s32) temp_s1_2, (s32) temp_s0->unk1E, (s32) temp_s2_2, temp_s1_2 + 1, temp_s2_2 + 1, 0x11);
        temp_s0->unk22 = 0;
        func_ovl0C_02_800490E0(temp_s0->unk4);
        func_ovl0C_02_80049228();
    }
    temp_s0->unk4->unk40->unk36 = var_s3;
    func_ovl0C_02_80049260();
    goto loop_1;
}

void func_ovl0C_02_80047D78(void) {
    UnkStruct_ovl0C_02_80049B84 *list;
    UnkStruct_ovl0C_02_80049B84 *p;

    list = func_ovl0C_02_80049240();
    for (p = list; p->unk2 != 0; p++) {
        p->unk20 = func_ovl0C_02_800493D8(5) + 0x14;
        p->unk22 = 1;
    }
    while (TRUE) {
        for (p = list; p->unk2 != 0; p++) {
            if (p->unk20-- <= 0 && p->unk22 == 1) {
                func_ovl0C_02_80049668(0xF, p->unk8 - 100.0f, p->unk14, p->unk10, 0);
                func_ovl0C_02_800497A0(0x4A);
                p->unk20 = func_ovl0C_02_800493D8(5) + 0x14;
            }
        }
        func_ovl0C_02_80049260();
    }
}

void func_ovl0C_02_80047B20(void) {
    UnkStructA *temp_s1;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 var_s0;
    UnkStruct_ovl0C_02_80049C24 *temp_v0;

    temp_v0 = func_ovl0C_02_80049240();
    temp_s1 = temp_v0->unk4;
    if (temp_v0->unk20 != NULL) {
        func_ovl0C_02_80049218(func_ovl0C_02_80047E90, temp_v0->unk20, 0, 0, 0x110);
    }
    temp_a0 = temp_v0->unk18;
    temp_a2 = temp_v0->unk1C;
    func_ovl0C_02_80048708((s32) temp_a0, (s32) temp_v0->unk1A, (s32) temp_a2, temp_a0 + 3, temp_a2 + 2, 0x10);
    temp_a0_2 = temp_v0->unk18;
    temp_a2_2 = temp_v0->unk1C;
    func_ovl0C_02_80048708((s32) temp_a0_2, (s32) temp_v0->unk1E, (s32) temp_a2_2, temp_a0_2 + 3, temp_a2_2 + 2, 0x10);
    if (temp_v0->unk24 == 1) {
        func_ovl0C_02_80048708(0x2B, 3, 0xB, 0x2D, 0x12, 0x11);
        func_ovl0C_02_80048708(0x2C, 3, 0xC, 0x2D, 0x11, 0x10);
        func_ovl0C_02_80048708(0x2B, 3, 0xE, 0x2B, 0xF, 0x10);
    }
loop_5:
    temp_v0_2 = temp_s1->unk40;
    temp_v0_2->unk1C -= 5.0f;
    if (!(temp_s1->unk40->unk1C < -50.0f)) {
        func_ovl0C_02_80049260();
        goto loop_5;
    }
    func_ovl0C_02_800490C8(temp_s1, 0x80000);
    var_s0 = 0xFF;
loop_9:
    var_s0 -= 0xA;
    if (var_s0 < 0) {
        var_s0 = 0;
    }
    temp_s1->unk40->unk36 = var_s0;
    func_ovl0C_02_80049148(temp_s1);
    if ((temp_s1->unk6C == 0.0f) && (temp_s1->unk68 == 0.0f)) {
        temp_v0_3 = temp_s1->unk40;
        func_ovl0C_02_80049668(0x10, temp_v0_3->unk10, temp_v0_3->unk14 + 100.0f, temp_v0_3->unk18, 0);
        func_ovl0C_02_800490D0(temp_s1, 0x01000000);
        func_ovl0C_02_80049228();
    }
    func_ovl0C_02_80049260();
    goto loop_9;
}

void func_ovl0C_02_8004797C(void) {
    UnkStruct_ovl0C_02_80049A38 *rec;
    UnkStructA_40 *p;

    rec = func_ovl0C_02_80049240();
    p = rec->unk4->unk40;
    D_ovl0C_02_8004A128[rec->unk0]->unkC = 0x40;
    while (TRUE) {
        if (D_ovl0C_02_8004A128[rec->unk0]->unk10 & 0x40) {
            func_ovl0C_02_80049490(0x429);
            func_ovl0C_02_800497A0(0x53);
            p->unk48->unk4->unk4 = func_ovl0C_02_80048E08(p, 0) - 0.01f;
            while (p->unk48->unk4->unk4 > 1.0f) {
                func_ovl0C_02_80049260();
                p->unk48->unk4->unk4 -= 1.0f;
            }
            p->unk48->unk4->unk4 = 0.0f;
            func_ovl0C_02_80044710(rec);
            func_ovl0C_02_80049228();
        }
        func_ovl0C_02_80049260();
    }
}

void func_ovl0C_02_800477B0(UnkStructA *arg0) {
    s32 sp38;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    UnkStructA *var_a2;
    UnkStructA_40 *temp_v0;
    s32 temp_s0;
    s32 temp_v0_2;
    s32 var_at;
    s32 var_at_2;
    s32 var_s0;
    s32 var_s0_2;

    if ((func_ovl0C_02_800494A0(0x41A) == 0) && (arg0->unk6C == 0.0f) && (arg0->unk68 == 0.0f)) {
        temp_v0 = arg0->unk40;
        sp30 = temp_v0->unk10;
        sp2C = temp_v0->unk14;
        sp28 = temp_v0->unk18;
        func_ovl0C_02_80049718(arg0, 0xC0, 12.0f);
        sp38 = 0;
        temp_v0_2 = arg0->unk8;
        var_a2 = NULL;
        if (temp_v0_2 & 3) {
            var_s0 = 0;
            if (temp_v0_2 & 2) {
                var_s0_2 = 0;
loop_6:
                var_at = var_s0_2 < 5;
                if (func_ovl0C_02_80048948(var_s0_2) != arg0) {
                    var_s0_2 += 1;
                    if (var_s0_2 == 5) {
                        var_at = var_s0_2 < 5;
                    } else {
                        goto loop_6;
                    }
                }
                if (var_at != 0) {
                    var_a2 = func_ovl0C_02_80048908(var_s0_2);
                } else {
                    var_a2 = NULL;
                }
            } else {
loop_13:
                var_at_2 = var_s0 < 5;
                if (func_ovl0C_02_80048908(var_s0) != arg0) {
                    var_s0 += 1;
                    if (var_s0 == 5) {
                        var_at_2 = var_s0 < 5;
                    } else {
                        goto loop_13;
                    }
                }
                if (var_at_2 != 0) {
                    var_a2 = func_ovl0C_02_80048948(var_s0);
                } else {
                    var_a2 = NULL;
                }
            }
        }
        temp_s0 = arg0->unkC;
        arg0->unkC = 0;
        if (var_a2 != NULL) {
            if (func_ovl0C_02_800491E8(arg0, 0x10, var_a2) != 0) {
                sp38 = 1;
            }
        } else if (func_ovl0C_02_80049078(arg0, 0x10) != 0) {
            sp38 = 1;
        }
        arg0->unkC = temp_s0;
        if (sp38 != 0) {
            arg0->unk40->unk10 = sp30;
            arg0->unk40->unk14 = sp2C;
            arg0->unk40->unk18 = sp28;
        }
    }
}

void func_ovl0C_02_800475BC(UnkStructA *arg0) {
    s32 sp38;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    UnkStructA *var_a2;
    UnkStructA_40 *temp_v0;
    f32 temp_fv0;
    s32 temp_s0;
    s32 temp_v0_2;
    s32 var_at;
    s32 var_at_2;
    s32 var_s0;
    s32 var_s0_2;

    if (func_ovl0C_02_800494A0(0x41A) == 0) {
        temp_v0 = arg0->unk40;
        sp30 = temp_v0->unk10;
        sp2C = temp_v0->unk14;
        sp28 = temp_v0->unk18;
        temp_fv0 = arg0->unk6C;
        if ((temp_fv0 == 0.0f) && (arg0->unk68 == 0.0f)) {
            func_ovl0C_02_80049718(arg0, 0xC0, 12.0f);
        } else {
            arg0->unk68 = 0.0f;
            arg0->unk6C = temp_fv0 + 2.0f;
            func_ovl0C_02_80049718(arg0, 0xC0, 3.0f);
        }
        sp38 = 0;
        temp_v0_2 = arg0->unk8;
        var_a2 = NULL;
        if (temp_v0_2 & 3) {
            var_s0 = 0;
            if (temp_v0_2 & 2) {
                var_s0_2 = 0;
loop_8:
                var_at = var_s0_2 < 5;
                if (func_ovl0C_02_80048948(var_s0_2) != arg0) {
                    var_s0_2 += 1;
                    if (var_s0_2 == 5) {
                        var_at = var_s0_2 < 5;
                    } else {
                        goto loop_8;
                    }
                }
                if (var_at != 0) {
                    var_a2 = func_ovl0C_02_80048908(var_s0_2);
                } else {
                    var_a2 = NULL;
                }
            } else {
loop_15:
                var_at_2 = var_s0 < 5;
                if (func_ovl0C_02_80048908(var_s0) != arg0) {
                    var_s0 += 1;
                    if (var_s0 == 5) {
                        var_at_2 = var_s0 < 5;
                    } else {
                        goto loop_15;
                    }
                }
                if (var_at_2 != 0) {
                    var_a2 = func_ovl0C_02_80048948(var_s0);
                } else {
                    var_a2 = NULL;
                }
            }
        }
        temp_s0 = arg0->unkC;
        arg0->unkC = 0;
        if (var_a2 != NULL) {
            if (func_ovl0C_02_800491E8(arg0, 0x10, var_a2) != 0) {
                sp38 = 1;
            }
        } else if (func_ovl0C_02_80049078(arg0, 0x10) != 0) {
            sp38 = 1;
        }
        arg0->unkC = temp_s0;
        if (sp38 != 0) {
            arg0->unk40->unk10 = sp30;
            arg0->unk40->unk14 = sp2C;
            arg0->unk40->unk18 = sp28;
        }
    }
}

void func_ovl0C_02_80047538(void) {
    UnkStructA *obj;
    s32 alpha;
    s32 step;

    func_ovl0C_02_800488B8(1);
    func_ovl0C_02_80049238(10);
    obj = func_ovl0C_02_80048908(func_ovl0C_02_800488A8());
    func_ovl0C_02_800497A0(0x44);
    func_ovl0C_02_800490C8(obj, 0x80000);
    step = 0x11;
    for (alpha = 0xFF; alpha > 0; alpha -= step) {
        obj->unk40->unk36 = alpha;
        func_ovl0C_02_80049260();
    }
    obj->unk40->unk36 = 0;
    func_ovl0C_02_80049228();
}

void func_ovl0C_02_80047410(void) {
    f32 var_fs0;
    f32 var_fs0_2;

    var_fs0 = 0.0f;
    if (0.0f < 100.0f) {
        do {
            func_ovl0C_02_80049518(0xFF, 0xFF, 0xFF, var_fs0);
            func_ovl0C_02_80049260();
            var_fs0 += 20.0f;
        } while (var_fs0 < 100.0f);
    }
    func_ovl0C_02_80049518(0xFF, 0xFF, 0xFF, 100.0f);
    func_ovl0C_02_80049238(5);
    var_fs0_2 = 100.0f;
    if (0.0f < 100.0f) {
        do {
            func_ovl0C_02_80049518(0xFF, 0xFF, 0xFF, var_fs0_2);
            func_ovl0C_02_80049260();
            var_fs0_2 -= 2.5f;
        } while (var_fs0_2 > 0.0f);
    }
    func_ovl0C_02_80049518(0xFF, 0xFF, 0xFF, 0.0f);
    func_ovl0C_02_80049228();
}

void func_ovl0C_02_80046DD0(void) {
    f32 spC0;
    f32 spBC;
    f32 spB8;
    UnkStructA *spB4;
    void (*sp78)();
    UnkStructA *temp_s4;
    f32 temp_fs2;
    f32 temp_ft1;
    f32 temp_ft5;
    f32 var_fs0;
    f32 var_fs1;
    s16 var_s0;
    s16 var_s0_2;
    s16 var_s0_3;
    s32 var_s0_4;
    s32 var_s2;
    UnkStruct_ovl0C_02_80049AB0 *temp_v0;

    func_ovl0C_02_80048830(0);
    func_ovl0C_02_800488B8(1);
    temp_v0 = func_ovl0C_02_80049240();
    spB4 = temp_v0->unk0;
    func_ovl0C_02_80049490(temp_v0->unk10);
    func_ovl0C_02_80049238(0x1E);
    temp_s4 = func_ovl0C_02_80046B68(temp_v0);
    var_s0 = 0xFF;
loop_1:
    spB8 = temp_v0->unk4;
    spBC = temp_v0->unk8 + 150.0f;
    spC0 = temp_v0->unkC;
    func_ovl0C_02_80049670(0x12, &spB8, 0);
    func_ovl0C_02_80049670(0x11, &spB8, 0);
    func_ovl0C_02_80049670(0x12, &spB8, 0);
    func_ovl0C_02_800497C8(0x47, &spB8);
    func_ovl0C_02_800490D0(spB4, 0x01000000);
    do {
        temp_s4->unk40->unk36 = var_s0;
        func_ovl0C_02_80049260();
        var_s0 -= 0xA;
    } while (var_s0 > 0);
    temp_s4->unk40->unk36 = 0;
    func_ovl0C_02_800490E0(temp_s4);
    if ((func_ovl0C_02_800494A0(0x416) != 0) && (func_ovl0C_02_800494A0(0x417) != 0) && (func_ovl0C_02_800494A0(0x418) != 0) && (func_ovl0C_02_800494A0(0x419) != 0)) {
        func_ovl0C_02_80049238(0x3C);
        func_ovl0C_02_800497A0(0x58);
        var_fs1 = 20.0f;
        var_fs0 = 0.0f;
        temp_fs2 = D_ovl0C_02_80049B50->unk0->unk40->unk18;
        var_s0_2 = 0;
loop_8:
        temp_ft5 = func_ovl0C_02_800493C0(var_fs0) * var_fs1;
        var_fs0 += 20.0f;
        D_ovl0C_02_80049B50->unk0->unk40->unk18 = temp_ft5 + temp_fs2;
        if (!(var_fs0 >= 360.0f)) {
block_12:
            func_ovl0C_02_80049260();
            goto loop_8;
        }
        var_s0_2 += 1;
        var_fs1 -= 3.0f;
        if (var_s0_2 < 6) {
            var_fs0 -= 360.0f;
            goto block_12;
        }
        sp78 = func_ovl0C_02_80047410;
        var_s2 = 0;
        D_ovl0C_02_80049B50->unk0->unk40->unk18 = temp_fs2;
        func_ovl0C_02_800497A0(0x56);
        func_ovl0C_02_80049218(func_ovl0C_02_80046924, NULL, 0, 0, 0x110);
        func_ovl0C_02_80049238(0x3C);
        func_ovl0C_02_80049218(sp78, NULL, 0, 0, 0x110);
        D_ovl0C_02_80049B50->unk0->unk68 = 80.0f;
        D_ovl0C_02_80049B50->unk0->unk6C = 0.0f;
        D_ovl0C_02_80049B50->unk0->unk70 = 1.6333334f;
        func_ovl0C_02_800490C8(D_ovl0C_02_80049B50->unk0, 0x80000);
        var_s0_3 = 0xFF;
        D_ovl0C_02_80049B50->unk0->unk40->unk8 = 0x61;
loop_14:
        D_ovl0C_02_80049B50->unk0->unk40->unk36 = var_s0_3;
        if (var_s0_3 < 0x80) {
            D_ovl0C_02_80049B50->unk0->unk40->unk36 = 0x80;
        }
        func_ovl0C_02_80049148(D_ovl0C_02_80049B50->unk0);
        if ((var_s2 == 0) && (D_ovl0C_02_80049B50->unk0->unk68 < D_ovl0C_02_80049B50->unk0->unk6C)) {
            var_s2 = 1;
            func_ovl0C_02_800490D0(D_ovl0C_02_80049B60->unk0, 0x01000000);
        }
        if (D_ovl0C_02_80049B50->unk0->unk6C != 0.0f) {
block_22:
            func_ovl0C_02_80048F08(32768.0f, D_ovl0C_02_80049B50->unk0->unk40->unk14, 32768.0f);
            func_ovl0C_02_80049260();
            var_s0_3 -= 5;
            goto loop_14;
        }
        if (D_ovl0C_02_80049B50->unk0->unk68 != 0.0f) {
            goto block_22;
        }
        func_ovl0C_02_800497A0(0x59);
        D_ovl0C_02_80049B50->unk0->unk68 = 15.0f;
        D_ovl0C_02_80049B50->unk0->unk6C = 0.0f;
        D_ovl0C_02_80049B50->unk0->unk70 = 1.6333334f;
loop_24:
        func_ovl0C_02_80049148(D_ovl0C_02_80049B50->unk0);
        if (D_ovl0C_02_80049B50->unk0->unk6C != 0.0f) {
block_26:
            func_ovl0C_02_80049260();
            goto loop_24;
        }
        if (D_ovl0C_02_80049B50->unk0->unk68 != 0.0f) {
            goto block_26;
        }
        D_ovl0C_02_80049B50->unk0->unk68 = 10.0f;
        D_ovl0C_02_80049B50->unk0->unk6C = 0.0f;
        D_ovl0C_02_80049B50->unk0->unk70 = 1.6333334f;
loop_29:
        func_ovl0C_02_80049148(D_ovl0C_02_80049B50->unk0);
        if (D_ovl0C_02_80049B50->unk0->unk6C != 0.0f) {
block_32:
            func_ovl0C_02_80049260();
            goto loop_29;
        }
        if (D_ovl0C_02_80049B50->unk0->unk68 != 0.0f) {
            goto block_32;
        }
        func_ovl0C_02_80049238(0x3C);
        func_ovl0C_02_800497A0(0x2C);
        D_ovl0C_02_8004A100[0] = 22.0f * 100.0f;
        var_s0_4 = 0;
        D_ovl0C_02_8004A100[1] = 0.0f;
        do {
            temp_ft1 = (f32) func_ovl0C_02_80048730(var_s0_4);
            var_s0_4 += 1;
            D_ovl0C_02_8004A100[1] += temp_ft1 * 100.0f;
        } while (var_s0_4 < 5);
        D_ovl0C_02_8004A100[1] += 100.0f;
        D_ovl0C_02_8004A100[2] = (f32) 0xE * 100.0f;
        D_ovl0C_02_8004A0F0 = func_ovl0C_02_80049670(0x28, &D_ovl0C_02_8004A100[0], 0);
        func_ovl0C_02_80049490(0x415);
        func_ovl0C_02_80049238(0x78);
        func_ovl0C_02_80049238(0x28);
    }
    var_s0 = 0xFF;
    func_ovl0C_02_800487C0(temp_v0->unk14, temp_v0->unk18, 0);
    func_ovl0C_02_80049238(0x3C);
    goto loop_1;
}

UnkStructA *func_ovl0C_02_80046B68(UnkStruct_ovl0C_02_80049AB0 *arg0) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    f32 temp_fs4;
    f32 temp_fv0;
    f32 var_fs0;
    s16 var_s0;
    s16 var_s0_2;
    s16 var_s0_3;

    temp_v0 = func_ovl0C_02_80049110(0x2A7, 0xD0, arg0->unk4, arg0->unk8 + 1000.0f, arg0->unkC);
    func_ovl0C_02_800490C8(temp_v0, 0x03080000);
    temp_v0_2 = temp_v0->unk40;
    temp_v0_2->unkC |= 0x8000;
    func_ovl0C_02_80048DD0(temp_v0->unk40, 2);
    func_ovl0C_02_80048DD8(temp_v0->unk40, 0x2A8, 0, 0);
    func_ovl0C_02_80048DD8(temp_v0->unk40, 0x2A8, 1, 1);
    temp_fv0 = func_ovl0C_02_800493C0(1.25f);
    temp_v0->unk40->unk30 = temp_fv0;
    temp_v0->unk40->unk28 = temp_fv0;
    var_fs0 = 0.0f;
    temp_v0->unk40->unk2C = 11.0f;
    temp_v0->unk40->unk20 = 0.0f;
    temp_fs4 = temp_v0->unk40->unk14;
    func_ovl0C_02_800497A0(0x51);
    var_s0 = 0;
    do {
        temp_v0->unk40->unk14 = temp_fs4 - (func_ovl0C_02_800493C0((f32) var_s0) * 1000.0f);
        temp_v0->unk40->unk20 = var_fs0;
        func_ovl0C_02_80049260();
        var_s0 += 2;
        var_fs0 += 20.0f;
    } while (var_s0 < 0x5A);
    var_s0_2 = 5;
    do {
        temp_v0->unk40->unk30 = func_ovl0C_02_800493C0((f32) var_s0_2) * 3.0f;
        temp_v0_3 = temp_v0->unk40;
        temp_v0_3->unk28 = temp_v0_3->unk30;
        temp_v0->unk40->unk20 = var_fs0;
        func_ovl0C_02_80049260();
        var_s0_2 += 2;
        var_fs0 += 20.0f;
    } while (var_s0_2 < 0x5A);
    var_s0_3 = 0;
    do {
        temp_v0->unk40->unk2C = (func_ovl0C_02_800493C8((f32) var_s0_3) * 10.0f) + 1.0f;
        temp_v0->unk40->unk20 = var_fs0;
        func_ovl0C_02_80049260();
        var_s0_3 += 2;
        var_fs0 += 20.0f;
    } while (var_s0_3 < 0x5A);
    return temp_v0;
}

void func_ovl0C_02_80046B30(void) {
    func_ovl0C_02_80049218(func_ovl0C_02_80047410, NULL, 0, 0, 0x110);
}

void func_ovl0C_02_80046924(void) {
    UnkStructA *temp_s2;
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    UnkStructA_40 *temp_v0_4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fs0;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;

    temp_s2 = D_ovl0C_02_80049B50->unk0;
    var_s0 = 0;
    var_s1 = 0;
    var_fs0 = 0.0f;
    do {
        temp_v0 = temp_s2->unk40;
        temp_v0->unk20 += var_fs0;
        temp_v0_2 = temp_s2->unk40;
        temp_fv0 = temp_v0_2->unk20;
        if (temp_fv0 >= 360.0f) {
            temp_v0_2->unk20 = temp_fv0 - 360.0f;
        } else {
            if (temp_fv0 < 0.0f) {
                var_fv1 = temp_fv0 + 360.0f;
            } else {
                var_fv1 = temp_fv0;
            }
            temp_v0_2->unk20 = var_fv1;
        }
        if (var_fs0 < 10.0f) {
            var_s0 += 1;
            if (var_s0 >= 6) {
                var_fs0 += 1.0f;
                var_s0 = 0;
            }
        } else {
            var_fs0 = 10.0f;
        }
        func_ovl0C_02_80049260();
        var_s1 += 1;
    } while (var_s1 < 0x32);
    var_s0_2 = 0;
    var_s1_2 = 0;
    do {
        temp_v0_3 = temp_s2->unk40;
        temp_v0_3->unk20 += var_fs0;
        temp_v0_4 = temp_s2->unk40;
        temp_fv0_2 = temp_v0_4->unk20;
        if (temp_fv0_2 >= 360.0f) {
            temp_v0_4->unk20 = temp_fv0_2 - 360.0f;
        } else {
            if (temp_fv0_2 < 0.0f) {
                var_fv1_2 = temp_fv0_2 + 360.0f;
            } else {
                var_fv1_2 = temp_fv0_2;
            }
            temp_v0_4->unk20 = var_fv1_2;
        }
        if (var_fs0 > 0.0f) {
            var_s0_2 += 1;
            if (var_s0_2 >= 6) {
                var_fs0 -= 1.0f;
                var_s0_2 = 0;
            }
        } else {
            var_fs0 = 0.0f;
        }
        func_ovl0C_02_80049260();
        var_s1_2 += 1;
    } while (var_s1_2 != 0x32);
    func_ovl0C_02_80049228();
}

void func_ovl0C_02_800468EC(void) {
    func_ovl0C_02_80049218(func_ovl0C_02_80046924, NULL, 0, 0, 0x110);
}

void func_ovl0C_02_800467D8(void) {
    UnkStructA **temp_s0;
    UnkStructA_40 *temp_v0;
    UnkStructA_40 *temp_v0_2;
    s16 var_s1;
    s32 var_s2;

    temp_s0 = func_ovl0C_02_80049240();
    var_s1 = 0x1E;
    var_s2 = 0xA;
loop_1:
    func_ovl0C_02_800490D0(*temp_s0, 0x01000000);
    func_ovl0C_02_80049238(var_s2);
    func_ovl0C_02_800490C8(*temp_s0, 0x01000000);
    temp_v0 = (*temp_s0)->unk40;
    temp_v0->unk36 -= 2;
    temp_v0_2 = (*temp_s0)->unk40;
    if (temp_v0_2->unk36 < 0) {
        temp_v0_2->unk36 = 0;
        func_ovl0C_02_800490D0(*temp_s0, 0x01000000);
        func_ovl0C_02_800490E0(*temp_s0);
        func_ovl0C_02_80049228();
    }
    var_s2 = (s32) (s16) (var_s2 - 1);
    if (var_s2 <= 0) {
        var_s2 = 1;
    }
    var_s1 -= 3;
    if (var_s1 <= 0) {
        var_s1 = 1;
    }
    func_ovl0C_02_80049238((s32) var_s1);
    goto loop_1;
}

void func_ovl0C_02_8004679C(void) {
    func_ovl0C_02_80049218(func_ovl0C_02_800467D8, D_ovl0C_02_80049B60, 0, 0, 0x110);
}

void func_ovl0C_02_80046720(void) {
    func_ovl0C_02_800488B8(1);
    func_ovl0C_02_80048830(0);
    func_ovl0C_02_800488D0("WM1 WG1 WAP WSH WDE WB10 ST1");
    func_ovl0C_02_80049978(0x3C);
    func_ovl0C_02_80049950(1);
    if (func_ovl0C_02_80049960() != 0) {
        do {
            func_ovl0C_02_80049260();
        } while (func_ovl0C_02_80049960() != 0);
    }
    func_ovl0C_02_80049980();
    func_ovl0C_02_80049228();
}

void func_ovl0C_02_8004661C(void) {
    s32 var_s0;
    UnkStruct_ovl0C_02_80049C24 *temp_s0;

    temp_s0 = func_ovl0C_02_80049240();
    func_ovl0C_02_80048830(0);
    func_ovl0C_02_80049028();
    func_ovl0C_02_80048F70(0x7F);
    if (temp_s0 == D_ovl0C_02_80049C24) {
        func_ovl0C_02_80048F08(4300.0f, 400.0f, 2000.0f);
        func_ovl0C_02_80048F28(315.0f, 45.0f, 2400.0f);
    } else {
        func_ovl0C_02_80048F08(3900.0f, 400.0f, 1300.0f);
        func_ovl0C_02_80048F28(225.0f, 45.0f, 2400.0f);
    }
    var_s0 = 0;
    do {
        func_ovl0C_02_80049260();
        var_s0 += 1;
    } while (var_s0 != 0x168);
    func_ovl0C_02_80049030();
    func_ovl0C_02_80048FF8(D_ovl0C_02_8004A0D0);
    func_ovl0C_02_80048F68(0x1F);
    func_ovl0C_02_80048830(1);
    func_ovl0C_02_80049228();
}

void func_ovl0C_02_8004639C(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0x2:
        func_ovl0C_02_800460B0();
        break;
    case 0x11:
        func_ovl0C_02_80045318();
        break;
    case 0x13:
        func_ovl0C_02_800452B0();
        break;
    case 0x14:
        func_ovl0C_02_8004523C();
        break;
    case 0x15:
        func_ovl0C_02_800451CC();
        break;
    case 0x16:
        func_ovl0C_02_80045158();
        break;
    case 0x17:
        UNK_MACRO_ovl0C_02_80045098(7, 0xC0, 0x40, 0.0f, 0);
        break;
    case 0x18:
        UNK_MACRO_ovl0C_02_80045098(8, 0xC0, 0x40, 0.0f, 0);
        break;
    case 0x19:
        UNK_MACRO_ovl0C_02_80045098(9, 0xC0, 0x40, 0.0f, 0);
        break;
    case 0x1A:
        UNK_MACRO_ovl0C_02_80045098(0xA, 0xC0, 0x40, 0.0f, 0);
        break;
    case 0x1B:
        func_ovl0C_02_80045030();
        break;
    case 0x1C:
        func_ovl0C_02_80044FCC();
        break;
    case 0x1D:
        func_ovl0C_02_80044F68();
        break;
    case 0x1E:
        func_ovl0C_02_80044F00();
        break;
    case 0x1F:
        func_ovl0C_02_80044E9C();
        break;
    case 0x4:
        func_ovl0C_02_80044CD0();
        break;
    case 0x5:
        func_ovl0C_02_8004460C();
        break;
    case 0x50:
        func_ovl0C_02_80044150();
        break;
    case 0x52:
        func_ovl0C_02_80043FD8();
        break;
    case 0x3:
        func_ovl0C_02_80043B64();
        break;
    case 0xF:
        func_ovl0C_02_80043250();
        break;
    case 0xC:
        func_ovl0C_02_80048910(1);
        break;
    case 0x1:
        if (D_ovl0C_02_8004A110.unk0 == 0xD) {
            func_ovl0C_02_80043018();
        }
        break;
    }
}

void func_ovl0C_02_800460B0(void) {
    UnkStructA *temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    u32 (*var_s0)[3];

    func_ovl0C_02_80046038();
    func_ovl0C_02_800487B0(func_ovl0C_02_80048074);
    func_ovl0C_02_80048800(func_ovl0C_02_80047FB4);
    func_ovl0C_02_80049580(D_ovl0C_02_800499C0);
    func_ovl0C_02_80049598(D_ovl0C_02_800499E4);
    func_ovl0C_02_80049748(2);
    func_ovl0C_02_800486C8(0x243);
    var_s0 = D_ovl0C_02_800499FC;
    var_s1 = 0;
    do {
        func_ovl0C_02_80049728((s32) var_s0[0][0], (s32) var_s0[0][1], (s32) var_s0[0][2]);
        var_s1 += 1;
        var_s0 += 0xC;
    } while (var_s1 < 5);
    func_ovl0C_02_800486E0(0x24D);
    func_ovl0C_02_80048878();
    func_ovl0C_02_800487A8(func_ovl0C_02_800477B0, 1);
    func_ovl0C_02_800487A8(func_ovl0C_02_800475BC, 5);
    func_ovl0C_02_80045E8C();
    func_ovl0C_02_80045B50();
    func_ovl0C_02_80045898();
    func_ovl0C_02_80045780();
    func_ovl0C_02_80045668();
    func_ovl0C_02_80045538();
    temp_v0 = func_ovl0C_02_80049110(D_ovl0C_02_80049EEC.unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    D_ovl0C_02_80049EEC.unk0 = temp_v0;
    func_ovl0C_02_800490C8(temp_v0, 0x01080000);
    func_ovl0C_02_800490D0(D_ovl0C_02_80049EEC.unk0, 0x02000000);
    if (D_ovl0C_02_80049EEC.unkC != -1) {
        if ((D_ovl0C_02_80049EEC.unkE != -1) && (D_ovl0C_02_80049EEC.unk10 != -1)) {
            if (D_ovl0C_02_80049EEC.unk12 != -1) {
                temp_v0_2 = func_ovl0C_02_80048E10(D_ovl0C_02_80049EEC.unk0->unk40, 0, (s32) D_ovl0C_02_80049EEC.unkC, (s32) D_ovl0C_02_80049EEC.unkE, (s32) D_ovl0C_02_80049EEC.unk10, (s32) D_ovl0C_02_80049EEC.unk12);
                D_ovl0C_02_80049EEC.unk4 = temp_v0_2;
                if (temp_v0_2 == -1) {
loop_7:
                    goto loop_7;
                }
            }
            goto block_8;
        }
        goto block_9;
    }
block_8:
block_9:
    D_ovl0C_02_80049EEC.unk0->unk40->unk10 = 0.0f * 10.0f;
    D_ovl0C_02_80049EEC.unk0->unk40->unk14 = 0.0f * 10.0f;
    D_ovl0C_02_80049EEC.unk0->unk40->unk18 = 0.0f * 10.0f;
    D_ovl0C_02_80049EEC.unk0->unk40->unk1C = 0.0f;
    D_ovl0C_02_80049EEC.unk0->unk40->unk20 = 0.0f;
    D_ovl0C_02_80049EEC.unk0->unk40->unk24 = 0.0f;
    D_ovl0C_02_80049EEC.unk0->unk40->unk28 = 0.0f;
    D_ovl0C_02_80049EEC.unk0->unk40->unk2C = 0.0f;
    D_ovl0C_02_80049EEC.unk0->unk40->unk30 = 1.0f;
    if (func_ovl0C_02_800494A0(0x41A) != 0) {
        func_ovl0C_02_80048E18(D_ovl0C_02_80049EEC.unk4);
        D_ovl0C_02_80049EEC.unk4 = func_ovl0C_02_80048E10(D_ovl0C_02_80049EEC.unk0->unk40, 0, 0xA, 0x400, (s32) D_ovl0C_02_80049EEC.unk10, (s32) D_ovl0C_02_80049EEC.unk12);
    }
    func_ovl0C_02_800454B4();
}

void func_ovl0C_02_80046078(void) {
    func_ovl0C_02_80046038();
    func_ovl0C_02_800487B0(func_ovl0C_02_80048074);
    func_ovl0C_02_80048800(func_ovl0C_02_80047FB4);
}

void func_ovl0C_02_80046038(void) {
    func_ovl0C_02_80049498(0x400);
    func_ovl0C_02_80049498(0x401);
    func_ovl0C_02_80049498(0x402);
    func_ovl0C_02_80049498(0x403);
    func_ovl0C_02_80049498(0x404);
}

void func_ovl0C_02_80046030(void) {
}

void func_ovl0C_02_80045E8C(void) {
    UnkStruct_ovl0C_02_80049A38 *p;
    f32 angle;
    UnkStructA *obj;
    s16 i;

    for (i = 0; i < 1; i++) {
        func_ovl0C_02_80045DD0(i);
        p = &D_ovl0C_02_80049A38[i];
        obj = func_ovl0C_02_80049110(0x2A9, 0xD0, p->unk8, p->unkC, p->unk10);
        func_ovl0C_02_800490C8(obj, 0x01000000);
        switch (p->unk14) {
            case 0:
                angle = 270.0f;
                break;
            case 0x40:
                angle = 180.0f;
                break;
            case 0x80:
                angle = 90.0f;
                break;
            case 0xC0:
                angle = 0.0f;
                break;
        }
        obj->unk40->unk20 = angle;
        p->unk4 = obj;
        func_ovl0C_02_80045D74(p);
    }
}

void func_ovl0C_02_80045DD0(s32 arg0) {
    D_ovl0C_02_8004A128[arg0] = func_ovl0C_02_800490F0(-1, 0, 0x20, 0);
    D_ovl0C_02_8004A128[arg0]->unk40->unk10 = D_ovl0C_02_80049A38[arg0].unk18;
    D_ovl0C_02_8004A128[arg0]->unk40->unk14 = D_ovl0C_02_80049A38[arg0].unk1C;
    D_ovl0C_02_8004A128[arg0]->unk40->unk18 = D_ovl0C_02_80049A38[arg0].unk20;
    D_ovl0C_02_8004A128[arg0]->unk30 = 1;
    D_ovl0C_02_8004A128[arg0]->unk34 = 200.0f;
    D_ovl0C_02_8004A128[arg0]->unk38 = 100.0f;
}

void func_ovl0C_02_80045D74(UnkStruct_ovl0C_02_80049A38 *arg0) {
    func_ovl0C_02_80043010();
    arg0->unk4->unk40->unk48->unk4->unk4 = func_ovl0C_02_80048E08(arg0->unk4->unk40, 0) - 0.0001f;
    func_ovl0C_02_80043A0C(arg0);
}

void func_ovl0C_02_80045B50(void) {
    UnkStructA *temp_v0;
    UnkStructA *temp_v0_2;
    UnkStruct_ovl0C_02_80049B50 *temp_s4;
    f32 temp_ft0;
    s16 var_s5;
    s32 var_s0;

    var_s5 = 0;
    do {
        temp_s4 = &D_ovl0C_02_80049B50[var_s5];
        temp_v0 = func_ovl0C_02_80049110(0x2A5, 0xD0, temp_s4->unk4, temp_s4->unk8, temp_s4->unkC);
        temp_v0_2 = func_ovl0C_02_80049100(temp_v0);
        temp_v0_2->unk54 = 2.0f;
        temp_v0_2->unk4C = 2.0f;
        temp_v0_2->unk40->unk36 = 0x19;
        func_ovl0C_02_800490C8(temp_v0, 0x0F000000);
        if ((func_ovl0C_02_800494A0(0x416) != 0) && (func_ovl0C_02_800494A0(0x417) != 0) && (func_ovl0C_02_800494A0(0x418) != 0) && (func_ovl0C_02_800494A0(0x419) != 0)) {
            func_ovl0C_02_800490C8(temp_v0, 0x80000);
            temp_v0->unk40->unk36 = 0x80;
            temp_v0->unk40->unk8 = 0x61;
            func_ovl0C_02_80045A7C();
        }
        var_s5 += 1;
        temp_s4->unk0 = temp_v0;
    } while (var_s5 <= 0);
}

void func_ovl0C_02_80045A7C(void) {
    func_ovl0C_02_80045A74(22.0f, 14, 5);
}

/* ovl_12_03's func_ovl12_03_8004316C; inlined into func_ovl0C_02_80045A7C
 * only, which is inlined into its callers in turn.  The body on one line
 * (a macro), as there. */
#define UNK_MACRO_ovl0C_02_80045A74()                                                     \
    D_ovl0C_02_8004A100[0] = x * 100.0f;                                                  \
    D_ovl0C_02_8004A100[1] = 0.0f;                                                        \
    for (i = 0; i < count; i++) {                                                         \
        D_ovl0C_02_8004A100[1] += func_ovl0C_02_80048730(i) * 100.0f;                     \
    }                                                                                     \
    D_ovl0C_02_8004A100[1] += 100.0f;                                                     \
    D_ovl0C_02_8004A100[2] = z * 100.0f;                                                  \
    D_ovl0C_02_8004A0F0 = func_ovl0C_02_80049670(0x28, D_ovl0C_02_8004A100, 0)

static void func_ovl0C_02_80045A74(f32 x, s32 z, s32 count) {
    s32 i;

    UNK_MACRO_ovl0C_02_80045A74();
    if (!i && !i) {
    }
}

void func_ovl0C_02_80045898(void) {
    UnkStructA *temp_v0;
    UnkStruct_ovl0C_02_80049B60 *temp_s0;
    s16 var_s1;

    if ((func_ovl0C_02_800494A0(0x416) == 0) || (func_ovl0C_02_800494A0(0x417) == 0) || (func_ovl0C_02_800494A0(0x418) == 0) || (func_ovl0C_02_800494A0(0x419) == 0)) {
        var_s1 = 0;
        do {
            temp_s0 = &D_ovl0C_02_80049B60[var_s1];
            temp_v0 = func_ovl0C_02_80049110(0x2B1, 0xD0, temp_s0->unk4, temp_s0->unk8, temp_s0->unkC);
            func_ovl0C_02_800490C8(temp_v0, 0x01080000);
            temp_s0->unk0 = temp_v0;
            var_s1 += 1;
            temp_v0->unk40->unk36 = 0x80;
        } while (var_s1 <= 0);
        return;
    }
    func_ovl0C_02_80048708(D_ovl0C_02_80049B60->unk10, D_ovl0C_02_80049B60->unk14, D_ovl0C_02_80049B60->unk18, D_ovl0C_02_80049B60->unk1C, D_ovl0C_02_80049B60->unk20, 0x11);
    func_ovl0C_02_80048708(0x17, 5, 0xE, 0x18, 0xF, 0x12);
    func_ovl0C_02_80048708(0x15, 5, 0xC, 0x15, 0xC, 0x1F);
    func_ovl0C_02_80048708(0x1A, 5, 0xC, 0x1A, 0xC, 0x1F);
    func_ovl0C_02_80048708(0x15, 5, 0x11, 0x15, 0x11, 0x1F);
    func_ovl0C_02_80048708(0x1A, 5, 0x11, 0x1A, 0x11, 0x1F);
}

void func_ovl0C_02_80045780(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStruct_ovl0C_02_80049AB0 *temp_s0;
    s16 var_s2;

    var_s2 = 0;
    do {
        temp_s0 = &D_ovl0C_02_80049AB0[var_s2];
        if (func_ovl0C_02_800494A0(temp_s0->unk10) == 0) {
            temp_v0 = func_ovl0C_02_80049110(0x2A3, 0xD0, temp_s0->unk4, temp_s0->unk8, temp_s0->unkC);
            func_ovl0C_02_800490C8(temp_v0, 0x03080000);
            temp_s0->unk0 = temp_v0;
            temp_v0_2 = temp_v0->unk40;
            temp_v0_2->unkC |= 0x8000;
            func_ovl0C_02_80048DD0(temp_s0->unk0->unk40, 2);
            func_ovl0C_02_80048DD8(temp_s0->unk0->unk40, 0x2A4, 0, 0);
            func_ovl0C_02_80048DD8(temp_s0->unk0->unk40, 0x2A4, 1, 1);
        }
        var_s2 += 1;
    } while (var_s2 < 4);
}

void func_ovl0C_02_80045668(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStruct_ovl0C_02_80049B20 *temp_s0;
    s16 var_s2;

    var_s2 = 0;
    do {
        temp_s0 = &D_ovl0C_02_80049B20[var_s2];
        if (func_ovl0C_02_800494A0(temp_s0->unk14) == 0) {
            temp_v0 = func_ovl0C_02_80049110(0x2A7, 0xD0, temp_s0->unk4, temp_s0->unk8, temp_s0->unkC);
            func_ovl0C_02_800490C8(temp_v0, 0x03080000);
            temp_s0->unk0 = temp_v0;
            temp_v0_2 = temp_v0->unk40;
            temp_v0_2->unkC |= 0x8000;
            func_ovl0C_02_80048DD0(temp_s0->unk0->unk40, 2);
            func_ovl0C_02_80048DD8(temp_s0->unk0->unk40, 0x2A8, 0, 0);
            func_ovl0C_02_80048DD8(temp_s0->unk0->unk40, 0x2A8, 1, 1);
        }
        var_s2 += 1;
    } while (var_s2 < 2);
}

void func_ovl0C_02_80045538(void) {
    UnkStructA *temp_v0;
    UnkStruct_ovl0C_02_80049F24 *temp_s0;
    s16 var_s3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s2_2;

    func_ovl0C_02_800448CC();
    var_s3 = 0;
    do {
        temp_s0 = &D_ovl0C_02_80049F24[var_s3];
        if (func_ovl0C_02_800494A0(temp_s0->unk28) == 0) {
            temp_v0 = func_ovl0C_02_80049110(temp_s0->unk4, 0xD0, temp_s0->unk8, temp_s0->unkC, temp_s0->unk10);
            func_ovl0C_02_800490C8(temp_v0, 0x03000000);
            temp_s1 = temp_s0->unk14;
            temp_s2 = temp_s0->unk1C;
            temp_s0->unk0 = temp_v0;
            func_ovl0C_02_80048708(temp_s1, temp_s0->unk20, temp_s2, temp_s1 + 1, temp_s2 + 1, 0x11);
            temp_s1_2 = temp_s0->unk14;
            temp_s2_2 = temp_s0->unk1C;
            func_ovl0C_02_80048710(temp_s1_2, temp_s0->unk24, temp_s2_2, temp_s1_2 + 1, temp_s0->unk18, temp_s2_2 + 1, 0x1F);
        }
        var_s3 += 1;
    } while (var_s3 < 4);
}

void func_ovl0C_02_800454B4(void) {
    UnkStructA *sp2C;
    Vec3f sp20;
    UnkStructA *temp_v0;

    if (func_ovl0C_02_80045448() != 0) {
        func_ovl0C_02_800453CC(&sp20);
        temp_v0 = func_ovl0C_02_80049110(0x328, 0xC0, sp20.x, sp20.y, sp20.z);
        sp2C = temp_v0;
        D_ovl0C_02_80049FE4->unk0 = temp_v0;
        func_ovl0C_02_80049100(temp_v0);
        func_ovl0C_02_800490C8(sp2C, 0x03000010);
        func_ovl0C_02_80045378(sp2C);
    }
}

s32 func_ovl0C_02_80045448(void) {
    s32 var_v0;

    if (func_ovl0C_02_80048818()[4] != 0) {
        return 0;
    }
    if (func_ovl0C_02_80049480(0xA4) != 0) {
        return 0;
    }
    var_v0 = 1;
    if (func_ovl0C_02_800431D4() < 5) {
        var_v0 = 0;
    }
    return var_v0;
}

void func_ovl0C_02_800453CC(Vec3f *arg0) {
    if (func_ovl0C_02_800494A0(0x415) == 0) {
        arg0->x = 2000.0f;
        arg0->y = 400.0f;
        arg0->z = 3100.0f;
        return;
    }
    arg0->x = 1800.0f;
    arg0->y = 800.0f;
    arg0->z = 1200.0f;
}

void func_ovl0C_02_80045378(UnkStructA *arg0) {
    if (func_ovl0C_02_800494A0(0x415) == 0) {
        arg0->unk40->unk20 = 180.0f;
        return;
    }
    arg0->unk40->unk20 = 270.0f;
}

void func_ovl0C_02_80045318(void) {
    func_ovl0C_02_80048880(0x23, 2, 0x10);
    UNK_MACRO_ovl0C_02_80045098(1, 0x40, 0x40, 0.0f, 0);
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
}

void func_ovl0C_02_800452B0(void) {
    func_ovl0C_02_80048880(1, 1, 0xE);
    UNK_MACRO_ovl0C_02_80045098(3, 0x40, 0xC0, 0.0f, 4);
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
}

void func_ovl0C_02_8004523C(void) {
    func_ovl0C_02_80048880(0x20, 5, 0x1E);
    UNK_MACRO_ovl0C_02_80045098(4, 0x40, 0xC0, 0.0f, 1);
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
    func_ovl0C_02_80048850(0x29, 0x1E);
}

void func_ovl0C_02_800451CC(void) {
    func_ovl0C_02_80048880(0x25, 1, 1);
    UNK_MACRO_ovl0C_02_80045098(5, 0, 0x80, 0.0f, 1);
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
    func_ovl0C_02_80048850(0x29, 0x1F);
}

void func_ovl0C_02_80045158(void) {
    func_ovl0C_02_80048880(0x2E, 4, 6);
    UNK_MACRO_ovl0C_02_80045098(6, 0xC0, 0x40, 0.0f, 1);
    func_ovl0C_02_80048850(0x28, 0x17);
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
}

void func_ovl0C_02_80045128(void) {
    UNK_MACRO_ovl0C_02_80045098(7, 0xC0, 0x40, 0.0f, 0);
}

void func_ovl0C_02_800450F8(void) {
    UNK_MACRO_ovl0C_02_80045098(8, 0xC0, 0x40, 0.0f, 0);
}

void func_ovl0C_02_800450C8(void) {
    UNK_MACRO_ovl0C_02_80045098(9, 0xC0, 0x40, 0.0f, 0);
}

void func_ovl0C_02_80045098(void) {
    UNK_MACRO_ovl0C_02_80045098(0xA, 0xC0, 0x40, 0.0f, 0);
}

void func_ovl0C_02_80045030(void) {
    func_ovl0C_02_80048880(0x1E, 3, 0x19);
    UNK_MACRO_ovl0C_02_80045098(0xB, 0x40, 0xC0, 0.0f, 0);
    func_ovl0C_02_80049030();
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
}

void func_ovl0C_02_80044FCC(void) {
    func_ovl0C_02_80048880(0x29, 2, 9);
    UNK_MACRO_ovl0C_02_80045098(0xC, 0, 0x80, 0.0f, 0);
    func_ovl0C_02_80049030();
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
}

void func_ovl0C_02_80044F68(void) {
    func_ovl0C_02_80048880(9, 1, 0xE);
    UNK_MACRO_ovl0C_02_80045098(0xD, 0x40, 0x20, 0.0f, 0);
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
}

void func_ovl0C_02_80044F00(void) {
    func_ovl0C_02_80048880(0x20, 5, 0x1E);
    UNK_MACRO_ovl0C_02_80045098(0xE, 0x40, 0xC0, 0.0f, 1);
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
}

void func_ovl0C_02_80044E9C(void) {
    func_ovl0C_02_80048880(0x25, 1, 1);
    UNK_MACRO_ovl0C_02_80045098(0xF, 0, 0x80, 0.0f, 1);
    func_ovl0C_02_80049568(0x37, 0x4D, 0xFF);
}

void func_ovl0C_02_80044E74(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    UNK_MACRO_ovl0C_02_80045098(arg0, arg1, arg2, arg3, arg4);
}

void func_ovl0C_02_80044CD0(void) {
    s32 sp1C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v1;

    func_ovl0C_02_80044BA0();
    temp_v0 = D_ovl0C_02_8004A110.unk0;
    switch (temp_v0) {                              /* irregular */
    case 12:
        break;
    default:
        func_ovl0C_02_80049498(0x429);
        /* fallthrough */
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        break;
    }
    var_v1 = 1;
    if ((temp_v0 == 7) || (temp_v0 == 8) || (temp_v0 == 9) || (temp_v0 == 0xA)) {
        var_v1 = 0;
    }
    sp1C = var_v1;
    if (func_ovl0C_02_800494A0(0x40D) == 0) {
        func_ovl0C_02_80044A68(D_ovl0C_02_80049ECC, D_ovl0C_02_80049C24, sp1C);
        func_ovl0C_02_80044914(D_ovl0C_02_80049B84, sp1C);
    }
    if (func_ovl0C_02_800494A0(0x40E) == 0) {
        func_ovl0C_02_80044A68(D_ovl0C_02_80049EDC, D_ovl0C_02_80049DB4, sp1C);
        func_ovl0C_02_80044914(D_ovl0C_02_80049D3C, sp1C);
    }
    temp_v0_2 = D_ovl0C_02_8004A110.unk0;
    if (temp_v0_2 == 0xD) {
        func_ovl0C_02_80044868();
    }
    if ((temp_v0_2 == 4) || (temp_v0_2 == 5)) {
        func_ovl0C_02_80044810();
    }
    if (temp_v0_2 == 3) {
        func_ovl0C_02_800447D4(D_ovl0C_02_80049A38);
    }
    if ((temp_v0_2 == 0xB) || (temp_v0_2 == 0xC)) {
        if (func_ovl0C_02_800494A0(0x429) != 0) {
            func_ovl0C_02_800447D4(D_ovl0C_02_80049A38);
        }
    }
}

void func_ovl0C_02_80044BA0(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_02_800488D8();
    switch (D_ovl0C_02_8004A110.unk8) {
        case 0:
            angle = 0.0f;
            break;
        case 0x80:
            angle = 180.0f;
            break;
        case 0xC0:
            angle = 90.0f;
            break;
        case 0x40:
            angle = 270.0f;
            break;
        case 1:
        default:
            angle = 360.0f;
            break;
    }
    if (angle != 360.0f) {
        func_ovl0C_02_80048F28(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_02_8004A110.unkC;
        func_ovl0C_02_80048F30(&sp1C, NULL, NULL);
        func_ovl0C_02_80048F28(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_02_800488C0(D_ovl0C_02_8004A110.unk4);
    func_ovl0C_02_80048FC0(45.0f, 45.1f);
}

void func_ovl0C_02_80044B58(f32 arg0) {
    f32 sp1C;

    func_ovl0C_02_80048F30(&sp1C, NULL, NULL);
    func_ovl0C_02_80048F28(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl0C_02_80044A68(UnkStruct_ovl0C_02_80049B50 *arg0, UnkStruct_ovl0C_02_80049C24 *arg1, s32 arg2) {
    UnkStructA *temp_s2;
    UnkStruct_ovl0C_02_80049C24 *var_s0;
    s16 temp_s1;
    s16 temp_s1_2;
    s16 temp_s2_2;
    s16 temp_s2_3;
    s16 temp_t2;

    var_s0 = arg1;
    temp_s2 = func_ovl0C_02_80049110(0x2BB, 0xD0, arg0->unk4, arg0->unk8, arg0->unkC);
    if (arg2 == 0) {

    }
    func_ovl0C_02_800490C8(temp_s2, 0x01000000);
    arg0->unk0 = temp_s2;
    if (var_s0->unk2 != 0) {
        do {
            temp_s1 = var_s0->unk18;
            temp_s2_2 = var_s0->unk1C;
            func_ovl0C_02_80048708((s32) temp_s1, (s32) var_s0->unk1A, (s32) temp_s2_2, temp_s1 + 3, temp_s2_2 + 2, 0x11);
            temp_s1_2 = var_s0->unk18;
            temp_s2_3 = var_s0->unk1C;
            func_ovl0C_02_80048708((s32) temp_s1_2, (s32) var_s0->unk1E, (s32) temp_s2_3, temp_s1_2 + 3, temp_s2_3 + 2, 0x1F);
            var_s0 += 1;
        } while (var_s0->unk2 != 0);
    }
}

void func_ovl0C_02_80044914(UnkStruct_ovl0C_02_80049B84 *arg0, s32 arg1) {
    UnkStructA *temp_s1;
    UnkStruct_ovl0C_02_80049B84 *var_s0;
    s16 temp_a0;
    s16 temp_a2;
    s16 temp_t4;

    var_s0 = arg0;
    func_ovl0C_02_800448CC();
    if (var_s0->unk2 != 0) {
        do {
            temp_s1 = func_ovl0C_02_80049110(0x2AE, 0xD0, var_s0->unk8, var_s0->unkC, var_s0->unk10);
            if (arg1 == 0) {

            }
            func_ovl0C_02_800490C8(temp_s1, 0x01000000);
            var_s0->unk4 = temp_s1;
            var_s0->unk22 = 0;
            func_ovl0C_02_80048DD0(temp_s1->unk40, 2);
            if (func_ovl0C_02_800494A0(var_s0->unk24) == 0) {
                func_ovl0C_02_80048DD8(var_s0->unk4->unk40, 0x2AF, 0, 0);
                func_ovl0C_02_80048DD8(var_s0->unk4->unk40, 0x2AF, 1, 1);
            } else {
                func_ovl0C_02_80048DD8(var_s0->unk4->unk40, 0x2AF, 0, 2);
                func_ovl0C_02_80048DD8(var_s0->unk4->unk40, 0x2AF, 1, 3);
            }
            temp_a0 = var_s0->unk18;
            temp_a2 = var_s0->unk1C;
            func_ovl0C_02_80048710((s32) temp_a0, (s32) var_s0->unk1A, (s32) temp_a2, temp_a0 + 1, (s32) var_s0->unk1E, temp_a2 + 1, 0x1F);
            var_s0 += 1;
        } while (var_s0->unk2 != 0);
    }
}

void func_ovl0C_02_800448CC(void) {
    if (func_ovl0C_02_800494A0(0x400) == 0) {
        D_ovl0C_02_8004A124 = func_ovl0C_02_800490F0(-1, 0, 0x20, 0);
        func_ovl0C_02_80049490(0x400);
    }
}

void func_ovl0C_02_80044868(void) {
    func_ovl0C_02_80048F28(-45.0f, 32768.0f, 32768.0f);
    func_ovl0C_02_80049218(func_ovl0C_02_80046720, NULL, 0, 0, 0x130);
    func_ovl0C_02_80048F70(0xF);
    func_ovl0C_02_80048F80(1);
}

void func_ovl0C_02_80044810(void) {
    D_ovl0C_02_8004A10C = func_ovl0C_02_80048908(func_ovl0C_02_800488A8());
    func_ovl0C_02_800490C8(D_ovl0C_02_8004A10C, 0x80000);
    D_ovl0C_02_8004A10C->unk40->unk36 = 0;
}

void func_ovl0C_02_800447D4(UnkStruct_ovl0C_02_80049A38 *arg0) {
    arg0->unk4->unk40->unk48->unk4->unk4 = 0.0f;
    func_ovl0C_02_80044710(arg0);
}

void func_ovl0C_02_80044710(UnkStruct_ovl0C_02_80049A38 *arg0) {
    func_ovl0C_02_80048710(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk34, arg0->unk38, 0x10);
    func_ovl0C_02_80048708(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk38, 0x11);
    func_ovl0C_02_80048708(arg0->unk3C, arg0->unk40, arg0->unk44, arg0->unk48, arg0->unk4C, 0x12);
    func_ovl0C_02_80048700(arg0->unk50, arg0->unk54, arg0->unk58, arg0->unk60);
    func_ovl0C_02_80048700(arg0->unk64, arg0->unk68, arg0->unk6C, arg0->unk74);
}

void func_ovl0C_02_8004460C(void) {
    s32 temp_v0;

    if ((D_ovl0C_02_8004A110.unk0 == 4) || (D_ovl0C_02_8004A110.unk0 == 5)) {
        func_ovl0C_02_80044580();
    }
    func_ovl0C_02_800488C8(D_ovl0C_02_8004A110.unk4, 3, 4.0f, D_ovl0C_02_8004A110.unk10, 0, 1, 1);
    temp_v0 = D_ovl0C_02_8004A110.unk0;
    if (temp_v0 == 7) {
        func_ovl0C_02_800444D4(D_ovl0C_02_80049AB0);
    }
    if (temp_v0 == 8) {
        func_ovl0C_02_800444D4(D_ovl0C_02_80049ACC);
    }
    if (temp_v0 == 9) {
        func_ovl0C_02_800444D4(D_ovl0C_02_80049AE8);
    }
    if (temp_v0 == 0xA) {
        func_ovl0C_02_800444D4(D_ovl0C_02_80049B04);
    }
    if (func_ovl0C_02_800494A0(0x429) == 0) {
        func_ovl0C_02_800442E0();
    }
}

void func_ovl0C_02_80044580(void) {
    s32 alpha;
    s32 step;

    func_ovl0C_02_800488B8(1);
    func_ovl0C_02_800497A0(0x45);
    step = 0x11;
    for (alpha = 0; alpha < 0xFF; alpha += step) {
        D_ovl0C_02_8004A10C->unk40->unk36 = alpha;
        func_ovl0C_02_80049260();
    }
    D_ovl0C_02_8004A10C->unk40->unk36 = 0xFF;
    func_ovl0C_02_800490D0(D_ovl0C_02_8004A10C, 0x80000);
    func_ovl0C_02_800488B8(0);
}

void func_ovl0C_02_80044538(void) {
    func_ovl0C_02_800488C8(D_ovl0C_02_8004A110.unk4, 3, 4.0f, D_ovl0C_02_8004A110.unk10, 0, 1, 1);
}

void func_ovl0C_02_800444D4(UnkStruct_ovl0C_02_80049AB0 *arg0) {
    func_ovl0C_02_80048838(1);
    func_ovl0C_02_80048830(0);
    func_ovl0C_02_800488B8(1);
    func_ovl0C_02_80044384();
    func_ovl0C_02_80049218(func_ovl0C_02_80046DD0, arg0, 0, 0, 0x110);
    func_ovl0C_02_800488B8(0);
}

void func_ovl0C_02_80044384(void) {
    s16 sp36;
    f32 var_fs0;

    if ((func_ovl0C_02_800494A0(0x416) == 0) && (func_ovl0C_02_800494A0(0x417) == 0) && (func_ovl0C_02_800494A0(0x418) == 0) && (func_ovl0C_02_800494A0(0x419) == 0)) {
        sp36 = 1;
        var_fs0 = D_ovl0C_02_80049B50->unk8 - 1000.0f;
    } else {
        var_fs0 = D_ovl0C_02_80049B50->unk8;
        sp36 = 0;
    }
    func_ovl0C_02_80048F70(0x7F);
    func_ovl0C_02_80048F08(D_ovl0C_02_80049B50->unk4, var_fs0, D_ovl0C_02_80049B50->unkC);
    func_ovl0C_02_80048F28(-90.0f, 45.0f, 2000.0f);
    if (sp36 == 1) {
        if (var_fs0 < D_ovl0C_02_80049B50->unk8) {
            do {
                func_ovl0C_02_80048F08(D_ovl0C_02_80049B50->unk4, var_fs0, D_ovl0C_02_80049B50->unkC);
                func_ovl0C_02_80049260();
                var_fs0 += 5.0f;
            } while (var_fs0 < D_ovl0C_02_80049B50->unk8);
        }
        func_ovl0C_02_80048F08(D_ovl0C_02_80049B50->unk4, D_ovl0C_02_80049B50->unk8, D_ovl0C_02_80049B50->unkC);
    }
}

void func_ovl0C_02_8004434C(void *arg0) {
    func_ovl0C_02_80049218(func_ovl0C_02_80046DD0, arg0, 0, 0, 0x110);
}

void func_ovl0C_02_800442E0(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0C_02_80049218(func_ovl0C_02_8004797C, &D_ovl0C_02_80049A38[i], 0, 0, 0x110);
    }
}

void func_ovl0C_02_80044150(void) {
    if (func_ovl0C_02_80048890(3, 4, 3, 7) != 0) {
        func_ovl0C_02_800487C0(0x28, 0x13, 0);
    }
    if (func_ovl0C_02_80048890(1, 0xE, 1, 0xF) != 0) {
        func_ovl0C_02_800440E4(D_ovl0C_02_80049A38);
        func_ovl0C_02_800487C0(0x28, 0x14, 0);
    }
    if (func_ovl0C_02_80048890(0x1F, 0x1E, 0x20, 0x1F) != 0) {
        func_ovl0C_02_80049218(func_ovl0C_02_80047538, NULL, 0, 0, 0x130);
        func_ovl0C_02_80048868(0x3C);
        func_ovl0C_02_800487C0(0x2B, 0x12, 4);
    }
    if (func_ovl0C_02_80048890(0x25, 1, 0x26, 1) != 0) {
        func_ovl0C_02_80049218(func_ovl0C_02_80047538, NULL, 0, 0, 0x130);
        func_ovl0C_02_80048868(0x3C);
        func_ovl0C_02_800487C0(0x2C, 0x12, 4);
    }
    if (func_ovl0C_02_80048890(0x2E, 5, 0x2E, 6) != 0) {
        func_ovl0C_02_800487C0(0x2C, 0x13, 0);
    }
    if (func_ovl0C_02_80048890(0x17, 0xE, 0x18, 0xF) != 0) {
        func_ovl0C_02_80049490(0x42B);
        func_ovl0C_02_80048978();
        func_ovl0C_02_800496A8();
        func_ovl0C_02_80049788();
        func_ovl0C_02_80049678(D_ovl0C_02_8004A0F0);
        func_ovl0C_02_800487E8();
    }
}

void func_ovl0C_02_800440E4(UnkStruct_ovl0C_02_80049A38 *arg0) {
    func_ovl0C_02_800488B8(1);
    func_ovl0C_02_800497A0(0x4B);
    func_ovl0C_02_800490C8(arg0->unk4, 0x04000000);
    func_ovl0C_02_80049238(60);
    func_ovl0C_02_800497A0(0x46);
    func_ovl0C_02_80043A0C(arg0);
    func_ovl0C_02_80049498(0x429);
    func_ovl0C_02_80049238(10);
}

void func_ovl0C_02_80044094(void) {
    func_ovl0C_02_80049490(0x42B);
    func_ovl0C_02_80048978();
    func_ovl0C_02_800496A8();
    func_ovl0C_02_80049788();
    func_ovl0C_02_80049678(D_ovl0C_02_8004A0F0);
    func_ovl0C_02_800487E8();
}

void func_ovl0C_02_80043FD8(void) {
    if (func_ovl0C_02_80048890(0x1E, 0x19, 0x1E, 0x19) != 0) {
        if (func_ovl0C_02_800494A0(0x418) == 0) {
            func_ovl0C_02_80043E0C(D_ovl0C_02_80049B20);
        }
    }
    if (func_ovl0C_02_80048890(0x29, 9, 0x29, 9) != 0) {
        if (func_ovl0C_02_800494A0(0x419) == 0) {
            func_ovl0C_02_80043E0C(D_ovl0C_02_80049B38);
        }
    }
    if ((func_ovl0C_02_80048890(0xB, 2, 0xB, 2) != 0) && (func_ovl0C_02_800494A0(0x41A) == 0)) {
        func_ovl0C_02_80043C54();
    }
}

void func_ovl0C_02_80043E0C(UnkStruct_ovl0C_02_80049B20 *arg0) {
    f32 sp38;
    f32 sp34;
    f32 sp30;
    UnkStructA_40 *temp_v0;
    f32 temp_fs0;
    s16 var_s0;
    s16 var_s0_2;
    s16 var_s0_3;

    func_ovl0C_02_800488B8(1);
    func_ovl0C_02_80048978();
    sp30 = arg0->unk4;
    sp34 = arg0->unk8;
    sp38 = arg0->unkC;
    func_ovl0C_02_800496B8(&sp30);
    func_ovl0C_02_80049788();
    func_ovl0C_02_80048838(1);
    func_ovl0C_02_80049290(0xB0, 0xB0);
    func_ovl0C_02_80048830(0);
    func_ovl0C_02_80049028();
    func_ovl0C_02_800488E0(1);
    func_ovl0C_02_800497A0(0x50);
    var_s0 = 0;
    do {
        arg0->unk0->unk40->unk2C = (func_ovl0C_02_800493C0((f32) var_s0) * 10.0f) + 1.0f;
        func_ovl0C_02_80049260();
        var_s0 += 2;
    } while (var_s0 < 0x5A);
    var_s0_2 = 0;
    do {
        arg0->unk0->unk40->unk30 = func_ovl0C_02_800493C8((f32) var_s0_2);
        temp_v0 = arg0->unk0->unk40;
        temp_v0->unk28 = temp_v0->unk30;
        func_ovl0C_02_80049260();
        var_s0_2 += 2;
    } while (var_s0_2 < 0x5A);
    temp_fs0 = arg0->unk0->unk40->unk14;
    var_s0_3 = 0;
    do {
        arg0->unk0->unk40->unk14 = temp_fs0 + (func_ovl0C_02_800493C0((f32) var_s0_3) * 1000.0f);
        func_ovl0C_02_80049260();
        var_s0_3 += 2;
    } while (var_s0_3 < 0x5A);
    func_ovl0C_02_800487C0(0x29, arg0->unk10, 0);
}

void func_ovl0C_02_80043C54(void) {
    f32 var_fs0;
    s16 var_s1;

    func_ovl0C_02_80048978();
    func_ovl0C_02_800496A8();
    func_ovl0C_02_80049788();
    func_ovl0C_02_80048838(1);
    func_ovl0C_02_80049290(0xB0, 0xB0);
    func_ovl0C_02_80048830(0);
    func_ovl0C_02_800488B8(1);
    func_ovl0C_02_800488E0(1);
    func_ovl0C_02_80049490(0x41A);
    func_ovl0C_02_80049028();
    func_ovl0C_02_80048F70(0x7F);
    func_ovl0C_02_80048F08(1550.0f, 0.0f, 550.0f);
    func_ovl0C_02_80048F28(-90.0f, 45.0f, 2000.0f);
    func_ovl0C_02_800497A0(0x29);
    func_ovl0C_02_800497A0(0x54);
    var_fs0 = 0.0f;
    var_s1 = 0;
    do {
        func_ovl0C_02_80048E18(D_ovl0C_02_80049EEC.unk4);
        D_ovl0C_02_80049EEC.unk4 = func_ovl0C_02_80048E10(D_ovl0C_02_80049EEC.unk0->unk40, 0, (s32) (s16) (0x40 - (s32) var_fs0), 0x400, (s32) D_ovl0C_02_80049EEC.unk10, (s32) D_ovl0C_02_80049EEC.unk12);
        func_ovl0C_02_80049260();
        var_s1 += 1;
        var_fs0 += 0.45f;
    } while (var_s1 < 0x78);
    func_ovl0C_02_80049238(0x1E);
    func_ovl0C_02_80049030();
    func_ovl0C_02_80048FF8(D_ovl0C_02_8004A0D0);
    func_ovl0C_02_80048F68(0x1F);
    func_ovl0C_02_80048838(0);
    func_ovl0C_02_80048830(1);
    func_ovl0C_02_800488B8(0);
}

void func_ovl0C_02_80043B64(void) {
    D_ovl0C_02_8004A0EC = func_ovl0C_02_800488A8();
    func_ovl0C_02_80048888(&D_ovl0C_02_8004A0E0);
    func_ovl0C_02_800488B0(D_ovl0C_02_8004A0EC, D_ovl0C_02_8004A0D0);
    if ((func_ovl0C_02_800494A0(0x404) == 0) && (D_ovl0C_02_8004A110.unk0 == 3)) {
        func_ovl0C_02_80043A98(D_ovl0C_02_80049A38);
    }
    if (func_ovl0C_02_800494A0(0x42B) == 0) {
        if (func_ovl0C_02_800494A0(0x40D) == 0) {
            func_ovl0C_02_80043840(&D_ovl0C_02_80049ECC->unk0, D_ovl0C_02_80049C24, D_ovl0C_02_80049B84, 0x40D);
        }
        if (func_ovl0C_02_800494A0(0x40E) == 0) {
            func_ovl0C_02_80043840(&D_ovl0C_02_80049EDC->unk0, D_ovl0C_02_80049DB4, D_ovl0C_02_80049D3C, 0x40E);
        }
    }
    func_ovl0C_02_80043338();
    func_ovl0C_02_80049490(0x404);
}

void func_ovl0C_02_80043B1C(void) {
    func_ovl0C_02_80043010();
    D_ovl0C_02_8004A0EC = func_ovl0C_02_800488A8();
    func_ovl0C_02_80048888(&D_ovl0C_02_8004A0E0);
    func_ovl0C_02_800488B0(D_ovl0C_02_8004A0EC, D_ovl0C_02_8004A0D0);
}

void func_ovl0C_02_80043A98(UnkStruct_ovl0C_02_80049A38 *arg0) {
    func_ovl0C_02_800488B8(1);
    func_ovl0C_02_80049238(90);
    func_ovl0C_02_800497A0(0x4B);
    func_ovl0C_02_800490C8(arg0->unk4, 0x04000000);
    func_ovl0C_02_80049238(60);
    func_ovl0C_02_800497A0(0x46);
    func_ovl0C_02_80049238(10);
    func_ovl0C_02_80043A0C(arg0);
    func_ovl0C_02_80049498(0x429);
    func_ovl0C_02_800488B8(0);
}

void func_ovl0C_02_80043A0C(UnkStruct_ovl0C_02_80049A38 *arg0) {
    func_ovl0C_02_80048710(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk34, arg0->unk38, 0x1F);
    func_ovl0C_02_80048700(arg0->unk50, arg0->unk54, arg0->unk58, arg0->unk5C);
    func_ovl0C_02_80048700(arg0->unk64, arg0->unk68, arg0->unk6C, arg0->unk70);
}

s32 func_ovl0C_02_80043840(UnkStructA **arg0, UnkStruct_ovl0C_02_80049C24 *arg1, UnkStruct_ovl0C_02_80049B84 *arg2, s32 arg3) {
    UnkStruct_ovl0C_02_80049B84 *sp2C;
    UnkStructA_40 *temp_v0_2;
    UnkStruct_ovl0C_02_80049B84 *var_s0_2;
    s16 temp_t1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;

    sp2C = arg2;
    D_ovl0C_02_8004A124->unk30 = 4;
    D_ovl0C_02_8004A124->unk34 = 90.0f;
    var_s0_2 = arg2;
    D_ovl0C_02_8004A124->unk38 = 400.0f;
    var_s2 = 0;
    if (arg2->unk2 != 0) {
        do {
            if (func_ovl0C_02_800494A0(var_s0_2->unk24) == 0) {
                D_ovl0C_02_8004A124->unk40->unk10 = var_s0_2->unk8;
                D_ovl0C_02_8004A124->unk40->unk14 = var_s0_2->unkC;
                D_ovl0C_02_8004A124->unk40->unk18 = var_s0_2->unk10;
                temp_v0 = func_ovl0C_02_80049078(D_ovl0C_02_8004A124, 0xC0);
                if (temp_v0 != 0) {
                    if (temp_v0 & 0x6000) {
                        func_ovl0C_02_800497C0(0x49, var_s0_2->unk8, var_s0_2->unkC, var_s0_2->unk10);
                        func_ovl0C_02_80048DD8(var_s0_2->unk4->unk40, 0x2AF, 0, 2);
                        func_ovl0C_02_80048DD8(var_s0_2->unk4->unk40, 0x2AF, 1, 3);
                        func_ovl0C_02_80049490(var_s0_2->unk24);
                    } else {
                        temp_v0_2 = D_ovl0C_02_8004A124->unk40;
                        var_s2 = 1;
                        func_ovl0C_02_800497C0(0x26, temp_v0_2->unk10, temp_v0_2->unk14, temp_v0_2->unk18);
                    }
                } else {
                    var_s2 = 1;
                }
            }
            var_s0_2 += 1;
        } while (var_s0_2->unk2 != 0);
    }
    var_s0 = 0;
    if (var_s2 == 0) {
        if (func_ovl0C_02_800494A0(arg3) == 0) {
            var_s0 = 1;
            func_ovl0C_02_80049490(arg3);
            func_ovl0C_02_80043650(arg0, arg1, sp2C, arg3);
        }
    }
    return var_s0;
}

void func_ovl0C_02_80043650(UnkStructA **arg0, UnkStruct_ovl0C_02_80049C24 *arg1, UnkStruct_ovl0C_02_80049B84 *arg2, s32 arg3) {
    s32 sp3C;
    UnkStruct_ovl0C_02_80049C24 *var_s0;
    s16 temp_t0;
    s16 temp_t3;
    s32 temp_s0;

    func_ovl0C_02_80048978();
    func_ovl0C_02_800488B8(1);
    temp_s0 = func_ovl0C_02_80049218(func_ovl0C_02_8004661C, arg1, 0, 0, 0x110);
    func_ovl0C_02_800490E0(*arg0);
    func_ovl0C_02_80043544(arg1, 0x40C);
    sp3C = func_ovl0C_02_80049218(func_ovl0C_02_80047D78, arg2, 0, 0, 0x110);
    func_ovl0C_02_80048838(1);
    func_ovl0C_02_80049278(temp_s0 & 0xFFFF);
    func_ovl0C_02_80049278(sp3C);
    func_ovl0C_02_80049290(0xB0, 0xB0);
    var_s0 = arg1;
    if (arg1->unk2 != 0) {
        do {
            func_ovl0C_02_80049668(0x10, var_s0->unk8 - 300.0f, var_s0->unkC + 200.0f, var_s0->unk10, 0);
            func_ovl0C_02_80049238(0x1E);
            var_s0 += 1;
        } while (var_s0->unk2 != 0);
        var_s0 = arg1;
    }
    func_ovl0C_02_800497C0(0x42, arg1->unk8, arg1->unkC, arg1->unk10);
    if (arg1->unk2 != 0) {
        do {
            func_ovl0C_02_80049218(func_ovl0C_02_80047B20, var_s0, 0, 0, 0x110);
            func_ovl0C_02_80049238(0xF);
            var_s0 += 1;
        } while (var_s0->unk2 != 0);
    }
    func_ovl0C_02_80049238(0x3C);
    func_ovl0C_02_80049220(sp3C);
    func_ovl0C_02_80049238(0x3C);
    func_ovl0C_02_80048838(0);
    if (*func_ovl0C_02_80048818() & 2) {
        func_ovl0C_02_800488B8(1);
    }
}

void func_ovl0C_02_80043544(UnkStruct_ovl0C_02_80049C24 *arg0, s32 arg1) {
    UnkStructA *temp_s3;
    UnkStruct_ovl0C_02_80049C24 *var_s0;
    s16 temp_s1;
    s16 temp_s1_2;
    s16 temp_s2;
    s16 temp_s2_2;
    s16 temp_t1;

    var_s0 = arg0;
    if (arg0->unk2 != 0) {
        do {
            temp_s3 = func_ovl0C_02_80049110(0x2B0, 0xD0, var_s0->unk8, var_s0->unk14, var_s0->unk10);
            if (arg1 == 0) {

            }
            func_ovl0C_02_800490C8(temp_s3, 0x01000000);
            temp_s1 = var_s0->unk18;
            temp_s2 = var_s0->unk1C;
            var_s0->unk4 = temp_s3;
            var_s0->unkC = var_s0->unk14;
            func_ovl0C_02_80048708((s32) temp_s1, (s32) var_s0->unk1A, (s32) temp_s2, temp_s1 + 3, temp_s2 + 2, 0x11);
            temp_s1_2 = var_s0->unk18;
            temp_s2_2 = var_s0->unk1C;
            func_ovl0C_02_80048708((s32) temp_s1_2, (s32) var_s0->unk1E, (s32) temp_s2_2, temp_s1_2 + 3, temp_s2_2 + 2, 0x1F);
            var_s0 += 1;
        } while (var_s0->unk2 != 0);
    }
}

void func_ovl0C_02_80043338(void) {
    UnkStructA_40 *temp_v0_2;
    UnkStruct_ovl0C_02_80049F24 *var_s0;
    s16 var_s4;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_v0;

    D_ovl0C_02_8004A124->unk30 = 4;
    D_ovl0C_02_8004A124->unk34 = 95.0f;
    var_s0 = D_ovl0C_02_80049F24;
    var_s4 = 0;
    D_ovl0C_02_8004A124->unk38 = 500.0f;
    do {
        if (func_ovl0C_02_800494A0(var_s0->unk28) == 0) {
            D_ovl0C_02_8004A124->unk40->unk10 = var_s0->unk8;
            D_ovl0C_02_8004A124->unk40->unk14 = var_s0->unkC;
            D_ovl0C_02_8004A124->unk40->unk18 = var_s0->unk10;
            temp_v0 = func_ovl0C_02_80049078(D_ovl0C_02_8004A124, 0xC0);
            if (temp_v0 != 0) {
                if (temp_v0 & 0x4000) {
                    func_ovl0C_02_800496E8((s32) var_s0->unk2E, var_s0->unk8, var_s0->unkC, var_s0->unk10);
                    func_ovl0C_02_80049668(0xF, var_s0->unk8, var_s0->unkC + 100.0f, var_s0->unk10, 0);
                    func_ovl0C_02_800490D0(var_s0->unk0, 0x01000000);
                    func_ovl0C_02_800490E0(var_s0->unk0);
                    temp_s1 = var_s0->unk14;
                    temp_s2 = var_s0->unk1C;
                    func_ovl0C_02_80048710(temp_s1, var_s0->unk20, temp_s2, temp_s1 + 1, var_s0->unk18, temp_s2 + 1, 0x10);
                    temp_s1_2 = var_s0->unk14;
                    temp_s2_2 = var_s0->unk1C;
                    func_ovl0C_02_80048708(temp_s1_2, var_s0->unk18, temp_s2_2, temp_s1_2 + 1, temp_s2_2 + 1, 0x11);
                    func_ovl0C_02_80049490(var_s0->unk28);
                } else {
                    temp_v0_2 = D_ovl0C_02_8004A124->unk40;
                    func_ovl0C_02_800497C0(0x26, temp_v0_2->unk10, temp_v0_2->unk14, temp_v0_2->unk18);
                }
            }
        }
        var_s4 += 1;
        var_s0 += 0x30;
    } while (var_s4 < 4);
}

void func_ovl0C_02_80043250(void) {
    if (func_ovl0C_02_800431D4() >= 5) {
        if (func_ovl0C_02_800494A0(0x415) == 0) {
            if (func_ovl0C_02_80048898(0x13, 2, 0x1E, 0x15, 0x1F) != 0) {
                if (func_ovl0C_02_800430D0(func_ovl0C_02_80048908(func_ovl0C_02_800488A8()), D_ovl0C_02_80049FE4->unk0) != 0) {
                    func_ovl0C_02_80048E30(0x35C, 7);
                }
            }
        } else if (func_ovl0C_02_80048898(0x11, 4, 0xB, 0x12, 0xD) != 0) {
            if (func_ovl0C_02_800430D0(func_ovl0C_02_80048908(func_ovl0C_02_800488A8()), D_ovl0C_02_80049FE4->unk0) != 0) {
                func_ovl0C_02_80048E30(0x35D, 6);
            }
        }
    }
}

s32 func_ovl0C_02_800431D4(void) {
    s32 var_v0;

    if (func_ovl0C_02_800494A0(0x412) == 0) {
        return 2;
    }
    if (func_ovl0C_02_800494A0(0x40F) == 0) {
        return 3;
    }
    if (func_ovl0C_02_800494A0(0x40C) == 0) {
        return 4;
    }
    var_v0 = 6;
    if (func_ovl0C_02_800494A0(0x415) == 0) {
        var_v0 = 5;
    }
    return var_v0;
}

s32 func_ovl0C_02_800430D0(UnkStructA *arg0, UnkStructA *arg1) {
    f32 sp18;
    f32 temp_fv0;
    s32 var_v0;

    sp18 = func_ovl0C_02_800493C0(arg0->unk40->unk20) * 50.0f;
    temp_fv0 = func_ovl0C_02_800493C8(arg0->unk40->unk20);
    D_ovl0C_02_8004A124->unk30 = 1;
    D_ovl0C_02_8004A124->unk34 = 30.0f;
    D_ovl0C_02_8004A124->unk38 = 50.0f;
    D_ovl0C_02_8004A124->unk40->unk10 = arg0->unk40->unk10 + sp18;
    D_ovl0C_02_8004A124->unk40->unk14 = arg0->unk40->unk14;
    D_ovl0C_02_8004A124->unk40->unk18 = arg0->unk40->unk18 + (temp_fv0 * 50.0f);
    var_v0 = 1;
    if (func_ovl0C_02_80049158(D_ovl0C_02_8004A124, 0x10) != arg1) {
        var_v0 = 0;
    }
    return var_v0;
}

void func_ovl0C_02_800430B0(void) {
    func_ovl0C_02_80043010();
    func_ovl0C_02_80048910(1);
}

void func_ovl0C_02_80043090(void) {
    func_ovl0C_02_80043010();
    func_ovl0C_02_80048910(1);
}

void func_ovl0C_02_80043060(void) {
    if (D_ovl0C_02_8004A110.unk0 == 0xD) {
        func_ovl0C_02_80043018();
    }
}

void func_ovl0C_02_80043018(void) {
    UnkStruct_ovl0C_02_80049968_C *temp_v1;

    temp_v1 = func_ovl0C_02_80049968(3)->unkC;
    temp_v1->unkC |= 1;
    func_ovl0C_02_80049568(0, 0, 0);
    func_ovl0C_02_80049988();
}

void func_ovl0C_02_80043010(void) {
}
