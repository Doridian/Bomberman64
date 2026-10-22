#include "common.h"

/* Float sign and tolerance compares.  -O3 (the Makefile's O3_C_FILES), so
 * written last function first: IDO 5.3 -O3 emits a file's functions in
 * reverse.  4E030's wrappers call these with a `jal`, which -O3 would have
 * inlined had they been one file (text_objects.txt has the boundary).
 *
 * The comparisons that give a truth value return int, not s32 (IDO's
 * long): returning `a && b` as a long computes it in $v1 and moves it to
 * $v0 at the end, as an int it is built in $v0 directly. */

f32 D_8029FE30 = 0.0001f;

s32 func_802337EC(f32 arg0) {
    return (arg0 > 0.0f) ? 1 : (arg0 < 0.0f) ? -1 : 0;
}

s32 func_802337B0(f32 arg0, f32 arg1) {
    return (arg1 < arg0) ? 1 : (arg0 < arg1) ? -1 : 0;
}

s32 func_80233768(f32 arg0) {
    return (D_8029FE30 < arg0) ? 1 : (arg0 < D_8029FE30) ? -1 : 0;
}

int func_8023372C(f32 arg0, f32 arg1) {
    return arg0 <= arg1 && -arg1 <= arg0;
}

int func_802336E4(f32 arg0) {
    return arg0 <= D_8029FE30 && -D_8029FE30 <= arg0;
}

int func_8023369C(f32 arg0, f32 arg1, f32 arg2) {
    f32 diff = arg0 - arg1;

    return diff <= arg2 && -arg2 <= diff;
}

int func_80233650(f32 arg0, f32 arg1) {
    return arg0 - arg1 <= D_8029FE30 && -D_8029FE30 <= arg0 - arg1;
}
