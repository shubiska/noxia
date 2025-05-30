#ifndef NOXIASYSDEF_H
#define NOXIASYSDEF_H

#include "../../noxia.h"
#include <Windows.h>

struct nContext {
    bool nContextClose;
    bool nContextCloseRequested;

    // window
    HWND nWindowHandle;
    HDC nWindowDeviceContext;
    uint32 nWindowStyle;

    // graphics
    bool nGraphicsVsync;

    // scheduler
    LARGE_INTEGER nSchedulerFreq;
    LARGE_INTEGER nSchedulerCycleStart;
    uint32 nSchedulerCycleRate;
};

#endif // NOXIASYSDEF_H
