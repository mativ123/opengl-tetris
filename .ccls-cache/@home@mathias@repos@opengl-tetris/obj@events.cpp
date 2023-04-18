#include <array>
#include <algorithm>

#include "events.h"

bool key::check(int key) {
    return key::states[key];
}

void down(int key) {
    key::states[key] = true;
};

void up(int key) {
    key::states[key] = false;
}
