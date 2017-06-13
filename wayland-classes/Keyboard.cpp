#include "Keyboard.h"

//#include "ShmPool.h"
//#include "Surface.h"
//#include "Buffer.h"

using namespace Wayland;

KeyboardData::KeyboardData()
{}
KeyboardData::~KeyboardData()
{
}

Keyboard::Keyboard(wl_keyboard * keyboard)
    : _keyboard(keyboard)
{
}

bool Keyboard::Set(wl_compositor * compositor)
{
    KeyboardData * data = new KeyboardData;

    wl_keyboard_set_user_data(_keyboard, data);
    return true;
}

void Keyboard::Release()
{
    KeyboardData * data = reinterpret_cast<KeyboardData *>(wl_keyboard_get_user_data(_keyboard));
    delete data;
    wl_keyboard_set_user_data(_keyboard, nullptr);
}
