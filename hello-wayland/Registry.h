#pragma once

struct wl_display;
struct wl_registry;

namespace Wayland
{

class Display;
class IRegistryListener;

class Registry
{
public:
    Registry(wl_display * display);
    ~Registry();
    void AddListener(IRegistryListener const * registryListener);

private:
    wl_registry * _registry;
};

} // namespace Wayland
