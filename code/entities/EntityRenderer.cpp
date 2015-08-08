#include "EntityRenderer.h"
#include "../models/RawModel.h"
#include "../renderEngine/MasterRenderer.h"

#include <iostream>
using namespace std;

EntityRenderer::EntityRenderer(MasterRenderer *masterRenderer)
{
    // Get the pointer of master render
    this->masterRenderer = masterRenderer;
}

EntityRenderer::~EntityRenderer()
{
    // delete Texture model and the entity
    for(map<TextureModel*, list<Entity*> >::const_iterator it = entities.begin(); it != entities.end(); ++it){
        const list<Entity*> &batch = it->second;

        // Iterate all entities of the given model
        for(list<Entity*>::const_iterator it2 = batch.begin(); it2 != batch.end(); it2++){
            // delete current entity
            delete *it2;
        }

        //delete TextureModel
        if(it->first)
            delete (it->first);
    }
}

void EntityRenderer::Rendering()
{
    // Iterate all model
    for(map<TextureModel*, list<Entity*> >::const_iterator it = entities.begin(); it != entities.end(); ++it){
        PreparetextureModel(it->first);
        const list<Entity*> &batch = it->second;

        // Retrieve raw model
        RawModel *model = it->first->GetRawModel();

        // Iterate all entities of the given model
        for(list<Entity*>::const_iterator it2 = batch.begin(); it2 != batch.end(); it2++){
            PrepareInstance(*it2);
            // Render entity here
            glDrawElements(GL_TRIANGLES, model->GetvertexCount(), GL_UNSIGNED_INT, 0);
        }

        UnbindTextureModel();
    }
}

void EntityRenderer::AddEntity(Entity *entity)
{
    // Get corresponding TextureModel
    TextureModel *model = entity->GetModel();
    // Find if a TextureModel is existed
    map<TextureModel*,list<Entity*> >::iterator it = entities.find(model);
    if(it != entities.end()){
        // Save the entity that share raw model
        it->second.push_back(entity);
    }else{
        // Not find, so new create a list
        list<Entity*> newBatch;
        newBatch.push_back(entity);
        entities.insert(std::pair<TextureModel*,list<Entity*> >(model, newBatch));
    }
}

void EntityRenderer::SetMasterRenderer(MasterRenderer *masterRenderer)
{
    this->masterRenderer = masterRenderer;
}
