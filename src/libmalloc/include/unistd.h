/* Stub for gmalloc.c (this project's, not GNU malloc's), for the PC port
   only: it compiles gmalloc.c with -DHAVE_UNISTD_H so that sbrk has a
   prototype in __default_morecore (an implicit `int` would cut its pointer
   to 32 bits on a 64-bit host).  The N64 build doesn't define
   HAVE_UNISTD_H.  sbrk is the game's func_80225B00 (40300.c), by -D as in
   the Makefile.  See ../README.md. */
#ifndef _STUB_UNISTD
#define _STUB_UNISTD
void *sbrk(int increment);
#endif
