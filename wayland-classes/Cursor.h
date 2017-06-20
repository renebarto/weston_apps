#pragma once

#include <wayland-client.h>

struct wl_cursor;
struct wl_cursor_image;
struct wl_cursor_theme;

namespace Wayland
{

class Shm;

class Cursor
{
public:
    Cursor(wl_cursor * cursor);
    ~Cursor();

    wl_cursor * Get() { return _cursor; }
    wl_cursor_image * GetImage(int index);
    void Cleanup();

private:
    wl_cursor * _cursor;
};

class CursorTheme
{
public:
    CursorTheme(wl_cursor_theme * theme);
    ~CursorTheme();

    void Cleanup();

    Cursor * GetCursor(const char *name);

private:
    wl_cursor_theme * _theme;
};

} // namespace Wayland
