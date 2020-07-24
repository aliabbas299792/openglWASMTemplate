#include "header/shader.h"
#include "header/helper.h"

unsigned int shader::compileShader(const std::string& fileName, GLenum shader_type) {
  std::string sourceFile = readFile(fileName);
  const char* sourceCString = sourceFile.c_str();

  unsigned int shader;
  shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &sourceCString, nullptr);
  glCompileShader(shader); //compiles the shader

  int success; //indicates the success
  char infoLog[512]; //possible error info
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success){ //if there was an issue, print the error
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    const std::string shaderType = shader_type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader"; //const GLubyte* is literally just const char*, so can convert directly to string
    std::cout << "Shader Compilation Failed (type: " << shaderType << "): " << infoLog << "\n";
  }

  return shader;
}

unsigned int shader::compileVertexShader(const std::string& fileName) {
  return compileShader(fileName, GL_VERTEX_SHADER);
}

unsigned int shader::compileFragmentShader(const std::string& fileName) {
  return compileShader(fileName, GL_FRAGMENT_SHADER);
}

unsigned int shader::createShaderProgram(const std::string& vertexShaderSourceLocation, const std::string& fragmentShaderSourceLocation, const std::string& programName) {
  const unsigned int vertexShader = compileVertexShader(vertexShaderSourceLocation);
  const unsigned int fragmentShader = compileFragmentShader(fragmentShaderSourceLocation);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  //below 2 lines add 2 compiled shaders
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  //below links all the attached programs into one larger program
  glLinkProgram(shaderProgram);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success){ //will print errors
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "Shader Program Compile Error: " << infoLog << "\n";
  }

  glUseProgram(shaderProgram); //uses the program by default

  shaderPrograms.insert({programName, shaderProgram}); //insert the program into the unordered map

  //deletes the independent programs since we have linked them in the shaderProgram
  glDeleteProgram(vertexShader);
  glDeleteProgram(fragmentShader);

  this->currentlyActiveShader = shaderProgram;

  return shaderProgram;
}

unsigned int shader::useShaderProgram(const std::string& shaderProgramName) {
  const unsigned int program = shaderPrograms[shaderProgramName];
  glUseProgram(program);

  this->currentlyActiveShader = program;

  return program;
}

void shader::deleteShaderProgram(const std::string& shaderProgramName) {
  const unsigned int program = this->shaderPrograms[shaderProgramName];
  this->shaderPrograms.erase(shaderProgramName);
  glDeleteProgram(program);
}

void shader::setUniform1f(std::string uniformName, float value) {
  glUniform1f(
    glGetUniformLocation(this->currentlyActiveShader, uniformName.c_str()),
    value
  );
}

void shader::setUniform2f(std::string uniformName, float value1, float value2) {
  glUniform2f(
    glGetUniformLocation(this->currentlyActiveShader, uniformName.c_str()),
    value1,
    value2
  );
}

void shader::setUniform3f(std::string uniformName, float value1, float value2, float value3) {
  glUniform3f(
    glGetUniformLocation(this->currentlyActiveShader, uniformName.c_str()),
    value1,
    value2,
    value3
  );
}

void shader::setUniform4fv(std::string uniformName, int count, bool transpose, const float *value) {
  glUniformMatrix4fv(
    glGetUniformLocation(this->currentlyActiveShader, uniformName.c_str()),
    count,
    transpose,
    value
  );
}
