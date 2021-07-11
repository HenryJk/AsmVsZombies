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
} // namespace

void OnTick(pvz::Game *game_ptr) {}

void OnFrame(IDirect3DDevice7 *d3d_device) {
    if (base_ptr->game_ptr == nullptr) return;
    auto &game = *(base_ptr->game_ptr);
    std::vector<pvz::Plant *> bottom_plants;
    std::vector<pvz::Plant *> middle_plants;
    std::vector<pvz::Plant *> pumpkins;
    for (int i = 0; i < game.plant_count; i++) {
        auto &plant = game.plant_ptr[i];
        if (plant.id >> 16 == 0) continue;
        if (plant.is_squashed) continue;
        if (plant.is_disappearing) continue;
        switch (plant.type) {
            case pvz::PlantType::kPumpkin:
                pumpkins.push_back(&plant);
                break;
            case pvz::PlantType::kLilyPad:
            case pvz::PlantType::kFlowerPot:
                bottom_plants.push_back(&plant);
                break;
            default:
                middle_plants.push_back(&plant);
        }
    }
    std::vector<D3DRECT> health_bars;
    for (auto &plant_ptr : bottom_plants) {
        health_bars.push_back(D3DRECT{
                (LONG) plant_ptr->xpos + 4,
                (LONG) plant_ptr->ypos + 4,
                (LONG) plant_ptr->xpos + 76,
                (LONG) plant_ptr->ypos + 9,
        });
    }
    for (auto &plant_ptr : middle_plants) {
        health_bars.push_back(D3DRECT{
                (LONG) plant_ptr->xpos + 4,
                (LONG) plant_ptr->ypos - 1,
                (LONG) plant_ptr->xpos + 76,
                (LONG) plant_ptr->ypos + 4,
        });
    }
    for (auto &plant_ptr : pumpkins) {
        health_bars.push_back(D3DRECT{
                (LONG) plant_ptr->xpos + 4,
                (LONG) plant_ptr->ypos - 6,
                (LONG) plant_ptr->xpos + 76,
                (LONG) plant_ptr->ypos - 1,
        });
    }
    if (health_bars.empty()) return;
    d3d_device->Clear(health_bars.size(), &health_bars[0], D3DCLEAR_TARGET, 0x00000000, 0.0, 0);

    health_bars.clear();
    for (auto &plant_ptr : bottom_plants) {
        if (plant_ptr->hp != plant_ptr->max_hp) continue;
        health_bars.push_back(D3DRECT{
                (LONG) plant_ptr->xpos + 5,
                (LONG) plant_ptr->ypos + 5,
                (LONG) plant_ptr->xpos + 75,
                (LONG) plant_ptr->ypos + 8,
        });
    }
    for (auto &plant_ptr : middle_plants) {
        if (plant_ptr->hp != plant_ptr->max_hp) continue;
        health_bars.push_back(D3DRECT{
                (LONG) plant_ptr->xpos + 5,
                (LONG) plant_ptr->ypos,
                (LONG) plant_ptr->xpos + 75,
                (LONG) plant_ptr->ypos + 3,
        });
    }
    for (auto &plant_ptr : pumpkins) {
        if (plant_ptr->hp != plant_ptr->max_hp) continue;
        health_bars.push_back(D3DRECT{
                (LONG) plant_ptr->xpos + 5,
                (LONG) plant_ptr->ypos - 5,
                (LONG) plant_ptr->xpos + 75,
                (LONG) plant_ptr->ypos - 2,
        });
    }
    if (!health_bars.empty()) {
        d3d_device->Clear(health_bars.size(), &health_bars[0], D3DCLEAR_TARGET, 0xFF00FF00, 0.0, 0);
        health_bars.clear();
    }

    for (auto &plant_ptr : bottom_plants) {
        if (plant_ptr->hp == plant_ptr->max_hp) continue;
        D3DRECT bar = {
                (LONG) plant_ptr->xpos + 5,
                (LONG) plant_ptr->ypos + 5,
                (LONG) (plant_ptr->xpos + 5 + (70 * plant_ptr->hp / plant_ptr->max_hp)),
                (LONG) plant_ptr->ypos + 8,
        };
        auto red = 0xFF * (plant_ptr->max_hp - plant_ptr->hp) / plant_ptr->max_hp;
        auto green = 0xFF * plant_ptr->hp / plant_ptr->max_hp;
        uint8_t color[4] = {0, (uint8_t)green, (uint8_t)red, 0xFF};
        d3d_device->Clear(1, &bar, D3DCLEAR_TARGET, *(uint32_t *)color, 0.0, 0);
    }
    for (auto &plant_ptr : middle_plants) {
        if (plant_ptr->hp == plant_ptr->max_hp) continue;
        D3DRECT bar = {
                (LONG) plant_ptr->xpos + 5,
                (LONG) plant_ptr->ypos,
                (LONG) (plant_ptr->xpos + 5 + (70 * plant_ptr->hp / plant_ptr->max_hp)),
                (LONG) plant_ptr->ypos + 3,
        };
        auto red = 0xFF * (plant_ptr->max_hp - plant_ptr->hp) / plant_ptr->max_hp;
        auto green = 0xFF * plant_ptr->hp / plant_ptr->max_hp;
        uint8_t color[4] = {0, (uint8_t)green, (uint8_t)red, 0xFF};
        d3d_device->Clear(1, &bar, D3DCLEAR_TARGET, *(uint32_t *)color, 0.0, 0);
    }
    for (auto &plant_ptr : pumpkins) {
        if (plant_ptr->hp == plant_ptr->max_hp) continue;
        D3DRECT bar = {
                (LONG) plant_ptr->xpos + 5,
                (LONG) plant_ptr->ypos - 5,
                (LONG) (plant_ptr->xpos + 5 + (70 * plant_ptr->hp / plant_ptr->max_hp)),
                (LONG) plant_ptr->ypos - 2,
        };
        auto red = 0xFF * (plant_ptr->max_hp - plant_ptr->hp) / plant_ptr->max_hp;
        auto green = 0xFF * plant_ptr->hp / plant_ptr->max_hp;
        uint8_t color[4] = {0, (uint8_t)green, (uint8_t)red, 0xFF};
        d3d_device->Clear(1, &bar, D3DCLEAR_TARGET, *(uint32_t *)color, 0.0, 0);
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
