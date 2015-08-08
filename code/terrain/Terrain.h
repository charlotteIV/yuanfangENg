#ifndef TERRAIN_H
#define TERRAIN_H

#include "glew/glew.h"
#include "glm/glm.hpp"

class Loader;
class RawModel;
class TerrainTexture;
class TerrainTexturePack;

class Terrain
{
public:
    Terrain(GLint gridX, GLint gridZ, TerrainTexturePack *texture, TerrainTexture* blendMap);
    ~Terrain();

    GLfloat GetX() const { return x; }
    GLfloat GetZ() const { return z; }

    RawModel *GetRawModel() const { return model; }

    // get the terrain height of specific location
    GLfloat GetTerrainHeight(GLfloat worldX, GLfloat worldZ);

    // Retrieve blend map
    TerrainTexture* GetBlendMap() const { return blendMap; }

    // Retrieve Terrain texture pack
    TerrainTexturePack *GetTexturePack() const { return texture; }

private:
    GLfloat x;
    GLfloat z;

    // heights[x][y]
    GLfloat **fTerrainHeights;
    // The number of vertices on the edge
    GLuint uiVerticesCount;

    RawModel *model;
    TerrainTexture *blendMap;
    TerrainTexturePack *texture;

    // Get the Height of the HeightMap
    GLfloat GetHeight(GLuint x, GLuint z, GLubyte *data);

    // Calculate normal of the pixel(x,y)
    glm::vec3 CalculateNormal(GLuint x, GLuint z, GLubyte *data);

    // Generate funtion
    RawModel *GenerateTerrain(const GLchar* heightmap=0);

    const static GLuint SIZE = 800;
    const static GLuint MAX_HEIGHT = 40;
    const static GLuint MAX_PIXEL_COLOR_HALF = 16777216 / 2;
};

#endif // TERRAIN_H
