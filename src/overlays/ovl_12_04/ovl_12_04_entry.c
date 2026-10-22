#include "common.h"

void func_ovl12_04_80043570(s32);

/* The overlay's entry: the loader calls 0x80043000 and keeps the function
 * it returns (docs/LAYOUT.md, "Loaders"). */
void *func_ovl12_04_80043000(void) {
    return func_ovl12_04_80043570;
}
