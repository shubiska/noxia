#ifdef _WIN64
#include "../include/noxia/win/syswindow.h"
#endif

#include "../include/noxia/math.h"
#include <string.h>

nContext *nContextCreate();
void nContextEvents(nContext *context);
void nContextClose(nContext *context);
void nContextSetTitle(nContext *context, char *title);
void nContextSetSize(nContext *context, uint32 width, uint32 height);
void nContextSetPosition(nContext *context, uint32 x, uint32 y);
void nContextCenter(nContext *context);

nContext *nContextCreate() {
    nContext *context = nWindowCreate();
    if (context == null) {
        return null;
    }

    return context;
}

void nContextEvents(nContext *context) {
    if (context == null) {
        return;
    }

    nWindowShow(context, true);

    while (!context->nContextClose) {
        nWindowEvents(context);

        if (context->nContextCloseRequested) {
            nContextClose(context);
        }
    }

    nWindowDestroy(context);
}

void nContextClose(nContext *context) {
    if (context == null) {
        return;
    }

    context->nContextClose = true;
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

    width = (uint32)nClampU(width, 128, nDisplayGetWidth());
    height = (uint32)nClampU(height, 128, nDisplayGetHeight());

    nWindowSetSize(context, width, height);
}

void nContextSetPosition(nContext *context, uint32 x, uint32 y) {
    if (context == null) {
        return;
    }

    x = (uint32)nClampU(x, 0, nDisplayGetWidth());
    y = (uint32)nClampU(y, 0, nDisplayGetHeight());

    nWindowSetPosition(context, x, y);
}

void nContextCenter(nContext *context) {
    if (context == null) {
        return;
    }

    nWindowCenter(context);
}
