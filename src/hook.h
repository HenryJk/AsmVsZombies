//
// Created by henryj on 27/6/2021.
//

#pragma once

#include "memory.h"
#include "pvz.h"

namespace hook {
    void Install();
    void RegisterOnTickHandler(void (*handler)(pvz::Game *));
    void RegisterOnZombieCreatedHandler(void (*handler)(pvz::Zombie *));
    void Uninstall(Memory &memory);
}
