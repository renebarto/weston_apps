#include "Pointer.h"

#include "ShmPool.h"
#include "Surface.h"
#include "Buffer.h"

using namespace Wayland;

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
