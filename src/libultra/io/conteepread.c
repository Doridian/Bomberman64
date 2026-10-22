/*
 * libultra io/conteepread.c, from decompals/ultralib, as this game has it:
 * older than 2.0I.  Only a 4K EEPROM is supported, so the address is
 * range-checked before anything else and any other device is
 * CONT_NO_RESPONSE_ERROR (returned with the SI still held).  The PIF RAM
 * is refilled with 0xFF before the response is read, and the packer fills
 * all 16 words with 0xFF first.
 *
 * __osEepPifRam is defined by the asm data (docs/LIBULTRA.md, "Data").
 */
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

static void __osPackEepReadData(u8 address);

s32 osEepromRead(OSMesgQueue* mq, u8 address, u8* buffer) {
    s32 ret = 0;
    int i = 0;
    u8* ptr = (u8*)&__osEepPifRam.ramarray;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

    if (address > EEPROM_MAXBLOCKS) {
        return -1;
    }

    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    if (ret != 0 || sdata.type != CONT_EEPROM) {
        return CONT_NO_RESPONSE_ERROR;
    }

    while (sdata.status & CONT_EEPROM_BUSY) {
        __osEepStatus(mq, &sdata);
    }

    __osPackEepReadData(address);
    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam); // send command to pif
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    for (i = 0; i < 16; i++) {
        ((u32*)&__osEepPifRam)[i] = 0xFF;
    }
    __osEepPifRam.pifstatus = 0;

    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam); // recv response
    __osContLastCmd = CONT_CMD_READ_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        // skip the first 4 bytes
        ptr++;
    }

    eepromformat = *(__OSContEepromFormat*)ptr;
    ret = CHNL_ERR(eepromformat);

    if (ret == 0) {
        for (i = 0; i < ARRLEN(eepromformat.data); i++) {
            *buffer++ = eepromformat.data[i];
        }
    }
    __osSiRelAccess();
    return ret;
}

static void __osPackEepReadData(u8 address) {
    u8* ptr = (u8*)&__osEepPifRam.ramarray;
    __OSContEepromFormat eepromformat;
    int i;

    for (i = 0; i < 16; i++) {
        ((u32*)&__osEepPifRam)[i] = 0xFF;
    }
    __osEepPifRam.pifstatus = CONT_CMD_EXE;

    eepromformat.txsize = CONT_CMD_READ_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_READ_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_READ_EEPROM;
    eepromformat.address = address;

    for (i = 0; i < ARRLEN(eepromformat.data); i++) {
        eepromformat.data[i] = 0;
    }

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = 0;
    }

    *(__OSContEepromFormat*)(ptr) = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    ptr[0] = CONT_CMD_END;
}
