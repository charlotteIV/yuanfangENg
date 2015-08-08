#ifndef SHADER_H
#define SHADER_H

#include <string>
using namespace std;

#include "glew/glew.h"

class Shader
{
public:
    Shader(GLuint type, string filename);
    ~Shader();

    GLuint GetShaderID() { return shaderID; }

private:
    // Loader shader from file
    void LoadShader(GLuint type, string filename);

    GLuint shaderID;
};

#endif // SHADER_H
