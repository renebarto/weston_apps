#include "Compositor.h"

#include <wayland-client.h>
#include "Region.h"
#include "Surface.h"

using namespace Wayland;

Compositor::Compositor(wl_compositor *compositor)
    : _compositor(compositor)
{
}

Compositor::~Compositor()
{
    Cleanup();
}

void Compositor::Cleanup()
{
    if (_compositor)
        wl_compositor_destroy(_compositor);
    _compositor = nullptr;
}

Surface * Compositor::CreateSurface()
{
    Surface * surface = new Surface(wl_compositor_create_surface(_compositor));
    return surface;
}


Region * Compositor::CreateRegion()
{
    Region * region = new Region(wl_compositor_create_region(_compositor));
    return region;
}

