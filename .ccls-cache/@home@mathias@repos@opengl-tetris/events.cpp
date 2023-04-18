#include <vector>
#include <algorithm>

#include "events.h"

Key::Key() {
    states.resize(2);
    std::fill(states.begin(), states.end(), false);

    left = 0;
    right = 1;
}

bool Key::check(int key) {
    return states[key];
}

bool Key::checkDown(int key) {
    if(states[key]) {
        states[key] = false;
        return true;
    }
    return false;
}

void Key::press(int key) {
    states[key] = true;
};

void Key::release(int key) {
    states[key] = false;
}
