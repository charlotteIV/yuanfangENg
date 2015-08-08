#include "TerrainRenderer.h"
#include "glm/glm.hpp"
#include "../GlobalVar.h"
#include "../toolbox/Maths.h"
#include "../models/RawModel.h"
#include "../Terrain/Terrain.h"
#include "../renderEngine/MasterRenderer.h"
#include "../terrain/TerrainShader.h"
#include "../textures/TerrainTexture.h"
#include "../textures/TerrainTexturePack.h"

TerrainRenderer::TerrainRenderer(MasterRenderer *masterRender)
{
    this->masterRender = masterRender;
    // Assign shader
    this->shader = new TerrainShader(GlobalVar::TERRAIN_VERTEX_FILE, GlobalVar::TERRAIN_FRAGMENT_FILE);

    shader->Start();
    shader->ConnectTextureUnits();
    shader->LoadLights(this->masterRender->GetLightsList());
    shader->LoadSkyColor(GlobalVar::bg_RED, GlobalVar::bg_GREEN, GlobalVar::bg_BLUE);
    shader->LoadProjectionMatrix(shader->GetUniformLocations("projectionMatrix"));
    shader->Stop();
}

TerrainRenderer::~TerrainRenderer()
{
    terrains.clear();
    delete shader;
}

void TerrainRenderer::Rendering()
{
    // Terrain
    shader->Start();

    // Update lights
    shader->LoadLights(masterRender->GetLightsList());
    shader->LoadViewMatrix(masterRender->GetCamera());

    // Iterated render
    for(list<Terrain*>::iterator it=terrains.begin(); it!=terrains.end(); ++it){
        // Bind VAO and texture
        PrepareTerrain(*it);
        // Send matrix
        LoadModelMatrix(*it);
        // Render entity here
        glDrawElements(GL_TRIANGLES, (*it)->GetRawModel()->GetvertexCount(), GL_UNSIGNED_INT, 0);
        UnbindTextureModel();
    }

    shader->Stop();
}

void TerrainRenderer::AddTerrain(Terrain *terrain)
{
    for(list<Terrain*>::iterator it=terrains.begin(); it!=terrains.end(); ++it){
        if((*it) == terrain)
            return;
    }
    // Not find, just add it
    terrains.push_back(terrain);
}

void TerrainRenderer::PrepareTerrain(const Terrain *terrain)
{
    ///////////////////////////////////////////////////////////////////////////////////////
    ///! VAO & VBO
    RawModel* rawModel = terrain->GetRawModel();;
    // Bind VAO first
    glBindVertexArray(rawModel->GetvaoID());
    // Enable the vertex array
    glEnableVertexAttribArray(0);
    // Enable texture coordinates
    glEnableVertexAttribArray(1);
    // Normal attribute
    glEnableVertexAttribArray(2);

    ///////////////////////////////////////////////////////////////////////////////////////
    ///! TEXTURE
    BindTexture(terrain);

    // Set specular parameters to shader
    shader->LoadShineVariables(1, 0);
}

void TerrainRenderer::BindTexture(const Terrain *terrain)
{
    TerrainTexturePack *texturePack = terrain->GetTexturePack();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturePack->GetBackgroundTexture()->GetTextureID());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texturePack->GetrTexture()->GetTextureID());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texturePack->GetgTexture()->GetTextureID());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texturePack->GetbTexture()->GetTextureID());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, terrain->GetBlendMap()->GetTextureID());
}

void TerrainRenderer::UnbindTextureModel()
{
    ///! UNBIND VBO AND VAO
    // Disable vertex and texture coordinates array
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    // Unbind VAO
    glBindVertexArray(0);
}

void TerrainRenderer::LoadModelMatrix(const Terrain *terrain)
{
    // Transformation
    glm::mat4 transformMatrix = Maths::CreateTransformationMatrix(glm::vec3(terrain->GetX(), 0.0f, terrain->GetZ()),
                                                                  glm::vec3(0.0f), glm::vec3(1.0f));
    shader->LoadTransformMatrix(transformMatrix);
}
