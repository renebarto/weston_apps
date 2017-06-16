#pragma once

#include <cstdint>

class zxdg_toplevel_v6;

namespace Wayland
{

class Seat;
class IZXDGTopLevelV6Listener;

class ZXDGTopLevelV6
{
public:
    ZXDGTopLevelV6(zxdg_toplevel_v6 * toplevel);
    ~ZXDGTopLevelV6();

    zxdg_toplevel_v6 * Get() { return _toplevel; }
    void AddListener(IZXDGTopLevelV6Listener * listener);
    void RemoveListener() { AddListener(nullptr); }
    void Cleanup();
    void SetTitle(const char * title);
    void SetFullScreen();
    void UnsetFullScreen();
    void Move(Seat * seat, uint32_t serial);

private:
    zxdg_toplevel_v6 * _toplevel;
};

} // namespace Wayland
