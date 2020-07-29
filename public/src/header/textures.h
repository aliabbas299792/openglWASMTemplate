#ifndef TEXTURES
#define TEXTURES

#include <unordered_map>
#include <iostream>

#include "header/shader.h"

#include <emscripten/emscripten.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>

class texturesManager {
private:
  std::unordered_map<std::string, std::pair<GLenum, unsigned  int>> textureStore;
  shader *localShaderStore = NULL;
public:
  texturesManager(shader *shaderStore);
  unsigned int loadAndUseNewTexture(std::string filePath, std::string textureName, GLenum textureUnit);
  void activateAndBindTextures();
};

#endif
