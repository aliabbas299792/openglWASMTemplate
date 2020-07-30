#ifndef ASSIMP
#define ASSIMP

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "header/shader.h"

#include <emscripten.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct texture {
    unsigned int id;
    std::string type; //diffuse/specular type
    std::string path; //store the path to compare with other textures and prevent duplicates
};

class mesh{
public:
    //mesh data
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<texture> textures;

    mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures);
    void draw(shader* ShaderProgram);
private:
    unsigned int VAO, VBO, EBO; //render data

    void setupMesh();
};

class model{
private:
    //model data
    std::vector<texture> textures_loaded;
    std::vector<mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
public:
    model(std::string path);
    void draw(shader *ShaderProgram);
};

#endif
