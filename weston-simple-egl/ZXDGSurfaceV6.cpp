#include "ZXDGSurfaceV6.h"

#include <cstdio>
#include <wayland-client.h>
#include "protocol/xdg-shell-unstable-v6-client-protocol.h"
#include "IZXDGSurfaceV6Listener.h"

using namespace Wayland;

static void XDGSurfaceConfigure(void * data,
                                zxdg_surface_v6 * surface, uint32_t serial)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## xdg_surface_configure(data %p, surface %p, serial %u)\n",
            data, surface, serial);
#endif
    IZXDGSurfaceV6Listener * listener = reinterpret_cast<IZXDGSurfaceV6Listener *>(data);
    listener->OnXDGSurfaceConfigure(surface, serial);
}

static const zxdg_surface_v6_listener ZXDGSurfaceV6Listener = {
    .configure = XDGSurfaceConfigure
};

ZXDGSurfaceV6::ZXDGSurfaceV6(zxdg_surface_v6 * surface)
    : _surface(surface)
{
}

ZXDGSurfaceV6::~ZXDGSurfaceV6()
{
    Cleanup();
}

void ZXDGSurfaceV6::AddListener(IZXDGSurfaceV6Listener * listener)
{
    zxdg_surface_v6_add_listener(_surface, &ZXDGSurfaceV6Listener, listener);
}

void ZXDGSurfaceV6::Cleanup()
{
    if (_surface)
        zxdg_surface_v6_destroy(_surface);
    _surface = nullptr;
}
