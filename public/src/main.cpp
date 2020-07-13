#include <functional>
#include <unistd.h>

#include <emscripten/emscripten.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include <cmath>

#include "header/helper.h"
#include "header/shader.h"

std::function<void()> lambdaDrawLoop;
void drawLoop() { lambdaDrawLoop(); }

GLFWwindow *window = NULL; //global window
shader shaderStore;

int main() {
  initWindow();

  const unsigned int shaderProgram = shaderStore.createShaderProgram("assets/vertexshader.glsl", "assets/fragshader.glsl", "default");

  float vertices[] = {
          -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.0f, 0.5f, 0.0f
  };

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO); //bind it

  unsigned int VBO;
  glGenBuffers(1, &VBO); //generates 1 vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO); //buffer type of vertex buffer object is GL_ARRAY_BUFFER

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copies the buffer data into memory

  int posAttrib = glGetAttribLocation(shaderProgram, "pos"); //gets attribute index with name pos
  glEnableVertexAttribArray(posAttrib); //enables that, so the next operation happens for that index
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //for basically telling how OpenGL should interpret the VBO data

  int width, height; //will store the height and width, updated in the main loop

  lambdaDrawLoop = [&] {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glfwGetWindowSize(window, &width, &height); //sets the width and height variables

    int screenSizeLocation = glGetUniformLocation(shaderProgram, "screenSize");
    glUniform2f(screenSizeLocation, (float)width, (float)height); //sets the uniform

    int timeLocation = glGetUniformLocation(shaderProgram, "time");
    glUniform1f(timeLocation, (float)glfwGetTime()); //sets the time uniform

    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  };

  emscripten_set_main_loop(drawLoop, -1, true); //sets the emscripten main loop

  return EXIT_SUCCESS;
}