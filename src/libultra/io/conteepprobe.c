/*
 * libultra io/conteepprobe.c, from decompals/ultralib, as this game has it:
 * older than 2.0I.  There is no 16K EEPROM yet, so any EEPROM is reported
 * as 1 (EEPROM_TYPE_4K).
 */
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

s32 osEepromProbe(OSMesgQueue* mq) {
    s32 ret = 0;
    OSContStatus sdata;

    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    if (ret == 0 && (sdata.type & CONT_EEPROM) != 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    __osSiRelAccess();
    return ret;
}
