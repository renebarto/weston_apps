#pragma once

#include <cstddef>
#include <wayland-client.h>

namespace Wayland
{

using pixel = uint32_t;

class ShmPool
{
public:
    class PoolData
    {
    public:
        PoolData() {}
        bool Create(size_t size, int fd);
        ~PoolData();

        int FD() const { return _fd; }
        size_t Capacity() const { return _capacity; }
    private:
        int _fd;
        pixel * _memory;
        size_t _capacity;
        int _size;
    };
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

private:
    wl_shm_pool * _pool;
};

} // namespace Wayland
