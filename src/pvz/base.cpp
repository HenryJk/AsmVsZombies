//
// Created by henryj on 28/6/2021.
//

#include "address.h"

#include "pvz/base.h"

double PvZ::Base::GetMusicVolume() {
    return *(double*)((char*)this + MUSIC_VOLUME_OFFSET);
}

void PvZ::Base::SetMusicVolume(double v) {
    *(double*)((char*)this + MUSIC_VOLUME_OFFSET) = v;
}

double PvZ::Base::GetSFXVolume() {
    return *(double*)((char*)this + 0xD8);
}