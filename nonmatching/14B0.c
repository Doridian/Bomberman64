/*
 * NON_MATCHING: boot_code's 14B0, complete: Hudson's copy of the N64
 * sample scheduler ("sched.c" in its assert strings), written from the
 * asm with ultralib's PR/sched.h types. Hudson's changes: func_80000A88
 * calls itself again until a pass schedules nothing more, the first
 * swapped frame turns the blanking off (D_80019FB8), and a frame's
 * timing is taken with osGetTime() (D_80019FAC steps 0-4 from a retrace
 * through the RSP and RDP done messages; func_80001698, in ZeroJump's
 * module 1, hands the times out and starts over). Not built into the
 * ROM (docs/DECOMPILING.md, "NON_MATCHING drafts").
 * flags: -O3
 * differing words: us 0, eu 0, jp 0
 *
 * Every function matches in all three versions (pass 2). Pass 1's
 * 227 words in func_8000101C were two behaviour errors, not schedule:
 * the retrace count (D_80019FA0) is only stepped when the timing starts
 * (inside `if (D_80019FAC == 0)`), and the RSP done handler hands a
 * task to func_80000C7C only when it didn't yield. func_80000A88's
 * jump table word was a real .rodata layout difference: strings go to
 * .rodata in parse order, and the original has the dead
 * "sc->curRDPTask == gfx" assert's strings last, after func_80000908's,
 * so the dead call sits in func_800008B0 (defined last) rather than in
 * func_80000A88, which puts the jump table at jtbl_8001B754.
 *
 * -O3 evidence: func_80000908 and func_80000E58 take their arguments in
 * s registers (IPA statics), func_80000A88 keeps sc in t0, and the
 * handlers of the RSP and RDP done messages (func_8000101C_inl1/2),
 * the list append and the yield (func_80000E58_inl1/2) are inlined
 * statics with their `jr ra` stubs left. func_80000D44 and
 * func_80000E0C are globals inlined into func_8000101C as well as
 * emitted.
 *
 * What fixed the order and the frames:
 * - umerge walks the file backwards; a static with callers waits for
 *   one, and a function's callees come out first (last call first).
 *   func_800008B0 and func_80000A88 are global (the caller spills
 *   a1-a3/t0 around their calls, so no IPA), func_800008B0 defined
 *   last and func_80000A88, func_80000D44 and func_80000E0C before
 *   func_8000101C, so that main's walk emits func_80000908,
 *   func_80000A88, func_80000C7C, the stubs, func_80000D44 and
 *   func_80000E0C between them, as the original has.
 * - func_80000A88's "until nothing changes" is tail recursion: as a
 *   loop, sp and dp leave a1/a2.
 * - func_800008B0's frame (0x28, the local at 0x18) is a 4-word array.
 * - D_80019FB8 is a function-scope static of func_80000C7C (one lui per
 *   access); the unreferenced "sc->curRDPTask == gfx" string is a dead
 *   assert, placed last (above).
 *
 * Asserts call func_800018A8 (2350's empty stub) with the expression,
 * "sched.c" and the line.
 */
#include "common.h"
#include "ultralib/ultra64.h"
#include "ultralib/PR/sched.h"

void func_800018A8(char *expr, char *file, s32 line);

#define SC_ASSERT(e, line) ((e) ? (void)0 : func_800018A8(#e, "sched.c", line))

/* the interrupt queue's messages */
#define SC_MSG_RETRACE 0x29A
#define SC_MSG_RSP_DONE 0x29B
#define SC_MSG_RDP_DONE 0x29C
#define SC_MSG_PRE_NMI 0x29D

/* a task's state bits beside OS_SC_NEEDS_RDP/RSP */
#define SC_STATE_YIELD 0x10
#define SC_STATE_YIELDED 0x20

/* the task types (OS_SC_TYPE_MASK) that are switched on */
#define SC_TYPE_XBUS 3

extern OSViMode D_8001A3B0[];

/* .data: Hudson's frame timing */
s32 D_80019FA0 = 0; /* retraces */
s32 D_80019FA4 = 0; /* D_80019FA0 when the times were last handed out */
s32 D_80019FA8 = 0; /* D_80019FA0 when the times were taken */
s32 D_80019FAC = 0; /* the timing's step */
s32 D_80019FB0 = 0;
s32 D_80019FB4 = 0;


/* .bss: the times */
OSTime D_8001C440; /* gfx task started (and again, D_8001C450) */
OSTime D_8001C448; /* gfx task's RSP done */
OSTime D_8001C450;
OSTime D_8001C458; /* RDP done */
OSTime D_8001C460; /* retrace */
OSTime D_8001C468; /* audio task started */
OSTime D_8001C470; /* audio task done */
OSTime D_8001C478; /* the copies handed out */
OSTime D_8001C480;
OSTime D_8001C488;
OSTime D_8001C490;
OSTime D_8001C498;
OSTime D_8001C4A0; /* the audio task's, copied at once */
OSTime D_8001C4A8;

void func_8000101C(void *arg);
static void func_80000E58(OSSched *sc);
static s32 func_80000C7C(OSSched *sc, OSScTask *t);
static void func_80000908(OSSched *sc, OSScTask *sp, OSScTask *dp);
s32 func_80000A88(OSSched *sc, OSScTask **sp, OSScTask **dp, s32 availRCP);
OSScTask *func_800008B0(OSScTask *t);
static void func_8000101C_inl1(OSSched *sc);
static void func_8000101C_inl2(OSSched *sc);
static void func_80000E58_inl1(OSSched *sc, OSScTask *t);
static void func_80000E58_inl2(OSSched *sc);
void func_80000D44(void);
void func_80000E0C(void);

void func_80001698(OSTime *gfxStart, OSTime *gfxRspDone, OSTime *gfxStart2, OSTime *rdpDone,
                   OSTime *retrace) {
    if (D_80019FAC == 4) {
        *gfxStart = D_8001C478;
        *gfxRspDone = D_8001C480;
        *gfxStart2 = D_8001C488;
        *rdpDone = D_8001C490;
        *retrace = D_8001C498;
        D_80019FA4 = D_80019FA0;
        D_80019FAC = 0;
    }
}

void osCreateScheduler(OSSched *sc, void *stack, OSPri priority, u8 mode, u8 numFields) {
    sc->curRSPTask = NULL;
    sc->curRDPTask = NULL;
    sc->clientList = NULL;
    sc->frameCount = 0;
    sc->audioListHead = NULL;
    sc->gfxListHead = NULL;
    sc->audioListTail = NULL;
    sc->gfxListTail = NULL;
    sc->retraceMsg.type = OS_SC_RETRACE_MSG;
    sc->prenmiMsg.type = OS_SC_PRE_NMI_MSG;
    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&D_8001A3B0[mode]);
    osViBlack(TRUE);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)SC_MSG_RSP_DONE);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)SC_MSG_RDP_DONE);
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg)SC_MSG_PRE_NMI);
    osViSetEvent(&sc->interruptQ, (OSMesg)SC_MSG_RETRACE, numFields);
    osCreateThread(&sc->thread, 4, func_8000101C, sc, stack, priority);
    osStartThread(&sc->thread);
}

void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    c->msgQ = msgQ;
    c->next = sc->clientList;
    sc->clientList = c;
    osSetIntMask(mask);
}

void func_80001488(OSSched *sc, OSScClient *c) {
    OSScClient *client = sc->clientList;
    OSScClient *prev = NULL;
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    while (client != NULL) {
        if (client == c) {
            if (prev != NULL) {
                prev->next = c->next;
            } else {
                sc->clientList = c->next;
            }
            break;
        }
        prev = client;
        client = client->next;
    }
    osSetIntMask(mask);
}

OSMesgQueue *func_80001480(OSSched *sc) {
    return &sc->cmdQ;
}

void func_80000E0C(void) {
    D_8001C4A0 = D_8001C468;
    D_8001C4A8 = D_8001C470;
}

void func_80000D44(void) {
    if (D_80019FAC == 3) {
        D_80019FAC = 4;
        D_80019FA8 = D_80019FA0;
        D_8001C478 = D_8001C440;
        D_8001C480 = D_8001C448;
        D_8001C488 = D_8001C450;
        D_8001C490 = D_8001C458;
        D_8001C498 = D_8001C460;
    }
}

s32 func_80000A88(OSSched *sc, OSScTask **sp, OSScTask **dp, s32 availRCP) {
    s32 avail;
    OSScTask *gfx;
    OSScTask *audio;

    {
        avail = availRCP;
        gfx = sc->gfxListHead;
        audio = sc->audioListHead;
        if (sc->doAudio && (avail & OS_SC_NEEDS_RSP)) {
            if (gfx != NULL && (gfx->flags & OS_SC_PARALLEL_TASK)) {
                *sp = gfx;
                avail &= ~OS_SC_NEEDS_RSP;
            } else {
                *sp = audio;
                avail &= ~OS_SC_NEEDS_RSP;
                sc->doAudio = FALSE;
                sc->audioListHead = sc->audioListHead->next;
                if (sc->audioListHead == NULL) {
                    sc->audioListTail = NULL;
                }
            }
        } else if (func_800008B0(gfx)) {
            switch (gfx->flags & OS_SC_TYPE_MASK) {
                case SC_TYPE_XBUS:
                    if (gfx->state & SC_STATE_YIELDED) {
                        if (avail & OS_SC_NEEDS_RSP) {
                            *sp = gfx;
                            avail &= ~OS_SC_NEEDS_RSP;
                            if (gfx->state & OS_SC_NEEDS_RDP) {
                                *dp = gfx;
                                avail &= ~OS_SC_NEEDS_RDP;
                            }
                            sc->gfxListHead = sc->gfxListHead->next;
                            if (sc->gfxListHead == NULL) {
                                sc->gfxListTail = NULL;
                            }
                        }
                    } else if (avail == (OS_SC_NEEDS_RSP | OS_SC_NEEDS_RDP)) {
                        *dp = gfx;
                        *sp = gfx;
                        avail &= ~(OS_SC_NEEDS_RSP | OS_SC_NEEDS_RDP);
                        sc->gfxListHead = sc->gfxListHead->next;
                        if (sc->gfxListHead == NULL) {
                            sc->gfxListTail = NULL;
                        }
                    }
                    break;
                case 2:
                case 6:
                case 7:
                    if (gfx->state & OS_SC_NEEDS_RSP) {
                        if (avail & OS_SC_NEEDS_RSP) {
                            *sp = gfx;
                            avail &= ~OS_SC_NEEDS_RSP;
                        }
                    } else if ((gfx->state & OS_SC_NEEDS_RDP) && (avail & OS_SC_NEEDS_RDP)) {
                        *dp = gfx;
                        avail &= ~OS_SC_NEEDS_RDP;
                        sc->gfxListHead = sc->gfxListHead->next;
                        if (sc->gfxListHead == NULL) {
                            sc->gfxListTail = NULL;
                        }
                    }
                    break;
                case 1:
                case 4:
                case 5:
                    break;
            }
        }
    }
    if (avail != availRCP) {
        return func_80000A88(sc, sp, dp, avail);
    }
    return avail;
}
void func_8000101C(void *arg) {
    OSMesg msg;
    OSSched *sc = (OSSched *)arg;
    OSScClient *client;

    for (;;) {
        osRecvMesg(&sc->interruptQ, &msg, OS_MESG_BLOCK);
        switch ((s32)msg) {
            case SC_MSG_RETRACE:
                if (D_80019FAC == 0) {
                    D_80019FAC = 1;
                    D_8001C460 = osGetTime();
                    D_80019FA0++;
                }
                func_80000E58(sc);
                break;
            case SC_MSG_RSP_DONE:
                if (sc->curRSPTask->list.t.type == M_GFXTASK) {
                    D_8001C448 = osGetTime();
                } else if (sc->curRSPTask->list.t.type == M_AUDTASK) {
                    D_8001C470 = osGetTime();
                }
                func_80000E0C();
                func_8000101C_inl1(sc);
                break;
            case SC_MSG_RDP_DONE:
                if (D_80019FAC == 2) {
                    D_8001C458 = osGetTime();
                    D_80019FAC = 3;
                }
                func_80000D44();
                func_8000101C_inl2(sc);
                break;
            case SC_MSG_PRE_NMI:
                for (client = sc->clientList; client != NULL; client = client->next) {
                    osSendMesg(client->msgQ, (OSMesg)&sc->prenmiMsg, OS_MESG_NOBLOCK);
                }
                break;
        }
    }
}

static void func_80000E58(OSSched *sc) {
    OSScTask *rspTask;
    OSScClient *client;
    s32 state;
    OSScTask *sp = NULL;
    OSScTask *dp = NULL;

    sc->frameCount++;
    while (osRecvMesg(&sc->cmdQ, (OSMesg *)&rspTask, OS_MESG_NOBLOCK) != -1) {
        func_80000E58_inl1(sc, rspTask);
    }
    if (sc->doAudio && sc->curRSPTask != NULL) {
        func_80000E58_inl2(sc);
    } else {
        state = ((sc->curRSPTask == NULL) << 1) | (sc->curRDPTask == NULL);
        if (func_80000A88(sc, &sp, &dp, state) != state) {
            func_80000908(sc, sp, dp);
        }
    }
    for (client = sc->clientList; client != NULL; client = client->next) {
        osSendMesg(client->msgQ, (OSMesg)sc, OS_MESG_NOBLOCK);
    }
}

static void func_8000101C_inl1(OSSched *sc) {
    OSScTask *t;
    OSScTask *sp = NULL;
    OSScTask *dp = NULL;
    s32 state;

    SC_ASSERT(sc->curRSPTask, 0x153);
    t = sc->curRSPTask;
    sc->curRSPTask = NULL;
    if ((t->state & SC_STATE_YIELD) && osSpTaskYielded(&t->list)) {
        t->state |= SC_STATE_YIELDED;
        if ((t->flags & OS_SC_TYPE_MASK) == SC_TYPE_XBUS) {
            t->next = sc->gfxListHead;
            sc->gfxListHead = t;
            if (sc->gfxListTail == NULL) {
                sc->gfxListTail = t;
            }
        }
    } else {
        t->state &= ~OS_SC_NEEDS_RSP;
        func_80000C7C(sc, t);
    }
    state = ((sc->curRSPTask == NULL) << 1) | (sc->curRDPTask == NULL);
    if (func_80000A88(sc, &sp, &dp, state) != state) {
        func_80000908(sc, sp, dp);
    }
}

static void func_8000101C_inl2(OSSched *sc) {
    OSScTask *t;
    OSScTask *sp = NULL;
    OSScTask *dp = NULL;
    s32 state;

    SC_ASSERT(sc->curRDPTask, 0x17E);
    SC_ASSERT(sc->curRDPTask->list.t.type == M_GFXTASK, 0x17F);
    t = sc->curRDPTask;
    sc->curRDPTask = NULL;
    t->state &= ~OS_SC_NEEDS_RDP;
    func_80000C7C(sc, t);
    state = ((sc->curRSPTask == NULL) << 1) | (sc->curRDPTask == NULL);
    if (func_80000A88(sc, &sp, &dp, state) != state) {
        func_80000908(sc, sp, dp);
    }
}

static s32 func_80000C7C(OSSched *sc, OSScTask *t) {
    static s32 D_80019FB8 = 1; /* the screen is still blanked */

    if ((t->state & OS_SC_RCP_MASK) == 0) {
        SC_ASSERT(t->msgQ, 0x1B9);
        osSendMesg(t->msgQ, t->msg, OS_MESG_BLOCK);
        if (t->list.t.type == M_GFXTASK) {
            if ((t->flags & OS_SC_SWAPBUFFER) && (t->flags & OS_SC_LAST_TASK)) {
                if (D_80019FB8) {
                    osViBlack(FALSE);
                    D_80019FB8 = 0;
                }
                osViSwapBuffer(t->framebuffer);
            }
        }
        return 1;
    }
    return 0;
}

static void func_80000E58_inl1(OSSched *sc, OSScTask *t) {
    s32 type = t->list.t.type;

    SC_ASSERT((type == M_AUDTASK) || (type == M_GFXTASK), 0x1D9);
    if (type == M_AUDTASK) {
        if (sc->audioListTail != NULL) {
            sc->audioListTail->next = t;
        } else {
            sc->audioListHead = t;
        }
        sc->audioListTail = t;
        sc->doAudio = TRUE;
    } else {
        if (sc->gfxListTail != NULL) {
            sc->gfxListTail->next = t;
        } else {
            sc->gfxListHead = t;
        }
        sc->gfxListTail = t;
    }
    t->next = NULL;
    t->state = t->flags & OS_SC_RCP_MASK;
}

static void func_80000908(OSSched *sc, OSScTask *sp, OSScTask *dp) {
    s32 rv;

    SC_ASSERT(sc->curRSPTask == 0, 0x201);
    if (sp != NULL) {
        if (sp->list.t.type == M_AUDTASK) {
            osWritebackDCacheAll();
        }
        sp->state &= ~(SC_STATE_YIELD | SC_STATE_YIELDED);
        osSpTaskLoad(&sp->list);
        if (sp->list.t.type == M_GFXTASK) {
            if (D_80019FAC == 1) {
                D_8001C440 = osGetTime();
                D_8001C450 = osGetTime();
                D_80019FAC = 2;
            }
        } else if (sp->list.t.type == M_AUDTASK) {
            D_8001C468 = osGetTime();
        }
        osSpTaskStartGo(&sp->list);
        sc->curRSPTask = sp;
        if (sp == dp) {
            sc->curRDPTask = dp;
        }
    }
    if (dp != NULL && dp != sp) {
        SC_ASSERT(dp->list.t.output_buff, 0x219);
        rv = osDpSetNextBuffer(dp->list.t.output_buff, *dp->list.t.output_buff_size);
        D_80019FB0 = 1;
        D_80019FB4 = 0;
        SC_ASSERT(rv == 0, 0x228);
        sc->curRDPTask = dp;
    }
}

static void func_80000E58_inl2(OSSched *sc) {
    if (sc->curRSPTask->list.t.type == M_GFXTASK) {
        sc->curRSPTask->state |= SC_STATE_YIELD;
        osSpTaskYield();
    }
}

OSScTask *func_800008B0(OSScTask *t) {
    void *fb[4];

    if (t != NULL) {
        fb[0] = osViGetCurrentFramebuffer();
        if (osViGetNextFramebuffer() != fb[0]) {
            return NULL;
        }
        return t;
    }
    if (0) {
        func_800018A8("sc->curRDPTask == gfx", "sched.c", 0);
    }
    return NULL;
}

