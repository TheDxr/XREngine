#include "Application.h"

#include <iostream>
#include <stdexcept>
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>


Application::Application()
    : mState(stateReady), mWidth(512), mHeight(512), mTitle("Application")
{
    spdlog::info("GLFW initialized");
    // initialize the GLFW library
    if(!glfwInit()) {
        throw std::runtime_error("Couldn't init GLFW");
    }

    // setting the opengl version
    int major = 3;
    int minor = 2;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create the window
    mpWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);
    if(!mpWindow) {
        glfwTerminate();
        throw std::runtime_error("Couldn't create a window");
    }
    
    glfwMakeContextCurrent(mpWindow);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error(std::string("Could initialize GLAD"));
    }

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);
    
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;

    // opengl configuration
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

    // vsync
    // glfwSwapInterval(false);
}

Application::Application(int width, int height,int posX, int posY, std::string title)
    : mState(stateReady), mWidth(width), mHeight(height), mTitle(title)
{
    spdlog::info("GLFW initialized");
    // 初始化 GLFW
    if(!glfwInit()) {
        throw std::runtime_error("Couldn't init GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    mpWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!mpWindow) {
        glfwTerminate();
        throw std::runtime_error("Couldn't create a window");
    }
	glfwSetWindowPos(mpWindow, posX, posY);
    glfwMakeContextCurrent(mpWindow);
    // 载入GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error(std::string("Could initialize GLAD"));
    }
    // 获取版本信息
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version  = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;
}

GLFWwindow* Application::GetWindow() { return mpWindow; }

void Application::Exit() { mState = stateExit; }

float Application::GetFrameDeltaTime() { return mDeltaTime; }

float Application::GetTime() const { return mTime; }

void Application::Run()
{
    mState = stateRun;

    // Make the window's context current
    glfwMakeContextCurrent(mpWindow);

    mTime = static_cast<float>(glfwGetTime());

    while(mState == stateRun) {
        // compute new mTime and delta mTime
        float t   = static_cast<float>(glfwGetTime());
        mDeltaTime = t - mTime;
        mTime      = t;

        // detech window related changes
        DetectWindowDimensionChange();
        if(glfwWindowShouldClose( GetWindow()))
            Exit();
        // execute the frame code
        Update();

        // Swap Front and Back buffers (double buffering)
        glfwSwapBuffers(mpWindow);

        // Pool and process events
        glfwPollEvents();
    }

    glfwTerminate();
}

void Application::DetectWindowDimensionChange()
{
    int w, h;
    glfwGetWindowSize(GetWindow(), &w, &h);
    mDimensionChanged = (w != mWidth || h != mHeight);
    if(mDimensionChanged) {
        mWidth = w;
        mHeight = h;
        glViewport(0, 0, mWidth, mHeight);
    }
}

void Application::Update() { std::cout << "[INFO] : Update" << std::endl; }

int Application::GetWidth() { return mWidth; }

int Application::GetHeight() { return mHeight; }

float Application::GetWindowRatio() { return float(mWidth) / float(mHeight); }

bool Application::WindowDimensionChanged() { return mDimensionChanged; }
