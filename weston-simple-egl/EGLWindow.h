#pragma once

#include <string>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "Geometry.h"

struct wl_surface;
struct wl_egl_window;

namespace Wayland
{

class Surface;

class EGLWindow
{
public:
    EGLWindow();
    ~EGLWindow();

    bool Initialize(EGLDisplay display,
                    const EGLint * configAttributes,
                    const EGLint * contextAttributes,
                    int bufferSize);
    const char * GetSwapBuffersWithDamageExtension() { return _swapBuffersWithDamageExtension.c_str(); }
    bool DetermineSwapBuffersExtension();
    bool Create(Surface * surface, const Geometry & size);
    void DestroyWindow();
    void Resize(const Geometry & size);
    EGLSurface CreateSurface();
    void DestroySurface();
    void SetSwapInterval(EGLint interval);
    void SwapBuffers();

private:
    EGLDisplay _display;
    EGLContext _context;
    EGLConfig _config;
    EGLSurface _surface;
    std::string _swapBuffersWithDamageExtension;
    PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC _swapBuffersWithDamage;
    wl_egl_window * _window;
    Geometry _size;
};

}
