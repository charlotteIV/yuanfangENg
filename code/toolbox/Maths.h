#ifndef MATHS_H
#define MATHS_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
using namespace std;

static glm::mat4 Identity = glm::mat4();

class Maths
{
public:
    Maths();
    static glm::mat4 CreateTransformationMatrix(const glm::vec3 &transform, const glm::vec3 &rotate, const glm::vec3 &scale){

        // transform in reverse order
        glm::mat4 matrix = glm::mat4();
        matrix = glm::translate(matrix, transform);
        if(rotate.x != 0.0f){
            matrix = glm::rotate(matrix, glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        if(rotate.y != 0.0f){
            matrix = glm::rotate(matrix, glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if(rotate.z != 0.0f){
            matrix = glm::rotate(matrix, glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
        }

        matrix = glm::scale(matrix, scale);

        return matrix;
    }

    static glm::mat4 ModelViewProjection(const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model){
        // Just ordered multiplied
        return proj * view * model;
    }

    static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
        float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
        float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
        float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
        float l3 = 1.0f - l1 - l2;
        return l1 * p1.y + l2 * p2.y + l3 * p3.y;
    }

};

#endif // MATHS_H
