#include "Light.h"

Light::Light(const glm::vec3 &position, const glm::vec3 &color)
{
    this->position = position;
    this->color = color;
    this->attenuation = glm::vec3(1, 0, 0);
}

Light::Light(const glm::vec3 &position, const glm::vec3 &color, const glm::vec3 &attenuation)
{
    this->position = position;
    this->color = color;
    this->attenuation = attenuation;
}

void Light::SetAttenuation(const glm::vec3 &attenuation)
{
    this->attenuation = attenuation;
}

void Light::SetPosition(const glm::vec3 &position)
{
    this->position = position;
}

void Light::SetColor(const glm::vec3 &color)
{
    this->color = color;
}
