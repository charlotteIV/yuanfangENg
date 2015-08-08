#include "StaticRenderer.h"
#include "../renderEngine/MasterRenderer.h"
#include "../GlobalVar.h"
#include "../toolbox/Maths.h"
#include "../entities/Entity.h"
#include "../models/RawModel.h"
#include "../models/TextureModel.h"
#include "../static/StaticShader.h"

StaticRenderer::StaticRenderer(MasterRenderer *masterRender)
{
    // The pointer of master render
    this->masterRenderer = masterRender;
    this->masterRenderer->ProcessEntityRenderer(this);

    // Assign shader
    this->shader = new StaticShader(GlobalVar::STATIC_VERTEX_FILE, GlobalVar::STATIC_FRAGMENT_FILE);

    this->shader->Start();
    this->shader->LoadSkyColor(GlobalVar::bg_RED, GlobalVar::bg_GREEN, GlobalVar::bg_BLUE);
    this->shader->LoadLights(this->masterRenderer->GetLightsList());
    this->shader->LoadProjectionMatrix(this->shader->GetUniformLocations("projectionMatrix"));
    this->shader->Stop();
}

StaticRenderer::~StaticRenderer()
{
    delete shader;
}

void StaticRenderer::PreparetextureModel(const TextureModel *model)
{
    shader->Start();
    ///////////////////////////////////////////////////////////////////////////////////////
    ///! VAO & VBO
    RawModel* rawModel = model->GetRawModel();
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
    // Shiness and reflectivity
    ModelTexture *texture = model->GetTexture();

    // Make sure that transparency texture disable back face cull
    if(texture->IsHasTransparency()){
        GetMasterRenderer()->EnableCullface(false);
    }

    // load number of rows in texture
    shader->LoadNumberOfRows(texture->GetNumofRows());
    // FakeLighting
    shader->LoadFakeLighting(texture->IsUseFakeLighing());
    // Set specular parameters to shader
    shader->LoadShineVariables(texture->GetShineDamper(), texture->GetReflectivity());

    // SELECT TEXTURE
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
}

void StaticRenderer::UnbindTextureModel()
{
    // Disable face culling
    GetMasterRenderer()->EnableCullface(false);

    ///! UNBIND VBO AND VAO
    // Disable vertex and texture coordinates array
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    // Unbind VAO
    glBindVertexArray(0);
    shader->Stop();
}

void StaticRenderer::PrepareInstance(const Entity *entity)
{
    //ModelTexture *texture
    // Transformation
    glm::mat4 transformMatrix = Maths::CreateTransformationMatrix(entity->GetPosition(), entity->GetRotation(), entity->GetScale());
    shader->LoadTransformMatrix(transformMatrix);
    shader->LoadOffset(entity->GetTextureXOffset(), entity->GetTextureYOffset());

    // Update lights
    shader->LoadLights(this->masterRenderer->GetLightsList());

    // Update camera
    shader->LoadViewMatrix(this->masterRenderer->GetCamera());
}
