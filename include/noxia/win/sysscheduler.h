#ifndef NOXIASYSSCHEDULER_H
#define NOXIASYSSCHEDULER_H

#include "sysdef.h"

void nSchedulerCycleBegin(nContext *context);
void nSchedulerCycleEnd(nContext *context);
uint64 nSchedulerGetTime(nContext *context);

void nSchedulerCycleBegin(nContext *context) {
    if (context->nSchedulerFreq.QuadPart == 0) {
        QueryPerformanceFrequency(&context->nSchedulerFreq);
    }

    timeBeginPeriod(1);
    QueryPerformanceCounter(&context->nSchedulerCycleStart);
}

void nSchedulerCycleEnd(nContext *context) {
    uint64 cycleDuration = 10000000 / context->nSchedulerCycleRate;

    int32 sleepTime = (cycleDuration - nSchedulerGetTime(context)) / 10000 - 3;
    if (sleepTime > 0) {
        Sleep(sleepTime);
    }

    while (nSchedulerGetTime(context) < cycleDuration) {
    }

    timeEndPeriod(1);
}

static uint64 nSchedulerGetTime(nContext *context) {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    return (now.QuadPart - context->nSchedulerCycleStart.QuadPart) * 10000000 / context->nSchedulerFreq.QuadPart;
}

#endif // NOXIASYSSCHEDULER_H
