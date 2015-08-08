#include "Entity.h"
#include "../models/TextureModel.h"

Entity::Entity()
{
}

Entity::Entity(TextureModel *model, const glm::vec3 &position, const glm::vec3 &rotation,
               const glm::vec3 &scale)
{
    this->model = model;
    this->uiTextureIndex = 0;
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

Entity::Entity(TextureModel *model, GLuint index, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
{
    this->model = model;
    this->uiTextureIndex = index;
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

void Entity::SetModel(TextureModel *model)
{
    this->model = model;
}

GLfloat Entity::GetTextureXOffset() const
{
    GLuint column = uiTextureIndex % model->GetTexture()->GetNumofRows();
    return (GLfloat)column / (GLfloat)model->GetTexture()->GetNumofRows();
}

GLfloat Entity::GetTextureYOffset() const
{
    GLuint row = uiTextureIndex / model->GetTexture()->GetNumofRows();
    return (GLfloat)row / (GLfloat)model->GetTexture()->GetNumofRows();
}

void Entity::SetPosition(GLuint in, GLfloat value)
{
    this->position[in] = value;
}

void Entity::SetPosition(const glm::vec3 position)
{
    this->position = position;
}

void Entity::SetRotation(const glm::vec3 &rotation)
{
    this->rotation = rotation;
}

void Entity::SetScale(const glm::vec3 &scale)
{
    this->scale = scale;
}

void Entity::IncreasePosition(const glm::vec3 &move)
{
    this->position += move;
}

void Entity::IncreaseRotation(const glm::vec3 &rotation)
{
    this->rotation += rotation;
}
