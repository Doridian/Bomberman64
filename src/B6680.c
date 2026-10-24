#include "common.h"

/*
 * RDP render mode and colour combiner set-up from strings, and 4x4 float
 * matrix rotation, scale and translation (angles in degrees), an arctangent.
 * -O3 and -mips2 (after main_code's ZeroJump block): written last function
 * first, as IDO emits them in reverse.
 */

f32 sinf(f32);
f32 fcos(f32);

void func_8029BE80(u32 *gfx, u32 mode);
u32 func_8029BE94(u8 *s);
void func_8029BF30(u32 *gfx, u8 *s, u8 *c1, u8 *c2);
void func_8029C08C(u32 *gfx, u8 *s, u8 *c);
void func_8029C0AC(u32 *gfx, s32 *p);
s32 func_8029C18C(u8 c);
void func_8029C1C4(u32 *gfx, u8 *s1, u8 *s2);
void func_8029C240(u32 *gfx, u8 *s);
void func_8029C2A4(f32 m[4][4], f32 angle);
void func_8029C3A0(f32 m[4][4], f32 angle);
void func_8029C494(f32 m[4][4], f32 angle);
void func_8029C590(f32 m[4][4], f32 r[3][3]);
void func_8029C680(f32 m[4][4], f32 x, f32 y, f32 z);
void func_8029C7A8(f32 m[4][4], f32 x, f32 y, f32 z);
void func_8029C8D0(f32 m[4][4], f32 x, f32 y, f32 z);
void func_8029CA00(f32 m[4][4], f32 x, f32 y, f32 z);
void func_8029CA80(f32 m[4][4], f32 x, f32 y, f32 z);
f32 func_8029CB40(f32 x);

f32 func_8029CB40(f32 x) {
    s32 sign;
    s32 i;
    f32 t;

    if (x > 1.0f) {
        sign = 1;
        x = 1.0f / x;
    } else if (x < -1.0f) {
        sign = -1;
        x = 1.0f / x;
    } else {
        sign = 0;
    }
    t = 0.0f;
    for (i = 6; i > 0; i--) {
        t = (i * i) * x * x / ((2 * i + 1) + t);
    }
    if (sign > 0) {
        return 1.5707963267948966 - x / (1.0f + t);
    } else if (sign < 0) {
        return -1.5707963267948966 - x / (1.0f + t);
    }
    return x / (1.0f + t);
}

void func_8029CA80(f32 m[4][4], f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 0; i < 4; i++) {
        m[3][i] += m[0][i] * x + m[1][i] * y + m[2][i] * z;
    }
}

void func_8029CA00(f32 m[4][4], f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 0; i < 3; i++) {
        m[0][i] *= x;
        m[1][i] *= y;
        m[2][i] *= z;
    }
}

void func_8029C8D0(f32 m[4][4], f32 x, f32 y, f32 z) {
    f32 r[3][3];
    f32 sx, sy, sz, cx, cy, cz;
    f32 a, b;

    x *= 0.017453292f;
    y *= 0.017453292f;
    z *= 0.017453292f;
    sx = sinf(x);
    cx = fcos(x);
    sy = sinf(y);
    cy = fcos(y);
    sz = sinf(z);
    cz = fcos(z);
    a = sx * sy;
    b = cx * sy;
    r[0][0] = cy * cz;
    r[0][1] = cy * sz;
    r[0][2] = -sy;
    r[1][0] = a * cz - cx * sz;
    r[1][1] = a * sz + cx * cz;
    r[1][2] = sx * cy;
    r[2][0] = b * cz + sx * sz;
    r[2][1] = b * sz - sx * cz;
    r[2][2] = cx * cy;
    func_8029C590(m, r);
}

void func_8029C7A8(f32 m[4][4], f32 x, f32 y, f32 z) {
    f32 r[3][3];
    f32 sx, sy, sz, cx, cy, cz;
    f32 a, b, c, d;

    x *= 0.017453292f;
    y *= 0.017453292f;
    z *= 0.017453292f;
    sx = sinf(x);
    cx = fcos(x);
    sy = sinf(y);
    cy = fcos(y);
    sz = sinf(z);
    cz = fcos(z);
    b = cy * cz;
    a = sx * sy;
    c = cy * sz;
    d = sy * cz;
    r[0][0] = b - a * sz;
    r[0][1] = a * cz + c;
    r[0][2] = -(cx * sy);
    r[1][0] = -(cx * sz);
    r[1][1] = cx * cz;
    r[1][2] = sx;
    r[2][0] = sx * c + d;
    r[2][1] = sy * sz - sx * b;
    r[2][2] = cx * cy;
    func_8029C590(m, r);
}

void func_8029C680(f32 m[4][4], f32 x, f32 y, f32 z) {
    f32 r[3][3];
    f32 sx, sy, sz, cx, cy, cz;
    f32 a, b, c, d;

    x *= 0.017453292f;
    y *= 0.017453292f;
    z *= 0.017453292f;
    sx = sinf(x);
    cx = fcos(x);
    sy = sinf(y);
    cy = fcos(y);
    sz = sinf(z);
    cz = fcos(z);
    b = cy * cz;
    a = sx * sy;
    c = cy * sz;
    d = sy * cz;
    r[0][0] = a * sz + b;
    r[0][1] = cx * sz;
    r[0][2] = sx * c - d;
    r[1][0] = a * cz - c;
    r[1][1] = cx * cz;
    r[1][2] = sx * b + sy * sz;
    r[2][0] = cx * sy;
    r[2][1] = -sx;
    r[2][2] = cx * cy;
    func_8029C590(m, r);
}

void func_8029C590(f32 m[4][4], f32 r[3][3]) {
    s32 i;
    s32 j;
    s32 k;
    f32 tmp[3][3];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            tmp[i][j] = 0.0f;
            for (k = 0; k < 3; k++) {
                tmp[i][j] += r[i][k] * m[k][j];
            }
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m[i][j] = tmp[i][j];
        }
    }
}

void func_8029C494(f32 m[4][4], f32 angle) {
    f32 t;
    f32 s;
    f32 c;
    s32 i;
    f32 tmp[3];

    t = angle * 0.017453292f;
    tmp[0] = t;
    s = sinf(tmp[0]);
    c = fcos(tmp[0]);
    for (i = 0; i < 3; i++) {
        tmp[i] = m[1][i];
    }
    for (i = 0; i < 3; i++) {
        m[1][i] = tmp[i] * c + m[2][i] * s;
        m[2][i] = -tmp[i] * s + m[2][i] * c;
    }
}

void func_8029C3A0(f32 m[4][4], f32 angle) {
    f32 t;
    f32 s;
    f32 c;
    s32 i;
    f32 tmp[3];

    t = angle * 0.017453292f;
    tmp[0] = t;
    s = sinf(tmp[0]);
    c = fcos(tmp[0]);
    for (i = 0; i < 3; i++) {
        tmp[i] = m[0][i];
    }
    for (i = 0; i < 3; i++) {
        m[0][i] = tmp[i] * c - m[2][i] * s;
        m[2][i] = tmp[i] * s + m[2][i] * c;
    }
}

// The radians pass through tmp[0]: the original spills them into the
// array's first element (as in func_8029C3A0 and func_8029C494).
void func_8029C2A4(f32 m[4][4], f32 angle) {
    f32 t;
    f32 s;
    f32 c;
    s32 i;
    f32 tmp[3];

    t = angle * 0.017453292f;
    tmp[0] = t;
    s = sinf(tmp[0]);
    c = fcos(tmp[0]);
    for (i = 0; i < 3; i++) {
        tmp[i] = m[0][i];
    }
    for (i = 0; i < 3; i++) {
        m[0][i] = tmp[i] * c + m[1][i] * s;
        m[1][i] = -tmp[i] * s + m[1][i] * c;
    }
}

void func_8029C240(u32 *gfx, u8 *s) {
    s32 i;
    s32 p[16];

    for (i = 0; i < 8; i++) {
        p[i] = p[i + 8] = func_8029C18C(s[i]);
    }
    func_8029C0AC(gfx, p);
}

void func_8029C1C4(u32 *gfx, u8 *s1, u8 *s2) {
    s32 i;
    s32 p[16];

    for (i = 0; i < 8; i++) {
        p[i] = func_8029C18C(s1[i]);
        p[i + 8] = func_8029C18C(s2[i]);
    }
    func_8029C0AC(gfx, p);
}

s32 func_8029C18C(u8 c) {
    if (c >= 'a') {
        c -= 0x20;
    }
    if (c >= 'A') {
        return c - 'A' + 10;
    }
    return c - '0';
}

// gDPSetCombineLERP's words from 16 inputs (RGB a, b, c, d and alpha a, b,
// c, d per cycle); only the RGB inputs are masked.  The first word's terms
// match only in this order.
void func_8029C0AC(u32 *gfx, s32 *p) {
    u32 w;

    w = ((p[2] & 0x1F) << 15) | (p[4] << 12) | (p[6] << 9) | ((p[0] & 0xF) << 20);
    w |= 0xFC000000;
    w |= ((p[8] & 0xF) << 5) | (p[10] & 0x1F);
    gfx[0] = w;
    w = ((p[1] & 0xF) << 28) | ((p[3] & 7) << 15) | (p[5] << 12) | (p[7] << 9);
    w |= ((p[9] & 0xF) << 24) | (p[12] << 21) | (p[14] << 18) | ((p[11] & 7) << 6) | (p[13] << 3) | p[15];
    gfx[1] = w;
}

void func_8029C08C(u32 *gfx, u8 *s, u8 *c) {
    func_8029BF30(gfx, s, c, c);
}

// Render mode flags from a string of '0'/'1' (and '0'-'3' for the two
// two-bit fields), the blender settings from two more (func_8029BE94).
void func_8029BF30(u32 *gfx, u8 *s, u8 *c1, u8 *c2) {
    u32 v = 0;
    u32 b;
    u8 *p;

    p = s;
    if (*p++ == '1') v |= 0x8;
    if (*p++ == '1') v |= 0x10;
    if (*p++ == '1') v |= 0x20;
    if (*p++ == '1') v |= 0x40;
    if (*p++ == '1') v |= 0x80;
    if (*p >= '0' && *p <= '3') v |= (*p - '0') << 8;
    p++;
    if (*p >= '0' && *p <= '3') v |= (*p - '0') << 10;
    p++;
    if (*p++ == '1') v |= 0x1000;
    if (*p++ == '1') v |= 0x2000;
    if (*p++ == '1') v |= 0x4000;
    if (*p++ == '1') v |= 0; /* TEX_EDGE, 0 (it was 0x8000) */
    b = func_8029BE94(c1);
    b |= func_8029BE94(c2) >> 2;
    func_8029BE80(gfx, v | b);
}

u32 func_8029BE94(u8 *s) {
    u32 v = 0;

    if (*s >= '0' && *s <= '3') {
        v |= (*s - '0') << 30;
    }
    s++;
    if (*s >= '0' && *s <= '3') {
        v |= (*s - '0') << 26;
    }
    s++;
    if (*s >= '0' && *s <= '3') {
        v |= (*s - '0') << 22;
    }
    s++;
    if (*s >= '0' && *s <= '3') {
        v |= (*s - '0') << 18;
    }
    return v;
}

void func_8029BE80(u32 *gfx, u32 mode) {
    gfx[0] = 0xB900031D;
    gfx[1] = mode;
}
