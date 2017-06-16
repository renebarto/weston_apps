#include "Pointer.h"

#include <cstdio>
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
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## pointer_enter(data %p, pointer %p, serial %u, surface %p, X %d, Y %d)\n",
            data, pointer, serial, surface, surfaceX, surfaceY);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->OnPointerEnter(pointer, serial, surface, surfaceX, surfaceY);
}

static void PointerLeave(void * data,
                         wl_pointer * pointer, uint32_t serial,
                         wl_surface * surface)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## pointer_leave(data %p, pointer %p, serial %u, surface %p)\n",
            data, pointer, serial, surface);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->OnPointerLeave(pointer, serial, surface);
}

static void PointerMotion(void * data,
                          wl_pointer * pointer, uint32_t time,
                          wl_fixed_t surfaceX, wl_fixed_t surfaceY)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## pointer_motion(data %p, pointer %p, time %u, X %d, Y %d)\n",
            data, pointer, time, surfaceX, surfaceY);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->OnPointerMotion(pointer, time, surfaceX, surfaceY);
}

static void PointerButton(void *data,
                          wl_pointer * pointer, uint32_t serial,
                          uint32_t time, uint32_t button, uint32_t state)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## pointer_button(data %p, pointer %p, serial %u, time %u, button %d, state %u)\n",
            data, pointer, serial, time, button, state);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->OnPointerButton(pointer, serial, time, button, state);
}

static void PointerAxis(void *data,
                        wl_pointer * pointer, uint32_t time,
                        uint32_t axis, wl_fixed_t value)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## pointer_axis(data %p, pointer %p, time %u, axis %u, value %d)\n",
            data, pointer, time, axis, value);
#endif
    IPointerListener * listener = reinterpret_cast<IPointerListener *>(data);
    listener->OnPointerAxis(pointer, time, axis, value);
}

static const wl_pointer_listener PointerListener = {
    .enter = PointerEnter,
    .leave = PointerLeave,
    .motion = PointerMotion,
    .button = PointerButton,
    .axis = PointerAxis
};

Pointer::Pointer(wl_pointer * pointer)
    : _pointer(pointer)
    , _targetSurface()
    , _surface()
    , _buffer()
    , _hotspotX()
    , _hotspotY()
{
}

Pointer::~Pointer()
{
    Reset();
    if (_pointer)
        wl_pointer_destroy(_pointer);
    _pointer = nullptr;
}

void Pointer::AddListener(IPointerListener * listener)
{
    wl_pointer_add_listener(_pointer, &PointerListener, listener);
}

bool Pointer::SetFromPool(Compositor * compositor, ShmPool & pool,
                          unsigned width, unsigned height,
                          int32_t hotspotX, int32_t hotspotY)
{
    _surface = new Surface;
    if (!_surface->Create(compositor))
    {
        Reset();
        return false;
    }

    _buffer = new Buffer;
    if (!_buffer->Create(pool, width, height))
    {
        Reset();
        return false;
    }

    _hotspotX = hotspotX;
    _hotspotY = hotspotY;

    return true;
}

void Pointer::Reset()
{
    if (_surface)
        delete _surface;
    _surface = nullptr;
    if (_buffer)
        delete _buffer;
    _buffer = nullptr;
    _hotspotX = {};
    _hotspotY = {};
}

void Pointer::AttachBufferToSurface()
{
    _surface->Attach(_buffer->Get());
    _surface->Commit();
}

void Pointer::SetCursor(uint32_t serial)
{
    wl_pointer_set_cursor(_pointer, serial,
                          _surface->Get(),
                          _hotspotX,
                          _hotspotY);
}