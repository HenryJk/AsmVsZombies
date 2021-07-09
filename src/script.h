//
// Created by henryj on 2/7/2021.
//

#pragma once

#include "pvz.h"

namespace script {
    void OnHook();
    void OnTick(void (*handler)(pvz::Game *));
    void OnZombieCreated(void (*handler)(pvz::Zombie *));
    void OnZombieDestroyed(void (*handler)(pvz::Zombie *));
}
