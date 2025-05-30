#ifdef _WIN64
#include "../include/noxia/win/sysgraphics.h"
#include "../include/noxia/win/sysscheduler.h"
#include "../include/noxia/win/syswindow.h"
#endif

#include "../include/noxia.h"
#include "../include/noxia/math.h"
#include <string.h>

static nContext *nContextCreate() {
    nContext *context = nWindowCreate();
    if (context == null) {
        return null;
    }

    nGraphicsCreate(context);

    nContextSetRate(context, nDisplayGetRate());
    nContextSetVsync(context, true);

    return context;
}

static void nContextEvents(nContext *context) {
    if (context == null) {
        return;
    }

    nWindowShow(context, true);

    while (!context->nContextClose) {
        if (!context->nGraphicsVsync) {
            nSchedulerCycleBegin(context);
        }

        nWindowEvents(context);

        if (context->nContextCloseRequested) {
            nContextClose(context);
        }

        nGraphicsRenderBegin(context);

        nGraphicsRenderEnd(context);

        if (!context->nGraphicsVsync) {
            nSchedulerCycleEnd(context);
        }
    }

    nWindowDestroy(context);
}

static void nContextClose(nContext *context) {
    if (context == null) {
        return;
    }

    context->nContextClose = true;
}

static void nContextSetTitle(nContext *context, char *title) {
    if (context == null) {
        return;
    }

    if (strlen(title) > 128) {
        title[128] = '\0';
    }

    nWindowSetTitle(context, title);
}

static void nContextSetSize(nContext *context, uint32 width, uint32 height) {
    if (context == null) {
        return;
    }

    width = (uint32)nClampU(width, 128, nDisplayGetWidth());
    height = (uint32)nClampU(height, 128, nDisplayGetHeight());

    nWindowSetSize(context, width, height);
}

static void nContextSetPosition(nContext *context, uint32 x, uint32 y) {
    if (context == null) {
        return;
    }

    x = (uint32)nClampU(x, 0, nDisplayGetWidth());
    y = (uint32)nClampU(y, 0, nDisplayGetHeight());

    nWindowSetPosition(context, x, y);
}

static void nContextCenter(nContext *context) {
    if (context == null) {
        return;
    }

    nWindowCenter(context);
}

static void nContextSetRate(nContext *context, uint32 rate) {
    context->nSchedulerCycleRate = (uint32)nClampU(rate, 1, 360);
}

static void nContextSetVsync(nContext *context, bool vsync) {
    context->nGraphicsVsync = vsync;
    nGraphicsSetVsync(context, vsync);
}
