//
// Created by henryj on 27/6/2021.
//

// clang-format off
#ifndef ASMVSZOMBIES_ADDRESS_H
#define ASMVSZOMBIES_ADDRESS_H

#define _STR(x) #x
#define STR(x) _STR(x)

#ifdef VERSION_1_0_0_1051 // Original English
    #define BASE_ADDRESS 0x6A9EC0
    #define CLICK_SCENE_CALL_ADDRESS 0x411F20
    #define CLICK_CALL_ADDRESS 0x539390

#elif VERSION_1_0_0_105123 // Dummy
  #define CLICK_FUNC_ADDRESS 0x00
#endif

#endif // ASMVSZOMBIES_ADDRESS_H
// clang-format on
