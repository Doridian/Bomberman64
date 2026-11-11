/*
 * NON_MATCHING: main_code's 85A10, complete first draft: the audio
 * manager, Hudson's version of the N64 SDK demos' audiomgr.c (the
 * manager D_802AD6A0 with its two command lists, three AudioInfos,
 * thread, frame and reply queues and ALGlobals; the DMA buffers
 * D_802AF930 and their callback; error flags and peaks D_802AD680).
 * src/85A10.c has every function GLOBAL_ASM: the object is -O3 (IPA
 * statics: func_8026B238 takes its two arguments in s6 and fp and uses
 * s-registers it never saves, so func_8026B584 saves all of them), so this
 * is the whole object, last function first. Every procedure is emitted in
 * the original's order and at its size. The `jr ra` stubs 8026B228/30 are
 * __amHandleDoneMsg (8026B584's, its `firstTime` D_802A1370 a
 * function-scope static) and __clearAudioDMA (8026B238's), inlined.
 * Not built into the ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 0, eu 0, jp 0
 *
 * jp's 8026B9CC has no osTvType test (always 60 fields a second).
 * Every function matches in all three versions (the object can move to
 * src/). What fixed the second pass:
 * - func_8026B9CC: locals declared i, fsize, buffs, err, fps (fps gets no
 *   slot below err); err = 0 first; the peaks zeroed in one chain, flags
 *   first (it uses up the three ugen temps the original's t-registers
 *   show); osCreateMesgQueue (func_80297D80) declared void, which moves
 *   amc's reloads from v1 to v0. The chained `D_802AF938 = D_802AF93C =
 *   D_802AF948 = 0` gives the original's address registers (v1, a2).
 * - the statics' run from func_8026B210: __amMain's locals in the SDK's
 *   order (done, msg, lastInfo) under an unused `s32 pad`;
 *   __clearAudioDMA's iomsg declared second; the task's flags set right
 *   after next.
 */
#include "common.h"

/* audiomgr.c's DMABuffer (an ALLink first) */
typedef struct UnkStruct_8026B804 {
    /* 0x00 */ struct UnkStruct_8026B804 *next;
    /* 0x04 */ struct UnkStruct_8026B804 *prev;
    /* 0x08 */ u32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ u8 *ptr;
} UnkStruct_8026B804; /* size 0x14 */

/* audiomgr.c's AMDMAState, without its initialized flag */
typedef struct {
    /* 0x00 */ UnkStruct_8026B804 *firstUsed;
    /* 0x04 */ UnkStruct_8026B804 *firstFree;
} UnkStruct_802AF930;

/* sched.h's OSScTask, its OSTask's fields flattened */
typedef struct {
    /* 0x00 */ void *next;
    /* 0x04 */ u32 state;
    /* 0x08 */ u32 flags;
    /* 0x0C */ void *framebuffer;
    /* 0x10 */ u32 type;
    /* 0x14 */ u32 taskFlags;
    /* 0x18 */ void *ucode_boot;
    /* 0x1C */ u32 ucode_boot_size;
    /* 0x20 */ void *ucode;
    /* 0x24 */ u32 ucode_size;
    /* 0x28 */ void *ucode_data;
    /* 0x2C */ u32 ucode_data_size;
    /* 0x30 */ void *dram_stack;
    /* 0x34 */ u32 dram_stack_size;
    /* 0x38 */ void *output_buff;
    /* 0x3C */ void *output_buff_size;
    /* 0x40 */ void *data_ptr;
    /* 0x44 */ u32 data_size;
    /* 0x48 */ void *yield_data_ptr;
    /* 0x4C */ u32 yield_data_size;
    /* 0x50 */ void *msgQ;
    /* 0x54 */ void *msg;
    /* 0x58 */ u8 unk58[0x10];
} UnkStruct_8026B238_8; /* size 0x68 */

/* audiomgr.c's AudioInfo */
typedef struct UnkStruct_8026B238 {
    /* 0x00 */ s16 *data;
    /* 0x04 */ s16 frameSamples;
    /* 0x08 */ UnkStruct_8026B238_8 task;
    /* 0x70 */ s16 msgType;
    /* 0x74 */ struct UnkStruct_8026B238 *msgInfo;
    /* 0x78 */ u8 unk78[0x18];
} UnkStruct_8026B238; /* size 0x90 */

/* audiomgr.h's AudioMsg */
typedef struct {
    /* 0x00 */ s16 type;
    /* 0x04 */ struct UnkStruct_8026B238 *info;
} UnkStruct_8026B584;

/* os.h's OSMesgQueue */
typedef struct {
    /* 0x00 */ void *mtqueue;
    /* 0x04 */ void *fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ void **msg;
} UnkStruct_802AD868; /* size 0x18 */

/* abi.h's Acmd */
typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} UnkStruct_802AD6A0_0; /* size 0x8 */

/* audiomgr.c's AMAudioMgr */
typedef struct {
    /* 0x000 */ UnkStruct_802AD6A0_0 *ACMDList[2];
    /* 0x008 */ UnkStruct_8026B238 *audioInfo[3];
    /* 0x018 */ u64 thread[0x1B0 / 8];
    /* 0x1C8 */ UnkStruct_802AD868 audioFrameMsgQ;
    /* 0x1E0 */ void *audioFrameMsgBuf[8];
    /* 0x200 */ UnkStruct_802AD868 audioReplyMsgQ;
    /* 0x218 */ void *audioReplyMsgBuf[8];
    /* 0x238 */ u8 g[1];
} UnkStruct_802AD6A0;

/* error flags (1 heap, 2 DMA, 4 AI underrun, 8 command list, 0x10 DMA
 * buffers) and peaks: DMAs per frame, buffers used, commands */
typedef struct {
    /* 0x00 */ u32 flags;
    /* 0x04 */ u32 maxDMAs;
    /* 0x08 */ u32 maxBuffers;
    /* 0x0C */ u32 maxCmds;
} UnkStruct_802AD680;

/* libaudio.h's ALSynConfig */
typedef struct {
    /* 0x00 */ s32 maxVVoices;
    /* 0x04 */ s32 maxPVoices;
    /* 0x08 */ s32 maxUpdates;
    /* 0x0C */ s32 maxFXbusses;
    /* 0x10 */ void *dmaproc;
    /* 0x14 */ void *heap;
    /* 0x18 */ s32 outputRate;
} UnkStruct_8026B9CC_0;

/* audiomgr.h's amConfig, Hudson's */
typedef struct {
    /* 0x00 */ u16 numDMABuffers;
    /* 0x04 */ s32 dmaBufferLength;
    /* 0x08 */ u32 framesPerField;
    /* 0x0C */ u32 maxACMDSize;
    /* 0x10 */ s32 outputRate;
    /* 0x14 */ void *sched;
    /* 0x18 */ s32 pri;
    /* 0x1C */ s32 id;
} UnkStruct_8026B9CC_1;

/* libaudio.h's ALHeap */
typedef struct {
    /* 0x00 */ u8 *base;
    /* 0x04 */ u8 *cur;
    /* 0x08 */ s32 len;
} UnkStruct_802AF928;

/* os.h's OSIoMesg */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
} UnkStruct_802AF960;

void *func_80297D48(void *);
void func_80297D80(void *, void *, s32);
s32 func_80297D90(void *, void *, s32);
s32 func_80297D98(void *, void *, s32);
void func_80297DA8(void *, s32, void *, void *, void *, s32);
void func_80297DB0(void *);
void func_80297DC8(void *);
void func_80297DF0(void *, void *, void *);
void *func_80297E00(void *);
u32 func_80297FB8(void);
s32 func_80297FC0(s32);
void func_80297FC8(void *, s32);
void func_80298028(void *, s32, s32, u32, void *, s32, void *);
s32 func_802983B0(void);
void func_802983B8(void *);
void func_802983C0(void *, void *);
void *func_802983D8(void *, s32, UnkStruct_802AF928 *, s32, s32);
void func_80298490(void *, void *);
void func_80298498(void *);
UnkStruct_802AD6A0_0 *func_802984A0(UnkStruct_802AD6A0_0 *, s32 *, void *, s32);
void func_80267754(void);
void func_802686B8(void);
void func_8026910C(void);
void func_802691A8(void);

extern u8 D_8029D250[];
extern u8 D_8029D320[];
extern u8 D_8029E750[];
extern u8 D_802A5040[];
extern UnkStruct_802AD680 D_802AD680;
extern void *D_802AD690;
extern u8 D_802AD698[];
extern UnkStruct_802AD6A0 D_802AD6A0;
extern UnkStruct_802AF928 *D_802AF928;
extern UnkStruct_802AF930 D_802AF930;
extern u32 D_802AF938;
extern u32 D_802AF93C;
extern u16 D_802AF940;
extern s32 D_802AF944;
extern s32 D_802AF948;
extern u32 D_802AF94C;
extern s32 D_802AF950;
extern u32 D_802AF954;
extern u32 D_802AF958;
extern u32 D_802AF95C;
extern UnkStruct_802AF960 D_802AF960[];
extern UnkStruct_802AD868 D_802AFBA0;
extern void *D_802AFBB8[];

void *func_8026B72C(s32 arg0);
static void func_8026B584(void *arg);
static s32 func_8026B804(s32 addr, s32 len, void *state);
static void *func_8026B210(UnkStruct_802AF930 **state);

s16 func_8026B9CC(UnkStruct_8026B9CC_0 *c, UnkStruct_8026B9CC_1 *amc) {
    s32 i;
    f32 fsize;
    UnkStruct_8026B804 *buffs;
    s16 err;
#if !VERSION_JP
    f32 fps;
#endif

    err = 0;
    D_802AD680.flags = D_802AD680.maxDMAs = D_802AD680.maxBuffers = D_802AD680.maxCmds = 0;
    D_802AF938 = D_802AF93C = D_802AF948 = 0;
    D_802AF940 = amc->numDMABuffers;
    D_802AF944 = amc->dmaBufferLength;
    D_802AF928 = c->heap;
    c->dmaproc = func_8026B210;
    c->outputRate = func_80297FC0(amc->outputRate);
#if VERSION_JP
    fsize = (f32) amc->framesPerField * c->outputRate / 60.0f;
#else
    if (func_802983B0() == 0) {
        fps = 50.0f;
    } else {
        fps = 60.0f;
    }
    fsize = (f32) amc->framesPerField * c->outputRate / fps;
#endif
    D_802AF954 = (s32) fsize;
    if (D_802AF954 < fsize) {
        D_802AF954++;
    }
    if (D_802AF954 & 0xF) {
        D_802AF954 = (D_802AF954 & ~0xF) + 0x10;
    }
    D_802AF94C = D_802AF954 - 0x10;
    D_802AF950 = D_802AF954 + 0x60;
    func_80298490(D_802AD6A0.g, c);

    buffs = func_8026B72C(D_802AF940 * sizeof(UnkStruct_8026B804));
    if (buffs == NULL) {
        err = 1;
        goto end;
    }
    buffs[D_802AF940 - 1].next = NULL;
    buffs[0].prev = buffs[0].next = buffs[D_802AF940 - 1].next;
    for (i = 0; i < D_802AF940 - 1; i++) {
        func_802983C0(&buffs[i + 1], &buffs[i]);
        buffs[i].ptr = func_8026B72C(D_802AF944);
        if (buffs[i].ptr == NULL) {
            err = 1;
            goto end;
        }
    }
    buffs[i].ptr = func_8026B72C(D_802AF944);
    if (buffs[i].ptr == NULL) {
        err = 1;
        goto end;
    }
    D_802AF930.firstUsed = NULL;
    D_802AF930.firstFree = buffs;

    D_802AF958 = amc->maxACMDSize;
    for (i = 0; i < 2; i++) {
        D_802AD6A0.ACMDList[i] = func_8026B72C(D_802AF958 * sizeof(UnkStruct_802AD6A0_0));
        if (D_802AD6A0.ACMDList[i] == NULL) {
            err = 1;
            goto end;
        }
    }
    for (i = 0; i < 3; i++) {
        D_802AD6A0.audioInfo[i] = func_8026B72C(sizeof(UnkStruct_8026B238));
        if (D_802AD6A0.audioInfo[i] == NULL) {
            err = 1;
            goto end;
        }
        D_802AD6A0.audioInfo[i]->msgType = 2;
        D_802AD6A0.audioInfo[i]->msgInfo = D_802AD6A0.audioInfo[i];
        D_802AD6A0.audioInfo[i]->data = func_8026B72C(D_802AF950 * 4);
        if (D_802AD6A0.audioInfo[i]->data == NULL) {
            err = 1;
            goto end;
        }
    }
end:
    func_80297D80(&D_802AD6A0.audioReplyMsgQ, D_802AD6A0.audioReplyMsgBuf, 8);
    func_80297D80(&D_802AFBA0, D_802AFBB8, 0x18);
    if (amc->sched != NULL) {
        func_80297D80(&D_802AD6A0.audioFrameMsgQ, D_802AD6A0.audioFrameMsgBuf, 8);
        D_802AD690 = func_80297E00(amc->sched);
        func_80297DF0(amc->sched, D_802AD698, &D_802AD6A0.audioFrameMsgQ);
    }
    func_80297DA8(D_802AD6A0.thread, amc->id, func_8026B584, NULL, &D_802AF928, amc->pri);
    func_80297DB0(D_802AD6A0.thread);
    return err;
}

static s32 func_8026B804(s32 addr, s32 len, void *state) {
    u8 *foundBuffer;
    s32 delta;
    s32 addrEnd;
    s32 buffEnd;
    UnkStruct_8026B804 *dmaPtr;
    UnkStruct_8026B804 *lastDmaPtr;

    lastDmaPtr = NULL;
    dmaPtr = D_802AF930.firstUsed;
    addrEnd = addr + len;
    while (dmaPtr != NULL) {
        buffEnd = dmaPtr->startAddr + D_802AF944;
        if (dmaPtr->startAddr > addr) {
            break;
        } else if (addrEnd <= buffEnd) {
            dmaPtr->lastFrame = D_802AF938;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return (s32) func_80297D48(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = dmaPtr->next;
    }
    dmaPtr = D_802AF930.firstFree;
    if (dmaPtr == NULL) {
        return (s32) func_80297D48(D_802AF930.firstUsed);
    }
    D_802AF930.firstFree = dmaPtr->next;
    func_802983B8(dmaPtr);
    if (lastDmaPtr != NULL) {
        func_802983C0(dmaPtr, lastDmaPtr);
    } else if (D_802AF930.firstUsed != NULL) {
        lastDmaPtr = D_802AF930.firstUsed;
        D_802AF930.firstUsed = dmaPtr;
        dmaPtr->next = lastDmaPtr;
        dmaPtr->prev = NULL;
        lastDmaPtr->prev = dmaPtr;
    } else {
        D_802AF930.firstUsed = dmaPtr;
        dmaPtr->next = NULL;
        dmaPtr->prev = NULL;
    }
    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = D_802AF938;
    func_80298028(&D_802AF960[D_802AF93C++], 0, 0, addr, foundBuffer, D_802AF944, &D_802AFBA0);
    return (s32) func_80297D48(foundBuffer) + delta;
}

void func_8026B7D4(void) {
    func_80297DC8(D_802AD6A0.thread);
    func_80298498(D_802AD6A0.g);
}

void func_8026B7A8(u32 frames) {
    D_802AF95C = 0;
    while (D_802AF95C < frames) {
    }
}

UnkStruct_802AD680 *func_8026B79C(void) {
    return &D_802AD680;
}

void *func_8026B72C(s32 size) {
    if (D_802AF928->len - (D_802AF928->cur - D_802AF928->base) < size) {
        D_802AD680.flags |= 1;
        return NULL;
    }
    return func_802983D8(NULL, 0, D_802AF928, 1, size);
}

/* audiomgr.c's __amHandleDoneMsg */
static void func_8026B228(UnkStruct_8026B238 *info) {
    s32 samplesLeft;
    static s32 D_802A1370 = 1;

    samplesLeft = func_80297FB8() >> 2;
    if (samplesLeft == 0 && D_802A1370 == 0) {
        D_802AD680.flags |= 4;
        D_802A1370 = 0;
    }
}

/* audiomgr.c's __clearAudioDMA, with the peaks */
static void func_8026B230(void) {
    u32 i;
    void *iomsg;
    UnkStruct_8026B804 *dmaPtr;
    UnkStruct_8026B804 *nextPtr;

    if (D_802AD680.maxDMAs < D_802AF93C) {
        D_802AD680.maxDMAs = D_802AF93C;
    }
    i = 0;
    for (dmaPtr = D_802AF930.firstUsed; dmaPtr != NULL; dmaPtr = dmaPtr->next) {
        i++;
    }
    if (D_802AD680.maxBuffers < i) {
        D_802AD680.maxBuffers = i;
    }
    if (i >= D_802AF940) {
        D_802AD680.flags |= 0x10;
    }
    for (i = 0; i < D_802AF93C; i++) {
        if (func_80297D90(&D_802AFBA0, &iomsg, 0) == -1) {
            D_802AD680.flags |= 2;
        }
    }
    dmaPtr = D_802AF930.firstUsed;
    while (dmaPtr != NULL) {
        nextPtr = dmaPtr->next;
        if (dmaPtr->lastFrame + 1 < D_802AF938) {
            if (D_802AF930.firstUsed == dmaPtr) {
                D_802AF930.firstUsed = dmaPtr->next;
            }
            func_802983B8(dmaPtr);
            if (D_802AF930.firstFree != NULL) {
                func_802983C0(dmaPtr, D_802AF930.firstFree);
            } else {
                D_802AF930.firstFree = dmaPtr;
                dmaPtr->next = NULL;
                dmaPtr->prev = NULL;
            }
        }
        dmaPtr = nextPtr;
    }
    D_802AF93C = 0;
    D_802AF938++;
}

/* audiomgr.c's __amHandleFrameMsg */
static s32 func_8026B238(UnkStruct_8026B238 *info, UnkStruct_8026B238 *lastInfo) {
    void *audioPtr;
    UnkStruct_802AD6A0_0 *cmdp;
    s32 cmdLen;
    UnkStruct_8026B238_8 *t;

    func_8026B230();
    audioPtr = func_80297D48(info->data);
    if (lastInfo != NULL) {
        func_80297FC8(lastInfo->data, lastInfo->frameSamples << 2);
    }
    info->frameSamples = ((D_802AF954 - (func_80297FB8() >> 2) + 0x50) & 0xFFF0) + 0x10;
    if ((u32) info->frameSamples < D_802AF94C) {
        info->frameSamples = D_802AF94C;
    }
    cmdp = func_802984A0(D_802AD6A0.ACMDList[D_802AF948], &cmdLen, audioPtr, info->frameSamples);
    if (D_802AD680.maxCmds < (u32) cmdLen) {
        D_802AD680.maxCmds = cmdLen;
    }
    if (D_802AF958 < (u32) cmdLen) {
        D_802AD680.flags |= 8;
        return 0;
    }
    if (cmdLen == 0) {
        return 0;
    }
    t = &info->task;
    t->next = NULL;
    t->flags = 2;
    t->msgQ = &D_802AD6A0.audioReplyMsgQ;
    t->msg = &info->msgType;
    t->data_ptr = D_802AD6A0.ACMDList[D_802AF948];
    t->data_size = (cmdp - D_802AD6A0.ACMDList[D_802AF948]) * sizeof(UnkStruct_802AD6A0_0);
    t->type = 2;
    t->ucode_boot = D_8029D250;
    t->ucode_boot_size = D_8029D320 - D_8029D250;
    t->taskFlags = 0;
    t->ucode = D_8029E750;
    t->ucode_data = D_802A5040;
    t->ucode_data_size = 0x800;
    t->dram_stack = NULL;
    t->dram_stack_size = 0;
    t->output_buff = NULL;
    t->output_buff_size = 0;
    t->yield_data_ptr = NULL;
    t->yield_data_size = 0;
    func_80297D98(D_802AD690, t, 1);
    D_802AF948 ^= 1;
    return 1;
}

/* audiomgr.c's __amMain */
static void func_8026B584(void *arg) {
    s32 pad; /* an unused slot above done (frame 0x60) */
    s32 done;
    UnkStruct_8026B584 *msg;
    UnkStruct_8026B238 *lastInfo;

    done = 0;
    lastInfo = NULL;
    while (!done) {
        func_80297D90(&D_802AD6A0.audioFrameMsgQ, &msg, 1);
        switch (msg->type) {
            case 1:
                if (func_8026B238(D_802AD6A0.audioInfo[D_802AF938 % 3], lastInfo)) {
                    func_80297D90(&D_802AD6A0.audioReplyMsgQ, &msg, 1);
                    func_8026B228(msg->info);
                    lastInfo = msg->info;
                    func_802691A8();
                    func_802686B8();
                }
                D_802AF95C++;
                break;
            case 4:
                done = 1;
                func_8026910C();
                func_80267754();
                break;
            case 10:
                done = 1;
                break;
        }
    }
    func_80298498(D_802AD6A0.g);
}

/* audiomgr.c's __amDmaNew */
static void *func_8026B210(UnkStruct_802AF930 **state) {
    *state = &D_802AF930;
    return func_8026B804;
}
