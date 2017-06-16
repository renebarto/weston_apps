#include "Application.h"

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <iostream>
#include <linux/input.h>
#include "Display.h"
#include "Keyboard.h"
#include "Pointer.h"
#include "Registry.h"
#include "Seat.h"
#include "Surface.h"
#include "Touch.h"
#include "ZXDGShellV6.h"
#include "ZXDGSurfaceV6.h"
#include "ZXDGTopLevelV6.h"
#include "IVISurface.h"
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
    : _window()
    , _display()
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
    , _egl()
    , _swapBuffersWithDamage()
    , _isRunning()
{
}

Application::~Application()
{
    Cleanup();
}

bool Application::Setup(const Settings & settings)
{
    _window.display = _display;
    _window.geometry.width  = 250;
    _window.geometry.height = 250;
    _window.window_size = _window.geometry;
    _window.fullscreen = settings.fullScreen;
    _window.opaque = settings.opaque;
    _window.buffer_size = settings.bufferSize;
    _window.frame_sync = settings.frameSync;

    _display = new Display;
    if (!_display->Setup(nullptr))
    {
        std::cerr << "Error opening display" << std::endl;
        return false;
    }
    Registry registry(_display);
    registry.AddListener(this);
    _display->Roundtrip();

    InitEGL(&_window);
    CreateSurface(&_window);
    InitGL(&_window);

    _cursorSurface = wl_compositor_create_surface(_compositor->Get());

    g_isRunning = true;
    return true;
}

void Application::Cleanup()
{
    DestroySurface(&_window);
    FiniEGL();

    if (_cursorSurface)
        wl_surface_destroy(_cursorSurface);
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
    if (_shm)
        wl_shm_destroy(_shm);
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
    if (_window.wait_for_configure)
    {
        if (wl_display_dispatch(_display->Get()) < 0)
            return false;
    } else
    {
        if (wl_display_dispatch_pending(_display->Get()) < 0)
            return false;
        Redraw(&_window, NULL, 0);
    }
    return true;
//    return _display ? _display->Dispatch() : false;
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
        _shm = reinterpret_cast<struct wl_shm *>(wl_registry_bind(registry, name, &wl_shm_interface, 1));
        _cursorTheme = wl_cursor_theme_load(nullptr, 32, _shm);
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

    if (_window.fullscreen)
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
                              _cursorSurface,
                              image->hotspot_x,
                              image->hotspot_y);
        wl_surface_attach(_cursorSurface, buffer, 0, 0);
        wl_surface_damage(_cursorSurface, 0, 0, image->width, image->height);
        wl_surface_commit(_cursorSurface);
    }
//    _pointer->SetTargetSurface(surface);
//    _pointer->AttachBufferToSurface();
//    _pointer->SetCursor(serial);
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

    if (!_window.xdg_toplevel)
        return;

    if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED)
        zxdg_toplevel_v6_move(_window.xdg_toplevel->Get(),
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
        if (_window.fullscreen)
            _window.xdg_toplevel->UnsetFullScreen();
        else
            _window.xdg_toplevel->SetFullScreen();
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

    _window.xdg_toplevel->Move(_seat, serial);
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

    _window.wait_for_configure = false;
}

void Application::OnXDGTopLevelConfigure(zxdg_toplevel_v6 * toplevel,
                                         int32_t width,
                                         int32_t height,
                                         wl_array * states)
{
    uint32_t *p;

    _window.fullscreen = false;
    for (p = reinterpret_cast<uint32_t *>(states->data);
         (const char *) p < (reinterpret_cast<const char *>(states->data) + states->size);
         p++)
    {
        uint32_t state = *p;
        switch (state)
        {
            case ZXDG_TOPLEVEL_V6_STATE_FULLSCREEN:
                _window.fullscreen = true;
                break;
        }
    }

    if ((width > 0) && (height > 0))
    {
        if (!_window.fullscreen)
        {
            _window.window_size.width = width;
            _window.window_size.height = height;
        }
        _window.geometry.width = width;
        _window.geometry.height = height;
    } else if (!_window.fullscreen)
    {
        _window.geometry = _window.window_size;
    }

    if (_window.native)
        wl_egl_window_resize(_window.native,
                             _window.geometry.width, _window.geometry.height, 0, 0);
}

void Application::OnXDGTopLevelClose(zxdg_toplevel_v6 * toplevel)
{
    Stop();
}

void Application::OnIVISurfaceConfigure(ivi_surface * surface, int32_t width, int32_t height)
{
    wl_egl_window_resize(_window.native, width, height, 0, 0);

    _window.geometry.width = width;
    _window.geometry.height = height;

    if (!_window.fullscreen)
        _window.window_size = _window.geometry;
}

void Application::InitEGL(struct window * window)
{
    static const struct {
        const char *extension, *entrypoint;
    } swap_damage_ext_to_entrypoint[] = {
        {
            .extension = "EGL_EXT_swap_buffers_with_damage",
            .entrypoint = "eglSwapBuffersWithDamageEXT",
        },
        {
            .extension = "EGL_KHR_swap_buffers_with_damage",
            .entrypoint = "eglSwapBuffersWithDamageKHR",
        },
    };

    static const EGLint context_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    const char *extensions;

    EGLint config_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_ALPHA_SIZE, 1,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLint major, minor, n, count, i, size;
    EGLConfig *configs;
    EGLBoolean ret;

    if (window->opaque || window->buffer_size == 16)
        config_attribs[9] = 0;

    _egl.dpy =
        weston_platform_get_egl_display(EGL_PLATFORM_WAYLAND_KHR,
                                        _display->Get(), nullptr);
    assert(_egl.dpy);

    ret = eglInitialize(_egl.dpy, &major, &minor);
    assert(ret == EGL_TRUE);
    ret = eglBindAPI(EGL_OPENGL_ES_API);
    assert(ret == EGL_TRUE);

    if (!eglGetConfigs(_egl.dpy, NULL, 0, &count) || count < 1)
        assert(0);

    configs = reinterpret_cast<void **>(calloc(count, sizeof *configs));
    assert(configs);

    ret = eglChooseConfig(_egl.dpy, config_attribs,
                          configs, count, &n);
    assert(ret && n >= 1);

    for (i = 0; i < n; i++) {
        eglGetConfigAttrib(_egl.dpy,
                           configs[i], EGL_BUFFER_SIZE, &size);
        if (window->buffer_size == size) {
            _egl.conf = configs[i];
            break;
        }
    }
    free(configs);
    if (_egl.conf == NULL) {
        fprintf(stderr, "did not find config with buffer size %d\n",
                window->buffer_size);
        exit(EXIT_FAILURE);
    }

    _egl.ctx = eglCreateContext(_egl.dpy,
                                        _egl.conf,
                                        EGL_NO_CONTEXT, context_attribs);
    assert(_egl.ctx);

    _swapBuffersWithDamage = NULL;
    extensions = eglQueryString(_egl.dpy, EGL_EXTENSIONS);
    if (extensions &&
        weston_check_egl_extension(extensions, "EGL_EXT_buffer_age"))
    {
        for (i = 0; i < (int) ARRAY_LENGTH(swap_damage_ext_to_entrypoint); i++)
        {
            if (weston_check_egl_extension(extensions,
                                           swap_damage_ext_to_entrypoint[i].extension))
            {
                /* The EXTPROC is identical to the KHR one */
                _swapBuffersWithDamage =
                    (PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)
                        eglGetProcAddress(swap_damage_ext_to_entrypoint[i].entrypoint);
                break;
            }
        }
    }

    if (_swapBuffersWithDamage)
        printf("has EGL_EXT_buffer_age and %s\n", swap_damage_ext_to_entrypoint[i].extension);

}

void Application::FiniEGL()
{
    eglTerminate(_egl.dpy);
    eglReleaseThread();
}

GLuint Application::CreateShader(struct window * window, const char * source, GLenum shader_type)
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

void Application::InitGL(struct window * window)
{
    GLuint frag, vert;
    GLuint program;
    GLint status;

    frag = CreateShader(window, frag_shader_text, GL_FRAGMENT_SHADER);
    vert = CreateShader(window, vert_shader_text, GL_VERTEX_SHADER);

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

    window->gl.pos = 0;
    window->gl.col = 1;

    glBindAttribLocation(program, window->gl.pos, "pos");
    glBindAttribLocation(program, window->gl.col, "color");
    glLinkProgram(program);

    window->gl.rotation_uniform =
        glGetUniformLocation(program, "rotation");
}

void Application::CreateXDGSurface(struct window * window)
{
    window->xdg_surface = new ZXDGSurfaceV6(zxdg_shell_v6_get_xdg_surface(_shell->Get(), window->surface));
    window->xdg_surface->AddListener(this);

    window->xdg_toplevel = new ZXDGTopLevelV6(zxdg_surface_v6_get_toplevel(window->xdg_surface->Get()));
    window->xdg_toplevel->AddListener(this);
    window->xdg_toplevel->SetTitle("simple-egl");

    window->wait_for_configure = true;
    wl_surface_commit(window->surface);
}

void Application::CreateIVISurface(struct window * window)
{
    uint32_t id_ivisurf = IVI_SURFACE_ID + (uint32_t)getpid();
    window->ivi_surface = new IVISurface(ivi_application_surface_create(_iviApplication,
                                                                        id_ivisurf, window->surface));

    if (window->ivi_surface == nullptr)
    {
        fprintf(stderr, "Failed to create ivi_client_surface\n");
        abort();
    }

    window->ivi_surface->AddListener(this);
}

void Application::CreateSurface(struct window * window)
{
    EGLBoolean ret;

    window->surface = wl_compositor_create_surface(_compositor->Get());

    window->native =
        wl_egl_window_create(window->surface,
                             window->geometry.width,
                             window->geometry.height);
    window->egl_surface =
        weston_platform_create_egl_surface(_egl.dpy,
                                           _egl.conf,
                                           window->native, NULL);


    if (_shell)
    {
        CreateXDGSurface(window);
    } else if (_iviApplication)
    {
        CreateIVISurface(window);
    } else {
        assert(0);
    }

    ret = eglMakeCurrent(_egl.dpy, window->egl_surface,
                         window->egl_surface, _egl.ctx);
    assert(ret == EGL_TRUE);

    if (!window->frame_sync)
        eglSwapInterval(_egl.dpy, 0);

    if (!_shell)
        return;

    if (window->fullscreen)
        window->xdg_toplevel->SetFullScreen();
}

void Application::DestroySurface(struct window * window)
{
    if (window->egl_surface)
    {
        /* Required, otherwise segfault in egl_dri2.c: dri2_make_current()
         * on eglReleaseThread(). */
        eglMakeCurrent(_egl.dpy, EGL_NO_SURFACE, EGL_NO_SURFACE,
                       EGL_NO_CONTEXT);

        weston_platform_destroy_egl_surface(_egl.dpy,
                                            window->egl_surface);
    }
    window->egl_surface = nullptr;
    if (window->native)
        wl_egl_window_destroy(window->native);
    window->native = nullptr;

    delete window->xdg_toplevel;
    window->xdg_toplevel = nullptr;
    delete window->xdg_surface;
    window->xdg_surface = nullptr;
    delete window->ivi_surface;
    _iviApplication = nullptr;
    if (window->surface)
        wl_surface_destroy(window->surface);
    window->surface = nullptr;

    if (window->callback)
        wl_callback_destroy(window->callback);
    window->callback = nullptr;
}

void Application::Redraw(void * data, struct wl_callback * callback, uint32_t time)
{
    struct window *window = reinterpret_cast<struct window *>(data);
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
    EGLint rect[4];
    EGLint buffer_age = 0;
    struct timeval tv;

    assert(window->callback == callback);
    window->callback = NULL;

    if (callback)
        wl_callback_destroy(callback);

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    if (window->frames == 0)
        window->benchmark_time = time;
    if (time - window->benchmark_time > (benchmark_interval * 1000)) {
        printf("%d frames in %d seconds: %f fps\n",
               window->frames,
               benchmark_interval,
               (float) window->frames / benchmark_interval);
        window->benchmark_time = time;
        window->frames = 0;
    }

    angle = (time / speed_div) % 360 * M_PI / 180.0;
    rotation[0][0] =  cos(angle);
    rotation[0][2] =  sin(angle);
    rotation[2][0] = -sin(angle);
    rotation[2][2] =  cos(angle);

    if (_swapBuffersWithDamage)
        eglQuerySurface(_egl.dpy, window->egl_surface,
                        EGL_BUFFER_AGE_EXT, &buffer_age);

    glViewport(0, 0, window->geometry.width, window->geometry.height);

    glUniformMatrix4fv(window->gl.rotation_uniform, 1, GL_FALSE,
                       (GLfloat *) rotation);

    glClearColor(0.0, 0.0, 0.0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    glVertexAttribPointer(window->gl.pos, 2, GL_FLOAT, GL_FALSE, 0, verts);
    glVertexAttribPointer(window->gl.col, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(window->gl.pos);
    glEnableVertexAttribArray(window->gl.col);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(window->gl.pos);
    glDisableVertexAttribArray(window->gl.col);

    if (window->opaque || window->fullscreen) {
        region = wl_compositor_create_region(_compositor->Get());
        wl_region_add(region, 0, 0,
                      window->geometry.width,
                      window->geometry.height);
        wl_surface_set_opaque_region(window->surface, region);
        wl_region_destroy(region);
    } else {
        wl_surface_set_opaque_region(window->surface, NULL);
    }

    if (_swapBuffersWithDamage && buffer_age > 0) {
        rect[0] = window->geometry.width / 4 - 1;
        rect[1] = window->geometry.height / 4 - 1;
        rect[2] = window->geometry.width / 2 + 2;
        rect[3] = window->geometry.height / 2 + 2;
        _swapBuffersWithDamage(_egl.dpy,
                                          window->egl_surface,
                                          rect, 1);
    } else {
        eglSwapBuffers(_egl.dpy, window->egl_surface);
    }
    window->frames++;
}

