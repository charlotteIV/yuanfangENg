#include "Camera.h"
#include "../GlobalVar.h"

#include <iostream>
using namespace std;

Camera::Camera(){
    this->fPitch = 0.0f;
    this->fYaw   = 0.0f;
    this->fRoll  = 0.0f;
}

void Camera::SetPosition(glm::vec3 position)
{
    this->position = position;
}

void Camera::SetPitch(GLfloat fPitch)
{
    this->fPitch = fPitch;
}

void Camera::SetYaw(GLfloat fYaw)
{
    this->fYaw = fYaw;
}

void Camera::SetRoll(GLfloat fRoll)
{
    this->fRoll = fRoll;
}

void Camera::SetProjectionMatrix(GLfloat FOV,
                                 GLfloat aspect, GLfloat fNear, GLfloat fFar)
{
    // Uisng glm library
    projMatrix = glm::perspective(FOV, aspect, fNear, fFar);
}

// The defination of static camera projection matrix
glm::mat4 Camera::projMatrix = glm::perspective(GlobalVar::FOV,
                                                GlobalVar::aspect,GlobalVar::fNear,GlobalVar::fFar);

