#include "common.h"

/* A display list command, two words (gbi.h's Gfx, not in include/ yet). */
typedef struct {
    u32 w0;
    u32 w1;
} Gfx_80225840;

void func_80225CC0(void);
void func_80225CCC(void);
void func_80225FB8(void);
void func_8022616C(void);
void func_80226368(void);
void func_80226604(void);
void func_802266DC(void);
void func_802266E8(void);
void func_80226860(void);
void func_80226D80(void);
void func_80226E84(Gfx_80225840 *);
Gfx_80225840 *func_80227464(void);
u32 func_80227678(s32);
void func_80227708(s32, s32, s32, s32);
s32 func_8022773C(void);
void func_802277D0(void);
void func_8022787C(Gfx_80225840 **);
void func_80227D50(s32, s32, s32, s32, s32);
void func_802290CC(void);
void func_8022A858(void);
void func_80232E60(void);
void func_802334CC(void);
void func_802341C8(void);
void func_80236F54(void);
void func_80237890(void);
void func_80238100(void);
void func_802381F8(void);
void func_8023876C(s32, s32, s32);
void func_80238A10(void (*)(void), s32, void *, s32, s32);
void func_802392F8(void);
void func_8023946C(void);
void func_8023A104(void);
void func_8023A208(void);
void func_8023A22C(void);
void func_8023A318(void);
void func_8023A3E0(void);
void func_8025E16C(void);
void func_8025E1D4(Gfx_80225840 **);
void func_8025E6A4(u32);
void func_80265C04(void);
void func_8026C208(void);
void func_8026C77C(void);
void func_802817D0(void);
void func_80292B54(void);
void func_80294E54(void);
void func_80297D20(void);
void func_80297D30(s32, void *);
u64 func_80297E38(void);
void func_80297F80(s32);
void func_80297FA0(s32);
void *func_80225C7C(void *, s32, s32);
void func_80225CA8(void);
void *malloc(u32);
void free(void *);

extern u8 D_802A5300[]; /* main_code's .bss, */
extern u8 D_802B36D0[]; /* to its end */
extern u8 D_80063000[];
extern u8 D_800BEA60[];
extern s32 D_802A1230;
extern s32 D_802A1234;
extern s32 D_802A123C;
extern s32 D_802AC5C0;

/* .data */
void (*D_8029F570[])(void) = {
    func_802266E8, func_80226604, func_80226368, func_8022616C,
    func_80225FB8, func_80225CCC, func_80225CC0, func_802266DC,
};
void *D_8029F590[] = { malloc, free };

/* main_code's main function: main_code_entry calls it, and it never
 * returns. */
void func_80225840(s32 arg0) {
    s32 count;
    Gfx_80225840 *gfx;
    s32 sp3C;
    void *stack;
    u32 dl;

    count = 8;
    func_80297D20();
    func_80225C7C(D_802A5300, 0, D_802B36D0 - D_802A5300);
    func_80225C7C(D_80063000, 0, D_800BEA60 - D_80063000);
    func_80225CA8();
    func_80297D30(4, D_8029F570);
    func_80297D30(5, D_8029F590);
    func_802341C8();
    func_8023876C(arg0, 10, 10);
    func_80297F80(2);
    func_80297F80(4);
    func_80297F80(0x40);
    func_80297F80(0x10);
    func_8023946C();
    func_8023A318();
    func_8023A22C();
    func_80294E54();
    D_802A1230 = 0;
    D_802A1234 = 0;
    D_802A123C = 0;
    func_80226860();
    func_8022A858();
    func_80232E60();
    func_802817D0();
    func_80292B54();
    func_802277D0();
    func_80226D80();
    func_8025E16C();
    sp3C = func_8022773C();
    func_8026C77C();
    func_8025E6A4(func_80297E38());
    stack = malloc(0x1000);
    func_80237890();
    func_80238A10(func_80236F54, 0, stack, 0x1000, 0x401);
    func_80238A10(func_802334CC, 0, NULL, 0, 0x402);
    func_8023A208();
    func_8023A3E0();
    func_80265C04();
    while (1) {
        func_8023A104();
        gfx = func_80227464();
        func_80238100();
        func_802381F8();
        func_802392F8();
        func_8022787C(&gfx);
        func_802290CC();
        dl = func_80227678(sp3C);
        {
            /* gSPDisplayList(gfx++, dl) */
            Gfx_80225840 *g = gfx++;

            g->w1 = dl;
            g->w0 = 0x06000000;
        }
        func_8025E1D4(&gfx);
        func_8026C208();
        func_8023A208();
        func_80226E84(gfx);
        if (count != 0) {
            count--;
            if (count == 0) {
                func_80227D50(D_802AC5C0, 8, 6, 0x130, 0xE4);
                func_80227708(8, 6, 0x130, 0xE4);
                func_80297FA0(0);
            }
        }
    }
}
