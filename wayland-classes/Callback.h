#pragma once

struct wl_callback;

namespace Wayland
{

class Callback
{
public:
    Callback(wl_callback * callback);
    ~Callback();
    wl_callback * Get() const { return _callback; }
    void Cleanup();

private:
    wl_callback * _callback;
};

} // namespace Wayland

