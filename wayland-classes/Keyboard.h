#pragma once

#include <wayland-client.h>
#include "IKeyboardListener.h"

namespace Wayland
{

class Surface;

class Keyboard
{
public:
    Keyboard(wl_keyboard * pointer);
    ~Keyboard();

    const wl_keyboard * Get() const { return _keyboard; }
    void AddListener(IKeyboardListener * keyboardListener);
    void RemoveListener() { AddListener(nullptr); }
    bool Set(wl_compositor * compositor);
    void Reset();

private:
    wl_keyboard * _keyboard;
};

} // namespace Wayland
