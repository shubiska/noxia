#ifndef NOXIASYSDISPLAY_H
#define NOXIASYSDISPLAY_H

#include "sysdef.h"

u32Vector2 nDisplayGetSize(nContext *context);
uint32 nDisplayGetRate();

u32Vector2 nDisplayGetSize(nContext *context) {
    HMONITOR monitor = MonitorFromWindow(context->nWindowHandle, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO info = {.cbSize = sizeof(MONITORINFO)};
    GetMonitorInfo(monitor, &info);

    return (u32Vector2){info.rcMonitor.right - info.rcMonitor.left, info.rcMonitor.bottom - info.rcMonitor.top};
}

uint32 nDisplayGetRate() {
    DEVMODE devMode = {0};
    devMode.dmSize = sizeof(DEVMODE);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);

    return devMode.dmDisplayFrequency;
}

#endif // NOXIASYSDISPLAY_H
