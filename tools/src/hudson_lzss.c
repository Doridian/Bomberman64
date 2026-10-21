/*
 * Hudson's LZSS encoder (Okumura's LZSS.C with N = 1024, F = 66,
 * THRESHOLD = 2, a zero-filled window), the fast path of
 * tools/hudson_lzss.py, which loads it through ctypes.  It must give exactly
 * the bytes the Python encoder does; tools/lzss_check.py checks both
 * against the ROM.
 *
 *   cc -O2 -shared -fPIC -o build/tools/libhudson_lzss.so tools/src/hudson_lzss.c
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define N 1024
#define F 66
#define THRESHOLD 2
#define NIL N

struct state
{
    uint8_t text[N + F - 1];
    int lson[N + 1], rson[N + 257], dad[N + 1];
    int ml, mp;
};

static void insert(struct state *st, int r)
{
    int i, p, cmp = 1;
    uint8_t *key = &st->text[r];

    p = N + 1 + key[0];
    st->rson[r] = st->lson[r] = NIL;
    st->ml = 0;
    for (;;)
    {
        if (cmp >= 0)
        {
            if (st->rson[p] != NIL)
                p = st->rson[p];
            else
            {
                st->rson[p] = r;
                st->dad[r] = p;
                return;
            }
        }
        else
        {
            if (st->lson[p] != NIL)
                p = st->lson[p];
            else
            {
                st->lson[p] = r;
                st->dad[r] = p;
                return;
            }
        }
        for (i = 1; i < F; i++)
            if ((cmp = key[i] - st->text[p + i]) != 0)
                break;
        if (i > st->ml)
        {
            st->mp = p;
            if ((st->ml = i) >= F)
                break;
        }
    }
    st->dad[r] = st->dad[p];
    st->lson[r] = st->lson[p];
    st->rson[r] = st->rson[p];
    st->dad[st->lson[p]] = r;
    st->dad[st->rson[p]] = r;
    if (st->rson[st->dad[p]] == p)
        st->rson[st->dad[p]] = r;
    else
        st->lson[st->dad[p]] = r;
    st->dad[p] = NIL;
}

static void delete(struct state *st, int p)
{
    int q;

    if (st->dad[p] == NIL)
        return;
    if (st->rson[p] == NIL)
        q = st->lson[p];
    else if (st->lson[p] == NIL)
        q = st->rson[p];
    else
    {
        q = st->lson[p];
        if (st->rson[q] != NIL)
        {
            do
                q = st->rson[q];
            while (st->rson[q] != NIL);
            st->rson[st->dad[q]] = st->lson[q];
            st->dad[st->lson[q]] = st->dad[q];
            st->lson[q] = st->lson[p];
            st->dad[st->lson[p]] = q;
        }
        st->rson[q] = st->rson[p];
        st->dad[st->rson[p]] = q;
    }
    st->dad[q] = st->dad[p];
    if (st->rson[st->dad[p]] == p)
        st->rson[st->dad[p]] = q;
    else
        st->lson[st->dad[p]] = q;
    st->dad[p] = NIL;
}

/* out needs 4 + len * 9 / 8 + 16 bytes; returns the length written. */
size_t hudson_lzss_encode(const uint8_t *in, size_t len, uint8_t *out)
{
    static struct state st;
    uint8_t code[17];
    size_t o = 4, pos;
    int i, n, s, r, cbp, mask, last;
    long length;

    out[0] = len >> 24;
    out[1] = len >> 16;
    out[2] = len >> 8;
    out[3] = len;
    if (len == 0)
        return o;
    memset(&st, 0, sizeof st);
    for (i = N + 1; i < N + 257; i++)
        st.rson[i] = NIL;
    for (i = 0; i < N; i++)
        st.dad[i] = NIL;

    code[0] = 0;
    cbp = mask = 1;
    s = 0;
    r = N - F;
    n = len < F ? (int)len : F;
    memcpy(&st.text[r], in, n);
    pos = n;
    length = n;
    for (i = 1; i <= F; i++)
        insert(&st, r - i);
    insert(&st, r);
    while (length > 0)
    {
        if (st.ml > length)
            st.ml = length;
        if (st.ml <= THRESHOLD)
        {
            st.ml = 1;
            code[0] |= mask;
            code[cbp++] = st.text[r];
        }
        else
        {
            code[cbp++] = st.mp & 0xFF;
            code[cbp++] = ((st.mp >> 2) & 0xC0) | (st.ml - (THRESHOLD + 1));
        }
        if ((mask = (mask << 1) & 0xFF) == 0)
        {
            memcpy(out + o, code, cbp);
            o += cbp;
            code[0] = 0;
            cbp = mask = 1;
        }
        last = st.ml;
        for (i = 0; i < last && pos < len; i++)
        {
            uint8_t c = in[pos++];
            delete(&st, s);
            st.text[s] = c;
            if (s < F - 1)
                st.text[s + N] = c;
            s = (s + 1) & (N - 1);
            r = (r + 1) & (N - 1);
            insert(&st, r);
        }
        while (i++ < last)
        {
            delete(&st, s);
            s = (s + 1) & (N - 1);
            r = (r + 1) & (N - 1);
            if (--length)
                insert(&st, r);
        }
    }
    if (cbp > 1)
    {
        memcpy(out + o, code, cbp);
        o += cbp;
    }
    return o;
}
