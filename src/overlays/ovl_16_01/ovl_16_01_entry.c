#include "common.h"

void func_ovl16_01_80043A54(s32);

/* The overlay's entry: the loader calls 0x80043000 and keeps the function
 * it returns (docs/LAYOUT.md, "Loaders").  Built -g, as the rest of the
 * overlay: the return is followed by the two `jr ra` IDO -g ends a
 * function with, so the file is 0x20 bytes. */
void *func_ovl16_01_80043000(void) {
    return func_ovl16_01_80043A54;
}
