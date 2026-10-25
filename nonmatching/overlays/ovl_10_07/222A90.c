/*
 * NON_MATCHING: ovl_10_07's game object, complete: every function, its
 * .bss and its .data tables. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 126, jp 126
 *
 * What still differs in us (words):
 * - func_ovl10_07_80043B98 (1), 80044FD8 (12), 800452A8 (14), 80045758
 *   (62), 80046E28 (9), 8004713C (9) and 800479D4 (2): ovl_10_09's
 *   80043B78, 80044FEC, 800452BC, 8004576C, 800468FC, 80046C10 and
 *   800474A8, with the same differences (its
 *   header).
 * - func_ovl10_07_80043254 (6): ovl_10_08's 800432B0 (the same code; the
 *   same C as ovl_10_09's 80043238, which misses by 2), with the same
 *   differences.
 * - func_ovl10_07_8004809C (11): the same code; the padding IDO puts after its
 *   endless loop (to a 16-byte boundary) is a word longer
 *   because 80045758 is a word short (as in ovl_10_11's 80044C24).
 *
 * ovl_10_07's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Most of it is ovl_10_09's
 * draft, renamed (scratch/10_07/ in the checkout has the scripts). Its own:
 * the handler 80045AE8 and its cases (80043010, 8004374C, 8004376C,
 * 80043E60, 80044704, 80044824, 800448BC, 80044AC0, 80044BA8), the set-up
 * 800458C4, and the doors the gate's opening drives (80045CAC-800462DC: a
 * chain of tasks, each giving the next with its delay). The set-up passes
 * 80048688 its tile as ints (13, 0, 8): written 0.0f, IDO keeps 0.0f in an
 * f20 across the calls. 800443E4 is defined above 8004563C and the .data
 * tables after the functions, as in ovl_10_09: .data, .rodata and .bss
 * build to the original's bytes and places.
 */
#include "common.h"
/* What func_ovl10_07_80049200 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_07_80049200;

void func_ovl10_07_800482E8(const char *, ...);
void func_ovl10_07_80048628(s32);
void func_ovl10_07_80048630(s32, f32, f32, f32, s32, s32);
void func_ovl10_07_80048640(s32);
void func_ovl10_07_80048660(s32, s32, s32, s32);
void func_ovl10_07_80048680(f32, f32, f32, s32 *, s32);
void func_ovl10_07_80048688(f32, f32, f32, Vec3f *, s32);
f32 func_ovl10_07_800486C8(s32);
void func_ovl10_07_800486D0(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_07_800486D8(s32, s32, s32, s32, s32, s32);
void func_ovl10_07_800486E0(s32);
void func_ovl10_07_80048710(void (*)(UnkStructA *));
void func_ovl10_07_80048720(s32, s32, s32);
s32 *func_ovl10_07_80048778(void);
void func_ovl10_07_80048790(s32);
void func_ovl10_07_800487D8(void);
void func_ovl10_07_800487E0(s32, s32, s32);
s32 func_ovl10_07_800487F8(s32, s32, s32, s32, s32);
s32 func_ovl10_07_80048808(void);
void func_ovl10_07_80048818(s32);
void func_ovl10_07_80048828(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_07_80048838(void);
void func_ovl10_07_80048840(s32);
void func_ovl10_07_80048850(s32);
UnkStructA *func_ovl10_07_80048868(s32);
void func_ovl10_07_80048880(s32);
void func_ovl10_07_80048E68(f32, f32, f32);
void func_ovl10_07_80048E88(f32, f32, f32);
void func_ovl10_07_80048E90(f32 *, f32 *, f32 *);
void func_ovl10_07_80048ED0(s32);
void func_ovl10_07_80048EF0(f32);
void func_ovl10_07_80048EF8(f32);
void func_ovl10_07_80048F10(f32);
void func_ovl10_07_80049030(UnkStructA *, s32);
void func_ovl10_07_80049040(UnkStructA *);
UnkStructA *func_ovl10_07_80049050(s32, s32, s32, UnkStructA *);
void func_ovl10_07_800490A8(UnkStructA *);
void func_ovl10_07_800490F8(UnkStructA *, Vec3f *);
void func_ovl10_07_80049178(void (*)(void), s32, s32, s32, s32);
void func_ovl10_07_80049198(s32);
void func_ovl10_07_800491C0(void);
void func_ovl10_07_800491F0(s32, s32);
UnkStruct_ovl10_07_80049200 *func_ovl10_07_80049200(void);
void func_ovl10_07_80049210(UnkStruct_ovl10_07_80049200 *, s32);
s32 *func_ovl10_07_80049410(void);
void func_ovl10_07_80049478(s32, s32, s32, f32);
void func_ovl10_07_800494B8(s32, s32, s32, s32, s32);
void func_ovl10_07_800494C8(s32, s32, s32);
void func_ovl10_07_800494E0(u32 (*)[3]);
s32 func_ovl10_07_800495D0(s32, Vec3f *, UnkStructA *);
void func_ovl10_07_80049688(s32, s32, s32);
s32 func_ovl10_07_80049700(s32);
void func_ovl10_07_80049720(s32, f32, f32, f32);
void func_ovl10_07_80048820(s32);
void func_ovl10_07_80048830(const char *);
void func_ovl10_07_800488C8(s32);
s32 func_ovl10_07_800488F0(s32);
void func_ovl10_07_80048D30(UnkStructA_40 *, s32);
void func_ovl10_07_80048D38(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl10_07_80048D70(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl10_07_80048EA0(u32 *, s32, s32);
void func_ovl10_07_80048EE0(s32);
f32 func_ovl10_07_80048FD0(Vec3f *, Vec3f *);
void func_ovl10_07_80049028(UnkStructA *, s32);
void func_ovl10_07_80049188(void);
s32 func_ovl10_07_80049338(s32);
void func_ovl10_07_800496A8(s32);
s32 func_ovl10_07_80049728(s32, Vec3f *);
void func_ovl10_07_80049730(s32);
void func_ovl10_07_80049878(void);
void func_ovl10_07_80049880(void);

void func_ovl10_07_800486A0(s32);
void func_ovl10_07_800486A8(void);
s32 func_ovl10_07_800486F8(s32);
void func_ovl10_07_80048700(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_07_800495F8(s16, s32);
void func_ovl10_07_80049600(s16, s32);


void func_ovl10_07_80048798(s32);
void func_ovl10_07_800487B0(s32, s32);
s32 *func_ovl10_07_800488E8(s32);
void func_ovl10_07_80048D48(UnkStructA_40 *, s32);
void func_ovl10_07_80048D50(UnkStructA_40 *, s32, s32);
f32 func_ovl10_07_80048D68(UnkStructA_40 *, s32);
void func_ovl10_07_80048D80(UnkStructA_40 *, s32, s32);
void func_ovl10_07_80048D90(s32, s32);
void func_ovl10_07_80049060(UnkStructA *);
s32 func_ovl10_07_800493E0(s32);
void func_ovl10_07_800495C8(s32, f32, f32, f32, s32);
void func_ovl10_07_800495D8(s32);

void func_ovl10_07_80048288(void);
void func_ovl10_07_80048270(void);
void func_ovl10_07_80048214(f32 arg0, f32 arg1, f32 arg2);
void func_ovl10_07_800481CC(f32 arg0);
void func_ovl10_07_80048198(s32 arg0, UnkStructA *arg1);
void func_ovl10_07_8004809C(void);
s32 func_ovl10_07_800430F4(void (*arg0)(void));
s32 func_ovl10_07_80048064(void (*arg0)(void), const char *arg1);
void func_ovl10_07_80048038(void (*arg0)(void));
s32 func_ovl10_07_80047FF4(void (*arg0)(void));
void func_ovl10_07_80047FE0(s32 arg0);
void func_ovl10_07_80047F50(void);
void func_ovl10_07_80047F14(void);
void func_ovl10_07_80047EA8(UnkStructA *arg0);
void func_ovl10_07_80047E28(UnkStructA *arg0);
void func_ovl10_07_800479D4(void);
void func_ovl10_07_800478B0(void);
void func_ovl10_07_80047878(s32 arg0);
void func_ovl10_07_80047630(void);
void func_ovl10_07_80047550(void);
void func_ovl10_07_80047330(void);
void func_ovl10_07_8004713C(void);
void func_ovl10_07_80046E28(s32 arg0, s32 arg1);
void func_ovl10_07_80046DC4(s32 arg0, s32 arg1);
void func_ovl10_07_80046AA8(void);
void func_ovl10_07_80046A08(s32 arg0);
void func_ovl10_07_80046954(void);
void func_ovl10_07_800467F0(s32 arg0, s32 arg1);
f32 func_ovl10_07_80046798(s32 arg0);
void func_ovl10_07_800465E0(void);
void func_ovl10_07_800465A8(s32 arg0);
void func_ovl10_07_800462DC(void);
void func_ovl10_07_80046210(void);
void func_ovl10_07_80046104(void);
void func_ovl10_07_80046088(void);
void func_ovl10_07_8004603C(void);
void func_ovl10_07_80045E2C(void);
void func_ovl10_07_80045DE0(void);
void func_ovl10_07_80045D78(void);
void func_ovl10_07_80045D5C(s32 arg0);
void func_ovl10_07_80045D40(void (*arg0)(void));
void func_ovl10_07_80045CD4(void);
void func_ovl10_07_80045CAC(void);
void func_ovl10_07_80045C90(void);
void func_ovl10_07_80045AE8(s32 arg0);
void func_ovl10_07_800458C4(void);
void func_ovl10_07_80045758(s32 *arg0);
void func_ovl10_07_800443E4(s32 arg0, s32 arg1);
void func_ovl10_07_8004563C(s32 arg0);
void func_ovl10_07_80045588(s32 *arg0);
void func_ovl10_07_800452A8(s32 *arg0);
void func_ovl10_07_80044FD8(s32 *arg0);
void func_ovl10_07_80044E8C(s32 *arg0);
void func_ovl10_07_80044DC8(s32 arg0);
void func_ovl10_07_80044C5C(s32 *arg0);
void func_ovl10_07_80044BE0(void);
void func_ovl10_07_80044BA8(void);
void func_ovl10_07_80044AC0(void);
void func_ovl10_07_8004495C(void);
void func_ovl10_07_800448BC(void);
void func_ovl10_07_8004489C(void);
void func_ovl10_07_80044824(void);
void func_ovl10_07_80044704(void);
void func_ovl10_07_8004453C(void);
void func_ovl10_07_80044318(void);
void func_ovl10_07_80044268(void);
void func_ovl10_07_800441C4(void);
void func_ovl10_07_800440C8(s32 arg0, s32 arg1);
void func_ovl10_07_80043EEC(s32 arg0);
void func_ovl10_07_80043E60(void);
void func_ovl10_07_80043DE8(s32 arg0);
void func_ovl10_07_80043DA8(void);
void func_ovl10_07_80043B98(s32 arg0, s32 arg1);
void func_ovl10_07_80043944(s32 arg0, s32 arg1);
void func_ovl10_07_80043914(s32 arg0);
void func_ovl10_07_800438CC(s32 arg0);
void func_ovl10_07_8004389C(s32 arg0);
void func_ovl10_07_80043804(s32 arg0);
void func_ovl10_07_800437EC(s32 arg0);
void func_ovl10_07_800437D4(void);
void func_ovl10_07_8004376C(void);
void func_ovl10_07_8004374C(void);
s32 func_ovl10_07_8004347C(s32 arg0);
void func_ovl10_07_80043340(void);
void func_ovl10_07_80043254(void);
void func_ovl10_07_8004316C(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl10_07_800430EC(void);
void func_ovl10_07_80043084(void);
void func_ovl10_07_80043034(void);
void func_ovl10_07_80043010(void);

/* .bss */
u8 D_ovl10_07_80049B80[0x24]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_80049BA4;
s32 D_ovl10_07_80049BA8;
u8 D_ovl10_07_80049BAC[0x4]; /* unused (func_ovl10_07_80048288) */
Vec3f D_ovl10_07_80049BB0;
u8 D_ovl10_07_80049BBC[0x4]; /* unused (func_ovl10_07_80048288) */
UnkStructA *D_ovl10_07_80049BC0[12];
s32 D_ovl10_07_80049BF0[11][3];
u8 D_ovl10_07_80049C74[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_80049C78[12];
s32 D_ovl10_07_80049CA8[12];
s32 D_ovl10_07_80049CD8[64];
s32 D_ovl10_07_80049DD8;
u8 D_ovl10_07_80049DDC[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_80049DE0[12];
s32 D_ovl10_07_80049E10[12];
s32 D_ovl10_07_80049E40[11];
s32 D_ovl10_07_80049E6C;
s32 D_ovl10_07_80049E70[11];
s32 D_ovl10_07_80049E9C;
s32 D_ovl10_07_80049EA0;
s32 D_ovl10_07_80049EA4;
s32 D_ovl10_07_80049EA8[64];
s32 D_ovl10_07_80049FA8;
u8 D_ovl10_07_80049FAC[0x4]; /* unused (func_ovl10_07_80048288) */
void (*D_ovl10_07_80049FB0[64])(void);
UnkStruct_ovl10_07_80049200 *D_ovl10_07_8004A0B0;
u8 D_ovl10_07_8004A0B4[0x4]; /* unused (func_ovl10_07_80048288) */
UnkStructA *D_ovl10_07_8004A0B8[6];
s32 D_ovl10_07_8004A0D0[6][3];
s32 D_ovl10_07_8004A118[6];
s32 D_ovl10_07_8004A130[6];
s32 D_ovl10_07_8004A148[64];
s32 D_ovl10_07_8004A248;
u8 D_ovl10_07_8004A24C[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_8004A250[6];
s32 D_ovl10_07_8004A268[6];
f32 D_ovl10_07_8004A280[6];
f32 D_ovl10_07_8004A298[6];
UnkStructA *D_ovl10_07_8004A2B0; /* the doors */
UnkStructA *D_ovl10_07_8004A2B4;
UnkStructA *D_ovl10_07_8004A2B8;
s32 D_ovl10_07_8004A2BC;
s32 D_ovl10_07_8004A2C0;
s32 D_ovl10_07_8004A2C4;
s32 D_ovl10_07_8004A2C8;
f32 D_ovl10_07_8004A2CC;
f32 D_ovl10_07_8004A2D0;
u8 D_ovl10_07_8004A2D4[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_8004A2D8[4][3];
UnkStructA *D_ovl10_07_8004A308[4];
s32 D_ovl10_07_8004A318;
u8 D_ovl10_07_8004A31C[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_8004A320[4];
s32 D_ovl10_07_8004A330[4];
s32 D_ovl10_07_8004A340[5];
s32 D_ovl10_07_8004A354;
f32 D_ovl10_07_8004A358;
f32 D_ovl10_07_8004A35C;
f32 D_ovl10_07_8004A360;
u8 D_ovl10_07_8004A364[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_8004A368[6][3];
UnkStructA *D_ovl10_07_8004A3B0[6];
UnkStructA *D_ovl10_07_8004A3C8;
s32 D_ovl10_07_8004A3CC;
s32 D_ovl10_07_8004A3D0;
s32 D_ovl10_07_8004A3D4;
s32 D_ovl10_07_8004A3D8;
s32 D_ovl10_07_8004A3DC;
s32 D_ovl10_07_8004A3E0[6];
s32 D_ovl10_07_8004A3F8[6];
s32 D_ovl10_07_8004A410[6];
s32 D_ovl10_07_8004A428;
u8 D_ovl10_07_8004A42C[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_8004A430[6];
s32 D_ovl10_07_8004A448[6];
s32 D_ovl10_07_8004A460[6];
s32 D_ovl10_07_8004A478[6];
s32 D_ovl10_07_8004A490[6];
f32 D_ovl10_07_8004A4A8;
f32 D_ovl10_07_8004A4AC;
f32 D_ovl10_07_8004A4B0;
f32 D_ovl10_07_8004A4B4;
f32 D_ovl10_07_8004A4B8;
f32 D_ovl10_07_8004A4BC;
f32 D_ovl10_07_8004A4C0;
u8 D_ovl10_07_8004A4C4[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_8004A4C8[1][3]; /* the gate: its tile */
UnkStructA *D_ovl10_07_8004A4D4[1]; /* its two halves */
UnkStructA *D_ovl10_07_8004A4D8[1];
s32 D_ovl10_07_8004A4DC[1]; /* open */
s32 D_ovl10_07_8004A4E0[64]; /* per task: its gate */
s32 D_ovl10_07_8004A5E0;
s32 D_ovl10_07_8004A5E4[1]; /* moving */
f32 D_ovl10_07_8004A5E8[1];
f32 D_ovl10_07_8004A5EC[1];
f32 D_ovl10_07_8004A5F0[1];
u8 D_ovl10_07_8004A5F4[0x4]; /* unused (func_ovl10_07_80048288) */
UnkStructA *D_ovl10_07_8004A5F8[28];
UnkStructA *D_ovl10_07_8004A668[28];
s32 D_ovl10_07_8004A6D8[27][3];
u8 D_ovl10_07_8004A81C[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_8004A820[28];
s32 D_ovl10_07_8004A890[28];
s32 D_ovl10_07_8004A900[64];
s32 D_ovl10_07_8004AA00;
u8 D_ovl10_07_8004AA04[0x4]; /* unused (func_ovl10_07_80048288) */
s32 D_ovl10_07_8004AA08[28];
s32 D_ovl10_07_8004AA78[28];
s32 D_ovl10_07_8004AAE8[27][4];
f32 D_ovl10_07_8004AC98[28];
f32 D_ovl10_07_8004AD08[28];
f32 D_ovl10_07_8004AD78[27];
s32 D_ovl10_07_8004ADE4;
s32 D_ovl10_07_8004ADE8;
s32 D_ovl10_07_8004ADEC;
s32 D_ovl10_07_8004ADF0[64];
s32 D_ovl10_07_8004AEF0;
s32 D_ovl10_07_8004AEF4;

/* .data: defined at the end of the file */
extern u32 D_ovl10_07_80049940[][3];
extern s32 D_ovl10_07_80049964[];
extern s32 D_ovl10_07_800499B8[];
extern s32 D_ovl10_07_800499EC[];
extern s32 D_ovl10_07_80049A1C[];
extern s32 D_ovl10_07_80049A40[];
extern s32 D_ovl10_07_80049A54[];

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_07_800482D8(void) {
}

static void func_ovl10_07_800482D0(void) {
}

static void func_ovl10_07_800482C8(void) {
}

static void func_ovl10_07_800482C0(void) {
}

static void func_ovl10_07_800482B8(void) {
}

static void func_ovl10_07_800482B0(void) {
}

static void func_ovl10_07_800482A8(void) {
}

static void func_ovl10_07_800482A0(void) {
}

static void func_ovl10_07_80048298(void) {
}

static void func_ovl10_07_80048290(void) {
}

void func_ovl10_07_80048288(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_07_80049B80[0] = D_ovl10_07_80049BAC[0] + D_ovl10_07_80049BBC[0] + D_ovl10_07_80049C74[0] + D_ovl10_07_80049DDC[0] + D_ovl10_07_80049FAC[0] + D_ovl10_07_8004A0B4[0] + D_ovl10_07_8004A24C[0] + D_ovl10_07_8004A2D4[0] + D_ovl10_07_8004A31C[0] + D_ovl10_07_8004A364[0] + D_ovl10_07_8004A42C[0] + D_ovl10_07_8004A4C4[0] + D_ovl10_07_8004A5F4[0] + D_ovl10_07_8004A81C[0] + D_ovl10_07_8004AA04[0];
    }
}

void func_ovl10_07_80048270(void) {
    D_ovl10_07_80049BA4 = -1;
    D_ovl10_07_80049BA8 = -1;
}

void func_ovl10_07_80048214(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_07_80048E68(D_ovl10_07_80049BB0.x, D_ovl10_07_80049BB0.y, D_ovl10_07_80049BB0.z);
    func_ovl10_07_80048E88(arg0, arg1, arg2);
    func_ovl10_07_80049198(180);
}

void func_ovl10_07_800481CC(f32 arg0) {
    f32 sp1C;

    func_ovl10_07_80048E90(&sp1C, NULL, NULL);
    func_ovl10_07_80048E88(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_07_80048198(s32 arg0, UnkStructA *arg1) {
    func_ovl10_07_80049720(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_07_8004809C(void) {
    s32 i;

    D_ovl10_07_80049EA0 = 0;
    D_ovl10_07_80049EA4 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_07_80049FB0[i] != NULL) {
                D_ovl10_07_80049FA8 = i;
                if (D_ovl10_07_80049EA8[i] == 0) {
                    D_ovl10_07_80049FB0[i]();
                } else {
                    D_ovl10_07_80049EA8[i]--;
                }
            }
        }
        D_ovl10_07_80049EA0++;
        D_ovl10_07_80049EA0 &= 3;
        func_ovl10_07_800491C0();
    }
}

/* Defined above its caller 80046FD0, which pulls it out among the earlier
 * functions all the same: only so does its string come first in .rodata. */
s32 func_ovl10_07_800430F4(void (*arg0)(void)) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_07_80049FB0[i] == NULL) {
            D_ovl10_07_80049FB0[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_07_800482E8("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_07_80048064(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_07_800430F4(arg0);
    func_ovl10_07_800482E8("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_07_80048038(void (*arg0)(void)) {
    D_ovl10_07_80049FB0[func_ovl10_07_80047FF4(arg0)] = NULL;
}

s32 func_ovl10_07_80047FF4(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_07_80049FB0[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_07_80047FE0(s32 arg0) {
    D_ovl10_07_80049FB0[arg0] = NULL;
}

void func_ovl10_07_80047F50(void) {
    D_ovl10_07_8004A0B0 = func_ovl10_07_80049200();
    func_ovl10_07_80049210(D_ovl10_07_8004A0B0, 0x20000001);
    D_ovl10_07_8004A0B0->unk40 = 0.5f;
    D_ovl10_07_8004A0B0->unk44 = D_ovl10_07_8004A0B0->unk40 * 0.75f;
    D_ovl10_07_8004A0B0->unk18 = 0.1f;
    D_ovl10_07_8004A0B0->unk1C = -0.1f;
}

void func_ovl10_07_80047F14(void) {
    s32 *p;

    p = func_ovl10_07_80049410();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_07_80047EA8(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_07_80048ED0(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_07_800490A8(arg0);
        func_ovl10_07_800491C0();
    }
}

void func_ovl10_07_80047E28(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_07_80049478(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_07_80049030(arg0, 0x01000000);
        func_ovl10_07_80049198(5);
        func_ovl10_07_80049478(0, 0, 0, 0.0f);
        func_ovl10_07_800490F8(arg0, &pos);
        func_ovl10_07_800495D0(12, &pos, 0);
    }
}

void func_ovl10_07_800479D4(void) {
    s32 y;
    s32 i;
    s32 a;
    s32 b;
    s32 out[6];
    s32 *flags;

    i = D_ovl10_07_8004A354;
    D_ovl10_07_8004A3C8 = func_ovl10_07_80048868(func_ovl10_07_80048808());
    D_ovl10_07_8004A3B0[i]->unk40->unk14 += D_ovl10_07_8004A358;
    D_ovl10_07_8004A3C8->unk40->unk14 = D_ovl10_07_8004A3B0[i]->unk40->unk14;
    D_ovl10_07_8004A358 += D_ovl10_07_8004A35C;
    if (D_ovl10_07_8004A4C0 != -1.0f &&
        ((D_ovl10_07_8004A358 > 0.0f && D_ovl10_07_8004A4C0 <= D_ovl10_07_8004A3B0[i]->unk40->unk14) ||
         (D_ovl10_07_8004A358 < 0.0f && D_ovl10_07_8004A3B0[i]->unk40->unk14 <= D_ovl10_07_8004A4C0))) {
        D_ovl10_07_8004A35C = -D_ovl10_07_8004A35C;
        D_ovl10_07_8004A4C0 = -1.0f;
    }
    if (D_ovl10_07_8004A360 != -1.0f &&
        (D_ovl10_07_8004A358 == 0.0f ||
         (D_ovl10_07_8004A358 > 0.0f && D_ovl10_07_8004A360 < D_ovl10_07_8004A3B0[i]->unk40->unk14) ||
         (D_ovl10_07_8004A358 < 0.0f && D_ovl10_07_8004A3B0[i]->unk40->unk14 < D_ovl10_07_8004A360))) {
        flags = func_ovl10_07_80048778();
        if (!(*flags & 2)) {
            func_ovl10_07_80048790(1);
        }
        func_ovl10_07_80045C90();
        D_ovl10_07_8004A3C8->unk70 = 1.6333334f;
        if (D_ovl10_07_8004A358 != 0.0f) {
            D_ovl10_07_8004A3B0[i]->unk40->unk14 = D_ovl10_07_8004A360;
            D_ovl10_07_8004A3C8->unk40->unk14 = D_ovl10_07_8004A360;
        }
        if (D_ovl10_07_8004A3E0[i] == 2) {
            func_ovl10_07_80048680(D_ovl10_07_8004A3B0[i]->unk40->unk10, D_ovl10_07_8004A3B0[i]->unk40->unk14,
                                   D_ovl10_07_8004A3B0[i]->unk40->unk18, out, 2);
            y = out[1];
            func_ovl10_07_800486D0(D_ovl10_07_8004A368[i][0], D_ovl10_07_8004A368[i][1], D_ovl10_07_8004A368[i][2],
                                   D_ovl10_07_8004A368[i][0] + 1, D_ovl10_07_8004A368[i][2] + 1,
                                   D_ovl10_07_8004A368[i][0], y, D_ovl10_07_8004A368[i][2]);
            func_ovl10_07_800486D8(D_ovl10_07_8004A368[i][0], D_ovl10_07_8004A368[i][1], D_ovl10_07_8004A368[i][2],
                                   D_ovl10_07_8004A368[i][0] + 1, D_ovl10_07_8004A368[i][2] + 1, 0);
            D_ovl10_07_8004A430[i] = D_ovl10_07_8004A368[i][1];
            D_ovl10_07_8004A368[i][1] = y;
            if (D_ovl10_07_8004A358 > 0.0f) {
                a = D_ovl10_07_8004A448[i];
                b = D_ovl10_07_8004A460[i];
            } else {
                a = D_ovl10_07_8004A478[i];
                b = D_ovl10_07_8004A490[i];
            }
            func_ovl10_07_80048828(a, 3, 8.5f, b, 1, 1, 1);
            func_ovl10_07_80048EF8(0.1f);
            func_ovl10_07_80048F10(40.0f);
        }
        func_ovl10_07_800486E0(0);
        if (!(*flags & 2)) {
            func_ovl10_07_80048818(0);
        }
        func_ovl10_07_800491F0(0xD0, 0xD0);
    }
}

void func_ovl10_07_800478B0(void) {
    s32 i;

    for (i = 0; i < D_ovl10_07_8004A428; i++) {
        if (D_ovl10_07_8004A3E0[i] == 2 && D_ovl10_07_8004A3F8[i] != D_ovl10_07_8004A340[D_ovl10_07_8004A410[i]]) {
            if (D_ovl10_07_8004A3B0[i] != NULL) {
                func_ovl10_07_80047878(i);
            }
            D_ovl10_07_8004A3F8[i] = D_ovl10_07_8004A340[D_ovl10_07_8004A410[i]];
            func_ovl10_07_8004563C(i);
        }
    }
}

void func_ovl10_07_80047878(s32 arg0) {
    func_ovl10_07_80049040(D_ovl10_07_8004A3B0[arg0]);
    D_ovl10_07_8004A3B0[arg0] = NULL;
}

/* the gate opens or closes */
void func_ovl10_07_80047630(void) {
    s32 i;
    s32 v;
    s32 w;

    i = D_ovl10_07_8004A4E0[D_ovl10_07_80049FA8];
    D_ovl10_07_8004A4D4[i]->unk40->unk18 += D_ovl10_07_8004A5E8[i];
    D_ovl10_07_8004A4D8[i]->unk40->unk18 -= D_ovl10_07_8004A5E8[i];
    if ((D_ovl10_07_8004A5E8[i] < 0.0f && D_ovl10_07_8004A4D4[i]->unk40->unk18 <= D_ovl10_07_8004A5EC[i]) ||
        (D_ovl10_07_8004A5E8[i] > 0.0f && D_ovl10_07_8004A5EC[i] <= D_ovl10_07_8004A4D4[i]->unk40->unk18)) {
        D_ovl10_07_8004A4DC[i] = (D_ovl10_07_8004A4DC[i] + 1) % 2;
        if (D_ovl10_07_8004A4DC[i] != 0) {
            v = 1;
            w = 0;
        } else {
            v = 15;
            w = 1;
        }
        func_ovl10_07_80048660(D_ovl10_07_8004A4C8[i][0], D_ovl10_07_8004A4C8[i][1], D_ovl10_07_8004A4C8[i][2] + 1, v);
        func_ovl10_07_80048660(D_ovl10_07_8004A4C8[i][0], D_ovl10_07_8004A4C8[i][1], D_ovl10_07_8004A4C8[i][2] + 2, v);
        func_ovl10_07_80048660(D_ovl10_07_8004A4C8[i][0], D_ovl10_07_8004A4C8[i][1] + 1, D_ovl10_07_8004A4C8[i][2] + 1, w);
        func_ovl10_07_80048660(D_ovl10_07_8004A4C8[i][0], D_ovl10_07_8004A4C8[i][1] + 1, D_ovl10_07_8004A4C8[i][2] + 2, w);
        D_ovl10_07_8004A4D4[i]->unk40->unk18 = D_ovl10_07_8004A5EC[i];
        D_ovl10_07_8004A4D8[i]->unk40->unk18 = D_ovl10_07_8004A5F0[i];
        func_ovl10_07_80045C90();
        D_ovl10_07_8004A5E4[i] = 0;
        func_ovl10_07_80049700(0xA8);
    }
}

void func_ovl10_07_80047550(void) {
    if (D_ovl10_07_8004ADE4 != 0) {
        func_ovl10_07_80049478(0xFF, 0, 0, D_ovl10_07_8004AEF0);
    }
    D_ovl10_07_8004AEF0 += D_ovl10_07_8004AEF4;
    if (D_ovl10_07_8004AEF4 == 2 && D_ovl10_07_8004AEF0 >= 60) {
        D_ovl10_07_8004AEF4 = -2;
        D_ovl10_07_8004AEF0 = 60;
    }
    if (D_ovl10_07_8004AEF4 == -2 && D_ovl10_07_8004AEF0 <= 0) {
        D_ovl10_07_8004AEF4 = 2;
        D_ovl10_07_8004AEF0 = 0;
        func_ovl10_07_80049700(0x9E);
    }
    if (D_ovl10_07_8004ADE4 == 0) {
        func_ovl10_07_80045C90();
    }
}

void func_ovl10_07_80047330(void) {
    s32 i;

    i = D_ovl10_07_8004ADF0[D_ovl10_07_80049FA8];
    if (D_ovl10_07_8004ADE8 == 0) {
        D_ovl10_07_8004AD08[i] += D_ovl10_07_8004AC98[i];
        D_ovl10_07_8004A5F8[i]->unk40->unk36 = D_ovl10_07_8004AD08[i];
        D_ovl10_07_8004A668[i]->unk40->unk36 = D_ovl10_07_8004AD08[i] * 0.5f;
        D_ovl10_07_8004A668[i]->unk40->unk2C += D_ovl10_07_8004AD78[i];
        if (D_ovl10_07_8004AC98[i] > 0.0f && D_ovl10_07_8004A5F8[i]->unk40->unk36 >= 256) {
            D_ovl10_07_8004A5F8[i]->unk40->unk36 = 255;
            D_ovl10_07_8004A668[i]->unk40->unk36 = 128;
            func_ovl10_07_80045C90();
        }
        if (D_ovl10_07_8004AC98[i] < 0.0f && D_ovl10_07_8004A5F8[i]->unk40->unk36 < 0) {
            if (D_ovl10_07_8004A5F8[i] != NULL) {
                func_ovl10_07_80049040(D_ovl10_07_8004A5F8[i]);
                func_ovl10_07_80049040(D_ovl10_07_8004A668[i]);
                D_ovl10_07_8004A5F8[i] = NULL;
                func_ovl10_07_80046DC4(i, 0);
            }
            func_ovl10_07_80045C90();
        }
    } else {
        func_ovl10_07_80045C90();
    }
}

void func_ovl10_07_8004713C(void) {
    s32 i;
    s32 j;
    s32 found;
    s32 k;

    i = D_ovl10_07_8004A900[D_ovl10_07_80049FA8];
    found = -1;
    j = 0;
    do {
        if (D_ovl10_07_8004AA08[i] == D_ovl10_07_8004AAE8[i][j]) {
            D_ovl10_07_8004A820[i] = 0;
            found = 0;
            D_ovl10_07_8004A890[i]++;
            func_ovl10_07_80046E28(i, 1);
        }
        j++;
    } while (D_ovl10_07_8004AAE8[i][j] != -1 && found == -1);
    if (D_ovl10_07_8004A890[i] != 0) {
        D_ovl10_07_8004A820[i]++;
        if (D_ovl10_07_8004A820[i] == 80) {
            D_ovl10_07_8004A890[i] = 0;
            func_ovl10_07_80046E28(i, 0);
        }
    }
    if (D_ovl10_07_8004ADE8 != 0) {
        for (k = 0; k < D_ovl10_07_8004AA00; k++) {
            if (D_ovl10_07_8004A5F8[k] != NULL) {
                func_ovl10_07_80049040(D_ovl10_07_8004A5F8[k]);
                func_ovl10_07_80049040(D_ovl10_07_8004A668[k]);
                D_ovl10_07_8004A5F8[k] = NULL;
                func_ovl10_07_80046DC4(k, 0);
                D_ovl10_07_8004A890[k] = 0;
            }
        }
        func_ovl10_07_80045C90();
    }
    D_ovl10_07_8004AA08[i]++;
    if (D_ovl10_07_8004AA08[i] == D_ovl10_07_8004AA78[i]) {
        D_ovl10_07_8004AA08[i] = 40;
    }
}

void func_ovl10_07_80046E28(s32 arg0, s32 arg1) {
    Vec3f pos;
    Vec3f pos2;

    D_ovl10_07_8004ADF0[func_ovl10_07_800430F4(func_ovl10_07_80047330)] = arg0;
    if (arg1 != 0) {
        D_ovl10_07_8004A5F8[arg0] = func_ovl10_07_80049050(0xBE, 0x01080000, 0x10, 0);
        func_ovl10_07_80048688(D_ovl10_07_8004A6D8[arg0][0], D_ovl10_07_8004A6D8[arg0][1],
                               D_ovl10_07_8004A6D8[arg0][2], &pos, 0);
        D_ovl10_07_8004A5F8[arg0]->unk40->unk10 = pos.x;
        D_ovl10_07_8004A5F8[arg0]->unk40->unk14 = pos.y + 10.0f;
        D_ovl10_07_8004A5F8[arg0]->unk40->unk18 = pos.z;
        D_ovl10_07_8004A5F8[arg0]->unk40->unk36 = 0;
        D_ovl10_07_8004AC98[arg0] = 12.0f;
        D_ovl10_07_8004AD08[arg0] = 0.0f;
        D_ovl10_07_8004A668[arg0] = func_ovl10_07_80049050(0x2A7, 0x01080000, 0x10, 0);
        func_ovl10_07_80048688(D_ovl10_07_8004A6D8[arg0][0], D_ovl10_07_8004A6D8[arg0][1],
                               D_ovl10_07_8004A6D8[arg0][2], &pos, 0);
        D_ovl10_07_8004A668[arg0]->unk40->unk10 = pos.x + 40.0f;
        D_ovl10_07_8004A668[arg0]->unk40->unk14 = pos.y;
        D_ovl10_07_8004A668[arg0]->unk40->unk18 = pos.z + 40.0f;
        D_ovl10_07_8004A668[arg0]->unk40->unk28 = 2.0f;
        D_ovl10_07_8004A668[arg0]->unk40->unk2C = 2.0f;
        D_ovl10_07_8004A668[arg0]->unk40->unk30 = 2.0f;
        D_ovl10_07_8004A668[arg0]->unk40->unkC |= 0x8000;
        func_ovl10_07_80048D30(D_ovl10_07_8004A668[arg0]->unk40, 2);
        func_ovl10_07_80048D38(D_ovl10_07_8004A668[arg0]->unk40, 0x2A8, 0, 0);
        func_ovl10_07_80048D38(D_ovl10_07_8004A668[arg0]->unk40, 0x2A8, 1, 1);
        D_ovl10_07_8004A668[arg0]->unk40->unk36 = 0;
        D_ovl10_07_8004AD78[arg0] = 0.1f;
        func_ovl10_07_80046DC4(arg0, 1);
        func_ovl10_07_800490F8(D_ovl10_07_8004A668[arg0], &pos2);
        func_ovl10_07_80049728(0xAA, &pos2);
    } else {
        D_ovl10_07_8004AC98[arg0] = -6.0f;
        D_ovl10_07_8004AD08[arg0] = 255.0f;
        D_ovl10_07_8004AD78[arg0] = -0.1f;
    }
}

void func_ovl10_07_80046DC4(s32 arg0, s32 arg1) {
    s32 v;

    if (arg1 != 0) {
        v = 1;
    } else {
        v = 11;
    }
    func_ovl10_07_800486D8(D_ovl10_07_8004A6D8[arg0][0], D_ovl10_07_8004A6D8[arg0][1], D_ovl10_07_8004A6D8[arg0][2],
                           D_ovl10_07_8004A6D8[arg0][0] + 1, D_ovl10_07_8004A6D8[arg0][2] + 1, v);
}

void func_ovl10_07_80046AA8(void) {
    s32 i;
    s32 j;
    s32 v;

    i = D_ovl10_07_80049CD8[D_ovl10_07_80049FA8];
    D_ovl10_07_80049DE0[i]--;
    func_ovl10_07_80046A08(i);
    if (D_ovl10_07_80049DE0[i] == 0) {
        D_ovl10_07_80049CA8[i] = (D_ovl10_07_80049CA8[i] + 2) & 3;
        if (D_ovl10_07_80049CA8[i] & 2) {
            func_ovl10_07_80043914(i);
            D_ovl10_07_80049DE0[i] = func_ovl10_07_80049338(60) + 90;
            v = 9;
        } else {
            func_ovl10_07_8004389C(i);
            v = 1;
            D_ovl10_07_80049DE0[i] = 120;
        }
        if (D_ovl10_07_80049C78[i] & 1) {
            for (j = 0; j < D_ovl10_07_80049E70[i]; j++) {
                func_ovl10_07_80048660(D_ovl10_07_80049BF0[i][0] + j, D_ovl10_07_80049BF0[i][1], D_ovl10_07_80049BF0[i][2], v);
            }
        } else {
            for (j = 0; j < D_ovl10_07_80049E70[i]; j++) {
                func_ovl10_07_80048660(D_ovl10_07_80049BF0[i][0], D_ovl10_07_80049BF0[i][1], D_ovl10_07_80049BF0[i][2] + j, v);
            }
        }
        if (D_ovl10_07_8004ADE4 != 0) {
            D_ovl10_07_80049DE0[i] = 30;
        }
    }
    if (D_ovl10_07_80049E10[i] != 0) {
        if (D_ovl10_07_80049CA8[i] & 2) {
            func_ovl10_07_8004389C(i);
            if (D_ovl10_07_80049C78[i] & 1) {
                for (j = 0; j < D_ovl10_07_80049E70[i]; j++) {
                    func_ovl10_07_80048660(D_ovl10_07_80049BF0[i][0] + j, D_ovl10_07_80049BF0[i][1], D_ovl10_07_80049BF0[i][2], 1);
                }
            } else {
                for (j = 0; j < D_ovl10_07_80049E70[i]; j++) {
                    func_ovl10_07_80048660(D_ovl10_07_80049BF0[i][0], D_ovl10_07_80049BF0[i][1], D_ovl10_07_80049BF0[i][2] + j, 1);
                }
            }
        }
        func_ovl10_07_80045C90();
    }
}

void func_ovl10_07_80046A08(s32 arg0) {
    f32 d;

    if (D_ovl10_07_80049CA8[arg0] & 1) {
        d = func_ovl10_07_80046798(arg0);
        if (D_ovl10_07_80049E6C == -1 && (D_ovl10_07_80049CA8[arg0] & 2) && d <= 300.0f) {
            func_ovl10_07_800467F0(arg0, 1);
        } else {
            func_ovl10_07_800467F0(arg0, 0);
        }
    }
}

void func_ovl10_07_80046954(void) {
    s32 i;
    f32 d;

    i = D_ovl10_07_80049CD8[D_ovl10_07_80049FA8];
    d = func_ovl10_07_80046798(i);
    if (D_ovl10_07_80049E6C == -1 && d <= 300.0f) {
        func_ovl10_07_800467F0(i, 1);
    } else {
        func_ovl10_07_800467F0(i, 0);
    }
    if (D_ovl10_07_80049E10[i] != 0) {
        func_ovl10_07_80045C90();
    }
}

void func_ovl10_07_800467F0(s32 arg0, s32 arg1) {
    s32 pad[2];
    Vec3f pos;
    s32 i;
    s32 n;

    n = 0;
    for (i = 0; i < D_ovl10_07_80049DD8; i++) {
        if ((D_ovl10_07_80049CA8[i] & 2) && func_ovl10_07_80046798(i) <= 300.0f) {
            n++;
        }
    }
    if (arg1 != 0 && n == 1 && D_ovl10_07_80049E6C == -1) {
        func_ovl10_07_800490F8(D_ovl10_07_80049BC0[arg0], &pos);
        D_ovl10_07_80049E6C = func_ovl10_07_80049728(0x9D, &pos);
    }
    if (arg1 == 0 && n == 0 && D_ovl10_07_80049E6C != -1) {
        func_ovl10_07_80043034();
    }
}

f32 func_ovl10_07_80046798(s32 arg0) {
    s32 pad;
    Vec3f a;
    Vec3f b;

    func_ovl10_07_800490F8(D_ovl10_07_80049BC0[arg0], &a);
    func_ovl10_07_800490F8(func_ovl10_07_80048868(func_ovl10_07_80048808()), &b);
    return func_ovl10_07_80048FD0(&a, &b);
}

void func_ovl10_07_800465E0(void) {
    s32 i;

    i = D_ovl10_07_8004A148[D_ovl10_07_80049FA8];
    D_ovl10_07_8004A0B8[i]->unk40->unk28 += D_ovl10_07_8004A280[i];
    D_ovl10_07_8004A0B8[i]->unk40->unk2C += D_ovl10_07_8004A280[i];
    D_ovl10_07_8004A0B8[i]->unk40->unk30 += D_ovl10_07_8004A280[i];
    if ((D_ovl10_07_8004A280[i] > 0.0f && D_ovl10_07_8004A298[i] <= D_ovl10_07_8004A0B8[i]->unk40->unk28) ||
        (D_ovl10_07_8004A280[i] < 0.0f && D_ovl10_07_8004A0B8[i]->unk40->unk28 <= D_ovl10_07_8004A298[i])) {
        D_ovl10_07_8004A0B8[i]->unk40->unk28 = D_ovl10_07_8004A298[i];
        D_ovl10_07_8004A0B8[i]->unk40->unk2C = D_ovl10_07_8004A298[i];
        D_ovl10_07_8004A0B8[i]->unk40->unk30 = D_ovl10_07_8004A298[i];
        if (D_ovl10_07_8004A130[i] == 0) {
            func_ovl10_07_800465A8(i);
        }
        func_ovl10_07_80044DC8(i);
        D_ovl10_07_8004A268[i] = 0;
        func_ovl10_07_80045C90();
    }
}

void func_ovl10_07_800465A8(s32 arg0) {
    func_ovl10_07_80049040(D_ovl10_07_8004A0B8[arg0]);
    D_ovl10_07_8004A0B8[arg0] = NULL;
}

void func_ovl10_07_800462DC(void) {
    Vec3f pos;

    if (D_ovl10_07_8004A2BC != 0) {
        D_ovl10_07_8004A2B0->unk40->unk10 += D_ovl10_07_8004A2CC;
        D_ovl10_07_8004A2B0->unk40->unk1C += D_ovl10_07_8004A2D0;
        func_ovl10_07_800490A8(D_ovl10_07_8004A2B0);
        if (D_ovl10_07_8004A2B0->unk6C == 0.0f) {
            if (D_ovl10_07_8004A2C0 == 0) {
                func_ovl10_07_800490F8(D_ovl10_07_8004A2B0, &pos);
                func_ovl10_07_800495D0(0xE, &pos, 0);
                D_ovl10_07_8004A2CC = 5.0f;
                D_ovl10_07_8004A2D0 = 20.0f;
                func_ovl10_07_80048D50(D_ovl10_07_8004A2B0->unk40, 0x10, 0);
                D_ovl10_07_8004A2B0->unk40->unk48->unk4->unk8 |= 0x20;
                D_ovl10_07_8004A2B0->unk40->unk48->unk4->unk8 |= 0x40;
                D_ovl10_07_8004A2B0->unk40->unk48->unk4->unk4 =
                    func_ovl10_07_80048D68(D_ovl10_07_8004A2B0->unk40, 0) - 0.1f;
                D_ovl10_07_8004A2B0->unk68 = 41.0f;
                pos.x = 0.0f;
                pos.z = 0.0f;
                pos.y = 80.0f;
                D_ovl10_07_8004A2C4 = func_ovl10_07_800495D0(5, &pos, D_ovl10_07_8004A2B0);
                D_ovl10_07_8004A2C8 = func_ovl10_07_80049700(0x21);
            }
            if (D_ovl10_07_8004A2C0 == 1) {
                D_ovl10_07_8004A2CC = 0.0f;
                D_ovl10_07_8004A2D0 = 0.0f;
                D_ovl10_07_8004A2B0->unk40->unk1C = 0.0f;
                func_ovl10_07_80048D50(D_ovl10_07_8004A2B0->unk40, 0x11, 0);
                func_ovl10_07_80049028(D_ovl10_07_8004A2B0, 0x0C000000);
                D_ovl10_07_8004A2B0->unk40->unk48->unk4->unk8 = 0;
                func_ovl10_07_80048D80(D_ovl10_07_8004A2B0->unk40, 4, 0xC);
                func_ovl10_07_80048D80(D_ovl10_07_8004A2B0->unk40, 5, 0xD);
                func_ovl10_07_80045D5C(180);
                func_ovl10_07_80045D40(func_ovl10_07_80046210);
            }
            if (D_ovl10_07_8004A2C0 < 2) {
                D_ovl10_07_8004A2C0++;
            }
        }
    }
}

void func_ovl10_07_80046210(void) {
    func_ovl10_07_800495D8(D_ovl10_07_8004A2C4);
    func_ovl10_07_80048D80(D_ovl10_07_8004A2B0->unk40, 4, 4);
    func_ovl10_07_80048D80(D_ovl10_07_8004A2B0->unk40, 5, 5);
    func_ovl10_07_80049030(D_ovl10_07_8004A2B0, 0x08000000);
    func_ovl10_07_80048D50(D_ovl10_07_8004A2B0->unk40, 0x18, 0);
    func_ovl10_07_80045D5C(90);
    func_ovl10_07_80049730(D_ovl10_07_8004A2C8);
    func_ovl10_07_80049700(0x1A2);
    func_ovl10_07_80045D40(func_ovl10_07_80046104);
}

void func_ovl10_07_80046104(void) {
    UnkStructA *obj;

    obj = func_ovl10_07_80048868(func_ovl10_07_80048808());
    obj->unk40->unk10 = D_ovl10_07_8004A2B0->unk40->unk10;
    obj->unk40->unk14 = D_ovl10_07_8004A2B0->unk40->unk14;
    obj->unk40->unk18 = D_ovl10_07_8004A2B0->unk40->unk18;
    func_ovl10_07_80049040(D_ovl10_07_8004A2B0);
    D_ovl10_07_8004A2B0 = NULL;
    func_ovl10_07_80049028(obj, 0x09000011);
    func_ovl10_07_80048D50(obj->unk40, 0, 0);
    func_ovl10_07_80045C90();
    *func_ovl10_07_800488E8(func_ovl10_07_80048808()) &= ~0x2020;
    func_ovl10_07_80048818(0);
    func_ovl10_07_80048798(0);
    func_ovl10_07_80048790(1);
}

void func_ovl10_07_80046088(void) {
    func_ovl10_07_80048790(0);
    func_ovl10_07_80048798(1);
    func_ovl10_07_80048818(1);
    func_ovl10_07_800495C8(2, 200.0f, 4000.0f, 1400.0f, 0);
    func_ovl10_07_80049700(0x45);
    func_ovl10_07_80045D5C(10);
    func_ovl10_07_80045D40(func_ovl10_07_8004603C);
}

void func_ovl10_07_8004603C(void) {
    func_ovl10_07_80045E2C();
    func_ovl10_07_80045D5C(60);
    func_ovl10_07_80045D40(func_ovl10_07_80045DE0);
}

void func_ovl10_07_80045E2C(void) {
    s32 i;

    D_ovl10_07_8004A2B0 = func_ovl10_07_80049050(0x49, 0x0D000000, 0xD0, 0);
    D_ovl10_07_8004A2B0->unk40->unk10 = 200.0f;
    D_ovl10_07_8004A2B0->unk40->unk14 = 4000.0f;
    D_ovl10_07_8004A2B0->unk40->unk18 = 1400.0f;
    D_ovl10_07_8004A2B0->unk40->unk20 = 90.0f;
    D_ovl10_07_8004A2B0->unk30 = 1;
    D_ovl10_07_8004A2B0->unk34 = 30.0f;
    D_ovl10_07_8004A2B0->unk38 = 51.0f;
    D_ovl10_07_8004A2B0->unk6C = 0.0f;
    D_ovl10_07_8004A2B0->unk70 = 1.6333334f;
    D_ovl10_07_8004A2B0->unk68 = 0.0f;
    func_ovl10_07_80048D48(D_ovl10_07_8004A2B0->unk40, 2);
    func_ovl10_07_80048D30(D_ovl10_07_8004A2B0->unk40, 0xC);
    for (i = 0; i != 12; i++) {
        func_ovl10_07_80048D38(D_ovl10_07_8004A2B0->unk40, 0x4A, i, i);
    }
    func_ovl10_07_80048D50(D_ovl10_07_8004A2B0->unk40, 0x14, 0);
    D_ovl10_07_8004A2B0->unk40->unk48->unk4->unk8 |= 0x20;
    D_ovl10_07_8004A2B0->unk40->unk48->unk4->unk8 |= 0x40;
    D_ovl10_07_8004A2B0->unk40->unk48->unk4->unk4 = func_ovl10_07_80048D68(D_ovl10_07_8004A2B0->unk40, 0) - 0.1f;
    D_ovl10_07_8004A2B0->unk40->unk14 = 4000.0f;
    func_ovl10_07_80049060(D_ovl10_07_8004A2B0);
}

void func_ovl10_07_80045DE0(void) {
    func_ovl10_07_80045D78();
    func_ovl10_07_80045D5C(60);
    func_ovl10_07_80045D40(func_ovl10_07_80045CD4);
}

void func_ovl10_07_80045D78(void) {
    D_ovl10_07_8004A2B4 = func_ovl10_07_80049050(0x4E, 0x11200000, 0xD0, D_ovl10_07_8004A2B0);
    D_ovl10_07_8004A2B4->unk4C = 70.0f;
    D_ovl10_07_8004A2B4->unk50 = 200.0f;
    D_ovl10_07_8004A2B4->unk54 = 0.0f;
}

void func_ovl10_07_80045D5C(s32 arg0) {
    D_ovl10_07_80049EA8[D_ovl10_07_80049FA8] = arg0;
}

void func_ovl10_07_80045D40(void (*arg0)(void)) {
    D_ovl10_07_80049FB0[D_ovl10_07_80049FA8] = arg0;
}

void func_ovl10_07_80045CD4(void) {
    func_ovl10_07_80045CAC();
    func_ovl10_07_800430F4(func_ovl10_07_800462DC);
    func_ovl10_07_80049700(0x1B);
    func_ovl10_07_80048868(func_ovl10_07_80048808())->unk70 = 1.6333334f;
    func_ovl10_07_80045C90();
}

void func_ovl10_07_80045CAC(void) {
    func_ovl10_07_80049040(D_ovl10_07_8004A2B4);
}

/* clears the running task */
void func_ovl10_07_80045C90(void) {
    D_ovl10_07_80049FB0[D_ovl10_07_80049FA8] = NULL;
}

void func_ovl10_07_80045AE8(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl10_07_800458C4();
            break;
        case 16:
            func_ovl10_07_80044BA8();
            break;
        case 17:
            func_ovl10_07_80044AC0();
            break;
        case 18:
            func_ovl10_07_800448BC();
            break;
        case 4:
            func_ovl10_07_8004489C();
            break;
        case 5:
            func_ovl10_07_80044824();
            break;
        case 0x52:
            func_ovl10_07_80044704();
            break;
        case 0x53:
            func_ovl10_07_80043E60();
            break;
        case 15:
            func_ovl10_07_8004376C();
            break;
        case 0x50:
            func_ovl10_07_8004374C();
            break;
        case 1:
            func_ovl10_07_80043084();
            break;
        case 3:
            func_ovl10_07_80043010();
            break;
    }
}

void func_ovl10_07_800458C4(void) {
    Vec3f pos;

    func_ovl10_07_800494E0(D_ovl10_07_80049940);
    func_ovl10_07_80049688(0, 0, 0xDE);
    func_ovl10_07_80049688(1, 2, 0xE0);
    func_ovl10_07_80049688(2, 3, 0xE1);
    func_ovl10_07_80049688(3, 0x11, 0xEF);
    func_ovl10_07_80049688(4, 0x18, 0xF6);
    func_ovl10_07_80048628(0x1E9);
    func_ovl10_07_80048630(0x1EA, 0.0f, 0.0f, 0.0f, 0x60, 0);
    func_ovl10_07_80048630(0xC7, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_07_80048630(0xC7, 0.0f, 12000.0f, 0.0f, 0x50, 0);
    func_ovl10_07_80048640(0x1F3);
    func_ovl10_07_800494B8(0x3C6, 0x3E8, 0, 0xFF, 0xFF);
    func_ovl10_07_800494C8(0, 0xFF, 0xFF);
    func_ovl10_07_800487D8();
    func_ovl10_07_80045758(D_ovl10_07_800499EC);
    func_ovl10_07_80045588(D_ovl10_07_80049A1C);
    func_ovl10_07_800452A8(D_ovl10_07_80049A40);
    func_ovl10_07_80044FD8(D_ovl10_07_80049964);
    func_ovl10_07_80044E8C(D_ovl10_07_800499B8);
    func_ovl10_07_80044C5C(D_ovl10_07_80049A54);
    func_ovl10_07_80048710(func_ovl10_07_80047E28);
    func_ovl10_07_80044BE0();
    D_ovl10_07_8004A2BC = 0;
    func_ovl10_07_80048688(13, 0, 8, &pos, 0);
    D_ovl10_07_8004A2B8 = func_ovl10_07_80049050(0x323, 0x01000010, 0xC0, 0);
    D_ovl10_07_8004A2B8->unk40->unk10 = pos.x;
    D_ovl10_07_8004A2B8->unk40->unk14 = pos.y;
    D_ovl10_07_8004A2B8->unk40->unk18 = pos.z;
    D_ovl10_07_8004A2B8->unk40->unk20 = 315.0f;
    func_ovl10_07_80049060(D_ovl10_07_8004A2B8);
}

/* reads records of 11 words up to a -1 */
void func_ovl10_07_80045758(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_07_8004A368[i][0] = arg0[0];
        D_ovl10_07_8004A368[i][1] = arg0[1];
        D_ovl10_07_8004A368[i][2] = arg0[2];
        D_ovl10_07_8004A430[i] = arg0[3];
        D_ovl10_07_8004A3E0[i] = arg0[4];
        D_ovl10_07_8004A3F8[i] = arg0[5];
        D_ovl10_07_8004A410[i] = arg0[6];
        D_ovl10_07_8004A448[i] = arg0[7];
        D_ovl10_07_8004A460[i] = arg0[8];
        D_ovl10_07_8004A478[i] = arg0[9];
        D_ovl10_07_8004A490[i] = arg0[10];
        arg0 += 11;
        func_ovl10_07_8004563C(i);
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_07_8004A428 = i;
}

void func_ovl10_07_800443E4(s32 arg0, s32 arg1) {
    s32 sp38[4] = { 0xBF, 0xC0, 0xC1, 0xC4 };
    Vec3f pos;

    if (arg1 == 1) {
        D_ovl10_07_8004A308[arg0] =
            func_ovl10_07_80049050(sp38[D_ovl10_07_8004A320[arg0] - 1], 0x01000000, 0xD0, 0);
        func_ovl10_07_80048688(D_ovl10_07_8004A2D8[arg0][0], D_ovl10_07_8004A2D8[arg0][1],
                               D_ovl10_07_8004A2D8[arg0][2], &pos, 0);
        D_ovl10_07_8004A308[arg0]->unk40->unk10 = pos.x;
        D_ovl10_07_8004A308[arg0]->unk40->unk14 = pos.y;
        D_ovl10_07_8004A308[arg0]->unk40->unk18 = pos.z;
    } else {
        func_ovl10_07_80049040(D_ovl10_07_8004A308[arg0]);
        D_ovl10_07_8004A308[arg0] = NULL;
    }
}

void func_ovl10_07_8004563C(s32 arg0) {
    Vec3f pos;
    s32 sp2C[2] = { 0xCA, 0xB2 };

    D_ovl10_07_8004A3B0[arg0] = func_ovl10_07_80049050(sp2C[D_ovl10_07_8004A3F8[arg0]], 0x01000000, 0xD0, 0);
    func_ovl10_07_80048688(D_ovl10_07_8004A368[arg0][0], D_ovl10_07_8004A368[arg0][1], D_ovl10_07_8004A368[arg0][2],
                           &pos, 0);
    D_ovl10_07_8004A3B0[arg0]->unk40->unk10 = pos.x;
    D_ovl10_07_8004A3B0[arg0]->unk40->unk14 = pos.y;
    D_ovl10_07_8004A3B0[arg0]->unk40->unk18 = pos.z;
}

void func_ovl10_07_80045588(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_07_8004A2D8[i][0] = arg0[0];
        D_ovl10_07_8004A2D8[i][1] = arg0[1];
        D_ovl10_07_8004A2D8[i][2] = arg0[2];
        D_ovl10_07_8004A320[i] = arg0[3];
        D_ovl10_07_8004A330[i] = 0;
        arg0 += 4;
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_07_8004A318 = i;
    for (i = 1; i < 5; i++) {
        D_ovl10_07_8004A340[i] = 0;
    }
}

/* reads the gates: records of 4 words up to a -1 */
void func_ovl10_07_800452A8(s32 *arg0) {
    s32 i;
    s32 v;
    Vec3f pos;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_07_8004A4C8[i][0] = arg0[0];
            D_ovl10_07_8004A4C8[i][1] = arg0[1];
            D_ovl10_07_8004A4C8[i][2] = arg0[2];
            D_ovl10_07_8004A4DC[i] = arg0[3];
            arg0 += 4;
            func_ovl10_07_80048688(D_ovl10_07_8004A4C8[i][0], D_ovl10_07_8004A4C8[i][1], D_ovl10_07_8004A4C8[i][2],
                                   &pos, 0);
            D_ovl10_07_8004A4D4[i] = func_ovl10_07_80049050(0xC2, 0x01000110, 0xD0, 0);
            D_ovl10_07_8004A4D4[i]->unk40->unk10 = pos.x;
            D_ovl10_07_8004A4D4[i]->unk40->unk14 = pos.y;
            D_ovl10_07_8004A4D4[i]->unk40->unk18 = pos.z + 50.0f;
            D_ovl10_07_8004A4D4[i]->unk34 = 50.0f;
            D_ovl10_07_8004A4D4[i]->unk38 = 50.0f;
            D_ovl10_07_8004A4D8[i] = func_ovl10_07_80049050(0xC2, 0x01000110, 0xD0, 0);
            D_ovl10_07_8004A4D8[i]->unk40->unk10 = pos.x;
            D_ovl10_07_8004A4D8[i]->unk40->unk14 = pos.y;
            D_ovl10_07_8004A4D8[i]->unk40->unk18 = pos.z + 250.0f;
            D_ovl10_07_8004A4D8[i]->unk40->unk20 = 180.0f;
            D_ovl10_07_8004A4D8[i]->unk34 = 50.0f;
            D_ovl10_07_8004A4D8[i]->unk38 = 50.0f;
            if (D_ovl10_07_8004A4DC[i] != 0) {
                v = 1;
                D_ovl10_07_8004A4D4[i]->unk40->unk18 -= 100.0f;
                D_ovl10_07_8004A4D8[i]->unk40->unk18 += 100.0f;
            } else {
                v = 15;
            }
            func_ovl10_07_80048660(D_ovl10_07_8004A4C8[i][0], D_ovl10_07_8004A4C8[i][1], D_ovl10_07_8004A4C8[i][2] + 1, v);
            func_ovl10_07_80048660(D_ovl10_07_8004A4C8[i][0], D_ovl10_07_8004A4C8[i][1], D_ovl10_07_8004A4C8[i][2] + 2, v);
            D_ovl10_07_8004A5E4[i] = 0;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_07_8004A5E0 = i;
}

void func_ovl10_07_80044FD8(s32 *arg0) {
    s32 i;
    s32 j;
    s32 flags;
    s32 pad;
    Vec3f pos;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_07_80049BF0[i][0] = arg0[0];
            D_ovl10_07_80049BF0[i][1] = arg0[1];
            D_ovl10_07_80049BF0[i][2] = arg0[2];
            flags = arg0[3];
            D_ovl10_07_80049C78[i] = flags & 0xF;
            D_ovl10_07_80049E70[i] = flags >> 4;
            D_ovl10_07_80049E40[i] = arg0[4];
            arg0 += 5;
            func_ovl10_07_80048688(D_ovl10_07_80049BF0[i][0], D_ovl10_07_80049BF0[i][1], D_ovl10_07_80049BF0[i][2],
                                   &pos, 0);
            D_ovl10_07_80049BC0[i] = func_ovl10_07_80049050(0xBD, 0, 0xD0, 0);
            D_ovl10_07_80049BC0[i]->unk40->unk10 = pos.x;
            D_ovl10_07_80049BC0[i]->unk40->unk14 = pos.y;
            D_ovl10_07_80049BC0[i]->unk40->unk18 = pos.z;
            if (D_ovl10_07_80049C78[i] & 2) {
                D_ovl10_07_80049BC0[i]->unk40->unk10 = pos.x + 5.0f;
                D_ovl10_07_80049BC0[i]->unk40->unk20 = 270.0f;
            } else {
                D_ovl10_07_80049BC0[i]->unk40->unk18 = pos.z - 5.0f;
            }
            func_ovl10_07_80048D70(D_ovl10_07_80049BC0[i]->unk40, 0, 0x28, 0x190, 0, 0);
            D_ovl10_07_80049CA8[i] = 0;
            if (D_ovl10_07_80049C78[i] & 1) {
                for (j = 0; j < D_ovl10_07_80049E70[i]; j++) {
                    func_ovl10_07_80048660(D_ovl10_07_80049BF0[i][0] + j, D_ovl10_07_80049BF0[i][1], D_ovl10_07_80049BF0[i][2], 1);
                }
            } else {
                for (j = 0; j < D_ovl10_07_80049E70[i]; j++) {
                    func_ovl10_07_80048660(D_ovl10_07_80049BF0[i][0] + j, D_ovl10_07_80049BF0[i][1], D_ovl10_07_80049BF0[i][2], 1);
                }
            }
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_07_80049DD8 = i;
    D_ovl10_07_80049E6C = -1;
}

void func_ovl10_07_80044E8C(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_07_8004A0D0[i][0] = arg0[0];
            D_ovl10_07_8004A0D0[i][1] = arg0[1];
            D_ovl10_07_8004A0D0[i][2] = arg0[2];
            D_ovl10_07_8004A118[i] = arg0[3];
            D_ovl10_07_8004A250[i] = arg0[4];
            D_ovl10_07_8004A130[i] = arg0[5];
            arg0 += 6;
            D_ovl10_07_8004A0B8[i] = NULL;
            if (D_ovl10_07_8004A130[i] != 0) {
                func_ovl10_07_80043EEC(i);
            }
            func_ovl10_07_80044DC8(i);
            D_ovl10_07_8004A268[i] = 0;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_07_8004A248 = i;
}

void func_ovl10_07_80044DC8(s32 arg0) {
    s32 v;
    s32 w;
    s32 t;
    s32 h;
    s32 pad;

    if (D_ovl10_07_8004A130[arg0] != 0) {
        v = 1;
    } else {
        v = 0;
    }
    if (D_ovl10_07_8004A118[arg0] & 4) {
        w = 6;
        h = 3;
    }
    if (D_ovl10_07_8004A118[arg0] & 8) {
        w = 5;
        h = 1;
    }
    if (D_ovl10_07_8004A118[arg0] & 2) {
        t = h;
        h = w;
        w = t;
    }
    func_ovl10_07_800486D8(D_ovl10_07_8004A0D0[arg0][0], D_ovl10_07_8004A0D0[arg0][1], D_ovl10_07_8004A0D0[arg0][2],
                           D_ovl10_07_8004A0D0[arg0][0] + w, D_ovl10_07_8004A0D0[arg0][2] + h, v);
}

void func_ovl10_07_80044C5C(s32 *arg0) {
    s32 i;
    s32 j;
    s32 n;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_07_8004A6D8[i][0] = arg0[0];
            D_ovl10_07_8004A6D8[i][1] = arg0[1];
            D_ovl10_07_8004A6D8[i][2] = arg0[2];
            D_ovl10_07_8004AA78[i] = arg0[3];
            n = arg0[4];
            arg0 += 5;
            for (j = 0; j < n; j++) {
                D_ovl10_07_8004AAE8[i][j] = *arg0;
                arg0++;
            }
            D_ovl10_07_8004AAE8[i][n] = -1;
            D_ovl10_07_8004A890[i] = 0;
            D_ovl10_07_8004A5F8[i] = NULL;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_07_8004AA00 = i;
    D_ovl10_07_8004ADE4 = 0;
    D_ovl10_07_8004ADE8 = 0;
    D_ovl10_07_8004ADEC = 0;
    func_ovl10_07_80049478(0, 0, 0, 0.0f);
}

void func_ovl10_07_80044BE0(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_07_80049FB0[i] = NULL;
        D_ovl10_07_80049EA8[i] = 0;
    }
    func_ovl10_07_80049178(func_ovl10_07_8004809C, 0, 0, 0, 0x110);
}

void func_ovl10_07_80044BA8(void) {
    func_ovl10_07_800487E0(2, 0, 0xE);
    func_ovl10_07_80048820(0x40);
    D_ovl10_07_80049E9C = 3;
}

void func_ovl10_07_80044AC0(void) {
    D_ovl10_07_8004A354 = 0;
    D_ovl10_07_8004A3CC = 1;
    D_ovl10_07_8004A4A8 = 1100.0f;
    D_ovl10_07_8004A4AC = 270.0f;
    D_ovl10_07_8004A3D0 = 0x2B;
    D_ovl10_07_8004A3D4 = 0x13;
    D_ovl10_07_8004A4B0 = -21.0f;
    D_ovl10_07_8004A4B4 = 0.2f;
    D_ovl10_07_8004A4B8 = 49.0f;
    D_ovl10_07_8004A4BC = 50.0f;
    func_ovl10_07_8004495C();
    D_ovl10_07_8004A330[1] = 1;
    func_ovl10_07_800443E4(1, 1);
    D_ovl10_07_8004A340[2] = 1;
    func_ovl10_07_80044268();
    func_ovl10_07_800441C4();
    func_ovl10_07_80044318();
    D_ovl10_07_80049E9C = 1;
}

void func_ovl10_07_8004495C(void) {
    f32 y;

    D_ovl10_07_8004A4C0 = -1.0f;
    y = func_ovl10_07_800486C8(D_ovl10_07_8004A3CC);
    func_ovl10_07_800487E0(D_ovl10_07_8004A3D0, D_ovl10_07_8004A3CC, D_ovl10_07_8004A3D4);
    func_ovl10_07_80048818(1);
    D_ovl10_07_8004A3C8 = func_ovl10_07_80048868(func_ovl10_07_80048808());
    D_ovl10_07_8004A3C8->unk70 = 0.0f;
    D_ovl10_07_8004A3C8->unk40->unk10 += D_ovl10_07_8004A4B8;
    D_ovl10_07_8004A3C8->unk40->unk14 += D_ovl10_07_8004A4A8;
    D_ovl10_07_8004A3C8->unk40->unk18 += D_ovl10_07_8004A4BC;
    D_ovl10_07_8004A3C8->unk40->unk20 = D_ovl10_07_8004A4AC;
    D_ovl10_07_8004A3B0[D_ovl10_07_8004A354]->unk40->unk14 += D_ovl10_07_8004A4A8;
    func_ovl10_07_8004316C(D_ovl10_07_8004A354, D_ovl10_07_8004A4B0, D_ovl10_07_8004A4B4, y);
    D_ovl10_07_8004A3C8->unk70 = 1.6333334f;
}

void func_ovl10_07_800448BC(void) {
    UnkStructA *obj;

    obj = func_ovl10_07_80048868(func_ovl10_07_80048808());
    func_ovl10_07_800487E0(3, 5, 0xE);
    func_ovl10_07_80048820(0x40);
    obj->unk40->unk14 = 4000.0f;
    func_ovl10_07_80049030(obj, 0x01000011);
    obj->unk70 = 0.0f;
    D_ovl10_07_80049E9C = 2;
    D_ovl10_07_8004A2C0 = 0;
    D_ovl10_07_8004A2CC = 0.0f;
    D_ovl10_07_8004A2D0 = 0.0f;
    func_ovl10_07_800487B0(0x6E, 0x10);
}

void func_ovl10_07_8004489C(void) {
    func_ovl10_07_80048838();
}

void func_ovl10_07_80044824(void) {
    switch (D_ovl10_07_80049E9C) {
        case 1:
            func_ovl10_07_80049198(0x78);
            func_ovl10_07_80048828(0xC0, 3, 8.5f, 2, 0, 1, 0);
            break;
        case 2:
            func_ovl10_07_800430F4(func_ovl10_07_80046088);
            break;
    }
}

void func_ovl10_07_80044704(void) {
    s32 i;

    func_ovl10_07_80049700(0x29);
    func_ovl10_07_8004453C();
    if (D_ovl10_07_8004A340[1] != 0) {
        func_ovl10_07_80043B98(0, 0);
    } else {
        func_ovl10_07_80043B98(0, 1);
    }
    if (D_ovl10_07_8004A340[2] != 0) {
        func_ovl10_07_80044318();
    } else if (D_ovl10_07_8004ADE4 == 0) {
        func_ovl10_07_800437D4();
    }
    if (func_ovl10_07_800487F8(D_ovl10_07_8004A2D8[1][0], D_ovl10_07_8004A2D8[1][1], D_ovl10_07_8004A2D8[1][2],
                               D_ovl10_07_8004A2D8[1][0] + 1, D_ovl10_07_8004A2D8[1][2] + 1) != 0 &&
        D_ovl10_07_8004ADE4 != 0) {
        for (i = 0; i < D_ovl10_07_80049DD8; i++) {
            func_ovl10_07_80043944(i, 0);
        }
        func_ovl10_07_80043DE8(0);
    }
    func_ovl10_07_80044268();
    func_ovl10_07_800441C4();
}

void func_ovl10_07_8004453C(void) {
    s32 found;
    s32 i;

    found = -1;
    i = 0;
    do {
        if (func_ovl10_07_800487F8(D_ovl10_07_8004A2D8[i][0], D_ovl10_07_8004A2D8[i][1], D_ovl10_07_8004A2D8[i][2],
                                   D_ovl10_07_8004A2D8[i][0] + 1, D_ovl10_07_8004A2D8[i][2] + 1) != 0) {
            found = i;
        }
        i++;
    } while (i < D_ovl10_07_8004A318 && found == -1);
    if (found != -1) {
        D_ovl10_07_8004A330[found] = (D_ovl10_07_8004A330[found] + 1) % 2;
        func_ovl10_07_800443E4(found, D_ovl10_07_8004A330[found]);
        D_ovl10_07_8004A340[D_ovl10_07_8004A320[found]] = (D_ovl10_07_8004A340[D_ovl10_07_8004A320[found]] + 1) % 2;
        if (D_ovl10_07_8004A330[found] == 1 && D_ovl10_07_8004A320[found] != 4) {
            for (i = 0; i < D_ovl10_07_8004A318; i++) {
                if (i != found && D_ovl10_07_8004A320[i] != 4 && D_ovl10_07_8004A330[i] == 1) {
                    D_ovl10_07_8004A330[i] = 0;
                    func_ovl10_07_800443E4(i, 0);
                    D_ovl10_07_8004A340[D_ovl10_07_8004A320[i]] = 0;
                }
            }
        }
    }
}

void func_ovl10_07_80044318(void) {
    s32 i;

    if (D_ovl10_07_8004ADEC == 0) {
        for (i = 0; i < D_ovl10_07_8004AA00; i++) {
            D_ovl10_07_8004A900[func_ovl10_07_800430F4(func_ovl10_07_8004713C)] = i;
            D_ovl10_07_8004AA08[i] = 0;
            D_ovl10_07_8004A820[i] = 0;
        }
        D_ovl10_07_8004ADEC = 1;
        D_ovl10_07_8004ADE8 = 0;
    }
}

void func_ovl10_07_80044268(void) {
    s32 i;

    if (D_ovl10_07_8004ADE4 == 0) {
        for (i = 0; i < D_ovl10_07_80049DD8; i++) {
            if (D_ovl10_07_80049CA8[i] != D_ovl10_07_8004A340[D_ovl10_07_80049E40[i]]) {
                func_ovl10_07_80043944(i, D_ovl10_07_8004A340[D_ovl10_07_80049E40[i]]);
            }
        }
    }
}

void func_ovl10_07_800441C4(void) {
    s32 i;

    for (i = 0; i < D_ovl10_07_8004A248; i++) {
        if (D_ovl10_07_8004A130[i] != D_ovl10_07_8004A340[D_ovl10_07_8004A250[i]]) {
            func_ovl10_07_800440C8(i, D_ovl10_07_8004A340[D_ovl10_07_8004A250[i]]);
        }
    }
}

void func_ovl10_07_800440C8(s32 arg0, s32 arg1) {
    D_ovl10_07_8004A130[arg0] = arg1;
    if (D_ovl10_07_8004A268[arg0] == 0) {
        D_ovl10_07_8004A148[func_ovl10_07_800430F4(func_ovl10_07_800465E0)] = arg0;
    }
    if (arg1 != 0) {
        D_ovl10_07_8004A280[arg0] = 0.05f;
        D_ovl10_07_8004A298[arg0] = 1.0f;
        if (D_ovl10_07_8004A0B8[arg0] == NULL) {
            func_ovl10_07_80043EEC(arg0);
        }
        func_ovl10_07_80049700(0xA2);
    } else {
        D_ovl10_07_8004A280[arg0] = -0.05f;
        D_ovl10_07_8004A298[arg0] = 0.0f;
    }
    D_ovl10_07_8004A268[arg0] = 1;
}

void func_ovl10_07_80043EEC(s32 arg0) {
    s32 sp40[2] = { 0xC5, 0xC6 };
    Vec3f pos;

    func_ovl10_07_80048688(D_ovl10_07_8004A0D0[arg0][0], D_ovl10_07_8004A0D0[arg0][1], D_ovl10_07_8004A0D0[arg0][2], &pos, 0);
    D_ovl10_07_8004A0B8[arg0] = func_ovl10_07_80049050(sp40[(D_ovl10_07_8004A118[arg0] >> 2) - 1], 0x01080000, 0xD0, 0);
    D_ovl10_07_8004A0B8[arg0]->unk40->unk10 = pos.x;
    D_ovl10_07_8004A0B8[arg0]->unk40->unk14 = pos.y;
    D_ovl10_07_8004A0B8[arg0]->unk40->unk18 = pos.z;
    D_ovl10_07_8004A0B8[arg0]->unk40->unk28 = 0.0f;
    D_ovl10_07_8004A0B8[arg0]->unk40->unk2C = 0.0f;
    D_ovl10_07_8004A0B8[arg0]->unk40->unk30 = 0.0f;
    if (D_ovl10_07_8004A118[arg0] & 2) {
        if (D_ovl10_07_8004A118[arg0] & 4) {
            D_ovl10_07_8004A0B8[arg0]->unk40->unk18 += 600.0f;
        }
        if (D_ovl10_07_8004A118[arg0] & 8) {
            D_ovl10_07_8004A0B8[arg0]->unk40->unk18 += 500.0f;
        }
        D_ovl10_07_8004A0B8[arg0]->unk40->unk20 = 90.0f;
    }
}

void func_ovl10_07_80043E60(void) {
    s32 i;

    func_ovl10_07_80043DE8(1);
    func_ovl10_07_80043B98(0, 0);
    for (i = 0; i < D_ovl10_07_80049DD8; i++) {
        func_ovl10_07_80043944(i, 1);
    }
    if (D_ovl10_07_8004ADEC != 0) {
        func_ovl10_07_800437D4();
    }
}

void func_ovl10_07_80043DE8(s32 arg0) {
    if (arg0 != D_ovl10_07_8004ADE4) {
        D_ovl10_07_8004ADE4 = arg0;
        if (arg0 == 1) {
            func_ovl10_07_80043DA8();
        } else {
            func_ovl10_07_80049478(0, 0, 0, 0.0f);
        }
    }
}

void func_ovl10_07_80043DA8(void) {
    D_ovl10_07_8004AEF0 = 0;
    D_ovl10_07_8004AEF4 = 2;
    func_ovl10_07_800430F4(func_ovl10_07_80047550);
    func_ovl10_07_80049700(0x9E);
}

/* opens (arg1 1) or closes the gate */
void func_ovl10_07_80043B98(s32 arg0, s32 arg1) {
    s32 pad;
    Vec3f pos;

    if (arg1 != D_ovl10_07_8004A4DC[arg0]) {
        if (D_ovl10_07_8004A5E4[arg0] == 0) {
            D_ovl10_07_8004A4E0[func_ovl10_07_800430F4(func_ovl10_07_80047630)] = arg0;
        }
        if (arg1 != 0) {
            D_ovl10_07_8004A5EC[arg0] = D_ovl10_07_8004A4D4[arg0]->unk40->unk18 - 100.0f;
            D_ovl10_07_8004A5F0[arg0] = D_ovl10_07_8004A4D8[arg0]->unk40->unk18 + 100.0f;
            D_ovl10_07_8004A5E8[arg0] = -5.0f;
            func_ovl10_07_80048660(D_ovl10_07_8004A4C8[arg0][0], D_ovl10_07_8004A4C8[arg0][1], D_ovl10_07_8004A4C8[arg0][2] + 1, 0);
            func_ovl10_07_80048660(D_ovl10_07_8004A4C8[arg0][0], D_ovl10_07_8004A4C8[arg0][1], D_ovl10_07_8004A4C8[arg0][2] + 2, 0);
        } else {
            D_ovl10_07_8004A5EC[arg0] = D_ovl10_07_8004A4D4[arg0]->unk40->unk18 + 100.0f;
            D_ovl10_07_8004A5F0[arg0] = D_ovl10_07_8004A4D8[arg0]->unk40->unk18 - 100.0f;
            D_ovl10_07_8004A5E8[arg0] = 5.0f;
            func_ovl10_07_80048660(D_ovl10_07_8004A4C8[arg0][0], D_ovl10_07_8004A4C8[arg0][1], D_ovl10_07_8004A4C8[arg0][2] + 1, 9);
            func_ovl10_07_80048660(D_ovl10_07_8004A4C8[arg0][0], D_ovl10_07_8004A4C8[arg0][1], D_ovl10_07_8004A4C8[arg0][2] + 2, 9);
        }
        func_ovl10_07_800490F8(D_ovl10_07_8004A4D4[arg0], &pos);
        D_ovl10_07_8004A5E4[arg0] = 1;
    }
}

void func_ovl10_07_80043944(s32 arg0, s32 arg1) {
    s32 j;
    s32 v;
    s32 pad[2];

    if (arg1 != (D_ovl10_07_80049CA8[arg0] & 1)) {
        if (arg1 != 0) {
            D_ovl10_07_80049CA8[arg0] |= 1;
        } else {
            D_ovl10_07_80049CA8[arg0] &= ~1;
        }
        if (D_ovl10_07_80049C78[arg0] & 4) {
            func_ovl10_07_80043914(arg0);
            if (arg1 != 0) {
                v = 9;
                D_ovl10_07_80049CA8[arg0] |= 2;
                /* func_ovl10_07_800438CC(arg0), written out */
                D_ovl10_07_80049CD8[func_ovl10_07_800430F4(func_ovl10_07_80046954)] = arg0;
                D_ovl10_07_80049E10[arg0] = 0;
            } else {
                D_ovl10_07_80049CA8[arg0] &= ~2;
                func_ovl10_07_8004389C(arg0);
                v = 1;
                func_ovl10_07_800437EC(arg0);
            }
            /* Nothing, but it keeps arg0 in v1 for the loops. */
            if (arg0) {
            }
            if (D_ovl10_07_80049C78[arg0] & 1) {
                for (j = 0; j < D_ovl10_07_80049E70[arg0]; j++) {
                    func_ovl10_07_80048660(D_ovl10_07_80049BF0[arg0][0] + j, D_ovl10_07_80049BF0[arg0][1], D_ovl10_07_80049BF0[arg0][2], v);
                }
            } else {
                for (j = 0; j < D_ovl10_07_80049E70[arg0]; j++) {
                    func_ovl10_07_80048660(D_ovl10_07_80049BF0[arg0][0], D_ovl10_07_80049BF0[arg0][1], D_ovl10_07_80049BF0[arg0][2] + j, v);
                }
            }
        }
        if (D_ovl10_07_80049C78[arg0] & 8) {
            if (arg1 != 0) {
                func_ovl10_07_80043804(arg0);
            } else {
                func_ovl10_07_800437EC(arg0);
            }
        }
    }
}

void func_ovl10_07_80043914(s32 arg0) {
    func_ovl10_07_80049028(D_ovl10_07_80049BC0[arg0], 0x01000000);
}

void func_ovl10_07_800438CC(s32 arg0) {
    D_ovl10_07_80049CD8[func_ovl10_07_800430F4(func_ovl10_07_80046954)] = arg0;
    D_ovl10_07_80049E10[arg0] = 0;
}

void func_ovl10_07_8004389C(s32 arg0) {
    func_ovl10_07_80049030(D_ovl10_07_80049BC0[arg0], 0x01000000);
}

void func_ovl10_07_80043804(s32 arg0) {
    D_ovl10_07_80049CD8[func_ovl10_07_800430F4(func_ovl10_07_80046AA8)] = arg0;
    D_ovl10_07_80049E10[arg0] = 0;
    if (D_ovl10_07_8004ADE4 != 0) {
        D_ovl10_07_80049DE0[arg0] = 30;
    } else {
        D_ovl10_07_80049DE0[arg0] = func_ovl10_07_80049338(60) + 90;
    }
    D_ovl10_07_80049CA8[arg0] = 1;
}

void func_ovl10_07_800437EC(s32 arg0) {
    D_ovl10_07_80049E10[arg0] = 1;
}

void func_ovl10_07_800437D4(void) {
    D_ovl10_07_8004ADE8 = 1;
    D_ovl10_07_8004ADEC = 0;
}

void func_ovl10_07_8004376C(void) {
    if (func_ovl10_07_800487F8(0xC, 0, 8, 0xD, 9) != 0) {
        if (func_ovl10_07_800493E0(0xA4) != 0) {
            func_ovl10_07_80048D90(0x291, 1);
        } else {
            func_ovl10_07_80048D90(0xCE, 4);
        }
    }
}

void func_ovl10_07_8004374C(void) {
    func_ovl10_07_8004347C(1);
}

s32 func_ovl10_07_8004347C(s32 arg0) {
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    if (arg0 == 2) {
        do {
            if (D_ovl10_07_8004A3E0[i] == 2 && D_ovl10_07_8004A3F8[i] == 1 &&
                func_ovl10_07_800487F8(D_ovl10_07_8004A368[i][0], D_ovl10_07_8004A368[i][1],
                                       D_ovl10_07_8004A368[i][2], D_ovl10_07_8004A368[i][0] + 1,
                                       D_ovl10_07_8004A368[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_07_8004A428 && found == 0);
        if (found) {
            D_ovl10_07_8004A354 = i;
            if (D_ovl10_07_8004A430[i] < D_ovl10_07_8004A368[i][1]) {
                D_ovl10_07_8004A4B0 = 0.0f;
                D_ovl10_07_8004A4B4 = -0.2f;
            } else {
                D_ovl10_07_8004A4B0 = -0.0f;
                D_ovl10_07_8004A4B4 = 0.2f;
            }
        }
    } else {
        do {
            if (func_ovl10_07_800487F8(D_ovl10_07_8004A368[i][0], D_ovl10_07_8004A368[i][1],
                                       D_ovl10_07_8004A368[i][2], D_ovl10_07_8004A368[i][0] + 1,
                                       D_ovl10_07_8004A368[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_07_8004A428 && found == 0);
    }
    if (found) {
        D_ovl10_07_8004A354 = i;
        if (D_ovl10_07_8004A430[i] < D_ovl10_07_8004A368[i][1]) {
            D_ovl10_07_8004A4B0 = 0.0f;
            D_ovl10_07_8004A4B4 = -0.2f;
        } else {
            D_ovl10_07_8004A4B0 = -0.0f;
            D_ovl10_07_8004A4B4 = 0.2f;
        }
        if (arg0 == 2) {
            func_ovl10_07_80043340();
        } else {
            D_ovl10_07_8004A3D8 = D_ovl10_07_8004A448[i];
            D_ovl10_07_8004A3DC = D_ovl10_07_8004A460[i];
            func_ovl10_07_80043254();
        }
    }
    return found;
}

void func_ovl10_07_80043340(void) {
    s32 out[6];
    f32 a;
    f32 b;
    s32 i;

    i = D_ovl10_07_8004A354;
    a = func_ovl10_07_800486C8(D_ovl10_07_8004A430[i]);
    b = func_ovl10_07_800486C8(D_ovl10_07_8004A368[i][1]);
    func_ovl10_07_80048850(0x40);
    func_ovl10_07_80048840(1);
    D_ovl10_07_8004A3C8 = func_ovl10_07_80048868(func_ovl10_07_80048808());
    D_ovl10_07_8004A4C0 = (a - b) * 0.5f;
    D_ovl10_07_8004A4C0 += b;
    D_ovl10_07_8004A3C8->unk70 = 0.0f;
    func_ovl10_07_80048680(D_ovl10_07_8004A3C8->unk40->unk10, D_ovl10_07_8004A3C8->unk40->unk14,
                           D_ovl10_07_8004A3C8->unk40->unk18, out, 2);
    func_ovl10_07_80048818(1);
    func_ovl10_07_80048EF0(10.0f);
    func_ovl10_07_80048EF8(5.0f);
    func_ovl10_07_80048F10(0.0f);
    func_ovl10_07_8004316C(i, D_ovl10_07_8004A4B0, D_ovl10_07_8004A4B4, a);
}

void func_ovl10_07_80043254(void) {
    s32 out[6];
    s32 pad1;
    s32 pad2;
    s32 pad3;

    D_ovl10_07_8004A4C0 = -1.0f;
    func_ovl10_07_80048850(0x40);
    func_ovl10_07_80048840(1);
    D_ovl10_07_8004A3C8 = func_ovl10_07_80048868(func_ovl10_07_80048808());
    D_ovl10_07_8004A3C8->unk70 = 0.0f;
    func_ovl10_07_80048680(D_ovl10_07_8004A3C8->unk40->unk10, D_ovl10_07_8004A3C8->unk40->unk14,
                           D_ovl10_07_8004A3C8->unk40->unk18, out, 2);
    func_ovl10_07_80048660(out[0], out[1], out[2], 0);
    func_ovl10_07_80048818(1);
    func_ovl10_07_8004316C(D_ovl10_07_8004A354, D_ovl10_07_8004A4B0, D_ovl10_07_8004A4B4, -1.0f);
    func_ovl10_07_80049198(0x78);
    D_ovl10_07_80049BA4 = D_ovl10_07_8004A3D8;
    D_ovl10_07_80049BA8 = D_ovl10_07_8004A3DC;
    func_ovl10_07_80048720(D_ovl10_07_8004A3D8, D_ovl10_07_8004A3DC, 0);
}

void func_ovl10_07_8004316C(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_ovl10_07_8004A354 = arg0;
    D_ovl10_07_8004A358 = arg1;
    D_ovl10_07_8004A35C = arg2;
    D_ovl10_07_8004A360 = arg3;
    func_ovl10_07_800430F4(func_ovl10_07_800479D4);
    D_ovl10_07_8004A3C8 = func_ovl10_07_80048868(func_ovl10_07_80048808());
    D_ovl10_07_8004A3C8->unk70 = 0.0f;
    func_ovl10_07_800486E0(1);
    if (arg1 == 0.0f && arg2 < 0.0f && arg3 == -1.0f) {
        func_ovl10_07_80048880(1);
    }
    func_ovl10_07_80049700(0x98);
    func_ovl10_07_80048790(0);
}

/* empty: the two words after 80043084 */
void func_ovl10_07_800430EC(void) {
}

void func_ovl10_07_80043084(void) {
    func_ovl10_07_80049478(0, 0, 0, 0.0f);
    func_ovl10_07_80043034();
}

void func_ovl10_07_80043034(void) {
    if (D_ovl10_07_80049E6C != -1) {
        if (func_ovl10_07_800488F0(0) != 0) {
            func_ovl10_07_80049730(D_ovl10_07_80049E6C);
        }
        D_ovl10_07_80049E6C = -1;
    }
}

/* sets the flag the doors' task waits for (the handler's case 3) */
void func_ovl10_07_80043010(void) {
    if (D_ovl10_07_8004A2BC == 0) {
        D_ovl10_07_8004A2BC = 1;
    }
}

/* .data */
u32 D_ovl10_07_80049940[][3] = { { 0xA60002, 0xE, 0x4 }, { 0xA50003, 0xF, 0x4 }, { 0xA70001, 0xE, 0x4 } };
s32 D_ovl10_07_80049964[] = { 0x8, 0x0, 0x19, 0x45, 0x1, 0x20, 0x1, 0x8, 0x4A, 0x2, 0x23, 0x1, 0x8, 0x4A, 0x2, 0x26, 0x1, 0x8, 0x4A, 0x2, -1 };
s32 D_ovl10_07_800499B8[] = { 0xE, 0x0, 0xC, 0x5, 0x1, 0x0, 0x20, 0x1, 0x3, 0x5, 0x2, 0x0, -1 };
s32 D_ovl10_07_800499EC[] = { 0x2B, 0x1, 0x13, 0xFF, 0x1, 0x1, 0x0, 0x6F, 0x11, 0x0, 0x0, -1 };
s32 D_ovl10_07_80049A1C[] = { 0x9, 0x0, 0x8, 0x1, 0x2A, 0x1, 0x9, 0x2, -1 };
s32 D_ovl10_07_80049A40[] = { 0x27, 0x1, 0x12, 0x1, -1 };
s32 D_ovl10_07_80049A54[] = { 0x20, 0x1, 0x13, 0x168, 0x2, 0x0, 0x140, 0x22, 0x1, 0x13, 0x168, 0x2, 0x50, 0xF0, 0x24, 0x1, 0x13, 0x168, 0x1, 0xA0, -1, 0x0, 0x0 };
