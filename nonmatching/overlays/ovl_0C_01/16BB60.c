/*
 * NON_MATCHING: ovl_0C_01's game object, complete: every function and its
 * data (.data 0x520, .rodata 0x3B0 and .bss 0x70; the .data and .rodata
 * words are the original's, though IDO puts the scripts' strings in .rodata).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 1757, jp 1757
 *
 * A first complete draft: the functions with a ratio-1.00 sibling are that
 * sibling's C translated (scratch/0C_01/sib.py: ovl_0C_06 first, then
 * ovl_0C_07, 0C_09, 0C_04, 0C_02), the rest m2c's output with its types
 * fixed, and the tasks 80047338, 80047454 and 80047A60 and the stage's
 * place helpers 800450B0, 80045920 and 800459FC by hand.  68 of the 103
 * functions match.  Then 80043E74, 80047CA8 and 80047E9C became ovl_0C_02's
 * 80043338, 800475BC and 800477B0 translated (they match there); 80043E74's
 * loop is `i < 8` where its twin has `i < 4`.  71 of the 103 match.
 *
 * What still differs in us (words):
 * - From ovl_0C_02's draft, its open problems too: 800452F4 (98), whose
 *   twin 80043E0C is 5 words off there, so not ported; 800464F8 (76), whose
 *   twin 80045538 doesn't match there yet.
 * - From ovl_0C_06's, its known unsolved `arg ? 0x01000000 : 0x01000000`:
 *   80045E68 (84), 80045FBC (57), 8004476C (55).
 * - m2c's register use and loop shapes, not yet worked on: 80044D3C (160),
 *   800468EC (152, the object set-up), 80043C20 (92), 80044080 (83),
 *   800444DC (75), 800443A4 (72), 800439C0 (70), 80047074 (69, the
 *   handler; not ovl_0C_02's 8004639C, which is 0.78 by ratio), 800441D4 (62), 800435C4 (52), 80046224 (51), 80043248 (50),
 *   800438E8 (49), 800436A0 (26), 80048068 (25), 8004333C (24), 80043058
 *   (17), 800477EC (15), 800474FC (12), 80047054 (10), 800463E0 and
 *   800459FC (7 each), 80045194 (5), 8004514C and 800450B0 (2 each).
 * - The hand-written tasks 80047A60 (136) and 80047338 (60): loop shapes.
 */
#include "common.h"

/* the handler's state (ovl_0C_07's D_ovl0C_07_80047990) */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_ovl0C_01_8004A9C8;

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
} UnkStruct_ovl0C_01_8004A104;

/* an object at a position, with three arguments */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0C_01_8004A5B4;

typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStruct_ovl0C_01_8004A584;

/* an object and its position */
typedef struct {
    /* 0x00 */ UnkStructA *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_ovl0C_01_8004A3BC;

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
} UnkStruct_ovl0C_01_8004A22C;


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
    /* 0x20 */ UnkStruct_ovl0C_01_8004A22C *unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
} UnkStruct_ovl0C_01_8004A2A4;

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
} UnkStruct_ovl0C_01_8004A54C;

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
} UnkStruct_ovl0C_01_8004A3CC;

/* what the ZeroJump stub 0x3106 returns */
typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ s32 unkC;
} UnkStruct_ovl0C_01_ZJ3106_C;

typedef struct {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ UnkStruct_ovl0C_01_ZJ3106_C *unkC;
} UnkStruct_ovl0C_01_ZJ3106;

/* objects at a position, each a task's (func_ovl0C_01_80047A60) */
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
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s32 unk28;
} UnkStruct_ovl0C_01_8004A17C;

/* a list of these ends at the one whose unk2 is 0 */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ UnkStructA *unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
} UnkStruct_ovl0C_01_8004A1A8;

void func_ovl0C_01_80048A70(const char *);
void func_ovl0C_01_80048DB8(s32);
void func_ovl0C_01_80048DD0(s32);
void func_ovl0C_01_80048DF0(s32, s32, s32, s32);
void func_ovl0C_01_80048DF8(s32, s32, s32, s32, s32, s32);
void func_ovl0C_01_80048E00(s32, s32, s32, s32, s32, s32, s32);
void func_ovl0C_01_80048E40(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0C_01_80048E98(void (*)(UnkStructA *), s32);
void func_ovl0C_01_80048EA0(void (*)(UnkStructA *));
void func_ovl0C_01_80048EB0(s32, s32, s32);
void func_ovl0C_01_80048EF0(void (*)(UnkStructA *));
s32 *func_ovl0C_01_80048F08(void);
void func_ovl0C_01_80048F20(s32);
void func_ovl0C_01_80048F28(s32);
void func_ovl0C_01_80048F40(s32, s32);
void func_ovl0C_01_80048F58(s32);
void func_ovl0C_01_80048F68(void);
void func_ovl0C_01_80048F70(s32, s32, s32);
void func_ovl0C_01_80048F78(void *);
s32 func_ovl0C_01_80048F80(s32, s32, s32, s32);
s32 func_ovl0C_01_80048F88(s32, s32, s32, s32, s32);
s32 func_ovl0C_01_80048F98(void);
void func_ovl0C_01_80048FA0(s32, void *);
void func_ovl0C_01_80048FA8(s32);
void func_ovl0C_01_80048FB0(s32);
void func_ovl0C_01_80048FB8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0C_01_80048FC0(const char *);
void func_ovl0C_01_80048FC8(void);
void func_ovl0C_01_80048FD0(s32);
void func_ovl0C_01_80048FE0(s32);
UnkStructA *func_ovl0C_01_80048FF8(s32);
void func_ovl0C_01_80049000(s32);
UnkStructA *func_ovl0C_01_80049038(s32);
void func_ovl0C_01_80049050(s32);
void func_ovl0C_01_80049068(void);
void func_ovl0C_01_800494C0(UnkStructA_40 *, s32);
void func_ovl0C_01_800494C8(UnkStructA_40 *, s32, s32, s32);
void func_ovl0C_01_800494E0(UnkStructA_40 *, s32, s32);
f32 func_ovl0C_01_800494F8(UnkStructA_40 *, s32);
s32 func_ovl0C_01_80049500(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl0C_01_80049508(s32);
void func_ovl0C_01_80049520(s32, s32);
void func_ovl0C_01_800495F8(f32, f32, f32);
void func_ovl0C_01_80049618(f32, f32, f32);
void func_ovl0C_01_80049620(f32 *, f32 *, f32 *);
void func_ovl0C_01_80049658(s32);
void func_ovl0C_01_80049660(s32);
void func_ovl0C_01_80049670(s32);
void func_ovl0C_01_800496B0(f32, f32);
void func_ovl0C_01_800496E8(void *);
void func_ovl0C_01_80049718(void);
void func_ovl0C_01_80049720(void);
s32 func_ovl0C_01_80049768(UnkStructA *, s32);
void func_ovl0C_01_800497B8(UnkStructA *, s32);
void func_ovl0C_01_800497C0(UnkStructA *, s32);
void func_ovl0C_01_800497D0(UnkStructA *);
UnkStructA *func_ovl0C_01_800497E0(s32, s32, s32, s32);
UnkStructA *func_ovl0C_01_800497F0(UnkStructA *);
UnkStructA *func_ovl0C_01_80049800(s32, s32, f32, f32, f32);
void func_ovl0C_01_80049838(UnkStructA *);
UnkStructA *func_ovl0C_01_80049848(UnkStructA *, s32);
s32 func_ovl0C_01_800498D8(UnkStructA *, s32, UnkStructA *);
void func_ovl0C_01_80049900(void *);
s32 func_ovl0C_01_80049908(void (*)(void), void *, s32, s32, s32);
void func_ovl0C_01_80049910(s32);
void func_ovl0C_01_80049918(void);
void func_ovl0C_01_80049928(s32);
void *func_ovl0C_01_80049930(void);
void func_ovl0C_01_80049950(void);
void func_ovl0C_01_80049968(u16);
void func_ovl0C_01_80049980(s32, s32);
f32 func_ovl0C_01_80049AB0(f32);
f32 func_ovl0C_01_80049AB8(f32);
s32 func_ovl0C_01_80049AC8(s32);
s32 func_ovl0C_01_80049B70(s32);
void func_ovl0C_01_80049B80(s32);
void func_ovl0C_01_80049B88(s32);
s32 func_ovl0C_01_80049B90(s32);
s32 *func_ovl0C_01_80049BA0(void);
void func_ovl0C_01_80049C58(s32, s32, s32);
void func_ovl0C_01_80049C70(u32 (*)[3]);
void func_ovl0C_01_80049D58(s32, f32, f32, f32, s32);
void func_ovl0C_01_80049D88(s16, s32);
void func_ovl0C_01_80049D90(s16, s32);
void func_ovl0C_01_80049DA8(f32 *);
void func_ovl0C_01_80049DD8(s32, f32, f32, f32);
void func_ovl0C_01_80049E08(UnkStructA *, s32, f32);
void func_ovl0C_01_80049E18(s32, s32, s32);
void func_ovl0C_01_80049E38(s32);
void func_ovl0C_01_80049E78(void);
void func_ovl0C_01_80049E88(f32 *); /* 0x2A0E */
void func_ovl0C_01_80049E90(s32);
void func_ovl0C_01_80049EB0(s32, f32, f32, f32);
void func_ovl0C_01_8004A008(void);
void func_ovl0C_01_8004A010(void);

void func_ovl0C_01_80043010(void);
void func_ovl0C_01_80043018(void);
void func_ovl0C_01_80043038(void);
void func_ovl0C_01_80043058(void);
void func_ovl0C_01_800430B0(void);
void func_ovl0C_01_800430D0(void);
void func_ovl0C_01_800430F0(void);
s32 func_ovl0C_01_80043138(UnkStructA *arg0, UnkStructA *arg1);
void func_ovl0C_01_80043248(f32 *arg0, f32 arg1, s32 arg2);
void func_ovl0C_01_8004333C(void);
void func_ovl0C_01_800435C4(f32 *arg0, f32 arg1, s32 arg2);
void func_ovl0C_01_800436A0(void);
void func_ovl0C_01_80043894(void);
void func_ovl0C_01_800438E8(void);
void func_ovl0C_01_800439C0(void);
void func_ovl0C_01_80043BC0(void);
void func_ovl0C_01_80043C20(void);
void func_ovl0C_01_80043E74(void);
void func_ovl0C_01_80044080(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, s32 arg4);
void func_ovl0C_01_800441D4(void);
void func_ovl0C_01_800443A4(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, s32 arg4);
void func_ovl0C_01_800444DC(void);
void func_ovl0C_01_800446F8(s32 arg0);
void func_ovl0C_01_8004476C(UnkStruct_ovl0C_01_8004A2A4 *arg0, s32 arg1);
void func_ovl0C_01_80044878(UnkStruct_ovl0C_01_8004A3BC *arg0, UnkStruct_ovl0C_01_8004A2A4 *arg1, UnkStruct_ovl0C_01_8004A22C *arg2, s32 arg3);
s32 func_ovl0C_01_80044A68(UnkStruct_ovl0C_01_8004A3BC *arg0, UnkStruct_ovl0C_01_8004A2A4 *arg1, UnkStruct_ovl0C_01_8004A22C *list, s32 arg3);
void func_ovl0C_01_80044C34(UnkStruct_ovl0C_01_8004A104 *arg0);
void func_ovl0C_01_80044CC0(UnkStruct_ovl0C_01_8004A104 *arg0);
void func_ovl0C_01_80044D3C(void);
s32 func_ovl0C_01_800450B0(void);
void func_ovl0C_01_8004514C(void);
void func_ovl0C_01_80045194(void);
void func_ovl0C_01_800452F4(UnkStruct_ovl0C_01_8004A584 *arg0);
void func_ovl0C_01_800454C0(void);
void func_ovl0C_01_80045540(UnkStruct_ovl0C_01_8004A104 *arg0);
void func_ovl0C_01_800455AC(void);
void func_ovl0C_01_80045648(void);
void func_ovl0C_01_800456B4(void);
void func_ovl0C_01_8004572C(void);
void func_ovl0C_01_80045774(void);
void func_ovl0C_01_80045800(void);
void func_ovl0C_01_80045894(UnkStructA *arg0);
void func_ovl0C_01_80045920(f32 *pos);
void func_ovl0C_01_800459FC(void);
void func_ovl0C_01_80045A78(UnkStruct_ovl0C_01_8004A104 *arg0);
void func_ovl0C_01_80045B3C(UnkStruct_ovl0C_01_8004A104 *arg0);
void func_ovl0C_01_80045B78(void);
void func_ovl0C_01_80045BD0(void);
void func_ovl0C_01_80045C4C(void);
void func_ovl0C_01_80045CD4(void);
void func_ovl0C_01_80045D90(void);
void func_ovl0C_01_80045E68(UnkStruct_ovl0C_01_8004A22C *arg0, s32 arg1);
void func_ovl0C_01_80045FBC(UnkStruct_ovl0C_01_8004A3BC *arg0, UnkStruct_ovl0C_01_8004A2A4 *arg1, s32 arg2);
void func_ovl0C_01_800460AC(f32 arg0);
void func_ovl0C_01_800460F4(void);
void func_ovl0C_01_80046224(void);
void func_ovl0C_01_800463B0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4);
void func_ovl0C_01_800463D8(void);
void func_ovl0C_01_800463E0(void);
void func_ovl0C_01_800464F8(void);
void func_ovl0C_01_80046628(UnkStruct_ovl0C_01_8004A104 *arg0);
void func_ovl0C_01_80046684(s32 arg0);
void func_ovl0C_01_80046740(void);
void func_ovl0C_01_800468E4(void);
void func_ovl0C_01_800468EC(void);
void func_ovl0C_01_80046B98(void);
void func_ovl0C_01_80046BF4(void);
void func_ovl0C_01_80046C68(void);
void func_ovl0C_01_80046CC4(void);
void func_ovl0C_01_80046D20(void);
void func_ovl0C_01_80046D84(void);
void func_ovl0C_01_80046DE4(void);
void func_ovl0C_01_80046E48(void);
void func_ovl0C_01_80046EBC(void);
void func_ovl0C_01_80046F28(void);
void func_ovl0C_01_80046F84(void);
void func_ovl0C_01_80046FDC(void);
void func_ovl0C_01_8004701C(void);
void func_ovl0C_01_80047054(void);
void func_ovl0C_01_80047074(s32 arg0);
void func_ovl0C_01_80047268(void);
void func_ovl0C_01_80047338(void);
void func_ovl0C_01_80047454(void);
void func_ovl0C_01_800474FC(void);
void func_ovl0C_01_80047564(void);
void func_ovl0C_01_800476AC(void);
void func_ovl0C_01_8004772C(void);
void func_ovl0C_01_800477B0(void);
void func_ovl0C_01_800477EC(void);
void func_ovl0C_01_80047A60(void);
void func_ovl0C_01_80047CA8(UnkStructA *arg0);
void func_ovl0C_01_80047E9C(UnkStructA *arg0);
void func_ovl0C_01_80048068(void);
void func_ovl0C_01_80048200(void);
void func_ovl0C_01_80048458(void);
void func_ovl0C_01_80048570(void);
void func_ovl0C_01_80048694(UnkStructA *arg0);
void func_ovl0C_01_80048754(UnkStructA *arg0);
void func_ovl0C_01_80048798(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_ovl0C_01_80048870(void);
void func_ovl0C_01_80048980(s32 arg0, UnkStructA *arg1);
void func_ovl0C_01_800489B4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl0C_01_80048A10(void);
static void func_ovl0C_01_80048A28(void);

/* the handler's state, set in one line (ovl_0C_07's func_ovl0C_07_80043CF0, here
 * never a function of its own) */
#define SET_STATE(a, b, c, d, e) \
    D_ovl0C_01_8004A9C8.unk0 = (a); D_ovl0C_01_8004A9C8.unk4 = (b); D_ovl0C_01_8004A9C8.unk8 = (c); D_ovl0C_01_8004A9C8.unkC = (d); D_ovl0C_01_8004A9C8.unk10 = (e)

/* The three statements are on one line, a macro: only then does IDO
 * schedule across them (as in ovl_0C_04, ovl_0C_06, ovl_0C_07 and ovl_0C_09). */
#define UNK_MACRO_ovl0C_01_8004514C() \
    D_ovl0C_01_8004A99C = func_ovl0C_01_80048F98(); func_ovl0C_01_80048F78(&D_ovl0C_01_8004A990); func_ovl0C_01_80048FA0(D_ovl0C_01_8004A99C, D_ovl0C_01_8004A980)

/* .bss */
f32 D_ovl0C_01_8004A980[4];
Vec3f D_ovl0C_01_8004A990;
s32 D_ovl0C_01_8004A99C;
u8 D_ovl0C_01_8004A9A0[0x4];
s32 D_ovl0C_01_8004A9A4;
s32 D_ovl0C_01_8004A9A8;
u8 D_ovl0C_01_8004A9AC[0x4];
Vec3f D_ovl0C_01_8004A9B0;
UnkStructA *D_ovl0C_01_8004A9BC;
s32 D_ovl0C_01_8004A9C0;
s32 D_ovl0C_01_8004A9C4;
UnkStruct_ovl0C_01_8004A9C8 D_ovl0C_01_8004A9C8;
UnkStructA *D_ovl0C_01_8004A9DC;
UnkStructA *D_ovl0C_01_8004A9E0[4];

/* .data */
u32 D_ovl0C_01_8004A0B0[][3] = {
    { 0x8F0002, 0x3000E, 4 },
    { 0x900000, 0xE, 4 },
    { 0x930000, 0xE, 0x2004 },
};
u32 D_ovl0C_01_8004A0D4[][3] = {
    { 0, 6, 0xE4 },
    { 1, 4, 0xE2 },
    { 2, 0, 0xDE },
    { 3, 5, 0x34F },
};
UnkStruct_ovl0C_01_8004A104 D_ovl0C_01_8004A104[] = {
    { 0, NULL, 4400.0f, 300.0f, 1550.0f, 0xC0, 4350.0f, 300.0f, 1550.0f, 0x2A, 2, 0xF, 0x2D, 3, 0x10, 0x2E, 2, 0xF, 0x2E, 0x10, 0x2B, 2, 0xE, 0x1D, 0x11, 0x2B, 2, 0x11, 0x1C, 0x11 },
};
UnkStruct_ovl0C_01_8004A17C D_ovl0C_01_8004A17C[] = {
    { NULL, 1650.0f, 700.0f, 2750.0f, 4, 5, 0x19, 0x10, 0x1E, 0.0f, 1 },
};
UnkStruct_ovl0C_01_8004A1A8 D_ovl0C_01_8004A1A8[] = {
    { 0, 1, NULL, 600.0f, 200.0f, 2800.0f, 6, 1, 0x1C, 4, 0x401, 0x40F },
    { 1, 2, NULL, 1100.0f, 200.0f, 2800.0f, 0xB, 1, 0x1C, 4, 0x402, 0x40F },
    { 2, 0, NULL, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0 },
};
UnkStruct_ovl0C_01_8004A22C D_ovl0C_01_8004A22C[] = {
    { 0, 1, NULL, 3550.0f, 100.0f, 1050.0f, 350.0f, 0x23, 3, 0xA, 2, 0, 0, 0x405 },
    { 1, 2, NULL, 3550.0f, 100.0f, 1850.0f, 350.0f, 0x23, 3, 0x12, 2, 0, 0, 0x406 },
    { 2, 0, NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0 },
};
UnkStruct_ovl0C_01_8004A2A4 D_ovl0C_01_8004A2A4[] = {
    { 0, 1, NULL, 3550.0f, 600.0f, 550.0f, 600.0f, 0x22, 5, 3, 4, NULL, 0, 0 },
    { 1, 2, NULL, 3550.0f, 600.0f, 850.0f, 600.0f, 0x22, 5, 6, 4, NULL, 0, 0 },
    { 2, 3, NULL, 3550.0f, 600.0f, 1150.0f, 600.0f, 0x22, 5, 9, 4, &D_ovl0C_01_8004A22C[0], 0, 0 },
    { 3, 4, NULL, 3550.0f, 600.0f, 1450.0f, 600.0f, 0x22, 5, 0xC, 4, NULL, 0, 0 },
    { 4, 5, NULL, 3550.0f, 600.0f, 1750.0f, 600.0f, 0x22, 5, 0xF, 4, NULL, 0, 0 },
    { 5, 6, NULL, 3550.0f, 600.0f, 2050.0f, 600.0f, 0x22, 5, 0x12, 4, &D_ovl0C_01_8004A22C[1], 0, 0 },
    { 6, 0, NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, NULL, 0, 0 },
};
UnkStruct_ovl0C_01_8004A3BC D_ovl0C_01_8004A3BC = { NULL, 3550.0f, 600.0f, 550.0f };
UnkStruct_ovl0C_01_8004A3CC D_ovl0C_01_8004A3CC[] = {
    { NULL, 0x2AD, 1550.0f, 200.0f, 1250.0f, 0xF, 1, 0xC, 5, 4, 0x41D, 0, 8 },
    { NULL, 0x2AD, 1550.0f, 200.0f, 1850.0f, 0xF, 1, 0x12, 5, 4, 0x41E, 0, 8 },
    { NULL, 0x2AD, 2350.0f, 200.0f, 2650.0f, 0x17, 1, 0x1A, 5, 4, 0x41F, 0, 8 },
    { NULL, 0x2AD, 2350.0f, 200.0f, 2850.0f, 0x17, 1, 0x1C, 5, 4, 0x420, 0, 8 },
    { NULL, 0x2AD, 2350.0f, 200.0f, 3050.0f, 0x17, 1, 0x1E, 5, 4, 0x421, 0, 8 },
    { NULL, 0x2AD, 2450.0f, 200.0f, 1250.0f, 0x18, 1, 0xC, 5, 4, 0x422, 0, 8 },
    { NULL, 0x2AD, 2450.0f, 200.0f, 1850.0f, 0x18, 1, 0x12, 5, 4, 0x423, 0, 8 },
    { NULL, 0x2AD, 4450.0f, 700.0f, 50.0f, 0x2C, 5, 0, 5, 5, 0x424, 0, 0xA },
};
UnkStruct_ovl0C_01_8004A54C D_ovl0C_01_8004A54C = { NULL, -1, 0x2B3, 0x40, 0x400, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
UnkStruct_ovl0C_01_8004A584 D_ovl0C_01_8004A584[] = {
    { NULL, 500.0f, 200.0f, 2600.0f, 0x17, 0x416 },
};
UnkStruct_ovl0C_01_8004A584 D_ovl0C_01_8004A59C[] = {
    { NULL, 4400.0f, 300.0f, 2200.0f, 0x18, 0x417 },
};
UnkStruct_ovl0C_01_8004A5B4 D_ovl0C_01_8004A5B4[] = {
    { NULL, 400.0f, 300.0f, 1500.0f, 0, 0, 0 },
};

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl0C_01_80048A68(void) {
}
static void func_ovl0C_01_80048A60(void) {
}
static void func_ovl0C_01_80048A58(void) {
}
static void func_ovl0C_01_80048A50(void) {
}
static void func_ovl0C_01_80048A48(void) {
}
static void func_ovl0C_01_80048A40(void) {
}
static void func_ovl0C_01_80048A38(void) {
}
static void func_ovl0C_01_80048A30(void) {
}
static void func_ovl0C_01_80048A28(void) {
}

void func_ovl0C_01_80048A10(void) {
    D_ovl0C_01_8004A9A4 = -1;
    D_ovl0C_01_8004A9A8 = -1;
}

void func_ovl0C_01_800489B4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0C_01_800495F8(D_ovl0C_01_8004A9B0.x, D_ovl0C_01_8004A9B0.y, D_ovl0C_01_8004A9B0.z);
    func_ovl0C_01_80049618(arg0, arg1, arg2);
    func_ovl0C_01_80049928(180);
}

void func_ovl0C_01_80048980(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0C_01_80049EB0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0C_01_80048870(void) {
    s32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    UnkStructA *src;
    UnkStructA *obj;
    s32 i;
    s32 count;

    src = func_ovl0C_01_80049930();
    func_ovl0C_01_80049EB0(0xB3, src->unk40->unk10, src->unk40->unk14, src->unk40->unk18);
    obj = func_ovl0C_01_800497E0(0x183, 0x11080000, 0xD0, 0);
    obj->unk40->unk10 = src->unk40->unk10;
    obj->unk40->unk14 = src->unk40->unk14;
    obj->unk40->unk18 = src->unk40->unk18;
    count = 20;
    for (i = 0; i < count; i++) {
        func_ovl0C_01_80048798(obj, i, count, 2.0f, 4.0f);
        func_ovl0C_01_80049950();
    }
    func_ovl0C_01_800497D0(obj);
    func_ovl0C_01_80049918();
}

void func_ovl0C_01_80048798(UnkStructA *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    arg0->unk40->unk28 = func_ovl0C_01_80049AB0((f32) arg1 / (f32) arg2 * 90.0f) * arg3;
    arg0->unk40->unk2C = func_ovl0C_01_80049AB0((f32) arg1 / (f32) arg2 * 180.0f) * arg4;
    arg0->unk40->unk36 = (s32) ((1.0f - (f32) arg1 / (f32) arg2) * 63.0f) + 0x80;
}

void func_ovl0C_01_80048754(UnkStructA *arg0) {
    func_ovl0C_01_800497C0(arg0, 0x01000000);
    func_ovl0C_01_80049908(func_ovl0C_01_80048870, arg0, 0, 0, 0x150);
}

void func_ovl0C_01_80048694(UnkStructA *arg0) {
    func_ovl0C_01_80049928(10);
    func_ovl0C_01_80048E40(arg0->unk40, &arg0->unk40->unk1C, &arg0->unk40->unk20);
    arg0->unk40->unk28 *= 2.0f;
    arg0->unk40->unk30 *= 2.0f;
    arg0->unk40->unk2C *= 0.1f;
    arg0->unk40->unk14 += 20.0f;
    arg0->unk6C = 0.0f;
    arg0->unk70 = 0.0f;
    func_ovl0C_01_80049928(60);
}

/* a switch fading out with its block: its tiles open */
void func_ovl0C_01_80048570(void) {
    UnkStruct_ovl0C_01_8004A22C *rec;
    s16 alpha;

    rec = func_ovl0C_01_80049930();
    alpha = 0xFF;
    while (TRUE) {
        alpha -= 0xA;
        func_ovl0C_01_800497B8(rec->unk4, 0x80000);
        if (alpha < 0) {
            alpha = 0;
            func_ovl0C_01_800497C0(rec->unk4, 0x01000000);
            func_ovl0C_01_80048E00(rec->unk18, rec->unk1A, rec->unk1C, rec->unk18 + 1, rec->unk1E + 1, rec->unk1C + 1, 0x10);
            func_ovl0C_01_80048DF8(rec->unk18, rec->unk1E, rec->unk1C, rec->unk18 + 1, rec->unk1C + 1, 0x11);
            rec->unk22 = 0;
            func_ovl0C_01_800497D0(rec->unk4);
            func_ovl0C_01_80049918();
        }
        rec->unk4->unk40->unk36 = alpha;
        func_ovl0C_01_80049950();
    }
}

/* the switches' sparks, each on its own random timer */
void func_ovl0C_01_80048458(void) {
    UnkStruct_ovl0C_01_8004A22C *list;
    UnkStruct_ovl0C_01_8004A22C *p;

    list = func_ovl0C_01_80049930();
    for (p = list; p->unk2 != 0; p++) {
        p->unk20 = func_ovl0C_01_80049AC8(5) + 0x14;
        p->unk22 = 1;
    }
    while (TRUE) {
        for (p = list; p->unk2 != 0; p++) {
            if (p->unk20-- <= 0 && p->unk22 == 1) {
                func_ovl0C_01_80049D58(0xF, p->unk8 - 100.0f, p->unk14, p->unk10, 0);
                func_ovl0C_01_80049E90(0x4A);
                p->unk20 = func_ovl0C_01_80049AC8(5) + 0x14;
            }
        }
        func_ovl0C_01_80049950();
    }
}

void func_ovl0C_01_80048200(void) {
    UnkStructA *temp_s1;
    UnkStructA_40 *temp_v0_2;
    UnkStructA_40 *temp_v0_3;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 var_s0;
    UnkStruct_ovl0C_01_8004A2A4 *temp_v0;

    temp_v0 = func_ovl0C_01_80049930();
    temp_s1 = temp_v0->unk4;
    if (temp_v0->unk20 != NULL) {
        func_ovl0C_01_80049908(func_ovl0C_01_80048570, temp_v0->unk20, 0, 0, 0x110);
    }
    temp_a0 = temp_v0->unk18;
    temp_a2 = temp_v0->unk1C;
    func_ovl0C_01_80048DF8((s32) temp_a0, (s32) temp_v0->unk1A, (s32) temp_a2, temp_a0 + 3, temp_a2 + 2, 0x10);
    temp_a0_2 = temp_v0->unk18;
    temp_a2_2 = temp_v0->unk1C;
    func_ovl0C_01_80048DF8((s32) temp_a0_2, (s32) temp_v0->unk1E, (s32) temp_a2_2, temp_a0_2 + 3, temp_a2_2 + 2, 0x10);
    if (temp_v0->unk24 == 1) {
        func_ovl0C_01_80048DF8(0x2B, 3, 0xB, 0x2D, 0x12, 0x11);
        func_ovl0C_01_80048DF8(0x2C, 3, 0xC, 0x2D, 0x11, 0x10);
        func_ovl0C_01_80048DF8(0x2B, 3, 0xE, 0x2B, 0xF, 0x10);
    }
loop_5:
    temp_v0_2 = temp_s1->unk40;
    temp_v0_2->unk1C -= 5.0f;
    if (!(temp_s1->unk40->unk1C < -50.0f)) {
        func_ovl0C_01_80049950();
        goto loop_5;
    }
    func_ovl0C_01_800497B8(temp_s1, 0x80000);
    var_s0 = 0xFF;
loop_9:
    var_s0 -= 0xA;
    if (var_s0 < 0) {
        var_s0 = 0;
    }
    temp_s1->unk40->unk36 = var_s0;
    func_ovl0C_01_80049838(temp_s1);
    if ((temp_s1->unk6C == 0.0f) && (temp_s1->unk68 == 0.0f)) {
        temp_v0_3 = temp_s1->unk40;
        func_ovl0C_01_80049D58(0x10, temp_v0_3->unk10, temp_v0_3->unk14 + 100.0f, temp_v0_3->unk18, 0);
        func_ovl0C_01_800497C0(temp_s1, 0x01000000);
        func_ovl0C_01_80049918();
    }
    func_ovl0C_01_80049950();
    goto loop_9;
}

void func_ovl0C_01_80048068(void) {
    UnkStruct_ovl0C_01_8004A104 *rec;
    UnkStructA_40 *p;

    rec = func_ovl0C_01_80049930();
    p = rec->unk4->unk40;
    D_ovl0C_01_8004A9E0[rec->unk0]->unkC = 0x40;
    while (TRUE) {
        if (D_ovl0C_01_8004A9E0[rec->unk0]->unk10 & 0x40) {
            func_ovl0C_01_80049B80(0x429);
            func_ovl0C_01_80049E90(0x53);
            p->unk48->unk4->unk4 = func_ovl0C_01_800494F8(p, 0) - 0.01f;
            while (p->unk48->unk4->unk4 > 1.0f) {
                func_ovl0C_01_80049950();
                p->unk48->unk4->unk4 -= 1.0f;
            }
            p->unk48->unk4->unk4 = 0.0f;
            func_ovl0C_01_80045A78(rec);
            func_ovl0C_01_80049918();
        }
        func_ovl0C_01_80049950();
    }
}

void func_ovl0C_01_80047E9C(UnkStructA *arg0) {
    s32 pad;
    s32 moved;
    s32 pad2; /* unused: pad and pad2 place the original's locals */
    f32 x;
    f32 y;
    f32 z;
    UnkStructA *other;
    s32 saved;
    s32 i;

    if (func_ovl0C_01_80049B90(0x41A) == 0 && arg0->unk6C == 0.0f && arg0->unk68 == 0.0f) {
        x = arg0->unk40->unk10;
        y = arg0->unk40->unk14;
        z = arg0->unk40->unk18;
        func_ovl0C_01_80049E08(arg0, 0xC0, 12.0f);
        moved = 0;
        if (arg0->unk8 & 3) {
            if (arg0->unk8 & 2) {
                for (i = 0; i < 5; i++) {
                    if (func_ovl0C_01_80049038(i) == arg0) {
                        break;
                    }
                }
                other = i < 5 ? func_ovl0C_01_80048FF8(i) : NULL;
            } else {
                for (i = 0; i < 5; i++) {
                    if (func_ovl0C_01_80048FF8(i) == arg0) {
                        break;
                    }
                }
                other = i < 5 ? func_ovl0C_01_80049038(i) : NULL;
            }
        } else {
            other = NULL;
        }
        saved = arg0->unkC;
        arg0->unkC = 0;
        if (other != NULL) {
            if (func_ovl0C_01_800498D8(arg0, 0x10, other) != 0) {
                moved = 1;
            }
        } else if (func_ovl0C_01_80049768(arg0, 0x10) != 0) {
            moved = 1;
        }
        arg0->unkC = saved;
        if (moved != 0) {
            arg0->unk40->unk10 = x;
            arg0->unk40->unk14 = y;
            arg0->unk40->unk18 = z;
        }
    }
}

void func_ovl0C_01_80047CA8(UnkStructA *arg0) {
    s32 pad;
    s32 moved;
    s32 pad2; /* unused: pad and pad2 place the original's locals */
    f32 x;
    f32 y;
    f32 z;
    UnkStructA *other;
    s32 saved;
    s32 i;

    if (func_ovl0C_01_80049B90(0x41A) == 0) {
        x = arg0->unk40->unk10;
        y = arg0->unk40->unk14;
        z = arg0->unk40->unk18;
        if (arg0->unk6C == 0.0f && arg0->unk68 == 0.0f) {
            func_ovl0C_01_80049E08(arg0, 0xC0, 12.0f);
        } else {
            arg0->unk68 = 0.0f;
            arg0->unk6C += 2.0f;
            func_ovl0C_01_80049E08(arg0, 0xC0, 3.0f);
        }
        moved = 0;
        if (arg0->unk8 & 3) {
            if (arg0->unk8 & 2) {
                for (i = 0; i < 5; i++) {
                    if (func_ovl0C_01_80049038(i) == arg0) {
                        break;
                    }
                }
                other = i < 5 ? func_ovl0C_01_80048FF8(i) : NULL;
            } else {
                for (i = 0; i < 5; i++) {
                    if (func_ovl0C_01_80048FF8(i) == arg0) {
                        break;
                    }
                }
                other = i < 5 ? func_ovl0C_01_80049038(i) : NULL;
            }
        } else {
            other = NULL;
        }
        saved = arg0->unkC;
        arg0->unkC = 0;
        if (other != NULL) {
            if (func_ovl0C_01_800498D8(arg0, 0x10, other) != 0) {
                moved = 1;
            }
        } else if (func_ovl0C_01_80049768(arg0, 0x10) != 0) {
            moved = 1;
        }
        arg0->unkC = saved;
        if (moved != 0) {
            arg0->unk40->unk10 = x;
            arg0->unk40->unk14 = y;
            arg0->unk40->unk18 = z;
        }
    }
}

void func_ovl0C_01_80047A60(void) {
    UnkStruct_ovl0C_01_8004A17C *p;
    UnkStructA *obj;
    f32 step;
    f32 dist;
    s16 alpha;

    p = func_ovl0C_01_80049930();
    obj = p->unk0;
    func_ovl0C_01_80048DF8(D_ovl0C_01_8004A17C->unk10, D_ovl0C_01_8004A17C->unk14, D_ovl0C_01_8004A17C->unk18,
                           D_ovl0C_01_8004A17C->unk1C, D_ovl0C_01_8004A17C->unk20, 0x10);
    if (p->unk28 != 0) {
        step = 0.0f;
        dist = 0.0f;
        while (dist < 25.0f) {
            func_ovl0C_01_80049950();
            dist += step;
            obj->unk40->unk24 += step;
            step += 0.5f;
        }
        obj->unk40->unk24 = 25.0f;
        func_ovl0C_01_80049EB0(0x43, 1600.0f, 700.0f, 2750.0f);
    }
    func_ovl0C_01_800497B8(p->unk0, 0x80000);
    obj->unk68 = 0.0f;
    obj->unk70 = 1.6333334f;
    alpha = 0xFF;
    while (1) {
        alpha -= 0xA;
        if (p->unk28 == 0) {
            func_ovl0C_01_80049838(obj);
        }
        if (alpha < 0) {
            if (p->unk28 == 0) {
                func_ovl0C_01_80049EB0(0x43, 3000.0f, 500.0f, 1400.0f);
            }
            alpha = 0;
            func_ovl0C_01_800497C0(p->unk0, 0x01000000);
            if (p->unk28 != 0) {
                func_ovl0C_01_80048DF8(0xE, 4, 0x19, 0xF, 0x1A, 0x11);
            }
            if (p->unk28 != 0 && func_ovl0C_01_80049B90(0x413) == 0) {
                func_ovl0C_01_80049B80(0x413);
                func_ovl0C_01_800446F8(3);
            }
            func_ovl0C_01_800497D0(p->unk0);
            func_ovl0C_01_80049918();
        }
        p->unk0->unk40->unk36 = alpha;
        func_ovl0C_01_80049950();
    }
}

void func_ovl0C_01_800477EC(void) {
    UnkStruct_ovl0C_01_8004A1A8 *rec;
    UnkStructA *obj;
    s16 alpha;
    s32 i;

    rec = func_ovl0C_01_80049930();
    obj = rec->unk4;
    obj->unk30 = 4;
    obj->unkC = 0xC0;
    obj->unk34 = 50.0f;
    obj->unk38 = 100.0f;
    while (TRUE) {
        if ((obj->unk10 & 0xC0) && func_ovl0C_01_80049B90(rec->unk24) == 0) {
            func_ovl0C_01_80049B80(rec->unk24);
            func_ovl0C_01_80049D58(0xF, rec->unk8, rec->unkC, rec->unk10, 0);
            func_ovl0C_01_80049E90(0x49);
            func_ovl0C_01_800497B8(rec->unk4, 0x80000);
            alpha = 0xFF;
            while (TRUE) {
                alpha -= 10;
                if (alpha < 0) {
                    alpha = 0;
                    func_ovl0C_01_800497C0(rec->unk4, 0x01000000);
                    func_ovl0C_01_80048E00(rec->unk14, rec->unk20, rec->unk1C, rec->unk14, rec->unk18, rec->unk1C, 0x10);
                    func_ovl0C_01_80048DF8(rec->unk14, rec->unk18, rec->unk1C, rec->unk14, rec->unk1C, 0x11);
                    /* indexed: a pointer walk keeps &D_ovl0C_01_8004A1A8[0] in
                     * one register where the original materializes it */
                    i = 0;
                    while (D_ovl0C_01_8004A1A8[i].unk2 != 0) {
                        if (func_ovl0C_01_80049B90(D_ovl0C_01_8004A1A8[i].unk24) == 0) {
                            break;
                        }
                        i = D_ovl0C_01_8004A1A8[i].unk2;
                    }
                    if (D_ovl0C_01_8004A1A8[i].unk2 == 0 && func_ovl0C_01_80049B90(rec->unk28) == 0) {
                        func_ovl0C_01_80049B80(rec->unk28);
                        func_ovl0C_01_800477B0();
                    }
                    func_ovl0C_01_800497D0(rec->unk4);
                    func_ovl0C_01_80049918();
                }
                rec->unk4->unk40->unk36 = alpha;
                func_ovl0C_01_80049950();
            }
        }
        func_ovl0C_01_80049950();
    }
}

void func_ovl0C_01_800477B0(void) {
    func_ovl0C_01_80049908(func_ovl0C_01_80047A60, D_ovl0C_01_8004A17C, 0, 0, 0x110);
}

void func_ovl0C_01_8004772C(void) {
    UnkStructA *obj;
    s32 alpha;
    s32 step;

    func_ovl0C_01_80048FA8(1);
    func_ovl0C_01_80049928(10);
    obj = func_ovl0C_01_80048FF8(func_ovl0C_01_80048F98());
    func_ovl0C_01_80049E90(0x44);
    func_ovl0C_01_800497B8(obj, 0x80000);
    step = 0x11;
    for (alpha = 0xFF; alpha > 0; alpha -= step) {
        obj->unk40->unk36 = alpha;
        func_ovl0C_01_80049950();
    }
    obj->unk40->unk36 = 0;
    func_ovl0C_01_80049918();
}

void func_ovl0C_01_800476AC(void) {
    func_ovl0C_01_80048F20(0);
    func_ovl0C_01_80049050(1);
    func_ovl0C_01_80048FC0("WM1 WG1 WSH WAP WDE WB5 ST1 WDN WB0 M1 ST1");
    func_ovl0C_01_80048FE0(0x400);
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH ST60 M2 ST10 WDS WB2 ST1 WDN WB0 ST150");
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH WDS WB0 ST10 M1 ST1");
    func_ovl0C_01_80048FE0(0x400);
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH ST60 M2 ST180 WDE WB0");
    func_ovl0C_01_80049928(0x168);
    func_ovl0C_01_8004A008();
    func_ovl0C_01_80049918();
}

void func_ovl0C_01_80047564(void) {
    func_ovl0C_01_80048F20(0);
    func_ovl0C_01_80049050(3);
    func_ovl0C_01_80049D88(func_ovl0C_01_80048F98(), 2);
    func_ovl0C_01_80049D90(func_ovl0C_01_80048F98(), 8);
    func_ovl0C_01_80048FC0("WM1 WG1 WSH WAP WDW M1 ST1");
    func_ovl0C_01_80048FE0(0x400);
    func_ovl0C_01_80048FC0("WM1 WG1 WAP ST60 M2 ST30");
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH M1 ST1");
    func_ovl0C_01_80048FE0(0x400);
    func_ovl0C_01_80048FC0("WM1 WG1 WAP ST60 M2 ST45");
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH WDW WB1 ST30 M0 ST30");
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH WDS WB3 ST1 WDN WB0 ST30");
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH M1 ST30");
    func_ovl0C_01_80048FE0(0x400);
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH ST60 M2 ST30");
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH WDE WB1 ST1 WDN WB0 ST1 M0 ST10 M0 ST30");
    func_ovl0C_01_80049050(1);
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH M1 ST8 M2 ST30");
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH WDE WB2 ST1 WDN WB0 ST1 M1 ST10");
    func_ovl0C_01_80048FE0(0x400);
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH ST30 M2 ST1");
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH WDE WB2 ST1 WDN WB3 ST1 M0 ST25");
    func_ovl0C_01_80048FC0("WM1 WG1 WAP WSH WDN WB3 ST1 WDE WB3 ST1 WDS WB3 ST1 WDW WB3");
    func_ovl0C_01_80049928(0xF0);
    func_ovl0C_01_8004A008();
    func_ovl0C_01_80049918();
}

void func_ovl0C_01_800474FC(void) {
    func_ovl0C_01_80048E00(0x13, 3, 0x18, 0x19, 5, 0x18, 0x10);
    func_ovl0C_01_80048DF8(0x13, 2, 0x18, 0x19, 0x18, 0x11);
}

void func_ovl0C_01_80047454(void) {
    UnkStructA_40 *s = ((UnkStructA *)func_ovl0C_01_80049930())->unk40;

    while (s->unk20 < 315.0f) {
        s->unk20 += 4.5f;
        func_ovl0C_01_80049950();
    }
    s->unk20 = 315.0f;
    func_ovl0C_01_80049918();
}

void func_ovl0C_01_80047338(void) {
    UnkStructA_40 *s = ((UnkStructA *)func_ovl0C_01_80049930())->unk40;
    f32 a;

    while (!(s->unk20 > 90.0f && s->unk20 < 315.0f)) {
        a = s->unk20 + 6.75f;
        if (a >= 360.0f) {
            s->unk20 = a - 360.0f;
        } else {
            s->unk20 = a < 0.0f ? a + 360.0f : a;
        }
        func_ovl0C_01_80049950();
    }
    s->unk20 = 90.0f;
    func_ovl0C_01_80049918();
}

void func_ovl0C_01_80047268(void) {
    s32 var_s0;

    if (!(*func_ovl0C_01_80048F08() & 2)) {
        func_ovl0C_01_80048F20(0);
        func_ovl0C_01_80049718();
        func_ovl0C_01_80049660(0x7F);
        func_ovl0C_01_800495F8(3500.0f, 300.0f, 1550.0f);
        func_ovl0C_01_80049618(225.0f, 45.0f, 2400.0f);
        var_s0 = 0;
        do {
            func_ovl0C_01_80049950();
            var_s0 += 1;
        } while (var_s0 != 0x168);
        func_ovl0C_01_80049720();
        func_ovl0C_01_800496E8(D_ovl0C_01_8004A980);
        func_ovl0C_01_80049658(0x1F);
        func_ovl0C_01_80048F20(1);
    }
    func_ovl0C_01_80049918();
}

void func_ovl0C_01_80047074(s32 arg0) {
    s32 temp_v0;

    switch (arg0) {                                 /* irregular */
    case 0x2:
        func_ovl0C_01_8004701C();
        break;
    case 0x10:
        func_ovl0C_01_80046F84();
        break;
    case 0x11:
        func_ovl0C_01_80046F28();
        break;
    case 0x12:
        func_ovl0C_01_80046EBC();
        break;
    case 0x13:
        func_ovl0C_01_80046E48();
        break;
    case 0x14:
        func_ovl0C_01_80046DE4();
        break;
    case 0x15:
        func_ovl0C_01_80046D84();
        break;
    case 0x16:
        func_ovl0C_01_80046D20();
        break;
    case 0x17:
        func_ovl0C_01_80046CC4();
        break;
    case 0x18:
        func_ovl0C_01_80046C68();
        break;
    case 0x19:
        func_ovl0C_01_80046BF4();
        break;
    case 0x1A:
        func_ovl0C_01_80046B98();
        break;
    case 0x4:
        func_ovl0C_01_80046224();
        break;
    case 0x5:
        func_ovl0C_01_80045800();
        break;
    case 0x50:
        func_ovl0C_01_800455AC();
        break;
    case 0x52:
        func_ovl0C_01_800454C0();
        break;
    case 0x3:
        func_ovl0C_01_80045194();
        break;
    case 0xF:
        func_ovl0C_01_80043C20();
        break;
    case 0xC:
        func_ovl0C_01_80049000(1);
        break;
    case 0x1:
        temp_v0 = D_ovl0C_01_8004A9C8.unk0;
        if (temp_v0 == 8) {
            func_ovl0C_01_8004A010();
        }
        if (temp_v0 == 9) {
            func_ovl0C_01_8004A010();
        }
        func_ovl0C_01_80049B88(0x42A);
        break;
    }
}

void func_ovl0C_01_80047054(void) {
    func_ovl0C_01_8004701C();
}

void func_ovl0C_01_8004701C(void) {
    func_ovl0C_01_80046FDC();
    func_ovl0C_01_80048EA0(func_ovl0C_01_80048754);
    func_ovl0C_01_80048EF0(func_ovl0C_01_80048694);
}

void func_ovl0C_01_80046FDC(void) {
    func_ovl0C_01_80049B88(0x400);
    func_ovl0C_01_80049B88(0x401);
    func_ovl0C_01_80049B88(0x402);
    func_ovl0C_01_80049B88(0x403);
    func_ovl0C_01_80049B88(0x404);
}

void func_ovl0C_01_80046F84(void) {
    func_ovl0C_01_80049E38(2);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(3, 2, 0xF);
    SET_STATE(0, 0x40, 0x40, 0.0f, 0);
}

void func_ovl0C_01_80046F28(void) {
    func_ovl0C_01_80049E38(2);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(0x26, 2, 0xA);
    SET_STATE(1, 0x80, 0, 0.0f, 0);
}

void func_ovl0C_01_80046EBC(void) {
    func_ovl0C_01_80049E38(2);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(0x13, 5, 0x13);
    SET_STATE(2, 0, 0, 0.0f, 1);
    func_ovl0C_01_80048F40(0x28, 0x1A);
}

void func_ovl0C_01_80046E48(void) {
    func_ovl0C_01_80049E38(2);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(0x2E, 5, 6);
    SET_STATE(3, 0xC0, 0x40, 0.0f, 1);
    func_ovl0C_01_80048F40(0x28, 0x17);
}

void func_ovl0C_01_80046DE4(void) {
    func_ovl0C_01_80049E38(2);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(0x2E, 2, 0xF);
    SET_STATE(4, 0xC0, 0x80, 0.0f, 5);
}

void func_ovl0C_01_80046D84(void) {
    func_ovl0C_01_80049E38(2);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(5, 1, 0x1A);
    SET_STATE(5, 0, 0, 0.0f, 0);
    func_ovl0C_01_80049720();
}

void func_ovl0C_01_80046D20(void) {
    func_ovl0C_01_80049E38(2);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(0x2C, 2, 0x16);
    SET_STATE(6, 0, 0x80, 0.0f, 0);
    func_ovl0C_01_80049720();
}

void func_ovl0C_01_80046CC4(void) {
    func_ovl0C_01_80049E38(2);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(0x14, 1, 2);
    SET_STATE(7, 0x40, 0x40, 0.0f, 0);
}

void func_ovl0C_01_80046C68(void) {
    func_ovl0C_01_80049E38(0);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(0x1B, 1, 0xE);
    SET_STATE(8, 0x40, 0x40, 0.0f, 0);
}

void func_ovl0C_01_80046BF4(void) {
    func_ovl0C_01_80049B80(0x41F);
    func_ovl0C_01_80049B80(0x420);
    func_ovl0C_01_80049B80(0x421);
    func_ovl0C_01_80049E38(0);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(0x19, 1, 0x14);
    SET_STATE(9, 0xC0, 0xC0, 0.0f, 0);
}

void func_ovl0C_01_80046B98(void) {
    func_ovl0C_01_80049E38(2);
    func_ovl0C_01_800468EC();
    func_ovl0C_01_80048F70(0x13, 5, 0x13);
    SET_STATE(0xA, 0, 0, 0.0f, 1);
}

void func_ovl0C_01_800468EC(void) {
    UnkStructA *temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    u32 (*var_s0)[3];

    func_ovl0C_01_80049C70(D_ovl0C_01_8004A0B0);
    func_ovl0C_01_80048DB8(0x242);
    var_s0 = D_ovl0C_01_8004A0D4;
    var_s1 = 0;
    do {
        func_ovl0C_01_80049E18((s32) var_s0[0][0], (s32) var_s0[0][1], (s32) var_s0[0][2]);
        var_s1 += 1;
        var_s0 += 0xC;
    } while (var_s1 < 4);
    func_ovl0C_01_80048DD0(0x24C);
    func_ovl0C_01_80048F68();
    func_ovl0C_01_80048E98(func_ovl0C_01_80047E9C, 1);
    func_ovl0C_01_80048E98(func_ovl0C_01_80047CA8, 5);
    func_ovl0C_01_80046740();
    func_ovl0C_01_800464F8();
    func_ovl0C_01_800463E0();
    temp_v0 = func_ovl0C_01_80049800(D_ovl0C_01_8004A54C.unk8, 0xD0, 0.0f, 0.0f, 0.0f);
    D_ovl0C_01_8004A54C.unk0 = temp_v0;
    func_ovl0C_01_800497B8(temp_v0, 0x01080000);
    func_ovl0C_01_800497C0(D_ovl0C_01_8004A54C.unk0, 0x02000000);
    if (D_ovl0C_01_8004A54C.unkC != -1) {
        if ((D_ovl0C_01_8004A54C.unkE != -1) && (D_ovl0C_01_8004A54C.unk10 != -1)) {
            if (D_ovl0C_01_8004A54C.unk12 != -1) {
                temp_v0_2 = func_ovl0C_01_80049500(D_ovl0C_01_8004A54C.unk0->unk40, 0, (s32) D_ovl0C_01_8004A54C.unkC, (s32) D_ovl0C_01_8004A54C.unkE, (s32) D_ovl0C_01_8004A54C.unk10, (s32) D_ovl0C_01_8004A54C.unk12);
                D_ovl0C_01_8004A54C.unk4 = temp_v0_2;
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
    D_ovl0C_01_8004A54C.unk0->unk40->unk10 = 0.0f * 10.0f;
    D_ovl0C_01_8004A54C.unk0->unk40->unk14 = 0.0f * 10.0f;
    D_ovl0C_01_8004A54C.unk0->unk40->unk18 = 0.0f * 10.0f;
    D_ovl0C_01_8004A54C.unk0->unk40->unk1C = 0.0f;
    D_ovl0C_01_8004A54C.unk0->unk40->unk20 = 0.0f;
    D_ovl0C_01_8004A54C.unk0->unk40->unk24 = 0.0f;
    D_ovl0C_01_8004A54C.unk0->unk40->unk28 = 0.0f;
    D_ovl0C_01_8004A54C.unk0->unk40->unk2C = 0.0f;
    D_ovl0C_01_8004A54C.unk0->unk40->unk30 = 1.0f;
    if (func_ovl0C_01_80049B90(0x41A) != 0) {
        func_ovl0C_01_80049508(D_ovl0C_01_8004A54C.unk4);
        D_ovl0C_01_8004A54C.unk4 = func_ovl0C_01_80049500(D_ovl0C_01_8004A54C.unk0->unk40, 0, 0xA, 0x400, (s32) D_ovl0C_01_8004A54C.unk10, (s32) D_ovl0C_01_8004A54C.unk12);
    }
    func_ovl0C_01_80049C58(0x37, 0x4D, 0xFF);
}

void func_ovl0C_01_800468E4(void) {

}

void func_ovl0C_01_80046740(void) {
    UnkStruct_ovl0C_01_8004A104 *p;
    f32 angle;
    UnkStructA *obj;
    s16 i;

    for (i = 0; i < 1; i++) {
        func_ovl0C_01_80046684(i);
        p = &D_ovl0C_01_8004A104[i];
        obj = func_ovl0C_01_80049800(0x2A9, 0xD0, p->unk8, p->unkC, p->unk10);
        func_ovl0C_01_800497B8(obj, 0x01000000);
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
        func_ovl0C_01_80046628(p);
    }
}

void func_ovl0C_01_80046684(s32 arg0) {
    D_ovl0C_01_8004A9E0[arg0] = func_ovl0C_01_800497E0(-1, 0, 0x20, 0);
    D_ovl0C_01_8004A9E0[arg0]->unk40->unk10 = D_ovl0C_01_8004A104[arg0].unk18;
    D_ovl0C_01_8004A9E0[arg0]->unk40->unk14 = D_ovl0C_01_8004A104[arg0].unk1C;
    D_ovl0C_01_8004A9E0[arg0]->unk40->unk18 = D_ovl0C_01_8004A104[arg0].unk20;
    D_ovl0C_01_8004A9E0[arg0]->unk30 = 1;
    D_ovl0C_01_8004A9E0[arg0]->unk34 = 200.0f;
    D_ovl0C_01_8004A9E0[arg0]->unk38 = 100.0f;
}

void func_ovl0C_01_80046628(UnkStruct_ovl0C_01_8004A104 *arg0) {
    arg0->unk4->unk40->unk48->unk4->unk4 = func_ovl0C_01_800494F8(arg0->unk4->unk40, 0) - 0.0001f;
    func_ovl0C_01_80044C34(arg0);
}

void func_ovl0C_01_800464F8(void) {
    UnkStructA *temp_v0;
    UnkStruct_ovl0C_01_8004A3CC *temp_s0;
    s16 var_s3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s2_2;

    func_ovl0C_01_800430F0();
    var_s3 = 0;
    do {
        temp_s0 = &D_ovl0C_01_8004A3CC[var_s3];
        if (func_ovl0C_01_80049B90(temp_s0->unk28) == 0) {
            temp_v0 = func_ovl0C_01_80049800(temp_s0->unk4, 0xD0, temp_s0->unk8, temp_s0->unkC, temp_s0->unk10);
            func_ovl0C_01_800497B8(temp_v0, 0x03000000);
            temp_s1 = temp_s0->unk14;
            temp_s2 = temp_s0->unk1C;
            temp_s0->unk0 = temp_v0;
            func_ovl0C_01_80048DF8(temp_s1, temp_s0->unk20, temp_s2, temp_s1 + 1, temp_s2 + 1, 0x11);
            temp_s1_2 = temp_s0->unk14;
            temp_s2_2 = temp_s0->unk1C;
            func_ovl0C_01_80048E00(temp_s1_2, temp_s0->unk24, temp_s2_2, temp_s1_2 + 1, temp_s0->unk18, temp_s2_2 + 1, 0x1F);
        }
        var_s3 += 1;
    } while (var_s3 < 4);
}

void func_ovl0C_01_800463E0(void) {
    UnkStructA *temp_v0;
    UnkStructA_40 *temp_v0_2;
    UnkStruct_ovl0C_01_8004A584 *temp_s0;
    s16 var_s2;

    var_s2 = 0;
    do {
        temp_s0 = &D_ovl0C_01_8004A584[var_s2];
        if (func_ovl0C_01_80049B90(temp_s0->unk10) == 0) {
            temp_v0 = func_ovl0C_01_80049800(0x2A3, 0xD0, temp_s0->unk4, temp_s0->unk8, temp_s0->unkC);
            func_ovl0C_01_800497B8(temp_v0, 0x03080000);
            temp_s0->unk0 = temp_v0;
            temp_v0_2 = temp_v0->unk40;
            temp_v0_2->unkC |= 0x8000;
            func_ovl0C_01_800494C0(temp_s0->unk0->unk40, 2);
            func_ovl0C_01_800494C8(temp_s0->unk0->unk40, 0x2A4, 0, 0);
            func_ovl0C_01_800494C8(temp_s0->unk0->unk40, 0x2A4, 1, 1);
        }
        var_s2 += 1;
    } while (var_s2 < 4);
}

void func_ovl0C_01_800463D8(void) {

}

void func_ovl0C_01_800463B0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    SET_STATE(arg0, arg1, arg2, arg3, arg4);
}

void func_ovl0C_01_80046224(void) {
    s32 temp_v0;

    func_ovl0C_01_800460F4();
    if ((D_ovl0C_01_8004A9C8.unk0 != 5) && (D_ovl0C_01_8004A9C8.unk0 != 6)) {
        func_ovl0C_01_80049B88(0x429);
    }
    if (func_ovl0C_01_80049B90(0x40C) == 0) {
        func_ovl0C_01_80045FBC(&D_ovl0C_01_8004A3BC, D_ovl0C_01_8004A2A4, 1);
        func_ovl0C_01_80045E68(D_ovl0C_01_8004A22C, 1);
    }
    if (func_ovl0C_01_80049B90(0x40F) == 0) {
        func_ovl0C_01_80045D90();
        func_ovl0C_01_80045CD4();
        func_ovl0C_01_80048DF8(0xE, 4, 0x19, 0xF, 0x1A, 0x1F);
    }
    temp_v0 = D_ovl0C_01_8004A9C8.unk0;
    if (temp_v0 == 8) {
        func_ovl0C_01_80045C4C();
    }
    if (temp_v0 == 9) {
        func_ovl0C_01_80045BD0();
    }
    if (temp_v0 == 2) {
        func_ovl0C_01_80045B78();
    }
    if (temp_v0 == 4) {
        func_ovl0C_01_80045B3C(D_ovl0C_01_8004A104);
    }
    if (((temp_v0 == 5) || (temp_v0 == 6)) && (func_ovl0C_01_80049B90(0x429) != 0)) {
        func_ovl0C_01_80045B3C(D_ovl0C_01_8004A104);
    }
    func_ovl0C_01_800438E8();
    D_ovl0C_01_8004A9C4 = D_ovl0C_01_8004A9C0;
    func_ovl0C_01_800459FC();
}

void func_ovl0C_01_800460F4(void) {
    f32 pad[2]; /* unused: the original's frame is 8 bytes bigger */
    f32 angle;
    f32 sp20;
    f32 sp1C;

    func_ovl0C_01_80048FC8();
    switch (D_ovl0C_01_8004A9C8.unk8) {
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
        func_ovl0C_01_80049618(angle, 32768.0f, 32768.0f);
    } else {
        sp20 = D_ovl0C_01_8004A9C8.unkC;
        func_ovl0C_01_80049620(&sp1C, NULL, NULL);
        func_ovl0C_01_80049618(sp1C + sp20, 32768.0f, 32768.0f);
    }
    func_ovl0C_01_80048FB0(D_ovl0C_01_8004A9C8.unk4);
    func_ovl0C_01_800496B0(45.0f, 45.1f);
}

void func_ovl0C_01_800460AC(f32 arg0) {
    f32 sp1C;

    func_ovl0C_01_80049620(&sp1C, NULL, NULL);
    func_ovl0C_01_80049618(sp1C + arg0, 32768.0f, 32768.0f);
}

/* the wall the blocks stand in front of, and the blocks' tiles */
void func_ovl0C_01_80045FBC(UnkStruct_ovl0C_01_8004A3BC *arg0, UnkStruct_ovl0C_01_8004A2A4 *arg1, s32 arg2) {
    UnkStruct_ovl0C_01_8004A2A4 *p;
    UnkStructA *obj;

    p = arg1;
    obj = func_ovl0C_01_80049800(0x2BB, 0xD0, arg0->unk4, arg0->unk8, arg0->unkC);
    func_ovl0C_01_800497B8(obj, arg2 ? 0x01000000 : 0x01000000);
    arg0->unk0 = obj;
    for (; p->unk2 != 0; p++) {
        func_ovl0C_01_80048DF8(p->unk18, p->unk1A, p->unk1C, p->unk18 + 3, p->unk1C + 2, 0x11);
        func_ovl0C_01_80048DF8(p->unk18, p->unk1E, p->unk1C, p->unk18 + 3, p->unk1C + 2, 0x1F);
    }
}

/* the switches' objects, turned if already hit, and their tiles */
void func_ovl0C_01_80045E68(UnkStruct_ovl0C_01_8004A22C *arg0, s32 arg1) {
    UnkStruct_ovl0C_01_8004A22C *p;
    UnkStructA *obj;

    p = arg0;
    func_ovl0C_01_800430F0();
    for (; p->unk2 != 0; p++) {
        obj = func_ovl0C_01_80049800(0x2AE, 0xD0, p->unk8, p->unkC, p->unk10);
        func_ovl0C_01_800497B8(obj, arg1 ? 0x01000000 : 0x01000000);
        p->unk4 = obj;
        p->unk22 = 0;
        func_ovl0C_01_800494C0(obj->unk40, 2);
        if (!func_ovl0C_01_80049B90(p->unk24)) {
            func_ovl0C_01_800494C8(p->unk4->unk40, 0x2AF, 0, 0);
            func_ovl0C_01_800494C8(p->unk4->unk40, 0x2AF, 1, 1);
        } else {
            func_ovl0C_01_800494C8(p->unk4->unk40, 0x2AF, 0, 2);
            func_ovl0C_01_800494C8(p->unk4->unk40, 0x2AF, 1, 3);
        }
        func_ovl0C_01_80048E00(p->unk18, p->unk1A, p->unk1C, p->unk18 + 1, p->unk1E, p->unk1C + 1, 0x1F);
    }
}

void func_ovl0C_01_80045D90(void) {
    UnkStruct_ovl0C_01_8004A17C *p;
    UnkStructA *obj;
    s16 i;

    for (i = 0; i < 1; i++) {
        p = &D_ovl0C_01_8004A17C[i];
        obj = func_ovl0C_01_80049800(0x2AA, 0xD0, p->unk4, p->unk8, p->unkC);
        func_ovl0C_01_800497B8(obj, 0x01000000);
        p->unk0 = obj;
        obj->unk40->unk20 = p->unk24;
        func_ovl0C_01_80048DF8(D_ovl0C_01_8004A17C->unk10, D_ovl0C_01_8004A17C->unk14, D_ovl0C_01_8004A17C->unk18,
                               D_ovl0C_01_8004A17C->unk1C, D_ovl0C_01_8004A17C->unk20, 0x11);
    }
}

void func_ovl0C_01_80045CD4(void) {
    UnkStruct_ovl0C_01_8004A1A8 *p;
    UnkStructA *obj;

    for (p = D_ovl0C_01_8004A1A8; p->unk2 != 0; p++) {
        if (func_ovl0C_01_80049B90(p->unk24) == 0) {
            obj = func_ovl0C_01_80049800(0x2AB, 0x20, p->unk8, p->unkC, p->unk10);
            func_ovl0C_01_800497B8(obj, 0x01000000);
            p->unk4 = obj;
            func_ovl0C_01_80048E00(p->unk14, p->unk20, p->unk1C, p->unk14, p->unk18, p->unk1C, 0x1F);
        }
    }
}

void func_ovl0C_01_80045C4C(void) {
    func_ovl0C_01_80049660(0x7F);
    func_ovl0C_01_800495F8(3300.0f, 300.0f, 1300.0f);
    func_ovl0C_01_80049618(-45.0f, 30.0f, 2500.0f);
    func_ovl0C_01_80048FA8(1);
    func_ovl0C_01_80049E38(0);
    func_ovl0C_01_80049908(func_ovl0C_01_800476AC, NULL, 0, 0, 0x130);
}

void func_ovl0C_01_80045BD0(void) {
    func_ovl0C_01_80049618(0.0f, 60.0f, 32768.0f);
    func_ovl0C_01_80049660(0xF);
    func_ovl0C_01_80049670(2);
    func_ovl0C_01_800496B0(60.0f, 60.1f);
    func_ovl0C_01_80048FA8(1);
    func_ovl0C_01_80049908(func_ovl0C_01_80047564, NULL, 0, 0, 0x130);
}

void func_ovl0C_01_80045B78(void) {
    D_ovl0C_01_8004A9BC = func_ovl0C_01_80048FF8(func_ovl0C_01_80048F98());
    func_ovl0C_01_800497B8(D_ovl0C_01_8004A9BC, 0x80000);
    D_ovl0C_01_8004A9BC->unk40->unk36 = 0;
}

void func_ovl0C_01_80045B3C(UnkStruct_ovl0C_01_8004A104 *arg0) {
    arg0->unk4->unk40->unk48->unk4->unk4 = 0.0f;
    func_ovl0C_01_80045A78(arg0);
}

void func_ovl0C_01_80045A78(UnkStruct_ovl0C_01_8004A104 *arg0) {
    func_ovl0C_01_80048E00(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk34, arg0->unk38, 0x10);
    func_ovl0C_01_80048DF8(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk38, 0x11);
    func_ovl0C_01_80048DF8(arg0->unk3C, arg0->unk40, arg0->unk44, arg0->unk48, arg0->unk4C, 0x12);
    func_ovl0C_01_80048DF0(arg0->unk50, arg0->unk54, arg0->unk58, arg0->unk60);
    func_ovl0C_01_80048DF0(arg0->unk64, arg0->unk68, arg0->unk6C, arg0->unk74);
}

void func_ovl0C_01_800459FC(void) {
    Vec3f pos;
    UnkStructA *obj;

    if (func_ovl0C_01_800450B0() != 0) {
        func_ovl0C_01_80045920((f32 *)&pos);
        obj = func_ovl0C_01_80049800(0x328, 0xC0, pos.x, pos.y, pos.z);
        D_ovl0C_01_8004A5B4->unk0 = obj;
        func_ovl0C_01_800497F0(obj);
        func_ovl0C_01_800497B8(obj, 0x03000010);
        func_ovl0C_01_80045894(obj);
    }
}

void func_ovl0C_01_80045920(f32 *pos) {
    switch (D_ovl0C_01_8004A9C0) {
        case 1:
            pos[0] = 1700.0f;
            pos[1] = 3000.0f;
            pos[2] = 1500.0f;
            break;
        case 2:
            pos[0] = 2700.0f;
            pos[1] = 200.0f;
            pos[2] = 1500.0f;
            break;
        case 3:
            pos[0] = 1600.0f;
            pos[1] = 200.0f;
            pos[2] = 2500.0f;
            break;
        case 4:
            pos[0] = 3300.0f;
            pos[1] = 300.0f;
            pos[2] = 1100.0f;
            break;
    }
}

void func_ovl0C_01_80045894(UnkStructA *arg0) {
    switch (D_ovl0C_01_8004A9C0) {                  /* irregular */
    case 1:
        arg0->unk40->unk20 = 270.0f;
        return;
    case 2:
        arg0->unk40->unk20 = 270.0f;
        return;
    case 3:
        arg0->unk40->unk20 = 90.0f;
        return;
    case 4:
        arg0->unk40->unk20 = 270.0f;
        return;
    }
}

void func_ovl0C_01_80045800(void) {
    if (D_ovl0C_01_8004A9C8.unk0 == 2) {
        func_ovl0C_01_80045774();
    }
    func_ovl0C_01_80048FB8(D_ovl0C_01_8004A9C8.unk4, 3, 4.0f, D_ovl0C_01_8004A9C8.unk10, 0, 1, 1);
    if (func_ovl0C_01_80049B90(0x40F) == 0) {
        func_ovl0C_01_800456B4();
    }
    if (func_ovl0C_01_80049B90(0x429) == 0) {
        func_ovl0C_01_80045648();
    }
}

void func_ovl0C_01_80045774(void) {
    s32 alpha;
    s32 step;

    func_ovl0C_01_80048FA8(1);
    func_ovl0C_01_80049E90(0x45);
    step = 0x11;
    for (alpha = 0; alpha < 0xFF; alpha += step) {
        D_ovl0C_01_8004A9BC->unk40->unk36 = alpha;
        func_ovl0C_01_80049950();
    }
    D_ovl0C_01_8004A9BC->unk40->unk36 = 0xFF;
    func_ovl0C_01_800497C0(D_ovl0C_01_8004A9BC, 0x80000);
    func_ovl0C_01_80048FA8(0);
}

void func_ovl0C_01_8004572C(void) {
    func_ovl0C_01_80048FB8(D_ovl0C_01_8004A9C8.unk4, 3, 4.0f, D_ovl0C_01_8004A9C8.unk10, 0, 1, 1);
}

void func_ovl0C_01_800456B4(void) {
    UnkStruct_ovl0C_01_8004A1A8 *p;

    for (p = D_ovl0C_01_8004A1A8; p->unk2 != 0; p++) {
        if (func_ovl0C_01_80049B90(p->unk24) == 0) {
            func_ovl0C_01_80049908(func_ovl0C_01_800477EC, p, 0, 0, 0x110);
        }
    }
}

void func_ovl0C_01_80045648(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        func_ovl0C_01_80049908(func_ovl0C_01_80048068, &D_ovl0C_01_8004A104[i], 0, 0, 0x110);
    }
}

void func_ovl0C_01_800455AC(void) {
    if (func_ovl0C_01_80048F80(0x13, 0x13, 0x14, 0x14) != 0) {
        func_ovl0C_01_80049908(func_ovl0C_01_8004772C, NULL, 0, 0, 0x130);
        func_ovl0C_01_80048F58(0x3C);
        func_ovl0C_01_80048EB0(0x2A, 0x14, 4);
    }
    if (func_ovl0C_01_80048F80(0x2E, 0xF, 0x2E, 0x10) != 0) {
        func_ovl0C_01_80045540(D_ovl0C_01_8004A104);
        func_ovl0C_01_80048EB0(0x29, 0x13, 0);
    }
}

void func_ovl0C_01_80045540(UnkStruct_ovl0C_01_8004A104 *arg0) {
    func_ovl0C_01_80048FA8(1);
    func_ovl0C_01_80049E90(0x4B);
    func_ovl0C_01_800497B8(arg0->unk4, 0x04000000);
    func_ovl0C_01_80049928(60);
    func_ovl0C_01_80049E90(0x46);
    func_ovl0C_01_80044C34(arg0);
    func_ovl0C_01_80049B88(0x429);
    func_ovl0C_01_80049928(10);
}

void func_ovl0C_01_800454C0(void) {
    if (func_ovl0C_01_80048F80(5, 0x1A, 5, 0x1A) != 0) {
        if (func_ovl0C_01_80049B90(0x416) == 0) {
            func_ovl0C_01_800452F4(D_ovl0C_01_8004A584);
        }
    }
    if (func_ovl0C_01_80048F80(0x2C, 0x16, 0x2C, 0x16) != 0) {
        if (func_ovl0C_01_80049B90(0x417) == 0) {
            func_ovl0C_01_800452F4(D_ovl0C_01_8004A59C);
        }
    }
}

void func_ovl0C_01_800452F4(UnkStruct_ovl0C_01_8004A584 *arg0) {
    f32 sp38;
    f32 sp34;
    f32 sp30;
    UnkStructA_40 *temp_v0;
    f32 temp_fs0;
    s16 var_s0;
    s16 var_s0_2;
    s16 var_s0_3;

    func_ovl0C_01_80048FA8(1);
    func_ovl0C_01_80049068();
    sp30 = arg0->unk4;
    sp34 = arg0->unk8;
    sp38 = arg0->unkC;
    func_ovl0C_01_80049DA8(&sp30);
    func_ovl0C_01_80049E78();
    func_ovl0C_01_80048F28(1);
    func_ovl0C_01_80049980(0xB0, 0xB0);
    func_ovl0C_01_80048F20(0);
    func_ovl0C_01_80049718();
    func_ovl0C_01_80048FD0(1);
    func_ovl0C_01_80049E90(0x50);
    var_s0 = 0;
    do {
        arg0->unk0->unk40->unk2C = (func_ovl0C_01_80049AB0((f32) var_s0) * 10.0f) + 1.0f;
        func_ovl0C_01_80049950();
        var_s0 += 2;
    } while (var_s0 < 0x5A);
    var_s0_2 = 0;
    do {
        arg0->unk0->unk40->unk30 = func_ovl0C_01_80049AB8((f32) var_s0_2);
        temp_v0 = arg0->unk0->unk40;
        temp_v0->unk28 = temp_v0->unk30;
        func_ovl0C_01_80049950();
        var_s0_2 += 2;
    } while (var_s0_2 < 0x5A);
    temp_fs0 = arg0->unk0->unk40->unk14;
    var_s0_3 = 0;
    do {
        arg0->unk0->unk40->unk14 = temp_fs0 + (func_ovl0C_01_80049AB0((f32) var_s0_3) * 1000.0f);
        func_ovl0C_01_80049950();
        var_s0_3 += 2;
    } while (var_s0_3 < 0x5A);
    func_ovl0C_01_80048EB0(0x29, arg0->unk10, 0);
}

void func_ovl0C_01_80045194(void) {
    s32 *sp1C;

    D_ovl0C_01_8004A99C = func_ovl0C_01_80048F98();
    func_ovl0C_01_80048F78(&D_ovl0C_01_8004A990);
    func_ovl0C_01_80048FA0(D_ovl0C_01_8004A99C, D_ovl0C_01_8004A980);
    if (func_ovl0C_01_80049B90(0x404) == 0) {
        sp1C = func_ovl0C_01_80049BA0();
        if ((func_ovl0C_01_80049B90(0x40C) == 0) && (*sp1C == 0) && (D_ovl0C_01_8004A9C8.unk0 == 0) && (func_ovl0C_01_800450B0() != 0) && (func_ovl0C_01_80049B90(0x411) == 0)) {
            func_ovl0C_01_80044D3C();
        }
    }
    if ((func_ovl0C_01_80049B90(0x404) == 0) && (D_ovl0C_01_8004A9C8.unk0 == 4)) {
        func_ovl0C_01_80044CC0(D_ovl0C_01_8004A104);
    }
    if (func_ovl0C_01_80049B90(0x40C) == 0) {
        func_ovl0C_01_80044A68(&D_ovl0C_01_8004A3BC.unk0, D_ovl0C_01_8004A2A4, D_ovl0C_01_8004A22C, 0x40C);
    }
    if ((func_ovl0C_01_80049B90(0x40C) != 0) && (func_ovl0C_01_80049B90(0x414) == 0)) {
        func_ovl0C_01_80049B80(0x414);
        func_ovl0C_01_800446F8(4);
    }
    func_ovl0C_01_80043E74();
    func_ovl0C_01_80049B80(0x404);
}

void func_ovl0C_01_8004514C(void) {
    UNK_MACRO_ovl0C_01_8004514C();
}

s32 func_ovl0C_01_800450B0(void) {
    s32 *st = func_ovl0C_01_80048F08();

    if (st[4] != 0) {
        return 0;
    }
    if (st[0] & 2) {
        return 0;
    }
    if (func_ovl0C_01_80049B70(0xA4) != 0) {
        return 0;
    }
    func_ovl0C_01_800438E8();
    if (D_ovl0C_01_8004A9C0 >= 5) {
        return 0;
    }
    return 1;
}

void func_ovl0C_01_80044D3C(void) {
    UnkStructA *sp60;
    s32 sp58;
    s32 sp54;
    UnkStructA_40 *sp50;
    f32 *sp48;
    UnkStructA_40 *temp_s0;
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *temp_v0_2;
    UnkStructA_40_48_4 *var_v0;
    UnkStructA_40_48_4 *var_v0_2;
    f32 *temp_a0;
    f32 temp_fs0;

    func_ovl0C_01_80049000(1);
    temp_s0 = D_ovl0C_01_8004A5B4->unk0->unk40;
    temp_s0->unkC |= 0x40;
    sp60 = D_ovl0C_01_8004A5B4->unk0;
    func_ovl0C_01_800494E0(temp_s0, 0x16, 0);
    temp_s0->unk48->unk4->unk4 = func_ovl0C_01_800494F8(temp_s0, 0) - 0.01f;
    sp50 = temp_s0;
    sp54 = 0x213;
    sp58 = 0x3C;
    func_ovl0C_01_80049900(&sp50);
    temp_a0 = &temp_s0->unk10;
    sp48 = temp_a0;
    func_ovl0C_01_800443A4(temp_a0, 500.0f, &temp_s0->unk14, 600.0f, 0x1E);
    func_ovl0C_01_80049EB0(0x211, temp_s0->unk10, temp_s0->unk14, temp_s0->unk18);
    var_v0 = temp_s0->unk48->unk4;
    if (var_v0->unk4 > 1.0f) {
        do {
            func_ovl0C_01_80049950();
            temp_v0 = temp_s0->unk48->unk4;
            temp_v0->unk4 -= 1.0f;
            var_v0 = temp_s0->unk48->unk4;
        } while (var_v0->unk4 > 1.0f);
    }
    var_v0->unk4 = 0.0f;
    if (temp_s0->unk14 > 300.0f) {
        do {
            func_ovl0C_01_80049950();
            temp_s0->unk14 -= 20.0f;
        } while (temp_s0->unk14 > 300.0f);
    }
    temp_s0->unk14 = 300.0f;
    func_ovl0C_01_80049520(0x358, 8);
    if (temp_s0->unk14 < 700.0f) {
        do {
            func_ovl0C_01_80049950();
            temp_s0->unk14 += 20.0f;
        } while (temp_s0->unk14 < 700.0f);
    }
    temp_s0->unk14 = 700.0f;
    func_ovl0C_01_80049EB0(0x211, temp_s0->unk10, 700.0f, temp_s0->unk18);
    var_v0_2 = temp_s0->unk48->unk4;
    temp_fs0 = func_ovl0C_01_800494F8(temp_s0, 0) - 0.01f;
    if (var_v0_2->unk4 < temp_fs0) {
        do {
            func_ovl0C_01_80049950();
            temp_v0_2 = temp_s0->unk48->unk4;
            temp_v0_2->unk4 += 1.0f;
            var_v0_2 = temp_s0->unk48->unk4;
        } while (var_v0_2->unk4 < temp_fs0);
    }
    var_v0_2->unk4 = temp_fs0;
    func_ovl0C_01_80049950();
    sp50 = temp_s0;
    sp54 = 0x20F;
    sp58 = 0x44;
    func_ovl0C_01_80049900(&sp50);
    func_ovl0C_01_80043248(sp48, -800.0f, 0x1E);
    temp_s0->unk48->unk4->unk4 = 0.0f;
    sp60->unk40->unk10 = 2700.0f;
    sp60->unk40->unk14 = 200.0f;
    sp60->unk40->unk18 = 1500.0f;
    func_ovl0C_01_80049B80(0x411);
    func_ovl0C_01_800438E8();
    D_ovl0C_01_8004A9C4 = D_ovl0C_01_8004A9C0;
    func_ovl0C_01_80049000(0);
}

void func_ovl0C_01_80044CC0(UnkStruct_ovl0C_01_8004A104 *arg0) {
    func_ovl0C_01_80048FA8(1);
    func_ovl0C_01_80049928(0x5A);
    func_ovl0C_01_80049E90(0x4B);
    func_ovl0C_01_800497B8(arg0->unk4, 0x04000000);
    func_ovl0C_01_80049928(0x3C);
    func_ovl0C_01_80049E90(0x46);
    func_ovl0C_01_80049928(0xA);
    func_ovl0C_01_80044C34(arg0);
    func_ovl0C_01_80049B88(0x429);
    func_ovl0C_01_80048FA8(0);
}

void func_ovl0C_01_80044C34(UnkStruct_ovl0C_01_8004A104 *arg0) {
    func_ovl0C_01_80048E00(arg0->unk24, arg0->unk28, arg0->unk2C, arg0->unk30, arg0->unk34, arg0->unk38, 0x1F);
    func_ovl0C_01_80048DF0(arg0->unk50, arg0->unk54, arg0->unk58, arg0->unk5C);
    func_ovl0C_01_80048DF0(arg0->unk64, arg0->unk68, arg0->unk6C, arg0->unk70);
}

/* bombs on the switches: a switch hit turns, and once none is left the
 * blocks crumble */
s32 func_ovl0C_01_80044A68(UnkStruct_ovl0C_01_8004A3BC *arg0, UnkStruct_ovl0C_01_8004A2A4 *arg1, UnkStruct_ovl0C_01_8004A22C *list, s32 arg3) {
    UnkStructA_40 *pos;
    s32 hit;
    s32 left;
    s32 ret;
    UnkStruct_ovl0C_01_8004A22C *saved;

    saved = list;
    D_ovl0C_01_8004A9DC->unk30 = 4;
    D_ovl0C_01_8004A9DC->unk34 = 90.0f;
    D_ovl0C_01_8004A9DC->unk38 = 400.0f;
    left = 0;
    for (; list->unk2 != 0; list++) {
        if (!func_ovl0C_01_80049B90(list->unk24)) {
            D_ovl0C_01_8004A9DC->unk40->unk10 = list->unk8;
            D_ovl0C_01_8004A9DC->unk40->unk14 = list->unkC;
            D_ovl0C_01_8004A9DC->unk40->unk18 = list->unk10;
            hit = func_ovl0C_01_80049768(D_ovl0C_01_8004A9DC, 0xC0);
            if (hit) {
                if (hit & 0x6000) {
                    func_ovl0C_01_80049EB0(0x49, list->unk8, list->unkC, list->unk10);
                    func_ovl0C_01_800494C8(list->unk4->unk40, 0x2AF, 0, 2);
                    func_ovl0C_01_800494C8(list->unk4->unk40, 0x2AF, 1, 3);
                    func_ovl0C_01_80049B80(list->unk24);
                } else {
                    pos = D_ovl0C_01_8004A9DC->unk40;
                    func_ovl0C_01_80049EB0(0x26, pos->unk10, pos->unk14, pos->unk18);
                    left = 1;
                }
            } else {
                left = 1;
            }
        }
    }
    ret = 0;
    if (!left && !func_ovl0C_01_80049B90(arg3)) {
        ret = 1;
        func_ovl0C_01_80049B80(arg3);
        func_ovl0C_01_80044878(arg0, arg1, saved, arg3);
    }
    return ret;
}

/* the blocks crumble (a cut scene) */
void func_ovl0C_01_80044878(UnkStruct_ovl0C_01_8004A3BC *arg0, UnkStruct_ovl0C_01_8004A2A4 *arg1, UnkStruct_ovl0C_01_8004A22C *arg2, s32 arg3) {
    s32 sparks;
    s32 task;
    UnkStruct_ovl0C_01_8004A2A4 *p;

    func_ovl0C_01_80049068();
    func_ovl0C_01_80048FA8(1);
    task = func_ovl0C_01_80049908(func_ovl0C_01_80047268, arg1, 0, 0, 0x110);
    func_ovl0C_01_800497D0(arg0->unk0);
    func_ovl0C_01_8004476C(arg1, 0x40C);
    sparks = func_ovl0C_01_80049908(func_ovl0C_01_80048458, arg2, 0, 0, 0x110);
    func_ovl0C_01_80048F28(1);
    func_ovl0C_01_80049968(task);
    func_ovl0C_01_80049968(sparks);
    func_ovl0C_01_80049980(0xB0, 0xB0);
    for (p = arg1; p->unk2 != 0; p++) {
        func_ovl0C_01_80049D58(0x10, p->unk8 - 300.0f, p->unkC + 200.0f, p->unk10, 0);
        func_ovl0C_01_80049928(0x1E);
    }
    func_ovl0C_01_80049EB0(0x42, arg1->unk8, arg1->unkC, arg1->unk10);
    for (p = arg1; p->unk2 != 0; p++) {
        func_ovl0C_01_80049908(func_ovl0C_01_80048200, p, 0, 0, 0x110);
        func_ovl0C_01_80049928(0xF);
    }
    func_ovl0C_01_80049928(0x3C);
    func_ovl0C_01_80049910(sparks);
    func_ovl0C_01_80049928(0x3C);
    func_ovl0C_01_80048F28(0);
    if (*func_ovl0C_01_80048F08() & 2) {
        func_ovl0C_01_80048FA8(1);
    }
}

/* the blocks' objects, and their tiles made solid */
void func_ovl0C_01_8004476C(UnkStruct_ovl0C_01_8004A2A4 *arg0, s32 arg1) {
    UnkStruct_ovl0C_01_8004A2A4 *p;
    UnkStructA *obj;
    s32 flag;

    for (p = arg0; p->unk2 != 0; p++) {
        obj = func_ovl0C_01_80049800(0x2B0, 0xD0, p->unk8, p->unk14, p->unk10);
        if (arg1) {
            flag = 0x01000000;
        } else if (arg1 == 0) {
            flag = 0x01000000;
        }
        func_ovl0C_01_800497B8(obj, flag);
        p->unk4 = obj;
        p->unkC = p->unk14;
        func_ovl0C_01_80048DF8(p->unk18, p->unk1A, p->unk1C, p->unk18 + 3, p->unk1C + 2, 0x11);
        func_ovl0C_01_80048DF8(p->unk18, p->unk1E, p->unk1C, p->unk18 + 3, p->unk1C + 2, 0x1F);
    }
}

void func_ovl0C_01_800446F8(s32 arg0) {
    if (D_ovl0C_01_8004A9C4 >= arg0) {
        switch (D_ovl0C_01_8004A9C4) {              /* irregular */
        case 2:
            func_ovl0C_01_800439C0();
            return;
        case 3:
            func_ovl0C_01_800444DC();
            return;
        case 4:
            func_ovl0C_01_800441D4();
            break;
        }
    }
}

void func_ovl0C_01_800444DC(void) {
    UnkStructA *sp60;
    s32 sp58;
    s32 sp54;
    UnkStructA_40 *sp50;
    UnkStructA_40 *temp_s0;
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *var_v0;
    f32 temp_fs1;

    if (D_ovl0C_01_8004A9C0 == 3) {
        func_ovl0C_01_80049000(1);
        sp60 = D_ovl0C_01_8004A5B4->unk0;
        temp_s0 = D_ovl0C_01_8004A5B4->unk0->unk40;
        if (temp_s0->unk14 < 600.0f) {
            do {
                func_ovl0C_01_80049950();
                temp_s0->unk14 += 20.0f;
            } while (temp_s0->unk14 < 600.0f);
        }
        temp_s0->unk14 = 600.0f;
        func_ovl0C_01_800494E0(temp_s0, 0x16, 0);
        func_ovl0C_01_80049EB0(0x211, temp_s0->unk10, temp_s0->unk14, temp_s0->unk18);
        var_v0 = temp_s0->unk48->unk4;
        temp_fs1 = func_ovl0C_01_800494F8(temp_s0, 0) - 0.01f;
        if (var_v0->unk4 < temp_fs1) {
            do {
                func_ovl0C_01_80049950();
                temp_v0 = temp_s0->unk48->unk4;
                temp_v0->unk4 += 1.0f;
                var_v0 = temp_s0->unk48->unk4;
            } while (var_v0->unk4 < temp_fs1);
        }
        var_v0->unk4 = temp_fs1;
        func_ovl0C_01_80049950();
        sp50 = temp_s0;
        sp54 = 0x20F;
        sp58 = 0x44;
        func_ovl0C_01_80049900(&sp50);
        func_ovl0C_01_800443A4(&temp_s0->unk10, 2700.0f, &temp_s0->unk14, 3000.0f, 0x1E);
        func_ovl0C_01_800497C0(sp60, 0x01000000);
        func_ovl0C_01_800438E8();
        D_ovl0C_01_8004A9C4 = D_ovl0C_01_8004A9C0;
        switch (D_ovl0C_01_8004A9C0) {              /* irregular */
        case 3:
            func_ovl0C_01_800436A0();
            break;
        case 4:
            func_ovl0C_01_8004333C();
            break;
        }
        func_ovl0C_01_80049000(0);
    }
}

void func_ovl0C_01_800443A4(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, s32 arg4) {
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 var_fs0;

    var_fs0 = 0.0f;
    temp_fs4 = *arg0;
    temp_fs5 = *arg2;
    if (0.0f < 90.0f) {
        temp_fs1 = arg1 - temp_fs4;
        temp_fs2 = arg3 - temp_fs5;
        do {
            *arg0 = (func_ovl0C_01_80049AB0(var_fs0) * temp_fs1) + temp_fs4;
            *arg2 = (func_ovl0C_01_80049AB0(var_fs0) * temp_fs2) + temp_fs5;
            func_ovl0C_01_80049950();
            var_fs0 += 90.0f / (f32) arg4;
        } while (var_fs0 < 90.0f);
    }
    *arg0 = arg1;
    *arg2 = arg3;
}

void func_ovl0C_01_800441D4(void) {
    UnkStructA *sp50;
    s32 sp48;
    s32 sp44;
    UnkStructA_40 *sp40;
    UnkStructA_40 *temp_s0;
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *var_v0;
    f32 temp_fs1;

    func_ovl0C_01_80049000(1);
    if (D_ovl0C_01_8004A9C0 == 4) {
        sp50 = D_ovl0C_01_8004A5B4->unk0;
        temp_s0 = D_ovl0C_01_8004A5B4->unk0->unk40;
        if (temp_s0->unk14 < 600.0f) {
            do {
                func_ovl0C_01_80049950();
                temp_s0->unk14 += 20.0f;
            } while (temp_s0->unk14 < 600.0f);
        }
        temp_s0->unk14 = 600.0f;
        func_ovl0C_01_800494E0(temp_s0, 0x16, 0);
        func_ovl0C_01_80049EB0(0x211, temp_s0->unk10, temp_s0->unk14, temp_s0->unk18);
        var_v0 = temp_s0->unk48->unk4;
        temp_fs1 = func_ovl0C_01_800494F8(temp_s0, 0) - 0.01f;
        if (var_v0->unk4 < temp_fs1) {
            do {
                func_ovl0C_01_80049950();
                temp_v0 = temp_s0->unk48->unk4;
                temp_v0->unk4 += 1.0f;
                var_v0 = temp_s0->unk48->unk4;
            } while (var_v0->unk4 < temp_fs1);
        }
        var_v0->unk4 = temp_fs1;
        func_ovl0C_01_80049950();
        sp40 = temp_s0;
        sp44 = 0x20F;
        sp48 = 0x44;
        func_ovl0C_01_80049900(&sp40);
        func_ovl0C_01_80044080(&temp_s0->unk10, 2300.0f, &temp_s0->unk14, 3000.0f, 0x1E);
        func_ovl0C_01_800497C0(sp50, 0x01000000);
        func_ovl0C_01_80049000(0);
    }
}

void func_ovl0C_01_80044080(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, s32 arg4) {
    f32 sp50;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 var_fs0;

    var_fs0 = 0.0f;
    temp_fs4 = *arg2;
    temp_fs3 = *arg0;
    sp50 = arg3 - temp_fs4;
    temp_fs5 = arg1 - temp_fs3;
    if (0.0f < 90.0f) {
        do {
            *arg0 = ((1.0f - func_ovl0C_01_80049AB8(var_fs0)) * temp_fs5) + temp_fs3;
            *arg2 = ((1.0f - func_ovl0C_01_80049AB8(var_fs0)) * sp50) + temp_fs4;
            func_ovl0C_01_80049950();
            var_fs0 += 90.0f / (f32) arg4;
        } while (var_fs0 < 90.0f);
    }
    *arg0 = arg1;
    *arg2 = arg3;
}

void func_ovl0C_01_80043E74(void) {
    UnkStruct_ovl0C_01_8004A3CC *p;
    s16 i;
    s32 hit;

    D_ovl0C_01_8004A9DC->unk30 = 4;
    D_ovl0C_01_8004A9DC->unk34 = 95.0f;
    D_ovl0C_01_8004A9DC->unk38 = 500.0f;
    for (i = 0, p = D_ovl0C_01_8004A3CC; i < 8; i++, p++) {
        if (func_ovl0C_01_80049B90(p->unk28) == 0) {
            D_ovl0C_01_8004A9DC->unk40->unk10 = p->unk8;
            D_ovl0C_01_8004A9DC->unk40->unk14 = p->unkC;
            D_ovl0C_01_8004A9DC->unk40->unk18 = p->unk10;
            hit = func_ovl0C_01_80049768(D_ovl0C_01_8004A9DC, 0xC0);
            if (hit != 0) {
                if (hit & 0x4000) {
                    func_ovl0C_01_80049DD8(p->unk2E, p->unk8, p->unkC, p->unk10);
                    func_ovl0C_01_80049D58(0xF, p->unk8, p->unkC + 100.0f, p->unk10, 0);
                    func_ovl0C_01_800497C0(p->unk0, 0x01000000);
                    func_ovl0C_01_800497D0(p->unk0);
                    func_ovl0C_01_80048E00(p->unk14, p->unk20, p->unk1C, p->unk14 + 1, p->unk18, p->unk1C + 1, 0x10);
                    func_ovl0C_01_80048DF8(p->unk14, p->unk18, p->unk1C, p->unk14 + 1, p->unk1C + 1, 0x11);
                    func_ovl0C_01_80049B80(p->unk28);
                } else {
                    func_ovl0C_01_80049EB0(0x26, D_ovl0C_01_8004A9DC->unk40->unk10, D_ovl0C_01_8004A9DC->unk40->unk14, D_ovl0C_01_8004A9DC->unk40->unk18);
                }
            }
        }
    }
}

void func_ovl0C_01_80043C20(void) {
    f32 sp2C;
    f32 sp24;
    f32 var_fv0;
    f32 var_fv1;

    switch (D_ovl0C_01_8004A9C4) {                  /* irregular */
    case 2:
        if ((func_ovl0C_01_80048F88(0x1A, 1, 0xE, 0x1B, 0x10) != 0) && (func_ovl0C_01_80043138(func_ovl0C_01_80048FF8(func_ovl0C_01_80048F98()), D_ovl0C_01_8004A5B4->unk0) != 0)) {
            func_ovl0C_01_80043BC0();
        }
        break;
    case 3:
        if (func_ovl0C_01_80048F88(0x10, 1, 0x18, 0x11, 0x1A) != 0) {
            if (func_ovl0C_01_80043138(func_ovl0C_01_80048FF8(func_ovl0C_01_80048F98()), D_ovl0C_01_8004A5B4->unk0) != 0) {
                func_ovl0C_01_80049520(0x35A, 4);
            }
        }
        break;
    case 4:
        sp2C = 10.0f;
        sp24 = 12.0f;
        var_fv0 = 10.0f;
        var_fv1 = 12.0f;
        if (func_ovl0C_01_80049B90(0x42A) != 0) {
            var_fv0 = 10.0f + 8.0f;
            var_fv1 = 12.0f + 8.0f;
        }
        if (func_ovl0C_01_80048F88((s32) 32.0f, (s32) 2.0f, (s32) var_fv0, (s32) 33.0f, (s32) var_fv1) != 0) {
            if (func_ovl0C_01_80043138(func_ovl0C_01_80048FF8(func_ovl0C_01_80048F98()), D_ovl0C_01_8004A5B4->unk0) != 0) {
                func_ovl0C_01_80049520(0x35B, 8);
            }
        }
        break;
    }
}

void func_ovl0C_01_80043BC0(void) {
    func_ovl0C_01_80049000(1);
    if (func_ovl0C_01_80048F08()[0x12] == 0) {
        func_ovl0C_01_80049520(0x359, 6);
    } else {
        func_ovl0C_01_80049520(0x364, 6);
    }
    func_ovl0C_01_800439C0();
    func_ovl0C_01_80049000(0);
}

void func_ovl0C_01_800439C0(void) {
    UnkStructA *sp58;
    s32 sp50;
    s32 sp4C;
    UnkStructA_40 *sp48;
    UnkStructA_40 *temp_s0;
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *var_v0;
    f32 temp_fs1;

    func_ovl0C_01_80049000(1);
    sp58 = D_ovl0C_01_8004A5B4->unk0;
    temp_s0 = D_ovl0C_01_8004A5B4->unk0->unk40;
    if (temp_s0->unk14 < 700.0f) {
        do {
            func_ovl0C_01_80049950();
            temp_s0->unk14 += 20.0f;
        } while (temp_s0->unk14 < 700.0f);
    }
    temp_s0->unk14 = 700.0f;
    func_ovl0C_01_800494E0(temp_s0, 0x16, 0);
    func_ovl0C_01_80049EB0(0x211, temp_s0->unk10, temp_s0->unk14, temp_s0->unk18);
    var_v0 = temp_s0->unk48->unk4;
    temp_fs1 = func_ovl0C_01_800494F8(temp_s0, 0) - 0.01f;
    if (var_v0->unk4 < temp_fs1) {
        do {
            func_ovl0C_01_80049950();
            temp_v0 = temp_s0->unk48->unk4;
            temp_v0->unk4 += 1.0f;
            var_v0 = temp_s0->unk48->unk4;
        } while (var_v0->unk4 < temp_fs1);
    }
    var_v0->unk4 = temp_fs1;
    func_ovl0C_01_80049950();
    sp48 = temp_s0;
    sp4C = 0x20F;
    sp50 = 0x44;
    func_ovl0C_01_80049900(&sp48);
    func_ovl0C_01_80043248(&temp_s0->unk10, 1400.0f, 0x1E);
    func_ovl0C_01_800497C0(sp58, 0x01000000);
    func_ovl0C_01_80049B80(0x412);
    func_ovl0C_01_800438E8();
    D_ovl0C_01_8004A9C4 = D_ovl0C_01_8004A9C0;
    switch (D_ovl0C_01_8004A9C0) {                  /* irregular */
    case 3:
        func_ovl0C_01_800436A0();
        break;
    case 4:
        func_ovl0C_01_8004333C();
        break;
    }
    func_ovl0C_01_80049000(0);
}

void func_ovl0C_01_800438E8(void) {
    s32 *sp24;
    s32 *temp_v0;

    D_ovl0C_01_8004A9C0 = 0;
    temp_v0 = func_ovl0C_01_80049BA0();
    if (D_ovl0C_01_8004A9C8.unk0 == 0) {
        sp24 = temp_v0;
        if ((func_ovl0C_01_80049B90(0x411) == 0) && (*sp24 == 0)) {
            D_ovl0C_01_8004A9C0 = 1;
            return;
        }
    }
    if (func_ovl0C_01_80049B90(0x412) == 0) {
        D_ovl0C_01_8004A9C0 = 2;
        return;
    }
    if (func_ovl0C_01_80049B90(0x40F) == 0) {
        D_ovl0C_01_8004A9C0 = 3;
        return;
    }
    if (func_ovl0C_01_80049B90(0x40C) == 0) {
        D_ovl0C_01_8004A9C0 = 4;
        return;
    }
    if (func_ovl0C_01_80049B90(0x415) == 0) {
        D_ovl0C_01_8004A9C0 = 5;
        return;
    }
    D_ovl0C_01_8004A9C0 = 6;
}

void func_ovl0C_01_80043894(void) {
    switch (D_ovl0C_01_8004A9C0) {                  /* irregular */
    case 3:
        func_ovl0C_01_800436A0();
        return;
    case 4:
        func_ovl0C_01_8004333C();
        return;
    }
}

void func_ovl0C_01_800436A0(void) {
    UnkStructA *sp44;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    UnkStructA *temp_a0;
    UnkStructA_40 *temp_s0;
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *var_v0;

    func_ovl0C_01_80049000(1);
    temp_a0 = D_ovl0C_01_8004A5B4->unk0;
    temp_s0 = temp_a0->unk40;
    temp_s0->unk20 = 90.0f;
    temp_s0->unk10 = 1000.0f;
    temp_s0->unk14 = 800.0f;
    temp_s0->unk18 = 2500.0f;
    sp44 = temp_a0;
    func_ovl0C_01_80049950();
    func_ovl0C_01_800497B8(temp_a0, 0x01000000);
    func_ovl0C_01_800435C4(&temp_s0->unk10, 1600.0f, 0x1E);
    func_ovl0C_01_800494E0(temp_s0, 0x16, 0);
    temp_s0->unk48->unk4->unk4 = func_ovl0C_01_800494F8(temp_s0, 0) - 0.01f;
    var_v0 = temp_s0->unk48->unk4;
    if (var_v0->unk4 > 1.0f) {
        do {
            func_ovl0C_01_80049950();
            temp_v0 = temp_s0->unk48->unk4;
            temp_v0->unk4 -= 1.0f;
            var_v0 = temp_s0->unk48->unk4;
        } while (var_v0->unk4 > 1.0f);
    }
    var_v0->unk4 = 0.0f;
    if (temp_s0->unk14 > 200.0f) {
        do {
            func_ovl0C_01_80049950();
            temp_s0->unk14 -= 20.0f;
        } while (temp_s0->unk14 > 200.0f);
    }
    temp_s0->unk14 = 200.0f;
    sp34 = temp_s0->unk10;
    sp38 = temp_s0->unk14;
    sp3C = temp_s0->unk18;
    func_ovl0C_01_80049DA8(&sp34);
    func_ovl0C_01_80049E88(&sp34);
    func_ovl0C_01_80049000(0);
}

void func_ovl0C_01_800435C4(f32 *arg0, f32 arg1, s32 arg2) {
    f32 temp_fs1;
    f32 temp_fs2;
    f32 var_fs0;

    var_fs0 = 0.0f;
    temp_fs1 = *arg0;
    if (0.0f < 90.0f) {
        temp_fs2 = arg1 - temp_fs1;
        do {
            *arg0 = (func_ovl0C_01_80049AB0(var_fs0) * temp_fs2) + temp_fs1;
            func_ovl0C_01_80049950();
            var_fs0 += 90.0f / (f32) arg2;
        } while (var_fs0 < 90.0f);
    }
    *arg0 = arg1;
}

void func_ovl0C_01_8004333C(void) {
    UnkStructA *sp44;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    UnkStructA *temp_a2;
    UnkStructA_40 *temp_s0;
    UnkStructA_40_48_4 *temp_v0;
    UnkStructA_40_48_4 *var_v0;

    func_ovl0C_01_80049000(1);
    temp_a2 = D_ovl0C_01_8004A5B4->unk0;
    temp_s0 = temp_a2->unk40;
    temp_s0->unk20 = 270.0f;
    temp_s0->unk10 = 4000.0f;
    temp_s0->unk14 = 800.0f;
    if ((D_ovl0C_01_8004A980[0] > 3100.0f) && (D_ovl0C_01_8004A980[0] < 3300.0f) && (D_ovl0C_01_8004A980[2] > 1000.0f) && (D_ovl0C_01_8004A980[2] < 1200.0f)) {
        sp44 = temp_a2;
        func_ovl0C_01_80049B80(0x42A);
        temp_s0->unk18 = 1900.0f;
    } else {
        temp_s0->unk18 = 1100.0f;
    }
    sp44 = temp_a2;
    func_ovl0C_01_80049950();
    func_ovl0C_01_800497B8(sp44, 0x01000000);
    func_ovl0C_01_80043248(&temp_s0->unk10, 3300.0f, 0x1E);
    func_ovl0C_01_800494E0(temp_s0, 0x16, 0);
    temp_s0->unk48->unk4->unk4 = func_ovl0C_01_800494F8(temp_s0, 0) - 0.01f;
    var_v0 = temp_s0->unk48->unk4;
    if (var_v0->unk4 > 1.0f) {
        do {
            func_ovl0C_01_80049950();
            temp_v0 = temp_s0->unk48->unk4;
            temp_v0->unk4 -= 1.0f;
            var_v0 = temp_s0->unk48->unk4;
        } while (var_v0->unk4 > 1.0f);
    }
    var_v0->unk4 = 0.0f;
    if (temp_s0->unk14 > 300.0f) {
        do {
            func_ovl0C_01_80049950();
            temp_s0->unk14 -= 20.0f;
        } while (temp_s0->unk14 > 300.0f);
    }
    temp_s0->unk14 = 300.0f;
    sp34 = temp_s0->unk10;
    sp38 = temp_s0->unk14;
    sp3C = temp_s0->unk18;
    func_ovl0C_01_80049DA8(&sp34);
    func_ovl0C_01_80049E88(&sp34);
    func_ovl0C_01_80049000(0);
}

void func_ovl0C_01_80043248(f32 *arg0, f32 arg1, s32 arg2) {
    f32 temp_fs1;
    f32 temp_fs2;
    f32 var_fs0;

    var_fs0 = 0.0f;
    temp_fs1 = *arg0;
    temp_fs2 = arg1 - temp_fs1;
    if (0.0f < 90.0f) {
        do {
            *arg0 = ((1.0f - func_ovl0C_01_80049AB8(var_fs0)) * temp_fs2) + temp_fs1;
            func_ovl0C_01_80049950();
            var_fs0 += 90.0f / (f32) arg2;
        } while (var_fs0 < 90.0f);
    }
    *arg0 = arg1;
}

/* whether the player (arg0) faces arg1: probes 50 units ahead with the
 * shared probe object */
s32 func_ovl0C_01_80043138(UnkStructA *arg0, UnkStructA *arg1) {
    f32 dz;
    f32 dx;

    func_ovl0C_01_800430F0();
    dx = func_ovl0C_01_80049AB0(arg0->unk40->unk20) * 50.0f;
    dz = func_ovl0C_01_80049AB8(arg0->unk40->unk20);
    D_ovl0C_01_8004A9DC->unk30 = 1;
    D_ovl0C_01_8004A9DC->unk34 = 30.0f;
    D_ovl0C_01_8004A9DC->unk38 = 50.0f;
    D_ovl0C_01_8004A9DC->unk40->unk10 = arg0->unk40->unk10 + dx;
    D_ovl0C_01_8004A9DC->unk40->unk14 = arg0->unk40->unk14;
    D_ovl0C_01_8004A9DC->unk40->unk18 = arg0->unk40->unk18 + dz * 50;
    if (func_ovl0C_01_80049848(D_ovl0C_01_8004A9DC, 0x10) != arg1) {
        return 0;
    }
    return 1;
}

void func_ovl0C_01_800430F0(void) {
    if (func_ovl0C_01_80049B90(0x400) == 0) {
        D_ovl0C_01_8004A9DC = func_ovl0C_01_800497E0(-1, 0, 0x20, 0);
        func_ovl0C_01_80049B80(0x400);
    }
}

void func_ovl0C_01_800430D0(void) {
    func_ovl0C_01_80049000(1);
}

void func_ovl0C_01_800430B0(void) {
    func_ovl0C_01_80049000(1);
}

void func_ovl0C_01_80043058(void) {
    s32 temp_v0;

    temp_v0 = D_ovl0C_01_8004A9C8.unk0;
    if (temp_v0 == 8) {
        func_ovl0C_01_8004A010();
    }
    if (temp_v0 == 9) {
        func_ovl0C_01_8004A010();
    }
    func_ovl0C_01_80049B88(0x42A);
}

void func_ovl0C_01_80043038(void) {
    func_ovl0C_01_8004A010();
}

void func_ovl0C_01_80043018(void) {
    func_ovl0C_01_8004A010();
}

void func_ovl0C_01_80043010(void) {

}
