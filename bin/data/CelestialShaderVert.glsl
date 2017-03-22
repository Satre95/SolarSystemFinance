#version 410 core

layout (location = 0) in vec3 position;
layout (location = 0) in vec4 color;

uniform mat4 modelViewProjectionMatrix;

void main() {
	gl_Position = modelViewProjectionMatrix * vec4(position, 1.0f);
}