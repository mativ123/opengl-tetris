#include <iostream>
#include "common/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common/Texture.h"
#include "common/shader.h"
#include "common/VAO.h"
#include "common/EBO.h"
#include "common/VBO.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main(int argc, char *argv[]) {
    float deltaTime { 0.0f };
    float lastFrame { 0.0f };

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
    BLOC.Unbind();

    glm::vec3 blocScale(0.25f, 0.25f, 0.5f);

    float y { 1.0f + blocScale[1] };
    float x {};

    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.26f, 0.53f, 0.96f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderPogram.use();

        BLOCZ.Bind();

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            x -= 0.7f * deltaTime;
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            x += 0.7f * deltaTime;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, 0.0f));
        glfwGetWindowSize(window, &windowW, &windowH);
        model = glm::scale(model, glm::vec3(1.0f, (float)windowW / (float)windowH, 1.0f) * blocScale);
        shaderPogram.setMat4f("model", 1, glm::value_ptr(model));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if(y < -(1.0f + blocScale[1] * (float)windowW / (float)windowH))
            y = 1.0f + blocScale[1] * (float)windowW / (float)windowH;
        else
            y -= 0.2f * deltaTime;
    }

    BLOC.Delete();
    BLOCZ.Delete();
    VBO1.Delete();

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
