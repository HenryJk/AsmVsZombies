#include "event.hpp"
#include "pvz.hpp"

#include <windows.h>

#include <cmath>
#include <iostream>
#include <vector>


#define OFFSET_OF(type, field) &(((type *) NULL)->field)
using namespace std;
using namespace pvz;

namespace {
    int plant_health_style  = 0;
    int zombie_health_style = 0;

    LRESULT(CALLBACK *ScWndProc)(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK NewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (uMsg == WM_KEYDOWN) {
            if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_MENU) & 0x8000)) {
                if (wParam == 0x50) {
                    plant_health_style++;
                    plant_health_style %= 3;
                } else if (wParam == 0x5A) {
                    zombie_health_style++;
                    zombie_health_style %= 3;
                }
            }
        }
        return CallWindowProc(ScWndProc, hwnd, uMsg, wParam, lParam);
    }
} // namespace

void update(pvz::Event *event) {}

void DrawHealthBar(pvz::Event *event) {
    auto app        = LawnApp::GetInstance();
    auto d3d_device = app.mDDInterface->mD3DInterface->mD3DDevice;
    auto &board     = *app.mBoard;
    auto &plants    = board.mPlants;
    auto &zombies   = board.mZombies;

    uint32_t black     = 0xFF000000;
    uint32_t dark_gray = 0xFF303030;
    uint32_t soft_blue = 0xFF008FC7;
    uint32_t soft_red  = 0xFFA10B0B;

    vector<D3DRECT> health_bar_containers;
    vector<D3DRECT> health_bar;
    if (plant_health_style) {
        for (int i = 0; i < plants.mMaxUsedCount; i++) {
            if ((plants.mBlock[i].mID >> 16) == 0) continue;
            auto &plant = plants.mBlock[i].mItem;
            if (plant.mDead) continue;
            D3DRECT container_rectangle, health_rectangle, missing_rectangle;
            int32_t rectangle_length;
            uint8_t health_color[4];
            if (plant_health_style == 1) {
                health_color[0] = 0;
                health_color[1] = (uint8_t) (255.0 * sqrt((float) plant.mPlantHealth / plant.mPlantMaxHealth));
                health_color[2] = (uint8_t) (255.0 * sqrt(1.0 - ((float) plant.mPlantHealth / plant.mPlantMaxHealth)));
                health_color[3] = 0xFF;
            } else {
                (uint32_t &) health_color[0] = soft_blue;
            }
            switch (plant.mSeedType) {
                case SeedType::kPumpkinshell:
                    rectangle_length    = 60 * plant.mPlantHealth / plant.mPlantMaxHealth;
                    container_rectangle = {
                            max(plant.mX + board.mX + 9, 0),
                            plant.mY + board.mY - 6,
                            plant.mX + board.mX + 71,
                            plant.mY + board.mY - 1,
                    };
                    health_rectangle = {
                            max(plant.mX + board.mX + 10, 0),
                            plant.mY + board.mY - 5,
                            plant.mX + board.mX + rectangle_length + 10,
                            plant.mY + board.mY - 2,
                    };
                    missing_rectangle = {
                            max(plant.mX + board.mX + rectangle_length + 10, 0),
                            plant.mY + board.mY - 5,
                            plant.mX + board.mX + 70,
                            plant.mY + board.mY - 2,
                    };
                    break;
                case SeedType::kLilypad:
                case SeedType::kFlowerpot:
                    rectangle_length    = 60 * plant.mPlantHealth / plant.mPlantMaxHealth;
                    container_rectangle = {
                            max(plant.mX + board.mX + 9, 0),
                            plant.mY + board.mY + 4,
                            plant.mX + board.mX + 71,
                            plant.mY + board.mY + 9,
                    };
                    health_rectangle = {
                            max(plant.mX + board.mX + 10, 0),
                            plant.mY + board.mY + 5,
                            plant.mX + board.mX + rectangle_length + 10,
                            plant.mY + board.mY + 8,
                    };
                    missing_rectangle = {
                            max(plant.mX + board.mX + rectangle_length + 10, 0),
                            plant.mY + board.mY + 5,
                            plant.mX + board.mX + 70,
                            plant.mY + board.mY + 8,
                    };
                    break;
                case SeedType::kCobcannon:
                    rectangle_length    = 140 * plant.mPlantHealth / plant.mPlantMaxHealth;
                    container_rectangle = {
                            max(plant.mX + board.mX + 9, 0),
                            plant.mY + board.mY - 1,
                            plant.mX + board.mX + 151,
                            plant.mY + board.mY + 4,
                    };
                    health_rectangle = {
                            max(plant.mX + board.mX + 10, 0),
                            plant.mY + board.mY,
                            plant.mX + board.mX + rectangle_length + 10,
                            plant.mY + board.mY + 3,
                    };
                    missing_rectangle = {
                            max(plant.mX + board.mX + rectangle_length + 10, 0),
                            plant.mY + board.mY,
                            plant.mX + board.mX + 150,
                            plant.mY + board.mY + 3,
                    };
                    break;
                default:
                    rectangle_length    = 60 * plant.mPlantHealth / plant.mPlantMaxHealth;
                    container_rectangle = {
                            max(plant.mX + board.mX + 9, 0),
                            plant.mY + board.mY - 1,
                            plant.mX + board.mX + 71,
                            plant.mY + board.mY + 4,
                    };
                    health_rectangle = {
                            max(plant.mX + board.mX + 10, 0),
                            plant.mY + board.mY,
                            plant.mX + board.mX + rectangle_length + 10,
                            plant.mY + board.mY + 3,
                    };
                    missing_rectangle = {
                            max(plant.mX + board.mX + rectangle_length + 10, 0),
                            plant.mY + board.mY,
                            plant.mX + board.mX + 70,
                            plant.mY + board.mY + 3,
                    };
                    break;
            }
            if (container_rectangle.x2 >= 0) {
                d3d_device->Clear(1, &container_rectangle, D3DCLEAR_TARGET, black, 0.0, 0);
            }
            if (health_rectangle.x2 >= 0) {
                d3d_device->Clear(1, &health_rectangle, D3DCLEAR_TARGET, *(uint32_t *) health_color, 0.0, 0);
            }
            if (missing_rectangle.x2 >= 0) {
                d3d_device->Clear(1, &missing_rectangle, D3DCLEAR_TARGET, dark_gray, 0.0, 0);
            }
        }
    }

    if (zombie_health_style) {
        for (int i = 0; i < zombies.mMaxUsedCount; i++) {
            if ((zombies.mBlock[i].mID >> 16) == 0) continue;
            auto &zombie = zombies.mBlock[i].mItem;
            if (zombie.mDead) continue;
            D3DRECT container_rectangle, health_rectangle, missing_rectangle;
            uint8_t health_color[4];
            auto current_health = zombie.mBodyHealth + zombie.mHelmHealth;
            auto max_health     = zombie.mBodyMaxHealth + zombie.mHelmMaxHealth;
            if (zombie_health_style == 1) {
                health_color[0] = 0;
                health_color[1] = (uint8_t) (255.0 * sqrt((float) current_health / max_health));
                health_color[2] = (uint8_t) (255.0 * sqrt(1.0 - ((float) current_health / max_health)));
                health_color[3] = 0xFF;
            } else {
                (uint32_t &) health_color[0] = soft_red;
            }
            int32_t rectangle_length = (zombie.mZombieRect.mWidth + 18) * current_health / max_health;

            container_rectangle = {
                    max(zombie.mX + zombie.mZombieRect.mX + board.mX - 10, 0),
                    zombie.mY + zombie.mZombieRect.mY - (int32_t)zombie.mAltitude + board.mY - 5,
                    zombie.mX + zombie.mZombieRect.mX + board.mX + zombie.mZombieRect.mWidth + 10,
                    zombie.mY + zombie.mZombieRect.mY - (int32_t)zombie.mAltitude + board.mY,
            };
            health_rectangle = {
                    max(zombie.mX + zombie.mZombieRect.mX + board.mX - 9, 0),
                    zombie.mY + zombie.mZombieRect.mY - (int32_t)zombie.mAltitude + board.mY - 4,
                    zombie.mX + zombie.mZombieRect.mX + board.mX - 9 + rectangle_length,
                    zombie.mY + zombie.mZombieRect.mY - (int32_t)zombie.mAltitude + board.mY - 1,
            };
            missing_rectangle = {
                    max(zombie.mX + zombie.mZombieRect.mX + board.mX - 9 + rectangle_length, 0),
                    zombie.mY + zombie.mZombieRect.mY - (int32_t)zombie.mAltitude + board.mY - 4,
                    zombie.mX + zombie.mZombieRect.mX + board.mX + zombie.mZombieRect.mWidth + 9,
                    zombie.mY + zombie.mZombieRect.mY - (int32_t)zombie.mAltitude + board.mY - 1,
            };
            if (container_rectangle.x2 >= 0) {
                d3d_device->Clear(1, &container_rectangle, D3DCLEAR_TARGET, black, 0.0, 0);
            }
            if (health_rectangle.x2 >= 0) {
                d3d_device->Clear(1, &health_rectangle, D3DCLEAR_TARGET, *(uint32_t *) health_color, 0.0, 0);
            }
            if (missing_rectangle.x2 >= 0) {
                d3d_device->Clear(1, &missing_rectangle, D3DCLEAR_TARGET, dark_gray, 0.0, 0);
            }
        }
    }
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            //pvz::RegisterOnTickHook(shoot);
            //            Event::InjectEventHandler(EventType::kBoard_UpdateGameObjects, update);
            Event::InjectEventHandler(EventType::kBoard_DrawGameObjects, DrawHealthBar);

            ScWndProc = (LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM)) SetWindowLongPtr(
                    LawnApp::GetInstance().mHWnd, GWL_WNDPROC, (long) NewWndProc);

            //cout << sizeof(string) << endl;
            break;
        case DLL_PROCESS_DETACH:

            break;
        default:
            return FALSE;
    }
    return TRUE; // successful
}
