//
// Created by henryj on 27/6/2021.
//

#include <avz.h>
#include <cstdint>

#include "hook.h"
#include "memory.h"

void hook::install(Memory &memory) {
    auto addr = (uintptr_t)memory.Alloc(4096);
    /*
    0x415945:
    call addr
    */
    uint8_t call_addr[5];

    // call addr
    call_addr[0] = 0xe8;
    (int32_t &)call_addr[1] = addr - (0x415945 + 5);

    memory.Write(0x415945, sizeof(call_addr), call_addr);

    /*
    addr:
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
    (int &)patch[2] = (uintptr_t)Script - (addr + 1 + 5);

    // pop ebx
    patch[6] = 0x5b;

    // call 4130d0
    patch[7] = 0xe8;
    (int &)patch[8] = 0x4130d0 - (addr + 7 + 5);

    // ret
    patch[12] = 0xc3;

    memory.Write(addr, sizeof(patch), patch);
}

void hook::uninstall(Memory &memory) {
    /*
    0x415945:
    call 0x4130d0
    */
    uint8_t call_addr[5];

    // call addr
    call_addr[0] = 0xe8;
    (int &)call_addr[1] = 0x4130d0 - (0x415945 + 5);

    memory.Write(0x415945, sizeof(call_addr), call_addr);
}
