#pragma once

#include <wayland-client.h>
#include "IKeyboardListener.h"

namespace Wayland
{

class Keyboard
{
public:
    Keyboard(wl_keyboard * keyboard);
    ~Keyboard();

    const wl_keyboard * Get() const { return _keyboard; }
    void AddListener(IKeyboardListener * listener);
    void RemoveListener() { AddListener(nullptr); }
    void Reset();

private:
    wl_keyboard * _keyboard;
};

} // namespace Wayland
