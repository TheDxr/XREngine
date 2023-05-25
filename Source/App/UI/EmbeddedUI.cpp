#include "EmbeddedUI.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


EmbeddedUI::EmbeddedUI(GLFWwindow *window) : mWindow(window) {

}

void EmbeddedUI::init() {
#pragma region 设置gui
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
#pragma endregion

}
void EmbeddedUI::RenderLoadPanel()
{
    //const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    /*ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);*/

    ImGui::Text("Load Obj from Path");
    ImGui::SameLine();
    ImGui::Text("Load Texture from Path");
    ImGui::SameLine();
}

void EmbeddedUI::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if(ShowDemoWindow)
        ImGui::ShowDemoWindow(&ShowDemoWindow);
    // 2. Show a simple window that we create ourselves. We Use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;
        auto clear_color  = (1.0f, 0.8f, 0.8f, 1.0f);
        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");          // Display some text (you can Use a format strings too)
        ImGui::Checkbox("Demo Window", &ShowDemoWindow); // Edit bools storing our window open/close mState
        ImGui::Checkbox("Another Window", &ShowDemoWindow);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f

        ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

        if(ImGui::Button("Button"))
            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }
    ImGui::Render();
    //glfwGetFramebufferSize(GetWindow(), &width, &height);
    //glViewport(0, 0, width, height);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

