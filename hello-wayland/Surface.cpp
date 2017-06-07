#include "Surface.h"

using namespace Wayland;

static void ShellSurfacePing(void * data,
                             struct wl_shell_surface * shell_surface, uint32_t serial)
{
    wl_shell_surface_pong(shell_surface, serial);
}

static void ShellSurfaceConfigure(void *data,
                                  struct wl_shell_surface *shell_surface,
                                  uint32_t edges, int32_t width, int32_t height)
{

}

static const struct wl_shell_surface_listener shell_surface_listener = {
    .ping = ShellSurfacePing,
    .configure = ShellSurfaceConfigure,
};

Surface::Surface()
    : _surface()
{

}

Surface::~Surface()
{
    if (_surface != nullptr)
        Destroy();
}

bool Surface::Create(wl_compositor * compositor)
{
    _surface = wl_compositor_create_surface(compositor);
    return true;
}

void Surface::Destroy()
{
    wl_surface_destroy(_surface);
    _surface = nullptr;
}

void Surface::SetUserData(void (*callback)(uint32_t))
{
    wl_surface_set_user_data(_surface, reinterpret_cast<void*>(callback));
}

void Surface::Attach(wl_buffer * buffer)
{
    wl_surface_attach(_surface, buffer, 0, 0);
}

void Surface::Commit()
{
    wl_surface_commit(_surface);
}

ShellSurface::ShellSurface()
{

}

ShellSurface::~ShellSurface()
{

}

bool ShellSurface::Create(wl_compositor * compositor, wl_shell * shell)
{
    Surface * surface = new Surface();
    surface->Create(compositor);

    if (surface == nullptr)
        return false;

    _shellSurface = wl_shell_get_shell_surface(shell, surface->Get());

    if (_shellSurface == nullptr)
    {
        delete surface;
        return false;
    }

    wl_shell_surface_add_listener(_shellSurface,
                                  &shell_surface_listener, nullptr);
    wl_shell_surface_set_toplevel(_shellSurface);
    wl_shell_surface_set_user_data(_shellSurface, surface);
    wl_surface_set_user_data(surface->Get(), nullptr);
}

void ShellSurface::Destroy()
{
    Surface * surface = GetSurface();
    wl_shell_surface_destroy(_shellSurface);
    delete surface;
    _shellSurface = nullptr;
}

void ShellSurface::SetButtonCallback(void (*callback)(uint32_t))
{
    Surface * surface = GetSurface();
    surface->SetUserData(callback);
}

Surface * ShellSurface::GetSurface()
{
    return reinterpret_cast<Surface *>(wl_shell_surface_get_user_data(_shellSurface));
}

