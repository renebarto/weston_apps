#pragma once

#include <cstdint>

struct wl_surface;
struct wl_shell_surface;
struct wl_shell;
struct wl_buffer;

namespace Wayland
{

class Compositor;
class Region;

class Surface
{
public:
    Surface(wl_surface * surface);
    ~Surface();
    wl_surface * Get() const { return _surface; }
    void Destroy();
    void SetUserData(void (*callback)(uint32_t));
    void Attach(wl_buffer * buffer);
    void Commit();
    void SetOpaqueRegion(Region * region);
    void SetTransparent();

private:
    wl_surface * _surface;
};

class ShellSurface
{
public:
    ShellSurface();
    ~ShellSurface();
    bool Create(Compositor * compositor, wl_shell * shell);
    void Destroy();
    void SetButtonCallback(void (*callback)(uint32_t));
    Surface * GetSurface();

private:
    wl_shell_surface * _shellSurface;
};

} // namespace Wayland

