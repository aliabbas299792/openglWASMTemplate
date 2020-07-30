#ifndef SHADER
#define SHADER

#include <unordered_map>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include <iostream>

class shader{
private:
    unsigned int compileShader(const std::string& fileName, GLenum shader_type);
    unsigned int compileVertexShader(const std::string& fileName);
    unsigned int compileFragmentShader(const std::string& fileName);
    unsigned int shaderProgramID = -1;
public:
    shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    unsigned int useShaderProgram();
    void deleteShaderProgram();
    void setUniform1f(std::string uniformName, float value);
    void setUniform1i(std::string uniformName, int value);
    void setUniform2f(std::string uniformName, float value1, float value2);
    void setUniform3f(std::string uniformName, float value1, float value2, float value3);
    void setUniform4fv(std::string uniformName, int count, bool transpose, const float* value);
};

#endif
