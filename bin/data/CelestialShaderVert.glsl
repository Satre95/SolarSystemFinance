#version 410 core

in vec4 position;
in vec4 color;

out vec4 fragColor;

uniform mat4 orientationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

void main() {
	gl_Position = modelViewProjectionMatrix * position;
	fragColor = color;


}