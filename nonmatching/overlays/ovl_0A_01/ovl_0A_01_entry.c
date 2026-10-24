/*
 * NON_MATCHING: ovl_0A_01's entry. It matches; it waits for its object
 * (an entry in src/ alone would be fine, but it goes with the object).
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O2
 * differing words: us 0, eu 0, jp 0
 *
 * What still differs in us (words):
 * Nothing.
 */
#include "common.h"

void func_ovl0A_01_80046C88(s32);

void *func_ovl0A_01_80043000(void) {
    return func_ovl0A_01_80046C88;
}
