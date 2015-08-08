#include "SkyboxRenderer.h"
#include "../GlobalVar.h"
#include "../toolbox/Loader.h"
#include "../models/RawModel.h"
#include "../skybox/SkyboxShader.h"

#include <iostream>
#include <vector>
using namespace std;

SkyboxRenderer::SkyboxRenderer(Loader *loader, Camera *camera)
{
    this->camera = camera;

    // cube vertices
    GLfloat verticesArray[]={
        -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,

        -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,

         GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,

        -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,

        -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,

        -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,
        -GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
         GlobalVar::fSkyBox_SIZE, -GlobalVar::fSkyBox_SIZE,  GlobalVar::fSkyBox_SIZE,
    };

    // SkyBox textures (Cube map, 6 textures in total)
    const GLchar* textureFiles[] = {
            "../res/images/skybox/right.png",   "../res/images/skybox/left.png",        // x direction
            "../res/images/skybox/top.png",     "../res/images/skybox/bottom.png",      // y direction
            "../res/images/skybox/back.png",    "../res/images/skybox/front.png",       // z direction
    };

    vector<GLfloat> vertices;
    for(GLuint i=0; i<sizeof(verticesArray)/sizeof(GLfloat); ++i){
        vertices.push_back(verticesArray[i]);
    }

    cube = loader->LoadToVAO(vertices, 3);
    textureID = loader->LoadCubeMaps(textureFiles);

    shader = new SkyBoxShader(GlobalVar::SKYBOX_VERTEX_FILE, GlobalVar::SKYBOX_FRAGMENT_FILE);
    shader->Start();
    shader->LoadProjectionMatrix(shader->GetUniformLocations("projectionMatrix"));
    shader->Stop();
}

void SkyboxRenderer::Render()
{
    shader->Start();
    shader->LoadViewMatrix(camera);
    // Bind VAO
    glBindVertexArray(cube->GetvaoID());
    glEnableVertexAttribArray(0);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // Draw triangle arrays
    glDrawArrays(GL_TRIANGLES, 0, cube->GetvertexCount());

    // Unbind VAO
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader->Stop();
}
