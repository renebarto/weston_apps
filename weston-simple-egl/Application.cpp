#include "Application.h"

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <iostream>
#include <linux/input.h>
#include "Compositor.h"
#include "Display.h"
#include "Keyboard.h"
#include "Pointer.h"
#include "Region.h"
#include "Registry.h"
#include "Seat.h"
#include "Shm.h"
#include "Surface.h"
#include "Touch.h"
#include "ZXDGShellV6.h"
#include "ZXDGSurfaceV6.h"
#include "ZXDGTopLevelV6.h"
#include "IVISurface.h"
#include "EGLWindow.h"
#include "shared/helpers.h"
#include "shared/platform.h"
#include "shared/weston-egl-ext.h"

using namespace std;
using namespace Wayland;

#define IVI_SURFACE_ID 9000

static bool g_isRunning = false;

static const char *vert_shader_text =
    "uniform mat4 rotation;\n"
        "attribute vec4 pos;\n"
        "attribute vec4 color;\n"
        "varying vec4 v_color;\n"
        "void main() {\n"
        "  gl_Position = rotation * pos;\n"
        "  v_color = color;\n"
        "}\n";

static const char *frag_shader_text =
    "precision mediump float;\n"
        "varying vec4 v_color;\n"
        "void main() {\n"
        "  gl_FragColor = v_color;\n"
        "}\n";

Application::Application()
    : _display()
    , _compositor()
    , _shm()
    , _shell()
    , _seat()
    , _pointer()
    , _keyboard()
    , _touch()
    , _cursorTheme()
    , _defaultCursor()
    , _cursorSurface()
    , _iviApplication()
    , _eglWindow()
    , _isRunning()
    , _geometry()
    , _windowSize()
    , _gl()
    , _benchmarkTime()
    , _numFrames()
    , _surface()
    , _xdgSurface()
    , _xdgTopLevel()
    , _iviSurface()
    , _fullScreen()
    , _opaque()
    , _bufferSize()
    , _frameSync()
    , _waitForConfigure()
{
}

Application::~Application()
{
    Cleanup();
}

bool Application::Setup(const Settings & settings)
{
    _geometry.width  = 250;
    _geometry.height = 250;
    _windowSize = _geometry;
    _fullScreen = settings.fullScreen;
    _opaque = settings.opaque;
    _bufferSize = settings.bufferSize;
    _frameSync = settings.frameSync;

    _display = new Display;
    if (!_display->Setup(nullptr))
    {
        std::cerr << "Error opening display" << std::endl;
        return false;
    }
    Registry registry(_display);
    registry.AddListener(this);
    _display->Roundtrip();

    InitEGL();
    CreateSurface();
    InitGL();

    _cursorSurface = _compositor->CreateSurface();

    g_isRunning = true;
    return true;
}

void Application::Cleanup()
{
    DestroySurface();
    FiniEGL();

    delete _cursorSurface;
    _cursorSurface = nullptr;
    if (_cursorTheme)
        wl_cursor_theme_destroy(_cursorTheme);
    _cursorTheme = nullptr;
    delete _shell;
    _shell = nullptr;

    if (_iviApplication)
        ivi_application_destroy(_iviApplication);
    _iviApplication = nullptr;

    delete _compositor;
    _compositor = nullptr;

    delete _keyboard;
    _keyboard = nullptr;
    delete _pointer;
    _pointer = nullptr;
    delete _touch;
    _touch = nullptr;
    delete _seat;
    _seat = nullptr;
    delete _shm;
    _shm = nullptr;
    delete _display;
    _display = nullptr;
}

bool Application::Dispatch()
{
    /* The mainloop here is a little subtle.  Redrawing will cause
     * EGL to read events so we can just call
     * wl_display_dispatch_pending() to handle any events that got
     * queued up as a side effect. */
    if (!g_isRunning)
        _isRunning = false;
    if (_waitForConfigure)
    {
        if (!_display->Dispatch())
            return false;
    } else
    {
        if (!_display->DispatchPending())
            return false;
        Redraw(0);
    }
    return true;
}

void Application::OnRegistryAdd(wl_registry *registry, uint32_t name,
                                const char *interface, uint32_t version)
{
    if (strcmp(interface, wl_compositor_interface.name) == 0)
        _compositor = new Compositor(reinterpret_cast<wl_compositor *>(wl_registry_bind(registry, name, &wl_compositor_interface, 1)));
    else if (strcmp(interface, zxdg_shell_v6_interface.name) == 0)
    {
        _shell = new ZXDGShellV6(reinterpret_cast<struct zxdg_shell_v6 *>(wl_registry_bind(registry, name, &zxdg_shell_v6_interface, 1)));
        _shell->AddListener(this);
    } else if (strcmp(interface, wl_seat_interface.name) == 0)
    {
        _seat = new Seat(reinterpret_cast<struct wl_seat *>(wl_registry_bind(registry, name, &wl_seat_interface, 1)));
        _seat->AddListener(this);
    } else if (strcmp(interface, wl_shm_interface.name) == 0)
    {
        _shm = new Shm(reinterpret_cast<struct wl_shm *>(wl_registry_bind(registry, name, &wl_shm_interface, 1)));
        _cursorTheme = wl_cursor_theme_load(nullptr, 32, _shm->Get());
        if (!_cursorTheme)
        {
            cerr << "unable to load default theme" << endl;
            return;
        }
        _defaultCursor = wl_cursor_theme_get_cursor(_cursorTheme, "left_ptr");
        if (!_defaultCursor)
        {
            cerr << "unable to load default left pointer" << endl;
            // TODO: abort ?
        }
    } else if (strcmp(interface, ivi_application_interface.name) == 0)
    {
        _iviApplication = reinterpret_cast<struct ivi_application *>(wl_registry_bind(registry, name, &ivi_application_interface, 1));
    }
}

// Is this ever called?
void Application::OnRegistryRemove(wl_registry *registry, uint32_t name)
{
}

void Application::OnPointerEnter(wl_pointer *pointer,
                                 uint32_t serial, wl_surface *surface,
                                 wl_fixed_t surfaceX, wl_fixed_t surfaceY)
{
    assert(pointer == _pointer->Get());

    if (_fullScreen)
    {
        // Hide cursor
        wl_pointer_set_cursor(pointer, serial, nullptr, 0, 0);
    }
    else if (_defaultCursor)
    {
        wl_cursor_image * image = _defaultCursor->images[0];
        wl_buffer * buffer = wl_cursor_image_get_buffer(image);
        if (!buffer)
            return;
        wl_pointer_set_cursor(pointer, serial,
                              _cursorSurface->Get(),
                              image->hotspot_x,
                              image->hotspot_y);
        _cursorSurface->Attach(buffer);
        wl_surface_damage(_cursorSurface->Get(), 0, 0, image->width, image->height);
        _cursorSurface->Commit();
    }
}

void Application::OnPointerLeave(wl_pointer *pointer, uint32_t serial,
                                 wl_surface *surface)
{
    assert(pointer == _pointer->Get());
}

void Application::OnPointerMotion(wl_pointer *pointer, uint32_t time,
                                  wl_fixed_t surfaceX, wl_fixed_t surfaceY)
{
    assert(pointer == _pointer->Get());
}

void Application::OnPointerButton(wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state)
{
    assert(pointer == _pointer->Get());

    if (!_xdgTopLevel)
        return;

    if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED)
        zxdg_toplevel_v6_move(_xdgTopLevel->Get(),
                              _seat->Get(), serial);
}

void Application::OnPointerAxis(wl_pointer *pointer, uint32_t time,
                                uint32_t axis, wl_fixed_t value)
{
    assert(pointer == _pointer->Get());
}

void Application::OnKeyboardKeymap(wl_keyboard *keyboard,
                                   uint32_t format,
                                   int32_t fd,
                                   uint32_t size)
{
    assert(keyboard == _keyboard->Get());
}

void Application::OnKeyboardEnter(wl_keyboard *keyboard,
                                  uint32_t serial,
                                  wl_surface *surface,
                                  wl_array *keys)
{
    assert(keyboard == _keyboard->Get());
}

void Application::OnKeyboardLeave(wl_keyboard *keyboard,
                                  uint32_t serial,
                                  wl_surface *surface)
{
    assert(keyboard == _keyboard->Get());
}

void Application::OnKeyboardKey(wl_keyboard *keyboard,
                                uint32_t serial,
                                uint32_t time,
                                uint32_t key,
                                uint32_t state)
{
    assert(keyboard == _keyboard->Get());

    if (!_shell)
        return;

    if (key == KEY_F11 && state)
    {
        if (_fullScreen)
            _xdgTopLevel->UnsetFullScreen();
        else
            _xdgTopLevel->SetFullScreen();
    } else if (key == KEY_ESC && state)
        Stop();
}

void Application::OnKeyboardModifiers(wl_keyboard *keyboard,
                                      uint32_t serial,
                                      uint32_t mods_depressed,
                                      uint32_t mods_latched,
                                      uint32_t mods_locked,
                                      uint32_t group)
{
    assert(keyboard == _keyboard->Get());
}

void Application::OnKeyboardRepeatInfo(wl_keyboard *keyboard,
                                       int32_t rate,
                                       int32_t delay)
{
    assert(keyboard == _keyboard->Get());
}

void Application::OnTouchDown(wl_touch * touch,
                              uint32_t serial,
                              uint32_t time,
                              wl_surface * surface,
                              int32_t id,
                              wl_fixed_t x,
                              wl_fixed_t y)
{
    assert(touch == _touch->Get());

    if (!_shell)
        return;

    _xdgTopLevel->Move(_seat, serial);
}

void Application::OnTouchUp(wl_touch * touch,
                            uint32_t serial,
                            uint32_t time,
                            int32_t id)
{
    assert(touch == _touch->Get());
}

void Application::OnTouchMotion(wl_touch * touch,
                                uint32_t time,
                                int32_t id,
                                wl_fixed_t x,
                                wl_fixed_t y)
{
    assert(touch == _touch->Get());
}

void Application::OnTouchFrame(wl_touch * touch)
{
    assert(touch == _touch->Get());
}

void Application::OnTouchCancel(wl_touch * touch)
{
    assert(touch == _touch->Get());
}

void Application::OnSeatHandleCapabilities(wl_seat * seat,
                                           uint32_t caps)
{
    if ((caps & WL_SEAT_CAPABILITY_POINTER) && !_pointer)
    {
        cerr << "Got pointer" << endl;
        _pointer = new Pointer(wl_seat_get_pointer(seat));
        _pointer->AddListener(this);
    } else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && _pointer)
    {
        delete _pointer;
        _pointer = nullptr;
    }

    if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && !_keyboard)
    {
        cerr << "Got keyboard" << endl;
        _keyboard = new Keyboard(wl_seat_get_keyboard(seat));
        _keyboard->AddListener(this);
    } else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && _keyboard)
    {
        delete _keyboard;
        _keyboard = nullptr;
    }

    if ((caps & WL_SEAT_CAPABILITY_TOUCH) && !_touch)
    {
        cerr << "Got touch device" << endl;
        _touch = new Touch(wl_seat_get_touch(seat));
        _touch->AddListener(this);
    } else if (!(caps & WL_SEAT_CAPABILITY_TOUCH) && _touch)
    {
        delete _touch;
        _touch = nullptr;
    }
}

void Application::OnSeatName(wl_seat * seat, const char * name)
{    
}

void Application::OnXDGShellPing(zxdg_shell_v6 *shell,
                                 uint32_t serial)
{
    zxdg_shell_v6_pong(shell, serial);
}

void Application::OnXDGSurfaceConfigure(zxdg_surface_v6 * surface, uint32_t serial)
{
    zxdg_surface_v6_ack_configure(surface, serial);

    _waitForConfigure = false;
}

void Application::OnXDGTopLevelConfigure(zxdg_toplevel_v6 * toplevel,
                                         int32_t width,
                                         int32_t height,
                                         wl_array * states)
{
    uint32_t *p;

    _fullScreen = false;
    for (p = reinterpret_cast<uint32_t *>(states->data);
         (const char *) p < (reinterpret_cast<const char *>(states->data) + states->size);
         p++)
    {
        uint32_t state = *p;
        switch (state)
        {
            case ZXDG_TOPLEVEL_V6_STATE_FULLSCREEN:
                _fullScreen = true;
                break;
        }
    }

    if ((width > 0) && (height > 0))
    {
        if (!_fullScreen)
        {
            _windowSize.width = width;
            _windowSize.height = height;
        }
        _geometry.width = width;
        _geometry.height = height;
    } else if (!_fullScreen)
    {
        _geometry = _windowSize;
    }

    if (_eglWindow)
        _eglWindow->Resize(_geometry.width, _geometry.height);
}

void Application::OnXDGTopLevelClose(zxdg_toplevel_v6 * toplevel)
{
    Stop();
}

void Application::OnIVISurfaceConfigure(ivi_surface * surface, int32_t width, int32_t height)
{
    if (_eglWindow)
        _eglWindow->Resize(width, height);

    _geometry.width = width;
    _geometry.height = height;

    if (!_fullScreen)
        _windowSize = _geometry;
}

void Application::InitEGL()
{
    _eglWindow = new EGLWindow;

    static const EGLint contextAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLint configAttribs[] =
    {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_ALPHA_SIZE, 1,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    if (_opaque || _bufferSize == 16)
        // Aaarrgh, this means set ALPHA_SIZE to 0
        configAttribs[9] = 0;

    if (!_eglWindow->Initialize(weston_platform_get_egl_display(EGL_PLATFORM_WAYLAND_KHR, _display->Get(), nullptr),
                                configAttribs, contextAttribs, _bufferSize))
        exit(EXIT_FAILURE);

    if (_eglWindow->DetermineSwapBuffersExtension())
        cout << "has EGL_EXT_buffer_age and " << _eglWindow->GetSwapBuffersWithDamageExtension() << endl;
}

void Application::FiniEGL()
{
    delete _eglWindow;
    _eglWindow = nullptr;
}

GLuint Application::CreateShader(const char * source, GLenum shader_type)
{
    GLuint shader;
    GLint status;

    shader = glCreateShader(shader_type);
    assert(shader != 0);

    glShaderSource(shader, 1, (const char **) &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char log[1000];
        GLsizei len;
        glGetShaderInfoLog(shader, 1000, &len, log);
        fprintf(stderr, "Error: compiling %s: %*s\n",
                shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment",
                len, log);
        exit(1);
    }

    return shader;
}

void Application::InitGL()
{
    GLuint frag, vert;
    GLuint program;
    GLint status;

    frag = CreateShader(frag_shader_text, GL_FRAGMENT_SHADER);
    vert = CreateShader(vert_shader_text, GL_VERTEX_SHADER);

    program = glCreateProgram();
    glAttachShader(program, frag);
    glAttachShader(program, vert);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        char log[1000];
        GLsizei len;
        glGetProgramInfoLog(program, 1000, &len, log);
        fprintf(stderr, "Error: linking:\n%*s\n", len, log);
        exit(1);
    }

    glUseProgram(program);

    _gl.pos = 0;
    _gl.col = 1;

    glBindAttribLocation(program, _gl.pos, "pos");
    glBindAttribLocation(program, _gl.col, "color");
    glLinkProgram(program);

    _gl.rotationUniform =
        glGetUniformLocation(program, "rotation");
}

void Application::CreateXDGSurface()
{
    _xdgSurface = new ZXDGSurfaceV6(zxdg_shell_v6_get_xdg_surface(_shell->Get(), _surface->Get()));
    _xdgSurface->AddListener(this);

    _xdgTopLevel = new ZXDGTopLevelV6(zxdg_surface_v6_get_toplevel(_xdgSurface->Get()));
    _xdgTopLevel->AddListener(this);
    _xdgTopLevel->SetTitle("simple-egl");

    _waitForConfigure = true;
    _surface->Commit();
}

void Application::CreateIVISurface()
{
    uint32_t id_ivisurf = IVI_SURFACE_ID + (uint32_t)getpid();
    _iviSurface = new IVISurface(ivi_application_surface_create(_iviApplication,
                                                                        id_ivisurf, _surface->Get()));

    if (_iviSurface == nullptr)
    {
        fprintf(stderr, "Failed to create ivi_client_surface\n");
        abort();
    }

    _iviSurface->AddListener(this);
}

void Application::CreateSurface()
{
    EGLBoolean ret;

    _surface = _compositor->CreateSurface();

    _eglWindow->Create(_surface->Get(),
                       _geometry.width,
                       _geometry.height);

    if (_shell)
    {
        CreateXDGSurface();
    } else if (_iviApplication)
    {
        CreateIVISurface();
    } else {
        assert(0);
    }

    _eglWindow->CreateSurface();
    if (!_frameSync)
        _eglWindow->SetSwapInterval(0);

    if (!_shell)
        return;

    if (_fullScreen)
        _xdgTopLevel->SetFullScreen();
}

void Application::DestroySurface()
{
    if (_eglWindow)
    {
        _eglWindow->DestroySurface();
        _eglWindow->DestroyWindow();
    }
    delete _xdgTopLevel;
    _xdgTopLevel = nullptr;
    delete _xdgSurface;
    _xdgSurface = nullptr;
    delete _iviSurface;
    _iviSurface = nullptr;
    delete _surface;
    _surface = nullptr;
}

void Application::Redraw(uint32_t time)
{
    static const GLfloat verts[3][2] = {
        { -0.5, -0.5 },
        {  0.5, -0.5 },
        {  0,    0.5 }
    };
    static const GLfloat colors[3][3] = {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    };
    GLfloat angle;
    GLfloat rotation[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };
    static const uint32_t speed_div = 5, benchmark_interval = 5;
    struct wl_region *region;
    struct timeval tv;

    gettimeofday(&tv, nullptr);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    if (_numFrames == 0)
        _benchmarkTime = time;
    if (time - _benchmarkTime > (benchmark_interval * 1000)) {
        printf("%d frames in %d seconds: %f fps\n",
               _numFrames,
               benchmark_interval,
               (float) _numFrames / benchmark_interval);
        _benchmarkTime = time;
        _numFrames = 0;
    }

    angle = (time / speed_div) % 360 * M_PI / 180.0;
    rotation[0][0] =  cos(angle);
    rotation[0][2] =  sin(angle);
    rotation[2][0] = -sin(angle);
    rotation[2][2] =  cos(angle);

    glViewport(0, 0, _geometry.width, _geometry.height);

    glUniformMatrix4fv(_gl.rotationUniform, 1, GL_FALSE,
                       (GLfloat *) rotation);

    glClearColor(0.0, 0.0, 0.0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    glVertexAttribPointer(_gl.pos, 2, GL_FLOAT, GL_FALSE, 0, verts);
    glVertexAttribPointer(_gl.col, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(_gl.pos);
    glEnableVertexAttribArray(_gl.col);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(_gl.pos);
    glDisableVertexAttribArray(_gl.col);

    if (_opaque || _fullScreen)
    {
        Region * region = _compositor->CreateRegion();
        region->Add(_geometry.width, _geometry.height);
        _surface->SetOpaqueRegion(region);
        delete region;
    } else
    {
        _surface->SetTransparent();
    }

    _eglWindow->SwapBuffers();

    _numFrames++;
}

