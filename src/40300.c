#include "common.h"

extern u8 *D_8029F5A0;
extern u8 D_80300000[];
extern s32 __malloc_initialized;

void *func_80225B00(s32 size) {
    u8 *p = D_8029F5A0;

    D_8029F5A0 += size;
    if (D_8029F5A0 - D_80300000 >= 0x100000) {
        return (void *)-1;
    }
    return p;
}

char *func_80225B40(char *dst, char *src) {
    char *ret = dst;

    while (*dst != '\0') {
        dst++;
    }
    while ((*dst++ = *src++) != '\0') {
    }
    return ret;
}

s32 func_80225B90(char *str) {
    s32 len = 0;
    char *p = str;

    while (*p != '\0') {
        len++;
        p++;
    }
    return len;
}

void *func_80225BB8(void *dst, void *src, s32 n) {
    u8 *d = dst;
    u8 *s = src;

    if (n != 0 && dst != src) {
        if (s < d && d < s + n) {
            while (n--) {
                *(n + d) = s[n]; /* n + d: IDO adds in that order */
            }
        } else {
            while (n--) {
                *d++ = *s++;
            }
        }
    }
    return dst;
}

void *func_80225C44(void *dst, void *src, s32 n) {
    u8 *d = dst;
    u8 *s = src;

    while (n--) {
        *d++ = *s++;
    }
    return dst;
}

void *func_80225C7C(void *dst, s32 c, s32 n) {
    u8 *d = dst;

    while (n--) {
        *d++ = c;
    }
    return dst;
}

void func_80225CA8(void) {
    __malloc_initialized = 0;
}
