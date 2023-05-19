#include <GLFW/glfw3.h>
#include <functional>

#include "InputSystem.h"

// Slow and inefficient
void InputSystem::ProcessKeyInput(const std::function<void(int)> &keyCallback)
{
    for(int i = 0; i < GLFW_KEY_LAST; i++) {
        if(glfwGetKey(mpWindow, i) == GLFW_PRESS) {
            keyCallback(i);
        }
    }
}
InputSystem::InputSystem(GLFWwindow *window) : mpWindow(window)
{
    glfwSetKeyCallback(mpWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    });
    //    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //    glfwSetCursorPosCallback(window, mouse_callback);
    //    glfwSetScrollCallback(window, scroll_callback);
}
void InputSystem::EnableCursor() { glfwSetInputMode(mpWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
void InputSystem::DisableCursor() { glfwSetInputMode(mpWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
void InputSystem::SetGlfwKeyCallback(GLFWkeyfun callback) { glfwSetKeyCallback(mpWindow, callback); }
void InputSystem::SetGlfwCursorPosCallback(GLFWcursorposfun callback) { glfwSetCursorPosCallback(mpWindow, callback); }
void InputSystem::SetGlfwScrollCallback(GLFWscrollfun callback) { glfwSetScrollCallback(mpWindow, callback);}
