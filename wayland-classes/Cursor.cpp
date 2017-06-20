#include "Cursor.h"

#include <cassert>
#include <cstdio>
#include <wayland-cursor.h>
#include "Shm.h"

using namespace Wayland;

Cursor::Cursor(wl_cursor * cursor)
    : _cursor(cursor)
{
}

Cursor::~Cursor()
{
    Cleanup();
}

wl_cursor_image * Cursor::GetImage(int index)
{
    assert(index >=0 && index < _cursor->image_count);
    return _cursor->images[index];
}

void Cursor::Cleanup()
{
}

CursorTheme::CursorTheme(wl_cursor_theme * theme)
    : _theme(theme)
{
}

CursorTheme::~CursorTheme()
{
    Cleanup();
}

void CursorTheme::Cleanup()
{
    if (_theme)
        wl_cursor_theme_destroy(_theme);
    _theme = nullptr;
}

Cursor * CursorTheme::GetCursor(const char *name)
{
    wl_cursor * cursor = wl_cursor_theme_get_cursor(_theme, name);
    if (cursor == nullptr)
        return nullptr;
    return new Cursor(cursor);
}