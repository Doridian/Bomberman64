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
void func_80000698(void *dst, u32 size, u32 rom);
void func_80001A30(s32 id, void **table);

/* .data: ZeroJump module 0 */
void *D_80019F80[] = { func_80001A30 };
/* .bss: the ZeroJump module table */
void **D_8001BFC0[256];

#ifdef NON_MATCHING
/* 6 differing words (us 6, eu 6, jp 6): `page` is in v0 rather than t0.
 * uopt gives t0 only when v0 and v1 are both forbidden over its live range:
 * declaring func_80000698 as returning s64 and testing the result in a
 * dead `if (func_80000698(...)) {}` (with no `page` local) gives exactly
 * the original, but func_80000698 is void (10D0.c) */
void func_80000450(void) {
    u32 page = (u32)func_80042000;

    func_80000698((void *)page, (u32)zerojump_ROM_END - (u32)zerojump_ROM_START, (u32)zerojump_ROM_START);
    osMapTLB(0, OS_PM_4K, NULL, page + 0x80000000, -1, -1);
    D_8001BFC0[0] = D_80019F80;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/1050/func_80000450.s")
#endif
