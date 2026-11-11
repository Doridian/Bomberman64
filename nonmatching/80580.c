/*
 * NON_MATCHING: main_code's 80580, complete first draft: Hudson's sound
 * manager over libultra audio (the ALSndPlayer voices D_802AD654 with
 * their scripts D_802AD65C, the 'T1'/'T2' sound tables, the 'S1'/'S2'
 * sequence files on the ALCSPlayer, and the SDK's oscillator example).
 * One object (no caller before its callee, no padding, the data, rodata
 * and bss follow function order). Every procedure is emitted in the
 * original's order. Not built into the ROM (docs/DECOMPILING.md,
 * "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 46, eu 46, jp 46
 *
 * The object is the same in all three versions. 70 of the 79 original
 * procedures match (stubs included). The IPA statics
 * (s-registers used unsaved, or arguments in odd registers) are static
 * here: 80266D8C, 8026706C (num, def: the original's num is homed at
 * 0(sp) though -O3 passes it in a1), 80267784, 802679C0, 80267A18,
 * 80268440, 80269144, 802699C8, 80269A8C, 80269AFC, 8026A108, 8026A164.
 * The 8-byte stubs are statics inlined into the function after them:
 * 80267A10 (a sound's free voice), 802679A0-B8 (the script's clamps and
 * fade), 802691A0 (the sequence load), 80267064 (a volume, returning
 * from both arms), 80266928 (a script's reset), 80268430/38 (80268440's
 * script setup and bank search), 80269A7C/84 (empty statics whose calls
 * 80269AFC keeps), the recursive setters' stubs 80266154/298/3D8/508
 * (empty, the setters recurse themselves).
 * func_80265FBC is a static too (callers keep registers live across
 * it), inlined only into 80265FF8: a dead `if (0)` store keeps IDO
 * from inlining it into the others. 8026724C's unused second SndDef
 * and 80268440's pad give the original's frame sizes.
 * 80267A18 has the original's size and s-registers: the dead `if (op ==
 * K) {}` tests and `if (idx) {}` give its constants their s-registers,
 * the stop loop reuses v and num, the vibrato and sweep convert with
 * (s16), and their quotients go through r. What is left there is its
 * frame (0xA0 against 0xB0, so every sp offset), case 3's argument
 * order and temp names. Biggest left: 8026A164 (2 words short: the
 * loop's s4 count tests blez where the original tests beq, and a
 * subtraction scheduled ahead of its call), 802691A8 (a word long: its
 * flag tests are laid out the other way), 80267A18, 80266D8C (a word
 * short: D_802A1368's address is kept in a register where the original
 * rebuilds it with lui at each time and stores it twice), 8026706C
 * (temp names and D_802AD648 in a3, the original's v0), 80269AFC (a
 * store scheduled two slots apart), 80268440 (registers only),
 * 80268F94 (the original reuses one constant 1 for both flags).
 */
#include "common.h"

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

/* libultra's ALBankFile/ALBank/ALInstrument (libaudio.h), as the code reads them. */
typedef struct SndInst {
    /* 0x00 */ u8 volume;
    /* 0x01 */ u8 pan;
    /* 0x02 */ u8 priority;
    /* 0x03 */ u8 flags;
    /* 0x04 */ u8 trem[4];
    /* 0x08 */ u8 vib[4];
    /* 0x0C */ s16 bendRange;
    /* 0x0E */ s16 soundCount;
    /* 0x10 */ void *soundArray[1];
} SndInst;

typedef struct SndBank {
    /* 0x00 */ s16 instCount;
    /* 0x02 */ u8 flags;
    /* 0x03 */ u8 pad;
    /* 0x04 */ s32 sampleRate;
    /* 0x08 */ SndInst *percussion;
    /* 0x0C */ SndInst *instArray[1];
} SndBank;

typedef struct SndBankFile {
    /* 0x00 */ s16 revision;
    /* 0x02 */ s16 bankCount;
    /* 0x04 */ SndBank *bankArray[1];
} SndBankFile;

/* One entry of the sound table D_802AD650 points to. */
typedef struct SndEntry {
    /* 0x00 */ s8 unk0;
    /* 0x01 */ s8 unk1;
    /* 0x02 */ s8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u16 unk6;
} SndEntry;

typedef struct SndTable {
    /* 0x00 */ s16 magic; /* 'T1' 0x5431 or 'T2' 0x5432 */
    /* 0x02 */ s16 count;
    /* 0x04 */ SndEntry entries[1];
} SndTable;

/* What func_8026706C makes of an entry. */
typedef struct SndDef {
    /* 0x00 */ void *sound;
    /* 0x04 */ f32 pitch;
    /* 0x08 */ s16 script;
    /* 0x0A */ s16 vol;
    /* 0x0C */ u8 pan;
    /* 0x0D */ u8 prio;
    /* 0x0E */ s8 unkE;
    /* 0x0F */ u8 unkF;
} SndDef;

/* The voices, D_802AD654[D_802A12BC]. */
typedef struct Voice {
    /* 0x00 */ void *sound;
    /* 0x04 */ f32 pitch;
    /* 0x08 */ s32 flags;
    /* 0x0C */ s16 num;
    /* 0x0E */ s16 sndId;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 state;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ s8 unk1F;
} Voice; /* size 0x20 */

/* Per voice, the script running on it, D_802AD65C[D_802A12BC]. */
typedef struct VoiceScript {
    /* 0x00 */ u8 *pc;
    /* 0x04 */ s32 flags;
    /* 0x08 */ s16 script;
    /* 0x0A */ s16 parent;
    /* 0x0C */ s16 wait;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 child[3];
    /* 0x1A */ s16 nchild;
    /* 0x1C */ u8 loop;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
} VoiceScript; /* size 0x34 */

extern SndBankFile *D_802AD648;
extern SndTable *D_802AD650;
extern Voice *D_802AD654;
extern VoiceScript *D_802AD65C;
extern s32 D_802A12BC;

/* The N64 SDK's oscillator example (initOsc/updateOsc/stopOsc), Hudson's copy. */
typedef struct oscData_s {
    /* 0x00 */ struct oscData_s *next;
    /* 0x04 */ u8 type;
    /* 0x05 */ u8 stateFlags;
    /* 0x06 */ u16 maxCount;
    /* 0x08 */ u16 curCount;
    /* 0x0C */ union {
        struct {
            u8 halfdepth;
            u8 baseVol;
        } tsin;
        struct {
            u8 curVal;
            u8 hiVal;
            u8 loVal;
        } tsqr;
        struct {
            u8 baseVol;
            u8 depth;
        } tsaw;
        struct {
            f32 depthcents;
        } vsin;
        struct {
            f32 loRatio;
            f32 hiRatio;
        } vsqr;
        struct {
            s32 hicents;
            s32 centsrange;
        } vdsaw;
        struct {
            s32 locents;
            s32 centsrange;
        } vasaw;
    } data;
} oscData; /* size 0x14 */

extern oscData *D_802AD3C4;
extern oscData D_802AD3C8[32];

typedef struct SeqData {
    /* 0x00 */ u8 *offset;
    /* 0x04 */ s32 len;
} SeqData;

typedef struct SeqFile {
    /* 0x00 */ s16 revision; /* 'S1' 0x5331 or 'S2' 0x5332 */
    /* 0x02 */ s16 seqCount;
    /* 0x04 */ SeqData seqArray[1];
} SeqFile;

/* 'S2': per sequence, its bank, after the SeqData. */
typedef struct SeqInfo {
    /* 0x00 */ u8 bank;
    /* 0x01 */ s8 vol;
    /* 0x04 */ s32 bankRom;
    /* 0x08 */ u32 bankLen;
    /* 0x0C */ s32 table;
} SeqInfo;

/* 'T2': the header after the sound table. */
typedef struct SndHeader {
    /* 0x00 */ s32 count;
    /* 0x04 */ s32 rom;
    /* 0x08 */ s32 len;
    /* 0x0C */ s32 table;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 scriptRom;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 scriptLen;
} SndHeader;

/* 'T2': the sounds (ALSound), relocated in place. */
typedef struct SndWave {
    /* 0x00 */ s32 base;
    /* 0x04 */ s32 len;
    /* 0x08 */ u8 type;
    /* 0x09 */ u8 flags;
    /* 0x0C */ void *loop;
    /* 0x10 */ void *book;
} SndWave;

typedef struct SndSound {
    /* 0x00 */ void *envelope;
    /* 0x04 */ void *keyMap;
    /* 0x08 */ SndWave *wavetable;
    /* 0x0C */ u8 samplePan;
    /* 0x0D */ u8 sampleVolume;
    /* 0x0E */ u8 flags;
} SndSound;

typedef struct ChlState {
    /* 0x00 */ s32 prog;
    /* 0x04 */ u8 pan;
    /* 0x05 */ u8 fxmix;
    /* 0x06 */ u8 vol;
    /* 0x07 */ u8 prio;
} ChlState;

extern SeqFile *D_802AD22C;
extern SeqInfo *D_802AD230;
extern SndBankFile *D_802AD21C;
extern u16 **D_802AD658;
extern ChlState D_802AD340[16];
extern void *D_802AD220; /* ALCSPlayer */
extern void *D_802AD224; /* the sequence */
extern void *D_802AD228; /* ALCSeq */
extern void *D_802AD64C; /* ALSndPlayer */

/* Stop voice i (inlined everywhere it's used). */
#define VOICE_STOP(i)                                         \
    {                                                         \
        Voice *_v = &D_802AD654[i];                           \
        VoiceScript *_s;                                      \
        if (_v->state == 1) {                                 \
            if (_v->flags & 0x1000) {                         \
                _v->flags &= ~0x1000;                         \
            } else {                                          \
                func_802986F0(D_802AD64C, _v->sndId);         \
                func_80298710(D_802AD64C);                    \
                _v->flags |= 0x2000;                          \
            }                                                 \
            _v->unk1F = 0;                                    \
            _s = &D_802AD65C[i];                              \
            _s->script = -1;                                  \
            _s->flags = 0;                                    \
        }                                                     \
    }

static void *func_80268438(s16 num);
static void func_80268430(s16 idx, s16 script, s8 type);
static s16 func_802699C0();
static void func_80266928(s16 idx);
void *func_8026B72C(s32);
s32 *func_8026B79C(void);
void func_8026B7A8(s32);
void func_8026B7D4(void);
s16 func_8026B9CC(void *, void *);
void func_80297D50(void *, void *);
void func_80297D80(void *, void *, s32);
s32 func_80297D90(void *, void *, s32);
void func_80298028(void *, s32, s32, s32, void *, s32, void *);
void func_802983A8(u8);
void func_802983D0(void *, s32, s32);
void func_802983E8(void *, void *);
void func_802983F0(void *, void *);
void func_80298510(void *, void *);
void func_80298540(void *, void *);
void func_80298548(void *, void *);
f32 func_80298550(s32);
void func_80298618(void *, void *);
void func_80298620(void *);
void func_80298628(void *, void *);
void func_80298638(void *);
void func_80298640(void *);
s32 func_80298648(void *);
void func_80298650(void *, void *);
void func_80298658(void *, s32);
s32 func_80298660(void *);
void func_80298670(void *, s16);
void func_80298678(void *, u8, u8);
s32 func_80298680(void *, u8);
void func_80298688(void *, u8, u8);
u8 func_80298690(void *, u8);
void func_80298698(void *, u8, u8);
u8 func_802986A0(void *, u8);
void func_802986A8(void *, u8, u8);
u8 func_802986B0(void *, u8);
void func_802986B8(void *, u8, u8);
u8 func_802986C0(void *, u8);
void func_802986D0(void *, void *);
void func_802986D8(void *);
s16 func_802986E0(void *, void *);
void func_802986E8(void *, s16);
void func_802986F0(void *, s16);
void func_80298700(void *);
void func_80298710(void *);
void func_80298718(void *, s16);
void func_80298720(void *, f32);
void func_80298728(void *, u8);
void func_80298730(void *, s16, u8);
void func_80298738(void *, u8);
s32 func_80298740(void *);
f32 sinf(f32);

extern s32 D_802A1250;
extern u8 D_802A1254[];
extern u8 D_802A1278[];
extern s32 D_802A1288;
extern u8 D_802A1298[];
extern s32 D_802A12B4;
extern s32 D_802A12B8;
extern s32 D_802A12C0;
extern u8 D_802A12C8[];
extern s32 D_802A1330;
extern s32 D_802A1334;
extern s32 D_802A1338;
extern s32 D_802A133C;
extern s32 D_802A1340;
extern s32 D_802A1344;
extern s32 D_802A1348;
extern s32 D_802A134C;
extern s32 D_802A1350;
extern f32 D_802A1354;
extern f32 D_802A1358;
extern f32 D_802A135C;
extern f32 D_802A1360;
extern s16 D_802A1364;
extern u8 D_802AD120[];
extern u8 D_802AD130[];
extern u8 D_802AD1F8[];
extern s32 D_802AD210;
extern s32 D_802AD214;
extern u8 D_802AD218;
extern s32 D_802AD234;
extern u32 D_802AD238;
extern f32 D_802AD23C;
extern f32 D_802AD240;
extern s16 D_802AD244;
extern s16 D_802AD246;
extern s16 D_802AD248;
extern s16 D_802AD24A;
extern u8 D_802AD24C;
extern u8 D_802AD250[];
extern s16 D_802AD3C0;
extern oscData D_802AD3DC;
extern oscData D_802AD3F0;
extern oscData D_802AD404;
extern oscData ***D_802AD418;
extern oscData **D_802AD42C;
extern oscData *D_802AD440;
extern oscData D_802AD454;
extern s32 D_802AD660;
extern f32 D_802AD664;
extern f32 D_802AD668;
extern s16 D_802AD66C;
extern s16 D_802AD66E;
extern s16 D_802AD670;
extern s16 D_802AD672;
extern u8 D_802AD674;
extern u8 D_802AD675;
extern u8 D_802AD684[];
static s16 func_80267A10(s16 num);
static void func_802679B8(s16 *p, s16 lo, s16 hi);
static void func_802679A8(VoiceScript *s);
static void func_802679B0(VoiceScript *s, Voice *v);
static void func_802679A0(VoiceScript *s, Voice *v);
static void func_802691A0(void);
static void func_80266154();
static void func_80266298();
static void func_802663D8();
static void func_80266508();

s8 func_80265D80(void);
s16 func_80265D90(void);
u8 func_80265DA0(void);
s8 func_80265DB0(void);
void func_80265DD8(s8 arg0);
void func_80265E7C(s16 arg0);
void func_80265F1C(u8 arg0);
static s16 func_80265FBC(s8 arg0);
void func_80265FF8(s8 arg0);
static void func_802660B4(void);
void func_80266118(s8 arg0);
static void func_80266154();
void func_8026615C(s16 idx, s8 vol);
static void func_80266298();
void func_802662A0(s16 idx, s16 pitch);
static void func_802663D8();
void func_802663E0(s16 idx, u8 pan);
static void func_80266508();
void func_80266510(s16 idx, s8 vol);
void func_80266644(s16 arg0, s16 arg1, f32 arg2);
void func_802668D4(s16 arg0);
void func_80266930(s16 arg0);
void func_80266B50(void);
s16 func_80266CA0(void);
u8 func_80266CD4(s16 arg0);
s32 func_80266CFC(void);
s16 func_80266D0C(s16 arg0);
static s16 func_80266D8C(u8 prio, s32 arg1);
static s32 func_80267064(s8 vol);
static void func_8026706C(s16 num, SndDef *def);
s16 func_8026724C(s16 num);
s16 func_802675F4(s16 arg0, s16 arg1, f32 arg2);
void func_80267654(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_80267730(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80267754(void);
static void func_80267784(s16 arg0);
static f32 func_802679C0(u8 depth);
static s16 func_80267A10(s16 num);
static void func_80267A18(s16 idx);
static void func_80268440(s16 idx);
void func_802686B8(void);
void func_802689B4(s16 arg0);
void func_80268A40(s16 arg0);
s16 func_80268BB8(void);
void func_80268C54(void);
s8 func_80268D6C(void);
void func_80268D94(s8 arg0);
void func_80268E0C(s8 arg0);
void func_80268E7C(s16 arg0);
void func_80268EE4(void);
s16 func_80268F3C(void);
s32 func_80268F70(void);
s32 func_80268F94(s16 arg0);
void func_802690DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8026910C(void);
static void func_80269144(void *dst, s32 size, s32 rom);
void func_802691A8(void);
s16 *func_80269680(u32 arg0);
void func_80269704(u8 arg0);
s32 func_802697A0(void);
s32 func_802697C0(void);
s32 func_802697E0(void);
s32 func_80269800(void);
s32 func_80269820(void);
s32 func_80269840(void);
void func_8026984C(u8 *arg0);
void func_80269908(u8 *arg0);
static s32 func_802699C8(void);
static s32 func_80269A8C(s32 size);
static s16 func_80269AFC(void);
static s32 func_8026A108(s32 arg0);
static s16 func_8026A164(void);
s16 func_8026A5BC(void);
s16 func_8026A754(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_8026A8B4(void **oscState, f32 *initVal, u8 oscType, u8 oscRate, u8 oscDepth, u8 oscDelay);
s32 func_8026ABF4(void *oscState, f32 *updateVal);
void func_8026B1EC(void *oscState);

void func_8026B1EC(void *oscState) {
    ((oscData *) oscState)->next = D_802AD3C4;
    D_802AD3C4 = (oscData *) oscState;
}

s32 func_8026ABF4(void *oscState, f32 *updateVal) {
    f32 tmpFlt;
    oscData *statePtr = (oscData *) oscState;
    s32 deltaTime = 16000;

    switch (statePtr->type) {
        case 1:
            statePtr->curCount++;
            if (statePtr->curCount >= statePtr->maxCount) {
                statePtr->curCount = 0;
            }
            tmpFlt = (f32) statePtr->curCount / (f32) statePtr->maxCount;
            tmpFlt = sinf(tmpFlt * 6.2831853);
            tmpFlt = tmpFlt * (f32) statePtr->data.tsin.halfdepth;
            *updateVal = (f32) statePtr->data.tsin.baseVol + tmpFlt;
            break;
        case 2:
            if (statePtr->stateFlags == 0) {
                *updateVal = (f32) statePtr->data.tsqr.loVal;
                statePtr->stateFlags = 1;
            } else {
                *updateVal = (f32) statePtr->data.tsqr.hiVal;
                statePtr->stateFlags = 0;
            }
            deltaTime *= statePtr->maxCount;
            break;
        case 3:
            statePtr->curCount++;
            if (statePtr->curCount > statePtr->maxCount) {
                statePtr->curCount = 0;
            }
            tmpFlt = (f32) statePtr->curCount / (f32) statePtr->maxCount;
            tmpFlt *= (f32) statePtr->data.tsaw.depth;
            *updateVal = (f32) statePtr->data.tsaw.baseVol - tmpFlt;
            break;
        case 4:
            statePtr->curCount++;
            if (statePtr->curCount > statePtr->maxCount) {
                statePtr->curCount = 0;
            }
            tmpFlt = (f32) statePtr->curCount / (f32) statePtr->maxCount;
            tmpFlt *= (f32) statePtr->data.tsaw.depth;
            *updateVal = (f32) statePtr->data.tsaw.baseVol + tmpFlt;
            break;
        case 0x80:
            statePtr->curCount++;
            if (statePtr->curCount >= statePtr->maxCount) {
                statePtr->curCount = 0;
            }
            tmpFlt = (f32) statePtr->curCount / (f32) statePtr->maxCount;
            tmpFlt = sinf(tmpFlt * 6.2831853) * statePtr->data.vsin.depthcents;
            *updateVal = func_80298550((s32) tmpFlt);
            break;
        case 0x81:
            if (statePtr->stateFlags == 0) {
                statePtr->stateFlags = 1;
                *updateVal = statePtr->data.vsqr.loRatio;
            } else {
                statePtr->stateFlags = 0;
                *updateVal = statePtr->data.vsqr.hiRatio;
            }
            deltaTime *= statePtr->maxCount;
            break;
        case 0x82:
            statePtr->curCount++;
            if (statePtr->curCount > statePtr->maxCount) {
                statePtr->curCount = 0;
            }
            tmpFlt = (f32) statePtr->curCount / (f32) statePtr->maxCount;
            tmpFlt *= (f32) statePtr->data.vdsaw.centsrange;
            tmpFlt = (f32) statePtr->data.vdsaw.hicents - tmpFlt;
            *updateVal = func_80298550((s32) tmpFlt);
            break;
        case 0x83:
            statePtr->curCount++;
            if (statePtr->curCount > statePtr->maxCount) {
                statePtr->curCount = 0;
            }
            tmpFlt = (f32) statePtr->curCount / (f32) statePtr->maxCount;
            tmpFlt *= (f32) statePtr->data.vasaw.centsrange;
            tmpFlt += (f32) statePtr->data.vasaw.locents;
            *updateVal = func_80298550((s32) tmpFlt);
            break;
    }
    return deltaTime;
}

s32 func_8026A8B4(void **oscState, f32 *initVal, u8 oscType, u8 oscRate, u8 oscDepth, u8 oscDelay) {
    oscData *statePtr;
    s32 deltaTime = 0;

    if (D_802AD3C4 != NULL) {
        statePtr = D_802AD3C4;
        D_802AD3C4 = D_802AD3C4->next;
        statePtr->type = oscType;
        *oscState = statePtr;
        deltaTime = oscDelay << 14;
        switch (oscType) {
            case 1:
                statePtr->curCount = 0;
                statePtr->maxCount = 259 - oscRate;
                statePtr->data.tsin.halfdepth = oscDepth >> 1;
                statePtr->data.tsin.baseVol = 127 - statePtr->data.tsin.halfdepth;
                *initVal = (f32) statePtr->data.tsin.baseVol;
                break;
            case 2:
                statePtr->maxCount = 256 - oscRate;
                statePtr->curCount = statePtr->maxCount;
                statePtr->stateFlags = 0;
                statePtr->data.tsqr.loVal = 127 - oscDepth;
                statePtr->data.tsqr.hiVal = 127;
                statePtr->data.tsqr.curVal = 127;
                *initVal = (f32) 127;
                break;
            case 3:
                statePtr->maxCount = 256 - oscRate;
                statePtr->curCount = 0;
                statePtr->data.tsaw.baseVol = 127;
                statePtr->data.tsaw.depth = oscDepth;
                *initVal = (f32) statePtr->data.tsaw.baseVol;
                break;
            case 4:
                statePtr->maxCount = 256 - oscRate;
                statePtr->curCount = 0;
                statePtr->data.tsaw.baseVol = 127 - oscDepth;
                statePtr->data.tsaw.depth = oscDepth;
                *initVal = (f32) statePtr->data.tsaw.baseVol;
                break;
            case 0x80:
                statePtr->data.vsin.depthcents = func_802679C0(oscDepth);
                statePtr->curCount = 0;
                statePtr->maxCount = 259 - oscRate;
                *initVal = 1.0f;
                break;
            case 0x81: {
                s32 cents;
                statePtr->maxCount = 256 - oscRate;
                statePtr->curCount = statePtr->maxCount;
                statePtr->stateFlags = 0;
                cents = func_802679C0(oscDepth);
                statePtr->data.vsqr.loRatio = func_80298550(-cents);
                statePtr->data.vsqr.hiRatio = func_80298550(cents);
                *initVal = statePtr->data.vsqr.hiRatio;
            } break;
            case 0x82: {
                s32 cents;
                statePtr->maxCount = 256 - oscRate;
                statePtr->curCount = statePtr->maxCount;
                cents = func_802679C0(oscDepth);
                statePtr->data.vdsaw.hicents = cents;
                statePtr->data.vdsaw.centsrange = 2 * cents;
                *initVal = func_80298550(statePtr->data.vdsaw.hicents);
            } break;
            case 0x83: {
                s32 cents;
                statePtr->maxCount = 256 - oscRate;
                statePtr->curCount = statePtr->maxCount;
                cents = func_802679C0(oscDepth);
                statePtr->data.vasaw.locents = -cents;
                statePtr->data.vasaw.centsrange = 2 * cents;
                *initVal = func_80298550(statePtr->data.vasaw.locents);
            } break;
            default:
                deltaTime = 255 << 14;
        }
    }
    return deltaTime;
}

s16 func_8026A754(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;

    func_80297D80(D_802AD1F8, D_802AD130, 0x32);
    D_802AD210 = arg3;
    D_802AD214 = arg4;
    func_802983D0(D_802AD120, D_802AD210, D_802AD214);
    M2C_FIELD(D_802A1278, s32 *, 0x14) = arg2;
    M2C_FIELD(D_802A1254, s8 *, 0x1C) = 6;
    M2C_FIELD(D_802A1254, M2C_UNK **, 0x20) = D_802A12C8;
    M2C_FIELD(D_802A1278, s32 *, 0x18) = arg0;
    M2C_FIELD(D_802A1278, s32 *, 0x1C) = arg1;
    M2C_FIELD(D_802A1278, s32 *, 0x10) = (s32) D_802A1250;
    temp_v0_3 = func_8026B9CC(D_802A1254, D_802A1278);
    if (temp_v0_3 != 0) {
        return temp_v0_3;
    }
    temp_v0_2 = func_8026A164();
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = func_80269AFC();
    if (temp_v0 != 0) {
        return temp_v0;
    }
    D_802AD218 = 0;
    func_802983A8(D_802AD218);
    return 0;
}

s16 func_8026A5BC() {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;

    if (D_802AD238 == 1) {
        func_80298640(D_802AD220);
    }
    if (D_802AD24C == 1) {
        D_802AD24C = 0;
    }
    D_802AD3C0 = 0;
    func_80266B50();
    if (D_802AD238 != 0) {
        do {

        } while (D_802AD238 != 0);
    }
    if (D_802AD660 != 0) {
        do {

        } while (D_802AD660 != 0);
    }
    func_80298620(D_802AD220);
    func_802986D8(D_802AD64C);
    func_8026B7A8(2);
    func_8026B7D4();
    func_802983D0(D_802AD120, D_802AD210, D_802AD214);
    M2C_FIELD(D_802A1278, s32 *, 0x14) = 0;
    M2C_FIELD(D_802A1278, s32 *, 0x10) = (s32) D_802A1250;
    temp_v0_3 = func_8026B9CC(D_802A1254, D_802A1278);
    if (temp_v0_3 != 0) {
        return temp_v0_3;
    }
    temp_v0_2 = func_8026A164();
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = func_80269AFC();
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

static s16 func_8026A164() {
    s16 count;
    u32 maxLen;
    u32 bankLen;
    u32 i;
    oscData *os;
    u32 n;

    D_802AD220 = func_8026B72C(0x7C);
    if (D_802AD220 == NULL) {
        return 1;
    }
    func_80298618(D_802AD220, &D_802A1298);
    D_802AD24C = 0;
    D_802AD238 = 0;
    D_802AD23C = 0.0f;
    D_802AD24A = 0x7FFF;
    D_802AD3C0 = 0;
    D_802AD234 = 0;
    if (D_802A1330 == 0) {
        return 0;
    }
    if (func_8026A108(4) != 0) {
        return 1;
    }
    count = D_802AD22C->seqCount;
    switch (D_802AD22C->revision) {
        case 0x5331:
            n = count;
            if (func_8026A108(n * 8 + 4) != 0) {
                return 1;
            }
            func_802983F0(D_802AD22C, (void *) D_802A1330);
            maxLen = 0;
            for (i = 0; i < count; i++) {
                if (maxLen < (u32) D_802AD22C->seqArray[i].len) {
                    maxLen = D_802AD22C->seqArray[i].len;
                }
            }
            bankLen = D_802A133C - D_802A1338;
            break;
        case 0x5332:
            n = count;
            if (func_8026A108(n * 0x18 + 4) != 0) {
                return 1;
            }
            D_802AD230 = (SeqInfo *) &D_802AD22C->seqArray[count];
            maxLen = 0;
            bankLen = 0;
            for (i = 0; i < count; i++) {
                if (D_802AD22C->seqArray[i].len >= 0) {
                    D_802AD22C->seqArray[i].offset += D_802A1330;
                    D_802AD230[i].bankRom += D_802A1330;
                    D_802AD230[i].table += D_802A1330;
                    if (bankLen < D_802AD230[i].bankLen) {
                        bankLen = D_802AD230[i].bankLen;
                    }
                    if (maxLen < (u32) D_802AD22C->seqArray[i].len) {
                        maxLen = D_802AD22C->seqArray[i].len;
                    }
                }
            }
            break;
        default:
            maxLen = D_802A1334 - D_802A1330;
            bankLen = D_802A133C - D_802A1338;
            D_802AD22C->seqCount = 1;
    }
    if (bankLen == 0 || maxLen == 0) {
        D_802A1330 = 0;
        return 0;
    }
    D_802AD228 = func_8026B72C(0xF8);
    if (D_802AD228 == NULL) {
        return 1;
    }
    if (maxLen & 1) {
        maxLen++;
    }
    D_802AD224 = func_8026B72C(maxLen);
    if (D_802AD224 == NULL) {
        return 1;
    }
    if (bankLen & 1) {
        bankLen++;
    }
    D_802AD21C = func_8026B72C(bankLen);
    if (D_802AD21C == NULL) {
        return 1;
    }
    os = &D_802AD3C8[0];
    D_802AD3C4 = os;
    for (i = 0; i < 31; i++) {
        os->next = &D_802AD3C8[i + 1];
        os = os->next;
    }
    os->next = NULL;
    return 0;
}

static s32 func_8026A108(s32 size) {
    SeqFile *p;

    if (size & 1) {
        size++;
    }
    p = D_802AD22C = func_8026B72C(size);
    if (p == NULL) {
        return 1;
    }
    func_80269144(p, size, D_802A1330);
    return 0;
}

static s32 func_80269A84(SndHeader *hdr);
static s32 func_80269A7C(SndHeader *hdr);
static s16 func_80269AFC() {
    s32 i;
    s32 j;
    s16 k;
    s32 rc;
    s32 size;
    s32 rom;
    SndHeader *hdr;
    SndSound *snd;
    SndWave *wave;

    D_802AD658 = NULL;
    D_802A12BC = D_802A12B4 + D_802A12B8;
    D_802AD64C = func_8026B72C(0x54);
    if (D_802AD64C == NULL) {
        return 1;
    }
    func_802986D0(D_802AD64C, &D_802A12BC);
    size = D_802A12BC * sizeof(Voice);
    D_802AD654 = func_8026B72C(size);
    if (D_802AD654 == NULL) {
        return 1;
    }
    D_802AD670 = 0;
    D_802AD672 = 0x7FFF;
    D_802AD674 = 0x40;
    D_802AD675 = 0;
    D_802AD66E = 0x7FFF;
    D_802AD664 = 0.0f;
    for (i = 0; i < D_802A12BC; i++) {
        Voice *v = &D_802AD654[i];
        v->state = 0;
        v->flags = 0;
        v->sndId = -1;
        v->unk1A = 0;
        v->unk14 = D_802AD672;
        v->unk18 = v->unk19 = D_802AD674;
        v->unk1E = D_802AD675;
        v->unk10 = v->unk12 = D_802AD670;
        v->unk1F = 0;
    }
    D_802AD660 = 0;
    if (func_80269A8C(4) != 0) {
        return 1;
    }
    switch (D_802AD650->magic) {
        case 0x5431:
            if (D_802A1348 == 0) {
                return 0;
            }
            size = D_802AD650->count * 8 + 4;
            if (func_80269A8C(size) != 0) {
                return 1;
            }
            rc = func_802699C8();
            if (rc != 0) {
                return rc - 1;
            }
            break;
        case 0x5432:
            size = D_802AD650->count * 8 + 4;
            if (func_80269A8C(size) != 0) {
                return 1;
            }
            rom = D_802A1344 + size + size % 8;
            hdr = func_8026B72C(0x1C);
            if (hdr == NULL) {
                return 1;
            }
            func_80269144(hdr, 0x1C, rom);
            rc = func_80269A84(hdr);
            if (rc != 0) {
                return rc - 1;
            }
            rc = func_80269A7C(hdr);
            if (rc != 0) {
                return rc - 1;
            }
            break;
        default:
            if (D_802A1348 == 0) {
                return 0;
            }
            rc = func_802699C8();
            if (rc != 0) {
                return rc - 1;
            }
            D_802AD650->count = func_802699C0();
            break;
    }
    return 0;
}

static s32 func_80269A8C(s32 size) {
    SndTable *p;

    if (size & 1) {
        size++;
    }
    p = D_802AD650 = func_8026B72C(size);
    if (p == NULL) {
        return 1;
    }
    if (D_802A1344 == 0) {
        p->magic = 0;
    } else {
        func_80269144(p, size, D_802A1344);
    }
    return 0;
}

static s32 func_80269A84(SndHeader *hdr) {
    s32 size;
    s32 k;
    SndSound *snd;
    SndWave *wave;

    hdr->rom += D_802A1344;
    hdr->table += D_802A1344;
    size = hdr->len;
    if (size == 0) {
        D_802A1348 = 0;
        return 1;
    }
    if (size & 1) {
        size++;
    }
    D_802AD648 = func_8026B72C(size);
    if (D_802AD648 == NULL) {
        return 2;
    }
    D_802A1348 = hdr->rom;
    func_80269144(D_802AD648, size, D_802A1348);
    for (k = 0; k < hdr->count; k++) {
        snd = (SndSound *) ((u8 *) D_802AD648 + k * 16);
        if (snd->flags != 0) {
            continue;
        }
        snd->flags = 1;
        snd->envelope = (u8 *) snd->envelope + (u32) D_802AD648;
        wave = snd->wavetable = (SndWave *) ((u8 *) snd->wavetable + (u32) D_802AD648);
        if (wave->flags != 0) {
            continue;
        }
        wave->flags = 1;
        wave->base += hdr->table;
        wave->book = (u8 *) wave->book + (u32) D_802AD648;
        if (wave->loop != NULL) {
            wave->loop = (u8 *) wave->loop + (u32) D_802AD648;
        }
    }
    return 0;
}

static s32 func_80269A7C(SndHeader *hdr) {
    s16 total;
    s16 i;

    if (hdr->scriptRom == 0) {
        return 1;
    }
    total = hdr->scriptLen;
    if (total == 0) {
        return 1;
    }
    if (total & 1) {
        total++;
    }
    D_802AD658 = func_8026B72C(total);
    if (D_802AD658 == NULL) {
        return 2;
    }
    hdr->scriptRom += D_802A1344;
    func_80269144(D_802AD658, total, hdr->scriptRom);
    *D_802AD658 = (u16 *) ((u8 *) *D_802AD658 + (u32) D_802AD658);
    total = D_802A12BC * sizeof(VoiceScript);
    D_802AD65C = func_8026B72C(total);
    if (D_802AD65C == NULL) {
        return 2;
    }
    for (i = 0; i < D_802A12BC; i++) {
        VoiceScript *s = &D_802AD65C[i];
        s->script = -1;
        s->flags = 0;
    }
    return 0;
}

static s16 func_802699C0() {
    s16 total;
    s16 bi;
    s16 ii;
    SndBankFile *f;
    SndBank *bank;
    SndInst *inst;

    total = 0;
    f = D_802AD648;
    for (bi = 0; bi < f->bankCount; bi++) {
        bank = f->bankArray[bi];
        for (ii = 0; ii < bank->instCount; ii++) {
            inst = bank->instArray[ii];
            total += inst->soundCount;
        }
    }
    return total;
}

static s32 func_802699C8() {
    SndBankFile *p;
    s32 size;

    size = D_802A134C - D_802A1348;
    if (size == 0) {
        D_802A1348 = 0;
        return 1;
    }
    if (size & 1) {
        size += 1;
    }
    p = D_802AD648 = func_8026B72C(size);
    if (p == NULL) {
        return 2;
    }
    func_80269144(p, size, D_802A1348);
    p = D_802AD648;
    if (p->revision != 0x4231) {
        D_802A1348 = 0;
        return 1;
    }
    func_802983E8(p, (void *) D_802A1350);
    return 0;
}

void func_80269908(u8 *arg0) {
    M2C_FIELD(D_802A1254, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(D_802A1254, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(D_802A1254, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(D_802A1254, u8 *, 0x1C) = (u8) M2C_FIELD(arg0, u8 *, 0x10);
    M2C_FIELD(D_802A1254, s32 *, 0x20) = (s32) M2C_FIELD(arg0, s32 *, 0x14);
    M2C_FIELD(D_802A1298, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
    M2C_FIELD(D_802A1298, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
    D_802A12B4 = M2C_FIELD(arg0, s32 *, 0x20);
    D_802A12B8 = M2C_FIELD(arg0, s32 *, 0x24);
    D_802A12C0 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(D_802A1278, u16 *, 0) = (u16) M2C_FIELD(arg0, u16 *, 0x2C);
    M2C_FIELD(D_802A1278, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x30);
    M2C_FIELD(D_802A1278, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x34);
    M2C_FIELD(D_802A1278, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x38);
    D_802A1250 = M2C_FIELD(arg0, s32 *, 0xC);
}

void func_8026984C(u8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(D_802A1254, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(D_802A1254, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(D_802A1254, s32 *, 8);
    M2C_FIELD(arg0, u8 *, 0x10) = (u8) M2C_FIELD(D_802A1254, u8 *, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(D_802A1254, s32 *, 0x20);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(D_802A1298, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(D_802A1298, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) D_802A12B4;
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) D_802A12B8;
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) D_802A12C0;
    M2C_FIELD(arg0, u16 *, 0x2C) = (u16) M2C_FIELD(D_802A1278, u16 *, 0);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(D_802A1278, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) M2C_FIELD(D_802A1278, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) M2C_FIELD(D_802A1278, s32 *, 0xC);
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) D_802A1250;
}

s32 func_80269840() {
    return 0x640013;
}

typedef struct SndHeap { u8 *base; u8 *cur; s32 len; } SndHeap;
s32 func_80269820() {
    SndHeap *h;
    s32 used;

    h = (SndHeap *) D_802AD120;
    used = h->len - (h->cur - h->base);
    return used;
}

s32 func_80269800() {
    return *func_8026B79C();
}

s32 func_802697E0() {
    return M2C_FIELD(func_8026B79C(), s32 *, 4);
}

s32 func_802697C0() {
    return M2C_FIELD(func_8026B79C(), s32 *, 8);
}

s32 func_802697A0() {
    return M2C_FIELD(func_8026B79C(), s32 *, 0xC);
}

void func_80269704(u8 arg0) {
    Voice *v;
    s32 i;

    D_802AD218 = 0;
    D_802AD218 |= (u8) (arg0 & 1);
    func_802983A8(D_802AD218);
    for (i = 0; i < D_802A12BC; i++) {
        v = &D_802AD654[i];
        if (v->state != 1) {
            continue;
        }
        v->flags |= 4;
    }
}

s16 *func_80269680(u32 arg0) {
    u8 *sp4;                                      /* compiler-managed */

    switch (arg0) {
    case 0:
        sp4 = D_802AD220;
        break;
    case 1:
        sp4 = D_802AD64C;
        break;
    case 2:
        sp4 = D_802AD21C;
        break;
    case 3:
        sp4 = D_802AD654;
        break;
    case 4:
        sp4 = D_802AD65C;
        break;
    }
    return (s16 *) sp4;
}

void func_802691A8() {
    s16 vol;
    u8 st;

    D_802AD238 = func_80298648(D_802AD220);
    if (D_802AD24C == 1 && D_802AD238 == 0) {
        func_802691A0();
        D_802AD24C = 0;
    }
    if (D_802AD238 != 0) {
        if (D_802AD23C > 0.0f) {
            D_802AD240 += D_802AD23C;
            if (D_802AD24A <= D_802AD240) {
                if (D_802AD238 == 1) {
                    func_80298640(D_802AD220);
                }
                D_802AD23C = 0.0f;
                D_802AD3C0 = 0;
                st = D_802AD24C;
                if ((st ^ 1) == 0) {
                    D_802AD24C = 0;
                }
            } else if (D_802AD240 != 0.0f) {
                vol = D_802AD24A - D_802AD240;
                if (vol != D_802AD246) {
                    func_80298670(D_802AD220, (vol * D_802AD248) / 32767); D_802AD246 = vol;
                }
            }
        }
        if (D_802AD23C < 0.0f) {
            D_802AD240 -= D_802AD23C;
            vol = D_802AD24A;
            if (D_802AD24A <= D_802AD240) {
                D_802AD23C = 0.0f;
            } else {
                vol = D_802AD240;
            }
            if (vol != D_802AD246) {
                func_80298670(D_802AD220, (vol * D_802AD248) / 32767);
                D_802AD246 = vol;
            }
        }
    }
}

static void func_802691A0(void) {
    s32 len;
    SeqData *sd;
    SeqInfo *info;
    s32 rom;
    s32 table;
    u8 bank;

    if (D_802AD22C->revision) {}
    if (D_802AD22C->revision == 0x5331 || D_802AD22C->revision == 0x5332) {
        sd = &D_802AD22C->seqArray[D_802AD244];
        len = sd->len;
        if (len & 1) {
            len++;
        }
        func_80269144(D_802AD224, len, (s32) sd->offset);
    } else {
        len = D_802A1334 - D_802A1330;
        if (len & 1) {
            len++;
        }
        func_80269144(D_802AD224, len, D_802A1330);
    }
    func_80298510(D_802AD228, D_802AD224);
    if (D_802AD22C->revision == 0x5332) {
        info = &D_802AD230[D_802AD244];
        rom = info->bankRom;
        table = info->table;
        len = info->bankLen;
        bank = info->bank;
    } else {
        rom = D_802A1338;
        table = D_802A1340;
        len = D_802A133C - rom;
        bank = 0;
        if (len & 1) {
            len++;
        }
    }
    if (rom == D_802AD234) {
        goto play;
    }
    func_80269144(D_802AD21C, len, rom);
    if (D_802AD21C->revision == 0x4231) {
        func_802983E8(D_802AD21C, (void *) table);
        D_802AD234 = rom;
play:
        func_80298650(D_802AD220, D_802AD21C->bankArray[bank]);
        func_80298628(D_802AD220, D_802AD228);
        func_80298670(D_802AD220, (D_802AD24A * D_802AD248) / 32767);
        func_80298638(D_802AD220);
        D_802AD23C = 0;
        D_802AD3C0 = 0;
        D_802AD238 = 1;
    }
}

static void func_80269144(void *dst, s32 size, s32 rom) {
    struct {
        u32 w[6];
    } mb; /* OSIoMesg */

    func_80297D50(dst, (void *) size);
    func_80298028(&mb, 0, 0, rom, dst, size, D_802AD1F8);
    func_80297D90(D_802AD1F8, NULL, 1);
}

void func_8026910C() {
    func_80298640(D_802AD220);
    func_80298620(D_802AD220);
}

void func_802690DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    D_802A1330 = arg0;
    D_802A1334 = arg1;
    D_802A1338 = arg2;
    D_802A133C = arg3;
    D_802A1340 = arg4;
}

s32 func_80268F94(s16 num) {
    s8 vol;

    if (D_802A1330 == 0) {
        return -1;
    }
    if (num >= D_802AD22C->seqCount || num < 0) {
        return -1;
    }
    switch (D_802AD22C->revision) {
        case 0x5332:
            if (D_802AD22C->seqArray[num].len < 0) {
                return -1;
            }
            vol = D_802AD230[num].vol;
            break;
        case 0x5331:
            if (D_802AD22C->seqArray[num].len < 0) {
                return -1;
            }
        default:
            vol = 0x7F;
            break;
    }
    D_802AD248 = func_80265FBC(vol);
    if (D_802AD238 == 1 && D_802AD24C == 0) {
        func_80298640(D_802AD220);
    } else {
        D_802AD238 = 1;
    }
    D_802AD244 = num;
    D_802AD24C = 1;
    return 0;
}

s32 func_80268F70() {
    s32 var_v1;

    var_v1 = D_802AD238;
    if (D_802AD3C0 != 0) {
        var_v1 = 0x100;
    }
    return var_v1;
}

s16 func_80268F3C() {
    if (D_802A1330 == 0) {
        return 0;
    }
    return D_802AD22C->seqCount;
}

void func_80268EE4() {
    if (D_802AD238 == 1) {
        func_80298640(D_802AD220);
    }
    if (D_802AD24C == 1) {
        D_802AD24C = 0;
    }
    D_802AD3C0 = 0;
}

void func_80268E7C(s16 arg0) {
    if (D_802AD238 != 0) {
        if (arg0 < 0) {
            arg0 = 1;
        }
        D_802AD23C = (f32) D_802AD24A / (f32) arg0;
        D_802AD240 = 0.0f;
        D_802AD246 = D_802AD24A;
    }
}

void func_80268E0C(s8 arg0) {
    D_802AD248 = func_80265FBC(arg0);
    func_80298670(D_802AD220, (s16) ((s32) (D_802AD24A * D_802AD248) / 32767));
}

void func_80268D94(s8 arg0) {
    D_802AD24A = func_80265FBC(arg0);
    func_80298670(D_802AD220, (s16) ((s32) (D_802AD24A * D_802AD248) / 32767));
    D_802AD23C = 0.0f;
}

s8 func_80268D6C() {
    return (s8) ((s16) D_802AD248 / 256);
}

void func_80268C54() {
    s32 i;

    if (D_802AD3C0 == 0 && D_802AD238 != 0 && ((D_802AD238 & 0xF) || D_802AD24C != 1)) {
    for (i = 0; i < 16; i++) {
        D_802AD340[i].prog = func_80298680(D_802AD220, i);
        D_802AD340[i].fxmix = func_802986B0(D_802AD220, i);
        D_802AD340[i].vol = func_802986A0(D_802AD220, i);
        D_802AD340[i].pan = func_802986C0(D_802AD220, i);
        D_802AD340[i].prio = func_80298690(D_802AD220, i);
    }
        D_802AD3C0 = func_80268BB8();
        func_80298548(D_802AD228, D_802AD250);
        func_80298640(D_802AD220);
    }
}

s16 func_80268BB8() {
    s32 temp_v0;

    if (D_802A1330 == 0) {
        return 0;
    }
    temp_v0 = func_80298660(D_802AD220);
    if (temp_v0 == 0) {
        return 0;
    }
    return (s16) (s32) (60.0f / ((f32) temp_v0 / 1000000.0f));
}

void func_80268A40(s16 arg0) {
    s32 i;

    if (D_802AD3C0 != 0) {
        func_80298638(D_802AD220);
        D_802AD238 = 1;
        for (i = 0; i < 16; i++) {
            func_80298678(D_802AD220, i, D_802AD340[i].prog);
            func_802986A8(D_802AD220, i, D_802AD340[i].fxmix);
            func_80298698(D_802AD220, i, D_802AD340[i].vol);
            func_802986B8(D_802AD220, i, D_802AD340[i].pan);
            func_80298688(D_802AD220, i, D_802AD340[i].prio);
        }
        func_802689B4(D_802AD3C0);
        func_80298540(D_802AD228, D_802AD250);
        D_802AD3C0 = 0;
        if (arg0 != 0 && !(D_802AD23C > 0.0f)) {
            D_802AD23C = -((f32) D_802AD24A / (f32) arg0);
            D_802AD240 = 0.0f;
            D_802AD246 = 0;
            func_80298670(D_802AD220, 0);
        }
    }
}

void func_802689B4(s16 arg0) {
    if (arg0 <= 0) {
        arg0 = 1;
    }
    func_80298658(D_802AD220, (s32) ((60.0f / (f32) arg0) * 1000.0f * 1000.0f));
}

void func_802686B8() {
    Voice *v;
    s16 i;

    D_802AD660 = 0;
    for (i = 0; i < D_802A12BC; i++) {
        v = &D_802AD654[i];
        if (v->sndId >= 0) {
            func_802986F0(D_802AD64C, v->sndId);
            v->state = func_80298740(D_802AD64C);
            switch (v->state) {
                case 0:
                    func_802986E8(D_802AD64C, v->sndId);
                    v->sndId = -1;
                    if (!(v->flags & 0x1000)) {
                        v->unk1F = 0;
                    }
                    v->flags &= ~0x2000;
                    break;
                case 2:
                    if (v->flags & 0x1000) {
                        v->state = 1;
                    } else {
                        v->unk1F = 0;
                    }
                    v->flags &= ~0x2000;
                    D_802AD660++;
                    break;
                case 1:
                    if (v->flags & 0x2000) {
                        func_80298710(D_802AD64C);
                    } else {
                        func_80267A18(i);
                    }
                    D_802AD660++;
                    break;
            }
        }
        if ((v->flags & 0x1000) && v->sndId < 0) {
            func_80268440(i);
            D_802AD660++;
        }
        if (v->flags & 0xF) {
            func_80267784(i);
        }
    }
    if (D_802AD664 > 0.0f) {
        D_802AD668 += D_802AD664;
        if (D_802AD66C <= D_802AD668) {
            func_80266B50();
            D_802AD664 = 0.0f;
        } else {
            i = D_802AD66C - D_802AD668;
            if (i != D_802AD66E) {
                D_802AD66E = i;
                func_802660B4();
            }
        }
    }
}

static void func_80268430(s16 idx, s16 script, s8 type) {
    VoiceScript *s;
    u16 *t;

    if (D_802AD658 != NULL) {
        s = &D_802AD65C[idx];
        if (type != 3) {
            s->parent = -1;
        }
        s->flags = 0;
        s->script = script;
        if (script >= 0) {
            t = *D_802AD658;
            s->pc = (u8 *) D_802AD658 + t[script];
            s->wait = 0;
            s->nchild = 0;
            s->loop = 0;
            s->unk26 = 0;
            s->unkE = 0;
            s->unk10 = 0x7F;
            s->unk12 = 0x40;
        }
    }
}

static void *func_80268438(s16 num) {
    SndBank *bank;
    SndInst *inst;
    s16 n;
    s16 i;
    s16 j;
    s16 k;
    void *snd;

    n = 0;
    for (i = 0; i < D_802AD648->bankCount; i++) {
        bank = D_802AD648->bankArray[i];
        for (j = 0; j < bank->instCount; j++) {
            inst = bank->instArray[j];
            for (k = 0; k < inst->soundCount; k++) {
                snd = inst->soundArray[k];
                if (n == num) {
                    return snd;
                }
                n++;
            }
        }
    }
    return NULL;
}

static void func_80268440(s16 idx) {
    Voice *v;
    SndDef def;
    s32 pad[2];

    v = &D_802AD654[idx];
    v->flags &= ~0x1000;
    v->state = 0;
    if (D_802AD650->magic == 0x5431 || D_802AD650->magic == 0x5432) {
        func_8026706C(v->num, &def);
        v->sound = def.sound;
    } else {
        v->sound = func_80268438(v->num);
        def.script = -1;
    }
    if (v->sound != NULL) {
        v->sndId = func_802986E0(D_802AD64C, v->sound);
        if (v->sndId >= 0) {
            func_80298730(D_802AD64C, v->sndId, v->unk1A + 11);
            func_80268430(idx, def.script, v->unk1F);
            func_80267A18(idx);
            v->flags |= 0xF;
            func_80267784(idx);
            func_80298700(D_802AD64C);
            v->state = 1;
        }
    }
}

static void func_80267A18(s16 idx) {
    VoiceScript *s;
    Voice *v;
    u8 *pc;
    s16 num;
    s16 ch;

    if (D_802AD658 != NULL) {
        s = &D_802AD65C[idx];
        if (s->script >= 0) {
            v = &D_802AD654[idx];
            pc = s->pc;
            while (s->wait == 0) {
                s32 op = pc[0];
                s->wait = (pc[1] << 8) + pc[2];
                pc += 3;
                if (op == 0x105) {}
                if (op == ~2) {}
                switch (op - 0x80) {
                    case 3:
                        num = (pc[0] << 8) + pc[1];
                        pc += 2;
                        if (num != v->num && s->parent < 0 && s->nchild < 3) {
                            ch = func_80267A10(num);
                            if (ch >= 0 && ch != idx) {
                                ch = func_8026724C(num);
                                s->child[s->nchild] = ch;
                                s->nchild++;
                                D_802AD654[ch].unk1F = 3;
                                D_802AD65C[ch].parent = idx;
                                D_802AD654[ch].unk14 = v->unk14;
                                D_802AD654[ch].unk18 = v->unk18;
                                D_802AD654[ch].unk10 = v->unk10;
                                D_802AD654[ch].unk1E = v->unk1E;
                            }
                        }
                        break;
                    case 4: {
                        u8 *lp = &s->loop;
                        if (*lp == 1) {
                            *lp = 0;
                            pc += 3;
                            break;
                        }
                        if (*lp != 0) {
                            (*lp)--;
                        } else if (pc[0] == 0) {
                            pc += 3;
                            break;
                        } else {
                            *lp = pc[0];
                        }
                        pc = (s16) ((pc[1] << 8) + pc[2]) + pc;
                        pc -= 3;
                        break;
                    }
                    case 5:
                        pc = (s16) ((pc[0] << 8) + pc[1]) + pc - 3;
                        break;
                    case 8:
                        s->unk1D = pc[0];
                        s->unk1F = pc[1];
                        s->unk1E = pc[2];
                        pc += 3;
                        break;
                    case 16:
                        s->unk10 = pc[0];
                        pc += 1;
                        break;
                    case 17:
                        s->unk10 += (s8) pc[0];
                        pc += 1;
                        break;
                    case 24:
                        s->unk12 = pc[0];
                        pc += 1;
                        break;
                    case 25:
                        s->unk12 += (s8) pc[0];
                        pc += 1;
                        break;
                    case 26:
                        if (*pc++ & 1) {
                            s->flags |= 8;
                        } else {
                            s->flags |= 0x10;
                        }
                        s->unk30 = (pc[0] << 8) + pc[1];
                        pc += 2;
                        s->unk2E = (s->unk30 * s->unk12) / 127;
                        break;
                    case 32:
                        s->unkE = (pc[0] << 8) + pc[1];
                        pc += 2;
                        break;
                    case 33:
                        s->unkE += (s16) ((pc[0] << 8) + pc[1]);
                        pc += 2;
                        break;
                    case 34:
                        if (*pc++) {
                            s->unk22 = 0x105 - s->unk1F;
                            s->unk24 = (s16) func_802679C0(s->unk1E) >> 1;
                            s->unk20 = 0;
                            s->flags |= 2;
                        } else {
                            s->flags &= ~2;
                        }
                        break;
                    case 35:
                        s->unk26 = pc[0];
                        s->unk28 = (pc[1] << 8) + pc[2];
                        s->unk2C = (pc[3] << 8) + pc[4];
                        s->unk2A = 0;
                        pc += 5;
                        break;
                    case 40:
                        v->unk1E = *pc++;
                        v->flags |= 8;
                        break;
                    case 0:
                        s->flags |= 0x100;
                    case 1:
                        s->flags |= 0x200;
                        s->script = -1;
                        s->wait = 1;
                        break;
                    default:
                        s->flags |= 0x300;
                        s->script = -1;
                        s->wait = 1;
                        break;
                }
                if (idx) {}
            }
            s->wait--;
            s->pc = pc;
            func_802679A8(s);
            if (s->unkE >= 0x4B1) {
                s->unkE = 0x4B0;
            }
            if (v->unk12 != s->unkE) {
                v->unk12 = s->unkE;
                v->flags |= 1;
            }
            func_802679B0(s, v);
            func_802679A0(s, v);
            if (s->flags & 0x100) {
                while (s->nchild > 0) {
                    s->nchild--;
                    num = s->child[s->nchild];
                    if (idx == D_802AD65C[num].parent) {
                        v = &D_802AD654[num];
                        if (v->state == 1) {
                            if (v->flags & 0x1000) {
                                v->flags &= ~0x1000;
                            } else {
                                func_802986F0(D_802AD64C, v->sndId);
                                func_80298710(D_802AD64C);
                                v->flags |= 0x2000;
                            }
                            v->unk1F = 0;
                            {
                                VoiceScript *cs = &D_802AD65C[num];
                                cs->script = -1;
                                cs->flags = 0;
                            }
                        }
                    }
                }
                v = &D_802AD654[idx];
                func_802986F0(D_802AD64C, v->sndId);
                func_80298710(D_802AD64C);
                v->unk1F = 0;
                v->flags |= 0x2000;
            }
        }
    }
}

static s16 func_80267A10(s16 num) {
    SndDef def;

    if (num >= D_802AD650->count || num < 0) {
        return -1;
    }
    func_8026706C(num, &def);
    return func_80266D8C(def.prio, 1);
}

static void func_802679B8(s16 *p, s16 lo, s16 hi) {
    if (*p < lo) {
        *p = lo;
    } else if (*p > hi) {
        *p = hi;
    }
}

static void func_802679A8(VoiceScript *s) {
    f32 f;
    f32 r;

    f = 0.0f;
    if (s->unk20 == 0) {
        s->unk32 = 0;
    }
    if ((s->flags & 2) && s->unk1D == 1) {
        if (s->unk20) {}
        s->unk20 += 2;
        if (s->unk20 >= s->unk22) {
            s->unk20 = 0;
            f = -s->unk32;
        } else {
            r = (f32) s->unk20 / (f32) s->unk22;
            f = sinf(r * 6.28318530000000042) * s->unk24;
            s->unk32 += (s16) f;
        }
    }
    if (s->unk26 == 1) {
        s->unk2A++;
        if (s->unk2A >= s->unk2C) {
            s->unk26 = 0;
            s->unkE += s->unk28;
            f = 0.1f;
        } else {
            r = (f32) s->unk2A / (f32) s->unk2C;
            f = s->unk28 * r + f;
        }
    }
    s->unkE += (s16) f;
}

static void func_802679B0(VoiceScript *s, Voice *v) {
    s16 vol;

    func_802679B8(&s->unk12, 0, 0x7F);
    if (s->flags & 0x18) {
        if (s->flags & 8) {
            s->unk2E++;
            if (s->unk2E >= s->unk30) {
                s->unk2E = s->unk30;
                s->flags &= ~8;
            }
        } else {
            s->unk2E--;
            if (s->unk2E <= 0) {
                s->unk2E = 0;
                s->flags &= ~0x10;
            }
        }
        vol = (s->unk2E * 127.0f) / s->unk30;
        func_802679B8(&vol, 0, 0x7F);
        s->unk12 = (u8) vol;
    }
    if (v->unk19 != s->unk12) {
        v->unk19 = s->unk12;
        v->flags |= 4;
    }
}

static void func_802679A0(VoiceScript *s, Voice *v) {
    s16 vol;

    func_802679B8(&s->unk10, 0, 0x7F);
    vol = func_80265FBC(s->unk10);
    if (vol != v->unk16) {
        v->unk16 = vol;
        v->flags |= 2;
    }
}

static f32 func_802679C0(u8 depth) {
    f32 x = 1.03099303;
    f32 cents = 1.0;

    while (depth) {
        if (depth & 1) {
            cents *= x;
        }
        x *= x;
        depth >>= 1;
    }
    return cents;
}

static void func_80267784(s16 arg0) {
    Voice *v;
    s16 vol;
    s16 pan;

    v = &D_802AD654[arg0];
    if (v->sndId >= 0) {
        func_802986F0(D_802AD64C, v->sndId);
        if (v->flags & 2) {
            vol = (v->unk16 * v->unk14) / 32767;
            func_80298718(D_802AD64C, (vol * D_802AD66E) / 32767);
            v->flags &= ~2;
        }
        if (v->flags & 1) {
            func_80298720(D_802AD64C, func_80298550(v->unk12 + v->unk10) * v->pitch);
            v->flags &= ~1;
        }
        if (v->flags & 8) {
            func_80298738(D_802AD64C, v->unk1E);
            v->flags &= ~8;
        }
        if (v->flags & 4) {
            if (D_802AD218 & 1) {
                func_80298728(D_802AD64C, 0x40);
            } else {
                pan = (v->unk18 + v->unk19) - 0x40;
                if (pan < 0) {
                    pan = 0;
                }
                if (pan >= 0x80) {
                    pan = 0x7F;
                }
                func_80298728(D_802AD64C, pan);
            }
            v->flags &= ~4;
        }
    }
}

void func_80267754() {
    func_80266B50();
    func_802986D8(D_802AD64C);
}

void func_80267730(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_802A1344 = arg0;
    D_802A1348 = arg1;
    D_802A134C = arg2;
    D_802A1350 = arg3;
}

void func_80267654(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    if (arg0 >= 0) {
        D_802A1364 = arg0;
        if (D_802A1364 >= 0x168) {
            D_802A1364 = 0;
        }
    }
    if (arg1 >= 0.0f) {
        D_802A1354 = arg1;
    }
    if (arg2 >= 0.0f) {
        D_802A1358 = arg2 - arg1;
    }
    if (arg3 >= 0.0f) {
        D_802A135C = arg3;
    }
    if (arg4 >= 0.0f) {
        D_802A1360 = arg4 - D_802A135C;
        if (D_802A1360 < 0.0f) {
            D_802A1360 = 0.0f;
        }
    }
}

s16 func_802675F4(s16 arg0, s16 arg1, f32 arg2) {
    s16 v;

    v = func_8026724C(arg0);
    if (v < 0) {
        return -1;
    }
    func_80266644(v, arg1, arg2);
    return v;
}

s16 func_8026724C(s16 num) {
    Voice *v;
    VoiceScript *s;
    s16 idx;
    s16 ch;
    SndDef def;
    SndDef def2;

    if (D_802A1348 == 0) {
        return -1;
    }
    if (num >= D_802AD650->count || num < 0) {
        return -1;
    }
    if (D_802AD650->magic == 0x5431 || D_802AD650->magic == 0x5432) {
        func_8026706C(num, &def);
        idx = func_80266D8C(def.prio, 0);
        if (idx < 0) {
            return -1;
        }
        v = &D_802AD654[idx];
        v->unk1A = (def.prio >> 4) & 0xF;
    } else {
        idx = 0;
        v = &D_802AD654[0];
        v->unk1A = 5;
        def.vol = 0x7FFF;
        def.pan = 0x40;
        def.unkE = 0;
        def.script = -1;
        def.pitch = 1.0f;
    }
    if (v->state == 1 && !(v->flags & 0x1000)) {
        if (v->unk1F == 2) {
            s = &D_802AD65C[idx];
            while (s->nchild > 0) {
                s->nchild--;
                ch = s->child[s->nchild];
                if (idx == D_802AD65C[ch].parent) {
                    VOICE_STOP(ch);
                }
            }
            v = &D_802AD654[idx];
        }
        func_802986F0(D_802AD64C, v->sndId);
        func_80298710(D_802AD64C);
        if (D_802AD658 != NULL) {
            VoiceScript *p = &D_802AD65C[idx];
            p->script = -1;
            p->flags = 0;
        }
        v->flags = 0x2000;
    } else {
        v->flags = 0;
    }
    v->flags |= 0x1000;
    v->num = num;
    v->unk14 = D_802AD672;
    v->unk16 = def.vol;
    v->unk18 = D_802AD674;
    v->unk19 = def.pan;
    v->unk10 = D_802AD670;
    v->unk12 = 0;
    v->pitch = def.pitch;
    v->unk1D = def.unkE;
    v->state = 1;
    if (def.unkF != 0) {
        v->unk1E = 0;
        v->flags |= 0x10;
    } else {
        v->unk1E = D_802AD675;
    }
    if (def.script < 0) {
        v->unk1F = 1;
    } else {
        v->unk1F = 2;
    }
    return idx;
}

static void func_8026706C(s16 num, SndDef *def) {
    SndEntry *e;
    SndBankFile *f;
    SndBank *bank;
    SndInst *inst;
    u8 b;
    u8 i;
    u8 k;
    void *snd;
    s32 n;
    s32 m;

    e = &D_802AD650->entries[num];
    def->vol = 0x7FFF;
    def->pan = 0x40;
    def->prio = e->unk3;
    def->pitch = (f32) e->unk6 / (f32) D_802A1288;
    def->script = -1;
    def->unkF = 0;
    switch (D_802AD650->magic) {
        case 0x5431:
            f = D_802AD648;
            b = e->unk0;
            i = e->unk1;
            k = e->unk2;
            n = f->bankCount;
            if (n < b) {
                snd = NULL;
            } else {
                bank = f->bankArray[b];
                n = bank->instCount;
                if (n < i) {
                    snd = NULL;
                } else {
                    inst = bank->instArray[i];
                    m = inst->soundCount;
                    if (m < k) {
                        snd = NULL;
                    } else {
                        snd = inst->soundArray[k];
                    }
                }
            }
            def->sound = snd;
            def->unkE = 0;
            break;
        case 0x5432:
            def->sound = (u8 *) D_802AD648 + (e->unk4 & 0x7FFF) * 0x10;
            if (e->unk4 < 0) {
                def->unkF = 1;
            }
            if (e->unk0 >= 0) {
                def->vol = func_80267064(e->unk1 & 0x7F);
                def->pan = e->unk0;
            } else if (D_802AD658 != NULL) {
                def->script = ((u8) (e->unk0 & 0x7F) << 8) + (u8) e->unk1;
            }
            def->unkE = e->unk2;
            break;
    }
}

static s32 func_80267064(s8 vol) {
    s32 v;

    if (vol > 0) {
        v = (vol << 8) + 0xFF;
    } else {
        v = 0;
    }
    return v;
}

static s16 func_80266D8C(u8 prio, s32 arg1) {
    Voice *v;
    s32 i;
    s32 oldest;
    u8 min;
    u8 pr;
    static u8 D_802A1368 = 1;
    pr = (prio >> 4) & 0xF;
    i = prio & 0xF;
    if (D_802A12B8 == 0) {
        i = 0;
    }
    if (i != 0 || D_802A12B4 < 2) {
        if (D_802A12B8 < i) {
            return -1;
        }
        if (D_802A12B4 != 0) {
            i = D_802A12B4 + i - 1;
        }
        v = &D_802AD654[i];
        if (v->state == 1 && pr < v->unk1A) {
            return -1;
        }
        return i;
    }
    min = 0xFF;
    for (i = 0; i < D_802A12B4; i++) {
        v = &D_802AD654[i];
        if (v->state != 1) {
            break;
        }
        if (v->unk1C <= min) {
            min = v->unk1C;
            oldest = i;
        }
    }
    if (i == D_802A12B4) {
        v = &D_802AD654[oldest];
        i = oldest;
        if (pr < v->unk1A) {
            return -1;
        }
    }
    if (arg1 == 0) {
        v->unk1C = D_802A1368++;
        if (D_802A1368 == 0) {
            min = 0xFF;
            for (oldest = 0; oldest < D_802A12B4; oldest++) {
                v = &D_802AD654[oldest];
                if (v->state == 1 && v->unk1C < min) {
                    min = v->unk1C;
                }
            }
            arg1 = 0x100 - min;
            D_802A1368 = arg1;
            if (D_802A1368) {
                for (oldest = 0; oldest < D_802A12B4; oldest++) {
                    D_802AD654[oldest].unk1C += D_802A1368;
                }
            } else {
                for (oldest = 0; oldest < D_802A12B4; oldest++) {
                    v = &D_802AD654[oldest];
                    switch (v->unk1C) {
                        case 0:
                            v->unk1C = 1;
                            break;
                        case 0xFF:
                            v->unk1C = D_802A12B4;
                            break;
                        default:
                            v->unk1C = 2;
                    }
                }
                D_802A1368 = D_802A12B4 + 1;
            }
        }
    }
    return i;
}

s16 func_80266D0C(s16 arg0) {
    s16 i;
    Voice *v;

    for (i = 0; i < D_802A12BC; i++) {
        v = &D_802AD654[i];
        if (v->state != 0 && arg0 == v->num) {
            return i;
        }
    }
    return -1;
}

s32 func_80266CFC() {
    return D_802AD660;
}

u8 func_80266CD4(s16 arg0) {
    return D_802AD654[arg0].state;
}

s16 func_80266CA0() {
    if (D_802A1348 == 0) {
        return 0;
    }
    return D_802AD650->count;
}

void func_80266B50() {
    Voice *v;
    VoiceScript *s;
    s16 i;

    for (i = 0; i < D_802A12BC; i++) {
        v = &D_802AD654[i];
        if (v->state != 1) {
            continue;
        }
        if (v->flags & 0x1000) {
            v->flags &= ~0x1000;
        } else {
            func_802986F0(D_802AD64C, v->sndId);
            func_80298710(D_802AD64C);
            v->flags |= 0x2000;
        }
        if (D_802AD658 != NULL) {
            s = &D_802AD65C[i];
            s->script = -1;
            s->flags = 0;
        }
        v->unk1F = 0;
    }
}

static void func_80266928(s16 idx) {
    VoiceScript *s;

    s = &D_802AD65C[idx];
    s->script = -1;
    s->flags = 0;
}

void func_80266930(s16 idx) {
    Voice *v;
    VoiceScript *s;
    s16 c;

    v = &D_802AD654[idx];
    if (v->state == 1) {
        if (v->flags & 0x1000) {
            v->flags &= ~0x1000;
        } else {
            func_802986F0(D_802AD64C, v->sndId);
            func_80298710(D_802AD64C);
            v->flags |= 0x2000;
            if (v->unk1F == 2) {
                s = &D_802AD65C[idx];
                while (s->nchild > 0) {
                    s->nchild--;
                    c = s->child[s->nchild];
                    if (idx != D_802AD65C[c].parent) {
                        continue;
                    }
                    v = &D_802AD654[c];
                    if (v->state != 1) {
                        continue;
                    }
                    if (v->flags & 0x1000) {
                        v->flags &= ~0x1000;
                    } else {
                        func_802986F0(D_802AD64C, v->sndId);
                        func_80298710(D_802AD64C);
                        v->flags |= 0x2000;
                    }
                    v->unk1F = 0;
                    func_80266928(c);
                }
            }
        }
        D_802AD654[idx].unk1F = 0;
        if (D_802AD658 != NULL) {
            func_80266928(idx);
        }
    }
}

void func_802668D4(s16 arg0) {
    if (arg0 < 0) {
        arg0 = 1;
    }
    D_802AD664 = (f32) D_802AD66E / (f32) arg0;
    D_802AD668 = 0.0f;
    D_802AD66C = D_802AD66E;
}

void func_80266644(s16 idx, s16 angle, f32 dist) {
    f32 d;
    s16 vol;
    s8 c;
    u8 pan;

    d = dist - D_802A1354;
    if (d < 0.0f) {
        d = 0.0f;
    }
    vol = 0;
    if (d <= D_802A1358) {
        vol = (s16) (((D_802A1358 - d) * 128.0) / D_802A1358);
        if (vol >= 0x80) {
            vol = 0x7F;
        }
        c = D_802AD654[idx].unk1D;
        if (vol < (c & 0x7F)) {
            if (c & 0x80) {
                vol = c & 0x7F;
            } else {
                vol = 0;
            }
        }
    }
    angle += D_802A1364;
    if (angle >= 360) {
        angle -= 360;
    }
    if (angle > 180) {
        angle = 360 - angle;
    }
    pan = (angle << 7) / 180;
    if (pan >= 0x80) {
        pan = 0x7F;
    }
    if (D_802A1360 != 0.0f) {
        d = dist - D_802A135C;
        if (d < 0.0f) {
            d = 0.0f;
        }
        if (d < D_802A1360) {
            pan = 64.0f - (0x40 - pan) * (d / D_802A1360);
        }
    }
    func_80266510(idx, vol);
    func_802663E0(idx, pan);
}

void func_80266510(s16 idx, s8 vol) {
    Voice *v;
    VoiceScript *s;
    s16 i;

    func_80266508();
    if (!idx) {}
    v = &D_802AD654[idx];
    if (v->state == 1) {
        if (!(v->flags & 0x1000)) {
            v->flags |= 2;
            if (v->unk1F == 2) {
                s = &D_802AD65C[idx];
                i = s->nchild;
                while (i > 0) {
                    i--;
                    if (idx == D_802AD65C[s->child[i]].parent) {
                        func_80266510(s->child[i], vol);
                    }
                }
            }
        }
        v->unk14 = func_80265FBC(vol);
    }
}

static void func_80266508() {
}

void func_802663E0(s16 idx, u8 pan) {
    Voice *v;
    VoiceScript *s;
    s16 i;

    func_802663D8();
    if (!idx) {}
    v = &D_802AD654[idx];
    if (v->state == 1) {
        if (pan >= 0x80) {
            pan = 0x7F;
        }
        if (!(v->flags & 0x1000)) {
            v->flags |= 4;
            if (v->unk1F == 2) {
                s = &D_802AD65C[idx];
                i = s->nchild;
                while (i > 0) {
                    i--;
                    if (idx == D_802AD65C[s->child[i]].parent) {
                        func_802663E0(s->child[i], pan);
                    }
                }
            }
        }
        v->unk18 = pan;
    }
}

static void func_802663D8() {
}

void func_802662A0(s16 idx, s16 pitch) {
    Voice *v;
    VoiceScript *s;
    s16 i;

    func_80266298();
    if (!idx) {}
    v = &D_802AD654[idx];
    if (v->state == 1) {
        if (pitch >= 0x4B1) {
            pitch = 0x4B0;
        }
        if (!(v->flags & 0x1000)) {
            v->flags |= 1;
            if (v->unk1F == 2) {
                s = &D_802AD65C[idx];
                i = s->nchild;
                while (i > 0) {
                    i--;
                    if (idx == D_802AD65C[s->child[i]].parent) {
                        func_802662A0(s->child[i], pitch);
                    }
                }
            }
        }
        v->unk10 = pitch;
    }
}

static void func_80266298() {
}

void func_8026615C(s16 idx, s8 vol) {
    Voice *v;
    VoiceScript *s;
    s16 i;

    func_80266154();
    v = &D_802AD654[idx];
    if (v->state == 1 && !(v->flags & 0x10)) {
        if (vol < 0) {
            vol = 0;
        }
        if (!(v->flags & 0x1000)) {
            v->flags |= 8;
            if (v->unk1F == 2) {
                s = &D_802AD65C[idx];
                i = s->nchild;
                while (i > 0) {
                    i--;
                    if (idx == D_802AD65C[s->child[i]].parent) {
                        func_8026615C(s->child[i], vol);
                    }
                }
            }
        }
        v->unk1E = vol;
    }
}

static void func_80266154() {
}

void func_80266118(s8 arg0) {
    D_802AD66E = func_80265FBC(arg0);
    func_802660B4();
    D_802AD664 = 0.0f;
}

static void func_802660B4(void) {
    s32 i;
    Voice *v;

    if (0) {
        func_80298710(0);
    }
    for (i = 0; i < D_802A12BC; i++) {
        v = &D_802AD654[i];
        if (v->state == 1) {
            v->flags |= 2;
        }
    }
}

void func_80265FF8(s8 arg0) {
    s32 i;
    Voice *v;
    s32 t;

    D_802AD672 = func_80265FBC(arg0);
    for (i = 0; i < D_802A12BC; i++) {
        v = &D_802AD654[i];
        if (v->state == 1) {
            if (!(v->flags & 0x1000) && v->unk14 != D_802AD672) {
                v->flags |= 2;
            }
            v->unk14 = D_802AD672;
        }
    }
}

static s16 func_80265FBC(s8 arg0) {
    s32 v;

    if (0) {
        D_802AD218 = 0;
    }
    if (arg0 > 0) {
        v = (arg0 << 8) + 0xFF;
    } else {
        v = 0;
    }
    return v;
}

void func_80265F1C(u8 arg0) {
    s32 i;
    Voice *v;

    if (arg0 >= 0x80) {
        arg0 = 0x7F;
    }
    for (i = 0; i < D_802A12BC; i++) {
        v = &D_802AD654[i];
        if (v->state != 1) {
            continue;
        }
        if (!(v->flags & 0x1000) && v->unk18 != arg0) {
            v->flags |= 4;
        }
        v->unk18 = arg0;
    }
    D_802AD674 = arg0;
}

void func_80265E7C(s16 arg0) {
    s32 i;
    Voice *v;

    if (arg0 >= 0x4B1) {
        arg0 = 0x4B0;
    }
    for (i = 0; i < D_802A12BC; i++) {
        v = &D_802AD654[i];
        if (v->state != 1) {
            continue;
        }
        if (!(v->flags & 0x1000) && arg0 != v->unk10) {
            v->flags |= 1;
        }
        v->unk10 = arg0;
    }
    D_802AD670 = arg0;
}

void func_80265DD8(s8 arg0) {
    s32 i;
    Voice *v;

    if (arg0 < 0) {
        arg0 = 0;
    }
    for (i = 0; i < D_802A12BC; i++) {
        v = &D_802AD654[i];
        if (v->state != 1 || (v->flags & 0x10)) {
            continue;
        }
        if (!(v->flags & 0x1000) && v->unk1E != (u8) arg0) {
            v->flags |= 8;
        }
        v->unk1E = arg0;
    }
    D_802AD675 = arg0;
}

s8 func_80265DB0() {
    return (s8) ((s16) D_802AD672 / 256);
}

u8 func_80265DA0() {
    return D_802AD674;
}

s16 func_80265D90() {
    return D_802AD670;
}

s8 func_80265D80() {
    return D_802AD675;
}
