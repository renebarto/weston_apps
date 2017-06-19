#pragma once

#include <string>
#include <EGL/egl.h>
#include <EGL/eglext.h>

struct wl_surface;
struct wl_egl_window;

namespace Wayland
{

class EGLWindow
{
public:
    EGLWindow();
    ~EGLWindow();

    bool Initialize(EGLDisplay display,
                    const EGLint * configAttributes,
                    const EGLint * contextAttributes,
                    int bufferSize);
    EGLDisplay GetDisplay() { return _display; }
    const char * GetSwapBuffersWithDamageExtension() { return _swapBuffersWithDamageExtension.c_str(); }
    bool DetermineSwapBuffersExtension();
    bool Create(wl_surface * surface, int width, int height);
    void DestroyWindow();
    void Resize(int width, int height);
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
    int _width;
    int _height;
};

}
