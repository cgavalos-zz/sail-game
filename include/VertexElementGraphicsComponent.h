#pragma once

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

class VertexElementGraphicsComponent {
private:
	unsigned int numElements;
	GLuint vao;
	GLuint vertexBuffer;
	GLuint elementBuffer;

	void initializeState();
public:
	VertexElementGraphicsComponent();
	VertexElementGraphicsComponent(
		std::vector<GLfloat> const & vertexData,
		std::vector<GLuint> const & elements);
	VertexElementGraphicsComponent(
		std::vector<glm::vec3> const & vertices,
		std::vector<GLuint> const & elements);
	VertexElementGraphicsComponent(
		size_t vLength, GLfloat const * vData,
		size_t elLength, GLuint const * elData);
	void setVertexBuffer(size_t length, GLfloat const * data) const;
	void updateVertexBuffer(size_t length, GLfloat const * data) const;
	void setElementBuffer(size_t length, GLuint const * data);
	void updateElementBuffer(size_t length, GLuint const * data) const;
	void use(GLuint program) const;
	void draw() const;
	GLuint getVertexBuffer() const;
};
