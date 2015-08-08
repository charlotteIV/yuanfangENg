#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

const GLfloat GRAVITY = -50.0f;
class Terrain;
class Actor : public Entity
{
public:
    Actor(TextureModel *model, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

    // translate the player
    void Transform(Terrain* terrain, GLdouble dt);

    void Move(GLdouble dt);
    void Jump();
    void TurnAround(GLdouble dt);

    // Set Speed
    void SetInstanceUpSpeed(GLfloat speed);
    void SetUpWardSpeed(GLfloat speed);
    void SetMoveSpeed(GLfloat speed);
    void SetTurnSpeed(GLfloat speed);

    // Is actor moving
    void SetIsActorMoving(bool isMoving){
        this->isMoving = isMoving;
    }
    bool IsActorMoving() { return isMoving; }

private:
    GLfloat fUpWardSpeed;
    GLfloat fInstantUpSpeed;
    GLfloat fCurrentSpeed;
    GLfloat fCurrentTurnSpeed;

    bool isIntheAir;    // If the actor has already jumped
    bool isMoving;        // If the actor is moving
};

#endif // PLAYER_H
