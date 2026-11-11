/*
 * boot_code's start: the idle thread (func_800019A0, then func_80001914),
 * the main thread (func_80001750: ZeroJump's tables for the libraries,
 * then the game's segments, run one after another from 0x80225800), and
 * the debug stubs the tables point at. -O2 (-O3 schedules
 * func_80001750 differently). eu sets osTvType itself; jp has no
 * func_80001A14 (nor its entry in module 0x12's table).
 *
 * Its .data and .bss are its own, placed on their own
 * (data_split.txt): 14B0, before it, is not C yet.
 */
#include "common.h"
#include "ultralib/ultra64.h"
#include "ultralib/PR/sched.h"
#include "ultralib/PR/libaudio.h"

/* boot_code's own functions in the tables */
void func_80000450(void);
void func_80000698(void *dst, u32 size, u32 rom);
void func_80000794(void);
void func_80000870(void);
void func_8000083C(s32 seg, void *entry, void *arg);
void func_80001A30(s32 id, void **table);
void func_800004D0();
void func_80000524();
void func_8000059C();
void func_8000064C();
void func_80000768();
void func_80001480();
void func_80001488();
void func_80001698();
void func_80003190(void);
void func_80005480();
void func_8000C8D0();
void __d_to_ll();
void __ll_to_d();
void __ull_to_f();
void __f_to_ull();
void __ull_to_d();
void __osGetCurrFaultedThread();
void osPiRawWriteIo();
void osPiRawReadIo();
void osPiRawStartDma();
void osPfsReSizeFile();

void func_800018A8(char *expr, char *file, s32 line);
s32 func_800018B8(f32 arg0);
void func_800018C4(s32 arg0);
void func_800018CC(char *fmt, ...);
void func_800018E8(char *expr, char *file, s32 line);
void func_800018F8(char *fmt, ...);
void func_80001A04(u8 arg0);
s32 func_80001A14(void);

/* ZeroJump module 1: threads, messages, caches, the scheduler, time */
void *D_80019FC0[] = {
    func_800018F8,
    sprintf,
    osVirtualToPhysical,
    osInvalDCache,
    osInvalICache,
    osWritebackDCache,
    osWritebackDCacheAll,
    osSpTaskLoad,
    osSpTaskStartGo,
    osCreateMesgQueue,
    osSetEventMesg,
    osRecvMesg,
    osSendMesg,
    osJamMesg,
    osCreateThread,
    osStartThread,
    osStopThread,
    osYieldThread,
    osDestroyThread,
    osGetThreadPri,
    osSetThreadPri,
    osGetThreadId,
    osCreateScheduler,
    osScAddClient,
    func_80001488,
    func_80001480,
    osCreatePiManager,
    func_800018E8,
    func_800018CC,
    func_800018C4,
    func_800018B8,
    func_80001698,
    osGetTime,
    osSetTime,
    osSetTimer,
    osStopTimer,
    osGetCount,
    osEepromProbe,
    osEepromRead,
    osEepromWrite,
    osEepromLongRead,
    osEepromLongWrite,
    osMotorInit,
    osMotorStop,
    osMotorStart,
    osGetIntMask,
    osSetIntMask,
};

/* module 2: 10D0's PI DMA */
void *D_8001A07C[] = {
    func_80000768, func_800004D0, func_80000698, func_8000064C, func_8000059C, func_80000524,
};

/* module 6: VI */
void *D_8001A094[] = {
    osViGetStatus,
    osViGetCurrentMode,
    osViGetCurrentLine,
    osViGetCurrentField,
    osViGetCurrentFramebuffer,
    osViGetNextFramebuffer,
    osViSetXScale,
    osViSetYScale,
    osViSetSpecialFeatures,
    osViSetMode,
    osViSetEvent,
    osViSwapBuffer,
    osViBlack,
    osViFade,
};

/* module 7: AI */
void *D_8001A0CC[] = {
    osAiGetStatus,
    osAiGetLength,
    osAiSetFrequency,
    osAiSetNextBuffer,
};

/* module 8: DP */
void *D_8001A0DC[] = {
    osDpGetStatus,
    osDpSetStatus,
    osDpGetCounters,
    osDpSetNextBuffer,
};

/* module 9: PI */
void *D_8001A0EC[] = {
    osPiGetStatus,
    func_80005480,
    osPiRawWriteIo,
    osPiRawReadIo,
    osPiRawStartDma,
    osPiWriteIo,
    osPiReadIo,
    osPiStartDma,
};

/* module 0xA: controllers */
void *D_8001A10C[] = {
    osContInit,
    osContStartReadData,
    osContGetReadData,
    osContReset,
    osContStartQuery,
    osContSetCh,
    osContGetQuery,
};

/* module 0x12: 64-bit conversions and the rest */
void *D_8001A128[] = {
    __d_to_ll,
    __ll_to_d,
    __ull_to_f,
    __f_to_ull,
    __ull_to_d,
    func_800018A8,
    __osGetCurrFaultedThread,
    func_80001A04,
#if !VERSION_JP
    func_80001A14,
#endif
};

/* module 0x13: libaudio */
void *D_8001A14C[] = {
    alUnlink,
    alLink,
    alCopy,
    alHeapInit,
    alHeapDBAlloc,
    alHeapCheck,
    alBnkfNew,
    alSeqFileNew,
    alSynNew,
    alSynDelete,
    alSynAddPlayer,
    alSynRemovePlayer,
    alSynAllocVoice,
    alSynFreeVoice,
    alSynStartVoice,
    alSynStartVoiceParams,
    alSynStopVoice,
    alSynSetVol,
    alSynSetPitch,
    alSynSetPan,
    alSynSetFXMix,
    alSynSetPriority,
    alSynGetPriority,
    alSynAllocFX,
    alSynGetFXRef,
    alSynFreeFX,
    alSynSetFXParam,
    alInit,
    alClose,
    alAudioFrame,
    alEvtqNew,
    alEvtqNextEvent,
    alEvtqPostEvent,
    alEvtqFlush,
    alEvtqFlushType,
    alSeqNew,
    alSeqNextEvent,
    alSeqGetTicks,
    alSeqTicksToSec,
    alSeqSecToTicks,
    alSeqNewMarker,
    alSeqSetLoc,
    alSeqGetLoc,
    alCSeqNew,
    alCSeqNextEvent,
    alCSeqGetTicks,
    alCSeqTicksToSec,
    alCSeqSecToTicks,
    alCSeqNewMarker,
    alCSeqSetLoc,
    alCSeqGetLoc,
    alCents2Ratio,
    alSeqpNew,
    alSeqpDelete,
    alSeqpSetSeq,
    alSeqpGetSeq,
    alSeqpPlay,
    alSeqpStop,
    alSeqpGetState,
    alSeqpSetBank,
    alSeqpSetTempo,
    alSeqpGetTempo,
    alSeqpGetVol,
    alSeqpSetVol,
    alSeqpLoop,
    alSeqpSetChlProgram,
    alSeqpGetChlProgram,
    alSeqpSetChlFXMix,
    alSeqpGetChlFXMix,
    alSeqpSetChlVol,
    alSeqpGetChlVol,
    alSeqpSetChlPan,
    alSeqpGetChlPan,
    alSeqpSetChlPriority,
    alSeqpGetChlPriority,
    alSeqpSendMidi,
    alCSPNew,
    alCSPDelete,
    alCSPSetSeq,
    alCSPGetSeq,
    alCSPPlay,
    alCSPStop,
    alCSPGetState,
    alCSPSetBank,
    alCSPSetTempo,
    alCSPGetTempo,
    alCSPGetVol,
    alCSPSetVol,
    alCSPSetChlProgram,
    alCSPGetChlProgram,
    alCSPSetChlFXMix,
    alCSPGetChlFXMix,
    alCSPSetChlPan,
    alCSPGetChlPan,
    alCSPSetChlVol,
    alCSPGetChlVol,
    alCSPSetChlPriority,
    alCSPGetChlPriority,
    alCSPSendMidi,
    alSndpNew,
    alSndpDelete,
    alSndpAllocate,
    alSndpDeallocate,
    alSndpSetSound,
    func_8000C8D0,
    alSndpPlay,
    alSndpPlayAt,
    alSndpStop,
    alSndpSetVol,
    alSndpSetPitch,
    alSndpSetPan,
    alSndpSetPriority,
    alSndpSetFXMix,
    alSndpGetState,
};

/* module 0x16: the controller pak */
void *D_8001A314[] = {
    osPfsInit,
    osPfsReFormat,
    osPfsChecker,
    osPfsAllocateFile,
    osPfsFindFile,
    osPfsDeleteFile,
    osPfsReadWriteFile,
    osPfsFileState,
    osPfsGetLabel,
    osPfsSetLabel,
    osPfsIsPlug,
    osPfsFreeBlocks,
    osPfsNumFiles,
    osPfsReSizeFile,
    osPfsInitPak,
    osPfsRepairId,
};

u8 D_8001C4B0;
OSThread D_8001C4B8;
u64 D_8001C668[0x4000 / sizeof(u64)];
OSThread D_80020668;
u64 D_80020818[0x4000 / sizeof(u64)];
s32 D_80024818;
u8 D_80024820[0x100];

void func_80001750(void *arg) {
    u32 size;
    u8 *entry = (u8 *)0x80225800;

    D_80024818 = 2;
    func_80000450();
    func_80001A30(1, D_80019FC0);
    func_80001A30(2, D_8001A07C);
    func_80001A30(6, D_8001A094);
    func_80001A30(0xA, D_8001A10C);
    func_80001A30(0x12, D_8001A128);
    func_80001A30(7, D_8001A0CC);
    func_80001A30(8, D_8001A0DC);
    func_80001A30(9, D_8001A0EC);
    func_80001A30(0x13, D_8001A14C);
    func_80001A30(0x16, D_8001A314);
    func_80000870();
    size = D_80024820[2] << 11;
    if (size == 0) {
        size = 0x80000;
    }
    func_80000698(size + entry, D_80024820[3] << 11, size + 0x40000);
    for (;;) {
        func_8000083C(D_80024818, entry, &D_80020668);
    }
}

void func_800018A8(char *expr, char *file, s32 line) {
}

s32 func_800018B8(f32 arg0) {
    return 0;
}

void func_800018C4(s32 arg0) {
}

void func_800018CC(char *fmt, ...) {
}

void func_800018E8(char *expr, char *file, s32 line) {
}

void func_800018F8(char *fmt, ...) {
}

void func_80001914(void *arg) {
    func_80000794();
    osCreateThread(&D_80020668, 3, func_80001750, arg, &D_80024818, 10);
    osStartThread(&D_80020668);
    osSetThreadPri(NULL, 0);
    for (;;) {
    }
}

void func_800019A0(void) {
    func_80003190();
#if VERSION_EU
    osTvType = OS_TV_PAL;
#endif
    osInitialize();
    osCreateThread(&D_8001C4B8, 1, func_80001914, NULL, &D_80020668, 10);
    osStartThread(&D_8001C4B8);
}

void func_80001A04(u8 arg0) {
    D_8001C4B0 = arg0;
}

#if !VERSION_JP
s32 func_80001A14(void) {
    return osTvType;
}
#endif
