#pragma once

#include <string.h>
#include <iostream>
#include <wayland-client.h>
#include "IRegistryListener.h"

namespace Wayland
{

class Display :
    public IRegistryListener
{
public:
    Display() {}
    ~Display() {}

    bool Setup();
    void Cleanup()
    {
        wl_pointer_destroy(_pointer);
        wl_seat_destroy(_seat);
        wl_shell_destroy(_shell);
        wl_shm_destroy(_shm);
        wl_compositor_destroy(_compositor);
        wl_display_disconnect(_display);
    }
    bool Dispatch()
    {
        return (wl_display_dispatch(_display) >= 0);
    }

    wl_display * Get() const { return _display; }

    static wl_compositor * Compositor() { return _compositor; }
    static wl_shm * Shm() { return _shm; }
    static wl_shell * Shell() { return _shell; }
    static wl_seat * Seat() { return _seat; }
    static wl_pointer * Pointer() { return _pointer; }

private:
    virtual void RegistryCallbackGlobalAdd(wl_registry * wl_registry,
                                           uint32_t name,
                                           const char * interface,
                                           uint32_t version) override final;
    virtual void RegistryCallbackGlobalRemove(wl_registry * wl_registry,
                                              uint32_t name) override final;

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
    static wl_pointer * _pointer;
};

} // namespace Wayland
