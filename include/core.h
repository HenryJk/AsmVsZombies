//
// Created by henryj on 27/6/2021.
//

#pragma once

class Core {

public:
    static void* main_address;
    static void Init();
    static void Click(int x, int y, int key);
};