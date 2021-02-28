/*******************************************************************

    PROPRIETARY NOTICE

These coded instructions, statements, and computer programs contain
proprietary information of eComCloud Object Solutions, and they are
protected under copyright law. They may not be distributed, copied,
or used except under the provisions of the terms of the Source Code
Licence Agreement, in the file "LICENCE.md", which should have been
included with this software

    Copyright Notice

    (c) 2015-2021 eComCloud Object Solutions.
        All rights reserved.
********************************************************************/

#include "eci/Logger.hh"
#include "eci/Platform.h"

#if defined(ECI_EVENT_DRIVER_Poll)
#include <sys/poll.h>
#include <sys/signal.h>
#include <time.h>

typedef timer_t TimerID;
#elif defined(ECI_EVENT_DRIVER_EPoll)
#warning EPoll Driver
#elif defined(ECI_EVENT_DRIVER_KQueue)

typedef int TimerID;
#endif

class EventLoop : Logger
{
#if defined(ECI_EVENT_DRIVER_Poll)
#warning Poll driver
    int nPFDs;
    struct pollfd *pFDs;

    static void sigHandler(int signum, siginfo_t *siginfo, void *ctx);
#elif defined(ECI_EVENT_DRIVER_EPoll)
#warning EPoll Driver
    int epollFD;
#elif defined(ECI_EVENT_DRIVER_KQueue)
#warning KQueue
    int kqFD;
#endif

  public:
    EventLoop(Logger *parent = NULL) : Logger("evloop", parent){};

    /**
     *  Begin monitoring an FD for events.
     *
     * @returns -errno if unsuccessful.
     */
    int addFD(int fd);

    /**
     * Handle a signal with the event loop.
     *
     * @returns -errno if unsuccessful.
     */
    int addSignal(int signum);

    /**
     * Adds a timer to go off in \param ts time.
     *
     * @returns A unique timer ID (>= 0) if successful.
     * @returns -errno if unsuccessful.
     */
    int addTimer(struct timespec *ts);

    /**
     * Initialise this event loop.
     *
     * @returns -errno if unsuccessful.
     */
    int init();

    /**
     * Begin an event-loop iteration for a max of \p ts time.
     * If \param ts is a NULL pointer, waits indefinitely for an event.
     * If \param ts points to a zero-valued timespec, returns immediately.
     *
     * @returns -errno if an error is encountered
     * @returns 0 if timed out
     * @returns >0 if events were received and dispatched.
     */
    int loop(struct timespec *ts);
};