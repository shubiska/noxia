#ifndef NOXIASYSDISPLAY_H
#define NOXIASYSDISPLAY_H

#include "sysdef.h"

uint32 nDisplayGetWidth();
uint32 nDisplayGetHeight();
uint32 nDisplayGetRate();

uint32 nDisplayGetWidth() {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);

    return rect.right;
}

uint32 nDisplayGetHeight() {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);

    return rect.bottom;
}

uint32 nDisplayGetRate() {
    DEVMODE devMode = {0};
    devMode.dmSize = sizeof(DEVMODE);

    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);

    return devMode.dmDisplayFrequency;
}

#endif // NOXIASYSDISPLAY_H
