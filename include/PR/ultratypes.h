#ifndef _ULTRATYPES_H_
#define _ULTRATYPES_H_

/*
 * The fixed-size types of the N64 SDK's <PR/ultratypes.h>.  IDO's long is
 * 32 bits; the port (TARGET_PC) uses int, whatever the host's long is.
 */

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) || defined(TARGET_PC)

#ifdef TARGET_PC
typedef unsigned int u32;
typedef int s32;
typedef volatile unsigned int vu32;
typedef volatile int vs32;
#else
typedef unsigned long u32;
typedef long s32;
typedef volatile unsigned long vu32;
typedef volatile long vs32;
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

typedef signed char s8;
typedef short s16;
typedef long long s64;

typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long long vu64;

typedef volatile signed char vs8;
typedef volatile short vs16;
typedef volatile long long vs64;

typedef float f32;
typedef double f64;

#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#endif
