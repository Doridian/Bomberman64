/*
 * boot_code: loads ZeroJump (its ROM segment) to its page at 0x80042000,
 * maps that page at virtual address 0 with the TLB, and registers
 * module 0's table. -O2 (the same as
 * -O3 here; -O2 is Hudson's usual).
 */
#include "common.h"
#include "ultralib/ultra64.h"

extern u8 zerojump_ROM_START[];
extern u8 zerojump_ROM_END[];
void func_80042000(void);
#ifdef TARGET_PC
void func_80000698(void *dst, u32 size, u32 rom);
#else
/* fake: func_80000698 is void (10D0.c); see func_80000450 */
s64 func_80000698(void *dst, u32 size, u32 rom);
#endif
void func_80001A30(s32 id, void **table);

/* .data: ZeroJump module 0 */
void *D_80019F80[] = { func_80001A30 };
/* .bss: the ZeroJump module table */
void **D_8001BFC0[256];

/*
 * The page's address is one expression, (u32)func_80042000, coloured over
 * both calls. The original has it in $t0 (saved at sp+0x24 across the
 * DMA); at -O2 uopt gives t0 only when v0 and v1 are both forbidden (a0
 * to a3 carry arguments in both blocks).
 * - fake: the dead test of func_80000698's result, declared s64 here,
 *   does that: the result keeps R2 live into the osMapTLB block, which
 *   forbids v0 there, and a 64-bit R2 anywhere in the procedure forbids
 *   v1 with it (uopt's r2_overlap_r3). A 32-bit result gives v1; no test
 *   gives v0. Passing the page as `(void *)(u32)func_80042000` keeps one
 *   expression for both uses (a plain `func_80042000` is a second
 *   constant, which takes a0), and a `page` local moves the save to
 *   sp+0x20.
 */
void func_80000450(void) {
#ifdef TARGET_PC
    func_80000698((void *)func_80042000, (u32)zerojump_ROM_END - (u32)zerojump_ROM_START, (u32)zerojump_ROM_START);
#else
    if (func_80000698((void *)(u32)func_80042000, (u32)zerojump_ROM_END - (u32)zerojump_ROM_START,
                      (u32)zerojump_ROM_START)) {
    }
#endif
    osMapTLB(0, OS_PM_4K, NULL, (u32)func_80042000 + 0x80000000, -1, -1);
    D_8001BFC0[0] = D_80019F80;
}
