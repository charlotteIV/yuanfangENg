#include "MeshLoader.h"

#include <vector>
#include <iostream>
using namespace std;

#include "glm/glm.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

RawModel* MeshLoader::LoadObjModel(string fileName)
{
    // Loading mesh with assimp
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout<<"ERROR::ASSIMP::"<<importer.GetErrorString()<<std::endl;
        exit(1);
    }


    // If a mesh is exist
    if(scene->HasMeshes()){
        vector<GLfloat> vertices;
        vector<GLfloat> textures;
        vector<GLfloat> normals;
        vector<GLuint>  indices;

        // Only Handle the first model
        aiMesh* mesh = scene->mMeshes[0];

        glm::vec2 vector2;
        glm::vec3 vector3;
        // Process vertex position, normals and texCoords
        for(GLuint i=0; i<mesh->mNumVertices; ++i){
            // Position
            vector3.x = mesh->mVertices[i].x;
            vector3.y = mesh->mVertices[i].y;
            vector3.z = mesh->mVertices[i].z;
            vertices.push_back(vector3.x);vertices.push_back(vector3.y);vertices.push_back(vector3.z);
            // Normal
            vector3.x = mesh->mNormals[i].x;
            vector3.y = mesh->mNormals[i].y;
            vector3.z = mesh->mNormals[i].z;
            normals.push_back(vector3.x);normals.push_back(vector3.y);normals.push_back(vector3.z);
            // TexCoords
            /* Does the mesh contain texture coordinates? */
            if(mesh->mTextureCoords[0]){
                vector2.x = mesh->mTextureCoords[0][i].x;
                vector2.y = mesh->mTextureCoords[0][i].y;
            }else
                vector2 = glm::vec2(0.0f, 0.0f);
            textures.push_back(vector2.x);textures.push_back(vector2.y);
        }

        // Process indices
        for(GLuint i=0; i<mesh->mNumFaces; ++i){
            aiFace *face = &mesh->mFaces[i];
            for(GLuint j=0; j<face->mNumIndices; ++j)
                indices.push_back(face->mIndices[j]);
        }

        return Loader::LoadToVAO(vertices, textures, normals, indices);
    }
    cout<<"ERROR::OBJLOADER::WITHOUT A MESH!"<<endl;
    exit(8);
    return new RawModel(1,1);
}
