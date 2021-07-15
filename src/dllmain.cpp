#include "pvz.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <windows.h>
#include <cmath>


using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

namespace {
    pvz::Base *base_ptr;
    int last_launch_tick = 0;
    int tick             = 0;

    void debug(uint8_t *address, uint32_t length) {
        for (int i = 0; i < length; i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (uint32_t) address[i];
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

    auto timing             = std::chrono::high_resolution_clock::now();
    int stage_finished_tick = tick;

    D3DRECT CreateMaxHpBar(pvz::Plant &plant) {
        switch (plant.type) {
            case pvz::PlantType::kPumpkin:
                return {
                        (LONG) plant.xpos + 4,
                        (LONG) plant.ypos - 6,
                        (LONG) plant.xpos + 75,
                        (LONG) plant.ypos - 1,
                };
            case pvz::PlantType::kLilyPad:
            case pvz::PlantType::kFlowerPot:
                return {
                        (LONG) plant.xpos + 4,
                        (LONG) plant.ypos + 4,
                        (LONG) plant.xpos + 75,
                        (LONG) plant.ypos + 9,
                };
            case pvz::PlantType::kCobCannon:
                return {
                        (LONG) plant.xpos + 4,
                        (LONG) plant.ypos - 1,
                        (LONG) plant.xpos + 155,
                        (LONG) plant.ypos + 4,
                };
            default:
                return {
                        (LONG) plant.xpos + 4,
                        (LONG) plant.ypos - 1,
                        (LONG) plant.xpos + 75,
                        (LONG) plant.ypos + 4,
                };
        }
    }

    std::vector<D3DRECT> CreateCurrentHpBar(pvz::Plant &plant, int separator_threshold) {
        LONG bar_length = plant.type == pvz::PlantType::kCobCannon ? 150 : 70;
        std::vector<LONG> separators;
        for (int tmp = separator_threshold; tmp < plant.hp; tmp += separator_threshold) {
            separators.push_back((LONG) (bar_length * tmp / plant.max_hp));
        }
        separators.push_back((LONG) (bar_length * plant.hp / plant.max_hp));

        std::vector<D3DRECT> bars;
        LONG current_bar_x = 0;
        LONG bar_y1, bar_y2;
        switch (plant.type) {
            case pvz::PlantType::kPumpkin:
                bar_y1 = (LONG) plant.ypos - 5;
                bar_y2 = (LONG) plant.ypos - 2;
                break;
            case pvz::PlantType::kFlowerPot:
            case pvz::PlantType::kLilyPad:
                bar_y1 = (LONG) plant.ypos + 5;
                bar_y2 = (LONG) plant.ypos + 8;
                break;
            default:
                bar_y1 = (LONG) plant.ypos;
                bar_y2 = (LONG) plant.ypos + 3;
        }
        for (long separator : separators) {
            bars.push_back(D3DRECT{
                    current_bar_x + (LONG) plant.xpos + 5,
                    bar_y1,
                    separator + (LONG) plant.xpos + 4,
                    bar_y2,
            });
            current_bar_x = separator;
        }
        //        for (auto &bar : bars) {
        //            std::cout << bar.x1 << " " << bar.x2 << std::endl;
        //        }
        //        std::cout << std::endl;
        return bars;
    }
} // namespace

void OnZombieSpawn(pvz::Zombie *zombie_ptr) { zombie_ptr->is_visible = false; }

void OnTick() {
    tick++;
    auto pregame_ui_ptr = base_ptr->pregame_ui_ptr;
    auto game_ptr       = base_ptr->game_ptr;
    if (game_ptr->card_selection_ui_ptr->is_active) {
//        pregame_ui_ptr->SelectImitaterCard(pvz::PlantType::kIceShroom);
        pregame_ui_ptr->SelectCard(pvz::PlantType::kTallNut);
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
                  << (tick - stage_finished_tick) / ms_double.count() * 1000 << " tps)" << std::endl;
        stage_finished_tick = tick;
        timing              = now;

        return;
    }

    //    for (int i = 0; i < game_ptr->zombie_count; i++) game_ptr->zombie_ptr[i].is_visible = false;
    //    for (int i = 0; i < game_ptr->plant_count; i++) game_ptr->plant_ptr[i].is_visible = false;
    //    for (int i = 0; i < game_ptr->projectile_count; i++) game_ptr->projectile_ptr[i].is_visible = false;


    std::map<std::pair<int, int>, int> pumpkin_hp;
    for (int i = 4; i <= 6; i++) {
        for (int j = 2; j <= 3; j++) { pumpkin_hp[{i, j}] = 0; }
    }
    for (int i = 0; i < game_ptr->plant_count; i++) {
        auto &plant = game_ptr->plant_ptr[i];
        if (plant.id >> 8 == 0) continue;
        if (plant.type != pvz::PlantType::kPumpkin) continue;
        pumpkin_hp[{(int) plant.column_index, (int) plant.row_index}] = (int) plant.hp;
    }
    int minimum_hp = 2000;
    for (auto &[pos, hp] : pumpkin_hp) minimum_hp = std::min(hp, minimum_hp);
    for (auto &[pos, hp] : pumpkin_hp) {
        if (hp == minimum_hp) {
            auto &[col, row] = pos;
            SelectSeed(pvz::PlantType::kPumpkin);
            game_ptr->Click(80 * col + 80, 85 * row + 145, 1);
            break;
        }
    }

    if (game_ptr->spawned_wave_count == 0) return;

    auto tick_from_wave_spawn = game_ptr->next_wave_initial_countdown - game_ptr->next_wave_countdown;

    bool should_launch = (tick - last_launch_tick >= 870) &&
                         (tick_from_wave_spawn >= 870 - 200 - 373 && game_ptr->next_wave_countdown > 574);

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
        auto &seed_bank = *game_ptr->seed_bank_ptr;
        game_ptr->Click(0, 0, -1);
        SelectSeed(pvz::PlantType::kBlover);
        game_ptr->Click(80, 145, 1);
        break;
    }
}

void OnHit(pvz::Projectile *projectile_ptr, pvz::Zombie *zombie_ptr) {
    projectile_ptr->type = pvz::ProjectileType::kCob;
}

void OnFrame(IDirect3DDevice7 *d3d_device) {
    if (base_ptr->game_ptr == nullptr) return;
    if (base_ptr->pregame_ui_ptr != nullptr) return;
    auto &game = *(base_ptr->game_ptr);
    if (game.is_paused) return;
    std::set<std::pair<uint32_t, uint32_t>> laddered_positions;
    for (int i = 0; i < game.grid_item_count; i++) {
        auto &grid_item = game.grid_item_ptr[i];
        if (grid_item.id >> 16 == 0) continue;
        if (grid_item.type != pvz::GridItemType::kLadder) continue;
        auto x = grid_item.column_index;
        auto y = grid_item.row_index;
        laddered_positions.emplace(x, y);
    }
    std::vector<pvz::Plant *> active_plants;
    for (int i = 0; i < game.plant_count; i++) {
        auto &plant = game.plant_ptr[i];
        if (plant.id >> 16 == 0) continue;
        if (plant.is_crushed) continue;
        if (plant.is_disappearing) continue;
        if (plant.is_disappearing) continue;
        if (plant.hp < 0) continue;
        auto x = plant.column_index;
        auto y = plant.row_index;
        if (laddered_positions.count({x, y})) continue;
        active_plants.push_back(&plant);
    }
    std::vector<D3DRECT> max_hp_bars;
    std::vector<D3DRECT> semi_green_hp_bars;
    std::vector<D3DRECT> green_hp_bars;
    for (auto &plant_ptr : active_plants) {
        max_hp_bars.push_back(CreateMaxHpBar(*plant_ptr));
        if (plant_ptr->hp != plant_ptr->max_hp) continue;
        auto current_hp_bar      = CreateCurrentHpBar(*plant_ptr, 250);
        auto semi_current_hp_bar = CreateCurrentHpBar(*plant_ptr, 1000);
        green_hp_bars.insert(green_hp_bars.end(), current_hp_bar.begin(), current_hp_bar.end());
        semi_green_hp_bars.insert(semi_green_hp_bars.end(), semi_current_hp_bar.begin(), semi_current_hp_bar.end());
    }
    if (!max_hp_bars.empty())
        d3d_device->Clear(max_hp_bars.size(), &max_hp_bars[0], D3DCLEAR_TARGET, 0x00000000, 0.0, 0);
    if (!semi_green_hp_bars.empty())
        d3d_device->Clear(semi_green_hp_bars.size(), &semi_green_hp_bars[0], D3DCLEAR_TARGET, 0xFF00BF00, 0.0, 0);
    if (!green_hp_bars.empty())
        d3d_device->Clear(green_hp_bars.size(), &green_hp_bars[0], D3DCLEAR_TARGET, 0xFF00FF00, 0.0, 0);

    for (auto &plant_ptr : active_plants) {
        if (plant_ptr->hp == plant_ptr->max_hp) continue;
        auto current_hp_bar      = CreateCurrentHpBar(*plant_ptr, 250);
        auto semi_current_hp_bar = CreateCurrentHpBar(*plant_ptr, 1000);
        auto red_multiplier = sqrt(((double)plant_ptr->max_hp - plant_ptr->hp) / plant_ptr->max_hp);
        auto green_multiplier = sqrt((double)plant_ptr->hp / plant_ptr->max_hp);
        auto red                 = 0xFF * red_multiplier;
        auto green               = 0xFF * green_multiplier;

        uint8_t color1[4] = {0, (uint8_t) (green * 3 / 4), (uint8_t) (red * 3 / 4), 0xFF};
        d3d_device->Clear(semi_current_hp_bar.size(), &semi_current_hp_bar[0], D3DCLEAR_TARGET, *(uint32_t *) color1,
                          0.0, 0);
        uint8_t color2[4] = {0, (uint8_t) green, (uint8_t) red, 0xFF};
        d3d_device->Clear(current_hp_bar.size(), &current_hp_bar[0], D3DCLEAR_TARGET, *(uint32_t *) color2, 0.0, 0);

    }
}

void OnBasketball(pvz::Projectile *projectile_ptr, pvz::Plant *plant_ptr) {
    projectile_ptr->type  = pvz::ProjectileType::kCob;
    plant_ptr->is_visible = !plant_ptr->is_visible;
}

void OnPlantBitten(pvz::Plant *plant_ptr, pvz::Zombie *zombie_ptr) {
    std::cout << (uint32_t)plant_ptr->type << std::endl;
    std::cout << (uint32_t)zombie_ptr->type << std::endl;
}

void OnSpikerockDamaged(pvz::Plant *plant_ptr, pvz::Zombie *zombie_ptr) {
    std::cout << "spikerock damaged\n";
    std::cout << (uint32_t) plant_ptr->type << ": " << plant_ptr->hp << std::endl;
    std::cout << (uint32_t) zombie_ptr->type << ": " << zombie_ptr->hp << std::endl;
}

void OnSpikeweedRanOver(pvz::Plant *plant_ptr, pvz::Zombie *zombie_ptr) {
    std::cout << "spikeplant ran over\n";
    std::cout << (uint32_t) plant_ptr->type << ": " << plant_ptr->hp << std::endl;
    std::cout << (uint32_t) zombie_ptr->type << ": " << zombie_ptr->hp << std::endl;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            pvz::EnableSpeedUnlock();
            pvz::EnableAutoCollect();
            pvz::EnableNoDrop();
            pvz::EnableBackgroundRunning();
            pvz::EnableNoSave();
            base_ptr = &pvz::Base::GetInstance();

//            base_ptr->ms_per_tick = 0;
//            pvz::RegisterOnTickHook(OnTick);
            //            pvz::RegisterOnProjectileCollideHook(OnHit);
//            pvz::RegisterOnZombieCreatedHook(OnZombieSpawn);
            pvz::RegisterOnFrameRenderedHook(OnFrame);
            pvz::RegisterOnSpikerockDamaged(OnSpikerockDamaged);
            pvz::RegisterOnSpikeplantRanOver(OnSpikeweedRanOver);
//            pvz::RegisterOnPlantFlattenedHook(OnPlantBitten);
            //            pvz::RegisterOnPlantBittenHook(OnPlantBitten);
            //            pvz::RegisterOnBasketballCollideHook(OnBasketball);
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
