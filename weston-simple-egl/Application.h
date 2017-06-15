#pragma once

#include <string.h>
#include <iostream>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "protocol/xdg-shell-unstable-v6-client-protocol.h"
#include "protocol/ivi-application-client-protocol.h"
#include "IRegistryListener.h"
#include "IPointerListener.h"
#include "IKeyboardListener.h"

namespace Wayland
{

class Display;
class Compositor;
class Seat;
class Pointer;
class Keyboard;
class Touch;
class Cursor;
class Registry;
class Surface;

using KeyCode = int;
using KeyboardCallbackFunction = void (*)();

struct display
{
    struct wl_display *display;
    struct wl_registry *registry;
    struct wl_compositor *compositor;
    struct zxdg_shell_v6 *shell;
    struct wl_seat *seat;
    struct wl_pointer *pointer;
    struct wl_touch *touch;
    struct wl_keyboard *keyboard;
    struct wl_shm *shm;
    struct wl_cursor_theme *cursor_theme;
    struct wl_cursor *default_cursor;
    struct wl_surface *cursor_surface;
    struct
    {
        EGLDisplay dpy;
        EGLContext ctx;
        EGLConfig conf;
    } egl;
    struct window *window;
    struct ivi_application *ivi_application;

    PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC swap_buffers_with_damage;
};

struct geometry
{
    int width, height;
};

struct window
{
    struct display *display;
    struct geometry geometry, window_size;
    struct
    {
        GLuint rotation_uniform;
        GLuint pos;
        GLuint col;
    } gl;

    uint32_t benchmark_time, frames;
    struct wl_egl_window *native;
    struct wl_surface *surface;
    struct zxdg_surface_v6 *xdg_surface;
    struct zxdg_toplevel_v6 *xdg_toplevel;
    struct ivi_surface *ivi_surface;
    EGLSurface egl_surface;
    struct wl_callback *callback;
    int fullscreen, opaque, buffer_size, frame_sync;
    bool wait_for_configure;
};

struct Settings
{
    Settings()
        : fullscreen()
        , opaque()
        , bufferSize(0)
        , frameSync(true)
    {
    }
    bool fullscreen;
    bool opaque;
    int bufferSize;
    bool frameSync;
};

class Application :
    public IRegistryListener,
    public IPointerListener,
    public IKeyboardListener
{
public:
    Application();
    ~Application();

    bool Setup(const Settings & settings);
    void Cleanup();
    void Start() { _isRunning = true; }
    void Stop() { _isRunning = false; }
    bool Dispatch();
    bool IsRunning() { return _isRunning; }

//    Compositor * GetCompositor() { return _compositor; }
//    wl_shm * GetShm() { return _shm; }
//    wl_shell * GetShell() { return _shell; }
//    const Seat * GetSeat() const { return _seat; }
//    Pointer * GetPointer() { return _pointer; }
//    const Keyboard * GetKeyboard() const { return _keyboard; }

    void SetKeyboardCallback(KeyCode key, KeyboardCallbackFunction callback);

private:
    void InitEGL(struct display * display, struct window * window);
    void FiniEGL(struct display * display);
    GLuint CreateShader(struct window * window, const char * source, GLenum shader_type);
    void InitGL(struct window * window);
    void CreateXDGSurface(struct window * window, struct display * display);
    void CreateIVISurface(struct window * window, struct display * display);
    void CreateSurface(struct window * window);
    void DestroySurface(struct window * window);
    void Redraw(void * data, struct wl_callback * callback, uint32_t time);

    virtual void RegistryCallbackAdd(wl_registry *wl_registry,
                                     uint32_t name,
                                     const char *interface,
                                     uint32_t version) override final;
    virtual void RegistryCallbackRemove(wl_registry *wl_registry,
                                        uint32_t name) override final;

    virtual void PointerEnter(wl_pointer * pointer,
                              uint32_t serial, wl_surface * surface,
                              wl_fixed_t surfaceX, wl_fixed_t surfaceY) override final;

    virtual void PointerLeave(wl_pointer * pointer, uint32_t serial,
                              wl_surface * surface) override final;

    virtual void PointerMotion(wl_pointer * pointer, uint32_t time,
                               wl_fixed_t surfaceX, wl_fixed_t surfaceY) override final;

    virtual void PointerButton(wl_pointer * pointer, uint32_t serial,
                               uint32_t time, uint32_t button, uint32_t state) override final;

    virtual void PointerAxis(wl_pointer * pointer, uint32_t time,
                             uint32_t axis, wl_fixed_t value) override final;

    virtual void KeyboardKeymap(wl_keyboard * keyboard,
                                uint32_t format,
                                int32_t fd,
                                uint32_t size) override final;

    virtual void KeyboardEnter(wl_keyboard * keyboard,
                               uint32_t serial,
                               wl_surface * surface,
                               wl_array * keys) override final;

    virtual void KeyboardLeave(wl_keyboard * keyboard,
                               uint32_t serial,
                               wl_surface * surface) override final;

    virtual void KeyboardKey(wl_keyboard * keyboard,
                             uint32_t serial,
                             uint32_t time,
                             uint32_t key,
                             uint32_t state) override final;

    virtual void KeyboardModifiers(wl_keyboard * keyboard,
                                   uint32_t serial,
                                   uint32_t mods_depressed,
                                   uint32_t mods_latched,
                                   uint32_t mods_locked,
                                   uint32_t group) override final;

    virtual void KeyboardRepeatInfo(wl_keyboard * keyboard,
                                    int32_t rate,
                                    int32_t delay) override final;

    window _window;
    display _display;

//    Display * _display;
//    Compositor * _compositor;
//    wl_shm * _shm;
//    wl_shell * _shell;
//    Seat * _seat;
//    Pointer * _pointer;
//    Keyboard * _keyboard;
//    KeyboardCallbackFunction _keyboardCallback;
//    KeyCode _keyFilter;
    bool _isRunning;
};

} // namespace Wayland
