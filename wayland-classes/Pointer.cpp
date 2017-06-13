#include "Pointer.h"

#include <cstdio>
#include <wayland-client.h>
#include "ShmPool.h"
#include "Surface.h"
#include "Buffer.h"
#include "IPointerListener.h"

using namespace Wayland;

static void PointerEnter(void * data,
                         wl_pointer * pointer,
                         uint32_t serial, wl_surface * surface,
                         wl_fixed_t surfaceX, wl_fixed_t surfaceY)
{
#ifdef WAYLAND_DEBUG
    fprintf(stderr, "## pointer_enter_callback(data %p, pointer %p, serial %u, surface %p, X %d, Y %d)\n",
            data, pointer, serial, surface, surfaceX, surfaceY);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->PointerEnter(pointer, serial, surface, surfaceX, surfaceY);
}

static void PointerLeave(void * data,
                         wl_pointer * pointer, uint32_t serial,
                         wl_surface * surface)
{
#ifdef WAYLAND_DEBUG
    fprintf(stderr, "## pointer_enter_callback(data %p, pointer %p, serial %u, surface %p)\n",
            data, pointer, serial, surface);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->PointerLeave(pointer, serial, surface);
}

static void PointerMotion(void * data,
                          wl_pointer * pointer, uint32_t time,
                          wl_fixed_t surfaceX, wl_fixed_t surfaceY)
{
#ifdef WAYLAND_DEBUG
    fprintf(stderr, "## pointer_motion_callback(data %p, pointer %p, time %u, X %d, Y %d)\n",
            data, pointer, time, surfaceX, surfaceY);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->PointerMotion(pointer, time, surfaceX, surfaceY);
}

static void PointerButton(void *data,
                          wl_pointer * pointer, uint32_t serial,
                          uint32_t time, uint32_t button, uint32_t state)
{
#ifdef WAYLAND_DEBUG
    fprintf(stderr, "## pointer_button_callback(data %p, pointer %p, serial %u, time %u, button %d, state %u)\n",
            data, pointer, serial, time, button, state);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->PointerButton(pointer, serial, time, button, state);
}

static void PointerAxis(void *data,
                        wl_pointer * pointer, uint32_t time,
                        uint32_t axis, wl_fixed_t value)
{
#ifdef WAYLAND_DEBUG
    fprintf(stderr, "## pointer_axis_callback(data %p, pointer %p, time %u, axis %u, value %d)\n",
            data, pointer, time, axis, value);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->PointerAxis(pointer, time, axis, value);
}

static const wl_pointer_listener PointerListener = {
    .enter = PointerEnter,
    .leave = PointerLeave,
    .motion = PointerMotion,
    .button = PointerButton,
    .axis = PointerAxis
};

PointerData::PointerData()
    : _surface()
    , _buffer()
    , _hotspotX()
    , _hotspotY()
    , _targetSurface()
{}
PointerData::~PointerData()
{
    if (_buffer != nullptr)
        delete _buffer;
    _buffer = nullptr;
    if (_surface != nullptr)
        delete _surface;
    _surface = nullptr;
    _targetSurface = nullptr;
    _hotspotX = {};
    _hotspotY = {};
}

Pointer::Pointer(wl_pointer * pointer)
    : _pointer(pointer)
{
}

void Pointer::AddListener(IPointerListener const * pointerListener)
{
    wl_pointer_add_listener(_pointer, &PointerListener, const_cast<IPointerListener *>(pointerListener));
}

bool Pointer::SetFromPool(wl_compositor * compositor, ShmPool & pool,
                          unsigned width, unsigned height,
                          int32_t hotspotX, int32_t hotspotY)
{
    PointerData * data = new PointerData;

    data->_hotspotX = hotspotX;
    data->_hotspotY = hotspotY;
    data->_surface = new Surface;
    if (!data->_surface->Create(compositor))
    {
        delete data;
        return false;
    }

    data->_buffer = new Buffer;
    if (!data->_buffer->Create(pool, width, height))
    {
        delete data;
        return false;
    }

    wl_pointer_set_user_data(_pointer, data);
    return true;
}

void Pointer::Release()
{
    PointerData * data = reinterpret_cast<PointerData *>(wl_pointer_get_user_data(_pointer));
    delete data;
    wl_pointer_set_user_data(_pointer, nullptr);
}
