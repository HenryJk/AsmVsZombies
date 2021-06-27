//
// Created by henryj on 27/6/2021.
//

#include "address.h"
#include "core.h"

void* Core::main_address = nullptr;

void Core::Click(int x, int y, int key)
{
    __asm__ __volatile__(
    "pushl %0;"
    "pushl %1;"
    "pushl %2;"
    "movl %3, %%ecx;"
    "movl %4, %%eax;"
    "calll %%eax;"
    :
    : "g"(key), "g"(y), "g"(x), "g"(Core::main_address), "n"(CLICK_SCENE_CALL_ADDRESS)
    : "eax", "ecx");
}