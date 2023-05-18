#include "DxrApplication.h"
// #include <windows.h>
// extern "C"
// {
//     _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// }
int main(int argc, const char* argv[]) {
    DxrApplication::GetInstance().Run();
    return 0;
}