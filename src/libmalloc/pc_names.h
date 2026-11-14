/* The PC port's names for GNU malloc's (this project's file, not GNU
   malloc's; see README.md).

   gmalloc.c is kept as it came, so the port can't rename its symbols in the
   file.  Built for a host, `malloc`, `free`, `realloc`, `__malloc_hook` and
   the rest would clash with the host C library's, and the game's heap must
   stay Hudson's allocator (a deterministic layout, docs/NETPLAY.md).  The
   port force-includes this header (`-include src/libmalloc/pc_names.h`)
   when it compiles gmalloc.c and the game's C that calls the allocator, so
   both use the bm64_ names.  The four helpers gmalloc.c calls (sbrk,
   memmove, memcpy, memset) are the game's (40300.c): they are not renamed
   here, which would reach the host's headers in every file, but mapped for
   gmalloc.c alone with -D, as the N64 build does (Makefile).  It does
   nothing outside TARGET_PC. */
#ifndef LIBMALLOC_PC_NAMES_H
#define LIBMALLOC_PC_NAMES_H
#ifdef TARGET_PC

#define malloc                   bm64_malloc
#define free                     bm64_free
#define realloc                  bm64_realloc
#define calloc                   bm64_calloc
#define cfree                    bm64_cfree
#define valloc                   bm64_valloc
#define memalign                 bm64_memalign
#define _malloc                  bm64__malloc
#define _free                    bm64__free
#define _realloc                 bm64__realloc
#define _free_internal           bm64__free_internal
#define __default_morecore       bm64___default_morecore
#define __morecore               bm64___morecore
#define _aligned_blocks          bm64__aligned_blocks
#define _heapbase                bm64__heapbase
#define _heapinfo                bm64__heapinfo
#define _heapindex               bm64__heapindex
#define _heaplimit               bm64__heaplimit
#define _fraghead                bm64__fraghead
#define _chunks_used             bm64__chunks_used
#define _bytes_used              bm64__bytes_used
#define _chunks_free             bm64__chunks_free
#define _bytes_free              bm64__bytes_free
#define __after_morecore_hook    bm64___after_morecore_hook
#define __malloc_initialized     bm64___malloc_initialized
#define __malloc_initialize_hook bm64___malloc_initialize_hook
#define __free_hook              bm64___free_hook
#define __malloc_hook            bm64___malloc_hook
#define __realloc_hook           bm64___realloc_hook
#define __memalign_hook          bm64___memalign_hook

#endif /* TARGET_PC */
#endif /* LIBMALLOC_PC_NAMES_H */
