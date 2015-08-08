#include "ActorCamera.h"
#include "../entities/Actor.h"
#include "../GlobalVar.h"
#include "glm/gtx/euler_angles.hpp"
#include <iostream>
using namespace std;

ActorCamera::ActorCamera(Actor *actor)
    :Camera(){
    this->actor = actor;
    this->fDistanceFromActor = 50.0f;
    this->fAngleAroundPlayer = 0.0f;
    this->fPitch = 20.0f;
    // Update view matrix once
    UpdateViewMatrix();
}

void ActorCamera::Update()
{
    // Determine if there is a need to update view matrix
    bool bUpdateViewMatrix = false;

    // calculate zoom
    if(GlobalVar::bMouseWheelY != 0.0f){
        this->fDistanceFromActor += GlobalVar::bMouseWheelY * 2.0f;
        GlobalVar::bMouseWheelY = 0.0f;
        bUpdateViewMatrix = true;
    }

    // Calculate pitch
    if(GlobalVar::keys[GLFW_MOUSE_BUTTON_LEFT] || GlobalVar::keys[GLFW_MOUSE_BUTTON_RIGHT]){
        // Retrieve cursor current position
        GLdouble newposx, newposy;
        glfwGetCursorPos(GlobalVar::glfwWindow, &newposx, &newposy);

        static GLfloat MOUSESENSITIVTY =  0.1f;

        if(GlobalVar::keys[GLFW_MOUSE_BUTTON_LEFT]){
        // Calculate yaw (meaning somehow)
            this->fAngleAroundPlayer -= (GLfloat)(GlobalVar::dCursorRestpos[0] - newposx) * MOUSESENSITIVTY;
        }else{
        // Calculate Pitch
            this->fPitch -= (GLfloat)(newposy - GlobalVar::dCursorRestpos[1]) * MOUSESENSITIVTY;
        }

        // Save last cursor position
        GlobalVar::dCursorRestpos[0] = newposx;
        GlobalVar::dCursorRestpos[1] = newposy;

        bUpdateViewMatrix = true;
    }

    // Update View matrix
    if(bUpdateViewMatrix  || this->actor->IsActorMoving() ){
        UpdateViewMatrix();
        this->actor->SetIsActorMoving(false);
    }
}

void ActorCamera::UpdateViewMatrix()
{
    // Real am yaw degree
    this->fYaw = (this->actor->GetRotation().y + fAngleAroundPlayer);

    // Calculate new camera position
    CalculateCameraPosition(CalculateHorizontalDistance(), CalculateVerticalDistance());
    // Calculate the rotation matrix
    glm::mat4 R = glm::yawPitchRoll(glm::radians(this->fYaw),
                                    glm::radians(this->fPitch), glm::radians(this->fRoll));

    viewMatrix = glm::lookAt(position, position + glm::vec3(R*glm::vec4(0,0,1,0)),glm::vec3(R*glm::vec4(0,1,0,0)));
}

void ActorCamera::CalculateCameraPosition(GLfloat horizDist, GLfloat verticDist)
{
    // Total angle
    GLfloat theta = glm::radians(actor->GetRotation().y + fAngleAroundPlayer);
    GLfloat offsetX = horizDist * glm::sin(theta);
    GLfloat offsetZ = horizDist * glm::cos(theta);
    position.x = this->actor->GetPosition().x - offsetX;
    position.y = this->actor->GetPosition().y + verticDist;
    position.z = this->actor->GetPosition().z - offsetZ;
}

GLfloat ActorCamera::CalculateVerticalDistance()
{
    return fDistanceFromActor * glm::sin(glm::radians(fPitch));
}

GLfloat ActorCamera::CalculateHorizontalDistance()
{
    return fDistanceFromActor * glm::cos(glm::radians(fPitch));
}
