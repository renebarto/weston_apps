#pragma once

class zxdg_surface_v6;

namespace Wayland
{

class IZXDGSurfaceV6Listener;

    class ZXDGSurfaceV6
{
public:
    ZXDGSurfaceV6(zxdg_surface_v6 * surface);
    ~ZXDGSurfaceV6();

    zxdg_surface_v6 * Get() { return _surface; }
    void AddListener(IZXDGSurfaceV6Listener * listener);
    void RemoveListener() { AddListener(nullptr); }
    void Cleanup();

private:
    zxdg_surface_v6 * _surface;
};

} // namespace Wayland
