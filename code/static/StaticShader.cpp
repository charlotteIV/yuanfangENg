#include "StaticShader.h"
#include "../GlobalVar.h"
#include "../graphic/Light.h"
#include "../camera/Camera.h"
#include <iostream>
using namespace std;

StaticShader::StaticShader(string vertexFile, string fragmentFile)
{
    InitShader(vertexFile, fragmentFile);
}

StaticShader::~StaticShader()
{

}

// !Override virtual function, call in the constructor
void StaticShader::BindAllAttributes()
{
    BindAttribute(0, "position");           // BIND POSITION TO LOCATION 0
    BindAttribute(1, "textureCoords");      // BIND TEXTURE COORDINATE TO LOCATION 1
    BindAttribute(2, "normal");             // BIND NORMAL TO LOCATION 2
}

// !Override virtual function, call in the constructor
void StaticShader::GetAllUniformLocations()
{
    ///////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief All uniform values should be binded HERE before using

    AddUniformValue("transformMatrix");
    AddUniformValue("projectionMatrix");
    AddUniformValue("viewMatrix");
    AddUniformValue("shineDamper");
    AddUniformValue("reflectivity");
    AddUniformValue("useFakeLighting");
    AddUniformValue("skyColor");
    AddUniformValue("numberOfRows");
    AddUniformValue("offset");

    // Get light and color location
    for(GLuint i=0; i<GlobalVar::MAX_LIGHTS; ++i){
        char ch[6];
        sprintf_s(ch,"%d",i);
        string strUniform = "lightPosition[" + string(ch) + ']';
        AddUniformValue(strUniform);
        strUniform = "lightColor[" + string(ch) + ']';
        AddUniformValue(strUniform);
        strUniform = "attenuation[" + string(ch) + ']';
        AddUniformValue(strUniform);
    }
}

void StaticShader::LoadTransformMatrix(const glm::mat4 &matrix)
{
    LoadMatrix(GetUniformLocations("transformMatrix"), matrix);
}

void StaticShader::LoadViewMatrix(Camera *camera)
{
    LoadMatrix(GetUniformLocations("viewMatrix"), camera->GetViewMatrix());
}

void StaticShader::LoadLights(vector<Light> *lights)
{
    for(GLuint i=0; i<GlobalVar::MAX_LIGHTS; ++i){
        char ch[6];
        sprintf_s(ch,"%d",i);
        string strUniform = "lightPosition[" + string(ch) + ']';
        if(i < lights->size()){
            // Postion
            LoadVector3(GetUniformLocations(strUniform), (*lights)[i].GetPosition());
            // Color
            strUniform = "lightColor[" + string(ch) + ']';
            LoadVector3(GetUniformLocations(strUniform), (*lights)[i].GetColor());
            // attenuation
            strUniform = "attenuation[" + string(ch) + ']';
            LoadVector3(GetUniformLocations(strUniform), (*lights)[i].GetAttenuation());
        }else{
            LoadVector3(GetUniformLocations(strUniform), glm::vec3(0.0f));
            strUniform = "lightColor[" + string(ch) + ']';
            LoadVector3(GetUniformLocations(strUniform), glm::vec3(0.0f));
            strUniform = "attenuation[" + string(ch) + ']';
            LoadVector3(GetUniformLocations(strUniform), glm::vec3(1.0f, 0.0f,0.0f));
        }
    }
}

void StaticShader::LoadShineVariables(GLfloat shineDamer, GLfloat reflectivity)
{
    LoadFloat(GetUniformLocations("shineDamper"), shineDamer);
    LoadFloat(GetUniformLocations("reflectivity"), reflectivity);
}

void StaticShader::LoadFakeLighting(bool useFake)
{
    LoadFloat(GetUniformLocations("useFakeLighting"), useFake);
}

void StaticShader::LoadSkyColor(GLfloat r, GLfloat g, GLfloat b)
{
    LoadVector3(GetUniformLocations("skyColor"), glm::vec3(r, g, b));
}

void StaticShader::LoadNumberOfRows(GLuint numberOfRows)
{
    LoadFloat(GetUniformLocations("numberOfRows"), (GLfloat)numberOfRows);
}

void StaticShader::LoadOffset(GLfloat x, GLfloat y)
{
    LoadVector2(GetUniformLocations("offset"), glm::vec2(x, y));
}

