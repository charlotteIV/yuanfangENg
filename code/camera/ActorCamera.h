#ifndef ACTORCAMERA_H
#define ACTORCAMERA_H

#include "Camera.h"

class Actor;
class ActorCamera : public Camera
{
public:
    ActorCamera(Actor *actor);

    void Update();

    // update matrix
    void UpdateViewMatrix();

    // calculate vertical distance
    GLfloat CalculateVerticalDistance();

    // calculate horizontal distance
    GLfloat CalculateHorizontalDistance();

    // Calculate new camera position based on horizontal and vertical distance
    void CalculateCameraPosition(GLfloat horizDist, GLfloat verticDist);

private:
    Actor *actor;        // Actor pointer
    GLfloat fDistanceFromActor; // the distance between actor and camera
    GLfloat fAngleAroundPlayer; // the angler around the player
};

#endif // ACTORCAMERA_H
