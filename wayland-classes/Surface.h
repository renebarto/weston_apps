#pragma once

#include <wayland-client.h>

namespace Wayland
{

class Surface
{
public:
    Surface();
    ~Surface();
    wl_surface * Get() const { return _surface; }
    bool Create(wl_compositor * compositor);
    void Destroy();
    void SetUserData(void (*callback)(uint32_t));
    void Attach(wl_buffer * buffer);
    void Commit();

private:
    wl_surface * _surface;
};

class ShellSurface
{
public:
    ShellSurface();
    ~ShellSurface();
    bool Create(wl_compositor * compositor, wl_shell * shell);
    void Destroy();
    void SetButtonCallback(void (*callback)(uint32_t));
    Surface * GetSurface();

private:
    wl_shell_surface * _shellSurface;
};

} // namespace Wayland

