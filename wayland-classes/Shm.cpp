#include "Shm.h"

#include <wayland-client.h>
#include <wayland-cursor.h>
#include "Cursor.h"

using namespace Wayland;

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

CursorTheme * Shm::Load(const char * name, int size)
{
    wl_cursor_theme * theme = wl_cursor_theme_load(name, size, _shm);
    if (theme == nullptr)
        return nullptr;
    return new CursorTheme(theme);
}

