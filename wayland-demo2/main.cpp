#include <fcntl.h>
#include <zconf.h>
#include <iostream>

#include "Registry.h"
#include "Display.h"
#include "Surface.h"

using namespace std;

static bool done = false;

void OnButtonPressed(uint32_t button)
{
    done = true;
}

int main(int argc, char * argv[])
{
    Wayland::Display display;

    if (!display.Setup())
        return EXIT_FAILURE;
    Wayland::Registry registry(display);
    registry.AddListener(&display);
    display.Roundtrip();
    Wayland::ShellSurface surface;
    surface.Create(Wayland::Display::Compositor(), Wayland::Display::Shell());

    surface.SetButtonCallback(OnButtonPressed);

    while (!done)
    {
        if (!display.Dispatch())
        {
            cerr << "Main loop error" << endl;
            done = true;
        }
    }

    cerr << "Exiting sample wayland client..." << endl;

    surface.Destroy();
    registry.Cleanup();
    display.Cleanup();

    return EXIT_SUCCESS;
}