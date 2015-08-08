#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <map>
#include <string>
#include <vector>
using namespace std;

#include "glew/glew.h"
#include "glm/glm.hpp"

class Shader;

class ShaderProgram
{
public:
    ShaderProgram() {}

    ShaderProgram(string vertexFile, string fragmentFile);
    virtual ~ShaderProgram();

    // Bind and release the shader program
    void Start() { glUseProgram(programID); }
    void Stop()  { glUseProgram(0); }

    // Add one uniform to uniform map
    void AddUniformValue(string uniformName);

    // Retrieve uniform value location
    GLuint GetUniformLocations(string uniformName);

    // Load projection matrix
    virtual void LoadProjectionMatrix(GLuint location);

    // Bind Atributes
    void BindAttribute(GLuint attribute, string variableName);

protected:
    /////////////////////////////////////////////////////////////////////////////////////
    ///\! Virtual function, should override in its sub-class
    // Bind Attributes
    virtual void BindAllAttributes() {}
    // Get Uniform location here
    virtual void GetAllUniformLocations() {}

    // Initialize shaders and program
    void InitShader(string vertexFile, string fragmentFile);

    /////////////////////////////////////////////////////////////////////////////////////
    // Assign int
    void LoadInt(GLuint location, GLint value);
    // Assign boolean
    void LoadBool(GLuint location, bool value);
    // Assign float
    void LoadFloat(GLuint location, GLfloat value);
    // Assign Matrix
    void LoadMatrix(GLuint location, const glm::mat4 &value);
    // Assign vector2D
    void LoadVector2(GLuint location, glm::vec2 vector);
    // Assign vector3D
    void LoadVector3(GLuint location, glm::vec3 vector);

private:
    // program id
    GLuint programID;
    Shader *vertexShader;
    Shader *fragmentShader;

    // Map between uniform name and its location in shaders
    map<string, GLuint> m_uniformVar;
};

#endif // SHADERPROGRAM_H
