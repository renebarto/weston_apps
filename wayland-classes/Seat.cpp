#include "Seat.h"

#include <wayland-client.h>

using namespace Wayland;

Seat::Seat(wl_seat *seat)
    : _seat(seat)
{

}

Seat::~Seat()
{
    if (_seat)
        wl_seat_destroy(_seat);
    _seat = nullptr;
}

wl_pointer * Seat::GetPointer()
{
    return wl_seat_get_pointer(_seat);
}

wl_keyboard * Seat::GetKeyboard()
{
    return wl_seat_get_keyboard(_seat);
}
