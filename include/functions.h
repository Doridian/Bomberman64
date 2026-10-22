#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* Prototypes of the game's functions that C calls across files.  Names
 * are us's func_XXXXXXXX (CLAUDE.md, "Don't guess names").  The game's
 * structs are named by their tags here, so that this needs no other
 * header. */

#include "common.h"

struct UnkStruct_80225CC0;

/* 40300 */
void *func_80225C44(void *dst, void *src, s32 n);
void *func_80225C7C(void *dst, s32 c, s32 n);

/* 404C0 */
s32 func_8022616C(u8 *buf, s32 size, s32 count, struct UnkStruct_80225CC0 *file);
void func_80226368(struct UnkStruct_80225CC0 *file);
struct UnkStruct_80225CC0 *func_80226604(u32 id, s32 mode);
u32 func_802266DC(struct UnkStruct_80225CC0 *file);
void func_802266E8(s32 base);

/* 40FB0 */
void func_802267E0(s32 arg0);

/* 87190 */
void *func_8026CE28(s32 id);
void func_8026CCBC(s32 id);

/* not yet C */
void func_8022A1E8(void *);
void *func_8022A6C4(void *, s32);
void func_80292BD0(struct UnkStruct_80225CC0 *file, void *dst, s32 size);

/* B3B70 on: not yet C */
void func_80297D30(s32, void *);
void func_80297D60(void *, s32);
void func_80297DC0(void);
void func_80297EC0(void *dst, s32 size, s32 src);

#endif
