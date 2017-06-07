#include <cstdlib>
#include <string>
#include <GL/glew.h>
#include "Application.h"
#include "Shader.h"

using namespace std;
using namespace OpenGL;

class App : public Application
{
public:
    App(int argc, char * argv[])
        : Application()
        , _argc(argc)
        , _argv(argv)
        , _applicationPath()
        , _programID()
        , _vertexPosition_modelSpaceID()
        , _vertexBuffer()
        , _offset()
    {
        _applicationPath = argv[0];
        size_t pathSeparatorIndex = _applicationPath.find_last_of("\\/");
        if (pathSeparatorIndex != string::npos)
            _applicationPath = _applicationPath.substr(0, pathSeparatorIndex);
    }
    bool SetupApplication() override
    {
        // Create and compile our GLSL program from the shaders
        _programID = LoadShaders("SimpleVertexShader.vertexshader",
                                 "SimpleFragmentShader.fragmentshader");
        if (!_programID)
            return false;

        // Get a handle for our buffers
        _vertexPosition_modelSpaceID = glGetAttribLocation(_programID, "vertexPosition_modelspace");
        glGenBuffers(1, &_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexBufferData), _vertexBufferData, GL_DYNAMIC_DRAW);
        return true;
    }
    void Draw() override
    {
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        // Use our shader
        glUseProgram(_programID);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(_vertexPosition_modelSpaceID);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

        _offset += 0.01F;
        if (_offset > 2.0F)
            _offset -= 2.0F;
        GLfloat vertexBuffer[9];
        int offset = 0;
        vertexBuffer[offset++] = -1.0F;
        vertexBuffer[offset++] = -1.0F + _offset;
        vertexBuffer[offset++] = 0.0F;
        vertexBuffer[offset++] = 1.0F;
        vertexBuffer[offset++] = -1.0F + _offset;
        vertexBuffer[offset++] = 0.0F;
        vertexBuffer[offset++] = 0.0F;
        vertexBuffer[offset++] = 1.0F;
        vertexBuffer[offset++] = 0.0F;
        glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexBufferData), vertexBuffer, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(
            _vertexPosition_modelSpaceID, // The attribute we want to configure
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(_vertexPosition_modelSpaceID);
    }
    
private:
    int _argc;
    char ** _argv;
    std::string _applicationPath;
    GLuint _programID;
    GLint _vertexPosition_modelSpaceID;
    GLuint _vertexBuffer;
    GLfloat _offset;
    static const GLfloat _vertexBufferData[9];
};

const GLfloat App::_vertexBufferData[] =
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

int main(int argc, char * argv[])
{
    App app(argc, argv);
    if (!app.Initialize())
        return EXIT_FAILURE;
    if (!app.Run())
        return EXIT_FAILURE;
    app.Terminate();
    return EXIT_SUCCESS;
}

