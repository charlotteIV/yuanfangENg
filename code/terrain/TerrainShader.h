#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include "../shaders/ShaderProgram.h"
#include "../camera/FreeCamera.h"
#include "../graphic/Light.h"

#include <vector>
using std::vector;

class TerrainShader : public ShaderProgram
{
public:
    TerrainShader(string vertexFile, string fragmentFile);
    ~TerrainShader();

    void LoadTransformMatrix(const glm::mat4 &matrix);

    void LoadViewMatrix(Camera *camera);

    void LoadLights(vector<Light> *lights);

    void LoadShineVariables(GLfloat shineDamer, GLfloat reflectivity);

    void LoadSkyColor(GLfloat r, GLfloat g, GLfloat b);

    void ConnectTextureUnits();

protected:
    ///////////////////////////////////////////////////////////////////////////////////////////////
    /// \! Each shader sub-class must override these two virtual functions
    // Bind Attributes, like position, normal and texture
    void BindAllAttributes();
    // Retrieve uniform location
    void GetAllUniformLocations();
};

#endif // TERRAINSHADER_H
