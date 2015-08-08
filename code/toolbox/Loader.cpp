#include "Loader.h"
#include "soil.h"
#include "../models/RawModel.h"
#include "../models/ModelData.h"
#include <iostream>
using namespace std;

// static variable defiantions here
vector<GLuint> Loader::vaos;
vector<GLuint> Loader::vbos;
vector<GLuint> Loader::vtextures;

void Loader::CleanUp()
{
    for(GLuint i = 0; i< vaos.size(); ++i){
        glDeleteVertexArrays(1, &vaos[i]);
    }

    for(GLuint i = 0; i< vbos.size(); ++i){
        glDeleteBuffers(1, &vbos[i]);
    }

    for(GLuint i=0; i<vtextures.size(); ++i){
        glDeleteTextures(1, &vtextures[i]);
    }
}

/*-----------------------------------------------------------------------------
 * type represent if a texture is transparent, mipmap and so on
 *
 * type = 0 generic
 * type = 1 transparent
 * type = 2 Mipmap
 * type = 3 transparent and Mipmap
 *-----------------------------------------------------------------------------*/
GLuint Loader::LoadTexture(const GLchar *filename, GLuint type)
{
    // Read image data
    GLint width, height, channel;
    GLubyte* img = SOIL_load_image(filename, &width, &height, &channel, (type ==1 || type==3)?SOIL_LOAD_RGBA:SOIL_LOAD_RGB);
    if(img == NULL){
        std::cout<<"load image: "<<filename<<" failed!\n"
                <<"!!QUIT UNSUCCESSFUL!!"<<std::endl;
        exit(1);
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Texture Filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Repeat mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    switch (type) {
    case 1:
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        break;
    case 2:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        break;
    case 3:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
        break;
    default:
        break;
    }
    // Generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, (type ==1 || type==3)?GL_RGBA:GL_RGB, width, height, 0, (type ==1 || type==3)?GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, img);

    // keep instant
    vtextures.push_back(textureID);

    if(type == 2 || type == 3)
        glGenerateMipmap(GL_TEXTURE_2D);

    // free image data
    SOIL_free_image_data(img);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

GLuint Loader::LoadCubeMaps(const GLchar *filenames[])
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for(GLuint i=0; i<6; ++i){
        // Read image data
        GLint width, height, channel;
        GLubyte* img = SOIL_load_image(filenames[i], &width, &height, &channel, SOIL_LOAD_RGB);
        if(img == NULL){
            std::cout<<"load image: "<<filenames[i]<<" failed!\n"
                    <<"!!QUIT UNSUCCESSFUL!!"<<std::endl;
            exit(1);
        }

        // Generate texture
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

        // free image data
        SOIL_free_image_data(img);
    }

    // Texture Filter
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    vtextures.push_back(textureID);
    return textureID;
}

RawModel *Loader::LoadToVAO(vector<GLfloat> &positions, GLuint dimensions)
{
    // Create VAO
    GLuint vaoID = CreateVAO();

    // Sava position data in VBO
    StoreDataInAttributeList(0, dimensions, positions);

    UnbindVAO();

    return new RawModel(vaoID, positions.size() / dimensions);
}

RawModel *Loader::LoadToVAO(vector<GLfloat> &positions, vector<GLfloat> &textureCoords, vector<GLfloat> &normals, vector<GLuint> &indices)
{
    // Create VAO
    GLuint vaoID = CreateVAO();

    // Bind Inidces
    BindIndices(indices);

    // Sava position data in VBO
    StoreDataInAttributeList(0, 3, positions);

    // Save texture coordinates
    StoreDataInAttributeList(1, 2, textureCoords);

    // Save texture coordinates
    StoreDataInAttributeList(2, 3, normals);

    // Unbind the VAO, avoiding further error operating
    UnbindVAO();

    return new RawModel(vaoID, indices.size());
}

RawModel *Loader::LoadToVAO(Mesh *mesh)
{
    return LoadToVAO(mesh->GetVertices(), mesh->GetTextures(), mesh->GetNormals(), mesh->GetIndices());
}

GLuint Loader::CreateVAO()
{
    GLuint vaoID;
    // Create VAO
    glGenVertexArrays(1, &vaoID);
    // Add the vao id into vaos
    vaos.push_back(vaoID);
    // And then bind it
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::BindIndices(vector<GLuint> &data)
{
    GLuint eboID;
    // Create EBO
    glGenBuffers(1, &eboID);
    vbos.push_back(eboID);
    // Bind and send data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * data.size(), &data[0], GL_STATIC_DRAW);
}

void Loader::StoreDataInAttributeList(GLuint attributeNumber, GLuint coordinateSize, vector<GLfloat> &data)
{
    GLuint vboID;
    // Create VBO
    glGenBuffers(1, &vboID);
    // Add the vao id into vaos
    vbos.push_back(vboID);
    // Then bind and send data
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data[0], GL_STATIC_DRAW);
    // Set attribute pointer
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(GLfloat), (GLvoid*)0);
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::UnbindVAO()
{
    glBindVertexArray(0);
}
