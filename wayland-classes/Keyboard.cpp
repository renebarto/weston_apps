#include "Keyboard.h"

#include <cstdio>

using namespace Wayland;

static void KeyboardKeymap(void * data,
                           wl_keyboard * keyboard,
                           uint32_t format,
                           int32_t fd,
                           uint32_t size)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## keyboard_keymap(data %p, keyboard %p, format %u, fd %d, size %u)\n",
            data, keyboard, format, fd, size);
#endif
    IKeyboardListener * listener = reinterpret_cast<IKeyboardListener *>(data);
    listener->OnKeyboardKeymap(keyboard, format, fd, size);
}

static void KeyboardEnter(void * data,
                          wl_keyboard * keyboard,
                          uint32_t serial,
                          wl_surface * surface,
                          wl_array * keys)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## keyboard_enter(data %p, keyboard %p, serial %u, surface %p, keys %p)\n",
            data, keyboard, serial, surface, keys);
#endif
    IKeyboardListener * listener = reinterpret_cast<IKeyboardListener *>(data);
    listener->OnKeyboardEnter(keyboard, serial, surface, keys);
}

static void KeyboardLeave(void * data,
                          wl_keyboard * keyboard,
                          uint32_t serial,
                          wl_surface * surface)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## keyboard_leave(data %p, keyboard %p, serial %u, surface %p)\n",
            data, keyboard, serial, surface);
#endif
    IKeyboardListener * listener = reinterpret_cast<IKeyboardListener *>(data);
    listener->OnKeyboardLeave(keyboard, serial, surface);
}

static void KeyboardKey(void * data,
                        wl_keyboard * keyboard,
                        uint32_t serial,
                        uint32_t time,
                        uint32_t key,
                        uint32_t state)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## keyboard_key(data %p, keyboard %p, serial %u, time %u, key %u, state %u)\n",
            data, keyboard, serial, time, key, state);
#endif
    IKeyboardListener * listener = reinterpret_cast<IKeyboardListener *>(data);
    listener->OnKeyboardKey(keyboard, serial, time, key, state);
}

static void KeyboardModifiers(void * data,
                              wl_keyboard * keyboard,
                              uint32_t serial,
                              uint32_t mods_depressed,
                              uint32_t mods_latched,
                              uint32_t mods_locked,
                              uint32_t group)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## keyboard_key(data %p, keyboard %p, serial %u, depressed %u, latched %u, locked %u, group %u)\n",
            data, keyboard, serial, mods_depressed, mods_latched, mods_locked, group);
#endif
    IKeyboardListener * listener = reinterpret_cast<IKeyboardListener *>(data);
    listener->OnKeyboardModifiers(keyboard, serial, mods_depressed, mods_latched, mods_locked, group);
}

static void KeyboardRepeatInfo(void * data,
                                wl_keyboard * keyboard,
                                int32_t rate,
                                int32_t delay)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## keyboard_key(data %p, keyboard %p, rate %d, delay %d)\n",
            data, keyboard, rate, delay);
#endif
    IKeyboardListener * listener = reinterpret_cast<IKeyboardListener *>(data);
    listener->OnKeyboardRepeatInfo(keyboard, rate, delay);
}

static const wl_keyboard_listener KeyboardListener = {
    .keymap = KeyboardKeymap,
    .enter = KeyboardEnter,
    .leave = KeyboardLeave,
    .key = KeyboardKey,
    .modifiers = KeyboardModifiers,
    .repeat_info = KeyboardRepeatInfo
};

Keyboard::Keyboard(wl_keyboard * keyboard)
    : _keyboard(keyboard)
{
}

Keyboard::~Keyboard()
{
    Reset();
    if (_keyboard)
        wl_keyboard_destroy(_keyboard);
    _keyboard = nullptr;
}

void Keyboard::AddListener(IKeyboardListener * listener)
{
    wl_keyboard_add_listener(_keyboard, &KeyboardListener, listener);
}

void Keyboard::Reset()
{
}

