//
// Created by henryj on 2/7/2021.
//
#include "script.h"
#include "pvz.h"

pvz::Base *base_ptr;

void script::OnHook() {
    base_ptr = *(pvz::Base **)BASE_PTR_ADDRESS;
}

int tick_counter = 0;
void script::OnTick() {
    tick_counter++;
    if (tick_counter % 100) return;
    pvz::ClickBattlefield(300, 300, 1, base_ptr->game_ptr);
}