#include "common.h"

/*
 * A subtractive random number generator (Knuth's, as in Numerical Recipes'
 * ran3, -O3): func_8025E6A4 seeds it (40040's init, with the cycle
 * counter), func_8025E5EC returns the next value in [0, MBIG),
 * func_8025E63C the same scaled to [0, 1).  Unlike ran3 it refills the
 * whole table at once (func_8025E4A0, a static: only t6-t9 as temporaries,
 * and its callers keep &D_802ACFE0 in a3 across the call), and seeds with
 * the value itself.  D_802ACFE4 (ran3's inextp) is never used.
 */

#define MBIG 1000000000

s32 D_802ACFE0;
s32 D_802ACFE4;
s32 D_802ACFE8[56];

static void func_8025E4A0(void);
s32 func_8025E5EC(void);

void func_8025E6A4(s32 mj) {
    s32 mk, i, ii;

    D_802ACFE8[55] = mj;
    mk = 1;
    for (i = 1; i < 55; i++) {
        ii = (21 * i) % 55;
        D_802ACFE8[ii] = mk;
        mk = mj - mk;
        if (mk < 0) {
            mk += MBIG;
        }
        mj = D_802ACFE8[ii];
    }
    func_8025E4A0();
    func_8025E4A0();
    func_8025E4A0();
    D_802ACFE0 = 55;
}

f64 func_8025E63C(void) {
    return func_8025E5EC() * 1e-9;
}

s32 func_8025E5EC(void) {
    if (++D_802ACFE0 >= 56) {
        func_8025E4A0();
        D_802ACFE0 = 1;
    }
    return D_802ACFE8[D_802ACFE0];
}

static void func_8025E4A0(void) {
    s32 i, j;

    for (i = 1; i < 25; i++) {
        j = D_802ACFE8[i] - D_802ACFE8[i + 31];
        if (j < 0) {
            j += MBIG;
        }
        D_802ACFE8[i] = j;
    }
    for (i = 25; i < 56; i++) {
        j = D_802ACFE8[i] - D_802ACFE8[i - 24];
        if (j < 0) {
            j += MBIG;
        }
        D_802ACFE8[i] = j;
    }
}
