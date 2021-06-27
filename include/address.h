//
// Created by henryj on 27/6/2021.
//
// clang-format off
#pragma once

#ifdef VERSION_1_0_0_1051_EN // Original English
    #define CLICK_SCENE_CALL_ADDRESS    0x411F20
    #define CLICK_CALL_ADDRESS 0x539390
    #define MAIN_LOOP_FUNC_ADDRESS      0x4130d0
    #define MAIN_LOOP_CALL_ADDRESS      0x415945

    #define BASE_ADDRESS 0x6A9EC0

#elif VERSION_1_2_0_1096_EN // Steam GOTY
    #define CLICK_SCENE_CALL_ADDRESS    0x414830
    #define MAIN_LOOP_FUNC_ADDRESS      0x4159E0
    #define MAIN_LOOP_CALL_ADDRESS      0x418195
    #define CLICK_FUNC_ADDRESS 0x00
#endif
// clang-format on
