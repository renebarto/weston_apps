#include "IVISurface.h"

#include <cstdio>
#include <wayland-client.h>
#include "protocol/ivi-application-client-protocol.h"
#include "IIVISurfaceListener.h"

using namespace Wayland;

static void OnIVISurfaceConfigure(void * data,
                                  ivi_surface * surface, int32_t width, int32_t height)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## ivi_surface_configure(data %p, surface %p, width %d, height %d)\n",
            data, surface, width, height);
#endif
    IIVISurfaceListener * listener = reinterpret_cast<IIVISurfaceListener *>(data);
    listener->OnIVISurfaceConfigure(surface, width, height);
}

static const ivi_surface_listener IVISurfaceListener = {
    .configure = OnIVISurfaceConfigure
};

IVISurface::IVISurface(ivi_surface * surface)
    : _surface(surface)
{
}

IVISurface::~IVISurface()
{
    Cleanup();
}

void IVISurface::AddListener(IIVISurfaceListener * listener)
{
    ivi_surface_add_listener(_surface, &IVISurfaceListener, listener);
}

void IVISurface::Cleanup()
{
    if (_surface)
        ivi_surface_destroy(_surface);
    _surface = nullptr;
}
