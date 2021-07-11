#include "pvz.h"

#include <windows.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <map>


using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

namespace {
    pvz::Base *base_ptr;
    int last_launch_tick = 0;
    int tick = 0;

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
            base_ptr->game_ptr->Click(slot.xpos + slot.width / 2, slot.ypos + slot.height / 2, 1);
            //pvz::ClickBattlefield(base_ptr->game_ptr, slot.xpos + slot.width / 2, slot.ypos + slot.height / 2, 1);
            return;
        }
    }

    auto timing = std::chrono::high_resolution_clock::now();
    int stage_finished_tick = tick;
}

void OnZombieSpawn(pvz::Zombie *zombie_ptr) {
    zombie_ptr->is_visible = false;
}

void OnTick(pvz::Game *game_ptr) {
    tick++;
    auto pregame_ui_ptr = base_ptr->pregame_ui_ptr;
    //auto game_ptr = base_ptr->game_ptr;
    if (game_ptr->card_selection_ui_ptr->is_active) {
        pregame_ui_ptr->SelectImitaterCard(pvz::PlantType::kIceShroom);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kIceShroom);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kCoffeeBean);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kDoomShroom);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kLilyPad);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kSquash);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kCherryBomb);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kBlover);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kPumpkin);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kPuffShroom);
        pregame_ui_ptr->LetsRock();

        uint32_t total_damage = 0;
        for (int i = 0; i < game_ptr->plant_count; i++) {
            auto &plant = game_ptr->plant_ptr[i];
            if (plant.id >> 16 == 0) continue;
            if (plant.type == pvz::PlantType::kPumpkin) continue;
            total_damage += (plant.max_hp - plant.hp);
        }

        auto now = std::chrono::high_resolution_clock::now();
        duration<double, std::milli> ms_double = now - timing;
        std::cout << ms_double.count() << "ms for " << tick - stage_finished_tick << " tick to finish a stage ("
                  << (tick - stage_finished_tick)/ms_double.count() * 1000 << " tps), " << total_damage << " damage taken" << std::endl;
        stage_finished_tick = tick;
        timing = now;

        return;
    }

//    for (int i = 0; i < game_ptr->zombie_count; i++) game_ptr->zombie_ptr[i].is_visible = false;
//    for (int i = 0; i < game_ptr->plant_count; i++) game_ptr->plant_ptr[i].is_visible = false;
//    for (int i = 0; i < game_ptr->projectile_count; i++) game_ptr->projectile_ptr[i].is_visible = false;


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
            game_ptr->Click(80 * col + 80, 85 * row + 145, 1);
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
                plant.LaunchCob(620, 210);
            } else {
                plant.LaunchCob(620, 485);
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
        auto &seed_bank = *game_ptr->seed_bank_ptr;\
        game_ptr->Click(0, 0, -1);
        SelectSeed(pvz::PlantType::kBlover);
        game_ptr->Click(80, 145, 1);
        break;
    }

}

void OnHit(pvz::Projectile *projectile_ptr, pvz::Zombie *zombie_ptr) {
    projectile_ptr->type = pvz::ProjectileType::kCob;
}


BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            pvz::EnableSpeedUnlock();
            pvz::EnableAutoCollect();
            pvz::EnableAutoCollect();
            base_ptr = &pvz::Base::GetInstance();
            base_ptr->ms_per_tick = 10;
//            pvz::RegisterOnTickHook(OnTick);
//            pvz::RegisterOnZombieCreatedHook(OnZombieSpawn);
            pvz::RegisterOnProjectileCollideHook(OnHit);
            break;
        case DLL_PROCESS_DETACH:
            base_ptr->ms_per_tick = 10;
            pvz::DisableAllHooks();
            pvz::DisableAllCheats();
            break;
        default:
            return FALSE;
    }
    return TRUE; // successful
}
