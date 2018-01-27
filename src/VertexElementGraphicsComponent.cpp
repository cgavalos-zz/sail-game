#include "VertexElementGraphicsComponent.h"

void VertexElementGraphicsComponent::initializeState() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	glVertexArrayElementBuffer(vao, elementBuffer);
}

VertexElementGraphicsComponent::VertexElementGraphicsComponent() {}

VertexElementGraphicsComponent::VertexElementGraphicsComponent(
	std::vector<glm::vec3> const & vertices,
	std::vector<GLuint> const & elements) {

	initializeState();
	setVertexBuffer(vertices.size() * 3, (GLfloat *)vertices.data());
	setElementBuffer(elements.size(), elements.data());
}

VertexElementGraphicsComponent::VertexElementGraphicsComponent(
	std::vector<GLfloat> const & vertices,
	std::vector<GLuint> const & elements) {

	initializeState();
	setVertexBuffer(vertices.size(), vertices.data());
	setElementBuffer(elements.size(), elements.data());
}

VertexElementGraphicsComponent::VertexElementGraphicsComponent(
	size_t vLength, GLfloat const * vData,
	size_t elLength, GLuint const * elData) {

	initializeState();
	setVertexBuffer(vLength, vData);
	setElementBuffer(elLength, elData);
}

void VertexElementGraphicsComponent::setVertexBuffer(
	size_t length, 
	GLfloat const * data) const {
	glNamedBufferData(vertexBuffer, sizeof(GLfloat) * length, data, GL_STREAM_DRAW);
}

void VertexElementGraphicsComponent::updateVertexBuffer(
	size_t length, 
	GLfloat const * data) const {
	glNamedBufferSubData(vertexBuffer, 0, sizeof(GLfloat) * length, data);
}

void VertexElementGraphicsComponent::setElementBuffer(
	size_t length, 
	GLuint const * data) {
	numElements = length;
	glNamedBufferData(elementBuffer, sizeof(GLuint) * length, data, GL_STATIC_DRAW);
}

void VertexElementGraphicsComponent::updateElementBuffer(
	size_t length, 
	GLuint const * data) const {
	glNamedBufferSubData(elementBuffer, 0, sizeof(GLuint) * length, data);
}

void VertexElementGraphicsComponent::use(GLuint program) const {
	glUseProgram(program);
	glBindVertexArray(vao);
}

void VertexElementGraphicsComponent::draw() const {
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

GLuint VertexElementGraphicsComponent::getVertexBuffer() const {
	return vertexBuffer;
}