// #include "DxrApplication.h"
// #include "LogManager.h"
#include <random>
#include <iostream>
#include "../UnitTest.h"

#include "Components/EntityKernel.h"
#include "Components/Transform.h"
#include "Core/Command.h"
#include "Core/Ecs.h"
#include "Systems/PhysicsSystem.h"
#include "Timer.h"
#include "OpenGL/Application.h"
//#include "Vulkan/Application.h"
using namespace std;
int main()
{
   dxr::gl::Application app{800, 600, 0, 0, "Hello GL"};
   app.run();
}
//    Dxr::LogManager::Init();
//    Dxr::Application app{800, 600, 0, 0, "Hello Vulkan!"};
//    app.Run();
//    DxrApplication::GetInstance().Run();
