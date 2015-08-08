#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "Camera.h"

static GLfloat SPEEDT = 20.0f;

class FreeCamera : public Camera
{
public:
    FreeCamera(const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
               const glm::vec3 &look = glm::vec3(0.0f, 0.0f, -1.0f));

    // update camera
    void Update();

    // Rotate Camera
    void Rotate(const float yaw, const float pitch, const float roll);

    // Translation
    void MoveForward(GLfloat dt);
    void MoveRight(GLfloat dt);
    void MoveUp(GLfloat dt);
};

#endif // CAMERA_H
