#include "DxrApplication.h"
#include "LogManager.h"
#include "Vulkan/Application.h"

int main(int argc, const char* argv[]) {
    LogManager::GetInstance().Init();
    Dxr::Application app;
    app.Run();
    //DxrApplication::GetInstance().Run();
    return 0;
}