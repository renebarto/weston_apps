#pragma once

struct wl_compositor;

namespace Wayland
{

class Surface;
class Region;

class Compositor
{
public:
    Compositor(wl_compositor * compositor);
    ~Compositor();

    wl_compositor * Get() { return _compositor; }
    void Cleanup();
    Surface * CreateSurface();
    Region * CreateRegion();

private:
    wl_compositor * _compositor;
};

} // namespace Wayland
