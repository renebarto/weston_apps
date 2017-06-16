#pragma once

#include <cstdint>

class zxdg_toplevel_v6;

namespace Wayland
{

class IZXDGTopLevelV6Listener
{
public:
    virtual ~IZXDGTopLevelV6Listener() {}

    virtual void OnXDGTopLevelConfigure(zxdg_toplevel_v6 * toplevel,
                                        int32_t width,
                                        int32_t height,
                                        wl_array * states) = 0;

    virtual void OnXDGTopLevelClose(zxdg_toplevel_v6 * toplevel) = 0;
};

} // namespace Wayland
