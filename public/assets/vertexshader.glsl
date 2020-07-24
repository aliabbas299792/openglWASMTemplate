#version 300 es
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 normal;

void main() {
  fragPos = vec3(model * vec4(pos, 1.0f));
  normal = mat3(transpose(inverse(model))) * norm;

  gl_Position = projection * view * vec4(fragPos, 1.0);
}