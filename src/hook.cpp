//
// Created by henryj on 27/6/2021.
//

#include <cstdint>

#include "hook.h"
#include "memory.h"
#include "pvz.h"

#include <iostream>
#include <cmath>

#include "global.h"

int tick_counter = 0;

void Script() {
    tick_counter++;
    std::cout << global::base_ptr << std::endl;
    if (tick_counter < 800) return;
    if (tick_counter % 100) return;
    pvz::Click(300, 300, 1);
}



void hook::install(Memory &memory) {
    auto shim = (uintptr_t)memory.Alloc(4096);
    /*
    0x415945:
    call shim
    */
    uint8_t call_shim[5];

    // call shim
    call_shim[0] = 0xe8;
    (int32_t &)call_shim[1] = (int32_t)shim - (MAIN_LOOP_CALL_ADDRESS + 5);

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
    (int &)patch[2] = (uintptr_t)Script - (shim + 1 + 5);

    // pop ebx
    patch[6] = 0x5b;

    // call 4130d0
    patch[7] = 0xe8;
    (int &)patch[8] = MAIN_LOOP_FUNC_ADDRESS - (shim + 7 + 5);

    // ret
    patch[12] = 0xc3;

    memory.Write(shim, sizeof(patch), patch);
    global::base_ptr = *(pvz::Base **)BASE_PTR_ADDRESS;
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
}
