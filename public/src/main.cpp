#include <functional>
#include <unistd.h>

#include <emscripten/emscripten.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include <cmath>

#include "header/helper.h"
#include "header/shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::function<void()> lambdaDrawLoop;
void drawLoop() { lambdaDrawLoop(); }

GLFWwindow *window = NULL; //global window
shader shaderStore;

int main() {
  initWindow();

  const unsigned int shaderProgram = shaderStore.createShaderProgram("assets/vertexshader.glsl", "assets/fragshader.glsl", "default");

  float vertices[] = {
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

          -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

          -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
          -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

          0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
          0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
          0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
          0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

          -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
          0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

          -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
          0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
          -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
          -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
  };

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO); //bind it

  /////
  //VBO stuff
  /////
  unsigned int VBO;
  glGenBuffers(1, &VBO); //generates 1 vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO); //buffer type of vertex buffer object is GL_ARRAY_BUFFER

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copies the buffer data into memory

  /////
  //EBO stuff
  /////
  /*
  unsigned int EBO; //element buffer object
  glGenBuffers(1, &EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //ebo object
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //copy the indexed ebo data
  */

  /////
  //attribute stuff
  /////
  int posAttrib = glGetAttribLocation(shaderProgram, "pos"); //gets attribute index with name pos
  glEnableVertexAttribArray(posAttrib); //enables that, so the next operation happens for that index
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //for basically telling how OpenGL should interpret the VBO data

  int normalAttrib = glGetAttribLocation(shaderProgram, "norm");
  glEnableVertexAttribArray(normalAttrib);
  glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

  int width, height; //will store the height and width, updated in the main loop

  lambdaDrawLoop = [&] {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwGetWindowSize(window, &width, &height); //sets the width and height variables

    glUseProgram(shaderProgram);

    shaderStore.setUniform2f("screenSize", (float)width, (float)height); //sets the size uniform
    shaderStore.setUniform1f("time", (float)glfwGetTime()); //sets the time uniform

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(5.0f, 10.0f, 15.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

    shaderStore.setUniform4fv("model", 1, false, glm::value_ptr(model));
    shaderStore.setUniform4fv("view", 1, false, glm::value_ptr(view));
    shaderStore.setUniform4fv("projection", 1, false, glm::value_ptr(projection));

    shaderStore.setUniform3f("lightColour", 1.0f, 1.0f, 1.0f);
    shaderStore.setUniform3f("lightPos", 0.0f, 10.0f, 3.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36); //divide by 2 since we have 3 elements per vertex for the normal

    //EBO drawing
    /*
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
    */

    glfwSwapBuffers(window);
    glfwPollEvents();
  };
  
  emscripten_set_main_loop(drawLoop, -1, true); //sets the emscripten main loop

  return EXIT_SUCCESS;
}
