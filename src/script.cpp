//
// Created by henryj on 2/7/2021.
//
#include "script.h"
#include "cheat.h"
#include "pvz.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <utility>

namespace {
    pvz::Base *base_ptr;
    int last_launch_tick = 0;
    int tick = 0;
    bool has_paused = false;
    bool has_printed = false;

    void debug(uint8_t *address, uint32_t length) {
        for (int i = 0; i < length; i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)address[i];
            if (i % 16 == 15) {
                std::cout << std::endl;
            } else if (i % 4 == 3) {
                std::cout << ' ';
            }
        }
        std::cout << std::endl << std::endl;
    }

    void SelectSeed(pvz::PlantType type) {
        auto &seed_bank = *base_ptr->game_ptr->seed_bank_ptr;
        for (int i = 0; i < seed_bank.slot_count; i++) {
            auto &slot = seed_bank.slot[i];
            if (slot.type != type) continue;
            pvz::ClickBattlefield(base_ptr->game_ptr, slot.xpos + slot.width / 2, slot.ypos + slot.height / 2, 1);
            return;
        }
    }
}

void script::OnHook() {
    base_ptr = *(pvz::Base **)BASE_PTR_ADDRESS;
    cheat::AutoCollect();
    cheat::NoDrop();
    cheat::AllowInfiniteSpeed();
    base_ptr->ms_per_tick = 0;
    //base_ptr->free_planting_mode = true;
}

void script::OnTick() {
    tick++;
    auto pregame_ui_ptr = base_ptr->pregame_ui_ptr;
    auto game_ptr = base_ptr->game_ptr;
    if (game_ptr->card_selection_ui_ptr->is_active) {
        pvz::SelectImitaterCard(pregame_ui_ptr, pvz::PlantType::kIceShroom);
        pvz::SelectCard(pregame_ui_ptr, pvz::PlantType::kIceShroom);
        pvz::SelectCard(pregame_ui_ptr, pvz::PlantType::kCoffeeBean);
        pvz::SelectCard(pregame_ui_ptr, pvz::PlantType::kDoomShroom);
        pvz::SelectCard(pregame_ui_ptr, pvz::PlantType::kLilyPad);
        pvz::SelectCard(pregame_ui_ptr, pvz::PlantType::kSquash);
        pvz::SelectCard(pregame_ui_ptr, pvz::PlantType::kCherryBomb);
        pvz::SelectCard(pregame_ui_ptr, pvz::PlantType::kBlover);
        pvz::SelectCard(pregame_ui_ptr, pvz::PlantType::kPumpkin);
        pvz::SelectCard(pregame_ui_ptr, pvz::PlantType::kPuffShroom);
        pvz::LetsRock(pregame_ui_ptr);
        return;
    }

    if (!has_printed) {
        for (int i = 0; i < game_ptr->plant_count; i++) {
            auto &plant = game_ptr->plant_ptr[i];
            debug((uint8_t *)&plant, PLANT_STRUCT_SIZE);
        }
        has_printed = true;
        return;
    } else {
        return;
    }

    std::map<std::pair<int, int>, int> pumpkin_hp;
    for (int i = 4; i <= 6; i++) {
        for (int j = 2; j <= 3; j++) {
            pumpkin_hp[{i, j}] = 0;
        }
    }
    for (int i = 0; i < game_ptr->plant_count; i++) {
        auto &plant = game_ptr->plant_ptr[i];
        if (plant.id >> 8 == 0) continue;
        if (plant.type != pvz::PlantType::kPumpkin) continue;
        pumpkin_hp[{(int)plant.column_index, (int)plant.row_index}] = (int)plant.hp;
    }
    int minimum_hp = 2000;
    for (auto &[pos, hp]: pumpkin_hp) minimum_hp = std::min(hp, minimum_hp);
    for (auto &[pos, hp]: pumpkin_hp) {
        if (hp == minimum_hp) {
            auto &[col, row] = pos;
            SelectSeed(pvz::PlantType::kPumpkin);
            pvz::ClickBattlefield(game_ptr, 80 * col + 80, 85 * row + 145, 1);
            break;
        }
    }

    if (game_ptr->spawned_wave_count == 0) return;

    auto tick_from_wave_spawn = game_ptr->next_wave_initial_countdown - game_ptr->next_wave_countdown;

    bool should_launch = (tick - last_launch_tick >= 870) && (tick_from_wave_spawn >= 870 - 200 - 373 && game_ptr->next_wave_countdown > 574);

    bool has_zombie = false;
    for (int i = 0; i < game_ptr->zombie_count; i++) {
        auto &zombie = game_ptr->zombie_ptr[i];
        if (zombie.id >> 16 == 0) continue;
        if (zombie.type == pvz::ZombieType::kImp) continue;
        if (zombie.type == pvz::ZombieType::kDiggerZombie) continue;
        if (zombie.type == pvz::ZombieType::kBungeeZombie) continue;
        if (zombie.row_index == 2 || zombie.row_index == 3) continue;
        if (zombie.hp == 0) continue;
        has_zombie = true;
        break;
    }

    if (should_launch && has_zombie) {
        int required_launch = 2;
        for (int i = 0; i < game_ptr->plant_count && required_launch; i++) {
            auto &plant = game_ptr->plant_ptr[i];
            if (plant.id >> 16 == 0) continue;
            if (plant.type != pvz::PlantType::kCobCannon) continue;
            if (plant.ability_countdown) continue;
            if (required_launch == 2) {
                pvz::LaunchCob(&plant, 620, 210);
            } else {
                pvz::LaunchCob(&plant, 620, 465);
            }
            required_launch--;
        }
        last_launch_tick = tick;
    }

    for (int i = 0; i < game_ptr->zombie_count; i++) {
        auto &zombie = game_ptr->zombie_ptr[i];
        if (zombie.id >> 16 == 0) continue;
        if (zombie.type != pvz::ZombieType::kBalloonZombie) continue;
        if (zombie.xpos > 150) continue;
        auto &seed_bank = *game_ptr->seed_bank_ptr;
        for (int j = 0; j < seed_bank.slot_count; j++) {
            auto &slot = seed_bank.slot[j];
            if (slot.type != pvz::PlantType::kBlover) continue;
            pvz::ClickBattlefield(game_ptr, slot.xpos + slot.width / 2, slot.ypos + slot.height / 2, 1);
            pvz::ClickBattlefield(game_ptr, 80, 165, 1);
        }
        break;
    }

    for (int i = 0; i < game_ptr->plant_count; i++) {
        auto &plant = game_ptr->plant_ptr[i];
        if (plant.id >> 8 == 0) continue;
        if (plant.type == pvz::PlantType::kPumpkin) continue;
        if (plant.hp < plant.max_hp || plant.is_squashed) {
            debug((uint8_t *)&plant, PLANT_STRUCT_SIZE);
            base_ptr->ms_per_tick = 200;
            if (!has_paused) {
                game_ptr->is_paused = true;
                has_paused = true;
            }
        }
    }

}