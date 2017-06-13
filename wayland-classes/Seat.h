#pragma once

struct wl_seat;

namespace Wayland
{

class Seat
{
public:
    Seat(wl_seat * seat);
    ~Seat();

private:
    wl_seat * _seat;
};

} // namespace Wayland
