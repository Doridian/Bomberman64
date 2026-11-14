/* Stub for gmalloc.c (this project's, not GNU malloc's).  The Makefile maps
   these names to the game's own helpers in 40300.c.  See ../README.md. */
#include <stddef.h>
extern void *memcpy(void *, const void *, size_t);
extern void *memset(void *, int, size_t);
extern void *memmove(void *, const void *, size_t);
