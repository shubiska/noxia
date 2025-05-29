#ifndef NOXIASYSDISPLAY_H
#define NOXIASYSDISPLAY_H

#include "../typedef.h"
#include <Windows.h>

uint32 nDisplayGetWidth();
uint32 nDisplayGetHeight();
uint32 nDisplayGetRate();

static uint32 nDisplayGetWidth() {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);

    return rect.right;
}

static uint32 nDisplayGetHeight() {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);

    return rect.bottom;
}

static uint32 nDisplayGetRate() {
    DEVMODE devMode = {};
    devMode.dmSize = sizeof(DEVMODE);

    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);

    return devMode.dmDisplayFrequency;
}

#endif // NOXIASYSDISPLAY_H
