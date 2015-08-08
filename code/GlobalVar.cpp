#include "GlobalVar.h"

/////////////////////////////////////////////////////////////////////////////////////////
///\! global varibale definationn
///
namespace GlobalVar {

    // Window pointer
    GLFWwindow *glfwWindow = NULL;

    // Window size
    GLuint WINDOWWIDTH = 960;
    GLuint WINDOWHEIGHT = 620;

    // View frustum
    GLfloat FOV = 45.0f;
    GLfloat aspect = (GLfloat)WINDOWWIDTH / WINDOWHEIGHT;
    GLfloat fNear = 0.1f;
    GLfloat fFar = 1000.0f;

    // Key states
    bool keys[1024] = {GL_FALSE};

    // Mouse wheel and position
    GLfloat bMouseWheelY = 0.0f;
    GLdouble dCursorRestpos[2] = {0.0};

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///!\ OpenGL scene configuration
    // The max-number of lights in cuurent shader
    const GLuint MAX_LIGHTS = 4;

    // background color (also known as sky color)
    GLfloat bg_RED = 0.2f, bg_GREEN = 0.2f, bg_BLUE = 0.2f;

    // SkyBox Size
    const GLfloat fSkyBox_SIZE = 500.0f;

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///!\ Shader files
    // General shader
    const string STATIC_VERTEX_FILE   = "../res/shaders/Static.vert";
    const string STATIC_FRAGMENT_FILE = "../res/shaders/Static.frag";

    // Terrain shaders
    const string TERRAIN_VERTEX_FILE   = "../res/shaders/Terrain.vert";
    const string TERRAIN_FRAGMENT_FILE = "../res/shaders/Terrain.frag";

    // Skybox shaders
    const string SKYBOX_VERTEX_FILE   = "../res/shaders/Skybox.vert";
    const string SKYBOX_FRAGMENT_FILE = "../res/shaders/Skybox.frag";

}
