/*
 * libultra io/pfsgetstatus.c, from decompals/ultralib, as this game has it:
 * older than 2.0I.  __osPfsGetStatus asks every channel for its status
 * with __osPfsRequestData and reads them with __osPfsGetInitData
 * (pfsisplug.c) instead of 2.0I's one-channel request, so the object has
 * only the one function.
 */
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

s32 __osPfsGetStatus(OSMesgQueue* queue, int channel) {
    s32 ret = 0;
    OSMesg dummy;
    u8 pattern;
    OSContStatus data[MAXCONTROLLERS];

    __osPfsRequestData(CONT_CMD_REQUEST_STATUS);

    ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);

    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);

    __osPfsGetInitData(&pattern, data);

    if (((data[channel].status & CONT_CARD_ON) != 0) && ((data[channel].status & CONT_CARD_PULL) != 0)) {
        return PFS_ERR_NEW_PACK;
    } else if ((data[channel].errno != 0) || ((data[channel].status & CONT_CARD_ON) == 0)) {
        return PFS_ERR_NOPACK;
    } else if ((data[channel].status & CONT_ADDR_CRC_ER) != 0) {
        return PFS_ERR_CONTRFAIL;
    }

    return ret;
}
