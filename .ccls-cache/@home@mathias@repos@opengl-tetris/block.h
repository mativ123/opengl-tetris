#pragma once

class Block {
    private:
        float counter { 1.0f };
        int boardW;
        int boardH;
        int blockH;

    public:
        Block(std::vector<std::array<int, 2>> preset, int h, int boardW, int boardH);
        int move(float rate, float deltaTime, int h, std::vector<std::array<int, 2>> *there);

        std::vector<std::array<int, 2>> shape {};
        int x {};
        int y {};
        bool moving { true };
};
