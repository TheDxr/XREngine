#include "DxrApplication.h"
#include "LogManager.h"
#include "Vulkan/Application.h"

int main(int argc, const char *argv[])
{
    LogManager::GetInstance().Init();
    Dxr::Application app{800, 600, 0, 0, "Hello Vulkan!"};
    app.Run();
    // DxrApplication::GetInstance().Run();
    return 0;
}