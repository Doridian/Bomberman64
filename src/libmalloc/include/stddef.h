/* Stub for gmalloc.c (this project's, not GNU malloc's): IDO would read the
   host's <stddef.h>.  See ../README.md. */
#ifndef _STUB_STDDEF
#define _STUB_STDDEF
#ifdef TARGET_PC
/* the host's widths: a host's pointers can be 64 bits */
typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#else
typedef unsigned int size_t;
typedef int ptrdiff_t;
#endif
#ifndef NULL
#define NULL 0
#endif
#endif
