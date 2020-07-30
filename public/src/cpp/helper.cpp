#include "header/helper.h"

#define STB_IMAGE_IMPLEMENTATION //since we're going to make functions which use it
#include <stb/stb_image.h>

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

void initWindow(){ //will create the window using the global window
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
}

unsigned int loadTextureFromFile(std::string directory, std::string filename) {
  stbi_set_flip_vertically_on_load(true);
  //OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom side of the image, but images usually have 0.0 at the top of the y-axis
  //This vertically flips it
  //directly quoted from learnopengl.com

  std::string filepath = directory + '/' + filename;

  unsigned int texture;
  glGenTextures(1, &texture); //generates a texture
  glBindTexture(GL_TEXTURE_2D, texture);

  //s, t and r are the texture equivalents for x, y and z
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //GL_LINEAR basically blurs it by taking the average of pixels if the texture is scaled up (so kinda smoother)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, numChannels;
  unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &numChannels, 0);
  //set last param to 0 to allow however many channels there are normally (usually 8, i.e usually 8 bits per pixel)

  if(data){
    glTexImage2D( //set properties of the texture
      GL_TEXTURE_2D,
      0/*mip map level*/,
      GL_RGB/*colour components in the image*/,
      width,
      height,
      0,
      GL_RGB/*format of the pixel data*/,
      GL_UNSIGNED_BYTE,
      data
    );
    glGenerateMipmap(GL_TEXTURE_2D); //currently bound texture object now has the texture image attached to it
  }else{
    std::cout << "There was an error with loading the image from: " << filepath << "\n";
    emscripten_force_exit(-1); //there was an error
  }

  stbi_image_free(data); //frees the memory for this image

  return texture;
}