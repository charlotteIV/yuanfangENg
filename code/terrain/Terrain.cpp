#include "Terrain.h"
#include "soil.h"
#include "../toolbox/Maths.h"
#include "../toolbox/Loader.h"
#include "../textures/TerrainTexture.h"
#include "../textures/TerrainTexturePack.h"
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

Terrain::Terrain(GLint gridX, GLint gridZ, TerrainTexturePack *texture, TerrainTexture* blendMap)
{
    this->fTerrainHeights = NULL;
    this->x = (GLfloat)gridX * SIZE;
    this->z = (GLfloat)gridZ * SIZE;
    this->texture = texture;
    this->blendMap = blendMap;

    this->model = GenerateTerrain("../res/images/heightmap.png");
}

Terrain::~Terrain()
{
    if(fTerrainHeights != NULL){
        for(GLuint i=0; i<uiVerticesCount; ++i){
            delete fTerrainHeights[i];
        }
        delete fTerrainHeights;
        //cout<<"Release terrain heights correctly!"<<endl;
    }
}

GLfloat Terrain::GetTerrainHeight(GLfloat worldX, GLfloat worldZ)
{
    GLfloat fTerrainX = worldX - this->x;
    GLfloat fTerrainZ = worldZ - this->z;

    GLfloat gridSquareSize = SIZE / (GLfloat)(uiVerticesCount-1);
    GLint gridX = (GLint)(fTerrainX / gridSquareSize);
    GLint gridZ = (GLint)(fTerrainZ / gridSquareSize);
    if(gridX >= (GLint)(uiVerticesCount-1) || gridZ >= (GLint)(uiVerticesCount-1) || gridX<=0 || gridZ<=0)
        return 0.0f;
    GLfloat xCoord = fmodf(fTerrainX, gridSquareSize) / gridSquareSize;
    GLfloat zCoord = fmodf(fTerrainZ, gridSquareSize) / gridSquareSize;
    GLfloat answer;
    if(xCoord <= (1-zCoord)){
        answer = Maths::barryCentric(glm::vec3(0, fTerrainHeights[gridX][gridZ],0),
                glm::vec3(1, fTerrainHeights[gridX+1][gridZ],0),glm::vec3(0, fTerrainHeights[gridX][gridZ+1],1), glm::vec2(xCoord, zCoord));
    }else{
        answer = Maths::barryCentric(glm::vec3(1, fTerrainHeights[gridX+1][gridZ],0),
                glm::vec3(1, fTerrainHeights[gridX+1][gridZ+1],1),glm::vec3(0, fTerrainHeights[gridX][gridZ+1],1), glm::vec2(xCoord, zCoord));
    }
    return answer;
}

GLfloat Terrain::GetHeight(GLuint x, GLuint z, GLubyte *data)
{
    // The width and height has not take into account
    if(x<0 || z<0 || x >= uiVerticesCount || z >= uiVerticesCount){
        return 0.0f;
    }

    // Pixel index
    GLuint index = (x + z*uiVerticesCount)*3;
    GLfloat height = (GLfloat)((data[index] << 16) | (data[index+1] << 8) | data[index+2]);
    height -= (GLfloat)MAX_PIXEL_COLOR_HALF;
    height /= (GLfloat)MAX_PIXEL_COLOR_HALF;
    height *= (GLfloat)MAX_HEIGHT;
    return height;
}

glm::vec3 Terrain::CalculateNormal(GLuint x, GLuint z, GLubyte *data)
{
    GLfloat heightL = (x==0) ? 0.0f : GetHeight(x-1, z, data);
    GLfloat heightR = GetHeight(x+1, z, data);
    GLfloat heightD = (z==0) ? 0.0f : GetHeight(x, z-1, data);
    GLfloat heightU = GetHeight(x, z+1, data);

    return  glm::normalize(glm::vec3(heightL-heightR, 2.0f, heightD-heightU));
}

RawModel *Terrain::GenerateTerrain(const GLchar *heightmap)
{
    // Read image data
    GLint width, height, channel;
    GLubyte* img = SOIL_load_image(heightmap, &width, &height, &channel, SOIL_LOAD_RGB);
    if(img == NULL){
        std::cout<<"load image: "<<heightmap<<" failed!\n"
                <<"!!QUIT UNSUCCESSFUL!!"<<std::endl;
        exit(1);
    }

    // The number of vertex (on the edge)
    uiVerticesCount = height;
    // allocate memory to save vertex height
    fTerrainHeights = new GLfloat*[uiVerticesCount];
    for(GLuint i=0; i<uiVerticesCount; ++i){
        // two dimensional array
        fTerrainHeights[i] = new GLfloat[uiVerticesCount];
    }

    //GLuint count = VERTEX_COUNT * VERTEX_COUNT;
    vector<GLfloat> vertices;
    vector<GLfloat> normals;
    vector<GLfloat> textures;
    vector<GLuint>  indices;
    bool bCalculateNormal = true;
    // Position \ normal \ texture
    for(GLuint i=0; i<uiVerticesCount; ++i){
        for(GLuint j=0; j<uiVerticesCount; ++j){
            GLfloat fHeight = GetHeight(j, i, img);
            fTerrainHeights[j][i] = fHeight;
            // position
            vertices.push_back((GLfloat)j/((GLfloat)uiVerticesCount -1)*SIZE);
            vertices.push_back(fHeight);
            vertices.push_back((GLfloat)i/((GLfloat)uiVerticesCount -1)*SIZE);
            // normal
            glm::vec3 normal = bCalculateNormal ? CalculateNormal(j, i, img) : glm::vec3(0,1,0);
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
            // texture
            textures.push_back((GLfloat)j/((GLfloat)uiVerticesCount - 1));
            textures.push_back((GLfloat)i/((GLfloat)uiVerticesCount - 1));

        }
    }

    // Indice
    for(GLuint gz=0; gz<uiVerticesCount-1; ++gz){
        for(GLuint gx=0; gx<uiVerticesCount-1; ++gx){
            GLuint topLeft = (gz*uiVerticesCount) + gx;
            GLuint topRight = topLeft + 1;
            GLuint bottomLeft = ((gz+1)*uiVerticesCount) + gx;
            GLuint bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
    SOIL_free_image_data(img);
    return Loader::LoadToVAO(vertices, textures, normals, indices);
}
