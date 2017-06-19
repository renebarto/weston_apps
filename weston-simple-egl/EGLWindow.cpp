#include "EGLWindow.h"
#include "shared/platform.h"
#include "shared/helpers.h"

#include <cassert>
#include <iostream>

using namespace std;
using namespace Wayland;

EGLWindow::EGLWindow()
    : _display()
    , _context()
    , _config()
    , _surface()
    , _swapBuffersWithDamageExtension()
    , _swapBuffersWithDamage()
    , _window()
    , _width()
    , _height()
{
}

EGLWindow::~EGLWindow()
{
    eglTerminate(_display);
    eglReleaseThread();
}

bool EGLWindow::Initialize(EGLDisplay display,
                           const EGLint * configAttributes,
                           const EGLint * contextAttributes,
                           int bufferSize)
{
    _display = display;
    assert(_display);

    EGLint major, minor;
    EGLBoolean ret = eglInitialize(_display, &major, &minor);
    assert(ret == EGL_TRUE);
    ret = eglBindAPI(EGL_OPENGL_ES_API);
    assert(ret == EGL_TRUE);

    EGLint count;
    if (!eglGetConfigs(_display, nullptr, 0, &count) || count < 1)
        assert(0);

    EGLConfig * configs = new EGLConfig[count];
    assert(configs);

    EGLint n;
    ret = eglChooseConfig(_display, configAttributes,
                          configs, count, &n);
    assert(ret && n >= 1);

    for (EGLint  i = 0; i < n; i++)
    {
        EGLint size;
        eglGetConfigAttrib(_display, configs[i], EGL_BUFFER_SIZE, &size);
        if (bufferSize == size)
        {
            _config = configs[i];
            break;
        }
    }
    delete [] configs;

    if (_config == nullptr)
    {
        cerr << "Did not find config with buffer size " << bufferSize << endl;
        return false;
    }

    _context = eglCreateContext(_display, _config, EGL_NO_CONTEXT, contextAttributes);
    assert(_context);
    return true;
}

bool EGLWindow::DetermineSwapBuffersExtension()
{
    static const struct
    {
        const char * extension, * entryPoint;
    } swapDamageExtToEntryPoint[] =
    {
        {
            .extension = "EGL_EXT_swap_buffers_with_damage",
            .entryPoint = "eglSwapBuffersWithDamageEXT",
        },
        {
            .extension = "EGL_KHR_swap_buffers_with_damage",
            .entryPoint = "eglSwapBuffersWithDamageKHR",
        },
    };

    _swapBuffersWithDamage = NULL;
    const char * extensions = eglQueryString(_display, EGL_EXTENSIONS);
    EGLint i;
    if ((extensions != nullptr) &&
        weston_check_egl_extension(extensions, "EGL_EXT_buffer_age"))
    {
        for (i = 0; i < static_cast<EGLint>(ARRAY_LENGTH(swapDamageExtToEntryPoint)); i++)
        {
            if (weston_check_egl_extension(extensions,
                                           swapDamageExtToEntryPoint[i].extension))
            {
                /* The EXTPROC is identical to the KHR one */
                _swapBuffersWithDamage =
                    reinterpret_cast<PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC>(
                        eglGetProcAddress(swapDamageExtToEntryPoint[i].entryPoint));
                break;
            }
        }
    }

    if (_swapBuffersWithDamage)
    {
        _swapBuffersWithDamageExtension = swapDamageExtToEntryPoint[i].extension;
        return true;
    }
    return false;
}

bool EGLWindow::Create(wl_surface * surface, int width, int height)
{
    _window = wl_egl_window_create(surface, width, height);
    _width = width;
    _height = height;
    return _window != nullptr;
}

void EGLWindow::DestroyWindow()
{
    if (_window)
        wl_egl_window_destroy(_window);
    _window = nullptr;
}

void EGLWindow::Resize(int width, int height)
{
    wl_egl_window_resize(_window,
                         width, height, 0, 0);
    _width = width;
    _height = height;
}

EGLSurface EGLWindow::CreateSurface()
{
    _surface = weston_platform_create_egl_surface(_display, _config, _window, nullptr);
    EGLint ret = eglMakeCurrent(_display, _surface, _surface, _context);
    assert(ret == EGL_TRUE);
}

void EGLWindow::DestroySurface()
{
    if (_surface)
    {
        /* Required, otherwise segfault in egl_dri2.c: dri2_make_current()
         * on eglReleaseThread(). */
        eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        weston_platform_destroy_egl_surface(_display, _surface);
    }
    _surface = nullptr;
}

void EGLWindow::SetSwapInterval(EGLint interval)
{
    eglSwapInterval(_display, interval);
}

void EGLWindow::SwapBuffers()
{
    EGLint bufferAge = 0;

    if (_swapBuffersWithDamage)
    {
        eglQuerySurface(_display, _surface, EGL_BUFFER_AGE_EXT, &bufferAge);
    }
    if (_swapBuffersWithDamage && (bufferAge > 0))
    {
        EGLint rect[4];
        rect[0] = _width / 4 - 1;
        rect[1] = _height / 4 - 1;
        rect[2] = _width / 2 + 2;
        rect[3] = _height / 2 + 2;
        _swapBuffersWithDamage(_display, _surface, rect, 1);
    }
    else
    {
        eglSwapBuffers(_display, _surface);
    }
}