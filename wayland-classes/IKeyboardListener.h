#pragma once

class wl_keyboard;
class wl_surface;
class wl_array;

namespace Wayland
{

class IKeyboardListener
{
public:
    virtual ~IKeyboardListener() {}

    virtual void OnKeyboardKeymap(wl_keyboard * keyboard,
                                  uint32_t format,
                                  int32_t fd,
                                  uint32_t size) = 0;

    virtual void OnKeyboardEnter(wl_keyboard * keyboard,
                                 uint32_t serial,
                                 wl_surface * surface,
                                 wl_array *keys) = 0;

    virtual void OnKeyboardLeave(wl_keyboard * keyboard,
                                 uint32_t serial,
                                 wl_surface * surface) = 0;

    virtual void OnKeyboardKey(wl_keyboard * keyboard,
                               uint32_t serial,
                               uint32_t time,
                               uint32_t key,
                               uint32_t state) = 0;

    virtual void OnKeyboardModifiers(wl_keyboard * keyboard,
                                     uint32_t serial,
                                     uint32_t mods_depressed,
                                     uint32_t mods_latched,
                                     uint32_t mods_locked,
                                     uint32_t group) = 0;

    virtual void OnKeyboardRepeatInfo(wl_keyboard * keyboard,
                                      int32_t rate,
                                      int32_t delay) = 0;
};

} // namespace Wayland
