#include "Seat.h"

#include <cstdio>
#include <wayland-client.h>
#include "ISeatListener.h"

using namespace Wayland;

static void SeatHandleCapabilities(void * data,
                                   wl_seat * seat, uint32_t caps)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## seat_capabilities(data %p, seat %p, caps %u)\n",
            data, seat, caps);
#endif
    ISeatListener * listener = reinterpret_cast<ISeatListener *>(data);
    listener->OnSeatHandleCapabilities(seat, caps);
}

static void SeatName(void * data,
                     wl_seat * seat, const char * name)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## seat_name(data %p, seat %p, name %s)\n",
            data, seat, name);
#endif
    ISeatListener * listener = reinterpret_cast<ISeatListener *>(data);
    listener->OnSeatName(seat, name);
}

static const struct wl_seat_listener SeatListener =
{
    .capabilities = SeatHandleCapabilities,
    .name = SeatName
};

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

wl_touch * Seat::GetTouch()
{
    return wl_seat_get_touch(_seat);
}

void Seat::AddListener(ISeatListener * listener)
{
    wl_seat_add_listener(_seat, &SeatListener, listener);
}

void Seat::Cleanup()
{
    if (_seat)
        wl_seat_destroy(_seat);
    _seat = nullptr;
}
