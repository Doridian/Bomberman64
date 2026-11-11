/*
 * boot_code's PI DMA: blocking reads from cartridge ROM (func_80000698,
 * which also flushes the caches over the target) and writes to it, and
 * unblocked starts and waits, all through one request and reply queue.
 * ZeroJump module 2 points at these (2350's D_8001A07C). -O3: the
 * functions come out in reverse order (-O2 schedules func_80000698's
 * loop and the starts differently).
 */
#include "common.h"
#include "ultralib/ultra64.h"

/* .bss: the PI manager's queue, a busy flag, and one DMA request and its
 * reply queue shared by every transfer */
OSMesg D_8001C3C0[8];
OSMesgQueue D_8001C3E0;
s32 D_8001C3F8;
OSIoMesg D_8001C400;
OSMesgQueue D_8001C418;
OSMesg D_8001C430[1];

void func_80000794(void) {
    D_8001C3F8 = 0;
    osCreatePiManager(OS_PRIORITY_PIMGR, &D_8001C3E0, D_8001C3C0, 8);
    osCreateMesgQueue(&D_8001C418, D_8001C430, 1);
}

void func_80000768(void) {
    osRecvMesg(&D_8001C418, NULL, OS_MESG_NOBLOCK);
}

void func_80000698(void *vaddr, u32 size, u32 devAddr) {
    while (D_8001C3F8) {
        osYieldThread();
    }
    D_8001C3F8 = 1;
    osWritebackDCache(vaddr, size);
    osInvalDCache(vaddr, size);
    osInvalICache(vaddr, size);
    osPiStartDma(&D_8001C400, OS_MESG_PRI_NORMAL, OS_READ, devAddr, vaddr, size, &D_8001C418);
    osRecvMesg(&D_8001C418, NULL, OS_MESG_BLOCK);
    D_8001C3F8 = 0;
}

void func_8000064C(void *vaddr, u32 size, u32 devAddr) {
    osPiStartDma(&D_8001C400, OS_MESG_PRI_NORMAL, OS_READ, devAddr, vaddr, size, &D_8001C418);
}

void func_8000059C(u32 devAddr, u32 size, void *vaddr) {
    while (D_8001C3F8) {
        osYieldThread();
    }
    D_8001C3F8 = 1;
    osWritebackDCache(vaddr, devAddr);
    osPiStartDma(&D_8001C400, OS_MESG_PRI_NORMAL, OS_WRITE, devAddr, vaddr, size, &D_8001C418);
    osRecvMesg(&D_8001C418, NULL, OS_MESG_BLOCK);
    D_8001C3F8 = 0;
}

void func_80000570(void) {
    osRecvMesg(&D_8001C418, NULL, OS_MESG_BLOCK);
}

void func_80000524(u32 devAddr, u32 size, void *vaddr) {
    osPiStartDma(&D_8001C400, OS_MESG_PRI_NORMAL, OS_WRITE, devAddr, vaddr, size, &D_8001C418);
}

void func_800004D0(void *vaddr, u32 size, u32 devAddr, s32 direction) {
    osPiStartDma(&D_8001C400, OS_MESG_PRI_NORMAL, direction, devAddr, vaddr, size, &D_8001C418);
}
