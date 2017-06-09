#include "Registry.h"

#include <wayland-client.h>
#include "Display.h"

using namespace Wayland;

static void RegistryGlobalAdd(void * data,
                              wl_registry * registry, uint32_t name,
                              const char * interface, uint32_t version)
{
    IRegistryListener * listener = reinterpret_cast<IRegistryListener *>(data);
    listener->RegistryCallbackGlobalAdd(registry, name, interface, version);
}

static void RegistryGlobalRemove(void * data, wl_registry * registry, uint32_t name)
{
    IRegistryListener * listener = reinterpret_cast<IRegistryListener *>(data);
    listener->RegistryCallbackGlobalRemove(registry, name);
}

static const wl_registry_listener RegistryListener = {
    .global = RegistryGlobalAdd,
    .global_remove = RegistryGlobalRemove
};

Registry::Registry(wl_display * display)
    : _registry(wl_display_get_registry(display))
{
}

Registry::~Registry()
{
    wl_registry_destroy(_registry);
    _registry = nullptr;
}

void Registry::AddListener(IRegistryListener const * registryListener)
{
    wl_registry_add_listener(_registry, &RegistryListener, const_cast<IRegistryListener *>(registryListener));
}
