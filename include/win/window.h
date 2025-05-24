#ifndef NOXIAWINDOWWIN_H
#define NOXIAWINDOWWIN_H
#define _CRT_SECURE_NO_WARNINGS

#include "typedef.h"
#include <Windows.h>

#define StyleWindowed WS_OVERLAPPEDWINDOW & ~(WS_SIZEBOX | WS_MAXIMIZEBOX)

LRESULT CALLBACK _nWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    nWindow *window = (nWindow *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch (uMsg) {
    case WM_CLOSE:
        window->windowEvent = CloseRequested;
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

nWindow *_nWindowCreate() {
    uint16 displayWidth = GetSystemMetrics(SM_CXSCREEN);
    uint16 displayHeight = GetSystemMetrics(SM_CYSCREEN);
    uint16 displayCenterX = (displayWidth - displayWidth / 2) / 2;
    uint16 displayCenterY = (displayHeight - displayHeight / 2) / 2;

    HINSTANCE windowInstanceHandle = GetModuleHandle(NULL);
    WNDCLASS windowClass = {0};
    windowClass.lpfnWndProc = _nWindowProcedure;
    windowClass.hInstance = windowInstanceHandle;
    windowClass.lpszClassName = "Noxia";

    RegisterClass(&windowClass);

    HWND windowHandle = CreateWindowEx(0, "Noxia", "Noxia", StyleWindowed, displayCenterX, displayCenterY, displayWidth / 2, displayHeight / 2, NULL, NULL,
                                       windowInstanceHandle, null);
    if (windowHandle == null) {
        return null;
    }

    nWindow *window = (nWindow *)malloc(sizeof(nWindow));
    window->windowHandle = windowHandle;
    window->width = displayWidth / 2;
    window->height = displayHeight / 2;

    SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)window);

    return window;
}

void _nWindowShow(nWindow *window) {
    UpdateWindow(window->windowHandle);
    ShowWindow(window->windowHandle, SW_SHOWNORMAL);
}

void _nWindowDestroy(nWindow *window) {
    DestroyWindow(window->windowHandle);
    free(window);
}

void _nWindowEvents(nWindow *window) {
    while (PeekMessage(&window->windowMessage, null, 0, 0, PM_REMOVE)) {
        TranslateMessage(&window->windowMessage);
        DispatchMessage(&window->windowMessage);
    }
}

#endif // NOXIAWINDOWWIN_H
