#version 430 core
#include bigBlock.glsl

in vec3 position;
out vec3 pos;

uniform mat4 model;

void main() {
	gl_Position = projection * view * model * vec4(position, 1);
	pos = vec3(model * vec4(position, 1));
}