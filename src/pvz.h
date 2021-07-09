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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

    enum class ZombieType: uint32_t {
        kZombie = 0,
        kFlagZombie = 1,
        kConeheadZombie = 2,
        kPoleVaultingZombie = 3,
        kBucketheadZombie = 4,
        kNewspaperZombie = 5,
        kScreenDoorZombie = 6,
        kFootballZombie = 7,
        kDancingZombie = 8,
        kBackupDancer = 9,
        kDuckyTubeZombie = 10,
        kSnorkelZombie = 11,
        kZomboni = 12,
        kZombieBobsledTeam = 13,
        kDolphinRiderZombie = 14,
        kJackInTheBoxZombie = 15,
        kBalloonZombie = 16,
        kDiggerZombie = 17,
        kPogoZombie = 18,
        kZombieYeti = 19,
        kBungeeZombie = 20,
        kLadderZombie = 21,
        kCatapultZombie = 22,
        kGargantuar = 23,
        kImp = 24,
        kDrZomboss = 25,
        kPeashooterZombie = 26,
        kWallNutZombie = 27,
        kJalapenoZombie = 28,
        kGatlingPeaZombie = 29,
        kSquashZombie = 30,
        kTallNutZombie = 31,
        kGigaGargantuar = 32,
    };

    enum class HelmetType: uint32_t {
        kNone = 0,
        kCone = 1,
        kBucket = 2,
        kRugby = 3,
        kMiner = 4,
        kSled = 7,
        kWallNut = 8,
        kTallNut = 9,
    };

    enum class ShieldType: uint32_t {
        kNone = 0,
        kScreenDoor = 1,
        kNewspaper = 2,
        kLadder = 3,
        kPickaxe = 4,
    };

    enum class PlantType: uint32_t {
        kPeashooter = 0,
        kSunflower = 1,
        kCherryBomb = 2,
        kWallNut = 3,
        kPotatoMine = 4,
        kSnowPea = 5,
        kChomper = 6,
        kRepeater = 7,
        kPuffShroom = 8,
        kSunShroom = 9,
        kFumeShroom = 10,
        kGraveBuster = 11,
        kHypnoShroom = 12,
        kScaredyShroom = 13,
        kIceShroom = 14,
        kDoomShroom = 15,
        kLilyPad = 16,
        kSquash = 17,
        kThreepeater = 18,
        kTangleKelp = 19,
        kJalapeno = 20,
        kSpikeweed = 21,
        kTorchwood = 22,
        kTallNut = 23,
        kSeaShroom = 24,
        kPlantern = 25,
        kCactus = 26,
        kBlover = 27,
        kSplitPea = 28,
        kStarFruit = 29,
        kPumpkin = 30,
        kMagnetShroom = 31,
        kCabbagePult = 32,
        kFlowerPot = 33,
        kKernelPult = 34,
        kCoffeeBean = 35,
        kGarlic = 36,
        kUmbrellaLeaf = 37,
        kMarigold = 38,
        kMelonPult = 39,
        kGatlingPea = 40,
        kTwinSunflower = 41,
        kGloomShroom = 42,
        kCattail = 43,
        kWinterMelon = 44,
        kGoldMagnet = 45,
        kSpikerock = 46,
        kCobCannon = 47,
        kImitater = 48,
        kExplodeONut = 49,
        kGiantWallNut = 50,
        kSprout = 51,
        kReverseRepeater = 52,
    };

    enum class FloatingItemType: uint32_t {
        kNone = 0,
        kSilverCoin = 1,
        kGoldCoin = 2,
        kDiamond = 3,
        kSun = 4,
        kSmallSun = 5,
        kBigSun = 6,
        kTrophy = 8,
        kSeedPacket = 16,
        kZenGardenPlant = 17,
    };

    enum class GridItemType: uint32_t {
        kNone = 0,
        kGrave = 1,
        kCrater = 2,
        kLadder = 3,
        kRake = 11,
        kBrain = 12,
    };

    enum class CursorItem: uint32_t {
        kNone = 0,
        kPlant = 1,
        kShovel = 6,
        kMallet = 7,
        kCannonTarget = 8,
        kWateringCan = 9,
        kFertilizer = 10,
        kBugSpray = 11,
        kPhonograph = 12,
        kChocolate = 13,
        kGardeningGlove = 14,
        kSellPlant = 15,
        kWheelBarrow = 16,
        kTreeFood = 17,
    };

    enum class TerrainType: uint32_t {
        kLand = 1,
        kUnsodded = 2,
        kWater = 3,
    };

    enum class BattlefieldType: uint32_t {
        kDay = 0,
        kNight = 1,
        kPool = 2,
        kFog = 3,
        kRoof = 4,
        kMoon = 5,
    };

    enum class CardState: uint32_t {
        kSelectedMoving = 0,
        kSelected = 1,
        kUnselectedMoving = 2,
        kUnselected = 3,
        kUntransformed = 4,
    };

#pragma clang diagnostic pop

    OFFSET_STRUCT(Screen,
    );

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
        OF(uint32_t age,                            ZOMBIE_AGE_OFFSET);
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
        OF(uint32_t xpos,                           PLANT_XPOS_OFFSET);
        OF(uint32_t ypos,                           PLANT_YPOS_OFFSET);
        OF(bool is_visible,                         PLANT_IS_VISIBLE_OFFSET);
        OF(uint32_t row_index,                      PLANT_ROW_INDEX_OFFSET);
        OF(PlantType type,                          PLANT_TYPE_OFFSET);
        OF(uint32_t column_index,                   PLANT_COLUMN_INDEX_OFFSET);
        OF(uint32_t state,                          PlANT_STATE_OFFSET);
        OF(uint32_t hp,                             PLANT_HP_OFFSET);
        OF(uint32_t max_hp,                         PLANT_MAX_HP_OFFSET);
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

    OFFSET_STRUCT(SeedSlot,
        EXACT_SIZE(SEED_SLOT_STRUCT_SIZE);
        OF(uint32_t xpos,                           SEED_SLOT_XPOS_OFFSET);
        OF(uint32_t ypos,                           SEED_SLOT_YPOS_OFFSET);
        OF(uint32_t width,                          SEED_SLOT_WIDTH_OFFSET);
        OF(uint32_t height,                         SEED_SLOT_HEIGHT_OFFSET);
        OF(bool is_visible,                         SEED_SLOT_IS_VISIBLE_OFFSET);
        OF(uint32_t recharge_progress,              SEED_SLOT_RECHARGE_PROGRESS_OFFSET);
        OF(uint32_t refresh_threshold,              SEED_SLOT_REFRESH_THRESHOLD_OFFSET);
        OF(uint32_t index,                          SEED_SLOT_INDEX_OFFSET);
        OF(PlantType type,                          SEED_SLOT_TYPE_OFFSET);
        OF(PlantType imitater_type,                 SEED_SLOT_IMITATER_TYPE_OFFSET);
        OF(bool is_available,                       SEED_SLOT_IS_AVAILABLE_OFFSET);
        OF(uint32_t usage_counter,                  SEED_SLOT_USAGE_COUNTER_OFFSET);
    );

    OFFSET_STRUCT(SeedBank,
        OF(bool is_visible,                         SEED_BANK_IS_VISIBLE_OFFSET);
        OF(uint32_t slot_count,                     SEED_BANK_SLOT_COUNT_OFFSET);
        OF(SeedSlot slot[10],                       SEED_BANK_SLOT_ARRAY_OFFSET);
    );

    OFFSET_STRUCT(Button,
        OF(uint32_t xpos,                           BUTTON_XPOS_OFFSET);
        OF(uint32_t ypos,                           BUTTON_YPOS_OFFSET);
        OF(uint32_t width,                          BUTTON_WIDTH_OFFSET);
        OF(uint32_t height,                         BUTTON_HEIGHT_OFFSET);
        OF(bool is_disabled,                        BUTTON_IS_DISABLED_OFFSET);
        OF(bool is_hidden,                          BUTTON_IS_HIDDEN_OFFSET);
    );

    OFFSET_STRUCT(CardSelectionUI,
        OF(bool is_active,                          CARD_SELECTION_UI_IS_ACTIVE_OFFSET);
        OF(bool is_zombie_generated,                CARD_SELECTION_UI_IS_ZOMBIE_GENERATED_OFFSET);
    );

    struct Game {
        union {
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
            OF(SeedBank *seed_bank_ptr,                 GAME_SEED_BANK_PTR_OFFSET);
            OF(Button *menu_button_ptr,                 GAME_MENU_BUTTON_PTR_OFFSET);
            OF(Button *last_stand_button_ptr,           GAME_LAST_STAND_BUTTON_PTR_OFFSET);
            OF(CardSelectionUI *card_selection_ui_ptr,  GAME_CARD_SELECTION_UI_PTR_OFFSET);
            OF(bool is_paused,                          GAME_IS_PAUSED_OFFSET);
            OF(TerrainType terrain_type_array[54],      GAME_TERRAIN_TYPE_ARRAY_OFFSET);
            OF(uint32_t ice_trail_coord_array[6],       GAME_ICE_TRAIL_COORD_ARRAY_OFFSET);
            OF(uint32_t ice_trail_countdown_array[6],   GAME_ICE_TRAIL_COUNTDOWN_ARRAY_OFFSET);
            OF(ZombieType spawn_list[1000],             GAME_SPAWN_LIST_OFFSET);
            OF(bool spawn_flags[33],                    GAME_SPAWN_FLAGS_OFFSET);
            OF(uint32_t falling_sun_countdown,          GAME_FALLING_SUN_COUNTDOWN_OFFSET);
            OF(BattlefieldType battlefield_type,        GAME_BATTLEFIELD_TYPE_OFFSET);
            OF(uint32_t sun_value,                      GAME_SUN_VALUE_OFFSET);
            OF(uint32_t total_wave_count,               GAME_TOTAL_WAVE_COUNT_OFFSET);
            OF(uint32_t spawned_wave_count,             GAME_SPAWNED_WAVE_COUNT_OFFSET);
            OF(uint32_t spawn_wave_hp_threshold,        GAME_SPAWN_WAVE_HP_THRESHOLD_OFFSET);
            OF(uint32_t current_wave_total_hp,          GAME_CURRENT_WAVE_TOTAL_HP_OFFSET);
            OF(uint32_t next_wave_countdown,            GAME_NEXT_WAVE_COUNTDOWN_OFFSET);
            OF(uint32_t next_wave_initial_countdown,    GAME_NEXT_WAVE_INITIAL_COUNTDOWN_OFFSET);
            OF(uint32_t huge_wave_countdown,            GAME_HUGE_WAVE_COUNTDOWN_OFFSET);
            OF(uint32_t cannon_debounce_countdown,      GAME_CANNON_DEBOUNCE_COUNTDOWN_OFFSET);
            OF(uint32_t cannon_debounce_xpos,           GAME_CANNON_DEBOUNCE_XPOS_OFFSET);
            OF(uint32_t cannon_debounce_ypos,           GAME_CANNON_DEBOUNCE_YPOS_OFFSET);
        };

        [[maybe_unused]] inline void Click(uint32_t x, uint32_t y, int32_t key) {
            asm volatile(
            "pushal;"
            "pushl %0;"
            "pushl %1;"
            "pushl %2;"
            "movl %3, %%ecx;"
            "movl %4, %%eax;"
            "calll *%%eax;"
            "popal;"
            :
            : "g"(key), "g"(y), "g"(x), "g"(this), "i"(CLICK_BATTLEFIELD_FUNC_ADDRESS)
            : "eax", "ecx", "esp"
            );
        }
    };

    OFFSET_STRUCT(PlantCard,
        EXACT_SIZE(PLANT_CARD_STRUCT_SIZE);
        OF(uint32_t xpos,                           PLANT_CARD_XPOS_OFFSET);
        OF(uint32_t ypos,                           PLANT_CARD_YPOS_OFFSET);
        OF(PlantType type,                          PLANT_CARD_TYPE_OFFSET);
        OF(CardState state,                         PLANT_CARD_STATE_OFFSET);
        OF(uint32_t slot_index,                     PLANT_CARD_SLOT_INDEX_OFFSET);
        OF(PlantType imitater_type,                 PLANT_CARD_IMITATER_TYPE_OFFSET);
        OF(bool is_enforced,                        PLANT_CARD_IS_ENFORCED_OFFSET);
    );

    OFFSET_STRUCT(PreGameUI,
        OF(Button *lets_rock_button_ptr,            PRE_GAME_UI_LETS_ROCK_BUTTON_PTR_OFFSET);
        OF(PlantCard card[49],                      PRE_GAME_UI_CARD_ARRAY_OFFSET);
        OF(uint32_t next_slot_index,                PRE_GAME_UI_NEXT_SLOT_INDEX_OFFSET);
    );

    OFFSET_STRUCT(Base,
        OF(double music_volume,                     BASE_MUSIC_VOLUME_OFFSET);
        OF(double sfx_volume,                       BASE_SFX_VOLUME_OFFSET);
        OF(Screen *screen_ptr,                      BASE_SCREEN_PTR_OFFSET);
        OF(int32_t ms_per_tick,                     BASE_MS_PER_TICK_OFFSET);
        OF(Game *game_ptr,                          BASE_GAME_PTR_OFFSET);
        OF(PreGameUI *pregame_ui_ptr,               BASE_PREGAME_UI_PTR_OFFSET);
        OF(uint32_t game_type,                      BASE_GAME_TYPE_OFFSET);
        OF(uint32_t game_status,                    BASE_GAME_STATUS_OFFSET);
        OF(bool free_planting_mode,                 BASE_FREE_PLANTING_MODE_OFFSET);
    );

    [[maybe_unused]] inline void ClickBattlefield(Game *game_ptr, uint32_t x, uint32_t y, int32_t key) {
        asm volatile(
            "pushal;"
            "pushl %0;"
            "pushl %1;"
            "pushl %2;"
            "movl %3, %%ecx;"
            "movl %4, %%eax;"
            "calll *%%eax;"
            "popal;"
            :
            : "g"(key), "g"(y), "g"(x), "g"(game_ptr), "i"(CLICK_BATTLEFIELD_FUNC_ADDRESS)
            : "eax", "ecx", "esp"
        );
    }

     [[maybe_unused]] inline void ClickScreen(Screen *screen_ptr, uint32_t x, uint32_t y, int32_t key) {
        asm volatile(
            "pushl %0;"
            "movl %1, %%ebx;"
            "movl %2, %%eax;"
            "movl %3, %%ecx;"
            "movl %4, %%edx;"
            "calll *%%edx;"
            :
            : "g"(x), "g"(key), "g"(y), "g"(screen_ptr), "i"(CLICK_SCREEN_FUNC_ADDRESS)
            : "eax" , "ebx" , "ecx" , "edx", "esp"
        );
    }

    [[maybe_unused]] inline void LetsRock(PreGameUI *pregame_ui_ptr) {
        asm volatile(
            "pushal;"
            "movl %0, %%ebx;"
            "movl %1, %%esi;"
            "movl $0x1, %%edi;"
            "movl $0x1, %%ebp;"
            "movl %2, %%eax;"
            "calll *%%eax;"
            "popal;"
            :
            : "g"(pregame_ui_ptr), "i"(BASE_PTR_ADDRESS), "i"(LETS_ROCK_FUNC_ADDRESS)
            : "eax", "ebx", "esi", "edi", "esp"
        );
    }

    [[maybe_unused]] inline void LaunchCob(Plant *cob_ptr, uint32_t x, uint32_t y) {
        asm volatile(
            "pushal;"
            "pushl %0;"
            "pushl %1;"
            "movl %2, %%eax;"
            "movl %3, %%ebx;"
            "calll *%%ebx;"
            "popal;"
            :
            : "g"(y), "g"(x), "g"(cob_ptr), "i"(LAUNCH_COB_FUNC_ADDRESS)
            : "eax", "ebx", "esp"
        );
    }

    void SelectCard(PreGameUI *pregame_ui_ptr, PlantType card_type);
    void SelectImitaterCard(PreGameUI *pregame_ui_ptr, PlantType imitater_type);

    // clang-format on
}// namespace PvZ

