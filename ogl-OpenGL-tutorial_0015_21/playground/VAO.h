#pragma once

#include <GL/glew.h>

namespace OpenGL
{

class VAO
{
public:
    VAO()
        : _vertexArrayID()
    {
        glGenVertexArrays(1, &_vertexArrayID);
        glBindVertexArray(_vertexArrayID);
    }
    ~VAO()
    {
        glDeleteVertexArrays(1, &_vertexArrayID);
        _vertexArrayID = {};
    }
private:
    GLuint _vertexArrayID;
};

} // namespace OpenGL
