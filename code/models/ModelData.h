#ifndef MODELDATA_H
#define MODELDATA_H

#include <vector>
#include "glew/glew.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
using namespace std;

class Loader;
class RawModel;
class Mesh{
private:
    // vertex position
    vector<GLfloat> vertices;
    // vertex normal
    vector<GLfloat> normals;
    // vertex texture
    vector<GLfloat> textures;
    // vertex index
    vector<GLuint> indices;

public:
    // Create Rawmodel in memory
    RawModel* LoadtoRawModel(Loader *loader);

    // Retrieve function
    vector<GLfloat>& GetVertices() { return vertices; }
    vector<GLfloat>& GetNormals() { return normals; }
    vector<GLfloat>& GetTextures() { return textures; }
    vector<GLuint>& GetIndices() { return indices; }
};

class ModelData
{
public:
    ModelData();

    // Initialize from model file
    ModelData(const GLchar* filename);

    // retrieve specific mesh in the vector
    Mesh& GetMesh(GLuint in) { return mMeshList[in]; }

private:
    vector<Mesh> mMeshList;
};

#endif // MODELDATA_H
