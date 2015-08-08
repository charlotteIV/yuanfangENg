#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "glew/glew.h"

class Loader;
class Camera;
class RawModel;
class SkyBoxShader;
class SkyboxRenderer
{
public:
    SkyboxRenderer(Loader *loader, Camera *camera);

    void Render();

private:
    Camera *camera;
    RawModel* cube;
    GLuint textureID;
    SkyBoxShader* shader;
};

#endif // SKYBOXRENDERER_H
