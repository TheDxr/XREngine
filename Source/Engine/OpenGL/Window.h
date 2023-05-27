#pragma once


#include <string>

struct GLFWwindow;
namespace dxr::gl {

    class Window {
    public:
        Window(int width, int height, const std::string &title = "Application");

        ~Window() = default;

        Window(const Window &) = delete;

        Window &operator=(const Window &) = delete;

        void setWindowPos(int x, int y);


        GLFWwindow *getHandle() { return window_; }

        int getWidth();

        int getHeight();

        float getWindowRatio();

        bool windowDimensionChanged();

        void detectWindowDimensionChange();

    private:
        bool dimensionChanged = false;
        GLFWwindow *window_;
        int width;
        int height;
    };

} // namespace Dxr::gl
