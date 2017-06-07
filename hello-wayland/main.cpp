#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <zconf.h>
#include <iostream>
#include <wayland-client.h>
#include "helpers.h"

#include "Registry.h"
#include "Display.h"
#include "ShmPool.h"
#include "Surface.h"
#include "Buffer.h"
#include "Pointer.h"

using namespace std;

static const unsigned WIDTH = 320;
static const unsigned HEIGHT = 200;
static const unsigned CURSOR_WIDTH = 100;
static const unsigned CURSOR_HEIGHT = 59;
static const int32_t CURSOR_HOT_SPOT_X = 10;
static const int32_t CURSOR_HOT_SPOT_Y = 35;

static bool done = false;

void on_button(uint32_t button)
{
    done = true;
}

int main(int argc, char * argv[])
{
    Wayland::Display display;

    if (!display.Setup())
        return EXIT_FAILURE;

    int image = open("images.bin", O_RDWR);

    if (image < 0)
    {
        cerr << "Error opening surface image" << endl;
        return EXIT_FAILURE;
    }

    Wayland::ShmPool pool;
    pool.Create(image);
    Wayland::ShellSurface surface;
    surface.Create(Wayland::Display::Compositor(), Wayland::Display::Shell());
    Wayland::Buffer buffer;
    buffer.Create(pool, WIDTH, HEIGHT);
    buffer.Bind(surface);
    Wayland::Pointer pointer(display.Pointer());
    if (!pointer.SetFromPool(display.Compositor(), pool, CURSOR_WIDTH, CURSOR_HEIGHT, CURSOR_HOT_SPOT_X, CURSOR_HOT_SPOT_Y))
    {
        cerr << "Error setting pointer" << endl;
        return EXIT_FAILURE;
    }

    surface.SetButtonCallback(on_button);

    while (!done)
    {
        if (!display.Dispatch())
        {
            cerr << "Main loop error" << endl;
            done = true;
        }
    }

    cerr << "Exiting sample wayland client..." << endl;

    pointer.Release();
    buffer.Free();
    surface.Destroy();
    pool.Free();
    close(image);

    display.Cleanup();

    return EXIT_SUCCESS;
}