#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include <GL/glew.h>

#include "Shader.h"

using namespace std;

GLuint OpenGL::LoadShaders(const string & vertexFilePath, const string & fragmentFilePath)
{
    // Create the shaders
    GLuint vertexSharedID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Read the Vertex Shader code from the file
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
    if (vertexShaderStream.is_open())
    {
        std::string line = "";
        while(getline(vertexShaderStream, line))
            vertexShaderCode += "\n" + line;
        vertexShaderStream.close();
    }
    else
    {
        cout << "Impossible to open " << vertexFilePath << ". Are you in the right directory ? Don't forget to read the FAQ !" << endl;
        return 0;
    }
    
    // Read the Fragment Shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
    if(fragmentShaderStream.is_open())
    {
        std::string line = "";
        while(getline(fragmentShaderStream, line))
            fragmentShaderCode += "\n" + line;
        fragmentShaderStream.close();
    }
    
    GLint result = GL_FALSE;
    int infoLogLength;
    
    // Compile Vertex Shader
    cout << "Compiling shader : " << vertexFilePath << endl;
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexSharedID, 1, &vertexSourcePointer, nullptr);
    glCompileShader(vertexSharedID);
    
    // Check Vertex Shader
    glGetShaderiv(vertexSharedID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexSharedID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(static_cast<size_t>(infoLogLength + 1));
        glGetShaderInfoLog(vertexSharedID, infoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        cout << &VertexShaderErrorMessage[0] << endl;
    } 
    
    // Compile Fragment Shader
    cout << "Compiling shader : " << fragmentFilePath << endl;
    char const * FragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer , nullptr);
    glCompileShader(fragmentShaderID);
    
    // Check Fragment Shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> fragmentShaderErrorMessage(static_cast<size_t>(infoLogLength + 1));
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, nullptr, &fragmentShaderErrorMessage[0]);
        cout << &fragmentShaderErrorMessage[0] << endl;
    }
        
    // Link the program
    cout << "Linking program" << endl;
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexSharedID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    
    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(static_cast<size_t>(infoLogLength + 1));
        glGetProgramInfoLog(programID, infoLogLength, nullptr, &ProgramErrorMessage[0]);
        cout << &ProgramErrorMessage[0] << endl;
    }

    // After linking program, shaders can be removed.
    glDetachShader(programID, vertexSharedID);
    glDetachShader(programID, fragmentShaderID);
    
    glDeleteShader(vertexSharedID);
    glDeleteShader(fragmentShaderID);
    
    return programID;
}
