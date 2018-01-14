#include "RigidObjectGraphicsComponent.h"

#include <glm/gtc/type_ptr.hpp>

GLuint RigidObjectGraphicsComponent::getProgram() const {
	return program;
}

RigidObjectGraphicsComponent::RigidObjectGraphicsComponent(
	std::vector<glm::vec3> const & vertices,
	std::vector<unsigned int> const & elements) : vegc(vertices, elements) {

	std::vector<GLenum> types({
		GL_VERTEX_SHADER, GL_FRAGMENT_SHADER });

	std::vector<std::string> filenames({
		"buoyantVert.glsl", "buoyantFrag.glsl" });

	program = programSetup(types, filenames);
	glUseProgram(program);

	GLuint pLoc = glGetAttribLocation(program, "position");

	glEnableVertexAttribArray(pLoc);
	glVertexAttribPointer(pLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void RigidObjectGraphicsComponent::update(glm::mat4 const & modelMatrix) const {

	vegc.use(program);

	glUniformMatrix4fv(
		glGetUniformLocation(program, "model"),
		1,
		GL_FALSE,
		glm::value_ptr(modelMatrix));

	vegc.draw();
}
