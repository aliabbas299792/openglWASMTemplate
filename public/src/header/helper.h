#ifndef HELPER
#define HELPER

#include <emscripten/emscripten.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include <fstream>
#include <iostream>

std::string readFile(std::string fileName);
int initWindow();

extern GLFWwindow* window; //this will be a global variable for use elsewhere

extern "C" {
  void EMSCRIPTEN_KEEPALIVE setWindowSize(int width, int height);
}

#endif