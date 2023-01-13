#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <GLFW/glfw3.h>

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

    return 1;
}

Block::Block(std::vector<std::array<int, 2>> preset) {
    shape = preset;
}

void Block::keys(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_RIGHT:
                x += 1;
                break;
            case GLFW_KEY_LEFT:
                x -= 1;
                break;
        }
    }

}
