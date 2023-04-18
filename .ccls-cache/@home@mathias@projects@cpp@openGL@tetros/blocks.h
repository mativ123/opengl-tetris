#pragma once
float verts[] {
    // collumns (t-b)
    // right
    1.0f,  1.0f, 0.0f, // 0
    1.0f,  0.5f, 0.0f, // 1
    1.0f,  0.0f, 0.0f, // 2
    1.0f, -0.5f, 0.0f, // 3
    1.0f, -1.0f, 0.0f, // 4
    // center right
    0.5f,  1.0f, 0.0f, // 5
    0.5f,  0.5f, 0.0f, // 6
    0.5f,  0.0f, 0.0f, // 7
    0.5f, -0.5f, 0.0f, // 8
    0.5f, -1.0f, 0.0f, // 9
    // center          
    0.0f,  1.0f, 0.0f, // 10
    0.0f,  0.5f, 0.0f, // 11
    0.0f,  0.0f, 0.0f, // 12
    0.0f, -0.5f, 0.0f, // 13
    0.0f, -1.0f, 0.0f, // 14
    // center left
    -0.5f,  1.0f, 0.0f, // 15
    -0.5f,  0.5f, 0.0f, // 16
    -0.5f,  0.0f, 0.0f, // 17
    -0.5f, -0.5f, 0.0f, // 18
    -0.5f, -1.0f, 0.0f, // 19
    // left
    -1.0f,  1.0f, 0.0f, // 20
    -1.0f,  0.5f, 0.0f, // 21
    -1.0f,  0.0f, 0.0f, // 22
    -1.0f, -0.5f, 0.0f, // 23
    -1.0f, -1.0f, 0.0f, // 24
};

unsigned int iblock[] {
    23, 3, 4,
    23, 24, 4,
};

unsigned int jblock[] {
    17, 18, 13,
    17, 12, 13,
    18, 19, 4,
    4, 3, 18,
};

unsigned int lblock[] {
    7, 2, 3,
    3, 8, 7,
    18, 19, 4,
    4, 3, 18,
};

unsigned int tblock[] {
    7, 8, 12,
    12, 13, 8,
    18, 19, 4,
    4, 3, 18,
};

unsigned int oblock[] {
    22, 24, 14,
    14, 12, 22,
};

unsigned int sblock[] {
    23, 24, 14,
    14, 13, 23,
    18, 8, 7,
    7, 17, 18,
};

unsigned int zblock[] {
    22, 23, 13,
    22, 12, 13,
    18, 19, 9,
    9, 8, 18,
};

//  switch(choice) {
//      case 0:
//          BLOC = EBO(iblock, sizeof(iblock));
//          break;
//      case 1:
//          BLOC = EBO(jblock, sizeof(jblock));
//          break;
//      case 2:
//          BLOC = EBO(lblock, sizeof(lblock));
//          break;
//      case 3:
//          BLOC = EBO(tblock, sizeof(tblock));
//          break;
//      case 4:
//          BLOC = EBO(oblock, sizeof(oblock));
//          break;
//      case 5:
//          BLOC = EBO(sblock, sizeof(sblock));
//          break;
//      case 6:
//          BLOC = EBO(zblock, sizeof(zblock));
//          break;
//  }

//  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//      x -= 0.7f * deltaTime;
//  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//      x += 0.7f * deltaTime;

//  glm::mat4 model = glm::mat4(1.0f);
//  model = glm::translate(model, glm::vec3(x, y, 0.0f));
//  glfwGetWindowSize(window, &windowW, &windowH);
//  model = glm::scale(model, glm::vec3(1.0f, (float)windowW / (float)windowH, 1.0f) * blocScale);
//  shaderPogram.setMat4f("model", 1, glm::value_ptr(model));

//  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

// if(y < -(1.0f + blocScale[1] * (float)windowW / (float)windowH))
//     y = 1.0f + blocScale[1] * (float)windowW / (float)windowH;
// else
//     y -= 0.2f * deltaTime;
