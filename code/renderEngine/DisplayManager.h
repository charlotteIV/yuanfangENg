#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <string>
using std::string;

#include "glew/glew.h"

struct GLFWwindow;
class DisplayManager
{
public:
    DisplayManager(string windowTitle, GLuint width = 960, GLuint height = 620);
    ~DisplayManager();

    void CreateDisplay();   // INITIALIZE WINDOW AND GLEW
    void UpdateDisplay();   // UPDATE GRAPHICS
    void CloseDisplay();    // CLOSE GLFW WINDOW

    // determine whether the window should close
    GLint isWindowShouldClose();

    // set window postion
    void SetWindowPosition(GLuint x, GLuint y);

    // Retrieve the time between two frames
    GLdouble GetFrameTimeSeconds() { return deltaT; }


private:
    string windowTitile;    // window title
    GLuint iWindowWidth;    // window width
    GLuint iWindowHeight;   // window height

    GLdouble lastFrameTime;
    GLdouble deltaT;         // the time escaped between two frame
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///! GLOBAL FUNCTIONS
// mouse button event
void mouse_button_callback(GLFWwindow* w, int button, int action, int mods);

// mouse wheel event
void mouse_wheel_callback(GLFWwindow* w, GLdouble xoffset, GLdouble yoffset);

// key press event
void key_press_callback(GLFWwindow *w, GLint key, GLint scancode, GLint action, GLint modes);

#endif // DISPLAYMANAGER_H
