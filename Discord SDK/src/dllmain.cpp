#include <windows.h>

// outsmart GCC's missing-declarations warning
//BOOL WINAPI DllMain(HMODULE, DWORD, LPVOID);
//BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
//
//    {
//    if (fdwReason == DLL_PROCESS_ATTACH) {
//        DisableThreadLibraryCalls(hinstDLL);
//        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WinMain, lpReserved, NULL, NULL);
//    }
//
//    return TRUE;
//   
//}
