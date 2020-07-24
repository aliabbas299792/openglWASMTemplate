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
    unsigned int currentlyActiveShader = -1; //the ID of the currently active shader
public:
    unsigned int createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const std::string& programName);
    unsigned int useShaderProgram(const std::string& shaderProgramName);
    void deleteShaderProgram(const std::string& shaderProgramName);
    void setUniform1f(std::string uniformName, float value);
    void setUniform2f(std::string uniformName, float value1, float value2);
    void setUniform3f(std::string uniformName, float value1, float value2, float value3);
    void setUniform4fv(std::string uniformName, int count, bool transpose, const float* value);
};

#endif
