#include "Shm.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <wayland-client.h>

namespace Wayland
{

Shm::Shm(wl_shm * shm)
    : _shm(shm)
{
}

Shm::~Shm()
{
    Cleanup();
}

void Shm::Cleanup()
{
    if (_shm != nullptr)
    {
        wl_shm_destroy(_shm);
    }
    _shm = nullptr;
}

} // namespace Wayland
