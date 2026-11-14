#include "common.h"

/*
 * -O3, so written last function first. Five functions (us
 * 0x8022DB00-0x8022DE00): func_8022DB00 and two tasks that draw screen
 * rectangles. 48600 (src/48600.c) is a separate object:
 * func_80232E60 calls func_8022DB00 with a jal, where one -O3 file inlines
 * it (text_objects.txt).
 */

/* A screen rectangle (0x40 bytes from func_8022A6C4). */
typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ f32 x0;
    /* 0x14 */ f32 y0;
    /* 0x18 */ f32 x1;
    /* 0x1C */ f32 y1;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} Rect40;

s32 func_80238A10(void *, s32, s32, s32, s32);
void func_8023903C(s32);
void func_80239094(void);
s32 func_802391F0(void);
void func_80239430(void);
s32 *func_8023A840(void);
void func_8026C454(s32, f32, f32, f32);
s32 func_8026C51C(s32, f32, f32, f32);

extern Rect40 *D_800A7F08[8];
extern u8 D_8029FD40[];

void func_8022DB00(void);
static void func_8022DB28(void);
void func_8022DBBC(s32 arg0);
static void func_8022DBF4(Rect40 **arg0, f32 arg1, f32 arg2, s32 *arg3, s32 arg4);
static void func_8022DD6C(void);
void func_8022DDB4(s32 arg0);

void func_8022DDB4(s32 arg0) {
    if (!(*func_8023A840() & 2)) {
        func_80238A10(func_8022DD6C, arg0, 0, 0, 0x150);
    }
}

static void func_8022DD6C() {
    func_8022DBF4(D_800A7F08, 291.0f, 56.0f, (s32 *)(func_802391F0()), 0);
    func_80239430();
}

static void func_8022DBF4(Rect40 **arg0, f32 arg1, f32 arg2, s32 *arg3, s32 arg4) {
    Rect40 *r;
    s32 cur;
    s32 tgt;
    s32 n;
    f32 f;

    r = *arg0;
    cur = 0;
    while (TRUE) {
        n = *arg3 - arg4;
        if (n < 0) {
            n = 0;
        }
        if (n < 3) {
            tgt = n * 4;
        } else {
            tgt = 8;
        }
        if (cur == tgt && n == 0) {
            break;
        }
        if (cur == tgt && n >= 3) {
            func_8022DBF4(arg0 + 1, arg1, arg2 + 16.0f + 4.0f, arg3, arg4 + 2);
        }
        if (cur < tgt) {
            cur++;
        } else if (tgt < cur) {
            cur--;
        }
        f = cur;
        r->x0 = arg1 - f;
        r->y0 = arg2 - f;
        r->x1 = f + arg1;
        r->y1 = f + arg2;
        func_8023903C(2);
    }
}

void func_8022DBBC(s32 arg0) {
    func_80238A10(func_8022DB28, arg0, 0, 0, 0x150);
}

static void func_8022DB28() {
    s32 *args;
    Rect40 *r;
    s32 id;
    s32 n;
    s32 i;

    args = (s32 *) func_802391F0();
    r = (Rect40 *) args[0];
    id = args[1];
    n = args[2];
    id = func_8026C51C(id, r->x0, r->y0, r->x1);
    for (i = 0; i < n; i++) {
        func_8026C454(id, r->x0, r->y0, r->x1);
        func_80239094();
    }
    func_80239430();
}

void func_8022DB00(void) {
    func_80297D30(0x18, D_8029FD40);
}
