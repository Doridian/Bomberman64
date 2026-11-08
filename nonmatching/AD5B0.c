/*
 * NON_MATCHING: main_code's AD5B0, complete: the EEPROM save (header,
 * three slots, the format, load, store and checks). Every function is
 * emitted in the original's order, with the original's stubs for the
 * inlined statics. Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 70, eu 70, jp 70
 *
 * p4 (665 -> 70): only func_80292DB0's range (DB8 and E90) is left;
 * func_802934E8 and func_8029414C match.
 * - func_802934E8 was one word long (a load-delay nop in D8); most of its
 *   529 words were the shift. D8 and D0 interleave the checksum with the
 *   ors (sum = *p++; *out |= *p; ...), which hoists the sum's lbu above
 *   the or/sw. D0 is defined before 34E8 (lower .loc lines put li a0,2 in
 *   the jal delay slot). The last or of D0 and the first of D8 read
 *   (u8)(x << 0): it burns one ugen temp so the t-register rotation lines
 *   up (plain, & 0xFF and other casts are a register behind or change
 *   414C). The 8-byte copy loop is sum += *p; *q++ = *p++; (addu before
 *   sb). Frame: s32 pad[8] in D8 puts E0's i at sp+0x5C and pad2[6] in E0
 *   (after its locals) makes the frame 0x128.
 * - 33E8 and 4064 take their pointer arguments first ((pp, a, b) and
 *   (pp, chk, a, b)): IPA keeps their registers, and ugen's argument order
 *   then puts the pointer moves first in the second call of each loop.
 * - 414C's for line gets a #line one below the *p++ = ...(chk, 6) line
 *   (then a #line back to the real numbering), so the loop's init is
 *   scheduled before the sw of p and chk. Both are absolute: renumber
 *   them when lines above move.
 * - DB8: the original keeps the guard on retry (li v0,1; beqz v0) before
 *   the loop preheader. Any form where uopt knows retry == 1 folds it
 *   (while, goto, for/do variants, retry from i or ret, narrow types, a
 *   late assignment, retry = 0 instead of break). Passing retry as a
 *   parameter (1 from every caller) gives the exact structure (guard
 *   before the preheader), but it lives in s0 and the callers get worse.
 *   The kept form is for (;;) { if (!retry) break; ... } with retry = 1
 *   just before: the guard stays but the preheader (s1, s5) comes before
 *   it and the exit takes an extra move v0,s2 (one word long).
 * - E90: declaring i first gives its spill slot 92. The original copies
 *   ret to v1 after both calls (move v1,v0; bnez v1); ours tests v0, one
 *   word short, so DB8 and E90 cancel in size and E90 is shifted. ret
 *   with a later use (return ret, if (ret) {} after the loop) gets its own
 *   register but lives across the E88 call; u16 ret gives a per-branch
 *   register with an andi.
 *
 * p3 (1112 -> 665): func_80292DB0's range, func_802934E8 and
 * func_8029414C are left; everything else matches.
 * - func_80292DB8: the original keeps the retry loop's constant top test
 *   (li v0,1; beqz v0). A goto form keeps it, but retry lands in s1 and
 *   the callers get worse.
 * - func_80292E90: the original keeps ret in v1 after both calls; its
 *   spill slot is 92 against our 88.
 * - func_802934E8: frame 0x128 against our 0xF0 (56 bytes short); E0's
 *   i is spilled at sp+92 in the original and sp+68 in ours. In D0,
 *   *out |= p[0] & 0xFF (or p[1] & 0xFF) gives the original's lbu-before-
 *   or schedule (nd 24 -> 21), but it makes 4144's loop reload *pp in
 *   414C (+300 words), so it isn't used.
 * - func_8029414C: the sw of p/chk after the first 3EAC call comes after
 *   the loop's init in the original; the second loop call's arguments go
 *   s2, s1, a0, s3 in the original and a0, s3, s2, s1 in ours.
 */
#include "common.h"

/* The EEPROM save: a 0x1B8-byte image (D_80063000), an 8-byte header
 * ("BAKU", the revision, the option flags, "Hu", a checksum) and three
 * 0x90-byte slots of 18 blocks each; the game's flags and counters
 * (func_8028A060's table, func_8028A36C's bits) are packed into a slot in
 * checksummed chunks. */

s32 *func_8028A060(s32);
s32 func_8028A36C(s32);
void func_8028A3D0(s32);
void func_8028A428(s32);
void func_80239094(void);
s32 func_80297D40(char *, const char *, ...);
void func_80297D50(void *, s32);
s32 func_80297E60(void *);
s32 func_80297E68(void *, u8, u8 *);
s32 func_80297E70(void *, u8, u8 *);
s32 func_80297E78(void *, u8, u8 *, s32);
s32 func_80297E80(void *, u8, u8 *, s32);

static s32 func_80294A40(s32 slot);
static s32 func_802949BC(u8 b);
static s32 func_802948A0(u8 *p);
static void func_80294144(u8 **pp, u8 *src);
static void func_8029413C(u8 **pp, u16 v);
static void func_80294134(u8 **pp, u32 v);
static void func_80294064(u8 **pp, u8 **chk, s32 a, s32 b);
static void func_80294040(u8 **pp, u32 v);
static u8 func_80293FE4(s32 base);
static u8 func_80293F90(s32 base);
static u8 func_80293F34(s32 base);
static u8 func_80293EAC(u8 *buf, s32 n);
static s32 func_802934E0(u8 **pp);
static u8 func_802934D8(u8 **pp, s32 *out);
static u8 func_802934D0(u8 **pp, s32 *out);
static s32 func_802933E8(u8 **pp, s32 a, s32 b);
static u8 func_80293378(u8 **pp, s32 *out);
static void func_80293314(u8 bits, s32 base);
static void func_802932B0(u8 bits, s32 base);
static void func_8029324C(u8 bits, s32 base);
static s32 func_80292E90(u8 addr, u8 *buf, u8 n);
static s32 func_80294DB8(void);
static s32 func_80292E88(u8 addr, u8 n);
static s32 func_80292DB0(u8 *a, u8 *b, u8 n);
static s32 func_80292E80(u8 addr, u8 *buf, u8 n);
static s32 func_80292DB8(u8 addr, u8 *buf, u8 n);

extern u8 D_80063000[];
extern u8 D_800631B8[];
extern s32 D_80063004;
extern u8 D_802AC3E0[];

#define SLOT(i) (&D_80063000[(i) * 0x90 + 8])

s32 func_80294D34(u8 *hdr);
s32 func_80294CE8(s32 i);
s32 func_80294CA0(s32 i);
void func_8029414C(u8 *buf);
s32 func_802934E8(u8 *buf);
void func_802930F8(u8 *buf, s32 kind);
s32 func_80294E54(void);
s32 func_802952CC(u8 *buf);
s32 func_8029522C(s32 slot, u8 *buf);
s32 func_80294A48(s32 slot, u32 kind);
s32 func_802947AC(void);
void func_80293EA0(s32 slot);
void func_80293E5C(s32 kind);
s32 func_80293E1C(void);
s32 func_8029301C(void);
s32 func_80295330(s32 i);
s32 func_80294DC0(void);

s32 D_802A1DA0 = 0;
s32 D_802A1DA4 = 0;
s32 D_802A1DA8 = 0;
s32 D_802A1DAC = 0;
s32 D_802A1DB0 = 0;
s32 D_802A1DB4 = -1;
s32 D_802A1DB8 = 0;
void *D_802A1DBC[] = {
    func_80294D34, func_80294CE8, func_80294CA0, func_8029414C, func_802934E8, func_802930F8,
    func_80294E54, func_802952CC, func_8029522C, func_80294A48, func_802947AC, func_80293EA0,
    func_80293E5C, func_80293E1C, func_8029301C, func_80295330, func_80294DC0,
};

void func_802953E0(void) {
}

static void func_802953A8(void) {
    func_80297D30(0x2F, D_802A1DBC);
}

void func_802953B0(void) {
    func_802953A8();
    D_802A1DB4 = -1;
}


void func_80295384(void) {
    func_80294D34(D_80063000);
}

s32 func_80295330(s32 i) {
    switch (i) {
        case 0:
            return D_802A1DA8;
        case 1:
            return D_802A1DAC;
        case 2:
            return D_802A1DB0;
    }
    return 0;
}

s32 func_802952CC(u8 *buf) {
    return func_80292DB8(0, buf, 1);
}

s32 func_8029522C(s32 slot, u8 *buf) {
    u8 addr;

    switch (slot) {
        case 0:
            addr = 1;
            break;
        case 1:
            addr = 0x13;
            break;
        case 2:
            addr = 0x25;
            break;
    }
    return func_80292DB8(addr, buf, 0x12);
}

s32 func_802951B8(u8 addr, u8 *buf, u8 n) {
    return func_80292E90(addr, buf, n);
}

static s32 func_80294DB8(void) {
    func_80294CA0(0);
    func_80294CA0(1);
    func_80294CA0(2);
    func_80294D34(D_80063000);
    func_802930F8(SLOT(0), 10);
    func_802930F8(SLOT(1), 10);
    func_802930F8(SLOT(2), 10);
    D_802A1DB4 = -1;
    if (func_8029301C() != 0) {
        return -1;
    }
    D_802A1DA0 = 0;
    return 0;
}

s32 func_80294DC0(void) {
    return func_80294DB8();
}

s32 func_80294E54(void) {
    s32 i;
    s32 r;

    D_802A1DB8 = 0;
    D_802A1DA0 = 0;
    D_802A1DA4 = func_80297E60(D_802AC3E0);
    if (D_802A1DA4 == 0) {
        func_80294DC0();
        return -1;
    }
    if (func_80292DB8(0, D_80063000, 0x37) != 0) {
        func_80294DC0();
        return -1;
    }
    if (*(s32 *) D_80063000 != 0x42414B55 || (D_80063004 & 0xFFFF00) != 0x487500) {
        if (func_80294DC0() != 0) {
            return -1;
        }
        return 0;
    }
    if ((D_80063000[4] & 0x1F) != 2) {
        D_802A1DA0 = 1;
        return -2;
    }
    for (i = 0; i < 3; i++) {
        r = func_802934E8(SLOT(i));
        if (r != 2 && r != 0) {
            func_802930F8(SLOT(i), 10);
            D_802A1DB4 = i;
            func_8029301C();
        }
    }
    if (D_80063000[4] & 0x80) {
        func_80294CE8(2);
    } else {
        func_80294CA0(2);
    }
    if (D_80063000[4] & 0x40) {
        func_80294CE8(1);
    } else {
        func_80294CA0(1);
    }
    if (D_80063000[4] & 0x20) {
        func_80294CE8(0);
    } else {
        func_80294CA0(0);
    }
    return 1;
}

s32 func_80294D34(u8 *hdr) {
    D_802A1DB8 = 1;
    *(s32 *) hdr = 0x42414B55;
    hdr[4] = (D_802A1DB0 << 7) | (D_802A1DAC << 6) | (D_802A1DA8 << 5) | 2;
    hdr[5] = 0x48;
    hdr[6] = 0x75;
    hdr[7] = func_80293EAC(hdr, 7);
}

s32 func_80294CE8(s32 i) {
    switch (i) {
        case 0:
            D_802A1DA8 = 1;
            break;
        case 1:
            D_802A1DAC = 1;
            break;
        case 2:
            D_802A1DB0 = 1;
            break;
    }
}

s32 func_80294CA0(s32 i) {
    switch (i) {
        case 0:
            D_802A1DA8 = 0;
            break;
        case 1:
            D_802A1DAC = 0;
            break;
        case 2:
            D_802A1DB0 = 0;
            break;
    }
}

s32 func_80294A48(s32 slot, u32 kind) {
    u8 *s;
    s32 ret = 0;

    switch (kind) {
        case 0:
            s = (u8 *) ((uintptr_t) D_80063000 + (slot * 0x90 + 8));
            if (s[4] & 0x80) {
                if (s[6] & 0x80) {
                    ret = 1;
                }
            } else {
                ret = 10;
            }
            break;
        case 1:
            ret = func_80294A40(slot);
            break;
        case 2:
            ret = func_802948A0(&D_80063000[slot * 0x90 + 0x20]);
            break;
        case 3:
            ret = func_802948A0(&D_80063000[slot * 0x90 + 0x30]);
            break;
        case 4:
            ret = func_802948A0(&D_80063000[slot * 0x90 + 0x40]);
            break;
        case 5:
            ret = func_802948A0(&D_80063000[slot * 0x90 + 0x50]);
            break;
        case 6:
            ret = func_802948A0(&D_80063000[slot * 0x90 + 0x60]);
            break;
        case 7:
            ret = func_802948A0(&D_80063000[slot * 0x90 + 0x70]);
            break;
        case 8:
            if (func_80294A48(slot, 0) != 10) {
                ret = (s32) &D_80063000[slot * 0x90 + 0x10];
            }
            break;
    }
    return ret;
}

static s32 func_80294A40(s32 slot) {
    s32 n = 0;
    u8 *p = &D_80063000[slot * 0x90 + 0x82];
    s32 i;

    for (i = 0; i < 5; i++) {
        n += func_802949BC(*p++);
    }
    p++;
    for (i = 0; i < 7; i++) {
        n += func_802949BC(*p++);
    }
    p++;
    for (i = 0; i != 3; i++) {
        n += func_802949BC(*p++);
    }
    return n;
}

static s32 func_802949BC(u8 b) {
    s32 n = 0;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (b & (1 << i)) {
            n++;
        }
    }
    return n;
}

static s32 func_802948A0(u8 *p) {
    s32 ret = 0;

    if ((p[14] & 0x38) || p[11] || p[12] || p[13]) {
        ret = 4;
    } else if ((p[14] & 7) || p[8] || p[9] || p[10]) {
        ret = 3;
    } else if ((p[6] & 0x38) || p[3] || p[4] || p[5]) {
        ret = 2;
    } else if ((p[6] & 7) || p[0] || p[1] || p[2]) {
        ret = 1;
    }
    return ret;
}

s32 func_802947AC(void) {
    u8 *slot = SLOT(D_802A1DB4);
    s32 ret = 0;

    func_8029414C(slot);
    if (D_802A1DB8) {
        D_802A1DB8 = 0;
        ret = func_80292E90(0, D_80063000, 1);
    }
    if (ret == 0) {
        ret = func_80292E90(D_802A1DB4 * 18 + 1, slot, 0x12);
    }
    return ret;
}

static void func_80294134(u8 **pp, u32 v) {
    u8 *p = *pp;

    *p++ = (v >> 24) & 0xFF;
    *p++ = (v >> 16) & 0xFF;
    *p++ = (v >> 8) & 0xFF;
    *p++ = v & 0xFF;
    *pp = p;
}

static void func_8029413C(u8 **pp, u16 v) {
    u8 *p = *pp;

    *p++ = (v >> 8) & 0xFF;
    *p++ = v & 0xFF;
    *pp = p;
}

void func_8029414C(u8 *buf) {
    u8 *chk = buf;
    u8 *p = buf;
    s32 *x;
    s32 i;
    s32 j;
    s32 k;

    func_80294134(&p, *func_8028A060(1));
    func_8029413C(&p, (*func_8028A060(2) & 0x3FF) | 0x8000);
    x = func_8028A060(4);
    *p++ = (*func_8028A060(3) << 7) | (*x & 0x7F);
    *p++ = func_80293EAC(chk, 7);
    chk += 8;
    func_80294144(&p, (u8 *) func_8028A060(12));
    *p++ = func_80293EAC(chk, 8);
    chk += 9;
    *p = *func_8028A060(5) & 0x7F;
    if (func_8028A36C(0xA4)) {
        *p |= 0x80;
    }
    p++;
    *p++ = *func_8028A060(6) & 0x7F;
    x = func_8028A060(8);
    *p++ = ((*func_8028A060(9) & 0xF) << 4) | (*x & 0xF);
    x = func_8028A060(10);
    *p++ = ((*func_8028A060(11) & 0xF) << 4) | (*x & 0xF);
    *p++ = func_80293FE4(0);
    *p++ = func_80293FE4(0xB);
    *p++ = func_80293EAC(chk, 6);
    chk += 7;
#line 461
    for (k = 0, i = 0; i < 6; i++, k += 4) {
#line 467
        j = k + 0x15;
        do {} while (0);
        func_80294064(&p, &chk, j, j + 1);
        func_80294064(&p, &chk, j + 2, j + 3);
    }
    *p++ = func_80293FE4(0x16);
    *p++ = func_80293FE4(0x21);
    *p++ = func_80293F90(0x2C);
    *p++ = func_80293F90(0x34);
    *p++ = func_80293F90(0x3C);
    *p++ = func_80293F90(0x44);
    *p++ = func_80293F90(0x4C);
    *p++ = func_80293EAC(chk, 7);
    chk += 8;
    *p++ = func_80293F90(0x54);
    *p++ = func_80293F90(0x5C);
    *p++ = func_80293F90(0x64);
    *p++ = func_80293F90(0x6C);
    *p++ = func_80293F90(0x74);
    *p++ = func_80293F90(0x7C);
    *p++ = func_80293F90(0x84);
    *p++ = func_80293EAC(chk, 7);
    chk += 8;
    *p++ = func_80293F90(0x8C);
    *p++ = func_80293F90(0x94);
    *p++ = func_80293F90(0x9C);
    *p++ = func_80293F34(7);
    *p++ = func_80293F34(0x12);
    *p++ = func_80293F34(0x1D);
    *p++ = func_80293F34(0x28);
    *p = func_80293EAC(chk, 7);
}

static void func_80294144(u8 **pp, u8 *src) {
    s32 i;

    for (i = 0; i < 8; i++) {
        *(*pp)++ = src[0];
        src++;
    }
}

static void func_80294064(u8 **pp, u8 **chk, s32 a, s32 b) {
    s32 *x = func_8028A060(a);
    s32 *y = func_8028A060(b);
    u8 *q = *pp;

    func_80294040(&q, *x);
    func_80294040(&q, *y);
    *q = (((*y >> 24) & 7) << 3) | ((*x >> 24) & 7);
    q++;
    *q = func_80293EAC(*chk, 7);
    q++;
    *chk += 8;
    *pp = q;
}

static void func_80294040(u8 **pp, u32 v) {
    u8 *p = *pp;

    p[0] = (v >> 16) & 0xFF;
    p[1] = (v >> 8) & 0xFF;
    p[2] = v & 0xFF;
    p += 3;
    *pp = p;
}

static u8 func_80293FE4(s32 base) {
    u8 bits = 0;
    s32 i;

    for (i = 1; i < 7; i++) {
        if (func_8028A36C(base + i)) {
            bits |= 1 << i;
        }
    }
    return bits | 0x80;
}

static u8 func_80293F90(s32 base) {
    u8 bits = 0;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (func_8028A36C(base + i)) {
            bits |= 1 << i;
        }
    }
    return bits;
}

static u8 func_80293F34(s32 base) {
    u8 bits = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_8028A36C(base + i)) {
            bits |= 1 << i;
        }
    }
    return bits | 0xF0;
}

static u8 func_80293EAC(u8 *buf, s32 n) {
    u8 *p = buf;
    u8 sum = 0;
    s32 i;

    for (i = 0; i < n; i++) {
        sum += *p++;
    }
    return 0xFF - sum;
}

void func_80293EA0(s32 slot) {
    D_802A1DB4 = slot;
}

void func_80293E5C(s32 kind) {
    func_802930F8(SLOT(D_802A1DB4), kind);
}

s32 func_80293E1C(void) {
    return func_802934E8(SLOT(D_802A1DB4));
}

static u8 func_802934D0(u8 **pp, s32 *out) {
    u8 *p = *pp;
    u8 sum;

    *out = (p[0] << 24) & 0xFF000000;
    sum = *p++;
    *out |= (p[0] << 16) & 0xFF0000;
    sum += *p++;
    *out |= (p[0] << 8) & 0xFF00;
    sum += *p++;
    *out |= (u8)(p[0] << 0);
    sum += *p++;
    *pp = p;
    return sum;
}

s32 func_802934E8(u8 *buf) {
    s32 r;
    u8 *p;
    s32 *v;
    char msg[0x58];
    s32 *w;
    u8 sum;
    s32 i;
    u8 *q;

    p = buf;
    while (D_802A1DA0) {
        func_80297D40(msg, "EEPROM : SAVE DATA REVISION ERROR. PLEASE FORMAT EEPROM. REVISION=%d", D_80063000[4] & 0x1F);
        func_80239094();
    }
    if (!D_802A1DA4) {
        func_802930F8(buf, 10);
        return -2;
    }
    sum = func_802934D0(&p, func_8028A060(1));
    v = func_8028A060(2);
    sum += func_802934D8(&p, v);
    if (!(*v & 0x8000)) {
        func_802930F8(buf, 10);
        return 2;
    }
    *v &= 0x3FF;
    v = func_8028A060(4);
    w = func_8028A060(3);
    if (*p & 0x80) {
        *w = 1;
    } else {
        *w = 0;
    }
    *v = *p & 0x7F;
    sum += *p++;
    sum += *p++;
    if (sum != 0xFF) {
        func_802930F8(buf, 10);
        return 1;
    }
    sum = 0;
    q = (u8 *) func_8028A060(12);
    for (i = 0; i < 8; i++) {
        sum += *p;
        *q++ = *p++;
    }
    sum += *p++;
    if (sum != 0xFF) {
        func_802930F8(buf, 10);
        return 1;
    }
    v = func_8028A060(5);
    *v = *p & 0x7F;
    if (*p & 0x80) {
        func_8028A3D0(0xA4);
    } else {
        func_8028A428(0xA4);
    }
    sum = *p++;
    v = func_8028A060(6);
    *v = *p & 0x7F;
    sum += *p++;
    v = func_8028A060(8);
    w = func_8028A060(9);
    *v = *p & 0xF;
    *w = (*p >> 4) & 0xF;
    sum += *p++;
    v = func_8028A060(10);
    w = func_8028A060(11);
    *v = *p & 0xF;
    *w = (*p >> 4) & 0xF;
    sum += *p++;
    func_80293314(*p, 0);
    sum += *p++;
    func_80293314(*p, 0xB);
    sum += *p++;
    sum += *p++;
    if (sum != 0xFF) {
        func_802930F8(buf, 10);
        return 1;
    }
    r = func_802934E0(&p);
    if (r == 1) {
        func_802930F8(buf, 10);
        return 1;
    }
    func_80293314(*p, 0x16);
    sum = *p++;
    func_80293314(*p, 0x21);
    sum += *p++;
    func_802932B0(*p, 0x2C);
    sum += *p++;
    func_802932B0(*p, 0x34);
    sum += *p++;
    func_802932B0(*p, 0x3C);
    sum += *p++;
    func_802932B0(*p, 0x44);
    sum += *p++;
    func_802932B0(*p, 0x4C);
    sum += *p++;
    sum += *p++;
    if (sum != 0xFF) {
        func_802930F8(buf, 10);
        return 1;
    }
    func_802932B0(*p, 0x54);
    sum = *p++;
    func_802932B0(*p, 0x5C);
    sum += *p++;
    func_802932B0(*p, 0x64);
    sum += *p++;
    func_802932B0(*p, 0x6C);
    sum += *p++;
    func_802932B0(*p, 0x74);
    sum += *p++;
    func_802932B0(*p, 0x7C);
    sum += *p++;
    func_802932B0(*p, 0x84);
    sum += *p++;
    sum += *p++;
    if (sum != 0xFF) {
        func_802930F8(buf, 10);
        return 1;
    }
    func_802932B0(*p, 0x8C);
    sum = *p++;
    func_802932B0(*p, 0x94);
    sum += *p++;
    func_802932B0(*p, 0x9C);
    sum += *p++;
    func_8029324C(*p, 7);
    sum += *p++;
    func_8029324C(*p, 0x12);
    sum += *p++;
    func_8029324C(*p, 0x1D);
    sum += *p++;
    func_8029324C(*p, 0x28);
    sum += *p++;
    sum += *p++;
    if (sum != 0xFF) {
        func_802930F8(buf, 10);
        return 1;
    }
    return 0;
}

static s32 func_802934E0(u8 **pp) {
    s32 i;
    s32 j;
    s32 k;
    s32 r;
    s32 pad2[6];

    for (k = 0, i = 0; i < 6; i++, k += 4) {
        j = k + 0x15;
        do {} while (0);
        r = func_802933E8(pp, j, j + 1);
        if (r == 1) {
            break;
        }
        r = func_802933E8(pp, j + 2, j + 3);
        if (r == 1) {
            break;
        }
    }
    return r;
}

static u8 func_802934D8(u8 **pp, s32 *out) {
    s32 pad[8];
    u8 *p = *pp;
    u8 sum;

    *out = (p[0] << 8) & 0xFF00;
    sum = *p++;
    *out |= (u8)(*p << 0);
    sum += *p++;
    *pp = p;
    return sum;
}

static s32 func_802933E8(u8 **pp, s32 a, s32 b) {
    s32 *x = func_8028A060(a);
    s32 *y = func_8028A060(b);
    s32 r;
    u8 *q = *pp;
    u8 sum;

    *x = 0;
    *y = 0;
    sum = func_80293378(&q, x);
    sum += func_80293378(&q, y);
    *y |= (*q & 7) << 21;
    *x |= (*q & 7) << 24;
    sum += *q++;
    sum += *q++;
    if (sum != 0xFF) {
        return 1;
    }
    *pp = q;
    return 0;
}

static u8 func_80293378(u8 **pp, s32 *out) {
    u8 *p = *pp;
    u8 sum;

    do {
    *out |= (p[0] << 16) & 0xFF0000;
    sum = p[0];
    *out |= (p[1] << 8) & 0xFF00;
    sum += p[1];
    *out |= p[2] & 0xFF;
    sum += p[2];
    p += 3;
    *pp = p;
    } while (0);
    return sum;
}

static void func_80293314(u8 bits, s32 base) {
    s32 i;

    for (i = 1; i < 7; i++) {
        if (bits & (1 << i)) {
            func_8028A3D0(base + i);
        } else {
            func_8028A428(base + i);
        }
    }
}

static void func_802932B0(u8 bits, s32 base) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (bits & (1 << i)) {
            func_8028A3D0(base + i);
        } else {
            func_8028A428(base + i);
        }
    }
}

static void func_8029324C(u8 bits, s32 base) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (bits & (1 << i)) {
            func_8028A3D0(base + i);
        } else {
            func_8028A428(base + i);
        }
    }
}

void func_80293244(void) {
}

void func_802930F8(u8 *buf, s32 kind) {
    s32 *w = (s32 *) buf;
    s32 i = 0;

    w[i++] = 0;
    switch (kind) {
        case 0:
            w[i++] = 0x8000007F;
            break;
        case 1:
            w[i++] = 0x800080FF;
            break;
        case 10:
            w[i++] = 0xFF;
            break;
        default:
            w[i++] = 0xFF;
            break;
    }
#if VERSION_JP
    w[i++] = 0x9F5F9BF9;
    w[i++] = 0x7E5F0000;
    w[i++] = 0x90000000;
#else
    w[i++] = 0x1B28261B;
    w[i++] = 0x1E2B0000;
    w[i++] = 0x32000000;
#endif
    w[i++] = 0x8282FB;
    while (i < 30) {
        w[i++] = 0;
        w[i++] = 0xFF;
    }
    w[i++] = 0x82820000; w[i++] = 0xFB;
    w[i++] = 0;
    w[i++] = 0xFF;
    w[i++] = 0xF0; w[i++] = 0xF0F0F03F;
    func_8028A3D0(1);
    func_8028A3D0(12);
    func_8028A3D0(23);
    func_8028A3D0(34);
}

s32 func_8029301C(void) {
    s32 ret;

    if (D_802A1DB4 == -1) {
        ret = func_80292E90(0, D_80063000, 0x37);
        D_802A1DB8 = 0;
    } else {
        ret = func_80292E90(D_802A1DB4 * 18 + 1, SLOT(D_802A1DB4), 0x12);
    }
    if (ret != 0) {
        return -1;
    }
    return 0;
}

static s32 func_80292E90(u8 addr, u8 *buf, u8 n) {
    s32 i;
    s32 size;
    s32 ret;

    if (!D_802A1DA4) {
        return -2;
    }
    size = n * 8;
    func_80297D60(buf, size);
    for (i = 0; i != 3; i++) {
        if (n == 1) {
            ret = func_80297E70(D_802AC3E0, addr, buf);
        } else {
            ret = func_80297E80(D_802AC3E0, addr, buf, size);
        }
        if (ret == 0) {
            if (func_80292E88(addr, n) == 0) {
                return 0;
            }
        }
    }
    return -1;
}

static s32 func_80292E88(u8 addr, u8 n) {
    u8 *p = &D_800631B8[addr * 8];

    if (func_80292E80(addr, p, n) != 0) {
        return 2;
    }
    if (func_80292DB0(&D_80063000[addr * 8], p, n)) {
        return 1;
    } else {
        return 0;
    }
}

static s32 func_80292E80(u8 addr, u8 *buf, u8 n) {
    return func_80292DB8(addr, buf, n);
}

static s32 func_80292DB8(u8 addr, u8 *buf, u8 n) {
    s32 ret = -1;
    s32 size;
    s32 i;
    s32 retry;

    if (!D_802A1DA4) {
        return -2;
    }
    size = n * 8;
    func_80297D60(buf, size);
    func_80297D50(buf, size);
    i = 1;
    retry = 1;
    for (;;) {
        if (!retry) {
            break;
        }
        if (n == 1) {
            ret = func_80297E68(D_802AC3E0, addr, buf);
        } else {
            ret = func_80297E78(D_802AC3E0, addr, buf, size);
        }
        if (ret == 0) {
            break;
        }
        retry = i < 3;
        i++;
    }
    return ret;
}

static s32 func_80292DB0(u8 *a, u8 *b, u8 n) {
    s32 i;

    for (i = 0; i < n * 8; i++) {
        if (b[i] != a[i]) {
            return 1;
        }
    }
    return 0;
}
