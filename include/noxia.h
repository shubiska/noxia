#include "typedef.h"
#include "win/window.h"
#ifdef _WIN32
#include "win/typedef.h"
#else
#error "Unsupported OS"
#endif

nContext *nContextCreate();
void nContextEvents(nContext *context);
void nContextClose(nContext *context);

nContext context;

nContext *nContextCreate() {
    nWindow *window = _nWindowCreate();
    if (window == null) {
        return null;
    }

    context._nInternalWindow = window;

    return &context;
}

void nContextEvents(nContext *context) {
    _nWindowShow(context->_nInternalWindow);

    while (!context->_nInternalClose) {
        _nWindowEvents(context->_nInternalWindow);
        nWindowEvent event = context->_nInternalWindow->windowEvent;
        if (event) {
            if (event == CloseRequested) {
                context->_nInternalClose = true;
            }

            context->_nInternalWindow->windowEvent = None;
        }
    }

    _nWindowDestroy(context->_nInternalWindow);
}

void nContextClose(nContext *context) {
    context->_nInternalClose = true;
}
