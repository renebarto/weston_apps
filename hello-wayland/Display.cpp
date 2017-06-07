#include "Display.h"
#include "Registry.h"

using namespace Wayland;

wl_compositor * Display::_compositor = nullptr;
wl_shm * Display::_shm = nullptr;
wl_shell * Display::_shell = nullptr;
wl_seat * Display::_seat = nullptr;
wl_pointer * Display::_pointer = nullptr;
const wl_registry_listener Display::_registryListener = {
    .global = RegistryGlobalAdd,
    .global_remove = RegistryGlobalRemove
};

bool Display::Setup()
{
    _display = wl_display_connect(NULL);
    if (_display == nullptr) {
    std::cerr << "Error opening display" << std::endl;
    return false;
    }
    Registry registry(*this);
    registry.AddListener(_registryListener);
    wl_display_roundtrip(_display);
}
