#pragma once

#include <cstdint>

class ivi_application;

namespace Wayland
{

class Surface;
class IVISurface;

class IVIApplication
{
public:
    IVIApplication(ivi_application * application);
    ~IVIApplication();

    ivi_application * Get() { return _application; }
    void Cleanup();
    IVISurface * CreateSurface(Surface * surface, uint32_t id);

private:
    ivi_application * _application;
};

} // namespace Wayland
