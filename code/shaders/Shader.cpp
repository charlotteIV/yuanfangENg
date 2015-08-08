#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(GLuint type, string filename)
{
    LoadShader(type, filename);
}

Shader::~Shader()
{
    glDeleteShader(shaderID);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief ShaderProgram::LoadShader
/// \param type : GLSL shader tye, GL_VERTEX_SHADER | GL_FRAGMENT_SHADER
/// \param filename : GLSL shader file
/// \return
///
void Shader::LoadShader(GLuint type, string filename)
{
    // Create shader
    shaderID = glCreateShader(type);

    /********************************************************************************/
    /* Parse the shader file */
    std::string shaderSource;
    /* read file on the disk*/
    try{
        // Open file
        std::ifstream shaderFileStream(filename);
        std::stringstream shaderStream;

        if(shaderFileStream.fail()){
            std::cout<<"CANNOT OPEN THE SHADER FILE:"<<filename<<"!"<<std::endl;
            exit(1);
        }

        // Read file’s buffer contents into streams
        shaderStream<<shaderFileStream.rdbuf();
        // Close file handle
        shaderFileStream.close();

        // Convert stream into GLchar array
        shaderSource = shaderStream.str();

    }catch(std::exception e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" <<
                     std::endl;
    }
    /* finished parsing file */
    const char *shaderSourceArray = shaderSource.c_str();
    glShaderSource(shaderID, 1, &shaderSourceArray, NULL);
    /********************************************************************************/

    // BUILD AND VERIFY
    glCompileShader(shaderID);
    GLint status;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if(0 == status){
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);

        GLchar* shaderT = (type == GL_VERTEX_SHADER ) ? "VERTEX" : "FRAGMENT";
        std::cout<<"ERROR::"<<shaderT
                <<"::SHADER: compilation failed\n"<<infoLog<<std::endl;

        exit(4);
    }
}
