//
// Created by henryj on 4/7/2021.
//

#include "cheat.h"
#include "reference.h"
#include "memory.h"

namespace {
    std::unordered_map<uintptr_t, uint8_t> original_code;

    inline void SaveOriginalCode(uintptr_t address, uint32_t length) {
        for (int i = 0; i < length; i++) original_code[address + i] = *(uint8_t *)address;
    }

    inline void Patch(uintptr_t address, uint32_t length, uint8_t *patch) {
        Memory memory;
        memory.OpenSelf();
        SaveOriginalCode(address, length);
        memory.Write(address, length, patch);
    }
}

void cheat::AllowInfiniteSpeed() {
    uint8_t patch[2] = {0x90, 0x90};
    Patch(ALLOW_INFINITE_SPEED_CHEAT_ADDRESS, sizeof(patch), patch);
}

void cheat::AutoCollect() {
    uint8_t patch[1] = {0xEB};
    Patch(AUTO_COLLECT_CHEAT_ADDRESS, sizeof(patch), patch);
}

void cheat::NoDrop() {
    uint8_t patch[2] = {0x90, 0xE9};
    Patch(NO_DROP_CHEAT_ADDRESS, sizeof(patch), patch);
}

void cheat::RemoveAllCheats() {
    Memory memory;
    memory.OpenSelf();
    for (auto &[address, code]: original_code) {
        memory.Write(address, 1, &code);
    }
}