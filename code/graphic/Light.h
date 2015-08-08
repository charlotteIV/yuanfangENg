#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"

class Light
{
public:
    Light(const glm::vec3 &position, const glm::vec3 &color);
    Light(const glm::vec3 &position, const glm::vec3 &color, const glm::vec3 &attenuation);

    void SetAttenuation(const glm::vec3 &attenuation);
    void SetPosition(const glm::vec3 &position);
    void SetColor(const glm::vec3 &color);

    glm::vec3 GetAttenuation() { return attenuation; }
    glm::vec3 GetPosition() { return position; }
    glm::vec3 GetColor() { return color; }

private:
    glm::vec3 position;
    glm::vec3 color;

    glm::vec3 attenuation;
};

#endif // LIGHT_H
