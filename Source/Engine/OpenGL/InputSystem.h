#pragma once
#include <functional>
#include <GLFW/glfw3.h>

class InputSystem
{
public:
    InputSystem() = default;
    ~InputSystem() = default;
    explicit InputSystem(GLFWwindow *window);
    void ProcessKeyInput(const std::function<void(int)>& keyCallback);
    void EnableCursor();
    void DisableCursor();
    void SetGlfwKeyCallback(GLFWkeyfun callback);
    void SetGlfwCursorPosCallback(GLFWcursorposfun callback);
    void SetGlfwScrollCallback(GLFWscrollfun callback);
private:
    GLFWwindow *mpWindow;
};
