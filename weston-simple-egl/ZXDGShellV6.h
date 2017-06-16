#pragma once

class zxdg_shell_v6;

namespace Wayland
{

class IZXDGShellV6Listener;

    class ZXDGShellV6
{
public:
    ZXDGShellV6(zxdg_shell_v6 * shell);
    ~ZXDGShellV6();

    zxdg_shell_v6 * Get() { return _shell; }
    void AddListener(IZXDGShellV6Listener * listener);
    void RemoveListener() { AddListener(nullptr); }
    void Cleanup();

private:
    zxdg_shell_v6 * _shell;
};

} // namespace Wayland
