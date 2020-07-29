#include "header/helper.h"

extern "C"{
  extern const char* getFile(const char* filename, int length);
}

std::string readFile(const std::string &filename){ //calls a JavaScript function to get the data (it should be pre-fetched however)
  const char* data = getFile(filename.c_str(), filename.size()); //get the file via JavaScript
  const std::string returnData = data; //make a copy of the string
  free((void*)data); //free the allocated memory

  return returnData;
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
  glEnable(GL_DEPTH_TEST);

  return 1;
}