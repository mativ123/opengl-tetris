#pragma once

class Block {
    private:
        float counter { 1.0f };

    public:
        Block(std::vector<std::array<int, 2>> preset);
        int move(float rate, float deltaTime, int h);
        void keys(GLFWwindow *window, int key, int scancode, int action, int mods);

        std::vector<std::array<int, 2>> shape {};
        int x {};
        int y {};
        bool moving { true };
};
