#include "common.h"

void func_ovl0C_03_8004391C(s32);

/* The overlay's entry: the loader calls 0x80043000 and keeps the function
 * it returns (docs/LAYOUT.md, "Loaders"). */
void *func_ovl0C_03_80043000(void) {
    return func_ovl0C_03_8004391C;
}
