/*
 * libultra io/conteeplongread.c, from decompals/ultralib, as this game has
 * it: older than 2.0I.  The start address is range-checked first, and
 * each block is followed by the same 12ms wait as a write.  The wait is
 * computed through osClockRate (libultra_bm64.h).
 */
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"
#include "libultra_bm64.h"

s32 osEepromLongRead(OSMesgQueue* mq, u8 address, u8* buffer, int length) {
    s32 ret = 0;

    if (address > EEPROM_MAXBLOCKS) {
        return -1;
    }

    while (length > 0) {
        ERRCK(osEepromRead(mq, address, buffer));
        length -= EEPROM_BLOCK_SIZE;
        address++;
        buffer += EEPROM_BLOCK_SIZE;
        osSetTimer(&__osEepromTimer, OS_USEC_TO_CYCLES(12000), 0, &__osEepromTimerQ, &__osEepromTimerMsg);
        osRecvMesg(&__osEepromTimerQ, NULL, OS_MESG_BLOCK);
    }

    return ret;
}
