#include "Windows.h"
#include <avz.h>
#include <core.h>
#include "hook.h"
#include <memory.h>


BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    Memory memory;
    Core::main_address = (void *) (memory.ReadMemory<uint32_t>({BASE_ADDRESS}) + 0x768);
    Core::main_address = (void *) (*(uint32_t **) BASE_ADDRESS)[0x768 / 4];
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            memory.OpenSelf();
            hook::install(memory);
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            AvZ::__Exit();
            Sleep(10);
            hook::uninstall(memory);
            break;
        default:
            return FALSE;
    }
    return TRUE;// successful
}
