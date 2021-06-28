//
// Created by henryj on 28/6/2021.
//

#pragma once
#include "address.h"
#include "offset_struct.h"

namespace PvZ {
    // clang-format off
    OFFSET_STRUCT(Game,
        OF(void* zombie_ptr,            ZOMBIE_PTR_OFFSET);
        OF(uint32_t zombie_count,       ZOMBIE_COUNT_OFFSET);
        OF(void* plant_ptr,             PLANT_PTR_OFFSET);
        OF(uint32_t plant_count,        PLANT_COUNT_OFFSET);
        OF(uint32_t next_plant_index,   PLANT_NEXT_OFFSET);
        OF(void* bullet_ptr,            BULLET_PTR_OFFSET);
    );
    // clang-format on
}
