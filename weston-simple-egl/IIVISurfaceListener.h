#pragma once

#include <cstdint>

class ivi_surface;

namespace Wayland
{

class IIVISurfaceListener
{
public:
    virtual ~IIVISurfaceListener() {}

    virtual void OnIVISurfaceConfigure(ivi_surface * surface, int32_t width, int32_t height) = 0;
};

} // namespace Wayland
