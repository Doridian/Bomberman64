/*
 * NON_MATCHING: ovl_10_08's game object, complete: every function, its
 * .bss and its .data tables. Not built into the ROM
 * (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 126, jp 126
 *
 * What still differs in us (words):
 * - func_ovl10_08_800432B0 (6), 80044F98 (12), 800455FC (62), 8004675C
 *   (9), 80046A70 (9) and 80047264 (2): ovl_10_12's 800432B0, 80044C68,
 *   80044FEC, 80046048, 8004635C and 80046908, with the same differences (its header).
 * - .data order (not counted above): ovl_10_09 found that the original puts
 *   the functions' local array initialisers before the tables; this draft's
 *   order is unchecked against the ROM.
 * - func_ovl10_08_80047964 (11): the same code; the padding IDO puts after its
 *   endless loop (to a 16-byte boundary) is a word longer
 *   because 800455FC is a word short (as in ovl_10_11's 80044C24).
 * - func_ovl10_08_80044238 (1): pos sits a word higher than the
 *   original's (a pad word above it; `s32 pad[2]` puts pos right but the
 *   three spill slots a word low).
 * - func_ovl10_08_80045268 (14): s3 and s4 swap (arg0 and &8004A004[i],
 *   later v).
 *
 * ovl_10_08's game object, IDO -O3: the functions are written last to first
 * (IDO -O3 emits a file's functions in reverse). Most of it is ovl_10_12's
 * draft, renamed (scratch/10_08/ in the checkout has the scripts); the
 * gate (80044238, 80045268, 8004701C), the main switch 80045988 and its
 * cases, the set-up 80045768 and the camera task 80045BA4 are its own
 * (ovl_10_07 and ovl_10_09 have the gate too).
 */
#include "common.h"
/* What func_ovl10_08_80048AC0 returns. */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} UnkStruct_ovl10_08_80048AC0;

void func_ovl10_08_80047BA8(const char *, ...);
void func_ovl10_08_80047EE8(s32);
void func_ovl10_08_80047EF0(s32, f32, f32, f32, s32, s32);
void func_ovl10_08_80047F00(s32);
void func_ovl10_08_80047F20(s32, s32, s32, s32);
void func_ovl10_08_80047F40(f32, f32, f32, s32 *, s32);
void func_ovl10_08_80047F48(f32, f32, f32, Vec3f *, s32);
f32 func_ovl10_08_80047F88(s32);
void func_ovl10_08_80047F90(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_08_80047F98(s32, s32, s32, s32, s32, s32);
void func_ovl10_08_80047FA0(s32);
void func_ovl10_08_80047FD0(void (*)(UnkStructA *));
void func_ovl10_08_80047FE0(s32, s32, s32);
s32 *func_ovl10_08_80048038(void);
void func_ovl10_08_80048050(s32);
void func_ovl10_08_80048098(void);
void func_ovl10_08_800480A0(s32, s32, s32);
s32 func_ovl10_08_800480B8(s32, s32, s32, s32, s32);
s32 func_ovl10_08_800480C8(void);
void func_ovl10_08_800480D8(s32);
void func_ovl10_08_800480E8(s32, s32, f32, s32, s32, s32, s32);
void func_ovl10_08_800480F8(void);
void func_ovl10_08_80048100(s32);
void func_ovl10_08_80048110(s32);
UnkStructA *func_ovl10_08_80048128(s32);
void func_ovl10_08_80048140(s32);
void func_ovl10_08_80048728(f32, f32, f32);
void func_ovl10_08_80048748(f32, f32, f32);
void func_ovl10_08_80048750(f32 *, f32 *, f32 *);
void func_ovl10_08_80048790(s32);
void func_ovl10_08_800487B0(f32);
void func_ovl10_08_800487B8(f32);
void func_ovl10_08_800487D0(f32);
void func_ovl10_08_800488F0(UnkStructA *, s32);
void func_ovl10_08_80048900(UnkStructA *);
UnkStructA *func_ovl10_08_80048910(s32, s32, s32, s32);
void func_ovl10_08_80048968(UnkStructA *);
void func_ovl10_08_800489B8(UnkStructA *, Vec3f *);
void func_ovl10_08_80048A38(void (*)(void), s32, s32, s32, s32);
void func_ovl10_08_80048A58(s32);
void func_ovl10_08_80048A80(void);
void func_ovl10_08_80048AB0(s32, s32);
UnkStruct_ovl10_08_80048AC0 *func_ovl10_08_80048AC0(void);
void func_ovl10_08_80048AD0(UnkStruct_ovl10_08_80048AC0 *, s32);
s32 *func_ovl10_08_80048CD0(void);
void func_ovl10_08_80048D38(s32, s32, s32, f32);
void func_ovl10_08_80048D78(s32, s32, s32, s32, s32);
void func_ovl10_08_80048D88(s32, s32, s32);
void func_ovl10_08_80048DA0(u32 (*)[3]);
void func_ovl10_08_80048E90(s32, Vec3f *, s32);
void func_ovl10_08_80048F48(s32, s32, s32);
void func_ovl10_08_80048FC0(s32);
void func_ovl10_08_80048FE0(s32, f32, f32, f32);
void func_ovl10_08_800480E0(s32);
void func_ovl10_08_800480F0(const char *);
void func_ovl10_08_80048188(s32);
s32 func_ovl10_08_800481B0(s32);
void func_ovl10_08_800485F0(UnkStructA_40 *, s32);
void func_ovl10_08_800485F8(UnkStructA_40 *, s32, s32, s32);
s32 func_ovl10_08_80048630(UnkStructA_40 *, s32, s32, s32, s32, s32);
void func_ovl10_08_80048760(u32 *, s32, s32);
void func_ovl10_08_800487A0(s32);
f32 func_ovl10_08_80048890(Vec3f *, Vec3f *);
void func_ovl10_08_800488E8(UnkStructA *, s32);
void func_ovl10_08_80048A48(void);
s32 func_ovl10_08_80048BF8(s32);
void func_ovl10_08_80048F68(s32);
s32 func_ovl10_08_80048FE8(s32, Vec3f *);
void func_ovl10_08_80048FF0(s32);
void func_ovl10_08_80049138(void);
void func_ovl10_08_80049140(void);

void func_ovl10_08_80047F60(s32);
void func_ovl10_08_80047F68(void);
s32 func_ovl10_08_80047FB8(s32);
void func_ovl10_08_80047FC0(s32, s32, s32, s32, s32, s32, s32, s32);
void func_ovl10_08_80048EB8(s16, s32);
void func_ovl10_08_80048EC0(s16, s32);

void func_ovl10_08_80047B48(void);
void func_ovl10_08_80047B30(void);
void func_ovl10_08_80047AD4(f32 arg0, f32 arg1, f32 arg2);
void func_ovl10_08_80047A8C(f32 arg0);
void func_ovl10_08_80047A58(s32 arg0, UnkStructA *arg1);
void func_ovl10_08_80047964(void);
s32 func_ovl10_08_80043150(void (*arg0)(void));
s32 func_ovl10_08_8004792C(void (*arg0)(void), const char *arg1);
void func_ovl10_08_80047900(void (*arg0)(void));
s32 func_ovl10_08_800478BC(void (*arg0)(void));
void func_ovl10_08_800478A8(s32 arg0);
void func_ovl10_08_8004788C(s32 arg0);
void func_ovl10_08_80047870(void (*arg0)(void));
void func_ovl10_08_800477E0(void);
void func_ovl10_08_800477A4(void);
void func_ovl10_08_80047738(UnkStructA *arg0);
void func_ovl10_08_800476B8(UnkStructA *arg0);
void func_ovl10_08_80047264(void);
void func_ovl10_08_8004701C(void);
void func_ovl10_08_80046F3C(void);
void func_ovl10_08_80046D1C(void);
void func_ovl10_08_80046CA4(s32 arg0);
void func_ovl10_08_80046C64(void);
void func_ovl10_08_80046A70(void);
void func_ovl10_08_8004675C(s32 arg0, s32 arg1);
void func_ovl10_08_800466F8(s32 arg0, s32 arg1);
void func_ovl10_08_8004662C(void);
void func_ovl10_08_80046614(void);
void func_ovl10_08_800464A8(s32 *arg0);
void func_ovl10_08_8004618C(void);
void func_ovl10_08_800460EC(s32 arg0);
void func_ovl10_08_80046038(void);
void func_ovl10_08_80045ED4(s32 arg0, s32 arg1);
f32 func_ovl10_08_80045E7C(s32 arg0);
void func_ovl10_08_80045CC4(void);
void func_ovl10_08_80045C8C(s32 arg0);
void func_ovl10_08_80045C70(void);
void func_ovl10_08_80045BA4(void);
void func_ovl10_08_80045B30(void);
void func_ovl10_08_80045988(s32 arg0);
void func_ovl10_08_80045768(void);
void func_ovl10_08_800455FC(s32 *arg0);
void func_ovl10_08_80045548(s32 *arg0);
void func_ovl10_08_80045268(s32 *arg0);
void func_ovl10_08_80044F98(s32 *arg0);
void func_ovl10_08_80044E4C(s32 *arg0);
void func_ovl10_08_80044D88(s32 arg0);
void func_ovl10_08_80044D0C(void);
void func_ovl10_08_80044D04(void);
void func_ovl10_08_80044CFC(void);
void func_ovl10_08_80044C58(void);
void func_ovl10_08_80044BB0(void);
void func_ovl10_08_80044AFC(void);
void func_ovl10_08_80044998(void);
void func_ovl10_08_80044938(void);
void func_ovl10_08_80044910(void);
void func_ovl10_08_80044880(void);
void func_ovl10_08_800447D4(void);
void func_ovl10_08_80044768(void);
void func_ovl10_08_800445A0(void);
void func_ovl10_08_80044448(s32 arg0, s32 arg1);
void func_ovl10_08_80044238(s32 arg0, s32 arg1);
void func_ovl10_08_80044188(void);
void func_ovl10_08_80043F34(s32 arg0, s32 arg1);
void func_ovl10_08_80043F04(s32 arg0);
void func_ovl10_08_80043EBC(s32 arg0);
void func_ovl10_08_80043E8C(s32 arg0);
void func_ovl10_08_80043DF4(s32 arg0);
void func_ovl10_08_80043DDC(s32 arg0);
void func_ovl10_08_80043D38(void);
void func_ovl10_08_80043C3C(s32 arg0, s32 arg1);
void func_ovl10_08_80043A60(s32 arg0);
void func_ovl10_08_8004393C(void);
void func_ovl10_08_80043904(s32 arg0);
void func_ovl10_08_800437E8(s32 arg0);
void func_ovl10_08_800437C8(void);
void func_ovl10_08_800437A8(void);
s32 func_ovl10_08_800434D8(s32 arg0);
void func_ovl10_08_8004339C(void);
void func_ovl10_08_800432B0(void);
void func_ovl10_08_800431C8(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_ovl10_08_80043148(void);
void func_ovl10_08_800430B0(void);
void func_ovl10_08_80043060(void);
void func_ovl10_08_80043018(void);
void func_ovl10_08_80043010(void);

/* .bss */
u8 D_ovl10_08_800496C0[0x24]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_800496E4;
s32 D_ovl10_08_800496E8;
u8 D_ovl10_08_800496EC[0x4]; /* unused (func_ovl10_08_80047B48) */
Vec3f D_ovl10_08_800496F0;
u8 D_ovl10_08_800496FC[0x4]; /* unused (func_ovl10_08_80047B48) */
UnkStructA *D_ovl10_08_80049700[12];
s32 D_ovl10_08_80049730[11][3];
u8 D_ovl10_08_800497B4[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_800497B8[12];
s32 D_ovl10_08_800497E8[12];
s32 D_ovl10_08_80049818[64];
s32 D_ovl10_08_80049918;
u8 D_ovl10_08_8004991C[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_80049920[12];
s32 D_ovl10_08_80049950[12];
s32 D_ovl10_08_80049980[11];
s32 D_ovl10_08_800499AC;
s32 D_ovl10_08_800499B0[11];
s32 D_ovl10_08_800499DC;
s32 D_ovl10_08_800499E0;
s32 D_ovl10_08_800499E4;
s32 D_ovl10_08_800499E8[64];
s32 D_ovl10_08_80049AE8;
u8 D_ovl10_08_80049AEC[0x4]; /* unused (func_ovl10_08_80047B48) */
void (*D_ovl10_08_80049AF0[64])(void);
UnkStruct_ovl10_08_80048AC0 *D_ovl10_08_80049BF0;
u8 D_ovl10_08_80049BF4[0x4]; /* unused (func_ovl10_08_80047B48) */
UnkStructA *D_ovl10_08_80049BF8[6];
s32 D_ovl10_08_80049C10[6][3];
s32 D_ovl10_08_80049C58[6];
s32 D_ovl10_08_80049C70[6];
s32 D_ovl10_08_80049C88[64];
s32 D_ovl10_08_80049D88;
u8 D_ovl10_08_80049D8C[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_80049D90[6];
s32 D_ovl10_08_80049DA8[6];
f32 D_ovl10_08_80049DC0[6];
f32 D_ovl10_08_80049DD8[6];
s32 *D_ovl10_08_80049DF0;
u8 D_ovl10_08_80049DF4[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_80049DF8[4][3];
UnkStructA *D_ovl10_08_80049E28[4];
s32 D_ovl10_08_80049E38;
u8 D_ovl10_08_80049E3C[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_80049E40[4];
s32 D_ovl10_08_80049E50[4];
s32 D_ovl10_08_80049E60;
u8 D_ovl10_08_80049E64[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_80049E68[5];
s32 D_ovl10_08_80049E6C;
s32 D_ovl10_08_80049E7C;
f32 D_ovl10_08_80049E80;
f32 D_ovl10_08_80049E84;
f32 D_ovl10_08_80049E88;
u8 D_ovl10_08_80049E8C[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_80049E90[6][3];
UnkStructA *D_ovl10_08_80049ED8[6];
UnkStructA *D_ovl10_08_80049EF0;
s32 D_ovl10_08_80049EF4;
s32 D_ovl10_08_80049EF8;
s32 D_ovl10_08_80049EFC;
s32 D_ovl10_08_80049F00;
s32 D_ovl10_08_80049F04;
s32 D_ovl10_08_80049F08[6];
s32 D_ovl10_08_80049F20[6];
s32 D_ovl10_08_80049F38[6];
s32 D_ovl10_08_80049F50;
u8 D_ovl10_08_80049F54[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_80049F58[6];
s32 D_ovl10_08_80049F70[6];
s32 D_ovl10_08_80049F88[6];
s32 D_ovl10_08_80049FA0[6];
s32 D_ovl10_08_80049FB8[6];
f32 D_ovl10_08_80049FD0;
f32 D_ovl10_08_80049FD4;
f32 D_ovl10_08_80049FD8;
f32 D_ovl10_08_80049FDC;
f32 D_ovl10_08_80049FE0;
f32 D_ovl10_08_80049FE4;
f32 D_ovl10_08_80049FE8;
u8 D_ovl10_08_80049FEC[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_80049FF0[1][3]; /* the gate: its tile */
UnkStructA *D_ovl10_08_80049FFC[1]; /* its two halves */
UnkStructA *D_ovl10_08_8004A000[1];
s32 D_ovl10_08_8004A004[1]; /* open */
s32 D_ovl10_08_8004A008[64]; /* per task: its gate */
s32 D_ovl10_08_8004A108;
s32 D_ovl10_08_8004A10C[1]; /* moving */
f32 D_ovl10_08_8004A110[1];
f32 D_ovl10_08_8004A114[1];
f32 D_ovl10_08_8004A118[1];
u8 D_ovl10_08_8004A11C[0x4]; /* unused (func_ovl10_08_80047B48) */
UnkStructA *D_ovl10_08_8004A120[28];
UnkStructA *D_ovl10_08_8004A190[28];
s32 D_ovl10_08_8004A200[27][3];
u8 D_ovl10_08_8004A344[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_8004A348[28];
s32 D_ovl10_08_8004A3B8[28];
s32 D_ovl10_08_8004A428[64];
s32 D_ovl10_08_8004A528;
u8 D_ovl10_08_8004A52C[0x4]; /* unused (func_ovl10_08_80047B48) */
s32 D_ovl10_08_8004A530[28];
s32 D_ovl10_08_8004A5A0[28];
s32 D_ovl10_08_8004A610[27][4];
f32 D_ovl10_08_8004A7C0[28];
f32 D_ovl10_08_8004A830[28];
f32 D_ovl10_08_8004A8A0[27];
s32 D_ovl10_08_8004A90C;
s32 D_ovl10_08_8004A910;
s32 D_ovl10_08_8004A914;
s32 D_ovl10_08_8004A918[64];
s32 D_ovl10_08_8004AA18;
s32 D_ovl10_08_8004AA1C;

/* .data */
u32 D_ovl10_08_80049200[] = { 0x14, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40900000, 0x0, 0x0, 0xBE75C28F, 0x0, 0x0, 0x0, 0x0 };
u32 D_ovl10_08_80049244[] = { 0x14, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xC0900000, 0x0, 0x0, 0x3E75C28F, 0x0, 0x0, 0x0, 0x0 };
u32 D_ovl10_08_80049288[][3] = { { 0xA60002, 0xE, 0x4 }, { 0xA50003, 0xF, 0x4 }, { 0xA70001, 0xE, 0x4 } };
s32 D_ovl10_08_800492AC[] = { 0x13, 0x1, 0xE, 0x4A, 0x1, 0x15, 0x1, 0xE, 0x4A, 0x1, 0x17, 0x1, 0xE, 0x4A, 0x1,
                              0x19, 0x1, 0x8, 0x49, 0x1, 0x19, 0x1, 0xB, 0x49, 0x1, 0x19, 0x1, 0x13, 0x49, 0x1,
                              0x19, 0x1, 0x15, 0x49, 0x1, 0x19, 0x1, 0x17, 0x49, 0x1, 0x27, 0x1, 0x14, 0x49, 0x1,
                              0x27, 0x1, 0x17, 0x49, 0x1, -1 };
s32 D_ovl10_08_80049378[] = { 0x19, 0x1, 0x3, 0x5, 0x1, 0x0, 0x1F, 0x1, 0x19, 0x5, 0x1, 0x0, 0x27, 0x1, 0x7, 0x6, 0x1, 0x0, -1 };
s32 D_ovl10_08_800493C4[] = { 0x1, 0x1, 0xF, -0xFF, 0x1, 0x1, 0x0, 0x6E, 0x11, 0x0, 0x0, 0x1, 0x4, 0xF, 0xFF, 0x1, 0x1, 0x0, 0x70,
                              0x11, 0x0, 0x0, 0x2D, 0x4, 0xF, 0xFF, 0x1, 0x1, 0x0, 0x72, 0x12, 0x0, 0x0, 0x10, 0x1, 0x8, 0x4, 0x2,
                              0x0, 0x1, 0xC0, 0x2, 0xC0, 0x2, 0x22, 0x2, 0x9, 0x4, 0x2, 0x0, 0x1, 0x40, 0x2, 0xC0, 0x2, -1 };
s32 D_ovl10_08_800494A4[] = { 0x2D, 0x1, 0xF, 0x1, -1 };
/* the gate */
s32 D_ovl10_08_800494B8[] = { 0x21, 0x0, 0xE, 0x1, -1 };

/* unused: the stubs IDO -O3 leaves at the end of the object */
static void func_ovl10_08_80047B98(void) {
}

static void func_ovl10_08_80047B90(void) {
}

static void func_ovl10_08_80047B88(void) {
}

static void func_ovl10_08_80047B80(void) {
}

static void func_ovl10_08_80047B78(void) {
}

static void func_ovl10_08_80047B70(void) {
}

static void func_ovl10_08_80047B68(void) {
}

static void func_ovl10_08_80047B60(void) {
}

static void func_ovl10_08_80047B58(void) {
}

static void func_ovl10_08_80047B50(void) {
}

void func_ovl10_08_80047B48(void) {
    /* a fake: the reference keeps the unused words in .bss, which would
     * otherwise be common; it builds to nothing */
    if (0) {
        D_ovl10_08_800496C0[0] = D_ovl10_08_800496EC[0] + D_ovl10_08_800496FC[0] + D_ovl10_08_800497B4[0] + D_ovl10_08_8004991C[0] + D_ovl10_08_80049AEC[0] + D_ovl10_08_80049BF4[0] + D_ovl10_08_80049D8C[0] + D_ovl10_08_80049DF4[0] + D_ovl10_08_80049E3C[0] + D_ovl10_08_80049E64[0] + D_ovl10_08_80049E8C[0] + D_ovl10_08_80049F54[0] + D_ovl10_08_80049FEC[0] + D_ovl10_08_8004A11C[0] + D_ovl10_08_8004A344[0] + D_ovl10_08_8004A52C[0];
    }
}

void func_ovl10_08_80047B30(void) {
    D_ovl10_08_800496E4 = -1;
    D_ovl10_08_800496E8 = -1;
}

void func_ovl10_08_80047AD4(f32 arg0, f32 arg1, f32 arg2) {
    func_ovl10_08_80048728(D_ovl10_08_800496F0.x, D_ovl10_08_800496F0.y, D_ovl10_08_800496F0.z);
    func_ovl10_08_80048748(arg0, arg1, arg2);
    func_ovl10_08_80048A58(180);
}

void func_ovl10_08_80047A8C(f32 arg0) {
    f32 sp1C;

    func_ovl10_08_80048750(&sp1C, NULL, NULL);
    func_ovl10_08_80048748(sp1C + arg0, 32768.0f, 32768.0f);
}

void func_ovl10_08_80047A58(s32 arg0, UnkStructA *arg1) {
    func_ovl10_08_80048FE0(arg0, arg1->unk40->unk10, arg1->unk40->unk14, arg1->unk40->unk18);
}

/* runs the tasks, one frame each time round */
void func_ovl10_08_80047964(void) {
    s32 i;

    D_ovl10_08_800499E0 = 0;
    D_ovl10_08_800499E4 = 0;
    while (TRUE) {
        for (i = 0; i < 64; i++) {
            if (D_ovl10_08_80049AF0[i] != NULL) {
                D_ovl10_08_80049AE8 = i;
                if (D_ovl10_08_800499E8[i] == 0) {
                    D_ovl10_08_80049AF0[i]();
                } else {
                    D_ovl10_08_800499E8[i]--;
                }
            }
        }
        D_ovl10_08_800499E0++;
        D_ovl10_08_800499E0 &= 3;
        func_ovl10_08_80048A80();
    }
}

/* Defined above its caller 80046FD0, which pulls it out among the earlier
 * functions all the same: only so does its string come first in .rodata. */
s32 func_ovl10_08_80043150(void (*arg0)(void)) {
    s32 found;
    s32 i;

    i = 0;
    found = -1;
    do {
        if (D_ovl10_08_80049AF0[i] == NULL) {
            D_ovl10_08_80049AF0[i] = arg0;
            found = i;
        }
        i++;
    } while (i < 64 && found == -1);
    if (found == -1) {
        func_ovl10_08_80047BA8("trap task:entry failed\n");
    }
    return found;
}

s32 func_ovl10_08_8004792C(void (*arg0)(void), const char *arg1) {
    s32 i;

    i = func_ovl10_08_80043150(arg0);
    func_ovl10_08_80047BA8("task_entry>%d:%s\n", i, arg1);
    return i;
}

void func_ovl10_08_80047900(void (*arg0)(void)) {
    D_ovl10_08_80049AF0[func_ovl10_08_800478BC(arg0)] = NULL;
}

s32 func_ovl10_08_800478BC(void (*arg0)(void)) {
    s32 i;
    s32 found;

    found = -1;
    i = 0;
    do {
        if (arg0 == D_ovl10_08_80049AF0[i]) {
            found = i;
        }
        i++;
    } while (found == -1 && i < 64);
    return found;
}

void func_ovl10_08_800478A8(s32 arg0) {
    D_ovl10_08_80049AF0[arg0] = NULL;
}

void func_ovl10_08_8004788C(s32 arg0) {
    D_ovl10_08_800499E8[D_ovl10_08_80049AE8] = arg0;
}

void func_ovl10_08_80047870(void (*arg0)(void)) {
    D_ovl10_08_80049AF0[D_ovl10_08_80049AE8] = arg0;
}

void func_ovl10_08_800477E0(void) {
    D_ovl10_08_80049BF0 = func_ovl10_08_80048AC0();
    func_ovl10_08_80048AD0(D_ovl10_08_80049BF0, 0x20000001);
    D_ovl10_08_80049BF0->unk40 = 0.5f;
    D_ovl10_08_80049BF0->unk44 = D_ovl10_08_80049BF0->unk40 * 0.75f;
    D_ovl10_08_80049BF0->unk18 = 0.1f;
    D_ovl10_08_80049BF0->unk1C = -0.1f;
}

void func_ovl10_08_800477A4(void) {
    s32 *p;

    p = func_ovl10_08_80048CD0();
    if (*p <= 0 || *p == 0) {
        *p = 1;
    }
}

void func_ovl10_08_80047738(UnkStructA *arg0) {
    s32 i;

    if (arg0->unk8 & 1) {
        func_ovl10_08_80048790(16);
    }
    for (i = 0; i < 30; i++) {
        func_ovl10_08_80048968(arg0);
        func_ovl10_08_80048A80();
    }
}

void func_ovl10_08_800476B8(UnkStructA *arg0) {
    Vec3f pos;

    if (arg0->unk8 & 1) {
        func_ovl10_08_80048D38(0xFF, 0xFF, 0xFF, 100.0f);
        func_ovl10_08_800488F0(arg0, 0x01000000);
        func_ovl10_08_80048A58(5);
        func_ovl10_08_80048D38(0, 0, 0, 0.0f);
        func_ovl10_08_800489B8(arg0, &pos);
        func_ovl10_08_80048E90(12, &pos, 0);
    }
}

void func_ovl10_08_80047264(void) {
    s32 y;
    s32 i;
    s32 a;
    s32 b;
    s32 out[6];
    s32 *flags;

    i = D_ovl10_08_80049E7C;
    D_ovl10_08_80049EF0 = func_ovl10_08_80048128(func_ovl10_08_800480C8());
    D_ovl10_08_80049ED8[i]->unk40->unk14 += D_ovl10_08_80049E80;
    D_ovl10_08_80049EF0->unk40->unk14 = D_ovl10_08_80049ED8[i]->unk40->unk14;
    D_ovl10_08_80049E80 += D_ovl10_08_80049E84;
    if (D_ovl10_08_80049FE8 != -1.0f &&
        ((D_ovl10_08_80049E80 > 0.0f && D_ovl10_08_80049FE8 <= D_ovl10_08_80049ED8[i]->unk40->unk14) ||
         (D_ovl10_08_80049E80 < 0.0f && D_ovl10_08_80049ED8[i]->unk40->unk14 <= D_ovl10_08_80049FE8))) {
        D_ovl10_08_80049E84 = -D_ovl10_08_80049E84;
        D_ovl10_08_80049FE8 = -1.0f;
    }
    if (D_ovl10_08_80049E88 != -1.0f &&
        (D_ovl10_08_80049E80 == 0.0f ||
         (D_ovl10_08_80049E80 > 0.0f && D_ovl10_08_80049E88 < D_ovl10_08_80049ED8[i]->unk40->unk14) ||
         (D_ovl10_08_80049E80 < 0.0f && D_ovl10_08_80049ED8[i]->unk40->unk14 < D_ovl10_08_80049E88))) {
        flags = func_ovl10_08_80048038();
        if (!(*flags & 2)) {
            func_ovl10_08_80048050(1);
        }
        func_ovl10_08_80045C70();
        D_ovl10_08_80049EF0->unk70 = 1.6333334f;
        if (D_ovl10_08_80049E80 != 0.0f) {
            D_ovl10_08_80049ED8[i]->unk40->unk14 = D_ovl10_08_80049E88;
            D_ovl10_08_80049EF0->unk40->unk14 = D_ovl10_08_80049E88;
        }
        if (D_ovl10_08_80049F08[i] == 2) {
            func_ovl10_08_80047F40(D_ovl10_08_80049ED8[i]->unk40->unk10, D_ovl10_08_80049ED8[i]->unk40->unk14,
                                   D_ovl10_08_80049ED8[i]->unk40->unk18, out, 2);
            y = out[1];
            func_ovl10_08_80047F90(D_ovl10_08_80049E90[i][0], D_ovl10_08_80049E90[i][1], D_ovl10_08_80049E90[i][2],
                                   D_ovl10_08_80049E90[i][0] + 1, D_ovl10_08_80049E90[i][2] + 1,
                                   D_ovl10_08_80049E90[i][0], y, D_ovl10_08_80049E90[i][2]);
            func_ovl10_08_80047F98(D_ovl10_08_80049E90[i][0], D_ovl10_08_80049E90[i][1], D_ovl10_08_80049E90[i][2],
                                   D_ovl10_08_80049E90[i][0] + 1, D_ovl10_08_80049E90[i][2] + 1, 0);
            D_ovl10_08_80049F58[i] = D_ovl10_08_80049E90[i][1];
            D_ovl10_08_80049E90[i][1] = y;
            if (D_ovl10_08_80049E80 > 0.0f) {
                a = D_ovl10_08_80049F70[i];
                b = D_ovl10_08_80049F88[i];
            } else {
                a = D_ovl10_08_80049FA0[i];
                b = D_ovl10_08_80049FB8[i];
            }
            func_ovl10_08_800480E8(a, 3, 8.5f, b, 1, 1, 1);
            func_ovl10_08_800487B8(0.1f);
            func_ovl10_08_800487D0(40.0f);
        }
        func_ovl10_08_80047FA0(0);
        if (!(*flags & 2)) {
            func_ovl10_08_800480D8(0);
        }
        func_ovl10_08_80048AB0(0xD0, 0xD0);
    }
}

/* the gate opens or closes */
void func_ovl10_08_8004701C(void) {
    s32 i;
    s32 v;
    s32 w;

    i = D_ovl10_08_8004A008[D_ovl10_08_80049AE8];
    D_ovl10_08_80049FFC[i]->unk40->unk18 += D_ovl10_08_8004A110[i];
    D_ovl10_08_8004A000[i]->unk40->unk18 -= D_ovl10_08_8004A110[i];
    if ((D_ovl10_08_8004A110[i] < 0.0f && D_ovl10_08_80049FFC[i]->unk40->unk18 <= D_ovl10_08_8004A114[i]) ||
        (D_ovl10_08_8004A110[i] > 0.0f && D_ovl10_08_8004A114[i] <= D_ovl10_08_80049FFC[i]->unk40->unk18)) {
        D_ovl10_08_8004A004[i] = (D_ovl10_08_8004A004[i] + 1) % 2;
        if (D_ovl10_08_8004A004[i] != 0) {
            v = 1;
            w = 0;
        } else {
            v = 15;
            w = 1;
        }
        func_ovl10_08_80047F20(D_ovl10_08_80049FF0[i][0], D_ovl10_08_80049FF0[i][1], D_ovl10_08_80049FF0[i][2] + 1, v);
        func_ovl10_08_80047F20(D_ovl10_08_80049FF0[i][0], D_ovl10_08_80049FF0[i][1], D_ovl10_08_80049FF0[i][2] + 2, v);
        func_ovl10_08_80047F20(D_ovl10_08_80049FF0[i][0], D_ovl10_08_80049FF0[i][1] + 1, D_ovl10_08_80049FF0[i][2] + 1, w);
        func_ovl10_08_80047F20(D_ovl10_08_80049FF0[i][0], D_ovl10_08_80049FF0[i][1] + 1, D_ovl10_08_80049FF0[i][2] + 2, w);
        D_ovl10_08_80049FFC[i]->unk40->unk18 = D_ovl10_08_8004A114[i];
        D_ovl10_08_8004A000[i]->unk40->unk18 = D_ovl10_08_8004A118[i];
        func_ovl10_08_80045C70();
        D_ovl10_08_8004A10C[i] = 0;
        func_ovl10_08_80048FC0(0xA8);
    }
}

void func_ovl10_08_80046F3C(void) {
    if (D_ovl10_08_8004A90C != 0) {
        func_ovl10_08_80048D38(0xFF, 0, 0, D_ovl10_08_8004AA18);
    }
    D_ovl10_08_8004AA18 += D_ovl10_08_8004AA1C;
    if (D_ovl10_08_8004AA1C == 2 && D_ovl10_08_8004AA18 >= 60) {
        D_ovl10_08_8004AA1C = -2;
        D_ovl10_08_8004AA18 = 60;
    }
    if (D_ovl10_08_8004AA1C == -2 && D_ovl10_08_8004AA18 <= 0) {
        D_ovl10_08_8004AA1C = 2;
        D_ovl10_08_8004AA18 = 0;
        func_ovl10_08_80048FC0(0x9E);
    }
    if (D_ovl10_08_8004A90C == 0) {
        func_ovl10_08_80045C70();
    }
}

void func_ovl10_08_80046D1C(void) {
    s32 i;

    i = D_ovl10_08_8004A918[D_ovl10_08_80049AE8];
    if (D_ovl10_08_8004A910 == 0) {
        D_ovl10_08_8004A830[i] += D_ovl10_08_8004A7C0[i];
        D_ovl10_08_8004A120[i]->unk40->unk36 = D_ovl10_08_8004A830[i];
        D_ovl10_08_8004A190[i]->unk40->unk36 = D_ovl10_08_8004A830[i] * 0.5f;
        D_ovl10_08_8004A190[i]->unk40->unk2C += D_ovl10_08_8004A8A0[i];
        if (D_ovl10_08_8004A7C0[i] > 0.0f && D_ovl10_08_8004A120[i]->unk40->unk36 >= 256) {
            D_ovl10_08_8004A120[i]->unk40->unk36 = 255;
            D_ovl10_08_8004A190[i]->unk40->unk36 = 128;
            func_ovl10_08_80045C70();
        }
        if (D_ovl10_08_8004A7C0[i] < 0.0f && D_ovl10_08_8004A120[i]->unk40->unk36 < 0) {
            if (D_ovl10_08_8004A120[i] != NULL) {
                func_ovl10_08_80048900(D_ovl10_08_8004A120[i]);
                func_ovl10_08_80048900(D_ovl10_08_8004A190[i]);
                D_ovl10_08_8004A120[i] = NULL;
                func_ovl10_08_800466F8(i, 0);
            }
            func_ovl10_08_80045C70();
        }
    } else {
        func_ovl10_08_80045C70();
    }
}

void func_ovl10_08_80046CA4(s32 arg0) {
    if (arg0 != D_ovl10_08_8004A90C) {
        D_ovl10_08_8004A90C = arg0;
        if (arg0 == 1) {
            func_ovl10_08_80046C64();
        } else {
            func_ovl10_08_80048D38(0, 0, 0, 0.0f);
        }
    }
}

void func_ovl10_08_80046C64(void) {
    D_ovl10_08_8004AA18 = 0;
    D_ovl10_08_8004AA1C = 2;
    func_ovl10_08_80043150(func_ovl10_08_80046F3C);
    func_ovl10_08_80048FC0(0x9E);
}

void func_ovl10_08_80046A70(void) {
    s32 i;
    s32 j;
    s32 found;
    s32 k;

    i = D_ovl10_08_8004A428[D_ovl10_08_80049AE8];
    found = -1;
    j = 0;
    do {
        if (D_ovl10_08_8004A530[i] == D_ovl10_08_8004A610[i][j]) {
            D_ovl10_08_8004A348[i] = 0;
            found = 0;
            D_ovl10_08_8004A3B8[i]++;
            func_ovl10_08_8004675C(i, 1);
        }
        j++;
    } while (D_ovl10_08_8004A610[i][j] != -1 && found == -1);
    if (D_ovl10_08_8004A3B8[i] != 0) {
        D_ovl10_08_8004A348[i]++;
        if (D_ovl10_08_8004A348[i] == 80) {
            D_ovl10_08_8004A3B8[i] = 0;
            func_ovl10_08_8004675C(i, 0);
        }
    }
    if (D_ovl10_08_8004A910 != 0) {
        for (k = 0; k < D_ovl10_08_8004A528; k++) {
            if (D_ovl10_08_8004A120[k] != NULL) {
                func_ovl10_08_80048900(D_ovl10_08_8004A120[k]);
                func_ovl10_08_80048900(D_ovl10_08_8004A190[k]);
                D_ovl10_08_8004A120[k] = NULL;
                func_ovl10_08_800466F8(k, 0);
                D_ovl10_08_8004A3B8[k] = 0;
            }
        }
        func_ovl10_08_80045C70();
    }
    D_ovl10_08_8004A530[i]++;
    if (D_ovl10_08_8004A530[i] == D_ovl10_08_8004A5A0[i]) {
        D_ovl10_08_8004A530[i] = 40;
    }
}

void func_ovl10_08_8004675C(s32 arg0, s32 arg1) {
    Vec3f pos;
    Vec3f pos2;

    D_ovl10_08_8004A918[func_ovl10_08_80043150(func_ovl10_08_80046D1C)] = arg0;
    if (arg1 != 0) {
        D_ovl10_08_8004A120[arg0] = func_ovl10_08_80048910(0xBE, 0x01080000, 0x10, 0);
        func_ovl10_08_80047F48(D_ovl10_08_8004A200[arg0][0], D_ovl10_08_8004A200[arg0][1],
                               D_ovl10_08_8004A200[arg0][2], &pos, 0);
        D_ovl10_08_8004A120[arg0]->unk40->unk10 = pos.x;
        D_ovl10_08_8004A120[arg0]->unk40->unk14 = pos.y + 10.0f;
        D_ovl10_08_8004A120[arg0]->unk40->unk18 = pos.z;
        D_ovl10_08_8004A120[arg0]->unk40->unk36 = 0;
        D_ovl10_08_8004A7C0[arg0] = 12.0f;
        D_ovl10_08_8004A830[arg0] = 0.0f;
        D_ovl10_08_8004A190[arg0] = func_ovl10_08_80048910(0x2A7, 0x01080000, 0x10, 0);
        func_ovl10_08_80047F48(D_ovl10_08_8004A200[arg0][0], D_ovl10_08_8004A200[arg0][1],
                               D_ovl10_08_8004A200[arg0][2], &pos, 0);
        D_ovl10_08_8004A190[arg0]->unk40->unk10 = pos.x + 40.0f;
        D_ovl10_08_8004A190[arg0]->unk40->unk14 = pos.y;
        D_ovl10_08_8004A190[arg0]->unk40->unk18 = pos.z + 40.0f;
        D_ovl10_08_8004A190[arg0]->unk40->unk28 = 2.0f;
        D_ovl10_08_8004A190[arg0]->unk40->unk2C = 2.0f;
        D_ovl10_08_8004A190[arg0]->unk40->unk30 = 2.0f;
        D_ovl10_08_8004A190[arg0]->unk40->unkC |= 0x8000;
        func_ovl10_08_800485F0(D_ovl10_08_8004A190[arg0]->unk40, 2);
        func_ovl10_08_800485F8(D_ovl10_08_8004A190[arg0]->unk40, 0x2A8, 0, 0);
        func_ovl10_08_800485F8(D_ovl10_08_8004A190[arg0]->unk40, 0x2A8, 1, 1);
        D_ovl10_08_8004A190[arg0]->unk40->unk36 = 0;
        D_ovl10_08_8004A8A0[arg0] = 0.1f;
        func_ovl10_08_800466F8(arg0, 1);
        func_ovl10_08_800489B8(D_ovl10_08_8004A190[arg0], &pos2);
        func_ovl10_08_80048FE8(0xAA, &pos2);
    } else {
        D_ovl10_08_8004A7C0[arg0] = -6.0f;
        D_ovl10_08_8004A830[arg0] = 255.0f;
        D_ovl10_08_8004A8A0[arg0] = -0.1f;
    }
}

void func_ovl10_08_800466F8(s32 arg0, s32 arg1) {
    s32 v;

    if (arg1 != 0) {
        v = 1;
    } else {
        v = 11;
    }
    func_ovl10_08_80047F98(D_ovl10_08_8004A200[arg0][0], D_ovl10_08_8004A200[arg0][1], D_ovl10_08_8004A200[arg0][2],
                           D_ovl10_08_8004A200[arg0][0] + 1, D_ovl10_08_8004A200[arg0][2] + 1, v);
}

void func_ovl10_08_8004662C(void) {
    s32 i;

    if (D_ovl10_08_8004A914 == 0) {
        for (i = 0; i < D_ovl10_08_8004A528; i++) {
            D_ovl10_08_8004A428[func_ovl10_08_80043150(func_ovl10_08_80046A70)] = i;
            D_ovl10_08_8004A530[i] = 0;
            D_ovl10_08_8004A348[i] = 0;
        }
        D_ovl10_08_8004A914 = 1;
        D_ovl10_08_8004A910 = 0;
    }
}

void func_ovl10_08_80046614(void) {
    D_ovl10_08_8004A910 = 1;
    D_ovl10_08_8004A914 = 0;
}

void func_ovl10_08_800464A8(s32 *arg0) {
    s32 i;
    s32 j;
    s32 n;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_08_8004A200[i][0] = arg0[0];
            D_ovl10_08_8004A200[i][1] = arg0[1];
            D_ovl10_08_8004A200[i][2] = arg0[2];
            D_ovl10_08_8004A5A0[i] = arg0[3];
            n = arg0[4];
            arg0 += 5;
            for (j = 0; j < n; j++) {
                D_ovl10_08_8004A610[i][j] = *arg0;
                arg0++;
            }
            D_ovl10_08_8004A610[i][n] = -1;
            D_ovl10_08_8004A3B8[i] = 0;
            D_ovl10_08_8004A120[i] = NULL;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_08_8004A528 = i;
    D_ovl10_08_8004A90C = 0;
    D_ovl10_08_8004A910 = 0;
    D_ovl10_08_8004A914 = 0;
    func_ovl10_08_80048D38(0, 0, 0, 0.0f);
}

void func_ovl10_08_8004618C(void) {
    s32 i;
    s32 j;
    s32 v;

    i = D_ovl10_08_80049818[D_ovl10_08_80049AE8];
    D_ovl10_08_80049920[i]--;
    func_ovl10_08_800460EC(i);
    if (D_ovl10_08_80049920[i] == 0) {
        D_ovl10_08_800497E8[i] = (D_ovl10_08_800497E8[i] + 2) & 3;
        if (D_ovl10_08_800497E8[i] & 2) {
            func_ovl10_08_80043F04(i);
            D_ovl10_08_80049920[i] = func_ovl10_08_80048BF8(60) + 90;
            v = 9;
        } else {
            func_ovl10_08_80043E8C(i);
            v = 1;
            D_ovl10_08_80049920[i] = 120;
        }
        if (D_ovl10_08_800497B8[i] & 1) {
            for (j = 0; j < D_ovl10_08_800499B0[i]; j++) {
                func_ovl10_08_80047F20(D_ovl10_08_80049730[i][0] + j, D_ovl10_08_80049730[i][1], D_ovl10_08_80049730[i][2], v);
            }
        } else {
            for (j = 0; j < D_ovl10_08_800499B0[i]; j++) {
                func_ovl10_08_80047F20(D_ovl10_08_80049730[i][0], D_ovl10_08_80049730[i][1], D_ovl10_08_80049730[i][2] + j, v);
            }
        }
        if (D_ovl10_08_8004A90C != 0) {
            D_ovl10_08_80049920[i] = 30;
        }
    }
    if (D_ovl10_08_80049950[i] != 0) {
        if (D_ovl10_08_800497E8[i] & 2) {
            func_ovl10_08_80043E8C(i);
            if (D_ovl10_08_800497B8[i] & 1) {
                for (j = 0; j < D_ovl10_08_800499B0[i]; j++) {
                    func_ovl10_08_80047F20(D_ovl10_08_80049730[i][0] + j, D_ovl10_08_80049730[i][1], D_ovl10_08_80049730[i][2], 1);
                }
            } else {
                for (j = 0; j < D_ovl10_08_800499B0[i]; j++) {
                    func_ovl10_08_80047F20(D_ovl10_08_80049730[i][0], D_ovl10_08_80049730[i][1], D_ovl10_08_80049730[i][2] + j, 1);
                }
            }
        }
        func_ovl10_08_80045C70();
    }
}

void func_ovl10_08_800460EC(s32 arg0) {
    f32 d;

    if (D_ovl10_08_800497E8[arg0] & 1) {
        d = func_ovl10_08_80045E7C(arg0);
        if (D_ovl10_08_800499AC == -1 && (D_ovl10_08_800497E8[arg0] & 2) && d <= 300.0f) {
            func_ovl10_08_80045ED4(arg0, 1);
        } else {
            func_ovl10_08_80045ED4(arg0, 0);
        }
    }
}

void func_ovl10_08_80046038(void) {
    s32 i;
    f32 d;

    i = D_ovl10_08_80049818[D_ovl10_08_80049AE8];
    d = func_ovl10_08_80045E7C(i);
    if (D_ovl10_08_800499AC == -1 && d <= 300.0f) {
        func_ovl10_08_80045ED4(i, 1);
    } else {
        func_ovl10_08_80045ED4(i, 0);
    }
    if (D_ovl10_08_80049950[i] != 0) {
        func_ovl10_08_80045C70();
    }
}

void func_ovl10_08_80045ED4(s32 arg0, s32 arg1) {
    s32 pad[2];
    Vec3f pos;
    s32 i;
    s32 n;

    n = 0;
    for (i = 0; i < D_ovl10_08_80049918; i++) {
        if ((D_ovl10_08_800497E8[i] & 2) && func_ovl10_08_80045E7C(i) <= 300.0f) {
            n++;
        }
    }
    if (arg1 != 0 && n == 1 && D_ovl10_08_800499AC == -1) {
        func_ovl10_08_800489B8(D_ovl10_08_80049700[arg0], &pos);
        D_ovl10_08_800499AC = func_ovl10_08_80048FE8(0x9D, &pos);
    }
    if (arg1 == 0 && n == 0 && D_ovl10_08_800499AC != -1) {
        func_ovl10_08_80043060();
    }
}

f32 func_ovl10_08_80045E7C(s32 arg0) {
    s32 pad;
    Vec3f a;
    Vec3f b;

    func_ovl10_08_800489B8(D_ovl10_08_80049700[arg0], &a);
    func_ovl10_08_800489B8(func_ovl10_08_80048128(func_ovl10_08_800480C8()), &b);
    return func_ovl10_08_80048890(&a, &b);
}

void func_ovl10_08_80045CC4(void) {
    s32 i;

    i = D_ovl10_08_80049C88[D_ovl10_08_80049AE8];
    D_ovl10_08_80049BF8[i]->unk40->unk28 += D_ovl10_08_80049DC0[i];
    D_ovl10_08_80049BF8[i]->unk40->unk2C += D_ovl10_08_80049DC0[i];
    D_ovl10_08_80049BF8[i]->unk40->unk30 += D_ovl10_08_80049DC0[i];
    if ((D_ovl10_08_80049DC0[i] > 0.0f && D_ovl10_08_80049DD8[i] <= D_ovl10_08_80049BF8[i]->unk40->unk28) ||
        (D_ovl10_08_80049DC0[i] < 0.0f && D_ovl10_08_80049BF8[i]->unk40->unk28 <= D_ovl10_08_80049DD8[i])) {
        D_ovl10_08_80049BF8[i]->unk40->unk28 = D_ovl10_08_80049DD8[i];
        D_ovl10_08_80049BF8[i]->unk40->unk2C = D_ovl10_08_80049DD8[i];
        D_ovl10_08_80049BF8[i]->unk40->unk30 = D_ovl10_08_80049DD8[i];
        if (D_ovl10_08_80049C70[i] == 0) {
            func_ovl10_08_80045C8C(i);
        }
        func_ovl10_08_80044D88(i);
        D_ovl10_08_80049DA8[i] = 0;
        func_ovl10_08_80045C70();
    }
}

void func_ovl10_08_80045C8C(s32 arg0) {
    func_ovl10_08_80048900(D_ovl10_08_80049BF8[arg0]);
    D_ovl10_08_80049BF8[arg0] = NULL;
}

/* clears the running task */
void func_ovl10_08_80045C70(void) {
    D_ovl10_08_80049AF0[D_ovl10_08_80049AE8] = NULL;
}

void func_ovl10_08_80045BA4(void) {
    func_ovl10_08_80048EB8(func_ovl10_08_800480C8(), 2);
    func_ovl10_08_80048EC0(func_ovl10_08_800480C8(), 8);
    func_ovl10_08_80048A80();
    func_ovl10_08_800480D8(1);
    func_ovl10_08_80048050(0);
    func_ovl10_08_80048188(1);
    func_ovl10_08_800480F0("WM1 WAP WG1 WSH WDE WB1");
    func_ovl10_08_800480F0("ST230 WM1 WAP WG1 WSH WDW WB5 WDS WB14 WDE WB13");
    func_ovl10_08_800480F0("WM1 WAP WG1 WSH WDN WB5 M0 M0 ST40 M0 M0 ST20 M5 WB8");
    func_ovl10_08_800480F0("WM1 WAP WG1 WSH WDE WB2 M0 M0 ST40 M0 M0 ST20 M5 WB5");
    func_ovl10_08_80048188(0);
    func_ovl10_08_800480F0("WM1 WAP WG1 WSH WDE WB10");
    func_ovl10_08_80048A58(10);
    func_ovl10_08_80049138();
    func_ovl10_08_80048A48();
}

void func_ovl10_08_80045B30(void) {
    func_ovl10_08_80048748(315.0f, 32768.0f, 32768.0f);
    func_ovl10_08_80048A58(120);
    func_ovl10_08_80048760(D_ovl10_08_80049200, 0x170, 0);
    func_ovl10_08_80048A58(60);
    func_ovl10_08_80048760(D_ovl10_08_80049200, 0x170, 0);
    func_ovl10_08_80048A48();
}

void func_ovl10_08_80045988(s32 arg0) {
    switch (arg0) {
        case 2:
            func_ovl10_08_80045768();
            break;
        case 17:
            func_ovl10_08_80044C58();
            break;
        case 18:
            func_ovl10_08_80044BB0();
            break;
        case 19:
            func_ovl10_08_80044AFC();
            break;
        case 25:
            func_ovl10_08_80044938();
            break;
        case 4:
            func_ovl10_08_80044910();
            break;
        case 5:
            func_ovl10_08_800447D4();
            break;
        case 0x52:
            func_ovl10_08_80044768();
            break;
        case 0x53:
            func_ovl10_08_800437C8();
            break;
        case 0x50:
            func_ovl10_08_800437A8();
            break;
        case 1:
            func_ovl10_08_800430B0();
            break;
    }
}

void func_ovl10_08_80045768(void) {
    s32 tbl[10] = { 1, 1, 0xF, 1, 4, 0xF, 0x2D, 4, 0xF, -1 };
    s32 pad[2];

    func_ovl10_08_80048DA0(D_ovl10_08_80049288);
    func_ovl10_08_80048F48(0, 0, 0xDE);
    func_ovl10_08_80048F48(1, 0x11, 0xEF);
    func_ovl10_08_80048F48(2, 0x1A, 0xF8);
    func_ovl10_08_80048F48(3, 0x1B, 0xF9);
    func_ovl10_08_80048F48(4, 0x18, 0xF6);
    func_ovl10_08_80047EE8(0x1EB);
    func_ovl10_08_80047EF0(0x1EC, 0.0f, 0.0f, 0.0f, 0x60, 0);
    func_ovl10_08_80047EF0(0xC7, 0.0f, 0.0f, 0.0f, 0x50, 0);
    func_ovl10_08_80047EF0(0xC7, 0.0f, 12000.0f, 0.0f, 0x50, 0);
    func_ovl10_08_80047F60(0x1F4);
    D_ovl10_08_80049E60 = func_ovl10_08_80047FB8(0x1F5);
    if (*func_ovl10_08_80048038() & 2) {
        func_ovl10_08_80047FC0(D_ovl10_08_80049E60, 8, 8, 0x10, 0x18, 8, 4, 8);
    }
    func_ovl10_08_80047F68();
    func_ovl10_08_80048D78(0x3C6, 0x3E8, 0, 0xFF, 0xFF);
    func_ovl10_08_80048D88(0, 0xFF, 0xFF);
    func_ovl10_08_80048098();
    func_ovl10_08_800455FC(D_ovl10_08_800493C4);
    func_ovl10_08_80045548(D_ovl10_08_800494A4);
    func_ovl10_08_80045268(D_ovl10_08_800494B8);
    func_ovl10_08_80044F98(D_ovl10_08_800492AC);
    func_ovl10_08_80044E4C(D_ovl10_08_80049378);
    D_ovl10_08_8004A90C = 0;
    func_ovl10_08_80047FD0(func_ovl10_08_800476B8);
    func_ovl10_08_80044D0C();
}

/* reads records of 11 words up to a -1 */
void func_ovl10_08_800455FC(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_08_80049E90[i][0] = arg0[0];
        D_ovl10_08_80049E90[i][1] = arg0[1];
        D_ovl10_08_80049E90[i][2] = arg0[2];
        D_ovl10_08_80049F58[i] = arg0[3];
        D_ovl10_08_80049F08[i] = arg0[4];
        D_ovl10_08_80049F20[i] = arg0[5];
        D_ovl10_08_80049F38[i] = arg0[6];
        D_ovl10_08_80049F70[i] = arg0[7];
        D_ovl10_08_80049F88[i] = arg0[8];
        D_ovl10_08_80049FA0[i] = arg0[9];
        D_ovl10_08_80049FB8[i] = arg0[10];
        arg0 += 11;
        func_ovl10_08_800437E8(i);
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_08_80049F50 = i;
}

void func_ovl10_08_80045548(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
        D_ovl10_08_80049DF8[i][0] = arg0[0];
        D_ovl10_08_80049DF8[i][1] = arg0[1];
        D_ovl10_08_80049DF8[i][2] = arg0[2];
        D_ovl10_08_80049E40[i] = arg0[3];
        D_ovl10_08_80049E50[i] = 0;
        arg0 += 4;
        i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_08_80049E38 = i;
    for (i = 1; i < 5; i++) {
        D_ovl10_08_80049E68[i] = 0;
    }
}

/* reads the gates: records of 4 words up to a -1 */
void func_ovl10_08_80045268(s32 *arg0) {
    s32 i;
    s32 v;
    Vec3f pos;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_08_80049FF0[i][0] = arg0[0];
            D_ovl10_08_80049FF0[i][1] = arg0[1];
            D_ovl10_08_80049FF0[i][2] = arg0[2];
            D_ovl10_08_8004A004[i] = arg0[3];
            arg0 += 4;
            func_ovl10_08_80047F48(D_ovl10_08_80049FF0[i][0], D_ovl10_08_80049FF0[i][1], D_ovl10_08_80049FF0[i][2],
                                   &pos, 0);
            D_ovl10_08_80049FFC[i] = func_ovl10_08_80048910(0xC2, 0x01000110, 0xD0, 0);
            D_ovl10_08_80049FFC[i]->unk40->unk10 = pos.x;
            D_ovl10_08_80049FFC[i]->unk40->unk14 = pos.y;
            D_ovl10_08_80049FFC[i]->unk40->unk18 = pos.z + 50.0f;
            D_ovl10_08_80049FFC[i]->unk34 = 50.0f;
            D_ovl10_08_80049FFC[i]->unk38 = 50.0f;
            D_ovl10_08_8004A000[i] = func_ovl10_08_80048910(0xC2, 0x01000110, 0xD0, 0);
            D_ovl10_08_8004A000[i]->unk40->unk10 = pos.x;
            D_ovl10_08_8004A000[i]->unk40->unk14 = pos.y;
            D_ovl10_08_8004A000[i]->unk40->unk18 = pos.z + 250.0f;
            D_ovl10_08_8004A000[i]->unk40->unk20 = 180.0f;
            D_ovl10_08_8004A000[i]->unk34 = 50.0f;
            D_ovl10_08_8004A000[i]->unk38 = 50.0f;
            if (D_ovl10_08_8004A004[i] != 0) {
                v = 1;
                D_ovl10_08_80049FFC[i]->unk40->unk18 -= 100.0f;
                D_ovl10_08_8004A000[i]->unk40->unk18 += 100.0f;
            } else {
                v = 15;
            }
            func_ovl10_08_80047F20(D_ovl10_08_80049FF0[i][0], D_ovl10_08_80049FF0[i][1], D_ovl10_08_80049FF0[i][2] + 1, v);
            func_ovl10_08_80047F20(D_ovl10_08_80049FF0[i][0], D_ovl10_08_80049FF0[i][1], D_ovl10_08_80049FF0[i][2] + 2, v);
            D_ovl10_08_8004A10C[i] = 0;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_08_8004A108 = i;
}

void func_ovl10_08_80044F98(s32 *arg0) {
    s32 i;
    s32 j;
    s32 flags;
    s32 pad;
    Vec3f pos;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_08_80049730[i][0] = arg0[0];
            D_ovl10_08_80049730[i][1] = arg0[1];
            D_ovl10_08_80049730[i][2] = arg0[2];
            flags = arg0[3];
            D_ovl10_08_800497B8[i] = flags & 0xF;
            D_ovl10_08_800499B0[i] = flags >> 4;
            D_ovl10_08_80049980[i] = arg0[4];
            arg0 += 5;
            func_ovl10_08_80047F48(D_ovl10_08_80049730[i][0], D_ovl10_08_80049730[i][1], D_ovl10_08_80049730[i][2],
                                   &pos, 0);
            D_ovl10_08_80049700[i] = func_ovl10_08_80048910(0xBD, 0, 0xD0, 0);
            D_ovl10_08_80049700[i]->unk40->unk10 = pos.x;
            D_ovl10_08_80049700[i]->unk40->unk14 = pos.y;
            D_ovl10_08_80049700[i]->unk40->unk18 = pos.z;
            if (D_ovl10_08_800497B8[i] & 2) {
                D_ovl10_08_80049700[i]->unk40->unk10 = pos.x + 5.0f;
                D_ovl10_08_80049700[i]->unk40->unk20 = 270.0f;
            } else {
                D_ovl10_08_80049700[i]->unk40->unk18 = pos.z - 5.0f;
            }
            func_ovl10_08_80048630(D_ovl10_08_80049700[i]->unk40, 0, 0x28, 0x190, 0, 0);
            D_ovl10_08_800497E8[i] = 0;
            if (D_ovl10_08_800497B8[i] & 1) {
                for (j = 0; j < D_ovl10_08_800499B0[i]; j++) {
                    func_ovl10_08_80047F20(D_ovl10_08_80049730[i][0] + j, D_ovl10_08_80049730[i][1], D_ovl10_08_80049730[i][2], 1);
                }
            } else {
                for (j = 0; j < D_ovl10_08_800499B0[i]; j++) {
                    func_ovl10_08_80047F20(D_ovl10_08_80049730[i][0] + j, D_ovl10_08_80049730[i][1], D_ovl10_08_80049730[i][2], 1);
                }
            }
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_08_80049918 = i;
    D_ovl10_08_800499AC = -1;
}

void func_ovl10_08_80044E4C(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[0] != -1) {
            D_ovl10_08_80049C10[i][0] = arg0[0];
            D_ovl10_08_80049C10[i][1] = arg0[1];
            D_ovl10_08_80049C10[i][2] = arg0[2];
            D_ovl10_08_80049C58[i] = arg0[3];
            D_ovl10_08_80049D90[i] = arg0[4];
            D_ovl10_08_80049C70[i] = arg0[5];
            arg0 += 6;
            D_ovl10_08_80049BF8[i] = NULL;
            if (D_ovl10_08_80049C70[i] != 0) {
                func_ovl10_08_80043A60(i);
            }
            func_ovl10_08_80044D88(i);
            D_ovl10_08_80049DA8[i] = 0;
            i++;
        }
    } while (arg0[0] != -1);
    D_ovl10_08_80049D88 = i;
}

void func_ovl10_08_80044D88(s32 arg0) {
    s32 v;
    s32 w;
    s32 t;
    s32 h;
    s32 pad;

    if (D_ovl10_08_80049C70[arg0] != 0) {
        v = 1;
    } else {
        v = 0;
    }
    if (D_ovl10_08_80049C58[arg0] & 4) {
        w = 6;
        h = 3;
    }
    if (D_ovl10_08_80049C58[arg0] & 8) {
        w = 5;
        h = 1;
    }
    if (D_ovl10_08_80049C58[arg0] & 2) {
        t = h;
        h = w;
        w = t;
    }
    func_ovl10_08_80047F98(D_ovl10_08_80049C10[arg0][0], D_ovl10_08_80049C10[arg0][1], D_ovl10_08_80049C10[arg0][2],
                           D_ovl10_08_80049C10[arg0][0] + w, D_ovl10_08_80049C10[arg0][2] + h, v);
}

void func_ovl10_08_80044D0C(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_ovl10_08_80049AF0[i] = NULL;
        D_ovl10_08_800499E8[i] = 0;
    }
    func_ovl10_08_80048A38(func_ovl10_08_80047964, 0, 0, 0, 0x110);
}

/* empty: two stubs before 80044D0C */
void func_ovl10_08_80044D04(void) {
}

void func_ovl10_08_80044CFC(void) {
}

void func_ovl10_08_80044C58(void) {
    D_ovl10_08_80049E7C = 0;
    D_ovl10_08_80049EF4 = 1;
    D_ovl10_08_80049FD0 = -1100.0f;
    D_ovl10_08_80049FD4 = 90.0f;
    D_ovl10_08_80049EF8 = 1;
    D_ovl10_08_80049EFC = 0xF;
    D_ovl10_08_80049FD8 = 21.0f;
    D_ovl10_08_80049FDC = -0.2f;
    D_ovl10_08_80049FE0 = 50.0f;
    D_ovl10_08_80049FE4 = 50.0f;
    func_ovl10_08_80044998();
    D_ovl10_08_800499DC = 1;
}

void func_ovl10_08_80044BB0(void) {
    D_ovl10_08_80049E7C = 1;
    D_ovl10_08_80049EF4 = 4;
    D_ovl10_08_80049FD0 = 1100.0f;
    D_ovl10_08_80049FD4 = 90.0f;
    D_ovl10_08_80049EF8 = 1;
    D_ovl10_08_80049EFC = 0xF;
    D_ovl10_08_80049FD8 = -21.0f;
    D_ovl10_08_80049FDC = 0.2f;
    D_ovl10_08_80049FE0 = 50.0f;
    D_ovl10_08_80049FE4 = 50.0f;
    func_ovl10_08_80044998();
    D_ovl10_08_800499DC = 2;
}

void func_ovl10_08_80044AFC(void) {
    D_ovl10_08_80049E7C = 2;
    D_ovl10_08_80049EF4 = 4;
    D_ovl10_08_80049FD0 = 1100.0f;
    D_ovl10_08_80049FD4 = 270.0f;
    D_ovl10_08_80049EF8 = 0x2D;
    D_ovl10_08_80049EFC = 0xF;
    D_ovl10_08_80049FD8 = -21.0f;
    D_ovl10_08_80049FDC = 0.2f;
    D_ovl10_08_80049FE0 = 49.0f;
    D_ovl10_08_80049FE4 = 50.0f;
    func_ovl10_08_80044998();
    D_ovl10_08_800499DC = 3;
}

void func_ovl10_08_80044998(void) {
    f32 y;

    D_ovl10_08_80049FE8 = -1.0f;
    y = func_ovl10_08_80047F88(D_ovl10_08_80049EF4);
    func_ovl10_08_800480A0(D_ovl10_08_80049EF8, D_ovl10_08_80049EF4, D_ovl10_08_80049EFC);
    func_ovl10_08_800480D8(1);
    D_ovl10_08_80049EF0 = func_ovl10_08_80048128(func_ovl10_08_800480C8());
    D_ovl10_08_80049EF0->unk70 = 0.0f;
    D_ovl10_08_80049EF0->unk40->unk10 += D_ovl10_08_80049FE0;
    D_ovl10_08_80049EF0->unk40->unk14 += D_ovl10_08_80049FD0;
    D_ovl10_08_80049EF0->unk40->unk18 += D_ovl10_08_80049FE4;
    D_ovl10_08_80049EF0->unk40->unk20 = D_ovl10_08_80049FD4;
    D_ovl10_08_80049ED8[D_ovl10_08_80049E7C]->unk40->unk14 += D_ovl10_08_80049FD0;
    func_ovl10_08_800431C8(D_ovl10_08_80049E7C, D_ovl10_08_80049FD8, D_ovl10_08_80049FDC, y);
    D_ovl10_08_80049EF0->unk70 = 1.6333334f;
}

void func_ovl10_08_80044938(void) {
    func_ovl10_08_800480A0(0xF, 1, 9);
    func_ovl10_08_800480E0(0x40);
    D_ovl10_08_80049E50[0] = 1;
    func_ovl10_08_80044448(0, 1);
    D_ovl10_08_80049E68[1] = 1;
    func_ovl10_08_8004393C();
    D_ovl10_08_800499DC = 9;
}

void func_ovl10_08_80044910(void) {
    func_ovl10_08_800480F8();
    func_ovl10_08_80044880();
}

void func_ovl10_08_80044880(void) {
    D_ovl10_08_80049DF0 = func_ovl10_08_80048038();
    if (*D_ovl10_08_80049DF0 & 2) {
        func_ovl10_08_80048A38(func_ovl10_08_80045BA4, 0, 0, 0, 0x130);
        func_ovl10_08_80048A38(func_ovl10_08_80045B30, 0, 0, 0, 0x130);
        func_ovl10_08_80048790(15);
        func_ovl10_08_800487A0(2);
        func_ovl10_08_80048F68(0);
    }
}

void func_ovl10_08_800447D4(void) {
    switch (D_ovl10_08_800499DC) {
        case 1:
        case 2:
            func_ovl10_08_80048A58(0x78);
            func_ovl10_08_800480E8(0x40, 3, 8.5f, 2, 0, 1, 1);
            break;
        case 3:
            func_ovl10_08_80048A58(0x78);
            func_ovl10_08_800480E8(0xC0, 3, 8.5f, 2, 0, 1, 1);
            break;
    }
}

void func_ovl10_08_80044768(void) {
    func_ovl10_08_80048FC0(0x29);
    func_ovl10_08_800445A0();
    if (D_ovl10_08_80049E68[1] != 0) {
        func_ovl10_08_80044238(0, 0);
    } else {
        func_ovl10_08_80044238(0, 1);
    }
    func_ovl10_08_80044188();
    func_ovl10_08_80043D38();
    func_ovl10_08_8004393C();
}

void func_ovl10_08_800445A0(void) {
    s32 found;
    s32 i;

    found = -1;
    i = 0;
    do {
        if (func_ovl10_08_800480B8(D_ovl10_08_80049DF8[i][0], D_ovl10_08_80049DF8[i][1], D_ovl10_08_80049DF8[i][2],
                                   D_ovl10_08_80049DF8[i][0] + 1, D_ovl10_08_80049DF8[i][2] + 1) != 0) {
            found = i;
        }
        i++;
    } while (i < D_ovl10_08_80049E38 && found == -1);
    if (found != -1) {
        D_ovl10_08_80049E50[found] = (D_ovl10_08_80049E50[found] + 1) % 2;
        func_ovl10_08_80044448(found, D_ovl10_08_80049E50[found]);
        D_ovl10_08_80049E68[D_ovl10_08_80049E40[found]] = (D_ovl10_08_80049E68[D_ovl10_08_80049E40[found]] + 1) % 2;
        if (D_ovl10_08_80049E50[found] == 1 && D_ovl10_08_80049E40[found] != 4) {
            for (i = 0; i < D_ovl10_08_80049E38; i++) {
                if (i != found && D_ovl10_08_80049E40[i] != 4 && D_ovl10_08_80049E50[i] == 1) {
                    D_ovl10_08_80049E50[i] = 0;
                    func_ovl10_08_80044448(i, 0);
                    D_ovl10_08_80049E68[D_ovl10_08_80049E40[i]] = 0;
                }
            }
        }
    }
}

void func_ovl10_08_80044448(s32 arg0, s32 arg1) {
    s32 sp38[4] = { 0xBF, 0xC0, 0xC1, 0xC4 };
    Vec3f pos;

    if (arg1 == 1) {
        D_ovl10_08_80049E28[arg0] =
            func_ovl10_08_80048910(sp38[D_ovl10_08_80049E40[arg0] - 1], 0x01000000, 0xD0, 0);
        func_ovl10_08_80047F48(D_ovl10_08_80049DF8[arg0][0], D_ovl10_08_80049DF8[arg0][1],
                               D_ovl10_08_80049DF8[arg0][2], &pos, 0);
        D_ovl10_08_80049E28[arg0]->unk40->unk10 = pos.x;
        D_ovl10_08_80049E28[arg0]->unk40->unk14 = pos.y;
        D_ovl10_08_80049E28[arg0]->unk40->unk18 = pos.z;
    } else {
        func_ovl10_08_80048900(D_ovl10_08_80049E28[arg0]);
        D_ovl10_08_80049E28[arg0] = NULL;
    }
}

/* opens (arg1 1) or closes the gate */
void func_ovl10_08_80044238(s32 arg0, s32 arg1) {
    s32 pad;
    Vec3f pos;

    if (arg1 != D_ovl10_08_8004A004[arg0]) {
        if (D_ovl10_08_8004A10C[arg0] == 0) {
            D_ovl10_08_8004A008[func_ovl10_08_80043150(func_ovl10_08_8004701C)] = arg0;
        }
        if (arg1 != 0) {
            D_ovl10_08_8004A114[arg0] = D_ovl10_08_80049FFC[arg0]->unk40->unk18 - 100.0f;
            D_ovl10_08_8004A118[arg0] = D_ovl10_08_8004A000[arg0]->unk40->unk18 + 100.0f;
            D_ovl10_08_8004A110[arg0] = -5.0f;
            func_ovl10_08_80047F20(D_ovl10_08_80049FF0[arg0][0], D_ovl10_08_80049FF0[arg0][1], D_ovl10_08_80049FF0[arg0][2] + 1, 0);
            func_ovl10_08_80047F20(D_ovl10_08_80049FF0[arg0][0], D_ovl10_08_80049FF0[arg0][1], D_ovl10_08_80049FF0[arg0][2] + 2, 0);
        } else {
            D_ovl10_08_8004A114[arg0] = D_ovl10_08_80049FFC[arg0]->unk40->unk18 + 100.0f;
            D_ovl10_08_8004A118[arg0] = D_ovl10_08_8004A000[arg0]->unk40->unk18 - 100.0f;
            D_ovl10_08_8004A110[arg0] = 5.0f;
            func_ovl10_08_80047F20(D_ovl10_08_80049FF0[arg0][0], D_ovl10_08_80049FF0[arg0][1], D_ovl10_08_80049FF0[arg0][2] + 1, 9);
            func_ovl10_08_80047F20(D_ovl10_08_80049FF0[arg0][0], D_ovl10_08_80049FF0[arg0][1], D_ovl10_08_80049FF0[arg0][2] + 2, 9);
        }
        func_ovl10_08_800489B8(D_ovl10_08_80049FFC[arg0], &pos);
        D_ovl10_08_8004A10C[arg0] = 1;
    }
}

void func_ovl10_08_80044188(void) {
    s32 i;

    if (D_ovl10_08_8004A90C == 0) {
        for (i = 0; i < D_ovl10_08_80049918; i++) {
            if (D_ovl10_08_800497E8[i] != D_ovl10_08_80049E68[D_ovl10_08_80049980[i]]) {
                func_ovl10_08_80043F34(i, D_ovl10_08_80049E68[D_ovl10_08_80049980[i]]);
            }
        }
    }
}

void func_ovl10_08_80043F34(s32 arg0, s32 arg1) {
    s32 j;
    s32 v;
    s32 pad[2];

    if (arg1 != (D_ovl10_08_800497E8[arg0] & 1)) {
        if (arg1 != 0) {
            D_ovl10_08_800497E8[arg0] |= 1;
        } else {
            D_ovl10_08_800497E8[arg0] &= ~1;
        }
        if (D_ovl10_08_800497B8[arg0] & 4) {
            func_ovl10_08_80043F04(arg0);
            if (arg1 != 0) {
                v = 9;
                D_ovl10_08_800497E8[arg0] |= 2;
                /* func_ovl10_08_80043EBC(arg0), written out */
                D_ovl10_08_80049818[func_ovl10_08_80043150(func_ovl10_08_80046038)] = arg0;
                D_ovl10_08_80049950[arg0] = 0;
            } else {
                D_ovl10_08_800497E8[arg0] &= ~2;
                func_ovl10_08_80043E8C(arg0);
                v = 1;
                func_ovl10_08_80043DDC(arg0);
            }
            /* Nothing, but it keeps arg0 in v1 for the loops. */
            if (arg0) {
            }
            if (D_ovl10_08_800497B8[arg0] & 1) {
                for (j = 0; j < D_ovl10_08_800499B0[arg0]; j++) {
                    func_ovl10_08_80047F20(D_ovl10_08_80049730[arg0][0] + j, D_ovl10_08_80049730[arg0][1], D_ovl10_08_80049730[arg0][2], v);
                }
            } else {
                for (j = 0; j < D_ovl10_08_800499B0[arg0]; j++) {
                    func_ovl10_08_80047F20(D_ovl10_08_80049730[arg0][0], D_ovl10_08_80049730[arg0][1], D_ovl10_08_80049730[arg0][2] + j, v);
                }
            }
        }
        if (D_ovl10_08_800497B8[arg0] & 8) {
            if (arg1 != 0) {
                func_ovl10_08_80043DF4(arg0);
            } else {
                func_ovl10_08_80043DDC(arg0);
            }
        }
    }
}

void func_ovl10_08_80043F04(s32 arg0) {
    func_ovl10_08_800488E8(D_ovl10_08_80049700[arg0], 0x01000000);
}

void func_ovl10_08_80043EBC(s32 arg0) {
    D_ovl10_08_80049818[func_ovl10_08_80043150(func_ovl10_08_80046038)] = arg0;
    D_ovl10_08_80049950[arg0] = 0;
}

void func_ovl10_08_80043E8C(s32 arg0) {
    func_ovl10_08_800488F0(D_ovl10_08_80049700[arg0], 0x01000000);
}

void func_ovl10_08_80043DF4(s32 arg0) {
    D_ovl10_08_80049818[func_ovl10_08_80043150(func_ovl10_08_8004618C)] = arg0;
    D_ovl10_08_80049950[arg0] = 0;
    if (D_ovl10_08_8004A90C != 0) {
        D_ovl10_08_80049920[arg0] = 30;
    } else {
        D_ovl10_08_80049920[arg0] = func_ovl10_08_80048BF8(60) + 90;
    }
    D_ovl10_08_800497E8[arg0] = 1;
}

void func_ovl10_08_80043DDC(s32 arg0) {
    D_ovl10_08_80049950[arg0] = 1;
}

void func_ovl10_08_80043D38(void) {
    s32 i;

    for (i = 0; i < D_ovl10_08_80049D88; i++) {
        if (D_ovl10_08_80049C70[i] != D_ovl10_08_80049E68[D_ovl10_08_80049D90[i]]) {
            func_ovl10_08_80043C3C(i, D_ovl10_08_80049E68[D_ovl10_08_80049D90[i]]);
        }
    }
}

void func_ovl10_08_80043C3C(s32 arg0, s32 arg1) {
    D_ovl10_08_80049C70[arg0] = arg1;
    if (D_ovl10_08_80049DA8[arg0] == 0) {
        D_ovl10_08_80049C88[func_ovl10_08_80043150(func_ovl10_08_80045CC4)] = arg0;
    }
    if (arg1 != 0) {
        D_ovl10_08_80049DC0[arg0] = 0.05f;
        D_ovl10_08_80049DD8[arg0] = 1.0f;
        if (D_ovl10_08_80049BF8[arg0] == NULL) {
            func_ovl10_08_80043A60(arg0);
        }
        func_ovl10_08_80048FC0(0xA2);
    } else {
        D_ovl10_08_80049DC0[arg0] = -0.05f;
        D_ovl10_08_80049DD8[arg0] = 0.0f;
    }
    D_ovl10_08_80049DA8[arg0] = 1;
}

void func_ovl10_08_80043A60(s32 arg0) {
    s32 sp40[2] = { 0xC5, 0xC6 };
    Vec3f pos;

    func_ovl10_08_80047F48(D_ovl10_08_80049C10[arg0][0], D_ovl10_08_80049C10[arg0][1], D_ovl10_08_80049C10[arg0][2], &pos, 0);
    D_ovl10_08_80049BF8[arg0] = func_ovl10_08_80048910(sp40[(D_ovl10_08_80049C58[arg0] >> 2) - 1], 0x01080000, 0xD0, 0);
    D_ovl10_08_80049BF8[arg0]->unk40->unk10 = pos.x;
    D_ovl10_08_80049BF8[arg0]->unk40->unk14 = pos.y;
    D_ovl10_08_80049BF8[arg0]->unk40->unk18 = pos.z;
    D_ovl10_08_80049BF8[arg0]->unk40->unk28 = 0.0f;
    D_ovl10_08_80049BF8[arg0]->unk40->unk2C = 0.0f;
    D_ovl10_08_80049BF8[arg0]->unk40->unk30 = 0.0f;
    if (D_ovl10_08_80049C58[arg0] & 2) {
        if (D_ovl10_08_80049C58[arg0] & 4) {
            D_ovl10_08_80049BF8[arg0]->unk40->unk18 += 600.0f;
        }
        if (D_ovl10_08_80049C58[arg0] & 8) {
            D_ovl10_08_80049BF8[arg0]->unk40->unk18 += 500.0f;
        }
        D_ovl10_08_80049BF8[arg0]->unk40->unk20 = 90.0f;
    }
}

void func_ovl10_08_8004393C(void) {
    s32 i;

    for (i = 0; i < D_ovl10_08_80049F50; i++) {
        if (D_ovl10_08_80049F08[i] == 2 && D_ovl10_08_80049F20[i] != D_ovl10_08_80049E68[D_ovl10_08_80049F38[i]]) {
            if (D_ovl10_08_80049ED8[i] != NULL) {
                func_ovl10_08_80043904(i);
            }
            D_ovl10_08_80049F20[i] = D_ovl10_08_80049E68[D_ovl10_08_80049F38[i]];
            func_ovl10_08_800437E8(i);
        }
    }
}

void func_ovl10_08_80043904(s32 arg0) {
    func_ovl10_08_80048900(D_ovl10_08_80049ED8[arg0]);
    D_ovl10_08_80049ED8[arg0] = NULL;
}

void func_ovl10_08_800437E8(s32 arg0) {
    Vec3f pos;
    s32 sp2C[2] = { 0xCA, 0xB2 };

    D_ovl10_08_80049ED8[arg0] = func_ovl10_08_80048910(sp2C[D_ovl10_08_80049F20[arg0]], 0x01000000, 0xD0, 0);
    func_ovl10_08_80047F48(D_ovl10_08_80049E90[arg0][0], D_ovl10_08_80049E90[arg0][1], D_ovl10_08_80049E90[arg0][2],
                           &pos, 0);
    D_ovl10_08_80049ED8[arg0]->unk40->unk10 = pos.x;
    D_ovl10_08_80049ED8[arg0]->unk40->unk14 = pos.y;
    D_ovl10_08_80049ED8[arg0]->unk40->unk18 = pos.z;
}

void func_ovl10_08_800437C8(void) {
    func_ovl10_08_800434D8(2);
}

void func_ovl10_08_800437A8(void) {
    func_ovl10_08_800434D8(1);
}

s32 func_ovl10_08_800434D8(s32 arg0) {
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    if (arg0 == 2) {
        do {
            if (D_ovl10_08_80049F08[i] == 2 && D_ovl10_08_80049F20[i] == 1 &&
                func_ovl10_08_800480B8(D_ovl10_08_80049E90[i][0], D_ovl10_08_80049E90[i][1],
                                       D_ovl10_08_80049E90[i][2], D_ovl10_08_80049E90[i][0] + 1,
                                       D_ovl10_08_80049E90[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_08_80049F50 && found == 0);
        if (found) {
            D_ovl10_08_80049E7C = i;
            if (D_ovl10_08_80049F58[i] < D_ovl10_08_80049E90[i][1]) {
                D_ovl10_08_80049FD8 = 0.0f;
                D_ovl10_08_80049FDC = -0.2f;
            } else {
                D_ovl10_08_80049FD8 = -0.0f;
                D_ovl10_08_80049FDC = 0.2f;
            }
        }
    } else {
        do {
            if (func_ovl10_08_800480B8(D_ovl10_08_80049E90[i][0], D_ovl10_08_80049E90[i][1],
                                       D_ovl10_08_80049E90[i][2], D_ovl10_08_80049E90[i][0] + 1,
                                       D_ovl10_08_80049E90[i][2] + 1) != 0) {
                found = 1;
            } else {
                i++;
            }
        } while (i < D_ovl10_08_80049F50 && found == 0);
    }
    if (found) {
        D_ovl10_08_80049E7C = i;
        if (D_ovl10_08_80049F58[i] < D_ovl10_08_80049E90[i][1]) {
            D_ovl10_08_80049FD8 = 0.0f;
            D_ovl10_08_80049FDC = -0.2f;
        } else {
            D_ovl10_08_80049FD8 = -0.0f;
            D_ovl10_08_80049FDC = 0.2f;
        }
        if (arg0 == 2) {
            func_ovl10_08_8004339C();
        } else {
            D_ovl10_08_80049F00 = D_ovl10_08_80049F70[i];
            D_ovl10_08_80049F04 = D_ovl10_08_80049F88[i];
            func_ovl10_08_800432B0();
        }
    }
    return found;
}

void func_ovl10_08_8004339C(void) {
    s32 out[6];
    f32 a;
    f32 b;
    s32 i;

    i = D_ovl10_08_80049E7C;
    a = func_ovl10_08_80047F88(D_ovl10_08_80049F58[i]);
    b = func_ovl10_08_80047F88(D_ovl10_08_80049E90[i][1]);
    func_ovl10_08_80048110(0x40);
    func_ovl10_08_80048100(1);
    D_ovl10_08_80049EF0 = func_ovl10_08_80048128(func_ovl10_08_800480C8());
    D_ovl10_08_80049FE8 = (a - b) * 0.5f;
    D_ovl10_08_80049FE8 += b;
    D_ovl10_08_80049EF0->unk70 = 0.0f;
    func_ovl10_08_80047F40(D_ovl10_08_80049EF0->unk40->unk10, D_ovl10_08_80049EF0->unk40->unk14,
                           D_ovl10_08_80049EF0->unk40->unk18, out, 2);
    func_ovl10_08_800480D8(1);
    func_ovl10_08_800487B0(10.0f);
    func_ovl10_08_800487B8(5.0f);
    func_ovl10_08_800487D0(0.0f);
    func_ovl10_08_800431C8(i, D_ovl10_08_80049FD8, D_ovl10_08_80049FDC, a);
}

void func_ovl10_08_800432B0(void) {
    s32 out[6];
    s32 pad1;
    s32 pad2;
    s32 pad3;

    D_ovl10_08_80049FE8 = -1.0f;
    func_ovl10_08_80048110(0x40);
    func_ovl10_08_80048100(1);
    D_ovl10_08_80049EF0 = func_ovl10_08_80048128(func_ovl10_08_800480C8());
    D_ovl10_08_80049EF0->unk70 = 0.0f;
    func_ovl10_08_80047F40(D_ovl10_08_80049EF0->unk40->unk10, D_ovl10_08_80049EF0->unk40->unk14,
                           D_ovl10_08_80049EF0->unk40->unk18, out, 2);
    func_ovl10_08_80047F20(out[0], out[1], out[2], 0);
    func_ovl10_08_800480D8(1);
    func_ovl10_08_800431C8(D_ovl10_08_80049E7C, D_ovl10_08_80049FD8, D_ovl10_08_80049FDC, -1.0f);
    func_ovl10_08_80048A58(0x78);
    D_ovl10_08_800496E4 = D_ovl10_08_80049F00;
    D_ovl10_08_800496E8 = D_ovl10_08_80049F04;
    func_ovl10_08_80047FE0(D_ovl10_08_80049F00, D_ovl10_08_80049F04, 0);
}

void func_ovl10_08_800431C8(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_ovl10_08_80049E7C = arg0;
    D_ovl10_08_80049E80 = arg1;
    D_ovl10_08_80049E84 = arg2;
    D_ovl10_08_80049E88 = arg3;
    func_ovl10_08_80043150(func_ovl10_08_80047264);
    D_ovl10_08_80049EF0 = func_ovl10_08_80048128(func_ovl10_08_800480C8());
    D_ovl10_08_80049EF0->unk70 = 0.0f;
    func_ovl10_08_80047FA0(1);
    if (arg1 == 0.0f && arg2 < 0.0f && arg3 == -1.0f) {
        func_ovl10_08_80048140(1);
    }
    func_ovl10_08_80048FC0(0x98);
    func_ovl10_08_80048050(0);
}

/* empty, as ovl_10_11's 80043044: two words before 80043150 */
void func_ovl10_08_80043148(void) {
}

void func_ovl10_08_800430B0(void) {
    func_ovl10_08_80048D38(0, 0, 0, 0.0f);
    func_ovl10_08_80043060();
    func_ovl10_08_80043018();
}

void func_ovl10_08_80043060(void) {
    if (D_ovl10_08_800499AC != -1) {
        if (func_ovl10_08_800481B0(0) != 0) {
            func_ovl10_08_80048FF0(D_ovl10_08_800499AC);
        }
        D_ovl10_08_800499AC = -1;
    }
}

void func_ovl10_08_80043018(void) {
    D_ovl10_08_80049DF0 = func_ovl10_08_80048038();
    if (*D_ovl10_08_80049DF0 & 2) {
        func_ovl10_08_80049140();
    }
}

void func_ovl10_08_80043010(void) {
}
