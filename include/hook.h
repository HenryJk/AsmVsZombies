//
// Created by henryj on 27/6/2021.
//

#pragma once

#include "memory.h"

namespace hook {
    void install(Memory &memory);
    void uninstall(Memory &memory);
}
