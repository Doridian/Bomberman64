#include "common.h"

/* Hudson's LZSS decoder (docs/COMPRESSION.md) for a file opened with
 * func_80226604: a 0x400-byte ring buffer filled from 0x3BE, flag bits
 * LSB first, a 10-bit position and a length of 3-66 per reference.
 * D_802A1D90 is set while it runs. */

void *malloc(s32);
void free(void *);
s32 func_80226304(struct UnkStruct_80225CC0 *file);

s32 D_802A1D90 = 0;
u8 *D_802B0310;
u16 D_802B0314;

void func_80292BD0(struct UnkStruct_80225CC0 *file, u8 *dst, s32 size) {
    u16 flags;
    s32 i;
    s32 lo;
    s32 len;
    void *start = dst;
    s32 c;

    D_802A1D90 = 1;
    D_802B0310 = malloc(0x400);
    D_802B0314 = 0x3BE;
    func_80225C7C(D_802B0310, 0, 0x400);
    flags = 0;
    while (size != 0) {
        flags >>= 1;
        if (!(flags & 0x100)) {
            flags = func_80226304(file) | 0xFF00;
        }
        if (flags & 1) {
            c = func_80226304(file);
            *dst++ = c;
            D_802B0310[D_802B0314] = c;
            D_802B0314++;
            D_802B0314 &= 0x3FF;
            size--;
        } else {
            lo = func_80226304(file);
            c = func_80226304(file);
            lo |= (c & ~0x3F) << 2;
            len = (c & 0x3F) + 3;
            for (i = 0; i < len; i++) {
                c = D_802B0310[(lo + i) & 0x3FF];
                *dst++ = c;
                D_802B0310[D_802B0314] = c;
                D_802B0314++;
                D_802B0314 &= 0x3FF;
            }
            size -= i;
        }
    }
    func_80297D60((void *) (((uintptr_t) start + 15) >> 4 << 4), (u32) (size + 15) >> 4 << 4);
    free(D_802B0310);
    D_802A1D90 = 0;
}
