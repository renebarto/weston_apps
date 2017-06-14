#pragma once

#include <string.h>
#include <iostream>
#include <wayland-client.h>
#include "IRegistryListener.h"
#include "IPointerListener.h"
#include "IKeyboardListener.h"

namespace Wayland
{

class Display;
class Compositor;
class Seat;
class Keyboard;
class Pointer;
using KeyCode = int;
using KeyboardCallbackFunction = void (*)();

class Application :
    public IRegistryListener,
    public IPointerListener,
    public IKeyboardListener
{
public:
    Application();
    ~Application();

    bool Setup();
    void Cleanup();
    bool Dispatch();

    Compositor * GetCompositor() { return _compositor; }
    wl_shm * GetShm() { return _shm; }
    wl_shell * GetShell() { return _shell; }
    const Seat * GetSeat() const { return _seat; }
    Pointer * GetPointer() { return _pointer; }
    const Keyboard * GetKeyboard() const { return _keyboard; }

    void SetKeyboardCallback(KeyCode key, KeyboardCallbackFunction callback);

private:
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

    Display * _display;
    Compositor * _compositor;
    wl_shm * _shm;
    wl_shell * _shell;
    Seat * _seat;
    Pointer * _pointer;
    Keyboard * _keyboard;
    KeyboardCallbackFunction _keyboardCallback;
    KeyCode _keyFilter;
};

} // namespace Wayland
