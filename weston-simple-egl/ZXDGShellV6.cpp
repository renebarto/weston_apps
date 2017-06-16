#include "ZXDGShellV6.h"

#include <cstdio>
#include <wayland-client.h>
#include "protocol/xdg-shell-unstable-v6-client-protocol.h"
#include "IZXDGShellV6Listener.h"

using namespace Wayland;

static void XDGShellPing(void * data,
                         zxdg_shell_v6 * shell, uint32_t serial)
{
#ifdef WAYLAND_CLASSES_DEBUG
    fprintf(stderr, "## xdg_shell_ping(data %p, shell %p, serial %u)\n",
            data, shell, serial);
#endif
    IZXDGShellV6Listener * listener = reinterpret_cast<IZXDGShellV6Listener *>(data);
    listener->OnXDGShellPing(shell, serial);
}

static const zxdg_shell_v6_listener ZXDGShellV6Listener = {
    .ping = XDGShellPing
};

ZXDGShellV6::ZXDGShellV6(zxdg_shell_v6 * shell)
    : _shell(shell)
{
}

ZXDGShellV6::~ZXDGShellV6()
{
    Cleanup();
}

void ZXDGShellV6::AddListener(IZXDGShellV6Listener * listener)
{
    zxdg_shell_v6_add_listener(_shell, &ZXDGShellV6Listener, listener);
}

void ZXDGShellV6::Cleanup()
{
    if (_shell)
        zxdg_shell_v6_destroy(_shell);
    _shell = nullptr;
}
