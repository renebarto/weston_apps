#pragma once

class wl_seat;

namespace Wayland
{

class ISeatListener
{
public:
    virtual ~ISeatListener() {}

    virtual void OnSeatHandleCapabilities(wl_seat * seat,
                                          uint32_t caps) = 0;
    virtual void OnSeatName(wl_seat * seat, const char * name) = 0;
};

} // namespace Wayland
