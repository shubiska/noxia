#include "../include/noxia.h"

nContext *nContextCreate() {
    nContext *context = nWindowCreate();
    if (context == null) {
        return null;
    }

    return context;
}

void nContextEvents(nContext *context) {
    nWindowShow(context);

    while (!context->nContextClose) {
        nWindowEvents(context);
        if (context->nContextCloseRequested) {
            nContextClose(context);
        }
    }

    nWindowDestroy(context);
}
void nContextClose(nContext *context) {
    context->nContextClose = true;
}
