#include "Registry.h"

#include <wayland-client.h>
#include "Display.h"
#include "IRegistryListener.h"

using namespace Wayland;

static void RegistryGlobalAdd(void * data,
                              wl_registry * registry, uint32_t name,
                              const char * interface, uint32_t version)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## registry_global_add_callback(data %p, registry %p, name %u, intf %s, version %u)\n",
            data, registry, name, interface, version);
#endif
    IRegistryListener * listener = reinterpret_cast<IRegistryListener *>(data);
    listener->RegistryCallbackAdd(registry, name, interface, version);
}

static void RegistryGlobalRemove(void * data, wl_registry * registry, uint32_t name)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## registry_global_remove_callback(data %p, registry %p, name %u)\n",
            data, registry, name);
#endif
    IRegistryListener * listener = reinterpret_cast<IRegistryListener *>(data);
    listener->RegistryCallbackRemove(registry, name);
}

static const wl_registry_listener RegistryListener = {
    .global = RegistryGlobalAdd,
    .global_remove = RegistryGlobalRemove
};

Registry::Registry(const Display * display)
    : _registry(wl_display_get_registry(display->Get()))
{
}

Registry::~Registry()
{
    Cleanup();
}

void Registry::AddListener(IRegistryListener * registryListener)
{
    wl_registry_add_listener(_registry, &RegistryListener, registryListener);
}

void Registry::Cleanup()
{
    if (_registry)
        wl_registry_destroy(_registry);
    _registry = nullptr;
}
