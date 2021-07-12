#include "pvz.h"

#include <chrono>
#include <d3d.h>
#include <iomanip>
#include <iostream>
#include <vector>
#include <windows.h>


using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

namespace {
    pvz::Base *base_ptr;
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

    std::vector<D3DRECT> CreateCurrentHpBar(pvz::Plant &plant) {
        LONG bar_length = plant.type == pvz::PlantType::kCobCannon ? 150 : 70;
        std::vector<LONG> separators;
        for (int tmp = 250; tmp < plant.hp; tmp += 250) {
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
        for (int i = 0; i < separators.size(); i++) {
            bars.push_back(D3DRECT{
                    current_bar_x + (LONG) plant.xpos + 5,
                    bar_y1,
                    separators[i] + (LONG) plant.xpos + 5 - (i % 4 == 3 ? 2 : 1),
                    bar_y2,
            });
            current_bar_x = separators[i];
        }
        //        for (auto &bar : bars) {
        //            std::cout << bar.x1 << " " << bar.x2 << std::endl;
        //        }
        //        std::cout << std::endl;
        return bars;
    }
} // namespace

void OnTick(pvz::Game *game_ptr) {}

void OnFrame(IDirect3DDevice7 *d3d_device) {
    if (base_ptr->game_ptr == nullptr) return;
    if (base_ptr->pregame_ui_ptr != nullptr) return;
    auto &game = *(base_ptr->game_ptr);
    if (game.is_paused) return;
    std::vector<pvz::Plant *> active_plants;
    for (int i = 0; i < game.plant_count; i++) {
        auto &plant = game.plant_ptr[i];
        if (plant.id >> 16 == 0) continue;
        if (plant.is_squashed) continue;
        if (plant.is_disappearing) continue;
        active_plants.push_back(&plant);
    }
    std::vector<D3DRECT> max_hp_bars;
    std::vector<D3DRECT> green_hp_bars;
    for (auto &plant_ptr : active_plants) {
        max_hp_bars.push_back(CreateMaxHpBar(*plant_ptr));
        auto current_hp_bar = CreateCurrentHpBar(*plant_ptr);
        if (plant_ptr->hp != plant_ptr->max_hp) continue;
        green_hp_bars.insert(green_hp_bars.end(), current_hp_bar.begin(), current_hp_bar.end());
    }
    if (!max_hp_bars.empty())
        d3d_device->Clear(max_hp_bars.size(), &max_hp_bars[0], D3DCLEAR_TARGET, 0x00000000, 0.0, 0);
    if (!green_hp_bars.empty())
        d3d_device->Clear(green_hp_bars.size(), &green_hp_bars[0], D3DCLEAR_TARGET, 0xFF00FF00, 0.0, 0);
    for (auto &plant_ptr : active_plants) {
        auto current_hp_bar = CreateCurrentHpBar(*plant_ptr);
        if (plant_ptr->hp == plant_ptr->max_hp) continue;
        auto red         = 0xFF * (plant_ptr->max_hp - plant_ptr->hp) / plant_ptr->max_hp;
        auto green       = 0xFF * plant_ptr->hp / plant_ptr->max_hp;
        uint8_t color[4] = {0, (uint8_t) green, (uint8_t) red, 0xFF};
        d3d_device->Clear(current_hp_bar.size(), &current_hp_bar[0], D3DCLEAR_TARGET, *(uint32_t *) color, 0.0, 0);
    }
}


BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            //            pvz::EnableSpeedUnlock();
            //            pvz::EnableAutoCollect();
            base_ptr              = &pvz::Base::GetInstance();
            base_ptr->ms_per_tick = 10;
            //            pvz::RegisterOnTickHook(OnTick);
            pvz::RegisterOnFrameRenderedHook(OnFrame);
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
