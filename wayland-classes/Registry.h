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
    Registry(const Display * display);
    ~Registry();
    void AddListener(IRegistryListener * registryListener);
    void RemoveListener() { AddListener(nullptr); }
    void Cleanup();

private:
    wl_registry * _registry;
};

} // namespace Wayland
