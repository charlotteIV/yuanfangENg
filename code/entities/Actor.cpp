#include "Actor.h"
#include "../GlobalVar.h"
#include "../Terrain/Terrain.h"
#include "../renderEngine/DisplayManager.h"

#include <iostream>
using namespace std;

const GLfloat fAcceleration  = 6.0f;

Actor::Actor(TextureModel *model, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
    :Entity(model, position, rotation, scale)
{
    SetInstanceUpSpeed(30.0f);
    SetUpWardSpeed(0.0f);
    SetMoveSpeed(20.0f);    // move forward speed
    SetTurnSpeed(20.0f);    // turn around speed
    this->isIntheAir = false;
    this->isMoving = false;
}

void Actor::Transform(Terrain *terrain, GLdouble dt)
{
    // Acceleration
    dt *= fAcceleration;

    if(GlobalVar::keys[GLFW_KEY_UP]){
        Move(dt);
    }
    if(GlobalVar::keys[GLFW_KEY_DOWN]){
        Move(-dt);
    }
    if(GlobalVar::keys[GLFW_KEY_LEFT]){
        TurnAround(dt);
    }
    if(GlobalVar::keys[GLFW_KEY_RIGHT]){
        TurnAround(-dt);
    }
    if(GlobalVar::keys[GLFW_KEY_SPACE]){
        if(!isIntheAir){
            Jump();
            isIntheAir = true;
        }
    }

    // Determine if the player is in the air
    fUpWardSpeed += GRAVITY * (GLfloat)dt;
    GLfloat terrainHeight = terrain->GetTerrainHeight(this->GetPosition().x, this->GetPosition().z);
    IncreasePosition(glm::vec3(0, fUpWardSpeed*dt, 0));
    if(GetPosition().y < terrainHeight){
        fUpWardSpeed = 0.0f;
        SetPosition(1, terrainHeight);
        isIntheAir = false;
    }

    if(isIntheAir || GlobalVar::keys[GLFW_KEY_UP] || GlobalVar::keys[GLFW_KEY_DOWN] ||
                     GlobalVar::keys[GLFW_KEY_LEFT] || GlobalVar::keys[GLFW_KEY_RIGHT]){
        isMoving = true;
    }
}

void Actor::Move(GLdouble dt)
{
    GLdouble distance = fCurrentSpeed * dt;
    GLdouble dx = distance * glm::sin(glm::radians(GetRotation().y));
    GLdouble dz = distance * glm::cos(glm::radians(GetRotation().y));
    IncreasePosition(glm::vec3(dx, 0.0f, dz));
}

void Actor::Jump()
{
    fUpWardSpeed = fInstantUpSpeed;
}

void Actor::TurnAround(GLdouble dt)
{
    IncreaseRotation(glm::vec3(0.0f, fCurrentTurnSpeed * dt, 0.0f));
}

void Actor::SetInstanceUpSpeed(GLfloat speed)
{
    this->fInstantUpSpeed = speed;
}

void Actor::SetUpWardSpeed(GLfloat speed)
{
    this->fUpWardSpeed = speed;
}

void Actor::SetMoveSpeed(GLfloat speed)
{
    this->fCurrentSpeed = speed;
}

void Actor::SetTurnSpeed(GLfloat speed)
{
    this->fCurrentTurnSpeed = speed;
}
