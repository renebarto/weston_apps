#pragma once

#include <cstdint>

class zxdg_surface_v6;

namespace Wayland
{

class IZXDGSurfaceV6Listener
{
public:
    virtual ~IZXDGSurfaceV6Listener() {}

    virtual void OnXDGSurfaceConfigure(zxdg_surface_v6 * surface, uint32_t serial) = 0;
};

} // namespace Wayland
