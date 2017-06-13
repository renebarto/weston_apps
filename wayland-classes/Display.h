#pragma once

#include <string.h>
#include <iostream>
#include <wayland-client.h>
#include "IRegistryListener.h"
#include "IPointerListener.h"

namespace Wayland
{

class Pointer;

class Display :
    public IRegistryListener,
    public IPointerListener
{
public:
    Display() {}
    ~Display() {}

    bool Setup();
    void Roundtrip();
    void Cleanup();
    bool Dispatch()
    {
        return (wl_display_dispatch(_display) >= 0);
    }

    wl_display * Get() const { return _display; }

    static wl_compositor * Compositor() { return _compositor; }
    static wl_shm * Shm() { return _shm; }
    static wl_shell * Shell() { return _shell; }
    static wl_seat * Seat() { return _seat; }
    static Pointer * GetPointer() { return _pointer; }

private:
    virtual void RegistryCallbackGlobalAdd(wl_registry * wl_registry,
                                           uint32_t name,
                                           const char * interface,
                                           uint32_t version) override final;
    virtual void RegistryCallbackGlobalRemove(wl_registry * wl_registry,
                                              uint32_t name) override final;

    virtual void PointerEnter(wl_pointer * pointer,
                              uint32_t serial, wl_surface * surface,
                              wl_fixed_t surfaceX, wl_fixed_t surfaceY) override final;

    virtual void PointerLeave(wl_pointer * pointer, uint32_t serial,
                              wl_surface * wl_surface) override final;

    virtual void PointerMotion(wl_pointer * pointer, uint32_t time,
                               wl_fixed_t surfaceX, wl_fixed_t surfaceY) override final;

    virtual void PointerButton(wl_pointer * pointer, uint32_t serial,
                               uint32_t time, uint32_t button, uint32_t state) override final;

    virtual void PointerAxis(wl_pointer * pointer, uint32_t time,
                             uint32_t axis, wl_fixed_t value) override final;


//    static constexpr wl_pointer_listener _pointerListener = {
//        .enter = pointer_enter,
//        .leave = pointer_leave,
//        .motion = pointer_motion,
//        .button = pointer_button,
//        .axis = pointer_axis
//    };

    wl_display * _display;
    static wl_compositor * _compositor;
    static wl_shm * _shm;
    static wl_shell * _shell;
    static wl_seat * _seat;
    static Pointer * _pointer;
};

} // namespace Wayland
