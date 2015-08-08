#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include "../shaders/ShaderProgram.h"

class Camera;

class SkyBoxShader : public ShaderProgram
{
public:
    SkyBoxShader(string vertexFile, string fragmentFile);
    ~SkyBoxShader();

    // Load view matrix without translation
    // only apply rotation
    void LoadViewMatrix(Camera *camera);

protected:
    void BindAllAttributes();
    void GetAllUniformLocations();

};

#endif // SKYBOXSHADER_H
