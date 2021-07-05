//
// Created by henryj on 2/7/2021.
//

#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

// code disassembly
#define CLICK_BATTLEFIELD_FUNC_ADDRESS                  0x411F20
#define MAIN_LOOP_FUNC_ADDRESS                          0x4130d0
#define MAIN_LOOP_CALL_ADDRESS                          0x415945
#define LAUNCH_COB_FUNC_ADDRESS                         0x466D50
#define LETS_ROCK_FUNC_ADDRESS                          0x486D20
#define CLICK_SCREEN_FUNC_ADDRESS                       0x539390
#define BASE_PTR_ADDRESS                                0x6A9EC0

#define NO_DROP_CHEAT_ADDRESS                           0x41D025
#define AUTO_COLLECT_CHEAT_ADDRESS                      0x43158f
#define ALLOW_INFINITE_SPEED_CHEAT_ADDRESS              0x551DBF


// Base object structure
#define BASE_MUSIC_VOLUME_OFFSET                        0xD0
#define BASE_SFX_VOLUME_OFFSET                          0xD8
#define BASE_SCREEN_PTR_OFFSET                          0x320
#define BASE_MS_PER_TICK_OFFSET                         0x454
#define BASE_GAME_PTR_OFFSET                            0x768
#define BASE_PREGAME_UI_PTR_OFFSET                      0x774
#define BASE_GAME_TYPE_OFFSET                           0x7F8
#define BASE_GAME_STATUS_OFFSET                         0x7FC
#define BASE_FREE_PLANTING_MODE_OFFSET                  0x814

// Game object structure
#define GAME_ZOMBIE_PTR_OFFSET                          0x90
#define GAME_ZOMBIE_COUNT_OFFSET                        0x94
#define GAME_PLANT_PTR_OFFSET                           0xAC
#define GAME_PLANT_COUNT_OFFSET                         0xB0
#define GAME_PLANT_NEXT_OFFSET                          0xB8
#define GAME_PROJECTILE_PTR_OFFSET                      0xC8
#define GAME_PROJECTILE_COUNT_OFFSET                    0xCC
#define GAME_FLOATING_ITEM_PTR_OFFSET                   0xE4
#define GAME_FLOATING_ITEM_COUNT_OFFSET                 0xE8
#define GAME_LAWNMOWER_PTR_OFFSET                       0x100
#define GAME_LAWNMOWER_COUNT_OFFSET                     0x104
#define GAME_GRID_ITEM_PTR_OFFSET                       0x11C
#define GAME_GRID_ITEM_COUNT_OFFSET                     0x120
#define GAME_CURSOR_PTR_OFFSET                          0x138
#define GAME_SEED_BANK_PTR_OFFSET                       0x144
#define GAME_MENU_BUTTON_PTR_OFFSET                     0x148
#define GAME_LAST_STAND_BUTTON_PTR_OFFSET               0x14C
#define GAME_CARD_SELECTION_UI_PTR_OFFSET               0x15C
#define GAME_IS_PAUSED_OFFSET                           0x164
#define GAME_TERRAIN_TYPE_ARRAY_OFFSET                  0x168
#define GAME_ICE_TRAIL_COORD_ARRAY_OFFSET               0x60C
#define GAME_ICE_TRAIL_COUNTDOWN_ARRAY_OFFSET           0x624
#define GAME_SPAWN_LIST_OFFSET                          0x6B4
#define GAME_SPAWN_FLAGS_OFFSET                         0x54D4
#define GAME_FALLING_SUN_COUNTDOWN_OFFSET               0x5538
#define GAME_BATTLEFIELD_TYPE_OFFSET                    0x554C
#define GAME_SUN_VALUE_OFFSET                           0x5560
#define GAME_TOTAL_WAVE_COUNT_OFFSET                    0x5564
#define GAME_SPAWNED_WAVE_COUNT_OFFSET                  0x557C
#define GAME_SPAWN_WAVE_HP_THRESHOLD_OFFSET             0x5594
#define GAME_CURRENT_WAVE_TOTAL_HP_OFFSET               0x5598
#define GAME_NEXT_WAVE_COUNTDOWN_OFFSET                 0x559C
#define GAME_NEXT_WAVE_INITIAL_COUNTDOWN_OFFSET         0x55A0
#define GAME_HUGE_WAVE_COUNTDOWN_OFFSET                 0x55A0
#define GAME_HAS_SHOVEL_OFFSET                          0x55F1
#define GAME_CANNON_DEBOUNCE_COUNTDOWN_OFFSET           0x5754
#define GAME_CANNON_DEBOUNCE_XPOS_OFFSET                0x5758
#define GAME_CANNON_DEBOUNCE_YPOS_OFFSET                0x575C

// Zombie object structure
#define ZOMBIE_STRUCT_SIZE                              0x15C
#define ZOMBIE_IS_VISIBLE_OFFSET                        0x18
#define ZOMBIE_ROW_INDEX_OFFSET                         0x1C
#define ZOMBIE_TYPE_OFFSET                              0x24
#define ZOMBIE_STATE_OFFSET                             0x28
#define ZOMBIE_XPOS_OFFSET                              0x2C
#define ZOMBIE_YPOS_OFFSET                              0x30
#define ZOMBIE_ANIMATION_SPEED_OFFSET                   0x34
#define ZOMBIE_IS_BITING_OFFSET                         0x51
#define ZOMBIE_MOVEMENT_STATUS_OFFSET                   0x64
#define ZOMBIE_ABILITY_COUNTDOWN_OFFSET                 0x68
#define ZOMBIE_BUNGEE_TARGET_COLUMN_OFFSET              0x80
#define ZOMBIE_EXTRA_HEIGHT_OFFSET                      0x84
#define ZOMBIE_PROJECTILE_COLLISION_BOX_OFFSET          0x8C
#define ZOMBIE_ATTACK_COLLISION_BOX_OFFSET              0x9C
#define ZOMBIE_SLOW_COUNTDOWN_OFFSET                    0xAC
#define ZOMBIE_STUN_COUNTDOWN_OFFSET                    0xB0
#define ZOMBIE_FREEZE_COUNTDOWN_OFFSET                  0xB4
#define ZOMBIE_IS_HYPNOTIZED_OFFSET                     0xB8
#define ZOMBIE_IS_BLOWN_OFFSET                          0xB9
#define ZOMBIE_HAS_CONSUMABLE_OFFSET                    0xBC
#define ZOMBIE_IS_SWIMMING_OFFSET                       0xBD
#define ZOMBIE_IS_CLIMBING_OFFSET                       0xBE
#define ZOMBIE_IS_DISGUSTED_OFFSET                      0xBF
#define ZOMBIE_DISGUSTED_COUNTDOWN_OFFSET               0xC0
#define ZOMBIE_HELMET_TYPE_OFFSET                       0xC4
#define ZOMBIE_HP_OFFSET                                0xC8
#define ZOMBIE_HELMET_HP_OFFSET                         0xD0
#define ZOMBIE_SHIELD_TYPE_OFFSET                       0xD8
#define ZOMBIE_SHIELD_HP_OFFSET                         0xDC
#define ZOMBIE_BALLOON_HP_OFFSET                        0xE4
#define ZOMBIE_ANIMATION_ID_OFFSET                      0x118
#define ZOMBIE_ID_OFFSET                                0x158

// Plant object structure
#define PLANT_STRUCT_SIZE                               0x14C
#define PLANT_XPOS_OFFSET                               0x8
#define PLANT_YPOS_OFFSET                               0xC
#define PLANT_IS_VISIBLE_OFFSET                         0x18
#define PLANT_ROW_INDEX_OFFSET                          0x1C
#define PLANT_TYPE_OFFSET                               0x24
#define PLANT_COLUMN_INDEX_OFFSET                       0x28
#define PlANT_STATE_OFFSET                              0x3C
#define PLANT_HP_OFFSET                                 0x40
#define PLANT_MAX_HP_OFFSET                             0x44
#define PLANT_IS_SHOOTER_OFFSET                         0x48
#define PLANT_EXPLOSION_COUNTDOWN_OFFSET                0x50
#define PLANT_ABILITY_COUNTDOWN_OFFSET                  0x54
#define PLANT_WORK_COUNTDOWN_OFFSET                     0x58
#define PLANT_WORK_INTERVAL_OFFSET                      0x5C
#define PLANT_COB_TARGET_XPOS_OFFSET                    0x80
#define PLANT_COB_TARGET_YPOS_OFFSET                    0x84
#define PLANT_PARTICLE_ID_OFFSET                        0x8C
#define PLANT_PROJECTILE_COUNTDOWN_OFFSET               0x90
#define PLANT_WAKEUP_COUNTDOWN_OFFSET                   0x130
#define PLANT_IMITATER_TYPE_OFFSET                      0x138
#define PLANT_IS_SQUASHED_OFFSET                        0x142
#define PLANT_IS_SLEEPING_OFFSET                        0x143
#define PLANT_ID_OFFSET                                 0x148

// Projectile object structure
#define PROJECTILE_STRUCT_SIZE                          0x94
#define PROJECTILE_IS_VISIBLE_OFFSET                    0x18
#define PROJECTILE_ROW_INDEX_OFFSET                     0x1C
#define PROJECTILE_XPOS_OFFSET                          0x30
#define PROJECTILE_YPOS_OFFSET                          0x34
#define PROJECTILE_IS_COLLIDING_OFFSET                  0x74
#define PROJECTILE_CATTAIL_TARGET_ID_OFFSET             0x88
#define PROJECTILE_ID_OFFSET                            0x90

// FloatingItem object structure
#define FLOATING_ITEM_STRUCT_SIZE                       0xD8
#define FLOATING_ITEM_WIDTH_OFFSET                      0x10
#define FLOATING_ITEM_HEIGHT_OFFSET                     0x14
#define FLOATING_ITEM_IS_VISIBLE_OFFSET                 0x18
#define FLOATING_ITEM_XPOS_OFFSET                       0x24
#define FLOATING_ITEM_YPOS_OFFSET                       0x28
#define FLOATING_ITEM_IS_COLLECTED_OFFSET               0x50
#define FLOATING_ITEM_DISAPPEAR_COUNTDOWN_OFFSET        0x54
#define FLOATING_ITEM_TYPE_OFFSET                       0x58
#define FLOATING_ITEM_HAS_HALO_OFFSET                   0xC8
#define FLOATING_ITEM_ID_OFFSET                         0xD0

// GridItem object structure
#define GRID_ITEM_STRUCT_SIZE                           0xEC
#define GRID_ITEM_TYPE_OFFSET                           0x8
#define GRID_ITEM_COLUMN_INDEX_OFFSET                   0x10
#define GRID_ITEM_ROW_INDEX_OFFSET                      0x14
#define GRID_ITEM_CRATER_COUNTDOWN_OFFSET               0x18
#define GRID_ITEM_ID_OFFSET                             0xE8

// Cursor object structure
#define CURSOR_XPOS_OFFSET                              0x8
#define CURSOR_YPOS_OFFSET                              0xC
#define CURSOR_SEED_INDEX_OFFSET                        0x24
#define CURSOR_PLANT_TYPE_OFFSET                        0x28
#define CURSOR_IMITATER_TYPE_OFFSET                     0x2C
#define CURSOR_HELD_ITEM_OFFSET                         0x30

// SeedBank object structure
#define SEED_BANK_IS_VISIBLE_OFFSET                     0x18
#define SEED_BANK_SLOT_COUNT_OFFSET                     0x24
#define SEED_BANK_SLOT_ARRAY_OFFSET                     0x28

// SeedSlot object structure
#define SEED_SLOT_STRUCT_SIZE                           0x50
#define SEED_SLOT_XPOS_OFFSET                           0x8
#define SEED_SLOT_YPOS_OFFSET                           0xC
#define SEED_SLOT_WIDTH_OFFSET                          0x10
#define SEED_SLOT_HEIGHT_OFFSET                         0x14
#define SEED_SLOT_IS_VISIBLE_OFFSET                     0x18
#define SEED_SLOT_RECHARGE_PROGRESS_OFFSET              0x24
#define SEED_SLOT_REFRESH_THRESHOLD_OFFSET              0x28
#define SEED_SLOT_INDEX_OFFSET                          0x2C
#define SEED_SLOT_TYPE_OFFSET                           0x34
#define SEED_SLOT_IMITATER_TYPE_OFFSET                  0x38
#define SEED_SLOT_IS_AVAILABLE_OFFSET                   0x48
#define SEED_SLOT_USAGE_COUNTER_OFFSET                  0x4C

// CardSelectionUI
#define CARD_SELECTION_UI_IS_ACTIVE_OFFSET              0x2C
#define CARD_SELECTION_UI_IS_ZOMBIE_GENERATED_OFFSET    0x35

// Button object structure
#define BUTTON_XPOS_OFFSET                              0x8
#define BUTTON_YPOS_OFFSET                              0xC
#define BUTTON_WIDTH_OFFSET                             0x10
#define BUTTON_HEIGHT_OFFSET                            0x14
#define BUTTON_IS_DISABLED_OFFSET                       0x1A
#define BUTTON_IS_HIDDEN_OFFSET                         0xF9

// PreGameUI object structure
#define PRE_GAME_UI_LETS_ROCK_BUTTON_PTR_OFFSET         0x88
#define PRE_GAME_UI_CARD_ARRAY_OFFSET                   0xA4
#define PRE_GAME_UI_NEXT_SLOT_INDEX_OFFSET              0xD24

// PlantCard object structure
#define PLANT_CARD_STRUCT_SIZE                          0x3C
#define PLANT_CARD_XPOS_OFFSET                          0x0
#define PLANT_CARD_YPOS_OFFSET                          0x4
#define PLANT_CARD_TYPE_OFFSET                          0x20
#define PLANT_CARD_STATE_OFFSET                         0x24
#define PLANT_CARD_SLOT_INDEX_OFFSET                    0x28
#define PLANT_CARD_IMITATER_TYPE_OFFSET                 0x34
#define PLANT_CARD_IS_ENFORCED_OFFSET                   0x38

//
#pragma clang diagnostic pop
