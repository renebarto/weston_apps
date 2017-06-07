#pragma once

#include <wayland-client.h>
#include "Surface.h"

namespace Wayland
{

class ShmPool;

class Buffer
{
public:
    Buffer();
    ~Buffer();

    bool Create(ShmPool & pool,
                unsigned width, unsigned height);
    void Free();
    void Bind(ShellSurface & surface);

    wl_buffer * Get() { return _buffer; }

private:
    wl_buffer * _buffer;
};

} // namespace Wayland
