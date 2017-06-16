#pragma once

struct wl_seat;
struct wl_pointer;
struct wl_keyboard;
struct wl_touch;

namespace Wayland
{

class ISeatListener;

class Seat
{
public:
    Seat(wl_seat * seat);
    ~Seat();

    wl_seat * Get() { return _seat; }
    wl_pointer * GetPointer();
    wl_keyboard * GetKeyboard();
    wl_touch * GetTouch();

    void AddListener(ISeatListener * listener);
    void RemoveListener() { AddListener(nullptr); }
    void Cleanup();

private:
    wl_seat * _seat;
};

} // namespace Wayland
