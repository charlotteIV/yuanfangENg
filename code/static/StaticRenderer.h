#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <list>
#include "glm/glm.hpp"
#include "../entities/EntityRenderer.h"
using namespace std;

class Entity;
class RawModel;
class TextureModel;
class StaticShader;
class MasterRenderer;
class StaticRenderer : public EntityRenderer
{
public:
    StaticRenderer(MasterRenderer* masterRenderer=NULL);
    ~StaticRenderer();

    // Bind VAO and VBO
    void PreparetextureModel(const TextureModel *model);

    // Unbind
    void UnbindTextureModel();

    // Create transformation matrix
    void PrepareInstance(const Entity *entity);

    // Retrieve current shader
    StaticShader* GetShader(){ return shader; }

private:
    // Shader
    StaticShader *shader;
};

#endif // RENDERER_H
