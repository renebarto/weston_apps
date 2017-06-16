#pragma once

class wl_pointer;
class wl_surface;
#include "wayland-util.h"

namespace Wayland
{

class IPointerListener
{
public:
    virtual ~IPointerListener() {}

    virtual void OnPointerEnter(wl_pointer *pointer,
                                uint32_t serial, wl_surface *surface,
                                wl_fixed_t surfaceX, wl_fixed_t surfaceY) = 0;

    virtual void OnPointerLeave(wl_pointer *pointer, uint32_t serial,
                                wl_surface *wl_surface) = 0;

    virtual void OnPointerMotion(wl_pointer *pointer, uint32_t time,
                                 wl_fixed_t surfaceX, wl_fixed_t surfaceY) = 0;

    virtual void OnPointerButton(wl_pointer *pointer, uint32_t serial,
                                 uint32_t time, uint32_t button, uint32_t state) = 0;

    virtual void OnPointerAxis(wl_pointer *pointer, uint32_t time,
                               uint32_t axis, wl_fixed_t value) = 0;
};

} // namespace Wayland
