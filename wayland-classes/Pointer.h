#pragma once

#include <wayland-client.h>

namespace Wayland
{

class ShmPool;
class Surface;
class Buffer;
class Compositor;
class IPointerListener;

class Pointer
{
public:
    Pointer(wl_pointer * pointer);
    ~Pointer();

    wl_pointer * Get() { return _pointer; }
    void AddListener(IPointerListener * listener);
    void RemoveListener() { AddListener(nullptr); }
    bool SetFromPool(Compositor * compositor, ShmPool & pool,
                     unsigned width, unsigned height,
                     int32_t hotspotX, int32_t hotspotY);

    void Reset();
    wl_surface * GetTargetSurface() { return _targetSurface; }
    void SetTargetSurface(wl_surface * surface) { _targetSurface = surface; }
    void AttachBufferToSurface();
    void SetCursor(uint32_t serial);

private:
    wl_pointer * _pointer;
    wl_surface * _targetSurface;
    Surface * _surface;
    Buffer * _buffer;
    int32_t _hotspotX;
    int32_t _hotspotY;
};

} // namespace Wayland
