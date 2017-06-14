#include "ShmPool.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include "../wayland-demo1/Application.h"

namespace Wayland
{

PoolData::PoolData()
    : _fd()
    , _memory()
    , _capacity()
    , _size()
{
}

bool PoolData::Create(size_t size, int fd)
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

PoolData::~PoolData()
{
    munmap(_memory, _capacity);
    _capacity = {};
    _size = {};
    _fd = {};
    _memory = {};
}

bool ShmPool::Create(Application * app, int fd)
{
    struct stat stat;

    if (fstat(fd, &stat) != 0)
        return NULL;

    PoolData * data = new PoolData();

    if (!data->Create(static_cast<size_t>(stat.st_size), fd))
    {
        delete data;
        return false;
    }

    _pool = wl_shm_create_pool(app->GetShm(), data->FD(), static_cast<int32_t>(data->Capacity()));

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
    PoolData * data = reinterpret_cast<PoolData *>(wl_shm_pool_get_user_data(_pool));
    wl_shm_pool_destroy(_pool);
    delete data;
    _pool = nullptr;
}

wl_buffer * ShmPool::CreateBuffer(unsigned width, unsigned height, uint32_t format)
{
    PoolData * data = reinterpret_cast<PoolData *>(wl_shm_pool_get_user_data(_pool));
    wl_buffer *buffer = wl_shm_pool_create_buffer(_pool, data->Size(), width, height,
                                                  width*sizeof(pixel), format);

    if (buffer == nullptr)
        return nullptr;

    data->Size() += width*height*sizeof(pixel);

    return buffer;
}

} // namespace Wayland
