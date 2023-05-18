#pragma once

#include <GLFW/glfw3.h>
#include "IGUI.h"
class EmbeddedUI : public IGUI
{
public:
    explicit EmbeddedUI(GLFWwindow *window);
    ~EmbeddedUI() override = default;
    void Init() override;
    void Render() override;
    void RenderLoadPanel();

    bool ShowDemoWindow    = true;
    bool ShowAnotherWindow = true;
private:
    GLFWwindow *mWindow;


};
