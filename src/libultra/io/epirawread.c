/*
 * libultra io/epirawread.c, from decompals/ultralib, as this game has it:
 * older than 2.0I.  osEPiRawReadIo only waits for the PI; it doesn't
 * switch the domain's timing registers to the handle's (EPI_SYNC).
 */
#include "PRinternal/piint.h"
#include "PR/ultraerror.h"

s32 __osEPiRawReadIo(OSPiHandle* pihandle, u32 devAddr, u32* data) {
    register u32 stat;

    WAIT_ON_IOBUSY(stat);
    *data = IO_READ(pihandle->baseAddress | devAddr);

    return 0;
}
