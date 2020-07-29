#version 300 es
precision mediump float; //needed for OpenGL ES

uniform vec2 screenSize;
uniform float time;

in vec3 fragPos;
in vec3 colour;
in vec2 texCoords;

uniform sampler2D cross;
uniform sampler2D naught;

out vec4 FragColour;

void main() {
  float xColour = pow(sin(time), 2.0f) * gl_FragCoord.x/screenSize.x + 0.1f;
  float yColour = pow(cos(time), 2.0f) * gl_FragCoord.y/screenSize.y + 0.1f;
  float zColour = pow(sin(time/2.0f), 2.0f) * gl_FragCoord.x/screenSize.x + 0.1f;
  vec3 objectColour = vec3(xColour, yColour, zColour);

  FragColour = mix(texture(cross, texCoords), texture(naught, texCoords), 0.5) * vec4(colour * objectColour, 1.0f);
}