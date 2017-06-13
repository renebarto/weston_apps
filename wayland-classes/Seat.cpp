#include "Seat.h"

using namespace Wayland;

Seat::Seat(wl_seat *seat)
    : _seat(seat)
{

}

Seat::~Seat()
{
    _seat = nullptr;
}