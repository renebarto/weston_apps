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

using namespace std;

namespace Wayland
{

class Surface
{

};

}

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
    struct wl_buffer *buffer;
    struct wl_shell_surface *surface;
    int image;

    Wayland::Display display;

    display.Setup();

    image = open("images.bin", O_RDWR);

    if (image < 0)
    {
        cerr << "Error opening surface image" << endl;
        return EXIT_FAILURE;
    }

    Wayland::ShmPool pool;
    pool.Create(image);
    surface = hello_create_surface();
    buffer = hello_create_buffer(pool.Get(), WIDTH, HEIGHT);
    hello_bind_buffer(buffer, surface);
    hello_set_cursor_from_pool(pool.Get(), CURSOR_WIDTH,
                               CURSOR_HEIGHT, CURSOR_HOT_SPOT_X, CURSOR_HOT_SPOT_Y);
    hello_set_button_callback(surface, on_button);

    while (!done)
    {
        if (!display.Dispatch())
        {
            cerr << "Main loop error" << endl;
            done = true;
        }
    }

    cerr << "Exiting sample wayland client..." << endl;

    hello_free_cursor();
    hello_free_buffer(buffer);
    hello_free_surface(surface);
    pool.Free();
    close(image);

    display.Cleanup();

    return EXIT_SUCCESS;
}