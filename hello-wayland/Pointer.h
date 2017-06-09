#pragma once

#include <wayland-client.h>

namespace Wayland
{

class ShmPool;
class Surface;
class Buffer;

    class PointerData
{
public:
    PointerData();
    ~PointerData();

    Surface * _surface;
    Buffer * _buffer;
    int32_t _hotspotX;
    int32_t _hotspotY;
    wl_surface * _targetSurface;
};

class Pointer
{
public:
    Pointer(wl_pointer * pointer);
    ~Pointer()
    {
        _pointer = nullptr;
    }

    bool SetFromPool(wl_compositor * compositor, ShmPool & pool,
                     unsigned width, unsigned height,
                     int32_t hotspotX, int32_t hotspotY);

    void Release();

private:
    wl_pointer * _pointer;
};

} // namespace Wayland
