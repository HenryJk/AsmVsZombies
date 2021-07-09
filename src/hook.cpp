//
// Created by henryj on 27/6/2021.
//

#include <cstdint>

#include "hook.h"
#include "reference.h"
#include "script.h"

namespace {
    uint8_t *shim;

    void (*on_tick_handler)(pvz::Game *) = nullptr;
    void (*on_zombie_created_handler)(pvz::Zombie *) = nullptr;

    void all_scripts(pvz::Game *game_ptr) {
        if (on_zombie_created_handler != nullptr) {
            for (int i = 0; i < game_ptr->zombie_count; i++) {
                auto &zombie = game_ptr->zombie_ptr[i];
                if (zombie.id >> 16 == 0) continue;
                if (zombie.age == 1) on_zombie_created_handler(&zombie);
            }
        }
        if (on_tick_handler != nullptr) on_tick_handler(game_ptr);
    }
}

void hook::Install() {
    shim = (uint8_t *) VirtualAlloc(nullptr, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    shim[0] = 0x53; // push ebx;
    shim[1] = 0xE8; // call [all_scripts]
    (uintptr_t &)shim[2] = (uintptr_t)all_scripts - ((uintptr_t)shim + 6);
    shim[6] = 0x5b; // pop ebx;
    shim[7] = 0xE8; // call [MAIN_LOOP_FUNC_ADDRESS]
    (uintptr_t &)shim[8] = MAIN_LOOP_FUNC_ADDRESS - ((uintptr_t)shim + 12);
    shim[12] = 0xC3; // ret

    uint8_t patch[5];
    patch[0] = 0xE8; // call [shim]
    (uintptr_t &)patch[1] = (uintptr_t)shim - (MAIN_LOOP_CALL_ADDRESS + 5);
    WriteProcessMemory(GetCurrentProcess(), (void *)MAIN_LOOP_CALL_ADDRESS, patch, 5, nullptr);
}

void hook::RegisterOnTickHandler(void (*handler)(pvz::Game *)) {
    on_tick_handler = handler;
}

void hook::RegisterOnZombieCreatedHandler(void (*handler)(pvz::Zombie *)) {
    on_zombie_created_handler = handler;
}


void hook::Uninstall(Memory &memory) {
    /*
    0x415945:
    call 0x4130d0
    */
    uint8_t call_shim[5];

    // call shim
    call_shim[0] = 0xe8;
    (int &)call_shim[1] = MAIN_LOOP_FUNC_ADDRESS - (MAIN_LOOP_CALL_ADDRESS + 5);

    memory.Write(MAIN_LOOP_CALL_ADDRESS, sizeof(call_shim), call_shim);
    memory.Free(shim);
}
