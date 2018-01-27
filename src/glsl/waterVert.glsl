#version 430 core

in float z;

uniform int verticesPerSide;

void main() {
	
	// gl_VertexID is what the element buffer spits out
	int x = gl_VertexID % verticesPerSide;
	int y = gl_VertexID / verticesPerSide;

	gl_Position = vec4(x, y, z, 1);
}