#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint id)
{
    this->textureID = id;
    this->uiNumofRows = 1;
    this->shineDamper = 1.0f;
    this->reflectivity = 0;

    this->hasTransparency = false;
    this->useFakeLighting = false;
}

ModelTexture::~ModelTexture()
{
    glDeleteTextures(1, &textureID);
}

void ModelTexture::SetNumofRows(GLuint uiNumofRows)
{
    this->uiNumofRows = uiNumofRows;
}

void ModelTexture::SetShineDamper(GLfloat shineDamper)
{
    this->shineDamper = shineDamper;
}

void ModelTexture::SetReflectivity(GLfloat reflectivity)
{
    this->reflectivity = reflectivity;
}

void ModelTexture::SetHasTransparency(bool hasTransparency)
{
    this->hasTransparency = hasTransparency;
}

void ModelTexture::SetUseFakeLighing(bool useFakeLighting)
{
    this->useFakeLighting = useFakeLighting;
}
