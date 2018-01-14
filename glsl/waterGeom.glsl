#version 430 core
#include glsl/bigBlock.glsl

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 model;
uniform bool allBlack;

out vec3 onormal;

void main() {

	vec3 tempNormal = cross(
					vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position), 
					vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position));

	mat4 vm = view * model;
	onormal = normalize(mat3(vm) * normalize(tempNormal));
	mat4 pvm = projection * vm;

	gl_Position = pvm * gl_in[0].gl_Position;
	if (allBlack) {
		gl_Position.z -= 0.01f;
	}
	EmitVertex();
	gl_Position = pvm * gl_in[1].gl_Position;
	if (allBlack) {
		gl_Position.z -= 0.01f;
	}
	EmitVertex();
	gl_Position = pvm * gl_in[2].gl_Position;
	if (allBlack) {
		gl_Position.z -= 0.01f;
	}
	EmitVertex();

	EndPrimitive();
}
