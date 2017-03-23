#version 410 core
in vec4 fragColor;

uniform sampler2D tex;

out vec4 finalColor;
void main() {
	finalColor = texture(tex, gl_PointCoord);
}