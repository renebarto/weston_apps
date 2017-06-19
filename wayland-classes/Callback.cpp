#include "Callback.h"

#include <wayland-client.h>

using namespace Wayland;

Callback::Callback(wl_callback * callback)
    : _callback(callback)
{

}

Callback::~Callback()
{
    Cleanup();
}

void Callback::Cleanup()
{
    if (_callback != nullptr)
    {
        wl_callback_destroy(_callback);
        _callback = nullptr;
    }
}

