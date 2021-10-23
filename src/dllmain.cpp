#include "pvz.hpp"
#include "hook.hpp"

#include <windows.h>

#include <bits/stdc++.h>

#define OFFSET_OF(type, field) &(((type *) NULL)->field)
using namespace std;

int tick = 1;
void shoot() {
  if (tick % 1000) {
    tick++;
    return;
  }
  pvz::LawnApp app = *(pvz::LawnApp *)((void*)((uint32_t *)0x6A9EC0));
  auto pd = app.mBoard->mPlants;
  for (int i = 0; i < pd.mSize; i++) {
    auto plant = pd.mBlock[i].mItem;
    if (plant.mSeedType == pvz::SeedType::kCobcannon) {
      plant.CobCannonFire(400, 300);
      cout << "shooting" << endl << endl;
      break;
    }
  }
  tick++;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    cout << hex << endl;
    cout << OFFSET_OF(pvz::Board, mChocolateCollected) << endl;
    cout << sizeof(pvz::Board) << endl;

    pvz::RegisterOnTickHook(shoot);

    //cout << sizeof(string) << endl;
    break;
  case DLL_PROCESS_DETACH:

    break;
  default:
    return FALSE;
  }
  return TRUE; // successful
}
