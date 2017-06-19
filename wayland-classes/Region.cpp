#include "Region.h"

#include <wayland-client.h>

using namespace Wayland;

Region::Region(wl_region * region)
    : _region(region)
{

}

Region::~Region()
{
    Destroy();
}

void Region::Destroy()
{
    if (_region != nullptr)
    {
        wl_region_destroy(_region);
        _region = nullptr;
    }
}

void Region::Add(int width, int height)
{
    wl_region_add(_region, 0, 0,
                  width,
                  height);
}