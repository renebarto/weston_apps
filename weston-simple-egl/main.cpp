/*
 * Copyright © 2011 Benjamin Franzke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include "Application.h"

//#include <stdint.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdbool.h>
//#include <math.h>
//#include <assert.h>

//#include <wayland-client.h>
//#include <wayland-egl.h>
//#include <wayland-cursor.h>
//
//#include <GLES2/gl2.h>
//#include <EGL/egl.h>
//#include <EGL/eglext.h>
//
//#include "protocol/xdg-shell-unstable-v6-client-protocol.h"
//#include "protocol/ivi-application-client-protocol.h"
#include "SignalHandler.h"

using namespace std;
using namespace Wayland;

static void Usage(int errorCode)
{
    cerr << "Usage: simple-egl [OPTIONS]" << endl << endl
         << "  -f\tRun in fullscreen mode" << endl
        << "  -o\tCreate an opaque surface" << endl
        << "  -s\tUse a 16 bpp EGL config" << endl
        << "  -b\tDon't sync to compositor redraw (eglSwapInterval 0)" << endl
        << "  -h\tThis help text" << endl << endl;

    exit(errorCode);
}

static void ParseArguments(int argc, char * argv[], Settings & settings)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp("-f", argv[i]) == 0)
            settings.fullScreen = true;
        else if (strcmp("-o", argv[i]) == 0)
            settings.opaque = true;
        else if (strcmp("-s", argv[i]) == 0)
            settings.bufferSize = 16;
        else if (strcmp("-b", argv[i]) == 0)
            settings.frameSync = false;
        else if (strcmp("-h", argv[i]) == 0)
            Usage(EXIT_SUCCESS);
        else
            Usage(EXIT_FAILURE);
    }
}

int main(int argc, char * argv[])
{
    Settings settings;
    ParseArguments(argc, argv, settings);
    Application app;
    if (!app.Setup(settings))
        return EXIT_FAILURE;

    SignalHandler signalHandler;

    app.Start();
    while (app.IsRunning())
    {
        if (signalHandler.CheckSignal(SIGINT))
        {
            cerr << "Signalling to stop (SIGINT)" << endl;
            app.Stop();
            continue;
        }
        if (!app.Dispatch())
        {
            cerr << "Main loop error" << endl;
            app.Stop();
        }
    }

    cerr << "Exiting " << argv[0] << "..." << endl;

    app.Cleanup();

    return EXIT_SUCCESS;
}
