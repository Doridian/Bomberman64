#ifndef LIBULTRA_BM64_H
#define LIBULTRA_BM64_H

/*
 * What Bomberman 64's libultra has differently from 2.0I's headers
 * (include/ultralib, decompals/ultralib's).  The game's libultra is 2.0I's
 * build, but its SI/PI layer and a few other objects are an older revision
 * (docs/LIBULTRA.md, "What doesn't match").
 */

/*
 * Time conversion through osClockRate (a u64, 0x8001B0D0), multiplied
 * then divided by __ll_mul/__ull_div: osContInit and osEepromLong*
 * compute their waits this way, where 2.0I's os_convert.h folds
 * OS_CPU_COUNTER into a constant.
 */
#undef OS_USEC_TO_CYCLES
#define OS_USEC_TO_CYCLES(n) (((u64)(n) * osClockRate) / 1000000LL)

#endif
