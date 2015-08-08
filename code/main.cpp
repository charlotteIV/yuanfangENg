#include <iostream>
#include <map>
#include <list>
#include <stdlib.h>
using namespace std;

#include "GlobalVar.h"

#include "HEUEngine.h"
#include "toolbox/MeshLoader.h"

///////////////////////////////////////////////////////////////////////////////
///!* GLOBAL VARIABLES DEFINATION */
    ActorCamera *g_Camera = NULL;
    // WINDOW SIZE
    const GLuint WINDOWWIDTH  = 960;
    const GLuint WINDOWHEIGHT = 620;
///! END GLOBAL  VARIABLES DEFINATION
///////////////////////////////////////////////////////////////////////////////

/* GLOBAL FUNCTION DEFINATION */

int main()
{
    ///! PRINT　WELCOME INFORMATION
    cout<<"***********************************************************************"<<endl;
    cout<<"\n\t\t\tWelcome to HEUEngine"<<endl;
    cout<<"\n\t\t\tProject Build:2015\\07\\06"<<endl;
    cout<<"\n\t\t\tAuthor:ZhangJG@hrbeu.edu.cn"<<endl;
    cout<<"***********************************************************************"<<endl;

    /* Create Display and Setup OpenGL */
    DisplayManager displayManager("HEUEngine", WINDOWWIDTH, WINDOWHEIGHT);
    displayManager.CreateDisplay();
    displayManager.SetWindowPosition(200, 80);

    ///////////////////////////////////////////////////////////////////////////
    ///! Configuration
    ///
    // Camera
    //g_Camera = new FreeCamera(glm::vec3(-100.0f, 35.0f, -40.0f));
    // Lighting
    vector<Light> lights;
    Light light0(glm::vec3(0.0f, 1000.0f, -7000.0f), glm::vec3(0.4f, 0.4f, 0.4f));
    lights.push_back(light0);
    Light light1(glm::vec3(185.0f, 12.8f, -293.0f), glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(1, 0.01f, 0.02f));
    lights.push_back(light1);
    Light light2(glm::vec3(370.0f, 24.0f, -300.0f), glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(1, 0.01f, 0.02f));
    lights.push_back(light2);
    Light light3(glm::vec3(293.0f, 10.0f, -305.0f), glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(1, 0.01f, 0.02f));
    lights.push_back(light3);


    // Tree
    TextureModel *tree = new TextureModel(MeshLoader::LoadObjModel("../res/models/tree.obj"),
                      new ModelTexture(Loader::LoadTexture("../res/images/tree.png")));
    // Grass
    TextureModel *grass = new TextureModel(MeshLoader::LoadObjModel("../res/models/grassModel.obj"),
                       new ModelTexture(Loader::LoadTexture("../res/images/grassTexture.png", 3)));
    grass->GetTexture()->SetHasTransparency(true);
    grass->GetTexture()->SetUseFakeLighing(true);
    // Fern
    TextureModel *fern = new TextureModel(MeshLoader::LoadObjModel("../res/models/fern.obj"),
                      new ModelTexture(Loader::LoadTexture("../res/images/fern.png", 3)));
    fern->GetTexture()->SetHasTransparency(true);
    fern->GetTexture()->SetNumofRows(2);
    // Flower
    TextureModel *flower = new TextureModel(MeshLoader::LoadObjModel("../res/models/grassModel.obj"),
                       new ModelTexture(Loader::LoadTexture("../res/images/flower.png", 3)));
    flower->GetTexture()->SetHasTransparency(true);
    flower->GetTexture()->SetUseFakeLighing(true);

    // Bubble
    TextureModel *bubble = new TextureModel(MeshLoader::LoadObjModel("../res/models/pine.obj"),
                      new ModelTexture(Loader::LoadTexture("../res/images/pine.png",3)));

    // Terrain texture packs
    TerrainTexturePack terrainTexturePack("../res/images/grassy3.png","../res/images/mud.png",
                                          "../res/images/grassFlowers.png","../res/images/path.png");
    TerrainTexture blendMap(Loader::LoadTexture("../res/images/blendMap.png"));

    // Terrains
    Terrain *terrain0 = new Terrain(0, -1, &terrainTexturePack, &blendMap);
    //Terrain terrain1(1, 0, &loader, &terrainTexturePack, &blendMap);

    // BunnyModel
    TextureModel *bunny = new TextureModel(MeshLoader::LoadObjModel("../res/models/player.obj"),
                       new ModelTexture(Loader::LoadTexture("../res/images/player.png")));
    glm::vec3 actorPosition(200, 5, -304);
    // Let the actor stands on the terrain
    actorPosition.y = terrain0->GetTerrainHeight(actorPosition.x, actorPosition.z);
    Actor *bunnyEntity = new Actor(bunny, actorPosition, glm::vec3(0,90,0), glm::vec3(1));
    // Actor camera
    g_Camera = new ActorCamera(bunnyEntity);

    TextureModel *lamp = new TextureModel(MeshLoader::LoadObjModel("../res/models/lamp.obj"),
                             new ModelTexture(Loader::LoadTexture("../res/images/lamp.png")));

    MasterRenderer *renderer = new MasterRenderer((Camera*)g_Camera, &lights);
    renderer->GetTerrainList()->AddTerrain(terrain0);

    StaticRenderer *staticRenderer = new StaticRenderer(renderer);
    // Entity List
    staticRenderer->AddEntity(bunnyEntity);
    staticRenderer->AddEntity(new Entity(lamp, glm::vec3(185, -4.7f, -293),glm::vec3(0.0f), glm::vec3(1.0f)));
    staticRenderer->AddEntity(new Entity(lamp, glm::vec3(370, 4.2f, -300),glm::vec3(0.0f), glm::vec3(1.0f)));
    staticRenderer->AddEntity(new Entity(lamp, glm::vec3(293, -6.8f, -305),glm::vec3(0.0f), glm::vec3(1.0f)));

    Random random(1000);
    for(GLuint i=0; i<500; i++){
        if(i%7 == 0){
            GLfloat x = random.NextFloat() * 800;
            GLfloat z = -10 + random.NextFloat() * -780;
            GLfloat y = terrain0->GetTerrainHeight(x,z);
            Entity *grassEntity = new Entity(grass, glm::vec3(x, y, z),glm::vec3(0.0f), glm::vec3(1.8f));
            staticRenderer->AddEntity(grassEntity);

            x = random.NextFloat() * 800;
            z = -10 + random.NextFloat() * -780;
            y = terrain0->GetTerrainHeight(x,z);
            Entity *fernEntity = new Entity(fern, rand()%4,  glm::vec3(x, y, z),glm::vec3(0.0f, random.NextFloat()*360.0f, 0.0f), glm::vec3(0.9f));
            staticRenderer->AddEntity(fernEntity);

            x = random.NextFloat() * 800;
            z = -10 + random.NextFloat() * -780;
            y = terrain0->GetTerrainHeight(x,z);
            Entity *flowerEntity = new Entity(flower, glm::vec3(x, y, z),glm::vec3(0.0f), glm::vec3(2.3f));
            staticRenderer->AddEntity(flowerEntity);
        }
        if(i%3 == 0){
            GLfloat x = random.NextFloat() * 800;
            GLfloat z = -10 + random.NextFloat() * -780;
            GLfloat y = terrain0->GetTerrainHeight(x,z);
            Entity *bubbleEntity = new Entity(bubble, glm::vec3(x, y, z),glm::vec3(0.0f, random.NextFloat()*360.0f, 0.0f), glm::vec3(random.NextFloat() * 0.1f + 0.6f));
            staticRenderer->AddEntity(bubbleEntity);

            x = random.NextFloat() * 800;
            z = -10 + random.NextFloat() * -760;
            y = terrain0->GetTerrainHeight(x,z);
            Entity *treeEntity = new Entity(tree, glm::vec3(x, y, z),glm::vec3(0.0f), glm::vec3(random.NextFloat() * 1.0f + 4.0f));
            staticRenderer->AddEntity(treeEntity);
        }
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    ///! END Configuration
    //////////////////////////////////////////////////////////////////////////
    /* RENDER ITERATION LOOP */
    while(!displayManager.isWindowShouldClose()){

        g_Camera->Update();
        //tree.IncreaseRotation(glm::vec3(0.0f,2.0f,0.0f));
        bunnyEntity->Transform(terrain0, displayManager.GetFrameTimeSeconds());

        // Rendering process
        renderer->Rendering();

        // SWAP BUFFERS
        displayManager.UpdateDisplay();
    }

    // Terminate
    Loader::CleanUp();
    renderer->CleanUp();
    displayManager.CloseDisplay();

    // EXIT　SUCCESSFUL
    cout<<"\n\t\t----------PRESS ENTER TO QUIT----------\n"<<endl;
    return 0;
}

