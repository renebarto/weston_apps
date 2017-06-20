#include "IVIApplication.h"

#include <wayland-client.h>
#include "protocol/ivi-application-client-protocol.h"
#include "Surface.h"
#include "IVISurface.h"

using namespace Wayland;

IVIApplication::IVIApplication(ivi_application * application)
    : _application(application)
{
}

IVIApplication::~IVIApplication()
{
    Cleanup();
}

void IVIApplication::Cleanup()
{
    if (_application)
        ivi_application_destroy(_application);
    _application = nullptr;
}

IVISurface * IVIApplication::CreateSurface(Surface * surface, uint32_t id)
{
    ivi_surface * iviSurface = ivi_application_surface_create(_application, id, surface->Get());
    if (iviSurface == nullptr)
        return nullptr;
    return new IVISurface(iviSurface);
}
