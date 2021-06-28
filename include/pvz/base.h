//
// Created by henryj on 28/6/2021.
//

#pragma once

#include "address.h"
#include "offset_struct.h"
#include "pvz/game.h"

namespace PvZ {
    // clang-format off
    OFFSET_STRUCT(Base,
        OF(double music_volume,     MUSIC_VOLUME_OFFSET);
        OF(double sfx_volume,       SFX_VOLUME_OFFSET);
        OF(int32_t ms_per_frame,    MS_PER_FRAME_OFFSET);
        OF(PvZ::Game* game_ptr,     GAME_PTR_OFFSET);
    );
    // clang-format on
}// namespace PvZ
