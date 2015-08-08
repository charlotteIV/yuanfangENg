#include "FreeCamera.h"
#include "../GlobalVar.h"
#include "../renderEngine/DisplayManager.h"
#include "glm/gtx/euler_angles.hpp"


FreeCamera::FreeCamera(const glm::vec3 &position, const glm::vec3 &look)
    :Camera(){
    this->position = position;

    this->fRoll  = 0.0f;
    this->fPitch =  glm::degrees(glm::atan(look.y / look.z));
    this->fYaw   =  180.0f + glm::degrees(glm::atan(look.x / look.z));

    // Without default rotating, there are small value errors
    Rotate(0.0f, 0.0f, 0.0f);
}

void FreeCamera::Update()
{
    float deltaT = 0.01f;
    static GLfloat ACCELERATION = 2.0f;

    if(GlobalVar::keys[GLFW_KEY_RIGHT_CONTROL])
        deltaT *= ACCELERATION;
    /* Camera movment*/
    if(GlobalVar::keys[GLFW_KEY_W]) MoveForward(deltaT);
    if(GlobalVar::keys[GLFW_KEY_S]) MoveForward(-deltaT);

    if(GlobalVar::keys[GLFW_KEY_A]) MoveRight(-deltaT);
    if(GlobalVar::keys[GLFW_KEY_D]) MoveRight(deltaT);

    if(GlobalVar::keys[GLFW_KEY_R]) MoveUp(deltaT);
    if(GlobalVar::keys[GLFW_KEY_F]) MoveUp(-deltaT);

    // Rotate camera
    if(GlobalVar::keys[GLFW_MOUSE_BUTTON_LEFT]){
        // Retrieve cursor current position
        GLdouble newposX, newposY;
        glfwGetCursorPos(GlobalVar::glfwWindow, &newposX, &newposY);

        static GLfloat Rx=0.0f, Ry=0.0f;
        static GLfloat MOUSESENSITIVTY =  0.1f;
        Rx = (GLfloat)(GlobalVar::dCursorRestpos[0] - newposX) * MOUSESENSITIVTY;
        Ry = (GLfloat)(newposY - GlobalVar::dCursorRestpos[1]) * MOUSESENSITIVTY;
        Rotate(Rx, Ry, 0);

        // Save last cursor position
        GlobalVar::dCursorRestpos[0] = newposX;
        GlobalVar::dCursorRestpos[1] = newposY;
    }
}

void FreeCamera::Rotate(const float yaw, const float pitch, const float roll)
{
    // Calculate the rotation matrix
    glm::mat4 R = glm::yawPitchRoll(glm::radians(this->fYaw += yaw),
                                    glm::radians(this->fPitch += pitch), glm::radians(this->fRoll += roll));

    viewMatrix = glm::lookAt(position, position + glm::vec3(R*glm::vec4(0,0,1,0)),glm::vec3(R*glm::vec4(0,1,0,0)));
}

void FreeCamera::MoveForward(GLfloat dt)
{
    // Retrieve Up direction
    glm::vec3 Forward = glm::vec3(-viewMatrix[0][2],-viewMatrix[1][2],-viewMatrix[2][2]);
    // Update position and assign it to the view matrix
    position += Forward * SPEEDT * dt;
    viewMatrix[3][2] = glm::dot(Forward,position);
}

void FreeCamera::MoveRight(GLfloat dt)
{
    // Retrieve Right direction
    glm::vec3 Right = glm::vec3(viewMatrix[0][0],viewMatrix[1][0],viewMatrix[2][0]);
    // Update position and assign it to the view matrix
    position += Right * SPEEDT * dt;
    viewMatrix[3][0] = -glm::dot(Right,position);
}

void FreeCamera::MoveUp(GLfloat dt)
{
    // Retrieve Up direction
    glm::vec3 Up = glm::vec3(viewMatrix[0][1],viewMatrix[1][1],viewMatrix[2][1]);
    // Update position and assign it to the view matrix
    position += Up * SPEEDT * dt;
    viewMatrix[3][1] = -glm::dot(Up,position);
}
