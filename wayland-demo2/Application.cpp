#include "Application.h"

#include <cassert>
#include "Display.h"
#include "Keyboard.h"
#include "Pointer.h"
#include "Registry.h"
#include "Seat.h"
#include "Surface.h"

using namespace Wayland;

using CallbackFunction = void (*)(uint32_t);

Application::Application()
    : _display()
    , _compositor()
    , _shm()
    , _shell()
    , _seat()
    , _pointer()
    , _keyboard()
    , _keyboardCallback()
    , _keyFilter()
{
}

Application::~Application()
{
    Cleanup();
}

bool Application::Setup()
{
    _display = new Display;
    if (!_display->Setup(nullptr))
    {
        std::cerr << "Error opening display" << std::endl;
        return false;
    }
    Registry registry(_display);
    registry.AddListener(this);
    _display->Roundtrip();
    return true;
}

void Application::Cleanup()
{
    delete _keyboard;
    _keyboard = nullptr;
    delete _pointer;
    _pointer = nullptr;
    delete _seat;
    _seat = nullptr;
    wl_shell_destroy(_shell);
    wl_shm_destroy(_shm);
    delete _compositor;
    _compositor = nullptr;
    delete _display;
    _display = nullptr;
}

bool Application::Dispatch()
{
    return _display ? _display->Dispatch() : false;
}

void Application::SetKeyboardCallback(KeyCode key, KeyboardCallbackFunction callback)
{
    _keyboardCallback = callback;
    _keyFilter = key;
}

void Application::RegistryCallbackAdd(wl_registry *registry, uint32_t name,
                                  const char *interface, uint32_t version)
{
    if (strcmp(interface, wl_compositor_interface.name) == 0)
        _compositor = new Compositor(reinterpret_cast<wl_compositor *>(wl_registry_bind(registry, name, &wl_compositor_interface, std::min(version, uint32_t(4)))));
    else if (strcmp(interface, wl_shm_interface.name) == 0)
        _shm = reinterpret_cast<wl_shm *>(wl_registry_bind(registry, name, &wl_shm_interface, std::min(version, uint32_t(1))));
    else if (strcmp(interface, wl_shell_interface.name) == 0)
        _shell = reinterpret_cast<wl_shell *>(wl_registry_bind(registry, name, &wl_shell_interface, std::min(version, uint32_t(1))));
    else if (strcmp(interface, wl_seat_interface.name) == 0)
    {
        _seat = new Seat(reinterpret_cast<wl_seat *>(wl_registry_bind(registry, name, &wl_seat_interface, std::min(version, uint32_t(2)))));
        _pointer = new Pointer(_seat->GetPointer());
        _pointer->AddListener(this);
        _keyboard = new Keyboard(_seat->GetKeyboard());
        _keyboard->AddListener(this);
    }
}

// Is this ever called?
void Application::RegistryCallbackRemove(wl_registry *registry, uint32_t name)
{

}

void Application::PointerEnter(wl_pointer * pointer,
                               uint32_t serial, wl_surface * surface,
                               wl_fixed_t surfaceX, wl_fixed_t surfaceY)
{
    assert(pointer == _pointer->Get());
    _pointer->SetTargetSurface(surface);
    _pointer->AttachBufferToSurface();
    _pointer->SetCursor(serial);
}

void Application::PointerLeave(wl_pointer * pointer, uint32_t serial,
                               wl_surface * surface)
{
    assert(pointer == _pointer->Get());

}

void Application::PointerMotion(wl_pointer * pointer, uint32_t time,
                                wl_fixed_t surfaceX, wl_fixed_t surfaceY)
{
    assert(pointer == _pointer->Get());

}

void Application::PointerButton(wl_pointer * pointer, uint32_t serial,
                                uint32_t time, uint32_t button, uint32_t state)
{
    assert(pointer == _pointer->Get());
    CallbackFunction callback;

    callback = reinterpret_cast<CallbackFunction>(wl_surface_get_user_data(_pointer->GetTargetSurface()));
    if (callback != nullptr)
        callback(button);
}

void Application::PointerAxis(wl_pointer * pointer, uint32_t time,
                              uint32_t axis, wl_fixed_t value)
{
    assert(pointer == _pointer->Get());

}

void Application::KeyboardKeymap(wl_keyboard * keyboard,
                                 uint32_t format,
                                 int32_t fd,
                                 uint32_t size)
{
    assert(keyboard == _keyboard->Get());
}

void Application::KeyboardEnter(wl_keyboard * keyboard,
                                uint32_t serial,
                                wl_surface * surface,
                                wl_array * keys)
{
    assert(keyboard == _keyboard->Get());
}

void Application::KeyboardLeave(wl_keyboard * keyboard,
                                uint32_t serial,
                                wl_surface * surface)
{
    assert(keyboard == _keyboard->Get());
}

void Application::KeyboardKey(wl_keyboard * keyboard,
                              uint32_t serial,
                              uint32_t time,
                              uint32_t key,
                              uint32_t state)
{
    assert(keyboard == _keyboard->Get());

    if ((key == _keyFilter) && state)
    {
        if (_keyboardCallback != nullptr)
            _keyboardCallback();
    }
}

void Application::KeyboardModifiers(wl_keyboard * keyboard,
                                    uint32_t serial,
                                    uint32_t mods_depressed,
                                    uint32_t mods_latched,
                                    uint32_t mods_locked,
                                    uint32_t group)
{
    assert(keyboard == _keyboard->Get());
}

void Application::KeyboardRepeatInfo(wl_keyboard * keyboard,
                                     int32_t rate,
                                     int32_t delay)
{
    assert(keyboard == _keyboard->Get());
}
