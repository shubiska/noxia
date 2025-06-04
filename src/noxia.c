#ifdef _WIN64
#include "../include/noxia/win/sysdisplay.h"
#include "../include/noxia/win/sysgraphics.h"
#include "../include/noxia/win/sysinput.h"
#include "../include/noxia/win/sysscheduler.h"
#include "../include/noxia/win/syswindow.h"

#endif

#include "../include/noxia.h"
#include <stdio.h>
#include <string.h>

nContext *nContextCreate() {
    nContext *context = nSysAlloc(nContext);
    if (context == null) {
        return null;
    }

    if (!nWindowCreate(context)) {
        return null;
    }

    u32Vector2 displaySize = nDisplayGetSize(context);

    nContextSetSize(context, displaySize.x / 2, displaySize.y / 2);
    nContextCenter(context);

    nGraphicsCreate(context);

    nInputKeyboardSetup(context);

    nContextSetRate(context, nDisplayGetRate());
    nContextSetVsync(context, true);

    return context;
}

void nContextEvents(nContext *context) {
    if (context == null) {
        return;
    }

    nWindowShow(context, true);

    while (!context->Close) {
        if (!context->Vsync) {
            nSchedulerCycleBegin(context);
        }

        nWindowEvents(context);

        if (context->nWindowIsUnreachable) {
            nContextCenter(context);
            context->nWindowIsUnreachable = false;
        }

        if (context->nWindowFocused) {
            nInputMouseUpdate(context);
            nInputKeyboardUpdate(context);
        }

        if (context->CloseRequested) {
            nContextClose(context);
        }

        nGraphicsRenderBegin(context);

        nGraphicsRenderEnd(context);

        if (!context->Vsync) {
            nSchedulerCycleEnd(context);
        }
    }

    nGraphicsDestroy(context);
    nWindowDestroy(context);
}

void nContextClose(nContext *context) {
    if (context == null) {
        return;
    }

    context->Close = true;
}

void nContextCenter(nContext *context) {
    if (context == null) {
        return;
    }

    u32Vector2 displaySize = nDisplayGetSize(context);
    nWindowCenter(context, displaySize);
}

void nContextSetTitle(nContext *context, char *title) {
    if (context == null) {
        return;
    }

    if (strlen(title) > 128) {
        title[128] = '\0';
    }

    nWindowSetTitle(context, title);
}

void nContextSetSize(nContext *context, uint32 width, uint32 height) {
    if (context == null) {
        return;
    }

    u32Vector2 displaySize = nDisplayGetSize(context);

    width = nClamp(width, 128, displaySize.x);
    height = nClamp(height, 128, displaySize.y);

    nWindowSetSize(context, width, height);
    nGraphicsResize(context);
}

void nContextSetPosition(nContext *context, uint32 x, uint32 y) {
    if (context == null) {
        return;
    }

    u32Vector2 displaySize = nDisplayGetSize(context);

    x = nClamp(x, 0, displaySize.x);
    y = nClamp(y, 0, displaySize.y);

    nWindowSetPosition(context, x, y);
}

void nContextSetRate(nContext *context, uint32 rate) {
    if (context == null) {
        return;
    }

    context->nSchedulerCycleRate = (uint32)nClamp(rate, 1, 360);
}

void nContextSetVsync(nContext *context, bool vsync) {
    if (context == null) {
        return;
    }

    nGraphicsSetVsync(context, vsync);

    context->Vsync = vsync;
}
