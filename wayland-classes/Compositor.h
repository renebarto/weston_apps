#pragma once

struct wl_compositor;

namespace Wayland
{

class Compositor
{
public:
    Compositor(wl_compositor * compositor);
    ~Compositor();

    wl_compositor * Get() { return _compositor; }

private:
    wl_compositor * _compositor;
};

} // namespace Wayland
