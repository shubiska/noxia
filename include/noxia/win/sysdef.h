#ifndef NOXIASYSDEF_H
#define NOXIASYSDEF_H

#include "../typedef.h"
#include <Windows.h>

typedef struct {
    bool nContextClose;
    bool nContextCloseRequested;

    // window
    HWND nWindowHandle;
    uint32 nWindowStyle;
} nContext;

#endif // NOXIASYSDEF_H
