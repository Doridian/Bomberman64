/*
 * libultra io/epirawwrite.c, from decompals/ultralib, as this game has it:
 * older than 2.0I.  osEPiRawWriteIo only waits for the PI; it doesn't
 * switch the domain's timing registers to the handle's (EPI_SYNC).
 */
#include "PRinternal/piint.h"
#include "PR/ultraerror.h"

s32 __osEPiRawWriteIo(OSPiHandle* pihandle, u32 devAddr, u32 data) {
    register u32 stat;

    WAIT_ON_IOBUSY(stat);
    IO_WRITE(pihandle->baseAddress | devAddr, data);

    return 0;
}
