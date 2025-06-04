#ifndef NOXIASYSGRAPHICS_H
#define NOXIASYSGRAPHICS_H

#include "sysdef.h"
#include <stdio.h>
#define GL_IMPLEMENTATION
#include "extgl.h"

bool nGraphicsCreate(nContext *context);
void nGraphicsRenderBegin(nContext *context);
void nGraphicsRenderEnd(nContext *context);
void nGraphicsSetVsync(nContext *context, bool vsync);
void nGraphicsResize(nContext *context);
void nGraphicsDestroy(nContext *context);

bool nGraphicsCreate(nContext *context) {
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    SetPixelFormat(context->nWindowDeviceContext, ChoosePixelFormat(context->nWindowDeviceContext, &pfd), &pfd);

    HGLRC _graphicsContext = wglCreateContext(context->nWindowDeviceContext);
    wglMakeCurrent(context->nWindowDeviceContext, _graphicsContext);

    const char *versionStr = (const char *)glGetString(GL_VERSION);
    uint32 major = versionStr[0] - '0';
    uint32 minor = versionStr[2] - '0';
    if (!(major >= 3 && minor >= 3)) {
        return false;
    }

    nExternalGraphicsLoadGL();

    int32 attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0};
    int32 pixelAttribs[] = {WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, WGL_SUPPORT_OPENGL_ARB, GL_TRUE, WGL_DOUBLE_BUFFER_ARB, GL_TRUE, WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB, WGL_COLOR_BITS_ARB, 32, WGL_DEPTH_BITS_ARB, 24, WGL_STENCIL_BITS_ARB, 8, WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE, 0};
    HGLRC graphicsContext = wglCreateContextAttribsARB(context->nWindowDeviceContext, 0, attributes);

    wglMakeCurrent(context->nWindowDeviceContext, graphicsContext);
    wglDeleteContext(_graphicsContext);

    int32 pixelFormat;
    UINT numFormats;
    wglChoosePixelFormatARB(context->nWindowDeviceContext, pixelAttribs, NULL, 1, &pixelFormat, &numFormats);
    SetPixelFormat(context->nWindowDeviceContext, pixelFormat, &pfd);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    context->nGraphicsContext = graphicsContext;

    return true;
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

void nGraphicsResize(nContext *context) {
    glViewport(0, 0, context->nWindowWidth, context->nWindowHeight);
}

void nGraphicsDestroy(nContext *context) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(context->nGraphicsContext);
    ReleaseDC(context->nWindowHandle, context->nWindowDeviceContext);
}

#endif // NOXIASYSGRAPHICS_H
