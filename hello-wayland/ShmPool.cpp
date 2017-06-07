#include "ShmPool.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include "Display.h"

namespace Wayland
{

bool ShmPool::PoolData::Create(size_t size, int fd)
{
    _capacity = size;
    _size = 0;
    _fd = fd;
    _memory = reinterpret_cast<pixel *>(mmap(0, _capacity, PROT_READ, MAP_SHARED, fd, 0));
    if (_memory == MAP_FAILED)
    {
        return false;
    }
    return true;
}

ShmPool::PoolData::~PoolData()
{
    munmap(_memory, _capacity);
}

bool ShmPool::Create(int fd) {
    PoolData *data;
    struct stat stat;

    if (fstat(fd, &stat) != 0)
        return NULL;

    data = new PoolData();

    if (!data->Create(static_cast<size_t>(stat.st_size), fd))
    {
        delete data;
        return false;
    }

    _pool = wl_shm_create_pool(Display::Shm(), data->FD(), static_cast<int32_t>(data->Capacity()));

    if (_pool == nullptr)
    {
        delete data;
        return false;
    }

    wl_shm_pool_set_user_data(_pool, data);

    return true;
}

void ShmPool::Free()
{
    PoolData *data;

    data = reinterpret_cast<PoolData *>(wl_shm_pool_get_user_data(_pool));
    wl_shm_pool_destroy(_pool);
    delete data;
    _pool = nullptr;
}

} // namespace Wayland
