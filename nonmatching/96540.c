/*
 * NON_MATCHING: main_code's 96540, complete: the controller pak save.
 * flags: -O3
 * differing words: us 654, eu 654, jp 654
 */
#include "common.h"
#include "ultralib/PR/os_pfs.h"

/* The libultra Pfs calls go through ZeroJump module 0x16's table
 * (boot_code's D_8001A314: osPfsInit, ReFormat, Checker, AllocateFile,
 * FindFile, DeleteFile, ReadWriteFile, FileState, GetLabel, SetLabel,
 * IsPlug, FreeBlocks, NumFiles, ReSizeFile, InitPak, RepairId). */
s32 func_80298830(OSPfs *, u16, u32, u8 *, u8 *, int, s32 *); /* 0x1603 osPfsAllocateFile */
s32 func_80298838(OSPfs *, u16, u32, u8 *, u8 *, s32 *);      /* 0x1604 osPfsFindFile */
s32 func_80298840(OSPfs *, u16, u32, u8 *, u8 *);             /* 0x1605 osPfsDeleteFile */
s32 func_80298848(OSPfs *, s32, u8, int, int, u8 *);          /* 0x1606 osPfsReadWriteFile */
s32 func_80298850(OSPfs *, s32, OSPfsState *);                /* 0x1607 osPfsFileState */
s32 func_80298868(OSMesgQueue *, u8 *);                       /* 0x160A osPfsIsPlug */
s32 func_80298870(OSPfs *, s32 *);                            /* 0x160B osPfsFreeBlocks */
s32 func_80298878(OSPfs *, s32 *, s32 *);                     /* 0x160C osPfsNumFiles */
s32 func_80298888(OSMesgQueue *, OSPfs *, int);               /* 0x160E osPfsInitPak */
s32 func_80298890(OSPfs *);                                   /* 0x160F osPfsRepairId */

/* A file in func_8027BF38's listing. */
typedef struct {
    /* 0x00 */ s32 used;
    /* 0x04 */ u32 size;
    /* 0x08 */ u8 ext[4];
    /* 0x0C */ u8 name[16];
} PakFile; /* size 0x1C */

typedef struct {
    /* 0x00 */ s32 freeBytes;
    /* 0x04 */ PakFile files[16];
} PakDir;

/* A slot of the EEPROM save image (AD5B0's D_80063000). */
typedef struct {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ u8 unk10[8];
    /* 0x18 */ u8 unk18[3];
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D[0x73];
} SaveSlot96540; /* size 0x90 */

/* What func_8023A834 returns: per controller pak, four values and a name. */
typedef struct {
    /* 0x00 */ u8 unk0[0x50];
    /* 0x50 */ s32 unk50[4][4];
    /* 0x90 */ u8 unk90[0x34];
    /* 0xC4 */ u8 unkC4[4][9];
} UnkStruct_8023A834;

UnkStruct_8023A834 *func_8023A834(void);

extern SaveSlot96540 D_80063000[];
extern OSMesgQueue *D_800BCDE4;

/* .data */
#if VERSION_JP
u8 D_802A1520[16] = { 0x8B, 0x57, 0x8F, 0x4F, 0x8B, 0x3B, 0x6E, 0x4F };
#elif VERSION_EU
u8 D_802A1520[16] = { 0x1B, 0x28, 0x26, 0x1B, 0x1E, 0x2B, 0x26, 0x1A, 0x27, 0x16, 0x14, 0x1E };
#else
u8 D_802A1520[16] = { 0x1B, 0x28, 0x26, 0x1B, 0x1E, 0x2B, 0x26, 0x1A, 0x27, 0x16, 0x14, 0x2E };
#endif
u8 D_802A1530[4] = { 0 };

#if VERSION_JP
#define COMPANY_CODE 0x3138
#define GAME_CODE 0x4E424D4A /* NBMJ */
#elif VERSION_EU
#define COMPANY_CODE 0x3031
#define GAME_CODE 0x4E424D50 /* NBMP */
#else
#define COMPANY_CODE 0x3031
#define GAME_CODE 0x4E424D45 /* NBME */
#endif

/* .bss */
extern OSPfs D_802AFF70[4];
extern UnkStruct_8023A834 *D_802B0110;
extern s32 D_802B0118[4];
extern u8 D_802B0128[];
extern u8 D_802B0150[];

void func_8027CDA4(OSMesgQueue *mq);
void func_8027CBD4(void);
s32 func_8027C88C(s32 ch);
s32 func_8027C788(s32 slot, s32 overwrite);
s32 func_8027C8A4(s32 ch);
s32 func_8027BF38(PakDir *dir);
s32 func_8027BEF0(void);
s32 func_8027BEC0(void);
s32 func_8027BE60(s32 file);
s32 func_8027C900(s32 ch, s32 *file);
s32 func_8027BE28(void);
u8 *func_8027BD68(void);
void func_8027C96C(s32 ch);
void func_8027C5E0(s32 slot);

void *D_802A1534[] = {
    func_8027CDA4, func_8027CBD4, func_8027C88C, func_8027C788, func_8027C8A4,
    func_8027BF38, func_8027BEF0, func_8027BEC0, func_8027BE60, func_8027C900,
    func_8027BE28, func_8027BD68, func_8027C96C, func_8027C5E0, NULL,
};

static s32 func_8027BD74(s32 err, s32 mode);
static s32 func_8027C0DC(u8 **pp, s32 unused, s32 len, s32 err);
static s32 func_8027C18C(s32 ch, s32 file, u8 *buf);
static s32 func_8027C3DC(s32 *file);
static s32 func_8027C4F4(s32 ch, s32 *file);
static void func_8027C560(s32 len, u8 *p);
static void func_8027CA14(s32 ch, s32 retried);
static void func_8027BF30();
static void func_8027C0D4();
static void func_8027C174();
static void func_8027C17C();
static void func_8027C184();
static void func_8027C3D4();
static void func_8027C4EC();
static void func_8027C8F8();
static void func_8027CBC4();
static void func_8027CBCC();

void func_8027CDA4(OSMesgQueue *mq) {
    s32 i;

    D_800BCDE4 = mq;
    for (i = 0; i < 4; i++) {
        D_802B0118[i] = func_8027C8A4(i);
    }
}

static void func_8027CBCC() {
}

static void func_8027CBC4() {
}

void func_8027CBD4(void) {
    s32 i;
    s32 bytes;
    s32 ret;

    func_8027CBC4();
    func_8027CBCC();
    D_802B0110 = func_8023A834();
    for (i = 0; i < 4; i++) {
        D_802B0110->unk50[i][0] = 0;
        D_802B0110->unk50[i][1] = 0;
        D_802B0110->unk50[i][2] = 0;
        D_802B0110->unk50[i][3] = 0;
#if VERSION_JP
        D_802B0110->unkC4[i][0] = 0x9F;
        D_802B0110->unkC4[i][1] = 0x5F;
        D_802B0110->unkC4[i][2] = 0x9B;
        D_802B0110->unkC4[i][3] = 0xF9;
        D_802B0110->unkC4[i][4] = 0x7E;
        D_802B0110->unkC4[i][5] = 0x5F;
#else
        D_802B0110->unkC4[i][0] = 0x1B;
        D_802B0110->unkC4[i][1] = 0x28;
        D_802B0110->unkC4[i][2] = 0x26;
        D_802B0110->unkC4[i][3] = 0x1B;
        D_802B0110->unkC4[i][4] = 0x1E;
        D_802B0110->unkC4[i][5] = 0x2B;
#endif
        D_802B0110->unkC4[i][6] = 0;
        D_802B0110->unkC4[i][7] = 0;
        D_802B0110->unkC4[i][8] = 0;
    }
    for (i = 0; i < 4; i++) {
        ret = func_8027BD74(func_80298870(&D_802AFF70[i], &bytes), 2);
        if (ret == 1 || ret == 0) {
            D_802B0118[i] = ret;
        } else {
            D_802B0118[i] = func_8027C8A4(i);
        }
    }
    for (i = 0; i < 4; i++) {
        func_8027CA14(i, 0);
    }
}

static void func_8027CA14(s32 ch, s32 retried) {
    s32 j;

    switch (D_802B0118[ch]) {
        case 1:
            func_8027C96C(ch);
            if (D_802B0118[ch] == 9) {
                D_802B0110->unk50[ch][0] = D_802B0128[0x16];
                D_802B0110->unk50[ch][1] = D_802B0128[0x17];
                D_802B0110->unk50[ch][2] = D_802B0128[0x18];
                D_802B0110->unk50[ch][3] = D_802B0128[0x19];
                for (j = 0; j < 8; j++) {
                    D_802B0110->unkC4[ch][j] = D_802B0128[8 + j];
                }
                D_802B0110->unkC4[ch][8] = 0;
            }
            break;
        case 2:
            if (!retried) {
                D_802B0118[ch] = func_8027C8A4(ch);
                func_8027CA14(ch, 1);
            }
            break;
        case 6:
            break;
    }
}

void func_8027C96C(s32 ch) {
    s32 file;

    D_802B0118[ch] = func_8027C900(ch, &file);
    if (D_802B0118[ch] == 8) {
        D_802B0118[ch] = func_8027C18C(ch, file, D_802B0128);
    }
}

static void func_8027C8F8() {
}

s32 func_8027C900(s32 ch, s32 *file) {
    s32 ret;

    func_8027C8F8();
    while (TRUE) {
        ret = func_8027C4F4(ch, file);
        if (ret != 2) {
            break;
        }
        ret = func_8027C8A4(ch);
        if (ret != 1) {
            break;
        }
    }
    return ret;
}

s32 func_8027C8A4(s32 ch) {
    return func_8027BD74(func_80298888(D_800BCDE4, &D_802AFF70[ch], ch), 2);
}

s32 func_8027C88C(s32 ch) {
    return D_802B0118[ch];
}

/* The 32-byte file: "BAKU", the revision, "Hu", a checksum; the slot's
 * name and its checksum; four zeros, 0xFF, four nibbles of the slot, their
 * checksum; 0xFE and four zeros. Every checksummed run sums to 0xFF. */
void func_8027C5E0(s32 slot) {
    u8 *buf = D_802B0128;
    s32 i;
    s32 j;

    buf[0] = 'B';
    buf[1] = 'A';
    buf[2] = 'K';
    buf[3] = 'U';
    buf[4] = 1;
    buf[5] = 'H';
    buf[6] = 'u';
    func_8027C560(7, buf);
    j = 8;
    for (i = 0; i < 8; i++) {
        buf[j++] = D_80063000[slot].unk10[i];
    }
    func_8027C560(8, &D_802B0128[8]);
    j++;
    buf[j++] = 0;
    buf[j++] = 0;
    buf[j++] = 0;
    buf[j++] = 0;
    buf[j++] = 0xFF;
    buf[j++] = D_80063000[slot].unk1B & 0xF;
    buf[j++] = (D_80063000[slot].unk1B >> 4) & 0xF;
    buf[j++] = D_80063000[slot].unk1C & 0xF;
    buf[j++] = (D_80063000[slot].unk1C >> 4) & 0xF;
    func_8027C560(4, &D_802B0128[0x16]);
    j++;
    buf[j++] = 0xFE;
    buf[j++] = 0;
    buf[j++] = 0;
    buf[j++] = 0;
    buf[j++] = 0;
}

static void func_8027C560(s32 len, u8 *p) {
    u8 sum = 0;
    s32 i;

    for (i = 0; i < len; i++) {
        sum += *p++;
    }
    *p = 0xFF - sum;
}

static void func_8027C4EC() {
}

s32 func_8027C788(s32 slot, s32 overwrite) {
    s32 ret;
    s32 file;

    func_8027C5E0(slot);
    if (func_8027C4F4(0, &file) == 8) {
        if (overwrite) {
            ret = func_8027C3DC(&file);
        } else {
            ret = 0xD;
        }
    } else {
        func_8027C4EC();
        ret = func_8027BD74(func_80298830(D_802AFF70, COMPANY_CODE, GAME_CODE, D_802A1520, D_802A1530, 0x20, &file), 1);
        if (ret == 8) {
            ret = func_8027C3DC(&file);
        }
    }
    return ret;
}

static s32 func_8027C4F4(s32 ch, s32 *file) {
    return func_8027BD74(func_80298838(&D_802AFF70[ch], COMPANY_CODE, GAME_CODE, D_802A1520, D_802A1530, file), 1);
}

static void func_8027C3D4() {
}

static s32 func_8027C3DC(s32 *file) {
    s32 i;
    s32 j;
    s32 ret;
    s32 diff;

    func_8027C3D4();
    for (i = 0; i < 3; i++) {
        ret = func_8027BD74(func_80298848(D_802AFF70, *file, PFS_WRITE, 0, 0x20, D_802B0128), 0);
        if (ret == 9) {
            ret = func_8027C18C(0, *file, D_802B0150);
            if (ret == 9) {
                for (j = 0; j < 0x20; j++) {
                    if (D_802B0128[j] != D_802B0150[j]) {
                        diff = 1;
                        goto done;
                    }
                }
                diff = 0;
            done:
                ret = 9;
                if (diff == 1) {
                    ret = 0x10;
                }
            }
            if (ret == 9) {
                break;
            }
        }
    }
    return ret;
}

static void func_8027C184() {
}

static void func_8027C17C() {
}

static void func_8027C174() {
}

static s32 func_8027C18C(s32 ch, s32 file, u8 *buf) {
    s32 i;
    s32 ret;
    s32 err;
    u8 *p;

    func_8027C174();
    func_8027C17C();
    func_8027C184();
    for (i = 0; i < 3; i++) {
        switch (func_80298848(&D_802AFF70[ch], file, PFS_READ, 0, 0x20, buf)) {
            case 0:
                err = 0;
                ret = 0;
                if (D_802B0128[4] != 1) {
                    ret = 1;
                }
                if (ret) {
                    ret = 0xB;
                    break;
                }
                p = D_802B0128;
                if (func_8027C0DC(&p, 0, 8, 1)) {
                    err = 1;
                } else if (func_8027C0DC(&p, 0, 9, 2)) {
                    err = 2;
                } else if (func_8027C0DC(&p, 0, 5, 3)) {
                    err = 3;
                } else if (func_8027C0DC(&p, 0, 5, 4)) {
                    err = 4;
                } else if (*p++ != 0xFE) {
                    err = 5;
                } else if (*p++ != 0) {
                    err = 6;
                } else if (*p++ != 0) {
                    err = 7;
                } else if (*p++ != 0) {
                    err = 8;
                } else if (*p++ != 0) {
                    err = 9;
                }
                if (err) {
                    ret = 0xA;
                } else {
                    ret = 9;
                }
                break;
            case 1:
                ret = 0;
                break;
            case 2:
                ret = 2;
                break;
            case 3:
                ret = 4;
                break;
            case 5:
                ret = 7;
                break;
            case 6:
                ret = 0xC;
                break;
            default:
                ret = 0;
                break;
        }
        if (ret == 0 || ret == 2 || ret == 9) {
            break;
        }
    }
    return ret;
}

static s32 func_8027C0DC(u8 **pp, s32 unused, s32 len, s32 err) {
    u8 *p = *pp;
    u8 sum = 0;
    s32 i;

    func_8027C0D4();
    for (i = 0; i < len; i++) {
        sum += *p++;
    }
    if (sum != 0xFF) {
        return err;
    }
    *pp = p;
    return 0;
}

static void func_8027C0D4() {
}

s32 func_8027BF38(PakDir *dir) {
    s32 ret = 9;
    s32 i;
    s32 j;
    OSPfsState state;

    func_8027BF30();
    switch (func_80298870(D_802AFF70, &dir->freeBytes)) {
        case 0:
            for (i = 0; i < 16; i++) {
                if (func_80298850(D_802AFF70, i, &state) == 0) {
                    dir->files[i].used = 1;
                    dir->files[i].size = state.file_size;
                    for (j = 0; j < 4; j++) {
                        dir->files[i].ext[j] = state.ext_name[j];
                    }
                    for (j = 0; j < 16; j++) {
                        dir->files[i].name[j] = state.game_name[j];
                    }
                } else {
                    dir->files[i].used = 0;
                }
            }
            break;
        case 1:
            ret = 0;
            break;
        case 2:
            ret = 2;
            break;
        case 3:
            ret = 4;
            break;
        case 4:
            ret = 3;
            break;
        case 5:
            ret = 7;
            break;
    }
    return ret;
}

static void func_8027BF30() {
}

s32 func_8027BEF0(void) {
    u8 pattern = 0;
    s32 ret;

    func_80298868(D_800BCDE4, &pattern);
    ret = 0;
    if (pattern & 1) {
        ret = 1;
    }
    return ret;
}

s32 func_8027BEC0(void) {
    return func_8027BD74(func_80298890(D_802AFF70), 0);
}

s32 func_8027BE60(s32 file) {
    OSPfsState state;
    s32 ret;

    ret = func_80298850(D_802AFF70, file, &state);
    if (ret == 0) {
        ret = func_80298840(D_802AFF70, state.company_code, state.game_code, (u8 *) state.game_name,
                            (u8 *) state.ext_name);
    }
    return func_8027BD74(ret, 0);
}

s32 func_8027BE28(void) {
    s32 max;
    s32 used;

    return func_8027BD74(func_80298878(D_802AFF70, &max, &used), 2);
}

static s32 func_8027BD74(s32 err, s32 mode) {
    s32 ret = 0;

    switch (err) {
        case 0:
            switch (mode) {
                case 0:
                    return 9;
                case 1:
                    return 8;
                case 2:
                    return 1;
            }
            return ret;
        case 1:
            break;
        case 2:
            return 2;
        case 3:
            return 4;
        case 4:
            return 3;
        case 10:
            return 5;
        case 11:
            return 6;
        case 5:
            return 7;
        case 6:
            return 0xC;
        case 7:
            return 0xE;
        case 8:
            return 0xF;
        case 9:
            ret = 0xD;
            break;
    }
    return ret;
}

u8 *func_8027BD68(void) {
    return D_802B0128;
}

void func_8027BD40(void) {
    func_80297D30(0x1C, D_802A1534);
}
