#ifndef ENTITY_H
#define ENTITY_H

#include "glew/glew.h"
#include "glm/glm.hpp"

class TextureModel;

class Entity
{
public:
    Entity();
    Entity(TextureModel *model, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
    Entity(TextureModel *model, GLuint index, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

    ~Entity(){}

    void SetModel(TextureModel *model);
    TextureModel*  GetModel() { return this->model; }

    // GetTextureOffset
    GLfloat GetTextureXOffset() const;
    GLfloat GetTextureYOffset() const;

    void SetPosition(GLuint in, GLfloat value);
    void SetPosition(const glm::vec3 position);
    const glm::vec3& GetPosition() const { return this->position; }

    void SetRotation(const glm::vec3 &rotation);
    const glm::vec3& GetRotation() const { return this->rotation; }

    void SetScale(const glm::vec3 &scale);
    const glm::vec3& GetScale() const { return this->scale; }

    // Move
    void IncreasePosition(const glm::vec3 &move);

    // Rotate
    void IncreaseRotation(const glm::vec3 &rotation);

private:
    // model pointer
    TextureModel *model;
    // Texture id
    GLuint uiTextureIndex;
    // entity position
    glm::vec3 position;
    // rotation in x-y-z axis in degree
    glm::vec3 rotation;
    // scalation
    glm::vec3 scale;
};

#endif // ENTITY_H
