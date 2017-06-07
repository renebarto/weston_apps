#include "Application.h"

#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>

using namespace std;
using namespace OpenGL;

Application::Application()
    : _window()
{
}

Application::~Application()
{

}

bool Application::Initialize()
{
    InitGLFW();

    CreateWindow();

    InitGLEW();

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    if (!SetupApplication())
        return false;

    return true;
}

bool Application::InitGLFW()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        Terminate();
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);                // 4x antialiasing
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);  // We want OpenGL 2.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
}

bool Application::CreateWindow()
{
    // Open a _window and create its OpenGL context
    _window = glfwCreateWindow(1024, 768, "Playground", nullptr, nullptr);
    if (_window == nullptr)
    {
        cerr << "Failed to open GLFW _window. If you have an Intel GPU, they are not 3.3 compatible. "
                "Try the 2.1 version of the tutorials." << endl;
        Terminate();
        return false;
    }
    glfwMakeContextCurrent(_window);
    return true;
}

bool Application::InitGLEW()
{
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        cerr << "Failed to initialize GLEW" << endl;
        Terminate();
        return false;
    }
}

bool Application::Run()
{
    do
    {
        // Draw nothing, see you in tutorial 2 !
        Draw();

        // Swap buffers
        glfwSwapBuffers(_window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the _window was closed
    while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(_window) == 0);
    return true;
}

void Application::Terminate()
{
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
