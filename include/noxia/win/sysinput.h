#ifndef NOXIASYSINPUT_H
#define NOXIASYSINPUT_H

#include "sysdef.h"
#include <stdio.h>
#include <winuser.h>

typedef enum {
    K_UNKNOWN,
    K_F1,
    K_F2,
    K_F3,
    K_F4,
    K_F5,
    K_F6,
    K_F7,
    K_F8,
    K_F9,
    K_F10,
    K_F11,
    K_F12,
    K_ESCAPE,
    K_TAB,
    K_CAPSLOCK,
    K_LSHIFT,
    K_RSHIFT,
    K_LCONTROL,
    K_RCONTROL,
    K_LALT,
    K_RALT,
    K_SPACEBAR,
    K_BACKSPACE,
    K_RETURN,
    K_UP,
    K_LEFT,
    K_DOWN,
    K_RIGHT,
    K_1,
    K_2,
    K_3,
    K_4,
    K_5,
    K_6,
    K_7,
    K_8,
    K_9,
    K_0,
    K_A,
    K_B,
    K_C,
    K_D,
    K_E,
    K_F,
    K_G,
    K_H,
    K_I,
    K_J,
    K_K,
    K_L,
    K_M,
    K_N,
    K_O,
    K_P,
    K_Q,
    K_R,
    K_S,
    K_T,
    K_U,
    K_V,
    K_W,
    K_X,
    K_Y,
    K_Z,
    K_ANY,
} nKeyboardKey;

enum {
    M_LEFT,
    M_RIGHT,
    M_MIDDLE,
} nMouseKey;

enum {
    None,
    Pressed,
    Held,
    Released,
} nKeyState;

void nInternalKeyState(bool isPressed, uint8 *map);
nKeyboardKey nInternalGetKey(nContext *context, uint8 key);

void nInputKeyboardSetup(nContext *context) {
    GetKeyboardState(context->nInputKeyboardState);
    for (uint8 key = 0; key < 255; key++) {
        uint8 result = nInternalGetKey(context, key);
        if (result) {
            context->nInputKeyboardMap[key] = result;
        }
    }
}

void nInputKeyboardUpdate(nContext *context) {
    GetKeyboardState(context->nInputKeyboardState);
    for (int vk = 0; vk < 255; vk++) {
        uint8 key = context->nInputKeyboardMap[vk];
        if (key != K_UNKNOWN) {
            nInternalKeyState((context->nInputKeyboardState[vk] & 0x80), &context->nInputKeyboardKeys[key]);
        }
    }
}

bool nInputKeyboardPressed(nContext *context, nKeyboardKey key) {
    return context->nInputKeyboardKeys[key] == 1;
}

bool nInputKeyboardReleased(nContext *context, nKeyboardKey key) {
    return context->nInputKeyboardKeys[key] == 3;
}

void nInputMouseUpdate(nContext *context) {
    nInternalKeyState((GetAsyncKeyState(VK_LBUTTON) & 0x8000), &context->nInputMouseButtons[0]);
    nInternalKeyState((GetAsyncKeyState(VK_RBUTTON) & 0x8000), &context->nInputMouseButtons[1]);
    nInternalKeyState((GetAsyncKeyState(VK_MBUTTON) & 0x8000), &context->nInputMouseButtons[2]);

    POINT mouseCoordinates;
    GetCursorPos(&mouseCoordinates);
    ScreenToClient(context->nWindowHandle, &mouseCoordinates);

    context->nInputMouseCoordinates.x = (uint32)nClamp(mouseCoordinates.x, 0, context->nWindowWidth);
    context->nInputMouseCoordinates.y = (uint32)nClamp(mouseCoordinates.y, 0, context->nWindowHeight);
}

static void nInternalKeyState(bool isPressed, uint8 *map) {
    if (isPressed) {
        if (*map == None || *map == Pressed) {
            (*map)++;
        }
    } else {
        if (*map == Pressed || *map == Held) {
            *map = Released;
        } else {
            *map = None;
        }
    }
}

nKeyboardKey nInternalGetKey(nContext *context, uint8 key) {
    UINT scanCode = MapVirtualKey(key, MAPVK_VK_TO_VSC);
    WCHAR buff;

    switch (key) {
    case VK_F1:
        return K_F1;
    case VK_F2:
        return K_F2;
    case VK_F3:
        return K_F3;
    case VK_F4:
        return K_F4;
    case VK_F5:
        return K_F5;
    case VK_F6:
        return K_F6;
    case VK_F7:
        return K_F7;
    case VK_F8:
        return K_F8;
    case VK_F9:
        return K_F9;
    case VK_F10:
        return K_F10;
    case VK_F11:
        return K_F11;
    case VK_F12:
        return K_F12;
    case VK_ESCAPE:
        return K_ESCAPE;
    case VK_TAB:
        return K_TAB;
    case VK_CAPITAL:
        return K_CAPSLOCK;
    case VK_LSHIFT:
        return K_LSHIFT;
    case VK_RSHIFT:
        return K_RSHIFT;
    case VK_LCONTROL:
        return K_LCONTROL;
    case VK_RCONTROL:
        return K_RCONTROL;
    case VK_LMENU:
        return K_LALT;
    case VK_RMENU:
        return K_RALT;
    case VK_SPACE:
        return K_SPACEBAR;
    case VK_BACK:
        return K_BACKSPACE;
    case VK_RETURN:
        return K_RETURN;
    case VK_UP:
        return K_UP;
    case VK_LEFT:
        return K_LEFT;
    case VK_DOWN:
        return K_DOWN;
    case VK_RIGHT:
        return K_RIGHT;
    }

    if (ToUnicode(key, scanCode, context->nInputKeyboardState, &buff, 1, 0)) {
        switch (buff) {
        case '0':
            return K_0;
        case '1':
            return K_1;
        case '2':
            return K_2;
        case '3':
            return K_3;
        case '4':
            return K_4;
        case '5':
            return K_5;
        case '6':
            return K_6;
        case '7':
            return K_7;
        case '8':
            return K_8;
        case '9':
            return K_9;
        case 'a':
            return K_A;
        case 'b':
            return K_B;
        case 'C':
        case 'c':
            return K_C;
        case 'd':
            return K_D;
        case 'e':
            return K_E;
        case 'f':
            return K_F;
        case 'g':
            return K_G;
        case 'h':
            return K_H;
        case 'i':
            return K_I;
        case 'j':
            return K_J;
        case 'k':
            return K_K;
        case 'l':
            return K_L;
        case 'm':
            return K_M;
        case 'n':
            return K_N;
        case 'o':
            return K_O;
        case 'p':
            return K_P;
        case 'q':
            return K_Q;
        case 'r':
            return K_R;
        case 's':
            return K_S;
        case 't':
            return K_T;
        case 'u':
            return K_U;
        case 'v':
            return K_V;
        case 'w':
            return K_W;
        case 'x':
            return K_X;
        case 'y':
            return K_Y;
        case 'z':
            return K_Z;
        }
    }

    return K_UNKNOWN;
}

#endif // NOXIASYSINPUT_H
