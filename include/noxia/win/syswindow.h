#ifndef NOXIASYSWINDOW_H
#define NOXIASYSWINDOW_H
#include "sysdef.h"

#define StyleWindowed WS_OVERLAPPEDWINDOW & ~(WS_SIZEBOX | WS_MAXIMIZEBOX)

nContext *nWindowCreate();
void nWindowEvents(nContext *context);
void nWindowShow(nContext *context);
void nWindowDestroy(nContext *context);
LRESULT CALLBACK nWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static inline nContext *nWindowCreate() {
    WNDCLASS windowClass = {0};
    windowClass.lpfnWndProc = nWindowProcedure;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.lpszClassName = "Noxia";
    RegisterClass(&windowClass);

    HWND windowHandle = CreateWindowEx(0, windowClass.lpszClassName, "Noxia", StyleWindowed, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, windowClass.hInstance, null);
    if (windowHandle == null) {
        return null;
    }

    nContext *context = (nContext *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(nContext));
    SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)context);

    context->nWindowHandle = windowHandle;

    return context;
}

static void nWindowEvents(nContext *context) {
    MSG message;
    while (PeekMessage(&message, null, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

static void nWindowShow(nContext *context) {
    UpdateWindow(context->nWindowHandle);
    ShowWindow(context->nWindowHandle, SW_SHOWNORMAL);
}

static void nWindowDestroy(nContext *context) {
    DestroyWindow(context->nWindowHandle);
    HeapFree(GetProcessHeap(), 0, context);
}

static LRESULT CALLBACK nWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    nContext *context = (nContext *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch (uMsg) {
    case WM_CLOSE: {
        context->nContextCloseRequested = true;
        return 0;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

#endif
