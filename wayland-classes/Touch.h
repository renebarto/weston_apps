#pragma once

#include <wayland-client.h>
#include "ITouchListener.h"

namespace Wayland
{

class Surface;

class Touch
{
public:
    Touch(wl_touch * touch);
    ~Touch();

    const wl_touch * Get() const { return _touch; }
    void AddListener(ITouchListener * listener);
    void RemoveListener() { AddListener(nullptr); }
    void Reset();

private:
    wl_touch * _touch;
};

} // namespace Wayland
