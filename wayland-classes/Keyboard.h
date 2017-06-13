#pragma once

#include <wayland-client.h>

namespace Wayland
{

//class ShmPool;
class Surface;
//class Buffer;

class KeyboardData
{
public:
    KeyboardData();
    ~KeyboardData();

};

class Keyboard
{
public:
    Keyboard(wl_keyboard * pointer);
    ~Keyboard()
    {
        _keyboard = nullptr;
    }

    bool Set(wl_compositor * compositor);

    void Release();

private:
    wl_keyboard * _keyboard;
};

} // namespace Wayland
