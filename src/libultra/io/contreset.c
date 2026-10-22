/*
 * libultra io/contreset.c, from decompals/ultralib, as this game has it:
 * older than 2.0I.  osContReset sets __osContLastCmd at the end, after
 * the last read, and __osPackResetData clears all 16 words of the PIF RAM
 * and writes no CONT_CMD_END after the four channel resets.
 */
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

void __osPackResetData(void);

s32 osContReset(OSMesgQueue* mq, OSContStatus* data) {
    u8 pattern;
    s32 ret;

    __osSiGetAccess();

    if (__osContLastCmd != CONT_CMD_RESET) {
        __osPackResetData();

        ret = __osSiRawStartDma(OS_WRITE, __osContPifRam.ramarray);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = __osSiRawStartDma(OS_READ, __osContPifRam.ramarray);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        __osPackRequestData(CONT_CMD_RESET);

        ret = __osSiRawStartDma(OS_WRITE, __osContPifRam.ramarray);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }

    ret = __osSiRawStartDma(OS_READ, __osContPifRam.ramarray);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    __osContGetInitData(&pattern, data);
    __osContLastCmd = CONT_CMD_RESET;
    __osSiRelAccess();

    return ret;
}

void __osPackResetData(void) {
    u8* ptr;
    int i;

    for (i = 0; i < 16; i++) {
        ((u32*)&__osContPifRam)[i] = 0;
    }

    __osContPifRam.pifstatus = CONT_CMD_EXE;
    ptr = (u8*)__osContPifRam.ramarray;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = CONT_CMD_CHANNEL_RESET;
    }
}
