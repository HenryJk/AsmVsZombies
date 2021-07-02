#include "Windows.h"
#include "hook.h"
#include "memory.h"
#include "pvz.h"


BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    Memory memory;
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            memory.OpenSelf();
            hook::install(memory);
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            Sleep(10);
            hook::uninstall(memory);
            break;
        default:
            return FALSE;
    }
    return TRUE;// successful
}
