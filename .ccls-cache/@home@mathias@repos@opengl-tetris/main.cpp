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

#include "block.h"
#include "events.h"

// callbacks
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// board dimensoins
int boardW { 10 };
int boardH { 20 };

// pos of black tile
int blocX {}, blocY{};

Key events;

int main(int argc, char *argv[]) {
    // time actions independent of fps
    float deltaTime { 0.0f };
    float lastFrame { 0.0f };

    std::vector<std::array<int, 2>> iblock {
        {0, 0},
        {0, 1},
        {0, 2},
        {0, 3},
    };

    Block din(iblock, 4, boardW, boardH);

    std::vector<std::array<int, 2>> there;

    // start glfw and create window etc.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int windowW { 500 };
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

    glViewport(0, 0, 500, 1000);

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

    // for drawing tiles
    float x { 1.0f }, y { 1.0f};
    float w { 2.0f / (float)boardW };
    float h { 2.0f / (float)boardH };


    glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 black(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);

    glm::vec4 color { white };

    // move black tile every n seconds 

    float tps { 2.0f };
    float counter { tps };

    // main loop
    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        din.move(tps, deltaTime, boardH, &there);

        if(blocY == boardH)
            blocY = 0;

        glClearColor(0.26f, 0.53f, 0.96f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderPogram.use();

        BLOCZ.Bind();

        glfwGetWindowSize(window, &windowW, &windowH);

        x = 1.0f;
        y = 1.0f;

        if(events.checkDown(events.left) && din.x < boardW - 1) {
            din.x += 1;
        }

        if(events.checkDown(events.right) && din.x > 0) {
            din.x -= 1;
        }

        for(int xInd {}; xInd<boardW; ++xInd) {
            for(int yInd {}; yInd<boardH; ++yInd) {
                std::cout << xInd << 'x' << yInd << "- " << "x: " << x << ", y: " << y << '\n';
                std::array<int, 2> ind { din.x - xInd, din.y - yInd };
                std::array<int, 2> pos = { xInd, yInd };
                if(std::find(din.shape.begin(), din.shape.end(), ind) != din.shape.end())
                    color = black;
                else
                    color = white;

                if(std::find(there.begin(), there.end(), pos) != there.end())
                    color = red;

                glm::mat4 transform = glm::mat4(1.0f);
                transform = glm::translate(transform, glm::vec3(x - w, y - h, 0.0f));
                transform = glm::scale(transform, glm::vec3(w, h, 1.0f));
                shaderPogram.setMat4f("transform", 1, glm::value_ptr(transform));
                shaderPogram.setVec4f("color", 1, glm::value_ptr(color));
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                y -= h;
            }
            x -= w;
            y = 1.0f;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
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
    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_F2:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            case GLFW_KEY_F3:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            case GLFW_KEY_LEFT:
                events.press(events.left);
                break;
            case GLFW_KEY_RIGHT:
                events.press(events.right);
                break;
            default:
                std::cout << glfwGetKeyName(key, scancode) << " pressed!\n";
                break;
        }
    }
    if(action == GLFW_RELEASE) {
        switch(key) {
            case GLFW_KEY_LEFT:
                events.release(0);
                break;
            case GLFW_KEY_RIGHT:
                events.release(1);
                break;
            default:
                std::cout << glfwGetKeyName(key, scancode) << " released!\n";
                break;
        }
    }
}
