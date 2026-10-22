#ifndef MACROS_H
#define MACROS_H

/* Helpers the game's C uses in more than one file. */

/* ovl_17_04 compares with 0.0f, and IDO's code for the two sides of the
 * test is what this spelling gives. */
#define ABS(x) ((x) < 0.0f ? -(x) : (x))

#endif
