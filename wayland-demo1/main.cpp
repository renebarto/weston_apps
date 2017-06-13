#include <fcntl.h>
#include <zconf.h>
#include <iostream>

#include "Registry.h"
#include "Display.h"

using namespace std;

int main(int argc, char * argv[])
{
    Wayland::Display display;

    if (!display.Setup())
        return EXIT_FAILURE;
    Wayland::Registry registry(display);
    registry.AddListener(&display);
    display.Roundtrip();

    cerr << "Exiting sample wayland client..." << endl;

    registry.Cleanup();
    display.Cleanup();

    return EXIT_SUCCESS;
}