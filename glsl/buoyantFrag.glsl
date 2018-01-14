#version 430 core

in vec3 pos;
out vec4 finalColor;

void main() {
	if (pos.y < 0) {
		finalColor = vec4(0, 0, 1, 1);
	} else {
		finalColor = vec4(1, 0, 0, 1);
	}
}
