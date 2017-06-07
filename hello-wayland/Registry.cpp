#include "Registry.h"
#include "Display.h"

using namespace Wayland;

Registry::Registry(const Display & display)
    : _registry(wl_display_get_registry(display.Get()))
{
}