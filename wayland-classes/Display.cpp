#include "Display.h"
#include "Registry.h"
#include "Pointer.h"
#include "Surface.h"
#include "Buffer.h"

using namespace Wayland;

wl_compositor * Display::_compositor = nullptr;
wl_shm * Display::_shm = nullptr;
wl_shell * Display::_shell = nullptr;
wl_seat * Display::_seat = nullptr;
Pointer * Display::_pointer = nullptr;

typedef void (*CallbackFunction)(uint32_t);

bool Display::Setup()
{
    _display = wl_display_connect(NULL);
    if (_display == nullptr)
    {
        std::cerr << "Error opening display" << std::endl;
        return false;
    }
    return true;
}

void Display::Cleanup()
{
    delete _pointer;
    wl_seat_destroy(_seat);
    wl_shell_destroy(_shell);
    wl_shm_destroy(_shm);
    wl_compositor_destroy(_compositor);
    wl_display_disconnect(_display);
}

void Display::Roundtrip()
{
    wl_display_roundtrip(_display);
}


void Display::RegistryCallbackGlobalAdd(wl_registry * registry, uint32_t name,
                                        const char * interface, uint32_t version)
{
    if (strcmp(interface, wl_compositor_interface.name) == 0)
        _compositor = reinterpret_cast<wl_compositor *>(wl_registry_bind(registry, name, &wl_compositor_interface, std::min(version, uint32_t(4))));
    else if (strcmp(interface, wl_shm_interface.name) == 0)
        _shm = reinterpret_cast<wl_shm *>(wl_registry_bind(registry, name, &wl_shm_interface, std::min(version, uint32_t(1))));
    else if (strcmp(interface, wl_shell_interface.name) == 0)
        _shell = reinterpret_cast<wl_shell *>(wl_registry_bind(registry, name, &wl_shell_interface, std::min(version, uint32_t(1))));
    else if (strcmp(interface, wl_seat_interface.name) == 0)
    {
        _seat = reinterpret_cast<wl_seat *>(wl_registry_bind(registry, name, &wl_seat_interface, std::min(version, uint32_t(2))));
        _pointer = new Pointer(wl_seat_get_pointer(_seat));
        _pointer->AddListener(this);
    }
}

void Display::RegistryCallbackGlobalRemove(wl_registry * registry, uint32_t name)
{

}

void Display::PointerEnter(wl_pointer * pointer,
                           uint32_t serial, wl_surface * surface,
                           wl_fixed_t surfaceX, wl_fixed_t surfaceY)
{
    PointerData * pointerData = reinterpret_cast<PointerData *>(wl_pointer_get_user_data(pointer));
    pointerData->_targetSurface = surface;
    pointerData->_surface->Attach(pointerData->_buffer->Get());
    pointerData->_surface->Commit();
    wl_pointer_set_cursor(pointer, serial,
                          pointerData->_surface->Get(),
                          pointerData->_hotspotX,
                          pointerData->_hotspotY);
}

void Display::PointerLeave(wl_pointer * pointer, uint32_t serial,
                           wl_surface * wl_surface)
{

}

void Display::PointerMotion(wl_pointer * pointer, uint32_t time,
                            wl_fixed_t surfaceX, wl_fixed_t surfaceY)
{

}

void Display::PointerButton(wl_pointer * pointer, uint32_t serial,
                            uint32_t time, uint32_t button, uint32_t state)
{
    PointerData * pointerData = reinterpret_cast<PointerData *>(wl_pointer_get_user_data(pointer));
    CallbackFunction callback;

    callback = reinterpret_cast<CallbackFunction>(wl_surface_get_user_data(pointerData->_targetSurface));
    if (callback != nullptr)
        callback(button);
}

void Display::PointerAxis(wl_pointer * pointer, uint32_t time,
                          uint32_t axis, wl_fixed_t value)
{

}

