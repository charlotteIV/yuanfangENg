#include "ModelData.h"
#include "RawModel.h"
#include "../toolbox/Loader.h"

#include <iostream>
using namespace std;

ModelData::ModelData()
{
}

RawModel *Mesh::LoadtoRawModel(Loader *loader)
{
    return loader->LoadToVAO(this);
}


ModelData::ModelData(const GLchar *filename)
{
    // Loading mesh with assimp
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout<<"ERROR::ASSIMP::"<<importer.GetErrorString()<<std::endl;
        exit(9);
    }

    // Iterate all mesh
    for(GLuint i=0; i<scene->mNumMeshes; ++i){
        Mesh meshElement;

        // Only Handle the first model
        aiMesh* mesh = scene->mMeshes[0];


        // Process vertex position, normals and texCoords
        for(GLuint i=0; i<mesh->mNumVertices; ++i){
            // Position
            meshElement.GetVertices().push_back(mesh->mVertices[i].x);
            meshElement.GetVertices().push_back(mesh->mVertices[i].y);
            meshElement.GetVertices().push_back(mesh->mVertices[i].z);
            // Normal
            meshElement.GetNormals().push_back(mesh->mNormals[i].x);
            meshElement.GetNormals().push_back(mesh->mNormals[i].y);
            meshElement.GetNormals().push_back(mesh->mNormals[i].z);
            // TexCoords
            /* Does the mesh contain texture coordinates? */
            if(mesh->mTextureCoords[0]){
                meshElement.GetTextures().push_back(mesh->mTextureCoords[0][i].x);
                meshElement.GetTextures().push_back(mesh->mTextureCoords[0][i].y);
            }
            else{
                meshElement.GetTextures().push_back(0.0f);
                meshElement.GetTextures().push_back(0.0f);
            }
        }

        // Process indices
        for(GLuint i=0; i<mesh->mNumFaces; ++i){
            aiFace *face = &mesh->mFaces[i];
            for(GLuint j=0; j<face->mNumIndices; ++j)
                meshElement.GetIndices().push_back(face->mIndices[j]);
        }
        // save the mesh
        mMeshList.push_back(meshElement);
    }
}
