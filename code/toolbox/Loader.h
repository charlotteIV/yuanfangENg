/* This class load a three dimensional model into memory
 *
 */
#ifndef LOADER_H
#define LOADER_H

#include <vector>
using std::vector;
#include "glew/glew.h"

class Mesh;
class RawModel;

class Loader
{
public:
    Loader(){}

    static void CleanUp();

    /*-----------------------------------------------------------------------------
     * type represent if a texture is transparent, mipmap and so on
     *
     * type = 0 generic
     * type = 1 transparent
     * type = 2 Mipmap
     * type = 3 transparent and Mipmap
     *-----------------------------------------------------------------------------*/
    static GLuint LoadTexture(const GLchar* filename, GLuint type = 0);

    // load 6 images for cube maps
    static GLuint LoadCubeMaps(const GLchar* filenames[]);

    // Load Object buffer from float array
    static RawModel* LoadToVAO(vector<GLfloat> &positions, vector<GLfloat> &textureCoords,
                        vector<GLfloat> &normals,   vector<GLuint> &indices);

    // Load Object buffer from float array
    static RawModel* LoadToVAO(vector<GLfloat> &positions, GLuint dimensions);

    // Load Object buffer
    static RawModel* LoadToVAO(Mesh *mesh);

private:
    static GLuint CreateVAO();
    static void BindIndices(vector<GLuint> &data);
    static void StoreDataInAttributeList(GLuint attributeNumber, GLuint coordinateSize, vector<GLfloat> &data);
    static void UnbindVAO();

    // To free memory
    static vector<GLuint> vaos;
    static vector<GLuint> vbos;
    static vector<GLuint> vtextures;

};

//  Data convertor
//! Mainly convert int and float array into their corresponding vector
//!
template <typename T>
class DataConvertor{
public:
    // HANDLE FLOAT
    static vector<T> ArraytoVector(T data[], GLuint size){
        // Variable need to be returned
        vector<T> vData;

        for(GLuint i=0; i<size; i++){
            vData.push_back(data[i]);
        }
        return vData;
    }
};

#endif // LOADER_H
