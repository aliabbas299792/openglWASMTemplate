#include "header/textures.h"

#define STB_IMAGE_IMPLEMENTATION //since we're going to make functions which use it
#include <stb/stb_image.h>

texturesManager::texturesManager(shader *shaderStore) {
  localShaderStore = shaderStore;
}

unsigned int texturesManager::loadAndUseNewTexture(std::string filePath, std::string textureName, GLenum textureUnit) {
  stbi_set_flip_vertically_on_load(true);
  //OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom side of the image, but images usually have 0.0 at the top of the y-axis
  //This vertically flips it
  //directly quoted from learnopengl.com

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
  unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &numChannels, 0);
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
    std::cout << "There was an error with loading the image from: " << filePath << "\n";
    emscripten_force_exit(-1); //there was an error
  }

  stbi_image_free(data); //frees the memory for this image

  localShaderStore->setUniform1i(textureName, textureUnit - GL_TEXTURE0); //this will ensure the minimum value is 0

  textureStore[textureName] = {textureUnit, texture};

  return texture;
}

void texturesManager::activateAndBindTextures() {
  for(const auto& textureData : textureStore){
    glActiveTexture(textureData.second.first); //the texture unit
    glBindTexture(GL_TEXTURE_2D, textureData.second.second); //the texture
  }
}