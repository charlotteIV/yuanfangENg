#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include "glew/glew.h"
#include "glfw/glfw3.h"

#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
///\! global varibale declaration with extern
///
namespace GlobalVar {

    // Window pointer
    extern GLFWwindow *glfwWindow;

    // Window size
    extern GLuint WINDOWWIDTH;
    extern GLuint WINDOWHEIGHT;

    // View frustum
    extern GLfloat FOV;
    extern GLfloat aspect;
    extern GLfloat fNear;
    extern GLfloat fFar;

    // Key states
    extern bool keys[1024];

    // Mouse wheel and position
    extern GLfloat bMouseWheelY;
    extern GLdouble dCursorRestpos[2];

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///!\ OpenGL scene configuration
    // The max-number of lights in cuurent shader
    extern const GLuint MAX_LIGHTS;

    // background color
    extern GLfloat bg_RED, bg_GREEN, bg_BLUE;

    // SkyBox Size
    extern const GLfloat fSkyBox_SIZE;

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///!\ Shader files
    // General shaders
    extern const string STATIC_VERTEX_FILE;
    extern const string STATIC_FRAGMENT_FILE;

    // Terrain shaders
    extern const string TERRAIN_VERTEX_FILE;
    extern const string TERRAIN_FRAGMENT_FILE;

    // SkyBox Shaders
    extern const string SKYBOX_VERTEX_FILE;
    extern const string SKYBOX_FRAGMENT_FILE;

}

#endif // GLOBALVAR_H
