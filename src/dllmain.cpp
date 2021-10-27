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

    template<typename T>
    void _debug_print(T t) {
        cout << t << ");" << endl;
    }

    template<typename T, typename... Args>
    void _debug_print(T t, Args... params) {
        cout << t << ", ";
        _debug_print(params...);
    }

    template<typename... Args>
    void debug_print(const string &func, Args... params) {
        cout << func << "(";
        _debug_print(params...);
    }
} // namespace

void update(Event *event) {}

void TestBoardKillAllPlantsInRadius(Event *event) {
    debug_print("Board::KillAllPlantsInRadius", (void *) event->mParams[0], event->mParams[1], event->mParams[2]);
}

void TestPlantFire(Event *event) {
    debug_print("Plant::Fire",
                (void *) event->mParams[0],
                (void *) event->mParams[1],
                event->mParams[2],
                event->mParams[3]);
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            //pvz::RegisterOnTickHook(shoot);
            //            Event::InjectEventHandler(EventType::kBoard_UpdateGameObjects, update);
            //            ScWndProc = (LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM)) SetWindowLongPtr(
            //                    LawnApp::GetInstance().mHWnd, GWL_WNDPROC, (long) NewWndProc);
            //cout << sizeof(string) << endl;

            Event::InjectEventHandler(EventType::kBoard_KillAllPlantsInRadius, nullptr, TestBoardKillAllPlantsInRadius);
            Event::InjectEventHandler(EventType::kPlant_Fire, nullptr, TestPlantFire);
            break;
        case DLL_PROCESS_DETACH:
            break;
        default:
            return FALSE;
    }
    return TRUE; // successful
}
