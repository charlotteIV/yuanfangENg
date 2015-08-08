#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "glew/glew.h"

class ModelTexture
{
public:
    ModelTexture(GLuint id);
    ~ModelTexture();

    // Retrieve texture id
    GLuint GetTextureID(){ return textureID; }

    // Set and Get numofRows
    void SetNumofRows(GLuint uiNumofRows);
    GLuint GetNumofRows(){ return uiNumofRows; }

    // Set and retrieve Shine damper
    void SetShineDamper(GLfloat shineDamper);
    GLfloat GetShineDamper() { return shineDamper; }

    // Set and retrieve Reflectivity
    void SetReflectivity(GLfloat reflectivity);
    GLfloat GetReflectivity() { return reflectivity; }

    // Set and retrieve transparency property
    void SetHasTransparency(bool hasTransparency);
    bool IsHasTransparency() { return hasTransparency; }

    // Set and retrieve fake lighting property
    void SetUseFakeLighing(bool useFakeLighting);
    bool IsUseFakeLighing() { return useFakeLighting; }

private:
    // Texture ID
    GLuint textureID;
    // texture atlases
    GLuint uiNumofRows;
    // shine damper
    GLfloat shineDamper;
    // the reflective ability
    GLfloat reflectivity;
    // Wether the texture is transparency or not
    bool hasTransparency;
    // Grass Lighting
    bool useFakeLighting;
};

#endif // MODELTEXTURE_H
