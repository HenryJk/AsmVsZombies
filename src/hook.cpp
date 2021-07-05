//
// Created by henryj on 27/6/2021.
//

#include <cstdint>

#include "cheat.h"
#include "hook.h"
#include "reference.h"
#include "script.h"

namespace {
    void *shim;
}

void hook::install(Memory &memory) {
    shim = memory.Alloc(4096);
    /*
    0x415945:
    call shim
    */
    uint8_t call_shim[5];

    // call shim
    call_shim[0] = '\xE8';
    (uint32_t &)call_shim[1] = (uint32_t)shim - (MAIN_LOOP_CALL_ADDRESS + 5);

    memory.Write(MAIN_LOOP_CALL_ADDRESS, sizeof(call_shim), call_shim);

    /*
    shim:
    push ebx
    call _script
    pop ebx
    call 0x4130d0
    ret
    */
    uint8_t patch[13];

    // push ebx
    patch[0] = 0x53;

    // call _script
    patch[1] = 0xe8;
    (uint32_t &)patch[2] = (uintptr_t)script::OnTick - ((uint32_t)shim + 1 + 5);

    // pop ebx
    patch[6] = 0x5b;

    // call 4130d0
    patch[7] = 0xe8;
    (uint32_t &)patch[8] = MAIN_LOOP_FUNC_ADDRESS - ((uint32_t)shim + 7 + 5);

    // ret
    patch[12] = 0xc3;

    memory.Write((uint32_t)shim, sizeof(patch), patch);
    script::OnHook();
}

void hook::uninstall(Memory &memory) {
    /*
    0x415945:
    call 0x4130d0
    */
    uint8_t call_shim[5];

    // call shim
    call_shim[0] = 0xe8;
    (int &)call_shim[1] = MAIN_LOOP_FUNC_ADDRESS - (MAIN_LOOP_CALL_ADDRESS + 5);

    memory.Write(MAIN_LOOP_CALL_ADDRESS, sizeof(call_shim), call_shim);
    cheat::RemoveAllCheats();
    memory.Free(shim);
}
