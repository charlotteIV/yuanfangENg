#include "DisplayManager.h"
#include "glfw/glfw3.h"
#include "../GlobalVar.h"
#include "../camera/Camera.h"
#include <iostream>
using namespace std;


DisplayManager::DisplayManager(string windowTitle, GLuint width, GLuint height)
{
    this->windowTitile  = windowTitle;
    this->iWindowWidth  = width;
    this->iWindowHeight = height;
    // Set projection matrix
    Camera::SetProjectionMatrix(GlobalVar::FOV, (GLfloat)width / (GLfloat)height, GlobalVar::fNear, GlobalVar::fFar);
}

DisplayManager::~DisplayManager()
{
    CloseDisplay();
}

void DisplayManager::CreateDisplay()
{
    /* INIT GLFW */
    if(!glfwInit()){
        /* If initialize failed */
        std::cout<<"ERROR::GLFW INIT FAILED!"<<std::endl;
        exit(1);
    }

    /* GLFW CONFIGURATION */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* CREATE WINDOW */
    GlobalVar::glfwWindow = glfwCreateWindow(iWindowWidth, iWindowHeight, windowTitile.c_str(), NULL, NULL);
    if(!GlobalVar::glfwWindow){
        /* If create window failed */
        std::cout<<"ERROR::GLFW WINDOW CREATION FAILED!"<<std::endl;
        glfwTerminate();
        exit(2);
    }

    /* Let the window be the current */
    glfwMakeContextCurrent(GlobalVar::glfwWindow);

    /* Register key and mouse button event call back */
    glfwSetKeyCallback(GlobalVar::glfwWindow, key_press_callback);
    glfwSetScrollCallback(GlobalVar::glfwWindow, mouse_wheel_callback);
    glfwSetMouseButtonCallback(GlobalVar::glfwWindow, mouse_button_callback);

    /* OPENGL INITIALIZATION */
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        /* If glew initialize failed */
        std::cout<<"ERROR::GLEW INITIALIZATION FAILED!"<<std::endl;
        exit(3);
    }

	/*
	const GLubyte * name = glGetString(GL_VENDOR);
	const GLubyte * biaoshifu = glGetString(GL_RENDERER);
	const GLubyte * OpenGLVersion = glGetString(GL_VERSION);
	const GLubyte * gluVersion = gluGetString(GLU_VERSION);
	printf("OpenGL实现厂商的名字：%s\n", name);
	printf("渲染器标识符：%s\n", biaoshifu);
	printf("OOpenGL实现的版本号：%s\n", OpenGLVersion);
	printf("OGLU工具库版本：%s\n", gluVersion);
	*/

    glViewport(0, 0, iWindowWidth, iWindowHeight);
    glEnable(GL_DEPTH_TEST);

    // Get the time since window created
    lastFrameTime = glfwGetTime();
}

void DisplayManager::UpdateDisplay()
{
    // SWAP BUFFERS
    glfwSwapBuffers(GlobalVar::glfwWindow);

    // In seconds
    GLdouble currentFrameTime = glfwGetTime();
    deltaT = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}

void DisplayManager::CloseDisplay()
{
    glfwTerminate();
}

void DisplayManager::SetWindowPosition(GLuint x, GLuint y)
{
    glfwSetWindowPos(GlobalVar::glfwWindow, x, y);
}

GLint DisplayManager::isWindowShouldClose()
{
    return glfwWindowShouldClose(GlobalVar::glfwWindow);
}

//! Must be global or static since glfw use it as callback
void key_press_callback(GLFWwindow *w, GLint key, GLint scancode, GLint action, GLint modes)
{
    // close window
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(w, true);

    // Handle camera motion
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            GlobalVar::keys[key] = true;
        else if (action == GLFW_RELEASE)
            GlobalVar::keys[key] = false;
    }
}

// Mouse or touchpad scroll callback
void mouse_wheel_callback(GLFWwindow* w, GLdouble xoffset, GLdouble yoffset)
{
    // Only enable here, please disbale in your own requirement
    GlobalVar::bMouseWheelY = (GLfloat)yoffset;
}

/* Mouse button press event */
void mouse_button_callback(GLFWwindow* w, int button, int action, int mods)
{
    if(action == GLFW_PRESS){
        GlobalVar::keys[button] = true;
        glfwGetCursorPos(w, &GlobalVar::dCursorRestpos[0], &GlobalVar::dCursorRestpos[1]);
    }else if(action == GLFW_RELEASE){
        GlobalVar::keys[button] = false;
    }
}
