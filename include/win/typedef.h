#ifndef NOXIATYPEWIN_H
#define NOXIATYPEWIN_H

#include "../typedef.h"
#include <Windows.h>

typedef struct {
    nWindowEvent windowEvent;
    MSG windowMessage;
    HWND windowHandle;
    uint16 width, height;
} nWindow;

typedef struct {
    bool _nInternalClose;
    nWindow *_nInternalWindow;
} nContext;

#endif // NOXIATYPEWIN_H
