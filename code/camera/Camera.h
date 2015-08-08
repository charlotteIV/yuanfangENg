#ifndef CAMERA_H
#define CAMERA_H

#include "glew/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../renderEngine/DisplayManager.h"

class Camera
{
public:
    Camera();
    // Update camera, should be called in every frame
    virtual void Update() = 0;

    // Retrieve view matrix
    glm::mat4& GetViewMatrix() { return viewMatrix; }

    // Retrieve projection matrix Camera::GetProjMatrix
    static glm::mat4& GetProjMatrix() { return projMatrix; }

    //-----------------------------------------------------------------------------------
    // Retrieve and set pitch angle in degree
    void SetPitch(GLfloat fPitch);
    GLfloat GetPitch() { return fPitch; }

    // Retrieve and set yaw angle in degree
    void SetYaw(GLfloat fYaw);
    GLfloat GetYaw() { return fYaw; }

    // Retrieve and set yaw angle in degree
    void SetRoll(GLfloat fRoll);
    GLfloat GetRoll() { return fRoll; }

    // Set and retrieve position
    void SetPosition(glm::vec3 position);
    glm::vec3& GetPosition() { return position; }

    // Projection matrix
    static glm::mat4 projMatrix;
    // Set Projection matrix
    static void SetProjectionMatrix(GLfloat FOV, GLfloat aspect, GLfloat fNear, GLfloat fFar);

protected:
    // Camera position
    glm::vec3 position;

    // Camera rotation, Pitch(x), yaw(y) and roll(z)
    GLfloat fPitch, fYaw, fRoll;

    // View matrix
    glm::mat4 viewMatrix;

};

#endif // CAMERA_H
