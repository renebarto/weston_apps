#pragma once

#include <cstddef>

struct wl_shm;

namespace Wayland
{

class Shm
{
public:
public:
    Shm(wl_shm * shm);
    ~Shm();

    void Cleanup();
    wl_shm * Get() const { return _shm; }

private:
    wl_shm * _shm;
};

} // namespace Wayland
