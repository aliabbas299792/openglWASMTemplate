#include <functional>
#include <unistd.h>

#include <emscripten/emscripten.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>

#include "header/helper.h"
#include "header/shader.h"
#include "header/textures.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::function<void()> lambdaDrawLoop;
void drawLoop() { lambdaDrawLoop(); }

GLFWwindow *window = NULL; //global window
shader Shader;

texturesManager TexturesManager(&Shader);

int main() {
  initWindow();

  const std::string shaderProgramName = "default";
  const unsigned int shaderProgram = Shader.createShaderProgram("assets/glsl/vertexshader.glsl", "assets/glsl/fragshader.glsl", shaderProgramName);

  float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
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
  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  unsigned int EBO; //element buffer object
  glGenBuffers(1, &EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //ebo object
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //copy the indexed ebo data

  /////
  //attribute stuff
  /////
  const int stride = 8 * sizeof(float); //6 floats per element

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0); //for basically telling how OpenGL should interpret the VBO data
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float))); //offset of 3
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float))); //offset of 6
  glEnableVertexAttribArray(2);

  int width, height, prevWidth, prevHeight; //will store the height and width, updated in the main loop (and below, to initialise)
  glfwGetWindowSize(window, &width, &height);

  TexturesManager.loadAndUseNewTexture("assets/images/cross.jpg", "cross", GL_TEXTURE0);
  TexturesManager.loadAndUseNewTexture("assets/images/naught.jpg", "naught", GL_TEXTURE1);

  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  Shader.setUniform4fv("view", 1, false, glm::value_ptr(view));

  lambdaDrawLoop = [&] {
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      prevWidth = width;
      prevHeight = height;
      glfwGetWindowSize(window, &width, &height); //sets the width and height variables

      if(width != prevWidth || height != prevHeight){ //so only runs when the screen size changes
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
        Shader.setUniform4fv("projection", 1, false, glm::value_ptr(projection));
      }

      glUseProgram(shaderProgram);

      Shader.setUniform2f("screenSize", (float)width, (float)height); //sets the size uniform
      Shader.setUniform1f("time", (float)glfwGetTime()); //sets the time uniform

      glm::mat4 model = glm::mat4(1.0f);

      model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(5.0f, 10.0f, 15.0f));

      Shader.setUniform4fv("model", 1, false, glm::value_ptr(model));

      TexturesManager.activateAndBindTextures(); //activates and binds textures

      glBindVertexArray(VAO);
      //glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/stride); //divides the size of the array by the stride to get the actual count
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); //last param is the offset of the start of the indices

      glfwSwapBuffers(window);
      glfwPollEvents();
  };

  emscripten_set_main_loop(drawLoop, -1, true); //sets the emscripten main loop
}