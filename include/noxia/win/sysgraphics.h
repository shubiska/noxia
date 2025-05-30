#ifndef NOXIASYSGRAPHICS_H
#define NOXIASYSGRAPHICS_H

#include "sysdef.h"
#include "sysdisplay.h"
#include <gl/GL.h>
#include <wingdi.h>

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALEXTPROC)(int32 interval);
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = null;
typedef HGLRC(APIENTRY *PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC DeviceContext, HGLRC _, const int32 *attributes);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = null;

void nGraphicsCreate(nContext *context);
void nGraphicsRenderBegin(nContext *context);
void nGraphicsRenderEnd(nContext *context);
void nGraphicsSetVsync(nContext *context, bool vsync);
void nGraphicsLoadGl();

void nGraphicsCreate(nContext *context) {
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    SetPixelFormat(context->nWindowDeviceContext, ChoosePixelFormat(context->nWindowDeviceContext, &pfd), &pfd);

    HGLRC tempContext = wglCreateContext(context->nWindowDeviceContext);
    wglMakeCurrent(context->nWindowDeviceContext, tempContext);

    nGraphicsLoadGl();

    int32 attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0};
    HGLRC graphicsContext = wglCreateContextAttribsARB(context->nWindowDeviceContext, 0, attributes);

    wglMakeCurrent(context->nWindowDeviceContext, graphicsContext);
    wglDeleteContext(tempContext);
    glViewport(0, 0, nDisplayGetWidth() / 2, nDisplayGetHeight() / 2);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    wglSwapIntervalEXT(0);
}

void nGraphicsRenderBegin(nContext *context) {
    glClear(GL_COLOR_BUFFER_BIT);
}

void nGraphicsRenderEnd(nContext *context) {
    SwapBuffers(context->nWindowDeviceContext);
}

void nGraphicsSetVsync(nContext *context, bool vsync) {
    wglSwapIntervalEXT(vsync);
}

void nGraphicsLoadGl() {
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
}

#endif // NOXIASYSGRAPHICS_H
