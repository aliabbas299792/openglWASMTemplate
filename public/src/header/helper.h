#ifndef HELPER
#define HELPER

#include <fstream>
#include <iostream>

#include <emscripten/emscripten.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>

#include "header/shader.h"

std::string readFile(const std::string &filename); //actually just calls a JS function to get the files
int initWindow(); //initialises the window

extern GLFWwindow* window; //this will be a global variable for use elsewhere

extern "C" {
  void EMSCRIPTEN_KEEPALIVE setWindowSize(int width, int height);
}

#endif