#include "ZXDGTopLevelV6.h"

#include <cstdio>
#include <wayland-client.h>
#include "Seat.h"
#include "protocol/xdg-shell-unstable-v6-client-protocol.h"
#include "IZXDGTopLevelV6Listener.h"

using namespace Wayland;

static void XDGTopLevelConfigure(void * data,
                                 zxdg_toplevel_v6 * toplevel,
                                 int32_t width,
                                 int32_t height,
                                 wl_array * states)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## xdg_toplevel_configure(data %p, toplevel %p, width %d, height %d, states %p)\n",
            data, toplevel, width, height, states);
#endif
    IZXDGTopLevelV6Listener * listener = reinterpret_cast<IZXDGTopLevelV6Listener *>(data);
    listener->OnXDGTopLevelConfigure(toplevel, width, height, states);
}

static void XDGTopLevelClose(void * data,
                             zxdg_toplevel_v6 * toplevel)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## xdg_toplevel_close(data %p, toplevel %p)\n",
            data, toplevel);
#endif
    IZXDGTopLevelV6Listener * listener = reinterpret_cast<IZXDGTopLevelV6Listener *>(data);
    listener->OnXDGTopLevelClose(toplevel);
}

static const zxdg_toplevel_v6_listener ZXDGTopLevelV6Listener = {
    .configure = XDGTopLevelConfigure,
    .close = XDGTopLevelClose
};

ZXDGTopLevelV6::ZXDGTopLevelV6(zxdg_toplevel_v6 * toplevel)
    : _toplevel(toplevel)
{
}

ZXDGTopLevelV6::~ZXDGTopLevelV6()
{
    Cleanup();
}

void ZXDGTopLevelV6::AddListener(IZXDGTopLevelV6Listener * listener)
{
    zxdg_toplevel_v6_add_listener(_toplevel, &ZXDGTopLevelV6Listener, listener);
}

void ZXDGTopLevelV6::Cleanup()
{
    if (_toplevel)
        zxdg_toplevel_v6_destroy(_toplevel);
    _toplevel = nullptr;
}

void ZXDGTopLevelV6::SetTitle(const char *title)
{
    zxdg_toplevel_v6_set_title(_toplevel, title);
}

void ZXDGTopLevelV6::SetFullScreen()
{
    zxdg_toplevel_v6_set_fullscreen(_toplevel, nullptr);
}

void ZXDGTopLevelV6::UnsetFullScreen()
{
    zxdg_toplevel_v6_unset_fullscreen(_toplevel);
}

void ZXDGTopLevelV6::Move(Seat * seat, uint32_t serial)
{
    zxdg_toplevel_v6_move(_toplevel, seat->Get(), serial);
}