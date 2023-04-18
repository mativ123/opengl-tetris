#include <iostream>
#include <iomanip>
#include "common/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <numeric>
#include <algorithm>
#include <array>

#include "common/Texture.h"
#include "common/shader.h"
#include "common/VAO.h"
#include "common/EBO.h"
#include "common/VBO.h"

// callbacks
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
bool CheckInput(int key, int action);

const unsigned int boardW { 10 };
const unsigned int  boardH = { 20 };

float tileW {};
float tileH {};

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

int BlockGravity(int pos);

void CreateColumn(std::vector<Tile>& column);

std::vector<Event> events {};
std::vector<Event> eventsBuffer {};

Tile tiles[boardW][boardH] {};

int main(int argc, char *argv[]) {
    unsigned int pos { boardH - 1 };

    // time actions independent of fps
    float deltaTime { 0.0f };
    float lastFrame { 0.0f };

    // start glfw and create window etc.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int windowW { 1000 };
    int windowH { 1000 };

    GLFWwindow *window = glfwCreateWindow(windowW, windowH, "tetros", NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, windowW, windowH);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // define tiles to be drawn on the board
    float verts[] {
         1.0f,  1.0f, 0.0f, // top right
         1.0f, -1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f, // top left
    };

    unsigned int inds[] {
        0, 1, 2,
        2, 3, 0,
    };

    Shader shaderPogram("default.vert", "default.frag");

    VAO BLOCZ;
    BLOCZ.Bind();

    VBO VBO1(verts, sizeof(verts));
    EBO BLOC(inds, sizeof(inds));

    BLOCZ.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    BLOCZ.Unbind();
    VBO1.Unbind();

    glm::mat4 transform = glm::mat4(1.0f);

    unsigned int t_windowW { 0 };
    unsigned int t_windowH { 0 };
    
    float counter { 0.0f };

    while(!glfwWindowShouldClose(window)) {
        eventsBuffer = events;

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        std::cout << "fps: " << 1000 / deltaTime << '\n';

        counter += deltaTime;

        if(counter > 1) {
            pos = BlockGravity(pos);
            counter = 0;
        }

        if(CheckInput(GLFW_KEY_F2, GLFW_PRESS)) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        if(CheckInput(GLFW_KEY_F3, GLFW_PRESS)) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        glClearColor(0.26f, 0.53f, 0.96f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderPogram.use();

        BLOCZ.Bind();

        glfwGetWindowSize(window, &windowW, &windowH);

        // normalized dimensions of a tile
        tileW = (float)(windowW / boardW) / windowW;
        tileH = (float)(windowH / boardH) / windowH;
        
        for(int x {}; x<boardW; ++x) {
            for(int y {}; y<boardH; ++y) {
                if(tiles[x][y].full) {
                    shaderPogram.setVec4f("color", 1, glm::value_ptr(tiles[x][y].fg));
                } else {
                    shaderPogram.setVec4f("color", 1, glm::value_ptr(tiles[x][y].bg));
                }
                transform = glm::mat4(1.0f);
                // offset tile by half a tile width
                transform = glm::translate(transform, glm::vec3(tileW, tileH, 0.0f));

                // multiply by 2 to tranlate the correct distance
                transform = glm::translate(transform, glm::vec3(tileW * 2 * (x - (float)boardW / 2), tileH * 2 * (y - (float)boardH / 2), 0.0f));
                transform = glm::scale(transform, glm::vec3(tileW, tileH, 1.0f));
                shaderPogram.setMat4f("transform", 1, glm::value_ptr(transform));

                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            transform = glm::translate(transform, glm::vec3(2.0f, 0.0f, 0.0f));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        if(events.size() == eventsBuffer.size() && !events.empty()) {
            events.clear();
        }

        eventsBuffer.clear();
    }

    // cleanup
    BLOC.Delete();
    BLOCZ.Delete();
    VBO1.Delete();

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Event tmp = { key, action };
    events.push_back(tmp);
}

bool CheckInput(int key, int action) {
    for(Event event : events) {
        return event.key == key && event.action == action;
    }

    return false;
}

int BlockGravity(int pos) {
    // reset color of last pos
    if (pos + 1 < boardH)
        tiles[5][pos + 1].full = false;

    // loop position
    if(pos < 0)
        pos = boardH - 1;

    tiles[5][pos].full = true;

    return pos - 1;
}
