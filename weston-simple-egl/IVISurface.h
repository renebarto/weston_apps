#pragma once

class ivi_surface;

namespace Wayland
{

class IIVISurfaceListener;

    class IVISurface
{
public:
    IVISurface(ivi_surface * surface);
    ~IVISurface();

    ivi_surface * Get() { return _surface; }
    void AddListener(IIVISurfaceListener * listener);
    void RemoveListener() { AddListener(nullptr); }
    void Cleanup();

private:
    ivi_surface * _surface;
};

} // namespace Wayland
