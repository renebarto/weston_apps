#include "Display.h"


#include <cassert>
#include "Registry.h"
#include "Pointer.h"

using namespace Wayland;

Display::Display()
    : _display()
{
}

bool Display::Setup(const char * name)
{
    _display = wl_display_connect(name);
    return (_display != nullptr);
}

void Display::Cleanup()
{
    wl_display_disconnect(_display);
}

void Display::Roundtrip()
{
    wl_display_roundtrip(_display);
}

bool Display::Dispatch()
{
    return (wl_display_dispatch(_display) >= 0);
}
