#include "cheats.h"

BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            HANDLE handle;
            handle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) &cheatLoop, hModule, 0, nullptr);
            CloseHandle(handle);
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
        default:
            break;
    }
    return TRUE;
}
