#pragma once

struct wl_region;

namespace Wayland
{

class Region
{
public:
    Region(wl_region * region);
    ~Region();
    wl_region * Get() const { return _region; }
    void Destroy();

    void Add(int width, int height);

private:
    wl_region * _region;
};

} // namespace Wayland

