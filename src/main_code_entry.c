#include "common.h"

void func_80225840(s32);

/* main_code's entry: the boot thread loads main_code to 0x80225800 and
 * calls this (docs/LAYOUT.md, "Loaders").  Built -g. */
void func_80225800(s32 arg0) {
    void (*fn)(s32) = func_80225840;

    fn(arg0);
}
