/*
 * NON_MATCHING: ovl_17_07's entry. It matches; it waits for its object.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O2
 * differing words: us 0, eu 0, jp 0
 */
#include "common.h"

void func_ovl17_07_8004320C(s32);

/* The overlay's entry: the loader calls 0x80043000 and keeps the function
 * it returns (docs/LAYOUT.md, "Loaders"). */
void *func_ovl17_07_80043000(void) {
    return func_ovl17_07_8004320C;
}
