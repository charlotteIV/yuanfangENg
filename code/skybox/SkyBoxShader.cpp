#include "SkyBoxShader.h"
#include "../camera/Camera.h"
#include <iostream>
using namespace std;

SkyBoxShader::SkyBoxShader(string vertexFile, string fragmentFile)
{
    InitShader(vertexFile, fragmentFile);
}


SkyBoxShader::~SkyBoxShader()
{

}

void SkyBoxShader::LoadViewMatrix(Camera *camera)
{
    glm::mat4 matrix = camera->GetViewMatrix();
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    LoadMatrix(GetUniformLocations("viewMatrix"), matrix);
}

void SkyBoxShader::BindAllAttributes()
{
    BindAttribute(0, "position");
}

void SkyBoxShader::GetAllUniformLocations()
{
    AddUniformValue("projectionMatrix");
    AddUniformValue("viewMatrix");
}
