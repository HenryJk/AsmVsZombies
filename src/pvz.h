//
// Created by henryj on 2/7/2021.
//

#pragma once

#include <cstdint>
#include "reference.h"

// clang-format off
#define OFFSET_STRUCT(name, members) \
    union name {                     \
        members                      \
    }

#ifdef NO_CHEAT
    // Using const to denote read only, to prevent tampering with memory for the no-cheat build
    #define OFFSET_FIELD(name, offset)       \
        struct __attribute__((__packed__)) { \
            char __unused_##offset[offset];  \
            const name;                      \
        }
#else
    #define OFFSET_FIELD(name, offset)       \
        struct __attribute__((__packed__)) { \
            char __unused_##offset[offset];  \
            name;                            \
        }
#endif

#define OF OFFSET_FIELD

#define EXACT_SIZE(size) \
    struct __attribute__((__packed__)) { \
        char __full_##size[size];  \
    }

namespace pvz {
    enum class ZombieType: uint32_t;
    enum class HelmetType: uint32_t;
    enum class ShieldType: uint32_t;
    enum class PlantType: uint32_t;
    enum class FloatingItemType: uint32_t;
    enum class GridItemType: uint32_t;
    enum class CursorItem: uint32_t;
    enum class TerrainType: uint32_t;

    OFFSET_STRUCT(Zombie,
        EXACT_SIZE(ZOMBIE_STRUCT_SIZE);
        OF(bool is_visible,                         ZOMBIE_IS_VISIBLE_OFFSET);
        OF(uint32_t row_index,                      ZOMBIE_ROW_INDEX_OFFSET);
        OF(ZombieType type,                         ZOMBIE_TYPE_OFFSET);
        OF(uint32_t state,                          ZOMBIE_STATE_OFFSET);
        OF(float xpos,                              ZOMBIE_XPOS_OFFSET);
        OF(float ypos,                              ZOMBIE_YPOS_OFFSET);
        OF(float animation_speed,                   ZOMBIE_ANIMATION_SPEED_OFFSET);
        OF(bool is_biting,                          ZOMBIE_IS_BITING_OFFSET);
        OF(uint32_t movement_status,                ZOMBIE_MOVEMENT_STATUS_OFFSET);
        OF(uint32_t ability_countdown,              ZOMBIE_ABILITY_COUNTDOWN_OFFSET);
        OF(uint32_t bungee_target_column,           ZOMBIE_BUNGEE_TARGET_COLUMN_OFFSET);
        OF(uint32_t extra_height,                   ZOMBIE_EXTRA_HEIGHT_OFFSET);
        OF(int32_t projectile_collision_box[4],     ZOMBIE_PROJECTILE_COLLISION_BOX_OFFSET);
        OF(int32_t attack_collision_box[4],         ZOMBIE_ATTACK_COLLISION_BOX_OFFSET);
        OF(uint32_t slow_countdown,                 ZOMBIE_SLOW_COUNTDOWN_OFFSET);
        OF(uint32_t stun_countdown,                 ZOMBIE_STUN_COUNTDOWN_OFFSET);
        OF(uint32_t freeze_countdown,               ZOMBIE_FREEZE_COUNTDOWN_OFFSET);
        OF(bool is_hypnotized,                      ZOMBIE_IS_HYPNOTIZED_OFFSET);
        OF(bool is_blown,                           ZOMBIE_IS_BLOWN_OFFSET);
        OF(bool has_consumable,                     ZOMBIE_HAS_CONSUMABLE_OFFSET);
        OF(bool is_swimming,                        ZOMBIE_IS_SWIMMING_OFFSET);
        OF(bool is_climbing,                        ZOMBIE_IS_CLIMBING_OFFSET);
        OF(bool is_disgusted,                       ZOMBIE_IS_DISGUSTED_OFFSET);
        OF(uint32_t disgusted_countdown,            ZOMBIE_DISGUSTED_COUNTDOWN_OFFSET);
        OF(HelmetType helmet_type,                  ZOMBIE_HELMET_TYPE_OFFSET);
        OF(uint32_t hp,                             ZOMBIE_HP_OFFSET);
        OF(uint32_t helmet_hp,                      ZOMBIE_HELMET_HP_OFFSET);
        OF(ShieldType shield_type,                  ZOMBIE_SHIELD_TYPE_OFFSET);
        OF(uint32_t shield_hp,                      ZOMBIE_SHIELD_HP_OFFSET);
        OF(uint32_t balloon_hp,                     ZOMBIE_BALLOON_HP_OFFSET);
        OF(uint32_t animation_id,                   ZOMBIE_ANIMATION_ID_OFFSET);
        OF(uint32_t id,                             ZOMBIE_ID_OFFSET);
    );

    OFFSET_STRUCT(Plant,
        EXACT_SIZE(PLANT_STRUCT_SIZE);
        OF(bool is_visible,                         PLANT_IS_VISIBLE_OFFSET);
        OF(uint32_t row_index,                      PLANT_ROW_INDEX_OFFSET);
        OF(PlantType type,                          PLANT_TYPE_OFFSET);
        OF(uint32_t column_index,                   PLANT_COLUMN_INDEX_OFFSET);
        OF(uint32_t state,                          PlANT_STATE_OFFSET);
        OF(uint32_t hp,                             PLANT_HP_OFFSET);
        OF(bool is_shooter,                         PLANT_IS_SHOOTER_OFFSET);
        OF(uint32_t explosion_countdown,            PLANT_EXPLOSION_COUNTDOWN_OFFSET);
        OF(uint32_t ability_countdown,              PLANT_ABILITY_COUNTDOWN_OFFSET);
        OF(uint32_t work_countdown,                 PLANT_WORK_COUNTDOWN_OFFSET);
        OF(uint32_t work_interval,                  PLANT_WORK_INTERVAL_OFFSET);
        OF(uint32_t cob_target_xpos,                PLANT_COB_TARGET_XPOS_OFFSET);
        OF(uint32_t cob_target_ypos,                PLANT_COB_TARGET_YPOS_OFFSET);
        OF(uint32_t particle_id,                    PLANT_PARTICLE_ID_OFFSET);
        OF(uint32_t projectile_countdown,           PLANT_PROJECTILE_COUNTDOWN_OFFSET);
        OF(uint32_t wakeup_countdown,               PLANT_WAKEUP_COUNTDOWN_OFFSET);
        OF(PlantType imitater_type,                 PLANT_IMITATER_TYPE_OFFSET);
        OF(bool is_squashed,                        PLANT_IS_SQUASHED_OFFSET);
        OF(bool is_sleeping,                        PLANT_IS_SLEEPING_OFFSET);
        OF(uint32_t id,                             PLANT_ID_OFFSET);
    );

    OFFSET_STRUCT(Projectile,
        EXACT_SIZE(PROJECTILE_STRUCT_SIZE);
        OF(bool is_visible,                         PROJECTILE_IS_VISIBLE_OFFSET);
        OF(uint32_t row_index,                      PROJECTILE_ROW_INDEX_OFFSET);
        OF(uint32_t xpos,                           PROJECTILE_XPOS_OFFSET);
        OF(uint32_t ypos,                           PROJECTILE_YPOS_OFFSET);
        OF(bool is_colliding,                       PROJECTILE_IS_COLLIDING_OFFSET);
        OF(uint32_t cattail_target_id,              PROJECTILE_CATTAIL_TARGET_ID_OFFSET);
        OF(uint32_t id,                             PROJECTILE_ID_OFFSET);
    );

    OFFSET_STRUCT(FloatingItem,
        EXACT_SIZE(FLOATING_ITEM_STRUCT_SIZE);
        OF(uint32_t width,                          FLOATING_ITEM_WIDTH_OFFSET);
        OF(uint32_t height,                         FLOATING_ITEM_HEIGHT_OFFSET);
        OF(bool is_visible,                         FLOATING_ITEM_IS_VISIBLE_OFFSET);
        OF(uint32_t xpos,                           FLOATING_ITEM_XPOS_OFFSET);
        OF(uint32_t ypos,                           FLOATING_ITEM_YPOS_OFFSET);
        OF(bool is_collected,                       FLOATING_ITEM_IS_COLLECTED_OFFSET);
        OF(uint32_t disappear_countdown,            FLOATING_ITEM_DISAPPEAR_COUNTDOWN_OFFSET);
        OF(FloatingItemType type,                   FLOATING_ITEM_TYPE_OFFSET);
        OF(bool has_halo,                           FLOATING_ITEM_HAS_HALO_OFFSET);
        OF(uint32_t id,                             FLOATING_ITEM_ID_OFFSET);
    );

    OFFSET_STRUCT(GridItem,
        EXACT_SIZE(GRID_ITEM_STRUCT_SIZE);
        OF(GridItemType type,                       GRID_ITEM_TYPE_OFFSET);
        OF(uint32_t column_index,                   GRID_ITEM_COLUMN_INDEX_OFFSET);
        OF(uint32_t row_index,                      GRID_ITEM_ROW_INDEX_OFFSET);
        OF(uint32_t crater_countdown,               GRID_ITEM_CRATER_COUNTDOWN_OFFSET);
        OF(uint32_t id,                             GRID_ITEM_ID_OFFSET);
    );
    OFFSET_STRUCT(Cursor,
        OF(uint32_t xpos,                           CURSOR_XPOS_OFFSET);
        OF(uint32_t ypos,                           CURSOR_YPOS_OFFSET);
        OF(uint32_t seed_index,                     CURSOR_SEED_INDEX_OFFSET);
        OF(PlantType plant_type,                    CURSOR_PLANT_TYPE_OFFSET);
        OF(PlantType imitater_type,                 CURSOR_IMITATER_TYPE_OFFSET);
        OF(CursorItem held_item,                    CURSOR_HELD_ITEM_OFFSET);
    );

    OFFSET_STRUCT(Game,
        OF(Zombie *zombie_ptr,                      GAME_ZOMBIE_PTR_OFFSET);
        OF(uint32_t zombie_count,                   GAME_ZOMBIE_COUNT_OFFSET);
        OF(Plant *plant_ptr,                        GAME_PLANT_PTR_OFFSET);
        OF(uint32_t plant_count,                    GAME_PLANT_COUNT_OFFSET);
        OF(uint32_t next_plant_index,               GAME_PLANT_NEXT_OFFSET);
        OF(Projectile *projectile_ptr,              GAME_PROJECTILE_PTR_OFFSET);
        OF(uint32_t projectile_count,               GAME_PROJECTILE_COUNT_OFFSET);
        OF(FloatingItem *floating_item_ptr,         GAME_FLOATING_ITEM_PTR_OFFSET);
        OF(uint32_t floating_item_count,            GAME_FLOATING_ITEM_COUNT_OFFSET);
        OF(void *lawnmower_ptr,                     GAME_LAWNMOWER_PTR_OFFSET);
        OF(uint32_t lawnmower_count,                GAME_LAWNMOWER_COUNT_OFFSET);
        OF(GridItem *grid_item_ptr,                 GAME_GRID_ITEM_PTR_OFFSET);
        OF(uint32_t grid_item_count,                GAME_GRID_ITEM_COUNT_OFFSET);
        OF(Cursor *cursor_ptr,                      GAME_CURSOR_PTR_OFFSET);
        OF(void* card_slot_ptr,                     GAME_CARD_SLOT_PTR_OFFSET);
        OF(uint32_t terrain_type_array[54],         GAME_TERRAIN_TYPE_ARRAY_OFFSET);
        OF(uint32_t ice_trail_coord_array[6],       GAME_ICE_TRAIL_COORD_ARRAY_OFFSET);
        OF(uint32_t ice_trail_countdown_array[6],   GAME_ICE_TRAIL_COUNTDOWN_ARRAY_OFFSET);
        OF(uint32_t spawn_list[1000],               GAME_SPAWN_LIST_OFFSET);
        OF(bool spawn_flags[33],                    GAME_SPAWN_FLAGS_OFFSET);
        OF(uint32_t falling_sun_countdown,          GAME_FALLING_SUN_COUNTDOWN_OFFSET);
        OF(uint32_t battlefield_type,               GAME_BATTLEFIELD_TYPE_OFFSET);
        OF(uint32_t sun_value,                      GAME_SUN_VALUE_OFFSET);
        OF(uint32_t total_wave_count,               GAME_TOTAL_WAVE_COUNT_OFFSET);
        OF(uint32_t spawned_wave_count,             GAME_SPAWNED_WAVE_COUNT_OFFSET);
        OF(uint32_t spawn_wave_hp_threshold,        GAME_SPAWN_WAVE_HP_THRESHOLD_OFFSET);
        OF(uint32_t current_wave_total_hp,          GAME_CURRENT_WAVE_TOTAL_HP_OFFSET);
        OF(uint32_t next_wave_countdown,            GAME_NEXT_WAVE_COUNTDOWN_OFFSET);
        OF(uint32_t huge_wave_countdown,            GAME_HUGE_WAVE_COUNTDOWN_OFFSET);
        OF(uint32_t cannon_debounce_countdown,      GAME_CANNON_DEBOUNCE_COUNTDOWN_OFFSET);
        OF(uint32_t cannon_debounce_xpos,           GAME_CANNON_DEBOUNCE_XPOS_OFFSET);
        OF(uint32_t cannon_debounce_ypos,           GAME_CANNON_DEBOUNCE_YPOS_OFFSET);
    );

    OFFSET_STRUCT(Base,
        OF(double music_volume,                     BASE_MUSIC_VOLUME_OFFSET);
        OF(double sfx_volume,                       BASE_SFX_VOLUME_OFFSET);
        OF(int32_t ms_per_frame,                    BASE_MS_PER_FRAME_OFFSET);
        OF(Game *game_ptr,                          BASE_GAME_PTR_OFFSET);
        OF(void* pregame_ui_ptr,                    BASE_PREGAME_UI_PTR_OFFSET);
        OF(uint32_t game_type,                      BASE_GAME_TYPE_OFFSET);
        OF(uint32_t game_status,                    BASE_GAME_STATUS_OFFSET);
        OF(bool free_planting_mode,                 BASE_FREE_PLANTING_MODE_OFFSET);
    );


    inline void ClickBattlefield(uint32_t x, uint32_t y, uint32_t key, Game *game_ptr) {
        asm volatile(
            "pushl %0;"
            "pushl %1;"
            "pushl %2;"
            "movl %3, %%ecx;"
            "movl $0x411f20, %%eax;"
            "calll *%%eax;"
            :
            : "g"(key), "g"(y), "g"(x), "g"(game_ptr)
            : "eax", "ecx", "esp"
        );
    }



    // clang-format on
}// namespace PvZ

