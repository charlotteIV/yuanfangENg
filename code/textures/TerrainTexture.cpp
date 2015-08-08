#include "TerrainTexture.h"

TerrainTexture::TerrainTexture(GLuint textureID)
{
    this->textureID = textureID;
}

TerrainTexture::~TerrainTexture()
{
    glDeleteTextures(1, &textureID);
}
