#include "Compositor.h"

#include <wayland-client.h>

using namespace Wayland;

Compositor::Compositor(wl_compositor *compositor)
    : _compositor(compositor)
{
}

Compositor::~Compositor()
{
    if (_compositor)
        wl_compositor_destroy(_compositor);
    _compositor = nullptr;
}