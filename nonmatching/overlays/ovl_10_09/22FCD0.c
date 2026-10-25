/*
 * NON_MATCHING: ovl_10_09's game object, complete: every function, its
 * .bss and its .data tables. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 128, jp 128
 *
 * What still differs in us (words):
 * - func_ovl10_09_80044FEC (12), 8004576C (62), 800468FC (9), 80046C10
 *   (9) and 800474A8 (2): ovl_10_08's 80044F98, 800455FC, 8004675C,
 *   80046A70 and 80047264 (ovl_10_12's), with the same differences
 *   (their headers).
 * - func_ovl10_09_80047B70 (17): the same code; the padding IDO puts after its
 *   endless loop (to a 16-byte boundary) is a word longer
 *   because 8004576C is a word short (as in ovl_10_11's 80044C24).
 * - func_ovl10_09_80043238 (2): a `lui at` scheduled one place early, as
 *   in ovl_10_08's 800432B0.
 * - func_ovl10_09_80043B78 (1): pos a word high, as in ovl_10_08's
 *   80044238.
 * - func_ovl10_09_800452BC (14): s3 and s4 swap, as in ovl_10_08's
 *   80045268.
 *
 * ovl_10_09's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Most of it is ovl_10_08's
 * draft, renamed (scratch/10_09/ in the checkout has the scripts). Its own:
 * the handler 80045A80 and its cases (80043068, 80043730, 80043E40,
 * 800446F4, 800448C4, 800448E4, 80044BC4, 80044820), the set-up 800458D8,
 * and the three fades the gate's opening starts (80045C80-80045FE0, with
 * their f32s at 8004A0E0). 800443D4 is defined above 80045650 and the .data
 * tables after the functions: IDO lays .data out in source order, and the
 * original has 800443D4's local array first, then 80045650's and
 * 80043EDC's, then the tables. .data, .rodata and .bss build to the
 * original's bytes and places.
 */
#include "common.h"
/* What func_ovl10_09_80048CE0 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_09_80048CE0;

void func_ovl10_09_80047DC8(const char *, ...);
void func_ovl10_09_80048108(s32);
void func_ovl10_09_80048110(s32, f32, f32, f32, s32, s32);
void func_ovl10_09_80048120(s32);
void func_ovl10_09_80048140(s32, s32, s32, s32);
void func_ovl10_09_80048160(f32, f32, f32, s32 *, s32);
void func_ovl10_09_80048168(f32, f32, f32, Vec3f *, s32);
f32 func_ovl10_09_800481A8(s32);
void func_ovl10_09_800481B0(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_09_800481B8(s32, s32, s32, s32, s32, s32);
void func_ovl10_09_800481C0(s32);
void func_ovl10_09_800481F0(void (*)(UnkStructA *));
void func_ovl10_09_80048200(s32, s32, s32);
s32 *func_ovl10_09_80048258(void);
void func_ovl10_09_80048270(s32);
void func_ovl10_09_800482B8(void);
void func_ovl10_09_800482C0(s32, s32, s32);
s32 func_ovl10_09_800482D8(s32, s32, s32, s32, s32);
s32 func_ovl10_09_800482E8(void);
void func_ovl10_09_800482F8(s32);
void func_ovl10_09_80048308(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_09_80048318(void);
void func_ovl10_09_80048320(s32);
void func_ovl10_09_80048330(s32);
UnkStructA *func_ovl10_09_80048348(s32);
void func_ovl10_09_80048360(s32);
void func_ovl10_09_80048948(f32, f32, f32);
void func_ovl10_09_80048968(f32, f32, f32);
void func_ovl10_09_80048970(f32 *, f32 *, f32 *);
void func_ovl10_09_800489B0(s32);
void func_ovl10_09_800489D0(f32);
void func_ovl10_09_800489D8(f32);
void func_ovl10_09_800489F0(f32);
void func_ovl10_09_80048B10(UnkStructA *, s32);
void func_ovl10_09_80048B20(UnkStructA *);
UnkStructA *func_ovl10_09_80048B30(s32, s32, s32, s32);
void func_ovl10_09_80048B88(UnkStructA *);
void func_ovl10_09_80048BD8(UnkStructA *, Vec3f *);
void func_ovl10_09_80048C58(void (*)(void), s32, s32, s32, s32);
void func_ovl10_09_80048C78(s32);
void func_ovl10_09_80048CA0(void);
void func_ovl10_09_80048CD0(s32, s32);
UnkStruct_ovl10_09_80048CE0 *func_ovl10_09_80048CE0(void);
void func_ovl10_09_80048CF0(UnkStruct_ovl10_09_80048CE0 *, s32);
s32 *func_ovl10_09_80048EF0(void);
void func_ovl10_09_80048F58(s32, s32, s32, f32);
void func_ovl10_09_80048F98(s32, s32, s32, s32, s32);
void func_ovl10_09_80048FA8(s32, s32, s32);
void func_ovl10_09_80048FC0(u32 (*)[3]);
void func_ovl10_09_800490B0(s32, Vec3f *, s32);
void func_ovl10_09_80049168(s32, s32, s32);
void func_ovl10_09_800491E0(s32);
void func_ovl10_09_80049200(s32, f32, f32, f32);
void func_ovl10_09_80048300(s32);
void func_ovl10_09_80048310(const char *);
void func_ovl10_09_800483A8(s32);
s32 func_ovl10_09_800483D0(s32);
void func_ovl10_09_80048810(UnkStructA_40 *, s32);
void func_ovl10_09_80048818(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl10_09_80048850(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl10_09_80048980(u32 *, s32, s32);
void func_ovl10_09_800489C0(s32);
f32 func_ovl10_09_80048AB0(Vec3f *, Vec3f *);
void func_ovl10_09_80048B08(UnkStructA *, s32);
void func_ovl10_09_80048C68(void);
s32 func_ovl10_09_80048E18(s32);
void func_ovl10_09_80049188(s32);
s32 func_ovl10_09_80049208(s32, Vec3f *);
void func_ovl10_09_80049210(s32);
void func_ovl10_09_80049358(void);
void func_ovl10_09_80049360(void);

void func_ovl10_09_80048180(s32);
void func_ovl10_09_80048188(void);
s32 func_ovl10_09_800481D8(s32);
void func_ovl10_09_800481E0(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_09_800490D8(s16, s32);
void func_ovl10_09_800490E0(s16, s32);

void func_ovl10_09_80048278(s32);

void func_ovl10_09_80047D68(void);
void func_ovl10_09_80047D50(void);
void func_ovl10_09_80047CF4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl10_09_80047CAC(f32 arg0);
void func_ovl10_09_80047C78(s32 arg0, UnkStructA *arg1);
void func_ovl10_09_80047B70(void);
s32 func_ovl10_09_800430D8(void (*arg0)(void));
s32 func_ovl10_09_80047B38(void (*arg0)(void), const char *arg1);
void func_ovl10_09_80047B0C(void (*arg0)(void));
s32 func_ovl10_09_80047AC8(void (*arg0)(void));
void func_ovl10_09_80047AB4(s32 arg0);
void func_ovl10_09_80047A24(void);
void func_ovl10_09_800479E8(void);
void func_ovl10_09_8004797C(UnkStructA *arg0);
void func_ovl10_09_800478FC(UnkStructA *arg0);
void func_ovl10_09_800474A8(void);
void func_ovl10_09_80047384(void);
void func_ovl10_09_8004734C(s32 arg0);
void func_ovl10_09_80047104(void);
void func_ovl10_09_80047024(void);
void func_ovl10_09_80046E04(void);
void func_ovl10_09_80046C10(void);
void func_ovl10_09_800468FC(s32 arg0, s32 arg1);
void func_ovl10_09_80046898(s32 arg0, s32 arg1);
void func_ovl10_09_8004657C(void);
void func_ovl10_09_800464DC(s32 arg0);
void func_ovl10_09_80046428(void);
void func_ovl10_09_800462C4(s32 arg0, s32 arg1);
f32 func_ovl10_09_8004626C(s32 arg0);
void func_ovl10_09_800460B4(void);
void func_ovl10_09_8004607C(s32 arg0);
void func_ovl10_09_80045FE0(void);
void func_ovl10_09_80045F48(void);
void func_ovl10_09_80045E58(void);
void func_ovl10_09_80045DFC(void);
void func_ovl10_09_80045D94(void);
void func_ovl10_09_80045D00(void);
void func_ovl10_09_80045CC0(void);
void func_ovl10_09_80045C80(void);
void func_ovl10_09_80045C64(void (*arg0)(void));
void func_ovl10_09_80045C48(s32 arg0);
void func_ovl10_09_80045C2C(void);
void func_ovl10_09_80045C10(void);
void func_ovl10_09_80045A80(s32 arg0);
void func_ovl10_09_800458D8(void);
void func_ovl10_09_8004576C(s32 *arg0);
void func_ovl10_09_800443D4(s32 arg0, s32 arg1);
void func_ovl10_09_80045650(s32 arg0);
void func_ovl10_09_8004559C(s32 *arg0);
void func_ovl10_09_800452BC(s32 *arg0);
void func_ovl10_09_80044FEC(s32 *arg0);
void func_ovl10_09_80044EA0(s32 *arg0);
void func_ovl10_09_80044DDC(s32 arg0);
void func_ovl10_09_80044C70(s32 *arg0);
void func_ovl10_09_80044BF4(void);
void func_ovl10_09_80044BC4(void);
void func_ovl10_09_80044B20(void);
void func_ovl10_09_80044A78(void);
void func_ovl10_09_80044914(void);
void func_ovl10_09_800448E4(void);
void func_ovl10_09_800448C4(void);
void func_ovl10_09_80044820(void);
void func_ovl10_09_800446F4(void);
void func_ovl10_09_8004452C(void);
void func_ovl10_09_80044308(void);
void func_ovl10_09_80044258(void);
void func_ovl10_09_800441B4(void);
void func_ovl10_09_800440B8(s32 arg0, s32 arg1);
void func_ovl10_09_80043EDC(s32 arg0);
void func_ovl10_09_80043E40(void);
void func_ovl10_09_80043DC8(s32 arg0);
void func_ovl10_09_80043D88(void);
void func_ovl10_09_80043B78(s32 arg0, s32 arg1);
void func_ovl10_09_80043924(s32 arg0, s32 arg1);
void func_ovl10_09_800438F4(s32 arg0);
void func_ovl10_09_800438AC(s32 arg0);
void func_ovl10_09_8004387C(s32 arg0);
void func_ovl10_09_800437E4(s32 arg0);
void func_ovl10_09_800437CC(s32 arg0);
void func_ovl10_09_800437B4(void);
void func_ovl10_09_80043730(void);
s32 func_ovl10_09_80043460(s32 arg0);
void func_ovl10_09_80043324(void);
void func_ovl10_09_80043238(void);
void func_ovl10_09_80043150(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl10_09_800430D0(void);
void func_ovl10_09_80043068(void);
void func_ovl10_09_80043018(void);
void func_ovl10_09_80043010(void);

/* .bss */
u8 D_ovl10_09_800499B0[0x24]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_800499D4;
s32 D_ovl10_09_800499D8;
u8 D_ovl10_09_800499DC[0x4]; /* unused (func_ovl10_09_80047D68) */
Vec3f D_ovl10_09_800499E0;
u8 D_ovl10_09_800499EC[0x4]; /* unused (func_ovl10_09_80047D68) */
UnkStructA *D_ovl10_09_800499F0[12];
s32 D_ovl10_09_80049A20[11][3];
u8 D_ovl10_09_80049AA4[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_80049AA8[12];
s32 D_ovl10_09_80049AD8[12];
s32 D_ovl10_09_80049B08[64];
s32 D_ovl10_09_80049C08;
u8 D_ovl10_09_80049C0C[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_80049C10[12];
s32 D_ovl10_09_80049C40[12];
s32 D_ovl10_09_80049C70[11];
s32 D_ovl10_09_80049C9C;
s32 D_ovl10_09_80049CA0[11];
s32 D_ovl10_09_80049CCC;
s32 D_ovl10_09_80049CD0;
s32 D_ovl10_09_80049CD4;
s32 D_ovl10_09_80049CD8[64];
s32 D_ovl10_09_80049DD8;
u8 D_ovl10_09_80049DDC[0x4]; /* unused (func_ovl10_09_80047D68) */
void (*D_ovl10_09_80049DE0[64])(void);
UnkStruct_ovl10_09_80048CE0 *D_ovl10_09_80049EE0;
u8 D_ovl10_09_80049EE4[0x4]; /* unused (func_ovl10_09_80047D68) */
UnkStructA *D_ovl10_09_80049EE8[6];
s32 D_ovl10_09_80049F00[6][3];
s32 D_ovl10_09_80049F48[6];
s32 D_ovl10_09_80049F60[6];
s32 D_ovl10_09_80049F78[64];
s32 D_ovl10_09_8004A078;
u8 D_ovl10_09_8004A07C[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_8004A080[6];
s32 D_ovl10_09_8004A098[6];
f32 D_ovl10_09_8004A0B0[6];
f32 D_ovl10_09_8004A0C8[6];
f32 D_ovl10_09_8004A0E0;
f32 D_ovl10_09_8004A0E4;
f32 D_ovl10_09_8004A0E8;
f32 D_ovl10_09_8004A0EC;
f32 D_ovl10_09_8004A0F0;
u8 D_ovl10_09_8004A0F4[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_8004A0F8[4][3];
UnkStructA *D_ovl10_09_8004A128[4];
s32 D_ovl10_09_8004A138;
u8 D_ovl10_09_8004A13C[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_8004A140[4];
s32 D_ovl10_09_8004A150[4];
s32 D_ovl10_09_8004A160[5];
s32 D_ovl10_09_8004A174;
f32 D_ovl10_09_8004A178;
f32 D_ovl10_09_8004A17C;
f32 D_ovl10_09_8004A180;
u8 D_ovl10_09_8004A184[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_8004A188[6][3];
UnkStructA *D_ovl10_09_8004A1D0[6];
UnkStructA *D_ovl10_09_8004A1E8;
s32 D_ovl10_09_8004A1EC;
s32 D_ovl10_09_8004A1F0;
s32 D_ovl10_09_8004A1F4;
s32 D_ovl10_09_8004A1F8;
s32 D_ovl10_09_8004A1FC;
s32 D_ovl10_09_8004A200[6];
s32 D_ovl10_09_8004A218[6];
s32 D_ovl10_09_8004A230[6];
s32 D_ovl10_09_8004A248;
u8 D_ovl10_09_8004A24C[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_8004A250[6];
s32 D_ovl10_09_8004A268[6];
s32 D_ovl10_09_8004A280[6];
s32 D_ovl10_09_8004A298[6];
s32 D_ovl10_09_8004A2B0[6];
f32 D_ovl10_09_8004A2C8;
f32 D_ovl10_09_8004A2CC;
f32 D_ovl10_09_8004A2D0;
f32 D_ovl10_09_8004A2D4;
f32 D_ovl10_09_8004A2D8;
f32 D_ovl10_09_8004A2DC;
f32 D_ovl10_09_8004A2E0;
u8 D_ovl10_09_8004A2E4[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_8004A2E8[1][3]; /* the gate: its tile */
UnkStructA *D_ovl10_09_8004A2F4[1]; /* its two halves */
UnkStructA *D_ovl10_09_8004A2F8[1];
s32 D_ovl10_09_8004A2FC[1]; /* open */
s32 D_ovl10_09_8004A300[64]; /* per task: its gate */
s32 D_ovl10_09_8004A400;
s32 D_ovl10_09_8004A404[1]; /* moving */
f32 D_ovl10_09_8004A408[1];
f32 D_ovl10_09_8004A40C[1];
f32 D_ovl10_09_8004A410[1];
u8 D_ovl10_09_8004A414[0x4]; /* unused (func_ovl10_09_80047D68) */
UnkStructA *D_ovl10_09_8004A418[28];
UnkStructA *D_ovl10_09_8004A488[28];
s32 D_ovl10_09_8004A4F8[27][3];
u8 D_ovl10_09_8004A63C[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_8004A640[28];
s32 D_ovl10_09_8004A6B0[28];
s32 D_ovl10_09_8004A720[64];
s32 D_ovl10_09_8004A820;
u8 D_ovl10_09_8004A824[0x4]; /* unused (func_ovl10_09_80047D68) */
s32 D_ovl10_09_8004A828[28];
s32 D_ovl10_09_8004A898[28];
s32 D_ovl10_09_8004A908[27][4];
f32 D_ovl10_09_8004AAB8[28];
f32 D_ovl10_09_8004AB28[28];
f32 D_ovl10_09_8004AB98[27];
s32 D_ovl10_09_8004AC04;
s32 D_ovl10_09_8004AC08;
s32 D_ovl10_09_8004AC0C;
s32 D_ovl10_09_8004AC10[64];
s32 D_ovl10_09_8004AD10;
s32 D_ovl10_09_8004AD14;

/* .data: defined at the end of the file */
extern u32 D_ovl10_09_80049420[][3];
extern s32 D_ovl10_09_80049444[];
extern s32 D_ovl10_09_800494AC[];
extern s32 D_ovl10_09_80049540[];
extern s32 D_ovl10_09_800495C8[];
extern s32 D_ovl10_09_8004960C[];
extern s32 D_ovl10_09_80049620[];

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_09_80047DB8(void) {
}

static void func_ovl10_09_80047DB0(void) {
}

static void func_ovl10_09_80047DA8(void) {
}

static void func_ovl10_09_80047DA0(void) {
}

static void func_ovl10_09_80047D98(void) {
}

static void func_ovl10_09_80047D90(void) {
}

static void func_ovl10_09_80047D88(void) {
}

static void func_ovl10_09_80047D80(void) {
}

static void func_ovl10_09_80047D78(void) {
}

static void func_ovl10_09_80047D70(void) {
}

void func_ovl10_09_80047D68(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_09_800499B0[0] = D_ovl10_09_800499DC[0] + D_ovl10_09_800499EC[0] + D_ovl10_09_80049AA4[0] + D_ovl10_09_80049C0C[0] + D_ovl10_09_80049DDC[0] + D_ovl10_09_80049EE4[0] + D_ovl10_09_8004A07C[0] + D_ovl10_09_8004A0F4[0] + D_ovl10_09_8004A13C[0] + D_ovl10_09_8004A184[0] + D_ovl10_09_8004A24C[0] + D_ovl10_09_8004A2E4[0] + D_ovl10_09_8004A414[0] + D_ovl10_09_8004A63C[0] + D_ovl10_09_8004A824[0];
    }
}

void func_ovl10_09_80047D50(void) {
    D_ovl10_09_800499D4 = -1;
    D_ovl10_09_800499D8 = -1;
}

void func_ovl10_09_80047CF4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_09_80048948(D_ovl10_09_800499E0.x, D_ovl10_09_800499E0.y, D_ovl10_09_800499E0.z);
    func_ovl10_09_80048968(arg0, arg1, arg2);
    func_ovl10_09_80048C78(180);
}

void func_ovl10_09_80047CAC(f32 arg0) {
    f32 sp1C;

    func_ovl10_09_80048970(&sp1C, NULL, NULL);
    func_ovl10_09_80048968(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_09_80047C78(s32 arg0, UnkStructA *arg1) {
    func_ovl10_09_80049200(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_09_80047B70(void) {
    s32 i;

    D_ovl10_09_80049CD0 = 0;
    D_ovl10_09_80049CD4 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_09_80049DE0[i] != NULL) {
                D_ovl10_09_80049DD8 = i;
                if (D_ovl10_09_80049CD8[i] == 0) {
                    D_ovl10_09_80049DE0[i]();
                } else {
                    D_ovl10_09_80049CD8[i]--;
                }
            }
        }
        D_ovl10_09_80049CD0++;
        D_ovl10_09_80049CD0 &= 3;
        func_ovl10_09_80048CA0();
    }
}

/* Defined above its caller 80046FD0, which pulls it out among the earlier
 * functions all the same: only so does its string come first in .rodata. */
s32 func_ovl10_09_800430D8(void (*arg0)(void)) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_09_80049DE0[i] == NULL) {
            D_ovl10_09_80049DE0[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_09_80047DC8("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_09_80047B38(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_09_800430D8(arg0);
    func_ovl10_09_80047DC8("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_09_80047B0C(void (*arg0)(void)) {
    D_ovl10_09_80049DE0[func_ovl10_09_80047AC8(arg0)] = NULL;
}

s32 func_ovl10_09_80047AC8(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_09_80049DE0[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_09_80047AB4(s32 arg0) {
    D_ovl10_09_80049DE0[arg0] = NULL;
}

void func_ovl10_09_80047A24(void) {
    D_ovl10_09_80049EE0 = func_ovl10_09_80048CE0();
    func_ovl10_09_80048CF0(D_ovl10_09_80049EE0, 0x20000001);
    D_ovl10_09_80049EE0->unk40 = 0.5f;
    D_ovl10_09_80049EE0->unk44 = D_ovl10_09_80049EE0->unk40 * 0.75f;
    D_ovl10_09_80049EE0->unk18 = 0.1f;
    D_ovl10_09_80049EE0->unk1C = -0.1f;
}

void func_ovl10_09_800479E8(void) {
    s32 *p;

    p = func_ovl10_09_80048EF0();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_09_8004797C(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_09_800489B0(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_09_80048B88(arg0);
        func_ovl10_09_80048CA0();
    }
}

void func_ovl10_09_800478FC(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_09_80048F58(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_09_80048B10(arg0, 0x01000000);
        func_ovl10_09_80048C78(5);
        func_ovl10_09_80048F58(0, 0, 0, 0.0f);
        func_ovl10_09_80048BD8(arg0, &pos);
        func_ovl10_09_800490B0(12, &pos, 0);
    }
}

void func_ovl10_09_800474A8(void) {
    s32 y;
    s32 i;
    s32 a;
    s32 b;
    s32 out[6];
    s32 *flags;

    i = D_ovl10_09_8004A174;
    D_ovl10_09_8004A1E8 = func_ovl10_09_80048348(func_ovl10_09_800482E8());
    D_ovl10_09_8004A1D0[i]->unk40->unk14 += D_ovl10_09_8004A178;
    D_ovl10_09_8004A1E8->unk40->unk14 = D_ovl10_09_8004A1D0[i]->unk40->unk14;
    D_ovl10_09_8004A178 += D_ovl10_09_8004A17C;
    if (D_ovl10_09_8004A2E0 != -1.0f &&
        ((D_ovl10_09_8004A178 > 0.0f && D_ovl10_09_8004A2E0 <= D_ovl10_09_8004A1D0[i]->unk40->unk14) ||
         (D_ovl10_09_8004A178 < 0.0f && D_ovl10_09_8004A1D0[i]->unk40->unk14 <= D_ovl10_09_8004A2E0))) {
        D_ovl10_09_8004A17C = -D_ovl10_09_8004A17C;
        D_ovl10_09_8004A2E0 = -1.0f;
    }
    if (D_ovl10_09_8004A180 != -1.0f &&
        (D_ovl10_09_8004A178 == 0.0f ||
         (D_ovl10_09_8004A178 > 0.0f && D_ovl10_09_8004A180 < D_ovl10_09_8004A1D0[i]->unk40->unk14) ||
         (D_ovl10_09_8004A178 < 0.0f && D_ovl10_09_8004A1D0[i]->unk40->unk14 < D_ovl10_09_8004A180))) {
        flags = func_ovl10_09_80048258();
        if (!(*flags & 2)) {
            func_ovl10_09_80048270(1);
        }
        func_ovl10_09_80045C10();
        D_ovl10_09_8004A1E8->unk70 = 1.6333334f;
        if (D_ovl10_09_8004A178 != 0.0f) {
            D_ovl10_09_8004A1D0[i]->unk40->unk14 = D_ovl10_09_8004A180;
            D_ovl10_09_8004A1E8->unk40->unk14 = D_ovl10_09_8004A180;
        }
        if (D_ovl10_09_8004A200[i] == 2) {
            func_ovl10_09_80048160(D_ovl10_09_8004A1D0[i]->unk40->unk10, D_ovl10_09_8004A1D0[i]->unk40->unk14,
                                   D_ovl10_09_8004A1D0[i]->unk40->unk18, out, 2);
            y = out[1];
            func_ovl10_09_800481B0(D_ovl10_09_8004A188[i][0], D_ovl10_09_8004A188[i][1], D_ovl10_09_8004A188[i][2],
                                   D_ovl10_09_8004A188[i][0] + 1, D_ovl10_09_8004A188[i][2] + 1,
                                   D_ovl10_09_8004A188[i][0], y, D_ovl10_09_8004A188[i][2]);
            func_ovl10_09_800481B8(D_ovl10_09_8004A188[i][0], D_ovl10_09_8004A188[i][1], D_ovl10_09_8004A188[i][2],
                                   D_ovl10_09_8004A188[i][0] + 1, D_ovl10_09_8004A188[i][2] + 1, 0);
            D_ovl10_09_8004A250[i] = D_ovl10_09_8004A188[i][1];
            D_ovl10_09_8004A188[i][1] = y;
            if (D_ovl10_09_8004A178 > 0.0f) {
                a = D_ovl10_09_8004A268[i];
                b = D_ovl10_09_8004A280[i];
            } else {
                a = D_ovl10_09_8004A298[i];
                b = D_ovl10_09_8004A2B0[i];
            }
            func_ovl10_09_80048308(a, 3, 8.5f, b, 1, 1, 1);
            func_ovl10_09_800489D8(0.1f);
            func_ovl10_09_800489F0(40.0f);
        }
        func_ovl10_09_800481C0(0);
        if (!(*flags & 2)) {
            func_ovl10_09_800482F8(0);
        }
        func_ovl10_09_80048CD0(0xD0, 0xD0);
    }
}

void func_ovl10_09_80047384(void) {
    s32 i;

    for (i = 0; i < D_ovl10_09_8004A248; i++) {
        if (D_ovl10_09_8004A200[i] == 2 && D_ovl10_09_8004A218[i] != D_ovl10_09_8004A160[D_ovl10_09_8004A230[i]]) {
            if (D_ovl10_09_8004A1D0[i] != NULL) {
                func_ovl10_09_8004734C(i);
            }
            D_ovl10_09_8004A218[i] = D_ovl10_09_8004A160[D_ovl10_09_8004A230[i]];
            func_ovl10_09_80045650(i);
        }
    }
}

void func_ovl10_09_8004734C(s32 arg0) {
    func_ovl10_09_80048B20(D_ovl10_09_8004A1D0[arg0]);
    D_ovl10_09_8004A1D0[arg0] = NULL;
}

/* the gate opens or closes */
void func_ovl10_09_80047104(void) {
    s32 i;
    s32 v;
    s32 w;

    i = D_ovl10_09_8004A300[D_ovl10_09_80049DD8];
    D_ovl10_09_8004A2F4[i]->unk40->unk18 += D_ovl10_09_8004A408[i];
    D_ovl10_09_8004A2F8[i]->unk40->unk18 -= D_ovl10_09_8004A408[i];
    if ((D_ovl10_09_8004A408[i] < 0.0f && D_ovl10_09_8004A2F4[i]->unk40->unk18 <= D_ovl10_09_8004A40C[i]) ||
        (D_ovl10_09_8004A408[i] > 0.0f && D_ovl10_09_8004A40C[i] <= D_ovl10_09_8004A2F4[i]->unk40->unk18)) {
        D_ovl10_09_8004A2FC[i] = (D_ovl10_09_8004A2FC[i] + 1) % 2;
        if (D_ovl10_09_8004A2FC[i] != 0) {
            v = 1;
            w = 0;
        } else {
            v = 15;
            w = 1;
        }
        func_ovl10_09_80048140(D_ovl10_09_8004A2E8[i][0], D_ovl10_09_8004A2E8[i][1], D_ovl10_09_8004A2E8[i][2] + 1, v);
        func_ovl10_09_80048140(D_ovl10_09_8004A2E8[i][0], D_ovl10_09_8004A2E8[i][1], D_ovl10_09_8004A2E8[i][2] + 2, v);
        func_ovl10_09_80048140(D_ovl10_09_8004A2E8[i][0], D_ovl10_09_8004A2E8[i][1] + 1, D_ovl10_09_8004A2E8[i][2] + 1, w);
        func_ovl10_09_80048140(D_ovl10_09_8004A2E8[i][0], D_ovl10_09_8004A2E8[i][1] + 1, D_ovl10_09_8004A2E8[i][2] + 2, w);
        D_ovl10_09_8004A2F4[i]->unk40->unk18 = D_ovl10_09_8004A40C[i];
        D_ovl10_09_8004A2F8[i]->unk40->unk18 = D_ovl10_09_8004A410[i];
        func_ovl10_09_80045C10();
        D_ovl10_09_8004A404[i] = 0;
        func_ovl10_09_800491E0(0xA8);
    }
}

void func_ovl10_09_80047024(void) {
    if (D_ovl10_09_8004AC04 != 0) {
        func_ovl10_09_80048F58(0xFF, 0, 0, D_ovl10_09_8004AD10);
    }
    D_ovl10_09_8004AD10 += D_ovl10_09_8004AD14;
    if (D_ovl10_09_8004AD14 == 2 && D_ovl10_09_8004AD10 >= 60) {
        D_ovl10_09_8004AD14 = -2;
        D_ovl10_09_8004AD10 = 60;
    }
    if (D_ovl10_09_8004AD14 == -2 && D_ovl10_09_8004AD10 <= 0) {
        D_ovl10_09_8004AD14 = 2;
        D_ovl10_09_8004AD10 = 0;
        func_ovl10_09_800491E0(0x9E);
    }
    if (D_ovl10_09_8004AC04 == 0) {
        func_ovl10_09_80045C10();
    }
}

void func_ovl10_09_80046E04(void) {
    s32 i;

    i = D_ovl10_09_8004AC10[D_ovl10_09_80049DD8];
    if (D_ovl10_09_8004AC08 == 0) {
        D_ovl10_09_8004AB28[i] += D_ovl10_09_8004AAB8[i];
        D_ovl10_09_8004A418[i]->unk40->unk36 = D_ovl10_09_8004AB28[i];
        D_ovl10_09_8004A488[i]->unk40->unk36 = D_ovl10_09_8004AB28[i] * 0.5f;
        D_ovl10_09_8004A488[i]->unk40->unk2C += D_ovl10_09_8004AB98[i];
        if (D_ovl10_09_8004AAB8[i] > 0.0f && D_ovl10_09_8004A418[i]->unk40->unk36 >= 256) {
            D_ovl10_09_8004A418[i]->unk40->unk36 = 255;
            D_ovl10_09_8004A488[i]->unk40->unk36 = 128;
            func_ovl10_09_80045C10();
        }
        if (D_ovl10_09_8004AAB8[i] < 0.0f && D_ovl10_09_8004A418[i]->unk40->unk36 < 0) {
            if (D_ovl10_09_8004A418[i] != NULL) {
                func_ovl10_09_80048B20(D_ovl10_09_8004A418[i]);
                func_ovl10_09_80048B20(D_ovl10_09_8004A488[i]);
                D_ovl10_09_8004A418[i] = NULL;
                func_ovl10_09_80046898(i, 0);
            }
            func_ovl10_09_80045C10();
        }
    } else {
        func_ovl10_09_80045C10();
    }
}

void func_ovl10_09_80046C10(void) {
    s32 i;
    s32 j;
    s32 found;
    s32 k;

    i = D_ovl10_09_8004A720[D_ovl10_09_80049DD8];
    found = -1;
    j = 0;
    do {
        if (D_ovl10_09_8004A828[i] == D_ovl10_09_8004A908[i][j]) {
            D_ovl10_09_8004A640[i] = 0;
            found = 0;
            D_ovl10_09_8004A6B0[i]++;
            func_ovl10_09_800468FC(i, 1);
        }
        j++;
    } while (D_ovl10_09_8004A908[i][j] != -1 && found == -1);
    if (D_ovl10_09_8004A6B0[i] != 0) {
        D_ovl10_09_8004A640[i]++;
        if (D_ovl10_09_8004A640[i] == 80) {
            D_ovl10_09_8004A6B0[i] = 0;
            func_ovl10_09_800468FC(i, 0);
        }
    }
    if (D_ovl10_09_8004AC08 != 0) {
        for (k = 0; k < D_ovl10_09_8004A820; k++) {
            if (D_ovl10_09_8004A418[k] != NULL) {
                func_ovl10_09_80048B20(D_ovl10_09_8004A418[k]);
                func_ovl10_09_80048B20(D_ovl10_09_8004A488[k]);
                D_ovl10_09_8004A418[k] = NULL;
                func_ovl10_09_80046898(k, 0);
                D_ovl10_09_8004A6B0[k] = 0;
            }
        }
        func_ovl10_09_80045C10();
    }
    D_ovl10_09_8004A828[i]++;
    if (D_ovl10_09_8004A828[i] == D_ovl10_09_8004A898[i]) {
        D_ovl10_09_8004A828[i] = 40;
    }
}

void func_ovl10_09_800468FC(s32 arg0, s32 arg1) {
    Vec3f pos;
    Vec3f pos2;

    D_ovl10_09_8004AC10[func_ovl10_09_800430D8(func_ovl10_09_80046E04)] = arg0;
    if (arg1 != 0) {
        D_ovl10_09_8004A418[arg0] = func_ovl10_09_80048B30(0xBE, 0x01080000, 0x10, 0);
        func_ovl10_09_80048168(D_ovl10_09_8004A4F8[arg0][0], D_ovl10_09_8004A4F8[arg0][1],
                               D_ovl10_09_8004A4F8[arg0][2], &pos, 0);
        D_ovl10_09_8004A418[arg0]->unk40->unk10 = pos.x;
        D_ovl10_09_8004A418[arg0]->unk40->unk14 = pos.y + 10.0f;
        D_ovl10_09_8004A418[arg0]->unk40->unk18 = pos.z;
        D_ovl10_09_8004A418[arg0]->unk40->unk36 = 0;
        D_ovl10_09_8004AAB8[arg0] = 12.0f;
        D_ovl10_09_8004AB28[arg0] = 0.0f;
        D_ovl10_09_8004A488[arg0] = func_ovl10_09_80048B30(0x2A7, 0x01080000, 0x10, 0);
        func_ovl10_09_80048168(D_ovl10_09_8004A4F8[arg0][0], D_ovl10_09_8004A4F8[arg0][1],
                               D_ovl10_09_8004A4F8[arg0][2], &pos, 0);
        D_ovl10_09_8004A488[arg0]->unk40->unk10 = pos.x + 40.0f;
        D_ovl10_09_8004A488[arg0]->unk40->unk14 = pos.y;
        D_ovl10_09_8004A488[arg0]->unk40->unk18 = pos.z + 40.0f;
        D_ovl10_09_8004A488[arg0]->unk40->unk28 = 2.0f;
        D_ovl10_09_8004A488[arg0]->unk40->unk2C = 2.0f;
        D_ovl10_09_8004A488[arg0]->unk40->unk30 = 2.0f;
        D_ovl10_09_8004A488[arg0]->unk40->unkC |= 0x8000;
        func_ovl10_09_80048810(D_ovl10_09_8004A488[arg0]->unk40, 2);
        func_ovl10_09_80048818(D_ovl10_09_8004A488[arg0]->unk40, 0x2A8, 0, 0);
        func_ovl10_09_80048818(D_ovl10_09_8004A488[arg0]->unk40, 0x2A8, 1, 1);
        D_ovl10_09_8004A488[arg0]->unk40->unk36 = 0;
        D_ovl10_09_8004AB98[arg0] = 0.1f;
        func_ovl10_09_80046898(arg0, 1);
        func_ovl10_09_80048BD8(D_ovl10_09_8004A488[arg0], &pos2);
        func_ovl10_09_80049208(0xAA, &pos2);
    } else {
        D_ovl10_09_8004AAB8[arg0] = -6.0f;
        D_ovl10_09_8004AB28[arg0] = 255.0f;
        D_ovl10_09_8004AB98[arg0] = -0.1f;
    }
}

void func_ovl10_09_80046898(s32 arg0, s32 arg1) {
    s32 v;

    if (arg1 != 0) {
        v = 1;
    } else {
        v = 11;
    }
    func_ovl10_09_800481B8(D_ovl10_09_8004A4F8[arg0][0], D_ovl10_09_8004A4F8[arg0][1], D_ovl10_09_8004A4F8[arg0][2],
                           D_ovl10_09_8004A4F8[arg0][0] + 1, D_ovl10_09_8004A4F8[arg0][2] + 1, v);
}

void func_ovl10_09_8004657C(void) {
    s32 i;
    s32 j;
    s32 v;

    i = D_ovl10_09_80049B08[D_ovl10_09_80049DD8];
    D_ovl10_09_80049C10[i]--;
    func_ovl10_09_800464DC(i);
    if (D_ovl10_09_80049C10[i] == 0) {
        D_ovl10_09_80049AD8[i] = (D_ovl10_09_80049AD8[i] + 2) & 3;
        if (D_ovl10_09_80049AD8[i] & 2) {
            func_ovl10_09_800438F4(i);
            D_ovl10_09_80049C10[i] = func_ovl10_09_80048E18(60) + 90;
            v = 9;
        } else {
            func_ovl10_09_8004387C(i);
            v = 1;
            D_ovl10_09_80049C10[i] = 120;
        }
        if (D_ovl10_09_80049AA8[i] & 1) {
            for (j = 0; j < D_ovl10_09_80049CA0[i]; j++) {
                func_ovl10_09_80048140(D_ovl10_09_80049A20[i][0] + j, D_ovl10_09_80049A20[i][1], D_ovl10_09_80049A20[i][2], v);
            }
        } else {
            for (j = 0; j < D_ovl10_09_80049CA0[i]; j++) {
                func_ovl10_09_80048140(D_ovl10_09_80049A20[i][0], D_ovl10_09_80049A20[i][1], D_ovl10_09_80049A20[i][2] + j, v);
            }
        }
        if (D_ovl10_09_8004AC04 != 0) {
            D_ovl10_09_80049C10[i] = 30;
        }
    }
    if (D_ovl10_09_80049C40[i] != 0) {
        if (D_ovl10_09_80049AD8[i] & 2) {
            func_ovl10_09_8004387C(i);
            if (D_ovl10_09_80049AA8[i] & 1) {
                for (j = 0; j < D_ovl10_09_80049CA0[i]; j++) {
                    func_ovl10_09_80048140(D_ovl10_09_80049A20[i][0] + j, D_ovl10_09_80049A20[i][1], D_ovl10_09_80049A20[i][2], 1);
                }
            } else {
                for (j = 0; j < D_ovl10_09_80049CA0[i]; j++) {
                    func_ovl10_09_80048140(D_ovl10_09_80049A20[i][0], D_ovl10_09_80049A20[i][1], D_ovl10_09_80049A20[i][2] + j, 1);
                }
            }
        }
        func_ovl10_09_80045C10();
    }
}

void func_ovl10_09_800464DC(s32 arg0) {
    f32 d;

    if (D_ovl10_09_80049AD8[arg0] & 1) {
        d = func_ovl10_09_8004626C(arg0);
        if (D_ovl10_09_80049C9C == -1 && (D_ovl10_09_80049AD8[arg0] & 2) && d <= 300.0f) {
            func_ovl10_09_800462C4(arg0, 1);
        } else {
            func_ovl10_09_800462C4(arg0, 0);
        }
    }
}

void func_ovl10_09_80046428(void) {
    s32 i;
    f32 d;

    i = D_ovl10_09_80049B08[D_ovl10_09_80049DD8];
    d = func_ovl10_09_8004626C(i);
    if (D_ovl10_09_80049C9C == -1 && d <= 300.0f) {
        func_ovl10_09_800462C4(i, 1);
    } else {
        func_ovl10_09_800462C4(i, 0);
    }
    if (D_ovl10_09_80049C40[i] != 0) {
        func_ovl10_09_80045C10();
    }
}

void func_ovl10_09_800462C4(s32 arg0, s32 arg1) {
    s32 pad[2];
    Vec3f pos;
    s32 i;
    s32 n;

    n = 0;
    for (i = 0; i < D_ovl10_09_80049C08; i++) {
        if ((D_ovl10_09_80049AD8[i] & 2) && func_ovl10_09_8004626C(i) <= 300.0f) {
            n++;
        }
    }
    if (arg1 != 0 && n == 1 && D_ovl10_09_80049C9C == -1) {
        func_ovl10_09_80048BD8(D_ovl10_09_800499F0[arg0], &pos);
        D_ovl10_09_80049C9C = func_ovl10_09_80049208(0x9D, &pos);
    }
    if (arg1 == 0 && n == 0 && D_ovl10_09_80049C9C != -1) {
        func_ovl10_09_80043018();
    }
}

f32 func_ovl10_09_8004626C(s32 arg0) {
    s32 pad;
    Vec3f a;
    Vec3f b;

    func_ovl10_09_80048BD8(D_ovl10_09_800499F0[arg0], &a);
    func_ovl10_09_80048BD8(func_ovl10_09_80048348(func_ovl10_09_800482E8()), &b);
    return func_ovl10_09_80048AB0(&a, &b);
}

void func_ovl10_09_800460B4(void) {
    s32 i;

    i = D_ovl10_09_80049F78[D_ovl10_09_80049DD8];
    D_ovl10_09_80049EE8[i]->unk40->unk28 += D_ovl10_09_8004A0B0[i];
    D_ovl10_09_80049EE8[i]->unk40->unk2C += D_ovl10_09_8004A0B0[i];
    D_ovl10_09_80049EE8[i]->unk40->unk30 += D_ovl10_09_8004A0B0[i];
    if ((D_ovl10_09_8004A0B0[i] > 0.0f && D_ovl10_09_8004A0C8[i] <= D_ovl10_09_80049EE8[i]->unk40->unk28) ||
        (D_ovl10_09_8004A0B0[i] < 0.0f && D_ovl10_09_80049EE8[i]->unk40->unk28 <= D_ovl10_09_8004A0C8[i])) {
        D_ovl10_09_80049EE8[i]->unk40->unk28 = D_ovl10_09_8004A0C8[i];
        D_ovl10_09_80049EE8[i]->unk40->unk2C = D_ovl10_09_8004A0C8[i];
        D_ovl10_09_80049EE8[i]->unk40->unk30 = D_ovl10_09_8004A0C8[i];
        if (D_ovl10_09_80049F60[i] == 0) {
            func_ovl10_09_8004607C(i);
        }
        func_ovl10_09_80044DDC(i);
        D_ovl10_09_8004A098[i] = 0;
        func_ovl10_09_80045C10();
    }
}

void func_ovl10_09_8004607C(s32 arg0) {
    func_ovl10_09_80048B20(D_ovl10_09_80049EE8[arg0]);
    D_ovl10_09_80049EE8[arg0] = NULL;
}

void func_ovl10_09_80045FE0(void) {
    UnkStructA *obj;

    if (D_ovl10_09_8004A0E0 <= 0.0f) {
        D_ovl10_09_8004A0E0 = 0.0f;
        func_ovl10_09_80045C10();
    }
    obj = func_ovl10_09_80048348(func_ovl10_09_800482E8());
    obj->unk40->unk36 = D_ovl10_09_8004A0E0;
    D_ovl10_09_8004A0E0 -= 2.0f;
}

void func_ovl10_09_80045F48(void) {
    if (D_ovl10_09_8004A0E4 >= 10.0f) {
        D_ovl10_09_8004A0E4 = 10.0f;
        func_ovl10_09_80045C10();
    }
    func_ovl10_09_80048348(func_ovl10_09_800482E8())->unk40->unk28 = D_ovl10_09_8004A0E4;
    D_ovl10_09_8004A0E4 += D_ovl10_09_8004A0EC;
    D_ovl10_09_8004A0EC += 0.1f;
}

void func_ovl10_09_80045E58(void) {
    UnkStructA *obj;
    Vec3f pos;

    obj = func_ovl10_09_80048348(func_ovl10_09_800482E8());
    if (D_ovl10_09_8004A0E8 <= 0.0f) {
        D_ovl10_09_8004A0E8 = 0.0f;
        func_ovl10_09_80048BD8(obj, &pos);
        pos.y += 80.0f;
        func_ovl10_09_800490B0(2, &pos, 0);
        func_ovl10_09_800491E0(0x44);
        func_ovl10_09_80048B10(obj, 0x01000000);
        func_ovl10_09_80045C10();
    }
    obj->unk40->unk2C = D_ovl10_09_8004A0E8;
    obj->unk40->unk30 = D_ovl10_09_8004A0E8;
    D_ovl10_09_8004A0E8 -= D_ovl10_09_8004A0F0;
    D_ovl10_09_8004A0F0 += 0.0125f;
}

void func_ovl10_09_80045DFC(void) {
    func_ovl10_09_80048278(1);
    func_ovl10_09_800482F8(1);
    func_ovl10_09_80045D94();
    func_ovl10_09_80045C64(func_ovl10_09_80045D00);
    func_ovl10_09_80045C48(60);
}

void func_ovl10_09_80045D94(void) {
    UnkStructA *obj;

    D_ovl10_09_8004A0E0 = 255.0f;
    obj = func_ovl10_09_80048348(func_ovl10_09_800482E8());
    func_ovl10_09_80048B08(obj, 0x80000);
    obj->unk40->unkC |= 0x1000;
    func_ovl10_09_800430D8(func_ovl10_09_80045FE0);
}

void func_ovl10_09_80045D00(void) {
    func_ovl10_09_80045CC0();
    func_ovl10_09_80045C80();
    func_ovl10_09_80045C64(func_ovl10_09_80045C2C);
    func_ovl10_09_80045C48(30);
}

void func_ovl10_09_80045CC0(void) {
    D_ovl10_09_8004A0E4 = 1.0f;
    D_ovl10_09_8004A0EC = 0.0f;
    func_ovl10_09_800430D8(func_ovl10_09_80045F48);
}

void func_ovl10_09_80045C80(void) {
    D_ovl10_09_8004A0E8 = 1.0f;
    D_ovl10_09_8004A0F0 = 0.0f;
    func_ovl10_09_800430D8(func_ovl10_09_80045E58);
}

void func_ovl10_09_80045C64(void (*arg0)(void)) {
    D_ovl10_09_80049DE0[D_ovl10_09_80049DD8] = arg0;
}

void func_ovl10_09_80045C48(s32 arg0) {
    D_ovl10_09_80049CD8[D_ovl10_09_80049DD8] = arg0;
}

/* ends the current task (a second copy of 80045C10) */
void func_ovl10_09_80045C2C(void) {
    D_ovl10_09_80049DE0[D_ovl10_09_80049DD8] = NULL;
}

/* clears the running task */
void func_ovl10_09_80045C10(void) {
    D_ovl10_09_80049DE0[D_ovl10_09_80049DD8] = NULL;
}

/* the overlay's handler (the entry returns it) */
void func_ovl10_09_80045A80(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl10_09_800458D8();
            break;
        case 16:
            func_ovl10_09_80044BC4();
            break;
        case 17:
            func_ovl10_09_80044B20();
            break;
        case 18:
            func_ovl10_09_80044A78();
            break;
        case 19:
            func_ovl10_09_800448E4();
            break;
        case 4:
            func_ovl10_09_800448C4();
            break;
        case 5:
            func_ovl10_09_80044820();
            break;
        case 0x52:
            func_ovl10_09_800446F4();
            break;
        case 0x53:
            func_ovl10_09_80043E40();
            break;
        case 0x50:
            func_ovl10_09_80043730();
            break;
        case 1:
            func_ovl10_09_80043068();
            break;
    }
}

void func_ovl10_09_800458D8(void) {
    func_ovl10_09_80048FC0(D_ovl10_09_80049420);
    func_ovl10_09_80049168(0, 0, 0xDE);
    func_ovl10_09_80049168(1, 0x11, 0xEF);
    func_ovl10_09_80049168(2, 0x1A, 0xF8);
    func_ovl10_09_80049168(3, 0x1B, 0xF9);
    func_ovl10_09_80049168(4, 0x18, 0xF6);
    func_ovl10_09_80048108(0x1ED);
    func_ovl10_09_80048110(0x1EE, 0.0f, 0.0f, 0.0f, 0x60, 0);
    func_ovl10_09_80048110(0xC7, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_09_80048110(0xC7, 0.0f, 12000.0f, 0.0f, 0x50, 0);
    func_ovl10_09_80048110(0xBA, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_09_80048120(0x1F6);
    func_ovl10_09_80048F98(0x3C6, 0x3E8, 0, 0xFF, 0xFF);
    func_ovl10_09_80048FA8(0, 0xFF, 0xFF);
    func_ovl10_09_800482B8();
    func_ovl10_09_8004576C(D_ovl10_09_80049540);
    func_ovl10_09_8004559C(D_ovl10_09_800495C8);
    func_ovl10_09_800452BC(D_ovl10_09_8004960C);
    func_ovl10_09_80044FEC(D_ovl10_09_80049444);
    func_ovl10_09_80044EA0(D_ovl10_09_800494AC);
    func_ovl10_09_80044C70(D_ovl10_09_80049620);
    func_ovl10_09_800481F0(func_ovl10_09_800478FC);
    func_ovl10_09_80044BF4();
}

/* reads records of 11 words up to a -1 */
void func_ovl10_09_8004576C(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_09_8004A188[i][0] = arg0[0];
        D_ovl10_09_8004A188[i][1] = arg0[1];
        D_ovl10_09_8004A188[i][2] = arg0[2];
        D_ovl10_09_8004A250[i] = arg0[3];
        D_ovl10_09_8004A200[i] = arg0[4];
        D_ovl10_09_8004A218[i] = arg0[5];
        D_ovl10_09_8004A230[i] = arg0[6];
        D_ovl10_09_8004A268[i] = arg0[7];
        D_ovl10_09_8004A280[i] = arg0[8];
        D_ovl10_09_8004A298[i] = arg0[9];
        D_ovl10_09_8004A2B0[i] = arg0[10];
        arg0 += 11;
        func_ovl10_09_80045650(i);
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_09_8004A248 = i;
}

void func_ovl10_09_800443D4(s32 arg0, s32 arg1) {
    s32 sp38[4] = { 0xBF, 0xC0, 0xC1, 0xC4 };
    Vec3f pos;

    if (arg1 == 1) {
        D_ovl10_09_8004A128[arg0] =
            func_ovl10_09_80048B30(sp38[D_ovl10_09_8004A140[arg0] - 1], 0x01000000, 0xD0, 0);
        func_ovl10_09_80048168(D_ovl10_09_8004A0F8[arg0][0], D_ovl10_09_8004A0F8[arg0][1],
                               D_ovl10_09_8004A0F8[arg0][2], &pos, 0);
        D_ovl10_09_8004A128[arg0]->unk40->unk10 = pos.x;
        D_ovl10_09_8004A128[arg0]->unk40->unk14 = pos.y;
        D_ovl10_09_8004A128[arg0]->unk40->unk18 = pos.z;
    } else {
        func_ovl10_09_80048B20(D_ovl10_09_8004A128[arg0]);
        D_ovl10_09_8004A128[arg0] = NULL;
    }
}

void func_ovl10_09_80045650(s32 arg0) {
    Vec3f pos;
    s32 sp2C[2] = { 0xCA, 0xB2 };

    D_ovl10_09_8004A1D0[arg0] = func_ovl10_09_80048B30(sp2C[D_ovl10_09_8004A218[arg0]], 0x01000000, 0xD0, 0);
    func_ovl10_09_80048168(D_ovl10_09_8004A188[arg0][0], D_ovl10_09_8004A188[arg0][1], D_ovl10_09_8004A188[arg0][2],
                           &pos, 0);
    D_ovl10_09_8004A1D0[arg0]->unk40->unk10 = pos.x;
    D_ovl10_09_8004A1D0[arg0]->unk40->unk14 = pos.y;
    D_ovl10_09_8004A1D0[arg0]->unk40->unk18 = pos.z;
}

void func_ovl10_09_8004559C(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_09_8004A0F8[i][0] = arg0[0];
        D_ovl10_09_8004A0F8[i][1] = arg0[1];
        D_ovl10_09_8004A0F8[i][2] = arg0[2];
        D_ovl10_09_8004A140[i] = arg0[3];
        D_ovl10_09_8004A150[i] = 0;
        arg0 += 4;
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_09_8004A138 = i;
    for (i = 1; i < 5; i++) {
        D_ovl10_09_8004A160[i] = 0;
    }
}

/* reads the gates: records of 4 words up to a -1 */
void func_ovl10_09_800452BC(s32 *arg0) {
    s32 i;
    s32 v;
    Vec3f pos;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_09_8004A2E8[i][0] = arg0[0];
            D_ovl10_09_8004A2E8[i][1] = arg0[1];
            D_ovl10_09_8004A2E8[i][2] = arg0[2];
            D_ovl10_09_8004A2FC[i] = arg0[3];
            arg0 += 4;
            func_ovl10_09_80048168(D_ovl10_09_8004A2E8[i][0], D_ovl10_09_8004A2E8[i][1], D_ovl10_09_8004A2E8[i][2],
                                   &pos, 0);
            D_ovl10_09_8004A2F4[i] = func_ovl10_09_80048B30(0xC2, 0x01000110, 0xD0, 0);
            D_ovl10_09_8004A2F4[i]->unk40->unk10 = pos.x;
            D_ovl10_09_8004A2F4[i]->unk40->unk14 = pos.y;
            D_ovl10_09_8004A2F4[i]->unk40->unk18 = pos.z + 50.0f;
            D_ovl10_09_8004A2F4[i]->unk34 = 50.0f;
            D_ovl10_09_8004A2F4[i]->unk38 = 50.0f;
            D_ovl10_09_8004A2F8[i] = func_ovl10_09_80048B30(0xC2, 0x01000110, 0xD0, 0);
            D_ovl10_09_8004A2F8[i]->unk40->unk10 = pos.x;
            D_ovl10_09_8004A2F8[i]->unk40->unk14 = pos.y;
            D_ovl10_09_8004A2F8[i]->unk40->unk18 = pos.z + 250.0f;
            D_ovl10_09_8004A2F8[i]->unk40->unk20 = 180.0f;
            D_ovl10_09_8004A2F8[i]->unk34 = 50.0f;
            D_ovl10_09_8004A2F8[i]->unk38 = 50.0f;
            if (D_ovl10_09_8004A2FC[i] != 0) {
                v = 1;
                D_ovl10_09_8004A2F4[i]->unk40->unk18 -= 100.0f;
                D_ovl10_09_8004A2F8[i]->unk40->unk18 += 100.0f;
            } else {
                v = 15;
            }
            func_ovl10_09_80048140(D_ovl10_09_8004A2E8[i][0], D_ovl10_09_8004A2E8[i][1], D_ovl10_09_8004A2E8[i][2] + 1, v);
            func_ovl10_09_80048140(D_ovl10_09_8004A2E8[i][0], D_ovl10_09_8004A2E8[i][1], D_ovl10_09_8004A2E8[i][2] + 2, v);
            D_ovl10_09_8004A404[i] = 0;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_09_8004A400 = i;
}

void func_ovl10_09_80044FEC(s32 *arg0) {
    s32 i;
    s32 j;
    s32 flags;
    s32 pad;
    Vec3f pos;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_09_80049A20[i][0] = arg0[0];
            D_ovl10_09_80049A20[i][1] = arg0[1];
            D_ovl10_09_80049A20[i][2] = arg0[2];
            flags = arg0[3];
            D_ovl10_09_80049AA8[i] = flags & 0xF;
            D_ovl10_09_80049CA0[i] = flags >> 4;
            D_ovl10_09_80049C70[i] = arg0[4];
            arg0 += 5;
            func_ovl10_09_80048168(D_ovl10_09_80049A20[i][0], D_ovl10_09_80049A20[i][1], D_ovl10_09_80049A20[i][2],
                                   &pos, 0);
            D_ovl10_09_800499F0[i] = func_ovl10_09_80048B30(0xBD, 0, 0xD0, 0);
            D_ovl10_09_800499F0[i]->unk40->unk10 = pos.x;
            D_ovl10_09_800499F0[i]->unk40->unk14 = pos.y;
            D_ovl10_09_800499F0[i]->unk40->unk18 = pos.z;
            if (D_ovl10_09_80049AA8[i] & 2) {
                D_ovl10_09_800499F0[i]->unk40->unk10 = pos.x + 5.0f;
                D_ovl10_09_800499F0[i]->unk40->unk20 = 270.0f;
            } else {
                D_ovl10_09_800499F0[i]->unk40->unk18 = pos.z - 5.0f;
            }
            func_ovl10_09_80048850(D_ovl10_09_800499F0[i]->unk40, 0, 0x28, 0x190, 0, 0);
            D_ovl10_09_80049AD8[i] = 0;
            if (D_ovl10_09_80049AA8[i] & 1) {
                for (j = 0; j < D_ovl10_09_80049CA0[i]; j++) {
                    func_ovl10_09_80048140(D_ovl10_09_80049A20[i][0] + j, D_ovl10_09_80049A20[i][1], D_ovl10_09_80049A20[i][2], 1);
                }
            } else {
                for (j = 0; j < D_ovl10_09_80049CA0[i]; j++) {
                    func_ovl10_09_80048140(D_ovl10_09_80049A20[i][0] + j, D_ovl10_09_80049A20[i][1], D_ovl10_09_80049A20[i][2], 1);
                }
            }
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_09_80049C08 = i;
    D_ovl10_09_80049C9C = -1;
}

void func_ovl10_09_80044EA0(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_09_80049F00[i][0] = arg0[0];
            D_ovl10_09_80049F00[i][1] = arg0[1];
            D_ovl10_09_80049F00[i][2] = arg0[2];
            D_ovl10_09_80049F48[i] = arg0[3];
            D_ovl10_09_8004A080[i] = arg0[4];
            D_ovl10_09_80049F60[i] = arg0[5];
            arg0 += 6;
            D_ovl10_09_80049EE8[i] = NULL;
            if (D_ovl10_09_80049F60[i] != 0) {
                func_ovl10_09_80043EDC(i);
            }
            func_ovl10_09_80044DDC(i);
            D_ovl10_09_8004A098[i] = 0;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_09_8004A078 = i;
}

void func_ovl10_09_80044DDC(s32 arg0) {
    s32 v;
    s32 w;
    s32 t;
    s32 h;
    s32 pad;

    if (D_ovl10_09_80049F60[arg0] != 0) {
        v = 1;
    } else {
        v = 0;
    }
    if (D_ovl10_09_80049F48[arg0] & 4) {
        w = 6;
        h = 3;
    }
    if (D_ovl10_09_80049F48[arg0] & 8) {
        w = 5;
        h = 1;
    }
    if (D_ovl10_09_80049F48[arg0] & 2) {
        t = h;
        h = w;
        w = t;
    }
    func_ovl10_09_800481B8(D_ovl10_09_80049F00[arg0][0], D_ovl10_09_80049F00[arg0][1], D_ovl10_09_80049F00[arg0][2],
                           D_ovl10_09_80049F00[arg0][0] + w, D_ovl10_09_80049F00[arg0][2] + h, v);
}

void func_ovl10_09_80044C70(s32 *arg0) {
    s32 i;
    s32 j;
    s32 n;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_09_8004A4F8[i][0] = arg0[0];
            D_ovl10_09_8004A4F8[i][1] = arg0[1];
            D_ovl10_09_8004A4F8[i][2] = arg0[2];
            D_ovl10_09_8004A898[i] = arg0[3];
            n = arg0[4];
            arg0 += 5;
            for (j = 0; j < n; j++) {
                D_ovl10_09_8004A908[i][j] = *arg0;
                arg0++;
            }
            D_ovl10_09_8004A908[i][n] = -1;
            D_ovl10_09_8004A6B0[i] = 0;
            D_ovl10_09_8004A418[i] = NULL;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_09_8004A820 = i;
    D_ovl10_09_8004AC04 = 0;
    D_ovl10_09_8004AC08 = 0;
    D_ovl10_09_8004AC0C = 0;
    func_ovl10_09_80048F58(0, 0, 0, 0.0f);
}

void func_ovl10_09_80044BF4(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_09_80049DE0[i] = NULL;
        D_ovl10_09_80049CD8[i] = 0;
    }
    func_ovl10_09_80048C58(func_ovl10_09_80047B70, 0, 0, 0, 0x110);
}

void func_ovl10_09_80044BC4(void) {
    func_ovl10_09_800482C0(0x18, 2, 0x10);
    D_ovl10_09_80049CCC = 3;
}

void func_ovl10_09_80044B20(void) {
    D_ovl10_09_8004A174 = 0;
    D_ovl10_09_8004A1EC = 0;
    D_ovl10_09_8004A2C8 = -1100.0f;
    D_ovl10_09_8004A2CC = 90.0f;
    D_ovl10_09_8004A1F0 = 1;
    D_ovl10_09_8004A1F4 = 0xF;
    D_ovl10_09_8004A2D0 = 21.0f;
    D_ovl10_09_8004A2D4 = -0.2f;
    D_ovl10_09_8004A2D8 = 50.0f;
    D_ovl10_09_8004A2DC = 50.0f;
    func_ovl10_09_80044914();
    D_ovl10_09_80049CCC = 1;
}

void func_ovl10_09_80044A78(void) {
    D_ovl10_09_8004A174 = 1;
    D_ovl10_09_8004A1EC = 4;
    D_ovl10_09_8004A2C8 = 1100.0f;
    D_ovl10_09_8004A2CC = 90.0f;
    D_ovl10_09_8004A1F0 = 1;
    D_ovl10_09_8004A1F4 = 0xF;
    D_ovl10_09_8004A2D0 = -21.0f;
    D_ovl10_09_8004A2D4 = 0.2f;
    D_ovl10_09_8004A2D8 = 50.0f;
    D_ovl10_09_8004A2DC = 50.0f;
    func_ovl10_09_80044914();
    D_ovl10_09_80049CCC = 2;
}

void func_ovl10_09_80044914(void) {
    f32 y;

    D_ovl10_09_8004A2E0 = -1.0f;
    y = func_ovl10_09_800481A8(D_ovl10_09_8004A1EC);
    func_ovl10_09_800482C0(D_ovl10_09_8004A1F0, D_ovl10_09_8004A1EC, D_ovl10_09_8004A1F4);
    func_ovl10_09_800482F8(1);
    D_ovl10_09_8004A1E8 = func_ovl10_09_80048348(func_ovl10_09_800482E8());
    D_ovl10_09_8004A1E8->unk70 = 0.0f;
    D_ovl10_09_8004A1E8->unk40->unk10 += D_ovl10_09_8004A2D8;
    D_ovl10_09_8004A1E8->unk40->unk14 += D_ovl10_09_8004A2C8;
    D_ovl10_09_8004A1E8->unk40->unk18 += D_ovl10_09_8004A2DC;
    D_ovl10_09_8004A1E8->unk40->unk20 = D_ovl10_09_8004A2CC;
    D_ovl10_09_8004A1D0[D_ovl10_09_8004A174]->unk40->unk14 += D_ovl10_09_8004A2C8;
    func_ovl10_09_80043150(D_ovl10_09_8004A174, D_ovl10_09_8004A2D0, D_ovl10_09_8004A2D4, y);
    D_ovl10_09_8004A1E8->unk70 = 1.6333334f;
}

void func_ovl10_09_800448E4(void) {
    func_ovl10_09_800482C0(0x2D, 0, 0x1B);
    D_ovl10_09_80049CCC = 3;
}

void func_ovl10_09_800448C4(void) {
    func_ovl10_09_80048318();
}

void func_ovl10_09_80044820(void) {
    switch (D_ovl10_09_80049CCC) {
        case 1:
            func_ovl10_09_80048C78(0x78);
            func_ovl10_09_80048308(0x40, 3, 8.5f, 2, 0, 1, 1);
            break;
        case 2:
            func_ovl10_09_80048C78(0x78);
            func_ovl10_09_80048308(0x40, 3, 8.5f, 2, 0, 1, 1);
            break;
    }
}

void func_ovl10_09_800446F4(void) {
    s32 i;

    func_ovl10_09_800491E0(0x29);
    func_ovl10_09_8004452C();
    if (D_ovl10_09_8004A160[3] != 0) {
        func_ovl10_09_80043B78(0, 1);
        if (D_ovl10_09_8004AC04 == 0) {
            func_ovl10_09_80044308();
        }
    } else {
        func_ovl10_09_80043B78(0, 0);
        if (D_ovl10_09_8004AC04 == 0) {
            func_ovl10_09_800437B4();
        }
    }
    if (func_ovl10_09_800482D8(D_ovl10_09_8004A0F8[2][0], D_ovl10_09_8004A0F8[2][1], D_ovl10_09_8004A0F8[2][2],
                               D_ovl10_09_8004A0F8[2][0] + 1, D_ovl10_09_8004A0F8[2][2] + 1) != 0 &&
        D_ovl10_09_8004AC04 != 0) {
        for (i = 0; i < D_ovl10_09_80049C08; i++) {
            func_ovl10_09_80043924(i, 0);
        }
        func_ovl10_09_80043DC8(0);
    }
    func_ovl10_09_80044258();
    func_ovl10_09_800441B4();
}

void func_ovl10_09_8004452C(void) {
    s32 found;
    s32 i;

    found = -1;
    i = 0;
    do {
        if (func_ovl10_09_800482D8(D_ovl10_09_8004A0F8[i][0], D_ovl10_09_8004A0F8[i][1], D_ovl10_09_8004A0F8[i][2],
                                   D_ovl10_09_8004A0F8[i][0] + 1, D_ovl10_09_8004A0F8[i][2] + 1) != 0) {
            found = i;
        }
        i++;
    } while (i < D_ovl10_09_8004A138 && found == -1);
    if (found != -1) {
        D_ovl10_09_8004A150[found] = (D_ovl10_09_8004A150[found] + 1) % 2;
        func_ovl10_09_800443D4(found, D_ovl10_09_8004A150[found]);
        D_ovl10_09_8004A160[D_ovl10_09_8004A140[found]] = (D_ovl10_09_8004A160[D_ovl10_09_8004A140[found]] + 1) % 2;
        if (D_ovl10_09_8004A150[found] == 1 && D_ovl10_09_8004A140[found] != 4) {
            for (i = 0; i < D_ovl10_09_8004A138; i++) {
                if (i != found && D_ovl10_09_8004A140[i] != 4 && D_ovl10_09_8004A150[i] == 1) {
                    D_ovl10_09_8004A150[i] = 0;
                    func_ovl10_09_800443D4(i, 0);
                    D_ovl10_09_8004A160[D_ovl10_09_8004A140[i]] = 0;
                }
            }
        }
    }
}

void func_ovl10_09_80044308(void) {
    s32 i;

    if (D_ovl10_09_8004AC0C == 0) {
        for (i = 0; i < D_ovl10_09_8004A820; i++) {
            D_ovl10_09_8004A720[func_ovl10_09_800430D8(func_ovl10_09_80046C10)] = i;
            D_ovl10_09_8004A828[i] = 0;
            D_ovl10_09_8004A640[i] = 0;
        }
        D_ovl10_09_8004AC0C = 1;
        D_ovl10_09_8004AC08 = 0;
    }
}

void func_ovl10_09_80044258(void) {
    s32 i;

    if (D_ovl10_09_8004AC04 == 0) {
        for (i = 0; i < D_ovl10_09_80049C08; i++) {
            if (D_ovl10_09_80049AD8[i] != D_ovl10_09_8004A160[D_ovl10_09_80049C70[i]]) {
                func_ovl10_09_80043924(i, D_ovl10_09_8004A160[D_ovl10_09_80049C70[i]]);
            }
        }
    }
}

void func_ovl10_09_800441B4(void) {
    s32 i;

    for (i = 0; i < D_ovl10_09_8004A078; i++) {
        if (D_ovl10_09_80049F60[i] != D_ovl10_09_8004A160[D_ovl10_09_8004A080[i]]) {
            func_ovl10_09_800440B8(i, D_ovl10_09_8004A160[D_ovl10_09_8004A080[i]]);
        }
    }
}

void func_ovl10_09_800440B8(s32 arg0, s32 arg1) {
    D_ovl10_09_80049F60[arg0] = arg1;
    if (D_ovl10_09_8004A098[arg0] == 0) {
        D_ovl10_09_80049F78[func_ovl10_09_800430D8(func_ovl10_09_800460B4)] = arg0;
    }
    if (arg1 != 0) {
        D_ovl10_09_8004A0B0[arg0] = 0.05f;
        D_ovl10_09_8004A0C8[arg0] = 1.0f;
        if (D_ovl10_09_80049EE8[arg0] == NULL) {
            func_ovl10_09_80043EDC(arg0);
        }
        func_ovl10_09_800491E0(0xA2);
    } else {
        D_ovl10_09_8004A0B0[arg0] = -0.05f;
        D_ovl10_09_8004A0C8[arg0] = 0.0f;
    }
    D_ovl10_09_8004A098[arg0] = 1;
}

void func_ovl10_09_80043EDC(s32 arg0) {
    s32 sp40[2] = { 0xC5, 0xC6 };
    Vec3f pos;

    func_ovl10_09_80048168(D_ovl10_09_80049F00[arg0][0], D_ovl10_09_80049F00[arg0][1], D_ovl10_09_80049F00[arg0][2], &pos, 0);
    D_ovl10_09_80049EE8[arg0] = func_ovl10_09_80048B30(sp40[(D_ovl10_09_80049F48[arg0] >> 2) - 1], 0x01080000, 0xD0, 0);
    D_ovl10_09_80049EE8[arg0]->unk40->unk10 = pos.x;
    D_ovl10_09_80049EE8[arg0]->unk40->unk14 = pos.y;
    D_ovl10_09_80049EE8[arg0]->unk40->unk18 = pos.z;
    D_ovl10_09_80049EE8[arg0]->unk40->unk28 = 0.0f;
    D_ovl10_09_80049EE8[arg0]->unk40->unk2C = 0.0f;
    D_ovl10_09_80049EE8[arg0]->unk40->unk30 = 0.0f;
    if (D_ovl10_09_80049F48[arg0] & 2) {
        if (D_ovl10_09_80049F48[arg0] & 4) {
            D_ovl10_09_80049EE8[arg0]->unk40->unk18 += 600.0f;
        }
        if (D_ovl10_09_80049F48[arg0] & 8) {
            D_ovl10_09_80049EE8[arg0]->unk40->unk18 += 500.0f;
        }
        D_ovl10_09_80049EE8[arg0]->unk40->unk20 = 90.0f;
    }
}

void func_ovl10_09_80043E40(void) {
    s32 i;

    if (func_ovl10_09_80043460(2) == 0) {
        func_ovl10_09_80043DC8(1);
        func_ovl10_09_80043B78(0, 0);
        for (i = 0; i < D_ovl10_09_80049C08; i++) {
            func_ovl10_09_80043924(i, 1);
        }
        if (D_ovl10_09_8004AC0C != 0) {
            func_ovl10_09_800437B4();
        }
    }
}

void func_ovl10_09_80043DC8(s32 arg0) {
    if (arg0 != D_ovl10_09_8004AC04) {
        D_ovl10_09_8004AC04 = arg0;
        if (arg0 == 1) {
            func_ovl10_09_80043D88();
        } else {
            func_ovl10_09_80048F58(0, 0, 0, 0.0f);
        }
    }
}

void func_ovl10_09_80043D88(void) {
    D_ovl10_09_8004AD10 = 0;
    D_ovl10_09_8004AD14 = 2;
    func_ovl10_09_800430D8(func_ovl10_09_80047024);
    func_ovl10_09_800491E0(0x9E);
}

/* opens (arg1 1) or closes the gate */
void func_ovl10_09_80043B78(s32 arg0, s32 arg1) {
    s32 pad;
    Vec3f pos;

    if (arg1 != D_ovl10_09_8004A2FC[arg0]) {
        if (D_ovl10_09_8004A404[arg0] == 0) {
            D_ovl10_09_8004A300[func_ovl10_09_800430D8(func_ovl10_09_80047104)] = arg0;
        }
        if (arg1 != 0) {
            D_ovl10_09_8004A40C[arg0] = D_ovl10_09_8004A2F4[arg0]->unk40->unk18 - 100.0f;
            D_ovl10_09_8004A410[arg0] = D_ovl10_09_8004A2F8[arg0]->unk40->unk18 + 100.0f;
            D_ovl10_09_8004A408[arg0] = -5.0f;
            func_ovl10_09_80048140(D_ovl10_09_8004A2E8[arg0][0], D_ovl10_09_8004A2E8[arg0][1], D_ovl10_09_8004A2E8[arg0][2] + 1, 0);
            func_ovl10_09_80048140(D_ovl10_09_8004A2E8[arg0][0], D_ovl10_09_8004A2E8[arg0][1], D_ovl10_09_8004A2E8[arg0][2] + 2, 0);
        } else {
            D_ovl10_09_8004A40C[arg0] = D_ovl10_09_8004A2F4[arg0]->unk40->unk18 + 100.0f;
            D_ovl10_09_8004A410[arg0] = D_ovl10_09_8004A2F8[arg0]->unk40->unk18 - 100.0f;
            D_ovl10_09_8004A408[arg0] = 5.0f;
            func_ovl10_09_80048140(D_ovl10_09_8004A2E8[arg0][0], D_ovl10_09_8004A2E8[arg0][1], D_ovl10_09_8004A2E8[arg0][2] + 1, 9);
            func_ovl10_09_80048140(D_ovl10_09_8004A2E8[arg0][0], D_ovl10_09_8004A2E8[arg0][1], D_ovl10_09_8004A2E8[arg0][2] + 2, 9);
        }
        func_ovl10_09_80048BD8(D_ovl10_09_8004A2F4[arg0], &pos);
        D_ovl10_09_8004A404[arg0] = 1;
    }
}

void func_ovl10_09_80043924(s32 arg0, s32 arg1) {
    s32 j;
    s32 v;
    s32 pad[2];

    if (arg1 != (D_ovl10_09_80049AD8[arg0] & 1)) {
        if (arg1 != 0) {
            D_ovl10_09_80049AD8[arg0] |= 1;
        } else {
            D_ovl10_09_80049AD8[arg0] &= ~1;
        }
        if (D_ovl10_09_80049AA8[arg0] & 4) {
            func_ovl10_09_800438F4(arg0);
            if (arg1 != 0) {
                v = 9;
                D_ovl10_09_80049AD8[arg0] |= 2;
                /* func_ovl10_09_800438AC(arg0), written out */
                D_ovl10_09_80049B08[func_ovl10_09_800430D8(func_ovl10_09_80046428)] = arg0;
                D_ovl10_09_80049C40[arg0] = 0;
            } else {
                D_ovl10_09_80049AD8[arg0] &= ~2;
                func_ovl10_09_8004387C(arg0);
                v = 1;
                func_ovl10_09_800437CC(arg0);
            }
            /* Nothing, but it keeps arg0 in v1 for the loops. */
            if (arg0) {
            }
            if (D_ovl10_09_80049AA8[arg0] & 1) {
                for (j = 0; j < D_ovl10_09_80049CA0[arg0]; j++) {
                    func_ovl10_09_80048140(D_ovl10_09_80049A20[arg0][0] + j, D_ovl10_09_80049A20[arg0][1], D_ovl10_09_80049A20[arg0][2], v);
                }
            } else {
                for (j = 0; j < D_ovl10_09_80049CA0[arg0]; j++) {
                    func_ovl10_09_80048140(D_ovl10_09_80049A20[arg0][0], D_ovl10_09_80049A20[arg0][1], D_ovl10_09_80049A20[arg0][2] + j, v);
                }
            }
        }
        if (D_ovl10_09_80049AA8[arg0] & 8) {
            if (arg1 != 0) {
                func_ovl10_09_800437E4(arg0);
            } else {
                func_ovl10_09_800437CC(arg0);
            }
        }
    }
}

void func_ovl10_09_800438F4(s32 arg0) {
    func_ovl10_09_80048B08(D_ovl10_09_800499F0[arg0], 0x01000000);
}

void func_ovl10_09_800438AC(s32 arg0) {
    D_ovl10_09_80049B08[func_ovl10_09_800430D8(func_ovl10_09_80046428)] = arg0;
    D_ovl10_09_80049C40[arg0] = 0;
}

void func_ovl10_09_8004387C(s32 arg0) {
    func_ovl10_09_80048B10(D_ovl10_09_800499F0[arg0], 0x01000000);
}

void func_ovl10_09_800437E4(s32 arg0) {
    D_ovl10_09_80049B08[func_ovl10_09_800430D8(func_ovl10_09_8004657C)] = arg0;
    D_ovl10_09_80049C40[arg0] = 0;
    if (D_ovl10_09_8004AC04 != 0) {
        D_ovl10_09_80049C10[arg0] = 30;
    } else {
        D_ovl10_09_80049C10[arg0] = func_ovl10_09_80048E18(60) + 90;
    }
    D_ovl10_09_80049AD8[arg0] = 1;
}

void func_ovl10_09_800437CC(s32 arg0) {
    D_ovl10_09_80049C40[arg0] = 1;
}

void func_ovl10_09_800437B4(void) {
    D_ovl10_09_8004AC08 = 1;
    D_ovl10_09_8004AC0C = 0;
}

void func_ovl10_09_80043730(void) {
    if (func_ovl10_09_800482D8(0x2C, 0, 0x1C, 0x2D, 0x1D) != 0) {
        func_ovl10_09_800430D8(func_ovl10_09_80045DFC);
        func_ovl10_09_80048C78(0x78);
        D_ovl10_09_800499D4 = 0x6E;
        D_ovl10_09_800499D8 = 0x12;
        func_ovl10_09_80048200(0x6E, 0x12, 0);
    } else {
        func_ovl10_09_80043460(1);
    }
}

s32 func_ovl10_09_80043460(s32 arg0) {
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    if (arg0 == 2) {
        do {
            if (D_ovl10_09_8004A200[i] == 2 && D_ovl10_09_8004A218[i] == 1 &&
                func_ovl10_09_800482D8(D_ovl10_09_8004A188[i][0], D_ovl10_09_8004A188[i][1],
                                       D_ovl10_09_8004A188[i][2], D_ovl10_09_8004A188[i][0] + 1,
                                       D_ovl10_09_8004A188[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_09_8004A248 && found == 0);
        if (found) {
            D_ovl10_09_8004A174 = i;
            if (D_ovl10_09_8004A250[i] < D_ovl10_09_8004A188[i][1]) {
                D_ovl10_09_8004A2D0 = 0.0f;
                D_ovl10_09_8004A2D4 = -0.2f;
            } else {
                D_ovl10_09_8004A2D0 = -0.0f;
                D_ovl10_09_8004A2D4 = 0.2f;
            }
        }
    } else {
        do {
            if (func_ovl10_09_800482D8(D_ovl10_09_8004A188[i][0], D_ovl10_09_8004A188[i][1],
                                       D_ovl10_09_8004A188[i][2], D_ovl10_09_8004A188[i][0] + 1,
                                       D_ovl10_09_8004A188[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_09_8004A248 && found == 0);
    }
    if (found) {
        D_ovl10_09_8004A174 = i;
        if (D_ovl10_09_8004A250[i] < D_ovl10_09_8004A188[i][1]) {
            D_ovl10_09_8004A2D0 = 0.0f;
            D_ovl10_09_8004A2D4 = -0.2f;
        } else {
            D_ovl10_09_8004A2D0 = -0.0f;
            D_ovl10_09_8004A2D4 = 0.2f;
        }
        if (arg0 == 2) {
            func_ovl10_09_80043324();
        } else {
            D_ovl10_09_8004A1F8 = D_ovl10_09_8004A268[i];
            D_ovl10_09_8004A1FC = D_ovl10_09_8004A280[i];
            func_ovl10_09_80043238();
        }
    }
    return found;
}

void func_ovl10_09_80043324(void) {
    s32 out[6];
    f32 a;
    f32 b;
    s32 i;

    i = D_ovl10_09_8004A174;
    a = func_ovl10_09_800481A8(D_ovl10_09_8004A250[i]);
    b = func_ovl10_09_800481A8(D_ovl10_09_8004A188[i][1]);
    func_ovl10_09_80048330(0x40);
    func_ovl10_09_80048320(1);
    D_ovl10_09_8004A1E8 = func_ovl10_09_80048348(func_ovl10_09_800482E8());
    D_ovl10_09_8004A2E0 = (a - b) * 0.5f;
    D_ovl10_09_8004A2E0 += b;
    D_ovl10_09_8004A1E8->unk70 = 0.0f;
    func_ovl10_09_80048160(D_ovl10_09_8004A1E8->unk40->unk10, D_ovl10_09_8004A1E8->unk40->unk14,
                           D_ovl10_09_8004A1E8->unk40->unk18, out, 2);
    func_ovl10_09_800482F8(1);
    func_ovl10_09_800489D0(10.0f);
    func_ovl10_09_800489D8(5.0f);
    func_ovl10_09_800489F0(0.0f);
    func_ovl10_09_80043150(i, D_ovl10_09_8004A2D0, D_ovl10_09_8004A2D4, a);
}

void func_ovl10_09_80043238(void) {
    s32 out[6];
    s32 pad1;
    s32 pad2;
    s32 pad3;

    D_ovl10_09_8004A2E0 = -1.0f;
    func_ovl10_09_80048330(0x40);
    func_ovl10_09_80048320(1);
    D_ovl10_09_8004A1E8 = func_ovl10_09_80048348(func_ovl10_09_800482E8());
    D_ovl10_09_8004A1E8->unk70 = 0.0f;
    func_ovl10_09_80048160(D_ovl10_09_8004A1E8->unk40->unk10, D_ovl10_09_8004A1E8->unk40->unk14,
                           D_ovl10_09_8004A1E8->unk40->unk18, out, 2);
    func_ovl10_09_80048140(out[0], out[1], out[2], 0);
    func_ovl10_09_800482F8(1);
    func_ovl10_09_80043150(D_ovl10_09_8004A174, D_ovl10_09_8004A2D0, D_ovl10_09_8004A2D4, -1.0f);
    func_ovl10_09_80048C78(0x78);
    D_ovl10_09_800499D4 = D_ovl10_09_8004A1F8;
    D_ovl10_09_800499D8 = D_ovl10_09_8004A1FC;
    func_ovl10_09_80048200(D_ovl10_09_8004A1F8, D_ovl10_09_8004A1FC, 0);
}

void func_ovl10_09_80043150(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_ovl10_09_8004A174 = arg0;
    D_ovl10_09_8004A178 = arg1;
    D_ovl10_09_8004A17C = arg2;
    D_ovl10_09_8004A180 = arg3;
    func_ovl10_09_800430D8(func_ovl10_09_800474A8);
    D_ovl10_09_8004A1E8 = func_ovl10_09_80048348(func_ovl10_09_800482E8());
    D_ovl10_09_8004A1E8->unk70 = 0.0f;
    func_ovl10_09_800481C0(1);
    if (arg1 == 0.0f && arg2 < 0.0f && arg3 == -1.0f) {
        func_ovl10_09_80048360(1);
    }
    func_ovl10_09_800491E0(0x98);
    func_ovl10_09_80048270(0);
}

/* empty: the two words after 80043068 */
void func_ovl10_09_800430D0(void) {
}

void func_ovl10_09_80043068(void) {
    func_ovl10_09_80048F58(0, 0, 0, 0.0f);
    func_ovl10_09_80043018();
}

void func_ovl10_09_80043018(void) {
    if (D_ovl10_09_80049C9C != -1) {
        if (func_ovl10_09_800483D0(0) != 0) {
            func_ovl10_09_80049210(D_ovl10_09_80049C9C);
        }
        D_ovl10_09_80049C9C = -1;
    }
}

void func_ovl10_09_80043010(void) {
}

/* .data */
u32 D_ovl10_09_80049420[][3] = { { 0xA60002, 0xE, 0x4 }, { 0xA50003, 0xF, 0x4 }, { 0xA70001, 0xE, 0x4 } };
s32 D_ovl10_09_80049444[] = { 0x20, 0x0, 0xE, 0x4A, 0x4, 0x22, 0x0, 0xE, 0x4A, 0x4, 0x24, 0x0, 0xE, 0x4A, 0x4, 0x26, 0x0, 0xE, 0x4A, 0x4, 0x28, 0x0, 0xE, 0x4A, 0x4, -1 };
s32 D_ovl10_09_800494AC[] = { 0x5, 0x4, 0x11, 0xA, 0x3, 0x0, 0x7, 0x4, 0x1A, 0x9, 0x3, 0x0, 0x11, 0x0, 0x7, 0xA, 0x1, 0x0, 0x11, 0x0, 0x13, 0xA, 0x3, 0x0, 0x17, 0x0, 0x3, 0x9, 0x4, 0x0, 0x15, 0x0, 0xF, 0x9, 0x2, 0x0, -1 };
s32 D_ovl10_09_80049540[] = { 0x1, 0x0, 0xF, -255, 0x1, 0x1, 0x0, 0x6F, 0x12, 0x0, 0x0, 0x1, 0x4, 0xF, 0xFF, 0x1, 0x1, 0x0, 0x71, 0x11, 0x0, 0x0, 0x2C, 0x0, 0x3, 0x4, 0x2, 0x1, 0x0, 0xC0, 0x2, 0xC0, 0x2, -1 };
s32 D_ovl10_09_800495C8[] = { 0x4, 0x0, 0xA, 0x1, 0x7, 0x0, 0xA, 0x2, 0xA, 0x0, 0xA, 0x3, 0x2C, 0x0, 0xF, 0x4, -1 };
s32 D_ovl10_09_8004960C[] = { 0x20, 0x0, 0x18, 0x0, -1 };
s32 D_ovl10_09_80049620[] = { 0x13, 0x0, 0x1B, 0x3E8, 0x2, 0x0, 0x3C0, 0x15, 0x0, 0x1B, 0x3E8, 0x2, 0x50, 0x370, 0x17, 0x0, 0x1B, 0x3E8, 0x2, 0xA0, 0x320, 0x17, 0x0, 0x19, 0x3E8, 0x2, 0xF0, 0x2D0, 0x19, 0x0, 0x19, 0x3E8, 0x2, 0x140, 0x280, 0x1B, 0x0, 0x19, 0x3E8, 0x2, 0x190, 0x230, 0x1D, 0x0, 0x19, 0x3E8, 0x1, 0x1E0, 0x2A, 0x0, 0x16, 0x7A8, 0x1, 0x3C0, 0x2A, 0x0, 0x18, 0x7A8, 0x1, 0x410, 0x2A, 0x0, 0x1A, 0x7A8, 0x1, 0x460, 0x2A, 0x0, 0x1C, 0x7A8, 0x1, 0x4B0, 0x28, 0x0, 0x16, 0x7A8, 0x1, 0x370, 0x28, 0x0, 0x18, 0x7A8, 0x1, 0x320, 0x28, 0x0, 0x1A, 0x7A8, 0x1, 0x2D0, 0x28, 0x0, 0x1C, 0x7A8, 0x2, 0x500, 0x640, 0x26, 0x0, 0x16, 0x7A8, 0x1, 0x140, 0x26, 0x0, 0x18, 0x7A8, 0x1, 0x190, 0x26, 0x0, 0x1A, 0x7A8, 0x1, 0x280, 0x26, 0x0, 0x1C, 0x7A8, 0x3, 0x550, 0x5F0, 0x690, 0x24, 0x0, 0x16, 0x7A8, 0x1, 0xF0, 0x24, 0x0, 0x18, 0x7A8, 0x1, 0x1E0, 0x24, 0x0, 0x1A, 0x7A8, 0x1, 0x230, 0x24, 0x0, 0x1C, 0x7A8, 0x2, 0x5A0, 0x6E0, 0x22, 0x0, 0x16, 0x7A8, 0x1, 0xA0, 0x22, 0x0, 0x18, 0x7A8, 0x1, 0x50, 0x22, 0x0, 0x1A, 0x7A8, 0x2, 0x0, 0x780, 0x22, 0x0, 0x1C, 0x7A8, 0x1, 0x730, -1, 0x0, 0x0 };
