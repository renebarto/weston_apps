#pragma once

#include <string.h>
#include <iostream>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "protocol/xdg-shell-unstable-v6-client-protocol.h"
#include "protocol/ivi-application-client-protocol.h"
#include "IRegistryListener.h"
#include "IPointerListener.h"
#include "IKeyboardListener.h"
#include "ITouchListener.h"
#include "ISeatListener.h"
#include "IZXDGShellV6Listener.h"
#include "IZXDGSurfaceV6Listener.h"
#include "IZXDGTopLevelV6Listener.h"
#include "IIVISurfaceListener.h"
#include "Geometry.h"

namespace Wayland
{

class Callback;
class Compositor;
class Cursor;
class CursorTheme;
class Display;
class EGLWindow;
class IVISurface;
class Keyboard;
class Pointer;
class Registry;
class Seat;
class Shm;
class Touch;
class Surface;
class Touch;
class ZXDGShellV6;
class ZXDGSurfaceV6;
class ZXDGTopLevelV6;
class IVIApplication;

struct Settings
{
    Settings()
        : fullScreen()
        , opaque()
        , bufferSize(32)
        , frameSync(true)
    {
    }
    bool fullScreen;
    bool opaque;
    int bufferSize;
    bool frameSync;
};

class Application :
    public IRegistryListener,
    public IPointerListener,
    public IKeyboardListener,
    public ITouchListener,
    public ISeatListener,
    public IZXDGShellV6Listener,
    public IZXDGSurfaceV6Listener,
    public IZXDGTopLevelV6Listener,
    public IIVISurfaceListener
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

private:
    void InitEGL();
    void CleanupEGL();
    GLuint CreateShader(const char * source, GLenum shader_type);
    void InitGL();
    void CreateXDGSurface();
    void CreateIVISurface();
    void CreateSurface();
    void DestroySurface();
    void Redraw(uint32_t time);

    virtual void OnRegistryAdd(wl_registry *wl_registry,
                               uint32_t name,
                               const char *interface,
                               uint32_t version) override final;
    virtual void OnRegistryRemove(wl_registry *wl_registry,
                                  uint32_t name) override final;

    virtual void OnPointerEnter(wl_pointer *pointer,
                                uint32_t serial, wl_surface *surface,
                                wl_fixed_t surfaceX, wl_fixed_t surfaceY) override final;

    virtual void OnPointerLeave(wl_pointer *pointer, uint32_t serial,
                                wl_surface *surface) override final;

    virtual void OnPointerMotion(wl_pointer *pointer, uint32_t time,
                                 wl_fixed_t surfaceX, wl_fixed_t surfaceY) override final;

    virtual void OnPointerButton(wl_pointer *pointer, uint32_t serial,
                                 uint32_t time, uint32_t button, uint32_t state) override final;

    virtual void OnPointerAxis(wl_pointer *pointer, uint32_t time,
                               uint32_t axis, wl_fixed_t value) override final;

    virtual void OnKeyboardKeymap(wl_keyboard *keyboard,
                                  uint32_t format,
                                  int32_t fd,
                                  uint32_t size) override final;

    virtual void OnKeyboardEnter(wl_keyboard *keyboard,
                                 uint32_t serial,
                                 wl_surface *surface,
                                 wl_array *keys) override final;

    virtual void OnKeyboardLeave(wl_keyboard *keyboard,
                                 uint32_t serial,
                                 wl_surface *surface) override final;

    virtual void OnKeyboardKey(wl_keyboard *keyboard,
                               uint32_t serial,
                               uint32_t time,
                               uint32_t key,
                               uint32_t state) override final;

    virtual void OnKeyboardModifiers(wl_keyboard *keyboard,
                                     uint32_t serial,
                                     uint32_t mods_depressed,
                                     uint32_t mods_latched,
                                     uint32_t mods_locked,
                                     uint32_t group) override final;

    virtual void OnKeyboardRepeatInfo(wl_keyboard *keyboard,
                                      int32_t rate,
                                      int32_t delay) override final;

    virtual void OnTouchDown(wl_touch * touch,
                             uint32_t serial,
                             uint32_t time,
                             wl_surface * surface,
                             int32_t id,
                             wl_fixed_t x,
                             wl_fixed_t y) override final;

    virtual void OnTouchUp(wl_touch * touch,
                           uint32_t serial,
                           uint32_t time,
                           int32_t id) override final;

    virtual void OnTouchMotion(wl_touch * touch,
                               uint32_t time,
                               int32_t id,
                               wl_fixed_t x,
                               wl_fixed_t y) override final;

    virtual void OnTouchFrame(wl_touch * touch) override final;

    virtual void OnTouchCancel(wl_touch * touch) override final;

    virtual void OnSeatHandleCapabilities(wl_seat * seat,
                                          uint32_t caps) override final;

    virtual void OnSeatName(wl_seat * seat, const char * name) override final;

    virtual void OnXDGShellPing(zxdg_shell_v6 *shell,
                                uint32_t serial) override final;

    virtual void OnXDGSurfaceConfigure(zxdg_surface_v6 * surface, uint32_t serial) override final;

    virtual void OnXDGTopLevelConfigure(zxdg_toplevel_v6 * toplevel,
                                        int32_t width,
                                        int32_t height,
                                        wl_array * states) override final;

    virtual void OnXDGTopLevelClose(zxdg_toplevel_v6 * toplevel) override final;

    virtual void OnIVISurfaceConfigure(ivi_surface * surface, int32_t width, int32_t height) override final;

    Display * _display;
    Compositor * _compositor;
    Shm * _shm;
    ZXDGShellV6 * _shell;
    Seat * _seat;
    Pointer * _pointer;
    Keyboard * _keyboard;
    Touch * _touch;
    CursorTheme * _cursorTheme;
    Cursor * _defaultCursor;
    Surface * _cursorSurface;
    IVIApplication * _iviApplication;
    EGLWindow * _eglWindow;
    bool _isRunning;
    Geometry _geometry;
    Geometry _windowSize;
    struct
    {
        GLuint rotationUniform;
        GLuint pos;
        GLuint col;
    } _gl;

    uint32_t _benchmarkTime;
    uint32_t _numFrames;
    Surface * _surface;
    ZXDGSurfaceV6 * _xdgSurface;
    ZXDGTopLevelV6 * _xdgTopLevel;
    IVISurface * _iviSurface;
    bool _fullScreen;
    bool _opaque;
    int _bufferSize;
    bool _frameSync;
    bool _waitForConfigure;
};

} // namespace Wayland
