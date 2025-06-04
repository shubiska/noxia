#ifndef NOXIASYSDEF_H
#define NOXIASYSDEF_H

#include "../typedef.h"
#include <Windows.h>

typedef struct nContext nContext;

struct nContext {
    // window
    HWND nWindowHandle;
    HDC nWindowDeviceContext;
    uint32 nWindowStyle;
    uint32 nWindowWidth;
    uint32 nWindowHeight;
    bool nWindowFocused;

    // scheduler
    LARGE_INTEGER nSchedulerFreq;
    LARGE_INTEGER nSchedulerCycleStart;
    uint32 nSchedulerCycleRate;

    // graphics
    HGLRC nGraphicsContext;

    // input
    uint8 nInputKeyboardState[256];
    uint8 nInputKeyboardMap[256];
    uint8 nInputKeyboardKeys[256];

    u32Vector2 nInputMouseCoordinates;
    uint8 nInputMouseButtons[3];

    // context
    bool nWindowIsUnreachable;
    bool Close;
    bool CloseRequested;
    bool Vsync;
};

#define nSysAlloc(Type) (Type *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(Type))
#define nSysFree(Data) HeapFree(GetProcessHeap(), 0, Data)

#endif // NOXIASYSDEF_H
