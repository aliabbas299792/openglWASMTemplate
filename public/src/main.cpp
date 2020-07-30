#include <functional>
#include <unistd.h>

#include <emscripten/emscripten.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>

#include "header/helper.h"
#include "header/shader.h"
#include "header/assimp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::function<void()> lambdaDrawLoop;
void drawLoop() { lambdaDrawLoop(); }

GLFWwindow *window = NULL; //global window, defined as an extern in helper.h

int main() {
  initWindow();

  shader ShaderProgram("assets/glsl/vertexshader.glsl", "assets/glsl/fragshader.glsl");

  model backpack("assets/models/backpack/backpack.obj");

  int width, height, prevWidth, prevHeight; //will store the height and width, updated in the main loop (and below, to initialise)
  glfwGetWindowSize(window, &width, &height);

  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
  ShaderProgram.setUniform4fv("view", 1, false, glm::value_ptr(view));

  lambdaDrawLoop = [&] {
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      prevWidth = width;
      prevHeight = height;
      glfwGetWindowSize(window, &width, &height); //sets the width and height variables

      ShaderProgram.setUniform3f("lightColour", 1.0f, 1.0f, 1.0f);
      ShaderProgram.setUniform3f("lightPos", 0.0f, 10.0f, 3.0f);

      if(width != prevWidth || height != prevHeight){ //so only runs when the screen size changes
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
        ShaderProgram.setUniform4fv("projection", 1, false, glm::value_ptr(projection));
      }

      ShaderProgram.useShaderProgram();

      ShaderProgram.setUniform2f("screenSize", (float)width, (float)height); //sets the size uniform
      ShaderProgram.setUniform1f("time", (float)glfwGetTime()); //sets the time uniform

      glm::mat4 model = glm::mat4(1.0f);

      model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(5.0f, 10.0f, 15.0f));

      ShaderProgram.setUniform4fv("model", 1, false, glm::value_ptr(model));

      backpack.draw(&ShaderProgram);

      glfwSwapBuffers(window);
      glfwPollEvents();
  };

  emscripten_set_main_loop(drawLoop, -1, true); //sets the emscripten main loop
}