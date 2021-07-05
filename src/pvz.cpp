//
// Created by henryj on 2/7/2021.
//

#include <cstdint>
#include "pvz.h"

void pvz::SelectCard(PreGameUI *pregame_ui_ptr, PlantType card_type) {
    auto &card = pregame_ui_ptr->card[(uint32_t)card_type];
    card.state = pvz::CardState::kSelected;
    card.slot_index = pregame_ui_ptr->next_slot_index;
    pregame_ui_ptr->next_slot_index++;
}

void pvz::SelectImitaterCard(PreGameUI *pregame_ui_ptr, PlantType imitater_type) {
    auto &card = pregame_ui_ptr->card[(uint32_t)PlantType::kImitater];
    card.state = pvz::CardState::kSelected;
    card.imitater_type = imitater_type;
    card.slot_index = pregame_ui_ptr->next_slot_index;
    pregame_ui_ptr->next_slot_index++;
}