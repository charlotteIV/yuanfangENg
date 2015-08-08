#include "ShaderProgram.h"
#include <iostream>
#include "Shader.h"
#include "../camera/Camera.h"
#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram(string vertexFile, string fragmentFile)
{
    InitShader(vertexFile, fragmentFile);
}

ShaderProgram::~ShaderProgram(){
    Stop();
    glDetachShader(programID, vertexShader->GetShaderID());
    glDetachShader(programID, fragmentShader->GetShaderID());
    glDeleteShader(vertexShader->GetShaderID());
    glDeleteShader(fragmentShader->GetShaderID());
    glDeleteProgram(programID);

    delete vertexShader;
    delete fragmentShader;
}

void ShaderProgram::AddUniformValue(string uniformName)
{
    // Determine if the uniform value has been added
    if(m_uniformVar.find(uniformName)!=m_uniformVar.end())
        return;
    // if not, add it
    else{
        GLuint loc = glGetUniformLocation(programID, uniformName.c_str());
        m_uniformVar.insert(pair<string, GLuint>(uniformName, loc));
    }
}

GLuint ShaderProgram::GetUniformLocations(string uniformName)
{
    // Exsisted
    if(m_uniformVar.find(uniformName) != m_uniformVar.end())
        return m_uniformVar[uniformName];
    // Not exsisted, add and then return
    else{
        GLuint loc = glGetUniformLocation(programID, uniformName.c_str());
        m_uniformVar.insert(pair<string, GLuint>(uniformName, loc));
        return loc;
    }
}

void ShaderProgram::LoadProjectionMatrix(GLuint location)
{
    LoadMatrix(location, Camera::GetProjMatrix());
}

void ShaderProgram::InitShader(string vertexFile, string fragmentFile)
{
    // Create vertex shader
    vertexShader = new Shader(GL_VERTEX_SHADER, vertexFile);

    // Create fragment shader
    fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentFile);

    /* Shader program*/
    programID = glCreateProgram();

    /* Attach and link */
    glAttachShader(programID, vertexShader->GetShaderID());
    glAttachShader(programID, fragmentShader->GetShaderID());

    // BIND ATTRib
    BindAllAttributes();

    // LINK and VALIDATE
    glLinkProgram(programID);
    glValidateProgram(programID);

    /* Check for any error */
    GLint status;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    if(status == 0){
        GLchar infoLog[512];
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout<<"SHADER PROGRAM LINK FAILED\n"
                <<infoLog<<std::endl;
        exit(5);
    }

    // Get uniform location
    GetAllUniformLocations();
}

void ShaderProgram::BindAttribute(GLuint attribute, string variableName)
{
    glBindAttribLocation(programID, attribute, variableName.c_str());
}

//GLuint ShaderProgram::GetUniformLocation(string uniformName)
//{
//    return glGetUniformLocation(programID, uniformName.c_str());
//}

void ShaderProgram::LoadInt(GLuint location, GLint value)
{
    glUniform1i(location, value);
}

void ShaderProgram::LoadBool(GLuint location, bool value)
{
    GLfloat toFloat = 0;
    if(value){
        toFloat = 1;
    }
    glUniform1f(location, toFloat);
}

void ShaderProgram::LoadFloat(GLuint location, GLfloat value)
{
    glUniform1f(location, value);
}

void ShaderProgram::LoadVector3(GLuint location, glm::vec3 vector)
{
    glUniform3f(location, vector.x ,vector.y, vector.z);
}

void ShaderProgram::LoadVector2(GLuint location, glm::vec2 vector)
{
    glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::LoadMatrix(GLuint location, const glm::mat4 &value)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
