#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include <map>
#include <list>
#include "glm/glm.hpp"
using namespace std;

class Entity;
class TextureModel;
class MasterRenderer;

class EntityRenderer
{
public:
    EntityRenderer(MasterRenderer* masterRenderer=NULL);
    virtual ~EntityRenderer();

    // Render operation
    void Rendering();

    // Add one entity into entity list
    void AddEntity(Entity *entity);

    // Send uniform parameters in shaders
    virtual void PrepareInstance(const Entity *entity){}

    // Bind VAO and VBO
    virtual void PreparetextureModel(const TextureModel *model){}

    // Unbind VAO and VBO
    virtual void UnbindTextureModel(){}

    // Set master renderer
    void SetMasterRenderer(MasterRenderer* masterRenderer);

    // Retrieve master renderer
    MasterRenderer* GetMasterRenderer() { return masterRenderer; }

protected:
    // Used to configure the opengl options
    MasterRenderer* masterRenderer;

    // Entities list
    map<TextureModel *, list<Entity *> > entities;
};

#endif // ENTITYRENDERER_H
