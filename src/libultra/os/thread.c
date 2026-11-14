/*
 * libultra os/thread.c, from decompals/ultralib.  The thread queues
 * (__osThreadTail, __osRunQueue, __osActiveQueue, __osRunningThread,
 * __osFaultedThread) are defined by the asm data (docs/LIBULTRA.md, "Data").
 */
#include "PR/os_internal.h"
#include "PRinternal/osint.h"

extern struct __osThreadTail __osThreadTail;
extern OSThread* __osRunQueue;
extern OSThread* __osActiveQueue;
extern OSThread* __osRunningThread;
extern OSThread* __osFaultedThread;

void __osDequeueThread(register OSThread** queue, register OSThread* t) {
    register OSThread* pred;
    register OSThread* succ;

    pred = (OSThread*)queue;
    succ = pred->next;

    while (succ != NULL) {
        if (succ == t) {
            pred->next = t->next;
#ifdef _DEBUG
            t->next = NULL;
#endif
            return;
        }
        pred = succ;
        succ = pred->next;
    }
}
