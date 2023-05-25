#pragma once

#include <GLFW/glfw3.h>
#include "Interface/IGuiInterface.h"
class EmbeddedUI : public IGuiInterface
{
public:
    explicit EmbeddedUI(GLFWwindow *window);
    ~EmbeddedUI() override = default;
    void init() override;
    void render() override;
    void RenderLoadPanel();

    bool ShowDemoWindow    = true;
    bool ShowAnotherWindow = true;
private:
    GLFWwindow *mWindow;


};
