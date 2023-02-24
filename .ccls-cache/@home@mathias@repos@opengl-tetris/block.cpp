#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <GLFW/glfw3.h>

#include "block.h"


int Block::move(float rate, float deltaTime, int h, std::vector<std::array<int, 2>> *there) {
    if(!moving)
        return 0;
    
    if(counter > 0)
        counter -= rate * deltaTime;
    else {
        counter = 1.0f;
        y += 1;
    }

    if(y == boardH - 1) {
        for(std::array<int, 2> pos : shape) {
            std::array<int, 2> temp { pos[0] + x, pos[1] + y };
            there->push_back(temp);
        }
    }

    return 1;
}

Block::Block(std::vector<std::array<int, 2>> preset, int h, int inW, int inH) {
    shape = preset;
    boardW = inW;
    boardH = inH;
    blockH = h;
}
