#include "EGLWindow.h"
#include "shared/platform.h"
#include "shared/helpers.h"

#include <cassert>
#include <iostream>
#include "Surface.h"

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
    , _size()
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
    cout << "Creating EGL window" << endl;
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

    cout << "Selected configuration" << endl;
    EGLint value;
    eglGetConfigAttrib(_display, _config, EGL_RED_SIZE, &value);
    cout << "  RED_SIZE             : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_GREEN_SIZE, &value);
    cout << "  GREEN_SIZE           : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_BLUE_SIZE, &value);
    cout << "  BLUE_SIZE            : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_ALPHA_SIZE, &value);
    cout << "  ALPHA_SIZE           : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_DEPTH_SIZE, &value);
    cout << "  DEPTH_SIZE           : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_LUMINANCE_SIZE, &value);
    cout << "  LUMINANCE_SIZE       : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_STENCIL_SIZE, &value);
    cout << "  STENCIL_SIZE         : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_ALPHA_MASK_SIZE, &value);
    cout << "  ALPHA_MASK_SIZE      : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_BUFFER_SIZE, &value);
    cout << "  BUFFER_SIZE          : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_TRANSPARENT_RED_VALUE, &value);
    cout << "  TRANSP_RED_VALUE     : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_TRANSPARENT_GREEN_VALUE, &value);
    cout << "  TRANSP_GREEN_VALUE   : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_TRANSPARENT_BLUE_VALUE, &value);
    cout << "  TRANSP_BLUE_VALUE    : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_BIND_TO_TEXTURE_RGB, &value);
    cout << "  BIND_TO_TEXTURE_RGB  : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_BIND_TO_TEXTURE_RGBA, &value);
    cout << "  BIND_TO_TEXTURE_RGBA : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_SAMPLES, &value);
    cout << "  SAMPLES              : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_SAMPLE_BUFFERS, &value);
    cout << "  SAMPLE_BUFFERS       : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_MIN_SWAP_INTERVAL, &value);
    cout << "  MIN_SWAP_INTERVAL    : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_MAX_SWAP_INTERVAL, &value);
    cout << "  MAX_SWAP_INTERVAL    : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_MAX_PBUFFER_WIDTH, &value);
    cout << "  MAX_PBUFFER_WIDTH    : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_MAX_PBUFFER_HEIGHT, &value);
    cout << "  MAX_PBUFFER_HEIGHT   : " << value << endl;
    eglGetConfigAttrib(_display, _config, EGL_MAX_PBUFFER_PIXELS, &value);
    cout << "  MAX_PBUFFER_PIXELS   : " << value << endl;

    _context = eglCreateContext(_display, _config, EGL_NO_CONTEXT, contextAttributes);
    assert(_context);
    return true;
}

bool EGLWindow::DetermineSwapBuffersExtension()
{
    cout << "Determining SwapBuffers extension" << endl;
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

    _swapBuffersWithDamage = nullptr;
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

bool EGLWindow::Create(Surface * surface, const Geometry & size)
{
    cout << "Creating EGL window (" << size.width << "x" << size.height << ")" << endl;
    _window = wl_egl_window_create(surface->Get(), size.width, size.height);
    _size = size;
    return _window != nullptr;
}

void EGLWindow::DestroyWindow()
{
    cout << "Destroying EGL window" << endl;
    if (_window)
        wl_egl_window_destroy(_window);
    _window = nullptr;
}

void EGLWindow::Resize(const Geometry & size)
{
    cout << "Resize EGL window (" << size.width << "x" << size.height << ")" << endl;
    wl_egl_window_resize(_window, size.width, size.height, 0, 0);
    _size = size;
}

EGLSurface EGLWindow::CreateSurface()
{
    cout << "Creating EGL surface" << endl;
    _surface = weston_platform_create_egl_surface(_display, _config, _window, nullptr);
    EGLint ret = eglMakeCurrent(_display, _surface, _surface, _context);
    assert(ret == EGL_TRUE);
}

void EGLWindow::DestroySurface()
{
    cout << "Destroying EGL surface" << endl;
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
        rect[0] = _size.width / 4 - 1;
        rect[1] = _size.height / 4 - 1;
        rect[2] = _size.width / 2 + 2;
        rect[3] = _size.height / 2 + 2;
        _swapBuffersWithDamage(_display, _surface, rect, 1);
    }
    else
    {
        eglSwapBuffers(_display, _surface);
    }
}