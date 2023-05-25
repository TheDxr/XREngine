#pragma once

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>
#include <string>

namespace dxr::gl {

    class Window {
    public:
        Window(int width, int height, const std::string &title = "Application");

        ~Window() = default;

        Window(const Window &) = delete;

        Window &operator=(const Window &) = delete;

        void setWindowPos(int x, int y);

        GLFWwindow *getHandle() { return window; }

        int getWidth();

        int getHeight();

        float getWindowRatio();

        bool windowDimensionChanged();

        void detectWindowDimensionChange();

    private:
        bool dimensionChanged = false;
        GLFWwindow *window;
        int width;
        int height;
    };

} // namespace Dxr::gl
