#include "common.h"

void func_ovl09_02_800430A0(void);

/* The overlay's entry: the loader calls 0x80043000 and keeps the function
 * it returns (docs/LAYOUT.md, "Loaders"). */
void *func_ovl09_02_80043000(void) {
    return func_ovl09_02_800430A0;
}
