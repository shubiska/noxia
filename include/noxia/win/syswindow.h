#ifndef NOXIASYSWINDOW_H
#define NOXIASYSWINDOW_H

#include "sysdef.h"
#include "sysdisplay.h"

#define StyleWindowed WS_OVERLAPPEDWINDOW & ~(WS_SIZEBOX | WS_MAXIMIZEBOX)
#define StyleBorderless WS_POPUP

nContext *nWindowCreate();
void nWindowEvents(nContext *context);
void nWindowShow(nContext *context, bool visible);
void nWindowSetTitle(nContext *context, char *title);
void nWindowSetSize(nContext *context, uint32 width, uint32 height);
void nWindowSetPosition(nContext *context, uint32 x, uint32 y);
void nWindowCenter(nContext *context);
void nWindowDestroy(nContext *context);
LRESULT CALLBACK nWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

nContext *nWindowCreate() {
    WNDCLASS windowClass = {0};
    windowClass.lpfnWndProc = nWindowProcedure;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.lpszClassName = "Noxia";
    if (RegisterClass(&windowClass) == null) {
        return null;
    }

    HWND windowHandle = CreateWindowEx(0, windowClass.lpszClassName, "Noxia", StyleWindowed, 0, 0, 0, 0, NULL, NULL, windowClass.hInstance, null);
    if (windowHandle == null) {
        return null;
    }

    HDC deviceContext = GetDC(windowHandle);
    if (deviceContext == null) {
        return null;
    }

    nContext *context = (nContext *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(nContext));
    if (context == null) {
        return null;
    }

    SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)context);

    context->nWindowHandle = windowHandle;
    context->nWindowDeviceContext = deviceContext;
    context->nWindowStyle = StyleWindowed;

    nWindowSetSize(context, nDisplayGetWidth() / 2, nDisplayGetHeight() / 2);
    nWindowCenter(context);

    return context;
}

void nWindowEvents(nContext *context) {
    MSG message;
    while (PeekMessage(&message, null, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

void nWindowShow(nContext *context, bool visible) {
    UpdateWindow(context->nWindowHandle);
    ShowWindow(context->nWindowHandle, visible);
}

void nWindowSetTitle(nContext *context, char *title) {
    SetWindowText(context->nWindowHandle, title);
}

void nWindowSetSize(nContext *context, uint32 width, uint32 height) {
    RECT rect = {0, 0, width, height};

    AdjustWindowRectEx(&rect, context->nWindowStyle, FALSE, null);

    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    SetWindowPos(context->nWindowHandle, null, null, null, width, height, SWP_NOMOVE | SWP_NOZORDER);
}

void nWindowSetPosition(nContext *context, uint32 x, uint32 y) {
    SetWindowPos(context->nWindowHandle, null, x, y, null, null, SWP_NOSIZE | SWP_NOZORDER);
}
void nWindowCenter(nContext *context) {
    RECT rect;
    GetWindowRect(context->nWindowHandle, &rect);

    uint32 x = (nDisplayGetWidth() - (rect.right - rect.left)) / 2;
    uint32 y = (nDisplayGetHeight() - (rect.bottom - rect.top)) / 2;

    SetWindowPos(context->nWindowHandle, null, x, y, null, null, SWP_NOSIZE | SWP_NOZORDER);
}

void nWindowDestroy(nContext *context) {
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
