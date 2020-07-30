#include "header/assimp.h"

mesh::mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  setupMesh();
}

void mesh::draw(shader *ShaderProgram) {
  unsigned int diffuseNumber = 1; //up to 3 diffuse textures
  unsigned int specularNumber = 1; //up to 3 specular textures

  for(unsigned int i = 0; i < textures.size(); i++){
    glActiveTexture(GL_TEXTURE0 + i); //activate the proper texture binding

    std::string number;
    std::string name = textures[i].type;
    if(name == "texture_diffuse")
      number = std::to_string(diffuseNumber++);
    else if(name == "texture_specular")
      number = std::to_string(specularNumber++);

    ShaderProgram->setUniform1f("material." + name + number, i); //sets the uniform and adds material. to the beginning
    glBindTexture(GL_TEXTURE_2D, textures[i].id);
  }
  glActiveTexture(GL_TEXTURE0); //resets the active texture back to 0

  //draws the mesh
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0); //reset the bound vertex array
}

void mesh::setupMesh() {
  glGenVertexArrays(1, &VAO); //generate VAO
  //generate buffers for the data
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO); //bind VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW); //copies the buffer data into memory

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //ebo object
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned  int), indices.data(), GL_STATIC_DRAW); //copy the indexed ebo data

  //vector.data() basically returns &vector[0] - a pointer to the first element

  const int stride = 8 * sizeof(float); //6 floats per element

  //vertex positions
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0); //for basically telling how OpenGL should interpret the VBO data
  glEnableVertexAttribArray(0);
  //vertex normals
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float))); //offset of 3
  glEnableVertexAttribArray(1);
  //vertex texture coords
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float))); //offset of 6
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); //resets the existing vertex array object binding

  //the reason why using vectors and structs works is because they are all sequential in memory, otherwise you can't use them in the buffer data
  //an array of structs of size 10, where each struct has 3 elements is like an array of 30 elements sequential in memory
}
