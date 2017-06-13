#include "Compositor.h"

using namespace Wayland;

Compositor::Compositor(wl_compositor *compositor)
    : _compositor(compositor)
{

}

Compositor::~Compositor()
{
    _compositor = nullptr;
}