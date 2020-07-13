#include "header/helper.h"

std::string readFile(std::string filename){ //simple file reading function
  std::ifstream file(filename);

  file.seekg(0, std::ios::end); //seek to end of file
  int size = file.tellg(); //get size of file
  std::string buffer(size, ' ');
  file.seekg(0); //seek back to beginning of file
  file.read(&buffer[0], size);

  return buffer;
}

extern "C" {
void EMSCRIPTEN_KEEPALIVE setWindowSize(int width, int height){ //since this is called from JS it needs to be able to access the global variable window from main.cpp
  glfwSetWindowSize(window, width, height);
  glViewport(0, 0, width, height);
}
}

int initWindow(){ //will create the window using the global window
  if(!glfwInit()){
    std::cout << "Failed to initialise GLFW: " << stderr << "\n";
    emscripten_force_exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);

  window  = glfwCreateWindow(800, 450, "Window", NULL, NULL); //initial size of 800x450

  if(!window){
    std::cout << "Failed to create GLFW window" << "\n";
    glfwTerminate();
    emscripten_force_exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  glViewport(0, 0, 800, 450);

  return 1;
}