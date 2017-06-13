#pragma once

#include <cstddef>
#include <wayland-client.h>

namespace Wayland
{

using pixel = uint32_t;

class PoolData
{
public:
    PoolData();
    bool Create(size_t size, int fd);
    ~PoolData();

    int FD() const { return _fd; }
    size_t Capacity() const { return _capacity; }
    size_t & Size() { return _size; }

private:
    int _fd;
    pixel * _memory;
    size_t _capacity;
    size_t _size;
};

class ShmPool
{
public:
public:
    ShmPool()
        : _pool()
    {}
    ~ShmPool()
    {
        if (_pool != nullptr)
            Free();
    }

    bool Create(int fd);
    void Free();
    wl_shm_pool * Get() const { return _pool; }

    wl_buffer * CreateBuffer(unsigned width, unsigned height, uint32_t format);

private:
    wl_shm_pool * _pool;
};

} // namespace Wayland
