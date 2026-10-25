/*
 * NON_MATCHING: ovl_0F_10's game object, complete: every function and its data
 * (.data and .rodata as the original; .bss 0x60 with its unused words common).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 826, eu 828, jp 826
 *
 * Every function is in the original's place, stubs included (the inlined
 * statics are named for the stubs they leave). What still differs in us
 * (words):
 * - func_ovl0F_10_80043430 (430): case 2's
 *   `D_ovl0F_10_80046AE0[1]->unk40->unk14 += 3200.0f` keeps a load-delay
 *   nop and its store before the `jal` of func_ovl0F_10_80046190 in the
 *   original (ours moves the store into the delay slot), so ours is one
 *   word short and the rest shifts; the frame's spill slots also sit 16
 *   bytes lower and the inlined func_ovl0F_10_80043344's local 8 higher.
 * - func_ovl0F_10_80044074 (252): ovl_0F_07's 80043A58 family. The
 *   original masks unk64's speed first (into a1), the flags second, and
 *   leaves one word less in the side-flag if/else; ours the other way,
 *   which renames every temporary after. The unused 0x5C bytes of its
 *   frame are `pad0`/`pad` (a guess: inlined statics' slots).
 * - func_ovl0F_10_80044B8C (97): ovl_0F_07's 80044208, same miss (the
 *   `move s1,v0` before `mtc1 zero,$f12`).
 * - func_ovl0F_10_80043CCC (29): s0 and s1 swapped (the counter and
 *   &D_ovl0F_10_800468B0), `i = 0` before the branch, and the original's
 *   six nops after its endless loop. (Tried, no gain: while/do/for forms,
 *   `i != 90`, u8/s16/u32 counters, a float pointer, pads, `i = 0` before
 *   the `if`: the counter stays in s1.)
 * - func_ovl0F_10_800448A0 (18): the original's extra nop after its
 *   endless loop; `pad[1]` gives its frame's unused word.
 */
#include "common.h"

/*
 * ovl_0F_10's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). ovl_0F_07 (1FCAC0) and
 * ovl_0F_08 (1FF8F0) share most of its helpers. The statics IDO inlines
 * everywhere are named for the empty stubs they leave.
 */

/* a model the stage places: four in D_ovl0F_10_8004672C, two in
 * D_ovl0F_10_800467DC */
typedef struct {
    /* 0x00 */ UnkStructA **unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
} UnkStruct_ovl0F_10_8004672C; /* size 0x2C */

/* seven arguments of func_ovl0F_10_800455B8 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_ovl0F_10_800468C0; /* size 0x1C */

/* the task func_ovl0F_10_80044B8C runs as: its argument at 0x2C */
typedef struct {
    /* 0x00 */ u8 unk0[0x2C];
    /* 0x2C */ UnkStructA **unk2C;
} UnkStruct_ovl0F_10_80045F30;

void func_ovl0F_10_800453B8(s32);
void func_ovl0F_10_800453D0(s32);
void func_ovl0F_10_80045418(f32, f32, f32, f32 *, s32);
void func_ovl0F_10_80045440(UnkStructA_40 *, f32 *, f32 *);
void func_ovl0F_10_80045498(void (*)(UnkStructA *), s32);
void func_ovl0F_10_800454A0(void (*)(UnkStructA *));
void func_ovl0F_10_800454B0(s32, s32, s32);
s32 func_ovl0F_10_800454B8(void);
s32 *func_ovl0F_10_80045508(void);
void func_ovl0F_10_80045520(s32);
void func_ovl0F_10_80045528(s32);
void func_ovl0F_10_80045568(void);
void func_ovl0F_10_80045570(s32, s32, s32);
void func_ovl0F_10_80045578(Vec3f *);
s32 func_ovl0F_10_80045580(s32, s32, s32, s32);
s32 func_ovl0F_10_80045588(s32, s32, s32, s32, s32);
s32 func_ovl0F_10_80045598(void);
void func_ovl0F_10_800455A0(s32, void *);
void func_ovl0F_10_800455A8(s32);
void func_ovl0F_10_800455B0(s32);
void func_ovl0F_10_800455B8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl0F_10_800455C0(char *);
void func_ovl0F_10_800455C8(void);
void func_ovl0F_10_800455D0(s32);
void func_ovl0F_10_800455E0(s32);
UnkStructA *func_ovl0F_10_800455F8(s32);
void func_ovl0F_10_80045600(s32);
UnkStructA *func_ovl0F_10_80045638(s32);
void func_ovl0F_10_80045648(s32, s32);
void func_ovl0F_10_80045658(s32);
void func_ovl0F_10_80045AB0(UnkStructA_40 *, s32);
void func_ovl0F_10_80045B20(s32, s32);
void func_ovl0F_10_80045BF8(f32, f32, f32);
void func_ovl0F_10_80045C18(f32, f32, f32);
void func_ovl0F_10_80045C20(f32 *, f32 *, f32 *);
void func_ovl0F_10_80045C58(s32);
void func_ovl0F_10_80045C60(s32);
void func_ovl0F_10_80045C80(f32);
void func_ovl0F_10_80045C88(f32);
void func_ovl0F_10_80045CA0(f32);
void func_ovl0F_10_80045CB0(f32, f32);
s32 func_ovl0F_10_80045D68(UnkStructA *, s32);
void func_ovl0F_10_80045DB8(UnkStructA *, s32);
void func_ovl0F_10_80045DC0(UnkStructA *, s32);
s32 func_ovl0F_10_80045DD0(UnkStructA *);
UnkStructA *func_ovl0F_10_80045DE0(s32, s32, s32, s32);
UnkStructA *func_ovl0F_10_80045E28(s32, s32);
void func_ovl0F_10_80045E38(UnkStructA *);
void func_ovl0F_10_80045E98(f32);
void func_ovl0F_10_80045EA0(s32);
s32 func_ovl0F_10_80045ED8(UnkStructA *, s32, UnkStructA *);
s32 func_ovl0F_10_80045F08(void (*)(void), void *, s32, s32, s32);
void func_ovl0F_10_80045F10(s32);
void func_ovl0F_10_80045F18(void);
void func_ovl0F_10_80045F28(s32);
void *func_ovl0F_10_80045F30(void);
void func_ovl0F_10_80045F50(void);
UnkStructC *func_ovl0F_10_80045F90(s32);
void func_ovl0F_10_80045FA0(UnkStructC *, s32);
s32 func_ovl0F_10_80046170(s32);
void func_ovl0F_10_80046180(s32);
s32 func_ovl0F_10_80046190(s32);
void func_ovl0F_10_80046270(u32 (*)[3]);
void func_ovl0F_10_80046358(s32, f32, f32, f32, s32);
void func_ovl0F_10_80046368(s32);
void func_ovl0F_10_80046398(void);
void func_ovl0F_10_80046408(UnkStructA *, s32, f32);
void func_ovl0F_10_80046418(s32, s32, s32);
void func_ovl0F_10_80046438(s32);
void func_ovl0F_10_80046478(void);
void func_ovl0F_10_80046490(s32);
void func_ovl0F_10_800464B0(s32, f32, f32, f32);
void func_ovl0F_10_80046608(void);
void func_ovl0F_10_80046610(void);

void func_ovl0F_10_80043344(f32);
void func_ovl0F_10_80043430(s32);
void func_ovl0F_10_80043CCC(void);
void func_ovl0F_10_80043E08(void);
void func_ovl0F_10_80044074(UnkStructA *);
void func_ovl0F_10_80044780(UnkStructA *);
void func_ovl0F_10_800448A0(void);
void func_ovl0F_10_80044AD4(void);
void func_ovl0F_10_80044B8C(void);
void func_ovl0F_10_80044D3C(void);
void func_ovl0F_10_80044F40(s32, UnkStructA *);
void func_ovl0F_10_80044F74(f32, f32, f32);
void func_ovl0F_10_80044FD0(void);
void func_ovl0F_10_80044FE8(void);

static s32 func_ovl0F_10_80043010(s32);
static void func_ovl0F_10_80043088(UnkStruct_ovl0F_10_8004672C *);
static void func_ovl0F_10_8004310C(UnkStruct_ovl0F_10_8004672C *, s32);
static void func_ovl0F_10_800431BC(UnkStruct_ovl0F_10_8004672C *, s32);
static void func_ovl0F_10_800432E0(s32 *);
static void func_ovl0F_10_8004338C(s32);
static void func_ovl0F_10_80043FAC(f32, f32 *, s32 *);
static void func_ovl0F_10_8004406C(void);
static void func_ovl0F_10_80044064(UnkStructA *);
static void func_ovl0F_10_8004405C(UnkStructA *, f32 *);
static void func_ovl0F_10_80044054(UnkStructA *, s32, f32);
static s32 func_ovl0F_10_80043FA4(UnkStructA *);
static void func_ovl0F_10_80043F9C(UnkStructA *, f32 *);
static void func_ovl0F_10_80043F94(s32 *, s32, f32);
static void func_ovl0F_10_80044B7C(UnkStruct_ovl0F_10_80045F30 *, UnkStructA *);
static void func_ovl0F_10_80044B84(void);

/* .bss */
UnkStructA *D_ovl0F_10_80046AE0[6];
f32 D_ovl0F_10_80046AF8[3];
s32 D_ovl0F_10_80046B04;
Vec3f D_ovl0F_10_80046B08;
s32 D_ovl0F_10_80046B14;
u8 D_ovl0F_10_80046B18[0x4];
s32 D_ovl0F_10_80046B1C;
s32 D_ovl0F_10_80046B20;
u8 D_ovl0F_10_80046B24[0x4];
Vec3f D_ovl0F_10_80046B28;
UnkStructC *D_ovl0F_10_80046B34;
u8 D_ovl0F_10_80046B38[0x8];

/* .data */
s32 D_ovl0F_10_800466B0 = 0;
s32 D_ovl0F_10_800466B4 = 0;
s32 D_ovl0F_10_800466B8 = 0;
s32 D_ovl0F_10_800466BC = -1;
u8 D_ovl0F_10_800466C0[4] = { 0 };
extern UnkStruct_ovl0F_10_8004672C D_ovl0F_10_8004672C[4];
extern UnkStruct_ovl0F_10_8004672C D_ovl0F_10_800467DC[2];
extern s32 D_ovl0F_10_800466C8;
extern s32 D_ovl0F_10_800466CC;
extern s32 D_ovl0F_10_800466D0;
extern s32 D_ovl0F_10_800466D4;
extern s32 D_ovl0F_10_800468A4;
extern s32 D_ovl0F_10_800468A8;
extern s32 D_ovl0F_10_800468AC;
extern f32 D_ovl0F_10_800468B0;
extern s32 D_ovl0F_10_800468B4;
extern UnkStructA *D_ovl0F_10_800468B8;
extern s32 D_ovl0F_10_800468BC;
extern UnkStruct_ovl0F_10_800468C0 D_ovl0F_10_800468C0;

/* unused: the stubs IDO -O3 leaves at the end of the object */
/* A second caller keeps func_ovl0F_10_80043088 from being inlined. */
static void func_ovl0F_10_80045068(void) {
    func_ovl0F_10_80043088(D_ovl0F_10_8004672C);
}

static void func_ovl0F_10_80045060(void) {
}

static void func_ovl0F_10_80045058(void) {
}

static void func_ovl0F_10_80045050(void) {
}

static void func_ovl0F_10_80045048(void) {
}

static void func_ovl0F_10_80045040(void) {
}

static void func_ovl0F_10_80045038(void) {
}

static void func_ovl0F_10_80045030(void) {
}

static void func_ovl0F_10_80045028(void) {
}

static void func_ovl0F_10_80045020(void) {
}

static void func_ovl0F_10_80045018(void) {
}

static void func_ovl0F_10_80045010(void) {
}

static void func_ovl0F_10_80045008(void) {
}

static void func_ovl0F_10_80045000(void) {
}

static void func_ovl0F_10_80044FF8(void) {
}

static void func_ovl0F_10_80044FF0(void) {
}

void func_ovl0F_10_80044FE8(void) {
}

void func_ovl0F_10_80044FD0(void) {
    D_ovl0F_10_80046B1C = -1;
    D_ovl0F_10_80046B20 = -1;
}

void func_ovl0F_10_80044F74(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl0F_10_80045BF8(D_ovl0F_10_80046B28.x, D_ovl0F_10_80046B28.y, D_ovl0F_10_80046B28.z);
    func_ovl0F_10_80045C18(arg0, arg1, arg2);
    func_ovl0F_10_80045F28(180);
}

void func_ovl0F_10_80044F40(s32 arg0, UnkStructA *arg1) {
    UnkStructA_40 *p;

    p = arg1->unk40;
    func_ovl0F_10_800464B0(arg0, p->unk10, p->unk14, p->unk18);
}

void func_ovl0F_10_80044D3C(void) {
    s32 dir;
    UnkStructA *obj;
    f32 angle;
    f32 step;
    f32 i;

    dir = (s32)func_ovl0F_10_80045F30();
    obj = func_ovl0F_10_800455F8(func_ovl0F_10_80045598());
    D_ovl0F_10_800466B4 = 1;
    angle = 0.0f;
    i = 0.0f;
    func_ovl0F_10_80045C20(NULL, &angle, NULL);
    func_ovl0F_10_80045600(1);
    func_ovl0F_10_80045528(1);
    func_ovl0F_10_80045520(0);
    func_ovl0F_10_80045C60(0x7F);
    if (dir == 0) {
        step = -((angle > 180.0f ? 360.0f - angle : angle) / 50.0f);
    } else {
        step = (angle > 180.0f ? 360.0f - angle : angle) / 50.0f;
    }
    step *= 1.1f;
    while (i < 100.0f) {
        func_ovl0F_10_80045BF8(obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18);
        func_ovl0F_10_80045C18(32768.0f, -angle, 32768.0f);
        i += 1.0f;
        angle += step;
        func_ovl0F_10_80045F50();
    }
    func_ovl0F_10_80045528(0);
    func_ovl0F_10_80045600(0);
    func_ovl0F_10_80045520(1);
    func_ovl0F_10_80045C58(0x1F);
    D_ovl0F_10_800466B4 = 0;
    func_ovl0F_10_80045F18();
}

void func_ovl0F_10_80044B8C(void) {
    UnkStruct_ovl0F_10_80045F30 *task;
    UnkStructA *obj;

    task = func_ovl0F_10_80045F30();
    obj = func_ovl0F_10_800455F8(func_ovl0F_10_80045598());
    func_ovl0F_10_80044B84();
    func_ovl0F_10_80044B7C(task, obj);
    func_ovl0F_10_80045F18();
}

static void func_ovl0F_10_80044B7C(UnkStruct_ovl0F_10_80045F30 *task, UnkStructA *obj) {
    static s32 D_ovl0F_10_800466C4 = 0;

    while (D_ovl0F_10_800466C4 < 400) {
        (*task->unk2C)->unk40->unk14 += 3.75f;
        (*task->unk2C)->unk40->unk18 -= 3.75f;
        obj->unk40->unk14 += 3.75f;
        D_ovl0F_10_800466C4++;
        func_ovl0F_10_80045F50();
    }
}

static void func_ovl0F_10_80044B84(void) {
    func_ovl0F_10_80045E98(0.0f);
    func_ovl0F_10_80045EA0(0x7F);
    if (D_ovl0F_10_800466BC != -1) {
        func_ovl0F_10_80046368(D_ovl0F_10_800466BC);
    }
    func_ovl0F_10_80045F28(250);
    func_ovl0F_10_800455D0(1);
    func_ovl0F_10_80045600(1);
    func_ovl0F_10_80045C80(30.0f);
    func_ovl0F_10_80045C88(1.0f);
    func_ovl0F_10_80045CA0(10.0f);
    func_ovl0F_10_800455B8(D_ovl0F_10_800468C0.unk0, D_ovl0F_10_800468C0.unk4, D_ovl0F_10_800468C0.unk8,
                           D_ovl0F_10_800468C0.unkC, D_ovl0F_10_800468C0.unk10, D_ovl0F_10_800468C0.unk14,
                           D_ovl0F_10_800468C0.unk18);
    func_ovl0F_10_80046490(0x8E);
}

/* .data after func_ovl0F_10_80044B7C's static */
s32 D_ovl0F_10_800466C8 = 0;
s32 D_ovl0F_10_800466CC = 0;
s32 D_ovl0F_10_800466D0 = 0;
s32 D_ovl0F_10_800466D4 = 0;
/* passed to func_ovl0F_10_80046270: three 12-byte records */
u32 D_ovl0F_10_800466D8[][3] = {
    { 0x25D0001, 0xE, 4 },
    { 0, 0, 4 },
    { 0, 0, 4 },
};
/* four 12-byte records, each passed to func_ovl0F_10_80046418 */
u32 D_ovl0F_10_800466FC[][3] = {
    { 0, 0x14, 0xF2 },
    { 1, 0x16, 0xF4 },
    { 2, 0x12, 0xF0 },
    { 3, 0x15, 0xF3 },
};
UnkStruct_ovl0F_10_8004672C D_ovl0F_10_8004672C[4] = {
    { &D_ovl0F_10_80046AE0[0], 0x234, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0x80000, 0 },
    { &D_ovl0F_10_80046AE0[1], 0x22F, 0, 63.0f, 0.0f, 25.0f, 0.0f, -90.0f, 0.0f, 0, 0 },
    { &D_ovl0F_10_80046AE0[2], 0x235, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { &D_ovl0F_10_80046AE0[3], 0x22E, 0, 63.0f, 5.0f, 25.0f, 0.0f, -90.0f, 0.0f, 0, 0 },
};
UnkStruct_ovl0F_10_8004672C D_ovl0F_10_800467DC[2] = {
    { &D_ovl0F_10_80046AE0[4], 0x1B3, 0, 11.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0, 0x405 },
    { &D_ovl0F_10_80046AE0[5], 0x262, 0, 22.0f, 5.0f, 7.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};
/* func_ovl0F_10_800432E0's: four arguments to test, three to pass on */
s32 D_ovl0F_10_80046834[7] = { 0x2D, 0x1D, 0x2D, 0x1E, 0x5F, 0x14, 0 };
s32 D_ovl0F_10_80046850[7] = { 0xA, 0x1E, 0xA, 0x1E, 0x60, 0x14, 0 };
UnkStruct_ovl0F_10_800468C0 D_ovl0F_10_8004686C[2] = {
    { 0, 3, 8.5f, 2, 0, 1, 0 },
    { 0, 3, 8.5f, 2, 0, 1, 0 },
};
s32 D_ovl0F_10_800468A4 = 0;
s32 D_ovl0F_10_800468A8 = 0;
s32 D_ovl0F_10_800468AC = 0;
f32 D_ovl0F_10_800468B0 = 0.0f;
s32 D_ovl0F_10_800468B4 = 0;
UnkStructA *D_ovl0F_10_800468B8 = NULL;
s32 D_ovl0F_10_800468BC = -1;
UnkStruct_ovl0F_10_800468C0 D_ovl0F_10_800468C0 = { 0, 3, 3.75f, 15, 0, 0, 0 };
/* the camera scripts func_ovl0F_10_80043E08 passes to func_ovl0F_10_800455C0 */
char D_ovl0F_10_800468DC[] = "WM1 WG1 WSL WAP WDN WB3 WDNE WB1 WDN WB2";
char D_ovl0F_10_80046908[] = "M9 ST90";
char D_ovl0F_10_80046910[] = "WM1 WG1 WSH WAP WDN WB12 WDNW WB7 WDW WB8 WDNW WB3 WDW WB4";
char D_ovl0F_10_8004694C[] = "WM1 WG1 WSL WAP WDSW WB0 ST80";
char D_ovl0F_10_8004696C[] = "M8 ST80";
char D_ovl0F_10_80046974[] = "M7 ST120 WM1 WG1 WSH WAP WDSW WB1";
char D_ovl0F_10_80046998[] = "WM1 WG1 WSL WAP WDSE WB1 WDS WB0 ST60";

/* a task: the trembling flight to the end of the stage */
void func_ovl0F_10_80044AD4(void) {
    UnkStructA *obj;
    s32 i;

    obj = func_ovl0F_10_80045F30();
    for (i = 0; i < 5; i++) {
        func_ovl0F_10_80046358(0x19, obj->unk40->unk10, obj->unk40->unk14, obj->unk40->unk18, 0);
        if (D_ovl0F_10_800466C8 == 1) {
            func_ovl0F_10_80046490(0x27);
        }
        func_ovl0F_10_80045F28(20);
    }
    func_ovl0F_10_80045F18();
}

void func_ovl0F_10_800448A0(void) {
    s32 pad[1];
    f32 x;
    f32 y;
    f32 z;
    f32 rx;
    f32 ry;
    f32 rz;
    s32 i;

    x = 2898.7f;
    y = 3582.5f;
    z = 1940.3f;
    rx = 247.7f;
    ry = 1.7f;
    rz = 344.0f;
    for (i = 0; i < 300; i++) {
        x += -2.7783334f;
        z += -1.1396668f;
        func_ovl0F_10_80045BF8(x, 32768.0f, z);
        func_ovl0F_10_80045F50();
    }
    func_ovl0F_10_80045F28(110);
    for (i = 0; i < 500; i++) {
        rx += 0.18460001f;
        func_ovl0F_10_80045C18(rx, 32768.0f, 32768.0f);
        func_ovl0F_10_80045F50();
    }
    func_ovl0F_10_80045F28(120);
    for (i = 0; i < 180; i++) {
        x += 2.7854452f;
        y += -5.2938886f;
        z += -9.473778f;
        ry += 0.14222221f;
        rz += 14.183333f;
        func_ovl0F_10_80045BF8(x, y, z);
        func_ovl0F_10_80045C18(32768.0f, ry, rz);
        func_ovl0F_10_80045F50();
    }
    func_ovl0F_10_80045F28(360);
    for (i = 0; i < 600; i++) {
        rx += -0.33816665f;
        ry += -0.0068333307f;
        rz += 2.8933334f;
        func_ovl0F_10_80045C18(rx, ry, rz);
        func_ovl0F_10_80045F50();
    }
    while (1) {
        func_ovl0F_10_80045F28(100);
    }
}

void func_ovl0F_10_80044780(UnkStructA *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl0F_10_80045C60(0x10);
    }
    dx = arg0->unk40->unk28 / 30.0f;
    dy = arg0->unk40->unk2C / 30.0f;
    dz = arg0->unk40->unk30 / 30.0f;
    func_ovl0F_10_80045DC0(arg0, 0x02000000);
    for (i = 0; i < 30; i++) {
        arg0->unk40->unk28 -= dx;
        arg0->unk40->unk2C -= dy;
        arg0->unk40->unk30 -= dz;
        func_ovl0F_10_80045E38(arg0);
        func_ovl0F_10_80045F50();
    }
    func_ovl0F_10_80045DC0(arg0, 0x01000000);
}

void func_ovl0F_10_80044074(UnkStructA *arg0) {
    s32 pad0[1];
    s32 flags;
    f32 speed;
    f32 dist;
    f32 angle;
    f32 pos[3];
    s32 pad[22];
    s32 v;

    func_ovl0F_10_8004406C();
    v = arg0->unk64;
    flags = v & 0xF0000000;
    speed = (v & 0x0FFFFFFF) * 0.01;
    dist = 0.0f;
    angle = 0.0f;
    if (arg0->unk8 & 0x20000) {
        return;
    }
    func_ovl0F_10_80044064(arg0);
    func_ovl0F_10_8004405C(arg0, pos);
    func_ovl0F_10_80045440(arg0->unk40, &dist, &angle);
    switch ((s32)angle) {
        case 270:
        if (flags == 0) {
            flags = 0x30000000;
            if (D_ovl0F_10_800466D4 == 0) {
                D_ovl0F_10_800466D4 = 10;
                func_ovl0F_10_80045F08(func_ovl0F_10_80044AD4, arg0, 0, 0, 0x110);
            }
        }
        if (flags == 0x30000000) {
            if (arg0->unk40->unk10 <= arg0->unk58) {
                speed += (dist < 50.0f) ? 0.1f : 0.16f;
                if (25.0f < speed) {
                    speed = 25.0f;
                }
                speed += (arg0->unk58 - arg0->unk40->unk10) * 0.01f;
                if (25.0f < speed) {
                    speed = 25.0f;
                }
            } else {
                arg0->unk40->unk14 -= (arg0->unk40->unk14 - arg0->unk5C) * 0.8f;
                arg0->unk40->unk10 -= (arg0->unk40->unk10 - arg0->unk58) * 0.8f;
                speed += (dist < 50.0f) ? 0.1f : 0.16f;
                if (25.0f < speed) {
                    speed = 25.0f;
                }
            }
            if (D_ovl0F_10_800466C8 == 1 && D_ovl0F_10_800466CC == 0) {
                func_ovl0F_10_80046490(0x32);
                D_ovl0F_10_800466CC = 20;
            }
        } else if (flags == 0x40000000) {
            func_ovl0F_10_80043FAC(dist + 100.0f, &speed, &flags);
        }
            break;
        case 90:
        if (flags == 0) {
            flags = 0x40000000;
            if (D_ovl0F_10_800466D4 == 0) {
                D_ovl0F_10_800466D4 = 10;
                func_ovl0F_10_80045F08(func_ovl0F_10_80044AD4, arg0, 0, 0, 0x110);
            }
        }
        if (flags == 0x40000000) {
            if (arg0->unk58 <= arg0->unk40->unk10) {
                speed += (dist < 50.0f) ? 0.1f : 0.16f;
                if (25.0f < speed) {
                    speed = 25.0f;
                }
                speed += (arg0->unk40->unk10 - arg0->unk58) * 0.01f;
                if (25.0f < speed) {
                    speed = 25.0f;
                }
            } else {
                arg0->unk40->unk14 -= (arg0->unk40->unk14 - arg0->unk5C) * 0.8f;
                arg0->unk40->unk10 -= (arg0->unk40->unk10 - arg0->unk58) * 0.8f;
                speed += (dist < 50.0f) ? 0.1f : 0.16f;
                if (25.0f < speed) {
                    speed = 25.0f;
                }
            }
            if (D_ovl0F_10_800466C8 == 1 && D_ovl0F_10_800466CC == 0) {
                func_ovl0F_10_80046490(0x32);
                D_ovl0F_10_800466CC = 20;
            }
        } else if (flags == 0x30000000) {
            func_ovl0F_10_80043FAC(dist + 100.0f, &speed, &flags);
        }
            break;
    }
    func_ovl0F_10_80044054(arg0, flags, speed);
    func_ovl0F_10_80043FAC(dist, &speed, &flags);
    if (func_ovl0F_10_80043FA4(arg0)) {
        func_ovl0F_10_80043F9C(arg0, pos);
    } else {
        func_ovl0F_10_80043F94(&arg0->unk64, flags, speed);
    }
}

static void func_ovl0F_10_8004406C(void) {
}

/* the side flags */
static void func_ovl0F_10_80044064(UnkStructA *arg0) {
    if (arg0->unk8 & 1) {
        D_ovl0F_10_800466C8 = 1;
    } else {
        D_ovl0F_10_800466C8 = 0;
    }
}

static void func_ovl0F_10_8004405C(UnkStructA *arg0, f32 *pos) {
    pos[0] = arg0->unk40->unk10;
    pos[1] = arg0->unk40->unk14;
    pos[2] = arg0->unk40->unk18;
}

static void func_ovl0F_10_80044054(UnkStructA *arg0, s32 flags, f32 speed) {
    switch (flags) {
        case 0x30000000:
            func_ovl0F_10_80046408(arg0, 0xC0, speed);
            break;
        case 0x40000000:
            func_ovl0F_10_80046408(arg0, 0x40, speed);
            break;
    }
}

static void func_ovl0F_10_80043FAC(f32 dist, f32 *speed, s32 *flags) {
    if (dist < 50.0f) {
        *speed -= 0.05f;
    } else if (dist < 100.0f) {
        *speed -= 0.1f;
    } else {
        *speed -= 0.2f;
    }
    if (*speed < 0.0f) {
        *speed = 0.0f;
        *flags = 0;
    }
}

static s32 func_ovl0F_10_80043FA4(UnkStructA *arg0) {
    s32 hit;
    s32 saved;
    UnkStructA *other;
    s32 id;

    hit = 0;
    other = NULL;
    saved = arg0->unkC;
    arg0->unkC = 0;
    if (arg0->unk8 & 1) {
        other = func_ovl0F_10_80045638(func_ovl0F_10_80045598());
    } else if (arg0->unk8 & 2) {
        id = func_ovl0F_10_80045598();
        if (func_ovl0F_10_80045638(id) == arg0) {
            other = func_ovl0F_10_800455F8(id);
        } else {
            other = NULL;
        }
    }
    if (other != NULL) {
        if (func_ovl0F_10_80045ED8(arg0, 0x10, other) != 0) {
            hit = 1;
        }
    } else if (func_ovl0F_10_80045D68(arg0, 0x10) != 0) {
        hit = 1;
    }
    arg0->unkC = saved;
    return hit;
}

static void func_ovl0F_10_80043F9C(UnkStructA *arg0, f32 *pos) {
    arg0->unk40->unk10 = pos[0];
    arg0->unk40->unk14 = pos[1];
    arg0->unk40->unk18 = pos[2];
}

static void func_ovl0F_10_80043F94(s32 *dst, s32 flags, f32 speed) {
    *dst = (flags & 0xF0000000) | ((s32)(speed * 100.0f) & 0x0FFFFFFF);
}


void func_ovl0F_10_80043E08(void) {
    s32 task;
    s32 id;

    id = func_ovl0F_10_80045598();
    func_ovl0F_10_800455F8(id);
    D_ovl0F_10_800468A4 = 0;
    D_ovl0F_10_80046B34->unk3C = D_ovl0F_10_80046B34->unk4C * 0.05f;
    func_ovl0F_10_80045C60(0x7F);
    func_ovl0F_10_80045BF8(2898.7f, 3582.5f, 1940.3f);
    func_ovl0F_10_80045C18(247.7f, 1.7f, 344.0f);
    while (D_ovl0F_10_800468A4 == 0) {
        func_ovl0F_10_80045F50();
    }
    task = func_ovl0F_10_80045F08(func_ovl0F_10_800448A0, NULL, 0, 0, 0x130);
    func_ovl0F_10_80045658(1);
    func_ovl0F_10_800455C0(D_ovl0F_10_800468DC);
    func_ovl0F_10_800455C0(D_ovl0F_10_80046908);
    func_ovl0F_10_800455C0(D_ovl0F_10_80046910);
    func_ovl0F_10_800455C0(D_ovl0F_10_8004694C);
    func_ovl0F_10_80045648(id, 0xB);
    func_ovl0F_10_80045F28(60);
    func_ovl0F_10_800455C0(D_ovl0F_10_8004696C);
    func_ovl0F_10_800455C0(D_ovl0F_10_80046974);
    func_ovl0F_10_800455C0(D_ovl0F_10_80046998);
    func_ovl0F_10_80045658(0);
    func_ovl0F_10_800455E0(0x4000000);
    func_ovl0F_10_80045F28(40);
    func_ovl0F_10_80045658(1);
    func_ovl0F_10_80045F28(0x262);
    func_ovl0F_10_80046608();
    func_ovl0F_10_80045F10(task);
    func_ovl0F_10_80045F18();
}

void func_ovl0F_10_80043CCC(void) {
    s32 i;

    D_ovl0F_10_800468AC = 0;
    D_ovl0F_10_800468B0 = 0.0f;
    while (1) {
        if (D_ovl0F_10_800468AC != 0) {
            for (i = 0; i < 90; i++) {
                if (D_ovl0F_10_800468B4 != 0) {
                    D_ovl0F_10_800468B0 += 0.22222222f;
                } else {
                    D_ovl0F_10_800468B0 += -0.22222222f;
                }
                func_ovl0F_10_80045CB0(D_ovl0F_10_800468B0, D_ovl0F_10_800468B0 - 0.1f);
                func_ovl0F_10_80045F50();
            }
            D_ovl0F_10_800468AC = 0;
        }
        func_ovl0F_10_80045F28(5);
    }
}

void func_ovl0F_10_80043344(f32 arg0) {
    f32 sp1C;

    func_ovl0F_10_80045C20(&sp1C, NULL, NULL);
    func_ovl0F_10_80045C18(sp1C + arg0, 32768.0f, 32768.0f);
}

/* case 2's: the models of D_ovl0F_10_80046AE0[1] */
static void func_ovl0F_10_80043408(void) {
    func_ovl0F_10_80045AB0(D_ovl0F_10_80046AE0[1]->unk40, 0x61);
    D_ovl0F_10_80046AE0[1]->unk40->unk14 += 3200.0f;
}

static void func_ovl0F_10_80043410(void) {
    func_ovl0F_10_800453B8(0x233);
    func_ovl0F_10_800453D0(0x240);
    func_ovl0F_10_80045568();
}

static void func_ovl0F_10_80043418(void) {
    s32 count;
    u32 (*p)[3];
    s32 i;

    func_ovl0F_10_80046270(D_ovl0F_10_800466D8);
    p = D_ovl0F_10_800466FC;
    count = 4;
    for (i = 0; i < count; i++) {
        func_ovl0F_10_80046418((*p)[0], (*p)[1], (*p)[2]);
        p++;
    }
}

static void func_ovl0F_10_80043420(void) {
    D_ovl0F_10_800468B8 = func_ovl0F_10_80045DE0(0x323, 0x1000010, 0xC0, 0);
    D_ovl0F_10_800468B8->unk40->unk10 = 1300.0f;
    D_ovl0F_10_800468B8->unk40->unk14 = 0.0f;
    D_ovl0F_10_800468B8->unk40->unk18 = 300.0f;
}

static void func_ovl0F_10_80043428(void) {
    D_ovl0F_10_80046B04 = func_ovl0F_10_800454B8();
    if (D_ovl0F_10_80046B04 == 0x10) {
        D_ovl0F_10_800466D0 = 1;
        func_ovl0F_10_80046180(0x405);
        func_ovl0F_10_80046438(0);
    } else {
        D_ovl0F_10_800466D0 = 0;
    }
}

static void func_ovl0F_10_8004333C(void) {
    func_ovl0F_10_80045C18(0.0f, 32768.0f, 32768.0f);
}

static void func_ovl0F_10_80043334(void) {
    func_ovl0F_10_80045508();
}

static void func_ovl0F_10_8004332C(void) {
    switch (func_ovl0F_10_800454B8()) {
        case 0x12:
            func_ovl0F_10_800455B8(D_ovl0F_10_8004686C[0].unk0, D_ovl0F_10_8004686C[0].unk4,
                                   D_ovl0F_10_8004686C[0].unk8, D_ovl0F_10_8004686C[0].unkC,
                                   D_ovl0F_10_8004686C[0].unk10, D_ovl0F_10_8004686C[0].unk14,
                                   D_ovl0F_10_8004686C[0].unk18);
            break;
        case 0x13:
            func_ovl0F_10_800455B8(D_ovl0F_10_8004686C[1].unk0, D_ovl0F_10_8004686C[1].unk4,
                                   D_ovl0F_10_8004686C[1].unk8, D_ovl0F_10_8004686C[1].unkC,
                                   D_ovl0F_10_8004686C[1].unk10, D_ovl0F_10_8004686C[1].unk14,
                                   D_ovl0F_10_8004686C[1].unk18);
            break;
    }
}

static void func_ovl0F_10_80043078(s32 count, UnkStruct_ovl0F_10_8004672C *p) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_ovl0F_10_80045DD0(*p->unk0);
        p++;
    }
}

static void func_ovl0F_10_800432D8(void) {
    if (func_ovl0F_10_80046190(0x405) == 0 && func_ovl0F_10_80045580(0xB, 3, 0xC, 4) != 0) {
        func_ovl0F_10_800455A8(1);
        func_ovl0F_10_80046478();
        func_ovl0F_10_80046398();
        func_ovl0F_10_800455D0(1);
        func_ovl0F_10_80046490(0x29);
        func_ovl0F_10_80046180(D_ovl0F_10_800467DC[0].unk28);
        func_ovl0F_10_80043078(1, D_ovl0F_10_800467DC);
        func_ovl0F_10_800431BC(D_ovl0F_10_800467DC, 0);
        func_ovl0F_10_800454B0(0x5C, 0x11, 0);
    }
}

static void func_ovl0F_10_80043080(void) {
    f32 y;

    if (func_ovl0F_10_80045588(0xD, 0, 4, 0xD, 4) != 0) {
        y = func_ovl0F_10_800455F8(func_ovl0F_10_80045598())->unk40->unk20;
        if (135.0f <= y && y <= 225.0f) {
            if (func_ovl0F_10_80046170(0xA4) != 0) {
                func_ovl0F_10_80045B20(0x291, 1);
            } else {
                func_ovl0F_10_80045B20(0x278, 2);
            }
        }
    }
}

static void func_ovl0F_10_80043070(void) {
    D_ovl0F_10_80046B14 = func_ovl0F_10_80045598();
    func_ovl0F_10_80045578(&D_ovl0F_10_80046B08);
    func_ovl0F_10_800455A0(D_ovl0F_10_80046B14, D_ovl0F_10_80046AF8);
}

static void func_ovl0F_10_80043068(void) {
    if (D_ovl0F_10_800466D0 == 0) {
        if (2500.0f <= D_ovl0F_10_80046AF8[2] && D_ovl0F_10_800468A8 == 1) {
            if (func_ovl0F_10_80043010(0)) {
                D_ovl0F_10_800468A8 = 0;
            }
        } else if (D_ovl0F_10_80046AF8[2] < 2500.0f && D_ovl0F_10_800468A8 == 0) {
            if (func_ovl0F_10_80043010(1)) {
                D_ovl0F_10_800468A8 = 1;
            }
        }
    }
}

/* The overlay's handler: the entry returns it to the loader. */
void func_ovl0F_10_80043430(s32 arg0) {
    switch (arg0) {
        case 2:
            D_ovl0F_10_800468BC = -1;
            D_ovl0F_10_800466D4 = 0;
            func_ovl0F_10_80043428();
            func_ovl0F_10_80043420();
            func_ovl0F_10_80043418();
            func_ovl0F_10_80043410();
            D_ovl0F_10_800466B4 = 0;
            D_ovl0F_10_800466B0 = 0;
            func_ovl0F_10_80045CB0(70.0f, 45.0f);
            func_ovl0F_10_8004310C(D_ovl0F_10_8004672C, 4);
            func_ovl0F_10_80043408();
            if (func_ovl0F_10_80046190(0x405) == 0) {
                func_ovl0F_10_8004338C(0x279);
            } else {
                func_ovl0F_10_8004338C(0x27A);
            }
            func_ovl0F_10_800431BC(D_ovl0F_10_800467DC, 1);
            break;
        case 16:
            D_ovl0F_10_800466D0 = 1;
            func_ovl0F_10_80045570(0x2D, 5, 0x1D);
            func_ovl0F_10_800455B0(0);
            break;
        case 18:
            func_ovl0F_10_800455B0(0);
            func_ovl0F_10_80045570(0x2D, 5, 0x1D);
            func_ovl0F_10_80043344(-90.0f);
            break;
        case 19:
            func_ovl0F_10_800455B0(0);
            func_ovl0F_10_80045570(0xA, 0, 0x1E);
            func_ovl0F_10_80043344(90.0f);
            break;
        case 20:
            func_ovl0F_10_80045570(0x2D, 5, 0x1A);
            break;
        case 21:
            func_ovl0F_10_80045570(0xB, 2, 3);
            func_ovl0F_10_8004333C();
            break;
        case 4:
            func_ovl0F_10_800455C8();
            D_ovl0F_10_800468A8 = 0;
            func_ovl0F_10_80045CB0(55.0f, 54.9f);
            func_ovl0F_10_800454A0(func_ovl0F_10_80044780);
            func_ovl0F_10_80043334();
            func_ovl0F_10_80045498(func_ovl0F_10_80044074, 1);
            if (D_ovl0F_10_800466D0 == 1) {
                func_ovl0F_10_800455A8(1);
                func_ovl0F_10_80045520(0);
                func_ovl0F_10_80045F08(func_ovl0F_10_80043E08, NULL, 0, 0, 0x130);
            }
            D_ovl0F_10_800468BC = func_ovl0F_10_80045F08(func_ovl0F_10_80043CCC, NULL, 0, 0, 0x130);
            break;
        case 5:
            func_ovl0F_10_8004332C();
            break;
        case 0x50:
            func_ovl0F_10_800432E0(D_ovl0F_10_80046834);
            func_ovl0F_10_800432E0(D_ovl0F_10_80046850);
            break;
        case 0x52:
            func_ovl0F_10_800432D8();
            break;
        case 15:
            func_ovl0F_10_80043080();
            break;
        case 1:
            func_ovl0F_10_80043078(4, D_ovl0F_10_8004672C);
            if (D_ovl0F_10_800466B8 != 0) {
                func_ovl0F_10_80043078(D_ovl0F_10_800466B8, D_ovl0F_10_800467DC);
            }
            func_ovl0F_10_80045DD0(D_ovl0F_10_800468B8);
            D_ovl0F_10_800468B8 = NULL;
            if (D_ovl0F_10_800466D0 == 1) {
                func_ovl0F_10_80046610();
            }
            if (D_ovl0F_10_800468BC != -1) {
                func_ovl0F_10_80045F10(D_ovl0F_10_800468BC);
                D_ovl0F_10_800468BC = -1;
            }
            break;
        case 12:
            func_ovl0F_10_80045600(1);
            break;
        case 3:
            func_ovl0F_10_80043070();
            func_ovl0F_10_80043068();
            D_ovl0F_10_800468A4 = 1;
            if (D_ovl0F_10_800466CC > 0) {
                D_ovl0F_10_800466CC--;
            }
            if (D_ovl0F_10_800466D4 > 0) {
                D_ovl0F_10_800466D4--;
            }
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
        case 17:
            break;
        case 0x53:
            break;
    }
}

static void func_ovl0F_10_8004338C(s32 arg0) {
    D_ovl0F_10_80046B34 = func_ovl0F_10_80045F90(arg0);
    func_ovl0F_10_80045FA0(D_ovl0F_10_80046B34, 0x20000000);
    D_ovl0F_10_80046B34->unk40 = 0.6f;
    D_ovl0F_10_80046B34->unk44 = D_ovl0F_10_80046B34->unk40 * 0.75f;
    D_ovl0F_10_80046B34->unk3C = D_ovl0F_10_80046B34->unk4C * 0.3f;
}

static void func_ovl0F_10_800431BC(UnkStruct_ovl0F_10_8004672C *arg0, s32 arg1) {
    if (func_ovl0F_10_80046190(arg0->unk28) != 0) {
        arg0->unk4 = 0x1B0;
        D_ovl0F_10_800466B8 = 1;
    } else {
        arg0->unk4 = 0x1B3;
        D_ovl0F_10_800466B8 = 1;
    }
    func_ovl0F_10_8004310C(arg0, D_ovl0F_10_800466B8);
    (*arg0->unk0)->unk40->unk10 += 50.0f;
    (*arg0->unk0)->unk40->unk14 += 2.0f;
    (*arg0->unk0)->unk40->unk18 += 50.0f;
    (*arg0->unk0)->unk40->unk28 = 2.0f;
    (*arg0->unk0)->unk40->unk30 = 2.0f;
}

static void func_ovl0F_10_8004310C(UnkStruct_ovl0F_10_8004672C *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *arg0->unk0 = func_ovl0F_10_80045E28(arg0->unk4, arg0->unk8);
        func_ovl0F_10_80045DB8(*arg0->unk0, arg0->unk24 | 0x01000000);
        func_ovl0F_10_80043088(arg0);
        (*arg0->unk0)->unk40->unk1C = arg0->unk18;
        (*arg0->unk0)->unk40->unk20 = arg0->unk1C;
        (*arg0->unk0)->unk40->unk24 = arg0->unk20;
        arg0++;
    }
}

static void func_ovl0F_10_80043088(UnkStruct_ovl0F_10_8004672C *arg0) {
    f32 pos[3];

    func_ovl0F_10_80045418(arg0->unkC, arg0->unk10, arg0->unk14, pos, 0);
    (*arg0->unk0)->unk40->unk10 = pos[0];
    (*arg0->unk0)->unk40->unk14 = pos[1];
    (*arg0->unk0)->unk40->unk18 = pos[2];
}

static void func_ovl0F_10_800432E0(s32 *arg0) {
    if (func_ovl0F_10_80045580(arg0[0], arg0[1], arg0[2], arg0[3]) != 0) {
        func_ovl0F_10_800454B0(arg0[4], arg0[5], arg0[6]);
    }
}

static s32 func_ovl0F_10_80043010(s32 arg0) {
    s32 ret;

    ret = 0;
    if (D_ovl0F_10_800468AC == 0) {
        ret = 1;
        if (arg0 != 0) {
            D_ovl0F_10_800468B0 = 55.0f;
        } else {
            D_ovl0F_10_800468B0 = 75.0f;
        }
        D_ovl0F_10_800468B4 = arg0;
        D_ovl0F_10_800468AC = 1;
    }
    return ret;
}
