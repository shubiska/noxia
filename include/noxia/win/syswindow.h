#ifndef NOXIASYSWINDOW_H
#define NOXIASYSWINDOW_H

#include "sysdef.h"
#include <winuser.h>

#define StyleWindowed WS_OVERLAPPEDWINDOW & ~(WS_SIZEBOX | WS_MAXIMIZEBOX)
#define StyleBorderless WS_POPUPWINDOW

bool nWindowCreate(nContext *context);
void nWindowEvents(nContext *context);
void nWindowShow(nContext *context, bool visible);
void nWindowSetTitle(nContext *context, char *title);
void nWindowSetSize(nContext *context, uint32 width, uint32 height);
void nWindowSetPosition(nContext *context, uint32 x, uint32 y);
void nWindowCenter(nContext *context, u32Vector2 displaySize);
void nWindowDestroy(nContext *context);
LRESULT CALLBACK nWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool nWindowCreate(nContext *context) {
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);

    WNDCLASS windowClass = {0};
    windowClass.lpfnWndProc = nWindowProcedure;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.lpszClassName = "Noxia";
    if (RegisterClass(&windowClass) == null) {
        return false;
    }

    HWND windowHandle = CreateWindowEx(0, windowClass.lpszClassName, "Noxia", StyleWindowed, 0, 0, 0, 0, NULL, NULL, windowClass.hInstance, null);
    if (windowHandle == null) {
        return false;
    }

    HDC deviceContext = GetDC(windowHandle);
    if (deviceContext == null) {
        return false;
    }

    SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)context);

    context->nWindowHandle = windowHandle;
    context->nWindowDeviceContext = deviceContext;
    context->nWindowStyle = StyleWindowed;

    return true;
}

void nWindowEvents(nContext *context) {
    MSG message;
    while (PeekMessage(&message, null, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    context->nWindowFocused = GetFocus() != null;
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

    context->nWindowWidth = width;
    context->nWindowHeight = height;

    AdjustWindowRectEx(&rect, context->nWindowStyle, FALSE, null);

    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    SetWindowPos(context->nWindowHandle, null, null, null, width, height, SWP_NOMOVE | SWP_NOZORDER);
}

void nWindowSetPosition(nContext *context, uint32 x, uint32 y) {
    SetWindowPos(context->nWindowHandle, null, x, y, null, null, SWP_NOSIZE | SWP_NOZORDER);
}

void nWindowCenter(nContext *context, u32Vector2 displaySize) {
    RECT rect;
    GetWindowRect(context->nWindowHandle, &rect);

    uint32 x = (displaySize.x - (rect.right - rect.left)) / 2;
    uint32 y = (displaySize.y - (rect.bottom - rect.top)) / 2;

    SetWindowPos(context->nWindowHandle, null, x, y, null, null, SWP_NOSIZE | SWP_NOZORDER);
}

void nWindowDestroy(nContext *context) {
    DestroyWindow(context->nWindowHandle);
    HeapFree(GetProcessHeap(), 0, context);
}

static LRESULT CALLBACK nWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    nContext *context = (nContext *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch (uMsg) {
    case WM_ACTIVATE: {
        if (LOWORD(lParam) != WA_ACTIVE) {
            context->nWindowIsUnreachable = (MonitorFromWindow(context->nWindowHandle, MONITOR_DEFAULTTONULL) == null);
        }
        return 0;
    }
    case WM_CLOSE: {
        context->CloseRequested = true;
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
