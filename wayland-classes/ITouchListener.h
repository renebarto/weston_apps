#pragma once

class wl_touch;
class wl_surface;
class wl_array;

namespace Wayland
{

class ITouchListener
{
public:
    virtual ~ITouchListener() {}

    virtual void OnTouchDown(wl_touch * touch,
                             uint32_t serial,
                             uint32_t time,
                             wl_surface * surface,
                             int32_t id,
                             wl_fixed_t x,
                             wl_fixed_t y) = 0;

    virtual void OnTouchUp(wl_touch * touch,
                           uint32_t serial,
                           uint32_t time,
                           int32_t id) = 0;

    virtual void OnTouchMotion(wl_touch * touch,
                               uint32_t time,
                               int32_t id,
                               wl_fixed_t x,
                               wl_fixed_t y) = 0;

    virtual void OnTouchFrame(wl_touch * touch) = 0;

    virtual void OnTouchCancel(wl_touch * touch) = 0;
};

} // namespace Wayland
