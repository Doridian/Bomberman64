/*
 * NON_MATCHING: ovl_0B_06's entry. It matches; it waits for its object
 * (an entry in src/ alone would be fine, but it goes with the object).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O2
 * differing words: us 0, eu 0, jp 0
 *
 * What still differs in us (words):
 * Nothing.
 */
#include "common.h"

void func_ovl0B_06_80043C48(s32);

/* The overlay's entry: the loader calls 0x80043000 and keeps the function
 * it returns (docs/LAYOUT.md, "Loaders"). */
void *func_ovl0B_06_80043000(void) {
    return func_ovl0B_06_80043C48;
}
