#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "../shaders/ShaderProgram.h"

class Light;
class Camera;
class StaticShader : public ShaderProgram
{
public:
    StaticShader(string vertexFile, string fragmentFile);
    ~StaticShader();

    // Send transform matrix to shader
    void LoadTransformMatrix(const glm::mat4 &matrix);

    // Send view matrix
    void LoadViewMatrix(Camera *camera);

    // Send light position, color and other propetries
    void LoadLights(vector<Light> *lights);

    // Send light Shiness
    void LoadShineVariables(GLfloat shineDamer, GLfloat reflectivity);

    // Send Fake lighting boolean
    void LoadFakeLighting(bool useFake);

    // Send Sky Color
    void LoadSkyColor(GLfloat r, GLfloat g, GLfloat b);

    // Send number of row of the ued textures
    void LoadNumberOfRows(GLuint numberOfRows);

    // Send texture coordinate offset
    void LoadOffset(GLfloat x, GLfloat y);

protected:
    ///////////////////////////////////////////////////////////////////////////////////////////////
    /// \! Each shader sub-class must override these two virtual functions
    // Bind Attributes, like position, normal and texture
    void BindAllAttributes();
    // Retrieve uniform location
    void GetAllUniformLocations();
};

#endif // STATICSHADER_H
