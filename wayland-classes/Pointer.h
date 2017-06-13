#pragma once

#include <wayland-client.h>

namespace Wayland
{

class ShmPool;
class Surface;
class Buffer;
class IPointerListener;

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
        wl_pointer_destroy(_pointer);
        _pointer = nullptr;
    }

    void AddListener(IPointerListener const * pointerListener);
    void RemoveListener() { AddListener(nullptr); }
    bool SetFromPool(wl_compositor * compositor, ShmPool & pool,
                     unsigned width, unsigned height,
                     int32_t hotspotX, int32_t hotspotY);

    void Release();

private:
    wl_pointer * _pointer;
};

} // namespace Wayland
