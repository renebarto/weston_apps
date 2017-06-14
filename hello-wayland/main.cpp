#include <fcntl.h>
#include <zconf.h>
#include <iostream>
#include <wayland-client.h>
#include <ShmPool.h>
#include <Surface.h>
#include <Buffer.h>

#include "Application.h"
#include "Pointer.h"

using namespace std;

static const unsigned WIDTH = 320;
static const unsigned HEIGHT = 200;
static const unsigned CURSOR_WIDTH = 100;
static const unsigned CURSOR_HEIGHT = 59;
static const int32_t CURSOR_HOT_SPOT_X = 10;
static const int32_t CURSOR_HOT_SPOT_Y = 35;

static bool done = false;

void OnButtonPressed(uint32_t button)
{
    done = true;
}

int main(int argc, char * argv[])
{
    Wayland::Application app;
    if (!app.Setup())
        return EXIT_FAILURE;

    int image = open("images.bin", O_RDWR);

    if (image < 0)
    {
        cerr << "Error opening surface image" << endl;
        return EXIT_FAILURE;
    }

    Wayland::ShmPool pool;
    pool.Create(&app, image);
    Wayland::ShellSurface surface;
    surface.Create(app.GetCompositor(), app.GetShell());
    Wayland::Buffer buffer;
    buffer.Create(pool, WIDTH, HEIGHT);
    buffer.Bind(surface);
    Wayland::Pointer * pointer = app.GetPointer();
    if (!pointer->SetFromPool(app.GetCompositor(), pool, CURSOR_WIDTH, CURSOR_HEIGHT, CURSOR_HOT_SPOT_X, CURSOR_HOT_SPOT_Y))
    {
        cerr << "Error setting pointer" << endl;
        return EXIT_FAILURE;
    }

    surface.SetButtonCallback(OnButtonPressed);

    while (!done)
    {
        if (!app.Dispatch())
        {
            cerr << "Main loop error" << endl;
            done = true;
        }
    }

    cerr << "Exiting sample wayland client..." << endl;

    pointer->Reset();
    buffer.Free();
    surface.Destroy();
    pool.Free();
    close(image);

    app.Cleanup();

    return EXIT_SUCCESS;
}