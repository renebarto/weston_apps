#pragma once

#include <string.h>
#include <iostream>
#include <wayland-client.h>

namespace Wayland
{

class Display
{
public:
    Display();
    ~Display();

    bool Setup(const char * name);
    void Roundtrip();
    void Cleanup();
    bool Dispatch();
    bool DispatchPending();

    wl_display * Get() const { return _display; }

private:
    wl_display * _display;
};

} // namespace Wayland
