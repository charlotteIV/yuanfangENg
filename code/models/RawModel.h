/* This class render a three dimensional model in memory
 *
 */
#include "glew/glew.h"

#ifndef RAWMODEL_H
#define RAWMODEL_H

class RawModel
{
public:
    RawModel(GLuint vaoID, GLuint vertexCount);

    GLuint GetvaoID() { return vaoID; }
    GLuint GetvertexCount() { return vertexCount; }

private:
    GLuint vaoID;          // Vertex array buffer id
    GLuint vertexCount;    // The number of vertices of the model
};

#endif // RAWMODEL_H
