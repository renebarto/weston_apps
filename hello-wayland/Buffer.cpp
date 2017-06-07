#include "Buffer.h"
#include "ShmPool.h"

using namespace Wayland;

Buffer::Buffer()
    : _buffer()
{
}

Buffer::~Buffer()
{
    if (_buffer != nullptr)
        Free();
}

static const uint32_t PIXEL_FORMAT_ID = WL_SHM_FORMAT_ARGB8888;

bool Buffer::Create(ShmPool & pool,
                    unsigned width, unsigned height)
{
    _buffer = pool.CreateBuffer(width, height, PIXEL_FORMAT_ID);
    if (_buffer == nullptr)
        return false;

    return true;
}

void Buffer::Free()
{
    wl_buffer_destroy(_buffer);
    _buffer = nullptr;
}

void Buffer::Bind(ShellSurface & shellSurface)
{
    Surface * surface = shellSurface.GetSurface();
    surface->Attach(_buffer);
    surface->Commit();
}
