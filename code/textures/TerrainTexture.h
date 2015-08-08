#ifndef TERRAINTEXTURE_H
#define TERRAINTEXTURE_H

#include "glew/glew.h"

class TerrainTexture
{
public:
    TerrainTexture(GLuint textureID);
    ~TerrainTexture();

    // Retrieve texture id
    GLuint GetTextureID(){ return textureID; }

private:
    GLuint textureID;
};

#endif // TERRAINTEXTURE_H
