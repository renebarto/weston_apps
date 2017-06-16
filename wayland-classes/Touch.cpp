#include "Touch.h"

#include <cstdio>
//#include "ShmPool.h"
//#include "Surface.h"
//#include "Buffer.h"

using namespace Wayland;

static void TouchDown(void * data,
                      wl_touch * touch,
                      uint32_t serial,
                      uint32_t time,
                      wl_surface * surface,
                      int32_t id,
                      wl_fixed_t x,
                      wl_fixed_t y)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## touch_down(data %p, touch %p, serial %u, time %u, surface %p, id %d, X %d, Y %d)\n",
            data, touch, serial, time, surface, id, x, y);
#endif
    ITouchListener * listener = reinterpret_cast<ITouchListener *>(data);
    listener->OnTouchDown(touch, serial, time, surface, id, x, y);
}

static void TouchUp(void * data,
                    wl_touch * touch,
                    uint32_t serial,
                    uint32_t time,
                    int32_t id)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## touch_up(data %p, touch %p, serial %u, time %u, id %d)\n",
            data, touch, serial, time, id);
#endif
    ITouchListener * listener = reinterpret_cast<ITouchListener *>(data);
    listener->OnTouchUp(touch, serial, time, id);
}

static void TouchMotion(void * data,
                        wl_touch * touch,
                        uint32_t time,
                        int32_t id,
                        wl_fixed_t x,
                        wl_fixed_t y)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## touch_motion(data %p, touch %p, time %u, id %d, X %d, Y %d)\n",
            data, touch, time, id, x, y);
#endif
    ITouchListener * listener = reinterpret_cast<ITouchListener *>(data);
    listener->OnTouchMotion(touch, time, id, x, y);
}

static void TouchFrame(void * data,
                       wl_touch * touch)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## touch_frame(data %p, touch %p)\n",
            data, touch);
#endif
    ITouchListener * listener = reinterpret_cast<ITouchListener *>(data);
    listener->OnTouchFrame(touch);
}

static void TouchCancel(void * data,
                        wl_touch * touch)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## touch_cancel(data %p, touch %p)\n",
            data, touch);
#endif
    ITouchListener * listener = reinterpret_cast<ITouchListener *>(data);
    listener->OnTouchCancel(touch);
}

static const wl_touch_listener TouchListener = {
    .down = TouchDown,
    .up = TouchUp,
    .motion = TouchMotion,
    .frame = TouchFrame,
    .cancel = TouchCancel
};

Touch::Touch(wl_touch * touch)
    : _touch(touch)
{
}

Touch::~Touch()
{
    Reset();
    if (_touch)
        wl_touch_destroy(_touch);
    _touch = nullptr;
}

void Touch::AddListener(ITouchListener * listener)
{
    wl_touch_add_listener(_touch, &TouchListener, listener);
}

void Touch::Reset()
{
}

