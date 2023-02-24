#pragma once

class Key {
    private:
        std::vector<bool> states;

    public:
        unsigned int left;
        unsigned int right;

        Key();

        bool check(int key);
        bool checkDown(int key);
        void press(int key);
        void release(int key);
};
