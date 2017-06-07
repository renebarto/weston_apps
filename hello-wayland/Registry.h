#pragma once

#include <wayland-client.h>

namespace Wayland
{

class Display;

class Registry
{
public:
    Registry(const Display & display);
    ~Registry()
    {
        wl_registry_destroy(_registry);
        _registry = nullptr;
    }
    void AddListener(wl_registry_listener const & registryListener)
    {
        wl_registry_add_listener(_registry, &registryListener, nullptr);
    }

private:
    wl_registry * _registry;
};

} // namespace Wayland
