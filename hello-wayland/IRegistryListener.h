#pragma once

class wl_registry;

namespace Wayland
{

class IRegistryListener
{
public:
    virtual ~IRegistryListener() {}

    virtual void RegistryCallbackGlobalAdd(wl_registry * wl_registry,
                                           uint32_t name,
                                           const char * interface,
                                           uint32_t version) = 0;
    virtual void RegistryCallbackGlobalRemove(wl_registry * wl_registry,
                                              uint32_t name) = 0;
};

} // namespace Wayland
