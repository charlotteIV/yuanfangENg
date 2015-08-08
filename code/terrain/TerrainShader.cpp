#include "TerrainShader.h"
#include "../GlobalVar.h"
#include "../camera/Camera.h"

#include <iostream>
using namespace std;

TerrainShader::TerrainShader(std::string vertexFile, std::string fragmentFile)
{
    InitShader(vertexFile, fragmentFile);
}

TerrainShader::~TerrainShader()
{

}

void TerrainShader::BindAllAttributes()
{
    BindAttribute(0, "position");           // BIND POSITION TO LOCATION 0
    BindAttribute(1, "textureCoords");      // BIND TEXTURE COORDINATE TO LOCATION 1
    BindAttribute(2, "normal");             // BIND NORMAL TO LOCATION 2
}

void TerrainShader::GetAllUniformLocations()
{
    AddUniformValue("transformMatrix");
    AddUniformValue("projectionMatrix");
    AddUniformValue("viewMatrix");
    AddUniformValue("shineDamper");
    AddUniformValue("reflectivity");
    AddUniformValue("skyColor");
    AddUniformValue("backgroundTexture");
    AddUniformValue("rTexture");
    AddUniformValue("gTexture");
    AddUniformValue("bTexture");
    AddUniformValue("blendMap");

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

void TerrainShader::ConnectTextureUnits()
{
    LoadInt(GetUniformLocations("backgroundTexture"), 0);
    LoadInt(GetUniformLocations("rTexture"), 1);
    LoadInt(GetUniformLocations("gTexture"), 2);
    LoadInt(GetUniformLocations("bTexture"), 3);
    LoadInt(GetUniformLocations("blendMap"), 4);
}

void TerrainShader::LoadSkyColor(GLfloat r, GLfloat g, GLfloat b)
{
    LoadVector3(GetUniformLocations("skyColor"), glm::vec3(r, g, b));
}

void TerrainShader::LoadShineVariables(GLfloat shineDamer, GLfloat reflectivity)
{
    LoadFloat(GetUniformLocations("shineDamper"), shineDamer);
    LoadFloat(GetUniformLocations("reflectivity"), reflectivity);
}

void TerrainShader::LoadLights(vector<Light> *lights)
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

void TerrainShader::LoadViewMatrix(Camera *camera)
{
    //cout<<"view::"<<GetUniformLocations("viewMatrix")<<endl;
    LoadMatrix(GetUniformLocations("viewMatrix"), camera->GetViewMatrix());
}

void TerrainShader::LoadTransformMatrix(const glm::mat4 &matrix)
{
    //cout<<"trans::"<<GetUniformLocations("transformMatrix")<<endl;
    LoadMatrix(GetUniformLocations("transformMatrix"), matrix);
}
