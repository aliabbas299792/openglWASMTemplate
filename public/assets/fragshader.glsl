#version 300 es
precision mediump float; //needed for OpenGL ES

uniform vec2 screenSize;
uniform float time;
out vec4 FragColour;

void main() {
  float xColour = pow(sin(time), 2.0f) * gl_FragCoord.x/screenSize.x;
  float yColour = pow(cos(time), 2.0f) * gl_FragCoord.y/screenSize.y;
  float zColour = pow(sin(time/2.0f), 2.0f) * gl_FragCoord.x/screenSize.x;
  FragColour = vec4(xColour, yColour, zColour, 1.0f);
}