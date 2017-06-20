#pragma once

namespace Wayland
{

struct Geometry
{
    int width, height;

    Geometry()
        : width()
        , height()
    {}
    Geometry(int width, int height)
        : width(width)
        , height(height)
    {}
};

} // namespace Wayland
