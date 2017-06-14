#pragma once

struct wl_seat;
struct wl_pointer;
struct wl_keyboard;

namespace Wayland
{

class Seat
{
public:
    Seat(wl_seat * seat);
    ~Seat();

    wl_pointer * GetPointer();
    wl_keyboard * GetKeyboard();

private:
    wl_seat * _seat;
};

} // namespace Wayland
