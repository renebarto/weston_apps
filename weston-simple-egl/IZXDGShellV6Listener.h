#pragma once

#include <cstdint>

class zxdg_shell_v6;

namespace Wayland
{

class IZXDGShellV6Listener
{
public:
    virtual ~IZXDGShellV6Listener() {}

    virtual void OnXDGShellPing(zxdg_shell_v6 *shell, uint32_t serial) = 0;
};

} // namespace Wayland
