#pragma once

struct Event {
    int key;
    int action;
};

struct Tile {
    bool full { false };
    // color if the tile is not full
    glm::vec4 bg { 0.0f, 0.0f, 0.0f, 1.0f }; // background
    // color if tile is full
    glm::vec4 fg { 1.0f, 1.0f, 1.0f, 1.0f }; // foreground
};

struct Block {
    int pos[2] {};
    std::vector<int[2]> tiles;
    glm::vec4 color { 1.0f, 1.0f, 1.0f, 1.0f };
};
