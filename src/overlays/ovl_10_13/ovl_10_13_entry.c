#include "common.h"

void func_ovl10_13_80046940(s32);

/* The overlay's entry: the loader calls 0x80043000 and keeps the function
 * it returns (docs/LAYOUT.md, "Loaders"). */
void *func_ovl10_13_80043000(void) {
    return func_ovl10_13_80046940;
}
