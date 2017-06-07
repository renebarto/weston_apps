#pragma once

#include <string>

class GLFWwindow;

namespace OpenGL
{

class Application
{
public:
    Application();
    virtual ~Application();

    bool Initialize();
    bool InitGLFW();
    bool CreateWindow();
    bool InitGLEW();
    virtual bool SetupApplication() { return true; }
    bool Run();
    virtual void Draw() {}
    void Terminate();

private:
    GLFWwindow * _window;
};

} // namespace OpenGL
