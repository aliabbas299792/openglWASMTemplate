#version 300 es
precision mediump float; //needed for OpenGL ES

uniform vec2 screenSize;
uniform float time;

uniform vec3 lightColour;
uniform vec3 lightPos;

out vec4 FragColour;

in vec3 normal;
in vec3 fragPos;

void main() {
  float ambientStrength = 0.3f;
  vec3 ambient = ambientStrength * lightColour;

  float xColour = pow(sin(time), 2.0f) * gl_FragCoord.x/screenSize.x + 0.1f;
  float yColour = pow(cos(time), 2.0f) * gl_FragCoord.y/screenSize.y + 0.1f;
  float zColour = pow(sin(time/2.0f), 2.0f) * gl_FragCoord.x/screenSize.x + 0.1f;
  vec3 objectColour = vec3(xColour, yColour, zColour);

  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);

  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);

  FragColour = vec4( (ambient + diffuse) * objectColour, 1.0f);
}