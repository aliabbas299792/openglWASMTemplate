#ifndef SHADER
#define SHADER

#include <unordered_map>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include <iostream>

class shader{
private:
    std::unordered_map<std::string, unsigned int> shaderPrograms;
    unsigned int compileShader(const std::string& fileName, GLenum shader_type);
    unsigned int compileVertexShader(const std::string& fileName);
    unsigned int compileFragmentShader(const std::string& fileName);
public:
    unsigned int createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const std::string& programName);
    unsigned int useShaderProgram(const std::string& shaderProgramName);
    void deleteShaderProgram(const std::string& shaderProgramName);
};

#endif
