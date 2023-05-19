#pragma once

#include <string>

struct GLFWwindow;
class Application
{
public:
	Application();
	Application(int width, int height, int posX= 0, int posY = 0,
	            std::string title = "Application");
	virtual ~Application() = default;
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&&) = delete;

	// get the window id
	GLFWwindow* GetWindow();

	// window control
	void Exit();

	// delta mTime between frame and mTime from beginning
	float GetFrameDeltaTime();
	float GetTime() const;

	// application Run
	void Run();

	// Application information
	int GetWidth();
	int GetHeight();
	float GetWindowRatio();
	bool WindowDimensionChanged();

protected:
	enum State { stateReady, stateRun, stateExit };

	State mState;
	virtual void Update();
		// Time:
	float mTime = 0.0f;
	float mDeltaTime = 0.0f;

	// Dimensions:
	int mWidth;
	int mHeight;
	std::string mTitle;
	bool mDimensionChanged = false;
	void DetectWindowDimensionChange();
private:
	GLFWwindow* mpWindow;
};
