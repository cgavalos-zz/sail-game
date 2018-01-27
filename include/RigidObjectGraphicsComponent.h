#pragma once

#include <GL/glew.h>
#include <vector>

#include "ShaderMisc.h"
#include "VertexElementGraphicsComponent.h"

class RigidObjectGraphicsComponent {
private:
	GLuint program;
	VertexElementGraphicsComponent vegc;
public:
	GLuint getProgram() const;
	RigidObjectGraphicsComponent(
		std::vector<glm::vec3> const & vertices,
		std::vector<unsigned int> const & elements);
	void update(glm::mat4 const & modelMatrix) const;
};