#include "MasterRenderer.h"
#include "DisplayManager.h"
#include "glfw/glfw3.h"
#include "../toolbox/Loader.h"
#include "../GlobalVar.h"
#include "../camera/Camera.h"

#include <iostream>
#include <vector>
using namespace std;

MasterRenderer::MasterRenderer(Camera *camera, vector<Light> *lights)
{
    this->camera = camera;
    this->lights = lights;

    // Default background color
    SetBackgroundColor(0.2f, 0.2f, 0.2f, 1.0f);

    // Enable face cull and not render back face
    EnableCullface(true);

    Loader loader;
    // Create skybox renderer
    skyboxRender = new SkyboxRenderer(&loader, camera);

    // Create terrain renderer
    terrainRender = new TerrainRenderer(this);
}

MasterRenderer::~MasterRenderer()
{
    CleanUp();
    //delete Entity renderer;
    for(list<EntityRenderer*>::iterator it= entitiesRenderer.begin(); it != entitiesRenderer.end(); ++it){
        delete (*it);
    }
}

void MasterRenderer::CleanUp(){

    //staticRenderer->GetShader()->CleanUp();
    //terrainShader.CleanUp();
}

void MasterRenderer::Prepare()
{
    /* Check events and clear buffers*/
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::EnableCullface(bool enabled)
{
    if(enabled){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }else{
        glDisable(GL_CULL_FACE);
    }
}

void MasterRenderer::ProcessEntityRenderer(EntityRenderer *entityRenedrer)
{
    for(list<EntityRenderer*>::iterator it= entitiesRenderer.begin(); it != entitiesRenderer.end(); ++it){
        if((*it) == entityRenedrer)
            return;
    }
    // if not found, just add it to the list
    this->entitiesRenderer.push_back(entityRenedrer);
}

void MasterRenderer::Rendering()
{
    // Clear opengl buffers
    Prepare();

    // Entities
    for(list<EntityRenderer*>::iterator it= entitiesRenderer.begin(); it != entitiesRenderer.end(); ++it){
        (*it)->Rendering();
    }

    // Terrain
    terrainRender->Rendering();

    // SkyBox
    skyboxRender->Render();
}

void MasterRenderer::SetCamera(Camera *camera)
{
    this->camera = camera;
}

void MasterRenderer::SetLightsList(vector<Light> *lights)
{
    this->lights = lights;
}

void MasterRenderer::SetBackgroundColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alph)
{
    GlobalVar::bg_RED = r; GlobalVar::bg_GREEN = g; GlobalVar::bg_BLUE = b;
    glClearColor(GlobalVar::bg_RED, GlobalVar::bg_GREEN, GlobalVar::bg_BLUE, alph);
}
