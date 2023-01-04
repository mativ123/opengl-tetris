#include <vector>
#include <array>
#include <iostream>

#include "block.h"

int Block::move(float rate, float deltaTime, int h) {
    if(!moving)
        return 0;
    
    if(counter > 0)
        counter -= rate * deltaTime;
    else {
        counter = 1.0f;
        y += 1;
    }

    if(y == h - 1)
        moving = false;

    return 1;
}

Block::Block(std::vector<std::array<int, 2>> preset) {
    shape = preset;
}
