#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "../skybox/SkyboxRenderer.h"
#include "../static/StaticRenderer.h"
#include "../terrain/TerrainRenderer.h"
#include "../entities/Entity.h"
#include "../models/TextureModel.h"
#include "../static//StaticShader.h"
#include "../skybox/SkyboxShader.h"
#include "../terrain/TerrainShader.h"
#include "../entities/EntityRenderer.h"

#include <map>
#include <list>
using namespace std;

class Camera;

class MasterRenderer
{
public:
    MasterRenderer(Camera *camera = NULL, vector<Light> *lights = NULL);
    ~MasterRenderer();

    // Clear buffers
    void Prepare();

    void CleanUp();

    void Rendering();

    // Back face cull
    void EnableCullface(bool enabled);

    // Entity renderer
    void ProcessEntityRenderer(EntityRenderer *entityRenedrer);

    // Set camera
    void SetCamera(Camera *camera);

    // Retrieve camera
    Camera* GetCamera() { return camera; }

    // Set lights
    void SetLightsList(vector<Light> *lights);

    // Retrieve lights
    vector<Light>* GetLightsList(){ return lights; }

    // Retrieve terrain renderer
    TerrainRenderer* GetTerrainList() { return terrainRender; }

    // Set background color of the window
    void SetBackgroundColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alp);

private:
    // Camera
    Camera *camera;

    // Lights list
    vector<Light> *lights;

    // Entity renderer
    list<EntityRenderer*> entitiesRenderer;

    // Terrain Shader and renderer
    TerrainRenderer *terrainRender;

    // Skybox
    SkyboxRenderer *skyboxRender;
};

#endif // MASTERRENDERER_H
