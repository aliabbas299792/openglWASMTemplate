#version 300 es
precision mediump float; //needed for OpenGL ES

uniform vec2 screenSize;
uniform float time;

uniform vec3 lightColour;
uniform vec3 lightPos;

in vec3 fragPos;
in vec2 texCoords;
in vec3 normal;

//textures defined via assimp
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;

out vec4 FragColour;

void main() {
  float ambientStrength = 0.1f;
  vec3 ambient = ambientStrength * lightColour;

  float xColour = pow(sin(time), 2.0f) * gl_FragCoord.x/screenSize.x + 0.1f;
  float yColour = pow(cos(time), 2.0f) * gl_FragCoord.y/screenSize.y + 0.1f;
  float zColour = pow(sin(time/2.0f), 2.0f) * gl_FragCoord.x/screenSize.x + 0.1f;
  vec3 objectColour = vec3(xColour, yColour, zColour);

  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);

  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);

  FragColour = vec4((ambient + diffuse), 1.0f) * mix(texture(texture_diffuse1, texCoords), texture(texture_specular1, texCoords), 0.5);
}