//
// Created by henryj on 2/7/2021.
//

#include <memoryapi.h>
#include <processthreadsapi.h>
#include <winnt.h>

#include "cheat.h"
#include "pvz.h"
#include "script.h"

namespace {

}

void script::OnTick(void (*handler)(pvz::Game *)) {
    auto hook             = (uint8_t *) VirtualAlloc(nullptr, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    hook[0]               = 0x53;// push ebx;
    hook[1]               = 0xE8;// call [handler];
    (uintptr_t &) hook[2] = (uintptr_t) handler - ((uintptr_t) hook + 6);
    hook[6]               = 0x5B;// pop ebx;
    hook[7]               = 0xE8;// call [MAIN_LOOP_FUNC_ADDRESS];
    (uintptr_t &) hook[8] = MAIN_LOOP_FUNC_ADDRESS - ((uintptr_t) hook + 12);
    hook[12]              = 0xC3;// ret;

    uint8_t patch[5];
    patch[0]               = 0xE8;// call [hook]
    (uintptr_t &) patch[1] = (uintptr_t) hook - (MAIN_LOOP_CALL_ADDRESS + 5);
    WriteProcessMemory(GetCurrentProcess(), (void *) MAIN_LOOP_CALL_ADDRESS, patch, 5, nullptr);
}

void script::OnZombieCreated(void (*handler)(pvz::Zombie *)) {
    auto hook             = (uint8_t *) VirtualAlloc(nullptr, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    hook[0]               = 0x8B;// mov esp, ebp;
    hook[1]               = 0xE5;
    hook[2]               = 0x5D;// pop ebp;
    hook[3]               = 0x60;// pushad;
    hook[4]               = 0xFF;// push [esp+24];
    hook[5]               = 0x74;
    hook[6]               = 0x24;
    hook[7]               = 0x24;
    hook[8]               = 0xE8;// call [handler];
    (uintptr_t &) hook[9] = (uintptr_t) handler - ((uintptr_t) hook + 13);
    hook[13]              = 0x83;// add esp, 4;
    hook[14] = 0xC4;
    hook[15] = 0x04;
    hook[16]              = 0x61;// popad;
    hook[17]              = 0xC2;// retn 0x14;
    (uint16_t &) hook[18] = 0x14;

    uint8_t patch[5];
    patch[0]               = 0xE9;// jmp [hook]
    (uintptr_t &) patch[1] = (uintptr_t) hook - (ON_ZOMBIE_CREATED_INJECTION_ADDRESS + 5);
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_ZOMBIE_CREATED_INJECTION_ADDRESS, patch, 5, nullptr);
}