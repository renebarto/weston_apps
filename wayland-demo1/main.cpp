#include <iostream>
#include "Application.h"

using namespace std;

int main(int argc, char * argv[])
{
    Wayland::Application app;
    if (!app.Setup())
        return EXIT_FAILURE;

    cerr << "Exiting sample wayland client..." << endl;

    app.Cleanup();

    return EXIT_SUCCESS;
}